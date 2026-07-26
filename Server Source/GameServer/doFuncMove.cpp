#include <boost/foreach.hpp>
#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "Server.h"
#include "CmdMsg.h"
#include "doFunc.h"
#include "WarCastle.h"
#include "DratanCastle.h"
#include "Artifact_Manager.h"
#include "../ShareLib/packetType/ptype_old_do_action.h"
#include "../ShareLib/packetType/ptype_old_do_move.h"
#include "../ShareLib/packetType/ptype_old_do_skill.h"
#include "../ShareLib/packetType/ptype_old_do_monstercombo.h"
#include "../ShareLib/DBCmd.h"
#include "DBManager.h"
class CNPC;

//////////////////
// �̵����� �Լ�

void do_pd_Move(CPC* ch, CNetMsg::SP& msg)
{
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	pCastle->CheckRespond(ch);
	do_Move_hook(ch, msg, 1);
	RequestClient::moveForPernalDungeon* packet = reinterpret_cast<RequestClient::moveForPernalDungeon*>(msg->m_buf);

	if(packet->multicount > 20)
	{
		LOG_ERROR("HACKING : invalid multi count[%d]. charIndex[%d]", packet->multicount, ch->m_index);
		ch->m_desc->Close("invalid multi count");
		return;
	}

	{
		std::set<int> tset;
		for (int i = 0; i < packet->multicount; ++i)
		{
			if (tset.insert(packet->list[i].multiIndex).second == false)
			{
				LOG_ERROR("HACKING : duplicate multiIndex. charIndex[%d]", ch->m_index);
				ch->m_desc->Close("duplicate multiIndex");
				return;
			}
		}
	}

	if (ch->m_pZone == NULL || ch->m_pArea == NULL)
	{
		LOG_ERROR("HACKING : character is not in zone. charIndex[%d]", ch->m_index);
		ch->m_desc->Close("character is not in zone");
		return;
	}

	switch (packet->moveType)
	{
	case MSG_MOVE_WALK:
	case MSG_MOVE_RUN:
		ch->SetPlayerState(PLAYER_STATE_MOVING);
		break;

	case MSG_MOVE_PLACE:
		break;

	case MSG_MOVE_STOP:
		ch->ResetPlayerState(PLAYER_STATE_MOVING);
		break;

	case MSG_MOVE_FLY:
		if (!ch->m_wearInventory.wearItemInfo[WEARING_BACKWING])
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_PRODUCE_NOTOOL);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}
		ch->SetPlayerState(PLAYER_STATE_MOVING);
		break;

	default:
		return ;
	}

	for (int i = 0; i < packet->multicount; ++i)
	{
		if (packet->list[i].x < 0 || packet->list[i].z < 0 ||
				packet->list[i].x >= ch->m_pZone->m_attrMap[0].m_size[0] ||
				packet->list[i].z >= ch->m_pZone->m_attrMap[0].m_size[1] ||
				packet->list[i].ylayer < 0 || packet->list[i].ylayer >= ch->m_pZone->m_countY * 2)
		{
#ifdef _DEBUG
			LOG_INFO("doPDMove : x: %.2f, z: %.2f, h: %.2f, y: %d -> x: %.2f, z: %.2f, h: %.2f, y: %d",
					 GET_X(ch), GET_Z(ch), GET_H(ch), GET_YLAYER(ch),
					 packet->list[i].x, packet->list[i].z, packet->list[i].h, packet->list[i].ylayer);
#endif
			continue ;
		}

		CArea* m_area = ch->m_pArea;
		if (!m_area) return ;
		if(!m_area->m_zone->IsPersonalDungeon()) return ;

		CCharacter* tch = m_area->FindCharInCell(ch, packet->list[i].multiIndex, (MSG_CHAR_TYPE) MSG_CHAR_NPC);
		if (!tch) return ;

		CNPC* npc = IS_NPC(tch) ? TO_NPC(tch) : NULL;
		if (npc == NULL)
			continue;

		GET_X(npc) = packet->list[i].x;
		GET_Z(npc) = packet->list[i].z;
		GET_R(npc) = packet->list[i].r;
		npc->m_pos.m_h = packet->list[i].h;
		GET_YLAYER(npc) = packet->list[i].ylayer;
	}
}

void do_Move(CPC* ch, CNetMsg::SP& msg)
{

	do_Move_hook(ch, msg, 2);
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	pCastle->CheckRespond(ch);

	unsigned short old_map_attr = ch->GetMapAttr();
	int old_extra = ch->m_pZone->GetExtra(GET_X(ch), GET_Z(ch));

	bool old_war_zone = false;
	bool new_war_zone = false;

	old_war_zone = ch->isWarZone();

	RequestClient::moveForNormal* packet = reinterpret_cast<RequestClient::moveForNormal*>(msg->m_buf);

	if (ch->m_pZone == NULL || ch->m_pArea == NULL)
	{
		LOG_ERROR("HACKING : character is not in zone. charIndex[%d]", ch->m_index);
		ch->m_desc->Close("character is not in zone");
		return;
	}

	if (packet->x < 0 || packet->z < 0 || packet->x >= ch->m_pZone->m_attrMap[0].m_size[0] ||
			packet->z >= ch->m_pZone->m_attrMap[0].m_size[1] || packet->ylayer < 0 || packet->ylayer >= ch->m_pZone->m_countY * 2)
	{
#ifdef _DEBUG
		LOG_INFO("doMove : x: %.2f, z: %.2f, h: %.2f, y: %d -> x: %.2f, z: %.2f, h: %.2f, y: %d",
				 GET_X(ch), GET_Z(ch), GET_H(ch), GET_YLAYER(ch),
				 packet->x, packet->z, packet->h, packet->ylayer);
#endif
		return ;
	}

	switch (packet->moveType)
	{
	case MSG_MOVE_WALK:
	case MSG_MOVE_RUN:
	case MSG_MOVE_PLACE:
	case MSG_MOVE_STOP:
		break;

	case MSG_MOVE_FLY:
		if (!ch->m_wearInventory.wearItemInfo[WEARING_BACKWING])
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_PRODUCE_NOTOOL);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}
		break;

	default:
		{
			LOG_ERROR("HACKING : invalid moveType[%d]. charIndex[%d]", packet->moveType, ch->m_index);
			ch->m_desc->Close("invalid moveType");
			return;
		}
	}

	CCharacter* chMove = NULL;

	switch (packet->charType)
	{
	case MSG_CHAR_PC:
#ifdef __DEBUG
		GAMELOG << init("RECV : CharMove", ch)
				<< packet->speed << delim
				<< packet->x << delim
				<< packet->z << delim
				<< packet->h << delim
				<< packet->r << delim
				<< packet->ylayer
				<< end;
#endif

		if (ch->m_index != packet->index)
			return;

		chMove = ch;

		// �̵��ӵ� �˻�
		if (ch->m_admin < 1)
		{
			// �۽��� ������ ����
			//if (!ch->m_pZone->IsPersonalDungeon() && !ch->m_pZone->IsGuildRoom()) : �� pd�� �˻����� �ʴ°�? X, Z�� �Ÿ��� �˻��ϵ��� ���� bw
			//{
			// 060109 : BS : BEGIN : 200���� �̻� �̵� �Ұ�
			float walkSpeed = ch->m_walkSpeed;
			float runSpeed = ch->GetRunSpeed();
			float flySpeed = ch->m_flySpeed;

			if(ch->m_pZone->m_index == ZONE_DRATAN_CASTLE_DUNGEON && IS_PC(ch))
			{
				CDratanCastle * pCastle = CDratanCastle::CreateInstance();
				if(pCastle->m_dvd.GetZone() && pCastle->m_dvd.GetEnvRate() >= 90)
				{
					walkSpeed = walkSpeed + walkSpeed*0.1;
					runSpeed = runSpeed + runSpeed*0.1;
					flySpeed = flySpeed + flySpeed*0.1;
				}
			}

			float spd = 0.0f;
			switch( packet->moveType )
			{
			case MSG_MOVE_WALK :
				spd = walkSpeed;
				break;
			case MSG_MOVE_RUN :
				spd = runSpeed;
				break;
			case MSG_MOVE_FLY :
				spd = flySpeed;
				break;
			case MSG_MOVE_STOP:
				spd = runSpeed;
				break;
			default :
				spd = walkSpeed;
				break;
			}
			float dist = GetDistance(packet->x, packet->z, ch->m_pArea->GetHeight(GET_YLAYER(ch), packet->x, packet->z), ch);
			bool bCurrectX = false;
			bool bCurrectZ = false;
			//float chx = GET_X(ch);
			//float chz = GET_Z(ch);
			float errorFloat =0.0f;
			float tempFloat = ch->m_pArea->GetHeight(GET_YLAYER(ch), GET_X(ch), GET_Z(ch));
			float checkSpeed = 0.0f;

			//if( ABS(tempFloat-h) > 1 )
			{
				errorFloat = ABS(tempFloat-packet->h);
			}

			checkSpeed = spd;

			CPet* pet = ch->GetPet();
			if( pet )
			{
				if( pet->IsMount() )
					checkSpeed = pet->GetRunSpeed();
			}

			if( packet->moveType == MSG_MOVE_STOP )
				checkSpeed = checkSpeed * 5;
			else
				checkSpeed = checkSpeed * 3;

			if( GET_X(ch) > packet->x-checkSpeed - errorFloat && GET_X(ch) < packet->x+checkSpeed + errorFloat)
				bCurrectX = true;
			if( GET_Z(ch) > packet->z-checkSpeed - errorFloat && GET_Z(ch) < packet->z+checkSpeed + errorFloat)
				bCurrectZ = true;

			if( !bCurrectX || !bCurrectZ )
				//if (dist > 200.0f)
			{
				GAMELOG << init("HACK MOVE", ch)
						<< ch->m_pArea->m_zone->m_index << delim
						<< GET_X(ch) << delim
						<< GET_Z(ch) << delim
						<< GET_H(ch) << delim
						<< GET_YLAYER(ch) << delim
						<< packet->x << delim
						<< packet->z << delim
						<< ch->m_pArea->GetHeight(GET_YLAYER(ch), packet->x, packet->z) << delim
						<< packet->ylayer << delim
						<< dist << delim
						<< spd << delim
						<< bCurrectX << delim
						<< bCurrectZ << end;

				ch->SetDisableTime(3);

				GoTo(ch, GET_YLAYER(ch), GET_X(ch), GET_Z(ch), GET_H(ch), GET_R(ch), 1);

				ch->m_desc->IncreaseHackCount(1);
				return ;
			}
		}

		
		// ���� ����
		switch (packet->moveType)
		{
		case MSG_MOVE_WALK:
		case MSG_MOVE_RUN:
		case MSG_MOVE_FLY:
			ch->SetPlayerState(PLAYER_STATE_MOVING);
			break;
		case MSG_MOVE_STOP:
			ch->ResetPlayerState(PLAYER_STATE_MOVING);
			break;

		case MSG_MOVE_PLACE:
			break;
		default:
			return ;
		}
		break;

	case MSG_CHAR_NPC:
		chMove = ch->m_pArea->FindCharInCell(ch, packet->index, MSG_CHAR_NPC);
		break;

	case MSG_CHAR_PET:
		if (ch->GetPet())
		{
			CPet* pet = ch->GetPet();
			if (pet->m_index != packet->index)
				return ;
			if (pet->m_pArea == NULL)
				return ;
			if (pet->m_pZone == NULL)
				return ;
			if (!pet->IsSummon())
				return ;
			if (!pet->IsActive())
				return ;
			if (pet->IsMountType())
				return ;
			chMove = pet;
		}
		else
			return ;
		break;

	case MSG_CHAR_ELEMENTAL:
		chMove = ch->m_pArea->FindCharInCell(ch, packet->index, MSG_CHAR_ELEMENTAL);
		if (chMove)
		{
			CElemental* elemental = TO_ELEMENTAL(chMove);
			if (elemental)
			{
				// ������ �����ϰ�
				if (elemental->GetOwner() != ch)
					return ;

				if (GetDistance(chMove, ch) >= 25) //kimpobin
					GoTo(chMove, ch->m_pos.m_yLayer, ch->m_pos.m_x, ch->m_pos.m_z, ch->m_pos.m_h, ch->m_pos.m_r);

			}
		}
		break;

	case MSG_CHAR_APET:
		{
			CAPet* apet = ch->GetAPet();
			if( apet )
			{
				if ( !apet->IsSummon() )
					return ;
				chMove = apet;
			}
		}
		break;

	default:
		return ;
	}

	if (!chMove || DEAD(chMove) || !chMove->CanMove())
		return ;

	if (!IS_NPC(chMove))
	{
		if( IS_PC(chMove) )
		{
			CAPet* apet = TO_PC(chMove)->GetAPet();
			if( apet && apet->IsMount() )
				ch->m_pArea->MoveChar((CCharacter*)apet, packet->ylayer, packet->x, packet->z, packet->h, packet->r, (MSG_MOVE_TYPE)packet->moveType);
		}
		ch->m_pArea->MoveChar(chMove, packet->ylayer, packet->x, packet->z, packet->h, packet->r, (MSG_MOVE_TYPE)packet->moveType);
	}
	else
	{
		GAMELOG << init("DEBUG NPC MOVE")
				<< "ZONE : " << ch->m_pZone->m_index << " : NPC : " << chMove->m_name << end;
	}

	if (TO_PC(ch)->GetPlayerState() == PLAYER_STATE_PKMODE || 
		TO_PC(ch)->GetPlayerState() == PLAYER_STATE_PKMODEDELAY) {
		ch->m_assist.CureBySkillIndex(CUBE_BUF);
		ch->m_assist.CureBySkillIndex(IGNI1_BUF);
		ch->m_assist.CureBySkillIndex(IGNI2_BUF);
		ch->m_assist.CureBySkillIndex(IGNI3_BUF);
		ch->m_assist.CureBySkillIndex(IGNI4_BUF);
		ch->m_assist.CureBySkillIndex(CAST_POTION);
		ch->m_assist.CureBySkillIndex(VELOCITY_BUF);
		ch->m_assist.CureBySkillIndex(1742);
		ch->m_assist.CureBySkillIndex(975);
		ch->m_assist.CureBySkillIndex(1897);
		ch->m_assist.CureBySkillIndex(981);
		ch->m_assist.CureBySkillIndex(1903);
		ch->m_assist.CureBySkillIndex(988);
		ch->m_assist.CureBySkillIndex(1910);
		ch->m_assist.CureBySkillIndex(1172);
		ch->m_assist.CureBySkillIndex(1278);
		ch->m_assist.CureBySkillIndex(1310);
		ch->m_assist.CureBySkillIndex(1938);
		ch->m_assist.CureBySkillIndex(1174);
		ch->m_assist.CureBySkillIndex(1280);
		ch->m_assist.CureBySkillIndex(1312);
		ch->m_assist.CureBySkillIndex(1940);
		ch->m_assist.CureBySkillIndex(1188);
		ch->m_assist.CureBySkillIndex(1287);
		ch->m_assist.CureBySkillIndex(1319);
		ch->m_assist.CureBySkillIndex(1947);
		ch->m_assist.CureBySkillIndex(931);
		ch->m_assist.CureBySkillIndex(1037);
		ch->m_assist.CureBySkillIndex(1876);
		ch->m_assist.CureBySkillIndex(1918);
		ch->m_assist.CureBySkillIndex(936);
		ch->m_assist.CureBySkillIndex(1042);
		ch->m_assist.CureBySkillIndex(1881);
		ch->m_assist.CureBySkillIndex(1923);
		ch->m_assist.CureBySkillIndex(947);
		ch->m_assist.CureBySkillIndex(10553);
		ch->m_assist.CureBySkillIndex(1892);
		ch->m_assist.CureBySkillIndex(1934);
		ch->m_assist.CureBySkillIndex(946);
		ch->m_assist.CureBySkillIndex(1891);
		ch->m_assist.CureBySkillIndex(1052);
		ch->m_assist.CureBySkillIndex(1933);
		ch->m_assist.CureBySkillIndex(963);
		ch->m_assist.CureBySkillIndex(967);
		ch->m_assist.CureBySkillIndex(1186);
		ch->m_assist.CureBySkillIndex(1285);
		ch->m_assist.CureBySkillIndex(1317);
		ch->m_assist.CureBySkillIndex(1945);
		ch->m_assist.CureBySkillIndex(1036);
		ch->m_assist.CureBySkillIndex(1917);
		ch->m_assist.CureBySkillIndex(794);
		ch->m_assist.CureBySkillIndex(1896);
		ch->m_assist.CureBySkillIndex(980);
		ch->m_assist.CureBySkillIndex(1902);
		ch->m_assist.CureBySkillIndex(968);
		ch->m_assist.CureBySkillIndex(962);
		ch->m_assist.CureBySkillIndex(1093);
		ch->m_assist.CureBySkillIndex(229);
		ch->m_assist.CureBySkillIndex(323);
		ch->m_assist.CureBySkillIndex(1798);
		ch->m_assist.CureBySkillIndex(1871);
		ch->m_assist.CureBySkillIndex(1997);
		ch->m_assist.CureBySkillIndex(1998);
		ch->m_assist.CureBySkillIndex(1999);
		ch->m_assist.CureBySkillIndex(2000);
		ch->m_assist.CureBySkillIndex(2001);
		ch->m_assist.CureBySkillIndex(2002);
		ch->m_assist.CureBySkillIndex(2003);
		ch->m_assist.CureBySkillIndex(2013);
		ch->m_assist.CureBySkillIndex(2044);
		ch->m_assist.CureBySkillIndex(2045);
		ch->m_assist.CureBySkillIndex(2046);
		ch->m_assist.CureBySkillIndex(2047);
		ch->m_assist.CureBySkillIndex(987);
		ch->m_assist.CureBySkillIndex(1909);
		ch->m_assist.CureBySkillIndex(935);
		ch->m_assist.CureBySkillIndex(1880);
		ch->m_assist.CureBySkillIndex(1057);
		ch->m_assist.CureBySkillIndex(1058);
		ch->m_assist.CureBySkillIndex(1059);
		ch->m_assist.CureBySkillIndex(1077);
		ch->m_assist.CureBySkillIndex(1076);
		ch->m_assist.CureBySkillIndex(939);
		ch->m_assist.CureBySkillIndex(941);
		ch->m_assist.CureBySkillIndex(943);
		ch->m_assist.CureBySkillIndex(966);
		ch->m_assist.CureBySkillIndex(971);
		ch->m_assist.CureBySkillIndex(977);
		ch->m_assist.CureBySkillIndex(984);
		ch->m_assist.CureBySkillIndex(991);
		ch->m_assist.CureBySkillIndex(1045);
		ch->m_assist.CureBySkillIndex(1047);
		ch->m_assist.CureBySkillIndex(1049);
		ch->m_assist.CureBySkillIndex(1176);
		ch->m_assist.CureBySkillIndex(1190);
		ch->m_assist.CureBySkillIndex(1197);
		ch->m_assist.CureBySkillIndex(1282);
		ch->m_assist.CureBySkillIndex(1289);
		ch->m_assist.CureBySkillIndex(1296);
		ch->m_assist.CureBySkillIndex(1314);
		ch->m_assist.CureBySkillIndex(1321);
		ch->m_assist.CureBySkillIndex(1328);
		ch->m_assist.CureBySkillIndex(1369);
		ch->m_assist.CureBySkillIndex(1884);
		ch->m_assist.CureBySkillIndex(1886);
		ch->m_assist.CureBySkillIndex(1888);
		ch->m_assist.CureBySkillIndex(1899);
		ch->m_assist.CureBySkillIndex(1906);
		ch->m_assist.CureBySkillIndex(1913);
		ch->m_assist.CureBySkillIndex(1926);
		ch->m_assist.CureBySkillIndex(1928);
		ch->m_assist.CureBySkillIndex(1930);
		ch->m_assist.CureBySkillIndex(1942);
		ch->m_assist.CureBySkillIndex(1949);
		ch->m_assist.CureBySkillIndex(1956);
		ch->m_assist.CureBySkillIndex(1080);
		ch->m_assist.CureBySkillIndex(1834);
		ch->m_assist.CureBySkillIndex(1835);
		ch->m_assist.CureBySkillIndex(1836);
		ch->m_assist.CureBySkillIndex(1838);
		ch->m_assist.CureBySkillIndex(1839);
		ch->m_assist.CureBySkillIndex(1837);
		ch->m_assist.CureBySkillIndex(2057);
		ch->m_assist.CureBySkillIndex(1079);
	}

	if (ch->m_assist.FindBySkillIndex(IMMOTAL_BUF) && ch->m_bFirstDoIt == false)
	{
		//���� �ð��� 15�ʷμ���, ����� ������ ��Ŷ ����
		CAssistData* data = ch->m_assist.m_help.getHead();
		while(data)
		{
			if(data->m_proto->m_index == IMMOTAL_BUF)
			{
				data->m_remain = 100;
				ch->m_bFirstDoIt = true;

				CNetMsg::SP rmsg(new CNetMsg);
				AssistModifyMsg(rmsg, ch, data->m_index, data->m_proto->m_index, data->m_level, data->m_remain, 1);
				ch->m_pArea->SendToCell(rmsg, ch, true);
			}
			data = data->m_next;
		}
	}

	unsigned short new_map_attr = ch->GetMapAttr();
	int new_extra = ch->m_pZone->GetExtra(GET_X(ch), GET_Z(ch));

	new_war_zone = ch->isWarZone();

	if(old_war_zone != new_war_zone)
	{
		ch->CalcStatus(true);
	}

	if(old_map_attr != new_map_attr)
	{
		ch->m_bChangeStatus = true;
	}

	if(ch->GetJoinFlag(ch->m_pZone->m_index) != 0)
	{
		if ( ch->GetMapAttr() & MATT_WAR || ch->m_pZone->IsWarZone(GET_X(ch), GET_Z(ch)) == true ) 
		{
			if( ApplyWarSkill(ch, ch->m_pZone->m_index) == false )
				ClearWarSkill(ch);
		}
		else
		{
			ClearWarSkill(ch);
		}
	}
	else if(ch->m_isWarSkillCheck == true)
	{
		ClearWarSkill(ch);
		ch->m_isWarSkillCheck = false;
	}

	//���� �������� ����ִ� ���� �ǽ������� �̵��ߴٸ�
	if(ch->m_bChangeStatus == true && ArtifactManager::instance()->isOwnerPC(ch->m_index) == true)
	{
		ch->CalcStatus(true);
		
		//��Ƽ�� �ִٸ�
		if(ch->m_party != NULL)
		{
			ch->m_party->updateCalcMember();
		}
	}

	else if(ch->m_bChangeStatus == true 
		&& ch->m_party != NULL
		&& ArtifactManager::instance()->isArtifactParty(ch->m_party) == true)
	{
		ch->CalcStatus(true);
	}
}

void do_GoZone(CPC* ch, CNetMsg::SP& msg)
{
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	pCastle->CheckRespond(ch);

	RequestClient::moveGoZone* packet = reinterpret_cast<RequestClient::moveGoZone*>(msg->m_buf);

	//rvr Ÿ���� �ִ� ��� ��.
	if (ch->m_pZone->isRVRZone() && packet->zone != ZONE_START)
	{
		CNPCProto* npcProto = gserver->m_npcProtoList.FindProto(packet->npcIndex);
	
		if (npcProto == NULL) 
		{
			LOG_ERROR("HACKING? : not found npc. charIndex[%d] npcIndex[%d]", ch->m_index, packet->npcIndex);
			ch->m_desc->Close("not found npc");
			return;
		}

		if (npcProto->m_rvr_value > 0 && npcProto->m_rvr_value != ch->getSyndicateType())
		{
			LOG_ERROR("HACKING? : not equal rvr type. charIndex[%d] npcIndex[%d]", ch->m_index, packet->npcIndex);
			ch->m_desc->Close("not equal rvr type");
			return;
		}
	}
	
	

	bool bRoyal = false;
	if(ch->m_admin < 1)
	{
		if (packet->zone == ZONE_START)
			bRoyal = true;
		// �Ѵ� ����� �����ϸ� bRoyal = true; �ξⷳ���� ���°Ŵ�!!!
		if((packet->zone == 38) && (gserver->m_RoyalRumble.m_WaitPlayerList.FindNode(ch->m_index)))
			bRoyal = true;
	}
	else
	{
		bRoyal = true;
	}

	if( !ch->m_pZone->IsPersonalDungeon() )
	{
		// ���̵� ��ȿ�� �˻�
		bool bHackGoZone = false;
		bool bSkipFindNPC = false;

		// ������ ���� ��ȿ�� �˻�
		const int nSizeOfTable = 15;
		// Current Zone, Request Zone, Request Position, Valid Position, Valid Cell Size
		static int nCheckValidWarp[nSizeOfTable][5] =
		{
			{ ZONE_EGEHA_DUNGEON_1, ZONE_EGEHA_DUNGEON_8, 0, 1, 2},
			{ ZONE_EGEHA_DUNGEON_8, ZONE_EGEHA_DUNGEON_1, 1, 0, 2},
			{ ZONE_EGEHA_DUNGEON_8, ZONE_EGEHA_DUNGEON_9, 0, 1, 2},
			{ ZONE_EGEHA_DUNGEON_9, ZONE_EGEHA_DUNGEON_8, 1, 0, 2},
			{ ZONE_EGEHA_DUNGEON_9, ZONE_EGEHA_DUNGEON_10, 0, 1, 2},
			{ ZONE_EGEHA_DUNGEON_10, ZONE_EGEHA_DUNGEON_9, 1, 0, 2},
			{ ZONE_STREIANA, ZONE_MONDSHINE, 0, 1, 5},
			{ ZONE_MONDSHINE, ZONE_STREIANA, 6, 5, 2},
			{ ZONE_MERAC, ZONE_BLOODYMIR, 0, 20, 2 }
		};
		int nCheck;
		for (nCheck = 0; nCheck < nSizeOfTable; nCheck++)
		{
			if (ch->m_pZone->m_index == nCheckValidWarp[nCheck][0])
			{
				if (packet->zone == nCheckValidWarp[nCheck][1])
				{
					if (packet->extra == nCheckValidWarp[nCheck][2])
					{
						int nTestCellX, nTestCellZ;
						ch->m_pArea->PointToCellNum(ch->m_pZone->m_zonePos[nCheckValidWarp[nCheck][3]][1] / 2.0f, ch->m_pZone->m_zonePos[nCheckValidWarp[nCheck][3]][2] / 2.0f, &nTestCellX, &nTestCellZ);
						if (ABS(ch->m_cellX - nTestCellX) > nCheckValidWarp[nCheck][4] || ABS(ch->m_cellZ - nTestCellZ) > nCheckValidWarp[nCheck][4])
							bHackGoZone = true;
					}
					else
					{
						bHackGoZone = true;
					}
					bSkipFindNPC = true;
					break;
				}
			}

			if( packet->npcIndex == 89 )		// �������� ������ �̵�
			{
				bSkipFindNPC = true;
				break;
			}

			if(ch->m_pZone->m_index == ZONE_START && packet->zone == ZONE_MONDSHINE)
 		    {
  				bSkipFindNPC = true;
 			}

			if(ch->m_pZone->m_index == ZONE_START && packet->zone == ZONE_TARIAN)
 		    {
  				bSkipFindNPC = true;
 			}

			 if(ch->m_pZone->m_index == ZONE_START && packet->zone == ZONE_TRIVIA_CANYON)
 		    {
  				bSkipFindNPC = true;
 			}

			 if(ch->m_pZone->m_index == ZONE_START && packet->zone == ZONE_DUNGEON1)
 		    {
  				bSkipFindNPC = true;
 			}
			  if(ch->m_pZone->m_index == ZONE_RVR && packet->zone == ZONE_START)
 		    {
  				bSkipFindNPC = true;
 			}

			  if (ch->m_pZone->m_index == WANDERLUST && packet->zone == WANDERLUST)
			  {
				  bSkipFindNPC = true;
			  }
		}

		if(bRoyal)
			bSkipFindNPC = true;

		if ( !bSkipFindNPC && !ch->m_pArea->FindProtoNPCInCell(ch, packet->npcIndex, false, 2) )
			bHackGoZone = true;

		if ( gserver->m_npcProtoList.FindProto(packet->npcIndex) && !(gserver->m_npcProtoList.FindProto(packet->npcIndex)->m_zone_flag & (LONGLONG)1 << packet->zone) )
			bHackGoZone = true;

		if ( gserver->m_npcProtoList.FindProto(packet->npcIndex) && gserver->m_npcProtoList.FindProto(packet->npcIndex)->m_extra_flag != packet->extra )
			bHackGoZone = true;

		if (bHackGoZone)
		{
			GAMELOG << init("HACK_GO_ZONE", ch)
					<< end;
			return ;
		}
	}

	if (packet->zone == ZONE_OXQUIZROOM)
	{
		time_t timeCurrent;
		time(&timeCurrent);
		if ((!gserver->m_bEventOX || gserver->m_timeEventOXStart < timeCurrent) && ch->m_admin < 2)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			EventOXQuizMsg(rmsg, MSG_EVENT_OXQUIZ_INVALID_TIME);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
	}

	// ���� �̱� �������δ� �̵� �Ұ�
	if ((ch->m_pZone->IsPersonalDungeon() || ch->m_pZone->IsGuildRoom() || ch->m_pZone->IsComboZone()) && ch->m_pZone->m_index == packet->zone)
		return ;

	// ���� ã�Ƽ�
	CZone* pZone  = gserver->FindZone(packet->zone);
	if (pZone == NULL)
		return;

#ifdef EGEHA_ZONE_PAYMENT
	if ( packet->zone == ZONE_EGEHA )
	{
		if( ch->m_pZone->m_index != ZONE_EGEHA_DUNGEON_1 && ch->m_pZone->m_index != ZONE_EGEHA_DUNGEON_8
				&& ch->m_pZone->m_index != ZONE_EGEHA_DUNGEON_9 && ch->m_pZone->m_index != ZONE_EGEHA_DUNGEON_10
				&& ch->m_pZone->m_index != ZONE_FLORAIM_CAVE)
		{
			if( ch->m_inventory.getMoney())
			{
				if( ch->m_inventory.getMoney() < EGEHA_ZONE_PAYMENT )
				{
					// ���� ������ �ִ� ���� ���� �����޼��� ����
					CNetMsg::SP rmsg(new CNetMsg);
					SysMsg( rmsg, MSG_SYS_SHORT_MONEY);
					SEND_Q( rmsg, ch->m_desc );
					return;
				}
				else if ( ch->m_inventory.getMoney() >= EGEHA_ZONE_PAYMENT )
				{
					ch->m_inventory.decreaseMoney(EGEHA_ZONE_PAYMENT);
				}
			}
			else
			{
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg( rmsg, MSG_SYS_SHORT_MONEY);
				SEND_Q( rmsg, ch->m_desc );
				return;
			}
		}
	}

#endif // EGEHA_ZONE_PAYMENT

#ifdef FUN_ZONE_PAYMENT
	if (packet->zone == FUN_ZONE)
	{
		// Check for the required item (ID: 20753) in the character's inventory
		CItem* funitem20753 = ch->m_inventory.FindByDBIndex(20753, 0, 0);

		if (funitem20753 == NULL)
		{
			// Send a system message: Unable to warp to the zone
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_SHORT_MONEY);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}	
		ch->m_inventory.decreaseItemCount(funitem20753, 1);
		
		
	}

#endif
	if(pZone->IsExtremeCube() || pZone->IsExpedRaidZone() || pZone->IsPartyRaidZone())
	{
		GAMELOG << init("MSG_GO_ZONE HACK", ch) << "ZONE" << delim << packet->zone << end;
	//	ch->m_desc->Close("MSG_GO_ZONE_HACK");
	//	return ;
	}

	if (packet->extra < 0 || packet->extra >= pZone->m_countZonePos)
		return ;

	if (ch->m_pZone->m_index == ZONE_SINGLE_DUNGEON_TUTORIAL && packet->zone == ZONE_START)
		packet->extra = 6;

#if defined (LC_GAMIGO) || defined (QUEST_EXTEND_REPEAT_DAY)
	if(pZone->IsPersonalDungeon())
	{
		int questindex = 0;
		switch(pZone->m_index)
		{
		case ZONE_SINGLE_DUNGEON1:
			questindex = 13;
			break;
		case ZONE_SINGLE_DUNGEON2:
			questindex = 14;
			break;
		default:
			questindex = 0;
			break;
		}

		if(questindex > 0)
		{
			CQuest* quest;
			quest = ch->m_questList.FindQuest(questindex);
			if(!quest)
			{
				// ����Ʈ�� ���� ����.
				GAMELOG << init("GO_ZONE_FAILED: QUEST NOT EXIST", ch) << questindex << end;
				return ;
			}

			if(quest->IsCompleted())
			{
				// �̹� �Ϸ� �Ǿ���.
				GAMELOG << init("GO_ZONE_FAILED: QUEST COMPLETE", ch) << questindex << end;
				return ;
			}
		}
	}
#endif // LC_GAMIGO

#ifdef MOVE_MONDSHINE_NO_QUEST
	
	if( packet->zone == ZONE_MONDSHINE)
	{
		if( !(ch->m_questList.FindQuest(249, QUEST_STATE_DONE) || ch->m_questList.FindQuest(249, QUEST_STATE_RUN)) )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			QuestErrorMsg(rmsg, MSG_QUEST_ERR_CHECK_DONE_ING);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}
	}

#endif // END MOVE_MONDSHINE_NO_QUEST
// ITS 4620 : ���� �����
// #ifdef BLOODYMIR_MOVE_LIMIT // ���̰� ������ ���� ����
//	if( zone == ZONE_BLOODYMIR)
//	{
//		if( !(ch->m_questList.FindQuest(580, QUEST_STATE_DONE) || ch->m_questList.FindQuest(580, QUEST_STATE_RUN)) )
//			return;
//	}
//#endif

	ch->m_bBattleWarfare = false;

	GoZone(ch, packet->zone,
		   pZone->m_zonePos[packet->extra][0],														// ylayer
		   GetRandom(pZone->m_zonePos[packet->extra][1], pZone->m_zonePos[packet->extra][3]) / 2.0f,		// x
		   GetRandom(pZone->m_zonePos[packet->extra][2], pZone->m_zonePos[packet->extra][4]) / 2.0f);		// z
}

bool __GoZoneBase(CPC* ch, int zone, char ylayer, float x, float z, const char *fname, const int line);

bool GoZoneBase(CPC* ch, int zone, char ylayer, float x, float z, const char *fname, const int line)
{
	bool breturn = __GoZoneBase(ch, zone, ylayer, x, z, fname, line);

	CZone* pZone = gserver->FindZone(zone);

	if(pZone == NULL)
	{
		return breturn;
	}

	//���� ��ų ���� �� ����
	if ( ch->GetMapAttr() & MATT_WAR || ch->m_pZone->IsWarZone(GET_X(ch), GET_Z(ch)) == true )
	{
		if( ApplyWarSkill(ch, pZone->m_index) == false )
		{
			ClearWarSkill(ch);
		}
	}
	else
	{
		ClearWarSkill(ch);
	}

	if( ch->m_desc->m_connected == CON_PREPARE_PLAY )
	{
		ch->m_targetPC = NULL;
		ch->m_desc->m_connected = CON_PREPARE_PLAY_BEFORE;
	}

	return breturn;
}

bool __GoZoneBase(CPC* ch, int zone, char ylayer, float x, float z, const char *fname, const int line)
{
	LOG_INFO("GoZone > %s : %s : %s : DEST : %d LAYER : %d FILE : %s LINE : %d",
			 (const char*)ch->m_name, (const char *)ch->m_nick, (const char *)ch->m_desc->m_idname,
			 zone, ylayer, fname, line);

#ifdef GER_LOG
	GAMELOGGEM << init( 0, "CHAR_ZONE_TRANSITION")
		<< LOG_VAL("account-id", ch->m_desc->m_idname ) << blank
		<< LOG_VAL("character-id", ch->m_desc->m_pChar->m_name ) << blank
		<< LOG_VAL("dest-zone-id", zone ) << blank
		<< LOG_VAL("src-zone-id", ch->m_desc->m_pChar->m_pZone->m_index ) << blank
		<< LOG_VAL("first-time","1") << blank
		<< LOG_VAL("level", ch->m_level ) << blank
		<< endGer;
#endif // GER_LOG


	if (ch->m_exchange)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ExchangeReqMsg(rmsg, MSG_EXCHANGE_REQ_REJECT, NULL, NULL);
		do_Exchange(ch, rmsg);
	}

	ch->SummonNpcRemoveAll(true);
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	pCastle->CheckRespond(ch);

	CPC* findCPC = PCManager::instance()->getPlayerByCharIndex(ch->m_index);
	if (findCPC == NULL)
		return false;

	if(!ch || !ch->m_pZone || !ch->m_pArea || !ch->m_desc)
	{
		return false;
	}

	if(ArtifactManager::instance()->isOwnerPC(ch->m_index) == true)
	{
		//������ ���� �ִ� ������ ��� �Ʒ� ������ �����Ϸ��� �ϸ� return
		if(ArtifactManager::instance()->canMove(zone) == false)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_ARTIFACT_DONT_IN_DUNGEON);
			SEND_Q(rmsg, ch->m_desc);
			return false;
		}
	}

	switch(zone)
	{
	case ZONE_SINGLE_DUNGEON3:
	case ZONE_SINGLE_DUNGEON4:
		if( ch->m_admin < 2 && !ch->CheckDungeonData(zone) )
		{
			GAMELOG << init("PD_BUG_GO_ZONE", ch)
					<< end;
			return false;
		}
	default:
		break;
	}

	bool bGoto = false;
	bool bValid = false;
	CZone* pZone = NULL;

#if defined (EXTREME_CUBE) || defined(LC_TLD)
	CParty* pParty = NULL;
#endif
	int nTempRaidAreaNum = -1;
	CExpedition* pExped = NULL;

	// �ɾ������� ������ �����.
	if(ch->IsSetPlayerState(PLAYER_STATE_SITDOWN))
	{
		ch->TogglePlayerState(PLAYER_STATE_SITDOWN);
		ch->CalcStatus(true);
	}

	int i = 0;
	if (ch->m_pZone->m_index == zone)
	{
		// ���� ���ȿ����� �̵�
		bGoto = true;
		bValid = true;
		pZone = ch->m_pZone;
	}
	else
	{
		pZone = gserver->FindZone(zone);
		if (pZone == NULL || pZone->m_area == NULL)
			return false;

		if (pZone->m_bRemote)
		{
			// �ܺ� ������ �ν��Ͻ� ������ �Ұ���
			if (!pZone->IsGuildRoom() && !pZone->IsPersonalDungeon())
			{
				bGoto = false;
				bValid = true;
			}
		}
		else
		{
			bGoto = true;
			bValid = true;
		}
	}

	if (!bValid)
	{
		return false;
	}

	if(pZone->isRVRZone())
	{
		//�̱״ϼ� ������ �ִٸ� ����
		//ch->m_assist.CureBySkillIndex(CUBE_BUF);
		//ch->m_assist.CureBySkillIndex(IGNI1_BUF);
		//ch->m_assist.CureBySkillIndex(IGNI2_BUF);
		//ch->m_assist.CureBySkillIndex(IGNI3_BUF);
		//ch->m_assist.CureBySkillIndex(IGNI4_BUF);
		ch->m_assist.CureBySkillIndex(VELOCITY_BUF);

		//�� ������ �ִٸ� ����
		ch->m_assist.CureByPetSkill();
	}

	CZone* pCurZone = ch->m_pZone;
	CArea* pCurArea = ch->m_pArea;

	if(!pCurArea || !pCurZone || !pCurZone->m_area)
	{
		return false;
	}

	// ���� �ٲ��
	if (pCurZone != pZone)
	{
		int errortype = ch->CanWarp() ;
		if( errortype && errortype != MSG_SYS_CANT_WARP_OTHER )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg( rmsg, (MSG_SYS_TYPE) errortype );
			SEND_Q( rmsg, ch->m_desc );
			return false;
		}

		if( ch->m_level < pZone->m_minLevel || ch->m_level > pZone->m_maxLevel )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg( rmsg, (MSG_SYS_TYPE) MSG_SYS_CANNOT_GOZONE_LEVEL );
			SEND_Q( rmsg, ch->m_desc );
			return false;
		}

		// area�� disable�Ǵ� ��Ȳ�̸� ��Ƽ�� areanum�� �ʱ�ȭ ��Ų��.
		if (pCurZone && (pCurZone->m_index == ZONE_ALTER_OF_DARK || pCurZone->m_index == ZONE_CAPPELLA_1 || pCurZone->m_index == ZONE_AKAN_TEMPLE
						 || pCurZone->m_index == ZONE_TARIAN_DUNGEON || pCurZone->m_index == ZONE_ENCHANTED_DUNGEON)
				&& pCurArea->GetAllClientCount_Area() <= 1 && pCurArea->m_inCount == 0 )
		{
			if(ch->IsExped())
			{
				nTempRaidAreaNum = ch->m_Exped->m_nRaidAreaNum;
				ch->m_Exped->m_nRaidAreaNum = -1;
				ch->m_Exped->m_nRaidZoneNum = -1;
				ch->m_Exped->m_nDifficulty = -1;
			}
			/*if (ch->IsParty())
			{
				nTempRaidAreaNum = ch->m_party->m_nRaidAreaNum;
				ch->m_party->m_nRaidAreaNum = -1;
				ch->m_party->m_nRaidZoneNum = -1;
			}*/
		}
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS	
		if (pCurZone && (pCurZone->m_index == ZONE_CAPPELLA_1
#ifndef CLOUD_EXPEDITION_SOLO_DUNGEONS	
			|| pCurZone->m_index == ZONE_PARTY_DUNGEON0
			|| pCurZone->m_index == ZONE_PARTY_DUNGEON1
			|| pCurZone->m_index == ZONE_PARTY_DUNGEON2
			|| pCurZone->m_index == ZONE_PARTY_DUNGEON3
			|| pCurZone->m_index == ZONE_PARTY_DUNGEON4
#endif
			)
			&& pCurArea->GetAllClientCount_Area() <= 1)
		{
			GAMELOG << init("CLOSE PARTY AREA MOVE", ch)
				<< "AREA INDEX: " << pCurArea->m_index << delim
				<< "AREA COUNT: " << pCurArea->m_inCount << delim
				<< "AREA DIFFICULTY: " << pCurArea->m_RaidDifficulty << delim
				<< end;


			if (ch->IsParty())
			{
				nTempRaidAreaNum = ch->m_party->m_nRaidAreaNum;
				ch->m_party->m_nRaidAreaNum = -1;
				ch->m_party->m_nRaidZoneNum = -1;
				ch->m_party->m_nDifficulty = -1;

				GAMELOG << init("NEW PARTY INFOS", ch)
					<< "PARTY AREA NUM: " << ch->m_party->m_nRaidAreaNum << delim
					<< "PARTY ZONE: " << ch->m_party->m_nRaidZoneNum << delim
					<< "PARTY DIFFICULTY: " << ch->m_party->m_nDifficulty << delim
					<< end;
			}
		}
#endif
		// ��Ƽ ó��
		if (ch->m_party != NULL)
		{
			ch->m_party->deletePartyRecallMember(ch->m_index);
			// �ʴ��ϰų�, �ʴ���� ����� ��� ������ ó��
			if (ch->m_party->GetRequestIndex() > 0 && (ch->m_party->GetBossIndex() == ch->m_index || ch->m_party->GetRequestIndex() == ch->m_index))
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PartyMsg(rmsg, MSG_PARTY_REJECT);
				do_Party(ch, rmsg);
			}
			// ������ �۴��̸� ��ƼŻ��
			else if (pZone->IsPersonalDungeon()
					 || pZone->IsWarGroundZone()
					 || pZone->IsPersonalRaid()
					)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PartyMsg(rmsg, MSG_PARTY_QUIT);
				do_Party(ch, rmsg);
			}
			else if (pZone->isRVRZone())
			{
				// �ٸ� ��Ƽ����� ���밡 �ٸ��ٸ� ��Ƽ Ż��
				for (int i = 0; i < MAX_PARTY_MEMBER; ++i)
				{
					if (	ch->m_party->m_listMember[i] != NULL
							&&	ch->m_party->m_listMember[i]->GetCharIndex() != ch->m_index
							&&  ch->m_party->m_listMember[i]->GetMemberPCPtr() != NULL
							&&	ch->m_party->m_listMember[i]->GetMemberPCPtr()->getSyndicateType() != ch->getSyndicateType()
					   )
					{
						CNetMsg::SP rmsg(new CNetMsg);
						PartyMsg(rmsg, MSG_PARTY_QUIT);
						do_Party(ch, rmsg);

						{
							CNetMsg::SP rmsg(new CNetMsg);
							SysMsg(rmsg, MSG_SYS_DO_NOT_PARTY_THISZONE);
							SEND_Q(rmsg, ch->m_desc);
						}
					}
				}
			}

#if defined (EXTREME_CUBE) || defined(LC_TLD)
			if(ch->IsParty())
			{
				pParty = ch->m_party;
			}
#endif //
			ch->m_party->SetMemberPCPtr(ch->m_index, NULL);
			ch->m_party = NULL;
		}

		// ������ ó��
		if (ch->IsExped())
		{
			if (ch->m_Exped->GetRequestIndex() > 0 && (ch->m_Exped->GetBossIndex() == ch->m_index || ch->m_Exped->GetRequestIndex() == ch->m_index))
			{
				// �ʴ� �ź�
				CNetMsg::SP rmsg(new CNetMsg);
				ExpedRejectReqMsg(rmsg);
				do_Expedition(ch, rmsg);
			}
			// ������ �۴��̸� ������ Ż��
			else if (pZone->IsPersonalDungeon()
					 || pZone->IsWarGroundZone()
					 || pZone->IsPersonalRaid()
					)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				//ExpedMsg(tmpmsg, MSG_QUIT_REQ);
				ExpedQuitReqMsg(rmsg, 0);
				//tmpmsg.Init(MSG_EXPEDITION);
				//tmpmsg << (unsigned char)MSG_QUIT_REQ;
				do_Expedition(ch, rmsg);
			}
			else if (pZone->isRVRZone())
			{
				// �ٸ� ���̵��� ���밡 �ٸ��ٸ� ���̵� Ż��
				for (int i = 0; i < MAX_EXPED_GROUP; ++i)
				{
					for (int j = 0; j < MAX_EXPED_GMEMBER; ++j)
					{
						CPC* pExpedMember = ch->m_Exped->GetMemberPCPtr(i, j);
						if (	pExpedMember != NULL &&	pExpedMember->m_index != ch->m_index
								&&	pExpedMember->getSyndicateType() != ch->getSyndicateType()
						   )
						{
							CNetMsg::SP rmsg(new CNetMsg);
							ExpedQuitReqMsg(rmsg, 0);
							do_Expedition(ch, rmsg);
						}
					}
				}
			}

			ch->m_Exped->SendToExpedTargetClear(ch);

			pExped = ch->m_Exped;

			ch->m_Exped->SetMemberPCPtr(ch->m_index, NULL);
			ch->m_Exped = NULL;
		}

		ArtifactManager::instance()->move_zone(ch, zone);
	} // ���� �ٲ��

	bool bSetPrePlay = false;

	if( !pZone->IsExpedRaidZone() && !pZone->IsPartyRaidZone() ) // �̵��� ���� ���̵� ���� �ƴϸ� ���� ���� �ʱ�ȭ
	{
		ch->m_nJoinInzone_ZoneNo = -1;
		ch->m_nJoinInzone_RoomNo = -1;
		ch->m_nJoinInzone_AreaNo = -1;
	}

	if (bGoto)
	{
		ch->ProcDisconnect(false, (pCurZone == pZone));

		// �������� �̵�

		i = pCurArea - pCurZone->m_area;

		// ���� �ٲ��
		if (pCurZone != pZone)
		{
			// ������ ���� ���̾� �� �̸�
			if (pZone->m_countArea > 1)
			{
				if (pZone->IsGuildRoom())
				{
					if (!ch->m_guildInfo || !(ch->m_guildInfo->guild()))
					{
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsg(rmsg, MSG_SYS_DO_NOT_GO_ZONE_GMORDER);
						SEND_Q(rmsg, ch->m_desc);
						goto RETURN_RESTORE_PARTY_AND_EXPED;
					}

					int idx;
					for (idx=0; idx < pZone->m_countArea; idx++)
					{
						if (!pZone->m_area[idx].m_bEnable)
							continue;

						if (pZone->m_area[idx].m_guildIndex == ch->m_guildInfo->guild()->index())
						{
							i = idx;
							break;
						}
					}

					if (idx == pZone->m_countArea)
					{
						i = pZone->SetEnableArea();
						// �� ���� ����
						if (i == -1)
						{
							CNetMsg::SP rmsg(new CNetMsg);
							SysMsg(rmsg, MSG_SYS_SINGLEDUNGEON_FULL);
							SEND_Q(rmsg, ch->m_desc);
							goto RETURN_RESTORE_PARTY_AND_EXPED;
						}
						pZone->m_area[i].m_guildIndex = ch->m_guildInfo->guild()->index();
					}
				}
				// �޺�����
				else if(pZone->IsComboZone())
				{
					if(pParty)
					{
						int idx;
						for(idx = 0 ; idx < pZone->m_countArea; ++idx)
						{
							if(!pZone->m_area[idx].m_bEnable)
								continue;

							if((pZone->m_area[idx].m_monsterCombo->m_nIndex != -1) &&
									(pZone->m_area[idx].m_monsterCombo->m_nIndex == pParty->m_comboAreaIndex))
							{
								i = idx;
								break;
							}
						}

						// area ����, ���� area ���� ����
						if(idx == pZone->m_countArea)
						{
							// ���常 area ������ �� ����
							if(pParty->GetBossIndex() != ch->m_index)
								goto RETURN_RESTORE_PARTY_AND_EXPED;

							i = pZone->SetEnableArea();
							if(i == -1)
							{
								CNetMsg::SP rmsg(new CNetMsg);
								ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_FULL);
								SEND_Q(rmsg, ch->m_desc);
								goto RETURN_RESTORE_PARTY_AND_EXPED;
							}

							// �޺��� �̼����̽� ����
							if(!pZone->m_area[i].m_monsterCombo->SetMonsterCombo(ch))
								goto RETURN_RESTORE_PARTY_AND_EXPED;

							// ��Ƽ �޺��ε��� ����
							pParty->m_comboAreaIndex = pZone->m_area[i].m_monsterCombo->m_nIndex;

							// ���������� ����
							ch->m_listSaveComboData.clear();
							// �ٸ� ��Ƽ�� ��ȯ
							{
								CNetMsg::SP rmsg(new CNetMsg);
								HelperComboGotoWaitRoomPrompt(rmsg, ch->m_index, (const char*)ch->m_name);
								SEND_Q(rmsg, gserver->m_helper);
							}

							GAMELOG << init("CREATE COMBO AREA", ch)
									<< "AREA INDEX: " << i
									<< "COMBO INDEX: " << pZone->m_area[i].m_monsterCombo->m_nIndex
									<< end;

							{
								CNetMsg::SP rmsg(new CNetMsg);
								HelperCreateComboMsg(rmsg, gserver->m_subno, ch->m_index, i, pZone->m_area[i].m_monsterCombo->m_nIndex);
								SEND_Q(rmsg, gserver->m_helper);
							}
						}
					}
					else
					{
						// ������ �����Ͱ� �ִ��� Ȯ��
						if(ch->m_listSaveComboData.size() < 1)
							goto RETURN_RESTORE_PARTY_AND_EXPED;

						i = pZone->SetEnableArea();
						// �� ���� ����
						if(i == -1)
						{
							CNetMsg::SP rmsg(new CNetMsg);
							ResponseClient::makeMBErrorMsg(rmsg, MSG_EX_MONSTERCOMBO_ERROR_FULL);
							SEND_Q(rmsg, ch->m_desc);
							goto RETURN_RESTORE_PARTY_AND_EXPED;
						}

						// �̼����̽� ����
						if(!pZone->m_area[i].m_monsterCombo->SetMonsterCombo(ch))
							goto RETURN_RESTORE_PARTY_AND_EXPED;

						// �̼����̽� ���� ���� ����
						ch->m_listSaveComboData.clear();

						GAMELOG << init("CREATE COMBO AREA", ch)
								<< "AREA INDEX: " << i
								<< "COMBO INDEX: " << pZone->m_area[i].m_monsterCombo->m_nIndex
								<< end;

						{
							CNetMsg::SP rmsg(new CNetMsg);
							HelperCreateComboMsg(rmsg, gserver->m_subno, ch->m_index, i, pZone->m_area[i].m_monsterCombo->m_nIndex);
							SEND_Q(rmsg, gserver->m_helper);
						}
					}
				}
#ifdef EXTREME_CUBE
				else if(pZone !=NULL && pZone->IsExtremeCube())
				{
					// ������ ���� cube �̸�
					// memlist �� �߰���Ų��.
					// 1. memlist ã��
					CCubeMemList* memlist = NULL;
					if(gserver->m_extremeCube.IsGuildCubeTime())
					{
						if(ch->m_guildInfo && ch->m_guildInfo->guild())
						{
							memlist = gserver->m_extremeCube.FindMemList(ch->m_guildInfo->guild());
						}
					}
					else
					{
						if(pParty)
						{
							memlist = gserver->m_extremeCube.FindMemList(pParty);
						}
					}

					if(!memlist)
					{
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsg(rmsg, MSG_SYS_DO_NOT_GO_ZONE_GMORDER);
						SEND_Q(rmsg, ch->m_desc);

						GAMELOG << init("EXTREME CUBE MOVE ERROR 1", ch);
						goto RETURN_RESTORE_PARTY_AND_EXPED;
					}
					if(!memlist->GetCubeNum(i))
					{
						// ����
						GAMELOG << init("EXTREME CUBE MOVE ERROR 1", ch) << "CUBEIDX" << delim << memlist->GetIndex() << end;
						goto RETURN_RESTORE_PARTY_AND_EXPED;
					}

					memlist->AddPC(ch);
				}
#endif // EXTREME_CUBE

				else if (pZone->m_index == ZONE_ALTER_OF_DARK || pZone->m_index == ZONE_CAPPELLA_1 || pZone->m_index == ZONE_AKAN_TEMPLE
						 || pZone->m_index == ZONE_TARIAN_DUNGEON || pZone->m_index == ZONE_ENCHANTED_DUNGEON
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
#ifndef CLOUD_EXPEDITION_SOLO_DUNGEONS	
						 || pZone->m_index == ZONE_PARTY_DUNGEON0
						 || pZone->m_index == ZONE_PARTY_DUNGEON1
						 || pZone->m_index == ZONE_PARTY_DUNGEON2
						 || pZone->m_index == ZONE_PARTY_DUNGEON3
						 || pZone->m_index == ZONE_PARTY_DUNGEON4
#endif
#endif							
					)
				{
					if(ch->m_nJoinInzone_AreaNo >= 0)
					{
						i = ch->m_nJoinInzone_AreaNo;
					}
					else
					{
						//i = 0;
						// gozone �������� ���̵� ���� �� ����.
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsg(rmsg, MSG_SYS_DO_NOT_GO_ZONE_GMORDER);
						SEND_Q(rmsg, ch->m_desc);
						goto RETURN_RESTORE_PARTY_AND_EXPED;
					}
				}
				else if(pZone->IsWarGroundZone())
				{
					CWaitPlayer* p = NULL;
					p = gserver->m_RoyalRumble.m_WaitPlayerList.GetNode(ch->m_index);
					if(p)
					{
						i = p->GetLevelType();
					}
				}
				else if(pZone->m_index == ZONE_DUNGEON4
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
#ifdef CLOUD_EXPEDITION_SOLO_DUNGEONS
				|| pZone->m_index == ZONE_PARTY_DUNGEON0
				|| pZone->m_index == ZONE_PARTY_DUNGEON1
				|| pZone->m_index == ZONE_PARTY_DUNGEON2
				|| pZone->m_index == ZONE_PARTY_DUNGEON3
				|| pZone->m_index == ZONE_PARTY_DUNGEON4
#endif
#endif				
				)
				{
					int loop;
					for(loop = 0; loop < pZone->m_countArea; loop++)
					{
						if(!pZone->m_area[loop].m_bEnable)
							break;
					}
					if(loop == pZone->m_countArea)
					{
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsg(rmsg, MSG_SYS_SINGLEDUNGEON_FULL);
						SEND_Q(rmsg, ch->m_desc);
						goto RETURN_RESTORE_PARTY_AND_EXPED;
					}
					else
						i = loop;
				}
				else
				{
					i = pZone->SetEnableArea();
					// �� ���� ����
					if (i == -1)
					{
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsg(rmsg, MSG_SYS_SINGLEDUNGEON_FULL);
						SEND_Q(rmsg, ch->m_desc);
						goto RETURN_RESTORE_PARTY_AND_EXPED;
					}
				}
			}
			else
			{
				i= 0;
			}

			// �ٸ� ������ �̵�
			// ĳ���͸� �����÷��� ���·�
			ch->m_bPlaying = false;
			STATE(ch->m_desc) = CON_PREPARE_PLAY;
			bSetPrePlay = true;
		} // �ٸ� ������ �̵�
		else
		{
#ifdef EXTREME_CUBE
			// ���� ������ �̵�
			if(pCurZone !=NULL && pCurZone->IsExtremeCube())
			{
				// �̵��� �Ѵ�.
				CCubeMemList* memlist = NULL;
				if(gserver->m_extremeCube.IsGuildCubeTime())
				{
					if(ch->m_guildInfo && ch->m_guildInfo->guild())
					{
						memlist = gserver->m_extremeCube.FindMemList(ch->m_guildInfo->guild());
					}
				}
				else
				{
					if(ch->m_party)
					{
						memlist = gserver->m_extremeCube.FindMemList(ch->m_party);
					}
				}

				if(!memlist)
				{
					GAMELOG << init("EXTREME CUBE MOVE ERROR 2", ch);
					goto RETURN_RESTORE_PARTY_AND_EXPED;
				}
				if(!memlist->GetCubeNum(i))
				{
					// ����
					GAMELOG << init("EXTREME CUBE MOVE ERROR 2", ch) << "CUBEIDX" << delim << memlist->GetIndex() << end;
					goto RETURN_RESTORE_PARTY_AND_EXPED;
				}

				if( i == ch->m_pArea->m_index )
				{
					if( !memlist->FindPC(ch) )
						memlist->AddPC(ch);
				}
			}
#endif // EXTREME_CUBE
		}

		// ĳ������ ��ġ ����
		ch->m_pZone = pZone;
		if(ch->m_pZone && ch->m_pZone->m_area)
		{
			ch->m_pArea = ch->m_pZone->m_area + i;

			if( pExped && pExped->m_nDifficulty != -1 )
			{
				ch->m_pArea->m_RaidDifficulty = pExped->m_nDifficulty;
			}
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
#ifndef CLOUD_EXPEDITION_SOLO_DUNGEONS	
			if (pParty && pParty->m_nDifficulty != -1)
			{
				ch->m_pArea->m_RaidDifficulty = pParty->m_nDifficulty;
			}
#endif
#ifdef CLOUD_EXPEDITION_SOLO_DUNGEONS
			if (ch && ch->m_nSoloDifficulty != -1)
			{
				ch->m_pArea->m_RaidDifficulty = ch->m_nSoloDifficulty;
				//ch->m_nSoloDifficulty = 0;
			}
#endif
#endif
		}
		else
		{
			goto RETURN_RESTORE_PARTY_AND_EXPED;
		}

		if( !ch->m_pArea )
			goto RETURN_RESTORE_PARTY_AND_EXPED;
		// ���̵� �����̸� SetEnable�� ���� ����� �Ѵ�.
		if (pZone->m_index == ZONE_ALTER_OF_DARK || pZone->m_index == ZONE_CAPPELLA_1 || pZone->m_index == ZONE_AKAN_TEMPLE
				|| pZone->m_index == ZONE_TARIAN_DUNGEON || pZone->m_index == ZONE_ENCHANTED_DUNGEON
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS	
#ifndef CLOUD_EXPEDITION_SOLO_DUNGEONS	
			|| pZone->m_index == ZONE_PARTY_DUNGEON0
			|| pZone->m_index == ZONE_PARTY_DUNGEON1
			|| pZone->m_index == ZONE_PARTY_DUNGEON2
			|| pZone->m_index == ZONE_PARTY_DUNGEON3
			|| pZone->m_index == ZONE_PARTY_DUNGEON4
#endif
#endif			   
			)
		{
			// ĳ���Ͱ� �� area�� �ƹ��� ���� ���� �ʱ�ȭ
			ch->m_pArea->m_inCount++;

			//�̵��� ������ bInCount �� true�� �Ǿ�� ������ �̵��� �Ϸ�� ���°� ��
			ch->bMoveInsDunFinish = false;
			if (ch->m_pArea->GetAllClientCount_Area() < 1)
			{
				ch->m_pArea->SetEnable(ch->m_nJoinInzone_RoomNo, ch->m_pArea->m_RaidDifficulty);
				if(pZone->m_index == ZONE_AKAN_TEMPLE)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					RaidSceneMsg(rmsg, OBJECT_TYPE_TODO, START_RAID, 1, -1);
					do_ExRaidScene(ch, rmsg);
				}
				if(pZone->m_index == ZONE_TARIAN_DUNGEON)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					RaidSceneMsg(rmsg, OBJECT_TYPE_TODO, START_RAID, 1, -1);
					do_ExRaidScene(ch, rmsg);
				}
				if (pZone->m_index == ZONE_ENCHANTED_DUNGEON)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					RaidSceneMsg(rmsg, OBJECT_TYPE_TODO, START_RAID, 1, -1);
					do_ExRaidScene(ch, rmsg);
				}
				
			}
		}
		else if(pZone->m_index == ZONE_DUNGEON4
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS	
#ifdef CLOUD_EXPEDITION_SOLO_DUNGEONS	
			|| pZone->m_index == ZONE_PARTY_DUNGEON0
			|| pZone->m_index == ZONE_PARTY_DUNGEON1
			|| pZone->m_index == ZONE_PARTY_DUNGEON2
			|| pZone->m_index == ZONE_PARTY_DUNGEON3
			|| pZone->m_index == ZONE_PARTY_DUNGEON4
#endif
#endif					
			)
		{
			{
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_EXTEND);
				RefMsg(rmsg) << MSG_EX_PARTY_MATCH
							 << MSG_EX_PARTY_MATCH_DEL_REQ;
				do_Extend(ch, rmsg);
			}

			if(ch->m_pArea->GetAllClientCount_Area() < 1)
			{
				if (pZone->m_index == ZONE_DUNGEON4)
				{
					ch->m_pArea->m_RaidDifficulty = DUNGEON_DIFFICULTY_NORMAL;
					ch->m_pArea->SetEnable(i, DUNGEON_DIFFICULTY_NORMAL);
				}
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
				else
				{
					ch->m_pArea->m_RaidDifficulty = ch->m_nSoloDifficulty;
					ch->m_pArea->SetEnable(i, ch->m_nSoloDifficulty);
				}
#endif
				CNetMsg::SP rmsg(new CNetMsg);
				RaidSceneMsg(rmsg, OBJECT_TYPE_TODO, START_RAID, 1, -1);
				do_ExRaidScene(ch, rmsg);
			}
		}

		GET_YLAYER(ch)	= ylayer;
		GET_R(ch)		= 0.0f;
		GET_X(ch)		= x;
		GET_Z(ch)		= z;

		{
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeGoMsg(rmsg, ch);
			SEND_Q(rmsg, ch->m_desc);
		}

		if( ch->m_guildInfo && ch->m_guildInfo->guild() )
		{
			ch->m_guildInfo->zoneindex( pZone->m_index );
		}

		if (!bSetPrePlay)
		{
			int cx, cz;

			while (ch->m_elementalList)
				ch->UnsummonElemental(ch->m_elementalList);

			ch->ResetPlayerState(PLAYER_STATE_SITDOWN);

			ch->m_pArea->PointToCellNum(GET_X(ch), GET_Z(ch), &cx, &cz);
			ch->m_pArea->CharToCell(ch, GET_YLAYER(ch), cx, cz);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, ch, true);
				ch->m_pArea->SendToCell(rmsg, ch);
			}

			if(ch->holy_water_item != NULL)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				UpdateClient::holyWaterStateMsg(rmsg, ch->m_index, ch->holy_water_item->getDBIndex());
				ch->m_pArea->SendToCell(rmsg, ch, true);
			}

			{
				std::map<int, MAKE_TITLE*>::iterator it = ch->_map_title.find(ch->m_custom_title_index);
				if(it != ch->_map_title.end())
				{
					CNetMsg::SP rmsg(new CNetMsg);
					TitleUserInfoMsg(rmsg, ch->m_index, it->second->color, it->second->background_color, it->second->effect, it->second->name);
					ch->m_pArea->SendToCell(rmsg, ch, true);
				}
			}

			ch->m_pArea->SendCellInfo(ch, true);
			if( ch->m_guildInfo && ch->m_guildInfo->guild() )
			{
				CNetMsg::SP rmsg(new CNetMsg);
				GuildPointRankingMsg( rmsg, ch->m_index, ch->m_guildInfo->guild()->index(), ch->m_guildInfo->guild()->GetGuildPointRanking() );
				ch->m_pArea->SendToCell( rmsg, ch );
			}

			{
				CNetMsg::SP rmsg(new CNetMsg);
				GuildNameColorStateMsg(rmsg, ch );
				ch->m_pArea->SendToCell( rmsg, ch, true );
			}

			if (IS_PC(ch))
			{
				CPC* pc = TO_PC(ch);
				CPet* pet = pc->GetPet();
				if (pet && pet->IsSummon())
				{
					GoTo(pet, GET_YLAYER(ch), x, z, ch->m_pArea->GetHeight(GET_YLAYER(ch), x, z), GET_R(pet));
				}
			}

			if (IS_PC(ch))
			{
				CPC* pc = TO_PC(ch);
				CElemental* elemental = pc->m_elementalList;
				while (elemental)
				{
					GoTo(elemental, GET_YLAYER(ch), x, z, ch->m_pArea->GetHeight(GET_YLAYER(ch), x, z), GET_R(elemental));
					elemental = elemental->m_nextElemental;
				}
			}

			if (IS_PC(ch))
			{
				CPC* pc = TO_PC(ch);
				CAPet* apet = pc->GetAPet();
				if (apet && apet->IsSummon())
				{
					GoTo(apet, GET_YLAYER(ch), x, z, ch->m_pArea->GetHeight(GET_YLAYER(ch), x, z), GET_R(apet));
				}
			}
		}

		if (!DEAD(ch))
		{
			// GO_ZONE ȿ�� �޽��� ����
			CNetMsg::SP rmsg(new CNetMsg);
			EffectEtcMsg(rmsg, ch, MSG_EFFECT_ETC_GOZONE);
			ch->m_pArea->SendToCell(rmsg, ch, true);
		}

		if (ch->m_admin < 2)
		{
			switch (zone)
			{
			case ZONE_SINGLE_DUNGEON3:
				ch->m_pd3Count++;

				if(ch->m_pd3Count == 1 || ch->m_pd3Count > 6)
				{
					time_t now;
					time(&now);
					ch->m_pd3Time = now;
				}
				break;
			case ZONE_SINGLE_DUNGEON4:
				ch->m_pd4Count++;
				if(ch->m_pd4Count == 1 || ch->m_pd4Count > 4)
				{
					time_t now;
					time(&now);
					ch->m_pd4Time = now;
				}
				break;
			}
		}
//#endif

		ch->m_bChangeStatus = true;

		CWarCastle * castle = CWarCastle::GetCastleObject(pZone->m_index);
		if( castle && castle->GetState() != WCSF_NORMAL && !(ch->m_pArea->GetAttr(ylayer, x, z) == MATT_WAR && ch->GetJoinFlag(pZone->m_index) & WCJF_NONE) )
			ch->ApplyGuildGradeSkill();
		else
			ch->CureGuildGradeSkill();

		//���� �����ڰ� �̵��ϴ� ��� üũ
		if(ArtifactManager::instance()->isOwnerPC(ch->m_index))
		{
			ch->CalcStatus(true);

			if(ch->m_party != NULL)
			{
				ch->m_party->updateCalcMember();
			}
		}
		else if(ch->m_party != NULL
			&& ArtifactManager::instance()->isArtifactParty(ch->m_party) == true)
		{
			ch->CalcStatus(true);
		}

		// ���̵��� PK��� üũ
		if (ch->IsSetPlayerState(PLAYER_STATE_PKMODE) == false)
		{
			// PK��尡 �ƴ� ���
			return true;
		}

		bool bPKState = false;

		// ���� üũ
		castle = CWarCastle::GetCastleObject(ch->m_pZone->m_index);
		if (castle)
		{
			if (castle->GetState() != WCSF_NORMAL)
			{
				if ( ch->GetMapAttr() & MATT_WAR)
				{
					bPKState = true;
				}
			}
		}

		if (ch->IsInPeaceZone(false) == false)
		{
			// PK��
			if (ch->GetMapAttr() & MATT_FREEPKZONE)
			{
				bPKState = true;
			}
		}

		if (bPKState == false)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ch->ResetPlayerState(PLAYER_STATE_PKMODE | PLAYER_STATE_PKMODEDELAY);
			ResponseClient::makeAction(rmsg, ch, 0, AGT_PKMODE);
			SEND_Q(rmsg, ch->m_desc);
		}
	}
	else
	{
		// ���� �ܺη� �̵� ó��

		// �� �̵� �޽��� ����
		ResponseClient::makeGoZone(ch->m_desc->m_msgGoZone, pZone->m_index, 0,
								   pZone->m_remoteIP, pZone->m_remotePort);
//#ifdef GER_LOG
//		GAMELOGGEM << init( 0, "CHAR_ZONE_TRANSITION")
//			<< LOG_VAL("account-id", ch->m_desc->m_idname ) << blank
//			<< LOG_VAL("character-id", ch->m_desc->m_pChar->m_name ) << blank
//			<< LOG_VAL("dest-zone-id", pZone->m_index ) << blank
//			<< LOG_VAL("src-zone-id", ch->m_desc->m_pChar->m_pZone->m_index ) << blank
//			<< LOG_VAL("first-time","0") << blank
//			<< LOG_VAL("level", ch->m_level ) << blank
//			<< endGer;
//#endif // GER_LOG
		// ��ǥ ����
		ch->m_pZone = pZone;
		ch->m_pArea = NULL;
		GET_YLAYER(ch)	= ylayer;
		GET_X(ch)		= x;
		GET_Z(ch)		= z;
		ch->m_desc->m_bGoZone = true;
		ch->m_desc->m_bGoZoneSent = false;
		ch->m_desc->Close("GoZone - CHAR_ZONE_TRANSITION");
		return true; // gozone ����
	}

	return true; // ���д� �����̴� ��

RETURN_RESTORE_PARTY_AND_EXPED:

	// ���̵��� �ϸ� ��Ƽ���� ���ܽ�Ű�µ� ���̵� ���н� �ٽ� ��Ƽ�� ���� �����ִ� �Լ�
	if(pParty)
	{
		pParty->SetMemberRegister_AfterGoZone(ch);
		ch->m_party = pParty;
		if(ch->m_party)
		{
			ch->m_party->m_nRaidAreaNum = nTempRaidAreaNum;
		}
	}
	else if(pExped)
	{
		pExped->SetMemberRegister_AfterGoZone(ch);
		ch->m_Exped = pExped;
		if(ch->m_Exped)
			ch->m_Exped->m_nRaidAreaNum = nTempRaidAreaNum;
	}
#ifdef LC_GAMIGO
	GAMELOG << init("GO ZONE FAILED", ch) << zone << end;
#endif // LC_GAMIGO

	if(ch->m_pArea != NULL)
	{
		int cx, cz;
		ch->m_pArea->PointToCellNum(GET_X(ch), GET_Z(ch), &cx, &cz);
		ch->m_pArea->CharToCell(ch, GET_YLAYER(ch), cx, cz);

		ch->m_pArea->SendCellInfo(ch, true);

		{
			CNetMsg::SP rmsg(new CNetMsg);
			AppearMsg(rmsg, ch, true);
			ch->m_pArea->SendToCell(rmsg, ch);
		}

		CAPet* apet = ch->GetAPet();
		CPet* pet = ch->GetPet();

		if(apet != NULL)
		{
			apet->Appear(true, false);
		}		
		else if(pet != NULL)
		{
			pet->Appear(true);
		}
	}
	
	return false;
}

void GoTo(CCharacter* ch, char y, float x, float z, float h, float r, char bHack)
{
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if (IS_PC(ch))
	{
		pCastle->CheckRespond(TO_PC(ch));
	}

	// ���ȿ� �˸���
	ch->SendDisappearAllInCell(true);

	// ������ ����
	ch->m_pArea->CharFromCell(ch, true);

	if(IS_APET(ch))
	{
		CAPet* apet = TO_APET(ch);
		CPC* ower = apet->GetOwner();
		if(ower)
			apet->m_pArea = ower->m_pArea;
	}

	// �̵�
	ch->Move(x, z, h, r, y);

	// ���� �ְ�
	int cx, cz;
	ch->m_pArea->PointToCellNum(x, z, &cx, &cz);
	ch->m_pArea->CharToCell(ch, y, cx, cz);

	if (IS_PC(ch))
	{
		TO_PC(ch)->SummonNpcRemoveAll(true);

		// ���� ��ų ���� ���
		if( ch->m_currentSkill != NULL )
		{
			ch->m_currentSkill->Cancel(ch);
			ch->m_currentSkill = NULL;
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeSkillCancelMsg(rmsg, ch);
			ch->m_pArea->SendToCell(rmsg, ch, true);
		}

		CPC* pc = TO_PC(ch);
		pc->ResetPlayerState(PLAYER_STATE_SITDOWN);

		{
			// �̵� ��� �˸���
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeGoMsg(rmsg, pc, bHack);
			SEND_Q(rmsg, pc->m_desc);
		}
		// �� ���� ������
		pc->m_pArea->SendCellInfo(pc, true);

		CWarCastle * castle = CWarCastle::GetCastleObject(ch->m_pZone->m_index);
		if( castle && castle->GetState() != WCSF_NORMAL && ch->GetMapAttr() & MATT_WAR
				&& TO_PC(ch)->GetJoinFlag(ch->m_pZone->m_index) != WCJF_NONE )
			TO_PC(ch)->ApplyGuildGradeSkill();
		else
			TO_PC(ch)->CureGuildGradeSkill();

		{
			CNetMsg::SP rmsg(new CNetMsg);
			CharStatusMsg(rmsg, ch, 0);
			SEND_Q(rmsg, pc->m_desc);
		}
	}

	// ��Ÿ���� �� �˸���
	if (IS_PC(ch))
	{
		{
			CNetMsg::SP rmsg(new CNetMsg);
			AppearMsg(rmsg, ch, false);
			ch->m_pArea->SendToCell(rmsg, ch);
		}

		CPC* pc = TO_PC(ch);
		if( pc->m_guildInfo )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			GuildPointRankingMsg( rmsg, pc->m_index, pc->m_guildInfo->guild()->index(), pc->m_guildInfo->guild()->GetGuildPointRanking() );
			ch->m_pArea->SendToCell( rmsg, ch );
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			GuildNameColorStateMsg(rmsg, TO_PC(ch) );
			ch->m_pArea->SendToCell( rmsg, TO_PC(ch) );
		}

		{
			std::map<int, MAKE_TITLE*>::iterator it = pc->_map_title.find(pc->m_custom_title_index);
			if(it != pc->_map_title.end())
			{
				CNetMsg::SP rmsg(new CNetMsg);
				TitleUserInfoMsg(rmsg, pc->m_index, it->second->color, it->second->background_color, it->second->effect, it->second->name);
				pc->m_pArea->SendToCell(rmsg, pc, true);
			}
		}
	}
	else
	{
		CNetMsg::SP rmsg(new CNetMsg);
		AppearMsg(rmsg, ch, false);
		ch->m_pArea->SendToCell(rmsg, ch, true);
	}

	CPet* pet = NULL;
	if (IS_PC(ch))
	{
		CPC* pc = TO_PC(ch);
		pet = pc->GetPet();
		if (pet && pet->IsSummon())
		{
			GoTo(pet, y, x, z, h, r);
		}
	}

	if (IS_PC(ch))
	{
		CElemental* elemental = NULL;
		CPC* pc = TO_PC(ch);
		elemental = pc->m_elementalList;
		while (elemental)
		{
			GoTo(elemental, y, x, z, h, r);
			elemental = elemental->m_nextElemental;
		}
	}

	CAPet* apet = NULL;
	if (IS_PC(ch))
	{
		CPC* pc = TO_PC(ch);
		apet = pc->GetAPet();
		if (apet && apet->IsSummon())
		{
			GoTo(apet, y, x, z, h, r);
		}
	}

	if ( IS_APET(ch) )
	{
		apet = TO_APET(ch);

		{
			CNetMsg::SP rmsg(new CNetMsg);
			ExAPetStatusMsg( rmsg, apet );
			SEND_Q( rmsg, apet->GetOwner()->m_desc );
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			APetAIOnOffMsg(rmsg, apet, MSG_APET_ERROR_OK);
			SEND_Q(rmsg, apet->GetOwner()->m_desc);
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			APetAIListMsg(rmsg, apet);
			SEND_Q(rmsg, apet->GetOwner()->m_desc);
		}
	}
}

void GoZoneForceBase(CPC* ch, int zone, char ylayer, float x, float z, const char* fname, const int line)
{
	LOG_INFO("GoZoneForce > %s : %s : %s : DEST : %d LAYER : %d FILE : %s LINE : %d",
			 (const char*)ch->m_name, (const char *)ch->m_nick, (const char *)ch->m_desc->m_idname,
			 zone, ylayer, fname, line);

	if (DEAD(ch))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_PC_REBIRTH);
		do_Rebirth(ch, rmsg);
	}

	if (ch->IsSetPlayerState(PLAYER_STATE_SITDOWN))
	{
		ch->TogglePlayerState(PLAYER_STATE_SITDOWN);
		ch->CalcStatus(true);
	}

	if (ch->m_currentSkill)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeSkillCancelMsg(rmsg, ch);
		ch->m_pArea->SendToCell(rmsg, ch, true);
		ch->m_currentSkill->Cancel(ch);
		ch->m_currentSkill = NULL;
	}

	if (ch->m_exchange)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ExchangeReqMsg(rmsg, MSG_EXCHANGE_REQ_REJECT, NULL, NULL);
		do_Exchange(ch, rmsg);
	}

	// ��Ƽ ��û ���̸� �����Ѵ�.
	if (ch->m_party != NULL)
	{
		// �ʴ��ϰų�, �ʴ���� ����� ��� ������ ó��
		if (ch->m_party->GetRequestIndex() > 0 && (ch->m_party->GetBossIndex() == ch->m_index || ch->m_party->GetRequestIndex() == ch->m_index))
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PartyMsg(rmsg, MSG_PARTY_REJECT);
			do_Party(ch, rmsg);
		}
		ch->m_party->SetMemberPCPtr(ch->m_index, NULL);
		ch->m_party = NULL;
	}

	GoZone(ch, zone, ylayer, x, z);
}

void GMGoZone(CPC* ch, CPC* pc)
{
	_GMGoZone(ch, pc);

	if( ch->m_desc->m_connected == CON_PREPARE_PLAY )
	{
		ch->m_targetPC = NULL;
		ch->m_desc->m_connected = CON_PREPARE_PLAY_BEFORE;
	}
}

bool _GMGoZone(CPC* ch, CPC* pc)
{
	int zone = pc->m_pZone->m_index;
	char ylayer = pc->m_pos.m_yLayer;
	float x = pc->m_pos.m_x;
	float z = pc->m_pos.m_z;

	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	pCastle->CheckRespond(ch);

	if( ch->CanWarp() )
		return false;

	switch(zone)
	{
	case ZONE_SINGLE_DUNGEON3:
	case ZONE_SINGLE_DUNGEON4:
		if( ch->m_admin < 2 && !ch->CheckDungeonData(zone) )
		{
			GAMELOG << init("PD_BUG_GO_ZONE", ch)
					<< end;
			return false;
		}
	default:
		break;
	}

	bool bGoto = false;
	bool bValid = false;
	CZone* pZone = NULL;

	CParty* pParty = NULL;

	int i = 0;
	if (ch->m_pZone->m_index == zone)
	{
		// ���� ���ȿ����� �̵�
		bGoto = true;
		bValid = true;
		pZone = ch->m_pZone;
	}
	else
	{
		pZone = gserver->FindZone(zone);
		if (pZone == NULL || pZone->m_area == NULL)
			return false;

		if (pZone->m_bRemote)
		{
			// �ܺ� ������ �ν��Ͻ� ������ �Ұ���
			if (!pZone->IsGuildRoom() && !pZone->IsPersonalDungeon())
			{
				bGoto = false;
				bValid = true;
			}
		}
		else
		{
			bGoto = true;
			bValid = true;
		}
	}

	if (!bValid)
	{
		// ����
		return false;
	}

	CZone* pCurZone = ch->m_pZone;
	CArea* pCurArea = ch->m_pArea;

	// ���� �ٲ��
	if (pCurZone != pZone)
	{
		// ��Ƽ ó��
		if (ch->m_party != NULL)
		{
			// �ʴ��ϰų�, �ʴ���� ����� ��� ������ ó��
			if (ch->m_party->GetRequestIndex() > 0 && (ch->m_party->GetBossIndex() == ch->m_index || ch->m_party->GetRequestIndex() == ch->m_index))
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PartyMsg(rmsg, MSG_PARTY_REJECT);
				do_Party(ch, rmsg);
			}
			// ������ �۴��̸� ��ƼŻ��
			else if (pZone->IsPersonalDungeon()
					 || pZone->IsWarGroundZone()
					 || pZone->IsPersonalRaid()
					)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PartyMsg(rmsg, MSG_PARTY_QUIT);
				do_Party(ch, rmsg);
			}
			else if (pZone->isRVRZone())
			{
				// �ٸ� ��Ƽ����� ���밡 �ٸ��ٸ� ��Ƽ Ż��
				for (int i = 0; i < MAX_PARTY_MEMBER; ++i)
				{
					if (	ch->m_party->m_listMember[i] != NULL
							&&	ch->m_party->m_listMember[i]->GetCharIndex() != ch->m_index
							&&	ch->m_party->m_listMember[i]->GetMemberPCPtr()->getSyndicateType() != ch->getSyndicateType()
					   )
					{
						CNetMsg::SP rmsg(new CNetMsg);
						PartyMsg(rmsg, MSG_PARTY_QUIT);
						do_Party(ch, rmsg);
						break;
					}
				}
			}
#if defined (EXTREME_CUBE)
			if(ch->IsParty())
			{
				pParty = ch->m_party;
			}
#endif

			ch->m_party->SetMemberPCPtr(ch->m_index, NULL);
			ch->m_party = NULL;
		}

		// ������ ó��
		if (ch->IsExped())
		{
			if (ch->m_Exped->GetRequestIndex() > 0 && (ch->m_Exped->GetBossIndex() == ch->m_index || ch->m_Exped->GetRequestIndex() == ch->m_index))
			{
				// �ʴ� �ź�
				CNetMsg::SP rmsg(new CNetMsg);
				ExpedRejectReqMsg(rmsg);
				do_Expedition(ch, rmsg);
			}
			// ������ �۴��̸� ������ Ż��
			else if (pZone->IsPersonalDungeon()
					 || pZone->IsWarGroundZone()
					 || pZone->IsPersonalRaid()
					)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ExpedQuitReqMsg(rmsg, 0);
				do_Expedition(ch, rmsg);
			}
			else if (pZone->isRVRZone())
			{
				// �ٸ� ���̵������ ���밡 �ٸ��ٸ� ���̵� Ż��
				for (int i = 0; i < MAX_EXPED_GROUP; ++i)
				{
					for (int j = 0; j < MAX_EXPED_GMEMBER; ++j)
					{
						CPC* pExpedMember = ch->m_Exped->GetMemberPCPtr(i, j);
						if (	pExpedMember != NULL &&	pExpedMember->m_index != ch->m_index
								&&	pExpedMember->getSyndicateType() != ch->getSyndicateType()
						   )
						{
							CNetMsg::SP rmsg(new CNetMsg);
							ExpedQuitReqMsg(rmsg, 0);
							do_Expedition(ch, rmsg);
						}
					}
				}
			}

			/*CExpedition* pExped = ch->m_Exped;*/

			ch->m_Exped->SetMemberPCPtr(ch->m_index, NULL);
			ch->m_Exped = NULL;
		}
	} // ���� �ٲ��

	bool bSetPrePlay = false;
	if (bGoto)
	{
		ch->ProcDisconnect(false, (pCurZone == pZone));

		// �������� �̵�

		i = pCurArea - pCurZone->m_area;

		// ������ ���� ���̾� �� �̸�
		if (pZone->m_countArea > 1)
		{
			if(pc->m_pArea->m_bEnable)
				i = pc->m_pArea->m_index;
			else
				return false;
		}
		else
			i= 0;

		// ���� �ٲ��
		if (pCurZone != pZone)
		{
			// �ٸ� ������ �̵�
			// ĳ���͸� �����÷��� ���·�
			ch->m_bPlaying = false;
			STATE(ch->m_desc) = CON_PREPARE_PLAY;
			bSetPrePlay = true;
		} // �ٸ� ������ �̵�

		// ĳ������ ��ġ ����
		ch->m_pZone = pZone;
		ch->m_pArea = ch->m_pZone->m_area + i;

		GET_YLAYER(ch)	= ylayer;
		GET_R(ch)		= 0.0f;
		GET_X(ch)		= x;
		GET_Z(ch)		= z;

		{
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeGoMsg(rmsg, ch);
			SEND_Q(rmsg, ch->m_desc);
		}

		switch(zone)
		{
		case ZONE_SINGLE_DUNGEON1:
		case ZONE_SINGLE_DUNGEON2:
		case ZONE_SINGLE_DUNGEON_TUTORIAL:
		case ZONE_SINGLE_DUNGEON3:
		case ZONE_SINGLE_DUNGEON4:
			return false;
		case ZONE_COMBO_DUNGEON:
			ch->m_gmGoZoneType = GM_GOZONE_COMBO;
			break;
		default:
			ch->m_gmGoZoneType = GM_GOZONE_NONE;
			break;
		}

		if( ch->m_guildInfo && ch->m_guildInfo->guild() )
		{
			ch->m_guildInfo->zoneindex( pZone->m_index );
		}

		if (!bSetPrePlay)
		{
			int cx, cz;
			ch->m_pArea->PointToCellNum(GET_X(ch), GET_Z(ch), &cx, &cz);
			ch->m_pArea->CharToCell(ch, GET_YLAYER(ch), cx, cz);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, ch, true);
				ch->m_pArea->SendToCell(rmsg, ch);
			}

			ch->m_pArea->SendCellInfo(ch, true);
			if( ch->m_guildInfo && ch->m_guildInfo->guild() )
			{
				CNetMsg::SP rmsg(new CNetMsg);
				GuildPointRankingMsg( rmsg, ch->m_index, ch->m_guildInfo->guild()->index(), ch->m_guildInfo->guild()->GetGuildPointRanking() );
				ch->m_pArea->SendToCell( rmsg, ch );
			}

			{
				CNetMsg::SP rmsg(new CNetMsg);
				GuildNameColorStateMsg(rmsg, ch );
				ch->m_pArea->SendToCell( rmsg, ch );
			}

			if (IS_PC(ch))
			{
				CPC* pc = TO_PC(ch);
				CPet* pet = pc->GetPet();
				if (pet && pet->IsSummon())
				{
					GoTo(pet, GET_YLAYER(ch), x, z, ch->m_pArea->GetHeight(GET_YLAYER(ch), x, z), GET_R(pet));
				}
			}

			if (IS_PC(ch))
			{
				CPC* pc = TO_PC(ch);
				CElemental* elemental = pc->m_elementalList;
				while (elemental)
				{
					GoTo(elemental, GET_YLAYER(ch), x, z, ch->m_pArea->GetHeight(GET_YLAYER(ch), x, z), GET_R(elemental));
					elemental = elemental->m_nextElemental;
				}
			}

			if (IS_PC(ch))
			{
				CPC* pc = TO_PC(ch);
				CAPet* apet = pc->GetAPet();
				if (apet && apet->IsSummon())
				{
					GoTo(apet, GET_YLAYER(ch), x, z, ch->m_pArea->GetHeight(GET_YLAYER(ch), x, z), GET_R(apet));
				}
			}
		}

		if (!DEAD(ch))
		{
			// GO_ZONE ȿ�� �޽��� ����
			CNetMsg::SP rmsg(new CNetMsg);
			EffectEtcMsg(rmsg, ch, MSG_EFFECT_ETC_GOZONE);
			ch->m_pArea->SendToCell(rmsg, ch, true);
		}

		if (ch->m_admin < 2)
		{
			switch (zone)
			{
			case ZONE_SINGLE_DUNGEON3:
				ch->m_pd3Count++;

				if(ch->m_pd3Count == 1 || ch->m_pd3Count > 6)
				{
					time_t now;
					time(&now);
					ch->m_pd3Time = now;
				}
				break;
			case ZONE_SINGLE_DUNGEON4:
				ch->m_pd4Count++;
				if(ch->m_pd4Count == 1 || ch->m_pd4Count > 4)
				{
					time_t now;
					time(&now);
					ch->m_pd4Time = now;
				}
				break;
			}
		}
//#endif

		ch->m_bChangeStatus = true;

// 		// ���̵��� PK��� üũ
// 		if (ch->IsSetPlayerState(PLAYER_STATE_PKMODE) == false)
// 		{
// 			// PK��尡 �ƴ� ���
// 			return false;
// 		}

		bool bPKState = false;

		// ���� üũ
		CWarCastle * castle = CWarCastle::GetCastleObject(ch->m_pZone->m_index);
		if (castle)
		{
			if (castle->GetState() != WCSF_NORMAL)
			{
				if ( ch->GetMapAttr() & MATT_WAR)
				{
					bPKState = true;
				}
			}
		}

		if (ch->IsInPeaceZone(false) == false)
		{
			// PK��
			if (ch->GetMapAttr() & MATT_FREEPKZONE)
			{
				bPKState = true;
			}
		}

		if (bPKState == false)
		{
			ch->ResetPlayerState(PLAYER_STATE_PKMODE | PLAYER_STATE_PKMODEDELAY);
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeAction(rmsg, ch, 0, AGT_PKMODE);
			SEND_Q(rmsg, ch->m_desc);
		}
	}
	else
	{
		// ���� �ܺη� �̵� ó��

		// �� �̵� �޽��� ����
		ResponseClient::makeGoZone(ch->m_desc->m_msgGoZone, pZone->m_index, 0,
								   pZone->m_remoteIP, pZone->m_remotePort);
//#ifdef GER_LOG
//		GAMELOGGEM << init( 0, "CHAR_ZONE_TRANSITION")
//			<< LOG_VAL("account-id", ch->m_desc->m_idname ) << blank
//			<< LOG_VAL("character-id", ch->m_desc->m_pChar->m_name ) << blank
//			<< LOG_VAL("dest-zone-id", pZone->m_index ) << blank
//			<< LOG_VAL("src-zone-id", ch->m_desc->m_pChar->m_pZone->m_index ) << blank
//			<< LOG_VAL("first-time","0") << blank
//			<< LOG_VAL("level", ch->m_level ) << blank
//			<< endGer;
//#endif // GER_LOG
		// ��ǥ ����
		ch->m_pZone = pZone;
		ch->m_pArea = NULL;
		GET_YLAYER(ch)	= ylayer;
		GET_X(ch)		= x;
		GET_Z(ch)		= z;
		ch->m_desc->m_bGoZone = true;
		ch->m_desc->m_bGoZoneSent = false;
		ch->m_desc->Close("GMGoZone - CHAR_ZONE_TRANSITION");
	}

	return true;
}
