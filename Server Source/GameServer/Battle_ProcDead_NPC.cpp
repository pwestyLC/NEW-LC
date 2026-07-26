#include <boost/assign/list_of.hpp>
#include "stdhdrs.h"

#include "Server.h"
#include "Battle.h"
#include "WarCastle.h"
#include "CmdMsg.h"
#include "Log.h"
#include "doFunc.h"
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
#include "CloudThings.h"
#endif

void ProcDead_PD2(CNPC* df);
void ProcDead_RVR(CPC* op, CNPC* df);
#ifdef PARTY_QUEST_ITEM_BUG_
void ProcDeadQuestProc(CPC * opc,CNPC * df, int partyScale); //[2009/12/28 derek] ��Ÿ ģ�Ѱ� ������ ���� �س��� �ٸ� ���� ��� ����Ʈ �˻��� ���� �ʾƼ� ����Ʈ ó���κ��� �Լ��� ����.
#endif
#ifdef BATTLE_PASS_SYSTEM
void ProcDeadBattlePass(CPC* op, CNPC* df);
#endif

extern bool do_ItemUsePotion(CPC* ch, CItem* item, int extra1);

void ProcDead(CNPC* df, CCharacter* of)
{
	CPC*		opc				= NULL;
	CNPC*		onpc			= NULL;
	CPet*		opet			= NULL;
	CElemental*	oelemental		= NULL;
	CAPet*		oapet			= NULL;

	bool bNPCKilledNPC = false; // npc�� npc�� ���� ��� �� �̰��� true�� ������Ѵ�.

	switch (of->m_type)
	{
	case MSG_CHAR_PC:
		opc = TO_PC(of);
		if (opc == NULL)
			goto END_PROC;
		break;

	case MSG_CHAR_NPC:
		onpc = TO_NPC(of);
		break;

	case MSG_CHAR_PET:
		opet = TO_PET(of);
		opc = opet->GetOwner();
		if (opc == NULL)
			goto END_PROC;
		break;

	case MSG_CHAR_ELEMENTAL:
		oelemental = TO_ELEMENTAL(of);
		opc = oelemental->GetOwner();
		if (opc == NULL)
			goto END_PROC;
		break;
	case MSG_CHAR_APET:
		oapet	= TO_APET(of);
		opc		= oapet->GetOwner();
		if( opc == NULL )
			goto END_PROC;
		break;

	default:
		goto END_PROC;
	}
#ifdef SYSTEM_TREASURE_MAP
//	if( df->m_idNum == TREASURE_BOX_NPC_INDEX)	 // �������� npc�� ��Ҵ�. ������ ��������.
//		df->m_pZone->RemoveTreasureBoxNpc(df );
#endif

	// ���ֱ��� ����Ʈ (�۽��� ���� 2) ����
	ProcDead_PD2(df);

	// ���� ���� ���̹� ������ ���
	if (df->Check_MobFlag( STATE_MONSTER_TAMING ) )
	{
		CPC* owner = NULL;			// ���͸� ���̹��� ĳ����
		owner = df->GetOwner();		// ���Ͱ� ���̹� �Ǿ����� Ȯ��

		// ������ �����ϰ� �ִ� Ÿ���� �����ش�. ������ ���̹� ���� �ƴѰɷ� �ٲ��ش�.
		if ( owner )
		{
			owner->DeleteSlave( df );
		}
		goto SKIP_DROP;
	}

	// ���� ���� ���̹� ������ ���
	if (onpc && onpc->Check_MobFlag( STATE_MONSTER_TAMING ) )
	{
		CPC* owner = NULL;				// ���͸� ���̹��� ĳ����
		owner = onpc->GetOwner();		// ���Ͱ� ���̹� �Ǿ����� Ȯ��

		// ������ �����ϰ� �ִ� Ÿ���� �����ش�.
		if ( owner )
		{
			owner->SetOwners_target(NULL);
			// opc�� ������ �־��ش�.
			opc = owner;
			bNPCKilledNPC = true;
		}
		else
			goto SKIP_DROP;
	}
	else if( onpc && onpc->GetOwner() ) // ������ NPC�� ���ʰ� �ִٸ�
	{
		CNPC* sumNpc = onpc->GetOwner()->GetSummonNpc(onpc);
		if( sumNpc )
		{
			if( sumNpc->Check_MobFlag((STATE_MONSTER_MERCENARY)) )
			{
				sumNpc->GetOwner()->SetSummonOwners_target(NULL);
			}

			opc = onpc->GetOwner();
			bNPCKilledNPC = true;
		}
		else
			goto SKIP_DROP;
	}

	if( df && df->GetOwner() ) // ���� ���� owner �ִٸ�
	{
		if( df->Check_MobFlag(STATE_MONSTER_PARASITE) ) // �з�����Ʈ�� �ɷ��ִٸ�.
		{
			int parasiteCnt = GetRandom(0,3);
			parasiteCnt -= df->GetOwner()->GetBombSummonCont();
			if( parasiteCnt > 0 )
			{
				int parasiteIdx = df->m_assist.GetSummonNpcIndex();
				if( parasiteIdx > 0 )
				{
					int i;
					for(i=0; i<parasiteCnt; i++)
					{
						CNPC* pParasiteNPC;
						pParasiteNPC = gserver->m_npcProtoList.Create(parasiteIdx, NULL );
						if( pParasiteNPC == NULL )
							continue;

						GET_X(pParasiteNPC) = GET_X(df);
						GET_Z(pParasiteNPC) = GET_Z(df);
						GET_R(pParasiteNPC) = GET_R(df);
						GET_YLAYER(pParasiteNPC) = GET_YLAYER(df);

						float fRand = GetRandom(0,1) ? 1.0f : -1.0f ;
						float x  = 2.0f + ( fRand * (float)(GetRandom( 0 , 200 ) / 100.0f) );
						fRand = GetRandom(0,1) ? 1 : -1 ;
						float z  = 2.0f + ( fRand * (float)(GetRandom( 0 , 200 ) / 100.0f) );

						pParasiteNPC->m_regenX = GET_X(pParasiteNPC) += x;
						pParasiteNPC->m_regenZ = GET_Z(pParasiteNPC) += z;
						pParasiteNPC->m_regenY = GET_YLAYER(pParasiteNPC);

						pParasiteNPC->CalcStatus(false);

						CSkill * pSkill = gserver->m_skillProtoList.Create( 1133 ); // �ڻ� ����
						if( pSkill == NULL )
						{
							delete pParasiteNPC ;
							pParasiteNPC = NULL;
							continue;
						}

						pParasiteNPC->SetOwner(df->GetOwner());

						bool bApply;
						if( 0 != ApplySkill((CCharacter*)df->GetOwner(), (CCharacter*)pParasiteNPC, pSkill, -1, bApply) )
						{
							delete pSkill;
							pSkill = NULL;

							delete pParasiteNPC;

							continue;
						}
						delete pSkill;
						pSkill = NULL;

						if( bApply == false )
						{
							delete pParasiteNPC ;
							pParasiteNPC = NULL;
							continue;
						}
						df->GetOwner()->SetBombSummonNPC(pParasiteNPC);

						int cx, cz;
						df->m_pArea->AddNPC(pParasiteNPC);
						df->m_pArea->PointToCellNum(GET_X(pParasiteNPC), GET_Z(pParasiteNPC), &cx, &cz);
						df->m_pArea->CharToCell(pParasiteNPC, GET_YLAYER(pParasiteNPC), cx, cz);

						{
							CNetMsg::SP rmsg(new CNetMsg);
							AppearMsg(rmsg, pParasiteNPC, true);
							df->m_pArea->SendToCell(rmsg, GET_YLAYER(pParasiteNPC), cx, cz);
						}
					}
				}
			}
		}

		CNPC* sumNpc = df->GetOwner()->GetSummonNpc(df);
		if( sumNpc )
		{
#ifdef BUGFIX_MERCNERAY_DELETE
			sumNpc->GetOwner()->SummonNpcRemove(df, false);
#else
			sumNpc->GetOwner()->SummonNpcRemove(df);
#endif
			goto SKIP_DROP;
		}
	}
	/*

	*/

	// �̰����� �Ѿ���� ���̹��� �ƴϹǷ�, ��� ���ʹ� ���Ϳ��� ������ �н�
	else if (onpc && !bNPCKilledNPC)
	{
		goto SKIP_DROP;
	}

	// pc�� npc�� ���̸� ���̹� ������ Ÿ���� �����ش�.
	if (opc)
	{
		opc->SetOwners_target(NULL);
		opc->SetSummonOwners_target(NULL);
	}

	// ���� ����� ó��
	if (!df->m_proto->CheckFlag(NPC_RAID))
		ProcFollowNPC(df);

	// ���� ����Ʈ ���
	if (opc)
		CalcWarPoint(opc, df);

	// ���� NPC�� ����ž�̳� ��ȣ���� �ƴ� ��� ó��
	if (!df->m_proto->CheckFlag(NPC_CASTLE_TOWER | NPC_CASTLE_GUARD))
	{
		int level = -1;
		LONGLONG nTotalDamage = 0;
		// �켱�� PC, ��� ���� ���ϱ�
		CPC* tpc = FindPreferencePC(df, &level, &nTotalDamage);
#ifdef GER_LOG
		if( IS_PC( of ))
		{
			CPC *user = TO_PC( of );
			GAMELOGGEM << init( 0, "CHAR_VICTORY" )
					   << LOG_VAL("account-id", user->m_desc->m_idname ) << blank
					   << LOG_VAL("character-id", user->m_desc->m_pChar->m_name ) << blank
					   << LOG_VAL("zone-id", user->m_desc->m_pChar->m_pZone->m_index ) << blank
					   << LOG_VAL("victim-id", df->m_index ) << blank
					   /*<< LOG_VAL("opponent-id", kill) << blank*/
					   << LOG_VAL("longitude", GET_X(user) ) << blank
					   << LOG_VAL("latitude", GET_Z(user) ) << blank
					   << endGer;
		}
#endif
		//pwesty fix
		// Ensure pointers are valid
		if (!df || !opc) {
			LOG_ERROR("Invalid df or opc pointer");
			return;
		}

		// Check if the event summon is active and NPC is valid in the correct zone
		if (gserver->m_event_summon.IsActive() &&
			gserver->m_event_summon.CheckNpc(df->m_proto->m_index) &&
			of->m_pZone && of->m_pZone->m_index == ZONE_START) {

			// Cast opc to CPC* and increment event summon count
			CPC* pc = static_cast<CPC*>(opc);  // Ensure opc is of type CPC*
			pc->m_eventSummonCount++;

			// Determine the event index based on NPC index
			int eventIndex = gserver->m_event_summon.CheckNpc(df->m_proto->m_index);
			if (eventIndex == -1) {
				LOG_ERROR("No event found for NPC index: %d", df->m_proto->m_index);
				return;
			}

			// Increase the dead NPC count for the event
			gserver->m_event_summon.IncreaseDead(eventIndex);

			// Process the drop for the event
			gserver->m_event_summon.ProcDrop(pc, df, eventIndex);

			// Log the event details
			LOG_INFO("Event summon: %d %d %d %d",
				static_cast<int>(gserver->m_event_summon.IsActive()),
				static_cast<int>(gserver->m_event_summon.CheckNpc(df->m_proto->m_index)),
				df->m_proto->m_index,
				pc->m_eventSummonCount);
		}


		// ������
		if (df->m_proto->CheckFlag(NPC_BOSS | NPC_MBOSS | NPC_RAID))
		{
			GAMELOG << init("MOB DEAD")
					<< "INDEX" << delim
					<< df->m_proto->m_index << delim
					<< "NAME" << delim
					<< df->m_name << delim
					<< "ZONE" << delim
					<< df->m_pZone->m_index << delim
					<< "POSITION" << delim
					<< GET_X(df) << delim
					<< GET_Z(df) << delim
					<< GET_YLAYER(df) << delim
					<< "KILL BY" << delim;
			if (opc)
			{
				GAMELOG << opc->m_index << delim
						<< opc->m_name << delim
						<< opc->m_nick << delim
						<< opc->m_job << delim
						<< opc->m_job2 << delim
						<< opc->m_level;
			}
			else
			{
				GAMELOG << of->m_type << delim
						<< of->m_index << delim
						<< of->m_name << delim
						<< of->m_level;
			}
			GAMELOG << end;

			if (df->m_proto->CheckFlag(NPC_BOSS | NPC_MBOSS))
			{
				// ī�� ���� ȸ�� : �������� ������ ȸ�� ���ʽ�
				if (opc && opc->IsChaotic() && tpc == opc)
				{
					if( !gserver->m_bNonPK )
						opc->m_pkPenalty += df->m_level / 10;

					if (opc->m_pkPenalty > 0)
						opc->m_pkPenalty = 0;

					{
						CNetMsg::SP rmsg(new CNetMsg);
						CharStatusMsg(rmsg, opc, 0);
						opc->m_pArea->SendToCell(rmsg, opc, false);
					}

					opc->m_bChangeStatus = true;
				}

				if (df->m_proto->IsBossInList()) {
					// boss msg system
					CNetMsg::SP rmsg(new CNetMsg);
					CPC *user = TO_PC( of );
					
					time_t tmNow;
					struct tm* timeinfo;
					time(&tmNow);
					timeinfo = localtime( &tmNow );
					
					{
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsgBossDead(rmsg, user->m_desc->m_pChar->m_nick, df->m_proto->m_name, 
						timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
						PCManager::instance()->sendToAll(rmsg);
					}
				}
			}
		} // ������

		if(opc && opc->m_pArea && df->m_proto->m_index == 1002 && df->m_pZone && df->m_pZone->m_index == ZONE_ALTER_OF_DARK)
		{
			// ���ӵ� ���� ���� ������ üũ
			opc->m_pArea->m_CTriggerList.Set_TriggerFlag(TRIGGER_FLAG_NAMEDNPC_DEATH1);
			opc->m_pArea->m_CTriggerList.Set_TriggerFlag(TRIGGER_FLAG_NAMEDNPC_DEATH1002_BEFORE);
			opc->m_pArea->m_CTriggerList.SaveTriggerInfo(TRIGGER_SAVE_ALTER_OF_DARK_1002, opc->m_nJoinInzone_RoomNo);	//Ʈ���� ���� ����
			opc->m_pArea->Change_NpcRegenRaid(TRIGGER_SAVE_ALTER_OF_DARK_1002, 1002);
		}
		else if(opc && opc->m_pArea && df->m_proto->m_index == 1003 && df->m_pZone && df->m_pZone->m_index == ZONE_ALTER_OF_DARK)
		{
			// ���ӵ� ���� ���� ������ üũ
			opc->m_pArea->m_CTriggerList.Set_TriggerFlag(TRIGGER_FLAG_NAMEDNPC_DEATH2);
			opc->m_pArea->m_CTriggerList.Set_TriggerFlag(TRIGGER_FLAG_NAMEDNPC_DEATH1003_BEFORE);
			opc->m_pArea->m_CTriggerList.SaveTriggerInfo(TRIGGER_SAVE_ALTER_OF_DARK_1003, opc->m_nJoinInzone_RoomNo);	//Ʈ���� ���� ����
			opc->m_pArea->Change_NpcRegenRaid(TRIGGER_SAVE_ALTER_OF_DARK_1003, 1003);
		}
		else if(opc && opc->m_pArea && df->m_proto->m_index == 1018 && df->m_pZone && df->m_pZone->m_index == ZONE_ALTER_OF_DARK)
		{
			// ���ӵ� ���� ���� ������ üũ
			opc->m_pArea->m_CTriggerList.Set_TriggerFlag(TRIGGER_FLAG_NAMEDNPC_DEATH1018_BEFORE);
			opc->m_pArea->m_CTriggerList.SaveTriggerInfo(TRIGGER_SAVE_ALTER_OF_DARK_1018, opc->m_nJoinInzone_RoomNo);	//Ʈ���� ���� ����
			opc->m_pArea->Change_NpcRegenRaid(TRIGGER_SAVE_ALTER_OF_DARK_1018, 1018);
		}
		else if (opc && opc->m_pArea && df->m_proto->m_index == 963 && df->m_pZone && df->m_pZone->m_index == ZONE_CAPPELLA_1)
		{
			// Ʈ���Ÿ� ����ϱ� ���� npc963 ���� count ����
			opc->m_pArea->m_CTriggerList.m_nNPC963_KilledCount += 1;
		}
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
		//cloud add trigger de nascer boss aqui zonas 0 a 4
		//DG0
		else if (opc && opc->m_pArea
			&& df->m_proto->m_index != gserver->m_PartyConfig.GetDungeonBoss1(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty)//PARTY_DG0_FIRST_BOSS_INDEX_NORMAL
			&& df->m_proto->m_index != gserver->m_PartyConfig.GetDungeonBoss2(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty)//PARTY_DG0_SECOND_BOSS_INDEX_NORMAL
			&& df->m_proto->m_index != gserver->m_PartyConfig.GetDungeonBoss3(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty)//PARTY_DG0_FINAL_BOSS_INDEX_NORMAL
			
			&& df->m_pZone && df->m_pZone->m_index == ZONE_PARTY_DUNGEON0)
		{
			opc->m_pArea->m_CTriggerList.m_nNPCDG0_KilledCount += 1;
			opc->m_pArea->m_CTriggerList.m_nNPCDG0_KilledCount2 += 1;

		}
		else if (opc && opc->m_pArea && df->m_proto->m_index == gserver->m_PartyConfig.GetDungeonBoss1(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty) && df->m_pZone && df->m_pZone->m_index == ZONE_PARTY_DUNGEON0)
			//else if (opc && opc->m_pArea && (df->m_proto->m_index == PARTY_DG0_FIRST_BOSS_INDEX_NORMAL || df->m_proto->m_index == PARTY_DG0_FIRST_BOSS_INDEX_HARD || df->m_proto->m_index == PARTY_DG0_FIRST_BOSS_INDEX_HELL) && df->m_pZone && df->m_pZone->m_index == ZONE_PARTY_DUNGEON0)
		{
			opc->m_pArea->m_CTriggerList.m_nBOSS1DG0_Killed += 1;
			opc->m_pArea->m_CTriggerList.m_nBOSS1DG0_IsDead = 1;
		}
		else if (opc && opc->m_pArea && df->m_proto->m_index == gserver->m_PartyConfig.GetDungeonBoss2(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty) && df->m_pZone && df->m_pZone->m_index == ZONE_PARTY_DUNGEON0)
			//else if (opc && opc->m_pArea && (df->m_proto->m_index == PARTY_DG0_SECOND_BOSS_INDEX_NORMAL || df->m_proto->m_index == PARTY_DG0_SECOND_BOSS_INDEX_HARD || df->m_proto->m_index == PARTY_DG0_SECOND_BOSS_INDEX_HELL) && df->m_pZone && df->m_pZone->m_index == ZONE_PARTY_DUNGEON0)
		{
			opc->m_pArea->m_CTriggerList.m_nBOSS2DG0_Killed += 1;
			opc->m_pArea->m_CTriggerList.m_nBOSS2DG0_IsDead = 1;

			if (opc->m_pArea->m_RaidDifficulty == DUNGEON_DIFFICULTY_NORMAL)
				opc->m_pArea->Change_NpcRegenRaid(3, gserver->m_PartyConfig.GetDungeonBoss2(opc->m_pZone->m_index, DUNGEON_DIFFICULTY_NORMAL));
			else if (opc->m_pArea->m_RaidDifficulty == DUNGEON_DIFFICULTY_HARD)
				opc->m_pArea->Change_NpcRegenRaid(4, gserver->m_PartyConfig.GetDungeonBoss2(opc->m_pZone->m_index, DUNGEON_DIFFICULTY_HARD));
			else if (opc->m_pArea->m_RaidDifficulty == DUNGEON_DIFFICULTY_HELL)
				opc->m_pArea->Change_NpcRegenRaid(5, gserver->m_PartyConfig.GetDungeonBoss2(opc->m_pZone->m_index, DUNGEON_DIFFICULTY_HELL));
		}
		else if (opc && opc->m_pArea && df->m_proto->m_index == gserver->m_PartyConfig.GetDungeonBoss3(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty) && df->m_pZone && df->m_pZone->m_index == ZONE_PARTY_DUNGEON0)
			//else if (opc && opc->m_pArea && (df->m_proto->m_index == PARTY_DG0_FINAL_BOSS_INDEX_NORMAL || df->m_proto->m_index == PARTY_DG0_FINAL_BOSS_INDEX_HARD || df->m_proto->m_index == PARTY_DG0_FINAL_BOSS_INDEX_HELL) && df->m_pZone && df->m_pZone->m_index == ZONE_PARTY_DUNGEON0)
		{
			int finalbossrewardidx = 0;
			int finalbossrewardidx1 = 0;
			int finalbossrewardidx2 = 0;
			int finalbossrewardidx3 = 0;
			int finalbossrewardidx4 = 0;

			int finalbosscount = 0;
			int finalbosscount1 = 0;
			int finalbosscount2 = 0;
			int finalbosscount3 = 0;
			int finalbosscount4 = 0;

			int EquipnLevel = 0;
			int EquipnWearType = 0;
			int EquipnPlus = 0;
			int EquipnFlag = 0;

			int progresspoint;
			int stringinfo;

			if (opc->m_pArea->m_CTriggerList.m_PcDeadPenaltyTime == 0)
				opc->m_pArea->m_CTriggerList.m_PcDeadPenaltyTime = 2;

			if (opc->m_pArea->m_RaidDifficulty == gserver->m_PartyConfig.GetDungeonDifficulty(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty))//DUNGEON_DIFFICULTY_NORMAL
			{
				
				for (int i = 0; i < gserver->m_PartyConfig.m_PartyExpeditions.size(); i++)
				{
					if (opc->m_pZone->m_index == gserver->m_PartyConfig.m_PartyExpeditions[i].zoneid && opc->m_pArea->m_RaidDifficulty == gserver->m_PartyConfig.m_PartyExpeditions[i].difficulty)
					{
						finalbossrewardidx = gserver->m_PartyConfig.m_PartyExpeditions[i].rewardindex;   finalbosscount = gserver->m_PartyConfig.m_PartyExpeditions[i].count;
						finalbossrewardidx1 = gserver->m_PartyConfig.m_PartyExpeditions[i].rewardindex1;  finalbosscount1 = gserver->m_PartyConfig.m_PartyExpeditions[i].count1;
						finalbossrewardidx2 = gserver->m_PartyConfig.m_PartyExpeditions[i].rewardindex2;  finalbosscount2 = gserver->m_PartyConfig.m_PartyExpeditions[i].count2;
						finalbossrewardidx3 = gserver->m_PartyConfig.m_PartyExpeditions[i].rewardindex3;  finalbosscount3 = gserver->m_PartyConfig.m_PartyExpeditions[i].count3;
						finalbossrewardidx4 = gserver->m_PartyConfig.m_PartyExpeditions[i].rewardindex4;  finalbosscount4 = gserver->m_PartyConfig.m_PartyExpeditions[i].count4;
					}
				}

				progresspoint = gserver->m_PartyConfig.GetDungeonPoint(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty);
				stringinfo = gserver->m_PartyConfig.GetDungeonType(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty);
			}
			

			const int itemCount = 5;

			int tab[itemCount] = { finalbossrewardidx,finalbossrewardidx1,finalbossrewardidx2,finalbossrewardidx3,finalbossrewardidx4 };
			int tab2[itemCount] = { finalbosscount,finalbosscount1,finalbosscount2,finalbosscount3,finalbosscount4 };

			if (opc->IsParty())
			{
				int i;
				CPartyMember* pPartyMember = NULL;
				CPC* pMember = NULL;
				for (i = 0; i < MAX_PARTY_MEMBER; i++)
				{
					pPartyMember = opc->m_party->GetMemberByListIndex(i);
					if (pPartyMember && pPartyMember->GetMemberPCPtr())
					{
						pMember = pPartyMember->GetMemberPCPtr();

						if (pMember->m_pZone->m_index == opc->m_pZone->m_index)
						{
							
							int z;
							for (z = 0; z < itemCount; z++)
							{
								if (false == pMember->GiveItem(tab[z], 0, 0, tab2[z], false, false))
								{
									GAMELOG << init("BLACK_CASTLE_REWARD_FAIL", pMember)
										<< end;
								}
							}

							
							{
								CNetMsg::SP rmsg(new CNetMsg);
								RoyalRumbleWinner(rmsg, stringinfo, pMember->m_index, pMember->m_nick, pMember->m_pZone->m_index);
								PCManager::instance()->sendToAll(rmsg);
							}

							for (int i = 0; i < gserver->m_PartyConfig.GetZoneCount(0); i++)
							{
								if (pMember->m_pZone->m_index == gserver->m_PartyConfig.m_PartyExpeditions[i].zoneid)
									pMember->m_PartyDGCompleteData[i] += progresspoint;
							}
							
							UpdatePartyDungeonInfo(pMember);
						}
					}
				}
			}
#ifdef CLOUD_EXPEDITION_SOLO_DUNGEONS
			else
			{
				

				int z;
				for (z = 0; z < itemCount; z++)
				{
					if (false == opc->GiveItem(tab[z], 0, 0, tab2[z], false, false))
					{
						GAMELOG << init("BLACK_CASTLE_REWARD_FAIL", opc)
							<< end;
					}
				}

				
				{
					CNetMsg::SP rmsg(new CNetMsg);
					RoyalRumbleWinner(rmsg, stringinfo, opc->m_index, opc->m_nick, opc->m_pZone->m_index);
					PCManager::instance()->sendToAll(rmsg);
				}

				for (int i = 0; i < gserver->m_PartyConfig.GetZoneCount(0); i++)
				{
					if (opc->m_pZone->m_index == gserver->m_PartyConfig.m_PartyExpeditions[i].zoneid)
						opc->m_PartyDGCompleteData[i] += progresspoint;
				}
				UpdatePartyDungeonInfo(opc);

			}
#endif
		}
		//DG1
		else if (opc && opc->m_pArea
			&& df->m_proto->m_index != gserver->m_PartyConfig.GetDungeonBoss1(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty)//PARTY_DG0_FIRST_BOSS_INDEX_NORMAL
			&& df->m_proto->m_index != gserver->m_PartyConfig.GetDungeonBoss2(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty)//PARTY_DG0_SECOND_BOSS_INDEX_NORMAL
			&& df->m_proto->m_index != gserver->m_PartyConfig.GetDungeonBoss3(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty)//PARTY_DG0_FINAL_BOSS_INDEX_NORMAL
			&& df->m_pZone && df->m_pZone->m_index == gserver->m_PartyConfig.GetDungeonZoneID(df->m_pZone->m_index))
		{
			opc->m_pArea->m_CTriggerList.m_nNPCDG1_KilledCount += 1;
			opc->m_pArea->m_CTriggerList.m_nNPCDG1_KilledCount2 += 1;
		}
		else if (opc && opc->m_pArea && df->m_proto->m_index == gserver->m_PartyConfig.GetDungeonBoss1(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty) && df->m_pZone && df->m_pZone->m_index == gserver->m_PartyConfig.GetDungeonZoneID(df->m_pZone->m_index))
			//else if (opc && opc->m_pArea && (df->m_proto->m_index == PARTY_DG1_FIRST_BOSS_INDEX_NORMAL || df->m_proto->m_index == PARTY_DG1_FIRST_BOSS_INDEX_HARD || df->m_proto->m_index == PARTY_DG1_FIRST_BOSS_INDEX_HELL) && df->m_pZone && df->m_pZone->m_index == ZONE_PARTY_DUNGEON1)
		{
			opc->m_pArea->m_CTriggerList.m_nBOSS1DG1_Killed += 1;
			opc->m_pArea->m_CTriggerList.m_nBOSS1DG1_IsDead = 1;

			if (opc->m_pArea->m_RaidDifficulty == DUNGEON_DIFFICULTY_NORMAL)
				opc->m_pArea->Change_NpcRegenRaid(3, gserver->m_PartyConfig.GetDungeonBoss1(opc->m_pZone->m_index, DUNGEON_DIFFICULTY_NORMAL));
			else if (opc->m_pArea->m_RaidDifficulty == DUNGEON_DIFFICULTY_HARD)
				opc->m_pArea->Change_NpcRegenRaid(4, gserver->m_PartyConfig.GetDungeonBoss1(opc->m_pZone->m_index, DUNGEON_DIFFICULTY_HARD));
			else if (opc->m_pArea->m_RaidDifficulty == DUNGEON_DIFFICULTY_HELL)
				opc->m_pArea->Change_NpcRegenRaid(5, gserver->m_PartyConfig.GetDungeonBoss1(opc->m_pZone->m_index, DUNGEON_DIFFICULTY_HELL));
		}
		else if (opc && opc->m_pArea && df->m_proto->m_index == gserver->m_PartyConfig.GetDungeonBoss2(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty) && df->m_pZone && df->m_pZone->m_index == gserver->m_PartyConfig.GetDungeonZoneID(df->m_pZone->m_index))
			//else if (opc && opc->m_pArea && (df->m_proto->m_index == PARTY_DG1_SECOND_BOSS_INDEX_NORMAL || df->m_proto->m_index == PARTY_DG1_SECOND_BOSS_INDEX_HARD || df->m_proto->m_index == PARTY_DG1_SECOND_BOSS_INDEX_HELL) && df->m_pZone && df->m_pZone->m_index == ZONE_PARTY_DUNGEON1)
		{
			opc->m_pArea->m_CTriggerList.m_nBOSS2DG1_Killed += 1;
			opc->m_pArea->m_CTriggerList.m_nBOSS2DG1_IsDead = 1;

			if (opc->m_pArea->m_RaidDifficulty == DUNGEON_DIFFICULTY_NORMAL)
				opc->m_pArea->Change_NpcRegenRaid(6, gserver->m_PartyConfig.GetDungeonBoss2(opc->m_pZone->m_index, DUNGEON_DIFFICULTY_NORMAL));
			else if (opc->m_pArea->m_RaidDifficulty == DUNGEON_DIFFICULTY_HARD)
				opc->m_pArea->Change_NpcRegenRaid(7, gserver->m_PartyConfig.GetDungeonBoss2(opc->m_pZone->m_index, DUNGEON_DIFFICULTY_HARD));
			else if (opc->m_pArea->m_RaidDifficulty == DUNGEON_DIFFICULTY_HELL)
				opc->m_pArea->Change_NpcRegenRaid(8, gserver->m_PartyConfig.GetDungeonBoss2(opc->m_pZone->m_index, DUNGEON_DIFFICULTY_HELL));
		}
		else if (opc && opc->m_pArea && df->m_proto->m_index == gserver->m_PartyConfig.GetDungeonBoss3(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty) && df->m_pZone && df->m_pZone->m_index == gserver->m_PartyConfig.GetDungeonZoneID(df->m_pZone->m_index))
			//else if (opc && opc->m_pArea && (df->m_proto->m_index == PARTY_DG1_FINAL_BOSS_INDEX_NORMAL || df->m_proto->m_index == PARTY_DG1_FINAL_BOSS_INDEX_HARD || df->m_proto->m_index == PARTY_DG1_FINAL_BOSS_INDEX_HELL) && df->m_pZone && df->m_pZone->m_index == ZONE_PARTY_DUNGEON1)
		{
			int finalbossrewardidx = 0;
			int finalbossrewardidx1 = 0;
			int finalbossrewardidx2 = 0;
			int finalbossrewardidx3 = 0;
			int finalbossrewardidx4 = 0;

			int finalbosscount = 0;
			int finalbosscount1 = 0;
			int finalbosscount2 = 0;
			int finalbosscount3 = 0;
			int finalbosscount4 = 0;

			int EquipnLevel = 0;
			int EquipnWearType = 0;
			int EquipnPlus = 0;
			int EquipnFlag;

			int progresspoint;
			int stringinfo;

			if (opc->m_pArea->m_CTriggerList.m_PcDeadPenaltyTime == 0)
				opc->m_pArea->m_CTriggerList.m_PcDeadPenaltyTime = 2;

			if (opc->m_pArea->m_RaidDifficulty == DUNGEON_DIFFICULTY_NORMAL)
			{			

				for (int i = 0; i < gserver->m_PartyConfig.m_PartyExpeditions.size(); i++)
				{
					if (opc->m_pZone->m_index == gserver->m_PartyConfig.m_PartyExpeditions[i].zoneid && opc->m_pArea->m_RaidDifficulty == gserver->m_PartyConfig.m_PartyExpeditions[i].difficulty)
					{
						finalbossrewardidx = gserver->m_PartyConfig.m_PartyExpeditions[i].rewardindex;   finalbosscount = gserver->m_PartyConfig.m_PartyExpeditions[i].count;
						finalbossrewardidx1 = gserver->m_PartyConfig.m_PartyExpeditions[i].rewardindex1;  finalbosscount1 = gserver->m_PartyConfig.m_PartyExpeditions[i].count1;
						finalbossrewardidx2 = gserver->m_PartyConfig.m_PartyExpeditions[i].rewardindex2;  finalbosscount2 = gserver->m_PartyConfig.m_PartyExpeditions[i].count2;
						finalbossrewardidx3 = gserver->m_PartyConfig.m_PartyExpeditions[i].rewardindex3;  finalbosscount3 = gserver->m_PartyConfig.m_PartyExpeditions[i].count3;
						finalbossrewardidx4 = gserver->m_PartyConfig.m_PartyExpeditions[i].rewardindex4;  finalbosscount4 = gserver->m_PartyConfig.m_PartyExpeditions[i].count4;
					}
				}

				progresspoint = gserver->m_PartyConfig.GetDungeonPoint(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty);
				stringinfo = gserver->m_PartyConfig.GetDungeonType(opc->m_pZone->m_index, opc->m_pArea->m_RaidDifficulty);
			}			

			const int itemCount = 5;

			int tab[itemCount] = { finalbossrewardidx,finalbossrewardidx1,finalbossrewardidx2,finalbossrewardidx3,finalbossrewardidx4 };
			int tab2[itemCount] = { finalbosscount,finalbosscount1,finalbosscount2,finalbosscount3,finalbosscount4 };

			if (opc->IsParty())
			{
				int i;
				CPartyMember* pPartyMember = NULL;
				CPC* pMember = NULL;
				for (i = 0; i < MAX_PARTY_MEMBER; i++)
				{
					pPartyMember = opc->m_party->GetMemberByListIndex(i);
					if (pPartyMember && pPartyMember->GetMemberPCPtr())
					{
						pMember = pPartyMember->GetMemberPCPtr();
						//if(opc->m_pArea->FindCharInCell(opc, pMember->m_index, MSG_CHAR_PC))
						if (pMember->m_pZone->m_index == opc->m_pZone->m_index)
						{
							
							int z;
							for (z = 0; z < itemCount; z++)
							{
								if (false == pMember->GiveItem(tab[z], 0, 0, tab2[z], false, false))
								{
									GAMELOG << init("BLACK_CASTLE_REWARD_FAIL", pMember)
										<< end;
								}
							}

							
							{
								CNetMsg::SP rmsg(new CNetMsg);
								RoyalRumbleWinner(rmsg, stringinfo, pMember->m_index, pMember->m_nick, pMember->m_pZone->m_index);
								PCManager::instance()->sendToAll(rmsg);
							}

							for (int i = 0; i < gserver->m_PartyConfig.GetZoneCount(0); i++)
							{
								if (pMember->m_pZone->m_index == gserver->m_PartyConfig.m_PartyExpeditions[i].zoneid)
									pMember->m_PartyDGCompleteData[i] += progresspoint;
							}

							UpdatePartyDungeonInfo(pMember);
						}
					}
				}
			}
#ifdef CLOUD_EXPEDITION_SOLO_DUNGEONS
			else
			{

				int z;
				for (z = 0; z < itemCount; z++)
				{
					if (false == opc->GiveItem(tab[z], 0, 0, tab2[z], false, false))
					{
						GAMELOG << init("BLACK_CASTLE_REWARD_FAIL", opc)
							<< end;
					}
				}


				{
					CNetMsg::SP rmsg(new CNetMsg);
					RoyalRumbleWinner(rmsg, stringinfo, opc->m_index, opc->m_nick, opc->m_pZone->m_index);
					PCManager::instance()->sendToAll(rmsg);
				}

				for (int i = 0; i < gserver->m_PartyConfig.GetZoneCount(0); i++)
				{
					if (opc->m_pZone->m_index == gserver->m_PartyConfig.m_PartyExpeditions[i].zoneid)
						opc->m_PartyDGCompleteData[i] += progresspoint;
				}

				
				UpdatePartyDungeonInfo(opc);

			}
#endif
		}
#endif
		int nObjectData;
		int nAkanNpcIdx = df->m_proto->m_index;

		switch(nAkanNpcIdx)
		{
		case 1115:				// �ĵ����� ����(Hard)
		case 1170:				// �ĵ����� ����(Normal)
			{
				nObjectData = 10;
				if(opc && opc->m_pArea && df->m_pZone && df->m_pZone->m_index == ZONE_AKAN_TEMPLE)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					RaidSceneMsg(rmsg, OBJECT_TYPE_TODO, KILL_NPC, nAkanNpcIdx, nObjectData);
					do_ExRaidScene(opc, rmsg);
				}
			}
			break;
		case 1112:				// ����
		case 1116:				// �ĵ���
		case 1120:				// ��Ÿ
		case 1124:				// ����
		case 1126:				// ���� ���ݼ��� ����
		case 1127:				// ���� �������� �̿�
		case 1128:				// ������ ����
		case 1167:				// ����
		case 1171:				// �ĵ���
		case 1175:				// ��Ÿ
		case 1179:				// ����
		case 1180:				// ���� ���ݼ��� ����
		case 1181:				// ���� �������� �̿�
		case 1182:				// ������ ����
			{
				nObjectData = 1;
				if(opc && opc->m_pArea && df->m_pZone && df->m_pZone->m_index == ZONE_AKAN_TEMPLE)
				{
					{
						CNetMsg::SP rmsg(new CNetMsg);
						RaidSceneMsg(rmsg, OBJECT_TYPE_TODO, KILL_NPC, nAkanNpcIdx, nObjectData);
						do_ExRaidScene(opc, rmsg);
					}
				}
			}
			break;
		case 1259:	//������ ����
			{
				nObjectData = 1;
				if(opc && opc->m_pArea && df->m_pZone && df->m_pZone->m_index == ZONE_DUNGEON4)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					RaidSceneMsg(rmsg, OBJECT_TYPE_TODO, KILL_NPC, nAkanNpcIdx, nObjectData);
					do_ExRaidScene(opc, rmsg);
				}
			}
			break;
		case 1364:
			{
				if(opc && opc->m_pArea && df->m_pZone && df->m_pZone->m_index == ZONE_TARIAN_DUNGEON)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					RaidSceneMsg(rmsg, OBJECT_TYPE_TODO, KILL_NPC, nAkanNpcIdx, 1);
					do_ExRaidScene(opc, rmsg);
				}
			}
			break;
		//Val add new raid
		case 1738:	// first boss
		case 1739:	// second boss
		case 1746:	// third boss
		case 1747:	// fake boss
		case 1749:	// final boss
		{
			if (opc && opc->m_pArea && df->m_pZone && df->m_pZone->m_index == ZONE_ENCHANTED_DUNGEON)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				RaidSceneMsg(rmsg, OBJECT_TYPE_TODO, KILL_NPC, nAkanNpcIdx, 1);
				do_ExRaidScene(opc, rmsg);
			}
		}
		break;
		case 1748:				// fake boss clones
		{
			nObjectData = 6;
			if (opc && opc->m_pArea && df->m_pZone && df->m_pZone->m_index == ZONE_ENCHANTED_DUNGEON)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				RaidSceneMsg(rmsg, OBJECT_TYPE_TODO, KILL_NPC, nAkanNpcIdx, nObjectData);
				do_ExRaidScene(opc, rmsg);
			}
		}
		break;
		default:
			break;
		}

#ifdef REFORM_PK_PENALTY_201108 // PK �г�Ƽ ���� :: npc�� ������ ������ ���� ������ ��� �����ش�.
		if( !gserver->m_bNonPK )
		{
			if(df && opc)
			{
				int nlevel = df->m_level - opc->m_level;
				int pkPenalty = 0;
				if( nlevel > 4 )
					pkPenalty += 15;
				else if( nlevel > -5 )
					pkPenalty += 10;
				else if( nlevel <= -5 && nlevel >= -10)
					pkPenalty += 5;

				// ���� ��ġ ��� �������� ��� ���̶��
				if( opc->m_assist.m_avRate.pkDispositionPointValue > 0 )
				{
					pkPenalty = pkPenalty * opc->m_assist.m_avRate.pkDispositionPointValue;
					opc->m_assist.CureByItemIndex(7474);	// ���� ��ġ ��� ������
					opc->m_assist.CureByItemIndex(7475);	// ���� ��ġ ��� ������
					opc->m_assist.CureByItemIndex(7476);	// ���� ��ġ ��� ������
				}
				opc->AddPkPenalty( pkPenalty );

				{
					CNetMsg::SP rmsg(new CNetMsg);
					CharStatusMsg(rmsg, opc, 0);
					opc->m_pArea->SendToCell(rmsg, opc, false);
				}

				opc->m_bChangeStatus = true;
			}
		}
#else // REFORM_PK_PENALTY_201108 // PK �г�Ƽ ����
		if (opc && opc->IsChaotic() && df->m_level >= opc->m_level - 5)
		{
			opc->m_pkRecoverNPCCount++;
			if (opc->m_pkRecoverNPCCount >= 25)
			{
				opc->m_pkRecoverNPCCount = 0;

				if( !gserver->m_bNonPK )
					opc->m_pkPenalty++;

				{
					CNetMsg::SP rmsg(new CNetMsg);
					CharStatusMsg(rmsg, opc, 0);
					opc->m_pArea->SendToCell(rmsg, opc, false);
				}

				opc->m_bChangeStatus = true;
			}
		} // ī�� ���� ȸ��
#endif // REFORM_PK_PENALTY_201108 // PK �г�Ƽ ����
		// Exp, SP �й�
		// �̷�ƾ�� �������� �Ͽ� ���̵��� �Ͽ��� ��� ������ �������� �ʴ´�.
		DivisionExpSP(df, tpc, nTotalDamage);
		ProcDropItemAfterBattle(df, opc, tpc, level);

		// �������� Quest �� ���� npc�� �������̸� UpdateData
		if (opc && opc == tpc)
		{
			if( opc->m_pZone->IsPersonalDungeon() )
			{
				opc->m_pArea->m_nMakeNPC++;

#if defined ( LC_GAMIGO ) || defined ( LC_KOR ) || defined ( LC_USA )
				if( df->m_proto->m_index == 5 )
				{
					if(opc->m_pArea->m_nMakeNPC < 103)
						goto SKIP_DROP;
					else
					{
						GAMELOG << init("QUEST COMPLETE PD1", opc)
								<< opc->m_pArea->m_nMakeNPC
								<< end;
					}
				}
				else if(df->m_proto->m_index == 201 && opc->m_pArea->m_nMakeNPC < 50)
				{
					goto SKIP_DROP;
				}
#else
				if( (df->m_proto->m_index == 5 || df->m_proto->m_index == 201 ) && opc->m_pArea->m_nMakeNPC < 50 )
				{
					goto SKIP_DROP;
				}
#endif // LC_GAMIGO || LC_KOR || LC_USA
			}

#ifdef PARTY_QUEST_ITEM_BUG_
			ProcDeadQuestProc(opc, df, QTYPE_SCALE_PERSONAL); // ���� ��׷ε� �԰� ���͵� ��Ÿ �ƴܴ�.
#else
			CQuest* pQuest = NULL;
			CQuest* pQuestNext = opc->m_questList.GetNextQuest(NULL, QUEST_STATE_RUN);
			while ((pQuest = pQuestNext))
			{
				pQuestNext = opc->m_questList.GetNextQuest(pQuestNext, QUEST_STATE_RUN);
				// ����Ʈ �ְ� �������̰� �ݺ�, ����, ����, ���� ����Ʈ�̸�
				switch (pQuest->GetQuestType0())
				{
				case QTYPE_KIND_REPEAT:
				case QTYPE_KIND_COLLECTION:
				case QTYPE_KIND_DEFEAT:
				case QTYPE_KIND_SAVE:
					pQuest->QuestUpdateDataForParty(opc, df);
					break;

				default:
					break;
				}
			}
			if( pQuest == NULL && opc->IsParty() && opc->m_party )
			{
				int i;
				const CPartyMember* pPartyMember;
				CPC*	pPartyPC;

				for(i=0; i<MAX_PARTY_MEMBER; ++i)
				{
					pPartyMember = opc->m_party->GetMemberByListIndex(i);
					if(pPartyMember && pPartyMember->GetMemberPCPtr())
					{
						pPartyPC = pPartyMember->GetMemberPCPtr();

						if(opc->m_pArea->FindCharInCell(opc, pPartyPC->m_index, MSG_CHAR_PC))
						{
							pQuest = pPartyPC->m_questList.FindQuestByMob( df->m_idNum);

							if( pQuest == NULL)
								continue;

							if( pQuest->GetPartyScale() != QTYPE_SCALE_PARTY)
								break;

							switch (pQuest->GetQuestType0())
							{
							case QTYPE_KIND_REPEAT:
							case QTYPE_KIND_COLLECTION:
							case QTYPE_KIND_DEFEAT:
							case QTYPE_KIND_SAVE:
								pQuest->QuestUpdateData(pPartyPC, df);
								break;

							default:
								break;
							}
						}
					}
				}
			}
#endif // PARTY_QUEST_ITEM_BUG_
		}
#ifdef PARTY_QUEST_ITEM_BUG_
		else if(opc) // [2010/12/28 derek] opc == NULL �ε��� ������ ����Ʈ ã�ٰ� ���� �ٿ�Ǿ� �߰���.
		{
#ifdef _BATTLEGROUP_QUEST_BUG_PIX
			if( opc->IsExped() ) // ����� �ʸԾ����� ��Ÿ�� �������
				ProcDeadQuestProc(opc, df, QTYPE_SCALE_BATTLEGROUP);
			else
#endif
				ProcDeadQuestProc(opc, df, QTYPE_SCALE_PARTY);
		}

#endif //PARTY_QUEST_ITEM_BUG_
	} // ���� NPC�� ����ž�̳� ��ȣ���� �ƴ� ��� ó��
	else
	{
		int level = -1;
		LONGLONG nTotalDamage = 0;
		// �켱�� PC, ��� ���� ���ϱ�
		CPC* tpc = FindPreferencePC(df, &level, &nTotalDamage);
		DropWarCastleToken(df, opc, tpc, level);
	}

SKIP_DROP:

	// ��ȣž�� DelNPC() ���ϰ� UpdateGateState() �Ŀ� �޽����� �˸���.
	if (df->m_proto->CheckFlag(NPC_CASTLE_TOWER) != 0)
	{
		int gstate_old = 0, gstate_new = 0;

		CWarCastle * castle = CWarCastle::GetCastleObject(ZONE_MERAC);
		CDratanCastle * pCastle = CDratanCastle::CreateInstance();

		if (of->m_pZone->m_index == ZONE_MERAC)
		{
			if (castle != NULL)
			{
				gstate_old = castle->GetGateState();
				gstate_old |= pCastle->GetGateState();
				castle->UpdateGateState(df);
				gstate_new = castle->GetGateState();
				gstate_new |= pCastle->GetGateState();
			}
		}
		else if (of->m_pZone->m_index == ZONE_DRATAN)
		{
			gstate_old = pCastle->GetGateState();

			if (castle != NULL)
			{
				gstate_old |= castle->GetGateState();
			}

			pCastle->UpdateGateState(df);
			gstate_new = pCastle->GetGateState();

			if (castle != NULL)
			{
				gstate_new |= castle->GetGateState();
			}

			if (df->m_proto->CheckFlag(NPC_WARCASTLE) != 0)
			{
				// NPC_CASTLE_TOWER �� NPC_WARCASTLE ��
				// ������ Ÿ���� ��Ȱ����
				int qindex = df->m_proto->m_index;
				if (qindex >= 390 && qindex <= 396)
				{
					// ��Ȱ���� �ı� �˸�
					CNetMsg::SP rmsg(new CNetMsg);
					CastleTowerQuartersCrushMsg(rmsg, qindex);
					of->m_pArea->SendToAllClient(rmsg);

					// ��Ȱ���� �ı� ó��
					/*pCastle->m_nRebrithGuild[df->m_proto->m_index - 390] =  -1;
					memset((void *)pCastle->m_strRebrithGuild[df->m_proto->m_index - 390], 0, 51);*/
				}
			}
		}

		if (gstate_old != gstate_new)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			GuildWarGateStateMsg(rmsg, gstate_old, gstate_new);
			of->m_pArea->SendToAllClient(rmsg);
		}

		DelAttackList(df);

		if (of->m_pZone->m_index == ZONE_DRATAN)
		{
			if( df->m_proto->m_index == 351)
			{
				// ������ Ÿ��
				// ��� Ÿ�� ��� ����
				pCastle->StopCastleTower();
			}
			else if (df->m_proto->CheckFlag(NPC_CASTLE_TOWER) != 0)
			{
				// ���� ��ȣ�� (����� �� ��..) �α�
				GAMELOG << init("DRATAN CASTLE NPC DEAD : ") << df->m_proto->m_name
						<< " BROKEN BY : " << of->m_name << end;
				// ������ Ÿ���� �ƴ� ��� Ÿ��
				int  i;
				// ��Ȱ ���� ����
				for (i=0; i<7; i++)
				{
					if (pCastle->m_pRebrithNPC[i] == df)
					{
						pCastle->m_pRebrithNPC[i] = NULL;
						pCastle->m_nRebrithGuild[i] = -1;
						memset((void *)pCastle->m_strRebrithGuild[i], 0, 51);
					}
				}

				// ���� Ÿ�� ����
				for (i=0; i<5; i++)
				{
					if (pCastle->m_pWarpNPC[i] == df)
					{
						pCastle->m_pWarpNPC[i] = NULL;
					}
				}

				// ����� �� ����
				for (i=0; i<5; i++)
				{
					if (pCastle->m_gateNPC[i] == df)
					{
						pCastle->m_gateNPC[i] = NULL;
					}
				}

				// �˸�
				of->m_pArea->CharFromCell(df, true);
				of->m_pArea->DelNPC(df);
			}
		}
		return ;
	} // ��ȣž�� DelNPC() ���ϰ� UpdateGateState() �Ŀ� �޽����� �˸���.
//#endif

#ifdef EXTREME_CUBE
	if(df->m_bCubeRegen)
	{
		CCubeSpace* cube = gserver->m_extremeCube.GetExtremeCube(df->m_pArea->m_index);
		if(cube)
		{
			if(gserver->m_extremeCube.IsGuildCubeTime() && opc && opc->m_guildInfo && opc->m_guildInfo->guild())
			{
				CCubeMemList* CubeMemList;
				CubeMemList = gserver->m_extremeCube.FindMemList(opc->m_guildInfo->guild());
				if(CubeMemList)
				{
					time_t lastCubePoint;

					time(&lastCubePoint);
					CNetMsg::SP rmsg(new CNetMsg);
					HelperAddCubePointMsg(rmsg, opc->m_guildInfo->guild()->index(), df->m_level, lastCubePoint);
					SEND_Q(rmsg, gserver->m_helper);
				}
			}
		}
	}

	if(df->m_pZone != NULL && df->m_proto->m_index == 529 && df->m_pZone->IsExtremeCube())
	{
		CCubeSpace* cube = gserver->m_extremeCube.GetExtremeCube(df->m_pArea->m_index);

		if(cube && (cube->m_crystal == df) )
		{
			// cube->m_crystal = NULL;

			cube->DelCrystal(false);
			cube->m_waitTime = gserver->m_pulse + PULSE_REAL_SEC * 10;
			return ;
		}
	}
	else if(df->m_pZone != NULL && df->m_proto->m_index == 527 && df->m_pZone->IsExtremeCube())
	{
		CCubeSpace* cube = gserver->m_extremeCube.GetExtremeCube(df->m_pArea->m_index);

		if(cube && (cube->m_crystal == df) )
		{
			// cube->m_crystal = NULL;

			cube->DelCrystal(false);
			cube->m_waitTime = gserver->m_pulse + PULSE_REAL_SEC * 10;
			return ;
		}
	}
#endif // EXTREME_CUBE

	if(df && opc)
	{
		vec_affinityList_t::iterator it = df->m_proto->m_affinityList.begin();
		vec_affinityList_t::iterator endit = df->m_proto->m_affinityList.end();
		
		int point = 0;

		for(; it != endit; ++it)
		{
			CAffinityProto* proto = *(it);

			CAffinity* affinity = opc->m_affinityList.FindAffinity(proto->m_index);
			if (affinity)
			{
				point = proto->GetAffinityPointOfNPC(df->m_idNum);
				int bonus = 0;
				if (opc->m_avPassiveAddition.affinity_monster > 0)
				{
					bonus += opc->m_avPassiveAddition.affinity_monster;
				}
				if (opc->m_avPassiveRate.affinity_monster > 0)
				{
					bonus = point * (opc->m_avPassiveRate.affinity_monster - 100) / SKILL_RATE_UNIT;
				}

				if (gserver->isActiveEvent(A_EVENT_DOUBLE_AFFINITY)) {
					point = point * 2;
				}
               	if (opc->m_assist.FindByItemIndex(12333)) {
				   	point = point * 4;
					affinity->AddPoint( point, opc, bonus);
			   	} else {
					affinity->AddPoint( point, opc, bonus);
				}
			}
		}

		if (opc->m_assist.FindByItemIndex(12333)) {
			opc->m_assist.CureByItemIndex(12333);
		}
	}

	if(df->m_ctCount > 0)
	{
		gserver->m_npc_ctTime.erase(df->m_index);
	}

END_PROC:

#ifdef BATTLE_PASS_SYSTEM
	if (opc && df)
		ProcDeadBattlePass(opc, df);
#endif

	//rvr ������ ���ݽÿ� �����ؾ� �Ǵ� �Լ� (NPC �� �׾��� ���)
	if(opc != NULL && of->m_pZone->isRVRZone() && df->m_pZone->isRVRZone())
	{
		ProcDead_RVR(opc, df);
	}

	// ��� ���ʹ� ���Ϳ��� ������ �н�
	if ( onpc || bNPCKilledNPC )
	{
		// �ش� ���� ���� ���� ǥ���Ѵ�.  ���⼭�� �ٷ� ������� ���� ó��..
		// MobActivity.cpp::MobActivity() Ÿ�� ������ �� ���� ���ľ��Ѵ�.
		onpc->m_pArea->m_nNPC_Killed_NPC++;
	}
	else
	{
		DelAttackList(df);
		of->m_pArea->CharFromCell(df, true);
		of->m_pArea->DelNPC(df);
	}

	//���� �׾��� �� �ߵ��Ǵ� ����� ������ üũ
	if(opc != NULL)
	{
		if(opc->m_deadnpc_toggle_item.size() > 0)
		{
			std::vector<CItem*>::iterator it = opc->m_deadnpc_toggle_item.begin();

			CItem* item;

			for(; it != opc->m_deadnpc_toggle_item.end(); )
			{
				item = opc->m_inventory.getItem( (*it)->tab(), (*it)->getInvenIndex() );
				
				if(item == NULL)
				{
					it = opc->m_deadnpc_toggle_item.erase(it);
					continue;
				}

				if( (item->m_itemProto->getItemFlag() & ITEM_FLAG_TOGGLE) == false )
				{
					it = opc->m_deadnpc_toggle_item.erase(it);
					continue;
				}

				if(item->m_toggle == true)
				{
					if( do_ItemUsePotion(opc, item, 0) == false)
					{
						it++;
						continue;
					}
					
					if(item->getItemCount() == 1)
						it = opc->m_deadnpc_toggle_item.erase(it);
					else
						it++;

					opc->m_inventory.decreaseItemCount(item, 1);
				}
				else
				{
					it = opc->m_deadnpc_toggle_item.erase(it);
				}
			}
		}
	}
}

void ProcDead_RVR(CPC* op, CNPC* df)
{
	//�� npc �� �׿��� ��쿡�� ��ް� �� ���밡 ������ �������� ���� �⿩���� �ο����ش�.
	int jewelKailuxPoint		= SyndicateInfoDataManager::instance()->getJewelPoint(SYNDICATE::eSYNDICATE_KAILUX);
	int jewelDealerMoonPoint	= SyndicateInfoDataManager::instance()->getJewelPoint(SYNDICATE::eSYNDICATE_DEALERMOON);
	int grade = df->m_proto->m_rvr_grade;
    int multiplier = gserver->m_serverConfig.rvr_points;
	//�����ڰ� ī�̷轺 �� ���
	
	if (op->m_assist.m_avAddition.hcFactionUP == true)
			multiplier *=2;

	if (op->m_assist.FindByItemIndex(12559))	
			multiplier*=2;


	if(op->getSyndicateType() == SYNDICATE::eSYNDICATE_KAILUX)
	{   
		if (jewelKailuxPoint < jewelDealerMoonPoint)
		{
			if (op->m_assist.FindByItemIndex(12559))
				op->m_assist.CureByItemIndex(12559);
			op->m_syndicateManager.increaseSyndicatePoint(1 * multiplier);
		}
		else
		{
			if (op->m_assist.FindByItemIndex(12559))
				op->m_assist.CureByItemIndex(12559);
			op->m_syndicateManager.increaseSyndicatePoint(1 * multiplier);
		}
	}
	else if(op->getSyndicateType() == SYNDICATE::eSYNDICATE_DEALERMOON)
	{
		if (jewelKailuxPoint < jewelDealerMoonPoint)
		{
			if (op->m_assist.FindByItemIndex(12559))
				op->m_assist.CureByItemIndex(12559);
			op->m_syndicateManager.increaseSyndicatePoint(1 * multiplier);
		}
		else
		{
			if (op->m_assist.FindByItemIndex(12559))
				op->m_assist.CureByItemIndex(12559);
			op->m_syndicateManager.increaseSyndicatePoint(1 * multiplier);
		}
	}
}

void ProcDead_PD2(CNPC* df)
{
	if (df->m_pZone->m_index == ZONE_SINGLE_DUNGEON2)
	{
		CCharacter* ch = NULL;
		CPC* pc = NULL;

		int i, j;
		for (i = 0; i < df->m_pArea->m_size[0]; i++)
		{
			for (j = 0; j < df->m_pArea->m_size[1]; j++)
			{
				ch = df->m_pArea->m_cell[i][j].m_listChar;
				while (ch)
				{
					if (IS_PC(ch) && !DEAD(ch))
					{
						pc = TO_PC(ch);
						break;
					}
					ch = ch->m_pCellNext;
				}
			}
		}

		if (!pc)
			return ;

		// ����Ʈ ����
		CQuest* pQuest = NULL;
		CQuest* pQuestNext = NULL;
		const CQuestProto* pQuestProto = NULL;
		pQuestNext = pc->m_questList.GetNextQuest(NULL, QUEST_STATE_RUN);
		while ((pQuest = pQuestNext))
		{
			pQuestNext = pc->m_questList.GetNextQuest(pQuestNext, QUEST_STATE_RUN);
			// ������ ����Ʈ �̰�
			if (pQuest->GetQuestType0() == QTYPE_KIND_SAVE)
			{
				pQuestProto = pQuest->GetQuestProto();
				int j;
				for (j = 0; j < QUEST_MAX_CONDITION; j++)
				{
					// ���� df�� ������ ���� �̸�
					if (pQuestProto->m_conditionType[j] == QCONDITION_NPC &&
							pQuestProto->m_conditionIndex[j] == df->m_proto->m_index)
					{
						// ������ ����
						pQuest->RemoeQuestItem(pc);

						// Quest Fail Log
						GAMELOG << init("QUEST FAIL", pc)
								<< pQuestProto->m_index
								<< end;

						CNetMsg::SP rmsg(new CNetMsg);
						QuestFailMsg(rmsg, pQuest);
						pc->m_questList.DelQuest(pc, pQuest);
						SEND_Q(rmsg, pc->m_desc);
						return ;
					}
				}
			}
		} // while (pQuest)
	}
}

#ifdef PARTY_QUEST_ITEM_BUG_
void ProcDeadQuestProc(CPC * opc,CNPC * df, int partyScale)
{
#ifdef HUNT_QUEST_COMPLETE_FOR_OTHER_PARTYMEMBER
	// ��Ƽ �������� ����� �Ѿ���� �������.
	// ��Ÿģ����� ����������, ��Ƽ����, �ַ������� üũ�Ѵ�.
	// �������� ��� ������ ����Ʈ�� ����ȴ�. �ַ�����Ʈ�� ������ �ȵȴ�.
	// �ַγ� ��Ƽ�ϰ�� �ڱ� ����Ʈ�� �ǰ�, ��Ƽ�� ����Ʈ�� ���� �ȴ�.
	if(opc->IsExped())
	{
		// ������ ����Ʈ
		int i, j;
		CPC* pExpedPC = NULL;
		if(opc->m_Exped)
		{
			for(i = 0; i < MAX_EXPED_GROUP; i++)
			{
				for(j = 0; j < MAX_EXPED_GMEMBER; j++)
				{
					pExpedPC = opc->m_Exped->GetMemberPCPtr(i, j);
					if(pExpedPC == NULL)
						continue;

					if(opc->m_pArea->FindCharInCell(opc, pExpedPC->m_index, MSG_CHAR_PC))
					{
						CQuest* pQuest = NULL;
						CQuest* pQuestNext = pExpedPC->m_questList.GetNextQuest(NULL, QUEST_STATE_RUN);
						while((pQuest = pQuestNext))
						{
							pQuestNext = pExpedPC->m_questList.GetNextQuest(pQuestNext, QUEST_STATE_RUN);
							switch(pQuest->GetQuestType0())
							{
							case QTYPE_KIND_REPEAT:
							case QTYPE_KIND_COLLECTION:
							case QTYPE_KIND_DEFEAT:
							case QTYPE_KIND_SAVE:
								{
									if(pQuest->GetPartyScale() == QTYPE_SCALE_BATTLEGROUP)
										pQuest->QuestUpdateData(pExpedPC, df);
								}
								break;
							default:
								break;
							}
						}
					}
				}
			}
		}
		return ;
	}
	else
	{
		if(!opc->IsParty()) // ��Ƽ�� ������ ���� ����Ʈ ������Ʈ
		{
			CQuest* pQuest = NULL;
			CQuest* pQuestNext = opc->m_questList.GetNextQuest(NULL, QUEST_STATE_RUN);
			while((pQuest = pQuestNext))
			{
				pQuestNext = opc->m_questList.GetNextQuest(pQuestNext, QUEST_STATE_RUN);
				switch(pQuest->GetQuestType0())
				{
				case QTYPE_KIND_REPEAT:
				case QTYPE_KIND_COLLECTION:
				case QTYPE_KIND_DEFEAT:
				case QTYPE_KIND_SAVE:
					{
						if(pQuest->GetPartyScale() == QTYPE_SCALE_PERSONAL || pQuest->GetPartyScale() == QTYPE_SCALE_PARTY)
							pQuest->QuestUpdateData(opc, df);
					}
					break;
				default:
					break;
				}
			}
			return ;
		}
		else
		{
			int i;
			CPartyMember* pPartyMember = NULL;
			CPC* pMember = NULL;
			for(i = 0; i < MAX_PARTY_MEMBER; i++)
			{
				pPartyMember = opc->m_party->GetMemberByListIndex(i);
				if(pPartyMember && pPartyMember->GetMemberPCPtr())
				{
					pMember = pPartyMember->GetMemberPCPtr();
					if(opc->m_pArea->FindCharInCell(opc, pMember->m_index, MSG_CHAR_PC))
					{
						CQuest* pQuest = NULL;
						CQuest* pQuestNext = pMember->m_questList.GetNextQuest(NULL, QUEST_STATE_RUN);
						while((pQuest = pQuestNext))
						{
							pQuestNext = pMember->m_questList.GetNextQuest(pQuestNext, QUEST_STATE_RUN);
							switch(pQuest->GetQuestType0())
							{
							case QTYPE_KIND_REPEAT:
							case QTYPE_KIND_COLLECTION:
							case QTYPE_KIND_DEFEAT:
							case QTYPE_KIND_SAVE:
								{
									if(pQuest->GetPartyScale() == QTYPE_SCALE_PERSONAL || pQuest->GetPartyScale() == QTYPE_SCALE_PARTY)
										pQuest->QuestUpdateData(pMember, df);
								}
								break;
							default:
								break;
							}
						}
					}
				}
			}
		}
	}

#else // HUNT_QUEST_COMPLETE_FOR_OTHER_PARTYMEMBER
	CQuest* pQuest = NULL;
	CQuest* pQuestNext = opc->m_questList.GetNextQuest(NULL, QUEST_STATE_RUN);

	while ((pQuest = pQuestNext))
	{
		pQuestNext = opc->m_questList.GetNextQuest(pQuestNext, QUEST_STATE_RUN);
		// ����Ʈ �ְ� �������̰� �ݺ�, ����, ����, ���� ����Ʈ�̸�
		if( (partyScale == QTYPE_SCALE_PARTY && pQuest->GetPartyScale() != QTYPE_SCALE_PARTY )
#ifdef _BATTLEGROUP_QUEST_BUG_PIX
				|| (partyScale == QTYPE_SCALE_BATTLEGROUP && pQuest->GetPartyScale() != QTYPE_SCALE_BATTLEGROUP )
#endif // _BATTLEGROUP_QUEST_BUG_PIX
		  )
		{
			return;
		}

		switch (pQuest->GetQuestType0() )
		{
		case QTYPE_KIND_REPEAT:
		case QTYPE_KIND_COLLECTION:
		case QTYPE_KIND_DEFEAT:
		case QTYPE_KIND_SAVE:
			pQuest->QuestUpdateDataForParty(opc, df);
			break;

		default:
			break;
		}
	}
#endif // HUNT_QUEST_COMPLETE_FOR_OTHER_PARTYMEMBER
}
#endif // PARTY_QUEST_ITEM_BUG_
//

#ifdef BATTLE_PASS_SYSTEM
void ProcDeadBattlePass(CPC* opc, CNPC* df)
{
	if (opc->m_battlePassLevel >= gserver->m_listBattlePass.size())
		return;
	
	CBattlePass * bp = gserver->m_listBattlePass[opc->m_battlePassLevel];
	if (bp == NULL)
		return;
	
	int calculatedPoints = 10 * df->m_level + 400;
	if (opc->m_assist.FindByItemIndex(12195))
	{
		calculatedPoints *= 2;
		opc->m_assist.CureByItemIndex(12195);
	}

	if (opc->m_battlePassPremium)
		calculatedPoints *= 2;
	
	bool bWasBelow = opc->m_battlePassPoints < bp->m_points;

	opc->m_battlePassPoints += calculatedPoints;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_EXTEND);
		RefMsg(rmsg) << MSG_EX_STRING
			<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
			<< 8534
			<< 1
			<< 1
			<< calculatedPoints;
		SEND_Q(rmsg, opc->m_desc);
	}

	// Notify player when they have enough points to claim a reward
	if (bWasBelow && opc->m_battlePassPoints >= bp->m_points)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_EXTEND);
		RefMsg(rmsg) << MSG_EX_STRING
			<< (unsigned char)MSG_EX_STRING_OUTPUT_NOTICE
			<< 9429 // Add string: "You have a Battle Pass reward ready to claim!"
			<< 0;
		SEND_Q(rmsg, opc->m_desc);
	}

}
#endif