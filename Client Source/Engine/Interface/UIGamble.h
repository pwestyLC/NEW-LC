// ----------------------------------------------------------------------------
//  File : UIGamble.h
//  Desc : Created by dongmin
// ----------------------------------------------------------------------------

#ifndef	UIGAMBLE_H_
#define	UIGAMBLE_H_
#ifdef	PRAGMA_ONCE
	#pragma once
#endif

class CUIIcon;

#include <Engine/Ska/ModelInstance.h>


// Define text position
#define	GAMBLE_TITLE_TEXT_OFFSETX			25
#define	GAMBLE_TITLE_TEXT_OFFSETY			5

// Define size of shop
#define GAMBLE_MAIN_WIDTH					255
#define	GAMBLE_MAIN_HEIGHT					213
#define GAMBLE_TOTAL_MARK					7
#define GAMBLE_TOTAL_NUMBER					10
#define GAMBLE_TOTAL_SLOT					5

// [071122] New_MoonStone :Su-won
#define MAX_REWARD_COUNT					24		//�ִ� ����ǰ ��

#define MOONSTONE_MAX						6

// ----------------------------------------------------------------------------
// Name : CUIGamble
// Desc :
// ----------------------------------------------------------------------------
class CUIGamble : public CUIWindow
{
protected:
	// Region
	UIRect				m_rcMainTitle;	
	UIRect				m_rcSlot[GAMBLE_TOTAL_SLOT];
	DOUBLE				m_dSlotOld[GAMBLE_TOTAL_SLOT];
	DOUBLE				m_dSlotElapsed[GAMBLE_TOTAL_SLOT];	
	int					m_iSelectedMarker[GAMBLE_TOTAL_SLOT];		// �������� ���� ���õ� ��Ŀ��...
	int					m_iCurMarker[GAMBLE_TOTAL_SLOT];
	int					m_iMarkerScore[GAMBLE_TOTAL_MARK];			// ���� ���� ����...
	BOOL				m_iStoppedMarker[GAMBLE_TOTAL_MARK];
	BOOL				m_bSelectedFixed;
	int					m_iMaxMarker;
	int					m_iAccumulate;
	CTString			m_strAccumulate;

	// Background
	UIRectUV			m_rtBackTop;
	UIRectUV			m_rtBackMiddle;
	UIRectUV			m_rtBackBottom;	

	UIRectUV			m_rtMark[GAMBLE_TOTAL_MARK];				// ������ ǥ�� ��ũ...
	UIRectUV			m_rtSelect;									// ������ ���õ� ��ũ ǥ��.
	UIRectUV			m_rtSmallNumber[GAMBLE_TOTAL_NUMBER];		// ������ ����Ʈ ǥ�� ����
	
	// Buttons	
	CUIButton			m_btnStop;
	CUIButton			m_btnCancel;

	// Position of target npc
	//FLOAT				m_fNpcX, m_fNpcZ;
	BOOL				m_bBegin;
	BOOL				m_bStart;
	BOOL				m_bSendedStart;

	int					m_iStopSlot;
	CEntity*			m_pNpcEntity;

	BOOL			m_bIsCashMoonStone;
	BOOL			m_bIsReady;			// Check Ready State
	INDEX			m_selCashItemIdx;

	// Cash MoonStone Structure
	struct CASHITEMS{
		INDEX			cashIdx;		// cash item catalog index
		CTString		cashName;		// cash item name
		INDEX			cashCnt;		// cash item count (exclude set items)
	};
	
	std::vector<CASHITEMS> m_cashItemList;


	//////////////////////////////////////////////////////////////////////////////////////////////
	// [071122: Su-won] NEW_MOONSTONE
	CStaticArray<INDEX>	m_saReward[MOONSTONE_MAX];
	INDEX*				m_iTexID;					// ������ ������ �ؽ��� ID
	UIRectUV*			m_rtNewMark;				// ������ ������ �ؽ��� ��ǥ
	
	INDEX				m_iUsedMoonStone;							// �����濡 ���� ������ ����

	CUIIcon*			m_pIconsMoonStone[5];								// �귿�� ����� ������ ��ư
	// [071108: Su-won] NEW_MOONSTONE
	//////////////////////////////////////////////////////////////////////////////////////////////
private:
	int					m_nMoonstoneMax;

	bool				m_autoClick;

public:
	CUIGamble();
	~CUIGamble();

	// Create
	void	Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight );
	ENGINE_API void	OpenGamble( CEntity* pEntity ,BOOL bIsCashMoonStone = FALSE);
	void	ShowGamble();

	void	Start();
	void	Stop();

	BOOL 	IsAutoClick();
	//void	SendAutoClick();

	// Render
	void	Render();	

	// Adjust position
	void	ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void	AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );	

	void	ResetGamble();

	// ���� ����Ʈ ǥ���ϱ�...
	void	ShowPrizeEffect();
	
	void	SetSelectedMarker( int iSlot, int iCount );
	void	SetAccumulate( int iAccumulate );

	// Check Cash Item
	BOOL	 	CheckCashItem(int itemIdx);
	void		SetSelCashItemIdx(int idx) { m_selCashItemIdx = idx; }
	int			GetSelCashItemIdx() { return m_selCashItemIdx; }

	//////////////////////////////////////////////////////////
	// [071122: Su-won] NEW_MOONSTONE
	void		ReadMoonStoneLOD();
	INDEX		GetUsedMoonStoneIndex();
	void		SetSelectedItem( INDEX	iRewardItem );
	// [071122: Su-won] NEW_MOONSTONE
	//////////////////////////////////////////////////////////

	// Messages
	WMSG_RESULT	MouseMessage( MSG *pMsg );

	
	std::vector<CASHITEMS>& GetCashItemList() { return m_cashItemList; }

protected:	
	void	DrawNumber( int x, int y, int nNumber );				// ����ǥ��
	void	DrawNumber( int x, int y, CTString& strNumber );		// ����ǥ��
	void	RenderSlot( int iSlot, int iMarker );
	void	RenderSelectedSlot( );
	void	Init();
};

#endif // UIGAMBLE_H_

