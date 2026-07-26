#include "stdhdrs.h"

#include "Server.h"
#include "CmdMsg.h"
#include "Log.h"
#include "../ShareLib/packetType/ptype_old_do_changejob.h"
#include "../ShareLib/packetType/ptype_old_do_skill.h"
#include "../ShareLib/packetType/ptype_old_extend.h"
#include "../ShareLib/packetType/ptype_server_to_server.h"

#include "GuildBattleManager.h"

struct T_Skill 
{
	int			index;
	int			active;
};

bool do_ChangeJobReq(CPC* pc, CNetMsg::SP& msg);
bool do_ChangeJobResetReq(CPC* pc, CNetMsg::SP& msg);
bool do_ChangeClassReq(CPC* pc, CNetMsg::SP& msg);

void do_ChangeJob(CPC* pc, CNetMsg::SP& msg)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(msg->m_buf);

	switch (pBase->subType)
	{
	case MSG_CHANGEJOB_REQ:
		{
			if (do_ChangeJobReq(pc, msg) == false)
				return;
		}
		break;
	case MSG_CHANGECLASS_REQ:
		{
			if (do_ChangeClassReq(pc, msg))
				return;
		}
		break;

	case MSG_CHANGEJOB_RESET_REQ:
		{
			if (do_ChangeJobResetReq(pc, msg) == false)
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

	// ��ȯ ���
	while (pc->m_elementalList)
		pc->UnsummonElemental(pc->m_elementalList);

	// ���� ���
	if (pc->m_evocationIndex != EVOCATION_NONE)
		pc->Unevocation();
}

bool do_ChangeClassReq(CPC* pc, CNetMsg::SP& msg)
{
	RequestClient::changeJob* packet = reinterpret_cast<RequestClient::changeJob*>(msg->m_buf);

	if (pc->m_job == packet->job) 
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_ALREADY);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}
	if (pc->m_pArea->FindCharInCell(pc, packet->npcIndex, MSG_CHAR_NPC, false) == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_NOT_EXIST_NPC);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}
	// check if certificate change class exist
	CItem * certificate = pc->m_inventory.FindByDBIndex(12385);
	if (certificate == NULL)
	{	
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_NOITEM);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}
// check if have money
	long needmoney = 2000000000; // 2b
	if (pc->m_inventory.getMoney() < needmoney)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_NOMONEY);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	//we should check if the players are wearing anything then take it off if so. (check iventory space before take off)
	CItem*  itemWear;
    int     iSlotsneeded = 0;
    for (int i = 0; i < COSTUME2_WEARING_START; i++)
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
	// check if char is using items
	/*if(pc->m_wearInventory.IsWearingSomething())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysFullInventoryMsg(rmsg, 0);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}*/

	// change to the new job
	pc->m_job = packet->job;
	if (pc->m_job == JOB_NIGHTSHADOW) {

		if (pc->m_level < 90) 
			pc->m_level = 90;

		pc->m_job2 = 1;
		
	} else {
		pc->m_job2 = 0;
	}

	// reset stats point
	int totalStats = pc->m_statpt_str + pc->m_statpt_dex +  //pwesty fix
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
	pc->m_statpt_remain += 75;
	
#ifdef DEMIGOD
	if ( pc->m_bPhoenix_Char == 1  || pc->m_bPremium_Phoenix == 1 || pc->m_DemiGod == 1)
#else
		if (pc->m_bPhoenix_Char == 1 || pc->m_bPremium_Phoenix == 1)
#endif
	{
		pc->m_statpt_remain += 30;
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
        if (!cmd.Open() )//|| !cmd1.MoveFirst())
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
        if (!cmd1.Open() )//|| !cmd1.MoveFirst())
        {
           
        }
        while (cmd1.MoveNext())
        {
            short type;
            T_Skill ski;
            cmd1.GetRec("a_index", ski.index);
            cmd1.GetRec("a_type", type);
			if (type >= 0 && type <= 2)
			{
				ski.active = 1;
			}
            else
            {
                ski.active = 0;
            }
            Skill.push_back(ski);
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
				//if (skillType == 0) continue;
				LOG_INFO(" Active Skill %d", Skill[i].index);

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

				LOG_INFO("skill %d %d %d", Skill[i].index, learnItemIndex, learnItemCount);

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
	
	GAMELOG << init( "CLIENT_RESTART", pc ) << end;

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
			//����� ���� ó��
			GuildBattleManager::instance()->giveup(pc->m_index);
		}
	}

	pc->m_inventory.decreaseItemCount(certificate, 1);
	pc->m_inventory.decreaseMoney(needmoney);

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeExRestart(rmsg, 1);
		SEND_Q( rmsg, pc->m_desc );
	}

	pc->m_desc->returnToCharacterSelectMode();

	return true;
}

bool do_ChangeJobReq(CPC* pc, CNetMsg::SP& msg)
{
	if (pc->m_job2 != 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_ALREADY);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	if (pc->m_level < JOB_2ND_LEVEL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_NOCONDITION_LEVEL);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

#ifdef GIVE_ITEM_IN_CHANGE_JOB
	if(pc->m_inventory.getEmptyCount() < 1)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysFullInventoryMsg(rmsg, 0);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}
#endif

	RequestClient::changeJob* packet = reinterpret_cast<RequestClient::changeJob*>(msg->m_buf);

	if (packet->npcIndex <= 0) // ���� �������� �����
	{
		if (pc->m_inventory.FindByDBIndex(2868) == NULL)
		{
			LOG_ERROR("HACKING : not found item(2868). charIndex[%d]", pc->m_index);
			pc->m_desc->Close("not found item");
			return false;
		}
	}
	else
	{
		if (pc->m_pArea->FindCharInCell(pc, packet->npcIndex, MSG_CHAR_NPC, false) == NULL)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_NOT_EXIST_NPC);
			SEND_Q(rmsg, pc->m_desc);
			return false;
		}
	}

	CSkill* skill = NULL;
	int needskilllevel = 5;

	// ��ų ���ϱ� : �ʿ� ��ų ������ 5�� �ƴϸ� ���� �ʿ�
	switch (pc->m_job)
	{
	case JOB_TITAN:
		{
			switch (packet->job)
			{
			case JOB_2ND_HIGHLANDER:
			case JOB_2ND_WARMASTER:
				skill = pc->m_activeSkillList.Find(43);
				break;

			default:
				{
					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_WRONGMSG);
					SEND_Q(rmsg, pc->m_desc);
				}
				return false;
			}
		}
		break;

	case JOB_KNIGHT:
		{
			switch (packet->job)
			{
			case JOB_2ND_ROYALKNIGHT:
			case JOB_2ND_TEMPLEKNIGHT:
				skill = pc->m_activeSkillList.Find(48);
				break;

			default:
				{
					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_WRONGMSG);
					SEND_Q(rmsg, pc->m_desc);
				}
				return false;
			}
		}
		break;

	case JOB_HEALER:
		{
			switch (packet->job)
			{
			case JOB_2ND_ARCHER:
			case JOB_2ND_CLERIC:
				skill = pc->m_activeSkillList.Find(52);
				break;

			default:
				{
					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_WRONGMSG);
					SEND_Q(rmsg, pc->m_desc);
				}
				return false;
			}
		}
		break;

	case JOB_MAGE:
		{
			switch (packet->job)
			{
			case JOB_2ND_WIZARD:
			case JOB_2ND_WITCH:
				skill = pc->m_activeSkillList.Find(65);
				break;

			default:
				{
					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_WRONGMSG);
					SEND_Q(rmsg, pc->m_desc);
				}
				return false;
			}
		}
		break;

	case JOB_ROGUE:
		{
			switch (packet->job)
			{
			case JOB_2ND_ASSASSIN:
			case JOB_2ND_RANGER:
				skill = pc->m_activeSkillList.Find(131);
				break;

			default:
				{
					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_WRONGMSG);
					SEND_Q(rmsg, pc->m_desc);
				}
				return false;
			}
		}
		break;

	case JOB_SORCERER:
		{
			switch (packet->job)
			{
			case JOB_2ND_ELEMENTALLIST:
			case JOB_2ND_SPECIALLIST:
				skill = pc->m_activeSkillList.Find(308);
				break;

			default:
				{
					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_WRONGMSG);
					SEND_Q(rmsg, pc->m_desc);
				}
				return false;
			}
		}
		break;

#ifdef EX_ROGUE
	case JOB_EX_ROGUE:
		{
			switch (packet->job)
			{
			case JOB_2ND_EX_ASSASSIN:
			case JOB_2ND_EX_RANGER:
				// EXROGUE : ���� ��, �ݵ�� ������� ��ų �ε��� ����
				skill = pc->m_activeSkillList.Find(1536);
				break;
			default:
				{
					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_WRONGMSG);
					SEND_Q(rmsg, pc->m_desc);
				}
				break;
			}
		}
		break;
#endif // EX_ROGUE

#ifdef EX_MAGE
	case JOB_EX_MAGE:
		{
			switch (packet->job)
			{
			case JOB_2ND_WIZARD:
			case JOB_2ND_WITCH:
				// EXMAGE : ���� ��, �ݵ�� ������� ��ų �ε��� ����
				skill = pc->m_activeSkillList.Find(1638);
				break;

			default:
				{
					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_WRONGMSG);
					SEND_Q(rmsg, pc->m_desc);
				}
				return false;
			}
		}
		break;
#endif // EX_MAGE

	default:
		{
			LOG_ERROR("HACKING : invalid job[%d]. charIndex[%d]", packet->job, pc->m_index);
			pc->m_desc->Close("invalid job");
			return false;
		}
	}

	// --- ��ų ���ϱ�
	// if (skill == NULL)
	// {
	// 	CNetMsg::SP rmsg(new CNetMsg);
	// 	ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_NOCONDITION_SKILL);
	// 	SEND_Q(rmsg, pc->m_desc);
	// 	return false;
	// }

	// if (skill->m_level < needskilllevel)
	// {
	// 	CNetMsg::SP rmsg(new CNetMsg);
	// 	ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_NOCONDITION_SKILL);
	// 	SEND_Q(rmsg, pc->m_desc);
	// 	return false;
	// }

	int needmoney = 50000;

	if (pc->m_inventory.getMoney() < needmoney)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_NOMONEY);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}
	else
	{
		pc->m_inventory.decreaseMoney(needmoney);
	}

	GAMELOG << init("CHANGE JOB", pc)
			<< "2ND JOB" << delim
			<< packet->job << delim
			<< "ORIGINAL STATPOINT" << delim
			<< pc->m_statpt_str << delim
			<< pc->m_statpt_dex << delim
			<< pc->m_statpt_int << delim
			<< pc->m_statpt_con << delim
			<< pc->m_statpt_remain << delim;

	pc->m_job2 = packet->job;

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
#ifdef DEMIGOD
	if ( pc->m_bPhoenix_Char == 1 || pc->m_bPremium_Phoenix == 1 || pc->m_DemiGod == 1)
#else
	if (pc->m_bPhoenix_Char == 1 || pc->m_bPremium_Phoenix == 1)
#endif
	{
		// �Ǵн��� �����ϸ鼭 �߰��� 30 ���� ����Ʈ ������
		pc->m_statpt_remain += 30;
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

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJob(rmsg, pc->m_index, pc->m_job, pc->m_job2);
		pc->m_pArea->SendToCell(rmsg, pc, true);
	}

	if (pc->IsParty())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyMemberChangeJobMsg(rmsg, pc->m_party->GetBossIndex(), pc->m_index, pc->m_job, pc->m_job2);
		SEND_Q(rmsg, gserver->m_helper);
	}

#ifdef GIVE_ITEM_IN_CHANGE_JOB
	// SP����
	// pc->AddExpSP(0, 10000000, false, false, true); ũ���� ������ �������⸦ ���־ ���õ� ���� �۾��� �����Ͽ� ��.
	// ������ ����
	//0:Ÿ��ź, 1:����Ʈ, 2:����, 3:������, 4:�α�, 5:�Ҽ���, 6:����Ʈ������(dummy), 7:EX �α�, 8:EX ������
#ifdef EX_ROGUE
#ifdef EX_MAGE
	const int nGiveItem[JOBCOUNT] = {6893, 6895, 6897, 6899, 6901, 6903, 0, 6901, 6899};
#else
	const int nGiveItem[JOBCOUNT] = {6893, 6895, 6897, 6899, 6901, 6903, 0, 6901};
#endif // EX_MAGE
#else
	const int nGiveItem[6] = {6893, 6895, 6897, 6899, 6901, 6903};
#endif // EX_ROGUE

	CItem* pItem = gserver->m_itemProtoList.CreateItem(nGiveItem[pc->m_job], -1, 0, 0, 1);
	if(pItem == NULL)
	{
		GAMELOG << init("ITEM ERROR") << "ITEM IS NOT EXIST" << "ITEM INDEX" << delim << nGiveItem[pc->m_job] << end;
		return true; // �������� �������� ���ѻ� ������ ����
	}

	if (pc->m_inventory.addItem(pItem) == false)
	{
		delete pItem;
		return true; // �������� �������� ���ѻ� ������ ����
	}
#endif

	#ifdef AUTO_SKILL
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
        if (!cmd.Open() )//|| !cmd1.MoveFirst())
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
        if (!cmd1.Open() )//|| !cmd1.MoveFirst())
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
 
#endif

	return true;
}

bool do_ChangeJobResetReq(CPC* pc, CNetMsg::SP& msg)
{
	RequestClient::changeJobReset* packet = reinterpret_cast<RequestClient::changeJobReset*>(msg->m_buf);

	CNPC* pNpc = (CNPC*)pc->m_pArea->FindCharInCell(pc, packet->npcIndex, MSG_CHAR_NPC, false);
	if (pNpc == NULL || pNpc->IsFlag(NPC_RESETSTAT) == 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_NOT_EXIST_NPC);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	if (pc->m_job2 == 0	|| pc->m_job == JOB_NIGHTSHADOW)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_WRONGMSG);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	LONGLONG statptall = pc->m_statpt_str + pc->m_statpt_dex + pc->m_statpt_int + pc->m_statpt_con;
	LONGLONG needNas = statptall * (LONGLONG)(25000 * pc->m_level / JOB_2ND_LEVEL) + 100000;

	if (pc->m_inventory.getMoney() < needNas)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJobError(rmsg, MSG_CHANGEJOB_ERROR_NOMONEY);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	pc->m_inventory.decreaseMoney(needNas);

	GAMELOG << init("CHANGE JOB", pc)
			<< "2ND JOB" << delim
			<< pc->m_job2 << delim
			<< "NEED MONEY" << delim
			<< needNas << delim
			<< "ORIGINAL STATPOINT" << delim
			<< pc->m_statpt_str << delim
			<< pc->m_statpt_dex << delim
			<< pc->m_statpt_int << delim
			<< pc->m_statpt_con << delim
			<< pc->m_statpt_remain << end;

	// �ʱ�ȭ
	// ����
	pc->m_job2 = 0;

	// ��ų
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

#ifdef DEMIGOD
	if ( pc->m_bPhoenix_Char == 1  || pc->m_bPremium_Phoenix == 1 || pc->m_DemiGod == 1) 
#else
	if (pc->m_bPhoenix_Char == 1 || pc->m_bPremium_Phoenix == 1)
#endif
	{
		
		pc->m_statpt_remain += 30;
	}

	pc->InitStat();

	pc->CalcStatus(true);

	pc->m_hp = pc->m_maxHP;
	pc->m_mp = pc->m_maxMP;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		StatPointRemainMsg(rmsg, pc);
		SEND_Q(rmsg, pc->m_desc);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJobReset(rmsg, pc);
		pc->m_pArea->SendToCell(rmsg, pc, true);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeSkillListMsg(rmsg, pc);
		SEND_Q(rmsg, pc->m_desc);
	}

	if (pc->IsParty())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyMemberChangeJobMsg(rmsg, pc->m_party->GetBossIndex(), pc->m_index, pc->m_job, pc->m_job2);
		SEND_Q(rmsg, gserver->m_helper);
	}

	return true;
}
