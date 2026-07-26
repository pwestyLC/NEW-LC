#include <boost/scoped_array.hpp>
#include "stdhdrs.h"

#include "Log.h"
#include "Area.h"
#include "CmdMsg.h"
#include "Zone.h"
#include "Server.h"
#include "Env.h"
#include "../ShareLib/DBCmd.h"
#include "Battle.h"
#include "hardcoding.h"
#include "DratanCastle.h"
#include "../ShareLib/packetType/ptype_old_do_skill.h"
#include "../ShareLib/packetType/ptype_old_do_move.h"
#include "ExtremeCube.h"

// npc ȸ��
void MobRecover(CNPC* npc);

// npc ��ų ���, ���� npc ai ��ŵ�� �ʿ��ϸ� true
bool MobProcSkill(CNPC* npc);

//bool MobProcSkillMercenary(CNPC *npc);
bool MobProcSkillTotem_Buff(CNPC *npc);
bool MobProcSkillTrap_Attk(CNPC *npc);
bool MobProcSkillSuicide_Attk(CNPC *npc);
bool MobProcSkillItemTotem_Buff(CNPC *npc);
int GetSummonNpcMultiTarget(CNPC* npc, MultiTarget *multitarget, int mcount);

// npc �Ǿ� ó��, �Ǿ�� �������� npc�̸� true
bool MobProcFear(CNPC* npc, CCharacter* target);

////////////////////
// Function name	: MobMoveTo
// Description	    : npc�� x, z�� �̵�
// Return type		: float
//                  : ����������� ���� �Ÿ�
// Argument         : CNPC* npc
//                  : �̵��� NPC
// Argument         : float x
// Argument         : float z
//                  : �̵��� ��ġ
// Argument         : bool bRun
//                  : �پ �̵����� ����
// Argument         : bool bAttack
//                  : ������ ���� �̵����� ���� (x, z ��ǥ�� �Ӽ����� �˻����� �����ϴµ� ����)
// Argument         : CCharacter* target
//                  : target�� �̵����� �������� ����
float MobMoveTo(CNPC* npc, float x, float z, bool bRun, bool bAttack, CCharacter* target);

// npc�� ���� ��� ����
CCharacter* MobSelectTarget(CNPC* npc);

CCharacter* MobSelectTarget_Taming_or_Confused(CNPC* npc);

// npc ���� �̵�
void MobMoveRandom(CNPC* npc);

// npc ��ų ����
CCharacter* MobSelectSkill(CNPC* npc, CCharacter* target);

// npc ��ų ����, ���� ������ true
bool MobReadySkill(CNPC* npc, CCharacter* target);

/////////////////////////////////////////////////////////////////
// �� �ൿ ��ƾ
void CArea::MobActivity()
{
	CNPC* npc = NULL;
	CNPC* tnpc = m_npcList;

	CCharacter* target = NULL;

	while ((npc = tnpc))
	{
		//�ϵ��ھ� ������ ��� activity �Լ��ȿ��� area�� false�� �� �� ����
		if(this->m_bEnable == false)
			return;

		if(npc->m_proto == NULL)
		{
			tnpc = npc->m_pNPCNext;
			continue;
		}

		tnpc = npc->m_pNPCNext;

		if(tnpc != NULL && tnpc->m_pZone != NULL && this->m_zone->m_index != tnpc->m_pZone->m_index)
			return;

		if( npc->Check_MobFlag(STATE_MONSTER_MERCENARY)
				|| npc->Check_MobFlag(STATE_MONSTER_TOTEM_BUFF)
				|| npc->Check_MobFlag(STATE_MONSTER_TOTEM_ATTK)
				|| npc->Check_MobFlag(STATE_MONSTER_TRAP)
				|| npc->Check_MobFlag(STATE_MONSTER_SUICIDE) )
		{
			// �̳ѵ��� �ٷλ����� �ƴ�
			if( npc->m_hp == 0 )
				continue;

			// ���ʰ� ������ ������ ����
			if( !npc->GetOwner() )
			{
				npc->m_hp = 0;
				npc->m_pArea->m_nNPC_Killed_NPC ++;
			}
		}

		if( npc->m_hp == 0 )
			continue;

		npc = MobTimeCheck(npc);

		target = NULL;

		if (npc == NULL )
			continue ;

		if(npc->m_proto->CheckFlag(NPC_CASTLE_GUARD)
				&& npc->m_regenInfo
				&& m_zone->m_index == ZONE_DRATAN)
		{
			// ���ź ��ȣ���� ��� ������ �ð��� �ƴ� ��  �������� ����
			CDratanCastle * pCastle = CDratanCastle::CreateInstance();
			if( pCastle->GetState() == WCSF_NORMAL)
			{
				continue;
			}
		}

#ifdef SYSTEM_TREASURE_MAP
		if( npc->m_idNum == TREASURE_BOX_NPC_INDEX
				&& npc->m_regenTime + TREASURE_BOX_NPC_REGEN < gserver->getNowSecond() )
		{
			//npc->m_pZone->RemoveTreasureBoxNpc(npc);
			npc->SendDisappearAllInCell( false );
			DelAttackList( npc );
			CharFromCell( npc, true );
			DelNPC( npc );
			npc = NULL;
			continue;
		}
#endif

		if( npc->m_proto->m_index == 314 )
		{
			if( npc->m_regenTime + PANDOR_REGEN_TIME <= gserver->m_pulse )
			{
				if(npc->m_regenInfo)
				{
					npc->m_regenInfo->m_lastDieTime = gserver->m_pulse - npc->m_regenTime;
					npc->SendDisappearAllInCell( false );

					DelAttackList( npc );

					CharFromCell( npc, true );
					DelNPC( npc );
					npc = NULL;
					continue;
				}
			}
		}

		if (npc->m_proto->CheckFlag(NPC_RAID) && npc->m_regenInfo)
		{
			if (npc->m_nRaidMoveTime <= gserver->m_pulse)
			{
				CNPCRegenInfo* pRegeninfo = npc->m_regenInfo;
				npc->SendDisappearAllInCell(false);
				DelAttackList(npc);
				CharFromCell(npc, true);
				DelNPC(npc);
				pRegeninfo->m_lastDieTime = gserver->m_pulse - pRegeninfo->m_regenSec;
				pRegeninfo->m_bRaidMoveRandom = true;
				npc = NULL;
				continue ;
			}
		}

		// NPC ȸ��
		MobRecover(npc);

		if (gserver->m_pulse - npc->m_aipulse < npc->m_delay)
			continue ;

		static const int		nIndexWarrior		= 310;					// ������ �ձ�
		static const int		nIndexGuard			= 311;					// ��ȣ�� �ձ�
		static const int		nIndexBrave			= 312;					// ����� �ձ�
		static const int		nIndexProtect		= 313;					// ��ȣ�� �ձ�

		switch (npc->m_idNum)
		{
		case nIndexWarrior:
		case nIndexGuard:
		case nIndexBrave:
		case nIndexProtect:
			DropBlessWarrior(npc);
			npc = NULL;
			break;
		default:
			break;
		}

		if (npc == NULL)
			continue ;

        // ����, ���̵�, ���ݼ���, ����Ʈ, ��ų������, Ư����ų������, ���˺�, �̺�Ʈ NPC, ���� ����
        // Allow scripted-movement NPCs to proceed even if proto has SHOPPER flag

   

        // Skip certain special-proto NPCs that should not run normal AI unless they are under scripted movement.
        // Allow `NPC_SHOPPER` to move normally (shops should be able to walk) so exclude it from the mask.
        if (npc->m_proto->CheckFlag(NPC_ZONEMOVER | NPC_REFINER | NPC_QUEST | NPC_REMISSION | NPC_EVENT | NPC_LORD_SYMBOL)
                && !npc->m_bScriptedMovement)
        {
            // Skip non-scripted special-proto NPCs (ZONEMOVER, REFINER, etc.) without verbose logging to avoid spam
            continue ;
        }

		// ��ų ó��
		if( npc->Check_MobFlag(STATE_MONSTER_TOTEM_BUFF) )
		{
			if( MobProcSkillTotem_Buff(npc) )
				continue;
		}
		else if( npc->Check_MobFlag(STATE_MONSTER_TRAP) )
		{
			MobProcSkillTrap_Attk(npc);
			continue;
		}
		else if( npc->Check_MobFlag(STATE_MONSTER_SUICIDE) )
		{
			if( MobProcSkillSuicide_Attk(npc) )
				continue;
		}
		else if( npc->Check_MobFlag(STATE_MONSTER_TOTEM_ITEM_BUFF) )
		{
			if( MobProcSkillTotem_Buff(npc) )
				continue;
		}
		else if (MobProcSkill(npc))
			continue;

		// ��ų ó�� ���Ŀ� ��ų�� SKILL_CON_NORMAL�̸� ��ų ����� ���� �̵��ϵ��� ��
		if (npc->m_currentSkill && npc->m_currentSkill->m_state == SKILL_CON_NORMAL)
		{
			// ��ų�� Ÿ���� ã�´�
			target = npc->m_pArea->FindCharInCell(npc, npc->m_currentSkill->m_targetIndex, npc->m_currentSkill->m_targetType, false);
			if ( target == NULL || target == npc || (!npc->CanMove() && GetDistance((CCharacter*)npc, target) > npc->m_currentSkill->m_proto->GetFireRange(npc) + 1.0f) )
			{
				npc->m_currentSkill->m_usetime = 0;
				npc->m_currentSkill = NULL;
			}
		}

		// 1��
		npc->m_aipulse = gserver->m_pulse;
		npc->m_delay = NPC_ACTIVITY_DELAY;

		// ���������� ó��
		if ( npc->Check_MobFlag( STATE_MONSTER_TAMING ) )
		{
			// npc�� ���ֿ̹� �ɸ��� �ʾ����� ���÷��׵� ������Ų��.
//			if(npc->m_assist.FindByType(MT_ASSIST, MST_ASSIST_TAMING) <= 0)
//				npc->reSet_MobFlag(STATE_MONSTER_TAMING);
//			else
			MobActivity_Taming(npc);
			continue;
		}

		else if ( npc->Check_MobFlag( STATE_MONSTER_CONFUSION ) )
		{
			// npc�� ȥ���� �ɸ��� �ʾ����� ���÷��׵� ������Ų��.
			if(npc->m_assist.FindByType(MT_ASSIST, MST_ASSIST_CONFUSED) <= 0)
				npc->reSet_MobFlag(STATE_MONSTER_CONFUSION);
			else
				MobActivity_Confused(npc);
			continue;
		}


#ifndef BUGFIX_MERCENARY_GETOWNER_NULL_SERVERDOWN // �Ʒ����� ó���ϴ� ��ƾ�� ���� �����ϴ� ���� ������.
		if ( npc->Check_MobFlag( STATE_MONSTER_MERCENARY ) )
		{
			MobActivity_Mercenary(npc);
			continue;
		}
#endif

		if( npc->GetOwner() )
		{
			switch( npc->GetOwner()->GetSummonNpcType(npc) )
			{
			case SUMMON_NPC_TYPE_MERCENARY:
				MobActivity_Mercenary(npc);
				continue;
			case SUMMON_NPC_TYPE_TOTEM:
				MobActivity_Totem(npc);
				continue;
			case SUMMON_NPC_TYPE_BOMB_1:
			case SUMMON_NPC_TYPE_BOMB_2:
			case SUMMON_NPC_TYPE_BOMB_3:
				MobActivity_Suicide(npc);
				continue;
			case SUMMON_NPC_TYPE_TOTEM_ITEM:
				MobActivity_Item_Totem(npc);
				continue;
			}
		}
		// �Ǿ� ó��
		if (MobProcFear(npc, NULL))
			continue ;

		// Ÿ�� ����
		if (!target)
		{
			target = MobSelectTarget(npc);

			// ��Ŀ Ÿ�� �÷��� 2�̸� HP�� 20%�̸��϶� ����
			// ������ ���� Ÿ�� �÷��� 3�̸� HP�� 20% �̸��϶� ����
			if ( (npc->m_proto->m_aitype == NPC_AI_TANKER && npc->m_proto->CheckAIBit(2) && npc->m_hp < npc->m_maxHP * 20 / 100) ||
					(npc->m_proto->m_aitype == NPC_AI_DAMAGEDEALER && npc->m_proto->CheckAIBit(3) && npc->m_hp < npc->m_maxHP * 20 / 100) )
			{
				MobProcFear(npc, target);
				continue ;
			}

			// �� ��ų ����
			target = MobSelectSkill(npc, target);
		}
#ifdef MONSTER_AI
		if (!target && npc->m_bMoveToRegen)
		{
			if (npc->GetDistToRegen() <= 0.3f)
			{
				npc->m_bMoveToRegen = false;
				npc->m_bMoveLock = true;
				npc->m_postregendelay = gserver->m_pulse;
			}
			else
			{
				MobMoveTo(npc, npc->m_regenX, npc->m_regenZ, false, false, NULL);
			}

			continue;
		}

		if (npc->m_bMoveLock)
		{
			if (npc->m_postregendelay)
				continue;

			// Ÿ���� ���ų�, Ÿ���� �ִµ�, 1�е��� ���� ���¿��ٸ� �������.
			if (!target || (target && npc->m_pulseMoveLock != 0 && gserver->m_pulse >= npc->m_pulseMoveLock + PULSE_REAL_MIN))
			{
				npc->m_bMoveLock = false;
				npc->m_pulseMoveLock = 0;

				npc->m_hp = npc->m_maxHP;
				npc->m_mp = npc->m_maxMP;

				{
					CNetMsg::SP rmsg(new CNetMsg);
					CharStatusMsg(rmsg, npc, 0);
					npc->m_pArea->SendToCell(rmsg, npc, false);
				}

				npc->m_nBlockRegen = npc->m_index;
				MobMoveTo(npc, npc->m_regenX, npc->m_regenZ, false, false, NULL);

				continue;
			}
		}
#endif

		if(target && IS_PC(target))
		{
			CPC* pc = TO_PC(target);
			if(pc->m_bVisible == false)
			{
				DelAttackList(target);
				target = NULL;
			}
		}

		// Ÿ���� ������ ���� �̵�
		if (!target)
		{
			if ( !this->IsFreeze(gserver->m_pulse) )
				MobMoveRandom(npc);

			continue ;
		}

#ifdef RESTRICT_PVP_SKILL
		if (target && IS_PC(target))
		{
			CPC* pTargetPC = TO_PC(target);
			pTargetPC->m_nRestrictPvPSkillDelaySec = RESTRICT_PVP_SKILL;
		}
#endif // RESTRICT_PVP_SKILL

		// NPC�� ������ �ص� ���� ���¸� ����
		if (target && !IS_NPC(target))
			npc->m_nRaidMoveTime = gserver->m_pulse + GetRandom(PULSE_MONSTER_RAID_MOVE * 9 / 10, PULSE_MONSTER_RAID_MOVE * 11 / 10);

		if ( target && IS_NPC(target) )
		{
			CNPC* pNpc = TO_NPC(target);

			if(!pNpc)
				continue;

			if( target->m_index != npc->m_index )
			{
#ifdef ATTACK_LIST_BUG_FIX
				// �Ϲ� ���Ͱ� ȥ�� ���͸� ������ ���� ����
				if ( pNpc->Check_MobFlag( STATE_MONSTER_CONFUSION ) )
				{
					DelAttackList(target);
					continue ;
				}
#else //ATTACK_LIST_BUG_FIX
				// �Ϲ� ���Ͱ� �ٸ� �Ϲ� ���͸� ���󰡴� ���� ����
				// ���ø���Ʈ�� �߰��� �ǳ� ������ ���ϹǷ� ���� �ٴϰ� �� ���̾���
				if( !pNpc->Check_MobFlag( STATE_MONSTER_TAMING ) && !pNpc->Check_MobFlag( STATE_MONSTER_CONFUSION ) )
				{
					DelAttackList(target);
					continue ;
				}

				if( !pNpc->Check_MobFlag( STATE_MONSTER_MERCENARY ) && !pNpc->Check_MobFlag( STATE_MONSTER_CONFUSION ) )
				{
					DelAttackList(target);
					continue ;
				}

				// �Ϲ� ���Ͱ� ȥ�� ���͸� ������ ���� ����
				else if ( pNpc->Check_MobFlag( STATE_MONSTER_CONFUSION ) )
				{
					DelAttackList(target);
					continue ;
				}

				// �Ϲ� ���Ͱ� ȥ�� ���͸� ������ ���� ����
				else if ( pNpc->Check_MobFlag( STATE_MONSTER_TOTEM_BUFF ) )
				{
					DelAttackList(target);
					continue ;
				}

				// �Ϲ� ���Ͱ� ȥ�� ���͸� ������ ���� ����
				else if ( pNpc->Check_MobFlag( STATE_MONSTER_TOTEM_ATTK ) )
				{
					DelAttackList(target);

					continue ;
				}
#endif // ATTACK_LIST_BUG_FIX
			}
		}

		// Ÿ���� ������ Ÿ���� ���� �̵�
		if(target->m_pArea->m_zone->isRVRZone() &&
				target->getSyndicateType() == npc->getSyndicateType())
		{
			DelAttackList(target);
			continue;
		}

		float dist = MobMoveTo(npc, GET_X(target), GET_Z(target), true, true, target);
#if defined (LC_GAMIGO)
		char outY;
#endif // defined (LC_GAMIGO)

		if (dist <= 0.3f && npc->m_proto->CheckFlag(NPC_ATTACK) && npc->CanAttack()
#if defined (LC_GAMIGO)
				&& npc->m_pArea && npc->m_pArea->IsNotBlocked(npc, target, true, outY)
#endif // defined (LC_GAMIGO)
		   )
		{
			// ���� ó��
			// ����������� AI���ú��� �ʱ�ȭ
			npc->InitAIVar();

#ifdef MONSTER_AI
			npc->m_bMoveLock = false;
			npc->m_pulseMoveLock = 0;
#endif

			if (!npc->m_bStop)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeMoveMsg(rmsg, MSG_MOVE_STOP, npc);
				npc->m_bStop = true;
				SendToCell(rmsg, npc, false);
			}
			if (target)
			{
				// ��ȣž�� ��ų�� ��밡��
				if (!(npc->m_currentSkill == NULL && (npc->m_proto->CheckFlag(NPC_CASTLE_TOWER))))
				{
					if (!MobReadySkill(npc, target) && gserver->m_pulse - npc->m_pulseAttack >= npc->m_attackSpeed * 15 / 10 && npc->IsEnemy(target))
					{
						npc->m_pulseAttack = gserver->m_pulse;
						ProcAttack( (CCharacter *)npc, target, npc->GetAttackType(NULL), NULL, 0);

						{ //dethunter12
							CPC* pc = NULL;
							switch (target->m_type)
							{
								case MSG_CHAR_PC:
									pc = TO_PC(target);
									break;
								case MSG_CHAR_APET:
								{
									CAPet* apet = TO_APET(target);
									pc = apet ? apet->GetOwner() : NULL;
								}
								break;
								case MSG_CHAR_PET:
								{
									CPet* pet = TO_PET(target);
									pc = pet ? pet->GetOwner() : NULL;
								}
								break;
								case MSG_CHAR_ELEMENTAL:
								{
									CElemental* elemental = TO_ELEMENTAL(target);
									pc = elemental ? elemental->GetOwner() : NULL;
								}
								break;
								case MSG_CHAR_NPC:       
								case MSG_CHAR_UNKNOWN:   
								default:
									pc = NULL;
									break;
							}

							if (pc)
							{
								CNetMsg::SP rmsg(new CNetMsg);
								SendMobAggressiveStatus(rmsg, npc, true);
								SEND_Q(rmsg, pc->m_desc);

								PCManager::instance()->sendToAlliesInCell(rmsg, pc);
							}
						}
					}
				}
			}
		}
#ifdef MONSTER_AI
		// Ÿ���� ������, ������ �ȵ� ���
		else
		{
			if (npc->m_bMoveLock)
				continue;

			// ���� ��ġ�� ������ ������
			if (npc->m_nOldDist == dist)
			{
				npc->m_bMoveLock = true;
				npc->m_pulseMoveLock = gserver->m_pulse;
			}
			else
			{
				// ���� ��ġ�� 100M �̻� or Ÿ�ٰ��� �Ÿ��� 50M �̻�
				if (GetDistance((CCharacter*)npc, target) > 50.0f || npc->GetDistToRegen() > 100.0f)
				{
					npc->m_hp = npc->m_maxHP;
					npc->m_mp = npc->m_maxMP;
					//npc->m_walkSpeed += 5;

					{
						CNetMsg::SP rmsg(new CNetMsg);
						CharStatusMsg(rmsg, npc, 0);
						npc->m_pArea->SendToCell(rmsg, npc, false);
					}

					npc->m_bMoveToRegen = true;
					DelTargetFromAttackList(npc, target);
				}
			}
		}

		npc->m_nOldDist = dist;
#endif
	}
}

CNPC* CArea::MobTimeCheck(CNPC* npc)
{
	if (!npc)
		return NULL;

	if (DEAD(npc))
		return NULL;

	// TODO : �� ���¿� ���õ� �ð� �˻�

	npc->m_assist.DecreaseTime();

	// ���Ͱ� ��ȥ�� ���ѱ� �� ���� �ð��� ������ ��ȥ�� �ٽ� ����Ѵ�.
	if (npc->m_pulseSoulRecover != 0 && npc->m_pulseSoulRecover + PULSE_REAL_MIN < gserver->m_pulse)
	{
		npc->m_pulseSoulRecover = 0;
		npc->reSet_MobFlag(STATE_MONSTER_NO_SOUL);
	}

	// ���̸� return
	if (npc->m_disableTime <= 0)
	{
		// 050310 : bs : �������� �����ð� ����
		if (!npc->m_postregendelay)
		{
			return npc;
		}
		else if (gserver->m_pulse >= npc->m_postregendelay + PULSE_POST_REGEN_DELAY)
		{
			npc->m_postregendelay = 0;

#ifdef MONSTER_AI
			npc->m_bMoveLock = false;
#endif

			return npc;
		}
		// --- 050310 : bs : �������� �����ð� ����
	}

	// ���� �� �����̰� Ǯ���� ���� �޽����� ������
	else if (npc->m_disableTime <= time(0))
	{
		npc->m_disableTime = 0;
		{
			CNetMsg::SP rmsg(new CNetMsg);
			AppearMsg(rmsg, npc, true);
			SendToCell(rmsg, npc);
		}

		// 050310 : bs : �������� �����ð� ���� : ���� ���͸�
		if (npc->m_proto->CheckFlag(NPC_FIRSTATTACK))
			npc->m_postregendelay = gserver->m_pulse;
		else
			npc->m_postregendelay = 0;
		// --- 050310 : bs : �������� �����ð� ����

		return NULL;
	}

	return NULL;
}

void CArea::AddNPC(CNPC* npc)
{
	if (npc->m_idNum < 0)
		return;

	ADD_TO_BILIST(npc, m_npcList, m_pNPCPrev, m_pNPCNext);
	npc->m_pZone = m_zone;
	npc->m_pArea = this;
	m_nCountNPC++;

	if (npc->m_lifetime > 0)
	{
		CArea::m_lifetime_set.insert(npc);
	}
}

void CArea::DelNPC(CNPC* npc)
{
	if(npc == NULL)
		return;

	if (npc->m_pArea != this)
		return ;

	if (npc->m_bScriptedMovement && gserver)
	{
		gserver->RemoveMovementTasksForNPC(npc);
	}

	REMOVE_FROM_BILIST(npc, m_npcList, m_pNPCPrev, m_pNPCNext);

	if (npc->m_regenInfo)
	{
		npc->m_regenInfo->m_lastDieTime = gserver->m_pulse;
		npc->m_regenInfo->m_bAlive = false;
	}

#ifdef SYSTEM_TREASURE_MAP
	if( npc->m_pZone && npc->m_idNum == TREASURE_BOX_NPC_INDEX )
		npc->m_pZone->RemoveTreasureBoxNpc(npc);
#endif
	if (npc->m_lifetime > 0)
	{
		CArea::m_lifetime_set.erase(npc);
	}

#ifdef EXTREME_CUBE

	if(npc->m_bCubeRegen)
	{
		CCubeSpace* cube = gserver->m_extremeCube.GetExtremeCube(npc->m_pArea->m_index);
		if(cube)
		{
			cube->DelMob(npc);
		}
	}
#endif // EXTREME_CUBE


	npc->m_pZone = NULL;
	npc->m_pArea = NULL;
	npc->DeleteNPC();
	npc = NULL;

	m_nCountNPC--;
}

void CArea::MobRegen()
{
	bool bRegenRaid = false;

	for (size_t i = 0; i < m_npcRegenList.m_infoList.size(); ++i)
	{
		CNPCRegenInfo& p = m_npcRegenList.m_infoList[i];

		if (!p.m_bRegen || p.m_lastDieTime == 0)
			continue;

		CNPCProto* proto = gserver->m_npcProtoList.FindProto(p.m_npcIdx);
		if (!proto)
			continue;

#ifdef TLD_EVENT_SONG
		if ((p.m_npcIdx == 1622 || p.m_npcIdx == 1623) && !gserver->tld_event)
			continue;
#endif

		// Castle state check (manually create pointer to existing DratanCastle)
		if (m_zone->m_index == ZONE_DRATAN && proto->CheckFlag(NPC_CASTLE_GUARD))
		{
			CDratanCastle* castle = CDratanCastle::CreateInstance();
			if (castle && castle->GetState() == WCSF_NORMAL)
				continue;
		}

		// Adaptive regen timing based on NPC density
		int regenSec = p.m_regenSec;
		if (!proto->CheckFlag(NPC_BOSS | NPC_MBOSS | NPC_RAID) &&
			!(m_zone->m_index == ZONE_DRATAN && proto->CheckFlag(NPC_CASTLE_GUARD)))
		{
			int cx, cz;
			PointToCellNum(p.m_regenX, p.m_regenZ, &cx, &cz);

			if (cx >= 0 && cz >= 0 && cx < m_size[0] && cz < m_size[1])
			{
				int count1x1 = m_cell[cx][cz].m_nCountNPC;
				int regen1x1 = m_cell[cx][cz].m_nTotalRegen;
				int count3x3 = 0;
				int regen3x3 = 0;

				for (int dx = -1; dx <= 1; ++dx)
				{
					for (int dz = -1; dz <= 1; ++dz)
					{
						int nx = cx + dx;
						int nz = cz + dz;
						if (nx < 0 || nz < 0 || nx >= m_size[0] || nz >= m_size[1])
							continue;

						count3x3 += m_cell[nx][nz].m_nCountNPC;
						regen3x3 += m_cell[nx][nz].m_nTotalRegen;
					}
				}

				float adjust = 1.0f;
				if (regen3x3 > 0 && count3x3 <= regen3x3 / 2)
					adjust -= adjust / 3;
				if (regen1x1 > 0 && count1x1 <= regen1x1 / 2)
					adjust -= adjust / 2;

				int newSec = static_cast<int>(p.m_regenSec * adjust);
				if (p.m_regenSec > 100 && newSec < 100)
					newSec = 100;
				regenSec = newSec;
			}
		}

#ifdef TLD_EVENT_SONG
		if (p.m_npcIdx == 1622)
			regenSec = p.m_regenSec;
#endif

		if ((gserver->m_pulse - p.m_lastDieTime) < regenSec)
			continue;

		if (p.m_totalNum == 0 || (p.m_totalNum != -1 && p.m_numRegen >= p.m_totalNum))
			continue;

		CNPC* npc = gserver->m_npcProtoList.Create(p.m_npcIdx, &p);
		if (!npc)
		{
			p.m_totalNum = 0;
			continue;
		}

		if (!proto->CheckFlag(NPC_PEACEFUL))
		{
			unsigned short attr = GetAttr(p.m_regenY, p.m_regenX, p.m_regenZ);
			if (attr & MATT_UNWALKABLE || attr & MATT_PEACE)
			{
				delete npc;
				p.m_totalNum = 0;
				continue;
			}
		}

		// Set Position
		GET_X(npc) = p.m_regenX;
		GET_YLAYER(npc) = p.m_regenY;
		GET_Z(npc) = p.m_regenZ;
		GET_R(npc) = (proto->CheckFlag(NPC_ATTACK) && proto->m_index != 339)
			? GetRandom(0, static_cast<int>(PI_2 * 10000)) / 10000
			: p.m_regenR;

		npc->m_regenX = GET_X(npc);
		npc->m_regenY = GET_YLAYER(npc);
		npc->m_regenZ = GET_Z(npc);
		npc->m_regenTime = gserver->m_pulse;
		npc->m_disableTime = time(0) + 3;
		npc->m_recoverPulse = gserver->m_pulse;

		// Special logic for raid
		if (!bRegenRaid && p.m_npcIdx != 314 &&
			proto->CheckFlag(NPC_ATTACK) &&
			RaidMobRegen(GET_X(npc), GET_Z(npc), GET_R(npc), GET_YLAYER(npc)))
		{
			delete npc;
			p.m_lastDieTime = gserver->m_pulse;
			bRegenRaid = true;
			continue;
		}
		bRegenRaid = true;

		// Finalize
		npc->InitPointsToMax();
		p.m_bAlive = true;
		p.m_numRegen++;
		p.m_lastDieTime = 0;

		AddNPC(npc);

		int cx, cz;
		PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
		CharToCell(npc, GET_YLAYER(npc), cx, cz);

        // (scripted movement regen persistence disabled in this build)

		// Optional logging for bosses
		if (proto->CheckFlag(NPC_BOSS | NPC_MBOSS) && proto->IsBossInList())
		{
			GAMELOG << init("MOB REGEN")
				<< "INDEX" << delim << proto->m_index
				<< "NAME" << delim << npc->m_name
				<< "ZONE" << delim << m_zone->m_index
				<< "POSITION" << delim << GET_X(npc) << delim << GET_Z(npc) << delim << GET_YLAYER(npc)
				<< end;
		}
	}
}

bool CArea::RaidMobRegen(float x, float z, float r, char y)
{
	vec_raidnpcrregenlist_t::iterator it = m_raidNPCRegenList.begin();
	vec_raidnpcrregenlist_t::iterator endit = m_raidNPCRegenList.end();

	for (; it != endit; ++it)
	{
		CNPCRegenInfo* p = *it;
		if (!p)
			continue;

		
		if (p->m_lastDieTime == 0)
			continue;

		const int waitPulse = gserver->m_pulse - p->m_lastDieTime;

		// Not ready yet
		if (waitPulse < p->m_regenSec)
			continue;


		GAMELOG << init("RAID REGEN READY")
			<< "NPC_IDX" << delim << p->m_npcIdx
			<< "WAIT_PULSE" << delim << waitPulse
			<< "WAIT_SEC" << delim << (waitPulse / PASSES_PER_SEC)
			<< "REGEN_PULSE" << delim << p->m_regenSec
			<< "TOTALNUM" << delim << p->m_totalNum
			<< "NUMREGEN" << delim << p->m_numRegen
			<< end;

		if (p->m_totalNum == 0)
		{
			GAMELOG << init("RAID REGEN SKIP") << "NPC_IDX" << delim << p->m_npcIdx
				<< "REASON" << delim << "TOTALNUM=0" << end;
			continue;
		}

		if ((p->m_totalNum != -1) && (p->m_numRegen >= p->m_totalNum))
		{
			GAMELOG << init("RAID REGEN SKIP") << "NPC_IDX" << delim << p->m_npcIdx
				<< "REASON" << delim << "LIMIT" << end;
			continue;
		}

		int pub = GetRandom(1, 10000);
		if (!p->m_bRaidMoveRandom && pub <= 24)
		{
			GAMELOG << init("RAID REGEN SKIP") << "NPC_IDX" << delim << p->m_npcIdx
				<< "REASON" << delim << "RANDOM"
				<< "PUB" << delim << pub
				<< end;
			continue;
		}

		CNPC* npc = gserver->m_npcProtoList.Create(p->m_npcIdx, p);
		if (!npc)
		{
			GAMELOG << init("RAID REGEN FAIL") << "NPC_IDX" << delim << p->m_npcIdx
				<< "REASON" << delim << "CREATE_FAILED" << end;

			
			p->m_totalNum = 0;
			continue;
		}

		if (!npc->m_proto->CheckFlag(NPC_PEACEFUL))
		{
			unsigned short mapAttr = GetAttr(y, x, z);
			if ((mapAttr & MATT_UNWALKABLE) || (mapAttr & MATT_PEACE))
			{
				GAMELOG << init("RAID REGEN FAIL") << "NPC_IDX" << delim << p->m_npcIdx
					<< "REASON" << delim << "BAD_TILE"
					<< "ATTR" << delim << mapAttr
					<< end;
				delete npc;
				continue;
			}
		}

		if (this->FindProtoNPCInCell(x, z, NPC_RAID, true, CELL_EXT * 2, false) != NULL)
		{
			GAMELOG << init("RAID REGEN BLOCK") << "NPC_IDX" << delim << p->m_npcIdx
				<< "REASON" << delim << "RAID_NEARBY" << end;
			delete npc;
			continue;
		}

		int cx, cz;

		GET_X(npc) = x;
		GET_YLAYER(npc) = y;
		GET_Z(npc) = z;

		if (npc->m_proto->CheckFlag(NPC_ATTACK))
			GET_R(npc) = GetRandom(0, (int)(PI_2 * 10000)) / 10000.0f;
		else
			GET_R(npc) = r;

		npc->m_regenX = GET_X(npc);
		npc->m_regenY = GET_YLAYER(npc);
		npc->m_regenZ = GET_Z(npc);
		npc->m_recoverPulse = gserver->m_pulse;

		p->m_bAlive = true;
		p->m_numRegen++;
		p->m_bRaidMoveRandom = false;

		
		GAMELOG << init("RAID REGEN SPAWN")
			<< "NPC_IDX" << delim << p->m_npcIdx
			<< "WAIT_SEC" << delim << (waitPulse / PASSES_PER_SEC)
			<< "X" << delim << x << "Z" << delim << z << "Y" << delim << (int)y
			<< "NPC_FLAG_RAID" << delim << (npc->m_proto->CheckFlag(NPC_RAID) ? 1 : 0)
			<< end;

		p->m_lastDieTime = 0;

		npc->InitPointsToMax();
		npc->m_disableTime = time(0);

		AddNPC(npc);
		PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
		CharToCell(npc, GET_YLAYER(npc), cx, cz);

		CNetMsg::SP rmsg(new CNetMsg);
		SysRaidmobRegenMsg(rmsg, npc->m_proto->m_index, GET_X(npc), GET_Z(npc));
		SendToCell(rmsg, GET_YLAYER(npc), npc->m_cellX, npc->m_cellZ, RAID_NPC_NOTICE_CELL_EXT);

		return true;
	}

	return false;
}


void MobRecover(CNPC* npc)
{
	// NPC ȸ��
	if (gserver->m_pulse - npc->m_recoverPulse >= NPC_RECOVER_PULSE)
	{
		if (npc->m_hp != npc->m_maxHP || npc->m_mp != npc->m_maxMP)
		{
			int hp = npc->m_hp + npc->m_recoverHP;
			int mp = npc->m_mp + npc->m_recoverMP;

			if (hp > npc->m_maxHP)
				npc->m_hp = npc->m_maxHP;
			else
				npc->m_hp = hp;

			if (mp > npc->m_maxMP)
				npc->m_mp = npc->m_maxMP;
			else
				npc->m_mp = mp;

			{
				CNetMsg::SP rmsg(new CNetMsg);
				CharStatusMsg(rmsg, npc, 0);
				npc->m_pArea->SendToCell(rmsg, npc, false);
			}
		}

		npc->m_recoverPulse = gserver->m_pulse;
	}
}
bool MobProcSkill(CNPC* npc)
{
	bool bSkip = false;
	// ���� ��ų ������ΰ�
	if(npc->m_currentSkill)
	{
		CCharacter* tskillTarget = NULL;

		switch (npc->m_currentSkill->m_state)
		{
		case SKILL_CON_NORMAL:
			break;

		case SKILL_CON_READY:
			try
			{
				// ��ų ����->���̾� �˻�
				if (npc->m_currentSkill->m_usetime + npc->m_currentSkill->m_proto->m_readyTime + npc->m_currentSkill->m_proto->m_stillTime <= gserver->m_pulse)
				{
					// hp, mp �˻�
					if (npc->m_hp <= npc->m_currentSkill->m_proto->Level(npc->m_currentSkill->m_level)->m_needHP
							|| npc->m_mp <= npc->m_currentSkill->m_proto->Level(npc->m_currentSkill->m_level)->m_needMP)
						throw 0;

					// Ÿ�� �˻�
					if (npc->m_currentSkill->m_targetIndex != -1)
					{
						// ���� Ÿ���� ���ؼ�
						tskillTarget = npc->m_pArea->FindCharInCell(npc, npc->m_currentSkill->m_targetIndex, npc->m_currentSkill->m_targetType, false);
						if (tskillTarget == NULL || tskillTarget->IsInPeaceZone(false))
							throw 0;
					}

					int	mcount = npc->m_currentSkill->m_proto->m_levelproto[npc->m_currentSkill->m_level - 1]->m_targetNum ;

					boost::scoped_array<MultiTarget> multitarget(new MultiTarget[mcount]);

					CCharacter* tcenter = (tskillTarget) ? tskillTarget : npc;
					float tr = (tskillTarget) ? atan2(GET_Z(tcenter) - GET_Z(npc), GET_X(tcenter) - GET_X(npc)) : GET_R(npc);
					float tr2;

					int sx = tcenter->m_cellX - CELL_EXT;
					int ex = tcenter->m_cellX + CELL_EXT;
					int sz = tcenter->m_cellZ - CELL_EXT;
					int ez = tcenter->m_cellZ + CELL_EXT;

					int i = 0;
					int x, z;
					bool bHelp = (npc->m_currentSkill->m_proto->m_flag & SF_HELP) ? true : false;
					bool bNotHelp = (npc->m_currentSkill->m_proto->m_flag & SF_NOTHELP) ? true : false;

					if (mcount < 1)
						mcount = 0;

					if (mcount > 0)			// ��Ƽ Ÿ�� ���ϱ� : �Ÿ� ���� ����� �������
					{
						i = 0;
						for (x = sx; x <= ex; x++)
						{
							if (x < 0 || x >= tcenter->m_pArea->m_size[0]) continue;

							for (z = sz; z <= ez; z++)
							{
								if (z < 0 || z >= tcenter->m_pArea->m_size[1]) continue;

								CCharacter *pChar;
								CCharacter *pCharNext = tcenter->m_pArea->m_cell[x][z].m_listChar;

								while ((pChar = pCharNext))
								{
									pCharNext = pCharNext->m_pCellNext;

									if ( pChar == NULL )
										throw 0;

									if (pChar->m_index <= 0)
									{
										int nIndex = 0;
										if (npc) nIndex	= npc->m_proto->m_index;

										GAMELOG << init("MOB_BUG - SORT ") << "npc " << nIndex << delim << "count " << mcount << delim
												<< "target type " << delim << pChar->m_type << delim
												<< "char index "  << delim << pChar->m_index << end;
										continue;
									}

									if(IS_NPC(pChar))
									{
										CNPC* target = TO_NPC(pChar);
#ifdef EXTREME_CUBE
										if(	   target->m_proto->m_index == CUBEMASTER_RED
											|| target->m_proto->m_index == CUBEMASTER_BLUE
											|| target->m_proto->m_index == CUBEMASTER_YELLOW
											|| target->m_proto->m_index == CUBEMASTER_PURPLE
											|| target->m_proto->m_index == CUBEMASTER_ORANGE
											|| target->m_proto->m_index == CUBE_RED
											|| target->m_proto->m_index == CUBE_BLUE
											|| target->m_proto->m_index == CUBE_YELLOW
											|| target->m_proto->m_index == CUBE_PURPLE
											|| target->m_proto->m_index == CUBE_ORANGE)
										{
											continue;
										}
#endif //EXTREME_CUBE
									}

									float tdist = GetDistance(tcenter, pChar);

									if (pChar != tcenter && !DEAD(pChar) && ((bHelp && !npc->IsEnemy(pChar)) || (bNotHelp && npc->IsEnemy(pChar))))
									{
										if (ABS(GET_YLAYER(pChar) - GET_YLAYER(tcenter)) <= 1 && tdist <= npc->m_currentSkill->m_proto->m_appRange)
										{
											// ����120, ���� ���簢 �˻�
											switch (npc->m_currentSkill->m_proto->m_targetType)
											{
											case STT_TARGET_D120:
												tr2 = atan2(GET_Z(pChar) - GET_Z(npc), GET_X(pChar) - GET_X(npc));
												if (ABS(tr - tr2) > PI / 3)
													continue ;
												break;

											case STT_TARGET_RECT:
												tr2 = ABS(atan2(GET_Z(pChar) - GET_Z(npc), GET_X(pChar) - GET_X(npc)) - tr);
												if (sin(tr2) * GetDistance(GET_X(npc), GET_X(pChar), GET_Z(npc), GET_Z(pChar), 0, 0) - pChar->GetSize()> 0.6)
													continue ;
												break;
											}

											if (i == mcount -1 )
											{
												int j = 0, k =0 ;
												for (k = 1; k < mcount; k++)
												{
													if ( multitarget[j].mdist < multitarget[k].mdist )
														j = k;
												}

												if ( multitarget[j].mdist > tdist)
												{
													multitarget[j].mtarget		= pChar;
													multitarget[j].mtargettype	= (char)pChar->m_type;
													multitarget[j].mtargetindex = pChar->m_index;
													multitarget[j].mdist		= tdist;
												}
											}
											else
											{
												multitarget[i].mtarget		= pChar;
												multitarget[i].mtargettype  = (char)pChar->m_type;
												multitarget[i].mtargetindex = pChar->m_index;
												multitarget[i].mdist		= tdist;
												i++;
											}
										}
									}
								}
							}
						}
					}

					mcount = i;

					int m = 0;
					for (m = 0; m < mcount; m++)
					{
						if (multitarget[m].mtarget == NULL && multitarget[m].mtargettype != MSG_CHAR_UNKNOWN)
						{
							int nIndex = 0;
							if (npc) nIndex	= npc->m_proto->m_index;

							GAMELOG << init("MOB_BUG - targer is NULL ") << "npc " << nIndex << delim << "i " << m << delim << "count " << mcount << delim
									<< "target type " << delim << multitarget[m].mtargettype << delim
									<< "char index "  << delim << multitarget[m].mtargetindex << end;
							continue;
						}

						if (multitarget[m].mtarget == NULL)
							continue;

						if (multitarget[m].mtarget->m_index <= 0)
						{
							int nIndex = 0;
							if (npc) nIndex	= npc->m_proto->m_index;

							GAMELOG << init("MOB_BUG - wrong index ") << "npc " << nIndex << delim << "i " << m << delim << "count " << mcount << delim
									<< "target type " << delim << multitarget[m].mtargettype << delim
									<< "char index "  << delim << multitarget[m].mtargetindex << end;
							continue;
						}
					}

					npc->m_currentSkill->Fire();
					{
						CNetMsg::SP rmsg(new CNetMsg);
						ResponseClient::makeSkillFireMsg(rmsg, npc, npc->m_currentSkill, tskillTarget, mcount, multitarget.get(), 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
						npc->m_pArea->SendToCell(rmsg, npc, false);
					}

					npc->m_hp -= npc->m_currentSkill->m_proto->Level(npc->m_currentSkill->m_level)->m_needHP;
					npc->m_mp -= npc->m_currentSkill->m_proto->Level(npc->m_currentSkill->m_level)->m_needMP;
					{
						CNetMsg::SP rmsg(new CNetMsg);
						CharStatusMsg(rmsg, npc, 0);
						npc->m_pArea->SendToCell(rmsg, npc, false);
					}
//dethunter12
					if (tskillTarget)
					{
						CPC* pc = NULL;
						switch (tskillTarget->m_type)
						{
							case MSG_CHAR_PC:
								pc = TO_PC(tskillTarget);
								break;
							case MSG_CHAR_APET:
							{
								CAPet* apet = TO_APET(tskillTarget);
								pc = apet ? apet->GetOwner() : NULL;
							}
							break;
							case MSG_CHAR_PET:
							{
								CPet* pet = TO_PET(tskillTarget);
								pc = pet ? pet->GetOwner() : NULL;
							}
							break;
							case MSG_CHAR_ELEMENTAL:
							{
								CElemental* elemental = TO_ELEMENTAL(tskillTarget);
								pc = elemental ? elemental->GetOwner() : NULL;
							}
							break;
							case MSG_CHAR_NPC:       // handle or ignore
							case MSG_CHAR_UNKNOWN:   // handle or ignore
							default:
								pc = NULL;
								break;
						}

						if (pc)
						{
							CNetMsg::SP rmsg(new CNetMsg);
							SendMobAggressiveStatus(rmsg, npc, true);
							SEND_Q(rmsg, pc->m_desc);

							PCManager::instance()->sendToAlliesInCell(rmsg, pc);
						}
					}

					{
						MultiTarget* mTarget = multitarget.get();
						for (int i = 0; i < mcount; i++)
						{
							if (mTarget[i].mtargetindex <= 0)
								continue;

							if (!mTarget[i].mtarget)
								continue;

							CPC* pc = NULL;
							CCharacter* target = mTarget[i].mtarget;

							switch (target->m_type)
							{
								case MSG_CHAR_PC:
									pc = TO_PC(target);
									break;
								case MSG_CHAR_APET:
								{
									CAPet* apet = TO_APET(target);
									pc = apet ? apet->GetOwner() : NULL;
								}
								break;
								case MSG_CHAR_PET:
								{
									CPet* pet = TO_PET(target);
									pc = pet ? pet->GetOwner() : NULL;
								}
								break;
								case MSG_CHAR_ELEMENTAL:
								{
									CElemental* elemental = TO_ELEMENTAL(target);
									pc = elemental ? elemental->GetOwner() : NULL;
								}
								break;
								case MSG_CHAR_NPC:       // handle or ignore
								case MSG_CHAR_UNKNOWN:   // handle or ignore
								default:
									pc = NULL;
									break;
							}
							
							if (pc)
							{
								CNetMsg::SP rmsg(new CNetMsg);
								SendMobAggressiveStatus(rmsg, npc, true);
								SEND_Q(rmsg, pc->m_desc);

								PCManager::instance()->sendToAlliesInCell(rmsg, pc);
							}
						}
					}

					// 스킬 적용
					// 타게팅에 따라
					bool bApply;
					switch (npc->m_currentSkill->m_proto->m_targetType)
					{
					case STT_SELF_ONE:
						ApplySkill(npc, npc, npc->m_currentSkill, -1, bApply);
						break;

					case STT_SELF_RANGE:
						{
							if (ApplySkill(npc, npc, npc->m_currentSkill, -1, bApply) != -1)
							{
								for (i = 0; i < mcount; i++)
								{
									if (multitarget[i].mtarget->m_index <= 0)
									{
										int nIndex = 0;
										if (npc) nIndex	= npc->m_proto->m_index;

										GAMELOG << init("MOB_BUG - STT_SELF_RANGE ") << "npc " << nIndex << delim << "i " << i << delim << "count " << mcount << delim
												<< "target type " << delim << multitarget[i].mtargettype << delim
												<< "char index "  << delim << multitarget[i].mtargetindex << end;
										break;
									}
									// npc�� ���ֵ̹� �����̸�
									if ( npc->Check_MobFlag( STATE_MONSTER_TAMING )
											|| npc->Check_MobFlag( STATE_MONSTER_MERCENARY ) )
									{
										const CSkillProto* proto = npc->m_currentSkill->m_proto;

										// ��ų�� �ز��� Ÿ���̸�
										if ( proto && proto->m_flag & SF_NOTHELP && multitarget[i].mtargettype != MSG_CHAR_NPC )
										{
											// NPC�� �������� �Դ´�.
											continue;
										}
									}
									if (ApplySkill(npc, multitarget[i].mtarget, npc->m_currentSkill, -1, bApply) == -1)
										break;
								}
							}
						}
						break;

					case STT_TARGET_ONE:
						if (tskillTarget)
							ApplySkill(npc, tskillTarget, npc->m_currentSkill, -1, bApply);
						break;

					case STT_TARGET_RANGE:
					case STT_TARGET_D120:
					case STT_TARGET_RECT:
						{
							if (tskillTarget)
							{
								if (ApplySkill(npc, tskillTarget, npc->m_currentSkill, -1, bApply) != -1)
								{
									if(npc->m_proto == NULL)
										break;
									
									for (i = 0; i < mcount; i++)
									{
										if (multitarget[i].mtarget->m_index <= 0)
										{
											int nIndex = 0;
											if (npc) nIndex	= npc->m_proto->m_index;

											GAMELOG << init("MOB_BUG - STT_TARGET_RANGE ") << "npc " << nIndex << delim << "i " << i << delim << "count " << mcount << delim
													<< "target type " << delim << multitarget[i].mtargettype << delim
													<< "char index "  << delim << multitarget[i].mtargetindex << end;
											break;
										}
										// npc�� ���ֵ̹� �����̸�
										if ( npc->Check_MobFlag( STATE_MONSTER_TAMING )
												|| npc->Check_MobFlag( STATE_MONSTER_MERCENARY ) )
										{
											const CSkillProto* proto = npc->m_currentSkill->m_proto;

											// ��ų�� �ز��� Ÿ���̸�
											if ( proto && proto->m_flag & SF_NOTHELP && multitarget[i].mtargettype != MSG_CHAR_NPC )
											{
												// NPC�� �������� �Դ´�.
												continue;
											}
										}
										if (ApplySkill(npc, multitarget[i].mtarget, npc->m_currentSkill, -1, bApply) == -1)
											break;
									}
								}
							}
						}
						break;

					case STT_PARTY_ONE:
						if (tskillTarget)
						{
							if (npc->m_proto->m_family != -1 && IS_NPC(tskillTarget) && npc->m_proto->m_family == TO_NPC(tskillTarget)->m_proto->m_family)
								ApplySkill(npc, tskillTarget, npc->m_currentSkill, -1, bApply);
						}
						break;

					case STT_PARTY_ALL:
						if (npc->m_proto->m_family != -1)
						{
							int sx = npc->m_cellX - CELL_EXT;
							int ex = npc->m_cellX + CELL_EXT;
							int sz = npc->m_cellZ - CELL_EXT;
							int ez = npc->m_cellZ + CELL_EXT;

							int x, z;

							for (x = sx; x <= ex; x++)
							{
								if (x < 0 || x >= npc->m_pArea->m_size[0])
									continue;

								for (z = sz; z <= ez; z++)
								{
									if (z < 0 || z >= npc->m_pArea->m_size[1])
										continue;

									CCharacter *pChar;
									CCharacter *pCharNext = npc->m_pArea->m_cell[x][z].m_listChar;

									while ((pChar = pCharNext))
									{
										pCharNext = pCharNext->m_pCellNext;

										if (IS_NPC(pChar) && TO_NPC(pChar)->m_proto->m_family == npc->m_proto->m_family)
										{
											if (ApplySkill(npc, pChar, npc->m_currentSkill, -1, bApply) == -1)
												break;
										}
									}
								}
							}
						}
						break;
					}
					if( npc->Check_MobFlag(STATE_MONSTER_SUICIDE) || npc->Check_MobFlag(STATE_MONSTER_TRAP) )
					{
						if( mcount > 0 || tskillTarget )  // �ѹ��̶� ��ų�� ����ߴٸ�
						{
							npc->GetOwner()->SummonNpcRemove(npc);
							bSkip = true;
						}
					}
				} // end if

				npc->m_aipulse = gserver->m_pulse;
				npc->m_delay = NPC_ACTIVITY_DELAY;
			}
			catch (...)
			{
				/* speed_ksw after */
				CNetMsg::SP rmsg(new CNetMsg);
				/* speed_ksw after */
				npc->m_currentSkill->Cancel(npc);
				npc->m_currentSkill = NULL;
				ResponseClient::makeSkillCancelMsg(rmsg, npc);
				npc->m_pArea->SendToCell(rmsg, npc, false);
			}
			bSkip = true;
			break;

		case SKILL_CON_FIRE:
			if (npc->m_currentSkill->m_usetime + npc->m_currentSkill->m_proto->m_readyTime + npc->m_currentSkill->m_proto->m_stillTime + npc->m_currentSkill->m_proto->m_fireTime <= gserver->m_pulse)
			{
				npc->m_currentSkill->Cancel(npc);
				npc->m_currentSkill = NULL;
				npc->m_aipulse = gserver->m_pulse;
				npc->m_delay = NPC_ACTIVITY_DELAY;
			}
			else
				bSkip = true;
			break;
		}
	}

	return bSkip;
}

CCharacter* MobSelectSkill(CNPC* npc, CCharacter* target)
{
	// ���� ��ų ������̸� ��ŵ
	if (npc->m_currentSkill)
		return target;

	bool bHealerFlag2_Mercenary = ( npc->m_proto->m_aitype == NPC_AI_HEALER && npc->m_proto->CheckAIBit(2) );
	if ( bHealerFlag2_Mercenary && ( npc->Check_MobFlag( STATE_MONSTER_MERCENARY) ) )
	{
		if( npc->GetOwner() && npc->GetOwner()->m_hp < npc->GetOwner()->m_maxHP )
		{
			target = (CCharacter *)npc->GetOwner();
			return target;
		}
		else
			target = npc->GetOwner()->GetSummonOwners_target();
	}
	else if( npc->Check_MobFlag( STATE_MONSTER_MERCENARY) && npc->GetOwner() )
	{
		target = npc->GetOwner()->GetSummonOwners_target();
	}

	if( npc->Check_MobFlag( STATE_MONSTER_MERCENARY) )
	{
		if( !npc->GetOwner() )
			return NULL;

		if( (target && ( target->m_pZone->m_index != npc->m_pZone->m_index || GetDistance(target, (CCharacter*)npc) >= 40.0f ))
				|| GetDistance( (CCharacter*)npc->GetOwner(), (CCharacter*)npc) > 40.0f ) // ���� ���� ���� �ʰų� �Ÿ��� �ʹ� �ָ� ���ʿ� �ʹ� �־����� ������ �������.
		{
			npc->GetOwner()->SetSummonOwners_target(NULL);
			return NULL;
		}
	}

	// ȸ�� ��ų�� ���� npc�� ���̹� �Ǿ��� ���
	// ���̹� ���� �̸鼭 ������ �÷��� 2�϶� HP 80% �̸��� �ڽŰ� PC���� ��ȿ�� ��ų ���
	//bool bHealerFlag2_Taming = ( npc->m_proto->m_aitype == NPC_AI_HEALER && npc->m_proto->CheckAIBit(2) );
	if ( /*bHealerFlag2_Taming &&*/ ( npc->Check_MobFlag( STATE_MONSTER_TAMING ) ) )
	{
		int sx1 = npc->m_cellX - CELL_EXT;
		int ex1 = npc->m_cellX + CELL_EXT;
		int sz1 = npc->m_cellZ - CELL_EXT;
		int ez1 = npc->m_cellZ + CELL_EXT;

		int a, b;

		// �ϴ� �ٸ� ���� �˻� ���Ѵ�
		for (a = sx1; a <= ex1; a++)
		{
			if (a < 0 || a >= npc->m_pArea->m_size[0]) continue;
			for (b = sz1; b <= ez1; b++)
			{
				if (b < 0 || b >= npc->m_pArea->m_size[1]) continue;
				CCharacter *pChar;
				for (pChar = npc->m_pArea->m_cell[a][b].m_listChar; pChar; pChar = pChar->m_pCellNext)
				{
					// ������ ����, �ٸ��� ����
					if ( DEAD(pChar) || ABS( GET_YLAYER(npc) - GET_YLAYER(pChar) ) >= 2)
						continue;

					// npc�̸� �ڱ� �ڽ� ������ ����
					if ( IS_NPC(pChar) )
					{
						CNPC* check_npc = TO_NPC(pChar);
						if ( check_npc != npc )
						{
							continue;
						}
					}

					// ��ų ��� ���� �˻�
					int skillindex = -1;
					int i;
					for (i = 0; i < MAX_NPC_SKILL; i++)
					{
						if (npc->m_skills[i]
								&& (npc->m_skills[i]->m_proto->m_flag & SF_HELP)
								&& npc->m_skills[i]->IsReady(npc)
								&& npc->CanSpell()
								&& npc->m_hp > npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)->m_needHP
								&& npc->m_mp > npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)->m_needMP
								&& pChar->CanApplySkill(npc->m_skills[i]->m_proto, npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level))
								&& (npc->CanMove() || GetDistance(npc, pChar) - npc->m_skills[i]->m_proto->GetFireRange(npc) <= 0.3))
						{
							// AI Type�� ���� ����� ��ų ���� ����(����, ��ȿ)
							if (    ( //bHealerFlag2_Taming &&
										npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)->m_durtime < 1
										&& pChar->m_hp < pChar->m_maxHP * 80 / 100)										// ���� �÷���2�� ��ȿ���� ü�º��� ��󿡰� �ɾ���
							   )
							{
								skillindex = i;
								break;
							}
						}
					}

					// ��ų ��� ���� ������
					if ( skillindex >= 0 )
					{
						target = pChar;
						npc->m_currentSkill = npc->m_skills[skillindex];
						npc->m_currentSkill->m_targetType = target->m_type;
						npc->m_currentSkill->m_targetIndex = target->m_index;
						return target;
					}
				}
			}  // for
		}  // for
	}  // if

	// ������������ �÷��� 2�϶� �ֺ� �������� ������ �ɾ��ش�
	// ������ �÷��� 0�϶� �ֺ� �������� ������ �ɾ��ش�
	// ������ �÷��� 2�϶� �ֺ� ����(�ڽ�����) HP 80% �̸����� ��ȿ�� ��ų ���
	bool bDamageDealerFlag2 = (target && npc->m_proto->m_aitype == NPC_AI_DAMAGEDEALER && npc->m_proto->CheckAIBit(2) && npc->m_hp >= npc->m_maxHP * 80 / 100 && npc->m_proto->m_family != -1);
	bool bHealerFlag0 = (target && npc->m_proto->m_aitype == NPC_AI_HEALER && npc->m_proto->CheckAIBit(0) && npc->m_hp >= npc->m_maxHP * 80 / 100 && npc->m_proto->m_family != -1);
	bool bHealerFlag2 = (npc->m_proto->m_aitype == NPC_AI_HEALER && npc->m_proto->CheckAIBit(2) && npc->m_proto->m_family != -1);
	if (bDamageDealerFlag2 || bHealerFlag0 || bHealerFlag2)
	{
		int sx = npc->m_cellX - CELL_EXT;
		int ex = npc->m_cellX + CELL_EXT;
		int sz = npc->m_cellZ - CELL_EXT;
		int ez = npc->m_cellZ + CELL_EXT;

		int x, z;
		float dist = 999.9f;
		CNPC* ret = NULL;
		CSkill* retSkill = NULL;

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
					// NPC��, ������ ����, �ٸ��� ����
					if (!IS_NPC(pChar) || DEAD(pChar) || ABS(GET_YLAYER(npc) - GET_YLAYER(pChar)) >= 2)
						continue ;

					CNPC* tnpc = TO_NPC(pChar);

					// �����̰�
					if (tnpc->m_proto->m_family != npc->m_proto->m_family)
						continue ;

					// ��ų ��� ���� �˻�
					int skillindex = -1;
					int i;
					for (i = 0; i < MAX_NPC_SKILL; i++)
					{
						if (npc->m_skills[i]
								&& (npc->m_skills[i]->m_proto->m_flag & SF_HELP)
								&& npc->m_skills[i]->IsReady(npc)
								&& npc->CanSpell()
								&& npc->m_hp > npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)->m_needHP
								&& npc->m_mp > npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)->m_needMP
								&& tnpc->CanApplySkill(npc->m_skills[i]->m_proto, npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level))
								&& (npc->CanMove() || GetDistance(npc, tnpc) - npc->m_skills[i]->m_proto->GetFireRange(npc) <= 0.3))
						{
							// AI Type�� ���� ����� ��ų ���� ����(����, ��ȿ)
							if (    (bDamageDealerFlag2
									 && npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)->m_durtime > 0
									 && !tnpc->m_assist.FindBySkillIndex(npc->m_skills[i]->m_proto->m_index))		// ����� ������ ������ �Ȱɸ� ��󿡰� �ɾ���

									|| (bHealerFlag0
										&& npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)->m_durtime > 0
										&& !tnpc->m_assist.FindBySkillIndex(npc->m_skills[i]->m_proto->m_index))		// ���� �÷���0�� ������ �Ȱɸ� ��󿡰� �ɾ���

									|| (bHealerFlag2
										&& npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)->m_durtime < 1
										&& tnpc->m_hp < tnpc->m_maxHP * 80 / 100)										// ���� �÷���2�� ��ȿ���� ü�º��� ��󿡰� �ɾ���
							   )
							{
								skillindex = i;
								break;
							}
						}
					}

					// ��ų ��� ���� ������
					if (skillindex >= 0)
					{
						// ������ Ÿ�԰˻� : ��Ŀ, �ڽ���Ÿ��, �׿�, ����
						// Ÿ���� ������ �Ÿ��� ��
						int resComp = AIComp(npc, tnpc, ret);
						if (resComp < 0 || (resComp == 0 && dist > GetDistance(npc, tnpc)))
						{
							dist = GetDistance(npc, tnpc);
							ret = tnpc;
							retSkill = npc->m_skills[skillindex];
						}
					}
				}
			}
		}

		if (ret)
		{
			target = ret;
			npc->m_currentSkill = retSkill;
			npc->m_currentSkill->m_targetType = target->m_type;
			npc->m_currentSkill->m_targetIndex = target->m_index;
			return target;
		}
	}

	// ���̵� �� �г� ó�� : ü���� 50% ���Ϸ� ��������
	if (npc->m_proto->CheckFlag(NPC_RAID) && npc->m_hp <= npc->m_maxHP / 2)
	{
		// ���� �г� ��ų�� ������� �ʾ��� ��
		if (npc->m_assist.FindBySkillIndex(RAID_NPC_RAGE_SKILL) == 0)
		{
			npc->m_currentSkill = gserver->m_skillProtoList.Create(RAID_NPC_RAGE_SKILL, RAID_NPC_RAGE_SKILL_LEVEL);
			if (npc->m_currentSkill)
			{
				npc->m_currentSkill->m_targetType = npc->m_type;
				npc->m_currentSkill->m_targetIndex = npc->m_index;
				return npc;
			}
		}
	}

	// Ÿ���� ���� �� : �̰��� �����Ը� ����
	if (target)
	{
		// ȥ���̳� ���ֵ̹� npc�� unhelpŸ�� ��ų Ÿ���� pc�� ���� �� ����.
		if( IS_PC(target)
				&& ( npc->Check_MobFlag( STATE_MONSTER_TAMING ) || npc->Check_MobFlag( STATE_MONSTER_CONFUSION ) )
		  )
			return target;

		if(DEAD(target))
			return NULL;

		float dist = GetDistance((CCharacter*)npc, target);
		if (!npc->m_proto->CheckFlag(NPC_CASTLE_TOWER))
		{
			int skillindex = -1;
			int i;
			for (i = 0; i < MAX_NPC_SKILL; i++)
			{
				int skillprob = GetRandom(1, 10000);
				// ��ų ��� ���� �˻�
				if (npc->m_skills[i]
						&& npc->m_proto->m_skillProb[i] >= skillprob
						&& npc->m_skills[i]->IsReady(npc)
						&& npc->CanSpell()
						&& npc->m_hp > npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)->m_needHP
						&& npc->m_mp > npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)->m_needMP
						&& target->CanApplySkill(npc->m_skills[i]->m_proto, npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level))
						&& (npc->CanMove() || dist - npc->m_skills[i]->m_proto->GetFireRange(npc) <= 0.3))
				{
					skillindex = i;
					break;
				}
			}
			if (skillindex >= 0)
			{
				npc->m_currentSkill = npc->m_skills[skillindex];
				npc->m_currentSkill->m_targetType = target->m_type;
				npc->m_currentSkill->m_targetIndex = target->m_index;
			}
		}
	}

	return target;
}

bool MobReadySkill(CNPC* npc, CCharacter* target)
{

	if (npc->m_currentSkill && npc->m_currentSkill->m_state == SKILL_CON_NORMAL && GetDistance(npc, target) - npc->m_currentSkill->m_proto->GetFireRange(npc) <= 0.3)
	{
		if( !npc->Check_MobFlag( STATE_MONSTER_TRAP ))
			npc->CancelInvisible();

		switch (npc->m_currentSkill->m_proto->m_targetType)
		{
		case STT_SELF_ONE:
		case STT_SELF_RANGE:
		case STT_PARTY_ONE:
		case STT_PARTY_ALL:
			npc->m_currentSkill->Ready(NULL);
			break;

		default:
			npc->m_currentSkill->Ready(target);
			break;
		}

#if defined (LC_GAMIGO)  || defined(LC_BILA)
		// imso- NPC_RAID BUG
		if (!npc->m_proto->CheckFlag(NPC_RAID))
#endif
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeSkillReadyMsg(rmsg, npc, npc->m_currentSkill, target);
			npc->m_pArea->SendToCell(rmsg, npc, false);
		}
		npc->m_aipulse = gserver->m_pulse;
		npc->m_delay = 0;

		return true;
	}
	return false;
}

bool MobProcFear(CNPC* npc, CCharacter* target)
{
	// �Ǿ� �ɸ� NPC�ΰ�? : �ǽ�NPC, �̵��Ұ� NPC�� �Ǿ� ����
	if (npc->m_proto->CheckFlag(NPC_PEACEFUL) ||
			!npc->m_proto->CheckFlag(NPC_MOVING) ||
			(target == NULL && npc->m_assist.m_avAddition.hcFearIndex < 1))
		return false;

	// �Ǿ� ��� ã��
	if (target == NULL && npc->m_assist.m_avAddition.hcFearIndex > 0)
	{
		target = npc->m_pArea->FindCharInCell(npc, npc->m_assist.m_avAddition.hcFearIndex, npc->m_assist.m_avAddition.hcFearType, false);

		// �Ǿ� ����� �þ߳��� ������ Ǯ��
		if (!target)
		{
			npc->m_assist.CureAssist(MST_ASSIST_FEAR, 99);
			return false;
		}
	}

	// �Ǿ��� ������κ��� ����
	float tr = (float)atan2(GET_Z(npc) - GET_Z(target), GET_X(npc) - GET_X(target));
	float dist = npc->GetRunSpeed();
	float x = GET_X(npc) + dist * (float)cos(tr);
	float z = GET_Z(npc) + dist * (float)sin(tr);
	MobMoveTo(npc, x, z, true, false, target);

	return true;
}

float MobMoveTo(CNPC* npc, float x, float z, bool bRun, bool bAttack, CCharacter* target)
{
	float ox = x;
	float oz = z;
	float dist = 0;

	if (!npc->CanMove())
	{
		dist = GetDistance(ox, oz, npc->m_pArea->GetHeight(GET_YLAYER(npc), ox, oz), npc);
		if (target)
			dist -= target->GetSize();
		if (npc->m_currentSkill)
			dist -= npc->m_currentSkill->m_proto->GetFireRange(npc);
		else if (target && bAttack && npc->CanAttack())
			dist -= npc->m_attackRange;

		return dist;
	}

	// �ٱ��� ����
	npc->m_bMoveRun = bRun;
	// �ִ� �̵� �Ÿ��� �̼ӿ��� ������
	float moveSpeed = (bRun) ? npc->GetRunSpeed() : npc->m_walkSpeed;

	// ����
	float tr = (float)atan2(z - GET_Z(npc), x - GET_X(npc));

	// ��� ������ ����
	float h = npc->m_pArea->GetHeight(GET_YLAYER(npc), x, z);

	float trh = 0.0f;
	bool bRunAI = false;

	char outY;

	// �̵��� �������� �ִ��� �˻�
	if (npc->m_pArea->IsNotBlocked(npc, GET_YLAYER(npc), x, z, bAttack, outY))
	{
		// Ÿ�ٰ��� �Ÿ� �˻� H ����
		dist = GetDistance(x, z, h, npc);
		if (target)
			dist -= target->GetSize();
		if (npc->m_currentSkill)
			dist -= npc->m_currentSkill->m_proto->GetFireRange(npc);
		else if (target && bAttack && npc->CanAttack())
			dist -= npc->m_attackRange;

		

		// �̵� �Ÿ��� 0.3 �̸��̸� ����
		if (dist <= 0.3f)
			return 0.0f;

		// �̵��Ÿ����� ������ �����̸� ������ �ٿ��� �̵�
		if (dist < moveSpeed)
		{
			if (dist < (moveSpeed / 2))
				npc->m_delay  = 0;
		}

		float fValidCheck = (h - GET_H(npc)) / (GetDistance(x, GET_X(npc), z, GET_Z(npc), h, GET_H(npc)) + 0.01f);
		if (fValidCheck > 1.0f)
			fValidCheck = 1.0f;
		trh = (float)asin(fValidCheck);
	}
	else
	{
		bRunAI = true;

		

		// AI �̵���ο��� ������������ �ְ� ���� �ٲ�� �ϸ� ���� ��ȯ
		if (npc->m_nBlockAI != 0 && npc->m_bChangeDir)
			npc->m_moveDir *= -1;

		// ���ʹ������� �ٲٸ鼭 �õ� Ƚ�� 3������ �ʰ��� �����̵�(Ÿ���� ���°�ó��)
		if (npc->m_nBlockAI > 3)
		{
			tr = GetRandom((int)(-PI* 1000), (int)(PI * 1000)) / 1000.0f;
			dist = npc->m_walkSpeed;
			npc->m_bMoveRun= false;

			// AI���ú��� �ʱ�ȭ
			npc->InitAIVar();
		}
		// 90������
		else
		{
			if (npc->m_bFail45)
				// Create �� ������ �������� 90�� ȸ�� 45�� ȸ���� �����ϰ�� �õ�
				tr += npc->m_moveDir * PI_HALF;
			else
				// ������ �������� 45�� ȸ��
				tr += npc->m_moveDir * PI_HALF / 2;

			// ���� �ȹٲ㵵 �ȴ�
			npc->m_bChangeDir = false;

			// runSpeed ��ŭ �̵�
			//dist = npc->m_runSpeed;
			npc->m_bMoveRun =true;
			dist = 1.0f;
			npc->m_delay = 0;
		}

		// ��������
		x = GET_X(npc) + dist * (float)cos(tr);
		z = GET_Z(npc) + dist * (float)sin(tr);
		h = npc->m_pArea->GetHeight(GET_YLAYER(npc), x, z);
		float fValidCheck = (h - GET_H(npc)) / (GetDistance(x, GET_X(npc), z, GET_Z(npc), h, GET_H(npc)) + 0.01f);
		if (fValidCheck > 1.0f)
			fValidCheck = 1.0f;
		trh = (float)asin(fValidCheck);
	}

	npc->m_bStop = false;

	if (npc->m_bMoveRun)
	{
		if (dist > npc->GetRunSpeed())
			dist = npc->GetRunSpeed();
	}
	else
	{
		if (dist > npc->m_walkSpeed)
			dist = npc->m_walkSpeed;
	}
	float dist2 = dist * (float)cos(trh);

	x = GET_X(npc) + dist2 * (float)cos(tr);
	z = GET_Z(npc) + dist2 * (float)sin(tr);

	bool bTeleportToRegen = false;

	// �̵� ���� ���ΰ� ����
	if (!target)
	{
		if (ABS(npc->m_regenX - x) > npc->m_moveArea || ABS(npc->m_regenZ - z) > npc->m_moveArea)
			bTeleportToRegen = true;
		// Ÿ���� ���� �̵����� �ȿ� �ִ� ���
		else
			npc->m_nBlockRegen = 0;
	}

	// ��ȭ���� ���� ��� ������ ���� ��ġ�� ���� ���ư���
	if (npc->IsInPeaceZone(true))
		bTeleportToRegen = true;

    if (bTeleportToRegen)
    {
        // If this NPC is controlled by scripted movement, avoid teleport/disappear/appear logic
        // which would snap or interrupt the scripted movement when players come into view.
        if (npc->m_bScriptedMovement)
        {
            // cancel teleport handling for scripted NPCs
            bTeleportToRegen = false;
        }

		if (npc->m_nBlockRegen > 3)
		{
			{
				CNetMsg::SP rmsg(new CNetMsg);
				DisappearMsg(rmsg, npc);
				npc->m_pArea->SendToCell(rmsg, npc, false);
			}

			npc->m_pArea->CharFromCell(npc, true);

			GET_X(npc) = npc->m_regenX;
			GET_YLAYER(npc) = npc->m_regenY;
			GET_Z(npc) = npc->m_regenZ;

			int cx, cz;
			npc->m_pArea->PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
			npc->m_pArea->CharToCell(npc, GET_YLAYER(npc), cx, cz);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, npc, false);
				npc->m_pArea->SendToCell(rmsg, npc, false);
			}

			// AI ���� ���� �ʱ�ȭ
			npc->InitAIVar();

			return 999.9f;
		}
		else
		{
			// ���� ���̸� ���� ��ġ�� ���� �̵��ϰ�
			tr = (float)atan2(npc->m_regenZ - GET_Z(npc), npc->m_regenX - GET_X(npc));

			x = GET_X(npc) + (float)cos(tr) * npc->GetRunSpeed();
			z = GET_Z(npc) + (float)sin(tr) * npc->GetRunSpeed();
			float h = npc->m_pArea->GetHeight(GET_YLAYER(npc), x, z);

			// ���̰� ����
			float fValidCheck = (h - GET_H(npc)) / (GetDistance(x, GET_X(npc), z, GET_Z(npc), h, GET_H(npc)) + 0.01f);
			if (fValidCheck > 1.0f)
				fValidCheck = 1.0f;
			trh = (float)asin(fValidCheck);

			dist2 = dist * (float)cos(trh);
			x = GET_X(npc) + dist2 * (float)cos(tr);
			z = GET_Z(npc) + dist2 * (float)sin(tr);

			npc->m_bMoveRun = true;
		}
	}

	if (npc->m_bMoveRun)
	{
		if (!npc->m_pArea->MoveChar(npc, outY, x, z, npc->m_pArea->GetHeight(outY, x, z), tr, MSG_MOVE_RUN, target))
		{
			// AI���� �� Move�� �����Ѱ�� ī��Ʈ ���� ������ȯ ����
			if (bRunAI)
			{
				npc->m_nBlockAI++;
				npc->m_bChangeDir = true;
			}

			// 45�� �����̾��ٸ� ���з�
			if (!npc->m_bFail45)
				npc->m_bFail45 = true;

			// ���� �� ���� �� ���
			if (bTeleportToRegen)
				npc->m_nBlockRegen++;

			npc->m_bStop = true;
		}
	}
	else
	{
		if (!npc->m_pArea->MoveChar(npc, outY, x, z, npc->m_pArea->GetHeight(outY, x, z), tr, MSG_MOVE_WALK, target))
		{
			npc->m_bStop = true;
		}
	}	// if (npc->m_bMoveRun)

	dist = GetDistance(ox, oz, npc->m_pArea->GetHeight(GET_YLAYER(npc), ox, oz), npc);
	if (target)
		dist -= target->GetSize();
	if (npc->m_currentSkill)
		dist -= npc->m_currentSkill->m_proto->GetFireRange(npc);
	else if (target && bAttack && npc->CanAttack())
		dist -= npc->m_attackRange;

	return dist;
}

CCharacter* MobSelectTarget(CNPC* npc)
{
	CCharacter* target = NULL;

	if (npc->m_attackList)
		target = CheckAttackPulse(npc);

	// ��ȭ NPC�� Ÿ�� ���� ����
	if (npc->m_proto->CheckFlag(NPC_PEACEFUL))
		return NULL;

	// ������ ������ HP�� 80% �̻��϶�
	bool bDamageDealerFlag1 = (npc->m_proto->m_aitype == NPC_AI_DAMAGEDEALER && (target == NULL || npc->m_hp >= npc->m_maxHP * 80 / 100) && npc->m_proto->CheckAIBit(1));
	bool bDamageDealerFlag0 = (npc->m_proto->m_aitype == NPC_AI_DAMAGEDEALER && (target == NULL || npc->m_hp >= npc->m_maxHP * 80 / 100) && npc->m_proto->CheckAIBit(0));
	// ���� flag 1
	bool bHealerFlag0 = (npc->m_proto->m_aitype == NPC_AI_HEALER && (target == NULL || npc->m_hp >= npc->m_maxHP * 80 / 100) && npc->m_proto->CheckAIBit(1));
	if (bDamageDealerFlag1 || bDamageDealerFlag0 || bHealerFlag0)
	{
		CNPC* familyForHelp = NULL;

		// ����� ���� flag 1 ���� �ֺ��� ������ ü���� 60%�̸��̸� ���� ����
		if (familyForHelp == NULL && bDamageDealerFlag1)
			familyForHelp = npc->m_pArea->FindNearestFamily(npc, NPC_AI_HEALER, 60);

		// ����� ���� flag 0/���� flag 1 ���� �ֺ��� ��Ŀ Ÿ���� ����
		if (familyForHelp == NULL && (bDamageDealerFlag0 || bHealerFlag0))
			familyForHelp = npc->m_pArea->FindNearestFamily(npc, NPC_AI_TANKER);

		if (familyForHelp)
		{
			CCharacter* targetOfFamily = MobSelectTarget(familyForHelp);
			if (targetOfFamily)
			{
				if (target == NULL)
				{
					AddAttackList(npc, targetOfFamily, HATE_FIRST_ATTACK);
				}
				target = targetOfFamily;
			}
		}
	}

	// ��ȣž�� ������ ���� ����
	if (npc->m_proto->CheckFlag(NPC_CASTLE_TOWER))
		target = NULL;

	// Ÿ�� ����
	// �����̸� �ֺ� ĳ���� ã��
	float dist = 999.9f;
	if (!npc->m_pArea->IsFreeze(gserver->m_pulse))
	{
		if (!target && npc->m_proto->CheckFlag(NPC_FIRSTATTACK))
		{
			if (npc->m_disableTime == 0 && !npc->IsBlind())
			{
				target = npc->m_pArea->FindNearestTarget(npc, &dist);

				// �ǽ��� �ȿ����� Ÿ���� �� �� ����
				if (target && target->IsInPeaceZone(false))
					target = NULL;
								
				if (target && 
					target->m_pZone != NULL &&
					target->m_pZone->isRVRZone() == true &&
					target->getSyndicateType() == npc->getSyndicateType())
				{
					target = NULL;
				}

				if (target)
					AddAttackList(npc, target, HATE_FIRST_ATTACK);
			}
		}

		if (!target && npc->m_proto->CheckFlag(NPC_CASTLE_GUARD | NPC_CASTLE_TOWER))
		{
			if (npc->m_disableTime == 0 && !npc->IsBlind())
			{
				target = npc->m_pArea->FindNearestTarget(npc, &dist);
				if (target)
					AddAttackList(npc, target, HATE_FIRST_ATTACK);
			}
		}
	}

	if( !target && ( TO_NPC(npc)->Check_MobFlag(STATE_MONSTER_SUICIDE) || TO_NPC(npc)->Check_MobFlag(STATE_MONSTER_TRAP) ) )
	{
		target = npc->m_pArea->FindNearestTarget(npc, &dist);
	}

	if( target && IS_NPC(target) && TO_NPC(target)->GetOwner()  )
	{
		if( TO_NPC(target)->Check_MobFlag(STATE_MONSTER_TOTEM_ATTK) || TO_NPC(target)->Check_MobFlag(STATE_MONSTER_TOTEM_BUFF) )
		{
			target = (CCharacter*)TO_NPC(target)->GetOwner();
		}
	}

	return target;
}

CCharacter* MobSelectTarget_Taming_or_Confused(CNPC* npc)
{
	CCharacter* target = NULL;

	// ���� ��� ��ǥ�� �ٲ�� �̰� ����� ��
	//if (npc->m_attackList)
	//	target = CheckAttackPulse(npc);

	// ���Ͱ� ���͸� ����
	float dist = 999.9f;
	if (!target)
	{
		if (npc->m_disableTime == 0 && !npc->IsBlind())
		{
			target = npc->m_pArea->FindNearestTarget_Taming_or_Confused(npc, &dist);

			// �ǽ��� �ȿ����� Ÿ���� �� �� ����
			if (target && target->IsInPeaceZone(false))
				target = NULL;

			if (target)
				AddAttackList(npc, target, HATE_FIRST_ATTACK);
		}
	}

	return target;
}

void MobMoveRandom(CNPC* npc)
{
	// �̵��Ұ���
	if (!npc->CanMove())
		return ;

	// 20%�� Ȯ���� ���� ������
	// ���� ���� �����̸� 100% ���� ������(�Ⱥ���)
	// 10%�� Ȯ���� �����̵�
	/*speed_ksw before*/
	if ((npc->m_disableTime !=0) || (GetRandom(1, 100) <= 20))
		/*speed_ksw before*/
		/*
		speed_ksw after
		if ((npc->m_disableTime !=0) || (GetRandom(1, 10000) <= 500))
		speed_ksw after
		*/
	{
		float tr = GetRandom((int)(-PI* 1000), (int)(PI * 1000)) / 1000.0f;
		npc->m_bMoveRun = false;
		// ��������
		float x = GET_X(npc) + (npc->m_walkSpeed + npc->m_proto->m_size) * (float)cos(tr);
		float z = GET_Z(npc) + (npc->m_walkSpeed + npc->m_proto->m_size) * (float)sin(tr);
		MobMoveTo(npc, x, z, false, false, NULL);
	}
}

void CArea::MobActivity_Taming(CNPC* npc)
{
	CPC*	owner = NULL;				// ���͸� ���̹��� ĳ����
	CNPC*	target_tamingNpc = NULL;	// ���ֵ̹� ���Ͱ� �븮�� ����
	//CPC*	target_for_heal = NULL;		// npc�� ���� ���ִ� PC
	CCharacter* temp = NULL;

	// ������ ã�´�.
	owner = npc->GetOwner();
	if (owner == NULL)
	{
		npc->reSet_MobFlag( STATE_MONSTER_TAMING );
		npc->m_assist.CureAssist(MST_ASSIST_TAMING, 99);
		DelAttackList(npc);
		npc->SetOwner(NULL);
		MobMoveRandom(npc);
		return ;
	}

	// ������ �װų� �ָ� ��������(100����) ���̹��� Ǯ���� ���� �̵�
	if ( owner->m_hp <= 0 ) // || GetDistance(owner, npc) >= 100.0f )
	{
		npc->reSet_MobFlag( STATE_MONSTER_TAMING );
		npc->m_assist.CureAssist(MST_ASSIST_TAMING, 99);
		DelAttackList(npc);
		MobMoveRandom(npc);

		// ������ �ִ��� Ȯ��, ������ ���̹� ���� ����
		owner->DeleteSlave(npc);

		// npc�� ���ε� ���� ��
		npc->SetOwner(NULL);
		return;
	}
	else
	{
		// ������ ������ ���͸� �����Ѵ�.
		temp = owner->GetOwners_target();
	}

	// �ʱ⿡�� �ֺ��� �Ϲ� ���͸� ã�Ƽ� �����̾���... ������ ������ ������ ���͸� �����Ѵ�.
	// �ֺ� ���� �������� �ٲ��� �ϸ� �̰��� �ּ��� �����ϸ� �ȴ�.    yhj
	//temp = MobSelectTarget_Taming_or_Confused(npc);

	/* //  �ӽ÷� ���ֵ̹� npc�� ��ų�� ��� ���ϰ� ���´�.
	// �� ��ų ����
	temp = MobSelectSkill(npc, temp); */

	if ( temp && IS_NPC(temp) )
	{
		target_tamingNpc = TO_NPC(temp);
	}

	/*
	else if( temp && IS_PC(temp) )
	{
		// ���̸� Ÿ���� PC�� ��´�.
		target_for_heal = TO_PC(temp);
	}

	// ���̸� Ÿ�ٿ��� ��ų�� ����Ѵ�.
	if ( target_for_heal )
	{
		// ��ų�� �ٷ� ����Ѵ�.
		MobReadySkill(npc, target_for_heal);
		return;
	}

	else *///  �ӽ÷� ���ֵ̹� npc�� ��ų�� ��� ���ϰ� ���´�.

	if( target_tamingNpc && target_tamingNpc != npc)
	{
		// Ÿ���� ������ Ÿ���� ���� �̵�
		float dist = MobMoveTo(npc, GET_X(target_tamingNpc), GET_Z(target_tamingNpc), true, true, (CCharacter*)target_tamingNpc);

		if (dist <= 0.3f && npc->m_proto->CheckFlag(NPC_ATTACK) && npc->CanAttack())
		{
			// ���� ó��
			// ����������� AI���ú��� �ʱ�ȭ
			npc->InitAIVar();

			if (!npc->m_bStop)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeMoveMsg(rmsg, MSG_MOVE_STOP, npc);
				npc->m_bStop = true;
				SendToCell(rmsg, npc, false);
			}

			//  �ӽ÷� ���ֵ̹� npc�� ��ų�� ��� ���ϰ� ���´�.
			if (/*!MobReadySkill(npc, target_tamingNpc) && */gserver->m_pulse - npc->m_pulseAttack >= npc->m_attackSpeed * 15 / 10 )
			{
				npc->m_pulseAttack = gserver->m_pulse;
				ProcAttack((CCharacter *)npc, (CCharacter *)target_tamingNpc, npc->GetAttackType(NULL), NULL, 0);
			}
		}
	}
	// Ÿ���� ������ ���̹��� ĳ���͸� ���� �̵�
	else if ( owner )
	{
		MobMoveTo(npc, GET_X(owner), GET_Z(owner), true, false, owner);
		return ;
	}
}

void CArea::MobActivity_Confused(CNPC* npc)
{
	CNPC*	target_ConfusedNpc = NULL;	// ȥ�� ������ ���Ͱ� �븮�� ����
	CCharacter* temp = NULL;

	// ȥ�� ���¶��
	int nConfusing = npc->Check_MobFlag( STATE_MONSTER_CONFUSION );
	if ( nConfusing )
	{
		temp = MobSelectTarget_Taming_or_Confused(npc);

		// �� ��ų ����//  �ӽ÷� ȥ�� ������ npc�� ��ų�� ��� ���ϰ� ���´�.
		//temp = MobSelectSkill(npc, temp);
		if ( temp && IS_NPC(temp) )
		{
			target_ConfusedNpc = TO_NPC(temp);
		}
	}

	if( target_ConfusedNpc && target_ConfusedNpc != npc )
	{
		// Ÿ���� ������ Ÿ���� ���� �̵�
		float dist = MobMoveTo(npc, GET_X(target_ConfusedNpc), GET_Z(target_ConfusedNpc), true, true, target_ConfusedNpc);

		if (dist <= 0.3f && npc->m_proto->CheckFlag(NPC_ATTACK) && npc->CanAttack())
		{
			// ���� ó��
			// ����������� AI���ú��� �ʱ�ȭ
			npc->InitAIVar();

			if (!npc->m_bStop)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeMoveMsg(rmsg, MSG_MOVE_STOP, npc);
				npc->m_bStop = true;
				SendToCell(rmsg, npc, false);
			}

			//  �ӽ÷� ȥ�� ������ npc�� ��ų�� ��� ���ϰ� ���´�.
			if (/*!MobReadySkill(npc, target_ConfusedNpc) &&*/ gserver->m_pulse - npc->m_pulseAttack >= npc->m_attackSpeed * 15 / 10 )
			{
				npc->m_pulseAttack = gserver->m_pulse;
				ProcAttack((CCharacter *)npc, (CCharacter *)target_ConfusedNpc, npc->GetAttackType(NULL), NULL, 0);
			}
		}
	}

	// Ÿ���� ������ ���� �̵�
	else if ( !target_ConfusedNpc )
	{
		MobMoveRandom(npc);
	}
}

// nCount�� ���� Area���� npc�� npc�� ���� ��...yhj
void CArea::Monster_synchronization( int nCount )
{
	CNPC* npc = NULL;
	CNPC* tnpc = m_npcList;

	if ( nCount == 0 )
		return;

	if ( tnpc == NULL || tnpc->m_pArea == NULL )
		return;

	// npcList�� �˻��Ѵ�. �� �Ѹ��� �����ϰ� ������ ���´�.
	while ((npc = tnpc))
	{
		tnpc = npc->m_pNPCNext;

		if (npc == NULL)
			continue ;

		if ( npc->m_pArea == NULL )
			continue ;

		if ( npc->m_hp == 0 && npc->IsFlag(NPC_LORD_SYMBOL) == 0)
		{
			nCount--;
			// npc->m_pArea-> �̰ͺ��� this-> �̰� ������ ����... ������ �Ǹ� �ٲ���
			npc->m_pArea->m_nNPC_Killed_NPC = nCount;

			DelAttackList(npc);
			npc->m_pArea->CharFromCell(npc, true);
			npc->m_pArea->DelNPC(npc);
			break;
		}
	} // while ((npc = tnpc))

	// ���� ���� npc�� ���� �ִٸ� ��� �Լ� ȣ��
	// ���ÿ� �������� �����ϸ� NULL ������ �߻��Ͽ� ���� �ٿ� ��...
	if ( nCount > 0 )
	{
		if( tnpc && tnpc->m_pArea )
			tnpc->m_pArea->Monster_synchronization(nCount);
	}
}



void CArea::MobActivity_Mercenary(CNPC* npc)
{
	CPC*	owner = NULL;					// ���͸� ���̹��� ĳ����
	CCharacter * target_Attack = NULL;		// �뺴 ���Ͱ� �븮�� Ÿ��
	CCharacter * target_Heal = NULL;		// npc�� ���� ���ִ� PC(owner)
	CCharacter* temp = NULL;

	owner = npc->GetOwner();

	if( !owner )
		return;

	// �ֺ��� ������ Ÿ���� �����ϴ��� ���� Ȯ������.
	if( owner->GetSummonOwners_target() != NULL )
	{
		int i=0;
		for( i=0; i<MSG_CHAR_APET+1 ; i++)
		{
			temp = owner->m_pArea->FindChar( owner->GetSummonOwners_target()->m_index, (__tagMsgCharType)i );
			if( temp )
				break;
		}
	}

	if( temp==NULL )
	{
		owner->SetSummonOwners_target(NULL);
	}


	if (owner == NULL
			|| ( owner && ( owner->m_hp <= 0 || GetDistance((CCharacter*)owner, (CCharacter*)npc) >= 50.0f )) )
	{
		if( owner )
			owner->SummonNpcRemove(npc, true);
		return;
	}

	temp = MobSelectSkill(npc, temp);

	if( temp && IS_PC(temp)  )
	{
		if( npc->GetOwner() == TO_PC(temp) ) // ������ �ڰ� �����̸� �����ش�.
			target_Heal = temp;
		else
			target_Attack = temp;
	}
	else
		target_Attack = temp;

	// ���̸� Ÿ�ٿ��� ��ų�� ����Ѵ�.
	if ( target_Heal )
	{
		// ��ų�� �ٷ� ����Ѵ�.
		MobReadySkill(npc, target_Heal);
		return;
	}

	if( target_Attack && target_Attack != npc)
	{
		// Ÿ���� ������ Ÿ���� ���� �̵�
		float dist = MobMoveTo(npc, GET_X(target_Attack), GET_Z(target_Attack), true, true, target_Attack);

		if (dist <= 0.3f && npc->m_proto->CheckFlag(NPC_ATTACK) && npc->CanAttack())
		{
			// ���� ó��
			// ����������� AI���ú��� �ʱ�ȭ
			npc->InitAIVar();

			if (!npc->m_bStop)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeMoveMsg(rmsg, MSG_MOVE_STOP, npc);
				npc->m_bStop = true;
				SendToCell(rmsg, npc, false);
			}

			if ( !MobReadySkill(npc, target_Attack) && gserver->m_pulse - npc->m_pulseAttack >= npc->m_attackSpeed * 15 / 10 )
			{
				npc->m_pulseAttack = gserver->m_pulse;
				ProcAttack((CCharacter *)npc, target_Attack, npc->GetAttackType(NULL), NULL, 0);
			}
		}
	}
	// Ÿ���� ������ ���̹��� ĳ���͸� ���� �̵�
	else if ( owner  && GetDistance((CCharacter*)owner,(CCharacter*)npc) > 3.0f)
	{
		float fRand = GetRandom(0,100)%2 ? 1.0f : -1.0f ;
		float x  = GET_X(owner) + 3.0f * fRand + ((float)(GetRandom( 0 , 200 ) / 100.0f) );
		fRand = GetRandom(0,100)%2 ? 1 : -1 ;
		float z  = GET_Z(owner) + 3.0f * fRand + ((float)(GetRandom( 0 , 200 ) / 100.0f) );

		MobMoveTo(npc, x, z, true, false, owner);
		return ;
	}
}

void CArea::MobActivity_Totem(CNPC *npc)
{

	CPC* owner = npc->GetOwner();

	if (owner == NULL || ( owner && (owner->m_hp <= 0 || GetDistance((CCharacter*)owner, (CCharacter*)npc) >= 100.0f ) ))
	{
		if( owner && owner->GetSummonNpc(npc))
			owner->SummonNpcRemove(npc, true);
		return;
	}

	if( npc->m_currentSkill ) // ��ų�� ������̸�
		return;

	if( npc->Check_MobFlag(STATE_MONSTER_TOTEM_BUFF))
	{
		if ( !(	npc->m_skills[0] && (npc->m_skills[0]->m_proto->m_flag & SF_HELP)
				&& npc->m_skills[0]->IsReady(npc) && npc->CanSpell()))
			return;
	}

	if( npc->Check_MobFlag(STATE_MONSTER_TOTEM_ATTK))
	{
		if ( !(	npc->m_skills[0] && (npc->m_skills[0]->m_proto->m_flag & SF_NOTHELP)
				&& npc->m_skills[0]->IsReady(npc) && npc->CanSpell()))
			return;
	}

	CCharacter * pTarget = NULL;

	pTarget = (CCharacter*)owner;
	if( npc->m_hp > npc->m_skills[0]->m_proto->Level(npc->m_skills[0]->m_level)->m_needHP
			&& npc->m_mp > npc->m_skills[0]->m_proto->Level(npc->m_skills[0]->m_level)->m_needMP
			&& pTarget->CanApplySkill(npc->m_skills[0]->m_proto, npc->m_skills[0]->m_proto->Level(npc->m_skills[0]->m_level)) )
	{
		npc->m_currentSkill = npc->m_skills[0];
		MobReadySkill(npc, npc);
	}
}

void CArea::MobActivity_Suicide(CNPC *npc)
{
	if( npc->m_currentSkill && npc->m_currentSkill->m_state != SKILL_CON_NORMAL )
		return;

	CPC * owner = npc->GetOwner();

	if( !owner || ( owner && ( DEAD(owner) || GetDistance((CCharacter*)owner,(CCharacter*)npc) >= 100.0f ) ) )
	{
		if( owner )
			owner->SummonNpcRemove(npc, true);

		npc->m_hp = 0;
		return;
	}
	float dist = 20.0f;
	CCharacter * target = npc->m_pArea->FindNearestTarget(npc, &dist );

	if( target )
	{
		npc->m_currentSkill = npc->m_skills[0];
		npc->m_currentSkill->m_targetIndex = target->m_index;
		npc->m_currentSkill->m_targetType = target->m_type;
		npc->m_currentSkill->m_state = SKILL_CON_READY;

		dist = GetDistance( (CCharacter*)npc, (CCharacter*)target);
		if( dist > npc->m_skills[0]->m_proto->m_appRange ) // ��ų ����ȿ�⸮���� ª���� �i�ư���.
		{
			MobMoveTo(npc, GET_X(target), GET_Z(target), true, false, target);
		}
		return;
	}
	else if( owner )// Ÿ���� ������ ���ƴ���~
	{
		float fRand = GetRandom(0,100)%2 ? 1.0f : -1.0f ;
		float x  = GET_X(npc->GetOwner()) + ( fRand * ((float)(GetRandom( 500 , 1000 ) / 100.0f)) );
		fRand = GetRandom(0,100)%2 ? 1.0f : -1.0f ;
		float z  = GET_Z(npc->GetOwner()) + ( fRand * ((float)(GetRandom( 500 , 1000 ) / 100.0f)) );

		MobMoveTo(npc, x, z, true, false, npc->GetOwner());
		return;
	}
}

void CArea::MobActivity_Item_Totem(CNPC *npc)
{
	if(npc == NULL)
		return ;

	CPC* owner = npc->GetOwner();

	if(owner == NULL)
		return ;

	if( owner->m_hp <= 0 || GetDistance((CCharacter*)owner, (CCharacter*)npc) >= 100.0f  )
	{
		if( owner->GetSummonNpc(npc) )
		{
			owner->SummonNpcRemove(npc, true);

			//���ο��� ������� �˷��ش�. (Disappear ��Ŷ�� �̿��ؼ�)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				DisappearMsgForClientEffect(rmsg, npc, owner->m_index);
				SEND_Q(rmsg, owner->m_desc);
			}
		}
		return;
	}

	if( npc->m_currentSkill ) // ��ų�� ������̸�
		return;

	////
	CCharacter * pTarget = NULL;
	pTarget = (CCharacter*)owner;

	int skillindex = -1;
	int i;
	
	for (i = 0; i < MAX_NPC_SKILL; i++)
	{
		int skillprob = GetRandom(1, 10000);
		// ��ų ��� ���� �˻�
		if (npc->m_skills[i]
		&& npc->m_proto->m_skillProb[i] >= skillprob
			&& npc->m_skills[i]->IsReady(npc)
			&& npc->CanSpell()
			&& npc->m_hp > npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)->m_needHP
			&& npc->m_mp > npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)->m_needMP
			&& pTarget->CanApplySkill(npc->m_skills[i]->m_proto, npc->m_skills[i]->m_proto->Level(npc->m_skills[i]->m_level)))
		{
			skillindex = i;
			break;
		}
	}
	
	if (skillindex >= 0)
	{
		npc->m_currentSkill = npc->m_skills[skillindex];
		/*npc->m_currentSkill->m_targetType = pTarget->m_type;
		npc->m_currentSkill->m_targetIndex = pTarget->m_index;*/
		MobReadySkill(npc, npc);
	}
}

/*
bool MobProcSkillMercenary(CNPC *npc)
{
	// ���� ��ų ������ΰ�
	if (!npc->m_currentSkill )
		return false;

	if( !npc->GetOwner() )
		return false;

	CNetMsg::SP rmsg(new CNetMsg);
	bool bSkip = false;
}
*/

bool MobProcSkillTotem_Buff(CNPC *npc)
{
	// ���� ��ų ������ΰ�
	if (!npc->m_currentSkill )
		return false;

	if( !npc->GetOwner() )
		return false;

	bool bSkip = false;

	switch( npc->m_currentSkill->m_state )
	{
	case SKILL_CON_READY:
		try
		{
			// ��ų ����->���̾� �˻�
			if (npc->m_currentSkill->m_usetime + npc->m_currentSkill->m_proto->m_readyTime + npc->m_currentSkill->m_proto->m_stillTime <= gserver->m_pulse)
			{
				// hp, mp �˻�
				if (npc->m_hp <= npc->m_currentSkill->m_proto->Level(npc->m_currentSkill->m_level)->m_needHP
						|| npc->m_mp <= npc->m_currentSkill->m_proto->Level(npc->m_currentSkill->m_level)->m_needMP)
					throw 0;

				CPC* owner = npc->GetOwner();
				int	mcount = npc->m_currentSkill->m_proto->m_levelproto[npc->m_currentSkill->m_level - 1]->m_targetNum ;

				boost::scoped_array<MultiTarget> multitarget(new MultiTarget[mcount]);

				bool bApply;
				int i;

				if( owner->m_party == NULL && owner->m_Exped == NULL)
				{
					mcount = 0;
					float dist = GetDistance((CCharacter*)npc, (CCharacter*)owner);
					if( dist <= npc->m_currentSkill->m_proto->m_appRange )
					{
						multitarget[mcount].mtarget			= (CCharacter*)owner;
						multitarget[mcount].mdist			= dist;
						multitarget[mcount].mtargettype		= owner->m_type;
						multitarget[mcount].mtargetindex	= owner->m_index;
						mcount++;
					}

					// �ֵ� ����
					if( owner->GetAPet() )
					{
						dist = GetDistance((CCharacter*)npc, (CCharacter*)owner->GetAPet());
						if( dist <= npc->m_currentSkill->m_proto->m_appRange )
						{
							multitarget[mcount].mtarget			= (CCharacter*)owner->GetAPet();
							multitarget[mcount].mdist			= dist;
							multitarget[mcount].mtargettype		= owner->GetAPet()->m_type;
							multitarget[mcount].mtargetindex	= owner->GetAPet()->m_index;
							mcount++;
						}
					}

					// ��ȯ�ּ��� ����
					if( owner->m_job == JOB_SORCERER )
					{
						CElemental* elemental = owner->m_elementalList;
						while (elemental)
						{
							dist = GetDistance((CCharacter*)npc, (CCharacter*)elemental);
							if( dist <= npc->m_currentSkill->m_proto->m_appRange )
							{
								multitarget[mcount].mtarget			= (CCharacter*)elemental;
								multitarget[mcount].mdist			= dist;
								multitarget[mcount].mtargettype		= elemental->m_type;
								multitarget[mcount].mtargetindex	= elemental->m_index;
								mcount++;
							}
							elemental = elemental->m_nextElemental;
						}
					}
				}
				else if( owner->m_party || owner->m_Exped )// ��Ƽ������ ��� ������ �Ѹ���.
				{
					int realCount = 0;
					int nCount;
					int n, j;
					int group = -1;

					if( owner->m_party )
					{
						nCount = MAX_PARTY_MEMBER;
						group = -1;
					}

					if( owner->m_Exped )
					{
						nCount = MAX_EXPED_GMEMBER;
						group = owner->m_Exped->FindMemberGroupIndex(owner->m_index);
						if( group == -1 )
							return true;
					}

					for (n = 0; n < nCount ; n++)
					{
						const CPartyMember* pPartyMember = NULL;
						CExpedMember * pExpedMember = NULL;
						CPC * pPC = NULL;

						if( owner->m_party  )
						{
							pPartyMember = owner->m_party->GetMemberByListIndex(n);
							if( !pPartyMember )
								continue;
							pPC = pPartyMember->GetMemberPCPtr();
						}

						if( owner->m_Exped )
						{
							pExpedMember = owner->m_Exped->GetMemberByListIndex(group, n);
							if( !pExpedMember )
								continue;
							pPC = pExpedMember->GetMemberPCPtr();
						}

						if( pPC )
						{
							float dist = GetDistance((CCharacter*)npc, (CCharacter*)pPC);
							if( dist <= npc->m_currentSkill->m_proto->m_appRange )
							{
								for(i=0; i<mcount; i++)
								{
									if( multitarget[i].mdist >= dist )
									{
										for(j=mcount-1; j>i; j--)
										{
											multitarget[j].mtarget		= multitarget[j-1].mtarget;
											multitarget[j].mtargetindex	= multitarget[j-1].mtargetindex;
											multitarget[j].mtargettype	= multitarget[j-1].mtargettype;
											multitarget[j].mdist		= multitarget[j-1].mdist;
										}
										multitarget[i].mtarget		= (CCharacter*)pPC;
										multitarget[i].mtargetindex	= pPC->m_index;
										multitarget[i].mtargettype	= pPC->m_type;
										multitarget[i].mdist		= dist;
										realCount ++;
										break;
									}
								}
							}
							// �ֵ� ����
							if( pPC->GetAPet() )
							{
								dist = GetDistance((CCharacter*)npc, (CCharacter*)pPC->GetAPet());
								if( dist <= npc->m_currentSkill->m_proto->m_appRange )
								{
									for(i=0; i<mcount; i++)
									{
										if( multitarget[i].mdist >= dist )
										{
											for(j=mcount-1; j>i; j--)
											{
												multitarget[j].mtarget		= multitarget[j-1].mtarget;
												multitarget[j].mtargetindex	= multitarget[j-1].mtargetindex;
												multitarget[j].mtargettype	= multitarget[j-1].mtargettype;
												multitarget[j].mdist		= multitarget[j-1].mdist;
											}
											multitarget[i].mtarget		= (CCharacter*)pPC->GetAPet();
											multitarget[i].mtargetindex	= pPC->GetAPet()->m_index;
											multitarget[i].mtargettype	= pPC->GetAPet()->m_type;
											multitarget[i].mdist		= dist;
											realCount ++;
											break;
										}
									}
								}
							}

							// ��ȯ�ּ��� ����
							if( pPC->m_job == JOB_SORCERER )
							{
								CElemental* elemental = pPC->m_elementalList;
								while (elemental)
								{
									dist = GetDistance((CCharacter*)npc,(CCharacter*)elemental);
									if( dist <= npc->m_currentSkill->m_proto->m_appRange )
									{
										for(i=0; i<mcount; i++)
										{
											if( multitarget[i].mdist >= dist )
											{
												for(j=mcount-1; j>i; j--)
												{
													multitarget[j].mtarget		= multitarget[j-1].mtarget;
													multitarget[j].mtargetindex	= multitarget[j-1].mtargetindex;
													multitarget[j].mtargettype	= multitarget[j-1].mtargettype;
													multitarget[j].mdist		= multitarget[j-1].mdist;
												}
												multitarget[i].mtarget		= (CCharacter*)elemental;
												multitarget[i].mtargetindex	= elemental->m_index;
												multitarget[i].mtargettype	= elemental->m_type;
												multitarget[i].mdist		= dist;
												realCount ++;
												break;
											}
										}
									}
									elemental = elemental->m_nextElemental;
								}
							}
						}
					}
					if( realCount <= mcount )
						mcount = realCount;
				}
				else
					return true;

				if( mcount > 0)
				{
					#ifdef SOUL_BUFF_ONLY_OWNER
					// wizard - 1145
					// witch - 1146
					if (npc->m_currentSkill->m_proto->m_index == 1145 ||
						npc->m_currentSkill->m_proto->m_index == 1146) {
						
						npc->m_currentSkill->Fire();

						{
							boost::scoped_array<MultiTarget> temp(new MultiTarget[0]);
							CNetMsg::SP rmsg(new CNetMsg);
							ResponseClient::makeSkillFireMsg(rmsg, npc, npc->m_currentSkill, (CCharacter*)owner, 0, temp.get(), 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
							npc->m_pArea->SendToCell(rmsg, npc, false);
						}

						ApplySkill(npc, (CCharacter*)owner, npc->m_currentSkill, -1, bApply);

					} else 
					#endif
					{
						npc->m_currentSkill->Fire();

						{
							CNetMsg::SP rmsg(new CNetMsg);
							ResponseClient::makeSkillFireMsg(rmsg, npc, npc->m_currentSkill, (CCharacter*)owner, mcount, multitarget.get(), 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
							npc->m_pArea->SendToCell(rmsg, npc, false);
						}

						// ��ų ����.
						for(i=0; i<mcount; i++)
						{
							ApplySkill(npc, multitarget[i].mtarget, npc->m_currentSkill, -1, bApply);
						}
					}
				}

				break;
			}
		}
		catch (...)
		{
			npc->m_currentSkill->Cancel(npc);
			npc->m_currentSkill = NULL;

			{
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeSkillCancelMsg(rmsg, npc);
				npc->m_pArea->SendToCell(rmsg, npc, false);
			}
		}
		bSkip = true;
		break;

	case SKILL_CON_FIRE:
		if (npc->m_currentSkill->m_usetime + npc->m_currentSkill->m_proto->m_readyTime + npc->m_currentSkill->m_proto->m_stillTime + npc->m_currentSkill->m_proto->m_fireTime <= gserver->m_pulse)
		{
			npc->m_currentSkill->Cancel(npc);
			npc->m_currentSkill = NULL;
			npc->m_aipulse = gserver->m_pulse;
			npc->m_delay = NPC_ACTIVITY_DELAY;
		}
		else
			bSkip = true;

		break;
	}

	return bSkip;
}

bool MobProcSkillTrap_Attk(CNPC *npc)
{
	if (npc->GetOwner() == NULL		// ���� ����.
			|| (npc->GetOwner()
				&& ( npc->GetOwner()->m_hp <= 0
					 || GetDistance((CCharacter*)npc->GetOwner(), (CCharacter*)npc) >= 100.0f
				   )
			   )
	   )
	{
		if( npc->GetOwner() )
			npc->GetOwner()->SummonNpcRemove(npc);
		return true;
	}

	if( !npc->m_currentSkill ) // ���� ����
	{
		npc->m_currentSkill = npc->m_skills[0];
		npc->m_currentSkill->m_targetIndex = npc->m_index;
		npc->m_currentSkill->m_targetType = npc->m_type;
		npc->m_currentSkill->m_state = SKILL_CON_READY;
	}

	switch( npc->m_currentSkill->m_state )
	{
	case SKILL_CON_NORMAL:
	case SKILL_CON_READY:
		try
		{
			// ��ų ����->���̾� �˻�
			if (npc->m_currentSkill->m_usetime + npc->m_currentSkill->m_proto->m_readyTime + npc->m_currentSkill->m_proto->m_stillTime <= gserver->m_pulse)
			{
				// hp, mp �˻�
				if (npc->m_hp <= npc->m_currentSkill->m_proto->Level(npc->m_currentSkill->m_level)->m_needHP
						|| npc->m_mp <= npc->m_currentSkill->m_proto->Level(npc->m_currentSkill->m_level)->m_needMP)
					throw 0;

				int	mcount = npc->m_currentSkill->m_proto->m_levelproto[npc->m_currentSkill->m_level - 1]->m_targetNum ; // ���� ���ɼ��� 10��
				boost::scoped_array<MultiTarget> multitarget(new MultiTarget[mcount]);
				mcount = GetSummonNpcMultiTarget(npc, multitarget.get(), mcount);

				if( mcount > 0)
				{
					{
						CNetMsg::SP rmsg(new CNetMsg);
						ResponseClient::makeSkillReadyMsg(rmsg, npc, npc->m_currentSkill, npc);
						npc->m_pArea->SendToCell(rmsg, npc, false);
					}

					{
						npc->m_currentSkill->Fire();
						CNetMsg::SP rmsg(new CNetMsg);
						ResponseClient::makeSkillFireMsg(rmsg, npc, npc->m_currentSkill, (CCharacter*)npc, mcount, multitarget.get(), 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
						npc->m_pArea->SendToCell(rmsg, npc, false);
					}

					// ��ų ����
					bool bApply = false;
					for(int i = 0; i < mcount; i++)
					{
						if (multitarget[i].mtarget == NULL)
							continue;

						if (multitarget[i].mtarget->m_index <= 0)
							continue;

						ApplySkill(npc, multitarget[i].mtarget, npc->m_currentSkill, -1, bApply);
					}
					npc->GetOwner()->SummonNpcRemove(npc);

					return true;
				}
			}
		}
		catch (...)
		{
			npc->m_currentSkill->Cancel(npc);
			npc->m_currentSkill = NULL;
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeSkillCancelMsg(rmsg, npc);
			npc->m_pArea->SendToCell(rmsg, npc, false);
		}
		break;

	case SKILL_CON_FIRE:
		if (npc->m_currentSkill->m_usetime + npc->m_currentSkill->m_proto->m_readyTime + npc->m_currentSkill->m_proto->m_stillTime + npc->m_currentSkill->m_proto->m_fireTime <= gserver->m_pulse)
		{
			npc->m_currentSkill->Cancel(npc);
			npc->m_currentSkill = NULL;
			npc->m_aipulse = gserver->m_pulse;
			npc->m_delay = NPC_ACTIVITY_DELAY;
		}
		return true;
	}
	return true;
}

bool MobProcSkillSuicide_Attk(CNPC *npc)
{
	if( !npc->m_currentSkill )
		return false;

	if( npc->m_currentSkill->m_state == SKILL_CON_NORMAL  )
		return false;

	bool bSkip = false;
	switch( npc->m_currentSkill->m_state )
	{
	case SKILL_CON_READY:
		try
		{
			// ��ų ����->���̾� �˻�
			if (npc->m_currentSkill->m_usetime + npc->m_currentSkill->m_proto->m_readyTime + npc->m_currentSkill->m_proto->m_stillTime <= gserver->m_pulse)
			{
				// hp, mp �˻�
				if (npc->m_hp <= npc->m_currentSkill->m_proto->Level(npc->m_currentSkill->m_level)->m_needHP
						|| npc->m_mp <= npc->m_currentSkill->m_proto->Level(npc->m_currentSkill->m_level)->m_needMP)
					throw 0;

				int	mcount = npc->m_currentSkill->m_proto->m_levelproto[npc->m_currentSkill->m_level - 1]->m_targetNum ; // ���� ���ɼ��� 10��
				boost::scoped_array<MultiTarget> multitarget(new MultiTarget[mcount]);
				mcount = GetSummonNpcMultiTarget(npc, multitarget.get(), mcount);

				if( mcount > 0)
				{
					{
						CNetMsg::SP rmsg(new CNetMsg);
						ResponseClient::makeSkillReadyMsg(rmsg, npc, npc->m_currentSkill, npc);
						npc->m_pArea->SendToCell(rmsg, npc, false);
					}

					npc->m_currentSkill->Fire();

					{
						CNetMsg::SP rmsg(new CNetMsg);
						ResponseClient::makeSkillFireMsg(rmsg, npc, npc->m_currentSkill, (CCharacter*)npc, mcount, multitarget.get(), 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
						npc->m_pArea->SendToCell(rmsg, npc, false);
					}

					// ��ų ����.
					bool bApply = false;
					int i;
					for(i=0; i<mcount; i++)
					{
						if( multitarget[i].mtarget )
							ApplySkill(npc, multitarget[i].mtarget, npc->m_currentSkill, -1, bApply);
					}
					npc->GetOwner()->SummonNpcRemove(npc);
					bSkip = true;
				}
				else
				{
					npc->m_currentSkill->Ready(NULL);
					npc->m_currentSkill->m_state = SKILL_CON_NORMAL;
					npc->m_currentSkill = NULL;
				}
			}
		}
		catch (...)
		{
			npc->m_currentSkill->Cancel(npc);
			npc->m_currentSkill->m_state = SKILL_CON_NORMAL;
			npc->m_currentSkill = NULL;
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeSkillCancelMsg(rmsg, npc);
			npc->m_pArea->SendToCell(rmsg, npc, false);
		}
		break;

	case SKILL_CON_FIRE:
		if (npc->m_currentSkill->m_usetime + npc->m_currentSkill->m_proto->m_readyTime + npc->m_currentSkill->m_proto->m_stillTime + npc->m_currentSkill->m_proto->m_fireTime <= gserver->m_pulse)
		{
			npc->m_currentSkill->Cancel(npc);
			npc->m_currentSkill = NULL;
			npc->m_aipulse = gserver->m_pulse;
			npc->m_delay = NPC_ACTIVITY_DELAY;
		}
		bSkip =  true;
		break;
	}
	return bSkip;
}

bool MobProcSkillItemTotem_Buff(CNPC *npc)
{
	return true;
}

int GetSummonNpcMultiTarget(CNPC* npc, MultiTarget *multitarget, int mcount)
{
	if( !npc->GetOwner())
		return 0;

	int x, z;
	int sx = npc->m_cellX - CELL_EXT;
	int ex = npc->m_cellX + CELL_EXT;
	int sz = npc->m_cellZ - CELL_EXT;
	int ez = npc->m_cellZ + CELL_EXT;

	CPC* owner = npc->GetOwner();
	int realCount = 0;

	for (x = sx; x <= ex; x++)
	{
		if (x < 0 || x >= npc->m_pArea->m_size[0]) continue;

		for (z = sz; z <= ez; z++)
		{
			if (z < 0 || z >= npc->m_pArea->m_size[1]) continue;

			CCharacter *pChar;
			CCharacter *pCharNext = npc->m_pArea->m_cell[x][z].m_listChar;

			while ((pChar = pCharNext))
			{
				pCharNext = pCharNext->m_pCellNext;

				if ( pChar == NULL || DEAD(pChar) )
					break;

				if( pChar->m_index < 0)
					continue;

				CPC *ptowner = NULL;
				if( IS_PC(pChar) )
					ptowner = TO_PC(pChar);
				else if( IS_PET(pChar) )
					ptowner = TO_PET(pChar)->GetOwner();
				else if( IS_APET(pChar) )
				{
					if( ! TO_APET(pChar)->IsProtoFlag( APET_FLAG_ATTACK ) )
						continue;
					ptowner = TO_APET(pChar)->GetOwner();
				}
				else if( IS_ELEMENTAL(pChar) )
					ptowner = TO_ELEMENTAL(pChar)->GetOwner();
				else if( IS_NPC(pChar) )
				{
					if( npc == TO_NPC(pChar))
						continue;

					if (npc->m_proto->CheckFlag(NPC_ZONEMOVER | NPC_REFINER | NPC_QUEST | NPC_REMISSION | NPC_EVENT | NPC_LORD_SYMBOL)
						&& !npc->m_bScriptedMovement)
					{
						// Skip non-scripted special-proto NPCs (SHOPPER, ZONEMOVER, etc.) without verbose logging to avoid spam
						// Skip non-scripted special-proto NPCs (ZONEMOVER, REFINER, etc.) without verbose logging to avoid spam
						continue;
					}

					if( TO_NPC(pChar)->GetOwner() && TO_NPC(pChar)->GetOwner()->GetSummonNpc(TO_NPC(pChar)) )
						ptowner = TO_NPC(pChar)->GetOwner();
				}

				if( ptowner && ptowner ==  owner)
					continue;

				bool bTarget = false;

				float tdist = GetDistance((CCharacter*)npc, pChar);
				// ���� �����Ѱ� �����ΰ�?
				if( pChar != npc && !DEAD(pChar) && pChar != (CCharacter*)owner
						&& ABS(GET_YLAYER(pChar) - GET_YLAYER(npc)) <= 1
						&& tdist <= npc->m_currentSkill->m_proto->m_appRange )
				{
					int zoneindex = owner->m_pZone->m_index;
					CWarCastle* castle = CWarCastle::GetCastleObject(zoneindex);

					if( castle != NULL && castle->GetState() != WCSF_NORMAL // ���� ���̰�
							&& owner->GetMapAttr() & MATT_WAR  // ���� �����̰�
							&& ( IS_ATTACK_TEAM( owner->GetJoinFlag( owner->m_pZone->m_index ) )
								 || IS_DEFENSE_TEAM( owner->GetJoinFlag( owner->m_pZone->m_index ) ) ) ) // ���ʰ� ������ ������ �ִٸ�
					{
						if( IS_ATTACK_TEAM(owner->GetJoinFlag( owner->m_pZone->m_index) ) )// ���� ���̶��
						{
							if( ptowner)
							{
								if( IS_DEFENSE_TEAM( ptowner->GetJoinFlag(owner->m_pZone->m_index))  )
									bTarget =true;
							}
							else if( IS_NPC(pChar))
							{
								if( !TO_NPC(pChar)->m_proto->CheckFlag(NPC_LORD_SYMBOL) && TO_NPC(pChar)->m_proto->CheckFlag(NPC_WARCASTLE) )
									bTarget = true;
							}
						}
						else if(IS_DEFENSE_TEAM( owner->GetJoinFlag(owner->m_pZone->m_index) ) ) // ���� ���̶��
						{
							if( ptowner )
							{
								if( IS_ATTACK_TEAM( ptowner->GetJoinFlag(owner->m_pZone->m_index) ) )
								{
									if( IS_NPC(pChar)
											&& (TO_NPC(pChar)->Check_MobFlag(STATE_MONSTER_TOTEM_BUFF) ||TO_NPC(pChar)->Check_MobFlag(STATE_MONSTER_TOTEM_ATTK)) )
										continue;

									bTarget =true;
								}
							}
						}
						else if( ptowner && ( IsRaList(owner, ptowner) || IsRaList(ptowner, owner) ))
							bTarget = true;
						else if( ptowner && owner->IsSetPlayerState( PLAYER_STATE_PKMODE) && ptowner->IsSetPlayerState(PLAYER_STATE_PKMODE ))
							bTarget = true;
					}
					else if( ptowner && ( IsRaList(owner, ptowner) || IsRaList(ptowner, owner) ))
					{
						if( IS_NPC(pChar)
								&& (TO_NPC(pChar)->Check_MobFlag(STATE_MONSTER_TOTEM_BUFF) ||TO_NPC(pChar)->Check_MobFlag(STATE_MONSTER_TOTEM_ATTK) ))
							continue;

						bTarget = true;
					}
					else if( ptowner && owner->IsSetPlayerState( PLAYER_STATE_PKMODE) && ptowner->IsSetPlayerState(PLAYER_STATE_PKMODE ))
						bTarget = true;
					else if (IS_NPC(pChar) && !ptowner)
					{
						if( TO_NPC(pChar)->m_proto->CheckFlag(NPC_CASTLE_TOWER | NPC_GUARD | NPC_CASTLE_GUARD)
								|| TO_NPC(pChar)->m_idNum==491
						  ) // ���� �޺����� �ٴ� ���̹����� ����
							continue;
						bTarget = true;
					}

					if( bTarget )
					{
						int i,j;

						for(i=0; i<mcount; i++)
						{
							if( multitarget[i].mdist >= tdist )
							{
								for(j=mcount-1; j>i; j--)
								{
									multitarget[j].mtarget		= multitarget[j-1].mtarget;
									multitarget[j].mtargetindex	= multitarget[j-1].mtargetindex;
									multitarget[j].mtargettype	= multitarget[j-1].mtargettype;
									multitarget[j].mdist		= multitarget[j-1].mdist;
								}
								multitarget[i].mtarget		= pChar;
								multitarget[i].mtargetindex	= pChar->m_index;
								multitarget[i].mtargettype	= pChar->m_type;
								multitarget[i].mdist		= tdist;
								realCount ++;
								break;
							}
						}
					}
				}
			}
		}
	}

	if( mcount < realCount )
		realCount = mcount;

	return realCount;
}
