#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "Server.h"
#include "CmdMsg.h"
#include "Battle.h"
#include "DratanCastle.h"
#include "../ShareLib/packetType/ptype_old_do_attack.h"

// �ɸ� ����
void do_pd_Attack(CPC* pc, CNetMsg::SP& msg)
{
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	pCastle->CheckRespond(pc);

	RequestClient::doPDAttack* packet = reinterpret_cast<RequestClient::doPDAttack*>(msg->m_buf);

	if (packet->multicount > 20)
	{
		LOG_ERROR("HACKING : invalid multi count[%d]. charIndex[%d]", packet->multicount, pc->m_index);
		pc->m_desc->Close("invalid multi count");
		return;
	}

	// multi target�� �ߺ� �˻�
	if (packet->multicount > 1)
	{
		std::set<int> tset;
		for (int i = 0; i < packet->multicount; ++i)
		{
			if (tset.insert(packet->list[i].index).second == false)
			{
				LOG_ERROR("HACKING : duplicate multi target[%d]. charIndex[%d]", packet->list[i].index, pc->m_index);
				pc->m_desc->Close("duplicate multi target");
				return;
			}
		}
	}

	// ��� �˻� : ���� ��������
	CArea* area = pc->m_pArea;
	if (area == NULL)
	{
		LOG_ERROR("HACKING : not found area. charIndex[%d]", pc->m_index);
		pc->m_desc->Close("not found area");
		return;
	}

	CCharacter* tch = area->FindCharInCell(pc, packet->tIndex, (MSG_CHAR_TYPE)packet->tCharType);
	if (tch == NULL)
		return;

	int preIndex = -1;
	for (int i = 0; i < packet->multicount; ++i)
	{
		if(preIndex == packet->list[i].index)
		{
			// ����� ������
			int nearZone;
			int nearZonePos;
			CZone* pZone = gserver->FindNearestZone(pc->m_pZone->m_index, GET_X(pc), GET_Z(pc), &nearZone, &nearZonePos);
			if (pZone == NULL)
				return;

			GoZone(pc, nearZone,
				   pZone->m_zonePos[nearZonePos][0],															// ylayer
				   GetRandom(pZone->m_zonePos[nearZonePos][1], pZone->m_zonePos[nearZonePos][3]) / 2.0f,		// x
				   GetRandom(pZone->m_zonePos[nearZonePos][2], pZone->m_zonePos[nearZonePos][4]) / 2.0f);		// z

			return;
		}

		preIndex = packet->list[i].index;

		CCharacter* ch = area->FindCharInCell(pc, packet->list[i].index, (MSG_CHAR_TYPE) MSG_CHAR_NPC);

		if(!ch) continue;

		if( !IS_NPC(ch) )
		{
			CPC* bugPC = NULL;
			if( IS_ELEMENTAL(ch) )
			{
				CElemental *ele = TO_ELEMENTAL(ch);
				bugPC = ele->GetOwner();
			}
			if( IS_PET(ch) )
			{
				CPet* pet = TO_PET(ch);
				bugPC = pet->GetOwner();
			}

			if( IS_PC(ch) )
			{
				bugPC = TO_PC(ch);
			}

			if( !bugPC )
				return;

			// ����� ������
			int nearZone;
			int nearZonePos;
			CZone* pZone = gserver->FindNearestZone(bugPC->m_pZone->m_index, GET_X(bugPC), GET_Z(bugPC), &nearZone, &nearZonePos);
			if (pZone == NULL)
				return;

			GoZone(bugPC, nearZone,
				   pZone->m_zonePos[nearZonePos][0],															// ylayer
				   GetRandom(pZone->m_zonePos[nearZonePos][1], pZone->m_zonePos[nearZonePos][3]) / 2.0f,		// x
				   GetRandom(pZone->m_zonePos[nearZonePos][2], pZone->m_zonePos[nearZonePos][4]) / 2.0f);		// z

			GAMELOG << init("PD_BUG", bugPC)
					<< end;
			return;
		}

		int ret = ProcAttack(ch, tch, ch->GetAttackType(NULL), NULL, 0);
		if (ret == -1)
			return ;
	}
}

void do_Attack(CPC* pc, CNetMsg::SP& msg)
{
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	pCastle->CheckRespond(pc);

	RequestClient::doAttack* packet = reinterpret_cast<RequestClient::doAttack*>(msg->m_buf);

	// ���� ������ �ִ� 5
	if (packet->multicount > 5)
	{
		LOG_ERROR("HACKING : invalid multi count[%d]. charIndex[%d]", packet->multicount, pc->m_index);
		pc->m_desc->Close("invalid multi count");
		return;
	}

	// multi target�� �ߺ� �˻�
	if (packet->multicount > 1)
	{
		std::set<int> tset;
		for (int i = 0; i < packet->multicount; ++i)
		{
			if (tset.insert(packet->list[i].index).second == false)
			{
				LOG_ERROR("HACKING : duplicate multi target[%d]. charIndex[%d]", packet->list[i].index, pc->m_index);
				pc->m_desc->Close("duplicate multi target");
				return;
			}
		}
	}

	// ��� �˻� : ���� ��������
	CArea* area = pc->m_pArea;
	if (area == NULL)
		return;

	CCharacter* ch = area->FindCharInCell(pc, packet->aIndex, (MSG_CHAR_TYPE)packet->aCharType);
	if (ch == NULL)
		return;

	CCharacter* tch = area->FindCharInCell(ch, packet->tIndex, (MSG_CHAR_TYPE)packet->tCharType);
	if (tch == NULL)
		return;

	// �����ڰ� PC�̸� �ڽ��� ĳ���� ����
	if (IS_PC(ch) && ch != pc)
		return ;

	switch (ch->m_type)
	{
	case MSG_CHAR_PC:
		{
			if( IS_NPC(tch))
			{
				CPC * pPC = TO_PC(ch);
				CNPC * pNPC = TO_NPC(tch);
				if( pPC->GetSummonNpc(SUMMON_NPC_TYPE_MERCENARY) == pNPC )
					return;
			}

			//pvp��ȣ ������ üũ
			if (checkPvPProtect(pc, tch) == false)
				return;

			// ���� �Ÿ� �˻�
			if (GetDistance(ch, tch) > ch->m_attackRange * 2)
				return ;

			// ���� �˻�
			if ( ch->ChekAttackType() && ch->CheckHackAttack(pc))
				return ;

			// �� Ÿ�� ������ �Ұ���
			if (pc->GetPet() && pc->GetPet()->IsMount())
				return ;

			// ���� ������ ����� �ش� ��ų �ߵ�
			int mixSkillIndex[] = { pc->m_opSturnIndex, pc->m_opBloodIndex, pc->m_opPoisonIndex, pc->m_opSlowIndex, pc->m_opMoveIndex };
			int mixSkillLevel[] = { pc->m_opSturnLevel, pc->m_opBloodLevel, pc->m_opPoisonLevel, pc->m_opSlowLevel, pc->m_opMoveLevel };
			CSkill* skillMixItem = NULL;
			int i;
			int bStop = 0;
			for (i = 0; i < 5; i++)
			{
				if (mixSkillIndex[i] > 0 && mixSkillLevel[i] > 0)
				{
					skillMixItem = gserver->m_skillProtoList.Create(mixSkillIndex[i], mixSkillLevel[i]);
					if (skillMixItem)
					{
						bool bApply;
						bStop = ApplySkill(ch, tch, skillMixItem, -1, bApply);
					}
					delete skillMixItem;
					skillMixItem = NULL;
					if (bStop != 0)
						return ;
				}
			}

			if (IS_PC(ch))
			{
				CPC* pPCAttacker = TO_PC(ch);
				CItem* weaponItem = pPCAttacker->m_wearInventory.wearItemInfo[WEARING_WEAPON];

				// ���� ����
				if (pPCAttacker->m_opAttackBlind > 0)
				{
					CSkill* pSkillBlind = gserver->m_skillProtoList.Create(415, pPCAttacker->m_opAttackBlind);
					int nRetApplySkill = 0;
					if (pSkillBlind)
					{
						bool bApply;
						nRetApplySkill = ApplySkill(ch, tch, pSkillBlind, -1, bApply);
					}
					delete pSkillBlind;
					pSkillBlind = NULL;
					if (nRetApplySkill != 0)
						return ;
				}

				// �� ����
				if (pPCAttacker->m_opAttackPoison > 0)
				{
					CSkill* pSkillPoison = gserver->m_skillProtoList.Create(414, pPCAttacker->m_opAttackPoison);
					int nRetApplySkill = 0;
					if (pSkillPoison)
					{
						bool bApply;
						nRetApplySkill = ApplySkill(ch, tch, pSkillPoison, -1, bApply);
					}
					delete pSkillPoison;
					pSkillPoison = NULL;
					if (nRetApplySkill != 0)
						return ;
				}
			}
		} // PC �˻�

		break;

	case MSG_CHAR_PET:
	case MSG_CHAR_ELEMENTAL:
		// TODO : ��ȯ�� ���� �˻�
		// ���� �Ÿ� �˻�
		if (GetDistance(ch, tch) > ch->m_attackRange * 2)
			return ;

		// ���� �˻�
		if (ch->CheckHackAttack(pc))
			return ;

		break;

	default:
		break;
	}

	if(IS_PC(tch))
	{
		if( TO_PC(tch)->m_bImmortal == true )
			return;
	}

	if (DEAD(ch) || !ch->CanAttack() || pc->IsDisable())	return ;
	// ���ɸ� ����� ���� ���Ѵ�.
	if ( tch->m_assist.m_state & AST_FREEZE )	return;
	//���� ���� ����� ������ �� ����.
	if ( tch->m_assist.m_state & AST_SAFEGUARD )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_DO_NOT_ATTACK_IMMOTAL);
		SEND_Q(rmsg, pc->m_desc);
		return;
	}


	// ����� NPC�϶��� ��Ƽ ����
	if (!IS_NPC(tch))
		packet->multicount = 0;

	// �ּ��� ���� 1ȸ �̻�
	bool bAttacked = false;
	bool bAttackedPet = false;		// �ֿϵ����� NPC���� ���� �˻�

	// ��Ƽ ���� �˻��
	std::set<int> listMultiTarget;

	while (tch)
	{
		bool bBlocked = false;

		// NPC�� ������ ������ �Ӽ��� �˻� (����PK ������ �ƴҶ���)
		if ( IS_NPC(tch) && !(tch->GetMapAttr() & MATT_FREEPKZONE) )
		{
			char tempy = GET_YLAYER(ch);
			bBlocked = (!area->IsNotBlocked(ch, tch, true, tempy));
		}

		int ret = 0;
		if (!bBlocked)
		{
			if (IS_PC(ch) && ch->IsEnemy(tch))
			{
				bAttacked = true;
#ifdef MONSTER_AI
				if (tch != NULL	&& IS_NPC(tch))
				{
					CNPC * pTemp = TO_NPC(tch);
					if (pTemp != NULL)
					{
						if (ch->m_level - tch->m_level <= 5 && pTemp->m_proto->m_index != 303 /*�Ǹ��� ����*/)
						{
							bAttackedPet = true;
						}

						if (pTemp->m_bMoveLock || pTemp->m_bMoveToRegen)
						{
							pTemp->m_bMoveToRegen = false;
							pTemp->m_bMoveLock = false;
							pTemp->m_pulseMoveLock = 0;
							pTemp->m_postregendelay = 0;
						}
					}
				}
#else
				if (tch != NULL	&& IS_NPC(tch) && ch->m_level - tch->m_level <= 5)
				{
					CNPC * pTemp = TO_NPC(tch);
					if (pTemp != NULL && pTemp->m_proto->m_index != 303 /*�Ǹ��� ����*/)
					{
						bAttackedPet = true;
					}
				}
#endif
			}

			listMultiTarget.insert(tch->m_index);
			ret = ProcAttack(ch, tch, ch->GetAttackType(NULL), NULL, 0);
		}

		if (ret == -1 || tch->m_index == -1) // ProcAttack()�ȿ��� Character ��ü�� �Ҹ�� ��쵵 ����
		{
			tch = NULL;
			continue ;
		}

		//���� �ߵ��� ��ų �߰�
		if( pc->m_optionAttSkillList.count() > 0 )
		{
			//���� �� �ÿ� ������ ��ų ����
			void* pos = pc->m_optionAttSkillList.GetHeadPosition();
			bool bApply = false;
			while (pos)
			{
				CSkill* skill = pc->m_passiveSkillList.GetNext(pos);
				if (skill && skill->m_proto)
				{
					int rand = GetRandom(1, 10000);
					if( rand < skill->m_optionSkillProb )
					{
						ApplySkill(ch, tch, skill, -1, bApply);
						if(bApply == false)
						{
							GAMELOG << init("EVENT_PCBANG_2NDS SKILL FAILED (LOGIN) ", pc ) << end;// ��ų ���� ����
						}
					}
				}
			}
		}

		if (area->m_zone->IsPersonalDungeon() == false)
		{
			tch = NULL;
			continue;
		}

		if (packet->multicount && !DEAD(ch))
		{
			int multitarget = packet->list[packet->multicount].index;
			--packet->multicount;

			tch = area->FindCharInCell(ch, multitarget, (MSG_CHAR_TYPE)packet->tCharType);
			if (tch == NULL)
			{
				continue;
			}

			if (GetDistance(ch, tch) > ch->m_attackRange * 2)
			{
				tch = NULL;
				continue;
			}

			std::set<int>::iterator it = listMultiTarget.find(tch->m_index);
			if (it != listMultiTarget.end())
			{
				GAMELOG << init("HACK ATTACK MULTI TARGET", pc)
						<< "ZONE" << delim
						<< pc->m_pZone->m_index << delim
						<< "TARGET" << delim
						<< packet->tCharType << delim
						<< multitarget
						<< end;

				if (pc->m_desc->IncreaseHackCount(1))
					return ;

				tch = NULL;
			}
		}
		else
		{
			tch = NULL;
			continue;
		}

		if (packet->multicount <= 0)
		{
			tch = NULL;
			continue;
		}
	} // end while

	if (bAttackedPet && !ch->IsInPeaceZone(true))
		pc->m_pulseLastAttackSkill = gserver->m_pulse;

#ifdef EVENT_SEARCHFRIEND_TIME
	// ���ݽ� �̺�Ʈ �ð� ���� �˻�
	if (gserver->m_bSearchFriendEvent && (pc->m_nEventSearchFriendListCount >= 1)
			&& (pc->m_bEventSearchFriendSelect == true) && (pc->m_nTimeEventSearchFriend <= 216000)
			&& bAttacked && !ch->IsInPeaceZone(true))
		pc->m_pulseEventSearchFriend = gserver->m_pulse;
#endif // #ifdef EVENT_SEARCHFRIEND_TIME
}
