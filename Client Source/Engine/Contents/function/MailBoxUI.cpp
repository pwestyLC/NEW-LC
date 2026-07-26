#include "StdH.h"
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIMessenger.h>
#include <Engine/Contents/function/MailBoxManager.h>
#include <Engine/Contents/function/LetterUI.h>
#include "MailBoxUI.h"

CUIMailBox::CUIMailBox()
	: m_tab(nullptr)
	, m_moveArea(nullptr)
	, m_pManager(nullptr)
	, isMove(false)
	, nX(0)
	, nY(0)
{
	memset(&m_lists, 0, sizeof(CUIList*) * Lists::MaxList);
	memset(&m_buttons, 0, sizeof(CUIButton*) * Buttons::MaxBtn);
}

CUIMailBox::~CUIMailBox()
{
	Destroy();
}

void CUIMailBox::initialize()
{
	m_tab = (CUITab*)findUI("tab_ui");
	m_moveArea = findUI("base_move");
	std::string btnNames[Buttons::MaxBtn] =
	{
		"btn_close", "btn_delete_all", "btn_write",
		"btn_open", "btn_delete", "btn_refresh"
	};

	_ui_func btnFunctions[Buttons::MaxBtn] =
	{
		boost::bind(&CUIMailBox::CloseUI, this),
		boost::bind(&CUIMailBox::RequestDeleteAllMails, this),
		boost::bind(&CUIMailBox::WriteLetter, this),
		boost::bind(&CUIMailBox::OpenLetter, this),
		boost::bind(&CUIMailBox::RequestDeleteMail, this),
		boost::bind(&CUIMailBox::RefreshLetters, this)
	};

	for (int32_t i = Buttons::Close; i < Buttons::MaxBtn; i++)
	{
		m_buttons[i] = (CUIButton*)findUI(btnNames[i].c_str());
		if (m_buttons[i])
		{
			m_buttons[i]->SetCommandFUp(btnFunctions[i]);
		}
	}

	std::string listNames[Lists::MaxList] = { "list_received", "list_sent", "list_system" };
	for (int32_t i = Lists::Received; i < Lists::MaxList; i++)
	{
		m_lists[i] = (CUIList*)findUI(listNames[i].c_str());
	}

	m_ptdBaseTexture = CreateTexture("Data\\Interface\\MessageBox.tex");
	FLOAT fTexWidth = m_ptdBaseTexture->GetPixWidth();
	FLOAT fTexHeight = m_ptdBaseTexture->GetPixHeight();

	m_popupMenu.Create(this, 0, 0, 100, 200, _pUIFontTexMgr->GetLineHeight(), 6, 3, 1, TRUE, TRUE);
	m_popupMenu.SetScrollBar(FALSE);
	m_popupMenu.SetSelBar(100, _pUIFontTexMgr->GetLineHeight() + 2, 287, 421, 341, 475, fTexWidth, fTexHeight);
	m_popupMenu.SetOverColor(0xF8E1B5FF);
	m_popupMenu.SetSelectColor(0xF8E1B5FF);
	m_popupMenu.Hide();

	m_popupMenu.m_rtBackUL.SetUV(164, 45, 171, 63, fTexWidth, fTexHeight);
	m_popupMenu.m_rtBackUM.SetUV(174, 45, 176, 63, fTexWidth, fTexHeight);
	m_popupMenu.m_rtBackUR.SetUV(179, 45, 186, 63, fTexWidth, fTexHeight);
	m_popupMenu.m_rtBackML.SetUV(164, 55, 171, 58, fTexWidth, fTexHeight);
	m_popupMenu.m_rtBackMM.SetUV(174, 55, 176, 58, fTexWidth, fTexHeight);
	m_popupMenu.m_rtBackMR.SetUV(179, 55, 186, 58, fTexWidth, fTexHeight);
	m_popupMenu.m_rtBackLL.SetUV(164, 60, 171, 68, fTexWidth, fTexHeight);
	m_popupMenu.m_rtBackLM.SetUV(174, 60, 176, 68, fTexWidth, fTexHeight);
	m_popupMenu.m_rtBackLR.SetUV(179, 60, 186, 68, fTexWidth, fTexHeight);
}

void CUIMailBox::ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	SetPos((pixMaxI + pixMinI - GetWidth()) / 2, (pixMaxJ + pixMinJ - GetHeight()) / 2);
}

void CUIMailBox::AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	if (m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ)
		ResetPosition(pixMinI, pixMinJ, pixMaxI, pixMaxJ);
}

void CUIMailBox::OpenUI()
{
	if (IsVisible())
		return;

	if (!m_pManager)
	{
		m_pManager = GameDataManager::getSingleton()->GetMailBoxManager();
		m_pManager->setMailBoxUI(this);
	}

	PrepareOpening();
	UIMGR()->RearrangeOrder(UI_MAIL_BOX, TRUE);
}

void CUIMailBox::CloseUI()
{
	PrepareClosing();

	if (m_pManager->GetUILetter()->IsVisible()) m_pManager->GetUILetter()->CloseUI();
	
	UIMGR()->RearrangeOrder(UI_MAIL_BOX, FALSE);
}

void CUIMailBox::OnPostRender(CDrawPort* pDraw)
{
	pDraw->InitTextureData(m_ptdBaseTexture);

	m_popupMenu.Render();

	pDraw->FlushRenderingQueue();
	pDraw->EndTextEx();
}

void CUIMailBox::UpdateUI()
{
	ClearListsItems();

	MailBoxManager::mails_map_ mails = m_pManager->getMails();
	MailBoxManager::mails_map_::iterator mails_begin = mails.begin();
	for (; mails_begin != mails.end(); mails_begin++)
	{
		MailBoxMessageTypes pageType = (*mails_begin).first;
		std::vector<MailCardInfo*> vec = (*mails_begin).second;
		std::vector<MailCardInfo*>::iterator vec_iter = vec.begin();
		for (; vec_iter != vec.end(); vec_iter++)
		{
			CUIText* pText;
			CUIImage* pImage;
			MailCardInfo* pMail = *vec_iter;

			if (!pMail) return;

			CUIList* pList = m_lists[pageType];
			if (!pList) return;
			
			CUIListItem* pItemTemplate = (CUIListItem*)pList->GetListItemTemplate()->Clone();
			if (!pItemTemplate) return;

			pList->AddListItem(pItemTemplate);

			// Set target user text
			pText = (CUIText*)pItemTemplate->findUI("txt_nick");
			if (pText) pText->SetText(CTString(pMail->targetUser));

			// Set mail subject
			pText = (CUIText*)pItemTemplate->findUI("txt_subject");
			if (pText) pText->SetText(CTString(pMail->subject));

			// Set recv mail time
			pText = (CUIText*)pItemTemplate->findUI("txt_recv_time");
			if (pText)
			{
				time_t curTime = time(0);
				time_t diffTime = curTime - pMail->recvTime;
				CTString time;

				if (diffTime < 60)
				{
					time.PrintF("%d sec ago", diffTime);
				}
				else if (diffTime < 60 * 60)
				{
					time.PrintF("%d min ago", diffTime / 60);
				}
				else
				{
					char timeBuf[64] = { 0, };
					const tm* timeInfo = localtime((time_t*)&pMail->recvTime);
					strftime(timeBuf, 64, "%d/%m/%Y %H:%M", timeInfo);
					time.PrintF(timeBuf);
				}

				pText->SetText(time);
			}
			
			// Change hide status for 'gift' icon
			pImage = (CUIImage*)pItemTemplate->findUI("img_attached");
			if (pImage) pImage->Hide(!pMail->haveAttachment);

			// Set read/unread icon
			{
				pImage = (CUIImage*)pItemTemplate->findUI("img_readed");
				if (pImage) pImage->Hide(!pMail->isRead);

				pImage = (CUIImage*)pItemTemplate->findUI("img_nreaded");
				if (pImage) pImage->Hide(pMail->isRead);
			}
		}

		// Update thumb
		if (m_lists[pageType]->GetScroll())
		{
			m_lists[pageType]->GetScroll()->SetScrollPos(0);
			m_lists[pageType]->UpdateScroll(vec.size());
		}

		m_lists[pageType]->UpdateList();
	}
}

void CUIMailBox::PrepareOpening()
{
	m_tab->ResetTabPos();
	m_pManager->SendListReq(MailBoxMessageTypes::Received, -1);
	m_pManager->SendListReq(MailBoxMessageTypes::Sent, -1);
	m_pManager->SendListReq(MailBoxMessageTypes::SystemMails, -1);
}

void CUIMailBox::PrepareClosing()
{
	ClearListsItems();

	MailBoxManager::mails_map_ mails = m_pManager->getMails();
	MailBoxManager::mails_map_::iterator mails_begin = mails.begin();
	for (; mails_begin != mails.end(); mails_begin++)
	{
		std::vector<MailCardInfo*> vec = (*mails_begin).second;
		std::vector<MailCardInfo*>::iterator vec_iter = vec.begin();
		for (; vec_iter != vec.end(); vec_iter++)
		{
			MailCardInfo* pMail = *vec_iter;
			SAFE_DELETE(pMail);
		}
	}

	m_pManager->clearMails();
}

void CUIMailBox::ClearListsItems()
{
	for (int32_t i = Lists::Received; i < Lists::MaxList; i++)
	{
		if (m_lists[i])
		{
			m_lists[i]->DeleteAllListItem();
		}
	}
}

WMSG_RESULT CUIMailBox::OnKeyMessage(MSG* pMsg)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (!IsVisible())
		return WMSG_FAIL;

	if (pMsg->wParam == VK_ESCAPE)
	{
		int messageBoxes[3] = { MSGCMD_MAILBOX_ERROR, MSGCMD_MAILBOX_DELETE, MSGCMD_MAILBOX_DELETE_ALL };
		for (int i = 0; i < 3; i++)
		{
			if (pUIManager->DoesMessageBoxExist(messageBoxes[i]))
			{
				pUIManager->CloseMessageBox(messageBoxes[i]);
				return WMSG_SUCCESS;
			}
		}

		CloseUI();
		return WMSG_SUCCESS;
	}

	return WMSG_FAIL;
}

WMSG_RESULT CUIMailBox::OnLButtonDown(UINT16 x, UINT16 y)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (m_bHide || !IsVisible())
		return WMSG_FAIL;

	if (!IsInside(x, y))
		return WMSG_FAIL;

	int messageBoxes[3] = { MSGCMD_MAILBOX_ERROR, MSGCMD_MAILBOX_DELETE, MSGCMD_MAILBOX_DELETE_ALL };
	for (int i = 0; i < 3; i++)
	{
		if (pUIManager->DoesMessageBoxExist(messageBoxes[i]))
			return WMSG_SUCCESS;
	}

	if (m_moveArea && m_moveArea->IsInside(x, y))
	{
		isMove = true;
		nX = x;
		nY = y;
		return WMSG_SUCCESS;
	}

	// Popup menu havent only MouseMessage handler,
	//I create mouse event and call handler
	{
		MSG mouseMsg;
		mouseMsg.message = WM_LBUTTONDOWN;
		mouseMsg.lParam = MAKELONG(x, y);

		if (m_popupMenu.MouseMessage(&mouseMsg) != WMSG_FAIL)
			return WMSG_SUCCESS;

		m_popupMenu.Hide();
	}


	CUIBase::LButtonDownChild(x, y);
	return WMSG_SUCCESS;
}

WMSG_RESULT CUIMailBox::OnLButtonDBLClick(UINT16 x, UINT16 y)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (m_bHide || !IsVisible())
		return WMSG_FAIL;

	if (!IsInside(x, y))
		return WMSG_FAIL;

	int messageBoxes[3] = { MSGCMD_MAILBOX_ERROR, MSGCMD_MAILBOX_DELETE, MSGCMD_MAILBOX_DELETE_ALL };
	for (int i = 0; i < 3; i++)
	{
		if (pUIManager->DoesMessageBoxExist(messageBoxes[i]))
			return WMSG_SUCCESS;
	}

	if (m_tab && m_tab->IsInside(x, y))
	{
		OpenLetter();
	}

	return WMSG_FAIL;
}

WMSG_RESULT CUIMailBox::OnRButtonDown(UINT16 x, UINT16 y)
{
	CUIManager* pUIManager = CUIManager::getSingleton();
		
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	MailBoxMessageTypes pageType = (MailBoxMessageTypes)m_tab->getCurSelTab();
	int32_t mailPos = m_lists[pageType]->getMouseOverItem();
	if (pageType == MailBoxMessageTypes::Received && mailPos >= 0)
	{
		m_lists[pageType]->OnLButtonDown(x, y);
		OpenPopupMenu(x, y);
		return WMSG_SUCCESS;
	}

	return WMSG_FAIL;
}

WMSG_RESULT CUIMailBox::OnLButtonUp(UINT16 x, UINT16 y)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	// Popup menu havent only MouseMessage handler,
	//I create mouse event and call handler
	{
		MSG mouseMsg;
		mouseMsg.message = WM_LBUTTONUP;
		mouseMsg.lParam = MAKELONG(x, y);

		if (m_popupMenu.MouseMessage(&mouseMsg) != WMSG_FAIL)
		{
			int32_t actionId = m_popupMenu.GetCurSel();
			switch (actionId)
			{
			case PopupButtons::PopupBlock:
				BlockUser();
				break;
			case PopupButtons::PopupDelete:
			{
				MailBoxMessageTypes pageType = (MailBoxMessageTypes)m_tab->getCurSelTab();
				int32_t mailPos = m_lists[pageType]->getCurSel();
				MailCardInfo* pMail = m_pManager->getMailAt(pageType, mailPos);
				if (pMail->haveAttachment)
					RequestDeleteMail();
				else
					DeleteMail();

			}	break;
			}

			m_popupMenu.Hide();
			return WMSG_SUCCESS;
		}

		m_popupMenu.Hide();
	}

	isMove = false;
	return WMSG_FAIL;
}

WMSG_RESULT CUIMailBox::OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg)
{
	if (m_bHide)
		return WMSG_FAIL;

	if (isMove && (pMsg->wParam & MK_LBUTTON))
	{
		int ndX = x - nX;
		int ndY = y - nY;

		nX = x;
		nY = y;

		Move(ndX, ndY);
		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	// Popup menu havent only MouseMessage handler,
	//I create mouse event and call handler
	{
		MSG moveMsg;
		moveMsg.message = WM_MOUSEMOVE;
		moveMsg.lParam = MAKELONG(x, y);
		m_popupMenu.MouseMessage(&moveMsg);
	}

	CUIManager::getSingleton()->SetMouseCursorInsideUIs();
	return WMSG_FAIL;
}

void CUIMailBox::RequestDeleteMail()
{
	CTString strMessage;
	CUIMsgBox_Info msgBoxInfo;
	CUIManager* pUIManager = CUIManager::getSingleton();

	MailBoxMessageTypes pageType = (MailBoxMessageTypes)m_tab->getCurSelTab();
	int32_t mailPos = m_lists[pageType]->getCurSel();
	if (mailPos < 0) return;

	MailCardInfo* pMail = m_pManager->getMailAt(pageType, mailPos);
	if (!pMail) return;

	msgBoxInfo.SetMsgBoxInfo(CTString("Notify"), UMBS_OKCANCEL, UI_MAIL_BOX, MSGCMD_MAILBOX_DELETE);

	if (pMail->haveAttachment)
	{
		strMessage.PrintF("Mail has attachments inside . you sure you want to delete this mail?");
	}
	else
	{
		strMessage.PrintF("Are you sure you want to delete this mail?");
	}

	msgBoxInfo.AddString(strMessage);
	pUIManager->CreateMessageBox(msgBoxInfo);
}

void CUIMailBox::RequestDeleteAllMails()
{
	if (m_pManager->IsMessageOpen()) return;

	CTString strMessage;
	CUIMsgBox_Info msgBoxInfo;
	CUIManager* pUIManager = CUIManager::getSingleton();

	msgBoxInfo.SetMsgBoxInfo(CTString("Notify"), UMBS_OKCANCEL, UI_MAIL_BOX, MSGCMD_MAILBOX_DELETE_ALL);
	strMessage.PrintF("%s", "U want delete all mails?");

	msgBoxInfo.AddString(strMessage);
	pUIManager->CreateMessageBox(msgBoxInfo);
}

void CUIMailBox::DeleteMail()
{
	MailBoxMessageTypes pageType = (MailBoxMessageTypes)m_tab->getCurSelTab();
	int32_t mailPos = m_lists[pageType]->getCurSel();
	if(mailPos >= 0) m_pManager->SendDeleteMail(pageType, mailPos);
}

void CUIMailBox::DeleteAllMails()
{
	MailBoxMessageTypes pageType = (MailBoxMessageTypes)m_tab->getCurSelTab();
	m_pManager->SendDeleteAllMails(pageType);
}

void CUIMailBox::RefreshLetters()
{
	if (m_pManager->IsMessageOpen()) return;

	MailBoxMessageTypes pageType = (MailBoxMessageTypes)m_tab->getCurSelTab();

	if (m_lists[pageType])
	{
		m_lists[pageType]->DeleteAllListItem();
	}

	MailBoxManager::mails_map_ mails = m_pManager->getMails();
	std::vector<MailCardInfo*> vec = mails[pageType];
	std::vector<MailCardInfo*>::iterator vec_iter = vec.begin();
	for (; vec_iter != vec.end(); vec_iter++)
	{
		MailCardInfo* pMail = *vec_iter;
		SAFE_DELETE(pMail);
	}

	m_pManager->clearMails(pageType);
	m_pManager->SendListReq(pageType, -1);
}

void CUIMailBox::WriteLetter()
{
	if (m_pManager->IsMessageOpen()) return;

	if (m_pManager->IsLock())
	{
		m_pManager->showErrorMessage(MailBoxErrors::AlreadyUsed);
		return;
	}

	UIMGR()->GetLetterBox()->OpenUI(LetterTypes::LetterWrite);
}

void CUIMailBox::MsgBoxCommand(int nCommandCode, BOOL bOK, CTString& strInput)
{
	if (bOK == TRUE)
	{
		switch (nCommandCode)
		{
			case MSGCMD_MAILBOX_DELETE:
				DeleteMail();
				break;

			case MSGCMD_MAILBOX_DELETE_ALL:
				DeleteAllMails();
				break;
		}
	}
}

void CUIMailBox::MarkAsReaded(int page, int pos)
{
	if (m_lists[page])
	{
		CUIImage* pImage = nullptr;
		CUIListItem* pItem = (CUIListItem*)m_lists[page]->GetListItem(pos);
		if (pItem)
		{
			pImage = (CUIImage*)pItem->findUI("img_readed");
			if (pImage) pImage->Hide(FALSE);

			pImage = (CUIImage*)pItem->findUI("img_nreaded");
			if (pImage) pImage->Hide(TRUE);
		}
	}
}

void CUIMailBox::MarkAsCollected(int page, int pos)
{
	if (m_lists[page])
	{
		CUIImage* pImage = nullptr;
		CUIListItem* pItem = (CUIListItem*)m_lists[page]->GetListItem(pos);
		if (pItem)
		{
			pImage = (CUIImage*)pItem->findUI("img_attached");
			if (pImage) pImage->Hide(TRUE);
		}
	}
}

void CUIMailBox::OpenLetter()
{
	if (m_pManager->IsMessageOpen()) return;

	if (!m_pManager->IsLock())
	{
		MailBoxMessageTypes pageType = (MailBoxMessageTypes)m_tab->getCurSelTab();
		if (pageType >= 0 && pageType < Lists::MaxList)
		{
			int32_t curItemIdx = m_lists[pageType]->getCurSel();
			if (curItemIdx >= 0)
			{
				m_pManager->SendOpenMail(pageType, curItemIdx);
			}
		}
	}
}

void CUIMailBox::OpenPopupMenu(UINT16 x, UINT16 y)
{
	MailBoxMessageTypes pageType = (MailBoxMessageTypes)m_tab->getCurSelTab();
	int32_t mailPos = m_lists[pageType]->getCurSel();

	if (mailPos >= 0)
	{
		MailCardInfo* mailCard = m_pManager->getMailAt(pageType, mailPos);

		m_popupMenu.ResetAllStrings();
		std::string str = boost::str(boost::format("User: %s") % mailCard->targetUser);
		m_popupMenu.AddMenuList(str.c_str(), 0xC2BAC5FF);

		if (UIMGR()->GetMessenger()->FindBlockMember(mailCard->targetUser).m_nCharIndex > 0)
		{
			m_popupMenu.AddMenuList("Unblock", 0xFFFFFFFF, PopupButtons::PopupBlock);
		}
		else
		{
			m_popupMenu.AddMenuList("Block", 0xFFFFFFFF, PopupButtons::PopupBlock);
		}

		m_popupMenu.AddMenuList("Delete", 0xFFFFFFFF, PopupButtons::PopupDelete);

		CUIBase* letterBlock = m_lists[pageType]->GetListItem(mailPos);
		int localX = x - this->GetAbsPosX();
		int localY = y - this->GetAbsPosY();
		m_popupMenu.SetPos(localX, localY);
		m_popupMenu.Show();
	}
}

void CUIMailBox::BlockUser()
{
	MailBoxMessageTypes pageType = (MailBoxMessageTypes)m_tab->getCurSelTab();
	int32_t mailPos = m_lists[pageType]->getCurSel();

	if (mailPos >= 0)
	{
		MailCardInfo* mailCard = m_pManager->getMailAt(pageType, mailPos);

		if (UIMGR()->GetMessenger()->FindBlockMember(mailCard->targetUser).m_nCharIndex > 0)
		{
			_pNetwork->MgrUnBlock(mailCard->targetIndex);
		}
		else
		{
			_pNetwork->MgrBlock(mailCard->targetUser);
		}
	}
}

void CUIMailBox::SelectLastMail()
{
	int32_t curTab = m_tab->getCurSelTab();
	if (m_lists[curTab] && m_lists[curTab]->GetItemCount() > 0)
	{

		m_lists[curTab]->setCurSel(0);
	}
}
