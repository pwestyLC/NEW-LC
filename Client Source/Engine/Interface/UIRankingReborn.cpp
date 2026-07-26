#include "stdh.h"

// ��� ����. [12/2/2009 rumist]
#include <vector>
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIRankingReborn.h>
#include <algorithm>

#define RANKING_LIST_BOX_WIDTH			(280)
#define RANKING_LIST_BOX_HEIGHT			(200)

// ----------------------------------------------------------------------------
// Name : CUIRankingReborn()
// Desc : 
// ----------------------------------------------------------------------------
CUIRankingReborn::CUIRankingReborn()
{
}

// ----------------------------------------------------------------------------
// Name : ~CUIRankingReborn()
// Desc : Destructor
// ----------------------------------------------------------------------------
CUIRankingReborn::~CUIRankingReborn()
{
	if(!m_vectorRankingList.empty())
	{
		m_vectorRankingList.clear();
	}
}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
void CUIRankingReborn::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight )
{
	CUIWindow::Create(pParentWnd, nX, nY, nWidth, nHeight);

	// Region of each part
	m_rcTitle.SetRect( 0, 0, 311, 22 );	

	// Create skill learn texture
	m_ptdBaseTexture = CreateTexture( CTString( "Data\\Interface\\MessageBox.tex" ) );
	FLOAT	fTexWidth = m_ptdBaseTexture->GetPixWidth();
	FLOAT	fTexHeight = m_ptdBaseTexture->GetPixHeight();

	// UV Coordinate of each part
	// Background
	m_rtBackTop.SetUV( 0, 0, 216, 26, fTexWidth, fTexHeight );
	m_rtBackMiddle1.SetUV( 0, 31, 216, 33, fTexWidth, fTexHeight );
	m_rtBackMiddle2.SetUV( 0, 35, 216, 37, fTexWidth, fTexHeight );
	m_rtBackManagerTop.SetUV( 36, 86, 252, 106, fTexWidth, fTexHeight );		// 20
	m_rtBackManagerMiddle.SetUV( 36, 106, 252, 112, fTexWidth, fTexHeight );	// 6
	m_rtBackManagerBottom.SetUV( 36, 112, 252, 116, fTexWidth, fTexHeight );	// 4
	m_rtBackBottom.SetUV( 0, 38, 216, 45, fTexWidth, fTexHeight );

	m_rtTab.SetUV( 43, 69, 44, 86, fTexWidth, fTexHeight );

	// Close button
	m_btnClose.Create( this, CTString( "" ), 279, 4, 14, 14 );
	m_btnClose.SetUV( UBS_IDLE, 219, 0, 233, 14, fTexWidth, fTexHeight );
	m_btnClose.SetUV( UBS_CLICK, 234, 0, 248, 14, fTexWidth, fTexHeight );
	m_btnClose.CopyUV( UBS_IDLE, UBS_ON );
	m_btnClose.CopyUV( UBS_IDLE, UBS_DISABLE );

	// List box of guild description
	m_lbRankingList.Create( this, 8, 46, RANKING_LIST_BOX_WIDTH, RANKING_LIST_BOX_HEIGHT, _pUIFontTexMgr->GetLineHeight(), 13, 3, 5, FALSE );
	m_lbRankingList.CreateScroll( TRUE, 0, 0, 9, RANKING_LIST_BOX_HEIGHT, 9, 7, 0, 0, 10 );		
	m_lbRankingList.SetColumnPosX( 0, 10 );
	m_lbRankingList.SetColumnPosX( 1, 40 );
	m_lbRankingList.SetColumnPosX( 2, 132 );
	m_lbRankingList.SetColumnPosX( 3, 220 );
	// Up button
	m_lbRankingList.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbRankingList.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbRankingList.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbRankingList.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbRankingList.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbRankingList.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbRankingList.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbRankingList.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbRankingList.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbRankingList.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbRankingList.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );
}

// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUIRankingReborn::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUIRankingReborn::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

//------------------------------------------------------------------------------
// CUIRankingReborn::SetFocus
// Explain:  
// Date : 2005-03-10(���� 1:02:39) Lee Ki-hwan
//------------------------------------------------------------------------------
void CUIRankingReborn::SetFocus( BOOL bVisible )
{
	CUIWindow::SetFocus( bVisible );
}

// ----------------------------------------------------------------------------
// Name : OpenRankingList()
// Desc : 
// ----------------------------------------------------------------------------
void CUIRankingReborn::OpenRankingList( )
{	
	if( IsVisible() )
	{		
		return;
	}

	m_lbRankingList.ResetAllStrings();

	m_lbRankingList.SetEnable( TRUE );

	RefreshRankingList( TRUE );	

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();
	// Render all elements
	pDrawPort->FlushRenderingQueue();
	// Flush all render text queue
	pDrawPort->EndTextEx();

	CUIManager::getSingleton()->RearrangeOrder( UI_RANKING_REBORN, TRUE );
}

// ----------------------------------------------------------------------------
// Name : ResetRanking()
// Desc : 
// ----------------------------------------------------------------------------
void CUIRankingReborn::ResetRanking()
{		
	m_lbRankingList.ResetAllStrings();
	m_sTotal.Clear();

	ClearRankingList();

	CUIManager::getSingleton()->RearrangeOrder( UI_RANKING_REBORN, FALSE );
}

// ----------------------------------------------------------------------------
// Name : ClearRankingList()
// Desc : ��� ����� Ŭ�����մϴ�.
// ----------------------------------------------------------------------------
void CUIRankingReborn::ClearRankingList()
{
	if(!m_vectorRankingList.empty())
	{
		m_vectorRankingList.clear();
	}
}

// ----------------------------------------------------------------------------
// Name : PressOKBtn()
// Desc : Ȯ�� ��ư�� ������ ���� ó��.
// ----------------------------------------------------------------------------
void CUIRankingReborn::PressOKBtn()
{	
}

// ----------------------------------------------------------------------------
// Name : AddToRankingList()
// Desc : ��� ��Ͽ� �߰�
// ----------------------------------------------------------------------------
void CUIRankingReborn::AddToRankingList( const CTString& strName, INDEX iReborn, INDEX iJob )
{	
	sUserRanking TempRankingUser;
	TempRankingUser.strName	= strName;
	TempRankingUser.iReborn = iReborn;
	TempRankingUser.iJob 	= iJob;
	m_vectorRankingList.push_back(TempRankingUser);
}

// ----------------------------------------------------------------------------
// Name : RefreshRankingList()
// Desc : ����� �����մϴ�.
// ----------------------------------------------------------------------------
void CUIRankingReborn::RefreshRankingList( BOOL bInit )
{
	if( !bInit && !IsVisible() )
		return;

	m_lbRankingList.ResetAllStrings();

	CTString	strTemp;	

	std::vector<sUserRanking>::const_iterator member_end = m_vectorRankingList.end();
	std::vector<sUserRanking>::iterator it = m_vectorRankingList.begin();
	int iNo	= 1;
	for(it = m_vectorRankingList.begin(); it != member_end; ++it, ++iNo )
	{
		unsigned int color = 0xFFFFFFFF;
		if (iNo < 4)
			color = 0xFFFF00FF;

		strTemp.PrintF( "%d.", iNo );
		m_lbRankingList.AddString( 0, strTemp, color );
		m_lbRankingList.AddString( 1, (*it).strName, color );

		strTemp.PrintF( "%s", CJobInfo::getSingleton()->GetName((*it).iJob, 0) );
		m_lbRankingList.AddString( 2, strTemp, color );

		strTemp.PrintF( "%ld", (*it).iReborn );
		m_lbRankingList.AddString( 3, strTemp, color );
	}
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CUIRankingReborn::Render(void)
{
	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Set skill learn texture
	pDrawPort->InitTextureData( m_ptdBaseTexture );

	// Add render regions
	int	nX, nY;

	// Background
	// Top
	nX = m_nPosX + m_nWidth;
	nY = m_nPosY + 26;
	pDrawPort->AddTexture( m_nPosX, m_nPosY, nX, nY,
										m_rtBackTop.U0, m_rtBackTop.V0,
										m_rtBackTop.U1, m_rtBackTop.V1,
										0xFFFFFFFF );
	
	{
		// Manager
		pDrawPort->AddTexture( m_nPosX, nY, nX, nY + 20,
											m_rtBackManagerTop.U0, m_rtBackManagerTop.V0,
											m_rtBackManagerTop.U1, m_rtBackManagerTop.V1,
											0xFFFFFFFF );

		nY += 20;
		
		pDrawPort->AddTexture( m_nPosX, nY, nX, nY + RANKING_LIST_BOX_HEIGHT + 2,
			m_rtBackManagerMiddle.U0, m_rtBackManagerMiddle.V0,
			m_rtBackManagerMiddle.U1, m_rtBackManagerMiddle.V1,
			0xFFFFFFFF );
		
		nY += RANKING_LIST_BOX_HEIGHT + 2;		

		pDrawPort->AddTexture( m_nPosX, nY, nX, nY + 4,
											m_rtBackManagerBottom.U0, m_rtBackManagerBottom.V0,
											m_rtBackManagerBottom.U1, m_rtBackManagerBottom.V1,
											0xFFFFFFFF );

		nY += 4;
	}

	// Middle 2
	pDrawPort->AddTexture( m_nPosX, m_nPosY + 26, nX, m_nPosY + m_nHeight - 7 ,
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

	nX = m_nPosX + 55;
	nY = m_nPosY + 26;
	int nX2 = nX + 1;
	int nY2 = nY + 16;
	pDrawPort->AddTexture( nX, nY, nX2, nY2,
												m_rtTab.U0, m_rtTab.V0, m_rtTab.U1, m_rtTab.V1,
												0xFFFFFFFF );	

	// Ranking List Tab
	nX = m_nPosX + 132;	
	nX2 = nX + 1;
	pDrawPort->AddTexture( nX, nY, nX2, nY2,
											m_rtTab.U0, m_rtTab.V0, m_rtTab.U1, m_rtTab.V1,
											0xFFFFFFFF );
	
	nX = m_nPosX + 205;
	nX2 = nX + 1;
	pDrawPort->AddTexture( nX, nY, nX2, nY2,
											m_rtTab.U0, m_rtTab.V0, m_rtTab.U1, m_rtTab.V1,
											0xFFFFFFFF );
	
	// Close button
	m_btnClose.Render();	

	m_lbRankingList.Render();
	
	pDrawPort->PutTextEx( _S( 1714, "Rank" ), m_nPosX + 20,		
										m_nPosY + 29, 0xFFFFFFFF );

	pDrawPort->PutTextEx( _S( 71, "Name" ), m_nPosX + 80,	
										m_nPosY + 29, 0xFFFFFFFF );

	pDrawPort->PutTextEx( _S( 72, "Class" ), m_nPosX + 152,
		m_nPosY + 29, 0xFFFFFFFF );

	m_sTotal.PrintF(_S( 8374, "Total Reborn" ));
	pDrawPort->PutTextEx( m_sTotal, m_nPosX + 230,
		m_nPosY + 29, 0xFFFFFFFF );

	// Text in guild
	pDrawPort->PutTextEx( _S( 8370, "Ranking Reborn" ), m_nPosX + RANKING_TITLE_TEXT_OFFSETX,
										m_nPosY + RANKING_TITLE_TEXT_OFFSETY, 0xFFFFFFFF );

	// Render all elements
	pDrawPort->FlushRenderingQueue();
	// Flush all render text queue
	pDrawPort->EndTextEx();
}

// ----------------------------------------------------------------------------
// Name : MouseMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT	CUIRankingReborn::MouseMessage( MSG *pMsg )
{
	if (!IsVisible())
	{
		return WMSG_FAIL;
	}

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
			else if( m_btnClose.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_lbRankingList.MouseMessage( pMsg ) != WMSG_FAIL )			
				return WMSG_SUCCESS;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			if( IsInside( nX, nY ) )
			{
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
				else if( m_lbRankingList.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}

				CUIManager::getSingleton()->RearrangeOrder( UI_RANKING_REBORN, TRUE );
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
					ResetRanking();
				}
				return WMSG_SUCCESS;
			}			
			// List box
			else if( m_lbRankingList.MouseMessage( pMsg ) != WMSG_FAIL )
			{
				return WMSG_SUCCESS;
			}
		}
		break;

	case WM_MOUSEWHEEL:
		{
			if( IsInside( nX, nY ) )
			{	
				// List box of member list
				if( m_lbRankingList.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;
			}
		}
		break;
	}
	return WMSG_FAIL;
}