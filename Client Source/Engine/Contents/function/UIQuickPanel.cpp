#include "stdh.h"
#include <Engine/Interface/UIInternalClasses.h>
#include "UIQuickPanel.h"
#include <Engine/Interface/UIMessenger.h>
#include <Engine/Info/MyInfo.h>
#include <Engine/Contents/Base/UICharacterInfoNew.h>
#include <Engine/Base/KeyNames.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Interface/UICashShopEX.h>
#include <Engine/Interface/UIHelp.h>
#include <Engine/Interface/UIReformSystem.h>
#include <Engine/Contents/Base/UIRankingSystem.h>
#include <Engine/Interface/UIGuild.h>
#include <Engine/Contents/function/WildPetInfoUI.h>
#include <Engine/Interface/UIPetInfo.h>
#include <Engine/Entities/InternalClasses.h>

#ifdef QUICK_PANEL
class CmdQuickPanelClose : public Command
{
public:
	CmdQuickPanelClose() : m_pWnd(NULL) {}
	void setData( CUIQuickPanel* pWnd ) { m_pWnd = pWnd; }
	void execute()
	{
		if( m_pWnd )
			m_pWnd->Close();
	}
private:
	CUIQuickPanel* m_pWnd;
};

class CmdQuickPanelUse : public Command
{
public:
	CmdQuickPanelUse() : m_pWnd(NULL) {}
	void setData( CUIQuickPanel* pWnd ) { m_pWnd = pWnd; }
	void execute()
	{
		if( m_pWnd )
		{
			for (int i = 0; i < 25; i++)
			{
                  m_pWnd->UseQuickSlot(i);
			}
		}
	}
private:
	CUIQuickPanel* m_pWnd;
};

class CmdQuickPanelOk : public Command
{
public:
	CmdQuickPanelOk() : m_pWnd(NULL) {}
	void setData( CUIQuickPanel* pWnd ) { m_pWnd = pWnd; }
	void execute()
	{
		if( m_pWnd )
			m_pWnd->SendItemUsed();
	}
private:
	CUIQuickPanel* m_pWnd;
};

extern INDEX g_iShowQuickPanel;

CUIQuickPanel::CUIQuickPanel()
:
    m_pDrag(NULL)
	, m_nOriX(0)
	, m_pbtnClose(NULL)
	, m_pbtnUse(NULL)
	, m_nOriY(0)
	, m_bDrag(false)
	, m_nCashBagNum(-1)
	, m_pSendItems(NULL)

	
{
	for (int i = 0; i < 25; i++)
	{
		m_pIcon[i] = NULL;
	}
	setInherit(false);
}

void CUIQuickPanel::initialize()
{
	m_pConsoleGM = (CUIImage*)findUI("img_back");
	m_pDrag	= (CUIText*)findUI("base_drag_area");
	m_pbtnClose = (CUIButton*)findUI("btn_close");
	m_pbtnUse = (CUIButton*)findUI("btn_use");

	if (m_pbtnClose != NULL)
	{
		CmdQuickPanelClose* pCmd = new CmdQuickPanelClose;
		pCmd->setData(this);
		m_pbtnClose->SetCommandUp(pCmd);
	}

	if (m_pbtnUse != NULL)
	{
		CmdQuickPanelUse* pCmd = new CmdQuickPanelUse;
		pCmd->setData(this);
		m_pbtnUse->SetCommandUp(pCmd);
	}

	CTString strIconId;
	for (int i = 0; i < 25; ++i)
	{
		strIconId.PrintF("icon_%d", i);
		m_pIcon[i] = (CUIIcon*)findUI(strIconId);

		if (m_pIcon[i] != NULL)
			m_pIcon[i]->clearIconData();
	}

}

void CUIQuickPanel::Open()
{
	Hide(FALSE);
	SetVisible(TRUE);

	CUIManager* pUIManager = CUIManager::getSingleton();

	for (int i = 0; i < 25; i++)
	{
		
		int type = _pNetwork->MyCharacterInfo.cloud_QuickPanelBtnType[i];
		int dataidx = _pNetwork->MyCharacterInfo.cloud_QuickPanelBtnIdx[i];

		if(type == UBET_SKILL)
		{
			
			CSkill skillData = _pNetwork->GetSkillData( dataidx );

			if (skillData.Skill_Data.index > 0)
				m_pIcon[i]->setSkill(dataidx);
		}
		else if(type == UBET_ITEM)
		{

			CItemData*	pItem = _pNetwork->GetItemData( dataidx );
			if(pItem != NULL)
			{
				m_pIcon[i]->setData(UBET_ITEM,dataidx);
			}
		}


		int nMyItemCount = UIMGR()->GetInventory()->GetItemCount(m_pIcon[i]->getIndex());
		m_pIcon[i]->setCount(nMyItemCount);

		m_pIcon[i]->setCooltime(true);

		if (nMyItemCount < 1 && m_pIcon[i] != NULL && m_pIcon[i]->getBtnType() == UBET_ITEM)
				m_pIcon[i]->clearIconData();

	}
	UIMGR()->RearrangeOrder(UI_QuickPanel, TRUE);
}

void CUIQuickPanel::Close()
{
	Hide(TRUE);
	SetVisible(FALSE);
	//Destroy();
	SendSaveItens();
	UIMGR()->RearrangeOrder(UI_QuickPanel, FALSE);
}

bool CUIQuickPanel::_CheckDuplicate(CUIIcon * pIcon)
{
	for (int i = 0; i < 25; i++)
	{
		if (m_pIcon[i] != NULL && pIcon != NULL)
		{
			if (m_pIcon[i]->getBtnType() == UBET_SKILL && m_pIcon[i]->getIndex() == pIcon->getIndex())
				return true;

			if (m_pIcon[i]->getItems() == NULL || pIcon->getItems() == NULL)
				continue;

			if (pIcon->getItems()->ItemData->GetItemIndex() == m_pIcon[i]->getItems()->ItemData->GetItemIndex())
				return true;
		}
	}
	return false;
}

void CUIQuickPanel::SendItemUsed()
{
	for (int i = 0; i < 25; i++)
	{
		if(m_pIcon[i] == NULL)
		{
			ErrMessage(eERR_EMPTY_KEY);
			return;
		}
	}
	
	if (m_pSendItems == NULL)
	{
		ErrMessage(eERR_EMPTY_KEY);
		return;
	}
	else
	_pNetwork->UseSlotItem(m_pSendItems->Item_Tab, m_pSendItems->InvenIndex);
}

BOOL CUIQuickPanel::CloseWindowByEsc()
{
	Close();
	return TRUE;
}

WMSG_RESULT CUIQuickPanel::OnLButtonDown(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if( m_pDrag && m_pDrag->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}
	for (int i = 0; i < 25; i++)
	{
		if( m_pIcon[i] && m_pIcon[i]->IsInside(x, y) )
		{
			if (m_pIcon[i] != NULL)
				m_pIcon[i]->clearIconData();
		}
	}
	
	CUIManager::getSingleton()->RearrangeOrder(UI_QuickPanel, TRUE);
	return CUIBase::OnLButtonDown(x, y);
}

WMSG_RESULT CUIQuickPanel::OnLButtonUp(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	for (int i = 0; i < 25; i++)
	{
		if( m_pIcon[i] && m_pIcon[i]->IsInside(x, y) )
		{
			if (UIMGR()->GetDragIcon() != NULL)
				SetPutOnItemData(i);
			int nMyItemCount = UIMGR()->GetInventory()->GetItemCount(m_pIcon[i]->getIndex());
		    m_pIcon[i]->setCount(nMyItemCount);
			m_pIcon[i]->setCooltime(true);

		}
	}
	return CUIBase::OnLButtonUp(x, y);
}


WMSG_RESULT CUIQuickPanel::OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg )
{
	if (m_bHide)
		return WMSG_FAIL;

	if( m_bDrag && ( pMsg->wParam & MK_LBUTTON ) )
	{
		int ndX = x - m_nOriX;
		int ndY = y - m_nOriY;

		m_nOriX = x;
		m_nOriY = y;

		Move( ndX, ndY );
		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	for (int i = 0; i < 25; i++)
	{
		int nMyItemCount = UIMGR()->GetInventory()->GetItemCount(m_pIcon[i]->getIndex());
		m_pIcon[i]->setCount(nMyItemCount);
		m_pIcon[i]->setCooltime(true);
		if (nMyItemCount < 1 && m_pIcon[i] != NULL && m_pIcon[i]->getBtnType() == UBET_ITEM)
				m_pIcon[i]->clearIconData();
	}
	CUIManager::getSingleton()->SetMouseCursorInsideUIs();

	return CUIBase::OnMouseMove(x, y, pMsg);
}
void CUIQuickPanel::SetPutOnItemData(int iconcount)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->GetMessenger()->SetDragging(false);

	if (pUIManager->GetDragIcon()->getBtnType() == UBET_SKILL )
	{
		CUIIcon* pDrag = pUIManager->GetDragIcon();
		if (pDrag == NULL)
			return;

		if (_CheckDuplicate(pDrag))
		{
			ErrMessage(eERR_CAN_NOT_OPEN_KEY);
			pUIManager->ResetHoldBtn();
			return;
		}

		int	nSkillIndex0 = pDrag->getIndex();


		if (nSkillIndex0 == 5046 || nSkillIndex0 == 31 || nSkillIndex0 == 32 || nSkillIndex0 == 33 || nSkillIndex0 == 50 || nSkillIndex0 == 39
		 || nSkillIndex0 == 177 || nSkillIndex0 == 178 || nSkillIndex0 == 548 || nSkillIndex0 == 549 || nSkillIndex0 == 621 || nSkillIndex0 == 622 
		 || nSkillIndex0 == 640 || nSkillIndex0 == 641 || nSkillIndex0 == 723 || nSkillIndex0 == 724 || nSkillIndex0 == 1117 || nSkillIndex0 == 317
		 || nSkillIndex0 == 318 || nSkillIndex0 == 320 || nSkillIndex0 == 321 || nSkillIndex0 == 293 || nSkillIndex0 == 294 || nSkillIndex0 == 300
		 || nSkillIndex0 == 301 || nSkillIndex0 == 131 || nSkillIndex0 == 191


		 )
		{
			ErrMessage(eERR_CAN_NOT_OPEN_KEY);
			pUIManager->ResetHoldBtn();
			return;
		}

		CSkill	&rSelSkill0 = _pNetwork->GetSkillData( nSkillIndex0 );
		if (_pNetwork->GetSkillData( nSkillIndex0 ).GetType() == CSkill::ST_PET_SKILL_ACTIVE )
		{
			ErrMessage(eERR_CAN_NOT_OPEN_KEY);
			pUIManager->ResetHoldBtn();
			return;
		}
		else if (_pNetwork->GetSkillData( nSkillIndex0 ).GetType() == CSkill::ST_PET_COMMAND )
		{
			ErrMessage(eERR_CAN_NOT_OPEN_KEY);
			pUIManager->ResetHoldBtn();
			return;
		}
		else if (_pNetwork->GetSkillData(nSkillIndex0).GetJob() == WILDPET_JOB)
		{
			ErrMessage(eERR_CAN_NOT_OPEN_KEY);
			pUIManager->ResetHoldBtn();
			return;
		}

		if( !(rSelSkill0.GetSorcererFlag() & ( SSF_USE_FIRE | SSF_USE_WIND | SSF_USE_EARTH | SSF_USE_WATER )) )
		{
			if( m_pIcon[iconcount])
			{				
				m_pIcon[iconcount]->setSkill(nSkillIndex0);	
				m_pIcon[iconcount]->setCooltime(true);
				pUIManager->ResetHoldBtn();
				return;
			}
		}

	}

	if (pUIManager->GetDragIcon()->getBtnType() == UBET_ITEM )
	{
		CUIIcon* pDrag = pUIManager->GetDragIcon();
		if (pDrag == NULL)
			return;

		if (_CheckDuplicate(pDrag))
		{
			ErrMessage(eERR_CAN_NOT_OPEN_KEY);
			pUIManager->ResetHoldBtn();
			return;
		}

		int	nItemIndex0= pDrag->getIndex();

		CItemData*	pItem = _pNetwork->GetItemData( nItemIndex0 );
		if(pItem != NULL)
		{
			if (pItem->GetType() == CItemData::ITEM_POTION && pItem->GetSubType() != CItemData::POTION_HP && pItem->GetSubType() != CItemData::POTION_MP && pItem->GetSubType() != CItemData::POTION_DUAL)
			{
				if( m_pIcon[iconcount] )
				{				
					m_pIcon[iconcount]->setData(UBET_ITEM,nItemIndex0);	
					int nMyItemCount = UIMGR()->GetInventory()->GetItemCount(m_pIcon[iconcount]->getIndex());
					m_pIcon[iconcount]->setCount(nMyItemCount);
					pUIManager->ResetHoldBtn();

					return;
				}
			}
			else
			{
				ErrMessage(eERR_CAN_NOT_OPEN_KEY);
				pUIManager->ResetHoldBtn();
				return;
			}
		}
	}

	if (pUIManager->GetDragIcon()->getBtnType() == UBET_ACTION)
	{
	   ErrMessage(eERR_CAN_NOT_OPEN_KEY);
	   pUIManager->ResetHoldBtn();
	   return;
	}

	ErrMessage(eERR_CAN_NOT_OPEN_KEY);
	pUIManager->ResetHoldBtn();
}

void CUIQuickPanel::ErrMessage( int errCode )
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString strMessage;
	CUIMsgBox_Info	MsgBoxInfo;

	MsgBoxInfo.SetMsgBoxInfo( _S( 191, "Confirm" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
	
	switch( errCode )
	{
	case eERR_CAN_NOT_OPEN_KEY:
		{
			strMessage.PrintF( _S(8558, "You can not use the lack of Skill"));//4783 4783
		}
		break;
	case eERR_EMPTY_KEY:
		{
			strMessage.PrintF( _S(8558, "You can not use the lack of Skill"));//4783 4783
		}
		break;
	}
	if( strMessage.IsEmpty() == FALSE )
	{
		MsgBoxInfo.AddString( strMessage );
		pUIManager->CreateMessageBox( MsgBoxInfo );
	}

	m_pSendItems = NULL;

}

void CUIQuickPanel::UseQuickSlot(int iconcount)
{
	CUIManager* pUIManager = CUIManager::getSingleton();	
	if( pUIManager->GetLacaBall()->IsVisible() )
		return;	
	if (m_pIcon[iconcount]->IsEmpty())
		return;
	int	nType = m_pIcon[iconcount]->getBtnType();

	if (nType == UBET_SKILL )		
	{
		int		nSkillIndex = m_pIcon[iconcount]->getIndex();
		BOOL	bDelay = MY_INFO()->GetSkillDelay(nSkillIndex, m_pIcon[iconcount]->IsSpecial());
		int nSkillLevel = MY_INFO()->GetSkillLevel(nSkillIndex, m_pIcon[iconcount]->IsSpecial());

		if(nSkillIndex < 1 || nSkillLevel < 1)
			return;

		if (bDelay == TRUE)
			return;

		if (_pNetwork->GetSkillData( nSkillIndex ).GetType() == CSkill::ST_PET_SKILL_ACTIVE )
		{
			return;//pUIManager->GetPetInfo()->UseSkill( nSkillIndex );
			
		}
		else if (_pNetwork->GetSkillData( nSkillIndex ).GetType() == CSkill::ST_PET_COMMAND )
		{
			return;//pUIManager->GetPetInfo()->UseCommand( nSkillIndex );
		}
		else if (_pNetwork->GetSkillData(nSkillIndex).GetJob() == WILDPET_JOB)
		{
			return;//pUIManager->GetWildPetInfoUI()->UseSkill(nSkillIndex);
		}
		else
		{
			if (_pNetwork->GetSkillData( nSkillIndex ).GetFlag() & SF_GUILD)
			{	// 길드 스킬일 경우, 사용 조건 체크
				if ( !pUIManager->GetGuild()->CheckUseGuildSkill( nSkillIndex ))
				{	// 조건 충족을 못할 경우 리턴
					return;
				}
			}

			UseBuffReq(nSkillIndex, nSkillLevel);
		}
	}

	else if (nType == UBET_ITEM )		
	{
		if( pUIManager->IsCSFlagOn( CSF_WAREHOUSE ) )
				return;
		
		int	nItemIndex0 = m_pIcon[iconcount]->getIndex();
		CItems* pItems = m_pIcon[iconcount]->getItems();	

		if(pItems == NULL)
			return;

		if(nItemIndex0 == NULL)
			return;

		int nMyItemCount = UIMGR()->GetInventory()->GetItemCount(m_pIcon[iconcount]->getIndex());
		if(nMyItemCount < 1)
		{
			return;
		}


		SQUAD llTerm = _pTimer->GetHighPrecisionTimer().GetMilliseconds() - MY_INFO()->GetUseItem(nItemIndex0);

		if( llTerm > 500 )
		{
			MY_INFO()->SetUseItem(nItemIndex0, _pTimer->GetHighPrecisionTimer().GetMilliseconds());
		}
		else 
		{ return; }

		if (m_pIcon[iconcount]->IsRestritionItem() == true)
		{
			CTString strTitle;
			CTString strMessage1;
			CUIMsgBox_Info	MsgBoxInfo;

			strTitle	=	_S(191,"확인");
			strMessage1	=	_S( 4428, "여기서는 사용 할 수 없습니다" ); 
			MsgBoxInfo.SetMsgBoxInfo(strTitle,UMBS_OK,UI_NONE,MSGCMD_NULL);
			MsgBoxInfo.AddString(strMessage1);
			pUIManager->CreateMessageBox(MsgBoxInfo);
			return;
		}
		if (m_pIcon[iconcount]->IsWearTab() == false)
		{
			int	nTab = pItems->Item_Tab;
			int	nIdx = pItems->InvenIndex;
			int	nCount = pItems->Item_Sum;

			

			CItemData*	ItemSkill6 = _pNetwork->GetItemData( nItemIndex0 );

			pUIManager->GetInventory()->GetItemSlotInfo( nItemIndex0, nTab, nIdx );
			
			pUIManager->GetInventory()->SendUseSlotItem(nTab, nIdx);
			
		}
		else
		{
			int	nType = m_pIcon[iconcount]->GetQuickSlotWearType();
			int nWear = pItems->Item_Wearing;
			int	nIdx = pItems->InvenIndex;
			int vIdx = pItems->Item_UniIndex;

			switch (nType)
			{
			case 0:
				_pNetwork->SendItemWearingMSG(MSG_ITEM_WEAR_TAKE_OFF, 
					nWear, -1, -1, 0);
				break;
			case 1:
				_pNetwork->SendItemWearingMSG(MSG_ITEM_WEAR_COSTUME_TAKEOFF,
					nWear, -1, -1, 0, vIdx);	
				break;
			case 2:
				_pNetwork->SendItemWearingMSG(MSG_ITEM_WEAR_COSTUME_SUIT_TAKEOFF,
					nWear, -1, -1, 0, vIdx);
				break;
			}				
		}
	}
	else if (nType == UBET_ACTION )		
	{
		return;

	}
	ResetallBtns();
	pUIManager->ResetHoldBtn();
}

void CUIQuickPanel::ResetallBtns()
{
	for (int i = 0; i < 25; i++)
	{
		if(m_pIcon[i])
		{
			int nMyItemCount = UIMGR()->GetInventory()->GetItemCount(m_pIcon[i]->getIndex());
			int		nIndex = m_pIcon[i]->getIndex();
            CItems* pItems = UIMGR()->GetInventory()->GetItems(nIndex);
			m_pIcon[i]->setCount(nMyItemCount);
			m_pIcon[i]->setCooltime(true);

			if (nMyItemCount < 1 && m_pIcon[i] != NULL && m_pIcon[i]->getBtnType() == UBET_ITEM)
				m_pIcon[i]->clearIconData();
		}
	}
}

void CUIQuickPanel::UseBuffReq(int nSkillIndex, int sbLevel) 
{
	CNetworkMessage UseBuffReq((UBYTE)MSG_EXTEND);
	UseBuffReq << (DWORD)MSG_EX_CLOUD_SKILLS_USE;

	UseBuffReq << (DWORD)nSkillIndex
		       << (DWORD)sbLevel;
	
	_pNetwork->SendToServerNew(UseBuffReq);
}

void CUIQuickPanel::SendSaveItens()
{
	CNetworkMessage Savemsg((UBYTE)MSG_EXTEND);
	Savemsg << (DWORD)MSG_EX_CLOUD_SAVE_QUICKPANEL;

	for (int i = 0; i < 25; i++)
	{
		if (m_pIcon[i]->getBtnType() == UBET_SKILL)
		{
			Savemsg << (INDEX) UBET_SKILL;
			Savemsg << (INDEX) m_pIcon[i]->getIndex();
		}
		else if (m_pIcon[i]->getBtnType() == UBET_ITEM)
		{
			if (m_pIcon[i]->getItems() == NULL || m_pIcon[i]->getItems()->ItemData == NULL) continue;

			Savemsg << (INDEX) UBET_ITEM;
			Savemsg << (INDEX) m_pIcon[i]->getItems()->ItemData->GetItemIndex();
		}
		else
		{
			Savemsg << (INDEX) -1;
			Savemsg << (INDEX) -1;
		}
	}
	
	_pNetwork->SendToServerNew(Savemsg);
}
#endif
