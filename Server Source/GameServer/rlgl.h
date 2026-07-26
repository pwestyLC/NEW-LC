#ifndef __RLGL_H__
#define __RLGL_H__

enum MSG_RLGL
{
	MSG_RLGL_OPEN = 0,
	MSG_RLGL_CLOSE,
	MSG_RLGL_STARTLINE,
	MSG_RLGL_FINISHLINE,
	MSG_RLGL_LIGHT,
	MSG_RLGL_STARTZONEPROMPT,
	MSG_RLGL_GM,
	MSG_RLGL_TAB

};
 
enum MSG_RLGL_GMCMD {
	MSG_RLGL_GM_CLOSEGATE1=0,
	MSG_RLGL_GM_CLOSEGATE2,
	MSG_RLGL_GM_OPENGATE1,
	MSG_RLGL_GM_OPENGATE2,
	MSG_RLGL_GM_TELE1,
	MSG_RLGL_GM_TELE2,
	MSG_RLGL_GM_TELE3,
	MSG_RLGL_GM_START,
	MSG_RLGL_GM_STOP,
	MSG_RLGL_GM_COLOR1,
	MSG_RLGL_GM_COLOR2,
	MSG_RLGL_GM_STARTBGM,
	MSG_RLGL_GM_STOPBGM,
	MSG_RLGL_GM_TIME,
	MSG_RLGL_GM_GAMESTAT,


	MSG_RLGL_GM_END,


};

enum LIGHTSTATE
{
	ls_green = 0,
	ls_red = 1
};




class RLGL
{


public:
	//variables

	bool m_bevent_on;

	int m_placement;

	LIGHTSTATE m_lightstizzle ;
	time_t m_nextfiretime;
	time_t m_lastfiretime;

	int m_ieventstart;//imovewait
	bool m_bmovewait, m_bmovestart, m_bracestart, m_braceend;
	
	int alive;
	int eliminated;
	CLCString placeone;
	CLCString placetwo;
	CLCString placetree;

public:
	void RLGLMSG(CNetMsg::SP& msg);
	void do_RLGL(CPC* ch, CNetMsg::SP& msg);
	RLGL();
	~RLGL();



	bool LoadRLGL();
	void ReloadRLGL();

	void SendMenu(CPC* ch, int gm);
	void SendMenuTab(CPC* ch, int tab);

	void SendTimer(CPC * ch, int time);

	void RLGLMENU(CPC* ch , int sub);

	void MoveHook(CPC* ch, CNetMsg::SP& msg, int pd);

	void MoveToRegenPoint();
	void UpdateWaitTime();

	void MoveToStart();

	void MoveToWait();

	void MoveToKick();

	void RaceStart();

	void RaceUpdate();

	void RaceEnd();

	void Tick();

	void OnEnterZone(CPC* ch);

	void RLGLCMD(CPC* ch, const char* arg, std::vector<std::string>& vec);

	// Automatically give prizes to winners using the t_rlgl table in the data database
	void GivePrizes();

	// Give loser/consolation prizes from t_rlgl (a_pos = 0) to a single player
	void GiveLoserPrize(CPC* pc);
};
#endif