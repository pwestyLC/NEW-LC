#include "stdh.h"

#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/LocalDefine.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Contents/Base/UIMsgBoxNumeric_only.h>
#include "SealComposeUI.h"

class CmdBoxPutOnItem : public Command
{
public:
	CmdBoxPutOnItem() : m_pWnd(NULL), m_bOk(false) {}
	void setData(CSealComposeUI* pWnd, bool bOk)	{	m_pWnd = pWnd; m_bOk = bOk;	}
	void execute()
	{
		if (m_pWnd != NULL)
		{
			if (m_bOk == true)
				m_pWnd->PutOnCallBack();
			else
				m_pWnd->PutOnCancelCallBack();
		}
	}
private:
	CSealComposeUI* m_pWnd;
	bool m_bOk;
};

// ----------------------------------------------------------------------------
// Name : CSealComposeUI()
// Desc : Constructor
// ----------------------------------------------------------------------------
CSealComposeUI::CSealComposeUI()
	: m_pIconSlotItem(NULL)
	, m_btnCancel(NULL)
	, m_btnOK(NULL)
	, m_btnClose(NULL)
	, m_tTitle(NULL)
{
	m_bWaitResult = FALSE;
}

// ----------------------------------------------------------------------------
// Name : ~CSealComposeUI()
// Desc : Destructor
// ----------------------------------------------------------------------------
CSealComposeUI::~CSealComposeUI()
{
	SAFE_DELETE(m_pIconSlotItem);
}

void CSealComposeUI::openUI()
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

	manager->RearrangeOrder( UI_SEAL_COMPOSE, TRUE );

	manager->GetInventory()->Lock(TRUE, TRUE, LOCK_SEAL_COMPOSE);

	m_pIconSlotItem->clearIconData();
}

void CSealComposeUI::closeUI()
{
	// Reset slot item
	m_pIconSlotItem->clearIconData();

	CUIManager* pUIManager = CUIManager::getSingleton();

	Hide(TRUE);
	SetVisible(FALSE);

	pUIManager->RearrangeOrder( UI_SEAL_COMPOSE, FALSE );

	// Unlock inventory
	pUIManager->GetInventory()->Lock( FALSE, FALSE, LOCK_SEAL_COMPOSE );
	m_bWaitResult = FALSE;
}

// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CSealComposeUI::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CSealComposeUI::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

void CSealComposeUI::initialize()
{
	m_btnOK = (CUIButton*)findUI("btn_ok");
	
	m_btnCancel = (CUIButton*)findUI("btn_cancel");
	
	m_btnClose = (CUIButton*)findUI("btn_close");

	m_tTitle = (CUIText*)findUI("title");
	if (m_tTitle != NULL)
		m_tTitle->SetText(_S( 8421, "Seal Compose" ));

	m_rcItemSlot.SetRect( 91, 0, 125, 0 );
	m_rcInsertItem.SetRect( 3, 0, 213, 0 );

	m_rcItemSlot.Top = 88;
	m_rcItemSlot.Bottom = m_rcItemSlot.Top + 34;

	m_rcInsertItem.Top = 88;
	m_rcInsertItem.Bottom = m_rcItemSlot.Top + 34;

	m_pIconSlotItem = (CUIIcon*)findUI("iconitem");
	m_pIconSlotItem->Create(this, m_rcItemSlot.Left + 1, m_rcItemSlot.Top + 1, BTN_SIZE, BTN_SIZE, UI_SEAL_COMPOSE, UBET_ITEM);
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CSealComposeUI::Render()
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
WMSG_RESULT CSealComposeUI::MouseMessage( MSG *pMsg )
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

				CUIManager::getSingleton()->RearrangeOrder( UI_SEAL_COMPOSE, TRUE );
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
						SendSealsComposeReq();

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
							CUIManager* pUIManager = CUIManager::getSingleton();
							CUIIcon* pDrag = pUIManager->GetDragIcon();

							if (pDrag == NULL)
								return WMSG_FAIL;

							CItems* pItems = pDrag->getItems();

							if (pItems == NULL)
								return WMSG_FAIL;

							CItemData* pItemData = pItems->ItemData;
							if (pItemData->GetType() == CItemData::ITEM_ONCEUSE && 
							  	pItemData->GetSubType() == CItemData::ITEM_SUB_SEAL)
							{
								CUIMsgBoxNumericOnly* pMsgBoxNumOnly = pUIManager->GetMsgBoxNumOnly();

								if (pMsgBoxNumOnly->IsOpen() == true)
									pMsgBoxNumOnly->CloseBox();

								int nInitCount = pItems->Item_Sum;

								if (pItems->Item_Sum > 999)
									nInitCount = 999;

								CTString strMessage = _S( 8426,"How many seals do you want to compose?");

								CmdBoxPutOnItem* pCmdOk = new CmdBoxPutOnItem;
								pCmdOk->setData(this, true);

								CmdBoxPutOnItem* pCmdCancel = new CmdBoxPutOnItem;
								pCmdCancel->setData(this, false);

								pMsgBoxNumOnly->SetInfo(pCmdOk, _S(8421, "Seal Compose"), strMessage, 1, (int)nInitCount, pCmdCancel);
								pMsgBoxNumOnly->InitData((int)nInitCount);

								{
									m_pIconSlotItem->cloneItem(pDrag);
									m_pIconSlotItem->setCount(nInitCount);
								}
							} 
							else
							{
								pUIManager->GetChattingUI()->AddSysMessage(_S( 8425, "This is not a seal item"), SYSMSG_ERROR );
								pUIManager->ResetHoldBtn();
							}
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
//                           Send message functions                          //
// ========================================================================= //

// ----------------------------------------------------------------------------
// Name : SendSealsComposeReq()
// Desc :
// ----------------------------------------------------------------------------
void CSealComposeUI::SendSealsComposeReq()
{
	if( m_bWaitResult == TRUE )
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
		_pNetwork->SealComposeReq((SWORD)pItems->Item_Tab, (SWORD)pItems->InvenIndex, pItems->Item_Sum);

	m_bWaitResult = TRUE;
}


// ========================================================================= //
//                         Receive message functions                         // 
// ========================================================================= //

// ----------------------------------------------------------------------------
// Name : SealComposeRep()
// Desc :
// ----------------------------------------------------------------------------
void CSealComposeUI::SealComposeRep( SBYTE sbResult, LONG total, CTString name)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// Close message box
	pUIManager->CloseMessageBox( MSGCMD_SEAL_COMPOSE_REP );

	// Show result
	CTString	strMessage;
	switch( sbResult )
	{
	case MSG_ITEM_SEAL_COMPOSE_OK:
		strMessage.PrintF(_S( 8424, "You created %d new seals of type %s!" ), total, name);
		break;
	case MSG_ITEM_SEAL_COMPOSE_NOSPACE:
		strMessage = _S( 8423, "There is not space available" );
		break;
	default:
		strMessage = _S( 8422, "Sorry. Something was wrong and the seals cannot be created" );
		break;
	}

	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 8421, "Seal Compose" ), UMBS_OK, UI_SEAL_COMPOSE, MSGCMD_SEAL_COMPOSE_REP );
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );

	// Reset slot item
	m_pIconSlotItem->clearIconData();

	m_bWaitResult = FALSE;
}

void CSealComposeUI::PutOnCallBack()
{
	SQUAD llData = UIMGR()->GetMsgBoxNumOnly()->GetData();

	if (llData && llData <= 999 && llData > 0)
	{
		if (llData <= m_pIconSlotItem->getItems()->Item_Sum)
		{
			m_pIconSlotItem->setCount(llData);
		}
	}
	else
	{
		UIMGR()->GetChattingUI()->AddSysMessage( _S(8420, "The max amount of seals is 999"), SYSMSG_ERROR );
		m_pIconSlotItem->clearIconData();
		return;
	}

	if (m_pIconSlotItem->IsEmpty())
		m_pIconSlotItem->setCount(llData);
}

void CSealComposeUI::PutOnCancelCallBack()
{
	if (m_pIconSlotItem->IsEmpty() == true)
		return;

	m_pIconSlotItem->clearIconData();
}