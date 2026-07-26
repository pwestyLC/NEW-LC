#include "stdh.h"

#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/LocalDefine.h>
#include <Engine/Interface/UIInventory.h>
#include "ExtendMenuUI.h"

// ----------------------------------------------------------------------------
// Name : CExtendMenuUI()
// Desc : Constructor
// ----------------------------------------------------------------------------
CExtendMenuUI::CExtendMenuUI()
	: m_pIconSlotItem(NULL)
	, m_btnCancel(NULL)
	, m_btnClose(NULL)
	, m_tTitle(NULL)
	, m_btn1Day(NULL)
	, m_btn7Day(NULL)
	, m_btn30Day(NULL)
{
	m_bWaitRefineResult = FALSE;
}

// ----------------------------------------------------------------------------
// Name : ~CExtendMenuUI()
// Desc : Destructor
// ----------------------------------------------------------------------------
CExtendMenuUI::~CExtendMenuUI()
{
	SAFE_DELETE(m_pIconSlotItem);
}

void CExtendMenuUI::openUI()
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

	manager->RearrangeOrder( UI_EXTEND_MENU, TRUE );

	manager->GetInventory()->Lock(TRUE, TRUE, LOCK_EXTEND_MENU);

	m_pIconSlotItem->clearIconData();
}

void CExtendMenuUI::closeUI()
{
	// Reset slot item
	m_pIconSlotItem->clearIconData();

	CUIManager* pUIManager = CUIManager::getSingleton();

	Hide(TRUE);
	SetVisible(FALSE);

	pUIManager->RearrangeOrder( UI_EXTEND_MENU, FALSE );

	// Reset slot item
	m_pIconSlotItem->clearIconData();

	// Unlock inventory
	pUIManager->GetInventory()->Lock( FALSE, FALSE, LOCK_EXTEND_MENU );

	m_bWaitRefineResult = FALSE;
}

// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CExtendMenuUI::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CExtendMenuUI::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

void CExtendMenuUI::initialize()
{	
	m_btn1Day = (CUIButton*)findUI("btn1day");

	m_btn7Day = (CUIButton*)findUI("btn7day");
	
	m_btn30Day = (CUIButton*)findUI("btn30day");
	
	m_btnCancel = (CUIButton*)findUI("btn_cancel");

	m_btnClose = (CUIButton*)findUI("btn_close");
	
	if (m_tTitle = (CUIText*)findUI("title"))
		m_tTitle->SetText(_S( 8131, "Extender" ));

	m_rcItemSlot.SetRect( 91, 0, 125, 0 );
	m_rcInsertItem.SetRect( 3, 0, 213, 0 );

	m_rcItemSlot.Top = 88;
	m_rcItemSlot.Bottom = m_rcItemSlot.Top + 34;

	m_rcInsertItem.Top = 88;
	m_rcInsertItem.Bottom = m_rcItemSlot.Top + 34;

	m_pIconSlotItem = (CUIIcon*)findUI("iconitem");
	m_pIconSlotItem->Create(this, m_rcItemSlot.Left + 1, m_rcItemSlot.Top + 1, BTN_SIZE, BTN_SIZE, UI_TRANSMOGRIFY, UBET_ITEM);
	m_pIconSlotItem->clearIconData();
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CExtendMenuUI::Render()
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
WMSG_RESULT CExtendMenuUI::MouseMessage( MSG *pMsg )
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
			else if( m_btnClose->MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnCancel->MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btn1Day->MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btn7Day->MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btn30Day->MouseMessage( pMsg ) != WMSG_FAIL )
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
				else if( m_btnCancel->MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				} else if( m_btn1Day->MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				} else if( m_btn7Day->MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				} else if( m_btn30Day->MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}

				CUIManager::getSingleton()->RearrangeOrder( UI_EXTEND_MENU, TRUE );
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

				if( ( wmsgResult = m_btnClose->MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
						closeUI();

					return WMSG_SUCCESS;
				}
				else if( ( wmsgResult = m_btn1Day->MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
						SendExtendMenuReq(1);

					return WMSG_SUCCESS;
				}
				else if( ( wmsgResult = m_btn7Day->MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
						SendExtendMenuReq(7);

					return WMSG_SUCCESS;
				}
				else if( ( wmsgResult = m_btn30Day->MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
						SendExtendMenuReq(30);

					return WMSG_SUCCESS;
				}
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
							SetExtendMenuItem();
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
// Name : SetExtendMenuItem()
// Desc :
// ----------------------------------------------------------------------------
void CExtendMenuUI::SetExtendMenuItem()
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
	if( pItemData->GetType() != CItemData::ITEM_WEAPON &&
		pItemData->GetType() != CItemData::ITEM_SHIELD)
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 233, "" ), SYSMSG_ERROR );
		return;
	}
	if (!pItems->IsFlag(FLAG_ITEM_TRANSMOGRIFY) && !pItemData->IsFlag(ITEM_FLAG_COMPOSITE))
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 233, "" ), SYSMSG_ERROR );
		return;
	}

	// Insert upgrade slot
	m_pIconSlotItem->copyItem(pDrag);
}

// ----------------------------------------------------------------------------
// Name : SendExtendMenuReq()
// Desc :
// ----------------------------------------------------------------------------
void CExtendMenuUI::SendExtendMenuReq(int days)
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

	CItems* pItems = m_pIconSlotItem->getItems();

	if (pItems != NULL)
	{
		_pNetwork->ExtendMenuReq((SWORD)pItems->Item_Tab, (SWORD)pItems->InvenIndex, days);
		m_bWaitRefineResult = TRUE;
	}
}


// ========================================================================= //
//                         Receive message functions                         // 
// ========================================================================= //

// ----------------------------------------------------------------------------
// Name : RefineRep()
// Desc :
// ----------------------------------------------------------------------------
void CExtendMenuUI::ExtendMenuRep( SBYTE sbResult )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// Close message box
	pUIManager->CloseMessageBox( MSGCMD_EXTEND_MENU_REP );

	// Show result
	CTString	strMessage;
	switch( sbResult )
	{
	case MSG_ITEM_EXTEND_MENU_OK:
		strMessage = _S( 8358, "Item extended successful!" );
		break;
	case MSG_ITEM_EXTEND_MENU_ERROR_COUNT:
		strMessage = _S( 5708, "You don't have this amount of the items!" );
		break;
	case MSG_ITEM_EXTEND_MENU_ERROR_NO_ITEM:
		strMessage = _S( 8360, "You don't have the Costume Duration Extender" );
		break;
	case MSG_ITEM_EXTEND_MENU_ERROR_WRONG_TYPE:
		strMessage = _S( 8361, "Only costumes can be extended" );
		break;
	case MSG_ITEM_EXTEND_MENU_ERROR_WEARING:
		strMessage = _S( 8362, "Please remove the item to proceed." );
		break;
	}

	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 8353, "Extender" ), UMBS_OK, UI_EXTEND_MENU, MSGCMD_EXTEND_MENU_REP );
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );

	m_bWaitRefineResult = FALSE;
}
