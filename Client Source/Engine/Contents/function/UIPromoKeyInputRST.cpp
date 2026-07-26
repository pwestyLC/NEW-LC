#include "stdh.h"
#include <Engine/Interface/UIInternalClasses.h>

#include "UIPromoKeyInputRST.h"

#include "Info/MyInfo.h"
#include "Interface/UIInventory.h"
#include "Interface/UIManager.h"

constexpr int MAX_PROMO_KEY_LENGTH = 16;

CUIPromoKeyInputRST::CUIPromoKeyInputRST()
	: m_bDrag(false),
	m_Drag(nullptr)
{
	m_nOldX = 0;
	m_nOldY = 0;
}

CUIPromoKeyInputRST::~CUIPromoKeyInputRST()
{
}

void CUIPromoKeyInputRST::initialize()
{
	m_Drag = findUI("drag");

	m_pEditBoxKey = dynamic_cast<CUIEditBox*>(findUI("edit_key"));

	const CTString btnName[eBTN_MAX] = { "close", "apply" };
	for (int i = 0; i < eBTN_MAX; i++)
	{
		m_btn[i] = dynamic_cast<CUIButton*>(findUI("btn_" + btnName[i]));
	}

	m_btn[eBTN_CLOSE]->SetCommandFUp(boost::bind(&CUIPromoKeyInputRST::closeUI, this));
	m_btn[eBTN_APPLY]->SetCommandFUp(boost::bind(&CUIPromoKeyInputRST::OnSendPromoKey, this));
}

void CUIPromoKeyInputRST::openUI()
{
	if (IsVisible() != FALSE)
		return;

	m_pEditBoxKey->ResetString();

	SetVisible(TRUE);
	Hide(FALSE);

	CUIManager* pUIMgr = CUIManager::getSingleton();
	pUIMgr->RearrangeOrder(UI_PROMO_KEY_INPUT_RST, TRUE);
}

void CUIPromoKeyInputRST::closeUI()
{
	Hide(TRUE);
	SetVisible(FALSE);

	CUIManager* pUIMgr = UIMGR();
	pUIMgr->RearrangeOrder(UI_PROMO_KEY_INPUT_RST, FALSE);
}

void CUIPromoKeyInputRST::ToggleVisible()
{
	if (IsVisible())
		closeUI();
	else
		openUI();
}

WMSG_RESULT CUIPromoKeyInputRST::OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg)
{
	static int m_oldX, m_oldY;

	int ndXx = x - m_nOldX;
	int ndYy = y - m_nOldY;

	if (m_bHide)
		return WMSG_FAIL;

	if (m_bDrag)
	{
		m_nOldX = x; m_nOldY = y;
		Move(ndXx, ndYy);

		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;


	return WMSG_FAIL;
}

WMSG_RESULT CUIPromoKeyInputRST::OnLButtonDown(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	m_nOldX = x;
	m_nOldY = y;

	if (m_Drag->IsInside(x, y) == TRUE)
	{
		m_bDrag = true;
		return WMSG_SUCCESS;
	}

	return WMSG_FAIL;
}

WMSG_RESULT CUIPromoKeyInputRST::OnLButtonUp(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	return WMSG_FAIL;
}

WMSG_RESULT CUIPromoKeyInputRST::OnCharMessage(MSG* pMsg)
{
	return CUIWindow::OnCharMessage(pMsg);
}

WMSG_RESULT CUIPromoKeyInputRST::OnIMEMessage(MSG* pMsg)
{
	return WMSG_FAIL;
}

BOOL CUIPromoKeyInputRST::IsEditBoxFocused()
{
	return m_pEditBoxKey->IsFocused();
}

void CUIPromoKeyInputRST::KillFocusEditBox()
{
	m_pEditBoxKey->SetFocus(FALSE);
}

void CUIPromoKeyInputRST::OnSendPromoKey()
{
	if (!CheckPromoKey())
	{
		return;
	}

	CNetworkMessage nmMessage(MSG_EXTEND);
	nmMessage << htonl(MSG_EX_PROMO_KEY);
	nmMessage << static_cast<unsigned char>(MSG_EX_PROMO_KEY_USE_REQ);
	nmMessage << m_pEditBoxKey->GetString();
	_pNetwork->SendToServerNew(nmMessage);

	ToggleVisible();
}

bool CUIPromoKeyInputRST::CheckPromoKey()
{
	std::string strKey = m_pEditBoxKey->GetString();
	if (strKey.empty())
	{
		CTString message = CTString("Please enter the promo key.");
		UIMGR()->GetChattingUI()->AddSysMessage(message, SYSMSG_NOTIFY);
		return false;
	}

	if (strKey.length() > MAX_PROMO_KEY_LENGTH)
	{
		CTString message = CTString("Please enter the promo key correctly.");
		UIMGR()->GetChattingUI()->AddSysMessage(message, SYSMSG_ERROR);
		return false;
	}

	if (strKey.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") != std::string::npos)
	{
		CTString message = CTString("Please enter the promo key correctly.");
		UIMGR()->GetChattingUI()->AddSysMessage(message, SYSMSG_ERROR);
		return false;
	}

	return true;
}
