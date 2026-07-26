#include <boost/format.hpp>
#include "stdhdrs.h"

#include "Server.h"
#include "doFunc.h"
#include "CmdMsg.h"
#include "../ShareLib/DBCmd.h"
#include "Log.h"
#include "../ShareLib/packetType/ptype_mail_box.h"

int getCharIndex(CNetMsg::SP& msg);
void getItemByExpress(ExpressSystemItemInfo* info, CDBCmd& db, MYSQL_ROW& row);

void do_MailBoxList(CNetMsg::SP& msg, CDescriptor* dest);
void do_MailBoxDelete(CNetMsg::SP& msg, CDescriptor* dest);
void do_MailBoxCollect(CNetMsg::SP& msg, CDescriptor* dest);
void do_MailBoxCollectRollback(CNetMsg::SP& msg, CDescriptor* dest);
void do_MailBoxDeleteAll(CNetMsg::SP& msg, CDescriptor* dest);
void do_MailBoxOpenLetter(CNetMsg::SP& msg, CDescriptor* dest);
void do_MailBoxSendLetter(CNetMsg::SP& msg, CDescriptor* dest);
void do_MailBoxCheckNewLetter(CNetMsg::SP& msg, CDescriptor* dest);

void do_MailBox(CNetMsg::SP& msg, CDescriptor* dest)
{
	pTypeBase* packet = reinterpret_cast<pTypeBase*>(msg->m_buf);
	int charId = getCharIndex(msg);

	if (packet->subType != MSG_SUB_MAILBOX_LIST)
	{
		if (gserver.m_mailBoxLocker.IsLock(charId))
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::MailBoxErrorGS* rpacket = reinterpret_cast<ResponseClient::MailBoxErrorGS*>(rmsg->m_buf);
			rpacket->type = MSG_MAIL_BOX;
			rpacket->subType = MSG_SUB_MAILBOX_ERROR;
			rpacket->errorCode = MailBoxLocked;
			rpacket->charIndex = charId;
			rmsg->setSize(sizeof(*rpacket));
			SEND_Q(rmsg, dest);
			return;
		}

		gserver.m_mailBoxLocker.Lock(charId);
	}

	switch (packet->subType)
	{
	case MSG_SUB_MAILBOX_LIST:
		do_MailBoxList(msg, dest);
		break;
	case MSG_SUB_MAILBOX_DELETE:
		do_MailBoxDelete(msg, dest);
		break;
	case MSG_SUB_MAILBOX_DELETE_ALL:
		do_MailBoxDeleteAll(msg, dest);
		break;
	case MSG_SUB_MAILBOX_OPEN_LETTER:
		do_MailBoxOpenLetter(msg, dest);
		break;
	case MSG_SUB_MAILBOX_LETTER_COLLECT:
		do_MailBoxCollect(msg, dest);
		break;
	case MSG_SUB_MAILBOX_LETTER_COLLECT_ROLLBACK:
		do_MailBoxCollectRollback(msg, dest);
		break;
	case MSG_SUB_MAILBOX_SEND_LETTER:
		do_MailBoxSendLetter(msg, dest);
		break;
	case MSG_SUB_MAILBOX_UPDATE_STATUS:
		do_MailBoxCheckNewLetter(msg, dest);
		break;
	}

	if (packet->subType != MSG_SUB_MAILBOX_LIST)
	{
		gserver.m_mailBoxLocker.Unlock(charId);
	}
}

void do_MailBoxList(CNetMsg::SP& msg, CDescriptor* dest)
{
	CNetMsg::SP rmsg(new CNetMsg);

	RequestClient::MailBoxListGS* packet = reinterpret_cast<RequestClient::MailBoxListGS*>(msg->m_buf);
	ResponseClient::MailBoxListGS* rpacket = reinterpret_cast<ResponseClient::MailBoxListGS*>(rmsg->m_buf);
	rpacket->listCount = 0;

	std::string sql;
	CDBCmd db;

	int i = 0;
	int isRead = 0, haveAttachment = 0;
	int senderType = 0;
	LONGLONG timestamp = 0;
	CLCString subject(MAX_SUBJECT_LENGTH);
	CLCString user(16);
	
	db.Init(&gserver.m_dbchar);

	switch (packet->pageType)
	{
	case Sent:
		sql = boost::str(boost::format("SELECT mailbox.a_index, mailbox.a_sender_idx, mailbox.a_sender_type, mailbox.a_receiver_idx, chTarget.a_index as char_index, chTarget.a_nick, "
			"mailbox.a_subject, UNIX_TIMESTAMP(mailbox.a_date) as a_date, mailbox.a_readed, mailbox.a_collected FROM t_mailbox mailbox "
			"INNER JOIN t_characters ch ON ch.a_index = mailbox.a_sender_idx "
			"INNER JOIN t_characters chTarget ON chTarget.a_index = mailbox.a_receiver_idx WHERE ch.a_user_index = %d AND mailbox.a_sender_idx = %d AND mailbox.a_enable_sender <> 0 ORDER BY mailbox.a_index DESC LIMIT 50") % packet->userIndex % packet->charIndex);
		break;
	case Received:
		sql = boost::str(boost::format("SELECT mailbox.a_index, mailbox.a_sender_idx, mailbox.a_sender_type, mailbox.a_receiver_idx, chTarget.a_index as char_index, chTarget.a_nick, mailbox.a_subject, "
			"UNIX_TIMESTAMP(mailbox.a_date) as a_date, mailbox.a_readed, mailbox.a_collected FROM t_mailbox mailbox "
			"INNER JOIN t_characters ch ON ch.a_index = mailbox.a_receiver_idx "
			"INNER JOIN t_characters chTarget ON chTarget.a_index = mailbox.a_sender_idx WHERE ch.a_user_index = %d AND mailbox.a_receiver_idx = %d AND a_sender_type = %d AND mailbox.a_enable_receiver <> 0 ORDER BY mailbox.a_index DESC LIMIT 50") 
			% packet->userIndex % packet->charIndex % (int)User);
	break;
	case SystemMails:
		sql = boost::str(boost::format("SELECT mailbox.a_index, mailbox.a_sender_idx, mailbox.a_sender_type, mailbox.a_receiver_idx, -1 as char_index, 'System' as a_nick, mailbox.a_subject, "
			"UNIX_TIMESTAMP(mailbox.a_date) as a_date, mailbox.a_readed, mailbox.a_collected FROM t_mailbox mailbox "
			"INNER JOIN t_characters ch ON ch.a_index = mailbox.a_receiver_idx WHERE ch.a_user_index = %d AND mailbox.a_receiver_idx = %d AND a_sender_type = %d AND mailbox.a_enable_receiver <> 0 ORDER BY mailbox.a_index DESC LIMIT 50")
			% packet->userIndex % packet->charIndex % (int)System);
		break;
	default:
		rpacket->error = UnknownError;
		goto SEND_MESSAGE;
	}

	if (packet->lastMailId > 0)
		sql += boost::str(boost::format(" AND mailbox.a_index > %d") % packet->lastMailId);
	
	db.SetQuery(sql);

	if (!db.Open())
	{
		rpacket->error = DbError;
		goto SEND_MESSAGE;
	}

	while (db.MoveNext())
	{
		db.GetRec("a_index", rpacket->list[i].index);
		db.GetRec("a_sender_type", senderType);
		db.GetRec("char_index", rpacket->list[i].targetIndex);
		db.GetRec("a_nick", user);
		db.GetRec("a_subject", subject);
		db.GetRec("a_date", timestamp);
		db.GetRec("a_collected", haveAttachment);
		if (packet->pageType != Sent)
		{
			db.GetRec("a_readed", isRead);
		}

		rpacket->list[i].recvTime = timestamp;
		rpacket->list[i].senderType = (MailSenderTypes)senderType;
		rpacket->list[i].isRead = isRead;
		rpacket->list[i].haveAttachment = !haveAttachment;
		rpacket->list[i].pageType = packet->pageType;

		strcpy(rpacket->list[i].targetUser, (const char*)user);
		strcpy(rpacket->list[i].subject, (const char*)subject);
		i++;
	}

	rpacket->error = Ok;
	rpacket->listCount = i;

SEND_MESSAGE:
	rpacket->type = MSG_MAIL_BOX;
	rpacket->subType = MSG_SUB_MAILBOX_LIST_FINISH;
	rpacket->charIndex = packet->charIndex;

	rmsg->setSize(sizeof(*rpacket) + (sizeof(rpacket->list[0]) * rpacket->listCount));
	SEND_Q(rmsg, dest);
}

void do_MailBoxDelete(CNetMsg::SP& msg, CDescriptor* dest)
{
	CNetMsg::SP rmsg(new CNetMsg);

	RequestClient::MailBoxDeleteMailGS* packet = reinterpret_cast<RequestClient::MailBoxDeleteMailGS*>(msg->m_buf);
	ResponseClient::MailBoxDeleteMailGS* rpacket = reinterpret_cast<ResponseClient::MailBoxDeleteMailGS*>(rmsg->m_buf);

	std::string sql;
	switch (packet->pageType)
	{
	case Sent:
		sql = boost::str(boost::format("UPDATE t_mailbox mailbox INNER JOIN t_characters ch ON ch.a_index = mailbox.a_sender_idx "
			"SET mailbox.a_enable_sender = 0 WHERE ch.a_index = %d AND ch.a_user_index = %d AND mailbox.a_index = %d") % packet->charIndex % packet->userIndex % packet->mailId);
		break;
	case Received:
	case SystemMails:
		sql = boost::str(boost::format("UPDATE t_mailbox mailbox INNER JOIN t_characters ch ON ch.a_index = mailbox.a_receiver_idx "
			"SET mailbox.a_enable_receiver = 0 WHERE ch.a_index = %d AND ch.a_user_index = %d AND mailbox.a_index = %d") % packet->charIndex % packet->userIndex % packet->mailId);
		break;
	}
	
	CDBCmd db;
	db.Init(&gserver.m_dbchar);
	db.SetQuery(sql);

	if (!db.Update())
	{
		rpacket->error = DbError;
		goto SEND_MESSAGE;
	}

	if (db.GetRecordCount() == 0)
	{
		rpacket->error = LetterNotFound;
		goto SEND_MESSAGE;
	}

	rpacket->error = Ok;

SEND_MESSAGE:
	rpacket->type = MSG_MAIL_BOX;
	rpacket->subType = MSG_SUB_MAILBOX_DELETE;
	rpacket->charIndex = packet->charIndex;
	rpacket->mailId = packet->mailId;
	rpacket->pageType = packet->pageType;

	rmsg->setSize(sizeof(*rpacket));
	SEND_Q(rmsg, dest);
}

void do_MailBoxDeleteAll(CNetMsg::SP& msg, CDescriptor* dest)
{
	CNetMsg::SP rmsg(new CNetMsg);

	RequestClient::MailBoxDeleteAllMailsGS* packet = reinterpret_cast<RequestClient::MailBoxDeleteAllMailsGS*>(msg->m_buf);
	ResponseClient::MailBoxDeleteAllMailsGS* rpacket = reinterpret_cast<ResponseClient::MailBoxDeleteAllMailsGS*>(rmsg->m_buf);

	std::string sql;
	switch (packet->pageType)
	{
	case Sent:
		sql = boost::str(boost::format("UPDATE t_mailbox mailbox INNER JOIN t_characters ch ON ch.a_index = mailbox.a_sender_idx "
			"SET mailbox.a_enable_sender = 0 WHERE ch.a_index = %d AND ch.a_user_index = %d") % packet->charIndex % packet->userIndex);
		break;
	case Received:
	case SystemMails:
	{
		MailSenderTypes senderType = packet->pageType == Received ? User : System;
		sql = boost::str(boost::format("UPDATE t_mailbox mailbox INNER JOIN t_characters ch ON ch.a_index = mailbox.a_receiver_idx "
			"SET mailbox.a_enable_receiver = 0 WHERE ch.a_index = %d AND ch.a_user_index = %d AND mailbox.a_sender_type = %d") 
			% packet->charIndex % packet->userIndex % (int)senderType);
	} break;
	}

	CDBCmd db;
	db.Init(&gserver.m_dbchar);
	db.SetQuery(sql);

	if (!db.Update())
	{
		rpacket->error = DbError;
		goto SEND_MESSAGE;
	}

	if (db.GetRecordCount() == 0)
	{
		rpacket->error = LetterNotFound;
		goto SEND_MESSAGE;
	}

	rpacket->error = Ok;

SEND_MESSAGE:
	rpacket->type = MSG_MAIL_BOX;
	rpacket->subType = MSG_SUB_MAILBOX_DELETE_ALL;
	rpacket->charIndex = packet->charIndex;
	rpacket->pageType = packet->pageType;

	rmsg->setSize(sizeof(*rpacket));
	SEND_Q(rmsg, dest);
}

// crutch
int getCharIndex(CNetMsg::SP& msg)
{
	pTypeBase* packet = reinterpret_cast<pTypeBase*>(msg->m_buf);

	switch (packet->subType)
	{
	case MSG_SUB_MAILBOX_DELETE:
	{
		RequestClient::MailBoxDeleteMailGS* pPack = reinterpret_cast<RequestClient::MailBoxDeleteMailGS*>(msg->m_buf);
		return pPack->charIndex;
	}break;
	default:
		return -1;
	}
}

void do_MailBoxOpenLetter(CNetMsg::SP& msg, CDescriptor* dest)
{
	CNetMsg::SP rmsg(new CNetMsg);
	RequestClient::MailBoxOpenLetterGS* packet = reinterpret_cast<RequestClient::MailBoxOpenLetterGS*>(msg->m_buf);
	ResponseClient::MailBoxOpenLetterGS* rpacket = reinterpret_cast<ResponseClient::MailBoxOpenLetterGS*>(rmsg->m_buf);

	int i = 0;
	int isRead = 0;
	int isCollected = 0;
	int senderType = 0;
	LONGLONG timestamp = 0;
	CLCString message(MAX_MESSAGE_LENGTH);
	CLCString subject(MAX_SUBJECT_LENGTH);
	CLCString user(16);

	CDBCmd db;
	std::string sql;
	std::string sql_temp = "SELECT mailbox.a_index, mailbox.a_sender_idx, mailbox.a_sender_type, mailbox.a_receiver_idx, "
		"chTarget.a_nick, chTarget.a_job, mailbox.a_subject, mailbox.a_message, mailbox.a_nas, UNIX_TIMESTAMP(mailbox.a_date) as a_date, mailbox.a_readed, "
		"mailbox.a_collected FROM t_mailbox mailbox ";

	switch (packet->pageType)
	{
	case Sent:
		sql = sql_temp + boost::str(boost::format("INNER JOIN t_characters ch ON ch.a_index = mailbox.a_sender_idx "
			"INNER JOIN t_characters chTarget ON chTarget.a_index = mailbox.a_receiver_idx WHERE mailbox.a_index = %d AND mailbox.a_sender_idx = %d AND ch.a_user_index = %d")
			% packet->mailId % packet->charIndex % packet->userIndex);
		break;
	case Received:
		sql = sql_temp + boost::str(boost::format("INNER JOIN t_characters ch ON ch.a_index = mailbox.a_receiver_idx INNER JOIN t_characters chTarget ON chTarget.a_index = mailbox.a_sender_idx "
			"WHERE mailbox.a_index = %d AND mailbox.a_receiver_idx = %d AND mailbox.a_sender_type = 0 AND ch.a_user_index = %d")
			% packet->mailId % packet->charIndex % packet->userIndex);
		break;
	case SystemMails:
		sql = boost::str(boost::format("SELECT mailbox.a_index, mailbox.a_sender_idx, mailbox.a_sender_type, mailbox.a_receiver_idx, "
			"mailbox.a_subject, mailbox.a_message, mailbox.a_nas, UNIX_TIMESTAMP(mailbox.a_date) as a_date, mailbox.a_readed, "
			"mailbox.a_collected FROM t_mailbox mailbox INNER JOIN t_characters ch ON ch.a_index = mailbox.a_receiver_idx "
			"WHERE mailbox.a_index = %d AND mailbox.a_receiver_idx = %d AND mailbox.a_sender_type = 1 AND ch.a_user_index = %d")
			% packet->mailId % packet->charIndex % packet->userIndex);
		break;
	}

	db.Init(&gserver.m_dbchar);
	db.SetQuery(sql);

	if (!db.Open() || !db.MoveFirst())
	{
		rpacket->error = DbError;
		goto SEND_MESSAGE;
	}

	db.GetRec("a_index", rpacket->letter.index);
	db.GetRec("a_sender_type", senderType);
	db.GetRec("a_subject", subject);
	db.GetRec("a_message", message);
	db.GetRec("a_date", timestamp);
	db.GetRec("a_collected", isCollected);
	db.GetRec("a_nas", rpacket->letter.nas);
	db.GetRec("a_readed", isRead);

	if (packet->pageType == SystemMails)
	{
		user = "System";
		rpacket->letter.senderJob = 0;
	}
	else
	{
		db.GetRec("a_nick", user);
		db.GetRec("a_job", rpacket->letter.senderJob);
	}

	rpacket->letter.recvTime = timestamp;
	rpacket->letter.senderType = (MailSenderTypes)senderType;
	rpacket->letter.isRead = isRead;
	rpacket->letter.haveAttachment = !isCollected;
	rpacket->letter.isMeLetter = packet->pageType == Sent;

	strcpy(rpacket->letter.targetUser, (const char*)user);
	strcpy(rpacket->letter.subject, (const char*)subject);
	strcpy(rpacket->letter.message, (const char*)message);

	if (isCollected)
	{
		rpacket->letter.nas = 0;
	}
	else
	{
		sql = boost::str(boost::format("SELECT * FROM t_mailbox_items WHERE a_mail_index = %d LIMIT %d") % packet->mailId % LETTER_MAX_ITEMS);
		db.SetQuery(sql);
		if (!db.Open())
		{
			rpacket->error = DbError;
			goto SEND_MESSAGE;
		}

		while (db.MoveNext())
		{
			getItemByExpress(&rpacket->letter.list[i], db, db.GetRecordRow());
			i++;
		}
	}

	if (packet->pageType != Sent)
	{
		sql = boost::str(boost::format("UPDATE t_mailbox SET a_readed = 1 WHERE a_index = %d") % packet->mailId);
		db.SetQuery(sql);
		db.Update();
	}

	rpacket->error = Ok;

SEND_MESSAGE:
	rpacket->type = MSG_MAIL_BOX;
	rpacket->subType = MSG_SUB_MAILBOX_OPEN_LETTER;
	rpacket->charIndex = packet->charIndex;
	rpacket->letter.itemsCount = i;

	rmsg->setSize(sizeof(*rpacket) + (sizeof(rpacket->letter.list[0]) * rpacket->letter.itemsCount));
	SEND_Q(rmsg, dest);
}

void do_MailBoxCollect(CNetMsg::SP& msg, CDescriptor* dest)
{
	CNetMsg::SP rmsg(new CNetMsg);
	RequestClient::MailBoxCollectLetterGS* packet = reinterpret_cast<RequestClient::MailBoxCollectLetterGS*>(msg->m_buf);
	ResponseClient::MailBoxCollectLetterGS* rpacket = reinterpret_cast<ResponseClient::MailBoxCollectLetterGS*>(rmsg->m_buf);

	int i = 0;

	std::string sql = boost::str(boost::format("SELECT mailbox.a_nas FROM t_mailbox mailbox "
		"WHERE mailbox.a_index = %d AND mailbox.a_receiver_idx = %d AND mailbox.a_collected = 0")
		% packet->mailId % packet->charIndex);
	
	CDBCmd db;
	db.Init(&gserver.m_dbchar);
	db.BeginTrans();
	db.SetQuery(sql);
	if (!db.Open() || !db.MoveFirst())
	{
		rpacket->error = DbError;
		goto SEND_MESSAGE;
	}

	db.GetRec("a_nas", rpacket->nas);
	
	sql = boost::str(boost::format("SELECT * FROM t_mailbox_items WHERE a_mail_index = %d LIMIT %d") 
		% packet->mailId % LETTER_MAX_ITEMS);
	db.SetQuery(sql);
	if (!db.Open())
	{
		rpacket->error = DbError;
		goto SEND_MESSAGE;
	}

	while (db.MoveNext())
	{
		MYSQL_ROW row = db.GetRecordRow();
		getItemByExpress(&rpacket->list[i], db, row);
		i++;
	}

	sql = boost::str(boost::format("UPDATE t_mailbox SET a_collected = 1 WHERE a_index = %d") % packet->mailId);
	db.SetQuery(sql);
	if (!db.Update() || db.GetRecordCount() != 1)
	{
		rpacket->error = DbError;
		db.Rollback();
		goto SEND_MESSAGE;
	}

	rpacket->error = Ok;
	db.Commit();

SEND_MESSAGE:
	rpacket->type = MSG_MAIL_BOX;
	rpacket->subType = MSG_SUB_MAILBOX_LETTER_COLLECT;
	rpacket->mailId = packet->mailId;
	rpacket->charIndex = packet->charIndex;
	rpacket->itemsCount = i;

	rmsg->setSize(sizeof(*rpacket) + sizeof(rpacket->list[0]) * rpacket->itemsCount);
	SEND_Q(rmsg, dest);
}

void do_MailBoxCollectRollback(CNetMsg::SP& msg, CDescriptor* dest)
{
	RequestClient::MailBoxCollectLetterGS* packet = reinterpret_cast<RequestClient::MailBoxCollectLetterGS*>(msg->m_buf);
	std::string sql = boost::str(boost::format("UPDATE t_mailbox SET a_collected = 0 WHERE a_index = %d") % packet->mailId);

	CDBCmd db;
	db.Init(&gserver.m_dbchar);
	db.SetQuery(sql);
	db.Update();
}

void do_MailBoxSendLetter(CNetMsg::SP& msg, CDescriptor* dest)
{
	CNetMsg::SP rmsg(new CNetMsg);
	RequestClient::MailBoxSendGS* packet = reinterpret_cast<RequestClient::MailBoxSendGS*>(msg->m_buf);
	ResponseClient::MailBoxSendGS* rpacket = reinterpret_cast<ResponseClient::MailBoxSendGS*>(rmsg->m_buf);

	int mailId;
	std::string qry;
	qry.reserve(2048);

	char tSubject[MAX_SUBJECT_LENGTH];
	char tMessage[MAX_MESSAGE_LENGTH];

	mysql_real_escape_string(&gserver.m_dbchar, tSubject, packet->subject, strlen(packet->subject));
	mysql_real_escape_string(&gserver.m_dbchar, tMessage, packet->message, strlen(packet->message));

	bool haveAttachments = packet->nas > 0 || packet->itemCount > 0;
	std::string sql = boost::str(boost::format("INSERT INTO t_mailbox (a_sender_idx, a_sender_type, a_receiver_idx, "
		"a_subject, a_message, a_nas, a_date, a_collected) VALUES (%1%, %2%, %3%, '%4%', '%5%', %6%, NOW(), %7%)") 
		% packet->charIndex % packet->senderType % packet->targetCharIndex % tSubject % tMessage
		% packet->nas % (int)(!haveAttachments));

	CDBCmd db;
	db.Init(&gserver.m_dbchar);
	db.BeginTrans();
	db.SetQuery(sql);

	if (!db.Update())
	{
		db.Rollback();
		rpacket->error = DbError;
		goto SEND_MESSAGE;
	}

	mailId = db.insertid();

	for (int i = 0; i < packet->itemCount; i++)
	{
#ifdef DURABILITY
		qry = "INSERT INTO t_mailbox_items(a_mail_index, a_item_index, a_plus, a_plus2, a_flag, a_serial,"
			"a_item_count, a_option_count, a_option_0_type, a_option_0_level, a_option_1_type,"
			"a_option_1_level, a_option_2_type, a_option_2_level, a_option_3_type, a_option_3_level, a_option_4_type, a_option_4_level,"
			"a_socket0, a_socket1, a_socket2, a_socket3, a_socket4, a_socket5, a_socket6,"
			"a_item_origin_var0, a_item_origin_var1, a_item_origin_var2, a_item_origin_var3, a_item_origin_var4, a_item_origin_var5,a_now_dur,a_max_dur) VALUES(";
#else
		qry = "INSERT INTO t_mailbox_items(a_mail_index, a_item_index, a_plus, a_plus2, a_flag, a_serial,"
			"a_item_count, a_option_count, a_option_0_type, a_option_0_level, a_option_1_type,"
			"a_option_1_level, a_option_2_type, a_option_2_level, a_option_3_type, a_option_3_level, a_option_4_type, a_option_4_level,"
			"a_socket0, a_socket1, a_socket2, a_socket3, a_socket4, a_socket5, a_socket6,"
			"a_item_origin_var0, a_item_origin_var1, a_item_origin_var2, a_item_origin_var3, a_item_origin_var4, a_item_origin_var5) VALUES(";
#endif

		qry += boost::str(boost::format("%1%,") % mailId);
		qry += boost::str(boost::format("%1%,") % packet->list[i].item_index);
		qry += boost::str(boost::format("%1%,") % (int)packet->list[i].plus);
		qry += boost::str(boost::format("%1%,") % (int)packet->list[i].plus2);
		qry += boost::str(boost::format("%1%,") % packet->list[i].flag);
		qry += boost::str(boost::format("'%1%',") % packet->list[i].serial);
		qry += boost::str(boost::format("%1%,") % packet->list[i].item_count);
		qry += boost::str(boost::format("%1%,") % packet->list[i].option_count);
		qry += boost::str(boost::format("%1%,") % packet->list[i].option_type[0]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].option_level[0]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].option_type[1]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].option_level[1]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].option_type[2]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].option_level[2]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].option_type[3]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].option_level[3]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].option_type[4]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].option_level[4]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].socket[0]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].socket[1]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].socket[2]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].socket[3]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].socket[4]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].socket[5]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].socket[6]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].item_origin[0]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].item_origin[1]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].item_origin[2]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].item_origin[3]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].item_origin[4]);
		qry += boost::str(boost::format("%1%,") % packet->list[i].item_origin[5]);
#ifdef DURABILITY
		qry += boost::str(boost::format("%1%,") % packet->list[i].now_durability);
		qry += boost::str(boost::format("%1% )") % packet->list[i].max_durability);
#endif

		db.SetQuery(qry);
		if (!db.Update())
		{
			db.Rollback();
			rpacket->error = DbError;
			goto SEND_MESSAGE;
		}
	}

	db.Commit();
	rpacket->error = Ok;

	{
		CNetMsg::SP updateMsg(new CNetMsg);
		ResponseClient::MailBoxCheckLettersGS* updatePacket = reinterpret_cast<ResponseClient::MailBoxCheckLettersGS*>(updateMsg->m_buf);
		updatePacket->type = MSG_MAIL_BOX;
		updatePacket->subType = MSG_SUB_MAILBOX_UPDATE_STATUS;
		updatePacket->charIndex = packet->targetCharIndex;
		updatePacket->newMailsCount = 1;
		updateMsg->setSize(sizeof(*updateMsg));
		gserver.SendToAllGameServer(updateMsg);
	}

SEND_MESSAGE:
	rpacket->type = MSG_MAIL_BOX;
	rpacket->subType = MSG_SUB_MAILBOX_SEND_LETTER;
	rpacket->charIndex = packet->charIndex;
	rmsg->setSize(sizeof(*rpacket));
	SEND_Q(rmsg, dest);
}

void do_MailBoxCheckNewLetter(CNetMsg::SP& msg, CDescriptor* dest)
{
	RequestClient::MailBoxCheckLettersGS* packet = reinterpret_cast<RequestClient::MailBoxCheckLettersGS*>(msg->m_buf);
	std::string sql = boost::str(boost::format("SELECT COUNT(a_index) as letter_count FROM t_mailbox WHERE a_receiver_idx = %d AND a_readed = 0 AND a_enable_receiver = 1")
		% packet->charIndex);

	CDBCmd db;
	db.Init(&gserver.m_dbchar);
	db.SetQuery(sql);

	if (!db.Open() || !db.MoveFirst()) return;
	
	ResponseClient::MailBoxCheckLettersGS* rpacket = reinterpret_cast<ResponseClient::MailBoxCheckLettersGS*>(msg->m_buf);
	db.GetRec("letter_count", rpacket->newMailsCount);

	msg->setSize(sizeof(*rpacket));
	SEND_Q(msg, dest);
}

void getItemByExpress(ExpressSystemItemInfo* info, CDBCmd& db, MYSQL_ROW& row)
{
	info->index = atoi(row[db.FindField("a_index")]);
	info->item_index = atoi(row[db.FindField("a_item_index")]);
	info->plus = atoi(row[db.FindField("a_plus")]);
	info->plus2 = atoi(row[db.FindField("a_plus2")]);
	info->flag = atoi(row[db.FindField("a_flag")]);
	memcpy(info->serial, row[db.FindField("a_serial")], MAX_SERIAL_LENGTH);
	info->serial[MAX_SERIAL_LENGTH] = '\0';
	info->item_count = atoi(row[db.FindField("a_item_count")]);
	info->option_count = atoi(row[db.FindField("a_option_count")]);
	info->option_type[0] = atoi(row[db.FindField("a_option_0_type")]);
	info->option_level[0] = atoi(row[db.FindField("a_option_0_level")]);
	info->option_type[1] = atoi(row[db.FindField("a_option_1_type")]);
	info->option_level[1] = atoi(row[db.FindField("a_option_1_level")]);
	info->option_type[2] = atoi(row[db.FindField("a_option_2_type")]);
	info->option_level[2] = atoi(row[db.FindField("a_option_2_level")]);
	info->option_type[3] = atoi(row[db.FindField("a_option_3_type")]);
	info->option_level[3] = atoi(row[db.FindField("a_option_3_level")]);
	info->option_type[4] = atoi(row[db.FindField("a_option_4_type")]);
	info->option_level[4] = atoi(row[db.FindField("a_option_4_level")]);
	info->socket[0] = atoi(row[db.FindField("a_socket0")]);
	info->socket[1] = atoi(row[db.FindField("a_socket1")]);
	info->socket[2] = atoi(row[db.FindField("a_socket2")]);
	info->socket[3] = atoi(row[db.FindField("a_socket3")]);
	info->socket[4] = atoi(row[db.FindField("a_socket4")]);
	info->socket[5] = atoi(row[db.FindField("a_socket5")]);
	info->socket[6] = atoi(row[db.FindField("a_socket6")]);
	info->item_origin[0] = atoi(row[db.FindField("a_item_origin_var0")]);
	info->item_origin[1] = atoi(row[db.FindField("a_item_origin_var1")]);
	info->item_origin[2] = atoi(row[db.FindField("a_item_origin_var2")]);
	info->item_origin[3] = atoi(row[db.FindField("a_item_origin_var3")]);
	info->item_origin[4] = atoi(row[db.FindField("a_item_origin_var4")]);
	info->item_origin[5] = atoi(row[db.FindField("a_item_origin_var5")]);

#ifdef DURABILITY
	info->now_durability = atoi(row[db.FindField("a_now_dur")]);
	info->max_durability = atoi(row[db.FindField("a_max_dur")]);
#endif
}
