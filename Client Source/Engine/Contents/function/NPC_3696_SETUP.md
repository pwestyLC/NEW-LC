# NPC 3696 - Cash Exchange Merchant Setup

## Dialog Options to Add

For NPC 3696, add these dialog choices:

```
[1748] Direction       → Opens Cash Exchange UI (list/buy cash)
[1220] Cancel          → Close dialog
```

## Server-Side Script Pattern

In your NPC dialog handler, when player selects option [1748]:

```cpp
// Send message to client to open Cash Exchange UI
// Message: MSG_OPEN_CASHEXCHANGE or similar
// Parameters: NPC ID 3696

// Client receives message and calls:
// CCashExchangeUI::OpenUI();
```

## Client-Side Hook (CashExchangeUI.cpp)

Already implemented:
- `OpenUI()` - Opens the window
- `CloseUI()` - Closes the window
- `AddListing()` - Displays listings
- `OnListCashClick()` - Opens list dialog
- `BuyCurrentListing()` - Processes buy

## Next Steps

1. Add NPC dialog option that sends open UI message
2. Client receives message and calls `OpenUI()`
3. Player sees Cash Exchange window
4. "List Cash" button → Multi-step dialog
5. "Buy" button → Purchase listing

XML is ready, code is ready. Just need the NPC dialog wired up.
