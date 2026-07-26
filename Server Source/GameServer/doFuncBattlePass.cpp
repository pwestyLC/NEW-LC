#include "stdhdrs.h"

#include "Server.h"
#include "CmdMsg.h"
#include "Log.h"
#include "../ShareLib/packetType/ptype_old_do_battle_pass.h"

#ifdef BATTLE_PASS_SYSTEM

#define MAX_BATTLE_PASS_REWARD 1
#define MAX_BATTLE_PASS_PAGE_LIMIT 10

bool do_BattlePassReq(CPC* pc, CNetMsg::SP& msg);
bool do_BattlePassInfoReq(CPC* pc, CNetMsg::SP& msg);

void do_BattlePass(CPC* pc, CNetMsg::SP& msg)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(msg->m_buf);

	switch (pBase->subType)
	{
	case MSG_BATTLE_PASS_REQ:
	{
		if (do_BattlePassReq(pc, msg) == false)
			return;
	}
	break;
	case MSG_BATTLE_PASS_INFO_REQ:
	{
		if (do_BattlePassInfoReq(pc, msg) == false)
			return;
	}
	break;
	default:
	{
		LOG_ERROR("HACKING : invalid subtype[%d]. charIndex[%d]", pBase->subType, pc->m_index);
		pc->m_desc->Close("invalid subtype");
		return;
	}
	}

}

bool do_BattlePassReq(CPC* pc, CNetMsg::SP& msg)
{
	RequestClient::battlePass* packet = reinterpret_cast<RequestClient::battlePass*>(msg->m_buf);

	// Check if already at max level
	if (pc->m_battlePassLevel >= gserver->m_listBattlePass.size())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeBattlePassError(rmsg, MSG_BATTLE_PASS_ERROR_LIMIT);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	// Get the current level reward
	CBattlePass* currentLevel = gserver->m_listBattlePass[pc->m_battlePassLevel];
	if (!currentLevel)
		return false;

	
	int totalRewards = 1; 
	if (pc->m_battlePassPremium)
		totalRewards += 1; 

	if (totalRewards > pc->m_inventory.getEmptyCount())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeBattlePassError(rmsg, MSG_BATTLE_PASS_ERROR_EMPTY_SLOT);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	// Check points for free or premium rewards
	bool canClaimFree = pc->m_battlePassPoints >= currentLevel->m_points;
	bool canClaimPremium = pc->m_battlePassPremium && pc->m_battlePassPoints >= currentLevel->m_premium_points;

	if (!canClaimFree && !canClaimPremium)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeBattlePassError(rmsg, MSG_BATTLE_PASS_ERROR_EXP_NEEDED);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	
	if (canClaimFree)
		pc->m_battlePassPoints -= currentLevel->m_points;
	else if (canClaimPremium)
		pc->m_battlePassPoints -= currentLevel->m_premium_points;

	
	pc->m_battlePassLevel += 1;

	
	int rewardIndex = pc->m_battlePassLevel -1;
	if (rewardIndex < 0 || rewardIndex >= gserver->m_listBattleItems.size())
	{
		LOG_ERROR("BattlePass: Invalid reward index %d for level %d", rewardIndex, currentLevel->m_level);
		return false;
	}

	BATTLE_PASS_REWARD* reward = gserver->m_listBattleItems[rewardIndex];

	// Give free item
	if (reward->item_index > 0)
	{
		CItem* newItem = gserver->m_itemProtoList.CreateItem(
			reward->item_index, -1, 0, 0, reward->item_count);
		if (newItem) pc->m_inventory.addItem(newItem);

		LOG_INFO("BattlePass: Player %d leveled up to %d, received FREE item %d x%d",
			pc->m_index, pc->m_battlePassLevel, reward->item_index, reward->item_count);
	}

	// Give premium item
	if (pc->m_battlePassPremium && reward->premium_item_index > 0)
	{
		CItem* newItem = gserver->m_itemProtoList.CreateItem(
			reward->premium_item_index, -1, 0, 0, reward->premium_item_count);
		if (newItem) pc->m_inventory.addItem(newItem);

		LOG_INFO("BattlePass: Player %d leveled up to %d, received PREMIUM item %d x%d",
			pc->m_index, pc->m_battlePassLevel, reward->premium_item_index, reward->premium_item_count);
	}

	pc->CalcStatus(true);
    CNetMsg::SP rmsg(new CNetMsg);
    // Send level to client
    ResponseClient::makeBattlePass(rmsg, MSG_BATTLE_PASS_REP, pc->m_index, 0, pc->m_battlePassLevel);
	SEND_Q(rmsg, pc->m_desc);
	

	return true;
}



void fagMsg(CNetMsg::SP& msg)
{
	msg->Init(MSG_BATTLE_PASS);
	RefMsg(msg) << ((char)MSG_BATTLE_PASS_INFO_REP);
}

bool do_BattlePassInfoReq(CPC* pc, CNetMsg::SP& msg)
{
	RequestClient::battlePass* packet = reinterpret_cast<RequestClient::battlePass*>(msg->m_buf);

	int PageCount = (gserver->m_listBattlePass.size() + 9) / 10;

	if (packet->page >= PageCount)
		return false;

	LOG_INFO("BATTLE_PASS: PAGE %d %d %d", packet->page, 1, gserver->m_listBattlePass.size());

	//header 
	CNetMsg::SP rmsg(new CNetMsg); // open ui packet
	fagMsg(rmsg);
	CBattlePass* battlePassFree = NULL;
	if (pc->m_battlePassLevel >= gserver->m_listBattlePass.size())
		battlePassFree = gserver->m_listBattlePass[gserver->m_listBattlePass.size() - 1];
	else
		battlePassFree = gserver->m_listBattlePass[pc->m_battlePassLevel];

	if (battlePassFree == NULL)
		return false;


    // Send level to client UI
    RefMsg(rmsg) << 0/*nIndex*/ << htonl(pc->m_battlePassLevel);


	//progress
	if (pc->m_battlePassLevel >= gserver->m_listBattlePass.size()) {
		RefMsg(rmsg)
			<< (int)0
			<< htonl(gserver->m_listBattlePass[gserver->m_listBattlePass.size() - 1]->m_points);
	}
	else
	{
		RefMsg(rmsg)
			<< htonl(pc->m_battlePassPoints)
			<< htonl(battlePassFree->m_points);
	}
	char hasNext = (packet->page + 1 < PageCount) ? 1 : 0;
	RefMsg(rmsg) << htonl(pc->m_battlePassPremium)
		<< htonl(gserver->m_listBattlePass.size())
		<< htonl(packet->page)
		<< hasNext
		<< htonl(battlePassFree->m_season);  //season-

	int i = 0;

	//items
	for (int i = (packet->page * 10) ; i < gserver->m_listBattlePass.size() && i < ((packet->page * 10) + 10) ; i++)
	{

		CBattlePass* battlePass = gserver->m_listBattlePass[i];
		if (battlePass == NULL)
			return false;

		char staticArray[50];
		memset(staticArray, 0, 50);

		const char* battlePassName = battlePass->m_name.c_str();

		std::strncpy(staticArray, battlePassName, sizeof(staticArray) - 1); // Copy at most 49 characters

		staticArray[sizeof(staticArray) - 1] = '\0'; // Ensure null-terminated

		int fuk = strlen(staticArray);
		fuk += 1;
		BATTLE_PASS_REWARD* a = gserver->m_listBattleItems[i];

		RefMsg(rmsg) << htonl(battlePass->m_level)
			<< htonl(battlePass->m_points)
			<< staticArray;

		for (int z = 0; z < 50 && z < 50 - fuk; z++)
			RefMsg(rmsg) << (char)0x00;

		RefMsg(rmsg)
			<< htonl(a->item_index)
			<< htonl(a->item_count)
			<< htonl(a->premium_item_index)
			<< htonl(a->premium_item_count);


	}



	//LOG_INFO("MSG_BATTLE_PASS: SIZE MSG: %d", sizeof(ResponseClient::battlePassInfo) + ( sizeof(ResponseClient::battlePassItem) * packetInfo->total)); RefMsg(msg)

	SEND_Q(rmsg, pc->m_desc);


	return true;
}

#endif