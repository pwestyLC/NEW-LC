# CashExchangeUI Implementation Checklist

## ✅ Completed - Core Implementation

### Header File (CashExchangeUI.h)
- [x] Dialog state enum (CASH_DIALOG_NONE, AMOUNT, PRICE, CONFIRM, LOADING)
- [x] Message command constants (CE_MSGCMD_CASH_*)
- [x] CashListing struct definition
- [x] New method declarations:
  - [x] OnListCashClick()
  - [x] ShowCashAmountDialog()
  - [x] OnCashAmountInputConfirm()
  - [x] ShowPricePerUnitDialog()
  - [x] OnPricePerUnitInputConfirm()
  - [x] ShowConfirmationPreview()
  - [x] OnConfirmListingClick()
  - [x] SendCreateListingMessage()
  - [x] HandleCreateListingResult()
  - [x] MsgBoxCommand()
  - [x] ClearCashListingDialog()
  - [x] Validation helpers (ValidateCashAmount, ValidatePricePerUnit, ValidateOverflow)
  - [x] GetPlayerCashBalance()

### Implementation File (CashExchangeUI.cpp)
- [x] Constructor initialization with new fields
- [x] initialize() - Button binding for btn_list_cash and btn_buy
- [x] OnListCashClick() - Dialog state initialization
- [x] ShowCashAmountDialog() - Message preparation (TODO: UI wiring)
- [x] OnCashAmountInputConfirm() - Input parsing and validation
- [x] ShowPricePerUnitDialog() - Message preparation (TODO: UI wiring)
- [x] OnPricePerUnitInputConfirm() - Input parsing, validation, total calculation
- [x] ShowConfirmationPreview() - Confirmation message (TODO: UI wiring)
- [x] OnConfirmListingClick() - Confirm button handler
- [x] SendCreateListingMessage() - Network send preparation (TODO: API wiring)
- [x] HandleCreateListingResult() - Server response handler with error codes
- [x] MsgBoxCommand() - Message routing dispatcher
- [x] ClearCashListingDialog() - State and data cleanup
- [x] ValidateCashAmount() - Validates amount > 0 and ≤ player balance
- [x] ValidatePricePerUnit() - Validates price > 0
- [x] ValidateOverflow() - Prevents LONGLONG overflow
- [x] GetPlayerCashBalance() - Placeholder for player cash retrieval

### Features
- [x] State machine for multi-step dialog flow
- [x] Input validation at each step
- [x] Error handling and recovery
- [x] Total value preview before confirmation
- [x] Listing display integration (AddListing works)
- [x] Button click handlers wired
- [x] Message command routing

### Build Status
- [x] Compiles without errors
- [x] No unresolved symbols (in CashExchangeUI files)
- [x] Integrates with existing UI framework

---

## ⚠️ Placeholders - Awaiting Engine Integration

### 1. Player Cash Retrieval
- **Function**: `GetPlayerCashBalance()`
- **Current Status**: Returns 0 (placeholder)
- **Requires**: Connection to MyInfo, g_pPlayer, or character cash data
- **Priority**: HIGH - Needed for dialog display
- **Difficulty**: EASY

### 2. Message Box UI Integration
- **Functions**: 
  - `ShowCashAmountDialog()` - Numeric input dialog
  - `ShowPricePerUnitDialog()` - Numeric input dialog  
  - `ShowConfirmationPreview()` - Yes/No confirmation dialog
- **Current Status**: Message text built, but dialogs not displayed
- **Requires**: UIMsgBoxNumericOnly, MSGBOXMGR integration, Command binding
- **Priority**: HIGH - Core user interaction
- **Difficulty**: MEDIUM

### 3. Character Index Retrieval
- **Function**: `SendCreateListingMessage()`
- **Current Status**: `nCharIndex = 0` (placeholder)
- **Requires**: MY_INFO().GetCharIndex() or equivalent
- **Priority**: HIGH - Needed for server message
- **Difficulty**: EASY

### 4. Network Message Send
- **Function**: `SendCreateListingMessage()`
- **Current Status**: CNetMsg creation fully commented out
- **Requires**: CNetMsg class, MSG_CASHEXCHANGE_CREATE_LISTING ID, SEND_Q macro
- **Priority**: HIGH - Core server communication
- **Difficulty**: MEDIUM

### 5. Message Dispatcher Hook
- **Function**: `HandleCreateListingResult()`
- **Current Status**: Implementation ready, needs dispatcher routing
- **Requires**: Add MSG_CASHEXCHANGE_CREATE_LISTING_RESULT to message dispatcher
- **Priority**: MEDIUM - Needed for server responses
- **Difficulty**: EASY

---

## 📋 Integration Order Recommendation

1. **GetPlayerCashBalance()** - Show current balance in first dialog
2. **Message Box Dialogs** - Get user input for amount and price
3. **Character Index** - Prepare server message
4. **Network Send** - Send listing creation request
5. **Message Dispatcher** - Handle server response
6. **End-to-end Testing** - Verify complete flow

---

## 🧪 Testing Points

- [ ] Dialog displays correct player cash balance
- [ ] Numeric input validates and rejects invalid amounts
- [ ] Calculation shows correct total value
- [ ] Confirmation dialog displays final values
- [ ] Network message sends without errors
- [ ] Server response triggers correct handler
- [ ] Listing appears in exchange after creation
- [ ] Error cases show appropriate messages

---

## 📚 Reference Documentation

- [INTEGRATION_GUIDE.md](./INTEGRATION_GUIDE.md) - Detailed integration instructions
- [COMPLETION_SUMMARY.md](./COMPLETION_SUMMARY.md) - High-level status overview
- [CASHEXCHANGE_IMPLEMENTATION_GUIDE.md](./CASHEXCHANGE_IMPLEMENTATION_GUIDE.md) - Architecture details
- [PersonalshopUI.h/cpp](../Base/PersonalshopUI.h) - Reference implementation
- [itemproduct.xml](../../../Data/Interface/xml/itemproduct.xml) - UI layout (preferred)

---

## 📌 Key Files

- **Header**: `..\dx9\Client\Engine\Contents\function\CashExchangeUI.h`
- **Implementation**: `..\dx9\Client\Engine\Contents\function\CashExchangeUI.cpp`
- **Reference**: `..\dx9\Client\Engine\Contents\Base\PersonalshopUI.h`
- **UI Layout**: `itemproduct.xml` (reused, not custom)

---

**Last Updated**: This session
**Build Status**: ✅ Successful
**Completion**: ~80% (structure complete, API integration pending)
