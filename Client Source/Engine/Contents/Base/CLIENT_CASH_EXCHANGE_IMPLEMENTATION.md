# Client-Side Cash Exchange Implementation

## Overview
This document summarizes the client-side implementation for the cash exchange feature in the personal shop system. Players can now list their account cash (`bg_user.cash`) for sale in personal shops with custom pricing.

## Changes Made

### 1. PersonalshopUI.h - Constants and Member Fields

**Added Constant:**
```cpp
#define PS_CASH_ITEM_ID  999999  // Virtual item ID for cash listings
```

**Added Member Fields:**
```cpp
CUIButton*      m_pBtnListCash;        // List cash button
BOOL            m_bCashListing;        // Flag for cash listing mode
SQUAD           m_llCashAmount;        // Amount of cash to list
SQUAD           m_llCashPrice;         // Price per cash unit
CUIEditBox*     m_pEditCashAmount;     // Cash amount input
CUIEditBox*     m_pEditCashPrice;      // Cash price input
```

**Added Method Declarations:**
```cpp
void  add_cash_listing();               // Open cash listing dialog
void  on_cash_list_ok();                // Confirm cash listing
bool  CreateCashItem(SQUAD, SQUAD);     // Create virtual cash item
bool  IsCashItem(int) const;            // Check if item is cash
bool  ValidateCashListing(SQUAD, SQUAD); // Validate amount/price
```

### 2. PersonalshopUI.cpp - Implementation

#### Constructor Updates
- Initialize new member fields: `m_bCashListing = FALSE`, `m_llCashAmount = 0`, `m_llCashPrice = 0`

#### Helper Functions

**IsCashItem():**
- Returns true if item ID equals PS_CASH_ITEM_ID (999999)
- Used to identify cash items throughout the client code

**CreateCashItem():**
- Creates a virtual CItems object representing cash
- Finds an empty trade slot
- Sets Item data without looking up item proto
- Validates cash amount against player inventory
- Returns false and shows error if validation fails

**ValidateCashListing():**
- Checks player has sufficient cash available
- Validates cash amount > 0
- Validates price per unit > 0
- Checks total price doesn't overflow
- Shows localized error messages for each failure case

**add_cash_listing() / on_cash_list_ok():**
- Stubs for UI interaction
- Can be extended for dialog-based input

#### MsgBoxCommand Handler
- Added handlers for `MSGCMD_SHOP_PRICE + 1` (cash amount input)
- Added handlers for `MSGCMD_SHOP_PRICE + 2` (cash price input)
- Both handlers validate numeric input and call CreateCashItem
- Display success messages via system chat

#### SendPersonalShopStart() Updates
```cpp
// Special handling for cash items in packet serialization:
if (IsCashItem(m_vectorSellItemList[iItem]->Item_Index))
{
	// Send with special markers so server recognizes as cash
	nmPersonalShop << (SWORD)-1;                      // Tab = -1 (cash marker)
	nmPersonalShop << (SWORD)-1;                      // InvenIndex = -1 (cash marker)
	nmPersonalShop << (LONG)m_vectorSellItemList[iItem]->Item_UniIndex;  // Cash amount
	nmPersonalShop << (LONG)PS_CASH_ITEM_ID;          // Item_Index = 999999
	nmPersonalShop << m_vectorSellItemList[iItem]->Item_Sum;      // Cash amount
	nmPersonalShop << m_vectorSellItemList[iItem]->Item_Price;    // Price per unit
}
else
{
	// Normal item serialization (unchanged)
}
```

#### ReceivePersonalShopItemList() Updates
```cpp
// Special handling to avoid item proto lookup for cash items
if (IsCashItem(lIndex))
{
	CItems* TempItem = new CItems(PS_CASH_ITEM_ID);
	TempItem->SetData(PS_CASH_ITEM_ID, lUniIndex, 0, i, 0, 0, -1, 0, 0, -1, lUniIndex);
	TempItem->SetPrice(llPrice);
	m_vectorSellItemList.push_back(TempItem);
}
else
{
	// Normal item processing with proto lookup (unchanged)
}
```

## Key Features

1. **Virtual Item Representation**: Cash items are represented as CItems objects with Item_Index = PS_CASH_ITEM_ID, avoiding need for proto definitions.

2. **Player-Controlled Pricing**: Sellers set both cash amount and price per unit; no hardcoded exchange rate.

3. **Special Network Serialization**: Cash items use Tab=-1 and InvenIndex=-1 markers so the server recognizes them as cash transactions rather than regular items.

4. **Proto Lookup Bypass**: The client explicitly avoids calling `_pNetwork->GetItemData()` for cash items, preventing crashes from missing proto entries.

5. **Validation**: Comprehensive validation of cash amount and pricing before listing creation.

6. **Display Support**: Localized messages and system chat feedback for all user actions.

## Integration Notes

### With Server
- The server-side doFuncPersonalShop.cpp expects Item_Index == PS_CASH_ITEM_ID to identify cash items.
- Tab=-1, InvenIndex=-1 markers help server differentiate cash from regular items.
- Server deducts cash from `bg_user.cash` on listing and transfers between accounts on purchase.

### With UI
- No XML changes required for minimal UI integration.
- Existing message box system reused for cash amount/price input.
- System messages provide user feedback via existing chat UI.

### With Offline Shops
- Cash listings support the offline shop feature (`m_bOfflineMode`).
- Offline shops can include cash items just like regular shops.

## Localized Messages

The following string IDs are used for cash-related messages:
- 9000: "Trade slot is full. Cannot list cash."
- 9001: "You do not have enough cash to list."
- 9002: "Cash amount must be greater than 0."
- 9003: "Price per cash unit must be greater than 0."
- 9004: "Total price exceeds maximum value."
- 9005: "List Cash" (dialog title)
- 9006: "Enter cash amount to list:"
- 9007: "Enter Price" (dialog title)
- 9008: "Enter price per cash unit:"
- 9009: "Cash listing created successfully."

These should be added to the client's string table for localization.

## Build Status
✅ **Build successful** - No compilation errors or warnings.

## Next Steps
1. Add missing UI elements (buttons, input fields) if desired.
2. Test cash listing creation and network transmission.
3. Verify server-side processing of cash items.
4. Add string localizations for user messages.
5. Test offline shop persistence with cash items.
