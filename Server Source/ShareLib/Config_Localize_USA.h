#ifdef LC_USA

//#define JUNO_RENEWAL_MESSAGEBOX					// ���Ͽ�, �ű�ĳ���� �̵� �� ���� ���ٰ� ����ũ�� ����.
//#define SERVER_AUTHENTICATION		// ���� �⵿ ���� �ý���
//#define GIVE_ITEM_IN_CHANGE_JOB		// ������ ������ �����ϱ�
//#define INTERGRATION_SERVER

#if defined (INTERGRATION_SERVER)
#define INTERGRATION_USA 9
#define INTERGRATION_BRZ 10
#define INTERGRATION_GER 13
#define INTERGRATION_SPN 14
#endif
//#define WARFARE_START
////// ���� �ʵ� ���� //////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
#define		STASH_PASSWORD
#ifdef LC_USA
#define ITEM_NAME_FIELD         "a_name_usa"
#define NPC_NAME_FIELD          "a_name_usa"
#define ITEM_PRICE_FIELD        "a_price"
#define EVENT_ENABLE_FIELD      "a_enable_usa"
#define EVENT_EXTRA_FILED       "a_extra_usa"
#endif // LC_USA
#define BATTLE_PARTY_BOSS_CHANGE  //pwesty
////// IP �ڵ� ���� ���� ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#define IP_BLOCK_AUTO
#if defined (IP_BLOCK_AUTO )
#define IP_BLOCKNOKICK_AUTO     // ������ ������� �϶� ű���� �ʰ� �α׸� ����
#endif // #if defined (IP_BLOCK_AUTO )

////// �ؿ� ���� ���� ���� /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

////// OX QUIZ ���� �ڵ� ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#define OX_QUIZ_COUNTRY_CODE    9

//#define LOGO_HALLOWEEN
//#define LOGO_XMAS

////// ��� �̺�Ʈ /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

////// ������Ʈ ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

//#define XTRAP
//#define IMP_SPEED_SERVER
#define DROP_MAKE_DOCUMENT
#define PREMIUM_CHAR
#define DURABILITY
#define OFFLINE_SHOPS							// Offline personal shops (CPC keep-alive vendors, sales log, settlement mail, Discord notify)
#define ENABLE_SUBJOB							// ����
#define EVENT_DOUBLE

#define WINS_LOSES
#define EVENT_SUMMON
//#define GRIND_EXP_LEVEL
//#define AUTO_SKILL
#define ENABLE_DUNGEON_TIME
//#define PHOENIX_REQUIRE_LEVEL
//#define PHOENIX_BUFF_LEVEL_REQUIRED
//#define SKILL_SOUL
#define ROYAL_RUMBLE
#define GIFT_MAIL_REWARD
#define RETURN_REWARD
//#define AUTO_GOD_BLESS

//#define WARFARE_BATTLE
#define ALTAR_SUMMON_EASY_PILLAR
#define DUNGEON_TIME_GOLD_INCREASE // alan
//#define WAR_CASTLE_BUFF
//#define SOUL_BUFF_ONLY_OWNER
//#define AUTO_OPEN_CALENDAR
#define RANKER_NOTICE
#define BATTLE_PASS_SYSTEM
#ifdef BATTLE_PASS_SYSTEM
#define MAX_BATTLE_PASS_LEVEL 30 //was 10
//#define ENABLE_NPC_BATTLE_PASS
#define ARENA_TIME_SYSTEM
#define BATTLE_PASS_PREMIUM_ITEM_INDEX 12196
#endif
#define SKCD_425
#define CLOUD_AUTO_QUEST_DELIVERY	//Cloud auto quest
#define MAX_LEVEL_CHARACTER 140
#define RECOMMEND_SERVER_POTION_INDEX   1393
#define RECOMMEND_SERVER_LEVEL          30
#define MAX_UPGRADE_PLUS    25          // ������ ���׷��̵� �ִ� �÷��� ��ġ

#define DISABLE_REFINE_SPECIAL_STONE    // ���� ���ü� ��ȯ �Ұ���

#define PARTY_QUEST_ITEM_BUG_			// ��Ƽ ����Ʈ ������ ������ ���� �ʴ� ����
#define HUNT_QUEST_COMPLETE_FOR_OTHER_PARTYMEMBER	//��Ƽ���� �� ����Ʈ ���ֱ�(�� ����ָ� ī��Ʈ �ǰ� ��. ������ ��Ƽ���� ������ ���� �־�� ���� �Ǿ���)

#define NEW_DOUBLE_GM_AUTO
#define EXPANSION_INVENTORY
#define DEFAULT_NAS_PERCENT     50      // ���� ���Ȯ�� ����
#define DEFAULT_NAS_GET_PERCENT 100     // ���� ���淮 ����
#define DEFAULT_EXP_PERCENT     100     // ����ġ ȹ�淮 ����
#define DEFAULT_SP_PERCENT      100     // sp ȹ�淮 ����
#define DEFAULT_PRO_PERCENT     80      // ���� ���� Ȯ�� ����
#define DEFAULT_PRO_GET_NUMBER  1       // ���� ���� ����

#define RAID_NPC_RAGE_SKILL             394     // ���̵� �� �г� ��ų �ε���
#define RAID_NPC_RAGE_SKILL_LEVEL       2       // ���̵� �� �г� ��ų ����
#define RAID_NPC_NOTICE_CELL_EXT        5
#define MAX_RARE_OPTION_SETTING         10      // ���� �ɼǴ� �ɼ� ���� ��
#define MAX_RARE_OPTION_ITEM            10      // �����۴� ���� �ɼ� ��
#define PULSE_MONSTER_RAID_MOVE     (14 * PULSE_REAL_MIN)   // ���� ���̵� �̵� �ð�

//#ifdef BILL_SERVER_VERSION
//#undef BILL_SERVER_VERSION
//#define BILL_SERVER_VERSION "TEnterBillV1.0"
//#define USE_TENTER_BILLING
//#endif

#define BUGFIX_DEAD_AGAIN_DEAD
#define BUGFIX_DEAD_SECONDS 3
#define MAX_PLUS_MELDING    25
#define LIMIT_STAT_POINTS 20000

#define ARTIFACT_NOT_INCREASE_TIME

#define ALWAYS_USE_ITEM_REMOVE_DEBUFF
//#define MOVE_MONDSHINE_NO_QUEST

//#define NS_START_EGEHA
//#define BLOCK_MOUNT_NIGHTSHADOW

#define BLOCK_MAC_ADDR
#define GMCHECK
#define DOUBLE_PET_EXP
#define DOUBLE_ATTACK

#define EGEHA_ZONE_PAYMENT      500000	// ������ �����

#define KICK_PC_MULTI
#define SILENCE_PC_MULTI

//#define GUILD_MEMBER_KICK_JOIN_DELAY
//#define EVENT_PACKAGE_ITEM

#define MAX_NAME_LENGTH             24

#define DEFAULT_LIMIT_EXP           250

#define PULSE_GUILD_POINT_UPDATE        (5 * 60)    // ��� ��ų�� ����ġ ���� ����

#define CHAT_BLOCK_USA
#define CHAT_BLOCK_USA_NEXT_TIME	5	// ���� ��ĥ�� �ִ� �ð�
#define CHAT_BLOCK_USA_LEVEL		1 // ��ġ�� ������ ����

#define CHECKIP_USA

#define MONSTER_AI                      // ���� A.I
#define NO_CHATTING                     // ä�� ����
#define EXTREME_CUBE                    // �ͽ�Ʈ�� ť��

#define HANARO_EVENT                    // �ϳ��� �̺�Ʈ 2009   - 3ä�η� �����ؾ� ��  ...�̱��� �ణ ����


#define PET_TURNTO_NPC_ITEM

////////////////////  Ȯ����  ////////////////////
////////////////////  Ȯ����  ////////////////////


#define NO_PERIOD_COMPOSITE				// ���վ����� �� �Ⱓ�� ���� ������ �߰�


//#define DISCONNECT_HACK_CHARACTER		// �� ���α׷� ���� ����


#define _BATTLEGROUP_QUEST_BUG_PIX		// [2010-05-19] ������ ����Ʈ ���� ����(�ֿ���) : ������ �� ��Ÿ ģ ĳ���͸� ����Ʈ�� ������ ī��Ʈ �Ǵ� ���� ����.

#define LACARETTE_SYSTEM				// ��ī�� �ý��� (������2)

#define BUGFIX_ALLOW_EXPED_TYPE_SET

#define DUNGEON_TIME_SAVEFILE	".dungeontime"	// ����Ÿ�� ���� ���� ����.







#define DEV_SYSTEM_SKILL_EXTEND_2ND			// ĳ���� ��ų Ȯ�� 2��






#define CONTINENT_PARTY_RECALL				// ����� ��Ƽ���� ������ �߰�


#define RAIDBOX_DROP_COUNT_MODIFY		// ����� ���� ��� ��Ģ ����


#ifdef EXTREME_CUBE
#define EXTREME_CUBE_VER2									// ť��2
#endif // EXTREME_CUBE
#define SYSTEM_MONSTER_MERCENARY_CARD_EX
#define SYSTEM_MONSTER_MERCENARY_CARD_LOW_LEVEL_SUPPORT

#define DEV_LETS_PARTYTIME

#define UPGRADE_EVENT_AUTO			// ���׷��̵� �̺�Ʈ �ڵ�ȭ
#define UPGRADE_EVENT_AUTO_SAVEFILE		".upgradeevent"


#define BUGFIX_USE_SKILL_TO_NPC

#define BUGFIX_GUILD_SKILL_COOLTIME		// ��彺ų ��Ÿ�� ���ҿɼ� ����ȵǰ� ����

#define BUGFIX_WARCASTLE_REGEN									// ��Ȱ���� �����ð� ����


#define SYSTEM_TREASURE_MAP										// ���� ã�� �ý���
#define SYSTEM_TREASURE_MAP_GAMIGO
#define GM_TREASURE_MAP_SAVE_FILE		 ".treasuremapsave"
#define SYSTEM_TREASURE_MAP_LINKZONE_DROP						// ���� ���� ���� ���


#define BUGFIX_ITEMSELL_HACKUSER
#define REFORM_PK_PENALTY_201108
#define DEV_GUILD_MARK		// ��� ��ũ
#define DEV_GUILD_STASH		// ��� â��
#define NOTICE_SYSTEM           // ���� �ý���
#define GUILD_REMOTE_INVITE		// ��� ���� ���� �ý���
#define BCRYPT_USA // �̱� BCRPYT ����

#define EX_ROGUE	// EX �α� ĳ����
#define EX_MAGE
#define ASSIST_DECREASE_SKILL_MP
#define ASSIST_REDUCE_SKILL
#define SKILL_TYPE_NO_COOL_TIME
#define TLD_EVENT_SONG //dethunter12 add 
#define HACKING_PET_FIX
//dethunter12 defines
#define QUEST_COLLECT_MOD_10162021
#define HP_REDUCE_10222021
#define CAPTURE_THE_FLAG_10282021
#define LOG_DB_10292021
#define PET_EXP_ELIXER_11072021
#define PREMIUM_REFORMER_11072021
#define OPAL_MINUS_11132021
#define CUSTOM_OPTIONS_11182021
#define MULTI_EXCHANGE_11232021




/////pwesty shit///////
//#define DEMIGOD
#define REZAPCHA
#define REZABOT
#define PASSIVE_SYSTEM
#define FUNZONE
#define FUN_ZONE_PAYMENT           
#define ARENA_SPAWN
#define DARKTHEOSDEBUFFf
#define GMTOOL
#define PWESTY_ARENA_SYSTEM
////// MIHAV STUFF ///////
//#define AUTOPREMIUM
////// ��� ���� ���� ////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#define     GM_LEVEL_ECHO               1
#define     GM_LEVEL_GO_ZONE            3
#define     GM_LEVEL_GOTO               3
#define     GM_LEVEL_ITEMDROP           10
#define     GM_LEVEL_COUNT_PC           10
#define     GM_LEVEL_LOOPCOUNT          10
#define     GM_LEVEL_IMMORTAL           3
#define     GM_LEVEL_SHUTDOWN           10
#define     GM_LEVEL_REBOOT             10
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
#define     GM_LEVEL_KILL_NPC           3
#define     GM_LEVEL_EXPUP              8
#define     GM_LEVEL_BLOODPOINT         8
#define     GM_LEVEL_ENDGAME            10
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
#define     GM_LEVEL_KICK_PC_MULRI      8
#define     GM_LEVEL_SILENCE_PC_MULTI   8
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

#endif // LC_USA
