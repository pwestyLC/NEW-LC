#include "stdh.h"

#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/LocalDefine.h>
#include <Engine/Interface/UIInventory.h>
#include "PRSRemoveUI.h"

// ----------------------------------------------------------------------------
// Name : CPRSRemoveUI()
// Desc : Constructor
// ----------------------------------------------------------------------------
CPRSRemoveUI::CPRSRemoveUI()
	: m_btnCancel(NULL)
	, m_btnOK(NULL)
	, m_btnClose(NULL)
	, m_tTitle(NULL)
{
}

// ----------------------------------------------------------------------------
// Name : ~CPRSRemoveUI()
// Desc : Destructor
// ----------------------------------------------------------------------------
CPRSRemoveUI::~CPRSRemoveUI()
{
	SAFE_DELETE(m_pIconSlotItem[0]);
	SAFE_DELETE(m_pIconSlotItem[1]);
}

void CPRSRemoveUI::openUI()
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

	manager->RearrangeOrder( UI_PRS_REMOVE, TRUE );

	manager->GetInventory()->Lock(TRUE, TRUE, LOCK_PRS_REMOVE);
}

void CPRSRemoveUI::closeUI()
{
	// Reset slot item
	m_pIconSlotItem[0]->clearIconData();
	m_pIconSlotItem[1]->clearIconData();

	CUIManager* pUIManager = CUIManager::getSingleton();

	Hide(TRUE);
	SetVisible(FALSE);

	pUIManager->RearrangeOrder( UI_PRS_REMOVE, FALSE );

	// Unlock inventory
	pUIManager->GetInventory()->Lock( FALSE, FALSE, LOCK_PRS_REMOVE );
}

// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CPRSRemoveUI::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CPRSRemoveUI::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

void CPRSRemoveUI::initialize()
{
	m_btnOK = (CUIButton*)findUI("btn_ok");
	
	m_btnCancel = (CUIButton*)findUI("btn_cancel");
	
	m_btnClose = (CUIButton*)findUI("btn_close");

	m_tTitle = (CUIText*)findUI("title");
	if (m_tTitle != NULL)
		m_tTitle->SetText(_S( 2675, "Platinum refining effects" ));

	CTString icon;
	int left = 60;
	for (int i = 0; i < 2; i++) {
		m_rcItemSlot[i].SetRect( 91, 0, 125, 0 );
		m_rcInsertItem[i].SetRect( 3, 0, 213, 0 );

		m_rcItemSlot[i].Top = 88;
		m_rcItemSlot[i].Left = left;
		m_rcItemSlot[i].Bottom = m_rcItemSlot[i].Top + 34;

		m_rcInsertItem[i].Top = 88;
		m_rcInsertItem[i].Left = left;
		m_rcInsertItem[i].Bottom = m_rcInsertItem[i].Top + 34;

		icon.PrintF("iconitem_%d", i);
		m_pIconSlotItem[i] = (CUIIcon*)findUI(icon);
		m_pIconSlotItem[i]->Create(this, m_rcItemSlot[i].Left + 1, m_rcItemSlot[i].Top + 1, BTN_SIZE, BTN_SIZE, UI_PRS_REMOVE, UBET_ITEM);

		left += 60;
	}
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CPRSRemoveUI::Render()
{
	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Render all elements
	pDrawPort->FlushRenderingQueue();

	for (int i = 0; i < 2; i++) {
		if (!m_pIconSlotItem[i]->IsEmpty()) {
			m_pIconSlotItem[i]->Render(pDrawPort);
		}
	}

	pDrawPort->FlushBtnRenderingQueue( UBET_ITEM );
	pDrawPort->EndTextEx();
}

// ----------------------------------------------------------------------------
// Name : MouseMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT CPRSRemoveUI::MouseMessage( MSG *pMsg )
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
			if ( IsInside( nX, nY ) )
				CUIManager::getSingleton()->SetMouseCursorInsideUIs();

			m_pIconSlotItem[0]->MouseMessage( pMsg );
			m_pIconSlotItem[1]->MouseMessage( pMsg );

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

				CUIManager::getSingleton()->RearrangeOrder( UI_PRS_REMOVE, TRUE );
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
						SendPRSRemoveReq();

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
						if ( IsInsideRect( nX, nY, m_rcInsertItem[0] ) )
						{
							CUIManager* pUIManager = CUIManager::getSingleton();
							CUIIcon* pDrag = pUIManager->GetDragIcon();

							if (pDrag == NULL)
								return WMSG_FAIL;

							CItems* pItems = pDrag->getItems();

							if (pItems == NULL)
								return WMSG_FAIL;
							
							CItemData* pItemData = pItems->ItemData;
							if (pItemData->getindex() == 11320)
								m_pIconSlotItem[0]->copyItem(pDrag);
							else
								pUIManager->GetChattingUI()->AddSysMessage(_S(3048, "Unable to throw away." ), SYSMSG_ERROR );
						}
						if ( IsInsideRect( nX, nY, m_rcInsertItem[1] ) )
						{
							CUIManager* pUIManager = CUIManager::getSingleton();
							CUIIcon* pDrag = pUIManager->GetDragIcon();

							if (pDrag == NULL)
								return WMSG_FAIL;

							CItems* pItems = pDrag->getItems();

							if (pItems == NULL)
								return WMSG_FAIL;
							
							CItemData* pItemData = pItems->ItemData;
							if (pItemData->GetType() == CItemData::ITEM_WEAPON || pItemData->GetType() == CItemData::ITEM_SHIELD)
							{
								int nPlatinumPlus;
								CTString strEnt;
								FLAG_ITEM_PLATINUM_GET(pItems->Item_Flag, nPlatinumPlus);
								if (nPlatinumPlus > 0) {
									m_pIconSlotItem[1]->copyItem(pDrag);
								} else {
									pUIManager->GetChattingUI()->AddSysMessage(_S(3048, "Unable to throw away." ), SYSMSG_ERROR );
								}
							} 
							else
							{
								pUIManager->GetChattingUI()->AddSysMessage(_S(3048, "Unable to throw away." ), SYSMSG_ERROR );
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
// Name : SendPRSRemoveReq()
// Desc :
// ----------------------------------------------------------------------------
void CPRSRemoveUI::SendPRSRemoveReq()
{
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

	if (m_pIconSlotItem[0]->IsEmpty() || m_pIconSlotItem[1]->IsEmpty())
	{
		pUIManager->GetChattingUI()->AddSysMessage( _S( 235, "" ), SYSMSG_ERROR );
		return;
	}

	CItems* pItemRemove = m_pIconSlotItem[0]->getItems();
	CItems* pItemArmorWeapon = m_pIconSlotItem[1]->getItems();

	if (pItemRemove != NULL && pItemArmorWeapon != NULL) {
		_pNetwork->RemovePlatinumStone( pItemArmorWeapon->Item_Tab, pItemArmorWeapon->InvenIndex );
	}

	closeUI();
}