# Cash Exchange Feature - Complete

## Client Components

1. **CashExchangeUI.cpp / .h** - UI logic for listing and buying cash
2. **CashExchange.xml** - Window layout with listing list, "List Cash" & "Buy" buttons
3. **UIQuestNew.cpp** - NPC 3696 handler opens the Cash Exchange window

## Server Components

**GameServer\doFuncQuest.cpp** - When player talks to NPC 3696:
- Server intercepts quest request in `do_QuestRequest()`
- Returns empty quest list (count=0)
- Client then opens Cash Exchange UI window

## Flow

1. Player talks to NPC 3696
2. Client sends MSG_QUEST_REQUEST with npcIndex=3696
3. Server checks NPC index, returns empty quest list
4. Client's `OpenQuest()` sees empty quests and calls `findUI("cash_exchange_ui")->SetVisible(TRUE)`
5. Cash Exchange window opens

## Balance Source

Premium cash reads from: `UICashShopEX::m_hasCash` (updated by `MSG_EX_CASHITEM_BALANCE_REP` in SessionStateExten.cpp)

## Status

✓ Client code complete & builds
✓ Server code complete & compiles
✓ Ready for NPC 3696 database/world setup

## Next Steps

1. Create NPC 3696 in mob_proto database
2. Spawn NPC 3696 in desired location
3. Test in-game

