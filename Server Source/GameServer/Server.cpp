#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <boost/foreach.hpp>
#include "stdhdrs.h"

#include "gameserver_config.h"
#include "Log.h"
#include "Exp.h"
#include "Server.h"
#include "Character.h"
#include "Descriptor.h"
#include "Cmd.h"
#include "CmdMsg.h"
#include "../ShareLib/DBCmd.h"
#include "doFunc.h"
#include "doFuncPersonalShopDB.h"
#include "Battle.h"
#include "WarCastle.h"
#include "DratanCastle.h"
#include "LuckyDrawBox.h"
#include "WearInvenManager.h"
#include "../ShareLib/rnsocketioserviceTcp.h"
#include "../ShareLib/packetType/ptype_server_to_server.h"
#include "../ShareLib/packetType/ptype_old_do_item.h"
#include "../ShareLib/packetType/ptype_char_status.h"
#include "../ShareLib/packetType/ptype_old_mempos.h"
#include "../ShareLib/packetType/ptype_old_do_action.h"
#include "../ShareLib/packetType/ptype_old_do_skill.h"
#include "../ShareLib/packetType/ptype_old_do_move.h"
#include "../ShareLib/packetType/ptype_old_do_sskill.h"
#include "../ShareLib/packetType/ptype_old_do_title.h"

#include "TitleSystem.h"
#include "RaidData.h"
#include "MonsterMercenary.h"
#include "WarGround.h"
#ifdef GER_LOG
#include <stdlib.h>
#endif // GER_LOG
#include "GMCmdList.h"
#include "DBManager.h"
#include <thread>
#include <chrono>
#include <vector>
#include "itemExchangeProto.h"
#include "HolyWaterData.h"
#include "EquipExchangeExtend.h"
#include "ItemCollection.h"
#include "Notice.h"
#include "Artifact_Manager.h"
#include "GuildBattleManager.h"
#include "CloudThings.h"
#include "GMCommandListener.h"
#include "RezasFunction.h"
#include <inttypes.h>
#include "SkillUseLog.h"
// DescManager���� userIndex�� ����ũ�ϰ� ������ �ؾ��ϴµ�
// ���� ���ӽÿ��� userIndex�� ������ ���̰��� �־��ְ�
// Connector�� ���� �������� ������ �ٲپ��ش�.
// ������ �ִ�ġ�� -2147483647���� -1�� ���� 2147483647�� ��
static int local_dummy_user_index = 0;

CServer* gserver = NULL;
CCmdList gcmdlist;
CCmdList gexcmdlist;

bool    g_bUpgradeEvent;
int		g_nUpgradeProb;

void ServerSrandom(unsigned long initial_seed);

bool IsApllyDebuffSkilltoNPC(CPC* aPc, CNPC* tNpc); // ����Ʈ ������ ��ų #764,765 ��ų �� ���� �뺴�� ������� �ʵ��� ����ó��.

static LONGLONG local_seq_index = 0;

CServer::CServer()
	: m_serverAddr(HOST_LENGTH + 1)
	, m_dbcastle(m_dbchar)
	, m_dbcharingame(m_dbchar)
	, m_dbTrigger(m_dbchar)

#ifdef IMP_SPEED_SERVER
	, m_bSpeedServer(false)
#endif //IMP_SPEED_SERVER
{
	m_serverpath = GetServerPath();
	m_serverno = -1;
	m_subno = -1;
	m_maxplayers = 0;
	m_nameserverisslow = true;
	m_bShutdown = false;

	m_pulseReboot = -1;
	m_pulseShutdown = -1;
	m_pulseEndGame = -1;

	m_bLoop = 0;
	m_descLoop = NULL;
	m_observer = NULL;
	memset(m_chatmonitor, 0, sizeof(CDescriptor*) * 20);

#ifdef GMTOOL
	m_gmtool = NULL;
#endif // GMTOOL

	m_nowseconds = time(0);
	m_pulse = 0;

	m_resetWeather = 0;
	m_resetAdjustItem = 0;

	mysql_init(&m_dbchar);
	mysql_init(&m_dbdata);
	mysql_init(&m_dbauth);

#ifdef USE_TENTER_BILLING
	mysql_init(&m_dbcatal);
#endif

	m_numZone = 0;
	m_zones = NULL;

	m_clientversionMin = 0;
	m_clientversionMax = 0;

	memset(m_pulseRankRefresh, 0, sizeof(m_pulseRankRefresh));

	m_bDoubleEvent = false;

#ifdef DOUBLE_PET_EXP_AUTO
	m_tPetExpEventStart = -1;
	m_tPetExpEventEnd = -1;
#endif
#ifdef UPGRADE_EVENT_AUTO
	m_tUpgradeEventStart = -1;
	m_tUpgradeEventEnd = -1;
#endif
#ifdef NEW_DOUBLE_GM_ZONE
	m_bDoubleEventZone = -1;
#endif // NEW_DOUBLE_GM_ZONE

	for (int i = 0; i < 3; i++)
	{
		m_nGuildMarkTable[i] = 0;
	}



#ifdef DOUBLE_PET_EXP
	m_bDoublePetExpEvent = false;
	m_PetExpPercent = 100;
#endif // DOUBLE_PET_EXP

	m_bDoubleNasPercent = DEFAULT_NAS_PERCENT;
	m_bDoubleNasGetPercent = DEFAULT_NAS_GET_PERCENT;
	m_bDoubleExpPercent = DEFAULT_EXP_PERCENT;
	m_bDoubleSpPercent = DEFAULT_SP_PERCENT;
	m_bDoubleProducePercent = DEFAULT_PRO_PERCENT;
	m_bDoubleProduceNum = DEFAULT_PRO_GET_NUMBER;
#ifdef NEW_DOUBLE_GM_AUTO
	m_bDoubleNasPercentBackup = DEFAULT_NAS_PERCENT;
	m_bDoubleNasGetPercentBackup = DEFAULT_NAS_GET_PERCENT;
	m_bDoubleExpPercentBackup = DEFAULT_EXP_PERCENT;
	m_bDoubleSpPercentBackup = DEFAULT_SP_PERCENT;
	m_bDoubleProducePercentBackup = DEFAULT_PRO_PERCENT;
	m_bDoubleProduceNumBackup = DEFAULT_PRO_GET_NUMBER;
	memset(m_iDoubleGMStart, -1, sizeof(m_iDoubleGMStart));
	memset(m_iDoubleGMEnd, -1, sizeof(m_iDoubleGMEnd));
	m_bIsDEtime = false;
#endif // NEW_DOUBLE_GM_AUTO

#ifdef NEW_DOUBLE_EVENT_AUTO_TIME
	memset(m_iDoubleEventStart, -1, sizeof(m_iDoubleEventStart));
	memset(m_iDoubleEventEnd, -1, sizeof(m_iDoubleEventEnd));
#endif // NEW_DOUBLE_EVENT_AUTO_TIME
#ifdef EVENT_ITEMDROP_AUTO
	m_bIsItemdrop = false;
	memset(m_iEventItemdropStart, -1, sizeof(m_iEventItemdropStart));
	memset(m_iEventItemdropEnd, -1, sizeof(m_iEventItemdropEnd));
#endif // EVENT_ITEMDROP_AUTO

#ifdef GER_LOG
	m_hostname = NULL;
#endif // GER_LOG

#ifdef EVENT_DROPITEM
	m_bDropItem = false;
	m_bDropItemNpcIdx = -1;
	m_bDropItemIdx = -1;
	m_bDropProb = 0;
#endif // EVENT_DROPITEM

	m_CollectBugEventPercent = 10;

	m_bDoubleExpEvent = false;
	m_expPercent = 100;
	m_bLattoEvent = false;
	m_bNewYearEvent = false;
	m_bValentineEvent = false;

	m_nItemDropEventRate = 100;
#ifdef EVENT_ITEMDROP_AUTO
	m_nItemDropEventRateBackup = 100;
#endif

	m_itemDropProb = 100;
	m_moneyDropProb = 100;
	m_skillCooldownPvpPercent = 100;  // Default 100% = full opDecreaseSkillDelay in PVP
	m_skillCooldownPvePercent = 100;  // Default 100% = full opDecreaseSkillDelay in PVE

	m_statisticsItemBuy = 0;
	m_statisticsItemSell = 0;
	m_statistics152 = 0;
	m_statistics153 = 0;
	m_statistics154 = 0;
	m_statistics155 = 0;
	m_statistics156 = 0;
	m_statistics157 = 0;
	m_statistics158 = 0;
	m_statistics159 = 0;
	m_statistics160 = 0;
	m_statistics161 = 0;
	m_statistics162 = 0;
	m_statistics163 = 0;
	m_statistics197 = 0;
	m_statistics198 = 0;
	m_statistics199 = 0;

	m_taxItem = 0;
	m_taxProduceCastle = 0;
	m_taxSavePulse = 0;
	m_taxDivGuild = -1;

	m_taxItemDratan = 0;
	m_taxProduceCastleDratan = 0;

	m_taxProduceAkan = 0;
	m_taxProduceTrivia = 0;

	m_unEventXmasTreePoint = 0;

	m_bEventOX = false;

	m_bRecommend = false;
	m_pulseRecommendMoonstone = m_pulse;

	#ifdef OFFLINE_SHOPS
	// Initialize offline shop cleanup pulse timer
	m_pulseOfflineShopCleanup = m_pulse;
#endif

#if defined (LC_TLD)
	m_national = LC_TLD;
#elif defined (LC_USA)
	m_national = LC_USA;
#elif defined (LC_BRZ)
	m_national = LC_BRZ;
#elif defined (LC_GER)
	m_national = LC_GER;
#elif defined (LC_SPN)
	m_national = LC_SPN;
#elif defined (LC_FRC)
	m_national = LC_FRC;
#elif defined (LC_PLD)
	m_national = LC_PLD;
#elif defined (LC_RUS)
	m_national = LC_RUS;
#elif defined (LC_TUR)
	m_national = LC_TUR;
#elif defined (LC_ITA)
	m_national = LC_ITA;
#elif defined (LC_MEX)
	m_national = LC_MEX;
#elif defined (LC_UK)
	m_national = LC_UK;
#else
	m_national = LC_KOR;
#endif

	m_bpSiteGive = false;
	m_bpSiteCount = 300;

	m_bLoadPartyInfo = false;

	m_pulseProcHeartBeatPerSec = 0;

	m_bNonPK = false;

#ifdef FREE_PK_SYSTEM
	m_bFreePk = false;
#endif

#ifdef MAL_DISABLE_PKPENALTY
	m_bDisablePKPaenalty = false;
#endif //MAL_DISABLE_PKPENALTY

#ifdef DOUBLE_ITEM_DROP
	m_bDoubleItemEvent = false;
	m_bDoubleItemPercent = 0;
#endif	// DOUBLE_ITEM_DROP

	m_nExpLimit = DEFAULT_LIMIT_EXP;
	m_nSpLimit = DEFAULT_LIMIT_EXP;
#ifdef GM_EXP_LIMIT_AUTO
	m_bExpLimit = false;
	m_nExpLimitStart = DEFAULT_LIMIT_EXP;
	m_nExpLimitEnd = DEFAULT_LIMIT_EXP;
	m_nSpLimitStart = DEFAULT_LIMIT_EXP;
	m_nSpLimitEnd = DEFAULT_LIMIT_EXP;
	memset(m_nGMExpLimitStart, -1, sizeof(m_nGMExpLimitStart));
	memset(m_nGMExpLimitEnd, -1, sizeof(m_nGMExpLimitEnd));
#endif // GM_EXP_LIMIT_AUTO

	m_comboZone = NULL;

#ifdef NEW_DOUBLE_EVENT_AUTO
	m_bDoubleEventAuto = true;
	m_bDoubleEventAutoOn = false;
#endif // NEW_DOUBLE_EVENT_AUTO

	g_nUpgradeProb = 100;
	g_bUpgradeEvent = false;

	for (int j = 0; j < 24; j++)
	{
		if ((j == 0) || (j % 3 == 0))
			m_bTimeTable[j] = true;
		else
			m_bTimeTable[j] = false;
	}
	m_iTimeInterval = 1;
	m_iStartTime = -1;
	m_iEndTime = -1;
	m_bDungeonTimeToggle = true;
	m_bIsTime = false;
	m_iZoneCount = 0;

	m_tRealSystemTime = NOW();
	m_bCashShopLock = false;

#ifdef MEREC_CASTLE_TEST_GUILD_LEVEL_GM_SETTING
	MeracCastleDebugGuildLevel = 0;
#endif

	m_tLastRewardCheck = 0;

	m_tRaidResetProcess = 0;
	m_nProcess = 0;
	m_bCanEnterTheRaidDungeon = true;
	m_bIsCheckTime = false;
	m_nResetDay = RAID_RESET_TIME_DAY;
	m_nResethr = RAID_RESET_TIME_HOUR;
	m_nResetmin = RAID_RESET_TIME_MIN;

#ifdef BATTLE_PASS_SYSTEM
	BattlePassResetProcess = false;
#endif
#ifdef PRESTIGE_SYSTEM
	PrestigeResetProcess = false;
#endif

	m_bApplySkillToNPC = false;

#ifdef SYSTEM_TREASURE_MAP
#ifdef SYSTEM_TREASURE_MAP_LINKZONE_DROP
	bTreasureMapLinkZoneDrop = true;
#else
	bTreasureMapLinkZoneDrop = false;
#endif
#endif

	//warfare
	//	m_intergrationInfo.AddNation(INTERGRATION_BRZ);
	//	m_intergrationInfo.AddNation(INTERGRATION_GER);
		//m_intergrationInfo.AddNation(INTERGRATION_SPN);
	//	m_intergrationInfo.AddNation(INTERGRATION_USA);
#if defined (BILA_INTERGRATION_SERVER)
	m_intergrationInfo.AddNation(INTERGRATION_BRAZIL);
	m_intergrationInfo.AddNation(INTERGRATION_MEXICO);
#endif
#if defined (EU_INTERGRATION_SERVER)
	m_intergrationInfo.AddNation(INTERGRATION_GER);
	m_intergrationInfo.AddNation(INTERGRATION_SPN);
	m_intergrationInfo.AddNation(INTERGRATION_FRC);
	m_intergrationInfo.AddNation(INTERGRATION_PLD);
	m_intergrationInfo.AddNation(INTERGRATION_TUR);
	m_intergrationInfo.AddNation(INTERGRATION_ITA);
	m_intergrationInfo.AddNation(INTERGRATION_UK);
#endif

	m_messengerConnMsg.reset(new CNetMsg);
	m_connectorConnMsg.reset(new CNetMsg);
	m_helperConnMsg.reset(new CNetMsg);
	m_subHelperConnMsg.reset(new CNetMsg);

	m_messenger = MessengerInGame::instance();
	m_connector = ConnectorInGame::instance();
	m_helper = HelperInGame::instance();
	m_subHelper = SubHelperInGame::instance();

	barunsongames_flag = false;
	m_hardcore_flag_in_gameserver = 0;

	m_DratanCheckTime = 3;

	CWearInvenManager::Init();
#ifdef TLD_EVENT_SONG
	tld_event = false;
#endif

	m_battle_guild_index = -1;
	m_battle_guild_gm = -1;

#ifdef DOUBLE_ATTACK //RomeoST damage fix 
	m_bDoubleAttackEvent = false;
#endif

	gm_list_init();
}

CServer::~CServer()
{
	return;

	//////////////////////////////////////////////////////////////////////////


	if (m_zones)
		delete[] m_zones;
	m_zones = NULL;
	m_numZone = 0;
	if (m_serverpath)
		delete[] m_serverpath;
	m_serverpath = NULL;

	{
		map_listparty_t::iterator it = m_listParty.begin();
		map_listparty_t::iterator endit = m_listParty.end();
		for (; it != endit; ++it)
		{
			delete (it->second);
		}
		m_listParty.clear();
	}

	{
		map_listexped_t::iterator it = m_listExped.begin();
		map_listexped_t::iterator endit = m_listExped.end();
		for (; it != endit; ++it)
		{
			delete (it->second);
		}
		m_listExped.clear();
	}

	{
		map_listPartyMatchMember_t::iterator it = m_listPartyMatchMember.begin();
		map_listPartyMatchMember_t::iterator endit = m_listPartyMatchMember.end();
		for (; it != endit; ++it)
		{
			delete (it->second);
		}
		m_listPartyMatchMember.clear();
	}

	{
		map_listPartyMatchParty_t::iterator it = m_listPartyMatchParty.begin();
		map_listPartyMatchParty_t::iterator endit = m_listPartyMatchParty.end();
		for (; it != endit; ++it)
		{
			delete (it->second);
		}
		m_listPartyMatchParty.clear();
	}

	{
		map_listOXQuiz_t::iterator it = m_listOXQuiz.begin();
		map_listOXQuiz_t::iterator endit = m_listOXQuiz.end();
		for (; it != endit; ++it)
		{
			delete (it->second);
		}
		m_listOXQuiz.clear();
	}

	m_LuckyDrawBox.RemoveAll();

#ifdef LACARETTE_SYSTEM
	m_lacarette.RemoveAll();
#endif

#ifdef DEV_EVENT_PROMOTION2
	m_promotion2.RemoveAll();
#endif

	m_MonsterMercenary.ReleaseAll();

	if (m_XmasPuzzleGame)
		delete m_XmasPuzzleGame;
	if (m_XmasRockPaperScissorsGame)
		delete m_XmasRockPaperScissorsGame;
}

char* CServer::GetServerPath()
{
	char szBuffer[1024];
#ifdef CIRCLE_WINDOWS
	GetModuleFileName(::GetModuleHandle(NULL), szBuffer, 1000);
	int path_len = strlen(szBuffer);
	int i;

	for (i = path_len - 1; i >= 0; i--)
	{
		if (szBuffer[i] == '\\')
		{
			szBuffer[i + 1] = '\0';
			break;
		}
	}
	if (i < 0)
		return false;
#else
	getcwd(szBuffer, 512);
	strcat(szBuffer, "/");
#endif

	char* ret = new char[strlen(szBuffer) + 1];
	strcpy(ret, szBuffer);
	return ret;
}

bool CServer::LoadSettingFile()
{
	puts("Load setting file....");

	CLCString strTemp(1024);

	strTemp.Format("%s%s", m_serverpath, "gameserver.txt");


	if (!m_config.Load(strTemp))
		return false;
#ifdef DEV_EVENT_AUTO
	strTemp.Format("%s%s", m_serverpath, "data/event.ini");
	if (!m_eventConfig.Load(strTemp))
	{
		puts("Loading Error : [data/event.ini] file is not exist.");
		return false;
	}
	else
	{
		m_fathersDay.Load(m_eventConfig);
		m_DropEvent.Load(m_eventConfig);
	}
#endif

	m_serverno = atoi(m_config.Find("Server", "Number"));
	m_subno = atoi(m_config.Find("Server", "SubNumber"));
#ifdef GER_LOG
	m_hostname = getenv("HOSTNAME");
#endif // GER_LOG

#if defined(LC_GAMIGO) || defined ( LC_USA ) || defined (LC_BILA) || defined (LC_RUS)
	if (m_subno == 2 || m_subno == 5)
	{
		m_bNonPK = true;
	}
#elif defined(LC_KOR)
	if (m_subno == 3)
	{
		m_bNonPK = true;
	}
#else
	if (m_subno == 7 || m_subno == 8)
	{
		m_bNonPK = true;
	}
#endif


#if defined FREE_PK_SYSTEM
#if defined ( LC_TLD ) || defined ( LC_USA )
	if (m_serverno == 4)
		m_bFreePk = true;
	if ((m_serverno == 3 && m_subno == 1) || (m_serverno == 2 && m_subno == 1) || (m_serverno == 1 && m_subno == 1))
		m_bFreePk = true;
#endif
#endif // FREE_PK_SYSTEM

#if defined MAL_DISABLE_PKPENALTY

	if (m_subno == 1 || m_subno == 2)
		m_bDisablePKPaenalty = true;

#endif
	if (strcmp(m_config.Find("Server", "AllowExternalIP"), "FALSE") == 0)
		m_bOnlyLocal = true;
	else
		m_bOnlyLocal = false;

	if (strcmp(m_config.Find("Server", "NON_PK"), "TRUE") == 0)
		m_bNonPK = true;
	else if (strcmp(m_config.Find("Server", "NON_PK"), "FALSE") == 0)
		m_bNonPK = false;

#ifdef GMTOOL
	if (gserver->m_serverno == 1 && gserver->m_subno == 1)
	{
		const char* p = m_config.Find("GMTOOL", "count");
		if (!p)
			return false;
		m_nGMToolCount = atoi(p);
		if (m_nGMToolCount <= 0)
		{
			m_gmtool = NULL;
		}
		else
		{
			m_gmtool = new CDescriptor * [m_nGMToolCount];
			int i;
			for (i = 0; i < m_nGMToolCount; ++i) m_gmtool[i] = NULL;
		}
	}
#endif // GMTOOL

#if defined (INTERGRATION_SERVER)
	if (strcmp(m_config.Find("Server", "IntergrationServer"), "TRUE") == 0)
		m_intergrationInfo.SetEnable(true);
	else
		m_intergrationInfo.SetEnable(false);
#endif

#ifdef IMP_SPEED_SERVER
	if (strcmp(m_config.Find("Server", "SPEED_SERVER"), "TRUE") == 0)
		m_bSpeedServer = true;
#endif //IMP_SPEED_SERVER

#ifdef HARDCORE_SERVER
	if (strcmp(m_config.Find("Server", "HARDCORE"), "TRUE") == 0)
	{
		m_hardcore_flag_in_gameserver = 1;
	}
#endif

	// Load Skill Cooldown Delay Reduction Configuration - PVP vs PVE (0-100 percentage)
	// PVP states: War Zone, PK Mode, RA Mode, Change (combat) state - all use PvpOpDecreaseSkillDelayPercent
	const char* skillCooldownPvpStr = m_config.Find("SkillCooldown", "PvpOpDecreaseSkillDelayPercent");
	if (skillCooldownPvpStr && skillCooldownPvpStr[0] != '\0')
	{
		m_skillCooldownPvpPercent = atoi(skillCooldownPvpStr);
		if (m_skillCooldownPvpPercent < 0)
			m_skillCooldownPvpPercent = 0;
		else if (m_skillCooldownPvpPercent > 100)
			m_skillCooldownPvpPercent = 100;
	}

	const char* skillCooldownPveStr = m_config.Find("SkillCooldown", "PveOpDecreaseSkillDelayPercent");
	if (skillCooldownPveStr && skillCooldownPveStr[0] != '\0')
	{
		m_skillCooldownPvePercent = atoi(skillCooldownPveStr);
		if (m_skillCooldownPvePercent < 0)
			m_skillCooldownPvePercent = 0;
		else if (m_skillCooldownPvePercent > 100)
			m_skillCooldownPvePercent = 100;
	}

	return true;
}

bool CServer::LoadSettings()
{
	int i;

	GAMELOG << init("SYSTEM")
		<< "Load settings...."
		<< end;

	// version information loading
	GAMELOG << init("SYSTEM")
		<< "Client Version Loading..."
		<< end;

	CDBCmd dbcmd;
	dbcmd.Init(&m_dbdata);
	dbcmd.SetQuery("SELECT a_min, a_max FROM t_clientversion");
	if (!dbcmd.Open() || !dbcmd.MoveFirst() || !dbcmd.GetRec("a_min", m_clientversionMin) || !dbcmd.GetRec("a_max", m_clientversionMax))
	{
		LOG_INFO("Client Version Query Error.");
		return false;
	}

	ComposeItem::instance()->load();

	//�������� �ε�
	Notice::instance()->load();
	//�˾� �������� �ε�
	PopupNotice::instance()->load();

	CEquipExchangeExtend::instance()->load_();

#ifdef LACARETTE_SYSTEM
	if (!m_lacarette.Load())
	{
		GAMELOG << init("ERROR : CANNOT LOAD LACARETTE SYSTEM DATA") << end;
		return false;
	}
#endif

	if (!m_craft.Load())  //pwesty craft system
	{
		GAMELOG << init("ERROR : CANNOT LOAD CRAFT SYSTEM DATA") << end;
		return false;
	}
#ifdef DEV_EVENT_PROMOTION2
	if (!m_promotion2.Load())
	{
		GAMELOG << init("ERROR : CANNOT LOAD EVENT_PROMOTION DATA") << end;
		return false;
	}
#endif

#ifdef XTRAP
	if (!InitXTrap())
	{
		GAMELOG << init("ERROR : Init XTRAP ") << end;
		return false;
	}
#endif // XTRAP

	GAMELOG << init("SYSTEM")
		<< "Load MakeTitle Data"
		<< end;
	if (!m_titleMakedata.load())
	{
		GAMELOG << init("ERROR : CANNOT LOAD MAKE TITLE DATA") << end;
		return false;
	}

	// item proto loading
	GAMELOG << init("SYSTEM")
		<< "Item Loading..."
		<< end;
	if (!m_itemProtoList.Load())
	{
		LOG_INFO("ItemProtoList Load Error");
		return false;
	}

	GAMELOG << init("SYSTEM")
		<< "Set Item Loading..."
		<< end;
	if (!m_setItemProtoList.Load())
	{
		LOG_INFO("SetItemProtoList Load Error");
		return false;
	}

	GAMELOG << init("SYSTEM")
		<< "Factory Item Loading..."
		<< end;
	if (!m_factoryItemProtoList.Load())
	{
		LOG_INFO("FactoryItemProtoList Load Error");
		return false;
	}

	GAMELOG << init("SYSTEM")
		<< "CashItem Loading..."
		<< end;
	if (!m_catalogList.Load())
	{
		LOG_INFO("CatalogList Load Error");
		return false;
	}

	if (!LoadNpcBossList())
	{
		LOG_INFO("LoadNpcBossList Load Error");
		return false;
	}

	// Apet proto loading
	GAMELOG << init("SYSTEM")
		<< "Apet Loading..."
		<< end;
	if (!m_pApetlist.Load())
	{
		LOG_INFO("Apetlist Load Error");
		return false;
	}

	// skill proto loading
	GAMELOG << init("SYSTEM")
		<< "Skill Loading..."
		<< end;
	if (!m_magicProtoList.Load())
	{
		LOG_INFO("MagicProtoList Load Error");
		return false;
	}
	if (!m_skillProtoList.Load())
	{
		LOG_INFO("SkillProto List Load Error");
		return false;
	}

	// npc proto loading
	GAMELOG << init("SYSTEM")
		<< "Npc Loading..."
		<< end;
	if (!m_npcProtoList.Load())
	{
		LOG_INFO("npcProtoList Load Error");
		return false;
	}

	LOG_INFO("npcProtoList loaded %d npcs", m_npcProtoList.m_nCount);
	// quest proto loading
	GAMELOG << init("SYSTEM")
		<< "Quest Loading..."
		<< end;
	if (!m_questProtoList.Load())
	{
		LOG_INFO("questProtoList Load Error");
		return false;
	}
	LOG_INFO("questProtoList loaded %d quests", m_questProtoList.m_nCount);


	GAMELOG << init("SYSTEM") << "Reward Loading..." << end;
	if (!m_rewardMgr.loadReward(&gserver->m_dbdata))
	{
		LOG_INFO("Reward List Load Error");
		return false;
	}

	GAMELOG << init("SYSTEM") << "Event Automation Loading..." << end;
	if (!m_eventAutomationMgr.loadEvent())
	{
		LOG_INFO("Event Automation List Load Error");
		return false;
	}

	GAMELOG << init("SYSTEM") << "Drop List Loading..." << end;
	if (!m_dropItemMgr.loadDropData(&gserver->m_dbdata))
	{
		LOG_INFO("Drop List Load Error");
		return false;
	}

	// Option Proto Loading
	GAMELOG << init("SYSTEM")
		<< "Option Loading..."
		<< end;
	if (!m_optionProtoList.Load())
	{
		LOG_INFO("optionProtoList Load Error");
		return false;
	}

	// rare option proto loading
	GAMELOG << init("SYSTEM")
		<< "Rare Option Loading..."
		<< end;
	if (!m_rareOptionList.Load())
	{
		LOG_INFO("rareOptionList Load Error");
		return false;
	}

	// SSpecial Skill Proto Loading
	GAMELOG << init("SYSTEM")
		<< "Special Skill Loading..."
		<< end;

	if (!m_sSkillProtoList.Load())
	{
		LOG_INFO("sSkillProtoList Load Error");
		return false;
	}

	GAMELOG << init("SYSTEM")
		<< "Donation tier settings Loading..."
		<< end;
	if (!m_donationTierManager.Load())
	{
		LOG_ERROR("Donation tier load error");
		return false;
	}
	// OX Quiz Loading
	GAMELOG << init("SYSTEM")
		<< "OX Quiz Loading..."
		<< end;

	if (!LoadOXQuiz())
	{
		LOG_INFO("LoadOXQuiz Error");
		return false;
	}
#ifdef CLOUD_EXPEDITION_REWORK
	if (!m_PartyConfig.Load())
	{
		LOG_INFO("Party Expetidions Load Error");
		return false;
	}
#endif
	if (!m_moonstoneReward.Load())
	{
		LOG_INFO("moonstoneReward Load Error");
		return false;
	}

	GAMELOG << init("SYSTEM")
		<< "Trigger System Loading..."
		<< end;
	if (!m_CTriggerDBInfo.Load_Trigger())
	{
		LOG_INFO("TriggerDBInfo Load Error");
		return false;
	}

	GAMELOG << init("SYSTEM")
		<< "Load Raid Scene Info"
		<< end;
	if (!m_RaidInfo.Load())
	{
		GAMELOG << init("ERROR : CANNOT LOAD NEW RAID INFO") << end;
		return false;
	}

	GAMELOG << init("SYSTEM")
		<< "Load LuckydrawBox"
		<< end;
	if (!m_LuckyDrawBox.Load())
	{
		GAMELOG << init("ERROR: CANNOT LOAD LUCKYDRAWBOX DATA") << end;
		return false;
	}

	if (!LoadServerConfig())
	{
		GAMELOG << init("ERROR: CANNOT LOAD SERVER CONFIG DATA") << end;
		return false;
	}

	if (!LoadPetConfig())
	{
		GAMELOG << init("ERROR: CANNOT LOAD PET CONFIG DATA") << end;
		return false;
	}

	GAMELOG << init("SYSTEM") << "Load Monster Mercenary System Data" << end;
	if (!m_MonsterMercenary.LoadData())
	{
		GAMELOG << init("ERROR : CANNOT LOAD MONSTER MERCENARY SYSTEM DATA") << end;
		return false;
	}

	// Loading Zone
	m_numZone = atoi(m_config.Find("Zones", "Count"));
	if (m_numZone == 0 || m_numZone > MAX_ZONES)
	{
		GAMELOG << init("ERROR: ZONE MAX COUNT OVER") << end;
		return false;
	}

	m_zones = new CZone[m_numZone];
	for (i = 0; i < m_numZone; i++)
	{
		if (!m_zones[i].LoadZone(i))
		{
			LOG_INFO("LoadZone Error");
			return false;
		}

		if (m_zones[i].m_index == 21)
		{
			// ���� ���� ����
			CDratanCastle* pCastle = CDratanCastle::CreateInstance();
			pCastle->m_dvd.SetZone(&m_zones[i]);
		}

		// Shop Proto Loading
		if (!m_zones[i].LoadShop())
		{
			LOG_INFO("LoadShop Error");
			return false;
		}

		m_zones_map.insert(map_zone_t::value_type(m_zones[i].m_index, &m_zones[i]));
	}
#ifdef SYSTEM_TREASURE_MAP
	gserver->readTreasureMapSaveFile();
#endif
	for (i = 0; i < m_numZone; i++)
	{
		if (m_zones[i].m_index == ZONE_ALTER_OF_DARK || m_zones[i].m_index == ZONE_CAPPELLA_1 || m_zones[i].m_index == ZONE_AKAN_TEMPLE
			|| m_zones[i].m_index == ZONE_DUNGEON4
			|| m_zones[i].m_index == ZONE_TARIAN_DUNGEON
			|| m_zones[i].m_index == ZONE_ENCHANTED_DUNGEON
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
			|| m_zones[i].m_index == ZONE_PARTY_DUNGEON0
			|| m_zones[i].m_index == ZONE_PARTY_DUNGEON1
			|| m_zones[i].m_index == ZONE_PARTY_DUNGEON2
			|| m_zones[i].m_index == ZONE_PARTY_DUNGEON3
			|| m_zones[i].m_index == ZONE_PARTY_DUNGEON4
#endif		  
			)
			continue;

		if (!m_zones[i].LoadNPC())
		{
			LOG_INFO("LoadNPC Error");
			return false;
		}
	}

	// Load offline shops from database (persistent shops that survive disconnect)
#ifdef OFFLINE_SHOPS
	GAMELOG << init("SYSTEM")
		<< "Offline Shops Loading..."
		<< end;
	LoadOfflineShopsFromDB();
#endif

	// CPC-vendor model: startup restoration of vendors is deferred to Phase 2.
	// The CNPC-based spawn paths are disabled since offline vendors are now
	// kept alive as their actual CPC (with real appearance/equipment).

	GAMELOG << init("SYSTEM")
		<< "MISSIONCASE Loading..."
		<< end;

	if (!m_missionCaseList.LoadList())
	{
		LOG_INFO("missionCaseList Load Error");
		return false;
	}

	if (!m_affinityProtoList.LoadAffinity())
	{
		LOG_INFO("LoadAffinity Error");
		return false;
	}

	GAMELOG << init("Load Castle Information...") << end;
	if (!LoadCastleData())
	{
		GAMELOG << init("ERROR: CANNOT LOAD CASTLE INFO") << end;
		return false;
	}

#ifdef EXTREME_CUBE
	GAMELOG << init("SYSTEM")
		<< "Load Cube Data"
		<< end;

	if (!m_extremeCube.Load())
	{
		GAMELOG << init("ERROR: CANNOT LOAD EXTREME CUBE DATA") << end;
		return false;
	}

#endif // EXTREME_CUBE

	GAMELOG << init("SYSTEM")
		<< "Load TitleSystem Data"
		<< end;
	if (!m_titleProtoList.Load())
	{
		GAMELOG << init("ERROR : CANNOT LOAD TITLE SYSTEM DATA") << end;
		return false;
	}

	GAMELOG << init("SYSTEM")
		<< "Load JewelNas Data"
		<< end;
	if (!m_jewelDataList.Load())
	{
		GAMELOG << init("ERROR : CANNOT LOAD JEWEL DATA SYSTEM DATA") << end;
		return false;
	}

	if (!m_event_summon.Load())
	{
		GAMELOG << init("ERROR : CANNOT LOAD EVENT HIDE SYSTEM DATA") << end;
		return false;
	}

	if (!m_BattleWarfare.Load()) {
		GAMELOG << init("ERROR : CANNOT LOAD BATTLE WARFARE SYSTEM DATA") << end;
		return false;
	}

	if (!m_autoEventScheduler.Load()) {
		GAMELOG << init("ERROR : CANNOT LOAD AUTO EVENT SCHEDULER DATA") << end;
		return false;
	}

#ifdef BATTLE_PASS_SYSTEM
	if (!LoadBattlePass()) {
		GAMELOG << init("ERROR : CANNOT LOAD BATTLE PASS SYSTEM DATA") << end;
		return false;
	}
#endif
#ifdef PRESTIGE_SYSTEM
	if (!LoadPrestige()) {
		GAMELOG << init("ERROR : CANNOT LOAD PRESTIGE SYSTEM DATA") << end;
		return false;
	}
#endif

	//PASSIVE_SYSTEM
	GAMELOG << init("SYSTEM")
		<< "Passive System Loading..."
		<< end;
	if (!m_passiveSystemList.Load())
	{
		LOG_INFO("Passive system list Load Error");
		return false;
	}

	GAMELOG << init("HOOK")
		<< "Discord Bot Hook Loading..."
		<< end;
	StartGMCommandListener();

	GAMELOG << init("WATCHER")
		<< "skill hack detection Loading..."
		<< end;
	CSkillUseLog::LoadWatchedCharacters();



#ifdef EVENT_VALENTINE
	gserver->m_bValentineEvent = true;
#endif

#ifdef EVENT_WHITEDAY
	gserver->m_bWhiteDayEvent = true;
#endif

	//0704 �̺�Ʈ�� ���� ���� ����.
#ifdef NOTICE_EVENT
	i = 0;
	memset(m_aNotice, 0, sizeof(int) * 5);

#ifdef EVENT_TREASUREBOX
	addNotice(i, EVENT_TREASUREBOX);

	i++;
#endif // #ifdef EVENT_TREASUREBOX

	//#ifdef EVENT_TEACH
	//	addNotice(i, EVENT_TEACH);
	//	i++;
	//#endif // #ifdef EVENT_TEACH

#ifdef EVENT_CHILDERN_DAY
	addNotice(i, EVENT_CHILDERN_DAY);
	i++;
#endif // EVENT_CHILDERN_DAY

	std::map<int, CEventInfo*>* ActiveEventList = gserver->getActiveEvenList();
	if (ActiveEventList && ActiveEventList->size() != 0)
	{
		std::map<int, CEventInfo*>::iterator itr;
		std::map<int, CEventInfo*>::iterator itrEnd = ActiveEventList->end();
		for (itr = ActiveEventList->begin(); itr != itrEnd; itr++)
		{
			if (itr->second->getNotice())
			{
				addNotice(i, itr->second->getEventIndex());
				i++;
				if (i >= 5)
					break;
			}
		}
	}

#ifdef CHAOSBALL

	addNotice(i, CHAOSBALL);
	i++;

#endif

#if defined(LC_KOR)
#ifdef HANARO_EVENT
	// Config_Localize�� define ���� �ʿ�.
	addNotice(i, HANARO_EVENT);
	i++;
#endif // HANARO_EVENT
#endif // LC_KOR

#endif // #ifdef NOTICE_EVENT

#ifdef EVENT_WORLDCUP_2010
	addNotice(i, EVENT_WORLDCUP_2010);
	i++;
#endif

#ifdef EVENT_WORLDCUP_2010_TOTO
	addNotice(i, EVENT_WORLDCUP_2010_TOTO);
	i++;
#endif

	if (i > MAX_NOTICE)
	{
		LOG_ERROR("SYSTEM ERROR: OVERFLOW NOTICE. i = %d MAX_NOTICE = %d", i, MAX_NOTICE);
	}

	GAMELOG << init("SYSTEM") << "MC DUNGEON::";
	m_comboZone = FindZone(ZONE_COMBO_DUNGEON);
	if (m_comboZone == NULL)
	{
		GAMELOG << init("SYSTEM ERROR: NOT FOUND COMBO DUNGEON") << end;
		return false;
	}

	// �⼮ �̺�Ʈ ���� ������ �ε�
	if (!m_rewardItemList.init())
	{
		GAMELOG << init("ERROR : CANNOT LOAD REWARDEVENTITEM SYSTEM DATA") << end;
		return false;
	}

	if (!m_promoKeyManager.Load())
	{
		GAMELOG << init("ERROR : CANNOT LOAD PROMOTION KEY SYSTEM DATA") << end;
		return false;
	}

	// Load scripted NPC movements from the database
	if (!LoadScriptedMovements())
	{
		GAMELOG << init("WARNING") << "Failed to load scripted NPC movements (table may not exist yet)" << end;
	}

	gGMCmdList->load();

	

	m_XmasRockPaperScissorsGame = new CRockPaperScissorsGame(27, 1);
	int xmasPuzzleItem[] = { 9259, 9260, 9261, 9262, 9263, 9264, 9265, 9266, 9267 };
	m_XmasPuzzleGame = new CPuzzleGame(xmasPuzzleItem, 9);

#ifdef TLD_EVENT_SONG
	if (itemExchangeProto::instance()->Load() == false)
		return false;
#endif

	HolyWaterData::instance()->load();

	if (ItemCollectionData::instance()->load() == false)
	{
		return false;
	}
	//CEquipExchangeExtend::instance()->load_();

	GAMELOG << init("SYSTEM") << "LOADING BUFFSYSTEM::";
	if (!gserver->m_buffSystem.Init()) {
		GAMELOG << "ERROR" << end;
	}
	GAMELOG << "SUCCESS" << end;

#ifdef DAILY_LOGIN
	GAMELOG << init("SYSTEM") << "LOADING NEWLOGIN REWARD , DAILY LOGIN::";
	if (!gserver->m_DailyLogin.Init())
	{
		GAMELOG << "ERROR" << end;
	}
	GAMELOG << "SUCCESS" << end;;

#endif
	return true;
}

bool CServer::ConnectDB()
{
	if (!mysql_real_connect(
		&m_dbchar,
		m_config.Find("Char DB", "IP"),
		m_config.Find("Char DB", "User"),
		m_config.Find("Char DB", "Password"),
		m_config.Find("Char DB", "DBName"),
		0, NULL, 0))
	{
		LOG_ERROR("Can't connect char DB : ip[%s] id[%s] pw[%s] dbname[%s] error[%s]",
			m_config.Find("Char DB", "IP"),
			m_config.Find("Char DB", "User"),
			m_config.Find("Char DB", "Password"),
			m_config.Find("Char DB", "DBName"),
			mysql_error(&m_dbchar)
		);
		return false;
	}

	if (!mysql_real_connect(
		&m_dbdata,
		m_config.Find("Data DB", "IP"),
		m_config.Find("Data DB", "User"),
		m_config.Find("Data DB", "Password"),
		m_config.Find("Data DB", "DBName"),
		0, NULL, 0))
	{
		LOG_ERROR("Can't connect data DB : ip[%s] id[%s] pw[%s] dbname[%s] error[%s]",
			m_config.Find("Data DB", "IP"),
			m_config.Find("Data DB", "User"),
			m_config.Find("Data DB", "Password"),
			m_config.Find("Data DB", "DBName"),
			mysql_error(&m_dbdata)
		);
		return false;
	}

	if (!mysql_real_connect(
		&m_dbauth,
		m_config.Find("Auth DB", "IP"),
		m_config.Find("Auth DB", "User"),
		m_config.Find("Auth DB", "Password"),
		m_config.Find("Auth DB", "DBName"),
		0, NULL, 0))
	{
		LOG_ERROR("Can't connect data DB : ip[%s] id[%s] pw[%s] dbname[%s] error[%s]",
			m_config.Find("Auth DB", "IP"),
			m_config.Find("Auth DB", "User"),
			m_config.Find("Auth DB", "Password"),
			m_config.Find("Auth DB", "DBName"),
			mysql_error(&m_dbauth)
		);
		return false;
	}


	// �±� ��ǰ ���̺��� ������ ���� ��������
#ifdef USE_TENTER_BILLING
	const char* ip = m_config.Find("Catalog DB", "IP");
	const char* user = m_config.Find("Catalog DB", "User");
	const char* pw = m_config.Find("Catalog DB", "Password");
	const char* dbname = m_config.Find("Catalog DB", "DBName");
	if (!mysql_real_connect(
		&m_dbcatal,
		ip,
		user,
		pw,
		dbname,
		0, NULL, 0))
	{
		LOG_ERROR("Can't connect catalog DB : ip[%s] id[%s] pw[%s] dbname[%s] error[%s]",
			m_config.Find("Catalog DB", "IP"),
			m_config.Find("Catalog DB", "User"),
			m_config.Find("Catalog DB", "Password"),
			m_config.Find("Catalog DB", "DBName"),
			mysql_error(&m_dbcatal)
		);
		return false;
	}
#endif

	CDBCmd cmdCheckCharDB;
	cmdCheckCharDB.Init(&m_dbcharingame);

	cmdCheckCharDB.SetQuery("SELECT a_etc_event FROM t_characters LIMIT 1");
	if (!cmdCheckCharDB.Open())
	{
		GAMELOG << init("Error: Character DB Check: Not Found t_characters.a_etc_event!!") << end;
		return false;
	}

	// 060221 : bs : �� ����ð� �ʵ� �˻�
	cmdCheckCharDB.SetQuery("SELECT a_time_rebirth FROM t_pet LIMIT 1");
	if (!cmdCheckCharDB.Open())
	{
		GAMELOG << init("Error: Character DB Check: Not Found t_pet.a_time_rebirth!!") << end;
		return false;
	}

	// 060227 : bs : ����ȭ ������ 2��
	cmdCheckCharDB.SetQuery("SELECT a_index, a_char_index, a_item_index, a_end_time, a_skill_index, a_skill_level, a_hit0, a_hit1, a_hit2 FROM t_assist_abstime LIMIT 1");
	if (!cmdCheckCharDB.Open())
	{
		GAMELOG << init("Error: Character DB Check: Not Found t_assist_abstime!") << end;
		return false;
	}
	// 060227 : bs : ����ȭ ������ 2��

	// �ڵ� ���� ���̺�

	cmdCheckCharDB.SetQuery("SELECT a_index, a_char_index, a_item_index, a_item_plus, a_item_flag, a_item_used, a_item_count, a_item_option0, a_item_option1, a_item_option2, a_item_option3, a_item_option4 FROM t_auto_give LIMIT 1");
	if (!cmdCheckCharDB.Open())
	{
		GAMELOG << init("Error: Character DB Check: Not Found t_auto_give!") << end;
		return false;
	}

	// ĳ���� ���� ������ �ʵ�
	cmdCheckCharDB.SetQuery("SELECT a_deletedelay FROM t_characters LIMIT 1");
	if (!cmdCheckCharDB.Open())
	{
		GAMELOG << init("Error: Character DB Check: Not Found t_characters.a_deletedelay!") << end;
		return false;
	}

	cmdCheckCharDB.SetQuery("SELECT `a_mempos_new`, `a_charslot0_new`, `a_charslot1_new`, `a_stashext_new` FROM t_cashitemdate LIMIT 1");
	if (!cmdCheckCharDB.Open())
	{
		GAMELOG << init("Error: Character DB Check: Not Found t_cashitemdate.a_xxx_new!") << end;
		return false;
	}

	int nQuestTable;
	for (nQuestTable = 0; nQuestTable < 10; nQuestTable++)
	{
		std::string select_questdata_query = boost::str(boost::format(
			"SELECT a_char_index,a_quest_index,a_state,a_value0,a_value1,a_value2 FROM t_questdata%02d LIMIT 1") % nQuestTable);

		cmdCheckCharDB.SetQuery(select_questdata_query);
		if (!cmdCheckCharDB.Open())
		{
			GAMELOG << init("Error: Character DB Check: Not Found t_questdata") << nQuestTable << end;
			return false;
		}
	}

	for (int nInvenTable = 0; nInvenTable < 10; nInvenTable++)
	{
		std::string select_inven_query = boost::str(boost::format(
			"SELECT a_used0_2, a_used1_2, a_used2_2, a_used3_2, a_used4_2 FROM t_inven%02d LIMIT 1") % nInvenTable);
		cmdCheckCharDB.SetQuery(select_inven_query);
		if (!cmdCheckCharDB.Open())
		{
			GAMELOG << init("Error: Character DB Check: Not Found t_inven") << nInvenTable << ".a_used_2" << end;
			return false;
		}
	}

	for (int nStashTable = 0; nStashTable < 10; nStashTable++)
	{
		std::string select_used_2_query = boost::str(boost::format(
			"SELECT a_used_2 FROM t_stash%02d LIMIT 1") % nStashTable);
		cmdCheckCharDB.SetQuery(select_used_2_query);
		if (!cmdCheckCharDB.Open())
		{
			GAMELOG << init("Error: Character DB Check: Not Found t_stash") << nStashTable << ".a_used_2" << end;
			return false;
		}
	}

	cmdCheckCharDB.SetQuery("SELECT a_item_used_2 FROM t_auto_give LIMIT 1");
	if (!cmdCheckCharDB.Open())
	{
		GAMELOG << init("Error: Character DB Check: Not Found t_auto_give.a_item_used_2") << end;
		return false;
	}

	cmdCheckCharDB.SetQuery("SELECT * FROM t_characters_factory LIMIT 1");
	if (!cmdCheckCharDB.Open())
	{
		GAMELOG << init("Error: Character DB Check: Not Found t_characters_factory") << end;
		return false;
	}

	CDBCmd cmdCheckEventGomdori2007;
	cmdCheckEventGomdori2007.Init(&m_dbcharingame);
	cmdCheckEventGomdori2007.SetQuery("SELECT a_char_index, a_first_lose, a_first_win, a_total FROM t_event_gomdori_2007 LIMIT 1");
	if (!cmdCheckEventGomdori2007.Open())
	{
		GAMELOG << init("Error: Data DB Check : Not Found t_event_gomdori_2007") << end;
		return false;
	}

#ifdef EVENT_PARENTSDAY_2007
	CDBCmd cmdCheckEventParentsday2007;
	cmdCheckEventParentsday2007.Init(&m_dbcharingame);
	cmdCheckEventParentsday2007.SetQuery("SELECT * FROM t_event_2007_parentsday LIMIT 1");
	if (!cmdCheckEventParentsday2007.Open())
	{
		GAMELOG << init("Error: Data DB Check : Not Found t_event_2007_parentsday") << end;
		return false;
	}

	CDBCmd cmdCheckEventMay2007;
	cmdCheckEventMay2007.Init(&m_dbcharingame);
	cmdCheckEventMay2007.SetQuery("SELECT * FROM t_event_may2007 LIMIT 1");
	if (!cmdCheckEventMay2007.Open())
	{
		GAMELOG << init("Error: Data DB Check : Not Found t_event_may2007") << end;
		return false;
	}
#endif // EVENT_PARENTSDAY_2007

	CDBCmd cmdCheckPetName;
	cmdCheckPetName.Init(&m_dbcharingame);
	cmdCheckPetName.SetQuery("SELECT * FROM t_pet_name LIMIT 1");
	if (!cmdCheckPetName.Open())
	{
		GAMELOG << init("Error: Char DB Check : Not Found t_pet_name") << end;
		return false;
	}

	CDBCmd cmdNewGuild;
	cmdNewGuild.Init(&m_dbcharingame);
	cmdNewGuild.SetQuery("SELECT * FROM t_characters_guildpoint LIMIT 0");
	if (!cmdNewGuild.Open())
	{
		GAMELOG << init("Error: Data DB Check : Not Found t_characters_guildpoint") << end;
		return false;
	}

	cmdNewGuild.SetQuery("SELECT * FROM t_extend_guild LIMIT 0");
	if (!cmdNewGuild.Open())
	{
		GAMELOG << init("Error: Data DB Check : Not Found t_extend_guild") << end;
		return false;
	}

	cmdNewGuild.SetQuery("SELECT * FROM t_extend_guildmember LIMIT 0");
	if (!cmdNewGuild.Open())
	{
		GAMELOG << init("Error: Data DB Check : Not Found t_extend_guildmember") << end;
		return false;
	}

	cmdNewGuild.SetQuery("SELECT * FROM t_guild_notice LIMIT 0");
	if (!cmdNewGuild.Open())
	{
		GAMELOG << init("Error: Data DB Check : Not Found t_guild_notice") << end;
		return false;
	}

	CDBCmd cmdNewCastleWar;
	cmdNewCastleWar.Init(&m_dbcharingame);
	cmdNewCastleWar.SetQuery("SELECT * FROM t_castle_guard LIMIT 0");
	if (!cmdNewCastleWar.Open())
	{
		GAMELOG << init("Error: Data DB Check : Not Found t_castle_guard") << end;
		return false;
	}

	cmdNewCastleWar.SetQuery("SELECT * FROM t_castle_tower LIMIT 0");
	if (!cmdNewCastleWar.Open())
	{
		GAMELOG << init("Error: Data DB Check : Not Found t_castle_tower") << end;
		return false;
	}

	cmdNewCastleWar.SetQuery("SELECT * FROM t_castle_reinforce LIMIT 0");
	if (!cmdNewCastleWar.Open())
	{
		GAMELOG << init("Error: Data DB Check : Not Found t_castle_reinforce") << end;
		return false;
	}

	cmdNewCastleWar.SetQuery("SELECT * FROM t_castle_rebrith LIMIT 0");
	if (!cmdNewCastleWar.Open())
	{
		GAMELOG << init("Error: Data DB Check : Not Found t_castle_rebrith") << end;
		return false;
	}

	CDBCmd cmdPetColor;
	cmdPetColor.Init(&m_dbcharingame);
	cmdPetColor.SetQuery("SELECT a_color FROM t_pet LIMIT 1");
	if (!cmdPetColor.Open())
	{
		GAMELOG << init("Error: Character DB Check: Not Found t_pet") << ".a_color" << end;
		return false;
	}

	int nInven, nStash;
	for (nInven = 0; nInven < 10; nInven++)
	{
		std::string select_inven_query = boost::str(boost::format(
			"SELECT a_socket0, a_socket1, a_socket2, a_socket3, a_socket4 FROM t_inven%02d LIMIT 1") % nInven);

		cmdCheckCharDB.SetQuery(select_inven_query);
		if (!cmdCheckCharDB.Open())
		{
			GAMELOG << init("Error: Character DB Check: Not Found t_inven") << nInven << delim << "socket" << end;
			return false;
		}
	}
	for (nStash = 0; nStash < 10; nStash++)
	{
		std::string select_stash_query = boost::str(boost::format(
			"SELECT a_socket FROM t_stash%02d LIMIT 1") % nStash);

		cmdCheckCharDB.SetQuery(select_stash_query);
		if (!cmdCheckCharDB.Open())
		{
			GAMELOG << init("Error: Character DB Check: Not Found t_stash") << nStash << delim << "socket" << end;
			return false;
		}
	}
	cmdCheckCharDB.SetQuery("SELECT a_item_socket FROM t_auto_give LIMIT 1");
	if (!cmdCheckCharDB.Open())
	{
		GAMELOG << init("Error: Character DB Check: Not Found t_auto_give socket") << end;
		return false;
	}

	return true;
}

void CServer::DisconnectDB(bool bchar)
{
	if (bchar)
	{
		mysql_close(&m_dbchar);
		mysql_close(&m_dbcastle);
		mysql_close(&m_dbTrigger);
		mysql_close(&m_dbcharingame);
	}
	else
	{
		//mysql_close (&m_dbCharUnManaged);
		mysql_close(&m_dbdata);
		//mysql_close (&m_dbAuth);
	}
}

bool CServer::InitGame()
{
	BOOST_STATIC_ASSERT(MSG_MSGR_END_MSG < 255);
	BOOST_STATIC_ASSERT(MSG_CONN_END_MSG < 255);
	BOOST_STATIC_ASSERT(MSG_HELPER_END_MSG < 255);
	BOOST_STATIC_ASSERT(MSG_EVENT_END_MSG < 255);
	BOOST_STATIC_ASSERT(MSG_FAIL_END_MSG < 255);
	BOOST_STATIC_ASSERT(MSG_SYS_END_MSG < 255);
	BOOST_STATIC_ASSERT(MSG_ITEM_END_MSG < 255);

	ServerSrandom(time(0));

	InitExp();
	InitExpLimit();

	gcmdlist.AddMessage();
	gexcmdlist.AddExMessage();

	GAMELOG << init("SYSTEM")
		<< "Finding player limit."
		<< end;
	m_maxplayers = GetMaxPlayers();

	GAMELOG << init("SYSTEM")
		<< "Opening mother connection."
		<< end;

	SetHeaders();

#ifdef DEV_DEATH_EVENT_SAVEFILE
	FILE* fpdeath = fopen(DEV_DEATH_EVENT_SAVEFILE, "rt");
	if (fpdeath)
	{
		long start = 0;
		long end = 0;
		bool bFail = false;
		char tmpBuf[MAX_STRING_LENGTH] = { 0, };

		if (fgets(tmpBuf, 256, fpdeath) == NULL) bFail = true;
		start = atol(tmpBuf);
		if (fgets(tmpBuf, 256, fpdeath) == NULL) bFail = true;
		end = atol(tmpBuf);
		if (bFail == false)
		{
			gserver->m_tDeathEventStart = (time_t)start;
			gserver->m_tDeathEventEnd = (time_t)end;
		}
		fclose(fpdeath);
		fpdeath = NULL;
	}
#endif
	FILE* fpResetRaid = fopen(RESET_RAID_SAVEFILE, "rt");
	if (fpResetRaid)
	{
		int resetday = 0;
		int resethr = 0;
		int resetmin = 0;
		char tmpBuf[MAX_STRING_LENGTH] = { 0, };

		bool bFail = false;
		if (fgets(tmpBuf, 256, fpResetRaid) == NULL)	bFail = true;
		resetday = atoi(tmpBuf);
		if (fgets(tmpBuf, 256, fpResetRaid) == NULL)	bFail = true;
		resethr = atoi(tmpBuf);
		if (fgets(tmpBuf, 256, fpResetRaid) == NULL)	bFail = true;
		resetmin = atoi(tmpBuf);
		if (bFail == false)
		{
			this->m_nResetDay = resetday;
			this->m_nResethr = resethr;
			this->m_nResetmin = resetmin;
		}
		fclose(fpResetRaid);
		fpResetRaid = NULL;
	}
#ifdef DOUBLE_PET_EXP_SAVEFILE
	FILE* fpDoublePetExp = fopen(DOUBLE_PET_EXP_SAVEFILE, "rt");
	if (fpDoublePetExp)
	{
		long starttime = -1;
		long endtime = -1;
		int prob = 100;
		bool bFail = false;
		char tmpBuf[MAX_STRING_LENGTH] = { 0, };
		if (fgets(tmpBuf, 256, fpDoublePetExp) == NULL) bFail = true;
		starttime = atol(tmpBuf);
		if (fgets(tmpBuf, 256, fpDoublePetExp) == NULL) bFail = true;
		endtime = atol(tmpBuf);
		if (fgets(tmpBuf, 256, fpDoublePetExp) == NULL) bFail = true;
		prob = atoi(tmpBuf);
		if (bFail == false)
		{
			gserver->m_tPetExpEventStart = (time_t)starttime;
			gserver->m_tPetExpEventEnd = (time_t)endtime;
			gserver->m_PetExpPercent = prob;
		}
		fclose(fpDoublePetExp);
		fpDoublePetExp = NULL;
	}
#endif // DOUBLE_PET_EXP_SAVEFILE
#ifdef UPGRADE_EVENT_AUTO_SAVEFILE
	FILE* fpUpgradeEvent = fopen(UPGRADE_EVENT_AUTO_SAVEFILE, "rt");
	{
		if (fpUpgradeEvent)
		{
			long starttime = -1;
			long endtime = -1;
			int prob = 100;
			bool bFail = false;
			char tmpBuf[MAX_STRING_LENGTH] = { 0, };
			if (fgets(tmpBuf, 256, fpUpgradeEvent) == NULL) bFail = true;
			starttime = atol(tmpBuf);
			if (fgets(tmpBuf, 256, fpUpgradeEvent) == NULL) bFail = true;
			endtime = atol(tmpBuf);
			if (fgets(tmpBuf, 256, fpUpgradeEvent) == NULL) bFail = true;
			prob = atoi(tmpBuf);
			if (bFail == false)
			{
				gserver->m_tUpgradeEventStart = (time_t)starttime;
				gserver->m_tUpgradeEventEnd = (time_t)endtime;
				g_nUpgradeProb = prob;
			}
			fclose(fpUpgradeEvent);
			fpUpgradeEvent = NULL;
		}
	}
#endif // UPGRADE_EVENT_AUTO_SAVEFILE
#ifdef GM_EXP_LIMIT_AUTO_SAVEFILE
	FILE* fpExpLimit = fopen(GM_EXP_LIMIT_AUTO_SAVEFILE, "rt");
	if (fpExpLimit)
	{
		int i;
		int nLimitStart;
		int nLimitEnd;
		int starttime[6];
		int endtime[6];
		bool bFail = false;
		memset(starttime, -1, sizeof(starttime));
		memset(endtime, -1, sizeof(endtime));
		char tmpBuf[MAX_STRING_LENGTH] = { 0, };

		if (fgets(tmpBuf, 256, fpExpLimit) == NULL) bFail = true;
		nLimitStart = atoi(tmpBuf);
		if (fgets(tmpBuf, 256, fpExpLimit) == NULL) bFail = true;
		nLimitEnd = atoi(tmpBuf);

		for (i = 0; i < 6; i++)
		{
			if (fgets(tmpBuf, 256, fpExpLimit) == NULL) bFail = true;
			starttime[i] = atoi(tmpBuf);
		}
		for (i = 0; i < 6; i++)
		{
			if (fgets(tmpBuf, 256, fpExpLimit) == NULL) bFail = true;
			endtime[i] = atoi(tmpBuf);
		}

		if (bFail == false)
		{
			m_nExpLimit = m_nExpLimitEnd = nLimitEnd;
			m_nSpLimit = m_nSpLimitEnd = nLimitEnd;
			for (i = 0; i < 6; i++)
			{
				m_nGMExpLimitStart[i] = starttime[i];
				m_nGMExpLimitEnd[i] = endtime[i];
			}
		}
		fclose(fpExpLimit);
		fpExpLimit = NULL;
	}
#endif // GM_EXP_LIMIT_AUTO_SAVEFILE
#ifdef EVENT_ITEMDROP_AUTO_SAVEFILE
	FILE* fpItemdrop = fopen(EVENT_ITEMDROP_AUTO_SAVEFILE, "rt");
	if (fpItemdrop)
	{
		int i;
		int rate;
		int starttime[6];
		int endtime[6];
		bool bFail = false;
		memset(starttime, -1, sizeof(starttime));
		memset(endtime, -1, sizeof(endtime));
		char tmpBuf[MAX_STRING_LENGTH] = { 0, };

		if (fgets(tmpBuf, 256, fpItemdrop) == NULL) bFail = true;
		rate = atoi(tmpBuf);

		for (i = 0; i < 6; i++)
		{
			if (fgets(tmpBuf, 256, fpItemdrop) == NULL)
				bFail = true;
			starttime[i] = atoi(tmpBuf);
		}
		for (i = 0; i < 6; i++)
		{
			if (fgets(tmpBuf, 256, fpItemdrop) == NULL)
				bFail = true;
			endtime[i] = atoi(tmpBuf);
		}
		if (bFail == false)
		{
			gserver->m_nItemDropEventRateBackup = rate;
			for (i = 0; i < 6; i++)
			{
				m_iEventItemdropStart[i] = starttime[i];
				m_iEventItemdropEnd[i] = endtime[i];
			}
		}
		fclose(fpItemdrop);
		fpItemdrop = NULL;
	}
#endif // EVENT_ITEMDROP_AUTO_SAVEFILE

#ifdef NEW_DOUBLE_EVENT_AUTO_SAVEFILE
	FILE* fpDoubleEventAuto = fopen(NEW_DOUBLE_EVENT_AUTO_SAVEFILE, "rt");
	if (fpDoubleEventAuto)
	{
		int i;
		int starttime[6];
		int endtime[6];
		bool bFail = false;
		memset(starttime, -1, sizeof(starttime));
		memset(endtime, -1, sizeof(endtime));
		char tmpBuf[MAX_STRING_LENGTH] = { 0, };
		for (i = 0; i < 6; i++)
		{
			if (fgets(tmpBuf, 256, fpDoubleEventAuto) == NULL)
				bFail = true;
			starttime[i] = atoi(tmpBuf);
		}
		for (i = 0; i < 6; i++)
		{
			if (fgets(tmpBuf, 256, fpDoubleEventAuto) == NULL)
				bFail = true;
			endtime[i] = atoi(tmpBuf);
		}

		if (bFail == false)
		{
			for (i = 0; i < 6; i++)
			{
				m_iDoubleEventStart[i] = starttime[i];
				m_iDoubleEventEnd[i] = endtime[i];
			}
		}
		fclose(fpDoubleEventAuto);
		fpDoubleEventAuto = NULL;
	}
#endif // NEW_DOUBLE_EVENT_AUTO_SAVEFILE

#ifdef NEW_DOUBLE_GM_SAVEFILE
	FILE* fpDoubleEvent = fopen(NEW_DOUBLE_GM_SAVEFILE, "rt");
	if (fpDoubleEvent)
	{
		int 		nDoubleNasPercent;
		int 		nDoubleNasGetPercent;
		int 		nDoubleExpPercent;
		int 		nDoubleSpPercent;
		int 		nDoubleProducePercent;
		int 		nDoubleProduceNum;
#ifdef NEW_DOUBLE_GM_AUTO
		int i;
		int			starttime[6];
		int			endtime[6];
		memset(starttime, -1, sizeof(starttime));
		memset(endtime, -1, sizeof(endtime));
#endif
		char tmpBuf[MAX_STRING_LENGTH] = { 0, };

		bool bFail = false;

		if (fgets(tmpBuf, 256, fpDoubleEvent) == NULL)		bFail = true;
		nDoubleNasPercent = atoi(tmpBuf);

		if (fgets(tmpBuf, 256, fpDoubleEvent) == NULL)		bFail = true;
		nDoubleNasGetPercent = atoi(tmpBuf);

		if (fgets(tmpBuf, 256, fpDoubleEvent) == NULL)		bFail = true;
		nDoubleExpPercent = atoi(tmpBuf);

		if (fgets(tmpBuf, 256, fpDoubleEvent) == NULL)		bFail = true;
		nDoubleSpPercent = atoi(tmpBuf);

		if (fgets(tmpBuf, 256, fpDoubleEvent) == NULL)		bFail = true;
		nDoubleProducePercent = atoi(tmpBuf);

		if (fgets(tmpBuf, 256, fpDoubleEvent) == NULL)		bFail = true;
		nDoubleProduceNum = atoi(tmpBuf);
#ifdef NEW_DOUBLE_GM_AUTO
		bool bReadError = false;
		for (i = 0; i < 6; i++)
		{
			if (fgets(tmpBuf, 256, fpDoubleEvent) == NULL)
				bReadError = true;
			starttime[i] = atoi(tmpBuf);
		}
		for (i = 0; i < 6; i++)
		{
			if (fgets(tmpBuf, 256, fpDoubleEvent) == NULL)
				bReadError = true;
			endtime[i] = atoi(tmpBuf);
		}
#endif // NEW_DOUBLE_GM_AUTO

		if (!bFail)
		{
			m_bDoubleEvent = true;
#ifdef NEW_DOUBLE_GM_AUTO
			m_bDoubleNasPercentBackup = nDoubleNasPercent;
			m_bDoubleNasGetPercentBackup = nDoubleNasGetPercent;
			m_bDoubleExpPercentBackup = nDoubleExpPercent;
			m_bDoubleSpPercentBackup = nDoubleSpPercent;
			m_bDoubleProducePercentBackup = nDoubleProducePercent;
			m_bDoubleProduceNumBackup = nDoubleProduceNum;

			for (i = 0; i < 6; i++)
			{
				m_iDoubleGMStart[i] = starttime[i];
				m_iDoubleGMEnd[i] = endtime[i];
			}

			if (m_bDoubleNasPercentBackup < 0
				|| m_bDoubleNasGetPercentBackup < 0
				|| m_bDoubleExpPercentBackup < 0
				|| m_bDoubleSpPercentBackup < 0
				|| m_bDoubleProducePercentBackup < 0
				|| m_bDoubleProduceNumBackup < 0
				|| m_bDoubleNasPercentBackup > 200
				|| m_bDoubleNasGetPercentBackup > 200
				|| m_bDoubleExpPercentBackup  > 200
				|| m_bDoubleSpPercentBackup  > 200
				|| m_bDoubleProducePercentBackup  > 200
				|| m_bDoubleProduceNumBackup  > 10)
			{
				m_bDoubleNasPercentBackup = DEFAULT_NAS_PERCENT;
				m_bDoubleNasGetPercentBackup = DEFAULT_NAS_GET_PERCENT;
				m_bDoubleExpPercentBackup = DEFAULT_EXP_PERCENT;
				m_bDoubleSpPercentBackup = DEFAULT_SP_PERCENT;
				m_bDoubleProducePercentBackup = DEFAULT_PRO_PERCENT;
				m_bDoubleProduceNumBackup = DEFAULT_PRO_GET_NUMBER;

				GAMELOG << init("WARNING") << "USING DEFAULT DOUBLE EVENT VALUE" << end;
			}
#else
			m_bDoubleNasPercent = nDoubleNasPercent;
			m_bDoubleNasGetPercent = nDoubleNasGetPercent;
			m_bDoubleExpPercent = nDoubleExpPercent;
			m_bDoubleSpPercent = nDoubleSpPercent;
			m_bDoubleProducePercent = nDoubleProducePercent;
			m_bDoubleProduceNum = nDoubleProduceNum;

			if (m_bDoubleNasPercent < 0
				|| m_bDoubleNasGetPercent < 0
				|| m_bDoubleExpPercent < 0
				|| m_bDoubleSpPercent < 0
				|| m_bDoubleProducePercent < 0
				|| m_bDoubleProduceNum < 0
				|| m_bDoubleNasPercent > 200
				|| m_bDoubleNasGetPercent > 200
				|| m_bDoubleExpPercent  > 200
				|| m_bDoubleSpPercent  > 200
				|| m_bDoubleProducePercent  > 200
				|| m_bDoubleProduceNum  > 10)
			{
				m_bDoubleNasPercent = DEFAULT_NAS_PERCENT;
				m_bDoubleNasGetPercent = DEFAULT_NAS_GET_PERCENT;
				m_bDoubleExpPercent = DEFAULT_EXP_PERCENT;
				m_bDoubleSpPercent = DEFAULT_SP_PERCENT;
				m_bDoubleProducePercent = DEFAULT_PRO_PERCENT;
				m_bDoubleProduceNum = DEFAULT_PRO_GET_NUMBER;

				GAMELOG << init("WARNING") << "USING DEFAULT DOUBLE EVENT VALUE" << end;
			}
#endif // NEW_DOUBLE_GM_AUTO
		}

		fclose(fpDoubleEvent);
		fpDoubleEvent = NULL;
	}
#endif // NEW_DOUBLE_GM_SAVEFILE

	SetDungeonTime();

	if (gserver->isActiveEvent(A_EVENT_XMAS))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnEventXmas2007Msg(rmsg, MSG_CONN_EVENT_XMASTREE_POINT);
		SEND_Q(rmsg, gserver->m_connector);
	}

	this->m_RoyalRumble.Init();

	if (!m_Fortunelist.Make_fortune_proto_list(&m_dbdata))
		GAMELOG << init("SYS_ERR")
		<< "Fortune Costume Loading Failed..."
		<< end;

	GAMELOG << init("SYSTEM")
		<< "Entering game loop."
		<< end;


	gserver->LoadRewardItem();
	//gserver->LoadAutomaticReward();

	return true;
}

int CServer::GetMaxPlayers()
{
#ifndef CIRCLE_UNIX
	return MAX_PLAYING;
#else
	int max_descs = 0;
	const char* method;
	/*
	* First, we'll try using getrlimit/setrlimit.  This will probably work
	* on most systems.  HAS_RLIMIT is defined in sysdep.h.
	*/
#ifdef HAS_RLIMIT
	{
		struct rlimit limit;

		/* find the limit of file descs */
		method = "rlimit";
		if (getrlimit(RLIMIT_NOFILE, &limit) < 0)
		{
			GAMELOG << init("SYS_ERR") << "calling getrlimit" << end;
			exit(1);
		}

		/* set the current to the maximum */
		limit.rlim_cur = limit.rlim_max;
		if (setrlimit(RLIMIT_NOFILE, &limit) < 0)
		{
			GAMELOG << init("SYS_ERR") << "calling setrlimit" << end;
			exit(1);
		}
#ifdef RLIM_INFINITY
		if (limit.rlim_max == RLIM_INFINITY)
			max_descs = MAX_PLAYING + NUM_RESERVED_DESCS;
		else
			max_descs = MIN(MAX_PLAYING + NUM_RESERVED_DESCS, limit.rlim_max);
#else
		max_descs = MIN(MAX_PLAYING + NUM_RESERVED_DESCS, limit.rlim_max);
#endif
	}
#elif defined (OPEN_MAX) || defined(FOPEN_MAX)
#if !defined(OPEN_MAX)
#define OPEN_MAX FOPEN_MAX
#endif
	method = "OPEN_MAX";
	max_descs = OPEN_MAX;		/* Uh oh.. rlimit didn't work, but we have
	* OPEN_MAX */
#elif defined (_SC_OPEN_MAX)
	/*
	* Okay, you don't have getrlimit() and you don't have OPEN_MAX.  Time to
	* try the POSIX sysconf() function.  (See Stevens' _Advanced Programming
	* in the UNIX Environment_).
	*/
	method = "POSIX sysconf";
	errno = 0;
	if ((max_descs = sysconf(_SC_OPEN_MAX)) < 0)
	{
		if (errno == 0)
			max_descs = m_MaxPlaying + NUM_RESERVED_DESCS;
		else
		{
			GAMELOG << init("SYS_ERR") << "Error calling sysconf" << end;
			exit(1);
		}
	}
#else
	/* if everything has failed, we'll just take a guess */
	method = "random guess";
	max_descs = m_MaxPlaying + NUM_RESERVED_DESCS;
#endif

	/* now calculate max _players_ based on max descs */
	max_descs = MIN(MAX_PLAYING, max_descs - NUM_RESERVED_DESCS);

	if (max_descs <= 0)
	{
		GAMELOG << init("SYS_ERR") << "Non-positive max player limit!  (Set at" << max_descs << "using" << method << ")." << end;
		exit(1);
	}

	GAMELOG << init("SYSTEM") << "Setting player limit to" << max_descs << "using" << method << "." << end;

	return (max_descs);
#endif /* CIRCLE_UNIX */
}

void CServer::SetHeaders()
{
	int* zones = new int[m_numZone];
	int count = 0;
	int i;
	for (i = 0; i < m_numZone; i++)
	{
		if (m_zones[i].m_bRemote)
			continue;
		zones[count++] = m_zones[i].m_index;
	}

	MsgrConnectMsg(m_messengerConnMsg, SERVER_VERSION, m_serverno, m_subno, count, zones);
	ConnConnectMsg(m_connectorConnMsg, SERVER_VERSION, m_serverno, m_subno, count, zones);
	HelperConnectMsg(m_helperConnMsg, SERVER_VERSION, m_serverno, m_subno, count, zones);
	SubHelperConnectMsg(m_subHelperConnMsg, SERVER_VERSION, m_serverno, m_subno, count, zones);
	delete[] zones;
	zones = NULL;
}

void CServer::CloseSocket(CDescriptor* d)
{
	if (m_descLoop == d)
	{
		m_descLoop = NULL;
		m_bLoop = 0;
	}

	if (m_observer == d)
	{
		m_observer = NULL;
	}

	for (int i = 0; i < 20; i++)
	{
		if (m_chatmonitor[i] == d)
		{
			m_chatmonitor[i] = NULL;
		}
	}
#ifdef GMTOOL
	for (int i = 0; i < gserver->m_nGMToolCount; ++i)
	{
		if (gserver->m_gmtool[i] == d)
		{
			gserver->m_gmtool[i] = NULL;
		}
	}
#endif // GMTOOL

	if (d->m_pChar)
	{
		d->m_pChar->ProcDisconnect(true, false);
		d->m_pChar->OutputDBItemLog();
	}

	if (d->m_pChar)
	{
		if (PCManager::instance()->isPlaying(d->m_pChar))
		{
			d->m_pChar->m_bPlaying = false;
			// remove form player list..

			PCManager::instance()->deletePlayerByPC(d->m_pChar);

			// �� ������ �α� �����
			GAMELOG << init("HAVE_MONEY", d->m_pChar->m_name, d->m_pChar->m_nick, d->m_idname)
				<< d->m_pChar->m_inventory.getMoney()
				<< end;

			// ���� ������ �α� �����
			for (int i = 0; i < MAX_WEARING; i++)
			{
				if (d->m_pChar->m_wearInventory.wearItemInfo[i])
				{
					CItem* p = d->m_pChar->m_wearInventory.wearItemInfo[i];
					GAMELOG << init("WEAR ITEM", d->m_pChar->m_name, d->m_pChar->m_nick, d->m_idname)
						<< itemlog(p)
						<< end;
				}
			}

			// ���� �� �α� �����
			CPet* petNext = d->m_pChar->m_petList;
			CPet* pet;
			while ((pet = petNext))
			{
				petNext = pet->m_nextPet;
				// TODO : petlog
				GAMELOG << init("PET INFO", d->m_pChar)
					<< "PET" << delim
					<< pet->m_index << delim
					<< pet->GetPetType() << delim
					<< pet->GetPetGrade() << delim
					<< "LEVEL" << delim
					<< pet->m_level << delim
					<< "AP" << delim
					<< pet->GetAbilityPoint()
					<< end;
			}

			CAPet* apet_next = d->m_pChar->m_pApetlist;
			CAPet* apet;
			while ((apet = apet_next))
			{
				apet_next = apet->m_pNextPet;
				GAMELOG << init("APET_INPO", d->m_pChar)
					<< "APET" << apet->m_index << delim << apet->m_name << delim << apet->m_pProto->Index() << delim
					<< "LEVEL" << delim << apet->m_level << delim << "EXP" << delim << apet->m_exp << end;
			}

			// ĳ�� ������ ���� �α� �����
			int nAssistABSTypeCount = d->m_pChar->m_assist.GetABSTimeTypeList(NULL);
			if (nAssistABSTypeCount > 0)
			{
				int* nAssistABSItemIndex = new int[nAssistABSTypeCount];
				int* nAssistABSSkillIndex = new int[nAssistABSTypeCount];
				int* nAssistABSSkillLevel = new int[nAssistABSTypeCount];
				char* nAssistABSHit0 = new char[nAssistABSTypeCount];
				char* nAssistABSHit1 = new char[nAssistABSTypeCount];
				char* nAssistABSHit2 = new char[nAssistABSTypeCount];
				int* nAssistABSEndTime = new int[nAssistABSTypeCount];

				d->m_pChar->m_assist.GetABSTimeTypeList(nAssistABSItemIndex, nAssistABSSkillIndex, nAssistABSSkillLevel, nAssistABSHit0, nAssistABSHit1, nAssistABSHit2, nAssistABSEndTime);
				for (int i = 0; i < nAssistABSTypeCount; i++)
				{
					GAMELOG << init("CASH_ABS_ASSIST", d->m_pChar)
						<< nAssistABSItemIndex[i] << delim
						<< nAssistABSSkillIndex[i] << delim
						<< nAssistABSSkillLevel[i] << delim
						<< nAssistABSHit0[i] << delim
						<< nAssistABSHit1[i] << delim
						<< nAssistABSHit2[i] << delim
						<< nAssistABSEndTime[i] << end;
				}
			}
			// �޸� ��ũ�� ���� â�� Ȯ�� ī�� ���� �ð� �α� �����
			GAMELOG << init("CASH_MEMPOS_STASH_TIME", d->m_pChar)
				<< d->m_pChar->m_memposTime << delim
				<< d->m_pChar->m_stashextTime << end;

#ifdef GER_LOG
			//const int BUFSIZE = 128;
			//char buf[BUFSIZE]="";
			//d->m_pChar->GetCalcInGameTime(buf, BUFSIZE);

			GAMELOGGEM << init(0, "CHAR_LEAVE_GAME")
				<< LOG_VAL("account-id", d->m_idname) << blank
				<< LOG_VAL("char-id", d->m_pChar->m_name) << blank
				//<< LOG_VAL("in-game",buf) << blank
				<< endGer;

			GAMELOGGEM << init(0, "ACCOUNT_LOGOUT")
				<< LOG_VAL("account-id", d->m_idname) << blank
				<< LOG_VAL("char-id", d->m_pChar->m_name) << blank
				//<< LOG_VAL("in-game", buf) << blank
				<< endGer;
			// ���� ������ �ð� ���� �ʿ�.
#endif // GER_LOG
			GAMELOG << init("DISCONNECT", d->m_pChar->m_name, d->m_pChar->m_nick, d->m_idname)
				<< end;

			//�̺����̼� ���� Ǯ��
			if (d->m_pChar->m_evocationIndex > EVOCATION_NONE)
			{
				d->m_pChar->Unevocation();
			}
#ifdef CAPTURE_THE_FLAG_10282021
			if (d->m_pChar->m_inventory.FindByDBIndex(12272) != NULL && !d->m_pChar->IsInPeaceZone(true))
			{
				CItem* pitem11272 = NULL;
				pitem11272 = d->m_pChar->m_inventory.FindByDBIndex(12272, 0, 0);

				item_search_t vec_pvpflagitem;

				int sc = d->m_pChar->m_inventory.searchItemByCondition(12272, 0, 0, vec_pvpflagitem);
				// make sure the user doesnt have more then he should of the item
				if (sc == 0 || sc < 1)
					return;
				//delete item from inventory user died
				d->m_pChar->m_inventory.deleteItem(vec_pvpflagitem, 1);

				CQuest* pQuest = d->m_pChar->m_questList.FindQuest(818);
				if (pQuest && pQuest->GetQuestState() == QUEST_STATE_RUN)
				{
					d->m_pChar->m_questList.SetQuestState(pQuest, QUEST_STATE_ABANDON);
					{
						CNetMsg::SP rmsg(new CNetMsg);
						QuestForceGiveUpMsg(rmsg, pQuest);
						d->m_pChar->m_questList.DelQuest(d->m_pChar, pQuest);
						SEND_Q(rmsg, d->m_pChar->m_desc);
					}
					d->m_pChar->m_questList.DecreaseQuestComepleteCount();
				}

				d->m_pChar->m_bHasFlagItem = false;

				int npcindex = 1704;
				//make sure the npc isn't null (crash)
				CNPC* npc = gserver->m_npcProtoList.Create(npcindex, NULL);
				if (!npc)
					return;
				//grab the information for the mob from the dead player
				GET_X(npc) = GET_X(d->m_pChar);
				GET_Z(npc) = GET_Z(d->m_pChar);
				GET_YLAYER(npc) = GET_YLAYER(d->m_pChar);
				GET_R(npc) = GetRandom(0, (int)(PI_2 * 10000)) / 10000;

				if (d->m_pChar->m_pArea->GetAttr(GET_YLAYER(npc), GET_X(npc), GET_Z(npc)) & MATT_WALKABLE) {}


				npc->m_regenX = GET_X(npc);
				npc->m_regenY = GET_YLAYER(npc);
				npc->m_regenZ = GET_Z(npc);

				int cx, cz;
				d->m_pChar->m_pArea->AddNPC(npc);
				d->m_pChar->m_pArea->PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
				d->m_pChar->m_pArea->CharToCell(npc, GET_YLAYER(npc), cx, cz);

				{
					CNetMsg::SP rmsg(new CNetMsg);
					AppearMsg(rmsg, npc, true);
					d->m_pChar->m_pArea->SendToCell(rmsg, GET_YLAYER(npc), cx, cz);
				}

				{
					//annouce message to all with flag position
					CNetMsg::SP rmsg(new CNetMsg);
					SysMsgFlagDC(rmsg, d->m_pChar->m_nick, d->m_pChar->m_pos.m_x, d->m_pChar->m_pos.m_z);
					PCManager::instance()->sendToAll(rmsg);
				}
			}
#endif
			if (d->m_pChar->m_guildInfo != NULL && d->m_pChar->m_guildInfo->guild() != NULL)
			{
				CGuild* guild = d->m_pChar->m_guildInfo->guild();
				if (guild->boss()->GetPC() == d->m_pChar)
				{
					GuildBattleManager::instance()->delete_banish(guild->index());
					if (GuildBattleManager::instance()->cancel(guild->index()) == true)
					{
						guild->m_isUseTheStashAndSkill = true;

						CNetMsg::SP rmsg(new CNetMsg);
						ServerToServerPacket::makeGuildBattleStashLockOff(rmsg, guild->index());
						SEND_Q(rmsg, gserver->m_helper);
					}
				}

				if (guild->battleState() == GUILD_BATTLE_STATE_ING)
				{
					//����� ���� ó��
					GuildBattleManager::instance()->giveup(d->m_pChar->m_index);
				}
			}
			LOG_INFO("LOGOUT_INFO > name[%s], exp[%d], sp[%d], fp[%d]", d->m_pChar->GetName(), d->m_pChar->m_exp, d->m_pChar->m_skillPoint, d->m_pChar->m_syndicateManager.getSyndicatePoint(d->m_pChar->getSyndicateType()));
		}

		DBManager::instance()->SaveCharacterInfo(d, true);
	}

	if (d->m_idname[0] != '\0')
	{
		{
			struct tm connecttm;
			memcpy(&connecttm, localtime(&d->m_connect_time), sizeof(connecttm));

			struct tm disconnecttm;
			memcpy(&disconnecttm, localtime(&gserver->m_nowseconds), sizeof(disconnecttm));

			LOG_INFO("TOTAL CONNECTION TIME : userIndex : %d userId : %s time : %04d-%02d-%02d %02d:%02d:%02d - %04d-%02d-%02d %02d:%02d:%02d total_sec : %d sec",
				d->m_index, (const char*)d->m_idname,
				connecttm.tm_year + 1900, connecttm.tm_mon + 1, connecttm.tm_mday,
				connecttm.tm_hour, connecttm.tm_min, connecttm.tm_sec,
				disconnecttm.tm_year + 1900, disconnecttm.tm_mon + 1, disconnecttm.tm_mday,
				disconnecttm.tm_hour, disconnecttm.tm_min, disconnecttm.tm_sec,
				(gserver->m_nowseconds - d->m_connect_time)
			);
		}

		// �α����� ������ �ϰ�, �θ��� ���� ������ ó��
		// ���� �θ��� �ߴٸ�, ������ ���� �� ó��
		if (d->m_pChar == NULL)
		{
			// Connector Server�� �α׾ƿ� ������
			// Connector Server������ id�� ã�� ���ϸ� return��
			CNetMsg::SP rmsg(new CNetMsg);
			ConnLogoutMsg(rmsg, d->m_idname);
			SEND_Q(rmsg, m_connector);

			LOG_INFO("send logout msg to Connector : user_index[%d] id[%s]", d->m_index, (const char*)d->m_idname);

			{
				// Helper, SubHelper���� ���� ������ ����
				CNetMsg::SP rmsg(new CNetMsg);
				ServerToServerPacket::makeLogoutUserInfo(rmsg, d->m_index);
				SEND_Q(rmsg, gserver->m_helper);
				SEND_Q(rmsg, gserver->m_subHelper);
			}
		}
	}
}

void CServer::CommandInterpreter(CDescriptor* d, CNetMsg::SP& msg)
{
	CPC* ch = d->m_pChar;

	if (gcmdlist.Find(msg->m_mtype) == false)
	{
		LOG_ERROR("HACKING : invalid command[%d]. charIndex[%d]", msg->m_mtype, ch->m_index);
		d->Close("Invalid command");
		return;
	}

	if (msg->m_mtype != MSG_MOVE)
	{
		if (m_pulse - d->m_checktics >= PULSE_REAL_SEC)
		{
			// 1�ʸ��� ���� �� ���� ī���͸� �ʱ�ȭ �Ѵ�.
			// ��, 1�ʿ� ��� ������ ������ �� �ִ��� ���ϰ�
			// �̰����� �ʱ�ȭ �Ǳ� ���� ������ ������ �ѱ�� ��� ������ �����ϸ� �ȴ�
			if (d->m_commandcount > 20)
			{
				if (d->m_pChar) {
					CDBCmd cmd;
					cmd.Init(&gserver->m_dbchar);
					std::string insert_hack = boost::str(boost::format("insert into t_hack_command (a_idname, a_command_count, a_nick) value ('%s',%d,'%s')") % d->m_idname.GetBuffer() % d->m_commandcount % d->m_pChar->m_nick.GetBuffer());
					cmd.SetQuery(insert_hack);
					cmd.Update();
					GAMELOG << init("HACK COMMAND", d->m_pChar->m_name, d->m_pChar->m_nick, d->m_idname);
				}
				else {
					GAMELOG << init("HACK COMMAND", d->m_idname);
				}

				GAMELOG << d->m_commandcount
					<< end;

				// TODO : �� ī��Ʈ ����
				if (d->IncreaseHackCount(1) == true)
				{
					return;
				}
			}
			d->m_checktics = m_pulse;
			d->m_commandcount = 0;
		}

		d->m_commandcount++;
	}

	pTypeBase* pbase = reinterpret_cast<pTypeBase*>(msg->m_buf);
	int debug_type = pbase->type;
	int debug_subtype = pbase->subType;

	//if(debug_type != MSG_MOVE)
		//LOG_INFO("DEBUG_FUNC : START : type : %d : subtype : %d", debug_type, debug_subtype);

	gcmdlist.Run(msg->m_mtype, ch, msg);

	//if(debug_type != MSG_MOVE)
		//LOG_INFO("DEBUG_FUNC : END : type : %d : subtype : %d", debug_type, debug_subtype);
}

void CServer::DecreaseTimeForPC(CPC* ch)
{
	/////////////////////////////////////////////
	// BANGWALL : 2005-06-27 ���� 7:09:33
	// Comment : pd4 �ð�ó��

	if (ch->m_pd4StartTime > 0)
	{
		ch->m_pd4StartTime -= TIME_ONE_SECOND;
		if (ch->m_pd4StartTime <= 0)
		{
			CQuest* pQueset = ch->m_questList.FindQuest(105);
			if (pQueset && pQueset->GetQuestState() == QUEST_STATE_RUN)
			{
				{
					CNetMsg::SP rmsg(new CNetMsg);
					QuestFailMsg(rmsg, pQueset);
					SEND_Q(rmsg, ch->m_desc);
				}

				//do_Quest(ch, msg);

				{
					///////////////////////////////////
					// pd4 ����Ʈ�̸� helper ��ŷ�� ��� : BW
					//
					// char index�� ����
					CNetMsg::SP rmsg(new CNetMsg);

					rmsg->Init(MSG_HELPER_COMMAND);
					RefMsg(rmsg) << MSG_HELPER_PD4_RANK_END
						<< ch->m_index
						<< pQueset->GetQuestValue(0)
						<< 0;

					GAMELOG << init("PD4 END", ch->m_name, ch->m_nick, ch->m_desc->m_idname)
						<< pQueset->GetQuestValue(0) << end;

					if (gserver->isRunHelper())
					{
						SEND_Q(rmsg, gserver->m_helper);
					}
					else
					{
						GAMELOG << init("PD4 QUEST ERROR : RANK END ERROR NOT HELPER")
							<< ch->m_index << end;
					}
				}
			}

			ch->m_pd4StartTime = 0;
		}
	}

	if (ch->IsSetPlayerState(PLAYER_STATE_PKMODEDELAY))
	{
		if (ch->m_pkmodedelay > 0)
		{
			ch->m_pkmodedelay -= TIME_ONE_SECOND;
			if (ch->m_pkmodedelay < 0)
				ch->m_pkmodedelay = 0;
		}
		else
		{
			ch->ResetPlayerState(PLAYER_STATE_PKMODE | PLAYER_STATE_PKMODEDELAY);
			ch->m_pkmodedelay = 0;
			ch->CalcStatus(true);//Cloud
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeAction(rmsg, ch, 0, AGT_PKMODE);
			ch->m_pArea->SendToCell(rmsg, ch, true);
		}
	}

	// ���� �ý��� �ð� üũ
	if (ch->m_teachType != MSG_TEACH_NO_TYPE && ch->m_teachType != MSG_TEACH_NO_STUDENT_TYPE)
	{
		// �߽����� �������� 10���� �����ٸ� ���踦 ������ �����Ѵ�.
		if (ch->m_teachType == MSG_TEACH_TEACHER_TYPE)
		{
			// �ʰ��� ������� �޼���
			if (ch->m_displayCanSstone
				&& ((ch->m_fame >= 1000 && ch->m_superstone < 1)
					|| (ch->m_fame >= 2000 && ch->m_superstone < 2)
					|| (ch->m_fame >= 3000 && ch->m_superstone < 3)))
			{
				CNetMsg::SP rmsg(new CNetMsg);
				SysEnableSuperStoneMsg(rmsg, ch->m_fame);
				SEND_Q(rmsg, ch->m_desc);
				ch->m_displayCanSstone = false;
			}
		}
		else if (ch->m_teachType == MSG_TEACH_LIMITE_DAY_FAIL)  // ���� ���谡 10���� ���� ������ �߽����� ���
		{
			if (ch->m_teachTime[0] >= TEACH_STUDENT_MAX_GIVEUP)
				ch->m_teachType = MSG_TEACH_NO_STUDENT_TYPE;
			else
				ch->m_teachType = MSG_TEACH_NO_TYPE;

			{
				CNetMsg::SP rmsg(new CNetMsg);
				TeachEndMsg(rmsg, -1, "none", ch->m_index, ch->m_name, MSG_TEACH_END_FAIL);
				SEND_Q(rmsg, ch->m_desc);
			}

			{
				CNetMsg::SP rmsg(new CNetMsg);
				HelperTeacherGiveup(rmsg, -1, ch->m_index, ch->m_teachType, ch->m_teachTime[0]);
				SEND_Q(rmsg, gserver->m_helper);
			}
		}
	}

	// ��������϶�
	if (ch->IsSetPlayerState(PLAYER_STATE_RAMODE))
	{
		// ������� ����Ʈ�� �ִ�
		bool bHaveTarget = false;

		CRaChar* raList;
		CRaChar* raListNext = ch->m_raList;

		while ((raList = raListNext))
		{
			raListNext = raList->m_next;

			// �����ڸ� �ش�
			if (!raList->m_bAttacker)
				continue;
			raList->m_raPulse -= TIME_ONE_SECOND;
			if (raList->m_raPulse < 0)
				raList->m_raPulse = 0;

			if (raList->m_raPulse < 1)
			{
				if (NULL == TO_PC(raList->m_raTarget))
					continue;
				CPC* praTarget = PCManager::instance()->getPlayerByCharIndex(raList->m_raTarget->m_index);
				if (praTarget)
				{
					DelRaList(raList->m_raTarget);
				}
				else
				{
					return;
				}
				continue;
			}

			if (raList->m_raPulse == RAMODE_DELAY_PULSE)
			{
				bHaveTarget = true;
				CNetMsg::SP rmsg(new CNetMsg);
				RightAttackMsg(rmsg, raList->m_raTarget, MSG_RIGHT_ATTACK_DELAY);
				SEND_Q(rmsg, ch->m_desc);
				SEND_Q(rmsg, raList->m_raTarget->m_desc);
				continue;
			}
			bHaveTarget = true;
		}

		if (!bHaveTarget)
			ch->ResetPlayerState(PLAYER_STATE_RAMODE);
		ch->CalcStatus(true);//Cloud
	}

	// �������϶�
	if (ch->IsSetPlayerState(PLAYER_STATE_CHANGE) && ch->m_changeIndex != -1)
	{
		//ch->m_changePulse--;
		ch->m_changePulse -= TIME_ONE_SECOND;
		if (ch->m_changePulse < 0)
			ch->m_changePulse = 0;

		if (ch->m_changePulse < 1)
			ch->CancelChange();
	}

#ifdef WARFARE_BATTLE
	if (gserver->m_BattleWarfare.IsNotice(ch)) {
		LOG_INFO("Warfare Battle invite to %s", ch->m_nick.getBuffer());
		ch->m_bBattleWarfare = true;
		CNetMsg::SP rmsg(new CNetMsg);
		MoveBattleWarfareMsg(rmsg, ch->m_index);
		SEND_Q(rmsg, ch->m_desc);
	}
#endif

	// 1�ð��� PK ���� 1����Ʈ ȸ��
	if (ch->m_pkRecoverPulse != 0 && ch->m_pArea)
	{
		//ch->m_pkRecoverPulse--;
		ch->m_pkRecoverPulse -= TIME_ONE_SECOND;

		if (ch->m_pkRecoverPulse <= 0)
		{
			if (ch->m_pkPenalty < 0)
			{
				if (!gserver->m_bNonPK)
					ch->m_pkPenalty += 10;

				CNetMsg::SP rmsg(new CNetMsg);
				CharStatusMsg(rmsg, ch, 0);
				ch->m_pArea->SendToCell(rmsg, ch, false);
				ch->m_bChangeStatus = true;
			}

			if (ch->m_pkPenalty < 0)
				ch->m_pkRecoverPulse = TIME_ONE_HOUR;
			else
				ch->m_pkRecoverPulse = 0;
		}
	}

	// ���� ��ų�� ���� �ִٸ�, ���� �ð��� ��ٸ�, AppearMsg�� ������ �ϴ� ��Ȳ�̶��
	if (ch->m_currentSkill && ch->m_currentSkill->m_state == SKILL_CON_FIRE && ch->m_bCheckAppear)
	{
		// Ÿ�� �˻�, ���� Ÿ���� �ְ�
		if (ch->m_currentSkill->m_targetIndex != -1 && ch->m_pArea)
		{
			// ���� Ÿ���� ���ؼ�
			CCharacter* tch = ch->m_pArea->FindCharInCell(ch, ch->m_currentSkill->m_targetIndex, ch->m_currentSkill->m_targetType, false);
			// Ÿ���� ���ų� ������ �ٸ���
			if (tch)
			{
				boost::scoped_array<MultiTarget> temp(new MultiTarget[ch->m_skillTargetCount]);

				for (int i = 0; i < ch->m_skillTargetCount; ++i)
				{
					temp[i].mtargettype = ch->m_targettype[i];
					temp[i].mtargetindex = ch->m_targetindex[i];
				}

				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeSkillFireMsg(rmsg, ch, ch->m_currentSkill, tch, ch->m_skillTargetCount, temp.get(), 0, 0.0f, 0.0f, 0.0f, 0.0f, 0);
				ch->m_pArea->SendToCell(rmsg, ch, true);
			}
		}

		// skillfireMsg�� �������Ƿ� ����
		ch->m_bCheckAppear = false;
	}

	// ��ų ��� ���·�
	// �װų�
	// ��ų �ߵ����� �ð� ��������
	if (ch->m_currentSkill
		&& (DEAD(ch) || (ch->m_currentSkill->m_state == SKILL_CON_FIRE && m_pulse - ch->m_currentSkill->m_usetime > ch->m_currentSkill->m_proto->m_readyTime + ch->m_currentSkill->m_proto->m_stillTime + ch->m_currentSkill->m_proto->m_fireTime)))
	{
		ch->m_currentSkill->Cancel(ch);
		ch->m_currentSkill = NULL;
	}

	// assist �ð� ����
	ch->m_assist.DecreaseTime();

	// pc ���� ȸ��
	if (!DEAD(ch) && m_pulse - ch->m_recoverPulse >= PC_RECOVER_PULSE)
	{
		ch->RecoverPC();
		ch->m_recoverPulse = m_pulse;
	}

	// ������ ȸ�� ó��
	if (ch->m_recoverHPItemTime > 0)
	{
#ifdef BUGFIX_DEAD_AGAIN_DEAD
		if (DEAD(ch) || (mktime(&gserver->m_tRealSystemTime) - ch->m_deadTime < BUGFIX_DEAD_SECONDS)) {
			ch->m_recoverHPItemTime = 0;
		}
		else
#endif
		{
			ch->m_recoverHPItemTime -= TIME_ONE_SECOND;
			if (ch->m_recoverHPItemTime < 0)
				ch->m_recoverHPItemTime = 0;
			if (ch->m_recoverHPItemTime % 10 == 0)
			{
				ch->m_hp += ch->m_recoverHPItemValue;
				if (ch->m_hp > ch->m_maxHP)
					ch->m_hp = ch->m_maxHP;
				ch->m_bChangeStatus = true;
			}
		}
	}

	if (ch->m_recoverMPItemTime > 0)
	{
		if (DEAD(ch))
			ch->m_recoverMPItemTime = 0;
		else
		{
			ch->m_recoverMPItemTime -= TIME_ONE_SECOND;
			if (ch->m_recoverMPItemTime < 0)
				ch->m_recoverMPItemTime = 0;
			if (ch->m_recoverMPItemTime % 10 == 0)
			{
				ch->m_mp += ch->m_recoverMPItemValue;
				if (ch->m_mp > ch->m_maxMP)
					ch->m_mp = ch->m_maxMP;
				ch->m_bChangeStatus = true;
			}
		}
	}

	// ���� ������ ó��
	if (ch->m_billReqTime > 0)
	{
		ch->m_billReqTime -= TIME_ONE_SECOND;
		if (ch->m_billReqTime <= 0)
		{
			ch->ResetPlayerState(PLAYER_STATE_CASHITEM);
			ch->m_billReqTime = 0;
		}
	}

	// ���� �̵� ó��
	if (ch->m_reqWarpTime > 0)
	{
		if (DEAD(ch))
		{
			ch->m_reqWarpTime = 0;
			ch->m_reqWarpType = -1;
			ch->m_reqWarpData = -1;
			ch->ResetPlayerState(PLAYER_STATE_SITDOWN | PLAYER_STATE_MOVING | PLAYER_STATE_WARP);
		}
		else
		{
			ch->m_reqWarpTime -= TIME_ONE_SECOND;
			if (ch->m_reqWarpTime <= 0)
			{
				{
					CNetMsg::SP rmsg(new CNetMsg);
					WarpEndMsg(rmsg, ch);
					ch->m_pArea->SendToCell(rmsg, ch, true);
				}

				switch (ch->m_reqWarpType)
				{
				case IONCE_WARP_RETURN:
				{
					int zone;
					int zonepos;
					CZone* pZone = NULL;

					// �±� pvp �� �̵� ��������
					// ��ȯ ��ũ���� num1�� ����ȣ�� ���ϴ�.
					// ���� ��� �߰��մϴ� : bw
					if (ch->m_reqWarpData != -1)
					{
						zone = ch->m_reqWarpData;
						zonepos = 0;
						pZone = gserver->FindZone(zone);
					}
					else
					{
						pZone = gserver->FindNearestZone(ch->m_pZone->m_index, GET_X(ch), GET_Z(ch), &zone, &zonepos);

						if (ch->m_pZone->IsComboZone())
						{
							zone = ZONE_COMBO_DUNGEON;
							pZone = gserver->FindZone(ZONE_COMBO_DUNGEON);
							zonepos = 0;
						}

						// ���̵忡�� ������ ������ ������ ����.
						if (ch->m_pZone->m_index == ZONE_ALTER_OF_DARK
							|| ch->m_pZone->m_index == ZONE_CAPPELLA_1
							|| ch->m_pZone->m_index == ZONE_CAPPELLA_2)
						{
							zone = ZONE_MONDSHINE;
							pZone = gserver->FindZone(ZONE_MONDSHINE);
							zonepos = 0;
						}
						if (ch->m_pZone->m_index == ZONE_AKAN_TEMPLE)
						{
							zone = ZONE_EGEHA;
							pZone = gserver->FindZone(ZONE_EGEHA);
							zonepos = 0;
						}
						if (ch->m_pZone->m_index == ZONE_TARIAN_DUNGEON)
						{
							zone = ZONE_TARIAN;
							pZone = gserver->FindZone(ZONE_TARIAN);
							zonepos = 1;
						}
						if (ch->m_pZone->m_index == ZONE_ENCHANTED_DUNGEON)	//Val add new raid set return zone
						{
							zone = ZONE_MISTY_CANYON_EXTREME;
							pZone = gserver->FindZone(ZONE_MISTY_CANYON_EXTREME);
							zonepos = 0;
						}
						if (ch->m_pZone->m_index == ZONE_RVR)
						{
							zone = ZONE_RVR;
							pZone = gserver->FindZone(ZONE_RVR);
							zonepos = ch->m_syndicateType;
						}
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
						if (ch->m_pZone->m_index == ZONE_PARTY_DUNGEON0
							|| ch->m_pZone->m_index == ZONE_PARTY_DUNGEON1
							|| ch->m_pZone->m_index == ZONE_PARTY_DUNGEON2
							|| ch->m_pZone->m_index == ZONE_PARTY_DUNGEON3
							|| ch->m_pZone->m_index == ZONE_PARTY_DUNGEON4
							)
						{
							zone = ZONE_START;
							pZone = gserver->FindZone(ZONE_START);
							zonepos = 0;
						}
#endif
					}

					if (pZone == NULL)
					{
						zone = ZONE_START;
						pZone = gserver->FindZone(zone);
						zonepos = 0;
					}

					if (pZone)
					{
						// 060109 : BS : BEGIN : ���̵� �޽��� ������� �ʰ� ���� ȣ��
						GoZone(ch, zone,
							pZone->m_zonePos[zonepos][0],														// ylayer
							GetRandom(pZone->m_zonePos[zonepos][1], pZone->m_zonePos[zonepos][3]) / 2.0f,		// x
							GetRandom(pZone->m_zonePos[zonepos][2], pZone->m_zonePos[zonepos][4]) / 2.0f);		// z
						LOG_ERROR("Zone crash detected: zone=%d, pZone=%p", zone, pZone);
					}
				}
				break;

				case IONCE_WARP_MEMPOS:
					ch->GoMemPos(ch->m_reqWarpData);
					break;

				case IONCE_WARP_NPC_PORTAL_SCROLL:
					ch->GoNpcPortalScroll();
					ch->m_Npc_Portal_x = -1;
					ch->m_Npc_Portal_z = -1;
					ch->m_Npc_Portal_y = -1;
					break;

				}

				ch->m_reqWarpTime = 0;
				ch->m_reqWarpType = -1;
				ch->m_reqWarpData = -1;
				ch->ResetPlayerState(PLAYER_STATE_SITDOWN | PLAYER_STATE_MOVING | PLAYER_STATE_WARP);
			}
		}
	}

	if (ch->m_reqWarpTime_skill > 0)
	{
		if (DEAD(ch))
		{
			ch->m_reqWarpTime_skill = 0;
			ch->m_reqWarpType_skill = -1;
			ch->m_reqWarpData_skill = -1;
			ch->ResetPlayerState(PLAYER_STATE_SITDOWN | PLAYER_STATE_MOVING | PLAYER_STATE_WARP);
		}
		else
		{
			ch->m_reqWarpTime_skill -= TIME_ONE_SECOND;
			if (ch->m_reqWarpTime_skill <= 0)
			{
				{
					CNetMsg::SP rmsg(new CNetMsg);
					WarpEndMsg(rmsg, ch);
					ch->m_pArea->SendToCell(rmsg, ch, true);
				}

				switch (ch->m_reqWarpType_skill)
				{
				case MOVE_TO_GUILDROOM:
				{
					CZone* pZone = gserver->FindZone(ZONE_GUILDROOM);
					int area_count = 0;

					if (pZone == NULL)
						break;

					// �±� pvp �� �̵� ��������
					// ��ȯ ��ũ���� num1�� ����ȣ�� ���ϴ�.
					// ���� ��� �߰��մϴ� : bw

					if (!ch->m_guildInfo || !(ch->m_guildInfo->guild()))
					{
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsg(rmsg, MSG_SYS_DO_NOT_GO_ZONE_GMORDER);
						SEND_Q(rmsg, ch->m_desc);
						break;
					}

					int idx;
					for (idx = 0; idx < pZone->m_countArea; idx++)
					{
						if (!pZone->m_area[idx].m_bEnable)
							continue;

						if (pZone->m_area[idx].m_guildIndex == ch->m_guildInfo->guild()->index())
						{
							area_count = idx;
							break;
						}
					}

					if (idx == pZone->m_countArea)
					{
						area_count = pZone->SetEnableArea();
						// �� ���� ����
						if (area_count == -1)
						{
							CNetMsg::SP rmsg(new CNetMsg);
							SysMsg(rmsg, MSG_SYS_SINGLEDUNGEON_FULL);
							SEND_Q(rmsg, ch->m_desc);
							break;
						}
						pZone->m_area[area_count].m_guildIndex = ch->m_guildInfo->guild()->index();
					}

					if (pZone)
					{
						// 060109 : BS : BEGIN : ���̵� �޽��� ������� �ʰ� ���� ȣ��
						GoZone(ch, ZONE_GUILDROOM,
							pZone->m_zonePos[0][0],														// ylayer
							GetRandom(pZone->m_zonePos[0][1], pZone->m_zonePos[0][3]) / 2.0f,		// x
							GetRandom(pZone->m_zonePos[0][2], pZone->m_zonePos[0][4]) / 2.0f);	// z
					}
				}
				break;
				}

				ch->m_reqWarpTime_skill = 0;
				ch->m_reqWarpType_skill = -1;
				ch->m_reqWarpData_skill = -1;
				ch->ResetPlayerState(PLAYER_STATE_SITDOWN | PLAYER_STATE_MOVING | PLAYER_STATE_WARP);
			}
		}
	}

	// �۽��� ���� ���� ī��Ʈ ����
	time_t pdtime;
	struct tm tm1 = NOW();

	struct tm tm2;

	if ((ch->m_pd3Count && ch->m_pd3Time) || (ch->m_pd3Count && ch->m_pd3Time == 0))
	{
		pdtime = ch->m_pd3Time;
		memcpy(&tm2, localtime(&pdtime), sizeof(struct tm));
		if (tm1.tm_yday != tm2.tm_yday)
			ch->m_pd3Count = 0;
	}
	if ((ch->m_pd4Count && ch->m_pd4Time) || (ch->m_pd4Count && ch->m_pd4Time == 0))
	{
		pdtime = ch->m_pd4Time;
		memcpy(&tm2, localtime(&pdtime), sizeof(struct tm));
		if (tm1.tm_yday != tm2.tm_yday)
			ch->m_pd4Count = 0;
	}


	CQuest* pQuestNext = NULL, * pQuest;
	pQuestNext = ch->m_questList.GetNextQuest(NULL);
	int index_debug = 0;
	int level_debug = 0;
	int loop_count_debug = 0;
	int quest_index = 0;
	while ((pQuest = pQuestNext))
	{
		/////////////////// ����� ���� swkwon (10.03.16)///////////////////
		index_debug = ch->m_index;
		level_debug = ch->m_level;
		loop_count_debug++;
		if (pQuestNext != NULL)
			quest_index = pQuestNext->GetQuestIndex();
		/////////////////// ����� ���� swkwon (10.03.16)///////////////////
		pQuestNext = ch->m_questList.GetNextQuest(pQuestNext);
		switch (pQuest->GetQuestState())
		{
		case QUEST_STATE_RUN:
		case QUEST_STATE_DONE:
			if (pQuest->GetQuestState() == QUEST_STATE_RUN && pQuest->GetQuestProto()->m_failValue > 0)
			{
				if (pQuest->GetFailValue() < gserver->getNowSecond())
				{
					// Ÿ�Ӿ��� ����Ʈ ����
					CNetMsg::SP rmsg(new CNetMsg);
					QuestFailMsg(rmsg, pQuest);
					SEND_Q(rmsg, ch->m_desc);

					ch->m_questList.DelQuest(ch, pQuest);
				}
			}

			else if ((pQuest->GetQuestType1() == QTYPE_REPEAT_DAY || pQuest->GetQuestType1() == QTYPE_REPEAT_WEEK) && (pQuest->GetQuestState() == QUEST_STATE_DONE)) //dethunter12
			{
				// �� �Ѿ���� ����
				time_t nowtime;
				time(&nowtime);
				if (nowtime >= pQuest->GetCompleteTime())
				{
					ch->m_questList.DelQuest(ch, pQuest, QUEST_STATE_DONE);

					// ����Ʈ ���� �޽��� ����
				}
			}
			break;
		}
	}


	////////////////////////
	// ���� �˻��ؾ� �� ��ƾ
	{
		// OX ���� ������ ���ư���
		if (ch->m_pZone->IsOXQuizRoom() && ch->m_admin < 2)
		{
			if (!gserver->m_bEventOX)
			{
				CZone* pStartZone = gserver->FindZone(ZONE_START);
				if (pStartZone == NULL)
					return;

				GoZone(ch, ZONE_START,
					pStartZone->m_zonePos[0][0],													// ylayer
					GetRandom(pStartZone->m_zonePos[0][1], pStartZone->m_zonePos[0][3]) / 2.0f,		// x
					GetRandom(pStartZone->m_zonePos[0][2], pStartZone->m_zonePos[0][4]) / 2.0f);	// z
				return;
			}
		}

		// ����/���� ���� ��ҿ��� ȸ�� ����
		if (!DEAD(ch) && ch->m_pZone && ch->GetMapAttr() & MATT_WAR)
		{
			int joinflag = ch->GetJoinFlag(ch->m_pZone->m_index);
			if (joinflag != WCJF_NONE)
			{
				CWarCastle* castle = CWarCastle::GetCastleObject(ch->m_pZone->m_index);
				if (castle)
				{
					if (castle->GetState() != WCSF_NORMAL)
					{
						bool bIsIn = false;
						if (IS_ATTACK_TEAM(joinflag))
						{
							if (castle->IsInRegenPoint(ch, true))
								bIsIn = true;
						}
						else if (IS_DEFENSE_TEAM(joinflag))
						{
							if (castle->IsInRegenPoint(ch, false))
								bIsIn = true;
						}
						if (bIsIn)
						{
							ch->m_hp += ch->m_maxHP / 20;
							ch->m_mp += ch->m_maxMP / 20;
							if (ch->m_hp > ch->m_maxHP)
								ch->m_hp = ch->m_maxHP;
							if (ch->m_mp > ch->m_maxMP)
								ch->m_mp = ch->m_maxMP;
							ch->m_bChangeStatus = true;
							CNetMsg::SP rmsg(new CNetMsg);
							CharStatusMsg(rmsg, ch, 0);
							ch->m_pArea->SendToCell(rmsg, ch, true);
						}
					}
				}
			}
		}

		if (ch->m_bCreateMixItem)
		{
			CWarCastle* castle = CWarCastle::GetCastleObject(CWarCastle::GetCurSubServerCastleZoneIndex());
			if (!castle || !castle->IsRegenShop())
			{
				item_search_t vec;
				int sc = ch->m_inventory.searchFlagByItemProto(ITEM_FLAG_MIX, vec);
				if (sc > 0)
				{
					ch->m_inventory.deleteItem(vec, sc);
				}

				ch->m_bCreateMixItem = false;
			}
		}

		// �� ���� ����
		ch->UpdatePetValue();
		ch->UpdateAPetValue();

#ifdef EVENT_SEARCHFRIEND_TIME
		// �޸� �ɸ� �̺�Ʈ
		if (((ch->m_bEventSearchFriendSelect == true)
			&& (ch->m_nEventSearchFriendListCount >= 1)
			&& ch->m_pulseEventSearchFriend + PULSE_REAL_MIN * 5 >= gserver->m_pulse)
			&& (ch->m_nTimeEventSearchFriend <= 216000))
		{
			ch->m_nTimeEventSearchFriend++;

			if ((ch->m_nTimeEventSearchFriend % 3600) == 0)
			{
				//1�ð� �������� �޸��ɸ� ��ɽ� �˸�.
				CNetMsg::SP rmsg(new CNetMsg);
				ch->m_bGoodEventSearchFriendListImprove = true;
				EventHelperSearchFriendOneTimeCheckReqMsg(rmsg, ch->m_nTimeEventSearchFriend, ch->m_index);
				SEND_Q(rmsg, m_helper);
			}
		}
		//���󿩺� ���� �Ǵ� �κ�.
		if ((ch->m_bGoodEventSearchFriendListImprove == false) && ch->m_pulseEventSearchFriendList + PULSE_REAL_MIN * 5 <= gserver->m_pulse)
		{
			ch->m_bGoodEventSearchFriendListImprove = true;
		}
#endif // #ifdef EVENT_SEARCHFRIEND_TIME

		ch->m_inventory.checkItemTime();
		ch->m_wearInventory.checkItemTime();

		int title_index = ch->m_nCurrentTitle;
		CTitle* title = ch->m_titleList.Find(title_index);

		if (title != NULL)
		{
			if (!ch->m_titleList.HaveTitle(title_index) && title_index != 0)											// �� �κ��� �˼����� ������ ���� ó�� �κ����ν�
			{
				// �Ӹ��� �ް� �ִ� ȣĪ�� ����Ʈ�� �����ϰ� �ִ� ȣĪ�� �ƴҰ��
				CNetMsg::SP rmsg(new CNetMsg);																			//
				ch->m_nCurrentTitle = TITLE_SYSTEM_NO_TITLE;											// ȣĪ�� ���� ������ �κ��̴�.
				TitleSystemMsg(rmsg, MSG_EX_TITLE_SYSTEM_TITLE_CANCEL_SUCCESS, title_index, ch->m_index, title->m_custom_title_index);		// �̷��� ������ �־�� �ȵǴ� �κ��ε�..
				SEND_Q(rmsg, ch->m_desc);																// ���ܻ�Ȳ�� ����� ���� �߰��ϰ� �Ǿ���.
				ch->m_pArea->SendToCell(rmsg, ch);														//
				GAMELOG << init("TITLE SYSTEM ERROR", ch) << delim										//
					<< "This title is not exist in Title list" << delim								//
					<< "TITLE INDEX" << delim << title_index << end;										//
			}																							// �˼����� ���� �ּ� ��.
			if (ch->m_titleList.CheckTitleTime(title_index))													// ���� if���� �ð� ���� �Ǿ����� ó���ϴ� ��.
			{
				if (title_index == CUSTOM_TITLE_DUMMY_INDEX)
				{
					std::map<int, MAKE_TITLE*>::iterator it = ch->_map_title.find(ch->m_custom_title_index);
					if (it != ch->_map_title.end())
					{
						std::string query = boost::str(boost::format("DELETE FROM t_title_make where a_index = %d") % it->second->title_index);
						DBManager::instance()->pushQuery(0, query);

						{
							CNetMsg::SP rmsg(new CNetMsg);
							TitleDeleteInfoMsg(rmsg, it->second->title_index);
							SEND_Q(rmsg, ch->m_desc);
						}

						{
							CNetMsg::SP rmsg(new CNetMsg);
							TitleUserInfoMsg(rmsg, ch->m_index, -1, -1, -1, "");
							ch->m_pArea->SendToCell(rmsg, ch, true);
						}

						delete[] it->second->option_index;
						delete[] it->second->option_level;
						delete it->second;

						ch->_map_title.erase(ch->m_custom_title_index);
					}
				}

				ch->m_nCurrentTitle = TITLE_SYSTEM_NO_TITLE;
				ch->m_custom_title_index = -1;
				ch->CalcStatus(true);

				{
					CNetMsg::SP rmsg(new CNetMsg);
					SysMsg(rmsg, MSG_SYS_TITLE_EXPIRED);
					RefMsg(rmsg) << 1 << title_index;
					SEND_Q(rmsg, ch->m_desc);
				}

				{
					CNetMsg::SP rmsg(new CNetMsg);
					TitleSystemMsg(rmsg, MSG_EX_TITLE_SYSTEM_TITLE_EXPIRED, title_index, ch->m_index, title->m_custom_title_index);
					SEND_Q(rmsg, ch->m_desc);
					ch->m_pArea->SendToCell(rmsg, ch);
				}

				GAMELOG << init("TITLE EXPIRED TIME", ch) << delim
					<< "TITLE INDEX" << delim << title_index << end;

				{
					CNetMsg::SP rmsg(new CNetMsg);
					SubHelperTitleSystemTitleDelReq(rmsg, ch->m_index, title_index, title->m_custom_title_index);
					SEND_Q(rmsg, gserver->m_subHelper);
				}
			}
		}

#ifdef RESTRICT_PVP_SKILL
		if (ch->m_nRestrictPvPSkillDelaySec > 0)
			ch->m_nRestrictPvPSkillDelaySec--;
#endif // RESTRICT_PVP_SKILL

		// ����Ʈ �������� ������ ��ų
		CAssistData* outData;
		bool outHelp = false;
		int aura_type = 0;
		int level = 0;

		if (IS_IN_CELL(ch) && ch->CanSpell() && !ch->IsSetPlayerState(PLAYER_STATE_WARP))
		{
			// ������ ����ϰ� �ִ��� Ȯ��
			if (ch->m_assist.FindByType(MT_ASSIST, MST_ASSIST_AURA_DARKNESS))
				aura_type = MST_ASSIST_AURA_DARKNESS;
			else if (ch->m_assist.FindByType(MT_ASSIST, MST_ASSIST_AURA_WEAKNESS))
				aura_type = MST_ASSIST_AURA_WEAKNESS;
			else if (ch->m_assist.FindByType(MT_ASSIST, MST_ASSIST_AURA_ILLUSION))
				aura_type = MST_ASSIST_AURA_ILLUSION;

			// ������ ����ϸ� ������ �����´�.
			if (aura_type > 0)
				level = ch->m_assist.FindByType(MT_ASSIST, aura_type, &outHelp, &outData);

			if (level > 0 && outHelp == true && outData != NULL && outData->m_remain > 0 && ch->m_pArea && ch->m_pArea->m_cell)
			{
				int auraCount = 0;
				int cx, cz;

				ch->m_pArea->PointToCellNum(GET_X(ch), GET_Z(ch), &cx, &cz);

				// ĳ���Ͱ� �ִ� ���� npc���� �ڵ����� �������, pc���� �ڵ����� ������ �Ǵ�.
				CCharacter* pChar;
				CCharacter* pCharNext = ch->m_pArea->m_cell[cx][cz].m_listChar;
				while ((pChar = pCharNext))
				{
					pCharNext = pCharNext->m_pCellNext;

					// find char
					if (IS_PC(pChar))
					{
						//�����˻� pvp�� �Ǵ� ���ݸ�尡 �ƴϸ� return;
						if (ch->CanPvP(pChar, false) == false && outData->m_proto->m_index != 766)
							continue;

						if (outData->m_proto->m_index == 766)
						{
							if (pChar->m_index != ch->m_index && TO_PC(pChar)->IsParty() == false)
								continue;

							if (ch->IsParty() == true && ch->m_party->FindMember(pChar->m_index) == -1)
								continue;

							if (ch->m_index == pChar->m_index)
								continue;
						}
					}
					else if (IS_NPC(pChar))
					{
						if (IsApllyDebuffSkilltoNPC(ch, TO_NPC(pChar)) == false)
						{
							continue;
						}
					}
					ch->applyAuraSkill(pChar, auraCount, level, outData);

					// ������ ī��Ʈ�� �� 5ȸ�̸� loop�� ���� ������.
					if (auraCount >= 5)
						break;
				} // while
			} // if
		}// if

		// ĳ���� ���°� ��ũ�Ͻ� ��尡 �ƴϸ� ������ Ǯ���ش�.
		if (!ch->IsSetPlayerState(PLAYER_STATE_DARKNESS))
			ch->m_assist.CureAssist(MST_ASSIST_DARKNESS_MODE, 99);

		if (!ch->IsParty() && ch->m_pZone->IsPartyRaidZone())
		{
			// ��Ƽ�� �ƴϸ鼭 ��Ƽ ���̵� ���� �����ϸ� ��������.
			CNetMsg::SP rmsg(new CNetMsg);
			RaidInzoneQuitReq(rmsg, 1, 0);
			do_Raid(ch, rmsg);
		}
		else if (!ch->IsExped() && ch->m_pZone->IsExpedRaidZone())
		{
			// �����밡 �ƴϸ鼭 ������ ���̵� ���� �����ϸ� ��������.
			CNetMsg::SP rmsg(new CNetMsg);
			RaidInzoneQuitReq(rmsg, 1, 0);
			do_Raid(ch, rmsg);
		}
	}

	if (ch->GetMapAttr() & MATT_FREEPKZONE && ch->m_level > PKMODE_LIMIT_LEVEL)
	{
		if ((ch->GetPlayerState() & PLAYER_STATE_PKMODE) == false)
		{
			ch->ResetPlayerState(PLAYER_STATE_PKMODEDELAY | PLAYER_STATE_PKMODE);
			ch->SetPlayerState(PLAYER_STATE_PKMODE);
			//ch->CancelInvisible();

			//PK Und Igni Disable.
			ch->m_assist.CureBySkillIndex(IMMOTAL_BUF);
			ch->m_assist.CureBySkillIndex(CUBE_BUF);
			ch->m_assist.CureBySkillIndex(IGNI1_BUF);
			ch->m_assist.CureBySkillIndex(IGNI2_BUF);
			ch->m_assist.CureBySkillIndex(IGNI3_BUF);
			ch->m_assist.CureBySkillIndex(IGNI4_BUF);
			ch->m_assist.CureBySkillIndex(CAST_POTION);
			ch->m_assist.CureBySkillIndex(VELOCITY_BUF);

			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeAction(rmsg, ch, ACTION_GENERAL, AGT_PKMODE);
			ch->m_pArea->SendToCell(rmsg, ch, true);
		}
		// ������ �ٲ�� ������ ���� ������ ���� ������ �Ѵ� : ���� ���� �������� ���� �ʿ�
		if (ch->GetMapAttr() & MATT_WAR || ch->m_recentAtt & MATT_WAR)
			ch->CalcStatus(true);

		ch->m_recentAtt = ch->GetMapAttr();
		ch->m_bChangeStatus = true;
	}

	// ���������� �ƴ� ������ ������ PvP ��� ����
	if (ch->m_level <= PKMODE_LIMIT_LEVEL && ch->IsSetPlayerState(PLAYER_STATE_PKMODE | PLAYER_STATE_PKMODEDELAY))
	{
		bool bPvPOff = true;
		if (ch->m_pZone->m_index == CWarCastle::GetCurSubServerCastleZoneIndex() && ch->GetMapAttr() & MATT_WAR)
		{
			CWarCastle* castle = CWarCastle::GetCastleObject(ch->m_pZone->m_index);
			if (castle && castle->GetState() != WCSF_NORMAL)
				bPvPOff = false;
		}
#ifdef FREE_PK_SYSTEM
		if (gserver->m_bFreePk)
			bPvPOff = false;
#endif // FREE_PK_SYSTEM
		if (bPvPOff)
		{
			ch->ResetPlayerState(PLAYER_STATE_PKMODE | PLAYER_STATE_PKMODEDELAY);
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeAction(rmsg, ch, ACTION_GENERAL, AGT_PKMODE);
			ch->m_pArea->SendToCell(rmsg, ch, true);
		}
	}

	ch->m_autoSkillTime -= TIME_ONE_SECOND;

	if (ch->m_hp < ch->m_maxHP * 0.7f)
	{
		if (ch->m_activeSkillList.Find(152))
		{
			if (ch->m_assist.Find(194, 1)
				|| ch->m_assist.Find(194, 2)
				|| ch->m_assist.Find(194, 3)
				|| ch->m_assist.Find(194, 4)
				|| ch->m_assist.Find(194, 5))
			{
			}
			else
			{
				if (ch->m_autoSkillTime < 0
					&& ch->IsSetPlayerState(PLAYER_CRISTAL_RESPOND) == false)
				{
					ch->m_autoSkillTime = PULSE_AUTO_SKILL_DECREASE;
					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::makeSkillAutoUseMSg(rmsg, 152);
					SEND_Q(rmsg, ch->m_desc);
				}
			}
		}
	}
	else
	{
		if (ch->m_autoSkillTime < -PULSE_AUTO_SKILL_DECREASE)
			ch->m_autoSkillTime = 0;
	}

	CElemental* pElemental = NULL;
	CElemental* pElementalNext = ch->m_elementalList;
	while ((pElemental = pElementalNext))
	{
		// yhj ����.. ������Ż NULL üũ�� ���ؼ� ������ ������.. �� NULLüũ ������ �Ǹ� �ٸ� ����� �������.
		if (!pElemental)
			break;
		pElementalNext = pElemental->m_nextElemental;
		if (pElemental->DecreaseRemainTime())
			ch->UnsummonElemental(pElemental);
		else
			pElemental->m_assist.DecreaseTime();
	}

	int hp = ch->m_hp;
	int maxhp = ch->m_maxHP;

	int mp = ch->m_mp;
	int maxmp = ch->m_maxMP;

	int posioncount = 0;

	bool bHpRemain = false;	// ��Ÿ��
	bool bMpRemain = false;	// ��Ÿ��

	if (hp < maxhp * 0.5 && hp > 0)
	{
		// ü���� ���� ����
		CAssistData* outData = NULL;
		bool outHelp = false;
		ch->m_assist.FindByType(MT_ASSIST, MST_ASSIST_HP, &outHelp, &outData);

		if (outHelp == true
			&& outData != NULL
			&& outData->m_remain > 0)
		{
			// ü�� ȸ�� ������ �Ծ��� ���
			bHpRemain = true;
		}

		if (bHpRemain == false)
		{
			for (int k = WEARING_ACCESSORY1; k <= WEARING_ACCESSORY3; k++)
			{
				if (ch->m_wearInventory.wearItemInfo[k] == NULL)
					continue;

				if (ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 2610
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4940
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4941
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4942
					)
				{
					item_search_t vec;
					ch->m_inventory.searchAllItem(vec);
					item_search_t::iterator it = vec.begin();
					item_search_t::iterator endit = vec.end();
					for (; it != endit; ++it)
					{
						CItem* item = (*it).pItem;
						if (item->m_itemProto->getItemTypeIdx() != ITYPE_POTION || item->m_itemProto->getItemSubTypeIdx() != IPOTION_HP)
						{
							continue;
						}

						CNetMsg::SP rmsg(new CNetMsg);
						ResponseClient::ItemUseMsg(rmsg, item->tab(), item->getInvenIndex(), item->getVIndex(), item->getDBIndex());
						do_Item(ch, rmsg);
						posioncount++;
						goto USE_HP_POTION;
					}
				}
			} // end for
			// newslot - alanssoares
			if (ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4] != NULL && (ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
				|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
				|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
				|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 2610
				|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 4940
				|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 4941
				|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 4942
				))
			{
				item_search_t vec;
				ch->m_inventory.searchAllItem(vec);
				item_search_t::iterator it = vec.begin();
				item_search_t::iterator endit = vec.end();
				for (; it != endit; ++it)
				{
					CItem* item = (*it).pItem;
					if (!item || item->m_itemProto->getItemTypeIdx() != ITYPE_POTION || item->m_itemProto->getItemSubTypeIdx() != IPOTION_HP)
					{
						continue;
					}

					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::ItemUseMsg(rmsg, item->tab(), item->getInvenIndex(), item->getVIndex(), item->getDBIndex());
					do_Item(ch, rmsg);
					posioncount++;
					goto USE_HP_POTION;
				}
			}

			// newslot - alanssoares
			for (int k = WEARING_SPECIAL_ACCESSORY1; k <= WEARING_SPECIAL_ACCESSORY5; k++)
			{
				if (ch->m_wearInventory.wearItemInfo[k] == NULL)
					continue;

				if (ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 2610
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4940
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4941
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4942
					)
				{
					item_search_t vec;
					ch->m_inventory.searchAllItem(vec);
					item_search_t::iterator it = vec.begin();
					item_search_t::iterator endit = vec.end();
					for (; it != endit; ++it)
					{
						CItem* item = (*it).pItem;
						if (item->m_itemProto->getItemTypeIdx() != ITYPE_POTION || item->m_itemProto->getItemSubTypeIdx() != IPOTION_HP)
						{
							continue;
						}

						CNetMsg::SP rmsg(new CNetMsg);
						ResponseClient::ItemUseMsg(rmsg, item->tab(), item->getInvenIndex(), item->getVIndex(), item->getDBIndex());
						do_Item(ch, rmsg);
						posioncount++;
						goto USE_HP_POTION;
					}
				}
			} // end for
		}
	}

USE_HP_POTION:
	if (mp < maxmp * 0.5)
	{
		// ������ ���� ����
		CAssistData* outData = NULL;
		bool outHelp = false;
		ch->m_assist.FindByType(MT_ASSIST, MST_ASSIST_MP, &outHelp, &outData);

		if (outHelp == true
			&& outData != NULL
			&& outData->m_remain > 0)
		{
			// ���� ȸ�� ������ �Ծ��� ���
			bMpRemain = true;
		}

		if (bMpRemain == false)
		{
			for (int k = WEARING_ACCESSORY1; k <= WEARING_ACCESSORY3; k++)
			{
				if (ch->m_wearInventory.wearItemInfo[k])
				{
					if (ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
						|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
						|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
						|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 2610
						|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4940
						|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4941
						|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4942)
					{
						item_search_t vec;
						ch->m_inventory.searchAllItem(vec);
						item_search_t::iterator it = vec.begin();
						item_search_t::iterator endit = vec.end();
						for (; it != endit; ++it)
						{
							CItem* item = (*it).pItem;
							if (item->m_itemProto->getItemTypeIdx() != ITYPE_POTION || item->m_itemProto->getItemSubTypeIdx() != IPOTION_MP)
							{
								continue;
							}

							CNetMsg::SP rmsg(new CNetMsg);
							ResponseClient::ItemUseMsg(rmsg, item->tab(), item->getInvenIndex(), item->getVIndex(), item->getDBIndex());
							do_Item(ch, rmsg);
							posioncount++;

							goto USE_MP_POTION;
						}
					}
				}
			} // for( i ; i <= WEARING_ACCESSORY3; i++ )

			// newslot - alanssoares
			if (ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4])
			{
				if (ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 2610
					|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 4940
					|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 4941
					|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 4942)
				{
					item_search_t vec;
					ch->m_inventory.searchAllItem(vec);
					item_search_t::iterator it = vec.begin();
					item_search_t::iterator endit = vec.end();
					for (; it != endit; ++it)
					{
						CItem* item = (*it).pItem;
						if (item->m_itemProto->getItemTypeIdx() != ITYPE_POTION || item->m_itemProto->getItemSubTypeIdx() != IPOTION_MP)
						{
							continue;
						}

						CNetMsg::SP rmsg(new CNetMsg);
						ResponseClient::ItemUseMsg(rmsg, item->tab(), item->getInvenIndex(), item->getVIndex(), item->getDBIndex());
						do_Item(ch, rmsg);
						posioncount++;

						goto USE_MP_POTION;
					}
				}
			}

			// newslot - alanssoares
			for (int k = WEARING_SPECIAL_ACCESSORY1; k <= WEARING_SPECIAL_ACCESSORY5; k++)
			{
				if (ch->m_wearInventory.wearItemInfo[k])
				{
					if (ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
						|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
						|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
						|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 2610
						|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4940
						|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4941
						|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4942)
					{
						item_search_t vec;
						ch->m_inventory.searchAllItem(vec);
						item_search_t::iterator it = vec.begin();
						item_search_t::iterator endit = vec.end();
						for (; it != endit; ++it)
						{
							CItem* item = (*it).pItem;
							if (item->m_itemProto->getItemTypeIdx() != ITYPE_POTION || item->m_itemProto->getItemSubTypeIdx() != IPOTION_MP)
							{
								continue;
							}

							CNetMsg::SP rmsg(new CNetMsg);
							ResponseClient::ItemUseMsg(rmsg, item->tab(), item->getInvenIndex(), item->getVIndex(), item->getDBIndex());
							do_Item(ch, rmsg);
							posioncount++;

							goto USE_MP_POTION;
						}
					}
				}
			} // for( i ; i <= WEARING_SPECIAL_ACCESSORY5; i++ )
		}
	}

USE_MP_POTION:
	if (posioncount == 0
		&&
		((hp < maxhp * 0.5 && hp > 0) || (mp < maxmp * 0.5))
		&& (bHpRemain == false && bMpRemain == false)
		)

	{
		// ü���̳� ������ 50% ���Ͽ��� ����� ������ ���� ���
		bool bWare = true;
		for (int k = WEARING_ACCESSORY1; k <= WEARING_ACCESSORY3; k++)
		{
			if (ch->m_wearInventory.wearItemInfo[k])
			{
				if (ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 2610
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4940
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4941
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4942)
				{
					char wear_pos = ch->m_wearInventory.wearItemInfo[k]->getWearPos();

					ch->m_assist.CureByItemIndex(ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex());

					ch->m_wearInventory.DelNormalItem(k);

					bWare = false;
				}
			}
		}

		// newslot - alanssoares
		if (ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4])
		{
			if (ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
				|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
				|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
				|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 2610
				|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 4940
				|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 4941
				|| ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 4942)
			{
				char wear_pos = ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->getWearPos();

				ch->m_assist.CureByItemIndex(ch->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex());

				ch->m_wearInventory.DelNormalItem(WEARING_ACCESSORY4);

				bWare = false;
			}
		}

		// newslot - alanssoares
		for (int k = WEARING_SPECIAL_ACCESSORY1; k <= WEARING_SPECIAL_ACCESSORY5; k++)
		{
			if (ch->m_wearInventory.wearItemInfo[k])
			{
				if (ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 2610
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4940
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4941
					|| ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4942)
				{
					char wear_pos = ch->m_wearInventory.wearItemInfo[k]->getWearPos();

					ch->m_assist.CureByItemIndex(ch->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex());

					ch->m_wearInventory.DelNormalItem(k);

					bWare = false;
				}
			}
		}

		if (bWare == false)
		{
			// �ڵ� ���� ��� �������� ������ ���
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_NO_AUTO_ITEM);
			SEND_Q(rmsg, ch->m_desc);
		}
	}

	// ��Ʈ���̾Ƴ� ��
	ch->m_SkillTime_511 += TIME_ONE_SECOND;
	if (ch->m_SkillTime_511 >= 2 * TIME_ONE_MIN)
	{
		ch->m_SkillTime_511 = 0;
		if (ch->m_pZone->m_index == ZONE_STREIANA)
		{
			if (ch->m_job2 || ch->m_job)  //pwesty fix for bypassing this for single job
			{
				CItemProto* pItem = gserver->m_itemProtoList.FindIndex(2859);
				if (pItem && ch->m_assist.FindBySkillIndex(pItem->getItemNum0()))
					return;

				CSkill* pSkill = gserver->m_skillProtoList.Create(511, 1);
				if (pSkill && ch->CanApplySkill(pSkill->m_proto, pSkill->m_proto->Level(pSkill->m_level)))
				{
					bool bApply = false;
					ApplySkill(ch, ch, pSkill, -1, bApply);
				}
			}
		}
	}
#ifdef DARKTHEOSDEBUFF
	ch->m_SkillTime_theos += TIME_ONE_SECOND;
	if (ch->m_SkillTime_theos >= 2 * TIME_ONE_MIN)
	{
		ch->m_SkillTime_theos = 0;
		if (ch->m_pZone->m_index == ZONE_DARK_TEOS)
		{
			if (ch->m_job2 || ch->m_job)  //pwesty fix for bypassing this for single job
			{
				CItemProto* pItem = gserver->m_itemProtoList.FindIndex(20651);
				if (pItem && ch->m_assist.FindBySkillIndex(pItem->getItemNum0()))
					return;

				CSkill* pSkill = gserver->m_skillProtoList.Create(2054, 1);
				if (pSkill && ch->CanApplySkill(pSkill->m_proto, pSkill->m_proto->Level(pSkill->m_level)))
				{
					bool bApply = false;
					ApplySkill(ch, ch, pSkill, -1, bApply);
				}
			}
		}
	}
#endif
	// ������� �ش�.
	if (ch && ch->m_pZone->IsWarGroundZone())
	{
		int skilllevel = 1;
		CWaitPlayer* p = NULL;
		p = gserver->m_RoyalRumble.m_WaitPlayerList.GetNode(ch->m_index);
		if (p && p->GetIsEntered()) // ĳ���Ͱ� �ξⷳ���� ���� ���� ���¿��� �ǽ����� ����.
		{
			skilllevel += p->GetLevelType();
			if (ch->IsInPeaceZone(true))
			{
				if (!ch->m_assist.FindBySkillIndex(ROYAL_RUMBLE_DEBUFF_SKILL))
				{
					CSkill* pSkill = NULL;
					pSkill = gserver->m_skillProtoList.Create(ROYAL_RUMBLE_DEBUFF_SKILL, skilllevel);
					bool bApply;
					ApplySkill(ch, ch, pSkill, -1, bApply);
					GAMELOG << init("ROYAL RUMBLE", ch) << "DEBUFF SKILL CHARACTER IN THE PEACE AREA" << end;
					if (!bApply && pSkill)
					{
						delete pSkill;
						pSkill = NULL;
					}
				}
			}
		}
	}
#ifdef XTRAP

	ch->m_xtrapCheckPulse -= TIME_ONE_SECOND;

	if (ch->m_xtrapCheckPulse < 0/*10*PULSE_REAL_SEC*/)
	{
		ch->m_xtrapCheckPulse = 20 * TIME_ONE_SECOND;

		char msgbuffer[128];
		int nRet = XTrap_CS_Step1(ch->m_xtrapSessionBuf, msgbuffer);
#ifdef XTRAP_DUMP
		char filename[128];
		sprintf(filename, "%d.xtrap.log", ch->m_index);
		HexaDump4XTrap_Std(filename, msgbuffer, 128, "Step1_After");
#endif //XTRAP_DUMP

		{
			// Ŭ���̾�Ʈ�� XTRAP Ȯ�� ��û
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_XTRAP;
			rmsg->Write(msgbuffer, 128);
			SEND_Q(rmsg, ch->m_desc);
		}

		if (nRet != 0)
		{
			GAMELOG << init("SYSTEM ERROR : XTRAP", ch) << " error code " << nRet << end;
			ch->m_desc->Close("SYSTEM ERROR : XTRAP");
		}
	}
#endif // XTRAP

	//gps
	ch->m_gpsManager.sendGpsTargetMoveInfo();
	ch->m_arti_gpsManager.sendGpsTargetMoveInfo();

	//��ġ������
	if (ch->IsSearchLife() == true)
	{
		if (ch->m_targetPC != NULL && ch->m_targetPC->m_type != MSG_CHAR_UNKNOWN)
		{
			CPC* targetPC = ch->m_targetPC;
			CNetMsg::SP rmsg(new CNetMsg);
			UpdateClient::CharHpInfoMsg(rmsg, targetPC->m_index, targetPC->m_maxHP, targetPC->m_hp);
			SEND_Q(rmsg, ch->m_desc);
		}
	}

#ifdef PREMIUM_CHAR
	if (ch->m_premiumChar.isActive())
	{
		ch->m_premiumChar.checkExpireTime(gserver->m_nowseconds);
	}
#endif
}

CZone* CServer::FindZone(int zone)
{
	map_zone_t::iterator it = m_zones_map.find(zone);
	return (it != m_zones_map.end()) ? it->second : NULL;
}

bool CServer::DropProbLoad()
{
	CDBCmd cmd;
	cmd.Init(&m_dbdata);

	cmd.SetQuery("SELECT * FROM t_drop_prob");

	if (!cmd.Open() || !cmd.MoveFirst())
		return false;

	if (!cmd.GetRec("a_item_prob", m_itemDropProb) || !cmd.GetRec("a_money_prob", m_moneyDropProb))
		return false;

	// �ִ� 300 �ּ� 50 ����
	if (m_itemDropProb > 300)
		m_itemDropProb = 300;
	else if (m_itemDropProb < 50)
		m_itemDropProb = 50;

	return true;
}

//0502 kwon
void CServer::MoonStoneEndProcess(CPC* ch)
{
}

// ���� -> ������
void CServer::SaveTax()
{
	CDBCmd cmd;
	cmd.Init(&m_dbcastle);
	std::string udpate_castle_query = "";
	LONGLONG taxProduce = (m_taxProduceCastle / 3) + (m_taxProduceTrivia / 3);
	udpate_castle_query += boost::str(boost::format("UPDATE t_castle SET a_tax_item = a_tax_item + %1%, a_tax_produce = a_tax_produce + %2% WHERE a_zone_index=7") % (m_taxItem / 3) % taxProduce);

#ifdef LC_TLD // �±� ���� 1/3�� �Ѵ�
	m_taxItem /= 3;
	m_taxProduceCastle /= 3;
#endif

	cmd.SetQuery(udpate_castle_query);
	if (!cmd.Update())
	{
		GAMELOG << init("MERAC TAX SAVE FAIL")
			<< "ITEM" << delim
			<< (m_taxItem / 3) << delim
			<< "PRODUCE" << delim
			<< (m_taxProduceCastle / 3) << delim
			<< (m_taxProduceTrivia / 3)
			<< end;
	}
	else
	{
		GAMELOG << init("MERAC TAX SAVE SUCCESS")
			<< "ITEM" << delim
			<< (m_taxItem / 3) << delim
			<< "PRODUCE" << delim
			<< (m_taxProduceCastle / 3) << delim
			<< (m_taxProduceTrivia / 3)
			<< end;
		ResetTax();
		ResetTaxTrivia();
	}

	CDBCmd cmd2;
	cmd2.Init(&m_dbcastle);
	std::string udpate_castle_query1 = "";

	taxProduce = (m_taxProduceCastleDratan / 3) + (m_taxProduceAkan / 3);
	udpate_castle_query1 += boost::str(boost::format(
		"UPDATE t_castle SET a_tax_item = a_tax_item + %1%, a_tax_produce = a_tax_produce + %2% WHERE a_zone_index=4") % (m_taxItemDratan / 3) % taxProduce);

	cmd2.SetQuery(udpate_castle_query1);
	if (!cmd2.Update())
	{
		GAMELOG << init("DRATAN TAX SAVE FAIL")
			<< "ITEM" << delim
			<< (m_taxItemDratan / 3) << delim
			<< "PRODUCE" << delim
			<< (m_taxProduceCastleDratan / 3) << delim
			<< (m_taxProduceAkan / 3)
			<< end;
	}
	else
	{
		GAMELOG << init("DRATAN TAX SAVE SUCCESS")
			<< "ITEM" << delim
			<< (m_taxItemDratan / 3) << delim
			<< "PRODUCE" << delim
			<< (m_taxProduceCastleDratan / 3) << delim
			<< (m_taxProduceAkan / 3)
			<< end;
		ResetTaxDratan();
		ResetTaxAkan();
	}
}

// ���� -> ���
void CServer::DivideTax()
{
	// ������
	CDBCmd cmd;
	cmd.Init(&m_dbcastle);

	int zoneindex = CWarCastle::GetCurSubServerCastleZoneIndex();
	if (zoneindex < 0)
		return;

	std::string select_castle_query = boost::str(boost::format(
		"SELECT a_tax_guild_index, a_tax_item, a_tax_produce, a_tax_wday FROM t_castle WHERE a_zone_index = %d") % ZONE_MERAC);
	cmd.SetQuery(select_castle_query);

	if (cmd.Open() && cmd.MoveFirst())
	{
		int guildindex;
		LONGLONG taxItem;
		LONGLONG taxProduce;
		int wday;
		cmd.GetRec("a_tax_guild_index", guildindex);
		cmd.GetRec("a_tax_item", taxItem);
		cmd.GetRec("a_tax_produce", taxProduce);
		cmd.GetRec("a_tax_wday", wday);

		// �ֱ� ���� ������ ������ �ƴ� ��쿡��
		struct tm tmCur = NOW();
		if (wday != tmCur.tm_wday)
		{
			// ���ۿ��� �ּ� �ݾ��� �����Ѵ�
			CNetMsg::SP rmsg(new CNetMsg);
			HelperGuildStashSaveTaxReqMsg(rmsg, guildindex, ZONE_MERAC, taxItem, taxProduce);
			SEND_Q(rmsg, m_helper);
		}
	}
	else
	{
		GAMELOG << init("MERAC TAX DIVIDE FAIL")
			<< end;
	}

	CDBCmd cmd2;
	cmd2.Init(&m_dbcastle);
	std::string select_castle_query1 = boost::str(boost::format(
		"SELECT a_tax_guild_index, a_tax_item, a_tax_produce, a_tax_wday FROM t_castle WHERE a_zone_index = %d") % ZONE_DRATAN);
	cmd2.SetQuery(select_castle_query1);

	if (cmd2.Open() && cmd2.MoveFirst())
	{
		int guildindex;
		LONGLONG taxItem;
		LONGLONG taxProduce;
		int wday;
		cmd2.GetRec("a_tax_guild_index", guildindex);
		cmd2.GetRec("a_tax_item", taxItem);
		cmd2.GetRec("a_tax_produce", taxProduce);
		cmd2.GetRec("a_tax_wday", wday);

		// �ֱ� ���� ������ ������ �ƴ� ��쿡��
		struct tm tmCur = NOW();
		if (wday != tmCur.tm_wday)
		{
			// ���ۿ��� �ּ� �ݾ��� �����Ѵ�
			CNetMsg::SP rmsg(new CNetMsg);
			HelperGuildStashSaveTaxReqMsg(rmsg, guildindex, ZONE_DRATAN, taxItem, taxProduce);
			SEND_Q(rmsg, m_helper);
		}
	}
	else
	{
		GAMELOG << init("DRATAN TAX DIVIDE FAIL")
			<< end;
	}
}

void CServer::ChangeTaxGuild()
{
	CDBCmd cmd;
	cmd.Init(&m_dbcastle);

	std::string update_castle_query = boost::str(boost::format(
		"UPDATE t_castle SET a_tax_item = 0, a_tax_produce = 0, a_tax_guild_index = a_owner_guild_index WHERE a_zone_index = %d AND a_tax_guild_index != a_owner_guild_index")
		% CWarCastle::GetCurSubServerCastleZoneIndex());

	cmd.SetQuery(update_castle_query);
	if (!cmd.Update())
	{
		GAMELOG << init("MARAC TAX GUILD RESET FAIL")
			<< "ZONE" << delim
			<< CWarCastle::GetCurSubServerCastleZoneIndex()
			<< end;
	}
	else
	{
		GAMELOG << init(" MARAC TAX GUILD RESET SUCCESS")
			<< "ZONE" << delim
			<< CWarCastle::GetCurSubServerCastleZoneIndex()
			<< end;
	}

	CDBCmd cmd2;
	cmd2.Init(&m_dbcastle);
	std::string update_castle_query1 = boost::str(boost::format(
		"UPDATE t_castle SET a_tax_item = 0, a_tax_produce = 0, a_tax_guild_index = a_owner_guild_index WHERE a_zone_index = %d AND a_tax_guild_index != a_owner_guild_index")
		% ZONE_DRATAN);

	cmd2.SetQuery(update_castle_query1);
	if (!cmd2.Update())
	{
		GAMELOG << init("DRATAN TAX GUILD RESET FAIL")
			<< "ZONE" << delim
			<< CWarCastle::GetCurSubServerCastleZoneIndex()
			<< end;
	}
	else
	{
		GAMELOG << init("DRATAN TAX GUILD RESET SUCCESS")
			<< "ZONE" << delim
			<< CWarCastle::GetCurSubServerCastleZoneIndex()
			<< end;
	}
}

CZone* CServer::FindNearestZone(int zone, float x, float z, int* nearZone, int* nearZonePos, int syndicateType)
{
	// x, z�� �����̸� x, z �����ؾ� ��
	// �⺻ ��ġ
	*nearZone = ZONE_START;
	*nearZonePos = 0;

	switch (zone)
	{
	case ZONE_PK_TOURNAMENT:
		*nearZone = ZONE_PK_TOURNAMENT;
		*nearZonePos = 0;
		break;

	case ZONE_STREIANA:
	case ZONE_SPRIT_CAVE:
	case ZONE_QUANIAN_CAVE:
	case ZONE_GOLEM_CAVE:
	case ZONE_TRIVIA_CANYON:
		*nearZone = ZONE_STREIANA;
		*nearZonePos = 0;
		break;

	case ZONE_SINGLE_DUNGEON_TUTORIAL:	// ��� 2������ ����
		*nearZone = ZONE_START;
		*nearZonePos = 0;
		break;

	case ZONE_DUNGEON4:
	case ZONE_DUNGEON2:
	case ZONE_DRATAN:
	case ZONE_DRATAN_CASTLE_DUNGEON:
		*nearZone = ZONE_DRATAN;
		*nearZonePos = 0;
		break;

	case ZONE_MERAC:
	case ZONE_DUNGEON3:
	case ZONE_MISTY_CANYON:
	case ZONE_EXTREME_CUBE:
		*nearZone = ZONE_MERAC;
		*nearZonePos = 0;
		break;

	case ZONE_EGEHA:
	case ZONE_EGEHA_DUNGEON_1:
	case ZONE_EGEHA_DUNGEON_8:
	case ZONE_EGEHA_DUNGEON_9:
	case ZONE_EGEHA_DUNGEON_10:
	case ZONE_FLORAIM_CAVE:
		*nearZone = ZONE_EGEHA;
		*nearZonePos = 0;
		break;

	case ZONE_COMBO_DUNGEON:
		*nearZone = ZONE_COMBO_DUNGEON;
		*nearZonePos = 0;
		break;

	case ZONE_MONDSHINE:
		*nearZone = ZONE_MONDSHINE;
		*nearZonePos = 0;
		break;

	case ZONE_TARIAN:
		*nearZone = ZONE_TARIAN;
		*nearZonePos = 0;
		break;

	case ZONE_BLOODYMIR:
		*nearZone = ZONE_BLOODYMIR;
		*nearZonePos = 0;
		break;

	case ZONE_RVR:
		*nearZone = ZONE_RVR;
		*nearZonePos = syndicateType;
		break;

	case ZONE_MISTY_CANYON_EXTREME:
		*nearZone = ZONE_MISTY_CANYON_EXTREME;
		*nearZonePos = 0;
		break;

	case ZONE_MAGMA_CANYON:
		*nearZone = ZONE_MAGMA_CANYON;
		*nearZonePos = 0;
		break;

	case ZONE_START:	// ��� ����
	case ZONE_DUNGEON1:
	case ZONE_SINGLE_DUNGEON1:
	case ZONE_SINGLE_DUNGEON2:
	case ZONE_GUILDROOM:
	case ZONE_SINGLE_DUNGEON3:
	case ZONE_SINGLE_DUNGEON4:
	case ZONE_OXQUIZROOM:
	case ZONE_EBONY_MINE:
	default:
		*nearZone = ZONE_START;
		*nearZonePos = 0;
		break;
	}

	return FindZone(*nearZone);
}

CParty* CServer::FindPartyByBossIndex(int nBossIndex)
{
	map_listparty_t::iterator it = m_listParty.find(nBossIndex);
	return (it != m_listParty.end()) ? it->second : NULL;
}

CParty* CServer::FindPartyByMemberIndex(int nMemberIndex, bool bIncludeRequest)
{
	map_listparty_t::iterator it = m_listParty.begin();
	map_listparty_t::iterator endit = m_listParty.end();
	for (; it != endit; ++it)
	{
		CParty* pParty = it->second;
		if (pParty->FindMember(nMemberIndex) != -1)
			return pParty;
		if (bIncludeRequest && pParty->GetRequestIndex() == nMemberIndex)
			return pParty;
	}

	return NULL;
}

CExpedition* CServer::FindExpedByBossIndex(int nBossIndex)
{
	map_listexped_t::iterator it = m_listExped.find(nBossIndex);
	return (it != m_listExped.end()) ? it->second : NULL;
}

CExpedition* CServer::FindExpedByMemberIndex(int nMemberIndex, bool bIncludeRequest)
{
	map_listexped_t::iterator it = m_listExped.begin();
	map_listexped_t::iterator endit = m_listExped.end();
	for (; it != endit; ++it)
	{
		CExpedition* pExped = it->second;

		if (pExped->FindMemberListIndex(nMemberIndex) != -1)
			return pExped;
		if (bIncludeRequest && pExped->GetRequestIndex() == nMemberIndex)
			return pExped;
	}

	return NULL;
}

CPartyMatchMember* CServer::FindPartyMatchMemberByCharIndex(int nCharIndex)
{
	map_listPartyMatchMember_t::iterator it = m_listPartyMatchMember.find(nCharIndex);
	return (it != m_listPartyMatchMember.end()) ? it->second : NULL;
}

CPartyMatchParty* CServer::FindPartyMatchPartyByBossIndex(int nBossIndex)
{
	map_listPartyMatchParty_t::iterator it = m_listPartyMatchParty.find(nBossIndex);
	return (it != m_listPartyMatchParty.end()) ? it->second : NULL;
}

bool CServer::LoadOXQuiz()
{
	m_listOXQuiz.clear();

	if (!LoadOXReward())
		return false;

	CLCString sql(1024);
	sql.Format("SELECT a_index, a_question, a_answer FROM t_oxquiz WHERE a_country=%d ORDER BY a_index", m_national);
	CDBCmd cmd;
	cmd.Init(&m_dbdata);
	cmd.SetQuery(sql);
	if (!cmd.Open())
		return false;

	while (cmd.MoveNext())
	{
		int nIndex;
		CLCString strQuestion(256);
		CLCString strAnswer(2);

		if (
			!cmd.GetRec("a_index", nIndex)
			|| !cmd.GetRec("a_question", strQuestion)
			|| !cmd.GetRec("a_answer", strAnswer)
			)
			return false;

		COXQuizData* pQuiz = new COXQuizData(nIndex, strQuestion, (strcmp(strAnswer, "O") == 0) ? true : false);
		m_listOXQuiz.insert(map_listOXQuiz_t::value_type(pQuiz->GetQuizIndex(), pQuiz));
	}

	return true;
}

int CServer::addChatGroup(int& makeCharIndex, int& chatIndex, CLCString charName)
{
	CChatGroup* chatGroup = this->FindChatGroup(makeCharIndex, chatIndex);
	if (chatGroup)
	{
		// ������ ������� ����
		std::set<CLCString>::iterator it = chatGroup->m_charNameList.find(charName);
		if (it == chatGroup->m_charNameList.end())
		{
			if (chatGroup->CheckSameName(charName) == false)
			{
				// �ߺ� üũ
				return 0;
			}
			chatGroup->m_charNameList.insert(charName);
			if (chatGroup->m_charNameList.size() == 1)
			{
				// ó�� ������
				return -1;
			}
			return 1;
		}
	}
	else
	{
		chatIndex = this->GetMaxChatIndexPerPC(makeCharIndex) + 1;
		chatGroup = new CChatGroup(makeCharIndex, chatIndex);
		chatGroup->m_charNameList.insert(charName);
		LONGLONG key = MAKE_LONGLONG_KEY(makeCharIndex, chatIndex);
		this->m_chatList.insert(map_chatList_t::value_type(key, chatGroup));

		return 0;
	}

	return -1;
}

void CServer::discCharChatGroup(CLCString charName)
{
	map_chatList_t::iterator it = m_chatList.begin();
	map_chatList_t::iterator endit = m_chatList.end();
	for (; it != endit; ++it)
	{
		CChatGroup* chatGroup = it->second;

		CNetMsg::SP rmsg(new CNetMsg);
		MsgrMessengerChatMsg(rmsg, MSG_MSGR_MESSENGER_DEL, chatGroup->GetMakeCharIndex(), chatGroup->GetChatIndex(), 0, charName);
		SEND_Q(rmsg, gserver->m_messenger);
	}
}

void CServer::delChatGroup(int makeCharIndex, int chatIndex, CLCString charName)
{
	CChatGroup* chatGroup = this->FindChatGroup(makeCharIndex, chatIndex);
	if (chatGroup == NULL)
		return;

	std::set<CLCString>::iterator sit = chatGroup->m_charNameList.begin();
	std::set<CLCString>::iterator eit = chatGroup->m_charNameList.end();

	for (; sit != eit; ++sit)
	{
		if (strcmp((*sit), charName) == 0)
		{
			chatGroup->m_charNameList.erase(sit);
			if (chatGroup->m_charNameList.empty())
			{
				//����� ����
				LONGLONG key = MAKE_LONGLONG_KEY(makeCharIndex, chatIndex);
				m_chatList.erase(key);
				delete chatGroup;
			}
			break;
		}
	}
}

void CServer::SendChatGroup(MSG_EX_MESSENGER_TYPE subtype, int makeCharIndex, int chatIndex, int chatColor, CLCString charName, CLCString chat)
{
	CChatGroup* chatGroup = this->FindChatGroup(makeCharIndex, chatIndex);
	if (chatGroup)
	{
		chatGroup->SendGroup(subtype, chatColor, charName, chat);
	}
}

CChatGroup* CServer::FindChatGroup(int makeCharIndex, int chatIndex)
{
	LONGLONG key = MAKE_LONGLONG_KEY(makeCharIndex, chatIndex);
	map_chatList_t::iterator it = m_chatList.find(key);
	return (it != m_chatList.end()) ? it->second : NULL;
}

int CServer::GetMaxChatIndexPerPC(int makeCharIndex)
{
	int max = 0;
	map_chatList_t::iterator it = m_chatList.begin();
	map_chatList_t::iterator endit = m_chatList.end();
	for (; it != endit; ++it)
	{
		CChatGroup* chatGroup = it->second;

		if (chatGroup->GetMakeCharIndex() == makeCharIndex && chatGroup->GetChatIndex() > max)
			max = chatGroup->GetChatIndex();
	}

	return max;
}

bool CChatGroup::CheckSameName(CLCString charName)
{
	std::set<CLCString>::iterator it = m_charNameList.find(charName);
	return (it == m_charNameList.end()) ? true : false;
}

void CChatGroup::SendGroup(MSG_EX_MESSENGER_TYPE subtype, int chatColor, CLCString charName, CLCString chat)
{
	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_EXTEND);
	RefMsg(rmsg) << MSG_EX_MESSENGER
		<< (unsigned char)subtype
		<< this->GetMakeCharIndex()
		<< this->GetChatIndex();

	if (subtype == MSG_EX_MESSENGER_CHAT)
		RefMsg(rmsg) << chatColor;
	RefMsg(rmsg) << charName
		<< chat;

	CNetMsg::SP lmsg(new CNetMsg);
	if (subtype == MSG_EX_MESSENGER_INVITE)
	{
		lmsg->Init(MSG_EXTEND);
		RefMsg(lmsg) << MSG_EX_MESSENGER
			<< (unsigned char)MSG_EX_MESSENGER_CHARLIST
			<< this->GetMakeCharIndex()
			<< this->GetChatIndex()
			<< (int)this->m_charNameList.size();
	}

	CLCString SendcharName(MAX_CHAR_NAME_LENGTH + 1);
	std::set<CLCString>::iterator it = m_charNameList.begin();
	std::set<CLCString>::iterator endit = m_charNameList.end();
	for (; it != endit; ++it)
	{
		SendcharName = *(it);

		if (strcmp(SendcharName, "") != 0)
		{
			CPC* pc = PCManager::instance()->getPlayerByName(SendcharName, true);
			if (pc)
			{
				if (subtype == MSG_EX_MESSENGER_INVITE)
					RefMsg(lmsg) << SendcharName;

				SEND_Q(rmsg, pc->m_desc);
			}
		}
	}

	if (subtype == MSG_EX_MESSENGER_INVITE)
	{
		CPC* pc = PCManager::instance()->getPlayerByName(charName, true);
		if (pc)
			SEND_Q(lmsg, pc->m_desc);
	}
}

CChatGroup::CChatGroup(int makeCharIndex, int chatIndex)
{
	m_makeCharIndex = makeCharIndex;
	m_chatIndex = chatIndex;
}

CChatGroup::~CChatGroup()
{
}

void CServer::CharPrePlay(CDescriptor* d)
{
	if (d->m_pChar->m_pZone == NULL || d->m_pChar->m_pArea == NULL)
	{
		LOG_ERROR("Not Found Zone OR Not Found Area");
		d->Close("Not found zone OR Not Found Area");
		return;
	}

	CArea* area = d->m_pChar->m_pArea;

	d->m_pChar->m_bPlaying = true;
	bool bCashZoneMove = false;
	if (d->m_pChar->IsSetPlayerState(PLAYER_STATE_CASH_ZONE_MOVE))
		bCashZoneMove = true;
	d->m_pChar->ResetPlayerState(~PLAYER_STATE_RESET);
	//�ʱ�ȭ �� �� ������� ����Ʈ�� �˻� �� �� �����Ͱ� ���� ��쿡�� ������� ���·� ������ش�.
	if (d->m_pChar->m_raList != NULL && d->m_pChar->m_raList->m_raPulse > 0)
	{
		d->m_pChar->SetPlayerState(PLAYER_STATE_RAMODE);
	}

	d->m_pChar->m_regGuild = 0;

	d->m_pChar->m_inventory.CheckCompositeValidation();


	// ���� ���¸� ��Ȱ
	if (DEAD(d->m_pChar))
	{
		d->m_pChar->m_hp = d->m_pChar->m_dbHP / 2;

		// MP�� ���̻� ������ �״��..
		if (d->m_pChar->m_mp < d->m_pChar->m_dbMP / 2)
			d->m_pChar->m_mp = d->m_pChar->m_dbMP / 2;
	}

	if (d->m_pChar->m_exp > d->m_pChar->GetRequiredLevelExp())
	{
		GAMELOG << init("REVISE EXP", d->m_pChar)
			<< d->m_pChar->m_exp
			<< " ==>> "
			<< d->m_pChar->GetRequiredLevelExp()
			<< end;
		d->m_pChar->m_exp = d->m_pChar->GetRequiredLevelExp();
	}



	int i;

	// �ϵ��ڵ� : Ʃ�丮�� ����Ʈ ���������� �˻� �� ���� ������ �ִ°� �˻�
	if (d->m_pChar->m_job == JOB_NIGHTSHADOW)
	{
	}
	else
	{
		CQuest* pQuest;
		CQuest* pQuestNext = d->m_pChar->m_questList.GetNextQuest(NULL, QUEST_STATE_RUN);
		while ((pQuest = pQuestNext))
		{
			pQuestNext = d->m_pChar->m_questList.GetNextQuest(pQuestNext, QUEST_STATE_RUN);
			if (pQuest->GetQuestType0() == QTYPE_KIND_TUTORIAL)
			{
				CZone* pZone = gserver->FindZone(ZONE_SINGLE_DUNGEON_TUTORIAL);
				if (pZone == NULL)
				{
					LOG_ERROR("Not found zone. zone is %d", ZONE_SINGLE_DUNGEON_TUTORIAL);
					d->Close("Not found zone");
					return;
				}

				d->m_pChar->m_pZone = pZone;
				int idx = d->m_pChar->m_pZone->SetEnableArea();

				// �� ���� ���� : ������ ���´�
				if (idx == -1)
				{
					LOG_ERROR("Not found area");
					d->Close("Not found area");
					return;
				}

				d->m_pChar->m_pArea = d->m_pChar->m_pZone->m_area + idx;
				area = d->m_pChar->m_pArea;

				GET_YLAYER(d->m_pChar) = d->m_pChar->m_pZone->m_zonePos[0][0];
				GET_R(d->m_pChar) = 0.0f;
				GET_X(d->m_pChar) = d->m_pChar->m_pZone->m_zonePos[0][1] / 2;
				GET_Z(d->m_pChar) = d->m_pChar->m_pZone->m_zonePos[0][2] / 2;
				break;
			}
		}
	}

	// ��� ���� ����
	CGuildMember* member = m_guildlist.findmember(d->m_pChar->m_index);
	if (member && member->guild())
	{
		d->m_pChar->m_guildInfo = member;
	}
	else
	{
		d->m_pChar->m_guildInfo = NULL;
	}

	// ���� ���� �ݿ�
	CWarCastle::CheckJoinAll(d->m_pChar);

	// ���� ���� ������ ���� �������� �̵��ϸ� ���� ��������Ʈ�� �̵� ����
	int posPromptMove = -1;
	int zonePromptMove = -1;
	int gstate = 0;
	int castlezone = CWarCastle::GetCurSubServerCastleZoneIndex();

	// ���� ������ ���� ����
	CWarCastle* castle = CWarCastle::GetCastleObject(castlezone);
	if (castle != NULL
		&& d->m_pChar->GetJoinFlag(castlezone) != WCJF_NONE)
	{
		time_t ct;
		time(&ct);
		int nt = castle->GetNextWarTime();
		if (ct + 10 * 60 >= nt || castle->GetState() != WCSF_NORMAL)
		{
			zonePromptMove = castlezone;
			posPromptMove = castle->GetRegenPoint(d->m_pChar->GetJoinFlag(castlezone), d->m_pChar);
		}

#ifdef WARCASTLE_MOVE_MESSAGE_LIMIT
		if (d->m_pChar->m_pZone->m_index == castle->GetZoneIndex()
			&& d->m_pChar->m_pZone->InExtra((int)GET_X(d->m_pChar), (int)GET_Z(d->m_pChar), posPromptMove))
		{
			posPromptMove = -1;
		}
#endif
		{
			gstate = castle->GetGateState();
		}
	}

	// ���� ���� ������ ���� �������� �̵��ϸ� ���� ��������Ʈ�� �̵� ����
	int posPromptMove_Dratan = -1;
	int zonePromptMove_Dratan = -1;
	CDratanCastle* pCastle = CDratanCastle::CreateInstance();
	if (GetOutDratanDungeon(d->m_pChar))
	{
		area = d->m_pChar->m_pArea;
	}
	// ���� ������ ���� ����
	if (d->m_pChar->GetJoinFlag(pCastle->GetZoneIndex()) != WCJF_NONE
		&& gserver->m_subno == WAR_CASTLE_SUBNUMBER_DRATAN)
	{
		time_t ct;
		time(&ct);
		int nt = pCastle->GetNextWarTime();

		if (ct + 10 * 60 >= nt
			|| pCastle->GetState() != WCSF_NORMAL)
		{
			zonePromptMove_Dratan = pCastle->GetZoneIndex();
			posPromptMove_Dratan = pCastle->GetRegenPoint(d->m_pChar->GetJoinFlag(pCastle->GetZoneIndex()), d->m_pChar);
		}

#ifdef WARCASTLE_MOVE_MESSAGE_LIMIT
		if (d->m_pChar->m_pZone->m_index == pCastle->GetZoneIndex()
			&& d->m_pChar->m_pZone->InExtra((int)GET_X(d->m_pChar), (int)GET_Z(d->m_pChar), posPromptMove_Dratan))
		{
			zonePromptMove_Dratan = -1;
		}
#endif

		if (gstate > 0)
			gstate |= pCastle->GetGateState();
		else
			gstate = pCastle->GetGateState();
	}

	if (gstate > 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		GuildWarGateStateMsg(rmsg, gstate, gstate);
		SEND_Q(rmsg, d);
	}


	if (NULL != d->m_pChar->m_pZone
		&& ZONE_START == d->m_pChar->m_pZone->m_index)
	{
		int extra;
		extra = 0;		// ������
		float x;
		float z;
		x = d->m_pChar->m_pos.m_x * 2.0f;
		z = d->m_pChar->m_pos.m_z * 2.0f;
		if ((d->m_pChar->m_pZone->m_zonePos[0][1] >= x && d->m_pChar->m_pZone->m_zonePos[0][3] <= x)
			&& d->m_pChar->m_pZone->m_zonePos[0][2] >= z && d->m_pChar->m_pZone->m_zonePos[0][4] <= z)
		{
			d->m_pChar->m_pos.m_x = GetRandom(d->m_pChar->m_pZone->m_zonePos[extra][1], d->m_pChar->m_pZone->m_zonePos[extra][3]) / 2.0f;
			d->m_pChar->m_pos.m_z = GetRandom(d->m_pChar->m_pZone->m_zonePos[extra][2], d->m_pChar->m_pZone->m_zonePos[extra][4]) / 2.0f;
		}
	}

	int cx, cz;
	area->PointToCellNum(GET_X(d->m_pChar), GET_Z(d->m_pChar), &cx, &cz);
	area->CharToCell(d->m_pChar, GET_YLAYER(d->m_pChar), cx, cz);

	{
		// ĳ���Ϳ��� ó�� �����ϴ� ��ġ�� �˸�.
		CNetMsg::SP rmsg(new CNetMsg);
		AtMsg(rmsg, d->m_pChar);
		SEND_Q(rmsg, d);
	}

	// NOTE: Offline vendor broadcast disabled.
	// Offline vendors should be visible through normal cell grid discovery,
	// not through explicit appearance packets which can confuse the client
	// about which character is "you".

	// ��� ����
	if (d->m_pChar->m_guildInfo)
	{
		if (d->m_pChar->m_first_inmap)
		{
			d->m_pChar->m_guildInfo->online(1);
			d->m_pChar->m_guildInfo->SetPC(d->m_pChar);

			CNetMsg::SP rmsg(new CNetMsg);
			HelperGuildOnline(rmsg, d->m_pChar->m_guildInfo);
			RefMsg(rmsg) << d->m_pChar->m_pArea->m_zone->m_index;
			SEND_Q(rmsg, m_helper);
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			GuildInfoMsg(rmsg, d->m_pChar);
			SEND_Q(rmsg, d);
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			GuildListMsg(rmsg, d->m_pChar);
			SEND_Q(rmsg, d);
		}
	}

	{
		// STAT POINT
		CNetMsg::SP rmsg(new CNetMsg);
		StatPointRemainMsg(rmsg, d->m_pChar);
		SEND_Q(rmsg, d);
	}

	// �ϵ��ڵ� : 0¥�� ���ü� 40������ �ٲ�
	CItem* item = d->m_pChar->m_inventory.FindByDBIndex(84, 0, 0);
	if (item)
	{
		item->setFlag(40);
	}

	// ���� ���� ���Ѱų� ����
	bool bProcLordItem = false;
	if (d->m_pChar->m_guildInfo && d->m_pChar->m_guildInfo->guild())
	{
		int ownZoneCount;
		int* ownZoneIndex = CWarCastle::GetOwnCastle(d->m_pChar->m_guildInfo->guild()->index(), &ownZoneCount);
		if (ownZoneIndex)
		{
			time_t curtime;
			time(&curtime);

			int i;
			for (i = 0; i < ownZoneCount; i++)
			{
				CWarCastle* castle = CWarCastle::GetCastleObject(ownZoneIndex[i]);
				if (castle)
				{
					if (castle->GetOwnerCharIndex() == d->m_pChar->m_index)
					{
						bProcLordItem = castle->GiveLordItem(d->m_pChar);
					}
				}
			}
			delete[] ownZoneIndex;
		}
	}
	// ���ְ� �ƴ϶� �ƹ� ó�� �������� ���� ���� ������ ã�Ƽ� �����
	if (!bProcLordItem)
	{
		BOOST_FOREACH(CItemProto * flagload_item, gserver->m_itemProtoList.m_flagload)
		{
			item_search_t vec;
			int sc = d->m_pChar->m_inventory.searchItemByCondition(flagload_item->getItemIndex(), 0, 0, vec);
			if (sc == 0)
				continue;

			item_search_t::iterator it = vec.begin();
			item_search_t::iterator endit = vec.end();
			for (; it != endit; ++it)
			{
				CItem* item = (*it).pItem;

				if (item->getWearPos() != WEARING_NONE)
				{
					if (item->getWearPos() >= WEARING_SHOW_START && item->getWearPos() <= WEARING_SHOW_END && d->m_pChar->m_pArea)
					{
						CNetMsg::SP rmsg(new CNetMsg);
						WearingMsg(rmsg, d->m_pChar, item->getWearPos(), -1, 0);
						d->m_pChar->m_pArea->SendToCell(rmsg, d->m_pChar, true);
					}
					d->m_pChar->m_wearInventory.RemoveItem(item->getWearPos());
				}
			}
		}
	}

	// yhj ���� 090528... ������� ���� ����
	CPet* pet = d->m_pChar->m_petList;
	while (pet)
	{
		pet->ResetSummonMountFlag();
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ExPetStatusMsg(rmsg, pet);
			SEND_Q(rmsg, d);
		}
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ExPetSkillListMsg(rmsg, pet);
			SEND_Q(rmsg, d);
		}

		// ��ȯ���� ���� ����Ʈ Ÿ���� �ƴϸ� Appear ��Ű��
		if (pet->IsWearing())
		{
			if (pet->IsMountType() && d->m_pChar->m_pZone->m_bCanMountPet)
				pet->Mount(true);
			else if (!pet->IsMountType() && d->m_pChar->m_pZone->m_bCanSummonPet)
				pet->Appear(false);
			else
				d->m_pChar->RemovePetSkillFromQuickSlot();
		}
		pet = pet->m_nextPet;
	}

	CAPet* apet = d->m_pChar->m_pApetlist;
	while (apet)
	{
		// Pet ���� MSG
		if (apet->IsWearing() && !DEAD(apet))
		{
			if (d->m_pChar->m_pZone->m_bCanSummonPet)
			{
				apet->Appear(false);
				{
					CNetMsg::SP rmsg(new CNetMsg);
					ExAPetFuntionMsg(rmsg, MSG_SUB_SKILLLIST, apet, 0);
					SEND_Q(rmsg, d);
				}

				if (apet->IsMount() && !d->m_pChar->m_pZone->m_bCanMountPet)
				{
					apet->Mount(false);
				}

				{
					CNetMsg::SP rmsg(new CNetMsg);
					APetAIOnOffMsg(rmsg, apet, MSG_APET_ERROR_OK);
					SEND_Q(rmsg, apet->GetOwner()->m_desc);
				}

				{
					CNetMsg::SP rmsg(new CNetMsg);
					APetAIListMsg(rmsg, apet);
					SEND_Q(rmsg, apet->GetOwner()->m_desc);
				}
			}
			else
			{
				apet->m_bMount = false;
				//�� ���Կ��� apet ��ų�� ��� �����.
				d->m_pChar->RemoveApetSkillFromQuickSlot();
			}
		}
		else if (d->m_pChar->m_petStashManager.FindApet(apet))
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ExAPetStatusMsg(rmsg, apet);
			SEND_Q(rmsg, d);
		}
		else
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ExApetSellInfo(rmsg, apet);
			SEND_Q(rmsg, d);
		}
		apet = apet->m_pNextPet;
	}



	// ��纼 �̺�Ʈ ���� ī�� ȸ�� : �̺�Ʈ ���� ���� �ƴϸ�
	if (m_clGoldenBall.GetStatus() == GOLDENBALL_STATUS_NOTHING)
	{
		CItem* pItemCard = d->m_pChar->m_inventory.FindByDBIndex(GOLDENBALL_CARD_INDEX);
		if (pItemCard)
		{
			GAMELOG << init("GOLDEN BALL EVENT RECALL CARD", d->m_pChar)
				<< itemlog(pItemCard)
				<< end;

			d->m_pChar->m_inventory.decreaseItemCount(pItemCard, 1);
		}
	}

	d->m_pChar->ResetPlayerState(PLAYER_STATE_SUPPORTER);
	for (i = WEARING_ACCESSORY1; i <= WEARING_ACCESSORY3; i++)
	{
		if (d->m_pChar->m_wearInventory.wearItemInfo[i])
		{
			// ������ ������
			if (d->m_pChar->m_wearInventory.wearItemInfo[i]->m_itemProto->getItemIndex() == 1912)
				d->m_pChar->SetPlayerState(PLAYER_STATE_SUPPORTER);
		}
	}

	// newslot - alanssoares
	if (d->m_pChar->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4])
	{
		// ������ ������
		if (d->m_pChar->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 1912)
			d->m_pChar->SetPlayerState(PLAYER_STATE_SUPPORTER);
	}

	// newslot - alanssoares
	for (i = WEARING_SPECIAL_ACCESSORY1; i <= WEARING_SPECIAL_ACCESSORY5; i++)
	{
		if (d->m_pChar->m_wearInventory.wearItemInfo[i])
		{
			// ������ ������
			if (d->m_pChar->m_wearInventory.wearItemInfo[i]->m_itemProto->getItemIndex() == 1912)
				d->m_pChar->SetPlayerState(PLAYER_STATE_SUPPORTER);
		}
	}

	// inven
	d->m_pChar->m_inventory.sendInfoToClient();

	if (d->m_pChar->m_ep == -1)
	{
		//ep �ʱ�ȭ ��Ŷ ����
		CNetMsg::SP rmsg(new CNetMsg);
		UpdateClient::EPInitMsg(rmsg, true);
		SEND_Q(rmsg, d);

		d->m_pChar->m_ep = 0;
	}

	// status
	d->m_pChar->SendStatus();

	// wearInven
	d->m_pChar->m_wearInventory.sendWearInfoToClient();
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CharStatusMsg(rmsg, d->m_pChar, 0);
		SEND_Q(rmsg, d);
	}

	{
		// quest
		CNetMsg::SP rmsg(new CNetMsg);
		QuestPCListMsg(rmsg, d->m_pChar);
		SEND_Q(rmsg, d);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		QuestCompleteListMsg(rmsg, d->m_pChar);
		SEND_Q(rmsg, d);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		QuestAbandonListMsg(rmsg, d->m_pChar);
		SEND_Q(rmsg, d);
	}

	// quest complete check
	d->m_pChar->m_questList.CheckComplete(d->m_pChar);

	{
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_EXTEND);
		RefMsg(rmsg) << MSG_EX_SERVER_TIME
			<< (int)gserver->m_nowseconds;
		SEND_Q(rmsg, d);
	}

	{
		// skill
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeSkillListMsg(rmsg, d->m_pChar);
		SEND_Q(rmsg, d);
	}

	// sskill
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeSSkillList(rmsg, d->m_pChar);
		SEND_Q(rmsg, d);
	}
	// Quick Slot MSG
	d->m_pChar->SendQuickSlot();

	if (d->m_pChar->m_mempos.m_count > 0)
	{
		// mempos
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeMemposList(rmsg, d->m_pChar);
		SEND_Q(rmsg, d);
	}

	{
		// assist
		CNetMsg::SP rmsg(new CNetMsg);
		AssistListMsg(rmsg, d->m_pChar);
		SEND_Q(rmsg, d);
	}

	{
		// �����ý���
		CNetMsg::SP rmsg(new CNetMsg);
		TeachInfoMsg(rmsg, d->m_pChar);
		SEND_Q(rmsg, d);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		AffinityListInfoMsg(rmsg, d->m_pChar);
		SEND_Q(rmsg, d);
	}
	d->m_pChar->m_affinityList.SendRewardNotice(d->m_pChar);

	//0627
	if ((d->m_userFlag & NOVICE) && d->m_pChar->m_teachType == MSG_TEACH_NO_TYPE)
	{
		//��� �������� �ű������� ���� ������ �˸���.
		CNetMsg::SP rmsg(new CNetMsg);
		NoviceNotifyMsg(rmsg, d->m_pChar->GetName());

		PCManager::instance()->sendToAllTeacher(rmsg);
		d->m_userFlag = d->m_userFlag & ~NOVICE;
	}

	{  //pwesty invisible helm
		bool isInvisibleHelmet = d->m_pChar->m_inventory.m_inventoryOptions.GetOptionValue<bool>(INVENTORY_OPTION_INVENTORY_OPTION);
		CNetMsg::SP rmsg(new CNetMsg);
		WearingInvisibleMsg(rmsg, d->m_pChar, (int)isInvisibleHelmet);
		SEND_Q(rmsg, d);
	}

	if (d->m_pChar->m_guildInfo)
	{
		// ����� �϶� status msg ����
		CGuild* g = d->m_pChar->m_guildInfo->guild();
		if (g && g->battleState() != GUILD_BATTLE_STATE_PEACE)
		{
			CGuild* g2 = gserver->m_guildlist.findguild(g->battleIndex());
			if (g2)
			{
				if (g->battleState() == GUILD_BATTLE_STATE_PRIZE)
				{
					if (g->boss() && g->boss()->charindex() == d->m_pChar->m_index)
					{
						d->m_pChar->m_inventory.increaseMoney(g->battlePrizeNas());

						{
							CNetMsg::SP rmsg(new CNetMsg);
							HelperGuildBattlePeaceReqMsg(rmsg, g);
							SEND_Q(rmsg, gserver->m_helper);
						}
					}
				}
				else
				{
					CNetMsg::SP rmsg(new CNetMsg);
					GuildBattleStatusMsg(rmsg, g->index(), g->name(), g->killCount(), g2->index(), g2->name(), g2->killCount(), g->battleTime(), g->battleZone());
					SEND_Q(rmsg, d);
				}
			}
		}
	}

#ifdef NOTICE_EVENT
	//0704  �̺�Ʈ ���� ������.
	for (i = 0; i < MAX_NOTICE; i++)
	{
		if (d->m_notice[i] != 0)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			NoticeInfoMsg(rmsg, d->m_notice[i]);
			SEND_Q(rmsg, d);

			d->m_notice[i] = 0;
		}
	}
#endif

	{
		// appear
		CNetMsg::SP rmsg(new CNetMsg);
		AppearMsg(rmsg, d->m_pChar, true);
		area->SendToCell(rmsg, d->m_pChar);
	}

	if (d->m_pChar->holy_water_item != NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		UpdateClient::holyWaterStateMsg(rmsg, d->m_pChar->m_index, d->m_pChar->holy_water_item->getDBIndex());
		d->m_pChar->m_pArea->SendToCell(rmsg, d->m_pChar, true);
	}

	{
		std::map<int, MAKE_TITLE*>::iterator it = d->m_pChar->_map_title.find(d->m_pChar->m_custom_title_index);
		if (it != d->m_pChar->_map_title.end())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			TitleUserInfoMsg(rmsg, d->m_pChar->m_index, it->second->color, it->second->background_color, it->second->effect, it->second->name);
			d->m_pChar->m_pArea->SendToCell(rmsg, d->m_pChar, true);
		}
	}

	// �� ������ ĳ���͵��� ������ ������...
	area->SendCellInfo(d->m_pChar, false);

	{
		// GO_ZONE ȿ�� �޽��� ����
		CNetMsg::SP rmsg(new CNetMsg);
		EffectEtcMsg(rmsg, d->m_pChar, MSG_EFFECT_ETC_GOZONE);
		area->SendToCell(rmsg, d->m_pChar, true);
	}

	// ���⿡ �޽��� �ʱⵥ��Ÿ ������..
		//MSG_EX_MESSENGER_GROUP_LIST, // �׷� ����Ʈ ������ : count(n) gIndex(n) gName(str)
	if (d->m_pChar->m_Friend)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_EXTEND);
		RefMsg(rmsg) << MSG_EX_MESSENGER
			<< (unsigned char)MSG_EX_MESSENGER_GROUP_LIST
			<< d->m_pChar->m_Friend->GetGroupCount();

		CLCString gIndexList(255 + 1);
		CLCString gNameList(255 + 1);

		int gIndex = 0;

		d->m_pChar->m_Friend->GetGroupIndexString(gIndexList, gNameList);

		const char* pgName = (const char*)gNameList;
		const char* pgIndex = (const char*)gIndexList;

		char tmpBuf[MAX_STRING_LENGTH] = { 0, };
		while (*pgIndex && *pgName)
		{
			pgIndex = AnyOneArg(pgIndex, tmpBuf);
			gIndex = atoi(tmpBuf);
			tmpBuf[0] = '\0';
			pgName = AnyOneArg(pgName, tmpBuf);

			RefMsg(rmsg) << gIndex
				<< tmpBuf;

			tmpBuf[0] = '\0';
		}

		SEND_Q(rmsg, d);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		FriendListMsg(rmsg, d);
	}

	if (d->m_pChar->m_Friend)
	{
		d->m_pChar->m_nCondition = 1;

		CNetMsg::SP rmsg(new CNetMsg);
		HelperFriendSetConditionMsg(rmsg, d->m_pChar->m_index, d->m_pChar->m_nCondition, -1, d->m_pChar);
		SEND_Q(rmsg, m_helper);
	}
	{
		// ��������Ʈ ������
		CNetMsg::SP rmsg(new CNetMsg);
		BlockPCListMsg(rmsg, d);
	}

	// ��û ���� �ð��̸� Ȯ�� �޽�����
	// ������ ���� ���̸� ���� �޽����� ������
	///=== �޼��� ���� kjtest
	{
		castle = CWarCastle::GetCastleObject(CWarCastle::GetCurSubServerCastleZoneIndex());
		if (castle)
		{
			if (castle->GetState() == WCSF_NORMAL)
			{
				if (castle->IsJoinTime())
				{
					{
						struct tm nextWarTime;
						castle->GetNextWarTime(&nextWarTime, true);
						CNetMsg::SP rmsg(new CNetMsg);
						GuildWarNoticeTimeMsg(rmsg, ZONE_MERAC, nextWarTime.tm_mon, nextWarTime.tm_mday, nextWarTime.tm_hour, nextWarTime.tm_min);
						SEND_Q(rmsg, d);
					}
				}
			}
			else
			{
				CNetMsg::SP rmsg(new CNetMsg);
				GuildWarCastleStateMsg(rmsg, ZONE_MERAC, d->m_pChar, castle);
				SEND_Q(rmsg, d);
			}
		}

		// �̵� ����
		if (zonePromptMove != -1)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			WarpPromptMsg(rmsg, zonePromptMove, posPromptMove);
			SEND_Q(rmsg, d);
		}
	}

	// ��û ���� �ð��̸� Ȯ�� �޽�����
	// ������ ���� ���̸� ���� �޽����� ������
	{
		pCastle = CDratanCastle::CreateInstance();
		if (pCastle->GetState() == WCSF_NORMAL)
		{
			if (pCastle->IsJoinTime())
			{
				struct tm nextWarTime;
				pCastle->GetNextWarTime(&nextWarTime, true);
				CNetMsg::SP rmsg(new CNetMsg);
				GuildWarNoticeTimeMsg(rmsg, ZONE_DRATAN, nextWarTime.tm_mon, nextWarTime.tm_mday, nextWarTime.tm_hour, nextWarTime.tm_min);
				SEND_Q(rmsg, d);
			}
		}
		else
		{
			CNetMsg::SP rmsg(new CNetMsg);
			GuildWarCastleStateMsg(rmsg, ZONE_DRATAN, d->m_pChar, pCastle);
			SEND_Q(rmsg, d);
		}

		// �̵� ����
		if (zonePromptMove_Dratan != -1)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			WarpPromptMsg(rmsg, zonePromptMove_Dratan, posPromptMove_Dratan);
			SEND_Q(rmsg, d);
		}
	}

#ifdef GER_LOG
	// �ɸ��� �α��� �ð����
//	d->m_pChar->SetLoginTime();

	GAMELOGGEM << init(0, "CHAR_ENTER_GAME")
		<< LOG_VAL("account-id", d->m_idname) << blank
		<< LOG_VAL("character-name", d->m_pChar->m_name) << blank
		<< LOG_VAL("ipv4", d->getHostString()) << blank
		<< LOG_VAL("zone-id", d->m_pChar->m_pZone->m_index) << blank
		<< endGer;
#endif // GER_LOG
	GAMELOG << init("JOIN", d->m_pChar->m_name, d->m_pChar->m_nick, d->m_idname)
		<< d->m_pChar->m_index << delim
		<< d->m_pChar->m_pZone->m_index << delim
		<< d->getHostString()
		<< end;

	// ĳ���� �ð� ���� �ʱ�ȭ
	d->SetHackCheckPulse();

#ifdef RANKER_NOTICE
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnRankerReqMsg(rmsg, d->m_pChar->m_index, d->m_pChar->m_index);
		SEND_Q(rmsg, gserver->m_connector);
	}
#endif // RANKER_NOTICE

	/*if( d->m_pChar->m_guildInfo && d->m_pChar->m_guildInfo->guild() )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ConnGuildPointRankerReqMsg( rmsg, d->m_pChar->m_guildInfo->guild()->index(), d->m_pChar->m_index );
		SEND_Q(rmsg, gserver->m_connector );
	}*/

	if (d->m_pChar->m_guildInfo && d->m_pChar->m_guildInfo->guild() && d->m_pChar->m_pArea)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		GuildPointRankingMsg(rmsg, d->m_pChar->m_index, d->m_pChar->m_guildInfo->guild()->index(), d->m_pChar->m_guildInfo->guild()->GetGuildPointRanking());
		d->m_pChar->m_pArea->SendToCell(rmsg, d->m_pChar);
	}
	if (d->m_pChar->m_pArea)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		GuildNameColorStateMsg(rmsg, d->m_pChar);
		d->m_pChar->m_pArea->SendToCell(rmsg, d->m_pChar);
		SEND_Q(rmsg, d->m_pChar->m_desc);
	}

	// ��Ƽ ����Ʈ���� ���� ������ ��Ƽ ������ ã�� �����Ѵ�
	d->m_pChar->m_party = FindPartyByMemberIndex(d->m_pChar->m_index, false);
	if (d->m_pChar->IsParty())
	{
		GAMELOG << init("SET_PARTY_MEMBER", d->m_pChar)
			<< "BOSSINDEX" << delim << d->m_pChar->m_party->GetBossIndex()
			<< end;

#ifdef BATTLE_PARTY_BOSS_CHANGE // ������Ƽ ���� ����. �ڱ�� ������ �������̰� 10�����̻� ���� ���� �α׿��� �ߴٰ� ������ ����� ��Ż��.
		if (d->m_pChar->m_party->GetPartyType(0) == MSG_PARTY_TYPE_BATTLE &&
			d->m_pChar->m_party->GetPartyType(3) == MSG_PARTY_TYPE_BATTLE &&
			d->m_pChar->m_party->GetPartyType(4) == MSG_PARTY_TYPE_BATTLE)
		{
			CPartyMember* member = d->m_pChar->m_party->GetMemberByListIndex(0);
			if (member != NULL)
			{
				if (ABS(d->m_pChar->m_level - member->m_nLevel) < 11)
				{
					d->m_pChar->m_party->SetMemberRegister_AfterGoZone(d->m_pChar);
				}
				else
				{
					// �α��� ���� ��Ƽ Ż��
					{
						CNetMsg::SP rmsg(new CNetMsg);
						HelperPartyQuitReqMsg(rmsg, d->m_pChar->m_party->GetBossIndex(), d->m_pChar->m_index);
						SEND_Q(rmsg, gserver->m_helper);
					}
				}
			}
		}
		else
			d->m_pChar->m_party->SetMemberRegister_AfterGoZone(d->m_pChar);
#else
		d->m_pChar->m_party->SetMemberRegister_AfterGoZone(d->m_pChar);
#endif // BATTLE_PARTY_BOSS_CHANGE
	}

	// ������ ����Ʈ���� ���� ������ ������ ������ ã�� �����Ѵ�
	d->m_pChar->m_Exped = FindExpedByMemberIndex(d->m_pChar->m_index, false);
	if (d->m_pChar->IsExped())
	{
		d->m_pChar->m_Exped->SetMemberRegister_AfterGoZone(d->m_pChar);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyMatchMemberChangeInfoMsg(rmsg, d->m_pChar->m_index, MSG_HELPER_PARTY_MATCH_MEMBER_CHANGE_INFO_ZONE, "", d->m_pChar->m_level, d->m_pChar->m_pZone->m_index);
		SEND_Q(rmsg, gserver->m_helper);
	}

	if (d->m_pChar->m_nGoldenBallNoticeStatus != m_clGoldenBall.GetStatus())
	{
		d->m_pChar->m_nGoldenBallNoticeStatus = m_clGoldenBall.GetStatus();

		switch (m_clGoldenBall.GetStatus())
		{
		case GOLDENBALL_STATUS_VOTE:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			EventGoldenballVoteStartMsg(rmsg, m_clGoldenBall.GetTeam1Name(), m_clGoldenBall.GetTeam2Name(), m_clGoldenBall.GetEndYear(), m_clGoldenBall.GetEndMonth(), m_clGoldenBall.GetEndDay(), m_clGoldenBall.GetEndHour(), m_clGoldenBall.GetEndMinute());
			SEND_Q(rmsg, d);
		}
		break;

		case GOLDENBALL_STATUS_VOTE_END:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			EventGoldenballVoteEndMsg(rmsg, m_clGoldenBall.GetTeam1Name(), m_clGoldenBall.GetTeam2Name());
			SEND_Q(rmsg, d);
		}
		break;

		case GOLDENBALL_STATUS_GIFT:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			EventGoldenballGiftStartMsg(rmsg, m_clGoldenBall.GetTeam1Name(), m_clGoldenBall.GetTeam1Score(), m_clGoldenBall.GetTeam2Name(), m_clGoldenBall.GetTeam2Score(), m_clGoldenBall.GetEndYear(), m_clGoldenBall.GetEndMonth(), m_clGoldenBall.GetEndDay(), m_clGoldenBall.GetEndHour(), m_clGoldenBall.GetEndMinute());
			SEND_Q(rmsg, d);
		}
		break;

		default:
			break;
		}
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		CashItemGiftRecvNoticeRepMsg(rmsg, (d->m_userFlag & RECV_GIFT) ? 1 : 0);
		SEND_Q(rmsg, d);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ExPlayerStateChangeMsg(rmsg, d->m_pChar);
		SEND_Q(rmsg, d);
	}

	if (d->m_pChar->m_teachType == MSG_TEACH_TEACHER_TYPE)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperTeachLimitTimeCheck(rmsg, d->m_pChar->m_index);
		SEND_Q(rmsg, gserver->m_helper);
	}

	d->m_pChar->m_bLoadChar = true;
	d->m_pChar->OutputDBItemLog();

#ifdef FREE_PK_SYSTEM
	if (gserver->m_bFreePk)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		FreePKMsg(rmsg);
		SEND_Q(rmsg, d);
	}
#endif

	if (gserver->isActiveEvent(A_EVENT_XMAS))
	{
		CSkill* pSkill = gserver->m_skillProtoList.Create(491, 1);  //pwesty changed to sunrise skill was 490
		if (pSkill)
		{
			bool bApply = false;
			ApplySkill(d->m_pChar, d->m_pChar, pSkill, -1, bApply);
			if (!bApply)
			{
				GAMELOG << init("EVENT XMAS SKILL FAILED (LOGIN) ", d->m_pChar) << end;// ��ų ���� ����
			}
		}
	}
	else
	{
		if (d->m_pChar->m_assist.FindBySkillIndex(491))  //pwesty changed to sunrise skill was 490
		{
			d->m_pChar->m_assist.CureBySkillIndex(491); //pwesty changed to sunrise skill was 490
		}
	}

	if (d->m_pChar->m_assist.FindBySkillIndex(993))
	{
		d->m_pChar->m_assist.CureBySkillIndex(993);
	}

#ifdef EVENT_PCBANG_2ND
	if (d->m_location == BILL_LOCATION_PCBANG)
	{
		CSkill* pSkill = gserver->m_skillProtoList.Create(493, 1);
		if (pSkill != NULL)
		{
			bool bApply = false;
			ApplySkill(d->m_pChar, d->m_pChar, pSkill, -1, bApply);
			if (bApply == false)
			{
				GAMELOG << init("EVENT_PCBANG_2NDS SKILL FAILED (LOGIN) ", d->m_pChar) << end;// ��ų ���� ����
			}
		}
	}
#endif // EVENT_PCBANG_2ND

	// �Ǵн� �ɸ��� �̸鼭 100 ������ ���� �ʴ´ٸ� �Ǵн� ������ �ش�.
	if (d->m_pChar->m_bPhoenix_Char == 1 && d->m_pChar->m_reborn >= 1)
	{
		int level = 1;
		if (d->m_pChar->m_bPremium_Phoenix == 1)
			level = 2;

		CSkill* pSkill1 = gserver->m_skillProtoList.Create(516, level);
		if (pSkill1 != NULL)
		{
			bool bApply = false;
			ApplySkill(d->m_pChar, d->m_pChar, pSkill1, -1, bApply);
			if (bApply == false)
			{
				GAMELOG << init("EVENT_PHOENIX SKILL FAILED (LOGIN) ", d->m_pChar) << end;// ��ų ���� ����
			}
		}
	}
#ifdef DEMIGOD
	if (d->m_pChar->m_DemiGod == 1)
	{
		int level = 1;

		CSkill* pSkill1 = gserver->m_skillProtoList.Create(2059, level);
		if (pSkill1 != NULL)
		{
			bool bApply = false;
			ApplySkill(d->m_pChar, d->m_pChar, pSkill1, -1, bApply);
			if (bApply == false)
			{
				GAMELOG << init("EVENT_DEMIGOD SKILL FAILED (LOGIN) ", d->m_pChar) << end;// ��ų ���� ����
			}
		}
	}
#endif // DEMIGOD
#ifdef WAR_CASTLE_BUFF
	{
		char bCastellan;
		int zonenum;
		if (d->m_pChar->CheckCastellanType(zonenum, bCastellan) || !bCastellan)
		{
			LOG_INFO("Castle war buff");
			int skillIdx = -1;
			if (zonenum == ZONE_MERAC)
				skillIdx = 1869;
			else if (zonenum == ZONE_DRATAN)
				skillIdx = 1868;

			CSkill* pSkill1 = gserver->m_skillProtoList.Create(skillIdx, 1);
			if (pSkill1) {
				bool bApply;
				ApplySkill(d->m_pChar, d->m_pChar, pSkill1, -1, bApply);
				if (bApply) {
					LOG_INFO("Skill applied");
					GAMELOG << init("CASTLE BUFF ", d->m_pChar) << end;
				}
				else {
					LOG_INFO("Skill cannot be applied");
				}
			}
			else {
				LOG_INFO("Skill not found ", d->m_pChar);
			}
		}
		else {
			LOG_INFO("Remove castle war buff");
			d->m_pChar->m_assist.CureBySkillIndex(1868);
			d->m_pChar->m_assist.CureBySkillIndex(1869);
		}
	}
#endif

	if (pCastle != NULL && d->m_pChar != NULL && d->m_pChar->m_pZone->m_index == ZONE_DRATAN)
	{
		// �������̸� ��Ȱ ���� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		CastletowerQuartersListMsg(rmsg, pCastle);
		SEND_Q(rmsg, d);
	}

	switch (d->m_pChar->m_job)
	{
	case JOB_TITAN:
	case JOB_KNIGHT:
	case JOB_MAGE:
#ifdef EX_MAGE
	case JOB_EX_MAGE:
#endif // EX_MAGE
	case JOB_ROGUE:
#ifdef EX_ROGUE
	case JOB_EX_ROGUE:
#endif // EX_ROGUE
	case JOB_SORCERER:
	default:
		d->m_pChar->m_attacktype = ATTACK_TYPE_NORMAL;
		break;
	case JOB_HEALER:
	case JOB_NIGHTSHADOW:
		d->m_pChar->m_attacktype = ATTACK_TYPE_DOUBLE;
		break;
	}

	// Ʈ���Ÿ� ����ϴ� Area�̸�
	if (area && area->m_bUseTriggerEvent)
	{
		// �ش� Area�� Ʈ���� ����Ʈ ������ �����ش�.
		area->m_CTriggerList.SyncForClient_TriggerInfo(d->m_pChar);
	}


	{
		CNetMsg::SP rmsg(new CNetMsg);
		NpcPortalLoadingEndUseMsg(rmsg);
		SEND_Q(rmsg, d);
	}

	// ����Ÿ������ �� �˸� ������.
	if (m_bDungeonTimeToggle == true && m_bIsTime == true)
	{
		//msg ���� �� ��.
		int exp = 100;
		for (int i = 0; i < gserver->m_iZoneCount; i++)
		{
			if (gserver->m_iZoneExp[i] > 100)
			{
				exp = gserver->m_iZoneExp[i] - 100;
				break;
			}
		}

		CNetMsg::SP rmsg(new CNetMsg);
		DungeonTimeNoticeMsg(rmsg, MSG_EX_DUNGEONTIME_NOTICE, m_iStartTime, m_iEndTime, exp);
		SEND_Q(rmsg, d);
	}

	if (d->m_pChar->m_job == JOB_NIGHTSHADOW)
		d->m_pChar->m_newtutoComplete = 1;

	if (d->m_pChar->m_newtutoComplete == 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		NewTutorialMsg(rmsg);
		SEND_Q(rmsg, d);
	}

	if (d->m_pChar->m_pZone->m_index == ZONE_TARIAN_DUNGEON)
	{
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SendRaidSceneObjectStateMsg(rmsg, d->m_pChar);
			SEND_Q(rmsg, d->m_pChar->m_desc);
		}

		int loop;
		for (loop = 0; loop < 8; loop++)
		{
			if (d->m_pChar->m_pArea->m_AkanPCList[loop] == NULL)
			{
				d->m_pChar->m_pArea->m_AkanPCList[loop] = d->m_pChar;
				break;
			}
		}
		if (loop == 8)
		{
			// ��ĭ��� �ο��� ��ã�µ�, �� ���Դ�. ƨ�ܹ���!
			CNetMsg::SP rmsg(new CNetMsg);
			RaidInzoneQuitReq(rmsg, 1, 0);
			do_Raid(d->m_pChar, rmsg);
			return;
		}
	}

	if (d->m_pChar->m_pZone->m_index == ZONE_ENCHANTED_DUNGEON) //Val add new raid loops
	{
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SendRaidSceneObjectStateMsg(rmsg, d->m_pChar);
			SEND_Q(rmsg, d->m_pChar->m_desc);
		}

		int loop;
		for (loop = 0; loop < 8; loop++)
		{
			if (d->m_pChar->m_pArea->m_AkanPCList[loop] == NULL)
			{
				d->m_pChar->m_pArea->m_AkanPCList[loop] = d->m_pChar;
				break;
			}
		}
		if (loop == 8)
		{
			// ��ĭ��� �ο��� ��ã�µ�, �� ���Դ�. ƨ�ܹ���!
			CNetMsg::SP rmsg(new CNetMsg);
			RaidInzoneQuitReq(rmsg, 1, 0);
			do_Raid(d->m_pChar, rmsg);
			return;
		}
	}



	if (d->m_pChar->m_pZone->m_index == ZONE_AKAN_TEMPLE)
	{
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SendRaidSceneObjectStateMsg(rmsg, d->m_pChar);
			SEND_Q(rmsg, d->m_pChar->m_desc);
		}

		int loop;
		for (loop = 0; loop < 8; loop++)
		{
			if (d->m_pChar->m_pArea->m_AkanPCList[loop] == NULL)
			{
				d->m_pChar->m_pArea->m_AkanPCList[loop] = d->m_pChar;
				break;
			}
		}
		if (loop == 8)
		{
			// ��ĭ��� �ο��� ��ã�µ�, �� ���Դ�. ƨ�ܹ���!
			CNetMsg::SP rmsg(new CNetMsg);
			RaidInzoneQuitReq(rmsg, 1, 0);
			do_Raid(d->m_pChar, rmsg);
			return;
		}
	}

	char bCastellan;
	int castleNum;
	if (!d->m_pChar->CheckCastellanType(castleNum, bCastellan))
		castleNum = -1;

	// castleNum ���ܵ� ������, ȣĪ����
	d->m_pChar->m_inventory.CastllanItemRemove(castleNum, false, true, bCastellan);
	d->m_pChar->CastllanTitleDelete(castleNum, true, bCastellan);

	{
		CNetMsg::SP rmsg(new CNetMsg);
		if (gserver->m_bCashShopLock == true)
			MsgCashShopLock(rmsg, MSG_EX_CASHITEM_SHOP_LOCK);
		else
			MsgCashShopLock(rmsg, MSG_EX_CASHITEM_SHOP_UNLOCK);
		SEND_Q(rmsg, d->m_pChar->m_desc);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);

		if (g_bUpgradeEvent)
			EventEnchantRate(rmsg, 1, g_nUpgradeProb);
		else
			EventEnchantRate(rmsg, 0, g_nUpgradeProb);

		SEND_Q(rmsg, d->m_pChar->m_desc);
	}



	if (d->m_pChar->m_pZone->IsWarGroundZone())
	{
		CWaitPlayer* pWp = NULL;
		pWp = gserver->m_RoyalRumble.m_WaitPlayerList.GetNode(d->m_pChar->m_index);
		if (pWp != NULL)
			pWp->SetCheckIn(true);
	}
	else if (gserver->m_RoyalRumble.GetRoyalRumbleNotice())
	{
		if (gserver->m_subno == WAR_GROUND_CHANNEL)
		{
			if (!gserver->m_RoyalRumble.m_WGPlayerList.FindNode(d->m_pChar->m_index))
			{
				{
					CNetMsg::SP rmsg(new CNetMsg);
					RoyalRumbleRegistMenu(rmsg, 1);
					SEND_Q(rmsg, d->m_pChar->m_desc);
				}

				if (d->m_pChar->m_admin > 0)
				{
					GAMELOG << init("ROYAL RUMBLE") << "ROYAL RUMBLE NOTICE IS true" << end;
				}
			}
			int command = gserver->m_RoyalRumble.GetRoyalRumbleProcess();
			if (command >= 1 && command <= 5)
			{
				if (command == 1 || command == 2)
					command = 0;
				else if (command > 2)
					command = command - 2;

				{
					CNetMsg::SP rmsg(new CNetMsg);
					RoyalRumbleTimeNotice(rmsg, (unsigned char)command, gserver->m_RoyalRumble.GetRemainWaitTime());
					SEND_Q(rmsg, d->m_pChar->m_desc);
				}
			}
		}
	}
	else if (!gserver->m_RoyalRumble.GetRoyalRumbleNotice())
	{
		if (gserver->m_subno == WAR_GROUND_CHANNEL)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			RoyalRumbleRegistMenu(rmsg, 0);
			SEND_Q(rmsg, d->m_pChar->m_desc);
			if (d->m_pChar->m_admin > 0)
			{
				GAMELOG << init("ROYAL RUMBLE") << "ROYAL RUMBLE NOTICE IS false" << end;
			}
		}
	}
	// ���̵� �� ITEM_FLAG_ZONEMOVE_DEL �� �������� ��������.
	{
		item_search_t vec;
		d->m_pChar->m_inventory.searchFlagByItemProto(ITEM_FLAG_ZONEMOVE_DEL, vec);
		item_search_t::iterator it = vec.begin();
		item_search_t::iterator endit = vec.end();
		for (; it != endit; ++it)
		{
			CItem* item = (*it).pItem;

			CNetMsg::SP rmsg(new CNetMsg);
			insideServer_do_ItemDelete(rmsg, item);
			do_Item(d->m_pChar, rmsg);
		}
	}

#ifdef REFORM_PK_PENALTY_201108 // 2011-08 PK �г�Ƽ ����
	{
		CNetMsg::SP rmsg(new CNetMsg);
		MsgSubHelperPKPenaltyRewardInfoReq(rmsg, d->m_pChar->m_index);
		SEND_Q(rmsg, gserver->m_subHelper);
	}
#endif // REFORM_PK_PENALTY_201108

	std::map<int, CEventInfo*>* eventList = gserver->getActiveEvenList();
	if (eventList && eventList->size() > 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		EventActiveListMsg(rmsg, eventList);
		SEND_Q(rmsg, d->m_pChar->m_desc);
	}

	if (d->m_pChar->m_pArea->GetPCCount() > 1
		&& d->m_pChar->m_admin == 0
		&& d->m_pChar->m_pZone->IsComboZone()
		&& (!d->m_pChar->IsParty()))			// area�� �ٸ� ����� �ִµ� ���� ��Ƽ�� �ƴϴ�. �׷��� ��Ƽ ���� �޺��ε� ���� �߸��� ���̴�. �ٽ� ������.
	{
		int extra = 0;
		CZone* pZone = gserver->FindZone(ZONE_DRATAN);
		if (pZone)
		{
			GAMELOG << init("GET OUT COMBO AREA BY PARTY QUIT", d->m_pChar)
				<< "AREA INDEX: "
				<< d->m_pChar->m_pArea->m_index
				<< "COMBO INDEX: "
				<< d->m_pChar->m_pArea->m_monsterCombo->m_nIndex
				<< end;

			GoZoneForce(d->m_pChar, pZone->m_index,
				pZone->m_zonePos[extra][0],
				GetRandom(pZone->m_zonePos[extra][1], pZone->m_zonePos[extra][3]) / 2.0f,
				GetRandom(pZone->m_zonePos[extra][2], pZone->m_zonePos[extra][4]) / 2.0f);
		}
	}

	d->m_pChar->m_pArea->SetMelted();

	{
		if (d->m_pChar->m_memposTime - gserver->getNowSecond() <= 0)
		{
			d->m_pChar->m_memposTime = 0;
		}

		if (d->m_pChar->m_stashextTime - gserver->getNowSecond() <= 0)
		{
			d->m_pChar->m_stashextTime = 0;
		}

		CNetMsg::SP rmsg(new CNetMsg);
		UpdateClient::makeOldTimerItem(rmsg, d->m_pChar->m_memposTime, d->m_pChar->m_stashextTime);
		SEND_Q(rmsg, d);
	}

#ifdef PREMIUM_CHAR
	d->m_pChar->m_premiumChar.sendInfo();

	// �� ������ �α׾ƿ����¿��� �ð��� ����Ǿ��� ���� �˻���
	d->m_pChar->m_premiumChar.checkExpireTime(gserver->getNowSecond());

	d->m_pChar->m_premiumChar.checkJumpCount();
#endif

	gserver->m_RLGL.OnEnterZone(d->m_pChar);

	d->m_pChar->m_first_inmap = false;	// �� ������ �׻� �Լ� �� �������� ����Ұ�
}

#ifdef GMTOOL
void CServer::GMToolCharPrePlay(CDescriptor* d)
{
	int i = 0;
	char id[MAX_ID_NAME_LENGTH + 1];
	char tmpBuf[MAX_STRING_LENGTH] = { 0, };
	for (i = 0; i < gserver->m_nGMToolCount; ++i)
	{
		sprintf(tmpBuf, "GMTOOL_%d", i);
		if (gserver->m_config.Find(tmpBuf, "ID"))
		{
			memset(id, 0, MAX_ID_NAME_LENGTH + 1);
			strcpy(id, gserver->m_config.Find(tmpBuf, "ID"));
			if (strcmp(id, d->m_idname) == 0)
			{
				break;
			}
		}
	}

	if (i == gserver->m_nGMToolCount)
	{
		d->Close("Not gm id.");
		return;
	}

	if (gserver->m_nGMToolCount > 0)
	{
		for (i = 0; i < gserver->m_nGMToolCount; ++i)
		{
			if (gserver->m_gmtool[i] == NULL)
			{
				gserver->m_gmtool[i] = d;
				break;
			}
		}

		if (i == gserver->m_nGMToolCount)
		{
			d->Close("gm tool is full.");
			return;
		}
	}
	else
	{
		d->Close("gm tool count is 0.");
		return;
	}

	{
		int key = 0;
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_LOGIN);
		RefMsg(rmsg) << d->m_pChar->m_index
			<< d->m_pChar->m_name
			<< d->m_nPrepareSeed
			<< d->m_pChar->m_job
			<< key;

		SEND_Q(rmsg, d);
	}

	STATE(d) = CON_PLAYING;
	CDescriptor::auto_set[d->m_autoSaveSeq].erase(d);
}
#endif // GMTOOL

CMoonStoneRewardData::CMoonStoneRewardData()
{
}

CMoonStoneRewardData::~CMoonStoneRewardData()
{
	map_reward_t::iterator it = m_listReward.begin();
	map_reward_t::iterator endit = m_listReward.end();
	for (; it != endit; ++it)
	{
		delete (it->second);
	}
	m_listReward.clear();
}

bool CMoonStoneRewardData::Load(int idx)
{
	CLCString sql(1024);
	sql.Format("SELECT * FROM t_moonstone_reward WHERE a_type = %d ORDER BY a_giftindex", idx);

	CDBCmd cmd;
	cmd.Init(&gserver->m_dbdata);
	cmd.SetQuery(sql);
	if (!cmd.Open())
		return false;

	m_nMoonStoneIndex = idx;
	m_nTotalProb = 0;
	int giftindex, giftcount, giftflag;
	float giftprob;
	while (cmd.MoveNext())
	{
		REWARD* reward = new REWARD;

		cmd.GetRec("a_giftindex", giftindex);
		cmd.GetRec("a_giftcount", giftcount);
		cmd.GetRec("a_giftflag", giftflag);
		cmd.GetRec("a_giftprob", giftprob);

		reward->rewardindex = giftindex;
		reward->rewardcount = giftcount;
		reward->prob = giftprob;
		reward->rewardflag = giftflag;

		m_listReward.insert(map_reward_t::value_type(reward->rewardindex, reward));
		m_nTotalProb += (int)(giftprob * 10000.0);
	}

	return true;
}

CMoonStoneReward::CMoonStoneReward()
{
	m_pReward = NULL;
	m_nRewardDataCount = 0;
}

CMoonStoneReward::~CMoonStoneReward()
{
	if (m_pReward)
	{
		delete[] m_pReward;
		m_pReward = NULL;
	}

	m_nRewardDataCount = 0;
}

bool CMoonStoneReward::Load()
{
	CLCString sql(1024);
	sql.Format("SELECT distinct a_type FROM t_moonstone_reward ORDER BY a_type");
	CDBCmd cmd, cmddata;
	cmd.Init(&gserver->m_dbdata);
	cmddata.Init(&gserver->m_dbdata);

	cmd.SetQuery(sql);
	if (!cmd.Open())
		return false;

	if (cmd.GetRecordCount() == 0)
		return false;

	int i = 0;
	int type;
	m_nRewardDataCount = cmd.GetRecordCount();
	m_pReward = new CMoonStoneRewardData[cmd.GetRecordCount()];
	while (cmd.MoveNext())
	{
		cmd.GetRec("a_type", type);
		if (!m_pReward[i].Load(type))
			return false;

		map_.insert(map_t::value_type(m_pReward[i].m_nMoonStoneIndex, &m_pReward[i]));

		i++;
	}
	return true;
}

CBattleWarfare::~CBattleWarfare()
{
}

CBattleWarfare::CBattleWarfare()
{
}

bool CBattleWarfare::Load()
{
	m_start_hour = 0;
	m_status = false;
	m_item_idx = -1;
	m_item_count = 0;
	m_start_min = 0;
	m_time = 0;

	LOG_INFO("Initializing database command for CBattleWarfare::Load");

	CDBCmd dbcmd;
	dbcmd.Init(&gserver->m_dbdata);

	std::string select_config = "SELECT a_start_hour, a_start_min, a_item_idx, a_item_count, a_time FROM t_battle";
	dbcmd.SetQuery(select_config);

	LOG_INFO("Executing query: %s", select_config.c_str());

	if (!dbcmd.Open()) {
		LOG_ERROR("Failed to open database command for CBattleWarfare::Load");
		return false;
	}

	LOG_INFO("Query opened successfully for CBattleWarfare::Load");

	if (!dbcmd.MoveFirst()) {
		LOG_ERROR("No records found in t_battle table for CBattleWarfare::Load");
		return false;
	}

	LOG_INFO("Record found, loading warfare info");

	if (!dbcmd.GetRec("a_start_hour", m_start_hour)) {
		LOG_ERROR("Failed to retrieve a_start_hour");
		return false;
	}

	if (!dbcmd.GetRec("a_start_min", m_start_min)) {
		LOG_ERROR("Failed to retrieve a_start_min");
		return false;
	}

	if (!dbcmd.GetRec("a_item_idx", m_item_idx)) {
		LOG_ERROR("Failed to retrieve a_item_idx");
		return false;
	}

	if (!dbcmd.GetRec("a_item_count", m_item_count)) {
		LOG_ERROR("Failed to retrieve a_item_count");
		return false;
	}

	if (!dbcmd.GetRec("a_time", m_time)) {
		LOG_ERROR("Failed to retrieve a_time");
		return false;
	}

	LOG_INFO("Loaded warfare info successfully: start_hour=%d, start_min=%d, item_idx=%d, item_count=%d, time=%d",
		m_start_hour, m_start_min, m_item_idx, m_item_count, m_time);

	return true;
}

void CBattleWarfare::Finish()
{
	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter = playerMap.begin();
	PCManager::map_t::iterator endIter = playerMap.end();

	CZone* pStartZone = gserver->FindZone(ZONE_START);
	if (pStartZone == NULL)
		return;

	for (; iter != endIter; ++iter) {
		CPC* tpc = (*iter).pPlayer;
		if (tpc == NULL || tpc->m_pZone == NULL)
			continue;

		if (tpc->m_pZone->m_index == ZONE_WARFARE_BATTLE) {
			GoZone(tpc, ZONE_START, pStartZone->m_zonePos[0][0],								// ylayer
				GetRandom(pStartZone->m_zonePos[0][1], pStartZone->m_zonePos[0][3]) / 2.0f,		// x
				GetRandom(pStartZone->m_zonePos[0][2], pStartZone->m_zonePos[0][4]) / 2.0f);	// z
		}
	}

	m_status = false;
}

void CBattleWarfare::CheckTime()
{
	if (gserver->m_subno == WAR_GROUND_CHANNEL) {
		if (IsActive()) {
			if (gserver->m_tRealSystemTime.tm_min - m_start_min > m_time) {
				Finish();
			}
		}
		else if (gserver->m_tRealSystemTime.tm_hour == m_start_hour &&
			gserver->m_tRealSystemTime.tm_min == m_start_min) {
			m_status = true;
			MoveToBattle();
		}
	}
}

bool CBattleWarfare::IsNotice(CPC* ch)
{
	if (!gserver->m_BattleWarfare.IsActive())
		return false;

	if (ch->m_bBattleWarfare)
		return false;

	if (ch->m_pZone->m_index == ZONE_WARFARE_BATTLE)
		return false;

	return true;
}

void CBattleWarfare::MoveToBattle()
{
	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter = playerMap.begin();
	PCManager::map_t::iterator endIter = playerMap.end();
	for (; iter != endIter; ++iter) {
		CPC* tpc = (*iter).pPlayer;

		if (tpc == NULL || tpc->m_desc == NULL)
			continue;

		{
			CNetMsg::SP rmsg(new CNetMsg);
			MoveBattleWarfareMsg(rmsg, tpc->m_desc->m_index);
			SEND_Q(rmsg, tpc->m_desc);
		}
	}
}

CEventSummon::~CEventSummon()
{
}

CEventSummon::CEventSummon()
{
}
bool CEventSummon::CheckNpc(int index) {
	// Iterate through the events to find if any event involves the given NPC index
	for (const auto& event : m_events) {
		if (event.npc_idx == index) {
			return true;  // NPC is part of an event
		}
	}
	return false;  // NPC is not part of any event
}//pwesty fix
bool CEventSummon::IsActive() const {
	// Check if any event is currently active
	for (const auto& event : m_events) {
		if (event.status) {
			return true;
		}
	}
	return false;
}//pwesty fix
bool CEventSummon::Load() {
	// Clear previous data
	m_events.clear();
	m_items.clear();
	m_items_count.clear();

	CDBCmd dbcmd;
	dbcmd.Init(&gserver->m_dbdata);

	std::string select_config = "SELECT * FROM t_event_summon ORDER BY a_start_day, a_start_hour, a_start_min";
	dbcmd.SetQuery(select_config);

	if (!dbcmd.Open() || !dbcmd.MoveFirst()) {
		// Log or handle the error
		return false;
	}

	// Iterate through each row in the result set
	do {
		EventData eventData;
		if (!dbcmd.GetRec("a_start_day", eventData.start_day) ||
			!dbcmd.GetRec("a_start_hour", eventData.start_hour) ||
			!dbcmd.GetRec("a_start_min", eventData.start_min) ||
			!dbcmd.GetRec("a_npc_idx", eventData.npc_idx) ||
			!dbcmd.GetRec("a_npc_total", eventData.npc_total)) {
			// Log or handle the error
			return false;
		}

		// Initialize additional fields
		eventData.npc_total_dead = 0;
		eventData.status = false;
		eventData.last_min = 0;

		// You may need to retrieve specific event-related items here
		// Clear previous items and counts for each event
		std::vector<int> eventItems;
		std::vector<int> eventItemsCount;

		for (int i = 1; i <= 5; ++i) {
			int itemIdx = 0;
			int itemCount = 0;
			if (dbcmd.GetRec(boost::str(boost::format("a_item%d_idx") % i).c_str(), itemIdx) &&
				dbcmd.GetRec(boost::str(boost::format("a_item%d_count") % i).c_str(), itemCount) &&
				itemIdx > 0) {
				eventItems.push_back(itemIdx);
				eventItemsCount.push_back(itemCount);
			}
		}

		// Store items and counts in the class
		// If items are specific to the event, you might need to adjust how you store them

		// Push the event data to the events vector
		m_events.push_back(eventData);

	} while (dbcmd.MoveNext());

	return true;
}//pwesty fix

void CEventSummon::CheckEventTime() {
	if (gserver->m_subno == WAR_GROUND_CHANNEL) {
		int curDay = gserver->m_tRealSystemTime.tm_wday;
		int curHour = gserver->m_tRealSystemTime.tm_hour;
		int curMin = gserver->m_tRealSystemTime.tm_min;

		for (size_t i = 0; i < m_events.size(); ++i) {
			auto& event = m_events[i];

			// Reset event if all NPCs are dead
			if (event.npc_total == event.npc_total_dead) {
				event.status = false;
				event.npc_total_dead = 0;
			}

			// Skip if the event is active
			if (event.status) {
				int totalLeft = event.npc_total - event.npc_total_dead;
				if (totalLeft > 0 && curDay == event.start_day && curHour == event.start_hour && curMin == event.start_min - 5) {  // Notify 5 minutes before the event ends
					CNetMsg::SP rmsg(new CNetMsg);
					std::string buffer = boost::str(boost::format("Reminder: %d NPCs left to kill in the event!") % totalLeft);
					MsgrNoticeMsg(rmsg, -1, -1, -1, -1, buffer.c_str());
					SEND_Q(rmsg, gserver->m_messenger);
				}
				continue;  // Skip to the next event if the current event is active
			}

			// Check if it's time to start the event
			if (curDay == event.start_day && curHour == event.start_hour && curMin == event.start_min) {
				SummonAll(i);  // Pass the event index

				CNPCProto* npcProto = gserver->m_npcProtoList.FindProto(event.npc_idx);

				CNetMsg::SP rmsg(new CNetMsg);
				std::string buffer = boost::str(boost::format("Event Summon started! Go kill %s to receive rewards. %d were summoned in random places.") % npcProto->m_name.GetBuffer() % event.npc_total);
				MsgrNoticeMsg(rmsg, -1, -1, -1, -1, buffer.c_str());
				SEND_Q(rmsg, gserver->m_messenger);

				// Mark event as active
				event.status = true;
				event.last_min = curMin;  // Reset last_min to the current minute for countdown notifications
			}
			else if (curDay == event.start_day && curHour == event.start_hour && curMin < event.start_min) {
				int min = event.start_min - curMin;
				if (min <= 10 && (curMin - event.last_min) >= 2) {  // Notify every 2 minutes
					CNetMsg::SP rmsg(new CNetMsg);
					std::string buffer = boost::str(boost::format("The Event Summon starts in %d minutes") % min);
					MsgrNoticeMsg(rmsg, -1, -1, -1, -1, buffer.c_str());
					SEND_Q(rmsg, gserver->m_messenger);
					event.last_min = curMin;  // Update last_min to the current minute
				}
			}
		}
	}
}//pwesty fix

void CEventSummon::SummonAll(int eventIndex) {//pwesty fix
	if (eventIndex < 0 || eventIndex >= m_events.size()) {
		// Log or handle invalid event index
		return;
	}

	CZone* pStartZone = gserver->FindZone(ZONE_START);

	if (!pStartZone || !pStartZone->m_area) {
		// Log or handle the error if the zone or area is not found
		return;
	}

	const auto& event = m_events[eventIndex];

	for (int i = 0; i < event.npc_total; i++) {
		float x = 0.0f;
		float z = 0.0f;
		bool validLocation = false;

		// Attempt to find a valid location
		while (!validLocation) {
			x = 750 + (GetRandom(0, 1) ? -1 : 1) * GetRandom(10, 1000);
			z = 750 + (GetRandom(0, 1) ? -1 : 1) * GetRandom(10, 1000);

			if (x < 0.1f || z < 0.1f) {
				continue;  // Skip invalid locations
			}

			unsigned short mapAttr = pStartZone->m_area->GetAttr(0, x, z);
			if (mapAttr & (MATT_WALKABLE | MATT_STAIR_UP | MATT_STAIR_DOWN)) {
				validLocation = true;  // Valid location found
			}
		}

		// Create and initialize NPC
		CNPC* pNPC = gserver->m_npcProtoList.Create(event.npc_idx, NULL);
		if (pNPC) {
			GET_X(pNPC) = x;
			GET_Z(pNPC) = z;
			GET_R(pNPC) = GetRandom(0, (int)(PI_2 * 10000)) / 10000;
			GET_YLAYER(pNPC) = 0;

			pNPC->m_regenX = GET_X(pNPC);
			pNPC->m_regenZ = GET_Z(pNPC);
			pNPC->m_regenY = GET_YLAYER(pNPC);

			pNPC->m_recoverPulse = gserver->m_pulse;

			pNPC->InitPointsToMax();
			pNPC->m_disableTime = 0;
			pNPC->m_postregendelay = 0;

			pStartZone->m_area->AddNPC(pNPC);

			int nCellX, nCellZ;
			pStartZone->m_area->PointToCellNum(GET_X(pNPC), GET_Z(pNPC), &nCellX, &nCellZ);
			pStartZone->m_area->CharToCell(pNPC, GET_YLAYER(pNPC), nCellX, nCellZ);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, pNPC, true);
				pStartZone->m_area->SendToCell(rmsg, GET_YLAYER(pNPC), nCellX, nCellZ);
			}

			pNPC->m_aipulse = gserver->m_pulse;
			pNPC->m_delay = PULSE_REAL_SEC * 2;
		}
	}

	// Set the event status to true after summoning NPCs
	m_events[eventIndex].status = true;
}



void CEventSummon::IncreaseDead(int eventIndex)
{
	if (eventIndex >= 0 && eventIndex < m_events.size()) {
		auto& event = m_events[eventIndex];

		if (event.npc_total > event.npc_total_dead) {
			event.npc_total_dead++;
		}
	}
}

void CEventSummon::ProcDrop(CPC* pc, CNPC* npc, int eventIndex) {
	// Validate the event index
	if (eventIndex < 0 || eventIndex >= m_events.size()) {
		LOG_ERROR("Invalid event index: %d", eventIndex);
		return;
	}

	auto& event = m_events[eventIndex];
	int totalLeft = event.npc_total - event.npc_total_dead;

	// Notify players about the remaining NPCs
	if (event.npc_total_dead < event.npc_total) {
		CNetMsg::SP rmsg(new CNetMsg);
		SysMsgEventSummonNpcDead(rmsg, pc ? pc->m_nick.GetBuffer() : "Unknown", totalLeft);
		PCManager::instance()->sendToAll(rmsg);
	}

	// Check if there are items to drop (from the main class, not EventData)
	if (m_items.empty() || m_items_count.empty()) return;

	// Generate random item drop probability
	int prob = GetRandom(1, 100);

	// Generate a random index for the item to drop
	int reward_idx = GetRandom(0, m_items.size() - 1);

	// Ensure reward_idx is within bounds
	if (reward_idx < 0 || reward_idx >= m_items.size()) {
		reward_idx = 0;  // Fallback to a valid index
	}

	LOG_INFO("DROP EVENT SUMMON ITEM: %d %d %d", reward_idx, m_items.size(), m_items_count.size());

	// Check if the random probability falls within the event probability
	if (prob <= m_prob) {  // Changed to <= for inclusion
		CItem* pItem = gserver->m_itemProtoList.CreateItem(m_items.at(reward_idx), -1, 0, 0, m_items_count.at(reward_idx));
		if (!pItem) return;

		// Set item preference index
		pItem->m_preferenceIndex = (pc) ? pc->m_index : -1;

		// Try to add item to the player's inventory
		if (pc) {
			if (!pc->m_inventory.addItem(pItem)) {
				// Drop item if inventory is full
				CNetMsg::SP rmsg(new CNetMsg);
				ItemDropMsg(rmsg, npc, pItem);
				npc->m_pArea->SendToCell(rmsg, GET_YLAYER(pItem), pItem->m_cellX, pItem->m_cellZ);
			}
		}
		else {
			// Handle the case where there's no player (e.g., drop item directly in the area)
			CNetMsg::SP rmsg(new CNetMsg);
			ItemDropMsg(rmsg, npc, pItem);
			npc->m_pArea->SendToCell(rmsg, GET_YLAYER(pItem), pItem->m_cellX, pItem->m_cellZ);
		}
	}
}




void CServer::ProcMonsterCombo()
{
	int i;
	for (i = 0; i < m_comboZone->m_countArea; ++i)
	{
		if (m_comboZone->m_area[i].m_bEnable)
			m_comboZone->m_area[i].RunComboZone();
	}

	CZone* pAkanZone = gserver->FindZone(ZONE_AKAN_TEMPLE);
	if (pAkanZone)
	{
		for (int i = 0; i < pAkanZone->m_countArea; i++)
		{
			if (pAkanZone->m_area[i].m_GroundEffect2.IsStarted())
			{
				pAkanZone->m_area[i].m_GroundEffect2.Activity();
			}
		}
	}

	CZone* pDungeon4 = gserver->FindZone(ZONE_DUNGEON4);
	if (pDungeon4)
	{
		for (int i = 0; i < pDungeon4->m_countArea; i++)
		{
			if (pDungeon4->m_area[i].m_GroundEffect2.IsStarted())
			{
				pDungeon4->m_area[i].m_GroundEffect2.Activity();
			}
		}
	}
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	CZone* pPartyDungeon0 = gserver->FindZone(ZONE_PARTY_DUNGEON0);
	if (pPartyDungeon0)
	{
		for (int i = 0; i < pPartyDungeon0->m_countArea; i++)
		{
			if (pPartyDungeon0->m_area[i].m_GroundEffect2.IsStarted())
			{
				pPartyDungeon0->m_area[i].m_GroundEffect2.Activity();
			}
		}
	}

	CZone* pPartyDungeon1 = gserver->FindZone(ZONE_PARTY_DUNGEON1);
	if (pPartyDungeon1)
	{
		for (int i = 0; i < pPartyDungeon1->m_countArea; i++)
		{
			if (pPartyDungeon1->m_area[i].m_GroundEffect2.IsStarted())
			{
				pPartyDungeon1->m_area[i].m_GroundEffect2.Activity();
			}
		}
	}

	CZone* pPartyDungeon2 = gserver->FindZone(ZONE_PARTY_DUNGEON2);
	if (pPartyDungeon2)
	{
		for (int i = 0; i < pPartyDungeon2->m_countArea; i++)
		{
			if (pPartyDungeon2->m_area[i].m_GroundEffect2.IsStarted())
			{
				pPartyDungeon2->m_area[i].m_GroundEffect2.Activity();
			}
		}
	}

	CZone* pPartyDungeon3 = gserver->FindZone(ZONE_PARTY_DUNGEON3);
	if (pPartyDungeon3)
	{
		for (int i = 0; i < pPartyDungeon3->m_countArea; i++)
		{
			if (pPartyDungeon3->m_area[i].m_GroundEffect2.IsStarted())
			{
				pPartyDungeon3->m_area[i].m_GroundEffect2.Activity();
			}
		}
	}

	CZone* pPartyDungeon4 = gserver->FindZone(ZONE_PARTY_DUNGEON4);
	if (pPartyDungeon4)
	{
		for (int i = 0; i < pPartyDungeon4->m_countArea; i++)
		{
			if (pPartyDungeon4->m_area[i].m_GroundEffect2.IsStarted())
			{
				pPartyDungeon4->m_area[i].m_GroundEffect2.Activity();
			}
		}
	}
#endif
}

void CServer::ProcEndExped()
{
	time_t t_now = time(NULL);

	//������ ��ü ó��
	map_listexped_t::iterator it = m_listExped.begin();
	map_listexped_t::iterator endit = m_listExped.end();
	for (; it != endit; ++it)
	{
		CExpedition* pExped = it->second;

		int nEndExpedStartTime = pExped->GetEndExpedTime();
		if (nEndExpedStartTime > 0)
		{
			//20 �ʰ� üũ
			if ((t_now - nEndExpedStartTime) >= 20)
			{
				//������ ��ü �޼��� ����
				if (gserver->isRunHelper())
				{
					CNetMsg::SP rmsg(new CNetMsg);
					HelperExpedEndExpedMsg(rmsg, pExped->GetBossIndex());
					SEND_Q(rmsg, gserver->m_helper);

					pExped->SetEndExpedTime(0);
				}
			}
		}
	}
}

void CServer::SendRewardGift(int user_id)
{
	int reward_idx = GetRandom(1, gserver->m_return_reward.size());
	CReturnReward* reward = gserver->getReturnReward(reward_idx);

	if (reward == NULL) {
		return;
	}

	if (gserver->isRunHelper())
	{
		LOG_INFO("Sending reward to [%d]", user_id);

		std::string query = boost::str(
			boost::format("INSERT INTO t_users_reward (a_user_id, a_reward_item_idx) VALUES ('%s',%d)") % user_id % reward_idx);

		CDBCmd dbcmd;
		dbcmd.Init(&m_dbauth);
		dbcmd.SetQuery(query);

		if (dbcmd.Update()) {

			query = boost::str(
				boost::format("INSERT INTO t_auto_give (a_char_index,a_item_index,a_item_count) VALUES (%d,%d,%d)")
				% user_id % reward->m_item_index % 1);

			dbcmd.Init(&m_dbchar);
			dbcmd.SetQuery(query);
			dbcmd.Update();
		}
	}
}

void CServer::ReturningReward()
{
	time_t tmNow;
	time(&tmNow);

	if (tmNow - m_tLastRewardCheck < TIME_ONE_HOUR)
		return;
	else {
		m_tLastRewardCheck = tmNow;
	}

	LOG_INFO("START REWARD CHECK");

	CDBCmd dbcmd;
	dbcmd.Init(&m_dbchar);

	std::string select_log = boost::str(
		boost::format("SELECT a_index FROM t_characters WHERE a_datestamp < DATE(NOW()) - INTERVAL 7 DAY"));
	dbcmd.SetQuery(select_log);

	if (!dbcmd.Open()) {
		return;
	}

	int user_index;
	int tmReceived = 0;
	int tmLastReceived = 0;
	CDBCmd dbReward;
	dbReward.Init(&m_dbauth);

	while (dbcmd.MoveNext()) {

		dbcmd.GetRec("a_index", user_index);


		std::string select_reward = boost::str(
			boost::format(
				"SELECT a_user_id, a_reward_item_idx, UNIX_TIMESTAMP(MAX(a_received)) as a_received "
				"FROM t_users_reward "
				"WHERE a_user_id = '%d' "
				"GROUP BY a_user_id, a_reward_item_idx "
				"ORDER BY a_received DESC"
			) % user_index
		);

		dbReward.SetQuery(select_reward);

		if (!dbReward.Open()) {
			return;
		}

		if (dbReward.MoveFirst()) {
			dbReward.GetRec("a_received", tmReceived);
			tmLastReceived = tmNow - tmReceived;
			//LOG_INFO("Time - %d %d %d %d", user_index, tmNow, tmReceived, tmLastReceived);
			if (tmLastReceived > TIME_ONE_WEEK * 2) {
				SendRewardGift(user_index);
			}
		}
		else {
			SendRewardGift(user_index);
		}
	}
}

void CServer::ProcEndParty()
{
	time_t t_now = time(NULL);

	//��Ƽ ��ü ó��
	map_listparty_t::iterator it = m_listParty.begin();
	map_listparty_t::iterator endit = m_listParty.end();
	for (; it != endit; ++it)
	{
		CParty* pParty = it->second;

		int nEndPartyStartTime = pParty->GetEndPartyTime();
		if (nEndPartyStartTime > 0)
		{
			//20 �ʰ� üũ
			if ((t_now - nEndPartyStartTime) >= 20)
			{
				//��Ƽ ��ü �޼��� ����
				if (gserver->isRunHelper())
				{
					CNetMsg::SP rmsg(new CNetMsg);
					HelperPartyEndPartyReqMsg(rmsg, pParty->GetBossIndex());
					SEND_Q(rmsg, gserver->m_helper);

					pParty->SetEndPartyTime(0);
				}
			}
		}
	}
}

void CServer::ProcTrigger()
{
	int i, j;

	for (i = 0; i < this->m_numZone; i++)
	{
		if (m_zones[i].m_bRemote)
			continue;
		for (j = 0; j < m_zones[i].m_countArea; j++)
		{
			// Ʈ���Ÿ� ����ϴ� Area�̸�
			if (m_zones[i].m_area[j].m_bEnable && m_zones[i].m_area[j].m_bUseTriggerEvent)
			{
				if (m_pulse - m_zones[i].m_area[j].m_pulseProcTrigger >= PULSE_TRIGGER_SYSTEM)
				{
					// Ÿ�̸� üũ�ϴ� �Լ� ���, hardcording �� ���� ó���ϱ�
					m_zones[i].m_area[j].m_pulseProcTrigger = m_pulse;
					m_zones[i].m_area[j].m_CTriggerList.TriggerTimerCheck();
				}
			}
		}
	}
}

/* �߰� ���...���߿� ���ε��� �߰��Ǹ� ���� ����*/
int	CServer::GetTriggerSetTypeToZoneIndex(int zoneIndex)
{
	int triggerSetType = 0;

	switch (zoneIndex)
	{
	case ZONE_EGEHA:
		triggerSetType = TRIGGERSET_EGEHA;
		break;

	case ZONE_STREIANA:
		triggerSetType = TRIGGERSET_STREIANA;
		break;

	case ZONE_MONDSHINE:
		triggerSetType = TRIGGERSET_MONDSHINE;
		break;

	case ZONE_CAPPELLA_1:
		triggerSetType = TRIGGERSET_CAPPELLA_1;
		break;

	case ZONE_CAPPELLA_2:
		triggerSetType = TRIGGERSET_CAPPELLA_2;
		break;

	case ZONE_ALTER_OF_DARK:
		triggerSetType = TRIGGERSET_ALTER_OF_DARK;
		break;

	case ZONE_AKAN_TEMPLE:
		break;
	case ZONE_TARIAN_DUNGEON:
		break;
	case ZONE_ENCHANTED_DUNGEON:
		break;
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	case ZONE_PARTY_DUNGEON0:
		triggerSetType = TRIGGERSET_PARTY_DUNGEON0;
		break;
	case ZONE_PARTY_DUNGEON1:
		triggerSetType = TRIGGERSET_PARTY_DUNGEON1;
		break;
	case ZONE_PARTY_DUNGEON2:
		triggerSetType = TRIGGERSET_PARTY_DUNGEON2;
		break;
	case ZONE_PARTY_DUNGEON3:
		triggerSetType = TRIGGERSET_PARTY_DUNGEON3;
		break;
	case ZONE_PARTY_DUNGEON4:
		triggerSetType = TRIGGERSET_PARTY_DUNGEON4;
		break;
#endif
	case 999:
		triggerSetType = TRIGGERSET_TESTRAID;
		break;

	default:
		break;
	}

	return triggerSetType;
}

CGrobalEcho::CGrobalEcho()
{
	for (int i = 0; i < MAX_GECHO_SIZE; i++)
	{
		checkClock[i] = 0;
		remainTime[i] = 0;
		repeatTime[i] = 1;
	}
}

int CGrobalEcho::FindIndex()
{
	int idx = 0;
	unsigned int min = remainTime[0];
	for (int i = 1; i < MAX_GECHO_SIZE; i++)
	{
		if (remainTime[i] < min)
		{
			min = remainTime[i];
			idx = i;
		}
	}
	return idx;
}

void CGrobalEcho::Set(CNetMsg::SP& _msg, unsigned int _repeatTime, unsigned int _time)
{
	int idx = FindIndex();
	msg[idx].reset();
	msg[idx] = _msg;
	repeatTime[idx] = _repeatTime * 60;		// �д����� �Է��ؼ� �ʷ� ��ȯ
	remainTime[idx] = _time * 60;			// �д����� �Է��ؿ� �ʷ� ��ȯ
}

void CGrobalEcho::Print()
{
	for (int idx = 0; idx < MAX_GECHO_SIZE; idx++)
	{
		if (remainTime[idx] > 0)
		{
			checkClock[idx]++;
			remainTime[idx]--;
			if (remainTime[idx] < 0)
				remainTime[idx] = 0;

			if (repeatTime[idx] < 1)
				repeatTime[idx] = 30;

			if (checkClock[idx] % repeatTime[idx] == 0)
			{
				SEND_Q(msg[idx], gserver->m_messenger);
				checkClock[idx] = 0;
			}
		}
	}
}
void CServer::SetDungeonTime()
{
	CDBCmd cmd;

	cmd.Init(&gserver->m_dbdata);
	std::string select_zonedata_query = "SELECT a_zone_index FROM t_zonedata";
	cmd.SetQuery(select_zonedata_query);
	if (!cmd.Open() || !cmd.MoveFirst())
		return;

	m_iZoneExp = new LONGLONG[cmd.GetRecordCount()];
	m_iZoneCount = cmd.GetRecordCount();

	for (int i = 0; i < cmd.GetRecordCount(); i++)
	{
		switch (i)
		{
		case ZONE_DUNGEON1:
		case ZONE_DUNGEON2:
		case ZONE_DUNGEON3:
		case ZONE_DUNGEON4:
		case ZONE_EGEHA_DUNGEON_1:
		case ZONE_EGEHA_DUNGEON_8:
		case ZONE_EGEHA_DUNGEON_9:
		case ZONE_EGEHA_DUNGEON_10:
		case ZONE_DRATAN_CASTLE_DUNGEON:
		case ZONE_SPRIT_CAVE:
		case ZONE_QUANIAN_CAVE:
		case ZONE_GOLEM_CAVE:
		case ZONE_FLORAIM_CAVE:
		case ZONE_TRIVIA_CANYON:
		case ZONE_MISTY_CANYON:
		case ZONE_DARK_TEOS:
		case ZONE_AWAKE_TEOS:
#if !defined (BILA_DUNGEON_TIME_EXP_CHANGE)
			m_iZoneExp[i] = 150;
#else
		case ZONE_EBONY_MINE:
			m_iZoneExp[i] = 150;
#endif // BILA_DUNGEON_TIME_EXP_CHANGE
			break;

		default:
			m_iZoneExp[i] = 100;
			break;
		}
	}

	// FILE OPEN �Ͽ��� ���õ� �� �о����.
	FILE* fDungeonTime = fopen(DUNGEON_TIME_SAVEFILE, "rt");
	if (fDungeonTime == NULL)
	{
		//�⺻ ���ð� ���Ͽ� ����.
		SaveDungeonTime(m_iZoneCount);
	}
	else
	{
		//�������尪 load.
		fclose(fDungeonTime);
		fDungeonTime = NULL;
		LoadDungeonTime(m_iZoneCount);
	}
	ModifyDungeonTime(0);
}

void CServer::SaveDungeonTime(int count)
{
	int i;
	FILE* fDungeonTime = fopen(DUNGEON_TIME_SAVEFILE, "wt");
	if (fDungeonTime)
	{
		fprintf(fDungeonTime, "%d\n", count);
		for (i = 0; i < count; i++)
		{
			fprintf(fDungeonTime, "%" PRId64 "\n", gserver->m_iZoneExp[i]);
		}
		for (i = 0; i < 24; i++)
		{
			if (gserver->m_bTimeTable[i] == false)
				fprintf(fDungeonTime, "0\n");
			else if (gserver->m_bTimeTable[i] == true)
				fprintf(fDungeonTime, "1\n");
		}
		fprintf(fDungeonTime, "%d\n", gserver->m_iTimeInterval);
		if (gserver->m_bDungeonTimeToggle == false)
			fprintf(fDungeonTime, "0\n");
		else if (gserver->m_bDungeonTimeToggle == true)
			fprintf(fDungeonTime, "1\n");
		fclose(fDungeonTime);
		fDungeonTime = NULL;
	}
}

void CServer::LoadDungeonTime(int count)
{
	int i;
	int iZoneCount;
	bool bLoadFail = false;
	LONGLONG* iExp = new LONGLONG[count]; // Dynamically allocated memory

	int iInterval;
	bool bTime[24];
	bool bStart;

	FILE* fDungeonTime = fopen(DUNGEON_TIME_SAVEFILE, "rt");
	if (fDungeonTime != NULL)
	{
		char tmpBuf[MAX_STRING_LENGTH] = { 0, };
		if (fgets(tmpBuf, 256, fDungeonTime) == NULL)			bLoadFail = true;
		else	iZoneCount = atoi(tmpBuf);

		if (iZoneCount < count)
		{
			LOG_ERROR("not equal DungeonTime. db[%d] config[%d]", count, iZoneCount);
			exit(1);
		}

		for (i = 0; i < count; i++)
		{
			if (fgets(tmpBuf, 256, fDungeonTime) == NULL)		bLoadFail = true;
			else	iExp[i] = (short int)atoi(tmpBuf);
		}

		for (i = 0; i < 24; i++)
		{
			if (fgets(tmpBuf, 256, fDungeonTime) == NULL)		bLoadFail = true;
			else
			{
				if (atoi(tmpBuf) == 0)
					bTime[i] = false;
				else if (atoi(tmpBuf) == 1)
					bTime[i] = true;
			}
		}

		if (fgets(tmpBuf, 256, fDungeonTime) == NULL)			bLoadFail = true;
		else	iInterval = (short int)atoi(tmpBuf);

		if (fgets(tmpBuf, 256, fDungeonTime) == NULL)			bLoadFail = true;
		else
		{
			if (atoi(tmpBuf) == 0)
				bStart = false;
			else if (atoi(tmpBuf) == 1)
				bStart = true;
		}

		if (bLoadFail == false)								// bLoadFail�� true �̸� �⺻ �������� ���д�.
		{
			for (i = 0; i < count; i++)
			{
				m_iZoneExp[i] = iExp[i];
			}

			for (i = 0; i < 24; i++)
			{
				m_bTimeTable[i] = bTime[i];
			}

			m_iTimeInterval = iInterval;
			m_bDungeonTimeToggle = bStart;
		}
	}
}


void CServer::saveHackCharacter(const char* idname, int charIndex)
{

	int userCode;
	CLCString nick(20 + 1);

	CDBCmd dbauth;
	dbauth.Init(&m_dbauth);
	std::string selectAcc = boost::str(boost::format("SELECT user_code FROM bg_user c WHERE user_id like '%s'") % idname);
	dbauth.SetQuery(selectAcc.c_str());
	if (dbauth.Open()) {
		dbauth.MoveFirst();
		dbauth.GetRec("user_code", userCode);
	}

	if (charIndex) {
		CDBCmd dbcmd;
		dbcmd.Init(&m_dbchar);
		std::string selectCharacter = boost::str(boost::format("SELECT a_nick FROM t_characters WHERE a_index = %d") % charIndex);
		dbcmd.SetQuery(selectCharacter.c_str());
		if (dbcmd.Open()) {
			dbcmd.MoveFirst();
			dbcmd.GetRec("a_nick", nick, true);
		}

		LOG_INFO("SAVE HACK %d %s %d %s", userCode, idname, charIndex, nick.GetBuffer());

		CDBCmd DB_cmd1;
		DB_cmd1.Init(&m_dbchar);
		std::string sqlhack = boost::str(boost::format("insert into t_hack_characters (a_user_idx, a_user_id, a_char_idx, a_char_id, a_time, a_hacktype, a_delay) values (%d, '%s', %d, '%s', NOW(), '%s', %f)")
			% userCode % idname % charIndex % (const char*)nick % "Hack Speed Attack" % 0.0);
		DB_cmd1.SetQuery(sqlhack.c_str());
		DB_cmd1.Update();
	}
}

void CServer::LoadRewardItem()
{
	LOG_INFO("LOAD REWARD ITEM");

	CDBCmd dbcmd;
	dbcmd.Init(&m_dbauth);
	std::string select = boost::str(boost::format("SELECT a_index, a_item_idx, a_catalog_idx FROM t_users_reward_item"));
	dbcmd.SetQuery(select);

	if (!dbcmd.Open()) {
		return;
	}

	m_return_reward.clear();
	while (dbcmd.MoveNext()) {

		CReturnReward* reward = new CReturnReward();

		dbcmd.GetRec("a_index", reward->m_index);
		dbcmd.GetRec("a_item_idx", reward->m_item_index);
		dbcmd.GetRec("a_catalog_idx", reward->m_catalog_index);

		m_return_reward.push_back(reward);
	}
}



void CServer::CheckUpdateRanking()
{
	LOG_INFO("Check Update Ranking");
	if (gserver->m_subno == WAR_GROUND_CHANNEL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_SUBHELPER_COMMAND);
		RefMsg(rmsg) << MSG_SUBHELPER_RANKING_EX_REFRESH;
		SEND_Q(rmsg, gserver->m_subHelper);
		LOG_INFO("RANK REFRESH > Begin update");
	}
}

void CServer::CheckAutomaticEventTime()
{
	// Check every 6th hour  = event time (bool)
	// If (event time in for loop ) 
}

void CServer::CheckDungeonTime()
{
	LOG_INFO("DUNGEON TIME > RealSystemTime.Hour : %d and TimeTable : %d", m_tRealSystemTime.tm_hour, m_bTimeTable[m_tRealSystemTime.tm_hour] ? 1 : 0);
	for (int i = 0; i < 24; i++)
	{
		LOG_INFO("DUNGEON TIME > TimeTableList : %d and TimeTableRealDate : %d", m_bTimeTable[i] ? 1 : 0, m_bTimeTable[i]);
	}

	if (m_bTimeTable[m_tRealSystemTime.tm_hour])  // old = if(m_bTimeTable[m_tRealSystemTime.tm_hour] == true) pwesty
	{
		m_iStartTime = m_tRealSystemTime.tm_hour;
		m_iEndTime = m_iStartTime + m_iTimeInterval;

		if (m_iEndTime > 23)
			m_iEndTime = m_iEndTime - 24;

		int exp = 100;
		for (int i = 0; i < gserver->m_iZoneCount; i++)
		{
			if (gserver->m_iZoneExp[i] > 100)
			{
				exp = gserver->m_iZoneExp[i] - 100;
				break;
			}
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			DungeonTimeNoticeMsg(rmsg, MSG_EX_DUNGEONTIME_START, m_iStartTime, m_iEndTime, exp);
			PCManager::instance()->sendToAll(rmsg);
		}

		m_bIsTime = true;
		LOG_INFO("DUNGEON TIME START > StartTime : %d and EndTime : %d and Interval : %d", m_iStartTime, m_iEndTime, m_iTimeInterval);
		return;
	}
	else if (m_tRealSystemTime.tm_hour == m_iEndTime)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		DungeonTimeNoticeMsg(rmsg, MSG_EX_DUNGEONTIME_END, -1, -1, -1);
		LOG_INFO("DUNGEON TIME END > StartTime : %d and EndTime : %d and Interval : %d", m_iStartTime, m_iEndTime, m_iTimeInterval);
		PCManager::instance()->sendToAll(rmsg);
		m_bIsTime = false;
		return;
	}

}
void CServer::ModifyDungeonTime(int flag)
{
	int iStart = -1;
	int iEnd = -1;
	bool bTime = m_bIsTime;
	int nowtime = -1;

	nowtime = m_tRealSystemTime.tm_hour;

	for (int i = 23; i >= 0; i--)
	{
		if (m_bTimeTable[i] == true && i <= nowtime)
		{
			iStart = i;
			break;
		}
	}
	if (iStart == -1)
	{
		for (int i = 23; i >= 0; i--)
		{
			if (m_bTimeTable[i] == true)
			{
				iStart = i;
				break;
			}
		}
	}

	iEnd = iStart + m_iTimeInterval;
	m_iStartTime = iStart;
	m_iEndTime = iEnd;
	if (iEnd > 23)
	{
		iEnd -= 24;
		if (nowtime >= iStart || nowtime < iEnd)
		{
			//������ ����Ÿ��!!!
			//false���� true�� �ٲ�� ����!!!
			int exp = 100;
			for (int i = 0; i < gserver->m_iZoneCount; i++)
			{
				if (gserver->m_iZoneExp[i] > 100)
				{
					exp = gserver->m_iZoneExp[i] - 100;
					break;
				}
			}
			m_bIsTime = true;
			if (bTime == false)
			{
				if (gserver->m_bDungeonTimeToggle == true)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					DungeonTimeNoticeMsg(rmsg, MSG_EX_DUNGEONTIME_START, m_iStartTime, m_iEndTime, exp);
					PCManager::instance()->sendToAll(rmsg);
					GAMELOG << init("DUNGEON TIME") << "START" << end;
				}
			}
			if (flag == 1)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				DungeonTimeNoticeMsg(rmsg, MSG_EX_DUNGEONTIME_START, m_iStartTime, m_iEndTime, exp);
				PCManager::instance()->sendToAll(rmsg);
				GAMELOG << init("DUNGEON TIME") << "START" << end;
			}
			if (flag == 2)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				DungeonTimeNoticeMsg(rmsg, MSG_EX_DUNGEONTIME_END, -1, -1, -1);
				PCManager::instance()->sendToAll(rmsg);
				GAMELOG << init("DUNGEON TIME") << "END" << end;
			}
		}
		else
		{
			// ������ ���� Ÿ��
			// true���� false�� �ٲ������ ���� ����!!
			m_bIsTime = false;
			if (bTime == true)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				DungeonTimeNoticeMsg(rmsg, MSG_EX_DUNGEONTIME_END, -1, -1, -1);
				PCManager::instance()->sendToAll(rmsg);
				GAMELOG << init("DUNGEON TIME") << "END" << end;
			}
		}
	}
	else
	{
		if (iStart <= nowtime && iEnd > nowtime)
		{
			// ������ ���� Ÿ��!!!
			// false ���� true �� �ٲ�� ����!!!
			int exp = 100;
			for (int i = 0; i < gserver->m_iZoneCount; i++)
			{
				if (gserver->m_iZoneExp[i] > 100)
				{
					exp = gserver->m_iZoneExp[i] - 100;
					break;
				}
			}
			m_bIsTime = true;
			if (bTime == false)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				DungeonTimeNoticeMsg(rmsg, MSG_EX_DUNGEONTIME_START, m_iStartTime, m_iEndTime, exp);
				PCManager::instance()->sendToAll(rmsg);
			}
			if (flag == 1)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				DungeonTimeNoticeMsg(rmsg, MSG_EX_DUNGEONTIME_START, m_iStartTime, m_iEndTime, exp);
				PCManager::instance()->sendToAll(rmsg);
			}
			if (flag == 2)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				DungeonTimeNoticeMsg(rmsg, MSG_EX_DUNGEONTIME_END, -1, -1, -1);
				PCManager::instance()->sendToAll(rmsg);
			}
		}
		else
		{
			// ������ ���� Ÿ��
			// true���� false�� �ٲ�� ����!!!
			m_bIsTime = false;
			if (bTime == true)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				DungeonTimeNoticeMsg(rmsg, MSG_EX_DUNGEONTIME_END, -1, -1, -1);
				PCManager::instance()->sendToAll(rmsg);
			}
		}
	}
}

#ifdef BATTLE_PASS_SYSTEM
void CServer::CloudCheckBattlePassReset()
{
	//if(this->m_tRealSystemTime.tm_wday == 0 // Week Day 0~6 if want week reset
	if (this->m_tRealSystemTime.tm_mday == 28 //Month Day 1~31
		&& this->m_tRealSystemTime.tm_hour == 0 //Hour
		&& this->m_tRealSystemTime.tm_min == 0 //min
		&& (this->m_tRealSystemTime.tm_sec == 0 || this->m_tRealSystemTime.tm_sec == 1 || this->m_tRealSystemTime.tm_sec == 2 || this->m_tRealSystemTime.tm_sec == 3))//seconds
	{
		if (gserver->BattlePassResetProcess == false)
		{
			int season = 0;//Cloud add Season
			CBattlePass* bp = FindBattlePassByLevel(1);
			if (bp)
			{
				season = bp->m_season;
			}


			{
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_EXTEND);
				RefMsg(rmsg) << MSG_EX_STRING
					<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
					<< 8539//string idx
					<< 1//arg1
					<< 1//type int
					<< season;//int data1
				PCManager::instance()->sendToAll(rmsg);
			}
			ResetBattlePass();
			gserver->BattlePassResetProcess = true;
		}
	}

	//if(this->m_tRealSystemTime.tm_wday == 0 // Week Day 0~6 if want week reset
	if (this->m_tRealSystemTime.tm_mday == 27 //Month Day 1~31
		&& this->m_tRealSystemTime.tm_hour == 23) //Hour //min
	{
		if (this->m_tRealSystemTime.tm_min == 0 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{

			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 60;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 10 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 50;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 20 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 40;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}
		if (this->m_tRealSystemTime.tm_min == 30 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 30;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}
		if (this->m_tRealSystemTime.tm_min == 40 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 20;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 50 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 10;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 55 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 5;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 56 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 4;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 57 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 3;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 58 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 2;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 59 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 1;//int data1
			PCManager::instance()->sendToAll(rmsg);
			gserver->BattlePassResetProcess = false;
		}
	}
}
#endif
#ifdef PRESTIGE_SYSTEM
void CServer::CloudCheckPrestigeReset()
{
	//if(this->m_tRealSystemTime.tm_wday == 0 // Week Day 0~6 if want week reset
	if (this->m_tRealSystemTime.tm_mday == 28 //Month Day 1~31
		&& this->m_tRealSystemTime.tm_hour == 0 //Hour
		&& this->m_tRealSystemTime.tm_min == 0 //min
		&& (this->m_tRealSystemTime.tm_sec == 0 || this->m_tRealSystemTime.tm_sec == 1 || this->m_tRealSystemTime.tm_sec == 2 || this->m_tRealSystemTime.tm_sec == 3))//seconds
	{
		if (gserver->PrestigeResetProcess == false)
		{
			int season = 0;//Cloud add Season
			CPrestige* bp = FindPrestigeByLevel(1);
			if (bp)
			{
				season = bp->m_season;
			}


			{
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_EXTEND);
				RefMsg(rmsg) << MSG_EX_STRING
					<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
					<< 8539//string idx
					<< 1//arg1
					<< 1//type int
					<< season;//int data1
				PCManager::instance()->sendToAll(rmsg);
			}
			ResetPrestige();
			gserver->PrestigeResetProcess = true;
		}
	}

	//if(this->m_tRealSystemTime.tm_wday == 0 // Week Day 0~6 if want week reset
	if (this->m_tRealSystemTime.tm_mday == 27 //Month Day 1~31
		&& this->m_tRealSystemTime.tm_hour == 23) //Hour //min
	{
		if (this->m_tRealSystemTime.tm_min == 0 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{

			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 60;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 10 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 50;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 20 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 40;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}
		if (this->m_tRealSystemTime.tm_min == 30 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 30;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}
		if (this->m_tRealSystemTime.tm_min == 40 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 20;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 50 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 10;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 55 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 5;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 56 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 4;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 57 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 3;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 58 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 2;//int data1
			PCManager::instance()->sendToAll(rmsg);
		}

		if (this->m_tRealSystemTime.tm_min == 59 && this->m_tRealSystemTime.tm_sec == 0)//seconds
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_STRING
				<< (unsigned char)MSG_EX_STRING_OUTPUT_SYS
				<< 8540//string idx
				<< 1//arg1
				<< 1//type int
				<< 1;//int data1
			PCManager::instance()->sendToAll(rmsg);
			gserver->PrestigeResetProcess = false;
		}
	}
}
#endif
void CServer::CheckRaidReset()
{
	if (this->m_subno != RAID_SUBNUMBER)
	{
		return;
	}

	if ((this->m_nResetDay != 7) &&
		(this->m_tRealSystemTime.tm_wday != this->m_nResetDay) &&
		(this->m_tRaidResetProcess == 0))
	{
		return;
	}

	if (m_tRaidResetProcess == 0)
	{
		if (this->m_tRealSystemTime.tm_hour == this->m_nResethr &&
			this->m_tRealSystemTime.tm_min == this->m_nResetmin)
		{
			m_tRaidResetProcess = mktime(&m_tRealSystemTime);
			// ù��° ���� ����
			// (5 - m_nProcess)
			GAMELOG << init("RAID AUTO RESET REMAIN") << (5 - m_nProcess) << end;
			CNetMsg::SP rmsg(new CNetMsg);
			SysRaidZoneRemain(rmsg, (5 - m_nProcess));

			PCManager::instance()->sendToAll(rmsg);
			// ù��° ���� ��
			m_tRaidResetProcess += 60;
			m_nProcess++;
			m_bIsCheckTime = true;
		}
		else
			return;
	}
	else
	{
		if (mktime(&m_tRealSystemTime) >= m_tRaidResetProcess)
		{
			// 1~n�� ����
			if (m_nProcess <= 5)
			{
				//(5 - m_nProcess)
				if ((5 - m_nProcess) == 0)
				{
					GAMELOG << init("NO ENTER RAID ZONE") << end;
					CNetMsg::SP rmsg(new CNetMsg);
					SysMsg(rmsg, MSG_SYS_NO_ENTER_RAID_ZONE);

					PCManager::instance()->sendToAll(rmsg);
					m_bCanEnterTheRaidDungeon = false;
				}
				else
				{
					GAMELOG << init("RAID AUTO RESET REMAIN") << (5 - m_nProcess) << end;
					CNetMsg::SP rmsg(new CNetMsg);
					SysRaidZoneRemain(rmsg, (5 - m_nProcess));
					PCManager::instance()->sendToAll(rmsg);
				}
			}

			if (m_nProcess == 6)
			{
				// �ʱ�ȭ
				GAMELOG << init("START RAID RESET") << end;
				ResetRaid();
			}

			if (m_nProcess == 10)
			{
				// �����������
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg(rmsg, MSG_SYS_RAID_RESET_COMPLETE);
				PCManager::instance()->sendToAll(rmsg);
				GAMELOG << init("END RAID RESET") << end;
				// ������� ��
				m_bCanEnterTheRaidDungeon = true;
				m_bIsCheckTime = false;
				m_tRaidResetProcess = 0;
				m_nProcess = 0;
			}

			if (m_bIsCheckTime == true)
			{
				m_tRaidResetProcess += 60;
				m_nProcess++;
			}
		}
	}
}
void CServer::ResetRaid()
{
	int i, j;
	int AreaArrayIndex = 0;
	for (i = 0; i < this->m_numZone; i++)
	{
		int Area[MAX_AREA_COUNT][2] = { {-1,}, };
		if (m_zones[i].m_bRemote)
			continue;
		else
		{
			if (m_zones[i].IsExpedRaidZone())
			{
				for (j = 0; j < m_zones[i].m_countArea; j++)
				{
					if (m_zones[i].m_area[j].m_bEnable)
					{
						Area[AreaArrayIndex][0] = m_zones[i].m_area[j].m_nRaidRoomNo;
						Area[AreaArrayIndex][1] = m_zones[i].m_area[j].m_RaidDifficulty;
						AreaArrayIndex++;
					}
				}
				// ���� ���⼭ �޽����� ����� Helper�� ������.
				// ������ ����. ���� ��û �޽��� << AreaArrayIndex << zoneNo. << roomNo. << diffyculty
				// ����!!! ���� ������ �����ϰ� �ٸ� �͵��� �����ؾ��Ѵ�!!!!
				{
					CNetMsg::SP rmsg(new CNetMsg);
					HelperAutoResetRaid(rmsg, AreaArrayIndex, m_zones[i].m_index, Area);
					SEND_Q(rmsg, gserver->m_helper);
				}
			}
		}
	}
}

#ifdef NEW_DOUBLE_GM_AUTO
void CServer::SwapDoubleEventValue()
{
	int swap;

	swap = m_bDoubleNasPercent;
	m_bDoubleNasPercent = m_bDoubleNasPercentBackup;
	m_bDoubleNasPercentBackup = swap;

	swap = m_bDoubleNasGetPercent;
	m_bDoubleNasGetPercent = m_bDoubleNasGetPercentBackup;
	m_bDoubleNasGetPercentBackup = swap;

	swap = m_bDoubleExpPercent;
	m_bDoubleExpPercent = m_bDoubleExpPercentBackup;
	m_bDoubleExpPercentBackup = swap;

	swap = m_bDoubleSpPercent;
	m_bDoubleSpPercent = m_bDoubleSpPercentBackup;
	m_bDoubleSpPercentBackup = swap;

	swap = m_bDoubleProducePercent;
	m_bDoubleProducePercent = m_bDoubleProducePercentBackup;
	m_bDoubleProducePercentBackup = swap;

	swap = m_bDoubleProduceNum;
	m_bDoubleProduceNum = m_bDoubleProduceNumBackup;
	m_bDoubleProduceNumBackup = swap;
}
#endif

void CServer::CheckEventTime()
{
	time_t curtime;
	curtime = mktime(&m_tRealSystemTime);
#if defined (NEW_DOUBLE_GM_AUTO) || defined (NEW_DOUBLE_EVENT_AUTO_TIME) || defined (EVENT_ITEMDROP_AUTO) || defined (GM_EXP_LIMIT_AUTO)
	bool bBoolean;
	time_t starttime;
	time_t endtime;
	struct tm tStart;
	struct tm tEnd;
#endif

#ifdef DOUBLE_PET_EXP_AUTO
	if (curtime >= gserver->m_tPetExpEventStart && curtime < gserver->m_tPetExpEventEnd)
	{
		if (gserver->m_bDoublePetExpEvent == false)
		{
			GAMELOG << init("PET_EVENT_START") << "prob" << delim << gserver->m_PetExpPercent << end;
		}
		gserver->m_bDoublePetExpEvent = true;
	}
	else
	{
		if (gserver->m_bDoublePetExpEvent == true)
		{
			GAMELOG << init("PET_EVENT_END") << end;
		}
		gserver->m_bDoublePetExpEvent = false;
	}
#endif
#ifdef UPGRADE_EVENT_AUTO
	if (curtime >= gserver->m_tUpgradeEventStart && curtime < gserver->m_tUpgradeEventEnd)
	{
		// �̺�Ʈ �ð���.
		if (g_bUpgradeEvent == false)
		{
			GAMELOG << init("UPGRADE_EVENT_START") << "prob" << delim << g_nUpgradeProb << end;
			CNetMsg::SP rmsg(new CNetMsg);
			EventEnchantRate(rmsg, 1, g_nUpgradeProb);
			PCManager::instance()->sendToAll(rmsg);
		}
		g_bUpgradeEvent = true;
	}
	else
	{
		if (g_bUpgradeEvent == true)
		{
			GAMELOG << init("UPGRADE_EVENT_END") << end;
			CNetMsg::SP rmsg(new CNetMsg);
			EventEnchantRate(rmsg, 0, g_nUpgradeProb);
			PCManager::instance()->sendToAll(rmsg);
		}
		g_bUpgradeEvent = false;
	}
#endif // UPGRADE_EVENT_AUTO

#ifdef GM_EXP_LIMIT_AUTO
	memset(&tStart, 0x00, sizeof(tStart));
	memset(&tEnd, 0x00, sizeof(tEnd));

	bBoolean = m_bExpLimit;
	tStart.tm_year = m_nGMExpLimitStart[0] - 1900;
	tStart.tm_mon = m_nGMExpLimitStart[1] - 1;
	tStart.tm_mday = m_nGMExpLimitStart[2];
	tStart.tm_hour = m_nGMExpLimitStart[3];
	tStart.tm_min = m_nGMExpLimitStart[4];
	tStart.tm_sec = m_nGMExpLimitStart[5];
	tStart.tm_isdst = -1;
	starttime = mktime(&tStart);

	tEnd.tm_year = m_nGMExpLimitEnd[0] - 1900;
	tEnd.tm_mon = m_nGMExpLimitEnd[1] - 1;
	tEnd.tm_mday = m_nGMExpLimitEnd[2];
	tEnd.tm_hour = m_nGMExpLimitEnd[3];
	tEnd.tm_min = m_nGMExpLimitEnd[4];
	tEnd.tm_sec = m_nGMExpLimitEnd[5];
	tEnd.tm_isdst = -1;
	endtime = mktime(&tEnd);

	if (curtime >= starttime && curtime < endtime)
	{
		// �̺�Ʈ �ð���.
		m_bExpLimit = true;
		if (bBoolean == false)
		{
			m_nExpLimit = m_nExpLimitStart;
			m_nSpLimit = m_nSpLimitStart;
			GAMELOG << init("EXP SP LIMIT SET") << "EXP LIMIT VALUE" << delim << m_nExpLimit << delim << "SP LIMIT VALUE" << delim << m_nSpLimit << end;
		}
	}
	else
	{
		// �̺�Ʈ �ð��� �ƴ�.
		m_bExpLimit = false;
		if (bBoolean == true)
		{
			m_nExpLimit = m_nExpLimitEnd;
			m_nSpLimit = m_nSpLimitEnd;
			GAMELOG << init("EXP SP LIMIT SET") << "EXP LIMIT VALUE" << delim << m_nExpLimit << delim << "SP LIMIT VALUE" << delim << m_nSpLimit << end;
		}
	}
#endif //GM_EXP_LIMIT_AUTO
#ifdef EVENT_ITEMDROP_AUTO
	memset(&tStart, 0x00, sizeof(tStart));
	memset(&tEnd, 0x00, sizeof(tEnd));

	bBoolean = m_bIsItemdrop;
	tStart.tm_year = m_iEventItemdropStart[0] - 1900;
	tStart.tm_mon = m_iEventItemdropStart[1] - 1;
	tStart.tm_mday = m_iEventItemdropStart[2];
	tStart.tm_hour = m_iEventItemdropStart[3];
	tStart.tm_min = m_iEventItemdropStart[4];
	tStart.tm_sec = m_iEventItemdropStart[5];
	tStart.tm_isdst = -1;
	starttime = mktime(&tStart);

	tEnd.tm_year = m_iEventItemdropEnd[0] - 1900;
	tEnd.tm_mon = m_iEventItemdropEnd[1] - 1;
	tEnd.tm_mday = m_iEventItemdropEnd[2];
	tEnd.tm_hour = m_iEventItemdropEnd[3];
	tEnd.tm_min = m_iEventItemdropEnd[4];
	tEnd.tm_sec = m_iEventItemdropEnd[5];
	tEnd.tm_isdst = -1;
	endtime = mktime(&tEnd);

	if (curtime >= starttime && curtime < endtime)
	{
		// �̺�Ʈ �ð���.
		m_bIsItemdrop = true;
		if (bBoolean == false)
		{
			//SwapEventItemdropValue();
			gserver->m_nItemDropEventRate = gserver->m_nItemDropEventRateBackup;
			GAMELOG << init("Event ItemDrop Start") << "RATE" << delim << gserver->m_nItemDropEventRate << end;
		}
	}
	else
	{
		// �̺�Ʈ �ð��� �ƴ�.
		m_bIsItemdrop = false;
		gserver->m_nItemDropEventRate = 100;
		if (bBoolean == true)
		{
			GAMELOG << init("Event ItemDrop End") << "RATE" << delim << gserver->m_nItemDropEventRate << end;
		}
	}
#endif // EVENT_ITEMDROP_AUTO
#ifdef NEW_DOUBLE_GM_AUTO
	memset(&tStart, 0x00, sizeof(tStart));
	memset(&tEnd, 0x00, sizeof(tEnd));

	bBoolean = m_bIsDEtime;
	tStart.tm_year = m_iDoubleGMStart[0] - 1900;
	tStart.tm_mon = m_iDoubleGMStart[1] - 1;
	tStart.tm_mday = m_iDoubleGMStart[2];
	tStart.tm_hour = m_iDoubleGMStart[3];
	tStart.tm_min = m_iDoubleGMStart[4];
	tStart.tm_sec = m_iDoubleGMStart[5];
	tStart.tm_isdst = -1;
	starttime = mktime(&tStart);

	tEnd.tm_year = m_iDoubleGMEnd[0] - 1900;
	tEnd.tm_mon = m_iDoubleGMEnd[1] - 1;
	tEnd.tm_mday = m_iDoubleGMEnd[2];
	tEnd.tm_hour = m_iDoubleGMEnd[3];
	tEnd.tm_min = m_iDoubleGMEnd[4];
	tEnd.tm_sec = m_iDoubleGMEnd[5];
	tEnd.tm_isdst = -1;
	endtime = mktime(&tEnd);

	if (curtime >= starttime && curtime < endtime)
	{
		// �̺�Ʈ �ð�
		m_bIsDEtime = true;
		if (bBoolean == false)
		{
			//swap
			SwapDoubleEventValue();
			GAMELOG << init("Double Event Time Start")
				<< "NAS PERCENT : " << m_bDoubleNasPercent
				<< " NAS GET PERCENT : " << m_bDoubleNasGetPercent
				<< " EXP PERCENT : " << m_bDoubleExpPercent
				<< " SP PERCENT : " << m_bDoubleSpPercent
				<< " PRODUCE PERCENT : " << m_bDoubleProducePercent
				<< " PRODUCE NUM : " << m_bDoubleProduceNum << end;
		}
	}
	else
	{
		// �̺�Ʈ �ð� �ƴ�.
		m_bIsDEtime = false;
		if (bBoolean == true)
		{
			//swap
			SwapDoubleEventValue();

			GAMELOG << init("Double Event Time End")
				<< "NAS PERCENT : " << m_bDoubleNasPercent
				<< " NAS GET PERCENT : " << m_bDoubleNasGetPercent
				<< " EXP PERCENT : " << m_bDoubleExpPercent
				<< " SP PERCENT : " << m_bDoubleSpPercent
				<< " PRODUCE PERCENT : " << m_bDoubleProducePercent
				<< " PRODUCE NUM : " << m_bDoubleProduceNum << end;
		}
	}
#endif
#ifdef NEW_DOUBLE_EVENT_AUTO_TIME
	memset(&tStart, 0x00, sizeof(tStart));
	memset(&tEnd, 0x00, sizeof(tEnd));

	bBoolean = gserver->m_bDoubleEventAuto;
	tStart.tm_year = m_iDoubleEventStart[0] - 1900;
	tStart.tm_mon = m_iDoubleEventStart[1] - 1;
	tStart.tm_mday = m_iDoubleEventStart[2];
	tStart.tm_hour = m_iDoubleEventStart[3];
	tStart.tm_min = m_iDoubleEventStart[4];
	tStart.tm_sec = m_iDoubleEventStart[5];
	tStart.tm_isdst = -1;

	tEnd.tm_year = m_iDoubleEventEnd[0] - 1900;
	tEnd.tm_mon = m_iDoubleEventEnd[1] - 1;
	tEnd.tm_mday = m_iDoubleEventEnd[2];
	tEnd.tm_hour = m_iDoubleEventEnd[3];
	tEnd.tm_min = m_iDoubleEventEnd[4];
	tEnd.tm_sec = m_iDoubleEventEnd[5];
	tEnd.tm_isdst = -1;

	starttime = mktime(&tStart);
	endtime = mktime(&tEnd);

	if (curtime >= starttime && curtime < endtime)
	{
		gserver->m_bDoubleEventAuto = true;
		gserver->NewDoubleEventAuto();
		if (bBoolean == false)
		{
			// ����Ǿ��ٴ� ���ӷα�
			GAMELOG << init("Combo Double Event Auto Reservation Time") << "Start" << end;
		}
	}
	else
	{
		gserver->m_bDoubleEventAuto = false;
		gserver->m_bDoubleEventAutoOn = false;
		if (bBoolean == true)
		{
			// ����Ǿ��ٴ� ���ӷα�
			GAMELOG << init("Combo Double Event Auto Reservation Time") << "End" << end;
		}
	}
#endif // NEW_DOUBLE_EVENT_AUTO_TIME
	return;
}

#ifdef XTRAP
bool CServer::InitXTrap()
{
	LOG_INFO("Init XTrap");

	FILE* fp = fopen("data/map1.CS3", "rb");
	if (fp == NULL)
	{
		LOG_ERROR("data/map1.CS3 open error.");
		return false;
	}
	fread(m_XTrapMap[0], XTRAP_CS4_BUFSIZE_MAP, 1, fp);
	fclose(fp);

	LOG_INFO("Map XTrap loaded");

	if (XTrap_S_LoadDll() != XTRAP_API_RETURN_OK)
	{
		LOG_ERROR("XTrap_S_LoadDll() error.");
		return false;
	}

	LOG_INFO("DLL XTrap loaded");

	unsigned int ret = XTrap_S_SetAllowDelay(XTRAP_ALLOW_DELAY_2);
	if (ret != 0)
	{
		LOG_ERROR("XTrap_S_SetAllowDelay(XTRAP_ALLOW_DELAY_2) error.");
		return false;
	}

	LOG_INFO("Delay XTrap set");

	XTrap_S_Start(600, 2, m_XTrapMap, NULL);

	LOG_INFO("XTrap Started");

	return true;
}
#endif //XTRAP

int CServer::GetCastllanZoneZum(int charIndex)
{
	if (charIndex == CDratanCastle::CreateInstance()->GetOwnerCharIndex())
	{
		return CDratanCastle::CreateInstance()->GetZoneIndex();
	}
	return -1;
}

bool IsApllyDebuffSkilltoNPC(CPC* aPc, CNPC* tNpc)
{
	if (!tNpc->Check_MobFlag(STATE_MONSTER_MERCENARY))
		return true;

	if (tNpc->GetOwner())
	{
		CPC* pTpc = tNpc->GetOwner();
		if (pTpc == aPc)
			return false;

		if (!(IsRaList(pTpc, aPc) || IsRaList(aPc, pTpc)))
			return false;
	}

	return true;
}

#ifdef SYSTEM_TREASURE_MAP
void CServer::writeTreasureMapSaveFile()
{
	FILE* fp = fopen(GM_TREASURE_MAP_SAVE_FILE, "wt");
	if (fp)
	{
		fprintf(fp, "%d\n", (gserver->bTreasureMapLinkZoneDrop ? 1 : 0));

		int i;
		for (i = 0; i < gserver->m_numZone; i++)
		{
			CZone* pZone = gserver->m_zones + i;
			if (!pZone)
				continue;
			if (!pZone->IsTreasureDropZone())
				continue;

			fprintf(fp, "%d\n", pZone->m_index);
			fprintf(fp, "%d\n", (pZone->CheckTreasureDropFlag() ? 1 : 0));
		}

		fclose(fp);
		fp = NULL;
	}
}

void CServer::readTreasureMapSaveFile()
{
	FILE* fp = fopen(GM_TREASURE_MAP_SAVE_FILE, "rt");

	if (fp)
	{
		char tmpBuf[MAX_STRING_LENGTH] = { 0, };
		if (fgets(tmpBuf, 8, fp) == NULL)
			return;
		gserver->bTreasureMapLinkZoneDrop = (atoi(tmpBuf) ? true : false);

		while (1)
		{
			if (fgets(tmpBuf, 8, fp) == NULL)
				return;
			int zone = atoi(tmpBuf);

			if (fgets(tmpBuf, 8, fp) == NULL)
				return;
			int bDrop = atoi(tmpBuf);

			CZone* pZone = gserver->FindZone(zone);
			if (pZone == NULL)
				continue;

			if (!pZone->IsTreasureDropZone())
				continue;

			if (bDrop)
				pZone->SetTreasureDropFlag();
			else
				pZone->ResetTreasureDropFlag();
		}

		fclose(fp);
		fp = NULL;

		GAMELOG << init("SYSTEM")
			<< "TREASUREMAP SAVE FILE READ SUC"
			<< end;

		return;
	}

	GAMELOG << init("SYSTEM")
		<< "TREASUREMAP SAVE FILE READ FAIL"
		<< end;
}
#endif

#ifdef REFORM_PK_PENALTY_201108 // ���ÿ� �ѹ� ���� ���� ��ġ ������ �ִ� �÷��̾�� pk ���� ����Ʈ ���� ����������Ѵ�.
void CServer::CheckPkDisPosiotionPointReward()
{
	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator iter = playerMap.begin();
	PCManager::map_t::iterator endIter = playerMap.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc == NULL)
		{
			continue;
		}

		if (0 < pc->m_assist.m_avAddition.pkDispositionPointValue)
		{
			pc->AddPkPenalty(pc->m_assist.m_avAddition.pkDispositionPointValue);

			CNetMsg::SP rmsg(new CNetMsg);
			CharStatusMsg(rmsg, pc, 0);
			pc->m_pArea->SendToCell(rmsg, pc, false);
		}
	}
}

#endif

void CServer::CheckDratanCastleDungeonReward()
{
	for (int i = 0; i < gserver->m_DratanCheckTime; i++)
	{
		if (m_dratanCastleEnvCheck[i] == false)
		{
			return;
		}
		m_dratanCastleEnvCheck[i] = false;
	}

	CDratanCastle* pCastle = CDratanCastle::CreateInstance();
	ExpressSystemItemInfo* iteminfo = new ExpressSystemItemInfo;
	iteminfo->item_index = 10014;
	iteminfo->item_count = 1;
	iteminfo->send_type = EXPRESS_SEND_TYPE_ETC;
	memcpy(iteminfo->sender, "Dratan", sizeof(iteminfo->sender));
	DBManager::instance()->PushExpressInputItemNotConnectUser(pCastle->GetOwnerCharIndex(), iteminfo, false);
}

#ifdef DEV_EVENT_AUTO
void CEventKingsBirthdayRewardItem::giveRewardItem(CPC* pc, int giveCount)
{
	if (pc == NULL)
		return;

	CItem* pGiveItem = gserver->m_itemProtoList.CreateItem(getItemIndex(), -1, 0, 0, giveCount);
	if (pGiveItem == NULL)
		return;

	if (pc->m_inventory.addItem(pGiveItem) == false)
	{
		GAMELOG << init("NO ADD TO INVENTORY Heart Reward Item You Must Recovery!!", pc) << itemlog(pGiveItem) << end;

		delete pGiveItem;

		return;
	}
}

void CEventKingsBirthdayFlagReward::giveFlagRewardItem(CPC* pc)
{
	if (pc == NULL)
		return;

	CEventKingsBirthdayRewardItem* rewardItem = getFlagRewardItem(pc->m_job);
	if (!rewardItem)
		return;

	CItem* pGiveItem = gserver->m_itemProtoList.CreateItem(rewardItem->getItemIndex(), -1, 0, 0, 1);
	if (pGiveItem == NULL)
		return;

	if (pc->m_inventory.addItem(pGiveItem) == false)
	{
		GAMELOG << init("NO ADD TO INVENTORY Flag Reward Item You Must Recovery!!", pc) << itemlog(pGiveItem) << end;

		delete pGiveItem;

		return;
	}
}
CItem* CEventKingsBirthdayDropItemManager::getItem(int prob)
{
	CItem* pItem = NULL;
	int isProb = 0;
	//for(int i = 0; i < getDropItemCount(); i++)
	//{
	//	isProb = isProb + m_DropItem[i].getDropItemProb();
	//	if(isProb >= prob)
	//	{
	//		// drop
	//		pItem = gserver->m_itemProtoList.CreateItem(m_DropItem[i].getDropItemIndex(), -1, 0, 0, m_DropItem[i].getDropItemCount());
	//		break;
	//	}
	//}
	std::vector<CKingsBirthdayDropItem*>::const_iterator cit;
	std::vector<CKingsBirthdayDropItem*>::const_iterator citEnd = m_DropItem.end();
	CKingsBirthdayDropItem* pDropitem = NULL;
	for (cit = m_DropItem.begin(); cit != citEnd; cit++)
	{
		pDropitem = *cit;
		isProb = isProb + pDropitem->getDropItemProb();
		if (isProb >= prob)
		{
			// drop
			pItem = gserver->m_itemProtoList.CreateItem(pDropitem->getDropItemIndex(), -1, 0, 0, pDropitem->getDropItemCount());
			break;
		}
	}
	return pItem;
}
void CEventKingsBirthdayDropItemManager::deleteDropItem(CPC* pc)
{
	if (pc == NULL)
		return;

	int dropItemCount = getDropItemCount();
	for (int i = 0; i < dropItemCount; i++)
	{
		if (getDropItem(i) == NULL)
			continue;

		if (strcmp(getDropItem(i)->getType(), "Heart") != 0)
			continue;

		CItem* pItem = pc->m_inventory.FindByDBIndex(getDropItem(i)->getDropItemIndex(), 0, 0);
		if (pItem == NULL)
			continue;

		GAMELOG << init("FathersDay Delete Item(Exchange)", pc) << itemlog(pItem) << end;

		pc->m_inventory.decreaseItemCount(pItem, 1);
	}
}
void CEventKingsBirthdayDropItemManager::deleteFlagItem(CPC* pc)
{
	if (pc == NULL)
		return;

	int dropItemCount = getDropItemCount();
	for (int i = 0; i < dropItemCount; i++)
	{
		if (getDropItem(i) == NULL)
			continue;

		if (strcmp(getDropItem(i)->getType(), "Flag") != 0)
			continue;

		CItem* pItem = pc->m_inventory.FindByDBIndex(getDropItem(i)->getDropItemIndex(), 0, 0);
		if (pItem == NULL)
			continue;

		GAMELOG << init("FathersDay Delete Item(Exchange)", pc) << itemlog(pItem) << end;

		pc->m_inventory.decreaseItemCount(pItem, 1);
	}
}

void CEventKingsBirthdayFlagReward::setFlagReward(CConfigFile& eventConfig)
{
	setCount(atoi(eventConfig.Find("TLD_KB_FLAG_REWARDS", "Count")));
	if (getCount())
	{
		CLCString grouptag;
		int count = getCount();

		for (int i = 0; i < count; i++)
		{
			CEventKingsBirthdayRewardItem* pReward = new CEventKingsBirthdayRewardItem;
			grouptag.Format("TLD_KB_FLAG_REWARD_%d", i);
			pReward->setItemIndex(atoi(eventConfig.Find(grouptag, "FlagRewardIndex")));
			m_flagReward.push_back(pReward);
		}
	}
}

CEventKingsBirthdayRewardItem* CEventKingsBirthdayFlagReward::getFlagRewardItem(int job)
{
	//if(job < 0 || job >= getCount())
	//	job = 0;
	////if(m_flagReward)
	//return m_flagReward[job];
	if (m_flagReward.size())
	{
		if (job < 0 || job >= getCount())
			job = 0;
		std::vector<CEventKingsBirthdayRewardItem*>::const_iterator cit;
		cit = m_flagReward.begin();
		cit = cit + job;
		return *cit;
	}
	else
		return NULL;
}

void CEventKingsBirthdayDropItemManager::setDropItem(CConfigFile& eventConfig)
{
	setDropItemCount(atoi(eventConfig.Find("TLD_KB_DROP_ITEMS", "Count")));
	if (getDropItemCount())
	{
		//m_DropItem = new CKingsBirthdayDropItem[getDropItemCount()];
		CLCString grouptag;
		int dropItemCount = getDropItemCount();
		for (int i = 0; i < dropItemCount; i++)
		{
			CKingsBirthdayDropItem* pDropItem = new CKingsBirthdayDropItem;
			grouptag.Format("TLD_KB_DROP_ITEM_%d", i);
			pDropItem->setDropItemIndex(atoi(eventConfig.Find(grouptag, "Index")));
			pDropItem->setDropCount(atoi(eventConfig.Find(grouptag, "Count")));
			pDropItem->setDropProb(atoi(eventConfig.Find(grouptag, "Prob")));
			pDropItem->setPoint(atoi(eventConfig.Find(grouptag, "Point")));
			pDropItem->setType(eventConfig.Find(grouptag, "Type"));
			m_DropItem.push_back(pDropItem);
			//m_DropItem[i].setDropItemIndex(atoi(eventConfig.Find(grouptag, "Index")));
			//m_DropItem[i].setDropCount(atoi(eventConfig.Find(grouptag, "Count")));
			//m_DropItem[i].setDropProb(atoi(eventConfig.Find(grouptag, "Prob")));
			//m_DropItem[i].setPoint(atoi(eventConfig.Find(grouptag, "Point")));
			//m_DropItem[i].setType(eventConfig.Find(grouptag, "Type"));
		}
	}
}

CKingsBirthdayDropItem* CEventKingsBirthdayDropItemManager::getDropItem(int arrayIndex)
{
	//	if(arrayIndex < 0 || arrayIndex >= getDropItemCount())
	//		arrayIndex = 0;
	////		if(m_DropItem)
	//	return m_DropItem[arrayIndex];

	if (arrayIndex < 0 || arrayIndex >= getDropItemCount())
		return NULL;

	if (m_DropItem.size())
	{
		std::vector<CKingsBirthdayDropItem*>::const_iterator cit;
		cit = m_DropItem.begin();
		cit = cit + arrayIndex;
		return *cit;
	}
	else
		return NULL;
}

int CEventKingsBirthdayDropItemManager::calcPoint(CPC* pc)
{
	if (pc == NULL)
		return 0;

	int allPoint = 0;
	int dropItemCount = getDropItemCount();
	for (int i = 0; i < dropItemCount; i++)
	{
		if (getDropItem(i) == NULL)
			continue;

		if (strcmp(getDropItem(i)->getType(), "Heart") != 0)
			continue;

		item_search_t vec;
		int sc = pc->m_inventory.searchItemByCondition(getDropItem(i)->getDropItemIndex(), 0, 0, vec);
		if (sc == 0)
			continue;

		allPoint += sc * getDropItem(i)->getPoint();
	}

	return allPoint;
}

void CEventKingsBirthdayDropProbTable::setProbTable(CConfigFile& eventConfig)
{
	setCount(atoi(eventConfig.Find("TLD_KB_DROP_PROBS", "Count")));
	CLCString grouptag;
	if (getCount())
	{
		//m_levelSection = new CLevelSection[getCount()];
		int count = getCount();
		for (int i = 0; i < count; i++)
		{
			CLevelSection* plevel = new CLevelSection;
			grouptag.Format("TLD_KB_DROP_PROB_%d", i);
			plevel->setMinLevel(atoi(eventConfig.Find(grouptag, "Min")));
			plevel->setMaxLevel(atoi(eventConfig.Find(grouptag, "Max")));
			plevel->setProb(atoi(eventConfig.Find(grouptag, "Prob")));
			m_levelSection.push_back(plevel);
		}
	}
	setFirstPriority(atoi(eventConfig.Find("TLD_KB_DROP_PROB_MULTIPLICATION", "MBOSS_BOSS_RAID_NPC")));
	setSecondPriority(atoi(eventConfig.Find("TLD_KB_DROP_PROB_MULTIPLICATION", "PARTY_NPC")));
}

int CEventKingsBirthdayDropProbTable::getProb(CNPC* npc)
{
	int prob = 0;
	//for(int i = 0; i < getCount(); i++)
	//{
	//	if(m_levelSection[i].getMinLevel() <= npc->m_level && m_levelSection[i].getMaxLevel() >= npc->m_level)
	//	{
	//		prob = m_levelSection[i].getProb();
	//		break;
	//	}
	//}
	std::vector<CLevelSection*>::const_iterator cit;
	std::vector<CLevelSection*>::const_iterator citEnd = m_levelSection.end();
	CLevelSection* plevel = NULL;
	for (cit = m_levelSection.begin(); cit != citEnd; cit++)
	{
		plevel = *cit;
		if (plevel->getMinLevel() <= npc->m_level && plevel->getMaxLevel() >= npc->m_level)
		{
			prob = plevel->getProb();
			break;
		}
	}

	if (npc->m_proto->CheckFlag(NPC_MBOSS | NPC_BOSS | NPC_RAID))
	{
		prob = prob * m_firstPriority;
	}
	else if (npc->m_proto->CheckFlag(NPC_PARTY))
	{
		prob = prob * m_secondPriority;
	}

	return prob;
}

void CEventKingsBirthday::Load(CConfigFile& eventConfig)
{
	LoadDropItemManager(eventConfig);
	LoadHeartItem(eventConfig);
	LoadFlagItem(eventConfig);
	LoadItemDropProbTable(eventConfig);
	if (atoi(eventConfig.Find("TLD_EVENT_ENABLE", "Enable")) == 1)
	{
		setEventStart(true);
	}
	else
	{
		setEventStart(false);
	}
	if (atoi(eventConfig.Find("TLD_EVENT_ENABLE", "EventItemDelete")) == 1)
	{
		setEventDeleteItem(true);
	}
	else
	{
		setEventDeleteItem(false);
	}
}

void CItemDropEvent::Load(CConfigFile& eventConfig)
{
	LoadItemDropManager(eventConfig);
	LoadDropProbTable(eventConfig);
	if (atoi(eventConfig.Find("KOKO_EVENT", "Enable")) == 1)
	{
		setEnable(true);
	}
	else
	{
		setEnable(false);
	}
}

void CItemDropEvent::LoadItemDropManager(CConfigFile& eventConfig)
{
	m_DropItemManager.Load(eventConfig);
}
void CItemDropEvent::LoadDropProbTable(CConfigFile& eventConfig)
{
	m_DropProbTable.Load(eventConfig);
}
void CDropProbTable::Load(CConfigFile& eventConfig)
{
	CLCString grouptag;
	setLevelSectionCount(atoi(eventConfig.Find("KOKO_DROP_PROBS", "Count")));
	if (getLevelSectionCount())
	{
		int levelSectionCount = getLevelSectionCount();
		for (int i = 0; i < levelSectionCount; i++)
		{
			grouptag.Format("KOKO_DROP_PROB_%d", i);
			CLevelSection* pLevel = new CLevelSection;
			pLevel->setMinLevel(atoi(eventConfig.Find(grouptag, "Min")));
			pLevel->setMaxLevel(atoi(eventConfig.Find(grouptag, "Max")));
			pLevel->setProb(atoi(eventConfig.Find(grouptag, "Prob")));
			m_levelSection.push_back(pLevel);
		}
		setUnderLevel(atoi(eventConfig.Find("KOKO_DROP_PROB_MULTIPLICATION", "UNDER_LEVEL")));
		setUpperLevel(atoi(eventConfig.Find("KOKO_DROP_PROB_MULTIPLICATION", "UP_LEVEL")));
		setDivision(atoi(eventConfig.Find("KOKO_DROP_PROB_MULTIPLICATION", "DIVISION")));
		setMultiple(atoi(eventConfig.Find("KOKO_DROP_PROB_MULTIPLICATION", "MULTIPLE")));
		//setFirstPriority(atoi(eventConfig.Find("KOKO_DROP_PROB_MULTIPLICATION","MBOSS_BOSS_RAID_NPC")));
		//setSecondPriority(atoi(eventConfig.Find("KOKO_DROP_PROB_MULTIPLICATION","PARTY_NPC")));
	}

	setZoneCount(atoi(eventConfig.Find("ZONES_MULTIPLE", "Count")));
	if (getZoneCount())
	{
		int zoneCount = getZoneCount();;
		for (int i = 0; i < zoneCount; i++)
		{
			grouptag.Format("ZONE_%d", i);
			CZoneDropProb* pDrop = new CZoneDropProb;
			pDrop->setZoneIndex(atoi(eventConfig.Find(grouptag, "Zindex")));
			pDrop->setMultiple(atoi(eventConfig.Find(grouptag, "Multiple")));
			m_zoneDropProb.push_back(pDrop);
		}
	}
}
void CDropItemManager::Load(CConfigFile& eventConfig)
{
	CLCString grouptag;
	setCount(atoi(eventConfig.Find("KOKO_DROP_ITEMS", "Count")));
	if (getCount())
	{
		int count = getCount();
		for (int i = 0; i < count; i++)
		{
			grouptag.Format("KOKO_DROP_ITEM_%d", i);
			CDropItem* pDropItem = new CDropItem;
			pDropItem->setItemIndex(atoi(eventConfig.Find(grouptag, "Index")));
			pDropItem->setDropCount(atoi(eventConfig.Find(grouptag, "Count")));
			m_DropItem.push_back(pDropItem);
		}
	}
}

int CDropProbTable::getProb(CPC* pc, CNPC* npc)
{
	int prob = 0;
	std::vector<CLevelSection*>::const_iterator cit;
	std::vector<CLevelSection*>::const_iterator citEnd = m_levelSection.end();
	CLevelSection* plevel = NULL;
	for (cit = m_levelSection.begin(); cit != citEnd; cit++)
	{
		plevel = *cit;
		if (plevel->getMinLevel() <= npc->m_level && plevel->getMaxLevel() >= npc->m_level)
		{
			prob = plevel->getProb();
			break;
		}
	}

	if ((pc->m_level - npc->m_level) >= getUnderLevel())
	{
		prob = prob / getDivision();
	}
	else if ((npc->m_level - pc->m_level) >= getUpperLevel())
	{
		prob = prob * getMultiple();
	}
	if (m_zoneDropProb.size())
	{
		CZoneDropProb* pProb;
		std::vector<CZoneDropProb*>::const_iterator cit;
		std::vector<CZoneDropProb*>::const_iterator citEnd = m_zoneDropProb.end();
		for (cit = m_zoneDropProb.begin(); cit != citEnd; cit++)
		{
			pProb = *cit;
			if (pc->m_pZone->m_index == pProb->getZoneIndex())
			{
				prob = prob * pProb->getMultiple();
				break;
			}
		}
	}

	//if(npc->m_proto->CheckFlag(NPC_MBOSS | NPC_BOSS | NPC_RAID))
	//{ prob = prob * m_firstPriority; }
	//else if(npc->m_proto->CheckFlag(NPC_PARTY))
	//{ prob = prob * m_secondPriority; }

	return prob;
}
CItem* CDropItemManager::getItem()
{
	CItem* pItem = NULL;
	if (m_DropItem.size())
	{
		CDropItem* pDropItem = NULL;
		std::vector<CDropItem*>::const_iterator cit;
		cit = m_DropItem.begin();
		pDropItem = *cit;
		pItem = gserver->m_itemProtoList.CreateItem(pDropItem->getIetmIndex(), -1, 0, 0, pDropItem->getDropCount());
	}
	return pItem;
}
#endif

void CServer::addNotice(int _pos, int _index)
{
	if (_pos < 0 || _pos >= 5)
	{
		GAMELOG << init("NOTICE ADD OVER") << "count : " << _pos << delim << "index : " << _index << end;
		return;
	}

	if (m_aNotice[_pos] != 0)
		return;

	m_aNotice[_pos] = _index;
}

bool CServer::removeActiveEvent(int _eventIndex, bool _dbUpdate)
{
	if (!m_eventAutomationMgr.removeActiveEvent(_eventIndex, _dbUpdate))
		return false;

	//�̺�Ʈ�� ���� �̺�Ʈ �̸� �ش� �������� ��� ����
	if (_eventIndex == EVENT_ARTIFACT)
	{
		ArtifactManager::instance()->eventOff();
	}

	// ������� �˻��ؼ� �ش� npc�� �����ұ�? �Ѥ�;;
	CEventInfo* eInfo = getEventInfo(_eventIndex);
	if (!eInfo)
		return false;

	CNPC* npc = NULL;
	int i = 0, j = 0;
	for (i = 0; i < m_numZone; i++)
	{
#if defined( SYSTEM_TREASURE_MAP )
		if (!m_zones[i].IsFieldZone())
			continue;
#endif //SYSTEM_TREASURE_MAP

		for (j = 0; j < m_zones[i].m_countArea; j++)
		{
			CArea* pArea = &m_zones[i].m_area[j];

			if (!pArea->m_bEnable)
				continue;

			CNPC* next;
			next = pArea->m_npcList;
			while ((npc = next))
			{
				next = npc->m_pNPCNext;

				if (eInfo->isEventNpc(npc->m_idNum))
				{
					GAMELOG << init("Event NPC Delete")
						<< "EVENT INDEX : " << _eventIndex << delim
						<< "NPC DB INDEX : " << npc->m_idNum << end;
					npc->SendDisappearAllInCell(true);
					DelAttackList(npc);
					pArea->CharFromCell(npc, true);
					pArea->DelNPC(npc);
				}
			}
		}
	}
	return true;
}

void CServer::doEventDropItem(CNPC* npc, CPC* pc, CPC* tpc)
{
	if (tpc == NULL || pc == NULL || npc == NULL)
		return;

	CPC* pPc = pc;
	if (pc != tpc)
		pPc = tpc;

	if (pPc->m_pZone->IsPersonalDungeon())
		return;

	if (m_eventAutomationMgr.getActiveEventCount() == 0)
		return;

	std::map<int, CEventInfo*>* activeList = m_eventAutomationMgr.getActiveEvenList();
	std::map<int, CEventInfo*>::iterator itr;
	std::map<int, CEventInfo*>::iterator itrEnd = activeList->end();

	for (itr = activeList->begin(); itr != itrEnd; itr++)
	{
		if (itr->second->getDropCount() == 0)
			continue;

		int i = 0;
		int dropCount = itr->second->getDropCount();
		for (i = 0; i < dropCount; i++)
			m_dropItemMgr.doDrop(pPc, npc, itr->second->getDropIndex(i));
	}
}

bool CServer::GetOutDratanDungeon(CPC* pc)
{
	// ������ ���� ���̰�, �̵��Ϸ��� ���� ���ź ���� ����(�׿��� ����)�̸�, ���ź���� ������.
	// Return Value
	// true : ������, false : �Ⱥ�����
	if (CDratanCastle::CreateInstance()->GetState() != WCSF_NORMAL)
	{
		if (pc->m_pZone->m_index == ZONE_DRATAN_CASTLE_DUNGEON)
		{
			int extra = 0;
			CZone* pZone = gserver->FindZone(ZONE_DRATAN);
			if (pZone == NULL)
				return false;

			pc->m_pZone = pZone;
			pc->m_pArea = pZone->m_area;

			GET_YLAYER(pc) = pZone->m_zonePos[extra][0];
			GET_R(pc) = 0.0f;
			GET_X(pc) = GetRandom(pZone->m_zonePos[extra][1], pZone->m_zonePos[extra][3]) / 2.0f;
			GET_Z(pc) = GetRandom(pZone->m_zonePos[extra][2], pZone->m_zonePos[extra][4]) / 2.0f;

			{
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeGoMsg(rmsg, pc);
				SEND_Q(rmsg, pc->m_desc);
			}

			return true;
		}
	}

	return false;
}

void CServer::ClearMobAISeq(void)
{
	m_mobAISeq = 0;
	memset(&m_mobAIArea, 0, sizeof(int) * PASSES_PER_SEC);
	memset(&m_mobAIMobCnt, 0, sizeof(int) * PASSES_PER_SEC);
}

int CServer::AddMobAISeq(int regenCnt)
{
	int min = 2147483647, minseq = 0;
	int i;

	for (i = 0; i < PASSES_PER_SEC; i++)
	{
		if (m_mobAIMobCnt[i] < min)
		{
			min = m_mobAIMobCnt[i];
			minseq = i;
		}
	}

	m_mobAIArea[minseq]++;
	m_mobAIMobCnt[minseq] += regenCnt;

	if (m_mobAIMobCnt[minseq] < 0)
		m_mobAIMobCnt[minseq] = 2147483647;

	//m_mobAIArea[minseq]++;
	//m_mobAIMobCnt[minseq] = 2147483647;

	return minseq;
}

void CServer::RemoveMobAISeq(int minseq, int regenCnt)
{
	if (minseq < 0 || minseq >= PASSES_PER_SEC)
		return;

	m_mobAIArea[minseq]--;
	m_mobAIMobCnt[minseq] -= regenCnt;

	if (m_mobAIMobCnt[minseq] < 0)
		m_mobAIMobCnt[minseq] = 0;
}

void CServer::operate(rnSocketIOService* service)
{
	CDescriptor* newd = new CDescriptor(service);
	newd->m_seq_index = ++local_seq_index;
	newd->m_connect_time = gserver->m_nowseconds;
	service->SetUserData(newd);
	service->setCrypt();

	rnSocketIOServiceTcp* pTcp = reinterpret_cast<rnSocketIOServiceTcp*>(service);
	pTcp->setCheckSequence();

	STATE(newd) = CON_GET_LOGIN;

	newd->m_index = local_dummy_user_index;

	--local_dummy_user_index;
	if (local_dummy_user_index > 0)
		local_dummy_user_index = 0;
}

void CServer::NpcCtTimeCount()
{
	std::map<int, CNPC*>::iterator it = gserver->m_npc_ctTime.begin();
	std::map<int, CNPC*>::iterator endit = gserver->m_npc_ctTime.end();

	for (; it != endit; ++it)
	{
		if ((it->second)->m_ctTime > 0)
		{
			--it->second->m_ctTime;
		}
		else
		{
			--it->second->m_ctTime = IMMUN_SKILL_MCT_TIME;
			if ((it->second)->m_ctCount > 0)
				(it->second)->m_ctCount--;
			else
			{
				gserver->m_npc_ctTime_erase.push_back(it->first);
			}
		}
	}

	std::vector<int>::iterator it_e = gserver->m_npc_ctTime_erase.begin();
	std::vector<int>::iterator endit_e = gserver->m_npc_ctTime_erase.end();

	for (; it_e != endit_e; ++it_e)
	{
		gserver->m_npc_ctTime.erase(*it_e);
	}
	gserver->m_npc_ctTime_erase.clear();
}

void CServer::CheckDratanCastleDungeon(int num)
{
	CDratanCastle* pCastle = CDratanCastle::CreateInstance();
	if (pCastle->m_dvd.GetOwnerMode() == true)
	{
		if (pCastle->m_dvd.GetEnvRate() >= 90 && pCastle->m_dvd.GetMobRate() >= 90)
		{
			m_dratanCastleEnvCheck[num] = true;
		}
		else
		{
			m_dratanCastleEnvCheck[num] = false;
		}
	}
	else
	{
		m_dratanCastleEnvCheck[num] = false;
	}
}

#ifdef TLD_EVENT_SONG
void CServer::checkTldEvent()
{
	time_t nowtime = ::time(0);
	struct tm ttm;
	memcpy(&ttm, localtime(&nowtime), sizeof(ttm));

	switch (ttm.tm_hour)
	{
	case 16:
	case 17:
	case 20:
	case 21:
		tld_event = true;
		break;

	default:
		tld_event = false;
		break;
	}
}
#endif

bool CServer::LoadPetConfig()
{

	std::string query("SELECT a_pet_exp, a_apet_exp, a_exp_booster, a_apet_exp_limit FROM t_pet_config");
	CDBCmd cmd;
	cmd.Init(&m_dbdata);
	cmd.SetQuery(query.c_str());

	if (!cmd.Open() || !cmd.MoveFirst())
		return false;

	cmd.GetRec("a_pet_exp", m_petConfig.pet_exp);
	cmd.GetRec("a_apet_exp", m_petConfig.apet_exp);
	cmd.GetRec("a_exp_booster", m_petConfig.exp_booster);
	cmd.GetRec("a_apet_exp_limit", m_petConfig.apet_exp_limit);

	LOG_INFO("PET CONFIG LOAD: %d %d %d", m_petConfig.pet_exp, m_petConfig.apet_exp, m_petConfig.exp_booster);

	return true;
}

bool CServer::LoadServerConfig()
{
	GAMELOG << init("LOAD SERVER CONFIG") << end;

	std::string query("SELECT a_max_exp, a_max_sp, a_max_gold, a_max_gold_boss, a_min_ep_level, a_ep_factor, a_rvr_points, a_min_exp_level, a_prob_broken_hs, a_prob_plus_hs, a_prob_minus_hs, a_safe_hs FROM t_server_config");
	CDBCmd cmd;
	cmd.Init(&m_dbdata);
	cmd.SetQuery(query.c_str());

	if (!cmd.Open() || !cmd.MoveFirst())
		return false;

	cmd.GetRec("a_max_exp", m_serverConfig.max_exp);
	cmd.GetRec("a_max_sp", m_serverConfig.max_sp);
	cmd.GetRec("a_max_gold", m_serverConfig.max_gold);
	cmd.GetRec("a_max_gold_boss", m_serverConfig.max_gold_boss);
	cmd.GetRec("a_min_ep_level", m_serverConfig.min_ep_level);
	cmd.GetRec("a_ep_factor", m_serverConfig.ep_factor);
	cmd.GetRec("a_rvr_points", m_serverConfig.rvr_points);
	cmd.GetRec("a_min_exp_level", m_serverConfig.min_exp_level);
	GAMELOG << init("SERVER CONFIG INFO ")
		<< m_serverConfig.max_exp << " < "
		<< m_serverConfig.max_sp << " < "
		<< m_serverConfig.max_gold << " < "
		<< m_serverConfig.max_gold_boss << " < "
		<< m_serverConfig.min_ep_level << " < "
		<< m_serverConfig.ep_factor << " < "
		<< m_serverConfig.rvr_points << " < "
		<< m_serverConfig.min_exp_level << " < "
		<< end;

	return true;
}

bool CServer::LoadOXReward()
{
	m_rewardOXQuiz.clear();

	std::string query("SELECT a_quiz_index, a_item_index, a_item_count FROM t_oxquiz_reward");
	CDBCmd cmd;
	cmd.Init(&m_dbdata);
	cmd.SetQuery(query.c_str());

	if (!cmd.Open())
		return false;

	while (cmd.MoveNext()) {

		OXReward* reward = new OXReward();

		cmd.GetRec("a_quiz_index", reward->quiz_idx);
		cmd.GetRec("a_item_index", reward->item_idx);
		cmd.GetRec("a_item_count", reward->item_count);

		m_rewardOXQuiz.push_back(reward);
	}

	return true;
}

OXReward* CServer::FindOXReward(int index)
{
	for (int i = 0; i < m_rewardOXQuiz.size(); i++) {
		if (m_rewardOXQuiz[i]->quiz_idx == index) {
			return m_rewardOXQuiz[i];
		}
	}
	return NULL;
}

void CServer::gm_list_init()
{
	set_gmlist.insert(std::set<std::string>::value_type("echo"));
	set_gmlist.insert(std::set<std::string>::value_type("silence"));
	set_gmlist.insert(std::set<std::string>::value_type("doubleexp_event"));
	set_gmlist.insert(std::set<std::string>::value_type("upgrade_event"));
	set_gmlist.insert(std::set<std::string>::value_type("event"));
	set_gmlist.insert(std::set<std::string>::value_type("automationevent"));
	set_gmlist.insert(std::set<std::string>::value_type("jewelrye"));
	set_gmlist.insert(std::set<std::string>::value_type("double_event"));
	set_gmlist.insert(std::set<std::string>::value_type("godbless"));
	set_gmlist.insert(std::set<std::string>::value_type("reload_job_damage"));
	set_gmlist.insert(std::set<std::string>::value_type("battle_warfare"));
}

#ifdef BATTLE_PASS_SYSTEM
CBattlePass::CBattlePass()
{

}

CBattlePass::~CBattlePass()
{

}


bool CBattlePass::LoadReward()
{
	gserver->m_listBattleItems.clear();
	CDBCmd dbcmd;
	dbcmd.Init(&gserver->m_dbdata);

	std::string query = boost::str(
		boost::format("SELECT * FROM t_battle_pass_reward order by a_index asc"));
	dbcmd.SetQuery(query);

	if (!dbcmd.Open() || !dbcmd.MoveFirst()) {
		return false;
	}

	do {

		BATTLE_PASS_REWARD* reward = new BATTLE_PASS_REWARD();

		dbcmd.GetRec("a_item_idx", reward->item_index);
		dbcmd.GetRec("a_item_count", reward->item_count);
		dbcmd.GetRec("a_premium_item_idx", reward->premium_item_index);
		dbcmd.GetRec("a_premium_item_count", reward->premium_item_count);

		gserver->m_listBattleItems.push_back(reward);

	} while (dbcmd.MoveNext());

	return true;
}

CBattlePass* CServer::FindBattlePassByLevel(int level)
{
	if (level == 0)
		level = 1;

	//map_battle_pass_t::iterator it = gserver->m_listBattlePass.begin();
	//map_battle_pass_t::iterator endit = gserver->m_listBattlePass.end();
	for (int i = 0; i < gserver->m_listBattlePass.size(); i++)
	{
		CBattlePass* battlePass = gserver->m_listBattlePass[i];
		if (battlePass && battlePass->m_level == level)
			return battlePass;
	}
	return NULL;
}

bool CServer::LoadBattlePass()
{
	m_listBattlePass.clear();

	CDBCmd dbcmd;
	dbcmd.Init(&gserver->m_dbdata);

	// Order by level, skip placeholder levels
	std::string select =
		"SELECT * FROM t_battle_pass "
		"WHERE a_level > 0 "
		"ORDER BY a_level ASC";
	dbcmd.SetQuery(select);

	if (!dbcmd.Open() || !dbcmd.MoveFirst()) {
		return false;
	}

	do {
		CBattlePass* battlePass = new CBattlePass();

		dbcmd.GetRec("a_index", battlePass->m_index);
		dbcmd.GetRec("a_name", battlePass->m_name);
		dbcmd.GetRec("a_points", battlePass->m_points);
		dbcmd.GetRec("a_premium_points", battlePass->m_premium_points);
		dbcmd.GetRec("a_level", battlePass->m_level);
		dbcmd.GetRec("a_season", battlePass->m_season);

		// Load the reward for this battle pass
		m_listBattlePass.push_back(battlePass);

	} while (dbcmd.MoveNext());

	// Load rewards once after all battle pass levels are loaded
	if (!m_listBattlePass.empty())
		m_listBattlePass[0]->LoadReward();

	LOG_INFO("Loaded %zu battle pass levels.", m_listBattlePass.size());
	return true;
}


#endif
#ifdef PRESTIGE_SYSTEM
CPrestige::CPrestige()
{

}

CPrestige::~CPrestige()
{
	m_rewards.clear();
}

std::vector<CItem*> CPrestige::getItemsReward()
{
	std::vector<CItem*> items;

	for (int i = 0; i < m_rewards.size(); i++)
	{
		PRESTIGE_REWARD* reward = m_rewards[i];
		CItem* pGiveItem = gserver->m_itemProtoList.CreateItem(reward->item_index, -1, 0, 0, reward->item_count);
		if (pGiveItem == NULL)
			continue;

		items.push_back(pGiveItem);
	}

	return items;
}

std::vector<CItem*> CPrestige::getPremiumItemsReward()
{
	std::vector<CItem*> items;

	for (int i = 0; i < m_rewards.size(); i++)
	{
		PRESTIGE_REWARD* reward = m_rewards[i];

		CItem* pGiveItemPremium = gserver->m_itemProtoList.CreateItem(reward->premium_item_index, -1, 0, 0, reward->premium_item_count);
		if (pGiveItemPremium == NULL)
			continue;

		items.push_back(pGiveItemPremium);
	}

	return items;
}

bool CPrestige::LoadReward()
{
	m_rewards.clear();
	CDBCmd dbcmd;
	dbcmd.Init(&gserver->m_dbdata);

	std::string query = boost::str(
		boost::format("SELECT * FROM t_prestige_reward WHERE a_prestige_idx = %d") % m_index);
	dbcmd.SetQuery(query);

	if (!dbcmd.Open() || !dbcmd.MoveFirst()) {
		return false;
	}

	do {

		PRESTIGE_REWARD* reward = new PRESTIGE_REWARD();

		dbcmd.GetRec("a_item_idx", reward->item_index);
		dbcmd.GetRec("a_item_count", reward->item_count);
		dbcmd.GetRec("a_premium_item_idx", reward->premium_item_index);
		dbcmd.GetRec("a_premium_item_count", reward->premium_item_count);

		addReward(reward);

	} while (dbcmd.MoveNext());


	return true;
}

CPrestige* CServer::FindPrestigeByLevel(int level)
{
	if (level == 0)
		level = 1;
	map_prestige_t::iterator it = gserver->m_listPrestige.begin();
	map_prestige_t::iterator endit = gserver->m_listPrestige.end();
	for (; it != endit; ++it)
	{
		CPrestige* prestige = (*it).second;
		if (prestige && prestige->m_level == level)
			return prestige;
	}
	return NULL;
}

bool CServer::LoadPrestige()
{
	m_listPrestige.clear();
	CDBCmd dbcmd;
	dbcmd.Init(&gserver->m_dbdata);

	std::string select = "SELECT * FROM t_prestige";
	dbcmd.SetQuery(select);

	if (!dbcmd.Open() || !dbcmd.MoveFirst()) {
		return false;
	}

	do {

		CPrestige* prestige = new CPrestige();

		dbcmd.GetRec("a_index", prestige->m_index);
		dbcmd.GetRec("a_name", prestige->m_name);
		dbcmd.GetRec("a_points", prestige->m_points);
		dbcmd.GetRec("a_premium_points", prestige->m_premium_points);
		dbcmd.GetRec("a_level", prestige->m_level);
		dbcmd.GetRec("a_season", prestige->m_season);//Cloud add Season
		dbcmd.GetRec("a_char_level", prestige->m_char_level);//Cloud add Season
		prestige->LoadReward();

		m_listPrestige.insert(map_prestige_t::value_type(prestige->m_index, prestige));

	} while (dbcmd.MoveNext());

	return true;
}


#endif
#ifdef CLOUD_EXPEDITION_REWORK
CPartyExpeditions::CPartyExpeditions()
{
	m_PartyExpeditions.clear();
}

CPartyExpeditions::~CPartyExpeditions()
{

}

bool CPartyExpeditions::Load()
{
	m_PartyExpeditions.clear();

	std::string selectDB = "SELECT * FROM t_cloud_partyexpedition_config";
	CDBCmd cmd;
	cmd.Init(&gserver->m_dbdata);
	cmd.SetQuery(selectDB);
	if (!cmd.Open())
		return false;

	while (cmd.MoveNext())
	{
		PartyExpeditionsInfo config;
		//config.dungeoncount = cmd.GetRecordCount();

		cmd.GetRec("a_zonetid", config.zoneid);
		cmd.GetRec("a_difficulty", config.difficulty);
		cmd.GetRec("a_level", config.level);
		cmd.GetRec("a_cp", config.cp);
		cmd.GetRec("a_need_item_idx", config.needitem);
		cmd.GetRec("a_need_item_count", config.needcount);
		cmd.GetRec("a_member_need", config.partymember);
		cmd.GetRec("a_reward_item_idx", config.rewardindex);
		cmd.GetRec("a_reward_item_count", config.count);
		cmd.GetRec("a_reward_item_idx1", config.rewardindex1);
		cmd.GetRec("a_reward_item_count1", config.count1);
		cmd.GetRec("a_reward_item_idx2", config.rewardindex2);
		cmd.GetRec("a_reward_item_count2", config.count2);
		cmd.GetRec("a_reward_item_idx3", config.rewardindex3);
		cmd.GetRec("a_reward_item_count3", config.count3);
		cmd.GetRec("a_reward_item_idx4", config.rewardindex4);
		cmd.GetRec("a_reward_item_count4", config.count4);
		cmd.GetRec("a_tittle_reward", config.title);
		cmd.GetRec("a_box_reward", config.box);
		cmd.GetRec("a_box_count", config.boxcount);
		cmd.GetRec("a_boss_idx1", config.bossidx1);
		cmd.GetRec("a_boss_idx2", config.bossidx2);
		cmd.GetRec("a_boss_idx3", config.bossidx3);
		cmd.GetRec("a_domination0", config.domination0);
		cmd.GetRec("a_domination1", config.domination1);
		cmd.GetRec("a_domination_point", config.dominationpoint);
		cmd.GetRec("a_type", config.type);
		cmd.GetRec("a_time", config.time);
		m_PartyExpeditions.push_back(config);
	}
	return true;
}

int CPartyExpeditions::GetDungeonConfigs(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].zoneid;
	}

	return false;
}

int CPartyExpeditions::GetZoneCount(int difficulty)
{
	int count = 0;

	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (m_PartyExpeditions[i].difficulty == difficulty)
			count++;
	}

	return count;
}

int CPartyExpeditions::GetDungeonNeedItem(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].needitem;
	}

	return -1;
}

int CPartyExpeditions::GetDungeonNeedCount(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].needcount;
	}

	return 1;
}

int CPartyExpeditions::GetDungeonLevel(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].level;
	}

	return 0;
}

int CPartyExpeditions::GetDungeonCP(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].cp;
	}

	return 0;
}

int CPartyExpeditions::GetDungeonMember(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].partymember;
	}

	return 1;
}

int CPartyExpeditions::GetDungeonTitle(int zone)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && 0 == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].title;
	}

	return -1;
}
int CPartyExpeditions::GetDungeonBox(int zone)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && 0 == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].box;
	}

	return -1;
}
int CPartyExpeditions::GetDungeonBoxCount(int zone)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && 0 == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].boxcount;
	}

	return 0;
}
int CPartyExpeditions::GetDungeonDomination0(int zone)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && 0 == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].domination0;
	}

	return 0;
}
int CPartyExpeditions::GetDungeonDomination1(int zone)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && 0 == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].domination1;
	}

	return 0;
}

int CPartyExpeditions::GetDungeonBoss1(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].bossidx1;
	}

	return 0;
}

int CPartyExpeditions::GetDungeonBoss2(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].bossidx2;
	}

	return 0;
}

int CPartyExpeditions::GetDungeonBoss3(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].bossidx3;
	}

	return 0;
}

int CPartyExpeditions::GetDungeonZoneID(int zone)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid)
			return m_PartyExpeditions[i].zoneid;
	}

	return 0;
}

int CPartyExpeditions::GetDungeonDifficulty(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].difficulty;
	}

	return 0;
}
int CPartyExpeditions::GetDungeonPoint(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].dominationpoint;
	}

	return 0;
}
int CPartyExpeditions::GetDungeonType(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].type;
	}

	return 0;
}

int CPartyExpeditions::GetDungeonTime(int zone, int difficulty)
{
	for (int i = 0; i < m_PartyExpeditions.size(); i++)
	{
		if (zone == m_PartyExpeditions[i].zoneid && difficulty == m_PartyExpeditions[i].difficulty)
			return m_PartyExpeditions[i].time;
	}

	return 600;
}
#endif
bool CServer::LoadNpcBossList() {

	std::string select_boss_list_query = "SELECT * FROM t_boss_list";
	CDBCmd dbNpc;
	dbNpc.Init(&gserver->m_dbdata);
	dbNpc.SetQuery(select_boss_list_query);
	if (!dbNpc.Open())
		return false;

	int bossIndex;
	while (dbNpc.MoveNext())
	{
		dbNpc.GetRec("a_npc_idx", bossIndex);
		gserver->m_bossList.push_back(bossIndex);
	}

	return true;
}

// Load scripted NPC movement configurations from the database
bool CServer::LoadScriptedMovements()
{
	GAMELOG << init("SYSTEM") << "Loading scripted NPC movements..." << end;

	m_scriptedMovementConfigs.clear();

	CDBCmd dbcmd;
	dbcmd.Init(&m_dbdata);
	dbcmd.SetQuery("SELECT a_npc_db_index, a_order, a_x, a_z, a_tick_delay, a_loop FROM t_npc_scripted_movement ORDER BY a_npc_db_index, a_order");

	if (!dbcmd.Open())
	{
		LOG_INFO("LoadScriptedMovements: t_npc_scripted_movement table not found or query failed");
		return false;
	}

	// Group waypoints by npc db index
	std::map<int, ScriptedMovementConfig> configMap;

	while (dbcmd.MoveNext())
	{
		int npcDBIndex = 0;
		int order = 0;
		float x = 0.0f, z = 0.0f;
		int tickDelay = 1;
		int loopVal = 0;

		if (!dbcmd.GetRec("a_npc_db_index", npcDBIndex)
			|| !dbcmd.GetRec("a_order", order)
			|| !dbcmd.GetRec("a_x", x)
			|| !dbcmd.GetRec("a_z", z)
			|| !dbcmd.GetRec("a_tick_delay", tickDelay)
			)
		{
			LOG_ERROR("LoadScriptedMovements: failed to read record");
			return false;
		}

		dbcmd.GetRec("a_loop", loopVal);

		if (tickDelay <= 0)
			tickDelay = 1;

		std::map<int, ScriptedMovementConfig>::iterator it = configMap.find(npcDBIndex);
		if (it == configMap.end())
		{
			ScriptedMovementConfig cfg;
			cfg.npcDBIndex = npcDBIndex;
			cfg.tickDelay = tickDelay;
			cfg.loopType = loopVal;
			Waypoint wp;
			wp.x = x;
			wp.z = z;
			cfg.waypoints.push_back(wp);
			configMap.insert(std::make_pair(npcDBIndex, cfg));
		}
		else
		{
			Waypoint wp;
			wp.x = x;
			wp.z = z;
			it->second.waypoints.push_back(wp);
			// use tick_delay and loop from the first row, but allow override
			if (loopVal != 0)
				it->second.loopType = loopVal;
		}
	}

	// Move grouped configs into vector
	for (std::map<int, ScriptedMovementConfig>::iterator it = configMap.begin(); it != configMap.end(); ++it)
	{
		if (it->second.waypoints.size() < 2)
		{
			LOG_INFO("LoadScriptedMovements: npcDBIndex=%d has fewer than 2 waypoints, skipping", it->second.npcDBIndex);
			continue;
		}
		m_scriptedMovementConfigs.push_back(it->second);
	}

	LOG_INFO("LoadScriptedMovements: loaded %d scripted movement config(s)", (int)m_scriptedMovementConfigs.size());

	// Apply configs: find matching NPCs in all zones and set up their scripted movement
	for (size_t ci = 0; ci < m_scriptedMovementConfigs.size(); ++ci)
	{
		const ScriptedMovementConfig& cfg = m_scriptedMovementConfigs[ci];

		for (int zi = 0; zi < m_numZone; ++zi)
		{
			if (m_zones[zi].m_bRemote)
				continue;
			CZone& z = m_zones[zi];
			for (int ai = 0; ai < z.m_countArea; ++ai)
			{
				CArea& a = z.m_area[ai];
				if (!a.m_bEnable || a.m_npcList == NULL)
					continue;
				CNPC* npc = a.m_npcList;
				while (npc)
				{
					CNPC* next = npc->m_pNPCNext;
					if (npc->m_idNum == cfg.npcDBIndex)
					{
						// Validate waypoint is within the area bounds before modifying NPC
						int ocx = -1, ocz = -1;
						a.PointToCellNum(cfg.waypoints[0].x, cfg.waypoints[0].z, &ocx, &ocz);
						if (ocx < 0 || ocz < 0)
						{
							LOG_ERROR("LoadScriptedMovements: waypoint out of bounds for npcIndex=%d dbIndex=%d x=%.2f z=%.2f, skipping",
								npc->m_index, npc->m_idNum, cfg.waypoints[0].x, cfg.waypoints[0].z);
							npc = next;
							continue;
						}

						// prevent NPC AI from interfering with scripted movement
						npc->m_aipulse = m_pulse;
						npc->m_delay = PULSE_REAL_SEC * 60;

						// remove NPC from current cell before repositioning
						a.CharFromCell(npc, true);

						// place NPC at first waypoint
						GET_X(npc) = cfg.waypoints[0].x;
						GET_Z(npc) = cfg.waypoints[0].z;
						npc->m_regenX = cfg.waypoints[0].x;
						npc->m_regenZ = cfg.waypoints[0].z;

						a.CharToCell(npc, GET_YLAYER(npc), ocx, ocz);

						npc->m_bScriptedMovement = true;
						AddMovementTask(npc, cfg.waypoints, cfg.tickDelay, cfg.loopType);

						LOG_INFO("LoadScriptedMovements: applied movement for npcIndex=%d dbIndex=%d waypoints=%d tickDelay=%d loopType=%d",
							npc->m_index, npc->m_idNum, (int)cfg.waypoints.size(), cfg.tickDelay, cfg.loopType);
					}
					npc = next;
				}
			}
		}
	}

	return true;
}

void CServer::ReloadScriptedMovements()
{
	LOG_INFO("ReloadScriptedMovements: cleaning up %d active movement task(s)", (int)m_movementTasks.size());

	// Stop all active movement tasks and restore NPC state
	for (size_t i = 0; i < m_movementTasks.size(); ++i)
	{
		MovementTask& t = m_movementTasks[i];
		CNPC* npc = t.npc;
		if (npc && npc->m_index == t.npcIndex)
		{
			npc->m_bScriptedMovement = false;
			npc->m_flag = t.origInstanceFlags;

			if (npc->m_pArea)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeMoveMsg(rmsg, MSG_MOVE_PLACE, npc);
				npc->m_pArea->SendToCell(rmsg, npc, true);
			}
		}
	}
	m_movementTasks.clear();
	m_scriptedMovementConfigs.clear();

	// Reload from database
	if (!LoadScriptedMovements())
	{
		GAMELOG << init("WARNING") << "ReloadScriptedMovements: Failed to reload scripted NPC movements" << end;
	}
	else
	{
		LOG_INFO("ReloadScriptedMovements: reload complete, %d config(s), %d task(s) active",
			(int)m_scriptedMovementConfigs.size(), (int)m_movementTasks.size());
	}
}

int CServer::CalcSegmentSteps(CNPC* npc, const Waypoint& from, const Waypoint& to)
{
	float dx = to.x - from.x;
	float dz = to.z - from.z;
	float dist = sqrtf(dx * dx + dz * dz);
	float walkSpeed = 0.0f;
	if (npc && npc->m_proto)
		walkSpeed = npc->m_proto->m_walkSpeed;

	if (walkSpeed <= 0.0f && (npc && npc->m_proto))
		walkSpeed = npc->m_proto->m_runSpeed;

	if (walkSpeed <= 0.0f)
		walkSpeed = 1.0f;

	float timeSec = dist / walkSpeed;
	int totalTicks = (int)ceilf(timeSec / 0.1f);
	if (totalTicks <= 0)
		totalTicks = 1;
	return totalTicks;
}

// Movement task implementations
void CServer::AddMovementTask(CNPC* npc, const std::vector<Waypoint>& waypoints, int tickDelay, int loopType)
{
	if (!npc) return;
	if (waypoints.size() < 2) return;

	MovementTask t;
	t.npc = npc;
	t.npcIndex = npc->m_index;
	t.waypoints = waypoints;
	t.curSegment = 0;
	t.segmentSteps = CalcSegmentSteps(npc, waypoints[0], waypoints[1]);
	t.curStep = 0;
	t.tickDelay = (tickDelay > 0) ? tickDelay : 1;
	t.tickCounter = 0;
	t.loopType = loopType;
	t.reversing = false;
	t.origInstanceFlags = npc->m_flag;
	t.displayShop = false;

	t.lastCellX = -1;
	t.lastCellZ = -1;
	if (npc->m_pArea)
	{
		npc->m_pArea->PointToCellNum(GET_X(npc), GET_Z(npc), &t.lastCellX, &t.lastCellZ);
	}

	npc->m_bScriptedMovement = true;
	if (npc->m_proto && npc->m_proto->CheckFlag(NPC_SHOPPER))
	{
		npc->m_flag &= ~NPC_SHOPPER;
		LOG_INFO("AddMovementTask: cleared instance SHOPPER flag for npcIndex=%d dbIndex=%d protoFlags=0x%X npcFlags=0x%X",
			npc->m_index, npc->m_idNum, npc->m_proto->GetFlag(), npc->m_flag);
	}
	LOG_INFO("AddMovementTask: added scripted movement for npcIndex=%d dbIndex=%d waypoints=%d tickDelay=%d loopType=%d",
		npc->m_index, npc->m_idNum, (int)waypoints.size(), t.tickDelay, loopType);
	npc->m_aipulse = m_pulse;
	npc->m_delay = PULSE_REAL_SEC * 60 * 60;

	npc->m_regenX = waypoints[0].x;
	npc->m_regenZ = waypoints[0].z;

	m_movementTasks.push_back(t);
}

void CServer::RemoveMovementTasksForNPC(CNPC* npc)
{
	if (!npc) return;
	for (int i = (int)m_movementTasks.size() - 1; i >= 0; --i)
	{
		if (m_movementTasks[i].npc == npc)
		{
			LOG_INFO("RemoveMovementTasksForNPC: removing task for npcIndex=%d dbIndex=%d",
				npc->m_index, npc->m_idNum);
			m_movementTasks[i].npc = NULL;
			m_movementTasks.erase(m_movementTasks.begin() + i);
		}
	}
}

void CServer::UpdateScriptedMovements()
{
	if (m_movementTasks.empty()) return;

	for (int i = (int)m_movementTasks.size() - 1; i >= 0; --i)
	{
		MovementTask& t = m_movementTasks[i];
		CNPC* npc = t.npc;
		if (!npc || npc->m_pArea == NULL || npc->m_index != t.npcIndex)
		{
			if (npc && npc->m_index == t.npcIndex) {
				npc->m_bScriptedMovement = false;
				LOG_INFO("UpdateScriptedMovements: removing task because npc->m_pArea==NULL npcIndex=%d dbIndex=%d", npc->m_index, npc->m_idNum);
			}
			m_movementTasks.erase(m_movementTasks.begin() + i);
			continue;
		}

		t.tickCounter++;
		if (t.tickCounter < t.tickDelay)
			continue;
		t.tickCounter = 0;

		t.curStep++;

		// Interpolate position within current segment
		// When reversing (ping-pong), walk from waypoints[curSegment+1] to waypoints[curSegment]
		const Waypoint& wpFrom = t.reversing ? t.waypoints[t.curSegment + 1] : t.waypoints[t.curSegment];
		const Waypoint& wpTo = t.reversing ? t.waypoints[t.curSegment] : t.waypoints[t.curSegment + 1];

		if (t.curStep >= t.segmentSteps)
			t.curStep = t.segmentSteps;

		float frac = (float)t.curStep / (float)t.segmentSteps;
		float nx = wpFrom.x + (wpTo.x - wpFrom.x) * frac;
		float nz = wpFrom.z + (wpTo.z - wpFrom.z) * frac;

		int ncx = -1, ncz = -1;
		npc->m_pArea->PointToCellNum(nx, nz, &ncx, &ncz);
		if (ncx < 0 || ncz < 0)
		{
			LOG_ERROR("UpdateScriptedMovements: interpolated position out of bounds npcIndex=%d dbIndex=%d x=%.2f z=%.2f, removing task",
				npc->m_index, npc->m_idNum, nx, nz);
			npc->m_bScriptedMovement = false;
			m_movementTasks.erase(m_movementTasks.begin() + i);
			continue;
		}
		int ocx = -1, ocz = -1;
		npc->m_pArea->PointToCellNum(GET_X(npc), GET_Z(npc), &ocx, &ocz);
		if (ncx != ocx || ncz != ocz)
		{
			npc->m_pArea->CharFromCell(npc, true);
			GET_X(npc) = nx;
			GET_Z(npc) = nz;
			npc->m_pArea->CharToCell(npc, GET_YLAYER(npc), ncx, ncz);
		}
		else
		{
			GET_X(npc) = nx;
			GET_Z(npc) = nz;
		}

		npc->m_regenX = GET_X(npc);
		npc->m_regenZ = GET_Z(npc);

		{
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeMoveMsg(rmsg, MSG_MOVE_WALK, npc);
			npc->m_pArea->SendToCell(rmsg, npc, true);
		}

		// Check if we reached the end of the current segment
		if (t.curStep >= t.segmentSteps)
		{
			if (!t.reversing)
			{
				// Walking forward
				int nextSegment = t.curSegment + 1;

				if (nextSegment + 1 < (int)t.waypoints.size())
				{
					// More segments to walk forward
					t.curSegment = nextSegment;
					t.segmentSteps = CalcSegmentSteps(npc, t.waypoints[t.curSegment], t.waypoints[t.curSegment + 1]);
					t.curStep = 0;
				}
				else
				{
					// Reached the last waypoint
					if (t.loopType == 1)
					{
						// Restart from the beginning (ABC ABC ABC)
						t.curSegment = 0;
						t.segmentSteps = CalcSegmentSteps(npc, t.waypoints[0], t.waypoints[1]);
						t.curStep = 0;
					}
					else if (t.loopType == 2)
					{
						// Ping-pong: reverse direction (ABC BA BC BA)
						t.reversing = true;
						t.curSegment = (int)t.waypoints.size() - 2;
						t.segmentSteps = CalcSegmentSteps(npc, t.waypoints[t.curSegment + 1], t.waypoints[t.curSegment]);
						t.curStep = 0;
					}
					else
					{
						// Done - remove the task
						CNetMsg::SP rmsg(new CNetMsg);
						ResponseClient::makeMoveMsg(rmsg, MSG_MOVE_PLACE, npc);
						npc->m_pArea->SendToCell(rmsg, npc, true);
						npc->m_bScriptedMovement = false;
						m_movementTasks.erase(m_movementTasks.begin() + i);
					}
				}
			}
			else
			{
				// Walking backward (ping-pong reverse)
				int prevSegment = t.curSegment - 1;

				if (prevSegment >= 0)
				{
					// More segments to walk backward
					t.curSegment = prevSegment;
					t.segmentSteps = CalcSegmentSteps(npc, t.waypoints[t.curSegment + 1], t.waypoints[t.curSegment]);
					t.curStep = 0;
				}
			}
		}
	}
}

// ================================================================
// Offline Shop Registry Methods
// ================================================================

#ifdef OFFLINE_SHOPS

void CServer::RegisterOfflineShop(int shopId, CPersonalShop::SP pShop)
{
	if (!pShop || shopId <= 0)
	{
		LOG_WARN("RegisterOfflineShop: Invalid shop or ID - shopId=%d", shopId);
		return;
	}

	m_offlineShopRegistryMutex.lock();
	m_offlineShopRegistry[shopId] = pShop;
	m_offlineShopRegistryMutex.unlock();

	LOG_INFO("RegisterOfflineShop: Registered offline shop - shopId=%d, owner_char_index=%d", 
		shopId, pShop->GetCharIndex());
}

CPersonalShop::SP CServer::GetOfflineShop(int shopId)
{
	m_offlineShopRegistryMutex.lock();

	auto it = m_offlineShopRegistry.find(shopId);
	CPersonalShop::SP result;
	if (it != m_offlineShopRegistry.end())
	{
		result = it->second;
	}

	m_offlineShopRegistryMutex.unlock();
	return result;
}

CPersonalShop::SP CServer::GetOfflineShopByCharIndex(int charIndex)
{
	m_offlineShopRegistryMutex.lock();

	CPersonalShop::SP result;
	for (auto& pair : m_offlineShopRegistry)
	{
		if (pair.second && pair.second->GetCharIndex() == charIndex)
		{
			result = pair.second;
			break;
		}
	}

	m_offlineShopRegistryMutex.unlock();
	return result;
}

void CServer::UnregisterOfflineShop(int shopId)
{
	m_offlineShopRegistryMutex.lock();

	auto it = m_offlineShopRegistry.find(shopId);
	if (it != m_offlineShopRegistry.end())
	{
		LOG_INFO("UnregisterOfflineShop: Unregistered offline shop - shopId=%d", shopId);
		m_offlineShopRegistry.erase(it);
	}

	m_offlineShopRegistryMutex.unlock();
}

int CServer::GetOfflineShopCount()
{
	m_offlineShopRegistryMutex.lock();
	int count = (int)m_offlineShopRegistry.size();
	m_offlineShopRegistryMutex.unlock();
	return count;
}

// ================================================================
// Offline Vendor Spawn Helpers (SIMPLIFIED STUBS FOR NOW)
// ================================================================

CPC* CServer::SpawnOfflineVendor(CPersonalShop::SP pShop)
{
	// TODO: Implement headless vendor spawn
	// For now, just log and return NULL
	if (!pShop)
	{
		LOG_ERROR("SpawnOfflineVendor: Invalid shop");
		return NULL;
	}

	int shopId = pShop->GetShopId();
	LOG_INFO("SpawnOfflineVendor: Stub - shopId=%d", shopId);

	// TODO: Create CPC, place in zone, register in m_offlineVendorRegistry
	return NULL;
}

void CServer::DespawnOfflineVendor(int shopId)
{
	LOG_INFO("DespawnOfflineVendor: Stub - shopId=%d", shopId);
	// TODO: Remove from registry and clean up
}

CPC* CServer::GetOfflineVendor(int shopId)
{
	// TODO: Look up vendor in m_offlineVendorRegistry
	return NULL;
}

CPC* CServer::GetOfflineVendorByCharIndex(int charIndex)
{
	// TODO: Look up vendor by character index in registry
	return NULL;
}

void CServer::SpawnAllOfflineVendors()
{
	LOG_INFO("SpawnAllOfflineVendors: Stub - TODO implement at server startup");
	// TODO: Load offline shops from DB and spawn each one
}

int CServer::GetOfflineVendorCount()
{
	// TODO: Return actual count from m_offlineVendorRegistry
	return 0;
}

#endif // OFFLINE_SHOPS