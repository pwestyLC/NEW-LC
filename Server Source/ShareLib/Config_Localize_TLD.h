#ifdef LC_TLD

//#define JUNO_RENEWAL_MESSAGEBOX					// ?????, ???ĳ???? ??? ?? ???? ????? ??????? ????.
//#define SERVER_AUTHENTICATION		// ???? ?? ???? ?y???
//#define GIVE_ITEM_IN_CHANGE_JOB		// ?????? ?????? ???????
//#define INTERGRATION_SERVER


//#define PLAYERLIST //fix bug with thai names.
#define FREE_PK_SYSTEM
#define RAID_MONSTER_SKIP_STONE

#define MONSTER_COMBO_FIX
#define DYNAMIC_DUNGEON_BUG_FIX							// 테오스 무덤에서 스킬 사용 시 몹의 체력이 복구 되어지는 것처럼 보여지는 현상. maxHP reset으로 인해 그런것 처럼 보임.
#define ATTACK_LIST_BUG_FIX	
#define TLD_EVENT_SONG
#define RANKER_NOTICE 
#define DYNAMIC_DUNGEON_BUG_FIX		
#define ASSIST_DECREASE_TIME_BUG_FIX 	// 버프 시간 동기화, 광속(그외 스킬 포함) 버프 클라이언트와 서버 시간 안맞는 것 수정(권상욱).
#define BUGFIX_SPECIALBOX_DROPRATE     // 스페셜 상자 아이템 확률 프로세스 변경
#define BUGFIX_DEAD_AGAIN_DEAD			// 마을에 와서 한번더 죽는 문제 마을에서 3초간 무적으로 함.
#define STASH_PASSWORD
#define FREE_PK_SYSTEM          // 새로운 PK Server Open //kimpobin
#define DISCONNECT_HACK_CHARACTER
#define GMTOOL //kimpobin
#define MONSTER_COMBO_FIX //kimpobin 
#define BATTLE_PARTY_BOSS_CHANGE	 //kimpobin	// 전투파티 시 파티장 변경에 대한 조건 검사
#define CASHITEM_EXPSP_LIMIT_BUG
#define	_COMPOSITE_ITEM_UPGRADE_BUG_FIX
#define BUGFIX_WARP_TO_WARZONE								// 소환마법서 아이템을 이용하여 공성지역 이동불가
#define TIME_IN_WARCASTLE_BUG_FIX				// 공성중 텔레키네시스 스킬 못쓰도록 막음
#define QA_RANGESKILL_APET_DAMAGE				// PC 범위스킬사용시 APET 데미지 막음
#define TRADE_AGENT_LOG_SPEED_CHECK
#define BUGFIX_DROPITEM_LEVEL_CHECK				//
#define MEREC_CASTLE_TEST_GUILD_LEVEL_GM_SETTING
#define BUGFIX_TRADEAGENT_COPY
#define BUGFIX_DRATAN_CRISTAL_RESPOND
#define UPDATE_CHAOS_TIME_ALWAYS
#define BUGFIX_CASHSHOP_PURCHASE_CONFIRM
#define DISABLE_TRADEAGENT_CHECKCALC
#define WARCASTLE_STATE_CHANNEL_CYNC	// 공성 상태를 타 채널과 cync 하는 명령이 추가.
#define	WARCASTLE_MOVE_MESSAGE_LIMIT	// 공성전 이동 메시지 팝업창 제한.
#define BUGFIX_REFINE_SPECIAL_ITEM					// 128레벨 아이템 변환시 100% 고급제련석으로 주는 버그 수정. 방어구와 똑같이 처리하도록 수정.
#define BUGFIX_DONT_USE_GET_FIRST_PARTY			// 입수우선 파티를 퀵슬롯에서 제거
#define BUGFIX_REMOVE_SPACE
#define GUILD_MEMBER_KICK_JOIN_DELAY						// 길드원을 킥하면 3일동안 다른 길드에 가입하지 못하도록 수정.
#define GAMIGO_ITEM_COUNT_HACK_DELETE					// 아이템 카운트를 증가시키는 해킹을 방지. 10레벨 이하의 캐릭터가 로그 아웃 할때 카운트가 되는 아이템이 하나만 인벤에 있으면 무조건 삭제 처리.
#define IMP_SPEED_SERVER						// 스피드 서버
#define GIVE_ITEM_IN_CHANGE_JOB		// 전직시 아이템 지급하기
////// ???? ??? ???? //////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


#define ITEM_NAME_FIELD         "a_name_thai"
#define NPC_NAME_FIELD          "a_name_thai"
#define ITEM_PRICE_FIELD        "a_price"
#define EVENT_ENABLE_FIELD      "a_enable_tld"
#define EVENT_EXTRA_FILED       "a_extra_tld"


////// IP ??? ???? ???? ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#define IP_BLOCK_AUTO
#if defined (IP_BLOCK_AUTO )
#define IP_BLOCKNOKICK_AUTO     // ?????? ??????? ??? ????? ??? ?α?? ????
#endif // #if defined (IP_BLOCK_AUTO )

////// ??? ???? ???? ???? /////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

////// OX QUIZ ???? ??? ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

#define OX_QUIZ_COUNTRY_CODE    4

////// 상시 이벤트 /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

////// ??????? ////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

//#define XTRAP

#define DROP_MAKE_DOCUMENT
#define DURABILITY
#define PREMIUM_CHAR
#define ENABLE_SUBJOB							// 상인

//#define MAX_LEVEL_CHARACTER 175
#define RECOMMEND_SERVER_POTION_INDEX   1393
#define RECOMMEND_SERVER_LEVEL          30
#define MAX_UPGRADE_PLUS    18          // 아이템 업그레이드 최대 플러스 수치
#define DISABLE_REFINE_SPECIAL_STONE    // 고급 제련석 교환 불가능

#define PARTY_QUEST_ITEM_BUG_			// ??? ????? ?????? ?????? ???? ??? ????
#define HUNT_QUEST_COMPLETE_FOR_OTHER_PARTYMEMBER	//??????? ?? ????? ?????(?? ?????? ???? ??? ??. ?????? ??????? ?????? ???? ???? ???? ?????)

#define NEW_DOUBLE_GM_AUTO
/*
#define DEFAULT_NAS_PERCENT     100      // 나스 드롭확률 조절
#define DEFAULT_NAS_GET_PERCENT 100     // 나스 습득량 조절
#define DEFAULT_EXP_PERCENT     100     // 경험치 획득량 조절
#define DEFAULT_SP_PERCENT      100     // sp 획득량 조절
#define DEFAULT_PRO_PERCENT     80      // 생산 습득 확률 조절
#define DEFAULT_PRO_GET_NUMBER  1       // 생산 습득 갯수
*/
#define RAID_NPC_RAGE_SKILL             394     // 레이드 몹 분노 스킬 인덱스
#define RAID_NPC_RAGE_SKILL_LEVEL       2       // 레이드 몹 분노 스킬 레벨
#define RAID_NPC_NOTICE_CELL_EXT        5
#define MAX_RARE_OPTION_SETTING         10      // ???? ???? ??? ???? ??
#define MAX_RARE_OPTION_ITEM            10      // ??????? ???? ??? ??
#define PULSE_MONSTER_RAID_MOVE     (14 * PULSE_REAL_MIN)   // ???? ????? ??? ?ð?

//#ifdef BILL_SERVER_VERSION
//#undef BILL_SERVER_VERSION
//#define BILL_SERVER_VERSION "TEnterBillV1.0"
//#define USE_TENTER_BILLING
//#endif


#define DOUBLE_PET_EXP
#define DOUBLE_ATTACK

#define EGEHA_ZONE_PAYMENT      500000	// ?????? ?????

#define KICK_PC_MULTI
#define SILENCE_PC_MULTI

//#define GUILD_MEMBER_KICK_JOIN_DELAY
#define EVENT_PACKAGE_ITEM

//#define MAX_NAME_LENGTH             24

#define DEFAULT_LIMIT_EXP           250

#define PULSE_GUILD_POINT_UPDATE        (5 * 60)    // ??? ????? ????? ???? ????

#define CHAT_BLOCK_USA
#define CHAT_BLOCK_USA_NEXT_TIME	5	// ???? ????? ??? ?ð?
#define CHAT_BLOCK_USA_LEVEL		1 // ????? ?????? ????

#define CHECKIP_USA

#define MONSTER_AI                      // ???? A.I
#define NO_CHATTING                     // a?? ????
#define EXTREME_CUBE                    // ?????? ???


#define NEW_DOUBLE_GM_SAVEFILE  ".doubleevent"      // DOUBLE EVENT 명령어 저장
#define DEFAULT_NAS_PERCENT     100     // 나스 드롭확률 조절
#define DEFAULT_NAS_GET_PERCENT 100     // 나스 습득량 조절
#define DEFAULT_EXP_PERCENT     100     // 경험치 획득량 조절
#define DEFAULT_SP_PERCENT      100     // sp 획득량 조절
#define DEFAULT_PRO_PERCENT     100     // 생산 습득 확률 조절
#define DEFAULT_PRO_GET_NUMBER  1       // 생산 습득 갯수

//#define TLD_DOUBLE_EVENT    3000 // 태국은 더블 이벤트 사용 시 300%까지 지원
//#define DOUBLE_ITEM_DROP    // 아이템 드롭 2배 이벤트
//#define DOUBLE_ITEM_DROP_SAVEFILE   ".doubleitemevent"      // DOUBLE EVENT 명령어 저장


#define HANARO_EVENT                    // 하나로 이벤트 2009   - 3채널로 변경해야 함  ...미국은 약간 수정


#define PET_TURNTO_NPC_ITEM

////////////////////  ?????  ////////////////////
////////////////////  ?????  ////////////////////


#define NO_PERIOD_COMPOSITE				// ????????? ?? ???? ???? ?????? ???


#define DISCONNECT_HACK_CHARACTER		// ?? ???α?? ???? ????


#define _BATTLEGROUP_QUEST_BUG_PIX		// [2010-05-19] ?????? ????? ???? ????(?????) : ?????? ?? ??? ? ĳ????? ??????? ?????? ???? ??? ???? ????.

#define LACARETTE_SYSTEM				// ????? ?y??? (??????2)

#define BUGFIX_ALLOW_EXPED_TYPE_SET

#define DUNGEON_TIME_SAVEFILE	".dungeontime"	// ??????? ???? ???? ????.







#define DEV_SYSTEM_SKILL_EXTEND_2ND			// ĳ???? ??? ??? 2??






#define CONTINENT_PARTY_RECALL				// ????? ??????? ?????? ???


#define RAIDBOX_DROP_COUNT_MODIFY		// ????? ???? ??? ??? ????

// ---------------- Update 1104 -----------------------
#ifdef EXTREME_CUBE
#define EXTREME_CUBE_VER2									// ???2
#endif // EXTREME_CUBE
#define SYSTEM_MONSTER_MERCENARY_CARD_EX
#define SYSTEM_MONSTER_MERCENARY_CARD_LOW_LEVEL_SUPPORT
// ---------------- Update 1104 -----------------------

// test server : [110506], live server : [110518]

// test server : [110526], live server : [110608]
#define DEV_LETS_PARTYTIME

// test server : [110603], live server : [110608]

// ---------------- Event ------------------
#define UPGRADE_EVENT_AUTO			// ???????? ???? ????
#define UPGRADE_EVENT_AUTO_SAVEFILE		".upgradeevent"


// --------------- BugFix -------------------
#define BUGFIX_USE_SKILL_TO_NPC





#define BUGFIX_GUILD_SKILL_COOLTIME		// ???? ????? ?????? ??????? ????



// test server : [110513], live server : [110518]

// test server : [110526], live server : [110608]


// test server : [110531], live server : [110608]
#define BUGFIX_WARCASTLE_REGEN									// ??????? ?????ð? ????

// test server : [110602], live server : [110608]
#define SYSTEM_TREASURE_MAP										// ???? a?? ?y???
#define SYSTEM_TREASURE_MAP_GAMIGO
#define GM_TREASURE_MAP_SAVE_FILE		 ".treasuremapsave"
#define SYSTEM_TREASURE_MAP_LINKZONE_DROP						// ???? ???? ???? ???

// test server : [110621], live server : [110622]
#define BUGFIX_ITEMSELL_HACKUSER

// [110630]


// [110919]

//#define REFORM_PK_PENALTY_201108
//#define FREE_PK_SYSTEM
//#define MAL_DISABLE_PKPENALTY

//////// UPDATE 1106 ////////
//////// UPDATE 121Q (12?? 4?? 26?? ) ////////

#define DEV_GUILD_MARK		// ??? ???
#define DEV_GUILD_STASH		// ??? a??

#define NOTICE_SYSTEM           // ???? ?y???

#define GUILD_REMOTE_INVITE		// ??? ???? ???? ?y???

#define BCRYPT_USA // ??? BCRPYT ????
//////// UPDATE 121Q-1 (12?? 4?? 26?? ) ////////
 #define EX_ROGUE	// EX ?α? ĳ????
#define ASSIST_DECREASE_SKILL_MP
#define ASSIST_REDUCE_SKILL
#define SKILL_TYPE_NO_COOL_TIME
#define EX_MAGE
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
#define TLD_DOUBLE_EVENT    600 // 태국은 더블 이벤트 사용 시 300%까지 지원
#define DOUBLE_ITEM_DROP    // 아이템 드롭 2배 이벤트
#define DOUBLE_ITEM_DROP_SAVEFILE   ".doubleitemevent"      // DOUBLE EVENT 명령어 저장
#define TLD_EVENT_SONG //dethunter12 add 
#define HACKING_PET_FIX
//dethunter12 defines
////// ???? ???? ???? ////////////////////////////////////////////////////////////////////////
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
