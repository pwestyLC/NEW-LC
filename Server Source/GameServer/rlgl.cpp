#include "stdhdrs.h"
#include "CmdMsg.h"
#include "rlgl.h"
#include "Area.h"
#include <vector>
#include "../ShareLib/packetType/ptype_old_do_move.h"
#include "../ShareLib/DBCmd.h"
#include "DBManager.h"


#define IMOVESTART   (m_ieventstart + (60))
#define IRACESTART (IMOVESTART + (10))
#define IRACEEND   (IRACESTART + (60 * 2))


struct Player {
	CPC* pc;
};

bool comparePosition(const Player& player1, const Player& player2) {
	return player1.pc->m_pos.m_z < player2.pc->m_pos.m_z;
}

void  RLGL::RLGLMSG(CNetMsg::SP& msg) {
	msg->Init(MSG_REZA);
	RefMsg(msg) << ((int)REZA_RLGL);
}

void RLGL::do_RLGL(CPC* ch, CNetMsg::SP& msg)
{
	msg->MoveFirst();
	unsigned int op;
	unsigned int subtype;
	RefMsg(msg) >> op >> subtype;

	switch (subtype)
	{
	case MSG_RLGL_OPEN :
	{
		CNetMsg::SP rmsg(new CNetMsg); 
		RLGLMSG(rmsg);
		RefMsg(rmsg) << ((int)MSG_RLGL_OPEN);
		RefMsg(rmsg) << ((int)ch->m_admin);
	  
		SEND_Q(rmsg, ch->m_desc);
	}
	break;
	case MSG_RLGL_CLOSE:
	{
	}
	break;
	case MSG_RLGL_STARTLINE:
	{
	}
	break;
	case MSG_RLGL_FINISHLINE:
	{
	}
	break;
	case MSG_RLGL_LIGHT:
	{
	}
	break;
	case MSG_RLGL_STARTZONEPROMPT:
	{
	}
	break;
	case MSG_RLGL_GM:
	{
		int sub = 0; 
		RefMsg(msg) >> sub; 
		RLGLMENU(ch,sub);
	}
	break;
	default:
	{ 
		//ch->m_desc->Close(" "); 
	}
	return;

	}

}


RLGL::RLGL()
{

	m_bevent_on = false;

	m_placement = 0;
	m_lightstizzle = ls_green;
	m_nextfiretime = 0;
	m_lastfiretime = 0;

	 m_ieventstart = 0;//imovewait
	 m_bmovewait = false;
	 m_bmovestart = false;
	 m_bracestart = false;
	 m_braceend = false;

	  alive = 0 ;
	  eliminated = 0;
	  placeone = "";
	  placetwo ="";
	  placetree =""; 

}

RLGL::~RLGL()
{
	 
 

}

bool RLGL::LoadRLGL()
{
	
	return true;
}
void RLGL::ReloadRLGL()
{
	LoadRLGL();

}

void RLGL::SendMenu(CPC* ch, int gm) {

	CNetMsg::SP rmsg(new CNetMsg);
	RLGLMSG(rmsg);
	RefMsg(rmsg) << ((int)MSG_RLGL_OPEN);
	RefMsg(rmsg) << ((int)gm);

	SEND_Q(rmsg, ch->m_desc);

}

void RLGL::SendMenuTab(CPC* ch, int tab) {

	CNetMsg::SP rmsg(new CNetMsg);
	RLGLMSG(rmsg);
	RefMsg(rmsg) << ((int)MSG_RLGL_TAB);
	RefMsg(rmsg) << ((int)tab);

	SEND_Q(rmsg, ch->m_desc);

}

void RLGL::SendTimer(CPC* ch, int time) {

	CNetMsg::SP rmsg2(new CNetMsg);
	RLGLMSG(rmsg2);
	RefMsg(rmsg2) << ((int)MSG_RLGL_GM);
	RefMsg(rmsg2) << ((int)MSG_RLGL_GM_TIME);
	RefMsg(rmsg2) << ((int)time);

	SEND_Q(rmsg2, ch->m_desc);
}

void RLGL::RLGLMENU(CPC* ch , int sub) {


	if (sub < 0 || sub >= MSG_RLGL_GM_END)
		ch->m_desc->Close("gm menu rlgl fail check");


	switch (sub)
	{
	case MSG_RLGL_GM_OPENGATE1:
	{
		CNetMsg::SP rmsg(new CNetMsg);
		RLGLMSG(rmsg);
		RefMsg(rmsg) << ((int)MSG_RLGL_STARTLINE);
		RefMsg(rmsg) << ((int)ch->m_pZone->m_index); // zone
		RefMsg(rmsg) << ((int)7263); // barrier
		RefMsg(rmsg) << ((int)7272); // forcefield

		SEND_Q(rmsg, ch->m_desc);
		
	}
	break;
	case MSG_RLGL_GM_CLOSEGATE1:
	{
		CNetMsg::SP rmsg(new CNetMsg);
		RLGLMSG(rmsg);
		RefMsg(rmsg) << ((int)MSG_RLGL_FINISHLINE);
		RefMsg(rmsg) << ((int)ch->m_pZone->m_index); // zone
		RefMsg(rmsg) << ((int)7263); // barrier
		RefMsg(rmsg) << ((int)7272); // forcefield


		SEND_Q(rmsg, ch->m_desc);

	}
		break;
	case MSG_RLGL_GM_OPENGATE2:
	{
		CNetMsg::SP rmsg(new CNetMsg);
		RLGLMSG(rmsg);
		RefMsg(rmsg) << ((int)MSG_RLGL_STARTLINE);
		RefMsg(rmsg) << ((int)ch->m_pZone->m_index); // zone
		RefMsg(rmsg) << ((int)7264); // barrier
		RefMsg(rmsg) << ((int)7267); // forcefield

		SEND_Q(rmsg, ch->m_desc);

	}
	break;
	case MSG_RLGL_GM_CLOSEGATE2:
	{
		CNetMsg::SP rmsg(new CNetMsg);
		RLGLMSG(rmsg);
		RefMsg(rmsg) << ((int)MSG_RLGL_FINISHLINE);
		RefMsg(rmsg) << ((int)ch->m_pZone->m_index); // zone
		RefMsg(rmsg) << ((int)7264); // barrier
		RefMsg(rmsg) << ((int)7267); // forcefield


		SEND_Q(rmsg, ch->m_desc);

	}
	break;
	case MSG_RLGL_GM_START:
		MoveToRegenPoint();
		break;
	case MSG_RLGL_GM_STOP:
		RaceEnd();
		break;
	case MSG_RLGL_GM_COLOR1:
	{
		CNetMsg::SP rmsg(new CNetMsg);
		RLGLMSG(rmsg);
		RefMsg(rmsg) << ((int)MSG_RLGL_LIGHT);
		RefMsg(rmsg) << ((int)MSG_RLGL_GM_COLOR1);
		RefMsg(rmsg) << ((int)ch->m_pZone->m_index); // zone
		RefMsg(rmsg) << ((int)8); // COUNT
		RefMsg(rmsg) << ((int)7018); // light
		RefMsg(rmsg) << ((int)7017); //light
		RefMsg(rmsg) << ((int)7270); // light
		RefMsg(rmsg) << ((int)7271); //light
		RefMsg(rmsg) << ((int)7274); // light
		RefMsg(rmsg) << ((int)7276); //light
		RefMsg(rmsg) << ((int)7278); // light
		RefMsg(rmsg) << ((int)7280); //light

		 
		SEND_Q(rmsg, ch->m_desc); 
	}
		break;
	case MSG_RLGL_GM_COLOR2:
	{
		CNetMsg::SP rmsg(new CNetMsg);
		RLGLMSG(rmsg);

		RefMsg(rmsg) << ((int)MSG_RLGL_LIGHT);
		RefMsg(rmsg) << ((int)MSG_RLGL_GM_COLOR2);
		RefMsg(rmsg) << ((int)ch->m_pZone->m_index); // zone
		RefMsg(rmsg) << ((int)8); // COUNT
		RefMsg(rmsg) << ((int)7018); // light
		RefMsg(rmsg) << ((int)7017); //light
		RefMsg(rmsg) << ((int)7270); // light
		RefMsg(rmsg) << ((int)7271); //light
		RefMsg(rmsg) << ((int)7274); // light
		RefMsg(rmsg) << ((int)7276); //light
		RefMsg(rmsg) << ((int)7278); // light
		RefMsg(rmsg) << ((int)7280); //light

		SEND_Q(rmsg, ch->m_desc);
 
	}
		
	break;

	case MSG_RLGL_GM_TELE1:
	{
		MoveToWait();
	}
	break;
	case MSG_RLGL_GM_TELE2:
	{
		MoveToStart();

	}
	break;
	case MSG_RLGL_GM_TELE3:
	{
		MoveToKick();
	}
		break;


	case MSG_RLGL_GM_STARTBGM :
	{
		CNetMsg::SP rmsg2(new CNetMsg);
		RLGLMSG(rmsg2);
		RefMsg(rmsg2) << ((int)MSG_RLGL_GM);
		RefMsg(rmsg2) << ((int)MSG_RLGL_GM_STARTBGM);


		SEND_Q(rmsg2, ch->m_desc);
	}
	break;

	case MSG_RLGL_GM_STOPBGM:
	{
		CNetMsg::SP rmsg2(new CNetMsg);
		RLGLMSG(rmsg2);
		RefMsg(rmsg2) << ((int)MSG_RLGL_GM);
		RefMsg(rmsg2) << ((int)MSG_RLGL_GM_STOPBGM);


		SEND_Q(rmsg2, ch->m_desc);
	}
	break; 
	case MSG_RLGL_GM_TIME:
	{
		CNetMsg::SP rmsg2(new CNetMsg);
		RLGLMSG(rmsg2);
		RefMsg(rmsg2) << ((int)MSG_RLGL_GM);
		RefMsg(rmsg2) << ((int)MSG_RLGL_GM_TIME);
		RefMsg(rmsg2) << ((int)m_ieventstart);

		SEND_Q(rmsg2, ch->m_desc);
	}
	break;
	case MSG_RLGL_GM_GAMESTAT:
	{
		CNetMsg::SP rmsg2(new CNetMsg);
		RLGLMSG(rmsg2);
		RefMsg(rmsg2) << ((int)MSG_RLGL_GM);
		RefMsg(rmsg2) << ((int)MSG_RLGL_GM_GAMESTAT);
		RefMsg(rmsg2) << ((int)IRACEEND);
		RefMsg(rmsg2) << alive;
		RefMsg(rmsg2) << eliminated;
		RefMsg(rmsg2) << placeone;
		RefMsg(rmsg2) << placetwo;
		RefMsg(rmsg2) << placetree;
		
		SEND_Q(rmsg2, ch->m_desc);
	}
	break;

	}

}

enum movett {
	MMOVE_PD = 1,
	MMOVE_NORM = 2
};
void RLGL::MoveHook(CPC* ch, CNetMsg::SP& msg, int pd) {

	if (!m_bevent_on)
		return;
	if (ch->m_pZone->m_index != ZONE_RLGL)
		return;
	if (!m_bracestart)
		return;

	switch (pd)

	{

	case MMOVE_PD: // personal dungeon movement do_move_pd
	{

	}
	break;

	case MMOVE_NORM: //normal move type do_move
	{ 
		if (m_lightstizzle == ls_red)
		{
			if (time(NULL) > m_lastfiretime + 1) {


				CLCString Msg(255);
				Msg.Format("Kicked for moving on red. You were removed from the event area.");
				//SendRezaMessage(ch, Msg.getBuffer(), SystemMsgType::SYSMSG_RED);
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg(rmsg, MSG_SYS_REZA);
				RefMsg(rmsg) << Msg.GetBuffer();
				RefMsg(rmsg) << SystemMsgType::SYSMSG_RED;
				RefMsg(rmsg) << 1;
				SEND_Q(rmsg, ch->m_desc);

				// Give consolation item (85 x10) to eliminated player
				GiveLoserPrize(ch);

				int zone = 0;
				int extra = 0;

				CZone* pZone = gserver->FindZone(zone);
				GoZone(ch, zone,
					pZone->m_zonePos[extra][0],													// ylayer
					GetRandom(pZone->m_zonePos[extra][1], pZone->m_zonePos[extra][3]) / 2.0f, 		// x
					GetRandom(pZone->m_zonePos[extra][2], pZone->m_zonePos[extra][4]) / 2.0f);


				/*RequestClient::moveForNormal* packet = reinterpret_cast<RequestClient::moveForNormal*>(msg->m_buf);
				float reqX, reqH, reqZ, reqYlayer = 0;
				reqX = packet->x;
				reqZ = packet->z;
				reqH = packet->h;
				reqYlayer = packet->ylayer;


				int zone = 0;
				int extra = 7;
				CZone* pZone = gserver->FindZone(zone);
				int xmin = pZone->m_zonePos[extra][1] / 2;
				int xmax = pZone->m_zonePos[extra][3] / 2;
				int ymin = pZone->m_zonePos[extra][2] / 2;
				int ymax = pZone->m_zonePos[extra][4] / 2;
				//z is flipped because top left of map is 0,0 botom right is 512 512 
				if ((reqX > xmax || reqX < xmin) || (reqZ < ymax || reqZ > ymin)) {
					JailPlayer(ch);
				}*/

			}
		}
		if (m_lightstizzle == ls_green)
		{
			RequestClient::moveForNormal* packet = reinterpret_cast<RequestClient::moveForNormal*>(msg->m_buf);

			switch (packet->moveType)
			{
				case MSG_MOVE_WALK:
				case MSG_MOVE_RUN:
				case MSG_MOVE_FLY:
				case MSG_MOVE_PLACE:
					break;
				case MSG_MOVE_STOP:
				{
					float reqX, reqH, reqZ, reqYlayer = 0;
					reqX = packet->x;
					reqZ = packet->z;
					reqH = packet->h;
					reqYlayer = packet->ylayer;

					if (reqZ < 960) 
					{
						int added = 0;
						if (m_placement < 5)
						{
							added = 40 + 10 * (6 - m_placement);
						}
						else
						{
						 added = 10;
						}

						// Track actual finishers
						if (m_placement == 0)
							placeone = ch->GetName();
						else if (m_placement == 1)
							placetwo = ch->GetName();
						else if (m_placement == 2)
							placetree = ch->GetName();

						//ch->m_rlglpoints += added;
						
						//DBManager::instance()->SaveCharacterInfo(ch->m_desc, 0);
						CLCString Msg(255);
						Msg.Format("Event won %d place, which alloted you %d points", m_placement+1 , added );
						
						
						//SendRezaMessage(ch, Msg.getBuffer(), SystemMsgType::SYSMSG_RED);
						
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsg(rmsg, MSG_SYS_REZA);
						RefMsg(rmsg) << Msg.GetBuffer();
						RefMsg(rmsg) << SystemMsgType::SYSMSG_RED;
						RefMsg(rmsg) << 1;
						SEND_Q(rmsg, ch->m_desc)

						m_placement += 1;
						
						int zone = 0;
						int extra = 0;

						CZone* pZone = gserver->FindZone(zone);
						GoZone(ch, pZone->m_index,
							pZone->m_zonePos[extra][0],													// ylayer
							GetRandom(pZone->m_zonePos[extra][1], pZone->m_zonePos[extra][3]) / 2.0f,		// x
							GetRandom(pZone->m_zonePos[extra][2], pZone->m_zonePos[extra][4]) / 2.0f);
					}
				}
					break;

				default:
				{
				}
				return;
			}

			

				

				

		}
		}
	break;
	}


}

/*void RLGL::MoveToRegenPoint()
{
	CZone* pZone = gserver->FindZone(ZONE_RLGL);
	if (pZone == NULL)
		return;

	gserver->m_RLGL.m_ieventstart = time(NULL);
	gserver->m_RLGL.m_bevent_on = true;
	gserver->m_RLGL.m_bmovewait = true;
	gserver->m_RLGL.m_bmovestart = false;
	gserver->m_RLGL.m_bracestart = false;
	gserver->m_RLGL.m_braceend = false;
	gserver->m_RLGL.m_nextfiretime = 0;
	gserver->m_RLGL.m_lightstizzle = ls_green;
	gserver->m_RLGL.m_placement = 0;

	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter = playerMap.begin();
	PCManager::map_t::iterator endIter = playerMap.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc)
		{
			//int extra = GetRegenPoint(pc->GetJoinFlag(ZONE_DRATAN), pc);
			//if (extra == 0)
			//	continue;
			//check some join flag if they want the prompt or not 
#ifdef conditiontosend
			if (!(pc->m_pZone->m_index == GetZoneIndex()
				&& pc->m_pZone->InExtra((int)GET_X(pc), (int)GET_Z(pc), extra)))
#endif
			{
				//send warp request
				CNetMsg::SP rmsg(new CNetMsg);
				WarpPromptMsg(rmsg, pZone->m_index, 0); //warp to rlgl wating room prompt
				SEND_Q(rmsg, pc->m_desc);
			}
		}
	}
}*/

void RLGL::UpdateWaitTime()
{
	CZone* pZone = gserver->FindZone(ZONE_RLGL);
	if (pZone == NULL)
		return;

	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter = playerMap.begin();
	PCManager::map_t::iterator endIter = playerMap.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc)
		{
			//int extra = GetRegenPoint(pc->GetJoinFlag(ZONE_DRATAN), pc);
			//if (extra == 0)
			//	continue;
			//check some join flag if they want the prompt or not 

			if (pc->m_pZone->m_index == 55)
			{
				RLGLMENU(pc, MSG_RLGL_GM_TIME);

			}
		}
	}
}


void RLGL::MoveToStart()
{
	CZone* pZone = gserver->FindZone(ZONE_RLGL);
	if (pZone == NULL)
		return;


	std::vector<Player> players;

	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter = playerMap.begin();
	PCManager::map_t::iterator endIter = playerMap.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc)
		{
			//int extra = GetRegenPoint(pc->GetJoinFlag(ZONE_DRATAN), pc);
			//if (extra == 0)
			//	continue;
			//check some join flag if they want the prompt or not 

			if (pc->m_pZone->m_index == 55)
			{

				Player cp;
				cp.pc = pc;
				players.push_back(cp);

				SendTimer(pc, IRACESTART);

				RLGLMENU(pc, MSG_RLGL_GM_COLOR2);

				RLGLMENU(pc, MSG_RLGL_GM_CLOSEGATE1);

				RLGLMENU(pc, MSG_RLGL_GM_CLOSEGATE2);

				SendMenuTab(pc, 1);

				GoZone(pc, pZone->m_index,
					pZone->m_zonePos[1][0],
					GetRandom(pZone->m_zonePos[1][1], pZone->m_zonePos[1][3]) / 2.0f,
					GetRandom(pZone->m_zonePos[1][2], pZone->m_zonePos[1][4]) / 2.0f);
			}
		}
	}


	if (!players.empty()) {
	 
		alive = players.size();

		eliminated  = 0;
		placeone = "None";
		placetwo = "None";
		placetree = "None";
	 
		for (std::vector<Player>::const_iterator it = players.begin(); it != players.end(); ++it) {
			const Player& player = *it;
			RLGLMENU(player.pc, MSG_RLGL_GM_GAMESTAT);
		}
	}

}

void RLGL::MoveToWait()
{
	CZone* pZone = gserver->FindZone(ZONE_RLGL);
	if (pZone == NULL)
		return;

	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter = playerMap.begin();
	PCManager::map_t::iterator endIter = playerMap.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc)
		{
			//int extra = GetRegenPoint(pc->GetJoinFlag(ZONE_DRATAN), pc);
			//if (extra == 0)
			//	continue;
			//check some join flag if they want the prompt or not 

			if (pc->m_pZone->m_index == 55)
			{
				GoZone(pc, pZone->m_index,
					pZone->m_zonePos[0][0],
					GetRandom(pZone->m_zonePos[0][1], pZone->m_zonePos[0][3]) / 2.0f,
					GetRandom(pZone->m_zonePos[0][2], pZone->m_zonePos[0][4]) / 2.0f);
			}
		}
	}
}

void RLGL::MoveToKick()
{
	
	
	CZone* pZone = gserver->FindZone(ZONE_START);
	if (pZone == NULL)
		return;

	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter = playerMap.begin();
	PCManager::map_t::iterator endIter = playerMap.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc)
		{
			if (pc->m_pZone->m_index == 55)
			{
				// Give consolation prize from DB to losers
				GiveLoserPrize(pc);

				CLCString Msg(255);
				Msg.Format("Event has ended and you did not reach the end you were ejected.");
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg(rmsg, MSG_SYS_REZA);
				RefMsg(rmsg) << Msg.GetBuffer();
				RefMsg(rmsg) << SystemMsgType::SYSMSG_RED;
				RefMsg(rmsg) << 1;
				SEND_Q(rmsg, pc->m_desc);

				GoZone(pc, pZone->m_index,
					pZone->m_zonePos[0][0],
					GetRandom(pZone->m_zonePos[0][1], pZone->m_zonePos[0][3]) / 2.0f,
					GetRandom(pZone->m_zonePos[0][2], pZone->m_zonePos[0][4]) / 2.0f);
				
				//DBManager::instance()->SaveCharacterInfo(pc->m_desc, 0);
			}
		}
	}
}



void RLGL::RaceStart()
{
	CZone* pZone = gserver->FindZone(ZONE_RLGL);
	if (pZone == NULL)
		return;

	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter = playerMap.begin();
	PCManager::map_t::iterator endIter = playerMap.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc)
		{
			//int extra = GetRegenPoint(pc->GetJoinFlag(ZONE_DRATAN), pc);
			//if (extra == 0)
			//	continue;
			//check some join flag if they want the prompt or not 

			if (pc->m_pZone->m_index == pZone->m_index)
			{
				RLGLMENU(pc, MSG_RLGL_GM_OPENGATE1);

				RLGLMENU(pc, MSG_RLGL_GM_OPENGATE2);

				RLGLMENU(pc, MSG_RLGL_GM_STARTBGM);

				RLGLMENU(pc, MSG_RLGL_GM_COLOR1);

				SendMenuTab(pc, 1);
				//SendTimer(pc, IRACEEND);
				

			}
		}
	}
}



void RLGL::RaceUpdate()
{


	CZone* pZone = gserver->FindZone(ZONE_RLGL);
	if (pZone == NULL)
		return;

	std::vector<Player> players;

	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter = playerMap.begin();
	PCManager::map_t::iterator endIter = playerMap.end();


	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc)
		{ 
			if (pc->m_pZone->m_index == pZone->m_index)
			{
				Player cp;
				cp.pc = pc;
				players.push_back(cp);

				if (m_lightstizzle == ls_green)
				{
					//update green
					RLGLMENU(pc, MSG_RLGL_GM_STARTBGM);

					RLGLMENU(pc, MSG_RLGL_GM_COLOR1);
				}
				else {
					//update red
					RLGLMENU(pc, MSG_RLGL_GM_STOPBGM);

					RLGLMENU(pc, MSG_RLGL_GM_COLOR2);
					
					
				}

			}
		}
	}

	if (!players.empty()) {
		std::sort(players.begin(), players.end(), comparePosition);

		if (alive == 0) alive = players.size();

		eliminated += alive - players.size();
		
		alive = players.size();

		for (std::vector<Player>::const_iterator it = players.begin(); it != players.end(); ++it) {
			const Player& player = *it;
			RLGLMENU(player.pc, MSG_RLGL_GM_GAMESTAT);
		}
	}



}


void RLGL::RaceEnd()
{
	m_bevent_on = false;
	m_placement = 0;
	m_lightstizzle = ls_green;
	m_nextfiretime = 0;
	m_lastfiretime = 0;

	m_ieventstart = 0;
	m_bmovewait = false;
	m_bmovestart = false;
	m_bracestart = false;
	// Note: m_braceend remains true until next event starts in MoveToRegenPoint()

	// give prizes to top finishers
	GivePrizes();

	/*	
	CZone* pZone = gserver->FindZone(ZONE_RLGL);
	if (pZone == NULL)
		return;

	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter = playerMap.begin();
	PCManager::map_t::iterator endIter = playerMap.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc)
		{
			//int extra = GetRegenPoint(pc->GetJoinFlag(ZONE_DRATAN), pc);
			//if (extra == 0)
			//	continue;
			//check some join flag if they want the prompt or not 

			if (pc->m_pZone->m_index == pZone->m_index)
			{
				
				//	RLGLMENU(pc, MSG_RLGL_GM_STARTBGM);

				//	RLGLMENU(pc, MSG_RLGL_GM_COLOR1);
				

			}
		}
	}
	*/
}



void RLGL::Tick()
{
	if (!m_bevent_on)
		return;
	int timenow = time(NULL);

	if (timenow > m_ieventstart && !m_bmovewait)
	{
		MoveToRegenPoint();
		m_bmovewait = true;
	}
	else if (timenow > m_ieventstart && timenow < IMOVESTART  && m_bmovestart)
	{
	/*	//fix me later shit optimization 
		UpdateWaitTime();
		//updatetime*/
	}
	else if (timenow > IMOVESTART && !m_bmovestart)
	{
		GAMELOG << init("RLGL") << "Tick: MoveToStart triggered" << end;
		m_bmovestart = true;
		MoveToStart();
		eliminated = 0;
		alive = 0;
		m_placement = 0;
		placeone = "None";
		placetwo = "None";
		placetree = "None";
	}
	else if (timenow > IRACESTART && !m_bracestart) {

		GAMELOG << init("RLGL") << "Tick: RaceStart triggered" << end;
		m_bracestart = true;
		RaceStart();
		int randomDelay = rand() % 8 + 3;
		m_lightstizzle = ls_green;

		m_lastfiretime = m_nextfiretime;
		m_nextfiretime = timenow + randomDelay;
	

	}
	else if (timenow > IRACESTART && timenow < IRACEEND  && m_bracestart)
	{
		if (timenow > m_nextfiretime) 
		{
			if (m_lightstizzle == ls_green) 
			{
				m_lightstizzle = ls_red;
				int randomDelay = rand() % 8 + 3;

				m_lastfiretime = m_nextfiretime;
				m_nextfiretime = timenow + randomDelay;
			}
			else
			{
				m_lightstizzle = ls_green;
				int randomDelay = rand() % 8 + 3;

				m_lastfiretime = m_nextfiretime;
				m_nextfiretime = timenow + randomDelay;

			}
			//update placement stats
			RaceUpdate();
		}
		}
	else if (timenow > IRACEEND && !m_braceend)
	{ 
		m_braceend = true;
		// Announce event end to entire server
		{
			CNetMsg::SP nmsg(new CNetMsg);
			SayMsg(nmsg, MSG_CHAT_NOTICE, 0, "", "", "[RLGL] Red Light Green Light event has ended!");
			PCManager::instance()->sendToAll(nmsg);
		}

		RaceEnd();
		MoveToKick();

		//gserver->m_GuildRanking.ReLoadRLGLRanking();
	}

}


void RLGL::RLGLCMD(CPC* ch, const char* arg, std::vector<std::string>& vec) {

	if (vec.size() > 0) {
		/*if (vec[0] == "open") {
			gserver->m_RLGL.openmap(ch);
		}
		else if (vec[0] == "close") {
			gserver->m_RLGL.closemap(ch);
		}
		else if (vec[0] == "start") {
			gserver->m_RLGL.startgame(ch);
		}
		else if (vec[0] == "end") {
			if (vec.size() > 1)
				gserver->m_RLGL.stopgame(ch, atoi(vec[1].c_str()));

		}
		else if (vec[0] == "tele") {
			if (vec.size() > 1)
				gserver->m_RLGL.sendteleportreq(ch, atoi(vec[1].c_str()));

		}
		else*/
		if (strcmp(vec[0].c_str(), "start") == 0)
		{
			if (vec.size() == 1)
			{
				

				gserver->m_RLGL.MoveToRegenPoint();
			}
		}
		else if (strcmp(vec[0].c_str(), "menu") == 0)
		{
			if (vec.size() > 1)
				gserver->m_RLGL.SendMenu(ch, atoi(vec[1].c_str()));
		}
		else if (strcmp(vec[0].c_str(), "end") == 0)
		{
			if (vec.size() == 1)
				RaceEnd();
		}
		else if (strcmp(vec[0].c_str(), "reload") == 0)
		{
			gserver->m_autoEventScheduler.Reload();
		}
		else
		{
			return;
		}
	}
}



void RLGL::GivePrizes()
{
	

	CDBCmd dbcmd;
 dbcmd.Init(&gserver->m_dbdata);
 dbcmd.SetQuery("SELECT a_pos, a_item_idx, a_item_count, a_item_plus, a_item_flag, a_message FROM t_rlgl ORDER BY a_pos ASC");

	if (!dbcmd.Open()) {
		GAMELOG << init("RLGL GIVEPRIZES") << "Could not open t_rlgl" << end;
		return;
	}

	std::map<int, std::vector<std::tuple<int,int,int,int,std::string>>> prizeMap; // pos -> list of (itemidx,count,plus,flag,msg)

	int pos=0, itemidx=0, itemcount=0, itemplus=0, itemflag=0;
 std::string msg;
 while (dbcmd.MoveNext()) {
	 dbcmd.GetRec("a_pos", pos);
	 dbcmd.GetRec("a_item_idx", itemidx);
	 dbcmd.GetRec("a_item_count", itemcount);
	 dbcmd.GetRec("a_item_plus", itemplus);
	 dbcmd.GetRec("a_item_flag", itemflag);
	 dbcmd.GetRec("a_message", msg);

	 prizeMap[pos].push_back(std::make_tuple(itemidx, itemcount, itemplus, itemflag, msg));
 }

	// Determine top players from current RLGL tracked places (placeone, placetwo, placetree)
	std::vector<std::pair<int,std::string>> winners; // pos, name
	if (placeone.Length() > 0 && strcmp(placeone.GetBuffer(), "None") != 0) winners.push_back(std::make_pair(1, std::string(placeone.GetBuffer())));
	if (placetwo.Length() > 0 && strcmp(placetwo.GetBuffer(), "None") != 0) winners.push_back(std::make_pair(2, std::string(placetwo.GetBuffer())));
	if (placetree.Length() > 0 && strcmp(placetree.GetBuffer(), "None") != 0) winners.push_back(std::make_pair(3, std::string(placetree.GetBuffer())));

	for (auto &wp : winners) {
		int winnerPos = wp.first;
		std::string winnerName = wp.second;

		// Announce winner to entire server
		{
			CNetMsg::SP nmsg(new CNetMsg);
			CLCString announce(255);
			announce.Format("[RLGL] %s finished in %d place!", winnerName.c_str(), winnerPos);
			SayMsg(nmsg, MSG_CHAT_NOTICE, 0, "", "", announce.GetBuffer());
			PCManager::instance()->sendToAll(nmsg);
		}

		CPC* tgt = NULL;
		PCManager::map_t& pm = PCManager::instance()->getPlayerMap();
		for (PCManager::map_t::iterator it = pm.begin(); it != pm.end(); ++it) {
			CPC* pc = (*it).pPlayer;
			if (pc) {
				const char* pname = pc->GetName();
				if (pname && strcmp(pname, winnerName.c_str()) == 0) { tgt = pc; break; }
			}
		}

		if (tgt == NULL) {
			GAMELOG << init("RLGL GIVEPRIZES") << "Player " << winnerName.c_str() << " not online, skipping prizes" << end;
			continue;
		}

		for (auto &entry : prizeMap[winnerPos]) {
			int iidx, icnt, iplus, iflag;
			std::string imsg;
			std::tie(iidx, icnt, iplus, iflag, imsg) = entry;

			if (iidx > 0) {
				CItem* pItem = gserver->m_itemProtoList.CreateItem(iidx, -1, iplus, iflag, icnt);
				if (pItem) {
					pItem->setFlag(pItem->getFlag() | FLAG_ITEM_BELONG);
					if (!tgt->m_inventory.addItem(pItem)) {
						GAMELOG << init("RLGL GIVEPRIZES") << "Failed to give item " << iidx << " to " << tgt->GetName() << end;
						delete pItem;
					} else {
						CNetMsg::SP rmsg(new CNetMsg);
						CLCString sbuf(255);
						sbuf.Format("You received a prize for finishing %d place!", winnerPos);
						SysMsg(rmsg, MSG_SYS_REZA);
						RefMsg(rmsg) << sbuf.GetBuffer();
						RefMsg(rmsg) << SystemMsgType::SYSMSG_CYAN;
						RefMsg(rmsg) << 1;
						SEND_Q(rmsg, tgt->m_desc);
					}
				}
			}
		}
	}

	GAMELOG << init("RLGL GIVEPRIZES") << "Completed prize distribution" << end;
}

void RLGL::MoveToRegenPoint()
{
	CZone* pZone = gserver->FindZone(ZONE_RLGL);
	if (pZone == NULL)
		return;

	gserver->m_RLGL.m_ieventstart = time(NULL);
	gserver->m_RLGL.m_bevent_on = true;
	gserver->m_RLGL.m_bmovewait = true;
	gserver->m_RLGL.m_bmovestart = false;
	gserver->m_RLGL.m_bracestart = false;
	gserver->m_RLGL.m_braceend = false;
	gserver->m_RLGL.m_nextfiretime = 0;
	gserver->m_RLGL.m_lightstizzle = ls_green;
	gserver->m_RLGL.m_placement = 0;

	// Announce event start to entire server
	{
		CNetMsg::SP nmsg(new CNetMsg);
		SayMsg(nmsg, MSG_CHAT_NOTICE, 0, "", "", "[RLGL] Red Light Green Light event is starting! Accept the warp to join!");
		PCManager::instance()->sendToAll(nmsg);
	}

	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter = playerMap.begin();
	PCManager::map_t::iterator endIter = playerMap.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc)
		{
			//int extra = GetRegenPoint(pc->GetJoinFlag(ZONE_DRATAN), pc);
			//if (extra == 0)
			//	continue;
			//check some join flag if they want the prompt or not 
#ifdef conditiontosend
			if (!(pc->m_pZone->m_index == GetZoneIndex()
				&& pc->m_pZone->InExtra((int)GET_X(pc), (int)GET_Z(pc), extra)))
#endif
			{
				//send warp request
				CNetMsg::SP rmsg(new CNetMsg);
				WarpPromptMsg(rmsg, pZone->m_index, 0); //warp to rlgl wating room prompt
				SEND_Q(rmsg, pc->m_desc);
			}
		}
	}
}

void RLGL::OnEnterZone(CPC* ch)
{
	if (!m_bevent_on)
		return;
	if (ch == NULL || ch->m_pZone == NULL)
		return;
	if (ch->m_pZone->m_index != ZONE_RLGL)
		return;

	int timenow = time(NULL);

	// Still in waiting phase - send countdown to race start
	if (timenow < IMOVESTART)
	{
		int remaining = IMOVESTART - timenow;
		SendTimer(ch, m_ieventstart);
		SendMenuTab(ch, 0);
	}
	// In the move-to-start phase or race phase - send race timer
	else if (timenow < IRACEEND)
	{
		SendTimer(ch, IRACESTART);
		SendMenuTab(ch, 1);

		if (m_bracestart)
		{
			// Send current light state
			if (m_lightstizzle == ls_green)
			{
				RLGLMENU(ch, MSG_RLGL_GM_COLOR1);
				RLGLMENU(ch, MSG_RLGL_GM_STARTBGM);
			}
			else
			{
				RLGLMENU(ch, MSG_RLGL_GM_COLOR2);
				RLGLMENU(ch, MSG_RLGL_GM_STOPBGM);
			}

			RLGLMENU(ch, MSG_RLGL_GM_GAMESTAT);
		}
	}
}

void RLGL::GiveLoserPrize(CPC* pc)
{
	if (pc == NULL)
		return;

	CDBCmd dbcmd;
	dbcmd.Init(&gserver->m_dbdata);
	dbcmd.SetQuery("SELECT a_item_idx, a_item_count, a_item_plus, a_item_flag, a_message FROM t_rlgl WHERE a_pos = 0");

	if (!dbcmd.Open()) {
		GAMELOG << init("RLGL GIVELOSERPRIZE") << "Could not open t_rlgl for loser prizes" << end;
		return;
	}

	int itemidx = 0, itemcount = 0, itemplus = 0, itemflag = 0;
	std::string msg;
	while (dbcmd.MoveNext()) {
		dbcmd.GetRec("a_item_idx", itemidx);
		dbcmd.GetRec("a_item_count", itemcount);
		dbcmd.GetRec("a_item_plus", itemplus);
		dbcmd.GetRec("a_item_flag", itemflag);
		dbcmd.GetRec("a_message", msg);

		if (itemidx > 0) {
			CItem* pItem = gserver->m_itemProtoList.CreateItem(itemidx, -1, itemplus, itemflag, itemcount);
			if (pItem) {
				if (!pc->m_inventory.addItem(pItem)) {
					GAMELOG << init("RLGL GIVELOSERPRIZE") << "Failed to give item " << itemidx << " to " << pc->GetName() << end;
					delete pItem;
				} else {
					CNetMsg::SP rmsg(new CNetMsg);
					CLCString sbuf(255);
					sbuf.Format("You received a consolation prize for participating!");
					SysMsg(rmsg, MSG_SYS_REZA);
					RefMsg(rmsg) << sbuf.GetBuffer();
					RefMsg(rmsg) << SystemMsgType::SYSMSG_CYAN;
					RefMsg(rmsg) << 1;
					SEND_Q(rmsg, pc->m_desc);
				}
			}
		}
	}
}
