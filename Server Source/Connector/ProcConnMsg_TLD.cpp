#include "stdhdrs.h"

#ifdef USE_TENTER_BILLING

#include "Log.h"
#include "Server.h"
#include "../ShareLib/DBCmd.h"
#include "CmdMsg.h"
#include "ProcConnMsg.h"
#if defined(BCRYPT_USA) && !defined (CIRCLE_WINDOWS)
#include "../ShareLib/CheckPassword.h"
#elif defined RUS_BCRYPT
#include "../ShareLib/CheckPassword.h"
#endif
#ifdef PASSWORD_ENCRYPT_SHA256
#include "LCSha256.h"
#endif // PASSWORD_ENCRYPT_SHA256

//XX �α��� 1-A
void ConnLogin(CDescriptor* d, CNetMsg::SP& msg)
{
	unsigned char subtype;
	msg->MoveFirst();
	RefMsg(msg) >> subtype;

	CLCString id(MAX_ID_NAME_LENGTH + 1);
	CLCString pw(MAX_PWD_LENGTH + 1);
	int serverno, subno;
	unsigned char playmode;
	CLCString ip(HOST_LENGTH + 1);

	RefMsg(msg) >> id >> pw >> serverno >> subno >> playmode >> ip;

	if (serverno != gserver.m_serverno || subno < 1 || subno > gserver.m_maxSubServer)
	{
		GAMELOG << init("LOGIN_FAIL", id)
				<< "From" << delim << d->m_subno << delim
				<< "No match : server no or sub no" << delim
				<< "Server" << delim << serverno << "-" << subno
				<< end;
		CNetMsg::SP rmsg(new CNetMsg);
		LoginRepMsg(rmsg, MSG_CONN_ERROR_SYSTEM, id, NULL);
		SEND_Q(rmsg, d);
		return ;
	}

	// ���� ã��
	CUser* user = gserver.m_userList[subno - 1].Find(id);
	if (user == NULL)
	{
		// ���� ���� ��
		// �����ͺ��̽����� ã��
		MSG_CONN_ERRORCODE errcode = ReadDB(id, pw, serverno, subno, ip, &user, playmode);
		if (errcode != MSG_CONN_ERROR_SUCCESS)
		{
			GAMELOG << init("LOGIN_FAIL", id)
					<< "From" << delim << d->m_subno << delim
					<< errcode
					<< end;
			CNetMsg::SP rmsg(new CNetMsg);
			LoginRepMsg(rmsg, errcode, id, NULL);
			SEND_Q(rmsg, d);
			return ;
		}

		user->m_descserver = d;

		// �����ͺ��̽� ������Ʈ
		errcode = WriteDB(user->m_index, serverno, subno, 0, 0, user->m_name, ip, true);
		if (errcode != MSG_CONN_ERROR_SUCCESS)
		{
			GAMELOG << init("LOGIN_FAIL", id)
					<< "From" << delim << d->m_subno << delim
					<< errcode
					<< end;
			CNetMsg::SP rmsg(new CNetMsg);
			LoginRepMsg(rmsg, errcode, id, NULL);
			SEND_Q(rmsg, d);
			return ;
		}

		// �÷��̾� ����Ʈ�� �߰�
		if (gserver.m_userList[subno - 1].Add(user) == NULL)
		{
			GAMELOG << init("LOGIN_FAIL", id)
					<< "From" << delim << d->m_subno << delim
					<< MSG_CONN_ERROR_FULLUSER
					<< end;
			CNetMsg::SP rmsg(new CNetMsg);
			LoginRepMsg(rmsg, MSG_CONN_ERROR_FULLUSER, id, NULL);
			SEND_Q(rmsg, d);
			return ;
		}

		// ���� ����� �� ī��Ʈ
		gserver.m_userList[subno - 1].m_playersPerZone[user->m_zone]++;

		/*
		if (!gserver.m_billing.IsRunning())
		{
		*/
		GAMELOG << init("NO BILLING - FREE MODE", id)
				<< "From" << delim << d->m_subno << delim
				<< end;

		user->m_state = CONN_PLAYING;
		user->m_usertype = BILL_USER_FREE;
		user->m_timeremain = 0;
		user->m_paytype = BILL_PAY_FREE;
		//user->m_location = BILL_LOCATION_HOME;

		CNetMsg::SP rmsg(new CNetMsg);
		LoginRepMsg(rmsg, MSG_CONN_ERROR_SUCCESS, id, user);
		SEND_Q(rmsg, d);
		return ;
		/*
		}
		else
		{
		// ������ �˸���
		gserver.m_billing.Login(user->m_name, pw, ip);
		}
		*/

		user->m_descserver = d;
	}
	else
	{
		// ���� ���� ��
		// �÷��̸�� �˻�
		if (playmode == MSG_LOGIN_RE && user->m_state == CONN_CHANGE_SERVER)
		{
			// ���� �̵��� ��

			// ���� ���� �Ϲ����� ����
			user->m_state = CONN_PLAYING;

			CNetMsg::SP rmsg(new CNetMsg);
			LoginRepMsg(rmsg, MSG_CONN_ERROR_SUCCESS, id, user);
			SEND_Q(rmsg, d);
		}
		else
		{
			// ���� �̵� �ƴ� ��

			GAMELOG << init("LOGIN_FAIL", id)
					<< "From" << delim << d->m_subno << delim
					<< MSG_CONN_ERROR_ALREADY
					<< end;

			// ���� ó�� : �ߺ� ����
			CNetMsg::SP rmsg(new CNetMsg);
			LoginRepMsg(rmsg, MSG_CONN_ERROR_ALREADY, id, NULL);
			SEND_Q(rmsg, d);
		}
	}
}

void ConnLogout(CDescriptor* d, CNetMsg::SP& msg)
{
	unsigned char subtype;
	msg->MoveFirst();
	RefMsg(msg) >> subtype;

	CLCString id(MAX_ID_NAME_LENGTH + 1);
	RefMsg(msg) >> id;

	// ������ ã��
	CUser* user = NULL;
	if (d->m_bLoginServer)
	{
		int i;
		for (i = 0; i < gserver.m_maxSubServer; i++)
		{
			user = gserver.m_userList[i].Find(id);
			if (user != NULL)
				break;
		}
	}
	else
	{
		user = gserver.m_userList[d->m_subno - 1].Find(id);
	}

	if (user == NULL)
	{
		GAMELOG << init("SYS_ERR", id)
				<< "From" << delim << d->m_subno << delim
				<< "Not Found User" << end;

// TODO : DELETE 		// ������ �α׾ƿ� �˸���
// TODO : DELETE 		if (gserver.m_billing.IsRunning())
// TODO : DELETE 			gserver.m_billing.Logout(user->m_name);

//		// DB�� ����
//		if (!WriteDB(id))
//			GAMELOG << init("SYS_ERR", id)
//					<< "From" << delim << d->m_subno << delim
//					<< "Cannot Update DB for Logout" << end;
		return ;
	}

	gserver.ProcessLogout(user);
}

void ConnBLogin(CDescriptor* d, CNetMsg::SP& msg)
{
	unsigned char subtype;
	msg->MoveFirst();
	RefMsg(msg) >> subtype;

	CLCString id(MAX_ID_NAME_LENGTH + 1);
	CLCString ip(HOST_LENGTH + 1);

	RefMsg(msg) >> id >> ip;

	CUser* user = NULL;
	if (d->m_bLoginServer)
	{
		int i;
		for (i = 0; i < gserver.m_maxSubServer; i++)
		{
			user = gserver.m_userList[i].Find(id);
			if (user != NULL)
				break;
		}
	}
	else
	{
		user = gserver.m_userList[d->m_subno - 1].Find(id);
	}

	if (user == NULL)
	{
		GAMELOG << init("SYS_ERR", id)
				<< "From" << delim << d->m_subno << delim
				<< "BLogin" << delim << "Not Found User" << end;
		user = NULL;
		delete user;
		return ;
	}

	if (gserver.m_billing.IsRunning())
	{
		gserver.m_billing.Login(user->m_name, user->m_name, ip);
	}
	user = NULL;
	delete user;
}

void ConnBLogout(CDescriptor* d, CNetMsg::SP& msg)
{
	unsigned char subtype;
	msg->MoveFirst();
	RefMsg(msg) >> subtype;

	CLCString id(MAX_ID_NAME_LENGTH + 1);

	RefMsg(msg) >> id;

	CUser* user = NULL;
	if (d->m_bLoginServer)
	{
		int i;
		for (i = 0; i < gserver.m_maxSubServer; i++)
		{
			user = gserver.m_userList[i].Find(id);
			if (user != NULL)
				break;
		}
	}
	else
	{
		user = gserver.m_userList[d->m_subno - 1].Find(id);
	}

	if (user == NULL)
	{
		GAMELOG << init("SYS_ERR", id)
				<< "From" << delim << d->m_subno << delim
				<< "BLogout" << delim << "Not Found User" << end;

		user = NULL;
		delete user;
		return ;
	}

	if (gserver.m_billing.IsRunning())
	{
		gserver.m_billing.Logout(user->m_name);
	}
	user = NULL;
	delete user;
}

void ConnCashItemPurchaseHistoryReq(CDescriptor* d, CNetMsg::SP& msg)
{
	int userindex, charindex, y;
	char m, n;

	RefMsg(msg) >> userindex
				>> charindex
				>> y
				>> m
				>> n;

	CNetMsg::SP rmsg(new CNetMsg);
	ConnCashItemPurchaseHistoryRep(rmsg, userindex, charindex, y, m, n);
	SEND_Q(rmsg, d);
}
void ConnCashItemPurchaselistReq(CDescriptor* d, CNetMsg::SP& msg)
{
	//MSG_CONN_CASHITEM_PURCHASELIST_REQ, // ���Ը��     : userindex(n) charindex(n)
	//MSG_CONN_CASHITEM_PURCHASELIST_REP, // ����			: charindex(n) errorCode(uc) count(n) idx(n) ctid(n)
	int userindex, charindex;
	int count = 0;
	int ctid[25];
	int idx[25];

	memset(idx, -1, sizeof(idx) );
	memset(ctid, -1, sizeof(ctid) );

	RefMsg(msg) >> userindex
				>> charindex;

	CLCString sql(4096);
	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);
#ifdef BUGFIX_CASHSHOP_PURCHASE_CONFIRM
	sql.Format("select a_index, a_ctid from t_purchase0%d where a_confirm = 1 and a_use_char_idx = 0 and a_user_idx = %d and a_server = %d ", userindex % 10, userindex, gserver.m_serverno );
#else
	sql.Format("select a_index, a_ctid from t_purchase0%d where a_use_char_idx = 0 and a_user_idx = %d and a_server = %d ", userindex % 10, userindex, gserver.m_serverno );
#endif
	cmd.SetQuery(sql);

	if( !cmd.Open() )
	{
		// ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ConnCashItemPurchaselistRep(rmsg, charindex, MSG_EX_CASHITEM_ERROR_SUCCESS, count, 0, 0);
		SEND_Q(rmsg, d);
		return;
	}

	if( !cmd.MoveFirst() )
	{
		// ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ConnCashItemPurchaselistRep(rmsg, charindex, MSG_EX_CASHITEM_ERROR_SUCCESS, count, 0, 0);
		SEND_Q(rmsg, d);
		return;
	}

	do
	{
		cmd.GetRec("a_index", idx[count] );
		cmd.GetRec("a_ctid", ctid[count] );
		count++;
		if(count >= 25) break;
	}
	while( cmd.MoveNext() );

	CNetMsg::SP rmsg(new CNetMsg);
	ConnCashItemPurchaselistRep(rmsg, charindex, MSG_EX_CASHITEM_ERROR_SUCCESS, count, idx, ctid);
	SEND_Q(rmsg, d);
}
void ConnCashItemBringReq(CDescriptor* d, CNetMsg::SP& msg)
{
	ConnCashItemBringProcess(d, msg, false);
}

void ConnCashItemBringProcess(CDescriptor* d, CNetMsg::SP& msg, bool bPresent)
{
	//MSG_CONN_CASHITEM_BRING_REQ, ��������� ��������: userindex(n) charindex(n) count(n) idx(n)
	int userindex, charindex, count, i;
	int idx[MAX_PURCHASEITEM];
	int ctid[MAX_PURCHASEITEM];

	memset(idx, -1, sizeof(idx) );
	memset(ctid, -1, sizeof(ctid) );

	RefMsg(msg) >> userindex
				>> charindex
				>> count;

	for(i = 0; i < count; i++)
	{
		RefMsg(msg) >> idx[i]
					>> ctid[i];
	}

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);

	CLCString sql(4096);

	cmd.BeginTrans();

	for(i = 0; i < count; i++)
	{
		if( bPresent)
			sql.Format("update t_gift0%d set a_use_char_idx = %d, a_use_date = now() "
					   "where a_recv_user_idx = %d and a_use_char_idx = 0 and a_index = %d and a_ctid = %d and a_server = %d ",
					   userindex % 10, charindex, userindex, idx[i], ctid[i], gserver.m_serverno );
		else
			sql.Format("update t_purchase0%d set a_use_char_idx = %d, a_use_date = now() "
					   "where a_user_idx = %d and a_use_char_idx = 0 and a_index = %d and a_ctid = %d and a_server = %d ",
					   userindex % 10, charindex, userindex, idx[i], ctid[i], gserver.m_serverno );

		cmd.SetQuery(sql);
		if( !cmd.Update() )
		{
			// Ŀ���� �����޼���
			// �ѹ�
			CNetMsg::SP rmsg(new CNetMsg);
			ConnCashItemBringRep(rmsg, charindex, MSG_EX_CASHITEM_ERROR_NOTITEM, bPresent, count, ctid);
			SEND_Q(rmsg, d);
			cmd.Rollback();

			GAMELOG << init("CASH_ITEM_BRING_ERROR")
					<< (bPresent ? "PRESENT" : "NOT_PRESENT") << delim
					<< userindex << delim
					<< charindex << delim
					<< count << delim;

			for(i = 0; i < count; i++)
			{
				GAMELOG << idx[i] << delim
						<< ctid[i];
			}
			GAMELOG << end;
			return;
		}

		if( cmd.GetRecordCount() < 1 )
		{
			// Ŀ���� �����޼���
			// �ѹ�
			CNetMsg::SP rmsg(new CNetMsg);
			ConnCashItemBringRep(rmsg, charindex, MSG_EX_CASHITEM_ERROR_NOTITEM, bPresent, count, ctid);
			SEND_Q(rmsg, d);
			cmd.Rollback();

			GAMELOG << init("CASH_ITEM_BRING_ERROR")
					<< (bPresent ? "PRESENT" : "NOT_PRESENT") << delim
					<< userindex << delim
					<< charindex << delim
					<< count << delim;

			for(i = 0; i < count; i++)
			{
				GAMELOG << idx[i] << delim
						<< ctid[i];
			}
			GAMELOG << end;
			return;
		}
	}

	CNetMsg::SP rmsg(new CNetMsg);
	if( bPresent )
		ConnCashItemBringRep(rmsg, charindex, MSG_EX_CASHITEM_ERROR_GIFTRECV_SUCCESS, bPresent, count, ctid);
	else
		ConnCashItemBringRep(rmsg, charindex, MSG_EX_CASHITEM_ERROR_SUCCESS, bPresent, count, ctid);
	SEND_Q(rmsg, d);
	cmd.Commit();
	// ���� ����
}

void ConnCashItemBalanceReq(CDescriptor* d, CNetMsg::SP& msg)
{
	int userindex;
	CLCString idname(MAX_ID_NAME_LENGTH + 1);

	RefMsg(msg) >> userindex
				>> idname;

	if (gserver.m_billing.IsRunning())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		BillBalanceReqMsg(rmsg, userindex, idname);
		gserver.m_billing.WriteToOutput(rmsg);
	}
	else
	{
		//�������� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ConnCashItemBalanceRep(rmsg, userindex, MSG_EX_CASHITEM_ERROR_BILL, -1);
		SEND_Q(rmsg, d);
	}
}

void ConnCashItemPurchaseReq(CDescriptor* d, CNetMsg::SP& msg)
{
	int cash, count, userindex, charindex, i;
	int ctid[MAX_PURCHASEITEM];
	CLCString idname(MAX_ID_NAME_LENGTH + 1);
	int sumCount = 0;
	int requestCash = -1;

	memset(ctid, -1, sizeof(ctid) );

	RefMsg(msg) >> userindex
				>> idname
				>> charindex
				>> cash
				>> count;

	if(count > MAX_PURCHASEITEM)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnCashItemPurchaseRep(rmsg, userindex, MSG_EX_CASHITEM_ERROR_OVERITEM, cash);
		SEND_Q(rmsg, d);
		return;
	}

	for(i = 0; i < count; i++)
	{
		RefMsg(msg) >> ctid[i];
	}

	// ���� ��û�� ���Ӽ����� �����Ǹ� �������� �������� �����ϹǷ� �޾Ƽ� ���� Ŀ���Ͱ� ������ �ִ� ����Ʈ�� �ִ� ��ǰ�̸�
	// ���������� ���� ��û�ϰ� ���� ��ǰ�̸� Ŀ������ �����Ǹ� ����Ʈ�� �߰��Ѵ�.
	int lcount;
	RefMsg(msg) >> lcount;

	if(count + lcount > MAX_PURCHASEITEM)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnCashItemPurchaseRep(rmsg, userindex, MSG_EX_CASHITEM_ERROR_OVERITEM, cash);
		SEND_Q(rmsg, d);
		return;
	}

	for(; i < lcount + count; i++)
	{
		RefMsg(msg) >> ctid[i];

		CServer::map_limitsell_t::iterator it = gserver.m_limitSell.find(ctid[i]);
		if( it == gserver.m_limitSell.end() )
		{
			CLimitSell* limit = new CLimitSell(ctid[i], 0);
			gserver.m_limitSell.insert(CServer::map_limitsell_t::value_type(ctid[i], limit));
			gserver.m_changeLimit = true;
		}
	}
	count += lcount;

	RefMsg(msg) >> requestCash;

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);

	CLCString sql(4096);
	sql.Format("select count(*) as depository from t_purchase0%d where a_user_idx = %d and a_use_char_idx = 0 and a_confirm = 1 and a_server=%d", userindex%10, userindex, gserver.m_serverno);
	cmd.SetQuery(sql);

	if( !cmd.Open() )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnCashItemPurchaseRep(rmsg, userindex, MSG_EX_CASHITEM_ERROR_CONN, cash);
		SEND_Q(rmsg, d);
		return;
	}

	if( !cmd.MoveFirst() )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnCashItemPurchaseRep(rmsg, userindex, MSG_EX_CASHITEM_ERROR_CONN, cash);
		SEND_Q(rmsg, d);
		return;
	}

	if( !cmd.GetRec("depository", sumCount) )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnCashItemPurchaseRep(rmsg, userindex, MSG_EX_CASHITEM_ERROR_NOTITEM, cash);
		SEND_Q(rmsg, d);
		return;
	}

	sumCount += count;

	if( sumCount > MAX_DEPOSITORY)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnCashItemPurchaseRep(rmsg, userindex, MSG_EX_CASHITEM_ERROR_NOSPACE, cash);
		SEND_Q(rmsg, d);
		return;
	}

	// �������� ��û�� ���������� �Ѵ�
	if( gserver.m_billing.IsRunning() )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		BillCanbuyReqMsg(rmsg, userindex, idname, count, ctid, requestCash);
		gserver.m_billing.WriteToOutput(rmsg);

		{
			GAMELOG << init("BUY_CASH_ITEM_START") << userindex << delim;
			for (int i = 0; i < count; ++i)
			{
				GAMELOG << ctid[i] << delim;
			}
			GAMELOG << requestCash << end;
		}
	}
	else
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnCashItemPurchaseRep(rmsg, userindex, MSG_EX_CASHITEM_ERROR_BILL, cash);
		SEND_Q(rmsg, d);
		return;
	}
}

void ConnCashItemGift(CDescriptor* d, CNetMsg::SP& msg)
{
	CLCString sendName(MAX_CHAR_NAME_LENGTH + 1);
	CLCString recvName(MAX_CHAR_NAME_LENGTH + 1);
	CLCString sendMsg(MAX_GIFT_MESSAGE_LENGTH + 1);
	int recvUserIndex, sendUserIndex, sendCharIndex, recvCharIndex;
	int count, i;
	int idx[10], ctid[10];

	RefMsg(msg) >> sendUserIndex
				>> sendCharIndex
				>> sendName
				>> sendMsg
				>> recvUserIndex
				>> recvCharIndex
				>> recvName
				>> count;

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);

	CLCString sql(4096);
	cmd.BeginTrans();

	for(i = 0; i < count; i++ )
	{
		RefMsg(msg) >> idx[i]
					>> ctid[i];

		sql.Format("update t_purchase0%d set a_use_char_idx = %d, a_use_date = now() "
				   "where a_user_idx = %d and a_use_char_idx = 0 and a_index = %d and a_ctid = %d and a_server = %d ",
				   sendUserIndex % 10, sendCharIndex, sendUserIndex, idx[i], ctid[i], gserver.m_serverno );

		cmd.SetQuery(sql);
		if( !cmd.Update() )
		{
			// ���� �޼��� ( ���� ��û�� ��ǰ�� ���� )

			cmd.Rollback();
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_CONN_REP);
			RefMsg(rmsg) << (unsigned char) MSG_CONN_CASHITEM_GIFT
						 << (unsigned char) MSG_EX_CASHITEM_ERROR_NOTITEM
						 << sendCharIndex
						 << recvCharIndex;

			SEND_Q(rmsg, d);
			return;
		}

		if( cmd.GetRecordCount() < 1 )
		{
			// ���� �޼��� ( ���� ��û�� ��ǰ�� ���� )
			cmd.Rollback();
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_CONN_REP);
			RefMsg(rmsg) << (unsigned char) MSG_CONN_CASHITEM_GIFT
						 << (unsigned char) MSG_EX_CASHITEM_ERROR_NOTITEM
						 << sendCharIndex
						 << recvCharIndex;

			SEND_Q(rmsg, d);
			return;
		}

		char escape_sendName[MAX_CHAR_NAME_LENGTH * 2 + 1];
		mysql_escape_string(escape_sendName, sendName, sendName.Length());
		char escape_recvName[MAX_CHAR_NAME_LENGTH * 2 + 1];
		mysql_escape_string(escape_recvName, recvName, recvName.Length());
		char escape_sendMsg[MAX_GIFT_MESSAGE_LENGTH * 2 + 1];
		mysql_escape_string(escape_sendMsg, sendMsg, sendMsg.Length());

		sql.Format(" insert into t_gift0%d (a_server, a_send_user_idx, a_send_char_name, a_send_msg, a_recv_user_idx, a_recv_char_name, a_send_date, a_ctid ) "
				   "values (%d, %d, '%s', '%s', %d, '%s', now(), %d )",
				   recvUserIndex % 10, gserver.m_serverno, sendUserIndex, escape_sendName, escape_sendMsg, recvUserIndex, escape_recvName, ctid[i]);

		cmd.SetQuery(sql);
		if( !cmd.Update() )
		{
			cmd.Rollback();
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_CONN_REP);
			RefMsg(rmsg) << (unsigned char) MSG_CONN_CASHITEM_GIFT
						 << (unsigned char) MSG_EX_CASHITEM_ERROR_NOTITEM
						 << sendCharIndex
						 << recvCharIndex;

			SEND_Q(rmsg, d);
			return;
		}
	}
	cmd.Commit();

	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_CONN_REP);
	RefMsg(rmsg) << (unsigned char) MSG_CONN_CASHITEM_GIFT
				 << (unsigned char) MSG_EX_CASHITEM_ERROR_GIFT_SUCCESS
				 << sendCharIndex
				 << recvCharIndex;

	SEND_Q(rmsg, d);
}

void ConnCashItemSendHistory(CDescriptor* d, CNetMsg::SP& msg)
{
	ConnCashItemPresentHistory(d, msg, true);
}

void ConnCashItemRecvHistory(CDescriptor* d, CNetMsg::SP& msg)
{
	ConnCashItemPresentHistory(d, msg, false);
}

void ConnCashItemPresentHistory(CDescriptor* d, CNetMsg::SP& msg, bool bSend )
{
	int userindex, charindex, y;
	char m, n;

	RefMsg(msg) >> userindex
				>> charindex
				>> y
				>> m
				>> n;

	CNetMsg::SP rmsg(new CNetMsg);
	ConnCashItemPresentHistoryRep(rmsg, userindex, charindex, y, m, n, bSend);
	SEND_Q(rmsg, d);
}

void ConnCashItemRecvList(CDescriptor* d, CNetMsg::SP& msg)
{
	int charIndex, userIndex;
	int idx, ctid;
	int sendDate;
//	CLCString strMsg(50 + 1);
	CLCString strMsg(100 + 1);		// modified by kjban
	CLCString sendName( MAX_CHAR_NAME_LENGTH + 1);

	RefMsg(msg) >> userIndex
				>> charIndex;

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);

	CLCString sql(4096);
	sql.Format("select a_index, a_ctid, a_send_char_name, a_send_msg, UNIX_TIMESTAMP(a_send_date) as a_sendDate from t_gift0%d "
			   "where a_server = %d and a_recv_user_idx = %d and a_use_char_idx = 0 ", userIndex % 10, gserver.m_serverno, userIndex );

	cmd.SetQuery(sql);
	// 5������ �Ѱ��� ����
	if( cmd.Open() && cmd.GetRecordCount() > 0 && cmd.MoveFirst() )
	{
		int i = 0;
		int count = cmd.GetRecordCount();
		char listflag = 0;
		listflag |= ( 1 << 0 );

		CNetMsg temp;
		temp.Init();

		do
		{
			i++;
			cmd.GetRec("a_index", idx);
			cmd.GetRec("a_ctid", ctid);
			cmd.GetRec("a_send_char_name", sendName);
			cmd.GetRec("a_send_msg", strMsg);
			cmd.GetRec("a_sendDate", sendDate);

			temp << idx
				 << ctid
				 << sendDate
				 << sendName
				 << strMsg;

			if( i % 5 == 0 )
			{
				// ����				: listflag(c) count(n) idx(n) ctid(n) date(un) sendcharName(str) msg(str)
				if( count == i )
					listflag |= ( 1 << 1);
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_CONN_REP);
				RefMsg(rmsg) << (unsigned char) MSG_CONN_CASHITEM_GIFT_RECVLIST
							 << charIndex
							 << listflag
							 << (int) 5
							 << temp;

				// �޼��� ������,
				SEND_Q(rmsg, d);

				temp.Init();						// ��ǰ �޼����� �ʱ�ȭ �ϰ�,
				listflag = listflag &~ ( 1 << 0 );// ��ŸƮ �÷��׸� ����,
			}
		}
		while( cmd.MoveNext() );

		// ����				: listflag(c) count(n) idx(n) ctid(n) date(un) sendcharName(str) msg(str)
		// end ����Ʈ �÷��� �����ϰ�,
		if( i % 5 )
		{
			listflag |= ( 1 << 1 );
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_CONN_REP);
			RefMsg(rmsg) << (unsigned char) MSG_CONN_CASHITEM_GIFT_RECVLIST
						 << charIndex
						 << listflag
						 << (int) ( i% 5)
						 << temp;

			// �޼��� ������,
			SEND_Q(rmsg, d);
		}
	}
	else
	{
		// empty ����Ʈ �÷��� ����
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_CONN_REP);
		RefMsg(rmsg) << (unsigned char) MSG_CONN_CASHITEM_GIFT_RECVLIST
					 << charIndex
					 << (unsigned char) (1 << 2);

		SEND_Q(rmsg, d);
	}
}

void ConnCashItemRecv(CDescriptor* d, CNetMsg::SP& msg)
{
	ConnCashItemBringProcess(d, msg, true);
}


#endif