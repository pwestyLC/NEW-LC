#include "stdhdrs.h"

#include "CmdMsg.h"
#include "Server.h"
#include "Exp.h"
#include "Log.h"
#include "Battle.h"
#include "hardcoding.h"
#include "WarCastle.h"
#include "doFunc.h"
#include "HolyWaterData.h"
#include "Artifact_Manager.h"
#include "../ShareLib/packetType/ptype_old_do_item.h"
#include <map>
#include <ctime>
#include "Descriptor.h"
///////////////////
// ���� ���� �Լ���

int ProcAttack(CCharacter* of, CCharacter* df, MSG_DAMAGE_TYPE damageType, CSkill* skill, int magicindex, int damage)
{
	// ����ڰ� ���� ���� �� �ִ� �������� �˻�
	if (!IsAvailableAttack(of, df))
		return 0;
	// ���� ���� ����
	if (damageType == MSG_DAMAGE_UNKNOWN)
		return 0;


	const CSkillProto* proto = NULL;
	const CSkillLevelProto* levelproto = NULL;
	const CMagicProto* magic = NULL;
	const CMagicLevelProto* magiclevel = NULL;

	if (skill)
	{
		proto = skill->m_proto;
		if (!GetSkillPrototypes(proto, skill->m_level, magicindex, &levelproto, &magic, &magiclevel))
			return 0;
	}

	// ����� ���ݿ� ���� ���� ���
	df->m_assist.CancelSleep();
	df->m_assist.CancelFear();
	df->CancelInvisible();
	df->m_assist.CancelMantle();
	of->m_assist.CancelMantle();

	if( IS_APET(df) )
	{
		CAPet* apet = TO_APET(df);
		if ( apet && apet->GetOwner() && apet->IsMount() )
		{
			df = (CCharacter*) apet->GetOwner() ;
			if(DEAD(df))
				return 0;
		}
	}



	// ������ ���ݿ� ���� ���� ���
	of->CancelInvisible();
	if ( IS_APET(of) )
	{
		if(TO_APET(of)->GetOwner())
			TO_APET(of)->GetOwner()->CancelInvisible();
	}

	char flag;
	bool isCharge = false;
	switch (damageType)
	{
	case MSG_DAMAGE_REFLEX:
	case MSG_DAMAGE_LINK:
		flag = HITTYPE_NORMAL;
		if (damage == 0)
			return 0;
		break;

	default:
		// ����/ȸ��/ũ��Ƽ�� ���� �÷���
		flag = GetHitType(of, df, damageType);
		// ����/ȸ��/ũ��Ƽ�� �˻�
		if (flag != HITTYPE_MISS)
			flag = SelectHitType(of, df, damageType, flag, magic, magiclevel, true);
		// ������ ���		
		damage = GetDamage(of, df, damageType, flag, magic, magiclevel, isCharge);
		break;
	}

	// �ڻ� ������ NPC�� �����ϰ��� �������� 10%�� ����
	if( proto && proto->m_index == 1110 && !IS_NPC(df) )
		damage = (int)(damage * 0.1f);
	

		

	ApplyHateByDamage(of, df, flag, damage);
	ApplyDamage(of, df, damageType, proto, magic, damage, flag, isCharge);

	//���� �ɼ� üũ�Ͽ� ��ų �ߵ� ó��
	//�ɼ� ��ų �ߵ�
	if(IS_PC(of))
	{
		CPC* pc = TO_PC(of);
		if(pc->m_optionAttSkillList.count() > 0)
		{
			int optionCount  = pc->m_optionAttSkillList.count();
			void* pos = pc->m_optionAttSkillList.GetHeadPosition();
			bool bApply;
			for(int i=0; i<optionCount; i++)
			{
				int rand = GetRandom(1, 10000);
				CSkill *pAttskill = pc->m_optionAttSkillList.GetNext(pos);
				if(rand < pAttskill->m_optionSkillProb)
				{
					ApplySkill(of, df, pAttskill,-1, bApply);
				}
			}
		}

#ifdef DURABILITY
		// ���� ��� ������ ���� (������ �̹Ƿ�)
		pc->calcDurability_for_weapon();
#endif
	}
	if(IS_PC(df))
	{
		CPC* pc = TO_PC(df);
		if(pc->m_optionDefSkillList.count() > 0)
		{
			bool bRet;
			int optionCount  = pc->m_optionDefSkillList.count();
			void* pos = pc->m_optionDefSkillList.GetHeadPosition();
			bool bApply;
			bool bHits[] = {true, true, true};
			for(int i=0; i<optionCount; i++)
			{
				CSkill *pDefskill = pc->m_optionDefSkillList.GetNext(pos);
				int rand = GetRandom(1, 10000);
				if(rand < pDefskill->m_optionSkillProb)
				{
					if (df->m_assist.Add(df, -1, pDefskill->m_proto, pDefskill->m_level, bHits, true, -1,
										 -1,
										 0, 0, 0))
						bRet = true;
					ApplySkill(df, df, pDefskill,-1, bApply);
				}
			}
		}

#ifdef DURABILITY
		// ��(�׼�����) ��� ������ ���� (����� �̹Ƿ�)
		pc->calcDurability_for_armor();
#endif
	}

	if (flag != HITTYPE_MISS)
		ProcAfterHit(of, df);

	if (DEAD(df))
	{
		switch (df->m_type)
		{
		case MSG_CHAR_PC:
			ProcDead(TO_PC(df), of);
			break;
		case MSG_CHAR_NPC:
			ProcDead(TO_NPC(df), of);
			break;
		case MSG_CHAR_PET:
			ProcDead(TO_PET(df), of);
			break;
		case MSG_CHAR_ELEMENTAL:
			ProcDead(TO_ELEMENTAL(df), of);
			break;
		case MSG_CHAR_APET:
			ProcDead(TO_APET(df), of );
			break;
		default:
			break;
		}

		// ���� ���� df�� �޸𸮿��� ���� �� �� �ִ�
		// �׷��� �ƿ� NULL�� �ٲ������
		df = NULL;

		return 1;
	}
	else
	{
		// ��� ������ ������ �ݻ縦 �˻�
		if (damageType != MSG_DAMAGE_REFLEX && GetDistance(of, df) <= 25)
		{
			int reflexdam = 0;
			if (GetRandom(1, 10000) <= df->m_avPassiveAddition.hcReflexProb)
			{
				reflexdam += df->m_avPassiveAddition.hcReflex;
				reflexdam += damage * df->m_avPassiveRate.hcReflex / SKILL_RATE_UNIT;
			}
			if (GetRandom(1, 10000) <= df->m_assist.m_avAddition.hcReflexProb)
			{
				reflexdam += df->m_assist.m_avAddition.hcReflex;
				reflexdam += damage * df->m_assist.m_avRate.hcReflex / SKILL_RATE_UNIT;
			}
			if (reflexdam)
			{
				if (ProcAttack(df, of, MSG_DAMAGE_REFLEX, NULL, 0, reflexdam) == 1)
					return -1;
			}
		}

		if ( IS_PC(of) && IS_NPC(df) )
		{
			// ���̹� ���ʹ� ������ ������ Ÿ�ٸ� ������ ��
			// ���⼭ pc�� ������ npc ����
			CPC* temp = TO_PC(of);
			if(temp)
				temp->SetOwners_target(df);
		}

		if( IS_PC(of) )
		{
			CPC* pPcOf = TO_PC(of);
			if(pPcOf)
				pPcOf->SetSummonOwners_target(df);

			if( IS_NPC(df) )
			{
				CNPC * pNpc = TO_NPC(df);
				if( pNpc->GetOwner() && pNpc->GetOwner()->GetSummonNpc(SUMMON_NPC_TYPE_MERCENARY) == pNpc)
					pNpc->GetOwner()->SetSummonOwners_target(of);
			}

			if( pPcOf->IsSetPlayerState(PLAYER_STATE_PKMODE)  )
			{
				if(  IS_PC( df) )
				{
					CPC* pPcDf = TO_PC(df);
					if(pPcDf && pPcDf->GetSummonNpc(SUMMON_NPC_TYPE_MERCENARY) )
						pPcDf->SetSummonOwners_target(of);
				}
				// PVP ���¿��� �뺴�� ������ ���� �뺴�� ���ʿ��� ���� ������ ���� ��Ų��.
				else if( IS_NPC(df) && TO_NPC(df)->GetOwner() && TO_NPC(df) == TO_NPC(df)->GetOwner()->GetSummonNpc(SUMMON_NPC_TYPE_MERCENARY) )
				{
					CPC* pPcDf = TO_NPC(df)->GetOwner();
					AddRaList(pPcOf, pPcDf ); //
				}
			}
		}

	}

	return 0;
}

bool CheckBothPvPArea(CCharacter* ch, CCharacter* tch)
{
	if (ch == NULL)
		return false;
	if (tch == NULL)
		return false;

	// ������
	int chType = ch->m_type;
	int tchType = tch->m_type;
	chType = chType;
	tchType = tchType;
	if (ch->m_pZone == NULL)
		return false;
	if (tch->m_pZone == NULL)
		return false;
	if (ch->m_pArea == NULL)
		return false;
	if (ch->m_pZone == NULL)
		return false;
	if (ch->m_pZone->m_index != tch->m_pZone->m_index)
		return false;
	if (ch->m_pArea->m_index != tch->m_pArea->m_index)
		return false;

	if (ch->m_pos.m_yLayer != tch->m_pos.m_yLayer)
		return false;

	if (TO_PC(ch)->GetPlayerState() != TO_PC(tch)->GetPlayerState())
		return false;

	return true;
}
// ch, tch�� CELL_EXT ���� �ȿ� �ִ°� ������ true
bool CheckInNearCellExt(CCharacter* ch, CCharacter* tch)
{
	if (ch == NULL)
		return false;
	if (tch == NULL)
		return false;

	// ������
	int chType = ch->m_type;
	int tchType = tch->m_type;
	chType = chType;
	tchType = tchType;
	if (ch->m_pZone == NULL)
		return false;
	if (tch->m_pZone == NULL)
		return false;
	if (ch->m_pArea == NULL)
		return false;
	if (ch->m_pZone == NULL)
		return false;
	if (ch->m_pZone->m_index != tch->m_pZone->m_index)
		return false;
	if (ch->m_pArea->m_index != tch->m_pArea->m_index)
		return false;

	if (ch->m_pos.m_yLayer != tch->m_pos.m_yLayer)
		return false;

	if (ABS(ch->m_cellX - tch->m_cellX) <= CELL_EXT && ABS(ch->m_cellZ - tch->m_cellZ) <= CELL_EXT)
		return true;

	return false;
}

// �켱�� PC ã��
// target list���� ��� ���� ���ϱ�
// ã���� ����� ������
typedef struct __tagPreferencePCData
{
	CPC*		m_pc;		// PC ������
	int			m_damage;	// �ش� PC�� ������
} PPDATA;

CPC* FindPreferencePC(CNPC* npc, int* level, LONGLONG* pnTotalDamage)
{
	if (npc == NULL)
		return NULL;

	CPC* ret = NULL;
	CAttackChar* target = npc->m_attackList;

	int dam = 0;
	*pnTotalDamage = npc->GetTotalDamage();
	LONGLONG nPreferDamage = *pnTotalDamage + npc->m_maxHP * 2 / 10;		// �ִ� ������� NPC�� �ִ�HP 20%�� ���� ���� ������ �켱�ǿ� ���
	int totLevel = 0;
	int	count = 0;

	std::map<CPC*, PPDATA> listAttackPC;	// NPC ���ݿ� ������ PC ����Ʈ
	while (target)
	{
		if (target->ch)
		{
			// ������
			int npcType = npc->m_type;
			int tchType = target->ch->m_type;
			npcType = npcType;
			tchType = tchType;
			if (npc== NULL)
				break;
			if (target->ch == NULL)
				break;
			if (npc->m_pZone == NULL)
				break;
			if (target->ch->m_pZone == NULL)
				break;
			if (target->ch->m_pArea == NULL)
				break;
			if (npc->m_pZone == NULL)
				break;
			// ���� zone�� ���ų� ���� area�� ���ų� CELL_EXT(+-5) ���� �ȿ� ���ų�
			if ((npc->m_pZone->m_index != target->ch->m_pZone->m_index) ||
					(npc->m_pArea->m_index != target->ch->m_pArea->m_index) ||
					!CheckInNearCellExt(npc, target->ch))
				break;

			dam = target->m_damage;

			// ���� pc�� NPC �ִ� HP��  20% ���ʽ�!!
			if (target->m_next == NULL)
				dam += npc->m_maxHP * 2 / 10;

			PPDATA ppdata = {NULL, 0};
			switch (target->ch->m_type)
			{
			case MSG_CHAR_PC:
				ppdata.m_pc = target->pc;
				break;

			case MSG_CHAR_PET:
				if (TO_PET(target->ch)->GetOwner())
					ppdata.m_pc = TO_PET(target->ch)->GetOwner();
				break;

			case MSG_CHAR_ELEMENTAL:
				if (TO_ELEMENTAL(target->ch)->GetOwner())
					ppdata.m_pc = TO_ELEMENTAL(target->ch)->GetOwner();
				break;

			case MSG_CHAR_APET:
				if ( TO_APET(target->ch)->GetOwner() )
					ppdata.m_pc = TO_APET(target->ch)->GetOwner();
				break;

			case MSG_CHAR_NPC:
				if ( TO_NPC(target->ch)->GetOwner() )
					ppdata.m_pc = TO_NPC(target->ch)->GetOwner();
				break;
			default:
				break;
			}

			if (ppdata.m_pc)
			{
				std::map<CPC*, PPDATA>::iterator it = listAttackPC.find(ppdata.m_pc);
				if (it == listAttackPC.end())
				{
					PPDATA ppdatanew;
					ppdatanew.m_pc = ppdata.m_pc;
					ppdatanew.m_damage = dam;
					listAttackPC.insert(std::map<CPC*, PPDATA>::value_type(ppdatanew.m_pc, ppdatanew));
					count++;
					totLevel += ppdata.m_pc->m_level;
				}
				else
				{
					PPDATA& ppdatacur = it->second;
					ppdatacur.m_damage += dam;
				}
			}

			if( target->ch->m_type == MSG_CHAR_NPC )
			{
				if( TO_NPC(target->ch)->GetOwner() && TO_NPC(target->ch)->GetOwner()->GetSummonNpc(TO_NPC(target->ch)) )
				{
					target = target->m_next;
					continue;
				}
			}
		}
		target = target->m_next;
	}

	std::map<CPC*, PPDATA>::iterator it = listAttackPC.begin();
	std::map<CPC*, PPDATA>::iterator endit = listAttackPC.end();
	for(; it != endit; ++it)
	{
		PPDATA& ppdata = it->second;

		// 50% �̻� ������ �� PC ��ȯ
		if (ppdata.m_damage > nPreferDamage / 2)
			ret = ppdata.m_pc;
	}

	listAttackPC.clear();

	if (count == 0)
		*level = -1;
	else
	{
		*level = totLevel / count;
		if (*level < 0)
			*level = GetMaxLevel();
	}

	return ret;
}

// �յ� ��Ƽ �� �� ����Ա�
void DivisionPartyMoney(CPC* pc, CNPC* npc, LONGLONG count)
{
	// validation
	if (pc == NULL || count <= 0)
		return;

	int i;
	CParty* party = pc->m_party;
	int divCount = 0;				// �� ������� ��Ƽ ��� ��

	for (i=0; i < MAX_PARTY_MEMBER; i++)
	{
		CPC* pMemberPC = party->GetNearMember(pc, i);
		if (!pMemberPC)
			continue;

		divCount++;
	}

	if (divCount < 1)
		return;

	// �� ���󳻱�
	//bool bTake = false;		// ���� ���� ����� �ֳ�?: ������ �������� �ٴڿ� �״��
	count = count / divCount;

	if (count < 1)
		return;

	GoldType_t Artimoney = 0;

	// ��Ƽ������ �й�
	for (i = MAX_PARTY_MEMBER - 1; i >= 0; i--)
	{
		Artimoney = 0;

		CPC* pMemberPC = TO_PC(party->GetNearMember(pc, i));
		if (!pMemberPC)
			continue;

		// ���� �� �����
		int bonus = 0;
		if(pMemberPC->m_avPassiveAddition.money_nas > 0)
		{
			bonus += pMemberPC->m_avPassiveAddition.money_nas;	
		}
		if(pMemberPC->m_avPassiveRate.money_nas > 0)
		{
			bonus = count * (pMemberPC->m_avPassiveRate.money_nas - 100) / SKILL_RATE_UNIT;
		}

		Artimoney = count * pMemberPC->m_artiGold / 100;
		Artimoney = count + Artimoney;

		if (npc != NULL && npc->m_proto->IsBossInList()) {
			if (Artimoney > gserver->m_serverConfig.max_gold_boss)
				Artimoney = gserver->m_serverConfig.max_gold_boss;
		} 
		else if (Artimoney > gserver->m_serverConfig.max_gold && !pMemberPC->m_assist.FindBySkillIndex(2040))
		{
			Artimoney = gserver->m_serverConfig.max_gold;
		}

		else if (Artimoney > gserver->m_serverConfig.max_gold && pMemberPC->m_assist.FindBySkillIndex(2040))
		{
			if (Artimoney > MAX_GOLD_POTION)
				Artimoney = MAX_GOLD_POTION;
			else
				Artimoney = Artimoney;	
		}

		pMemberPC->m_inventory.increaseMoney(Artimoney, bonus);
	}
}

// �յ���Ƽ�϶� ������ �������� ��������
bool GetItemRandomParty(CPC* pc, CItem* item)
{
	// validation
	if (!pc && !item && !pc->m_party)
		return false;

	int i;
	CParty* party = pc->m_party;
	bool bPreference = false;		// �� ��Ƽ�� �ڰ��� �ִ°�
	int partyCount = 0;				// ���� �� �ִ� �ڰ��� �ִ� ��Ƽ�� ��

	for (i=0; i < MAX_PARTY_MEMBER; i++)
	{
		CPC* pMemberPC = party->GetNearMember(pc, i);
		if (!pMemberPC)
			continue;

		if (item->m_preferenceIndex == pMemberPC->m_index)
			bPreference = true;

		partyCount++;
	}

	// �켱���� �ִµ� ��Ƽ�� �ڰݾ����� return;
	if (item->m_preferenceIndex != -1 && !bPreference)
	{
		return false;
	}

	// ���� ����� ����.
	if (partyCount < 1)
		return false;

	bool bGiveItem = false;		// ������ ���� ����!
	int idx;					// ������ ��Ƽ�� �ε���

	int bitfield = 0;			// ���������� ������ ��Ƽ�� �ε��� ����
	bool bAll = false;

	int deleteVIndex = item->getVIndex();

	std::vector<CPC*> _user;

	for(int i = 0 ; i < party->GetMemberCount(); i++)
	{
		CPC* party_member = party->GetNearMember(pc, i);
		
		if(party_member == NULL)
			continue;

		else if(party_member->m_inventory.getEmptyCount() == 0)
			continue;

		else if(gserver->isActiveEvent(A_EVENT_EGGS_HUNT) &&
			item->getDBIndex() == 2148 &&
			party_member->m_inventory.FindByDBIndex(item->getDBIndex()) != NULL)
			continue;

		else if(item->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && item->m_itemProto->getItemSubTypeIdx() == IACCESSORY_ARTIFACT)
		{
			if(party_member->m_level <= PKMODE_LIMIT_LEVEL)
				continue;
			if(party_member->m_assist.FindBySkillIndex(PVP_PROTECT_SKILL_INDEX) != 0)
				continue;

			_user.push_back(party_member);
		}

		else
		{
			_user.push_back(party_member);
		}
	}

	if(_user.size() == 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_NOT_CONDITION_ITEM_ALL_USER);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	idx = GetRandom(0, _user.size() - 1);
	_user[idx]->m_inventory.addItem(item);

	if(item->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && item->m_itemProto->getItemSubTypeIdx() == IACCESSORY_ARTIFACT)
	{
		ArtifactManager::instance()->addOwner(_user[idx], item, true);
	}

#ifdef GER_LOG
	GAMELOGGEM << init( 0, "CHAR_LOOT")
		<< LOG_VAL("account-id", pc->m_desc->m_idname ) << blank
		<< LOG_VAL("character-id", pc->m_desc->m_pChar->m_name ) << blank
		<< LOG_VAL("item-id", item->getDBIndex() ) << blank
		<< LOG_VAL("amount",item->Count() ) << blank
		//<< LOG_VAL("amount", money ) << blank
		<<endGer;
#endif // GER_LOG

	// LOG
	itemPickGameLog(_user[idx], item);

	// ���� ������ ó��
	CNetMsg::SP disappmsg(new CNetMsg);
	CNetMsg::SP takemsg(new CNetMsg);
	CNetMsg::SP getmsg(new CNetMsg);

	int cx, cz;

	cx = item->m_cellX;
	cz = item->m_cellZ;

	ItemTakeMsg(takemsg, pc, item);
	ItemDisappearMsg(disappmsg, deleteVIndex);
	ItemGetMsg(getmsg, _user[idx], item);

	// �켱�� ����
	item->m_preferenceIndex = -1;

	// ������ ����
	pc->m_pArea->ItemFromCell(item);

	// �޽��� ������
	pc->m_pArea->SendToCell(takemsg, pc, true);
	pc->m_pArea->SendToCell(disappmsg, GET_YLAYER(pc), cx, cz);
	pc->m_party->SendToPCInSameZone(pc->m_pZone->m_index, pc->m_pArea->m_index, getmsg);

	return true;
}

//��Ƽ, ������ Box ������ ȹ��
bool GetItemRaidOpenBox(CPC* pc, CItem* item)
{
	// validation
	if (!pc || !item || !(pc->m_pArea))
		return false;

	time_t t_now;
	bool bGiveItem = false;		// ������ ���� ����!
	int BoxitemIndex = 4709;	// ���ھ����� �ε���

	int deleteVIndex = item->getVIndex();

	if(item->getDBIndex() != BoxitemIndex)
		return false;

	// ȹ�� �ð� üũ
	t_now = time(NULL);
	int nBoxItemTime = 0;

	nBoxItemTime = pc->GetRaidBoxItemTime();
	if(nBoxItemTime == 0)
	{
		// �ڽ������� ȹ�� �ð� ����
		pc->SetRaidBoxItemTime(t_now);
	}
	else if(nBoxItemTime > 0 && pc->m_isNotCoolBoxItem == false)
	{
		// 5�� üũ
		if( (t_now - pc->GetRaidBoxItemTime()) <= (5 * 60))
		{
			// �� �̻� ���� �ֿ� �� ����(ȹ�� �ð� 5��)
			CNetMsg::SP rmsg(new CNetMsg);
			RaidErrorMsg(rmsg, MSG_RAID_ERROR_INZONE_NOT_5MIN_GETBOX);
			SEND_Q(rmsg, pc->m_desc);
			return false;
		}
	}

	//Box �������� �̹� �ִ��� üũ (�ڽ� ������ �ε��� ���� �ʿ�)
	if(item->getDBIndex() == BoxitemIndex && pc->m_isNotCoolBoxItem == false)
	{
		if (pc->m_inventory.FindByDBIndex(item->getDBIndex()))
		{
			// ���̵� �ڽ� ������ �̹� �����ϰ� ����
			CNetMsg::SP rmsg(new CNetMsg);
			RaidErrorMsg(rmsg, MSG_RAID_ERROR_INZONE_ALREADY_GETBOX);
			SEND_Q(rmsg, pc->m_desc);
			return false;
		}
	}

	// �κ��� �ֱ�
	if (pc->m_inventory.addItem(item))
	{
		bGiveItem = true;

		// �ڽ������� ȹ�� �ð� ����
		pc->SetRaidBoxItemTime(t_now);

#ifdef GER_LOG
		GAMELOGGEM << init( 0 , "CHAR_LOOT")
				   << LOG_VAL("account-id", pc->m_desc->m_idname ) << blank
				   << LOG_VAL("character-id", pc->m_desc->m_pChar->m_name ) << blank
				   << LOG_VAL("item-id", item->getDBIndex() ) << blank
				   << LOG_VAL("amount",item->Count() ) << blank
				   <<endGer;
#endif // GER_LOG

		// LOG
		itemPickGameLog(pc, item);
	}
	else
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysFullInventoryMsg(rmsg, 0);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}
	// ���� ������ ó��
	CNetMsg::SP disappmsg(new CNetMsg);
	CNetMsg::SP takemsg(new CNetMsg);
	CNetMsg::SP getmsg(new CNetMsg);

	int cx, cz;

	cx = item->m_cellX;
	cz = item->m_cellZ;

	ItemTakeMsg(takemsg, pc, item);
	ItemDisappearMsg(disappmsg, deleteVIndex);
	ItemGetMsg(getmsg, pc, item);

	// �켱�� ����
	item->m_preferenceIndex = -1;

	// ������ ����
	pc->m_pArea->ItemFromCell(item);

	// �޾Ҵٰ� ����
	pc->m_bGiveItem = true;

	// �޽��� ������
	pc->m_pArea->SendToCell(takemsg, pc, true);
	pc->m_pArea->SendToCell(disappmsg, GET_YLAYER(pc), cx, cz);

	if(pc->IsParty())
	{
		pc->m_party->SendToPCInSameZone(pc->m_pZone->m_index, pc->m_pArea->m_index, getmsg);
	}
	else if(pc->IsExped())
	{
		pc->m_Exped->SendToPCInSameZone(pc->m_pZone->m_index, pc->m_pArea->m_index, getmsg);
	}

	return true;
}

// �յ� ��Ƽ �� �� ����Ա�(������)
void DivisionExpedMoney(CPC* pc, CNPC* npc, LONGLONG count)
{
	// validation
	if (!pc || count <= 0)
		return;

	int i,j;
	CExpedition* Exped = pc->m_Exped;
	int divCount = 0;				// �� ������� ��Ƽ ��� ��

	for (i=0; i < MAX_EXPED_GROUP; i++)
	{
		for (j=0; j < MAX_EXPED_GMEMBER; j++)
		{
			CPC* pMemberPC = Exped->GetNearMember(pc, i,j);
			if (!pMemberPC)
				continue;

			divCount++;
		}
	}

	if (divCount < 1)
		return;

	// �� ���󳻱�
	//bool bTake = false;		// ���� ���� ����� �ֳ�?: ������ �������� �ٴڿ� �״��
	count = count / divCount;

	if (count < 1)
		return;

	GoldType_t Artimoney = 0;

	// ��Ƽ������ �й�
	for (i = MAX_EXPED_GROUP - 1; i >= 0; i--)
	{
		for (j = MAX_EXPED_GMEMBER - 1; j >= 0; j--)
		{
			Artimoney = 0;

			CPC* pMemberPC = Exped->GetNearMember(pc, i,j);
			if (!pMemberPC)
				continue;

			// ���� �� �����
			int bonus = 0;

			if(pMemberPC->m_avPassiveAddition.money_nas > 0)
			{
				bonus += pMemberPC->m_avPassiveAddition.money_nas;	
			}
			if(pMemberPC->m_avPassiveRate.money_nas > 0)
			{
				bonus = count * (pMemberPC->m_avPassiveRate.money_nas - 100) / SKILL_RATE_UNIT;
			}

			Artimoney = count * pMemberPC->m_artiGold / 100;
			Artimoney = count + Artimoney;
            
			if (npc != NULL && npc->m_proto->IsBossInList()) 
			{
				if (Artimoney > gserver->m_serverConfig.max_gold_boss)
					Artimoney = gserver->m_serverConfig.max_gold_boss;
			}
			else if (Artimoney > gserver->m_serverConfig.max_gold && !pMemberPC->m_assist.FindBySkillIndex(2040))
			{
				Artimoney = gserver->m_serverConfig.max_gold;
			}
			else if (Artimoney > gserver->m_serverConfig.max_gold && pMemberPC->m_assist.FindBySkillIndex(2040))
			{
				if (Artimoney > MAX_GOLD_POTION)
					Artimoney = MAX_GOLD_POTION;
				else
					Artimoney = Artimoney;
			}
			
			pMemberPC->m_inventory.increaseMoney(Artimoney, bonus);
		}
	}
}

// �յ������ ������ �������� ��������(������)
bool GetItemRandomExped(CPC* pc, CItem* item)
{
	// validation
	if (!pc || !item || !(pc->m_Exped) || !(pc->m_pArea))
		return false;

	int i,j;
	CExpedition* Exped = pc->m_Exped;
	bool bPreference = false;		// �� �����밡 �ڰ��� �ִ°�
	int ExpedCount = 0;				// ���� �� �ִ� �ڰ��� �ִ� ������� ��

	for (i=0; i < MAX_EXPED_GROUP; i++)
	{
		for (j=0; j < MAX_EXPED_GMEMBER; j++)
		{
			CPC* pMemberPC = Exped->GetNearMember(pc, i,j);
			if (!pMemberPC)
				continue;

			if (item->m_preferenceIndex == pMemberPC->m_index)
				bPreference = true;

			ExpedCount++;
		}
	}

	// �켱���� �ִµ� �����밡 �ڰݾ����� return;
	if (item->m_preferenceIndex != -1 && !bPreference)
	{
		// �켱���� �����ϴ� �޽��� ����
		CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_NOT_OWNER_ITEM);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	// ���� ����� ����.
	if (ExpedCount < 1)
		return false;

	bool bGiveItem = false;		// ������ ���� ����!
	int idx,idx2;				// ������ ��Ƽ�� �ε���

	int bitfield = 0;			// ���������� ������ ������� �ε��� ����
	bool bAll = false;

	int deleteVIndex = item->getVIndex();

	//TODO
	/*
	1. �κ��丮�� �� ������ ���� ã�� �����͸� ������ ����
	2. �������� �������� �־��ش�.
	*/

	std::vector<CPC*> _user;

	for(int i = 0; i < MAX_EXPED_GROUP; i++)
	{
		for(int j = 0; j < pc->m_Exped->GetGroupMemberCount(i); j++)
		{
			CPC* exped_member = Exped->GetNearMember(pc, i, j);

			if(exped_member == NULL)
				continue;
			
			else if(exped_member->m_inventory.getEmptyCount() == 0)
				continue;

			else if(gserver->isActiveEvent(A_EVENT_EGGS_HUNT) &&
				item->getDBIndex() == 2148 &&
				exped_member->m_inventory.FindByDBIndex(item->getDBIndex()) != NULL)
				continue;

			else if(item->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && item->m_itemProto->getItemSubTypeIdx() == IACCESSORY_ARTIFACT)
			{
				if(exped_member->m_level <= PKMODE_LIMIT_LEVEL)
					continue;
				if(exped_member->m_assist.FindBySkillIndex(PVP_PROTECT_SKILL_INDEX) != 0)
					continue;

				_user.push_back(exped_member);
			}
			
			else
				_user.push_back(exped_member);
		}
	}

	if(_user.size() == 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_NOT_CONDITION_ITEM_ALL_USER);
		SEND_Q(rmsg, pc->m_desc);
		return false;
	}

	idx = GetRandom(0, _user.size() - 1);
	_user[idx]->m_inventory.addItem(item);

	if(item->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && item->m_itemProto->getItemSubTypeIdx() == IACCESSORY_ARTIFACT)
	{
		ArtifactManager::instance()->addOwner(_user[idx], item, true);
	}

#ifdef GER_LOG
	GAMELOGGEM << init( 0, "CHAR_LOOT")
		<< LOG_VAL("account-id", pc->m_desc->m_idname ) << blank
		<< LOG_VAL("character-id", pc->m_desc->m_pChar->m_name ) << blank
		<< LOG_VAL("item-id", item->getDBIndex() ) << blank
		<< LOG_VAL("amount",item->Count() ) << blank
		//<< LOG_VAL("amount", money ) << blank
		<<endGer;
#endif // GER_LOG
	itemPickGameLog(_user[idx], item);
		
	// ���� ������ ó��
	CNetMsg::SP disappmsg(new CNetMsg);
	CNetMsg::SP takemsg(new CNetMsg);
	CNetMsg::SP getmsg(new CNetMsg);

	int cx, cz;

	cx = item->m_cellX;
	cz = item->m_cellZ;

	ItemTakeMsg(takemsg, pc, item);
	ItemDisappearMsg(disappmsg, deleteVIndex);
	ItemGetMsg(getmsg, _user[idx], item);

	// �켱�� ����
	item->m_preferenceIndex = -1;

	// ������ ����
	pc->m_pArea->ItemFromCell(item);

	// �޽��� ������
	pc->m_pArea->SendToCell(takemsg, pc, true);
	pc->m_pArea->SendToCell(disappmsg, GET_YLAYER(pc), cx, cz);
	pc->m_Exped->SendToPCInSameZone(pc->m_pZone->m_index, pc->m_pArea->m_index, getmsg);

	return true;
}

bool GetItemGiveToBoss(CPC* pc, CItem* item)
{
	if(!pc || !item || !(pc->m_Exped) || !(pc->m_pArea))
		return false;

	int boss_idx = pc->m_Exped->GetBossIndex();
	CPC *pBoss = PCManager::instance()->getPlayerByCharIndex(boss_idx);
	if( !pBoss )
		return false;

	int deleteVIndex = item->getVIndex();

	if (pBoss->m_inventory.addItem(item))
	{
		GAMELOG << init("ITEM_PICK_TRIGGERITEM", pBoss)
				<< itemlog(item)
				<< end;
	}
	else
	{
		return false;
	}

	// ���� ������ ó��
	CNetMsg::SP disappmsg(new CNetMsg);
	CNetMsg::SP takemsg(new CNetMsg);
	CNetMsg::SP getmsg(new CNetMsg);

	int cx, cz;

	cx = item->m_cellX;
	cz = item->m_cellZ;

	ItemTakeMsg(takemsg, pc, item);
	ItemDisappearMsg(disappmsg, deleteVIndex);
	ItemGetMsg(getmsg, pBoss, item);

	item->m_preferenceIndex = -1;
	pc->m_pArea->ItemFromCell(item);

	pc->m_pArea->SendToCell(takemsg, pc, true);
	pc->m_pArea->SendToCell(disappmsg, GET_YLAYER(pc), cx, cz);
	pc->m_Exped->SendToPCInSameZone(pc->m_pZone->m_index, pc->m_pArea->m_index, getmsg);

	return true;
}

// tch �� ���ø���Ʈ�� ch ���� �߰�
// ch�� tch�� ���� ;;;;
CAttackChar* AddAttackList(CCharacter* ch, CCharacter* tch, int hate)
{
	if (ch == tch || ch == NULL || tch == NULL)
		return NULL;

	bool bCh = true;
	bool bTCh = true;

	CAttackChar* chAttackList = ch->m_attackList;
	CAttackChar* tchAttackList = tch->m_attackList;
	CAttackChar* ret = NULL;

	// �̹� ���ø����� ������ �ٽ� ���ø���ũ�� �� ���
	// TargetHate �� 0�� ���� �ִٸ� �������ٰ� �ٽ� �� ���
	// TargetHate�� �ʱⰪ���� ����
	while (chAttackList)
	{
		if (chAttackList->ch == tch)
		{
			bCh = false;
			chAttackList->m_targetHate += hate;
			break;
		}
		chAttackList = chAttackList->m_next;
	}

	while (tchAttackList)
	{
		if (tchAttackList->ch == ch)
		{
			bTCh = false;
			tchAttackList->m_targetHate += hate;
			ret = tchAttackList;
			if(IS_NPC(tch))
				tchAttackList->m_targetPulse = gserver->m_pulse;
			break;
		}
		tchAttackList = tchAttackList->m_next;
	}

	CAttackChar* attackCh = NULL;
	CAttackChar* attackTCh = NULL;

	if (bCh)
	{
		attackCh = new CAttackChar;
		attackCh->ch = tch;
		ADD_TO_BILIST(attackCh, ch->m_attackList, m_prev, m_next);
	}

	if (bTCh)
	{
		attackTCh = new CAttackChar;
		attackTCh->ch = ch;
		attackTCh->m_bFirstAttack = true;
		ADD_TO_BILIST(attackTCh, tch->m_attackList, m_prev, m_next);
		ret = attackTCh;
	}

	if (bCh && bTCh)
	{
		if (IS_NPC(tch))
			attackTCh->m_targetPulse = gserver->m_pulse;
		attackTCh->m_targetHate += hate;
	}

	return ret;
}

// ch ���ø���Ʈ���� ����
void DelAttackList(CCharacter* ch)
{
	if (ch == NULL
			|| ch->m_attackList == NULL)
	{
		return;
	}

	CAttackChar* attCh;
	CAttackChar* attChNext = ch->m_attackList;
	CAttackChar* attTCh;
	CAttackChar* attTChNext;

	while ((attCh = attChNext))
	{
		attChNext = attCh->m_next;

		attTChNext = attCh->ch->m_attackList;
		while ((attTCh = attTChNext))
		{
			attTChNext = attTCh->m_next;
			if (attTCh->ch == ch)
			{
				REMOVE_FROM_BILIST(attTCh, attCh->ch->m_attackList, m_prev, m_next);
				delete attTCh;
				attTCh = NULL;
				break;
			}
		}

		REMOVE_FROM_BILIST(attCh, ch->m_attackList, m_prev, m_next);
		delete attCh;
		attCh = NULL;
	}
}

// ch ���ø���Ʈ���� tch�� ����
void DelTargetFromAttackList(CCharacter* ch, CCharacter* tch)
{
	CAttackChar* attCh;
	CAttackChar* attChNext = ch->m_attackList;
	CAttackChar* attTCh;
	CAttackChar* attTChNext;

	while ((attCh = attChNext))
	{
		attChNext = attCh->m_next;

		if (attCh->ch == tch)
		{
			attTChNext = attCh->ch->m_attackList;
			while ((attTCh = attTChNext))
			{
				attTChNext = attTCh->m_next;
				if (attTCh->ch == ch)
				{
					REMOVE_FROM_BILIST(attTCh, attCh->ch->m_attackList, m_prev, m_next);
					delete attTCh;
					attTCh = NULL;
					break;
				}
			}

			REMOVE_FROM_BILIST(attCh, ch->m_attackList, m_prev, m_next);
			delete attCh;
			attCh = NULL;
			break;
		}
	}
}

// ������� ����Ʈ�� �߰�
void AddRaList(CPC* of, CPC* df)
{
	if (of == NULL || df == NULL) return;

	// ������ ���� ����Ʈ�� ������ �߰�
	CRaChar* raOf = new CRaChar;
	raOf->m_raTarget = of;
	raOf->m_raPulse = RAMODE_USE_PULSE;
	raOf->m_bAttacker = true;
	ADD_TO_BILIST(raOf, df->m_raList, m_prev, m_next);
	df->SetPlayerState(PLAYER_STATE_RAMODE);
	df->CalcStatus(true);//Cloud

	// ������ ���� ����Ʈ�� ������ �߰�
	CRaChar* raDf = new CRaChar;
	raDf->m_raTarget = df;
	raDf->m_bAttacker = false;
	ADD_TO_BILIST(raDf, of->m_raList, m_prev, m_next);

	CNetMsg::SP rmsg(new CNetMsg);
	RightAttackMsg(rmsg, of, MSG_RIGHT_ATTACK_ADD);
	SEND_Q(rmsg, of->m_desc);
	SEND_Q(rmsg, df->m_desc);
}

// ������� ����Ʈ���� ����
void DelRaList(CPC* pc, bool bForce)
{
	if (pc == NULL) return;

	CRaChar* raPC;
	CRaChar* raPCNext = pc->m_raList;

	CRaChar* raTPC;
	CRaChar* raTPCNext;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		RightAttackMsg(rmsg, pc, MSG_RIGHT_ATTACK_DEL);

		while ((raPC = raPCNext))
		{
			raPCNext = raPC->m_next;
			raTPCNext = raPC->m_raTarget->m_raList;

			while ((raTPC = raTPCNext))
			{
				raTPCNext = raTPC->m_next;

				if (raTPC->m_raTarget == pc)
				{
					if (!raTPC->m_bAttacker && !bForce)
						return;

					SEND_Q(rmsg, raTPC->m_raTarget->m_desc);
					REMOVE_FROM_BILIST(raTPC, raPC->m_raTarget->m_raList, m_prev, m_next);
					delete raTPC;
					raTPC = NULL;
					break;
				}
			}

			SEND_Q(rmsg, raPC->m_raTarget->m_desc);

			REMOVE_FROM_BILIST(raPC, pc->m_raList, m_prev, m_next);
			delete raPC;
			raPC = NULL;
		}
	}
}

// pc ������� ����Ʈ�� tpc�� �ִ°�
bool IsRaList(CPC* pc, CPC* tpc)
{
	if (pc == NULL || tpc == NULL) return false;

	CPC* findPC = PCManager::instance()->getPlayerByCharIndex(pc->m_index);
	if (findPC == NULL)
	{
		GAMELOG << init("PCMEM_CHECK_ERROR", pc) << "IsRaList" << end;
		return false;
	}

	CRaChar* raList = pc->m_raList;

	while (raList)
	{
		if (raList->m_raTarget == tpc)
			return true;

		raList = raList->m_next;
	}

	return false;
}

bool IsFirstAttackInAttackList(CPC* of, CPC* df)
{
	if (of == NULL || df == NULL) return false;

	CAttackChar* pAttackChar = df->m_attackList;
	while (pAttackChar)
	{
		if (pAttackChar->ch == of && pAttackChar->m_bFirstAttack)
			return true;
		pAttackChar = pAttackChar->m_next;
	}
	return false;
}

// ���� ���ϴ� npc�� ����ã�� : ������ ���� ����
void FindFamilyInNear(CCharacter* of, CNPC* npc)
{
	if (of == NULL || npc == NULL) return;

	// Cell 2�� ��������
	int sx = npc->m_cellX - 2;
	int ex = npc->m_cellX + 2;
	int sz = npc->m_cellZ - 2;
	int ez = npc->m_cellZ + 2;

	int x, z;

	for (x = sx; x <= ex; x++)
	{
		if (x < 0 || x >= npc->m_pArea->m_size[0])
			continue;

		for (z = sz; z <= ez; z++)
		{
			if (z < 0 || z >= npc->m_pArea->m_size[1])
				continue;

			CCharacter* ch = npc->m_pArea->m_cell[x][z].m_listChar;
			while (ch)
			{
				if (IS_NPC(ch) && TO_NPC(ch) != npc)
				{
					CNPC* tnpc = TO_NPC(ch);

					// �����̰� �þ� 2�� �̳� �Ÿ��̰� disableTime�� ���� �Ǿ� ���� ������
					// attacklist�� ��� ���� ��
					if (npc->m_proto->m_family != -1 &&
							tnpc->m_proto->m_family == npc->m_proto->m_family &&
							GetDistance(npc, tnpc) < npc->m_proto->m_sight * 2 &&
							tnpc->m_disableTime == 0 && !tnpc->IsBlind()
							&& tnpc->m_attackList == NULL)
						AddAttackList(of, tnpc, HATE_FIRST_ATTACK);
				}
				ch = ch->m_pCellNext;
			}
		}
	}
}

////////////////////
// Function name	: GetSkillPrototypes
// Description	    : proto, level, magicindex�� ������ ������Ÿ���� ��´�
// Return type		: bool
//                  : �����϶� true
bool GetSkillPrototypes(const CSkillProto* proto, int level, int magicindex, const CSkillLevelProto** levelproto, const CMagicProto** magic, const CMagicLevelProto** magiclevel)
{
	*levelproto = NULL;
	*magic = NULL;
	*magiclevel = NULL;

	if (proto == NULL)
		return false;

	if (magicindex < 0 || magicindex >= MAX_SKILL_MAGIC)
		return false;

	*levelproto = proto->Level(level);
	if (*levelproto == NULL)
		return false;

	*magic = (*levelproto)->m_magic[magicindex];
	if (*magic == NULL)
		return false;

	*magiclevel = (*magic)->Level((*levelproto)->m_magicLevel[magicindex]);
	if (*magiclevel == NULL)
		return false;

	return true;
}

// of -> df���� hate��ŭ HATE ��ġ ����
CAttackChar* ApplyHate(CCharacter* of, CCharacter* df, int hate, bool bApplyFamily)
{
	if (of == NULL || df == NULL) return NULL;

	// ���� �˻�
	bool bFirstAttack = false;

	// df�� ����Ʈ�� ����� ������ ����
	if (df->m_attackList == NULL)
	{
		bFirstAttack = true;
		hate += HATE_FIRST_ATTACK;
	}

	// ����Ʈ�� �߰�
	CAttackChar* ret = AddAttackList(of, df, hate);

	// �������� ���� : df == NPC�� ���
	if (bApplyFamily && IS_NPC(df))
		FindFamilyInNear(of, TO_NPC(df));

	return ret;
}

////////////////////
// Function name	: ApplyHateByDamage
// Description	    : of�� df�� damage��ŭ ���ݽ� �ش��ϴ� hate ��ġ�� ����
void ApplyHateByDamage(CCharacter* of, CCharacter* df, char hittype, int damage)
{
	if (of == NULL || df == NULL) return;

	if (hittype != HITTYPE_MISS)
	{
		int hate = 0;

		// of�� NPC�� ��� hate ���� ����
		// damage�� ���� hate ��ġ ���
		if (!IS_NPC(of))
		{
			hate += 10000 * damage / df->m_maxHP;
			if (hate < 1)
				hate = 1;
		}

		CAttackChar* p = ApplyHate(of, df, hate, true);
		if (p)
		{
			if (p->m_damage + damage > 1)
				p->m_damage += damage;
		}
	}
}

////////////////////
// Function name	: ApplyDamage
// Description	    : of�� df�� damageType������ proto�� ������ flag���·� damage��ŭ ����
//                  : �ش��ϴ� damage�޽����� proto�� �ٸ� effect�޽����� ����
void ApplyDamage(CCharacter* of, CCharacter* df, MSG_DAMAGE_TYPE damageType, const CSkillProto* proto, const CMagicProto* magic, int damage, char flag, bool isCharge)
{
	if (of == NULL || df == NULL) return;

	int realdamage = 0;

	// PvP������ ������ 25%��
	bool bIsPCof = (IS_PC(of) || IS_PET(of) || IS_ELEMENTAL(of) || IS_APET(of) );
	bool bIsPCdf = (IS_PC(df) || IS_PET(df) || IS_ELEMENTAL(df) || IS_APET(df) );
	if (bIsPCof && bIsPCdf)
		damage /= 4;


	// remove ign/cube
	if (IS_PC(of) && IS_PC(df)) {
		of->m_assist.CureBySkillIndex(IMMOTAL_BUF);
		of->m_assist.CureBySkillIndex(CUBE_BUF);
		of->m_assist.CureBySkillIndex(IGNI1_BUF);
		of->m_assist.CureBySkillIndex(IGNI2_BUF);
		of->m_assist.CureBySkillIndex(IGNI3_BUF);
		of->m_assist.CureBySkillIndex(IGNI4_BUF);
		of->m_assist.CureBySkillIndex(CAST_POTION);
		of->m_assist.CureBySkillIndex(VELOCITY_BUF);
		of->m_assist.CureBySkillIndex(1742);
		of->m_assist.CureBySkillIndex(975);
		of->m_assist.CureBySkillIndex(1897);
		of->m_assist.CureBySkillIndex(981);
		of->m_assist.CureBySkillIndex(1903);
		of->m_assist.CureBySkillIndex(988);
		of->m_assist.CureBySkillIndex(1910);
		of->m_assist.CureBySkillIndex(1172);
		of->m_assist.CureBySkillIndex(1278);
		of->m_assist.CureBySkillIndex(1310);
		of->m_assist.CureBySkillIndex(1938);
		of->m_assist.CureBySkillIndex(1174);
		of->m_assist.CureBySkillIndex(1280);
		of->m_assist.CureBySkillIndex(1312);
		of->m_assist.CureBySkillIndex(1940);
		of->m_assist.CureBySkillIndex(1188);
		of->m_assist.CureBySkillIndex(1287);
		of->m_assist.CureBySkillIndex(1319);
		of->m_assist.CureBySkillIndex(1947);
		of->m_assist.CureBySkillIndex(931);
		of->m_assist.CureBySkillIndex(1037);
		of->m_assist.CureBySkillIndex(1876);
		of->m_assist.CureBySkillIndex(1918);
		of->m_assist.CureBySkillIndex(936);
		of->m_assist.CureBySkillIndex(1042);
		of->m_assist.CureBySkillIndex(1881);
		of->m_assist.CureBySkillIndex(1923);
		of->m_assist.CureBySkillIndex(947);
		of->m_assist.CureBySkillIndex(10553);
		of->m_assist.CureBySkillIndex(1892);
		of->m_assist.CureBySkillIndex(1934);
		of->m_assist.CureBySkillIndex(946);
		of->m_assist.CureBySkillIndex(1891);
		of->m_assist.CureBySkillIndex(1052);
		of->m_assist.CureBySkillIndex(1933);
		of->m_assist.CureBySkillIndex(963);
		of->m_assist.CureBySkillIndex(967);
		of->m_assist.CureBySkillIndex(1186);
		of->m_assist.CureBySkillIndex(1285);
		of->m_assist.CureBySkillIndex(1317);
		of->m_assist.CureBySkillIndex(1945);
		of->m_assist.CureBySkillIndex(1036);
		of->m_assist.CureBySkillIndex(1917);
		of->m_assist.CureBySkillIndex(794);
		of->m_assist.CureBySkillIndex(1896);
		of->m_assist.CureBySkillIndex(980);
		of->m_assist.CureBySkillIndex(1902);
		of->m_assist.CureBySkillIndex(968);
		of->m_assist.CureBySkillIndex(962);
		of->m_assist.CureBySkillIndex(1093);
		of->m_assist.CureBySkillIndex(229);
		of->m_assist.CureBySkillIndex(323);
		of->m_assist.CureBySkillIndex(1798);
		of->m_assist.CureBySkillIndex(1871);
		of->m_assist.CureBySkillIndex(1997);
		of->m_assist.CureBySkillIndex(1998);
		of->m_assist.CureBySkillIndex(1999);
		of->m_assist.CureBySkillIndex(2000);
		of->m_assist.CureBySkillIndex(2001);
		of->m_assist.CureBySkillIndex(2002);
		of->m_assist.CureBySkillIndex(2003);
		of->m_assist.CureBySkillIndex(2013);
		of->m_assist.CureBySkillIndex(2044);
		of->m_assist.CureBySkillIndex(2045);
		of->m_assist.CureBySkillIndex(2046);
		of->m_assist.CureBySkillIndex(2047);
		of->m_assist.CureBySkillIndex(987);
		of->m_assist.CureBySkillIndex(1909);
		of->m_assist.CureBySkillIndex(935);
		of->m_assist.CureBySkillIndex(1880);
		of->m_assist.CureBySkillIndex(1057);
		of->m_assist.CureBySkillIndex(1058);
		of->m_assist.CureBySkillIndex(1059);
		of->m_assist.CureBySkillIndex(1077);
		of->m_assist.CureBySkillIndex(1076);
		of->m_assist.CureBySkillIndex(939);
		of->m_assist.CureBySkillIndex(941);
		of->m_assist.CureBySkillIndex(943);
		of->m_assist.CureBySkillIndex(966);
		of->m_assist.CureBySkillIndex(971);
		of->m_assist.CureBySkillIndex(977);
		of->m_assist.CureBySkillIndex(984);
		of->m_assist.CureBySkillIndex(991);
		of->m_assist.CureBySkillIndex(1045);
		of->m_assist.CureBySkillIndex(1047);
		of->m_assist.CureBySkillIndex(1049);
		of->m_assist.CureBySkillIndex(1176);
		of->m_assist.CureBySkillIndex(1190);
		of->m_assist.CureBySkillIndex(1197);
		of->m_assist.CureBySkillIndex(1282);
		of->m_assist.CureBySkillIndex(1289);
		of->m_assist.CureBySkillIndex(1296);
		of->m_assist.CureBySkillIndex(1314);
		of->m_assist.CureBySkillIndex(1321);
		of->m_assist.CureBySkillIndex(1328);
		of->m_assist.CureBySkillIndex(1369);
		of->m_assist.CureBySkillIndex(1884);
		of->m_assist.CureBySkillIndex(1886);
		of->m_assist.CureBySkillIndex(1888);
		of->m_assist.CureBySkillIndex(1899);
		of->m_assist.CureBySkillIndex(1906);
		of->m_assist.CureBySkillIndex(1913);
		of->m_assist.CureBySkillIndex(1926);
		of->m_assist.CureBySkillIndex(1928);
		of->m_assist.CureBySkillIndex(1930);
		of->m_assist.CureBySkillIndex(1942);
		of->m_assist.CureBySkillIndex(1949);
		of->m_assist.CureBySkillIndex(1956);
	
		of->m_assist.CureBySkillIndex(1080);
		of->m_assist.CureBySkillIndex(1834);
		of->m_assist.CureBySkillIndex(1835);
		of->m_assist.CureBySkillIndex(1836);
		of->m_assist.CureBySkillIndex(1838);
		of->m_assist.CureBySkillIndex(1839);
		of->m_assist.CureBySkillIndex(1837);
		of->m_assist.CureBySkillIndex(2057);
		of->m_assist.CureBySkillIndex(1079);


		df->m_assist.CureBySkillIndex(IMMOTAL_BUF);
		df->m_assist.CureBySkillIndex(CUBE_BUF);
		df->m_assist.CureBySkillIndex(IGNI1_BUF);
		df->m_assist.CureBySkillIndex(IGNI2_BUF);
		df->m_assist.CureBySkillIndex(IGNI3_BUF);
		df->m_assist.CureBySkillIndex(IGNI4_BUF);
		df->m_assist.CureBySkillIndex(CAST_POTION);
		df->m_assist.CureBySkillIndex(VELOCITY_BUF);
		df->m_assist.CureBySkillIndex(1742);
		df->m_assist.CureBySkillIndex(975);
		df->m_assist.CureBySkillIndex(1897);
		df->m_assist.CureBySkillIndex(981);
		df->m_assist.CureBySkillIndex(1903);
		df->m_assist.CureBySkillIndex(988);
		df->m_assist.CureBySkillIndex(1910);
		df->m_assist.CureBySkillIndex(1172);
		df->m_assist.CureBySkillIndex(1278);
		df->m_assist.CureBySkillIndex(1310);
		df->m_assist.CureBySkillIndex(1938);
		df->m_assist.CureBySkillIndex(1174);
		df->m_assist.CureBySkillIndex(1280);
		df->m_assist.CureBySkillIndex(1312);
		df->m_assist.CureBySkillIndex(1940);
		df->m_assist.CureBySkillIndex(1188);
		df->m_assist.CureBySkillIndex(1287);
		df->m_assist.CureBySkillIndex(1319);
		df->m_assist.CureBySkillIndex(1947);
		df->m_assist.CureBySkillIndex(931);
		df->m_assist.CureBySkillIndex(1037);
		df->m_assist.CureBySkillIndex(1876);
		df->m_assist.CureBySkillIndex(1918);
		df->m_assist.CureBySkillIndex(936);
		df->m_assist.CureBySkillIndex(1042);
		df->m_assist.CureBySkillIndex(1881);
		df->m_assist.CureBySkillIndex(1923);
		df->m_assist.CureBySkillIndex(947);
		df->m_assist.CureBySkillIndex(10553);
		df->m_assist.CureBySkillIndex(1892);
		df->m_assist.CureBySkillIndex(1934);
		df->m_assist.CureBySkillIndex(946);
		df->m_assist.CureBySkillIndex(1891);
		df->m_assist.CureBySkillIndex(1052);
		df->m_assist.CureBySkillIndex(1933);
		df->m_assist.CureBySkillIndex(963);
		df->m_assist.CureBySkillIndex(967);
		df->m_assist.CureBySkillIndex(1186);
		df->m_assist.CureBySkillIndex(1285);
		df->m_assist.CureBySkillIndex(1317);
		df->m_assist.CureBySkillIndex(1945);
		df->m_assist.CureBySkillIndex(1036);
		df->m_assist.CureBySkillIndex(1917);
		df->m_assist.CureBySkillIndex(794);
		df->m_assist.CureBySkillIndex(1896);
		df->m_assist.CureBySkillIndex(980);
		df->m_assist.CureBySkillIndex(1902);
		df->m_assist.CureBySkillIndex(968);
		df->m_assist.CureBySkillIndex(962);
		df->m_assist.CureBySkillIndex(1093);
		df->m_assist.CureBySkillIndex(229);
		df->m_assist.CureBySkillIndex(323);
		df->m_assist.CureBySkillIndex(1798);
		df->m_assist.CureBySkillIndex(1871);
		df->m_assist.CureBySkillIndex(1997);
		df->m_assist.CureBySkillIndex(1998);
		df->m_assist.CureBySkillIndex(1999);
		df->m_assist.CureBySkillIndex(2000);
		df->m_assist.CureBySkillIndex(2001);
		df->m_assist.CureBySkillIndex(2002);
		df->m_assist.CureBySkillIndex(2003);
		df->m_assist.CureBySkillIndex(2013);
		df->m_assist.CureBySkillIndex(2044);
		df->m_assist.CureBySkillIndex(2045);
		df->m_assist.CureBySkillIndex(2046);
		df->m_assist.CureBySkillIndex(2047);
		df->m_assist.CureBySkillIndex(987);
		df->m_assist.CureBySkillIndex(1909);
		df->m_assist.CureBySkillIndex(935);
		df->m_assist.CureBySkillIndex(1880);
		df->m_assist.CureBySkillIndex(1057);
		df->m_assist.CureBySkillIndex(1058);
		df->m_assist.CureBySkillIndex(1059);
		df->m_assist.CureBySkillIndex(1077);
		df->m_assist.CureBySkillIndex(1076);
		df->m_assist.CureBySkillIndex(939);
		df->m_assist.CureBySkillIndex(941);
		df->m_assist.CureBySkillIndex(943);
		df->m_assist.CureBySkillIndex(966);
		df->m_assist.CureBySkillIndex(971);
		df->m_assist.CureBySkillIndex(977);
		df->m_assist.CureBySkillIndex(984);
		df->m_assist.CureBySkillIndex(991);
		df->m_assist.CureBySkillIndex(1045);
		df->m_assist.CureBySkillIndex(1047);
		df->m_assist.CureBySkillIndex(1049);
		df->m_assist.CureBySkillIndex(1176);
		df->m_assist.CureBySkillIndex(1190);
		df->m_assist.CureBySkillIndex(1197);
		df->m_assist.CureBySkillIndex(1282);
		df->m_assist.CureBySkillIndex(1289);
		df->m_assist.CureBySkillIndex(1296);
		df->m_assist.CureBySkillIndex(1314);
		df->m_assist.CureBySkillIndex(1321);
		df->m_assist.CureBySkillIndex(1328);
		df->m_assist.CureBySkillIndex(1369);
		df->m_assist.CureBySkillIndex(1884);
		df->m_assist.CureBySkillIndex(1886);
		df->m_assist.CureBySkillIndex(1888);
		df->m_assist.CureBySkillIndex(1899);
		df->m_assist.CureBySkillIndex(1906);
		df->m_assist.CureBySkillIndex(1913);
		df->m_assist.CureBySkillIndex(1926);
		df->m_assist.CureBySkillIndex(1928);
		df->m_assist.CureBySkillIndex(1930);
		df->m_assist.CureBySkillIndex(1942);
		df->m_assist.CureBySkillIndex(1949);
		df->m_assist.CureBySkillIndex(1956);

		df->m_assist.CureBySkillIndex(1080);
		df->m_assist.CureBySkillIndex(1834);
		df->m_assist.CureBySkillIndex(1835);
		df->m_assist.CureBySkillIndex(1836);
		df->m_assist.CureBySkillIndex(1838);
		df->m_assist.CureBySkillIndex(1839);
		df->m_assist.CureBySkillIndex(1837);
		df->m_assist.CureBySkillIndex(2057);
		df->m_assist.CureBySkillIndex(1079);
	}

	if (flag != HITTYPE_MISS)
	{
		if (damage < 1)
			damage = 1;

		if (IS_PET(df))
		{
			damage = 1;
			// 050309: bw ����� 20���� �̸��϶� ������ 2�� ����
			CPet* p = TO_PET(df);
			if( p )
			{
				if( p->GetHungryPoint() < 20 )
					damage = 2;
			}
		}
	}
	else
		damage = 0;

	if (damage > 0)
	{
		//Ʈ����ų pvp ������ ó��
		if(proto != NULL && proto->m_index == 1753)
		{
			if(IS_PC(df) && IS_NPC(of) && TO_NPC(of)->m_owner != NULL)
			{
				damage /= 4;
			}
		}

		// ���� ó��
		if (df->m_assist.m_state & AST_DESPAIR)
		{
			damage += df->m_assist.m_avAddition.despair
					  + damage * df->m_assist.m_avRate.despair / SKILL_RATE_UNIT;
			df->m_assist.CancelDespair();
		}

		if (df->m_linkSource && df != df->m_linkSource && 
		CheckInNearCellExt(df, df->m_linkSource) && 
		CheckBothPvPArea(df, df->m_linkSource))
		{
			int linkdamage = damage / 2;
			damage -= linkdamage;
			if (linkdamage > 0)
				ProcAttack(of, df->m_linkSource, MSG_DAMAGE_LINK, NULL, 0, linkdamage);
		}

		if (IS_ELEMENTAL(df))
		{
			CElemental* pElemental = TO_ELEMENTAL(df);
			CPC* pPC = pElemental->GetOwner();
			if (pPC && (pPC->m_assist.m_state & AST_MANASCREEN) && CheckInNearCellExt(pElemental, pPC))
			{
				damage -= pPC->m_assist.m_avAddition.manascreen
						  + damage * pPC->m_assist.m_avRate.manascreen / SKILL_RATE_UNIT;
				pPC->m_mp -= pPC->m_maxMP * 3 / 100;
				if (pPC->m_mp <= 0)
				{
					pPC->m_mp = 0;
					pPC->m_assist.CancelManaScreen();
				}
				pPC->m_bChangeStatus = true;
			}
		}

		if (damage < 1)
			damage = 1;

#ifdef ASSIST_REDUCE_SKILL
		if (proto)
		{
			if (GetRandom(1, 10000) <=
					df->m_avPassiveAddition.reduceSkillProb)
			{
				damage = damage - df->m_avPassiveAddition.reduceSkill -
						 damage * df->m_avPassiveRate.reduceSkill /
						 SKILL_RATE_UNIT;
			}

			if (GetRandom(1, 10000) <=
					df->m_assist.m_avAddition.reduceSkillProb)
			{
				damage = damage - df->m_assist.m_avAddition.reduceSkill -
						 damage * df->m_assist.m_avRate.reduceSkill /
						 SKILL_RATE_UNIT;

			//	df->m_assist.DecreaseCount(MT_REDUCE, MST_REDUCE_SKILL);
			}

			if (damage < 0) /* reduce skill can cause damage zero */
				damage = 0;
		}
#endif
		damage = CalcNewDamage(of, df, damage);

		if (damage < 0)
			damage = 0;

		// HP ����
		if (damage > df->m_hp)
			realdamage = df->m_hp;
		else
			realdamage = damage;

		bool bSendOFStatusMsg = false;

		// HP/MP ��ƿ
		if (IS_PC(of) && realdamage > 0)
		{
			CPC* pPCOffense = TO_PC(of);

//#ifdef HP_STEEL_POTION
			if (pPCOffense->m_assist.m_avAddition.hcHPSteelPotion == true )
			{
				int prob = GetRandom( 1, 100 );
				if( prob > 70 ) // 30%
				{
					int nStealHP = realdamage * 5 / 100;
					if( nStealHP > 0 )
					{
						pPCOffense->m_hp += nStealHP;
						if( pPCOffense->m_hp > pPCOffense->m_maxHP )
							pPCOffense->m_hp = pPCOffense->m_maxHP;
						pPCOffense->m_bChangeStash = true;
						bSendOFStatusMsg = true;

						{
							CNetMsg::SP rmsg(new CNetMsg);
							EffectEtcMsg(rmsg, pPCOffense, MSG_EFFECT_ETC_HP_STEEL);
							pPCOffense->m_pArea->SendToCell(rmsg, pPCOffense, true);
						}
					}
				}
			}
			else
//#endif // HP_STEEL_POTION
				if (pPCOffense->m_opHPSteal > 0)
				{
					if (GetRandom(1, 100) > 95) // 5%
					{
						int nStealHP = realdamage * pPCOffense->m_opHPSteal / 100;
						if (nStealHP > 0)
						{
							pPCOffense->m_hp += nStealHP;
							if (pPCOffense->m_hp > pPCOffense->m_maxHP)
								pPCOffense->m_hp = pPCOffense->m_maxHP;
							pPCOffense->m_bChangeStatus = true;
							bSendOFStatusMsg = true;
						}
					}
				}

//#ifdef MP_STEEL_POTION
			if (pPCOffense->m_assist.m_avAddition.hcMPSteelPotion == true )
			{
				int prob = GetRandom( 1, 100 );
				if( prob > 70 ) // 30%
				{
					int nStealMP = pPCOffense->m_maxMP * 10 / 100;
					if (nStealMP > 0)
					{
						pPCOffense->m_mp += nStealMP;
						if (pPCOffense->m_mp > pPCOffense->m_maxMP)
							pPCOffense->m_mp = pPCOffense->m_maxMP;
						pPCOffense->m_bChangeStatus = true;
						bSendOFStatusMsg = true;

						{
							CNetMsg::SP rmsg(new CNetMsg);
							EffectEtcMsg(rmsg, pPCOffense, MSG_EFFECT_ETC_MP_STEEL);
							pPCOffense->m_pArea->SendToCell(rmsg, pPCOffense, true);
						}
					}
				}
			}
			else
//#endif // MP_STEEL_POTION
				if (pPCOffense->m_opMPSteal > 0)
				{
					if (GetRandom(1, 100) > 95) // 5%
					{
						int nStealMP = realdamage * pPCOffense->m_opMPSteal / 100;
						if (nStealMP > 0)
						{
							pPCOffense->m_mp += nStealMP;
							if (pPCOffense->m_mp > pPCOffense->m_maxMP)
								pPCOffense->m_mp = pPCOffense->m_maxMP;
							pPCOffense->m_bChangeStatus = true;
							bSendOFStatusMsg = true;
						}
					}
				}
		}

		if (magic
#ifdef ASSIST_REDUCE_SKILL
				&& realdamage > 0
#endif
		   )
		{
			switch (magic->m_type)
			{
			case MT_ATTACK:
				switch (magic->m_subtype)
				{
				case MST_ATTACK_DRAIN:
					if (!IS_PET(of) && !IS_PET(df))
					{
						if (IS_PC(of) && IS_PC(df))
							of->m_hp += realdamage / 2;
						else
							of->m_hp += realdamage;
						if (of->m_hp > of->m_maxHP)
							of->m_hp = of->m_maxHP;

						if (IS_PC(of))
						{
							CPC* opc = TO_PC(of);
							opc->m_bChangeStatus = true;
						}
						bSendOFStatusMsg = true;
					}
					break;
				case MST_ATTACK_ONESHOTKILL:
					// 15% �̸��̸� ��簡 �����
					if ( IS_NPC(df) && df->m_hp <= df->m_maxHP * 15 / 100 )
					{
						damage = df->m_hp;
					}
					break;
				}
				break;
			}
		}

		if ( IS_APET(df) )
		{
			CAPet* apet = TO_APET(df);
			if( apet )
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ExAPetStatusMsg( rmsg, apet);
				SEND_Q( rmsg, apet->GetOwner()->m_desc );
			}
		}

		if (bSendOFStatusMsg)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			CharStatusMsg(rmsg, of, 0);
			df->m_pArea->SendToCell(rmsg, of, true);
		}

		// npc�� ���÷��� �������� �ް� ������ npc=null �Ǿ� ���� �ٿ� ���� ����
		switch( damageType )
		{
		case MSG_DAMAGE_REFLEX:
		case MSG_DAMAGE_LINK:
			if( IS_NPC(df) )
			{
				if( damage >= df->m_hp )
					damage = df->m_hp -1;
			}
			break;
		default:
			break;
		}

#ifdef TLD_EVENT_SONG
		if (IS_NPC(df))
		{
			CNPC* pNpc = TO_NPC(df);
			if (pNpc->m_proto->m_index == 1622 || pNpc->m_proto->m_index == 1623)
			{
				damage = 1;
			}
		}
#endif

		df->m_hp -= damage;

		if ( of->m_assist.m_state & AST_INVERSE_DAMAGE && damageType != MSG_DAMAGE_COMBO )
		{
			// �� ������ ������� �ɸ� �����̸� ���� �޺� ����Ʈ �������� ������ ��� �������� ȸ������ �ٲ۴�.
			df->m_hp += damage * 2;
		}

		if(IS_APET(df))
		{
			if(df->m_hp >= df->m_maxHP + TO_APET(df)->GetOwner()->m_opJewelElementPetHPUP)
			{
				df->m_hp = df->m_maxHP + TO_APET(df)->GetOwner()->m_opJewelElementPetHPUP;
			}
		}
		else if (df->m_hp >= df->m_maxHP)
			df->m_hp = df->m_maxHP;
		if (df->m_hp <= 0)
			df->m_hp = 0;

		if(IS_PC(df))
		{
			CNetMsg::SP rmsg(new CNetMsg);
			UpdateClient::CharStatusHPMP(rmsg, df->m_maxHP, df->m_hp, df->m_maxMP, df->m_mp);
			SEND_Q(rmsg, TO_PC(df)->m_desc);
		}
	}
	//�����ۿ� �ɼ�(�нú�, ������, �����) �� �ִ� ��� ����.
	//TODO	1�ܰ� : ĳ���Ͱ� �԰� �ִ� �������� �˻��Ѵ�.
	//		2�ܰ� : �����ۿ� �ִ� �ɼ��߿� �нú��̸� �׻� ����, �������̸� ���ݽ� ����, ������̸� ���ظ� �Ծ��� �� �����Ų��.
	//		3�ܰ� : ��ų �޽����� ������.

	//���� ������ ������ ���� ���������� +@�� ��.

	int holyItemIndex = -1;

	if(IS_PC(of) && flag != HITTYPE_MISS )
	{
		CPC* pc = TO_PC(of);
		if(pc->holy_water_item != NULL && isCharge == false)
		{
			holyItemIndex = pc->holy_water_item->getDBIndex();
			damage = HolyWaterData::instance()->getDamage(pc, df, magic, damage);			
		}
	}

	// ��� �޽���
	if (proto)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		DamageMsg(rmsg, of, df, damageType, proto->m_index, damage, flag, holyItemIndex);
#if defined (LC_GAMIGO) || defined (LC_USAA) || defined (LC_RUS)					//�������� �α� �Դ���
		if(IS_NPC(df)) 															//����NPC���� �����ϴ� ��� �α�
		{
			CNPC *npc = TO_NPC(df);
			if(npc->m_proto->CheckFlag(NPC_BOSS | NPC_MBOSS))
			{
				GAMELOG << init("BOSS DAMAGE IN") << df->m_index << df->m_name << delim << damage << delim << proto->m_index << delim << of->m_name << delim;
				CAssistData *p = NULL;
				CAssistData *pNext = NULL;

				p = of->m_assist.m_help.getHead();
				while((pNext = p))
				{
					p = p->m_next;
					GAMELOG << pNext->m_proto->m_index << "(" << pNext->m_level << ") ";
				}
				GAMELOG << end;
			}
		}
		if(IS_NPC(of)) 															//����NPC���� ���ݴ��� ��� �α�
		{
			CNPC *npc = TO_NPC(of);
			if(npc->m_proto->CheckFlag(NPC_BOSS | NPC_MBOSS))
			{
				//GAMELOG << init("BOSS DAMAGE OUT") << of->m_index << of->m_name << delim << damage << delim << proto->m_index << delim << df->m_name << delim;
				CAssistData *p = NULL;
				CAssistData *pNext = NULL;

				p = df->m_assist.m_help.getHead();
				while((pNext = p))
				{
					p = p->m_next;
					GAMELOG << pNext->m_proto->m_index << "(" << pNext->m_level << ") ";
				}
				GAMELOG << end;
			}
		}
#endif
		df->m_pArea->SendToCell(rmsg, df, true);
	}
	else
	{
		//�Ϲ� �����϶�
		CNetMsg::SP rmsg(new CNetMsg);
		DamageMsg(rmsg, of, df, damageType, -1, damage, flag, holyItemIndex);
#if defined (LC_GAMIGO) || defined (LC_USAA) || defined (LC_RUS)					//�������� �α� �Դ���
		if(IS_NPC(df)) 															//����NPC���� ������ ��� �α�
		{
			CNPC *npc = TO_NPC(df);
			if(npc->m_proto->CheckFlag(NPC_BOSS | NPC_MBOSS))
			{
				GAMELOG << init("BOSS DAMAGE IN") << df->m_index << df->m_name << delim << damage << delim << -1 << delim << of->m_name << delim;
				CAssistData *p = NULL;
				CAssistData *pNext = NULL;

				p = of->m_assist.m_help.getHead();
				while((pNext = p))
				{
					p = p->m_next;
					GAMELOG << pNext->m_proto->m_index << "(" << pNext->m_level << ") ";
				}
				GAMELOG << end;
			}
		}
		if(IS_NPC(of)) 															//����NPC���� ���ݴ��� ��� �α�
		{
			CNPC *npc = TO_NPC(of);
			if(npc->m_proto->CheckFlag(NPC_BOSS | NPC_MBOSS))
			{
				//GAMELOG << init("BOSS DAMAGE OUT") << of->m_index << of->m_name << delim << damage << delim << -1 << delim << df->m_name << delim;
				CAssistData *p = NULL;
				CAssistData *pNext = NULL;

				p = df->m_assist.m_help.getHead();
				while((pNext = p))
				{
					p = p->m_next;
					GAMELOG << pNext->m_proto->m_index << "(" << pNext->m_level << ") ";
				}
				GAMELOG << end;
			}
		}
#endif
		df->m_pArea->SendToCell(rmsg, df, true);
	}

	//���� ������ �ִ� ��쿡(���ݰ��ɸ��)�� �ش� ������ �����ش�.
	if (of->m_assist.FindBySkillIndex(IMMOTAL_BUF) && of->m_bFirstDoIt == true)
	{
		of->m_assist.CureBySkillIndex(IMMOTAL_BUF);
	}
}

////////////////////
// Function name	: CalcPKPoint
// Description	    : of�� ���� df�� ����� of, df�� ���� ��ġ ���
//                  : bDeadPet�� true�̸� Pet ����� ���� ó��
void CalcPKPoint(CPC* of, CPC* df, bool bDeadPet)
{
	if (of == NULL || df == NULL) return;

	//�����ڰ� ���Ҽ��� �ƴ϶�� return;
	if (of->m_pZone->isRVRZone() && of->getSyndicateType() != 0)
		return;
	
	// ������ ī������ �˻�

#ifdef FREE_PK_SYSTEM
	if( !gserver->m_bFreePk )
	{
#endif // FREE_PK_SYSTEM

#ifdef MAL_DISABLE_PKPENALTY
		if( !gserver->m_bDisablePKPaenalty )
		{
#endif // MAL_DISABLE_PKPENALTY

			bool isPKChar = (of->m_pkPenalty < -9) ? true : false;

			if (!df->IsChaotic() || bDeadPet)
			{
				// ������ ��� ���� �Ǵ� �� ����
#ifdef REFORM_PK_PENALTY_201108 // PK �г�Ƽ ���� :: ������ ����� �׿����� ī���������� ����
				if( of->IsChaotic() ) // ī���� �Ϲ��̳� ���͸� �׿��� ���
				{
					int penalty = 0;
					if( of->m_pkPenalty >= PK_CHAOTIC_POINT_1 )
						penalty = -8000;
					else if ( of->m_pkPenalty >= PK_CHAOTIC_POINT_2 )
						penalty = -10000;
					else
						penalty = -15000;

					of->AddPkPenalty( penalty );
				}
				else // �Ϲ��̳� ���Ͱ� �Ϲ� Ȥ�� ���͸� �׿��� ��� ������ ī���� �����.
					of->m_pkPenalty = PK_CHAOTIC_POINT_1;
#else
				of->m_pkPenalty -= 10;
				if (!df->IsSetPlayerState(PLAYER_STATE_PKMODE))
					of->m_pkPenalty -= 10;
				if (of->m_pkPenalty < -155)
					of->m_pkPenalty = -155;
#endif // REFORM_PK_PENALTY_201108 // PK �г�Ƽ ����
				of->m_pkCount -= 1;
				if (of->m_pkCount < -110)
					of->m_pkCount = -110;
			}
			else
			{
				// ���۳� ����
#ifdef REFORM_PK_PENALTY_201108 // PK �г�Ƽ ���� :: ī���� �׿��ٸ�
				if( of->m_pkPenalty >= 0 && of->m_pkPenalty < PK_HUNTER_POINT_1 ) // Ư�� ���� ���������� ī���� ���϶� ���� ��ġ�� �ش�.
				{
					int nlevel = df->m_level - of->m_level;
					int pkPenalty = 0;
					if( nlevel > 4 )
						pkPenalty += 3000;
					else if( nlevel > -5 )
						pkPenalty += 1000;
					else if( nlevel <= -5 )
						pkPenalty += 200;

					if( of->m_assist.m_avRate.pkDispositionPointValue > 0 )
					{
						pkPenalty = pkPenalty * of->m_assist.m_avRate.pkDispositionPointValue;
						of->m_assist.CureByItemIndex(7474);	// ���� ��ġ ��� ������
						of->m_assist.CureByItemIndex(7475);	// ���� ��ġ ��� ������
						of->m_assist.CureByItemIndex(7476);	// ���� ��ġ ��� ������
					}

					of->AddPkPenalty( pkPenalty );
				}

				if( df->m_level >= of->m_level )
				{
					of->m_pkCount += 1;
					if (of->m_pkCount > 110)
						of->m_pkCount = 110;
				}
#else // REFORM_PK_PENALTY_201108 // PK �г�Ƽ ���� :: ī���� �׿��ٸ�
				// ���� �̻��̸�
				if (df->m_level >= of->m_level)
				{
					if( !gserver->m_bNonPK )
						of->m_pkPenalty += 5;

					if (of->m_pkPenalty > 155)
						of->m_pkPenalty = 155;

					of->m_pkCount += 1;

					if (of->m_pkCount > 110)
						of->m_pkCount = 110;
				}
#endif // REFORM_PK_PENALTY_201108  PK �г�Ƽ ���� :: ī���� �׿��ٸ�
			}

#ifdef REFORM_PK_PENALTY_201108 // PK �г�Ƽ ����
			if (of->m_pkPenalty < 0 )
#else // REFORM_PK_PENALTY_201108 // PK �г�Ƽ ����
			if (of->m_pkPenalty < -9)
#endif // REFORM_PK_PENALTY_201108 // PK �г�Ƽ ����
			{
				if (!isPKChar || of->m_pkRecoverPulse <= 0)
					of->m_pkRecoverPulse = TIME_ONE_HOUR;
			}
#ifdef MAL_DISABLE_PKPENALTY
		}
#endif // MAL_DISABLE_PKPENALTY

#ifdef FREE_PK_SYSTEM
	}
#endif // FREE_PK_SYSTEM

	of->m_bChangeStatus = true;


	{
		// ���Ƽ ��ġ ���� �˸���
		CNetMsg::SP rmsg(new CNetMsg);
		CharStatusMsg(rmsg, of, 0);
		of->m_pArea->SendToCell(rmsg, of, false);
	}

	of->m_bChangeStatus = true;
}

void CalcWarPoint(CCharacter* of, CCharacter* df)
{
	if (of == NULL || df == NULL) return;

	// ������ �̷������ �ִ� ������
	int zoneindex = of->m_pZone->m_index;
	CWarCastle* castle = CWarCastle::GetCastleObject(zoneindex);
	if (castle == NULL)
		return ;

	// �����߿� ����� ����� ����Ʈ ���� : 10 %
	if (IS_PC(df))
	{
		CPC* dpc = TO_PC(df);
		if (dpc->m_guildInfo && dpc->m_guildInfo->guild())
		{
			if (dpc->GetJoinFlag(dpc->m_pZone->m_index) == WCJF_ATTACK_GUILD)
			{
				if (castle->GetState() == WCSF_WAR_CASTLE)
				{
					if (castle->IsTop3Guild(dpc->m_guildInfo->guild()->index()))
					{
						int point=0;
						if(dpc->m_guildInfo->pos() == MSG_GUILD_POSITION_BOSS)
							point = (int)(point / 10.0 + 0.5);
						else if(dpc->m_guildInfo->pos() == MSG_GUILD_POSITION_OFFICER)
							point = (int)(point / 20.0 + 0.5);

						if(point > 0)
						{
							castle->IncreaseTeamPoint(dpc->m_guildInfo->guild()->index(), -point);
							PCManager::instance()->sendGuildWarPointMsg(castle, dpc->m_pZone->m_index);
						}
					}
				}
			}
		}
	} // �����߿� ����� ����� ����Ʈ ���� : 10 %

	if (castle->GetState() != WCSF_WAR_FIELD)
		return ;

	int mode = 0;			// ����Ʈ ��� ���, ����(0), ����1����Ʈ(1), ����1����Ʈ(2), ����20����Ʈ(3)

	// ���� ����� PC�ΰ�?
	if (IS_PC(of))
	{
		CPC* opc = TO_PC(of);

		if (IS_DEFENSE_TEAM(opc->GetJoinFlag(zoneindex)))
		{
			// �������� ���� �Ŷ��, ���� ����� ���� ���ΰ�?
			if (IS_PC(df))
			{
				CPC* dpc = TO_PC(df);
				if (IS_ATTACK_TEAM(dpc->GetJoinFlag(zoneindex)))
				{
					mode = 1;
				}
			}
		}
		else if (opc->GetJoinFlag(zoneindex) == WCJF_ATTACK_GUILD)
		{
			// ���������� ���� �Ŷ��
			// PC�ΰ�? ��ȣ���ΰ�
			if (IS_PC(df))
			{
				CPC* dpc = TO_PC(df);
				if (dpc->GetJoinFlag(zoneindex) != WCJF_NONE)
				{
					mode = 2;
				}
			}
			else if (IS_NPC(df))
			{
				CNPC* dnpc = TO_NPC(df);
				if (dnpc->m_proto->CheckFlag(NPC_CASTLE_GUARD))
				{
					mode = 3;
				}
			}
		}
	}
	else if (IS_NPC(of))
	{
		// ��ȣ���� �׿��ٸ�
		CNPC* onpc = TO_NPC(of);
		if (onpc->m_proto->CheckFlag(NPC_CASTLE_GUARD))
		{
			// ������ ������
			if (IS_PC(df))
			{
				CPC* dpc = TO_PC(df);
				if (IS_ATTACK_TEAM(dpc->GetJoinFlag(zoneindex)))
				{
					mode = 1;
				}
			}
		}
	}
	else
		return ;

	int increasePoint=0;
	switch(mode)
	{
	case 1:
	case 2:
		if (IS_PC(df))
		{
			CPC* dpc = TO_PC(df);
			int joinflag = dpc->GetJoinFlag(zoneindex);

			if(joinflag == WCJF_OWNER							// ��������� ��
					|| joinflag == WCJF_DEFENSE_GUILD
					|| joinflag == WCJF_ATTACK_GUILD)
			{
				if(dpc->m_guildInfo)
				{
					MSG_GUILD_POSITION_TYPE postype = dpc->m_guildInfo->pos();
					if(postype == MSG_GUILD_POSITION_BOSS)			increasePoint=20;
					else if(postype == MSG_GUILD_POSITION_OFFICER)	increasePoint=7;
					else if(postype != MSG_GUILD_POSITION_UNKNOWN)	increasePoint=5;
				}
			}
			else if(joinflag == WCJF_DEFENSE_CHAR				// �뺴������ ��
					|| joinflag == WCJF_ATTACK_CHAR)
			{
				// �뺴�� 5��
				increasePoint=5;
			}
		}
		break;
	case 3:														// ��ȣ�� NPC �� ��
		increasePoint=3;
		break;
	default:
		return ;
	}

	switch (mode)
	{
	case 1:			// ������ 1����Ʈ
		{
			int totalDamage = 0;
			int damage = 0;	// �������� �� ����� ����

			// PC�� �����ߴ� ĳ���� ������ ���鼭 �������� �� ����� ������ ���Ѵ�
			CAttackChar* p = df->m_attackList;
			while (p)
			{
				if (p->ch)
				{
					totalDamage += p->m_damage;

					switch (p->ch->m_type)
					{
					case MSG_CHAR_PC:
						// �ش� �� ������ �������
						if (IS_DEFENSE_TEAM(p->pc->GetJoinFlag(zoneindex)))
							damage += p->m_damage;
						break;
					case MSG_CHAR_NPC:
						// ��ȣ���̶��
						if (p->npc->m_proto->CheckFlag(NPC_CASTLE_GUARD))
							damage += p->m_damage;
						break;
					default:
						return ;
					}
				}	// if (p->ch)

				p = p->m_next;
			}	// while (p)

			// ü���� ���� �̻� ������� �ذ�� ����Ʈ ����
			if (totalDamage / 2 <= damage && damage > 0)
			{
				castle->IncreaseTeamPoint(0, increasePoint);
			}
		}
		break;

	case 2:			// ������ 1����Ʈ
	case 3:			// ������ 5����Ʈ
		{
			int totalDamage = 0;
			int countAttackGuild = castle->GetCountAttackGuild();		// ���� ��� ��
			int* indexAttackGuild = new int[countAttackGuild];			// ���� ��� �ε���
			int* damagePerAttackGuild = new int[countAttackGuild];		// ���� ��庰 �����
			int maxDamageGuild = 0;										// ������� ���� ���� �� ��� �迭 �ε���
			int damageAttackTeam = 0;									// ������(���, �뺴)�� �� ����� ����

			// �迭 �ʱ�ȭ
			memset(indexAttackGuild, 0, sizeof(int) * countAttackGuild);
			memset(damagePerAttackGuild, 0, sizeof(int) * countAttackGuild);

			// df �����ߴ� ĳ���� ������ ���鼭
			CAttackChar* p = df->m_attackList;
			while (p)
			{
				if (p->ch)
				{
					totalDamage += p->m_damage;

					if (IS_PC(p->ch))
					{
						// �ش� �� ������ ���� �߿�, ��� ������ �ִ� �����̸�
						if (p->pc->GetJoinFlag(zoneindex) == WCJF_ATTACK_GUILD && p->pc->m_guildInfo && p->pc->m_guildInfo->guild())
						{
							int i;
							for (i = 0; i < countAttackGuild; i++)
							{
								if (indexAttackGuild[i] == p->pc->m_guildInfo->guild()->index() || indexAttackGuild[i] == 0)
								{
									// �ش� ��� ����� �հ迡 ���ϰ�
									indexAttackGuild[i] = p->pc->m_guildInfo->guild()->index();
									damagePerAttackGuild[i] += p->m_damage;

									// ������ ��� �߿� ���� ������� ���� �� ��带 ���
									if (i != 0 && damagePerAttackGuild[i] >= damagePerAttackGuild[maxDamageGuild])
										maxDamageGuild = i;

									break;	// break for
								}
							}
						}
						if (IS_ATTACK_TEAM(p->pc->GetJoinFlag(zoneindex)))
							damageAttackTeam += p->m_damage;
					}
				}	// if (p->ch)

				p = p->m_next;
			}	// while (p)

			// ���� �����(�Ǵ� �ִ� ü��)�� �������� ��ü ������� ���ؼ� �������� 50% �̻��� �����ؾ� ����Ʈ�� ����
			if (totalDamage / 2 <= damageAttackTeam && indexAttackGuild[maxDamageGuild] != 0)
			{
				castle->IncreaseTeamPoint(indexAttackGuild[maxDamageGuild], increasePoint);
			}

			delete [] indexAttackGuild;
			delete [] damagePerAttackGuild;
		}
		break;
	default:
		return ;
	}
	PCManager::instance()->sendGuildWarPointMsg(castle, zoneindex);
}
typedef std::map<int, std::pair<int, time_t>> PlayerKillHistory; // Key: player's unique identifier, Value: consecutive kills count
void DropPvPTokenDeadPC(CCharacter* of, CCharacter* df)
{
	if (of == NULL || df == NULL) return;

	if (!IS_PC(df) || !IS_PC(of))
		return;

	CPC* dpc = TO_PC(df);
	CPC* pc = TO_PC(of);
	bool repeatKill = false;
	int diffLevel = of->m_level - df->m_level;
	int points = 0;
	int calculatedPoints = 10 * df->m_level + 200;
	 // Create or update the kill history between attacker and defender
   // Create or update the kill history between attacker and defender
    static PlayerKillHistory killHistory;
    time_t now;
    time(&now);

    // Check if 5 minutes have passed since the last kill for both players
    if (killHistory.find(pc->m_index) != killHistory.end() &&
        now - killHistory[pc->m_index].second >= 5 * 60)
    {
        // Reset the consecutive kill count for the attacker as 5 minutes have passed
        killHistory[pc->m_index].first = 0;
    }

    if (killHistory.find(df->m_index) != killHistory.end() &&
        now - killHistory[df->m_index].second >= 5 * 60)
    {
        // Reset the consecutive kill count for the defender as 5 minutes have passed
        killHistory[df->m_index].first = 0;
    }

    // Update the kill count and last kill timestamp for both players
    killHistory[pc->m_index].first++;
    killHistory[pc->m_index].second = now;
    killHistory[df->m_index].first++;
    killHistory[df->m_index].second = now;

    // Check if the defender has killed the attacker previously
    if (killHistory[df->m_index].first >= 3)
    {
        // If the defender has killed the attacker 3 times or more, prevent further points
        LOG_INFO("Player %d cannot receive points from consecutive kills by player %d", pc->m_index, df->m_index);
        return;
    }
	
	//Dont allow low levels to get points (only last 25 levels)
	if (pc->m_level <= 184 && dpc->m_level <= 184)
         return;
	//check if they are in castle  to lower the time needed between kills
	CWarCastle* castle = CWarCastle::GetCastleObject(df->m_pZone->m_index);

	int timeWait = 5;

	if (castle)
		timeWait = 1;
	
	//time_t now;
	//time(&now);
	for(int i = 0; i < pc->m_lastHonorKills.size(); i++)
	{
		if (pc->m_lastHonorKills[i].char_index == pc->m_index)
		{
			if ((now - pc->m_lastHonorKills[i].tm_kill) < TIME_ONE_MIN * 5 )
				repeatKill = true;
		}
	}

	HonorKill newKill;
	newKill.char_index = pc->m_index;
	newKill.tm_kill = now;
	pc->m_lastHonorKills.push_back(newKill);


	if (diffLevel <= 0)
	{
		points = 500;
		if (castle && castle->GetState() != WCSF_NORMAL && (df->GetMapAttr() & MATT_WAR || df->m_pZone->IsWarZone((int)df->m_pos.m_x, (int)df->m_pos.m_z)))
			points *= 2;
		else if (repeatKill)
			points = 50;
	}
	else
	{
		points = abs(diffLevel) * 10 + 100;
		if (points > 1000)
			points = 1000;
		if (castle && castle->GetState() != WCSF_NORMAL && (df->GetMapAttr() & MATT_WAR || df->m_pZone->IsWarZone((int)df->m_pos.m_x, (int)df->m_pos.m_z)))
			points *= 2;
		else if (repeatKill)
			points = 50;
	}

	int tmpPoints = pc->m_honor + points;
	if (tmpPoints > MAX_HONOR_PTS)
		tmpPoints = MAX_HONOR_PTS;
	
	LOG_INFO("Honor: %d : %d : %d", pc->m_index, pc->m_honor, tmpPoints);
	
	pc->m_honor += points;
	pc->m_prestigePoints += calculatedPoints;
	{
		// Exp, SP �޽��� ����
		CNetMsg::SP rmsg(new CNetMsg);
		HonorMsg(rmsg, points);
		SEND_Q(rmsg, pc->m_desc);
	}

	if (pc->m_lastHonorKills.size() > 30)
		pc->m_lastHonorKills.erase(pc->m_lastHonorKills.begin());
}

void DropWarCastleTokenDeadPC(CCharacter* df)
{
	if(!IS_PC(df))
		return ;

	CPC* dpc = TO_PC(df);

	int zoneindex=df->m_pZone->m_index;
	CWarCastle* castle = CWarCastle::GetCastleObject(zoneindex);
	if(castle == NULL)
		return ;

	if(castle->GetState() == WCSF_NORMAL)
		return ;

	if( dpc->GetJoinFlag(zoneindex) == WCJF_NONE  )
		return ;

	if ( !castle->IsInInnerCastle(dpc) )
		return ;

	// Ȯ�� ���
	if(GetRandom(1, 100) > 5)
		return ;

	int maxdamage = 0;
	CAttackChar* p = NULL;
	CAttackChar* pNext = dpc->m_attackList;

	CCharacter* preference = NULL;
	while( (p = pNext) )
	{
		pNext = pNext->m_next;
		if(!p->ch)
			continue;
		if(!IS_PC(p->ch))
			continue;

		if ((p->ch->m_pZone->m_index != df->m_pZone->m_index) ||
				(p->ch->m_pArea->m_index != df->m_pArea->m_index) ||
				!CheckInNearCellExt(p->ch, dpc))
			continue ;

		if(maxdamage <= p->m_damage)
		{
			maxdamage = p->m_damage;
			preference = p->ch;
		}

		//	p = p->m_next;
	}

	if(preference == NULL)
		return ;

	CItem* pItem = gserver->m_itemProtoList.CreateItem(6653, -1, 0, 0, 1);
	if (!pItem)
		return ;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		pItem->m_preferenceIndex = preference->m_index;
		dpc->m_pArea->DropItem(pItem, dpc);
		ItemDropMsg(rmsg, dpc, pItem);
		pItem->m_pArea->SendToCell(rmsg, dpc, true);
	}

	// 7. ���� �α�
	GAMELOG << init("WARCASTLE_TOKEN_DROP_DEAD_PC", dpc)
			<< "ITEM" << delim
			<< itemlog(pItem)
			<< end;
}

void DropWarCastleToken(CNPC* npc, CPC* pc, CPC* tpc, int level)
{
	if (!tpc || !npc)
		return ;

	if(!npc->m_proto->CheckFlag( (1 << 6) | (1 << 9) ))
		return ;

	CWarCastle* castle = CWarCastle::GetCastleObject(npc->m_pZone->m_index);
	if(!castle)
		return ;

	if(castle->GetState() == WCSF_NORMAL)
		return ;

	if(tpc->GetJoinFlag(castle->GetZoneIndex()) != WCJF_NONE)
	{
		// Ȯ�� ����
		if(GetRandom(1, 100) <= 5)
		{
			CItem* pItem = gserver->m_itemProtoList.CreateItem(6653, -1, 0, 0, 1);
			if (!pItem)
				return ;

			{
				CNetMsg::SP rmsg(new CNetMsg);
				pItem->m_preferenceIndex = tpc->m_index;
				npc->m_pArea->DropItem(pItem, npc);
				ItemDropMsg(rmsg, npc, pItem);
				pItem->m_pArea->SendToCell(rmsg, GET_YLAYER(pItem), pItem->m_cellX, pItem->m_cellZ);
			}

			// 7. ���� �α�
			GAMELOG << init("WARCASTLE_TOKEN_DROP", tpc)
					<< "NPC" << delim
					<< npc->m_idNum << delim
					<< npc->m_name << delim
					<< "NPC LEVEL" << delim
					<< npc->m_level << delim
					<< "PC LEVEL" << delim
					<< tpc->m_level << delim
					<< "ITEM" << delim
					<< itemlog(pItem)
					<< end;
		}
	}
}

void ProcFollowNPC(CNPC* npc)
{
	if (npc == NULL) return;

	// ���� �÷��� 0
	if (npc->m_proto->CheckLeaderBit(0) && npc->m_proto->m_family != -1)
	{
		// �������� ��Ŀ �켱���� �ִ� 5�� HP/MP ȸ��
		int sx = npc->m_cellX - CELL_EXT;
		int ex = npc->m_cellX + CELL_EXT;
		int sz = npc->m_cellZ - CELL_EXT;
		int ez = npc->m_cellZ + CELL_EXT;

		int x, z;
		float dist[5] = {999.9f, 999.9f, 999.9f, 999.9f, 999.9f};
		CNPC* ret[5] = {NULL, NULL, NULL, NULL, NULL};

		int i = 0;
		// �ϴ� �ٸ� ���� �˻� ���Ѵ�
		for (x = sx; x <= ex; x++)
		{
			if (x < 0 || x >= npc->m_pArea->m_size[0]) continue;
			for (z = sz; z <= ez; z++)
			{
				if (z < 0 || z >= npc->m_pArea->m_size[1]) continue;
				CCharacter *pChar;
				for (pChar = npc->m_pArea->m_cell[x][z].m_listChar; pChar; pChar = pChar->m_pCellNext)
				{
					// NPC��, �ڽ��� ����, ������ ����, �ٸ��� ����
					if (!IS_NPC(pChar) || pChar == npc || DEAD(pChar) || ABS(GET_YLAYER(npc) - GET_YLAYER(pChar)) >= 2)
						continue ;

					CNPC* tnpc = TO_NPC(pChar);

					// �����̰�
					if (tnpc->m_proto->m_family != npc->m_proto->m_family)
						continue ;

					// ������ Ÿ�԰˻� : ��Ŀ, �ڽ���Ÿ��, �׿�, ����
					// Ÿ���� ������ �Ÿ��� ��
					bool bReqSort = false;
					if (i < 5)
					{
						dist[i] = GetDistance(npc, tnpc);
						ret[i] = tnpc;
						i++;
						if (i == 5)
							bReqSort = true;
					}
					else
					{
						for (i = 0; i < 5; i++)
						{
							int resComp = AIComp(npc, tnpc, ret[i]);
							if (resComp < 0 || (resComp == 0 && dist[i] > GetDistance(npc, tnpc)))
							{
								dist[i] = GetDistance(npc, tnpc);
								ret[i] = tnpc;
								bReqSort = true;
								break;
							}
						}
					}

					// �Ÿ� ���� �� �༮�� �տ����� ����
					if (bReqSort)
					{
						int k;
						int j;
						int mindist;
						for (k = 0; k < 5 - 1; k++)
						{
							mindist = 0;
							for (j = 1; j < 5 - i; j++)
							{
								if (dist[j] < dist[mindist])
									mindist = j;
							}
							float tmpdist = dist[5 - k - 1];
							dist[5 - k - 1] = dist[mindist];
							dist[mindist] = tmpdist;
							CNPC* tmpNPC = ret[5 - k - 1];
							ret[5 - k - 1] = ret[mindist];
							ret[mindist] = tmpNPC;
						}
					}
				}
			}
		}

		for (i = 0; i < 5; i++)
		{
			if (ret[i])
			{
				ret[i]->m_hp = ret[i]->m_maxHP;
				ret[i]->m_mp = ret[i]->m_maxMP;
				CNetMsg::SP rmsg(new CNetMsg);
				CharStatusMsg(rmsg, ret[i], 0);
				ret[i]->m_pArea->SendToCell(rmsg, ret[i]);
			}
		}
	} // --- ���� �÷��� 0
}

int AIComp(CNPC* base, CNPC* n1, CNPC* n2)
{
	if (n1 == NULL && n2 == NULL)
		return 0;
	if (n1 == NULL)
		return 1;
	if (n2 == NULL)
		return -1;

	int typeb = base->m_proto->m_aitype;
	int type1 = n1->m_proto->m_aitype;
	int type2 = n2->m_proto->m_aitype;

	if (type1 == type2)
		return 0;

	// �Ϲ� ���� ���� �켱����
	if (type1 != NPC_AI_NORMAL && type2 == NPC_AI_NORMAL)
		return -1;
	if (type1 == NPC_AI_NORMAL && type2 != NPC_AI_NORMAL)
		return 1;

	// ��Ŀ 1����
	if (type1 == NPC_AI_TANKER)			return -1;
	if (type2 == NPC_AI_TANKER)			return 1;
	// ����Ÿ�� 2����
	if (type1 == typeb)					return -1;
	if (type2 == typeb)					return 1;
	// �׿� Ÿ���� ���� ����
	return 0;
}

// of�� df�� ���̸� PK���� �˻�
bool IsPK(CPC* of, CCharacter* df)
{
	if (of == NULL || df == NULL) return false;

#ifdef MAL_DISABLE_PKPENALTY
	if( gserver->m_bDisablePKPaenalty )
		return false;
#endif // MAL_DISALBE_PKPENALTY
	if (df->m_pZone->m_index == 47)
		return false;
#ifdef FREE_PK_SYSTEM
	if( gserver->m_bFreePk )
		return false;
#endif // FREE_PK_SYSTEM

	bool bPvP = false;
	CPC* dpc = NULL;
	switch (df->m_type)
	{
	case MSG_CHAR_PC:
		dpc = TO_PC(df);
		bPvP = true;
		break;
	case MSG_CHAR_PET:
		dpc = TO_PET(df)->GetOwner();
		break;
	case MSG_CHAR_ELEMENTAL:
		dpc = TO_ELEMENTAL(df)->GetOwner();
		break;
	case MSG_CHAR_APET:
		dpc = TO_APET(df)->GetOwner();
		break;
	case MSG_CHAR_NPC:
		dpc = TO_NPC(df)->GetOwner();
		break;
	default:
		return false;
	}

	if (dpc == NULL)
		return false;

	// �⺻������ �״°� �г�Ƽ�� ������, ���Ƽ �ִ°� Ʈ��
	// �������� pk��� �̰ų� ī���� �Ѵ� Ʈ��
	// �������� ���� ����Ʈ�� �ְ� ī���� �ƴϰ� �����ڵ� ī���� �ƴϸ� ī������ ��ġ�� ������� �ʴ´�
	// pk �г�Ƽ�� �ִ°� �Ӹ� �ƴ϶� ����ȸ������ ����ǹǷ� ���� ȸ���̳� �г�Ƽ�� ����Ϳ��� �ɸ��� true

	// of�� ������� ����Ʈ�� dpc�� �ִ°� : ������� - ����Ʈ���� ������ Point ���Ƽ ����
	CRaChar* raList = of->m_raList;
	while (raList)
	{
		if (raList->m_raTarget == dpc)
		{
			// ī���� �Ϲ��� ��������� ���϶� �г�Ƽ�� ���� of
			// �Ϲ��� ī���� ��������� ���϶� �г�Ƽ �� ���� ����� ���� dpc
			// �Ѵ� �Ϲ��̰� �������� ���������� m_bAttacker
			if (raList->m_bAttacker && !dpc->IsChaotic())
				return false;

			break;
		}
		raList = raList->m_next;
	}

#ifdef LC_TLD
	// �Ѵ� ī���� �ƴϰ� ĮŰ�� ������ �±��� ���� ��ġ ��ȭ����
	if( dpc->IsSetPlayerState(PLAYER_STATE_PKMODE) && of->IsSetPlayerState(PLAYER_STATE_PKMODE) && !of->IsChaotic() && !dpc->IsChaotic() )
		return false;
#endif

	// �����
	if (of->m_guildInfo && (of->m_guildInfo->guild()->battleState() == GUILD_BATTLE_STATE_ING) &&
			dpc->m_guildInfo && (dpc->m_guildInfo->guild()->battleState() == GUILD_BATTLE_STATE_ING))
	{
		if (of->m_guildInfo->guild()->battleIndex() == dpc->m_guildInfo->guild()->index() &&
				dpc->m_guildInfo->guild()->battleIndex() == of->m_guildInfo->guild()->index())
			return false;
	}

	// ���� ���� ����� �г�Ƽ ����
	CWarCastle* castle = CWarCastle::GetCastleObject(of->m_pZone->m_index);
	if (castle)
	{
		if (castle->GetState() != WCSF_NORMAL)
		{
			if ( (of->GetMapAttr() & MATT_WAR || of->m_pZone->IsWarZone((int)of->m_pos.m_x, (int)of->m_pos.m_z)) &&
					(df->GetMapAttr() & MATT_WAR || df->m_pZone->IsWarZone((int)df->m_pos.m_x, (int)df->m_pos.m_z)) &&
					(of->GetJoinFlag(of->m_pZone->m_index) != WCJF_NONE ))
				return false;
		}
	}
//#endif

	/////////////////////////////////////////////
	// BANGWALL : 2005-07-18 ���� 11:27:24
	// Comment : freepkzone �г�Ƽ ����
	// �����ڿ� ����ڰ� ��� freepkzone�� ������ pkpenalty ����

	
	if( of->GetMapAttr() == df->GetMapAttr() && of->GetMapAttr() & MATT_FREEPKZONE)
		return false;

	return true;
}
// npc attackList�� ���� ���� Pulse �ʰ��� ��� ���ø���Ʈ���� ����
// hate ��ġ ���� ���� pc ��ȯ
//
CCharacter* CheckAttackPulse(CNPC* npc)
{
	if (npc == NULL) return NULL;

	CAttackChar* target;
	CAttackChar* targetNext = npc->m_attackList;

	int hate = 0;
	CCharacter* retHate = NULL;
	int lowhp = 0x7fffffff;
	int lowhp_hate = 0;
	CCharacter* retLowHP = NULL;

	int checkPulse;

	while ((target = targetNext))
	{
		targetNext = targetNext->m_next;

		// �̳׶�, ���۹�, ������
		if (npc->m_proto->CheckFlag(NPC_MINERAL | NPC_CROPS | NPC_ENERGY))
			checkPulse = NPC_PRODUCE_DELETE_PULSE;
		// �׿� ��Ÿ NPC
		else
			checkPulse = NPC_ATTACK_DELETE_PULSE;

		// Ÿ���� ���� �������� �ְ� Pulse�� �ʰ��� ��� ����Ʈ���� ����
		if (target->m_damage > 0 && gserver->m_pulse - target->m_targetPulse > checkPulse)
		{
			// target�� attackList���� npc ����
			CAttackChar* tmp;
			CAttackChar* tmpNext = target->ch->m_attackList;
			while ((tmp = tmpNext))
			{
				tmpNext = tmpNext->m_next;

				if (tmp->ch == npc)
				{
					REMOVE_FROM_BILIST(tmp, target->ch->m_attackList, m_prev, m_next);
					delete tmp;
					tmp = NULL;
				}
			}

			REMOVE_FROM_BILIST(target, npc->m_attackList, m_prev, m_next);
			delete target;
			target = NULL;
			continue;
		}

		// 050315 : bs : Ÿ�� ���� ������ ��ŵ
		if (!target)
			continue ;
		if (!npc->CanVisible(target->ch))
			continue ;

		if ((target->ch->m_assist.m_state & AST_FAKEDEATH))
			continue ;

		// �þ߹����ȿ� ������ Ÿ���� �� �� ����.
		if (!CheckInNearCellExt(npc, target->ch))
			continue ;

		// ���� �ٸ��� ���̰� 5���� �̻��̸� ����
		if (ABS(GET_YLAYER(npc) - GET_YLAYER(target->ch)) > 1 && ABS(GET_H(npc) - GET_H(target->ch)) > 5.0f)
			continue ;

		// �ǽ��� �ȿ����� Ÿ���� �� �� ����
		if (target->ch->IsInPeaceZone(false))
			continue ;

		if (hate <= target->m_targetHate && target->m_targetHate != 0)
		{
			hate = target->m_targetHate;
			retHate = target->ch;
		}
		if (lowhp > target->ch->m_hp && target->m_targetHate != 0)
		{
			lowhp = target->ch->m_hp;
			lowhp_hate = target->m_targetHate;
			retLowHP = target->ch;
		}
	}

	switch (npc->m_proto->m_aitype)
	{
	case NPC_AI_TANKER:
		// �ڽ��� ü���� 20% �̸��̸� hate ���� ������κ��� ���� : flag 2
		if ( npc->m_proto->CheckAIBit(2) && npc->m_hp < npc->m_maxHP * 20 / 100 )
			return retHate;

		// �ǰ� ���� ���� ����� �ִ� hate�� ���� ����� hate ���� �̻��̸� �� ���� �༮�� ���� : flag 0
		if ( npc->m_proto->CheckAIBit(0) && hate  / 2 < lowhp_hate )
		{
			// ü���� ���� ���� �Ÿ��� 10���� �̻� ���̳��� hate ���� ����� ���� : flag 1
			if ( npc->m_proto->CheckAIBit(1) && GetDistance(retLowHP, npc) >= 10.0f )
				return retHate;

			// ü�� ���� ���� hate ���� ���� HP�� ������ hate ���� ��
			if (retHate && retLowHP && retHate->m_hp == retLowHP->m_hp)
				return retHate;

			return retLowHP;
		}

		return retHate;

	case NPC_AI_NORMAL:
	case NPC_AI_DAMAGEDEALER:
	case NPC_AI_HEALER:
	default:
		return retHate;
	}
}

int CalcNewDamage(CCharacter* of, CCharacter* df, int damage)
{
	if( IS_PC(of) && IS_PC(df) )
	{
		CPC* of_pc = TO_PC(of);
		CPC* df_pc = TO_PC(df);

		if(of_pc->IsChaotic() || df_pc->IsChaotic())
		{
			//������ ó��
			if(of_pc->IsChaotic() == true)
			{
				damage = damage - (damage * of_pc->m_pkPenalty / 1000 / 100 * (-1.5));
			}
			else
			{
				damage = damage + (damage * of_pc->m_pkPenalty / 1000 / 100 * 3.5);
			}
		}

		//����ȭ�� ���� ����
		{
			damage = damage - (df_pc->m_wearInventory.getWearItemPlusSumCount() * damage / (df_pc->m_wearInventory.getWearItemPlusSumCount() + 310));
		}
	}
	
	return damage;
}

void CalcNewHitProb(CCharacter* of, CCharacter* df, float& hit, float& avoid)
{
	if( IS_PC(of) && IS_PC(df) )
	{
		CPC* of_pc = TO_PC(of);
		CPC* df_pc = TO_PC(df);

		//���⿡ ���� ���߷� ���
		CItem* item_weapon = of_pc->m_wearInventory.getWearItem(WEARING_WEAPON);
		if(item_weapon != NULL)
		{
			hit = hit + ( item_weapon->getPlus() * ( (of_pc->m_level + 900) / df_pc->m_level ) );
		}

		//ī�� ��� �� ����� PVP ȸ�� ����
		if(df_pc->IsChaotic() == true)
		{
			avoid = avoid + ((df_pc->m_pkPenalty / (of_pc->m_level + df_pc->m_level)) - of_pc->m_level * 3);
		}
	}
}
bool checkPvPProtect( CPC* pc, CCharacter* tch )
{
	CPC* tpc = NULL;
	if(IS_PC(tch))
		tpc = TO_PC(tch);
	else if(IS_APET(tch))
		tpc = TO_APET(tch)->GetOwner();
	else if(IS_PET(tch))
		tpc = TO_PET(tch)->GetOwner();
	else if(IS_ELEMENTAL(tch))
		tpc = TO_ELEMENTAL(tch)->GetOwner();
	else if(IS_NPC(tch))
		tpc = TO_NPC(tch)->GetOwner();

	if(tpc == NULL)
		return true;

	if(tpc == pc)
		return true;

	if(tpc->m_assist.FindBySkillIndex(PVP_PROTECT_SKILL_INDEX) != 0)
	{
		//�������� ��쿡
		if(tpc->GetJoinFlag(tpc->m_pZone->m_index) != 0)
		{
			if ( tpc->GetMapAttr() & MATT_WAR || tpc->m_pZone->IsWarZone(GET_X(tpc), GET_Z(tpc)) == true ) 
			{
				return true;
			}
			else
			{
				//�̿ܿ��� ���� �Ұ�
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg(rmsg, MSG_SYS_DO_NOT_ATTACK_PROTECT_PVP);
				SEND_Q(rmsg, pc->m_desc);
				return false;
			}
		}
		else
		{
			switch(tpc->m_pArea->m_zone->m_index)
			{
			case ZONE_AKAN_TEMPLE:
			case ZONE_EGEHA_PK:
			case ZONE_PK_TOURNAMENT:
			case ZONE_EXTREME_CUBE:
			case ZONE_ROYAL_RUMBLE:
			case ZONE_RVR:
			case ZONE_ENCHANTED_DUNGEON: 
				break;
			default:
				// ���� �Ұ�
				if ( !(tpc->GetMapAttr() & MATT_FREEPKZONE) )
				{
					//�Ʒ����� ���������� ���� �Ұ�
					CNetMsg::SP rmsg(new CNetMsg);
					SysMsg(rmsg, MSG_SYS_DO_NOT_ATTACK_PROTECT_PVP);
					SEND_Q(rmsg, pc->m_desc);
					return false;
				}
				break;
			}
		}
	}
	return true;
}
