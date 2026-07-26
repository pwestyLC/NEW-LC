#ifndef __REZA_H
#define __REZA_H

#include <Common\CommonDef.h>

#ifdef REZEXTRAS
#include "Rezextras.h"
#endif

#ifdef SET_FUSION
#include <Engine/set_fusion.h>
#endif

#ifdef KILLMEDALS
#include <Engine/KillMedalStats.h>
#endif

#ifdef REZAPVP
#include "RezaPVP.h"
#endif

#ifdef REZAPCHA
//#include "Rezapcha.h"
#endif 
#ifdef REZARPS
#include "RezaRps.h"
#endif
#ifdef REZABOT
#include "ReZaBot.h"
#endif

#ifdef DAILY_LOGIN
#include "DailyLogin.h"
#endif

#include "rlgl.h"

#ifdef REZAMOG
#include "Rezamog.h"
#endif

#ifdef SET_FUSION
#include "set_fusion.h"
#endif 


enum REZAMSG
{
	
#ifdef REZAPVP
	REZAPVP_PVP = 0,
#endif
#ifdef REZAPCHA
	REZA_REZAPCHA = 1,
	POPLOCKNDROPIT = 2,
#endif
#ifdef REZABOT
	REZA_REZABOT = 3,
#endif 
#ifdef REZEXTRAS
	REZA_REZEXTRAS = 4,
#endif
#ifdef SET_FUSION
	REZA_FUSION = 5,
#endif
#ifdef DAILY_LOGIN
	REZA_DAILY_LOGIN = 6,
#endif
	
#ifdef REZAMOG
	REZA_TRANSMOG = 7,
#endif
#ifdef INSTANTLEARNCLASSCHANGE
	REZA_SKILLSKIP = 8, 
#endif
	REZA_RLGL = 9,
#ifdef REZARPS
	REZA_RPS = 69,
#endif
#ifdef PLRREMOVEBUFF
	REZA_REMOVEBUFFREQ,
#endif

};


	void do_Reza(CNetworkMessage* istr);


void SetMove(int v);

bool CantMove();
	



#endif