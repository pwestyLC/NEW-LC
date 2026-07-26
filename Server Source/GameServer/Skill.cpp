#include <boost/format.hpp>
#include "stdhdrs.h"
#include "SkillUseLog.h"
#include "Server.h"
#include "Skill.h"
#include "../ShareLib/DBCmd.h"
#include "CmdMsg.h"
#include "Log.h"
#include "Battle.h"
#include "../ShareLib/packetType/ptype_old_do_item.h"
#include "../ShareLib/packetType/ptype_old_do_skill.h"
#include "../ShareLib/packetType/ptype_old_extend.h"


///////////////////
// CMagicLevelProto
CMagicLevelProto::CMagicLevelProto(int nPower, int nHitrate)
{
	m_nPowerValue = nPower;
	m_nHitrateValue = nHitrate;
}

//////////////
// CMagicProto
CMagicProto::CMagicProto(int index, char maxlevel, char type, char subtype, char damagetype, char hittype, char attribute, int psp, int ptp, int hsp, int htp, int bTogel, CMagicLevelProto** levelproto)
{
	m_index = index;
	m_maxlevel = maxlevel;
	m_type = type;
	m_subtype = subtype;
	m_damagetype = damagetype;
	m_hittype = hittype;
	m_attribute = attribute;
	m_psp = psp;
	m_ptp = ptp;
	m_hsp = hsp;
	m_htp = htp;
	m_bTogel = bTogel;
	m_levelproto = levelproto;
}

CMagicProto::~CMagicProto()
{
	if (m_levelproto)
	{
		for (int i = 0; i < m_maxlevel; i++)
		{
			delete m_levelproto[i];
			m_levelproto[i] = NULL;
		}
		m_levelproto = NULL;
	}
}

const CMagicLevelProto* CMagicProto::Level(char level) const
{
	if (level < 1 || level > m_maxlevel)
		return NULL;
	else
		return (const CMagicLevelProto*)m_levelproto[level - 1];
}

///////////////////
// CSkillLevelProto

CSkillLevelProto::CSkillLevelProto(int needHP, int needMP, int needGP, int durtime, int hate, int needItemIndex[2], int needItemCount[2], int learnLevel, LONGLONG learnSP, int learnSkillIndex[3], char learnSkillLevel[3], int learnItemIndex[3], int learnItemCount[3], int learnstr, int learndex, int learnint, int learncon, int appMagicIndex[3], char appMagicLevel[3], const CMagicProto* magic[3], char magicLevel[3], LONGLONG learnGP
	, int useCount
	, int targetNum
)
{
	int i;
	m_needHP = needHP;
	m_needMP = needMP;
	m_needGP = needGP;
	m_durtime = durtime;
	m_hate = hate;
	for (i = 0; i < MAX_SKILL_NEED_ITEM; i++)
	{
		m_needItemIndex[i] = needItemIndex[i];
		m_needItemCount[i] = needItemCount[i];
	}
	m_learnLevel = learnLevel;
	m_learnSP = learnSP;
	for (i = 0; i < MAX_SKILL_LEARN_SKILL; i++)
	{
		m_learnSkillIndex[i] = learnSkillIndex[i];
		m_learnSkillLevel[i] = learnSkillLevel[i];
	}
	for (i = 0; i < MAX_SKILL_LEARN_ITEM; i++)
	{
		m_learnItemIndex[i] = learnItemIndex[i];
		m_learnItemCount[i] = learnItemCount[i];
	}
	m_learnstr = learnstr;
	m_learndex = learndex;
	m_learnint = learnint;
	m_learncon = learncon;
	for (i = 0; i < MAX_SKILL_APP_MAGIC; i++)
	{
		m_appMagicIndex[i] = appMagicIndex[i];
		m_appMagicLevel[i] = appMagicLevel[i];
	}
	for (i = 0; i < MAX_SKILL_MAGIC; i++)
	{
		m_magic[i] = magic[i];
		m_magicLevel[i] = magicLevel[i];
	}
	m_learnGP = learnGP;
	m_useCount = useCount;
	m_targetNum = targetNum;
}

//////////////
// CSkillProto
CSkillProto::CSkillProto(int index, int job, int job2, char type, int flag, int sorcerer_flag, char maxLevel, float appRange, float fireRange, float fireRange2, float minRange, char targetType, int useState, int useWeaponType0, int useWeaponType1, int useMagicIndex[3], char useMagicLevel[3], int appState, int appWeaponType0, int appWeaponType1, int readyTime, int stillTime, int fireTime, int reuseTime, int selfparam, int targetparam, CSkillLevelProto** levelproto, int nAPetIndex, int soul_consum, int useWearing, int appWearing, int summonIdx)
{
	int i;

	m_index = index;
	m_job = job;
	m_job2 = job2;
	m_type = type;
	m_flag = flag;
	m_sorcerer_flag = sorcerer_flag;
	m_maxLevel = maxLevel;
	m_appRange = appRange;
	m_fireRange = fireRange;
	m_fireRange2 = fireRange2;
	m_minRange = minRange;
	m_targetType = targetType;
	m_useState = useState;
	m_useWeaponType0 = useWeaponType0;
	m_useWeaponType1 = useWeaponType1;
	for (i = 0; i < MAX_SKILL_USE_MAGIC; i++)
	{
		m_useMagicIndex[i] = useMagicIndex[i];
		m_useMagicLevel[i] = useMagicLevel[i];
	}
	m_applyState = appState;
	m_applyWeaponType0 = appWeaponType0;
	m_applyWeaponType1 = appWeaponType1;
	m_readyTime = readyTime;
	m_stillTime = stillTime;
	m_fireTime = fireTime;
	m_reuseTime = reuseTime;
	m_levelproto = levelproto;
	m_selfparam = selfparam;
	m_targetparam = targetparam;
	m_nAPetIndex = nAPetIndex;
	m_soul_consum = soul_consum;
	m_useWearing = useWearing;
	m_appWearing = appWearing;

#ifdef EXTREME_CUBE_VER2
	m_allowzone = NULL;
#endif // EXTREME_CUBE_VER2
	m_summonIDX = summonIdx;

	//////////////////////////////////////////////////////////////////////////
	switch (m_type)
	{
	case ST_MELEE:
	case ST_RANGE:
	case ST_MAGIC:
	case ST_SUMMON_SKILL:
		is_active_flag = true;
		break;

	default:
		is_active_flag = false;
		break;
	}

	//////////////////////////////////////////////////////////////////////////
	switch (m_type)
	{
	case ST_PASSIVE:
	case ST_GUILD_SKILL_PASSIVE:
	case ST_PET_SKILL_PASSIVE:
		is_passive_flag = true;
		break;

	default:
		is_passive_flag = false;
		break;
	}

	//////////////////////////////////////////////////////////////////////////
	switch (m_type)
	{
	case ST_SUMMON_SKILL:
		is_summon_flag = true;
		break;

	default:
		is_summon_flag = false;
		break;
	}

	is_rvr_zone_not_use = false;
	switch (index)
	{
	case IGNI1_BUF:
	case IGNI2_BUF:
	case IGNI3_BUF:
	case IGNI4_BUF:
	case VELOCITY_BUF:
	case CAST_POTION:
		is_rvr_zone_not_use = true;
		break;
	default:
		is_rvr_zone_not_use = false;
		break;
	}
}

CSkillProto::~CSkillProto()
{
	if (m_levelproto)
	{
		for (int i = 0; i < m_maxLevel; i++)
		{
			delete m_levelproto[i];
			m_levelproto[i] = NULL;
		}
		delete[] m_levelproto;
		m_levelproto = NULL;
	}
#ifdef EXTREME_CUBE_VER2
	if (m_allowzone)
	{
		delete m_allowzone;
		m_allowzone = NULL;
	}
#endif // EXTREME_CUBE_VER2
}

const CSkillLevelProto* CSkillProto::Level(char level) const
{
	if (level < 1 || level > m_maxLevel)
		return NULL;
	else
		return (const CSkillLevelProto*)m_levelproto[(int)level - 1];
}

bool CSkillProto::IsSeal() const
{
	if (m_type == ST_SEAL)
		return true;
	return false;
}

bool CSkillProto::IsSameJob(CPC* pc) const
{
	// ���� �˻�
	if (m_job == pc->m_job)
	{
		if (m_job2)
		{
			if (m_job2 == pc->m_job2)
				return true;
			else
				return false;
		}
		return true;
	}
	else
		return false;
}

bool CSkillProto::IsSameJob(CPet* pet) const
{
	if (pet == NULL)
		return false;

	if (m_job != JOB_PET)
		return false;

	switch (m_job2)
	{
	case JOB_2ND_PET_HORSE:
		if (!(pet->GetPetType() == PET_TYPE_HORSE
			|| pet->GetPetType() == PET_TYPE_BLUE_HORSE
			|| pet->GetPetType() == PET_TYPE_UNKOWN_HORSE))
			return false;
		if (pet->IsMountType())
			return false;
		break;
	case JOB_2ND_PET_DRAGON:
		if (!(pet->GetPetType() == PET_TYPE_DRAGON
			|| pet->GetPetType() == PET_TYPE_PINK_DRAGON
			|| pet->GetPetType() == PET_TYPE_UNKOWN_DRAGON))
			return false;
		if (pet->IsMountType())
			return false;
		break;
	case JOB_2ND_PET_HORSE_MOUNT:
		if (!(pet->GetPetType() == PET_TYPE_HORSE
			|| pet->GetPetType() == PET_TYPE_BLUE_HORSE
			|| pet->GetPetType() == PET_TYPE_UNKOWN_HORSE))
			return false;
		if (!pet->IsMountType())
			return false;
		break;
	case JOB_2ND_PET_DRAGON_MOUNT:
		if (!(pet->GetPetType() == PET_TYPE_DRAGON
			|| pet->GetPetType() == PET_TYPE_PINK_DRAGON
			|| pet->GetPetType() == PET_TYPE_UNKOWN_DRAGON))
			return false;
		if (!pet->IsMountType())
			return false;
		break;
	default:
		return false;
	}

	return true;
}
//#endif

bool CSkillProto::IsSameJob(CAPet* apet) const
{
	// ���� �˻�
	if (!apet)
		return false;

	if (m_job2 != 0 && m_job2 != apet->m_pProto->m_Type)
		return false;

	if (m_nAPetIndex == 0 || m_nAPetIndex == apet->m_pProto->Index())
	{
		return true;
	}
	else
		return false;
}

float CSkillProto::GetFireRange(CCharacter* ch) const
{
	if (IS_PC(ch))
	{
		CPC* pc = TO_PC(ch);
		if (pc->m_wearInventory.wearItemInfo[WEARING_WEAPON])
		{
			if (!pc->m_wearInventory.wearItemInfo[WEARING_WEAPON]->IsWeaponType())
				return m_fireRange;

			int sub = pc->m_wearInventory.wearItemInfo[WEARING_WEAPON]->m_itemProto->getItemSubTypeIdx();
			if (sub == m_useWeaponType0)
				return m_fireRange;
			else if (sub == m_useWeaponType1)
				return m_fireRange2;
			else
				return m_fireRange;
		}
		else
			return m_fireRange;
	}
	else if (IS_NPC(ch))
	{
		// NPC�� ��� ������ų�� �����Ÿ��� ����������� ����
		// ��Ƽ�� ��� 999����
		switch (m_targetType)
		{
		case STT_SELF_RANGE:
			return m_appRange;

		case STT_PARTY_ONE:
		case STT_PARTY_ALL:
			return 999.0f;

		case STT_SELF_ONE:
		case STT_TARGET_ONE:
		case STT_TARGET_RANGE:
		case STT_TARGET_D120:
		case STT_TARGET_RECT:
		default:
			return m_fireRange;
		}
	}
	else if (IS_ELEMENTAL(ch))
	{
		CElemental* elemental = TO_ELEMENTAL(ch);
		if (elemental)
		{
			CPC* pc = elemental->GetOwner();
			if (!pc)
				return m_fireRange;

			if (pc->m_wearInventory.wearItemInfo[WEARING_WEAPON])
			{
				if (!pc->m_wearInventory.wearItemInfo[WEARING_WEAPON]->IsWeaponType())
					return m_fireRange;

				int sub = pc->m_wearInventory.wearItemInfo[WEARING_WEAPON]->m_itemProto->getItemSubTypeIdx();
				if (sub == m_useWeaponType0)
					return m_fireRange;
				else if (sub == m_useWeaponType1)
					return m_fireRange2;
				else
					return m_fireRange;
			}
			else
				return m_fireRange;
		}
		else
			return m_fireRange;
	}
	else if (IS_APET(ch))
	{
		return m_fireRange;
	}
	else
		return 1.0f;
}

float CSkillProto::GetMinRange() const
{
	return m_minRange;
}

int CSkillProto::CheckUseState(CCharacter* ch) const
{
	CPC* pc = NULL;

	if (IS_PC(ch))
		pc = TO_PC(ch);

	if (m_useState & SCT_DEATH)
	{
		if (!DEAD(ch))
			return SCT_DEATH;
	}

	if (pc && (m_useState & SCT_WEAPON))
	{
		// ������
		if (pc->m_wearInventory.wearItemInfo[WEARING_WEAPON] == NULL)
			return SCT_WEAPON;
		// ���� �ƴ�
		if (!pc->m_wearInventory.wearItemInfo[WEARING_WEAPON]->IsWeaponType())
			return SCT_WEAPON;
		// ��� ���� �ƴ�
		int sub = pc->m_wearInventory.wearItemInfo[WEARING_WEAPON]->m_itemProto->getItemSubTypeIdx();
		if ((m_useWeaponType0 >= 0 || m_useWeaponType1 >= 0) && (sub != m_useWeaponType0 && sub != m_useWeaponType1))
			return SCT_WEAPON;
	}

	if (pc && (m_useState & SCT_SHIELD))
	{
		// ������
		if (pc->m_wearInventory.wearItemInfo[WEARING_SHIELD] == NULL)
			return SCT_SHIELD;
		// ���� �ƴ�
		if (pc->m_wearInventory.wearItemInfo[WEARING_SHIELD]->m_itemProto->getItemTypeIdx() != ITYPE_WEAR)
			return SCT_SHIELD;
		if (pc->m_wearInventory.wearItemInfo[WEARING_SHIELD]->m_itemProto->getItemSubTypeIdx() != IWEAR_SHIELD)
			return SCT_SHIELD;
	}

	if (pc)
	{
		switch (m_useState & (SCT_SITDOWN | SCT_STAND))
		{
		case SCT_SITDOWN:
			if (!pc->IsSetPlayerState(PLAYER_STATE_SITDOWN))
				return SCT_SITDOWN;
			break;

		case SCT_STAND:
			if (pc->IsSetPlayerState(PLAYER_STATE_SITDOWN))
				return SCT_STAND;
			break;
		}
	}

	if ((m_useState & SCT_PEACEZONE) && ch->IsInPeaceZone(false))
		return SCT_PEACEZONE;

	// ��ũ�Ͻ� ����϶� ��ũ�Ͻ� ���� ��ų�� �ƴϸ� ��� �Ұ�
	if (pc && !(m_useState & SCT_DARKNESS) && pc->IsSetPlayerState(PLAYER_STATE_DARKNESS))
		return SCT_DARKNESS;

	// ��� ���� �˻� : ȿ�� ����
	if (pc)
	{
		int i;
		for (i = 0; i < MAX_SKILL_USE_MAGIC; i++)
		{
			if (m_useMagicIndex[i] < 0)
				continue;
			if (!pc->m_assist.Find(m_useMagicIndex[i], m_useMagicLevel[i]))
				return -1;
		}
	}

	return 0;
}

#ifdef EXTREME_CUBE_VER2
bool CSkillProto::CheckAllowZone(char zoneindex) const
{
	if (m_allowzone)
	{
		if (m_allowzone->count > 0)
		{
			char i;
			for (i = 0; i < m_allowzone->count; i++)
			{
				if (m_allowzone->zoneindex[(int)i] == zoneindex)
					return true;
			}
			return false;
		}
	}
	return true;
}

bool CSkillProto::LoadAllowZone(const char* strZoneList)
{
	char cAllowZone[10];
	std::vector<char> allowzonelist;
	char allowzonecount;
	while (*strZoneList)
	{
		strZoneList = AnyOneArg(strZoneList, cAllowZone);
		if (*cAllowZone != '\0')
			allowzonelist.push_back(atoi(cAllowZone));
	}

	allowzonecount = (char)allowzonelist.size();
	if (allowzonecount > 0)
	{
		m_allowzone = new SKILLALLOWZONE(allowzonecount);
		std::vector<char>::iterator it = allowzonelist.begin();
		std::vector<char>::iterator endit = allowzonelist.end();
		for (int i = 0; it != endit; ++it, ++i)
		{
			m_allowzone->zoneindex[i] = *(it);
		}
	}
	return true;
}
#endif // EXTREME_CUBE_VER2

//////////////////
// CMagicProtoList
CMagicProtoList::CMagicProtoList()
{
	m_list = NULL;
	m_count = 0;
}

CMagicProtoList::~CMagicProtoList()
{
	if (m_list)
	{
		for (int i = 0; i < m_count; i++)
		{
			delete m_list[i];
			m_list[i] = NULL;
		}
		delete[] m_list;
		m_list = NULL;
	}
}

bool CMagicProtoList::Free()
{
	if (m_list)
	{
		for (int i = 0; i < m_count; i++)
		{
			delete m_list[i];
			m_list[i] = NULL;
		}
		delete[] m_list;
		m_list = NULL;
	}
	return true;
}

bool CMagicProtoList::Load()
{
	CDBCmd cmd1;
	CDBCmd cmd2;
	cmd1.Init(&gserver->m_dbdata);
	cmd2.Init(&gserver->m_dbdata);

	cmd1.SetQuery("SELECT * FROM t_magic ORDER BY a_index");
	if (!cmd1.Open())
		return false;

	int i, j;
	m_count = cmd1.GetRecordCount();
	if (m_count)
	{
		m_list = new CMagicProto * [m_count];
		memset(m_list, 0, sizeof(*m_list) * m_count);

		i = 0;
		while (cmd1.MoveNext())
		{
			int index;
			char maxlevel;
			char type;
			char subtype;
			char damagetype;
			char hittype;
			char attribute;
			int psp;
			int ptp;
			int hsp;
			int htp;
			int bTogel;

			cmd1.GetRec("a_index", index);
			cmd1.GetRec("a_maxlevel", maxlevel);
			cmd1.GetRec("a_type", type);
			cmd1.GetRec("a_subtype", subtype);
			cmd1.GetRec("a_damagetype", damagetype);
			cmd1.GetRec("a_hittype", hittype);
			cmd1.GetRec("a_attribute", attribute);
			cmd1.GetRec("a_psp", psp);
			cmd1.GetRec("a_ptp", ptp);
			cmd1.GetRec("a_hsp", hsp);
			cmd1.GetRec("a_htp", htp);
			cmd1.GetRec("a_togle", bTogel);
			std::string select_magicLevel_query = boost::str(boost::format(
				"SELECT * FROM t_magicLevel WHERE a_index=%d ORDER BY a_level") % index);

			cmd2.SetQuery(select_magicLevel_query);
			if (!cmd2.Open())
				return false;

			CMagicLevelProto** levelproto = new CMagicLevelProto * [maxlevel];
			memset(levelproto, 0, sizeof(*levelproto) * maxlevel);
			j = 0;
			while (cmd2.MoveNext())
			{
				int power;
				int hitrate;

				cmd2.GetRec("a_power", power);
				cmd2.GetRec("a_hitrate", hitrate);

				levelproto[j] = new CMagicLevelProto(power, hitrate);

				j++;
			}

			m_list[i] = new CMagicProto(index, maxlevel, type, subtype, damagetype, hittype, attribute, psp, ptp, hsp, htp, bTogel, levelproto);

			if (Find(m_list[i]->m_index) == NULL)
				map_.insert(map_t::value_type(m_list[i]->m_index, m_list[i]));
			else
				map_[m_list[i]->m_index] = m_list[i];
			i++;
		}
	}

	return true;
}

const CMagicProto* CMagicProtoList::Find(int index)
{
	map_t::iterator it = map_.find(index);
	return (it != map_.end()) ? it->second : NULL;
}

/////////
// CSkill
CSkill::CSkill(const CSkillProto* proto, char level)
{
	m_proto = proto;
	m_level = level;

	m_state = SKILL_CON_NORMAL;
	m_usetime = 0;
	m_targetType = MSG_CHAR_UNKNOWN;
	m_targetIndex = -1;
	m_enable = 1;
	m_toggle = false;
}

bool CSkill::IsReady(CCharacter* ch)
{
	if (m_state != SKILL_CON_NORMAL || m_proto == nullptr)
		return false;
	int reusetime = m_proto->m_reuseTime;
	reusetime += ch->m_magicSpeed;

#if defined(BUGFIX_GUILD_SKILL_COOLTIME) || defined(SKILL_TYPE_NO_COOL_TIME)
	if (1
#ifdef BUGFIX_GUILD_SKILL_COOLTIME
		&& !(m_proto->m_flag & SF_GUILD)
#endif
#ifdef SKILL_TYPE_NO_COOL_TIME
		&& !(m_proto->m_applyState & SCT_NO_COOL_TIME)
#endif
		)
#endif

		if (IS_PC(ch))
		{
			CPC* pPC = TO_PC(ch);
			if (pPC->m_opDecreaseSkillDelay > 0 || pPC->m_skillCooltime != 0)
			{
				// Use the new config-aware GetSkillCooldownValue() to calculate cooldown reduction
				// This respects PVP/PVE percentages instead of hardcoded formula
				int prob = gserver->GetSkillCooldownValue(pPC->m_opDecreaseSkillDelay, pPC->m_skillCooltime, pPC);

#if defined(BUGFIX_GUILD_SKILL_COOLTIME) || defined(SKILL_TYPE_NO_COOL_TIME)
				if (1
#ifdef BUGFIX_GUILD_SKILL_COOLTIME
					&& !(m_proto->m_flag & SF_GUILD)
#endif
#ifdef SKILL_TYPE_NO_COOL_TIME
					&& !(m_proto->m_applyState & SCT_NO_COOL_TIME)
#endif
					)
#endif 
					reusetime -= reusetime * prob / 100;
			}
		}
	if (IS_ELEMENTAL(ch))
	{
		CElemental* pEle = TO_ELEMENTAL(ch);
		if (pEle->GetOwner()->m_opDecreaseSkillDelay > 0 || pEle->GetOwner()->m_skillCooltime != 0)
		{
			// Use the new config-aware GetSkillCooldownValue() for elemental owner cooldown
			int prob = gserver->GetSkillCooldownValue(pEle->GetOwner()->m_opDecreaseSkillDelay, pEle->GetOwner()->m_skillCooltime, pEle->GetOwner());
			reusetime -= reusetime * (prob) / 100;
		}
	}
	if (IS_APET(ch))
	{
		reusetime = reusetime / 100;
	}

	if (reusetime < 0)
		reusetime = 0;
	

	if (this->m_proto->m_flag & SF_GUILD)
	{
		
		if (IS_PC(ch))
		{
			CPC* pc = TO_PC(ch);
			if (pc->m_guildInfo == NULL)
			{
				
				LOG_ERROR("HACKING? : invalid skill guildinfo. char_index[%d], skill_index[%d]", pc->m_index, this->m_proto->m_index);
				pc->m_desc->Close("Invalid guildInfo");
				return false;
			}
			GUILD_SKILL_USETIME_DATA::iterator it = m_gskill_usetime.find(pc->m_index);

			if (it == m_gskill_usetime.end())
			{
				//¾øÀ¸¸é
				return true;
			}
			else
			{
				//ÀÖÀ¸¸é
				if (gserver->m_pulse - it->second < reusetime)
					return false;// return false; // fuckmylife skill hack
			}
		}
	}
	else
	{
		if (m_usetime > 0)
		{
			if (IS_PC(ch)) {
				if (gserver->m_pulse - m_usetime < reusetime)
					return true;// return false; // fuckmylife skill hack
			}
			else {
				if (gserver->m_pulse - m_usetime < reusetime)
					return false;// return false; //npc skill hack fix #lol
			}
		}
	}


	//m_usetime = 0;
	return true;
}

void CSkill::Ready(CCharacter* tch)
{
	if (tch && tch->IsInvisible() && m_proto->m_index != 131)
		tch->CancelInvisible();

	m_state = SKILL_CON_READY;

	
	if (this->m_proto->m_flag & SF_GUILD)
	{
		if (IS_PC(tch) == false)
			return;

		CPC* pc = TO_PC(tch);
		if (pc->m_guildInfo == NULL)
		{
			//��ŷ�õ� ���� ����
			LOG_ERROR("HACKING? : invalid skill guildinfo. char_index[%d], skill_index[%d]", pc->m_index, this->m_proto->m_index);
			pc->m_desc->Close("Invalid guildInfo");
			return;
		}

		GUILD_SKILL_USETIME_DATA::iterator it = m_gskill_usetime.find(pc->m_index);
		if (it == m_gskill_usetime.end())
		{
			//������ �߰�
			m_gskill_usetime.insert(GUILD_SKILL_USETIME_DATA::value_type(pc->m_index, gserver->m_pulse));
		}
		else
		{
			//������ update
			it->second = gserver->m_pulse;
		}
	}

	m_usetime = gserver->m_pulse;
	if (tch)
	{
		m_targetType = tch->m_type;
		m_targetIndex = tch->m_index;
	}
	else
	{
		m_targetType = MSG_CHAR_UNKNOWN;
		m_targetIndex = -1;
	}
}

void CSkill::Fire()
{
	m_state = SKILL_CON_FIRE;
}

void CSkill::Cancel(CCharacter* pCharSkill)
{
	// ���� ��ų�� ����ϴ� ���¿����� ���� ��Ų��.
	if (IS_PC(pCharSkill))
	{
		CPC* pPC = TO_PC(pCharSkill);
		if (pPC && pPC->IsSetPlayerState(PLAYER_STATE_SKILL) && pPC->m_pArea)
		{
			{
				CNetMsg::SP rmsg(new CNetMsg);
				pPC->ResetPlayerState(PLAYER_STATE_SKILL);
				ExPlayerStateChangeMsg(rmsg, pPC);
				pPC->m_pArea->SendToCell(rmsg, pPC, true);
			}

			// ��ų�� Ÿ���� ã�´�
			CCharacter* target = NULL;
			target = pPC->m_pArea->FindCharInCell(pPC, m_targetIndex, m_targetType, false);

			if (target && m_proto)
				target->m_assist.CureBySkillIndex(m_proto->m_index);
		}
	}

	m_state = SKILL_CON_NORMAL;
	m_targetType = MSG_CHAR_UNKNOWN;
	m_targetIndex = -1;
	if (IS_NPC(pCharSkill))
	{
		CNPC* pNPC = TO_NPC(pCharSkill);
		int i;
		for (i = 0; i < MAX_NPC_SKILL; i++)
		{
			if (this == pNPC->m_skills[i])
				return;
		}
		delete this;
	}
}

//////////////////
// CSkillProtoList
CSkillProtoList::CSkillProtoList()
{
	m_list = NULL;
	m_count = 0;
}

CSkillProtoList::~CSkillProtoList()
{
	if (m_list)
	{
		for (int i = 0; i < m_count; i++)
		{
			delete m_list[i];
			m_list[i] = NULL;
		}
		delete[] m_list;
		m_list = NULL;
	}
}

bool CSkillProtoList::Free()
{
	if (m_list)
	{
		for (int i = 0; i < m_count; i++)
		{
			delete m_list[i];
			m_list[i] = NULL;
		}
		delete[] m_list;
		m_list = NULL;
	}
	return true;
}

bool CSkillProtoList::Load()
{
	CDBCmd cmd1;
	CDBCmd cmd2;
	cmd1.Init(&gserver->m_dbdata);
	cmd2.Init(&gserver->m_dbdata);
	cmd1.SetQuery("SELECT * FROM t_skill WHERE a_job!=-1 ORDER BY a_index");
	if (!cmd1.Open())
		return false;
	m_count = cmd1.GetRecordCount();
	if (m_count)
	{
		m_list = new CSkillProto * [m_count];
		memset(m_list, 0, sizeof(*m_list) * m_count);
	}

	int i, j;
	i = 0;
	while (cmd1.MoveNext())
	{
		int index;
		int job;
		int job2 = 0;
		char type;
		int flag;
		int sorcerer_flag;
		char maxLevel;
		float appRange;
		float fireRange;
		float fireRange2;
		float minRange;
		char targetType;
		char targetNum;
		int useState;
		int useWeapon0;
		int useWeapon1;
		int useMagicIndex[3];
		char useMagicLevel[3];
		int appState;
		int appWeapon0;
		int appWeapon1;
		int readyTime;
		int stillTime;
		int fireTime;
		int reuseTime;
		int selfparam;
		int targetparam;
		CSkillLevelProto** levelproto;
		int	nAPetIndex;
		int soul_consum;
		int useWearing;
		int appWearing;
		int summonIDX;
#ifdef EXTREME_CUBE_VER2
		CLCString allowzone(50);
#endif // EXTREME_CUBE_VER2

		cmd1.GetRec("a_index", index);
		cmd1.GetRec("a_job", job);
		cmd1.GetRec("a_job2", job2);
		cmd1.GetRec("a_type", type);
		cmd1.GetRec("a_flag", flag);
		cmd1.GetRec("a_sorcerer_flag", sorcerer_flag);
		cmd1.GetRec("a_maxLevel", maxLevel);
		cmd1.GetRec("a_appRange", appRange);
		cmd1.GetRec("a_fireRange", fireRange);
		cmd1.GetRec("a_fireRange2", fireRange2);
		cmd1.GetRec("a_minRange", minRange);
		cmd1.GetRec("a_targetType", targetType);
		cmd1.GetRec("a_targetNum", targetNum);
		cmd1.GetRec("a_useState", useState);
		cmd1.GetRec("a_useWeaponType0", useWeapon0);
		cmd1.GetRec("a_useWeaponType1", useWeapon1);
		cmd1.GetRec("a_useMagicIndex1", useMagicIndex[0]);
		cmd1.GetRec("a_useMagicLevel1", useMagicLevel[0]);
		cmd1.GetRec("a_useMagicIndex2", useMagicIndex[1]);
		cmd1.GetRec("a_useMagicLevel2", useMagicLevel[1]);
		cmd1.GetRec("a_useMagicIndex3", useMagicIndex[2]);
		cmd1.GetRec("a_useMagicLevel3", useMagicLevel[2]);
		cmd1.GetRec("a_appState", appState);
		cmd1.GetRec("a_appWeaponType0", appWeapon0);
		cmd1.GetRec("a_appWeaponType1", appWeapon1);
		cmd1.GetRec("a_readyTime", readyTime);
		cmd1.GetRec("a_stillTime", stillTime);
		cmd1.GetRec("a_fireTime", fireTime);
		cmd1.GetRec("a_reuseTime", reuseTime);
		cmd1.GetRec("a_selfparam", selfparam);
		cmd1.GetRec("a_targetparam", targetparam);
		cmd1.GetRec("a_apet_index", nAPetIndex);
		cmd1.GetRec("a_soul_consum", soul_consum);
		cmd1.GetRec("a_use_needWearingType", useWearing);
		cmd1.GetRec("a_app_needWearingType", appWearing);

#ifdef EXTREME_CUBE_VER2
		cmd1.GetRec("a_allowzone", allowzone);
#endif // EXTREME_CUBE_VER2
		cmd1.GetRec("a_summon_idx", summonIDX);
		std::string select_skillLevel_query = boost::str(boost::format(
			"SELECT * FROM t_skillLevel WHERE a_index=%d ORDER BY a_level") % index);
		cmd2.SetQuery(select_skillLevel_query);
		if (!cmd2.Open())
			return false;

		levelproto = new CSkillLevelProto * [(int)maxLevel];
		memset(levelproto, 0, sizeof(*levelproto) * maxLevel);
		j = 0;
		while (cmd2.MoveNext())
		{
			int needHP;
			int needMP;
			int needGP;
			int durtime;
			int hate;
			int needItemIndex[2];
			int needItemCount[2];
			int learnLevel;
			LONGLONG learnSP;
			int learnSkillIndex[3];
			char learnSkillLevel[3];
			int learnItemIndex[3];
			int learnItemCount[3];
			int appMagicIndex[3];
			char appMagicLevel[3];
			int magicIndex[3];
			char magicLevel[3];
			int learnstr = 0;
			int learndex = 0;
			int learnint = 0;
			int learncon = 0;
			LONGLONG learnGP;
			int useCount;
			int targetNum;

			cmd2.GetRec("a_needHP", needHP);
			cmd2.GetRec("a_needMP", needMP);
			cmd2.GetRec("a_needGP", needGP);
			cmd2.GetRec("a_durtime", durtime);
			cmd2.GetRec("a_hate", hate);
			cmd2.GetRec("a_needItemIndex1", needItemIndex[0]);
			cmd2.GetRec("a_needItemCount1", needItemCount[0]);
			cmd2.GetRec("a_needItemIndex2", needItemIndex[1]);
			cmd2.GetRec("a_needItemCount2", needItemCount[1]);
			cmd2.GetRec("a_learnLevel", learnLevel);
			cmd2.GetRec("a_learnSP", learnSP);
			cmd2.GetRec("a_learnSkillIndex1", learnSkillIndex[0]);
			cmd2.GetRec("a_learnSkillLevel1", learnSkillLevel[0]);
			cmd2.GetRec("a_learnSkillIndex2", learnSkillIndex[1]);
			cmd2.GetRec("a_learnSkillLevel2", learnSkillLevel[1]);
			cmd2.GetRec("a_learnSkillIndex3", learnSkillIndex[2]);
			cmd2.GetRec("a_learnSkillLevel3", learnSkillLevel[2]);
			cmd2.GetRec("a_learnItemIndex1", learnItemIndex[0]);
			cmd2.GetRec("a_learnItemCount1", learnItemCount[0]);
			cmd2.GetRec("a_learnItemIndex2", learnItemIndex[1]);
			cmd2.GetRec("a_learnItemCount2", learnItemCount[1]);
			cmd2.GetRec("a_learnItemIndex3", learnItemIndex[2]);
			cmd2.GetRec("a_learnItemCount3", learnItemCount[2]);
			cmd2.GetRec("a_appMagicIndex1", appMagicIndex[0]);
			cmd2.GetRec("a_appMagicLevel1", appMagicLevel[0]);
			cmd2.GetRec("a_appMagicIndex2", appMagicIndex[1]);
			cmd2.GetRec("a_appMagicLevel2", appMagicLevel[1]);
			cmd2.GetRec("a_appMagicIndex3", appMagicIndex[2]);
			cmd2.GetRec("a_appMagicLevel3", appMagicLevel[2]);
			cmd2.GetRec("a_magicIndex1", magicIndex[0]);
			cmd2.GetRec("a_magicLevel1", magicLevel[0]);
			cmd2.GetRec("a_magicIndex2", magicIndex[1]);
			cmd2.GetRec("a_magicLevel2", magicLevel[1]);
			cmd2.GetRec("a_magicIndex3", magicIndex[2]);
			cmd2.GetRec("a_magicLevel3", magicLevel[2]);
			cmd2.GetRec("a_learnstr", learnstr);
			cmd2.GetRec("a_learndex", learndex);
			cmd2.GetRec("a_learnint", learnint);
			cmd2.GetRec("a_learncon", learncon);
			cmd2.GetRec("a_learnGP", learnGP);
			cmd2.GetRec("a_use_count", useCount);
			cmd2.GetRec("a_targetNum", targetNum);

			// ȿ�� ����Ʈ���� �ش� ȿ�� ã��
			const CMagicProto* magic[3];
			magic[0] = gserver->m_magicProtoList.Find(magicIndex[0]);
			magic[1] = gserver->m_magicProtoList.Find(magicIndex[1]);
			magic[2] = gserver->m_magicProtoList.Find(magicIndex[2]);

			levelproto[j] = new CSkillLevelProto(needHP, needMP, needGP, durtime, hate, needItemIndex, needItemCount, learnLevel, learnSP, learnSkillIndex, learnSkillLevel, learnItemIndex, learnItemCount, learnstr, learndex, learnint, learncon, appMagicIndex, appMagicLevel, magic, magicLevel, learnGP
				, useCount
				, targetNum
			);
			j++;
		}
		m_list[i] = new CSkillProto(index, job, job2, type, flag, sorcerer_flag, maxLevel, appRange, fireRange, fireRange2, minRange, targetType, useState, useWeapon0, useWeapon1, useMagicIndex, useMagicLevel, appState, appWeapon0, appWeapon1, readyTime, stillTime, fireTime, reuseTime, selfparam, targetparam, levelproto, nAPetIndex, soul_consum, useWearing, appWearing, summonIDX);

#ifdef EXTREME_CUBE_VER2
		m_list[i]->LoadAllowZone((const char*)allowzone);
#endif // EXTREME_CUBE_VER2

		map_.insert(map_t::value_type(m_list[i]->m_index, m_list[i]));

		i++;
	}

	return true;
}

const CSkillProto* CSkillProtoList::Find(int skillIndex)
{
	map_t::iterator it = map_.find(skillIndex);
	return (it != map_.end()) ? it->second : NULL;
}

CSkill* CSkillProtoList::Create(int skillIndex, int level)
{
	const CSkillProto* proto = Find(skillIndex);
	if (proto == NULL)
		return NULL;
	if (proto->Level(level) == NULL)
		return NULL;

	return new CSkill(proto, level);
}

/////////////////
// CSkillListNode
CSkillListNode::CSkillListNode(CSkill* skill)
{
	m_skill = skill;
	m_prev = m_next = NULL;
	m_wearPos = 0;
}

CSkillListNode* CSkillListNode::prev()
{
	return m_prev;
}

void CSkillListNode::prev(CSkillListNode* p)
{
	m_prev = p;
}

CSkillListNode* CSkillListNode::next()
{
	return m_next;
}

void CSkillListNode::next(CSkillListNode* p)
{
	m_next = p;
}

CSkill* CSkillListNode::skill()
{
	return m_skill;
}

void CSkillListNode::skill(CSkill* p)
{
	m_skill = p;
}

/////////////
// CSkillList
CSkillList::CSkillList()
{
	m_head = m_tail = NULL;
	m_count = 0;
}

CSkillList::~CSkillList()
{
	Clear();
}

bool CSkillList::Add(CSkill*& skill)
{
	if (skill == NULL)
		return false;

	CSkill* p = Find(skill->m_proto->m_index);
	if (p)
	{
		p->m_level = skill->m_level;
		delete skill;
		skill = p;
		skill->m_enable = 1;
		return true;
	}
	else
	{
		CSkillListNode* node = new CSkillListNode(skill);

		if (m_head)
		{
			m_tail->next(node);
			node->prev(m_tail);
			m_tail = node;
			m_count++;
			return true;
		}
		else
		{
			m_head = m_tail = node;
			m_count = 1;
			return true;
		}
	}
}

bool CSkillList::Remove(CSkill* skill)
{
	if (skill == NULL)
		return false;

	CSkillListNode* pNode = m_head;

	while (pNode)
	{
		if (pNode->skill()->m_proto->m_index == skill->m_proto->m_index)
		{
			CSkillListNode* pPrev = pNode->prev();
			CSkillListNode* pNext = pNode->next();

			if (pPrev)
			{
				if (pNext)
				{
					pPrev->next(pNext);
					pNext->prev(pPrev);
				}
				else
				{
					pPrev->next(NULL);
					m_tail = pPrev;
				}
			}
			else
			{
				if (pNext)
				{
					pNext->prev(NULL);
					m_head = pNext;
				}
				else
				{
					m_head = m_tail = NULL;
				}
			}

			pNode->prev(NULL);
			pNode->next(NULL);

			delete pNode;
			pNode = NULL;

			m_count--;

			break;
		}
		pNode = pNode->next();
	}
	return true;
}

CSkill* CSkillList::Find(int index)
{
	CSkillListNode* p = m_head;
	while (p)
	{
		if (p->skill()->m_proto->m_index == index)
			return p->skill();
		else
			p = p->next();
	}

	return NULL;
}

CSkillListNode* CSkillList::FindNode(int index)
{
	CSkillListNode* p = m_head;
	while (p)
	{
		if (p->skill()->m_proto->m_index == index)
			return p;
		else
			p = p->next();
	}

	return NULL;
}

int CSkillList::count()
{
	return m_count;
}

char* CSkillList::GetIndexString(char* buf)
{
	*buf = '\0';
	CSkillListNode* p = m_head;
	while (p)
	{
		IntCat(buf, p->skill()->m_proto->m_index, true);
		p = p->next();
	}
	return buf;
}

void CSkillList::GetIndexString(std::string& bnf)
{
	bnf = "";
	CSkillListNode* p = m_head;
	while (p)
	{
		bnf += boost::str(boost::format(" %d") % p->skill()->m_proto->m_index);
		p = p->next();
	}
}


char* CSkillList::GetLevelString(char* buf)
{
	*buf = '\0';
	CSkillListNode* p = m_head;
	while (p)
	{
		IntCat(buf, p->skill()->m_level, true);
		p = p->next();
	}
	return buf;
}

void CSkillList::GetLevelString(std::string& bnf)
{
	bnf = "";
	CSkillListNode* p = m_head;
	while (p)
	{
		bnf += boost::str(boost::format(" %d") % (int)p->skill()->m_level);
		p = p->next();
	}
}


void* CSkillList::GetHeadPosition()
{
	return (void*)m_head;
}

CSkill* CSkillList::GetNext(void*& p)
{
	CSkillListNode* node = (CSkillListNode*)p;

	if (node == NULL)
	{
		p = NULL;
		return NULL;
	}

	p = (void*)node->next();
	return node->skill();
}

int CSkillList::RemoveSkillFor2ndJob()
{
	CSkillListNode* p;
	CSkillListNode* pn = m_head;

	LONGLONG spendSkillPoint = 0;
	int skillLevel = 0;

	while ((p = pn))
	{
		pn = p->next();

		CSkill* s = p->skill();

		if (s->m_proto->Get2ndJob())
		{
			if (p->prev())
			{
				p->prev()->next(p->next());
			}
			if (p->next())
			{
				p->next()->prev(p->prev());
			}
			if (p == m_head)
				m_head = p->next();
			if (p == m_tail)
				m_tail = p->prev();
			m_count--;
			p->next(NULL);
			p->prev(NULL);

			skillLevel = s->m_level;
			for (; skillLevel > 0; skillLevel--)
			{
				spendSkillPoint += s->m_proto->Level(skillLevel)->m_learnSP * 10000;
			}
			delete p;
		}
	}

	return spendSkillPoint;
}

void CSkillList::Clear()
{
	m_count = 0;
	while (m_head)
	{
		CSkillListNode* node = m_head->next();
		delete m_head;
		m_head = node;
	}
	m_head = m_tail = NULL;
}

void CSkillList::clearReadySkill()
{
	CSkillListNode* p = m_head;
	while (p)
	{
		CSkill* pSkill = p->skill();

		if (pSkill->m_state == SKILL_CON_READY)
		{
			pSkill->m_state = SKILL_CON_NORMAL;
			pSkill->m_usetime = 0;
		}

		p = p->next();
	}
}

bool CSkillList::AddOptionSkill(CSkill* skill, int prob, int wearPos)
{
	if (skill == NULL)
		return false;

	CSkill* p = Find(skill->m_proto->m_index);
	CSkillListNode* node = FindNode(skill->m_proto->m_index);

	//�̹� ��ϵ� ��ų�� ���
	if (node)
	{
		//���� ����̸� return;
		if (node->m_wearPos & (1 << wearPos))
			return false;
		//�ٸ� ����̸�
		else
		{
			p->m_optionSkillProb += prob;
			node->m_wearPos |= (1 << wearPos);
			return true;
		}
	}
	//���� ��ϵǴ� ��ų�� ���
	else
	{
		skill->m_optionSkillProb = prob;
		CSkillListNode* node = new CSkillListNode(skill);
		node->m_wearPos |= (1 << wearPos);

		if (m_head)			//�̹� �ϳ� �̻��� ��ų�� �ִ� ���.
		{
			m_tail->next(node);
			node->prev(m_tail);
			m_tail = node;
			m_count++;
			return true;
		}
		else				//�ɼ� ��ų�� �ϳ��� ��� �Ǿ� ���� ���� ���.
		{
			m_head = m_tail = node;
			m_count = 1;
			return true;
		}
	}
}

///////////////////////
// ApplySkill Functions

/////////////////////
// Function name	: ApplyMagic
// Description	    : ȿ�� ����
// Argument         : CCharacter* ch
//                  : ����ϴ� ĳ���� ĳ����
// Argument         : CCharacter* tch
//                  : ����Ǵ� ĳ����
// Argument         : const CMagicProto* magic
//                  : ȿ�� ������
// Argument         : const CMagicLevelProto* magiclevel
//                  : ȿ�� ���� ����
// Argument         : bool& bApply
//                  : ȿ�� ���� ����, �����ϸ� true, �ƴϸ� false�� ���õ�
void ApplyMagic(CCharacter* ch, CCharacter* tch, CSkill* skill, int magicindex, bool bForce, bool& bApply)
{
	const CSkillProto* proto = skill->m_proto;
	if (proto == NULL)
		return;
	const CSkillLevelProto* levelproto = proto->Level(skill->m_level);
	if (levelproto == NULL)
		return;

	if (magicindex < 0 || magicindex >= MAX_SKILL_MAGIC)
		return;

	const CMagicProto* magic = levelproto->m_magic[magicindex];
	if (magic == NULL)
		return;

	const CMagicLevelProto* magiclevel = magic->Level(levelproto->m_magicLevel[magicindex]);
	if (magiclevel == NULL)
		return;

	int currentSkillLevel = tch->m_assist.FindBySkillIndex(proto->m_index);
	if (currentSkillLevel != 0)
	{
		// ��ų�� �ߺ��� ���
		// rvr ��ų ���� ��쿡�� ���������� ó�� ������ ���Ƶ� ���� ���� ��ų�� ���� ���Ѿ� �Ѵ�.
		if (((proto->m_index != 1756) && (proto->m_index != 1757)) && (skill->m_level < currentSkillLevel))
			return;
	}

	if (IS_PET(tch))
	{
		if (proto->m_flag & SF_HELP)
			return;
		if (levelproto->m_durtime != 0)
			return;
	}
	//#endif
		// ���ְ̹� ȥ���� NPC���Ը� ���
	if (magic->m_type == MT_ASSIST &&
		(magic->m_subtype == MST_ASSIST_TAMING ||
			magic->m_subtype == MST_ASSIST_CONFUSED ||
			magic->m_subtype == MST_ASSIST_MERCENARY ||
			magic->m_subtype == MST_ASSIST_TRAP ||
			magic->m_subtype == MST_ASSIST_SUICIDE ||
			magic->m_subtype == MST_ASSIST_SOUL_TOTEM_BUFF ||
			magic->m_subtype == MST_ASSIST_SOUL_TOTEM_ATTK ||
			magic->m_subtype == MST_ASSIST_TOTEM_ITEM_BUFF ||
			magic->m_subtype == MST_ASSIST_TOTEM_ITEM_ATTK))
	{
		if (!IS_NPC(tch))
			return;
	}

	if (bForce == false)
	{
		bApply = false;
		return;
	}

	// ���� �Ǵ�
#ifdef ENABLE_ROGUE_SKILL125_BRZ
	if (!bForce && SelectHitType(ch, tch, MSG_DAMAGE_MAGIC, HITTYPE_MISS | HITTYPE_NORMAL, magic, magiclevel, (skill->m_proto->m_flag & SF_NOTHELP) ? true : false, skill->m_level) == HITTYPE_MISS)
#else
	if (!bForce && SelectHitType(ch, tch, MSG_DAMAGE_MAGIC, HITTYPE_MISS | HITTYPE_NORMAL, magic, magiclevel, (skill->m_proto->m_flag & SF_NOTHELP) ? true : false) == HITTYPE_MISS)
#endif // ENABLE_ROGUE_SKILL125_BRZ
	{
#ifdef ENABLE_ROGUE_SKILL125_BRZ
		if (magic->m_index != 173)
#endif // ENABLE_ROGUE_SKILL125_BRZ
			bApply = true;
		return;
	}

	if (bForce)
	{
		if (!((magic->m_type == MT_RECOVER) && (magic->m_subtype == MST_RECOVER_EXP || magic->m_subtype == MST_RECOVER_SP)))
		{
			bApply = true;
		}
	}

	int nPowerValue = magiclevel->m_nPowerValue;
	// ����, ����� �Ķ���� �߰�
	nPowerValue = nPowerValue * CalcSkillParam(ch, tch, magic->m_psp, magic->m_ptp) / 100;

	// ��ȿ�� ���� ȿ����
	switch (magic->m_type)
	{
	case MT_ASSIST:
		switch (magic->m_subtype)
		{
			// warning �߻��ϴ� �� ���ֱ� ���� �ӽ� �ڵ�
		case MST_ASSIST_POISON:
			break;

		case MST_ASSIST_SAFEGUARD:
			if (IS_PC(tch))
			{
				// PC���Ը� ���� ����
				CPC* pc = TO_PC(tch);
				if (pc != NULL)
				{
					//pc->m_bImmortal = true;
					pc->m_assist.m_state |= AST_SAFEGUARD;
					//					pc->m_bChangeStatus = true;
					//					CharStatusMsg(rmsg, tch, AST_SAFEGUARD);
					//					tch->m_pArea->SendToCell(rmsg, tch, true);
				}
			}
			break;
		case MST_ASSIST_CONFUSED:
			if (IS_NPC(tch))
			{
				CNPC* pNPC = TO_NPC(tch);
				if (pNPC)
				{
					pNPC->Set_MobFlag(STATE_MONSTER_CONFUSION);
					bApply = true;
				}
			}
			break;

		case MST_ASSIST_TAMING:
			// ���̹��� �Ǵ� npc�� ������ �־� �־�� �Ѵ�.
			if (IS_NPC(tch) && (IS_PC(ch) || IS_APET(ch)))
			{
				CNPC* pNPC = TO_NPC(tch);
				CPC* pPC = TO_PC(ch);
				if (IS_APET(ch))
					pPC = TO_APET(ch)->GetOwner();

				if (pNPC && pPC)
				{
					if (pPC->AddSlave(pNPC))
					{
						pNPC->SetOwner(pPC);
						pNPC->Set_MobFlag(STATE_MONSTER_TAMING);
						bApply = true;
					}
				}
			}
			break;

		case MST_ASSIST_DARKNESS_MODE:
			if (IS_PC(ch))
			{
				CPC* pPC = TO_PC(ch);

				if (pPC && ch->m_pArea)
				{
					if (pPC->IsSetPlayerState(PLAYER_STATE_DARKNESS))
						pPC->ResetPlayerState(PLAYER_STATE_DARKNESS);
					else
						pPC->SetPlayerState(PLAYER_STATE_DARKNESS);

					CNetMsg::SP rmsg(new CNetMsg);
					ExPlayerStateChangeMsg(rmsg, pPC);
					ch->m_pArea->SendToCell(rmsg, ch, true);
					bApply = true;
				}
			}
			break;

		case MST_ASSIST_AURA_DARKNESS:
		case MST_ASSIST_AURA_WEAKNESS:
		case MST_ASSIST_AURA_ILLUSION:
			// ������ ������ �ߵ��Ǿ����� �����ش�. ��� �� ������ ���´�.
			ch->m_assist.CureAssist(MST_ASSIST_AURA_DARKNESS, 99);
			ch->m_assist.CureAssist(MST_ASSIST_AURA_WEAKNESS, 99);
			ch->m_assist.CureAssist(MST_ASSIST_AURA_ILLUSION, 99);
			bApply = true;
			break;
		case MST_ASSIST_MERCENARY:
			if (IS_NPC(tch) && IS_PC(ch))
			{
				CNPC* pNPC = TO_NPC(tch);
				CPC* pPC = TO_PC(ch);
				if (pNPC && pPC)
				{
					if (pNPC->GetOwner() != NULL)
					{
						bApply = false;
					}
					else
					{
						pNPC->SetOwner(pPC);
						pPC->SetSummonNpc(SUMMON_NPC_TYPE_MERCENARY, pNPC);
						pNPC->Set_MobFlag(STATE_MONSTER_MERCENARY);
						bApply = true;
					}
				}
			}
			break;
		case MST_ASSIST_SOUL_TOTEM_BUFF:
			if (IS_NPC(tch) && IS_PC(ch))
			{
				CNPC* pNPC = TO_NPC(tch);
				CPC* pPC = TO_PC(ch);

				pNPC->Set_MobFlag(STATE_MONSTER_TOTEM_BUFF);
				pNPC->SetOwner(pPC);
				bApply = true;
			}
			break;

		case MST_ASSIST_SOUL_TOTEM_ATTK:
			if (IS_NPC(tch) && IS_PC(ch))
			{
				CNPC* pNPC = TO_NPC(tch);
				CPC* pPC = TO_PC(ch);
				pNPC->Set_MobFlag(STATE_MONSTER_TOTEM_ATTK);
				pNPC->SetOwner(pPC);
				bApply = true;
			}
			break;

		case MST_ASSIST_TRAP:
			if (IS_NPC(tch) && IS_PC(ch))
			{
				CNPC* pNPC = TO_NPC(tch);
				CPC* pPC = TO_PC(ch);
				pNPC->Set_MobFlag(STATE_MONSTER_TRAP);
				pNPC->SetOwner(pPC);
				bApply = true;
			}
			break;

		case MST_ASSIST_PARASITE:
			if (IS_NPC(tch) && IS_PC(ch))
			{
				CNPC* pNPC = TO_NPC(tch);
				CPC* pPC = TO_PC(ch);
				pNPC->Set_MobFlag(STATE_MONSTER_PARASITE);
				pNPC->SetOwner(pPC);
				bApply = true;
			}
			break;

		case MST_ASSIST_SUICIDE:
			if (IS_NPC(tch) && IS_PC(ch))
			{
				CNPC* pNPC = TO_NPC(tch);
				CPC* pPC = TO_PC(ch);
				pNPC->Set_MobFlag(STATE_MONSTER_SUICIDE);
				pNPC->SetOwner(pPC);
				bApply = true;
			}
			break;

		case MST_ASSIST_TOTEM_ITEM_BUFF:
			if (IS_NPC(tch) && IS_PC(ch))
			{
				CNPC* pNPC = TO_NPC(tch);
				CPC* pPC = TO_PC(ch);
				pNPC->Set_MobFlag(STATE_MONSTER_TOTEM_ITEM_BUFF);
				pNPC->SetOwner(pPC);
				bApply = true;
			}
			break;

		case MST_ASSIST_TOTEM_ITEM_ATTK:
			if (IS_NPC(tch) && IS_PC(ch))
			{
				CNPC* pNPC = TO_NPC(tch);
				CPC* pPC = TO_PC(ch);
				pNPC->Set_MobFlag(STATE_MONSTER_TOTEM_ITEM_ATTK);
				pNPC->SetOwner(pPC);
				bApply = true;
			}
			break;

		default:
			break;
		}
		break;

	case MT_RECOVER:
		if (DEAD(tch))
			break;


		switch (magic->m_subtype)
		{
		case MST_RECOVER_EXP:
		{
			switch (magic->m_damagetype)
			{
			case MDT_ONLYPOWER:
			{
				if (IS_PC(tch))
				{
					CPC* pPC = TO_PC(tch);
					if (pPC && pPC->m_loseexp > 0)
					{
						pPC->AddExpSP_Direct(pPC->m_loseexp, 0);

						{
							CNetMsg::SP rmsg(new CNetMsg);
							RecoverExpSp(rmsg, pPC->m_loseexp, 0);
							SEND_Q(rmsg, pPC->m_desc);
						}

						GAMELOG << init("RECOVER EXP USE SKILL", pPC) << "RECOVER EXP" << delim << pPC->m_loseexp << delim << "EXP" << delim << pPC->m_exp << end;

						pPC->m_loseexp = 0;
						bApply = true;
					}
				}
			}
			break;
			case MDT_ADDITION:
			case MDT_RATE:
			{
				GAMELOG << init("SYS_ERR") << "INVALID MAGIC DATA" << delim << magic->m_index << end;
			}
			break;
			default:
				break;
			}
		}
		break;
		case MST_RECOVER_SP:
		{
			switch (magic->m_damagetype)
			{
			case MDT_ONLYPOWER:
			{
				if (IS_PC(tch))
				{
					CPC* pPC = TO_PC(tch);
					if (pPC->m_losesp > 0)
					{
						pPC->AddExpSP_Direct(0, pPC->m_losesp);

						{
							CNetMsg::SP rmsg(new CNetMsg);
							RecoverExpSp(rmsg, 0, pPC->m_losesp);
							SEND_Q(rmsg, pPC->m_desc);
						}

						GAMELOG << init("RECOVER EXP USE SKILL", pPC) << "RECOVER SP" << delim << pPC->m_losesp << delim << "SP" << delim << pPC->m_skillPoint << end;

						pPC->m_losesp = 0;
						bApply = true;
					}
				}
			}
			break;
			case MDT_ADDITION:
			case MDT_RATE:
			{
				GAMELOG << init("SYS_ERR") << "INVALID MAGIC DATA" << delim << magic->m_index << end;
			}
			break;
			default:
				break;
			}
		}
		break;
		case MST_RECOVER_HP:
			switch (magic->m_damagetype)
			{
			case MDT_ONLYPOWER:
			{
				tch->m_hp += nPowerValue;
				bApply = true;

				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeRecoverHpMsg(rmsg, tch->m_index, nPowerValue);
				tch->m_pArea->SendToCell(rmsg, tch, true);
			}
			break;

			case MDT_ADDITION:
				GAMELOG << init("SYS_ERR")
					<< "INVALID MAGIC DATA"
					<< delim
					<< magic->m_index
					<< end;
				return;

			case MDT_RATE:
			{
				if (IS_APET(tch))
				{
					CAPet* apet = TO_APET(tch);
					tch->m_hp += (apet->m_maxHP + apet->GetOwner()->m_opJewelElementPetHPUP) * nPowerValue / SKILL_RATE_UNIT;
					bApply = true;
				}
				else
				{
					int healedHP = 0;
					if (tch->m_assist.m_state & AST_HEAL_REDUCE)
					{
						int healReduceVal;
						int healOrig;

						// 5000 * 20 / 100
						healOrig = tch->m_maxHP * nPowerValue / SKILL_RATE_UNIT;

						healReduceVal = healOrig - (healOrig * tch->m_assist.m_avRate.hp_recover_reduce / 100);

						tch->m_hp += healReduceVal;
						healedHP = healReduceVal;
					}
					else
					{
						healedHP = tch->m_maxHP * nPowerValue / SKILL_RATE_UNIT;
						tch->m_hp += healedHP;

					}

					bApply = true;

					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::makeRecoverHpMsg(rmsg, tch->m_index, healedHP);
					tch->m_pArea->SendToCell(rmsg, tch, true);
				}
			}
			break;
			}

			if (IS_APET(tch))
			{
				CAPet* apet = TO_APET(tch);
				if (tch->m_hp > apet->m_maxHP + apet->GetOwner()->m_opJewelElementPetHPUP)
					tch->m_hp = apet->m_maxHP + apet->GetOwner()->m_opJewelElementPetHPUP;
			}
			else
			{
				if (tch->m_hp > tch->m_maxHP)
					tch->m_hp = tch->m_maxHP;
			}

			if (IS_PC(tch))
			{
				CPC* pc = TO_PC(tch);
				pc->m_bChangeStatus = true;
			}
			else if (IS_ELEMENTAL(tch))
			{
				CElemental* pElemental = TO_ELEMENTAL(tch);
				pElemental->m_bChangeStatus = true;
			}
			if (IS_APET(tch))
			{
				CAPet* apet = TO_APET(tch);
				CNetMsg::SP rmsg(new CNetMsg);
				ExAPetStatusMsg(rmsg, apet);
				if (apet->m_pArea)
					apet->m_pArea->SendToCell(rmsg, apet->GetOwner(), true);
			}
			else
			{
				CNetMsg::SP rmsg(new CNetMsg);
				CharStatusMsg(rmsg, tch, 0);
				tch->m_pArea->SendToCell(rmsg, tch, true);
			}
			break;

		case MST_RECOVER_MP:
			switch (magic->m_damagetype)
			{
			case MDT_ONLYPOWER:
				tch->m_mp += nPowerValue;
				bApply = true;
				break;

			case MDT_ADDITION:
				GAMELOG << init("SYS_ERR")
					<< "INVALID MAGIC DATA"
					<< delim
					<< magic->m_index
					<< end;
				return;

			case MDT_RATE:
				tch->m_mp += tch->m_maxMP * nPowerValue / SKILL_RATE_UNIT;
				bApply = true;
				break;
			}

			if (tch->m_mp > tch->m_maxMP)
				tch->m_mp = tch->m_maxMP;

			if (IS_PC(tch))
			{
				CPC* pc = TO_PC(tch);
				pc->m_bChangeStatus = true;
			}
			else if (IS_ELEMENTAL(tch))
			{
				CElemental* pElemental = TO_ELEMENTAL(tch);
				pElemental->m_bChangeStatus = true;
			}
			if (IS_APET(tch))
			{
				CAPet* apet = TO_APET(tch);
				CNetMsg::SP rmsg(new CNetMsg);
				ExAPetStatusMsg(rmsg, apet);
				if (tch->m_pArea)
					tch->m_pArea->SendToCell(rmsg, apet->GetOwner(), true);
			}
			else
			{
				CNetMsg::SP rmsg(new CNetMsg);
				CharStatusMsg(rmsg, tch, 0);
				tch->m_pArea->SendToCell(rmsg, tch, true);
			}
			break;

		case MST_RECOVER_STM:
		{
			if (IS_APET(tch))
			{
				CAPet* apet = TO_APET(tch);
				switch (magic->m_damagetype)
				{
				case MDT_ONLYPOWER:
					apet->AddStamina(nPowerValue);
					bApply = true;
					break;

				case MDT_ADDITION:
					GAMELOG << init("SYS_ERR") << "INVALID MAGIC DATA" << delim
						<< magic->m_index << end;
					return;

				case MDT_RATE:
					apet->AddStamina(apet->m_pProto->m_nMaxStm * nPowerValue / SKILL_RATE_UNIT);
					bApply = true;
					break;
				}

				{
					CNetMsg::SP rmsg(new CNetMsg);
					ExAPetStatusMsg(rmsg, apet);
					if (tch->m_pArea)
						tch->m_pArea->SendToCell(rmsg, apet->GetOwner(), true);
				}
			}
		}
		break;

		case MST_RECOVER_FAITH:
		{
			if (IS_APET(tch))
			{
				CAPet* apet = TO_APET(tch);
				switch (magic->m_damagetype)
				{
				case MDT_ONLYPOWER:
					apet->AddFaith(nPowerValue);
					bApply = true;
					break;

				case MDT_ADDITION:
					GAMELOG << init("SYS_ERR") << "INVALID MAGIC DATA" << delim
						<< magic->m_index << end;
					return;

				case MDT_RATE:
					apet->AddFaith(apet->m_pProto->m_nMaxFaith * nPowerValue / SKILL_RATE_UNIT);
					bApply = true;
					break;
				}

				{
					CNetMsg::SP rmsg(new CNetMsg);
					ExAPetStatusMsg(rmsg, apet);
					if (tch->m_pArea)
						tch->m_pArea->SendToCell(rmsg, apet->GetOwner(), true);
				}
			}
		}
		break;
		}
		break;
	case MT_CURE:
		switch (magic->m_subtype)
		{
		case MST_CURE_BLIND:
			tch->m_assist.CureAssist(MST_ASSIST_BLIND, levelproto->m_magicLevel[magicindex]);
			bApply = true;
			break;

		case MST_CURE_POISON:
			tch->m_assist.CureAssist(MST_ASSIST_POISON, levelproto->m_magicLevel[magicindex]);
			bApply = true;
			break;

		case MST_CURE_HOLD:
			tch->m_assist.CureAssist(MST_ASSIST_HOLD, levelproto->m_magicLevel[magicindex]);
			bApply = true;
			break;

		case MST_CURE_CONFUSION:
			tch->m_assist.CureAssist(MST_ASSIST_CONFUSION, levelproto->m_magicLevel[magicindex]);
			bApply = true;
			break;

		case MST_CURE_STONE:
			tch->m_assist.CureAssist(MST_ASSIST_STONE, levelproto->m_magicLevel[magicindex]);
			bApply = true;
			break;

		case MST_CURE_SILENT:
			tch->m_assist.CureAssist(MST_ASSIST_SILENT, levelproto->m_magicLevel[magicindex]);
			bApply = true;
			break;

		case MST_CURE_BLOOD:
			tch->m_assist.CureAssist(MST_ASSIST_BLOOD, levelproto->m_magicLevel[magicindex]);
			bApply = true;
			break;

		case MST_CURE_REBIRTH:
			if (DEAD(tch))
			{
				CDratanCastle* pCastle = CDratanCastle::CreateInstance();
				if (IS_PC(tch))
				{
					CPC* pc = TO_PC(tch);
					if (pc != NULL
						&& pc->GetJoinFlag(ZONE_DRATAN) != WCJF_NONE
						&& pc->GetMapAttr() & MATT_WAR
						&& pCastle->GetState() != WCSF_NORMAL
						&& pc->m_pZone->m_index == ZONE_DRATAN)
					{
						switch (pc->GetJoinFlag(ZONE_DRATAN))
						{
						case WCJF_ATTACK_GUILD:
						{
							// ��Ȱ������ ������ ���Ұ�
							int gindex = pc->m_guildInfo->guild()->index();
							int i;
							for (i = 0; i < 7; i++)
							{
								if (pCastle->m_nRebrithGuild[i] == gindex)
								{
									break;
								}
							}

							if (i == 7)
							{
								if (IS_PC(ch))
								{
									CPC* ppc = TO_PC(ch);
									if (ppc)
									{
										CNetMsg::SP rmsg(new CNetMsg);
										ResponseClient::makeSkillErrorMsg(rmsg, MSG_SKILL_ERROR_CANNOT_SPELL, skill->m_proto->m_index, 0);
										SEND_Q(rmsg, ppc->m_desc);
									}
								}
								return;
							}

							break;
						}

						case WCJF_OWNER:
						case WCJF_DEFENSE_GUILD:
							// ����Ÿ���� ������ ���Ұ�
							if (pCastle->GetTowerStatus(7) == 0)
							{
								if (IS_PC(ch))
								{
									CPC* ppc = TO_PC(ch);
									if (ppc)
									{
										CNetMsg::SP rmsg(new CNetMsg);
										ResponseClient::makeSkillErrorMsg(rmsg, MSG_SKILL_ERROR_CANNOT_SPELL, skill->m_proto->m_index, 0);
										SEND_Q(rmsg, ppc->m_desc);
									}
								}
								return;
							}
							break;
						}
					}
				}
				bApply = true;

				tch->m_hp = tch->m_maxHP / 2;
				if (tch->m_mp < tch->m_maxMP / 2)
					tch->m_mp = tch->m_maxMP / 2;

				{
					// ��Ƴ��� �˸���
					CNetMsg::SP rmsg(new CNetMsg);
					RebirthMsg(rmsg, tch);
					if (tch->m_pArea)
						tch->m_pArea->SendToCell(rmsg, tch, true);
				}

				if (IS_PC(tch))
				{
					CPC* pc = TO_PC(tch);
					GoZone(pc,
						pc->m_pZone->m_index,
						pc->m_pos.m_yLayer,
						pc->m_pos.m_x,
						pc->m_pos.m_z);

					switch (magic->m_damagetype)
					{
					case MDT_RATE:
						if (!pc->IsChaotic())
						{
							LONGLONG exp = (LONGLONG)(pc->m_loseexp * 1.0 * nPowerValue / SKILL_RATE_UNIT + 0.5);
							pc->m_exp += exp;
							GAMELOG << init("RECOVER EXP", pc) << "RECOVER EXP" << delim << exp << delim
								<< "TOTAL EXP" << delim << pc->m_exp << end;
						}
						break;

					default:
						if (!pc->IsChaotic())
							pc->m_exp += (pc->m_loseexp < nPowerValue) ? pc->m_loseexp : nPowerValue;
						break;
					}
					pc->m_loseexp = 0;
					pc->CalcStatus(true);
				}
			}
			break;

		case MST_CURE_INVISIBLE:
			if (tch->IsInvisible())
			{
				/*tch->m_assist.CureAssist(MST_ASSIST_INVISIBLE, levelproto->m_magicLevel[magicindex]);*/
				tch->CancelInvisible();
			}
			bApply = true;
			break;

		case MST_CURE_STURN:
			tch->m_assist.CureAssist(MST_ASSIST_STURN, levelproto->m_magicLevel[magicindex]);
			bApply = true;
			break;

		case MST_CURE_SLOTH:
			tch->m_assist.CureAssist(MST_ASSIST_SLOTH, levelproto->m_magicLevel[magicindex]);
			bApply = true;
			break;

		case MST_CURE_DISEASE:
			tch->m_assist.CureAssist(MST_ASSIST_DISEASE, levelproto->m_magicLevel[magicindex]);
			bApply = true;
			break;

		case MST_CURE_CURSE:
			tch->m_assist.CureAssist(MST_ASSIST_CURSE, levelproto->m_magicLevel[magicindex]);
			bApply = true;
			break;

		case MST_CURE_NOTHELP:
		{
			// not ������ �ƴ� ������ ��� ġ��
			tch->m_assist.ClearAssist(true, false, false, true, false);
		}
		bApply = true;
		break;

		case MSG_CURE_ALL:
			tch->m_assist.ClearAssist(true, false, false, true, false);
			bApply = true;
			break;

		case MST_CURE_INSTANTDEATH:
			tch->m_assist.CureOtherAssist(MT_OTHER, MST_OTHER_INSTANTDEATH, levelproto->m_magicLevel[magicindex]);
			bApply = true;
			break;
		}
		break;

	case MT_OTHER:
		switch (magic->m_subtype)
		{
		case MST_OTHER_SKILLCANCEL:
			if (tch->m_currentSkill && tch->m_currentSkill->m_state == SKILL_CON_READY)
			{
				tch->m_currentSkill->Cancel(tch);
				tch->m_currentSkill = NULL;
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeSkillCancelMsg(rmsg, tch);
				if (tch->m_pArea)
					tch->m_pArea->SendToCell(rmsg, tch, true);
			}
			bApply = true;
			break;

		case MST_OTHER_TELEKINESIS:
#if defined(LC_BILA)
			if (IS_NPC(tch))
			{
				CNPC* pTarget = TO_NPC(tch);
				if (pTarget != NULL
					&& pTarget->m_proto->CheckFlag(NPC_CASTLE_TOWER) != 0)
				{
					bApply = false;
					break;
				}
			}
#endif

			if (IS_NPC(tch))
			{
				CNPC* pNPC = TO_NPC(tch);
				if (pNPC->m_proto->m_index == 339) {
					bApply = false;
				}
				else if (pNPC != NULL
					&& pNPC->m_proto->CheckFlag(NPC_WARCASTLE) == 0
					&& pNPC->m_proto->CheckFlag(NPC_CASTLE_TOWER) == 0)
				{
					GoTo(tch, GET_YLAYER(ch), GET_X(ch), GET_Z(ch), GET_H(ch), GET_R(tch));
					bApply = true;
				}
			}
			else if (IS_PC(tch))
			{
				CPC* pc = TO_PC(tch);
				CWarCastle* castle = CWarCastle::GetCastleObject(pc->m_pZone->m_index);
				if (castle)
				{
					if (!(pc->m_pArea->GetAttr(pc->m_pos.m_yLayer, pc->m_pos.m_x, pc->m_pos.m_z) & MATT_WAR) &&
						pc->m_pZone->IsWarZone((int)pc->m_pos.m_x, (int)pc->m_pos.m_z) == false)
					{
						GoTo(tch, GET_YLAYER(ch), GET_X(ch), GET_Z(ch), GET_H(ch), GET_R(tch));
						bApply = true;
					}
				}
				else
				{
					GoTo(tch, GET_YLAYER(ch), GET_X(ch), GET_Z(ch), GET_H(ch), GET_R(tch));
					bApply = true;
				}
			}
			else
			{
				GoTo(tch, GET_YLAYER(ch), GET_X(ch), GET_Z(ch), GET_H(ch), GET_R(tch));
				bApply = true;
			}
			break;

		case MST_OTHER_TOUNT:
			if (ch != tch && IS_NPC(tch))
			{
				// �����ڿ� ����� �ٸ���, ����� �ְ� hate ��ġ + ��ų �Ŀ��� ������ hate�� �����Ǹ�, �ְ� ��ġ�� �ش��ڴ� �������� hate�� ����
				// �������� ��󿡴��� hate => a
				// ����� �ְ� hate ��ġ => b
				// ����� �ְ� hate ĳ���� => c
				// c.hate = a
				// a = b + skill
				CAttackChar* p = tch->m_attackList;
				int nMaxHate = 0;
				CAttackChar* pMaxHate = NULL;
				int nCurHate = 0;
				CAttackChar* pCurHate = NULL;
				while (p)
				{
					if (nMaxHate < p->m_targetHate)
					{
						nMaxHate = p->m_targetHate;
						pMaxHate = p;
					}
					if (ch == p->ch)
					{
						nCurHate = p->m_targetHate;
						pCurHate = p;
					}
					p = p->m_next;
				}

				if (pMaxHate)
					pMaxHate->m_targetHate = nCurHate;
				if (pCurHate)
					pCurHate->m_targetHate = 0;

				ApplyHate(ch, tch, nMaxHate + nPowerValue, false);

				bApply = true;
			}
			break;

		case MST_OTHER_SUMMON:
			if (IS_PC(ch))
			{
				CPC* pc = TO_PC(ch);
				pc->SummonElemental(magiclevel->m_nPowerValue);
				bApply = true;
			}

			else if (IS_NPC(ch))
			{
				CNPC* pNPC = TO_NPC(ch);

				// ��ȯ ������ �Է� �Ǿ� ������
				if (pNPC->m_proto->m_aileader_idx > 0 && pNPC->m_proto->m_aileader_count > 0)
				{
					for (int i = 0; i < pNPC->m_proto->m_aileader_count; i++)
					{
						float x = 0.0f;
						float z = 0.0f;
						int nTry = 0;
						do
						{
							x = GET_X(pNPC) + (GetRandom(0, 1) ? -1 : 1) * GetRandom(20, 30) / 10.0f;
							z = GET_Z(pNPC) + (GetRandom(0, 1) ? -1 : 1) * GetRandom(20, 30) / 10.0f;
							unsigned short mapAttr = pNPC->m_pArea->GetAttr(GET_YLAYER(pNPC), x, z);
							if (mapAttr & MATT_WALKABLE || mapAttr & MATT_STAIR_UP || mapAttr & MATT_STAIR_DOWN) {
							}
							else
							{
								x = 0.0f;
								z = 0.0f;
							}
							nTry++;
						} while (nTry <= 10 && x < 0.1f && z < 0.1f);
						if (nTry > 10)
						{
							x = GET_X(pNPC);
							z = GET_Z(pNPC);
						}

						CNPC* rnpc = gserver->m_npcProtoList.Create(pNPC->m_proto->m_aileader_idx, NULL);
						if (!rnpc)
							continue;

						GET_X(rnpc) = x;
						GET_YLAYER(rnpc) = GET_YLAYER(pNPC);
						GET_Z(rnpc) = z;
						GET_R(rnpc) = GetRandom(0, (int)(PI_2 * 10000)) / 10000;
						rnpc->m_disableTime = 0;
						rnpc->m_postregendelay = 0;

						rnpc->m_regenX = GET_X(rnpc);
						rnpc->m_regenY = GET_YLAYER(rnpc);
						rnpc->m_regenZ = GET_Z(rnpc);

						int cx, cz;
						pNPC->m_pArea->AddNPC(rnpc);
						pNPC->m_pArea->PointToCellNum(GET_X(rnpc), GET_Z(rnpc), &cx, &cz);
						pNPC->m_pArea->CharToCell(rnpc, GET_YLAYER(rnpc), cx, cz);

						{
							CNetMsg::SP rmsg(new CNetMsg);
							AppearMsg(rmsg, rnpc, true);
							pNPC->m_pArea->SendToCell(rmsg, GET_YLAYER(rnpc), cx, cz);
						}

						bApply = true;
					}
				}
			}
			break;

		case MST_OTHER_EVOCATION:
			if (IS_PC(ch))
			{
				CPC* pc = TO_PC(ch);
				pc->ChangeEvocationState(skill->m_proto->m_index);
				bApply = true;
			}
			break;

		case MST_OTHER_TARGETFREE:
			if (IS_NPC(tch))
			{
				CNPC* pNPCTarget = TO_NPC(tch);
				DelTargetFromAttackList(pNPCTarget, ch);
				if (pNPCTarget->m_attackList == NULL)
					pNPCTarget->m_postregendelay = gserver->m_pulse;
				bApply = true;
			}
			break;

		case MST_OTHER_SOUL_DRAIN:
			if (IS_PC(ch) && IS_NPC(tch))
			{
				CPC* pPC = TO_PC(ch);
				CNPC* pNPC = TO_NPC(tch);
				int count = 0;

				// ������ �ִ� ��ȥ�� ������ �Ѱ� �ø���.
				if (pPC && pPC->m_desc && ch->m_pArea && pNPC && !pNPC->Check_MobFlag(STATE_MONSTER_NO_SOUL)
					&& pPC->m_currentSkill && pPC->m_currentSkill->m_state == SKILL_CON_FIRE)
				{
					count = pPC->GetSoul_Count();

					// ��ȥ ������ 10���� �ִ��̴�.
					if (count < MAX_SOUL_COUNT)
					{
						count++;
						pPC->SetSoul_Count(count);
					}

					{
						// ��ȥ ���� �ż��� ������
						CNetMsg::SP rmsg(new CNetMsg);
						ResponseClient::makeSkillSoulCountMsg(rmsg, pPC->GetSoul_Count());
						SEND_Q(rmsg, pPC->m_desc);
					}

					// ��ų�� ��������� ���� �ٲ�
					pPC->SetPlayerState(PLAYER_STATE_SKILL);

					{
						CNetMsg::SP rmsg(new CNetMsg);
						ExPlayerStateChangeMsg(rmsg, pPC);
						ch->m_pArea->SendToCell(rmsg, ch, true);
					}

					// NPC�� ���̻� ��ȥ�� ���ѱ��� �ʴ´�.
					pNPC->Set_MobFlag(STATE_MONSTER_NO_SOUL);

					// NPC ��ȥ ����� ���� �����̸� ���� ���� �޽��� �����Ѵ�.
					pNPC->m_pulseSoulRecover = gserver->m_pulse;
					bApply = true;
				}
			}
			break;

			// ����Ʈ ������ ����
		case MST_OTHER_WARP:
			if (ch->m_pArea)
			{
				// skill ready���� �̸� ���� �� �� ��ǥ�� �̵���Ų��.
				ch->m_pArea->MoveChar(ch, GET_YLAYER(ch), GET_X(ch), GET_Z(ch), GET_H(ch), GET_R(ch), MSG_MOVE_STOP, NULL);
				bApply = true;
			}
			break;

		case MST_OTHER_FLY:
			if (IS_PC(ch))
			{
				CPC* pPC = TO_PC(ch);

				// ���⿡ ���� ȿ��
				if (pPC && ch->m_pArea)
				{
					if (pPC->IsSetPlayerState(PLAYER_STATE_FLYING))
						pPC->ResetPlayerState(PLAYER_STATE_FLYING);
					else
						pPC->SetPlayerState(PLAYER_STATE_FLYING);

					{
						CNetMsg::SP rmsg(new CNetMsg);
						ExPlayerStateChangeMsg(rmsg, pPC);
						ch->m_pArea->SendToCell(rmsg, ch, true);
					}

					bApply = true;
				}
			}
			break;
		case MSG_OTHER_SUMMON_NPC:
		{
			//npc ��ȯ
			CNPC* npc = gserver->m_npcProtoList.Create(skill->m_proto->m_summonIDX, NULL);

			if (npc == NULL)
			{
				GAMELOG << init("SUMMON NPC FAIL :: create monster")
					<< "npc index : " << skill->m_proto->m_summonIDX << end;
				return;
			}

			npc->m_lifetime = magiclevel->m_nPowerValue + gserver->getNowSecond();

			GET_X(npc) = GET_X(ch);
			GET_Z(npc) = GET_Z(ch);
			GET_R(npc) = GET_R(ch);
			GET_YLAYER(npc) = GET_YLAYER(ch);

			npc->m_regenX = GET_X(npc);
			npc->m_regenZ = GET_Z(npc);
			npc->m_regenY = GET_YLAYER(npc);

			npc->CalcStatus(false);

			int cx, cz;
			ch->m_pArea->AddNPC(npc);
			ch->m_pArea->PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
			ch->m_pArea->CharToCell(npc, GET_YLAYER(npc), cx, cz);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, npc, true);
				ch->m_pArea->SendToCell(rmsg, GET_YLAYER(npc), cx, cz);
			}
		}
		break;
		}
		break;
	}
}

/////////////////////
// Function name	: ApplySkill
// Description	    : ��ų ����, ������ ����� -1 ����, ��� ����� 1 ����, �׿� 0
// Argument         : CCharacter* ch
//                  : ������
// Argument         : CCharacter* tch
//                  : ���
// Argument         : CSkill* skill
//                  : ��ų
// Argument         : int itemidx
//                  : �����ۿ� ���� ��ų�� ��� ������ �ε���, �׿ܴ� -1
// Argument         : bool& bApply
//                  : ��ų�� ���������� ����Ǹ� true, �ƴϸ� false
int ApplySkill(CCharacter* ch, CCharacter* tch, CSkill* skill, int itemidx, bool& bApply)
{
	bApply = false;
	if (!ch || !tch)
		return 0;

	if (!skill)
		return 0;

	if (IS_NPC(tch))
	{
		CNPC* tnpc = TO_NPC(tch);
		if (tnpc->m_proto->CheckFlag(NPC_BOSS | NPC_MBOSS | NPC_RAID) && (skill->m_proto->m_flag & SF_NOT_BOSS))
			return 0;
	}

	if (IS_PC(ch))
	{
		CPC* pc = TO_PC(ch);
		if (pc->GetPlayerState() == PLAYER_STATE_PKMODEDELAY ||
			pc->GetPlayerState() == PLAYER_STATE_PKMODE) {
			switch (skill->m_proto->m_index)
			{
			case IMMOTAL_BUF:
			case CUBE_BUF:
			case IGNI1_BUF:
			case IGNI2_BUF:
			case IGNI3_BUF:
			case IGNI4_BUF:
			case CAST_POTION:
			case VELOCITY_BUF:
			case 1742:
			case 975:
			case 1897:
			case 981:
			case 1903:
			case 988:
			case 1910:
			case 1172:
			case 1278:
			case 1310:
			case 1938:
			case 1174:
			case 1280:
			case 1312:
			case 1940:
			case 1188:
			case 1287:
			case 1319:
			case 1947:
			case 931:
			case 1037:
			case 1876:
			case 1918:
			case 936:
			case 1042:
			case 1881:
			case 1923:
			case 947:
			case 10553:
			case 1892:
			case 1934:
			case 946:
			case 1891:
			case 1052:
			case 1933:
			case 963:
			case 967:
			case 1186:
			case 1285:
			case 1317:
			case 1945:
			case 1036:
			case 1917:
			case 794:
			case 1896:
			case 980:
			case 1902:
			case 968:
			case 962:
			case 1093:
			case 229:
			case 323:
			case 1798:
			case 1871:
			case 1997:
			case 1998:
			case 1999:
			case 2000:
			case 2001:
			case 2002:
			case 2003:
			case 2013:
			case 2044:
			case 2045:
			case 2046:
			case 2047:
			case 987:
			case 1909:
			case 935:
			case 1880:
			case 1057:
			case 1058:
			case 1059:
			case 1077:
			case 1076:
			case 939:
			case 941:
			case 943:
			case 966:
			case 971:
			case 977:
			case 984:
			case 991:
			case 1045:
			case 1047:
			case 1049:
			case 1176:
			case 1190:
			case 1197:
			case 1282:
			case 1289:
			case 1296:
			case 1314:
			case 1321:
			case 1328:
			case 1369:
			case 1884:
			case 1886:
			case 1888:
			case 1899:
			case 1906:
			case 1913:
			case 1926:
			case 1928:
			case 1930:
			case 1942:
			case 1949:
			case 1956:
			case 1080:
			case 1834:
			case 1835:
			case 1836:
			case 1838:
			case 1839:
			case 1837:
			case 2057:
			case 1079:
				return 0;
				break;
			case INVISIBILITY:
				if (pc->m_bHasFlagItem)
					return 0;
				break;
			default:
				break;
			}
		}

		//pvp��ȣ ������ üũ
		if ((skill->m_proto->m_flag & SF_HELP) == false)
		{
			if (checkPvPProtect(pc, tch) == false)
				return 0;
		}
	}

	//������ ��ų�� ��� 
	if (itemidx > 0 && skill->m_proto->m_targetType != STT_PARTY_ALL)
	{
		if (ch->checkItemCoolTime(itemidx, skill) == false)
			return 0;
	}

	if (skill->m_proto->m_index == 1081)
	{
		// GP�Ҹ��Ͽ� ����ġ ��.
		if (!IS_PC(tch))
			return 0;
		CPC* pc = TO_PC(tch);

		//pc->AddExpUseGP(LONGLONG exp);
		pc->AddExpUseGP(30000);
		return 0;
	}

	if (skill->m_proto->m_index == SKILL_GUILD_ROOM_WARP)
	{
		// �̵� ���� �˻�
		CPC* pc = TO_PC(ch);
		//�̵��� ��ų���̱� ������ ���� ��ų ��뵥���� �ʱ�ȭ
		if (pc->m_currentSkill != NULL)
		{
			pc->m_currentSkill->m_state = SKILL_CON_NORMAL;
			pc->m_currentSkill = NULL;
		}

		int canWarp = pc->CanWarp();
		if (canWarp != 0)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, (MSG_SYS_TYPE)canWarp);
			SEND_Q(rmsg, pc->m_desc);
			return 0;
		}

		// 10���� �̵��ϰ� �ϱ�
		pc->m_reqWarpType_skill = IONCE_WARP_RETURN;
		pc->m_reqWarpData_skill = ZONE_GUILDROOM;
		pc->m_reqWarpTime_skill = PULSE_WARPDELAY;
		pc->SetPlayerState(PLAYER_STATE_WARP);

		{
			// ��������� �˸���
			CNetMsg::SP rmsg(new CNetMsg);
			WarpStartMsg(rmsg, pc);
			pc->m_pArea->SendToCell(rmsg, ch, true);
		}

		return 0;
	}

	if (skill->m_proto->m_index == SKILL_GUILD_ROOM_RECALL)
	{
		//���� �������� ��� �������� �޽��� ����
		CPC* pc = TO_PC(ch);

		CNetMsg::SP rmsg(new CNetMsg);
		UpdateClient::GuildRoomRecallRequestMsg(rmsg);
		pc->m_guildInfo->guild()->SendToAll(rmsg, false);

		return 0;
	}
	// 060227 : bs : �ߺ��ȵǴ� ��ų���� �˻�
	if ((skill->m_proto->m_flag & SF_NOTDUPLICATE) && tch->m_assist.FindBySkillIndex(skill->m_proto->m_index))
	{
		if (IS_PC(ch))
		{
			/*�ߺ���� �Ұ� ���� �޽���*/
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeSkillErrorMsg(rmsg, MSG_SKILL_ERROR_DUPLICATE, skill->m_proto->m_index, 0);
			SEND_Q(rmsg, TO_PC(ch)->m_desc);
		}
		return 0;
	}
	if ((skill->m_proto->m_flag & SF_NOTDUPLICATE) && tch->m_assist.FindBySkillIndex(skill->m_proto->m_index))
		return 0;
	if (IS_APET(tch) && TO_APET(tch)->IsProtoFlag(APET_FLAG_EXP) && !skill->m_proto->CheckSorcererFlag(SSF_APP_APET))
		return 0;

	if ((skill->m_proto->m_flag & SF_NOTHELP) && !ch->IsInPeaceZone(true))
	{
		CPC* pc = NULL;
		switch (ch->m_type)
		{
		case MSG_CHAR_PC:
			pc = TO_PC(ch);
			break;

		case MSG_CHAR_PET:
			pc = TO_PET(ch)->GetOwner();
			break;

		case MSG_CHAR_ELEMENTAL:
			pc = TO_ELEMENTAL(ch)->GetOwner();
			break;

		case MSG_CHAR_APET:
			pc = TO_APET(ch)->GetOwner();
			break;

		default:
			break;
		}
		if (pc != NULL
			&& tch != NULL
			&& IS_NPC(tch)
			&& pc->m_level - tch->m_level <= 5)
		{
			CNPC* pTemp = TO_NPC(tch);
			if (pTemp != NULL
				&& pTemp->m_proto->m_index != 303 /*�Ǹ��� ����*/)
			{
				pc->m_pulseLastAttackSkill = gserver->m_pulse;
			}
		}
	}

	// NPC�� ������ �ص� ���� ���¸� ����
	if (IS_NPC(ch))
		TO_NPC(ch)->m_nRaidMoveTime = gserver->m_pulse + GetRandom(PULSE_MONSTER_RAID_MOVE * 9 / 10, PULSE_MONSTER_RAID_MOVE * 11 / 10);

	// NPC�� �¾Ƶ� ����
	if (IS_NPC(tch))
		TO_NPC(tch)->m_nRaidMoveTime = gserver->m_pulse + GetRandom(PULSE_MONSTER_RAID_MOVE * 9 / 10, PULSE_MONSTER_RAID_MOVE * 11 / 10);

	if (IS_PC(tch))
	{
		CPC* pc = TO_PC(tch);
		if ((pc->m_bImmortal && pc->m_bFirstDoIt == false && (skill->m_proto->m_flag & SF_HELP) == false) || pc->IsDisable())
		{
			if (skill->m_proto->m_index != 1060 && skill->m_proto->m_index != IMMOTAL_BUF)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg(rmsg, MSG_SYS_DO_NOT_USE_DURING_IMMORTAL);
				SEND_Q(rmsg, pc->m_desc);
				return 0;
			}
		}
	}

	// ���ɸ� ����� ���� ���Ѵ�.
	if (tch->m_assist.m_state & AST_FREEZE)
		return 0;

	const CSkillProto* proto;
	const CSkillLevelProto* levelproto;

	int i;

	if ((proto = skill->m_proto) == NULL)
		return 0;
	if ((levelproto = proto->Level(skill->m_level)) == NULL)
		return 0;

	if (proto->m_flag & SF_SINGLEMODE)
	{
		if (!ch->m_pZone->IsPersonalDungeon())
			return 0;
	}

	// SSF_APP_ �˻�
	if (proto->CheckSorcererFlag(SSF_APP_ALL))
	{
		if (tch->m_type == MSG_CHAR_ELEMENTAL)
		{
			CElemental* pElemental = TO_ELEMENTAL(tch);
			switch (pElemental->GetElementalType())
			{
			case ELEMENTAL_FIRE:
				if (!proto->CheckSorcererFlag(SSF_APP_FIRE))
					return 0;
				break;
			case ELEMENTAL_WIND:
				if (!proto->CheckSorcererFlag(SSF_APP_WIND))
					return 0;
				break;
			case ELEMENTAL_EARTH:
				if (!proto->CheckSorcererFlag(SSF_APP_EARTH))
					return 0;
				break;
			case ELEMENTAL_WATER:
				if (!proto->CheckSorcererFlag(SSF_APP_WATER))
					return 0;
				break;
			default:
				return 0;
			}
		}
		else if (tch->m_type == MSG_CHAR_APET)
		{
			if (TO_APET(tch)->IsProtoFlag(APET_FLAG_EXP) && !skill->m_proto->CheckSorcererFlag(SSF_APP_APET))
				return 0;
		}
		else
		{
			if (!proto->CheckSorcererFlag(SSF_APP_CHARACTER))
				return 0;
		}
	}

	// �� � ��ų�� �ǽ������� �ٸ� �������� ��� �Ұ�
	if (ch->IsInPeaceZone(true) && !tch->IsInPeaceZone(false)
		&& skill->m_proto->m_index != ROYAL_RUMBLE_DEBUFF_SKILL
		&& skill->m_proto->m_index != 1359
		&& skill->m_proto->m_index != 511    //straya debuff poison
		&& skill->m_proto->m_index != 2054) // dakrness theos debuff
	{
		return 0;
	}

	bool bHelp = (proto->m_flag & SF_HELP) ? true : false;
	bool bNotHelp = (proto->m_flag & SF_NOTHELP) ? true : false;

	// ������ NPC�� ĳ���Ϳ��� ������ helpŸ������ ���� �ؾ��ϹǷ� �ڽ��� �ڽſ��� ����ϴ� ��ó�� �Ѵ�.
	if (IS_NPC(ch) &&
		(TO_NPC(ch)->Check_MobFlag(STATE_MONSTER_TOTEM_BUFF) || TO_NPC(ch)->Check_MobFlag(STATE_MONSTER_TOTEM_ITEM_BUFF)))
	{
		ch = tch;
	} // �ڱ� �ڽ��� �����ο��� ������ �Ŵ� ��ó�� �ٹ��� �Ѥ�;;

	// !((help on && ���ƴ�) || (nothelp && ��)) => ��ų ��� �Ұ�
	if (!((bHelp && !ch->IsEnemy(tch)) || (bNotHelp && ch->IsEnemy(tch)))
		&& skill->m_proto->m_index != 2054  //darkness theos debuff
		&& skill->m_proto->m_index != 511  //straya poison debuff
		&& itemidx != -2
		&& skill->m_proto->m_index != 1158
		&& skill->m_proto->m_index != ROYAL_RUMBLE_DEBUFF_SKILL
		&& skill->m_proto->m_index != 1359
		)	// ������ �ε����� -2�� Ʈ���ſ� ���� ��ų �ߵ��̹Ƿ� �н�
	{
		return 0;
	}

	// NOT HELP�� �ǽ������� ��� �Ұ�
	if ((bNotHelp && ch->IsInPeaceZone(true))
		&& skill->m_proto->m_index != ROYAL_RUMBLE_DEBUFF_SKILL
		&& skill->m_proto->m_index != 1359
		&& skill->m_proto->m_index != 511  //strata poison debuff
		&& skill->m_proto->m_index != 511) // darkness theos debuff
	{
		return 0;
	}

	if (!ch->CanVisible(tch))
	{
		// TODO : �κ������� �����ϴ� ��ų �߰��� �ε��� �˻��Ͽ�, ���� ��ų�� ��밡�����
		if (proto->m_index != 146)
			return 0;
	}

	if (IS_PC(ch) && proto->m_type == ST_SUMMON_SKILL)
	{
		CPC* pPc = TO_PC(ch);
		// ���͸� ��ȯ�Ѵ�.
		CNPC* pSummonNpc = NULL;
		int SummonNpcIdx = 0; // ��ȯ�� NPC Index;
		if (proto->Level(1)->m_magic[0]->m_type == MT_ASSIST)
		{
			switch (proto->Level(1)->m_magic[0]->m_subtype)
			{
			case MST_ASSIST_SOUL_TOTEM_BUFF: // Ʈ��
			case MST_ASSIST_SOUL_TOTEM_ATTK:
				SummonNpcIdx = proto->m_summonIDX;
				pSummonNpc = pPc->GetSummonNpc(SUMMON_NPC_TYPE_TOTEM);
				if (pSummonNpc)
					return 0;
				break;
			case MST_ASSIST_TRAP: // ����.
			{
				if (pPc->GetBombSummonCont() >= 3)
					return 0;
				CMagicLevelProto* pMLProto = gserver->m_magicProtoList.Find(proto->Level(skill->m_level)->m_magic[0]->m_index)->m_levelproto[proto->Level(skill->m_level)->m_magicLevel[0] - 1];
				SummonNpcIdx = pMLProto->GetSummonNpcIndex();
			}
			break;
			case MST_ASSIST_TOTEM_ITEM_BUFF:
			case MST_ASSIST_TOTEM_ITEM_ATTK:
				SummonNpcIdx = proto->m_summonIDX;
				pSummonNpc = pPc->GetSummonNpc(SUMMON_NPC_TYPE_TOTEM_ITEM);
				if (pSummonNpc)
				{
					pPc->SummonNpcRemove(SUMMON_NPC_TYPE_TOTEM_ITEM, true);
				}
				break;
			}
		}

		pSummonNpc = gserver->m_npcProtoList.Create(SummonNpcIdx, NULL);
		if (pSummonNpc == NULL)
		{
			GAMELOG << init("SUMMON TOTEM NPC FAIL :: create monster", pPc)
				<< "npc index : " << proto->m_index << end;
			return 0;
		}
		GET_X(pSummonNpc) = GET_X(pPc);
		GET_Z(pSummonNpc) = GET_Z(pPc);
		GET_R(pSummonNpc) = GET_R(pPc);
		GET_YLAYER(pSummonNpc) = GET_YLAYER(pPc);

		pSummonNpc->m_regenX = GET_X(pSummonNpc);
		pSummonNpc->m_regenZ = GET_Z(pSummonNpc);
		pSummonNpc->m_regenY = GET_YLAYER(pSummonNpc);

		pSummonNpc->CalcStatus(false);
		pSummonNpc->setSyndicateType(pPc->getSyndicateType());

		switch (proto->Level(1)->m_magic[0]->m_subtype)
		{
		case MST_ASSIST_SOUL_TOTEM_BUFF: // Ʈ��
			pSummonNpc->m_assist.m_state |= AST_SOUL_TOTEM_BUFF;
			break;
		case MST_ASSIST_SOUL_TOTEM_ATTK:
			pSummonNpc->m_assist.m_state |= AST_SOUL_TOTEM_ATTK;
			break;
		case MST_ASSIST_TRAP: // ����.
		{
			// �κ����� ��ų�� ���� ���� �־�����.
			CSkill* pSkill = gserver->m_skillProtoList.Create(1158); // Ʈ�� ���� �κ����� ��ų
			if (pSkill)
			{
				ApplySkill(pPc, pSummonNpc, pSkill, -1, bApply);
				delete pSkill;
				pSkill = NULL;
			}
		}
		//pSummonNpc->m_assist.m_state |= AST_TRAP;
		break;
		}

		if (proto->Level(1)->m_magic[0]->m_subtype == MST_ASSIST_TRAP)
		{
			pSummonNpc->m_assist.m_state |= AST_TRAP;
		}

		pSummonNpc->SetOwner(pPc);

		int cx, cz;
		pPc->m_pArea->AddNPC(pSummonNpc);
		pPc->m_pArea->PointToCellNum(GET_X(pSummonNpc), GET_Z(pSummonNpc), &cx, &cz);
		pPc->m_pArea->CharToCellForSummonNpc(pPc, pSummonNpc, GET_YLAYER(pSummonNpc), cx, cz);

		{
			CNetMsg::SP rmsg(new CNetMsg);
			AppearMsg(rmsg, pSummonNpc, true);
			pPc->m_pArea->SendToCell(rmsg, GET_YLAYER(pSummonNpc), cx, cz);
		}

		switch (proto->Level(1)->m_magic[0]->m_subtype)
		{
		case MST_ASSIST_SOUL_TOTEM_BUFF: // Ʈ��
		case MST_ASSIST_SOUL_TOTEM_ATTK:
			pPc->SetSummonNpc(SUMMON_NPC_TYPE_TOTEM, pSummonNpc);
			break;
		case MST_ASSIST_TRAP: // ����.
			pPc->SetBombSummonNPC(pSummonNpc);
			break;
		case MST_ASSIST_TOTEM_ITEM_BUFF:
		case MST_ASSIST_TOTEM_ITEM_ATTK:
		{
			pPc->SetSummonNpc(SUMMON_NPC_TYPE_TOTEM_ITEM, pSummonNpc);
			//�ý��� �޽��� ����
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_SUMMON_TOTEM_NPC);
			SEND_Q(rmsg, pPc->m_desc);
		}
		break;
		}

		tch = (CCharacter*)pSummonNpc;
		bHelp = false;
		bNotHelp = true;
	}

	switch (proto->m_index)
	{
	case 1129:	// ���� ���� �ູ
	case 1130:	// ���� ���� �ູ
	case 1131:	// ���� ���� �ູ
	case 1132:	// �ٶ��� ���� �ູ
		ch->m_assist.CureBySkillIndex(1129);
		ch->m_assist.CureBySkillIndex(1130);
		ch->m_assist.CureBySkillIndex(1131);
		ch->m_assist.CureBySkillIndex(1132);
		break;
	}

	// ��ų ����� ��� ��ų ����Ʈ �޽��� ����
	if (proto)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		EffectSkillMsg(rmsg, tch, proto);
		tch->m_pArea->SendToCell(rmsg, tch, true);
	}

	// �������� �˻�
	if (!tch->CanApplySkill(proto, levelproto))
		return 0;

	// ch�� tch�� Ʋ����
	if (ch != tch)
	{
		// hate ����
		// not help�� Ÿ�ٿ��� �ٷ� ����
		if (bNotHelp)
		{
			if (IS_PC(ch) && IS_PC(tch))
			{
				CPC* pc = TO_PC(ch);
				CPC* tpc = TO_PC(tch);
				if (!pc->CanPvP(tpc, true))
					return 0;
			}
			ApplyHate(ch, tch, levelproto->m_hate, true);
		}
		// help�� Ÿ���� attack list�� ���鿡�� ����
		else if (bHelp)
		{
			// ach : tch�� ������ ����Ʈ
			CAttackChar* ach = tch->m_attackList;
			while (ach)
			{
				ApplyHate(ch, ach->ch, levelproto->m_hate, true);
				ach = ach->m_next;
			}
		}
	}
	bool bRecoverExpSpSkill = false;
	bool bHit[MAX_SKILL_MAGIC] = { false, false, false };
	unsigned char attratt = 0;

	for (i = 0; i < MAX_SKILL_MAGIC; i++)
	{
		const CMagicProto* magic = levelproto->m_magic[i];

		if (magic == NULL)
			continue;

		const CMagicLevelProto* magiclevel =
			magic->Level(levelproto->m_magicLevel[i]);

		if (magiclevel == NULL)
			continue;

		if (magic->m_type != MT_ATTRIBUTE)
			continue;

		if (magic->m_subtype < 0 || magic->m_subtype > AT_LIGHT)
			continue;

		if (magiclevel->m_nPowerValue < 0 ||
			magiclevel->m_nPowerValue > AT_LEVELMAX)
			continue;

		if (magic->m_damagetype != MDT_ADDITION) /* not attack */
			continue;

		attratt = AT_MIX(magic->m_subtype, magiclevel->m_nPowerValue);
	}

	for (i = 0; i < MAX_SKILL_MAGIC; i++)
	{
		const CMagicProto* magic = levelproto->m_magic[i];
		if (magic == NULL)
			continue;
		const CMagicLevelProto* magiclevel = magic->Level(levelproto->m_magicLevel[i]);
		if (magiclevel == NULL)
			continue;

		if (itemidx < 0)
#ifdef ENABLE_ROGUE_SKILL125_BRZ
			bHit[i] = (SelectHitType(ch, tch, MSG_DAMAGE_MAGIC, HITTYPE_MISS | HITTYPE_NORMAL, magic, magiclevel, (skill->m_proto->m_flag & SF_NOTHELP) ? true : false, skill->m_level) != HITTYPE_MISS);
#else
			bHit[i] = (SelectHitType(ch, tch, MSG_DAMAGE_MAGIC, HITTYPE_MISS | HITTYPE_NORMAL, magic, magiclevel, (skill->m_proto->m_flag & SF_NOTHELP) ? true : false) != HITTYPE_MISS);
#endif // ENABLE_ROGUE_SKILL125_BRZ
		else if (itemidx > 0 && magic->m_type == MT_ASSIST)
		{
#ifdef ENABLE_ROGUE_SKILL125_BRZ
			bHit[i] = (SelectHitType(ch, tch, MSG_DAMAGE_MAGIC, HITTYPE_MISS | HITTYPE_NORMAL, magic, magiclevel, (skill->m_proto->m_flag & SF_NOTHELP) ? true : false, skill->m_level) != HITTYPE_MISS);
#else
			bHit[i] = (SelectHitType(ch, tch, MSG_DAMAGE_MAGIC, HITTYPE_MISS | HITTYPE_NORMAL, magic, magiclevel, (skill->m_proto->m_flag & SF_NOTHELP) ? true : false) != HITTYPE_MISS);
#endif // ENABLE_ROGUE_SKILL125_BRZ
			bApply = true;

			ch->addItemCoolTime(itemidx);
		}
		else
		{
			bHit[i] = true;
			ch->addItemCoolTime(itemidx);
		}

		int retAttack = 0;
		switch (magic->m_type)
		{
		case MT_ATTACK:
			// ������ ������ ���� ��������
			bApply = true;

			ch->m_attratt = attratt;
			retAttack = ProcAttack(ch, tch, ch->GetAttackType(proto), skill, i);
			if (retAttack)
				return retAttack;
			break;

		case MT_ASSIST:
			switch (magic->m_subtype)
			{
			case MST_ASSIST_DAMAGELINK:
				if (ch == tch)
					return 0;
				break;
			}
			// Ʈ����� �ڵ����� ��� Ʈ����� �ڵ���
			if (itemidx == 677 || itemidx == 3579)
				ApplyMagic(ch, tch, skill, i, true, bApply);
			// ����Ʈ ������ 100% �Ǿ� �ϴ� ��ų��
			else if (magic->m_subtype == (unsigned char)MST_ASSIST_CONFUSED
				|| magic->m_subtype == (unsigned char)MST_ASSIST_AURA_DARKNESS
				|| magic->m_subtype == (unsigned char)MST_ASSIST_AURA_WEAKNESS
				|| magic->m_subtype == (unsigned char)MST_ASSIST_AURA_ILLUSION
				|| magic->m_subtype == (unsigned char)MST_ASSIST_MERCENARY
				|| magic->m_subtype == (unsigned char)MST_ASSIST_SOUL_TOTEM_BUFF
				|| magic->m_subtype == (unsigned char)MST_ASSIST_SOUL_TOTEM_ATTK)
				ApplyMagic(ch, tch, skill, i, true, bApply);
			else
				ApplyMagic(ch, tch, skill, i, bHit[i], bApply);
			break;

		case MT_STAT:
		case MT_RECOVER:
		case MT_CURE:
		case MT_OTHER:
		{
			if (magic->m_subtype == MST_OTHER_REFLEX)
				bHit[0] = true;
			// Ʈ����� �ڵ����� ��� Ʈ����� �ڵ���
			if (itemidx == 677 || itemidx == 3579)
				ApplyMagic(ch, tch, skill, i, true, bApply);
			else
				ApplyMagic(ch, tch, skill, i, bHit[i], bApply);
			if (magic->m_type == MT_RECOVER && (magic->m_subtype == MST_RECOVER_EXP || magic->m_subtype == MST_RECOVER_SP))
			{
				bRecoverExpSpSkill = true;
			}
		}
		break;
		default:
		{
			if (bHit[i] && !bApply)
				bApply = true;
		}
		break;
		}
	}

	if (IS_PC(tch) && bRecoverExpSpSkill == true)
	{
		if (bApply == true)
		{
			// ������ ���� ��� ĳ���� ������Ʈ
		}
		else
		{
			// ������ ���������� ��� ����.
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::ItemNotUseMsg(rmsg, MSG_ITEM_USE_ERROR_DEATH_PENALTY);
			SEND_Q(rmsg, TO_PC(tch)->m_desc);
		}
	}

	int nBlessAdd = 0;
	int nBlessRate = 0;
	if (bHelp
		&& itemidx < 1
		&& (tch->m_assist.m_state & AST_BLESS)
		&& !(proto->m_flag & SF_NOTBLESS))
	{
		nBlessAdd = tch->m_assist.m_avAddition.bless;
		nBlessRate = tch->m_assist.m_avRate.bless;
	}
	int remain = -1;
	int remainCnt = -1;
	// ȿ������ : assist���� durtime�� �ִ� ��ų�� �߰��ǰ� ������ �ȵǴϱ� ������ �߰�ȣ��
	// ��ȣž, ���¿��� ���� �Ȱɸ�
	bool bCastleObject = false;
	if (IS_NPC(tch))
	{
		CNPC* npc = TO_NPC(tch);
		if (npc->m_proto->CheckFlag(NPC_CASTLE_TOWER | NPC_LORD_SYMBOL))
			bCastleObject = true;
	}
	if (!bCastleObject)
	{
#ifdef ENABLE_ROGUE_SKILL125_BRZ
		if (skill->m_proto->m_index == 125)
		{
			int diffLevel = tch->m_level - ch->m_level;
			if (diffLevel > 5)			remain = 80;
			else if (diffLevel > 2)		remain = 100;
		}
#endif // ENABLE_ROGUE_SKILL125_BRZ
		if (skill->m_proto->m_index == 1134)
		{
			remain = skill->m_usetime;
		}

		if (bApply)
		{
			if (false == tch->m_assist.Add(ch, itemidx, proto, skill->m_level, bHit, true, remain,
				remainCnt,
				CalcSkillParam(ch, tch, proto->m_selfparam, proto->m_targetparam), nBlessAdd, nBlessRate))
			{
				bApply = false;
			}
		}
	}

	if (bApply && (nBlessAdd || nBlessRate))
	{
		tch->m_assist.CancelBless();
	}

	if (!ch->CanVisible(tch) && (proto->m_flag & SF_NOTHELP))
		tch->CancelInvisible();

	if (IS_PC(ch))
	{
		CPC* pc = TO_PC(ch);
		if (skill->m_proto->m_flag & SF_TOGGLE)
		{
			pc->changeToggleState(skill->m_proto->m_index, TOGGLE_SKILL);
		}
	}

	return 0;
}

/////////////////////
// Function name	: ApplySkillParty
// Description	    : ��Ƽ�� ���� ������ ����
// Argument         : CPC* ch
//                  : ������
// Argument         : CSkill* skill
//                  : ��ų
// Argument         : int itemidx
//                  : �����ۿ� ���� ��ų�� ��� ������ �ε���, �׿ܴ� -1
// Argument         : bool& bApply
//                  : ��ų�� ���������� ����Ǹ� true, �ƴϸ� false
void ApplySkillParty(CPC* ch, CSkill* skill, int itemidx, bool& bApply)
{
	if (ch->m_pArea == NULL || ch->m_pZone == NULL)
		return;

	if (!ch->IsParty())
	{
		ApplySkill(ch, ch, skill, itemidx, bApply);
		return;
	}

	if (itemidx > 0)
	{
		if (ch->checkItemCoolTime(itemidx, skill) == false)
		{
			bApply = false;
			return;
		}
	}

	bool bApplyParty = false;
	int i;
	for (i = 0; i < MAX_PARTY_MEMBER; i++)
	{
		if (ch->m_party->GetNearMember(ch, i))
		{
			int retApplySkill = ApplySkill(ch, ch->m_party->GetNearMember(ch, i), skill, itemidx, bApply);
			// ��Ƽ�� �� �Ѹ����Զ� bApply�� true�� �Ǹ� ��ȯ�Ǵ� bApply�� true�� �Ѵ�.
			if (bApply)
				bApplyParty = true;
			if (retApplySkill == -1)
			{
				bApply = bApplyParty;
				return;
			}
		}
	}

	bApply = bApplyParty;
}

////////////////////
// Function name	: CalcSkillParam
// Description	    : ch�� tch���� ��ų ����, �ĸ������� ���� ��(1/100����)�� ���Ѵ�
int CalcSkillParam(const CCharacter* ch, const CCharacter* tch, int selfparam, int targetparam)
{
	if (!IS_PC(ch) || !IS_PC(tch))
		return 100;

	int sparam = 0;
	int tparam = 0;

	if (ch)
	{
		switch (selfparam)
		{
		case SPARAM_STR:
			sparam = ch->m_str;
			break;
		case SPARAM_DEX:
			sparam = ch->m_dex;
			break;
		case SPARAM_INT:
			sparam = ch->m_int;
			break;
		case SPARAM_CON:
			sparam = ch->m_con;
			break;
		}
	}
	if (tch)
	{
		switch (targetparam)
		{
		case SPARAM_STR:
			tparam = tch->m_str;
			break;
		case SPARAM_DEX:
			tparam = tch->m_dex;
			break;
		case SPARAM_INT:
			tparam = tch->m_int;
			break;
		case SPARAM_CON:
			tparam = tch->m_con;
			break;
		}
	}

	int param = 100 + (sparam - tparam) / 2;
	if (param < SKILL_PARAM_MIN)
		return SKILL_PARAM_MIN;
	if (param > SKILL_PARAM_MAX)
		return SKILL_PARAM_MAX;
	return param;
}

void ApplySkillGuild(CPC* ch, CSkill* skill, int itemidx, bool& bApply)
{
	if (ch->m_pArea == NULL || ch->m_pZone == NULL)
		return;
	if (!ch->m_guildInfo)
	{
		return;
	}

	bool bApplyGuild = false;
	int i;
	CPC* tpc = NULL;
	for (i = 0; i < GUILD_MAX_MEMBER; i++)
	{
		tpc = ch->m_guildInfo->guild()->GetNearMember(ch, i);
		if (tpc != NULL)
		{
			int retApplySkill = ApplySkill(ch, tpc, skill, itemidx, bApply);
			if (bApply)
				bApplyGuild = true;
			if (retApplySkill == -1)
			{
				bApply = bApplyGuild;
				return;
			}
		}
	}
	bApply = bApplyGuild;
}
/////////////////////
// Function name	: ApplySkillExped
// Description	    : �����뿡 ���� ������ ����
// Argument         : CPC* ch
//                  : ������
// Argument         : CSkill* skill
//                  : ��ų
// Argument         : int itemidx
//                  : �����ۿ� ���� ��ų�� ��� ������ �ε���, �׿ܴ� -1
// Argument         : bool& bApply
//                  : ��ų�� ���������� ����Ǹ� true, �ƴϸ� false
// ������ ���� �׷쿡�� ���� �ǰ� ��
void ApplySkillExped(CPC* ch, CSkill* skill, int itemidx, bool& bApply)
{
	if (ch->m_pArea == NULL || ch->m_pZone == NULL)
		return;

	if (!ch->IsExped())
	{
		ApplySkill(ch, ch, skill, itemidx, bApply);
		return;
	}

	bool bApplyExped = false;
	int nGroup = -1;
	const CExpedMember* pMember = ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	if (pMember)
	{
		nGroup = pMember->GetGroupType();
		if (nGroup >= 0)
		{
			for (int j = 0; j < MAX_EXPED_GMEMBER; j++)
			{
				if (ch->m_Exped->GetNearMember(ch, nGroup, j))
				{
					int retApplySkill = ApplySkill(ch, ch->m_Exped->GetNearMember(ch, nGroup, j), skill, itemidx, bApply);
					// ��Ƽ�� �� �Ѹ����Զ� bApply�� true�� �Ǹ� ��ȯ�Ǵ� bApply�� true�� �Ѵ�.
					if (bApply)
						bApplyExped = true;
					if (retApplySkill == -1)
					{
						bApply = bApplyExped;
						return;
					}
				}
			}
		}
	}

	bApply = bApplyExped;
}

void CSkillList::DeleteInstantSkill(int flag)
{
	CSkillListNode* p;
	CSkill* tmp;
	p = m_head;
	while (p)
	{
		if (p->skill()->m_proto->m_flag & flag)
		{
			//��ų����Ʈ��������
			tmp = p->skill();
			p = p->next();
			Remove(tmp);
		}
		else
		{
			p = p->next();
		}
	}
}

void CSkillList::SaveSkillCoolTime(CPC* ch, std::vector<std::string>& vec)
{
	std::string deletestr = boost::str(boost::format(
		"delete from t_skill_cooltime where a_char_index = %1%") % ch->m_index);

	vec.push_back(deletestr);


	CSkillListNode* p = m_head;

	std::string insertstr = "insert into t_skill_cooltime values";
	insertstr.reserve(2048);

	int count = 0;
	while (p)
	{
		if (p->skill()->IsReady(ch) == false)
		{
			int useUnixtime = int(gserver->m_nowseconds) - ((gserver->m_pulse - p->skill()->m_usetime) / 10);
			insertstr += boost::str(boost::format("(%1%, %2%, %3% ),") % ch->m_index % p->skill()->m_proto->m_index % useUnixtime);
			++count;
		}
		p = p->next();
	}

	if (count == 0)
		return;

	int index = insertstr.rfind(",");
	insertstr.erase(index);

	vec.push_back(insertstr);
}

bool CSkillList::Disable(CSkill* skill)
{
	if (skill == NULL)
		return false;

	CSkillListNode* pNode = m_head;

	while (pNode)
	{
		if (pNode->skill()->m_proto->m_index == skill->m_proto->m_index)
		{
			pNode->skill()->m_enable = 0;
			break;
		}
		pNode = pNode->next();
	}
	return true;
}

void CSkillProtoList::LearnAllSkill(CPC* ch)
{
	for (int i = 0; i < m_count; ++i)
	{
		CSkillProto* pSkillProto = m_list[i];
		if (!pSkillProto)
			continue;

		if (!pSkillProto->IsSameJob(ch))
			continue;

		CSkill* pSkill = NULL;
		if (pSkillProto->IsActive())
		{
			pSkill = ch->m_activeSkillList.Find(pSkillProto->m_index);
		}
		else if (pSkillProto->IsPassive())
		{
			pSkill = ch->m_passiveSkillList.Find(pSkillProto->m_index);
		}
		else
		{
			pSkill = ch->m_etcSkillList.Find(pSkillProto->m_index);
		}

		if (pSkill)
		{
			pSkill->m_level = pSkillProto->m_maxLevel;
		}
		else
		{
			pSkill = Create(pSkillProto->m_index, pSkillProto->m_maxLevel);
			if (pSkill)
			{
				if (pSkillProto->IsActive())
				{
					ch->m_activeSkillList.Add(pSkill);
				}
				else if (pSkillProto->IsPassive())
				{
					ch->m_passiveSkillList.Add(pSkill);
				}
				else
				{
					ch->m_etcSkillList.Add(pSkill);
				}
			}
		}

		// ��ȯ�� ��ų�� ��ȯ�����Ե� �߰� : ��Ƽ�길
		if ((pSkillProto->m_type == ST_MELEE || pSkillProto->m_type == ST_RANGE || pSkillProto->m_type == ST_MAGIC) && pSkillProto->CheckSorcererFlag(SSF_USE_ALL))
		{
			int needFlag = 0;
			CElemental* p = ch->m_elementalList;
			while (p)
			{
				switch (p->GetElementalType())
				{
				case ELEMENTAL_FIRE:
					needFlag = SSF_USE_FIRE;
					break;
				case ELEMENTAL_WIND:
					needFlag = SSF_USE_WIND;
					break;
				case ELEMENTAL_EARTH:
					needFlag = SSF_USE_EARTH;
					break;
				case ELEMENTAL_WATER:
					needFlag = SSF_USE_WATER;
					break;
				default:
					needFlag = -1;
					break;
				}
				if (needFlag != -1)
				{
					if (pSkillProto->CheckSorcererFlag(needFlag))
						p->AddSkill(pSkillProto->m_index, pSkill->m_level);
				}
				p = p->m_nextElemental;
			}
		}
		else
		{
			CElemental* p = ch->m_elementalList;
			while (p)
			{
				p->CalcStatus(true);
				p = p->m_nextElemental;
			}
		}
	}

	ch->CalcStatus(true);

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeSkillListMsg(rmsg, ch);
		SEND_Q(rmsg, ch->m_desc);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		EffectEtcMsg(rmsg, ch, MSG_EFFECT_ETC_FIRECRACKER);
		SEND_Q(rmsg, ch->m_desc);
	}
}

bool ApplyWarSkill(CPC* ch, int zone_index)
{
	if (ch->m_guildInfo == NULL)
		return false;

	int level = ch->m_level;
	int job = ch->m_job;

	CWarCastle* castle = NULL;

	//���� ������ �����ϴ� ĳ���� �� ���� ���� üũ
	if (zone_index == ZONE_MERAC)
	{
		castle = CWarCastle::GetCastleObject(ZONE_MERAC);
		if (castle == NULL)
			return false;

		if (level < 40 || level > 80)
			return false;
	}
	else if (zone_index == ZONE_DRATAN)
	{
		castle = CWarCastle::GetCastleObject(ZONE_DRATAN);
		if (castle == NULL)
			return false;

		if (level < 80 || level > 130)
			return false;
	}
	else
	{
		return false;
	}

	//���� ���� �ƴ϶��
	if (castle->GetState() != WCSF_WAR_CASTLE)
		return false;

	//���� �� ������ ��û�� ĳ����.
	if (castle->CheckJoin(ch) == WCJF_NONE)
		return false;

	int skill_index = 0;

	//������ ��ų
	if (zone_index == ZONE_DRATAN)
	{
		switch (job)
		{
		case JOB_TITAN:
			skill_index = 1778;
			break;
		case JOB_KNIGHT:
			skill_index = 1779;
			break;
		case JOB_HEALER:
			skill_index = 1780;
			break;
		case JOB_MAGE:
			skill_index = 1781;
			break;
		case JOB_ROGUE:
			skill_index = 1782;
			break;
		case JOB_SORCERER:
			skill_index = 1790;
			break;
		case JOB_NIGHTSHADOW:
			skill_index = 1783;
			break;
#ifdef EX_ROGUE
		case JOB_EX_ROGUE:
			skill_index = 1782;
			break;
#endif
#ifdef EX_MAGE
		case JOB_EX_MAGE:
			skill_index = 1781;
			break;
#endif
		}
	}
	else if (zone_index == ZONE_MERAC)
	{
		switch (job)
		{
		case JOB_TITAN:
			skill_index = 1773;
			break;
		case JOB_KNIGHT:
			skill_index = 1774;
			break;
		case JOB_HEALER:
			skill_index = 1775;
			break;
		case JOB_MAGE:
			skill_index = 1776;
			break;
		case JOB_ROGUE:
			skill_index = 1777;
			break;
		case JOB_SORCERER:
			skill_index = 1789;
			break;
#ifdef EX_ROGUE
		case JOB_EX_ROGUE:
			skill_index = 1777;
			break;
#endif
#ifdef EX_MAGE
		case JOB_EX_MAGE:
			skill_index = 1776;
			break;
#endif
		}
	}
	else
	{
		return false;
	}

	if (ch->m_assist.FindBySkillIndex(skill_index) != 0)
	{
		return true;
	}

	CSkill* skill = gserver->m_skillProtoList.Create(skill_index, 1);
	if (skill == NULL)
		return false;

	bool apply;
	ApplySkill(ch, ch, skill, -1, apply);
	ch->m_isWarSkillCheck = true;
	return true;
	;
}

void ClearWarSkill(CPC* ch)
{
	int skill_index_merac, skill_index_dratan;
	int job = ch->m_job;

	switch (job)
	{
	case JOB_TITAN:
		skill_index_dratan = 1778;
		skill_index_merac = 1773;
		break;
	case JOB_KNIGHT:
		skill_index_dratan = 1779;
		skill_index_merac = 1774;
		break;
	case JOB_HEALER:
		skill_index_dratan = 1780;
		skill_index_merac = 1775;
		break;
	case JOB_MAGE:
		skill_index_dratan = 1781;
		skill_index_merac = 1776;
		break;
	case JOB_ROGUE:
		skill_index_dratan = 1782;
		skill_index_merac = 1777;
		break;
	case JOB_SORCERER:
		skill_index_dratan = 1790;
		skill_index_merac = 1789;
		break;
	case JOB_NIGHTSHADOW:
		skill_index_dratan = 1783;
		skill_index_merac = -1;
		break;
#ifdef EX_ROGUE
	case JOB_EX_ROGUE:
		skill_index_dratan = 1782;
		skill_index_merac = 1777;
		break;
#endif
#ifdef EX_MAGE
	case JOB_EX_MAGE:
		skill_index_dratan = 1781;
		skill_index_merac = 1776;
		break;
#endif
	default:
		skill_index_dratan = -1;
		skill_index_merac = -1;
		break;
	}

	if (skill_index_merac != -1)
	{
		if (ch->m_assist.FindBySkillIndex(skill_index_merac))
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_WAR_BUF_NOT_IN_ZONE);
			SEND_Q(rmsg, ch->m_desc);
		}
		ch->m_assist.CureBySkillIndex(skill_index_merac);
	}
	if (skill_index_dratan != -1)
	{
		if (ch->m_assist.FindBySkillIndex(skill_index_dratan))
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_WAR_BUF_NOT_IN_ZONE);
			SEND_Q(rmsg, ch->m_desc);
		}
		ch->m_assist.CureBySkillIndex(skill_index_dratan);
	}
}

void ClearWarItemSkill(CPC* ch)
{
	std::vector<CItemProto*>::iterator it = gserver->m_itemProtoList.m_flagGuildWar.begin();
	std::vector<CItemProto*>::iterator it_end = gserver->m_itemProtoList.m_flagGuildWar.end();

	bool bSendSysMsg = false;

	for (; it != it_end; it++)
	{
		ch->m_assist.CureByItemIndex((*it)->getItemIndex());

		if (bSendSysMsg == false)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_WAR_BUF_END_WAR);
			SEND_Q(rmsg, ch->m_desc);
			bSendSysMsg = true;
		}
	}
}

//