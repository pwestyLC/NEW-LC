#include "stdhdrs.h"

#include "../ShareLib/bnf.h"
#include "Log.h"
#include "Descriptor.h"
#include "Server.h"
#include "CmdMsg.h"
#include "../ShareLib/DBCmd.h"
#include "Utils.h"
#include "IPCheck.h"
#include "MessengerInLogin.h"
#include "../ShareLib/packetType/ptype_old_login.h"
#ifdef IPVERIFY
#include <curl/curl.h>
#endif
#ifdef PASSWORD_ENCRYPT_SHA256
#include "LCSha256.h"
#endif // PASSWORD_ENCRYPT_SHA256
#if defined(BCRYPT_USA) && !defined (CIRCLE_WINDOWS)
#include "../ShareLib/CheckPassword.h"
#elif defined RUS_BCRYPT
#include "../ShareLib/CheckPassword.h"
#endif
#ifdef LOCAL_LOGIN_LOG
void OnLoginLocalLog(int usercode, const char* idname, const char* host, const char* nation);
#endif

#define RECONNECT_TIME_TO_CONNECTOR_SERVER		( 5 * 1000)

//////////////////////////////////////////////////////////////////////////

void CDescriptorReconnectTimer::operate( rnSocketIOService* service )
{
	// �ڽ��� Ÿ�̸� ����
	bnf::instance()->RemoveSession(service);

	// �� ���� �õ�
	desc_->Connect();
}

//////////////////////////////////////////////////////////////////////////

CDescriptor::CDescriptor(rnSocketIOService* service, int client_type)
	: service_(service)
	, m_idname(MAX_ID_NAME_LENGTH + 1)
	, m_passwd(MAX_PWD_LENGTH + 1)
	, reconnect_timer_(this)
{
	client_type_ = client_type;

	m_hardcore_flag = 0;
	m_serverNo = 0;
	m_nMaxServer = 0;

	m_playerNum = NULL;
	m_serverSubNo = NULL;
	m_ipAddr = NULL;
	m_portNumber = NULL;

	m_bclosed	= false;

	m_pPrev = NULL;
	m_pNext = NULL;
}

CDescriptor::~CDescriptor()
{
	delete [] m_playerNum;
	delete [] m_serverSubNo;
	delete [] m_ipAddr;
	delete [] m_portNumber;
}

void CDescriptor::WriteToOutput(CNetMsg::SP& msg)
{
	if (msg->m_mtype == MSG_UNKNOWN)
		return ;

	if (service_ == NULL)
		return;

	service_->deliver(msg);
}
void LogHexDump(const void* data, size_t size, const char* tag = "HexDump") {
	const unsigned char* buf = static_cast<const unsigned char*>(data);
	char line[128];

	for (size_t i = 0; i < size; i += 16) {
		char* ptr = line;

		// Offset
		ptr += sprintf(ptr, "%08X  ", (unsigned int)i);

		// Hex part
		for (size_t j = 0; j < 16; ++j) {
			if (i + j < size)
				ptr += sprintf(ptr, "%02X ", buf[i + j]);
			else
				ptr += sprintf(ptr, "   ");
		}

		ptr += sprintf(ptr, " ");

		// ASCII part
		for (size_t j = 0; j < 16; ++j) {
			if (i + j < size) {
				unsigned char c = buf[i + j];
				*ptr++ = (c >= 32 && c <= 126) ? c : '.';
			}
			else {
				*ptr++ = ' ';
			}
		}

		*ptr = '\0';

		// Output the line using your logging function
		LOG_INFO("[%s] %s", tag, line);
	}
}
#ifdef IPVERIFY
static std::string UrlEncode(const char* s)
{
	if (!s) return "";
	CURL* c = curl_easy_init();
	if (!c) return "";

	char* esc = curl_easy_escape(c, s, 0);
	std::string out = esc ? esc : "";
	if (esc) curl_free(esc);
	curl_easy_cleanup(c);
	return out;
}

static bool IsRecentIPTrusted(CDBCmd& dbAuth, const char* idname, const char* currentIp)
{
	CLCString q(512);
	// CHANGE a_index to your real ordering column (a_time, a_regdate, etc.)
	q.Format("SELECT a_ip FROM t_connect_log WHERE a_idname='%s' ORDER BY a_index DESC LIMIT 10",
		idname);

	dbAuth.SetQuery(q);
	if (!dbAuth.Open())
		return true; 

	int count = 0;
	while (dbAuth.MoveNext())
	{
		CLCString ip;
		if (!dbAuth.GetRec("a_ip", ip))
			continue;

		count++;
		if (strcmp((const char*)ip, currentIp) != 0)
			return false; 
	}

	
	return true;
}

static void MakeVerifyToken(char* out, size_t outSize)
{
	
	unsigned int r1 = (unsigned int)rand();
	unsigned int r2 = (unsigned int)rand();
	unsigned int t = (unsigned int)time(NULL);
	snprintf(out, outSize, "%08X%08X%08X%08X", t, r1, r2, (unsigned int)(r1 ^ r2 ^ t));
}

static size_t CurlDiscard(void* contents, size_t size, size_t nmemb, void*)
{
	return size * nmemb;
}

static bool HttpGet(const char* url)
{
	CURL* curl = curl_easy_init();
	if (!curl) return false;

	char errbuf[CURL_ERROR_SIZE] = { 0 };
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3L);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 2L);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlDiscard);

	CURLcode res = curl_easy_perform(curl);

	long httpCode = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

	curl_easy_cleanup(curl);

	if (res != CURLE_OK)
	{
		GAMELOG << init("VERIFY_HTTP_FAIL", "curl")
			<< delim << url
			<< delim << curl_easy_strerror(res)
			<< delim << errbuf
			<< delim << httpCode
			<< end;
		return false;
	}

	return (httpCode >= 200 && httpCode < 300);
}



static void SendVerifyRequestHTTP(int usercode, const char* email, const char* token, const char* ip)
{
	// shared secret so randoms can’t spam your mail endpoint
	const char* secret = gserver.m_config.Find("Verify", "Secret");

	CLCString url(1024);
	url.Format(
		"%s/internal/send_verify.php?u=%d&e=%s&t=%s&ip=%s&k=%s",
		gserver.m_config.Find("Verify", "BaseURL"),
		usercode,
		email,
		token,
		ip,
		gserver.m_config.Find("Verify", "Secret")
	);

	HttpGet((const char*)url);
}
#endif

bool CDescriptor::GetLogin(CNetMsg::SP& msg)
{
	
	try
	{

		if (msg->m_mtype != MSG_LOGIN)
			throw MSG_FAIL_LOGIN_SERVER;

		if (!msg->m_buf || msg->m_size < sizeof(RequestClient::LoginFromClient))
			throw MSG_FAIL_LOGIN_SERVER;

		auto* packet = reinterpret_cast<RequestClient::LoginFromClient*>(msg->m_buf);

		packet->id[MAX_ID_NAME_LENGTH - 1] = '\0';
		packet->pw[MAX_PWD_LENGTH - 1] = '\0';

#ifdef CHECKIP_USA
		int IsUSA;
#endif

		if (packet->version < gserver.m_clientversionMin || packet->version > gserver.m_clientversionMax)
			throw MSG_FAIL_LOGINSERV_WRONG_VERSION;


#ifdef IP_BLOCK_AUTO
		LONGLONG regdate;
		if( strcmp(packet->pw, "releaseblock") == 0)
		{
			AUTO_BLOCK_INFO* p = gserver.m_autoBlockTable;
			while(p)
			{
				if( strcmp(packet->id, p->ip) == 0 )
				{
					if(p->prev)
					{
						p->prev->next = p->next;
						if(p->next) p->next->prev = p->prev;
					}
					else
					{
						gserver.m_autoBlockTable = p->next;
						if( gserver.m_autoBlockTable ) gserver.m_autoBlockTable->prev = NULL;
					}
				}
				p = p->next;
			}
		}
#endif

		

		if (strinc(packet->id, "'"))
		{
			throw MSG_FAIL_LOGINSERV_WRONG_CHAR;			// ���̵� ' ��
		}

		int len = strlen(packet->id);
		if (len < 3 || len > MAX_ID_NAME_LENGTH)
		{
			throw MSG_FAIL_LOGINSERV_WRONG_CHAR;
		}

		m_idname = packet->id;


		if (strinc(packet->pw, "'"))
		{
			throw MSG_FAIL_LOGINSERV_WRONG_PASSWORD;		// ��ȣ�� ' ��
		}

		len = strlen(packet->pw);
		if (len < 4 || len > MAX_PWD_LENGTH)
		{
			throw MSG_FAIL_LOGINSERV_WRONG_PASSWORD;
		}

		{
			char temp_pw[128];
			mysql_real_escape_string(&gserver.m_dbuser, temp_pw, (const char*)packet->pw, strlen(packet->pw));
			m_passwd = temp_pw;
		}

		// check block by IP
		{
			CDBCmd dbUser;
			CLCString blockSql(1000);
			blockSql.Format("select a_index from t_ip_block where a_ip = '%s' ", (const char*)service_->ip().c_str() );
			dbUser.Init(&gserver.m_dbuser);
			dbUser.SetQuery(blockSql);
			dbUser.Open();

			if( dbUser.GetRecordCount() > 0 )
			{
				GAMELOG << init("BLOCK IP", packet->id) << service_->ip().c_str() << end;
				throw MSG_FAIL_CONNECT_SERVER;
			}
		}

		// check block by MAC
#ifdef BLOCK_MAC_ADDR
		{
			CDBCmd dbAuth;
			CLCString blockSql(1000);
			blockSql.Format(
				"SELECT a_index FROM t_mac_block WHERE a_mac = '%s' OR a_hwid = '%s'",
				(const char*)packet->mac,
				(const char*)packet->hwid
			);
			dbAuth.Init(&gserver.m_dbAuth);
			dbAuth.SetQuery(blockSql);
			dbAuth.Open();

			LOG_INFO("Block check by MAC or HWID %d - MAC: %s, HWID: %s",
				dbAuth.GetRecordCount(),
				(const char*)packet->mac,
				(const char*)packet->hwid);

			if (dbAuth.GetRecordCount() > 0)
			{
				throw MSG_FAIL_CONNECT_SERVER;
			}
		}
#endif //BLOCK_MAC_ADDR

		CLCString sql(1024);
	
		sql.Format("SELECT user_code, user_id, passwd FROM bg_user WHERE LOWER(user_id)=LOWER('%s') AND passwd=MD5('%s')", (const char*)m_idname, (const char*)m_passwd);


		CDBCmd dbAuth;
		dbAuth.Init(&gserver.m_dbAuth);
		dbAuth.SetQuery(sql);

		if (!dbAuth.Open())
		{
			throw MSG_FAIL_LOGINSERV_WRONG_PASSWORD;
		}

		if (!dbAuth.MoveFirst())
		{
			throw MSG_FAIL_LOGINSERV_WRONG_PASSWORD;
		}

		int usercode;

		dbAuth.GetRec("user_code", usercode);

#ifdef IPVERIFY
		// ----- EMAIL VERIFY / IP TRUST CHECK START -----
		{
			const char* curIp = service_->ip().c_str();

			// 1) Read email + a_enabled + cooldown info from bg_user
			CDBCmd dbAcc;
			dbAcc.Init(&gserver.m_dbAuth);

			// use unix_timestamp for cooldown math
			CLCString q(1024);
			q.Format(
				"SELECT email, a_enabled, "
				"       IFNULL(unix_timestamp(verify_sent_at), 0) AS sent_ts "
				"FROM bg_user "
				"WHERE user_code=%d",
				usercode
			);
			dbAcc.SetQuery(q);

			if (dbAcc.Open() && dbAcc.MoveFirst())
			{
				CLCString email;
				int enabled = 1;
				int sent_ts = 0;

				dbAcc.GetRec("email", email);
				dbAcc.GetRec("a_enabled", enabled);
				dbAcc.GetRec("sent_ts", sent_ts);

				// 2) Check last 10 IPs
				CDBCmd dbLog;
				dbLog.Init(&gserver.m_dbAuth);

				bool ipTrusted = IsRecentIPTrusted(dbLog, (const char*)m_idname, curIp);

				// If IP mismatch => force verify
				if (!ipTrusted)
				{
					// Disable + create token + store expiry
					if (email.Length() > 5)
					{
						// Cooldown (e.g. 60s) to prevent spam if user keeps retrying login
						const int now = (int)time(NULL);
						const int cooldown = 60;
						const bool canSend = (sent_ts == 0) || ((now - sent_ts) >= cooldown);

						char token[128] = { 0 };
						MakeVerifyToken(token, sizeof(token));

						CDBCmd dbUpd;
						dbUpd.Init(&gserver.m_dbAuth);

						// Always set a_enabled=0 when IP isn't trusted.
						// Only refresh verify_sent_at if we are going to send right now.
						CLCString uq(2048);
						if (canSend)
						{
							uq.Format(
								"UPDATE bg_user "
								"SET a_enabled=0, "
								"    verify_token='%s', "
								"    verify_expires=DATE_ADD(NOW(), INTERVAL 30 MINUTE), "
								"    verify_sent_at=NOW() "
								"WHERE user_code=%d",
								token, usercode
							);
						}
						else
						{
							uq.Format(
								"UPDATE bg_user "
								"SET a_enabled=0, "
								"    verify_token='%s', "
								"    verify_expires=DATE_ADD(NOW(), INTERVAL 30 MINUTE) "
								"WHERE user_code=%d",
								token, usercode
							);
						}
						dbUpd.SetQuery(uq);
						dbUpd.Update();

						bool httpOk = false;

						if (canSend)
						{
							// 3) Call website internal endpoint to actually send email
							std::string e = UrlEncode((const char*)email);
							std::string t = UrlEncode(token);
							std::string ip = UrlEncode(curIp);

							CLCString url(2048);
							url.Format(
								"%s/internal/send_verify.php?u=%d&e=%s&t=%s&ip=%s&k=%s",
								gserver.m_config.Find("Verify", "BaseURL"),
								usercode,
								e.c_str(),
								t.c_str(),
								ip.c_str(),
								gserver.m_config.Find("Verify", "Secret")
							);

							httpOk = HttpGet((const char*)url);
						}

						GAMELOG << init("EMAIL_VERIFY_REQUIRED", (const char*)m_idname)
							<< curIp
							<< delim << (const char*)email
							<< delim << (canSend ? 1 : 0)
							<< delim << (httpOk ? 1 : 0)
							<< end;
					}

					// Deny login until verified
					throw MSG_FAIL_LOGINSERV_EMAIL_SENT; // swap to your NEED_VERIFY code
				}

				// If IP trusted but account is still disabled => block (means verify pending)
				if (enabled == 0)
				{
					throw MSG_FAIL_LOGINSERV_EMAIL_SENT; // swap to your NEED_VERIFY code
				}
			}
		}
		// ----- EMAIL VERIFY / IP TRUST CHECK END -----
#endif

		// IP �˻��
		CLCString temp(50);
		CLCString blockBand(50);

		// user DB

// 050226 : bs : a_enable �˻� �߰�
		sql.Format("SELECT unix_timestamp(a_regi_date) as a_regtime, a_enable, a_server_num, a_subnum, a_zone_num FROM t_users WHERE a_portal_index=%d", usercode);

		CDBCmd dbUser;
		dbUser.Init(&gserver.m_dbuser);
		dbUser.SetQuery(sql);

		if (!dbUser.Open())
			goto FIRST_CONNECT;

		if (!dbUser.MoveFirst())
			goto FIRST_CONNECT;

		int enable;
		if (!dbUser.GetRec("a_enable", enable) || enable != 1)
		{
			throw MSG_FAIL_LOGINSERV_BLOCK_CHAR;
		}

// --- 050226 : bs : a_enable �˻� �߰�

		///////////////
		// ������ �˻�
		char blockTemp[50];
		int blockCount;

		char *token;

		temp = gserver.m_config.Find("Block IP", "Number");

		if(strcmp(temp, ""))
		{
			blockCount = atoi(temp);

			for(int j = 0; j < blockCount; j++)
			{
				// Ŭ���̾�Ʈ ip�� ��

				temp.Format("IP%d", j);

				if(strcmp(this->service_->ip().c_str(), gserver.m_config.Find("Block IP", temp)) == 0)
				{
					GAMELOG << init("BLOCK IP", packet->id)
							<< service_->ip().c_str()
							<< end;
					throw MSG_FAIL_CONNECT_SERVER;
				}
			}
		}

		// Band1=A-211.090.000.000-211.103.255.255
		temp = gserver.m_config.Find("Block Band", "Number");

		if(strcmp(temp, ""))
		{
			blockCount = atoi(temp);

			for(int j = 0; j < blockCount; j++)
			{
				// Ŭ���̾�Ʈ ip�� ��

				temp.Format("Band%d", j);
				blockBand = gserver.m_config.Find("Block Band", temp);
				strcpy(blockTemp, blockBand);

				token = strtok(blockTemp, "-");
				if(token == NULL) continue;
				temp = token;

				int ipStart[4] = {0, 0, 0, 0};
				int ipEnd[4] = {0, 0, 0, 0};
				int ipHost[4] = {0, 0, 0, 0};
				token = strtok(NULL, "-");
				if(token == NULL) continue;
				IPtoi(token, ipStart, ipStart + 1, ipStart + 2, ipStart + 3);
				token = strtok(NULL, "-");
				if(token == NULL) continue;
				IPtoi(token, ipEnd, ipEnd + 1, ipEnd + 2, ipEnd + 3);
				IPtoi(service_->ip().c_str(), ipHost, ipHost + 1, ipHost + 2, ipHost + 3);

				if( !strcmp(temp, "A") )
				{
					if (ipStart[0] == ipHost[0] && ipStart[1] <= ipHost[1] && ipHost[1] <= ipEnd[1])
					{
						GAMELOG << init("BLOCK Band", packet->id)
								<< blockBand << delim
								<< service_->ip().c_str()
								<< end;

						throw MSG_FAIL_CONNECT_SERVER;
					}
				}

				if( !strcmp(temp, "B") )
				{
					if (ipStart[0] == ipHost[0] && ipStart[1] == ipHost[1] && ipStart[2] <= ipHost[2] && ipHost[2] <= ipEnd[2])
					{
						GAMELOG << init("BLOCK Band", packet->id)
								<< blockBand << delim
								<< service_->ip().c_str()
								<< end;

						throw MSG_FAIL_CONNECT_SERVER;
					}
				}

				if( !strcmp(temp, "C") )
				{
					if (ipStart[0] == ipHost[0] && ipStart[1] == ipHost[1] && ipStart[1] == ipHost[1] &&
							ipStart[3] <= ipHost[3] && ipHost[3] <= ipEnd[3])
					{
						GAMELOG << init("BLOCK Band", packet->id)
								<< blockBand << delim
								<< service_->ip().c_str()
								<< end;
						throw MSG_FAIL_CONNECT_SERVER;
					}
				}
			}
		}

#ifdef IP_BLOCK_AUTO
		dbUser.GetRec("a_regtime", regdate);

		time_t notime, now;
		struct tm noblockDate;
		time(&now);
		noblockDate = *localtime(&now);
		noblockDate.tm_year = 105;
		noblockDate.tm_mon = 5;
		noblockDate.tm_mday = 20;
		noblockDate.tm_hour = 0;
		noblockDate.tm_min = 0;
		noblockDate.tm_sec = 0;
		noblockDate.tm_isdst = -1;
		notime = mktime(&noblockDate);

		if(notime > regdate)
		{
			// ������ �˻縦 ����ϸ�
			// �õ� ȸ�� �˻翡 ��
			// 1. �����ؾ��ϳ� �˻�
			// 2. ���� ������ �˻�
			// 3. ���̺����� �õ� ȸ�� �˻�
			// 4. ���̺� ����
			if (gserver.m_autoBlockPulse + PULSE_REAL_HOUR * atoi(gserver.m_config.Find("Auto Block", "Refresh")) < gserver.m_pulse)
			{
				gserver.m_autoBlockPulse = gserver.m_pulse;
				while (gserver.m_autoBlockTable)
				{
					AUTO_BLOCK_INFO* p = gserver.m_autoBlockTable;
					gserver.m_autoBlockTable = gserver.m_autoBlockTable->next;
					delete p;
				}
			}

			char tmpBuf[100] = {0,};
			char tmpBuf1[100] = {0,};
			sprintf(tmpBuf, "ExIP%s", (const char*)service_->ip().c_str());
			sprintf(tmpBuf1, "ExID%s", (const char*)packet->id);
			if ( strlen(gserver.m_config.Find("Auto Block", tmpBuf)) == 0 && strlen(gserver.m_config.Find("Block ExID", tmpBuf1)) == 0 )
			{
				// ���� �ƴ�
				int count = 0;
				bool bFound = false;
				AUTO_BLOCK_INFO* p = gserver.m_autoBlockTable;
				while (p)
				{
					if (strcmp(p->ip, service_->ip().c_str()) == 0)
					{
						count++;
						if (strcmp(p->id, packet->id) == 0)
						{
							bFound = true;
						}
					}
					p = p->next;
				}

				if (count >= atoi(gserver.m_config.Find("Auto Block", "MaxTry")))
				{
					GAMELOG << init("AUTO BLOCK", packet->id)
							<< service_->ip().c_str() << delim
							<< count
							<< end;
#ifdef IP_BLOCKNOKICK_AUTO

#else
					throw MSG_FAIL_CONNECT_SERVER;
#endif
				}
				else
				{
					if (!bFound)
					{
						p = new AUTO_BLOCK_INFO;
						strcpy(p->ip, service_->ip().c_str());
						strcpy(p->id, packet->id);
						p->prev = NULL;
						p->next = gserver.m_autoBlockTable;
						if( gserver.m_autoBlockTable ) gserver.m_autoBlockTable->prev = p;
						gserver.m_autoBlockTable = p;
					}
				}
			}
		}

#endif

#ifdef BLOCK_MAC_ADDR
		{
			CLCString insertMacSql(1000);
			insertMacSql.Format(
				"INSERT INTO t_mac_log (a_user_code, a_mac, a_hwid) VALUES (%d, '%s', '%s')",
				usercode,
				(const char*)packet->mac,
				(const char*)packet->hwid
			);
			dbAuth.Init(&gserver.m_dbAuth);
			dbAuth.SetQuery(insertMacSql);
			dbAuth.Update();
		}
#endif // BLOCK_MAC_ADDR

		int server;
		int subnum;
		int zone;
		if (!dbUser.GetRec("a_server_num", server))
			goto FIRST_CONNECT;
		if(!dbUser.GetRec("a_subnum", subnum))
			goto FIRST_CONNECT;
		if (!dbUser.GetRec("a_zone_num", zone))
			goto FIRST_CONNECT;

		if (zone >= 0)
		{
			// �̹� ���ӵǾ� ����
			// �޽������� ���� ó�� ��û �޼���
			CNetMsg::SP rmsg(new CNetMsg);
			LogoutReqMsg(rmsg, server, subnum, zone, this);
			MessengerInLogin::instance()->WriteToOutput(rmsg);
			throw MSG_FAIL_LOGINSERV_ALREADY_CONNECT;
		}

#ifdef CHECKIP_USA
		IsUSA = CheckIPForUSA(service_->ip().c_str());
#endif // CHECKIP_USA

		GAMELOG << init("LOGIN", packet->id)
				<< service_->ip().c_str()
#ifdef CHECKIP_USA
				<< delim
				<< IsUSA
#endif // CHECKIP_USA
				<< end;

#ifndef INTERNATIONAL_LOCAL_ACCESS_RESTRICTIONS
		int i;
#endif //INTERNATIONAL_LOCAL_ACCESS_RESTRICTIONS
		for (i=0; i < gserver.m_nConnector; i++)
		{
			// ����� �� ����
			{
				CNetMsg::SP rmsg(new CNetMsg);
				PlayerNumMsg(rmsg, server, subnum, i);
				this->WriteToOutput(rmsg);
			}
		}
		return true;

FIRST_CONNECT:


#ifdef CHECKIP_USA
		IsUSA = CheckIPForUSA(service_->ip().c_str());
#endif // CHECKIP_USA

		GAMELOG << init("LOGIN", m_idname)
				<< service_->ip().c_str()
#ifdef CHECKIP_USA
				<< delim
				<< IsUSA
#endif // CHECKIP_USA
				<< end;

		for (i=0; i < gserver.m_nConnector; i++)
		{

			{
				CNetMsg::SP rmsg(new CNetMsg);
				PlayerNumMsg(rmsg, -1, -1, i);
				this->WriteToOutput(rmsg);
			}
		}

		STATE(this) = CON_PLAYING;

		return true;
	}
	catch (MSG_FAIL_TYPE failtype)
	{
		{
			CNetMsg::SP rmsg(new CNetMsg);
			FailMsg(rmsg, failtype);
			this->WriteToOutput(rmsg);
		}

		return false;
	}
}


void CDescriptor::operate( rnSocketIOService* service )
{
	CNetMsg::SP msg(service->GetMessage());

	switch (client_type_)
	{
	case CLIENT_TYPE_CLIENT:
		{
			if (STATE(this) == CON_GET_LOGIN)
			{
				bool ret = this->GetLogin(msg);
				if (ret)
				{
					LOG_INFO("LOGIN OK / id[%s]", (const char *)this->m_idname);
				}
				else
				{
					LOG_INFO("LOGIN Failed / id[%s]", (const char *)this->m_idname);
					this->service_->Close("Login Failed");
				}
			}
			else
			{
				LOG_ERROR("Invalid packet type[%d] / ip[%s]", msg->m_mtype, service->ip().c_str());
				service->Close("Invalid Packet");
			}
		}
		break;

	case CLIENT_TYPE_CONNECTOR:
		{
			gserver.ProcConnector(msg);
		}
		break;

	default:
		{
			LOG_ERROR("Invalid Client type[%d]", client_type_);
			service->Close("Invalid Client");
		}
		break;
	}
}

void CDescriptor::onClose( rnSocketIOService* service )
{
	service_ = NULL;
	bnf::instance()->RemoveSession(service);

	if (client_type_ == CLIENT_TYPE_CLIENT)
	{
		delete this;
	}
	else
	{
		// Connector server�� �������� Ÿ�̸� ����
		bnf::instance()->CreateMSecTimer(RECONNECT_TIME_TO_CONNECTOR_SERVER, &reconnect_timer_);

		for (int j = 0; j < m_nMaxServer; ++j)
		{
			m_playerNum[j] = -1;
		}

		LOG_FATAL("********************* Disconnect from Connector server (%s : %d) *********************",
				  connect_host_.c_str(), connect_port_);
	}
}

//////////////////////////////////////////////////////////////////////////

void CDescriptor::setConnectInfo( std::string connect_host, int connect_port )
{
	connect_host_ = connect_host;
	connect_port_ = connect_port;
}

void CDescriptor::Connect()
{
	bnf::instance()->CreateAsyncConnect(connect_host_, connect_port_, this);
}

void CDescriptor::onConnect( rnSocketIOService* service )
{
	service_ = service;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_CONN_CONNECT);
		RefMsg(rmsg) << SERVER_VERSION
					 << (int)LOGIN_SERVER_NUM;	// ��������ȣ ����

		if( gserver.m_bOnlyLocal )
			RefMsg(rmsg) << (int) 0;
		else
			RefMsg(rmsg) << (int) 1;

		this->WriteToOutput(rmsg);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		PlayerReqMsg(rmsg);
		this->WriteToOutput(rmsg);
	}

	LOG_INFO("connected to Connector server (%s : %d)", connect_host_.c_str(), connect_port_);
}

void CDescriptor::onConnectFail( rnSocketIOService* service )
{
	LOG_INFO("Can't connect to Connector server (%s : %d)", connect_host_.c_str(), connect_port_);
}
