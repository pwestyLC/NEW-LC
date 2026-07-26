#include "stdhdrs.h"

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
#include <boost/format.hpp>

#define WISHLIST_LENGTH		(65)

MSG_CONN_ERRORCODE ReadDB(const char* name, const char* pw, int server, int subno, const char* ip, CUser** user, char playmode)
{
	// ���п��� ���̵�/�н����� �˻�
	CLCString sql(MAX_STRING_LENGTH);

#if defined(BCRYPT_USA) && !defined(CIRCLE_WINDOWS)
	CLCString buf(1024);
	buf.Format("SELECT user_code, jumin, partner_id, unix_timestamp(create_date) as creat, passwd FROM bg_user WHERE BINARY user_id='%s'",(const char*)name);
	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(buf);
	if(!cmd.Open())		return MSG_CONN_ERROR_SYSTEM;
	if(!cmd.MoveFirst()) return MSG_CONN_ERROR_NOMATCH;

	CLCString dbpassword(100);
	cmd.GetRec("passwd", dbpassword);
	std::string dbpass((const char*)dbpassword);
	std::string pass(pw);

	//int crypttype = CCheckPassword::kPlainText;
	//if		(dbpass.size() == 60)	crpyttype = CCheckPassword::kBcryptedText;
	//else if	(dbpass.size() == 32)	crpyttype = CCheckPassword::kMD5Text;

	if(!CCheckPassword::checkPass(pass, dbpass))
		return MSG_CONN_ERROR_NOMATCH;
#elif defined(RUS_BCRYPT)
		CLCString buf(1024);
		buf.Format("SELECT user_code, jumin, partner_id, unix_timestamp(create_date) as creat, passwd FROM bg_user WHERE BINARY user_id='%s'",(const char*)name);
		CDBCmd cmd;
		cmd.Init(&gserver.m_dbauth);
		cmd.SetQuery(buf);
		if(!cmd.Open())		return MSG_CONN_ERROR_SYSTEM;
		if(!cmd.MoveFirst()) return MSG_CONN_ERROR_NOMATCH;

		CLCString dbpassword(100);
		cmd.GetRec("passwd", dbpassword);
		std::string dbpass((const char*)dbpassword);
		std::string pass(pw);

		//int crypttype = CCheckPassword::kPlainText;
		//if		(dbpass.size() == 60)	crpyttype = CCheckPassword::kBcryptedText;
		//else if	(dbpass.size() == 32)	crpyttype = CCheckPassword::kMD5Text;

		if(!CCheckPassword::checkPass(pass, dbpass))
			return MSG_CONN_ERROR_NOMATCH;
#else

#ifdef LC_TWN
	sql.Format("select user_code, chk_tester from bg_user where BINARY user_id = '%s' and passwd = '%s' ", name, pw );
#elif LC_TLD
	sql.Format("select a_index, a_specialsw, a_special, a_stash_password from bg_user where a_gametype = 'LC' and a_idname = '%s' and a_passwd = '%s' ", name, pw );
#elif defined(LC_BILA)
	sql.Format("select user_code, jumin, partner_id, unix_timestamp(create_date) as creat FROM bg_user WHERE BINARY user_id='%s' AND passwd=MD5('%s')", name, pw );
#elif defined (PASSWORD_ENCRYPT_SHA256)
	char lowerid[MAX_ID_NAME_LENGTH+1];
	AnyOneArg((const char*)name, lowerid, true);
	if(!ConverToHash256((const char*)lowerid, gserver.m_salt, (const char*)pw, gserver.m_hash, sizeof(gserver.m_hash)))
	{
		GAMELOG << init("SHA256 ENCRYPT ERROR") << end;
		return MSG_CONN_ERROR_NOMATCH;
	}
	sql.Format("select user_code, jumin, partner_id, unix_timestamp(create_date) as creat FROM bg_user WHERE BINARY user_id='%s' AND passwd='%s'", name, gserver.m_hash );
#else
#ifdef EMPAS_LOGIN
#ifdef LC_KOR
#ifdef JUMIN_DB_CRYPT
	sql.Format("select t1.user_code as user_code, t1.enc_jumin1 as enc_jumin1, t1.enc_jumin3 as enc_jumin3, t1.partner_id as partner_id, unix_timestamp(t1.create_date) as creat FROM bg_user as t1 left join bg_user_active as t2 on t1.user_code = t2.active_code "
			   " WHERE t1.user_id='%s' AND ( ( t1.passwd=password('%s') and t1.partner_id != 'B1' ) or (t2.active_code = t1.user_code and t2.active_game = 'LC' and t2.active_passwd = '%s' and unix_timestamp(t2.active_time) + 600 > unix_timestamp(now()) ) ) "
			   , name, pw, pw );
#else
	sql.Format("select t1.user_code as user_code, t1.jumin as jumin, t1.partner_id as partner_id, unix_timestamp(t1.create_date) as creat FROM bg_user as t1 left join bg_user_active as t2 on t1.user_code = t2.active_code "
			   " WHERE t1.user_id='%s' AND ( ( t1.passwd=password('%s') and t1.partner_id != 'B1' ) or (t2.active_code = t1.user_code and t2.active_game = 'LC' and t2.active_passwd = '%s' and unix_timestamp(t2.active_time) + 600 > unix_timestamp(now()) ) ) "
			   , name, pw, pw );
#endif
#else
	sql.Format("select t1.user_code as user_code, t1.jumin as jumin, t1.partner_id as partner_id, unix_timestamp(t1.create_date) as creat FROM bg_user as t1 left join bg_user_active as t2 on t1.user_code = t2.active_code "
			   " WHERE t1.user_id='%s' AND ( ( t1.passwd='%s' and t1.partner_id != 'B1' ) or (t2.active_code = t1.user_code and t2.active_game = 'LC' and t2.active_passwd = '%s' and unix_timestamp(t2.active_time) + 600 > unix_timestamp(now()) ) ) "
			   , name, pw, pw );
#endif // LC_KOR
#else//#ifdef EMPAS_LOGIN
#ifdef RUS_MD5
	sql.Format("select user_code, jumin, partner_id, unix_timestamp(create_date) as creat FROM bg_user "
			   " WHERE  BINARY user_id='%s' AND BINARY passwd=MD5('%s')"
			   , name, pw );
#else
	sql.Format("SELECT user_code, jumin, partner_id, unix_timestamp(create_date) AS creat FROM bg_user "
		"WHERE LOWER(user_id) = LOWER('%s') AND passwd = MD5('%s')",
		name, pw);
#endif
#endif//#ifdef EMPAS_LOGIN
#endif
	CDBCmd cmd;

	CLCString blockSql(1000);
	blockSql.Format(" select a_index from t_ip_block where a_ip = '%s' ", ip );
	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(blockSql);
	cmd.Open();

	if(cmd.GetRecordCount() > 0 )
	{
		return MSG_CONN_ERROR_NOMATCH;
	}

	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(sql);

	if (!cmd.Open())
		return MSG_CONN_ERROR_SYSTEM;

	if (cmd.GetRecordCount() < 1 || !cmd.MoveFirst())
		return MSG_CONN_ERROR_NOMATCH;

#endif

	int portal_idx;
#ifdef LC_TLD
	char m_specialsw;
	char m_special;
	cmd.GetRec("a_index", portal_idx);
	cmd.GetRec("a_specialsw", m_specialsw);
	cmd.GetRec("a_special", m_special);
#else
	int creat_date = 1139482800;
	CLCString proSite(3);
	cmd.GetRec("creat", creat_date);
	cmd.GetRec("partner_id", proSite);

	if( proSite.Length() < 1 )
		proSite = "LC";

	cmd.GetRec("user_code", portal_idx);
#endif

#ifdef CHARDEL_CHECKID
#ifdef LC_TLD
	CLCString ident(20);
	cmd.GetRec("a_stash_password", ident);
#else//#ifdef LC_TLD
	CLCString ident(50);
#ifdef JUMIN_DB_CRYPT
	int nFirst = 0;
	cmd.GetRec("enc_jumin1", ident);
	cmd.GetRec("enc_jumin3", nFirst);
#else // JUMIN_DB_CRYPT
	cmd.GetRec("jumin", ident);
#endif // JUMIN_DB_CRYPT

	char tempBuf[50] = {0,};
	strcpy(tempBuf, ident);

	char* pId = NULL;
	pId = strtok(tempBuf, "-");
	pId = strtok(NULL, "-");

	ident = pId;
#endif//#ifdef LC_TLD
#endif//#ifdef CHARDEL_CHECKID

	// ���� �����ͺ��̽����� ã��
	// �̸����� ã��


	std::string selectQuery = "";
#if defined (LOGIN_TIME_CHECK)
	selectQuery = boost::str(boost::format(
								 "SELECT a_portal_index, a_zone_num, a_timestamp, a_enable, UNIX_TIMESTAMP(a_regi_date) AS `createtime`, (UNIX_TIMESTAMP(NOW()) - a_login_time) AS `logincheck`  FROM t_users WHERE a_idname='%s'")
							 % name);
#else
	selectQuery = boost::str(boost::format(
								 "SELECT a_portal_index, a_zone_num, a_timestamp, a_enable, UNIX_TIMESTAMP(a_regi_date) AS `createtime` FROM t_users WHERE a_idname='%s'")
							 % name);
#endif

	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(selectQuery);

	if (!cmd.Open())
		return MSG_CONN_ERROR_SYSTEM;

	bool bFirstConn = true;

	//0627
	time_t	currenttime;
	time(&currenttime);
	int regi_time = 0;
	// 050124 - bs - ���� �̸����� �˻��Ͽ� ���� �ε��� Ȯ��
	if (cmd.GetRecordCount() > 0 && cmd.MoveNext())
	{
		int oldportalindex;
		cmd.GetRec("a_portal_index", oldportalindex);

#ifdef EVENT_USER_COMEBACK
#ifdef EVENT_USER_COMEBACK_AUTO_REG_DAY
		{
			std::string selectUserQuery = boost::str(boost::format(
											  " SELECT (UNIX_TIMESTAMP(NOW()) - UNIX_TIMESTAMP(a_end_date)) AS comeday FROM t_users WHERE a_idname='%s'")
										  % name);

			CDBCmd comeUserCmd;
			comeUserCmd.Init(&gserver.m_dbauth);
			comeUserCmd.SetQuery(selectUserQuery);

			if( comeUserCmd.Open() && comeUserCmd.MoveFirst())
			{
				int comeday;
				comeUserCmd.GetRec("comeday" , comeday);
				if( comeday >= 60*60*24*EVENT_USER_COMEBACK_AUTO_REG_DAY ) // �ش� ���� �����ٸ�. DB�� �������.
				{
					int userIndex = oldportalindex;
					if( portal_idx != oldportalindex)
						userIndex = portal_idx;

					std::string insertQuery = boost::str(boost::format(
							"INSERT INTO  t_event_usercomeback(a_user_idx) VALUES (%d)") % userIndex );

					comeUserCmd.SetQuery(insertQuery);
					if( !comeUserCmd.Update() )
					{
						GAMELOG << init("USER_COMEBACK_EVENT DB INSERT FAIL" )
								<< "portal index" << delim << userIndex << end;
					}
				}
			}
		}

#endif // EVENT_USER_COMEBACK_AUTO_REG_DAY
#endif // EVENT_USER_COMEBACK
		if (oldportalindex != portal_idx)
		{
			std::string updateQuery = boost::str(boost::format(	"UPDATE t_users SET a_idname='%1%_CS%2%', a_end_date = NOW() WHERE a_portal_index = %3%") % name % (LONGLONG)time(NULL) % oldportalindex);
			cmd.SetQuery(updateQuery);
			if (!cmd.Update())
				return MSG_CONN_ERROR_NOMATCH;
			bFirstConn = true;
		}
		else
		{
			bFirstConn = false;
//0627
			cmd.GetRec("createtime", regi_time);
		}
	}

	if (bFirstConn)
	{
		// ó�� ���ӿ� ����
		// ���� ���� ���̺��� �߰�
		// INSERT INTO t_users (a_idname, a_portal_index, a_regi_date, a_end_date) VALUES ('name', portal_idx, NOW(), NOW())

		std::string insertQuery = "";
		insertQuery = boost::str(boost::format(
									 "INSERT INTO t_users (a_idname, a_portal_index, a_regi_date, a_end_date) VALUES ('%s', %d, NOW(), NOW())")
								 % name % portal_idx);

		cmd.SetQuery(insertQuery);

		if (!cmd.Update())
			return MSG_CONN_ERROR_ALREADY;

#ifdef CHARDEL_CHECKID
		*user = new CUser(portal_idx, name, server, subno, ip, ident);
#else
		*user = new CUser(portal_idx, name, server, subno, ip);
#endif

		(*user)->m_userFlag |= NOVICE;

#ifdef GMTOOL
		if(playmode == MSG_LOGIN_GM)
		{
			(*user)->m_userFlag |= IS_GM_CHAR;
		}
#endif // GMTOOL

#ifdef LC_TLD
		(*user)->m_proSite = "";
#else
		(*user)->m_proSite = proSite;
#endif

		return MSG_CONN_ERROR_SUCCESS;
	}
	else
	{
		// ������ �÷��� �� �� �ִ� ����
		int oldzone;
		if (!cmd.GetRec("a_zone_num", oldzone))
			return MSG_CONN_ERROR_SYSTEM;

// 050226 : bs : a_enable �˻�
		switch (atoi(cmd.GetRec("a_enable")))
		{
		case 0:
			return MSG_CONN_ERROR_NOMATCH;
		case 1:
			break;
			//Admin Dark Ban Account
		//case 3:
		//	return MSG_CONN_ERROR_ACCBANNED;
			////Admin Dark Ban Account
		default:
			return MSG_CONN_ERROR_BLOCKEDUSER;
		}
// --- 050226 : bs : a_enable == 0 �˻�

		if (oldzone < 0)
		{
#ifdef LOGIN_TIME_CHECK
			int logincheck;
			cmd.GetRec("logincheck", logincheck);
			if(logincheck >= 60 || logincheck < 0)
				return MSG_CONN_ERROR_NOTALLOW_LOGINSERVER;
#endif // LOGIN_TIME_CHECK

#ifdef CHARDEL_CHECKID
			*user = new CUser(portal_idx, name, server, subno, ip, ident);
#else
			*user = new CUser(portal_idx, name, server, subno, ip);
#endif

			(*user)->m_timestamp = (int)time(0);

			//0627
			if(currenttime - regi_time < 64*60*60)
				(*user)->m_userFlag |= NOVICE;

#ifdef EVENT_PCBANG_2ND
			std::string selectPCBangQueyr2 = boost::str(boost::format(
												 "SELECT a_index FROM t_pcbang_2nd WHERE a_ip=md5('%s') and a_enable=1") % ip );

			cmd.SetQuery(selectPCBangQueyr2);

			if(cmd.Open() && cmd.GetRecordCount() > 0)
			{
				(*user)->m_location = BILL_LOCATION_PCBANG;

				// �Ǿ��� �α��� ��� �����
				CDBCmd cmdPCBang;
				cmdPCBang.Init(&gserver.m_dbauth);

				std::string insertPCBangLogQuery = boost::str(boost::format(
													   "INSERT INTO t_pcbang_log VALUES (%d, '%s', %d, NOW())") %  portal_idx % ip % PCBANG_LOGIN);

				cmdPCBang.SetQuery(insertPCBangLogQuery);
				cmdPCBang.Update();
			}
#endif // EVENT_PCBANG_2ND

			std::string selectGiftQuery = boost::str(boost::format(
											  "SELECT a_index FROM t_gift0%d WHERE a_recv_user_idx = %d AND a_use_char_idx = 0 AND a_server = %d" )
										  % (portal_idx % 10) % portal_idx % gserver.m_serverno );

			cmd.SetQuery(selectGiftQuery);

			if( cmd.Open() && cmd.GetRecordCount() > 0 )
			{
				(*user)->m_userFlag |= RECV_GIFT;
			}

#ifdef LC_TLD
			if( m_specialsw )
			{
				if( m_special )
					(*user)->m_userFlag |= ADULT;
			}
			else
			{
				(*user)->m_userFlag |= ADULT;
			}
#endif

#ifdef LC_TLD
			(*user)->m_proSite = "";
#else
			(*user)->m_proSite = proSite;
#endif

#ifdef GMTOOL
			if(playmode == MSG_LOGIN_GM)
			{
				(*user)->m_userFlag |= IS_GM_CHAR;
			}
#endif // GMTOOL

			return MSG_CONN_ERROR_SUCCESS;
		}
		else
			return MSG_CONN_ERROR_ALREADY;
	}
}

MSG_CONN_ERRORCODE WriteDB(int index, int server, int subno, int zone, int playtime, const char* name, const char* ip, bool bLogin, int pcbangTime)
{
	// 0�� ���� ������ ������ �ϴ� ����
	// ���� �ٽ� ������Ʈ�� ���� ���� ���� ���� (MSG_MENU_START�� �޴� ��������)
	// UPDATE t_users SET a_end_date=NOW(), a_server_num=server, a_subnum=subnum, a_zone_num=zone, a_timestamp=timestamp WHERE a_portal_index=index
	std::string updateQuery = boost::str(boost::format(
			"UPDATE t_users SET "
			"a_end_date=NOW(), a_server_num = %d, a_subnum = %d, a_zone_num = %d, a_timestamp = a_timestamp + %d ")
										 % server % subno % zone % playtime);

	updateQuery += boost::str(boost::format(" WHERE a_portal_index = %d ") % index);

	if (bLogin)
	{
		updateQuery += " AND a_zone_num=-1";
	}

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(updateQuery);

	if (!cmd.Update())
		return MSG_CONN_ERROR_SYSTEM;

	if (cmd.GetRecordCount() < 1)
		return MSG_CONN_ERROR_ALREADY;

	if (name && *name && ip && *ip)
	{
		// INSERT INTO t_connect_log (a_idname, a_date, a_ip) VALUES ('name', NOW(), 'ip')
		std::string insertQuery = boost::str(boost::format(
				"INSERT INTO t_connect_log (a_idname, a_date, a_ip) VALUES "
				" ('%s', NOW(), '%s')" )
											 % name % ip);

		cmd.SetQuery(insertQuery);

		cmd.Update();
	}

	return MSG_CONN_ERROR_SUCCESS;
}

bool WriteDB(const char* name)
{
	// 0�� ���� ������ ������ �ϴ� ����
	// ���� �ٽ� ������Ʈ�� ���� ���� ���� ���� (MSG_MENU_START�� �޴� ��������)
	// UPDATE t_users SET a_end_date=NOW(), a_zone_num=zone WHERE a_name=name

	std::string updateQuery = boost::str(boost::format(
			"UPDATE t_users SET a_end_date = NOW(), a_zone_num = -1 WHERE a_idname = '%s'")	% name);
	; //pwesty??


	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(updateQuery);

	if (!cmd.Update())
		return false;

	return true;
}

void ConnPlayerReq(CDescriptor* d, CNetMsg::SP& msg)
{
	CNetMsg::SP rmsg(new CNetMsg);
	PlayerRepMsg(rmsg);
	SEND_Q(rmsg, d);
}

void ConnPlaying(CDescriptor* d, CNetMsg::SP& msg)
{
	unsigned char subtype;
	msg->MoveFirst();
	RefMsg(msg) >> subtype;

	CLCString id(MAX_ID_NAME_LENGTH + 1);
	unsigned char mode;
	int zone;

	RefMsg(msg) >> id >> mode >> zone;

	if (d->m_subno < 1)
	{
		GAMELOG << init("SYS_ERR", id)
				<< "From" << delim << d->m_subno << delim
				<< "No match server or subno" << end;
		return ;
	}

	CUser* user = gserver.m_userList[d->m_subno - 1].Find(id);

	if (!user)
	{
		GAMELOG << init("SYS_ERR", id)
				<< "From" << delim << d->m_subno << delim
				<< "Change playing state: Not Found User" << end;
		return ;
	}

	GAMELOG << init("CHANGE_STATE", id)
			<< "From" << delim << d->m_subno << delim
			<< ((mode == MSG_LOGIN_NEW) ? "PLAYING" : "CHANGE_SERVER")
			<< delim
			<< user->m_zone
			<< delim
			<< zone
			<< end;

	gserver.m_userList[d->m_subno - 1].m_playersPerZone[user->m_zone]--;
	gserver.m_userList[d->m_subno - 1].m_playersPerZone[zone]++;

	user->m_state = (mode == MSG_LOGIN_NEW) ? CONN_PLAYING : CONN_CHANGE_SERVER;
	user->m_zone = zone;
	user->m_checkTics = 0;
	WriteDB(user->m_index, user->m_server, user->m_subnum, user->m_zone, 0, NULL, NULL, false);

	if (user->m_state == CONN_CHANGE_SERVER)
	{
		// ���� �̵��� �Ϸ� �����ֱ� ���� ������ �ش�
		CNetMsg::SP rmsg(new CNetMsg);
		MoveServerOKMsg(rmsg, user->m_index);
		SEND_Q(rmsg, d);
	}
}

void ConnPreopenGift(CDescriptor* d, CNetMsg::SP& msg)
{
}

void ConnLevelupPoint(CDescriptor* d, CNetMsg::SP& msg)
{
}

void ConnEvent2pan4panBoxReq(CDescriptor* d, CNetMsg::SP& msg)
{
}

void ConnEvent2pan4panBoxCommit(CDescriptor* d, CNetMsg::SP& msg)
{
}

void ConnEvent2pan4panGoodsReq(CDescriptor* d, CNetMsg::SP& msg)
{
}

void ConnEvent2pan4panGoodsCommit(CDescriptor* d, CNetMsg::SP& msg)
{
}

void ConnEvent2pan4panMoneyReq(CDescriptor* d, CNetMsg::SP& msg)
{
}

void ConnRankerReq(CDescriptor* d, CNetMsg::SP& msg)
{
	int charindex;

	RefMsg(msg) >> charindex;

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbDB);

	std::string selectQuery = boost::str(boost::format(
            "SELECT a_rank_by_level FROM t_ranking_ex WHERE a_rank_by_level <= 10 AND a_char_index = %d") % charindex);

	cmd.SetQuery(selectQuery);
	if( !cmd.Open() )
	{
		//DB error
		return;
	}

	if(cmd.GetRecordCount() > 0 )
	{
		LOG_INFO("Top Ranking %d moving zone", charindex);
		// ��Ŀ��� �޼���
		CNetMsg::SP rmsg(new CNetMsg);
		RankerRepMsg(rmsg, charindex);
		SEND_Q(rmsg, d);
	}
}

#ifdef EVENT_PACKAGE_ITEM
void ConnCouponConfirm(CDescriptor* d, CNetMsg::SP& msg)
{
	const int KIND_STRIMG_SIZE = 31;
	int charindex;

	CLCString coupon(25);
	CLCString kind(KIND_STRIMG_SIZE);
	int type = -1;
	int useDate;

	RefMsg(msg) >> charindex
				>> coupon;

#ifdef LC_GAMIGO
	int useridx;
	RefMsg(msg) >> useridx;
#endif // LC_GAMIGO

	if( !coupon || !charindex)
		return;

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);
	std::string selectQuery = boost::str(boost::format(
			"SELECT a_index, UNIX_TIMESTAMP(a_use_date) AS buse, a_kind FROM t_key WHERE a_enable = 1 AND a_strkey = '%s' ") % (const char*) coupon);

	cmd.SetQuery(selectQuery);

	if( !cmd.Open() || !cmd.MoveFirst() )
	{
		// ���� ���� ���� �޼���
		CNetMsg::SP rmsg(new CNetMsg);
		CouponConfirmMsg(rmsg, charindex, MSG_EVENT_ERROR_NOT_COUPON);
#if defined (LC_GAMIGO)
		RefMsg(rmsg) << kind;
#endif
		SEND_Q(rmsg, d);
		return;
	}

	cmd.GetRec("buse", useDate);
	cmd.GetRec("a_kind", kind);
//	cmd.GetRec("a_type", type);

	if (useDate > 0)
	{
		// �̹� ����� ����
		CNetMsg::SP rmsg(new CNetMsg);
		CouponConfirmMsg(rmsg, charindex, MSG_EVENT_ERROR_ALREADY_USE_COUNPON);
#if defined (LC_GAMIGO)
		RefMsg(rmsg) << kind;
#endif
		SEND_Q(rmsg, d);
		return;
	}

	// �����̽þ�, ȫ���� ������ ����
	if( strcmp(kind, "open1") == 0)
	{
		type = 1;
	}
	else if( strcmp(kind, "event2") == 0)
	{
		type = 2;
	}
	else if( strcmp(kind, "event3") == 0)
	{
		type = 3;
	}

#if !defined(LC_GAMIGO)
	else
	{
		// ���� ���� ���� �޼���
		CNetMsg::SP rmsg(new CNetMsg);
		CouponConfirmMsg(rmsg, charindex, MSG_EVENT_ERROR_NOT_COUPON);
		SEND_Q(rmsg, d);
		return;
	}
#endif

#if defined (LC_GAMIGO)
	if( strcmp(kind, "GCO") == 0)
	{
		CDBCmd dbcmd;
		std::string select_bg_user_query = boost::str(boost::format(
											   "SELECT * FROM bg_user WHERE user_code = %d AND create_date >= '2009-07-30 00:00:00'") % useridx);

		dbcmd.Init(&gserver.m_dbauth);
		dbcmd.SetQuery(select_bg_user_query);
		if(!dbcmd.Open())
			return ;
		if(!dbcmd.MoveFirst())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			CouponConfirmMsg(rmsg, charindex, MSG_EVENT_ERROR_INSUFF_CONDITION);
			RefMsg(rmsg) << kind;
			SEND_Q(rmsg, d);
			return ;
		}

		std::string select_promo_GCO_query = boost::str(boost::format(
				"SELECT * FROM t_promo_GCO WHERE a_useridx = %d") % useridx);
		dbcmd.Init(&gserver.m_dbauth);
		dbcmd.SetQuery(select_promo_GCO_query);
		if(!dbcmd.Open())
			return ;
		if(dbcmd.MoveFirst())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			CouponConfirmMsg(rmsg, charindex, MSG_EVENT_ERROR_INSUFF_CONDITION);
			RefMsg(rmsg) << kind;
			SEND_Q(rmsg, d);
			return ;
		}
	}
	else if( strcmp(kind, "PCGames") == 0 )
	{
		CDBCmd dbcmd;

		std::string select_promo_PCGames_query = boost::str(boost::format(
					"SELECT * FROM t_promo_PCGames WHERE a_useridx = %d") % useridx);
		dbcmd.Init(&gserver.m_dbauth);
		dbcmd.SetQuery(select_promo_PCGames_query);
		if(!dbcmd.Open())
			return ;
		if(dbcmd.MoveFirst())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			CouponConfirmMsg(rmsg, charindex, MSG_EVENT_ERROR_INSUFF_CONDITION);
			RefMsg(rmsg) << kind;
			SEND_Q(rmsg, d);
			return ;
		}
	}
	else if( strcmp(kind, "CBSblau") == 0 )
	{
		int nowtime;
		static const int starttime = 1275343200;	// 2010-6-1 00:00:00
		static const int endtime = 1278107999;		// 2010-7-2 23:59:59

		CDBCmd dbcmd;
		std::string query = "SELECT UNIX_TIMESTAMP() as nowtime";
		dbcmd.Init(&gserver.m_dbauth);
		dbcmd.SetQuery(query);
		if(!dbcmd.Open() || !dbcmd.MoveFirst())
			return ;

		dbcmd.GetRec("nowtime", nowtime);
		if(nowtime < starttime || nowtime > endtime)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			CouponConfirmMsg(rmsg, charindex, MSG_EVENT_ERROR_INSUFF_CONDITION);
			RefMsg(rmsg) << kind;
			SEND_Q(rmsg, d);
			return;
		}

		std::string select_promo_CBSblau_query = boost::str(boost::format(
					"SELECT * FROM t_promo_CBSblau WHERE a_useridx = %d") % useridx);
		dbcmd.SetQuery(select_promo_CBSblau_query);
		if(!dbcmd.Open())
			return ;

		if(dbcmd.MoveFirst())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			CouponConfirmMsg(rmsg, charindex, MSG_EVENT_ERROR_INSUFF_CONDITION);
			RefMsg(rmsg) << kind;
			SEND_Q(rmsg, d);
			return ;
		}
	}
#endif // (LC_GAMIGO)

	// �´� �޼���
	CNetMsg::SP rmsg(new CNetMsg);
	CouponConfirmMsg(rmsg, charindex, MSG_EVENT_ERROR_COUPON_SUCCESS, atoi(cmd.GetRec("a_index")), type);
#if defined (LC_GAMIGO)
	RefMsg(rmsg) << kind;
#endif
	SEND_Q(rmsg, d);
}

void ConnCouponUse(CDescriptor* d, CNetMsg::SP& msg)
{
	int charindex;
	int cIndex, type;

#ifdef EVENT_PACKAGE_ITEM_DBLOG
	CLCString idname(MAX_ID_NAME_LENGTH + 1);
	CLCString nick(MAX_CHAR_NAME_LENGTH + 1);
	int serverno;
#endif

	RefMsg(msg) >> charindex
				>> cIndex
#ifdef EVENT_PACKAGE_ITEM_DBLOG
				>> type
				>> idname
				>> nick
				>> serverno;
#else
				>> type;
#endif

#if defined (LC_GAMIGO)
	int useridx;
	CLCString strKind(30);
	RefMsg(msg) >> useridx
				>> strKind;
#endif // defined (LC_GER) || defined (LC_PLD) || defined (LC_SPN)

	if( cIndex == -1 )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CouponUseMsg(rmsg, charindex, MSG_EVENT_ERROR_ALREADY_USE_COUNPON, type);

#if defined (LC_GAMIGO)
		RefMsg(rmsg) << (const char*)strKind;
#endif // LC_GER
		SEND_Q(rmsg, d);

		GAMELOG << init("COUPON_USE_INDEX_ERROR")
				<< charindex << delim
				<< cIndex << end;
		return;
	}

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);

#ifdef LC_GAMIGO
	std::string selectQuery = boost::str(boost::format(
			"SELECT * FROM t_key WHERE a_index = %d AND a_use_date = 0 ") % cIndex);

	cmd.SetQuery(selectQuery);
	if(!cmd.Open() || !cmd.MoveFirst())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CouponUseMsg(rmsg, charindex, MSG_EVENT_ERROR_ALREADY_USE_COUNPON, type);
		RefMsg(rmsg) << (const char*)strKind;
		SEND_Q(rmsg, d);

		GAMELOG << init("COUPON_DUP_USE_ERROR")
				<< charindex << delim
				<< cIndex << end;
		return ;
	}
#endif // LC_GAMIGO
	std::string updateQuery = boost::str(boost::format(
			"UPDATE t_key SET a_use_date = NOW() WHERE a_index = %d AND a_use_date = 0 ") % cIndex);

	cmd.SetQuery(updateQuery);

	if( !cmd.Update() )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CouponUseMsg(rmsg, charindex, MSG_EVENT_ERROR_ALREADY_USE_COUNPON, type);

#if defined (LC_GAMIGO)
		RefMsg(rmsg) << (const char*)strKind;
#endif // LC_GAMIGO
		SEND_Q(rmsg, d);

		GAMELOG << init("COUPON_USE_UPDATE_ERROR")
				<< charindex << delim
				<< cIndex << end;
		return;
	}

	CNetMsg::SP rmsg(new CNetMsg);
	CouponUseMsg(rmsg, charindex, MSG_EVENT_ERROR_COUPON_SUCCESS, type);

#if defined (LC_GAMIGO)
	RefMsg(rmsg) << (const char*)strKind;
#endif // LC_GAMIGO

	SEND_Q(rmsg, d);

	CLCString coupon(25);
	CLCString kind(31);

	std::string select_key_query = boost::str(boost::format(
									   "SELECT a_strkey, a_kind FROM t_key WHERE a_index = %d ") % cIndex);

	cmd.SetQuery(select_key_query);
	if( cmd.Open() && cmd.MoveFirst() )
	{
		cmd.GetRec("a_strkey", coupon);
		cmd.GetRec("a_kind", kind);

		GAMELOG << init("COUPON_USE")
				<< charindex << delim
				<< cIndex << delim
				<< coupon << delim
				<< kind << end;
	}

#ifdef LC_GAMIGO
	if(strcmp(strKind, "GCO") == 0)
	{
		std::string insert_promo_GCO_query = boost::str(boost::format(
				"INSERT INTO t_promo_GCO (`a_useridx`, `a_update_time`) VALUES (%d, NOW())") % useridx);

		cmd.SetQuery(insert_promo_GCO_query);
		cmd.Update();
	}
	else if(strcmp(strKind, "PCGames") == 0)
	{
		std::string insert_promo_PCGames_query = boost::str(boost::format(
					"INSERT INTO t_promo_PCGames (`a_useridx`, `a_update_time`) VALUES (%d, NOW())") % useridx);
		cmd.SetQuery(insert_promo_PCGames_query);
		cmd.Update();
	}
	else if(strcmp(strKind, "CBSblau") == 0)
	{
		std::string insert_promo_CBSblau_query = boost::str(boost::format(
					"INSERT INTO t_promo_CBSblau (`a_useridx`, `a_update_time`) VALUES (%d, NOW())") % useridx);

		cmd.SetQuery(insert_promo_CBSblau_query);
		cmd.Update();
	}
#endif // LC_GAMIGO

#ifdef EVENT_PACKAGE_ITEM_DBLOG
// ��� ���̺��� �α� �����
// t_key_log
// a_id : a_nick : a_serial : a_serverno : a_usetime
// �������̵� : ĳ���� �̸� : �ø���ѹ� : ��������ȣ : ���ð�
	char insert_key_log_query[MAX_STRING_LENGTH] = {0,};
	sprintf(insert_key_log_query, "INSERT INTO t_key_log VALUES ('%s', '%s', '%s', %d, now())",
			(const char *)idname, (const char *)nick, (const char *)coupon, serverno);
	cmd.SetQuery(insert_key_log_query);
	cmd.Update();
#endif
}
#endif // EVENT_PACKAGE_ITEM

void ConnSetLimit(CDescriptor* d, CNetMsg::SP& msg)
{
	int ctid, moreSell;

	RefMsg(msg) >> ctid
				>> moreSell;

	CServer::map_limitsell_t::iterator it = gserver.m_limitSell.find(ctid);
	if( it != gserver.m_limitSell.end() )
	{
		CLimitSell* limit = it->second;
		limit->moreSell(moreSell);
		CNetMsg::SP rmsg(new CNetMsg);
		LimitCatalogMsg(rmsg, limit);
		gserver.SendAllGameServer(rmsg);
		gserver.m_changeLimit = true;
	}
	else
	{
		CLimitSell* limit = new CLimitSell(ctid, -moreSell);
		gserver.m_limitSell.insert(CServer::map_limitsell_t::value_type(ctid, limit));
		CNetMsg::SP rmsg(new CNetMsg);
		LimitCatalogMsg(rmsg, limit);
		gserver.SendAllGameServer(rmsg);
		gserver.m_changeLimit = true;
	}
}

void ConnEventGomdori2007(CDescriptor* d, CNetMsg::SP& msg)
{
	unsigned char			cSubType;
	struct tm				tmCur;
	CDBCmd					cmdUser;

	RefMsg(msg) >> cSubType;

	cmdUser.Init(&gserver.m_dbauth);

	switch (cSubType)
	{
	case MSG_CONN_EVENT_GOMDORI_2007_COUNT:
		gserver.m_nEventGomdori2007StatusCurServer++;
		break;

	case MSG_CONN_EVENT_GOMDORI_2007_STATUS:
		{
			int nCharIndex = 0;
			RefMsg(msg) >> nCharIndex;
			tmCur = NOW();
			int nTimeDiff = tmCur.tm_min - gserver.m_nEventGomdori2007LastRead;
			if (nTimeDiff < 0)
				nTimeDiff += 60;
			if (nTimeDiff >= 5 || gserver.m_nEventGomdori2007LastRead < 0)
			{
				gserver.m_nEventGomdori2007LastRead = tmCur.tm_min;
				gserver.m_nEventGomdori2007Count = 0;
				if (gserver.m_nEventGomdori2007Status)
					delete [] gserver.m_nEventGomdori2007Status;
				gserver.m_nEventGomdori2007Status = NULL;

				std::string selectQuery = "SELECT * FROM t_event_gomdori_count ORDER BY a_server";

				cmdUser.SetQuery(selectQuery);
				if (cmdUser.Open())
				{
					gserver.m_nEventGomdori2007Count = cmdUser.GetRecordCount(); 
					if (gserver.m_nEventGomdori2007Count > 0)
					{
						gserver.m_nEventGomdori2007Status = new int[gserver.m_nEventGomdori2007Count];
						int i = 0;
						while (cmdUser.MoveNext())
						{
							cmdUser.GetRec("a_count", gserver.m_nEventGomdori2007Status[i]);
							i++;
						}
					}
				}
			}
			CNetMsg::SP rmsg(new CNetMsg);
			ConnEventGomdori2007StatusMsg(rmsg, nCharIndex, gserver.m_nEventGomdori2007Count, gserver.m_nEventGomdori2007Status);
			SEND_Q(rmsg, d);
		}
		break;

	default:
		return ;
	}
}

#ifdef GMTOOL
void ConnGMToolCommand( CDescriptor* d, CNetMsg::SP& msg )
{
	int gmindex;
	CLCString gmname(MAX_CHAR_NAME_LENGTH + 1);
	CLCString gmcommand(1000);

	char name[100], command[1000];

	RefMsg(msg) >> gmindex
				>> gmname
				>> gmcommand;

	memset(name, 0, 100);
	memset(command, 0, 1000);
	mysql_real_escape_string(&gserver.m_dbauth, name, gmname, strlen(gmname));
	mysql_real_escape_string(&gserver.m_dbauth, command, gmcommand, strlen(gmcommand));

	char insert_gmtool_command_query[MAX_STRING_LENGTH] = {0,};
	sprintf(insert_gmtool_command_query, "INSERT INTO t_gmtool_command (`a_gmindex`, `a_gmname`, `a_date`, `a_gmcommand`) VALUES (%d, '%s', NOW(), '%s')",
			gmindex, name, command);

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(insert_gmtool_command_query);
	cmd.Update();
}

void ConnGMToolChatMonitor( CDescriptor* d, CNetMsg::SP& msg )
{
	int charindex;
	unsigned char chattype;
	int server, sub;
	CLCString chat(1000);
	CLCString MonitorName(MAX_CHAR_NAME_LENGTH + 1);

	RefMsg(msg) >> charindex
				>> MonitorName
				>> chattype
				>> server
				>> sub
				>> chat;


	char strEscapeChat[1000];
	memset(strEscapeChat, 0, 1000);
	mysql_real_escape_string(&gserver.m_dbauth, strEscapeChat, chat, strlen(chat));

	char insert_gmtool_chatmonitor_query[MAX_STRING_LENGTH];
	memset(insert_gmtool_chatmonitor_query, 0, sizeof(char) * MAX_STRING_LENGTH);
	sprintf(insert_gmtool_chatmonitor_query, "INSERT INTO t_gmtool_chatmonitor (`a_charindex`, `a_server`, `a_subno`, `a_type`, `a_chat`, `a_date`) VALUES (%d, %d, %d, %d, '%s', NOW())",
			charindex, server, sub, chattype, strEscapeChat);

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(insert_gmtool_chatmonitor_query);
	cmd.Update();
}

void ConnGMToolChatting( CDescriptor* d, CNetMsg::SP& msg )
{
	int server, sub, gmindex;
	CLCString gmname(MAX_CHAR_NAME_LENGTH + 1), username(MAX_CHAR_NAME_LENGTH + 1);
	CLCString chat(1000);
	RefMsg(msg) >> server
				>> sub
				>> gmindex
				>> gmname
				>> username
				>> chat;


	char strEscapeGMName[MAX_CHAR_NAME_LENGTH + 1], strEscapeUserName[MAX_CHAR_NAME_LENGTH + 1];
	char strEscapeChat[1000];
	memset(strEscapeGMName, 0, MAX_CHAR_NAME_LENGTH + 1);
	memset(strEscapeUserName, 0, MAX_CHAR_NAME_LENGTH + 1);
	memset(strEscapeChat, 0, 1000);

	mysql_real_escape_string(&gserver.m_dbauth, strEscapeGMName, (const char*)gmname, gmname.Length());
	mysql_real_escape_string(&gserver.m_dbauth, strEscapeUserName, (const char*)username, username.Length());
	mysql_real_escape_string(&gserver.m_dbauth, strEscapeChat, (const char*)chat, chat.Length());

	char insert_gmtool_chatting_query[MAX_STRING_LENGTH];
	memset(insert_gmtool_chatting_query, 0, 4096);
	sprintf(insert_gmtool_chatting_query,"INSERT INTO t_gmtool_chatting (`a_server`, `a_sub`, `a_gmindex`, `a_gmname`, `a_charname`, `a_chat`, `a_date`) VALUES (%d, %d, %d, '%s', '%s', '%s', NOW())",
			server, sub, gmindex, strEscapeGMName, strEscapeUserName, strEscapeChat);

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(insert_gmtool_chatting_query);
	cmd.Update();
}
#endif // GMTOOL

void ConnEventXmas2007( CDescriptor* d, CNetMsg::SP& msg )
{
// KYD TO DO
	// ���� Ʈ�� ����Ʈ ��û
	// �ڽ��� ���� ����Ʈ ����
	//	MSG_CONN_EVENT_XMASTREE_ADDPOINT,	// REQ : (un)point,
	CNetMsg			rmsg;
	unsigned char	cSubType = 0;
	RefMsg(msg) >> cSubType ;

	switch( cSubType )
	{
	case MSG_CONN_EVENT_XMASTREE_ADDPOINT :
		{
			unsigned int unPoint, unOldPoint;
			RefMsg(msg) >> unPoint;

			unOldPoint = gserver.m_unEventXmasTreePoint;
			gserver.m_unEventXmasTreePoint += unPoint;

			// 1000 Point ���� �� ü�ο� ������ ��� & ��ü�ο� ���� ������Ʈ MSG
			int nDropCount = (int)(gserver.m_unEventXmasTreePoint/1000) - (int)(unOldPoint/1000);
			if ( nDropCount > 0 )
			{
				// Send TreePoint to AllGameServer
				CNetMsg::SP rmsg(new CNetMsg);
				ConnEventXmas2007Msg( rmsg , MSG_CONN_EVENT_XMASTREE_POINT) ;
				RefMsg(rmsg) << gserver.m_unEventXmasTreePoint;
				gserver.SendAllGameServer(rmsg);

				// ItemDrop Count Setting
				gserver.m_nEventXmasTreeNoticeTime += (nDropCount * 6);
				//  TimerToGameServer ���� ���
			}
		}
		break;
	case MSG_CONN_EVENT_XMASTREE_POINT :
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ConnEventXmas2007Msg( rmsg , MSG_CONN_EVENT_XMASTREE_POINT) ;
			RefMsg(rmsg) << gserver.m_unEventXmasTreePoint;
			SEND_Q(rmsg, d);
		}
		break;
	}
}

#ifdef LACARETTE_SYSTEM
void ConnLacaretteSystemMsg(CDescriptor* d, CNetMsg::SP& msg)
{
	unsigned char subtype;
	int userindex, charindex;

	RefMsg(msg) >> subtype
				>> userindex
				>> charindex;

	switch( subtype )
	{
	case MSG_CONN_LACARETTE_TOKEN_READY_REQ:
		{
			unsigned char errortype;
			errortype = LacaretteToken(userindex, charindex, false);
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_CONN_REP);
			RefMsg(rmsg) << (unsigned char)MSG_CONN_LACARETTE_SYSTEM
						 << (unsigned char)MSG_CONN_LACARETTE_TOKEN_READY_REP
						 << errortype
						 << userindex
						 << charindex;

			SEND_Q(rmsg, d);
		}
		break;
	case MSG_CONN_LACARETTE_TOKEN_REQ: // DB���� ��ū ���� ���� Ȯ��
		{
			unsigned char errortype;
			errortype = LacaretteToken(userindex, charindex, false);

			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_CONN_REP);
			RefMsg(rmsg) << (unsigned char)MSG_CONN_LACARETTE_SYSTEM
						 << (unsigned char)MSG_CONN_LACARETTE_TOKEN_REP
						 << errortype
						 << userindex
						 << charindex;

			SEND_Q(rmsg, d);
		}
		break;
	case MSG_CONN_LACARETTE_TOKEN_WRITE:
		{
			unsigned char errortype;
			int bAdd;
			RefMsg(msg) >> bAdd;

			if( bAdd == 1 )
			{
				errortype = LacaretteToken(userindex, charindex, true);

				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_CONN_REP);
				RefMsg(rmsg) << (unsigned char)MSG_CONN_LACARETTE_SYSTEM
							 << (unsigned char)MSG_CONN_LACARETTE_TOKEN_WRITE
							 << errortype
							 << userindex
							 << charindex;

				SEND_Q(rmsg, d);
			}
			else if( bAdd == -1)
			{
				errortype = LacaretteToken(userindex, charindex, true, false);
				if( errortype == MSG_CONN_LACARETTE_TOKEN_ERROR )
				{
					GAMELOG << init("LACARETTE TOKEN LOG UPDATE -1 ERROR") << delim << userindex << delim << charindex << end;
				}
			}
		}
		break;

	case MSG_CONN_LACARETTE_RETTE_REQ:
		{
			unsigned char errortype;
			int cosArrNum, cosIndex, tokenIndex, repeat=0;
			RefMsg(msg) >> cosArrNum >> cosIndex >> tokenIndex;

			errortype = LacaretteRepeat(userindex, charindex, repeat, false);

			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_CONN_REP);
			RefMsg(rmsg) << (unsigned char)MSG_CONN_LACARETTE_SYSTEM
						 << (unsigned char)MSG_CONN_LACARETTE_RETTE_REP
						 << errortype
						 << userindex
						 << charindex
						 << cosArrNum
						 << cosIndex
						 << tokenIndex
						 << repeat;

			SEND_Q(rmsg, d);
		}
		break;

	case MSG_CONN_LACARETTE_RETTE_WRITE:
		{
			int giveitemindex, bAdd, errortype, repeat=0;
			RefMsg(msg) >> giveitemindex >> bAdd;

			if( bAdd == 1) // Ƚ�� ����
			{
				errortype  = LacaretteRepeat(userindex, charindex, repeat, true);
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_CONN_REP);
				RefMsg(rmsg) << (unsigned char)MSG_CONN_LACARETTE_SYSTEM
							 << (unsigned char)MSG_CONN_LACARETTE_RETTE_WRITE
							 << (unsigned char)errortype
							 << userindex
							 << charindex
							 << giveitemindex
							 << repeat;

				SEND_Q(rmsg, d);
			}
			else if( bAdd == -1 ) // Ƚ�� ����
			{
				errortype = LacaretteRepeat(userindex, charindex, repeat, true, false);
				if( errortype ==MSG_CONN_LACARETTE_RETTE_ERROR )
				{
					GAMELOG << init("LACARETTE REPEAT LOG UPDATE -1 ERROR") << delim << userindex << delim << charindex << end;
				}
			}
		}
		break;

	case MSG_CONN_LACARETTE_UI_REQ:
		{
			int repeat=0;
			unsigned char errortype;
			errortype = LacaretteRepeat(userindex, charindex, repeat, false);
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_CONN_REP);
			RefMsg(rmsg) << (unsigned char)MSG_CONN_LACARETTE_SYSTEM
						 << (unsigned char)MSG_CONN_LACARETTE_UI_REP
						 << errortype
						 << userindex
						 << charindex
						 << repeat;

			SEND_Q(rmsg, d);
		}
	}
}

unsigned char LacaretteToken(int userindex, int charindex, bool bWrite, bool bAdd )
{
	CDBCmd cmd;
	std::string  select_lacarette_log_query = boost::str(boost::format("SELECT * FROM t_lacarette_log WHERE a_user_idx=%d") % userindex);

	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(select_lacarette_log_query);

	if( !cmd.Open() )
		return MSG_CONN_LACARETTE_TOKEN_ERROR;

	if( !cmd.MoveFirst() && bAdd ) // ���ٸ� ���� ���ɻ��� DB�� ��� ���ش�.
	{
		if( bWrite )
		{
			char insret_lacarette_log_sql[MAX_STRING_LENGTH] = {0,};
			sprintf(insret_lacarette_log_sql, "INSERT INTO t_lacarette_log VALUES (%d, %d, now(), 0, now())", userindex, charindex);
			cmd.SetQuery(insret_lacarette_log_sql);

			if( !cmd.Update() )
			{
				GAMELOG << init("LACARETTE TOKEN LOG INSERT ERROR") << delim << userindex << delim << charindex << end;
				return MSG_CONN_LACARETTE_TOKEN_ERROR;
			}
			GAMELOG << init("LACARETTE TOKEN LOG INSERT") << delim << userindex << delim << charindex << end;
		}
		return MSG_CONN_LACARETTE_TOKEN_ERROR_SUC;
	}

	// �ִٸ� ���� ���� ���� Ȯ��
	std::string select_lacarette_log_query1 = boost::str(boost::format("SELECT * FROM t_lacarette_log WHERE a_user_idx=%d AND a_date > (now() - interval 1 day )") % userindex);
	cmd.SetQuery(select_lacarette_log_query1);
	cmd.Open();

	if( !cmd.MoveFirst() ) // ���ٸ� ���� ���� ���� DB�� ������ش�.
	{
		if( bWrite && bAdd)
		{
			std::string update_lacarette_log_query = boost::str(boost::format("UPDATE t_lacarette_log SET a_date=now(), a_char_idx=%d WHERE a_user_idx=%d") % charindex % userindex);
			cmd.SetQuery(update_lacarette_log_query);

			if( !cmd.Update() )
			{
				GAMELOG << init("LACARETTE TOKEN LOG UPDATE ERROR") << delim << userindex << delim << charindex << end;
				return MSG_CONN_LACARETTE_TOKEN_ERROR;
			}
			GAMELOG << init("LACARETTE TOKEN LOG UPDATE") << delim << userindex << delim << charindex << end;
		}

		return MSG_CONN_LACARETTE_TOKEN_ERROR_SUC;
	}
	else // �̹� ���ݵǾ���
	{
		if( bWrite && !bAdd)
		{
			std::string update_lacarette_log_query = boost::str(boost::format("UPDATE t_lacarette_log SET a_date=(now() - interval 1 day ), a_char_idx=%d WHERE a_user_idx=%d") % charindex % userindex);
			cmd.SetQuery(update_lacarette_log_query);

			if( !cmd.Update() )
			{
				GAMELOG << init("LACARETTE TOKEN LOG UPDATE -1 ERROR") << delim << userindex << delim << charindex << end;
				return MSG_CONN_LACARETTE_TOKEN_ERROR;
			}
			GAMELOG << init("LACARETTE TOKEN LOG UPDATE -1") << delim << userindex << delim << charindex << end;
			return MSG_CONN_LACARETTE_RETTE_ERROR_SUC;
		}

		return MSG_CONN_LACARETTE_TOKEN_ERROR_ALREADY;
	}
}

unsigned char LacaretteRepeat(int userindex, int charindex, int &repeat, bool bWrite, bool bAdd )
{
	CDBCmd cmd;
	std::string select_lacarette_log_query = boost::str(boost::format("SELECT * FROM t_lacarette_log WHERE a_user_idx=%d") % userindex);

	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(select_lacarette_log_query);

	if( !cmd.Open() )
		return MSG_CONN_LACARETTE_RETTE_ERROR;

	if( !cmd.MoveFirst() ) // ���ٸ� ���� ���ɻ��� DB�� ��� ���ش�.
	{
		if( bWrite && bAdd )
		{
			// ���� ���� ����� ���� ���̹Ƿ� a_date�� �� ���ڷ� ���ش�. ��ū�� ���� ���� �� �ֵ���
			std::string insert_lacarette_log_query = boost::str(boost::format("INSERT INTO t_lacarette_log VALUES (%d, %d, (now() - interval 1 day ), 1, now())") % userindex % charindex);
			cmd.SetQuery(insert_lacarette_log_query);

			if( !cmd.Update() )
			{
				GAMELOG << init("LACARETTE REPEAT LOG INSERT ERROR") << delim << userindex << delim << charindex << end;
				return MSG_CONN_LACARETTE_RETTE_ERROR;
			}
			GAMELOG << init("LACARETTE INSERT") << delim << userindex << delim << delim << charindex << end;
		}
		return MSG_CONN_LACARETTE_RETTE_ERROR_SUC;
	}

	cmd.GetRec("a_repeat",		repeat);

	std::string selete_lacarette_log_query = boost::str(boost::format("SELECT * FROM t_lacarette_log WHERE a_user_idx=%d AND a_repeat_date > (now() - interval 1 day )") % userindex);
	cmd.SetQuery(selete_lacarette_log_query);
	cmd.Open();

	if( cmd.MoveFirst() )
	{
		if( bWrite )
		{
			std::string update_lacarette_log_query = "";
			if( bAdd )
			{
				update_lacarette_log_query = boost::str(boost::format("UPDATE t_lacarette_log SET a_repeat=%d, a_repeat_date=now() WHERE a_user_idx=%d") % (repeat+1) % userindex);
			}
			else
			{
				update_lacarette_log_query = boost::str(boost::format("UPDATE t_lacarette_log SET a_repeat=%d, a_repeat_date=now() WHERE a_user_idx=%d") % (repeat-1) % userindex);
			}
			cmd.SetQuery(update_lacarette_log_query);

			if( !cmd.Update() )
			{
				if( bAdd)
					GAMELOG << init("LACARETTE REPEAT LOG UPDATE +1 ERROR") << delim << userindex << delim << charindex << end;
				else
					GAMELOG << init("LACARETTE REPEAT LOG UPDATE -1 ERROR") << delim << userindex << delim << charindex << end;

				return MSG_CONN_LACARETTE_RETTE_ERROR;
			}
			if( bAdd )
				repeat++;
			else
				repeat--;

			GAMELOG << init("LACARETTE REPEAT UPDATE") << delim << userindex << delim << delim << charindex << delim << repeat << end;
		}
		return MSG_CONN_LACARETTE_RETTE_ERROR_SUC;
	}
	else // ��¥�� �Ϸ� ������
	{
		if( bWrite && bAdd )
		{
			std::string update_lacarette_log_query = boost::str(boost::format("UPDATE t_lacarette_log SET a_repeat=1, a_repeat_date=now() WHERE a_user_idx=%d") % userindex);
			cmd.SetQuery(update_lacarette_log_query);

			if( !cmd.Update() )
			{
				GAMELOG << init("LACARETTE REPEAT LOG UPDATE +1 ERROR") << delim << userindex << delim << charindex << end;
				return MSG_CONN_LACARETTE_RETTE_ERROR;
			}
			repeat = 1;
			GAMELOG << init("LACARETTE REPEAT INIT 1") << delim << userindex << delim << delim << charindex << end;
		}
		repeat = 0;
		return MSG_CONN_LACARETTE_RETTE_ERROR_SUC;
	}
}
#endif // #ifdef LACARETTE_SYSTEM

#ifdef DEV_EVENT_PROMOTION2
void ConnEventPromotion2(CDescriptor *d, CNetMsg::SP& msg)
{
	unsigned char subType;
	RefMsg(msg) >> subType;
	switch( subType )
	{
	case MSG_CONN_PROMOTION2_COUPON_USE_REQ:
		EventPromotion2CouponUseReq(d, msg);
		break;
	case MSG_CONN_PROMOTION2_COUPON_ITEM_REQ:
		EventPromotion2CouponItemReq(d, msg);
	default:
		break;
	}
}

void EventPromotion2CouponUseReq(CDescriptor * d, CNetMsg::SP& msg)
{
	int userIndex, charIndex, kind, keyIndex;
	kind = -1;
	keyIndex = -1;
	int errorType = (int)MSG_CONN_PROMOTION2_REP_ERROR_SUC;
	CLCString coupon(25);

	RefMsg(msg) >> userIndex
				>> charIndex
				>> coupon;

	CDBCmd cmd;
	std::string select_promotion2_key_query = boost::str(boost::format("SELECT * FROM t_promotion2_key WHERE a_strKey='%s' ") % (const char*)coupon);

	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(select_promotion2_key_query);

	if( !cmd.Open() )
	{
		errorType = (int)MSG_CONN_PROMOTION2_REP_ERROR_FAIL;
	}
	else
	{
		if( !cmd.MoveFirst() )
		{
			errorType = (int)MSG_CONN_PROMOTION2_REP_ERROR_KEY;
		}
		else
		{
			int enable;
			int regUserIndex;
			cmd.GetRec("a_index", keyIndex );
			cmd.GetRec("a_user_idx", regUserIndex);
			cmd.GetRec("a_kind", kind);
			cmd.GetRec("a_enable", enable);

			if( enable == 0 )
			{
				errorType = (int)MSG_CONN_PROMOTION2_REP_ERROR_USED;
			}
			else if( userIndex != regUserIndex )
			{
				errorType = (int)MSG_CONN_PROMOTION2_REP_ERROR_USER;
			}
			else
			{
				std::string select_promotion2_key_query1 = boost::str(boost::format("SELECT * FROM t_promotion2_key WHERE a_index=%d AND a_use_date >= now() AND a_enable=1") % keyIndex);
				cmd.SetQuery(select_promotion2_key_query1);
				if( !cmd.Open() || !cmd.MoveFirst() )
				{
					// ��� �Ⱓ �� ������.
					errorType = (int)MSG_CONN_PROMOTION2_REP_ERROR_DATE;
				}
			}
		}
	}

	CNetMsg::SP rmsg(new CNetMsg);
	ConnPromotion2RepErrorMsg(rmsg, charIndex, errorType  );
	if( errorType == (int)MSG_CONN_PROMOTION2_REP_ERROR_SUC )
	{
		RefMsg(rmsg) << kind << keyIndex;
	}
	SEND_Q(rmsg, d);

	GAMELOG << init("EVENT_PROMOTION2")
			<< userIndex << delim
			<< charIndex << delim
			<< (const char*)coupon << delim
			<< kind << delim
			<< "errorType" << delim << errorType
			<< end;
}

void EventPromotion2CouponItemReq(CDescriptor * d, CNetMsg::SP& msg)
{
	int userIndex, charIndex, keyIndex;
	RefMsg(msg) >> userIndex >> charIndex >> keyIndex;
	std::string update_promotion2_key_query = boost::str(boost::format("UPDATE t_promotion2_key SET a_enable=0, a_use_char_idx=%d, a_use_date=now() WHERE a_index=%d AND a_user_idx=%d") % charIndex % keyIndex % userIndex);

	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(update_promotion2_key_query);

	if( !cmd.Update() )
	{
		GAMELOG << init("EVENT_PROMOTION2 COUPON DISABLE FAIL")
				<< userIndex << delim << charIndex << delim << keyIndex << end;
	}
	else
	{
		GAMELOG << init("EVENT_PROMOTION2 COUPON DISABLE SUC")
				<< userIndex << delim << charIndex << delim << keyIndex << end;
	}
}
#endif // #ifdef DEV_EVENT_PROMOTION2

void ConnWishListMsg(CDescriptor* d, CNetMsg::SP& msg)
{
	unsigned char command;
	int user_index;
	int char_index;

	int idx = 0;
	int count = 0;
	int ctid[8];
	memset(ctid, 0, sizeof(int)*8);
	CDBCmd cmd;
	CLCString ctids(WISHLIST_LENGTH);
	int i;
	const char* arg;
	int id = 0;

	RefMsg(msg) >> command
				>> user_index
				>> char_index;

	cmd.Init(&gserver.m_dbauth);
	std::string select_wishlist_query= "";

	switch(command)
	{

	case MSG_WISHLIST_TYPE_LIST_REQ:
		{
			select_wishlist_query = boost::str(boost::format("SELECT * FROM t_wishlist WHERE a_userindex = %d") % user_index);

			cmd.SetQuery(select_wishlist_query);

			if(!cmd.Open() || !cmd.MoveFirst() || !cmd.GetRec("a_ctids", ctids))
			{
				// ���ٰ� �޼��� ������
				CNetMsg::SP rmsg(new CNetMsg);
				ConnWishlistRep(rmsg, count, ctid, user_index, char_index);
				SEND_Q(rmsg, d);
			}
			else
			{
				// ������ ����. ��ū¥����...��Ʈ���� ctids(str)�� ����...
				arg = ctids;
				for(i = 0; i < 8; i++)
				{
					if(!arg || !(*arg) || i > 7)
					{
						break;
					}
					char tempBuf[100] = {0,};
					arg = AnyOneArg(arg, tempBuf, true);
					ctid[i] = atoi(tempBuf);
					count++;
				}
				CNetMsg::SP rmsg(new CNetMsg);
				ConnWishlistRep(rmsg, count, ctid, user_index, char_index);
				SEND_Q(rmsg, d);
			}
		}
		break;
	case MSG_WISHLIST_TYPE_SAVE_REQ:
		{
			RefMsg(msg) >> id;
			select_wishlist_query = boost::str(boost::format("SELECT * FROM t_wishlist WHERE a_userindex = %d") % user_index);
			cmd.SetQuery(select_wishlist_query);

			if(!cmd.Open())
			{
				// �ý��� ����
				CNetMsg::SP rmsg(new CNetMsg);
				ConnWishlistSaveRep(rmsg, user_index, char_index, 2, id);
				SEND_Q(rmsg, d);
			}
			else if(!cmd.MoveFirst())
			{
				CNetMsg::SP rmsg(new CNetMsg);
				// ���̺� ���� ���� �ٵ� ���� ����
				// �׷��� ���� ��Ʈ������ �ٲ㼭 ����~���� INSERT
				std::string insert_wishlist_query = boost::str(boost::format("INSERT INTO t_wishlist(a_userindex, a_ctids) VALUES (%d, '%d')") % user_index % id);
				cmd.SetQuery(insert_wishlist_query);
				if(!cmd.Update())
				{
					// ������Ʈ ����
					ConnWishlistSaveRep(rmsg, user_index, char_index, 2, id);
				}
				else
				{
					// ����
					ConnWishlistSaveRep(rmsg, user_index, char_index, 0, id);
				}
				SEND_Q(rmsg, d);
			}
			else
			{
				CNetMsg::SP rmsg(new CNetMsg);
				// ������ ����. ���� �����ؼ� UPDATE �ϱ�
				if(!cmd.GetRec("a_ctids", ctids))
				{
					ConnWishlistSaveRep(rmsg, user_index, char_index, 2, id);
				}
				else
				{
					arg = ctids;
					char tempBuf[100] = {0,};
					for(i = 0; i < 8; i++)
					{
						if(!arg || !(*arg))
						{
							break;
						}

						arg = AnyOneArg(arg, tempBuf, true);
						ctid[i] = atoi(tempBuf);
						count++;
					}
					if(count >= 8)
					{
						ConnWishlistSaveRep(rmsg, user_index, char_index, 1, id);
					}
					else if(count < 8)
					{
						std::string update_wishlist_query = "UPDATE t_wishlist SET a_ctids = '";
						ctid[count] = id;

						for (i = 0; i < 8; i++)
						{
							if(ctid[idx] != 0)
							{
								update_wishlist_query += boost::str(boost::format(" %d") % ctid[idx]);
								idx++;
							}
						}
						update_wishlist_query += boost::str(boost::format("' WHERE a_userindex = %d") % user_index);

						cmd.SetQuery(update_wishlist_query);
						if(!cmd.Update())
							ConnWishlistSaveRep(rmsg, user_index, char_index, 2, id);
						else
							ConnWishlistSaveRep(rmsg, user_index, char_index, 0, id);
					}
				}
				SEND_Q(rmsg, d);
			}
		}
		break;
	case MSG_WISHLIST_TYPE_DEL_REQ:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			RefMsg(msg) >> id;

			select_wishlist_query = boost::str(boost::format("SELECT * FROM t_wishlist WHERE a_userindex = %d") % user_index);
			cmd.SetQuery(select_wishlist_query);
			if(!cmd.Open())
			{
				// �ý��� ���� void ConnWishListDelRep(CNetMsg::SP& msg, int user_index, int char_index, unsigned char ErrorCode, int ctid)
				ConnWishlistDelRep(rmsg, user_index, char_index, 2, id);
			}
			else if(!cmd.MoveFirst())	// ������ ����. �� ����� ����
			{
				ConnWishlistDelRep(rmsg, user_index, char_index, 1, id);
			}
			else						// ������ ã���� GetRec �ؼ� ������û ���� id�� �ؽ�Ʈ�� �ִ��� �˻��� �Ѵ�
			{
				if(!cmd.GetRec("a_ctids", ctids))
				{
					ConnWishlistDelRep(rmsg, user_index, char_index, 2, id);
				}
				else
				{
					arg = ctids;
					for(i = 0; i < 8; i++)
					{
						char tmpBuf[1024] = {0,};

						if(!arg || !(*arg))
						{
							break;
						}
						arg = AnyOneArg(arg, tmpBuf, true);
						if(id == atoi(tmpBuf))
						{
							if(!arg || !(*arg))
							{
								break;
							}
							arg = AnyOneArg(arg, tmpBuf, true); // ã���� �ѹ��� ����
						}
						ctid[i] = atoi(tmpBuf);

						count++;
					} // ������� �� ã�Ұ�, ã�°� ������ ������.

					if(count == 0)	// ã�Ұ�..������..���� �����Ͱ� ������ ����
					{
						std::string delete_wishlist_query = boost::str(boost::format("DELETE FROM t_wishlist WHERE a_userindex = %d") % user_index);
						cmd.SetQuery(delete_wishlist_query);
						if(!cmd.Update())
						{
							ConnWishlistDelRep(rmsg, user_index, char_index, 2, id);
						}
						else
						{
							ConnWishlistDelRep(rmsg, user_index, char_index, 0, id);
						}
					}
					else
					{
						std::string update_wishlist_query = "UPDATE t_wishlist SET a_ctids = '";
						for(i = 0; i < 8; i++)
						{
							if(ctid[idx] != 0)
							{
								update_wishlist_query += boost::str(boost::format(" %d") % ctid[idx]);
								idx++;
							}
						}
						update_wishlist_query += boost::str(boost::format("' WHERE a_userindex = %d") % user_index);

						cmd.SetQuery(update_wishlist_query);
						if(!cmd.Update())
							ConnWishlistDelRep(rmsg, user_index, char_index, 2, id);//ConnWishlistSaveRep(rmsg, user_index, char_index, 2, id);
						else
							ConnWishlistDelRep(rmsg, user_index, char_index, 0, id);//ConnWishlistSaveRep(rmsg, user_index, char_index, 0, id);
					}
				}
			}

			SEND_Q(rmsg, d);
		}
		break;
	default:
		break;
	}
}

#ifdef EVENT_USER_COMEBACK
void ConnEventUserComeback(CDescriptor* d, CNetMsg::SP& msg)
{
	int userindex;
	int charindex;

#ifdef NPC_CHECK
	int npcindex;
	RefMsg(msg) >> npcindex
				>> userindex
				>> charindex;
#else
	RefMsg(msg) >> userindex
				>> charindex;
#endif

	CDBCmd cmd;
	std::string select_event_usercomeback_query = boost::str(boost::format("SELECT * FROM t_event_usercomeback WHERE a_user_idx=%d") % userindex);

	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(select_event_usercomeback_query);

	if( !cmd.Open() || !cmd.MoveFirst() ) // ���� ��� ����.
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnEventUserComebackRepMsg( rmsg, (char)MSG_EVENT_USER_COMEBACK_ERROR_NOT_USER , userindex, charindex );
		SEND_Q(rmsg, d);
		return;
	}

	int dbcharidx;
	cmd.GetRec("a_char_idx", dbcharidx);

	if( dbcharidx > 0) // �̹� �޾ҳ�
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnEventUserComebackRepMsg( rmsg, (char)MSG_EVENT_USER_COMEBACK_ERROR_NO_MORE , userindex, charindex );
		SEND_Q(rmsg, d);
		return;
	}

#ifdef EVENT_USER_COMEBACK_AUTO_REG_DAY
	std::string delete_event_usercomeback_query = boost::str(boost::format("DELETE FROM t_event_usercomeback WHERE a_user_idx=%d") % userindex);

	cmd.SetQuery(delete_event_usercomeback_query);

	if( !cmd.Update() ) // DB ���� ����
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnEventUserComebackRepMsg( rmsg, (char)MSG_EVENT_USER_COMEBACK_ERROR_NOT_USER , userindex, charindex );
		SEND_Q(rmsg, d);

		GAMELOG << init("EVENT_USER_COMEBACK : DB DELETE FAIL")
				<< "userIDX" << delim << userindex << delim
				<< "ServerNum" << delim << gserver.m_serverno << delim
				<< "charIDX" << delim << charindex << end;
		return;
	}
	else
	{
		// DB �α׸� ������ ������ �α׷ζ� �����.
		GAMELOG << init("EVENT_USER_COMEBACK : ITEM GIVE SUC")
				<< "userIDX" << delim << userindex << delim
				<< "ServerNum" << delim << gserver.m_serverno << delim
				<< "charIDX" << delim << charindex << end;
	}
#else
	std::string update_event_usercomeback_query = boost::str(boost::format("UPDATE t_event_usercomeback SET a_server_num=%d, a_char_idx=%d, a_gift_date=NOW() WHERE a_user_idx=%d") % gserver.m_serverno % charindex % userindex);

	cmd.SetQuery(update_event_usercomeback_query);

	if( !cmd.Update() ) // DB ������Ʈ ����
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnEventUserComebackRepMsg( rmsg, (char)MSG_EVENT_USER_COMEBACK_ERROR_NOT_USER , userindex, charindex );
		SEND_Q(rmsg, d);

		GAMELOG << init("EVENT_USER_COMEBACK : DB UPDATE FAIL")
				<< userindex << delim << charindex << end;
		return;
	}
#endif

	CNetMsg::SP rmsg(new CNetMsg);
	ConnEventUserComebackRepMsg( rmsg, (char)MSG_EVENT_USER_COMEBACK_ERROR_SUC , userindex, charindex );
	SEND_Q(rmsg, d);
}

#endif

#ifdef EVENT_EUR2_PROMOTION
void ConnEventEUR2Promotion(CDescriptor* d, CNetMsg::SP& msg)
{
	int charindex = 0;
	int userindex = 0;
	int record_val = 0;
	CLCString key(21);
	CLCString sql(1024);
	unsigned char bInvenSpace = 0;
	unsigned char bWeight = 0;

	RefMsg(msg) >> charindex >> userindex >> key >> bInvenSpace >> bWeight;

	// 1. key������ record�˻� ������ Invalid Key
	sql.Format("SELECT * FROM t_eur2_promotion WHERE a_key = '%s'", (const char*)key);
	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);
	cmd.SetQuery(sql);
	if(!cmd.Open())
	{
		GAMELOG << init("EUR2 PROMOTION TABLE OPEN ERROR(t_eur2_promotion)") << end;
		return ;
	}
	if(!cmd.MoveFirst())
	{
		GAMELOG << init("EUR2 PROMOTION ERROR") << "KEY IS INVALID" << delim << "User Index" << delim << userindex << delim
				<< "Char Index" << delim << charindex << delim
				<< "Key"		 << delim << key << end;
		// �Է��� ���� DB�� ����.
		CNetMsg::SP rmsg(new CNetMsg);
		ConnEUR2PromotionRepMsg(rmsg, MSG_EVENT_EUR2_PROMOTION_WRONG_KEY, charindex);
		SEND_Q(rmsg, d);
		return ;
	}
	// 2. record�� ã�Ҵµ� UserIndex Field�� ���� ������, �������. Invalid Key
	cmd.GetRec("a_user_index", record_val);
	if(record_val > 0)
	{
		// �̹� �������.
		CNetMsg::SP rmsg(new CNetMsg);
		ConnEUR2PromotionRepMsg(rmsg, MSG_EVENT_EUR2_PROMOTION_ALREADY_USED, charindex);
		SEND_Q(rmsg, d);
		return ;
	}
	// 3. UserIndex �˻� ���� �޾���.
	sql.Format("SELECT * FROM t_eur2_promotion WHERE a_user_index = %d", userindex);
	cmd.SetQuery(sql);
	if(!cmd.Open())
	{
		GAMELOG << init("EUR2 PROMOTION TABLE OPEN ERROR(t_eur2_promotion)") << end;
		return ;
	}
	if(cmd.MoveFirst())
	{
		// �����Ͱ� �ִ�!!! �������� ���� �ȵ�!!!
		CNetMsg::SP rmsg(new CNetMsg);
		ConnEUR2PromotionRepMsg(rmsg, MSG_EVENT_EUR2_PROMOTION_CANT_USE_USER, charindex);
		SEND_Q(rmsg, d);
		return ;
	}
	// 4. bInvenSpace == 0 �̸� inven���� ���� ���Ұ�
	if(bInvenSpace == 0)
	{
		// �κ����� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ConnEUR2PromotionRepMsg(rmsg, MSG_EVENT_EUR2_PROMOTION_LACK_INVENTORY, charindex);
		SEND_Q(rmsg, d);
		return ;
	}
	// 5. ���ſ�!!!!
	if(bWeight == 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnEUR2PromotionRepMsg(rmsg, MSG_EVENT_EUR2_PROMOTION_HEAVY_WEIGHT, charindex);
		SEND_Q(rmsg, d);
		return ;
	}
	// 6. key�� ����� �� �ִ� key�̰� �ƹ� ������ ������� �ʾ�����...userindex field, charindex field, use date������Ʈ
	sql.Format("UPDATE t_eur2_promotion SET a_user_index = %d, a_char_index = %d, a_use_date = NOW() WHERE a_key = '%s'", userindex, charindex, (const char*)key);
	cmd.SetQuery(sql);
	if(!cmd.Update())
	{
		GAMELOG << init("UPDATE FAIL") << "User Index" << delim << userindex << delim
				<< "Char Index" << delim << charindex << delim
				<< "Key"		 << delim << key << end;
		// UPDATE FAIL �޽��� �߼�. ���ȵ�.
		CNetMsg::SP rmsg(new CNetMsg);
		ConnEUR2PromotionRepMsg(rmsg, MSG_EVENT_EUR2_PROMOTION_SYS_ERROR_NOT_USED, charindex);
		SEND_Q(rmsg, d);
		return ;
	}
	else
	{
		GAMELOG << init("EUR2 PROMOTION UPDATE SUCCESS")
				<< "User Index" << delim << userindex << delim
				<< "Char Index" << delim << charindex << delim
				<< "Key"		<< delim << key << end;
		//�����޽��� �߼�
		CNetMsg::SP rmsg(new CNetMsg);
		ConnEUR2PromotionRepMsg(rmsg, MSG_EVENT_EUR2_PROMOTION_SUCCESS, charindex);
		SEND_Q(rmsg, d);
		return ;
	}
}
#endif

void ConnEventTableInit(CDescriptor* d, CNetMsg::SP& msg)
{
	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);
	int eventIndex;
	RefMsg(msg) >> eventIndex;
	std::string delete_query = "";
	switch(eventIndex)
	{
	case A_EVENT_BEAR_DOLL:
		delete_query = "DELETE FROM t_event_gomdori_count";
		cmd.SetQuery(delete_query);
		if(!cmd.Update())
		{
			GAMELOG << init("DB ERROR") << delete_query.c_str() << end;
		}
		break;
	case A_EVENT_XMAS:
		delete_query = "DELETE FROM t_event_xmastree_point";
		cmd.SetQuery(delete_query);
		if(!cmd.Update())
		{
			GAMELOG << init("DB ERROR") << delete_query.c_str() << end;
		}
		else
			gserver.m_unEventXmasTreePoint = 0;
		break;
	default:
		break;
	}
}
//
