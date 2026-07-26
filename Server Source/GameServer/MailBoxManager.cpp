#include "stdhdrs.h"

#include "Server.h"
#include "MailBoxManager.h"

void makeMailItemInfo(ExpressSystemItemInfo* itemInfo, CItem* pItem, int itemCount);

void MailBoxManager::SendSystemMail(const SendingSystemMailInfo& mailInfo)
{
	if (mailInfo.Receiver == NULL)
		return;
	
	if (mailInfo.Subject.size() >= MAX_SUBJECT_LENGTH
		|| mailInfo.Message.size() >= MAX_MESSAGE_LENGTH)
		return;

	if (mailInfo.Nas < 0)
		return;

	CNetMsg::SP rmsg(new CNetMsg);
	RequestClient::MailBoxSendGS* packet = reinterpret_cast<RequestClient::MailBoxSendGS*>(rmsg->m_buf);
	packet->type = MSG_MAIL_BOX;
	packet->subType = MSG_SUB_MAILBOX_SEND_LETTER;
	packet->charIndex = -1;
	packet->targetCharIndex = mailInfo.Receiver->m_index;
	packet->senderType = System;
	packet->nas = mailInfo.Nas;

	int itemsCount = 0;
	for (int i = 0; i < LETTER_MAX_ITEMS; i++)
	{
		CItem* pItem = mailInfo.Items[i];
		if (!pItem) continue;

		makeMailItemInfo(&packet->list[itemsCount++], pItem, pItem->Count());
	}

	packet->itemCount = itemsCount;

	strcpy(packet->subject, mailInfo.Subject.c_str());
	strcpy(packet->message, mailInfo.Message.c_str());

	rmsg->setSize(sizeof(*packet) + sizeof(packet->list[0]) * packet->itemCount);
	SEND_Q(rmsg, gserver->m_subHelper);
}

void makeMailItemInfo(ExpressSystemItemInfo* itemInfo, CItem* pItem, int itemCount)
{
	itemInfo->index = 0;
	itemInfo->item_index = pItem->getDBIndex();
	itemInfo->plus = pItem->getPlus();
	itemInfo->plus2 = pItem->getPlus_2();
	itemInfo->flag = pItem->getFlag();
	if (pItem->m_serial.empty())
	{
		itemInfo->serial[0] = '\0';
	}
	else
	{
		std::strncpy(itemInfo->serial, pItem->m_serial.c_str(), sizeof(itemInfo->serial) - 1);
		itemInfo->serial[sizeof(itemInfo->serial) - 1] = '\0';

	}

	itemInfo->item_count = itemCount;
	if (itemCount < 0)
		itemCount = 1;
	itemInfo->option_count = pItem->m_nOption;

	if (pItem->IsOriginItem())
	{
		for (int i = 0; i < MAX_ORIGIN_OPTION; ++i)
		{
			itemInfo->item_origin[i] = pItem->getOriginVar(i);
		}
	}
	else
	{
		itemInfo->option_count = pItem->m_nOption;

		for (int i = 0; i < MAX_ITEM_OPTION; ++i)
		{
			itemInfo->option_type[i] = pItem->m_option[i].m_type;
			itemInfo->option_level[i] = pItem->m_option[i].m_level;
		}
	}

	for (int i = 0; i < MAX_SOCKET_COUNT; ++i)
	{
		itemInfo->socket[i] = pItem->m_socketList.GetJewelAt(i);
	}

	itemInfo->nas = 0;

#ifdef DURABILITY
	itemInfo->now_durability = pItem->getNowDurability();
	itemInfo->max_durability = pItem->getMaxDurability();
#endif
}
