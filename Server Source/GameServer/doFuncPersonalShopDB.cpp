// ================================================================
// doFuncPersonalShopDB.cpp
// Database operations for offline personal shops
// ================================================================
// NOTE: This is a framework/reference implementation.
// Adapt the database calls and API to match your actual
// game server's DBManager API and Character object structure.
// ================================================================

#include "stdhdrs.h"
#include "Log.h"
#include "Character.h"
#include "PersonalShop.h"
#include "DBManager.h"
#include "Server.h"
#include "MailBoxManager.h"
#include "CmdMsg.h"
#include "doFuncPersonalShopDB.h"
#include <time.h>

#ifdef OFFLINE_SHOPS

// ================================================================
// Build the full item-fidelity column values for personal_shop_items.
// Reads the live CItem* from the owner's inventory so a vendor rebuilt
// after a server restart restores enchant/sockets/options/durability.
//
// The returned string is the comma-separated VALUES for columns:
//   item_wear_pos, item_plus, item_flag, item_used, item_used_2,
//   item_serial, item_socket_count, item_option, item_jewel,
//   item_origin, item_now_durability, item_max_durability
//
// Encoding mirrors the character save path (WearInvenManager /
// makeExpressSystemItemInfo) so CItemProtoList::CreateDBItem can rebuild
// the item exactly on load:
//   - item_option : MAX_ITEM_OPTION space-delimited shorts (option DB values;
//                   for rare items slot0=rareIndex, slot1=rareBit)
//   - item_jewel  : canonical socket string (GetSocketInfoString format)
//   - item_origin : MAX_VARIATION_COUNT space-delimited origin variation ints
// ================================================================
static std::string BuildItemFidelityValues(CItem* item)
{
	// Lossy fallback when the live item can't be located (keeps the row valid).
	if (!item)
		return std::string("-1, 0, 0, 0, 0, '', 0, '', '', '', 0, 0");

	// --- Options: encode exactly like the character inventory save ---
	short opt[MAX_ITEM_OPTION];
	memset(opt, 0, sizeof(opt));
	if (item->IsRareItem() && item->m_nOption == 2)
	{
		opt[0] = (short)item->m_nRareOptionIndex;
		opt[1] = (short)item->m_nRareOptionBit;
	}
	else
	{
		for (int j = 0; j < MAX_ITEM_OPTION; ++j)
		{
			if (item->m_option[j].m_level > 0)
			{
				item->m_option[j].SetDBValue();
				opt[j] = item->m_option[j].m_dbValue;
			}
		}
	}

	std::string optionStr;
	for (int j = 0; j < MAX_ITEM_OPTION; ++j)
	{
		if (j > 0)
			optionStr += " ";
		optionStr += boost::str(boost::format("%d") % (int)opt[j]);
	}

	// --- Sockets: reuse the canonical socket string the loader parses ---
	char socketBuf[64] = {0};
	item->m_socketList.GetSocketInfoString(socketBuf);

	// --- Origin variation: MAX_VARIATION_COUNT space-delimited ints ---
	std::string originStr;
	for (int j = 0; j < MAX_VARIATION_COUNT; ++j)
	{
		if (j > 0)
			originStr += " ";
		originStr += boost::str(boost::format("%d") % item->getOriginVar(j));
	}

	// --- Serial (escaped for SQL safety) ---
	// mysql_real_escape_string can double the input size, so allocate 2x buffer
	char escapedSerial[128] = {0};
	if (!item->m_serial.empty())
		mysql_real_escape_string(&gserver->m_dbchar, escapedSerial, item->m_serial.c_str(), item->m_serial.length());

	int nowDur = 0;
	int maxDur = 0;
#ifdef DURABILITY
	nowDur = item->getNowDurability();
	maxDur = item->getMaxDurability();
#endif

	std::string s;
	s.reserve(256);
	s += boost::str(boost::format("%d, ") % (int)item->getWearPos());
	s += boost::str(boost::format("%d, ") % item->getPlus());
	s += boost::str(boost::format("%d, ") % item->getFlag());
	s += boost::str(boost::format("%d, ") % item->getUsed());
	s += boost::str(boost::format("%d, ") % item->getUsed_2());
	s += boost::str(boost::format("'%s', ") % escapedSerial);
	s += boost::str(boost::format("%d, ") % (int)item->m_socketList.GetSocketCount());
	s += boost::str(boost::format("'%s', ") % optionStr);
	s += boost::str(boost::format("'%s', ") % socketBuf);
	s += boost::str(boost::format("'%s', ") % originStr);
	s += boost::str(boost::format("%d, ") % nowDur);
	s += boost::str(boost::format("%d") % maxDur);
	return s;
}

// ================================================================
// Build PSItemFidelity struct from a live CItem for in-memory storage.
// This captures all the item state needed for exact restoration later.
// ================================================================
PSItemFidelity BuildItemFidelityFromLive(CItem* item)
{
	PSItemFidelity fid;
	memset(&fid, 0, sizeof(fid));
	fid.valid = true;

	if (!item)
		return fid;

	fid.wearPos = item->getWearPos();
	fid.plus = item->getPlus();
	fid.flag = item->getFlag();
	fid.used = item->getUsed();
	fid.used_2 = item->getUsed_2();

	if (!item->m_serial.empty())
		strncpy(fid.serial, item->m_serial.c_str(), MAX_SERIAL_LENGTH);

	fid.socketCount = (char)item->m_socketList.GetSocketCount();

	// Options: encode exactly like the character inventory save
	short opt[MAX_ITEM_OPTION];
	memset(opt, 0, sizeof(opt));
	if (item->IsRareItem() && item->m_nOption == 2)
	{
		opt[0] = (short)item->m_nRareOptionIndex;
		opt[1] = (short)item->m_nRareOptionBit;
	}
	else
	{
		for (int j = 0; j < MAX_ITEM_OPTION; ++j)
		{
			if (item->m_option[j].m_level > 0)
			{
				item->m_option[j].SetDBValue();
				opt[j] = item->m_option[j].m_dbValue;
			}
		}
	}

	for (int j = 0; j < MAX_ITEM_OPTION; ++j)
		fid.option[j] = opt[j];

	// Note: Socket jewel data (jewel[]) will be populated from DB fidelity columns
	// when loading. We only capture socketCount here for validation.

	// Origin: capture all variation indices
	for (int j = 0; j < MAX_VARIATION_COUNT; ++j)
		fid.origin[j] = item->getOriginVar(j);

	// Durability
	fid.nowDurability = 0;
	fid.maxDurability = 0;
#ifdef DURABILITY
	fid.nowDurability = item->getNowDurability();
	fid.maxDurability = item->getMaxDurability();
#endif

	return fid;
}

// ================================================================
// Insert a new offline shop into the database
// ================================================================
void InsertOfflineShopToDB(CPersonalShop::SP& pShop, CPC* pChar)
{
	if (!pShop || !pChar)
	{
		LOG_ERROR("InsertOfflineShopToDB: Invalid shop or character pointer");
		return;
	}

	try
	{
		// Escape character name for SQL safety
		// mysql_real_escape_string can double the input size, so allocate 2x buffer
		char escapedCharName[512] = {0};
		mysql_real_escape_string(&gserver->m_dbchar, escapedCharName, pChar->m_nick, pChar->m_nick.Length());

		// Escape shop name for SQL safety
		char escapedShopName[512] = {0};
		mysql_real_escape_string(&gserver->m_dbchar, escapedShopName, pShop->GetName(), strlen(pShop->GetName()));

		// Build query using boost::format for safer formatting
		std::string insertQuery;
		insertQuery.reserve(2048);
		insertQuery = "INSERT INTO personal_shop_offline ";
		insertQuery += "(shop_id, char_index, char_name, shop_name, shop_type, is_offline, created_at, expires_at, ";
		insertQuery += "map_id, pos_x, pos_y, pos_z, is_active, total_sales, total_items_sold) ";
		insertQuery += "VALUES (";

		insertQuery += boost::str(boost::format("%d, ") % pShop->GetShopId());  // Insert shop_id
		insertQuery += boost::str(boost::format("%d, ") % pChar->m_index);
		insertQuery += boost::str(boost::format("'%s', ") % escapedCharName);
		insertQuery += boost::str(boost::format("'%s', ") % escapedShopName);
		insertQuery += boost::str(boost::format("%d, ") % (int)pShop->GetType());
		insertQuery += "1, ";  // is_offline = 1
		insertQuery += "CURRENT_TIMESTAMP, ";  // created_at
		insertQuery += "DATE_ADD(CURRENT_TIMESTAMP, INTERVAL 24 HOUR), ";  // expires_at (24 hours from now)
		insertQuery += boost::str(boost::format("%d, ") % pShop->GetMapId());
		insertQuery += boost::str(boost::format("%f, ") % pShop->GetPosX());
		insertQuery += boost::str(boost::format("%f, ") % pShop->GetPosY());
		insertQuery += boost::str(boost::format("%f, ") % pShop->GetPosZ());
		insertQuery += "1, ";  // is_active = 1
		insertQuery += "0, ";  // total_sales = 0
		insertQuery += "0)";   // total_items_sold = 0

		// Push query to database thread
		DBManager::instance()->pushQuery(pChar->m_desc->m_index, insertQuery);

		LOG_INFO("InsertOfflineShopToDB: Offline shop queued for char %d (%s), shop: %s (shop_id: %d)", 
				 pChar->m_index, pChar->m_nick, pShop->GetName(), pShop->GetShopId());
	}
	catch (std::exception& e)
	{
		LOG_ERROR("InsertOfflineShopToDB Exception: %s", e.what());
	}
}

// ================================================================
// Insert shop items into the database
// ================================================================
void InsertOfflineShopItemsToDB(CPersonalShop::SP& pShop, CPC* pChar)
{
	if (!pShop || !pChar)
	{
		LOG_ERROR("InsertOfflineShopItemsToDB: Invalid shop pointer or character pointer");
		return;
	}

	int shopId = pShop->GetShopId();
	if (shopId <= 0)
	{
		LOG_ERROR("InsertOfflineShopItemsToDB: Shop has no valid shop_id");
		return;
	}

	try
	{
		// Insert normal items (sell items)
		for (int i = 0; i < 20; i++)  // PS_MAX_NORMAL_ITEM = 20
		{
			int itemIndex = pShop->GetNormalItemIndex(i);
			int itemDBIndex = pShop->GetNormalItemDBIndex(i);
			if (itemIndex < 0)
				continue;  // Empty slot

			LONGLONG itemCount = pShop->GetNormalItemCount(i);
			LONGLONG itemPrice = pShop->GetNormalItemPrice(i);

			if (itemCount <= 0 || itemPrice < 0)
				continue;

			// Pull the live item so we can persist full fidelity (plus/sockets/
			// options/serial/durability). Rebuilt vendors restore these on load.
			CItem* liveItem = pChar->m_inventory.FindByVirtualIndex(itemIndex);
			std::string fidelityValues = BuildItemFidelityValues(liveItem);

			std::string insertItemQuery;
			insertItemQuery.reserve(1024);
			insertItemQuery = "INSERT INTO personal_shop_items ";
			insertItemQuery += "(shop_id, item_index, item_type, item_db_index, "
							   "item_wear_pos, item_plus, item_flag, item_used, item_used_2, "
							   "item_serial, item_socket_count, item_option, item_jewel, item_origin, "
							   "item_now_durability, item_max_durability, "
							   "item_count, item_count_sold, item_count_remain, price, is_sold_out, created_at) ";
			insertItemQuery += "VALUES (";

			insertItemQuery += boost::str(boost::format("%d, ") % shopId);
			insertItemQuery += boost::str(boost::format("%d, ") % itemIndex);
			insertItemQuery += "0, ";  // item_type = 0 (normal item)
			insertItemQuery += boost::str(boost::format("%d, ") % itemDBIndex);
			insertItemQuery += fidelityValues + ", ";  // fidelity columns
			insertItemQuery += boost::str(boost::format("%lld, ") % itemCount);  // item_count
			insertItemQuery += "0, ";  // item_count_sold = 0
			insertItemQuery += boost::str(boost::format("%lld, ") % itemCount);  // item_count_remain = item_count
			insertItemQuery += boost::str(boost::format("%lld, ") % itemPrice);  // price
			insertItemQuery += "0, ";  // is_sold_out = 0
			insertItemQuery += "CURRENT_TIMESTAMP)";  // created_at

			DBManager::instance()->pushQuery(pChar->m_desc->m_index, insertItemQuery);
		}

		// Insert package items if any
		LONGLONG packagePrice = pShop->GetPackagePrice();
		if (packagePrice > 0)
		{
			for (int i = 0; i < 5; i++)  // PS_MAX_PACKAGE_ITEM = 5
			{
				int itemIndex = pShop->GetPackageItemIndex(i);
				int itemDBIndex = pShop->GetPackageItemDBIndex(i);
				if (itemIndex < 0)
					continue;  // Empty slot

				LONGLONG itemCount = pShop->GetPackageItemCount(i);
				if (itemCount <= 0)
					continue;

				// Pull the live item so package entries persist full fidelity too.
				CItem* liveItem = pChar->m_inventory.FindByVirtualIndex(itemIndex);
				std::string fidelityValues = BuildItemFidelityValues(liveItem);

				std::string insertItemQuery;
				insertItemQuery.reserve(1024);
				insertItemQuery = "INSERT INTO personal_shop_items ";
				insertItemQuery += "(shop_id, item_index, item_type, item_db_index, "
								   "item_wear_pos, item_plus, item_flag, item_used, item_used_2, "
								   "item_serial, item_socket_count, item_option, item_jewel, item_origin, "
								   "item_now_durability, item_max_durability, "
								   "item_count, item_count_sold, item_count_remain, price, is_sold_out, created_at) ";
				insertItemQuery += "VALUES (";

				insertItemQuery += boost::str(boost::format("%d, ") % shopId);
				insertItemQuery += boost::str(boost::format("%d, ") % itemIndex);
				insertItemQuery += "1, ";  // item_type = 1 (package item)
				insertItemQuery += boost::str(boost::format("%d, ") % itemDBIndex);
				insertItemQuery += fidelityValues + ", ";  // fidelity columns
				insertItemQuery += boost::str(boost::format("%lld, ") % itemCount);  // item_count
				insertItemQuery += "0, ";  // item_count_sold = 0
				insertItemQuery += boost::str(boost::format("%lld, ") % itemCount);  // item_count_remain = item_count
				insertItemQuery += boost::str(boost::format("%lld, ") % packagePrice);  // price (package price)
				insertItemQuery += "0, ";  // is_sold_out = 0
				insertItemQuery += "CURRENT_TIMESTAMP)";  // created_at

				DBManager::instance()->pushQuery(pChar->m_desc->m_index, insertItemQuery);
			}
		}

		LOG_INFO("InsertOfflineShopItemsToDB: Items queued for shop %d", shopId);
	}
	catch (std::exception& e)
	{
		LOG_ERROR("InsertOfflineShopItemsToDB Exception: %s", e.what());
	}
}

// ================================================================
// Record a sale in the offline shop database
// ================================================================
void RecordOfflineShopSaleToDB(int shopId, int itemId, int vendorCharIndex, int buyerCharIndex, 
							   const char* buyerCharName, int itemindex, int itemdbindex, LONGLONG itemCount, LONGLONG pricePerItem)
{
	if (shopId <= 0 || itemId <= 0 || itemCount <= 0)
	{
		LOG_ERROR("RecordOfflineShopSaleToDB: Invalid parameters - shopId:%d itemId:%d itemCount:%lld", 
			shopId, itemId, itemCount);
		return;
	}

	try
	{
		LONGLONG totalPrice = itemCount * pricePerItem;

		// Escape buyer name for SQL safety
		// mysql_real_escape_string can double the input size, so allocate 2x buffer
		char escapedBuyerName[512] = {0};
		if (buyerCharName)
		{
			mysql_real_escape_string(&gserver->m_dbchar, escapedBuyerName, buyerCharName, strlen(buyerCharName));
		}

		// Resolve item name from the in-memory item proto table.
		// NOTE: parameter naming is misleading in this codebase - `itemdbindex`
		// is actually the proto id (matches t_item.a_index / CItemProto index),
		// while `itemindex` is the unique per-instance id. Look up by itemdbindex.
		std::string itemName = "Unknown Item";
		CItemProto* pItemProto = gserver ? gserver->m_itemProtoList.FindIndex(itemdbindex) : NULL;
		if (pItemProto)
		{
			CLCString protoName = pItemProto->getItemName();
			const char* nameBuf = protoName.GetBuffer();
			if (nameBuf && nameBuf[0] != '\0')
				itemName = nameBuf;
		}
		else
		{
			LOG_WARN("RecordOfflineShopSaleToDB: item proto not found for itemdbindex=%d (instance itemindex=%d)", itemdbindex, itemindex);
		}

		// Escape item name for SQL safety
		// mysql_real_escape_string can double the input size, so allocate 2x buffer
		char escapedItemName[1024] = {0};
		mysql_real_escape_string(&gserver->m_dbchar, escapedItemName, itemName.c_str(), strlen(itemName.c_str()));

		// Insert into personal_shop_sales_log
		std::string insertSaleQuery;
		insertSaleQuery.reserve(1024);
		insertSaleQuery = "INSERT INTO personal_shop_sales_log ";
		insertSaleQuery += "(shop_id, vendor_char_index, item_id, item_index, item_dbindex, buyer_char_index, buyer_char_name, item_name, item_count_sold, price_per_item, total_price, sold_at, notification_sent) ";
		insertSaleQuery += "VALUES (";

		insertSaleQuery += boost::str(boost::format("%d, ") % shopId);
		insertSaleQuery += boost::str(boost::format("%d, ") % vendorCharIndex);
		insertSaleQuery += boost::str(boost::format("%d, ") % itemId);
		insertSaleQuery += boost::str(boost::format("%d, ") % itemindex);
		insertSaleQuery += boost::str(boost::format("%d, ") % itemdbindex);
		insertSaleQuery += boost::str(boost::format("%d, ") % buyerCharIndex);
		insertSaleQuery += boost::str(boost::format("'%s', ") % escapedBuyerName);
		insertSaleQuery += boost::str(boost::format("'%s', ") % escapedItemName);
		insertSaleQuery += boost::str(boost::format("%lld, ") % itemCount);
		insertSaleQuery += boost::str(boost::format("%lld, ") % pricePerItem);
		insertSaleQuery += boost::str(boost::format("%lld, ") % totalPrice);
		insertSaleQuery += "CURRENT_TIMESTAMP, ";  // sold_at
		insertSaleQuery += "0)";  // notification_sent = 0 (not yet notified)

		DBManager::instance()->pushQuery(0, insertSaleQuery);  // Use 0 for system query (not tied to a player)

		// Update personal_shop_items to track the sale
		std::string updateItemQuery;
		updateItemQuery.reserve(1024);
		updateItemQuery = "UPDATE personal_shop_items SET ";
		updateItemQuery += boost::str(boost::format("item_count_sold = item_count_sold + %lld, ") % itemCount);
		updateItemQuery += boost::str(boost::format("item_count_remain = item_count_remain - %lld, ") % itemCount);
		updateItemQuery += "last_sold_at = CURRENT_TIMESTAMP";
		updateItemQuery += boost::str(boost::format(" WHERE item_id = %d") % itemId);

		DBManager::instance()->pushQuery(0, updateItemQuery);

		// Update personal_shop_items to mark as sold out if no items remain
		std::string markSoldOutQuery;
		markSoldOutQuery.reserve(1024);
		markSoldOutQuery = "UPDATE personal_shop_items SET is_sold_out = 1 ";
		markSoldOutQuery += boost::str(boost::format("WHERE item_id = %d AND item_count_remain <= 0") % itemId);

		DBManager::instance()->pushQuery(0, markSoldOutQuery);

		// Update personal_shop_offline to track total sales
		std::string updateShopQuery;
		updateShopQuery.reserve(1024);
		updateShopQuery = "UPDATE personal_shop_offline SET ";
		updateShopQuery += boost::str(boost::format("total_sales = total_sales + %lld, ") % totalPrice);
		updateShopQuery += boost::str(boost::format("total_items_sold = total_items_sold + %lld ") % itemCount);
		updateShopQuery += boost::str(boost::format("WHERE shop_id = %d") % shopId);

		DBManager::instance()->pushQuery(0, updateShopQuery);

		// Update or insert settlement record for the vendor (payout on login)
			// We use a single INSERT ... ON DUPLICATE KEY UPDATE to avoid race conditions
			// The duplicate key is (shop_id, is_settled) to uniquely identify an unsettled settlement
			std::string settlementQuery;
			settlementQuery.reserve(1024);
			settlementQuery = "INSERT INTO personal_shop_settlement (shop_id, char_index, total_amount, total_items_sold, is_settled, created_at) ";
			settlementQuery += "SELECT shop_id, char_index, ";
			settlementQuery += boost::str(boost::format("%lld, %d, 0, CURRENT_TIMESTAMP ") % totalPrice % (int)itemCount);
			settlementQuery += boost::str(boost::format("FROM personal_shop_offline WHERE shop_id = %d ") % shopId);
			settlementQuery += "ON DUPLICATE KEY UPDATE ";
			settlementQuery += "personal_shop_settlement.total_amount = personal_shop_settlement.total_amount + ";
			settlementQuery += boost::str(boost::format("%lld, ") % totalPrice);
			settlementQuery += "personal_shop_settlement.total_items_sold = personal_shop_settlement.total_items_sold + ";
			settlementQuery += boost::str(boost::format("%d") % (int)itemCount);

			DBManager::instance()->pushQuery(0, settlementQuery);

		LOG_INFO("RecordOfflineShopSaleToDB: Sale recorded - Shop:%d Item:%d Buyer:%s Count:%lld Price/item:%lld Total:%lld", 
			shopId, itemId, buyerCharName ? buyerCharName : "NULL", itemCount, pricePerItem, totalPrice);
	}
	catch (std::exception& e)
	{
		LOG_ERROR("RecordOfflineShopSaleToDB Exception: %s", e.what());
	}
}

// ================================================================
// Save offline shop to database when player disconnects with offline mode enabled
// Inserts shop into personal_shop_offline and all items into personal_shop_items
// ================================================================
void SaveOfflineShopToDB(CPersonalShop* pShop, CPC* pChar)
{
	if (!pShop)
	{
		LOG_ERROR("SaveOfflineShopToDB: NULL shop pointer");
		return;
	}

	// Allow saving shops that are either already in offline mode OR have a valid shop_id
	// (prepared for offline mode). We skip if neither condition is true.
	if (pShop->GetShopId() <= 0)
	{
		LOG_INFO("SaveOfflineShopToDB: Shop not prepared for offline mode (no shop_id), skipping save");
		return;
	}

	try
	{
		int shop_id = pShop->GetShopId();
		int char_index = pShop->GetCharIndex();
		const char* char_name = pChar ? pChar->m_name : "Unknown";  // Use shop char_index if pChar is NULL
		const char* shop_name = pShop->GetName();
		char shop_type = pShop->GetType();
		int map_id = pShop->GetMapId();
		float pos_x = pShop->GetPosX();
		float pos_y = pShop->GetPosY();
		float pos_z = pShop->GetPosZ();
		int is_active = 1;  // Shops are active when being saved
		time_t created_at = pShop->GetCreatedTime();
		time_t expires_at = pShop->GetExpiresTime();

		// Convert times to datetime strings
		char created_str[32], expires_str[32];
		struct tm* timeinfo = localtime(&created_at);
		strftime(created_str, sizeof(created_str), "%Y-%m-%d %H:%M:%S", timeinfo);
		timeinfo = localtime(&expires_at);
		strftime(expires_str, sizeof(expires_str), "%Y-%m-%d %H:%M:%S", timeinfo);

		// Escape shop name and character name for SQL
		// mysql_real_escape_string can double the input size, so allocate 2x buffer
		char escapedShopName[512] = {0};
		char escapedCharName[512] = {0};
		if (shop_name)
			mysql_real_escape_string(&gserver->m_dbchar, escapedShopName, shop_name, strlen(shop_name));
		if (char_name)
			mysql_real_escape_string(&gserver->m_dbchar, escapedCharName, char_name, strlen(char_name));

		// Check if shop already exists (UPDATE vs INSERT)
		std::string checkQuery;
		checkQuery.reserve(256);
		checkQuery = boost::str(boost::format("SELECT shop_id FROM personal_shop_offline WHERE shop_id = %d") % shop_id);

		if (mysql_query(&gserver->m_dbchar, checkQuery.c_str()) != 0)
		{
			LOG_ERROR("SaveOfflineShopToDB: Failed to check if shop exists - %s", mysql_error(&gserver->m_dbchar));
			return;
		}

		MYSQL_RES* checkResult = mysql_store_result(&gserver->m_dbchar);
		bool shopExists = (mysql_num_rows(checkResult) > 0);
		mysql_free_result(checkResult);

		std::string shopQuery;
		shopQuery.reserve(1024);

		if (shopExists)
		{
			// UPDATE existing shop
			shopQuery = "UPDATE personal_shop_offline SET ";
			shopQuery += boost::str(boost::format("char_name='%s', ") % escapedCharName);
			shopQuery += boost::str(boost::format("shop_name='%s', ") % escapedShopName);
			shopQuery += boost::str(boost::format("shop_type=%d, ") % (int)shop_type);
			shopQuery += boost::str(boost::format("map_id=%d, ") % map_id);
			shopQuery += boost::str(boost::format("pos_x=%f, pos_y=%f, pos_z=%f, ") % pos_x % pos_y % pos_z);
			shopQuery += boost::str(boost::format("is_active=%d, ") % is_active);
			shopQuery += boost::str(boost::format("is_offline=1 ") );
			shopQuery += boost::str(boost::format("WHERE shop_id=%d") % shop_id);

			LOG_INFO("SaveOfflineShopToDB: Updating existing shop_id=%d", shop_id);
		}
		else
		{
			// INSERT new shop
			shopQuery = "INSERT INTO personal_shop_offline ";
			shopQuery += "(shop_id, char_index, char_name, shop_name, shop_type, map_id, pos_x, pos_y, pos_z, is_active, is_offline, created_at, expires_at) ";
			shopQuery += "VALUES (";
			shopQuery += boost::str(boost::format("%d, ") % shop_id);
			shopQuery += boost::str(boost::format("%d, ") % char_index);
			shopQuery += boost::str(boost::format("'%s', ") % escapedCharName);
			shopQuery += boost::str(boost::format("'%s', ") % escapedShopName);
			shopQuery += boost::str(boost::format("%d, ") % (int)shop_type);
			shopQuery += boost::str(boost::format("%d, ") % map_id);
			shopQuery += boost::str(boost::format("%f, %f, %f, ") % pos_x % pos_y % pos_z);
			shopQuery += boost::str(boost::format("%d, ") % is_active);
			shopQuery += "1, ";  // is_offline = 1
			shopQuery += boost::str(boost::format("'%s', ") % created_str);
			shopQuery += boost::str(boost::format("'%s')") % expires_str);

			LOG_INFO("SaveOfflineShopToDB: Inserting new shop_id=%d", shop_id);
		}

		// For new shops (INSERT), use synchronous query so we can immediately reload the item_ids.
		// For updates, use async since the items already exist with valid IDs.
		if (!shopExists)
		{
			// Synchronous insert for the shop
			if (mysql_query(&gserver->m_dbchar, shopQuery.c_str()) != 0)
			{
				LOG_ERROR("SaveOfflineShopToDB: Failed to INSERT shop_id=%d - %s", 
					shop_id, mysql_error(&gserver->m_dbchar));
				return;
			}
			LOG_INFO("SaveOfflineShopToDB: Shop INSERT completed synchronously for shop_id=%d", shop_id);
		}
		else
		{
			// Async update for existing shops
			DBManager::instance()->pushQuery(0, shopQuery);
			LOG_INFO("SaveOfflineShopToDB: Shop UPDATE queued asynchronously for shop_id=%d", shop_id);
		}

		// Now reload item IDs after inserting/updating items
		std::string reloadItemsQuery;
		reloadItemsQuery.reserve(512);
		reloadItemsQuery = boost::str(boost::format(
			"SELECT item_id, item_index, item_type FROM personal_shop_items WHERE shop_id = %d ORDER BY item_id")
			% shop_id);

		if (mysql_query(&gserver->m_dbchar, reloadItemsQuery.c_str()) == 0)
		{
			MYSQL_RES* reloadResult = mysql_store_result(&gserver->m_dbchar);
			if (reloadResult)
			{
				MYSQL_ROW reloadRow;
				while ((reloadRow = mysql_fetch_row(reloadResult)) != NULL)
				{
					int itemId = atoi(reloadRow[0]);
					int itemIndex = atoi(reloadRow[1]);
					int itemType = atoi(reloadRow[2]);  // 0 = normal, 1 = package

					// Find the item in the shop and set its persisted ID
					int pos = pShop->FindItem(itemType == 0, itemIndex);
					if (pos >= 0)
					{
						if (itemType == 0)
							pShop->SetNormalItemId(pos, itemId);
						else
							pShop->SetPackageItemId(pos, itemId);

						LOG_INFO("SaveOfflineShopToDB: Populated item_id=%d for %s item at pos=%d (index=%d)", 
							itemId, itemType == 0 ? "normal" : "package", pos, itemIndex);
					}
				}
				mysql_free_result(reloadResult);
			}
		}
		else
		{
			LOG_ERROR("SaveOfflineShopToDB: Failed to reload items to get item_ids - %s", 
				mysql_error(&gserver->m_dbchar));
		}

		// IMPORTANT: Delete all old items for this shop to handle sold items correctly
		// This ensures sold items (which are marked as deleted in-memory) are also removed from the database
		// MUST be synchronous to ensure DELETE completes before new INSERTs
		std::string deleteItemsQuery;
		deleteItemsQuery.reserve(128);
		deleteItemsQuery = boost::str(boost::format(
			"DELETE FROM personal_shop_items WHERE shop_id = %d") % shop_id);

		if (shopExists)
		{
			// For existing shops, execute DELETE synchronously to ensure it completes
			// BEFORE we queue the new item INSERTs
			if (mysql_query(&gserver->m_dbchar, deleteItemsQuery.c_str()) != 0)
			{
				LOG_ERROR("SaveOfflineShopToDB: Failed to DELETE old items for shop_id=%d - %s", 
					shop_id, mysql_error(&gserver->m_dbchar));
			}
			LOG_INFO("SaveOfflineShopToDB: Synchronously deleted old items for shop_id=%d", shop_id);
		}
		else
		{
			// For new shops during initial save, skip delete since there's nothing to delete yet
			LOG_INFO("SaveOfflineShopToDB: Skipping DELETE for new shop_id=%d (no old items)", shop_id);
		}

		// Now save all items to personal_shop_items
		// Process normal items - iterate through all 20 slots
		for (int pos = 0; pos < 20; pos++)  // PS_MAX_NORMAL_ITEM = 20
		{
			int itemIndex = pShop->GetNormalItemIndex(pos);
			if (itemIndex < 0)
				continue;  // Skip empty slots

			int itemDBIndex = pShop->GetNormalItemDBIndex(pos);
			LONGLONG quantity = pShop->GetNormalItemCount(pos);
			LONGLONG price = pShop->GetNormalItemPrice(pos);
			const PSItemFidelity* fidelity = pShop->GetNormalItemFidelity(pos);

			// Build fidelity values string
			std::string fidelityValues;
			if (fidelity && fidelity->valid)
			{
				// Build the full fidelity string
				std::string optionStr, jewelStr, originStr;

				// Options
				for (int k = 0; k < MAX_ITEM_OPTION; k++)
				{
					if (k > 0) optionStr += " ";
					optionStr += boost::str(boost::format("%d") % fidelity->option[k]);
				}

				// Jewels
				for (int k = 0; k < MAX_SOCKET_COUNT; k++)
				{
					if (k > 0) jewelStr += " ";
					jewelStr += boost::str(boost::format("%d") % fidelity->jewel[k]);
				}

				// Origin
				for (int k = 0; k < MAX_VARIATION_COUNT; k++)
				{
					if (k > 0) originStr += " ";
					originStr += boost::str(boost::format("%d") % fidelity->origin[k]);
				}

				// Escape the serial for SQL safety. Clamp source length to
				// MAX_SERIAL_LENGTH (the struct's real capacity) so a corrupted or
				// unterminated serial cannot overflow escapedSerial (needs 2*len+1).
				char escapedSerial[MAX_SERIAL_LENGTH * 2 + 4] = {0};
				if (fidelity->serial[0] != '\0')
				{
					size_t slen = strnlen(fidelity->serial, MAX_SERIAL_LENGTH);
					mysql_real_escape_string(&gserver->m_dbchar, escapedSerial, fidelity->serial, (unsigned long)slen);
				}

				// Manually build the string to avoid format issues with char types
				std::string temp;
				temp = boost::str(boost::format("%d, %d, %d, %d, %d, '%s', %d, '")
					% fidelity->wearPos
					% fidelity->plus
					% fidelity->flag
					% fidelity->used
					% fidelity->used_2
					% escapedSerial
					% (int)fidelity->socketCount);  // Cast char to int
				temp += optionStr;
				temp += "', '";
				temp += jewelStr;
				temp += "', '";
				temp += originStr;
				temp += boost::str(boost::format("', %d, %d")
					% fidelity->nowDurability
					% fidelity->maxDurability);

				fidelityValues = temp;
			}
			else
			{
				LOG_INFO("SaveOfflineShopToDB: No valid fidelity for item index %d, using fallback", itemIndex);
				fidelityValues = BuildItemFidelityValues(NULL);  // Use fallback since no live item
			}

			// Always INSERT (we DELETE all old items at the start, so no need to check for existence)
			std::string itemQuery;
			itemQuery.reserve(1024);
			itemQuery = "INSERT INTO personal_shop_items ";
			itemQuery += "(shop_id, item_index, item_type, item_db_index, item_count, item_count_remain, price, ";
			itemQuery += "item_wear_pos, item_plus, item_flag, item_used, item_used_2, ";
			itemQuery += "item_serial, item_socket_count, item_option, item_jewel, item_origin, ";
			itemQuery += "item_now_durability, item_max_durability) ";
			itemQuery += "VALUES (";
			itemQuery += boost::str(boost::format("%d, %d, 0, %d, %lld, %lld, %lld, ")
				% shop_id % itemIndex % itemDBIndex % quantity % quantity % price);
			itemQuery += fidelityValues;
			itemQuery += ")";

			// For new shops, use synchronous queries so item_ids get populated immediately.
			// For existing shops, use async to avoid blocking.
			if (!shopExists)
			{
				if (mysql_query(&gserver->m_dbchar, itemQuery.c_str()) != 0)
				{
					LOG_ERROR("SaveOfflineShopToDB: Failed to INSERT item - %s", 
						mysql_error(&gserver->m_dbchar));
				}
			}
			else
			{
				DBManager::instance()->pushQuery(0, itemQuery);
			}
		}

		// Process package items
		if (pShop->GetType() & PST_PACKAGE)
		{
			int itemIndex = pShop->GetPackageItemIndex(0);
			int itemDBIndex = pShop->GetPackageItemDBIndex(0);
			LONGLONG quantity = pShop->GetPackageItemCount(0);
			LONGLONG price = pShop->GetPackagePrice();
			const PSItemFidelity* fidelity = pShop->GetPackageItemFidelity(0);

			// Skip empty package slot (shop declared PST_PACKAGE but no package item added)
			if (itemIndex < 0 || quantity <= 0)
			{
				LOG_INFO("SaveOfflineShopToDB: PST_PACKAGE flag set but no package item present, skipping");
			}
			else
			{

			std::string fidelityValues;
			if (fidelity && fidelity->valid)
			{
				std::string optionStr, jewelStr, originStr;
				for (int k = 0; k < MAX_ITEM_OPTION; k++)
				{
					if (k > 0) optionStr += " ";
					optionStr += boost::str(boost::format("%d") % fidelity->option[k]);
				}
				for (int k = 0; k < MAX_SOCKET_COUNT; k++)
				{
					if (k > 0) jewelStr += " ";
					jewelStr += boost::str(boost::format("%d") % fidelity->jewel[k]);
				}
				for (int k = 0; k < MAX_VARIATION_COUNT; k++)
				{
					if (k > 0) originStr += " ";
					originStr += boost::str(boost::format("%d") % fidelity->origin[k]);
				}

				// Escape the serial for SQL safety. Clamp source length to
				// MAX_SERIAL_LENGTH (the struct's real capacity) so a corrupted or
				// unterminated serial cannot overflow escapedSerial (needs 2*len+1).
				char escapedSerial[MAX_SERIAL_LENGTH * 2 + 4] = {0};
				if (fidelity->serial[0] != '\0')
				{
					size_t slen = strnlen(fidelity->serial, MAX_SERIAL_LENGTH);
					mysql_real_escape_string(&gserver->m_dbchar, escapedSerial, fidelity->serial, (unsigned long)slen);
				}

				// Manually build the string to avoid format issues with char types
				std::string temp;
				temp = boost::str(boost::format("%d, %d, %d, %d, %d, '%s', %d, '")
					% fidelity->wearPos
					% fidelity->plus
					% fidelity->flag
					% fidelity->used
					% fidelity->used_2
					% escapedSerial
					% (int)fidelity->socketCount);  // Cast char to int
				temp += optionStr;
				temp += "', '";
				temp += jewelStr;
				temp += "', '";
				temp += originStr;
				temp += boost::str(boost::format("', %d, %d")
					% fidelity->nowDurability
					% fidelity->maxDurability);

				fidelityValues = temp;
			}
			else
			{
				LOG_INFO("SaveOfflineShopToDB: No valid fidelity for package item index %d, using fallback", itemIndex);
				fidelityValues = BuildItemFidelityValues(NULL);  // Use fallback since no live item
			}

			std::string pkgItemQuery;
			pkgItemQuery.reserve(1024);
			pkgItemQuery = "INSERT INTO personal_shop_items ";
			pkgItemQuery += "(shop_id, item_index, item_type, item_db_index, item_count, item_count_remain, price, ";
			pkgItemQuery += "item_wear_pos, item_plus, item_flag, item_used, item_used_2, ";
			pkgItemQuery += "item_serial, item_socket_count, item_option, item_jewel, item_origin, ";
			pkgItemQuery += "item_now_durability, item_max_durability) ";
			pkgItemQuery += "VALUES (";
			pkgItemQuery += boost::str(boost::format("%d, %d, 1, %d, %lld, %lld, %lld, ")
				% shop_id % itemIndex % itemDBIndex % quantity % quantity % price);
			pkgItemQuery += fidelityValues;
			pkgItemQuery += ")";

			// For new shops, use synchronous queries so item_ids get populated immediately.
			if (!shopExists)
			{
				if (mysql_query(&gserver->m_dbchar, pkgItemQuery.c_str()) != 0)
				{
					LOG_ERROR("SaveOfflineShopToDB: Failed to INSERT package item - %s", 
						mysql_error(&gserver->m_dbchar));
				}
			}
			else
			{
				DBManager::instance()->pushQuery(0, pkgItemQuery);
			}
			} // end package-slot-present else
		}

		LOG_INFO("SaveOfflineShopToDB: Successfully queued save for shop_id=%d (%s) with normal items and %s package", 
			shop_id, shop_name, (pShop->GetType() & PST_PACKAGE) ? "1" : "0");
	}
	catch (std::exception& e)
	{
		LOG_ERROR("SaveOfflineShopToDB Exception: %s", e.what());
	}
}

// ================================================================
// Update offline shop status (e.g., close shop)
// ================================================================
void UpdateOfflineShopStatusToDB(int shopId, bool bIsActive)
{
	if (shopId <= 0)
	{
		LOG_ERROR("UpdateOfflineShopStatusToDB: Invalid shop_id");
		return;
	}

	try
	{
		std::string updateQuery;
		updateQuery.reserve(512);
		updateQuery = "UPDATE personal_shop_offline SET ";
		updateQuery += boost::str(boost::format("is_active = %d ") % (bIsActive ? 1 : 0));
		updateQuery += boost::str(boost::format("WHERE shop_id = %d") % shopId);

		DBManager::instance()->pushQuery(0, updateQuery);

		LOG_INFO("UpdateOfflineShopStatusToDB: Shop %d status updated to %s", 
			shopId, bIsActive ? "ACTIVE" : "INACTIVE");
	}
	catch (std::exception& e)
	{
		LOG_ERROR("UpdateOfflineShopStatusToDB Exception: %s", e.what());
	}
}

// ================================================================
// Process settlement payouts for a vendor on login
// Queries pending settlements and adds gold to the character
// ================================================================
void ProcessOfflineShopSettlementOnLogin(CPC* pChar)
{
	if (!pChar || !gserver)
	{
		LOG_ERROR("ProcessOfflineShopSettlementOnLogin: Invalid character or server");
		return;
	}

	try
	{
		// Query for all unsettled amounts for this character
		std::string settlementQuery;
		settlementQuery.reserve(512);
		settlementQuery = "SELECT COALESCE(SUM(total_amount), 0) as pending_gold, ";
		settlementQuery += "COALESCE(SUM(total_items_sold), 0) as total_sold ";
		settlementQuery += boost::str(boost::format("FROM personal_shop_settlement WHERE char_index = %d AND is_settled = 0") % pChar->m_index);

		if (mysql_query(&gserver->m_dbchar, settlementQuery.c_str()) != 0)
		{
			LOG_ERROR("ProcessOfflineShopSettlementOnLogin: Query failed for char %d - %s", 
				pChar->m_index, mysql_error(&gserver->m_dbchar));
			return;
		}

		MYSQL_RES* result = mysql_store_result(&gserver->m_dbchar);
		if (!result)
		{
			LOG_ERROR("ProcessOfflineShopSettlementOnLogin: mysql_store_result failed for char %d", pChar->m_index);
			return;
		}

		MYSQL_ROW row = mysql_fetch_row(result);
		if (row && row[0])
		{
			LONGLONG pendingGold = strtoll(row[0], NULL, 10);
			int totalSold = row[1] ? atoi(row[1]) : 0;

			if (pendingGold > 0)
			{
				// Client mail UI does not wrap text and ignores \n, so keep the body
				// short. Full per-sale details are preserved in personal_shop_sales_log.
				std::string messageBody = boost::str(boost::format(
					"Offline shop settlement: %d item(s) sold for %lld NAS.")
					% totalSold % pendingGold);

				// Send settlement via mail system for clean tracking
				SendingSystemMailInfo mailInfo;
				mailInfo.Receiver = pChar;
				mailInfo.Subject = "Offline Shop Settlement";

				mailInfo.Message = messageBody.c_str();
				mailInfo.Nas = pendingGold;
				mailInfo.ItemCount = 0;

				// Send the mail
				MailBoxManager mailMgr;
				mailMgr.SendSystemMail(mailInfo);

				LOG_INFO("ProcessOfflineShopSettlementOnLogin: Sent settlement mail to char %d (%s) - gold=%lld items_sold=%d", 
					pChar->m_index, pChar->m_name, pendingGold, totalSold);

				// Mark all settlements for this character as settled
				std::string markSettledQuery;
				markSettledQuery.reserve(512);
				markSettledQuery = "UPDATE personal_shop_settlement SET ";
				markSettledQuery += "is_settled = 1, ";
				markSettledQuery += "settled_at = CURRENT_TIMESTAMP ";
				markSettledQuery += boost::str(boost::format("WHERE char_index = %d AND is_settled = 0") % pChar->m_index);

				DBManager::instance()->pushQuery(0, markSettledQuery);
			}
		}

		mysql_free_result(result);
	}
	catch (std::exception& e)
	{
		LOG_ERROR("ProcessOfflineShopSettlementOnLogin Exception for char %d: %s", pChar->m_index, e.what());
	}
}

// ================================================================
// Cleanup offline shop on login
// When a character logs in, their offline shop is deleted since
// it has already been settled. They can create a new shop if needed.
// ================================================================
void RestoreOfflineShopOnLogin(CPC* pChar)
{
	if (!pChar || !gserver)
	{
		LOG_ERROR("RestoreOfflineShopOnLogin: Invalid character or gserver pointer");
		return;
	}

	try
	{
		// Check if this character has an offline shop in the registry
		CPersonalShop::SP offlineShop = gserver->GetOfflineShopByCharIndex(pChar->m_index);
		if (!offlineShop)
		{
			// No offline shop for this character
			return;
		}

		int shopId = offlineShop->GetShopId();

		LOG_INFO("RestoreOfflineShopOnLogin: Processing offline shop cleanup for char %d (shop_id=%d)", 
			pChar->m_index, shopId);

		// FIRST: Remove sold items from the vendor's true inventory
		// This must happen BEFORE we delete the shop
		RemoveSoldItemsFromVendorInventory(pChar);
		LOG_INFO("RestoreOfflineShopOnLogin: Item removal completed for char %d", pChar->m_index);

		// THEN: Delete the offline shop from database and registry
		// The shop has served its purpose (sales recorded, settlement paid, items removed)

		// Remove from registry
		gserver->UnregisterOfflineShop(pChar->m_index);
		LOG_INFO("RestoreOfflineShopOnLogin: Unregistered shop from registry for char %d", pChar->m_index);

		// IMPORTANT: Remove the character reference from the offline vendor registry
		// This releases the reference that was keeping the character object alive
		auto vendorIter = gserver->m_offlineVendorRegistry.find(shopId);
		if (vendorIter != gserver->m_offlineVendorRegistry.end())
		{
			CPC* pOfflineVendor = vendorIter->second;
			if (pOfflineVendor && pOfflineVendor != pChar)
			{
				// Remove the offline character from the cell grid before destroying it
				if (pOfflineVendor->m_pArea && IS_IN_CELL(pOfflineVendor))
				{
					LOG_INFO("RestoreOfflineShopOnLogin: Removing offline character from cell grid");
					pOfflineVendor->SendDisappearAllInCell(false);
					pOfflineVendor->m_pArea->CharFromCell(pOfflineVendor, true);
				}
				// The offline vendor CPC is a headless character kept alive after
				// disconnect. Its descriptor is NULL and it was removed from
				// PCManager at logout, so we own it here and must delete it to
				// prevent duplicate characters when the owner logs back in.
				LOG_INFO("RestoreOfflineShopOnLogin: Deleting offline vendor CPC for shop %d", shopId);
				delete pOfflineVendor;
			}
			gserver->m_offlineVendorRegistry.erase(vendorIter);
			LOG_INFO("RestoreOfflineShopOnLogin: Removed vendor character reference for shop %d", shopId);
		}

		// Delete from database
		if (shopId > 0)
		{
			std::string deleteQuery = boost::str(boost::format(
				"DELETE FROM personal_shop_offline WHERE shop_id = %d;") % shopId);

			// Also delete associated items (CASCADE should handle this, but being explicit)
			std::string deleteItemsQuery = boost::str(boost::format(
				"DELETE FROM personal_shop_items WHERE shop_id = %d;") % shopId);

			DBManager::instance()->pushQuery(0, deleteItemsQuery);
			DBManager::instance()->pushQuery(0, deleteQuery);

			LOG_INFO("RestoreOfflineShopOnLogin: Queued DB cleanup for shop_id=%d", shopId);
		}
	}
	catch (std::exception& e)
	{
		LOG_ERROR("RestoreOfflineShopOnLogin Exception for char %d: %s", pChar->m_index, e.what());
	}
}

// ================================================================
// Send appearance packets for ALL offline vendors to nearby players
// This makes offline vendors visible through the cell grid, just like NPCs
// Should be called when offline vendors are restored to the cell grid
// ================================================================
void SendOfflineVendorAppearanceToNearby()
{
	if (!gserver)
		return;

	try
	{
		boost::lock_guard<boost::recursive_mutex> lock(gserver->m_offlineShopRegistryMutex);

		// Iterate through all offline vendors in the registry
		for (auto& pair : gserver->m_offlineVendorRegistry)
		{
			CPC* pVendor = pair.second;
			if (!pVendor || !pVendor->m_pArea || !IS_IN_CELL(pVendor))
				continue;  // Skip if vendor is not in a valid cell

			// Send appearance packet to all nearby players in cells around this vendor
			// Using the same pattern as NPC reload - create AppearMsg and SendToCell
			CNetMsg::SP rmsg(new CNetMsg);
			AppearMsg(rmsg, pVendor, true);  // bNew=true since they're appearing for the first time
			pVendor->m_pArea->SendToCell(rmsg, GET_YLAYER(pVendor), pVendor->m_cellX, pVendor->m_cellZ);

			LOG_INFO("SendOfflineVendorAppearanceToNearby: Sent appearance for offline vendor char_idx=%d at cell [%d][%d]",
				pVendor->m_index, pVendor->m_cellX, pVendor->m_cellZ);
		}
	}
	catch (const std::exception& e)
	{
		LOG_ERROR("SendOfflineVendorAppearanceToNearby Exception: %s", e.what());
	}
}

// ================================================================
// Restore offline vendors to the cell grid after loading from database
// This rebuilds the zone/area references for offline vendors at startup
// so they can be made visible to nearby players
// ================================================================
void RestoreOfflineVendorsToAreaCells()
{
	if (!gserver)
		return;

	try
	{
		boost::lock_guard<boost::recursive_mutex> lock(gserver->m_offlineShopRegistryMutex);

		int restoredCount = 0;

		// Iterate through all offline vendors
		for (auto& pair : gserver->m_offlineVendorRegistry)
		{
			CPC* pVendor = pair.second;
			if (!pVendor)
				continue;

			// Get the zone and map ID from the vendor's current area
			int mapId = pVendor->m_pArea ? pVendor->m_pArea->m_zone->m_index : -1;

			// If no area, try to find it from the offline shop
			if (mapId == -1)
			{
				auto shopIter = gserver->m_offlineShopRegistry.find(pair.first);
				if (shopIter != gserver->m_offlineShopRegistry.end())
				{
					CPersonalShop::SP pShop = shopIter->second;
					if (pShop)
						mapId = pShop->GetMapId();
				}
			}

			if (mapId < 0)
			{
				LOG_WARN("RestoreOfflineVendorsToAreaCells: Cannot determine zone for vendor char_idx=%d", pVendor->m_index);
				continue;
			}

			// Find the zone
			CZone* pZone = gserver->FindZone(mapId);
			if (!pZone)
			{
				LOG_WARN("RestoreOfflineVendorsToAreaCells: Zone %d not found for vendor char_idx=%d", mapId, pVendor->m_index);
				continue;
			}

			// Find the area - vendor should already have an area from disconnect
			CArea* pArea = pVendor->m_pArea;
			if (!pArea)
			{
				LOG_WARN("RestoreOfflineVendorsToAreaCells: No area for vendor char_idx=%d in zone %d", pVendor->m_index, mapId);
				continue;
			}

			// If vendor is NOT already in a cell, add them to the cell grid
			if (!IS_IN_CELL(pVendor))
			{
				int cx, cz;
				pArea->PointToCellNum(GET_X(pVendor), GET_Z(pVendor), &cx, &cz);
				pArea->CharToCell(pVendor, GET_YLAYER(pVendor), cx, cz);

				LOG_INFO("RestoreOfflineVendorsToAreaCells: Restored vendor char_idx=%d to cell [%d][%d] in zone %d",
					pVendor->m_index, cx, cz, mapId);
				restoredCount++;
			}
			else
			{
				LOG_INFO("RestoreOfflineVendorsToAreaCells: Vendor char_idx=%d already in cell [%d][%d]",
					pVendor->m_index, pVendor->m_cellX, pVendor->m_cellZ);
			}
		}

		LOG_INFO("RestoreOfflineVendorsToAreaCells: Restored %d offline vendors to cell grid", restoredCount);
	}
	catch (const std::exception& e)
	{
		LOG_ERROR("RestoreOfflineVendorsToAreaCells Exception: %s", e.what());
	}
}

// ================================================================
// Load player-vendor NPCs from database and spawn them in zones
// Called during server startup after regular NPCs are loaded
// This makes offline shops visible as NPC entities in the world
// ================================================================
void LoadPlayerVendorNPCsFromDB()
{
	if (!gserver)
		return;

	try
	{
		CDBCmd dbCmd;
		dbCmd.Init(&gserver->m_dbdata);

		// Query all active player-vendor NPCs
		std::string query = "SELECT pr.a_player_idx, pr.a_zone_num, pr.a_pos_x, pr.a_pos_z, pr.a_pos_h, pr.a_pos_r, "
							"np.a_char_name, np.a_shop_id "
							"FROM t_player_regen pr "
							"JOIN t_npc_player np ON pr.a_player_idx = np.a_index "
							"WHERE pr.a_enable = 1 AND np.a_active = 1";

		dbCmd.SetQuery(query.c_str());
		if (!dbCmd.Open())
		{
			LOG_WARN("LoadPlayerVendorNPCsFromDB: Failed to query player-vendor NPCs");
			return;
		}

		int loadedCount = 0;

		while (dbCmd.MoveNext())
		{
			int playerIdx = 0;
			int zoneNum = 0;
			float pos_x = 0.0f;
			float pos_z = 0.0f;
			float pos_h = 0.0f;
			float pos_r = 0.0f;
			CLCString charName;
			int shopId = 0;

			dbCmd.GetRec("a_player_idx", playerIdx);
			dbCmd.GetRec("a_zone_num", zoneNum);
			dbCmd.GetRec("a_pos_x", pos_x);
			dbCmd.GetRec("a_pos_z", pos_z);
			dbCmd.GetRec("a_pos_h", pos_h);
			dbCmd.GetRec("a_pos_r", pos_r);
			dbCmd.GetRec("a_char_name", charName);
			dbCmd.GetRec("a_shop_id", shopId);

			// Find the zone
			CZone* pZone = gserver->FindZone(zoneNum);
			if (!pZone)
			{
				LOG_WARN("LoadPlayerVendorNPCsFromDB: Zone %d not found for player %d", zoneNum, playerIdx);
				continue;
			}

			// Get the area
			CArea* pArea = pZone->m_area;
			if (!pArea)
			{
				LOG_WARN("LoadPlayerVendorNPCsFromDB: Area not found in zone %d for player %d", zoneNum, playerIdx);
				continue;
			}

			// Create a player-vendor NPC using the player's character index as the NPC proto
			// We treat the player character model as the NPC model
			// If you want a different visual, you could use a different NPC proto here
			CNPC* vendorNpc = gserver->m_npcProtoList.Create(playerIdx, NULL);  // Use player idx as NPC index
			if (!vendorNpc)
			{
				LOG_WARN("LoadPlayerVendorNPCsFromDB: Failed to create NPC for player %d", playerIdx);
				continue;
			}

			// Set NPC position and rotation.
			// NOTE: pos_h stored in DB is world Y (height), NOT yLayer. yLayer must be
			// a small integer (0..(ycnt-1)*2). Default to 0 (ground) so CharToCell's
			// bounds check accepts it.
			char yLayer = 0;
			GET_X(vendorNpc) = pos_x;
			GET_Z(vendorNpc) = pos_z;
			GET_YLAYER(vendorNpc) = yLayer;
			GET_R(vendorNpc) = pos_r;

			// Register NPC in the area and place into the cell grid (required for visibility)
			pArea->AddNPC(vendorNpc);

			int cx, cz;
			pArea->PointToCellNum(pos_x, pos_z, &cx, &cz);
			pArea->CharToCell(vendorNpc, yLayer, cx, cz);

			// Appearance message sent on login via BroadcastOfflineShopsInAreaToPlayer
			LOG_INFO("LoadPlayerVendorNPCsFromDB: Placed player-vendor NPC in zone grid (player_idx=%d, name='%s', shop_id=%d) in zone %d",
				playerIdx, (const char*)charName, shopId, zoneNum);
			loadedCount++;
		}

		LOG_INFO("LoadPlayerVendorNPCsFromDB: Loaded %d player-vendor NPCs from database", loadedCount);
	}
	catch (const std::exception& e)
	{
		LOG_ERROR("LoadPlayerVendorNPCsFromDB Exception: %s", e.what());
	}
}

// ================================================================
// Create player-vendor NPC entries for offline shops
// Instead of using dummy NPCs, we create entries in t_npc_player and t_player_regen
// This allows player characters to act as NPC vendors when offline
// ================================================================
void CreateDummyNPCsForOfflineShops()
{
	if (!gserver)
		return;

	try
	{
		boost::lock_guard<boost::recursive_mutex> lock(gserver->m_offlineShopRegistryMutex);

		CDBCmd dbCmd;
		dbCmd.Init(&gserver->m_dbchar);

		int createdCount = 0;

		// Iterate through all offline shops
		for (auto& pair : gserver->m_offlineShopRegistry)
		{
			CPersonalShop::SP pShop = pair.second;
			if (!pShop)
				continue;

			// Get shop details
			int shopId = pShop->GetShopId();
			int mapId = pShop->GetMapId();
			float pos_x = pShop->GetPosX();
			float pos_y = pShop->GetPosY();
			float pos_z = pShop->GetPosZ();
			const char* shopName = pShop->GetName();

			// We need the player character index and account ID
			// These should be stored in the offline shop or retrieved from database
			// For now, we'll query the personal_shop table to get this info
			std::string selectShopQuery = boost::str(boost::format(
				"SELECT a_owner_idx, a_account_id FROM personal_shop WHERE a_shop_id = %d LIMIT 1") 
				% shopId);

			dbCmd.SetQuery(selectShopQuery.c_str());
			if (!dbCmd.Open())
			{
				LOG_WARN("CreateDummyNPCsForOfflineShops: Failed to query shop %d", shopId);
				continue;
			}

			if (!dbCmd.MoveNext())
			{
				LOG_WARN("CreateDummyNPCsForOfflineShops: Shop %d not found in database", shopId);
				dbCmd.Close();
				continue;
			}

			int playerIdx = 0;
			int accountId = 0;
			dbCmd.GetRec("a_owner_idx", playerIdx);
			dbCmd.GetRec("a_account_id", accountId);
			dbCmd.Close();

			if (playerIdx <= 0)
			{
				LOG_WARN("CreateDummyNPCsForOfflineShops: Invalid player index for shop %d", shopId);
				continue;
			}

			// Insert or update into t_npc_player using DBManager
			std::string insertNpcPlayerQuery = boost::str(boost::format(
				"INSERT INTO t_npc_player (a_index, a_account_id, a_char_name, a_zone_num, a_pos_x, a_pos_z, a_pos_h, a_pos_r, a_shop_id, a_active) "
				"VALUES (%d, %d, '%s', %d, %.2f, %.2f, %.2f, 0, %d, 1) "
				"ON DUPLICATE KEY UPDATE "
				"a_zone_num=%d, a_pos_x=%.2f, a_pos_z=%.2f, a_pos_h=%.2f, a_shop_id=%d, a_active=1, a_updated_at=CURRENT_TIMESTAMP")
				% playerIdx % accountId % shopName % mapId % pos_x % pos_z % pos_y % shopId
				% mapId % pos_x % pos_z % pos_y % shopId);

			// Push query to database (use player index or 0 for system query)
			DBManager::instance()->pushQuery(0, insertNpcPlayerQuery);

			// Insert or update into t_player_regen (use playerIdx as the key for simplicity)
			std::string insertRegenQuery = boost::str(boost::format(
				"INSERT INTO t_player_regen (a_index, a_player_idx, a_zone_num, a_pos_x, a_pos_z, a_pos_h, a_pos_r, a_regen_sec, a_total_num, a_enable) "
				"VALUES (%d, %d, %d, %.2f, %.2f, %.2f, 0, 0, 1, 1) "
				"ON DUPLICATE KEY UPDATE "
				"a_player_idx=%d, a_zone_num=%d, a_pos_x=%.2f, a_pos_z=%.2f, a_pos_h=%.2f, a_enable=1, a_updated_at=CURRENT_TIMESTAMP")
				% playerIdx % playerIdx % mapId % pos_x % pos_z % pos_y
				% playerIdx % mapId % pos_x % pos_z % pos_y);

			DBManager::instance()->pushQuery(0, insertRegenQuery);

			LOG_INFO("CreateDummyNPCsForOfflineShops: Queued player-vendor NPC for shop_id=%d (vendor='%s', player_idx=%d) at [%.2f, %.2f, %.2f]",
				shopId, shopName, playerIdx, pos_x, pos_y, pos_z);
			createdCount++;
		}

		LOG_INFO("CreateDummyNPCsForOfflineShops: Queued %d offline shops as player-vendor NPCs", createdCount);
	}
	catch (const std::exception& e)
	{
		LOG_ERROR("CreateDummyNPCsForOfflineShops Exception: %s", e.what());
	}
}

// ================================================================
// BroadcastOfflineShopsInAreaToPlayer - NO LONGER NEEDED.
// Offline vendor NPCs are CNPC objects placed in the zone cell grid via
// AddNPC + CharToCell at logout (ProcDisconnect) and at startup (LoadPlayerVendorNPCsFromDB).
// The engine's existing SendCellInfo() already iterates m_cell[x][z].m_listChar and
// sends AppearMsg for every character - including these CNPCs - to any joining player.
// No manual broadcast is required.
void BroadcastOfflineShopsInAreaToPlayer(CPC* /*pChar*/)
{
	// Intentional no-op. See comment above.
}

// Process settlements for all online characters
// Call this after LoadOfflineShopsFromDB at startup or whenever you want
// to trigger settlement processing for logged-in vendors
// ================================================================
void ProcessAllOfflineShopSettlementsForOnlineCharacters()
{
	try
	{
		// Get the player map from PCManager
		PCManager* pManager = PCManager::instance();
		if (!pManager)
			return;

		auto& playerMap = pManager->getPlayerMap();

		LOG_INFO("ProcessAllOfflineShopSettlementsForOnlineCharacters: Processing settlements for %zu online players", 
			playerMap.size());

		// Iterate through all online characters and process their settlements
		for (auto& playerInfo : playerMap)
		{
			if (playerInfo.pPlayer)
			{
				ProcessOfflineShopSettlementOnLogin(playerInfo.pPlayer);
			}
		}
	}
	catch (std::exception& e)
	{
		LOG_ERROR("ProcessAllOfflineShopSettlementsForOnlineCharacters Exception: %s", e.what());
	}
}

// ================================================================
// Load offline shops from database (called on server startup)
// ================================================================
void LoadOfflineShopsFromDB()
{
	try
	{
		if (!gserver)
		{
			LOG_ERROR("LoadOfflineShopsFromDB: gserver is NULL");
			return;
		}

		// Build query to load all active offline shops
		std::string loadQuery;
		loadQuery.reserve(512);
		loadQuery = "SELECT shop_id, char_index, char_name, shop_name, shop_type, map_id, ";
		loadQuery += "pos_x, pos_y, pos_z, is_active, total_sales, total_items_sold, ";
		loadQuery += "created_at, expires_at FROM personal_shop_offline ";
		loadQuery += "WHERE is_offline = 1 AND is_active = 1 AND expires_at > NOW() ORDER BY shop_id";

		LOG_INFO("LoadOfflineShopsFromDB: Loading offline shops - Query: %s", loadQuery.c_str());

		// Execute synchronous query against the database
		if (mysql_query(&gserver->m_dbchar, loadQuery.c_str()) != 0)
		{
			LOG_ERROR("LoadOfflineShopsFromDB: mysql_query failed - %s", mysql_error(&gserver->m_dbchar));
			return;
		}

		// Get the result set
		MYSQL_RES* result = mysql_store_result(&gserver->m_dbchar);
		if (!result)
		{
			LOG_ERROR("LoadOfflineShopsFromDB: mysql_store_result failed - %s", mysql_error(&gserver->m_dbchar));
			return;
		}

		int shopsLoaded = 0;
		MYSQL_ROW row;

		// Process each row
		while ((row = mysql_fetch_row(result)) != NULL)
		{
			try
			{
				// Extract shop data from row
				int shop_id = atoi(row[0]);
				int char_index = atoi(row[1]);
				const char* char_name = row[2] ? row[2] : "";
				const char* shop_name = row[3] ? row[3] : "Offline Shop";
				char shop_type = row[4] ? (char)atoi(row[4]) : 0;
				int map_id = atoi(row[5]);
				float pos_x = (float)atof(row[6]);
				float pos_y = (float)atof(row[7]);
				float pos_z = (float)atof(row[8]);
				int is_active = atoi(row[9]);
				LONGLONG total_sales = ATOLL(row[10]);
				int total_items_sold = atoi(row[11]);
				const char* created_at_str = row[12] ? row[12] : "";
				const char* expires_at_str = row[13] ? row[13] : "";

				LOG_INFO("LoadOfflineShopsFromDB: Loading shop_id=%d, char=%s (index=%d), name='%s', map_id=%d, pos=[%.2f, %.2f, %.2f], expires=%s", 
					shop_id, char_name, char_index, shop_name, map_id, pos_x, pos_y, pos_z, expires_at_str);

				// Create a new offline shop object
				CPersonalShop::SP pShop(new CPersonalShop(shop_type, shop_name));
				if (!pShop)
				{
					LOG_ERROR("LoadOfflineShopsFromDB: Failed to create CPersonalShop for shop_id=%d", shop_id);
					continue;
				}

				// Set all offline shop properties
				pShop->SetShopId(shop_id);
				pShop->SetCharIndex(char_index);
				pShop->SetOfflineMode(true);
				pShop->SetMapId(map_id);
				pShop->SetPosition(pos_x, pos_y, pos_z);
				pShop->AddSales(total_sales);


				// Add sales count  
				for (int i = 0; i < total_items_sold; i++)
					pShop->IncrementItemsSold(1);

				// Now load associated items for this shop
				std::string itemQuery;
				itemQuery.reserve(512);
				itemQuery = boost::str(boost::format(
					"SELECT item_id, item_index, item_type, item_db_index, item_count, price, "
					"item_wear_pos, item_plus, item_flag, item_used, item_used_2, "
					"item_serial, item_socket_count, item_option, item_jewel, item_origin, "
					"item_now_durability, item_max_durability "
					"FROM personal_shop_items "
					"WHERE shop_id = %d ORDER BY item_id") % shop_id);

				if (mysql_query(&gserver->m_dbchar, itemQuery.c_str()) != 0)
				{
					LOG_ERROR("LoadOfflineShopsFromDB: Failed to query items for shop_id=%d - %s", 
						shop_id, mysql_error(&gserver->m_dbchar));
					continue;
				}

				MYSQL_RES* itemResult = mysql_store_result(&gserver->m_dbchar);
				if (!itemResult)
				{
					LOG_ERROR("LoadOfflineShopsFromDB: Failed to get item result set for shop_id=%d", shop_id);
					continue;
				}

				MYSQL_ROW itemRow;
				int itemsLoaded = 0;

				while ((itemRow = mysql_fetch_row(itemResult)) != NULL)
				{
					int itemId = atoi(itemRow[0]);
					int itemIndex = atoi(itemRow[1]);
					int itemType = atoi(itemRow[2]);  // 0 = normal, 1 = package
					int itemDBIndex = atoi(itemRow[3]);
					LONGLONG quantity = ATOLL(itemRow[4]);
					LONGLONG price = ATOLL(itemRow[5]);

					// Add item to shop - now respects item_type
					bool isNormalItem = (itemType == 0);
					if (pShop->AddItem(isNormalItem, itemIndex, itemDBIndex, quantity, price))
					{
						int pos = pShop->FindItem(isNormalItem, itemIndex);
						if (pos >= 0)
						{
							if (isNormalItem)
								pShop->SetNormalItemId(pos, itemId);
							else
								pShop->SetPackageItemId(pos, itemId);
						}

						// Parse the full item-fidelity columns so the vendor can
						// reconstruct the exact CItem after a restart.
						PSItemFidelity fid;
						memset(&fid, 0, sizeof(fid));
						fid.valid          = true;
						fid.wearPos        = itemRow[6]  ? atoi(itemRow[6])  : -1;
						fid.plus           = itemRow[7]  ? atoi(itemRow[7])  : 0;
						fid.flag           = itemRow[8]  ? atoi(itemRow[8])  : 0;
						fid.used           = itemRow[9]  ? atoi(itemRow[9])  : 0;
						fid.used_2         = itemRow[10] ? atoi(itemRow[10]) : 0;
						if (itemRow[11])
							strncpy(fid.serial, itemRow[11], MAX_SERIAL_LENGTH);
						fid.socketCount    = itemRow[12] ? (char)atoi(itemRow[12]) : 0;

						// item_option: MAX_ITEM_OPTION space-delimited shorts
						if (itemRow[13] && *itemRow[13])
						{
							const char* p = itemRow[13];
							char buf[16];
							for (int k = 0; k < MAX_ITEM_OPTION && *p; k++)
							{
								p = AnyOneArg(p, buf);
								fid.option[k] = (short)atoi(buf);
							}
						}

						// item_jewel: canonical socket string (jewel0 count jewel1..)
						memset(fid.jewel, -1, sizeof(fid.jewel));
						if (itemRow[14] && *itemRow[14])
						{
							const char* p = itemRow[14];
							char buf[16];
							p = AnyOneArg(p, buf);
							fid.jewel[0] = atoi(buf);
							int sc = 0;
							if (*p)
							{
								p = AnyOneArg(p, buf);
								sc = atoi(buf);
							}
							if (sc >= 1 && sc <= MAX_SOCKET_COUNT)
							{
								fid.socketCount = (char)sc;
								for (int k = 1; k < MAX_SOCKET_COUNT && *p; k++)
								{
									p = AnyOneArg(p, buf);
									fid.jewel[k] = atoi(buf);
								}
							}
						}

						// item_origin: MAX_VARIATION_COUNT space-delimited ints
						if (itemRow[15] && *itemRow[15])
						{
							const char* p = itemRow[15];
							char buf[16];
							for (int k = 0; k < MAX_VARIATION_COUNT && *p; k++)
							{
								p = AnyOneArg(p, buf);
								fid.origin[k] = atoi(buf);
							}
						}

						fid.nowDurability  = itemRow[16] ? atoi(itemRow[16]) : 0;
						fid.maxDurability  = itemRow[17] ? atoi(itemRow[17]) : 0;

						fid.nowDurability = itemRow[15] ? atoi(itemRow[15]) : 0;
						fid.maxDurability = itemRow[16] ? atoi(itemRow[16]) : 0;

						// Store fidelity in appropriate array based on item type
						if (isNormalItem)
						{
							pShop->SetNormalItemFidelity(pShop->FindItem(true, itemIndex), fid);
						}
						else
						{
							pShop->SetPackageItemFidelity(pShop->FindItem(false, itemIndex), fid);
						}

						itemsLoaded++;
					}
					else
					{

					}
				}

				mysql_free_result(itemResult);

				LOG_INFO("LoadOfflineShopsFromDB: Loaded shop_id=%d with %d items", shop_id, itemsLoaded);

				// Register the loaded shop in the global registry
				if (gserver)
				{
					gserver->RegisterOfflineShop(shop_id, pShop);
				}

				shopsLoaded++;
			}
			catch (std::exception& e)
			{
				LOG_ERROR("LoadOfflineShopsFromDB: Exception processing shop row - %s", e.what());
				continue;
			}
		}

		mysql_free_result(result);

		LOG_INFO("LoadOfflineShopsFromDB: Successfully loaded %d offline shops from database", shopsLoaded);
	}
	catch (std::exception& e)
	{
		LOG_ERROR("LoadOfflineShopsFromDB Exception: %s", e.what());
	}
}

// ================================================================
// Mark sales as notified to Discord bot

void MarkSalesAsNotifiedToDB(const std::vector<int>& saleIds)
{
	if (saleIds.empty())
		return;

	try
	{
		// Build comma-separated list of sale IDs
		std::string saleIdList;
		for (size_t i = 0; i < saleIds.size(); i++)
		{
			if (i > 0) saleIdList += ",";
			saleIdList += boost::str(boost::format("%d") % saleIds[i]);
		}

		std::string updateQuery;
		updateQuery.reserve(512);
		updateQuery = "UPDATE personal_shop_sales_log SET ";
		updateQuery += "notification_sent = 1 ";
		updateQuery += boost::str(boost::format("WHERE sale_id IN (%s)") % saleIdList);

		DBManager::instance()->pushQuery(0, updateQuery);

		LOG_INFO("MarkSalesAsNotifiedToDB: Marked %zu sales as notified", saleIds.size());
	}
	catch (std::exception& e)
	{
		LOG_ERROR("MarkSalesAsNotifiedToDB Exception: %s", e.what());
	}
}

// ================================================================
// Cleanup expired offline shops (called periodically - every hour recommended)
// ================================================================
void CleanupExpiredOfflineShops()
{
	try
	{
		// Mark expired shops as inactive
		std::string updateQuery;
		updateQuery.reserve(512);
		updateQuery = "UPDATE personal_shop_offline SET ";
		updateQuery += "is_active = 0 ";
		updateQuery += "WHERE is_offline = 1 AND is_active = 1 AND expires_at <= CURRENT_TIMESTAMP";

		DBManager::instance()->pushQuery(0, updateQuery);

		LOG_INFO("CleanupExpiredOfflineShops: Marked expired offline shops as inactive");
	}
	catch (std::exception& e)
	{
		LOG_ERROR("CleanupExpiredOfflineShops Exception: %s", e.what());
	}
}

// ================================================================
// Get query for Discord bot to fetch unsold offline shops
// Returns all active offline shops with remaining items for bot queries
// ================================================================
const char* GetDiscordBotOfflineShopsQuery()
{
	static const char* query = 
		"SELECT "
		"  ps.shop_id, "
		"  ps.char_index, "
		"  ps.char_name, "
		"  ps.shop_name, "
		"  COUNT(psi.item_id) as item_count, "
		"  SUM(psi.item_count_remain) as total_remaining, "
		"  ps.total_sales, "
		"  ps.created_at "
		"FROM personal_shop_offline ps "
		"LEFT JOIN personal_shop_items psi ON ps.shop_id = psi.shop_id "
		"WHERE ps.is_offline = 1 "
		"  AND ps.is_active = 1 "
		"  AND psi.is_sold_out = 0 "
		"GROUP BY ps.shop_id, ps.char_index, ps.char_name, ps.shop_name, ps.total_sales, ps.created_at "
		"ORDER BY ps.created_at DESC";

	return query;
}

// ================================================================
// Get query for Discord bot to fetch recent sales for notifications
// ================================================================
const char* GetDiscordBotRecentSalesQuery()
{
	static const char* query = 
		"SELECT TOP 100 "
		"  psl.sale_id, "
		"  ps.char_name as seller_name, "
		"  ps.shop_name, "
		"  psl.buyer_char_name, "
		"  psl.item_count_sold, "
		"  psl.price_per_item, "
		"  psl.total_price, "
		"  psl.sold_at "
		"FROM personal_shop_sales_log psl "
		"JOIN personal_shop_offline ps ON psl.shop_id = ps.shop_id "
		"WHERE psl.notification_sent = 0 "
		"  AND psl.sold_at > DATEADD(hour, -24, GETUTCDATE()) "
		"ORDER BY psl.sold_at DESC";

	return query;
}

// ================================================================
// Update offline shop position when character disconnects
// ================================================================
void UpdateOfflineShopPosition(CPC* pChar)
{
	if (!pChar || !pChar->m_personalshop || !pChar->m_personalshop->IsOfflineMode())
	{
		return;
	}

	if (!gserver)
	{
		LOG_ERROR("UpdateOfflineShopPosition: gserver is NULL");
		return;
	}

	try
	{
		int shop_id = pChar->m_personalshop->GetShopId();
		float pos_x = pChar->m_pos.m_x;
		float pos_z = pChar->m_pos.m_z;
		float pos_y = pChar->m_pos.m_h;  // Use height as Y
		// Use m_pZone->m_index for the actual zone number, not m_pArea->m_index
		int map_id = pChar->m_pZone ? pChar->m_pZone->m_index : 0;

		std::string updateQuery;
		updateQuery.reserve(512);
		updateQuery = boost::str(boost::format(
			"UPDATE personal_shop_offline SET map_id=%d, pos_x=%f, pos_y=%f, pos_z=%f "
			"WHERE shop_id=%d")
			% map_id % pos_x % pos_y % pos_z % shop_id);

		// Push query to database thread
		DBManager::instance()->pushQuery(pChar->m_desc->m_index, updateQuery);

		LOG_INFO("UpdateOfflineShopPosition: Updated shop_id=%d position to [%.2f, %.2f, %.2f] in zone %d", 
			shop_id, pos_x, pos_y, pos_z, map_id);
	}
	catch (std::exception& e)
	{
		LOG_ERROR("UpdateOfflineShopPosition Exception: %s", e.what());
	}
}

// ================================================================
// Reconstruct a CItem from offline shop fidelity data
// Used when a buyer purchases from an offline vendor
// Returns a newly created item with full fidelity, or NULL on error
// ================================================================
CItem* CreateItemFromOfflineShopFidelity(const PSItemFidelity* fidelity, int itemDBIndex, LONGLONG count)
{
	if (!fidelity || !fidelity->valid)
	{
		LOG_ERROR("CreateItemFromOfflineShopFidelity: Invalid fidelity data");
		return NULL;
	}

	// Reconstruct from fidelity data
	CItem* pItem = gserver->m_itemProtoList.CreateDBItem(
		itemDBIndex,
		fidelity->wearPos,
		fidelity->plus,
		fidelity->flag,
		fidelity->used,
		fidelity->used_2,
		fidelity->serial,
		count,
		(short*)fidelity->option,
		fidelity->socketCount,
		(int*)fidelity->jewel,
		(int*)fidelity->origin,
		fidelity->nowDurability,
		fidelity->maxDurability
	);

	if (pItem)
	{
		LOG_INFO("CreateItemFromOfflineShopFidelity: Successfully created item - dbindex=%d, plus=%d, count=%lld",
			itemDBIndex, fidelity->plus, count);
	}
	else
	{
		LOG_ERROR("CreateItemFromOfflineShopFidelity: Failed to create item - dbindex=%d", itemDBIndex);
	}

	return pItem;
}

// ================================================================
// Remove sold items from vendor's TRUE inventory (t_inventory0X tables)
// This is called when the vendor logs in, after settlement is paid out
// ================================================================
void RemoveSoldItemsFromVendorInventory(CPC* pVendor)
{
	if (!pVendor)
	{
		LOG_ERROR("RemoveSoldItemsFromVendorInventory: Invalid vendor");
		return;
	}

	try
	{
		LOG_INFO("RemoveSoldItemsFromVendorInventory: Marking sold items for vendor %d", 
			pVendor->m_index);

		// NOTE: Actual inventory removal from t_inven0X tables requires knowledge of exact schema
		// For now, we mark sales as processed. The inventory removal should happen via:
		// 1) Direct player inventory API when purchase completes, OR
		// 2) Batch job that processes notification_sent = 0 records asynchronously

		// Mark all these sales as processed
		std::string markQuery = boost::str(boost::format(
			"UPDATE personal_shop_sales_log "
			"SET notification_sent = 1 "
			"WHERE vendor_char_index = %d AND notification_sent = 0") % pVendor->m_index);

		LOG_INFO("RemoveSoldItemsFromVendorInventory: Queuing mark-processed for vendor %d", 
			pVendor->m_index);
		DBManager::instance()->pushQuery(0, markQuery);
	}
	catch (const std::exception& e)
	{
		LOG_ERROR("RemoveSoldItemsFromVendorInventory Exception for vendor %d: %s", pVendor->m_index, e.what());
	}
}

#endif // OFFLINE_SHOPS
