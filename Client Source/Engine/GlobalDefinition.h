// ----------------------------------------------------------------------------
//  File : GlobalDefinition.h
//  Desc : Created by Dongmin
// ----------------------------------------------------------------------------

#ifndef	GLOBALDEFINITION_H_
#define	GLOBALDEFINITION_H_

#include <Engine/Base/FileName.h>
#include <Engine/LocalDefine.h>
//0707
#define COMPRESSION_MESSAGE
#define SECRET_KEY

// EDIT : BS : 070413 : �ű� ��Ŷ ��ȣȭ
// EDIT : BS : ��Ŷ ��ȣȭ
#define CRYPT_NET_MSG
//#define CRYPT_NET_MSG_MANUAL	// ��Ŷ ��ȣȭ Ű ������ �������� �Կ� ���� ���� Ű�� ��ȣ�� �õ��� �� ����, DES3 ���Ĵ� ������ �ڵ��̹Ƿ� �ּ�ó�� �ؾ���
// ��ȣȭ lib ��ũ
#ifdef NDEBUG
#pragma comment(lib, "LCCrypt_mt.lib")
#else
#pragma comment(lib, "LCCrypt_mtd.lib")
#endif


#define START_WORLD		("Data\\world\\StartZone\\startzone.wld")  

#define LOGIN_EP1
//#define LOGIN_EP1
//#define LOGIN_EP4

// connie [2009/7/21] - login2
#define LOGIN_WORLD_EP1				("Data\\World\\LoginWorld\\LoginWorld.wld")
#define LOGIN_WORLD_EP2				("Data\\World\\LoginWorld2\\LoginWorld2.wld")
#define LOGIN_WORLD_EP4				("Data\\World\\LoginWorld3_bg_only\\LoginWorld3_bg_only.wld")

//---------------------------------------------------------------------
#define CLASS_ENEMY		("Classes\\enemy.ecl")
#define CLASS_ITEM		("Classes\\Items.ecl")
#define CLASS_PET		("Classes\\Pet.ecl")
#define CLASS_SUMMON	("Classes\\Slave.ecl")
#define CLASS_WILDPET	("Classes\\WildPet.ecl")

#define LORD_SYMBOL_INDEX			225
#define DRATAN_LORD_SYMBOL_INDEX	401			// WSS_DRATAN_SEIGEWARFARE 2007/07/30 ���� ũ����Ż
#define DRATAN_MASTER_TOWER_INDEX	351			// WSS_DRATAN_SEIGEWARFARE 2007/07/30 ������ Ÿ��
#define MOB_FLOWERTREE_INDEX		342
#define MOB_XMAS_TREE_DECO			486			// ũ�������� ��Ŀ�
#define MOB_XMAS_TREE_CENTER		484			// ũ�������� �����
#define GAMIGO_10TH_CAKE			1304		// [ldy1978220 2011/5/31] ���̰� 10�ֳ� �̺�Ʈ ���� 

// Check Attack Flag
#define ENF_EX2_PVP				(1L<<0)
#define ENF_EX2_LEGIT			(1L<<1)
#define ENF_EX2_MYPARTY			(1L<<2)
#define ENF_EX2_MYGUILD			(1L<<3)
#define ENF_EX2_ENEMYGUILD		(1L<<4)
#define ENF_EX2_WAR_OURFORCE		(1L<<5)
#define ENF_EX2_WAR_ENEMY		(1L<<6)
#define ENF_EX2_SAFEGUARD		(1L<<7)

//---------------------------------------------------------------------
// �������� ���� �޼��� ó�������� ���
#define		PLAYER_STATE_SUPPORTER		(1 << 9)	// ���� ������ �÷��� (Ư�� ������ ����� ����Ʈ)
#define		PLAYER_STATE_OTHERZONE		(1 << 10)	// �ٸ� �Ӽ��� ������ ������
#define		PLAYER_STATE_CRISTAL_RESPOND	(1 << 11)	// ���ź ���� ũ����Ż ������ // WSS_DRATAN_SEIGEWARFARE 2007/07/31
#define		PLAYER_STATE_FLYING			(1 << 12) // ������(����Ʈ������)
#define		PLAYER_STATE_DARKNESS		(1 << 13) // �絵���(����Ʈ������)
#define		PLAYER_STATE_SKILL			(1 << 14) // ��ų�ߵ����(����Ʈ������)
#define		HAIR_RED_CAP				10 // ���� ��Ÿ ����
#define		HAIR_GREEN_CAP				20 // ��� ��Ÿ ���� 
//--------------------enum zone name begin()--------------------
// zone no  = // ���� �̸�
enum eZoneName
{
	F_JUNO,		// 0 ��븶��
	D_BELFIST,	// 1 ���ǽ�Ʈ ����
	PD_STRAIA,	// 2 ��Ʈ���̾� ����( �۽��� )
	P_PROCYON,	// 3 ����Ű�� ����
	F_DRATAN,	// 4 ���ź �ʵ�
	PD_MINOC,	// 5 �̳�ũ ź��( �۽��� )
	T_STRAIA,	// 6 ��Ʈ���̾� ���� ( Ʃ�丮�� )
	F_MERAC,	// 7 �޶�ũ �ʵ�
	GUILD_ROOM,	// 8 ��� �����
	P_MARGADUM,	// 9 �������� ���� ����
	PD_AJAKA,	// 10 ����ī ����( �۽��� )
	PD_GATEofDIMENSION,	// 11 ������ �� ( �۽��� )
	P_TEMPLEofFORGETFULNESS, // 12 ������ ����
	PKZONE_MARGADUM,	// 13 �������� PK��( �±� )
	OXEVENT_ROOM,		// 14 OX �̺�Ʈ Ȧ
	F_EGEHA				// 15 ������ �ʵ�
};
//--------------------enum zone name end()----------------------
#if defined(PRESTIGE_SYSTEM)
enum eInfoLevelExpB {
	TITLE_LEVEL,
	TEXT_LEVEL,
	TITLE_EXP,
	TEXT_EXP,
	TOTAL_LABEL
};
#endif

/**#if defined(BATTLE_PASS_SYSTEM)
enum eInfoLevelExp {
	bTITLE_LEVEL,
	bTEXT_LEVEL,
	bTITLE_EXP,
	bTEXT_EXP,
	bTOTAL_LABEL
};
#endif*/

// Date : 2005-05-26(���� 10:40:39), By Lee Ki-hwan
// ���� ���� (�޽������� ���)
enum eCondition
{
	OFFLINE,		// ���Ӿ���		
	ONLINE,			// ������
	LEFT_POSITION,	// �ڸ����
	TOTAL_CONDITION,
};

//---------------------------------------------------------------------
// ���� ���.
enum eJob
{
	TITAN		= 0,	// Ÿ��ź
	KNIGHT		= 1,	// ���		
	HEALER		= 2,	// ����
	MAGE		= 3,	// ������
	ROGUE		= 4,	// �α�
	SORCERER	= 5,	// �Ҽ���
	NIGHTSHADOW	= 6,	// ����Ʈ ������
#ifdef CHAR_EX_ROGUE
	EX_ROGUE,			// [2012/08/27 : Sora] EX�α� �߰�
#endif
#ifdef CHAR_EX_MAGE		//2013/01/08 jeil EX ������ �߰� 
	EX_MAGE,
#endif
	TOTAL_JOB,			// �� ������ ����.
};

// [2010/08/27 : Sora] ADD_SUBJOB
enum eSubJob
{
	SUBJOB_MERCHANT = (1 << 0),	// ����
	TOTAL_SUBJOB = 1,
};

// Date : 2005-09-23(���� 5:24:56), By Lee Ki-hwan
// �ֿϵ����� ������ �ƴѵ� ��ų �����߿��� �����Ѵ�...
#define PET_JOB				10
#define WILDPET_JOB			11

// FIXME : ���� �ʿ� ����...
// ���� �� ����
enum eJob2
{
	JOB_2ND_HIGHLANDER		= 1,		// ���̷���
	JOB_2ND_WARMASTER		= 2,		// ��������
	JOB_2ND_ROYALKNIGHT		= 1,		// �ο�����Ʈ
	JOB_2ND_TEMPLEKNIGHT	= 2,		// ���ó���Ʈ
	JOB_2ND_ARCHER			= 1,		// ��ó
	JOB_2ND_CLERIC			= 2,		// Ŭ����
	JOB_2ND_WIZARD			= 1,		// ���ڵ�
	JOB_2ND_WITCH			= 2,		// ��ġ
	JOB_2ND_ASSASSIN		= 1,		// �ӽ��
	JOB_2ND_RANGER			= 2,		// ������

	JOB_2ND_ELEMENTALIST		= 1,		// ���� �� �޸�
	JOB_2ND_SPECIALIST		= 2,		// ���� �� �߼�

	JOB_2ND_NIGHTSHADOW		= 1,		// ����Ʈ������

#ifdef CHAR_EX_ROGUE
	JOB_2ND_EX_ASSASSIN		= 1,		// [2012/08/27 : Sora] EX�α� �߰�
	JOB_2ND_EX_RANGER		= 2,		// [2012/08/27 : Sora] EX�α� �߰�
#endif
#ifdef CHAR_EX_MAGE
	JOB_2ND_EX_WIZARD		= 1,		//2013/01/08 jeil EX ������ �߰� 
	JOB_2ND_EX_WITCH		= 2,		//2013/01/08 jeil EX ������ �߰� 
#endif
	/*
	JOB_2ND_HORSE			= 1,
	JOB_2ND_DRAGON			= 2,
	JOB_2ND_HORSE_M			= 3,
	JOB_2ND_DRAGON_M		= 4,
	*/
};

#define TOTAL_HEAD	(5)
#define TOTAL_HAIR	(5)

// Job Bit Mask
#define MASK_TITAN		(1 << TITAN)
#define MASK_MAGE		(1 << MAGE)
#define	MASK_HEALER		(1 << HEALER)
#define MASK_KNIGHT		(1 << KNIGHT)
#define MASK_ROGUE		(1 << ROGUE)
#define MASK_SOCERER	(1 << SORCERER)
#define MASK_NIGHTSHADOW (1 << NIGHTSHADOW)
#ifdef CHAR_EX_ROGUE	// [2012/08/27 : Sora] EX�α� �߰�
	#define MASK_EX_ROGUE	(1 << EX_ROGUE)
#endif
#ifdef CHAR_EX_MAGE		//2013/01/08 jeil EX ������ �߰� 
	#define MASK_EX_MAGE	(1 << EX_MAGE)
#endif

//---------------------------------------------------------------------
// Equipment
enum eEquipment
{
	WEAR_NONE					= -1,
	WEAR_HELMET					= 0,
	WEAR_JACKET					= 1,
	WEAR_WEAPON					= 2,
	WEAR_PANTS					= 3,
	WEAR_SHIELD					= 4,
	WEAR_GLOVES					= 5,
	WEAR_BOOTS					= 6,
	WEAR_ACCESSORY1				= 7,
	WEAR_ACCESSORY2				= 8,
	WEAR_ACCESSORY3				= 9,
	WEAR_ACCESSORY4				= 10,
	WEAR_PET					= WEAR_ACCESSORY4,
	WEAR_BACKWING				= 11,	// ����
	WEAR_ACCESSORY_ANYWHERE		= 12, // newslot - alanssoares
	WEAR_ACCESSORY_SPECIAL1		= 13, // newslot - alanssoares
	WEAR_ACCESSORY_SPECIAL2		= 14, // newslot - alanssoares
	WEAR_ACCESSORY_SPECIAL3		= 15, // newslot - alanssoares
	WEAR_ACCESSORY_SPECIAL4		= 16, // newslot - alanssoares
	WEAR_ACCESSORY_SPECIAL5		= 17, // newslot - alanssoares
	WEAR_TOTAL					= 18,	// ������ ���������� �� �Ǽ����� ���Կ� �Ǽ������� �����Ѵ�.
};

enum eWildPetWear
{
	WILDPET_WEAR_HEAD	= 0,
	WILDPET_WEAR_BODY	= 1,
	WILDPET_WEAR_WEAPON = 2,
	WILDPET_WEAR_ACCE	= 3,
	WILDPET_WEAR_TOTAL	= 4,
};

enum eCostumeEquipment
{
	WEAR_COSTUME_HELMET					= 0,
	WEAR_COSTUME_JACKET					= 1,
	WEAR_COSTUME_WEAPON					= 2,
	WEAR_COSTUME_PANTS					= 3,
	WEAR_COSTUME_SHIELD					= 4,
	WEAR_COSTUME_GLOVES					= 5,
	WEAR_COSTUME_BOOTS					= 6,
	WEAR_COSTUME_BACKWING				= 7,
	WEAR_COSTUME_TOTAL					= 8,
};

enum eAccessoryWear
{
	WEAR_ACCESSORY_1 = 0,
	WEAR_ACCESSORY_2 = 1,
	WEAR_ACCESSORY_3 = 2,
	WEAR_ACCESSORY_MAX,
};

#define	INVEN_SLOT_TAB				7 // alanssoares two new tabs
#define	INVEN_SLOT_COL				5
#define	INVEN_SLOT_ROW				5
#define	INVEN_SLOT_ROW_TOTAL		20

#define	INVEN_ONE_BAG				25
#define ONE_SUIT_MAX				5
#ifdef EXPANSION_INVENTORY
#define INVEN_ONE_NEW_BAG           40
#endif

#define PET_TYPE_HORSE		(0x10)		// ��
#define PET_TYPE_DRAGON		(0x20)		// ��

#define PET_GRADE_CHILD		(0X01)		// �����
#define PET_GRADE_ADULT		(0X02)		// ������
#define PET_GRADE_MOUNT		(0X03)		// Ż��

//---------------------------------------------------------------------
// Zone Bit Mask
#define	ZONE0		(1 << 0)
#define	ZONE1		(1 << 1)
#define	ZONE2		(1 << 2)
#define	ZONE3		(1 << 3)
#define	ZONE4		(1 << 4)
#define	ZONE5		(1 << 5)
#define	ZONE6		(1 << 6)
#define	ZONE7		(1 << 7)
#define	ZONE8		(1 << 8)
#define	ZONE9		(1 << 9)
#define ZONEALL		(0x3FF)
 
#define	PC_STATE_STANDING		0		// PC ���� : ������
#define	PC_STATE_MOVING			1		// PC ���� : �̵���
#define	PC_STATE_SITDOWN		2		// PC ���� : ����
#define	PC_STATE_WARP			3		// PC ���� : ��ȯ��

/*
���� ���� ����
# LC_KOR 0
# LC_TWN 1
# LC_CHN 3
# LC_TLD 4
# LC_JPN 6
# LC_JPNEP 6
# LC_MAL 7
# LC_USA 9
# LC_BRZ 10
# LC_HBK 11
# LC_GER 13
# LC_SPN 14
# LC_FRC 15
# LC_PLD 16
# LC_RUS 17
# LC_TUR 18
# LC_ITA 19
# LC_MEX 20
# LC_ESP_USA 21
# LC_FRA_USA 22
# LC_NLD 23
# LC_UK 24
*/

// Define country
#define	KOREA					0		// �ѱ�
#define	TAIWAN					1		// �븸
#define	CHINA					2		// �߱�
#define THAILAND				3		// �±�
#define TAIWAN2					4		// �븸 õ�ϴ�� wooss 050929
#define JAPAN					5		// �Ϻ� wooss 051123
#define MALAYSIA    			6
#define USA						7		// �̱�
#define BRAZIL					8		// �����
#define HONGKONG				9		// ȫ��
#define GERMANY					10		// ����
#define SPAIN					11		// ������
#define FRANCE					12		// ������		FRANCE_SPAIN_CLOSEBETA_NA_20081124
#define POLAND					13		// ������
#define RUSSIA					14		// ���þ�
#define TURKEY					15		// ��Ű
#define MEXICO					16		// �߽���
#define ITALY					17		// ��Ż����
#define USA_FRANCE				18		// ���̸��� ������
#define USA_SPAIN				19		// ���̸��� ������ 
#define NETHERLANDS				20		// �״�����
#define ENGLAND					24

// ��ü ȭ�� ��� ����
#define OLD_WINDOW_MODE		0
#define FULLSCREEN_MODE		1
#define TAIWAN_WINDOW_MODE	2

#define IsFullScreen(X)	( (X==FULLSCREEN_MODE)?TRUE:FALSE )
#define IsGamigo(X) ( (X==GERMANY||X==SPAIN||X==FRANCE||X==POLAND||X==TURKEY||X==ITALY||X==ENGLAND||X==USA)?TRUE:FALSE )
#define IsBila(X)	( (X==MEXICO||X==BRAZIL)?TRUE:FALSE )

#define IsDotSeparator(X) ( (X == GERMANY || X == ITALY || X == RUSSIA) ? TRUE:FALSE )
// 1.234.567,89 ������ ���ڸ� ���� ����� ����, �׸���, ����ũ, ��Ż����, �ε��׽þ�, ���þ�
// 1,234,567.89�� ���� ���ڸ� ���� ����� �ѱ�, �̱�, ĳ����, �߱�, �Ϻ�, ����, ȣ��, �����

// Add LC time 060421 wooss
#define _LC_DAY_IN_MONTH		(30L)
#define _LC_DAY_SEC				(24L * 60L * 60L)    /* secs in a day */
#define _LC_YEAR_SEC			(360L * _LC_DAY_SEC)    /* secs in a year */
#define _LC_MONTH_SEC			(_LC_DAY_IN_MONTH * _LC_DAY_SEC)    /* secs in a year */

#define _LC_FOUR_YEAR_SEC		(1440L * _LC_DAY_SEC)   /* secs in a 4 year interval */
#define _LC_BASE_DOW			4                    /* 01-01-70 was a Thursday */

// weapon lease def
#define LEASE_MIN_LEVEL 37
#define LEASE_MAX_LEVEL 65

// WSS_WALLMOVE_BUGFIX 070531---->><<
#define MAX_MOVE_SLOPE_GRADE	45.0f

// ��Ű�� 4
// ��þƮ ���� [11/28/2011 ldy1978220]
// #if defined (G_THAI)
// 	#define ITEM_MEX_LEVEL	16
// #else
#define ITEM_MEX_LEVEL	17
#define ITEM_MAX_UPGRADE_RUNE 15
#define DEF_PET_ITEM_UPGRADE_MAX	15
//#endif

#define DEF_INIT_CAMERA_FOV	(45.0f)

#define SHOW_MOB_HP_BAR		(1 << 0)
#define SHOW_PLAYER_HP_BAR	(1 << 1)

#define	MAX_HONOR_POINTS	5000000
#endif