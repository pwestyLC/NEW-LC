#include "StdH.h"
#include <Engine/Interface/UIInternalClasses.h>

#include <Engine/GameDataManager/GameDataManager.h>
#include <Common/Packet/ptype_reserved_gm_command.h>
#include <Engine/Network/CNetwork.h>
#include <Engine/Help/Util_Help.h>


#include <Engine/Interface/UIInventory.h>

#include <Engine/Contents/function/PremiumChar.h>

#include <Engine/Interface/UIButton.h>
#include <Engine/Interface/UICheckButton.h>
#include <Engine/Interface/UIComboBox.h>
#include <Engine/Interface/UISlideBar.h>

#include <Engine/Contents/Base/UIMsgBoxMgr.h>

#include <Engine/Entities/InternalClasses.h>
#include <Engine/Templates/DynamicContainer.cpp>
#include <Engine/Templates/StaticArray.cpp>

#include <Engine/Math/Placement.h>
//#include <Engine/Graphics/Adapter.h>

#include <EntitiesMP\common\Flags.h>


#include "Reza.h" 
#include "rlgl.h"
#include "Sound/SoundObject.h"
 


#pragma region Overides

WMSG_RESULT RLGL::OnLButtonDown(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if (m_pDrag && m_pDrag->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}

	if (m_pebtest && m_pebtest->OnLButtonDown(x, y))
	{
		m_pebtest->SetFocus(TRUE);
		return WMSG_SUCCESS;
	}
	CUIManager::getSingleton()->RearrangeOrder(UI_RLGL, TRUE);


	return CUIBase::OnLButtonDown(x, y);
}

WMSG_RESULT RLGL::OnLButtonUp(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->ResetHoldBtn();

	return CUIBase::OnLButtonUp(x, y);
}

WMSG_RESULT RLGL::OnLButtonDBLClick(UINT16 x, UINT16 y) {

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	return CUIWindow::OnLButtonDBLClick(x, y);
}
#include <Engine\Entities\ItemData.h>
WMSG_RESULT RLGL::OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg)
{
	if (m_bHide)
		return WMSG_FAIL;

	bool clearicontooltip = false;


	if (!clearicontooltip) {
		CUITooltipMgr::getSingleton()->clearTooltip();
	}


	if (m_bDrag && (pMsg->wParam & MK_LBUTTON))
	{
		int ndX = x - m_nOriX;
		int ndY = y - m_nOriY;

		m_nOriX = x;
		m_nOriY = y;

		Move(ndX, ndY);
		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	CUIManager::getSingleton()->SetMouseCursorInsideUIs();

	return CUIBase::OnMouseMove(x, y, pMsg);
}


WMSG_RESULT RLGL::OnKeyMessage(MSG* pMsg)
{
	//if (m_bRecvRank == TRUE)
	//	return WMSG_SUCCESS;

	if (m_pebtest == NULL)
		return WMSG_FAIL;

	if (m_pebtest->IsFocused() == FALSE)
		return WMSG_FAIL;
	//m_pebsearch->OnKeyMessage(pMsg);

	switch (pMsg->wParam)
	{
	case VK_RETURN:
	{
		//SearchRankList(curpage);
	}
	break;
	}
	return WMSG_FAIL;
}

WMSG_RESULT RLGL::OnCharMessage(MSG* pMsg)
{
	if (m_pebtest == NULL)
		return WMSG_FAIL;

	if (m_pebtest->IsFocused() == FALSE)
		return WMSG_FAIL;

	return WMSG_FAIL;
}

WMSG_RESULT RLGL::OnIMEMessage(MSG* pMsg)
{

	if (m_pebtest == NULL)
		return WMSG_FAIL;

	if (m_pebtest->IsFocused() == FALSE)
		return WMSG_FAIL;

	return WMSG_FAIL;
}


void RLGL::KillFocusEditBox()
{
	if (m_pebtest == NULL)
		return;

	m_pebtest->SetFocus(FALSE);
}
#pragma endregion

RLGL::RLGL(void)
	:
	m_pDrag(NULL)
	, m_nOriX(0), m_nOriY(0), m_bDrag(0),
	m_pebtest(NULL)
{
	setInherit(false);
}

RLGL::~RLGL()
{
	Destroy();
}

void RLGL::initialize()
{

	cso = new CSoundObject();

	m_pDrag = (CUIText*)findUI("text_drag");
	if (m_pDrag)
	{
		int l = m_pDrag->GetPosX();
		int t = m_pDrag->GetPosY();
		int r = l + m_pDrag->GetWidth();
		int b = t + m_pDrag->GetHeight();

		setTitleRect(l, t, r, b);
	}

	m_pDrag = (CUIText*)findUI("text_drag");


	int i;
 
	std::string strBtnId[eBTN_MAX] = { "btn_close"  , "btn_closestart"  , "btn_closefinish" 
		, "btn_openstart" , "btn_openfinish" , "btn_tele1" , "btn_tele2" , "btn_tele3" , "btn_start" , "btn_stop", "btn_color1" , "btn_color2" , "btn_startbgm" , "btn_stopbgm" };

	for (i = 0; i < eBTN_MAX; ++i)
		m_pbtn[i] = (CUIButton*)findUI(strBtnId[i].c_str());


	if (m_pbtn[eBTN_CLOSE] != NULL)
	{
		m_pbtn[eBTN_CLOSE]->SetCommandFUp(boost::bind(&RLGL::CloseRLGL, this));
	}

	for (i = eBTN_CLOSEGATE1; i < eBTN_MAX; i++) {
		m_pbtn[i]->SetCommandFUp(boost::bind(&RLGL::GMBUTTONS, this, i));
	}


	m_pebtest = (CUIEditBox*)findUI("eb_search");

	if (m_pebtest)
		m_pebtest->SetEnable(TRUE);

	

	m_pWaitRoomTab = (CUIBase*)findUI("WaitRoom");; //WaitRoom


	m_pGameStatsTab = (CUIBase*)findUI("GameStats");; //GameStats



	m_countertime = 0;
	m_remaintime = 0;

	m_pCounterTab = (CUIBase*)findUI("counter");; //counter
	m_pGMTab = (CUIBase*)findUI("GM-MENU");; //GM-MENU

	m_pIAOnes = (CUIImageArray*)findUI("ones");; //ones
	m_pIATens = (CUIImageArray*)findUI("tens");; //tens




}

void RLGL::ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	SetPos((pixMaxI + pixMinI - GetWidth()) / 2, (pixMaxJ + pixMinJ - GetHeight()) / 2);
	m_rcOriginPos.SetRect(m_nPosX, m_nPosY, m_nWidth, m_nHeight);
}
void RLGL::AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	if (m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ)
		ResetPosition(pixMinI, pixMinJ, pixMaxI, pixMaxJ);
}

std::string convertSecondsToTimeString(int seconds) {
	int minutes = seconds / 60;
	int remainingSeconds = seconds % 60;

	// Use std::setw to set the width of the output to ensure two digits for both minutes and seconds
	std::ostringstream timeString;
	timeString << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << remainingSeconds;

	return timeString.str();
}
bool fuckcountdown = false;
void RLGL::OnRender(CDrawPort* pDraw)
{
	CUIWindow::OnRender(pDraw);

	if (m_bHide)
		return;
	if (m_pCounterTab && m_countertime != 0)
	{
		if (m_pCounterTab->IsVisible())
		{
			int timenw = time(NULL);
			int timediff = m_countertime - timenw;


			if (m_countertime == 0 || timediff < 0)
			{
				m_pCounterTab->Hide(true);
				m_countertime = 0;
				return;
			}

			if (!fuckcountdown)
			{
				if (timediff > 3)
					fuckcountdown = true;
			}
			int ones = 0;
			int tens = 0;
			int hundreds = 0; 

			// Extract ones and tens places
			ones = timediff % 10;        // Extract the ones place
			tens = (timediff / 10) % 10; // Extract the tens place
			hundreds = (timediff / 100) % 10; // Extract the hundreds place 

			m_pIAOnes->SetRenderIdx(ones);
			m_pIATens->SetRenderIdx(tens);
			if (fuckcountdown) {
				if (ones == 3 && tens == 0)
				{

					CPlayerEntity* penplayer = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
					penplayer->StopBGM(CTFILENAME(""));

					cso->Play_t(CTFILENAME("Data\\Sounds\\countdown.ogg"), SOF_LOCAL);
					fuckcountdown = false;
				}
			}


		}
	}

	if (m_pGameStatsTab && m_remaintime !=0)
	{
		if (m_pGameStatsTab->IsVisible())
		{
			

			int timenw = time(NULL);
			int timediff = m_remaintime - timenw;

			if (m_remaintime == 0 || timediff < 0)
			{
				m_remaintime = 0;
				return;
			}


			 
			CUIText* ctb; 
			ctb = (CUIText*)m_pGameStatsTab->findUI("stat3val");
			ctb->SetText(CTString(convertSecondsToTimeString(timediff).c_str()));


		}
	}


}

void RLGL::Render() {

	CUIWindow::Render();
}

void RLGL::SetTitle(CTString Title) {

	CUIText* m_pTitle = (CUIText*)findUI("text_title");
	m_pTitle->SetText(Title);
}

void RLGL::OpenRLGL(int gm)
{
	CUIManager::getSingleton()->RearrangeOrder(UI_RLGL, TRUE);
	SetPos(m_rcOriginPos.Left, m_rcOriginPos.Top);
	SetVisible(TRUE);
	Hide(FALSE);

	if (gm >= 10) {
		m_pGMTab->Hide(false);
		this->SetSize(200, 620);

	}
	else
	{
		m_pGMTab->Hide(true);
		this->SetSize(200, 240);
	}

	CPlayerEntity* penplayer = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
	penplayer->StopBGM(CTFILENAME(""));


}

void RLGL::CloseRLGL()
{
	Clear();


	Hide(TRUE);
	SetVisible(FALSE);
	CUIManager::getSingleton()->RearrangeOrder(UI_RLGL, FALSE);
}

void RLGL::Reset()
{
	if (m_pebtest)
	{
		m_pebtest->ResetString();
		m_pebtest->SetFocus(FALSE);
	}

}

void RLGL::Clear()
{
	Reset();
}
 

void RLGL::do_RLGL(CNetworkMessage* istr) {

	int type = 0;
	(*istr) >> type;
	switch (type)
	{
	case MSG_RLGL_OPEN:
	{
		int gm = 0;
		(*istr) >> gm;

		OpenRLGL(gm);

	}
	break; 
	case MSG_RLGL_CLOSE:
	{
		int gm = 0;
		(*istr) >> gm;

		CloseRLGL();

	}
	break;

	case MSG_RLGL_STARTLINE:
	{
		BarrierDelete(istr);
	}
	break;
	case MSG_RLGL_FINISHLINE:
	{
		BarrierStart(istr);
	}
	break;
	case MSG_RLGL_LIGHT:
	{

		int gm = 0;
		(*istr) >> gm;

		switch (gm) {
		case MSG_RLGL_GM_COLOR1:
		{

			Set2dModelColorGreen(istr);
		}
			break;
		case MSG_RLGL_GM_COLOR2: 
		{
			Set2dModelColorRed(istr);
		}
			break;

		}
	}
	break;
	case MSG_RLGL_GM:
	{
		int gm = 0;
		(*istr) >> gm;

		switch (gm) 
		{
			case MSG_RLGL_GM_STARTBGM:
			{

				//CTFileStream* cts = new CTFileStream();
				//cts->Open_t(CTFILENAME("Data\\Sounds\\rlgl.ogg"), CTStream::OpenMode::OM_READ);

				cso->Stop();
				cso->Play_t(CTFILENAME("Data\\Sounds\\rlglbitchsinging.ogg"), SOF_LOOP);

				/*
				CPlayerEntity* penplayer = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
				penplayer->PlayBGM(CTFILENAME("Data\\Sounds\\rlgl.ogg"));

				penplayer->*/
			}
			break;
			case MSG_RLGL_GM_STOPBGM:
			{
				CPlayerEntity* penplayer = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
				penplayer->StopBGM(CTFILENAME(""));


				cso->Stop();  
				cso->Play_t(CTFILENAME("Data\\Sounds\\rlglhornstop.ogg"), SOF_LOCAL);

				//cso->Stop();
			}
			break;	
			case MSG_RLGL_GM_TIME:
			{
				int time = 0;
				(*istr) >> time;
				m_countertime = time;
				m_pCounterTab->Hide(false);
				m_pIAOnes->SetRenderIdx(0);
				m_pIATens->SetRenderIdx(0);

			}
			break; 
			case MSG_RLGL_GM_GAMESTAT:
			{
				CPlayerEntity* penplayer = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
				penplayer->StopBGM(CTFILENAME(""));

				m_pWaitRoomTab->Hide(true);
				m_pGameStatsTab->Hide(false);

				int mtime = 0,
					alive = 0,
					eliminated = 0;
				CTString
				placeone,
				placetwo,
				placetree;

				(*istr) >> mtime 
					>> alive 
					>> eliminated 
					>> placeone 
					>> placetwo 
					>> placetree;
				//user counter tab to show placement
				//
				char buffer[100] = { 0 };
				CUIText* ctb;

				itoa(alive, buffer, 10);
				ctb = (CUIText*)m_pGameStatsTab->findUI("stat1val");
				ctb->SetText(CTString(buffer));

				itoa(eliminated, buffer, 10);
				ctb = (CUIText*)m_pGameStatsTab->findUI("stat2val");
				ctb->SetText(CTString(buffer));
				 

				m_remaintime = mtime;
				int timenw = time(NULL);
				int timediff = m_remaintime - timenw;

				ctb = (CUIText*)m_pGameStatsTab->findUI("stat3val");
				ctb->SetText(CTString(convertSecondsToTimeString(timediff).c_str()));

				ctb = (CUIText*)m_pGameStatsTab->findUI("stat4val");
				ctb->SetText(placeone);

				ctb = (CUIText*)m_pGameStatsTab->findUI("stat5val");
				ctb->SetText(placetwo);

				ctb = (CUIText*)m_pGameStatsTab->findUI("stat6val");
				ctb->SetText(placetree);



			}
			break;

		}
	}
		break;
	case MSG_RLGL_TAB: 
	{
		CPlayerEntity* penplayer = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
		penplayer->StopBGM(CTFILENAME(""));

		int tab = 0;
		(*istr) >> tab;

		switch (tab)
		{
			case 0: // waitroom 
			{
				m_pWaitRoomTab->Hide(false);
				m_pGameStatsTab->Hide(true);

			
			}
			break;
			case 1: // game stats
			{
				m_pWaitRoomTab->Hide(true);
				m_pGameStatsTab->Hide(false);
			}
			break;
		}
	
	}
		break;

	case MSG_RLGL_STARTZONEPROMPT:
	{

	}
		break;

	default:
	{
		//Nothing
	}
	break;
	}

}


void RLGL::GMBUTTONS(int i)
{
	i = i - eBTN_CLOSEGATE1;
	  
	CNetworkMessage RLGLGM((UBYTE)MSG_REZA);
	RLGLGM << (DWORD)REZA_RLGL;
	RLGLGM << (DWORD)MSG_RLGL_GM;
	RLGLGM << (DWORD)i;
	_pNetwork->SendToServerNew(RLGLGM);

}


#define EC_EStop 0x00000000
#define EC_EStart 0x00000001

void RLGL::BarrierStart(CNetworkMessage* istr)
{
	//init vars
	int iBarrier = -1;
	int iForceField = -1;
	int iZone = -1;
	
	//out of packet
	(*istr) >> iZone;
	(*istr) >> iBarrier;
	(*istr) >> iForceField;

	//find barrier
	CEntity* pBarrier = NULL;
	pBarrier = _pNetwork->ga_World.EntityFromID(iBarrier);

	
	//set collision
	if (pBarrier != NULL)
	{
		(pBarrier)->SetCollisionFlags(ECF_BRUSH);
	}



	//forcefield remove
	CEntity* pForceField = NULL;
	pForceField = _pNetwork->ga_World.EntityFromID(iForceField);

	if (pForceField)
	{
		CEntityEvent* ee = new CEntityEvent(EC_EStart);
		pForceField->SendEvent(*ee);
		delete ee;
	}

	
}

void RLGL::BarrierDelete(CNetworkMessage* istr)
{
	//init vars
	int iBarrier = -1;
	int iForceField = -1;
	int iZone = -1;

	//out of packet
	(*istr) >> iZone;
	(*istr) >> iBarrier;
	(*istr) >> iForceField;
	 
	//find barrier
	CEntity* pBarrier = NULL;
	pBarrier = _pNetwork->ga_World.EntityFromID(iBarrier);
	
	//set collision
	if (pBarrier != NULL)
	{
		(pBarrier)->SetCollisionFlags(ECF_MODEL_NO_COLLISION);  
	}


	//forcefield remove
	CEntity* pForceField = NULL;
	pForceField = _pNetwork->ga_World.EntityFromID(iForceField);

	if (pForceField)
	{
		CEntityEvent* ee = new CEntityEvent(EC_EStop);
		pForceField->SendEvent(*ee);
		delete ee; 
	}


}





void RLGL::Set2dModelColorGreen(CNetworkMessage* istr)
{
	//init vars
	int model = -1;
	int count = 0;
	int iZone = -1;

	//out of packet
	(*istr) >> iZone;
	(*istr) >> count;

	
	for (int i = 0; i < count; i++)
	{
		(*istr) >> model; 
		//find barrier
		CEntity* pModel = NULL;
		pModel = _pNetwork->ga_World.EntityFromID(model);

		//set collision
		if (pModel != NULL)
		{
			(pModel)->SetModelColor(0x00FF00ff);
		}
	}
	 

}
void RLGL::Set2dModelColorRed(CNetworkMessage* istr)
{
	//init vars
	int model = -1;
	int count = 0;
	int iZone = -1;

	//out of packet
	(*istr) >> iZone;
	(*istr) >> count;


	for (int i = 0; i < count; i++)
	{
		(*istr) >> model;
		//find barrier
		CEntity* pModel = NULL;
		pModel = _pNetwork->ga_World.EntityFromID(model);

		//set collision
		if (pModel != NULL)
		{
			(pModel)->SetModelColor(0xFF0000ff);
		}
	}

}



//gamestat  display

//display numbers


//display redlightgreenlight 
