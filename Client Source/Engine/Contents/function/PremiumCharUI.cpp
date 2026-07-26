#include "StdH.h"

#include <Engine/Interface/UIInternalClasses.h>
#include "PremiumCharUI.h"
#include <Engine/Contents/Base/UIMsgBoxMgr.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/function/PremiumChar.h>
#include <Engine/Contents/function/PremiumCharDesign.h>
#include <Engine/Contents/function/PetFreeUI.h>
#include <Engine/Interface/UIMessenger.h>
#include <Engine/Help/Util_Help.h>

//--------------------------------------------------------------
// �ݱ�
class CmdPremiumClose : public Command
{
public:
	CmdPremiumClose() : pUI_(NULL) {}
	void setData(CPremiumCharUI* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->CloseUI();
	}
private:
	CPremiumCharUI* pUI_;
};

//--------------------------------------------------------------
// �� ���� ��Ȱ
class CmdPremiumPetRevival : public Command
{
public:
	CmdPremiumPetRevival() : pUI_(NULL) {}
	void setData(CPremiumCharUI* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->PetRemoteRevival();
	}
private:
	CPremiumCharUI* pUI_;
};

//--------------------------------------------------------------
// �޽���â ����
class CmdPremiumOpenMessenger : public Command
{
public:
	CmdPremiumOpenMessenger() : pUI_(NULL) {}
	void setData(CPremiumCharUI* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->OpenMessenger();
	}
private:
	CPremiumCharUI* pUI_;
};

CPremiumCharUI::CPremiumCharUI()
	: m_pMoveArea(NULL)
	, m_bDrag(false)
	, m_nOriX(0), m_nOriY(0)
	, m_pDesign(NULL)

	, m_pstrExpire(NULL)

	, m_plistScroll(NULL)
{
	int i;

	for (i = 0; i < eBTN_MAX; ++i)
	{
		m_pBtn[i] = NULL;
	}

	for (i = 0; i < eLIST_MAX; ++i)
	{
		m_pList[i] = NULL;
	}

	setInherit(false);
}

CPremiumCharUI::~CPremiumCharUI()
{
	SAFE_DELETE(m_pDesign);
	Destroy();
}

void CPremiumCharUI::updateUI()
{

	updateExpireTime();

	updatePassive();
	updateActive();
}


void CPremiumCharUI::updateExpireTime()
{
	if (m_pstrExpire == NULL)
		return;

	CPremiumChar* pChar = GAMEDATAMGR()->GetPremiumChar();

	if (pChar == NULL)
		return;

	int nExpireTime = pChar->getExpireTime();

	tm*	pTimeEnd = NULL;
	char expire[25] = {0,};
	CTString strTooltip;

	pTimeEnd = localtime((time_t*)&nExpireTime);

	if (pTimeEnd)
	{
		strTooltip.PrintF( _S( 6070, "���� : %d��%d��%d��%d��%d��"), pTimeEnd->tm_year + 1900, pTimeEnd->tm_mon + 1, pTimeEnd->tm_mday, pTimeEnd->tm_hour, pTimeEnd->tm_min );
		m_pstrExpire->SetText(strTooltip);
	}
}


void CPremiumCharUI::updatePassive()
{
#ifdef PREMIUM_CHAR
	if (m_pList[eLIST_PASSIVE] == NULL)
		return;

	m_pList[eLIST_PASSIVE]->DeleteAllListItem();

	if (m_plistScroll)
		m_plistScroll->SetScrollPos(0);

	CPremiumChar* pChar = GAMEDATAMGR()->GetPremiumChar();

	if (pChar == NULL)
		return;
	
	CUITextBox* pTextBox = NULL;
	CTString strTemp;
	CUIListItem* plistItem = NULL;
	COLOR color = 0xffffffff;

	switch(pChar->getType())
	{
	case PREMIUM_CHAR_TYPE_FIRST:
		{
			// exp/sp 10%  ���
			plistItem = getPassiveItem(ePASSIVE_EXP_SP_UP);

			if (plistItem != NULL)
				m_pList[eLIST_PASSIVE]->AddListItem(plistItem);

			// ��� ��� -3
			plistItem = getPassiveItem(ePASSIVE_LEVEL_DOWN);

			if (plistItem != NULL)
				m_pList[eLIST_PASSIVE]->AddListItem(plistItem);

			// �ŷ����� ������ ����
			plistItem = getPassiveItem(ePASSIVE_AUCTION_NO_FEE);

			if (plistItem != NULL)
				m_pList[eLIST_PASSIVE]->AddListItem(plistItem);
			// ���̸��� ����1 ���
			plistItem = getPassiveItem(ePASSIVE_CASH_INVEN1_USE);

			if (plistItem != NULL)
				m_pList[eLIST_PASSIVE]->AddListItem(plistItem);

			// �ź��� ���� ȣ��� ���
			plistItem = getPassiveItem(ePASSIVE_EXPRESS_REMOTE_USE);

			if (plistItem != NULL)
				m_pList[eLIST_PASSIVE]->AddListItem(plistItem);

			// ���� ���� ������
			plistItem = getPassiveItem(ePASSIVE_CHANGE_FACE_PREE_USE);

			if (plistItem != NULL)
				m_pList[eLIST_PASSIVE]->AddListItem(plistItem);

			// ������ ���� ���� ���
			plistItem = getPassiveItem(ePASSIVE_DURABILITY_REMOTE_USE);

			if (plistItem != NULL)
				m_pList[eLIST_PASSIVE]->AddListItem(plistItem);

			plistItem = getPassiveItem(ePASSIVE_DONT_LOOSE_BUFF_DEAD);

			if (plistItem != NULL)
				m_pList[eLIST_PASSIVE]->AddListItem(plistItem);

			plistItem = getPassiveItem(ePASSIVE_AUTO_PICK_EVENT);

			if (plistItem != NULL)
				m_pList[eLIST_PASSIVE]->AddListItem(plistItem);

			plistItem = getPassiveItem(ePASSIVE_INCREASE_HP);
			
			if (plistItem != NULL)
				m_pList[eLIST_PASSIVE]->AddListItem(plistItem);
		}
		break;

	default:
		return;
	}

	// ����Ʈ ������Ʈ
	int nMaxItem = m_pList[eLIST_PASSIVE]->getListItemCount();
	
	m_pList[eLIST_PASSIVE]->UpdateScroll(nMaxItem);
	m_pList[eLIST_PASSIVE]->UpdateList();

	int nListItemWidth = m_pList[eLIST_PASSIVE]->GetItemTotalHeight();
	int nShowCnt = m_pList[eLIST_PASSIVE]->GetItemShowNum();

	if (nListItemWidth <= m_pList[eLIST_PASSIVE]->GetHeight())
		nShowCnt = nMaxItem;

	if (m_plistScroll != NULL)
		m_plistScroll->SetItemsPerPage(nShowCnt);
#endif	//	PREMIUM_CHAR
}

void CPremiumCharUI::updateActive()
{
#ifdef PREMIUM_CHAR
	CPremiumChar* pChar = GAMEDATAMGR()->GetPremiumChar();

	if (pChar == NULL)
		return;

	switch(pChar->getType())
	{
	case PREMIUM_CHAR_TYPE_FIRST:
		{
			// �� ���� ��� ����
			updateAc_PetRevival();

			// ģ������ �ڷ� ��Ʈ ����
			updateAc_Jump();
		}
		break;

	default:
		return;
	}
#endif	//	PREMIUM_CHAR
}

void CPremiumCharUI::updateAc_PetRevival()
{
	if (m_pList[eLIST_PET_REMOTE] == NULL)
		return;

	m_pList[eLIST_PET_REMOTE]->DeleteAllListItem();

	CUIText* pText = NULL;
	CTString strTemp;
	CUIListItem* plistItem = NULL;
	
	// �� ���� ����
	plistItem = (CUIListItem*)m_pDesign->CloneListActive();

	if (plistItem != NULL)
	{
		strTemp.PrintF(_S( 6337, "�� ���� ����" ));

		pText = (CUIText*)plistItem->findUI("str_copyContent");

		if (pText != NULL)
		{
			strTemp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTemp, pText->GetWidth(), CTString("..."));
			pText->SetText(strTemp);
		}

		m_pList[eLIST_PET_REMOTE]->AddListItem(plistItem);
	}

	// ����Ʈ ������Ʈ
	m_pList[eLIST_PET_REMOTE]->UpdateList();
}

void CPremiumCharUI::updateAc_Jump()
{
	if (m_pList[eLIST_JUMP] == NULL)
		return;

	m_pList[eLIST_JUMP]->DeleteAllListItem();

	CUIText* pText = NULL;
	CTString strTemp;
	CUIListItem* plistItem = NULL;

	// ģ�� ��� ����
	plistItem = (CUIListItem*)m_pDesign->CloneListActive();

	if (plistItem != NULL)
	{
		strTemp.PrintF(_S( 6339, "ģ�� ��� ����" ));

		pText = (CUIText*)plistItem->findUI("str_copyContent");

		if (pText != NULL)
		{
			strTemp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTemp, pText->GetWidth(), CTString("..."));
			pText->SetText(strTemp);
		}

		m_pList[eLIST_JUMP]->AddListItem(plistItem);
	}

	// ���� ��� ���� Ƚ��
	plistItem = (CUIListItem*)m_pDesign->CloneListActive();

	if (plistItem != NULL)
	{
		CPremiumChar* pChar = GAMEDATAMGR()->GetPremiumChar();
		int nCount = 0;

		if (pChar != NULL)
			nCount = pChar->getTeleportCount();
#ifdef PREMIUM_CHAR
		strTemp.PrintF(_S( 6340, "���� ��� ���� Ƚ�� (%d/%d)" ), nCount, PREMIUM_CHAR_JUMP_COUNT_MAX);
#endif	//	PREMIUM_CHAR

		pText = (CUIText*)plistItem->findUI("str_copyContent");

		if (pText != NULL)
		{
			strTemp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTemp, pText->GetWidth(), CTString("..."));
			pText->SetText(strTemp);

			if (nCount >= PREMIUM_CHAR_JUMP_COUNT_MAX)
				pText->setFontColor(DEF_UI_COLOR_RED);
			else
				pText->setFontColor(DEF_UI_COLOR_WHITE);
		}

		m_pList[eLIST_JUMP]->AddListItem(plistItem);
	}

	// ����Ʈ ������Ʈ
	m_pList[eLIST_JUMP]->UpdateList();
}

void CPremiumCharUI::initialize()
{
	// design
	m_pDesign = new CPremiumCharDesign;
	CUIManager::getSingleton()->LoadXML("PremiumDesign.xml", (CUIBase*)m_pDesign);

	m_pMoveArea = (CUIImage*)findUI("move_area");

	m_pstrExpire = (CUIText*)findUI("str_expiretime");

	int i;
	// btn
	CTString strBtnId[eBTN_MAX] = { "btn_close", "btn_petRemote", "btn_jump", "btn_cancel" };

	for (i = 0; i < eBTN_MAX; ++i)
	{
		m_pBtn[i] = (CUIButton*)findUI(strBtnId[i]);
	}

	// list
	CTString strListId[eLIST_MAX] = { "list_passive", "list_pet", "list_jump" };

	for (i = 0; i < eLIST_MAX; ++i)
	{
		m_pList[i] = (CUIList*)findUI(strListId[i]);
	}

	m_plistScroll = (CUIScrollBar*)findUI("scroll_passive");

	// Ŀ�ǵ� ����

	// x ��ư
	if (m_pBtn[eBTN_CLOSE] != NULL)
	{
		CmdPremiumClose* pCmd = new CmdPremiumClose;
		pCmd->setData(this);
		m_pBtn[eBTN_CLOSE]->SetCommandUp(pCmd);
	}

	// �ݱ� ��ư
	if (m_pBtn[eBTN_CANCEL] != NULL)
	{
		CmdPremiumClose* pCmd = new CmdPremiumClose;
		pCmd->setData(this);
		m_pBtn[eBTN_CANCEL]->SetCommandUp(pCmd);
	}

	// �� ���� ��ư
	if (m_pBtn[eBTN_PET_REMOTE] != NULL)
	{
		CmdPremiumPetRevival* pCmd = new CmdPremiumPetRevival;
		pCmd->setData(this);
		m_pBtn[eBTN_PET_REMOTE]->SetCommandUp(pCmd);
	}

	// ģ�� ���� ��ư
	if (m_pBtn[eBTN_JUMP] != NULL)
	{
		CmdPremiumOpenMessenger* pCmd = new CmdPremiumOpenMessenger;
		pCmd->setData(this);
		m_pBtn[eBTN_JUMP]->SetCommandUp(pCmd);
	}
}

void CPremiumCharUI::OpenUI()
{
#ifdef PREMIUM_CHAR
	CUIManager* pUIMgr = CUIManager::getSingleton();

	SetVisible(TRUE);
	Hide(FALSE);

	updateUI();

	pUIMgr->RearrangeOrder(UI_PREMIUM_CHAR, TRUE);
#endif	//	PREMIUM_CHAR
}

void CPremiumCharUI::CloseUI()
{
	Hide(TRUE);
	SetVisible(FALSE);

	CUIManager* pUIMgr = CUIManager::getSingleton();

	pUIMgr->RearrangeOrder(UI_PREMIUM_CHAR, FALSE);
	CUITooltipMgr::getSingleton()->setData(NULL);
}

WMSG_RESULT CPremiumCharUI::OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg )
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

	CUIManager::getSingleton()->SetMouseCursorInsideUIs();

	return WMSG_FAIL;
}

WMSG_RESULT CPremiumCharUI::OnLButtonUp( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	CUIManager::getSingleton()->ResetHoldBtn();
	return WMSG_FAIL;
}

WMSG_RESULT CPremiumCharUI::OnLButtonDown( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if( m_pMoveArea && m_pMoveArea->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}

	CUIManager::getSingleton()->RearrangeOrder(UI_PREMIUM_CHAR, TRUE);

	return WMSG_FAIL;
}

void CPremiumCharUI::PetRemoteRevival()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (_pNetwork->MyWearItem[WEAR_PET].IsEmptyItem() == FALSE && _pNetwork->MyWearItem[WEAR_PET].IsFlag( FLAG_ITEM_SEALED ))
	{
		pUIManager->CloseMessageBox( MSGCMD_PETTRAINING_NOTIFY );

		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo( _S(2188, "�ֿϵ���" ), UMBS_OK,
			UI_PET_TRAINING, MSGCMD_PETTRAINING_NOTIFY );
		MsgBoxInfo.AddString( _S(4765,"������ �����Ͽ��� ��Ȱ�� �����մϴ�.") );
		pUIManager->CreateMessageBox( MsgBoxInfo );
		return;
	}

	pUIManager->GetPetFree()->openUI(0.0f, 0.0f, -1);
}

void CPremiumCharUI::OpenMessenger()
{
	UIMGR()->GetMessenger()->ToggleVisible();
}

CUIListItem* CPremiumCharUI::getPassiveItem( ePASSIVE_TYPE eItem )
{
	CUITextBox* pTextBox = NULL;
	CTString strTemp;
	CUIListItem* plistItem = NULL;
	COLOR color = 0xffffffff;

	plistItem = (CUIListItem*)m_pDesign->CloneListPassive();

	if (plistItem != NULL)
	{
		strTemp = getPassiveItemString(eItem);

		pTextBox = (CUITextBox*)plistItem->findUI("tb_copyContent");

		if (pTextBox != NULL)
		{
			color = pTextBox->GetTextColor();
			pTextBox->SetText(strTemp, color, TRUE);
			plistItem->SetHeight(pTextBox->GetTextTotalHeight());
		}
	}

	return plistItem;
}

CTString CPremiumCharUI::getPassiveItemString( ePASSIVE_TYPE eItem )
{
	CTString strTemp = CTString("");

	switch(eItem)
	{
	case ePASSIVE_EXP_SP_UP:
		strTemp.PrintF(_S( 6329, "��� ���ͷκ��� �⺻ EXP/SP 10%�� �� ȹ�� �մϴ�." ));
		break;
	case ePASSIVE_LEVEL_DOWN:
		strTemp.PrintF(_S( 6330, "��� ��� 3���� ���� ������ �� �ֽ��ϴ�. (180���� ���� ����)" ));
		break;
	case ePASSIVE_AUCTION_NO_FEE:
		strTemp.PrintF(_S( 6331, "�ŷ����� �̿� �� �����ᰡ �����Դϴ�." ));
		break;
	case ePASSIVE_CASH_INVEN1_USE:
		strTemp.PrintF(_S( 6332, "���̸��� ����1�� ����� �� �ֽ��ϴ�." ));
		break;
	case ePASSIVE_EXPRESS_REMOTE_USE:
		strTemp.PrintF(_S( 6333, "�ź��� ���� ȣ��⸦ ����� �� �ֽ��ϴ�." ));
		break;
	case ePASSIVE_CHANGE_FACE_PREE_USE:
		strTemp.PrintF(_S( 6334, "���� ����� ���� ���� ������ �����մϴ�." ));
		break;
	case ePASSIVE_DURABILITY_REMOTE_USE:
		strTemp.PrintF(_S( 7108, "�������� ��Ƶ� ��𿡼��� �������� ���� �� �� �ֽ��ϴ�." ));
		break;
	case ePASSIVE_DONT_LOOSE_BUFF_DEAD:
		strTemp.PrintF(_S( 8344, "You don't loose buffs when someone kill you" ));
		break;
	case ePASSIVE_AUTO_PICK_EVENT:
		strTemp.PrintF(_S( 8345, "Auto pick enabled for event items" ));
		break;
	case ePASSIVE_INCREASE_HP:
		strTemp.PrintF(_S( 8346, "Increase your HP 10k" ));
		break;
	}

	return strTemp;	
}
