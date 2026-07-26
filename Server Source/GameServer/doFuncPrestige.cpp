#include "stdhdrs.h"

#include "Server.h"
#include "CmdMsg.h"
#include "Log.h"
#include "../ShareLib/packetType/ptype_old_do_prestige.h"

#ifdef PRESTIGE_SYSTEM

#define MAX_PRESTIGE_REWARD 1
#define MAX_PRESTIGE_PAGE_LIMIT 10

bool do_PrestigeReq(CPC* pc, CNetMsg::SP& msg);
bool do_PrestigeListReq(CPC* pc, CNetMsg::SP& msg);
bool do_PrestigeInfoReq(CPC* pc, CNetMsg::SP& msg);

void do_Prestige(CPC* pc, CNetMsg::SP& msg)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(msg->m_buf);

	switch (pBase->subType)
	{
	case MSG_PRESTIGE_REQ:
		{
			if (do_PrestigeReq(pc, msg) == false)
				return;
		}
		break;
	case MSG_PRESTIGE_INFO_REQ:
		{
			if (do_PrestigeInfoReq(pc, msg) == false)
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

bool do_PrestigeReq(CPC* pc, CNetMsg::SP& msg)
{
	RequestClient::prestige* packet = reinterpret_cast<RequestClient::prestige*>(msg->m_buf);

#ifdef ENABLE_NPC_PRESTIGE
	if (pc->m_pArea->FindCharInCell(pc, packet->npcIndex, MSG_CHAR_NPC, false) == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makePrestigeError(rmsg, MSG_PRESTIGE_ERROR_NOT_EXIST_NPC);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}
#endif

	// Check if already have max prestige
	if (pc->m_prestigeLevel == MAX_PRESTIGE_LEVEL) 
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makePrestigeError(rmsg, MSG_PRESTIGE_ERROR_LIMIT);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	// Get the next prestige level
	CPrestige * prestigeFree = gserver->FindPrestigeByLevel(pc->m_prestigeLevel + 1);
	if (prestigeFree == NULL)
		return false;
		
	// Check if have empty slot for reward
	std::vector<CItem*> rewardItemsFree = prestigeFree->getItemsReward();
	std::vector<CItem*> rewardItemsPremium = prestigeFree->getPremiumItemsReward();
	
	int totalRewards = rewardItemsFree.size();
	if (pc->m_prestigePremium)
		totalRewards += rewardItemsPremium.size();

	if (totalRewards > pc->m_inventory.getEmptyCount())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makePrestigeError(rmsg, MSG_PRESTIGE_ERROR_EMPTY_SLOT);
		SEND_Q(rmsg, pc->m_desc);
		return false;	
	}

	// Check if have exp for next prestige
	if (pc->m_prestigePoints < prestigeFree->m_points)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makePrestigeError(rmsg, MSG_PRESTIGE_ERROR_EXP_NEEDED);
		SEND_Q(rmsg, pc->m_desc);
		return false;	
	}

	// Check if have level for next prestige
	if (pc->m_level < prestigeFree->m_level)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makePrestigeError(rmsg, MSG_PRESTIGE_ERROR_NOCONDITION_LEVEL);
		SEND_Q(rmsg, pc->m_desc);
		return false;	
	}

	pc->m_prestigeLevel += 1; // increase prestige
	pc->m_prestigePoints -= prestigeFree->m_points; // decrease points

	// Give all rewards if have
	for (int i = 0; i < rewardItemsFree.size(); i++) 
	{
		CItem* newitem = gserver->m_itemProtoList.CreateItem(rewardItemsFree[i]->getDBIndex(), -1, 
				rewardItemsFree[i]->getPlus(), rewardItemsFree[i]->getFlag(), rewardItemsFree[i]->Count());
		if (newitem)
			pc->m_inventory.addItem(newitem);
	}

	if (pc->m_prestigePremium)
	{
		for (int i = 0; i < rewardItemsPremium.size(); i++) 
		{
			CItem* newitem = gserver->m_itemProtoList.CreateItem(rewardItemsPremium[i]->getDBIndex(), -1, 
				rewardItemsPremium[i]->getPlus(), rewardItemsPremium[i]->getFlag(), rewardItemsPremium[i]->Count());
			if (newitem)
				pc->m_inventory.addItem(newitem);
		}
	}

	pc->CalcStatus(true);

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makePrestige(rmsg, MSG_PRESTIGE_REP, pc->m_index, 0, pc->m_prestigeLevel);
		SEND_Q( rmsg, pc->m_desc );
	}

	return true;
}

bool do_PrestigeInfoReq(CPC* pc, CNetMsg::SP& msg)
{
	RequestClient::prestige* packet = reinterpret_cast<RequestClient::prestige*>(msg->m_buf);

#ifdef ENABLE_NPC_PRESTIGE
	if (pc->m_pArea->FindCharInCell(pc, packet->npcIndex, MSG_CHAR_NPC, false) == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makePrestigeError(rmsg, MSG_PRESTIGE_ERROR_NOT_EXIST_NPC);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}
#endif

	int pageLimit = packet->page * MAX_PRESTIGE_PAGE_LIMIT;
	if (pageLimit > gserver->m_listPrestige.size())
		return false;

	LOG_INFO("PRESTIGE: PAGE %d %d %d", packet->page, pageLimit, gserver->m_listPrestige.size());

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::prestigeInfo *packetInfo = reinterpret_cast<ResponseClient::prestigeInfo *>(rmsg->m_buf);
		packetInfo->type = MSG_PRESTIGE;
		packetInfo->subType = MSG_PRESTIGE_INFO_REP;
		packetInfo->level = pc->m_prestigeLevel;
		packetInfo->premium = pc->m_prestigePremium;
		packetInfo->page = packet->page;
		packetInfo->total = 0;
		packetInfo->next = pageLimit >= gserver->m_listPrestige.size();

		// Check if already have max prestige
		if (pc->m_prestigeLevel == MAX_PRESTIGE_LEVEL + 1) {
			packetInfo->progress = 0;
		} else {		
			CPrestige * prestigeFree = gserver->FindPrestigeByLevel(pc->m_prestigeLevel);
			if (prestigeFree == NULL)
				return false;

			packetInfo->points = prestigeFree->m_points;
			packetInfo->progress = pc->m_prestigePoints;
			packetInfo->season = prestigeFree->m_season;//Cloud add Season
			//LOG_INFO("MSG_BATTLE_PASS: Progress: %d", packetInfo->progress);

			int i = 0;
			int index;
			map_prestige_t::iterator it = gserver->m_listPrestige.begin();
			map_prestige_t::iterator endit = gserver->m_listPrestige.end();
			for(; it != endit; ++it)
			{
				index = (*it).first;
				if (index <= pageLimit && index > pageLimit - MAX_PRESTIGE_PAGE_LIMIT)
				{
					CPrestige * prestige = (*it).second;
					if (prestige == NULL)
						return false;

					const std::vector<CItem*> rewardItems = prestige->getItemsReward();
					if (rewardItems.size() == 0)
						continue;

					packetInfo->list[i].level = prestige->m_level;
					packetInfo->list[i].points = prestige->m_points;
					
					strncpy(packetInfo->list[i].name, prestige->m_name.c_str(), 50);

					packetInfo->list[i].item_index = rewardItems[0]->getDBIndex();
					packetInfo->list[i].item_count = rewardItems[0]->Count();

					const std::vector<CItem*> premiumRewardItems = prestige->getPremiumItemsReward();
					if (premiumRewardItems.size() == 0)
						continue;

					packetInfo->list[i].premium_item_index = premiumRewardItems[0]->getDBIndex();
					packetInfo->list[i].premium_item_count = premiumRewardItems[0]->Count();

					i++;
				}
			}

			packetInfo->total = i;
			LOG_INFO("MSG_PRESTIGE: Total: %d", packetInfo->total);
		}

		rmsg->setSize( sizeof(ResponseClient::prestigeInfo) + ( sizeof(ResponseClient::prestigeItem) * packetInfo->total));
		SEND_Q(rmsg, pc->m_desc);
	}

	return true;
}

#endif