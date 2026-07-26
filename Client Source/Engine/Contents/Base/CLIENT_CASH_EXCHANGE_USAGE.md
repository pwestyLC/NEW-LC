# Client-Side: How Players Create and Sell Cash Listings

## Flow Overview

### Step 1: Player Opens Cash Exchange UI
- Player interacts with **Cash Exchange NPC** (or menu option)
- Client sends `MSG_CASHEXCHANGE_OPEN` message
- Server responds with `MSG_CASHEXCHANGE_LISTING_LIST` containing all active listings

### Step 2: View Active Listings
- UI displays list of sellers with:
  - Seller name
  - Cash amount available
  - Price per unit (in NAS or game currency)
  - Total transaction price
- Player can scroll through and review prices

### Step 3: Create New Listing (If Selling)
Players who want to **list their cash for sale** follow:

#### 3a. Click "List Cash" Button
- Appears in the cash exchange UI
- Opens a dialog for input

#### 3b. Enter Amount to List
```
Dialog: "How much cash do you want to list?"
- Input field for cash amount
- Validation:
  - Must be > 0
  - Must not exceed player's current cash balance
  - Max might be limited (e.g., 10 million)
```

#### 3c. Set Price Per Unit
```
Dialog: "What is your price per cash unit?"
- Input field for price (in NAS or game currency)
- Validation:
  - Must be > 0
  - Total price = amount × price_per_unit must fit in LONGLONG
  - Min/max price limits might be enforced
```

#### 3d. Confirm Listing
- Player sees summary:
  ```
  Creating listing:
  - Amount: 100,000 cash
  - Price per unit: 50 NAS
  - Total value: 5,000,000 NAS
  - You will receive: 5,000,000 NAS after sale

  [Confirm] [Cancel]
  ```
- Click Confirm

#### 3e. Server Validates and Creates Listing
**Server-side checks:**
1. Player still has the cash (in case of concurrent operations)
2. Amount is valid (> 0)
3. Price is valid (> 0)
4. Total price doesn't overflow
5. Player hasn't exceeded max active listings

**If valid:**
- Deduct cash from player's account
- Insert into `t_cash_exchange_listings` table
- Send success response to client
- Broadcast updated listings to all players

**If invalid:**
- Send error message: "Insufficient cash" / "Invalid amount" / etc.
- No changes made

### Step 4: Listing Appears for Others
Once created, the listing:
- Appears in other players' cash exchange UIs
- Shows seller's character name
- Shows cash amount and price
- Can be purchased by other players

### Step 5: Monitoring Your Listing
Players can view their own listings (optional feature):
- "My Listings" tab in cash exchange UI
- Shows:
  - Amount still available
  - Original price per unit
  - Time listed
  - [Cancel Listing] button

### Step 6: Listing Sold
When someone buys from the listing:
- If fully sold (all cash purchased):
  - Listing marked as inactive
  - Seller receives currency (NAS) in inventory
  - Optional: Notification to seller

- If partially sold (e.g., 100k of 200k purchased):
  - Listing remains active
  - Amount updated to 100k remaining
  - Seller receives partial payment

### Step 7: Cancel Listing (Seller)
If player wants to remove listing before it sells:
- Click [Cancel] on listing
- Server refunds the cash
- Listing marked as inactive
- Confirmation message sent

## UI Layout

### Cash Exchange Window (Using itemproduct.xml style)

```
┌─────────────────────────────────────┐
│ Cash Exchange                    [X]│
├─────────────────────────────────────┤
│                                     │
│  [View Listings] [My Listings]      │
│                                     │
│  Seller Name     | Amount | Price   │
│ ─────────────────────────────────   │
│  Player1         | 50k    | 25 NAS  │
│  Player2         | 100k   | 26 NAS  │
│  Player3         | 200k   | 25 NAS  │
│                                     │
│  Selected: Player1 - 50,000 cash    │
│  Price: 25 NAS each = 1,250,000 NAS │
│                                     │
│  Buy Amount: [_____] [Max]          │
│                                     │
│  [Buy] [List Cash] [Refresh] [Exit] │
│                                     │
└─────────────────────────────────────┘
```

### "List Cash" Dialog

```
┌────────────────────────┐
│ List Cash for Sale     │
├────────────────────────┤
│                        │
│ Your Cash Balance:     │
│ 5,000,000              │
│                        │
│ Amount to List:        │
│ [____________]         │
│                        │
│ Price per Unit (NAS):  │
│ [____________]         │
│                        │
│ Preview:               │
│ Total Value: 0 NAS     │
│                        │
│    [Create] [Cancel]   │
│                        │
└────────────────────────┘
```

## Implementation: Client-Side Code Pattern

### In PersonalshopUI or CashExchangeUI

```cpp
// Step 1: Open dialog for cash listing
void CCashExchangeUI::OnListCashClick()
{
	ShowCashListingDialog();
}

// Step 2: Handle cash amount input
void CCashExchangeUI::OnCashAmountInput(SQUAD llAmount)
{
	// Validate
	if (llAmount <= 0) {
		ShowError("Amount must be greater than 0");
		return;
	}

	if (llAmount > GetPlayerCash()) {
		ShowError("Insufficient cash");
		return;
	}

	m_llCashAmount = llAmount;
	UpdatePreview();
}

// Step 3: Handle price input
void CCashExchangeUI::OnPricePerUnitInput(SQUAD llPrice)
{
	// Validate
	if (llPrice <= 0) {
		ShowError("Price must be greater than 0");
		return;
	}

	m_llPricePerUnit = llPrice;
	UpdatePreview();
}

// Step 4: Show preview before confirming
void CCashExchangeUI::UpdatePreview()
{
	SQUAD llTotal = m_llCashAmount * m_llPricePerUnit;

	// Update preview text
	sprintf(buffer, "Total Value: %I64d NAS", llTotal);
	m_pTxtPreview->SetString(buffer);
}

// Step 5: Send create listing message
void CCashExchangeUI::OnCreateListingClick()
{
	CNetMsg::SP msg(new CNetMsg);
	msg->InitSend(MSG_CASHEXCHANGE_CREATE_LISTING);

	RefMsg(msg) << m_pChar->m_index;           // Seller char index
	RefMsg(msg) << m_llCashAmount;             // Amount to list
	RefMsg(msg) << m_llPricePerUnit;           // Price per unit

	SEND_Q(msg, g_pDescManager->m_pConnDesc);

	CloseDialog();
}

// Step 6: Receive confirmation from server
void CCashExchangeUI::HandleCreateListingResult(CNetMsg::SP& msg)
{
	int success = 0;
	int errorCode = 0;

	RefMsg(msg) >> success >> errorCode;

	if (success)
	{
		SystemChat("Your cash listing has been created!");
		RequestListings();  // Refresh list
	}
	else
	{
		switch (errorCode)
		{
		case 1: SystemChat("Insufficient cash"); break;
		case 2: SystemChat("Invalid cash amount"); break;
		case 3: SystemChat("Invalid price"); break;
		default: SystemChat("Failed to create listing"); break;
		}
	}
}
```

## Message Flow Diagram

```
Client                                  Server
  │                                       │
  ├──────────────────────────────────────>│
  │  MSG_CASHEXCHANGE_OPEN                │
  │  (Request to view UI)                 │
  │                                       │
  │<──────────────────────────────────────┤
  │  MSG_CASHEXCHANGE_LISTING_LIST        │
  │  (All active listings)                │
  │                                       │
  ├──────────────────────────────────────>│
  │  MSG_CASHEXCHANGE_CREATE_LISTING      │
  │  (cash_amount, price_per_unit)        │
  │                                       │
  │<──────────────────────────────────────┤
  │  MSG_CASHEXCHANGE_CREATE_RESULT       │
  │  (success/failure)                    │
  │                                       │
  │ [Listing now visible to other        │
  │  players in their UI]                │
  │                                       │
  │ [Another player buys...]             │
  │                                       │
  │<──────────────────────────────────────┤
  │  MSG_CASHEXCHANGE_BUY_RESULT          │
  │  (notification of sale)               │
```

## Special Cases

### Case 1: Player Already Has Listing
- Option A: Allow unlimited listings
- Option B: Show "Max 5 listings" error
- Option C: Show existing listings, allow editing/replacement

### Case 2: Player Buys While Creating Listing
- Server validates cash amount at purchase time
- If concurrent operations: Use database locking or "optimistic" approach
- Show appropriate error if timing conflicts

### Case 3: Price Changes Dramatically
- No auto-adjustment - player must cancel and re-list
- Real-time prices not enforced by server
- Market-driven pricing model

### Case 4: Offline Players
- Listings persist while offline (seller can make sales while logged out)
- No notifications sent while offline (optional: send when logging in)
- Listing auto-expires after X days (optional safety feature)

## Localization Strings

```
STR_CASHEXCHANGE_OPEN          = "Cash Exchange"
STR_CASHEXCHANGE_LIST_CASH     = "List Cash for Sale"
STR_CASHEXCHANGE_VIEW_LISTINGS = "View Active Listings"
STR_CASHEXCHANGE_MY_LISTINGS   = "My Listings"
STR_CASHEXCHANGE_AMOUNT        = "Cash Amount:"
STR_CASHEXCHANGE_PRICE         = "Price per Unit (NAS):"
STR_CASHEXCHANGE_TOTAL         = "Total Value:"
STR_CASHEXCHANGE_BUY           = "Buy"
STR_CASHEXCHANGE_CONFIRM       = "Confirm Listing"
STR_CASHEXCHANGE_CANCEL        = "Cancel Listing"
STR_CASHEXCHANGE_ERROR_AMOUNT  = "Invalid cash amount"
STR_CASHEXCHANGE_ERROR_PRICE   = "Invalid price"
STR_CASHEXCHANGE_ERROR_BALANCE = "Insufficient cash"
STR_CASHEXCHANGE_SUCCESS       = "Cash listing created successfully!"
STR_CASHEXCHANGE_PURCHASED     = "You purchased cash from %s!"
STR_CASHEXCHANGE_SOLD          = "Your cash listing was sold to %s!"
```

## Integration with UI System

### In itemproduct.xml (or cash_exchange.xml)
```xml
<UIList id="listing_list" itemcount="0" itemshow_num="10">
  <UIListItem id="list_item_001">
	<UIText id="txt_seller" .../>       <!-- Seller name -->
	<UIText id="txt_amount" .../>       <!-- Cash amount -->
	<UIText id="txt_price" .../>        <!-- Price per unit -->
	<UIText id="txt_total" .../>        <!-- Total value -->
  </UIListItem>
</UIList>

<UIButton id="btn_list_cash" .../>      <!-- Open listing dialog -->
<UIButton id="btn_buy" .../>            <!-- Purchase button -->
```

## Testing Steps

1. **Player A Creates Listing**
   - Player A has 1,000,000 cash
   - Lists 500,000 at 50 NAS each
   - Should be deducted from inventory

2. **Player B Views Listings**
   - Player B opens cash exchange
   - Sees Player A's listing (500,000 @ 50 NAS)
   - Can see total value: 25,000,000 NAS

3. **Player B Purchases**
   - Buys 100,000 from Player A
   - Should receive 100,000 cash
   - Should pay 5,000,000 NAS

4. **Listing Updates**
   - Player A's listing now shows 400,000 remaining
   - Player B can see updated amount

5. **Player A Cancels**
   - Receives refund of 400,000 cash
   - Listing marked inactive
