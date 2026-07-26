#pragma once
#ifndef __REZASFUNCTIONS__
#define __REZASFUNCTIONS__
#include "../ShareLib/Config.h"
#include "RezasFunction.h"
enum REZAMSG
{
	REZAPVP_PVP = 0,
	REZA_REZAPCHA = 1,
	POPLOCKNDROPIT = 2,
	REZA_REZABOT = 3,
	REZA_REZEXTRAS = 4,
	REZA_FUSION = 5,
	REZA_DAILY_LOGIN = 6,
#ifdef REZAMOG
	REZA_TRANSMOG = 7,
#endif
#ifdef INSTANTSKILLCHANGE
	REZA_SKILLSKIP = 8,
#endif
	REZA_RLGL = 9,
	REZA_RPS = 69,
#ifdef PLRREMOVEBUFF
	REZA_REMOVEBUFFREQ,
#endif
};

enum SystemMsgType
{
	SYSMSG_NORMAL					= 0,
	SYSMSG_ATTACK					= 1,
	SYSMSG_ATTACKED					= 2,
	SYSMSG_ERROR					= 3,
	SYSMSG_NOTIFY					= 4,
	SYSMSG_USER						= 5, //wooss 070307 kw:WSS_WHITEDAY_2007
	SYSMSG_CYAN						= 6, //reza SYSCOLORS
	SYSMSG_RED						= 7,
	SYSMSG_DIRTYELLOW				= 8,
	SYSMSG_TOTAL					,

};
void do_Move_hook(CPC* ch, CNetMsg::SP& msg ,int pd ); 

//void SendSysMessage(CPC* ch, char* msg, SystemMsgType type);
void chatlog(CPC* ch , CNetMsg::SP& msg );
void GMLog(CPC* ch , CNetMsg::SP& msg );

void LogHack(CPC* ch, char* Log);

#ifdef PLRREMOVEBUFF
void RemoveBuffReq(CPC* ch, CNetMsg::SP& msg);
#endif

void SendRezaMessage(CPC* ch, char* msg, SystemMsgType type = SYSMSG_DIRTYELLOW);

void SendSysMessage(CPC* ch, char* msg, SystemMsgType type = SYSMSG_RED);
bool fkplayer(CPC* ch , char* msg , bool condition);
bool fkplayer(CPC* ch , char* msg , bool condition, int close);
bool fkplayer(CPC* ch , char* msg , bool condition , char* logmessage);
bool fkplayer(CPC* ch , SystemMsgType type,char* msg ,char* logmsg, bool condition ,int log,int close);

#ifdef REZAPCHA


bool JailCheck(CPC* ch , CNetMsg::SP& msg, int pd);
void LockPlayer(CPC* ch,int bOn); 
void JailPlayer(CPC* ch);
void JailPlayer(CPC* ch,int bOn);


#endif 


int REZAGetCRCOnOff();
int REZAGetCRCCount();
void REZAGetCRCList(unsigned int *CRCServer, int size); 

#ifdef INCREASECELLRENDER
void getNewCell_ext(CPC* ch , int& iCell_Ext);
void getNewCell_ext(CCharacter* ch , int& iCell_Ext);
void getNewCell_ext(int zone, int& iCell_Ext);
#endif


//rezextras 
void do_Ex_NameChangeColor(CPC* ch , CNetMsg::SP& msg); 


//#ifdef DYNAMICEXCHANGE
//#include "DynamicExchange.h"
//#endif
//#ifdef DYNAMICQUESTICLES
//#include "DQuest.h"
//#endif

#ifdef REZAPVP 
#include "RezaPVP.h"
#endif 
#ifdef REZAPCHA
//#include "Rezapcha.h" 
#endif 

#ifdef REZABOT
#include "ReZaBot.h" 
#endif

#ifdef KILLMEDALS
#include "KillMedals.h"
#endif

#include "rlgl.h"
#ifdef DAILY_LOGIN
#include "DailyLogin.h"
#endif
#ifdef buff_npc
#include "BuffNpc.h"
#endif 
#include "AutoBuffer.h"
#ifdef GM_AUTO_CHAT
#include "AutoChat.h"
#endif

#ifdef DAILY_LOGIN
#include "DailyLogin.h" 
#endif 

#ifdef RankingGuild_23_08_2018
#include "GuildRanking.h"
#endif

#ifdef REZAMOG
#include "RezaMog.h"
#endif 

#endif