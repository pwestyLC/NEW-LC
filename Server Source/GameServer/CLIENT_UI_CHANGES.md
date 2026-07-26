# Client-Side UI Changes for Cash Exchange Feature

## Minimal UI Changes Required

### 1. Personal Shop Creation Dialog

**Location**: `ShopUI.cpp` or related shop creation UI

**Changes**:
- Add special "Cash" item option that doesn't require inventory selection
- When "Cash" is selected:
  - Skip inventory browsing
  - Show input fields for:
	- **Cash Amount**: How much cash to sell (numeric input)
	- **Exchange Rate**: NAS per cash unit (numeric input)
	- Example: User enters "100 cash @ 10,000,000 NAS"

**Code Pattern**:
```cpp
// When user selects to add "Cash Item" (ID 999999)
if (itemdbindex == 999999) // PS_CASH_ITEM_ID
{
	// Show special cash item UI
	// Get cashAmount and exchangeRate from dialog

	// Send to server
	msg >> itemdbindex (999999)
		>> cashAmount (e.g., 100)
		>> exchangeRate (e.g., 10000000)
}
```

### 2. Personal Shop Display/Browsing

**Location**: `PersonalshopUI.cpp` or shop list view

**Changes**:
- When displaying shop items, check if itemdbindex == 999999
- If it's a cash item:
  - Display special icon/badge ("💰" or "CASH")
  - Show exchange rate prominently
  - Display as: "100 Cash @ 10,000,000 NAS" instead of normal item format
  - Don't attempt to look up in item proto database

**Code Pattern**:
```cpp
if (item->itemdbindex == 999999) // PS_CASH_ITEM_ID
{
	// Display special cash item
	sprintf(buffer, "Cash: %lld @ %lld NAS",
			item->count,           // amount of cash
			item->price);          // NAS per cash unit

	// Show special formatting/icon
	DisplayCashItemUI(buffer);
}
else
{
	// Normal item display
	DisplayNormalItemUI(item);
}
```

### 3. Purchase Confirmation

**Location**: Personal shop buy dialog

**Changes**:
- When buying cash item, show clear confirmation:
  ```
  [Confirm Purchase]

  Item: Cash
  Quantity: 100
  Unit Price: 10,000,000 NAS
  Total Cost: 1,000,000,000 NAS

  [Confirm] [Cancel]
  ```
- Validate buyer has sufficient NAS before allowing purchase
- Show buyer's current cash balance after transaction

### 4. Transaction Log

**Optional Enhancement**:
- Add cash transactions to personal shop transaction log:
  ```
  [17:30] Sold: 100 Cash @ 10,000,000 NAS = 1,000,000,000 NAS profit
  ```

### 5. Item Database Handling

**Important**: 
- Do NOT add cash items to the item proto database
- Item ID 999999 should be hardcoded as special case
- Skip item proto lookup for this ID

**Code Pattern**:
```cpp
int itemdbindex = GetItemDBIndexFromPacket();

if (itemdbindex == 999999) // PS_CASH_ITEM_ID - skip proto lookup
{
	// Handle as virtual cash item
	HandleCashItem();
}
else
{
	// Normal path - lookup in proto database
	CItemProto* proto = m_itemProtoList.Find(itemdbindex);
}
```

## Network Packet Format

### Server to Client - Personal Shop Item List

For cash items, the existing personal shop item protocol can be reused:
- **itemdbindex**: 999999 (special value indicating cash)
- **count**: Amount of cash (e.g., 100)
- **price**: Exchange rate in NAS (e.g., 10,000,000)
- **tab/invenIndex**: Can be ignored for cash items

The client should recognize itemdbindex == 999999 and:
1. Skip inventory item lookup
2. Display special UI for cash
3. Calculate total cost as: count × price

### Client to Server - Buy Request

Existing buy protocol works unchanged:
- Include cash item same as normal items
- itemdbindex = 999999
- Server handles special cash transfer logic

## Testing Checklist

- [ ] Create personal shop with cash items (no inventory items required)
- [ ] Verify cash is deducted from seller's bg_user.cash
- [ ] Browse shop and see cash items displayed correctly
- [ ] Purchase cash items and verify NAS is deducted
- [ ] Verify buyer's cash increases in bg_user table
- [ ] Close shop without selling all cash - verify unsold cash is refunded
- [ ] Test mixed shops (both normal items and cash)
- [ ] Test buying multiple cash items in one transaction
- [ ] Verify transaction logs show cash exchanges

## No Changes Required For

- Item proto database
- Inventory system
- Equipment/wear system
- Pet system
- Storage system
- Any existing item functionality
