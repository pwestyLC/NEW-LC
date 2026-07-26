# Cash Exchange UI - Architecture & Flow Diagram

## System Architecture

```
┌─────────────────────────────────────────────────────────────────────┐
│                         CASH EXCHANGE UI                            │
│                    (CashExchangeUI.cpp/.h)                          │
└─────────────────────────────────────────────────────────────────────┘
								   │
					┌──────────────┼──────────────┐
					│              │              │
		┌───────────▼──────┐  ┌────▼─────┐  ┌───▼──────────┐
		│ Dialog System    │  │ Validation│  │ Network      │
		│ (Message Boxes)  │  │ Helpers   │  │ (CNetMsg)    │
		└──────────────────┘  └──────────┘  └──────────────┘
					│              │              │
					└──────────────┼──────────────┘
								   │
					┌──────────────▼──────────────┐
					│  State Machine (5 states)  │
					│  - NONE                    │
					│  - AMOUNT                  │
					│  - PRICE                   │
					│  - CONFIRM                 │
					│  - LOADING                 │
					└──────────────┬──────────────┘
								   │
					┌──────────────┴──────────────┐
					│                             │
		┌───────────▼──────┐        ┌────────────▼────┐
		│ Player Balance   │        │ Server Response │
		│ (Game Engine)    │        │ Message Handler │
		└──────────────────┘        └─────────────────┘
```

## Message Flow Diagram

```
PLAYER                    CLIENT UI                    SERVER
  │                          │                            │
  ├─ Click "List Cash" ─────→│                            │
  │                          │                            │
  │                    [STATE: AMOUNT]                    │
  │                          │                            │
  │← Show Dialog ────────────│                            │
  │                          │                            │
  ├─ Enter 500000 ──────────→│                            │
  │                          │ Validate                   │
  │                    [STATE: PRICE]                     │
  │                          │                            │
  │← Show Dialog ────────────│                            │
  │                          │                            │
  ├─ Enter 50 ──────────────→│                            │
  │                          │ Validate + Overflow Check  │
  │                    [STATE: CONFIRM]                   │
  │                          │                            │
  │← Show Preview ──────────│                            │
  │  (500000, 50, 25M)       │                            │
  │                          │                            │
  ├─ Click Confirm ─────────→│                            │
  │                          │ Create MSG_CASHEXCHANGE   │
  │                    [STATE: LOADING]                   │
  │                          │                            │
  │                          ├─ Send Message ────────────→│
  │                          │                            │ Validate
  │                          │                            │ Deduct Cash
  │                          │                            │ Insert DB
  │                          │                            │
  │                          │←─ Send Response ──────────│
  │                          │   (success=1)              │
  │                          │                            │
  │← Show Success ────────────│                            │
  │  "Listing Created!"       │ [STATE: NONE]             │
  │
```

## State Machine Diagram

```
					┌─────────────┐
					│   START     │
					└──────┬──────┘
						   │
					[User clicks List Cash]
						   │
					┌──────▼──────┐
			┌──────→│  AMOUNT     │◄─────┐ [Invalid]
			│       └──────┬──────┘      │
			│              │             │
	   [Retry]      [User enters amount] │
			│              │ [Valid]     │
			│              │             │
			│       ┌──────▼──────┐      │
	   ┌────┴──────→│    PRICE    │◄────┤ [Invalid]
	   │            └──────┬──────┘      │
	   │  [Invalid]        │ [Valid]     │
	   │                   │             │
	   │            ┌──────▼──────┐      │
	   │   ┌───────→│   CONFIRM   │◄────┘ [Retry]
	   │   │        └──────┬──────┘
	   │   │ [Cancel]      │ [Confirm]
	   │   │ [Retry]       │
	   │   │        ┌──────▼──────┐
	   │   │        │   LOADING   │
	   │   │        └──────┬──────┘
	   │   │               │ [Server Response]
	   │   │        ┌──────▼──────┐
	   │   │        │    Result   │
	   │   │        └──────┬──────┘
	   │   │               │
	   │   └──────[Error]──┤
	   │                   │ [Success]
	   │            ┌──────▼──────┐
	   └────────────│    NONE     │
					└─────────────┘
```

## Validation Flow

```
┌─────────────────────────────┐
│  OnListCashClick()          │
│  [Initialize State]         │
└──────────┬──────────────────┘
		   │
		   ▼
┌─────────────────────────────┐
│  ShowCashAmountDialog()     │
│  [Show Input Dialog]        │
└──────────┬──────────────────┘
		   │
		   ▼
┌─────────────────────────────┐
│  OnCashAmountInputConfirm() │
└──────────┬──────────────────┘
		   │
		┌──┴──┐
		│     │
		▼     ▼
   ┌────────────────────┐
   │ ValidateCashAmount │
   ├─ amount > 0?       │
   ├─ amount <= balance?│
   └────┬───────────┬───┘
		│ FAIL      │ PASS
		│           │
		▼           ▼
	┌──────┐    ┌──────────────────────────┐
	│ ERROR│    │ ShowPricePerUnitDialog() │
	│ CODE:1    │ [Show Price Input]       │
	│ CODE:2    └──────┬───────────────────┘
	│                  │
	│                  ▼
	│     ┌──────────────────────────┐
	│     │OnPricePerUnitInputConfirm│
	│     └──────┬───────────────────┘
	│            │
	│         ┌──┴──┬──┐
	│         │     │  │
	│         ▼     ▼  ▼
	│     ┌────────────────────────┐
	│     │ ValidatePricePerUnit() │
	│     │ ValidateOverflow()     │
	│     ├─ price > 0?            │
	│     ├─ overflow?             │
	│     └────┬──────────┬────────┘
	│         │ FAIL     │ PASS
	│         │          │
	│         ▼          ▼
	│     ┌──────┐   ┌──────────────────────┐
	│     │ERROR │   │ShowConfirmationPreview
	│     │CODE:3│   └──────┬───────────────┘
	│     │CODE:4│          │
	│     │      │          ▼
	│     │      │   ┌──────────────────┐
	└─────┼──────┼──→│OnConfirmListing  │
		  │      │   │Click()           │
		  │      │   └──────┬───────────┘
		  │      │          │
		  │      │          ▼
		  │      │   ┌──────────────────┐
		  │      │   │SendCreateListing │
		  │      │   │Message()         │
		  │      │   └──────┬───────────┘
		  │      │          │
		  │      │          ▼
		  │      │   ┌──────────────────┐
		  │      │   │Server Processing │
		  │      │   └──────┬───────────┘
		  │      │          │
		  └──────┼──────────┼─────→ [Success/Error]
				 │          │
				 ▼          ▼
		┌──────────────────────────┐
		│HandleCreateListingResult │
		├─ success = 1?            │
		│  - Show Success          │
		│  - Refresh Listings      │
		├─ success = 0?            │
		│  - Show Error Code       │
		│  - Error Message         │
		└──────────────────────────┘
```

## Class Architecture

```
CUIWindow (base class)
	│
	├─ m_pListingList (CUIList)        [Display listings]
	├─ m_pBtnListCash (CUIButton)      [NEW: List Cash button]
	├─ m_pBtnBuy (CUIButton)           [Buy button]
	│
	├─ Dialog State
	│  ├─ m_nDialogState (int)         [NONE/AMOUNT/PRICE/CONFIRM/LOADING]
	│  ├─ m_llCashAmount (LONGLONG)    [User entered amount]
	│  ├─ m_llPricePerUnit (LONGLONG)  [User entered price]
	│  └─ m_llTotalValue (LONGLONG)    [Calculated total]
	│
	├─ Listing Data
	│  ├─ m_listings (vector)          [All listings from server]
	│  └─ m_nSelectedListingIndex (int) [Currently selected]
	│
	└─ Methods (15 total)
	   ├─ Lifecycle
	   │  ├─ initialize()
	   │  ├─ OpenUI()
	   │  └─ CloseUI()
	   │
	   ├─ NEW: Workflow
	   │  ├─ OnListCashClick()
	   │  ├─ ShowCashAmountDialog()
	   │  ├─ OnCashAmountInputConfirm()
	   │  ├─ ShowPricePerUnitDialog()
	   │  ├─ OnPricePerUnitInputConfirm()
	   │  ├─ ShowConfirmationPreview()
	   │  ├─ OnConfirmListingClick()
	   │  ├─ SendCreateListingMessage()
	   │  ├─ HandleCreateListingResult()
	   │  └─ MsgBoxCommand()
	   │
	   ├─ NEW: Validation
	   │  ├─ ValidateCashAmount()
	   │  ├─ ValidatePricePerUnit()
	   │  ├─ ValidateOverflow()
	   │  └─ GetPlayerCashBalance()
	   │
	   ├─ NEW: Utility
	   │  └─ ClearCashListingDialog()
	   │
	   └─ Existing: Listing
		  ├─ AddListing()
		  ├─ ClearListings()
		  ├─ SelectListing()
		  ├─ BuyCurrentListing()
		  └─ UpdateSelectedListingDisplay()
```

## Data Flow

```
INPUT                PROCESSING               OUTPUT
───────────────────────────────────────────────────────

User Input (Amount)
	│
	├─→ [Validate]
	│   ├─ > 0?
	│   └─ <= Balance?
	│
	├─→ [Store]
	│   └─ m_llCashAmount
	│
	└─→ [Next Step]
		└─ Show Price Dialog


User Input (Price)
	│
	├─→ [Validate]
	│   ├─ > 0?
	│   └─ No Overflow?
	│
	├─→ [Calculate]
	│   └─ Total = Amount × Price
	│
	├─→ [Store]
	│   ├─ m_llPricePerUnit
	│   └─ m_llTotalValue
	│
	└─→ [Next Step]
		└─ Show Confirmation


User Confirmation
	│
	├─→ [Format Message]
	│   ├─ CharIndex
	│   ├─ CashAmount
	│   └─ PricePerUnit
	│
	├─→ [Send to Server]
	│   └─ MSG_CASHEXCHANGE_CREATE_LISTING
	│
	└─→ [Wait for Response]
		└─ MSG_CASHEXCHANGE_CREATE_RESULT


Server Response
	│
	├─→ [Parse]
	│   ├─ Success?
	│   └─ Error Code?
	│
	├─→ [Process]
	│   ├─ [SUCCESS]
	│   │  └─ Show "Listing Created!"
	│   │     Refresh Listings
	│   │
	│   └─ [ERROR]
	│      └─ Show Error Message
	│         Based on Error Code
	│
	└─→ [Reset State]
		└─ m_nDialogState = NONE
		   Clear Values
```

## Integration Points (5 TODOs)

```
CashExchangeUI.cpp
│
├─ Line ~180: ShowCashAmountDialog()
│   TODO: Replace with MSGMGR()->ShowMsgBoxNumeric_only(...)
│
├─ Line ~207: ShowPricePerUnitDialog()
│   TODO: Replace with MSGMGR()->ShowMsgBoxNumeric_only(...)
│
├─ Line ~236: ShowConfirmationPreview()
│   TODO: Replace with MSGMGR()->ShowMsgBoxYesNo(...)
│
├─ Line ~348: GetPlayerCashBalance()
│   TODO: Replace with return g_pPlayer->GetCash();
│
├─ Line ~260-273: SendCreateListingMessage()
│   TODO: Uncomment network message code
│        Replace nCharIndex placeholder
│
└─ Message Dispatcher (External file)
   TODO: Add hook to call HandleCreateListingResult()
```

---

**This diagram shows the complete client-side architecture for cash listing creation!** 🎯
