#include <boost/scoped_ptr.hpp>
#include "stdhdrs.h"

#include "../ShareLib/bnf.h"
#include "Log.h"
#include "Character.h"
#include "CmdMsg.h"
#include "DBManager.h"
#include "Descriptor.h"
#include "Notice.h"
#include "../ShareLib/packetType/ptype_old_extend.h"
#include "../ShareLib/packetType/ptype_server_to_server.h"
#include "../ShareLib/packetType/ptype_syndicate.h"
#include "../ShareLib/packetType/ptype_attendance.h"
#include "../ShareLib/packetType/ptype_old_login.h"
#include "../ShareLib/packetType/ptype_notice.h"
#include "../ShareLib/packetType/ptype_old_do_title.h"
#include "../ShareLib/packetType/ptype_mail_box.h"
#include "DescManager.h"
#include "Artifact_Manager.h"
#include "Notice.h"
#include "RezasFunction.h"
unsigned int CDescriptor::static_auto_save_sequence = 0;
std::set<CDescriptor*> CDescriptor::auto_set[AUTO_SAVE_SEQUENCT];


CDescriptor::CDescriptor(rnSocketIOService* service)
	: m_idname(MAX_ID_NAME_LENGTH + 1)
	, m_passwd(MAX_PWD_LENGTH + 1)
	, m_ident(9)
	, m_proSite(3+1)
#ifdef HANARO_EVENT
	, m_hanaroCode(4)
#endif
	, m_tExtendCharacterSlotTime(0)
{
	m_seq_index = 0;
	request_start_game_flag_ = false;
	service_ = service;
	m_index = -1;

	m_nPrepareSeed = 0;

	m_hackCheckPulse = 0;
	m_hackServerPulse = 0;
	m_hackClientPulse = 0;
	m_hackLastClientDiff = 0;
	m_hackCount = 0;

	m_idletics = 0;
	m_commandcount = 0;
	m_checktics = 0;

	m_connected = 0;
	m_logined	= LOGIN_STATE_NOT;
	m_playmode = MSG_LOGIN_NEW;  // default play mode
	m_bclosed	= false;
	m_bGoZone = false;
	m_bGoZoneSent = true;

	m_pChar = NULL;
	m_pPrev = NULL;
	m_pNext = NULL;
//0704
	memset(m_notice, 0, sizeof(int) * MAX_NOTICE);

#if defined(EVENT_PCBANG_2ND)
	m_location = 0;
#endif //

	m_bCreate90Lv = false;
	m_bNotCreateNightShadow = false;
	m_bIsNSCreateCardUse = false;

	m_msgGoZone.reset(new CNetMsg);
	m_autoSaveSeq = 0;
}

CDescriptor::~CDescriptor()
{
	if (m_pChar)
	{
		auto_set[m_autoSaveSeq].erase(this);

		// Offline-vendor keep-alive: on a forced socket close the descriptor is
		// destroyed without going through returnToCharacterSelectMode, so we
		// have to detect the offline shop here too and preserve the CPC.
#ifdef OFFLINE_SHOPS
		if (m_pChar->m_personalshop && m_pChar->m_personalshop->IsOfflineMode())
		{
			CPC* vendor = m_pChar;
			PCManager::instance()->deletePlayerByPC(vendor);
			vendor->m_desc = NULL;

			int vendorShopId = vendor->m_personalshop->GetShopId();
			if (vendorShopId > 0)
			{
				boost::recursive_mutex::scoped_lock lock(gserver->m_offlineVendorRegistryMutex);
				gserver->m_offlineVendorRegistry[vendorShopId] = vendor;
			}

			LOG_INFO("~CDescriptor: Keeping offline vendor alive (char_index: %d, shop_id: %d)",
				vendor->m_index, vendorShopId);
		}
		else
#endif
		{
			PCManager::instance()->deletePlayerByPC(m_pChar);
			delete m_pChar;
		}
	}

	m_pChar = NULL;
}

void CDescriptor::WriteToOutput(CNetMsg::SP& msg)
{
	if (msg->isRightPacket() == false)
	{
		LOG_ERROR("Packet checksum is invalid.");
		raise(SIGABRT);
		return;
	}

	if(this->m_connected == CON_PREPARE_PLAY_BEFORE)
		return;

	if (msg->m_mtype == MSG_UNKNOWN)
		return;

	if (service_ == NULL)
		return;

	service_->deliver(msg);
}

bool CDescriptor::GetLogin(CNetMsg::SP& msg)
{
	try
	{
		if (msg->m_mtype != MSG_LOGIN)
			throw MSG_FAIL_CONNECT_SERVER;		// �߸��� �Է�

		if (PCManager::instance()->getPlayerCount() > MAX_PLAYER_LIST)
			throw MSG_FAIL_MANY_CONNECT;		// ���� ��û �ʰ�

		RequestClient::LoginFromClient* packet = reinterpret_cast<RequestClient::LoginFromClient*>(msg->m_buf);
		packet->id[MAX_ID_NAME_LENGTH] = '\0';
		packet->pw[MAX_PWD_LENGTH] = '\0';

#ifdef HANARO_EVENT

#if defined (LC_USA) || defined (LC_RUS) || defined (LC_GAMIGO)// �̱�,���þ�,���̰� ����
		m_hanaroCode = "";
#else // LC_USA
		// �ϳ�������-HF, ��ε���-SK
		CLCString proSite(4);
		RefMsg(msg) >> proSite;
		m_hanaroCode = proSite;
#endif // LC_USA || LC_RUS

#endif // HANARO_EVENT

		GAMELOG << init("LOGIN REQ", packet->id)
				<< "VERSION" << delim << packet->version << delim
				<< "MODE" << delim << packet->mode << delim
				<< "IP" << delim << getHostString() << delim
				<< "NATION" << delim << packet->nation
#ifdef HANARO_EVENT
				<< delim << "PROSITE" << delim << m_hanaroCode
#endif
				<< end;


		if (DescManager::instance()->getDescById((const char *)packet->id))
		{
			LOG_ERROR("duplicate login. id[%s] ip[%s]", (const char *)packet->id, this->service_->ip().c_str());
			throw MSG_FAIL_ALREADY_CONNECT;
		}
      
		// IP �˻��
		CLCString temp(50);
		CLCString blockBand(50);

		char blockTemp[50];
		int blockCount;

		char *token;

		temp = gserver->m_config.Find("Block IP", "Number");

		if(strcmp(temp, ""))
		{
			blockCount = atoi(temp);

			for(int j = 0; j < blockCount; j++)
			{
				// Ŭ���̾�Ʈ ip�� ��

				temp.Format("IP%d", j);

				if(strcmp(this->getHostString(), gserver->m_config.Find("Block IP", temp)) == 0)
				{
					GAMELOG << init("BLOCK IP", packet->id)
							<< this->getHostString()
							<< end;

					throw MSG_FAIL_LOGINSERV_NO_SERVICE;
				}
			}
		}

		// Band1=A-211.090.000.000-211.103.255.255
		temp = gserver->m_config.Find("Block Band", "Number");

		if(strcmp(temp, ""))
		{
			blockCount = atoi(temp);

			for(int j = 0; j < blockCount; j++)
			{
				// Ŭ���̾�Ʈ ip�� ��

				temp.Format("Band%d", j);
				blockBand = gserver->m_config.Find("Block Band", temp);
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
				IPtoi(getHostString(), ipHost, ipHost + 1, ipHost + 2, ipHost + 3);

				if( !strcmp(temp, "A") )
				{
					if (ipStart[0] == ipHost[0] && ipStart[1] <= ipHost[1] && ipHost[1] <= ipEnd[1])
					{
						GAMELOG << init("BLOCK Band", packet->id)
								<< blockBand << delim
								<< getHostString()
								<< end;

						throw MSG_FAIL_LOGINSERV_NO_SERVICE;
					}
				}

				if( !strcmp(temp, "B") )
				{
					if (ipStart[0] == ipHost[0] && ipStart[1] == ipHost[1] && ipStart[2] <= ipHost[2] && ipHost[2] <= ipEnd[2])
					{
						GAMELOG << init("BLOCK Band", packet->id)
								<< blockBand << delim
								<< getHostString()
								<< end;

						throw MSG_FAIL_LOGINSERV_NO_SERVICE;
					}
				}

				if( !strcmp(temp, "C") )
				{
					if (ipStart[0] == ipHost[0] && ipStart[1] == ipHost[1] && ipStart[1] == ipHost[1] &&
							ipStart[3] <= ipHost[3] && ipHost[3] <= ipEnd[3])
					{
						GAMELOG << init("BLOCK Band", packet->id)
								<< blockBand << delim
								<< getHostString()
								<< end;
						throw MSG_FAIL_LOGINSERV_NO_SERVICE;
					}
				}
			}
		}

		if (packet->version < gserver->m_clientversionMin || packet->version > gserver->m_clientversionMax )//VERSION_FOR_CLIENT)//reza
		{
			//if(!SKIPCOND)
			throw MSG_FAIL_WRONG_VERSION;
		}

#if defined (INTERGRATION_SERVER)
		if ( !gserver->m_intergrationInfo.Check(packet->nation) )
#else
		
#endif // BILA_INTERGRATION_SERVER
		

		if (packet->mode == MSG_LOGIN_NEW)
			this->m_playmode = MSG_LOGIN_NEW;
#ifdef GMTOOL
		else if (packet->mode == MSG_LOGIN_GM)
		{
			this->m_playmode = MSG_LOGIN_GM;
			if( gserver->m_serverno != 1 || gserver->m_subno != 1)
				throw MSG_FAIL_LOGINSERV_NO_SERVICE;
		}
#endif // GMTOOL
		else
			this->m_playmode = MSG_LOGIN_RE;

		if (strinc(packet->id, "'"))
			throw MSG_FAIL_WRONG_CHAR;			// ���̵� ' ��

		int len = strlen(packet->id);
		if (len < 3 || len > MAX_ID_NAME_LENGTH)
			throw MSG_FAIL_WRONG_CHAR;

		m_idname = packet->id;

		if (strinc(packet->pw, "'"))
			throw MSG_FAIL_WRONG_PASSWORD;		// ��ȣ�� ' ��

		len = strlen(packet->pw);
		if (len < 4 || len > MAX_PWD_LENGTH)
			throw MSG_FAIL_WRONG_PASSWORD;

		m_passwd = packet->pw;

// 050226 : bs : �ϴ� ������ �߱��� ������ �˻�
#if defined(LC_KOR)
		if (!CheckIP(getHostString()))
		{
			GAMELOG << init("SYS_ERR")
					<< "BLOCK IP"
					<< getHostString()
					<< end;
			throw MSG_FAIL_LOGINSERV_NO_SERVICE;
		}
#endif
// --- 050226 : bs : �ϴ� ������ �߱��� ������ �˻�

#ifdef GER_LOG
		GAMELOGGEM << init( 0, "ACCOUNT_LOGIN_SUCCESS")
				   << LOG_VAL("first-time", "1") << blank
				   << LOG_VAL("ipv4", this->getHostString()) << blank
				   << LOG_VAL("client-version", packet->version) << blank
				   << endGer;

#endif // GER_LOG

		return true;
	}
	catch (MSG_FAIL_TYPE failtype)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		FailMsg(rmsg, failtype);
		SEND_Q(rmsg, this);

		return false;
	}
}

//XX ĳ���ͼ��� 1
bool CDescriptor::StartGame(CNetMsg::SP& msg)
{
	if (this->m_pChar != NULL)
	{
		LOG_ERROR("Already selected character. userIndex[%d]", this->m_index);
		this->Close("Already selected character");
		return false;
	}

	msg->MoveFirst();

	unsigned char mode = 0;
	int char_index = 0;

	RefMsg(msg) >> mode
				>> char_index;

	CGuildMember* member = gserver->m_guildlist.findmember(char_index);
	if (member != NULL && member->guild() != NULL)
	{
		// ���� �� gamesever�� charindex�� �ش��ϴ� ������ ������ ������ �ٷ� ����...
		this->request_start_game_flag_ = false;
		DBManager::instance()->PushSelectCharacter(this, char_index, member);
	}
	else
	{
		// ���� �� gameserver�� charindex�� �ش��ϴ� ������ ���ٸ� ������ �ΰ��� �����
		// 1. �����̳� ���� gameserver�� guild info�� ������� ���� ���
		// 2. ������ �ƴѰ��
		// �׷��Ƿ� ���� helper server���� ��� ������ ��û�ϰ�, �ڵ��� ó�� ��Ŷ�� ������
		// ������ ������ ����
		{
			CNetMsg::SP rmsg(new CNetMsg);
			HelperGuildLoadReq(rmsg, this->m_idname, char_index, gserver->m_subno, 0);
			SEND_Q(rmsg, gserver->m_helper);
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_HELPER_COMMAND);
			RefMsg(rmsg) << MSG_HELPER_SELECT_CHARACTER
						 << this->m_index
						 << this->m_seq_index
						 << char_index;
			SEND_Q(rmsg, gserver->m_helper);
		}
	}

	return true;
}

//XX ĳ���ͻ��� 1
bool CDescriptor::CharNew(CNetMsg::SP& msg)
{
	msg->MoveFirst();

	unsigned char mode = 0;
	CLCString name(MAX_CHAR_NAME_LENGTH + 1);
	char job = -1;
	char hairstyle = 1;
	char facestyle = 1;

	RefMsg(msg) >> mode
				>> name
				>> job
				>> hairstyle
				>> facestyle;

	if( job == JOB_NIGHTSHADOW)
	{
		// ����Ʈ �����찡 �̹� ���� ��
		if( m_bNotCreateNightShadow )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			FailMsg(rmsg, MSG_FAIL_CANNOT_CREATE_NS);
			SEND_Q(rmsg, this);
			return false;
		}
		// 100lv ĳ���Ͱ� ���� NSCard ��� ������ ��
		if(!m_bCreate90Lv && !m_bIsNSCreateCardUse)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			FailMsg(rmsg, MSG_FAIL_CANNOT_CREATE_NS);
			SEND_Q(rmsg, this);
			return false;
		}
	}

	// �̸��� 0 ���� ������ �ȵȴ�.
	if (strlen(name) < 4 || strlen(name) > MAX_NAME_LENGTH)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		FailMsg(rmsg, MSG_FAIL_WRONG_CHAR);
		SEND_Q(rmsg, this);
		return false;
	}
	// �̸��� ' �� ��� ������ �ȵȴ�.
	if (strinc(name, "'") || strinc(name, " "))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		FailMsg(rmsg, MSG_FAIL_WRONG_CHAR);
		SEND_Q(rmsg, this);
		return false;
	}
	
	if(findPercentChar(name.GetBuffer()) != NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		FailMsg(rmsg, MSG_FAIL_WRONG_CHAR);
		SEND_Q(rmsg, this);
		return false;
	}

#ifdef LC_RUS
	// [selo: 101115] ���þƴ� ���þƾ� �̿��� ���� ���� �ȵȴ�.
	if( CheckNoRussianCharacter(name) )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		FailMsg(rmsg, MSG_FAIL_WRONG_CHAR);
		SEND_Q(rmsg, this);
		return false;
	}
#endif // LC_RUS

	if(CheckAnsii(name))
    {
        CNetMsg::SP rmsg(new CNetMsg);
        FailMsg(rmsg, MSG_FAIL_WRONG_CHAR);
        SEND_Q(rmsg, this);
        return false;
    }
	
	// �ӽ������� ĳ���͸� �����Ѵ�.
	// �Ʒ� �����߿� LevelUp()�Լ��� �̿��ϱ� ����
	boost::scoped_ptr<CPC> t_pChar(new CPC);

	t_pChar->m_name = name;
#ifdef LC_USA
	t_pChar->m_nick = name;
#endif

	// ��ȿ�� �˻�
	int haircount = 0;
	int facecount = 0;
	switch (job)
	{
	case JOB_TITAN:
		haircount = HAIR_TITAN;
		facecount = FACE_TITAN;
		break;
	case JOB_MAGE:
		haircount = HAIR_MAGE;
		facecount = FACE_MAGE;
		break;
	case JOB_HEALER:
		haircount = HAIR_HEALER;
		facecount = FACE_HEALER;
		break;
	case JOB_KNIGHT:
		haircount = HAIR_KNIGHT;
		facecount = FACE_KNIGHT;
		break;
	case JOB_ROGUE:
		haircount = HAIR_ROGUE;
		facecount = FACE_ROGUE;
		break;
	case JOB_SORCERER:
		haircount = HAIR_SORCERER;
		facecount = FACE_SORCERER;
		break;
	case JOB_NIGHTSHADOW:
		haircount = HAIR_NIGHTSHADOW;
		facecount = FACE_NIGHTSHADOW;
		break;
#ifdef EX_ROGUE
	case JOB_EX_ROGUE:
		haircount = HAIR_EX_LOG;
		facecount = FACE_EX_ROGUE;
		break;
#endif
#ifdef EX_MAGE
	case JOB_EX_MAGE:
		haircount = HAIR_EX_MAGE;
		facecount = FACE_EX_MAGE;
		break;
#endif
	}
	if (hairstyle < 1 || hairstyle > haircount || facestyle < 1 || facestyle > facecount)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		FailMsg(rmsg, MSG_FAIL_DB_NEW_CHAR);
		SEND_Q(rmsg, this);
		return false;
	}

	t_pChar->m_job = job;
	t_pChar->m_hairstyle = hairstyle;
	t_pChar->m_facestyle = facestyle;
	t_pChar->m_level = 1;


	if( t_pChar->m_job == JOB_NIGHTSHADOW )
	{
		t_pChar->m_level = 90;
		t_pChar->m_job2	= JOB_2ND_NIGHTSHADOW;
		t_pChar->m_statpt_remain = 236;

		
	}

	t_pChar->LevelUp(false);

	//////////////////////////////////////////////////////////////////////////
	// DBProcess�� �����ϱ� ���� ������ �����Ѵ�.
	// cinfo�� �Ҹ��� class DBProcess���� ó���� (boost::scoped_ptr<>)
	CreateCharacterInfo* cinfo = new CreateCharacterInfo;
	cinfo->m_index = this->m_index;
	cinfo->m_tExtendCharacterSlotTime = this->getExtendCharacterSlotTime();
#ifdef HANARO_EVENT
	cinfo->m_hanaroCode = (const char*)this->m_hanaroCode;
#endif
	cinfo->m_name = (const char*)t_pChar->m_name;
	cinfo->m_job = t_pChar->m_job;
	cinfo->m_hairstyle = t_pChar->m_hairstyle;
	cinfo->m_facestyle = t_pChar->m_facestyle;
	cinfo->m_str = t_pChar->m_str;
	cinfo->m_dex = t_pChar->m_dex;
	cinfo->m_int = t_pChar->m_int;
	cinfo->m_con = t_pChar->m_con;
	cinfo->m_dbHP = t_pChar->m_dbHP;
	cinfo->m_dbMP = t_pChar->m_dbMP;
	cinfo->m_level = t_pChar->m_level;
	cinfo->m_job2 = t_pChar->m_job2;
	cinfo->m_statpt_str = t_pChar->m_statpt_str;
	cinfo->m_statpt_dex = t_pChar->m_statpt_dex;
	cinfo->m_statpt_con = t_pChar->m_statpt_con;
	cinfo->m_statpt_int = t_pChar->m_statpt_int;
	cinfo->m_statpt_remain = t_pChar->m_statpt_remain;
	cinfo->m_etcEvent = t_pChar->m_etcEvent;
	DBManager::instance()->PushCreateChar(this, cinfo);

	return true;
}

//XX ĳ���ͻ��� 1
//XX ĳ���ͺ��� 1
bool CDescriptor::CharDel(CNetMsg::SP& msg)
{
	msg->MoveFirst();

	unsigned char mode = 0;
	int char_index = 0;

	RefMsg(msg) >> mode
				>> char_index;

#ifdef CHARDEL_CHECKID
#ifdef JUMIN_DB_CRYPT
	CLCString uid(MAX_ID_NAME_LENGTH + 1);
	RefMsg(msg) >> uid;
#else //JUMIN_DB_CRYPT
	CLCString ident(9);
	RefMsg(msg) >> ident;
#endif // JUMIN_DB_CRYPT

	if(
#ifdef LC_KOR
		!( m_proSite.Length() > 0 && ( strcmp(m_proSite, "IT") == 0 || strcmp(m_proSite, "B1") == 0 ) ) &&
#endif
#ifdef JUMIN_DB_CRYPT
		strcmp(this->m_idname, uid) != 0 )
#else //JUMIN_DB_CRYPT
		strcmp(this->m_ident, ident) != 0 )
#endif // JUMIN_DB_CRYPT
	{
		CNetMsg::SP rmsg(new CNetMsg);
		FailMsg(rmsg, MSG_FAIL_WRONG_IDENTIFICATION);
		SEND_Q(rmsg, this);
		return false;
	}
#endif

	char bCancelDelete = 0;
	RefMsg(msg) >> bCancelDelete;

	int guildoutdate = 0;
#if defined (LC_GAMIGO)
	if (!bCancelDelete)
	{
		time_t t;
		guildoutdate = time(&t) / 60 / 60 / 24;
	}
#endif

	if (bCancelDelete)
	{
		DBManager::instance()->PushCancelDeleteCharacter(this, char_index);
	}
	else
	{
		DBManager::instance()->PushDeleteCharacter(this, char_index, guildoutdate);
	}

	return true;
}

void CDescriptor::SetHackCheckPulse()
{
	m_hackCheckPulse = gserver->m_pulse;
	m_hackServerPulse = 0;
	m_hackClientPulse = 0;
	m_hackLastClientDiff = 0;
}

bool CDescriptor::CheckHackPulse(int clientPulse)
{
	// ���� ���̿� Ŭ���̾�Ʈ ���̰� 15�� �̻��̰ų�
	// Ŭ���̾�Ʈ�� ���̰� ���� Ŭ���̾�Ʈ�� ���̿� 30�ʰ� ��� �ȵǸ�(�޽��� ���� �������)

	m_hackCheckPulse = gserver->m_pulse;

	// ó�� ����ǰų�, 1�ð� ����� �� ����
	if (m_hackServerPulse < 1 || gserver->m_pulse - m_hackServerPulse > PULSE_HACK_PULSE_REFRESH)
	{
		m_hackServerPulse = gserver->m_pulse;
		m_hackClientPulse = clientPulse;
		return false;
	}

	int serverdiff = gserver->m_pulse - m_hackServerPulse;
	int clientdiff = clientPulse - m_hackClientPulse;
	int csdiff = clientdiff - serverdiff;

	bool bHack = false;

	// �ٰ˻� : ����-Ŭ���̾�Ʈ �ð� ���� �˻�
	if (csdiff > PULSE_HACK_PULSE_THRESHOLD)
	{
		if (m_pChar)
		{
			GAMELOG << init("HACK_PULSE", m_pChar)
					<< serverdiff
					<< delim
					<< clientdiff
					<< end;
		}
		else
		{
			GAMELOG << init("HACK_PULSE", m_idname)
					<< serverdiff
					<< delim
					<< clientdiff
					<< end;
		}
		bHack = true;
	}
	else if (ABS(m_hackLastClientDiff - clientdiff) < PULSE_HACK_CLIENT_THRESHOLD)
	{
		GAMELOG << init("HACK_PACKET", m_pChar)
				<< serverdiff
				<< delim
				<< clientdiff
				<< end;
		bHack = true;
	}

	if (bHack)
	{
		m_hackServerPulse = gserver->m_pulse;
		m_hackClientPulse = clientPulse;
		if (IncreaseHackCount(0))
			return true;
		else
			return false;
	}

	m_hackLastClientDiff = clientdiff;

	return false;
}

bool CDescriptor::IncreaseHackCount(int n)
{
	static const int limitHackCount = 20;
	int charIdx = 0;

	if (n <= 0)
		n = limitHackCount;

	m_hackCount += n;

	if (m_pChar)
	{
		charIdx = m_pChar->m_index;
		GAMELOG << init("HACK COUNT", m_pChar)
				<< m_hackCount
				<< end;
	}
	else
	{
		GAMELOG << init("HACK COUNT", m_idname)
				<< m_hackCount
				<< end;
	}

	if( m_hackCount >= limitHackCount )
	{

		LOG_ERROR("HACK COUNT is %d. limitHackCount is %d", m_hackCount, limitHackCount);
		
		gserver->saveHackCharacter((const char *)m_idname, charIdx);

		//this->Close("Hack Count");

		char tmpBuf[1024] = {0,};
		sprintf(tmpBuf, "HACK USERT %d - %d:%s:%s", gserver->m_serverno, gserver->m_subno, (const char *)m_idname, (m_pChar ? (const char *)m_pChar->m_name : "No Select Char") );
		{
			CNetMsg::SP rmsg(new CNetMsg);
			MsgrObserverMsg(rmsg, -1, -1, -1, -1, tmpBuf);
			SEND_Q(rmsg, gserver->m_messenger);
		}

		m_hackCount = 0;

		return true;
	}

	return false;
}
time_t CDescriptor::getExtendCharacterSlotTime() const
{
	return m_tExtendCharacterSlotTime;
}
void CDescriptor::setExtendCharacterSlotTime(const time_t _time)
{
	m_tExtendCharacterSlotTime = _time;
}

//////////////////////////////////////////////////////////////////////////

void CDescriptor::operate( rnSocketIOService* service )
{
	rnSocketIOServiceTcp* pServiceTcp =  dynamic_cast<rnSocketIOServiceTcp*>(service);

	{
		if (pServiceTcp->isCallCloseFunction())
		{
			return;
		}

		if (pServiceTcp->get_rqueue_size() > 100)
		{
			LOG_ERROR("HACKING? Too many read queue userIndex[%d] ", this->m_index);
			this->Close("Too many read queue.");

			return;
		}
	}

	CNetMsg::SP msg(service->GetMessage());

	if (msg->m_mtype == MSG_PULSE)
	{
		long sltime;
		char ubtvidx;
 #ifndef _WIN64
		float fTimedelay;
		float runspeed;
#else      
		FLOAT fTimedelay;
		FLOAT runspeed;
#endif 
		char attackspeed;
		char stage;
		long bExtension;
		long iCDvar;
		long iskillSpeed;

		RefMsg(msg) >>
			sltime >>
			ubtvidx >>
			fTimedelay >>
			attackspeed >>
			runspeed >>
			bExtension >>
			stage >>
			iCDvar >>
			iskillSpeed;

		try
		{
			if (stage == 6)
			{
				CPC* ch = this->m_pChar;
				if (this->m_pChar == NULL)
					return;

				bool hacked = true;
				
				//TODO SKILL SPEED 
				if (bExtension == true || bExtension == false)
				{
					hacked = false;
				}

				if (hacked)
				{
					if (this->m_pChar->m_Skill_hack < 3) {
						this->m_pChar->m_Skill_hack++;
					}
					else
					{
#ifdef KICKONHACK
						if (this->m_pChar->IncreaseHackCount(999))
							return;
#endif
					}
				}
				else
				{
					this->m_pChar->m_Skill_hack = 0;
				}

				//ATTACKSPEED DETECTION
				if (attackspeed != this->m_pChar->m_attackSpeed)
				{
					if (this->m_pChar->m_attackSpeed_hack < 4) {
						this->m_pChar->m_attackSpeed_hack++;
					}
					else
					{
#ifdef KICKONHACK
						if (this->m_pChar->IncreaseHackCount(999))
							return;
#endif
					}
				}
				else
				{
					this->m_pChar->m_attackSpeed_hack = 0;
				}

							//SKILLCD DETECTION
							// Use the same calculation as packet building to validate client's iCDvar
							int expectedCDvar = gserver->GetSkillCooldownValue(this->m_pChar->m_opDecreaseSkillDelay, this->m_pChar->m_skillCooltime, this->m_pChar);
							if (iCDvar != expectedCDvar)
							{
								if (this->m_pChar->m_skillcd_hack < 3)
								{
									this->m_pChar->m_skillcd_hack++;
								}
								else
								{
				#ifdef KICKONHACK
									if (this->m_pChar->IncreaseHackCount(999))
										return;
				#endif
								}
							}
							else
							{
								this->m_pChar->m_skillcd_hack = 0;
							}

				//SKILL SPEED DETECTION
				if (iskillSpeed != this->m_pChar->m_skillSpeed)
				{
					if (this->m_pChar->m_skillspeed_hack < 3)
					{
						this->m_pChar->m_skillspeed_hack++;
					}
					else
					{
#ifdef KICKONHACK
						if (this->m_pChar->IncreaseHackCount(999))
							return;
#endif
					}
				}
				else
				{
					this->m_pChar->m_skillspeed_hack = 0;
				}

				//RUNSPEED DETECTION
				char mountPet = 0;
				char colorType = 0;
				float trunspeed = this->m_pChar->m_runSpeed;

				if (ch->m_pZone->m_index == ZONE_DRATAN_CASTLE_DUNGEON)
				{
					CDratanCastle * pCastle = CDratanCastle::CreateInstance();
					if (pCastle->m_dvd.GetZone() && pCastle->m_dvd.GetEnvRate() >= 90)
					{
						trunspeed = trunspeed + trunspeed * 0.1;
					}
				}

				if (ch->m_wearInventory.wearItemInfo[WEARING_PET])
				{
					CPet* pet = ch->GetPet();
					if (pet)
					{
						if (pet->IsMount())
						{
							mountPet = pet->GetPetTypeGrade();
							trunspeed = pet->GetRunSpeed();
						}
					}
				}

				if (ch->IsSetPlayerState(PLAYER_STATE_FLYING))
					trunspeed = this->m_pChar->m_flySpeed;
				
				if (runspeed == 0)
					this->m_pChar->m_runSpeed_hack = 0;

				if (runspeed != trunspeed)
				{
					if (this->m_pChar->m_runSpeed_hack < 4)
					{
						this->m_pChar->m_runSpeed_hack++;
					}
					else
					{
#ifdef KICKONHACK
						if (this->m_pChar->IncreaseHackCount(999))
							return;
#endif
					}
				}
				else
				{
					this->m_pChar->m_runSpeed_hack = 0;
				}

			}

		}
		catch (int e)
		{
			return;
		}

		// alive packet
		return;
	}

	//if(msg->m_mtype != MSG_MOVE)
		//LOG_INFO("DEBUG_FUNC : START : mtype : %d", msg->m_mtype);

	switch(STATE(this))
	{
	case CON_PLAYING:
		{
			if (this->m_pChar == NULL)
			{
				LOG_ERROR("pChar is NULL but send command packet. userIndex[%d]", this->m_index);
				service->Close("pChar is NULL");
				return;
			}

			gserver->CommandInterpreter(this, msg);
		}
		break;

	//XX �α��� 1
	case CON_GET_LOGIN: // ���� �� ���� ����
		{
			if (gserver->isRunConnector() == false)
			{
				// Connect Server�� �������� ���� ���¿����� ��� �α��ε� ������� ����
				CNetMsg::SP rmsg(new CNetMsg);
				FailMsg(rmsg, MSG_FAIL_CONNECT_SERVER);
				SEND_Q(rmsg, this);

				this->Close("Not connect to ConnectServer");
				return;
			}

			bool ret_bool = this->GetLogin(msg);
			if (ret_bool)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ConnLoginMsg(rmsg, this);
				SEND_Q(rmsg, gserver->m_connector);

				STATE(this) = CON_WAIT_IDEN_MSG; // ���� ��û ��� ���� ��ȯ
				DescManager::instance()->insert(this);
			}
			else
			{
				this->Close("login error"); // �α��� �� ������ �߻��Ͽ� ���� ó���� �Ѵ�.
				return;
			}
		}
		break;

	case CON_PREPARE_PLAY:
		{
			if (msg->m_mtype != MSG_START_GAME)
			{
				LOG_ERROR("HACKING? : invalid command[%d]. userIndex[%d]", msg->m_mtype, this->m_index);
				this->Close("invalid command");
				return;
			}

			sendData_StartAndMoveZone();
		}
		break;

	case CON_PREPARE_PLAY_BEFORE:
		{
			if (msg->m_mtype == MSG_START_GAME)
				this->m_connected = CON_PREPARE_PLAY;
		}
		break;

	case CON_WAIT_IDEN_MSG: // Connect server���� ���� ��û�� �� �����̹Ƿ� Ŭ���̾�Ʈ�� ��� ��Ŷ�� ������ �ȵ�
		{
			LOG_ERROR("Invalid packet. type[%d] / now is waiting login. user_index[%d]", msg->m_mtype, this->m_index);
			this->Close("Invalid packet. now is waiting login");
			return;
		}
		break;

	case CON_GET_IDEN_MSG: // Connect server�� ���� ������ �� ����
		{
			// Ŭ���̾�Ʈ�� ĳ���� ����â
			// �̰����� ĳ���� ����/����/�������� ó���� ������
			msg->MoveFirst();
			unsigned char subtype = 0;
			RefMsg(msg) >> subtype;

			switch (msg->m_mtype)
			{
			case MSG_MENU:
				switch (subtype)
				{
				case MSG_MENU_NEW:
					this->CharNew(msg);
					break;
				case MSG_MENU_DEL:
					this->CharDel(msg);
					break;
				case MSG_MENU_START:
					this->StartGame(msg);
					break;
				case MSG_RETURN_TO_SELECT_CHANNEL:
					{
						CNetMsg::SP rmsg(new CNetMsg);
						ConnLogoutMsg(rmsg, this->m_idname);
						SEND_Q(rmsg, gserver->m_connector);
						LOG_INFO("send logout msg to Connector : user_index[%d] id[%s]", this->m_index, (const char *)(this->m_idname));
					}
					{
						CNetMsg::SP rmsg(new CNetMsg);
						pTypeBase* packet = reinterpret_cast<pTypeBase*>(rmsg->m_buf);
						packet->type = MSG_MENU;
						packet->subType = MSG_RETURN_TO_SELECT_CHANNEL;
						rmsg->setSize(sizeof(pTypeBase));
						SEND_Q(rmsg, this);
					}
					break;
				default:
					{
						LOG_ERROR("Invalid packet. type[%d] / subtype[%d] / now is character select screen. user_index",
								  msg->m_mtype, subtype, this->m_index);
						this->Close("Invalid packet. now is waiting login");
						return;
					}
					break;
				}
				break;

			case MSG_START_GAME:
				{
					// DB thread���� �����͸� �� ���� ���� ���¿��� Ŭ���̾�Ʈ�� ��Ŷ�� �������� �����
					this->request_start_game_flag_ = true;

					if (this->m_pChar != NULL)
					{
						sendData_StartAndMoveZone();
					}
				}
				break;
			case MSG_UI:
				break;
			default:
				{
					LOG_ERROR("Invalid packet. type[%d] / now is character select screen. user_index",
							  msg->m_mtype, this->m_index	);
					//this->Close("Invalid packet. now is character select screen");
					GAMELOG << init("INVALID_PACKET")
					<< "user_index" << delim
					<< this->m_index << delim
					<< end;
					return;
				}
				break;
			}
		}
		break;

	case CON_GET_DUMMY:
		{
			// �� ���´� Ŭ���̾�Ʈ�� ĳ���� ����â���� ���ư��� �߻���
			// ������ ���۸� �Ǿ��ִ� �Ϲ� ��Ŷ�� ó���ϱ� ����
			// �� �۾��� ���� ������ ������ �߸��� ��Ŷ���� �����Ͽ� Ŭ���̾�Ʈ�� �����ϰԵ�

			msg->MoveFirst();

			int subtype;
			char flag;

			RefMsg(msg) >> subtype >> flag;
			if (subtype == MSG_EX_RESTART && flag == 1)
			{
				STATE(this) = CON_GET_IDEN_MSG;
			}
		}
		break;

	default:
		break;
	}
	
	//if(msg->m_mtype != MSG_MOVE)
		//LOG_INFO("DEBUG_FUNC : END : mtype : %d", msg->m_mtype);
}

void CDescriptor::onClose( rnSocketIOService* service )
{
	if (DescManager::instance()->getDescByUserIndex(this->m_index))
	{
		gserver->CloseSocket(this);
		DescManager::instance()->erase(this);
	}

	service_ = NULL;

	delete this;

	bnf::instance()->RemoveSession(service);
}

void CDescriptor::Close( std::string errmsg )
{
	STATE(this) = CON_DISCONNECT;		// desc�� ���¸� �����Ͽ� ServerTimerPerSecond::operate()������ �۵��� ���� ���ϵ��� ��
	this->service_->Close(errmsg);
}

void CDescriptor::makeAutoSaveSequence( CDescriptor* desc )
{
	++static_auto_save_sequence;
	static_auto_save_sequence %= AUTO_SAVE_SEQUENCT;

	desc->m_autoSaveSeq = static_auto_save_sequence;

	auto_set[desc->m_autoSaveSeq].insert(desc);
}

void CDescriptor::sendData_StartAndMoveZone()
{
	STATE(this) = CON_PLAYING;

	gserver->CharPrePlay(this);

	this->m_pChar->m_TimerItem.sendListToClient();
	this->m_pChar->m_petStashManager.SendPetStashList();
	DBManager::instance()->PushExpressExist(this, EXPRESS_SEND_TYPE_LOGIN);	// â��NPC���� ������(�Ǵ� ��)�� �ִ��� Ȯ����
	DBManager::instance()->pushSendAnyInfoAfterLogin(this);

	GAMELOG << init("CHAR_LOAD", this->m_idname)
			<< "NAME" << delim
			<< this->m_pChar->m_name << delim
			<< "NICK" << delim
			<< this->m_pChar->m_nick << delim
			<< "JOB" << delim
			<< this->m_pChar->m_job << delim
			<< "LEVEL" << delim
			<< this->m_pChar->m_level << delim
			<< "EXP" << delim
			<< this->m_pChar->m_exp << delim
			<< "MONEY" << delim
			<< this->m_pChar->m_inventory.getMoney()
			<< end;

	{
		// ���� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		CastleOwnerInfoMsg(rmsg);
		SEND_Q(rmsg, this);
	}

	{
		// �����Ϳ� ��Ȯ�� �� ��ȣ�� �����ϰ� �÷��� ���¸� playing���� �����Ѵ�
		CNetMsg::SP rmsg(new CNetMsg);
		ConnPlayingMsg(rmsg, this, MSG_LOGIN_NEW);
		SEND_Q(rmsg, gserver->m_connector);
	}

#ifdef STASH_PASSWORDS
	{
		// â�� �н����� ���� ����
		unsigned char flag = (this->m_pChar->m_stash_password.empty()) ? 0 : 1;
		CNetMsg::SP rmsg(new CNetMsg);
		UpdateClient::makeStashPasswordFlag(rmsg, flag);
		SEND_Q(rmsg, this);
	}
#endif

#ifdef LC_KOR
	if (m_pChar->m_admin == 10)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		GMWhoAmIMsg(rmsg, m_pChar);
		SEND_Q(rmsg, this);
	}
#else
	if (m_pChar->m_admin >= 1)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		GMWhoAmIMsg(rmsg, m_pChar);
		SEND_Q(rmsg, this);
	}
#endif
	{
		bool bapply;
		CSkill* skill = gserver->m_skillProtoList.Create(IMMOTAL_BUF);
		ApplySkill(m_pChar, m_pChar, skill, -1, bapply);

		//�����ϱ��� ���� false��
		m_pChar->m_bFirstDoIt = false;
		//*���� ����
	}

	if(m_pChar->getSyndicateType() != 0)
	{
		//���� ������ �����ش�.
		m_pChar->m_syndicateManager.send();
	}

	//Ż��� �ʿ��� �� ���� ����(�޶��...)
	sendSyndicateOutNeedNasInfo();

	//gps ���� ������Ʈ
	CGPSDataManager::instance()->_update(m_pChar);

	if(m_pChar->m_gpsManager.isGps() == true )
	{
		m_pChar->m_gpsManager.sendTargetInfo();
	}
	if (m_pChar->m_pArea->m_zone->m_index == ZONE_RLGL) //RLGL
    {
        gserver->m_RLGL.SendMenu(m_pChar, m_pChar->m_admin);

        gserver->m_RLGL.SendTimer(m_pChar, gserver->m_RLGL.m_ieventstart + 60);

        gserver->m_RLGL.SendMenuTab(m_pChar, 0);

    }
	if (m_pChar->m_pArea->m_zone->m_index == ZONE_ALTER_OF_DARK || m_pChar->m_pArea->m_zone->m_index == ZONE_CAPPELLA_1 || m_pChar->m_pArea->m_zone->m_index == ZONE_AKAN_TEMPLE
		|| m_pChar->m_pArea->m_zone->m_index == ZONE_TARIAN_DUNGEON || m_pChar->m_pArea->m_zone->m_index == ZONE_ENCHANTED_DUNGEON
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
#ifndef CLOUD_EXPEDITION_SOLO_DUNGEONS
		|| m_pChar->m_pArea->m_zone->m_index == ZONE_PARTY_DUNGEON0
		|| m_pChar->m_pArea->m_zone->m_index == ZONE_PARTY_DUNGEON1
		|| m_pChar->m_pArea->m_zone->m_index == ZONE_PARTY_DUNGEON2
		|| m_pChar->m_pArea->m_zone->m_index == ZONE_PARTY_DUNGEON3
		|| m_pChar->m_pArea->m_zone->m_index == ZONE_PARTY_DUNGEON4
#endif
#endif					
		)
	{
		//�ε��� ������ ���� �ϸ� �̵��� ī��Ʈ�� 1���ҽ����ش�.
		m_pChar->m_pArea->m_inCount--;
		//������ �̵��� ������
		m_pChar->bMoveInsDunFinish = true;
	}

	if (gserver->isRunSubHelper())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		RequestClient::makeMailBoxUpdateMessage(rmsg, m_pChar->m_index);
		SEND_Q(rmsg, gserver->m_subHelper);
	}
	m_pChar->m_itemCollectionManager.sendDoingInfo();
	m_pChar->m_itemCollectionManager.sendFinishInfo();
	m_pChar->m_attendanceManager.checkAttendance();
	m_pChar->m_arti_gpsManager.sendGpsOwnerCountInfo();

	//���� �����ڰ� �̵��ϴ� ��� üũ
	if(ArtifactManager::instance()->isOwnerPC(m_pChar->m_index))
	{
		m_pChar->CalcStatus(true);

		if(m_pChar->m_party != NULL)
		{
			m_pChar->m_party->updateCalcMember();
		}
	}
	else if(m_pChar->m_party != NULL
		&& ArtifactManager::instance()->isArtifactParty(m_pChar->m_party) == true)
	{
		m_pChar->CalcStatus(true);
	}
	
	if(m_pChar->m_guildInfo != NULL)
	{
		if( gserver->isRunHelper() )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			HelperNewGuildSkillList( rmsg, m_pChar );
			SEND_Q( rmsg, gserver->m_helper );
		}
	}

	{
		std::map<int, MAKE_TITLE*>::iterator it = m_pChar->_map_title.find(m_pChar->m_custom_title_index);
		if(it != m_pChar->_map_title.end())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			TitleUserInfoMsg(rmsg, m_pChar->m_index, it->second->color, it->second->background_color, it->second->effect, it->second->name);
			m_pChar->m_pArea->SendToCell(rmsg, m_pChar, true);
		}
	}

	if(m_pChar->m_firstSendData == true)
	{
		{
			m_pChar->m_desc->sendStartData();
		}

		{
			if ( m_pChar->GetMapAttr() & MATT_WAR || m_pChar->GetMapAttr() & MATT_UNWALKABLE)
			{
				if( ApplyWarSkill(m_pChar, m_pChar->m_pZone->m_index) == false )
				{
					ClearWarSkill(m_pChar);
				}
			}
			else
			{
				ClearWarSkill(m_pChar);
			}
		}

		{
			CDratanCastle * pCastle = CDratanCastle::CreateInstance();
			if(pCastle->GetOwnerCharIndex() == m_pChar->m_index)
			{
				if(pCastle->m_dvd.GetOwnerMode() == false)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					DVDDungeonChangeToOwnerMsg(rmsg);
					SEND_Q(rmsg, this);
				}
			}
		}

		{
			PopupNotice::instance()->SendDataForUser(m_pChar);
		}

		if(m_pChar->_map_title.empty() == false)
		{
			std::map<int, MAKE_TITLE*>::iterator it = m_pChar->_map_title.begin();
			std::map<int, MAKE_TITLE*>::iterator it_end = m_pChar->_map_title.end();

			int _a = m_pChar->_map_title.size() / 10;

			for( int i = 0; i <= _a;  i++)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				UpdateClient::TitleSystemMakeList* packet = reinterpret_cast<UpdateClient::TitleSystemMakeList*>(rmsg->m_buf);
				packet->type = MSG_EXTEND;
				packet->subType = MSG_EX_TITLE_SYSTEM;
				packet->thirdType = MSG_EX_TITLE_SYSTEM_TITLE_MAKE_INFO_LIST;
				int count = 0;

				for(; it != it_end;)
				{
					packet->info[count].custom_title_index = it->second->title_index;
					strncpy(packet->info[count].name, it->second->name, CUSTOM_TITLE_NAME_LENGTH);
					packet->info[count].color = (int)it->second->color;
					packet->info[count].background = (int)it->second->background_color;
					packet->info[count].effect = (int)it->second->effect;

					for(int i = 0 ; i < MAX_TITLE_OPTION; i++)
					{
						packet->info[count].option_index[i] = it->second->option_index[i];
						packet->info[count].option_level[i] = it->second->option_level[i];
					}

					count++;
					it++;

					if(count != 0 && count % 10 == 0)
						break;
				}
				
				if (count == 0)
					break;

				packet->count = count;
				rmsg->setSize(sizeof(UpdateClient::TitleSystemMakeList) + sizeof(TitleSystemMakeInfo) * count);
				SEND_Q(rmsg, m_pChar->m_desc);
			}
		}

		if(m_pChar->m_ep > 0)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			UpdateClient::EPInitMsg(rmsg, false);
			SEND_Q(rmsg, m_pChar->m_desc);
		}

		m_pChar->m_firstSendData = false;
	}
}

void CDescriptor::returnToCharacterSelectMode()
{
	{
		// Helper, SubHelper���� ���� ������ ����
		CNetMsg::SP rmsg(new CNetMsg);
		ServerToServerPacket::makeLogoutUserInfo(rmsg, this->m_index);
		SEND_Q(rmsg, gserver->m_helper);
		SEND_Q(rmsg, gserver->m_subHelper);
	}

	this->m_pChar->ProcDisconnect(true, false);
	DBManager::instance()->SaveCharacterInfo(this, false);

	{
		// �޸𸮿��� ĳ���� ����
		auto_set[m_autoSaveSeq].erase(this);

		// Don't delete offline vendors
		if (!(this->m_pChar->m_personalshop && this->m_pChar->m_personalshop->IsOfflineMode()))
		{
			PCManager::instance()->deletePlayerByPC(this->m_pChar);
			delete this->m_pChar;
		}
		else
		{
#ifdef OFFLINE_SHOPS
			// Keep CPC alive as offline vendor. Detach from descriptor so nothing
			// tries to write packets to the closing socket, and remove from the
			// live-player manager so name/index lookups don't treat it as online.
			if (this->m_pChar->m_personalshop && this->m_pChar->m_personalshop->IsOfflineMode())
			{
				CPC* vendor = this->m_pChar;
				PCManager::instance()->deletePlayerByPC(vendor);
				vendor->m_desc = NULL;

				// Register the headless CPC in the offline vendor registry so that
				// RestoreOfflineShopOnLogin can find and evict it when the real
				// owner logs back in (prevents duplicate character in the world).
				int vendorShopId = vendor->m_personalshop->GetShopId();
				if (vendorShopId > 0)
				{
					boost::recursive_mutex::scoped_lock lock(gserver->m_offlineVendorRegistryMutex);
					gserver->m_offlineVendorRegistry[vendorShopId] = vendor;
				}

				LOG_INFO("returnToCharacterSelectMode: Keeping offline vendor alive (char_index: %d, shop_id: %d)",
					vendor->m_index, vendorShopId);
			}
#endif
		}

		this->m_pChar = NULL;
	}

	{
		// ���� ���¸� ��Ŷ ���� ���·� ����
		STATE(this) = CON_GET_DUMMY;
		DBManager::instance()->PushCharacterList(this); // DBManager�� ĳ���� ����Ʈ������ ��û��
	}
}

#ifdef HARDCORE_SERVER
void CDescriptor::Make_1_Level()
{
	CPC* ch = this->m_pChar;

	// ��������϶��� 1������ ���ư��� ����
	if (ch->IsSetPlayerState(PLAYER_STATE_RAMODE))
		return;

	GAMELOG << init("HARDCORE : char is die.", ch) << "Level : " << ch->m_level << end;

	// ������������ LCE�� ����
	ch->m_wearInventory.sendToLCE_Only_hardcore();

	// ���� �ʱ�ȭ
	boost::scoped_ptr<CPC> t_pChar(new CPC);
	t_pChar->m_job = ch->m_job;
	t_pChar->m_level = ch->m_level = 1;
	if( t_pChar->m_job == JOB_NIGHTSHADOW )
	{
		t_pChar->m_level = 90;
		t_pChar->m_job2	= JOB_2ND_NIGHTSHADOW;
		t_pChar->m_statpt_remain = 236;
	}
	t_pChar->InitStat();
	t_pChar->CalcStatus(false);

	ch->m_level = t_pChar->m_level;
	ch->m_str = t_pChar->m_str;
	ch->m_dex = t_pChar->m_dex;
	ch->m_int = t_pChar->m_int;
	ch->m_con = t_pChar->m_con;
	ch->m_dbHP = t_pChar->m_dbHP;
	ch->m_hp = t_pChar->m_dbHP;
	ch->m_dbMP = t_pChar->m_dbMP;
	ch->m_mp = t_pChar->m_dbMP;
	ch->m_job2 = t_pChar->m_job2;
	ch->m_statpt_str = t_pChar->m_statpt_str;
	ch->m_statpt_dex = t_pChar->m_statpt_dex;
	ch->m_statpt_con = t_pChar->m_statpt_con;
	ch->m_statpt_int = t_pChar->m_statpt_int;
	ch->m_statpt_remain = t_pChar->m_statpt_remain;
	ch->m_etcEvent = 0;

	ch->m_exp = 0;
	ch->m_skillPoint = 0;
	ch->m_pkCount = 0;
	ch->m_pkPenalty = 0;
	ch->m_pkRecoverPulse = 0;
	ch->m_pkmodedelay = 0;
	ch->m_pkPenaltyHP = 0;
	ch->m_pkPenaltyMP = 0;
	ch->m_pkRecoverNPCCount = 0;
	ch->CalcStatus(false);

	// ����ġ �ʱ�ȭ
	ch->m_fame = 0;
	ch->m_GuildFame = 0;
	ch->m_GuildExp = 0;

	// ��ų �ʱ�ȭ
	ch->m_activeSkillList.Clear();
	ch->m_passiveSkillList.Clear();
	ch->m_etcSkillList.Clear();
	ch->m_sSkillList.Init();
	ch->m_skillPoint = 0;
	if( ch->m_job != JOB_NIGHTSHADOW )
		ch->m_job2 = 0;

	// ������ �ʱ�ȭ
	for (int i = 0; i < QUICKSLOT_PAGE_NUM; ++i)
	{
		ch->m_quickSlot[i].clear();
	}

	// PK ���� �ʱ�ȭ
	ch->m_pkPenalty = 0;
	ch->m_pkCount = 0;
	ch->m_pkRecoverPulse = 0;
	ch->m_pkPenaltyHP = 0;
	ch->m_pkPenaltyMP = 0;

	ch->CalcStatus(false);

	// ���� �ʱ�ȭ
	ch->m_sealSkillList.Clear();
	for (int i = 0; i < MAX_SEAL_TYPE_SKILL; ++i)
	{
		ch->m_sealSkillExp[i].nSkillIdx = -1;
		ch->m_sealSkillExp[i].llExp = 0;
	}
	ch->m_listFactory.clear();

	// ģȭ�� �ʱ�ȭ
	ch->m_affinityList.clear();

	// ����Ʈ �ʱ�ȭ
	ch->m_inventory.deleteAllQuestItem();
	ch->m_questList.clear();

	// ���� ������ �ʱ�ȭ
	ch->m_pd3Count = 0;
	ch->m_pd3Time = 0;
	ch->m_pd4Count = 0;
	ch->m_pd4Time = 0;

	// ȣĪ �ʱ�ȭ
	ch->m_nCurrentTitle = TITLE_SYSTEM_NO_TITLE;
	if (ch->m_titleList.m_head != NULL)
	{
		std::string tstr = boost::str(boost::format("DELETE FROM t_titlelist WHERE a_char_index = %d") % ch->m_index);
		DBManager::instance()->pushQuery(ch->m_desc->m_index, tstr);
	}
	
	if (ch->_map_title.empty() == false)
	{
		std::string tstr = boost::str(boost::format("DELETE FROM t_title_make WHERE a_char_index = %d") % ch->m_index);
		DBManager::instance()->pushQuery(ch->m_desc->m_index, tstr);

		std::map<int, MAKE_TITLE*>::iterator it = ch->_map_title.begin();
		std::map<int, MAKE_TITLE*>::iterator it_end = ch->_map_title.end();

		for(; it != it_end; it++)
		{
			delete[] it->second->option_index;
			delete[] it->second->option_level;
			delete it->second;
		}

		ch->_map_title.clear();
	}

	// ������ ó��
	if (ch->m_Exped != NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpedQuitReqMsg(rmsg, ch->m_Exped->GetBossIndex(), ch->m_index, MSG_EXPED_QUITMODE_NORMAL);
		SEND_Q(rmsg, gserver->m_helper);

		ch->m_Exped = NULL;
	}

	// ��Ƽ ó��
	if (ch->m_party != NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyQuitReqMsg(rmsg, ch->m_party->GetBossIndex(), ch->m_index);
		SEND_Q(rmsg, gserver->m_helper);
	}

	{
		// Ŭ���̾�Ʈ�� restart MSG ����
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeExRestart(rmsg, 1);
		SEND_Q( rmsg, ch->m_desc );
	}

	this->returnToCharacterSelectMode();
}
#endif

void CDescriptor::sendSyndicateOutNeedNasInfo()
{
	CNetMsg::SP rmsg(new CNetMsg);
	UpdateClient::makeUpdateSyndicateOutNeedNas(rmsg, SYNDICATE_OUT_NEEDNAS);
	SEND_Q(rmsg, this);
}

void CDescriptor::sendStartData()
{
	//�⼮ Ȯ��
	//���� ������ ������� ���
	if(m_pChar->m_assist.FindBySkillIndex(1771) != 0)
	{
		//���� ���� ��Ŷ
		CNetMsg::SP rmsg(new CNetMsg);
		UpdateClient::makeAttendanceAssureCancelOkMsg(rmsg);
		SEND_Q(rmsg, m_pChar->m_desc);
	}

	m_pChar->m_attendanceManager.sendSysMsg();
	gserver->m_eventAutomationMgr.sendEventList(m_pChar);
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CheckNoticeMsg(rmsg, Notice::instance()->getLastRev());
		SEND_Q(rmsg, m_pChar->m_desc);
	}
}
