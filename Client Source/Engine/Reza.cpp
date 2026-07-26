#include "StdH.h"
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Common/Packet/ptype_reserved_gm_command.h>
#include <Engine/Network/CNetwork.h>
#include <Engine/Help/Util_Help.h>



#include "Reza.h"



void  do_Reza(CNetworkMessage* istr){
		int type = 0 ;
		(*istr) >> type ;
		switch (type)
		{
#ifdef REZAPVP
		case REZAPVP_PVP:
			{
				CUIManager* pUIManager = CUIManager::getSingleton();
				RezaPVP* pRezaPVP = pUIManager->GetRezaPVP();
				if (pRezaPVP != NULL)
					pRezaPVP->do_RezaPVP(istr);
			}
			break;
#endif

#ifdef REZAPCHA
		/*case REZA_REZAPCHA:
		{
				CUIManager* pUIManager = CUIManager::getSingleton();
				Rezapcha* pRezapcha = pUIManager->GetRezapcha();
				if (pRezapcha != NULL)
					pRezapcha->do_Rezapcha(istr);
		}
		break;*/

		case POPLOCKNDROPIT:
			{
				int typetwo = 0 ;
				(*istr) >> typetwo ;
				if(typetwo==0)
				{
					CUIManager* pUIManager = CUIManager::getSingleton();
					SetMove(0);
					pUIManager->SetCSFlagOff( CSF_TELEPORT );
				}
				else
				{
					SetMove(1);
					CUIManager* pUIManager = CUIManager::getSingleton();
				
					pUIManager->SetCSFlagOn( CSF_TELEPORT );
				}
			}
			break;
#endif
#ifdef REZARPS 
		case REZA_RPS:
			{
				CUIManager* pUIManager = CUIManager::getSingleton();
				RezaRPS* pRezaRPS = pUIManager->GetRezaRPS();
				if (pRezaRPS != NULL)
					pRezaRPS->do_RezaRPS(istr);
			}
			break;
#endif
#ifdef REZABOT
case REZA_REZABOT:
			{
				CUIManager* pUIManager = CUIManager::getSingleton();
				ReZaBotUI* pRezaBot = pUIManager->GetReZaBotUI();
				if (pRezaBot != NULL)
					pRezaBot->do_ReZaBotUI(istr);
			}
			break;
#endif
#ifdef PLAYER_COLOR_201705
case REZA_REZEXTRAS:
	{
		CUIManager* pUIManager = CUIManager::getSingleton();
		Rezextras* pRezextra = pUIManager->GetRezextras();
				if (pRezextra != NULL)
					pRezextra->DoRezextra(istr);
	}

	break;
#endif
#ifdef SET_FUSION

#endif
#ifdef REZAMOG 
case REZA_TRANSMOG:
	{
		CUIManager* pUIManager = CUIManager::getSingleton();
		RezaMog* pRzaMog = pUIManager->GetRezamog();
				if (pRzaMog != NULL)
					pRzaMog->DoRezaMog(istr);
	}
	break;

#endif
#ifdef DAILY_LOGIN
case REZA_DAILY_LOGIN:
	{
		CUIManager* pUIManager= CUIManager::getSingleton(); 
		DailyLogin* pDailyLogin = pUIManager->GetRezaDailyLogin();
		if(pDailyLogin!=NULL) 
		pDailyLogin->do_DailyLoginUI(istr);
	}
	break; //add 03092022


#endif
case REZA_RLGL:
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	RLGL* pRezaRLGL = pUIManager->GetRLGL();
	if (pRezaRLGL != NULL)
		pRezaRLGL->do_RLGL(istr);
}
break;
		default :
			break; 

		}
	}




int iCanMove = 0; 
void SetMove(int v)
{
	iCanMove = v; 
}

bool CantMove(){
	
	if (iCanMove >1 ) 
	{ iCanMove= 1 ;} 
	if (iCanMove <1 ) {
		iCanMove = 0;
	}

	return iCanMove==1;
}
