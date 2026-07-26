# NPC 3696 - Cash Exchange

## Implementation

**Client:** `UIQuestNew.cpp::OpenQuest()` - When player talks to NPC 3696, `findUI("cash_exchange_ui")->SetVisible(TRUE)` opens the window.

**Server:** `GameServer\doFuncQuest.cpp::do_QuestRequest()` - When player requests quest list from NPC 3696, sends empty quest list. Client then opens Cash Exchange window.

## Setup Required

1. **Database:** Create NPC 3696 in `mob_proto` table with quest flag
2. **World:** Spawn NPC 3696 in desired location
3. **No quests:** NPC 3696 should have 0 quests assigned (handled by server code)

The server-side check (`if (npcIndex == 3696)`) intercepts the request and returns immediately with an empty quest list, allowing the client to open the Cash Exchange UI.



