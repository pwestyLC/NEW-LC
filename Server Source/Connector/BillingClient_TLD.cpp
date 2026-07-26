#include "stdhdrs.h"

#include "../ShareLib/bnf.h"

#ifdef USE_TENTER_BILLING

#include "Server.h"
#include "Log.h"
#include "BillingClient.h"
#include "CmdMsg.h"
#include "ProcConnMsg.h"
#include <boost/format.hpp>

CBillingClient::CBillingClient()
{
}

bool CBillingClient::Login(const char* name, const char* pw, const char* ip)
{
	return true;
}

bool CBillingClient::Logout(const char* name)
{
	return true;
}

void CBillingClient::operate(rnSocketIOService* service)
{
	CNetMsg::SP msg(service->GetMessage());

	LOG_INFO("OOO (R) : type[%d] size[%d]", msg->m_mtype, msg->m_size);

	switch(msg->m_mtype)
	{
	case MSG_BILLITEM_CASHBALANCE_REP:
		{
			OnCashBalance(msg);
		}
		break;
	case MSG_BILLITEM_CANBUY_REP:
		{
			OnCanBuy(msg);
		}
		break;
	case MSG_BILLITEM_BUY_REP:
		{
			OnBuy(msg);
		}
		break;
	default:
		{
			GAMELOG << init("UNKNOWN PACKET") << msg->m_mtype << end;
			return;
		}
		break;
	}
}

void CBillingClient::OnCashBalance(CNetMsg::SP& msg)
{
	unsigned char returnCode = 0;
	unsigned char gid = 0;
	int userindex;
	int cid = 0;
	int cashBalance = 0;
	msg->MoveFirst();
	RefMsg(msg) >> returnCode
				>> gid
				>> userindex
				>> cid
				>> cashBalance;

	CUser * user = NULL;
	for(int i = 0; i < gserver.m_maxSubServer; i++)
	{
		user = gserver.m_userList[i].FindByUserIndex(userindex);
		if( user )
			break;
	}

	if( !user )
	{
		GAMELOG << init("CASH_BALANCE_ERROR")
				<< userindex;
		return;
	}

	//MSG_CONN_CASHiTEM_BALANCE_REP
	CNetMsg::SP rmsg(new CNetMsg);
	ConnCashItemBalanceRep(rmsg, user->m_index, (MSG_EX_CASHITEM_ERROR_TYPE) returnCode, cashBalance);
	SEND_Q(rmsg, user->m_descserver);
}
void CBillingClient::OnCanBuy(CNetMsg::SP& msg)
{
	//MSG_BILLITEM_CANBUY_REP,	// ����	  : returnCode(uc) gameId(uc) userId(str:32) cpId(n) itemId(n) cashBalance(int)
	// returnCode�� ���� �ൿ�� �Ͻÿ�
	unsigned char returnCode, gameId;
	int userindex;
	int cpId, cashBalance, ctId[MAX_PURCHASEITEM], i;
	char count;

	RefMsg(msg) >> returnCode
				>> gameId
				>> userindex
				>> cpId
				>> count;

	for(i = 0; i < count && i < MAX_PURCHASEITEM; i++)
	{
		RefMsg(msg) >> ctId[i];
	}

	RefMsg(msg) >> cashBalance;

	CUser* user = NULL;
	for(i = 0; i < gserver.m_maxSubServer; i++)
	{
		user = gserver.m_userList[i].FindByUserIndex(userindex);
		if(user) break;
	}

	if(!user)
	{
		GAMELOG << init("CASH_PURCHASE_REP_ERROR-NotUser")
				<< userindex << end;
		return;
	}

	if( returnCode == MSG_BILLITEM_ERROR_SUCCESS)
	{
		// ���� ��û�� ��
		// DB�� �����ʵ带 �߰�, �ø��� ��ȣ ������ �Žñ� �ؼ� �Žñ� �Ͻÿ�

		CDBCmd cmd(&gserver.m_dbauth);

//		a_index,	a_user_idx,a_server,a_ctid,a_serial,a_pdate,a_use_char_idx, a_use_date
		std::string insertSql = boost::str(boost::format("INSERT INTO t_purchase0%d ( a_user_idx, a_server, a_ctid, a_serial, a_pdate, a_ip) VALUES ") % (userindex % 10));
		int i = 0;
		for(i = 0; i < count && i < MAX_PURCHASEITEM && ctId[i] != -1; i++)
		{
			insertSql += boost::str(boost::format(" (%d, %d, %d, -1, now(), '%s'), ") % user->m_index % gserver.m_serverno % ctId[i] % (const char*) user->m_ip );
		}

		int pos = insertSql.rfind(",");
		insertSql.erase(pos);

		cmd.BeginTrans();

		cmd.SetQuery(insertSql);
		if( !cmd.Update() )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ConnCashItemPurchaseRep(rmsg, userindex, MSG_EX_CASHITEM_ERROR_CONN, cashBalance);
			SEND_Q(rmsg, user->m_descserver);

			GAMELOG << init("CASH_PURCHASE_REP_ERROR-NotUpdateDB")
					<< mysql_error(&gserver.m_dbauth) << delim
					<< userindex << end;

			cmd.Rollback();
			return;
		}

		int serial = cmd.insertid() * 10 + userindex % 10;
		std::string updateQuery = boost::str(boost::format("UPDATE t_purchase0%d SET a_serial = %d WHERE a_serial = -1 ") % (userindex % 10) % serial);


		cmd.SetQuery(updateQuery);
		if( !cmd.Update() )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ConnCashItemPurchaseRep(rmsg, userindex, MSG_EX_CASHITEM_ERROR_CONN, cashBalance);
			SEND_Q(rmsg, user->m_descserver);

			GAMELOG << init("CASH_PURCHASE_REP_ERROR-NotUpdateDB")
					<< mysql_error(&gserver.m_dbauth) << delim
					<< userindex << end;

			cmd.Rollback();
			return;
		}

		cmd.Commit();

		if( gserver.m_billing.IsRunning() )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			BillBuyReqMsg(rmsg, userindex, user->m_name, serial, count, ctId, user->m_ip);
			gserver.m_billing.WriteToOutput(rmsg);

			user->m_descserver->WaitBillReply(serial);
			return;
		}
		else
		{
			if(user)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ConnCashItemPurchaseRep(rmsg, userindex, MSG_EX_CASHITEM_ERROR_BILL, cashBalance);
				SEND_Q(rmsg, user->m_descserver);
			}
			else
			{
				GAMELOG << init("CASH_PURCHASE_REP_ERROR-NotUser")
						<< userindex << end;
			}

			// ���� ������ ���� �ʰ� �����Ƿ�  �ѹ� : �ش� �ø����� ���� ������ ����

			std::string deleteQuery = boost::str(boost::format("DELETE FROM t_purchase0%d WHERE a_serial = %d")	% (userindex % 10) % serial);
			cmd.SetQuery(deleteQuery);


			if( !cmd.Update() )
			{
				GAMELOG << init("CASH_PURCHASE_REP_ERROR-RollBack-update fail")
						<< userindex << delim;

				for(i = 0; i < MAX_PURCHASEITEM; i++)
				{
					GAMELOG << ctId[i] << delim;
				}
				GAMELOG << end;
			}
		}

		return;
	}

	// ���� �޼����� �ش��ϴ� ���ö���
	CNetMsg::SP rmsg(new CNetMsg);
	ConnCashItemPurchaseRep(rmsg, userindex, (MSG_EX_CASHITEM_ERROR_TYPE) returnCode, cashBalance);
	SEND_Q(rmsg, user->m_descserver);
}
void CBillingClient::OnBuy(CNetMsg::SP& msg)
{
	//MSG_BILLITEM_BUY_REP,		// ����	  : returnCode(uc) gameId(uc) userId(str:32) cpId(n) itemId(n) cashBalance(int)
	unsigned char returnCode, gameId;
	int userindex;
	int cpId, cashBalance, ctId[MAX_PURCHASEITEM], i, serial;
	char count;

	RefMsg(msg) >> serial
				>> returnCode
				>> gameId
				>> userindex
				>> cpId
				>> count;

	for(i = 0; i < count && i < MAX_PURCHASEITEM; i++)
	{
		RefMsg(msg) >> ctId[i];

		// ���� ���� ������ ��ǰ �ε����� Ŀ���Ͱ� ������ �ִ� �����Ǹ� ����Ʈ�� ã�Ƽ�
		// ������ �ȸ� ������ ���� ��Ű�� ��� ���Ӽ����� �޼����� ������.
		CServer::map_limitsell_t::iterator it = gserver.m_limitSell.find(ctId[i]);
		if( it != gserver.m_limitSell.end() )
		{
			CLimitSell* limit = it->second;
			limit->IncreaseSell();
			CNetMsg::SP rmsg(new CNetMsg);
			LimitCatalogMsg(rmsg, limit);
			gserver.SendAllGameServer(rmsg);
			gserver.m_changeLimit = true;
		}
	}

	RefMsg(msg) >> cashBalance;

	CUser* user = NULL;
	for(i = 0; i < gserver.m_maxSubServer; i++)
	{
		user = gserver.m_userList[i].FindByUserIndex(userindex);
		if(user) break;
	}

	if(!user)
	{
		GAMELOG << init("CASH_PURCHASE_REP_ERROR-NotUser")
				<< userindex << end;
		return;
	}

	user->m_descserver->WaitBillReply(0);

	CDBCmd cmd(&gserver.m_dbauth);

	if( returnCode == MSG_BILLITEM_ERROR_SUCCESS)
	{
		// �ش� �ø����� ���� ���ڵ带 �����Ѵ�.
		std::string updateQuery = boost::str(boost::format("UPDATE t_purchase0%d SET a_confirm = 1 WHERE a_serial = %d ") % (userindex % 10) % serial);
		cmd.SetQuery(updateQuery);

		if( !cmd.Update() )
		{
			GAMELOG << init("Confirm Error")
					<< serial
					<< end;
		}

		//���� �α׸� �����.
		{
			GAMELOG << init("BUY_CASH_ITEM_END") << userindex << delim;
			for(i = 0; i < count && i < MAX_PURCHASEITEM; i++)
			{
				GAMELOG << ctId[i] << delim;
			}
			GAMELOG << cashBalance << end;
		}
		

		CNetMsg::SP rmsg(new CNetMsg);
		ConnCashItemPurchaseRep(rmsg, userindex, (MSG_EX_CASHITEM_ERROR_TYPE) returnCode, cashBalance);
		SEND_Q(rmsg, user->m_descserver);
		return;
	}
	else
	{
		// �ø��� ���� ���� t_purchase�� ��� �ѹ��ϰ�
		// �����ڵ忡 ���� ���� �������� �����Ѵ�

		std::string deleteQuery = boost::str(boost::format("DELETE FROM t_purchase0%d WHERE a_serial = %d ") % (userindex % 10) % serial);
		cmd.SetQuery(deleteQuery);

		if( !cmd.Update() )
		{
			GAMELOG << init("CASH_PURCHASE_REP_ERROR-RollBack-update fail")
					<< userindex << delim;

			for(i = 0; i < MAX_PURCHASEITEM; i++)
			{
				GAMELOG << ctId[i] << delim;
			}
			GAMELOG << end;
		}
		CNetMsg::SP rmsg(new CNetMsg);
		ConnCashItemPurchaseRep(rmsg, userindex, (MSG_EX_CASHITEM_ERROR_TYPE) returnCode, cashBalance);
		SEND_Q(rmsg, user->m_descserver);
		return;
	}
}

void CBillingClient::WriteToOutput(CNetMsg::SP& msg)
{
	if (msg->m_mtype == -1)
		return;

	if (service_ == NULL)
		return;

	LOG_INFO("OOO (S) : type[%d] size[%d]", msg->m_mtype, msg->m_size);

	service_->deliverForTLDBilling(msg);
}

void CBillingClient::onClose(rnSocketIOService* service)
{
	bnf::instance()->RemoveSession(service);
	service_ = NULL;

	// ������ Ÿ�̸� ����
	session_handle handle = bnf::instance()->CreateMSecTimer(2 * 1000, (void *)CBillingClientConnectTimer::instance());
}

void CBillingClient::onConnect(rnSocketIOService* service)
{
	service_ = service;

	CNetMsg::SP rmsg(new CNetMsg);
	BillConnectMsg(rmsg);
	WriteToOutput(rmsg);

	LOG_INFO("connected to billing server");
}

void CBillingClient::onConnectFail(rnSocketIOService* service)
{
	LOG_INFO("Can't connected to billing server : ip[%s] port[%s]",
			 gserver.m_config.Find("Billing Server", "IP"),
			 gserver.m_config.Find("Billing Server", "Port"));
}

void CBillingClient::connect()
{
	// ���� ������ ���� �õ�
	std::string billing_host = gserver.m_config.Find("Billing Server", "IP");
	int billing_port = atoi(gserver.m_config.Find("Billing Server", "Port"));
	bnf::instance()->CreateAsyncConnect(billing_host, billing_port, &(gserver.m_billing), CONNECT_TYPE_FOR_TLD_BILLING);
}

//////////////////////////////////////////////////////////////////////////
CBillingClientConnectTimer* CBillingClientConnectTimer::instance()
{
	static CBillingClientConnectTimer __instance;
	return &__instance;
}

void CBillingClientConnectTimer::operate(rnSocketIOService* service)
{
	// �� Ÿ�̸� ����
	bnf::instance()->RemoveSession(service);

	// ���� ������ �� ����
	gserver.m_billing.connect();
}

#endif