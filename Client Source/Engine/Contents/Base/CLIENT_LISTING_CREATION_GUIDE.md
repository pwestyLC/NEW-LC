# How Players Create Cash Listings - Client-Side Details

## Quick Answer

**To add a cash listing on the client side:**

1. **NPC Interaction** → Opens cash exchange window
2. **Click "List Cash" button** → Opens input dialog
3. **Enter cash amount** → E.g., "500000"
4. **Enter price per unit** → E.g., "50" (NAS per cash)
5. **Confirm** → Message sent to server
6. **Wait for response** → Server processes and confirms
7. **Listing created** → Appears for other players

## Detailed Flow: Step-by-Step

### Step 1: NPC Opens Cash Exchange Window

**Trigger:** Player talks to Cash Exchange NPC

```cpp
// In NPC dialog handler or interaction system
void OnCashExchangeNPCClick()
{
	// Open the cash exchange UI window
	g_pCashExchangeUI->OpenUI();

	// Send request for current listings
	g_pCashExchangeUI->RequestListings();
}
```

**UI appears showing:**
- List of active cash listings from other sellers
- Seller names, amounts, prices
- [Buy] [List Cash] buttons

### Step 2: Player Clicks "List Cash" Button

**UI Element:**
```xml
<UIButton id="btn_list_cash" x="..." y="..." text="List Cash">
```

**Handler:**
```cpp
void CCashExchangeUI::OnListCashClick()
{
	// Show dialog for entering cash amount
	ShowCashAmountDialog();
}
```

### Step 3: Cash Amount Input Dialog

**What appears:**
```
┌──────────────────────────────┐
│ List Cash for Sale           │
├──────────────────────────────┤
│ Your current cash: 5,000,000 │
│                              │
│ How much cash to list?       │
│ ┌────────────────────────┐   │
│ │ [Enter amount]         │   │
│ └────────────────────────┘   │
│                              │
│ [OK] [Cancel]                │
└──────────────────────────────┘
```

**Validation on client side:**
```cpp
void CCashExchangeUI::HandleCashAmountInput(const char* strInput)
{
	// Parse input
	LONGLONG llAmount = _atoi64(strInput);

	// Validate
	if (llAmount <= 0)
	{
		ShowError("Cash amount must be greater than 0");
		return;
	}

	if (llAmount > GetPlayerCashBalance())
	{
		ShowError("You don't have enough cash");
		return;
	}

	// Store for next step
	m_llCashAmount = llAmount;

	// Move to price input
	ShowPricePerUnitDialog();
}

LONGLONG CCashExchangeUI::GetPlayerCashBalance()
{
	// Return player's current cash
	// This depends on your character class
	// Example: return g_pPlayer->m_llCash;
	return m_pPlayer->GetCash();
}
```

### Step 4: Price Per Unit Input Dialog

**What appears:**
```
┌──────────────────────────────┐
│ Set Price Per Unit           │
├──────────────────────────────┤
│ Listing amount: 500,000 cash │
│                              │
│ Price per unit (NAS)?        │
│ ┌────────────────────────┐   │
│ │ [Enter price]          │   │
│ └────────────────────────┘   │
│                              │
│ Preview:                     │
│ Total value: 0 NAS           │
│                              │
│ [Confirm] [Cancel]           │
└──────────────────────────────┘
```

**Validation on client side:**
```cpp
void CCashExchangeUI::HandlePricePerUnitInput(const char* strInput)
{
	// Parse input
	LONGLONG llPrice = _atoi64(strInput);

	// Validate
	if (llPrice <= 0)
	{
		ShowError("Price must be greater than 0");
		return;
	}

	// Check for overflow (total price = amount × price)
	if (m_llCashAmount > LLONG_MAX / llPrice)
	{
		ShowError("Total price too high");
		return;
	}

	LONGLONG llTotalValue = m_llCashAmount * llPrice;

	// Store
	m_llPricePerUnit = llPrice;

	// Update preview
	char buffer[256];
	sprintf_s(buffer, "Total value: %I64d NAS", llTotalValue);
	m_pTxtPreview->SetString(buffer);

	// Show confirm button
	m_pBtnConfirm->Enable();
}
```

### Step 5: Confirm Listing Creation

**What player sees:**
```
Final confirmation:
- Amount: 500,000 cash
- Price: 50 NAS each
- Total: 25,000,000 NAS

[Create Listing] [Cancel]
```

**On confirm click:**
```cpp
void CCashExchangeUI::OnConfirmListingClick()
{
	// Create and send message to server
	SendCreateListingMessage(m_llCashAmount, m_llPricePerUnit);
}

void CCashExchangeUI::SendCreateListingMessage(LONGLONG llAmount, LONGLONG llPrice)
{
	// Build message
	CNetMsg::SP msg(new CNetMsg);
	msg->InitSend(MSG_CASHEXCHANGE_CREATE_LISTING);

	// Add data
	RefMsg(msg) << m_pPlayer->m_index;  // Player's character index
	RefMsg(msg) << llAmount;             // Cash amount
	RefMsg(msg) << llPrice;              // Price per unit

	// Send to server
	SEND_Q(msg, g_pDescManager->m_pConnDesc);

	// Show loading indicator
	ShowLoadingMessage("Creating listing...");
}
```

**Message sent to server:**
```
MSG_CASHEXCHANGE_CREATE_LISTING
├─ char_index: 12345 (player's character)
├─ cash_amount: 500000
└─ price_per_unit: 50
```

### Step 6: Wait for Server Response

**Server processes the message:**
1. Validates cash amount and price
2. Checks player has enough cash
3. Deducts cash from player's account
4. Inserts into database table t_cash_exchange_listings
5. Sends response back

**Time:** Usually < 1 second

### Step 7: Receive Confirmation Response

**Server sends back:**
```
MSG_CASHEXCHANGE_CREATE_RESULT
├─ success: 1 (or 0 for failure)
└─ error_code: 0 (or error code if failed)
```

**Client receives and handles:**
```cpp
void CCashExchangeUI::HandleCreateListingResult(CNetMsg::SP& msg)
{
	int success = 0;
	int errorCode = 0;

	RefMsg(msg) >> success >> errorCode;

	HideLoadingMessage();

	if (success)
	{
		// Success!
		SystemChat("Cash listing created successfully!");

		// Clear the input fields
		ClearDialog();

		// Refresh the listings display
		RequestListings();

		// Close dialog automatically
		m_eDialogState = DIALOG_CLOSED;
	}
	else
	{
		// Handle errors
		const char* pszError = NULL;

		switch (errorCode)
		{
		case 1:
			pszError = "Insufficient cash to create listing";
			break;
		case 2:
			pszError = "Cash amount must be greater than 0";
			break;
		case 3:
			pszError = "Price per unit must be greater than 0";
			break;
		default:
			pszError = "Failed to create listing";
			break;
		}

		SystemChat(pszError);
		// Dialog stays open so player can retry
	}
}
```

## What Happens After Listing Created

### For the Seller:
1. Cash is **deducted from their account**
2. Amount appears in a database entry
3. Listing is marked as **active**
4. They can see it in their "My Listings" view
5. They can cancel it anytime to get cash back

### For Other Players:
1. Listing appears in their **cash exchange UI** (next time they open it or on refresh)
2. Shows:
   - Seller's character name
   - 500,000 cash available
   - 50 NAS per unit
   - Total value: 25,000,000 NAS
3. They can click to buy some/all of it

### For the Database:
```sql
INSERT INTO t_cash_exchange_listings (
	seller_user_code,
	seller_char_name,
	seller_char_index,
	cash_amount,
	price_per_unit,
	total_price,
	is_active
) VALUES (
	123,              -- seller's user code
	'PlayerName',     -- seller's character name
	12345,            -- seller's character index
	500000,           -- cash amount
	50,               -- price per unit (NAS)
	25000000,         -- total (500k * 50)
	1                 -- active
);
```

## Code Template: Complete Client-Side Handler

```cpp
// CashExchangeUI.cpp

class CCashExchangeUI : public CUIWindow
{
private:
	enum DialogState {
		DIALOG_CLOSED,
		DIALOG_AMOUNT_INPUT,
		DIALOG_PRICE_INPUT,
		DIALOG_CONFIRM,
		DIALOG_LOADING
	};

	DialogState m_eDialogState;
	LONGLONG m_llCashAmount;
	LONGLONG m_llPricePerUnit;

public:
	// Entry point: Player clicks "List Cash"
	void OnListCashButtonClick()
	{
		m_eDialogState = DIALOG_AMOUNT_INPUT;
		ShowDialog("How much cash to list?");
	}

	// Step 1: Get amount
	void OnAmountInputOK(const char* strAmount)
	{
		LONGLONG llAmount = _atoi64(strAmount);

		// Validate
		if (llAmount <= 0) {
			SystemChat("Invalid amount");
			return;
		}
		if (llAmount > GetPlayerCash()) {
			SystemChat("Not enough cash");
			return;
		}

		m_llCashAmount = llAmount;

		// Move to price step
		m_eDialogState = DIALOG_PRICE_INPUT;
		ShowDialog("Price per cash unit?");
	}

	// Step 2: Get price
	void OnPriceInputOK(const char* strPrice)
	{
		LONGLONG llPrice = _atoi64(strPrice);

		// Validate
		if (llPrice <= 0) {
			SystemChat("Invalid price");
			return;
		}

		m_llPricePerUnit = llPrice;

		// Show confirmation
		m_eDialogState = DIALOG_CONFIRM;
		ShowConfirmDialog(m_llCashAmount, m_llPricePerUnit);
	}

	// Step 3: Confirm and send to server
	void OnConfirmClick()
	{
		SendCreateListingMessage();
	}

	void SendCreateListingMessage()
	{
		CNetMsg::SP msg(new CNetMsg);
		msg->InitSend(MSG_CASHEXCHANGE_CREATE_LISTING);

		RefMsg(msg) << m_pPlayer->m_index;
		RefMsg(msg) << m_llCashAmount;
		RefMsg(msg) << m_llPricePerUnit;

		SEND_Q(msg, g_pDescManager->m_pConnDesc);

		m_eDialogState = DIALOG_LOADING;
		ShowLoadingMessage();
	}

	// Step 4: Receive and handle response
	void HandleCreateListingResult(CNetMsg::SP& msg)
	{
		int success = 0;
		RefMsg(msg) >> success;

		if (success)
		{
			SystemChat("Listing created!");
			ClearDialog();
			RequestListings();  // Refresh
		}
		else
		{
			SystemChat("Failed to create listing");
		}

		m_eDialogState = DIALOG_CLOSED;
	}
};
```

## UI XML Reference

The UI should reuse **itemproduct.xml** structure:

```xml
<!-- Main window -->
<Window id="CashExchangeUI">
	<!-- Listings area (left side) -->
	<UIList id="listing_list">
		<!-- Each item shows: seller, amount, price, total -->
	</UIList>

	<!-- Buttons -->
	<UIButton id="btn_list_cash" text="List Cash"/>
	<UIButton id="btn_buy" text="Buy"/>
	<UIButton id="btn_refresh" text="Refresh"/>

	<!-- Input dialog (hidden by default) -->
	<UIEditBox id="edit_amount" visible="false"/>
	<UIEditBox id="edit_price" visible="false"/>
	<UIText id="txt_preview" visible="false"/>
	<UIButton id="btn_confirm" visible="false"/>
</Window>
```

## Summary

**Creating a cash listing involves:**

1. Player opens NPC → Opens UI
2. Player clicks "List Cash" → Amount dialog appears
3. Player enters amount → Validates locally
4. Player enters price → Shows preview
5. Player confirms → Message sent to server
6. Server validates → Deducts cash, inserts listing
7. Server responds → Success/error
8. Client refreshes listings → Listing appears for others

**All input is validated twice:**
- **Client-side:** For user feedback and UX
- **Server-side:** For actual enforcement and security

This ensures a smooth user experience while maintaining security and data integrity.
