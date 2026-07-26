#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "CmdMsg.h"
#include "DBManager.h"
#include "Server.h"
#include "WarCastle.h"
#include "../ShareLib/packetType/ptype_mail_box.h"

bool isCorrectData(CPC* ch, MailBoxMessageTypes pageType, int mailId);
bool isCorrectTargetUser(CPC* pc, std::string nick, int* targetCharIndex);
void makeSystemItemInfo(ExpressSystemItemInfo* itemInfo, CItem* pItem, int itemCount);

void do_mailBoxSystemList(CPC* ch, CNetMsg::SP& msg);
void do_mailBoxSystemFindUser(CPC* ch, CNetMsg::SP& msg);

void do_mailBoxSystemDelete(CPC* ch, CNetMsg::SP& msg);
void do_mailBoxSystemDeleteAll(CPC* ch, CNetMsg::SP& msg);
void do_mailBoxSystemOpenLetter(CPC* ch, CNetMsg::SP& msg);

void do_mailBoxSystemCollect(CPC* ch, CNetMsg::SP& msg);
void do_mailBoxSystemSendLetter(CPC* ch, CNetMsg::SP& msg);

void do_mailBoxSystem(CPC* ch, CNetMsg::SP& msg)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(msg->m_buf);
	if (DEAD(ch) || ch->m_exchange || ch->m_personalshop || ch->m_currentSkill)
		return;

	if (!gserver->isRunSubHelper())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMailBoxErrorMessage(rmsg, ServiceNotWork);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	switch (pBase->subType)
	{
	case MSG_SUB_MAILBOX_LIST:
		do_mailBoxSystemList(ch, msg);
		break;
	case MSG_SUB_MAILBOX_FIND_USER:
		do_mailBoxSystemFindUser(ch, msg);
		break;
	case MSG_SUB_MAILBOX_DELETE:
		do_mailBoxSystemDelete(ch, msg);
		break;
	case MSG_SUB_MAILBOX_DELETE_ALL:
		do_mailBoxSystemDeleteAll(ch, msg);
		break;
	case MSG_SUB_MAILBOX_OPEN_LETTER:
		do_mailBoxSystemOpenLetter(ch, msg);
		break;
	case MSG_SUB_MAILBOX_LETTER_COLLECT:
		do_mailBoxSystemCollect(ch, msg);
		break;
	case MSG_SUB_MAILBOX_SEND_LETTER:
		do_mailBoxSystemSendLetter(ch, msg);
		break;
	default:
		{
			LOG_INFO("Mailbox : invalid packet. userId[%d] charId[%d] subType[%d]",
				ch->m_desc->m_index, ch->m_index, pBase->subType);
			ch->m_desc->Close("Mailbox : invalid packet.");
			return;
		}
	}
}

bool isCorrectData(CPC* ch, MailBoxMessageTypes pageType, int mailId)
{
	if (pageType < Received ||
		pageType > SystemMails)
	{
		LOG_INFO("Mail - Invalid pageType");
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMailBoxErrorMessage(rmsg, InvalidPageType);
		SEND_Q(rmsg, ch->m_desc);
		return false;
	}

	return true;
}

void do_mailBoxSystemList(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::MailBoxList* packet = reinterpret_cast<RequestClient::MailBoxList*>(msg->m_buf);
	
	if (!isCorrectData(ch, packet->pageType, packet->lastMailId))
		return;

	RequestClient::MailBoxListGS* rpacket = reinterpret_cast<RequestClient::MailBoxListGS*>(msg->m_buf);
	rpacket->charIndex = ch->m_index;
	rpacket->userIndex = ch->m_desc->m_index;
	msg->setSize(sizeof(*rpacket));
	SEND_Q(msg, gserver->m_subHelper);
}

void do_mailBoxSystemFindUser(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::MailBoxFindUser* packet = reinterpret_cast<RequestClient::MailBoxFindUser*>(msg->m_buf);

	packet->nickname[EXPRESS_SENDER_NAME-1] = '\0';
	if (strlen(packet->nickname) < 4)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMailBoxErrorMessage(rmsg, InvalidNickFormat);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if (strinc(packet->nickname, "'") || strinc(packet->nickname, "\"") || findPercentChar(packet->nickname))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMailBoxErrorMessage(rmsg, InvalidNickFormat);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	DBManager::instance()->PushExpressSearchNickName(ch->m_desc, packet->nickname);
}

void do_mailBoxSystemDelete(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::MailBoxDeleteMail* packet = reinterpret_cast<RequestClient::MailBoxDeleteMail*>(msg->m_buf);
	
	if (!isCorrectData(ch, packet->pageType, packet->mailId))
		return;

	RequestClient::MailBoxDeleteMailGS* rpacket = reinterpret_cast<RequestClient::MailBoxDeleteMailGS*>(msg->m_buf);
	rpacket->charIndex = ch->m_index;
	rpacket->userIndex = ch->m_desc->m_index;
	msg->setSize(sizeof(*rpacket));
	SEND_Q(msg, gserver->m_subHelper);
}

void do_mailBoxSystemDeleteAll(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::MailBoxDeleteAllMails* packet = reinterpret_cast<RequestClient::MailBoxDeleteAllMails*>(msg->m_buf);

	LOG_INFO("do_mailBoxSystemDeleteAll - packet %d", packet->subType);

	if (!isCorrectData(ch, packet->pageType, 1))
		return;

	RequestClient::MailBoxDeleteAllMailsGS* rpacket = reinterpret_cast<RequestClient::MailBoxDeleteAllMailsGS*>(msg->m_buf);
	rpacket->charIndex = ch->m_index;
	rpacket->userIndex = ch->m_desc->m_index;
	msg->setSize(sizeof(*rpacket));
	SEND_Q(msg, gserver->m_subHelper);

	LOG_INFO("do_mailBoxSystemDeleteAll - rpacket %d", rpacket->subType);
}

void do_mailBoxSystemOpenLetter(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::MailBoxOpenLetter* packet = reinterpret_cast<RequestClient::MailBoxOpenLetter*>(msg->m_buf);
	
	if (!isCorrectData(ch, packet->pageType, packet->mailId))
		return;

	RequestClient::MailBoxOpenLetterGS* rpacket = reinterpret_cast<RequestClient::MailBoxOpenLetterGS*>(msg->m_buf);
	rpacket->charIndex = ch->m_index;
	rpacket->userIndex = ch->m_desc->m_index;
	msg->setSize(sizeof(*rpacket));
	SEND_Q(msg, gserver->m_subHelper);
}

void do_mailBoxSystemCollect(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::MailBoxCollectLetter* packet = reinterpret_cast<RequestClient::MailBoxCollectLetter*>(msg->m_buf);

	if (packet->mailId <= 0)
	{
		LOG_INFO("HACKING? invalid mail id. user_id[%d] char_id[%d]", ch->m_desc->m_index, ch->m_index);
		ch->m_desc->Close("invalid mail id");
		return;
	}

	RequestClient::MailBoxCollectLetterGS* rpacket = reinterpret_cast<RequestClient::MailBoxCollectLetterGS*>(msg->m_buf);
	rpacket->charIndex = ch->m_index;
	msg->setSize(sizeof(*rpacket));
	SEND_Q(msg, gserver->m_subHelper);
}

void do_mailBoxSystemSendLetter(CPC* ch, CNetMsg::SP& msg)
{
	CNetMsg::SP rmsg(new CNetMsg);
	RequestClient::MailBoxSendLetter* packet = reinterpret_cast<RequestClient::MailBoxSendLetter*>(msg->m_buf);

	int targetCharIndex = 0;
	if (!isCorrectTargetUser(ch, packet->letter.targetUser, &targetCharIndex))
	{
		ResponseClient::MailBoxError* rpacket = reinterpret_cast<ResponseClient::MailBoxError*>(rmsg->m_buf);
		rpacket->type = MSG_MAIL_BOX;
		rpacket->subType = MSG_SUB_MAILBOX_ERROR;
		rpacket->errorCode = InvalidNickFormat;
		rmsg->setSize(sizeof(*rpacket));
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if(strlen(packet->letter.subject) >= MAX_SUBJECT_LENGTH ||
		strlen(packet->letter.message) >= MAX_MESSAGE_LENGTH)
	{
		LOG_ERROR("HACKING? : very big text. char_id[%d]", ch->m_index);
		ch->m_desc->Close("very big text");
		return;
	}

	if (packet->letter.itemCount < 0 || packet->letter.itemCount > LETTER_MAX_ITEMS)
	{
		LOG_ERROR("HACKING? : Invalid item count. char_id[%d] item_count[%d]", ch->m_index,
			packet->letter.itemCount);
		ch->m_desc->Close("Invalid item count");
		return;
	}

	std::set<int> checkdup;
	int key = 0;

	// Validate NAS BEFORE removing any items from inventory
	if (packet->letter.nas < 0 || packet->letter.nas > ch->m_inventory.getMoney())
	{
		LOG_ERROR("HACKING? : invalid nas. char_id[%d]", ch->m_index);
		ch->m_desc->Close("invalid nas");
		return;
	}

	ExpressSystemItemInfo* items = new ExpressSystemItemInfo[packet->letter.itemCount];
	for (int i = 0; i < packet->letter.itemCount; i++)
	{
		unsigned short tab = packet->letter.list[i].tab;
		unsigned short invenIndex = packet->letter.list[i].invenIndex;
		int virtualIndex = packet->letter.list[i].virtualIndex;
		unsigned int count = packet->letter.list[i].count;

		key = makeCheckDupKey(tab, invenIndex);
		if (checkdup.insert(key).second == false)
		{
			LOG_ERROR("HACKING? : Dupe item detected. char_id[%d]", ch->m_index);
			ch->m_desc->Close("Dupe item detected");
			return;
		}
	
		if (ch->m_inventory.isValidNormalInventory(tab, invenIndex) == false)
		{
			LOG_ERROR("HACKING? : invalid packet. char_id[%d] tab[%d] invenIndex[%d]",
				ch->m_index, tab, invenIndex);
			ch->m_desc->Close("invalid packet");
			return;
		}

		if (ch->m_inventory.isUsable(tab) == false)
		{
			LOG_ERROR("HACKING? : not usable inventory. char_id[%d] tab[%d] invenIndex[%d]",
				ch->m_index, tab, invenIndex);
			ch->m_desc->Close("not usable inventory");
			return;
		}

		CItem* item = ch->m_inventory.getItem(tab, invenIndex);
		if (item == NULL)
		{
			LOG_ERROR("HACKING? : not found item. char_id[%d] tab[%d] invenIndex[%d]", ch->m_index,
				tab, invenIndex);
			ch->m_desc->Close("not found item");
			return;
		}

		if (item->getVIndex() != virtualIndex)
		{
			LOG_ERROR("HACKING? : invalid virtual index. char_id[%d]", ch->m_index);
			ch->m_desc->Close("invalid virtual index");
			return;
		}

		if (count <= 0 || count > item->Count())
		{
			LOG_ERROR("HACKING? : invalid item count. char_id[%d] count[%d]", 
				ch->m_index, count);
			ch->m_desc->Close("invalid item count");
			return;
		}

		if (item->IsUsedPlatinumSpecial())
		{
			LOG_ERROR("HACKING? : item used platinumSpecial. char_id[%d] tab[%d] invenIndex[%d]",
				ch->m_index, tab, invenIndex);
			ch->m_desc->Close("item used platinumSpecial");
			return;
		}

		if (item->IsBelong() == true)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_BELONG_ITEM);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}

		if (item->getWearPos() != WEARING_NONE)
		{
			LOG_ERROR("HACKING? : this item is wear item. char_id[%d] tab[%d] invenIndex[%d]",
				ch->m_index, tab, invenIndex);
			ch->m_desc->Close("this item is wear item");
			return;
		}

		if ((item->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) && (item->getFlag() & FLAG_ITEM_COMPOSITION))
		{
			LOG_ERROR("HACKING? : this item is composite item. char_id[%d] tab[%d] invenIndex[%d]",
				ch->m_index, tab, invenIndex);
			ch->m_desc->Close("this item is composite item");
			return;
		}

		if (item->m_itemProto->isMonsterCard())
		{
			LOG_ERROR("HACKING? : this item is monster card. char_id[%d] tab[%d] invenIndex[%d]",
				ch->m_index, tab, invenIndex);
			ch->m_desc->Close("this item is monster card");
			return;
		}

		if ((item->m_itemProto->getItemFlag() & ITEM_FLAG_EXCHANGE) == 0)
		{
			LOG_ERROR("HACKING? : not exchange item. char_id[%d] itemDBIndex[%d]",
				ch->m_index, item->getDBIndex());
			ch->m_desc->Close("not exchange item");
			return;
		}

		if (item->getFlag() & FLAG_ITEM_LENT)
		{
			LOG_ERROR("HACKING? : is rent item. char_index[%d] itemDBIndex[%d]",
				ch->m_index, item->getDBIndex());
			ch->m_desc->Close("is rent item");
			return;
		}

		if (item->IsPet() || item->IsAPet())
		{
			LOG_ERROR("HACKING? : item is pet. char_id[%d] itemDBIndex[%d]",
				ch->m_index, item->getDBIndex());
			ch->m_desc->Close("item is apet");
			return;
		}

		if (item->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && item->m_itemProto->getItemSubTypeIdx() == IACCESSORY_ARTIFACT)
		{
			LOG_ERROR("HACKING? : item is artifactitem. char_id[%d] itemDBIndex[%d]",
				ch->m_index, item->getDBIndex());
			ch->m_desc->Close("item is artifact");
			return;
		}

		if (count == item->Count())
		{
			ch->m_inventory.eraseNotFree(item);
		}
		else
		{
			ch->m_inventory.decreaseItemCount(item, count);
		}

		makeSystemItemInfo(&items[i], item, count);
	}

	if (packet->letter.nas > 0)
	{ 
		ch->m_inventory.decreaseMoney(packet->letter.nas);
	}

	{
		RequestClient::MailBoxSendGS* rpacket = reinterpret_cast<RequestClient::MailBoxSendGS*>(rmsg->m_buf);
		rpacket->type = MSG_MAIL_BOX;
		rpacket->subType = MSG_SUB_MAILBOX_SEND_LETTER;
		rpacket->charIndex = ch->m_index;
		rpacket->targetCharIndex = targetCharIndex;
		rpacket->senderType = User;
		rpacket->nas = packet->letter.nas;
		rpacket->itemCount = packet->letter.itemCount;

		strcpy(rpacket->subject, packet->letter.subject);
		strcpy(rpacket->message, packet->letter.message);
		memcpy(&rpacket->list[0], items, sizeof(ExpressSystemItemInfo)* packet->letter.itemCount);

		rmsg->setSize(sizeof(*rpacket) + sizeof(rpacket->list[0]) * rpacket->itemCount);
		SEND_Q(rmsg, gserver->m_subHelper);
	}

	delete[] items;
}

bool isCorrectTargetUser(CPC* pc, std::string nick, int* targetCharIndex)
{
	char tnickName[EXPRESS_SENDER_NAME * 2];
	memset(tnickName, 0, sizeof(char) * EXPRESS_SENDER_NAME * 2);
	mysql_real_escape_string(&gserver->m_dbchar, tnickName, nick.c_str(), nick.length());

	std::string sql = boost::str(boost::format("SELECT a_index FROM t_characters WHERE a_nick = '%s' LIMIT 1") 
		% tnickName);
	
	CDBCmd db;
	db.Init(&gserver->m_dbchar);
	db.SetQuery(sql);

	if (!db.Open() || !db.MoveFirst())
	{
		return false;
	}

	int charIndex;
	db.GetRec("a_index", charIndex);

	CPC* ch = PCManager::instance()->getPlayerByCharIndex(charIndex);
	if (ch == NULL)
	{
		sql = boost::str(boost::format(
			"select * from t_block_friend where a_char_idx = %d ") % charIndex);
		db.SetQuery(sql);

		if (!db.Open() || !db.MoveFirst())
		{
			return false;
		}

		CLCString blockIndexList(255 + 1);
		CLCString blockNameList(255 + 1);

		db.GetRec("a_block_idx_list", blockIndexList);
		db.GetRec("a_block_name_list", blockNameList);

		const char* pblockIndex = (const char*)blockIndexList;
		const char* pblockName = (const char*)blockNameList;

		int blockIndex = -1;
		char m_buf[256];
		while (*pblockIndex && *pblockName)
		{
			pblockIndex = AnyOneArg(pblockIndex, m_buf);
			blockIndex = atoi(m_buf);
			m_buf[0] = '\0';
			pblockName = AnyOneArg(pblockName, m_buf);

			if (blockIndex == pc->m_index)
				return false;

			m_buf[0] = '\0';
		}

		*targetCharIndex = charIndex;
		return true;
	}
	else
	{
		if (ch->IsBlockPC(pc->m_index, nick.c_str()))
		{
			return false;
		}
		else
		{
			*targetCharIndex = ch->m_index;
			return true;
		}
	}
}

void makeSystemItemInfo(ExpressSystemItemInfo* itemInfo, CItem* pItem, int itemCount)
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
		strncpy(itemInfo->serial, pItem->m_serial.c_str(), sizeof(itemInfo->serial));
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
