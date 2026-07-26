// ================================================================
// doFuncPersonalShopDB.h
// Database operations for offline personal shops
// ================================================================

#ifndef __DO_FUNC_PERSONAL_SHOP_DB_H__
#define __DO_FUNC_PERSONAL_SHOP_DB_H__

#ifdef OFFLINE_SHOPS

#include <vector>
#include "PersonalShop.h"

class CPC;

// Save offline shop and all its items to the database when player disconnects
void SaveOfflineShopToDB(CPersonalShop* pShop, CPC* pChar);

// Record a sale in the offline shop database
void RecordOfflineShopSaleToDB(int shopId, int itemId, int vendorCharIndex, int buyerCharIndex,
							   const char* buyerCharName, int itemindex, int itemdbindex, LONGLONG itemCount, LONGLONG pricePerItem);

// Update offline shop status (e.g., close shop)
void UpdateOfflineShopStatusToDB(int shopId, bool bIsActive);

// Update offline shop position when character disconnects
void UpdateOfflineShopPosition(CPC* pChar);

// Load offline shops from database (called on server startup)
void LoadOfflineShopsFromDB();

// Process settlement payouts for a vendor on login (called when character enters game)
void ProcessOfflineShopSettlementOnLogin(CPC* pChar);

// Restore owner's offline shop on login so they can see and manage it
void RestoreOfflineShopOnLogin(CPC* pChar);

// Load player-vendor NPCs from database and spawn them in zones (called at server startup)
void LoadPlayerVendorNPCsFromDB();

// Create player-vendor NPC entries for offline shops (updates DB with shop location/info)
void CreateDummyNPCsForOfflineShops();

// Broadcast all offline shops in the area to a newly logging-in player
// This ensures newly logged-in players can see all offline vendor characters
void BroadcastOfflineShopsInAreaToPlayer(CPC* pChar);

// Process settlements for all online characters (call after LoadOfflineShopsFromDB or anytime)
void ProcessAllOfflineShopSettlementsForOnlineCharacters();

// Mark sales as notified to Discord bot
void MarkSalesAsNotifiedToDB(const std::vector<int>& saleIds);

// Cleanup expired offline shops (called periodically, e.g., every hour)
void CleanupExpiredOfflineShops();

// Get query string for Discord bot to fetch unsold offline shops
const char* GetDiscordBotOfflineShopsQuery();

// Get query string for Discord bot to fetch recent sales for notifications
const char* GetDiscordBotRecentSalesQuery();

// Reconstruct a CItem from offline shop fidelity data for purchase
CItem* CreateItemFromOfflineShopFidelity(const PSItemFidelity* fidelity, int itemDBIndex, LONGLONG count);

// Build PSItemFidelity struct from a live CItem for in-memory storage
PSItemFidelity BuildItemFidelityFromLive(CItem* item);

// Item purchased from offline shop - used for tracking what to remove from inventory
struct PurchasedItem {
	int itemindex;
	int itemdbindex;
	LONGLONG count;
	LONGLONG price;
	int itemDbId;
};

// Remove sold items from vendor's true inventory when they log in
// Called from RestoreOfflineShopOnLogin after settlement is processed
void RemoveSoldItemsFromVendorInventory(CPC* pVendor);

#endif // OFFLINE_SHOPS

#endif // __DO_FUNC_PERSONAL_SHOP_DB_H__
