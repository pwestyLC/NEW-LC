#ifndef __CONFIG_LOCALIZE_GAMIGO_H__
#define __CONFIG_LOCALIZE_GAMIGO_H__

#define LC_GAMIGO

#if defined(LC_GER)
#define GER_LOG											// ���� �α� �߰�
#define VERSIONKEY "1106"
#define INTERNATIONAL_LOCAL_ACCESS_RESTRICTIONS
#define DEV_GAMIGO_HTTPS								// ���̰� Https ���� ��� ( linux �� ���� )
#endif

#if defined (LC_SPN)
#define INTERNATIONAL_LOCAL_ACCESS_RESTRICTIONS_SPN			// �ؿ� ���� ���� ���� - new ����
#define INTERNATIONAL_LOCAL_ACCESS_RESTRICTIONS_NEW_USER	// �ű������� ���������� ���
#define IP_NATION_CHECK
#endif

#if defined (LC_FRC)
#endif

#if defined (LC_PLD)
#endif

#if defined (LC_ITA)
#define EVENT_EUR2_PROMOTION
#endif

////// ���� �ʵ� ���� //////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
#define		HARDCORE_SERVER

#ifdef LC_GER
#define ITEM_NAME_FIELD         "a_name_ger"
#define NPC_NAME_FIELD          "a_name_ger"
#define ITEM_PRICE_FIELD        "a_price"
#define EVENT_ENABLE_FIELD      "a_enable_ger"
#define EVENT_EXTRA_FILED       "a_extra_ger"
#elif defined (LC_SPN)
#define ITEM_NAME_FIELD         "a_name_spn"
#define NPC_NAME_FIELD          "a_name_spn"
#define ITEM_PRICE_FIELD        "a_price"
#define EVENT_ENABLE_FIELD      "a_enable_spn"
#define EVENT_EXTRA_FILED       "a_extra_spn"

#elif defined (LC_FRC)
#define ITEM_NAME_FIELD         "a_name_frc"
#define NPC_NAME_FIELD          "a_name_frc"
#define ITEM_PRICE_FIELD        "a_price"
#define EVENT_ENABLE_FIELD      "a_enable_frc"
#define EVENT_EXTRA_FILED       "a_extra_frc"

#elif defined (LC_PLD)
#define ITEM_NAME_FIELD         "a_name_pld"
#define NPC_NAME_FIELD          "a_name_pld"
#define ITEM_PRICE_FIELD        "a_price"
#define EVENT_ENABLE_FIELD      "a_enable_pld"
#define EVENT_EXTRA_FILED       "a_extra_pld"

#elif LC_ITA
#define ITEM_NAME_FIELD         "a_name_ita"
#define NPC_NAME_FIELD          "a_name_ita"
#define ITEM_PRICE_FIELD        "a_price"
#define EVENT_ENABLE_FIELD      "a_enable_ita"
#define EVENT_EXTRA_FILED       "a_extra_ita"
#elif LC_TUR
#define ITEM_NAME_FIELD         "a_name_tur"
#define NPC_NAME_FIELD          "a_name_tur"
#define ITEM_PRICE_FIELD        "a_price"
#define EVENT_ENABLE_FIELD      "a_enable_tur"
#define EVENT_EXTRA_FILED       "a_extra_tur"
#elif LC_UK
#define ITEM_NAME_FIELD         "a_name_uk"
#define NPC_NAME_FIELD          "a_name_uk"
#define ITEM_PRICE_FIELD        "a_price"
#define EVENT_ENABLE_FIELD      "a_enable_uk"
#define EVENT_EXTRA_FILED       "a_extra_uk"
#endif

////// OX QUIZ ���� �ڵ� ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#if defined (LC_GER)
#define OX_QUIZ_COUNTRY_CODE	13
#elif defined (LC_SPN)
#define OX_QUIZ_COUNTRY_CODE    14
#elif defined (LC_FRC)
#define OX_QUIZ_COUNTRY_CODE    15
#elif defined (LC_PLD)
#define OX_QUIZ_COUNTRY_CODE    16
#elif defined (LC_TUR)
#define OX_QUIZ_COUNTRY_CODE    18
#elif defined (LC_ITA)
#define OX_QUIZ_COUNTRY_CODE    19
#elif defined (LC_UK)
#define OX_QUIZ_COUNTRY_CODE    24
#endif

////// ��� �̺�Ʈ /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
#define DOUBLE_PET_EXP
#ifdef DOUBLE_PET_EXP
#define DOUBLE_PET_EXP_AUTO
#define DOUBLE_PET_EXP_SAVEFILE	".doublepetexp"
#endif

////// IP �ڵ� ���� ���� ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#define IP_BLOCK_AUTO
#if defined (IP_BLOCK_AUTO )
#define IP_BLOCKNOKICK_AUTO     // ������ ������� �϶� ű���� �ʰ� �α׸� ����
#endif // #if defined (IP_BLOCK_AUTO )

////// ��� ���� ���� //////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#define     GM_LEVEL_ECHO               5
#define     GM_LEVEL_GO_ZONE            3
#define     GM_LEVEL_GOTO               3
#define     GM_LEVEL_ITEMDROP           10
#define     GM_LEVEL_COUNT_PC           10
#define     GM_LEVEL_LOOPCOUNT          10
#define     GM_LEVEL_IMMORTAL           3
#define     GM_LEVEL_SHUTDOWN           10
#define     GM_LEVEL_REBOOT             9
#define     GM_LEVEL_COUNT_NPC          9
#define     GM_LEVEL_VISIBLE            3
#define     GM_LEVEL_GO_PC              3
#define     GM_LEVEL_GO_NPC             3
#define     GM_LEVEL_LEVELUP            8
#define     GM_LEVEL_KICK               5
#define     GM_LEVEL_COMON              8
#define     GM_LEVEL_SUMMON             9
#define     GM_LEVEL_SILENCE            5
#define     GM_LEVEL_WHERE_AM_I         3
#define     GM_LEVEL_QUEST_COMPLETE     7
#define     GM_LEVEL_STATPOINT          7
#define     GM_LEVEL_SKILLPOINT         7
#define     GM_LEVEL_SET_REGENSEC       8
#define     GM_LEVEL_NPC_REGEN          8
#define     GM_LEVEL_KILL_NPC           1
#define     GM_LEVEL_EXPUP              8
#define     GM_LEVEL_BLOODPOINT         8
#define     GM_LEVEL_ENDGAME            9
#define     GM_LEVEL_OBSERVE            9
#define     GM_LEVEL_CHATMONITOR        5
#define     GM_LEVEL_DOUBLE_EVENT       9
#define     GM_LEVEL_LATTO_EVENT        9
#define     GM_LEVEL_DOUBLE_EXP_EVENT   9
#define     GM_LEVEL_NEWYEAR_EVENT      9
#define     GM_LEVEL_VALENTINE_EVENT    9
#define     GM_LEVEL_WHITEDAY_EVENT     9
#define     GM_LEVEL_LETTER_EVENT       9
#define     GM_LEVEL_RELOAD_GMIP        10
#define     GM_LEVEL_SPEEDUP            3
#define     GM_LEVEL_FAMEUP             9
#define     GM_LEVEL_EVENT              9
#define     GM_LEVEL_PD4                9
#define     GM_LEVEL_KICK_ID            5
#define     GM_LEVEL_RESURRECTION       9
#define     GM_LEVEL_RECOMMEND          9
#define     GM_LEVEL_SETLIMIT           9
#define     GM_LEVEL_DISGUISE           9
#define     GM_LEVEL_LOGINSERVER        9
#define     GM_LEVEL_CALTIME            10
#define     GM_LEVEL_KICK_CHAR_INDEX    5
#define     GM_LEVEL_EVENTSHOW          5
#define     GM_LEVEL_EVENTSETTING       10
#define     GM_LEVEL_CHANCE_EVENT       9
#define     GM_LEVEL_GMCHATMONITOR      10
#define     GM_LEVEL_DOUBLE_ITEM_EVENT  9
#define     GM_LEVEL_DOUBLE_PET_EXP_EVENT   9
#define     GM_LEVEL_DOUBLE_ATTACK_EVENT    9
#define     GM_LEVEL_EVENT_DROPITEM     10
#define     GM_LEVEL_KICK_PC_MULRI      9
#define     GM_LEVEL_SILENCE_PC_MULTI   9
#define     GM_LEVEL_SET_EXPLIMIT       10
#define     GM_LEVEL_DOUBLE_EVENT_AUTO  10
#define     GM_LEVEL_UPGRADE_EVENT      10
#define     GM_LEVEL_KICK_GUILDMEMBER   10
#define     GM_LEVEL_APPLY_SKILL        10
#define		GM_LEVEL_STATE_FLAG			10
#define		GM_LEVEL_DATE				1
#define		GM_LEVEL_PLAY_TRIGGER		10
#define		GM_LEVEL_BATTLE_START		10
#define		GM_LEVEL_BATTLE_STOP		10
#define		GM_LEVEL_RESET_RAID			10
#define		GM_LEVEL_SET_SEAL_EXP		10
#define		GM_LEVEL_END_SUBHELPER		10
#define		GM_LEVEL_LCBALL_RESET		10
#define		GM_LEVEL_ECHONPC			9
#define		GM_LEVEL_DT_EXPSET			10
#define     GM_LEVEL_ITEMGET			10
#define		GM_LEVEL_ITEMGETRANGE		10
#define		GM_LEVEL_JOBRESET			10
#define		GM_LEVEL_JOBCHANGE			10

////// ���̰� ���� ������ /////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
#define SERVER_AUTHENTICATION		// ���� �⵿ ���� �ý���

#define DURABILITY
#define PREMIUM_CHAR
#define INTERGRATION_SERVER
#define EU_INTERGRATION_SERVER
#if defined (EU_INTERGRATION_SERVER)
#define INTERGRATION_USA 9
#define INTERGRATION_GER 13
#define INTERGRATION_SPN 14
#define INTERGRATION_FRC 15
#define INTERGRATION_PLD 16
#define INTERGRATION_TUR 18
#define INTERGRATION_ITA 19
#define INTERGRATION_UK  24
#define INTERGRATION_BRZ 10
#endif

#define DROP_MAKE_DOCUMENT                              // ���ۼ� ���
#define MAX_UPGRADE_PLUS                    25          // ������ ���׷��̵� �ִ� �÷��� ��ġ
#define RECOMMEND_SERVER_POTION_INDEX       1393
#define PULSE_GUILD_POINT_UPDATE            (5 * 60)    // ��� ��ų�� ����ġ ���� ����
#define DEFAULT_LIMIT_EXP               250
#define RANDOM_ZUNO                                     // �ֳ� ���� ������ ��ġ �߰�
#define NEW_DOUBLE_GM_SAVEFILE  ".doubleevent"      // DOUBLE EVENT ���ɾ� ����
#define DEFAULT_NAS_GET_PERCENT         100             // ���� ���淮 ����
#define DEFAULT_EXP_PERCENT             100             // ����ġ ȹ�淮 ����
#define DEFAULT_SP_PERCENT              100             // sp ȹ�淮 ����
#define DEFAULT_PRO_GET_NUMBER          1               // ���� ���� ����
#define GER_SERIAL_PROMOTION            "FP"

#define CHAT_BLOCK_USA                                  // ��ġ��
#define CHAT_BLOCK_USA_NEXT_TIME	30 // ���� ��ĥ�� �ִ� �ð�
#define CHAT_BLOCK_USA_LEVEL		15 // ��ġ�� ������ ����

#define EVENT_PACKAGE_ITEM                              // ��Ű�� �ø����� �̿��� ������ ����
#define EVENT_PACKAGE_ITEM_DBLOG
#define EGEHA_ZONE_PAYMENT              500000          // ������ �����
#define RAID_NPC_RAGE_SKILL             394             // ���̵� �� �г� ��ų �ε���
#define RAID_NPC_RAGE_SKILL_LEVEL       2               // ���̵� �� �г� ��ų ����
#define RAID_NPC_NOTICE_CELL_EXT        5
#define MAX_RARE_OPTION_SETTING         10              // ���� �ɼǴ� �ɼ� ���� ��
#define MAX_RARE_OPTION_ITEM            10              // �����۴� ���� �ɼ� ��
#define PULSE_MONSTER_RAID_MOVE         (14 * PULSE_REAL_MIN)   // ���� ���̵� �̵� �ð�
#define EXTREME_CUBE                                    // �ͽ�Ʈ�� ť��
#define HANARO_EVENT					//�ʺ������̺�Ʈ �߰�(2014-5-28)
#define MONSTER_COMBO_FIX
#define LOGIN_TIME_CHECK
#define BATTLE_PARTY_BOSS_CHANGE		// ������Ƽ �� ��Ƽ�� ���濡 ���� ���� �˻�
#define CASHITEM_EXPSP_LIMIT_BUG
#define LACARETTE_SYSTEM
#define DUNGEON_TIME_SAVEFILE	".dungeontime"	// ����Ÿ�� ���� ���� ����.

//#define XTRAP
#define	_COMPOSITE_ITEM_UPGRADE_BUG_FIX
#define CHECK_CASTLE_AREA						// �������� üũ �ȵǴ� ���� ����
#define BUGFIX_WARP_TO_WARZONE								// ��ȯ������ �������� �̿��Ͽ� �������� �̵��Ұ�
#define TIME_IN_WARCASTLE_BUG_FIX				// ������ �ڷ�Ű�׽ý� ��ų �������� ����
#define NEW_DOUBLE_GM_AUTO
#define QA_RANGESKILL_APET_DAMAGE				// PC ������ų���� APET ������ ����
#define TRADE_AGENT_LOG_SPEED_CHECK
#define ENABLE_SUBJOB							// ����
#define BUGFIX_DROPITEM_LEVEL_CHECK				//
#define MEREC_CASTLE_TEST_GUILD_LEVEL_GM_SETTING
#define PASSWORD_ENCRYPT_SHA256
#define DEV_SYSTEM_SKILL_EXTEND_2ND
#define BUGFIX_USE_SKILL_TO_NPC
#define BUGFIX_TRADEAGENT_COPY
#define CONTINENT_PARTY_RECALL
#define BUGFIX_DRATAN_CRISTAL_RESPOND
#define UPDATE_CHAOS_TIME_ALWAYS
#define BUGFIX_CASHSHOP_PURCHASE_CONFIRM
#define DISABLE_TRADEAGENT_CHECKCALC
#define BUGFIX_GUILD_SKILL_COOLTIME			// ��彺ų ��Ÿ�� ���ҿɼ� ����ȵǰ� ����
#define WARCASTLE_STATE_CHANNEL_CYNC	// ���� ���¸� Ÿ ä�ΰ� cync �ϴ� ������ �߰�.
#define	WARCASTLE_MOVE_MESSAGE_LIMIT	// ������ �̵� �޽��� �˾�â ����.
#define GAMIGO_CASH_AUTHENTICATION_CODE_USE // authentication code�� ����� ĳ�� ���� �������� ���� (���̰� ��û)
#define SYSTEM_TREASURE_MAP                                 // ���� ã�� �ý���
#define GM_TREASURE_MAP_SAVE_FILE ".treasuremapsave"
#define SYSTEM_TREASURE_MAP_LINKZONE_DROP                    // ���� ���� ���� ���
#define DEV_LETS_PARTYTIME									// ��Ƽ�� ������
#define JUNO_RENEWAL_MESSAGEBOX								// ���Ͽ�, �ű�ĳ���� �̵� �� ���� ���ٰ� ����ũ�� ����.
#define BUGFIX_WARCASTLE_REGEN						// ��Ȱ���� �����ð� ����
#define BUGFIX_ITEMSELL_HACKUSER					// �������ǸŽ� ������ ī��Ʈ �˻� �߰�
#define BUGFIX_REFINE_SPECIAL_ITEM					// 128���� ������ ��ȯ�� 100% �������ü����� �ִ� ���� ����. ���� �Ȱ��� ó���ϵ��� ����.
#define UPGRADE_EVENT_AUTO			// ���׷��̵� �̺�Ʈ �ڵ�ȭ
#define UPGRADE_EVENT_AUTO_SAVEFILE		".upgradeevent"
#ifdef EXTREME_CUBE
#define EXTREME_CUBE_VER2								// �ͽ�Ʈ�� ť�� ���� (����2)
#endif
#define SYSTEM_MONSTER_MERCENARY_CARD_EX						// ���� �뺴�� ������ ���� ��� �߰�
#define SYSTEM_TREASURE_MAP_GAMIGO							// ���̰���û : ���������� �κ��� ������ �־�� �������ڰ� ���. 1000���� ��������� 1���� Ȳ�ݿ��� ��ȯ.
#define BUGFIX_DONT_USE_GET_FIRST_PARTY			// �Լ��켱 ��Ƽ�� �����Կ��� ����
#define REFORM_PK_PENALTY_201108
#define DEV_GUILD_MARK		// ��� ��ũ
#define DEV_GUILD_STASH		// ��� â��
#define NOTICE_SYSTEM		// ���� �ý���
#define GUILD_REMOTE_INVITE		// ��� ���� ���� �ý���
#define BUGFIX_REMOVE_SPACE
#define NO_PERIOD_COMPOSITE
//#define GUILD_MEMBER_KICK_JOIN_DELAY						// ������ ű�ϸ� 3�ϵ��� �ٸ� ��忡 �������� ���ϵ��� ����.
#define IP_NATION_CHECK
#define RECOMMEND_SERVER_LEVEL          30
#define DEFAULT_NAS_PERCENT             100             // ���� ���Ȯ�� ����
#define DEFAULT_PRO_PERCENT             100             // ���� ���� Ȯ�� ����
#define GAMIGO_ITEM_COUNT_HACK_DELETE					// ������ ī��Ʈ�� ������Ű�� ��ŷ�� ����. 10���� ������ ĳ���Ͱ� �α� �ƿ� �Ҷ� ī��Ʈ�� �Ǵ� �������� �ϳ��� �κ��� ������ ������ ���� ó��.
#define IMP_SPEED_SERVER						// ���ǵ� ����
#define EX_ROGUE	// EX �α� ĳ����
#define ASSIST_DECREASE_SKILL_MP
#define ASSIST_REDUCE_SKILL
#define SKILL_TYPE_NO_COOL_TIME
#define EX_MAGE

#define PARTY_QUEST_ITEM_BUG_			// ��Ƽ ����Ʈ ������ ������ ���� �ʴ� ����
#define HUNT_QUEST_COMPLETE_FOR_OTHER_PARTYMEMBER	//��Ƽ���� �� ����Ʈ ���ֱ�(�� ����ָ� ī��Ʈ �ǰ� ��. ������ ��Ƽ���� ������ ���� �־�� ���� �Ǿ���)
#define GIVE_ITEM_IN_CHANGE_JOB


////// ���̰� ĳ�� ���� �ڵ� ������ ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef GAMIGO_CASH_AUTHENTICATION_CODE_USE // authentication code�� ����� ĳ�� ���� �������� ���� (���̰� ��û)

#if defined(LC_GER)
#define LCOAL_GAMIGO_GROUP_ID			19
#define LOCAL_AUTHENTICATION_SECRETCODE "b8779493de6958e68fc422a58daf713e"
#elif defined(LC_SPN)
#define LCOAL_GAMIGO_GROUP_ID			37
#define LOCAL_AUTHENTICATION_SECRETCODE "643debd2620d19013e0b918af6bd749a"
#elif defined(LC_FRC)
#define LCOAL_GAMIGO_GROUP_ID			36
#define LOCAL_AUTHENTICATION_SECRETCODE "2fbbbf178046c7634fc8bad1c81f6bab"
#elif defined(LC_PLD)
#define LCOAL_GAMIGO_GROUP_ID			38
#define LOCAL_AUTHENTICATION_SECRETCODE "1088d561108d0c46dda33cfcffc2c1f0"
#elif defined(LC_TUR)
#define LCOAL_GAMIGO_GROUP_ID			68
#define LOCAL_AUTHENTICATION_SECRETCODE "14143358d9b27eb222588745da79eb6e"
#elif defined(LC_ITA)
#define LCOAL_GAMIGO_GROUP_ID			66
#define LOCAL_AUTHENTICATION_SECRETCODE "47bb626b57e501d786b1f3264aa8b260"
#elif defined(LC_LND)
#define LCOAL_GAMIGO_GROUP_ID			83
#define LOCAL_AUTHENTICATION_SECRETCODE "f46e5007701f1a5047e3e72321795ef"
#elif defined(LC_UK)
#define LCOAL_GAMIGO_GROUP_ID			19
#define LOCAL_AUTHENTICATION_SECRETCODE "b8779493de6958e68fc422a58daf713e"
#endif

#endif

#endif
