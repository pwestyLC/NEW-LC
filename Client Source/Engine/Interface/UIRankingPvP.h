// ----------------------------------------------------------------------------
//  File : UIRankingPvP.h
//  Desc : Created by alan
// ----------------------------------------------------------------------------

#ifndef	UIRANKING_PVP_H_
#define	UIRANKING_PVP_H_
#ifdef	PRAGMA_ONCE
	#pragma once
#endif

// Define text position
#define	RANKING_TITLE_TEXT_OFFSETX		25
#define	RANKING_TITLE_TEXT_OFFSETY		5

// Define size of Ranking
#define	RANKING_WIDTH					311
#define	RANKING_HEIGHT					280

// ----------------------------------------------------------------------------
// Name : CUIRankingPvP
// Desc :
// ----------------------------------------------------------------------------
class CUIRankingPvP : public CUIWindow
{
protected:

	// internal structure
	struct sUserRanking
	{
		sUserRanking()
		{
			iNumDeadNpc			= 0;
			iJob			= 0;
		}

		~sUserRanking()
		{			
		}
		
		CTString		strName;
		INDEX			iNumDeadNpc;			
		INDEX			iJob;				
	};

	std::vector<sUserRanking>	m_vectorRankingList;

	CTString				m_sTotal;
	
	// Controls
	CUIButton				m_btnClose;						// Close button	

	// Region of each part
	UIRect					m_rcTitle;						// Region of title bar	

	// UV of each part
	UIRectUV				m_rtBackground;					// UV of background		
	UIRectUV				m_rtBackTop;					// UV of top background
	UIRectUV				m_rtBackMiddle1;				// UV of middle background
	UIRectUV				m_rtBackMiddle2;				// UV of middle background
	UIRectUV				m_rtBackManagerTop;				//
	UIRectUV				m_rtBackManagerMiddle;			//
	UIRectUV				m_rtBackManagerBottom;			//
	UIRectUV				m_rtBackBottom;					// UV of bottom background

	UIRectUV				m_rtTab;						// UV of section tab
	
	CUIListBox				m_lbRankingList;				// List box

protected:
	// Command
	void	PressOKBtn();	

public:
	CUIRankingPvP();
	~CUIRankingPvP();

	// Create
	void	Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight );

	// Render
	void	Render();

	void	closeUI();

	// Adjust position
	void	ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void	AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );

	// Open guild	
	void	OpenRankingList( );
	void	ResetRanking();
	void	ClearRankingList();
	
	void	AddToRankingList( const CTString& strName, LONG iNumOfDeadMonster, INDEX iJob );

	void	RefreshRankingList( BOOL bInit = FALSE );

	// Messages
	WMSG_RESULT	MouseMessage( MSG *pMsg );	

	// Set focus
	void	SetFocus( BOOL bVisible );	
	// esc closing support [5/30/2011 rumist]
	BOOL	CloseWindowByEsc()				{ ResetRanking();			return TRUE;		}
};

#endif	// UIRANKING_PVP_H_