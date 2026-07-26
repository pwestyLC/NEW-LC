#include "stdh.h"

// ��� ����. [12/2/2009 rumist]
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIRefine.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/LocalDefine.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Contents/Base/UIQuestBookNew.h>
#include <Engine/Interface/UIHelp.h>

#include <Engine/Contents/function/TransmogrifyUI.h>
#include <Engine/Contents/function/ExtendMenuUI.h>
#include <Engine/Contents/function/BoxOpenUI.h>
#include <Engine/Contents/function/PRSRemoveUI.h>

enum eSelection
{
	REFINE_OK,
	REFINE_TALK,
	REFINE_EVENT,
	TRANSMOGRIFY,
	EXTEND_MENU,
	BOX_OPEN,
	PRS_REMOVE
};

static int	_iMaxMsgStringChar = 0;

// [KH_07044] 3�� ���� ���� �߰�
extern INDEX g_iShowHelp1Icon;

// ----------------------------------------------------------------------------
// Name : CUIRefine()
// Desc : Constructor
// ----------------------------------------------------------------------------
CUIRefine::CUIRefine()
	: m_pIconSlotItem(NULL)
{
	m_nStringCount = 0;
	m_bWaitRefineResult = TRUE;
	m_strRefineMoney = CTString( "" );
	m_llRefineMoney = 0;
}

// ----------------------------------------------------------------------------
// Name : ~CUIRefine()
// Desc : Destructor
// ----------------------------------------------------------------------------
CUIRefine::~CUIRefine()
{
	SAFE_DELETE(m_pIconSlotItem);
}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
void CUIRefine::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight )
{
	CUIWindow::Create(pParentWnd, nX, nY, nWidth, nHeight);

	_iMaxMsgStringChar = 190 / ( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() );

	// Region of each part
	m_rcTitle.SetRect( 0, 0, 216, 22 );
	m_rcItemSlot.SetRect( 91, 0, 125, 0 );
	m_rcInsertItem.SetRect( 3, 0, 213, 0 );

	// Create refine texture
	m_ptdBaseTexture = CreateTexture( CTString( "Data\\Interface\\MessageBox.tex" ) );
	FLOAT	fTexWidth	= m_ptdBaseTexture->GetPixWidth();
	FLOAT	fTexHeight	= m_ptdBaseTexture->GetPixHeight();

	// UV Coordinate of each part
	// Background
	m_rtTop.SetUV( 0, 0, 216, 26, fTexWidth, fTexHeight );
	m_rtMiddle1.SetUV( 0, 31, 216, 33, fTexWidth, fTexHeight );
	m_rtMiddle2.SetUV( 0, 35, 216, 37, fTexWidth, fTexHeight );
	m_rtBottom.SetUV( 0, 38, 216, 45, fTexWidth, fTexHeight );
	m_rtItemSlot.SetUV( 0, 68, 34, 102, fTexWidth, fTexHeight );

	// Close button
	m_btnClose.Create( this, CTString( "" ), 184, 4, 14, 14 );
	m_btnClose.SetUV( UBS_IDLE, 219, 0, 233, 14, fTexWidth, fTexHeight );
	m_btnClose.SetUV( UBS_CLICK, 234, 0, 248, 14, fTexWidth, fTexHeight );
	m_btnClose.CopyUV( UBS_IDLE, UBS_ON );
	m_btnClose.CopyUV( UBS_IDLE, UBS_DISABLE );

	// OK button
	m_btnOK.Create( this, _S( 191, "Ȯ��" ), 36, 154, 63, 21 );
	m_btnOK.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnOK.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnOK.CopyUV( UBS_IDLE, UBS_ON );
	m_btnOK.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Cancel button
	m_btnCancel.Create( this, _S( 139, "���" ), 117, 154, 63, 21 );
	m_btnCancel.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnCancel.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnCancel.CopyUV( UBS_IDLE, UBS_ON );
	m_btnCancel.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Add string
	AddString( _S( 225, "���ü����� ��ȯ��ų �������� �κ��丮���� �����Ͽ� �־��ֽʽÿ�." ) );

	// Set region of slot item & money...
	int	nNewHeight = REFINE_DESC_TEXT_SY + ( m_nStringCount + 1 ) * _pUIFontTexMgr->GetLineHeight();
	m_rcItemSlot.Top = nNewHeight;
	m_rcItemSlot.Bottom = m_rcItemSlot.Top + 34;

	nNewHeight += 34 + _pUIFontTexMgr->GetLineHeight();
	m_nMoneyPosY = nNewHeight;
	nNewHeight += _pUIFontTexMgr->GetLineHeight() + 8 - _pUIFontTexMgr->GetLineSpacing();
	m_nTextRegionHeight = nNewHeight - REFINE_DESC_TEXT_SY + 8;

	m_rcInsertItem.Top = REFINE_DESC_TEXT_SY;
	m_rcInsertItem.Bottom = nNewHeight;

	nNewHeight += 6;
	m_btnOK.SetPosY( nNewHeight );
	m_btnCancel.SetPosY( nNewHeight );

	nNewHeight += m_btnOK.GetHeight() + 7;
	SetHeight( nNewHeight );

	// Slot item button
	m_pIconSlotItem = new CUIIcon;
	m_pIconSlotItem->Create(this, m_rcItemSlot.Left + 1, m_rcItemSlot.Top + 1, BTN_SIZE, BTN_SIZE, UI_REFINE, UBET_ITEM);
}

// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUIRefine::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUIRefine::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

// ----------------------------------------------------------------------------
// Name : OpenRefine()
// Desc :
// ----------------------------------------------------------------------------
void CUIRefine::OpenRefine(int iMobIndex, BOOL bHasQuest, FLOAT fX, FLOAT fZ )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// If this is already exist
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_REFINE_REQ ) || IsVisible() )
		return;

	// If inventory is already locked
	if( pUIManager->GetInventory()->IsLocked() )
	{
		pUIManager->GetInventory()->ShowLockErrorMessage();
		return;
	}

	// Set position of target npc
	m_fNpcX = fX;
	m_fNpcZ = fZ;

	CMobData* MD = CMobData::getData(iMobIndex);

	// Create refine message box
	pUIManager->CreateMessageBoxL( _S( 226, "����" ), UI_REFINE, MSGLCMD_REFINE_REQ );

	CTString	strNpcName = CMobData::getData(iMobIndex)->GetName();
	pUIManager->AddMessageBoxLString( MSGLCMD_REFINE_REQ, TRUE, strNpcName, -1, 0xE18600FF );

	pUIManager->AddMessageBoxLString( MSGLCMD_REFINE_REQ, TRUE, _S( 227, "� ���ÿ�, ���� ���翩.\n���� �����ִ� ���ݼ��� ���� �� ����̿�.\n\n��? �ƴ� �ƴ�, �ƹ� �� ���� �ʾƵ� ����. �����ڵ��� ���� ã�ƿ� �빫�� ������ ������.\n" ), -1, 0xA3A1A3FF );
	pUIManager->AddMessageBoxLString( MSGLCMD_REFINE_REQ, TRUE, _S( 228, "���� �־ �� ���� �ϳ��� �������� ����.\n���ü����� ������� �ϴ� ������ �Ѱ��ְԳ�." ), -1, 0xA3A1A3FF );

	pUIManager->AddMessageBoxLString( MSGLCMD_REFINE_REQ, FALSE, _S( 229, "���ü��� �����." ), REFINE_OK  );	

#ifdef ENABLE_TRANSMOGRIFY
	pUIManager->AddMessageBoxLString( MSGLCMD_REFINE_REQ, FALSE, _S( 8347, "Transmogrify item" ), TRANSMOGRIFY  );
#endif
#ifdef ENABLE_EXTEND_MENU 
	pUIManager->AddMessageBoxLString( MSGLCMD_REFINE_REQ, FALSE, _S( 8348, "Extend Menu" ), EXTEND_MENU  );
#endif
#ifdef ENABLE_OPEN_BOX
	pUIManager->AddMessageBoxLString( MSGLCMD_REFINE_REQ, FALSE, _S( 8394, "Open Box System" ), BOX_OPEN  );
#endif
#ifdef ENABLE_REMOVE_PLATINUM
	pUIManager->AddMessageBoxLString( MSGLCMD_REFINE_REQ, FALSE, _S( 8419, "Remove Platinum Stone" ), PRS_REMOVE  );
#endif
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// [070807: Su-won] EVENT_ADULT_OPEN
	//if( IS_EVENT_ON(TEVENT_ADULT_OPEN) )
	if( 0 )
	{
		pUIManager->AddMessageBoxLString( MSGLCMD_REFINE_REQ, FALSE, _S(3635, "������� ���ݼ� �̺�Ʈ" ), EVENT_ADULT_ALCHEMIST  );	
	}
	// [070807: Su-won] EVENT_ADULT_OPEN
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	pUIManager->AddMessageBoxLString( MSGLCMD_REFINE_REQ, FALSE, _S( 1220, "����Ѵ�." ) );	

	if( bHasQuest )
	{
		// 2009. 05. 27 ������
		// �̾߱��Ѵ� ���� ó��
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_REFINE_REQ);				
	}

	// FIXME : ����Ʈ�� ���� ��쿡 ������ ��.
	// FIXME : ����, �̺�Ʈ NPC�� �ǵ��� ����Ʈ�� ���� �ִ� ���·�???
	if( MD->IsEvent() )
	{
		pUIManager->AddMessageBoxLString( MSGLCMD_REFINE_REQ, FALSE, _S( 100, "�̺�Ʈ" ), REFINE_EVENT );		
	}

	m_bWaitRefineResult = FALSE;
}

// ----------------------------------------------------------------------------
// Name : CloseRefine()
// Desc :
// ----------------------------------------------------------------------------
void CUIRefine::CloseRefine()
{
	// Reset slot item
	m_pIconSlotItem->clearIconData();

	CUIManager* pUIManager = CUIManager::getSingleton();

	// Close refine
	pUIManager->RearrangeOrder( UI_REFINE, FALSE );

	// Unlock inventory
	pUIManager->GetInventory()->Lock( FALSE, FALSE, LOCK_REFINE );

	m_strRefineMoney.Clear();
	m_bWaitRefineResult = FALSE;
}

// ----------------------------------------------------------------------------
// Name : AddString()
// Desc :
// ----------------------------------------------------------------------------
void CUIRefine::AddString( CTString &strDesc )
{
	if( m_nStringCount >= MAX_REFINE_STRING )
		return;

	// Get length of string
	INDEX	nLength = strDesc.Length();
	if( nLength == 0 )
		return;

	int		iPos;
	// wooss 051002
#if defined G_THAI
	// Get length of string
	INDEX	nThaiLen = FindThaiLen(strDesc);
	INDEX	nChatMax= (_iMaxMsgStringChar-1)*(_pUIFontTexMgr->GetFontWidth()+_pUIFontTexMgr->GetFontSpacing());
	if( nLength == 0 )
		return;
	// If length of string is less than max char
	if( nThaiLen <= nChatMax )
	{
		// Check line character
		for( iPos = 0; iPos < nLength; iPos++ )
		{
			if( strDesc[iPos] == '\n' || strDesc[iPos] == '\r' )
				break;
		}

		// Not exist
		if( iPos == nLength )
			m_strRefineDesc[m_nStringCount++] = strDesc;
		else
		{
			// Split string
			CTString	strTemp;
			strDesc.Split( iPos, m_strRefineDesc[m_nStringCount++], strTemp );

			// Trim line character
			if( strTemp[0] == '\r' && strTemp[1] == '\n' )
				strTemp.TrimLeft( strTemp.Length() - 2 );
			else
				strTemp.TrimLeft( strTemp.Length() - 1 );

			AddString( strTemp );
		}
	}
	// Need multi-line
	else
	{
		// Check splitting position for 2 byte characters
		int		nSplitPos = _iMaxMsgStringChar;
		BOOL	b2ByteChar = FALSE;
		for( iPos = 0; iPos < nLength; iPos++ )
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
			CTString	strTemp;
			strDesc.Split( nSplitPos, m_strRefineDesc[m_nStringCount++], strTemp );

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

			AddString( strTemp );
		}
		else
		{
			// Split string
			CTString	strTemp;
			strDesc.Split( iPos, m_strRefineDesc[m_nStringCount++], strTemp );

			// Trim line character
			if( strTemp[0] == '\r' && strTemp[1] == '\n' )
				strTemp.TrimLeft( strTemp.Length() - 2 );
			else
				strTemp.TrimLeft( strTemp.Length() - 1 );

			AddString( strTemp );
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
			m_strRefineDesc[m_nStringCount++] = strDesc;
		else
		{
			// Split string
			CTString	strTemp;
			strDesc.Split( iPos, m_strRefineDesc[m_nStringCount++], strTemp );

			// Trim line character
			if( strTemp[0] == '\r' && strTemp[1] == '\n' )
				strTemp.TrimLeft( strTemp.Length() - 2 );
			else
				strTemp.TrimLeft( strTemp.Length() - 1 );

			AddString( strTemp );
		}
	}
	// Need multi-line
	else
	{
		// Check splitting position for 2 byte characters
		int		nSplitPos = _iMaxMsgStringChar;
		BOOL	b2ByteChar = FALSE;
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
			CTString	strTemp;
			strDesc.Split( nSplitPos, m_strRefineDesc[m_nStringCount++], strTemp );

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

			AddString( strTemp );
		}
		else
		{
			// Split string
			CTString	strTemp;
			strDesc.Split( iPos, m_strRefineDesc[m_nStringCount++], strTemp );

			// Trim line character
			if( strTemp[0] == '\r' && strTemp[1] == '\n' )
				strTemp.TrimLeft( strTemp.Length() - 2 );
			else
				strTemp.TrimLeft( strTemp.Length() - 1 );

			AddString( strTemp );
		}
	}
#endif
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CUIRefine::Render()
{
	// Check distance
	FLOAT	fDiffX = _pNetwork->MyCharacterInfo.x - m_fNpcX;
	FLOAT	fDiffZ = _pNetwork->MyCharacterInfo.z - m_fNpcZ;
	if( fDiffX * fDiffX + fDiffZ * fDiffZ > UI_VALID_SQRDIST )
		CloseRefine();

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Set refine texture
	pDrawPort->InitTextureData( m_ptdBaseTexture );

	// Background
	// Top
	int nX = m_nPosX + m_nWidth;
	int nY = m_nPosY + 26;
	pDrawPort->AddTexture( m_nPosX, m_nPosY, nX, nY,
										m_rtTop.U0, m_rtTop.V0, m_rtTop.U1, m_rtTop.V1,
										0xFFFFFFFF );

	// Middle 1
	pDrawPort->AddTexture( m_nPosX, nY, nX, nY + m_nTextRegionHeight,
										m_rtMiddle1.U0, m_rtMiddle1.V0, m_rtMiddle1.U1, m_rtMiddle1.V1,
										0xFFFFFFFF );

	// Middle 2
	nY += m_nTextRegionHeight;
	pDrawPort->AddTexture( m_nPosX, nY, nX, m_nPosY + m_nHeight - 7,
										m_rtMiddle2.U0, m_rtMiddle2.V0, m_rtMiddle2.U1, m_rtMiddle2.V1,
										0xFFFFFFFF );

	// Bottom
	nY = m_nPosY + m_nHeight - 7;
	pDrawPort->AddTexture( m_nPosX, nY, nX, m_nPosY + m_nHeight,
										m_rtBottom.U0, m_rtBottom.V0, m_rtBottom.U1, m_rtBottom.V1,
										0xFFFFFFFF );

	// Slot item region
	pDrawPort->AddTexture( m_nPosX + m_rcItemSlot.Left, m_nPosY + m_rcItemSlot.Top,
										m_nPosX + m_rcItemSlot.Right, m_nPosY + m_rcItemSlot.Bottom,
										m_rtItemSlot.U0, m_rtItemSlot.V0, m_rtItemSlot.U1, m_rtItemSlot.V1,
										0xFFFFFFFF );

	// Close button
	m_btnClose.Render();

	// OK button
	m_btnOK.Render();

	// Cancel button
	m_btnCancel.Render();

	// Render all elements
	pDrawPort->FlushRenderingQueue();

	// Item
	if (m_pIconSlotItem->IsEmpty() == false)
	{
		m_pIconSlotItem->Render(pDrawPort);
		pDrawPort->FlushBtnRenderingQueue( UBET_ITEM );
	}

	// Text in refine
	pDrawPort->PutTextEx( _S( 231, "����" ), m_nPosX + REFINE_TITLE_TEXT_OFFSETX,
										m_nPosY + REFINE_TITLE_TEXT_OFFSETY, 0xFFFFFFFF );

	nX = m_nPosX + REFINE_DESC_TEXT_SX;
	nY = m_nPosY + REFINE_DESC_TEXT_SY;
	for( int iDesc = 0; iDesc < m_nStringCount; iDesc++ )
	{
		pDrawPort->PutTextEx( m_strRefineDesc[iDesc], nX , nY, 0xC5C5C5FF );
		nY += _pUIFontTexMgr->GetLineHeight();
	}

	// Refineing money
	if( m_llRefineMoney > 0 )
	{
		pDrawPort->PutTextEx( m_strRefineMoney,
											m_nPosX + REFINE_DESC_TEXT_SX, m_nPosY + m_nMoneyPosY, 0xE1B300FF );
	}

	// Flush all render text queue
	pDrawPort->EndTextEx();
}

// ----------------------------------------------------------------------------
// Name : MouseMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT CUIRefine::MouseMessage( MSG *pMsg )
{
	WMSG_RESULT	wmsgResult;

	// Title bar
	static BOOL bTitleBarClick = FALSE;

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

			// Move refine
			if( bTitleBarClick && ( pMsg->wParam & MK_LBUTTON ) )
			{
				int	ndX = nX - nOldX;
				int	ndY = nY - nOldY;
				nOldX = nX;	nOldY = nY;

				Move( ndX, ndY );

				return WMSG_SUCCESS;
			}
			// Close button
			else if( m_btnClose.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			// OK button
			else if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			// Cancel button
			else if( m_btnCancel.MouseMessage( pMsg ) != WMSG_FAIL )
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
				// OK button
				else if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				// Cancel button
				else if( m_btnCancel.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}

				CUIManager::getSingleton()->RearrangeOrder( UI_REFINE, TRUE );
				return WMSG_SUCCESS;
			}
		}
		break;

	case WM_LBUTTONUP:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();

			// If holding button doesn't exist
			if (pUIManager->GetDragIcon() == NULL)
			{
				// Title bar
				bTitleBarClick = FALSE;

				// If refine isn't focused
				if( !IsFocused() )
					return WMSG_FAIL;

				// Close button
				if( ( wmsgResult = m_btnClose.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
						CloseRefine();

					return WMSG_SUCCESS;
				}
				// OK button
				else if( ( wmsgResult = m_btnOK.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
						SendRefineReq();

					return WMSG_SUCCESS;
				}
				// Cancel button
				else if( ( wmsgResult = m_btnCancel.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
						CloseRefine();

					return WMSG_SUCCESS;
				}
			}
			// If holding button exists
			else
			{
				if( IsInside( nX, nY ) )
				{
					// If holding button is item and comes from inventory
					if (pUIManager->GetDragIcon()->getBtnType() == UBET_ITEM &&
						pUIManager->GetDragIcon()->GetWhichUI() == UI_INVENTORY)
					{
						if( IsInsideRect( nX, nY, m_rcInsertItem ) )
						{
							// Set refine item
							SetRefineItem();
						}
					}

					// Reset holding button
					pUIManager->ResetHoldBtn();

					return WMSG_SUCCESS;
				}
			}
		}
		break;

	case WM_LBUTTONDBLCLK:
		{
			if( IsInside( nX, nY ) )
				return WMSG_SUCCESS;
		}
		break;
	}

	return WMSG_FAIL;
}


// ========================================================================= //
//                             Command functions                             //
// ========================================================================= //

// ----------------------------------------------------------------------------
// Name : SetRefineItem()
// Desc :
// ----------------------------------------------------------------------------
void CUIRefine::SetRefineItem()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	CUIIcon* pDrag = pUIManager->GetDragIcon();

	if (pDrag == NULL)
		return;

	CItems* pItems = pDrag->getItems();

	if (pItems == NULL)
		return;

	// If this is wearing item
	if (pDrag->IsWearTab() == true)
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 232, "����� �������� ���ü����� ��ȯ�� �Ұ����մϴ�." ), SYSMSG_ERROR );
		return;
	}

	// If this is not weapon or armor
	CItemData	*pItemData = pItems->ItemData;
	if( pItemData->GetType() != CItemData::ITEM_WEAPON &&
		pItemData->GetType() != CItemData::ITEM_SHIELD )
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 233, "����� ���� ���� �� �� �ֽ��ϴ�." ), SYSMSG_ERROR );
		return;
	}

	// If this item is upgraded
	if( pItems->Item_Plus > 0 )
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 234, "���׷��̵� �� �������� ���ü����� ��ȯ�� �Ұ����մϴ�." ), SYSMSG_ERROR );
		return;
	}

	// If refining money is short
	SLONG	slWearLevel = pItemData->GetLevel();
	CTString strRefineMoney;
	m_llRefineMoney = ( ( slWearLevel + 1 ) * ( slWearLevel + 3 ) * ( slWearLevel -1 ) + 100 ) / 4;
	strRefineMoney.PrintF("%I64d", m_llRefineMoney);
	pUIManager->InsertCommaToString(m_strRefineMoney);
	
	m_strRefineMoney.PrintF( _S( 419, "���� ��� : %s" ), strRefineMoney );

	// Insert upgrade slot
	m_pIconSlotItem->copyItem(pDrag);
}

// ----------------------------------------------------------------------------
// Name : MsgBoxCommand()
// Desc :
// ----------------------------------------------------------------------------
void CUIRefine::MsgBoxLCommand( int nCommandCode, int nResult )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	switch( nCommandCode )
	{
	case MSGLCMD_REFINE_REQ:
		if( nResult == REFINE_OK )
		{
			if( ( (CPlayerEntity*)CEntity::GetPlayerEntity(0) )->IsSkilling() )
			{
				pUIManager->GetChattingUI()->AddSysMessage( _S( 946, "��ų ����߿��� ������ �� �� �����ϴ�." ), SYSMSG_ERROR );		
				CloseRefine();
				return;
			}

			if( pUIManager->IsCSFlagOn( CSF_TELEPORT ) )
			{
				pUIManager->GetChattingUI()->AddSysMessage( _S( 947, "���� �̵��߿��� ������ �� �� �����ϴ�." ), SYSMSG_ERROR );	
				CloseRefine();
				return;
			}

			// If inventory is already locked
			if (pUIManager->GetInventory()->IsLocked() == TRUE ||
				pUIManager->GetInventory()->IsLockedArrange() == TRUE)
			{
				pUIManager->GetInventory()->ShowLockErrorMessage();
				CloseRefine();
				return;
			}

			if( !pUIManager->GetInventory()->IsVisible() )
				pUIManager->GetInventory()->ToggleVisible();

			pUIManager->RearrangeOrder( UI_REFINE, TRUE );

			pUIManager->GetInventory()->Lock(TRUE, TRUE, LOCK_REFINE);
			
// [KH_07044] 3�� ���� ���� �߰�
			if(g_iShowHelp1Icon)
			{
				pUIManager->GetHelp3()->ClearHelpString();
				pUIManager->GetHelp3()->AddHelpString(_S(3298, "���ü����� ������� �ϴ� ��� �κ��丮�κ��� �巡���Ͽ� �� â�� �� ������ �÷� ���� �� Ȯ�� ��ư�� Ŭ���ϸ� �ش� ��� ������ ������ �Ϲ� ���ü����� ��ȯ�˴ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3299, "�� ����� 2���� ���ü����� ��ȯ�Ǹ� ���� 1���� ���ü����� ��ȯ�˴ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3300, "�� �������� ��� �Ǵ� ��� �ƴ� �������� ���ü����� ��ȯ �� �� �����ϴ�."));
				pUIManager->GetHelp3()->OpenHelp(this);
				
			}
		}
		else if( nResult == REFINE_TALK )
		{
			//TODO : NewQuestSystem
			// ����Ʈ â ����
			CUIQuestBook::TalkWithNPC();
		}
		else if( nResult == REFINE_EVENT )		// Event
		{
		}
		else if( nResult == TRANSMOGRIFY )
		{
			pUIManager->GetTransmogrifyUI()->openUI();
		}
		else if( nResult == EXTEND_MENU )
		{
			pUIManager->GetExtendMenuUI()->openUI();
		}
		else if( nResult == BOX_OPEN )
		{
			pUIManager->GetBoxOpenUI()->openUI();
		}
		else if( nResult == PRS_REMOVE )
		{
			pUIManager->GetPRSRemoveUI()->openUI();
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		// [070807: Su-won] EVENT_ADULT_OPEN
		else if( nResult == EVENT_ADULT_ALCHEMIST )
		{
			pUIManager->GetQuest()->MsgBoxLCommand(MSGLCMD_QUEST_REQ, EVENT_ADULT_ALCHEMIST);
		}
		// [070807: Su-won] EVENT_ADULT_OPEN
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		// [090527: selo] Ȯ���� ����Ʈ ����
		else if( ciQuestClassifier < nResult )	
		{
			// ������ ����Ʈ�� ���� ���� �Ǵ� ���� â�� ����.
			CUIQuestBook::SelectQuestFromMessageBox( nResult );
		}

		break;
	}
}


// ========================================================================= //
//                           Send message functions                          //
// ========================================================================= //

// ----------------------------------------------------------------------------
// Name : SendRefineReq()
// Desc :
// ----------------------------------------------------------------------------
void CUIRefine::SendRefineReq()
{
	if( m_bWaitRefineResult == TRUE )
		return;

	CUIManager* pUIManager = CUIManager::getSingleton();

	if( ( (CPlayerEntity*)CEntity::GetPlayerEntity(0) )->IsSkilling() )
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 946, "��ų ����߿��� ������ �� �� �����ϴ�." ), SYSMSG_ERROR );		
		return;
	}

	if( pUIManager->IsCSFlagOn( CSF_TELEPORT ) )
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 947, "���� �̵��߿��� ������ �� �� �����ϴ�." ), SYSMSG_ERROR );	
		return;
	}

	if (m_pIconSlotItem->IsEmpty() == true)
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 235, "������ �������� �����ϴ�." ), SYSMSG_ERROR );
		return;
	}

	if( m_llRefineMoney > _pNetwork->MyCharacterInfo.money )
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 369, "���� ����� �����մϴ�." ), SYSMSG_ERROR );
		return;
	}

	CItems* pItems = m_pIconSlotItem->getItems();

	if (pItems != NULL)
		_pNetwork->RefineReq((SWORD)pItems->Item_Tab, (SWORD)pItems->InvenIndex);

	m_bWaitRefineResult = TRUE;
}


// ========================================================================= //
//                         Receive message functions                         // 
// ========================================================================= //

// ----------------------------------------------------------------------------
// Name : RefineRep()
// Desc :
// ----------------------------------------------------------------------------
void CUIRefine::RefineRep( SBYTE sbResult )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// Close message box
	pUIManager->CloseMessageBox( MSGCMD_REFINE_REP );

	// Show result
	CTString	strMessage;
	switch( sbResult )
	{
	case 0:
		strMessage = _S( 236, "�������� �����Ӱ� �����Ǿ� ���ü��� 2�� �ϼ��Ǿ����ϴ�." );
		break;

	case 1:
		strMessage = _S( 237, "�������� �����Ǿ� ���ü��� 1�� �ϼ��Ǿ����ϴ�." );
		break;

	case 2:
		strMessage = _S( 238, "�������� ���������� �����Ǿ� ���� ���ü��� 1�� �ϼ��Ǿ����ϴ�." );
		break;
	}

	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 231, "����" ), UMBS_OK, UI_REFINE, MSGCMD_REFINE_REP );
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );

	// Reset slot item
	m_pIconSlotItem->clearIconData();

	m_strRefineMoney.Clear();
	m_bWaitRefineResult = FALSE;
}
