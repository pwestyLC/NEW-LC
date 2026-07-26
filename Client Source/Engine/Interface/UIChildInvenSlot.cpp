#include "stdh.h"
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Interface/UIQuickSlot.h>
#include <Engine/Interface/UIChildQuickSlot.h>
#include "UIChildInvenSlot.h"
#include <Engine/Contents/Base/InvenData.h>
#include <Engine/Interface/UIReformSystem.h>
#include <Engine/Contents/function/InsectCollectUI.h>
#include <Engine/Contents/function/WareHouseUI.h>
#include <Engine/Interface/UIMix.h>
#include <Engine/Contents/function/CompoundUI.h>
#include <Engine/Contents/function/GuildWarMixUI.h>
#ifdef EXPANSION_INVENTORY
#include <Engine/Interface/UIInvenCashBag.h>
#endif
//#include <Engine/GameState.h>
extern INDEX g_iXPosInInvenSlot1;
extern INDEX g_iYPosInInvenSlot1;
extern INDEX g_iXPosInInvenSlot2;
extern INDEX g_iYPosInInvenSlot2;
extern INDEX g_iXPosInInvenSlot3;
extern INDEX g_iYPosInInvenSlot3;

enum EInvenTex
{
	EInvenNormalSelect,
		EInvenWearSelect,
		EInvenMixing,
		EInvenSealed,
		EInvenLeaseMark,
		EInvenTotal,
};

// ----------------------------------------------------------------------------
// Name : CUIChildInvenSlot()
// Desc : Constructorreturn ;
// ----------------------------------------------------------------------------
CUIChildInvenSlot::CUIChildInvenSlot(int _bag_index) 
: m_pAllItem(NULL)
, m_nIndexBag(_bag_index)
, m_pImgSelect(NULL)
{
	m_bPickTitle = FALSE;
	m_nSelSlotItemID = -1;
	m_NewItemEffectSurface.Clear();
	ClearNewItemEffect();
}

// ----------------------------------------------------------------------------
// Name : ~CUIChildInvenSlot()
// Desc : Destructor
// ----------------------------------------------------------------------------
CUIChildInvenSlot::~CUIChildInvenSlot()
{
	Destroy();

	if (m_ptdCommonTexture)
	{
		_pTextureStock->Release(m_ptdCommonTexture);
		m_ptdCommonTexture = NULL;
	}
	if (m_ptdBaseTexture)
	{
		_pTextureStock->Release(m_ptdBaseTexture);
		m_ptdBaseTexture = NULL;
	}
	if (m_ptdBGSlotTexture)
	{
		_pTextureStock->Release(m_ptdBGSlotTexture);
		m_ptdBGSlotTexture = NULL;
	}
	if (m_pAllItem)
	{
		m_pAllItem = NULL;
	}

	SAFE_DELETE(m_pImgSelect);
}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------

void CUIChildInvenSlot::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight )
{
#ifdef EXPANSION_INVENTORY
	if (nHeight == INVEN_CASH_BAG_NEW_H)
		CUIWindow::Create(pParentWnd, nX, nY, ITEM_SLOT_TOTAL_WIDTH, ITEM_SLOT_TOTAL_NEW_HEIGHT);
	else
#endif
		CUIWindow::Create(pParentWnd, nX, nY, ITEM_SLOT_TOTAL_WIDTH, ITEM_SLOT_TOTAL_HEIGHT);
	
	// UI���� �κ��丮 [10/4/2012 Ranma]
	m_ptdBGSlotTexture = CreateTexture(CTString("Data\\Interface\\new_PetInfo.tex"));
	FLOAT fTexWidth = m_ptdBGSlotTexture->GetPixWidth();
	FLOAT fTexHeight = m_ptdBGSlotTexture->GetPixHeight();
	
	// Region of each part
	m_rcTitle.SetRect(0, 0, ITEM_SLOT_TOTAL_WIDTH, ITEM_SLOT_TITLE_HEIGHT);
#ifdef EXPANSION_INVENTORY
	if (nHeight == INVEN_CASH_BAG_NEW_H)
		m_rcItemSlot.SetRect(ITEM_SLOT_SX, ITEM_SLOT_SY, ITEM_SLOT_SX + ITEM_SLOT_WIDTH, ITEM_SLOT_SY + ITEM_SLOT_NEW_HEIGHT);
	else
		m_rcItemSlot.SetRect(ITEM_SLOT_SX, ITEM_SLOT_SY, ITEM_SLOT_SX + ITEM_SLOT_WIDTH, ITEM_SLOT_SY + ITEM_SLOT_HEIGHT);
#else
	m_rcItemSlot.SetRect(ITEM_SLOT_SX, ITEM_SLOT_SY, ITEM_SLOT_SX + ITEM_SLOT_WIDTH, ITEM_SLOT_SY + ITEM_SLOT_HEIGHT);
#endif

	
	m_rsItemSlotSurface.AddRectSurface(UIRect(0, 0, ITEM_SLOT_TOTAL_WIDTH, ITEM_SLOT_TITLE_HEIGHT),
		UIRectUV(ITEM_SLOT_TITLE_UV_SX, ITEM_SLOT_TITLE_UV_SY, ITEM_SLOT_TITLE_UV_WIDTH, ITEM_SLOT_TITLE_UV_HEIGHT,fTexWidth,fTexHeight)); // ��� Ÿ��Ʋ
	
	m_rsItemSlotSurface.AddRectSurface(UIRect(ITEM_SLOT_MIDDLE_SX, ITEM_SLOT_MIDDLE_SY, ITEM_SLOT_TOTAL_WIDTH, ITEM_SLOT_MIDDLE_SY + ITEM_SLOT_MIDDLE_HEIGHT),
		UIRectUV(ITEM_SLOT_MIDDLE_UV_SX, ITEM_SLOT_MIDDLE_UV_SY, ITEM_SLOT_MIDDLE_UV_WIDTH, ITEM_SLOT_MIDDLE_UV_HEIGHT,fTexWidth,fTexHeight)); // ��� �̵�
	
	m_rsItemSlotSurface.AddRectSurface(UIRect(ITEM_SLOT_BOTTOM_SX, ITEM_SLOT_BOTTOM_SY, ITEM_SLOT_TOTAL_WIDTH, ITEM_SLOT_BOTTOM_SY + ITEM_SLOT_BOTTOM_HEIGHT),
		UIRectUV(ITEM_SLOT_BOTTOM_UV_SX, ITEM_SLOT_BOTTOM_UV_SY, ITEM_SLOT_BOTTOM_UV_WIDTH, ITEM_SLOT_BOTTOM_UV_HEIGHT,fTexWidth,fTexHeight)); // ��� ����
	
	// Create inventory texture
	m_ptdBaseTexture = CreateTexture(CTString("Data\\Interface\\NewInventory.tex"));
	fTexWidth = m_ptdBaseTexture->GetPixWidth();
	fTexHeight = m_ptdBaseTexture->GetPixHeight();
	
#ifdef EXPANSION_INVENTORY
	if (nHeight == INVEN_CASH_BAG_NEW_H)
		m_rcItemSlotUV.SetUV(ITEM_SLOT_UV_SX, ITEM_SLOT_UV_SY, ITEM_SLOT_UV_WIDTH, ITEM_SLOT_UV_NEW_HEIGHT, fTexWidth, fTexHeight);
	else
		m_rcItemSlotUV.SetUV(ITEM_SLOT_UV_SX, ITEM_SLOT_UV_SY, ITEM_SLOT_UV_WIDTH, ITEM_SLOT_UV_HEIGHT, fTexWidth, fTexHeight); // ��� ���� UV
#else
	m_rcItemSlotUV.SetUV(ITEM_SLOT_UV_SX, ITEM_SLOT_UV_SY, ITEM_SLOT_UV_WIDTH, ITEM_SLOT_UV_HEIGHT, fTexWidth, fTexHeight); // ��� ���� UV
#endif

	m_SlotInvenSurface.AddRectSurface(UIRect(0,0,0,0), UIRectUV(3,441,36,474,fTexWidth,fTexHeight)); // �κ� ������ ���� �����̹���
	m_SlotInvenSurface.AddRectSurface(UIRect(0,0,0,0), UIRectUV(41,441,74,474,fTexWidth,fTexHeight)); // �κ� ��� ���� �����̹���
	m_SlotInvenSurface.AddRectSurface(UIRect(0,0,0,0), UIRectUV(79,441,112,474,fTexWidth,fTexHeight)); // �κ� ���� ���� ��ư �̹���
	m_SlotInvenSurface.AddRectSurface(UIRect(0,0,0,0), UIRectUV(117,441,150,474,fTexWidth,fTexHeight)); // �κ� ���� ���� ��ư �̹���
	m_SlotInvenSurface.AddRectSurface(UIRect(0,0,0,0), UIRectUV(173,421,184,432,fTexWidth,fTexHeight)); // �κ� �뿩 ��ũ �̹���
	
	m_NewItemEffectSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(157, 441, 191, 475, fTexWidth, fTexHeight)); // ���� ������ ������ ������ �����̹���
	
	m_ptdCommonTexture = CreateTexture(CTString("Data\\Interface\\CommonBtn.tex"));
	fTexWidth = m_ptdCommonTexture->GetPixWidth();
	fTexHeight = m_ptdCommonTexture->GetPixHeight();
	
	m_btnClose.Create(this, CTString(""), ITEM_SLOT_TOTAL_WIDTH - CLOSE_BTN_SIZE - CLOSE_BTN_WIDTH_GAP, 4, CLOSE_BTN_SIZE, CLOSE_BTN_SIZE);
	m_btnClose.SetUV(UBS_IDLE, 211, 33, 226, 48, fTexWidth, fTexHeight);
	m_btnClose.SetUV(UBS_CLICK, 229, 33, 244, 48, fTexWidth, fTexHeight);
	m_btnClose.CopyUV(UBS_IDLE, UBS_ON);
	m_btnClose.CopyUV(UBS_IDLE, UBS_DISABLE);

	m_pImgSelect = UISUPPORT()->clone_Image(eIMG_TYPE_SELECT);
	m_pImgSelect->setParent(this);
	m_pImgSelect->Hide(TRUE);
}

// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUIChildInvenSlot::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

void CUIChildInvenSlot::ResetSavePosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );

	switch( m_nRearrangeOrderID )
	{
	case UI_INVEN_SLOT1:
		{
			g_iXPosInInvenSlot1 = GetPosX();
			g_iYPosInInvenSlot1 = GetPosY();
			break;	
		}
	case UI_INVEN_SLOT2:
		{
			g_iXPosInInvenSlot2 = GetPosX();
			g_iYPosInInvenSlot2 = GetPosY();
			break;	
		}
	case UI_INVEN_SLOT3:
		{
			g_iXPosInInvenSlot3 = GetPosX();
			g_iYPosInInvenSlot3 = GetPosY();
			break;	
		}
	}	
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUIChildInvenSlot::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CUIChildInvenSlot::Render()
{
	
	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();
	
	m_SlotInvenSurface.SetPos(m_nPosX, m_nPosY);
	m_NewItemEffectSurface.SetPos(m_nPosX, m_nPosY);

	// ��׶��� ����//////////////////
	pDrawPort->InitTextureData( m_ptdBGSlotTexture );
	
	m_rsItemSlotSurface.SetPos(m_nPosX, m_nPosY);
	m_rsItemSlotSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF);
	pDrawPort->FlushRenderingQueue();
	
	pDrawPort->EndTextEx();
	///////////////////////////////////

	CTString strTitle;
	//COLOR	 colStrTemp;
	if(m_nRearrangeOrderID == UI_INVEN_SLOT1)
		strTitle =  _S(5780,"2������");
	else if(m_nRearrangeOrderID == UI_INVEN_SLOT2)
		strTitle =  _S(5781,"3������");
	else
		strTitle =  _S(5782,"4������");
	
	pDrawPort->PutTextExCX( strTitle, m_nPosX+ITEM_SLOT_TOTAL_WIDTH/2, m_nPosY+17, 0xFFFFFFFF );
	pDrawPort->EndTextEx();
	
	// ������ ���� ����////////////////
	pDrawPort->InitTextureData( m_ptdBaseTexture );
	
	pDrawPort->AddTexture( m_nPosX + m_rcItemSlot.Left, m_nPosY + m_rcItemSlot.Top, m_nPosX + m_rcItemSlot.Right, m_nPosY + m_rcItemSlot.Bottom,
		m_rcItemSlotUV.U0, m_rcItemSlotUV.V0, m_rcItemSlotUV.U1, m_rcItemSlotUV.V1, 0xFFFFFFFF );
	pDrawPort->FlushRenderingQueue();
	
	pDrawPort->EndTextEx();
	////////////////////////////////////
	
	// ������ ���� ����////////////////
	pDrawPort->InitTextureData( m_ptdCommonTexture );
	m_btnClose.Render();
	pDrawPort->FlushRenderingQueue();
	
	pDrawPort->EndTextEx();
	////////////////////////////////////
	ItemRender();
	PostRender();
	///////////////////////////////////////////
}

void CUIChildInvenSlot::ItemRender()
{
	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();
	// ������ ���� /////////////////////
	int i, t = GetChildInvenTab();
	#ifdef EXPANSION_INVENTORY
    int bagTotal = INVEN_ONE_BAG;
    if (IsCashBag(t))
        bagTotal = INVEN_ONE_NEW_BAG;
    for (i = 0; i < bagTotal; ++i)
    #else
    for (i = 0; i < INVEN_ONE_BAG; ++i)
    #endif

	{
		if (IsPlayNewItemEffect(i) == TRUE)
		{
			CInvenData* pInven = CInvenData::getSingleton();

			if (pInven)
			{
				if (pInven->IsNewItemEffectRender() == TRUE &&
					IsCheckEffectPlayCount(i) == TRUE)
				{
					(*m_pAllItem)[t][GetChildInvenIdx(i)]->setImageHide(eIMG_TYPE_NEW, FALSE);
				}
				else
				{
					(*m_pAllItem)[t][GetChildInvenIdx(i)]->setImageHide(eIMG_TYPE_NEW, TRUE);
				}
			}
		}

		(*m_pAllItem)[t][GetChildInvenIdx(i)]->Render(pDrawPort);
	}

	pDrawPort->EndTextEx();

	pDrawPort->FlushRenderingQueue();

	if (m_pImgSelect != NULL)
		m_pImgSelect->Render(pDrawPort);
}

// ----------------------------------------------------------------------------
// Name : MouseMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT	CUIChildInvenSlot::MouseMessage( MSG *pMsg )
{
	WMSG_RESULT	wmsgResult;
	// Title bar
	static BOOL bLButtonClick = FALSE;
	
	// Item clicked
	static BOOL	bLButtonDownInItem = FALSE;
	
	// Mouse point
	static int	nOldX, nOldY;
	int	nX = LOWORD( pMsg->lParam );
	int	nY = HIWORD( pMsg->lParam );
	
	switch( pMsg->message )
	{
	case WM_MOUSEMOVE:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();
			
			int	ndX = nX - nOldX;
			int	ndY = nY - nOldY;
			
			if( IsInside( nX, nY ) )
				pUIManager->SetMouseCursorInsideUIs();
			
			// Move UI window.
			if( m_bPickTitle && ( pMsg->wParam & MK_LBUTTON ) )
			{
				nOldX = nX;	nOldY = nY;
				
				Move( ndX, ndY );
				return WMSG_SUCCESS;
			}
			// Close button
			else if( m_btnClose.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else
			{
				int i, t = GetChildInvenTab();
#ifdef EXPANSION_INVENTORY
				int bagTotal = INVEN_ONE_BAG;
				if (IsCashBag(t))
					bagTotal = INVEN_ONE_NEW_BAG;
				for (i = 0; i < bagTotal; ++i)
#else
				for (i = 0; i < INVEN_ONE_BAG; ++i)
#endif

				{
					(*m_pAllItem)[t][GetChildInvenIdx(i)]->MouseMessage(pMsg);
				}
			}
			
			// Hold item button
			if (pUIManager->GetDragIcon() == NULL && bLButtonDownInItem && 
				(pMsg->wParam& MK_LBUTTON) && (ndX != 0 || ndY != 0))
			{
				if (pUIManager->GetInventory()->IsLocked() == FALSE)
				{
					// Slot items
					if( m_nSelSlotItemID >= 0 )
					{
						// Close message box of inventory
						pUIManager->CloseMessageBox( MSGCMD_DROPITEM );
											
						pUIManager->SetHoldBtn((*m_pAllItem)[GetChildInvenTab()][m_nSelSlotItemID]);
						
						if(pUIManager->DoesUIExist(UI_REFORM_SYSTEM))
						{
							// ���� �����̰� ���� �� ������ �̵��� �߻��� ��� �˻� �ϱ� ���� ���� �ش�. [9/6/2012 Ranma]
							pUIManager->GetReformSystem()->SendReformItemBtnInitUniIndex(
								_pNetwork->MySlotItem[GetChildInvenTab()][m_nSelSlotItemID].Item_UniIndex);
						}
					}
				}
				
				bLButtonDownInItem = FALSE;
			}
			
			if( IsInside( nX, nY ) )
			{
				return WMSG_SUCCESS;
			}
		}
		break;
		
	case WM_LBUTTONDOWN:
		{
			if( IsInside( nX, nY ) )
			{
				CUIManager* pUIManager = CUIManager::getSingleton();
				
				nOldX = nX;		nOldY = nY;
				
				bLButtonClick = TRUE;
				
				if( m_btnClose.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					
				}
				else if( IsInsideRect( nX, nY, m_rcTitle ) )
				{
					m_bPickTitle = TRUE;
				}			
				else if( IsInsideRect( nX, nY, m_rcItemSlot ) )
				{					
					CUIManager* pUIManager = CUIManager::getSingleton();

					int i, t = GetChildInvenTab();

					if (m_nSelSlotItemID >= 0)
					{
						(*m_pAllItem)[t][m_nSelSlotItemID]->setImageHide(eIMG_TYPE_SELECT, TRUE);
					}

					m_nSelSlotItemID = -1;

					#ifdef EXPANSION_INVENTORY
					int bagTotal = INVEN_ONE_BAG;
					if (IsCashBag(t))
						bagTotal = INVEN_ONE_NEW_BAG;
					for (i = 0; i < bagTotal; ++i)
					#else
					for (i = 0; i < INVEN_ONE_BAG; ++i)
					#endif
					{
						// Update selected item
						if (pUIManager->GetInventory()->IsLockSelect() == true)
							break;

						if ((*m_pAllItem)[t][GetChildInvenIdx(i)]->IsInside(nX, nY))
						{
							m_nSelSlotItemID = GetChildInvenIdx(i);
							pUIManager->GetInventory()->SetCurSelectItem((*m_pAllItem)[t][GetChildInvenIdx(i)]);
							UpdateSelectItem();
							if (pMsg->wParam & MK_CONTROL)
							{
								CItems* pItems = (*m_pAllItem)[t][GetChildInvenIdx(i)]->getItems();
								if (pItems && pItems->ItemData)
									CUIManager::getSingleton()->GetChattingUI()->GluingMessage(pItems);
							}
							UpdateSelectItem();
						}

						if( (*m_pAllItem)[t][GetChildInvenIdx(i)]->MouseMessage( pMsg ) != WMSG_FAIL )
						{
							bLButtonDownInItem = TRUE;

							if( pUIManager->GetInsectCollect()->GetHide() == FALSE )
							{// ���� ä�� ���ڴ� ������ �ݴ´�.
								pUIManager->RearrangeOrder( UI_INSECTCOLLECT, FALSE );
								pUIManager->GetInsectCollect()->Hide(TRUE);
							}

							pUIManager->RearrangeOrder( m_nRearrangeOrderID, TRUE );
							return WMSG_SUCCESS;
						}
					}
				}
				
				pUIManager->RearrangeOrder( m_nRearrangeOrderID, TRUE );
				return WMSG_SUCCESS;
			}
		}	
		break;
		
	case WM_LBUTTONUP:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();
			
			bLButtonClick = FALSE;
			bLButtonDownInItem = FALSE;
			CTString	strMessage;
			
			pUIManager->GetInventory()->SetSelWearItemID(-1);

			// If holding button doesn't exist
			if (pUIManager->GetDragIcon() == NULL)
			{
				// Title bar
				m_bPickTitle = FALSE;
				
				// If inventory isn't focused
				if( !IsFocused() )
					return WMSG_FAIL;

				// Close button
				if( ( wmsgResult = m_btnClose.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						// nothing
						switch( m_nRearrangeOrderID )
						{
						case UI_INVEN_SLOT1:
							{
								pUIManager->GetInventory()->SetTabSlotInfo(FALSE, 0);
							}
							break;	
						case UI_INVEN_SLOT2:
							{
								pUIManager->GetInventory()->SetTabSlotInfo(FALSE, 1);
							}
							break;	
						case UI_INVEN_SLOT3:
							{
								pUIManager->GetInventory()->SetTabSlotInfo(FALSE, 2);	
							}
							break;
						case UI_INVEN_CASH1:
							{
								pUIManager->GetInventory()->SetTabSlotInfo(FALSE, INVENSLOT_CASH1);
							}
							break;
						case UI_INVEN_CASH2:
							{
								pUIManager->GetInventory()->SetTabSlotInfo(FALSE, INVENSLOT_CASH2);
							}
							break;
						case UI_INVEN_CASH3:
							{
								pUIManager->GetInventory()->SetTabSlotInfo(FALSE, INVENSLOT_CASH3);
							}
							break;	
						case UI_INVEN_CASH4:
							{
								pUIManager->GetInventory()->SetTabSlotInfo(FALSE, INVENSLOT_CASH4);
							}
							break;
							//dethunter12 add
						case UI_INVEN_CASH5:
						{
							pUIManager->GetInventory()->SetTabSlotInfo(FALSE, INVENSLOT_CASH5);
						}
						break;
						case UI_INVEN_CASH6:
						{
							pUIManager->GetInventory()->SetTabSlotInfo(FALSE, INVENSLOT_CASH6);
						}
						break;
						}
					}
					
					return WMSG_SUCCESS;
				}

				// Slot items
				else if (IsInsideRect(nX, nY, m_rcItemSlot))
				{
					int i, t = GetChildInvenTab();
#ifdef EXPANSION_INVENTORY
					int bagTotal = INVEN_ONE_BAG;
					if (IsCashBag(t))
						bagTotal = INVEN_ONE_NEW_BAG;
					for (i = 0; i < bagTotal; ++i)
#else
					for (i = 0; i < INVEN_ONE_BAG; ++i)
#endif
						(*m_pAllItem)[t][GetChildInvenIdx(i)]->MouseMessage(pMsg);

					return WMSG_SUCCESS;
				}

			}
			// If holding button exists
			else
			{
				if( IsInside( nX, nY ) )
				{
					CUIIcon* pDrag = pUIManager->GetDragIcon();
					// If holding button is item and comes from inventory
					if (pUIManager->GetDragIcon()->getBtnType() == UBET_ITEM &&
						pUIManager->GetDragIcon()->GetWhichUI() == UI_INVENTORY)
					{					
						// Slot items
						if( IsInsideRect( nX, nY, m_rcItemSlot ) )
						{							
							// Swap
							int i, t = GetChildInvenTab();
#ifdef EXPANSION_INVENTORY
							int bagTotal = INVEN_ONE_BAG;
							if (IsCashBag(t))
								bagTotal = INVEN_ONE_NEW_BAG;
							for (i = 0; i < bagTotal; ++i)
							#else
							for (i = 0; i < INVEN_ONE_BAG; ++i)
							#endif
							{
								if ((*m_pAllItem)[t][GetChildInvenIdx(i)]->IsInside(nX, nY))
								{
									CItems* pItems = pUIManager->GetDragIcon()->getItems();

									if (pItems == NULL)
										return WMSG_FAIL;

									int nVIdx = pItems->Item_UniIndex;

									if (nVIdx == -1 || 
										nVIdx != _pNetwork->MySlotItem[t][GetChildInvenIdx(i)].Item_UniIndex)
									{
										CUIInventory* pInven = pUIManager->GetInventory();
										// ĳ�� �κ��� ��� ������ �̵����� ���� üũ, GetchildInvenTab() == 0 : �Ϲ� �κ� GetchildInvenTab() > 0 ĳ�� �κ�.
										int nRetMovable = pInven->IsCashInvenMoveItem(pItems->Item_Tab, pItems->InvenIndex, 
											t, GetChildInvenIdx(i));

										if (nRetMovable > eERR_NONE)
										{
											pInven->ErrMessage(nRetMovable);
											pUIManager->ResetHoldBtn();
											return WMSG_SUCCESS;
										}

										if (pUIManager->GetDragIcon()->IsWearTab() == true)
										{
											if (pUIManager->GetInventory()->IsCostumeInventory() == TRUE)
											{
												int nVirIdx = pItems->Item_UniIndex;
												CItemData* pItemData = pItems->ItemData;

												SBYTE subType = MSG_ITEM_WEAR_COSTUME_TAKEOFF;

												if (pItemData == NULL)
													return WMSG_SUCCESS;

												if (_pNetwork->MyCharacterInfo.bOneSuit == TRUE)
												{
													subType = MSG_ITEM_WEAR_COSTUME_SUIT_TAKEOFF;
												}

												if (pUIManager->GetInventory()->IsLockedArrange() == FALSE)
												{
													_pNetwork->SendItemWearingMSG(subType, pItems->Item_Wearing,
														t, GetChildInvenIdx(i), 0, nVirIdx);
												}
																			
											}
											else
											{
												if (pUIManager->GetInventory()->IsLockedArrange() == FALSE)
												{
													_pNetwork->SendItemWearingMSG(MSG_ITEM_WEAR_TAKE_OFF, pItems->Item_Wearing,
														t, GetChildInvenIdx(i), 0);
												}												
											}
										}
										else
										{
											if (pMsg->wParam & MK_SHIFT)							
											{
												if (pInven->IsLocked() == FALSE)
												{
													if (pInven->IsDivideItem(pItems->Item_Tab, pItems->InvenIndex, 
														t, GetChildInvenIdx(i)) == true)
													{
														pInven->ShowDivideMsgBox(t, GetChildInvenIdx(i));
													}
												}
											}
											else
											{
												pInven->SendSwapSlotItems(pItems->Item_Tab, pItems->InvenIndex,
													t, GetChildInvenIdx(i) );
											}
										}
									}
									// Reset holding button
									pUIManager->ResetHoldBtn();

									return WMSG_SUCCESS;
								} // inside
							}
						}
						
					}
					else if( pDrag->getBtnType() == UBET_ITEM &&
						pDrag->GetWhichUI() == UI_WARE_HOUSE )
					{
						// Slot items
						if (IsInsideRect(nX, nY, m_rcItemSlot))
						{
							pUIManager->GetWareHouseUI()->DelWareHouseItemToInventory();							
						} // If - Slot items
					}
					else if( pDrag->getBtnType() == UBET_ITEM &&
						pDrag->GetWhichUI() == UI_WILDPET_INFO)
					{
						// Slot items
						if( IsInsideRect( nX, nY, m_rcItemSlot ) )
						{
							CItems* pItems = pDrag->getItems();

							if (pItems != NULL)
							{
								_pNetwork->SendUseWildPetItem(pItems->Item_Wearing, -1, -1, 
									pDrag->getIndex());
							}
						} // If - Slot items
						
					}
					// Reset holding button
					pUIManager->ResetHoldBtn();
					
					return WMSG_SUCCESS;
				} // If - IsInside
			} // If - If holding button doesn't exist
		}
		break;
		
	case WM_LBUTTONDBLCLK:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();
			
			if( IsInside( nX, nY ) )
			{
				// Slot items(������ �κ� ���� Ŭ����...)
				if (pUIManager->GetInventory()->IsLocked() == FALSE && IsInsideRect( nX, nY, m_rcItemSlot ))
				{
					m_nSelSlotItemID = -1;
					
					int i, t = GetChildInvenTab();
					#ifdef EXPANSION_INVENTORY
					int bagTotal = INVEN_ONE_BAG;
					if (IsCashBag(t))
						bagTotal = INVEN_ONE_NEW_BAG;
					for (i = 0; i < bagTotal; ++i)
					#else
					for (i = 0; i < INVEN_ONE_BAG; ++i)
					#endif
					{	
						if ((*m_pAllItem)[t][GetChildInvenIdx(i)]->MouseMessage(pMsg) == WMSG_COMMAND)
						{
							// Close message box of inventory
							pUIManager->CloseMessageBox( MSGCMD_DROPITEM );
								
							// [090609: selo] : �������� Flag�� ����ƮFlag�� ��� �Ѵٸ�
							//					��ġ�� ����� ���� ��� ���� �ȿ� ���� ���� ������ 
							//					������ �޽����� ������ �ʴ´�.								
							if(pUIManager->GetInventory()->IsRestritionItem(t, GetChildInvenIdx(i)))
							{
								// [090707: selo] : ������ �޽����� ������ ���� ��� ������ ��� ���� �޽��� �ڽ��� ���
								CTString strTitle;
								CTString strMessage1;
								CUIMsgBox_Info	MsgBoxInfo;
									
								strTitle	=	_S(191,"Ȯ��");
								strMessage1	=	_S( 4428, "���⼭�� ��� �� �� �����ϴ�" ); 
								MsgBoxInfo.SetMsgBoxInfo(strTitle,UMBS_OK,UI_NONE,MSGCMD_NULL);
								MsgBoxInfo.AddString(strMessage1);
								pUIManager->CreateMessageBox(MsgBoxInfo);
									
								return WMSG_SUCCESS;
							}
								
								
							// �̱�ȯ ���� (12.9) ����â�� Ȱ��ȭ �Ǿ� ���� ���� ����â���� �������� ���� 
							if( pUIManager->GetMix()->IsEnabled() && pUIManager->GetMix()->IsVisible() )
							{	
								pUIManager->SetHoldBtn((*m_pAllItem)[t][GetChildInvenIdx(i)]);									
								pUIManager->GetMix()->SetMixItem ();
							}
							else if( pUIManager->GetCompound()->IsEnabled() && pUIManager->GetCompound()->IsVisible() )
							{
								pUIManager->SetHoldBtn((*m_pAllItem)[t][GetChildInvenIdx(i)]);								
								pUIManager->GetCompound()->SetCompoundItem ();
							}
							else if( pUIManager->GetGWMix()->IsEnabled() && pUIManager->GetGWMix()->IsVisible() )
							{
								pUIManager->SetHoldBtn((*m_pAllItem)[t][GetChildInvenIdx(i)]);									
								pUIManager->GetGWMix()->SetMixItem();
							}
							else
							{
								// [2012/04/20 : Sora]  �κ��丮 lock ���¿����� ����Ŭ����
								// SetUseItemSlotInfo�Լ��� �����Ͽ� ���� ���� �����۰�
								// ���̰� �߻�, �ش� ���� ����(ITS 8280)
								if (pUIManager->GetInventory()->IsLocked() == FALSE &&
									pUIManager->GetInventory()->IsLockedArrange() == FALSE)
								{
									pUIManager->GetInventory()->SetUseItemSlotInfo(t, GetChildInvenIdx(i));
									// ������ �κ��� ���� ���� Ŭ����...
									pUIManager->GetInventory()->SendUseSlotItem(t, GetChildInvenIdx(i) );
								}
								else
								{
									pUIManager->GetInventory()->ShowLockErrorMessage();
								}
							}
								
							return WMSG_SUCCESS;
						}
					}
				}
				return WMSG_SUCCESS;
			}
		}
		break;
		
	case WM_MOUSEWHEEL:
		{
			if( IsInside( nX, nY ) )
			{
				return WMSG_SUCCESS;		// ������ ����
			}
		}
		break;
	}
	return WMSG_FAIL;
}

void CUIChildInvenSlot::_openUI(const BOOL bType )
{
	if (IsVisible()) // �ߺ� ���� ����
		return;
	
	CUIManager* pUIManager = CUIManager::getSingleton();
	
	switch( m_nRearrangeOrderID )
	{
	case UI_INVEN_SLOT1:
		{
			if(g_iXPosInInvenSlot1 == 0 && g_iYPosInInvenSlot1 == 0)
				break;
			
			SetPos( g_iXPosInInvenSlot1, g_iYPosInInvenSlot1 );
			break;	
		}
	case UI_INVEN_SLOT2:
		{
			if(g_iXPosInInvenSlot2 == 0 && g_iYPosInInvenSlot2 == 0)
				break;
			
			SetPos( g_iXPosInInvenSlot2, g_iYPosInInvenSlot2 );
			break;	
		}
	case UI_INVEN_SLOT3:
		{
			if(g_iXPosInInvenSlot2 == 0 && g_iYPosInInvenSlot2 == 0)
				break;
			
			SetPos( g_iXPosInInvenSlot3, g_iYPosInInvenSlot3 );
			break;	
		}
	}

#ifdef EXPANSION_INVENTORY
	if (m_nIndexBag >= INVEN_TAB_CASH1)
	{
		for (int i = 0; i < INVEN_ONE_NEW_BAG; i++)
		{
			SetStartItemEffect(i);
		}
	}
	else
	{
		for (int i = 0; i < INVEN_ONE_BAG; i++)
		{
			SetStartItemEffect(i);
		}
	}
#else
	for (int i = 0; i < INVEN_ONE_BAG; i++)
	{
		SetStartItemEffect(i);
	}
#endif


	pUIManager->RearrangeOrder( m_nRearrangeOrderID, TRUE );
}

void CUIChildInvenSlot::_closeUI()
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	
	switch( m_nRearrangeOrderID )
	{
	case UI_INVEN_SLOT1:
		{
			g_iXPosInInvenSlot1 = GetPosX();
			g_iYPosInInvenSlot1 = GetPosY();
			break;	
		}
	case UI_INVEN_SLOT2:
		{
			g_iXPosInInvenSlot2 = GetPosX();
			g_iYPosInInvenSlot2 = GetPosY();
			break;	
		}
	case UI_INVEN_SLOT3:
		{
			g_iXPosInInvenSlot3 = GetPosX();
			g_iYPosInInvenSlot3 = GetPosY();
			break;	
		}
	}	
	
	pUIManager->RearrangeOrder( m_nRearrangeOrderID, FALSE );
	ClearNewItemEffect();
	
	//��ǥ ����
}

void CUIChildInvenSlot::ToggleVisible(const BOOL bResultView /* = false */)
{	
	if( IsVisible() )
	{
		// ������ ���� ����.
		if (bResultView)
			return;
		else
			_closeUI();
	}
	else
	{
		if (bResultView)
		{
			_openUI(bResultView);
			
			// �ƹ��͵� �������� �ʾҴٸ� ����Ʈ �̹��� �Ⱥ��̰� ó��.
			if (m_nSelSlotItemID < 0)
				UpdateSelectItem();
		}		
	}	
}

// ----------------------------------------------------------------------------
// Name : RenderItems()
// Desc :
// ----------------------------------------------------------------------------
/*
void CUIChildInvenSlot::RenderItemSurfaces()
{
	int tv_posX,tv_posY;
	int nTab;
	
	nTab = 0;
	CUIManager* pUIManager = CUIManager::getSingleton();
	CDrawPort* pDrawPort = pUIManager->GetDrawPort();
	
	// Set inventory texture
	pDrawPort->InitTextureData(m_ptdBaseTexture);
	
	// Outline of wearing items in item slot
	int i, t = GetChildInvenTab();
	for (i = 0; i < INVEN_ONE_BAG; ++i)
	{
		// UI ���� �κ��丮 �ֽ�  [10/12/2012 Ranma]
			
		CItems*		pItems = &_pNetwork->MySlotItem[t][GetChildInvenIdx(i)];
		CItemData*	pItemData = pItems->ItemData;
			
		(*m_pAllItem)[t][GetChildInvenIdx(i)].GetPos(tv_posX, tv_posY);
			
		if (pItemData == NULL)
			continue;

		// ���� ������ ǥ��		
		if(pItems->IsFlag(FLAG_ITEM_COMPOSITION) && !pItemData->IsFlag(ITEM_FLAG_COMPOSITE))
		{
			m_SlotInvenSurface.m_RectSurfaceArray[EInvenSealed].m_RT = UIRect(tv_posX,tv_posY,tv_posX+BTN_SIZE,tv_posY+BTN_SIZE);
			m_SlotInvenSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF, EInvenSealed);
		}
		// �뿩 ������ ǥ��
		if(pItems->IsFlag(FLAG_ITEM_LENT))
		{
			m_SlotInvenSurface.m_RectSurfaceArray[EInvenLeaseMark].m_RT = UIRect(tv_posX+17, tv_posY+17,tv_posX+29,tv_posY+29);
			m_SlotInvenSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF, EInvenLeaseMark);
		}
			
		// [090608: selo] ����Ʈ ���� �������� ��� ��� �������� üũ�Ͽ� ��Ȱ�� ���� ó��
		if(pUIManager->GetInventory()->IsRestritionItem(t, GetChildInvenIdx(i)))
		{
			m_SlotInvenSurface.m_RectSurfaceArray[EInvenSealed].m_RT = UIRect(tv_posX,tv_posY,tv_posX+BTN_SIZE,tv_posY+BTN_SIZE);
			m_SlotInvenSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF, EInvenSealed);
		}

		// ���� ���� �������� ������ ����Ʈ
		if (IsPlayNewItemEffect(i) == TRUE)
		{
			CInvenData* pInven = CInvenData::getSingleton();

			if (pInven)
			{
				if (pInven->IsNewItemEffectRender() == TRUE &&
					IsCheckEffectPlayCount(i) == TRUE)
				{
					m_NewItemEffectSurface.m_RectSurfaceArray[NEW_EFFECT_ITEM].m_RT = UIRect(tv_posX, tv_posY, tv_posX + BTN_SIZE, tv_posY + BTN_SIZE);
					m_NewItemEffectSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF, NEW_EFFECT_ITEM);
				}
			}
		}
	}
	
	//  edit by cpp2angel (04.12.21) : �������� ������ ǥ��
	
	if ( pUIManager->GetMix()->IsVisible() )
	{
		for ( int i = 0; i < MIX_ITEM_SLOT_COUNT; i++ )
		{
			CUIButtonEx* ButtonEx = pUIManager->GetMix()->GetItemSlot ( i );
			
			if ( !ButtonEx->IsEmpty() ) // ��� ���� �ʴٸ�....
			{
				(*m_pAllItem)[ButtonEx->GetItemTab()][ButtonEx->GetInvenIndex()].GetPos( tv_posX, tv_posY );
				
				// 				tv_posX = tv_posX + m_nPosX - pUIManager->GetInventory()->GetPosX();
				// 				tv_posY = tv_posY + m_nPosY - pUIManager->GetInventory()->GetPosY();
				
				m_SlotInvenSurface.m_RectSurfaceArray[EInvenMixing].m_RT = UIRect(tv_posX,tv_posY,tv_posX+BTN_SIZE,tv_posY+BTN_SIZE);
				m_SlotInvenSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF, EInvenMixing);
			}
			
		}
	}
	
	if ( pUIManager->GetCompound()->IsVisible() )
	{
		for ( int i = 0; i < MIX_ITEM_SLOT_COUNT; i++ )
		{
			CUIButtonEx* ButtonEx = pUIManager->GetCompound()->GetItemSlot ( i );
			
			if ( !ButtonEx->IsEmpty() ) // ��� ���� �ʴٸ�....
			{
				(*m_pAllItem)[ButtonEx->GetItemTab()][ButtonEx->GetInvenIndex()].GetPos( tv_posX, tv_posY );
				
				// 				tv_posX = tv_posX + m_nPosX - pUIManager->GetInventory()->GetPosX();
				// 				tv_posY = tv_posY + m_nPosY - pUIManager->GetInventory()->GetPosY();
				
				m_SlotInvenSurface.m_RectSurfaceArray[EInvenMixing].m_RT = UIRect(tv_posX,tv_posY,tv_posX+BTN_SIZE,tv_posY+BTN_SIZE);
				m_SlotInvenSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF, EInvenMixing);
			}
			
		}
	}
	
	// Outline of selected item
	if (m_nSelSlotItemID >= 0)
	{		
		(*m_pAllItem)[t][m_nSelSlotItemID].GetPos( tv_posX, tv_posY );
		
		// 		tv_posX = tv_posX + m_nPosX - pUIManager->GetInventory()->GetPosX();
		// 		tv_posY = tv_posY + m_nPosY - pUIManager->GetInventory()->GetPosY();
		
		m_SlotInvenSurface.m_RectSurfaceArray[EInvenNormalSelect].m_RT = UIRect(tv_posX,tv_posY,tv_posX+BTN_SIZE,tv_posY+BTN_SIZE);
		m_SlotInvenSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF, EInvenNormalSelect);
	}
	
	pDrawPort->FlushRenderingQueue();
}
*/

int CUIChildInvenSlot::GetChildInvenTab( )
{
	int	nTab = 0;

	if (m_nIndexBag == INVEN_TAB_CASH1) 
		nTab = INVENTORY_TAB_CASH_1;
	else if (m_nIndexBag == INVEN_TAB_CASH2) 
		nTab = INVENTORY_TAB_CASH_2;
	else if (m_nIndexBag == INVEN_TAB_CASH3) 
		nTab = INVENTORY_TAB_CASH_3;
	else if (m_nIndexBag == INVEN_TAB_CASH4) 
		nTab = INVENTORY_TAB_CASH_4;
	//Dethunter12 Add
	else if (m_nIndexBag == INVEN_TAB_CASH5) 
		nTab = INVENTORY_TAB_CASH_5;
	else if (m_nIndexBag == INVEN_TAB_CASH6) 
		nTab = INVENTORY_TAB_CASH_6;

	return nTab;
}

int CUIChildInvenSlot::GetChildInvenIdx( int slot )
{
	int idx = -1;
	if (m_nIndexBag < INVEN_TAB_CASH1)
		idx = (m_nIndexBag * INVEN_ONE_BAG) + slot;
	else if (m_nIndexBag <= INVEN_TAB_CASH6) //Dethunter12 Adjust 4/
		idx = slot;

	return idx;
}

void CUIChildInvenSlot::ClearNewItemEffect()
{
	int     t = GetChildInvenTab();
#ifdef EXPANSION_INVENTORY
	int bagTotal = INVEN_ONE_BAG;
	if (IsCashBag(t))
		bagTotal = INVEN_ONE_NEW_BAG;
	for (int i = 0; i < bagTotal; i++)
#else
	for (int i = 0; i < INVEN_ONE_BAG; i++)
#endif
	{
		m_bNewItem[i] = FALSE;
		m_nPlayCount[i] = 0;
		m_bStartEffect[i] = FALSE;

		if (m_pAllItem != NULL)
			(*m_pAllItem)[t][GetChildInvenIdx(i)]->setImage(eIMG_TYPE_NEW, false);
	}
}

BOOL CUIChildInvenSlot::IsPlayNewItemEffect(int InvenIdx)
{
#ifdef EXPANSION_INVENTORY
	if (m_nIndexBag >= INVEN_TAB_CASH1)
	{
		if (InvenIdx < 0 || InvenIdx >= INVEN_ONE_NEW_BAG)
			return FALSE;
	}
	else
#endif
		if (InvenIdx < 0 || InvenIdx >= INVEN_ONE_BAG)
			return FALSE;

	return m_bNewItem[InvenIdx];

}

void CUIChildInvenSlot::SetNewItemEffect( BOOL bShow, int InvenIdx )
{
#ifdef EXPANSION_INVENTORY
	if (m_nIndexBag >= INVEN_TAB_CASH1)
	{
		if (InvenIdx < 0 || InvenIdx >= INVEN_ONE_NEW_BAG)
			return;
	}
	else
#endif
		if (InvenIdx < 0 || InvenIdx >= INVEN_ONE_BAG)
			return;

	m_bNewItem[InvenIdx] = bShow;
	m_bStartEffect[InvenIdx] = FALSE;
	m_nPlayCount[InvenIdx] = 0;

	if (IsVisible() != FALSE)
		SetStartItemEffect(InvenIdx);

}

BOOL CUIChildInvenSlot::IsCheckEffectPlayCount(int InvenIdx)
{
	CInvenData* pInvenData = CInvenData::getSingleton();

	if ( pInvenData == NULL )
		return FALSE;
#ifdef EXPANSION_INVENTORY
	if (m_nIndexBag >= INVEN_TAB_CASH1)
	{
		if (InvenIdx < 0 || InvenIdx >= INVEN_ONE_NEW_BAG)
			return FALSE;
	}
	else
#endif

	if (InvenIdx < 0 || InvenIdx >= INVEN_ONE_BAG)
		return FALSE;

	int nEffectCount = pInvenData->GetPlayCount();

	if ( nEffectCount == -1)
		return TRUE;

	if ( m_bStartEffect[InvenIdx] == FALSE)
		return FALSE;

	int nCount = pInvenData->GetRenderCount() - m_nPlayCount[InvenIdx];

	if ( nCount > nEffectCount )
	{
		SetNewItemEffect(FALSE, InvenIdx);
		return FALSE;
	}

	return TRUE;
}

void CUIChildInvenSlot::SetStartItemEffect( int InvenIdx )
{
#ifdef EXPANSION_INVENTORY
	if (m_nIndexBag >= INVEN_TAB_CASH1)
	{
		if (InvenIdx < 0 || InvenIdx >= INVEN_ONE_NEW_BAG)
			return;
	}
	else
#endif
		if (InvenIdx < 0 || InvenIdx >= INVEN_ONE_BAG)
			return;


	if (m_bNewItem[InvenIdx] == FALSE)
		return;

	CInvenData* pInvenData = CInvenData::getSingleton();

	if ( pInvenData == NULL )
		return;

	m_bStartEffect[InvenIdx] = TRUE;
	m_nPlayCount[InvenIdx] = pInvenData->GetRenderCount();
}

#ifdef EXPANSION_INVENTORY
bool CUIChildInvenSlot::IsCashBag(int tab)
{
	if (tab >= INVENTORY_TAB_CASH_1 && tab <= INVENTORY_TAB_CASH_6)
		return true;

	return false;
}
#endif

void CUIChildInvenSlot::UpdateSelectItem()
{
	if (m_nSelSlotItemID >= 0)
	{
		int		x, y;
		(*m_pAllItem)[GetChildInvenTab()][m_nSelSlotItemID]->GetPos(x, y);
		m_pImgSelect->SetPos(x, y);
		m_pImgSelect->Hide(FALSE);
	}
	else
	{
		m_pImgSelect->Hide(TRUE);
	}	
}
