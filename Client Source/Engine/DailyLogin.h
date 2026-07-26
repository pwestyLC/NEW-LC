#ifndef	DAILY_LOGIN_UI_H_
#define	DAILY_LOGIN_UI_H_


class CUIText;
class CUIArray;
class CUIIcon;

class ENGINE_API DailyLogin : public CUIWindow
{
public:
	
	
	DailyLogin();
	~DailyLogin();
	//void				Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight );
	void				initialize();
	


	void				OpenDailyLoginReq();
	void				OpenDailyLogin(CNetworkMessage* istr);

	void				CloseDailyLogin();
	
	BOOL				CloseWindowByEsc()	{ CloseDailyLogin(); return TRUE; }

public:

	void				ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void				AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void				OnRender(CDrawPort* pDraw);
	void				Render();

private:

	void				Reset();
	void				Clear();
	int m_precolor;
	CUIText*			m_pDrag;
	UIRect				m_rcOriginPos;
	bool				m_bDrag;
	int					m_nOriX, m_nOriY;
	
#pragma region Network Handles
public:
	enum DPACK {

		OpenD = 0,
		DClaim = 1, 
		DLError,

	};
	void do_DailyLoginUI(CNetworkMessage* istr);
private:
#pragma endregion 
#pragma region WindowHandles

#pragma region MouseHandles
	// Msg Proc
//	WMSG_RESULT MouseMessage(MSG* pMsg);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT	OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
#pragma endregion 

private:

	enum 
	{
		eBTN_CLOSE = 0, 
		eBTN_CLAIM =1,
		eBTN_MAX

	};
	CUIButton* m_pbtn[eBTN_MAX]; 
	CUIIcon* icons[35] ;
	CUIImage* CHEKEKS[35]; 
	CUIImage* Marker ; 

	CUIText* DCDisplay;// = (CUIText*) findUI("DCount");
	
	time_t timed;
	CUIText* TimerDisplay;//(CUIText*) findUI("nextdtimer");

	int attendance;
	
	void ClaimButton();
#pragma endregion 

};



#endif