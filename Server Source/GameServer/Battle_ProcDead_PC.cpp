#include "stdhdrs.h"

#include "Server.h"
#include "Battle.h"
#include "WarCastle.h"
#include "CmdMsg.h"
#include "Exp.h"
#include "Log.h"
#include "doFunc.h"
#include "Artifact_Manager.h"
#include "../ShareLib/packetType/ptype_old_do_item.h"
#include "../ShareLib/packetType/ptype_old_do_skill.h"


void ProcRVR(CPC* df, CCharacter* of);
void ProcDeadQuestProc(CPC* df, CPC* of);

void ProcDead(CPC* df, CCharacter* of)
{
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if (df != NULL)
	{
		pCastle->CheckRespond(df);
	}

	const char* strOFType = "UNKNOWN";
	const char* strOFName = "UNKNOWN";
	int strOFIndex = 0;

	CPC*		opc				= NULL;
	CNPC*		onpc			= NULL;
	CPet*		opet			= NULL;
	CElemental*	oelemental		= NULL;
	CAPet*		oapet			= NULL;

	if( IS_NPC(of) && TO_NPC(of)->Check_MobFlag(STATE_MONSTER_MERCENARY) && TO_NPC(of)->GetOwner() )
	{
		TO_NPC(of)->GetOwner()->SetSummonOwners_target(NULL);
	}

	switch (of->m_type)
	{
	case MSG_CHAR_PC:
		opc = TO_PC(of);
		strOFType = "PC";
		strOFName = opc->GetName();
		strOFIndex = opc->m_index;
		break;

	case MSG_CHAR_NPC:
		onpc = TO_NPC(of);
		strOFType = "NPC";
		strOFName = onpc->m_name;
		strOFIndex = onpc->m_idNum;
		break;

	case MSG_CHAR_PET:
		opet = TO_PET(of);
		opc = opet->GetOwner();
		if (opc == NULL)
			return ;
		strOFType = "PET";
		strOFName = opc->GetName();
		strOFIndex = opc->m_index;
		break;

	case MSG_CHAR_ELEMENTAL:
		oelemental = TO_ELEMENTAL(of);
		opc = oelemental->GetOwner();
		if (opc == NULL)
			return ;
		strOFType = "ELEMENTAL";
		strOFName = opc->GetName();
		strOFIndex = opc->m_index;
		break;
	case MSG_CHAR_APET:
		oapet = TO_APET(of);
		opc = oapet->GetOwner();
		if (opc == NULL)
			return ;
		strOFType = "APET";
		strOFName = opc->GetName();
		strOFIndex = opc->m_index;
		break;

	default:
		return ;
	}

	if( opc )
		opc->SetSummonOwners_target(NULL);

	// NPC�� ���� ����� ��� �г�Ƽ�� �⺻���� true, PC���� ����� ��� �г�Ƽ�� �⺻���� false
	// * bPKPenalty������ pk �г�Ƽ�� �ִ°� �Ӹ� �ƴ϶� ����ȸ������ ����ǹǷ� ���� ȸ���̳� �г�Ƽ�� ����Ϳ��� �ɸ��� true

	bool bPvP = (opc) ? true : false;
	bool bPKPenalty = (opc) ? IsPK(opc, df) : false;
	bool bDeadPenalty = (bPvP) ? false : true;
	// �Ʒ� boolean������ ����� �������� ���� �̷������ �մϴ�.
	// bool bRestorePKOfDefensePC = true; �̷������� ������ �ϸ� UPDATE1106������ ������� �ʴ� ������ warning�� ����մϴ�.

	//��ȯNPC���� �׾��� ��� ó�� (EX Ʈ��) - Ʈ���� ��쿡 Ÿ���� NPC�� ����ϰ� ����...�Ѥ�;;
	if(IS_NPC(of))
	{
		CNPC* npc = TO_NPC(of);
		if(npc->m_owner = nullptr)  //c++17 linux pwesty 
		{
			bPvP = false;
			bPKPenalty = true;
			bDeadPenalty = false;
		}
	}

	bool bRestorePKOfDefensePC;
	bRestorePKOfDefensePC = true;

	// ���� ����
	if (df->IsSetPlayerState(PLAYER_STATE_CHANGE))
		df->CancelChange();

	if (opc)
	{
#ifdef FREE_PK_SYSTEM
		if( !gserver->m_bFreePk )
		{
#endif // FREE_PK_SYSTEM

#ifdef MAL_DISABLE_PKPENALTY
			if( gserver->m_bDisablePKPaenalty )
				bDeadPenalty = true;
			else if( !gserver->m_bDisablePKPaenalty )
			{
#endif // MAL_DISABLE_PKPENALTY
				// df�� pk��� �̰ų� ī���� �Ѵ� Ʈ��
				if (df->IsSetPlayerState(PLAYER_STATE_PKMODE) || df->IsChaotic())
					bDeadPenalty = true;
#ifdef MAL_DISABLE_PKPENALTY
			}
#endif // MAL_DISABLE_PKPENALTY

#ifdef FREE_PK_SYSTEM
		}
#endif // FREE_PK_SYSTEM

		// �����
		if (opc->m_guildInfo && (opc->m_guildInfo->guild()->battleState() == GUILD_BATTLE_STATE_ING) &&
				df->m_guildInfo && (df->m_guildInfo->guild()->battleState() == GUILD_BATTLE_STATE_ING))
		{
			if (opc->m_guildInfo->guild()->battleIndex() == df->m_guildInfo->guild()->index() &&
					df->m_guildInfo->guild()->battleIndex() == opc->m_guildInfo->guild()->index())
			{
				bDeadPenalty = false;

				int killCount = opc->m_guildInfo->guild()->killCount();

				killCount++;

				if (gserver->isRunHelper())
				{
					CNetMsg::SP rmsg(new CNetMsg);
					HelperGuildBattleKillReqMsg(rmsg, opc->m_guildInfo->guild()->index(), df->m_guildInfo->guild()->index());
					SEND_Q(rmsg, gserver->m_helper);
				}
				else
				{
					GAMELOG << init("GUILD_BATTLE")
							<< "if( gserver->isRunHelper() ) false" << delim
							<< end;
					CNetMsg::SP rmsg(new CNetMsg);
					GuildErrorMsg(rmsg, MSG_GUILD_ERROR_GAMESERVER);
					SEND_Q(rmsg, opc->m_desc);
				}
			}
		}
	} // �����ڰ� PC �Ǵ� PC�� �������϶�

	// ���� ����Ʈ ���
	if (opc)
		CalcWarPoint(opc, df);
	else
		CalcWarPoint(of, df);

	// ���� ���� ����� �г�Ƽ ����
	CWarCastle* castle = CWarCastle::GetCastleObject(df->m_pZone->m_index);
	if (castle && castle->GetState() != WCSF_NORMAL && (df->GetMapAttr() & MATT_WAR || df->m_pZone->IsWarZone((int)df->m_pos.m_x, (int)df->m_pos.m_z)))
	{
		DropWarCastleTokenDeadPC(df);
		bDeadPenalty = false;
	}
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	if (df && df->m_pZone && (df->m_pZone->m_index == ZONE_PARTY_DUNGEON0
		|| df->m_pZone->m_index == ZONE_PARTY_DUNGEON1
		|| df->m_pZone->m_index == ZONE_PARTY_DUNGEON2
		|| df->m_pZone->m_index == ZONE_PARTY_DUNGEON3
		|| df->m_pZone->m_index == ZONE_PARTY_DUNGEON4
		)
		)
	{
		if (df->m_pArea->m_CTriggerList.m_PcDeadPenaltyTime == 0)
			df->m_pArea->m_CTriggerList.m_PcDeadPenaltyTime = 1;
	}
#endif
	/////////////////////////////////////////////
	// BANGWALL : 2005-07-18 ���� 11:27:24
	// Comment : freepkzone �г�Ƽ ����
	// �����ڿ� ����ڰ� ��� freepkzone�� ������ pkpenalty ����
	if( of->GetMapAttr() == df->GetMapAttr() && of->GetMapAttr() & MATT_FREEPKZONE)
		bDeadPenalty = false;

	// PvP���� PK ����
	if (opc && bPvP && bPKPenalty)
		CalcPKPoint(opc, df, false);

	bool bDeadExpPenalty = true;

#ifdef FREE_PK_SYSTEM
	if( gserver->m_bFreePk )
	{
		if(!bDeadPenalty)
			bDeadExpPenalty = false;
	}
#endif // FREE_PK_SYSTEM

#if defined(LC_BILA)
	if (bPvP)
#ifdef MAL_DISABLE_PKPENALTY
		if( gserver->m_bDisablePKPaenalty )
		{
			bDeadExpPenalty = false;
		}
#endif // MAL_DISABLE_PKPENALTY
#endif

	// �۽��� ������ ������ �г�Ƽ ����
	if (df->m_pZone->IsPersonalDungeon())
		bDeadPenalty = false;

	// ����ġ �϶�
	LONGLONG nLoseExp = 0;
	LONGLONG nLoseSP = 0;

	// �϶��� ����ġ�� �ֱ� �͸� ���
	df->m_loseexp = 0;
	df->m_losesp = 0;

	if( df->m_skillPoint < 0 )
		df->m_skillPoint = 0;

	//�����ڰ� ���Ҽ��� ��츸 ��� ���Ƽ ����
	if (df->m_pZone->isRVRZone())
	{
		if(df->getSyndicateType() == 0)
			bDeadPenalty = true;
		else
			bDeadPenalty = false;
	}

	if (bDeadPenalty)
	{
		if (bDeadExpPenalty)
		{
			// ����� �г�Ƽ
			if (df->m_level < 11)
			{
				/*				nLoseExp = (LONGLONG)(GetLevelupExp(df->m_level) * DEATH_PENALTY_EXP_1);
								nLoseSP = (LONGLONG)(df->m_skillPoint * DEATH_PENALTY_SP_1);*/
				nLoseExp = 0;
				nLoseSP = 0;
			}
			else if (df->m_level < 21)
			{
				/* 5% */
				/*				nLoseExp = (LONGLONG)(GetLevelupExp(df->m_level) * DEATH_PENALTY_EXP_2);
								nLoseSP = (LONGLONG)(df->m_skillPoint * DEATH_PENALTY_SP_2);*/
				nLoseExp = (LONGLONG)((GetLevelupExp(df->m_level) / 100) * 5);
				nLoseSP = (LONGLONG)((df->m_skillPoint / 100) * 5);
			}
			else if (df->m_level < 36)
			{
				/*				nLoseExp = (LONGLONG)(GetLevelupExp(df->m_level) * DEATH_PENALTY_EXP_3);
								nLoseSP = (LONGLONG)(df->m_skillPoint * DEATH_PENALTY_SP_3);*/
				nLoseExp = (LONGLONG)((GetLevelupExp(df->m_level) / 100) * 3);
				nLoseSP = (LONGLONG)((df->m_skillPoint / 100) * 3);
			}
			else
			{
				/*				nLoseExp = (LONGLONG)(GetLevelupExp(df->m_level) * DEATH_PENALTY_EXP_4);
								nLoseSP = (LONGLONG)(df->m_skillPoint * DEATH_PENALTY_SP_4);*/
				nLoseExp = (LONGLONG)((GetLevelupExp(df->m_level) / 100) * 2);
				nLoseSP = (LONGLONG)((df->m_skillPoint / 100) * 2);
			}

			// ������ ���� �ø��� ����
			switch (df->m_assist.m_avAddition.hcDeathExpPlus)
			{
			case 1:
				{
					nLoseExp -= 50000;
					if(nLoseExp < 0)
						nLoseExp = 0;
				}
				break;
			case 2:
				{
					nLoseExp -= 600000;
					if(nLoseExp < 0)
						nLoseExp = 0;
				}
				break;
			case 3:
				{
					nLoseExp /= 2;
				}
				break;
			default:
				break;
			}

			// ����� ���� ����
			if (df->m_assist.m_avAddition.hcDeathSPPlus)
				nLoseSP /= 2;
		}

#ifdef FREE_PK_SYSTEM
		if( !gserver->m_bFreePk )
		{
#endif // FREE_PK_SYSTEM

#ifdef MAL_DISABLE_PKPENALTY
			if( !gserver->m_bDisablePKPaenalty )
			{
#endif // MAL_DISABLE_PKPENALTY
				if (df->IsChaotic())
				{
#ifndef REFORM_PK_PENALTY_201108 // PK �г�Ƽ ���� :: ��� ��� ���� ��� ����
// TODO : DELETE			bSaveLose = false;
					bool bseal = false;

					if (df->m_pkPenalty <= -130)
					{
						nLoseExp = nLoseExp * 225 / 100;
						bseal = (GetRandom(1, 100) <= 13) ? true : false;
					}
					else if (df->m_pkPenalty <= -100)
					{
						nLoseExp = nLoseExp * 200 / 100;
						bseal = (GetRandom(1, 100) <= 11) ? true : false;
					}
					else if (df->m_pkPenalty <=  -70)
					{
						nLoseExp = nLoseExp * 175 / 100;
						bseal = (GetRandom(1, 100) <=  9) ? true : false;
					}
					else if (df->m_pkPenalty <=  -40)
					{
						nLoseExp = nLoseExp * 150 / 100;
						bseal = (GetRandom(1, 100) <=  7) ? true : false;
					}
					else if (df->m_pkPenalty <=  -10)
					{
						nLoseExp = nLoseExp * 125 / 100;
						bseal = (GetRandom(1, 100) <=  5) ? true : false;
					}

					if (bseal)
					{
						CItem* table[MAX_WEARING];
						memset(table, 0, sizeof(CItem*) * MAX_WEARING);
						int i = 0, j = 0;
						while (i < MAX_WEARING)
						{
							if (df->m_wearInventory.wearItemInfo[i] && !(df->m_wearInventory.wearItemInfo[i]->getFlag() & FLAG_ITEM_SEALED))
							{
								// ��� ���� ���� �Ǵ��� ����
								switch (i)
								{
								case WEARING_HELMET:
								case WEARING_ARMOR_UP:
								case WEARING_WEAPON:
								case WEARING_ARMOR_DOWN:
								case WEARING_SHIELD:
								case WEARING_GLOVE:
								case WEARING_BOOTS:
									if(!(df->m_wearInventory.wearItemInfo[i]->m_itemProto->getItemFlag() & ITEM_FLAG_COSTUME2))
										table[j] = df->m_wearInventory.wearItemInfo[i];
									j++;
									break;

								default:
									break;
								}
							}
							i++;
						}
						if (j)
						{
							i = GetRandom(0, j - 1);

							if (table[i])
							{
								table[i]->setFlag(table[i]->getFlag() | FLAG_ITEM_SEALED);

								{
									CNetMsg::SP rmsg(new CNetMsg);
									UpdateClient::makeUpdateItemFlag(rmsg, table[i]->tab(), table[i]->getInvenIndex(), table[i]->getFlag());
									SEND_Q(rmsg, df->m_desc);
								}

								{
									CNetMsg::SP rmsg(new CNetMsg);
									PKItemSealMsg(rmsg, table[i]);
									SEND_Q(rmsg, df->m_desc);
								}

								GAMELOG << init("ITEM SEAL" , df)
										<< "ITEM" << delim
										<< itemlog(table[i])
										<< end;
							}
						}
					}
#endif // REFORM_PK_PENALTY_201108 // PK �г�Ƽ ���� :: ��� ��� ���� ��� ����
					if (nLoseExp < 0)
						nLoseExp = 0;
					if (nLoseSP < 0)
						nLoseSP = 0;

					// 060318 : bs : ���� ��� ī��PC PvP �ÿ��� ���� ��� ȸ�� ����
					//             : ����ī���� �����̸� ȸ�� ����
					// ���� ȸ��

#ifndef REFORM_PK_PENALTY_201108 // PK �г�Ƽ ���� :: ī�� ����� ���� ȸ�� ����
					if (bRestorePKOfDefensePC)
					{
						if( !gserver->m_bNonPK )
							df->m_pkPenalty += 5;

						if (df->m_pkPenalty > 0)
							df->m_pkPenalty = 0;
					}

					{
						// ���Ƽ ��ġ ���� �˸���
						CNetMsg::SP rmsg(new CNetMsg);
						CharStatusMsg(rmsg, df, 0);
						df->m_pArea->SendToCell(rmsg, df, false);
					}

					df->m_bChangeStatus = true;
					df->CalcStatus(true);

#endif // REFORM_PK_PENALTY_201108 // PK �г�Ƽ ���� :: ī�� ����� ���� ȸ�� ����
				}
				else
				{
					if (df->m_exp < nLoseExp)
						nLoseExp = df->m_exp;
				}
#ifdef MAL_DISABLE_PKPENALTY
			}
			else
			{
				if( df->m_exp < nLoseExp )
					nLoseExp = df->m_exp;
			}
#endif
#ifdef FREE_PK_SYSTEM
		}
		else
		{
			if( df->m_exp < nLoseExp )
				nLoseExp = df->m_exp;
		}
#endif // FREE_PK_SYSTEM


		if (bDeadExpPenalty)
		{
			if (nLoseExp < 0)
				nLoseExp = 0;
			if (nLoseSP < 0)
				nLoseSP = 0;
			if (df->m_skillPoint < nLoseSP)
				nLoseSP = df->m_skillPoint;
// ����ġ - ����
			if ( df->m_exp < nLoseExp )
				nLoseExp = df->m_exp;

// ����
			if(df->m_pZone->IsComboZone())
			{
				nLoseExp = nLoseExp / 10;
				nLoseSP = nLoseSP / 10;
			}
			df->m_exp -= nLoseExp;
			if (df->m_exp < 0)
				df->m_exp = 0;

			df->m_skillPoint -= nLoseSP;
			if (df->m_skillPoint < 0)
				df->m_skillPoint = 0;

			df->m_bChangeStatus = true;

// TODO : DELETE			if (bSaveLose)
// TODO : DELETE			{
			df->m_loseexp = nLoseExp;
			df->m_losesp = nLoseSP;
// TODO : DELETE			}
		}
	} // ��� �г�Ƽ ����

	// Accessory ������
	int i;
	for (i = WEARING_ACCESSORY1; i <= WEARING_ACCESSORY3; i++)
	{
		if (!df->m_wearInventory.wearItemInfo[i] || df->m_wearInventory.wearItemInfo[i]->m_itemProto->getItemMaxUse() == -1)
			continue;

		df->m_wearInventory.wearItemInfo[i]->setUsed(df->m_wearInventory.wearItemInfo[i]->getUsed() - ACCESSORY_USED_DEATH);

		// �Ǽ��縮 �Ҹ�
		if (df->m_wearInventory.wearItemInfo[i]->getUsed() <= 0)
		{
			df->m_wearInventory.wearItemInfo[i]->setUsed(0);
			df->CalcStatus(true);
		}
	}

	/*int skillIdToPreserve = 179;
	int savedLevel = df->m_assist.FindBySkillIndex(skillIdToPreserve);
	int savedRemain = df->m_assist.GetRemainingTimeBySkillIndex(skillIdToPreserve);

	df->m_assist.ClearAssist(true, false, true, true, false);

	if (savedLevel > 0 && savedRemain > 0)
	{
		const CSkillProto* proto = gserver->m_skillProtoList.Find(skillIdToPreserve);
		if (proto)
		{
			const CSkillLevelProto* levelProto = proto->Level(savedLevel);
			if (!levelProto)
			{
				savedLevel = 1;
				levelProto = proto->Level(1);
			}

			if (levelProto)
			{
				bool bHit[MAX_SKILL_MAGIC] = { true, false, false };
				df->m_assist.Add(df, -1, proto, savedLevel, bHit, true,
					savedRemain,
					levelProto->m_useCount,
					0, 0, 0);
			}
		}
	}*/

	if (!df->m_premiumChar.isActive())
		df->m_assist.ClearAssist(true, false, true, true, false); //pwesty fix   //buff lock
	else
		df->m_assist.ClearAssist(true, false, false, true, false); //pwesty fix

	// �������̸� ���
	if (df->IsSetPlayerState(PLAYER_STATE_WARP))
	{
		df->m_reqWarpTime = 0;
		df->m_reqWarpType = -1;
		df->m_reqWarpData = -1;

		df->m_reqWarpTime_skill = -1;
		df->m_reqWarpType_skill = -1;
		df->m_reqWarpData_skill = -1;
	}

	df->ResetPlayerState(PLAYER_STATE_SITDOWN | PLAYER_STATE_MOVING | PLAYER_STATE_WARP | PLAYER_STATE_PKMODE | PLAYER_STATE_DARKNESS | PLAYER_STATE_SKILL);// fix skill bug on death REZA JOSH

	CPet* pet = df->GetPet();
	if (pet)
	{
		if (pet->IsMountType())
		{
			if(df->m_pZone != NULL && df->m_pZone->m_bCanMountPet == true)
			{
				// ��� ����
				pet->SetRemainRebirthTime();
			}
		}

		{
			// �� ���� ����
			CNetMsg::SP rmsg(new CNetMsg);
			ExPetStatusMsg(rmsg, pet);
			SEND_Q(rmsg, df->m_desc);
		}
	}

#ifdef LC_USA
	CAPet* apet = df->GetAPet();
	if(apet)
	{
		{
			// �� ���� ����
			CNetMsg::SP rmsg(new CNetMsg);
			ExAPetStatusMsg(rmsg, apet);
			SEND_Q(rmsg, df->m_desc);
		}
	}
#endif // LC_USA

	// ��ȯ ���
	while (df->m_elementalList)
		df->UnsummonElemental(df->m_elementalList);
	// ���� ���
	if (df->m_evocationIndex != EVOCATION_NONE)
		df->Unevocation();
	// ���� �ð� �ʱ�ȭ
	df->m_pulseEvocation[0] = 0;
	df->m_pulseEvocation[1] = 0;


	


	// new pvp msg chat system by alan
	if (IS_PC(of)) {

		CNetMsg::SP rmsg(new CNetMsg);
		CPC * pcOf = TO_PC(of);

#ifdef WINS_LOSES
		pcOf->m_wins += 1;
		df->m_loses += 1;
#endif

#ifdef WARFARE_BATTLE
		if (of->IsBattleWarfare()) {
			if (gserver->m_BattleWarfare.IsActive() && pcOf->IsZoneBattleWarfare()) {
				CItem* pItem = gserver->m_itemProtoList.CreateItem(gserver->m_BattleWarfare.getItemIdx(), -1, 0, 0, gserver->m_BattleWarfare.getItemCount());
				if (pItem) {
					pcOf->m_inventory.addItem(pItem);
				}
			}
		} 
		else
#endif
		{
			//if defender has the flag item index
				
			{
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsgPlayerDead(rmsg, pcOf->m_desc->m_pChar->m_nick, df->m_desc->m_pChar->m_nick);
				PCManager::instance()->sendToAll(rmsg);
			}
		}
	}
#ifdef CAPTURE_THE_FLAG_10282021
	if (IS_PC(df))
	{
		if (df->m_inventory.FindByDBIndex(12272) != NULL)
		{

			CItem* pitem11272 = NULL;
			pitem11272 = df->m_inventory.FindByDBIndex(12272, 0, 0);

			item_search_t vec_pvpflagitem;

			int sc = df->m_inventory.searchItemByCondition(12272, 0, 0, vec_pvpflagitem);
			// make sure the user doesnt have more then he should of the item
			if (sc == 0 || sc < 1)
				return;
			//delete item from inventory user died
			df->m_inventory.deleteItem(vec_pvpflagitem, 1);
			
			CQuest* pQuest = df->m_questList.FindQuest(818);
			if (pQuest && pQuest->GetQuestState() == QUEST_STATE_RUN)
			{
				df->m_questList.SetQuestState(pQuest, QUEST_STATE_ABANDON);

				{
					CNetMsg::SP rmsg(new CNetMsg);
					QuestForceGiveUpMsg(rmsg, pQuest);
					df->m_questList.DelQuest(df, pQuest);
					SEND_Q(rmsg, df->m_desc);
				}
				df->m_questList.DecreaseQuestComepleteCount();
			}

			df->m_bHasFlagItem = false;

			int npcindex = 1704;
			//make sure the npc isn't null (crash)
			CNPC* npc = gserver->m_npcProtoList.Create(npcindex, NULL);
			if (!npc)
				return;
			//grab the information for the mob from the dead player
			GET_X(npc) = GET_X(df);
			GET_Z(npc) = GET_Z(df);
			GET_YLAYER(npc) = GET_YLAYER(df);
			GET_R(npc) = GetRandom(0, (int)(PI_2 * 10000)) / 10000;

			if (df->m_pArea->GetAttr(GET_YLAYER(npc), GET_X(npc), GET_Z(npc)) & MATT_WALKABLE) {}


			npc->m_regenX = GET_X(npc);
			npc->m_regenY = GET_YLAYER(npc);
			npc->m_regenZ = GET_Z(npc);

			int cx, cz;
			df->m_pArea->AddNPC(npc);
			df->m_pArea->PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
			df->m_pArea->CharToCell(npc, GET_YLAYER(npc), cx, cz);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, npc, true);
				df->m_pArea->SendToCell(rmsg, GET_YLAYER(npc), cx, cz);
			}

			{
				//annouce message to all with flag position
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsgFlagDead(rmsg, df->m_desc->m_pChar->m_nick, df->m_pos.m_x, df->m_pos.m_z);
				PCManager::instance()->sendToAll(rmsg);
			}

		}
	}
#endif

	if ( of->m_currentSkill != NULL )
	{
		of->m_currentSkill->Cancel(of);
		of->m_currentSkill = NULL;
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeSkillCancelMsg(rmsg, of);
		of->m_pArea->SendToCell(rmsg, of, true);
	}

	if ( df->m_currentSkill != NULL )
	{
		df->m_currentSkill->Cancel(df);
		df->m_currentSkill = NULL;
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeSkillCancelMsg(rmsg, df);
		df->m_pArea->SendToCell(rmsg, df, true);
	}

#ifdef GER_LOG
	GAMELOGGEM << init( 0, "CHAR_DEATH")
			   << LOG_VAL("account-id", df->m_desc->m_idname ) << blank
			   << LOG_VAL("character-id", df->m_desc->m_pChar->m_name ) << blank
			   << LOG_VAL("zone-id", df->m_desc->m_pChar->m_pZone->m_index ) << blank
			   << LOG_VAL("from-id", strOFType ) << blank
			   << LOG_VAL("opponent-id", strOFIndex ) << blank
			   << LOG_VAL("longitude", GET_X(df) ) << blank
			   << LOG_VAL("latitude", GET_Z(df) ) << blank
			   << endGer;

	if ( IS_PC(of) )
	{
		CPC *user = TO_PC(of);
		GAMELOGGEM << init( 0, "CHAR_VICTORY")
				   << LOG_VAL("account-id", user->m_desc->m_idname ) << blank
				   << LOG_VAL("character-id", user->m_desc->m_pChar->m_name ) << blank
				   << LOG_VAL("zone-id", user->m_desc->m_pChar->m_pZone->m_index ) << blank
				   /*<< LOG_VAL("from-id", strOFType ) << blank*/
				   << LOG_VAL("opponent-id", df->m_desc->m_idname ) << blank
				   << LOG_VAL("longitude", GET_X(user) ) << blank
				   << LOG_VAL("latitude", GET_Z(user) ) << blank
				   << endGer;
	}
#endif // GER_LOG
	// �α�
	GAMELOG << init("CHAR_DEATH", df)
			<< "BY" << delim
			<< strOFType << delim
			<< strOFName << delim
			<< strOFIndex << delim
			<< "LOSE EXP" << delim
			<< nLoseExp << delim
			<< "CUR EXP" << delim
			<< df->m_exp << delim
			<< "LOSE SP" << delim
			<< nLoseSP << delim
			<< "CUR SP" << delim
			<< df->m_skillPoint
			<< "POS_X" << delim
			<< GET_X(df) << delim
			<< "POS_Z" << delim
			<< GET_Z(df) << delim
			<< "YLAYER" << delim
			<< GET_YLAYER(df) << delim
			<< "HEIGHT" << delim
			<< GET_H(df)
			<< end;

	DelAttackList(df);

	// ������� ����
	DelRaList(df);

	if (pCastle != NULL)
	{
		if (df->GetJoinFlag(ZONE_DRATAN) != WCJF_NONE
				&& pCastle->GetState() != WCSF_NORMAL
				&& (df->GetMapAttr() & MATT_WAR || df->m_pZone->IsWarZone((int)df->m_pos.m_x, (int)df->m_pos.m_z) ) )
		{
			// �����߿� ��������
			int wait_time = -1;
			switch(df->GetJoinFlag(ZONE_DRATAN))
			{
			case WCJF_ATTACK_GUILD:
				// ��Ȱ���Ⱑ ������ ��Ȱ��� �ð� 20��, ������ 60��
				wait_time = 60;
				if (df->m_guildInfo != NULL
						&& df->m_guildInfo->guild() != NULL)
				{
					for(int i=0; i<7; i++)
					{
						if (df->m_guildInfo->guild()->index() == pCastle->m_nRebrithGuild[i])
						{
							wait_time = 20;
							break;
						}
					}
				}
				break;
			case WCJF_OWNER:
			case WCJF_DEFENSE_GUILD:
				//  ��Ȱ��� �ð� 60�� - ����Ÿ������*10
				int count = 0;
				for(int i=0; i<5; i++)
				{
					if(pCastle->m_pWarpNPC[i] != NULL
							&& DEAD(pCastle->m_pWarpNPC[i]) == false)
					{
						count++;
					}
				}

				wait_time = 60 - count*10;
				break;
			}

			if (wait_time > 0)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				WaitTimeMsg(rmsg, wait_time);
				SEND_Q(rmsg, df->m_desc);
			}
		}
	}

#ifdef EXTREME_CUBE
	if(gserver->m_extremeCube.IsGuildCubeTime())
	{
		if(df->m_guildInfo && df->m_guildInfo->guild())
		{
			if(df->m_pZone != NULL && df->m_guildInfo->guild()->m_cubeUniqueIdx >= 0 && df->m_pZone->IsExtremeCube())
			{
				CCubeMemList* memlist = gserver->m_extremeCube.FindMemList(df->m_guildInfo->guild()->m_cubeUniqueIdx);
				if(memlist)
				{
					memlist->DelPC(df);

					if(opc && opc->m_guildInfo && opc->m_guildInfo->guild())
					{
						CCubeMemList* opcMemList = gserver->m_extremeCube.FindMemList(opc->m_guildInfo->guild());
						if(opcMemList)
						{
							time_t lastCubePoint;
							int point;
							time(&lastCubePoint);

							{
								CNetMsg::SP rmsg(new CNetMsg);
								HelperAddCubePointMsg(rmsg, opc->m_guildInfo->guild()->index(), df->m_level * 10, lastCubePoint);
								SEND_Q(rmsg, gserver->m_helper);
							}

							{
								// ���� ť������Ʈ ȹ��
								point = opcMemList->GetPersonalCubePoint(opc, df->m_level);
								CNetMsg::SP rmsg(new CNetMsg);
								HelperAddCubePointPersonalMsg(rmsg, opc->m_index, point, lastCubePoint);
								SEND_Q(rmsg, gserver->m_helper);
							}
						}
					}
				}
			}
		}
	}
	else
	{
		if(df->m_party)
		{
			if(df->m_pZone != NULL && df->m_party->m_cubeUniqueIdx >= 0 && df->m_pZone->IsExtremeCube())
			{
				CCubeMemList* memlist = gserver->m_extremeCube.FindMemList(df->m_party->m_cubeUniqueIdx);
				if(memlist)
				{
					memlist->DelPC(df);
					// ���� ť������Ʈ ȹ��
					if(opc && opc->m_party)
					{
						CCubeMemList* opcMemList = gserver->m_extremeCube.FindMemList(opc->m_party);
						if(opcMemList)
						{
							int point;
							time_t lastCubePoint;

							time(&lastCubePoint);
							point = opcMemList->GetPersonalCubePoint(opc, df->m_level);
							CNetMsg::SP rmsg(new CNetMsg);
							HelperAddCubePointPersonalMsg(rmsg, opc->m_index, point, lastCubePoint);
							SEND_Q(rmsg, gserver->m_helper);
						}
					}
				}
			}
		}
	}
#endif // EXTREME_CUBE

	if(df && df->m_pZone->IsWarGroundZone())
	{
		if(!opc && onpc)
		{
			if(onpc->Check_MobFlag(STATE_MONSTER_TRAP) || onpc->Check_MobFlag(STATE_MONSTER_PARASITE))
			{
				opc = onpc->GetOwner();
			}
		}
		if(opc)
			GAMELOG << init("ROYAL RUMBLE DEAD PC", df) << "ATTACKER" << delim << opc->m_nick << delim << opc->m_index << end;
		CWaitPlayer* p = NULL;
		p = gserver->m_RoyalRumble.m_WaitPlayerList.GetNode(df->m_index);
		if(p)
		{
			int leveltype = p->GetLevelType();
			int leftcount = 0;

			CWaitPlayer* player = NULL;
			CWaitPlayer* playern = NULL;
			playern = gserver->m_RoyalRumble.m_WaitPlayerList.GetHead();
			while((player = playern))
			{
				playern = playern->GetNext();
				if( player->GetLevelType() == leveltype &&
						player->GetCheckIn() == true )
					leftcount++;
			}
			leftcount -= 2;

			{
				CNetMsg::SP rmsg(new CNetMsg);
				RoyalRumbleLeftCount(rmsg, leftcount);
				CNetMsg::SP killmsg(new CNetMsg);
				if(opc)
					RoyalRumbleKillPlayer(killmsg, opc, df);
				switch(leveltype)
				{
				case LEVEL_TYPE_ROOKIE:
					{
						gserver->m_RoyalRumble.m_pRookieArea->SendToAllClient(rmsg);
						gserver->m_RoyalRumble.m_pRookieArea->SendToAllClient(killmsg);
					}
					break;
				case LEVEL_TYPE_SENIOR:
					{
						gserver->m_RoyalRumble.m_pSeniorArea->SendToAllClient(rmsg);
						gserver->m_RoyalRumble.m_pSeniorArea->SendToAllClient(killmsg);
					}
					break;
				case LEVEL_TYPE_MASTER:
					{
						gserver->m_RoyalRumble.m_pMasterArea->SendToAllClient(rmsg);
						gserver->m_RoyalRumble.m_pMasterArea->SendToAllClient(killmsg);
					}
					break;
				default:
					break;
				}
			}
		}
		gserver->m_RoyalRumble.m_WaitPlayerList.DelNode(df->m_index);
	}
	if(opc && opc->m_pZone->IsWarGroundZone())
	{
		// ��������Ʈ 1����Ʈ ����
		opc->AddWarGroundPoint(1);

		// ���� kill�� 1 ����
		opc->AddKillCount(1);
	}

#ifdef WINS_LOSES
	if (IS_PC(of))
		DropPvPTokenDeadPC(of, df);
#endif

	ProcDeadQuestProc(df, opc);

	// rvr �� ����
	if (df->m_pZone->isRVRZone())
	{
		ProcRVR(df, of);
	}

	if( ArtifactManager::instance()->isOwnerPC(df->m_index) == true )
	{
		if(IS_PC(of))
		{
			//pvp�� ���ߴµ� �����ڰ� ������ ���� �ִ� ���¶�� �����ڿ��� ������ �絵
			ArtifactManager::instance()->hunt(df, TO_PC(of));
		}
		else
		{
			//�̿ܿ� ������ ���ߴٸ� ������ ������ �ݳ�
			ArtifactManager::instance()->dead(df);
		}
	}

#ifdef HARDCORE_SERVER
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		switch (df->m_pZone->m_index )
		{
		case ZONE_START:
			{
				if (df->GetJoinFlag(df->m_pZone->m_index) == WCJF_NONE)	// �������� �ƴϰ�
				{
					if ( !(df->GetMapAttr() & MATT_FREEPKZONE) )
					{
						df->m_desc->Make_1_Level();
					}
				}
			}
			break;

		case ZONE_FREE_PK_DUNGEON:
		case ZONE_PK_TOURNAMENT:
		case ZONE_ROYAL_RUMBLE:
		case ZONE_RVR:
			break;

		default:
			{
				if (df->GetJoinFlag(df->m_pZone->m_index) == WCJF_NONE)	// �������� �ƴϸ�
				{
					df->m_desc->Make_1_Level();
				}
			}
			break;
		} // end if
	}
#endif
}
//

void ProcRVR(CPC* df, CCharacter* of)
{
	CPC* oPC;
	CNPC* oNPC;
	const int multiplier = gserver->m_serverConfig.rvr_points;
	if(IS_PC(of))
	{
		oPC = TO_PC(of);

		if (!df->isSyndicate() && !oPC->isSyndicate())
		{
			return;
		}

		if (df->isSyndicate() && !oPC->isSyndicate())
		{
			LONGLONG point = 1 * multiplier; //1
			if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
				point = point *2;
			df->m_syndicateManager.decreaseSyndicatePoint(point);
			return;
		}

		if (!df->isSyndicate() && oPC->isSyndicate())
		{
			LONGLONG point = 1 * multiplier; //1
			if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
				point = point *2;
			oPC->m_syndicateManager.increaseSyndicatePoint(point);
			return;
		}

		if (df->isSyndicate() && oPC->isSyndicate())
		{
			LONGLONG dfPoint = 0;
			LONGLONG attPoint = 0;
			int itemIndex = 0;

			//
			int jewelKailuxPoint		= SyndicateInfoDataManager::instance()->getJewelPoint(SYNDICATE::eSYNDICATE_KAILUX);
			int jewelDealerMoonPoint	= SyndicateInfoDataManager::instance()->getJewelPoint(SYNDICATE::eSYNDICATE_DEALERMOON);
           
			// ī�̷轺�� �������� ���󹮺��� ����
			if (jewelKailuxPoint < jewelDealerMoonPoint)
			{
				//�����ڰ� �������� ���� ���� �� ���
				if (oPC->getSyndicateType() == SYNDICATE::eSYNDICATE_KAILUX)
				{
					// �������� �������� ���� �������� �⿩���� ����
					if (df->m_syndicateManager.getSyndicatePoint(df->getSyndicateType()) < oPC->m_syndicateManager.getSyndicatePoint(oPC->getSyndicateType()))
					{
						attPoint = 2 * multiplier; //2
						dfPoint = 5 * multiplier;

						if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
						{
							attPoint = attPoint * 2;
							dfPoint = dfPoint * 2;
						}
			
						itemIndex = 10129;
					}
					else if(df->m_syndicateManager.getSyndicatePoint(df->getSyndicateType()) == oPC->m_syndicateManager.getSyndicatePoint(oPC->getSyndicateType()))
					{
						// �������� �������� ���� �⿩���� ����
						attPoint = 3 * multiplier;
						dfPoint = 3 * multiplier;

						if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
						{
							attPoint = attPoint * 2;
							dfPoint = dfPoint * 2;
						}
						itemIndex = 10130;
					}
					else
					{
						
						attPoint = 5 * multiplier;
						dfPoint = 2 * multiplier;

						if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
						{
							attPoint = attPoint * 2;
							dfPoint = dfPoint * 2;
						}
						itemIndex = 10130;
					}
				}
				//�����ڰ� �������� ū ���� �� ���
				else if (oPC->getSyndicateType() == SYNDICATE::eSYNDICATE_DEALERMOON)
				{
					if (df->m_syndicateManager.getSyndicatePoint(df->getSyndicateType()) < oPC->m_syndicateManager.getSyndicatePoint(oPC->getSyndicateType()))
					{
						// �������� �������� ���� �⿩���� ����
						attPoint = 1 * multiplier;
						dfPoint = 1 * multiplier;

						if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
						{
							attPoint = attPoint * 2;
							dfPoint = dfPoint * 2;
						}
						itemIndex = 10129;
					}
					else if(df->m_syndicateManager.getSyndicatePoint(df->getSyndicateType()) == oPC->m_syndicateManager.getSyndicatePoint(oPC->getSyndicateType()))
					{
						// �������� �������� ���� �⿩���� ����
						attPoint = 1 * multiplier;
						dfPoint = 1 * multiplier;

						if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
						{
							attPoint = attPoint * 2;
							dfPoint = dfPoint * 2;
						}
						itemIndex = 10130;
					}
					else
					{
						// �������� �������� ���� �⿩���� �۴�
						attPoint = 2 * multiplier;
						dfPoint = 1 * multiplier;

						if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
						{
							attPoint = attPoint * 2;
							dfPoint = dfPoint * 2;
						}

						itemIndex = 10130;
					}
				}
			}
			else
			{
				if (oPC->getSyndicateType() == SYNDICATE::eSYNDICATE_KAILUX)
				{
					// �������� �������� ���� �������� �⿩���� ����
					// ������� �������� ���� �⿩���� �۴�
					if (df->m_syndicateManager.getSyndicatePoint(df->getSyndicateType()) < oPC->m_syndicateManager.getSyndicatePoint(oPC->getSyndicateType()))
					{
						attPoint = 1 * multiplier;
						dfPoint = 1 * multiplier;

						if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
						{
							attPoint = attPoint * 2;
							dfPoint = dfPoint * 2;
						}

						itemIndex = 10129;
					}
					else if(df->m_syndicateManager.getSyndicatePoint(df->getSyndicateType()) == oPC->m_syndicateManager.getSyndicatePoint(oPC->getSyndicateType()))
					{
						// �������� �������� ������ �⿩���� ����
						attPoint = 1 * multiplier;
						dfPoint = 1 * multiplier;

						if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
						{
							attPoint = attPoint * 2;
							dfPoint = dfPoint * 2;
						}

						itemIndex = 10130;
					}
					else
					{
						// �������� �������� ���� �⿩���� ����
						attPoint = 2 * multiplier;
						dfPoint = 1 * multiplier;

						if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
						{
							attPoint = attPoint * 2;
							dfPoint = dfPoint * 2;
						}

						itemIndex = 10130;
					}
				}
				else if (oPC->getSyndicateType() == SYNDICATE::eSYNDICATE_DEALERMOON)
				{
					if (df->m_syndicateManager.getSyndicatePoint(df->getSyndicateType()) < oPC->m_syndicateManager.getSyndicatePoint(oPC->getSyndicateType()))
					{
						// �������� �������� ���� �⿩���� ����
						attPoint = 2 * multiplier;
						dfPoint = 5 * multiplier;

						if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
						{
							attPoint = attPoint * 2;
							dfPoint = dfPoint * 2;
						}

						itemIndex = 10129;
					}
					else if(df->m_syndicateManager.getSyndicatePoint(df->getSyndicateType()) == oPC->m_syndicateManager.getSyndicatePoint(oPC->getSyndicateType()))
					{
						// �������� �������� ���� �⿩���� ����
						attPoint = 3 * multiplier;
						dfPoint = 3 * multiplier;

						if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
						{
							attPoint = attPoint * 2;
							dfPoint = dfPoint * 2;
						}

						itemIndex = 10130;
					}
					else
					{
						// �������� �������� ���� �⿩���� �۴�
						attPoint = 5 * multiplier;
						dfPoint = 2 * multiplier; 

						if (gserver->isActiveEvent(A_EVENT_DOUBLE_RVR))
						{
							attPoint = attPoint * 2;
							dfPoint = dfPoint * 2;
						}
						
						itemIndex = 10130;
					}
				}
			}
			//�⿩�� ����
			df->m_syndicateManager.decreaseSyndicatePoint(dfPoint);
			oPC->m_syndicateManager.increaseSyndicatePoint(attPoint);

			//â���� ���� ���
			if(df->m_syndicateManager.isKing())
			{
				itemIndex = 10131;
			}

			CItem* pItem = gserver->m_itemProtoList.CreateItem(itemIndex, -1, 0, 0, 1);
			pItem = df->m_pArea->DropItem(pItem, (CCharacter*)df);

			if(pItem && pItem->m_pArea)
			{
				pItem->m_preferenceIndex = oPC->m_index;
				CNetMsg::SP rmsg(new CNetMsg);
				ItemDropMsg(rmsg, df, pItem);
				pItem->m_pArea->SendToCell(rmsg, GET_YLAYER(pItem), pItem->m_cellX, pItem->m_cellZ);
				GAMELOG << init("Syndicate Jewel Drop.", df) << "ITEM" << delim << itemlog(pItem) << end;
			}

			switch(itemIndex)
			{
			case 10129:
				df->m_syndicateManager.syndicateDelJewel(1);
				break;
			case 10130:
				df->m_syndicateManager.syndicateDelJewel(5);
				break;
			case 10131:
				df->m_syndicateManager.syndicateDelJewel(30);
				break;
			}
		}

		// �α� �߰�
		oPC->m_syndicateManager.historyManager_.battleWinHistory(oPC->getSyndicateType(), df->getSyndicateType(), df->GetName());
		df->m_syndicateManager.historyManager_.battleLoseHistory(df->getSyndicateType(), oPC->getSyndicateType(), oPC->GetName());

		// �����丮 ����
		oPC->m_syndicateManager.historyManager_.sendHistory(oPC->getSyndicateType());
		df->m_syndicateManager.historyManager_.sendHistory(df->getSyndicateType());
	}
	else if(IS_NPC(of))
	{
		oNPC = TO_NPC(of);

		int jewelKailuxPoint		= SyndicateInfoDataManager::instance()->getJewelPoint(SYNDICATE::eSYNDICATE_KAILUX);
		int jewelDealerMoonPoint	= SyndicateInfoDataManager::instance()->getJewelPoint(SYNDICATE::eSYNDICATE_DEALERMOON);

		if(jewelKailuxPoint > jewelDealerMoonPoint)
		{
			if(df->getSyndicateType() == SYNDICATE::eSYNDICATE_KAILUX)
			{
				df->m_syndicateManager.decreaseSyndicatePoint(2);
			}
			else
			{
				df->m_syndicateManager.decreaseSyndicatePoint(1);
			}
		}
		else
		{
			if(df->getSyndicateType() == SYNDICATE::eSYNDICATE_KAILUX)
			{
				df->m_syndicateManager.decreaseSyndicatePoint(1);
			}
			else
			{
				df->m_syndicateManager.decreaseSyndicatePoint(2);
			}
		}
	}
}

void ProcDeadQuestProc(CPC* dpc, CPC* opc)
{
	if(opc == NULL)
		return;

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
						pQuest->QuestUpdateData(opc, dpc);
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
									pQuest->QuestUpdateData(pMember, dpc);
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
