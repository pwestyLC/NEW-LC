#include "StdH.h"
#include <Engine/Interface/UIInternalClasses.h>

#include <Engine/GameDataManager/GameDataManager.h>
#include <Common/Packet/ptype_reserved_gm_command.h>
#include <Engine/Network/CNetwork.h>
#include <Engine/Help/Util_Help.h>

//#include "DailyLogin.h"
#include "Reza.h"


#include <Engine/Contents/function/PremiumChar.h>

#include <Engine/Interface/UIButton.h>
#include <Engine/Interface/UICheckButton.h>
#include <Engine/Interface/UIComboBox.h>
#include <Engine/Interface/UISlideBar.h>


#include <Engine/Contents/Base/UIMsgBoxMgr.h>

//#include <Engine/Graphics/Adapter.h>

int GetDaysInMonth() {
	time_t today =time(NULL) ;

	tm* t = localtime(&today);

	int month = t->tm_mon + 1;

	int year = t->tm_year+1900;


	int numberOfDays;

	if (month == 4 || month == 6 || month == 9 || month == 11)
		numberOfDays = 30;
	else if (month == 2)
	{
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (isLeapYear)
			numberOfDays = 29;
		else
			numberOfDays = 28;
	}
	else
		numberOfDays = 31;

	return numberOfDays;
}
int GetDaysInMonth(time_t fuck) {
	time_t today =fuck ;

	tm* t = localtime(&today);

	int month = t->tm_mon + 1;

	int year = t->tm_year+1900;


	int numberOfDays;

	if (month == 4 || month == 6 || month == 9 || month == 11)
		numberOfDays = 30;
	else if (month == 2)
	{
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (isLeapYear)
			numberOfDays = 29;
		else
			numberOfDays = 28;
	}
	else
		numberOfDays = 31;

	return numberOfDays;
}

DailyLogin::DailyLogin(void)
	:
		m_pDrag(NULL)
	,	m_nOriX(0), m_nOriY(0)
{
	
	setInherit(false);		// â �ȿ� ���� MsgProc â���� ��ȭ. �ٸ��� ��� ����
	
}

DailyLogin::~DailyLogin()
{
	Destroy();
}

void DailyLogin::initialize()
{
	timed=0; 
	//tnow = 0;
	attendance = 0;
	m_pDrag = (CUIText*)findUI("text_drag");
	

	int i;
	std::string strBtnId[eBTN_MAX] = { "btn_close" ,"btnClaim" };

	for (i = 0; i < eBTN_MAX; ++i)
		m_pbtn[i] = (CUIButton*)findUI(strBtnId[i].c_str());

	if( m_pbtn[eBTN_CLOSE] != NULL)
	{
		m_pbtn[eBTN_CLOSE]->SetCommandFUp(boost::bind(&DailyLogin::CloseDailyLogin, this));
	}

if( m_pbtn[eBTN_CLAIM] != NULL)
	{
		m_pbtn[eBTN_CLAIM]->SetCommandFUp(boost::bind(&DailyLogin::ClaimButton, this));
	}

	
	for(int i = 0; i < 35 ; i ++)  { 
		icons[i] = 0x0 ; 

	}

	char buffer[255] = "" ;

	int curweek = 0; 
	int curday= 0;
	int totalday= 0;
	for(curweek = 0 ; curweek < 5; curweek ++){

		for(curday= 0 ; curday < 7; curday ++)
		{
			
			_snprintf(buffer,255,"w%dd%d",curweek+1,curday+1);
			//const_cast<char*>
			icons[totalday] = (CUIIcon*) findUI((buffer));
			icons[totalday]->clearIconData();

			if(totalday > GetDaysInMonth()-1 )
			{
				icons[totalday]->getParent()->Hide(TRUE);
			}
			totalday++;
		}

	}
	DCDisplay = (CUIText*) findUI("DCount");
	TimerDisplay = (CUIText*) findUI("nextdtimer");

	for(int i = 0 ; i < 35 ; i++ ) {
	
		_snprintf(buffer, 255, "check%d" , i+1 );  
		CHEKEKS[i]  = (CUIImage*) findUI(buffer) ; 
		if(CHEKEKS[i] != NULL )
		CHEKEKS[i]->Hide(TRUE);
	
	}

	Marker = (CUIImage*) findUI("Result") ; 
	Marker->Hide(TRUE);




}

void DailyLogin::Render(){
	
	CUIWindow::Render();

}
void DailyLogin::OnRender(CDrawPort* pDraw){
	
	CUIWindow::OnRender(pDraw);
	char buffer[100];
	
	
		if(_pUIBuff->IsSkillBuff(1060)){
			BuffInfo* pBuff = _pUIBuff->GetBuffInfoSkill(1060);
		
			__int64	llCurTime = _pTimer->GetHighPrecisionTimer().GetSeconds();
			int secsdiff =  ((pBuff->m_llStartTime / 1000) + (pBuff->m_slRemain / 10)) - llCurTime;
			int hour = ((int)secsdiff / 60/60) - ((int)((int)((int)(secsdiff / 60) / 60)/60) * 60);
			int min = ((int)secsdiff/60) - ((int)((int)(secsdiff/60) / 60) * 60);
			int sec = ((int)secsdiff) - ((int)((int)secsdiff / 60 ) *60);
			
			m_pbtn[eBTN_CLAIM]->SetEnable(FALSE);


			_snprintf(buffer, 255, "%dH,%dM,%dS \n", hour , min , sec);
			TimerDisplay->SetText(CTString(buffer));
			
			
		}
	

	else{

	//	if(attendance == 0 ) {
			m_pbtn[eBTN_CLAIM]->SetEnable(TRUE);
	//	}

	struct tm pTime;
	struct tm pTime1;

	
	time_t tServerNow;
	time(&tServerNow);
	pTime = *localtime(&tServerNow);
	pTime.tm_year += _pNetwork->tServer.tm_year;
	pTime.tm_mon += _pNetwork->tServer.tm_mon;
	pTime.tm_mday += _pNetwork->tServer.tm_mday;
	pTime.tm_hour += _pNetwork->tServer.tm_hour;
	pTime.tm_min += _pNetwork->tServer.tm_min;
	pTime.tm_sec += _pNetwork->tServer.tm_sec;
	tServerNow = mktime(&pTime);


	time_t tServerEndOfDay;
	time(&tServerEndOfDay);
	pTime1 = *localtime(&tServerEndOfDay);
	pTime1.tm_year += _pNetwork->tServer.tm_year;
	pTime1.tm_mon += _pNetwork->tServer.tm_mon;
	pTime1.tm_mday += _pNetwork->tServer.tm_mday;
	pTime1.tm_hour += _pNetwork->tServer.tm_hour;
	pTime1.tm_min += _pNetwork->tServer.tm_min;
	pTime1.tm_sec += _pNetwork->tServer.tm_sec;

	pTime1.tm_mday+= 1;
	pTime1.tm_min = 0 ;
	pTime1.tm_sec = 0 ;
	pTime1.tm_hour =0;
	tServerEndOfDay = mktime(&pTime1);

	int secsdiff = tServerEndOfDay - tServerNow;
	
	//	int secsdiff = timed - now; 
		int hours = ((int)secsdiff / 60/60) - ((int)((int)((int)(secsdiff / 60) / 60)/60) * 60);
		int minutes = ((int)secsdiff/60) - ((int)((int)(secsdiff/60) / 60) * 60);
		int seconds = ((int)secsdiff) - ((int)((int)secsdiff / 60 ) *60);
		_snprintf(buffer, 255, "%dH, %dM, %dS \n", hours , minutes , seconds);
		
		TimerDisplay->SetText(CTString(buffer));
	}
	/*	time_t today = time(NULL);		// 
		tm* t = localtime(&today);
		int CurrentDay = t->tm_mday;
		if(attendance === 0 )
		if(CHEKEKS[CurrentDay-1]->GetHide() == TRUE) m_pbtn[eBTN_CLAIM]->SetEnable(TRUE);
		else m_pbtn[eBTN_CLAIM]->SetEnable(FALSE);
*/
}

void DailyLogin::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
	m_rcOriginPos.SetRect(m_nPosX, m_nPosY, m_nWidth, m_nHeight);
}
void DailyLogin::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

void DailyLogin::OpenDailyLoginReq()
{
	
	if(this->IsVisible() != FALSE)
		return;

	Hide(TRUE);
	SetVisible(FALSE);

	CNetworkMessage ProcDailyLogin((UBYTE)MSG_REZA);
	ProcDailyLogin << (DWORD)REZA_DAILY_LOGIN;
	ProcDailyLogin << (DWORD)OpenD;
	_pNetwork->SendToServerNew(ProcDailyLogin);


}
void DailyLogin::OpenDailyLogin(CNetworkMessage* msg){

	int DaysInMonth = GetDaysInMonth();  //	28-31


	SetPos( m_rcOriginPos.Left, m_rcOriginPos.Top );
	Reset();

	char buffer[255] = { 0x0 } ; 
	
	int DCount = 1;
	(*msg) >> DCount; 
	(*msg) >> attendance;
	//(*msg) >> timed;
	
	//ULONGLONG  ttnow = 0 ; 
	//(*msg) >> ttnow;
	//tnow = ttnow;
	//tnow = tnow - time(NULL);

	//timed = time(NULL) + timed;


	for(int i= 0 ; i < 35 ; i ++ )  {
		
		int tempidx=  0 ; 
		int count= 0 ; 
		int flag = 0 ; 
		int plus = 0 ;

		int bcheck = 0;

		(*msg) >> bcheck;
		if(CHEKEKS[i] != NULL)
		{
			CHEKEKS[i]->Hide(bcheck ==0 ? TRUE : FALSE );
		}

		(*msg) >> tempidx;
		(*msg) >> count;
		(*msg) >> flag; 
		(*msg) >> plus; 

		if(icons[i]!=NULL)
		{	
			if(icons[i]->getParent()->GetHide()!=TRUE){
				icons[i]->setData(UBET_ITEM, tempidx);
				icons[i]->setCount(count); 
				CItems* pItems = icons[i]->getItems();
				pItems->Item_Sum = count;
				pItems->Item_Flag = flag;
				pItems->Item_Plus = plus;
			}
		}
		

	} 
	
	_snprintf(buffer , 255 , "%d" , DCount);
	DCDisplay->SetText(CTString(buffer));
	


	struct tm pTime;
	//struct tm pTime2;

	time_t tme2;
	time(&tme2);
	pTime = *localtime(&tme2);
	pTime.tm_year += _pNetwork->tServer.tm_year;
	pTime.tm_mon += _pNetwork->tServer.tm_mon;
	pTime.tm_mday += _pNetwork->tServer.tm_mday;
	pTime.tm_hour += _pNetwork->tServer.tm_hour;
	pTime.tm_min += _pNetwork->tServer.tm_min;
	pTime.tm_sec += _pNetwork->tServer.tm_sec;


	int CurrentDay = pTime.tm_mday;

	int nx , ny ;

	icons[CurrentDay-1]->GetPos(nx,ny); 

	int nnx , nny ;

	icons[CurrentDay-1]->getParent()->GetPos(nnx,nny);
	
	nx += nnx ;
	ny += nny ;

	icons[CurrentDay-1]->getParent()->getParent()->GetPos(nnx,nny);
	nx += nnx ;
	ny += nny ;
	nx+=5;
	ny+=16;

	Marker->SetPos(nx,ny);
	Marker->Hide(FALSE);
	//end
	

	SetVisible(TRUE);
	Hide(FALSE);

	CUIManager::getSingleton()->RearrangeOrder(UI_DAILY_LOGIN, TRUE);
	
	
}

void DailyLogin::CloseDailyLogin()
{
	Reset();
	Hide(TRUE);
	SetVisible(FALSE);
	CUIManager::getSingleton()->RearrangeOrder(UI_DAILY_LOGIN, FALSE);
}

void DailyLogin::Reset()
{
	Clear();
	/*	if(GAMEDATAMGR()->GetPremiumChar()->getType() != PREMIUM_CHAR_TYPE_FIRST)
	{
		m_slRGB[0]->SetEnable(FALSE);
		m_slRGB[1]->SetEnable(FALSE);
		m_slRGB[2]->SetEnable(FALSE);
	}
	*/
	
}

void DailyLogin::Clear()
{
	DCDisplay->SetText(CTString("1")); 
}

	
	void DailyLogin::ClaimButton(){
		
			
	Hide(TRUE);
	SetVisible(FALSE);

	CNetworkMessage ProcDailyLogin((UBYTE)MSG_REZA);
	ProcDailyLogin << (DWORD)REZA_DAILY_LOGIN;
	ProcDailyLogin << (DWORD)DClaim;
	_pNetwork->SendToServerNew(ProcDailyLogin);

	m_pbtn[eBTN_CLAIM]->SetEnable(FALSE);
/*
		CUIManager* pUIMgr = UIMGR();
		
		MSGBOXMGR()->CreateMsgBoxNEW("LastChaos",
			"Would you like to claim your reward ? ",
			eMSG_YESNO
			,true
			,boost::bind(&DailyLogin::CloseDailyLogin,this)
			,boost::bind(&DailyLogin::CloseDailyLogin,this)
			,boost::bind(&DailyLogin::CloseDailyLogin,this)
			,&CTString("Claim")
			,&CTString("Wait")
			);*/
	}


#pragma region Network Handles
void DailyLogin::do_DailyLoginUI(CNetworkMessage* istr){
		int type = 0 ;
		(*istr) >> type ;

		switch (type)
		{
		case OpenD:

				OpenDailyLogin(istr);

			break;
		
		case DClaim: 
				
			break;


		case DLError:
			{
			CUIManager* pUIMgr = UIMGR();
		
			MSGBOXMGR()->CreateMsgBoxNEW("LastChaos",
				_S(9347,"not eligible"),eMSG_OK
			,true
			,boost::bind(&DailyLogin::CloseDailyLogin,this)
			,boost::bind(&DailyLogin::CloseDailyLogin,this)
			,boost::bind(&DailyLogin::CloseDailyLogin,this)
			,&CTString("OK")
			,&CTString("OK")
			);
		}
			break;

		default :
			//log and kick 
			break; 

		}
	}

#pragma endregion
#pragma region MouseHandles

WMSG_RESULT DailyLogin::OnLButtonDown( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if( m_pDrag && m_pDrag->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}


	CUIManager::getSingleton()->RearrangeOrder(UI_DAILY_LOGIN, TRUE);
	
	/*m_slRGB[0]->IsInside(x,y)
	for(int i = 0
		){

	}
	*/

	return CUIBase::OnLButtonDown(x, y);
}

WMSG_RESULT DailyLogin::OnLButtonUp( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;


	return CUIBase::OnLButtonUp(x, y);
}

WMSG_RESULT DailyLogin::OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg )
{
	if (m_bHide)
		return WMSG_FAIL;

	if( m_bDrag && ( pMsg->wParam & MK_LBUTTON ) )
	{
		int ndX = x - m_nOriX;
		int ndY = y - m_nOriY;

		m_nOriX = x;
		m_nOriY = y;

		Move( ndX, ndY );
		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;
	
	CUIManager::getSingleton()->SetMouseCursorInsideUIs();

	return CUIBase::OnMouseMove(x, y, pMsg);
}

#pragma endregion