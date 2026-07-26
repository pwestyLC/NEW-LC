#include "stdhdrs.h"

#include "../ShareLib/bnf.h"
#include "Server.h"
#include "JumpingSystem.h"
#include "../ShareLib/packetType/ptype_old_do_item.h"
#include "../ShareLib/packetType/ptype_old_do_changejob.h"
#include "../ShareLib/packetType/ptype_old_do_skill.h"
#include "../ShareLib/packetType/ptype_server_to_server.h"

#include "GuildBattleManager.h"

#include "Log.h"
#include "CmdMsg.h"

struct T_Skill 
{
	int			index;
	int			active;
};

CJumpingSystem::CJumpingSystem(CPC* _ch, int _itemIndex)
	: m_pc(_ch), m_itemIndex(_itemIndex), m_jumpingLevel(0), m_rewardIndex(-1)
{
	const CItemProto* _itemProto = gserver->m_itemProtoList.FindIndex(_itemIndex);
	if ( _itemProto )
	{
		m_jumpingLevel	= _itemProto->getItemNum0();
		m_rewardIndex	= _itemProto->getItemNum1();
	}
}

CJumpingSystem::~CJumpingSystem(void)
{
}

bool CJumpingSystem::UnwearItems()
{
	CItem*  itemWear;
    int     iSlotsneeded = 0;
    for (int i = 0; i < COSTUME2_WEARING_START; i++)
    {
        if (m_pc->m_wearInventory.wearItemInfo[i])
            iSlotsneeded++;
    }
    
	if (m_pc->m_inventory.getEmptyCount() < iSlotsneeded)
    {
        CNetMsg::SP rmsg(new CNetMsg);
		SysFullInventoryMsg(rmsg, 0);
        SEND_Q(rmsg, m_pc->m_desc);
        return false;
    }

    for (int i = 0; i < COSTUME2_WEARING_START; i++)
    {
        itemWear = m_pc->m_wearInventory.wearItemInfo[i];
        if (itemWear)
        {
			if (!m_pc->m_wearInventory.DelNormalItem(i)) {
				return false;
			}
			
			CNetMsg::SP rmsg(new CNetMsg);
			WearingMsg(rmsg, m_pc, i, -1, 0);
			m_pc->m_pArea->SendToCell(rmsg, m_pc, false);
        }
    }
	return true;
}




bool CJumpingSystem::learnSkill()  //pwesty fixed
{
    // Remove existing 2nd job skills
    int skillpoint = 0;
    skillpoint += m_pc->m_activeSkillList.RemoveSkillFor2ndJob();
    skillpoint += m_pc->m_passiveSkillList.RemoveSkillFor2ndJob();
    skillpoint += m_pc->m_etcSkillList.RemoveSkillFor2ndJob();

    // Reset stat points
    int totalStats = m_pc->m_statpt_str + m_pc->m_statpt_dex +
        m_pc->m_statpt_int + m_pc->m_statpt_con +
        m_pc->m_statpt_remain;

    m_pc->m_statpt_str = 0;
    m_pc->m_statpt_dex = 0;
    m_pc->m_statpt_int = 0;
    m_pc->m_statpt_con = 0;
    m_pc->m_statpt_remain = (m_pc->m_level - JOB_2ND_LEVEL) * 3 +
        (m_pc->m_level - JOB_2ND_LEVEL) / 2 +
        (JOB_2ND_LEVEL - 1);
    m_pc->m_statpt_remain += totalStats + m_pc->m_stats_addition;

#ifdef DEMIGOD
    if (m_pc->m_bPhoenix_Char == 1 || m_pc->m_bPremium_Phoenix == 1 || m_pc->m_DemiGod == 1)
#else
    if (m_pc->m_bPhoenix_Char == 1 || m_pc->m_bPremium_Phoenix == 1)
#endif
        m_pc->m_statpt_remain += 30;

    GAMELOG << "RESET STATPOINT" << delim
        << m_pc->m_statpt_str << delim
        << m_pc->m_statpt_dex << delim
        << m_pc->m_statpt_int << delim
        << m_pc->m_statpt_con << delim
        << m_pc->m_statpt_remain << end;

    m_pc->InitStat();
    m_pc->CalcStatus(true);

    m_pc->m_hp = m_pc->m_maxHP;
    m_pc->m_mp = m_pc->m_maxMP;

    // Send remaining stat points to client
    {
        CNetMsg::SP rmsg(new CNetMsg);
        StatPointRemainMsg(rmsg, m_pc);
        SEND_Q(rmsg, m_pc->m_desc);
    }

    // Quit group/expedition if necessary
    if (m_pc->m_Exped != nullptr)
    {
        CNetMsg::SP rmsg(new CNetMsg);
        HelperExpedQuitReqMsg(rmsg, m_pc->m_Exped->GetBossIndex(), m_pc->m_index, MSG_EXPED_QUITMODE_NORMAL);
        SEND_Q(rmsg, gserver->m_helper);
        m_pc->m_Exped = nullptr;
    }

    if (m_pc->m_party != nullptr)
    {
        CNetMsg::SP rmsg(new CNetMsg);
        HelperPartyQuitReqMsg(rmsg, m_pc->m_party->GetBossIndex(), m_pc->m_index);
        SEND_Q(rmsg, gserver->m_helper);
    }

    // Load skills from DB
    std::vector<T_Skill> Skill;

    CLCString sql(1024);
    CDBCmd cmd, cmd1, cmd2;
    cmd.Init(&gserver->m_dbdata);
    cmd1.Init(&gserver->m_dbdata);
    cmd2.Init(&gserver->m_dbdata);

    // Current job + 2nd job skills
    sql.Format("SELECT * FROM `t_skill` WHERE `a_job` = %i AND `a_job2` = %i", m_pc->m_job, m_pc->m_job2);
    cmd.SetQuery(sql);
    if (cmd.Open())
    {
        while (cmd.MoveNext())
        {
            T_Skill ski;
            short type;
            cmd.GetRec("a_index", ski.index);
            cmd.GetRec("a_type", type);
            ski.active = (type >= 0 && type <= 2) ? 1 : 0;
            Skill.push_back(ski);
        }
    }

    // Current job + base (2nd job = 0) skills
    sql.Format("SELECT * FROM `t_skill` WHERE `a_job` = %i AND `a_job2` = 0", m_pc->m_job);
    cmd1.SetQuery(sql);
    if (cmd1.Open())
    {
        while (cmd1.MoveNext())
        {
            T_Skill ski;
            short type;
            cmd1.GetRec("a_index", ski.index);
            cmd1.GetRec("a_type", type);
            ski.active = (type >= 0 && type <= 2) ? 1 : 0;
            Skill.push_back(ski);
        }
    }

    m_pc->m_activeSkillList.Clear();
    m_pc->m_passiveSkillList.Clear();

    // Assign skills
    for (auto& ski : Skill)
    {
        sql.Format("SELECT `a_level`, `a_learnItemIndex1`, `a_learnItemCount1` FROM `t_skillLevel` "
            "WHERE `a_learnLevel` <= %i AND `a_index` = %i "
            "ORDER BY `a_level` DESC LIMIT 1",
            m_pc->m_level, ski.index);
        cmd2.SetQuery(sql);
        if (!cmd2.Open() || !cmd2.MoveFirst())
            continue;

        int level = 0;
        int learnItemIndex = 0;
        int learnItemCount = 0;

        if (ski.active == 1)
        {
            cmd2.GetRec("a_level", level);
            if (CSkill* s = gserver->m_skillProtoList.Create(ski.index, level))
                m_pc->m_activeSkillList.Add(s);
        }
        else
        {
            cmd2.GetRec("a_level", level);
            cmd2.GetRec("a_learnItemIndex1", learnItemIndex);
            cmd2.GetRec("a_learnItemCount1", learnItemCount);

            if (learnItemIndex != -1)
            {
                item_search_t vec;
                int sc = m_pc->m_inventory.searchItemByCondition(learnItemIndex, 0, 0, vec);
                if (sc >= learnItemCount)
                    m_pc->m_inventory.deleteItem(vec, learnItemCount);
                else
                    continue; // skip if not enough items
            }

            if (CSkill* s = gserver->m_skillProtoList.Create(ski.index, level))
                m_pc->m_passiveSkillList.Add(s);
        }
    }

    // Send updated skill list to client
    {
        CNetMsg::SP rmsg(new CNetMsg);
        ResponseClient::makeSkillListMsg(rmsg, m_pc);
        SEND_Q(rmsg, m_pc->m_desc);
    }

    // Unsummon elementals
    while (m_pc->m_elementalList)
        m_pc->UnsummonElemental(m_pc->m_elementalList);

    if (m_pc->m_evocationIndex > EVOCATION_NONE)
        m_pc->Unevocation();

    // Guild handling
    if (m_pc->m_guildInfo != nullptr && m_pc->m_guildInfo->guild())
    {
        CGuild* guild = m_pc->m_guildInfo->guild();
        if (guild->boss()->GetPC() == m_pc)
        {
            GuildBattleManager::instance()->delete_banish(guild->index());
            if (GuildBattleManager::instance()->cancel(guild->index()))
            {
                guild->m_isUseTheStashAndSkill = true;

                CNetMsg::SP rmsg(new CNetMsg);
                ServerToServerPacket::makeGuildBattleStashLockOff(rmsg, guild->index());
                SEND_Q(rmsg, gserver->m_helper);
            }
        }

        if (guild->battleState() == GUILD_BATTLE_STATE_ING)
            GuildBattleManager::instance()->giveup(m_pc->m_index);
    }

    return true;
}


bool CJumpingSystem::check(void)
{
	// �⺻ �˻�
	if ( m_pc == NULL )
		return false;

	if ( m_pc->m_teachType == MSG_TEACH_STUDENT_TYPE )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::ItemNotUseMsg(rmsg, MSG_ITEM_USE_ERROR_GUARDIAN);
		SEND_Q(rmsg, m_pc->m_desc);

		return false;
	}

	// ���� ���� >= ������ �����̸� ��� �Ұ���
	if ( m_pc->m_level >= m_jumpingLevel )
		return false;

	// ���� ���� ���� ���� �� ���� ����
	if ( m_rewardIndex > 0 )
	{
		return gserver->m_rewardMgr.setRewardData(m_pc, m_rewardIndex);
	}

	return true;
}

bool CJumpingSystem::jump(void)
{
	if ( m_pc == NULL )
		return false;

	if ( m_jumpingLevel <= 0 )
		return false;

	// ������
	m_pc->m_level = m_jumpingLevel;
	m_pc->LevelUp(true);

	// ĳ���� �ʱ�ȭ
	if ( !initCharacter() )
	{
		return false;
	}

	// ���� ����
	if ( !giveReward() )
	{
		GAMELOG << init("JUMPING SYSTEM")
				<< "GIVE REWARD FAIL" << end;
		return false;
	}

	return true;
}

bool CJumpingSystem::initCharacter(void)
{
	// ���� �ʱ�ȭ
	if ( !initJob() )
	{
		GAMELOG << init("JUMPING SYSTEM")
				<< "INIT JOB FAIL" << end;
		return false;
	}

	// ��ų �ʱ�ȭ
	if ( !initSkill() )
	{
		GAMELOG << init("JUMPING SYSTEM")
				<< "INIT SKILL FAIL" << end;
		return false;
	}

	// ���� �ʱ�ȭ
	if ( !initStat() )
	{
		GAMELOG << init("JUMPING SYSTEM")
				<< "INIT STAT FAIL" << end;
		return false;
	}

	// HP, MP ä���
	m_pc->m_hp = m_pc->m_maxHP;
	m_pc->m_mp = m_pc->m_maxMP;

	return true;
}

bool CJumpingSystem::giveReward(void)
{
	if ( m_rewardIndex > 0 )
	{
		return gserver->m_rewardMgr.doReward(m_pc, m_rewardIndex);
	}

	return true;
}

bool CJumpingSystem::initJob(void)
{
	if ( m_pc->m_job != JOB_NIGHTSHADOW )
		m_pc->m_job2 = 0;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeChangeJob(rmsg, m_pc->m_index, m_pc->m_job, m_pc->m_job2);
		m_pc->m_pArea->SendToCell(rmsg, m_pc, true);
	}

	if (m_pc->IsParty())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyMemberChangeJobMsg(rmsg, m_pc->m_party->GetBossIndex(), m_pc->m_index, m_pc->m_job, m_pc->m_job2);
		SEND_Q(rmsg, gserver->m_helper);
	}

	return true;
}

bool CJumpingSystem::initSkill(void)
{
	// Active Skill �ʱ�ȭ
	m_pc->InitSkill(&m_pc->m_activeSkillList);

	// Passive Skill �ʱ�ȭ
	m_pc->InitSkill(&m_pc->m_passiveSkillList, true);

	CNetMsg::SP rmsg(new CNetMsg);
	ResponseClient::makeSkillListMsg(rmsg, m_pc);
	SEND_Q(rmsg, m_pc->m_desc);

	return true;
}

bool CJumpingSystem::initStat(void)
{
	// ���� ����
	// ���� ����Ʈ �ʱ�ȭ
	if ( m_pc->m_job == JOB_NIGHTSHADOW )
	{
		m_pc->m_statpt_remain = (m_pc->m_level - JOB_2ND_LEVEL) * 3 + (m_pc->m_level - JOB_2ND_LEVEL) / 2 + (JOB_2ND_LEVEL - 1);
	}
	else
	{
		m_pc->m_statpt_remain = m_pc->m_level - 1;
	}

	m_pc->m_statpt_remain += m_pc->m_stats_addition;

	m_pc->m_statpt_str = m_pc->m_statpt_dex = m_pc->m_statpt_int = m_pc->m_statpt_con = 0;

	m_pc->InitStat();
	m_pc->CalcStatus(true);

	CNetMsg::SP rmsg(new CNetMsg);
	StatPointRemainMsg(rmsg, m_pc);
	SEND_Q(rmsg, m_pc->m_desc);

	return true;
}

