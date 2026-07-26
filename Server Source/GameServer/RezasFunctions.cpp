#include "stdhdrs.h"
#include "Server.h"
#include "CmdMsg.h"
#include "Character.h" 
#include "RezasFunction.h"

#include "ReZaBot.h" 
#include "DBManager.h"

#include "../ShareLib/packetType/ptype_old_do_move.h"
//#include "../ShareLib/packetType/ptype_old_do_move.h"




void do_Reza(CPC* ch ,CNetMsg::SP& msg){

	int type = 0 ;
	RefMsg(msg)>>type ;
	switch (type)
	{
	

	case REZA_DAILY_LOGIN:
		{
			gserver->m_DailyLogin.do_DailyLogin(ch,msg);
		}
		break;
	case REZA_RLGL:
		{
	gserver->m_RLGL.do_RLGL(ch, msg); //RLGL
		}
		break;
	case REZA_REZABOT:
	{
		gserver->m_Rezabot.InterpretMsg(ch, msg);
	}
	break; 

	}
}

void do_Move_hook(CPC* ch , CNetMsg::SP& msg, int pd){

    gserver->m_RLGL.MoveHook(ch , msg, pd);
    

	if (ch->m_jailed == 1) {
		JailCheck(ch, msg, pd);
	}
    return;

}

void LockPlayer(CPC* ch, int bOn) {

	CNetMsg::SP msg(new CNetMsg);
	msg->Init(MSG_REZA);
	RefMsg(msg) << ((int)POPLOCKNDROPIT);
	RefMsg(msg) << ((int)bOn);
	SEND_Q(msg, ch->m_desc);
}

enum movet {
	MOVE_PD = 1,
	MOVE_NORM = 2
};
bool JailCheck(CPC* ch, CNetMsg::SP& msg, int pd)
{

	switch (pd)

	{

	case MOVE_PD:
	{

		JailPlayer(ch);
	}
	break;

	case MOVE_NORM:
	{

		RequestClient::moveForNormal* packet = reinterpret_cast<RequestClient::moveForNormal*>(msg->m_buf);
		float reqX, reqH, reqZ, reqYlayer = 0;
		reqX = packet->x;
		reqZ = packet->z;
		reqH = packet->h;
		reqYlayer = packet->ylayer;


		int zone = 0;
		int extra = 0;
		CZone* pZone = gserver->FindZone(zone);
		int xmin = pZone->m_zonePos[extra][1] / 2;
		int xmax = pZone->m_zonePos[extra][3] / 2;
		int ymin = pZone->m_zonePos[extra][2] / 2;
		int ymax = pZone->m_zonePos[extra][4] / 2;
		//z is flipped because top left of map is 0,0 botom right is 512 512 
		if ((reqX > xmax || reqX < xmin) || (reqZ < ymax || reqZ > ymin)) {
			JailPlayer(ch);
		}

	}
	break;
	}


	return false;

}
void JailPlayer(CPC* ch) {

	// 존을 찾아서
	ch->m_jailed_time = time(NULL);

	ch->m_jailed_count += 1;
	ch->m_jailed = 1;
	int zone = 0;
	int extra = 7;

	CZone* pZone = gserver->FindZone(zone);
	GoZone(ch, zone,
		pZone->m_zonePos[extra][0],														// ylayer
		GetRandom(pZone->m_zonePos[extra][1], pZone->m_zonePos[extra][3]) / 2.0f,		// x
		GetRandom(pZone->m_zonePos[extra][2], pZone->m_zonePos[extra][4]) / 2.0f);




}
void JailPlayer(CPC* ch, int bOn) {


	if (bOn) {
		JailPlayer(ch);
	}
	else {
		ch->m_jailed_time = 0;
		ch->m_jailed = 0;
		int zone = 0;
		int extra = 0;

		CZone* pZone = gserver->FindZone(zone);
		GoZone(ch, zone,
			pZone->m_zonePos[extra][0],														// ylayer
			GetRandom(pZone->m_zonePos[extra][1], pZone->m_zonePos[extra][3]) / 2.0f,		// x
			GetRandom(pZone->m_zonePos[extra][2], pZone->m_zonePos[extra][4]) / 2.0f);

	}


}


void SendRezaMessage(CPC* ch, char* msg, SystemMsgType type) { 

	//uh oh! message 
	CNetMsg::SP rmsg(new CNetMsg);
	SysMsg(rmsg, MSG_SYS_REZA);
	RefMsg(rmsg) << msg ;
	RefMsg(rmsg) << type; 
	RefMsg(rmsg) << 0;
	SEND_Q(rmsg, ch->m_desc);

}