#include "stdhdrs.h"
#include "Server.h"
#include "doFunc.h"
#include "CmdMsg.h"
#include "DBCmd.h"

void do_AliveReq(CNetMsg& msg, CDescriptor* desc)
{
	GAMELOG << init("MSG_BILLITEM_SERVERLIVE") << end;

	// send the pingback MSG_BILLITEM_SERVERLIVE
	CNetMsg rmsg;										
	Pingback(rmsg);
	SEND_Q(rmsg, desc);
}

void do_BalanceReq(CNetMsg& msg, CDescriptor* desc)
{
	int BonusPoints = 0;

	int userindex;
	CLCString idname(48);
	int cpid;
	int balance = 0;
	
	msg.MoveFirst();
	msg >> idname;
	msg	>> cpid
		>> userindex;		


	balance = GetBalance(userindex, idname);

	CNetMsg rmsg;
	if( balance == -1)
	{
		CashBalanceRepMsg(rmsg, MSG_BILLITEM_ERROR_NOTUSER, idname, userindex, cpid, balance, BonusPoints);
		SEND_Q(rmsg, desc);

		return;
	}

	GAMELOG << init("BALANCE_REQUEST_SUCCESS")
			<< cpid << delim
			<< userindex << delim
			<< idname << delim
			<< balance << end;

	CashBalanceRepMsg(rmsg, MSG_BILLITEM_ERROR_SUCCESS, idname, userindex, cpid, balance, BonusPoints);
	SEND_Q(rmsg, desc);
}

void do_CanbuyReq(CNetMsg& msg, CDescriptor* desc)
{		
	int BonusPoints = 0;

	CLCString idname(48);
	int cpid;
	int userindex;
	CLCString IPAddress(16);
	char count = 0;
	
	int itemID[MAX_PURCHASEITEM];
	int i = 0;
	int sumPrice = 0;
	int balance = 0;
	
	//int requestCash = 0;

	msg >> idname
		>> cpid
		>> userindex
		>> IPAddress
		>> count;
	
	CNetMsg rmsg;
	if(count > MAX_PURCHASEITEM || count <= 0)
	{
		CanBuyRepMsg(rmsg, MSG_BILLITEM_ERROR_NOTITEM, userindex, cpid, idname, count, itemID, balance, BonusPoints);
		SEND_Q(rmsg, desc);
		return;
	}
	
	// Sore all ItemID's
	for(i = 0; i < count; i++)
	{
		msg >> itemID[i];
	}
			
	// Get the balance of the user
	balance = GetBalance(userindex, idname);
	if( balance < 0 )
	{
		CanBuyRepMsg(rmsg, MSG_BILLITEM_ERROR_DATABASE, userindex, cpid, idname, count, itemID, balance, BonusPoints);
		SEND_Q(rmsg, desc);
		return;
	}

	// get the total need cash
	sumPrice = GetSumPrice(count, itemID);

	if( sumPrice < 0 )
	{
		CanBuyRepMsg(rmsg, MSG_BILLITEM_ERROR_NOTITEM, userindex, cpid, idname, count, itemID, balance, BonusPoints);
		SEND_Q(rmsg, desc);
		GAMELOG << init("CANBUY_REQUEST_ERROR")
				<< cpid << delim
				<< userindex << delim
				<< idname << delim
				<< (int) MSG_BILLITEM_ERROR_NOTITEM << end;
		return;
	}
	
	if( balance < sumPrice )
	{
		// 잔액 부족
		CanBuyRepMsg(rmsg, MSG_BILLITEM_ERROR_LACKCASH, userindex, cpid, idname, count, itemID, balance, BonusPoints);
		SEND_Q(rmsg, desc);

		GAMELOG << init("CANBUY_REQUEST_ERROR")
				<< cpid << delim
				<< userindex << delim
				<< idname << delim
				<< (int) MSG_BILLITEM_ERROR_LACKCASH << end;
		return;
	}

	// balance성공, 아이템 총 가격 성공, balance >= sumPrice이면 성공
	CanBuyRepMsg(rmsg, MSG_BILLITEM_ERROR_SUCCESS, userindex, cpid, idname, count, itemID, balance-sumPrice, BonusPoints);
	SEND_Q(rmsg, desc);
}

void do_BuyReq(CNetMsg& msg, CDescriptor* desc)
{
	int BonusPoints = 0;
	CLCString idname(48);
	CLCString ip(16);
	int userindex;
	int cpID;
	int itemID[MAX_PURCHASEITEM];
	int i = 0;
	int serial;
	int sumPrice = 0;
	int balance = 0;
	char count = 0;

	serial = msg.m_serial;
	msg >> idname
		>> cpID
		>> userindex		
		>> ip
		>> count;

	// Return MSG
	CNetMsg rmsg;
	if(count > MAX_PURCHASEITEM || count <= 0)
	{
		CanBuyRepMsg(rmsg, MSG_BILLITEM_ERROR_NOTITEM, userindex, cpID, idname, count, itemID, balance, BonusPoints);
		SEND_Q(rmsg, desc);
		return;
	}
	
	for(i = 0; i < count; i++)
	{
		msg >> itemID[i];
	}
		
	// get Cash Balance
	balance = GetBalance(userindex, idname);

	if( balance < 0 )
	{
		BuyRepMsg(rmsg, MSG_BILLITEM_ERROR_DATABASE, serial, userindex, cpID, idname, count, itemID, balance, BonusPoints);
		SEND_Q(rmsg, desc);
		return;
	}

	// Get The total Price of all items
	sumPrice = GetSumPrice(count, itemID);

	if( sumPrice < 0 )
	{
		BuyRepMsg(rmsg, MSG_BILLITEM_ERROR_DATABASE, serial, userindex, cpID, idname, count, itemID, balance, BonusPoints);
		SEND_Q(rmsg, desc);

		GAMELOG << init("BUY_REQUEST_ERROR")
				<< cpID << delim
				<< userindex << delim
				<< idname << delim
				<< (int) MSG_BILLITEM_ERROR_NOTITEM << end;
		return;
	}
	
	// Check balance
	if( balance < sumPrice )
	{
		// 잔액 부족
		BuyRepMsg(rmsg, MSG_BILLITEM_ERROR_DATABASE, serial, userindex, cpID, idname, count, itemID, balance, BonusPoints);
		SEND_Q(rmsg, desc);

		GAMELOG << init("BUY_REQUEST_ERROR")
				<< cpID << delim
				<< userindex << delim
				<< idname << delim
				<< (int) MSG_BILLITEM_ERROR_LACKCASH << end;
		return;
	}

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);

    // Verify connection health and log details
    {
        unsigned int pingres = 0;
        // mysql_ping returns 0 on success
        pingres = mysql_ping(&gserver.m_dbauth);
        if (pingres != 0)
        {
            GAMELOG << init("BALANCE_DEBUG") << "MYSQL_PING_FAILED" << delim << (int)pingres << delim << mysql_error(&gserver.m_dbauth) << end;
        }
        else
        {
            GAMELOG << init("BALANCE_DEBUG") << "MYSQL_PING_OK" << delim << (const char*)mysql_get_server_info(&gserver.m_dbauth) << delim << "thread:" << (long long)mysql_thread_id(&gserver.m_dbauth) << end;
        }
    }
	cmd.BeginTrans();


	// bill_log 남기고 bill_game_item_buy 로그 남기고 bill_game_item 어쩌고 차감.
	int sumMileage;
	int errorCode = DeductBalance(&cmd, serial, userindex, ip, cpID, count, itemID, balance, sumPrice, &sumMileage);
	if( errorCode )
	{
		GAMELOG << init("BUY_REQUEST_ERROR")
				<< "UPDATE_DB" << delim
				<< cpID << delim
				<< userindex << delim
				<< idname << end;


		BuyRepMsg(rmsg, MSG_BILLITEM_ERROR_DATABASE, serial, userindex, cpID, idname, count, itemID, balance, BonusPoints);
		SEND_Q(rmsg, desc);

		return;
	}

	cmd.Commit();

	cmd.Close();

	// balance성공, 아이템 총 가격 성공, balance >= sumPrice이면 성공
	BuyRepMsg(rmsg, MSG_BILLITEM_ERROR_SUCCESS, serial, userindex, cpID, idname, count, itemID, balance-sumPrice, BonusPoints);
	SEND_Q(rmsg, desc);

	GAMELOG << init("BUY_REQUEST_SUCCESS")
				<< cpID << delim
				<< userindex << delim
				<< idname << delim
				<< balance << delim
				<< sumPrice << end;

}

void do_onlineCash(int cash)
{
 	GAMELOG << init("ADDING CASH TO ALL ONLINE PLAYERS") << cash << end;
	CLCString sql(500);
	CDBCmd cmd;
	cmd.Init(&gserver.m_dbuser);
	
	if( gserver.m_usebg_users )
		sql.Format("UPDATE %s.bg_user as t1 SET t1.cash = t1.cash + %d WHERE t1.user_code = (SELECT t_users.a_portal_index as a_index FROM t_users where t_users.a_idname = t1.user_id AND t_users.a_zone_num > -1)", gserver.m_config.Find("Auth DB", "DBName"), cash);
	else
		sql.Format("UPDATE bill_user as t1 SET t1.user_point = t1.user_point + %d WHERE t1.user_index = (SELECT t_users.a_portal_index as a_index FROM t_users where t_users.a_idname = t1.user_id AND t_users.a_zone_num > -1)", cash);

	cmd.SetQuery(sql);
	if(!cmd.Update())
	{
		GAMELOG << init("ONLINE_CASH_ERROR") << end;
	}
	cmd.BeginTrans();
	cmd.Close();
}

int DeductBalance(CDBCmd *m_billCmd,int serial, int userindex, const char* ip, int cpID, char count, int itemID[], int balance, int sumPrice, int* sumMileage)
{
	// bill_game_item_buy와 bill_game_item 업데이트 
	int cash, mileage, i;
	*sumMileage = 0;
	CLCString ctname(50+1);

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbuser);
	// bill_log
	sprintf(g_buf, " insert into bill_log (log_user_index, log_date, log_buy_serial, log_type, log_add_point, log_old_point) "
		"values (%d, NOW(), %d, %d, 0, %d ) ", userindex, serial, 2, balance);

	cmd.SetQuery(g_buf);
	if(!cmd.Update())
	{
		GAMELOG << init("DEDUCTBALANCE_ERROR_INSERT_BILL_LOG")
				<< userindex << delim
				<< cpID	<< delim
				<< balance << delim
				<< ip << delim
				<< serial << end;
		cmd.Rollback();
		return MSG_BILLITEM_ERROR_DATABASE;
	}
	cmd.BeginTrans();

	CDBCmd dataCmd;
	dataCmd.Init(&gserver.m_catalDB);
	for(i = 0; i < count && itemID[i] != -1 ; i++)
	{
		sprintf(g_buf, "select a_ctname, a_cash, a_mileage from t_catalog where a_enable = 1 and a_ctid = %d ", itemID[i]);
		dataCmd.SetQuery(g_buf);

		if( !dataCmd.Open() || !dataCmd.MoveFirst() )
		{
			GAMELOG << init("DEDUCTBALANCE_ERROR")
					<< userindex << delim
					<< cpID	<< delim
					<< balance << delim
					<< itemID[i] << end;
			cmd.Rollback();

			return MSG_BILLITEM_ERROR_NOTITEM;
		}

		if( !dataCmd.GetRec("a_ctname", ctname)
			|| !dataCmd.GetRec("a_cash", cash)
			|| !dataCmd.GetRec("a_mileage", mileage) )
		{
			GAMELOG << init("DEDUCTBALANCE_GET_ERROR")
					<< userindex << delim
					<< cpID	<< delim
					<< balance << delim
					<< itemID[i] << end;
			cmd.Rollback();

			return MSG_BILLITEM_ERROR_DATABASE;
		}

		// bill_game_item 테이블에 레코드가 있으면 업데이트하고 없으면 인서트
		sprintf(g_buf, "select gitem_index from bill_game_item where gitem_index = %d", itemID[i]);


		cmd.SetQuery(g_buf);
		if(!cmd.Open())
		{
			GAMELOG << init("DEDUCTBALANCE_ERROR_OPEN_BILL_GAME_ITEM")
					<< userindex << delim
					<< cpID	<< delim
					<< balance << delim
					<< ip << delim
					<< itemID[i]  << delim				
					<< cmd.ErrorString()  << end;
			cmd.Rollback();

			return MSG_BILLITEM_ERROR_DATABASE;
		}
		

		if( !cmd.MoveFirst() )
		{
			// insert
			sprintf(g_buf, "insert into bill_game_item (gitem_index, gitem_name, gitem_count) "
				"values "
				"(%d, \"%s\", 1) ", itemID[i], (const char*)ctname);

			cmd.SetQuery(g_buf);
			if(!cmd.Update())
			{
				GAMELOG << init("DEDUCTBALANCE_ERROR_INSERT_BILL_GAME_ITEM")
						<< userindex << delim
						<< cpID	<< delim
						<< balance << delim
						<< ip << delim
						<< itemID[i]  << delim				
					<< cmd.ErrorString()  << end;
			cmd.Rollback();

				return MSG_BILLITEM_ERROR_DATABASE;
			}
			cmd.Commit();
		}
		else
		{
			//update
			sprintf(g_buf, "update bill_game_item "
				"set gitem_count = gitem_count + 1, gitem_name = \"%s\" "
				"where gitem_index = %d", (const char*) ctname, itemID[i]);

			cmd.SetQuery(g_buf);
			if(!cmd.Update())
			{
				GAMELOG << init("DEDUCTBALANCE_ERROR_UPDATE_BILL_GAME_ITEM")
						<< userindex << delim
						<< cpID	<< delim
						<< balance << delim
						<< ip << delim
						<< itemID[i] << delim				
						<< cmd.ErrorString()  << end;
						cmd.Rollback();

				return MSG_BILLITEM_ERROR_DATABASE;
			}
		}
				
		sprintf(g_buf, "insert into bill_game_item_buy "
			" ( gbuy_index, gbuy_user_index, gbuy_user_ip, gbuy_date, gbuy_gitem_index, gbuy_gitem_point, gbuy_gitem_bonus ) "
			" values "
			" ( %d, %d, '%s', NOW(), %d, %d, %d) ", serial, userindex, ip, itemID[i], cash, mileage);


	cmd.SetQuery(g_buf);
	if(!cmd.Update())
	{
			GAMELOG << init("DEDUCTBALANCE_ERROR_INSERT_ITEM_BUY_LOG")
					<< userindex << delim
					<< cpID	<< delim
					<< balance << delim
					<< ip << delim
					<< itemID[i]				
					<< cmd.ErrorString()  << end;
					cmd.Rollback();

			return MSG_BILLITEM_ERROR_DATABASE;
		}
		
		*sumMileage += mileage;
	}

	//bill_log에 addpoint 업데이트
	sprintf(g_buf, "update bill_log set log_add_point = %d where log_buy_serial = %d ", -sumPrice+*sumMileage, serial);

	cmd.SetQuery(g_buf);
	if(!cmd.Update())
	{
		GAMELOG << init("DEDUCTBALANCE_ERROR_UPDATE_BILL_LOG")
				<< userindex << delim
				<< cpID	<< delim
				<< balance << delim
				<< ip << delim
				<< serial << end;
				
			cmd.Rollback();

		return MSG_BILLITEM_ERROR_DATABASE;
	}

	// bill_user의 포인트 차감
	if( gserver.m_usebg_users )
		sprintf(g_buf, " update bg_user set cash = %d, cashused = cashused + %d, cashtotalused = cashtotalused + %d where user_code = %d ", balance-sumPrice+*sumMileage, sumPrice, sumPrice, userindex);
	else
		sprintf(g_buf, " update bill_user set user_point = %d, user_bonus = user_bonus + %d, user_point_used = user_point_used + %d, user_point_used_total = user_point_used_total + %d where user_index = %d ", balance-sumPrice+*sumMileage, *sumMileage, sumPrice, sumPrice, userindex);

	m_billCmd->SetQuery(g_buf);
	if(!m_billCmd->Update())
	{
		GAMELOG << init("DEDUCTBALANCE_ERROR_UPDATE_BILL_USER")
				<< userindex << delim
				<< cpID	<< delim
				<< balance << delim
				<< sumPrice  << delim
				<< *sumMileage  << delim
				<< ip << delim
				<< serial << end;					
			m_billCmd->Rollback();

		return MSG_BILLITEM_ERROR_DATABASE;
	}

	GAMELOG << init("DEDUCTBALANCE_SUCCESS_UPDATE_BILL_USER")
				<< userindex << delim
				<< cpID	<< delim
				<< balance << delim
				<< sumPrice  << delim
				<< *sumMileage  << delim
				<< ip << delim
				<< serial << end;

	return MSG_BILLITEM_ERROR_SUCCESS;
}

int GetSumPrice(char count, const int itemID[])
{
	int sumPrice = 0;
	int i;
	int price = 0;

	CDBCmd dataCmd;
	dataCmd.Init(&gserver.m_catalDB);

	for(i = 0; i < count && itemID[i] != -1; i++)
	{
		sprintf(g_buf, "select a_cash from t_catalog where a_ctid = %d ", itemID[i]);
		dataCmd.SetQuery(g_buf);

		if( !dataCmd.Open() || !dataCmd.MoveFirst() )
		{
			// 사려는 아이템이 없음
			GAMELOG << init("CANNOT_FIND_CATALOG")
					<< itemID[i] << end;

			return -1;
		}
		if( !dataCmd.GetRec("a_cash", price) )
		{
			GAMELOG << init("CANNOT_FIND_CATALOG_PRICE")
					<< itemID[i] << end;
			return -1;
		}

		sumPrice += price;

		price = 0;
	}

	return sumPrice;
}

int GetBalance(int userindex, const char *idname)
{
	CLCString name(50);
	int balance = -1;

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);

    char sqlbuf[512];
    const char* authdb = gserver.m_config.Find("Auth DB", "DBName");
    if (gserver.m_usebg_users) {
        if (authdb && authdb[0])
            snprintf(sqlbuf, sizeof(sqlbuf), "SELECT user_id, cash FROM %s.bg_user WHERE user_code = %d", authdb, userindex);
        else
            snprintf(sqlbuf, sizeof(sqlbuf), "SELECT user_id, cash FROM bg_user WHERE user_code = %d", userindex);
    } else {
        if (authdb && authdb[0])
            snprintf(sqlbuf, sizeof(sqlbuf), "SELECT user_id, user_point FROM %s.bill_user WHERE user_index = %d", authdb, userindex);
        else
            snprintf(sqlbuf, sizeof(sqlbuf), "SELECT user_id, user_point FROM bill_user WHERE user_index = %d", userindex);
    }

    // Log the exact SQL we will run (use local buffer to avoid global overwrite)
    GAMELOG << init("BALANCE_DEBUG") << "SQL:" << sqlbuf << end;

    cmd.SetQuery(sqlbuf);
    if (!cmd.Open())
    {
        const char* dberr = "";
        unsigned int dberrnum = 0;
        if (&gserver.m_dbauth)
        {
            dberrnum = mysql_errno(&gserver.m_dbauth);
            dberr = mysql_error(&gserver.m_dbauth);
        }

        GAMELOG << init("BALANCE_REQUEST_ERROR")
                << "OPEN_FAILED" << delim
                << (int)userindex << delim
                << (int)dberrnum << delim
                << (dberr ? dberr : "") << delim
                << "SQL:" << g_buf << end;
        return -1;
    }

    if (!cmd.MoveFirst())
    {
        // Query succeeded but returned no rows
        GAMELOG << init("BALANCE_REQUEST_ERROR")
                << "NO_ROWS" << delim
                << (int)userindex << delim
                << "SQL:" << g_buf << end;

        // Diagnostic: check which database the connection is using and whether the row
        // is visible via the same connection.
        {
            CDBCmd tcmd;
            tcmd.Init(&gserver.m_dbauth);

            // log configured Auth DB name
            const char* authdb = gserver.m_config.Find("Auth DB", "DBName");
            GAMELOG << init("BALANCE_DEBUG") << "AUTH_DB_CONFIG:" << (authdb ? authdb : "(null)") << end;

            // Query current database for this connection
            tcmd.SetQuery("SELECT DATABASE() AS dbname");
            if (tcmd.Open() && tcmd.MoveFirst()) {
                CLCString curdb(128);
                if (tcmd.GetRec("dbname", curdb))
                    GAMELOG << init("BALANCE_DEBUG") << "CONN_DATABASE:" << curdb << end;
            }
            tcmd.Close();

            // Build qualified table reference if possible
            CLCString qualified(256);
            if (authdb && strlen(authdb) > 0)
                qualified.Format("%s.bg_user", authdb);
            else
                qualified.Format("bg_user");

            // Count rows in bg_user for this userindex using the same connection
            char tbuf[512];
            snprintf(tbuf, sizeof(tbuf), "SELECT COUNT(*) AS cnt FROM %s WHERE user_code = %d", (const char*)qualified, userindex);
            tcmd.SetQuery(tbuf);
            if (tcmd.Open() && tcmd.MoveFirst()) {
                int cnt = 0;
                if (tcmd.GetRec("cnt", cnt))
                    GAMELOG << init("BALANCE_DEBUG") << "BG_USER_COUNT:" << (int)cnt << " FOR user_code:" << (int)userindex << end;
            } else {
                GAMELOG << init("BALANCE_DEBUG") << "COUNT_QUERY_FAILED SQL:" << tbuf << " ERR:" << (tcmd.ErrorString() ? tcmd.ErrorString() : "") << end;
            }
            tcmd.Close();

            // If possible, dump the row contents
            snprintf(tbuf, sizeof(tbuf), "SELECT user_code, user_id, cash FROM %s WHERE user_code = %d", (const char*)qualified, userindex);
            tcmd.SetQuery(tbuf);
            if (tcmd.Open() && tcmd.MoveFirst()) {
                CLCString row_user_id(128);
                int row_user_code = 0;
                int row_cash = 0;
                tcmd.GetRec("user_code", row_user_code);
                tcmd.GetRec("user_id", row_user_id);
                tcmd.GetRec("cash", row_cash);
                GAMELOG << init("BALANCE_DEBUG") << "ROW:" << (int)row_user_code << delim << row_user_id << delim << (int)row_cash << end;
            } else {
                GAMELOG << init("BALANCE_DEBUG") << "ROW_QUERY_NORESULT SQL:" << tbuf << end;
            }
            tcmd.Close();
        }

        cmd.Close();
        return -1;
    }

    // Read returned fields: user id and balance field
    // Ensure we fetch the user_id into 'name' so we can verify it matches the requested idname
    if (!cmd.GetRec("user_id", name)) {
        GAMELOG << init("BALANCE_REQUEST_ERROR")
                << "GET_USERID" << delim
                << userindex << delim
                << end;
        cmd.Close();
        return -1;
    }

    if (gserver.m_usebg_users) {
        if (!cmd.GetRec("cash", balance)) {
            GAMELOG << init("BALANCE_REQUEST_ERROR") << "GET_CASH" << delim << userindex << end;
            cmd.Close();
            return -1;
        }
    }
    else {
        if (!cmd.GetRec("user_point", balance)) {
            GAMELOG << init("BALANCE_REQUEST_ERROR") << "GET_USER_POINT" << delim << userindex << end;
            cmd.Close();
            return -1;
        }
    }

    cmd.Close();

#ifdef USER_ID_CASE_SENSITIVE
    if (strcmp(name, idname) != 0)
        return -1;
#else
    if( strcmp2(name, idname) != 0 )
        return -1;
#endif // USER_ID_CASE_SENSITIVE

	return balance;
}