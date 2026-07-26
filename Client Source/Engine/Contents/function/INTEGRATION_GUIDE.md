# Cash Exchange UI - Integration Guide

## Overview
The `CashExchangeUI` implementation is structurally complete and compiles successfully. This guide documents the remaining integration work needed to wire up the placeholder implementations with actual game engine APIs.

## Current Status
- ✅ CashExchangeUI.h/.cpp fully implemented with dialog state machine
- ✅ Listing display logic (AddListing, ClearListings, SelectListing)
- ✅ Cash listing creation workflow (dialog states and validation)
- ✅ Build successful - no compilation errors
- ⚠️ Placeholder implementations requiring engine integration (see below)

## Integration Points (TODO)

### 1. Player Cash Balance Retrieval
**File**: `..\dx9\Client\Engine\Contents\function\CashExchangeUI.cpp`
**Function**: `GetPlayerCashBalance()`
**Current**: Returns `0` (placeholder)

**Integration**:
```cpp
LONGLONG CCashExchangeUI::GetPlayerCashBalance() const
{
	// Option 1: Use MyInfo singleton
	// if (MY_INFO().IsValid())
	//     return MY_INFO().GetCash();  // or similar accessor

	// Option 2: Use global player object
	// if (g_pPlayer != NULL)
	//     return g_pPlayer->GetCash();

	// Option 3: Use player character info
	// CPlayerCharacter* pPC = GetPlayerCharacter();
	// if (pPC != NULL)
	//     return pPC->m_llCash;

	// Add your actual implementation here
	return 0;
}
```

**Reference**: Check `PersonalshopUI.h` for the pattern used in the existing cash listing system (line: `SQUAD GetPlayerCashBalance() const;`)

---

### 2. Message Box Integration (3 methods)

#### A. ShowCashAmountDialog()
**File**: `..\dx9\Client\Engine\Contents\function\CashExchangeUI.cpp`
**Current**: Builds message but doesn't show dialog

**Integration**:
```cpp
void CCashExchangeUI::ShowCashAmountDialog()
{
	// Build the message
	LONGLONG llBalance = GetPlayerCashBalance();
	CTString strMessage;
	strMessage.PrintF("Your current cash: %I64d\n\nHow much cash to list?", llBalance);

	// Show the numeric input dialog
	// Pattern: Use UIMsgBoxNumericOnly or similar message box component
	// The dialog should call OnCashAmountInputConfirm() when OK is clicked

	// Example (adapt to your actual message box API):
	// CUIMsgBoxNumericOnly* pBox = /* Get message box instance */;
	// if (pBox)
	// {
	//     Command* pCmd = new boost::bind(&CCashExchangeUI::OnCashAmountInputConfirm, this, _1);
	//     pBox->SetInfo(pCmd, "List Cash", strMessage, 1, llBalance);
	//     pBox->Show();
	// }
}
```

#### B. ShowPricePerUnitDialog()
**Similar pattern**: Show numeric input dialog for price per unit
**Callback**: `OnPricePerUnitInputConfirm(const CTString& strInput)`

#### C. ShowConfirmationPreview()
**Pattern**: Show Yes/No confirmation dialog
**Callbacks**: 
- Yes → `OnConfirmListingClick()`
- No → `ClearCashListingDialog()`

**Reference**: Check how `PersonalshopUI.cpp` uses message boxes for cash listing confirmations.

---

### 3. Player Character Index Retrieval
**File**: `..\dx9\Client\Engine\Contents\function\CashExchangeUI.cpp`
**Function**: `SendCreateListingMessage()`
**Current**: `nCharIndex = 0` (placeholder)

**Integration**:
```cpp
// Replace line in SendCreateListingMessage():
// int nCharIndex = 0;  // PLACEHOLDER

// With one of:
// Option 1: From MyInfo singleton
int nCharIndex = MY_INFO().GetCharIndex();

// Option 2: From global player pointer
int nCharIndex = g_pPlayer->m_index;

// Option 3: From player character
int nCharIndex = GetPlayerCharacter()->m_nIndex;
```

**Reference**: Check `MyInfo.h` for character data accessors

---

### 4. Network Message Send
**File**: `..\dx9\Client\Engine\Contents\function\CashExchangeUI.cpp`
**Function**: `SendCreateListingMessage()`
**Current**: Fully commented out network send

**Integration**:
Replace the commented code section with:

```cpp
void CCashExchangeUI::SendCreateListingMessage()
{
	// Step 1: Get player character index
	int nCharIndex = 0;  // Use integration point #3 above

	// Step 2: Validate data before sending
	if (m_llCashAmount <= 0 || m_llPricePerUnit <= 0)
	{
		// Show error dialog
		return;
	}

	try
	{
		// Step 3: Create network message
		// Message ID: MSG_CASHEXCHANGE_CREATE_LISTING (define this in your message IDs header)
		CNetMsg::SP msg(new CNetMsg);
		if (msg == NULL) 
			throw std::exception("Failed to allocate network message");

		// Step 4: Initialize message
		msg->InitSend(MSG_CASHEXCHANGE_CREATE_LISTING);

		// Step 5: Add parameters
		msg->AddMsg((SQUAD)nCharIndex);      // Character index
		msg->AddMsg(m_llCashAmount);         // Cash amount (LONGLONG)
		msg->AddMsg(m_llPricePerUnit);       // Price per unit (LONGLONG)

		// Step 6: Send to server
		SEND_Q(msg, g_pDescManager->m_pConnDesc);

		// Step 7: Clear dialog and reset state
		ClearCashListingDialog();

		// Optional: Show "Sending..." dialog or feedback
	}
	catch (const std::exception& e)
	{
		// Log error and notify user
		ClearCashListingDialog();
	}
}
```

**Required Definitions**:
- `MSG_CASHEXCHANGE_CREATE_LISTING` - Message ID (add to `MessageDefine.h`)
- `CNetMsg` - Network message class
- `SEND_Q` - Message queue macro
- `g_pDescManager` - Connection descriptor manager

---

### 5. Server Response Handler
**File**: `..\dx9\Client\Engine\Contents\function\CashExchangeUI.cpp`
**Function**: `HandleCreateListingResult(int nSuccess, int nErrorCode)`
**Current**: Partial implementation with error codes

**Integration**:
- Hook this function to be called when the server response arrives
- Add to message dispatcher to route `MSG_CASHEXCHANGE_CREATE_LISTING_RESULT` to this handler
- Error codes are already mapped (1-4):
  - Code 1: Insufficient cash
  - Code 2: Invalid price
  - Code 3: Server error
  - Code 4: Unknown error

**Reference**: Check `MessageDispatcher.cpp` for pattern of routing server messages to UI callbacks

---

## Validation Rules (Already Implemented)

✅ `ValidateCashAmount(LONGLONG llAmount)` - Checks amount is > 0 and ≤ player balance
✅ `ValidatePricePerUnit(LONGLONG llPrice)` - Checks price is > 0
✅ `ValidateOverflow(LONGLONG a, LONGLONG b)` - Checks for multiplication overflow

---

## Dialog State Machine (Already Implemented)

The state machine is fully implemented in the enum:
```cpp
enum eCashDialogState {
	CASH_DIALOG_NONE,        // No dialog active
	CASH_DIALOG_AMOUNT,      // Waiting for cash amount input
	CASH_DIALOG_PRICE,       // Waiting for price per unit input
	CASH_DIALOG_CONFIRM,     // Waiting for confirmation
	CASH_DIALOG_LOADING,     // Waiting for server response
};
```

**Flow**: 
1. User clicks "List Cash" button
2. OnListCashClick() → State = CASH_DIALOG_AMOUNT
3. ShowCashAmountDialog() displays input
4. OnCashAmountInputConfirm() validates → State = CASH_DIALOG_PRICE
5. ShowPricePerUnitDialog() displays input
6. OnPricePerUnitInputConfirm() validates → State = CASH_DIALOG_CONFIRM
7. ShowConfirmationPreview() displays confirmation
8. OnConfirmListingClick() → SendCreateListingMessage() → State = CASH_DIALOG_LOADING
9. HandleCreateListingResult() processes server response

---

## Recommended Integration Order

1. **First**: Implement `GetPlayerCashBalance()` - Simplest, no UI dependency
2. **Second**: Implement player character index retrieval in `SendCreateListingMessage()`
3. **Third**: Implement message box dialogs (ShowCashAmountDialog, etc.)
4. **Fourth**: Add network message send with proper `CNetMsg` API
5. **Fifth**: Hook message dispatcher to handle server responses
6. **Last**: Test end-to-end cash listing creation flow

---

## Files Modified in This Session

- `..\dx9\Client\Engine\Contents\function\CashExchangeUI.h` - Added dialog state constants and new method declarations
- `..\dx9\Client\Engine\Contents\function\CashExchangeUI.cpp` - Implemented full cash listing creation workflow
- Added documentation files (this file, IMPLEMENTATION_SUMMARY.md, etc.)

---

## Testing Checklist

When integration is complete:
- [ ] GetPlayerCashBalance() returns correct value
- [ ] Numeric input dialogs appear and accept input
- [ ] Confirmation dialog shows correct totals
- [ ] Network message sends successfully
- [ ] Server response triggers HandleCreateListingResult()
- [ ] Listings refresh after successful creation
- [ ] Error messages display for validation failures
- [ ] UI state resets properly after success or cancellation

---

## Reference Patterns

- **Message Box System**: PersonalshopUI.cpp (cash listing implementation)
- **Network Messages**: SessionState*.cpp files in Network folder
- **Message Dispatcher**: Network/MessageDispatcher.cpp
- **Player Data Access**: MyInfo.h, PlayerCharacter.h
- **Listing Display**: ItemProductUI.cpp (for itemproduct.xml pattern)

