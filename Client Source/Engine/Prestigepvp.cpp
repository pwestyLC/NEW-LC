#include "StdH.h"
#include <Engine/Interface/UIInternalClasses.h>

#include "Prestigepvp.h"

#include <Engine/Entities/TradeItem.h>
#include <Engine/Network/CNetwork.h>
#include <Common/Packet/ptype_old_do_item.h>
#include <common/header/EventTrade.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Info/MyInfo.h>

#ifdef PRESTIGE
extern INDEX g_iXPosInCharInfo;
extern INDEX g_iYPosInCharInfo;

#define BATTLE_PASS_BAR_PROGRESS_WIDTH 232

#define BP_PAGE_LEFT 	0
#define BP_PAGE_RIGHT 	1
#define BP_PAGE_MAX 	10

//#define SHOW_BATTLE_PASS_INFO

class CmdBattlePassClose : public Command
{
public:
	CmdBattlePassClose() : m_pWnd(NULL) {}
	void setData(CUIBattlePass* pWnd) { m_pWnd = pWnd; }
	void execute()
	{
		if (m_pWnd)
			m_pWnd->CloseUI();
	}

private:
	CUIBattlePass* m_pWnd;
};

class CmdBattlePassExchangeSend : public Command
{
public:
	CmdBattlePassExchangeSend() : m_pWnd(NULL) {}
	void setData(CUIBattlePass* pWnd) { m_pWnd = pWnd; }
	void execute()
	{
		if (m_pWnd)
			m_pWnd->SendExchangeExp();
	}

private:
	CUIBattlePass* m_pWnd;
};

class CmdBattlePassPageLeft : public Command
{
public:
	CmdBattlePassPageLeft() : m_pWnd(NULL) {}
	void setData(CUIBattlePass* pWnd) { m_pWnd = pWnd; }
	void execute()
	{
		if (m_pWnd)
			m_pWnd->SendPageChanged(BP_PAGE_LEFT);
	}

private:
	CUIBattlePass* m_pWnd;
};

class CmdBattlePassPageRight : public Command
{
public:
	CmdBattlePassPageRight() : m_pWnd(NULL) {}
	void setData(CUIBattlePass* pWnd) { m_pWnd = pWnd; }
	void execute()
	{
		if (m_pWnd)
			m_pWnd->SendPageChanged(BP_PAGE_RIGHT);
	}

private:
	CUIBattlePass* m_pWnd;
};

CUIBattlePass::CUIBattlePass()
	: m_pBtnOk(NULL)
	, m_pDragArea(NULL)
	, m_pTextTitle(NULL)
	, m_pTextProgress(NULL)
	, m_pImgBarProgrss(NULL)
	, m_pointBarProgress(NULL)//Cloud add
	, m_pTextCurrentLevel(NULL)
	, m_pTextNextLevel(NULL)//Cloud add
	, m_pBaseInfo(NULL)
	, m_pBtnPageLeft(NULL)
	, m_pBtnPageRight(NULL)
	, m_nOriX(0)
	, m_nOriY(0)
	, m_bHasNext(TRUE)
{
	setInherit(false);

	for (int i = 0; i < MAX_BATTLE_PASS; ++i)
	{
		m_pTextLevel[i] = NULL;
		m_iconFree[i] = NULL;
		m_pImgFreeCheck[i] = NULL;
		m_iconPremium[i] = NULL;
		m_pImgPremiumCheck[i] = NULL;
		m_pImgPremiumLock[i] = NULL;
	}
}

CUIBattlePass::~CUIBattlePass()
{
	m_pDragArea = NULL;
	m_pBtnOk = NULL;
	m_pBtnPageLeft = NULL;
	m_pBtnPageRight = NULL;
	m_pTextTitle = NULL;
	m_pTextProgress = NULL;
	m_pImgBarProgrss = NULL;
	m_pointBarProgress = NULL;//Cloud add
	m_pTextCurrentLevel = NULL;
	m_pTextNextLevel = NULL;//Cloud add
	m_pBaseInfo = NULL;
	m_nLevel = 0;
	m_nProgress = 0;
	m_nPoints = 0;
	m_nCurrentPage = 1;
}
void CUIBattlePass::BackPage()
{

	SendPageChanged(BP_PAGE_LEFT);
}

void CUIBattlePass::ForwardPage()
{

	SendPageChanged(BP_PAGE_RIGHT);
}

void CUIBattlePass::initialize()
{
	CUIButton* pClose = (CUIButton*)findUI("btn_close");

	if (pClose)
	{
		pClose->SetCommandFUp(boost::bind(&CUIBattlePass::CloseUI, this));
	}

	m_pBtnOk = (CUIButton*)findUI("btn_ok");

	if (m_pBtnOk)
	{
		m_pBtnOk->SetCommandFUp(boost::bind(&CUIBattlePass::SendExchangeExp, this));
	}

	m_pBtnPageLeft = (CUIButton*)findUI("btn_page_left");
	if (m_pBtnPageLeft)
	{
		m_pBtnPageLeft->SetCommandFUp(boost::bind(&CUIBattlePass::BackPage, this));
	}

	m_pBtnPageRight = (CUIButton*)findUI("btn_page_right");
	if (m_pBtnPageRight)
	{
		m_pBtnPageRight->SetCommandFUp(boost::bind(&CUIBattlePass::ForwardPage, this));
	}

	m_pDragArea = findUI("base_drag_area");
	m_pTextTitle = (CUIText*)findUI("text_title");
	m_pTextProgress = (CUIText*)findUI("text_progress");
	m_pTextCurrentLevel = (CUIText*)findUI("text_current_level");//Cloud add
	m_pTextNextLevel = (CUIText*)findUI("text_next_level");//Cloud add
	m_pImgBarProgrss = (CUIImage*)findUI("img_bar_progress");
	m_pointBarProgress = (CUIProgressBar*)findUI("pb_progress");//Cloud add
	m_pBaseInfo = findUI("base_info");

	CTString strTmp;
	for (int i = 0; i < MAX_BATTLE_PASS; ++i)
	{
		strTmp.PrintF("text_level_%d", i + 1);
		m_pTextLevel[i] = (CUIText*)findUI(strTmp);

		strTmp.PrintF("img_free_icon_%d", i + 1);
		m_iconFree[i] = (CUIIcon*)findUI(strTmp);

		strTmp.PrintF("img_free_check_%d", i + 1);
		m_pImgFreeCheck[i] = (CUIImage*)findUI(strTmp);

		strTmp.PrintF("img_premium_icon_%d", i + 1);
		m_iconPremium[i] = (CUIIcon*)findUI(strTmp);

		strTmp.PrintF("img_premium_check_%d", i + 1);
		m_pImgPremiumCheck[i] = (CUIImage*)findUI(strTmp);

		strTmp.PrintF("img_premium_lock_%d", i + 1);
		m_pImgPremiumLock[i] = (CUIImage*)findUI(strTmp);
	}
}

void CUIBattlePass::OpenUI()
{
	if (IsVisible() == TRUE || GetHide() == FALSE)
		return;

	if (UIMGR()->GetInventory()->IsLocked() == TRUE ||
		UIMGR()->GetInventory()->IsLockedArrange() == TRUE)
	{
		UIMGR()->GetInventory()->ShowLockErrorMessage();
		return;
	}

	SetPos(g_iXPosInCharInfo, g_iYPosInCharInfo);

	m_nCurrentPage = 1;

	UpdateListItem();

	UIMGR()->GetInventory()->Lock(TRUE, TRUE, LOCK_BATTLE_PASS);

	for (int i = 0; i < m_nLevel; i++)
	{
		if (m_pImgFreeCheck[i])
			m_pImgFreeCheck[i]->Hide(FALSE);

		if (m_pImgPremiumCheck[i] && m_nPremium)
			m_pImgPremiumCheck[i]->Hide(FALSE);

		if (m_pImgPremiumLock[i] && m_nPremium)
			m_pImgPremiumLock[i]->Hide(TRUE);
		else if (m_pImgPremiumLock[i] && !m_nPremium)//Cloud add
			m_pImgPremiumLock[i]->Hide(FALSE);
	}

	SetVisible(TRUE);
	Hide(FALSE);

	if (m_pBtnOk != NULL)
		m_pBtnOk->SetEnable(TRUE);

	UIMGR()->RearrangeOrder(UI_BATTLE_PASS, TRUE);
}

void CUIBattlePass::CloseUI()
{
	Hide(TRUE);
	SetVisible(FALSE);

	for (int i = 0; i < m_nLevel; i++)
	{
		if (m_pImgFreeCheck[i])
			m_pImgFreeCheck[i]->Hide(TRUE);

		if (m_pImgPremiumCheck[i])
			m_pImgPremiumCheck[i]->Hide(TRUE);

		if (m_pImgPremiumLock[i])
			m_pImgPremiumLock[i]->Hide(FALSE);
		else if (m_pImgPremiumLock[i] && !m_nPremium)//Cloud add
			m_pImgPremiumLock[i]->Hide(FALSE);
	}

	UIMGR()->GetInventory()->Lock(FALSE, FALSE, LOCK_BATTLE_PASS);
	UIMGR()->RearrangeOrder(UI_BATTLE_PASS, FALSE);
}

void CUIBattlePass::UpdateInfo(int premium, int points, int progress, int level, int season)
{
	m_nPoints = points;
	m_nPremium = premium;
	m_nLevel = level;
	m_nProgress = progress;
	m_nSeason = season;

}

void CUIBattlePass::UpdateListItem()
{
	CTString strTmp;
	int i = 0;

	for (i = 0; i < m_items_free.size(); ++i)
	{
		if (m_iconFree[i] == NULL)
			continue;

		m_iconFree[i]->setData(UBET_ITEM, m_items_free[i].reward.itemIdx);
		m_iconFree[i]->setCount(m_items_free[i].reward.itemCount);

		if (m_pTextLevel[i])
		{
			strTmp.PrintF("%d", m_items_free[i].level);
			m_pTextLevel[i]->SetText(strTmp);
		}
	}

	for (i = 0; i < m_items_premium.size(); ++i)
	{
		if (m_iconPremium[i] == NULL)
			continue;

		m_iconPremium[i]->setData(UBET_ITEM, m_items_premium[i].reward.itemIdx);
		m_iconPremium[i]->setCount(m_items_premium[i].reward.itemCount);

		if (m_pImgPremiumLock[i] && m_nPremium)
			m_pImgPremiumLock[i]->Hide(TRUE);

		else if (m_pImgPremiumLock[i] && !m_nPremium)//Cloud add
			m_pImgPremiumLock[i]->Hide(FALSE);
	}

	if (m_pointBarProgress != NULL)
	{

		SQUAD sqExp = m_nProgress;
		SQUAD sqMaxExp = m_nPoints;

		if (m_nLevel < 30) //was 10
		{
			m_pointBarProgress->SetProgressRange(0, sqMaxExp);
			m_pointBarProgress->OffsetProgressPos(sqExp);
		}
		else
		{
			m_pointBarProgress->SetProgressRange(0, 100);
			m_pointBarProgress->OffsetProgressPos(100);
		}

	}

	if (m_pTextProgress)
	{
		CUIManager* pUIManager = CUIManager::getSingleton();
		CTString CurnProgress;
		CTString CurnPoints;


		CurnProgress.PrintF("%d", m_nProgress);
		pUIManager->InsertCommaToString(CurnProgress);

		CurnPoints.PrintF("%d", m_nPoints);
		pUIManager->InsertCommaToString(CurnPoints);

		if (m_nLevel < 30) //was 10
			strTmp.PrintF("%s / %s", CurnProgress, CurnPoints);
		else
			strTmp.PrintF("Achieved the max battle pass");

		m_pTextProgress->SetText(strTmp);
	}

	if (m_pTextCurrentLevel)
	{
		strTmp.PrintF("Pass Lv.%d", m_nLevel);
		m_pTextCurrentLevel->SetText(strTmp);
	}

	if (m_pTextNextLevel)
	{
		if (m_nLevel < 30) //was 10
			strTmp.PrintF("Lv.%d Next", m_nLevel + 1);
		else
			strTmp.PrintF("Max Level");
		m_pTextNextLevel->SetText(strTmp);
	}

	if (CUITextBox* pTextSeason = (CUITextBox*)m_pBaseInfo->findUI("tb_amend_desc"))
	{
		CTString strString;
		strString.PrintF(_S(8536, "season info."), m_nSeason);

		pTextSeason->SetText(strString);
	}

	if (CUITextBox* pTextSeason = (CUITextBox*)m_pBaseInfo->findUI("tb_reward_desc"))
	{
		CTString strString = _S(8537, "reward info");
		pTextSeason->SetText(strString);
	}

	if (m_pBtnOk)//Cloud add
	{
		if (m_nProgress < m_nPoints)
			m_pBtnOk->Hide(TRUE);
		else
		{
			if (m_nLevel < 30) //was 10
				m_pBtnOk->Hide(FALSE);
			else
				m_pBtnOk->Hide(TRUE);
		}
	}

	/*if (m_pImgBarProgrss)
	{
		float percent = (m_nProgress * 100.0) / (float) m_nPoints;
		int width = (percent * BATTLE_PASS_BAR_PROGRESS_WIDTH) / 100;
		m_pImgBarProgrss->SetWidth(width);
	}*/

	if (m_nCurrentPage == 1)
	{
		m_pBtnPageLeft->Hide(TRUE);
	}
	else
	{
		m_pBtnPageLeft->Hide(FALSE);
	}
	m_pBtnPageRight->Hide(HasNext());
}

void CUIBattlePass::SendExchangeExp()
{
	if (UIMGR()->GetInventory()->IsInventoryFull() == TRUE)
	{
		UIMGR()->GetChattingUI()->AddSysMessage(_S(598, ""), SYSMSG_ERROR);
		return;
	}

	if (m_nLevel == 30) //was 10
	{
		CUIManager* pUIManager = CUIManager::getSingleton();
		CTString strMessage;

		CUIMsgBox_Info	MsgBoxInfo;
		strMessage.PrintF(_S(8459, "Battle Pass"));
		MsgBoxInfo.SetMsgBoxInfo(strMessage, UMBS_OK, UI_NONE, MSGCMD_NULL);
		strMessage.PrintF(_S(8514, "Sorry, you already achieved the max battle pass"));
		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);
		return;
	}

	LONGLONG lNpcVIndex = 0;
	CEntity* pEntity = NULL;

	pEntity = INFO()->GetTargetEntity(eTARGET);

	if (pEntity != NULL)
		lNpcVIndex = pEntity->GetNetworkID();	// npc virtual index

	_pNetwork->SendBattlePassReq(lNpcVIndex);

	CloseUI();
}

WMSG_RESULT CUIBattlePass::OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg)
{
	if (m_bHide)
		return WMSG_FAIL;

	if (m_bDrag && (pMsg->wParam & MK_LBUTTON))
	{
		int ndX = x - m_nOriX;
		int ndY = y - m_nOriY;

		m_nOriX = x;
		m_nOriY = y;

		Move(ndX, ndY);
		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	UIMGR()->SetMouseCursorInsideUIs();

	return CUIBase::OnMouseMove(x, y, pMsg);
}

WMSG_RESULT CUIBattlePass::OnLButtonDown(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if (m_pDragArea && m_pDragArea->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}

	UIMGR()->RearrangeOrder(UI_BATTLE_PASS, TRUE);

	return CUIBase::OnLButtonDown(x, y);
}

WMSG_RESULT CUIBattlePass::OnLButtonUp(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	UIMGR()->ResetHoldBtn();

	return CUIBase::OnLButtonUp(x, y);
}

WMSG_RESULT CUIBattlePass::OnLButtonDBLClick(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	return WMSG_SUCCESS;
}

void CUIBattlePass::ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	SetPos((pixMaxI + pixMinI - GetWidth()) / 2, (pixMaxJ + pixMinJ - GetHeight()) / 2);
}

void CUIBattlePass::AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	if (m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ)
		ResetPosition(pixMinI, pixMinJ, pixMaxI, pixMaxJ);
}

void CUIBattlePass::ResetSavePosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	ResetPosition(pixMinI, pixMinJ, pixMaxI, pixMaxJ);
	g_iXPosInCharInfo = GetPosX();
	g_iYPosInCharInfo = GetPosY();
}

void CUIBattlePass::AddItemFree(BattlePassItem item)
{
	m_items_free.push_back(item);
}

void CUIBattlePass::AddItemPremium(BattlePassItem item)
{
	m_items_premium.push_back(item);
}

void CUIBattlePass::SendPageChanged(int page)
{
	if (page == BP_PAGE_LEFT)
	{
		if (m_nCurrentPage - 1 < 1)
			return;

		m_nCurrentPage -= 1;
		_pNetwork->SendPrestigePvPInfoReq(-1, m_nCurrentPage);
	}
	else if (page == BP_PAGE_RIGHT)
	{
		if (m_nCurrentPage + 1 > BP_PAGE_MAX)
			return;

		m_nCurrentPage += 1;
		_pNetwork->SendPrestigePvPInfoReq(-1, m_nCurrentPage);
	}
}

void CUIBattlePass::RefreshUI() {

	UpdateListItem();

	for (int i = 0; i < m_nLevel; i++)
	{
		if (m_pImgFreeCheck[i])
			m_pImgFreeCheck[i]->Hide(FALSE);

		if (m_pImgPremiumCheck[i] && m_nPremium)
			m_pImgPremiumCheck[i]->Hide(FALSE);

		if (m_pImgPremiumLock[i] && m_nPremium)
			m_pImgPremiumLock[i]->Hide(TRUE);
	}
}
#endif