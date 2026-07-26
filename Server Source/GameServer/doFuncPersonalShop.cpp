#include <boost/format.hpp>
#include <vector>
#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "Server.h"
#include "CmdMsg.h"
#include "doFunc.h"
#include "DBManager.h"
#include "Artifact_Manager.h"
#include "doFuncPersonalShopDB.h"
#include <time.h>

#ifdef OFFLINE_SHOPS
// ================================================================
// Remove sold items from the kept-alive offline vendor CPC's inventory
// and persist the change to t_inven0X. The vendor CPC lives in
// m_offlineVendorRegistry[shopId] after logout with its full inventory
// intact, so we can mutate it exactly like a live vendor's inventory.
// ================================================================
static void RemoveSoldItemsFromOfflineVendor(CPersonalShop* offlineShop,
											   const std::vector<PurchasedItem>& sold)
{
	if (!offlineShop || sold.empty() || !gserver)
		return;

	int shopId = offlineShop->GetShopId();
	CPC* vendor = NULL;
	{
		boost::recursive_mutex::scoped_lock lock(gserver->m_offlineVendorRegistryMutex);
		auto it = gserver->m_offlineVendorRegistry.find(shopId);
		if (it != gserver->m_offlineVendorRegistry.end())
			vendor = it->second;
	}

	if (!vendor)
	{
		LOG_WARN("RemoveSoldItemsFromOfflineVendor: kept-alive vendor CPC not found for shop_id=%d (char=%d). Inventory rows will be reconciled on owner re-login.",
			shopId, offlineShop->GetCharIndex());
		return;
	}

	bool anyRemoved = false;
	for (const PurchasedItem& pi : sold)
	{
		CItem* vitem = vendor->m_inventory.FindByVirtualIndex(pi.itemindex);
		if (!vitem)
		{
			LOG_WARN("RemoveSoldItemsFromOfflineVendor: itemindex=%d not found in vendor inventory (char=%d)",
				pi.itemindex, vendor->m_index);
			continue;
		}

		if (vitem->Count() > pi.count)
		{
			vendor->m_inventory.decreaseItemCount(vitem, pi.count);
		}
		else
		{
			int tab = vitem->tab();
			int invenIndex = vitem->getInvenIndex();
			vendor->m_inventory.eraseNotFreeByInvenIndex(tab, invenIndex);
		}
		anyRemoved = true;

		LOG_INFO("RemoveSoldItemsFromOfflineVendor: Removed itemindex=%d count=%lld from vendor char=%d inventory",
			pi.itemindex, pi.count, vendor->m_index);
	}

	if (!anyRemoved)
		return;

	// Persist the vendor's inventory to t_inven%02d using the same DELETE+INSERT
	// batch pattern that DBManager::_SaveCharInvenQuery uses. This is the only
	// safe way to update the denormalized 5-items-per-row inventory tables.
	int table_no = vendor->m_index % 10;
	std::vector<std::string> queries;
	std::string deleteQuery = boost::str(boost::format(
		"DELETE FROM t_inven%02d WHERE a_char_idx=%d") % table_no % vendor->m_index);
	queries.push_back(deleteQuery);
	vendor->m_inventory.getSaveString(queries);

	for (std::string& q : queries)
		DBManager::instance()->pushQuery(0, q);

	LOG_INFO("RemoveSoldItemsFromOfflineVendor: Persisted vendor char=%d inventory to t_inven%02d (%d queries)",
		vendor->m_index, table_no, (int)queries.size());
}
#endif // OFFLINE_SHOPS

// ================================================================
// Refund unsold cash items when personal shop closes
// ================================================================
static void RefundCashFromClosedShop(CPersonalShop::SP ps, int userCode)
{
	if (!ps || userCode <= 0)
		return;

	// Cash listings are now handled by dedicated Cash Exchange NPC system
	// This function is deprecated and kept for backward compatibility only
}

// ================================================================
// Process cash transaction when buyer purchases cash from seller
// DEPRECATED: Cash transactions are now handled by dedicated Cash Exchange NPC system
// ================================================================
static void ProcessCashTransaction(CPC* buyerCh, int sellerUserCode, LONGLONG cashAmount)
{
	// This function is deprecated and kept for backward compatibility only
}

void do_PersonalShop(CPC* ch, CNetMsg::SP& msg)
{
	msg->MoveFirst();
	unsigned char subtype = (unsigned char)-1;
	RefMsg(msg) >> subtype;
	switch (subtype)
	{
	case MSG_PERSONALSHOP_SELL_START:
		do_PersonalShopSellStart(ch, msg);
		break;

	case MSG_PERSONALSHOP_SELL_LIST:
		do_PersonalShopSellList(ch, msg);
		break;

	case MSG_PERSONALSHOP_CHANGE:
		do_PersonalShopChange(ch, msg);
		break;

	case MSG_PERSONALSHOP_BUY:
		do_PersonalShopBuy(ch, msg);
		break;
	}
}

void do_PersonalShopSellStart(CPC* ch, CNetMsg::SP& msg)
{
	if (ch->m_pArea == NULL)
		return ;

	if ( !(ch->m_pArea->GetAttr(GET_YLAYER(ch), GET_X(ch), GET_Z(ch)) & MATT_PEACE ) )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_AREA);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	if (ch->GetMapAttr() & MATT_FREEPKZONE)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_AREA);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	if (ch->m_pArea->m_zone->isRVRZone() == true)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_AREA);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	
	if ( ch->m_pZone->IsOXQuizRoom()
			|| ch->m_pZone->IsWarGroundZone()
	   )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_AREA);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

#ifdef LC_USA
	if ( ch->m_level < 10 )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
#endif // LC_USA

#if defined (LC_GAMIGO)
	if ( ch->m_level < 15 )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
#endif

	if (ch->m_exchange)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_EXCHANGE);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
	if (ch->IsSetPlayerState(PLAYER_STATE_WARP))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_EXCHANGE);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
	if (ch->m_currentSkill)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_SKILL);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
	if (ch->m_personalshop)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ALREADY);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	int charindex = -1;
	char shoptype = -1;
	CLCString shopname(PS_MAX_SHOPNAME + 1);
	BYTE bOfflineMode = 0;							// NEW: Read offline mode flag
	RefMsg(msg) >> charindex
				>> shoptype
				>> shopname
				>> bOfflineMode;					// NEW: Read offline mode from client packet
	shopname.Trim();

	if(findPercentChar(shopname.GetBuffer()) != NULL)
	{
		
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	if (charindex < 1 || shoptype < 0 || (shoptype & PST_SELL) == 0 || shopname.Length() > PS_MAX_SHOPNAME)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	char normalCount = -1;
	RefMsg(msg) >> normalCount;
	if (normalCount < 0 || normalCount > PS_MAX_NORMAL_ITEM)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	if (normalCount == 0 && (shoptype & PST_PACKAGE) == 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	CPersonalShop::SP ps(new CPersonalShop(shoptype, shopname));

	int i;
	for (i = 0; i < normalCount; i++)
	{
		unsigned short tab =0;
		unsigned short invenIndex = 0;
		int itemindex = -1;
		int itemdbindex = -1;
		LONGLONG count = -1;
		LONGLONG price = -1;
		RefMsg(msg) >> tab
					>> invenIndex
					>> itemindex
					>> itemdbindex
					>> count
					>> price;
		if (itemdbindex == NAS_ITEM_DB_INDEX)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_MONEY);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}

		// Handle special cash exchange items
		// NOTE: Cash listings are now handled by dedicated Cash Exchange NPC system
		// Reject any attempts to list cash items in personal shop
		if (itemdbindex == 999999)  // PS_CASH_ITEM_ID sentinel - deprecated
		{
			// Reject cash items in personal shop - use Cash Exchange NPC instead
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}

		// 060406 : bs : ���ε� ������ ��ȯ �Ұ�
		CItem* item = ch->m_inventory.getItem(tab, invenIndex);
		if (item == NULL)
		{
			LOG_ERROR("HACKING? : not found item. char_index[%d] tab[%d] invenIndex[%d]",
					  ch->m_index, tab, invenIndex);
			ch->m_desc->Close("not found item");
			return;
		}

#ifdef ENABLE_SUBJOB
		if( item && item->CanUseTrader( TRADE_PERSONAL_SHOP, ch->IsSubJob(JOB_SUB_TRADER) ) == false )
		{
			
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}
#endif //ENABLE_SUBJOB

		if(item->m_itemProto->getItemIndex() == ARTIFACT_LEVEL1_ITEM_INDEX ||
			item->m_itemProto->getItemIndex() == ARTIFACT_LEVEL2_ITEM_INDEX ||
			item->m_itemProto->getItemIndex() == ARTIFACT_LEVEL3_ITEM_INDEX)
		{
			
			LOG_ERROR("HACKING? : Artifact Item. char_index[%d], item_index[%d]",
				ch->m_index, item->getDBIndex());
			ch->m_desc->Close("not found item");
			return;
		}

		if(item->IsBelong() == true)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_BELONG_ITEM);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}

		if ( item == NULL || item->getVIndex() != itemindex || item->getDBIndex() != itemdbindex	|| item->Count() < count || price < 1 || !item->CanExchange() )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
		
		if (item->IsPet())
		{
			CPet* pet = ch->GetPet(item->getPlus());
			if (!pet || pet->GetSkillList()->count() != 0 )
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
		}
		if( item->IsAPet() )
		{
			CAPet* apet = ch->GetAPet(item->getPlus());
			if( apet && apet->IsPetEquip() )
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
		}
		if (ps->FindItem(true, itemindex) != -1)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_DUPLICATION);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
		if (!ps->AddItem(true, itemindex, itemdbindex, count, price))
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}

		// Capture and store item fidelity for offline persistence
		int itemSlot = ps->FindItem(true, itemindex);
		if (itemSlot != -1)
		{
			PSItemFidelity fid = BuildItemFidelityFromLive(item);
			ps->SetNormalItemFidelity(itemSlot, fid);
		}
	}

	if (shoptype & PST_PACKAGE)
	{
		LONGLONG packprice = -1;
		char packcount = -1;
		RefMsg(msg) >> packprice
					>> packcount;
		if (packprice < 1 || packcount < 1 || packcount > PS_MAX_PACKAGE_ITEM)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
		int i;
		for (i = 0; i < packcount; i++)
		{
			unsigned short tab = 0;
			unsigned short invenIndex = 0;
			int itemindex = -1;
			int itemdbindex = -1;
			LONGLONG count = -1;
			RefMsg(msg) >> tab
						>> invenIndex
						>> itemindex
						>> itemdbindex
						>> count;
			if (itemdbindex == NAS_ITEM_DB_INDEX)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_MONEY);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}

			if (ch->m_inventory.isValidNormalInventory(tab, invenIndex) == false)
			{
				LOG_ERROR("HACKING? : invalid packet. char_index[%d] tab[%d] invenIndex[%d]",
						  ch->m_index, tab, invenIndex);
				ch->m_desc->Close("invalid packet");
				return;
			}

			if (ch->m_inventory.isUsable(tab) == false)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}

			// 060406 : bs : ���ε� ������ ��ȯ �Ұ�
			CItem* item = ch->m_inventory.getItem(tab, invenIndex);
			if (item == NULL)
			{
				LOG_ERROR("HACKING? : not found item. char_index[%d] tab[%d] invenIndex[%d]",
						  ch->m_index, tab, invenIndex);
				ch->m_desc->Close("not found item");
				return;
			}

			if(item->IsBelong() == true)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg(rmsg, MSG_SYS_BELONG_ITEM);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}

			if (item->getVIndex() != itemindex || item->getDBIndex() != itemdbindex
					|| item->Count() < count || !item->CanExchange())
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}

			if (ps->FindItem(true, itemindex) != -1)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_DUPLICATION);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
			if (ps->FindItem(false, itemindex) != -1)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_DUPLICATION);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
			
			if (item->IsPet())
			{
				CPet* pet = ch->GetPet(item->getPlus());
				if (!pet || pet->GetSkillList()->count() != 0 )
				{
					CNetMsg::SP rmsg(new CNetMsg);
					PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
					SEND_Q(rmsg, ch->m_desc);
					return ;
				}
			}
			if( item->IsAPet() )
			{
				CAPet* apet = ch->GetAPet(item->getPlus());
				if( apet && apet->IsPetEquip() )
				{
					CNetMsg::SP rmsg(new CNetMsg);
					PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
					SEND_Q(rmsg, ch->m_desc);
					return ;
				}
			}

			if (!ps->AddItem(false, itemindex, itemdbindex, count, packprice))
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}

			// Capture and store item fidelity for offline persistence
			int itemSlot = ps->FindItem(false, itemindex);
			if (itemSlot != -1)
			{
				PSItemFidelity fid = BuildItemFidelityFromLive(item);
				ps->SetPackageItemFidelity(itemSlot, fid);
			}
			}
	}

	ch->m_personalshop = ps;

	// NOTE: Cash items are no longer processed in personal shop
	// Cash exchange is handled by dedicated NPC system

	// NEW: Store offline mode flag but DON'T activate it yet
	// The flag will be checked at disconnect - only THEN do we truly go offline
	if (bOfflineMode)
	{
		ps->SetCharIndex(ch->m_index);

		// SET THE POSITION FROM CHARACTER'S CURRENT LOCATION
		// Use m_pZone->m_index for the actual zone number, not m_pArea->m_index
		int mapId = ch->m_pZone ? ch->m_pZone->m_index : 0;
		LOG_INFO("Setting offline shop map_id: ch->m_pZone=%p, m_index=%d", ch->m_pZone, mapId);

		ps->SetMapId(mapId);
		ps->SetPosition(ch->m_pos.m_x, ch->m_pos.m_h, ch->m_pos.m_z);

		time_t now = time(NULL);
		ps->SetCreatedTime(now);
		ps->SetExpiresTime(now + (PS_OFFLINE_PERSIST_HOURS * 3600));

		// Generate unique server-side shop_id: (char_index << 32) | timestamp_low_32bits
		// This ensures uniqueness across servers and avoids async database lookup
		long long uniqueShopId = ((long long)ch->m_index << 32) | (now & 0xFFFFFFFF);
		ps->SetShopId((int)uniqueShopId);
		ps->SetCharIndex(ch->m_index);  // Store the owner's character index for registry lookup

		// DO NOT activate offline mode yet - it will be activated at disconnect
		// This prevents the character from being removed from the world while shopping
		// The shop metadata is ready for persistence if/when the client closes

		LOG_INFO("Offline shop capability enabled for %s (charindex: %d, shop: %s, shopid: %d) at position [%.2f, %.2f, %.2f] in zone %d", 
			ch->m_nick, ch->m_index, ps->GetName(), ps->GetShopId(), 
			ch->m_pos.m_x, ch->m_pos.m_h, ch->m_pos.m_z, mapId);

		// Insert the shop to the DB immediately so item_ids get auto-generated and can be used
		// for sale tracking. The shop will be marked as inactive initially and activated on disconnect.
		SaveOfflineShopToDB(ps.get(), ch);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopSellStartMsg(rmsg, ch);
		ch->m_pArea->SendToCell(rmsg, ch, true);
	}

	GAMELOG << init("PERSONAL SHOP START", ch)
			<< "TYPE" << delim << ps->GetType() << delim << "ITEMS";
	int pos = -1;
	int count = (int)ps->GetNormalCount();
	for (i = 0; i < count; i++)
	{
		pos = ps->GetNextNormalItem(pos);
		int itemindex = ps->GetNormalItemIndex(pos);
		CItem* item = ch->m_inventory.FindByVirtualIndex(itemindex);
		GAMELOG << delim << itemlog(item)
				<< delim << ps->GetNormalItemCount(pos)
				<< delim << ps->GetNormalItemPrice(pos);
	}
	if (ps->GetType() & PST_PACKAGE)
	{
		GAMELOG << delim << "PACKAGE"
				<< delim << ps->GetPackagePrice();

		pos = -1;
		int packageCount = ps->GetPackageCount();
		for (i = 0; i < packageCount; i++)
		{
			pos = ps->GetNextPackageItem(pos);
			int itemindex = ps->GetPackageItemIndex(pos);
			CItem* item = ch->m_inventory.FindByVirtualIndex(itemindex);
			GAMELOG << delim << itemlog(item)
					<< delim << ps->GetPackageItemCount(pos);
		}
	}
	GAMELOG << delim << ps->GetName() << end;
}

void do_PersonalShopSellList(CPC* ch, CNetMsg::SP& msg)
{
	if (ch->m_pArea == NULL)
		return ;
	if (ch->m_personalshop)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ALREADY);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	int charindex = -1;
	RefMsg(msg) >> charindex;
	CPC* tch = TO_PC(ch->m_pArea->FindCharInCell(ch, charindex, MSG_CHAR_PC, false));

	// A kept-alive offline vendor CPC has no live descriptor; route it through
	// the offline path so the live-vendor branch never touches tch->m_desc.
	if (tch != NULL && (tch->m_desc == NULL ||
		(tch->m_personalshop && tch->m_personalshop->IsOfflineMode())))
	{
		tch = NULL;
	}

	CPersonalShop::SP offlineShop;
	if (tch == NULL)
	{
		// Vendor not visible as a live CPC in the cell. Fall back to the offline
		// shop registry (same-session or restored) keyed by owner char index.
		LOG_INFO("do_PersonalShopSellList: Vendor not found in cell, checking offline registry for charindex=%d", charindex);
		offlineShop = gserver->GetOfflineShopByCharIndex(charindex);
		if (!offlineShop)
		{
			LOG_ERROR("do_PersonalShopSellList: Offline shop NOT found in registry for charindex=%d", charindex);
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_NOTFOUND);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}

		if ((offlineShop->GetType() & PST_SELL) == 0)
		{
			LOG_ERROR("do_PersonalShopSellList: Offline shop found but is not a SELL shop! charindex=%d, type=%d", 
				charindex, offlineShop->GetType());
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_NOTSELL);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}

		LOG_INFO("do_PersonalShopSellList: Using offline shop from registry for charindex=%d, shop_id=%d", 
			charindex, offlineShop->GetShopId());
	}
	else
	{
		// Live vendor found - verify they have a shop
		if (tch->m_personalshop == NULL || (tch->m_personalshop->GetType() & PST_SELL) == 0)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_NOTSELL);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
	}

	// Handle offline shop browse via registry - return early to avoid null dereference
	if (offlineShop)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopSellListMsgOffline(rmsg, offlineShop, charindex);

		if (rmsg->m_size >= MAX_PACKET_SIZE)
		{
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_CANNOT_USE);
		}
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// Live shop only - tch is guaranteed to be valid here
	if (tch->m_personalshop->GetNormalCount())
	{
		int i;
		int pos = -1;
		int personalshopCount = tch->m_personalshop->GetNormalCount();
		for (i = 0; i < personalshopCount; i++)
		{
			pos = tch->m_personalshop->GetNextNormalItem(pos);
			if (pos != -1)
			{
				int itemindex = tch->m_personalshop->GetNormalItemIndex(pos);
				CItem* pitem = tch->m_inventory.FindByVirtualIndex(itemindex);
				if (pitem)
				{
					if (pitem->IsPet())
					{
						CPet* pet = tch->GetPet(pitem->getPlus());
						if (pet)
						{
							CNetMsg::SP rmsg(new CNetMsg);
							ExPetSellInfoMsg(rmsg, pet);
							SEND_Q(rmsg, ch->m_desc);
						}
					}
				}
			}
		}
	}
	
	if (tch->m_personalshop->GetType() & PST_PACKAGE)
	{
		int i;
		int pos = -1;
		int personalshopCount = tch->m_personalshop->GetPackageCount();
		for (i = 0; i < personalshopCount; i++)
		{
			pos = tch->m_personalshop->GetNextPackageItem(pos);
			if (pos != -1)
			{
				int itemindex = tch->m_personalshop->GetPackageItemIndex(pos);
				CItem* pitem = ch->m_inventory.FindByVirtualIndex(itemindex);
				if (pitem)
				{
					if (pitem->IsPet())
					{
						CPet* pet = tch->GetPet(pitem->getPlus());
						if (pet)
						{
							CNetMsg::SP rmsg(new CNetMsg);
							ExPetSellInfoMsg(rmsg, pet);
							SEND_Q(rmsg, ch->m_desc);
						}
					}
				}
			}
		}
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopSellListMsg(rmsg, tch);

		if (rmsg->m_size >= MAX_PACKET_SIZE)
		{
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_CANNOT_USE);
		}
		SEND_Q(rmsg, ch->m_desc);
	}
}

void do_PersonalShopChange(CPC* ch, CNetMsg::SP& msg)
{
	if (ch->m_pArea == NULL)
		return ;
	if (ch->m_exchange)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_EXCHANGE);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
	if (ch->IsSetPlayerState(PLAYER_STATE_WARP))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_EXCHANGE);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
	if (ch->m_currentSkill)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_SKILL);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	int charindex = -1;
	char shoptype = -1;
	RefMsg(msg) >> charindex
				>> shoptype;

	if (shoptype != PST_NOSHOP)
		return ;
	if (ch->m_personalshop == NULL)
		return ;
	if (ch->m_index != charindex)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	int shopId = ch->m_personalshop->GetShopId();
	bool isOfflineMode = ch->m_personalshop->IsOfflineMode();

	ch->m_personalshop.reset();

	// If offline shop, unregister from registry and mark inactive in DB
	if (isOfflineMode && shopId > 0)
	{
		gserver->UnregisterOfflineShop(shopId);
		UpdateOfflineShopStatusToDB(shopId, false);
		LOG_INFO("Offline shop closed: shopId=%d", shopId);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopChangeMsg(rmsg, ch);
		ch->m_pArea->SendToCell(rmsg, ch, true);
	}
}

void do_PersonalShopBuy(CPC* ch, CNetMsg::SP& msg)
{
	if (ch->m_pArea == NULL)
		return ;

	if (ch->m_personalshop)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ALREADY);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	
	LONGLONG needmoney = 0;

	
	int charindex = -1;
	char packbuy = -1;
	RefMsg(msg) >> charindex
				>> packbuy;

	LOG_INFO("do_PersonalShopBuy: Buyer (char %d) at cell [%d][%d] looking for vendor charindex=%d", 
		ch->m_index, ch->m_cellX, ch->m_cellZ, charindex);

	// For offline shops, we need to include "dead" characters (offline vendors are marked as dead)
	CPC* tch = TO_PC(ch->m_pArea->FindCharInCell(ch, charindex, MSG_CHAR_PC, true));

	// If the found CPC is a kept-alive offline vendor (no live descriptor), treat it
	// as offline so we don't dereference tch->m_desc in the live-vendor path.
	if (tch != NULL && (tch->m_desc == NULL ||
		(tch->m_personalshop && tch->m_personalshop->IsOfflineMode())))
	{
		tch = NULL;
	}

	// If vendor not found in cell, check if it's an offline shop in the registry
	CPersonalShop::SP offlineShop;
	if (tch == NULL)
	{
		LOG_INFO("do_PersonalShopBuy: Vendor not found in cell, checking offline registry for charindex=%d", charindex);
		offlineShop = gserver->GetOfflineShopByCharIndex(charindex);
		if (!offlineShop)
		{
			LOG_ERROR("do_PersonalShopBuy: Offline shop NOT found in registry for charindex=%d. Registry may be empty or shop not registered.", charindex);
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_NOTFOUND);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}

		if ((offlineShop->GetType() & PST_SELL) == 0)
		{
			LOG_ERROR("do_PersonalShopBuy: Offline shop found but is not a SELL shop! charindex=%d, type=%d", 
				charindex, offlineShop->GetType());
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_NOTSELL);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}

		LOG_INFO("do_PersonalShopBuy: Using offline shop from registry for charindex=%d, shop_id=%d", charindex, offlineShop->GetShopId());
	}
	else
	{
		// Live vendor found in cell
		if (tch->m_personalshop == NULL || (tch->m_personalshop->GetType() & PST_SELL) == 0)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_NOTSELL);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
	}

	// Check if the character must wait before purchasing another item
	if (ch->m_personalShopBuyPulse > gserver->m_pulse)
	{
		// Character needs to wait, send a message or take other actions as necessary
		CNetMsg::SP rmsg(new CNetMsg);
		// You can send a message to inform the player about the delay here
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_DELAY);
		SEND_Q(rmsg, ch->m_desc);
		GAMELOG << init("PERSONAL SHOP BUY Delay", ch) << end;
		return;
	}

	// Get shop pointer - either from live vendor (tch) or offline registry
	CPersonalShop* ps = (tch != NULL) ? tch->m_personalshop.get() : offlineShop.get();
	bool isOfflineShop = (tch == NULL);  // Flag to track if this is an offline vendor
	char shoptype = ps->GetType();

	int nCountOfPet = 0;
	if (ch->m_petList)
	{
		CPet* pPetOfBuyer = ch->m_petList;
		while (pPetOfBuyer)
		{
			nCountOfPet++;
			pPetOfBuyer = pPetOfBuyer->m_nextPet;
		}
	}

	
	CPersonalShop list(shoptype, "");

	
	if (packbuy)
	{
		if ((shoptype & PST_PACKAGE) == 0)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_NOTPACKAGE);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}

		needmoney = ps->GetPackagePrice();
		if (needmoney < 0 || needmoney > ch->m_inventory.getMoney())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_MONEY);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}

		
		std::vector<possible_search_t> search_vec;
		int i, j = -1;
		int packageCount = ps->GetPackageCount();
		for (i = 0; i < packageCount; i++)
		{
			j = ps->GetNextPackageItem(j);
			if (j == -1)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}

			// For offline shops, we can't verify items in live inventory
			// The items are persisted in the shop data already
			CItem* item = NULL;
			if (!isOfflineShop)
			{
				item = tch->m_inventory.FindByVirtualIndex(ps->GetPackageItemIndex(j));
				if(item == NULL)
					return ;
			}
			else
			{
				// For offline shops, create item from fidelity to check properties
				const PSItemFidelity* fid = ps->GetPackageItemFidelity(j);
				LOG_INFO("do_PersonalShopBuy: Checking fidelity for offline package item - pos=%d, fid=%p, valid=%d",
					j, fid, fid ? fid->valid : -1);
				if (fid && fid->valid)
				{
					item = CreateItemFromOfflineShopFidelity(fid, ps->GetPackageItemDBIndex(j), ps->GetPackageItemCount(j));
					LOG_INFO("do_PersonalShopBuy: Created package item from fidelity - dbindex=%d, plus=%d",
						ps->GetPackageItemDBIndex(j), item ? item->getPlus() : -1);
				}
				else
				{
					LOG_ERROR("do_PersonalShopBuy: Invalid fidelity for offline package item at pos=%d", j);
					CNetMsg::SP rmsg(new CNetMsg);
					PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
					SEND_Q(rmsg, ch->m_desc);
					return;
				}
			}

			if (item && item->IsPet())
				nCountOfPet++;

			if(item && item->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && item->m_itemProto->getItemSubTypeIdx() == IACCESSORY_ARTIFACT)
			{
				int error_ = ArtifactManager::instance()->checkValidUser(ch);
				if(error_ != 0)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					SysMsg(rmsg, (MSG_SYS_TYPE)error_);
					SEND_Q(rmsg, ch->m_desc);
					return ;
				}
			}

			list.AddItem(false, ps->GetPackageItemIndex(j), ps->GetPackageItemDBIndex(j), ps->GetPackageItemCount(j), ps->GetPackagePrice());
			search_vec.push_back(possible_search_t(item, ps->GetPackageItemCount(j)));
		}

		if (ch->m_inventory.isPossibleAdd(search_vec) == false)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_BUY_FULLINVENTORY);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
	}

	
	char normalcount = -1;
	RefMsg(msg) >> normalcount;
	if (normalcount == 0 && !packbuy)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
	if (normalcount < 0 || normalcount > ps->GetNormalCount())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	int i;
	std::vector<possible_search_t> search_vec_normal;
	for (i = 0; i < normalcount; i++)
	{
		int itemindex = -1;
		LONGLONG count = -1;
		RefMsg(msg) >> itemindex
					>> count;

		int pos = ps->FindItem(true, itemindex);
		if (pos == -1)
		{
			LOG_ERROR("do_PersonalShopBuy: Item not found in shop - itemindex=%d, isOffline=%d", itemindex, isOfflineShop);
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
		if (count < 1)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_COUNT);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
		if (ps->GetNormalItemCount(pos) < count)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_COUNT);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
		CItem* item = NULL;
		if (!isOfflineShop)
		{
			item = tch->m_inventory.FindByVirtualIndex(itemindex);
			if(item == NULL)
				return ;

			if (item->IsPet())
				nCountOfPet++;

			if(item->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && item->m_itemProto->getItemSubTypeIdx() == IACCESSORY_ARTIFACT)
			{
				int error_ = ArtifactManager::instance()->checkValidUser(ch);
				if(error_ != 0)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					SysMsg(rmsg, (MSG_SYS_TYPE)error_);
					SEND_Q(rmsg, ch->m_desc);
					return ;
				}
			}
		}
		else
		{
			// For offline shops, create item from fidelity to check properties
			const PSItemFidelity* fid = ps->GetNormalItemFidelity(pos);
			LOG_INFO("do_PersonalShopBuy: Checking fidelity for offline normal item - pos=%d, itemindex=%d, fid=%p, valid=%d",
				pos, itemindex, fid, fid ? fid->valid : -1);
			if (fid && fid->valid)
			{
				item = CreateItemFromOfflineShopFidelity(fid, ps->GetNormalItemDBIndex(pos), count);
				LOG_INFO("do_PersonalShopBuy: Created normal item from fidelity - itemindex=%d, dbindex=%d, plus=%d",
					itemindex, ps->GetNormalItemDBIndex(pos), item ? item->getPlus() : -1);

				if (item && item->IsPet())
					nCountOfPet++;

				if(item && item->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && item->m_itemProto->getItemSubTypeIdx() == IACCESSORY_ARTIFACT)
				{
					int error_ = ArtifactManager::instance()->checkValidUser(ch);
					if(error_ != 0)
					{
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsg(rmsg, (MSG_SYS_TYPE)error_);
						SEND_Q(rmsg, ch->m_desc);
						return ;
					}
				}
			}
			else
			{
				LOG_ERROR("do_PersonalShopBuy: Invalid fidelity for offline normal item at pos=%d, itemindex=%d", pos, itemindex);
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}
		}

		LONGLONG itemCost = ps->GetNormalItemPrice(pos) * count;
		if (itemCost < 0 || itemCost / count != ps->GetNormalItemPrice(pos))
		{
			GAMELOG << init("HACK PERSONAL SHOP OVERFLOW", ch)
					<< "price" << delim << ps->GetNormalItemPrice(pos)
					<< delim << "count" << delim << count
					<< delim << "result" << delim << itemCost << end;
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_MONEY);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
		needmoney += itemCost;
		if (needmoney < 0 || needmoney > ch->m_inventory.getMoney())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_MONEY);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
		
		if (list.FindItem(true, itemindex) != -1 || list.FindItem(false, itemindex) != -1)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_MONEY);
			SEND_Q(rmsg, ch->m_desc);
			GAMELOG << init("HACK PERSONAL SHOP BUY", ch) << end;
			return ;
		}
		list.AddItem(true, ps->GetNormalItemIndex(pos), ps->GetNormalItemDBIndex(pos), count, ps->GetNormalItemPrice(pos));

		// Include the item in the buyer's inventory-fit precheck for BOTH live and
		// offline shops. Without this the offline path skipped isPossibleAdd() and
		// the buyer could pay for items that had no room to be received.
		if (item != NULL)
		{
			search_vec_normal.push_back(possible_search_t(item, count));
		}
	}
	
	if (ch->m_inventory.isPossibleAdd(search_vec_normal) == false)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_BUY_FULLINVENTORY);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	if (nCountOfPet > MAX_OWN_PET)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_ANYMORE_PET);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	int needspace = 0;
	int pos;
	pos = list.GetNextNormalItem(-1);
	while (pos != -1)
	{
		int itemindex = list.GetNormalItemIndex(pos);

		if (!isOfflineShop)
		{
			CItem* pitem = tch->m_inventory.FindByVirtualIndex(itemindex);
			if (!pitem)
			{
				LOG_ERROR("do_PersonalShopBuy: Live vendor normal item not found - itemindex=%d", itemindex);
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
			if (pitem->Count() < list.GetNormalItemCount(pos))
			{
				LOG_ERROR("do_PersonalShopBuy: Live vendor normal item count insufficient - itemindex=%d, have=%lld, need=%lld", 
					itemindex, pitem->Count(), list.GetNormalItemCount(pos));
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
			if (!(pitem->m_itemProto->getItemFlag() & ITEM_FLAG_COUNT) || !ch->m_inventory.FindByDBIndex(pitem->getDBIndex(), pitem->getPlus(), pitem->getFlag()))
				needspace++;
		}
		else
		{
			LOG_INFO("do_PersonalShopBuy: Offline shop normal item validated - itemindex=%d, count=%lld", 
				itemindex, list.GetNormalItemCount(pos));
		}

		pos = list.GetNextNormalItem(pos);
	}
	pos = list.GetNextPackageItem(-1);
	while (pos != -1)
	{
		int itemindex = list.GetPackageItemIndex(pos);

		if (!isOfflineShop)
		{
			CItem* pitem = tch->m_inventory.FindByVirtualIndex(itemindex);
			if (!pitem)
			{
				LOG_ERROR("do_PersonalShopBuy: Live vendor package item not found - itemindex=%d", itemindex);
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
			if (pitem->Count() < list.GetPackageItemCount(pos))
			{
				LOG_ERROR("do_PersonalShopBuy: Live vendor package item count insufficient - itemindex=%d, have=%lld, need=%lld", 
					itemindex, pitem->Count(), list.GetPackageItemCount(pos));
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
			if (!(pitem->m_itemProto->getItemFlag() & ITEM_FLAG_COUNT) || !ch->m_inventory.FindByDBIndex(pitem->getDBIndex(), pitem->getPlus(), pitem->getFlag()))
				needspace++;
		}
		else
		{
			LOG_INFO("do_PersonalShopBuy: Offline shop package item validated - itemindex=%d, count=%lld", 
				itemindex, list.GetPackageItemCount(pos));
		}

		pos = list.GetNextPackageItem(pos);
	}

	
	if (ch->m_inventory.getEmptyCount() < needspace)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_BUY_FULLINVENTORY);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	// OFFLINE SHOP PURCHASE PATH - handle offline vendor purchases separately
	if (isOfflineShop)
	{
		LOG_INFO("do_PersonalShopBuy: Processing offline shop purchase - vendor charindex=%d", charindex);

		// Check buyer has enough money
		if (ch->m_inventory.getMoney() < needmoney)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_MONEY);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}

		// Deduct money from buyer
		ch->m_inventory.decreaseMoney(needmoney);

		GAMELOG << init("PERSONAL SHOP BUY OFFLINE", ch);
		GAMELOG << "SHOP" << delim << offlineShop->GetCharIndex() << delim
				<< "OFFLINE" << delim;
		if (packbuy)
			GAMELOG << "PACKAGE" << delim;
		else
			GAMELOG << "NO PACKAGE" << delim;
		GAMELOG << "NEEDMONEY" << delim << needmoney << delim;
		GAMELOG << "ITEMS";

		// First, collect list of items being purchased and their current item_ids
		// We need to do this BEFORE removing items or saving to DB
		std::vector<PurchasedItem> purchasedItems;

		// Process normal items from offline shop
		pos = list.GetNextNormalItem(-1);
		while (pos != -1)
		{
			int itemindex = list.GetNormalItemIndex(pos);
			int itemdbindex = list.GetNormalItemDBIndex(pos);
			LONGLONG count = list.GetNormalItemCount(pos);
			LONGLONG price = list.GetNormalItemPrice(pos);

			// Handle cash items specially
			// NOTE: Cash items now handled by Cash Exchange NPC - this is deprecated
			if (itemdbindex == 999999)  // PS_CASH_ITEM_ID sentinel
			{
				LOG_INFO("Deprecated: Cash transaction attempted via offline shop");
				// Skip processing - cash exchange moved to NPC system

				GAMELOG << delim << "CASH[" << count << "]@[" << price << "NAS]";

				pos = list.GetNextNormalItem(pos);
				continue;
			}

			// Get fidelity data from offline shop
			int shopPos = offlineShop->FindItem(true, itemindex);
			if (shopPos != -1)
			{
				const PSItemFidelity* fidelity = offlineShop->GetNormalItemFidelity(shopPos);
				CItem* item = CreateItemFromOfflineShopFidelity(fidelity, list.GetNormalItemDBIndex(pos), count);

				if (item)
				{
					ch->m_inventory.addItem(item);
					GAMELOG << delim << "itemindex[" << itemindex << "]count[" << count << "]";

					// Capture the item info BEFORE removing it
					int itemDbId = offlineShop->GetNormalItemId(shopPos);
					int itemDbIndex = offlineShop->GetNormalItemDBIndex(shopPos);
					PurchasedItem pi;
					pi.itemindex = itemindex;
					pi.itemdbindex = itemDbIndex;
					pi.count = count;
					pi.price = price;
					pi.itemDbId = itemDbId;
					purchasedItems.push_back(pi);

					// Remove the item from the offline shop inventory
					offlineShop->RemoveNormalItem(itemindex, count);
					LOG_INFO("do_PersonalShopBuy OFFLINE: Removed item from shop inventory - itemindex=%d count=%lld itemDbId=%d itemDbIndex=%d", 
						itemindex, count, itemDbId, itemDbIndex);

					LOG_INFO("do_PersonalShopBuy OFFLINE: Sold item itemindex=%d count=%lld price=%lld",
						itemindex, count, price);
				}
				else
				{
					LOG_ERROR("do_PersonalShopBuy OFFLINE: Failed to create item from fidelity");
					GAMELOG << delim << "itemindex[" << itemindex << "]FAILED";
				}
			}

			pos = list.GetNextNormalItem(pos);
		}

		GAMELOG << end;

		// Queue vendor payment settlement for when they log in
		LOG_INFO("do_PersonalShopBuy OFFLINE: Sale recorded - vendor will receive settlement on next login. Amount: %lld",
			needmoney);

		// Send success response to buyer
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopBuyMsg(rmsg, msg, ch);
			SEND_Q(rmsg, ch->m_desc);
		}

		ch->m_personalShopBuyPulse = gserver->m_pulse + (2 * PULSE_REAL_SEC);

		// Save buyer character data
		DBManager::instance()->SaveCharacterInfo(ch->m_desc, false);

		// Save the offline shop back to database with updated inventory (items removed)
		// This must happen BEFORE recording sales to finalize item_ids in case this is a new shop
		SaveOfflineShopToDB(offlineShop.get(), NULL);
		LOG_INFO("do_PersonalShopBuy OFFLINE: Saved updated offline shop to database after purchase");

		// Now record the sales using the item_ids we captured before removal
		for (const auto& pi : purchasedItems)
		{
			RecordOfflineShopSaleToDB(
				offlineShop->GetShopId(),
				pi.itemDbId,
				offlineShop->GetCharIndex(),
				ch->m_index,
				ch->m_name,
				pi.itemindex,
				pi.itemdbindex,
				pi.count,
				pi.price
			);
			LOG_INFO("do_PersonalShopBuy OFFLINE: Recorded sale - itemindex=%d itemDbId=%d", pi.itemindex, pi.itemDbId);
		}

		// Remove sold items from the kept-alive vendor CPC's inventory AND
		// persist to t_inven%02d so the seller can no longer resell them.
#ifdef OFFLINE_SHOPS
		RemoveSoldItemsFromOfflineVendor(offlineShop.get(), purchasedItems);
#endif

		return ;
	}
	// END OFFLINE SHOP PURCHASE PATH

	// LIVE SHOP PURCHASE PATH - original code for live vendors


	GAMELOG << "SHOP" << delim << tch->m_name << delim
			<< tch->m_nick << delim
			<< tch->m_desc->m_idname << delim;
	if (packbuy)
		GAMELOG << "PACKAGE" << delim;
	else
		GAMELOG << "NO PACKAGE" << delim;
	GAMELOG << "NEEDMONEY" << delim << needmoney << delim;
	GAMELOG << "ITEMS";


	pos = list.GetNextNormalItem(-1);
	while (pos != -1)
	{
		int itemindex = list.GetNormalItemIndex(pos);
		int itemdbindex = list.GetNormalItemDBIndex(pos);
		LONGLONG count = list.GetNormalItemCount(pos);

		// Handle cash items specially in live vendor shops
		// NOTE: Cash items now handled by Cash Exchange NPC - this is deprecated
		if (itemdbindex == 999999)  // PS_CASH_ITEM_ID sentinel
		{
			LOG_INFO("Deprecated: Cash transaction attempted in live shop");
			// Skip processing - cash exchange moved to NPC system
			continue;
		}

		CItem* pitem = NULL;
		CItem* nitem = NULL;

		if (!isOfflineShop)
		{
			pitem = tch->m_inventory.FindByVirtualIndex(itemindex);
			if (!pitem)
			{
				LOG_ERROR("do_PersonalShopBuy: Live vendor item not found - itemindex=%d", itemindex);
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}

			pitem->unWearPos();

			if (pitem->IsPet())
			{
				CPet* pet = tch->GetPet(pitem->getPlus());
				if (pet)
				{
					REMOVE_FROM_BILIST(pet, tch->m_petList, m_prevPet, m_nextPet);
					pet->SetOwner(ch);
					ADD_TO_BILIST(pet, ch->m_petList, m_prevPet, m_nextPet);

					std::string str = boost::str(boost::format(
													 "UPDATE t_pet SET a_owner=%1% WHERE a_index=%2% LIMIT 1")
												 % ch->m_index % pitem->getPlus());
					DBManager::instance()->pushQuery(ch->m_desc->m_index, str);

					{
						CNetMsg::SP rmsg(new CNetMsg);
						ExPetStatusMsg(rmsg, pet);
						SEND_Q(rmsg, ch->m_desc);
					}
					{
						CNetMsg::SP rmsg(new CNetMsg);
						ExPetSkillListMsg(rmsg, pet);
						SEND_Q(rmsg, ch->m_desc);
					}
				}
			}

			if( pitem->IsAPet() )
			{
				CAPet* apet = tch->GetAPet(pitem->getPlus());
				if( apet )
				{
					REMOVE_FROM_BILIST(apet, tch->m_pApetlist, m_pPrevPet, m_pNextPet);
					apet->SetOwner(ch);
					apet->AddFaith(-10);
					ADD_TO_BILIST(apet, ch->m_pApetlist, m_pPrevPet, m_pNextPet);

					std::string str = boost::str(boost::format(
													 "UPDATE t_apets SET a_owner=%1% WHERE a_index=%2% LIMIT 1")
												 % ch->m_index % pitem->getPlus());
					DBManager::instance()->pushQuery(ch->m_desc->m_index, str);
				}
			}

			if (pitem->Count() > count)
			{
				nitem = gserver->m_itemProtoList.CreateItem(pitem->getDBIndex(), -1, pitem->getPlus(), pitem->getFlag(), count);
				ch->m_inventory.addItem(nitem);
				tch->m_inventory.decreaseItemCount(pitem, count);
			}
			else
			{
				int tab = pitem->tab();
				int invenIndex = pitem->getInvenIndex();
				ch->m_inventory.addItem(pitem);
				nitem = pitem;
				tch->m_inventory.eraseNotFreeByInvenIndex(tab, invenIndex);
			}

			if(pitem->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && pitem->m_itemProto->getItemSubTypeIdx() == IACCESSORY_ARTIFACT)
			{
				ArtifactManager::instance()->changeOnwer(ch, pitem);
			}
		}
		else
		{
			LOG_INFO("do_PersonalShopBuy: Offline shop normal item being transferred - itemindex=%d, count=%lld", itemindex, count);
			int pos = offlineShop->FindItem(true, itemindex);
			if (pos < 0)
			{
				LOG_ERROR("do_PersonalShopBuy: Offline shop normal item not in inventory - itemindex=%d", itemindex);
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
			const PSItemFidelity* fidelity = offlineShop->GetNormalItemFidelity(pos);
			if (!fidelity || !fidelity->valid)
			{
				LOG_ERROR("do_PersonalShopBuy: Offline shop normal item fidelity invalid - itemindex=%d, pos=%d", itemindex, pos);
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
			int dbindex = offlineShop->GetNormalItemDBIndex(pos);
			pitem = CreateItemFromOfflineShopFidelity(fidelity, dbindex, count);
			if (!pitem)
			{
				LOG_ERROR("do_PersonalShopBuy: Failed to create offline normal item - itemindex=%d", itemindex);
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
			ch->m_inventory.addItem(pitem);
			nitem = pitem;
		}

		GAMELOG << delim << itemlog(nitem) << delim << count;
		ps->RemoveNormalItem(itemindex, count);

		if (isOfflineShop)
		{
			int dbShopPos = offlineShop->FindItem(true, itemindex);
			if (dbShopPos >= 0)
			{
				int itemDbId = offlineShop->GetNormalItemId(dbShopPos);
				LONGLONG price = list.GetNormalItemPrice(pos);

				RecordOfflineShopSaleToDB(
					offlineShop->GetShopId(),
					itemDbId,
					offlineShop->GetCharIndex(),
					ch->m_index,
					ch->m_name,
					itemindex,
					offlineShop->GetNormalItemDBIndex(dbShopPos),
					count,
					price
				);
				LOG_INFO("do_PersonalShopBuy: Recorded offline normal item sale - shop_id=%d, item_id=%d, buyer=%d, count=%lld",
					offlineShop->GetShopId(), itemDbId, ch->m_index, count);
			}
		}

		pos = list.GetNextNormalItem(pos);
	}

	
	pos = list.GetNextPackageItem(-1);
	while (pos != -1)
	{
		int itemindex = list.GetPackageItemIndex(pos);
		LONGLONG count = list.GetPackageItemCount(pos);

		CItem* pitem = NULL;
		CItem* nitem = NULL;

		if (!isOfflineShop)
		{
			pitem = tch->m_inventory.FindByVirtualIndex(itemindex);
			if (!pitem)
			{
				LOG_ERROR("do_PersonalShopBuy: Live vendor package item not found - itemindex=%d", itemindex);
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}

			if (pitem->IsPet())
			{
				CPet* pet = tch->GetPet(pitem->getPlus());
				if (pet)
				{
					REMOVE_FROM_BILIST(pet, tch->m_petList, m_prevPet, m_nextPet);
					pet->SetOwner(ch);
					ADD_TO_BILIST(pet, ch->m_petList, m_prevPet, m_nextPet);

					std::string str = boost::str(boost::format(
													 "UPDATE t_pet SET a_owner=%1% WHERE a_index=%2% LIMIT 1")
												 % ch->m_index % pitem->getPlus());
					DBManager::instance()->pushQuery(ch->m_desc->m_index, str);

					{
						CNetMsg::SP rmsg(new CNetMsg);
						ExPetStatusMsg(rmsg, pet);
						SEND_Q(rmsg, ch->m_desc);
					}
					{
						CNetMsg::SP rmsg(new CNetMsg);
						ExPetSkillListMsg(rmsg, pet);
						SEND_Q(rmsg, ch->m_desc);
					}
				}
			}

			if( pitem->IsAPet() )
			{
				CAPet* apet = tch->GetAPet(pitem->getPlus());
				if( apet )
				{
					REMOVE_FROM_BILIST(apet, tch->m_pApetlist, m_pPrevPet, m_pNextPet);
					apet->SetOwner(ch);
					apet->AddFaith(-10);
					ADD_TO_BILIST(apet, ch->m_pApetlist, m_pPrevPet, m_pNextPet);

					std::string str = boost::str(boost::format(
													 "UPDATE t_apets SET a_owner=%1% WHERE a_index=%2% LIMIT 1")
												 % ch->m_index % pitem->getPlus());
					DBManager::instance()->pushQuery(ch->m_desc->m_index, str);
				}
			}

			if (pitem->Count() > count)
			{
				nitem = gserver->m_itemProtoList.CreateItem(pitem->getDBIndex(), -1, pitem->getPlus(), pitem->getFlag(), count);
				ch->m_inventory.addItem(nitem);
				tch->m_inventory.decreaseItemCount(pitem, count);
			}
			else
			{
				int tab = pitem->tab();
				int invenIndex = pitem->getInvenIndex();
				ch->m_inventory.addItem(pitem);
				nitem = pitem;
				tch->m_inventory.eraseNotFreeByInvenIndex(tab, invenIndex);
			}

			if(pitem->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && pitem->m_itemProto->getItemSubTypeIdx() == IACCESSORY_ARTIFACT)
			{
				ArtifactManager::instance()->changeOnwer(ch, pitem);
			}
		}
		else
		{
			LOG_INFO("do_PersonalShopBuy: Offline shop package item being transferred - itemindex=%d, count=%lld", itemindex, count);
			int pos = offlineShop->FindItem(false, itemindex);
			if (pos < 0)
			{
				LOG_ERROR("do_PersonalShopBuy: Offline shop package item not in inventory - itemindex=%d", itemindex);
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
			const PSItemFidelity* fidelity = offlineShop->GetPackageItemFidelity(pos);
			if (!fidelity || !fidelity->valid)
			{
				LOG_ERROR("do_PersonalShopBuy: Offline shop package item fidelity invalid - itemindex=%d, pos=%d", itemindex, pos);
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
			int dbindex = offlineShop->GetPackageItemDBIndex(pos);
			pitem = CreateItemFromOfflineShopFidelity(fidelity, dbindex, count);
			if (!pitem)
			{
				LOG_ERROR("do_PersonalShopBuy: Failed to create offline package item - itemindex=%d", itemindex);
				CNetMsg::SP rmsg(new CNetMsg);
				PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}
			ch->m_inventory.addItem(pitem);
			nitem = pitem;
		}

		GAMELOG << delim << itemlog(nitem) << delim << count;
		ps->RemovePackage();

		if (isOfflineShop)
		{
			int dbShopPos = offlineShop->FindItem(false, itemindex);
			if (dbShopPos >= 0)
			{
				int itemDbId = offlineShop->GetPackageItemId(dbShopPos);
				LONGLONG price = list.GetPackagePrice();
				int itemDbIndex = offlineShop->GetPackageItemDBIndex(dbShopPos);

				RecordOfflineShopSaleToDB(
					offlineShop->GetShopId(),
					itemDbId,
					offlineShop->GetCharIndex(),
					ch->m_index,
					ch->m_name,
					itemindex,
					itemDbIndex,
					count,
					price
				);
				LOG_INFO("do_PersonalShopBuy: Recorded offline package item sale - shop_id=%d, item_id=%d, buyer=%d, count=%lld", 
					offlineShop->GetShopId(), itemDbId, ch->m_index, count);

				// Package purchases for offline shops (if reached) are handled by
				// RemoveSoldItemsFromOfflineVendor() via the offline branch above.
			}
		}

		pos = list.GetNextPackageItem(pos);
	}

	GAMELOG << end;

	
	if (needmoney <= 0 || ch->m_inventory.getMoney() < needmoney)
	{
		GAMELOG << init("HACK PERSONAL SHOP MONEY", ch)
				<< "needmoney" << delim << needmoney
				<< delim << "hasmoney" << delim << ch->m_inventory.getMoney() << end;
		return;
	}
	ch->m_inventory.decreaseMoney(needmoney);

	ch->m_personalShopBuyPulse = gserver->m_pulse + (2 * PULSE_REAL_SEC);

	int rate = (shoptype & (PST_PACKAGE | PST_PREMIUM)) ? PS_TEX_PREMIUM : PS_TEX_NORMAL;

	tch->m_inventory.increaseMoney(needmoney - (needmoney * rate / 10000));

	
	DBManager::instance()->SaveCharacterInfo(ch->m_desc, false);
	DBManager::instance()->SaveCharacterInfo(tch->m_desc, false);

	
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopBuyMsg(rmsg, msg, ch);
		SEND_Q(rmsg, tch->m_desc);
	}

	
	
	if (ps->GetType() != shoptype)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PersonalShopChangeMsg(rmsg, tch);
		tch->m_pArea->SendToCell(rmsg, tch, true);
		if (ps->GetType() == PST_NOSHOP)
		{
			tch->m_personalshop.reset();
		}
	}
}
