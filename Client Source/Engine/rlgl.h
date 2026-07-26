#ifndef UI_RLGL_H_
#define UI_RLGL_H_


class CUISlideBar;
class CUIArray;
class	CUIBase;
class	CUIButton;
class	CUIText;
class	CUIImage;
class CUIIcon;
class CUIProgressBar;
class CUICheckButton;

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
	MSG_RLGL_GM_CLOSEGATE1 = 0,
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
class ENGINE_API RLGL : public CUIWindow
{
public:
	RLGL();
	~RLGL();
	void				initialize();

	void				OpenRLGL(int gm); 
	void				CloseRLGL();
	void				ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);
	void				AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);
	void				OnRender(CDrawPort* pDraw);
	void				Render();
	void				Reset();
	void				Clear();

	BOOL				CloseWindowByEsc() { CloseRLGL(); return TRUE; }

	void SetTitle(CTString title);

#pragma region variables

	CUIText*			m_pDrag;
	UIRect				m_rcOriginPos;
	bool				m_bDrag;
	int					m_nOriX, m_nOriY;
	 
private:

	enum
	{
		eBTN_CLOSE = 0,
		//GMBUTTONS
		eBTN_CLOSEGATE1,
		eBTN_CLOSEGATE2,
		eBTN_OPENGATE1,
		eBTN_OPENGATE2,
		eBTN_TELE1,
		eBTN_TELE2,
		eBTN_TELE3,
		eBTN_START,
		eBTN_STOP, 
		eBTN_COLOR1,
		eBTN_COLOR2,
		eBTN_STARTBGM,
		eBTN_STOPBGM,
		eBTN_MAX
	};
	CUIButton* m_pbtn[eBTN_MAX];
	CUIEditBox* m_pebtest;

	CUIBase* m_pWaitRoomTab; //WaitRoom
	CUIBase* m_pGameStatsTab; //GameStats

	int m_countertime;
	int m_remaintime;
	CUIBase* m_pCounterTab; //counter 
	CUIBase* m_pGMTab; //GM-MENU 
	CUIImageArray* m_pIAOnes;//ones
	CUIImageArray* m_pIATens; //tens


	CSoundObject* cso;


public:
#pragma region MouseHandles

	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonDBLClick(UINT16 x, UINT16 y);
	WMSG_RESULT	OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);

	WMSG_RESULT OnKeyMessage(MSG* pMsg);

	WMSG_RESULT OnCharMessage(MSG* pMsg);

	WMSG_RESULT OnIMEMessage(MSG* pMsg);
	virtual BOOL		IsEditBoxFocused()
	{
		if (m_pebtest)
		{
			return m_pebtest->IsFocused();
		}

		return FALSE;
	}
	void KillFocusEditBox();
#pragma endregion 

	void do_RLGL(CNetworkMessage* istr);
	
	void GMBUTTONS(int i);

	void BarrierStart(CNetworkMessage * istr);

	void BarrierDelete(CNetworkMessage * istr);

	void Set2dModelColorRed(CNetworkMessage * istr);

	void Set2dModelColorGreen(CNetworkMessage * istr);


};

#endif 