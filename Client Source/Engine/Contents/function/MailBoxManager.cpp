#include "StdH.h"
#include <Engine/Util.h>
#include <Engine/Network/CNetwork.h>
#include <Engine/Interface/UIManager.h>
#include <Engine/Object/ActorMgr.h>
#include <Engine/Interface/UIRadar.h>
#include <Engine/Interface/UIMessageBox.h>
#include <Engine/Contents/function/MailBoxUI.h>
#include <Engine/Contents/function/LetterUI.h>
#include <Engine/Contents/Base/ChattingUI.h>
#include "MailBoxManager.h"

MailBoxManager::MailBoxManager()
	: m_UI(nullptr)
	, m_letterUI(nullptr)
	, m_bLock(false)
{

}

MailBoxManager::~MailBoxManager()
{
	auto mapBegin = m_mapMails.begin();
	for (; mapBegin != m_mapMails.end(); mapBegin++)
	{
		auto& vec = (*mapBegin).second;
		auto vecBegin = vec.begin();
		for (; vecBegin != vec.end(); vecBegin++)
			SAFE_DELETE(*vecBegin);

		vec.clear();
	}

	m_mapMails.clear();
}

void MailBoxManager::ReceiveMessage(CNetworkMessage* istr)
{
	pTypeBase* packet = reinterpret_cast<pTypeBase*>(istr->nm_pubMessage);
	switch (packet->subType)
	{
	case MSG_SUB_MAILBOX_LIST_FINISH:
	{
		ResponseClient::MailBoxList* pRecv = reinterpret_cast<ResponseClient::MailBoxList*>(istr->nm_pubMessage);
		int test2 = sizeof(*pRecv);
		int test3 = sizeof(pRecv->list[0]);
		int test = test2 + (test3 * pRecv->listCount);
		for (int32_t i = 0; i < pRecv->listCount; i++)
		{
			if (getMailPos(pRecv->list[i].pageType, pRecv->list[i].index) < 0) {
				MailCardInfo* pMailCardInfo = new MailCardInfo;
				pMailCardInfo->index = pRecv->list[i].index;
				pMailCardInfo->senderType = pRecv->list[i].senderType;
				pMailCardInfo->targetIndex = pRecv->list[i].targetIndex;
				pMailCardInfo->recvTime = pRecv->list[i].recvTime;
				pMailCardInfo->haveAttachment = pRecv->list[i].haveAttachment;
				pMailCardInfo->isRead = pRecv->list[i].isRead;

				strcpy(pMailCardInfo->targetUser, pRecv->list[i].targetUser);
				strcpy(pMailCardInfo->subject, pRecv->list[i].subject);

				MailBoxMessageTypes pageType = pRecv->list[i].pageType;

				if (m_mapMails.find(pageType) == m_mapMails.end())
				{
					std::vector<MailCardInfo*> vec;
					vec.push_back(pMailCardInfo);
					m_mapMails.insert(std::make_pair(pageType, vec));
				}
				else
				{
					m_mapMails[pageType].push_back(pMailCardInfo);
				}
			}
		}
		m_UI->UpdateUI();
		UIMGR()->GetRadar()->OffExpressNotice();
		Unlock();
	}break;
	case MSG_SUB_MAILBOX_DELETE:
	{
		ResponseClient::MailBoxDeleteMail* packet = reinterpret_cast<ResponseClient::MailBoxDeleteMail*>(istr->nm_pubMessage);
		deleteMail(packet->pageType, packet->mailId);

		Unlock();
	}break;
	case MSG_SUB_MAILBOX_DELETE_ALL:
	{
		ResponseClient::MailBoxDeleteAll* packet = reinterpret_cast<ResponseClient::MailBoxDeleteAll*>(istr->nm_pubMessage);
		deleteAllMails(packet->pageType);

		Unlock();
	}break;
	case MSG_SUB_MAILBOX_FIND_USER:
	{
		ResponseClient::MailBoxFindUser* packet = reinterpret_cast<ResponseClient::MailBoxFindUser*>(istr->nm_pubMessage);
		m_letterUI->updateFindUser(packet->isFind);
		
		Unlock();
	}break;
	case MSG_SUB_MAILBOX_OPEN_LETTER:
	{
		ResponseClient::MailBoxOpenLetter* packet = reinterpret_cast<ResponseClient::MailBoxOpenLetter*>(istr->nm_pubMessage);
		
		size_t size = sizeof(MailLetter) + sizeof(ExpressSystemItemInfo) * packet->letter.itemsCount;
		MailLetter* letter = (MailLetter*)malloc(size);
		memcpy(letter, &packet->letter, size);

		MailBoxMessageTypes page = MailBoxMessageTypes::Received;
		if (packet->letter.isMeLetter)
			page = MailBoxMessageTypes::Sent;
		else if (packet->letter.senderType == MailSenderTypes::System)
			page = MailBoxMessageTypes::SystemMails;

		int32_t pos = getMailPos(page, packet->letter.getIndex());
		if (page != MailBoxMessageTypes::Sent)
		{
			m_mapMails[page][pos]->isRead = true;
			m_UI->MarkAsReaded(page, pos);
		}

		LetterTypes letterUIType = page == MailBoxMessageTypes::Sent
			? LetterTypes::LetterSended
			: LetterTypes::LetterReceived;

		m_letterUI->OpenUI(letterUIType);
		m_letterUI->setData(letter);

		Unlock();
	} break;
	case MSG_SUB_MAILBOX_LETTER_COLLECT:
	{
		ResponseClient::MailBoxCollectLetter* packet = reinterpret_cast<ResponseClient::MailBoxCollectLetter*>(istr->nm_pubMessage);
		
		if (m_UI->IsVisible())
		{
			MailBoxMessageTypes page = MailBoxMessageTypes::Received;
			int32_t pos = getMailPos(page, packet->mailId);
			if (pos == -1)
			{
				page = MailBoxMessageTypes::SystemMails;
				pos = getMailPos(page, packet->mailId);
			}

			m_UI->MarkAsCollected(page, pos);
		}

		if (m_letterUI->IsVisible() && m_letterUI->getOpenMailId() == packet->mailId)
		{
			m_letterUI->collected();
		}

		Unlock();

	} break;
	case MSG_SUB_MAILBOX_SEND_LETTER:
	{
		if (m_letterUI->IsVisible()) m_letterUI->CloseUI();
		SendListReq(MailBoxMessageTypes::Sent);
	} break;
	case MSG_SUB_MAILBOX_ERROR:
	{
		ResponseClient::MailBoxError* packet = reinterpret_cast<ResponseClient::MailBoxError*>(istr->nm_pubMessage);
		showErrorMessage(packet->errorCode);
	} break;
	case MSG_SUB_MAILBOX_UPDATE_STATUS:
	{
		UpdateClient::MailBoxUpdateStatus* packet = reinterpret_cast<UpdateClient::MailBoxUpdateStatus*>(istr->GetBuffer());
		if (packet->gotNewMails > 0)
		{
			UIMGR()->GetRadar()->OnExpressNotice(packet->gotNewMails);
			ChangeMailNpc(MAIL_NPC_STATE_EXIST);

			if (m_UI && m_UI->IsVisible())
			{
				clearMails(MailBoxMessageTypes::Received);
				clearMails(MailBoxMessageTypes::SystemMails);
				SendListReq(MailBoxMessageTypes::Received);
				SendListReq(MailBoxMessageTypes::SystemMails);
			}
		}
		else
		{
			UIMGR()->GetRadar()->OffExpressNotice();
			ChangeMailNpc(MAIL_NPC_STATE_NONE);
		}
		Unlock();
	} break;
	default:
		Unlock();
		return;
	}
}

void MailBoxManager::SendListReq(MailBoxMessageTypes pageType, int32_t lastMail)
{
	CNetworkMessage nmsg;
	RequestClient::MailBoxList* packet = reinterpret_cast<RequestClient::MailBoxList*>(nmsg.nm_pubMessage);
	packet->type = MSG_MAIL_BOX;
	packet->subType = MSG_SUB_MAILBOX_LIST;
	packet->lastMailId = lastMail;
	packet->pageType = pageType;

	nmsg.setSize(sizeof(*packet));
	_pNetwork->SendToServerNew(nmsg);
}

void MailBoxManager::SendDeleteAllMails(MailBoxMessageTypes pageType)
{
	if (IsLock())
	{
		showErrorMessage(MailBoxErrors::AlreadyUsed);
		return;
	}

	if (m_letterUI->IsVisible()) m_letterUI->CloseUI();

	CNetworkMessage msg;
	RequestClient::MailBoxDeleteAllMails* packet = reinterpret_cast<RequestClient::MailBoxDeleteAllMails*>(msg.nm_pubMessage);
	packet->type = MSG_MAIL_BOX;
	packet->subType = MSG_SUB_MAILBOX_DELETE_ALL;
	packet->pageType = pageType;

	msg.setSize(sizeof(*packet));
	_pNetwork->SendToServerNew(msg);

	Lock();
}

void MailBoxManager::SendDeleteMail(MailBoxMessageTypes pageType, int32_t mailPos)
{
	SendDeleteMailById(pageType, getMailId(pageType, mailPos));
}

void MailBoxManager::SendDeleteMailById(MailBoxMessageTypes pageType, int32_t mailId)
{
	if (IsLock())
	{
		showErrorMessage(MailBoxErrors::AlreadyUsed);
		return;
	}

	CNetworkMessage msg;
	RequestClient::MailBoxDeleteMail* packet = reinterpret_cast<RequestClient::MailBoxDeleteMail*>(msg.nm_pubMessage);
	packet->type = MSG_MAIL_BOX;
	packet->subType = MSG_SUB_MAILBOX_DELETE;
	packet->mailId = mailId;
	packet->pageType = pageType;

	msg.setSize(sizeof(*packet));
	_pNetwork->SendToServerNew(msg);

	Lock();
}

void MailBoxManager::SendOpenMail(MailBoxMessageTypes pageType, int32_t mailPos)
{
	if (IsLock())
	{
		showErrorMessage(MailBoxErrors::AlreadyUsed);
		return;
	}

	CNetworkMessage msg;
	RequestClient::MailBoxOpenLetter* packet = reinterpret_cast<RequestClient::MailBoxOpenLetter*>(msg.nm_pubMessage);
	packet->type = MSG_MAIL_BOX;
	packet->subType = MSG_SUB_MAILBOX_OPEN_LETTER;
	packet->mailId = getMailId(pageType, mailPos);
	packet->pageType = pageType;

	msg.setSize(sizeof(*packet));
	_pNetwork->SendToServerNew(msg);

	Lock();
}

void MailBoxManager::SendFindUser(CTString nickname)
{
	if (IsLock())
	{
		showErrorMessage(MailBoxErrors::AlreadyUsed);
		return;
	}

	if (_pNetwork->MyCharacterInfo.name == nickname)
	{
		showErrorMessage(MailBoxErrors::CantSendYourself);
		return;
	}

	CNetworkMessage msg;
	RequestClient::MailBoxFindUser* packet = reinterpret_cast<RequestClient::MailBoxFindUser*>(msg.nm_pubMessage);
	packet->type = MSG_MAIL_BOX;
	packet->subType = MSG_SUB_MAILBOX_FIND_USER;
	strcpy(packet->nickname, nickname.str_String);

	msg.setSize(sizeof(*packet));
	_pNetwork->SendToServerNew(msg);

	Lock();
}

void MailBoxManager::SendCollectMessage(int32_t mailId)
{
	if (IsLock())
	{
		showErrorMessage(MailBoxErrors::AlreadyUsed);
		return;
	}

	CNetworkMessage msg;
	RequestClient::MailBoxCollectLetter* packet = reinterpret_cast<RequestClient::MailBoxCollectLetter*>(msg.nm_pubMessage);
	packet->type = MSG_MAIL_BOX;
	packet->subType = MSG_SUB_MAILBOX_LETTER_COLLECT;
	packet->mailId = mailId;

	msg.setSize(sizeof(*packet));
	_pNetwork->SendToServerNew(msg);

	Lock();
}

void MailBoxManager::SendLetter(SendingMailLetter& letter)
{
	if (IsLock())
	{
		showErrorMessage(MailBoxErrors::AlreadyUsed);
		return;
	}

	if (_pNetwork->MyCharacterInfo.name == CTString(letter.targetUser))
	{
		showErrorMessage(MailBoxErrors::CantSendYourself);
		return;
	}

	if (letter.nas > _pNetwork->MyCharacterInfo.money)
	{
		showErrorMessage(MailBoxErrors::CantSendYourself);
		return;
	}

	CNetworkMessage msg;
	RequestClient::MailBoxSendLetter* packet = reinterpret_cast<RequestClient::MailBoxSendLetter*>(msg.nm_pubMessage);
	packet->type = MSG_MAIL_BOX;
	packet->subType = MSG_SUB_MAILBOX_SEND_LETTER;
	packet->letter = letter;

	for (int i = 0; i < packet->letter.itemCount; i++)
	{
		packet->letter.list[i].tab = letter.list[i].tab;
		packet->letter.list[i].invenIndex = letter.list[i].invenIndex;
		packet->letter.list[i].virtualIndex = letter.list[i].virtualIndex;
		packet->letter.list[i].count = letter.list[i].count;
	}

	msg.setSize(sizeof(*packet) + sizeof(packet->letter.list[0]) * packet->letter.itemCount);
	_pNetwork->SendToServerNew(msg);

	Lock();
}

MailCardInfo* MailBoxManager::getMailAt(MailBoxMessageTypes pageType, size_t pos) const
{
	auto iter = m_mapMails.find(pageType);
	if (iter == m_mapMails.end())
		return nullptr;
	return (*iter).second.at(pos);
}

bool MailBoxManager::IsMessageOpen()
{
	int messageBoxes[3] = { MSGCMD_MAILBOX_ERROR, MSGCMD_MAILBOX_DELETE, MSGCMD_MAILBOX_DELETE_ALL };
	for (int i = 0; i < 3; i++) {
		if (UIMGR()->DoesMessageBoxExist(messageBoxes[i]))
			return true;
	}
	return false;
}

void MailBoxManager::showErrorMessage(MailBoxErrors errorType)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	int messageBoxes[3] = { MSGCMD_MAILBOX_ERROR, MSGCMD_MAILBOX_DELETE, MSGCMD_MAILBOX_DELETE_ALL };
	for (int i = 0; i < 3; i++) {
		if (pUIManager->DoesMessageBoxExist(messageBoxes[i]))
			pUIManager->CloseMessageBox(messageBoxes[i]);
	}

	CTString strMessage, strTitle;
	CUIMsgBox_Info msgBoxInfo;
//A.Kennedy 1/4/2021
	strTitle.PrintF(_S(191, "Error"));

	switch (errorType)
	{
	case MailBoxErrors::AlreadyUsed:
		strMessage.PrintF(_S(8436,"Already used"));
	break;
	case MailBoxErrors::InvalidNickFormat:
		strMessage.PrintF(_S(8437,"Invalid nickname"));
		break;
	case MailBoxErrors::InvalidPageType:
		strMessage.PrintF(_S(8438,"Invalid page type"));
		break;
	case MailBoxErrors::ServiceNotWork:
		strMessage.PrintF(_S(8439,"Service offline"));
		break;
	case MailBoxErrors::IncorrectItem:
		strMessage.PrintF(_S(8440,"Incorrect item"));
		break;
	case MailBoxErrors::CantSendYourself:
		strMessage.PrintF(_S(8441,"Cant send yourself"));
		break;
	case MailBoxErrors::FullInventory:
		strMessage.PrintF(_S(8442,"Full inventory"));
		break;
	case MailBoxErrors::DbError:
		strMessage.PrintF(_S(8443,"Db error"));
		break;
	case MailBoxErrors::LetterNotFound:
		strMessage.PrintF(_S(8444,"Letter not found"));
		break;
	case MailBoxErrors::MailBoxLocked:
		strMessage.PrintF(_S(8445,"Mail blocked"));
		break;
	case MailBoxErrors::UnknownError:
		strMessage.PrintF(_S(8446,"Unk error"));
		break;
	case MailBoxErrors::NotFoundUser:
		strMessage.PrintF(_S(8447,"Select correct user"));
		break;
	case MailBoxErrors::SubjectInvalidLenght:
		strMessage.PrintF(_S(8448,"Subject must have minimal 4 characters"));
		break;
	default:
		return;
	}

	msgBoxInfo.AddString(strMessage);
	msgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_OK, UI_NONE, MSGCMD_MAILBOX_ERROR);

	if (pUIManager)
		pUIManager->CreateMessageBox(msgBoxInfo);

	Unlock();
}

int32_t MailBoxManager::getMailId(MailBoxMessageTypes pageType, int32_t mailPos)
{
	try
	{
		return m_mapMails[pageType].at(mailPos)->index;
	}
	catch (std::out_of_range)
	{
		return -1;
	}
}

int32_t MailBoxManager::getMailPos(MailBoxMessageTypes pageType, int32_t mailId)
{
	std::vector<MailCardInfo*>& vec = m_mapMails[pageType];
	std::vector<MailCardInfo*>::iterator elem_iter = std::find_if(vec.begin(), vec.end(),
		MailSelector(mailId));

	int32_t pos = std::distance(vec.begin(), elem_iter);
	return pos >= vec.size() ? -1 : pos;
}

void MailBoxManager::deleteMail(MailBoxMessageTypes pageType, int32_t mailId)
{
	std::vector<MailCardInfo*>& vec = m_mapMails[pageType];
	int32_t pos = getMailPos(pageType, mailId);

	MailCardInfo* pMail = vec.at(pos);
	SAFE_DELETE(pMail);

	vec.erase(vec.begin() + pos);

	if (m_UI->IsVisible())
	{
		m_UI->UpdateUI(); // maybe need optimaze
		m_UI->SelectLastMail();
	}

	if (m_letterUI && m_letterUI->IsVisible() && m_letterUI->getOpenMailId() == mailId)
	{
		m_letterUI->CloseUI();
	}
}

void MailBoxManager::deleteAllMails(MailBoxMessageTypes pageType)
{
	std::vector<MailCardInfo*>& vec = m_mapMails[pageType];
	std::vector<MailCardInfo*>::iterator vec_iter = vec.begin();
	for (; vec_iter != vec.end(); vec_iter++)
	{
		SAFE_DELETE(*vec_iter);
	}

	vec.clear();

	if (m_UI->IsVisible())
	{
		m_UI->UpdateUI(); // maybe need optimaze
	}

	if (m_letterUI && m_letterUI->IsVisible() && m_letterUI->getOpenMailId() > 0)
	{
		m_letterUI->CloseUI();
	}
}

void MailBoxManager::ChangeMailNpc(eMAIL_NPC_STATE eNpcState)
{
	CTString strBaseEffectName = CTString("cube_mail");
	CTString strChageEffectName = CTString("cube_mail2");

	switch (eNpcState)
	{
	case MAIL_NPC_STATE_NONE:
	{
		ACTORMGR()->ChangeEffect(eOBJ_MOB, NPC_INDEX, strChageEffectName.str_String, strBaseEffectName.str_String);
	}
	break;

	case MAIL_NPC_STATE_EXIST:
	{
		ACTORMGR()->ChangeEffect(eOBJ_MOB, NPC_INDEX, strBaseEffectName.str_String, strChageEffectName.str_String);
	}
	break;

	//case MAIL_NPC_STATE_APPEAR:
	//{
	//	if (m_nNoticeFlag > 0)
	//	{
	//		ACTORMGR()->ChangeEffect(eOBJ_MOB, NPC_INDEX, strBaseEffectName.str_String, strChageEffectName.str_String);
	//	}
	//}
	//break;
	}
}
