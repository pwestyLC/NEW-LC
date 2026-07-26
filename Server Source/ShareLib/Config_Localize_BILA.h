#define LC_BILA

#define JUNO_RENEWAL_MESSAGEBOX					// ���Ͽ�, �ű�ĳ���� �̵� �� ���� ���ٰ� ����ũ�� ����.
#define SERVER_AUTHENTICATION		// ���� �⵿ ���� �ý���
#define GIVE_ITEM_IN_CHANGE_JOB		// ������ ������ �����ϱ�

////// ���� �ʵ� ���� //////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#if defined (LC_BRZ)
#define ITEM_NAME_FIELD         "a_name_brz"
#define NPC_NAME_FIELD          "a_name_brz"
#define ITEM_PRICE_FIELD        "a_price"
#define EVENT_ENABLE_FIELD      "a_enable_brz"
#define EVENT_EXTRA_FILED       "a_extra_brz"
#elif defined (LC_MEX)
#define ITEM_NAME_FIELD         "a_name_mex"
#define NPC_NAME_FIELD          "a_name_mex"
#define ITEM_PRICE_FIELD        "a_price"
#define EVENT_ENABLE_FIELD      "a_enable_mex"
#define EVENT_EXTRA_FILED       "a_extra_mex"
#endif

////// IP �ڵ� ���� ���� ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#define IP_NATION_CHECK					// �α��� ����, ������ ������ ��� �������� Ȯ���ϰ� t_users�� �����.

////// �ؿ� ���� ���� ���� /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef LC_MEX
#define INTERNATIONAL_LOCAL_ACCESS_RESTRICTIONS			// IP ����
#endif // #ifdef LC_MEX

////// OX QUIZ ���� �ڵ� ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#if defined (LC_BRZ)
#define OX_QUIZ_COUNTRY_CODE    10
#elif defined (LC_MEX)
#define OX_QUIZ_COUNTRY_CODE	20
#endif

////// ��� �̺�Ʈ /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#define EVENT_TREASUREBOX               1	// �������� �̺�Ʈ
#define HANARO_EVENT		59				// [2010-05-19 T-Srv] �߽��ڿ� ������� Ʋ����.

#define DOUBLE_PET_EXP						// �� ����ġ �̺�Ʈ �ڵ�ȭ
#ifdef DOUBLE_PET_EXP
#define DOUBLE_PET_EXP_AUTO
#define DOUBLE_PET_EXP_SAVEFILE	".doublepetexp"
#endif

////// ������Ʈ �ý��� /////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#define XTRAP

#define BUGFIX_GUILD_SKILL_COOLTIME
#define DROP_MAKE_DOCUMENT
#define DURABILITY
#define PREMIUM_CHAR
#define NO_PERIOD_COMPOSITE						// ���վ����� �� �Ⱓ�� ���� ������ �߰�
#define ENABLE_SUBJOB							// ����

#define SETTING_IF_INNER_IP_NEW			// �ܺ� �����ǿ� ���� �����ǰ� ������ ��� ...yhj

#define RECOMMEND_SERVER_POTION_INDEX   1393
#define RECOMMEND_SERVER_LEVEL          30

#define MAX_UPGRADE_PLUS    25          // ������ ���׷��̵� �ִ� �÷��� ��ġ
#define DISABLE_REFINE_SPECIAL_STONE    // ���� ���ü� ��ȯ �Ұ���

#define PARTY_QUEST_ITEM_BUG_			// ��Ƽ ����Ʈ ������ ������ ���� �ʴ� ����
#define HUNT_QUEST_COMPLETE_FOR_OTHER_PARTYMEMBER	//��Ƽ���� �� ����Ʈ ���ֱ�(�� ����ָ� ī��Ʈ �ǰ� ��. ������ ��Ƽ���� ������ ���� �־�� ���� �Ǿ���)


#define DEFAULT_NAS_PERCENT     50      // ���� ���Ȯ�� ����
#define DEFAULT_NAS_GET_PERCENT 100     // ���� ���淮 ����
#define DEFAULT_EXP_PERCENT     100     // ����ġ ȹ�淮 ����
#define DEFAULT_SP_PERCENT      100     // sp ȹ�淮 ����
#define DEFAULT_PRO_PERCENT     80      // ���� ���� Ȯ�� ����
#define DEFAULT_PRO_GET_NUMBER  1       // ���� ���� ����


#ifdef BILL_SERVER_VERSION              // ����� �׽�Ʈ��
#undef BILL_SERVER_VERSION
#define BILL_SERVER_VERSION "TEnterBillV1.0"
//#define USE_TENTER_BILLING
#endif

#define NEW_ACCERY_ADD              // ���ο� �Ǽ��縮 4��

#define ENABLE_ROGUE_SKILL125_BRZ

#define RAID_NPC_RAGE_SKILL             394     // ���̵� �� �г� ��ų �ε���
#define RAID_NPC_RAGE_SKILL_LEVEL       2       // ���̵� �� �г� ��ų ����
#define RAID_NPC_NOTICE_CELL_EXT        5
#define MAX_RARE_OPTION_SETTING         10      // ���� �ɼǴ� �ɼ� ���� ��
#define MAX_RARE_OPTION_ITEM            10      // �����۴� ���� �ɼ� ��
#define PULSE_MONSTER_RAID_MOVE     (14 * PULSE_REAL_MIN)   // ���� ���̵� �̵� �ð�


#define PET_TURNTO_NPC_ITEM
#define EVENT_DROPITEM      // ����� ��û ��� ���ɾ�

#define DEFAULT_LIMIT_EXP 250

#define BRZ_FAIL_PASSWORD

#define PULSE_GUILD_POINT_UPDATE        (5 * 60)    // ��� ��ų�� ����ġ ���� ����


#define EVENT_PCBANG_2ND




//#define DISCONNECT_HACK_CHARACTER     // �� ���α׷� ���� ����



#define MONSTER_AI                      // ���� A.I
#define EXTREME_CUBE                    // �ͽ�Ʈ�� ť��
#define	ENDGAME_COUNTDOWN_ADD			// ��� ���ɾ� endgame�� 10�� ����� ī��Ʈ

// UPDATE14
//#define RESTRICT_PVP_SKILL         3			// [2010/11/02] ��û�� ���� ��� ����  // ������ ��ų ��Ģ : ���� Ÿ���� �Ǿ� ���� ���, PK���, ������� ��� �κ�/������� �Ұ���
// ������ ���ܿ��� �κ�������Ƽ�� �Ƚ������� �־�� �ϴ� define



//----- BRZ - MEX COMMON SETTING :: START ------//



//	## 2010-10-25

#define	_COMPOSITE_ITEM_UPGRADE_BUG_FIX // 2010-04-06 ���վ����� ���׷��̵� ���� ��ġ

// ##### LiveSrv : 2010-10-14 ( Test : 2010-10-11 )
#define EGEHA_ZONE_PAYMENT		     500000		// �����̽þ� ������ ��� 500,000��� ����

// ##### LiveSrv : 2010-11-9/10 (Test : 2010-11-02 )
#define FREE_PK_SYSTEM	// ��û�� ���� �߰�

// ##### update 1005-1,2 :: LiveSrv 2010-10-14 ( TestSrv 2010-09-20 ) // ����� ���� ��
// ##### update 1005-1,2 :: LiveSrv 2010-11-23 ( TestSrv 2010-11-11 ) // �߽��� ���� ��
#define LACARETTE_SYSTEM						// ��ī��

#define DUNGEON_TIME_SAVEFILE	".dungeontime"	// ����Ÿ�� ���� ���� ����.

#define LOW_LEVEL_SUPPORT_QUEST					// �ʺ����� ����Ʈ

// ##### LiveSrv 2010-11-23 ( TestSrv 2010-11-11
#define CHECK_CASTLE_AREA						// �������� üũ �ȵǴ� ���� ����

// ##### LiveSrv 2010-11-10 ( TestSrv 2010-10-29 ) // �����
// ##### LiveSrv 2010-12-24 ( TestSrv 2010-11-22 ) // �߽���

// ##### LiveSrv 2010-12-21 ( TestSrv 2010-11-22 ) :: 1006, 1007, 1008  �߽���
// ##### LiveSrv 2010-12-22 ( TestSrv 2010-11-23 ) :: 1006, 1007, 1008  �����

///// BRZ 110217-110222
///// MEX 110216-110228
#define DONT_USE_ATTACK_ACTION			// �����û���� �� ���� ���� ���� �׼��� ������ ����. ���� �׼��� �����ϵ��� ���´�.

///// BRZ 110224-110330
///// MEX 110224-110308
#ifdef IP_NATION_CHECK
#define LOCAL_LOGIN_LOG				// ���� ������ �α� DB�� �����
#endif

///// BRZ 110224-110330
///// MEX 110224-110308


#define UPGRADE_EVENT_AUTO			// ���׷��̵� �̺�Ʈ �ڵ�ȭ
#define UPGRADE_EVENT_AUTO_SAVEFILE		".upgradeevent"




///// BRZ 110406-110412
///// MEX 110407-110413

///// BRZ 110414-110420
///// MEX 110414-110419
//#define EVENT_EGGS_HUNT_BILA			// ����� ��Ȱ�� �ް��� ������ ������ �� �ִ�.

///// BRZ 110421-110427
///// MEX 110420-110426

//// BRZ 110502-110518
//// MEX 110502-110517
//// �̴���Ű��

#define WARCASTLE_MOVE_MESSAGE_LIMIT	// ������ �̵� �޽��� �˾�â ����

//// BRZ 110519-110525
//// MEX 110518-110524
#define GM_COMMAND_NOTICE				// GM COMMAND kick, Silence ��� ��, ������ �˸�

//// BRZ 110526-110601
//// MEX 110525-110531

//// MEX 110610-110614
//// BRZ 110610-110615

//// MEX 110617-110621
//// BRZ 110617-110622
#define BUGFIX_REMOVE_SPACE				// config ���� �ε� ��, ���� ���� ���� �� ����

//// MEX 110622-110712
//// BRZ 110623-110713
//// UPDATE 1104 - 1105
#ifdef EXTREME_CUBE
#define EXTREME_CUBE_VER2									// ť��2
#endif // EXTREME_CUBE
#define SYSTEM_MONSTER_MERCENARY_CARD_EX
#define SYSTEM_TREASURE_MAP									// ���� ã�� �ý���
#define SYSTEM_TREASURE_MAP_GAMIGO
#define GM_TREASURE_MAP_SAVE_FILE    ".treasuremapsave"
#define SYSTEM_TREASURE_MAP_LINKZONE_DROP                     // ���� ���� ���� ���
#define DEV_LETS_PARTYTIME										// ��Ƽ�� ������


//// BUG_FIX
#define BUGFIX_REFINE_SPECIAL_ITEM								// 128���� ������ ��ȯ�� 100% �������ü����� �ִ� ���� ����. ���� �Ȱ��� ó���ϵ��� ����.


// ================================================================================================================
//// UPDATE 1106 (MEX : 111109-111122)(BRZ : 111110-111130)


#define REFORM_PK_PENALTY_201108



#define BILA_RECOMMEND_SERVER_REWARD_CHANGE			// ITS : 6364 ���� ��õ ���� �̺�Ʈ ���� ���� ([2846]ī���� �� 10��)

#define INTERGRATION_SERVER
#define BILA_INTERGRATION_SERVER					// �߽���, ����� ���� ����
#define INTERGRATION_BRAZIL		10
#define INTERGRATION_MEXICO		20

#define IMP_SPEED_SERVER							// ITS : 6502, 6503, 6505 ���ǵ� ����

#define BILA_DUNGEON_TIME_EXP_CHANGE				// ITS : 6504 ���� Ÿ�� �� �߰� (29, 30)

//// week02_120125
#define NEW_DOUBLE_GM_AUTO

#define NEW_DOUBLE_EVENT_AUTO

#ifdef NEW_DOUBLE_EVENT_AUTO
#define NEW_DOUBLE_EVENT_AUTO_TIME
#ifdef NEW_DOUBLE_EVENT_AUTO_TIME
#define NEW_DOUBLE_EVENT_AUTO_SAVEFILE ".doubleeventautotime"
#endif
#endif

#define EVENT_ITEMDROP_AUTO
#ifdef EVENT_ITEMDROP_AUTO
#define EVENT_ITEMDROP_AUTO_SAVEFILE ".eventitemdropauto"
#endif

#define GM_EXP_LIMIT_AUTO
#ifdef GM_EXP_LIMIT_AUTO
#define GM_EXP_LIMIT_AUTO_SAVEFILE ".explimitsave"
#endif
#define CASH_SHOP_NO_GIFT_BILA

//////// UPDATE 121Q (12�� 1�� 3�� ) ////////

#define DEV_GUILD_MARK		// ��� ��ũ
#define DEV_GUILD_STASH		// ��� â��

#define NOTICE_SYSTEM		// ���� �ý���

#define GUILD_REMOTE_INVITE		// ��� ���� ���� �ý���

#define EX_ROGUE	// EX �α� ĳ����
#define ASSIST_DECREASE_SKILL_MP
#define ASSIST_REDUCE_SKILL
#define SKILL_TYPE_NO_COOL_TIME
#define EX_MAGE
// ================================================================================================================

//------ BRZ - MEX COMMON SETTING :: END ------//

//------ Test define :: start -----//

#define MEREC_CASTLE_TEST_GUILD_LEVEL_GM_SETTING	// �޶�ũ ���� ��û ��� ���� GM ���ɾ�

//------ Test define :: end   -----//

//------ Brazil define (����� ����) :: start   -----//

#ifdef LC_BRZ

#endif //LC_BRZ

//------ Brazil define (����� ����) :: end   -----//

//------ Mexico define (�߽��� ����) :: start   -----//

#ifdef LC_MEX

#endif //LC_MEX

//------ Mexico define (�߽��� ����) :: end   -----//

////// ��� ���� ���� ////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#define     GM_LEVEL_ECHO               8
#define     GM_LEVEL_GO_ZONE            3
#define     GM_LEVEL_GOTO               3
#define     GM_LEVEL_ITEMDROP           10
#define     GM_LEVEL_COUNT_PC           10
#define     GM_LEVEL_LOOPCOUNT          10
#define     GM_LEVEL_IMMORTAL           3
#define     GM_LEVEL_SHUTDOWN           9
#define     GM_LEVEL_REBOOT             9
#define     GM_LEVEL_COUNT_NPC          9
#define     GM_LEVEL_VISIBLE            3
#define     GM_LEVEL_GO_PC              3
#define     GM_LEVEL_GO_NPC             3
#define     GM_LEVEL_LEVELUP            8

#ifdef GM_COMMAND_NOTICE
#define     GM_LEVEL_KICK               1
#else
#define     GM_LEVEL_KICK               5
#endif	// GM_COMMAND_NOTICE

#define     GM_LEVEL_COMON              8
#define     GM_LEVEL_SUMMON             9

#ifdef GM_COMMAND_NOTICE
#define     GM_LEVEL_SILENCE            1
#else
#define     GM_LEVEL_SILENCE            5
#endif	// GM_COMMAND_NOTICE

#define     GM_LEVEL_WHERE_AM_I         3
#define     GM_LEVEL_QUEST_COMPLETE     7
#define     GM_LEVEL_STATPOINT          7
#define     GM_LEVEL_SKILLPOINT         7
#define     GM_LEVEL_SET_REGENSEC       8
#define     GM_LEVEL_NPC_REGEN          8
#ifdef GM_COMMAND_NOTICE
#define     GM_LEVEL_KILL_NPC           2
#else
#define     GM_LEVEL_KILL_NPC           1
#endif
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
#ifdef GM_COMMAND_NOTICE
#define		GM_LEVEL_DATE				2
#else
#define		GM_LEVEL_DATE				1
#endif
#define		GM_LEVEL_PLAY_TRIGGER		10
#define		GM_LEVEL_BATTLE_START		10
#define		GM_LEVEL_BATTLE_STOP		10
#define		GM_LEVEL_RESET_RAID			10
#define		GM_LEVEL_SET_SEAL_EXP		10
#define		GM_LEVEL_END_SUBHELPER		10
#define		GM_LEVEL_LCBALL_RESET		10
#define		GM_LEVEL_ECHONPC			9
#define		GM_LEVEL_DT_EXPSET			9
#define     GM_LEVEL_ITEMGET			10
#define		GM_LEVEL_ITEMGETRANGE		10
#define		GM_LEVEL_JOBRESET			10
#define		GM_LEVEL_JOBCHANGE			10
