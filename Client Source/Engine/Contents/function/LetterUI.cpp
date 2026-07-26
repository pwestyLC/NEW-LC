#include "StdH.h"
#include <ctime>
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIManager.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/function/MailBoxManager.h>
#include <Engine/Interface/UIMessenger.h>
#include <Engine/Contents/Base/UIMsgBoxNumeric_only.h>
#include "LetterUI.h"

class CmdLetterCountItem : public Command
{
public:
	CmdLetterCountItem() : m_pWnd(NULL) {}
	void setData(CUILetter* pWnd) { m_pWnd = pWnd; }
	void setIconPos(int32_t iconPos) { m_iconPos = iconPos; }
	
	void execute()
	{
		if (m_pWnd)
			m_pWnd->CountItemCallback(m_iconPos);
	}

private:
	CUILetter*	m_pWnd;
	int32_t		m_iconPos;
};

CUILetter::CUILetter()
	: m_jobArray(nullptr)
	, m_moveArea(nullptr)
	, m_mailManager(nullptr)
	, m_curLetter(nullptr)
	, m_messageBox(nullptr)
	, m_windowType(LetterTypes::LetterWrite)
	, nX(0)
	, nY(0)
	, isMove(false)
	, m_selectedUser(false)
{
	memset(&m_UIBlocks, 0, sizeof(CUIBase*) * Areas::MaxArea);
	memset(&m_labels, 0, sizeof(CUIText*) * Texts::MaxText);
	memset(&m_buttons, 0, sizeof(CUIButton*) * Buttons::MaxBtn);
	memset(&m_editBoxes, 0, sizeof(CUIEditBox*) * EditBoxes::MaxEditBox);
	memset(&m_icons, 0, sizeof(CUIIcon*) * LETTER_MAX_ITEMS);
}

CUILetter::~CUILetter()
{
	SAFE_DELETE(m_curLetter);
	Destroy();
}

void CUILetter::initialize()
{
	int32_t i;
	m_jobArray = (CUIImageArray*)findUI("img_job_array");
	m_messageBox = (CUIMultiEditBox*)findUI("edit_message");
	m_moveArea = findUI("base_move");

	for (i = 0; i < LETTER_MAX_ITEMS; i++)
	{
		std::string iconName = boost::str(boost::format("icon_item_%d") % (i + 1));
		m_icons[i] = (CUIIcon*)findUI(iconName.c_str());
		if (m_icons[i]) m_icons[i]->clearIconData();
	}

	std::string textNames[Texts::MaxText] =
	{
		"txt_target_user", "text_sender", "text_send_date",
		"tb_subject_type", "tb_subject_text"
	};

	for (i = 0; i < Texts::MaxText; i++)
	{
		m_labels[i] = (CUIText*)findUI(textNames[i].c_str());
	}

	std::string btnNames[Buttons::MaxBtn] =
	{
		"btn_close", "btn_close2", "btn_search",
		"btn_send", "btn_collect", "btn_delete"
	};

	_ui_func btnActions[Buttons::MaxBtn] =
	{
		boost::bind(&CUILetter::CloseUI, this),
		boost::bind(&CUILetter::CloseUI, this),
		boost::bind(&CUILetter::findUserRequest, this),
		boost::bind(&CUILetter::sendMail, this),
		boost::bind(&CUILetter::collectAttachment, this),
		boost::bind(&CUILetter::deleteMail, this)
	};

	for (i = 0; i < Buttons::MaxBtn; i++)
	{
		m_buttons[i] = (CUIButton*)findUI(btnNames[i].c_str());
		if (m_buttons[i]) m_buttons[i]->SetCommandFUp(btnActions[i]);
	}

	std::string ebNames[EditBoxes::MaxEditBox] = { "eb_nick", "eb_subject", "eb_gold" };
	for (i = 0; i < EditBoxes::MaxEditBox; i++)
	{
		m_editBoxes[i] = (CUIEditBox*)findUI(ebNames[i].c_str());
		if (i == EditBoxes::SenderName && m_editBoxes[i])
		{
			m_editBoxes[i]->setInputCallbackF(boost::bind(&CUILetter::targetUserChanged, this));
		}
	}

	std::string areaNames[Areas::MaxArea] = { "base_header_read", "base_header_send" };
	for (i = 0; i < Areas::MaxArea; i++)
	{
		m_UIBlocks[i] = findUI(areaNames[i].c_str());
	}

	std::string imgNames[Images::MaxImage] = { "img_eb_red", "img_eb_green" };
	for (i = 0; i < Images::MaxImage; i++)
	{
		m_images[i] = (CUIImage*)findUI(imgNames[i].c_str());
	}

	if (!m_mailManager)
	{
		m_mailManager = GameDataManager::getSingleton()->GetMailBoxManager();
		m_mailManager->setLetterUI(this);
	}

	PrepareClose();
}

void CUILetter::ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	SetPos((pixMaxI + pixMinI - GetWidth()) / 2, (pixMaxJ + pixMinJ - GetHeight()) / 2);
}

void CUILetter::AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	if (m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ)
		ResetPosition(pixMinI, pixMinJ, pixMaxI, pixMaxJ);
}

void CUILetter::OpenUI(LetterTypes letterType)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (letterType == LetterWrite && 
		!pUIManager->GetInventory()->IsLocked() &&
		!pUIManager->GetInventory()->IsLockedArrange())
	{
		pUIManager->GetInventory()->Lock(TRUE, TRUE, LOCK_MAILBOX_LETTER);
		pUIManager->RearrangeOrder(UI_INVENTORY, TRUE);
	}
	else if (letterType != LetterWrite)
	{
		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_MAILBOX_LETTER);
	}

	if (IsVisible())
	{
		PrepareClose();
	}

	PrepareOpen(letterType);
	m_windowType = letterType;

	pUIManager->RearrangeOrder(UI_LETTER, TRUE);
}

void CUILetter::CloseUI()
{
	PrepareClose();

	SAFE_DELETE(m_curLetter);

	if (m_mailManager->IsLock())
		m_mailManager->Unlock();

	UIMGR()->GetMsgBoxNumOnly()->CloseBox();

	UIMGR()->GetInventory()->Lock(FALSE, FALSE, LOCK_MAILBOX_LETTER);
	UIMGR()->RearrangeOrder(UI_LETTER, FALSE);
}

void CUILetter::PrepareOpen(LetterTypes letterTypes)
{
	switch (letterTypes)
	{
	case LetterSended:
		m_UIBlocks[Areas::ReceiveArea]->Hide(FALSE);
		m_buttons[Buttons::Delete]->Hide(FALSE);
		m_editBoxes[EditBoxes::Gold]->SetEnable(FALSE);
		m_labels[Texts::TargetUserType]->SetText(_S(8449,"Receiver"));
		break;
	case LetterReceived:
		m_UIBlocks[Areas::ReceiveArea]->Hide(FALSE);
		m_buttons[Buttons::Delete]->Hide(FALSE);
		m_buttons[Buttons::Collect]->Hide(FALSE);
		m_editBoxes[EditBoxes::Gold]->SetEnable(FALSE);
		m_labels[Texts::TargetUserType]->SetText(_S(8450,"Sender"));
		break;
	case LetterWrite:
		m_UIBlocks[Areas::WriteLetterArea]->Hide(FALSE);
		m_images[Images::NotFoundUser]->Hide(FALSE);
		m_images[Images::FoundUser]->Hide(TRUE);
		m_buttons[Buttons::Send]->Hide(FALSE);
		m_editBoxes[EditBoxes::Gold]->SetString("0");
		m_messageBox->SetEnable(TRUE);
		break;
	}

	m_messageBox->ResetString();
}

void CUILetter::PrepareClose()
{
	int32_t i;
	for (i = 0; i < LETTER_MAX_ITEMS; i++)
	{
		if (m_icons[i])
		{
			CItems* item = m_icons[i]->getItems();
			if (item) m_icons[i]->clearIconData();
		}
	}

	for (i = Buttons::Send; i < Buttons::MaxBtn; i++)
	{
		if (m_buttons[i]) m_buttons[i]->Hide(TRUE);
	}

	for (i = 0; i < EditBoxes::MaxEditBox; i++)
	{
		if (m_editBoxes[i])
		{
			m_editBoxes[i]->ResetString();
			m_editBoxes[i]->SetEnable(TRUE);
		}
	}

	for (i = Texts::Sender; i < Texts::MaxText; i++)
	{
		if (i == Texts::SubjectType) continue;
		if (m_labels[i]) m_labels[i]->SetText(CTString(""));
	}

	for (i = 0; i < Areas::MaxArea; i++)
	{
		if (m_UIBlocks[i]) m_UIBlocks[i]->Hide(TRUE);
	}

	m_messageBox->SetEnable(FALSE);
}

void CUILetter::UpdateUI()
{
	if (!m_curLetter) return;

	if (m_windowType == LetterTypes::LetterReceived || m_windowType == LetterTypes::LetterSended)
	{
		m_jobArray->SetRenderIdx(m_curLetter->senderJob);
		m_labels[Texts::Sender]->SetText(CTString(m_curLetter->targetUser));

		char timeBuf[64] = { 0, };
		const tm* timeInfo = localtime((time_t*)&m_curLetter->recvTime);
		strftime(timeBuf, 64, "%d/%m/%Y %H:%M", timeInfo);

		m_labels[Texts::Date]->SetText(CTString(timeBuf));

		if (m_curLetter->senderType == MailSenderTypes::System)
		{
			m_labels[Texts::SubjectType]->Hide(FALSE);
			m_labels[Texts::Subject]->SetPos(62, 66);
		}
		else
		{
			m_labels[Texts::SubjectType]->Hide(TRUE);
			m_labels[Texts::Subject]->SetPos(11, 66);
		}

		if (m_windowType == LetterTypes::LetterReceived && m_curLetter && !m_curLetter->haveAttachment)
		{
			m_buttons[Buttons::Collect]->Hide(TRUE);
		}

		m_labels[Texts::Subject]->SetText(CTString(m_curLetter->subject));
		m_messageBox->SetString(m_curLetter->message, NULL, NULL);

		CTString nas;
		nas.PrintF("%I64d", m_curLetter->nas);
		CUIManager::getSingleton()->InsertCommaToString(nas);
		m_editBoxes[EditBoxes::Gold]->SetString(nas.str_String);

		for (int32_t i = 0; i < m_curLetter->itemsCount; i++)
		{
			ExpressSystemItemInfo* pInfo = &m_curLetter->list[i];
			CItemData* pItemData = _pNetwork->GetItemData(pInfo->item_index);
			if (pItemData == NULL)
				continue;

			CItems* pItems = new CItems;
			pItems->Item_Index = pInfo->item_index;
			pItems->Item_UniIndex = pInfo->index;
			pItems->Item_Flag = pInfo->flag;
			pItems->Item_Plus = pInfo->plus;
			pItems->Item_State_Plus = pInfo->plus2;

#ifdef	DURABILITY
			pItems->Item_durability_now = pInfo->now_durability;
			pItems->Item_durability_max = pInfo->max_durability;
#endif	// DURABILITY

			pItems->ItemData = pItemData;

			if (pItemData->GetFlag() & ITEM_FLAG_RARE)
			{
				if (pInfo->option_count == 0)
				{
					pItems->SetRareIndex(0);
				}
				else
				{
					LONG iRareIndex = pInfo->option_level[0];

					pItems->SetRareIndex(iRareIndex);

					WORD iRareOption = pInfo->option_level[1];
					WORD wCBit = 1;
					SBYTE sbOption = -1;

					for (int iBit = 0; iBit < 10; ++iBit)
					{
						if (iRareOption & wCBit)
						{
							CItemRareOption* prItem = CItemRareOption::getData(iRareIndex);

							if (prItem == NULL)
								continue;

							if (prItem->GetIndex() < 0)
								continue;

							int OptionType = prItem->rareOption[iBit].OptionIdx;
							int OptionLevel = prItem->rareOption[iBit].OptionLevel;
							pItems->SetOptionData(++sbOption, OptionType, OptionLevel, ORIGIN_VAR_DEFAULT);
						}

						wCBit <<= 1;
					}
				}
			}
			else
			{
				if (pItemData->GetFlag() & ITEM_FLAG_ORIGIN)
				{
					int		OpCount;

					for (OpCount = 0; OpCount < MAX_ORIGIN_OPTION; OpCount++)
					{
						pItems->SetOptionData(OpCount, pItemData->GetOptionOriginType(OpCount),
							pItemData->GetOptionOriginLevel(OpCount), pInfo->item_origin[OpCount]);
					}

					for (OpCount = 0; OpCount < MAX_ITEM_SKILL; OpCount++)
					{
						pItems->SetItemSkill(OpCount, pItemData->GetOptionSkillType(OpCount),
							pItemData->GetOptionSkillLevel(OpCount));
					}
				}
				else
				{
					for (int OpCount = 0; OpCount < pInfo->option_count; OpCount++)
					{
						pItems->SetOptionData(OpCount, pInfo->option_type[OpCount],
							pInfo->option_level[OpCount], ORIGIN_VAR_DEFAULT);
					}
				}
			}

			if (!pItems) continue;

			pItems->InitSocketInfo();

			int	socket;
			SBYTE sbSocketCreateCount = 0;

			for (socket = 0; socket < MAX_SOCKET_COUNT; socket++)
			{
				if (pInfo->socket[socket] >= 0)
					sbSocketCreateCount++;
			}

			pItems->SetSocketCount(sbSocketCreateCount);

			for (socket = 0; socket < MAX_SOCKET_COUNT; socket++)
			{
				if (pInfo->socket[socket] >= 0)
					pItems->SetSocketOption(socket, pInfo->socket[socket]);
			}

			m_icons[i]->setData(pItems, false);
			m_icons[i]->setCount(pInfo->item_count);
		}
	}
}

BOOL CUILetter::IsEditBoxFocused()
{
	for (int32_t i = 0; i < EditBoxes::MaxEditBox; i++)
	{
		if (m_editBoxes[i] && m_editBoxes[i]->IsFocused())
			return TRUE;
	}

	return m_messageBox->IsFocused();
}

WMSG_RESULT CUILetter::OnKeyMessage(MSG* pMsg)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (pMsg->wParam == VK_ESCAPE)
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_MAILBOX_ERROR))
		{
			pUIManager->CloseMessageBox(MSGCMD_MAILBOX_ERROR);
			return WMSG_SUCCESS;
		}

		CloseUI();
		return WMSG_SUCCESS;
	}

	return WMSG_FAIL;
}

WMSG_RESULT CUILetter::OnLButtonDown(UINT16 x, UINT16 y)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (m_bHide || !IsVisible())
		return WMSG_FAIL;

	if (!IsInside(x, y))
		return WMSG_FAIL;

	if (pUIManager->DoesMessageBoxExist(MSGCMD_MAILBOX_ERROR))
		return WMSG_SUCCESS;

	if (m_moveArea && m_moveArea->IsInside(x, y))
	{
		isMove = true;
		nX = x;
		nY = y;
		return WMSG_SUCCESS;
	}

	CUIBase::LButtonDownChild(x, y);
	CUIManager::getSingleton()->RearrangeOrder(UI_LETTER, TRUE);
	return WMSG_SUCCESS;
}

WMSG_RESULT CUILetter::OnLButtonUp(UINT16 x, UINT16 y)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if (pUIManager->DoesMessageBoxExist(MSGCMD_MAILBOX_ERROR))
		return WMSG_SUCCESS;

	if (CUIIcon* pDrag = pUIManager->GetDragIcon())
	{
		for (int32_t i = 0; i < LETTER_MAX_ITEMS; i++)
		{
			if (m_icons[i] != NULL && m_icons[i]->IsInside(x, y) && pDrag->getBtnType() == UIBtnExType::UBET_ITEM )
			{
				CItems* item = pDrag->getItems();
				CItemData* itemData = item->ItemData;
				if (canPutItem(item, i))
				{
					CItems* newItem = new CItems;
					memcpy(newItem, item, sizeof(CItems));

					m_icons[i]->setData(newItem);
				}
				else
				{
					m_mailManager->showErrorMessage(MailBoxErrors::IncorrectItem);
				}
			}
		}
		pUIManager->ResetHoldBtn();
		return WMSG_SUCCESS;
	}

	if (m_editBoxes[EditBoxes::SenderName] && m_editBoxes[EditBoxes::SenderName]->IsInside(x, y) && pUIManager->GetMessenger()->GetDrop())
	{
		CMemberInfo friendInfo = pUIManager->GetMessenger()->GetSelectMember();
		m_editBoxes[EditBoxes::SenderName]->SetString(friendInfo.m_strName.str_String);
		pUIManager->GetMessenger()->SetDrop(false);
	}

	isMove = false;
	pUIManager->ResetHoldBtn();
	return WMSG_FAIL;
}

WMSG_RESULT CUILetter::OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg)
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

	CUIManager::getSingleton()->SetMouseCursorInsideUIs();
	return WMSG_FAIL;
}

void CUILetter::setData(MailLetter* letter)
{
	SAFE_DELETE(m_curLetter);
	m_curLetter = letter;

	UpdateUI();
}

void CUILetter::deleteMail()
{
	if (!m_curLetter) return;
	m_mailManager->SendDeleteMailById(getMessageType(), m_curLetter->getIndex());
}

void CUILetter::findUserRequest()
{
	CTString nickname = m_editBoxes[EditBoxes::SenderName]->GetString();
	m_mailManager->SendFindUser(nickname);
}

void CUILetter::collectAttachment()
{
	if (!m_curLetter) return;
	m_mailManager->SendCollectMessage(m_curLetter->getIndex());
}

void CUILetter::sendMail()
{
	if (m_windowType != LetterWrite) return;
	
	if (!m_selectedUser)
	{
		m_mailManager->showErrorMessage(MailBoxErrors::NotFoundUser);
		return;
	}
		
	int32_t itemCount = 0;
	for (int i = 0; i < LETTER_MAX_ITEMS; i++)
	{
		CUIIcon* pIcon = m_icons[i];
		if (!pIcon) continue;

		CItems* pItem = pIcon->getItems();
		if (!pItem) continue;
	
		itemCount++;
	}

	SendingMailLetter* letter = (SendingMailLetter*)malloc(sizeof(SendingMailLetter) +
		12 /* SendingMailLetter::list[0] */ * itemCount);
	memset(letter->targetUser, 0, ARRAYCOUNT(letter->targetUser));
	memset(letter->subject, 0, ARRAYCOUNT(letter->subject));
	memset(letter->message, 0, ARRAYCOUNT(letter->message));

	letter->senderType = MailSenderTypes::User;

	CTString targetUser = m_editBoxes[EditBoxes::SenderName]->GetString();
	strcpy(letter->targetUser, targetUser.str_String);

	CTString subject = m_editBoxes[EditBoxes::SubjectText]->GetString();
	if (subject.Length() < 4)
	{
		m_mailManager->showErrorMessage(MailBoxErrors::SubjectInvalidLenght);
		return;
	}

	strcpy(letter->subject, subject.str_String);

	CTString message = m_messageBox->GetString();
	strcpy(letter->message, message.str_String);

	letter->nas = _atoi64(m_editBoxes[EditBoxes::Gold]->GetString());

	for (int i = 0; i < LETTER_MAX_ITEMS; i++)
	{
		CUIIcon* pIcon = m_icons[i];
		if (!pIcon) continue;

		CItems* pItem = pIcon->getItems();
		if (!pItem) continue;

		letter->list[i].tab = pItem->Item_Tab;
		letter->list[i].invenIndex = pItem->InvenIndex;
		letter->list[i].virtualIndex = pItem->Item_UniIndex;
		letter->list[i].count = pItem->Item_Sum;

	}

	letter->itemCount = itemCount;
	m_mailManager->SendLetter(*letter);
	delete letter;
}

void CUILetter::updateFindUser(bool isFind)
{
	m_images[Images::FoundUser]->Hide(!isFind);
	m_images[Images::NotFoundUser]->Hide(isFind);
	m_selectedUser = isFind;
}

void CUILetter::targetUserChanged()
{
	m_images[Images::FoundUser]->Hide(TRUE);
	m_images[Images::NotFoundUser]->Hide(FALSE);

	m_selectedUser = false;
}

MailBoxMessageTypes CUILetter::getMessageType()
{
	if (!m_curLetter) return MailBoxMessageTypes::Received;
	else if (m_curLetter->isMeLetter) return MailBoxMessageTypes::Sent;
	else if (m_curLetter->senderType == MailSenderTypes::System) return MailBoxMessageTypes::SystemMails;
	else return MailBoxMessageTypes::Received;
}

bool CUILetter::canPutItem(CItems* item, int32_t iconPos)
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CItemData* itemData = item->ItemData;
	CUIIcon* pDrag = pUIManager->GetDragIcon();
	
	if (!pDrag)
		return false;

	if (!item || !itemData) 
		return false;

	if (pDrag->getBtnType() != UBET_ITEM)
		return false;

	if (item->Item_UniIndex != pUIManager->GetInventory()->GetItemUniIndex(item->Item_Tab, item->InvenIndex))
		return false;

	for (int i = 0; i < LETTER_MAX_ITEMS; i++)
	{
		if (m_icons[i])
		{
			CItems* iconItem = m_icons[i]->getItems();
			if (iconItem)
			{
				if (iconItem->Item_Tab == item->Item_Tab &&
					iconItem->InvenIndex == item->InvenIndex)
				{
					return false;
				}
			}
		}
	}

	if (item->IsFlag(FLAG_ITEM_LENT))
		return false;

	if (item->IsFlag(FLAG_ITEM_BELONG))
		return false;

	if (item->IsFlag(FLAG_ITEM_COMPOSITION))
		return false;

	if (item->IsFlag(PLATINUM_MAX_PLUS))
		return false;

	if (!itemData->IsFlag(ITEM_FLAG_EXCHANGE))
		return false;

	if (itemData->GetType() == CItemData::ITEM_ACCESSORY &&
		(itemData->GetSubType() == CItemData::ACCESSORY_WILDPET || itemData->GetSubType() == CItemData::ACCESSORY_PET))
		return false;

	if (itemData->GetType() == CItemData::ITEM_ETC && itemData->GetSubType() == CItemData::ITEM_ETC_MONSTER_MERCENARY_CARD)
		return false;

	if (itemData->GetType() == CItemData::ITEM_ACCESSORY && itemData->GetSubType() == CItemData::ACCESSORY_RELIC)
		return false;

	if (itemData->IsFlag(ITEM_FLAG_COUNT))
	{
		CTString strMessage;
		const char* szItemName = _pNetwork->GetItemName(item->Item_Index);
		strMessage.PrintF(_S(150, "�� ���� %s�� �ű�ðڽ��ϱ�?"), szItemName);

		UIMGR()->GetMsgBoxNumOnly()->CloseBox();
		CmdLetterCountItem* pCmd = new CmdLetterCountItem;
		pCmd->setData(this);
		pCmd->setIconPos(iconPos);
		UIMGR()->GetMsgBoxNumOnly()->SetInfo(pCmd, _S(191, "Ȯ��"), strMessage, 1, item->Item_Sum);
	}

	return true;
}

void CUILetter::CountItemCallback(int iconPos)
{
	if (m_icons[iconPos])
	{
		SQUAD itemCount = UIMGR()->GetMsgBoxNumOnly()->GetData();
		CItems* item = m_icons[iconPos]->getItems();
		if (item && itemCount > 0)
		{
			item->Item_Sum = itemCount;
			m_icons[iconPos]->setData(item);
		}
	}
}

void CUILetter::collected()
{
	if (m_buttons[Buttons::Collect])
	{
		m_buttons[Buttons::Collect]->Hide(TRUE);
	}

	if (m_editBoxes[EditBoxes::Gold])
	{
		m_editBoxes[EditBoxes::Gold]->SetString("0");
	}

	for (int32_t i = 0; i < LETTER_MAX_ITEMS; i++)
	{
		if (m_icons[i]) m_icons[i]->clearIconData();
	}
}
