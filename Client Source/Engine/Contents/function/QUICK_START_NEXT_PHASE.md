# CashExchangeUI - Quick Start for Next Phase

## You Are Here

The CashExchangeUI client implementation is **complete and compilable**. You now need to integrate it with the game engine's actual APIs.

## What's Ready to Use

✅ **CashExchangeUI.h** - All declarations complete
✅ **CashExchangeUI.cpp** - All methods implemented with placeholders
✅ **Build** - Compiles successfully with no errors

## What Needs Wiring

### 1. [EASIEST] Get Player Cash Balance (10 minutes)

**File**: `CashExchangeUI.cpp`
**Function**: `GetPlayerCashBalance()`
**Line**: ~470 (search for "TODO: Get actual character index")

**Currently**:
```cpp
LONGLONG CCashExchangeUI::GetPlayerCashBalance() const
{
	// ... comments ...
	return 0;  // ← REPLACE THIS LINE
}
```

**Your task**: Find where player cash is stored and return it. Examples:
```cpp
// If using MyInfo singleton:
return MY_INFO().GetCash();

// If using global player:
return g_pPlayer->m_llCash;

// If using character info:
return pCharInfo->m_cash;
```

**Test**: The first cash listing dialog should show your player's current cash.

---

### 2. [EASY] Get Character Index (10 minutes)

**File**: `CashExchangeUI.cpp`
**Function**: `SendCreateListingMessage()`
**Line**: ~330 (search for "int nCharIndex = 0;")

**Currently**:
```cpp
int nCharIndex = 0;  // ← REPLACE THIS LINE
```

**Your task**: Get your character's index:
```cpp
// Option 1:
int nCharIndex = MY_INFO().GetCharIndex();

// Option 2:
int nCharIndex = g_pPlayer->m_index;

// Option 3:
int nCharIndex = GetPlayerCharacter()->m_nIndex;
```

**Test**: The character index should be non-zero when sending messages.

---

### 3. [MEDIUM] Wire Message Box Dialogs (30-45 minutes)

**File**: `CashExchangeUI.cpp`
**Functions**:
- `ShowCashAmountDialog()` (~line 200)
- `ShowPricePerUnitDialog()` (~line 240)
- `ShowConfirmationPreview()` (~line 270)

**Currently**: Each function builds a message but doesn't show the dialog.

**Pattern from PersonalshopUI.cpp**: (Find and study how PersonalshopUI uses message boxes)

**Example integration for ShowCashAmountDialog()**:
```cpp
void CCashExchangeUI::ShowCashAmountDialog()
{
	LONGLONG llBalance = GetPlayerCashBalance();
	CTString strMessage;
	strMessage.PrintF("Your current cash: %I64d\n\nHow much cash to list?", llBalance);

	// TODO: Show the numeric input dialog
	// Use UIMsgBoxNumericOnly or similar
	// On OK, call: OnCashAmountInputConfirm(inputValue);
	// On Cancel, call: ClearCashListingDialog();
}
```

**References**:
- PersonalshopUI.h - See how it declares message box callbacks
- PersonalshopUI.cpp - See how it shows/manages dialogs
- UIMsgBoxNumeric_only.h - API for numeric input dialog
- UIMsgBoxMgr.h - Macro: `MSGBOXMGR()` to get message box manager

**Test**: Clicking "List Cash" should show the first input dialog.

---

### 4. [MEDIUM] Wire Network Send (30 minutes)

**File**: `CashExchangeUI.cpp`
**Function**: `SendCreateListingMessage()`
**Location**: After the `nCharIndex` retrieval

**Currently**: All network code is commented out.

**Your task**: Uncomment and adapt this:
```cpp
CNetMsg::SP msg(new CNetMsg);
msg->InitSend(MSG_CASHEXCHANGE_CREATE_LISTING);
msg->AddMsg((SQUAD)nCharIndex);
msg->AddMsg(m_llCashAmount);
msg->AddMsg(m_llPricePerUnit);
SEND_Q(msg, g_pDescManager->m_pConnDesc);
```

**Prerequisites**:
- Define `MSG_CASHEXCHANGE_CREATE_LISTING` message ID
  - Location: Network/MessageDefine.h or similar
  - Value: Choose an unused message ID
- Ensure CNetMsg class is available
- Ensure SEND_Q macro is available

**References**:
- NetworkMessage.h - CNetMsg class definition
- MessageDefine.h - Where to add MSG_CASHEXCHANGE_CREATE_LISTING
- SessionState*.cpp - Examples of sending network messages
- Comparable message sends in the codebase

**Test**: Server should receive the listing creation request. Add logging to verify.

---

### 5. [EASY] Hook Server Response Handler (15 minutes)

**File**: `CashExchangeUI.cpp`
**Function**: `HandleCreateListingResult(int nSuccess, int nErrorCode)`

**Currently**: Function is implemented but not called from message dispatcher.

**Your task**: 
1. Add a new message handler for `MSG_CASHEXCHANGE_CREATE_LISTING_RESULT`
2. Route it to call `HandleCreateListingResult()`

**Location**: Usually in Network/MessageDispatcher.cpp or similar

**Pattern**:
```cpp
// In the message dispatcher:
case MSG_CASHEXCHANGE_CREATE_LISTING_RESULT:
	{
		SQUAD nSuccess;
		SQUAD nErrorCode;
		// Extract from message
		pUI->HandleCreateListingResult(nSuccess, nErrorCode);
	}
	break;
```

**Error codes handled by HandleCreateListingResult()**:
- 0 = Success
- 1 = Insufficient cash
- 2 = Invalid price
- 3 = Server error
- 4 = Unknown error

**Test**: Server response should properly update UI state.

---

## Testing Checklist

Before considering this complete, verify:

- [ ] First dialog shows your correct cash balance
- [ ] Can enter valid cash amount, dialog advances
- [ ] Can enter valid price, dialog advances
- [ ] Confirmation dialog shows correct total (amount × price)
- [ ] Clicking confirm sends a network message
- [ ] Server response appears in client
- [ ] Success shows confirmation message
- [ ] Error codes show appropriate messages
- [ ] UI resets after success or cancel

---

## Documentation to Review

1. **INTEGRATION_GUIDE.md** - Detailed templates for each integration point
2. **COMPLETION_SUMMARY.md** - Status and architecture overview
3. **IMPLEMENTATION_CHECKLIST.md** - Detailed checklist of all work
4. **ARCHITECTURE_DIAGRAMS.md** - Visual flow diagrams

---

## Key Files You'll Edit

1. `..\dx9\Client\Engine\Contents\function\CashExchangeUI.cpp` - Main edits
2. `Network/MessageDefine.h` - Add MSG_CASHEXCHANGE_CREATE_LISTING
3. `Network/MessageDispatcher.cpp` - Add message routing
4. Possibly: `PersonalshopUI.cpp` - Reference for patterns

---

## Estimated Time

- GetPlayerCashBalance: **10 min**
- Character Index: **10 min**
- Message Boxes: **45 min**
- Network Send: **30 min**
- Message Response: **15 min**
- **Total: ~2 hours**

---

## Build Command

```powershell
# From your workspace directory
msbuild ..\dx9\Client\Engine\Engine_2010.vcxproj /p:Configuration=Release
```

Current status: ✅ Builds successfully

---

## Git Workflow

```bash
# Check status
git status

# See what changed in CashExchangeUI
git diff ..\dx9\Client\Engine\Contents\function\CashExchangeUI.cpp

# When you're ready to commit your integration work:
git add ..\dx9\Client\Engine\Contents\function\CashExchangeUI.cpp
git add Network/MessageDefine.h
git add Network/MessageDispatcher.cpp
git commit -m "Integrate CashExchangeUI with game engine APIs"
```

---

## Common Issues & Solutions

**Issue**: "MSGMGR not found"
- **Solution**: Use `MSGBOXMGR()` macro instead (it's defined in UIMsgBoxMgr.h)

**Issue**: "MY_INFO() undefined"
- **Solution**: Add `#include <Engine/Info/MyInfo.h>` if needed

**Issue**: "CNetMsg not defined"
- **Solution**: Add `#include <Engine/Network/NetworkMessage.h>` or similar

**Issue**: "Message doesn't reach server"
- **Solution**: Verify MSG_CASHEXCHANGE_CREATE_LISTING value is unique and correct
- Check that SEND_Q actually queues the message

**Issue**: "OnCashAmountInputConfirm not called"
- **Solution**: Ensure the message box Command properly binds to this function
- Check the boost::bind syntax matches the pattern in PersonalshopUI

---

## Next Developer Note

This implementation follows the **PersonalshopUI pattern** because:
1. PersonalshopUI already has cash listing functionality
2. You wanted to reuse itemproduct.xml (not create custom XML)
3. The validation rules and data structures align

Use PersonalshopUI as your primary reference - it's the proven pattern in this codebase.

---

**Status**: Ready for API integration
**Difficulty**: Straightforward, well-structured codebase  
**Time Estimate**: 2 hours to complete

Good luck! 🚀
