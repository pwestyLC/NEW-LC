#include "stdhdrs.h"

#include "Server.h"
#include "CmdMsg.h"
#include "Log.h"
#include "../ShareLib/packetType/ptype_old_do_reborn.h"
#include "../ShareLib/packetType/ptype_old_do_skill.h"
#include "../ShareLib/packetType/ptype_old_extend.h"
#include "../ShareLib/packetType/ptype_server_to_server.h"

#include "GuildBattleManager.h"
#include "Exp.h"

struct T_Skill 
{
	int			index;
	int			active;
};

bool do_RebornReq(CPC* pc, CNetMsg::SP& msg);

void do_Reborn(CPC* pc, CNetMsg::SP& msg)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(msg->m_buf);

	switch (pBase->subType)
	{
	case MSG_REBORN_REQ:
		{
			if (do_RebornReq(pc, msg) == false)
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

bool do_RebornReq(CPC* pc, CNetMsg::SP& msg)
{
	RequestClient::reborn* packet = reinterpret_cast<RequestClient::reborn*>(msg->m_buf);

	// check npc change class exist
	if (pc->m_pArea->FindCharInCell(pc, packet->npcIndex, MSG_CHAR_NPC, false) == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeRebornError(rmsg, MSG_REBORN_ERROR_NOT_EXIST_NPC);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	// check max level
	if (pc->m_level < GetMaxLevel()) 
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeRebornError(rmsg, MSG_REBORN_ERROR_NOCONDITION_LEVEL);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	// check max reborn
#ifdef ENABLE_MAX_REBORN
	if (pc->m_reborn == MAX_REBORN) 
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeRebornError(rmsg, MSG_REBORN_ERROR_NOCONDITION_MAX_REBORN);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}
#endif

    // Undress 2.0 - now checks for type of wearing and uses already existing messages
    CItem*  itemWear;
    int     iSlotsneeded = 0;
    for (int i = 0; i < COSTUME2_WEARING_BACK; i++)
    {
        if (pc->m_wearInventory.wearItemInfo[i])
            iSlotsneeded++;
    }

	// +1 slot for reward
	iSlotsneeded += 1;
    
	if (pc->m_inventory.getEmptyCount() < iSlotsneeded)
    {
        CNetMsg::SP rmsg(new CNetMsg);
		SysFullInventoryMsg(rmsg, 0);
        SEND_Q(rmsg, pc->m_desc);
        return false;
    }

    for (int i = 0; i < COSTUME2_WEARING_BACK; i++)
    {
        itemWear = pc->m_wearInventory.wearItemInfo[i];
        if (itemWear)
        {
			if (i < COSTUME2_WEARING_START)
			{
				if (!pc->m_wearInventory.DelNormalItem(i)) {
					return false;
				}
			}
			else
			{
				if (!pc->m_wearInventory.DelCostumItem(itemWear->getWearPos()))
					return false;
			}
			
			CNetMsg::SP rmsg(new CNetMsg);
			WearingMsg(rmsg, pc, i, -1, 0);
			pc->m_pArea->SendToCell(rmsg, pc, false);
        }
    }

	// change to the new job
	if (pc->m_job == JOB_NIGHTSHADOW) {
		pc->m_job2 = 1;
		pc->m_level = 90;
	} else {
		pc->m_job2 = 0;
		pc->m_level = 1;
	}

	pc->m_reborn += 1;
	pc->m_exp = 0;
	
	int itemReward = -1;
	switch (pc->m_reborn)
	{
	case 1:
		itemReward = 12423;
		break;
	case 2:
		itemReward = 12423;
		break;
	case 3:
		itemReward = 12423;
		break;
	case 4:
		itemReward = 12423;
		break;
	case 5:
		itemReward = 20688;
		break;
	default:
		itemReward = 85;
		break;
	}

	int skillpoint = 0;
	skillpoint += pc->m_activeSkillList.RemoveSkillFor2ndJob();
	skillpoint += pc->m_passiveSkillList.RemoveSkillFor2ndJob();
	skillpoint += pc->m_etcSkillList.RemoveSkillFor2ndJob();
	
	// reset stats point
	int totalStats = pc->m_statpt_str + pc->m_statpt_dex +
		pc->m_statpt_int + pc->m_statpt_con +
		pc->m_statpt_remain;

	pc->m_statpt_str = 0;
	pc->m_statpt_dex = 0;
	pc->m_statpt_int = 0;
	pc->m_statpt_con = 0;
	pc->m_statpt_remain = 0;

	pc->m_statpt_remain = (pc->m_level - JOB_2ND_LEVEL) * 3 +
		(pc->m_level - JOB_2ND_LEVEL) / 2 +
		(JOB_2ND_LEVEL - 1);
	pc->m_statpt_remain += totalStats; // Add transferred stats and remaining points
	pc->m_statpt_remain += pc->m_stats_addition;
	pc->m_statpt_remain += pc->m_reborn * 250;
	
#ifdef DEMIGOD
	if (pc->m_bPhoenix_Char == 1 || pc->m_bPremium_Phoenix == 1 || pc->m_DemiGod == 1)
#else
	if (pc->m_bPhoenix_Char == 1 || pc->m_bPremium_Phoenix == 1)
#endif
	{
		pc->m_statpt_remain += 30;
	}

	if (pc->m_statpt_remain < 0)
	{
		printf("Error: Calculated stat points are negative.\n");
		pc->m_statpt_remain = 0;
	}

	GAMELOG << "RESET STATPOINT" << delim
			<< pc->m_statpt_str << delim
			<< pc->m_statpt_dex << delim
			<< pc->m_statpt_int << delim
			<< pc->m_statpt_con << delim
			<< pc->m_statpt_remain << end;

	pc->InitStat();
	pc->CalcStatus(true);

	pc->m_hp = pc->m_maxHP;
	pc->m_mp = pc->m_maxMP;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		StatPointRemainMsg(rmsg, pc);
		SEND_Q(rmsg, pc->m_desc);
	}

    // Group and Expedition
    if (pc->m_Exped != NULL)
    {
        CNetMsg::SP rmsg(new CNetMsg);
        HelperExpedQuitReqMsg(rmsg, pc->m_Exped->GetBossIndex(), pc->m_index, MSG_EXPED_QUITMODE_NORMAL);
        SEND_Q(rmsg, gserver->m_helper);
        pc->m_Exped = NULL;
    }

    if (pc->m_party != NULL)
    {
        CNetMsg::SP rmsg(new CNetMsg);
        HelperPartyQuitReqMsg(rmsg, pc->m_party->GetBossIndex(), pc->m_index);
        SEND_Q(rmsg, gserver->m_helper);
    }

	// learn all skills
	{
		std::vector<T_Skill> Skill;
		CLCString sql(1024);
		char g_buf[8192];
		sql.Format("SELECT * FROM `t_skill` WHERE  `a_job` = %i AND `a_job2` = %i", pc->m_job, pc->m_job2);
		CDBCmd cmd;
		CDBCmd cmd1;
		CDBCmd cmd2;
		cmd.Init(&gserver->m_dbdata);
		cmd1.Init(&gserver->m_dbdata);
		cmd2.Init(&gserver->m_dbdata);
		cmd.SetQuery(sql);
		int counts = cmd.GetRecordCount();
		if (!cmd.Open())//|| !cmd1.MoveFirst())
		{

		}
		while (cmd.MoveNext())
		{
			short type;
			T_Skill ski;
			cmd.GetRec("a_index", ski.index);
			cmd.GetRec("a_type", type);
			if (type >= 0 && type <= 2)
				ski.active = 1;
			else
			{
				ski.active = 0;
			}
			Skill.push_back(ski);
		}
		sql.Format("SELECT * FROM `t_skill` WHERE  `a_job` = %i AND `a_job2` = 0", pc->m_job);
		cmd1.SetQuery(sql);
		counts = cmd1.GetRecordCount();
		if (!cmd1.Open())//|| !cmd1.MoveFirst())
		{

		}
		while (cmd1.MoveNext())
		{
			short type;
			T_Skill ski;
			cmd1.GetRec("a_index", ski.index);
			cmd1.GetRec("a_type", type);
			if (type >= 0 && type <= 2)
				ski.active = 1;
			else
			{
				ski.active = 0;
			}
			Skill.push_back(ski);
		}
		int passiveSkills[2][21] =
		{
			{2019, 2020, 2021, 2022, 2023, 2024, 2025, 2026, 2027, 2028, 2029, 2030, 2031, 2032, 2033, 2034, 2035, 2036, 2037, 2038, 2039 },
			{12457, 12457, 12457, 12458, 12458, 12458, 12459, 12459, 12459, 12453, 12453, 12453, 12455, 12455, 12455, 12456, 12456, 12456, 12454, 12454, 12454 }
		};
		int i;
		int b;
		bool hasPassiveSkill = false;
		int passiveSkillIndex = -1;
		for (i = 0; i < 21; i++)
		{
			if (pc->m_passiveSkillList.Find(passiveSkills[0][i]))
			{
				hasPassiveSkill = true;
				passiveSkillIndex = passiveSkills[1][i];
				CItem* giveitem = gserver->m_itemProtoList.CreateItem(passiveSkillIndex, -1, 0, 0, 1);
				if (giveitem)
				{
					if (pc->m_inventory.getEmptyCount() > 1)
					{
						if (!pc->m_inventory.addItem(giveitem))
						{
							LOG_INFO(" Couldn't Give Skill Book %d", giveitem);
							delete giveitem;
						}

					}
				}
				
			}
		}

        pc->m_activeSkillList.Clear();
        pc->m_passiveSkillList.Clear();
        for (int i = 0; i < Skill.size(); i++)
        {
            sql.Format("SELECT `a_level`, `a_learnItemIndex1`, `a_learnItemCount1` FROM `t_skillLevel` WHERE  `a_learnLevel` <= %i AND `a_index` = %i ORDER BY `a_level` DESC LIMIT 1", pc->m_level, Skill[i].index);
            cmd2.SetQuery(sql);
            if (!cmd2.Open() || !cmd2.MoveFirst())
            {
                continue;
            }
            int level = 0;
			int learnItemIndex = 0;
			int learnItemCount = 0;
            if (Skill[i].active == 1)
            {
                cmd2.GetRec("a_level", level);
                CSkill* s = gserver->m_skillProtoList.Create(Skill[i].index, level);
                if (s != NULL)
                {
                    pc->m_activeSkillList.Add(s);
 
                }
            }
            else if (Skill[i].active == 0)
            {
                cmd2.GetRec("a_level", level);
				cmd2.GetRec("a_learnItemIndex1", learnItemIndex);
				cmd2.GetRec("a_learnItemCount1", learnItemCount);
				item_search_t vec;
				if (learnItemIndex != -1)
				{
					int sc = pc->m_inventory.searchItemByCondition(learnItemIndex, 0, 0, vec);
					if (sc == 0 || sc < learnItemCount)
					{
						continue;
					}
	
					pc->m_inventory.deleteItem(vec, learnItemCount);
				}
                CSkill* s = gserver->m_skillProtoList.Create(Skill[i].index, level);
                if (s != NULL)
                {
                    pc->m_passiveSkillList.Add(s);
                }
            }
        }
        CNetMsg::SP rmsg(new CNetMsg);
        ResponseClient::makeSkillListMsg(rmsg, pc);
        SEND_Q(rmsg, pc->m_desc);
	}

	while (pc->m_elementalList)
		pc->UnsummonElemental(pc->m_elementalList);
	
	if (pc->m_evocationIndex > EVOCATION_NONE)
	{
		pc->Unevocation();
	}

	if(pc->m_guildInfo != NULL && pc->m_guildInfo->guild())
	{
		CGuild* guild = pc->m_guildInfo->guild();
		if(guild->boss()->GetPC() == pc)
		{
			GuildBattleManager::instance()->delete_banish(guild->index());
			if( GuildBattleManager::instance()->cancel(guild->index()) == true)
			{
				guild->m_isUseTheStashAndSkill = true;

				CNetMsg::SP rmsg(new CNetMsg);
				ServerToServerPacket::makeGuildBattleStashLockOff(rmsg, guild->index());
				SEND_Q(rmsg, gserver->m_helper);
			}
		}

		if (guild->battleState() == GUILD_BATTLE_STATE_ING)
		{
			GuildBattleManager::instance()->giveup(pc->m_index);
		}
	}

	CItem* item = gserver->m_itemProtoList.CreateItem(itemReward, -1, 0, 0, 1);
	if (item)
	{
		item->m_preferenceIndex = pc->m_index;
		if (pc->m_inventory.addItem(item) == false)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysFullInventoryMsg(rmsg, 0);
			SEND_Q(rmsg, pc->m_desc);
			return false;
		}
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeReborn(rmsg, pc->m_index, MAX_REBORN, pc->m_reborn);
		SEND_Q( rmsg, pc->m_desc );
	}

	return true;
}