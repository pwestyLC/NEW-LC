#include "stdhdrs.h"

#include "Server.h"
#include "CmdMsg.h"
#include "Log.h"
#include "hardcoding.h"
#include "Battle.h"

// npc - ��� npc, pc - ������ ĳ����, tpc - �켱�� ĳ����, level - npc�� ������ ĳ������ ��շ���
typedef void (*NPC_DROP_FUNCTION) (CNPC* npc, CPC* pc, CPC* tpc, int level);
void ProcDropItemAfterBattle(CNPC* df, CPC* opc, CPC* tpc, int level)
{
	

	if(df->m_pZone->IsComboZone())
	{
		DropComboGiftMob(df, opc, tpc, level);
		return ;
	}

#ifdef SYSTEM_TREASURE_MAP
	if( df->m_idNum == TREASURE_BOX_NPC_INDEX ) // npc �ϰ�� ���� ���ڸ� ��� �Ѵ�.
	{
		DropTreasureBoxNpc(df, opc, tpc, level);
		return;
	}

	// ���� ������ �ʵ忡���� ����ȴ�.
	if( df->m_pZone->CheckTreasureDropFlag() && df->m_pZone->IsFieldZone() )
	{
		DropTreasureMap(df, opc, tpc, level);
	}
#endif

	// ������ ����� ������ �˻�
	bool hcSepDrop = false;
	bool hcDropPlus_S360 = false;
	bool hcPlatinumDrop = false;
	bool hcSepDropPrem = false;
	if (opc && tpc == opc)
	{
		if (opc->m_assist.m_avAddition.hcSepDrop)
		{
			opc->m_assist.CureByItemIndex(884);	// ������
			hcSepDrop = true;
			CNetMsg::SP rmsg(new CNetMsg);
			EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_DROP);
			SEND_Q(rmsg, opc->m_desc);
		}

		if (opc->m_assist.m_avAddition.hcSepDrop_Cash)
		{
			opc->m_assist.CureByItemIndex(6096);	// ������
			hcSepDrop = true;
			CNetMsg::SP rmsg(new CNetMsg);
			EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_DROP);
			SEND_Q(rmsg, opc->m_desc);
		}

		if (opc->m_assist.m_avAddition.hcSepDropPrem)
		{
			opc->m_assist.CureByItemIndex(12429);	// ������
			hcSepDropPrem = true;
			CNetMsg::SP rmsg(new CNetMsg);
			EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_DROP);
			SEND_Q(rmsg, opc->m_desc);
		}

		// ��õ�������� ����� ���
		else if (opc->m_assist.m_avAddition.hcDropPlus_S360)
		{
			opc->m_assist.CureBySkillIndex(360);
			hcDropPlus_S360 = true;
		}
		else if(opc->m_assist.m_avAddition.hcPlatinumDrop)
		{
			opc->m_assist.CureByItemIndex(2855);	// ������
			hcPlatinumDrop = true;
		}
	} // ������ ����� ������ �˻�

	// ������ ���
	int loopcount;
	bool IsNotDropInCube = true;
#ifdef EXTREME_CUBE
	if(df->m_bCubeRegen)
		IsNotDropInCube = false;
#endif // EXTREME_CUBE]

	int itemDropLoop = MAX_NPC_DROPITEM_LOOP;
#ifdef EVENT_WORLDCUP_2010
	if( df->m_proto->m_index == 1105 )
		itemDropLoop = 1;
#endif // #ifdef EVENT_WORLDCUP_2010

	for (loopcount = 0; loopcount < itemDropLoop; loopcount++)
	{
		// 5�������� ũ�� ������ ��� ����
		// 1. ����� �� �ִ� �� �������� ������ ����
		// 2. �� �������� ���Ȯ���� ��ӿ��� ����
		// 3. ���
#ifdef EVENT_WORLDCUP_2010 // Ʈ���̾ޱ� ��(1105) �ϰ�� ������ �������� ��� �Ѵ�
		if( ( df->m_proto->m_itemCount > 0 &&  ((level != -1 && level - df->m_level <= 5) ||  !IsNotDropInCube) )
			|| df->m_proto->m_index == 1105)
#else
		if (df->m_proto->m_itemCount > 0 &&  ((level != -1 && level - df->m_level <= 5) ||  !IsNotDropInCube) )
#endif
		{
			CItem* dropItem = NULL;
			int tableindex;
#ifdef EVENT_WORLDCUP_2010
			if( df->m_proto->m_index == 1105 )
			{
				// npc�� ��� ���̺�1,2���� ���� �౹��, Ȳ�� �౸����  100%gȮ���� �� �־�� �Ѵ�.
				tableindex = GetRandom(1, 10000); // 0. 95%Ȯ���� �౸��. 1. 5% Ȯ�� Ȳ�� �౸�� 2. ��
				if( tableindex <= 9000 )
					tableindex = 0;
				else if( tableindex <= 9500)
					tableindex = 1;
				else
					tableindex = 2;
			}
			else
#endif
				tableindex = GetRandom(0, MAX_NPC_DROPITEM - 1);
			int dropprob = df->m_proto->m_itemPercent[tableindex];

			dropprob = dropprob * gserver->m_itemDropProb / 100;

			if (tpc)
			{
				// �ڵ�
				if (tpc->m_assist.m_avAddition.hcDropPlus_838)
					dropprob *= 2;

				// ����ǽ�ũ��, 5080������ ��ũ�Ѱ� ������ ���� ����Ѵ�.
				if (tpc->m_assist.m_avAddition.hcScrollDrop)
					dropprob *= 2;

				if (tpc->m_assist.m_avAddition.hcScrollDrop_11340)
					dropprob *= 3;	

				if (tpc->m_assist.m_avAddition.hcScrollDropCube && tpc->m_pZone->m_index == ZONE_EXTREME_CUBE)
					dropprob += (dropprob * 30) / 100;

				if (tpc->m_assist.m_avAddition.hcScrollDrop_5081)
					dropprob *= 4;

				// ��� �ֹ���
				if (tpc->m_assist.m_avAddition.hcDropPlus_2141)
				{
					if (GetRandom(1, 10000) <= 2000 ) // 20 %
					{
						dropprob *= 2;
					}
				}
				if (tpc->m_assist.m_avAddition.hcDropPlus_11339)
				{
					if (GetRandom(1, 10000) <= 2000)
					{
						dropprob *= 3;
					}
				}

				// �÷�Ƽ�� ����� ��ũ��
				if(tpc->m_assist.m_avAddition.hcPlatinumScroll)
				{
					dropprob *= 4;
				}
			}

			// BS ���� : ������ ��� �̺�Ʈ
			dropprob = dropprob * gserver->m_nItemDropEventRate / 100;

			// ����� ��� %���� ����
			if (opc && tpc == opc && opc->m_assist.m_avAddition.hcDropPlusPer100 > 0)
				dropprob += dropprob * opc->m_assist.m_avAddition.hcDropPlusPer100 / 100;

#ifdef DOUBLE_ITEM_DROP
			if ( gserver->m_bDoubleItemEvent )
				dropprob += dropprob * gserver->m_bDoubleItemPercent / 100;
#endif // DOUBLE_ITEM_DROP

			// 9�� �̺�Ʈ ����� 10��
			if (hcSepDrop)
				dropprob = dropprob * 10;

			else if (hcSepDropPrem)
				dropprob = dropprob * 12;

			// ��õ�������� ����� ���
			else if (hcDropPlus_S360)
				dropprob = dropprob * 10;

			else if (hcPlatinumDrop)
				dropprob = dropprob * 20;

			if( opc && opc->m_assist.m_avAddition.hcRandomDropUp > 0  && GetRandom(0,100) <= opc->m_assist.m_avAddition.hcRandomDropUp )
			{
				dropprob = dropprob * 10;
				CNetMsg::SP rmsg(new CNetMsg);
				EffectEtcMsg(rmsg, opc, MSG_EFFECT_ETC_RANDOM_DROP);
				opc->m_pArea->SendToCell(rmsg, opc, true);
			}

			if( tpc )
			{
				if( gserver->isActiveEvent( A_EVENT_XMAS) )
				{
					if ( tpc->m_assist.m_avAddition.hcDropPlus_Xmas2007 > 0)
						dropprob += df->m_proto->m_itemPercent[tableindex] * tpc->m_assist.m_avAddition.hcDropPlus_Xmas2007;
				}
			}

#ifdef IMP_SPEED_SERVER
			// Zone Drop �� ����
			if( gserver->m_bSpeedServer && tpc && tpc->m_pZone )
			{
				dropprob = dropprob * tpc->m_pZone->GetZoneDrop() / 100;
			}
#endif //IMP_SPEED_SERVER

			if (df->m_proto->m_item[tableindex] != -1 && GetRandom(1, 10000) <= dropprob)
			{
				if (df->m_proto->m_item[tableindex] == 84)
				{
					dropItem = df->m_pArea->DropItem(df->m_proto->m_item[tableindex], df, 0, df->m_level, 1);
				}
				// �븸�� �����̽þƴ� �߼��� ü�¾��� �������� ��������
				else if( df->m_proto->m_item[tableindex] == 44
						 || df->m_proto->m_item[tableindex] == 45 )
				{
					dropItem = df->m_pArea->DropItem(43, df, 0, 0, 1);
				}
				// �븸�� �����̽þƴ� ���� ���� ȸ�� ������ ��ӵ��� �ʴ´�.
				else if ( df->m_proto->m_item[tableindex] == 485 )
				{
					dropItem = NULL;
				}
				// ���� �������� ���ۼ�, ���� ����, ���� ���� �޴��� ��� ����
				else if ( df->m_proto->m_item[tableindex] == 1066
						  || df->m_proto->m_item[tableindex] == 1067
						  || df->m_proto->m_item[tableindex] == 1068
						  || df->m_proto->m_item[tableindex] == 489)
				{
					dropItem = NULL;
				}
				else
				{
					// 61���� ����� �� 65���� �� ��� ���� ���ۼ� ��� ����
					switch (df->m_proto->m_item[tableindex])
					{
					case -1:	// ������ ����
						dropItem = NULL;
						break;

					default:
						{
							bool bAvailableDrop = true;
							if (bAvailableDrop)
								dropItem = df->m_pArea->DropItem(df->m_proto->m_item[tableindex], df, 0, 0, 1, true);
							else
								dropItem = NULL;
						}
						break;
					} // switch (df->m_proto->m_item[tableindex])
				}
			} // if (df->m_proto->m_item[tableindex] != -1 && GetRandom(1, 10000) <= dropprob)

			if (dropItem)
			{
// 050303 : bs : ���Ϳ��Լ� plus ���� ������ �����
				if (df->m_proto->m_minplus >= 0 && df->m_proto->m_maxplus >= df->m_proto->m_minplus && df->m_proto->m_probplus > 0 && dropItem->CanUpgrade())
				{
					if (GetRandom(1, 10000) <= df->m_proto->m_probplus)
					{
						dropItem->setPlus(GetRandom(df->m_proto->m_minplus, df->m_proto->m_maxplus));
					}
				}

				// Drop Msg ������
				// ������ �켱�� ���� (���� ������ ����, ���� ����)
				if (tpc)
					dropItem->m_preferenceIndex = tpc->m_index;
				else
					dropItem->m_preferenceIndex = -1;

				if (!AutoAddItem(opc, dropItem, df)) {
					CNetMsg::SP rmsg(new CNetMsg);
					ItemDropMsg(rmsg, df, dropItem);
					df->m_pArea->SendToCell(rmsg, GET_YLAYER(dropItem), dropItem->m_cellX, dropItem->m_cellZ);
				}
				
				if (df->m_proto->CheckFlag(NPC_BOSS | NPC_MBOSS))
				{
					GAMELOG << init("MOB DROP ITEM")
							<< "NPC INDEX" << delim
							<< df->m_proto->m_index << delim
							<< "NPC NAME" << delim
							<< df->m_name << delim
							<< "ITEM" << delim
							<< itemlog(dropItem)
							<< end;
				}
			}
		}
	} // // ������ ���

	// opc ���� ĳ����, tpc �켱�� ĳ����
	int job = -1;

	if(tpc)
		job = (int)tpc->m_job;
	else if(opc)
		job = (int)opc->m_job;

	if(job >= 0 && job < JOBCOUNT)
	{
		if(level != -1 && level - df->m_level <= 5)
		{
			if(df->m_proto->m_jobdropitem[job] > 0 && df->m_proto->m_jobdropitemprob[job] > 0)
			{
				int dropprob = df->m_proto->m_jobdropitemprob[job];
				if(GetRandom(1, 10000) <= dropprob)
				{
					CItem* dropItem = NULL;
					dropItem = gserver->m_itemProtoList.CreateItem(df->m_proto->m_jobdropitem[job], -1, 0, 0, 1);
					if(dropItem)
					{
						df->m_pArea->DropItem(dropItem, df);
						if (!AutoAddItem(opc, dropItem, df)) {
							CNetMsg::SP rmsg(new CNetMsg);
							ItemDropMsg(rmsg, df, dropItem);
							df->m_pArea->SendToCell(rmsg, df, true);
						}
						GAMELOG << init("MOB DROP ITEM")
								<< "NPC INDEX" << delim
								<< df->m_proto->m_index << delim
								<< "NPC NAME" << delim
								<< df->m_name << delim
								<< "ITEM" << delim
								<< itemlog(dropItem)
								<< end;
					}
				}
			}
		}
	}

	// �� �������� �������� ���� ������ ����Ʈ����.
	int loopi = 0;
	for(loopi = 0; loopi < MAX_NPC_DROPITEM; loopi++)
	{
		if(df->m_proto->m_dropallitem[loopi] < 1)
			continue ;

		int dropprob = df->m_proto->m_dropallitemprob[loopi];
		if(GetRandom(1, 10000) <= dropprob)
		{
			CItem* pItem = NULL;

			pItem = gserver->m_itemProtoList.CreateItem(df->m_proto->m_dropallitem[loopi], -1, 0, 0, 1);
			if(pItem)
			{
				if (tpc)
					pItem->m_preferenceIndex = tpc->m_index;
				else
					pItem->m_preferenceIndex = -1;

				
				df->m_pArea->DropItem(pItem, df);
				if (!AutoAddItem(opc, pItem, df)) {
					CNetMsg::SP rmsg(new CNetMsg);
					ItemDropMsg(rmsg, df, pItem);
					df->m_pArea->SendToCell(rmsg, df, true);
				}
				GAMELOG << init("MOB DROP ALL ITEM")
						<< "NPC INDEX" << delim
						<< df->m_proto->m_index << delim
						<< "NPC NAME" << delim
						<< df->m_name << delim
						<< "ITEM" << delim
						<< itemlog(pItem)
						<< end;
			}
		}
	}
	
	// ���� ���
	for (loopcount = 0; loopcount < MAX_NPC_DROPITEM_LOOP; loopcount++)
	{
		// 5�������� ũ�� ������ ��� ����
		// 1. ����� �� �ִ� �� �������� ������ ����
		// 2. �� �������� ���Ȯ���� ��ӿ��� ����
		// 3. ���
		if (df->m_proto->m_jewelCount > 0 &&  ((level != -1 && level - df->m_level <= 5) ||  !IsNotDropInCube)  )
		{
			CItem* dropItem = NULL;
			int tableindex = GetRandom(0, MAX_NPC_DROPJEWEL - 1);
			int dropprob = df->m_proto->m_jewelPercent[tableindex];

			if (df->m_proto->m_jewel[tableindex] != -1 && GetRandom(1, 10000) <= dropprob)
			{
				switch (df->m_proto->m_jewel[tableindex])
				{
				case -1:	// ������ ����
					dropItem = NULL;
					break;

				default:
					{
						dropItem = df->m_pArea->DropItem(df->m_proto->m_jewel[tableindex], df, 0, 0, 1, true);
					}
					break;
				}
			}

			if (dropItem)
			{
				// Drop Msg ������
				// ������ �켱�� ���� (���� ������ ����, ���� ����)
				if (tpc)
					dropItem->m_preferenceIndex = tpc->m_index;
				else
					dropItem->m_preferenceIndex = -1;

				if (!AutoAddItem(opc, dropItem, df)) {
					CNetMsg::SP rmsg(new CNetMsg);
					ItemDropMsg(rmsg, df, dropItem);
					df->m_pArea->SendToCell(rmsg, GET_YLAYER(dropItem), dropItem->m_cellX, dropItem->m_cellZ);
				}

				GAMELOG << init("JEWEL ITEM")
						<< "NPC INDEX" << delim
						<< df->m_proto->m_index << delim
						<< "NPC NAME" << delim
						<< df->m_name << delim
						<< "ITEM" << delim
						<< itemlog(dropItem)
						<< end;
			}
		}
	} // ���� ���
	// typedef void (*NPC_DROP_FUNCTION) (CNPC* npc, CPC* pc, CPC* tpc, int level);
	// pc, tpc�� NULL�� �� �� �ִ�
	NPC_DROP_FUNCTION fnNPCDrop[] =
	{
		DropBloodGem,						// �������� ��� : �븸 õ�ϴ��
		DropLuckySpecialStone,				// ����� ���ü� ��� : �븸 õ�ϴ��
		DropSpecialRefineStone,				// ���� ���
		DropPersonalDungeon2Ticket,			// �۽��δ��� 2 ����� ���
		DropBoosterItem,					// �ν���

		DropPersonalDungeon3Ticket,			// �۽��δ��� 3 ����� ���
		DropPersonalDungeon4Ticket,			// �۽��δ��� 4 ����� ���

		DropPetEgg,							// �ֿϵ��� �� ���
		DropHeaveStone,  //pwesty

		DropNewMoonStoneItem,

#ifdef EVENT_VALENTINE
		DropValentineItem,					// �߷�Ÿ��
#endif

#ifdef EVENT_WHITEDAY
		DropWhiteDayItem,					// ȭ��Ʈ����
#endif

#ifdef DROP_MAKE_DOCUMENT
		DropMakeDocument,					// ���۹��� ���
#endif // DROP_MAKE_DOCUMENT

		DropRecommendItem,					// ��õ ���� ���� �ν��Ͻ� ���� ������

		DropGoldenBallItem,					// ��纼 �̺�Ʈ

		RegenBlessWarrior,					// ������ �ູ

		DropHalloween2006Item,				// 2006 �ҷ��� �̺�Ʈ

		DropRaidMonsterItem,

		DropMobScrollSpecialStone,

		DropEventGomdori2007,

		DropEventIndependenceDay2007USA,

		DropEventAprilFoolEvent,

#ifdef EVENT_DROPITEM
		DropEventNpcDropItem,
#endif // EVENT_DROPITEM

		DropAPetLifeBook,

		DropPhoenix_MembersTicket,
		//DropPremPhoenix_MembersTicket,

		DropTriggerItem,

#ifdef LACARETTE_SYSTEM
		DropLacaRette,
#endif
		DropChristmas,
		DropValentineEvent,
		DropEasterEvent,
		DropHolyWater,
		DropZonePotion,
		DropRuneBox,
		DropCashItems,
		DropEssenceAndFrag,
		DropCraftingItems,
		DropArmorAndWeaponCraft,
		DropWorldCupEvent,
		DropHalloween2014Event,
		DropArtifactItem,

		DropEventCustomItem

#ifdef DEV_EVENT_AUTO
		DropEventItem,
#endif // DEV_EVENT_AUTO
	}; // ��� �Լ� ���̺�

	// ����ڵ� : tpc�� �ִµ� m_pZone�̳� m_pArea�� ������ NULL�� �ٲ۴�
	if (tpc && (tpc->m_pZone == NULL || tpc->m_pArea == NULL))
		tpc = NULL;

	unsigned int fnDropLoop;
	for (fnDropLoop = 0; fnDropLoop < sizeof(fnNPCDrop) / sizeof(NPC_DROP_FUNCTION); fnDropLoop++)
		(fnNPCDrop[fnDropLoop])(df, opc, tpc, level);

	gserver->doEventDropItem(df, opc, tpc);

	// �� ����߸� Ȯ�� : default 80 %
	// BS ���� : ���� ���� ���� ������ �г�Ƽ�� ����
	// ����� : �� ���Ȯ��
	int moneyDropProb = MONEY_DROP_PROB * gserver->m_moneyDropProb / 100;
	if (level != -1 && df->m_level - level < 0)
		moneyDropProb += (df->m_level - level) * 500;

	bool hcSepNas = false;
	if (opc && tpc == opc)
	{
		if (opc->m_assist.m_avAddition.hcSepNas)
		{
			opc->m_assist.CureByItemIndex(885);	// ����
			hcSepNas = true;
			CNetMsg::SP rmsg(new CNetMsg);
			EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_NAS);
			SEND_Q(rmsg, opc->m_desc);
		}
	}

	// �� ���
	//CItem* money = NULL;
	if (GetRandom(1, 10000) <= moneyDropProb)	// 80%
	{
		// �� �׼� : +- 50%
		if(!df)
		{
			//�߸��� ��ġ���� ���͸� ����� ���
			GAMELOG << "NOT FOUND TARGET....."
					<< df->m_idNum
					<< end;
			return ;
		}
		GoldType_t count = df->m_proto->m_price * GetRandom(50, 150) / 100;

#ifdef LC_RUS
		// ���þƴ� ������ ������ ������ �������� 65 ���� �̻��� ���Ͱ� ������ ������ 40% �� ���δ�.
		if (df->m_pZone && df->m_pZone->m_index != ZONE_DUNGEON4 && df->m_level >= 65)
			count = count / 5 * 2;
#endif // LC_RUS

		// �����̺�Ʈ
		if (gserver->m_bDoubleEvent)
		{
#ifdef NEW_DOUBLE_GM_ZONE
			if( gserver->m_bDoubleEventZone == -1 || gserver->m_bDoubleEventZone == df->m_pZone->m_index )
#endif // NEW_DOUBLE_GM_ZONE
				count = count * gserver->m_bDoubleNasPercent / 100 ;
		}

		// 9�� �̺�Ʈ ���� 10��
		if (hcSepNas)
			count = count * 10;

		// ��� �ֹ���
		if (tpc && tpc->m_assist.m_avAddition.hcDropPlus_2141)
		{
			if (GetRandom(1, 10000) <= 8000 ) // 80 %
			{
				count *= 2;
			}
		}
		if (tpc && tpc->m_assist.m_avAddition.hcDropPlus_11339)
		{
			if (GetRandom(1, 10000) <= 8000 ) // 80 %
			{
				count *= 2;
			}
		}

//#endif // CAHNCE_EVENT

		if( opc && opc->m_pZone->m_index == ZONE_DRATAN_CASTLE_DUNGEON )
		{
			CDratanCastle * pCastle = CDratanCastle::CreateInstance();
			if( opc->m_guildInfo && opc->m_guildInfo->guild()->index() == pCastle->GetOwnerGuildIndex()  )
			{
				// ���� ����
			}
			else
			{
				GoldType_t tax=0;
				tax = count * pCastle->m_dvd.GetHuntRate() / 100;
				count = count - tax;
				gserver->AddTaxItemDratan( tax );
			}
		}

		if( opc && opc->m_pZone->m_index == ZONE_MISTY_CANYON_EXTREME)
		{
			CDratanCastle * pCastle = CDratanCastle::CreateInstance();
			if( opc->m_guildInfo && opc->m_guildInfo->guild()->index() == pCastle->GetOwnerGuildIndex()  )
			{} else {
				GoldType_t tax = count - (count * .90);
				gserver->AddTaxProduceAkan( tax );
			}
		}

		if( opc && opc->m_pZone->m_index == ZONE_EXTREME_CUBE )
		{
			CWarCastle * pCastle = CWarCastle::GetCastleObject(ZONE_MERAC);
			if( opc->m_guildInfo && opc->m_guildInfo->guild()->index() == pCastle->GetOwnerGuildIndex()  )
			{} else {
				GoldType_t tax = count - (count * .90);
				gserver->AddTaxProduceTrivia( tax );
			}
		}

		if( tpc == NULL )
		{
			GAMELOG << "NOT FOUND TARGET....." << end;
			return;
		}

		//��Ƽ�̸鼭 Ÿ���� �յ��϶�
		if (tpc->IsParty() && (tpc->m_party->GetPartyType(MSG_DIVITYPE_MONEY) == MSG_PARTY_TYPE_RANDOM || tpc->m_party->GetPartyType(MSG_DIVITYPE_MONEY) == MSG_PARTY_TYPE_BATTLE) )
		{
			DivisionPartyMoney(tpc, df, count);
		}
		//�������̸鼭 Ÿ���� �յ��϶�
		else if ( tpc->IsExped() && (tpc->m_Exped->GetExpedType(MSG_DIVITYPE_MONEY) == MSG_EXPED_TYPE_RANDOM || tpc->m_Exped->GetExpedType(MSG_DIVITYPE_MONEY) == MSG_EXPED_TYPE_BATTLE) )
		{
			DivisionExpedMoney(tpc, df, count);
		}
		//�̵� ���� �ƴҶ� (���� �÷����Ҷ�)
		else
		{
			int bonus = 0;

			if(tpc->m_avPassiveAddition.money_nas > 0)
			{
				bonus += tpc->m_avPassiveAddition.money_nas;	
			}
			if(tpc->m_avPassiveRate.money_nas > 0)
			{
				bonus = count * (tpc->m_avPassiveRate.money_nas - 100) / SKILL_RATE_UNIT;
			}
			
			count = count + count * tpc->m_artiGold / 100;
			
			if (gserver->isActiveEvent(A_EVENT_DOUBLE_GOLD)) {
				count = count * 2;
			}

#ifdef DUNGEON_TIME_GOLD_INCREASE
			if (gserver->m_bDungeonTimeToggle && gserver->m_bIsTime &&
				gserver->m_iZoneExp[tpc->m_pZone->m_index] > 100)
			{
				count = count + count * 0.1;
			}
#endif
//dethunter12 modify 1/11/2022
			if (tpc->m_reborn > 0)
				count = count + (count * tpc->m_reborn * .07);
				
			if (tpc->m_bPremium_Phoenix == 1)
			{
					count = count + (count *.1);
			}
			
#ifdef CUSTOM_OPTIONS_11182021
			if (tpc->m_opNasRate > 0)
			{
				count += (count * tpc->m_opNasRate / 100) ;
			}
#endif
			
			
				
			if (df != NULL && df->m_proto->IsBossInList()) 
			{
				if (count > gserver->m_serverConfig.max_gold_boss)
					count = gserver->m_serverConfig.max_gold_boss;

			}
			else if (count > gserver->m_serverConfig.max_gold && !tpc->m_assist.FindBySkillIndex(2040))
			{
				count = gserver->m_serverConfig.max_gold;
			}
			else if (count > gserver->m_serverConfig.max_gold && tpc->m_assist.FindBySkillIndex(2040))
			{
				if (count > MAX_GOLD_POTION)
					count = MAX_GOLD_POTION;
				else
					count = count;
			}

			tpc->m_inventory.increaseMoney(count, bonus);
		}

		if (df->m_proto->CheckFlag(NPC_BOSS | NPC_MBOSS))
		{
			GAMELOG << init("MOB DROP MONEY")
					<< "NPC INDEX" << delim
					<< df->m_proto->m_index << delim
					<< "NPC NAME" << delim
					<< df->m_name << delim
					<< "MONEY(NAS)" << delim
					<< count
					<< end;
		}
	}
}
//