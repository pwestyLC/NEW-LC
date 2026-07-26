#include <boost/format.hpp>
#include "stdhdrs.h"

#include "../ShareLib/DBCmd.h"
#include "DratanCastle.h"
#include "../ShareLib/packetType/ptype_old_do_item.h"


CDungeon::CDungeon()
{
	m_nEnterFeeRate = 100;
	m_nHuntRate = 0;
	m_nMobRate = 50;
	m_nEnvRate = 50;
	m_pZone = 0;
	m_nChangeTime = 0;
}

CDungeon::~CDungeon()
{
}

void CDungeon::SetChangeTime(int nTime)
{
	m_nChangeTime = nTime;
}

CZone * CDungeon::GetZone()
{
	return m_pZone;
}

void CDungeon::ChangeFeeRate(int nRate)
{
	int newRate = nRate;
	if( newRate > 150 )
		newRate = 150;
	else if ( newRate < 70 )
		newRate = 70;

	SetFeeRate(newRate);
}

void CDungeon::ChangeHuntRate(int nRate)
{
	int newRate = nRate;
	if( newRate > 20 )
		newRate = 20;
	else if ( newRate < 0 )
		newRate = 0;

	SetHuntRate(newRate);
}

void CDungeon::ChangeMobRate(int nRate)
{
	int newRate = GetMobRate() + nRate;
	if( newRate > 100 )
		newRate = 100;
	else if ( newRate < 0 )
		newRate = 0;

	SetMobRate(newRate);
}

void CDungeon::ChangeEnvRate(int nRate)
{
	int newRate = GetEnvRate() + nRate;
	if( newRate > 100 )
		newRate = 100;
	else if ( newRate < 0 )
		newRate = 0;

	SetEnvRate(newRate);
}

int CDungeon::GetChangeTime()
{
	return m_nChangeTime;
}

void CDungeon::SetZone(CZone * pZone)
{
	m_pZone = pZone;
}

void CDungeon::ChangeSetting()
{
	if(m_pZone == 0)
	{
		return;
	}

	int nMobRate[10][4] =  	// ���ݷ�, ����, �ִ�ü��, �þ߹���
	{
		{20, 20, 30, 0},
		{10, 10, 15, 0},
		{5, 5, 10, 0},
		{0, 0, 0, 0},
		{-5, -5, -5, 0},
		{-7, -7, -7, 0},
		{-10, -10, -10, 0},
		{-15, -15, -15, 0},
		{-20, -20, -20, 0},
		{-25, -25, -25, -80},
	};

	// �� ����
	CNPC * npc = m_pZone->m_area->m_npcList;

	while(npc != 0)
	{
		int midx = GetMobRate()/10; //pwesty tomb dificulty settings
		if(midx > 9)
		{
			midx = 9;
		}

		// ���ݷ� ����
		if(npc->m_attackType == MSG_DAMAGE_MELEE)
		{
			npc->m_eqMelee = npc->m_proto->m_attack + npc->m_proto->m_attack * nMobRate[midx][0] / 100;
			if(npc->m_eqMelee < 0)
			{
				npc->m_eqMelee = 1;
			}
		}
		else if(npc->m_attackType == MSG_DAMAGE_RANGE)
		{
			npc->m_eqRange = npc->m_proto->m_attack + npc->m_proto->m_attack * nMobRate[midx][0] / 100;
			if(npc->m_eqRange < 0)
			{
				npc->m_eqRange = 1;
			}
		}
		else if(npc->m_attackType == MSG_DAMAGE_MAGIC)
		{
			npc->m_eqMagic = npc->m_proto->m_magic + npc->m_proto->m_magic * nMobRate[midx][0] / 100;
			if(npc->m_eqMagic < 0)
			{
				npc->m_eqMagic = 1;
			}
		}

		// ���� ����
		npc->m_eqDefense = npc->m_proto->m_defense + npc->m_proto->m_defense * nMobRate[midx][1] / 100;

		// �ִ� ü�� ����
		npc->m_maxHP = npc->m_proto->m_hp + npc->m_proto->m_hp * nMobRate[midx][2] / 100;
		if(npc->m_maxHP < 0)
		{
			npc->m_maxHP = 1;
		}

		// �þ� �Ÿ� ����
		if(nMobRate[midx][3] != 0 && npc->m_attackRange != 0)
		{
			npc->m_attackRange = npc->m_proto->m_attackArea + npc->m_proto->m_attackArea * nMobRate[midx][3] / 100;
		}

		npc = npc->m_pNPCNext;
	}
}

bool CDungeon::checkOwnerMode()
{
	if(GetEnvRate() <= 80 || GetMobRate() <= 80)
		return false;

	return true;
}

void CDungeon::setOwnerMode( bool ownerMode )
{
	m_owner_mode = ownerMode;

	if(ownerMode == false)
	{
		setChangeNormalTime(gserver->getNowSecond());

		//���۷� ���� �ð� ������Ʈ
		if(gserver->m_helper->isRun())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			HelperDVDNormalChangeTimeMsg(rmsg, GetChangeNormalTime());
			SEND_Q(rmsg, gserver->m_helper);
		}
	}
	else
	{
		setChangeNormalTime(0);
	}
}

CGuardList::CGuardList()
{
	maxcount = 0;
	maxkind = 0;
	m_pGardList = NULL;
	m_cnt = 0;
	m_maxcnt = 0;
}

CGuardList::~CGuardList()
{
	if( m_pGardList != NULL)
	{
		delete [] m_pGardList;
		m_pGardList = NULL;
	}
}

void CGuardList::clean()
{
	if( m_pGardList != NULL)
	{
		memset(m_pGardList, 0, m_maxcnt*sizeof(GUARD));
	}
}

CGuardList::CGuardList(int kind, int count)
{
	init(kind, count);
}

void CGuardList::init(int kind, int count)
{
	maxcount = count;
	maxkind = kind;
	m_maxcnt = maxcount*maxkind;
	m_pGardList = new GUARD[maxcount*maxkind];

	m_cnt = 0;
}

bool CGuardList::InsertGuard(int idx, float x, float z, float h)
{
	if(m_cnt > m_maxcnt)
	{
		return false;
	}

	if(GetCount(idx) > maxcount)
	{
		return false;
	}

	m_pGardList[m_cnt].mobindex = idx;
	m_pGardList[m_cnt].pos_x = x;
	m_pGardList[m_cnt].pos_z = z;
	m_pGardList[m_cnt].pos_h = h;

	m_cnt++;

	return true;
}

int CGuardList::GetCount(int idx)
{
	int ret = 0;
	for(int i =0; i < m_maxcnt; i++)
	{
		if(m_pGardList[i].mobindex == idx)
		{
			ret++;
		}
	}

	return ret;
}

int CGuardList::GetCount()
{
	return m_cnt;
}

int CGuardList::GetMaxCount()
{
	return m_maxcnt;
}

CDratanCastle * CDratanCastle::pInstance = 0;

CDratanCastle::CDratanCastle() : CWarCastle()
{
	memset(m_gateNPC, 0, sizeof(CNPC*) * COUNT_DRATAN_GATE_NPC);

	InitMasterTower();
	InitRespond();
	InitReinforce();
	InitWarpNPC();
	InitRebrithNPC();

	m_bMaster = false;
	m_bLoop = true;

	m_pDungeonNPC = NULL;
	m_isNotChange = false;
}

void CDratanCastle::InitRebrithNPC()
{
	for(int i = 0; i < 7; i++)
	{
		m_pRebrithNPC[i] = NULL;
		m_nRebrithGuild[i] = -1;
		m_strRebrithGuild[i] = new char[51];
		memset((void *)m_strRebrithGuild[i], 0, 51);

		m_nRegenTimeRebirthNPC[i] = 0;
	}
}

void CDratanCastle::ResetRebrithNPC()
{
	for(int i = 0; i < 7; i++)
	{
		m_nRebrithGuild[i] = -1;
		memset((void *)m_strRebrithGuild[i], 0, 51);
	}
}

void CDratanCastle::InitWarpNPC()
{
	for(int i = 0; i < 5; i++)
	{
		m_pWarpNPC[i] = NULL;
	}
}

void CDratanCastle::InitReinforce()
{
	memset(m_reinforce, 0, 3);
}

void CDratanCastle::InitRespond()
{
	for(int i = 0; i < 5; i++)
	{
		if(m_RespondMember[i] != 0)
		{
			CPC* pc = PCManager::instance()->getPlayerByCharIndex(m_RespondMember[i]);
			if( pc != NULL)
			{
				pc->ResetPlayerState(PLAYER_CRISTAL_RESPOND);
				pc->SetRespondTime(0);
			}
			m_RespondMember[i] = 0;
		}
	}

	m_respondCnt = 0;
}

bool CDratanCastle::SetRespondMember(CPC * pc)
{
#ifdef BUGFIX_DRATAN_CRISTAL_RESPOND
	if(m_respondCnt >= 5)
#else
	if(m_respondCnt > 5)
#endif // BUGFIX_DRATAN_CRISTAL_RESPOND
	{
		return false;
	}
	else
	{
		for(int i = 0; i < 5; i++)
		{
			if(m_RespondMember[i] == 0)
			{
				m_RespondMember[i] = pc->m_index;
#ifdef BUGFIX_DRATAN_CRISTAL_RESPOND
				m_respondCnt++;
#endif // BUGFIX_DRATAN_CRISTAL_RESPOND
				return true;
			}
		}
	}

	return false;
}

void CDratanCastle::ResetRespondMeber(CPC * pc)
{
	for(int i = 0; i < 5; i++)
	{
		if(m_RespondMember[i] == pc->m_index)
		{
			m_RespondMember[i] = 0;
			m_respondCnt--;

			pc->ResetPlayerState(PLAYER_CRISTAL_RESPOND);
			pc->SetRespondTime(0);

			return;
		}
	}
}

void CDratanCastle::InitMasterTower()
{
	memset( m_nMasterTower, 0, 7);
}

char CDratanCastle::GetTowerStatus(int i)
{
	if( i < 7
			&& m_nMasterTower[i] <= 5)
	{
		return m_nMasterTower[i];
	}

	return 0;
}

bool CDratanCastle::SetTowerStatus(int i, char values)
{
	if( i < 7
			&& values <= 5)
	{
		m_nMasterTower[i] = values;
		return true;
	}
	else
	{
		return false;
	}
}

void CDratanCastle::SetNextWarTime(int nextWarTime)
{
	time_t curtime;
	time(&curtime);

	// ���� ���� �ð��� ���� �ð������̸� �״�� ����
	if (GetState() == WCSF_NORMAL && nextWarTime != 0)
	{
		if (nextWarTime > curtime)
		{
			m_nextWarTime = nextWarTime;
			return ;
		}
		else
		{
			GAMELOG << init("WAR CASTLE : WARN SET TIME")
					<< "CUR TIME : " << (int)curtime << delim
					<< "NEXT TIME : " << nextWarTime
					<< end;
		}
	}

	// ���� �ð��� �⺻ ������ ����
	// ���� ������ ����
	struct tm curtm = NOW();

#if defined (LC_KOR) || defined(LC_BILA) || defined (LC_GAMIGO) || defined (LC_USA)
	// 다음 일요일을 구함
	int next = 7 - curtm.tm_wday;
	if (next < 0)
		next += 7;
#else
	// 다음 토요일을 구함
	int next = 7 - curtm.tm_wday;
	if (next < 7)
		next += 7;
#endif

	// ���� ����� 20�ÿ� �ش��ϴ� time_t ���� ����
	struct tm nexttm = curtm;

	nexttm.tm_hour = 19;
	nexttm.tm_min = 0;
	nexttm.tm_sec = 0;
	nexttm.tm_mday += next;
	nexttm.tm_isdst = -1;
	time_t nexttime = mktime(&nexttm);

	// ���� �ð����� ������ �����ַ�
	if (nexttime < curtime)
	{
		nexttm.tm_mday += 7;
		nexttime = mktime(&nexttm);
	}

	m_nextWarTime = nexttime;

	if (nextWarTime != 0)
	{
		GAMELOG << init("WAR CASTLE : SET NEXT TIME FOR LOAD")
				<< "IN : " << nextWarTime << delim
				<< "SET : " << m_nextWarTime
				<< end;
	}
}

bool CDratanCastle::IsJoinTime()
{
	if (m_bMoveToRegen)
		return false;

	struct tm tmJoinTime;
	GetJoinTime(&tmJoinTime, false);
	tmJoinTime.tm_isdst = -1;
	time_t jointime = mktime(&tmJoinTime);

	// ������ �����ð��� ��
	time_t curtime;
	time(&curtime);
	if (m_lastWarTime < curtime && curtime < jointime)
		return false;

	return true;
}

void CDratanCastle::GetJoinTime(struct tm* joinTime, bool bHumanable)
{
	// ���� ������ ���ϰ�
	struct tm tmNext;
	GetNextWarTime(&tmNext, false);

	// ������ ���ϱ�
	int nDay = tmNext.tm_wday;
	if (nDay == 0)
		nDay = 7;
	nDay -= 1;

	// ���� �������� nDay���� ����
	// �� �� 20�÷� ���� : 7��
	tmNext.tm_hour = 20;
	tmNext.tm_min = 0;
	tmNext.tm_sec = 0;
	tmNext.tm_mday -= nDay;
	tmNext.tm_isdst = -1;
	time_t tJoin = mktime(&tmNext);

	*joinTime = *localtime(&tJoin);

	if (bHumanable)
	{
		joinTime->tm_year += 1900;
		joinTime->tm_mon += 1;
	}
}

int CDratanCastle::GetRegenPoint(int joinflag, CPC* ch)
{
	switch (joinflag)
	{
	case WCJF_OWNER:
	case WCJF_DEFENSE_GUILD:
		return 25;

	case WCJF_ATTACK_GUILD:
		if (ch && ch->m_guildInfo && ch->m_guildInfo->guild())
		{
			int i;
			for (i = 0; i < 7; i++)
			{
				if (m_nRebrithGuild[i] == ch->m_guildInfo->guild()->index())
				{
					switch (i)
					{
					///===
					case 0:
						return 18;
					case 1:
						return 19;
					case 2:
						return 20;
					case 3:
						return 21;
					case 4:
						return 22;
					case 5:
						return 23;
					case 6:
						return 24;
					}
				}
			}
		}
		return 27;

	default:
		return 27;
	}
}

void CDratanCastle::SetRegenPoint(int nRegenPos, int nGuildIndex)
{
	if (nRegenPos > 9)
	{
		return;
	}

	m_posRegenPoint[nRegenPos] = nGuildIndex;
}

void CDratanCastle::SetGateNPC(CNPC* npc)
{
	if (npc->m_proto->CheckFlag(NPC_CASTLE_TOWER))
	{
		switch (npc->m_proto->m_index)
		{
		case 388:
			m_gateNPC[0] = npc;
			return;		// �ܼ���
		case 389:
			m_gateNPC[1] = npc;
			return;		// ������ 1
		case 404:
			m_gateNPC[2] = npc;
			return;		// ������ 2
		case 1625:
			m_gateNPC[3] = npc;
			return;
		case 1626:
			m_gateNPC[4] = npc;
			return;
		default:
			return ;
		}
	}
}

void CDratanCastle::SetWarpNPC(CNPC* npc)
{
	if (npc->m_proto->CheckFlag(NPC_CASTLE_TOWER)
			&& npc->m_proto->m_index >= 382
			&& npc->m_proto->m_index <= 386)
	{
		m_pWarpNPC[npc->m_proto->m_index - 382] = npc;
	}
}

void CDratanCastle::SetRebrithNPC(CNPC* npc)
{
	if (npc->m_proto->CheckFlag(NPC_WARCASTLE)
			&& npc->m_proto->CheckFlag(NPC_CASTLE_TOWER)
			&& npc->m_proto->m_index >= 390
			&& npc->m_proto->m_index <= 396)
	{
		if( m_pRebrithNPC[npc->m_proto->m_index - 390] == NULL )
		{
			m_pRebrithNPC[npc->m_proto->m_index - 390] = npc;
		}
	}
}

void CDratanCastle::UpdateGateState(CNPC* npc)
{
	int i;
	for (i = 0; i < COUNT_DRATAN_GATE_NPC; i++)
	{
		if (m_gateNPC[i] == npc)
		{
			m_gateState |= (1 << (i + 6));

			GAMELOG << init("DRATAN GATE NPC DESTROY")
					<< npc->m_proto->m_index << end;
			return;
		}
	}
}

bool CDratanCastle::IsOpenGate()
{
	// �ܼ���
	int outer1 = (1 << 6);

	// ������ 1
	int inner1 = (1 << 7);

	// ������ 2
	int inner2 = (1 << 8);

	// �ܼ���2
	int outer2 = (1 << 9);
	
	// �ܼ���3
	int outer3 = (1 << 10);

	if (GetGateState(outer1) == outer1)
		return true;

	if (GetGateState(inner1) == inner1)
		return true;

	if (GetGateState(inner2) == inner2)
		return true;

	if (GetGateState(outer2) == outer2)
		return true;

	if (GetGateState(outer3) == outer3)
		return true;

	return false;
}

bool CDratanCastle::SetNextWarTime(int wday, int hour)
{
	int minHour = 9999;
	int maxHour = -1;
	switch (wday)
	{
	case 0:		// �Ͽ��� : 13 ~ 23
#ifdef LC_USA	// �̱� : 11 ~ 20
		minHour = 16;
		maxHour = 21;
#else
		minHour = 13;
#if defined(LC_GAMIGO)
		maxHour = 21;
#else // LC_GAMIGO
		maxHour = 23;
#endif // LC_GAMIGO
#endif // LC_USA
		break;

	case 6:		// ����� : 18 ~ 23
#ifdef LC_USA	// �̱� : 11 ~ 23
		minHour = 16;
		maxHour = 21;
#else
		minHour = 17;
#if defined(LC_GAMIGO)
		maxHour = 21;
#else // LC_GAMIGO
		maxHour = 23;
#endif // LC_GAMIGO
#endif // LC_USA
		break;

	default:
		return false;
	}
	if (hour < minHour || hour > maxHour)
		return false;

	time_t curtime;
	time(&curtime);
	struct tm curtm = NOW();

	// ���� �ش� ���ϱ��� ���̸� ����
	int next = wday - curtm.tm_wday;
	if (next <= 0)
		next += 7;
	if (next <= 4)
		next += 7;

	// �׳� �ش� �ð��� time_t ���� ����
	struct tm nexttm = curtm;
	nexttm.tm_hour = hour;
	nexttm.tm_min = 0;
	nexttm.tm_sec = 0;
	nexttm.tm_mday += next;
	nexttm.tm_isdst = -1;
	time_t nexttime = mktime(&nexttm);

	// ���� �ð����� ������
	if (nexttime < curtime)
		return false;

	m_nextWarTime = nexttime;

	return true;
}

bool CDratanCastle::GiveLordItem(CPC* pc)
{
	return false; // ���ź�� ���� ���� ����
}

bool CDratanCastle::TakeLordItem(CPC* pc)
{
	CItem* item = NULL;

	if ((item = pc ->m_inventory.FindByDBIndex(GetLordItemIndex(pc->m_job, 1), 0, 0)) ||
			(item = pc->m_inventory.FindByDBIndex(GetLordItemIndex(pc->m_job, 2), 0, 0)) )
	{
		pc->m_inventory.decreaseItemCount(item, 1);
	}
	else if( (item = pc->m_wearInventory.FindByDBIndex(GetLordItemIndex(pc->m_job, 1))) ||
			 (item = pc->m_wearInventory.FindByDBIndex(GetLordItemIndex(pc->m_job, 2))) )
	{
		if (item->getWearPos() >= WEARING_SHOW_START && item->getWearPos() <= WEARING_SHOW_END && pc->m_pArea)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			WearingMsg(rmsg, pc, item->getWearPos(), -1, 0);
			pc->m_pArea->SendToCell(rmsg, pc, true);
		}

		pc->m_wearInventory.RemoveItem(item->getWearPos());
	}

	if (GetOwnerCharIndex() == pc->m_index)
	{
		m_bGiveLordWeapon = false;
	}
	return true;
}

int CDratanCastle::GetLordItemIndex(char job1, char job2)
{
	if (job2 == 0)
	{
		job2 = GetRandom(1, 2);
	}
	if (job2 < 1 || job2 > 2)
		return -1;

	const int itemindex[JOBCOUNT][2] =
	{
		{861, 862},
		{864, 863},
		{865, 866},
		{868, 867},
		{869, 870},
		{1070, 1071},
		{7274, 7274},
#ifdef EX_ROGUE
		{869, 870},
#endif // EX_ROGUE
#ifdef EX_MAGE
		{865, 866},
#endif // EX_MAGE
	};

	switch (job1)
	{
	case JOB_TITAN:
	case JOB_KNIGHT:
	case JOB_HEALER:
	case JOB_MAGE:
	case JOB_ROGUE:
	case JOB_SORCERER:
	case JOB_NIGHTSHADOW:
#ifdef EX_ROGUE
	case JOB_EX_ROGUE:
#endif // EX_ROGUE
#ifdef EX_MAGE
	case JOB_EX_MAGE:
#endif // EX_MAGE
		return itemindex[(int)job1][job2 - 1];
	default:
		return -1;
	}
}

bool CDratanCastle::IsDefenseWarpPoint(int pos)
{
	if (pos < 13 || pos > 17)
	{
		return false;
	}

	return true;
}

void CDratanCastle::InitGateNPC()
{
	memset(m_gateNPC, 0, sizeof(CNPC*) * COUNT_DRATAN_GATE_NPC);
	m_gateState = 0;
}

void CDratanCastle::GetInnerCastleRect(char* nYlayer, int* nX0x2, int* nZ0x2, int* nX1x2, int* nZ1x2)
{
	CZone* pZone = gserver->FindZone(GetZoneIndex());
	if (pZone == NULL)
		return;

	*nYlayer		= (char)(pZone->m_zonePos[26][0]);
	*nX0x2			= pZone->m_zonePos[26][1];
	*nZ0x2			= pZone->m_zonePos[26][2];
	*nX1x2			= pZone->m_zonePos[26][3];
	*nZ1x2			= pZone->m_zonePos[26][4];
}

CDratanCastle::CDratanCastle(const CDratanCastle & rhs)
	: CWarCastle()
{
}

CDratanCastle * CDratanCastle::CreateInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new CDratanCastle();
	}

	return pInstance;
}

void CDratanCastle::CheckWarCastle()
{
	///=== ���� ���� kjtest
	// ���� ���� ���̵� ����
	CheckDVD();

	SendCastleState( GetCurSubServerCastleZoneIndex() );

	// ���� NPC ó��
	CheckWarCastleNPC();

	CHECK_SUBSERVER(this);

	// ������ Ÿ��, ��Ȱ����
	CheckCastleControlNPC();

	// ���� ���� �˸�
	CheckWarCastleNotice();

	// ���� ����
	CheckWarCastleStartWarCastle();

	// ���� ��
	CheckWarCastleEnd();
	
	// ���� ����
	RegenLordSymbol();

	// ���� ����
	RegenShop();

	// ��Ȱ���� �����
	//CheckRegenRebirthNPC();
}

void CDratanCastle::CheckDVD()
{
	if(m_isNotChange == true)
		return;

	if(gserver->m_pulse - m_dvd.GetChangeTime() >= PULSE_REAL_HOUR)		// �ѽð� ���� 10% �϶�
	{
		if(m_dvd.GetMobRate() - 10 > 0)
		{
			m_dvd.ChangeMobRate(-10);
		}
		else
		{
			m_dvd.SetMobRate(0);
		}

		if(m_dvd.GetEnvRate() - 10 > 0)
		{
			m_dvd.ChangeEnvRate(-10);
		}
		else
		{
			m_dvd.SetEnvRate(0);
		}

		//����,�Ϲ� ���� ��� �߰�
		//���� ���� ����ε� 80���Ϸ� �϶� �Ͽ��� ��쿡�� �Ϲ� ���� ��ȯ
		if( m_dvd.GetOwnerMode() == true 
			&& m_dvd.checkOwnerMode() == false )
		{
			m_dvd.setOwnerMode(false);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				if(gserver->m_helper->isRun() == true)
				{
					HelperDVDNormalChangeNoticeMsg(rmsg);
					SEND_Q(rmsg, gserver->m_helper);
				}
			}
		}
		//

		//
		m_dvd.SetChangeTime(gserver->m_pulse);

		//
		m_dvd.ChangeSetting();

		GAMELOG << init("DRATAN DYNAMIC DUNGEON EVN CHANGE")
				<< "Env:" << m_dvd.GetEnvRate() << delim
				<< "Mob:" << m_dvd.GetMobRate() << end;

		{
			CNetMsg::SP rmsg(new CNetMsg);
			HelperDVDRateChangeMsg(rmsg, MSG_MANAGEMENT_ENV_CHANGE , m_dvd.GetEnvRate(), m_dvd.GetOwnerMode() );
			SEND_Q(rmsg, gserver->m_helper);
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			HelperDVDRateChangeMsg(rmsg, MSG_MANAGEMENT_STATE_CHANGE , m_dvd.GetMobRate(), m_dvd.GetOwnerMode() );
			SEND_Q(rmsg, gserver->m_helper);
		}
	}
}

bool CDratanCastle::CheckSubServer()
{
	return (GetZoneIndex() == GetCurSubServerCastleZoneIndex());
}

int CDratanCastle::GetCurSubServerCastleZoneIndex()
{
	switch (gserver->m_subno)
	{
	case WAR_CASTLE_SUBNUMBER_DRATAN:
		return ZONE_DRATAN;

	default:
		return -1;
	}
}

int CDratanCastle::CheckJoin(CPC* ch)
{
	if (ch->m_guildInfo)
	{
		CGuild * guild = ch->m_guildInfo->guild();
		// ���� ��� �˻�
		if (guild->index() == GetOwnerGuildIndex())
			return WCJF_OWNER;

		// ���� ��� �˻�
		if (IsAttackGuild(guild->index()))
			return WCJF_ATTACK_GUILD;

		// ���� ��� �˻�
		if (IsDefenseGuild(guild->index()))
			return WCJF_DEFENSE_GUILD;
	}

	return WCJF_NONE;
}

// ���� ���� �˸�
void CDratanCastle::CheckWarCastleNotice()
{
	switch (GetState())
	{
	case WCSF_NORMAL:
		// Ȯ�� �˸��� ������ �ƴϸ� ���� 10������ �˸��� ������ �˻�
		if (!m_bNoticeWarTime)
		{
			// ���� ��û ���� �ð����̰�
			if (!IsJoinTime())
				return ;

			// ���ӳ� ��� �������� �˸���
			{
				struct tm nextWarTime;
				GetNextWarTime(&nextWarTime, true);

				CNetMsg::SP rmsg(new CNetMsg);
				HelperWarNoticeTimeMsg(rmsg, GetZoneIndex(), nextWarTime.tm_mon, nextWarTime.tm_mday, nextWarTime.tm_hour, nextWarTime.tm_min);
				SEND_Q(rmsg, gserver->m_helper);
				m_bNoticeWarTime = true;
			}
		}
		else
		{
			struct tm nextWarTime;
			GetNextWarTime(&nextWarTime, true);
			int nexttime = GetNextWarTime();
			time_t curtime;
			time(&curtime);

			// ���� 10������ �źи���
			if (curtime + 10 * 60 >= nexttime)
			{
				// ���� �ð� ���ϱ�
				int remain = (nexttime - curtime) / 60;
				int modnum = (nexttime - curtime) % 60;
				if (modnum)
					remain++;
				if (remain != 0 && m_noticeRemain > remain && gserver->isRunHelper())
				{
					{
						CNetMsg::SP rmsg(new CNetMsg);
						HelperWarNoticeRemainMsg(rmsg, GetZoneIndex(), remain);
						SEND_Q(rmsg, gserver->m_helper);
					}

					m_noticeRemain = remain;

					// ����� ���� ��û
					if (curtime + 60 >= nexttime)
					{
						// �������� ��� ����Ʈ�� ���鼭
						// ����� ���̸� ���ۿ� ��û
						CGuild* p;
						for (p = gserver->m_guildlist.head(); p; p = p->nextguild())
						{
							if (p->battleZone() == GetZoneIndex())
							{
								switch (p->battleState())
								{
								case GUILD_BATTLE_STATE_WAIT:
								case GUILD_BATTLE_STATE_ING:
								case GUILD_BATTLE_STATE_STOP_WAIT:
									{
										CNetMsg::SP rmsg(new CNetMsg);
										HelperGuildBattleStopReqMsg(rmsg, p->index(), p->battleIndex());
										SEND_Q(rmsg, gserver->m_helper);
									}
									break;
								} // switch (p->battleState())
							} // if (p->battleZone() == GetZoneIndex())
						} // for (p = gserver->m_guildlist.head(); p; p = p->nextguild())
					} // if (curtime + 60 >= nexttime)
				} // if (remain != 0 && m_noticeRemain > remain && gserver->isRunHelper())
			} // if (curtime + 10 * 60 >= nexttime)

			// ���� 3���� �̵�
			if (!m_bMoveToRegen && curtime + 3 * 60 >= nexttime)
			{
				// ���� ����Ʈ �Ҵ�
				InitRegenPosition();

				// ���� ���̵� ��Ű��
				m_bMoveToRegen = true;
				MoveToRegenPoint();
			}

			// ������ ���� 1�� �����ʹ� �޸� ��ũ���� ����� �� ������ �ϱ� ����..
			if (!m_bWarCastleReady && (curtime + 1 * 60) >= nexttime)
			{
				m_bWarCastleReady = true;
			}
		}
		break;

	case WCSF_WAR_CASTLE:
		{
			if (m_bWarCastleReady)
				m_bWarCastleReady = false;
		}
		break;
	}
}

// ���� ����
void CDratanCastle::CheckWarCastleStartWarCastle()
{
	// ���� ���� �˻�
	if (GetState() != WCSF_NORMAL)
		return;

	// ���� ���� �ð��̻��̾�� �ϰ�
	time_t curTime;
	time(&curTime);
	int nextTime = GetNextWarTime();
	if (nextTime > curTime)
		return ;

	// �˸� �޽��� �ð� ���� ������ �ʱ�ȭ
	m_noticeRemain = 9999;

	SetOldOwnerChar( GetOwnerCharIndex() );

	// ���� ��û ��尡 ������ �������� �Ѿ
	if (m_attackGuildList == NULL)
	{
		SetState(WCSF_WAR_CASTLE);
		GAMELOG << init("WAR CASTLE : SKIP WAR") << GetZoneIndex() << end;
		return;
	}

	// ���� ����Ʈ �Ҵ�
	InitRegenPosition();

	// ���� ���̵� ��Ű��
	m_bMoveToRegen = true;

	// ���¸� �ٲٰ�
	SetState(WCSF_WAR_CASTLE);

	// ������ ���� ������ ��������
	GetOutNonDefense();

	// ���� ����Ʈ ����
//	RegenWarpNPC();		// ��ȣž ���� �Ҷ� ���� ����

	// ��ȣž ����
	RegenCastleTower();

	GAMELOG << init("WAR CASTLE : START WAR")
			<< GetZoneIndex() << end;

	// ���� ��� ���� ���
	CWarCastleJoin * pJoin = m_attackGuildList;
	while( pJoin != NULL )
	{
		GAMELOG << init("WAR CASTLE : JOIN ATTACK GUILD")
				<< pJoin->GetIndex() << end;
		pJoin = pJoin->GetNext();
	}

	pJoin = m_defenseGuildList;
	while( pJoin != NULL )
	{
		GAMELOG << init("WAR CASTLE : JOIN DEFANSE GUILD")
				<< pJoin->GetIndex() << end;
		pJoin = pJoin->GetNext();
	}

	// ������ Ÿ�� ���� �α�
	int i;
	GAMELOG << init("WAR CASTLE : REINFORCE SETTING");
	for( i = 0; i < 3; i++ )
	{
		GAMELOG << delim << (int)m_reinforce[i];
	}
	GAMELOG << end;

	// �˸� �޽��� �ð� ���� ������ �ʱ�ȭ
	m_noticeRemain = 9999;

	// ��� �������� ���� �ʱ�ȭ
	m_bLoop = true;

	// ���� ������ ���۸� ���� �˸���
	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperWarNoticeStartAttackCastleMsg(rmsg, GetZoneIndex(), GetRemainWarTime(), 0, 0, 0);
		SEND_Q(rmsg, gserver->m_helper);
	}

	{
		// ��Ȱ ���� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		CastletowerQuartersListMsg(rmsg, this);
		GetArea()->SendToAllClient(rmsg);
	}

	// ���� ���� ������ ���� ���� �̵�
	MoveingDVD();
}

// ���� ���� ������ ���� ���� �̵�
void CDratanCastle::MoveingDVD()
{
	// ���� ��� ���� ������ �̵�
	if (m_dvd.GetZone() == 0)
	{
		return;
	}

	m_dvd.GetZone()->m_area->MoveAllChar( ZONE_DRATAN, 27 );
}

void CDratanCastle::CheckWarCastleEnd()
{
	if (GetState() != WCSF_NORMAL)
	{
		if( gserver->getNowSecond() >= GetGuildGradeSkillTime() + APPLY_GUILD_GRADE_SKILL_TIME  )
		{
			SetGuildGradeSkillTime( gserver->getNowSecond() );
			ApplyGuildGradeSkillAll();
		}
	}

	// ���� ���� �˻�
	if (GetState() != WCSF_WAR_CASTLE)
		return;

	bool bFinished = false;

	// �ð��� ����Ǿ���?

	int endWarTime = GetNextWarTime() + CDratanCastle::WAR_TIME;

	time_t curTime;
	time(&curTime);
	if (endWarTime  <= curTime)
	{
		bFinished = true;
	}

	// ���� ��û ��尡 ������ �������� �Ѿ
	if (m_attackGuildList == NULL)
	{
		bFinished = true;
	}

	if (bFinished == false && m_bLoop == true)
		return;

	int oldOwnerCharIndex = GetOldOwnerChar();
	SetOldOwnerChar(0);
	if( oldOwnerCharIndex > 0)
	{
		CPC* pc = PCManager::instance()->getPlayerByCharIndex(oldOwnerCharIndex);
		if( pc ) // ������ ������ ȸ�� �Ѵ�.
		{
			pc->CastllanTitleDelete(-1, true);
			pc->m_inventory.CastllanItemRemove(-1, true, true); // �����Ѵ�.
		}
	}
	///== �¸��� ����

	char bWinDefense = (oldOwnerCharIndex == GetOwnerGuildIndex());

	ChangeGuildNameColor();

	// ����/��ȣž/��������Ʈ/����� ����
	RemoveLordSymbol();
	RemoveCastleTower();
//	RemoveWarpNPC();
	RemoveGuardNPC();

	// �� ������  ����
	RegenCastleNPC();

	GAMELOG << init("WAR CASTLE : END WAR")
			<< GetZoneIndex() << end;

	// �� ���� �ʱ�ȭ
	if(GetState() == WCSF_WAR_CASTLE)
		m_bWarCastleReady = false;
	SetState(WCSF_NORMAL);

	m_lastWarTime = endWarTime;
	SetNextWarTime(0);

	m_bNoticeWarTime = false;
	m_noticeRemain = 9999;
	m_gateState = 0;
	m_bMoveToRegen = false;

	m_countAttackGuild = 0;

	// DB �ʱ�ȭ
	CDBCmd cmd;
	cmd.Init(&gserver->m_dbcastle);

	std::string update_castle_sql = boost::str(boost::format(
										"UPDATE t_castle"
										" SET a_last_war_time = %d, a_state = 0, a_next_war_time = %d, a_owner_guild_index = %d, a_owner_guild_name = '%s', a_owner_char_index=%d, a_owner_char_name='%s'"
										" WHERE a_zone_index = %d")
									% m_lastWarTime % GetNextWarTime() % GetOwnerGuildIndex() % GetOwnerGuildName() % GetOwnerCharIndex() % GetOwnerCharName()
									% GetZoneIndex());
	cmd.SetQuery(update_castle_sql);
	if (!cmd.Update())
	{
		GAMELOG << init("SYS_ERR: CANNOT SAVE CASTLE INFO")
				<< "ZONE" << delim
				<< GetZoneIndex() << delim
				<< "OWNER" << delim
				<< GetOwnerGuildIndex() << delim
				<< GetOwnerGuildName() << delim
				<< "LASTTIME" << delim
				<< m_lastWarTime
				<< end;
	}
	else
	{
		GAMELOG << init("WAR CASTLE : SAVE WAR END")
				<< "ZONE"			<< delim << GetZoneIndex()											<< delim
				<< "LAST TIME"		<< delim << m_lastWarTime											<< delim
				<< "NEXT TIME"		<< delim << m_nextWarTime											<< delim
				<< "OWNER GUILD"	<< delim << GetOwnerGuildIndex() << delim << GetOwnerGuildName()	<< delim
				<< "OWNER CHAR"		<< delim << GetOwnerCharIndex() << delim << GetOwnerCharName()
				<< end;
	}

	std::string delete_castle_join_sql = boost::str(boost::format("DELETE FROM t_castle_join WHERE a_zone_index = %d") % GetZoneIndex());
	cmd.SetQuery(delete_castle_join_sql);
	if (!cmd.Update())
	{
		GAMELOG << init("SYS_ERR: CANNOT DELETE CASTLE JOIN INFO")
				<< "ZONE" << delim
				<< GetZoneIndex()
				<< end;
	}

	//  ����� �ʱ�ȭ
	m_GuardList.clean();
	std::string delete_castle_guard_sql = boost::str(boost::format("DELETE FROM t_castle_guard WHERE a_zone_num = %d") % GetZoneIndex());
	cmd.SetQuery(delete_castle_guard_sql);
	if (!cmd.Update())
	{
		GAMELOG << init("SYS_ERR: CANNOT DELETE CASTLE GUARD INFO")
				<< "ZONE" << delim
				<< GetZoneIndex()
				<< end;
	}

	// �������� �ʱ�ȭ
	ResetJoinFlag();

	// ���� ����Ʈ �ʱ�ȭ
	RemoveAllJoinList();

	// ������ Ÿ�� �ʱ�ȭ
	InitMasterTower();
	std::string delete_castle_tower_sql = boost::str(boost::format("DELETE FROM t_castle_tower WHERE a_zone_num = %d") % GetZoneIndex());
	cmd.SetQuery(delete_castle_tower_sql);
	if (!cmd.Update())
	{
		GAMELOG << init("SYS_ERR: CANNOT DELETE CASTLE GUARD INFO")
				<< "ZONE" << delim
				<< GetZoneIndex()
				<< end;
	}

	// ��ȣž ��ȭ �ʱ�ȭ
	InitReinforce();
	std::string delete_castle_reinforce_sql = boost::str(boost::format("DELETE FROM t_castle_reinforce WHERE a_zone_num = %d") % GetZoneIndex());
	cmd.SetQuery(delete_castle_reinforce_sql);
	if (!cmd.Update())
	{
		GAMELOG << init("SYS_ERR: CANNOT DELETE CASTLE TOWER REINFORCE")
				<< "ZONE" << delim
				<< GetZoneIndex()
				<< end;
	}

	// ��Ȱ ���� �ʱ�ȭ
	ResetRebrithNPC();
	std::string delete_castle_rebrith_sql = boost::str(boost::format("DELETE FROM t_castle_rebrith WHERE a_zone_num = %d") % GetZoneIndex());
	cmd.SetQuery(delete_castle_rebrith_sql);
	if (!cmd.Update())
	{
		GAMELOG << init("SYS_ERR: CANNOT DELETE CASTLE REBRITH")
				<< "ZONE" << delim
				<< GetZoneIndex()
				<< end;
	}

	// ������ Ÿ���� ��Ȱ���� �ٽ� ����
	RemoveCastleControlNPC();
	RegenCastleControlNPC();

	// ���� ��� �˸���
	struct tm tmJoin;
	GetJoinTime(&tmJoin, true);
	if (gserver->isRunHelper())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperWarNoticeEndMsg(rmsg, GetZoneIndex(), bWinDefense, GetOwnerGuildIndex(), GetOwnerGuildName(), GetOwnerCharIndex(), GetOwnerCharName(), tmJoin.tm_mon, tmJoin.tm_mday, tmJoin.tm_hour, tmJoin.tm_wday);
		SEND_Q(rmsg, gserver->m_helper);
	}
	else
	{
		{
			CNetMsg::SP rmsg(new CNetMsg);
			GuildWarEndMsg(rmsg, GetZoneIndex(), ((bWinDefense) ? (char)1 : (char)0), GetOwnerGuildIndex(), GetOwnerGuildName(), GetOwnerCharIndex(), GetOwnerCharName(), tmJoin.tm_mon, tmJoin.tm_mday, tmJoin.tm_hour, tmJoin.tm_wday);
			PCManager::instance()->sendToAll(rmsg);
		}

		EndWarRegenPoint();

		PCManager::map_t& playerMap			= PCManager::instance()->getPlayerMap();
		PCManager::map_t::iterator iter		= playerMap.begin();
		PCManager::map_t::iterator endIter	= playerMap.end();

		for (; iter != endIter; ++iter)
		{
			CPC* pc = (*iter).pPlayer;
			if (pc)
			{
				pc->CureGuildGradeSkill();
				// �ٷ� ������
				CNetMsg::SP rmsg(new CNetMsg);
				StatusMsg(rmsg, pc);
				SEND_Q(rmsg, pc->m_desc );
			}
		}
	}
}

// ������ �Ⱓ ���� �� ������ ����
void CDratanCastle::CheckWarCastleNPC()
{
	switch (m_state)
	{
	case WCSF_NORMAL:
		if (m_castleNPC == NULL || m_pDungeonNPC == NULL)
			RegenCastleNPC();
		break;

	default:
		if (m_castleNPC != NULL)
			RemoveCastleNPC();
		if ( m_pDungeonNPC != NULL )
			RemoveDungeonNPC();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// ���� ����
//////////////////////////////////////////////////////////////////////////

void CDratanCastle::CheckCastleControlNPC()
{
	if(m_bMaster == false)
	{
		RegenCastleControlNPC();
		m_bMaster = true;
	}
}

void CDratanCastle::RegenCastleControlNPC()
{
	// ������ Ÿ���� ��Ȱ����
	CHECK_SUBSERVER(this);

	CArea* area = GetArea();
	if (!area)
		return ;

	for (size_t i = 0; i < area->m_npcRegenList.m_infoList.size(); i++)
	{
		CNPCRegenInfo& p = area->m_npcRegenList.m_infoList.at(i);
		if (p.m_totalNum != 0)
			continue ;

		CNPCProto* proto = gserver->m_npcProtoList.FindProto(p.m_npcIdx);
		if (proto != NULL
				&& proto->CheckFlag(NPC_WARCASTLE) != 0
				&& proto->CheckFlag(NPC_CASTLE_TOWER) != 0)
		{
			CNPC * npc = gserver->m_npcProtoList.Create(proto->m_index, &p);
			if (!npc)
				return ;

			GET_X(npc) = p.m_regenX;
			GET_Z(npc) = p.m_regenZ;
			GET_R(npc) = p.m_regenR;
			GET_YLAYER(npc) = p.m_regenY;

			npc->m_regenX = GET_X(npc);
			npc->m_regenZ = GET_Z(npc);
			npc->m_regenY = GET_YLAYER(npc);

			npc->m_recoverPulse = gserver->m_pulse;

			p.m_bAlive = true;
			p.m_lastDieTime = 0;
			npc->m_disableTime = 0;

			npc->InitPointsToMax();
			area->AddNPC(npc);
			npc->m_postregendelay = 0;

			int cx, cz;
			area->PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
			area->CharToCell(npc, GET_YLAYER(npc), cx, cz);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, npc, true);
				area->SendToCell(rmsg, npc);
			}

			// ��Ȱ ���� ���
			SetRebrithNPC(npc);
		}
	}
}

void CDratanCastle::RemoveCastleControlNPC()
{
	CHECK_SUBSERVER(this);

	CArea* area = GetArea();
	if (!area)
		return ;

	CNPC* pNext = area->m_npcList;
	CNPC* p;
	while ((p = pNext))
	{
		pNext = p->m_pNPCNext;
		if (p->m_proto->CheckFlag(NPC_CASTLE_TOWER) != 0
				&& p->m_proto->CheckFlag(NPC_WARCASTLE) != 0)
		{
			p->SendDisappearAllInCell(true);

			// ���ø���Ʈ���� ����
			DelAttackList(p);

			// npc ����
			area->CharFromCell(p, true);
			area->DelNPC(p);
		}
	}

	InitMasterTower();
	InitRebrithNPC();
}

// ���� NPC ����
void CDratanCastle::RegenCastleNPC()
{
	if (m_castleNPC != NULL || m_pDungeonNPC != NULL )
		return;

	CArea* area = GetArea();
	if (!area)
		return ;

	int i;
	for (size_t i = 0; i < area->m_npcRegenList.m_infoList.size(); i++)
	{
		CNPCRegenInfo& p = area->m_npcRegenList.m_infoList.at(i);
		if (p.m_totalNum != 0)
			continue ;

		CNPCProto* proto = gserver->m_npcProtoList.FindProto(p.m_npcIdx);
		if (proto != NULL
				&& proto->CheckFlag(NPC_WARCASTLE) != 0
				&& ( proto->m_index == 387 || proto->m_index == 468 ) )
		{
			CNPC* pTempNPC = NULL;
			if( !m_pDungeonNPC && proto->m_index == 468 )
			{
				pTempNPC = m_pDungeonNPC = gserver->m_npcProtoList.Create(proto->m_index, &p);
			}
			else if( !m_castleNPC && proto->m_index == 387 )
			{
				pTempNPC = m_castleNPC = gserver->m_npcProtoList.Create(proto->m_index, &p);
			}

			if (!pTempNPC)
				return ;

			GET_X(pTempNPC) = p.m_regenX;
			GET_Z(pTempNPC) = p.m_regenZ;
			GET_R(pTempNPC) = p.m_regenR;
			GET_YLAYER(pTempNPC) = p.m_regenY;

			pTempNPC->m_regenX = GET_X(pTempNPC);
			pTempNPC->m_regenZ = GET_Z(pTempNPC);
			pTempNPC->m_regenY = GET_YLAYER(pTempNPC);

			pTempNPC->m_recoverPulse = gserver->m_pulse;

			p.m_bAlive = true;
			p.m_lastDieTime = 0;
			pTempNPC->InitPointsToMax();
			pTempNPC->m_disableTime = 0;

			pTempNPC->InitPointsToMax();
			area->AddNPC(pTempNPC);
			pTempNPC->m_postregendelay = 0;

			int cx, cz;
			area->PointToCellNum(GET_X(pTempNPC), GET_Z(pTempNPC), &cx, &cz);
			area->CharToCell(pTempNPC, GET_YLAYER(pTempNPC), cx, cz);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, pTempNPC, true);
				area->SendToCell(rmsg, pTempNPC);
			}

			GAMELOG << init("CASTLE NPC REGEN")
					<< "ZONE" << delim
					<< GetZoneIndex()
					<< delim << pTempNPC->m_idNum
					<< end;

			pTempNPC = NULL;
		}
	}
}

void CDratanCastle::RemoveCastleNPC()
{
	if (m_castleNPC == NULL)
		return ;
	CArea* area = m_castleNPC->m_pArea;
	if (area == NULL)
	{
		DelAttackList(m_castleNPC);
		delete m_castleNPC;
	}
	else
	{
		if( m_castleNPC )
		{
			m_castleNPC->SendDisappearAllInCell(true);
			DelAttackList(m_castleNPC);
			area->CharFromCell(m_castleNPC, true);
			area->DelNPC(m_castleNPC);
		}
	}
	m_castleNPC = NULL;
}

void CDratanCastle::RemoveDungeonNPC()  //pwesty remove new idea random cash shop npc
{
	if (m_pDungeonNPC == NULL)
		return ;
	CArea* area = m_pDungeonNPC->m_pArea;
	if (area == NULL)
	{
		DelAttackList(m_pDungeonNPC);
		delete m_pDungeonNPC;
	}
	else
	{
		if( m_pDungeonNPC )
		{
			m_pDungeonNPC->SendDisappearAllInCell(true);
			DelAttackList(m_pDungeonNPC);
			area->CharFromCell(m_pDungeonNPC, true);
			area->DelNPC(m_pDungeonNPC);
		}
	}
	m_pDungeonNPC = NULL;
}

// ���� Ÿ�� ����
void CDratanCastle::RegenCastleTower()
{
	CHECK_SUBSERVER(this);

	if (GetState() != WCSF_WAR_CASTLE)
		return ;

	CArea* area = GetArea();
	if (!area)
		return ;

	int regencount = 0;

	for(size_t i = 0; i < area->m_npcRegenList.m_infoList.size(); i++)
	{
		CNPCRegenInfo& p = area->m_npcRegenList.m_infoList.at(i);

		if (p.m_totalNum != 0 || p.m_bAlive || (gserver->m_pulse - p.m_lastDieTime < p.m_regenSec))
			continue ;

		CNPCProto* proto = gserver->m_npcProtoList.FindProto(p.m_npcIdx);
		if (proto && proto->CheckFlag(NPC_CASTLE_TOWER) && proto->CheckFlag(NPC_WARCASTLE) == 0)
		{
			// ������ Ÿ�� ���� �ݿ�
			if (CheckBuyTower(proto->m_index) == false)
			{
				continue;
			}

			CNPC* npc = gserver->m_npcProtoList.Create(proto->m_index, &p);
			if (!npc)
			{
				return;
			}

			GET_X(npc) = p.m_regenX;
			GET_Z(npc) = p.m_regenZ;
			GET_R(npc) = p.m_regenR;
			GET_YLAYER(npc) = p.m_regenY;

			npc->m_regenX = GET_X(npc);
			npc->m_regenZ = GET_Z(npc);
			npc->m_regenY = GET_YLAYER(npc);

			npc->m_recoverPulse = gserver->m_pulse;

			p.m_bAlive = true;
			p.m_lastDieTime = 0;
			npc->m_disableTime = 0;

			// ��ȣž ��ȭ ����
			SetTowerReinforce(npc);

			npc->InitPointsToMax();
			area->AddNPC(npc);
			npc->m_postregendelay = 0;

			int cx, cz;
			area->PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
			area->CharToCell(npc, GET_YLAYER(npc), cx, cz);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, npc, true);
				area->SendToCell(rmsg, npc);
			}

			// �������� NPC ����
			SetGateNPC(npc);

			// ���� Ÿ�� NPC ����
			SetWarpNPC(npc);

			regencount++;
		}
	}

	if (regencount > 0)
	{
		GAMELOG << init("CASTLE TOWER REGEN")
				<< "ZONE" << delim
				<< GetZoneIndex() << delim
				<< "COUNT" << delim
				<< regencount
				<< end;
	}
}

// ���� Ÿ�� ü�� 1/2 ����
void CDratanCastle::RegenCastleTowerHalf()
{
	if (GetState() != WCSF_WAR_CASTLE)
		return;

	RemoveCastleTower();

	CArea* area = GetArea();
	if (!area)
		return ;

	int regencount = 0;

	for (size_t i = 0; i < area->m_npcRegenList.m_infoList.size(); i++)
	{
		CNPCRegenInfo& p = area->m_npcRegenList.m_infoList.at(i);

		if (p.m_totalNum != 0
				|| p.m_bAlive
//			|| (gserver->m_pulse - p->m_lastDieTime < p->m_regenSec)		// Ÿ������ ���� �ð��� ���� ���� ����
		   )
		{
			continue ;
		}

		CNPCProto* proto = gserver->m_npcProtoList.FindProto(p.m_npcIdx);
		if (proto && proto->CheckFlag(NPC_CASTLE_TOWER) != 0 && proto->CheckFlag(NPC_WARCASTLE) == 0)
		{
			// ������ Ÿ�� ���� �ݿ�
			if (CheckBuyTower(proto->m_index) == false)
			{
				continue;
			}

			CNPC * npc = gserver->m_npcProtoList.Create(proto->m_index, &p);
			if (!npc)
			{
				return;
			}

			GET_X(npc) = p.m_regenX;
			GET_Z(npc) = p.m_regenZ;
			GET_R(npc) = p.m_regenR;
			GET_YLAYER(npc) = p.m_regenY;

			npc->m_regenX = GET_X(npc);
			npc->m_regenZ = GET_Z(npc);
			npc->m_regenY = GET_YLAYER(npc);

			npc->m_recoverPulse = gserver->m_pulse;

			p.m_bAlive = true;
			p.m_lastDieTime = 0;
			npc->m_disableTime = 0;

			// ��ȣž ��ȭ ����
			SetTowerReinforce(npc);

			npc->InitPointsToMax();
			area->AddNPC(npc);
			npc->m_postregendelay = 0;

			int cx, cz;
			area->PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
			area->CharToCell(npc, GET_YLAYER(npc), cx, cz);

			// ü�� 1/2 ����
			npc->m_hp = npc->m_proto->m_hp / 2;
			npc->m_maxHP = npc->m_hp;

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, npc, true);
				area->SendToCell(rmsg, npc);
			}

			// �������� NPC ����
			SetGateNPC(npc);

			// ���� Ÿ�� NPC ����
			SetWarpNPC(npc);

			regencount++;
		}
	}

	if (regencount > 0)
	{
		GAMELOG << init("CASTLE TOWER REGEN HALF")
				<< "ZONE" << delim
				<< GetZoneIndex() << delim
				<< "COUNT" << delim
				<< regencount
				<< end;
	}
}

// ���� Ÿ�� ����
void CDratanCastle::RemoveCastleTower()
{
	CHECK_SUBSERVER(this);

	CArea* area = GetArea();
	if (!area)
		return ;

	CNPC* pNext = area->m_npcList;
	CNPC* p;
	while ((p = pNext))
	{
		pNext = p->m_pNPCNext;
		if (p->m_proto->CheckFlag(NPC_CASTLE_TOWER) != 0
				&& p->m_proto->CheckFlag(NPC_WARCASTLE) == 0)
		{
			p->SendDisappearAllInCell(true);

			// ���ø���Ʈ���� ����
			DelAttackList(p);

			// npc ����
			area->CharFromCell(p, true);
			area->DelNPC(p);
		}
	}

	InitGateNPC();
	InitWarpNPC();
}

// ���� ���� ����
void CDratanCastle::RegenShop()
{
	CHECK_SUBSERVER(this);

	if (!m_bRegenShop && GetState() == WCSF_NORMAL)
	{
		m_bRegenShop = true;

		CArea* area = GetArea();
		if (!area)
			return ;

		int i;
		for (i = 0; i < area->m_zone->m_nShopCount; i++)
		{
			if ( !(area->GetAttr(area->m_zone->m_shopList[i].m_yLayer, area->m_zone->m_shopList[i].m_x, area->m_zone->m_shopList[i].m_z) & MATT_WAR) )
				continue ;

			CNPC* npc = gserver->m_npcProtoList.Create(area->m_zone->m_shopList[i].m_keeperIdx, NULL);
			if (!npc)
				return ;

			GET_X(npc) = area->m_zone->m_shopList[i].m_x;
			GET_Z(npc) = area->m_zone->m_shopList[i].m_z;
			GET_R(npc) = area->m_zone->m_shopList[i].m_r;
			GET_YLAYER(npc) = area->m_zone->m_shopList[i].m_yLayer;

			npc->m_regenX = GET_X(npc);
			npc->m_regenZ = GET_Z(npc);
			npc->m_regenY = GET_YLAYER(npc);

			npc->m_recoverPulse = gserver->m_pulse;

			npc->InitPointsToMax();
			npc->m_disableTime = 0;

			npc->InitPointsToMax();
			area->AddNPC(npc);
			npc->m_postregendelay = 0;

			int cx, cz;
			area->PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
			area->CharToCell(npc, GET_YLAYER(npc), cx, cz);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, npc, true);
				area->SendToCell(rmsg, npc);
			}

			GAMELOG << init("CASTLE SHOP REGEN")
					<< "ZONE" << delim
					<< GetZoneIndex() << delim
					<< "SHOP" << delim
					<< npc->m_name << delim
					<< GET_X(npc) << delim
					<< GET_Z(npc)
					<< end;
		}
	}
	else if (m_bRegenShop && GetState() == WCSF_WAR_CASTLE)
	{
		m_bRegenShop = false;

		CArea* area = GetArea();
		if (!area)
			return ;

		CNPC* pNext = area->m_npcList;
		CNPC* p;
		while ((p = pNext))
		{
			pNext = p->m_pNPCNext;
			if (p->m_proto->CheckFlag(NPC_SHOPPER) && p->GetMapAttr() & MATT_WAR)
			{
				p->SendDisappearAllInCell(true);

				// ���ø���Ʈ���� ����
				DelAttackList(p);

				// npc ����
				area->CharFromCell(p, true);
				area->DelNPC(p);
			}
		}
	}
}

//  ���� ũ����Ż ����
void CDratanCastle::RegenLordSymbol()
{
	CHECK_SUBSERVER(this);

	if (m_lordSymbol != NULL || GetState() != WCSF_WAR_CASTLE)
		return ;

	CArea* area = GetArea();
	if (!area)
		return ;

	int i;
	for (size_t i = 0; i < area->m_npcRegenList.m_infoList.size(); i++)
	{
		CNPCRegenInfo& p = area->m_npcRegenList.m_infoList.at(i);
		if (p.m_totalNum != 0 || p.m_bAlive || (gserver->m_pulse - p.m_lastDieTime < p.m_regenSec))
			continue ;

		CNPCProto* proto = gserver->m_npcProtoList.FindProto(p.m_npcIdx);
		if (proto && proto->CheckFlag(NPC_LORD_SYMBOL))
		{
			m_lordSymbol = gserver->m_npcProtoList.Create(proto->m_index, &p);
			if (!m_lordSymbol)
				return ;

			GET_X(m_lordSymbol) = p.m_regenX;
			GET_Z(m_lordSymbol) = p.m_regenZ;
			GET_R(m_lordSymbol) = p.m_regenR;
			GET_YLAYER(m_lordSymbol) = p.m_regenY;

			m_lordSymbol->m_regenX = GET_X(m_lordSymbol);
			m_lordSymbol->m_regenZ = GET_Z(m_lordSymbol);
			m_lordSymbol->m_regenY = GET_YLAYER(m_lordSymbol);

			m_lordSymbol->m_recoverPulse = gserver->m_pulse;

			p.m_bAlive = true;
			p.m_lastDieTime = 0;
			m_lordSymbol->InitPointsToMax();
			m_lordSymbol->m_disableTime = 0;

			m_lordSymbol->InitPointsToMax();
			area->AddNPC(m_lordSymbol);
			m_lordSymbol->m_postregendelay = 0;

			int cx, cz;
			area->PointToCellNum(GET_X(m_lordSymbol), GET_Z(m_lordSymbol), &cx, &cz);
			area->CharToCell(m_lordSymbol, GET_YLAYER(m_lordSymbol), cx, cz);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, m_lordSymbol, true);
				area->SendToCell(rmsg, m_lordSymbol);
			}

			GAMELOG << init("LORD SYMBOL REGEN")
					<< "ZONE" << delim
					<< GetZoneIndex()
					<< end;

			// TODO : ���¸� 2���̻� ��ġ�� break ���� �� ���� ����
			break;
		}
	}
}

void CDratanCastle::RemoveLordSymbol()
{
	CHECK_SUBSERVER(this);

	if (m_lordSymbol == NULL)
		return ;
	CArea* area = m_lordSymbol->m_pArea;
	if (!area)
	{
		DelAttackList(m_lordSymbol);
		delete m_lordSymbol;
	}
	else
	{
		m_lordSymbol->SendDisappearAllInCell(true);
		DelAttackList(m_lordSymbol);
		area->CharFromCell(m_lordSymbol, true);
		area->DelNPC(m_lordSymbol);
	}
	m_lordSymbol = NULL;
}

// ���� ����� ����
void CDratanCastle::RegenGuardNPC()
{
	CHECK_SUBSERVER(this);

//	if (GetState() == WCSF_NORMAL)
//		return;

	CArea * area = GetArea();
	if (area == NULL)
	{
		return;
	}

	int regencount = 0;

	int i;
	for (size_t i = 0; i < area->m_npcRegenList.m_infoList.size(); i++)
	{
		CNPCRegenInfo& p = area->m_npcRegenList.m_infoList.at(i);
//		if (gserver->m_pulse - p->m_lastDieTime < p->m_regenSec)
//		{	// ���� �ð� üũ
//			continue;
//		}

		if (!p.m_bRegen) // skip inactive NPCs
			continue;

		CNPCProto* proto = gserver->m_npcProtoList.FindProto(p.m_npcIdx);
		if (proto && proto->CheckFlag(NPC_CASTLE_GUARD))
		{
			CNPC* npc = gserver->m_npcProtoList.Create(proto->m_index, &p);
			if (!npc)
				return ;

			GET_X(npc) = p.m_regenX;
			GET_Z(npc) = p.m_regenZ;
			GET_R(npc) = p.m_regenR;
			GET_YLAYER(npc) = p.m_regenY;

			npc->m_regenX = GET_X(npc);
			npc->m_regenZ = GET_Z(npc);
			npc->m_regenY = GET_YLAYER(npc);

			npc->m_recoverPulse = gserver->m_pulse;

			p.m_bAlive = true;
			p.m_lastDieTime = 0;
			npc->InitPointsToMax();
			npc->m_disableTime = 0;

			npc->InitPointsToMax();
			area->AddNPC(npc);
			npc->m_postregendelay = 0;

			int cx, cz;
			area->PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
			area->CharToCell(npc, GET_YLAYER(npc), cx, cz);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, npc, true);
				area->SendToCell(rmsg, npc);
			}

			regencount++;
		}
	}

	if (regencount > 0)
	{
		GAMELOG << init("GUARD NPC REGEN")
				<< "ZONE" << delim
				<< GetZoneIndex() << delim
				<< "COUNT" << delim
				<< regencount
				<< end;
	}
}

void CDratanCastle::RemoveGuardNPC()
{
	CHECK_SUBSERVER(this);

	CArea* area = GetArea();
	if (!area)
		return ;

	CNPC* pNext = area->m_npcList;
	CNPC* p;
	while ((p = pNext))
	{
		pNext = p->m_pNPCNext;
		if (p->m_proto->CheckFlag(NPC_CASTLE_GUARD))
		{
			p->SendDisappearAllInCell(true);

			// ���ø���Ʈ���� ����
			DelAttackList(p);

			// npc ����
			area->CharFromCell(p, true);
			area->DelNPC(p);
		}
	}

	for (size_t i = 0; i < area->m_npcRegenList.m_infoList.size(); i++)
	{
		CNPCRegenInfo& p = area->m_npcRegenList.m_infoList.at(i);
		if (!p.m_bRegen) continue;

		CNPCProto* proto = gserver->m_npcProtoList.FindProto(p.m_npcIdx);
		if (proto && proto->CheckFlag(NPC_CASTLE_GUARD))
		{
			if(area->m_npcRegenList.DelRegenInfo(&p) == true)
			{
				i--;	// �������� �� ��ġ���� �ٽ� �˻�
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// �ð� ����
//////////////////////////////////////////////////////////////////////////
// ���� ���� �ð� ��������
void CDratanCastle::GetNextWarTime(struct tm* nextWarTime, bool bHumanable)
{
	time_t tNext = (time_t)GetNextWarTime();
	memcpy(nextWarTime, localtime(&tNext), sizeof(struct tm));
	if (bHumanable)
	{
		nextWarTime->tm_year += 1900;
		nextWarTime->tm_mon += 1;
	}
}

//////////////////////////////////////////////////////////////////////////
// �ʱ�ȭ
//////////////////////////////////////////////////////////////////////////
bool CDratanCastle::LoadCastleData()
{
	CWarCastle::LoadCastleData();

	// ������ ������ ����� ���� �ε�
	m_GuardList.init(3, 10); // 3���� ���� 10����

	CDBCmd cmd;
	cmd.Init(&gserver->m_dbcastle);

	std::string select_castle_guard_sql = boost::str(boost::format("SELECT * FROM t_castle_guard WHERE a_zone_num=%d") % ZONE_DRATAN);
	cmd.SetQuery(select_castle_guard_sql);

	if (cmd.Open() == false)
	{
		return false;
	}

	int regensec = 20*60*10;
	int mobindex;
	float x, z, r;
//	float h;

	CArea * pArea = GetArea();
	if( pArea == NULL)
	{
		return false;
	}

	while (cmd.MoveNext() == true)
	{
		cmd.GetRec("a_npc_idx", mobindex);
		cmd.GetRec("a_pos_x", x);
		cmd.GetRec("a_pos_z", z);

		r = GetRandom(0, (int) (PI_2 * 10000)) / 10000;

		m_GuardList.InsertGuard(mobindex, x, z, 0);

//		pArea->m_npcRegenList.AddRegenInfo(pArea->m_npcRegenList.m_wPos, mobindex, regensec, x, 0, z, r, 0, ZONE_DRATAN);
		pArea[0].m_npcRegenList.AddRegenInfo(pArea->m_npcRegenList.m_wPos, mobindex, regensec, x, 0, z, r, 1, ZONE_DRATAN);
	}

	// ��ȣ�� NPC ó��
	RegenGuardNPC();

	// ������ Ÿ�� ���� �ε�
	std::string select_castle_tower_sql = boost::str(boost::format("SELECT * FROM t_castle_tower WHERE a_zone_num=%d") % ZONE_DRATAN);
	cmd.SetQuery(select_castle_tower_sql);
	if (cmd.Open() == false)
	{
		return false;
	}
	int rowid = 0, colid = 0;
	while (cmd.MoveNext() == true)
	{
		cmd.GetRec("rowid", rowid);
		cmd.GetRec("status", colid);
		SetTowerStatus(rowid, (char)colid);
	}

	// ��ȣž ��ȭ ���� �ε�
	std::string select_castle_reinforce_sql = boost::str(boost::format("SELECT * FROM t_castle_reinforce WHERE a_zone_num=%d") % ZONE_DRATAN);
	cmd.SetQuery(select_castle_reinforce_sql);
	if (cmd.Open() == false)
	{
		return false;
	}
	char type = 0, step = 0;
	while (cmd.MoveNext() == true)
	{
		cmd.GetRec("a_type", type);
		cmd.GetRec("a_step", step);
		SetReinforceStep(type, step);
	}

	// ��Ȱ ���� ���� �ε�
	std::string select_castle_rebrith_sql = boost::str(boost::format("SELECT * FROM t_castle_rebrith WHERE a_zone_num=%d") % ZONE_DRATAN);
	cmd.SetQuery(select_castle_rebrith_sql);
	if (cmd.Open() == false)
	{
		return false;
	}
	int qindex = 0, gindex = 0;
	CLCString gname(MAX_CHAR_NAME_LENGTH + 1);
	while (cmd.MoveNext() == true)
	{
		cmd.GetRec("a_npc_idx", qindex);
		cmd.GetRec("a_guild_idx", gindex);
		cmd.GetRec("a_guild_name", gname);

		m_nRebrithGuild[qindex-390] = gindex;
		strncpy(m_strRebrithGuild[qindex-390], (const char *)gname, 51);
	}

	std::string select_castle_dungeon_sql = boost::str(boost::format("SELECT * FROM t_castle_dungeon"));
	cmd.SetQuery(select_castle_dungeon_sql);
	if(cmd.Open() == false)
	{
		return false;
	}

	int env_rate = 50;
	int mop_rate = 50;
	int tax_rate = 100;
	int hunt_rate = 0;
	int mode = 0;
	int normal_time = 0;
	while(cmd.MoveNext() == true)
	{
		cmd.GetRec("a_env_rate", env_rate);
		m_dvd.SetEnvRate(env_rate);
		cmd.GetRec("a_mop_rate", mop_rate);
		m_dvd.SetMobRate(mop_rate);
		cmd.GetRec("a_tax_rate", tax_rate);
		m_dvd.SetFeeRate(tax_rate);
		cmd.GetRec("a_hunt_rate", hunt_rate);
		m_dvd.SetHuntRate(hunt_rate);
		cmd.GetRec("a_mode", mode);
		m_dvd.setOwnerMode(mode);
		if(m_dvd.GetOwnerMode() == false)
		{
			cmd.GetRec("a_change_normal_time", normal_time);
			m_dvd.setChangeNormalTime(normal_time);
		}
	}

	return true;
}

void CDratanCastle::InitRegenPosition()
{
	if (m_posRegenPoint)
		delete [] m_posRegenPoint;
	m_nRegenPoint = 0;
	m_posRegenPoint = NULL;

	if (m_countAttackGuild > 0)
	{
		int* tmp = new int[m_countAttackGuild];
		memset(tmp, 0, sizeof(int) * m_countAttackGuild);

		CWarCastleJoin* p = m_attackGuildList;
		int i = 0;
		while (p)
		{
			tmp[i] = p->GetIndex();
			i++;
			p = p->GetNext();
		}

		// �������� ����
		for (i = 0; i < m_countAttackGuild; i++)
		{
			int j = GetRandom(0, m_countAttackGuild - 1);
			int s = tmp[i];
			tmp[i] = tmp[j];
			tmp[j] = s;
		}

		// ���� ���� �ִ� 8��
		m_nRegenPoint = (m_countAttackGuild < 8) ? m_countAttackGuild : 8;
		m_posRegenPoint = new int[m_nRegenPoint];

		memcpy(m_posRegenPoint, tmp, sizeof(int) * m_nRegenPoint);

		delete [] tmp;
	}
}

void CDratanCastle::ResetOwner()
{
	m_ownerGuildIndex = 0;
	m_ownerGuildName = "";
	m_ownerCharIndex = 0;
	m_ownerCharName = "";
	m_oldOwnerCharIndex = 0;
}

void CDratanCastle::SetOwner(CGuild* guild)
{
	if (guild)
	{
		m_ownerGuildIndex = guild->index();
		m_ownerGuildName = guild->name();
		m_ownerCharIndex = guild->boss()->charindex();
		m_ownerCharName = guild->boss()->GetName();
	}
	else
	{
		ResetOwner();
	}
}

void CDratanCastle::CheckRespond(CPC * ch)
{
	// ���� ���̸� ���� ���
	if(ch->IsSetPlayerState(PLAYER_CRISTAL_RESPOND) == true)
	{
		if (ch->m_pZone != NULL
				&& ch->m_pZone->m_index == ZONE_DRATAN)
		{
			if(GetState() == WCSF_WAR_CASTLE)
			{
				// �������̸� ���� ���� ����Ʈ ���̱�
				CNetMsg::SP rmsg(new CNetMsg);
				CastleCristalRespondFailMsg(rmsg, ch);
				ch->m_pArea->SendToCell(rmsg, ch, true);
			}
		}
		// ���� ����
		ResetRespondMeber(ch);
	}
}

char CDratanCastle::GetReinforceStep(int i)
{
	if( i >= 0 && i < 3)
	{
		return m_reinforce[i];
	}
	return -1;
}

void CDratanCastle::SetReinforceStep(char i, char v)
{
	if( i >= 0 && i < 3 && v > -1 && v < 4)
	{
		m_reinforce[(int)i] = v;
	}
}

bool CDratanCastle::CheckBuyTower(int index)
{
	if( index >= 352
			&& index <= 386)
	{
		// ��ȣž
		int rows = (index - 352)/5;
		int limit_npc = (352 + rows*5 ) + (int)(GetTowerStatus(rows));
		if(index >= limit_npc)
		{
			return false;
		}
	}

	return true;
}

void CDratanCastle::SetTowerReinforce(CNPC * npc)
{
	int type = (npc->m_proto->m_index - 352) / 5;
	if (type >=0 && type < 3)
	{
		type = 0;
	}
	else if (type >=3 && type < 6)
	{
		type = 1;
	}
	else if(npc->m_proto->m_index == 388
			|| npc->m_proto->m_index == 389
			|| npc->m_proto->m_index == 404)
	{
		type = 2;
	}
	else
	{
		return;
	}

	switch (m_reinforce[type])
	{
	case 1:
		npc->m_opMelee = npc->m_opMelee + (npc->m_eqMelee*30)/100;
		npc->m_opRange = npc->m_opRange + (npc->m_eqRange*30)/100;
		npc->m_opMagic = npc->m_opMagic + (npc->m_eqMagic*30)/100;
		return;

	case 2:
		npc->m_opMelee = npc->m_opMelee + (npc->m_eqMelee*50)/100;
		npc->m_opRange = npc->m_opRange + (npc->m_eqRange*50)/100;
		npc->m_opMagic = npc->m_opMagic + (npc->m_eqMagic*50)/100;

		npc->m_maxHP =  npc->m_maxHP + (npc->m_maxHP*50)/100;
		return;

	case 3:
		npc->m_opMelee = npc->m_opMelee + npc->m_eqMelee;
		npc->m_opRange = npc->m_opRange + npc->m_eqRange;
		npc->m_opMagic = npc->m_opMagic + npc->m_eqMagic;

		npc->m_maxHP =  npc->m_maxHP*2;
		return;

	default:
		return;
	}
}

void CDratanCastle::ChangeSide(int gindex)
{
	// ��� �� ��� ��� �������� �ʱ�ȭ
	CGuild * pGuild = gserver->m_guildlist.findguild(gindex);
	// ���� ��忡�� ����
	RemoveAttackGuild(gindex);

	if (pGuild)
	{
		// ���� ���� ���� ���� ��ȯ
		int j;
		int guildMaxMember = pGuild->maxmember();
		for (j = 0; j < guildMaxMember; j++)
		{
			if (pGuild->member(j) && pGuild->member(j)->GetPC())
			{
				pGuild->member(j)->GetPC()->SetJoinFlag(ZONE_DRATAN, WCJF_OWNER);
//				pGuild->member(j)->GetPC()->m_bChangeStatus = true;
				// �ٷ� ������
				CNetMsg::SP rmsg(new CNetMsg);
				StatusMsg(rmsg, pGuild->member(j)->GetPC());
				SEND_Q(rmsg, pGuild->member(j)->GetPC()->m_desc);
			}
		}
	}

	// ���� ���� DB�� ����
	// a_index ��� �ε��� or ĳ���� �ε���
	// a_guild 1�̸� ��� ���� 0�̸� ����
	// a_attack 1�̸� ���� 0 �̸� ����
	std::string delete_castle_join_sql = boost::str(boost::format("DELETE FROM t_castle_join WHERE a_zone_index=%d AND a_index=%d AND a_guild=1") % ZONE_DRATAN % gindex);
	CDBCmd cmd;
	cmd.Init(&gserver->m_dbcastle);
	cmd.SetQuery(delete_castle_join_sql);
	cmd.Update();

	// ���� ��� ����
	if(m_defenseGuildList != NULL)
	{
		CWarCastleJoin * pJoin = m_defenseGuildList;
		while ( pJoin != NULL && pJoin->GetIndex() > 0)
		{
			int tindex = pJoin->GetIndex();
			ChangeAttackGuild(tindex);

			pJoin = pJoin->GetNext();

			RemoveDefenseGuild(tindex);
		}
	}

	// ���� ���� ��� ó��
	ChangeAttackGuild(GetOwnerGuildIndex());
}

void CDratanCastle::ChangeAttackGuild(int gindex)
{
	CGuild * pGuild = gserver->m_guildlist.findguild(gindex);
	AddAttackGuild(gindex);

	if (pGuild)
	{
		// ���� ���� ���� ���� ��ȯ
		int j;
		int guildMaxMember = pGuild->maxmember();
		for (j = 0; j < guildMaxMember; j++)
		{
			if (pGuild->member(j) && pGuild->member(j)->GetPC())
			{
				pGuild->member(j)->GetPC()->SetJoinFlag(ZONE_DRATAN, WCJF_ATTACK_GUILD);

				// �ٷ� ������
				CNetMsg::SP rmsg(new CNetMsg);
				StatusMsg(rmsg, pGuild->member(j)->GetPC());
				SEND_Q(rmsg, pGuild->member(j)->GetPC()->m_desc);
			}
		}
	}

	// ���� ���� DB�� ����
	CDBCmd cmd;
	cmd.Init(&gserver->m_dbcastle);

	std::string delete_castle_join_sql = boost::str(boost::format("DELETE FROM t_castle_join WHERE a_index=%d") % gindex);
	cmd.SetQuery(delete_castle_join_sql);
	cmd.Update();

	std::string insert_castle_join_sql = boost::str(boost::format("INSERT INTO t_castle_join (a_zone_index, a_index, a_guild, a_attack) VALUES (%d, %d, 1, 1)") % ZONE_DRATAN % gindex);
	cmd.SetQuery(insert_castle_join_sql);
	cmd.Update();
}

int CDratanCastle::GetRemainWarTime()
{
	int startTime = GetNextWarTime();
	int endTime = startTime + CDratanCastle::WAR_TIME;
	time_t curTime;
	time(&curTime);

	return endTime - curTime;
}

void CDratanCastle::GetOutNonDefense()
{
	CZone*		pZone	= gserver->FindZone(GetZoneIndex());
	if (pZone == NULL)
		return;

	CArea*		pArea	= pZone->m_area;

	char		nYlayer	= 0;
	int			nX0x2	= 0;
	int			nZ0x2	= 0;
	int			nX1x2	= 0;
	int			nZ1x2	= 0;
	GetInnerCastleRect(&nYlayer, &nX0x2, &nZ0x2, &nX1x2, &nZ1x2);

	int			nCellX0	= 0;
	int			nCellZ0	= 0;
	int			nCellX1	= 0;
	int			nCellZ1	= 0;
	pArea->PointToCellNum(nX0x2 / 2.0f, nZ0x2 / 2.0f, &nCellX0, &nCellZ0);
	pArea->PointToCellNum(nX1x2 / 2.0f, nZ1x2 / 2.0f, &nCellX1, &nCellZ1);

	// ���� �̵���ų ������ ������ �̵� // �ٸ����� �̵��� �Ǵ� �̵��� ������ ���� �߻�

	std::vector<CPC*> m_MovePCList;
	int cx, cz;
	for (cx = nCellX0; cx <= nCellX1; cx++)
	{
		if (cx < 0 || cx >= pArea->m_size[0])
			continue ;

		for (cz = nCellZ0; cz <= nCellZ1; cz++)
		{
			if (cz < 0 || cz >= pArea->m_size[1])
				continue ;

			CCell& rCell = pArea->m_cell[cx][cz];
			CCharacter* pCharNext = rCell.m_listChar;
			CCharacter* pChar;
			while ((pChar = pCharNext))
			{
				pCharNext = pCharNext->m_pCellNext;
				if (IS_PC(pChar))
				{
					CPC* pPC = TO_PC(pChar);
					if (pPC)
					{
						m_MovePCList.push_back( pPC );
					}
				}
			}
		}
	}

	std::vector<CPC*>::iterator it = m_MovePCList.begin();
	std::vector<CPC*>::iterator endit = m_MovePCList.end();
	for(; it != endit; ++it)
	{
		CPC* movePc = *(it);

		ApplyWarSkill(movePc, GetZoneIndex());

		int nJoinFlag = movePc->GetJoinFlag(pZone->m_index);
		if (IsInInnerCastle(movePc))
		{
			int extra = GetRegenPoint(nJoinFlag, movePc);

#ifdef WARCASTLE_MOVE_MESSAGE_LIMIT
			if( !( movePc->m_pZone->m_index == GetZoneIndex()
					&& movePc->m_pZone->InExtra( (int)GET_X(movePc), (int)GET_Z(movePc) ,extra ) ) )
#endif
			{
				GoZone(movePc, pZone->m_index,
					   pZone->m_zonePos[extra][0],
					   GetRandom(pZone->m_zonePos[extra][1], pZone->m_zonePos[extra][3]) / 2.0f,
					   GetRandom(pZone->m_zonePos[extra][2], pZone->m_zonePos[extra][4]) / 2.0f);
				movePc->SetDisableTime(1);
			}
		}
	}

	m_MovePCList.clear();
}

bool CDratanCastle::IsInInnerCastle(CCharacter* pChar)
{
	char		nYlayer	= 0;
	int			nX0x2	= 0;
	int			nZ0x2	= 0;
	int			nX1x2	= 0;
	int			nZ1x2	= 0;
	GetInnerCastleRect(&nYlayer, &nX0x2, &nZ0x2, &nX1x2, &nZ1x2);

	if (nX0x2 / 2.0f > GET_X(pChar) || GET_X(pChar) > nX1x2 / 2.0f || nZ0x2 / 2.0f > GET_Z(pChar) || GET_Z(pChar) > nZ1x2 / 2.0f)
		return false;
	else
		return true;
}

bool CDratanCastle::CanLordChat(CPC* pc)
{
	switch (gserver->m_subno)
	{
	case WAR_CASTLE_SUBNUMBER_DRATAN:
		if (GetState() != WCSF_NORMAL)
			return false;
		if (GetOwnerCharIndex() != pc->m_index)
			return false;
		return true;

	default:
		return false;
	}
}

bool CDratanCastle::AddAttackGuild(int index)
{
	CWarCastleJoin * p = new CWarCastleJoin(index, 1);
	if (m_attackGuildList == NULL)
	{
		m_attackGuildList = p;
	}
	else
	{
		p->SetNext(m_attackGuildList);
		m_attackGuildList->SetPrev(p);
		m_attackGuildList = p;
	}

	m_countAttackGuild++;

	return true;
}

bool CDratanCastle::AddDefenseGuild(int index)
{
	CWarCastleJoin* p = new CWarCastleJoin(index, 1);
	if (m_defenseGuildList == NULL)
	{
		m_defenseGuildList = p;
	}
	else
	{
		p->SetNext(m_defenseGuildList);
		m_defenseGuildList->SetPrev(p);
		m_defenseGuildList = p;
	}

	return true;
}

bool CDratanCastle::IsAttackGuild(int index)
{
	return (FindAttackGuild(index)) ? true : false;
}

bool CDratanCastle::IsDefenseGuild(int index)
{
	return (FindDefenseGuild(index)) ? true : false;
}

void CDratanCastle::MoveToRegenPoint()
{
	CZone* pZone = gserver->FindZone(ZONE_DRATAN);
	if (pZone == NULL)
		return;

	PCManager::map_t& playerMap			= PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter		= playerMap.begin();
	PCManager::map_t::iterator endIter	= playerMap.end();
	for(; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if( pc )
		{
			int extra = GetRegenPoint(pc->GetJoinFlag(ZONE_DRATAN), pc);
			if (extra == 0)
				continue ;

#ifdef WARCASTLE_MOVE_MESSAGE_LIMIT
			if(!( pc->m_pZone->m_index == GetZoneIndex()
					&& pc->m_pZone->InExtra( (int)GET_X(pc), (int)GET_Z(pc) ,extra)) )
#endif
			{
				// Ȯ�� �޽��� ����
				CNetMsg::SP rmsg(new CNetMsg);
				WarpPromptMsg(rmsg, pZone->m_index, extra);
				SEND_Q(rmsg, pc->m_desc);
			}
		}
	}
}

void CDratanCastle::StopCastleTower()
{
	CHECK_SUBSERVER(this);

	CArea* area = GetArea();
	if (!area)
		return ;

	CNPC* pNext = area->m_npcList;
	CNPC* p;
	while ((p = pNext))
	{
		pNext = p->m_pNPCNext;
		if (p->m_proto->CheckFlag(NPC_CASTLE_TOWER) != 0
				&& p->m_proto->CheckFlag(NPC_WARCASTLE) == 0
				&& p->m_proto->m_index != 388
				&& p->m_proto->m_index != 389
				&& p->m_proto->m_index != 404 )
		{
			// ������ Ÿ������ ������ Ÿ���� ����
			p->m_hp = 0;
		}
	}

	// ���� Ÿ�� ���� �ʱ�ȭ
	InitWarpNPC();
}

void CDratanCastle::ChangeGuildNameColor()
{
	int i;
	CWarCastleJoin* join;
	CGuild* pGuild;
	join = m_attackGuildList;
	while(join)
	{
		pGuild = gserver->m_guildlist.findguild(join->GetIndex());
		if(pGuild)
		{
			int i;
			int guildMaxMember = pGuild->maxmember();
			for(i=0; i<guildMaxMember; i++)
			{
				if(pGuild->member(i) && pGuild->member(i)->GetPC())
				{
					CNetMsg::SP rmsg(new CNetMsg);
					GuildNameColorStateMsg(rmsg, pGuild->member(i)->GetPC() );
					SEND_Q(rmsg , pGuild->member(i)->GetPC()->m_desc);
				}
			}
		}
		join = join->GetNext();
	}

	join = m_defenseGuildList;
	while(join)
	{
		pGuild = gserver->m_guildlist.findguild(join->GetIndex());
		if(pGuild)
		{
			int guildMaxMember = pGuild->maxmember();
			for(i=0; i<guildMaxMember; i++)
			{
				if(pGuild->member(i) && pGuild->member(i)->GetPC())
				{
					CNetMsg::SP rmsg(new CNetMsg);
					GuildNameColorStateMsg(rmsg, pGuild->member(i)->GetPC() );
					SEND_Q(rmsg , pGuild->member(i)->GetPC()->m_desc);
				}
			}
		}
		join = join->GetNext();
	}

	pGuild = gserver->m_guildlist.findguild(m_ownerGuildIndex);
	if(pGuild)
	{
		int guildMaxMember = pGuild->maxmember();
		for(i=0; i<guildMaxMember; i++)
		{
			if(pGuild->member(i) && pGuild->member(i)->GetPC())
			{
				CNetMsg::SP rmsg(new CNetMsg);
				GuildNameColorStateMsg(rmsg, pGuild->member(i)->GetPC() );
				SEND_Q(rmsg , pGuild->member(i)->GetPC()->m_desc);
			}
		}
	}
}

void CDratanCastle::CheckRegenRebirthNPC()
{
	CHECK_SUBSERVER(this);

	CArea* area = GetArea();
	if (!area)
		return ;

	if(GetState() != WCSF_WAR_CASTLE)
		return ;

	int i;
	for(i=0; i < 7; i++)
	{
		if( (m_pRebrithNPC[i] == NULL) &&
				(m_nRebrithGuild[i] == -1) && m_nRegenTimeRebirthNPC[i] != 0 &&
#ifdef BUGFIX_WARCASTLE_REGEN
				(gserver->getNowSecond() > m_nRegenTimeRebirthNPC[i] )
#else
				(gserver->m_pulse > m_nRegenTimeRebirthNPC[i] )
#endif //BUGFIX_WARCASTLE_REGEN
		  )
		{
			for (size_t i = 0; i < area->m_npcRegenList.m_infoList.size(); i++)
			{
				CNPCRegenInfo& p = area->m_npcRegenList.m_infoList.at(i);
				if (p.m_totalNum != 0 || p.m_npcIdx != i+390)
					continue ;

				CNPCProto* proto = gserver->m_npcProtoList.FindProto(p.m_npcIdx);
				CNPC * npc = gserver->m_npcProtoList.Create(proto->m_index, &p);
				if (!npc)
					return ;

				GET_X(npc) = p.m_regenX;
				GET_Z(npc) = p.m_regenZ;
				GET_R(npc) = p.m_regenR;
				GET_YLAYER(npc) = p.m_regenY;

				npc->m_regenX = GET_X(npc);
				npc->m_regenZ = GET_Z(npc);
				npc->m_regenY = GET_YLAYER(npc);

				npc->m_recoverPulse = gserver->m_pulse;

				p.m_bAlive = true;
				p.m_lastDieTime = 0;
				npc->m_disableTime = 0;

				npc->InitPointsToMax();
				area->AddNPC(npc);
				npc->m_postregendelay = 0;

				int cx, cz;
				area->PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
				area->CharToCell(npc, GET_YLAYER(npc), cx, cz);

				{
					CNetMsg::SP rmsg(new CNetMsg);
					AppearMsg(rmsg, npc, true);
					area->SendToCell(rmsg, npc);
				}

				m_pRebrithNPC[i] = npc;

				m_nRegenTimeRebirthNPC[i] = 0;
				break;
			}
		}
	}
}

