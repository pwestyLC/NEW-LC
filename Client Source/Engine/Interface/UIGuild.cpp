#include "stdh.h"
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIGuild.h>
#include <algorithm>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Contents/Base/UIQuestBookNew.h>
#include <Engine/Contents/Base/UICharacterInfoNew.h>
#include <Engine/Interface/UIRadar.h>
#include <Engine/Interface/UIGuildNotice.h>
#include <Engine/Interface/UISiegeWarfare.h>
#include <Engine/Object/ActorMgr.h>
#include <Engine/Info/MyInfo.h>
#include <Engine/Interface/UISimplePop.h>
#include <Engine/Contents/Base/Party.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Help/Util_Help.h>
#include <Engine/Math/Float.h>
#include <Engine/Contents/function/GuildChangeSetUI.h>
#include <Engine/Contents/function/GuildDonateUI.h>

extern INDEX g_iCountry;

// WSS_NEW_GUILD_SYSTEM 070704
#define MAX_GUILD_LEVEL		(50)
#define DEF_GUILD_RECALL_SKILL_IDX 1234
// Date : 2005-03-07,   By Lee Ki-hwan
static int	_iMaxMsgStringChar = 0;
#define GUILD_NPC			89
#define pWEB					m_pWebBoard

#define ONE_HOUR_SECOND		  3600
#define ONE_DAY_SECOND		 86400
#define ONE_YEAR_DAY		   365

// WSS_NEW_GUILD_SYSTEM 070705 ---------------------------->><<
// ��� �ý��� �߰��� GP�� ���� ���� ����

class CmdGuildMemberListArrange : public Command
{
public:
	CmdGuildMemberListArrange()	: m_pWnd(NULL), m_eType(eGML_NAME)	{}
	void setData(CUIGuild* pWnd, eGUILD_MEMBER_LIST eType)
	{
		m_pWnd = pWnd;
		m_eType = eType;
	}

	void execute()
	{
		if (m_pWnd != NULL)
		{
			m_pWnd->ArrangeMemList(m_eType);
		}
	}

private:
	CUIGuild* m_pWnd;
	eGUILD_MEMBER_LIST m_eType;
};

//--------------------------------------------------------------
class CmdGuildMouseEvent : public Command
{
public:
	CmdGuildMouseEvent() : pUI_(NULL), m_pItem(NULL), m_Color(DEF_UI_COLOR_WHITE) {}
	void setData(CUIGuild* pUI, CUIListItem* pItem, COLOR col)	
	{
		pUI_ = pUI;
		m_pItem = pItem;
		m_Color = col;
	}
	void execute() {
		if (pUI_)
		{
			pUI_->SetMemberListStrColor(m_pItem, m_Color);
		}
	}
private:
	CUIGuild*	pUI_;
	CUIListItem*		m_pItem;
	COLOR				m_Color;
};

// ��� ���� ����
struct sGuildConditionTable
{
	int		iLevel;				// ��� ����
	int		iCaptionNeedLevel;	// ������ �ּ� ���� ����
	int		iNeedSP;			// �ʿ� SP
	SQUAD	llNeedMoney;		// �ʿ� ����
	int		iMaxMember;			// ��� �ο�.
	int		iNeedGP;			// �ʿ� GP 
};

// ��� ���� ���� ���̺�
sGuildConditionTable _GuildConditionTable[MAX_GUILD_LEVEL] = 
{
	{ 1, 10, 10, 10000, 10 ,0},				// 1 LV
	{ 2, 15, 30, 50000, 15 ,0},				// 2 LV
	{ 3, 20, 60, 250000, 20 ,0},			// 3 LV
	{ 4, 25, 120, 500000, 25 ,0},			// 4 LV
	{ 5, 30, 240, 1000000, 30 ,0},			// 5 LV
	{ 6, 30 , 500 , 2000000, 30 ,0},		// 6 LV
	{ 7, 30 , 550 , 2500000, 30 ,18000},	// 7 LV // ���� ���� (Nas/GP/SP����)
};

enum eSelection
{
	SEL_GUILD_CREATE,
	SEL_GUILD_UPGRADE,
	SEL_GUILD_DESTROY,
	SEL_GUILD_ROOM,
	SEL_GUILD_TALK,
	SEL_GUILD_BUFF,		// [2010/06/30 : Sora] ���� ��� �����ο�
// ==> 1107 ��� �ý��� ���� [trylord 11/12/28]
	SEL_GUILDMASTER_KICK_REQUEST,			// ����� ���� �ɻ� ��û
	SEL_GUILDMASTER_KICK_CANCEL_REQUEST,	// ����� ���� �������� ��û (�ڽ��� ������� ��)
// <== 1107 ��� �ý��� ���� [trylord 11/12/28]	
};

enum eCorpsComboSelection
{
	CMB_NOMEMBER			= 0,	// �δ����
	CMB_RUSH_CAPTAIN		= 1,	// ���ݴ���
	CMB_SUPPORT_CAPTAIN		= 2,	// ��������
	CMB_RECON_CAPTAIN		= 3,	// ��������
	CMB_RUSH_MEMBER			= 4,	// ���ݴ��
	CMB_SUPPORT_MEMBER		= 5,	// �������
	CMB_RECON_MEMBER		= 6,	// �������
};
// FIXME : �Ʒ� �̸��� ����.
#define	GUILD_TAB_WIDTH					(100)
#define START_BUTTON_Y					(GUILD_HEIGHT - 123)	// 284 - 123 = 161
#define DESC_LIST_BOX_HEIGHT			(190)
#define MEMBER_LIST_BOX_WIDTH			(190)
#define MEMBER_LIST_BOX_HEIGHT			(88)
#define	EDIT_BOX_Y						(GUILD_HEIGHT - 57)		// 284 - 57 = 227
#define START_BOTTOM_BUTTON_Y			(GUILD_HEIGHT - 29)		// 284 - 29 = 255
#define SPAN_TEXT_Y						(17)

#define	GUILD_DESC_CHAR_WIDTH			168

//WSS_NEW_GUILD_SYSTEM 070716
#define MAX_NOTICE_TITLE			(64)
#define MAX_NOTICE_CONTENTS			(512)
#define MAX_POSITION_NAME			(12)
#define MAX_PERCENT_LENGTH			(3)
#define NEW_GUILD_SYSTEM_WIDTH		(602)
#define NEW_GUILD_SYSTEM_HEIGHT		(346)
#define GUILD_SKILL_SLOT_ROW		(5)
#define GUILD_SKILL_SLOT_OFFSETY	(40)

#define GUILD_ACTIVE_SKILL_START	-1
#define GUILD_PASSIVE_SKILL_START	-2
#define GUILD_ETC_SKILL_START		-3

#define GUILD_SKILL_ACTIVE	0
#define GUILD_SKILL_PASSIVE 1
#define GUILD_SKILL_ETC		2

const static int nMaxCorpsMember = 29;
const static int nMaxCorpsBoss	 = 3;
/*
#ifdef LIMIT_GUILD_LEVEL
#undef LIMIT_GUILD_LEVEL
#define LIMIT_GUILD_LEVEL 0
#endif*/
// ----------------------------------------------------------------------------
// Name : CUIGuild()
// Desc : 
// ----------------------------------------------------------------------------
CUIGuild::CUIGuild()
	: m_pIconGuildMark(NULL)
	, m_pGuildMember(NULL)
	, m_pGuildChangeSetUI(NULL)
	, m_pGuildDonateUI(NULL)
{
	m_eGuildState			= GUILD_REQ;
	m_nCurrentTab			= GUILD_TAB_MEMBER;
	m_strBossName			= "";
	m_strViceBoss[0]		= "";
	m_strViceBoss[1]		= "";
	m_strGuildName			= "";
	m_iGuildLevel			= -1;
	m_iGuildIndex			= -1;
	m_iNumOfMember			= 0;
	m_iUserRanking			= GUILD_MEMBER_MEMBER;
	m_bChackNpc				= FALSE;
// WSS_NEW_GUILD_SYSTEM 070716 -------------------------------------->>
	m_iSelTab				= 0;				// ����Ʈ ��
	m_iGuildAverageLevel	= 0;				// ��� ��� ����
	m_iGuildOwnLand			= 0;				// ��� ���� ����
	m_iGuildTotalPoint		= 0;				// ��� �� ����Ʈ
	m_iGuildMyPoint			= 0;				// ���� �⿩ ����Ʈ
	m_bApplySettingOn		= FALSE;
	m_bApplyDonateUI	= FALSE;
	m_iNumOfMaxMember		= 0;
	m_iGuildSkillPos		= 0;
	m_bIsSelList			= FALSE;
	m_pWebBoard				= NULL;
	m_bEnableCorrect		= FALSE;
// ------------------------------------------------------------------<<
	m_nSelSkillTab		= GUILD_SKILL_PASSIVE;	// ��� ��ų ��
// ------------------------------------------------------------------<<
	// [1/3/2011 kiny8216] NEW_CORPS
	m_iCorpsMember		= 0;
	m_iCorpsBoss		= 0;

	m_guildMarkTime = -1;		// [sora] GUILD_MARK

	int	i;
	for (i = 0; i < GUILD_SKILL_VIEW_MAX; ++i)
	{
		m_pIconsGuildSkillEx[i] = NULL;
	}

	for (i = 0; i < eGML_MAX; ++i)
		m_pCbMemberArrange[i] = NULL;
}

// ----------------------------------------------------------------------------
// Name : ~CUIGuild()
// Desc : Destructor
// ----------------------------------------------------------------------------
CUIGuild::~CUIGuild()
{
	Destroy();

	if(!m_vectorMemberList.empty())
	{
		m_vectorMemberList.clear();
	}
	ClearGuildSkill();

	STOCK_RELEASE(m_ptdSelBoxTexture);

	int		i;

	for (i = 0; i < GUILD_SKILL_VIEW_MAX; ++i)
	{
		SAFE_DELETE(m_pIconsGuildSkillEx[i]);
	}

	SAFE_DELETE(m_pIconGuildMark);

	for (i = 0; i < eGML_MAX; ++i)
		SAFE_DELETE(m_pCbMemberArrange[i]);

	m_ContGuild.clear();
}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
void CUIGuild::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight )
{
	int		i;

	CUIWindow::Create(pParentWnd, nX, nY, nWidth, nHeight);

	InitString();

	_iMaxMsgStringChar = GUILD_DESC_CHAR_WIDTH / ( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() );

	// Region of each part
	m_rcTitle.SetRect( 0, 0, 216, 22 );
	m_rcTab.SetRect( 6, 26, 210, 42 );

	// Create skill learn texture
	m_ptdBaseTexture = CreateTexture( CTString( "Data\\Interface\\MessageBox.tex" ) );
	FLOAT	fTexWidth = m_ptdBaseTexture->GetPixWidth();
	FLOAT	fTexHeight = m_ptdBaseTexture->GetPixHeight();

	// UV Coordinate of each part
	// Background
	m_rtBackTop.SetUV( 0, 0, 216, 26, fTexWidth, fTexHeight );
	m_rtBackMiddle1.SetUV( 0, 31, 216, 33, fTexWidth, fTexHeight );
	m_rtBackMiddle2.SetUV( 0, 35, 216, 37, fTexWidth, fTexHeight );
	m_rtBackManagerTop.SetUV( 36, 69, 252, 106, fTexWidth, fTexHeight );		// 37
	m_rtBackManagerMiddle.SetUV( 36, 106, 252, 112, fTexWidth, fTexHeight );	// 6
	m_rtBackManagerBottom.SetUV( 36, 112, 252, 116, fTexWidth, fTexHeight );	// 4
	m_rtBackBottom.SetUV( 0, 38, 216, 45, fTexWidth, fTexHeight );

	// Input box
	m_rtInputBoxL.SetUV( 131, 46, 135, 59, fTexWidth, fTexHeight );
	m_rtInputBoxM.SetUV( 137, 46, 139, 59, fTexWidth, fTexHeight );
	m_rtInputBoxR.SetUV( 141, 46, 145, 59, fTexWidth, fTexHeight );

	m_rtTab.SetUV( 43, 69, 44, 86, fTexWidth, fTexHeight );

	// Close button
	m_btnClose.Create( this, CTString( "" ), 184, 4, 14, 14 );
	m_btnClose.SetUV( UBS_IDLE, 219, 0, 233, 14, fTexWidth, fTexHeight );
	m_btnClose.SetUV( UBS_CLICK, 234, 0, 248, 14, fTexWidth, fTexHeight );
	m_btnClose.CopyUV( UBS_IDLE, UBS_ON );
	m_btnClose.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Learn button
	m_btnOK.Create( this, _S( 191, "Ȯ��" ), 78, START_BOTTOM_BUTTON_Y, 63, 21 );
	m_btnOK.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnOK.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnOK.CopyUV( UBS_IDLE, UBS_ON );
	m_btnOK.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Cancel button
	m_btnCancel.Create( this, _S( 139, "���" ), 145, START_BOTTOM_BUTTON_Y, 63, 21 );
	m_btnCancel.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnCancel.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnCancel.CopyUV( UBS_IDLE, UBS_ON );
	m_btnCancel.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Exit button
	m_btnExit.Create( this, _S( 870, "�ݱ�" ), 145, START_BOTTOM_BUTTON_Y, 63, 21 );			
	m_btnExit.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnExit.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnExit.CopyUV( UBS_IDLE, UBS_ON );
	m_btnExit.CopyUV( UBS_IDLE, UBS_DISABLE );

	int nButtonY = START_BUTTON_Y;

	// Change Boss button
	m_btnChangeBoss.Create( this, _S( 871, "����� ����" ), 92, START_BUTTON_Y, 115, 21 );
	m_btnChangeBoss.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnChangeBoss.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnChangeBoss.CopyUV( UBS_IDLE, UBS_ON );
	m_btnChangeBoss.CopyUV( UBS_IDLE, UBS_DISABLE );

	nButtonY += 23;
	// Accept button
	m_btnAccept.Create( this, _S( 872, "������ �Ӹ�" ), 92, nButtonY, 115, 21 );		
	m_btnAccept.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnAccept.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnAccept.CopyUV( UBS_IDLE, UBS_ON );
	m_btnAccept.CopyUV( UBS_IDLE, UBS_DISABLE );

	nButtonY += 23;
	// Reject button
	m_btnReject.Create( this, _S( 873, "������ ����" ), 92, nButtonY, 115, 21 );		
	m_btnReject.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnReject.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnReject.CopyUV( UBS_IDLE, UBS_ON );
	m_btnReject.CopyUV( UBS_IDLE, UBS_DISABLE );

	nButtonY += 23;
	// MemberQuit button
	m_btnMemberFire.Create( this, _S( 874, "���� ����" ), 92, nButtonY, 115, 21 );	
	m_btnMemberFire.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnMemberFire.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnMemberFire.CopyUV( UBS_IDLE, UBS_ON );
	m_btnMemberFire.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Guild Name edit box
	m_ebGuildName.Create( this, 100, EDIT_BOX_Y - 2, 90, 16, 16 );
	m_ebGuildName.SetReadingWindowUV( 146, 46, 163, 62, fTexWidth, fTexHeight );
	m_ebGuildName.SetCandidateUV( 146, 46, 163, 62, fTexWidth, fTexHeight );

	// [2011/11/02 : Sora] Ŀ�� �̵� �Ұ��÷���
	m_ebGuildName.SetCursorMove( FALSE );

	// List box of guild description
	m_lbGuildDesc.Create( this, 8, 28, 190, 190, _pUIFontTexMgr->GetLineHeight(), 13, 3, 1, FALSE );
	m_lbGuildDesc.CreateScroll( TRUE, 0, 0, 9, DESC_LIST_BOX_HEIGHT, 9, 7, 0, 0, 10 );
	m_lbGuildDesc.SetSelBar( 190, _pUIFontTexMgr->GetLineHeight(), 187, 46, 204, 61, fTexWidth, fTexHeight );
	// Up button
	m_lbGuildDesc.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbGuildDesc.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbGuildDesc.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbGuildDesc.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbGuildDesc.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbGuildDesc.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbGuildDesc.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbGuildDesc.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbGuildDesc.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbGuildDesc.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbGuildDesc.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );

	// List box of guild description
	m_lbMemberList.Create( this, 8, 63, MEMBER_LIST_BOX_WIDTH, MEMBER_LIST_BOX_HEIGHT, _pUIFontTexMgr->GetLineHeight(), 13, 3, 2, TRUE );
	m_lbMemberList.CreateScroll( TRUE, 0, 0, 9, MEMBER_LIST_BOX_HEIGHT, 9, 7, 0, 0, 10 );
	m_lbMemberList.SetSelBar( MEMBER_LIST_BOX_WIDTH, _pUIFontTexMgr->GetLineHeight(), 187, 46, 204, 61, fTexWidth, fTexHeight );
	m_lbMemberList.SetOverColor( 0xF8E1B5FF );
	m_lbMemberList.SetSelectColor( 0xF8E1B5FF );
	m_lbMemberList.SetColumnPosX( 1, 110 );
	// Up button
	m_lbMemberList.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbMemberList.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbMemberList.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbMemberList.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbMemberList.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbMemberList.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbMemberList.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbMemberList.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbMemberList.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbMemberList.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbMemberList.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );	

	// List box of guild description
	m_lbApplicantList.Create( this, 8, 63, MEMBER_LIST_BOX_WIDTH, MEMBER_LIST_BOX_HEIGHT * 2, _pUIFontTexMgr->GetLineHeight()+5, 13, 3, 2, FALSE );
	m_lbApplicantList.CreateScroll( TRUE, 0, 0, 9, MEMBER_LIST_BOX_HEIGHT * 2, 9, 7, 0, 0, 10 );
	m_lbApplicantList.SetSelBar( MEMBER_LIST_BOX_WIDTH, _pUIFontTexMgr->GetLineHeight()+5, 187, 46, 204, 61, fTexWidth, fTexHeight );
	m_lbApplicantList.SetOverColor( 0xF8E1B5FF );
	m_lbApplicantList.SetSelectColor( 0xF8E1B5FF );
	m_lbApplicantList.SetColumnPosX( 1, 115 );
	// Up button
	m_lbApplicantList.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbApplicantList.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbApplicantList.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbApplicantList.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbApplicantList.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbApplicantList.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbApplicantList.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbApplicantList.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbApplicantList.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbApplicantList.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbApplicantList.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );	

	CSetFPUPrecision _set_Precision(FPT_64BIT);

// WSS_NEW_GUILD_SYSTEM 070704	
	for(i= 7;i<MAX_GUILD_LEVEL;i++)
	{
		if(i+1>=5 && i+1<=10) 
			_GuildConditionTable[i].iCaptionNeedLevel	=	30;	//pwesty
		else if(i+1>=11 && i+1<=19) 
			_GuildConditionTable[i].iCaptionNeedLevel	=	40;	
		else if(i+1>=20) 
			_GuildConditionTable[i].iCaptionNeedLevel	=	30 + 10*((i+1)/10);	
		
		_GuildConditionTable[i].iLevel				=	i+1;		
		// �ʿ䳪��/sp/gp = 7�������� �ʿ䷮ * (1.09^(���LV - 7))
		_GuildConditionTable[i].iMaxMember			=	_GuildConditionTable[6].iMaxMember; 
		_GuildConditionTable[i].iNeedGP				=	_GuildConditionTable[6].iNeedGP	* pow(1.09,i-6);
		_GuildConditionTable[i].iNeedSP				=	_GuildConditionTable[6].iNeedSP	* pow(1.09,i-6);
		_GuildConditionTable[i].llNeedMoney			=	_GuildConditionTable[6].llNeedMoney	* pow(1.09,i-6);
	}
	CreateNew(pParentWnd,nX,nY);

	// List Box of Guild Skill Use Info	: ��� ��ų ��� ����
	m_lbUseInfo.Create( this, 270, 178, 140, 70, _pUIFontTexMgr->GetLineHeight(), 13, 3, 1, FALSE );
	m_lbUseInfo.CreateScroll( TRUE, 0, 0, 9, 70, 9, 7, 0, 0, 10 );
	// Up button
	m_lbUseInfo.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbUseInfo.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbUseInfo.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbUseInfo.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbUseInfo.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbUseInfo.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbUseInfo.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbUseInfo.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbUseInfo.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbUseInfo.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbUseInfo.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );

	// List Box of Guild Skill Learn Info : ��ų ���� ����
	m_lbLearnInfo.Create( this, 427, 178, 140, 70, _pUIFontTexMgr->GetLineHeight(), 13, 3, 1, FALSE );
	m_lbLearnInfo.CreateScroll( TRUE, 0, 0, 9, 70, 9, 7, 0, 0, 10 );
	// Up button
	m_lbLearnInfo.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbLearnInfo.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbLearnInfo.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbLearnInfo.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbLearnInfo.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbLearnInfo.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbLearnInfo.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbLearnInfo.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbLearnInfo.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbLearnInfo.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbLearnInfo.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );

	// Use Skill
	m_btnUseSkill.Create( this, _S(5013, "����ϱ�" ), 295, 256, 100, 21 );
	m_btnUseSkill.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnUseSkill.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnUseSkill.CopyUV( UBS_IDLE, UBS_ON );
	m_btnUseSkill.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Tab Rect : Active / Passive
	m_rcSkillTab[GUILD_SKILL_PASSIVE].SetRect(15, 79, 37, 167);
	m_rcSkillTab[GUILD_SKILL_ACTIVE].SetRect(15, 169, 37, 257);

	m_rcSkillTabPopupInfo.SetRect( 0, 0, 100, 30 );
	// ��� ��ų ��ư rect
	int nPosY1 = 70, nPosY2 = 103;
	for (int iCnt=0; iCnt<5; ++iCnt)
	{
		m_rcSkillBtn[iCnt].SetRect(46, nPosY1, 240, nPosY2);
		nPosY1 += 40;
		nPosY2 += 40;
	}

	m_ptdSelBoxTexture = CreateTexture( CTString( "Data\\Interface\\CommonBtn.tex" ));
	fTexWidth	= m_ptdSelBoxTexture->GetPixWidth();
	fTexHeight	= m_ptdSelBoxTexture->GetPixHeight();
	// ��ų ���� ��, �ؽ���	
	m_rtSelBoxUV.SetUV( 145, 138, 240, 172, fTexWidth, fTexHeight );

	// ��� ��ų ���� ���� ��
	m_rtSelSideTabUV.SetUV(59, 0, 80, 101, fTexWidth, fTexHeight);
	m_rtUnSelSideTabUV.SetUV(86, 0, 107, 101, fTexWidth, fTexHeight);

	// ��� ��ų �� �˾� ����
	m_rtPopupUL.SetUV( 0, 229, 8, 237, fTexWidth, fTexHeight );
	m_rtPopupUM.SetUV( 8, 229, 76, 237, fTexWidth, fTexHeight );
	m_rtPopupUR.SetUV( 76, 229, 84, 237, fTexWidth, fTexHeight );
	m_rtPopupML.SetUV( 0, 237, 8, 243, fTexWidth, fTexHeight );
	m_rtPopupMM.SetUV( 8, 237, 76, 243, fTexWidth, fTexHeight );
	m_rtPopupMR.SetUV( 76, 237, 84, 243, fTexWidth, fTexHeight );
	m_rtPopupLL.SetUV( 0, 243, 8, 251, fTexWidth, fTexHeight );
	m_rtPopupLM.SetUV( 8, 243, 76, 251, fTexWidth, fTexHeight );
	m_rtPopupLR.SetUV( 76, 243, 84, 251, fTexWidth, fTexHeight );
	
	// ��� ��ų �� ���� �׷����� �ؽ���
	m_rtPassiveTabIconUV[0].SetUV(183, 222, 196, 236, fTexWidth, fTexHeight );
	m_rtPassiveTabIconUV[1].SetUV(200, 222, 213, 236, fTexWidth, fTexHeight );
	m_rtActiveTabIconUV[0].SetUV(183, 205, 196, 219, fTexWidth, fTexHeight );
	m_rtActiveTabIconUV[1].SetUV(200, 205, 213, 219, fTexWidth, fTexHeight );

	// [1/11/2011 kiny8216] Guild_Skill_Fix
	int nBtnY = 71;

	for ( int nCnt=0; nCnt < GUILD_SKILL_VIEW_MAX; ++nCnt )
	{
		m_pIconsGuildSkillEx[nCnt] = new CUIIcon();
		m_pIconsGuildSkillEx[nCnt]->Create(this, 48, nBtnY, 32, 31, UI_GUILD, UBET_SKILL);
		m_pIconsGuildSkillEx[nCnt]->SetWhichUI(UI_GUILD);

		nBtnY += 40;
	}

	// ���� ���� ��Ʈ�� �ʱ�ȭ

	// Guild Member List Box Setting
// 	m_lbGuildMemberList.SetPopBtnSpace(1, 1);
// 	m_lbGuildMemberList.SetPopBtnSize(19, m_lbGuildMemberList.GetLineHeight()-2);

	// Manage Button, Edit Box Position
	int nBtnHeight = 17, nGap = 1;
	int nBtnWidth[eGML_MAX] = {98, 74, 39, 81, 85, 46, 105};
	int nStrIdx[eGML_MAX] = {3105, 3856, 3851, 72, 3857, 3858, 3859};
	int nPosX, nPosY = 60;
	//3105, "ĳ���͸�"
	//3856, "������"  
	//3851, "Lv." 
	//72, "Ŭ����"
	//3857, "������ġ"
	//3858, "�⿩��" 
	//3859, "���� ����Ʈ

	for (i = 0; i < eGML_MAX; ++i)
	{
		UIRectUV uvNone, uvCheck;
		uvNone.SetUV(466, 40, 478, 52);
		uvCheck.SetUV(466, 54, 478, 66);

		m_pCbMemberArrange[i] = new CUICheckButton;
		m_pCbMemberArrange[i]->setParent(this);
		m_pCbMemberArrange[i]->SetSize(12, 12);
		m_pCbMemberArrange[i]->SetText(_S(nStrIdx[i], ""));

		if (i <= 0)
			nPosX = 48 + nBtnWidth[i] - 12;
		else
			nPosX = m_pCbMemberArrange[i - 1]->GetPosX() + nBtnWidth[i] + nGap;

		m_pCbMemberArrange[i]->setTextArea(nBtnWidth[i]);
		m_pCbMemberArrange[i]->SetPos(nPosX, nPosY);
		m_pCbMemberArrange[i]->setTexString("CommonBtn.tex");
		m_pCbMemberArrange[i]->SetUVTex(UCBS_NONE, uvNone);
		m_pCbMemberArrange[i]->SetUVTex(UCBS_CHECK, uvCheck);
		m_pCbMemberArrange[i]->SetCheckRegion(TRUE, nBtnWidth[i] - 12, nBtnWidth[i]);
		m_pCbMemberArrange[i]->SetTextColor(UCBS_NONE, 0xF2F2F2FF);
		m_pCbMemberArrange[i]->SetTextColor(UCBS_CHECK, 0xF2F2F2FF);

		CmdGuildMemberListArrange* pCmd = new CmdGuildMemberListArrange;
		pCmd->setData(this, eGUILD_MEMBER_LIST(i));
		m_pCbMemberArrange[i]->SetCommand(pCmd);
	}
}

// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUIGuild::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUIGuild::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

// WSS_NEW_GUILD_SYSTEM 070702
// ���ʿ��ؼ� �ּ�ó��
//------------------------------------------------------------------------------
// CUIGuild::SetFocus
// Explain:  
// Date : 2005-03-10(���� 1:02:39) Lee Ki-hwan
//------------------------------------------------------------------------------
//void CUIGuild::SetFocus( BOOL bVisible )
//{
//	CUIWindow::SetFocus( bVisible );
//
//	m_ebGuildName.SetFocus( TRUE );
//	if( !bVisible )
//	{
//		m_ebGuildName.SetFocus( FALSE );
//	}
//}


// ----------------------------------------------------------------------------
// Name : OpenGuild()
// Desc : 
// ----------------------------------------------------------------------------
void CUIGuild::OpenGuild( int iMobIndex, BOOL bHasQuest, int iUserRanking, int iGuildLevel )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if(pUIManager->DoesMessageBoxLExist( MSGLCMD_GUILD_REQ ) || IsVisible())
		return;	

	ResetGuild();

	m_iUserRanking = iUserRanking;
	m_iGuildLevel	= iGuildLevel;
	
	pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_DESTROY);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_QUIT);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);	
	pUIManager->CloseMessageBox(MSGCMD_GUILD_ROOM);

	// Create guild message box
	
	// Reset Window Size // WSS_NEW_GUILD_SYSTEM 070725
	SetSize( GUILD_WIDTH, GUILD_HEIGHT );

	pUIManager->CreateMessageBoxL( _S( 865, "���" ) , UI_GUILD, MSGLCMD_GUILD_REQ );					

	CTString	strNpcName = CMobData::getData(iMobIndex)->GetName();
	pUIManager->AddMessageBoxLString( MSGLCMD_GUILD_REQ, TRUE, strNpcName, -1, 0xE18600FF );

	pUIManager->AddMessageBoxLString( MSGLCMD_GUILD_REQ, TRUE, _S( 875, "����� ������ �����ϴ��� �ѽõ� �ð��� �� �� ����." ), -1, 0xA3A1A3FF );	
	pUIManager->AddMessageBoxLString( MSGLCMD_GUILD_REQ, TRUE, _S( 876, "����� ���ٸ� �׳� ���� ���ð�." ), -1, 0xA3A1A3FF );		

	if( m_iUserRanking == GUILD_MEMBER_MEMBER || m_iUserRanking == GUILD_MEMBER_VICE_BOSS || m_iUserRanking == GUILD_MEMBER_NOMEMBER )
	{
		pUIManager->AddMessageBoxLString( MSGLCMD_GUILD_REQ, FALSE,  _S( 877, "��� �Ἲ." ), SEL_GUILD_CREATE );	
	}

	if( m_iUserRanking == GUILD_MEMBER_BOSS )
	{
		pUIManager->AddMessageBoxLString( MSGLCMD_GUILD_REQ, FALSE, _S( 878, "��� �±�." ), SEL_GUILD_UPGRADE );
		pUIManager->AddMessageBoxLString( MSGLCMD_GUILD_REQ, FALSE, _S( 879, "��� �ػ�." ), SEL_GUILD_DESTROY );
	}

	if( m_iUserRanking != GUILD_MEMBER_NOMEMBER )
	{
		pUIManager->AddMessageBoxLString( MSGLCMD_GUILD_REQ, FALSE, _S( 1011, "��� ��ȭ������ �̵�." ), SEL_GUILD_ROOM );
	}

#ifdef	UPDATE1107_GUILDSYSTEM
	// 1107 ��� �ý��� ���� [trylord 11/12/28]
	if(_pNetwork->MyCharacterInfo.lGuildIndex != -1)
	{	// ��忡 �ҼӵǾ����� ������ �޴��� �����ش�
		if(_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_VICE_BOSS)
		{	// �δ����� ��� ����� ���� �ɻ縦 ��û�� �� �ִ�.
			pUIManager->AddMessageBoxLString( MSGLCMD_GUILD_REQ, FALSE, _S( 5613, "����� ���� �ɻ� ��û" ), SEL_GUILDMASTER_KICK_REQUEST );
		}
		else if(_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS
			&& _pNetwork->MyCharacterInfo.iGuildMasterKickStatus == 1)
		{	// �ڽ��� �����̰�, ���� �ڽ��� ���� �ɻ縦 ���� ���� -- ���Ǹ� ��û�� �� �ִ�.
			pUIManager->AddMessageBoxLString( MSGLCMD_GUILD_REQ, FALSE, _S( 5614, "����� ���� ��������" ), SEL_GUILDMASTER_KICK_CANCEL_REQUEST );
		}
	}
#endif	// #ifdef	UPDATE1107_GUILDSYSTEM

	if( bHasQuest )
	{	
		// 2009. 05. 27 ������
		// �̾߱��Ѵ� ���� ó��
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_GUILD_REQ);				
	}

	pUIManager->AddMessageBoxLString( MSGLCMD_GUILD_REQ, FALSE, _S( 1220, "����ϱ�." ) );				
}

// ----------------------------------------------------------------------------
// Name : OpenGuildManager()
// Desc : 
// ----------------------------------------------------------------------------
void CUIGuild::OpenGuildManager( int iUserRanking )
{
	if( iUserRanking < 0 || iUserRanking == GUILD_MEMBER_NOMEMBER )
	{
		return;
	}

	if( IsVisible() )
	{
		ResetGuild();
		return;
	}

	// Reset Window Size // WSS_NEW_GUILD_SYSTEM 070725
	SetSize( GUILD_WIDTH, GUILD_HEIGHT );

	// FIXME : ��� �޴��������� ȣ���ϸ� �ȵ�.
	// FIXME : �ֵ� ����� ���� ���� �� ���� �־�� �ϴµ�, ResetGuild()�� ȣ���ϸ� �� ����.
	//ResetGuild();

	m_iUserRanking	= iUserRanking;
	m_eGuildState	= GUILD_MANAGER;

	m_btnChangeBoss.SetEnable( (m_iUserRanking == GUILD_MEMBER_BOSS) ? TRUE : FALSE );
	m_btnAccept.SetEnable( (m_iUserRanking == GUILD_MEMBER_BOSS) ? TRUE : FALSE );
	m_btnReject.SetEnable( (m_iUserRanking == GUILD_MEMBER_BOSS) ? TRUE : FALSE );
	m_btnMemberFire.SetEnable( (m_iUserRanking < GUILD_MEMBER_MEMBER) ? TRUE : FALSE );	

	if( m_iUserRanking == GUILD_MEMBER_BOSS || m_iUserRanking == GUILD_MEMBER_VICE_BOSS )
	{
		RefreshMemberList( TRUE );
	}
	else
	{
		RefreshApplicantList( TRUE );
	}

	CUIManager::getSingleton()->RearrangeOrder( UI_GUILD, TRUE );

}

// ----------------------------------------------------------------------------
// Name : ResetGuild()
// Desc : 
// ----------------------------------------------------------------------------
void CUIGuild::ResetGuild()
{
	m_ebGuildName.ResetString();
	m_lbGuildDesc.ResetAllStrings();
	m_lbMemberList.ResetAllStrings();
	m_lbApplicantList.ResetAllStrings();
	
	//m_strBossName			= "";
	m_strViceBoss[0]		= "";
	m_strViceBoss[1]		= "";
	m_strGuildName			= "";

	m_iGuildLevel			= -1;
	m_iGuildIndex			= -1;
	m_iNumOfMember			= 0;

	m_eGuildState			= GUILD_REQ;
	m_nCurrentTab			= GUILD_TAB_MEMBER;
	m_iUserRanking			= GUILD_MEMBER_MEMBER;

	// NOTE : ��带 Ż���ϰų� ��ü ���� �ʴ� �̻�, Ŭ���� �ϸ� �ȵɰ� ����.
	//ClearMemberList();

	m_ebGuildName.SetFocus(FALSE);
	m_ebSearch.SetFocus(FALSE);
	m_ebWriteSubject.SetFocus(FALSE);
	m_ebNoticeTitle.SetFocus(FALSE);
	if (m_pGuildChangeSetUI != NULL)
		m_pGuildChangeSetUI->KillFocusEditBox();
	if (m_pGuildDonateUI != NULL)
		m_pGuildDonateUI->KillFocusEditBox();
	m_ContGuild.clear();

	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->RearrangeOrder( UI_GUILD, FALSE );
	
	if(pUIManager->GetSimplePop()->IsEnabled())
	{
		// SIMPLE POP�� ���� �־��ٸ� �ݾ� �ش�..
		pUIManager->GetSimplePop()->ClosePop();
	}
}

// ----------------------------------------------------------------------------
// Name : ClearMemberList()
// Desc : ��� ����� Ŭ�����մϴ�.
// ----------------------------------------------------------------------------
void CUIGuild::ClearMemberList()
{
	// NOTE : ��带 Ż���ϰų� ��ü ���� �ʴ� �̻�, Ŭ���� �ϸ� �ȵɰ� ����.
	if(!m_vectorMemberList.empty())
	{
		m_strBossName			= "";
		m_vectorMemberList.clear();
	}
}

// ----------------------------------------------------------------------------
// Name : PressOKBtn()
// Desc : Ȯ�� ��ư�� ������ ���� ó��.
// ----------------------------------------------------------------------------
void CUIGuild::PressOKBtn()
{
	switch( m_eGuildState )
	{
	case GUILD_CREATE:		// ��� ����
		CreateGuild();
		break;
	case GUILD_UPGRADE:		// ��� �±�
		UpgradeGuild();
		break;
	case GUILD_DESTROY:		// ��� ��ü
		{
			CUIManager* pUIManager = CUIManager::getSingleton();

			pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_DESTROY);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_QUIT);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);	
			pUIManager->CloseMessageBox(MSGCMD_GUILD_ROOM);
			
			// Create message box of guild destroy
			CTString	strMessage;
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILD_DESTROY );	
			strMessage.PrintF( _S( 881, "������ [%s] ��带 �ػ� �Ͻðڽ��ϱ�?" ), _pNetwork->MyCharacterInfo.strGuildName );		
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;
	}
}

void CUIGuild::PressChangeSetUIOK()
{
	if( CheckDataValidation() )
	{
		// TODO :: send apply message
		SendAdjustGuildMemberInfo(
			m_vManageMemberIndex[m_lbManageMemberList.GetCurSel()],
			m_pGuildChangeSetUI->GetString(CGuildChangeSetUI::eEDIT_CHANGE_POSITION),
			atoi(m_pGuildChangeSetUI->GetString(CGuildChangeSetUI::eEDIT_EXP_MIN)),
			atoi(m_pGuildChangeSetUI->GetString(CGuildChangeSetUI::eEDIT_EXP_MAX)),
			atoi(m_pGuildChangeSetUI->GetString(CGuildChangeSetUI::eEDIT_FAME_MIN)),
			atoi(m_pGuildChangeSetUI->GetString(CGuildChangeSetUI::eEDIT_FAME_MAX)),
			GetSelectedPositon(),
			(UBYTE)m_pGuildChangeSetUI->GetStashUsable());
	}	
	// ��Ȱ��ȭ
	SetManagePopup(FALSE);
}

void CUIGuild::PressChangeSetAllUIOK()
{
	if (m_pGuildDonateUI == NULL)
		return;

	if ( CheckDataValidationDonate() )
	{
		SendAdjustGuildMemberInfoAll( atoi(m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_EXP_MIN)),
			atoi(m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_EXP_MAX)),
			atoi(m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_FAME_MIN)),
			atoi(m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_FAME_MAX)),
			atoi(m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_EXP)),
			atoi(m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_FAME)));
	}	

	SetManageSetAllPopup(FALSE);
}

void CUIGuild::PressDonateUIOK()
{
	if (m_pGuildDonateUI == NULL)
		return;
	if ( CheckDataValidationDonate() )
	{
		SendAdjustGuildDonateInfo( atoi(m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_EXP)),
			atoi(m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_FAME)) );
	}

	SetManageSetAllPopup(FALSE);
}

// ----------------------------------------------------------------------------
// Name : CreateGuild()
// Desc : ��� ����
// ----------------------------------------------------------------------------
void CUIGuild::CreateGuild()
{
	// ��� ����.
	if( m_ebGuildName.GetString() )
	{
		CUIManager* pUIManager = CUIManager::getSingleton();
		m_strGuildName = m_ebGuildName.GetString();

		if(!pUIManager->checkName(m_strGuildName, eCHECK_TYPE_GUILD_NAME))
		{
			pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_DESTROY);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_QUIT);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_ROOM);
			
			m_ebGuildName.ResetString();
			m_ebGuildName.SetFocus( TRUE );
			return;
		}
		
		// ��� ���� �޽��� ������.
		_pNetwork->GuildCreate( m_strGuildName );
	}
}

// ----------------------------------------------------------------------------
// Name : GoGuildZone()
// Desc : ��� ���� �������� �̵�...
// ----------------------------------------------------------------------------
void CUIGuild::GoGuildZone()
{
	const int iGuildZoneID = 8;
	if( _pNetwork->MyCharacterInfo.lGuildIndex != GUILD_MEMBER_NOMEMBER )
	{
		_pNetwork->GoZone( iGuildZoneID, 0 , GUILD_NPC );
	}
}

// ----------------------------------------------------------------------------
// Name : UpgradeGuild()
// Desc : ��� �±�
// ----------------------------------------------------------------------------
void CUIGuild::UpgradeGuild()
{
	_pNetwork->GuildUpgrade();
}

// ----------------------------------------------------------------------------
// Name : DestroyGuild()
// Desc : ��� ��ü
// ----------------------------------------------------------------------------
void CUIGuild::DestroyGuild()
{
	_pNetwork->GuildDestroy();
}

static LONG g_lChaIndex		= -1;		// ���� ��û�� ���õ� �κп��� ����.
static LONG g_lGuildIndex	= -1;
static LONG g_lMemberIndex	= -1;		// ����� ���õ� �κп��� ����.

// ----------------------------------------------------------------------------
// Name : JoinGuild()
// Desc : ��� ����
// ----------------------------------------------------------------------------
void CUIGuild::JoinGuild( LONG lGuildIndex, LONG lChaIndex, const CTString& strName, INDEX iSyndiType )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_DESTROY);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_QUIT);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);	
	pUIManager->CloseMessageBox(MSGCMD_GUILD_ROOM);
	
	g_lChaIndex		= lChaIndex;
	g_lGuildIndex	= lGuildIndex;
	m_iSyndiType	= iSyndiType;
	
	// Create message box of guild destroy
	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILD_JOIN );	
	strMessage.PrintF( _S( 884, "[%s] ��忡 ���� ��û�� �Ͻðڽ��ϱ�?" ), strName );		
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );
}

// ----------------------------------------------------------------------------
// Name : QuitGuild()
// Desc : ��� Ż��
// ----------------------------------------------------------------------------
void CUIGuild::QuitGuild( )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_DESTROY);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_QUIT);
	pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);	
	pUIManager->CloseMessageBox(MSGCMD_GUILD_ROOM);
	
	// Create message box of guild destroy
	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILD_QUIT );	
	strMessage.PrintF( _S( 885, "[%s] ��带 Ż�� �Ͻðڽ��ϱ�?" ), _pNetwork->MyCharacterInfo.strGuildName );		
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );
}

// ----------------------------------------------------------------------------
// Name : ChangeBoss()
// Desc : ���� ����
// ----------------------------------------------------------------------------
void CUIGuild::ChangeBoss()
{
	// WSS_NEW_GUILD_SYSTEM 070719
	int	iSelMember;

	if(m_iGuildLevel < LIMIT_GUILD_LEVEL)

		iSelMember = m_lbMemberList.GetCurSel();
	else 
		iSelMember = m_lbManageMemberList.GetCurSel();

	if( iSelMember == -1 )
		return;

	sGuildMember &TempMember = m_vectorMemberList[iSelMember];
	if( _pNetwork->MyCharacterInfo.index == TempMember.lIndex )
		return;
	
	g_lMemberIndex = TempMember.lIndex;

	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->CloseMessageBox( MSGCMD_GUILD_KICK );
	pUIManager->CloseMessageBox( MSGCMD_GUILD_CHANGE_BOSS );
	pUIManager->CloseMessageBox( MSGCMD_GUILD_ADD_VICE_BOSS );
	pUIManager->CloseMessageBox( MSGCMD_GUILD_DEL_VICE_BOSS );
	
	// Create message box of guild destroy
	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILD_CHANGE_BOSS );	
	strMessage.PrintF( _S( 886, "[%s] ���� ������� ���� �Ͻðڽ��ϱ�?" ), TempMember.strMemberName );		
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );
}

// ----------------------------------------------------------------------------
// Name : AddViceBoss()
// Desc : �δ��� �Ӹ�
// ----------------------------------------------------------------------------
void CUIGuild::AddViceBoss()
{
	// WSS_NEW_GUILD_SYSTEM 070719
	int	iSelMember;

	if(m_iGuildLevel < LIMIT_GUILD_LEVEL)
		iSelMember = m_lbMemberList.GetCurSel();
	else 
		iSelMember = m_lbManageMemberList.GetCurSel();

	if( iSelMember != -1 )
	{
		sGuildMember &TempMember = m_vectorMemberList[iSelMember];
		g_lMemberIndex = TempMember.lIndex;

		if( TempMember.eRanking == GUILD_MEMBER_VICE_BOSS )
		{
			return;
		}

		CUIManager* pUIManager = CUIManager::getSingleton();

		pUIManager->CloseMessageBox( MSGCMD_GUILD_KICK );
		pUIManager->CloseMessageBox( MSGCMD_GUILD_CHANGE_BOSS );
		pUIManager->CloseMessageBox( MSGCMD_GUILD_ADD_VICE_BOSS );
		pUIManager->CloseMessageBox( MSGCMD_GUILD_DEL_VICE_BOSS );

		// Create message box of guild destroy
		CTString	strMessage;
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILD_ADD_VICE_BOSS );	
		strMessage.PrintF( _S( 887, "[%s]�� ���������� �Ӹ� �Ͻðڽ��ϱ�?" ), TempMember.strMemberName );		
		MsgBoxInfo.AddString( strMessage );
		pUIManager->CreateMessageBox( MsgBoxInfo );		
	}
}

// ----------------------------------------------------------------------------
// Name : DelViceBoss()
// Desc : �δ��� ����
// ----------------------------------------------------------------------------
void CUIGuild::DelViceBoss()
{
	// WSS_NEW_GUILD_SYSTEM 070719
	int	iSelMember;
	if(m_iGuildLevel < LIMIT_GUILD_LEVEL)
		iSelMember = m_lbMemberList.GetCurSel();
	else 
		iSelMember = m_lbManageMemberList.GetCurSel();
	
	if( iSelMember != -1 )
	{
		sGuildMember &TempMember = m_vectorMemberList[iSelMember];

		// �δ��常 ������.
		if(TempMember.eRanking != GUILD_MEMBER_VICE_BOSS)
			return;

		g_lMemberIndex = TempMember.lIndex;

		CUIManager* pUIManager = CUIManager::getSingleton();

		pUIManager->CloseMessageBox( MSGCMD_GUILD_KICK );
		pUIManager->CloseMessageBox( MSGCMD_GUILD_CHANGE_BOSS );
		pUIManager->CloseMessageBox( MSGCMD_GUILD_ADD_VICE_BOSS );
		pUIManager->CloseMessageBox( MSGCMD_GUILD_DEL_VICE_BOSS );

		// Create message box of guild destroy
		CTString	strMessage;
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILD_DEL_VICE_BOSS );	
		strMessage.PrintF( _S( 888, "[%s]�� �����忡�� ���� �Ͻðڽ��ϱ�?" ), TempMember.strMemberName );		
		MsgBoxInfo.AddString( strMessage );
		pUIManager->CreateMessageBox( MsgBoxInfo );
	}
}

// ----------------------------------------------------------------------------
// Name : MemberFire()
// Desc : �ܿ� ����
// ----------------------------------------------------------------------------
void CUIGuild::MemberFire()
{
	// WSS_NEW_GUILD_SYSTEM 070719
	int	iSelMember;

	if(m_iGuildLevel < LIMIT_GUILD_LEVEL)
		iSelMember = m_lbMemberList.GetCurSel();
	else 
		iSelMember = m_lbManageMemberList.GetCurSel();
	
	if( iSelMember != -1 )
	{
		sGuildMember &TempMember = m_vectorMemberList[iSelMember];

		// ����� ������ �ڱ� �������� ������ ���� ����Ŵ.
		if( TempMember.eRanking < _pNetwork->MyCharacterInfo.lGuildPosition )
			return;

		g_lMemberIndex = TempMember.lIndex;

		CUIManager* pUIManager = CUIManager::getSingleton();

		pUIManager->CloseMessageBox( MSGCMD_GUILD_KICK );
		pUIManager->CloseMessageBox( MSGCMD_GUILD_CHANGE_BOSS );
		pUIManager->CloseMessageBox( MSGCMD_GUILD_ADD_VICE_BOSS );
		pUIManager->CloseMessageBox( MSGCMD_GUILD_DEL_VICE_BOSS );
		
		// Create message box of guild destroy
		CTString	strMessage;
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILD_KICK );	
		strMessage.PrintF( _S( 889, "[%s]�� ���� �Ͻðڽ��ϱ�?" ), TempMember.strMemberName );		
		MsgBoxInfo.AddString( strMessage );
		pUIManager->CreateMessageBox( MsgBoxInfo );		
	}
}

// ----------------------------------------------------------------------------
// Name : ApplicantAccept()
// Desc : ���� ����
// ----------------------------------------------------------------------------
void CUIGuild::ApplicantAccept( LONG lIndex )
{
	CTString strMemberName = "";

	g_lChaIndex = lIndex;

	ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lIndex);

	if (pObject != NULL)
	{
		strMemberName = pObject->m_strName.c_str();
	}

	// Create message box of guild destroy
	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILD_APPLICANT_JOIN );	
	strMessage.PrintF( _S( 890, "[%s] �Բ��� ���� ��û�� �ϼ̽��ϴ�. �����Ͻðڽ��ϱ�?" ),  strMemberName );		
	MsgBoxInfo.AddString( strMessage );
	CUIManager::getSingleton()->CreateMessageBox( MsgBoxInfo );
}

// ----------------------------------------------------------------------------
// Name : AddToMemberList()
// Desc : ��� ��Ͽ� �߰�
// ----------------------------------------------------------------------------
void CUIGuild::AddToMemberList( LONG lIndex, const CTString& strName, int eLevel, BOOL bOnline )
{
	// �ܿ��� ����� ������ �ϴ� ���...
	/*
	if( m_iUserRanking != GUILD_MEMBER_MEMBER && 
	eLevel == GUILD_MEMBER_BOSS )		// ����
	{
		m_strBossName = strName;
	}
	else
	*/
	{
		sGuildMember TempGuildMember;
		TempGuildMember.lIndex			= lIndex;
		TempGuildMember.strMemberName	= strName;
		TempGuildMember.eRanking		= eLevel;
		TempGuildMember.bOnline			= bOnline;
		m_vectorMemberList.push_back(TempGuildMember);
	}
}

// ----------------------------------------------------------------------------
// Name : DelFromMemberList()
// Desc : ��� ��Ͽ��� ����
// ----------------------------------------------------------------------------
void CUIGuild::DelFromMemberList( LONG lIndex )
{
	sGuildMember TempGuildMember;
	TempGuildMember.lIndex = lIndex;
	std::vector<sGuildMember>::iterator iter = 
		std::find_if(m_vectorMemberList.begin(), m_vectorMemberList.end(), FindMember( TempGuildMember ) );

	if( iter != m_vectorMemberList.end() )
	{
		m_vectorMemberList.erase( iter );
	}
}

// ----------------------------------------------------------------------------
// Name : ChangeMemberLevel()
// Desc : ����� ������ ������.
// ----------------------------------------------------------------------------
void CUIGuild::ChangeMemberLevel( LONG lIndex, int eLevel )
{
	sGuildMember TempGuildMember;
	TempGuildMember.lIndex = lIndex;
	std::vector<sGuildMember>::iterator iter = 
		std::find_if(m_vectorMemberList.begin(), m_vectorMemberList.end(), FindMember( TempGuildMember ) );

	if( iter != m_vectorMemberList.end() )
	{
		(*iter).eRanking = eLevel;
	}
}

// ----------------------------------------------------------------------------
// Name : ChangeMemberOnline()
// Desc : ����� �¶��� ���¸� ������.
// ----------------------------------------------------------------------------
void CUIGuild::ChangeMemberOnline( LONG lIndex, BOOL bOnline )
{
	sGuildMember TempGuildMember;
	TempGuildMember.lIndex = lIndex;
	std::vector<sGuildMember>::iterator iter = 
		std::find_if(m_vectorMemberList.begin(), m_vectorMemberList.end(), FindMember( TempGuildMember ) );

	if( iter != m_vectorMemberList.end() )
	{
		(*iter).bOnline = bOnline;
	}
}

// ----------------------------------------------------------------------------
// Name : RefreshMemberList()
// Desc : ����� �����մϴ�.
// ----------------------------------------------------------------------------
void CUIGuild::RefreshMemberList( BOOL bInit )
{
	if( !bInit && !IsVisible() )
		return;

	m_lbMemberList.ResetAllStrings();
	std::sort(m_vectorMemberList.begin(), m_vectorMemberList.end());

	CTString	strLevel;
	COLOR		crLevel;

	int			iBossCount		= 0;
	int			iViceBossCount	= 0;
	m_strViceBoss[0]			= "";
	m_strViceBoss[1]			= "";
	std::vector<sGuildMember>::const_iterator member_end = m_vectorMemberList.end();
	std::vector<sGuildMember>::iterator it = m_vectorMemberList.begin();
	for(it = m_vectorMemberList.begin(); it != member_end; ++it)
	{
		switch( (*it).eRanking )
		{
		case GUILD_MEMBER_BOSS:			// �����
			{
				strLevel	= _S( 891, "�����" );	
				crLevel		= 0xFF9533FF;
				ASSERT(iBossCount <= 1 && "Invalid Boss Count");
				m_strBossName = (*it).strMemberName;
				iBossCount++;

				// ������ �̸��� ǥ�õǸ� �ȵǹǷ�...
				//continue;
			}
			break;
		case GUILD_MEMBER_VICE_BOSS:	// ������
			{
				strLevel	= _S( 892, "������" );	
				crLevel		= 0xFFC672FF;
				ASSERT(iViceBossCount <= 2 && "Invalid Vice-Boss Count");
				m_strViceBoss[iViceBossCount] = (*it).strMemberName;
				iViceBossCount++;
			}
			break;
		case GUILD_MEMBER_MEMBER:		// ����
			{
				strLevel	= _S( 893, "����" );	
				crLevel		= 0xCCCCCCFF;
			}
			break;
			/*
		case GUILD_MEMBER_APPLICANT:	// ������
			{
				ASSERTALWAYS("ȣ��Ǿ�� �ȵǴ� �κ�\n");
				strLevel	= _S( 894, "������" );	
				crLevel		= 0x9400D6FF;
			}
			break;
			*/
		}

		BOOL bOnline = (*it).bOnline;
		m_lbMemberList.AddString( 0, (*it).strMemberName, bOnline ? 0xFFFFFFFF : 0xAAAAAAFF );
		m_lbMemberList.AddString( 1, strLevel, crLevel);
	}
}

// ----------------------------------------------------------------------------
// Name : RefreshApplicantList()
// Desc : ����� �����մϴ�.
// ----------------------------------------------------------------------------
void CUIGuild::RefreshApplicantList( BOOL bInit )
{
	if( !bInit && !IsVisible() )
		return;

	m_lbApplicantList.ResetAllStrings();
	std::sort(m_vectorMemberList.begin(), m_vectorMemberList.end());

	CTString	strLevel;
	COLOR		crLevel;

	m_lbApplicantList.AddString( 0, _S( 895, "�¶���" ), 0xBCBCBCFF );		
	m_lbApplicantList.AddString( 1, CTString(""), 0xFFFFFFFF);

	int			iBossCount		= 0;
	int			iViceBossCount	= 0;

	// On-Line
	std::vector<sGuildMember>::const_iterator member_end = m_vectorMemberList.end();
	std::vector<sGuildMember>::iterator it = m_vectorMemberList.begin();
	for(it = m_vectorMemberList.begin(); it != member_end; ++it)
	{
		if( (*it).bOnline )
		{
			switch( (*it).eRanking )
			{
			case GUILD_MEMBER_BOSS:			// �����
				{
					strLevel	= _S( 891, "�����" );	
					crLevel		= 0xFF9533FF;
					ASSERT(iBossCount <= 1 && "Invalid Boss Count");
					m_strBossName = (*it).strMemberName;
					iBossCount++;
				}
				break;
			case GUILD_MEMBER_VICE_BOSS:	// ������
				{
					strLevel	= _S( 892, "������" );	
					crLevel		= 0xFFC672FF;
					ASSERT(iViceBossCount <= 2 && "Invalid Vice-Boss Count");
					m_strViceBoss[iViceBossCount] = (*it).strMemberName;
					iViceBossCount++;
				}
				break;
			case GUILD_MEMBER_MEMBER:		// ����
				{
					strLevel	= _S( 893, "����" );	
					crLevel		= 0xCCCCCCFF;
				}
				break;
				/*
			case GUILD_MEMBER_APPLICANT:	// ������
				{
					ASSERTALWAYS("ȣ��Ǿ�� �ȵǴ� �κ�\n");
					strLevel	= _S( 894, "������" );	
					crLevel		= 0x9400D6FF;
				}
				break;
				*/
			}
			m_lbApplicantList.AddString( 0, (*it).strMemberName, 0xFFFFFFFF );
			m_lbApplicantList.AddString( 1, strLevel, crLevel);
		}
	}

	m_lbApplicantList.AddString( 0, CTString("  "), 0xFFFFFFFF );		
	m_lbApplicantList.AddString( 1, CTString(""), 0xFFFFFFFF);

	m_lbApplicantList.AddString( 0, _S( 896, "��������" ), 0xCCCCCCFF );		
	m_lbApplicantList.AddString( 1, CTString(""), 0xFFFFFFFF);

	// Off-Line
	for(it = m_vectorMemberList.begin(); it != member_end; ++it)
	{
		if( !(*it).bOnline )
		{
			switch( (*it).eRanking )
			{
			case GUILD_MEMBER_BOSS:			// �����
				{
					strLevel	= _S( 891, "�����" );	
					crLevel		= 0xFF9533FF;
					ASSERT(iBossCount <= 1 && "Invalid Boss Count");
					m_strBossName = (*it).strMemberName;
					iBossCount++;
				}
				break;
			case GUILD_MEMBER_VICE_BOSS:	// ������
				{
					strLevel	= _S( 892, "������" );	
					crLevel		= 0xFFC672FF;
					ASSERT(iViceBossCount <= 2 && "Invalid Vice-Boss Count");
					m_strViceBoss[iViceBossCount] = (*it).strMemberName;
					iViceBossCount++;
				}
				break;
			case GUILD_MEMBER_MEMBER:		// ����
				{
					strLevel	= _S( 893, "����" );	
					crLevel		= 0xCCCCCCFF;
				}
				break;
				/*
			case GUILD_MEMBER_APPLICANT:	// ������
				{
					ASSERTALWAYS("ȣ��Ǿ�� �ȵǴ� �κ�\n");
					strLevel	= _S( 894, "������" );	
					crLevel		= 0x9400D6FF;
				}
				break;
				*/
			}
			m_lbApplicantList.AddString( 0, (*it).strMemberName, 0xAAAAAAFF );
			m_lbApplicantList.AddString( 1, strLevel, crLevel);
		}
	}
}

// ----------------------------------------------------------------------------
// Name : GetGuildDesc()
// Desc :
// ----------------------------------------------------------------------------
void CUIGuild::GetGuildDesc( BOOL bShow )
{
	m_lbGuildDesc.ResetAllStrings();
	SetSize( GUILD_WIDTH, GUILD_HEIGHT );

	if( bShow == FALSE )
		return;

	BOOL bSatisfied = TRUE;

	// Make description of guild
	CTString	strTemp	= "";
	CTString	strTemp2 = "";
	CUIManager* pUIMgr = UIMGR();

	switch( m_eGuildState )
	{
	case GUILD_CREATE:		// ��� ����
		{
			AddGuildDescString( _S( 897, "��带 �Ἲ �Ϸ��°�?" ) );	
			AddGuildDescString( _S( 898, "��� �ִ� �ڷα�." ) );			
			AddGuildDescString( _S( 899, "������, �׿� �����ϴ� ���� ���� ������ ����� ���� �ؾ� �ϳ�." ) );		
			AddGuildDescString( _S( 900, "�׷��� ���ٸ� �³�����." ) );		
			AddGuildDescString( _S( 901, "�� ������ ȥ���� ���� ���簡 �ʿ��ϴϱ�" ) );		
			AddGuildDescString( CTString( " " ) );

			ASSERT( m_iGuildLevel <= MAX_GUILD_LEVEL && "Invalid Guild Level" );

			const int	iMyLevel	= _pNetwork->MyCharacterInfo.level;
			const SQUAD llMyMoney	= _pNetwork->MyCharacterInfo.money;
			const SLONG	lMySP		= _pNetwork->MyCharacterInfo.sp / 10000;			
			const int	iNeedLevel	= _GuildConditionTable[0].iCaptionNeedLevel;
			const SQUAD llNeedMoney = _GuildConditionTable[0].llNeedMoney;
			const int	iNeedSP		= _GuildConditionTable[0].iNeedSP;

			strTemp.PrintF( _S( 902, "�ִ� ��� �ο� : %d ��" ), _GuildConditionTable[0].iMaxMember);		
			AddGuildDescString( strTemp, 0xFFFFFFFF );

			if( iMyLevel < iNeedLevel )
			{
				bSatisfied = FALSE;
			}

			strTemp.PrintF( _S( 903, "�ʿ� ���� : %d Lv" ), _GuildConditionTable[0].iCaptionNeedLevel);		
			AddGuildDescString( strTemp, iMyLevel >= iNeedLevel ? 0xFFC672FF : 0xBCBCBCFF );

			if( llMyMoney < llNeedMoney )
			{
				bSatisfied = FALSE;
			}

			strTemp2.PrintF("%I64d", _GuildConditionTable[0].llNeedMoney);
			pUIMgr->InsertCommaToString(strTemp2);
			strTemp.PrintF( _S( 904, "�ʿ� ���� : %s ����" ), strTemp2);
			AddGuildDescString( strTemp, llMyMoney >= llNeedMoney ? 0xFFC672FF : 0xBCBCBCFF );

			if( lMySP < iNeedSP )
			{
				bSatisfied = FALSE;
			}

			strTemp2.PrintF("%d", _GuildConditionTable[0].iNeedSP);
			pUIMgr->InsertCommaToString(strTemp2);
			strTemp.PrintF( _S( 905, "�ʿ� S P  : %s SP" ), strTemp2);		
			AddGuildDescString( strTemp, lMySP >= iNeedSP ? 0xFFC672FF : 0xBCBCBCFF );
		}
		break;
	case GUILD_UPGRADE:		// ��� �±�
		{
			AddGuildDescString( _S( 906, "���� �� �Ǿ� ����? ���� �̵��� �ڳ׸� ������ ����." ) );	
			AddGuildDescString( _S( 907, "�ڰ��� �ȴٸ�� �� ���� ������� ������ �� �ڳ��� �ɷ��̳׸�," ) );			
			AddGuildDescString( _S( 908, "���� �ڳװ� �� ���� ����� ������ �� ���� ���� ������ �� �Ǵ��ϰ�." ) );		
			AddGuildDescString( CTString( " " ) );

			ASSERT( m_iGuildLevel <= MAX_GUILD_LEVEL && "Invalid Guild Level" );

			const int	iMyLevel	= _pNetwork->MyCharacterInfo.level;
			const SQUAD llMyMoney	= _pNetwork->MyCharacterInfo.money;
			const int	lMySP		= _pNetwork->MyCharacterInfo.sp / 10000;
			const int	iNeedLevel	= _GuildConditionTable[m_iGuildLevel].iCaptionNeedLevel;
			const SQUAD llNeedMoney = _GuildConditionTable[m_iGuildLevel].llNeedMoney;
			const int	iNeedSP		= _GuildConditionTable[m_iGuildLevel].iNeedSP;			

			strTemp.PrintF( _S( 909, "���� ��� ���� : %d Lv" ), m_iGuildLevel);		
			AddGuildDescString( strTemp, 0xFFC672FF );

			strTemp.PrintF( _S( 902, "�ִ� ��� �ο� : %d ��" ), _GuildConditionTable[m_iGuildLevel].iMaxMember);		
			AddGuildDescString( strTemp, 0xFFFFFFFF );

			if( iMyLevel < iNeedLevel )
			{
				bSatisfied = FALSE;
			}

			strTemp.PrintF( _S( 903, "�ʿ� ���� : %d Lv" ), _GuildConditionTable[m_iGuildLevel].iCaptionNeedLevel);		
			AddGuildDescString( strTemp, iMyLevel >= iNeedLevel ? 0xFFC672FF : 0xBCBCBCFF );

			if( llMyMoney < llNeedMoney )
			{
				bSatisfied = FALSE;
			}

			strTemp2.PrintF("%I64d", _GuildConditionTable[m_iGuildLevel].llNeedMoney);
			pUIMgr->InsertCommaToString(strTemp2);
			strTemp.PrintF( _S( 904, "�ʿ� ���� : %s ����" ), strTemp2);		
			AddGuildDescString( strTemp, llMyMoney >= llNeedMoney ? 0xFFC672FF : 0xBCBCBCFF );

			if( lMySP < iNeedSP )
			{
				bSatisfied = FALSE;
			}

			strTemp2.PrintF("%d", _GuildConditionTable[m_iGuildLevel].iNeedSP);
			pUIMgr->InsertCommaToString(strTemp2);
			strTemp.PrintF( _S( 905, "�ʿ� S P  : %s SP" ), strTemp2);		
			AddGuildDescString( strTemp, lMySP >= iNeedSP ? 0xFFC672FF : 0xBCBCBCFF );
			
			strTemp2.PrintF("%d", _GuildConditionTable[m_iGuildLevel].iNeedGP);
			pUIMgr->InsertCommaToString(strTemp2);
			strTemp.PrintF( _S(3839, "�ʿ� G P  : %s GP" ), strTemp2);		
			AddGuildDescString( strTemp, 0x70BEFFFF);
		}
		break;
	case GUILD_DESTROY:		// ��� �ػ�
		{
			AddGuildDescString( _S( 910, "�ڳ׵� �ǰ��Ѱ� ����." ) );	
			AddGuildDescString( _S( 911, "������, ���� �׸� �дٸ� ���ݱ��� �ڳ׸� ������ �̵��� �Ǹ��� ũ������, " ) );			
			AddGuildDescString( _S( 912, "�ڳ� ���������ε� ��忡 �鿴�� ����� ��� ��簡 �ǳ�." ) );		
			AddGuildDescString( _S( 913, "�׷��� ��� ���ٸ� �ڳ��� ���� �ϰ�." ) );		
			AddGuildDescString( _S( 914, "���ݱ��� ������ �͸����ε� �ڳ׿��� ������ �����̴ϱ�." ) );		
		}
		break;
	}

	m_btnOK.SetEnable( bSatisfied );
}

// ----------------------------------------------------------------------------
// Name : AddGuildDescString()
// Desc :
// ----------------------------------------------------------------------------
void CUIGuild::AddGuildDescString( CTString &strDesc, COLOR colDesc )
{
	// Get length of string
	INDEX	nLength = strDesc.Length();
	if( nLength == 0 )
		return;

	// wooss 051002
#if defined (THAI)
	// Get length of string
	INDEX	nThaiLen = FindThaiLen(strDesc);
	INDEX	nChatMax= (_iMaxMsgStringChar-1)*(_pUIFontTexMgr->GetFontWidth()+_pUIFontTexMgr->GetFontSpacing());
	if( nLength == 0 )
		return;
	// If length of string is less than max char
	if( nThaiLen <= nChatMax )
	{
		// Check line character
		for( int iPos = 0; iPos < nLength; iPos++ )
		{
			if( strDesc[iPos] == '\n' || strDesc[iPos] == '\r' )
				break;
		}

		// Not exist
		if( iPos == nLength )
		{
			m_lbGuildDesc.AddString( 0, strDesc, colDesc );
		}
		else
		{
			// Split string
			CTString	strTemp, strTemp2;
			strDesc.Split( iPos, strTemp2, strTemp );
			m_lbGuildDesc.AddString( 0, strTemp2, colDesc );

			// Trim line character
			if( strTemp[0] == '\r' && strTemp[1] == '\n' )
				strTemp.TrimLeft( strTemp.Length() - 2 );
			else
				strTemp.TrimLeft( strTemp.Length() - 1 );

			AddGuildDescString( strTemp, colDesc );
		}
	}
	// Need multi-line
	else
	{
		// Check splitting position for 2 byte characters
		int		nSplitPos = _iMaxMsgStringChar;
		BOOL	b2ByteChar = FALSE;
		for( int iPos = 0; iPos < nLength; iPos++ )
		{
			if(nChatMax < FindThaiLen(strDesc,0,iPos))
				break;
		}
		nSplitPos = iPos;

		// Check line character
		for( iPos = 0; iPos < nSplitPos; iPos++ )
		{
			if( strDesc[iPos] == '\n' || strDesc[iPos] == '\r' )
				break;
		}

		// Not exist
		if( iPos == nSplitPos )
		{
			// Split string
			CTString	strTemp, strTemp2;
			strDesc.Split( nSplitPos, strTemp2, strTemp );
			m_lbGuildDesc.AddString( 0, strTemp2, colDesc );

			// Trim space
			if( strTemp[0] == ' ' )
			{
				int	nTempLength = strTemp.Length();
				for( iPos = 1; iPos < nTempLength; iPos++ )
				{
					if( strTemp[iPos] != ' ' )
						break;
				}

				strTemp.TrimLeft( strTemp.Length() - iPos );
			}

			AddGuildDescString( strTemp, colDesc );
		}
		else
		{
			// Split string
			CTString	strTemp, strTemp2;
			strDesc.Split( iPos, strTemp2, strTemp );
			m_lbGuildDesc.AddString( 0, strTemp2, colDesc );

			// Trim line character
			if( strTemp[0] == '\r' && strTemp[1] == '\n' )
				strTemp.TrimLeft( strTemp.Length() - 2 );
			else
				strTemp.TrimLeft( strTemp.Length() - 1 );

			AddGuildDescString( strTemp, colDesc );
		}

	}
#else	
	// If length of string is less than max char
	if( nLength <= _iMaxMsgStringChar )
	{
		// Check line character
		int iPos;
		for( iPos = 0; iPos < nLength; iPos++ )
		{
			if( strDesc[iPos] == '\n' || strDesc[iPos] == '\r' )
				break;
		}

		// Not exist
		if( iPos == nLength )
		{
			m_lbGuildDesc.AddString( 0, strDesc, colDesc );
		}
		else
		{
			// Split string
			CTString	strTemp, strTemp2;
			strDesc.Split( iPos, strTemp2, strTemp );
			m_lbGuildDesc.AddString( 0, strTemp2, colDesc );

			// Trim line character
			if( strTemp[0] == '\r' && strTemp[1] == '\n' )
				strTemp.TrimLeft( strTemp.Length() - 2 );
			else
				strTemp.TrimLeft( strTemp.Length() - 1 );

			AddGuildDescString( strTemp, colDesc );
		}
	}
	// Need multi-line
	else
	{
		// Check splitting position for 2 byte characters
		int		nSplitPos = _iMaxMsgStringChar;
		BOOL	b2ByteChar = FALSE;
		int		iPos;
		for( iPos = 0; iPos < nSplitPos; iPos++ )
		{
			if( strDesc[iPos] & 0x80 )
				b2ByteChar = !b2ByteChar;
			else
				b2ByteChar = FALSE;
		}

		if( b2ByteChar )
			nSplitPos--;

		// Check line character
		for( iPos = 0; iPos < nSplitPos; iPos++ )
		{
			if( strDesc[iPos] == '\n' || strDesc[iPos] == '\r' )
				break;
		}

		// Not exist
		if( iPos == nSplitPos )
		{
			// Split string
			CTString	strTemp, strTemp2;
			strDesc.Split( nSplitPos, strTemp2, strTemp );
			m_lbGuildDesc.AddString( 0, strTemp2, colDesc );

			// Trim space
			if( strTemp[0] == ' ' )
			{
				int	nTempLength = strTemp.Length();
				for( iPos = 1; iPos < nTempLength; iPos++ )
				{
					if( strTemp[iPos] != ' ' )
						break;
				}

				strTemp.TrimLeft( strTemp.Length() - iPos );
			}

			AddGuildDescString( strTemp, colDesc );
		}
		else
		{
			// Split string
			CTString	strTemp, strTemp2;
			strDesc.Split( iPos, strTemp2, strTemp );
			m_lbGuildDesc.AddString( 0, strTemp2, colDesc );

			// Trim line character
			if( strTemp[0] == '\r' && strTemp[1] == '\n' )
				strTemp.TrimLeft( strTemp.Length() - 2 );
			else
				strTemp.TrimLeft( strTemp.Length() - 1 );

			AddGuildDescString( strTemp, colDesc );
		}
	}
#endif
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CUIGuild::Render()
{

	// WSS_NEW_GUILD_SYSTEM 070611 ---------------------->>
	if( m_eGuildState == GUILD_MANAGER_NEW )
	{		
		RenderNew();
		return;
	}
	// --------------------------------------------------<<

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Set skill learn texture
	pDrawPort->InitTextureData( m_ptdBaseTexture );

	// Add render regions
	int	nX, nY, nX2, nY2;

	// Background
	// Top
	nX = m_nPosX + m_nWidth;
	nY = m_nPosY + 26;
	pDrawPort->AddTexture( m_nPosX, m_nPosY, nX, nY,
										m_rtBackTop.U0, m_rtBackTop.V0,
										m_rtBackTop.U1, m_rtBackTop.V1,
										0xFFFFFFFF );

	if( m_eGuildState != GUILD_MANAGER )
	{	
		// Not Manager
		pDrawPort->AddTexture( m_nPosX, nY, nX, nY + DESC_LIST_BOX_HEIGHT + 2,
											m_rtBackMiddle1.U0, m_rtBackMiddle1.V0,
											m_rtBackMiddle1.U1, m_rtBackMiddle1.V1,
											0xFFFFFFFF );

		nY += DESC_LIST_BOX_HEIGHT + 2;
	}
	else
	{
		// Manager
		pDrawPort->AddTexture( m_nPosX, nY, nX, nY + 37,
											m_rtBackManagerTop.U0, m_rtBackManagerTop.V0,
											m_rtBackManagerTop.U1, m_rtBackManagerTop.V1,
											0xFFFFFFFF );

		nY += 37;

		if( m_iUserRanking < GUILD_MEMBER_MEMBER )
		{
			pDrawPort->AddTexture( m_nPosX, nY, nX, nY + MEMBER_LIST_BOX_HEIGHT + 2,
				m_rtBackManagerMiddle.U0, m_rtBackManagerMiddle.V0,
				m_rtBackManagerMiddle.U1, m_rtBackManagerMiddle.V1,
				0xFFFFFFFF );
			
			nY += MEMBER_LIST_BOX_HEIGHT + 2;
		}
		else
		{
			pDrawPort->AddTexture( m_nPosX, nY, nX, nY + MEMBER_LIST_BOX_HEIGHT * 2 + 2,
				m_rtBackManagerMiddle.U0, m_rtBackManagerMiddle.V0,
				m_rtBackManagerMiddle.U1, m_rtBackManagerMiddle.V1,
				0xFFFFFFFF );
			
			nY += MEMBER_LIST_BOX_HEIGHT * 2 + 2;
		}

		pDrawPort->AddTexture( m_nPosX, nY, nX, nY + 4,
											m_rtBackManagerBottom.U0, m_rtBackManagerBottom.V0,
											m_rtBackManagerBottom.U1, m_rtBackManagerBottom.V1,
											0xFFFFFFFF );

		nY += 4;
	}

	// Middle 2
	pDrawPort->AddTexture( m_nPosX, nY, nX, m_nPosY + m_nHeight - 7,
										m_rtBackMiddle2.U0, m_rtBackMiddle2.V0,
										m_rtBackMiddle2.U1, m_rtBackMiddle2.V1,
										0xFFFFFFFF );

	// Bottom
	nY = m_nPosY + m_nHeight - 7;
	pDrawPort->AddTexture( m_nPosX, nY, nX, m_nPosY + m_nHeight,
										m_rtBackBottom.U0, m_rtBackBottom.V0,
										m_rtBackBottom.U1, m_rtBackBottom.V1,
										0xFFFFFFFF );
	// ----------------------------------------------------------------------------
	if( m_eGuildState != GUILD_MANAGER )
	{
	}
	// Guild Manager
	else
	{
		nX = m_nPosX + m_rcTab.Left + GUILD_TAB_WIDTH;
		nY = m_nPosY + m_rcTab.Top;
		nX2 = nX + 1;
		nY2 = nY + 16;
		pDrawPort->AddTexture( nX, nY, nX2, nY2,
												m_rtTab.U0, m_rtTab.V0, m_rtTab.U1, m_rtTab.V1,
												0xFFFFFFFF );	
	}
	
	// Close button
	m_btnClose.Render();

	// Create Guild
	if(m_eGuildState == GUILD_CREATE)
	{
		// Edit Box
		// Lower left
		nX	= m_nPosX + 95;
		nX2 = m_nPosX + m_nWidth - 10;
		nY	= m_nPosY + (EDIT_BOX_Y - 3);
		nY2 = nY + 16;
		pDrawPort->AddTexture( nX, nY, nX + 4, nY2,
			m_rtInputBoxL.U0, m_rtInputBoxL.V0, m_rtInputBoxL.U1, m_rtInputBoxL.V1,
			0xFFFFFFFF );
		// Lower middle
		pDrawPort->AddTexture( nX + 4, nY, nX2 - 4, nY2,
			m_rtInputBoxM.U0, m_rtInputBoxM.V0, m_rtInputBoxM.U1, m_rtInputBoxM.V1,
			0xFFFFFFFF );
		// Lower right
		pDrawPort->AddTexture( nX2 - 4, nY, nX2, nY2,
			m_rtInputBoxR.U0, m_rtInputBoxR.V0, m_rtInputBoxR.U1, m_rtInputBoxR.V1,
			0xFFFFFFFF );

		m_ebGuildName.Render();
	}

	if(m_eGuildState != GUILD_MANAGER)
	{
		// OK button
		m_btnOK.Render();

		// Cancel button
		m_btnCancel.Render();

		m_lbGuildDesc.Render();
	}

	if(m_eGuildState == GUILD_MANAGER)
	{
		if(m_nCurrentTab == GUILD_TAB_MEMBER)
		{
			if( m_iUserRanking < GUILD_MEMBER_MEMBER )
			{
				m_lbMemberList.Render();
				m_btnChangeBoss.Render();		// ���� ����
				m_btnAccept.Render();			// �δ��� �Ӹ�
				m_btnReject.Render();			// �δ��� ����
				m_btnMemberFire.Render();		// ��� ����
			}
			else
			{
				m_lbApplicantList.Render();
			}
		}

		m_btnExit.Render();
	}

	// Render all elements
	pDrawPort->FlushRenderingQueue();

	CTString strTitle = "";
	switch( m_eGuildState )
	{
	case GUILD_CREATE :
		strTitle = _S( 915, "��� �Ἲ" );		
		break;
	case GUILD_UPGRADE:
		strTitle = _S( 916, "��� �±�" );		
		break;
	case GUILD_DESTROY:
		strTitle = _S( 917, "��� ��ü" );		
		break;
	case GUILD_MANAGER:
		//strTitle = _S( 918, "��� ����" );		
		strTitle.PrintF( _S( 919, "%s ��� Lv.%d" ), _pNetwork->MyCharacterInfo.strGuildName, _pNetwork->MyCharacterInfo.lGuildLevel ); 
		break;
	}

	if( m_eGuildState == GUILD_CREATE)
	{
		// Text in guild
		pDrawPort->PutTextEx( _S( 920, "��� �̸�" ), m_nPosX + GUILD_TITLE_TEXT_OFFSETX - 4,		
										m_nPosY + (EDIT_BOX_Y - 2), 0xFFFFFFFF );
	}

	// Text in guild
	pDrawPort->PutTextEx( strTitle, m_nPosX + GUILD_TITLE_TEXT_OFFSETX,
										m_nPosY + GUILD_TITLE_TEXT_OFFSETY, 0xFFFFFFFF );

	if( m_eGuildState == GUILD_MANAGER)
	{
		// Tab
		nY = m_nPosY + 29;
		nX = m_nPosX + m_rcTab.Left + GUILD_TAB_WIDTH / 2;
		pDrawPort->PutTextExCX( _S( 921, "���� ����" ), nX, nY,			
											m_nCurrentTab == GUILD_TAB_MEMBER ? 0xE1B300FF : 0x6B6B6BFF );
	
		nX += GUILD_TAB_WIDTH;
		pDrawPort->PutTextExCX( _S( 922, "�� ��" ), nX, nY,				
											m_nCurrentTab == GUILD_TAB_TREE ? 0xE1B300FF : 0x6B6B6BFF );

		if( m_nCurrentTab == GUILD_TAB_MEMBER )
		{
			CTString strText;

			CTString strLevel;
			switch(m_iUserRanking)
			{
			case GUILD_MEMBER_BOSS:			// �����
				{
					strLevel	= _S( 891, "�����" );	
				}
				break;
			case GUILD_MEMBER_VICE_BOSS:	// ������
				{
					strLevel	= _S( 892, "������" );	
				}
				break;
			case GUILD_MEMBER_MEMBER:		// ����
				{
					strLevel	= _S( 893, "����" );	
				}
				break;
			}

			strText.PrintF( "%s %s", _pNetwork->MyCharacterInfo.name, strLevel );
			pDrawPort->PutTextExCX( strText, m_nPosX + (GUILD_WIDTH / 2),
											m_nPosY + 46, 0xFFFFFFFF );
		}
	
		if( m_iUserRanking != GUILD_MEMBER_MEMBER )
		{
			int nTextY = START_BUTTON_Y + 5;
			
			// Text in guild
			pDrawPort->PutTextEx( _S( 891, "�����" ), m_nPosX + 10,		
				m_nPosY + nTextY, 0xBCBCBCFF );
			
			nTextY += SPAN_TEXT_Y;
			pDrawPort->PutTextEx( m_strBossName, m_nPosX + 10,
				m_nPosY + nTextY, 0xFFFFFFFF );
			
			nTextY += SPAN_TEXT_Y + 4;
			pDrawPort->PutTextEx( _S( 892, "������" ), m_nPosX + 10,		
				m_nPosY + nTextY, 0xBCBCBCFF );
			
			nTextY += SPAN_TEXT_Y;
			pDrawPort->PutTextEx( m_strViceBoss[0], m_nPosX + 10,
				m_nPosY + nTextY, 0xFFFFFFFF );
			
			nTextY += SPAN_TEXT_Y;
			pDrawPort->PutTextEx( m_strViceBoss[1], m_nPosX + 10,
				m_nPosY + nTextY, 0xFFFFFFFF );
		}
		
	}

	// Flush all render text queue
	pDrawPort->EndTextEx();
	
	if(m_eGuildState == GUILD_CREATE)
	{
		// Reading window
		if( m_ebGuildName.DoesShowReadingWindow() )
		{
			// Set texture
			pDrawPort->InitTextureData( m_ptdBaseTexture );

			// Reading window
			m_ebGuildName.RenderReadingWindow();

			// Render all elements
			pDrawPort->FlushRenderingQueue();

			// Flush all render text queue
			pDrawPort->EndTextEx();
		}
	}

}

// ----------------------------------------------------------------------------
// Name : MouseMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT	CUIGuild::MouseMessage( MSG *pMsg )
{

	// TODO : ��� ���� ����
	// ��巹�� 6�̻�...
	if( m_eGuildState == GUILD_MANAGER_NEW )
		return MouseMessageNew (pMsg);
	
	
	WMSG_RESULT	wmsgResult;

	// Title bar
	static BOOL	bTitleBarClick = FALSE;

	// Item clicked
	static BOOL	bLButtonDownInItem = FALSE;

	// Mouse point
	static int	nOldX, nOldY;
	int	nX = LOWORD( pMsg->lParam );
	int	nY = HIWORD( pMsg->lParam );
	
	// Mouse message
	switch( pMsg->message )
	{
	case WM_MOUSEMOVE:
		{
			if( IsInside( nX, nY ) )
				CUIManager::getSingleton()->SetMouseCursorInsideUIs();

			int	ndX = nX - nOldX;
			int	ndY = nY - nOldY;

			// Move shop
			if( bTitleBarClick && ( pMsg->wParam & MK_LBUTTON ) )
			{
				nOldX = nX;	nOldY = nY;
				
				Move( ndX, ndY );
				
				return WMSG_SUCCESS;
			}

			// Close Button
			if( m_btnClose.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;

			if( m_eGuildState != GUILD_MANAGER)
			{
				// OK Button
				if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;
				// Cancel Button
				else if( m_btnCancel.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;
				// List box
				else if( m_lbGuildDesc.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;
				// Guild Name
				else if( m_eGuildState == GUILD_CREATE && m_ebGuildName.MouseMessage( pMsg ) != WMSG_FAIL )
				{					
					return WMSG_SUCCESS;
				}
			}
			else
			{
				if( m_nCurrentTab == GUILD_TAB_MEMBER )
				{
					if( m_iUserRanking < GUILD_MEMBER_MEMBER)
					{
						// Change Boss
						if( m_btnChangeBoss.MouseMessage( pMsg ) != WMSG_FAIL )
							return WMSG_SUCCESS;
						// Accept
						else if( m_btnAccept.MouseMessage( pMsg ) != WMSG_FAIL )
							return WMSG_SUCCESS;
						// Reject
						else if( m_btnReject.MouseMessage( pMsg ) != WMSG_FAIL )
							return WMSG_SUCCESS;
						// Member fire
						else if( m_btnMemberFire.MouseMessage( pMsg ) != WMSG_FAIL )
							return WMSG_SUCCESS;
						// List box
						else if( m_lbMemberList.MouseMessage( pMsg ) != WMSG_FAIL )
							return WMSG_SUCCESS;
						// Exit
						else if( m_btnExit.MouseMessage( pMsg ) != WMSG_FAIL )
							return WMSG_SUCCESS;
					}
					else
					{
						// List box
						if( m_lbApplicantList.MouseMessage( pMsg ) != WMSG_FAIL )
							return WMSG_SUCCESS;
						// Exit
						else if( m_btnExit.MouseMessage( pMsg ) != WMSG_FAIL )
							return WMSG_SUCCESS;
					}
				}	
				else if( m_nCurrentTab == GUILD_TAB_TREE )
				{
					// Exit
					if( m_btnExit.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			if( IsInside( nX, nY ) )
			{
				CUIManager* pUIManager = CUIManager::getSingleton();

				nOldX = nX;		nOldY = nY;

				// Close button
				if( m_btnClose.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				// Title bar
				else if( IsInsideRect( nX, nY, m_rcTitle ) )
				{
					bTitleBarClick = TRUE;
				}
				// tab
				else if( m_eGuildState == GUILD_MANAGER && IsInsideRect( nX, nY, m_rcTab ) )
				{
					int	nOldTab = m_nCurrentTab;
					int	nCurTab = ( nX - m_nPosX - m_rcTab.Left ) / GUILD_TAB_WIDTH;

					if( nCurTab >= 0 && nCurTab < GUILD_TAB_TOTAL )
					{
						m_nCurrentTab = nCurTab;
					}
				}
				else if( m_eGuildState != GUILD_MANAGER )
				{
					// OK Button
					if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Cancel Button
					else if( m_btnCancel.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;					
					// Guild Name
					else if( (m_eGuildState == GUILD_CREATE) && (m_ebGuildName.MouseMessage( pMsg ) != WMSG_FAIL ) )
					{
						// WSS_NEW_GUILD_SYSTEM 070702
						m_ebGuildName.SetFocus(TRUE);
						// Date : 2005-03-10,   By Lee Ki-hwan
						pUIManager->RearrangeOrder( UI_GUILD, TRUE );
						return WMSG_SUCCESS;
					}
					// List boxi
					else if( m_lbGuildDesc.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
				else
				{
					if( m_nCurrentTab == GUILD_TAB_MEMBER )
					{
						if( m_iUserRanking < GUILD_MEMBER_MEMBER)
						{
							// Change Boss
							if( m_btnChangeBoss.MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;
							// Accept
							else if( m_btnAccept.MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;
							// Reject
							else if( m_btnReject.MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;
							// Member fire
							else if( m_btnMemberFire.MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;
							// List box
							else if( m_lbMemberList.MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;
							// Exit
							else if( m_btnExit.MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;
						}
						else
						{
							// List box
							if( m_lbApplicantList.MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;
							// Exit
							else if( m_btnExit.MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;
						}
					}				
					else if( m_nCurrentTab == GUILD_TAB_TREE )
					{
						// Exit
						if( m_btnExit.MouseMessage( pMsg ) != WMSG_FAIL )
							return WMSG_SUCCESS;
					}
				}

				pUIManager->RearrangeOrder( UI_GUILD, TRUE );
				return WMSG_SUCCESS;
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			bTitleBarClick = FALSE;

			// Close button
			if( (wmsgResult = m_btnClose.MouseMessage( pMsg ) ) != WMSG_FAIL )
			{
				if(wmsgResult == WMSG_COMMAND)
				{
					ResetGuild();
				}
				return WMSG_SUCCESS;
			}
			else if( m_eGuildState != GUILD_MANAGER )
			{
				// OK Button
				if( (wmsgResult = m_btnOK.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if(wmsgResult == WMSG_COMMAND)
					{
						PressOKBtn();
					}
					return WMSG_SUCCESS;
				}
				// Cancel Button
				else if( (wmsgResult = m_btnCancel.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if(wmsgResult == WMSG_COMMAND)
					{
						ResetGuild();
					}
					return WMSG_SUCCESS;
				}
				// List box
				else if( m_lbGuildDesc.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					return WMSG_SUCCESS;
				}
			}
			else
			{
				if( m_nCurrentTab == GUILD_TAB_MEMBER )
				{	
					if( m_iUserRanking < GUILD_MEMBER_MEMBER)
					{
						// Change Boss(���� ����)
						if( (wmsgResult = m_btnChangeBoss.MouseMessage( pMsg ) ) != WMSG_FAIL )
						{
							if(wmsgResult == WMSG_COMMAND)
							{
								ChangeBoss();
							}
							return WMSG_SUCCESS;
						}
						// Accept(�δ��� �Ӹ�)
						else if( (wmsgResult = m_btnAccept.MouseMessage( pMsg ) ) != WMSG_FAIL )
						{
							if(wmsgResult == WMSG_COMMAND)
							{
								AddViceBoss();
							}
							return WMSG_SUCCESS;
						}
						// Reject(�δ��� ����)
						else if( (wmsgResult = m_btnReject.MouseMessage( pMsg ) ) != WMSG_FAIL )
						{
							if(wmsgResult == WMSG_COMMAND)
							{
								DelViceBoss();
							}
							return WMSG_SUCCESS;
						}
						// Member fire(�ܿ� ����)
						else if( (wmsgResult = m_btnMemberFire.MouseMessage( pMsg ) ) != WMSG_FAIL )
						{
							if(wmsgResult == WMSG_COMMAND)
							{
								MemberFire();
							}
							return WMSG_SUCCESS;
						}
						// List box
						else if( m_lbMemberList.MouseMessage( pMsg ) != WMSG_FAIL )
						{
							return WMSG_SUCCESS;
						}
						// Exit
						else if( (wmsgResult = m_btnExit.MouseMessage( pMsg ) ) != WMSG_FAIL )
						{
							if(wmsgResult == WMSG_COMMAND)
							{
								ResetGuild();
							}
							return WMSG_SUCCESS;
						}
					}
					else
					{
						// List box
						if( m_lbApplicantList.MouseMessage( pMsg ) != WMSG_FAIL )
						{
							return WMSG_SUCCESS;
						}
						// Exit
						else if( (wmsgResult = m_btnExit.MouseMessage( pMsg ) ) != WMSG_FAIL )
						{
							if(wmsgResult == WMSG_COMMAND)
							{
								ResetGuild();
							}
							return WMSG_SUCCESS;
						}
					}
				}			
				else if( m_nCurrentTab == GUILD_TAB_TREE )
				{
					// Exit
					if( (wmsgResult = m_btnExit.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if(wmsgResult == WMSG_COMMAND)
						{
							ResetGuild();
						}
						return WMSG_SUCCESS;
					}
				}
			}
		}
		break;

	case WM_RBUTTONDOWN:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();

			if( m_pGuildMember && m_pGuildMember->IsInside( nX, nY) )
			{
				if (pUIManager->GetGuild()->IsEnabled() && !pUIManager->GetGuild()->IsVisible())
				{
					pUIManager->RearrangeOrder( UI_GUILD, TRUE );
				}

				CTString strTargetName;
				switch(m_iSelTab)
				{
				case NEW_GUILD_MEMBER_INFO:
					{
						if (m_bApplyDonateUI == FALSE)
						{
							if (m_pGuildMember->m_pList == NULL)
								return WMSG_FAIL;

							return OpenGuildPop(m_pGuildMember->m_pList->getMouseOverItem(), nX, nY);
						}						
					}
					break;
				}
				pUIManager->RearrangeOrder( UI_GUILD, TRUE );
				return WMSG_SUCCESS;
			}
			else
			{
				pUIManager->GetSimplePop()->ClosePop();
			}
		}
		break;
	case WM_MOUSEWHEEL:
		{
			if( IsInside( nX, nY ) )
			{
				if( m_eGuildState != GUILD_MANAGER )
				{
					// List box of guild desc
					if( m_lbGuildDesc.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
				else
				{
					if( m_nCurrentTab == GUILD_TAB_MEMBER )
					{
						if( m_iUserRanking < GUILD_MEMBER_MEMBER)
						{
							// List box of member list
							if( m_lbMemberList.MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;
						}
						else
						{
							// List box of member list
							if( m_lbApplicantList.MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;
						}
					}				
				}
			}
		}
		break;

	}
	return WMSG_FAIL;
}

// ----------------------------------------------------------------------------
// Name : KeyMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT	CUIGuild::KeyMessage( MSG *pMsg )
{	
	if( !IsFocused() )
		return WMSG_FAIL;

	if( m_iGuildLevel < LIMIT_GUILD_LEVEL )
	{
		if( m_ebGuildName.KeyMessage( pMsg ) != WMSG_FAIL )
		{
			return WMSG_SUCCESS; 
		}
	}
	else 
	{
		switch(m_iSelTab)
		{
		case NEW_GUILD_NOTICE:
			{
				if( m_ebNoticeTitle.KeyMessage( pMsg ) != WMSG_FAIL )
				{
					return WMSG_SUCCESS; 
				}
				if( m_mebNoticeContent.KeyMessage( pMsg ) != WMSG_FAIL )
				{
					return WMSG_SUCCESS; 
				}	
				if( pMsg->wParam == VK_TAB )
				{
					if( m_ebNoticeTitle.IsFocused() )
					{
						m_ebNoticeTitle.SetFocus( FALSE );
						m_mebNoticeContent.SetFocus( TRUE );					
					}
					else if( m_mebNoticeContent.IsFocused() )
					{
						m_ebNoticeTitle.SetFocus( TRUE );
						m_mebNoticeContent.SetFocus( FALSE );
					}
					return WMSG_SUCCESS;
				}
			}
			break;
		case NEW_GUILD_MEMBER_INFO:
			{
				if (m_bApplyDonateUI)
				{
					if (m_pGuildDonateUI != NULL)
					{	
						if (m_pGuildDonateUI->KeyMessage(pMsg) != WMSG_FAIL)
							return WMSG_SUCCESS;
					}					
				}
			}
			break;
		case NEW_GUILD_MANAGE:
			{
				if(m_bApplySettingOn)
				{
					if (m_pGuildChangeSetUI != NULL)
					{	
						if (m_pGuildChangeSetUI->KeyMessage(pMsg) != WMSG_FAIL)
							return WMSG_SUCCESS;
					}					
				}
				else if (m_bApplyDonateUI)
				{
					if (m_pGuildDonateUI != NULL)
					{	
						if (m_pGuildDonateUI->KeyMessage(pMsg) != WMSG_FAIL)
							return WMSG_SUCCESS;
					}					
				}
			}			
			break;	
#ifndef LOCAL_NEW_GUILD // �ؿ� ���� �������� ����
		case NEW_GUILD_BOARD:
			{
				// List
				if( pWEB->m_nCurBoardType == UWT_LIST )
				{
					if( pMsg->wParam == VK_RETURN )
					{
						if( m_ebSearch.IsFocused() )
						{
							pWEB->m_nWantPage = 1;
							pWEB->DelayCommandPrepare(new CCommandList);
							return WMSG_SUCCESS;
						}
					}
					// Search edit box
					if( m_ebSearch.KeyMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
				else if( pWEB->m_nCurBoardType >= UWT_WRITE && pWEB->m_nCurBoardType <= UWT_MODIFY )
				{
					// �̱�ȯ ���� ����(05.01.01) : ����� ���� ���̿� TABŰ�� ��Ŀ�� �̵�
					if( pMsg->wParam == VK_TAB )
					{
						if( m_ebWriteSubject.IsFocused() )
						{
							m_ebWriteSubject.SetFocus ( FALSE );
							m_mebContent.SetFocus ( TRUE );

						}
						else if( m_mebContent.IsFocused() )
						{
							m_ebWriteSubject.SetFocus ( TRUE );
							m_mebContent.SetFocus ( FALSE );
						}
						return WMSG_SUCCESS;
					}
					// �̱�ȯ ���� �� : 
						
					
					// �̱�ȯ ���� ����(05.01.01) : ��Ƽ ����Ʈ �ڽ� ��ƾ �߰� 
					// Subject edit box
					if ( m_ebWriteSubject.KeyMessage ( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Content multi-edit box
					else if ( m_mebContent.KeyMessage ( pMsg ) != WMSG_FAIL )
					{
						return WMSG_SUCCESS;
					}
					// �̱�ȯ ���� ��
				}
			}
			break;
#endif		
		}	
	}	
	return WMSG_FAIL;
}

// ----------------------------------------------------------------------------
// Name : IMEMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT	CUIGuild::IMEMessage( MSG *pMsg )
{
	if( m_iGuildLevel < LIMIT_GUILD_LEVEL )
	{
		if(m_ebGuildName.IsFocused())
			return m_ebGuildName.IMEMessage( pMsg );
	}
	else {
		switch(m_iSelTab)
		{
		case NEW_GUILD_NOTICE:
			{
				if(m_ebNoticeTitle.IsFocused())
					return m_ebNoticeTitle.IMEMessage( pMsg );
				if(m_mebNoticeContent.IsFocused())
					return m_mebNoticeContent.IMEMessage( pMsg );
			}
			break;
		case NEW_GUILD_MEMBER_INFO:
			{
				if (m_bApplyDonateUI)
				{
					if (m_pGuildDonateUI != NULL)
					{
						if ( m_pGuildDonateUI->IsFocused() == true)
							return m_pGuildDonateUI->IMEMessage( pMsg );
					}
				}
			}
			break;
		case NEW_GUILD_MANAGE:
			{
				if(m_bApplySettingOn)
				{
					if (m_pGuildChangeSetUI != NULL)
					{
						if ( m_pGuildChangeSetUI->IsFocused() == true)
							return m_pGuildChangeSetUI->IMEMessage( pMsg );
					}
				}
				else if (m_bApplyDonateUI)
				{
					if (m_pGuildDonateUI != NULL)
					{
						if ( m_pGuildDonateUI->IsFocused() == true)
							return m_pGuildDonateUI->IMEMessage( pMsg );
					}
				}
			}			
			break;
#ifndef LOCAL_NEW_GUILD // �ؿ� ���� �������� ����
		case NEW_GUILD_BOARD:
			{
				// List
				if( pWEB->m_nCurBoardType == UWT_LIST )
				{				
					// Search edit box
					return m_ebSearch.IMEMessage( pMsg );				
				}
				else if( pWEB->m_nCurBoardType >= UWT_WRITE && pWEB->m_nCurBoardType <= UWT_MODIFY )
				{					
					// Subject edit box
					WMSG_RESULT wmsgResult;
					if ( ( wmsgResult = m_ebWriteSubject.IMEMessage( pMsg ) ) != WMSG_FAIL ) 
					{
						return wmsgResult;
					}
					
					if (m_mebContent.GetAllStringLength() >= 1024)
					{
						return WMSG_FAIL;
					}

					// Content multi-edit box
					return m_mebContent.IMEMessage ( pMsg );			
				}
			}
			break;
#endif
		}	
	}
	return WMSG_FAIL;
}

// ----------------------------------------------------------------------------
// Name : CharMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT	CUIGuild::CharMessage( MSG *pMsg )
{
	if( m_iGuildLevel < LIMIT_GUILD_LEVEL )
	{
		if( m_ebGuildName.CharMessage( pMsg ) != WMSG_FAIL )
		{
			return WMSG_SUCCESS;
		}

	}
	else 
	{
		switch(m_iSelTab)
		{
		case NEW_GUILD_NOTICE:
			{
				if( m_ebNoticeTitle.CharMessage( pMsg ) != WMSG_FAIL )
				{
					return WMSG_SUCCESS; 
				}
				if( m_mebNoticeContent.CharMessage( pMsg ) != WMSG_FAIL )
				{
					return WMSG_SUCCESS; 
				}
			}
			break;
		case NEW_GUILD_MEMBER_INFO:
			{
				if (m_bApplyDonateUI)
				{
					if (m_pGuildDonateUI != NULL)
					{
						if( m_pGuildDonateUI->CharMessage( pMsg ) != WMSG_FAIL )
							return WMSG_SUCCESS; 
					}
				}
			}
		case NEW_GUILD_MANAGE:
			{
				if(m_bApplySettingOn)
				{
					if (m_pGuildChangeSetUI != NULL)
					{
						if( m_pGuildChangeSetUI->CharMessage( pMsg ) != WMSG_FAIL )
							return WMSG_SUCCESS; 
					}
				}
				else if (m_bApplyDonateUI)
				{
					if (m_pGuildDonateUI != NULL)
					{
						if( m_pGuildDonateUI->CharMessage( pMsg ) != WMSG_FAIL )
							return WMSG_SUCCESS; 
					}
				}
			}			
			break;
#ifndef LOCAL_NEW_GUILD // �ؿ� ���� �������� ����
		case NEW_GUILD_BOARD:
			{
				// List
				if( pWEB->m_nCurBoardType == UWT_LIST )
				{
					// Search edit box
					if( m_ebSearch.CharMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
				else if( pWEB->m_nCurBoardType >= UWT_WRITE && pWEB->m_nCurBoardType <= UWT_MODIFY )
				{
					// Subject edit box
					if( m_ebWriteSubject.CharMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// �̱�ȯ ���� ����(05.01.01) : ��Ƽ ����Ʈ �ڽ� ��ƾ �߰� 

					if (m_mebContent.GetAllStringLength() >= 1024)
					{
						return WMSG_FAIL;
					}

					// Content multi-edit box
					if ( m_mebContent.CharMessage ( pMsg ) != WMSG_FAIL )
					{
						return WMSG_SUCCESS;
					}								
				}
			}
			break;
#endif
			
		}	

	}
	return WMSG_FAIL;
}

// ----------------------------------------------------------------------------
// Name : MsgBoxCommand()
// Desc :
// ----------------------------------------------------------------------------
void CUIGuild::MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput )
{	
	CUIManager* pUIManager = CUIManager::getSingleton();

	switch( nCommandCode )
	{
	case MSGCMD_GUILD_ERROR:	// ���� �߻�
		{
			if( !bOK )
				return;
		}
		break;
	case MSGCMD_GUILD_JOIN:		// ��� ����
		{
			if( !bOK )
				return;

// 			if (_pNetwork->IsRvrZone() && _pNetwork->MyCharacterInfo.iSyndicateType != m_iSyndiType)
// 			{
// 				pUIManager->GetChattingUI()->AddSysMessage( _S( 6090, "���� �������� ���� ������ ��� ����� �� ���� ����Դϴ�."  ), SYSMSG_ERROR );	
// 				return;
// 			}

			CTString	strMessage;
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(  _S( 865, "���" ) , UMBS_CANCEL, UI_GUILD, MSGCMD_GUILD_JOIN_REQ );	
			strMessage.PrintF(  _S( 923, "��� ���� ��û���Դϴ�." )  );		
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );

			_pNetwork->GuildJoin( g_lGuildIndex, g_lChaIndex, _pNetwork->MyCharacterInfo.index );
		}
		break;
	case MSGCMD_GUILD_JOIN_REQ:
		{
			// ������ ����ϸ� 1 �ƴϸ� 0
			_pNetwork->GuildApplicantReject( FALSE );
		}
		break;
	case MSGCMD_GUILD_QUIT:		// ��� Ż��
		{
			if( !bOK )
				return;
			_pNetwork->GuildQuit();
		}
		break;
	case MSGCMD_GUILD_DESTROY:			// ��� �ػ�
		{
			if( !bOK )
				return;
			DestroyGuild();
		}
		break;
	case MSGCMD_GUILD_APPLICANT_JOIN:	// ��û�� ����.
		{
			if( !bOK )
				// ������ ����ϸ� 1 �ƴϸ� 0
				_pNetwork->GuildApplicantReject( TRUE );			// ���� �ź�
			else
				_pNetwork->GuildApplicantAccept( g_lChaIndex );		// ���� ���
		}
		break;

	case MSGCMD_GUILD_ADD_VICE_BOSS:	// �ΰ� �Ӹ�
		{
			if( !bOK )
				return;
			_pNetwork->GuildAddViceBoss( g_lMemberIndex );
		}
		break;
	case MSGCMD_GUILD_DEL_VICE_BOSS:	// �ΰ� ����
		{
			if( !bOK )
				return;
			_pNetwork->GuildDelViceBoss( g_lMemberIndex );
		}
		break;
	case MSGCMD_GUILD_CHANGE_BOSS:		// ���� ����
		{
			if( !bOK )
				return;
			_pNetwork->GuildChangeBoss( g_lMemberIndex );
		}
		break;
	case MSGCMD_GUILD_KICK:				// ��� ¥����
		{
			if( !bOK )
				return;
			_pNetwork->GuildMemberFire( g_lMemberIndex );
		}
		break;
	case MSGCMD_GUILD_ROOM:				// ��� ���� ��������...
		{
			if( !bOK )
				return;
			GoGuildZone();
		}
		break;
	// 1107 ��� �ý��� ���� [trylord 11/12/28]
	case MSGCMD_GUILDMASTER_KICK_REQUEST:
		{
			if( !bOK )
				break;

			_pNetwork->SendGuildMasterKickReq(_pNetwork->MyCharacterInfo.lGuildIndex);
		}
		break;

	case MSGCMD_GUILDMASTER_KICK_CANCEL_REQUEST:
		{
			if( !bOK )
				break;

			_pNetwork->SendGuildMasterKickCancelReq(_pNetwork->MyCharacterInfo.lGuildIndex);
		}
		break;

	case MSGCMD_GUILDREMOTE_JOIN_TOUSER:
		{
			if( !bOK )
			{
				_pNetwork->SendGuildRemoteJoinNOReq();
			}
			else
			{
				_pNetwork->SendGuildRemoteJoinOKReq(GetRemoteGuildJoinTaget(), 1);
			}
		}
		break;

	case MSGCMD_GUILDREMOTE_JOIN_TOMASTER:
		{
			if( !bOK )
			{
				_pNetwork->SendGuildRemoteJoinNOReq();
			}
			else
			{
				_pNetwork->SendGuildRemoteJoinOKReq(GetRemoteGuildJoinTaget(), 0);
			}
		}
		break;

	case MSGCMD_GUILD_RECALL:
		{
			if (bOK)
			{
				_pNetwork->SendGuildRecallReq();
			}
		}
		break;

	case MSGCMD_GUILD_RECALL_USE_REQ:
		{
			if (bOK)
			{
				pUIManager->GetCharacterInfo()->UseSkill( DEF_GUILD_RECALL_SKILL_IDX );
			}
		}
		break;
	}
}

// ----------------------------------------------------------------------------
// Name : MsgBoxLCommand()
// Desc :
// ----------------------------------------------------------------------------
void CUIGuild::MsgBoxLCommand( int nCommandCode, int nResult )
{
	switch( nCommandCode )
	{
	case MSGLCMD_GUILD_REQ:
		{
			// [090527: selo] Ȯ���� ����Ʈ �̾߱� �Ѵ� ó�� ������ ���� ��ƾ
			int iQuestIndex = -1;
			if( ciQuestClassifier < nResult )	
			{
				iQuestIndex = nResult;
				nResult = ciQuestClassifier;
			}

			switch ( nResult ) 
			{
			case SEL_GUILD_CREATE:
				{
					// ��� ����� �ƴҶ��� ��� ������.
					if( m_iUserRanking == GUILD_MEMBER_NOMEMBER )
					{
						m_eGuildState = GUILD_CREATE; 
						GetGuildDesc( TRUE );
						CUIManager::getSingleton()->RearrangeOrder( UI_GUILD, TRUE );
					}
					else
					{
						m_eGuildState = GUILD_REQ;
						CUIManager::getSingleton()->RearrangeOrder( UI_GUILD, FALSE );
					}
				}
				break;

			case SEL_GUILD_DESTROY:
				{
					m_eGuildState = GUILD_DESTROY;
					GetGuildDesc( TRUE );
					CUIManager::getSingleton()->RearrangeOrder( UI_GUILD, TRUE );
				}
				break;

			case SEL_GUILD_UPGRADE:			// ��� �±�
				{
					if( m_iGuildLevel < MAX_GUILD_LEVEL )
					{
						m_eGuildState = GUILD_UPGRADE;
						GetGuildDesc( TRUE );
						CUIManager::getSingleton()->RearrangeOrder( UI_GUILD, TRUE );
					}
					else
					{
						m_eGuildState = GUILD_REQ;
						CUIManager::getSingleton()->RearrangeOrder( UI_GUILD, FALSE );
					}
				}
				break;

			case SEL_GUILD_ROOM:
				{
					CUIManager::getSingleton()->CloseMessageBox( MSGCMD_GUILD_ROOM );
					CTString	strMessage;
					CUIMsgBox_Info	MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILD_ROOM );	
					strMessage.PrintF( _S( 1012, "��� ��ȭ������ �̵��Ͻðڽ��ϱ�?" ) );
					MsgBoxInfo.AddString( strMessage );
					CUIManager::getSingleton()->CreateMessageBox( MsgBoxInfo );				
				}
				break;

			case SEL_GUILD_TALK:
				{
					// ����Ʈ â ����
					//CUIManager::getSingleton()->GetQuest()->OpenQuest( CUIManager::getSingleton()->GetCharacterInfo()->GetMobIndex(), m_fNpcX, m_fNpcZ );
					CUIQuestBook::TalkWithNPC();
				}
				break;

			// [2010/06/30 : Sora] ���� ��� �����ο�
			case SEL_GUILD_BUFF:
				{
					_pNetwork->SendOwnerGuildBuffReq();
				}
				break;
				
				// [090527: selo] Ȯ���� ����Ʈ ����
			case ciQuestClassifier:
				{
					// ������ ����Ʈ�� ���� ���� �Ǵ� ���� â�� ����.
					CUIQuestBook::SelectQuestFromMessageBox( iQuestIndex );					
				}
				break;
// ==> 1107 ��� �ý��� ���� [trylord 11/12/28]
			case SEL_GUILDMASTER_KICK_REQUEST:
				{	// ����� ���� ��û
					CUIManager::getSingleton()->CloseMessageBox( SEL_GUILDMASTER_KICK_REQUEST );
					CTString	strMessage;
					CUIMsgBox_Info	MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILDMASTER_KICK_REQUEST );	
					strMessage.PrintF( _S(5615, "[%s] ����� ����� ���� �ɻ縦 ��û �Ͻðڽ��ϱ�?"), _pNetwork->MyCharacterInfo.strGuildName );
					MsgBoxInfo.AddString( strMessage );
					CUIManager::getSingleton()->CreateMessageBox( MsgBoxInfo );
				}
				break;

			case SEL_GUILDMASTER_KICK_CANCEL_REQUEST:
				{	// ����� ���� ���� ��û
					if(_pNetwork->MyCharacterInfo.lGuildPosition != GUILD_MEMBER_BOSS)
					{	// ������� �ƴ� ��
						CUIManager::getSingleton()->CloseMessageBox( MSGCMD_GUILD_ERROR );
						CUIMsgBox_Info	MsgBoxInfo;
						MsgBoxInfo.SetMsgBoxInfo(  _S( 865, "���" ) , UMBS_OK, UI_GUILD, MSGCMD_GUILD_ERROR );		// Ȯ�θ� �ϸ� �ǹǷ� MSGCMD_GUILD_ERROR ������
						MsgBoxInfo.AddString( _S(5616, "����常 �������Ⱑ �����մϴ�." ));
						CUIManager::getSingleton()->CreateMessageBox( MsgBoxInfo );	

						return;
					}

					CUIManager::getSingleton()->CloseMessageBox( SEL_GUILDMASTER_KICK_CANCEL_REQUEST );
					CTString	strMessage;
					CUIMsgBox_Info	MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILDMASTER_KICK_CANCEL_REQUEST );	
					strMessage.PrintF( _S(5617, "����� ���ӿ� �������⸦ �Ͻðڽ��ϱ�?") );
					MsgBoxInfo.AddString( strMessage );
					CUIManager::getSingleton()->CreateMessageBox( MsgBoxInfo );
				}
				break;
// <== 1107 ��� �ý��� ���� [trylord 11/12/28]	

			default:		// ���
				{
					m_eGuildState = GUILD_REQ;
					CUIManager::getSingleton()->RearrangeOrder( UI_GUILD, FALSE );
				}
				break;
			}
		}
	}
}


void CUIGuild::SetMemberName(int charIndex,CTString strName)
{
	std::vector<sGuildMember>::iterator iBegin,iEnd,iNext;
	iBegin = iNext = m_vectorMemberList.begin();
	iEnd = m_vectorMemberList.end();
	for( ; iNext != iEnd ; iNext++)
	{
		if(iNext->lIndex == charIndex){
			iNext->strMemberName = strName;
			return;
		}
	}


	
}

// ��� �ý��� �߰� �۾� ------------------------------------------------------------------------------------------->>
// WSS_NEW_GUILD_SYSTEM 070703

// ----------------------------------------------------------------------------
// Name : InitNewGuildSystem()
// Desc :
// ----------------------------------------------------------------------------
void CUIGuild::InitNewGuildSystem()
{
	m_iSelTab				= 0;				// ����Ʈ ��
	m_iGuildAverageLevel	= 0;				// ��� ��� ����
	m_iGuildOwnLand			= 0;				// ��� ���� ����
	m_iGuildTotalPoint		= 0;				// ��� �� ����Ʈ
	m_iGuildMyPoint			= 0;				// ���� �⿩ ����Ʈ
	m_bApplySettingOn		= FALSE;			// ���� ����â ����
	m_bApplyDonateUI	= FALSE;
	m_iOnlineMembers		= 0;				// ������ ����	
	m_iGuildSkillPos		= 0;
	m_bIsSelList			= FALSE;	
	m_bEnableCorrect		= FALSE;			// �������� ��������
	m_lbMemberAllianceList.ResetAllStrings();
	m_lbMemberHostilityList.ResetAllStrings();
	if (m_pGuildMember != NULL)
		m_pGuildMember->resetList();
	m_sbGuildSkillBar.SetScrollPos(0);
	m_ebNoticeTitle.ResetString();
	m_mebNoticeContent.ResetString();	
	m_lbManageMemberList.ResetAllStrings();
	m_lbManageMemberListEx.ResetAllStrings();
	m_lbGuildSkillDesc.ResetAllStrings();	
	m_ebSearch.ResetString();
	m_lbListContent.ResetAllStrings();
	m_lbReadContent.ResetAllStrings();
	m_ebWriteSubject.ResetString();	
	m_mebContent.ResetString();

	// Init Web Board
	pWEB->m_nCurSection = UWS_GUILD;
	pWEB->m_nCurBoardType = UWT_LIST;	
	pWEB->m_nWantModifyMode = UWM_WRITE;
	pWEB->m_nCurrentPage = 0;
	
	m_nSelSkillTab = GUILD_SKILL_PASSIVE;
	m_sbGuildSkillBar.SetCurItemCount(m_vecGuildPassiveSkill.size());

	// [1/3/2011 kiny8216] NEW_CORPS
	m_iCorpsMember		= 0;
	m_iCorpsBoss		= 0;
}

// ----------------------------------------------------------------------------
// Name : CreateNew()
// Desc :
// ----------------------------------------------------------------------------
void CUIGuild::CreateNew( CUIWindow *pParentWnd, int nX, int nY)
{	
	int		i;
	// Region of each part
	m_rcTitleNew.SetRect( 0, 0, NEW_GUILD_SYSTEM_WIDTH-35, 22 );
	m_rcWindowNew.SetRect( 0, 0, NEW_GUILD_SYSTEM_WIDTH, NEW_GUILD_SYSTEM_HEIGHT );
	for( i = 0; i < MAX_GUILDINFO_TAB; i++ )
	{
		m_rcTabNew[i].SetRect( 98*i+7, 27, 98*(i+1)+6, 47 );
	}

	// window position
//	SetPos( nX, nY );	
//	SetSize( NEW_GUILD_SYSTEM_WIDTH, NEW_GUILD_SYSTEM_HEIGHT );

	// Create texture
	ASSERT(m_ptdBaseTexture!=NULL);
	FLOAT	fTexWidth = m_ptdBaseTexture->GetPixWidth();
	FLOAT	fTexHeight = m_ptdBaseTexture->GetPixHeight();

	
	// ��� ���� --------------------------------------------->>
	// UV Coordinate of each part

	// Set Box
	m_bxBackGroundBox.SetBoxUV(m_ptdBaseTexture,30,22,WRect(0,0,216,22));
	m_bxBackGroundBox2.SetBoxUV(m_ptdBaseTexture,20,11,WRect(0,22,216,45));	
	m_bxBox1.SetBoxUV(m_ptdBaseTexture,3,WRect(0,68,34,102));
	m_bxBox1_1.SetBoxUV(m_ptdBaseTexture,3,WRect(0,68,32,100));
	m_bxBox1_2.SetBoxUV(m_ptdBaseTexture,3,WRect(0,72,36,102));
	m_bxBox2.SetBoxUV(m_ptdBaseTexture,3,WRect(42,86,245,105));

	// List box of Alliance List
	m_lbMemberAllianceList.Create( this, 287,151,135,133, _pUIFontTexMgr->GetLineHeight(), 13, 3, 2, TRUE );
	m_lbMemberAllianceList.CreateScroll( TRUE, 0, 0, 9, 133, 9, 7, 0, 0, 10 );
	m_lbMemberAllianceList.SetSelBar( 129 , _pUIFontTexMgr->GetLineHeight(), 187, 46, 204, 61, fTexWidth, fTexHeight );
	m_lbMemberAllianceList.SetOverColor( 0xF8E1B5FF );
	m_lbMemberAllianceList.SetSelectColor( 0xF8E1B5FF );
	m_lbMemberAllianceList.SetColumnPosX( 1, 110 );
	// Up button
	m_lbMemberAllianceList.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbMemberAllianceList.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbMemberAllianceList.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbMemberAllianceList.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbMemberAllianceList.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbMemberAllianceList.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbMemberAllianceList.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbMemberAllianceList.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbMemberAllianceList.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbMemberAllianceList.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbMemberAllianceList.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );	

	// List box of Hostility List
	m_lbMemberHostilityList.Create( this, 437, 151, 135, 133, _pUIFontTexMgr->GetLineHeight(), 13, 3, 2, TRUE );
	m_lbMemberHostilityList.CreateScroll( TRUE, 0, 0, 9, 133, 9, 7, 0, 0, 10 );
	m_lbMemberHostilityList.SetSelBar( 129 , _pUIFontTexMgr->GetLineHeight(), 187, 46, 204, 61, fTexWidth, fTexHeight );
	m_lbMemberHostilityList.SetOverColor( 0xF8E1B5FF );
	m_lbMemberHostilityList.SetSelectColor( 0xF8E1B5FF );
	m_lbMemberHostilityList.SetColumnPosX( 1, 110 );
	// Up button
	m_lbMemberHostilityList.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbMemberHostilityList.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbMemberHostilityList.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbMemberHostilityList.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbMemberHostilityList.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbMemberHostilityList.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbMemberHostilityList.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbMemberHostilityList.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbMemberHostilityList.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbMemberHostilityList.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbMemberHostilityList.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );	

	// Background
	m_uvTabNew.SetUV( 0, 0, 216, 26, fTexWidth, fTexHeight );

	// Lines
	m_uvLineH.SetUV(43,86,244,86,fTexWidth,fTexHeight);
	m_uvLineV.SetUV(43,86,43,103,fTexWidth,fTexHeight);

	// Buttons
	// Close button
	m_btnCloseNew.Create( this, CTString( "" ), 572, 5, 14, 14 );
	m_btnCloseNew.SetUV( UBS_IDLE, 219, 0, 233, 14, fTexWidth, fTexHeight );
	m_btnCloseNew.SetUV( UBS_CLICK, 234, 0, 248, 14, fTexWidth, fTexHeight );
	m_btnCloseNew.CopyUV( UBS_IDLE, UBS_ON );
	m_btnCloseNew.CopyUV( UBS_IDLE, UBS_DISABLE );
	// Exit button
	m_btnExitNew.Create( this, _S( 870, "�ݱ�" ), 523,308, 63, 21 );			
	m_btnExitNew.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnExitNew.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnExitNew.CopyUV( UBS_IDLE, UBS_ON );
	m_btnExitNew.CopyUV( UBS_IDLE, UBS_DISABLE );
	// Edit button
	m_btnEdit.Create( this, _S(3840, "����" ), 215, 255, 63, 21 );			
	m_btnEdit.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnEdit.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnEdit.CopyUV( UBS_IDLE, UBS_ON );
	m_btnEdit.CopyUV( UBS_IDLE, UBS_DISABLE );
	// Guild Mark button
	m_btnGuildMarkBack.Create( this, CTString(""), 26, 244, 33, 33 );			
	m_btnGuildMarkBack.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnGuildMarkBack.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnGuildMarkBack.CopyUV( UBS_IDLE, UBS_ON );
	m_btnGuildMarkBack.CopyUV( UBS_IDLE, UBS_DISABLE );
	// ---------------------------------------------------------<<

	// ���� ���� --------------------------------------------->>
	// Member List
	if (m_pGuildMember == NULL)
	{
		m_pGuildMember = new CGuildMemberDesign;
		UIMGR()->LoadXML("guildmemberlist.xml", m_pGuildMember);
		addChild(m_pGuildMember);
		m_pGuildMember->SetPos(20, 78);
	}	
	// -----------------------------------------------------------<<

	// ��� ��ų ------------------------------------------------->>
	// Get Skill
	m_btnGetSkill.Create( this, _S(3841, "�����ϱ�" ), 450, 256, 100, 21 );
	m_btnGetSkill.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnGetSkill.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnGetSkill.CopyUV( UBS_IDLE, UBS_ON );
	m_btnGetSkill.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Left Skill Info scroll bar
	m_sbGuildSkillBar.Create( this, 251, 59, 9, 219 );
	m_sbGuildSkillBar.CreateButtons( TRUE, 9, 7, 0, 0, 10 );
	m_sbGuildSkillBar.SetScrollPos( 0 );
	m_sbGuildSkillBar.SetCurItemCount( 0 );
	m_sbGuildSkillBar.SetItemsPerPage( 5 );
	// Up button
	m_sbGuildSkillBar.SetUpUV( UBS_IDLE, 228, 16, 237, 22, fTexWidth, fTexHeight );
	m_sbGuildSkillBar.SetUpUV( UBS_CLICK, 228, 33, 237, 39, fTexWidth, fTexHeight );
	m_sbGuildSkillBar.CopyUpUV( UBS_IDLE, UBS_ON );
	m_sbGuildSkillBar.CopyUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_sbGuildSkillBar.SetDownUV( UBS_IDLE, 228, 25, 237, 32, fTexWidth, fTexHeight );
	m_sbGuildSkillBar.SetDownUV( UBS_CLICK, 228, 42, 237, 49, fTexWidth, fTexHeight );
	m_sbGuildSkillBar.CopyDownUV( UBS_IDLE, UBS_ON );
	m_sbGuildSkillBar.CopyDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_sbGuildSkillBar.SetBarTopUV( 217, 16, 226, 25, fTexWidth, fTexHeight );
	m_sbGuildSkillBar.SetBarMiddleUV( 217, 26, 226, 30, fTexWidth, fTexHeight );
	m_sbGuildSkillBar.SetBarBottomUV( 217, 31, 226, 41, fTexWidth, fTexHeight );
	// Wheel region
	m_sbGuildSkillBar.SetWheelRect( -203, 0, 213, 218 );
	
	// Member List	
	m_lbGuildSkillDesc.Create( this, 274, 78, 293, 75, _pUIFontTexMgr->GetLineHeight(), 5, 3, 1, FALSE );
	m_lbGuildSkillDesc.CreateScroll( TRUE, 0, 0, 9, 75, 9, 7, 0, 0, 10 );	
	// Up button
	m_lbGuildSkillDesc.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbGuildSkillDesc.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbGuildSkillDesc.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbGuildSkillDesc.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbGuildSkillDesc.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbGuildSkillDesc.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbGuildSkillDesc.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbGuildSkillDesc.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbGuildSkillDesc.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbGuildSkillDesc.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbGuildSkillDesc.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );
	m_rcGuildSkillList.SetRect( 48, 69, 241, 269 );
	// -----------------------------------------------------------<<

	// ��� �Խ��� ----------------------------------------------->>
	m_bxBox3.SetBoxUV(m_ptdBaseTexture,3,WRect(147,47,159,59));
	m_bxBox4.SetBoxUV(m_ptdBaseTexture,3,WRect(55,162,71,177));
	
	// Prev button
	m_btnPrev.Create( this, CTString( "" ), 0, 0, 10, 10 );
	m_btnPrev.SetUV( UBS_IDLE, 242, 162, 230, 172, fTexWidth, fTexHeight );
	m_btnPrev.SetUV( UBS_CLICK, 230, 147, 242, 159, fTexWidth, fTexHeight );
	m_btnPrev.CopyUV( UBS_IDLE, UBS_ON );
	m_btnPrev.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Next button
	m_btnNext.Create( this, CTString( "" ), 0, 0, 10, 10 );
	m_btnNext.SetUV( UBS_IDLE,  230, 172, 242, 162,fTexWidth, fTexHeight );
	m_btnNext.SetUV( UBS_CLICK, 242, 159, 230, 147, fTexWidth, fTexHeight );
	m_btnNext.CopyUV( UBS_IDLE, UBS_ON );
	m_btnNext.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Search button
	m_btnSearch.Create( this, _S( 386, "�˻�" ), 392, 270, 63, 21 );
	m_btnSearch.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnSearch.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnSearch.CopyUV( UBS_IDLE, UBS_ON );
	m_btnSearch.CopyUV( UBS_IDLE, UBS_DISABLE );
	// List button
	m_btnList.Create( this, _S( 313, "���" ), 23, 270, 63, 21 );
	m_btnList.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnList.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnList.CopyUV( UBS_IDLE, UBS_ON );
	m_btnList.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Write button
	m_btnWrite.Create( this, _S( 314, "����" ), 503, 270, 63, 21 );
	m_btnWrite.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnWrite.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnWrite.CopyUV( UBS_IDLE, UBS_ON );
	m_btnWrite.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Reply button
	m_btnReply.Create( this, _S( 321, "���" ), 377, 270, 63, 21 );
	m_btnReply.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnReply.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnReply.CopyUV( UBS_IDLE, UBS_ON );
	m_btnReply.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Delete button
	m_btnDelete.Create( this, _S( 338, "����" ), 446, 270, 63, 21 );
	m_btnDelete.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnDelete.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnDelete.CopyUV( UBS_IDLE, UBS_ON );
	m_btnDelete.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Modify button
	m_btnModify.Create( this, _S( 339, "����" ), 515, 270, 63, 21 );
	m_btnModify.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnModify.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnModify.CopyUV( UBS_IDLE, UBS_ON );
	m_btnModify.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Page buttons
	for( i = 0; i < 10; i++ )
	{
		m_btnPage[i].Create( this, CTString( "10" ), 0, 0, 0, 0 );
		m_btnPage[i].SetTextColor( UBS_IDLE, 0x9EB19AFF );
		m_btnPage[i].SetTextColor( UBS_ON, 0xFFD13CFF );
		m_btnPage[i].SetTextColor( UBS_CLICK, 0xFFD13CFF );
		m_btnPage[i].SetTextColor( UBS_DISABLE, 0xFFFFCAFF );
	}

	// List box of list type
	m_lbListContent.Create( this, 15, 75, 532, 174, 18, 0, 9, 5, TRUE );
	m_lbListContent.SetOverColor( 0xFFD13CFF );
	m_lbListContent.SetSelectColor( 0xFFD13CFF );
	m_lbListContent.SetColumnPosX( 0, 30, TEXT_CENTER );						// No
	m_lbListContent.SetColumnPosX( 1, 60 );									// Subject
	m_lbListContent.SetColumnPosX( 2, 345, TEXT_CENTER );						// Name
	m_lbListContent.SetColumnPosX( 3, 425, TEXT_CENTER );						// Date
	m_lbListContent.SetColumnPosX( 4, 504, TEXT_CENTER );						// Hit

	// List box of read type
	m_lbReadContent.Create( this, 24, 112, 537, 137, _pUIFontTexMgr->GetLineHeight()+5, 3, 3, 1, FALSE );
	m_lbReadContent.CreateScroll( TRUE, 0, 0, 9, 137, 9, 7, 0, 0, 10 );
	// Up button
	m_lbReadContent.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbReadContent.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbReadContent.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbReadContent.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbReadContent.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbReadContent.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbReadContent.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbReadContent.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbReadContent.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbReadContent.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbReadContent.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );

	// Search combobox
	m_cmbSearch.Create( this, 150, 271, 77, 15, 63, 1, 13, 13,
						2, _pUIFontTexMgr->GetFontHeight() + 4, 4, 4 );
	m_cmbSearch.SetBackUV( 54, 162, 72, 177, fTexWidth, fTexHeight );
	m_cmbSearch.SetDownBtnUV( 230, 162, 242, 172, fTexWidth, fTexHeight );
	m_cmbSearch.SetUpBtnUV( 242, 172, 230, 162, fTexWidth, fTexHeight );	
	m_cmbSearch.SetDropListUV( 54, 162, 70, 176, fTexWidth, fTexHeight );
	m_cmbSearch.AddString( _S( 341, "����" ) );
	m_cmbSearch.AddString( _S( 244, "�ۼ���" ) );
	m_cmbSearch.SetCurSel( 0 );

	// Search edit box
	m_ebSearch.Create( this, 233, 271, 145, 16, 32 );
	m_ebSearch.SetReadingWindowUV( 55, 162, 71, 177, fTexWidth, fTexHeight );
	m_ebSearch.SetCandidateUV( 55,162,71,177, fTexWidth, fTexHeight );

	// Subject edit box in writing
	m_ebWriteSubject.Create( this, 112, 80, 375, 16, 80 );
	m_ebWriteSubject.SetReadingWindowUV( 153, 98, 170, 114, fTexWidth, fTexHeight );
	m_ebWriteSubject.SetCandidateUV( 153, 98, 170, 114, fTexWidth, fTexHeight );

	m_mebContent.Create ( this, 111, 117, 444, 128 , 20 );
	
	// -----------------------------------------------------------<<

	// ��� ���� �Է�--------------------------------------------->>
	m_ebNoticeTitle.Create( this, 84, 75, 470, 16, MAX_NOTICE_TITLE );	// ���� 
	m_ebNoticeTitle.SetReadingWindowUV( 146, 46, 163, 62, fTexWidth, fTexHeight );
	m_ebNoticeTitle.SetCandidateUV( 146, 46, 163, 62, fTexWidth, fTexHeight );
	m_mebNoticeContent.Create ( this, 82, 115, 465, 135, 20 );	
	// ���� ��ư
	m_btnNotice.Create( this, _S(3842, "�����ϱ�" ), 80, 261, 100, 21 );
	m_btnNotice.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnNotice.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnNotice.CopyUV( UBS_IDLE, UBS_ON );
	m_btnNotice.CopyUV( UBS_IDLE, UBS_DISABLE );
	// ���� ��ư
	m_btnNoticeCorrect.Create( this, _S(3843, "�����ϱ�" ) , 340, 261 , 100, 21 );	
	m_btnNoticeCorrect.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnNoticeCorrect.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnNoticeCorrect.CopyUV( UBS_IDLE, UBS_ON );
	m_btnNoticeCorrect.CopyUV( UBS_IDLE, UBS_DISABLE );
	// �ۼ��Ϸ� ��ư
	m_btnUpdateNotice.Create( this, _S(3844, "�ۼ��Ϸ�" ) , 454, 261 , 100, 21 );	
	m_btnUpdateNotice.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnUpdateNotice.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnUpdateNotice.CopyUV( UBS_IDLE, UBS_ON );
	m_btnUpdateNotice.CopyUV( UBS_IDLE, UBS_DISABLE );
	
	// -----------------------------------------------------------<<

	// ��� ���� ------------------------------------------------->>
	// Buttons
	// Change Boss button
	m_btnChangeBossNew.Create( this, _S( 871, "����� ����" ), 20, 265, 100, 21 );
	m_btnChangeBossNew.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnChangeBossNew.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnChangeBossNew.CopyUV( UBS_IDLE, UBS_ON );
	m_btnChangeBossNew.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Accept button
	m_btnAcceptNew.Create( this, _S( 872, "������ �Ӹ�" ), 138, 265, 100, 21 );		
	m_btnAcceptNew.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnAcceptNew.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnAcceptNew.CopyUV( UBS_IDLE, UBS_ON );
	m_btnAcceptNew.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Reject button
	m_btnRejectNew.Create( this, _S( 873, "������ ����" ), 254, 265, 100, 21 );		
	m_btnRejectNew.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnRejectNew.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnRejectNew.CopyUV( UBS_IDLE, UBS_ON );
	m_btnRejectNew.CopyUV( UBS_IDLE, UBS_DISABLE );

	// MemberQuit button
	m_btnMemberFireNew.Create( this, _S( 874, "���� ����" ), 372, 265, 100, 21 );	
	m_btnMemberFireNew.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnMemberFireNew.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnMemberFireNew.CopyUV( UBS_IDLE, UBS_ON );
	m_btnMemberFireNew.CopyUV( UBS_IDLE, UBS_DISABLE );

	// MemberQuit button
	m_btnChangeSetting.Create( this, _S(3845, "���� ����" ), 488, 265, 100, 21 );	
	m_btnChangeSetting.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnChangeSetting.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnChangeSetting.CopyUV( UBS_IDLE, UBS_ON );
	m_btnChangeSetting.CopyUV( UBS_IDLE, UBS_DISABLE );
	
	m_btnDonateChange.Create( this, _S(6477, "�� ����" ), 20, 242, 100, 21 );	
	m_btnDonateChange.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnDonateChange.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnDonateChange.CopyUV( UBS_IDLE, UBS_ON );
	m_btnDonateChange.CopyUV( UBS_IDLE, UBS_DISABLE );

	m_btnChangeSettingAll.Create( this, _S(6478, "��ü �� ����" ), 488, 242, 100, 21 );	
	m_btnChangeSettingAll.SetUV( UBS_IDLE, 134, 117, 228, 138, fTexWidth, fTexHeight );
	m_btnChangeSettingAll.SetUV( UBS_CLICK, 134, 139, 228, 160, fTexWidth, fTexHeight );
	m_btnChangeSettingAll.CopyUV( UBS_IDLE, UBS_ON );
	m_btnChangeSettingAll.CopyUV( UBS_IDLE, UBS_DISABLE );
	
	if (m_pGuildChangeSetUI == NULL)
	{
		m_pGuildChangeSetUI = new CGuildChangeSetUI;
		UIMGR()->LoadXML("guild_changeSet.xml", m_pGuildChangeSetUI);
		addChild(m_pGuildChangeSetUI);
		m_pGuildChangeSetUI->initialize();
		int nPosX = m_nPosX + (NEW_GUILD_SYSTEM_WIDTH / 2) - (m_pGuildChangeSetUI->GetWidth() / 2);
		int nPosY =	m_nPosY + (NEW_GUILD_SYSTEM_HEIGHT / 2) - (m_pGuildChangeSetUI->GetHeight() / 2);
		m_pGuildChangeSetUI->SetPos(nPosX, nPosY);
	}

	if (m_pGuildDonateUI == NULL)
	{
		m_pGuildDonateUI = new CGuildDonateUI;
		UIMGR()->LoadXML("guild_donate.xml", m_pGuildDonateUI);
		addChild(m_pGuildDonateUI);
		m_pGuildDonateUI->initialize();
		int nPosX = m_nPosX + (NEW_GUILD_SYSTEM_WIDTH / 2) - (m_pGuildDonateUI->GetWidth() / 2);
		int nPosY =	m_nPosY + (NEW_GUILD_SYSTEM_HEIGHT / 2) - (m_pGuildDonateUI->GetHeight() / 2);
		m_pGuildDonateUI->SetPos(nPosX, nPosY);
	}	
	// Member List
	m_lbManageMemberList.Create( this, 20, 78, 553, 161, _pUIFontTexMgr->GetLineHeight(), 13, 3, 7, TRUE );
	m_lbManageMemberList.CreateScroll( TRUE, 0, 0, 9, 161, 9, 7, 0, 0, 10 );
	m_lbManageMemberList.SetSelBar( 553 , _pUIFontTexMgr->GetLineHeight(), 187, 46, 204, 61, fTexWidth, fTexHeight );
	m_lbManageMemberList.SetOverColor( 0xF8E1B5FF );
	m_lbManageMemberList.SetSelectColor( 0xF8E1B5FF );
	m_lbManageMemberList.SetColumnPosX( 0, 27 ,TEXT_CENTER);
	m_lbManageMemberList.SetColumnPosX( 1, 112 ,TEXT_CENTER);
	m_lbManageMemberList.SetColumnPosX( 2, 177 ,TEXT_CENTER);
	m_lbManageMemberList.SetColumnPosX( 3, 256 ,TEXT_CENTER);
	m_lbManageMemberList.SetColumnPosX( 4, 387 ,TEXT_RIGHT);
	m_lbManageMemberList.SetColumnPosX( 5, 468 ,TEXT_RIGHT);
	m_lbManageMemberList.SetColumnPosX( 6, 515 ,TEXT_RIGHT);

	m_lbManageMemberListEx.Create(this, 20, 78, 553, 161, _pUIFontTexMgr->GetLineHeight(), 13, 3, 4, TRUE);
	
	// Up button
	m_lbManageMemberList.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbManageMemberList.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbManageMemberList.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbManageMemberList.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbManageMemberList.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbManageMemberList.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbManageMemberList.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbManageMemberList.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbManageMemberList.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbManageMemberList.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbManageMemberList.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );	

	m_pIconGuildMark = new CUIGuildMarkIcon();
	m_pIconGuildMark->Create(this, 27, 250, BTN_SIZE, BTN_SIZE);
	// -----------------------------------------------------------<<
}

// ----------------------------------------------------------------------------
// WSS_NEW_GUILD_SYSTEM 070703
// Name : RenderNewGuildManagePopup()
// Desc : ��� ���� ����
// ----------------------------------------------------------------------------
void CUIGuild::RenderNewGuildManagePopup()
{
	int nX = m_nPosX;
	int nY = m_nPosY;

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Render all elements
	pDrawPort->FlushRenderingQueue();
	// Flush all render text queue
	pDrawPort->EndTextEx();

	// Set skill learn texture
	pDrawPort->InitTextureData( m_ptdBaseTexture );

	m_bxBox1.SetBoxPos(WRect(0,0,NEW_GUILD_SYSTEM_WIDTH,NEW_GUILD_SYSTEM_HEIGHT));
	m_bxBox1.Render(nX,nY);

	// Render all elements
	pDrawPort->FlushRenderingQueue();
	
	if (m_pGuildChangeSetUI != NULL)
		m_pGuildChangeSetUI->Render(pDrawPort);
}

void CUIGuild::RenderNewGuildManageSetAllPopup()
{
	int nX = m_nPosX;
	int nY = m_nPosY;

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Render all elements
	pDrawPort->FlushRenderingQueue();
	// Flush all render text queue
	pDrawPort->EndTextEx();

	// Set skill learn texture
	pDrawPort->InitTextureData( m_ptdBaseTexture );

	m_bxBox1.SetBoxPos(WRect(0,0,NEW_GUILD_SYSTEM_WIDTH,NEW_GUILD_SYSTEM_HEIGHT));
	m_bxBox1.Render(nX,nY);

	// Render all elements
	pDrawPort->FlushRenderingQueue();

	if (m_pGuildDonateUI != NULL)
		m_pGuildDonateUI->Render(pDrawPort);
}

// ----------------------------------------------------------------------------
// WSS_NEW_GUILD_SYSTEM 070703
// Name : RenderNewGuildManage()
// Desc : ��� �ý��� ���� ���� �������̽�
// ----------------------------------------------------------------------------
void CUIGuild::RenderNewGuildManage(int nX,int nY)
{
	if(_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS )
	{
		if(!m_btnChangeBossNew.IsEnabled())
		{
			m_btnChangeBossNew.SetEnable(TRUE);	// ���� ����
			m_btnAcceptNew.SetEnable(TRUE);		// �δ��� �Ӹ�
			m_btnRejectNew.SetEnable(TRUE);		// �δ��� ����
			m_btnMemberFireNew.SetEnable(TRUE);	// ��� ����
			m_btnChangeSetting.SetEnable(TRUE);	// ���� ����
			m_btnChangeSettingAll.SetEnable(TRUE);
		}
	}
	else if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_VICE_BOSS)
	{
		if (m_btnChangeBossNew.IsEnabled())
		{
			m_btnChangeBossNew.SetEnable(FALSE);		// ���� ����
			m_btnAcceptNew.SetEnable(FALSE);			// �δ��� �Ӹ�
			m_btnRejectNew.SetEnable(FALSE);			// �δ��� ����
			m_btnMemberFireNew.SetEnable(TRUE);			// ��� ����
			m_btnChangeSetting.SetEnable(FALSE);		// ���� ����
			m_btnChangeSettingAll.SetEnable(FALSE);
		}
	}
	else 
	{
		if(m_btnChangeBossNew.IsEnabled())
		{
			m_btnChangeBossNew.SetEnable(FALSE);		// ���� ����
			m_btnAcceptNew.SetEnable(FALSE);			// �δ��� �Ӹ�
			m_btnRejectNew.SetEnable(FALSE);			// �δ��� ����
			m_btnMemberFireNew.SetEnable(FALSE);		// ��� ����
			m_btnChangeSetting.SetEnable(FALSE);		// ���� ����
			m_btnChangeSettingAll.SetEnable(FALSE);
		}
	}

	// Button
	m_btnChangeBossNew.Render();		// ���� ����
	m_btnAcceptNew.Render();			// �δ��� �Ӹ�
	m_btnRejectNew.Render();			// �δ��� ����
	m_btnMemberFireNew.Render();		// ��� ����
	m_btnChangeSetting.Render();		// ���� ����
	m_btnChangeSettingAll.Render();

	// Box
	m_bxBox2.SetBoxPos(WRect(nX+20,nY+56,nX+583,nY+239));
	m_bxBox2.Render();	

	// List
	m_lbManageMemberList.Render();		// Guild Member List

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Line
	pDrawPort->AddTexture(nX+21,nY+74,nX+582,nY+75,
	m_uvLineH.U0,m_uvLineH.V0,m_uvLineH.U1,m_uvLineH.V1,0xFFFFFFFF);	

	pDrawPort->AddTexture(nX+98,nY+74,nX+99,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+186,nY+74,nX+187,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);	
	pDrawPort->AddTexture(nX+231,nY+74,nX+232,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+346,nY+74,nX+347,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);	
	pDrawPort->AddTexture(nX+425,nY+74,nX+426,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);	
	pDrawPort->AddTexture(nX+507,nY+74,nX+508,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);	

	// Text
	pDrawPort->PutTextExCX( _S(3850, "����" ), nX + 58 , nY +60);
	pDrawPort->PutTextExCX( _S(3847, "������ ����" ), nX +143, nY +60);
	pDrawPort->PutTextExCX( _S(3851, "Lv." ), nX +210, nY +60);
	pDrawPort->PutTextExCX( _S(3105, "ĳ���͸�" ), nX +286 , nY +60);
	pDrawPort->PutTextExCX( _S(3848, "����ġ ��" ), nX +385, nY +60);
	pDrawPort->PutTextExCX( _S(3849, "����ġ ��" ), nX +467, nY +60);		
	pDrawPort->PutTextExCX( _S(5559, "â�� ���" ), nX +542, nY +60);
}

// ----------------------------------------------------------------------------
// WSS_NEW_GUILD_SYSTEM 070702
// Name : RenderNewGuildNoticeInput()
// Desc : ��� �ý��� ���� ���� �������̽�
// ----------------------------------------------------------------------------
void CUIGuild::RenderNewGuildNoticeInput()
{
	// Add render regions
	int	nX, nY;
	
	nX = m_nPosX;
	nY = m_nPosY;

	if(_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS)
	{
		if(!m_btnNotice.IsEnabled())
		{
			m_btnNotice.SetEnable(TRUE);
			m_btnNoticeCorrect.SetEnable(TRUE);
			m_btnUpdateNotice.SetEnable(TRUE);		
		}		
		if (m_bEnableCorrect)
		{
			if( !m_ebNoticeTitle.IsEnabled() )
			{
				m_ebNoticeTitle.SetEnable(TRUE);
				m_mebNoticeContent.SetEnable(TRUE);
			}
		}
		else 
		{
			if( m_ebNoticeTitle.IsEnabled() )
			{
				m_ebNoticeTitle.SetEnable(FALSE);
				m_mebNoticeContent.SetEnable(FALSE);
			}
		}		
	}
	else 
	{
		if(m_btnNotice.IsEnabled())
		{
			m_btnNotice.SetEnable(FALSE);
			m_btnNoticeCorrect.SetEnable(FALSE);
			m_btnUpdateNotice.SetEnable(FALSE);
			m_ebNoticeTitle.SetEnable(FALSE);
			m_mebNoticeContent.SetEnable(FALSE);
		}
	}
	m_btnNotice.Render();						// ���� ��ư
	m_btnNoticeCorrect.Render();				// ���� ��ư
	m_btnUpdateNotice.Render();					// �ۼ��Ϸ� ��ư	

	m_bxBox2.SetBoxPos(WRect(80,72,553,100));
	m_bxBox2.Render(nX,nY);
	m_bxBox2.SetBoxPos(WRect(80,111,553,249));
	m_bxBox2.Render(nX,nY);	

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();
	
	// Render all elements
	pDrawPort->FlushRenderingQueue();
	// Flush all render text queue
	pDrawPort->EndTextEx();


	m_ebNoticeTitle.Render();					// ����	
	m_mebNoticeContent.Render();				// ����
	
	pDrawPort->PutTextExCX( _S(341, "����" ), nX + 43 , nY + 78);
	pDrawPort->PutTextExCX( _S(3852, "����" ), nX + 43 , nY + 171);	
}

// ----------------------------------------------------------------------------
// WSS_NEW_GUILD_SYSTEM 070719
// Name : RenderNewGuildBoardWrite()
// Desc : ��� �ý��� ���� ���� �������̽�
// ----------------------------------------------------------------------------
void CUIGuild::RenderNewGuildBoardWrite()
{
	// Rener Box
	m_bxBox3.SetBoxPos(WRect(25,54,98,71));
	m_bxBox3.Render(m_nPosX,m_nPosY);
	m_bxBox3.SetBoxPos(WRect(25,78,98,96));
	m_bxBox3.Render(m_nPosX,m_nPosY);
	m_bxBox3.SetBoxPos(WRect(25,115,98,245));
	m_bxBox3.Render(m_nPosX,m_nPosY);

	m_bxBox1.SetBoxPos(WRect(109,54,557,71));
	m_bxBox1.Render(m_nPosX,m_nPosY);
	m_bxBox1.SetBoxPos(WRect(109,78,557,96));
	m_bxBox1.Render(m_nPosX,m_nPosY);
	m_bxBox1.SetBoxPos(WRect(109,115,557,245));
	m_bxBox1.Render(m_nPosX,m_nPosY);

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Text in write type
	pDrawPort->PutTextEx ( _pNetwork->MyCharacterInfo.name, m_nPosX + 112,
										m_nPosY + 55, 0xFFFFCAFF ); 
	
	pDrawPort->PutTextEx( _S( 244, "�ۼ���" ), m_nPosX+43,
										m_nPosY + 57, 0xFFFFCAFF );
	pDrawPort->PutTextEx( _S( 195, "��  ��" ), m_nPosX+43,
										m_nPosY + 81, 0xFFFFCAFF );
	pDrawPort->PutTextEx( _S( 418, "��  ��" ), m_nPosX+43,
										m_nPosY + 120, 0xFFFFCAFF );

	// Render all elements
	pDrawPort->FlushRenderingQueue();

	m_mebContent.Render ();

	// Set web board texture
	pDrawPort->InitTextureData( m_ptdBaseTexture );

	// List button
	m_btnList.Render();

	// Subject edit box
	m_ebWriteSubject.Render();

	if( pWEB->m_nCurBoardType == UWT_MODIFY )
	{
		// Modify button
		m_btnModify.Render();
	}
	else
	{
		// Write button
		m_btnWrite.Render();
	}
	
	if ( m_ebWriteSubject.DoesShowReadingWindow () )
	{
		// Set web board texture
		pDrawPort->InitTextureData( m_ptdBaseTexture );

		// Reading window
		m_ebWriteSubject.RenderReadingWindow();

		// Render all elements
		pDrawPort->FlushRenderingQueue();

		// Flush all render text queue
		pDrawPort->EndTextEx();
	}
}

// ----------------------------------------------------------------------------
// WSS_NEW_GUILD_SYSTEM 070719
// Name : RenderNewGuildBoardRead()
// Desc : ��� �ý��� ���� ���� �������̽�
// ----------------------------------------------------------------------------
void CUIGuild::RenderNewGuildBoardRead()
{
	// Rener Box
	m_bxBox3.SetBoxPos(WRect(22,52,554,73));
	m_bxBox3.Render(m_nPosX,m_nPosY);

	m_bxBox1.SetBoxPos(WRect(21,90,557,247));
	m_bxBox1.Render(m_nPosX,m_nPosY);

	// Render Buttons
	m_btnList.Render();
	m_btnReply.Render();
	m_btnDelete.Render();
	m_btnModify.Render();
	
	// List box
	GetBoardReadContent();
	m_lbReadContent.Render();

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Text in read type
	pDrawPort->PutTextEx( pWEB->m_strReadNo, m_nPosX + 35,
											m_nPosY + 55, 0xFFFFCAFF );
	pDrawPort->PutTextEx( pWEB->m_strReadSubject, m_nPosX + 102,
											m_nPosY + 55, 0xFFFFCAFF );
	pDrawPort->PutTextExRX( pWEB->m_strReadName, m_nPosX + 546,
											m_nPosY + 55, 0xFFFFCAFF );

	pDrawPort->PutTextEx( pWEB->m_strReadDate, m_nPosX + 401,
											m_nPosY + 93, 0xFFFFCAFF );
	pDrawPort->PutTextExRX( pWEB->m_strReadHit, m_nPosX + 548,
											m_nPosY + 93, 0xFFFFCAFF );
}


// ----------------------------------------------------------------------------
// WSS_NEW_GUILD_SYSTEM 070719
// Name : RenderNewGuildBoardList()
// Desc : ��� �ý��� ���� ���� �������̽�
// ----------------------------------------------------------------------------
void CUIGuild::RenderNewGuildBoardList()
{
	m_bxBox3.SetBoxPos(WRect(22,52,554,73));
	m_bxBox3.Render(m_nPosX,m_nPosY);

	// Page buttons
	for( int iPage = 0; iPage < pWEB->m_nValidPageBtnCount; iPage++ )
	{		
		m_btnPage[iPage].SetText(pWEB->m_btnPage[iPage].GetText());
		m_btnPage[iPage].SetPos(pWEB->m_btnPage[iPage].GetPosX(),251);
		m_btnPage[iPage].Render();	
	}

	// Prev button
	if( pWEB->m_nCurrentFirstPage > 1 )
	{
		m_btnPrev.SetPos(pWEB->m_btnPrev.GetPosX(),253);
		m_btnPrev.Render();
	}

	// Next button
	if( pWEB->m_nCurrentLastPage < pWEB->m_nTotalPage )
	{
		m_btnNext.SetPos(pWEB->m_btnNext.GetPosX(),253);
		m_btnNext.Render();
	}

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Text in list type
	pDrawPort->PutTextEx( CTString( "No" ), m_nPosX + 38,m_nPosY + 57, 0xFFFFCAFF );
	pDrawPort->PutTextEx( _S( 341, "����" ), m_nPosX + 184,m_nPosY + 57, 0xFFFFCAFF );
	pDrawPort->PutTextEx( _S( 244, "�ۼ���" ), m_nPosX + 341,m_nPosY + 57, 0xFFFFCAFF );
	pDrawPort->PutTextEx( _S( 398, "�ۼ���" ), m_nPosX + 420,m_nPosY + 57, 0xFFFFCAFF );
	pDrawPort->PutTextEx( _S( 399, "��ȸ" ), m_nPosX + 504,m_nPosY + 57, 0xFFFFCAFF );

	// List box	
	GetBoardListContent();
	m_lbListContent.Render();

	// Search button
	m_btnSearch.Render();

	// Search combobox
	m_cmbSearch.Render();

	// Search edit box
	m_ebSearch.Render();	
	m_bxBox4.SetBoxPos(WRect(233,271,378,287));
	m_bxBox4.Render(m_nPosX,m_nPosY);

	// Write button
	m_btnWrite.Render();
}

// ----------------------------------------------------------------------------
// WSS_NEW_GUILD_SYSTEM 070719
// Name : RenderNewGuildBoard()
// Desc : ��� �ý��� ���� ���� �������̽�
// ----------------------------------------------------------------------------
void CUIGuild::RenderNewGuildBoard(int nx,int ny)
{
	if(!pWEB->DelayCommandExecute()) return;
	switch (pWEB->m_nCurBoardType)
	{
		
	case UWT_LIST:
		RenderNewGuildBoardList();
		break;
	case UWT_READ:
		RenderNewGuildBoardRead();
		break;
	case UWT_WRITE:
	case UWT_MODIFY:
	case UWT_REPLY:
		RenderNewGuildBoardWrite();
		break;
		
	}

}

// ----------------------------------------------------------------------------
// WSS_NEW_GUILD_SYSTEM 070608
// Name : RenderNewGuildMemberInfo()
// Desc : ��� �ý��� ���� ���� �������̽�
// ----------------------------------------------------------------------------
void CUIGuild::RenderNewGuildMemberInfo(int nX,int nY)
{
	// Box
	m_bxBox2.SetBoxPos(WRect(nX+20,nY+56,nX+583,nY+239));
	m_bxBox2.Render();	

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Line
	pDrawPort->AddTexture(nX+21,nY+74,nX+582,nY+75,
	m_uvLineH.U0,m_uvLineH.V0,m_uvLineH.U1,m_uvLineH.V1,0xFFFFFFFF);	

	pDrawPort->AddTexture(nX+47,nY+74,nX+48,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+146,nY+74,nX+147,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);	
	pDrawPort->AddTexture(nX+221,nY+74,nX+222,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+261,nY+74,nX+262,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);	
	pDrawPort->AddTexture(nX+343,nY+74,nX+344,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);	
	pDrawPort->AddTexture(nX+429,nY+74,nX+430,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);	
	pDrawPort->AddTexture(nX+476,nY+74,nX+477,nY+239,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);		

	m_btnDonateChange.Render();
	// Text
// 	pDrawPort->PutTextExCX( _S(3105, "ĳ���͸�" ), nX + 92 , nY +60);
// 	pDrawPort->PutTextExCX( _S(3856, "������" ), nX +184, nY +60);
// 	pDrawPort->PutTextExCX( _S(3851, "Lv." ), nX +240, nY +60);
// 	pDrawPort->PutTextExCX( _S(72, "Ŭ����" ), nX +300 , nY +60);
// 	pDrawPort->PutTextExCX( _S(3857, "������ġ" ), nX +386, nY +60);
// 	pDrawPort->PutTextExCX( _S(3858, "�⿩��" ), nX +453, nY +60);
// 	pDrawPort->PutTextExCX( _S(3859, "���� ����Ʈ" ), nX +529, nY+60);

//	pDrawPort->PutTextEx( _S(921, "���� ����" ), nX +21, nY+245);
	pDrawPort->PutTextExRX( _S(3860, "������ ����" ), nX +581, nY+245);
	CTString tStr;
	tStr.PrintF("%d/%d",m_iOnlineMembers,m_iNumOfMember);
	pDrawPort->PutTextExRX( tStr.str_String,nX+581,nY+259);
	// �Ϲ����� �ο���
	pDrawPort->PutTextExRX( _S( 5329, "�Ϲ����� �ο���" ), nX +430, nY+245);
	tStr.PrintF("%d/%d",m_iCorpsMember, nMaxCorpsMember);
	pDrawPort->PutTextExRX( tStr.str_String,nX+430,nY+259);
	// �������� �ο���
	pDrawPort->PutTextExRX( _S( 5330, "�������� �ο���" ), nX +262, nY+245);
	tStr.PrintF("%d/%d",m_iCorpsBoss, nMaxCorpsBoss);
	pDrawPort->PutTextExRX( tStr.str_String,nX+262,nY+259);
	// List
	if (m_pGuildMember != NULL)
	{
		pDrawPort->FlushRenderingQueue();
		// Flush all render text queue
		m_pGuildMember->Hide(FALSE);
		m_pGuildMember->Render(pDrawPort);		// Guild Member List
		pDrawPort->EndTextEx();

		pDrawPort->InitTextureData( m_ptdBaseTexture );
	}

	

	int i;
	for (i = 0; i < eGML_MAX; ++i)
	{
		m_pCbMemberArrange[i]->OnRender(pDrawPort);
	}
}
// ----------------------------------------------------------------------------
// WSS_NEW_GUILD_SYSTEM 070608
// Name : RenderNew()
// Desc : ��� �ý��� ���� ���� �������̽�
// ----------------------------------------------------------------------------
void CUIGuild::RenderNewGuildInfo(int nX,int nY)
{
	// Left Top
	m_bxBox2.SetBoxPos(WRect(nX+21,nY+54,nX+282,nY+218));
	m_bxBox2.Render();

	// Left Bottom
	m_bxBox2.SetBoxPos(WRect(nX+21,nY+224,nX+282,nY+286));
	m_bxBox2.Render();

	// Right Top
	m_bxBox2.SetBoxPos(WRect(nX+287,nY+54,nX+582,nY+121));
	m_bxBox2.Render();

	// Right Bottom1
	m_bxBox2.SetBoxPos(WRect(nX+287,nY+128,nX+432,nY+285));
	m_bxBox2.Render();

	// Right Bottom2
	m_bxBox2.SetBoxPos(WRect(nX+437,nY+128,nX+582,nY+285));
	m_bxBox2.Render();

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Horizon Line
	pDrawPort->AddTexture(nX+22,nY+244,nX+281,nY+245,
		m_uvLineH.U0,m_uvLineH.V0,m_uvLineH.U1,m_uvLineH.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+288,nY+75,nX+581,nY+76,
		m_uvLineH.U0,m_uvLineH.V0,m_uvLineH.U1,m_uvLineH.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+288,nY+149,nX+431,nY+150,
		m_uvLineH.U0,m_uvLineH.V0,m_uvLineH.U1,m_uvLineH.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+438,nY+149,nX+581,nY+150,
		m_uvLineH.U0,m_uvLineH.V0,m_uvLineH.U1,m_uvLineH.V1,0xFFFFFFFF);

	// Render List
	m_lbMemberAllianceList.Render();
	m_lbMemberHostilityList.Render();

	// Buttons
	m_btnEdit.Render();

	// Guild Mark
	m_bxBox1.SetBoxPos(WRect(nX+26,nY+249,nX+59,nY+282));
	m_bxBox1.Render();

//	m_btnGuildMarkBack.Render();

	if (m_guildMarkTime >= 0)
 		pDrawPort->FlushRenderingQueue();

#ifdef	GUILD_MARK
 	m_pIconGuildMark->Render(pDrawPort);
#endif	// GUILD_MARK	

	// Text 
	int nX2 = m_nPosX + 30;
	int nY2 = m_nPosY + 50;
	int nSpace = _pUIFontTexMgr->GetFontHeight() + 10;
	int nInc   = nSpace;
	CTString tStr;
	
	pDrawPort->PutTextEx( _S(3451, "����" ), nX2 , nY2 + nSpace);
	pDrawPort->PutTextEx( m_strGuildName, nX2 + 135 , nY2 + nSpace);

	pDrawPort->PutTextEx( _S(3861, "��� ����" ), nX2 , nY2 + (nSpace+=nInc));
	tStr.PrintF("%d",m_iGuildLevel);
	pDrawPort->PutTextEx( tStr, nX2 + 135 , nY2 + nSpace);

	pDrawPort->PutTextEx( _S(891, "�����" ), nX2 , nY2 + (nSpace+=nInc));
	pDrawPort->PutTextEx( m_strBossName, nX2 + 135 , nY2 + nSpace);

	pDrawPort->PutTextEx( _S(3862, "���� �ο�" ),nX2 , nY2 + (nSpace+=nInc));
	tStr.PrintF("%d/%d",m_iNumOfMember,m_iNumOfMaxMember);
	pDrawPort->PutTextEx( tStr, nX2 + 135 , nY2 + nSpace);

	pDrawPort->PutTextEx( _S(3863, "��� ��� ����" ),nX2 , nY2 + (nSpace+=nInc));
	tStr.PrintF("%d",m_iGuildAverageLevel);
	pDrawPort->PutTextEx( tStr, nX2 + 135 , nY2 + nSpace);

	pDrawPort->PutTextEx( _S(3864, "���� ����" ),nX2 , nY2 + (nSpace+=nInc));
	if(m_iGuildOwnLand>0)
		tStr.PrintF("%d",m_iGuildOwnLand);
	else 
		tStr=_S(3865, "����");
	pDrawPort->PutTextEx( tStr, nX2 + 135 , nY2 + nSpace);

	pDrawPort->PutTextEx( _S(3866, "��� ��ũ" ),nX +28 , nY + 228);	
// [sora] GUILD_MARK
#ifdef GUILD_MARK
	tStr = m_strGuildMarkTime;
#else
	tStr = _S(3867, "[���Ⱓ : 1��]" );
#endif
	pDrawPort->PutTextExCX( tStr, nX + 137 , nY + 259);
	pDrawPort->PutTextEx( _S(3977, "��� ����Ʈ(GP)" ),nX +294 , nY + 58);

	pDrawPort->PutTextEx( _S(3868, "�� ����Ʈ" ),nX +304 , nY + 81);
	tStr.PrintF("%lld",m_iGuildTotalPoint);
	UIMGR()->InsertCommaToString(tStr);
	pDrawPort->PutTextEx( tStr, nX + 500 , nY + 81);
	pDrawPort->PutTextEx( _S(3869, "�⿩ ����Ʈ" ),nX +304 , nY + 100);	
	tStr.PrintF("%lld",m_iGuildMyPoint);
	UIMGR()->InsertCommaToString(tStr);
	pDrawPort->PutTextEx( tStr, nX + 500 , nY + 100);
	
	pDrawPort->PutTextEx( _S(3870, "���� ����" ),nX +294 , nY + 132, COLOR(0x064729FF));	
	pDrawPort->PutTextEx( _S(3871, "���� ����" ),nX +446 , nY + 132, COLOR(0x531D2AFF));		
}

// ----------------------------------------------------------------------------
// WSS_NEW_GUILD_SYSTEM 070608
// Name : RenderNew()
// Desc : ��� �ý��� ���� ���� �������̽�
// ----------------------------------------------------------------------------
void CUIGuild::RenderNew()
{
	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Set skill learn texture
	pDrawPort->InitTextureData( m_ptdBaseTexture );

	// Add render regions
	int	nX, nY;
	
	nX = m_nPosX;
	nY = m_nPosY;

	// Background
	m_bxBackGroundBox.SetBoxPos(WRect(nX,nY,nX+NEW_GUILD_SYSTEM_WIDTH,nY+22));
	m_bxBackGroundBox.Render();
	m_bxBackGroundBox2.SetBoxPos(WRect(nX,nY+22,nX+NEW_GUILD_SYSTEM_WIDTH,nY+NEW_GUILD_SYSTEM_HEIGHT));
	m_bxBackGroundBox2.Render();
	// Tab
	
	for(int i=0;i<MAX_GUILDINFO_TAB;i++)
	{		
		if( m_iSelTab != i)
		{
			m_bxBox2.SetBoxPos(WRect(nX+m_rcTabNew[i].Left,nY+m_rcTabNew[i].Top,
							nX+m_rcTabNew[i].Right,nY+m_rcTabNew[i].Bottom));
			m_bxBox2.Render();
		}		
	}
	int tCabL=5 ,tCabR=5;
	if(m_iSelTab==0) tCabL = 0; else tCabL =5; 
	if(m_iSelTab==(MAX_GUILDINFO_TAB-1)) tCabR = 0; else tCabR =5;
	m_bxBox1_1.SetBoxPos(WRect(nX+m_rcTabNew[m_iSelTab].Left-tCabL,nY+m_rcTabNew[m_iSelTab].Top-3,
							nX+m_rcTabNew[m_iSelTab].Right+tCabR,nY+m_rcTabNew[m_iSelTab].Bottom));
	m_bxBox1_1.Render();

	m_bxBox1_2.SetBoxPos(WRect(nX+9,nY+47,nX+595,nY+295));
	m_bxBox1_2.Render();
	
	// Buttons
	m_btnExitNew.Render();
	m_btnCloseNew.Render();
	
	if (m_pGuildMember != NULL)
		m_pGuildMember->Hide(TRUE);
	// Render Guild Info
	switch(m_iSelTab)
	{
		case NEW_GUILD_INFO:
			RenderNewGuildInfo(nX,nY);
			break;
		case NEW_GUILD_MEMBER_INFO:
			RenderNewGuildMemberInfo(nX,nY);
			break;
		case NEW_GUILD_SKILL:
			RenderNewGuildSkillExtend(nX, nY);
			break;
#ifndef LOCAL_NEW_GUILD // �ؿ� ���� �������� ����
		case NEW_GUILD_BOARD:
			RenderNewGuildBoard(nX,nY);
		break;
#endif
		case NEW_GUILD_NOTICE:
			RenderNewGuildNoticeInput();
			break;
		case NEW_GUILD_MANAGE:
			RenderNewGuildManage(nX,nY);
			break;
	}

	// Text	
	pDrawPort->PutTextEx( m_strGuildName, m_nPosX + 19, m_nPosY + 6);
	pDrawPort->PutTextExCX( _S(3872, "��� ����" ), 
		m_nPosX + m_rcTabNew[NEW_GUILD_INFO].Left + m_rcTabNew[0].GetWidth()/2, m_nPosY + m_rcTabNew[NEW_GUILD_INFO].Top+3);
	pDrawPort->PutTextExCX( _S(3873, "���� ����" ), 
		m_nPosX + m_rcTabNew[NEW_GUILD_MEMBER_INFO].Left + m_rcTabNew[0].GetWidth()/2, m_nPosY + m_rcTabNew[NEW_GUILD_MEMBER_INFO].Top+3);
	pDrawPort->PutTextExCX( _S(3874, "��� ��ų" ), 
		m_nPosX + m_rcTabNew[NEW_GUILD_SKILL].Left + m_rcTabNew[0].GetWidth()/2, m_nPosY + m_rcTabNew[NEW_GUILD_SKILL].Top+3);
#ifndef LOCAL_NEW_GUILD // �ؿ� ���� �������� ����
	pDrawPort->PutTextExCX( _S( 3875, "��� �Խ���" ), 
		m_nPosX + m_rcTabNew[NEW_GUILD_BOARD].Left + m_rcTabNew[0].GetWidth()/2, m_nPosY + m_rcTabNew[NEW_GUILD_BOARD].Top+3);
#endif
	pDrawPort->PutTextExCX( _S(3876, "��� ��������" ), 
		m_nPosX + m_rcTabNew[NEW_GUILD_NOTICE].Left + m_rcTabNew[0].GetWidth()/2, m_nPosY + m_rcTabNew[NEW_GUILD_NOTICE].Top+3);
	pDrawPort->PutTextExCX( _S(918, "��� ����" ), 
		m_nPosX + m_rcTabNew[NEW_GUILD_MANAGE].Left + m_rcTabNew[0].GetWidth()/2, m_nPosY + m_rcTabNew[NEW_GUILD_MANAGE].Top+3);
	
	// Render all elements
	pDrawPort->FlushRenderingQueue();
	// Flush all render text queue
	pDrawPort->EndTextEx();

	if(m_bApplySettingOn)
		RenderNewGuildManagePopup();
	else if (m_bApplyDonateUI)
		RenderNewGuildManageSetAllPopup();
}



// ----------------------------------------------------------------------------
// Name : MouseMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT	CUIGuild::MouseMessageNewBoard( MSG *pMsg )
{
	WMSG_RESULT	wmsgResult;	
	
	// Mouse message
	switch( pMsg->message )
	{
		case WM_MOUSEMOVE:
			{
				// Guild Web Board
			
				// List
				if( pWEB->m_nCurBoardType == UWT_LIST )
				{
					// Search combobox
					if( m_cmbSearch.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Search button
					else if( m_btnSearch.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Write button
					else if( m_btnWrite.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// List box
					else if( m_lbListContent.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Prev button
					else if( m_btnPrev.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Next button
					else if( m_btnNext.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Page buttons
					else
					{
						for( int iPage = 0; iPage < pWEB->m_nValidPageBtnCount; iPage++ )
						{
							if( m_btnPage[iPage].MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;
						}
					}
				}
				// Read
				else if( pWEB->m_nCurBoardType == UWT_READ )
				{
					// List button
					if( m_btnList.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Reply button
					else if( m_btnReply.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Modify button
					else if( m_btnModify.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Delete button
					else if( m_btnDelete.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// List box of read type
					else if( m_lbReadContent.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
				// Write
				else if( pWEB->m_nCurBoardType == UWT_WRITE )
				{
					// List button
					if( m_btnList.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Write button
					else if( m_btnWrite.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					else if ( m_ebWriteSubject.MouseMessage ( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					else if ( m_mebContent.MouseMessage ( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
				// Reply
				else if( pWEB->m_nCurBoardType == UWT_REPLY )
				{
					// List button
					if( m_btnList.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Write button
					else if( m_btnWrite.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					else if ( m_ebWriteSubject.MouseMessage ( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					else if ( m_mebContent.MouseMessage ( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
				// Modify
				else if( pWEB->m_nCurBoardType == UWT_MODIFY )
				{
					// List button
					if( m_btnList.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Modify button
					else if( m_btnModify.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					else if ( m_ebWriteSubject.MouseMessage ( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					else if ( m_mebContent.MouseMessage ( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
		
			}
			break;
		case WM_LBUTTONDOWN:
			{
				// List
				if( pWEB->m_nCurBoardType == UWT_LIST )
				{
					// Search combobox
					m_cmbSearch.MouseMessage( pMsg );
					// Search edit box
					m_ebSearch.MouseMessage( pMsg );
					// Search button
					m_btnSearch.MouseMessage( pMsg );
					// Write button
					m_btnWrite.MouseMessage( pMsg );
					// Prev button
					m_btnPrev.MouseMessage( pMsg );
					// Next button
					m_btnNext.MouseMessage( pMsg );
					// List box
					if( ( wmsgResult = m_lbListContent.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ���� ���� ��û..
							pWEB->m_nWantWrite = m_lbListContent.GetCurSel();
							pWEB->DelayCommandPrepare(new CCommandView);							
						}
					}
					// Page buttons
					else
					{
						for( int iPage = 0; iPage < pWEB->m_nValidPageBtnCount; iPage++ )
						{
							if( m_btnPage[iPage].MouseMessage( pMsg ) != WMSG_FAIL )
								break;
						}
					}
				}
				// Read
				else if( pWEB->m_nCurBoardType == UWT_READ )
				{
					// List button
					m_btnList.MouseMessage( pMsg );
					// Reply button
					m_btnReply.MouseMessage( pMsg );
					// Modify button
					m_btnModify.MouseMessage( pMsg );
					// Delete button
					m_btnDelete.MouseMessage( pMsg );
					// List box of read type
					m_lbReadContent.MouseMessage( pMsg );
				}
				// Write
				else if( pWEB->m_nCurBoardType == UWT_WRITE )
				{
					// List button
					m_btnList.MouseMessage( pMsg );
					// Write button
					m_btnWrite.MouseMessage( pMsg );
					if ( m_ebWriteSubject.MouseMessage ( pMsg ) != WMSG_FAIL )
						m_mebContent.SetFocus ( FALSE );
					else if ( m_mebContent.MouseMessage ( pMsg ) != WMSG_FAIL )
						m_ebWriteSubject.SetFocus( FALSE );
				}
				// Reply
				else if( pWEB->m_nCurBoardType == UWT_REPLY )
				{
					// List button
					m_btnList.MouseMessage( pMsg );
					// Write button
					m_btnWrite.MouseMessage( pMsg );
					if ( m_ebWriteSubject.MouseMessage ( pMsg ) != WMSG_FAIL )
						m_mebContent.SetFocus ( FALSE );
					else if ( m_mebContent.MouseMessage ( pMsg ) != WMSG_FAIL )
						m_ebWriteSubject.SetFocus( FALSE );
				}
				// Modify
				else if( pWEB->m_nCurBoardType == UWT_MODIFY )
				{
					// List button
					m_btnList.MouseMessage( pMsg );
					// Modify button
					m_btnModify.MouseMessage( pMsg );
					if ( m_ebWriteSubject.MouseMessage ( pMsg ) != WMSG_FAIL )
						m_mebContent.SetFocus ( FALSE );
					if ( m_mebContent.MouseMessage ( pMsg ) != WMSG_FAIL )
						m_ebWriteSubject.SetFocus( FALSE );
				}
			}		
			break;
		case WM_LBUTTONUP:
			{
				// List
				if( pWEB->m_nCurBoardType == UWT_LIST )
				{
					// List box
					if( m_lbListContent.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					// Search button
					else if( ( wmsgResult = m_btnSearch.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							if( m_ebSearch.GetString() )
							{
								pWEB->m_cmbSearch.SetCurSel(m_cmbSearch.GetCurSel());
								pWEB->m_ebSearch.SetString(m_ebSearch.GetString());
								pWEB->m_nWantPage = 1;
								pWEB->DelayCommandPrepare(new CCommandList);								
							}
						}
						return WMSG_SUCCESS;
					}
					// Write button
					else if( ( wmsgResult = m_btnWrite.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// user name input ...
							// �۾��� ��û
							pWEB->m_nCurBoardType = UWT_WRITE;
							pWEB->m_ebWriteSubject.ResetString();
							//!!TODO:���뵵 ����.
							m_ebWriteSubject.SetFocus ( TRUE );
							m_mebContent.ResetString ();
							m_mebContent.SetFocus ( FALSE );

						}
						return WMSG_SUCCESS;
					}
					// Prev button
					else if( ( wmsgResult = m_btnPrev.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ������ �缳��
							pWEB->m_nWantPage = pWEB->m_nCurrentPage - 10;
							if(pWEB->m_nWantPage < 1) pWEB->m_nWantPage = 1;
							pWEB->DelayCommandPrepare(new CCommandList);
						}
						return WMSG_SUCCESS;
					}
					// Next button
					else if( ( wmsgResult = m_btnNext.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ������ �缳��
							pWEB->m_nWantPage = pWEB->m_nCurrentPage + 10;
							if(pWEB->m_nWantPage > pWEB->m_nTotalPage) pWEB->m_nWantPage = pWEB->m_nTotalPage;
							pWEB->DelayCommandPrepare(new CCommandList);
						}
						return WMSG_SUCCESS;
					}
					// Page buttons
					else
					{
						for( int iPage = 0; iPage < pWEB->m_nValidPageBtnCount; iPage++ )
						{
							if( ( wmsgResult = m_btnPage[iPage].MouseMessage( pMsg ) ) != WMSG_FAIL )
							{
								if( wmsgResult == WMSG_COMMAND )
								{
									// ������ ���� ó��
									pWEB->m_nWantPage = pWEB->m_nCurrentFirstPage + iPage;
									pWEB->DelayCommandPrepare(new CCommandList);									
								}
								return WMSG_SUCCESS;
							}
						}
					}
				}
				// Read
				else if( pWEB->m_nCurBoardType == UWT_READ )
				{
					// List button
					if( ( wmsgResult = m_btnList.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ��� ��û							
							pWEB->DelayCommandPrepare(new CCommandList);							
							pWEB->m_nCurBoardType = UWT_LIST;
							pWEB->m_nWantPage = pWEB->m_nCurrentPage;							
						}
						return WMSG_SUCCESS;
					}
					// Reply button
					else if( ( wmsgResult = m_btnReply.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ��� ��������
							pWEB->m_nCurBoardType = UWT_REPLY;
							CTString strTemp;
							strTemp.PrintF("Re: %s", pWEB->m_strReadSubject);
							m_ebWriteSubject.ResetString();
							m_ebWriteSubject.InsertChars(0, strTemp.str_String);
							//��Ƽ�����Ϳ� ���� ����. ������ �Ʒ��� ���� ������.
							//�������
							//----<�Ǵ���� �ۼ���>�� ���� ���Դϴ� -----
							//��� �� �տ� '>' ����.
								
							CTString strContent;
							
							for ( int i = 0; i < m_lbReadContent.GetCurItemCount(0); i++ )
							{
								strContent += m_lbReadContent.GetString ( 0, i );
								strContent += "\r\n";
							}

							m_ebWriteSubject.SetFocus ( FALSE );
							m_mebContent.SetFocus ( TRUE );
							m_mebContent.SetString ( strContent.str_String, pWEB->m_strReadName.str_String, ">" );
						}
						return WMSG_SUCCESS;
					}
					// Modify button
					else if( ( wmsgResult = m_btnModify.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ���� ��������
							pWEB->m_nCurBoardType = UWT_MODIFY;
							m_ebWriteSubject.ResetString();
							m_ebWriteSubject.InsertChars(0, pWEB->m_strReadSubject.str_String);

							//��Ƽ�����Ϳ� ���� ����.
							m_mebContent.ResetString();
							
							CTString strContent;
							for ( int i = 0; i < m_lbReadContent.GetCurItemCount(0); i++ )
							{
								strContent += m_lbReadContent.GetString ( 0, i );
								strContent += "\r\n";
							}
							m_ebWriteSubject.SetFocus ( FALSE );	
							m_mebContent.SetFocus ( TRUE );	
							m_mebContent.SetString ( strContent.str_String );

						}
						return WMSG_SUCCESS;
					}
					// Delete button
					else if( ( wmsgResult = m_btnDelete.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ���� ��û
							//TODO : ���ǻ� �ѹ� �����.
							pWEB->m_nWantModifyMode = UWM_DELETE;
							pWEB->DelayCommandPrepare(new CCommandModify);
						}
						return WMSG_SUCCESS;
					}
					// List box of read type
					else if( m_lbReadContent.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
				// Write
				else if( pWEB->m_nCurBoardType == UWT_WRITE )
				{
					SetFocus ( TRUE );

					// List button
					if( ( wmsgResult = m_btnList.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ��� ��û							
							pWEB->m_nWantPage = pWEB->m_nCurrentPage;
							pWEB->DelayCommandPrepare(new CCommandList);
						}
						return WMSG_SUCCESS;
					}
					// Write button
					else if( ( wmsgResult = m_btnWrite.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ���� ��û
							pWEB->m_nWantModifyMode = UWM_WRITE;
							pWEB->m_ebWriteSubject.SetString( m_ebWriteSubject.GetString());
							pWEB->m_mebContent.SetString(m_mebContent.GetString().str_String);
							pWEB->DelayCommandPrepare(new CCommandModify);
						}
						return WMSG_SUCCESS;
					}
				
				}
				// Reply
				else if( pWEB->m_nCurBoardType == UWT_REPLY )
				{
					// List button
					if( ( wmsgResult = m_btnList.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ��� ��û
							pWEB->m_nCurBoardType = UWT_LIST;
							pWEB->m_nWantPage = pWEB->m_nCurrentPage;
							pWEB->DelayCommandPrepare(new CCommandList);
						}
						return WMSG_SUCCESS;
					}
					// Write button
					else if( ( wmsgResult = m_btnWrite.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ���� ��û
							pWEB->m_nWantModifyMode = UWM_REPLY;
							pWEB->m_ebWriteSubject.SetString( m_ebWriteSubject.GetString());
							pWEB->m_mebContent.SetString(m_mebContent.GetString().str_String);
							pWEB->DelayCommandPrepare(new CCommandModify);
						}
						return WMSG_SUCCESS;
					}
					
				}
				// Modify
				else if( pWEB->m_nCurBoardType == UWT_MODIFY )
				{
					// List button
					if( ( wmsgResult = m_btnList.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ��� ��û
							pWEB->m_nCurBoardType = UWT_LIST;
							pWEB->m_nWantPage = pWEB->m_nCurrentPage;
							pWEB->DelayCommandPrepare(new CCommandList);
						}
						return WMSG_SUCCESS;
					}
					// Modify button
					else if( ( wmsgResult = m_btnModify.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// ���� ��û
							pWEB->m_ebWriteSubject.SetString( m_ebWriteSubject.GetString() );	
							pWEB->m_mebContent.SetString( m_mebContent.GetString().str_String );	
							pWEB->m_nWantModifyMode = UWM_MODIFY;
							pWEB->DelayCommandPrepare(new CCommandModify);
						}
						return WMSG_SUCCESS;
					}
				
				}
			}		
			break;
		case WM_MOUSEWHEEL:
			{
				// Read
				if( pWEB->m_nCurBoardType == UWT_READ )
				{
					// List box of read type
					if( m_lbReadContent.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
				else if( pWEB->m_nCurBoardType == UWT_WRITE )
				{
					if( m_mebContent.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
				else if( pWEB->m_nCurBoardType == UWT_REPLY )
				{
					if( m_mebContent.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}
				else if( pWEB->m_nCurBoardType == UWT_MODIFY )
				{
					if( m_mebContent.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}

			}
			break;

		case WM_LBUTTONDBLCLK:
			{			
				// Read
				if( pWEB->m_nCurBoardType == UWT_READ )
				{
					// List box of read type
					if( m_lbReadContent.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
				}					
			}
			break;
	}
	
	return WMSG_FAIL;
}

// ----------------------------------------------------------------------------
// Name : MouseMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT	CUIGuild::MouseMessageNew( MSG *pMsg )
{
	WMSG_RESULT	wmsgResult;

	// Title bar
	static BOOL	bTitleBarClick = FALSE;
	// Extended button clicked
	static BOOL	bLButtonDownInBtn = FALSE;
	// Mouse point
	static int	nOldX, nOldY;
	int	nX = LOWORD( pMsg->lParam );
	int	nY = HIWORD( pMsg->lParam );
	int i = 0;

	// Mouse message
	switch( pMsg->message )
	{
	case WM_MOUSEMOVE:
		{
			int	ndX = nX - nOldX;
			int	ndY = nY - nOldY;

			// Move Window
			if( bTitleBarClick && ( pMsg->wParam & MK_LBUTTON ) )
			{
				nOldX = nX;	nOldY = nY;
				
				Move( ndX, ndY );
				
				return WMSG_SUCCESS;
			}

			if( IsInsideRect( nX, nY ,m_rcWindowNew) )
			{
				// Close button
				m_btnCloseNew.MouseMessage( pMsg );
				// �ݱ� ��ư
				m_btnExitNew.MouseMessage(pMsg);

				CUIManager* pUIManager = CUIManager::getSingleton();

				pUIManager->SetMouseCursorInsideUIs();
				
				CUIIcon* pBtnSkill = NULL;
				int nScrollBarPos, nGuildSkillCount, i;
				m_strSkillTabPopupInfo.Clear();
				switch(m_iSelTab)
				{
					case NEW_GUILD_INFO:
						{
							// List
							m_btnEdit.MouseMessage( pMsg );
							m_lbMemberAllianceList.MouseMessage( pMsg );
							m_lbMemberHostilityList.MouseMessage( pMsg );	
						}						
						break;
					case NEW_GUILD_MEMBER_INFO:
						{
							if (m_bApplyDonateUI == TRUE)
							{
								if (m_pGuildDonateUI)
									m_pGuildDonateUI->MouseMessage( pMsg );
							}							
							else
							{
								if (m_pGuildMember != NULL )
									m_pGuildMember->MouseMessage(pMsg);

								m_btnDonateChange.MouseMessage(pMsg);
							}
						}
						break;
					case NEW_GUILD_SKILL:
						{
							m_btnGetSkill.MouseMessage(pMsg);

							if ( m_sbGuildSkillBar.MouseMessage( pMsg ) != WMSG_FAIL )
							{
								SetSkillBtnInfo();
							}
							m_lbGuildSkillDesc.MouseMessage( pMsg );
							nScrollBarPos	 = m_sbGuildSkillBar.GetScrollPos();
							nGuildSkillCount = GetGuildSkillCount();
							for ( i=0; i<5; ++i )
							{
								if ( nScrollBarPos+i < nGuildSkillCount )
								{
									pBtnSkill = GetSkillButton(nScrollBarPos+i);

									pBtnSkill->MouseMessage( pMsg );
								}
							}
							if (pUIManager->GetDragIcon() == NULL && bLButtonDownInBtn && 
								(pMsg->wParam& MK_LBUTTON) && (ndX != 0 || ndY != 0))
							{
								CSkill* pSkill = GetGuildSkill(m_iGuildSkillPos);
								if ( m_nSelSkillTab == GUILD_SKILL_ACTIVE && pSkill->GetCurLevel() > 0)
								{
									if (pSkill->GetTargetType() == CSkill::STT_GUILD_MEMBER_SELF ||
										_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS)
									{
										pBtnSkill = GetSkillButton(m_iGuildSkillPos);
										pUIManager->SetHoldBtn(pBtnSkill);
										bLButtonDownInBtn = FALSE;
									}
								}
							}
							if (m_lbUseInfo.MouseMessage( pMsg ) != WMSG_FAIL ||
								m_lbLearnInfo.MouseMessage( pMsg ) != WMSG_FAIL ||
								m_btnUseSkill.MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;

							for ( i=0; i<2; ++i )
							{
								if ( IsInsideRect( nX, nY, m_rcSkillTab[i] ) )
								{
									SetSkillPopupInfo(i);
								}
							}
							break;
						}						
#ifndef LOCAL_NEW_GUILD // �ؿ� ���� �������� ����
					case NEW_GUILD_BOARD:
						{
							MouseMessageNewBoard(pMsg);
						}						
						break;
#endif
					case NEW_GUILD_NOTICE:
						{
							m_btnNotice.MouseMessage(pMsg);
							m_btnNoticeCorrect.MouseMessage(pMsg);
							m_btnUpdateNotice.MouseMessage(pMsg);
							m_ebNoticeTitle.MouseMessage( pMsg );
							m_mebNoticeContent.MouseMessage( pMsg );
						}
						break;
					case NEW_GUILD_MANAGE:
						{
							m_lbManageMemberList.MouseMessage( pMsg );

							if (m_pGuildChangeSetUI)
								m_pGuildChangeSetUI->MouseMessage( pMsg );
							if (m_pGuildDonateUI)
								m_pGuildDonateUI->MouseMessage( pMsg );
							m_btnChangeBossNew.MouseMessage( pMsg );							
							m_btnAcceptNew.MouseMessage( pMsg );							
							m_btnRejectNew.MouseMessage( pMsg );							
							m_btnMemberFireNew.MouseMessage( pMsg );							
							m_btnChangeSetting.MouseMessage( pMsg );
							m_btnChangeSettingAll.MouseMessage( pMsg );
						}
						break; 						
				}	
				return WMSG_SUCCESS;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			if( IsInsideRect( nX, nY ,m_rcWindowNew) )
			{
				if (m_bApplyDonateUI == FALSE)
				{
					for (i = 0; i < eGML_MAX; ++i)
					{
						if (m_pCbMemberArrange[i]->OnLButtonDown(nX, nY) != WMSG_FAIL)
							return WMSG_SUCCESS;
					}
				}				

				CUIManager* pUIManager = CUIManager::getSingleton();
				nOldX = nX;
				nOldY = nY;

				if (pUIManager->GetGuild()->IsEnabled() && !pUIManager->GetGuild()->IsVisible())
				{
					pUIManager->RearrangeOrder( UI_GUILD, TRUE );
				}
			
				// Close button
				m_btnCloseNew.MouseMessage( pMsg );
				// �ݱ� ��ư
				m_btnExitNew.MouseMessage(pMsg);
				// Title bar
				if( IsInsideRect( nX, nY, m_rcTitleNew ) )
				{
					bTitleBarClick = TRUE;					
				}
				
				switch(m_iSelTab)
				{
					case NEW_GUILD_INFO:
						{
							// Edit button
							m_btnEdit.MouseMessage( pMsg );						
							// List
							m_lbMemberAllianceList.MouseMessage( pMsg );
							m_lbMemberHostilityList.MouseMessage( pMsg );	
						}							
						break;
					case NEW_GUILD_MEMBER_INFO:
						{
							if(m_bApplyDonateUI)
							{
								if (m_pGuildDonateUI != NULL)
									wmsgResult = m_pGuildDonateUI->MouseMessage(pMsg);

								pUIManager->RearrangeOrder( UI_GUILD, TRUE );
								return wmsgResult;
							}
							else
							{
								if (m_pGuildMember != NULL)
									m_pGuildMember->MouseMessage(pMsg);
								m_btnDonateChange.MouseMessage(pMsg);
							}
						}
						break;
					case NEW_GUILD_SKILL:
						{
							m_btnGetSkill.MouseMessage( pMsg );
							m_lbGuildSkillDesc.MouseMessage( pMsg );
							if(m_sbGuildSkillBar.MouseMessage( pMsg ) != WMSG_FAIL )
							{	
								SetSkillBtnInfo();	
							}
							else if ( IsInsideRect( nX, nY, m_rcGuildSkillList) )
							{
								int nScrollBarPos	 = m_sbGuildSkillBar.GetScrollPos();
								int nGuildSkillCount = GetGuildSkillCount();
								CUIIcon* pBtnSkill = NULL;
								for ( int i=0; i<5; ++i )
								{
									if ( nScrollBarPos+i < nGuildSkillCount )
									{
										pBtnSkill = GetSkillButton(nScrollBarPos+i);
										if (pBtnSkill->MouseMessage( pMsg ) != WMSG_FAIL )
										{
											m_iGuildSkillPos = nScrollBarPos + i;
											bLButtonDownInBtn = TRUE;
											break;
										}
									}
								}
							}
							else if ( IsInsideRect( nX, nY, m_rcSkillTab[GUILD_SKILL_PASSIVE]) )
							{
								m_nSelSkillTab	= GUILD_SKILL_PASSIVE;
								m_iGuildSkillPos = 0;
								m_bIsSelList = FALSE;
								m_sbGuildSkillBar.SetScrollPos( 0 );
								m_lbGuildSkillDesc.ResetAllStrings();
								m_lbUseInfo.ResetAllStrings();
								m_lbLearnInfo.ResetAllStrings();
								m_sbGuildSkillBar.SetCurItemCount(m_vecGuildPassiveSkill.size());
								SetSkillBtnInfo();
							}
							else if ( IsInsideRect( nX, nY, m_rcSkillTab[GUILD_SKILL_ACTIVE]) )
							{
								m_nSelSkillTab	= GUILD_SKILL_ACTIVE;
								m_iGuildSkillPos = 0;
								m_bIsSelList = FALSE;
								m_sbGuildSkillBar.SetScrollPos( 0 );
								m_lbGuildSkillDesc.ResetAllStrings();
								m_lbUseInfo.ResetAllStrings();
								m_lbLearnInfo.ResetAllStrings();
								m_sbGuildSkillBar.SetCurItemCount(m_vecGuildActiveSkill.size());
								SetSkillBtnInfo();
							}
							if (m_lbUseInfo.MouseMessage( pMsg ) != WMSG_FAIL ||
								m_lbLearnInfo.MouseMessage( pMsg ) != WMSG_FAIL ||
								m_btnUseSkill.MouseMessage( pMsg ) != WMSG_FAIL )
								return WMSG_SUCCESS;
						}
						break;
#ifndef LOCAL_NEW_GUILD // �ؿ� ���� �������� ����
					case NEW_GUILD_BOARD:
						{
							MouseMessageNewBoard(pMsg);
						}						
						break;
#endif
					case NEW_GUILD_NOTICE:
						{
							if( m_bEnableCorrect )
							{						
								if( m_ebNoticeTitle.MouseMessage( pMsg ) != WMSG_FAIL )
								{					
									m_ebNoticeTitle.SetFocus(TRUE);
									m_mebNoticeContent.SetFocus(FALSE);
								}
								else if( m_mebNoticeContent.MouseMessage( pMsg ) != WMSG_FAIL )
								{					
									m_ebNoticeTitle.SetFocus(FALSE);
									m_mebNoticeContent.SetFocus(TRUE);
								}
								else 
								{
									m_ebNoticeTitle.SetFocus(FALSE);
									m_mebNoticeContent.SetFocus(FALSE);
								}
							}
							m_btnNotice.MouseMessage( pMsg );		
							m_btnNoticeCorrect.MouseMessage( pMsg );	
							m_btnUpdateNotice.MouseMessage( pMsg );	
						}
						break;

					case NEW_GUILD_MANAGE:
						{
							if(m_bApplySettingOn)
							{
								if (m_pGuildChangeSetUI != NULL)
									wmsgResult = m_pGuildChangeSetUI->MouseMessage(pMsg);

								pUIManager->RearrangeOrder( UI_GUILD, TRUE );
								return wmsgResult;
							}
							if(m_bApplyDonateUI)
							{
								if (m_pGuildDonateUI != NULL)
									wmsgResult = m_pGuildDonateUI->MouseMessage(pMsg);

								pUIManager->RearrangeOrder( UI_GUILD, TRUE );
								return wmsgResult;
							}
							else 
							{
								m_btnChangeBossNew.MouseMessage( pMsg );							
								m_btnAcceptNew.MouseMessage( pMsg );							
								m_btnRejectNew.MouseMessage( pMsg );							
								m_btnMemberFireNew.MouseMessage( pMsg );							
								m_btnChangeSetting.MouseMessage( pMsg );
								m_btnChangeSettingAll.MouseMessage( pMsg );
								m_lbManageMemberList.MouseMessage( pMsg );
							}		
						}				
						break;
				}				
				pUIManager->RearrangeOrder( UI_GUILD, TRUE );
				return WMSG_SUCCESS;
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();
			bTitleBarClick = FALSE;
			bLButtonDownInBtn = FALSE;
			int nGuildSkillCount = GetGuildSkillCount();

			if (pUIManager->GetDragIcon() == NULL)
			{
				// tab
				if(!m_bApplySettingOn && !m_bApplyDonateUI)
				{
					for(int i=0; i<MAX_GUILDINFO_TAB;i++)
					{
						if( IsInsideRect( nX, nY, m_rcTabNew[i] ) )
						{
							if( m_iSelTab != i)
							{
								int tOldTab = m_iSelTab;
								m_iSelTab = i;							
								
								switch(m_iSelTab)
								{
#ifndef LOCAL_NEW_GUILD // �ؿ� ���� �������� ����
								case NEW_GUILD_BOARD:
									{
										// TODO :: �ӽ÷� �Խ��� ����... ���� ���� �۾��Ǹ� �߰�
										//	m_iSelTab = tOldTab;
										//	pUIManager->GetChattingUI()->AddSysMessage( _s( "���� ������ �������� �ʽ��ϴ�." ) );
										//	return WMSG_SUCCESS;
										
										pWEB->m_nWantPage = 1;
										pWEB->DelayCommandPrepare(new CCommandList);
										return WMSG_SUCCESS;
									}
									break;
#endif
								case NEW_GUILD_NOTICE:
									{
										m_iSelTab = tOldTab;
										m_bEnableCorrect		= FALSE;			// �������� ��������
										SendRequestGuildTab(NEW_GUILD_NOTICE);
										return WMSG_SUCCESS;
									}
									break;							
								case NEW_GUILD_MANAGE:
									{
										if( _pNetwork->MyCharacterInfo.lGuildPosition != GUILD_MEMBER_BOSS &&
											_pNetwork->MyCharacterInfo.lGuildPosition != GUILD_MEMBER_VICE_BOSS)
										{
											m_iSelTab = tOldTab;
											return WMSG_SUCCESS;
										}
									}
									break;
								case NEW_GUILD_SKILL:
									{
										SetSkillBtnInfo();
									}
									break;
								}
								
								// ��� ���� ��û
								SendRequestGuildTab(m_iSelTab);
								break;
							}						
						}
					}		
				}
				
				// Close button
				if( (wmsgResult = m_btnCloseNew.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if(wmsgResult == WMSG_COMMAND)
					{
						ResetGuild();
						InitNewGuildSystem();
					}
					return WMSG_SUCCESS;
				}
				if( (wmsgResult = m_btnExitNew.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if(wmsgResult == WMSG_COMMAND)
					{
						ResetGuild();
						InitNewGuildSystem();
					}
					return WMSG_SUCCESS;
				}			
				
				switch(m_iSelTab)
				{
				case NEW_GUILD_INFO: 
					{
						// Edit button
						if( (wmsgResult = m_btnEdit.MouseMessage( pMsg )) != WMSG_FAIL)
						{						
							if(wmsgResult == WMSG_COMMAND)
							{
								// TODO : ��帶ũ ����Ʈ ��ȹ�Ϸ��� �۾�
// [sora] GUILD_MARK
#ifdef GUILD_MARK
								_pNetwork->SendGuildMarkWndOpenReq();
#endif
							}
							return WMSG_SUCCESS;
						}
						// List
						if( (wmsgResult = m_lbMemberAllianceList.MouseMessage( pMsg )) != WMSG_FAIL )
						{
							return WMSG_SUCCESS;
						}					
					}
					break;
				case NEW_GUILD_MEMBER_INFO:
					{
						if (m_bApplyDonateUI)
						{
							if (m_pGuildDonateUI != NULL)
							{
								if ( (wmsgResult = m_pGuildDonateUI->MouseMessage( pMsg ) ) != WMSG_FAIL )
									return WMSG_SUCCESS;
							}
						}

						if( (wmsgResult = m_btnDonateChange.MouseMessage( pMsg ) ) != WMSG_FAIL )
						{
							if (m_bApplyDonateUI == FALSE)
								SendGuildDonateInfo();
							return WMSG_SUCCESS;						
						}
					}			
					break;
				case NEW_GUILD_SKILL:
					{
						if(IsInsideRect(nX,nY,m_rcGuildSkillList) )
						{
							m_lbGuildSkillDesc.ResetAllStrings();
							m_lbUseInfo.ResetAllStrings();
							m_lbLearnInfo.ResetAllStrings();
							INDEX iMaxChar = 35;

							m_iGuildSkillPos = (nY-(m_nPosY+m_rcGuildSkillList.Top))/40 + m_sbGuildSkillBar.GetScrollPos();
							
							if (nGuildSkillCount>m_iGuildSkillPos)
							{
								m_bIsSelList = TRUE;
								SetGuildSkillInfo();
								iMaxChar = 45;
							}
							else 
							{
								m_bIsSelList = FALSE;
								m_iGuildSkillPos = 0;
							}

							CSkill* pSkill = GetGuildSkill(m_iGuildSkillPos);
							if( pSkill != NULL )
							{
								pUIManager->AddStringToList(
									&m_lbGuildSkillDesc,
									CTString(pSkill->GetDescription()),
									iMaxChar);
							}
							CUIIcon* pBtnSkill = NULL;
							int nScrollBarPos = m_sbGuildSkillBar.GetScrollPos();
							for (int i=0; i<5; ++i)
							{
								if ( m_nSelSkillTab == GUILD_SKILL_ACTIVE )
								{
									nGuildSkillCount = m_vecGuildActiveSkill.size();
								}
								if ( nScrollBarPos+i < nGuildSkillCount )
								{
									pBtnSkill = GetSkillButton(nScrollBarPos+i);
									if ( pBtnSkill->MouseMessage( pMsg ) == WMSG_SUCCESS )
										break;
								}
							}
						}
						else if ( (wmsgResult=m_btnGetSkill.MouseMessage( pMsg )) != WMSG_FAIL)
						{
							if(wmsgResult == WMSG_COMMAND)
							{
								// TODO : ��� ���� ��û
								CSkill* pSkill = GetGuildSkill(m_iGuildSkillPos);
								if( pSkill != NULL )
									SendLearnGuildSkill(pSkill->GetIndex());
							}
							return WMSG_SUCCESS;
						}
						else if( (wmsgResult=m_sbGuildSkillBar.MouseMessage( pMsg )) != WMSG_FAIL)
						{
							SetGuildSkillInfo();
							return WMSG_SUCCESS;
						}
						else if( (wmsgResult=m_lbGuildSkillDesc.MouseMessage( pMsg )) != WMSG_FAIL)
						{
							return WMSG_SUCCESS;
						}					
						else if (m_lbUseInfo.MouseMessage( pMsg ) != WMSG_FAIL )
						{
							return WMSG_SUCCESS;
						}
						else if (m_lbLearnInfo.MouseMessage( pMsg ) != WMSG_FAIL )
						{
							return WMSG_SUCCESS;
						}
						else if ( m_btnUseSkill.MouseMessage( pMsg ) != WMSG_FAIL )
						{
							if ( m_nSelSkillTab == GUILD_SKILL_ACTIVE && m_iGuildSkillPos >= 0 && m_bIsSelList)
							{	// ��Ƽ�� ��ų�� ���, ������ ��ų�� �ִ� ���,
								CSkill* pSkill  = GetGuildSkill(m_iGuildSkillPos);
								int nSkillIndex = pSkill->GetIndex();
								if ( CheckUseGuildSkill(nSkillIndex) )
								{
									pUIManager->GetCharacterInfo()->UseSkill(nSkillIndex);
								}
							}
						}
					}
					break;
#ifndef LOCAL_NEW_GUILD // �ؿ� ���� �������� ����
				case NEW_GUILD_BOARD:
					MouseMessageNewBoard(pMsg);
					break;
#endif
				case NEW_GUILD_NOTICE:
					{
						if( m_bEnableCorrect )
						{
							m_ebNoticeTitle.MouseMessage( pMsg );		
							m_mebNoticeContent.MouseMessage( pMsg );
						}

						if ( m_btnNotice.MouseMessage( pMsg ) == WMSG_COMMAND)
						{
							SendRequestGuildNotice();
							return WMSG_SUCCESS;
						}
						else if ( m_btnNoticeCorrect.MouseMessage( pMsg ) == WMSG_COMMAND)
						{
							// TODO :: ����â Ȱ��ȭ
							m_bEnableCorrect = TRUE;
							m_ebNoticeTitle.SetFocus(FALSE);
							m_mebNoticeContent.SetFocus(TRUE);
							return WMSG_SUCCESS;
						}
						else if ( m_btnUpdateNotice.MouseMessage( pMsg ) == WMSG_COMMAND)
						{
							SendUpdateGuildNotice(m_ebNoticeTitle.GetString(),m_mebNoticeContent.GetString());
							return WMSG_SUCCESS;
						}
					}
					break;
				case NEW_GUILD_MANAGE:
					{
						if(m_bApplySettingOn)
						{
							if (m_pGuildChangeSetUI != NULL)
							{
								if ( (wmsgResult = m_pGuildChangeSetUI->MouseMessage( pMsg ) ) != WMSG_FAIL )
									return WMSG_SUCCESS;
							}							
						}
						else if (m_bApplyDonateUI)
						{
							if (m_pGuildDonateUI != NULL)
							{
								if ( (wmsgResult = m_pGuildDonateUI->MouseMessage( pMsg ) ) != WMSG_FAIL )
									return WMSG_SUCCESS;
							}
						}
						else
						{
							// Change Boss(���� ����)
							if( (wmsgResult = m_btnChangeBossNew.MouseMessage( pMsg ) ) != WMSG_FAIL )
							{
								if(wmsgResult == WMSG_COMMAND)
								{
									ChangeBoss();
								}
								return WMSG_SUCCESS;
							}
							// Accept(�δ��� �Ӹ�)
							else if( (wmsgResult = m_btnAcceptNew.MouseMessage( pMsg ) ) != WMSG_FAIL )
							{
								if(wmsgResult == WMSG_COMMAND)
								{
									AddViceBoss();
								}
								return WMSG_SUCCESS;
							}
							// Reject(�δ��� ����)
							else if( (wmsgResult = m_btnRejectNew.MouseMessage( pMsg ) ) != WMSG_FAIL )
							{
								if(wmsgResult == WMSG_COMMAND)
								{
									DelViceBoss();
								}
								return WMSG_SUCCESS;
							}
							// Member fire(�ܿ� ����)
							else if( (wmsgResult = m_btnMemberFireNew.MouseMessage( pMsg ) ) != WMSG_FAIL )
							{
								if(wmsgResult == WMSG_COMMAND)
								{
									MemberFire();
								}
								return WMSG_SUCCESS;
							}
							// ���� ����
							else if( (wmsgResult = m_btnChangeSetting.MouseMessage( pMsg ) ) != WMSG_FAIL )
							{
								// Ȱ��ȭ
								if(m_lbManageMemberList.GetCurSel()>=0)
								{
									ResetManagePopupString();
									SetManagePopup(TRUE);
								}
								return WMSG_SUCCESS;						
							}
							else if( (wmsgResult = m_btnChangeSettingAll.MouseMessage( pMsg ) ) != WMSG_FAIL )
							{
								ResetManageSetAllPopupString();
								SetManageSetAllPopup(TRUE, eDONATE_UI_SET_ALL);
								return WMSG_SUCCESS;						
							}
						}					
					}
					break;
				}
					
			}			
			else
			{
				if( IsInside( nX, nY ) )
				{
					// Reset holding button
					pUIManager->ResetHoldBtn();
					
					return WMSG_SUCCESS;
				}
			}
			
		}
		break;

	case WM_MOUSEWHEEL:
		{
			if( IsInsideRect( nX, nY , m_rcWindowNew ) )
			{
				switch(m_iSelTab)
				{
					case NEW_GUILD_INFO: 
						// List
						m_lbMemberAllianceList.MouseMessage( pMsg );
						m_lbMemberHostilityList.MouseMessage( pMsg );							
						break;
					case NEW_GUILD_MEMBER_INFO:
						if (m_bApplyDonateUI == FALSE)
						{
							if (m_pGuildMember != NULL)
								m_pGuildMember->MouseMessage(pMsg);
						}						
						break;
					case NEW_GUILD_SKILL:
						if ( m_sbGuildSkillBar.MouseMessage( pMsg ) != WMSG_FAIL )
						{
							SetSkillBtnInfo();
							return WMSG_SUCCESS;
						}
						else if ( m_lbUseInfo.MouseMessage( pMsg ) != WMSG_FAIL )
						{
							return WMSG_SUCCESS;
						}
						else if ( m_lbLearnInfo.MouseMessage( pMsg ) != WMSG_FAIL )
						{
							return WMSG_SUCCESS;
						}
						else if ( m_lbGuildSkillDesc.MouseMessage( pMsg ) != WMSG_FAIL )
						{
							return WMSG_SUCCESS;
						}
						break;
#ifndef LOCAL_NEW_GUILD // �ؿ� ���� �������� ����
					case NEW_GUILD_BOARD:
						MouseMessageNewBoard(pMsg);
						break;
#endif
					case NEW_GUILD_NOTICE:
						m_ebNoticeTitle.MouseMessage( pMsg );
						m_mebNoticeContent.MouseMessage( pMsg );
						break;
					case NEW_GUILD_MANAGE:
						m_lbManageMemberList.MouseMessage( pMsg );
						break;
				}
				
				return WMSG_SUCCESS;
			}
		}
		break;
	case WM_RBUTTONDOWN:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();

			if( m_pGuildMember && m_pGuildMember->IsInside( nX, nY) )
			{
				if (pUIManager->GetGuild()->IsEnabled() && !pUIManager->GetGuild()->IsVisible())
				{
					pUIManager->RearrangeOrder( UI_GUILD, TRUE );
				}

				CTString strTargetName;
				switch(m_iSelTab)
				{
				case NEW_GUILD_MEMBER_INFO:
					{
						if (m_bApplyDonateUI == FALSE)
						{
							if (m_pGuildMember->m_pList == NULL)
								return WMSG_FAIL;

							return OpenGuildPop(m_pGuildMember->m_pList->getMouseOverItem(), nX, nY);
						}						
					}
					break;
				}
				pUIManager->RearrangeOrder( UI_GUILD, TRUE );
				return WMSG_SUCCESS;
			}
			else
			{
				pUIManager->GetSimplePop()->ClosePop();
			}
		}
		break;
	case WM_LBUTTONDBLCLK :		
	case WM_RBUTTONDBLCLK :
		return WMSG_SUCCESS;
	}
	return WMSG_FAIL;
}

void CUIGuild::SetManageSetAllPopup( BOOL bEnable, int nOpenType )
{
	if (m_pGuildDonateUI == NULL)
		return;

	BOOL bTemp = bEnable;

	if (nOpenType < 0 || nOpenType >= eDONATE_UI_TYPE_MAX)
		bTemp = FALSE;

	m_bApplyDonateUI = bTemp;
	m_pGuildDonateUI->toggleVisible(bTemp, nOpenType);
	m_btnExitNew.SetEnable(!bTemp);
	m_btnCloseNew.SetEnable(!bTemp);

	if (m_iSelTab == NEW_GUILD_MEMBER_INFO)
	{
		if (m_pGuildMember != NULL)
		{
			COLOR color;
			if (bTemp == TRUE)
				color = 0x66686Eff;
			else
				color = 0xf2f2f2ff;

			m_pGuildMember->SetFontColor(color);
		}
	}
	
	if( bEnable && nOpenType == eDONATE_UI_CHANGE_INFO)
 	{
		int nSize = m_vectorMemberList.size();
		int nMyCharPosInMemberList = -1;

		for (int i = 0; i < nSize; ++i)
		{
			if (m_vectorMemberList[i].lIndex == _pNetwork->MyCharacterInfo.index )
			{
				nMyCharPosInMemberList = i;
				break;
			}
		}

		if (nMyCharPosInMemberList < 0 || nMyCharPosInMemberList >= nSize)
			return;

		CTString strTemp;
		if (m_lbManageMemberListEx.GetCurItemCount(0) > nMyCharPosInMemberList)
		{
			strTemp = m_lbManageMemberListEx.GetString( 0, nMyCharPosInMemberList );
			strTemp.DeleteChar( strTemp.Length()-1 );
			m_pGuildDonateUI->SetString(CGuildDonateUI::eEDIT_EXP_MIN, strTemp);
		}

		if (m_lbManageMemberListEx.GetCurItemCount(1) > nMyCharPosInMemberList)
		{
			strTemp = m_lbManageMemberListEx.GetString( 1, nMyCharPosInMemberList );
			strTemp.DeleteChar( strTemp.Length()-1 );
			m_pGuildDonateUI->SetString(CGuildDonateUI::eEDIT_EXP_MAX, strTemp);
		}

		if (m_lbManageMemberListEx.GetCurItemCount(2) > nMyCharPosInMemberList)
		{
			strTemp = m_lbManageMemberListEx.GetString( 2, nMyCharPosInMemberList );
			strTemp.DeleteChar( strTemp.Length()-1 );
			m_pGuildDonateUI->SetString(CGuildDonateUI::eEDIT_FAME_MIN, strTemp);
		}

		if (m_lbManageMemberListEx.GetCurItemCount(3) > nMyCharPosInMemberList)
		{
			strTemp = m_lbManageMemberListEx.GetString( 3, nMyCharPosInMemberList );
			strTemp.DeleteChar( strTemp.Length()-1 );
			m_pGuildDonateUI->SetString(CGuildDonateUI::eEDIT_FAME_MAX, strTemp);
		}

		if (m_lbManageMemberList.GetCurItemCount(4) > nMyCharPosInMemberList)
		{
			strTemp = m_lbManageMemberList.GetString( 4, nMyCharPosInMemberList );
			strTemp.DeleteChar( strTemp.Length()-1 );
			m_pGuildDonateUI->SetString(CGuildDonateUI::eEDIT_EXP, strTemp);
		}

		if (m_lbManageMemberList.GetCurItemCount(5) > nMyCharPosInMemberList)
		{
			strTemp = m_lbManageMemberList.GetString( 5, nMyCharPosInMemberList );
			strTemp.DeleteChar( strTemp.Length()-1 );
			m_pGuildDonateUI->SetString(CGuildDonateUI::eEDIT_FAME, strTemp);
		}
 	}
}

void CUIGuild::SetManagePopup(BOOL bEnable)
{
	if (m_pGuildChangeSetUI == NULL)
		return;

	m_bApplySettingOn = bEnable;

	m_pGuildChangeSetUI->toggleVisible(bEnable);
	m_btnExitNew.SetEnable(!bEnable);
	m_btnCloseNew.SetEnable(!bEnable);
	// data setting. [6/24/2011 rumist]
	if( bEnable )
	{
 		CTString strTemp = m_lbManageMemberList.GetString( 1, m_lbManageMemberList.GetCurSel() );
 		m_pGuildChangeSetUI->SetString(CGuildChangeSetUI::eEDIT_CHANGE_POSITION, strTemp);

 		strTemp = m_lbManageMemberListEx.GetString( 0, m_lbManageMemberList.GetCurSel() );
 		strTemp.DeleteChar( strTemp.Length()-1 );
		m_pGuildChangeSetUI->SetString(CGuildChangeSetUI::eEDIT_EXP_MIN, strTemp);

		strTemp = m_lbManageMemberListEx.GetString( 1, m_lbManageMemberList.GetCurSel() );
		strTemp.DeleteChar( strTemp.Length()-1 );
		m_pGuildChangeSetUI->SetString(CGuildChangeSetUI::eEDIT_EXP_MAX, strTemp);

		strTemp = m_lbManageMemberListEx.GetString( 2, m_lbManageMemberList.GetCurSel() );
		strTemp.DeleteChar( strTemp.Length()-1 );
		m_pGuildChangeSetUI->SetString(CGuildChangeSetUI::eEDIT_FAME_MIN, strTemp);

		strTemp = m_lbManageMemberListEx.GetString( 3, m_lbManageMemberList.GetCurSel() );
		strTemp.DeleteChar( strTemp.Length()-1 );
		m_pGuildChangeSetUI->SetString(CGuildChangeSetUI::eEDIT_FAME_MAX, strTemp);
	}
#ifdef ENABLE_GUILD_STASH
	
	if( bEnable )
	{
		CTString strTemp = m_lbManageMemberList.GetString( 6, m_lbManageMemberList.GetCurSel() );
		m_pGuildChangeSetUI->SetStashUsable( strTemp == _S(5560, "����") ? TRUE : FALSE );
	}
#endif
	if ( bEnable )
		SetCorpsComboBox();
}

void CUIGuild::ResetManagePopupString()
{
	if (m_pGuildChangeSetUI != NULL)
		m_pGuildChangeSetUI->ResetEditBox();

#ifdef ENABLE_GUILD_STASH
	m_pGuildChangeSetUI->SetStashUsable( FALSE );
#endif
}

void CUIGuild::ResetManageSetAllPopupString()
{
	if (m_pGuildDonateUI != NULL)
		m_pGuildDonateUI->ResetEditBox();
}

BOOL CUIGuild::CheckDataValidationDonate()
{
	if (m_pGuildDonateUI == NULL)
		return FALSE;

	CUIManager* pUIManager = CUIManager::getSingleton();
	CUIMsgBox_Info	MsgBoxInfo;
	int tInt;
	CTString tStr;

	pUIManager->CloseMessageBox(MSGCMD_NULL);
	MsgBoxInfo.SetMsgBoxInfo( _S(3877, "�Է� ����" ), UMBS_OK,
		UI_NONE,MSGCMD_NULL );

	for (int i = 0; i < CGuildDonateUI::eEDIT_MAX; ++i)
	{
		tStr = m_pGuildDonateUI->GetString(i);

		if (!tStr.IsInteger())
		{
			switch(i)
			{
			case CGuildDonateUI::eEDIT_EXP_MIN:
			case CGuildDonateUI::eEDIT_EXP_MAX:
			case CGuildDonateUI::eEDIT_EXP:
				MsgBoxInfo.AddString( _S(3879, "����ġ �Է��� �߸� �Ǿ����ϴ�.") );
				break;
			case CGuildDonateUI::eEDIT_FAME_MIN:
			case CGuildDonateUI::eEDIT_FAME_MAX:
			case CGuildDonateUI::eEDIT_FAME:
				MsgBoxInfo.AddString( _S(3881, "����ġ �Է��� �߸� �Ǿ����ϴ�.") );
				break;
			}

			pUIManager->CreateMessageBox( MsgBoxInfo );
			return FALSE;
		}

		tInt = atoi(tStr.str_String);

		if( tInt > 100 || tInt < 0 )
		{
			MsgBoxInfo.AddString( _S(3880, "[0~100]���� ���ڸ� �Է��� �ּ���.") );
			pUIManager->CreateMessageBox( MsgBoxInfo );
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CUIGuild::CheckDataValidation()
{
	if (m_pGuildChangeSetUI == NULL)
		return FALSE;

	CUIManager* pUIManager = CUIManager::getSingleton();
	CUIMsgBox_Info	MsgBoxInfo;
	int tInt;
	CTString tStr;

	pUIManager->CloseMessageBox(MSGCMD_NULL);
	MsgBoxInfo.SetMsgBoxInfo( _S(3877, "�Է� ����" ), UMBS_OK,
									UI_NONE,MSGCMD_NULL );

	// ������ ���� ���� �˻�
	tStr = m_pGuildChangeSetUI->GetString(CGuildChangeSetUI::eEDIT_CHANGE_POSITION);
	if( tStr.Length() == 0 )
	{
		MsgBoxInfo.AddString( _S(3878, "�Էµ� ���ڰ� �����ϴ�.") );
		pUIManager->CreateMessageBox( MsgBoxInfo );
		return FALSE;
		
	}
	else if (UTIL_HELP()->IsSpecialChar(tStr.str_String) == true)
	{
		MsgBoxInfo.AddString(_S( 437, "���忡 ������ �ܾ ���ԵǾ� �ֽ��ϴ�.")); 
		pUIManager->CreateMessageBox( MsgBoxInfo );
		return FALSE;
	}
	else if( _UIFiltering.Filtering ( tStr.str_String ) == TRUE)
	{		
		CTString	strMessage = _S( 435, "�߸��� ����[" );	
		strMessage += tStr.str_String;
		strMessage += _S( 436, "]�� ���ԵǾ� �ֽ��ϴ�." );
		
		MsgBoxInfo.AddString( strMessage );
		pUIManager->CreateMessageBox( MsgBoxInfo );
		m_pGuildChangeSetUI->ResetCharPostionString();
		return FALSE;
	}

	// �� ���� �˻�
	for (int i = 1; i < CGuildChangeSetUI::eEDIT_MAX; ++i)
	{
		tStr = m_pGuildChangeSetUI->GetString(i);

		if (!tStr.IsInteger())
		{
			switch(i)
			{
			case CGuildChangeSetUI::eEDIT_EXP_MIN:
			case CGuildChangeSetUI::eEDIT_EXP_MAX:
				MsgBoxInfo.AddString( _S(3879, "����ġ �Է��� �߸� �Ǿ����ϴ�.") );
				break;
			case CGuildChangeSetUI::eEDIT_FAME_MIN:
			case CGuildChangeSetUI::eEDIT_FAME_MAX:
				MsgBoxInfo.AddString( _S(3881, "����ġ �Է��� �߸� �Ǿ����ϴ�.") );
				break;
			}

			pUIManager->CreateMessageBox( MsgBoxInfo );
			return FALSE;
		}

		tInt = atoi(tStr.str_String);

		if( tInt > 100 || tInt < 0 )
		{
			MsgBoxInfo.AddString( _S(3880, "[0~100]���� ���ڸ� �Է��� �ּ���.") );
			pUIManager->CreateMessageBox( MsgBoxInfo );
			return FALSE;
		}
	}

	if ( m_pGuildChangeSetUI->GetComboCurSelIdx() < 0 )
	{
		MsgBoxInfo.AddString( _S( 5331, "�� ������ �߸� �Ǿ����ϴ�.") );
		pUIManager->CreateMessageBox( MsgBoxInfo );
		return FALSE;
	}
	return TRUE;
}

// Message Send -------------------->><<
// ��� ���� ��û 
void CUIGuild::SendRequestGuildTab(int iTabNum)
{
	CNetworkMessage nmGuild((UBYTE)MSG_GUILD);

	switch(iTabNum)
	{
	case NEW_GUILD_INFO :		
		nmGuild << (UBYTE)MSG_NEW_GUILD_INFO;
		break;
	case NEW_GUILD_MEMBER_INFO :
		{
			if (m_pGuildMember != NULL)
				m_pGuildMember->resetList();
			m_vecGuildMember.clear();
			m_ContGuild.clear();
			ResetArrangeState();
			m_iOnlineMembers =0;

			nmGuild << (UBYTE)MSG_NEW_GUILD_MEMBERLIST;			
		}
		break;
	case NEW_GUILD_SKILL :
		nmGuild << (UBYTE)MSG_NEW_GUILD_SKILL;	
		break;
#ifndef LOCAL_NEW_GUILD // �ؿ� ���� �������� ����
	case NEW_GUILD_BOARD :
		// TODO :: ��� �Խ���
		break;
#endif
	case NEW_GUILD_NOTICE :
		nmGuild << (UBYTE)MSG_NEW_GUILD_NOTICE;	
		break;
	case NEW_GUILD_MANAGE :
		{
			// Member List Init
			m_lbManageMemberList.ResetAllStrings();
			m_vManageMemberIndex.clear();
			ClearMemberList();

			nmGuild << (UBYTE)MSG_NEW_GUILD_MANAGE;
		}
		break;
	}
	_pNetwork->SendToServerNew(nmGuild);

}

// ��� ���� ����
void CUIGuild::SendChangeGuildInclination(UBYTE ubIncline)
{	
	CNetworkMessage nmGuild((UBYTE)MSG_GUILD);
	nmGuild << (UBYTE)MSG_NEW_GUILD_INCLINE_ESTABLISH << ubIncline;
	_pNetwork->SendToServerNew(nmGuild);
}

// ��� ���� ����
void CUIGuild::SendAdjustGuildMemberInfo(int charIdx, CTString posName ,int expMin, int expMax, int fameMin, int fameMax, int corps /* = -1 */, UBYTE ubStashAuth /* = 0  */)
{	
	CNetworkMessage nmGuild((UBYTE)MSG_GUILD);
	nmGuild << (UBYTE)MSG_NEW_GUILD_MEMBER_ADJUST
			<< (ULONG)charIdx
			<< posName
			<< (ULONG)expMin
			<< (ULONG)expMax
			<< (ULONG)fameMin
			<< (ULONG)fameMax;
	nmGuild	<< (INDEX)corps;
#ifdef ENABLE_GUILD_STASH
	nmGuild << (UBYTE)ubStashAuth;
#endif
	_pNetwork->SendToServerNew(nmGuild);	
}

// ��� ��ü ������ ����
void CUIGuild::SendAdjustGuildMemberInfoAll( int expMin, int expMax, int fameMin, int fameMax, int AdjustExp, int AdjustFame )
{
	CNetworkMessage nmGuild((UBYTE)MSG_GUILD);
	nmGuild << (UBYTE)MSG_GUILD_CONTRIBUTE_SETALL
		<< (ULONG)AdjustExp
		<< (ULONG)AdjustFame
		<< (ULONG)expMin
		<< (ULONG)expMax
		<< (ULONG)fameMin
		<< (ULONG)fameMax;
	_pNetwork->SendToServerNew(nmGuild);	
}

// ����ġ, ����ġ �� ���� ��û
void CUIGuild::SendGuildDonateInfo()
{
	CNetworkMessage nmGuild((UBYTE)MSG_GUILD);
	nmGuild << (UBYTE)MSG_GUILD_CONTRIBUTE_DATA;
	_pNetwork->SendToServerNew(nmGuild);	
}

// ����ġ, ����ġ �󳳵� ����
void CUIGuild::SendAdjustGuildDonateInfo(int AdjustExp, int AdjustFame )
{
	CNetworkMessage nmGuild((UBYTE)MSG_GUILD);
	nmGuild << (UBYTE)MSG_GUILD_CONTRIBUTE_SET
		<< (ULONG)AdjustExp
		<< (ULONG)AdjustFame;

	_pNetwork->SendToServerNew(nmGuild);	
}

// ��� ���� ������Ʈ(�����)
void CUIGuild::SendUpdateGuildNotice( CTString strTitle, CTString strContents)
{
	CNetworkMessage nmGuild((UBYTE)MSG_GUILD);
	EncodeNoticeString(strContents);
	nmGuild << (UBYTE)MSG_NEW_GUILD_NOTICE_UPDATE
			<< strTitle
			<< strContents;	
	
	_pNetwork->SendToServerNew(nmGuild);
}

//  ����� ���� ��û
void CUIGuild::SendRequestGuildNotice()
{
	CNetworkMessage nmGuild((UBYTE)MSG_GUILD);
	nmGuild << (UBYTE)MSG_NEW_GUILD_NOTICE_REQUEST;
	_pNetwork->SendToServerNew(nmGuild);

}

// ��� ��ų �����ϱ�
void CUIGuild::SendLearnGuildSkill(int skillIdx) 
{	
	CNetworkMessage nmGuild((UBYTE)MSG_GUILD);
	nmGuild << (UBYTE)MSG_NEW_GUILD_SKILL_LEARN;
	nmGuild << (ULONG)skillIdx;
	_pNetwork->SendToServerNew(nmGuild);
}

// Message Receive----------------->><<
void CUIGuild::ReceiveNewGuildMessage(UBYTE ubType,CNetworkMessage* istr)
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	
	switch(ubType)
	{		
		case MSG_NEW_GUILD_INCLINE_ESTABLISH:			
			// TODO : ��� ���� ó��
			break;		
		case MSG_NEW_GUILD_INFO:
			{
				ULONG GuildLevel;
				ULONG NumOfMember;
				ULONG NumOfMaxMember;
				ULONG GuildAverageLevel;
				SQUAD GuildTotalPoint;
				SQUAD GuildMyPoint;	

				(*istr) >> m_strGuildName
						>> GuildLevel
						>> m_strBossName
						>> NumOfMember
						>> NumOfMaxMember
						>> GuildAverageLevel
						>> GuildTotalPoint
						>> GuildMyPoint;	
				m_iGuildLevel			= (int)GuildLevel;
				m_iNumOfMember			= (int)NumOfMember;
				m_iNumOfMaxMember       = (int)NumOfMaxMember;
				m_iGuildAverageLevel    = (int)GuildAverageLevel;
				m_iGuildTotalPoint  	= (int)GuildTotalPoint;
				m_iGuildMyPoint			= (int)GuildMyPoint;	
				_pNetwork->MyCharacterInfo.iGP = GuildTotalPoint;

// [sora] GUILD_MARK
#ifdef GUILD_MARK
				SBYTE gm_row, gm_col, bg_row, bg_col;
				LONG guildMarkTime;

				(*istr) >> gm_row;
				(*istr) >> gm_col;
				(*istr) >> bg_row;
				(*istr) >> bg_col;
				(*istr) >> guildMarkTime;


				// todo ��� ��ũ ���� �߰�
				MY_INFO()->_guildmark.setData(gm_row, gm_col, bg_row, bg_col);
				UIMGR()->SetGuildMark();
				m_pIconGuildMark->CalcUV(gm_row, gm_col, true);
				m_pIconGuildMark->CalcUV(bg_row, bg_col, false);
				m_guildMarkTime = guildMarkTime;
				
				if( m_guildMarkTime >= 0 )
				{
					time_t tv_used = m_guildMarkTime;

					tm* g_tv_t = localtime((time_t*)&tv_used);

					m_strGuildMarkTime.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),g_tv_t->tm_year + 1900
						,g_tv_t->tm_mon + 1,g_tv_t->tm_mday,g_tv_t->tm_hour, g_tv_t->tm_min);
				}
				else
				{
					m_strGuildMarkTime = _s("");
				}
#endif
			}
			break;
		case MSG_NEW_GUILD_MEMBERLIST:
			{
				int i;
				CTString tPosName;
				CTString strMemName;
				ULONG ulListCnt;
				ULONG charLevel;
				LONG  zoneIndex;
				SQUAD cumulPoint;
				UBYTE iJob;
				UBYTE iJob2;	
				UBYTE bPlaying;
				ULONG ulPosition;	// ĳ���� ����(BOSS,VICEBOSS.MEMBER)
				LONG nlogout_date;

				//m_lbGuildMemberList.ResetAllStrings();
				//m_iOnlineMembers =0;
				(*istr) >> ulListCnt;				

				for(i=0; i<ulListCnt; i++)
				{
					clsGuildMemberNew* tGuildMemberNew = new clsGuildMemberNew;
					(*istr)	>> strMemName
						>> tPosName
							>> charLevel
							>> bPlaying
							>> zoneIndex
							>> cumulPoint
							>> iJob
							>> iJob2
							>> ulPosition
							>> nlogout_date;

					if(bPlaying)
						m_iOnlineMembers++;

					tGuildMemberNew->strMemberName  = strMemName.str_String;
					tGuildMemberNew->sPosName		= ResetPosName(tPosName,(INT)ulPosition).str_String;
					tGuildMemberNew->iLevel			= (INT)charLevel;
					tGuildMemberNew->bOnline		= (BOOL)bPlaying;
					tGuildMemberNew->iLocation		= (INT)zoneIndex;
					tGuildMemberNew->iCumulPoint	= cumulPoint;
					tGuildMemberNew->iJob			= (INT)iJob;
					tGuildMemberNew->iJob2			= (INT)iJob2;
					tGuildMemberNew->eRanking		= (INT)ulPosition;
					tGuildMemberNew->nLogoutDate	= (INT)nlogout_date;

					if (ulPosition == GUILD_MEMBER_MEMBER)
						tGuildMemberNew->nArrangeRank = MSG_GUILD_POSITION_UNKNOWN - 1;
					else
						tGuildMemberNew->nArrangeRank = (int)ulPosition;

					// TODO :: ����� �޴� Ȯ��... iJob�� ��Ʈ�� �����Ҷ��� �־...
					tGuildMemberNew->sJobName	= CJobInfo::getSingleton()->GetName(iJob,iJob2);					
					//if((int)zoneIndex == -1 )
					//	tGuildMemberNew->sLocName = _S(3978, "������");
					if ((int)zoneIndex >= 0) 
						tGuildMemberNew->sLocName = CZoneInfo::getSingleton()->GetZoneName( zoneIndex );
					
					m_ContGuild.insert(clsGuildMemberNew::SP(tGuildMemberNew));

					AddGuildMemberInfo(*tGuildMemberNew);
				}

				INDEX iCorpsMember, iCorpsBoss;
				(*istr)  >> iCorpsMember
						 >> iCorpsBoss;
				SetCorpsInfo( iCorpsMember, iCorpsBoss );

				updateGuildMemberList();
			}
			break;
		case MSG_NEW_GUILD_SKILL:
			// TODO :: ���� ��ų���� �߰� �� �۾�
			// skillcount(n) skillindex(n) skillLeanLevel(n) skillMaxLevel(n)
			{
				ReceiveGuildSkillExtend(istr);
			}
			break;
		case MSG_NEW_GUILD_NOTICE:
			{	
				m_iSelTab = NEW_GUILD_NOTICE;
				CTString tStr;
				(*istr) >> tStr;
				m_ebNoticeTitle.SetString(tStr.str_String);
				(*istr) >> tStr;
				DecodeNoticeString(tStr);
				m_mebNoticeContent.SetString(tStr.str_String);
			}
			break;			
		case MSG_NEW_GUILD_NOTICE_TRANSMISSION:
			{
				CTString tStr,tStr2;
				(*istr) >> m_strGuildName;		
				(*istr) >> tStr;				
				(*istr) >> tStr2;			
				DecodeNoticeString(tStr2);
				pUIManager->GetGuildNotice()->SetGuildNotice(m_strGuildName,tStr,tStr2);
				pUIManager->RearrangeOrder( UI_GUILD_NOTICE, TRUE );
			}
			break;
		case MSG_NEW_GUILD_MANAGE:
			{
				clsGuildMemberNew tMemberInfo;
				BYTE bFirstListMember;
				INDEX tLoop;
				ULONG eRanking;
				ULONG iLevel;
				ULONG iExpServ;
				ULONG iPayExpMin;
				ULONG iPayExpMax;
				ULONG iFameServ;
				ULONG iPayFameMin;
				ULONG iPayFameMax;
				ULONG icharIdx;
				BYTE bStashPermission = 0;
				CTString strMemName;
				CTString strPosName;
				(*istr) >> bFirstListMember;
				(*istr) >> tLoop;
				
				if (bFirstListMember > 0)
				{
					// Member List Init
					m_lbManageMemberList.ResetAllStrings();
					m_vManageMemberIndex.clear();
					ClearMemberList();					
				}

				for(int i=0;i<tLoop;i++)
				{
					(*istr) >> eRanking
						>> strMemName
						>> strPosName
						>> iLevel
						>> iPayExpMin
						>> iPayExpMax
						>> iPayFameMin
						>> iPayFameMax
						>> iExpServ
						>> iFameServ
						>> icharIdx
#ifdef ENABLE_GUILD_STASH
						>> bStashPermission
#endif
						;
					tMemberInfo.strMemberName = strMemName.str_String;
					tMemberInfo.sPosName    = strPosName.str_String;
					tMemberInfo.eRanking	= eRanking;
					tMemberInfo.iLevel		= iLevel;
					tMemberInfo.iExpServ	= iExpServ;
					tMemberInfo.iDonateExpMin	= iPayExpMin;
					tMemberInfo.iDonateExpMax	= iPayExpMax;
					tMemberInfo.iFameServ	= iFameServ;
					tMemberInfo.iDonateFameMin	= iPayFameMin;
					tMemberInfo.iDonateFameMax	= iPayFameMax;
#ifdef ENABLE_GUILD_STASH
					tMemberInfo.bStashPermission = bStashPermission;
#endif
					tMemberInfo.sRanking	= ResetPosName( CTString(""), eRanking );
					tMemberInfo.sPosName	= ResetPosName( CTString(tMemberInfo.sPosName.c_str()), eRanking );

					m_vManageMemberIndex.push_back(icharIdx);
					AddGuildManageInfo(tMemberInfo);
					// ����� ����,�Ӹ�,����,����� ���� ��ƾ�� ����ϱ� ����					
					AddToMemberList(icharIdx,CTString(tMemberInfo.strMemberName.c_str()),eRanking,FALSE);
				}
				INDEX iCorpsMember, iCorpsBoss;
				(*istr)  >> iCorpsMember
						 >> iCorpsBoss;
				SetCorpsInfo( iCorpsMember, iCorpsBoss );
			}			
			break;
	
		case MSG_NEW_GUILD_POINT_RANKING:
			{
				ULONG charindex;
				ULONG guildindex;
				ULONG rankingv;
				(*istr) >> charindex
						>> guildindex
						>> rankingv;

				if( charindex == _pNetwork->MyCharacterInfo.index)
				{				
					if( _pNetwork->MyCharacterInfo.lGuildIndex == guildindex )
						_pNetwork->MyCharacterInfo.sbGuildRank = rankingv;		
				}
				else
				{
					ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, charindex);

					if (pObject != NULL)
					{
						CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);

						if (pTarget->cha_lGuildIndex == guildindex)
						{
							pTarget->cha_sbGuildRank = rankingv;
						}
					}
				}
			}
			break;
		case MSG_GUILD_GP_INFO:
			{
				SQUAD iGP;
				(*istr) >> iGP;

				_pNetwork->MyCharacterInfo.iGP = iGP;
				m_iGuildTotalPoint = iGP;
			}
			break;
		// [2010/11/01 : Sora] ���� ����
		case MSG_GUILD_WAR_SET_TIME_MENU:
			{
				UBYTE count, zone, wday, hour;
				CUISiegeWarfare::stSiegeWarfareTimeInfo swInfo;
				
				pUIManager->GetSiegeWarfare()->InitSiegeWarfareTimeInfo();

				(*istr) >> count;
				for( int i=0; i<count; ++i )
				{
					(*istr) >> zone;
					(*istr) >> wday;
					(*istr) >> hour;

					swInfo.zone = zone;
					swInfo.wday = wday;
					swInfo.hour = hour;

					pUIManager->GetSiegeWarfare()->SetSiegeWarfareTimeInfo( swInfo );
				}

				pUIManager->GetSiegeWarfare()->OpenSetSWTime();
			}
			break;
		case MSG_GUILD_WAR_GET_TIME_UNI_REP:
			{
				SBYTE count, zone, month, day, hour, joinFlag, info;
				CTString guildName, guildBossName;

				pUIManager->GetSiegeWarfareInfo()->InitSiegeWarfareInfo();

				(*istr) >> count;

				CUISiegeWarfareInfo::stSiegeWarfareDefGuildInfo defGuildInfo;
				for( int i=0; i<count; ++i )
				{
					defGuildInfo.Init();

					(*istr) >> zone;
					(*istr) >> guildName;
					(*istr) >> month;
					(*istr) >> day;
					(*istr) >> hour;

					defGuildInfo.zone = zone;
					defGuildInfo.guildName = guildName;
					defGuildInfo.month = month;
					defGuildInfo.day = day;
					defGuildInfo.hour = hour;

					pUIManager->GetSiegeWarfareInfo()->SetSiegeWarfareDefGuildInfo( defGuildInfo );
				}

				(*istr) >> info;

				for (int i = 0; i < info; i++)
				{
					(*istr) >> guildName;
					(*istr) >> guildBossName;

					pUIManager->GetSiegeWarfareInfo()->SetMySiegeWarfareGuildInfo( guildName, guildBossName );

					(*istr) >> count;

					for( int i = 0; i < count; ++i )
					{
						(*istr) >> joinFlag;
						(*istr) >> zone;
						
						if( zone >= 0 )
						{
							pUIManager->GetSiegeWarfareInfo()->SetMySiegeWarfareJoinInfo( zone, joinFlag );
						}
					}
				}

				pUIManager->GetSiegeWarfareInfo()->ToggleSiegeWarfareInfo(TRUE);
			}
			break;
		case MSG_NEW_GUILD_MARK_EDIT_FIN:
			{
				pUIManager->GetChattingUI()->AddSysMessage( _S( 5511, "��� ��ũ�� ����Ͽ����ϴ�.") );

				SBYTE gm_row, gm_col, bg_row, bg_col;
				LONG guildMarkTime;

				(*istr) >> gm_row;
				(*istr) >> gm_col;
				(*istr) >> bg_row;
				(*istr) >> bg_col;
				(*istr) >> guildMarkTime;

				MY_INFO()->_guildmark.setData(gm_row, gm_col, bg_row, bg_col);
				UIMGR()->SetGuildMark();
				m_pIconGuildMark->CalcUV(gm_row, gm_col, true);
				m_pIconGuildMark->CalcUV(bg_row, bg_col, false);
				m_guildMarkTime = guildMarkTime;
				
				if( m_guildMarkTime >= 0 )
				{
					time_t tv_used = m_guildMarkTime;

					tm* g_tv_t = localtime((time_t*)&tv_used);

					m_strGuildMarkTime.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),g_tv_t->tm_year + 1900
						,g_tv_t->tm_mon + 1,g_tv_t->tm_mday,g_tv_t->tm_hour, g_tv_t->tm_min);
				}
				else
				{
					m_strGuildMarkTime = _s("");
				}
			}
			break;
		case MSG_NEW_GUILD_MARK_EXPIRE:
			{
				pUIManager->GetChattingUI()->AddSysMessage( _S( 5512, "��� ��ũ�� ��� �Ⱓ�� ����Ǿ����ϴ�.") );

				MY_INFO()->_guildmark.remove();
				pUIManager->GetGuildMark()->InitGuidMark();
			}
			break;

		case MSG_GUILD_CONTRIBUTE_DATA:
			{
				ULONG iExpServ;
				ULONG iPayExpMin;
				ULONG iPayExpMax;
				ULONG iFameServ;
				ULONG iPayFameMin;
				ULONG iPayFameMax;

				(*istr) >> iExpServ
					>> iFameServ
					>> iPayExpMin
					>> iPayExpMax
					>> iPayFameMin
					>> iPayFameMax;

				int nSize = m_vectorMemberList.size();
				int nMyCharPosInMemberList = -1;
				bool bFind = false;
				for (int i = 0; i < nSize; ++i)
				{
					if (m_vectorMemberList[i].lIndex == _pNetwork->MyCharacterInfo.index )
					{
						nMyCharPosInMemberList = i;
						bFind = true;
						break;
					}
				}

				if (bFind == true)
				{
					CTString StrTemp;
					StrTemp.PrintF("%d%%", iPayExpMin);	
					if (m_lbManageMemberListEx.GetCurItemCount(0) > nMyCharPosInMemberList)
						m_lbManageMemberListEx.SetString( 0, nMyCharPosInMemberList, StrTemp);
					else
					{
						if (m_pGuildDonateUI)
						{
							StrTemp.DeleteChar( StrTemp.Length()-1 );
							m_pGuildDonateUI->SetString(CGuildDonateUI::eEDIT_EXP_MIN, StrTemp);
						}
					}

					StrTemp.PrintF("%d%%", iPayExpMax);
					if (m_lbManageMemberListEx.GetCurItemCount(1) > nMyCharPosInMemberList)
						m_lbManageMemberListEx.SetString( 1, nMyCharPosInMemberList, StrTemp);
					else
					{
						if (m_pGuildDonateUI)
						{
							StrTemp.DeleteChar( StrTemp.Length()-1 );
							m_pGuildDonateUI->SetString(CGuildDonateUI::eEDIT_EXP_MAX, StrTemp);
						}
					}

					StrTemp.PrintF("%d%%", iPayFameMin);
					if (m_lbManageMemberListEx.GetCurItemCount(2) > nMyCharPosInMemberList)
						m_lbManageMemberListEx.SetString( 2, nMyCharPosInMemberList, StrTemp);
					else
					{
						if (m_pGuildDonateUI)
						{
							StrTemp.DeleteChar( StrTemp.Length()-1 );
							m_pGuildDonateUI->SetString(CGuildDonateUI::eEDIT_FAME_MIN, StrTemp);
						}
					}

					StrTemp.PrintF("%d%%", iPayFameMax);
					if (m_lbManageMemberListEx.GetCurItemCount(3) > nMyCharPosInMemberList)
						m_lbManageMemberListEx.SetString( 3, nMyCharPosInMemberList, StrTemp);
					else
					{
						if (m_pGuildDonateUI)
						{
							StrTemp.DeleteChar( StrTemp.Length()-1 );
							m_pGuildDonateUI->SetString(CGuildDonateUI::eEDIT_FAME_MAX, StrTemp);
						}
					}

					StrTemp.PrintF("%d%%", iExpServ);
					if (m_lbManageMemberList.GetCurItemCount(4) > nMyCharPosInMemberList)
						m_lbManageMemberList.SetString( 4, nMyCharPosInMemberList, StrTemp);
					else
					{
						if (m_pGuildDonateUI)
						{
							StrTemp.DeleteChar( StrTemp.Length()-1 );
							m_pGuildDonateUI->SetString(CGuildDonateUI::eEDIT_EXP, StrTemp);
						}
					}
					
					StrTemp.PrintF("%d%%", iFameServ);
					if (m_lbManageMemberList.GetCurItemCount(5) > nMyCharPosInMemberList)
						m_lbManageMemberList.SetString( 5, nMyCharPosInMemberList, StrTemp);
					else
					{
						if (m_pGuildDonateUI)
						{
							StrTemp.DeleteChar( StrTemp.Length()-1 );
							m_pGuildDonateUI->SetString(CGuildDonateUI::eEDIT_FAME, StrTemp);
						}
					}
				}

				// Open ����â.
				pUIManager->GetGuild()->SetManageSetAllPopup(TRUE, eDONATE_UI_CHANGE_INFO);
			}
			break;
	}	
}


void CUIGuild::UpdateGuildSkillLearnMessage(UpdateClient::doNewGuildSkillLearnToMemberMsg& SkillInfo)
{
	MY_INFO()->SetSkill(SkillInfo.skill_index, SkillInfo.skill_level);

	if ( SkillInfo.skill_type == GUILD_SKILL_ACTIVE)
	{
		INDEX tCnt = m_vecGuildActiveSkill.size();
	
		for(int i = 0; i < tCnt; i++)
		{
			if( m_vecGuildActiveSkill[i].GetIndex() == SkillInfo.skill_index)
			{
				m_vecGuildActiveSkill[i].SetCurLevel((int)SkillInfo.skill_level);
				break;
			}
		}
	}
	else if ( SkillInfo.skill_type == GUILD_SKILL_PASSIVE )
	{
		INDEX tCnt = m_vecGuildPassiveSkill.size();
	
		for(int i = 0; i < tCnt; i++)
		{
			if( m_vecGuildPassiveSkill[i].GetIndex() == SkillInfo.skill_index)
			{
				m_vecGuildPassiveSkill[i].SetCurLevel((int)SkillInfo.skill_level);
				break;
			}
		}
	}
	else
	{
		return;
	}

	if( IsVisible() == TRUE )
	{
		SetSkillBtnInfo();
		SetGuildSkillInfo();
		
	}
	
}

// ��� ��� ���� ����Ʈ �߰�
void CUIGuild::AddGuildMemberInfo(clsGuildMemberNew tMemberInfo)
{
	m_vecGuildMember.push_back(tMemberInfo);
}

// ��� ��� ���� ����Ʈ �߰�
void CUIGuild::AddGuildManageInfo(clsGuildMemberNew tMemberInfo)
{
	//�ڱ� ������ �������߰�
	CTString strTemp = tMemberInfo.strMemberName.c_str();
	if(strTemp.Matches(_pNetwork->MyCharacterInfo.name))
	{
		_pNetwork->MyCharacterInfo.guildPosName = tMemberInfo.sPosName.c_str();
	}
	CTString tPer;
	tPer.PrintF("%s",tMemberInfo.sRanking.c_str());
	m_lbManageMemberList.AddString(0,tPer);	
	m_lbManageMemberList.AddString(1,SetPosName(tMemberInfo.sPosName.c_str()));
	tPer.PrintF("%d",tMemberInfo.iLevel);
	m_lbManageMemberList.AddString(2,tPer);
	m_lbManageMemberList.AddString(3,CTString(tMemberInfo.strMemberName.c_str()));
	tPer.PrintF("%d%%",tMemberInfo.iExpServ);
	m_lbManageMemberList.AddString(4,tPer);
	tPer.PrintF("%d%%",tMemberInfo.iFameServ);
	m_lbManageMemberList.AddString(5,tPer);	
#ifdef ENABLE_GUILD_STASH
	m_lbManageMemberList.AddString(6,tMemberInfo.bStashPermission>0?_S(5560, "����") : _S(5561, "�Ұ�") );	
#endif
	tPer.PrintF("%d%%",tMemberInfo.iDonateExpMin);
	m_lbManageMemberListEx.AddString(0,tPer);
	tPer.PrintF("%d%%",tMemberInfo.iDonateExpMax);
	m_lbManageMemberListEx.AddString(1,tPer);
	tPer.PrintF("%d%%",tMemberInfo.iDonateFameMin);
	m_lbManageMemberListEx.AddString(2,tPer);
	tPer.PrintF("%d%%",tMemberInfo.iDonateFameMax);
	m_lbManageMemberListEx.AddString(3,tPer);	
}

// ----------------------------------------------------------------------------
// Name : OpenGuildManagerNew()
// Desc : 
// ----------------------------------------------------------------------------
void CUIGuild::OpenGuildManagerNew()
{
	if (IsVisible()) return;

	m_iGuildLevel = _pNetwork->MyCharacterInfo.lGuildLevel;

	// ������ 6���ϸ� ������� �ʴ´�...	
	if( m_iGuildLevel < LIMIT_GUILD_LEVEL )
	{
		return;
	}

	CUIManager* pUIManager = CUIManager::getSingleton();

	// ���Խ��� ����
	m_pWebBoard = pUIManager->GetWebBoard();

	// �ʱ�ȭ 
	InitNewGuildSystem();	

	// ��� ��ų ����Ʈ.
	SetGuildSkillList();
	m_sbGuildSkillBar.SetCurItemCount(m_vecGuildPassiveSkill.size());

	// ��� ���� ��û
	SendRequestGuildTab(0);

	// ������� ��ġ ���� 
	SetSize( NEW_GUILD_SYSTEM_WIDTH, NEW_GUILD_SYSTEM_HEIGHT );
	extern ENGINE_API CDrawPort	*_pdpMain;
	ResetPosition(_pdpMain->dp_MinI,_pdpMain->dp_MinJ,_pdpMain->dp_MaxI,_pdpMain->dp_MaxJ);
	
	m_eGuildState	= GUILD_MANAGER_NEW;

	pUIManager->RearrangeOrder( UI_GUILD, TRUE );

}

void CUIGuild::EncodeNoticeString(CTString& tStr)
{
	while(tStr.ReplaceSubstr("\r\n","``"));
}

void CUIGuild::DecodeNoticeString(CTString& tStr)
{
	while(tStr.ReplaceSubstr("``","\r\n"));
}

void CUIGuild::AdjustGuildMemberInfo()
{	
	INDEX tRow = m_lbManageMemberList.GetCurSel();
	CTString strCorps = ResetPosName( CTString(""), GetSelectedPositon() );

	m_lbManageMemberList.SetString(0,tRow, strCorps);

	m_vectorMemberList[tRow].eRanking = GetSelectedPositon();
	m_lbManageMemberList.SetString(1, tRow, m_pGuildChangeSetUI->GetString(CGuildChangeSetUI::eEDIT_CHANGE_POSITION));

	CTString strTmp;
	strTmp.PrintF("%s%%", m_pGuildChangeSetUI->GetString(CGuildChangeSetUI::eEDIT_EXP_MIN));
	m_lbManageMemberListEx.SetString(0, tRow, strTmp);

	strTmp.PrintF("%s%%", m_pGuildChangeSetUI->GetString(CGuildChangeSetUI::eEDIT_EXP_MAX));
	m_lbManageMemberListEx.SetString(1, tRow, strTmp);

	strTmp.PrintF("%s%%", m_pGuildChangeSetUI->GetString(CGuildChangeSetUI::eEDIT_FAME_MIN));
	m_lbManageMemberListEx.SetString(2, tRow, strTmp);

	strTmp.PrintF("%s%%", m_pGuildChangeSetUI->GetString(CGuildChangeSetUI::eEDIT_FAME_MAX));
	m_lbManageMemberListEx.SetString(3, tRow, strTmp);

#ifdef ENABLE_GUILD_STASH
	m_lbManageMemberList.SetString(6,tRow, m_pGuildChangeSetUI->GetStashUsable() ? _S(5560, "����") : _S(5561, "�Ұ�") );
#endif

	int nOldExp = atoi(m_lbManageMemberList.GetString( 4, tRow));
	int nExp = nOldExp;
	int nExpDonateMin = atoi(m_lbManageMemberListEx.GetString( 0, tRow));
	int nExpDonateMax = atoi(m_lbManageMemberListEx.GetString( 1, tRow));

	int nOldFame = atoi(m_lbManageMemberList.GetString( 5, tRow));
	int nFame = nOldFame;
	int nFameDonateMin = atoi(m_lbManageMemberListEx.GetString( 2, tRow));
	int nFameDonateMax = atoi(m_lbManageMemberListEx.GetString( 3, tRow));

	if (nExp > nExpDonateMax)
		nExp = nExpDonateMax;
	else if (nExp < nExpDonateMin)
		nExp = nExpDonateMin;

	if (nFame > nFameDonateMax)
		nFame = nFameDonateMax;
	else if (nFame < nFameDonateMin)
		nFame = nFameDonateMin;

	if (nOldExp != nExp)
	{
		strTmp.PrintF("%d%%", nExp);
		m_lbManageMemberList.SetString(4, tRow, strTmp);
	}

	if (nOldFame != nFame)
	{
		strTmp.PrintF("%d%%", nFame);
		m_lbManageMemberList.SetString(5, tRow, strTmp);
	}
}

void CUIGuild::AdjustDonateMinMaxInfo()
{
	if (m_pGuildDonateUI == NULL)
		return;

	int nSize = m_vManageMemberIndex.size();

	CTString strExpMin;
	strExpMin.PrintF("%s%%", m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_EXP_MIN));

	CTString strExpMax;
	strExpMax.PrintF("%s%%", m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_EXP_MAX));

	CTString strFameMin;
	strFameMin.PrintF("%s%%", m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_FAME_MIN));

	CTString strFameMax;
	strFameMax.PrintF("%s%%", m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_FAME_MAX));

	CTString strExp;
	strExp.PrintF("%s%%", m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_EXP));

	CTString strFame;
	strFame.PrintF("%s%%", m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_FAME));

	for (int i = 0; i < nSize; ++i)
	{		
		m_lbManageMemberListEx.SetString( 0, i, strExpMin);		
		m_lbManageMemberListEx.SetString( 1, i, strExpMax);		
		m_lbManageMemberListEx.SetString( 2, i, strFameMin);		
		m_lbManageMemberListEx.SetString( 3, i, strFameMax);		
		m_lbManageMemberList.SetString( 4, i, strExp);		
		m_lbManageMemberList.SetString( 5, i, strFame);
	}	
}

void CUIGuild::AdjustMyDonateInfo()
{
	if (m_pGuildDonateUI == NULL)
		return;

	int nSize = m_vectorMemberList.size();
	int nMyCharPosInMemberList = -1;

	for (int i = 0; i < nSize; ++i)
	{
		if (m_vectorMemberList[i].lIndex == _pNetwork->MyCharacterInfo.index )
		{
			nMyCharPosInMemberList = i;
			break;
		}
	}

	if (nMyCharPosInMemberList < 0 || nMyCharPosInMemberList >= nSize)
		return;

	CTString strTemp;

	strTemp.PrintF("%s%%", m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_EXP));

	if (m_lbManageMemberList.GetCurItemCount(4) > nMyCharPosInMemberList)
		m_lbManageMemberList.SetString( 4, nMyCharPosInMemberList, strTemp);

	strTemp.PrintF("%s%%", m_pGuildDonateUI->GetString(CGuildDonateUI::eEDIT_FAME));
	
	if (m_lbManageMemberList.GetCurItemCount(5) > nMyCharPosInMemberList)
		m_lbManageMemberList.SetString( 5, nMyCharPosInMemberList, strTemp);
}

void CUIGuild::SetGuildSkillList()
{
	// Set Skill List
	if( m_vecGuildPassiveSkill.size() > 0 )
		return;	

	INDEX tCnt = _pNetwork->ga_World.wo_aSkillData.Count();							
	INDEX tCnt2 = 0;
	INDEX tCnt3 = 0;
	INDEX tLoop = 0;

	// Check Guild Skill Count
	for( tLoop=0;tLoop<=tCnt;tLoop++)
	{
		CSkill &rSkillData = _pNetwork->GetSkillData(tLoop);
		if( rSkillData.GetType() == CSkill::ST_GUILD_SKILL_PASSIVE || ( rSkillData.GetFlag()&SF_GUILD && rSkillData.GetType() == CSkill::ST_PASSIVE ) )
		{										
			m_vecGuildPassiveSkill.push_back(rSkillData);
			tCnt2++;
		}
		else if ( rSkillData.GetFlag()&SF_GUILD && ( rSkillData.GetType() != CSkill::ST_GUILD_SKILL_PASSIVE || rSkillData.GetType() != CSkill::ST_PASSIVE ) )
		{
			m_vecGuildActiveSkill.push_back(rSkillData);
			tCnt3++;
		}
	}
}

void CUIGuild::GetBoardListContent()
{	
	if(m_lbListContent.GetCurItemCount(0)>0)
	{
		if( m_lbListContent.GetString(0,0) == pWEB->m_lbListContent.GetString(0,0) ) return;
	}

	int tColCnt = pWEB->m_lbListContent.GetColumnCount();
	int tItemCnt = pWEB->m_lbListContent.GetCurItemCount(0);
	m_lbListContent.ResetAllStrings();
	for(int j=0;j<tItemCnt;j++)
	{	
		for(int i=0;i<tColCnt;i++)
		{
			m_lbListContent.AddString(i,pWEB->m_lbListContent.GetString(i,j));
		}	
	}
}

void CUIGuild::GetBoardReadContent()
{	
	if(m_lbReadContent.GetCurItemCount(0)>0)
	{
		if( m_lbReadContent.GetString(0,0) == pWEB->m_lbReadContent.GetString(0,0) ) return;
	}
	m_lbReadContent.ResetAllStrings();	
	for(int i=0;i<pWEB->m_lbReadContent.GetCurItemCount(0);i++)
	{
		m_lbReadContent.AddString(0,pWEB->m_lbReadContent.GetString(0,i));
	}		
	
}

int CUIGuild::GetGuildSkillLevel(int skillIdx)
{
	CSkill& SkillData = _pNetwork->GetSkillData( skillIdx );
	if( SkillData.GetType() == CSkill::ST_GUILD_SKILL_PASSIVE || ( SkillData.GetFlag()&SF_GUILD && SkillData.GetType() == CSkill::ST_PASSIVE ) )
	{
		for(int i=0;i<m_vecGuildPassiveSkill.size();i++)
		{
			if(m_vecGuildPassiveSkill[i].GetIndex() == skillIdx)	
			{
				return m_vecGuildPassiveSkill[i].GetCurLevel();
			}
		}
	}
	else if ( SkillData.GetFlag()&SF_GUILD && ( SkillData.GetType() != CSkill::ST_GUILD_SKILL_PASSIVE || SkillData.GetType() != CSkill::ST_PASSIVE ) )
	{
		for (int i=0 ; i<m_vecGuildActiveSkill.size(); ++i)
		{
			if ( m_vecGuildActiveSkill[i].GetIndex() == skillIdx )
			{
				return m_vecGuildActiveSkill[i].GetCurLevel();
			}
		}
	}
	return 0;
}

CTString CUIGuild::SetPosName(CTString tName)
{
	if( tName.Length() )
	{
		return tName;
	}
	else 
	{
		// TODO : ������ �̸��� ������ ����Ʈ �������� �ٿ� �ش�. 
		return tName;		
	}

}

void CUIGuild::ResetGuildMaxMember(int guildSkillLevel)
{
	// WSS_NEW_GUILD_SYSTEM 070704	
	for(int i= 7;i<MAX_GUILD_LEVEL;i++)
	{
		// �ʿ䳪��/sp/gp = 7�������� �ʿ䷮ * (1.09^(���LV - 7))
		if (guildSkillLevel < 6)
		{// ��� ��ų ������ 6���� �̸��̸� +5�� �ִ� ��� ����
			_GuildConditionTable[i].iMaxMember = _GuildConditionTable[6].iMaxMember + 5*guildSkillLevel;
		}
		else
		{// ��� ��ų ������ 6���� �̻��̸� +9�� �ִ� ��� ����
			const int tmpGuildMember = 55;
			_GuildConditionTable[i].iMaxMember = tmpGuildMember + (9*(guildSkillLevel-5));
		}
	}		
}

CTString CUIGuild::ResetPosName(CTString tPosName,int ulPosition)
{
	if( tPosName.Length() == 0 )
	{
		return m_strCorps[ulPosition];
	}
	return tPosName;
}

BOOL CUIGuild::IsEditBoxFocused() 
{
	return (m_ebGuildName.IsFocused() ||
	m_ebSearch.IsFocused() ||
	m_cmbSearch.IsFocused() ||
	m_ebWriteSubject.IsFocused() ||
	m_mebContent.IsFocused() ||
	m_ebNoticeTitle.IsFocused() ||
	m_mebNoticeContent.IsFocused() ||
	(m_pGuildChangeSetUI && m_pGuildChangeSetUI->IsFocusedComboBox()) ||
	(m_pGuildChangeSetUI && m_pGuildChangeSetUI->IsFocused()) ||
	(m_pGuildDonateUI && m_pGuildDonateUI->IsFocused()));	
}

void CUIGuild::KillFocusEditBox() 
{ 
	m_ebGuildName.SetFocus( FALSE );
	m_ebSearch.SetFocus( FALSE );
	m_cmbSearch.SetFocus( FALSE );
	m_ebWriteSubject.SetFocus( FALSE );
	m_mebContent.SetFocus( FALSE );
	m_ebNoticeTitle.SetFocus( FALSE );
	m_mebNoticeContent.SetFocus( FALSE );
	m_pGuildChangeSetUI->SetFocusComboBox( FALSE );

	if (m_pGuildChangeSetUI != NULL)
		m_pGuildChangeSetUI->KillFocusEditBox();

	if (m_pGuildDonateUI != NULL)
		m_pGuildDonateUI->KillFocusEditBox();
}

// ----------------------------------------------------------------------------
// Name : RenderNewGuildSkillExtend()
// Desc : ��� ��ų Ȯ��â �׸���
// ----------------------------------------------------------------------------
void CUIGuild::RenderNewGuildSkillExtend(int nX,int nY)
{
	int tInc = 33;
	int tCab = 7;
	int nY2 = nY + 70;
	
	// Box 2 (Black)
	m_bxBox2.SetBoxPos(WRect(nX+36,nY+59,nX+250,nY+277));
	m_bxBox2.Render();	
	m_bxBox2.SetBoxPos(WRect(nX+270,nY+59,nX+577,nY+153));
	m_bxBox2.Render();	
	m_bxBox2.SetBoxPos(WRect(nX+270,nY+160,nX+419,nY+250));
	m_bxBox2.Render();	
	m_bxBox2.SetBoxPos(WRect(nX+427,nY+160,nX+577,nY+250));
	m_bxBox2.Render();	

	// Box 1 (Grey)
	m_bxBox1.SetBoxPos(WRect(nX+46,nY2 ,nX+240,(nY2+tInc)));
	m_bxBox1.Render();
	m_bxBox1.SetBoxPos(WRect(nX+47,nY2 ,nX+81,(nY2+tInc)));
	m_bxBox1.Render();
	nY2+=tInc+tCab;
	m_bxBox1.SetBoxPos(WRect(nX+46,nY2,nX+240,(nY2+tInc)));
	m_bxBox1.Render();	
	m_bxBox1.SetBoxPos(WRect(nX+47,nY2,nX+81,(nY2+tInc)));
	m_bxBox1.Render();	
	nY2+=tInc+tCab;
	m_bxBox1.SetBoxPos(WRect(nX+46,nY2,nX+240,(nY2+tInc)));
	m_bxBox1.Render();	
	m_bxBox1.SetBoxPos(WRect(nX+47,nY2,nX+81,(nY2+tInc)));
	m_bxBox1.Render();	
	nY2+=tInc+tCab;
	m_bxBox1.SetBoxPos(WRect(nX+46,nY2,nX+240,(nY2+tInc)));
	m_bxBox1.Render();	
	m_bxBox1.SetBoxPos(WRect(nX+47,nY2,nX+81,(nY2+tInc)));
	m_bxBox1.Render();	
	nY2+=tInc+tCab;
	m_bxBox1.SetBoxPos(WRect(nX+46,nY2,nX+240,(nY2+tInc)));
	m_bxBox1.Render();	
	m_bxBox1.SetBoxPos(WRect(nX+47,nY2,nX+81,(nY2+tInc)));
	m_bxBox1.Render();	
	m_bxBox1.SetBoxPos(WRect(nX+270,nY+77,nX+577,nY+153));
	m_bxBox1.Render();	

	m_bxBox1.SetBoxPos(WRect(nX+270,nY+178,nX+419,nY+250));
	m_bxBox1.Render();
	m_bxBox1.SetBoxPos(WRect(nX+427,nY+178,nX+577,nY+250));
	m_bxBox1.Render();

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	pDrawPort->FlushRenderingQueue();

	// Guild Skill List ----------------------------------------------------->>
	int iListCnt = GetGuildSkillCount();

	// Left Guild Skill List		
	int iRowS = m_sbGuildSkillBar.GetScrollPos();
	int iRowE = iRowS + GUILD_SKILL_SLOT_ROW;
	CTString tStr;
	iRowE = (iRowE>iListCnt)? iListCnt:iRowE;
	nY2 = 0;

	int nSkillCnt = GetGuildSkillCount();
	int nLoopCnt  = (nSkillCnt > GUILD_SKILL_VIEW_MAX)? GUILD_SKILL_VIEW_MAX : nSkillCnt;
	//SetSkillBtnInfo();
	for ( int i=0; i<nLoopCnt; ++i )
	{
		// Skill Button Render
		m_pIconsGuildSkillEx[i]->Render(pDrawPort);

		// Skill Info Render
		int nNum, tLv, nMaxLevel;
		CTString strSkillName;
		CSkill SkillData;

		nNum = m_sbGuildSkillBar.GetScrollPos() + i;
		if ( m_nSelSkillTab == GUILD_SKILL_PASSIVE )
		{
			SkillData = m_vecGuildPassiveSkill[nNum];
		}
		else
		{
			SkillData = m_vecGuildActiveSkill[nNum];
		}

		tLv = SkillData.GetCurLevel();
		nMaxLevel = SkillData.GetMaxLevel();
		strSkillName = SkillData.GetName();
		tStr.PrintF( "%s Lv%d/Lv%d", strSkillName, tLv, nMaxLevel );
		pDrawPort->PutTextEx( tStr, nX + 91 , nY +nY2+80,C_lYELLOW|CT_AMASK);
		nY2 += GUILD_SKILL_SLOT_OFFSETY;
	}
	if ( m_bIsSelList )
	{
		CTString strName = GetGuildSkill(m_iGuildSkillPos)->GetName();
		pDrawPort->PutTextEx( strName, nX + 277, nY + 63, C_lYELLOW|CT_AMASK);
	}
	pDrawPort->PutTextEx( _S(5026, "�������"), nX + 277, nY + 163, C_lYELLOW|CT_AMASK);
	pDrawPort->PutTextEx( _S(5027, "��������"), nX + 434, nY + 163, C_lYELLOW|CT_AMASK);
	// Flush Skill Button Rendering Queue
	pDrawPort->FlushBtnRenderingQueue( UBET_SKILL );
	
	pDrawPort->InitTextureData(m_ptdBaseTexture);

	if(m_bIsSelList)
	{	
		m_lbGuildSkillDesc.Render();	
		m_lbLearnInfo.Render();
		if ( m_nSelSkillTab	== GUILD_SKILL_ACTIVE)
		{	// ��Ƽ�� �� �϶��� ��� ���� ǥ��
			m_lbUseInfo.Render();
		}
	}	
	// Button
	if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS)
	{
		m_btnGetSkill.SetEnable(TRUE);
	}
	else
	{
		m_btnGetSkill.SetEnable(FALSE);
	}

	if ( m_nSelSkillTab	== GUILD_SKILL_ACTIVE)
	{
		CSkill& rSkill = m_vecGuildActiveSkill[m_iGuildSkillPos];
		if( rSkill.GetCurLevel() > 0 &&
			(rSkill.GetTargetType() == CSkill::STT_GUILD_MEMBER_SELF ||
			_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS))
		{	
			m_btnUseSkill.SetEnable(TRUE);	
		}
		else
		{
			m_btnUseSkill.SetEnable(FALSE);	
		}
	}
	else 
	{
		m_btnUseSkill.SetEnable(FALSE);
	}
	m_btnGetSkill.Render();
	m_btnUseSkill.Render();
	// ScrollBar
	m_sbGuildSkillBar.Render();
	// Render all elements
	pDrawPort->FlushRenderingQueue();
	
	// Render Selected Guild Skill
	pDrawPort->InitTextureData(m_ptdSelBoxTexture);
	UIRectUV rcPassiveTab	= m_rtSelSideTabUV;
	UIRectUV rcActiveTab	= m_rtUnSelSideTabUV;
	UIRectUV rcPassiveImage = m_rtPassiveTabIconUV[0];
	UIRectUV rcActiveImage	= m_rtActiveTabIconUV[1];
	
	if ( m_nSelSkillTab == GUILD_SKILL_ACTIVE )
	{
		rcPassiveTab	= m_rtUnSelSideTabUV;
		rcActiveTab		= m_rtSelSideTabUV;
		rcPassiveImage	= m_rtPassiveTabIconUV[1];
		rcActiveImage	= m_rtActiveTabIconUV[0];
	}
	pDrawPort->AddTexture( nX + m_rcSkillTab[GUILD_SKILL_PASSIVE].Left, nY + m_rcSkillTab[GUILD_SKILL_PASSIVE].Top, 
		nX + m_rcSkillTab[GUILD_SKILL_PASSIVE].Right, nY + m_rcSkillTab[GUILD_SKILL_PASSIVE].Bottom, 
		rcPassiveTab.U0, rcPassiveTab.V0, rcPassiveTab.U1, rcPassiveTab.V1, 0xFFFFFFFF);
	pDrawPort->AddTexture( nX + m_rcSkillTab[GUILD_SKILL_ACTIVE].Left, nY + m_rcSkillTab[GUILD_SKILL_ACTIVE].Top, 
		nX + m_rcSkillTab[GUILD_SKILL_ACTIVE].Right, nY + m_rcSkillTab[GUILD_SKILL_ACTIVE].Bottom, 
		rcActiveTab.U0, rcActiveTab.V0, rcActiveTab.U1, rcActiveTab.V1, 0xFFFFFFFF);
	pDrawPort->AddTexture( nX + m_rcSkillTab[GUILD_SKILL_PASSIVE].Left+6 , nY + m_rcSkillTab[GUILD_SKILL_PASSIVE].Top+34, 
		nX + m_rcSkillTab[GUILD_SKILL_PASSIVE].Left+20, nY + m_rcSkillTab[GUILD_SKILL_PASSIVE].Top+48, 
		rcPassiveImage.U0, rcPassiveImage.V0, rcPassiveImage.U1, rcPassiveImage.V1, 0xFFFFFFFF);
	pDrawPort->AddTexture( nX + m_rcSkillTab[GUILD_SKILL_ACTIVE].Left+6, nY + m_rcSkillTab[GUILD_SKILL_ACTIVE].Top+34, 
		nX + m_rcSkillTab[GUILD_SKILL_ACTIVE].Left+20, nY + m_rcSkillTab[GUILD_SKILL_ACTIVE].Top+48,
		rcActiveImage.U0, rcActiveImage.V0, rcActiveImage.U1, rcActiveImage.V1, 0xFFFFFFFF);

	if ( m_strSkillTabPopupInfo != CTString("") )
	{
		pDrawPort->AddTexture( nX + m_rcSkillTabPopupInfo.Left, nY + m_rcSkillTabPopupInfo.Top,
			nX + m_rcSkillTabPopupInfo.Left + 8, nY + m_rcSkillTabPopupInfo.Top + 8,
			m_rtPopupUL.U0, m_rtPopupUL.V0, m_rtPopupUL.U1, m_rtPopupUL.V1,
			0xFFFFFFBB );
		pDrawPort->AddTexture( nX + m_rcSkillTabPopupInfo.Left + 8, nY + m_rcSkillTabPopupInfo.Top,
			nX + m_rcSkillTabPopupInfo.Right - 8, nY + m_rcSkillTabPopupInfo.Top + 8,
			m_rtPopupUM.U0, m_rtPopupUM.V0, m_rtPopupUM.U1, m_rtPopupUM.V1,
			0xFFFFFFBB );
		pDrawPort->AddTexture( nX + m_rcSkillTabPopupInfo.Right - 8, nY + m_rcSkillTabPopupInfo.Top,
			nX + m_rcSkillTabPopupInfo.Right, nY + m_rcSkillTabPopupInfo.Top + 8,
			m_rtPopupUR.U0, m_rtPopupUR.V0, m_rtPopupUR.U1, m_rtPopupUR.V1,
			0xFFFFFFBB );
		pDrawPort->AddTexture( nX +m_rcSkillTabPopupInfo.Left, nY + m_rcSkillTabPopupInfo.Top + 8,
			nX + m_rcSkillTabPopupInfo.Left + 8, nY + m_rcSkillTabPopupInfo.Bottom - 8,
			m_rtPopupML.U0, m_rtPopupML.V0, m_rtPopupML.U1, m_rtPopupML.V1,
			0xFFFFFFBB );
		pDrawPort->AddTexture( nX + m_rcSkillTabPopupInfo.Left + 8, nY + m_rcSkillTabPopupInfo.Top + 8,
			nX + m_rcSkillTabPopupInfo.Right - 8, nY + m_rcSkillTabPopupInfo.Bottom - 8,
			m_rtPopupMM.U0, m_rtPopupMM.V0, m_rtPopupMM.U1, m_rtPopupMM.V1,
			0xFFFFFFBB );
		pDrawPort->AddTexture( nX + m_rcSkillTabPopupInfo.Right - 8, nY + m_rcSkillTabPopupInfo.Top + 8,
			nX + m_rcSkillTabPopupInfo.Right, nY + m_rcSkillTabPopupInfo.Bottom - 8,
			m_rtPopupMR.U0, m_rtPopupMR.V0, m_rtPopupMR.U1, m_rtPopupMR.V1,
			0xFFFFFFBB );
		pDrawPort->AddTexture( nX + m_rcSkillTabPopupInfo.Left, nY + m_rcSkillTabPopupInfo.Bottom - 8,
			nX + m_rcSkillTabPopupInfo.Left + 8, nY + m_rcSkillTabPopupInfo.Bottom,
			m_rtPopupLL.U0, m_rtPopupLL.V0, m_rtPopupLL.U1, m_rtPopupLL.V1,
			0xFFFFFFBB );
		pDrawPort->AddTexture( nX + m_rcSkillTabPopupInfo.Left + 8, nY + m_rcSkillTabPopupInfo.Bottom - 8,
			nX + m_rcSkillTabPopupInfo.Right - 8, nY + m_rcSkillTabPopupInfo.Bottom,
			m_rtPopupLM.U0, m_rtPopupLM.V0, m_rtPopupLM.U1, m_rtPopupLM.V1,
			0xFFFFFFBB );
		pDrawPort->AddTexture( nX + m_rcSkillTabPopupInfo.Right - 8, nY + m_rcSkillTabPopupInfo.Bottom - 8,
			nX + m_rcSkillTabPopupInfo.Right, nY + m_rcSkillTabPopupInfo.Bottom,
			m_rtPopupLR.U0, m_rtPopupLR.V0, m_rtPopupLR.U1, m_rtPopupLR.V1,
			0xFFFFFFBB );		

		int nPosX, nPosY;
		
		nPosX = m_rcSkillTabPopupInfo.Left + 10;
		nPosY = (m_rcSkillTabPopupInfo.GetHeight() - _pUIFontTexMgr->GetFontHeight()) /2 + m_rcSkillTabPopupInfo.Top;
		pDrawPort->PutTextEx( m_strSkillTabPopupInfo, nX + nPosX, nY + nPosY, 0xF2F2F2FF );
	}
	if( m_bIsSelList )
	{	// ���õȰ� ������ �׸���.
		int nSelPos = m_iGuildSkillPos - m_sbGuildSkillBar.GetScrollPos();
		if ( nSelPos >=0 && nSelPos < 5)
		{
			pDrawPort->AddTexture( nX + m_rcSkillBtn[nSelPos].Left, nY + m_rcSkillBtn[nSelPos].Top, nX + m_rcSkillBtn[nSelPos].Right, 
				nY + m_rcSkillBtn[nSelPos].Bottom, m_rtSelBoxUV.U0, m_rtSelBoxUV.V0, m_rtSelBoxUV.U1, m_rtSelBoxUV.V1, 0xFFFFFFFF);		
		}
	}	
}

// ----------------------------------------------------------------------------
// Name : GetGuildSkill()
// Desc : 
// ----------------------------------------------------------------------------
CSkill* CUIGuild::GetGuildSkill(int nPos)
{
	if ( m_nSelSkillTab == GUILD_SKILL_PASSIVE )
	{
		return &m_vecGuildPassiveSkill[nPos];
	}
	else
	{
		return &m_vecGuildActiveSkill[nPos];
	}
}

// ----------------------------------------------------------------------------
// Name : SetGuildSkillInfo()
// Desc : ��� ��ų ���� ���� : ��� ����/���� ����
// ----------------------------------------------------------------------------
void CUIGuild::SetGuildSkillInfo()
{
	int		i;
	m_lbUseInfo.ResetAllStrings();
	m_lbLearnInfo.ResetAllStrings();
	CSkill* pSkill = GetGuildSkill(m_iGuildSkillPos);
	CTString strMessage;
	CTString strSkillName;
	CTString strTemp;
	CTString strCount;

	if (pSkill == NULL)
		return;
	// ------------------------------------------------------------------
	// ��� ���� 
	int nCurSkillLevel = pSkill->GetCurLevel();
	int nMaxSkillLevel	= pSkill->GetMaxLevel();

	COLOR colUseSkillInfo;
	COLOR colLearnSkillInfo;
	colUseSkillInfo	  = 0x00ffffff;
	colLearnSkillInfo = 0x99ff33ff;

	if ( nCurSkillLevel > 0)
	{	// ��� ��ų�� ���� ���� ��� ���� ǥ��
		int nSkillLevel = nCurSkillLevel-1; // ������

		int nNeedGP		= pSkill->GetNeedGP(nSkillLevel);				// �Ҹ� GP
		int nNeedItemIndex1 = pSkill->GetNeedItemIndex1(nSkillLevel);	// �Ҹ� ������1
		int nNeedItemIndex2 = pSkill->GetNeedItemIndex2(nSkillLevel);	// �Ҹ� ������2
		int nNeedItemCount1	= pSkill->GetNeedItemCount1(nSkillLevel);	// �Ҹ� ������1�� ����
		int nNeedItemCount2	= pSkill->GetNeedItemCount2(nSkillLevel);	// �Ҹ� ������2�� ����
		int nPower		= pSkill->GetPower(nSkillLevel);					// ����
		float nRange	= pSkill->GetAppRange();								// ��ȿ �Ÿ�
		int nDurTime	= pSkill->GetDurTime(nSkillLevel)/10;			// ���� �ð�
		int nReuseTime	= pSkill->GetReUseTime()/10;							// ���� �ð�

		CUIManager* pUIManager = CUIManager::getSingleton();

		// Current Skill Level
		strMessage.PrintF( _S ( 5120, "���� ��ų ���� : %d" ), nCurSkillLevel);
		pUIManager->AddStringToList(&m_lbUseInfo, strMessage, 20, colUseSkillInfo);

		if ( nNeedGP > 0 )
		{	// Need GP
			strTemp.PrintF("%d", nNeedGP);
			pUIManager->InsertCommaToString(strTemp);
			strMessage.PrintF( _S( 5032, "�Ҹ� GP : %s" ), strTemp);
			pUIManager->AddStringToList(&m_lbUseInfo, strMessage, 20, colUseSkillInfo);
		}
		if ( nNeedItemIndex1 > 0 || nNeedItemIndex2 > 0 )
		{
			strMessage.PrintF( _S( 259, "�ʿ� ������" ));
			pUIManager->AddStringToList(&m_lbUseInfo, strMessage, 20, colUseSkillInfo);
			if ( nNeedItemIndex1 > 0)
			{	// Need Item1
				strCount = pUIManager->IntegerToCommaString(nNeedItemCount1);
				strMessage.PrintF( _S( 260, "  %s %s��" ), _pNetwork->GetItemName(nNeedItemIndex1), strCount );
				pUIManager->AddStringToList(&m_lbUseInfo, strMessage, 20, colUseSkillInfo);
			}
			if ( nNeedItemIndex2 > 0)
			{	// Need Item2
				strCount = pUIManager->IntegerToCommaString(nNeedItemCount2);
				strMessage.PrintF( _S( 260, "  %s %s��" ), _pNetwork->GetItemName(nNeedItemIndex1), strCount );
				pUIManager->AddStringToList(&m_lbUseInfo, strMessage, 20, colUseSkillInfo);
			}
		}
		if ( nPower > 0 )
		{	// Skill Power
			strMessage.PrintF( _S( 65, "���� : %d" ), nPower );
			pUIManager->AddStringToList(&m_lbUseInfo, strMessage, 20, colUseSkillInfo);
		}
		if ( nRange > 0 )
		{	// Skill Range
			strMessage.PrintF( _S( 66, "��ȿ �Ÿ� : %.1f" ), nRange );
			pUIManager->AddStringToList(&m_lbUseInfo, strMessage, 20, colUseSkillInfo);
		}
		if ( nDurTime > 0 )
		{	// Skill Time
			strMessage.PrintF( _S( 4172, "���ӽð� : %d��" ), nDurTime );
			pUIManager->AddStringToList(&m_lbUseInfo, strMessage, 20, colUseSkillInfo);
		}
		if ( nReuseTime > 0 )
		{	// Skill ReUsed Time
			strMessage.PrintF( _S( 4173, "���� �ð� : %d��" ), nReuseTime);
			pUIManager->AddStringToList(&m_lbUseInfo, strMessage, 20, colUseSkillInfo);
		}
		// Skill Target Type
		char nTargetType = pSkill->GetTargetType();
		if ( nTargetType == CSkill::STT_GUILD_ALL )
		{	// Skill Target Type : GUILD ALL
			strMessage.PrintF( _S( 5121, "Ÿ�ٴ�� : ���� ��ü" ));
			pUIManager->AddStringToList(&m_lbUseInfo, strMessage, 20, colUseSkillInfo);
		}	
		else if ( nTargetType == CSkill::STT_GUILD_ONE )
		{	// Skill Target Type : GUILD ONE
			strMessage.PrintF( _S( 5122, "Ÿ�ٴ�� : ���� �Ѹ�" ));
			pUIManager->AddStringToList(&m_lbUseInfo, strMessage, 20, colUseSkillInfo);
		}
		else if ( nTargetType == CSkill::STT_GUILD_SELF_RANGE )
		{	// Skill Target Type : GUILD SELF RANGE
			strMessage.PrintF( _S ( 5123, "Ÿ�ٴ�� : �ֺ� ��" ));
			pUIManager->AddStringToList(&m_lbUseInfo, strMessage, 20, colUseSkillInfo);
		}
	}

	// ------------------------------------------------------------------
	// ���� ����
	if ( nCurSkillLevel < nMaxSkillLevel )
	{	// ���� ���� ���� ����
		int nNextSkilllevel = nCurSkillLevel;	// ���� ���� ������
		
		int nLearnLevel = pSkill->GetLearnLevel(nNextSkilllevel);	// ��ų ���� ��, �ʿ� ����
		int nLearnGP	= pSkill->GetLearnGP(nNextSkilllevel);		// ��ų ���� ��, �ʿ� GP
		int nLearnStr	= pSkill->GetLearnStr(nNextSkilllevel);		// ��ų ���� ��, �ʿ� ��
		int nLearnDex	= pSkill->GetLearnDex(nNextSkilllevel);		// ��ų ���� ��, �ʿ� ��ø
		int nLearnInt	= pSkill->GetLearnInt(nNextSkilllevel);		// ��ų ���� ��, �ʿ� ����
		int nLearnCon	= pSkill->GetLearnCon(nNextSkilllevel);		// ��ų ���� ��, �ʿ� ü��
		int nNeedGP		= pSkill->GetNeedGP(nNextSkilllevel);		// ��ų ��� ��, �ʿ� GP
		int nPower		= pSkill->GetPower(nNextSkilllevel);		// ��ų ����
		float nRange	= pSkill->GetAppRange();						// ��ų ��ȿ �Ÿ�
		int nDurTime	= pSkill->GetDurTime(nNextSkilllevel)/10;	// ��ų ���� �ð�
		int nReuseTime	= pSkill->GetReUseTime()/10;					// ��ų ���� �ð�
		int nLearnItemIndex[3], nLearnItemCount[3], nLearnSkillIndex[3], nLearnSkillLevel[3];
		for ( i = 0; i < 3; ++i )
		{
			nLearnItemIndex[i]	= pSkill->GetLearnItemIndex(nNextSkilllevel, i);	// ��ų ���� ��, �ʿ� ������
			nLearnItemCount[i]	= pSkill->GetLearnItemCount(nNextSkilllevel, i);	// ��ų ���� ��, �ʿ� ������ ����
			nLearnSkillIndex[i]	= pSkill->GetLearnSkillIndex(nNextSkilllevel, i);	// ��ų ���� ��, �ʿ� ��ų
			nLearnSkillLevel[i]	= pSkill->GetLearnSkillLevel(nNextSkilllevel, i);	// ��ų ���� ��, �ʿ� ��ų ����
		}

		CUIManager* pUIManager = CUIManager::getSingleton();

		// Next Skill Level
		strMessage.PrintF( _S( 5118, "���� ��ų ���� : %d" ), nNextSkilllevel+1 );
		pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);

		if ( nLearnLevel > 0 )
		{	// Learn Level
			strMessage.PrintF( _S( 256, "�ʿ� ���� : %d" ), nLearnLevel);
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
		if ( nLearnGP > 0 )
		{	// Learn GP
			strTemp.PrintF("%d", nLearnGP);
			pUIManager->InsertCommaToString(strTemp);
			strMessage.PrintF( _S( 5119, "�ʿ� GP : %s" ), strTemp);
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}

		for ( i = 0; i < 3; ++i )
		{	// Learn Item
			if ( nLearnItemIndex[i] > 0 )
			{
				strCount = pUIManager->IntegerToCommaString(nLearnItemCount[i]);
				strMessage.PrintF( _S( 260, "  %s %s��" ), _pNetwork->GetItemName( nLearnItemIndex[i] ), strCount );
				strMessage = _S( 259, "�ʿ� ������" ) + strMessage;
				pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
			}
		}
		if ( nLearnStr > 0 )
		{	// Learn STR
			strMessage.PrintF( _S( 1391, "�ʿ� �� : %d" ), nLearnStr);
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
		if ( nLearnDex > 0 )
		{	// Learn DEX
			strMessage.PrintF( _S( 1392, "�ʿ� ��ø : %d" ), nLearnDex);
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
		if ( nLearnInt > 0 )
		{	// Learn INT
			strMessage.PrintF( _S( 1393, "�ʿ� ���� : %d" ), nLearnInt);
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
		if ( nLearnCon > 0 )
		{	// Learn CON
			strMessage.PrintF( _S( 1394, "�ʿ� ü�� : %d" ), nLearnCon);
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
		for ( i = 0; i < 3; ++i )
		{	// Learn Skill
			if ( nLearnSkillIndex[i] > 0 )
			{
				strMessage.PrintF( " : %s Lv.%d", _pNetwork->GetSkillData(nLearnSkillIndex[i]).GetName(), nLearnSkillLevel[i] );
				strMessage = _S( 258, "�ʿ� ��ų" ) + strMessage;
				pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
			}
		}
		if ( nNeedGP > 0 )
		{	// Need GP
			strTemp.PrintF("%d", nNeedGP);
			pUIManager->InsertCommaToString(strTemp);
			strMessage.PrintF( _S( 5032, "�Ҹ� GP : %s" ), strTemp);
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
		if ( nPower > 0 )
		{	// Skill Power
			strMessage.PrintF( _S( 65, "���� : %d" ), nPower );
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
		if ( nRange > 0 )
		{	// Skill Range
			strMessage.PrintF( _S( 66, "��ȿ �Ÿ� : %.1f" ), nRange );
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
		if ( nDurTime > 0 )
		{	// Skill Time
			strMessage.PrintF( _S( 4172, "���ӽð� : %d��" ), nDurTime);
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
		if ( nReuseTime > 0 )
		{	// ReUse Time
			strMessage.PrintF( _S( 4173, "���� �ð� : %d��" ), nReuseTime );
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
		// Skill Target Type
		char nTargetType = pSkill->GetTargetType();
		if ( nTargetType == CSkill::STT_GUILD_ALL )
		{
			strMessage.PrintF( _S( 5121, "Ÿ�ٴ�� : ���� ��ü" ));
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
		else if ( nTargetType == CSkill::STT_GUILD_ONE )
		{
			strMessage.PrintF( _S( 5122, "Ÿ�ٴ�� : ���� �Ѹ�" ));
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
		else if ( nTargetType == CSkill::STT_GUILD_SELF_RANGE )
		{
			strMessage.PrintF( _S ( 5123, "Ÿ�ٴ�� : �ֺ� ��" ));
			pUIManager->AddStringToList(&m_lbLearnInfo, strMessage, 20, colLearnSkillInfo);
		}
	}
}

// ----------------------------------------------------------------------------
// Name : ReceiveGuildSkillExtend()
// Desc : ��� ��ų ���� �ޱ�
// ----------------------------------------------------------------------------
void CUIGuild::ReceiveGuildSkillExtend(CNetworkMessage* istr)
{
	SetGuildSkillList();

	INDEX iSkillType, iCount, iSkillIndex, iSkillLevel, iLoopCnt, iCoolTime;
	// Active Guild Skill
	(*istr) >> iSkillType;
	if ( iSkillType == GUILD_ACTIVE_SKILL_START )
	{	// Active Guild Skill
		(*istr) >> iCount;
		if ( iCount == 0)
		{
			for(int i=0; i<m_vecGuildActiveSkill.size(); ++i)
			{
				m_vecGuildActiveSkill[i].SetCurLevel(0);
			}
		}
		else
		{
			for (iLoopCnt=0; iLoopCnt<iCount; ++iLoopCnt)
			{
				(*istr) >> iSkillIndex
						>> iSkillLevel
						>> iCoolTime;

				MY_INFO()->SetSkill(iSkillIndex, iSkillLevel);

				for(int j=0; j<m_vecGuildActiveSkill.size(); ++j)
				{
					if( m_vecGuildActiveSkill[j].GetIndex() == iSkillIndex )
					{
						m_vecGuildActiveSkill[j].SetCurLevel(iSkillLevel);
						
						if (iCoolTime > 0)
						{
							SLONG slRemainTime = ((SLONG)time(NULL) - _pNetwork->slServerTimeGap) - iCoolTime;
							CSkill &SkillData = _pNetwork->GetSkillData( iSkillIndex );
							SkillData.SetStartTime(slRemainTime);
							m_vecGuildActiveSkill[j].SetStartTime(slRemainTime);
						}
						break;
					}
				}
			}
		}
	}
	// Passive Guild Skill
	(*istr) >> iSkillType;
	if ( iSkillType == GUILD_PASSIVE_SKILL_START )
	{	// Passive Guild Skill
		(*istr) >> iCount;
		if ( iCount == 0)
		{
			for(int i=0; i<m_vecGuildPassiveSkill.size(); ++i)
			{
				m_vecGuildPassiveSkill[i].SetCurLevel(0);
			}
		}
		else
		{
			for (iLoopCnt=0; iLoopCnt<iCount; ++iLoopCnt)
			{
				(*istr) >> iSkillIndex
						>> iSkillLevel;

				MY_INFO()->SetSkill(iSkillIndex, iSkillLevel);

				for(int j=0; j<m_vecGuildPassiveSkill.size(); ++j)
				{
					if( m_vecGuildPassiveSkill[j].GetIndex() == iSkillIndex )
					{
						m_vecGuildPassiveSkill[j].SetCurLevel(iSkillLevel);
						break;
					}
				}
			}
		}
	}
	// Etc Guild Skill : Nothing (��� Active/Passive�� ó��)
	(*istr) >> iSkillType;
	if ( iSkillType == GUILD_ETC_SKILL_START )
	{	// Passive Guild Skill
		(*istr) >> iCount;
		for (iLoopCnt=0; iLoopCnt<iCount; ++iLoopCnt)
		{
			(*istr) >> iSkillIndex
					>> iSkillLevel;
			// Nothing : ��� Active/Passive�� ó��
			MY_INFO()->SetSkill(iSkillIndex, iSkillLevel);
		}
	}

	SetSkillBtnInfo();
}

// ----------------------------------------------------------------------------
// Name : GetSkillButton()
// Desc : ��� ��ų ��ư ���
// ----------------------------------------------------------------------------
CUIIcon* CUIGuild::GetSkillButton(int nPos)
{
	return m_pIconsGuildSkillEx[nPos - m_sbGuildSkillBar.GetScrollPos()];
}

// ----------------------------------------------------------------------------
// Name : GetGuildSkillCount(eGUILDSKILL SkillType)
// Desc : ��� ��ų �� ���� ���
// ----------------------------------------------------------------------------
int CUIGuild::GetGuildSkillCount()
{
	if ( m_nSelSkillTab == GUILD_SKILL_PASSIVE )
	{
		return m_vecGuildPassiveSkill.size();
	}
	else
	{
		return m_vecGuildActiveSkill.size();
	}
}

// ----------------------------------------------------------------------------
// Name : CheckUseGuildSkill()
// Desc : ��� ��ų ��� ���� üũ
// ----------------------------------------------------------------------------
BOOL CUIGuild::CheckUseGuildSkill(int nSkillIndex)
{
	SBYTE sbSkillLevel = GetGuildSkillLevel(nSkillIndex);

	CSkill skill = _pNetwork->GetSkillData(nSkillIndex);
	int nNeedGP = skill.GetNeedGP(sbSkillLevel-1);	
	char nTargetType = skill.GetTargetType();

	CUIManager* pUIMgr = UIMGR();
	CChattingUI* pChat = pUIMgr->GetChattingUI();

	if ( nTargetType != CSkill::STT_GUILD_MEMBER_SELF)
	{
		// ���� ���ΰ� ��밡���� Ÿ���� �ƴҰ��� �渶�� ��츸 ��ų ��� 
		if ( _pNetwork->MyCharacterInfo.lGuildPosition != GUILD_MEMBER_BOSS )
		{
			if (pChat)
				pChat->AddSysMessage( _S(5029, "��� �����͸� ��ų ����� �����մϴ�."));

			return FALSE;
		}
	}

	if ( _pNetwork->MyCharacterInfo.iGP < nNeedGP )
	{	// ���� GP�� �Ҹ� GP���� ũ�� ��ų ���
		if (pChat)
			pChat->AddSysMessage( _S(5028, "GP�� �����Ͽ� ��ų�� ����� �� �����ϴ�."));

		return FALSE;
	}

	if (nSkillIndex == DEF_GUILD_RECALL_SKILL_IDX)
	{
		pUIMgr->CloseMessageBox( MSGCMD_GUILD_RECALL_USE_REQ );

		CTString	strMessage;
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILD_RECALL_USE_REQ );	
		strMessage.PrintF( _S( 6435, "�������� �������� ��ȯ�Ͻðڽ��ϱ�?" ) );
		MsgBoxInfo.AddString( strMessage );

		pUIMgr->CreateMessageBox( MsgBoxInfo );
		return FALSE;
	}
	
	return TRUE;
}

// ----------------------------------------------------------------------------
// Name : StartGuildSkillDelay()
// Desc : ��� ��ų ������ ����
// ----------------------------------------------------------------------------
BOOL CUIGuild::StartGuildSkillDelay( int nSkillIndex )
{
	int		i;
	BOOL bResult = FALSE;
	for( i = 0; i < GUILD_SKILL_VIEW_MAX; ++i )
	{
		if (m_pIconsGuildSkillEx[i]->getIndex() == nSkillIndex)
		{
			if (MY_INFO()->GetSkillDelay(nSkillIndex) == true)
			{
				m_pIconsGuildSkillEx[i]->setCooltime(true);
				bResult = TRUE;
			}
			else
			{
				continue;
			}
		}
	}
	for( i = 0; i < m_vecGuildActiveSkill.size(); ++i )
	{
		if ( m_vecGuildActiveSkill[i].GetIndex() == nSkillIndex )
		{
			m_vecGuildActiveSkill[i].Skill_Data.Skill_StartTime = _pNetwork->GetSkillData( nSkillIndex ).Skill_Data.Skill_StartTime;
		}
	}
	return bResult;
}

// ----------------------------------------------------------------------------
// Name : SetSkillPopupInfo()
// Desc : ��� ��ų �˾� ���� ����
// ----------------------------------------------------------------------------
void CUIGuild::SetSkillPopupInfo(int nTab)
{
	if ( nTab == GUILD_SKILL_PASSIVE )
	{
		m_strSkillTabPopupInfo = _S(67, "�нú� ��ų");
	}
	else
	{
		m_strSkillTabPopupInfo = _S(63, "��Ƽ�� ��ų");
	}
	
	int nWidth = m_strSkillTabPopupInfo.Length() * _pUIFontTexMgr->GetFontWidth();
	m_rcSkillTabPopupInfo.SetRect( m_rcSkillTab[nTab].Left - nWidth - 20, m_rcSkillTab[nTab].Top, m_rcSkillTab[nTab].Left, m_rcSkillTab[nTab].Top + 30 );
	if ( m_nPosX < nWidth )
	{
		m_rcSkillTabPopupInfo.SetRect( m_rcSkillTab[nTab].Right, m_rcSkillTab[nTab].Top, m_rcSkillTab[nTab].Right+100, m_rcSkillTab[nTab].Top + 30 );
	}
}

// ----------------------------------------------------------------------------
// Name : GetSelectedPositon()
// Desc : �δ� ���� �޺� �ڽ����� ���� ���
// ----------------------------------------------------------------------------
INDEX CUIGuild::GetSelectedPositon()
{
	int iPosition = GUILD_MEMBER_NOMEMBER;
	int iSelMember = m_lbManageMemberList.GetCurSel();
	if( iSelMember != -1 )
	{
		sGuildMember &TmpMember = m_vectorMemberList[iSelMember];
		iPosition = TmpMember.eRanking;
		if ( iPosition != GUILD_MEMBER_BOSS && iPosition != GUILD_MEMBER_VICE_BOSS )
		{
			int nSelCombo = m_pGuildChangeSetUI->GetComboCurSelIdx();
			switch( nSelCombo )
			{
			case CMB_RUSH_CAPTAIN:
				iPosition = GUILD_MEMBER_RUSH_CAPTAIN;
				break;
			case CMB_SUPPORT_CAPTAIN:
				iPosition = GUILD_MEMBER_SUPPORT_CAPTAIN;
				break;
			case CMB_RECON_CAPTAIN:
				iPosition = GUILD_MEMBER_RECON_CAPTAIN;
				break;
			case CMB_RUSH_MEMBER:
				iPosition = GUILD_MEMBER_RUSH;
				break;
			case CMB_SUPPORT_MEMBER:
				iPosition = GUILD_MEMBER_SUPPORT;
				break;
			case CMB_RECON_MEMBER:
				iPosition = GUILD_MEMBER_RECON;
				break;
			case CMB_NOMEMBER:
				iPosition = GUILD_MEMBER_MEMBER;
				break;
			}
		}
	}
	return iPosition;
}

// ----------------------------------------------------------------------------
// Name : SetSkillBtnInfo()
// Desc : ��� ��ų ��ư ���� ����
// ----------------------------------------------------------------------------
void CUIGuild::SetSkillBtnInfo()
{
	int nScrollPos = m_sbGuildSkillBar.GetScrollPos();
	int nSkillCount = GetGuildSkillCount();
	int nLoopCnt = ( nSkillCount>5 ) ? 5 : nSkillCount;
	
	for ( int nIndex=0; nIndex<nLoopCnt; ++nIndex )
	{
		CSkill SkillData;
		if ( m_nSelSkillTab == GUILD_SKILL_PASSIVE )
		{
			SkillData = m_vecGuildPassiveSkill[nIndex+nScrollPos];
		}
		else
		{
			SkillData = m_vecGuildActiveSkill[nIndex+nScrollPos];
		}

		if (MY_INFO()->GetReuseSkill(SkillData.GetIndex()) > 0)
		{
			MY_INFO()->SetSkillDelay(SkillData.GetIndex(), true);
			m_pIconsGuildSkillEx[nIndex]->setCooltime(true);
		}

		m_pIconsGuildSkillEx[nIndex]->setData(UBET_SKILL, SkillData.GetIndex());
	}
}

// ----------------------------------------------------------------------------
// Name : GetReuseTime()
// Desc : ����ð� ���
// ----------------------------------------------------------------------------
DOUBLE CUIGuild::GetReuseTime( INDEX SkillIndex )
{
	CSkill SkillData = _pNetwork->GetSkillData( SkillIndex );
	DOUBLE ReuseTime = SkillData.GetReUseTime();

	return DOUBLE( ReuseTime + _pNetwork->MyCharacterInfo.magicspeed ) / 10.0;

}

// ----------------------------------------------------------------------------
// Name : GetCoolTime()
// Desc : ��Ÿ�� ���
// ----------------------------------------------------------------------------
DOUBLE CUIGuild::GetCoolTime( DOUBLE ReuseTime, DOUBLE StartTime )
{
	DOUBLE coolTime = ReuseTime - (_pTimer->GetHighPrecisionTimer().GetSeconds() - StartTime);
	
	return ( coolTime >= 0 ? coolTime : 0 );
}

// ----------------------------------------------------------------------------
// Name : GetSkillDelay()
// Desc : ��ų ������ ���
// ----------------------------------------------------------------------------
BOOL CUIGuild::GetSkillDelay( INDEX index )
{
	for ( int i=0; i<m_vecGuildActiveSkill.size(); ++i )
	{
		CSkill& SkillData = m_vecGuildActiveSkill[i];
		if ( m_vecGuildActiveSkill[i].GetIndex() == index )
		{
			DOUBLE ReuseTime = GetReuseTime( SkillData.GetIndex() );
			DOUBLE StartTime = SkillData.Skill_Data.Skill_StartTime;
			DOUBLE CoolTime  = GetCoolTime( ReuseTime, StartTime );
			if ( CoolTime > 0 )
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

// ----------------------------------------------------------------------------
// Name : SetCorpsInfo()
// Desc : ����� �δ� ���� ����
// ----------------------------------------------------------------------------
void CUIGuild::SetCorpsInfo( INDEX memberCount, INDEX bossCount )
{
	m_iCorpsMember	= memberCount;
	m_iCorpsBoss	= bossCount;
}

// ----------------------------------------------------------------------------
// Name : SetCorpsComboBox()
// Desc : �δ� ���� �޺� �ڽ� ����
// ----------------------------------------------------------------------------
void CUIGuild::SetCorpsComboBox()
{
	m_pGuildChangeSetUI->ResetComboBox();

	int iSelMember = m_lbManageMemberList.GetCurSel();
	if( iSelMember != -1 )
	{
		sGuildMember &TmpMember = m_vectorMemberList[iSelMember];
		int nPosition = TmpMember.eRanking;
		int nSelCombo = CMB_NOMEMBER;

		switch( nPosition )
		{
		case GUILD_MEMBER_BOSS:
			{
				m_pGuildChangeSetUI->AddComboString( m_strCorps[GUILD_MEMBER_BOSS] );
				nSelCombo = 0;
			}
			break;
		case GUILD_MEMBER_VICE_BOSS:
			{
				m_pGuildChangeSetUI->AddComboString( m_strCorps[GUILD_MEMBER_VICE_BOSS] );
				nSelCombo = 0;
			}
			break;
		case GUILD_MEMBER_RUSH_CAPTAIN:
			nSelCombo = CMB_RUSH_CAPTAIN;
			break;
		case GUILD_MEMBER_SUPPORT_CAPTAIN:
			nSelCombo = CMB_SUPPORT_CAPTAIN;
			break;
		case GUILD_MEMBER_RECON_CAPTAIN:
			nSelCombo = CMB_RECON_CAPTAIN;
			break;
		case GUILD_MEMBER_RUSH:
			nSelCombo = CMB_RUSH_MEMBER;
			break;
		case GUILD_MEMBER_SUPPORT:
			nSelCombo = CMB_SUPPORT_MEMBER;
			break;
		case GUILD_MEMBER_RECON:
			nSelCombo = CMB_RECON_MEMBER;
			break;
		case GUILD_MEMBER_MEMBER:
			nSelCombo = CMB_NOMEMBER;
			break;
		}

		if ( nPosition != GUILD_MEMBER_BOSS && nPosition != GUILD_MEMBER_VICE_BOSS )
		{
			for ( int iPos=GUILD_MEMBER_MEMBER; iPos<GUILD_MEMBER_TOTAL; ++iPos )
			{
				m_pGuildChangeSetUI->AddComboString( m_strCorps[iPos] );
			}
		}

		m_pGuildChangeSetUI->SetComboCurSelIdx( nSelCombo );
	}	
}

// ----------------------------------------------------------------------------
// Name : InitString()
// Desc : �δ� ���� ��Ʈ�� ����
// ----------------------------------------------------------------------------
void CUIGuild::InitString()
{
	m_strCorps[GUILD_MEMBER_BOSS]			 = _S( 891,  "�����" );
	m_strCorps[GUILD_MEMBER_VICE_BOSS]		 = _S( 892,  "������" );
	m_strCorps[GUILD_MEMBER_MEMBER]			 = _S( 893,  "����" );
	m_strCorps[GUILD_MEMBER_RUSH_CAPTAIN]	 = _S( 5323, "���ݴ���" );
	m_strCorps[GUILD_MEMBER_SUPPORT_CAPTAIN] = _S( 5324, "��������" );
	m_strCorps[GUILD_MEMBER_RECON_CAPTAIN]	 = _S( 5325, "��������" );
	m_strCorps[GUILD_MEMBER_RUSH]			 = _S( 5326, "���ݴ��" );
	m_strCorps[GUILD_MEMBER_SUPPORT]		 = _S( 5327, "�������" );
	m_strCorps[GUILD_MEMBER_RECON]			 = _S( 5328, "�������" );
}

// ----------------------------------------------------------------------------
// Name : ReceiveCorpsInfo()
// Desc : ��� �δ� ���� �ޱ�
// ----------------------------------------------------------------------------
void CUIGuild::ReceiveCorpsInfo( CNetworkMessage* istr )
{
	INDEX iCorpsMember, iCorpsBoss;
	
	(*istr) >> iCorpsMember
			>> iCorpsBoss;

	SetCorpsInfo( iCorpsMember, iCorpsBoss );
}

WMSG_RESULT CUIGuild::OpenGuildPop( int nMemberIdx, int nX, int nY )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	//check for secondary click here if so return wmsg_fail

	if (m_pGuildMember == NULL)
		return WMSG_FAIL;

	if (m_pGuildMember->m_pList == NULL)
		return WMSG_FAIL;

	if (m_pGuildMember->m_pList->getListItemCount() <= nMemberIdx || nMemberIdx < 0)
		return WMSG_FAIL;

	CUIListItem* pItem = (CUIListItem*)m_pGuildMember->m_pList->GetListItem(nMemberIdx);

	CUIText* pText = (CUIText*)pItem->findUI("text_name");

	if (pText == NULL)
		return WMSG_FAIL;

	CTString strTargetName = pText->getText();

	if ( IsOnline(strTargetName) == FALSE )
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(4523, "����� ã�� �� �����ϴ�."), SYSMSG_ERROR);
		return WMSG_FAIL;
	}

	int nCharIndex = GetMemberNetIdx(strTargetName);
	pUIManager->GetSimplePop()->OpenPopNoTarget(strTargetName, nCharIndex,
		(GAMEDATAMGR()->GetPartyInfo()->GetMemberCount() > 0 && GAMEDATAMGR()->GetPartyInfo()->AmILeader()) ? true : false, nX, nY);

 	return WMSG_SUCCESS;
}

BOOL CUIGuild::IsOnline( CTString strName )
{
	std::vector<sGuildMember>::iterator iter = m_vectorMemberList.begin();
	std::vector<sGuildMember>::iterator iter_end = m_vectorMemberList.end();

	for (; iter != iter_end; ++iter)
	{
		if ((*iter).strMemberName == strName)
			return (*iter).bOnline;
	}

	return false;
}

int CUIGuild::GetMemberNetIdx( CTString strName )
{
	std::vector<sGuildMember>::iterator iter = m_vectorMemberList.begin();
	std::vector<sGuildMember>::iterator iter_end = m_vectorMemberList.end();

	for (; iter != iter_end; ++iter)
	{
		if ((*iter).strMemberName == strName)
			return (*iter).lIndex;
	}

	return -1;
}


void CUIGuild::ArrangeMemList(const int eType)
{
#if		!defined(WORLD_EDITOR)
	int i;
	for (i = 0; i < eGML_MAX; ++i)
	{
		if (i == eType)
			continue;

		m_pCbMemberArrange[i]->SetCheck(FALSE);
	}

	BOOL bAscending = !(m_pCbMemberArrange[eType]->IsChecked());

	if (m_pGuildMember != NULL)
		m_pGuildMember->resetList();

	m_vecGuildMember.clear();

	switch(eType)
	{
	case eGML_NAME:
		{
			const ContGuild::nth_index<eGML_NAME>::type& use_index = m_ContGuild.get<eGML_NAME>();

			if (bAscending == TRUE)
			{
				for (auto iter = use_index.begin(); iter != use_index.end(); ++iter)
				{
					AddGuildMemberInfo(*(*iter).get());
				}
			}
			else
			{
				for (auto iter = use_index.rbegin(); iter != use_index.rend(); ++iter)
				{
					AddGuildMemberInfo(*(*iter).get());
				}
			}
		}
		break;
	case eGML_TITLE:
		{
			const ContGuild::nth_index<eGML_TITLE>::type& use_index = m_ContGuild.get<eGML_TITLE>();

			if (bAscending == FALSE)
			{
				for (auto iter = use_index.begin(); iter != use_index.end(); ++iter)
				{
					AddGuildMemberInfo(*(*iter).get());
				}
			}
			else
			{
				for (auto iter = use_index.rbegin(); iter != use_index.rend(); ++iter)
				{
					AddGuildMemberInfo(*(*iter).get());
				}
			}
		}
		break;
	case eGML_LV:
		{
			const ContGuild::nth_index<eGML_LV>::type& use_index = m_ContGuild.get<eGML_LV>();

			if (bAscending == TRUE)
			{
				for (auto iter = use_index.begin(); iter != use_index.end(); ++iter)
				{
					AddGuildMemberInfo(*(*iter).get());
				}
			}
			else
			{
				for (auto iter = use_index.rbegin(); iter != use_index.rend(); ++iter)
				{
					AddGuildMemberInfo(*(*iter).get());
				}
			}
		}
		break;
	case eGML_CLASS:
		{
			const ContGuild::nth_index<eGML_CLASS>::type& use_index = m_ContGuild.get<eGML_CLASS>();

			if (bAscending == TRUE)
			{
				for (auto iter = use_index.begin(); iter != use_index.end(); ++iter)
				{
					AddGuildMemberInfo(*(*iter).get());
				}
			}
			else
			{
				for (auto iter = use_index.rbegin(); iter != use_index.rend(); ++iter)
				{
					AddGuildMemberInfo(*(*iter).get());
				}
			}
		}
		break;
	case eGML_LOCAL:
		{
			const ContGuild::nth_index<eGML_LOCAL>::type& use_index = m_ContGuild.get<eGML_LOCAL>();
			const ContGuild::nth_index<eGML_LOGOUT_DATE>::type& use_index2 = m_ContGuild.get<eGML_LOGOUT_DATE>();

			if (bAscending == TRUE)
			{
				for (auto iter = use_index.begin(); iter != use_index.end(); ++iter)
				{
					if ( (*iter)->bOnline == FALSE )
						continue;

					AddGuildMemberInfo(*(*iter).get());
				}

				for (auto iter = use_index2.rbegin(); iter != use_index2.rend(); ++iter)
				{
					if ( (*iter)->bOnline == TRUE )
						continue;

					AddGuildMemberInfo(*(*iter).get());
				}
			}
			else
			{
				for (auto iter = use_index2.begin(); iter != use_index2.end(); ++iter)
				{
					if ( (*iter)->bOnline == TRUE )
						continue;

					AddGuildMemberInfo(*(*iter).get());
				}

				for (auto iter = use_index.rbegin(); iter != use_index.rend(); ++iter)
				{
					if ( (*iter)->bOnline == FALSE )
						continue;

					AddGuildMemberInfo(*(*iter).get());
				}
			}
		}
		break;
	case eGML_CONTRIBUTION:
	case eGML_POINT:
		{
			// �⿩���� ���� ����Ʈ�� �������� ��ġ�̹Ƿ� ���Ľÿ��� ��������Ʈ�� ���� �ǵ��� ����.
			const ContGuild::nth_index<eGML_CONTRIBUTION>::type& use_index = m_ContGuild.get<eGML_CONTRIBUTION>();

			if (bAscending == TRUE)
			{
				for (auto iter = use_index.begin(); iter != use_index.end(); ++iter)
				{
					AddGuildMemberInfo(*(*iter).get());
				}
			}
			else
			{
				for (auto iter = use_index.rbegin(); iter != use_index.rend(); ++iter)
				{
					AddGuildMemberInfo(*(*iter).get());
				}
			}
		}
		break;
	}

	updateGuildMemberList();
#endif	// WORLD_EDITOR
}

void CUIGuild::ResetArrangeState()
{
	int i;
	for (i = 0; i < eGML_MAX; ++i)
	{
		m_pCbMemberArrange[i]->SetCheck(FALSE);
	}
}

void CUIGuild::ClearGuildSkill()
{
	ClearGuildSkillCooltime();

	m_vecGuildPassiveSkill.clear();
	m_vecGuildActiveSkill.clear();
}

void CUIGuild::ClearGuildSkillCooltime()
{
	int size = m_vecGuildActiveSkill.size();

	if ( size <= 0)
		return;

	for( int i = 0; i < size; ++i )
	{
		int nIndex = m_vecGuildActiveSkill[i].GetIndex();

		CSkill& rSkill = _pNetwork->GetSkillData(nIndex);

		if ( rSkill.GetFlag() & SF_GUILD && ( rSkill.GetType() != CSkill::ST_GUILD_SKILL_PASSIVE || rSkill.GetType() != CSkill::ST_PASSIVE ) )
		{
			rSkill.Skill_Data.Skill_StartTime = 0;	
		}		
	}
}

CTString CUIGuild::GetMemberLogoutInfo( int nLogoutTime )
{
	CTString strTemp;
	if( nLogoutTime > 0 )
	{
		int nCurTime = time(NULL);
		int nTimeGap = nCurTime - nLogoutTime;

		if (nTimeGap <= 0 || nTimeGap <= ONE_HOUR_SECOND)
		{
			strTemp.PrintF(_S(7102, "%d�ð� ��"), 1);
		}
		else if (nTimeGap <= ONE_DAY_SECOND)
		{
			int nHour = nTimeGap / ONE_HOUR_SECOND;
			strTemp.PrintF(_S(7102, "%d�ð� ��"), nHour);
		}
		else
		{
			int nDay = nTimeGap / ONE_DAY_SECOND;	

			if (nDay <= ONE_YEAR_DAY)
				strTemp.PrintF(_S(7103, "%d�� ��"), nDay);
			else
			{
				int nYear = nDay / ONE_YEAR_DAY;
				strTemp.PrintF(_S(7104, "%d�� ��"), nYear);				
			}
		}
	}
	else
		strTemp = _S(3978, "������");

	return strTemp;
}

CTString CUIGuild::GetMemberLogoutTooltip( int nLogoutTime, int& nWidth )
{
	CTString strTemp = CTString("");

	if (nLogoutTime > 0)
	{
		time_t tv_used = nLogoutTime;

		tm* g_tv_t = localtime((time_t*)&tv_used);

		strTemp.PrintF(  _S( 7105,"%d��%d��%d��%d��%d��"), g_tv_t->tm_year + 1900
			, g_tv_t->tm_mon + 1, g_tv_t->tm_mday, g_tv_t->tm_hour, g_tv_t->tm_min);

		if (g_iCountry == RUSSIA)
		{
			extern  CFontData* _pfdDefaultFont;
			nWidth = UTIL_HELP()->GetNoFixedWidth(_pfdDefaultFont, strTemp.str_String);
		}
		else
		{
			CDrawPort* pDraw = CUIManager::getSingleton()->GetDrawPort();
			nWidth = pDraw->GetTextWidth2(strTemp);
		}

		strTemp += _S(6099, "�α׾ƿ�");
	}
	
	return strTemp;
}

void CUIGuild::updateGuildMemberList()
{
	if (m_pGuildMember == NULL)
		return;

	if (m_pGuildMember->m_pList == NULL)
		return;

	m_pGuildMember->resetList();

	CTString tPer;
	CTString strTemp;
	
	CUIListItem* pTemp = m_pGuildMember->m_pList->GetListItemTemplate();

	if (pTemp == NULL)
		return;

	CUIListItem* pItem = NULL;
	CUIText* pText = NULL;
	CUIImageArray* pImageArr = NULL;

	std::vector<clsGuildMemberNew>::iterator iter = m_vecGuildMember.begin();
	std::vector<clsGuildMemberNew>::iterator iter_end = m_vecGuildMember.end();

	int nListIdx = 0;
	for (; iter != iter_end; ++iter)
	{
		m_pGuildMember->m_pList->AddListItem(pTemp->Clone());
		pItem = (CUIListItem*)m_pGuildMember->m_pList->GetListItem(nListIdx);
		
		if (pItem == NULL)
			continue;

		CmdGuildMouseEvent* pCmdEnter = new CmdGuildMouseEvent;
		pCmdEnter->setData(this, pItem, 0xF8E1B5FF);
		pItem->SetCommandEnter(pCmdEnter);

		CmdGuildMouseEvent* pCmdLeave = new CmdGuildMouseEvent;
		pCmdLeave->setData(this, pItem, 0xF2F2F2FF);
		pItem->SetCommandLeave(pCmdLeave);

		clsGuildMemberNew tMemberInfo = *iter;

		pImageArr = (CUIImageArray*)pItem->findUI("ia_pos");

		if (pImageArr != NULL)
			pImageArr->SetRenderIdx(tMemberInfo.eRanking);

		pText = (CUIText*)pItem->findUI("text_name");

		if (pText != NULL)
			pText->SetText(CTString(tMemberInfo.strMemberName.c_str()));

		pText = (CUIText*)pItem->findUI("text_title");

		if (pText != NULL)
			pText->SetText(CTString(tMemberInfo.sPosName.c_str()));

		//�ڱ� ������ �������߰�
		strTemp = tMemberInfo.strMemberName.c_str();

		if(strTemp.Matches(_pNetwork->MyCharacterInfo.name))
			_pNetwork->MyCharacterInfo.guildPosName = tMemberInfo.sPosName.c_str();

		tPer.PrintF("%d",tMemberInfo.iLevel);
		pText = (CUIText*)pItem->findUI("text_level");
		
		if (pText != NULL)
			pText->SetText(tPer);

		tPer.PrintF("%s",tMemberInfo.sJobName.c_str());

		pText = (CUIText*)pItem->findUI("text_class");

		if (pText != NULL)
			pText->SetText(tPer);

		CTString strToolTip = CTString("");
		int nTooltipWidth = 0;
		if (tMemberInfo.iLocation >= 0)
			tPer.PrintF("%s",tMemberInfo.sLocName.c_str());
		else
		{
			tPer = GetMemberLogoutInfo(tMemberInfo.nLogoutDate);
			strToolTip = GetMemberLogoutTooltip(tMemberInfo.nLogoutDate, nTooltipWidth);	
		}

		pText = (CUIText*)pItem->findUI("text_local");

		if (pText != NULL)
		{
			pText->SetText(tPer);
			if (strToolTip.IsEmpty() == FALSE)
			{
				pText->setTooltip(strToolTip);
				pText->setTooltipWidth(nTooltipWidth);
			}
		}

		if(m_iGuildTotalPoint > 0)
			tPer.PrintF("%lld%",(tMemberInfo.iCumulPoint * 100) / m_iGuildTotalPoint);
		else 
			tPer.PrintF("0");

		UIMGR()->InsertCommaToString(tPer);
		pText = (CUIText*)pItem->findUI("text_contribution");

		if (pText != NULL)
			pText->SetText(tPer);

		tPer.PrintF("%lld",tMemberInfo.iCumulPoint);
		UIMGR()->InsertCommaToString(tPer);

		pText = (CUIText*)pItem->findUI("text_point");

		if (pText != NULL)
			pText->SetText(tPer);

		++nListIdx;
	}

	int nItemCount = m_pGuildMember->m_pList->getListItemCount();
	m_pGuildMember->m_pList->setCurSel(-1);
	CUIScrollBar* pScroll = m_pGuildMember->m_pList->GetScroll();
	if (pScroll != NULL)
		pScroll->SetScrollCurPos(0);

	m_pGuildMember->m_pList->UpdateScroll(nItemCount);
	m_pGuildMember->m_pList->UpdateList();
}

void CUIGuild::SetMemberListStrColor( CUIListItem* pListItem, COLOR col )
{
	if ( pListItem == NULL )
		return;

	int nMax = pListItem->getChildCount();
	CUIText* pTex;

	for (int i = 1; i < nMax; i++)
	{
		pTex = (CUIText*)pListItem->getChildAt(i);

		if ( pTex != NULL)
			pTex->setFontColor(col);
	}
}

// -------------------------------------------------------------------------------------------------------->>

CGuildMemberDesign::CGuildMemberDesign()
	: m_pList(NULL)
{

}

void CGuildMemberDesign::initialize()
{
	m_pList = (CUIList*)findUI("list_guildmember");
}

void CGuildMemberDesign::resetList()
{
	if (m_pList != NULL)
		m_pList->DeleteAllListItem();
}

void CGuildMemberDesign::SetFontColor( COLOR col )
{
	if (m_pList == NULL)
		return;

	CUIText* pText = NULL;
	CUIListItem* pItem = NULL;
	int count = m_pList->getListItemCount();

	for (int i = 0; i < count; ++i)
	{
		pItem = (CUIListItem*)m_pList->GetListItem(i);

		if (pItem == NULL)
			continue;

		pText = (CUIText*)pItem->findUI("text_name");

		if (pText != NULL)
			pText->setFontColor(col);

		pText = (CUIText*)pItem->findUI("text_title");

		if (pText != NULL)
			pText->setFontColor(col);

		pText = (CUIText*)pItem->findUI("text_level");

		if (pText != NULL)
			pText->setFontColor(col);

		pText = (CUIText*)pItem->findUI("text_class");

		if (pText != NULL)
			pText->setFontColor(col);

		pText = (CUIText*)pItem->findUI("text_local");

		if (pText != NULL)
			pText->setFontColor(col);

		pText = (CUIText*)pItem->findUI("text_contribution");

		if (pText != NULL)
			pText->setFontColor(col);

		pText = (CUIText*)pItem->findUI("text_point");

		if (pText != NULL)
			pText->setFontColor(col);
	}

	m_pList->UpdateList();
}
