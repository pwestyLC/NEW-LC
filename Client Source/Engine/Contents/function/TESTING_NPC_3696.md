# Testing NPC 3696 Cash Exchange

## Prerequisites

1. **Server:** NPC 3696 must be created in database and spawned in a zone
   - Database: Add entry to mob_proto with index=3696
   - World: Spawn NPC in your test zone

2. **Client:** Must have built with latest changes
   - UIQuestNew.cpp modified with NPC 3696 handler
   - CashExchange.xml loaded with window UI

## Test Steps

1. **Start server** with NPC 3696 spawned
2. **Start client** and log in
3. **Find NPC 3696** in the game world
4. **Click on NPC 3696** to interact
5. **Expected result:** Cash Exchange window opens (no quest dialog)

## What Should Happen

1. Player clicks NPC 3696
2. Client sends MSG_QUEST_REQUEST to server
3. Server intercepts in do_QuestRequest() and returns empty quest list
4. Client's OpenQuest() receives empty list
5. NPC 3696 handler executes: `pUIManager->findUI("cash_exchange_ui")->SetVisible(TRUE)`
6. **Cash Exchange window appears on screen**

## If It Doesn't Work

- **Window doesn't open:** Check that CashExchange.xml is loaded and cash_exchange_ui ID exists
- **NPC doesn't respond:** Verify NPC 3696 exists in database and is spawned
- **Server crashes:** Check doFuncQuest.cpp changes are correct
- **Client crashes:** Check UIQuestNew.cpp syntax is correct

## What You Can Do

Once window opens:
- View cash listings
- Click "List Cash" to sell premium cash
- Click "Buy" to purchase listings
- Balance shown is from bg_user.cash (premium currency)
