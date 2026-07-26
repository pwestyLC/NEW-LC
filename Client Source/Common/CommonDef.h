#ifndef		COMMON_DEF_H_
#define		COMMON_DEF_H_
#define		REZAPCHA
#define     DAILY_LOGIN
//pwesty shit
#define PASSIVE_SYSTEM
#define PRESTIGE_SYSTEM
#define SHOW_PROMO_KEY
//#define ADAPTER_VULKAN_INFO
#define     CLOUD_EXPEDITION_PARTY_DUNGEONS
#define		CLOUD_EXPEDITION_REWORK
//#define	RIGHT_MENU_ACTION
#define 	CEHACK
#define		REZABOT
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
#define CLOUD_EXPEDITION_REWORK
#define RECALL_STRING_IDX 9381 //exemple: Party Leader [%s] has started an Expedition, Do you want to move to the %s Expedition?
#endif
#define	PET_BUFF_ALL_SYSTEM
#define LIMIT_STAT_POINTS 5000

#define		PREMIUM_CHAR
#define		DURABILITY
#define		NAS_ITEM_DB_INDEX			(19)
#define		QUICK_PANEL
#define     CLOUD_NEW_WASD
//#define  	ANTICHEAT
#define CAPTURE_THE_FLAG
#if defined ADD_SUBJOB
	#define ENABLE_SUBJOB
#endif	//	ADD_SUBJOB
//#define AKAN_TEST_COMMAND //free look camera
#if defined GUILD_MARK
	#define DEV_GUILD_MARK
#endif	//	GUILD_MARK
#define		ARENA_TIME_SYSTEM

#define DEV_EXP_APET

#define		BATTLE_PASS_SYSTEM
#define 	ENABLE_HP_BAR
#define     DECRYPTXOR
#define     EXPANSION_INVENTORY
// �ӽ� define //////
#define WEARING_SHOW_END	6
#define MAX_GUILD_NAME_LENGTH 50
#define APET_WEARPOINT		4
#define MAX_SERIAL_LENGTH	20
#define MAX_SOCKET_COUNT	7
#define	MAX_ITEM_OPTION		5
#define MAX_ORIGIN_OPTION	6
#define	MAX_CHAR_NAME_LENGTH	50
#define	MAX_ID_NAME_LENGTH		64

#define NOTICE_PICKUP_ITEM
#ifdef NOTICE_PICKUP_ITEM
#define NOTICE_PICKUP_ITEM_MAX						5 // max show
#define NOTICE_PICKUP_ITEM_ICON_WIDTH				32 // icon width
#define NOTICE_PICKUP_ITEM_ICON_HEIGHT				32 // icon height
#define NOTICE_PICKUP_ITEM_ICON_POSITION			1 // 0 - left / 1 - right
#define NOTICE_PICKUP_ITEM_ICON_SHIFT_X				50 // icon shift along the axis X
#define NOTICE_PICKUP_ITEM_ICON_SHIFT_Y				140 // icon shift along the axis Y
#define NOTICE_PICKUP_ITEM_ICON_ICON_SHIFT			8 // vertical padding between icons
#define NOTICE_PICKUP_ITEM_FIDE_IN_TIME				1000 // fade in time (ms)
#define NOTICE_PICKUP_ITEM_FIDE_SHOW_TIME			5000 // show time (ms)
#define NOTICE_PICKUP_ITEM_FIDE_OUT_TIME			500 // fade out time (ms)
#define NOTICE_PICKUP_ITEM_BACK_PADDING				5 // background padding
#endif

#define		MEMPOS_COMMENT_LENGTH_RUS	25
#define		MEMPOS_COMMENT_LENGTH		32


typedef __int64		GoldType_t;

#define MAX_PWD_LENGTH				32
#define MAX_GUID_LENGTH				1000
#define     ENABLE_ADMIN_KICKBAN

#endif		// COMMON_DEF_H_