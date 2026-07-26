#ifndef	_UIEXPEDITION_NEW_H_
#define	_UIEXPEDITION_NEW_H_

#ifdef	PRAGMA_ONCE
#pragma once
#endif

#include <Engine/Interface/UITrackPopup.h>

#define VIEW_DETAIL_BTN_MAX 14

#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
#define PARTY_DG_INTERFACE_TITLE 8723//SYSTEM TITLE NAME STRING IDX "Party Expeditions"
#define PARTY_DG_PROGRESS_STRING 8724//DOMINATION PROGRESS STRING IDX "Domination Progress"

#define PARTY_DIFICULTY_STRING_NORMAL 8725// "Normal"
#define PARTY_DIFICULTY_STRING_HARD 8726// "Hard"
#define PARTY_DIFICULTY_STRING_HELL 8727// "Hell"
#define PARTY_DG0_INFO_STRING 8728//Face hordes of monsters, Defeat Boss Monsters and get great rewards.
#define PARTY_DG1_INFO_STRING 8729
#define PARTY_DG2_INFO_STRING 8730
#define PARTY_DG3_INFO_STRING 8731
#define PARTY_DG4_INFO_STRING 8732

#define PARTY_DG_COMPLETE_TIMES_TITLE 200
#define PARTY_DG_COMPLETE_TIMES_BOX 10
#endif

class CUIImage;
class CUIText;
class CUIButton;
class CUIList;
class CUIImageArray;
class CUIIcon;
class CItems;

#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
class CUIExpeditionPartyDungeon : public CUIWindow//Cloud Expedition_Party_Dungeon
{
public:
	CUIExpeditionPartyDungeon();
	~CUIExpeditionPartyDungeon();

	void	initialize();

	void	OpenUI();
	void	CloseUI();

	void	SetDungeonInfo(CTString strCharInfo, SBYTE sbJob);
#ifdef CLOUD_EXPEDITION_REWORK
	void	SetDetailInfo(int amend, SLONG nCount, SLONG zone, SLONG difficulty, SLONG level, SLONG cp, SLONG needitem, SLONG needcount, SLONG partymember, int time, SLONG rewardindex, SLONG rewardindex1, SLONG rewardindex2, SLONG rewardindex3, SLONG rewardindex4, SLONG title, SLONG box);//,box pvpabs,SLONG debuuftime,SLONG blockrate,SLONG skillspeed,SLONG ilevel, SQUAD Money,SLONG level, SLONG hp,SLONG mp,SLONG job,SLONG job2);
#endif	
	void	SetViewItemRewards(int nWearPos, CItems* pItem);
	void	ClearDungeonInfo();
	void    UpdateDungeonInfo();
	void    UpdateAmenddungeon(int nAmendIndex);
	void    UpdateInfoRank(int nAmendIndex);

	// Msg Proc
	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);


private:
	enum
	{
		eLIST_AMEND_DUNGEON = 0,
		//eLIST_AMEND_DGCONDITION,
		eLIST_DGEND
	};
	bool			m_bDrag;
	int				m_nOriX, m_nOriY;

	//CUIImageArray*	m_pIaBack;
	CUIButton* m_pbtnClose;
	CUIButton* m_pbtnJoin;
	CUIButton* m_pbtnCallMembers;
	CUIButton* m_pbtnReward;
	CUIText* m_pstrName;
	CUIText* m_pstrTitle;
	CUIText* m_pstrReward;
	CUIText* m_pstrEnter;
	CUIText* m_pstrEnterLv;
	CUIText* m_pstrEnterItem;
	CUIText* m_pstrEnterMembers;
	CUIText* m_pstrEnterMode;
	CUIText* m_pstrEnteriLv;
	CUIText* m_pstrEnterTimer;
	CUIBase* m_pMoveArea;
	CUIList* m_pList[eLIST_DGEND];
	CUIBase* BaseInfoDungeon;
	CUIScrollBar* m_plistScroll;
	CUIBase* BaseArrayReward;
	CUIBase* BaseInfoRank;
	CUIArray* m_pArrayRewardDG;
	CUIProgressBar* m_pDominateProgress;
	CUIText* m_StrProgress;
	CUIComboBox* m_difficulty;


	int				m_nLastCurSel;

#ifdef CLOUD_EXPEDITION_REWORK
	SLONG m_nCount, m_nzone[50], m_ndifficulty[50], m_nlevel[50], m_ncp[50], m_nneeditem[50], m_nneedcount[50], m_npartymember[50], m_nrewardindex[50], m_nrewardindex1[50], m_nrewardindex2[50], m_nrewardindex3[50], m_nrewardindex4[50], m_ntitle[50], m_nbox[50];
	int m_ntime[50];
#endif

	//Cloud new inpect sys
};
#endif

// 살펴보기 창(요청 했을 당시의 정보를 보여줌( 실시간 변경X ))
class CUIViewDetail : public CUIWindow
{
public:
	CUIViewDetail();

	void	initialize();

	void	openUI();
	void	closeUI();

	void	SetCharInfo( CTString strCharInfo, SBYTE sbJob);
	void	SetPetInfo( CNetworkLibrary::sPetInfo petInfo )		{ m_sPetInfo = petInfo;			}
	void	SetWildPetInfo( sPetItem_Info wildPetInfo )			{ m_sWildPetInfo = wildPetInfo; }
	void	SetViewItem(int nWearPos, CItems* pItem);
	void	ClearViewDetail();

	// Msg Proc
	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);

private:
	CNetworkLibrary::sPetInfo		m_sPetInfo;		// 살펴보기 펫 정보
	sPetItem_Info					m_sWildPetInfo;	// 살펴보기 공격형 펫 정보

	bool			m_bDrag;
	int				m_nOriX, m_nOriY;
	
	CUIImageArray*	m_pIaBack;
	CUIButton*		m_pbtnClose;
	CUIText*		m_pstrName;
	CUIImage*		m_pMoveArea;
	CUIIcon*		m_pIcon[WEAR_TOTAL];
};

//원정대 관리 창
class CUIExpManage : public CUIWindow
{
protected:

	//관리 창 POPUP COMMAND
	enum eManageCommandList
	{
		MANAGE_CONNAMD_CHANGE_LEADER = 0,
		MANAGE_CONNAMD_SET_SUBLEADER,
		MANAGE_CONNAMD_RESET_SUBLEADER,
		MANAGE_CONNAMD_KICK_MEMBER,
		MANAGE_CONNAMD_VIEW_MEMBER,
	};

	CTextureData	*m_ptdMessageBoxTexture;
	
	BOOL SetCommand(SLONG slPosition, BOOL bIsMyGroup = FALSE, BOOL bIsExpeditionLeader = FALSE);
	void RunCommand(INDEX iCommand);

public:
	CUIExpManage();
	~CUIExpManage();
	
	void	initialize();
	void	UpdateUI();
	void	openUI();
	void	closeUI();

	void	ClearExpManage();
	void	UpdateMemberInfo(int nGroup, int nPos);

	void	PressAddBtn();
	void	ShowManageMenu(int nGroup, int nPos);

	void	SetSelectIndex(int nIndex) { m_slDestIndex = nIndex; }
	int		GetSelectIndex()	{ return m_slDestIndex; }
	int		calcHpBar(int nGroup, int nPos, int nWidth);
	void	OnPostRender(CDrawPort* pDraw);

	void	SetSelectBtnGroup(int nIndex) { m_slSeletedBtnGroup = nIndex; }
	void	SetSelectBtnPos(int nIndex) { m_slSeletedBtnPos = nIndex; }
	void	SetBtnMove(bool bMove)	{ m_bCanUseBtn = bMove;	}
	int		GetSelectBtnGroup()	{ return m_slSeletedBtnGroup;	}
	int		GetSelectBtnPos()	{ return m_slSeletedBtnPos;		}
	bool	GetBtnMove()		{ return m_bCanUseBtn;			}
	// Msg Proc
	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);

	WMSG_RESULT MouseMessage( MSG *pMsg );

private:
	enum eBtnType
	{
		eBTN_CLOSE = 0, // 닫기 버튼
		eBTN_ADD,		// 대원추가 버튼
		eBTN_CANCEL,	// 취소 버튼
		eBTN_MAX
	};

	enum eGroupType
	{
		eGROUP_1 = 0,
		eGROUP_2,
		eGROUP_3,
		eGROUP_4,
		eGROUP_MAX
	};

	bool		m_bDrag;
	int			m_nOriX, m_nOriY;
	int			m_nMouseX, m_nMouseY;

	CUIImage*	m_pMoveArea;
	CUIText*	m_pstrTitle;
	CUIText*	m_pStrText[eGROUP_MAX];
	CUIButton*	m_pBtn[eBTN_MAX];
	CUIList*	m_pList[eGROUP_MAX];

	SLONG		m_slDestIndex;			// 선택된 멤버 index
	SLONG		m_slSeletedBtnGroup;
	SLONG		m_slSeletedBtnPos;
	CTString	m_strDestName;
	bool		m_bCanUseBtn;
	CUITrackPopup	m_tpList;			// 메뉴
};

#endif	//	_UIEXPEDITION_NEW_H_