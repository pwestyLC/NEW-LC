#ifndef	_REZA_BOT_UI_H_
#define	_REZA_BOT_UI_H_


#include <Engine/Interface/UIInternalClasses.h>


class CUISlideBar;
class CUIText;
class CUIArray;
class CUITab;
class CUICheckButton;
class CUITextBox;
class CUIList;
class CUIImageSplit;
class CUIScrollBar; 

class ENGINE_API ReZaBotUI : public CUIWindow
{
#define MAX_BOTHISTORY 50
#pragma region Objects and Variables

	enum REZABOTMSG
	{
		REZABOT_OPEN =68 ,
		REZABOT_START,
		REZABOT_STOP,
		REZABOT_CHECK,

	};
	//buttons
	enum
	{
		eBTN_CLOSE = 0, 
		eBTN_MINI,
		eBTN_START,
		eBTN_MOVETEST,
		eBTN_MAX
	};
	//edit boxes	
	enum 
	{
		eEDIT_MAXDIST = 0,
		eEDIT_HPSKILL1,
		eEDIT_HPSKILL2,
		eEDIT_MPSKILL1,
		eEDIT_MPSKILL2,
		eEDIT_HPBUFF1,
		eEDIT_HPBUFF2,
		eEDIT_MPBUFF1,
		eEDIT_MPBUFF2,

		eEDIT_HPITEM1,
		eEDIT_HPITEM2,
		eEDIT_MPITEM1,
		eEDIT_MPITEM2,

		eEDIT_MAX
	};
	//icons
	enum 
	{
		eICON_SKILL1 = 0,
		eICON_SKILL2,
		eICON_SKILL3,
		eICON_SKILL4,
		eICON_SKILL5,
		eICON_SKILL6,
		eICON_SKILL7,
		eICON_SKILL8,
		eICON_HPSKILL1,
		eICON_HPSKILL2,
		eICON_MPSKILL1,
		eICON_MPSKILL2,
		eICON_BUFF1,
		eICON_BUFF2,
		eICON_BUFF3,
		eICON_BUFF4,
		eICON_BUFF5,
		eICON_BUFF6,
		eICON_BUFF7,
		eICON_BUFF8,
		eICON_HPBUFF1,
		eICON_HPBUFF2,
		eICON_MPBUFF1,
		eICON_MPBUFF2,
	eICON_SKILLS_END = eICON_MPBUFF2,

		eICON_HPITEM1,
		eICON_HPITEM2,
		eICON_MPITEM1,
		eICON_MPITEM2,
		eICON_PETFEED1,
		eICON_PETFEED2,
		eICON_TIMERITEM1,
		eICON_TIMERITEM2,
		eICON_TIMERITEM3,
		eICON_TIMERITEM4,
		eICON_BOTTICKET,
		eICON_MAX
	};
	//check boxes
	enum 
	{
		eCHK_ATK = 0,
		eCHK_DEF,
		eCHK_WANDER,
		eCHK_RETURN,
		eCHK_SKILL,
		eCHK_BUFF,
		eCHK_ITEM,
		eCHK_IG1,
		eCHK_IG2,
		eCHK_IG3,
		eCHK_IG4,
		eCHK_PICKUP,
		eCHK_P1PICKUP,
		eCHK_SELLTOSHOP,

		eCHK_MAX
	};

	enum BotAction{
		ACT_ITEM = 0 ,
		ACT_ATK,
		ACT_SKILL,
		ACT_BUFF,
		ACT_PICKUP,
		ACT_SEARCH,
		ACT_P1PICK,
		ACT_MAX
	}_BOTACTION;
	
	CUITab* Tab_Win;
	CUIImageSplit* Window_BG;
	CUIBase* Controls;

	int64_t nas_earned;
	CUIText* m_pTextNas;

	CUIList* m_pList; 
	CUIScrollBar* m_plistScroll;
	
	struct ListObj {  //LISTOBJECT
		CUITextBox* Text; 
	} _ListObj; 

	CUIBase* m_pListItem; //LISTOBJECT

	CUIButton* m_pBtn[eBTN_MAX]; 
	CUIEditBox* m_pEdit[eEDIT_MAX]; //eEDIT_MAXDIST
	CUIIcon* m_pIcon[eICON_MAX];
	CUICheckButton* m_pChk[eCHK_MAX];
	
	
	public:
	//bot logic variables

	
	int m_ithinktimer;
	int m_ilastThought;
	bool b_pickup;
	bool b_petpick;
	bool b_useitem;
	bool b_usebuff;
	int buffcount;
	
	int lastcount;
	int failcount;
	int pickupc;

	int skillCount;
	bool WasSkilling;
	
	
	CEntity* lasttarget;
	CEntity* lastselected;
	
	int samecheck;

	int itemCount; 

	int distmax;

	//threading
	bool bBotison;
	HANDLE RezabotTimerThread;
	//cThreadWrapper*	RezabotTimerThread; 

	FLOAT3D StartPos;
	CUIText* m_pTextCoord;
	CUIText* m_pTextDist;

	bool aftersocial;

#pragma endregion

#pragma region Functions 

public:
	ReZaBotUI();
	~ReZaBotUI();
	
	void				initialize();

	void				OpenReZaBotUI(int ticketid,int ticketvindex);
	void				OpenReZaBotUI();

	void				CloseReZaBotUI();
	void				Mini();
	float					distcalc(FLOAT3D p1, FLOAT3D p2);
	void				MoveTest();
	
	
	void				StartBot();
	void				EndBOT();
	void				Mode(int id);
	void				Positioning(int id);
	void				Ignition(int lvl);
	void				UpdateEP(int lvl);

	BOOL				CloseWindowByEsc()	{ CloseReZaBotUI(); return TRUE; }

	void				Reset();
	void				Clear();

	//LISTBOX HANDLES
	void AddText(char* SystemName , char* text);
	void OutTextUpdate();
	private:
	void tacobuttplug(); 
	public:
	bool IsItemMatched( CItems* pItem ,int slot);
	bool CheckItem( CItems* pItem ,int slot);
	bool CheckSkillIcon( CSkill* Skill , bool Buff );

	private:
	void anotherbuttplug();
	public:
	bool IdleCheck();
	BotAction Think();
	void DoAction(BotAction Action);
	
	bool SearchEnemy();

	void UseSocialAction(int index);
	void PickUpItems();

	void UseBuff(int SkillIdx);
	bool UseBuffs();

	void UseSkill(int SkillIdx);
	void UseSkills();
	void UseItem(CItems* item , int index);
	bool UseItems();

	

	static UINT WINAPI	HandleTimer(void *parameter);
#pragma endregion


	//NETWORK HANDLE
public:
	void do_ReZaBotUI(CNetworkMessage* istr);

 


	//WINDOW FORM FUN

	void				CheckTime();

	void				UpdateMoney (int64_t value);

	void				OnRender(CDrawPort* pDraw);
	void				Render();
	void				ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void				AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );

private:

	CUIText*			m_pDrag;
	UIRect				m_rcOriginPos;
	bool				m_bDrag;
	int					m_nOriX, m_nOriY;

	BOOL checkparentshidden(CUIBase* checkhidden);
	WMSG_RESULT HandleIconDrag(UINT16 x , UINT16 y);
	// Msg Proc
//	WMSG_RESULT MouseMessage(MSG* pMsg);
	WMSG_RESULT OnLButtonDBLClick(UINT16 x, UINT16 y );
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT	OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	//edit box focus
	BOOL IsEditBoxFocused();
	void KillFocusEditBox();

void _resetIcon( int nSlotIdx );
public:
	
	#define DREZABOTX 379
	#define DREZABOTY 300
	#define DREZABOTW 115
	#define DREZABOTH 130
		UIRectUV		m_rtREZABOT;
		UIRect			m_rcREZABOT;


	void RenderBotHead(FLOAT3D vPopupPos,FLOAT fPopupZ, CEntity* pTarget, int isPC);

	void DrawBotting( int nX, int nY,int nZ, char botting, FLOAT fRatio );
};



#endif //UI_SETFUSION_H_