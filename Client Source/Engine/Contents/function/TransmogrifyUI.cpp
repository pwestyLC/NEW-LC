#include "stdh.h"

#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/LocalDefine.h>
#include <Engine/Interface/UIInventory.h>
#include "TransmogrifyUI.h"

// ----------------------------------------------------------------------------
// Name : CTransmogrifyUI()
// Desc : Constructor
// ----------------------------------------------------------------------------
CTransmogrifyUI::CTransmogrifyUI()
	: m_pIconSlotItem(NULL)
	, m_btnCancel(NULL)
	, m_btnOK(NULL)
	, m_btnClose(NULL)
	, m_tNas(NULL)
	, m_tTitle(NULL)
{
	m_bWaitRefineResult = FALSE;
	m_strRefineMoney = CTString( "" );
	m_llRefineMoney = 0;
}

// ----------------------------------------------------------------------------
// Name : ~CTransmogrifyUI()
// Desc : Destructor
// ----------------------------------------------------------------------------
CTransmogrifyUI::~CTransmogrifyUI()
{
	SAFE_DELETE(m_pIconSlotItem);
}

void CTransmogrifyUI::openUI()
{
	if (IsVisible() == TRUE)
		return;

	SetVisible(TRUE);
	Hide(FALSE);

	CUIManager * manager = CUIManager::getSingleton();

	if( ( (CPlayerEntity*)CEntity::GetPlayerEntity(0) )->IsSkilling() )
	{
		manager->GetChattingUI()->AddSysMessage( _S( 946, "" ), SYSMSG_ERROR );		
		closeUI();
		return;
	}

	if( manager->IsCSFlagOn( CSF_TELEPORT ) )
	{
		manager->GetChattingUI()->AddSysMessage( _S( 947, "" ), SYSMSG_ERROR );	
		closeUI();
		return;
	}

	if (manager->GetInventory()->IsLocked() == TRUE ||
		manager->GetInventory()->IsLockedArrange() == TRUE)
	{
		manager->GetInventory()->ShowLockErrorMessage();
		closeUI();
		return;
	}

	if( !manager->GetInventory()->IsVisible() )
		manager->GetInventory()->ToggleVisible();

	manager->RearrangeOrder( UI_TRANSMOGRIFY, TRUE );

	manager->GetInventory()->Lock(TRUE, TRUE, LOCK_TRANSMOGRIFY);
}

void CTransmogrifyUI::closeUI()
{
	// Reset slot item
	m_pIconSlotItem->clearIconData();

	CUIManager* pUIManager = CUIManager::getSingleton();

	Hide(TRUE);
	SetVisible(FALSE);

	pUIManager->RearrangeOrder( UI_TRANSMOGRIFY, FALSE );

	// Unlock inventory
	pUIManager->GetInventory()->Lock( FALSE, FALSE, LOCK_TRANSMOGRIFY );

	m_strRefineMoney.Clear();
	m_llRefineMoney = 0;
	m_bWaitRefineResult = FALSE;

	if (m_tNas != NULL)
		m_tNas->SetText(m_strRefineMoney);
}

// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CTransmogrifyUI::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CTransmogrifyUI::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

void CTransmogrifyUI::initialize()
{
	m_btnOK = (CUIButton*)findUI("btn_ok");
	
	m_btnCancel = (CUIButton*)findUI("btn_cancel");
	
	m_btnClose = (CUIButton*)findUI("btn_close");
	
	m_tNas = (CUIText*)findUI("txt_nas");

	m_tTitle = (CUIText*)findUI("title");
	if (m_tTitle != NULL)
		m_tTitle->SetText(_S( 8115, "Transmogrify" ));

	m_rcItemSlot.SetRect( 91, 0, 125, 0 );
	m_rcInsertItem.SetRect( 3, 0, 213, 0 );

	m_rcItemSlot.Top = 88;
	m_rcItemSlot.Bottom = m_rcItemSlot.Top + 34;

	m_rcInsertItem.Top = 88;
	m_rcInsertItem.Bottom = m_rcItemSlot.Top + 34;

	m_pIconSlotItem = (CUIIcon*)findUI("iconitem");
	m_pIconSlotItem->Create(this, m_rcItemSlot.Left + 1, m_rcItemSlot.Top + 1, BTN_SIZE, BTN_SIZE, UI_TRANSMOGRIFY, UBET_ITEM);
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CTransmogrifyUI::Render()
{
	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Render all elements
	pDrawPort->FlushRenderingQueue();

	// Item
	if (m_pIconSlotItem->IsEmpty() == false)
	{
		m_pIconSlotItem->Render(pDrawPort);
		pDrawPort->FlushBtnRenderingQueue( UBET_ITEM );
	}

	pDrawPort->EndTextEx();
}

// ----------------------------------------------------------------------------
// Name : MouseMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT CTransmogrifyUI::MouseMessage( MSG *pMsg )
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
			else if( m_btnClose->MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			// OK button
			else if( m_btnOK->MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			// Cancel button
			else if( m_btnCancel->MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
		}
		break;

	case WM_LBUTTONDOWN:
		{
			if( IsInside( nX, nY ) )
			{
				nOldX = nX;		nOldY = nY;

				// Close button
				if( m_btnClose->MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				// OK button
				else if( m_btnOK->MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				// Cancel button
				else if( m_btnCancel->MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}

				CUIManager::getSingleton()->RearrangeOrder( UI_TRANSMOGRIFY, TRUE );
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
				if( ( wmsgResult = m_btnClose->MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
						closeUI();

					return WMSG_SUCCESS;
				}
				// OK button
				else if( ( wmsgResult = m_btnOK->MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
						SendTransmogrifyReq();

					return WMSG_SUCCESS;
				}
				// Cancel button
				else if( ( wmsgResult = m_btnCancel->MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
						closeUI();

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
							SetTransmogrifyItem();
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
void CTransmogrifyUI::SetTransmogrifyItem()
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
		pUIManager->GetChattingUI()->AddSysMessage( _S( 232, "" ), SYSMSG_ERROR );
		return;
	}

	// If this is not weapon or armor
	CItemData	*pItemData = pItems->ItemData;
	if( (pItemData->GetType() != CItemData::ITEM_WEAPON && pItemData->GetType() != CItemData::ITEM_SHIELD) 
	|| pItems->IsFlag(FLAG_ITEM_TRANSMOGRIFY) || pItemData->IsFlag(ITEM_FLAG_COMPOSITE))
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 233, "" ), SYSMSG_ERROR );
		return;
	}

	// If refining money is short
	SLONG	slWearLevel = pItemData->GetLevel();
	m_llRefineMoney = ( ( slWearLevel + 1 ) * ( slWearLevel + 3 ) * ( slWearLevel -1 ) + 100 ) / 4;
	CTString strRefineMoney;
	strRefineMoney.PrintF("%I64d", m_llRefineMoney);
	pUIManager->InsertCommaToString(m_strRefineMoney);
	m_strRefineMoney.PrintF( _S( 419, "���� ��� : %s" ), strRefineMoney );
	m_tNas->SetText(m_strRefineMoney);

	// Insert upgrade slot
	m_pIconSlotItem->copyItem(pDrag);
}


// ========================================================================= //
//                           Send message functions                          //
// ========================================================================= //

// ----------------------------------------------------------------------------
// Name : TransmogrifyReq()
// Desc :
// ----------------------------------------------------------------------------
void CTransmogrifyUI::SendTransmogrifyReq()
{
	if( m_bWaitRefineResult == TRUE )
		return;

	CUIManager* pUIManager = CUIManager::getSingleton();

	if( ( (CPlayerEntity*)CEntity::GetPlayerEntity(0) )->IsSkilling() )
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 946, "" ), SYSMSG_ERROR );		
		return;
	}

	if( pUIManager->IsCSFlagOn( CSF_TELEPORT ) )
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 947, "" ), SYSMSG_ERROR );	
		return;
	}

	if (m_pIconSlotItem->IsEmpty() == true)
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 235, "" ), SYSMSG_ERROR );
		return;
	}

	if( m_llRefineMoney > _pNetwork->MyCharacterInfo.money )
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 369, "" ), SYSMSG_ERROR );
		return;
	}

	CItems* pItems = m_pIconSlotItem->getItems();

	if (pItems != NULL)
		_pNetwork->TransmogrifyReq((SWORD)pItems->Item_Tab, (SWORD)pItems->InvenIndex);

	m_bWaitRefineResult = TRUE;
}


// ========================================================================= //
//                         Receive message functions                         // 
// ========================================================================= //

// ----------------------------------------------------------------------------
// Name : RefineRep()
// Desc :
// ----------------------------------------------------------------------------
void CTransmogrifyUI::TransmogrifyRep( SBYTE sbResult )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// Close message box
	pUIManager->CloseMessageBox( MSGCMD_TRANSMOGRIFY_REP );

	// Show result
	CTString	strMessage;
	switch( sbResult )
	{
	case MSG_ITEM_TRANSMOGRIFY_OK:
		strMessage = _S( 8357, "Transmogrify successful!" );
		break;
	case MSG_ITEM_TRANSMOGRIFY_ERROR_WRONG_TYPE:
		strMessage = _S( 8363, "Only weapon and armor can be transmogrified" );
		break;
	case MSG_ITEM_TRANSMOGRIFY_ERROR_WEARING:
		strMessage = _S( 8362, "Please remove the item to proceed." );
		break;
	case MSG_ITEM_TRANSMOGRIFY_ERROR_NO_MONEY:
		strMessage = _S( 8364, "You don't have money" );
		break;
	}

	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 231, "Transmute" ), UMBS_OK, UI_TRANSMOGRIFY, MSGCMD_TRANSMOGRIFY_REP );
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );

	// Reset slot item
	m_pIconSlotItem->clearIconData();

	m_strRefineMoney.Clear();
	m_bWaitRefineResult = FALSE;
}
