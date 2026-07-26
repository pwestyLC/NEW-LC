#include <boost/foreach.hpp>
#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "DratanCastle.h"
#include "doFunc.h"
#include "../ShareLib/packetType/ptype_old_do_move.h"
#include "../ShareLib/packetType/ptype_old_do_monstercombo.h"

//////////////////////////////////////////////////////////////////////////
void do_MonsterComboEditComplete(CPC* ch, CNetMsg::SP& msg);
void do_MonsterComboEditCancel(CPC* ch);
void do_MonsterComboContextReq(CPC* ch);
void do_MonsterComboGotoCombo(CPC* ch, CNetMsg::SP& msg);
void do_MonsterComboConfirm(CPC* ch, CNetMsg::SP& msg);
void do_MonsterComboRecallToCombo(CPC* ch);
void do_MonsterComboGiveUp(CPC* ch, CNetMsg::SP& msg);
void do_MonsterComboGotoStage(CPC* ch);
void do_MonsterComboGotoWaitRoom( CPC* ch );
//////////////////////////////////////////////////////////////////////////

void do_MonsterCombo(CPC* ch, CNetMsg::SP& msg)
{
	pTypeThirdBase* pBase = reinterpret_cast<pTypeThirdBase*>(msg->m_buf);

	switch(pBase->thirdType)
	{
	case MSG_EX_MONSTERCOMBO_EDIT_COMPLETE:					// �����Ϸ��ư ������ ���
		do_MonsterComboEditComplete(ch, msg);
		break;
	case MSG_EX_MONSTERCOMBO_EDIT_CANCEL:					// ������ҹ�ư�� ������ ���
		do_MonsterComboEditCancel(ch);
		break;
	case MSG_EX_MONSTERCOMBO_EDIT_CONTEXT_REQ:				// �޺� �̼����̽� ����Ʈ ��û�� ���(��Ƽ��)
		do_MonsterComboContextReq( ch );
		break;
	case MSG_EX_MONSTERCOMBO_GOTO_COMBO:					// �����Ϸ� �� �������� ��
		do_MonsterComboGotoCombo(ch, msg);
		break;
	case MSG_EX_MONSTERCOMBO_GOTO_COMBO_CONFIRM:			// Ȯ�θ޽��� Ŭ������ ��
		do_MonsterComboConfirm(ch, msg);
		break;
	case MSG_EX_MONSTERCOMBO_RECALL_TO_COMBO:				// npc�� �̿��ؼ� ��Ƽ���� Ŭ������ ��
		do_MonsterComboRecallToCombo(ch);
		break;
	case MSG_EX_MONSTERCOMBO_GIVEUP:						// ���� �޺� ����
		do_MonsterComboGiveUp(ch, msg);
		break;
	case MSG_EX_MONSTERCOMBO_GOTO_STAGE:					// ���濡�� ���� ���������� �� �̼� ����
		do_MonsterComboGotoStage(ch);
		break;
	case MSG_EX_MONSTERCOMBO_GOTO_WAITROOM:					// ������������ �������� ��
		do_MonsterComboGotoWaitRoom( ch );
		break;
	default:
		{
			LOG_ERROR("HACKING : invalid third type[%d]. charIndex[%d]", pBase->thirdType, ch->m_index);
			ch->m_desc->Close("invalid third type");
		}
		return ;
	}
}

void do_MonsterComboEditComplete(CPC* ch, CNetMsg::SP& msg)
{
	// ��Ƽ�� �� ���常 �� �� ����
	if(ch->IsParty())
	{
		if(ch->m_index != ch->m_party->GetBossIndex())
		{
			ch->m_listSaveComboData.clear();
			return ;
		}

		// �޺����̸�
		if(ch->m_party->m_comboAreaIndex != -1)
			return ;
	}

	RequestClient::MCEditComplete* packet = reinterpret_cast<RequestClient::MCEditComplete*>(msg->m_buf);

	CNPC* pNpc = (CNPC*)ch->m_pArea->FindCharInCell(ch, packet->npcIndex, MSG_CHAR_NPC, true);
	if (pNpc == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_NOT_EXIST_NPC);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	// �������� üũ
	if( packet->count < 1 || packet->count > 20 || (packet->count % 5 != 0 ))
		return ;

	// ������ �ִ� �� ����
	ch->m_listSaveComboData.clear();

	MONSTER_COMBO_DATA data;
	const CMissionCaseProto* proto = NULL;
	for(int i = 0; i < packet->count; ++i)
	{
		proto = gserver->m_missionCaseList.FindProto(packet->list[i]);
		if(!proto)
		{
			// ���� ����
			ch->m_listSaveComboData.clear();

			{
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_EDIT_COMPLETE_FAIL);
				SEND_Q(rmsg, ch->m_desc);
			}

			// ���зα�
			GAMELOG << init("COMBO EDIT FAILED", ch)
					<< "Party Index: ";

			if(ch->IsParty())
				GAMELOG << ch->m_party->GetBossIndex();
			else
				GAMELOG << -1;

			GAMELOG << " CASE NUM: "
					<< packet->list[i]
					<< end;

			return;
		}

		data.nStep	= i;
		data.nIndex = packet->list[i];

		ch->m_listSaveComboData.push_back(data);
	}

	{
		// ���� �Ϸ������� �˸���.
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_EDIT_COMPLETE_OK);
		SEND_Q(rmsg, ch->m_desc);
	}

	// �����α�
	GAMELOG << init("COMBO EDIT OK", ch)
			<< "Party Index: ";

	if(ch->IsParty())
		GAMELOG << ch->m_party->GetBossIndex();
	else
		GAMELOG << -1;

	GAMELOG << " MISSION COUNT: "
			<< (int)ch->m_listSaveComboData.size();

	GAMELOG << " MISSION: ";

	BOOST_FOREACH(MONSTER_COMBO_DATA& data, ch->m_listSaveComboData)
	{
		GAMELOG << data.nIndex << " ";
	}
	GAMELOG << end;
}

void do_MonsterComboEditCancel(CPC* ch)
{
	if(ch->m_pZone->IsComboZone())
		return ;

	ch->m_listSaveComboData.clear();

	GAMELOG << init("COMBO EDIT CANCEL", ch)
			<< "Party Index: "
			<< (ch->IsParty() ? ch->m_party->GetBossIndex() : -1)
			<< end;
}

void do_MonsterComboContextReq(CPC* ch)
{
	if(ch->IsParty())				// ��Ƽ�� ���
	{
		int bossindex, count;
		bossindex = ch->m_party->GetBossIndex();
		CPC* pc = PCManager::instance()->getPlayerByCharIndex(bossindex);
		if(!pc)
			return ;

		count =  pc->m_listSaveComboData.size();
		if(count > 0)			// ���� ����
		{
			std::vector<int> vec;
			BOOST_FOREACH(MONSTER_COMBO_DATA& data, pc->m_listSaveComboData)
			{
				vec.push_back(data.nIndex);
			}
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeMBEditContext(rmsg, vec);
			SEND_Q(rmsg, ch->m_desc);
		}
		else					// �޺����� ����
		{
			// ���� �˻���.
			int i = gserver->m_comboZone->FindComboArea(ch->m_party->m_comboAreaIndex);
			if(i == -1)
				return;

			CArea* area = gserver->m_comboZone->m_area + i;
			CMonsterCombo* combo = area->m_monsterCombo;

			std::vector<int> vec;
			for(i = 0; i < combo->m_nTotalMission; ++i)
			{
				const MISSION* mission = combo->FindMission(i + 1);
				if(!mission)
					return ;

				vec.push_back(mission->proto->m_nIndex);
			}

			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeMBEditContext(rmsg, vec);
			SEND_Q(rmsg, ch->m_desc);
		}
	}
	else			// ������ ���
	{
		int count;
		count = ch->m_listSaveComboData.size();
		if(count > 0)
		{
			std::vector<int> vec;
			BOOST_FOREACH(MONSTER_COMBO_DATA& data, ch->m_listSaveComboData)
			{
				vec.push_back(data.nIndex);
			}

			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeMBEditContext(rmsg, vec);
			SEND_Q(rmsg, ch->m_desc);
		}
		else if(ch->m_pZone->IsComboZone())
		{
			CMonsterCombo* combo = ch->m_pArea->m_monsterCombo;
			std::vector<int> vec;
			for(int i = 0; i < combo->m_nTotalMission; ++i)
			{
				const MISSION* mission = combo->FindMission(i + 1);
				if(!mission)
					return ;

				vec.push_back(mission->proto->m_nIndex);
			}

			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeMBEditContext(rmsg, vec);
			SEND_Q(rmsg, ch->m_desc);
		}
	}
}

void do_MonsterComboGotoCombo(CPC* ch, CNetMsg::SP& msg)
{
	if(ch->IsParty())
	{
		// �������� Ȯ��
		if(ch->m_party->GetBossIndex() != ch->m_index)
			return ;

		if(ch->m_party->m_comboAreaIndex != -1)
			return ;
	}

	RequestClient::MCGotoCombo* packet = reinterpret_cast<RequestClient::MCGotoCombo*>(msg->m_buf);

	CNPC* pNpc = (CNPC*)ch->m_pArea->FindCharInCell(ch, packet->npcIndex, MSG_CHAR_NPC, true);
	if (pNpc == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_NOT_EXIST_NPC);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	int count = ch->m_listSaveComboData.size();

	// ���� �ϷḦ �������� Ȯ��
	if(count < 1)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_EDIT_COMPLETE_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ���� �˻�
	LONGLONG totalnas = 0;
	BOOST_FOREACH(MONSTER_COMBO_DATA& data, ch->m_listSaveComboData)
	{
		const CMissionCaseProto* proto = gserver->m_missionCaseList.FindProto(data.nIndex);
		if (proto == NULL)
			return ;

		totalnas += proto->m_nNas;
	}

	if( ch->m_inventory.getMoney() < totalnas )
	{
		// ���� ������ �ִ� ���� ���� �����޼��� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_MONEY);
		SEND_Q( rmsg, ch->m_desc );
		return;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		RequestClient::makeGoZone(rmsg, packet->zoneIndex, packet->extra, pNpc->m_proto->m_index);
		do_GoZone(ch, rmsg);
	}

	if(ch->m_pZone->IsComboZone())
	{
		ch->m_inventory.decreaseMoney(totalnas);
	}
}

void do_MonsterComboConfirm(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::MCConfirm* packet = reinterpret_cast<RequestClient::MCConfirm*>(msg->m_buf);

	if(packet->yesno == 0)
		return;

	CParty* party = gserver->FindPartyByBossIndex(packet->bossIndex);
	if(!party)
		return ;

	// ���Ȯ��
	int ret = party->FindMember(ch->m_index);
	if(ret == -1)
		return ;

	if(party->m_comboAreaIndex == -1)
		return ;

	if(ch->m_pZone->m_index == ZONE_COMBO_DUNGEON)
		return ;

	ret = gserver->m_comboZone->FindComboArea(party->m_comboAreaIndex);
	if(ret == -1)
		return ;

	CArea* area = gserver->m_comboZone->m_area + ret;

#ifdef MONSTER_COMBO_FIX
	if(!area->m_monsterCombo->m_bPartyRecall)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_ALREADY_START);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
#endif // MONSTER_COMBO_FIX

	if(area->GetPCCount() >= MAX_PARTY_MEMBER)
		return ;

	LONGLONG nas = area->m_monsterCombo->GetTotalNas();

	if( ch->m_inventory.getMoney() < nas )
	{
		// ���� ������ �ִ� ���� ���� �����޼��� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_MONEY);
		SEND_Q( rmsg, ch->m_desc );
		return;
	}

	int extra = 0;
	GoZone(ch, gserver->m_comboZone->m_index,
		   gserver->m_comboZone->m_zonePos[extra][0],														// ylayer
		   GetRandom(gserver->m_comboZone->m_zonePos[extra][1], gserver->m_comboZone->m_zonePos[extra][3]) / 2.0f,		// x
		   GetRandom(gserver->m_comboZone->m_zonePos[extra][2], gserver->m_comboZone->m_zonePos[extra][4]) / 2.0f);		// z

	if(ch->m_pZone->IsComboZone())
	{
		ch->m_inventory.decreaseMoney(nas);
	}

	GAMELOG << init("RECALL TO COMBO AREA", ch)
			<< "AREA INDEX: " << area->m_index
			<< " COMBO INDEX: " << area->m_monsterCombo->m_nIndex
			<< " NAS: " << nas
			<< end;
}

void do_MonsterComboRecallToCombo(CPC* ch)
{
	// �޺���������
	if(ch->m_pZone->m_index != ZONE_COMBO_DUNGEON)
		return ;

	// ��Ƽ����
	if(!ch->IsParty())
		return ;

	if(!ch->m_pArea)
		return ;

#ifdef MONSTER_COMBO_FIX
	if(!ch->m_pArea->m_monsterCombo)
		return ;

	if(!ch->m_pArea->m_monsterCombo->m_bPartyRecall)
	{
		GAMELOG << init("MONSTER COMBO PARTY RECALL FAIL", ch)
				<< ch->m_pArea->m_monsterCombo->m_nIndex
				<< end;

		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_ALREADY_START);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
#endif // MONSTER_COMBO_FIX

#if defined (LC_GAMIGO)
	if(ch->m_pArea->GetPCCount() >= MAX_PARTY_MEMBER)
		return ;
#endif // LC_GAMIGO

	GAMELOG << init("MONSTER COMBO PARTY RECALL", ch)
			<< end;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperRecallToWaitRoomPrompt(rmsg, ch->m_party->GetBossIndex());
		SEND_Q(rmsg, gserver->m_helper);
	}
}

void do_MonsterComboGiveUp(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::MCGiveup* packet = reinterpret_cast<RequestClient::MCGiveup*>(msg->m_buf);

	CNPC* pNpc = (CNPC*)ch->m_pArea->FindCharInCell(ch, packet->npcIndex, MSG_CHAR_NPC, true);
	if (pNpc == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_NOT_EXIST_NPC);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		RequestClient::makeGoZone(rmsg, packet->zoneIndex, packet->extra, pNpc->m_proto->m_index);
		do_GoZone(ch, rmsg);
	}

	if (ch->m_pZone->IsComboZone() == false)
	{
		GAMELOG << init("GET OUT FROM COMBO", ch)
				<< end;
	}
}

void do_MonsterComboGotoStage(CPC* ch)
{
	if(!ch->m_pZone->IsComboZone())
		return ;
	
	if(!ch->m_pArea->m_bEnable || ch->m_pArea->m_monsterCombo->m_nIndex == -1)
	{
		GAMELOG << init("CLOSE COMBO AREA")
				<< "BY Next Stage Error"
				<< "AREA INDEX: "
				<< ch->m_pArea->m_index
				<< " PARTY INDEX: "
				<< ch->m_pArea->m_monsterCombo->m_nIndex
				<< end;

		ch->m_pArea->CloseComboZone();
		return ;
	}

	CMonsterCombo* combo;
	combo = ch->m_pArea->m_monsterCombo;
	if(combo->m_bIsBattle)
	{
		// �������� �Ϸ�ȵ���
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_NOT_COMPLETE_STAGE);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

#ifdef MONSTER_COMBO_FIX
	if(!combo->IsAllCharLive())
	{
		GAMELOG << init("FAIL START STAGE")
				<< "By DEAD PC" << delim
				<< "AREA INDEX" << delim
				<< combo->m_area->m_index << delim
				<< "COMBO INDEX" << delim
				<< combo->m_area->m_monsterCombo->m_nIndex
				<< end;

		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_DEAD_CHAR);
		SEND_Q(rmsg, ch->m_desc);

		return ;
	}
#endif // MONSTER_COMBO_FIX

	GAMELOG << init("MONSTER COMBO START", ch)
			<< end;

	if(!combo->StartStage())
	{
		GAMELOG << init("FAIL START STAGE")
				<< "BY StartStage() Error"
				<< "AREA INDEX: "
				<< combo->m_area->m_index
				<< " COMBO INDEX: "
				<< combo->m_area->m_monsterCombo->m_nIndex
				<< end;

		return ;
	}
}

void do_MonsterComboGotoWaitRoom( CPC* ch )
{
	if(!ch->m_pZone->IsComboZone())
		return ;
	if(!ch->m_pArea->m_bEnable || ch->m_pArea->m_monsterCombo->m_nIndex == -1)
	{
		GAMELOG << init("CLOSE COMBO AREA")
				<< "BY GOTO WAITROON Error"
				<< "AREA INDEX: "
				<< ch->m_pArea->m_index
				<< " COMBO INDEX: "
				<< ch->m_pArea->m_monsterCombo->m_nIndex
				<< end;

		ch->m_pArea->CloseComboZone();
		return ;
	}

	float x, z;
	char ylayer;
	int extra = 0;   // ����

	x = GetRandom(gserver->m_comboZone->m_zonePos[extra][1], gserver->m_comboZone->m_zonePos[extra][3]) / 2.0f;
	z = GetRandom(gserver->m_comboZone->m_zonePos[extra][2], gserver->m_comboZone->m_zonePos[extra][4]) / 2.0f;
	ylayer = gserver->m_comboZone->m_zonePos[extra][0];
	GET_R(ch) = 0.0f;
	GoTo(ch, ylayer, x, z, ch->m_pArea->GetHeight(ylayer, x, z), GET_R(ch));
}

