/************************************
  ��������
  ������ ���: bs
  ������: 2004-11-19 ���� 8:02:59
  ����: ��ų ���� ��� ȿ��, ��ų ���� - ���� ���� �߰�
 ************************************/

#ifndef __GAME_Config_H__
#define __GAME_Config_H__

// ������ ���� : MAKEFILE����
//#define LC_KOR		0	// ����
//#define LC_TLD			4	// �±�
//#ifdef LC_TLD
//#endif // LC_TLD
#define	LC_USA			9	// �̱�
//#define	LC_BRZ			10	// �����

//#define	LC_GER			13  // ����
#define PET_BUFF_ALL_SYSTEM
#define CLOUD_EXPEDITION_PARTY_DUNGEONS
#if defined (LC_KOR)
#define LC_LOCAL_STRING "KOR"
#define LC_LOCAL_CODE		LC_KOR
#elif defined (LC_TLD)
#define LC_LOCAL_STRING "TLD"
#define LC_LOCAL_CODE		LC_TLD
#elif defined (LC_USA)
#define LC_LOCAL_STRING "USA"
#define LC_LOCAL_CODE		LC_USA
#elif defined (LC_BRZ)
#define LC_LOCAL_STRING "BRZ"
#define LC_LOCAL_CODE		LC_BRZ
#elif defined (LC_GER)
#define LC_LOCAL_STRING "DE"
#define LC_LOCAL_CODE		LC_GER
#elif defined (LC_FRC)
#define LC_LOCAL_STRING "FR"
#define LC_LOCAL_CODE		LC_FRC
#elif defined (LC_PLD)
#define LC_LOCAL_STRING "PD"
#define LC_LOCAL_CODE		LC_PLD
#elif defined (LC_SPN)
#define LC_LOCAL_STRING "ES"
#define LC_LOCAL_CODE		LC_SPN
#elif defined (LC_RUS)
#define LC_LOCAL_STRING "RUS"
#define LC_LOCAL_CODE		LC_RUS
#elif defined (LC_TUR)
#define LC_LOCAL_STRING "TR"
#define LC_LOCAL_CODE		LC_TUR
#elif defined (LC_ITA)
#define LC_LOCAL_STRING "IT"
#define LC_LOCAL_CODE		LC_ITA
#elif defined (LC_MEX)
#define LC_LOCAL_STRING "MEX"
#define LC_LOCAL_CODE		LC_MEX
#elif defined (LC_UK)
#define LC_LOCAL_STRING "UK"
#define LC_LOCAL_CODE		LC_UK
#else
#error "Not Set Language"
#endif // #if defined (LC_KOR)
// --- ������ ����

//#define		BLOCK_PVP					// TODO : PVP �������� �ּ� Ǯ��

#define SERVER_VERSION			600		// ���� ���� ����
#define SERVER_MIN_VERSION		600		// �޽���, �����Ϳ��� �����ϴ� ���� ���� ����
#define SERVER_MAX_VERSION		700		// �޽���, �����Ϳ��� �����ϴ� �ְ� ���� ����
#define CONNECTOR_SERVER_NUM	888		// ������ ���� ��ȣ
#define LOGIN_SERVER_NUM		999		// �α��� ���� ��ȣ
#define MESSENGER_SERVER_NUM	777		// �޽��� ���� ��ȣ
#define BILL_SERVER_VERSION		"BillCruxV40" // �������� �������� ����
#define		GAMEID				1		// ��ī ���� ���̵� 1��

#define BILL_LOCATION_HOME		0		// �Ϲ�
#define	BILL_LOCATION_PCBANG	1		// ��ϵ� pc��
#define MAX_GUID_LENGTH         1000
#define PCBANG_LOGIN			10		// pc�� �α���
#define PCBANG_LOGOUT			11		// pc�� �α� �ƿ�
#define LOGIN_SERVER_OPEN_CHECK_FILENAME	"login.open"		// �α��� ���� ���� �˻� ���ϸ�

//#define		GAMEID				1 // �̰� �ߺ��̶� �ּ� ó��
#define		CPID				1
#define		ID_LENGTH			32
#define		MAX_PURCHASEITEM	16
#define		MAX_DEPOSITORY		25

#define	PLAYER_COUNT_NUM		9999	// ����ڼ� ���� ���α׷� ��ȣ

#define NUM_RESERVED_DESCS		5		// ���������� ����� ��ũ���� ��
#define MAX_PLAYING				50000	// �ִ� ���� ��
#define MAX_ZONES				57		// always add +1 from your ZONE_ DEFINES
#define MAX_NOTICE				5

#define PI       3.14159265358979323846f
#define PI_2     6.28318530717958623200f
#define PI_3_4	 2.35619449019234492884f	/* ((3 / 4) * PI) */
#define PI_HALF	 (PI / 2)

// �ð� ����
#ifdef __GAME_SERVER__
#define OPT_USEC		100000				/* 10 passes per second */
#else
#define OPT_USEC		50000				/* 20 passes per second */
#endif
#define PASSES_PER_SEC	(1000000 / OPT_USEC)
#define RL_SEC			* PASSES_PER_SEC
#define RL_OCLOCK			3600				// ���� ����.
#define RL_24CLOCK			86400				// ���� 24��
// ���� �ð����� ����
#define PULSE_REAL_SEC				(1 RL_SEC)				// ���� 1��
#define PULSE_REAL_MIN				(60 RL_SEC)				// ���� 1��
#define PULSE_REAL_TENMIN			(600 RL_SEC)			// ���� 10��
#define PULSE_REAL_HALF				(1800 RL_SEC)			// ���� 30��
#define	PULSE_REAL_HOUR				(3600 RL_SEC)			// ���� 1�ð�
#define PULSE_REAL_24HOUR			(86400 RL_SEC)

#define PULSE_PCROOM_COUNT			(3 * PULSE_REAL_MIN)	// �Ǿ��� ������ �� ī��Ʈ �ֱ�
#define PULSE_TOTAL_COUNT			PULSE_REAL_MIN			// ��ü ���� �� ī��Ʈ �ֱ�
#define PULSE_NPC_AI				2						// NPC �ּ� AI ���� �ð� : 0.5��
#define	PULSE_NPC_REGEN				(15 RL_SEC)				// NPC ���� �ּ� ���� �ð� : ���� 30��
#define PULSE_WARPDELAY				(10 * TIME_ONE_SECOND)	// �����̵� ������ : 10��
#define PULSE_BILLITEMREQ			(20 * TIME_ONE_SECOND)	// ���������� ���� ���� �ð� 20��  �̽ð��� ������ ���� Ǭ��.
#define PULSE_BILLITEMLISTREQ		(4 * PULSE_REAL_SEC)	// ���������� ����Ʈ ��û ���� �ð� �̽ð��� ������ ���� Ǭ��.
#define PULSE_WARPCOUNTDOWN			(5 * PULSE_REAL_SEC)	// �����̵� ī��Ʈ �ٿ� ���� : 5�� ������
#define PULSE_ASSIST_CHECK			PULSE_REAL_SEC			// ����ȿ�� �ð� ���� �˻� ������
#define PULSE_HACK_CHECK_TIMEOUT	(6 * PULSE_REAL_MIN)	// �޽� �޽��� Ÿ�Ӿƿ� 6��
#define PULSE_HACK_PULSE_REFRESH	PULSE_REAL_HOUR			// �� �˻� �޽� ���� �ֱ� 1�ð�
#define PULSE_HACK_PULSE_THRESHOLD	(15 * PULSE_REAL_SEC)	// �� �޽� ���� ���� 15��
#define PULSE_HACK_CLIENT_THRESHOLD	(55 * PULSE_REAL_SEC)	// �� �޽� Ŭ���̾�Ʈ �ּ� �ֱ� 55�� �̺��� ���� ������ �ȵ�!
#define PULSE_PKMODE_DELAY			10		 				// PK��忡�� ��ȭ���� ��ȯ�� ������
#define PULSE_HACK_ATTACK_THRESHOLD	2						// ���� ���� ��� ����
#define	PULSE_HACK_ATTACK_COUNT		5						// ���� ��ī��Ʈ ������ ����
#define PULSE_ATTACKMODE_DELAY		(3 * PULSE_REAL_SEC)	// ���� ��� Ǯ���� ������ : ������ �������� �� �ð������� ���� ���̴�
#define PULSE_POST_REGEN_DELAY		(3 * PULSE_REAL_SEC)	// �������� �����ϱ� ������ ������
#define PULSE_PRODUCE_DELAY			(2 * PULSE_REAL_SEC)	// ���� ������
#define PULSE_PET_SYMPATHY_INCREASE	(5 * PULSE_REAL_MIN)	// �� ������ ���� ������
#define PULSE_PET_SYMPATHY_DECREASE	(PULSE_REAL_HOUR)		// �� ������ ���� ������
#define PULSE_PET_HUNGRY_DECREASE	(10 * PULSE_REAL_MIN)	// �� ����� ������
#define PULSE_AUTO_SKILL_DECREASE	(10 * TIME_ONE_SECOND)	// �ڵ� ��ų ���� �ð�
#define PULSE_KEY_CHANGE_THRESHOLD	(10 * PULSE_REAL_SEC)	// Ű ���� �Ӱ� �ð� : 10 ��
#define PULSE_KEY_CHANGE			(20 * PULSE_REAL_SEC)	// Ű ���� �ֱ� : 20 ��
#define	PULSE_SERVER_ALIVE			(2 * PULSE_REAL_MIN)	// ���� ���� ����̺� �޼��� Ÿ��
#define	PULSE_PCBANG_ITEM			(PULSE_REAL_HOUR)		// ��ϵ� PC�濡�� ������ ���� �ֱ�
#define PULSE_SAVECOUNT_NEW				5					// �������� ���� �÷��̾� �� ���� �ð�
#define PULSE_SAVEMAXCOUNT_NEW			2					// �������� �ִ� ���� �÷��̾� �� ���� �ð�
#define PULSE_TRIGGER_SYSTEM		(4 * PULSE_REAL_SEC)	// proc
 
#define HACK_FACTOR_ADD				100

#define TIME_ONE_SECOND				1						// 1��
#define TIME_ONE_MIN				60						// 1��
#define TIME_ONE_HOUR				60 * 60					// 1�ð�
#define TIME_ONE_DAY				TIME_ONE_HOUR * 24		// 1��
#define TIME_ONE_WEEK				TIME_ONE_DAY * 7		// 1����
#define TIME_ONE_MONTH				TIME_ONE_DAY * 30		// 30��

#define MAX_ID_NAME_LENGTH			64		// ���̵�, �̸� ����
#define MAX_PWD_LENGTH				32		// ��ȣ ����
#define HOST_LENGTH					30		// ȣ��Ʈ �ּ� ���ڿ� ����
#define MAX_CHAR_NAME_LENGTH		50		// �ɸ��� �̸� ����
#define MAX_GUILD_NAME_LENGTH		50		// ��� �̸� ����
#define MAX_ITEM_NAME_LENGTH		50		// ������ �̸�����
#define FRIEND_MAX_MEMBER			100		// ģ�� ��� ��
#define	FRIEND_GROUP_MAX_NUMBER		10		// �׷� ��
#define MAX_GROUP_NAME_LENGTH		20		// �׷� �̸� ����
#define BLOCK_MAX_MEMBER			20		// �ִ� ���� �ο���
#define	MAX_GIFT_MESSAGE_LENGTH		100		// ���� �޼��� ���� 100����Ʈ

// �������� ����ϴ� ���ڹ迭, CServer�� Run������ ���!!!
#define MAX_STRING_LENGTH		8192

// ���� ���� ���
#define CON_PLAYING						0		// ���� ��
#define CON_CLOSE						1		// ���� ����
#define CON_MOVESERVER					2		// ���� �̵���
#define CON_MOVESERVER_WAIT				3		// ���� �̵���
#define CON_WAIT_SCARD					4		// ���� ī�� ��� ��
#define CON_MENU						10		// �޴������� ����
#define CON_DISCONNECT					17		// ������ ���� ����
#define CON_WAIT_USER_DB				19		// ĳ���� ������ ��ٸ�
#define CON_WAIT_NEW_CHAR_DB			20		// ĳ���� ���� ��ٸ�
#define CON_WAIT_DEL_CHAR_DB			21		// ĳ���� ���� ��ٸ�
#define CON_WAIT_PLAY_CHAR_DB			22		// ĳ���� �� ���� ��ٸ�
#define CON_GET_LOGIN					23		// �α��� �õ�
#define CON_PREPARE_PLAY				25		// ���� ���� �����
#define CON_PREPARE_PLAY_BEFORE			26		// ĳ���� ���� ���
#define CON_WAIT_IDEN_MSG				30		// ���� ��ٸ�
#define CON_GET_IDEN_MSG				31		// ���� ��û
#define CON_GET_DUMMY					32		// ��Ŷ�� ������

#define STATE(d)			((d)->m_connected)
#define WAITTING_DB(d)		((d)->m_bwaitdb)
#define UPDATING_DB(d)		((d)->m_updatedb)
#define PLAYMODE(d)			((d)->m_playmode)

// �ű� ���� �ɸ���, �������� ����, �±��ϰ�� ����
//Ŀ���� class CUser�� m_userFlag
#define NOVICE					( 1 << 0 )
#define	RECV_GIFT				( 1 << 1 )
#define ADULT					( 1 << 2 )
#define IS_CHARACTER			( 1 << 3 )
#define IS_NEWUSER_JPN_2007_03	( 1 << 4 )
#define IS_GM_CHAR				( 1 << 5 )

/////////////////////////////////////////////////////////////////////////////
// ������ ����
#include "Config_Localize.h"
// ---- ������ ����
/////////////////////////////////////////////////////////////////////////////

// ��ų����Ʈ
#define MAX_SKILLPOINT		2000000000
#define DAILY_LOGIN
#define LOGINREWARDNEW
#define MAX_REBORN 5
#define MAX_REBORN_EXP_FACTOR 10
#define ENABLE_MAX_REBORN

#define DEFAULT_JOB_DAMAGE 31

//#define NIGHTSHADOW_START_NOITEM
#define GUARDIAN_ITEM_REWARD 3217//  old 3217

// ������ ���
#ifdef EX_ROGUE
#define JOBCOUNT			9
#else
#define JOBCOUNT			7
#endif // EX_ROGUE
#define JOB_TITAN			0
#define JOB_KNIGHT			1
#define JOB_HEALER			2
#define JOB_MAGE			3
#define JOB_ROGUE			4
#define JOB_SORCERER		5
#define JOB_NIGHTSHADOW		6
#ifdef EX_ROGUE
#define JOB_EX_ROGUE		7
#endif // EX_ROGUE
#ifdef EX_MAGE
#define JOB_EX_MAGE			8
#endif

#define JOB_PET				10
#define JOB_APET			11

#ifdef EX_ROGUE
#ifdef EX_MAGE
#define JOB2COUNT			17
#else
#define JOB2COUNT			15
#endif
#else
#define JOB2COUNT			13
#endif // EX_ROGUE

#define JOB_2ND_SPLIT_INDEX	2

#define JOB_2ND_HIGHLANDER			1		// ���̷���
#define	JOB_2ND_WARMASTER			2		// ��������

#define JOB_2ND_ROYALKNIGHT			1		// �ο�����Ʈ
#define	JOB_2ND_TEMPLEKNIGHT		2		// ���ó���Ʈ

#define JOB_2ND_ARCHER				1		// ��ó
#define	JOB_2ND_CLERIC				2		// Ŭ����

#define JOB_2ND_WIZARD				1		// ���ڵ�
#define	JOB_2ND_WITCH				2		// ��ġ

#define JOB_2ND_ASSASSIN			1		// ����
#define	JOB_2ND_RANGER				2		// ������

#define JOB_2ND_ELEMENTALLIST		1		// ������Ż ����Ʈ
#define JOB_2ND_SPECIALLIST			2		// ����� ����Ʈ

#define JOB_2ND_NIGHTSHADOW			1		// ����Ʈ ������
#define JOB_2ND_NIGHTSHADOW2		2		// Dummy ������

#define JOB_2ND_EX_ASSASSIN			1		// EX ����
#define JOB_2ND_EX_RANGER			2		// EX ������

#define JOB_2ND_EX_WIZARD			1		// EX ���ڵ�
#define JOB_2ND_EX_WITCH			2		// EX ��ġ

#define JOB_2ND_PET_HORSE			0	// ��
#define JOB_2ND_PET_DRAGON			1	// ��
#define JOB_2ND_PET_HORSE_MOUNT		2	// �� : Ż��
#define JOB_2ND_PET_DRAGON_MOUNT	3	// �� : Ż��

#define JOB_2ND_LEVEL			31		// ���� ����

#define JOB_SUB_TRADER			( 1 << 0 )		// ������ ����

// ĳ���� flag
#define CHAT_FLAG_NO_SAY		(1 << 0)		// �Ϲ� ä�� ����
#define CHAT_FLAG_NO_PARTY		(1 << 1)		// ��Ƽ ä�� ����
#define CHAT_FLAG_NO_GUILD		(1 << 2)		// ��� ä�� ����
#define CHAT_FLAG_NO_TRADE		(1 << 3)		// �Ÿ� ä�� ����
#define CHAT_FLAG_NO_WHISPER	(1 << 4)		// �ӼӸ� ����
#define CHAT_FLAG_NO_SHOUT		(1 << 5)		// ��ġ�� ����
#define CHAT_FLAG_NO_EXPED		(1 << 6)		// ������ ä�� ����

#define CHAT_MESSAGE_MAX		(250)

// �Ӹ� ��� ����
#define HAIR_TITAN			5
#define HAIR_KNIGHT			5
#define HAIR_HEALER			5
#define HAIR_MAGE			5
#define HAIR_ROGUE			5
#define HAIR_SORCERER		5
#define HAIR_NIGHTSHADOW	5
#define HAIR_EX_LOG			5
#define HAIR_EX_MAGE		5

#define HAIR_RED_CAP		10			// ���� ��Ÿ ����
#define HAIR_GREEN_CAP		20			// ��� ��Ÿ ����

// �� ��� ����
#define FACE_TITAN			5
#define FACE_KNIGHT			5
#define FACE_HEALER			5
#define FACE_MAGE			5
#define FACE_ROGUE			5
#define FACE_SORCERER		5
#define FACE_NIGHTSHADOW	5
#define FACE_EX_ROGUE		5
#define FACE_EX_MAGE		5

// �����ͺ��̽� ���� ����
#define DB_NOP					0		// DB No Operation...
#define DB_UPDATE				1		// Request DB Update...
#define DB_WAIT_SAVE			10		// Save Delay...
#define DB_END					11		// ���� ������ �α׾ƿ� �Ϸ�

// ���� �α��� ����
#define	MAX_CHAR_COUNT			8		// �ִ� ���� ���� ĳ���� ��
#define MAX_SKILL				60		// ĳ���� �� �ִ� ��ų ����
#define MAX_ASSIST_HELP			44		// ���� ȿ�� : �̷ο� ��
#define MAX_ASSIST_CURSE		16		// ���� ȿ�� : �طο� ��
#define MAX_ASSIST_ABS			44		// ���� �ð� ����ȿ��
#define MAX_EXT_CHAR_COUNT		2		// ������������� �߰� �Ҽ� �ִ� ���Լ�

///////
// ��Ÿ
#define NO_CELL				(-100)		// ���� ���� �ȵ� ����
#define EPSILON				(1.0e-5f)	// Tolerance for FLOATs
#define CELL_SIZE			12.0f		// �� ���� attr ���� (m ����)

#define CELL_EXT			5			// ������ ��ġ�� �� ����

#define MULTIPLE_HEIGHTMAP	100.0f		// ���̸� �������� ��ġ
#define MAX_PLAYER_LIST		8192		// �ִ� ���� ������ ��
#define MAX_MEMPOS					15			// ��� ��� ��
#define MAX_MEMPOS_NORMAL			10			// ��� ��� ��

#define ATTACK_TYPE_NORMAL			0			// �Ϲݰ���
#define ATTACK_TYPE_DOUBLE			2			// �������� ( �����ѹ��� 2�� ���� )
#define ATTACK_TYPE_INFINITY		10			// ���Ѱ��� ( ���Ӱ˻� ���� )

///////////////////
// NPC ����
#define		MAX_NPC_SKILL			4
#define		MAX_NPC_DROPITEM		20
#define		MAX_NPC_PRODUCT			5
#define		MAX_NPC_DROPITEM_LOOP	4
#define		MAX_NPC_DROPJEWEL		20

// NPC FLAG --
#define		NPC_SHOPPER				(1 << 0)	// �������ο���?
#define		NPC_FIRSTATTACK			(1 << 1)	// ��������?
#define		NPC_ATTACK				(1 << 2)	// �ݰݰ���?
#define		NPC_MOVING				(1 << 3)	// �̵�����?
#define		NPC_PEACEFUL			(1 << 4)	// ��ȭ���� ��(��Ŭ������ ���� �� ��ų��)
#define		NPC_ZONEMOVER			(1 << 5)	// �� �̵������ִ� NPC
#define		NPC_CASTLE_GUARD		(1 << 6)	// ��ȣ��
#define		NPC_REFINER				(1 << 7)	// ���ݼ��� NPC
#define		NPC_QUEST				(1 << 8)	// Quest NPC
#define		NPC_CASTLE_TOWER		(1 << 9)	// ������ ��ȣ��
#define		NPC_MINERAL				(1 << 10)	// �̳׶�
#define		NPC_CROPS				(1 << 11)	// ���۹�
#define		NPC_ENERGY				(1 << 12)	// ������
#define		NPC_ETERNAL				(1 << 13)	// ����
#define		NPC_LORD_SYMBOL			(1 << 14)	// ������ ����
#define		NPC_REMISSION			(1 << 15)	// ���˺�
#define		NPC_EVENT				(1 << 16)	// �̺�Ʈ
#define		NPC_GUARD				(1 << 17)	// ���
#define		NPC_KEEPER				(1 << 18)	// â��
#define		NPC_GUILD				(1 << 19)	// ���
#define		NPC_MBOSS				(1 << 20)	// �غ���
#define		NPC_BOSS				(1 << 21)	// ����
#define		NPC_RESETSTAT			(1 << 22)	// ���� �ʱ�ȭ
#define		NPC_CHANGEWEAPON		(1 << 23)	// ���� ��ü
#define		NPC_WARCASTLE			(1 << 24)	// ���� NPC
#define		NPC_DISPLAY_MAP			(1 << 25)	// ������ ǥ�õǴ��� ����
#define		NPC_QUEST_COLLECT		(1 << 26)	// ���� ����Ʈ��
#define		NPC_PARTY				(1 << 27)	// ��Ƽ�� ǥ�ÿ�
#define		NPC_RAID				(1 << 28)	// ���̵� ��
#define		NPC_SUBCITY				(1 << 29)	// ���� ���� NPC
#define		NPC_CHAOCITY			(1 << 30)	// ī������ ���� ���� NPC
#define		NPC_HUNTERCITY			(1 << 31)	// ���͸��� ���� ���� NPC

// NPC FLAG1(Ȯ��) --
#define		NPC1_TRADEAGENT			(1 << 0)	// �ŷ�����(���) �ý���
#define		XXX_NPC1_COLLSION			(1 << 1)	// ���̵� �ν���Ʈ ������ ������ NPC
#define		NPC1_FACTORY			(1 << 2)	// ���� �ý��� NPC
#define		NPC1_TRIGGER_CHOICE		(1 << 3)	// NPC�� ��ȭ�ϸ� Ʈ���� �ߵ�
#define		NPC1_TRIGGER_KILL		(1 << 4)	// NPC�� ���̸� Ʈ���� �ߵ�
#define		NPC1_NOT_NPCPORTAL		(1 << 5)	// NPCPORTAL ��ũ�� ����Ʈ�� ����Ǹ� �ʵǴ� �ѵ��� üũ
#define		NPC1_DONT_ATTACK		(1 << 6)	// ���� npc�� ������ ���� �ʴ´�.
#define		NPC1_AFFINITY			(1 << 7)	// ģȭ��
#define		NPC1_SHADOW				(1 << 8)	// �׸��� �Ӽ� ( �׸��� �������� ���ø� ���� )
#define		NPC1_CRAFTING			(1 << 9)	// ����2 ���� ������ npc
#define		NPC1_TOTEM_ITEM			(1 << 10)	// ���������� ���� ���� ��ȯ

// NPC AI TYPE
#define		NPC_AI_NORMAL			0			// �Ϲ� NPC
#define		NPC_AI_TANKER			1			// �Ϲ� NPC
#define		NPC_AI_DAMAGEDEALER		2			// �Ϲ� NPC
#define		NPC_AI_HEALER			3			// �Ϲ� NPC

#define IS_NPC(ch)			(ch->m_type == MSG_CHAR_NPC)	// NPC �ΰ���?
#define TO_NPC(ch)			((ch == NULL) ? NULL : (IS_NPC(ch) ? (CNPC*)ch : (CNPC*)NULL))		// NPC�� ĳ����
#define IS_PC(ch)			(ch->m_type == MSG_CHAR_PC)		// PC �ΰ���?
#define TO_PC(ch)			((ch == NULL) ? NULL : (IS_PC(ch) ? (CPC*)ch : (CPC*)NULL))			// PC�� ĳ����
#define IS_PET(ch)			(ch->m_type == MSG_CHAR_PET)	// �ֿϵ����ΰ�?
#define TO_PET(ch)			((ch == NULL) ? NULL : (IS_PET(ch) ? (CPet*)ch : (CPet*)NULL))		// Pet�� ĳ����

#define IS_APET(ch)			(ch->m_type == MSG_CHAR_APET)
#define TO_APET(ch)			((ch == NULL) ? NULL : (IS_APET(ch) ? (CAPet*)ch : (CAPet*)NULL))		// AttackPet�� ĳ����

#define IS_ELEMENTAL(ch)	(ch->m_type == MSG_CHAR_ELEMENTAL)	// ��ȯ�� �ΰ�?
#define TO_ELEMENTAL(ch)	((ch == NULL) ? NULL : (IS_ELEMENTAL(ch) ? (CElemental*)ch : (CElemental*)NULL)) // ��ȯ���� ĳ����
#define GET_CHAR_TYPE(ch)	((char)(ch->m_type))
#define DEAD(ch)			(ch->m_hp <= 0)					// ĳ���� �׾�����?
#define IS_IN_CELL(ch)		(ch->m_cellX >= 0)				// ĳ���Ͱ� ���� ��ġ�� �ֳ���?

#define CMD_NUM 200						// �ִ� �޽��� ���� ��

#define GET_X(obj)			(obj->m_pos.m_x)
#define GET_Z(obj)			(obj->m_pos.m_z)
#define GET_H(obj)			((obj && obj->m_pArea) ? obj->m_pArea->GetHeight(GET_YLAYER(obj), GET_X(obj), GET_Z(obj)) : 0.0f)
#define GET_R(obj)			(obj->m_pos.m_r)
#define GET_YLAYER(obj)		(obj->m_pos.m_yLayer)

// �Ӽ��� ���
#define	MATT_WALKABLE			0x0001
#define	MATT_PEACE				0x0002
#define	MATT_PRODUCT_PUBLIC		0x0004
#define	MATT_PRODUCT_PRIVATE	0x0008
#define	MATT_STAIR_UP			0x0010
#define	MATT_STAIR_DOWN			0x0020
#define	MATT_WAR				0x0040
#define	MATT_FREEPKZONE			0x0080

#define	MATT_UNWALKABLE			0x8000

///////////////////
// ������ ���� ���

// 050311 : bs : ���Ⱑ ����ϴ� ���ȿ� ���� ��� �߰�
#define USING_STR		0
#define USING_DEX		1
#define USING_INT		2
// --- 050311 : bs : ���Ⱑ ����ϴ� ���ȿ� ���� ��� �߰�
// ��ǰ Ÿ��
// category
#define		CATEGORY_HOTNNEW							10000
#define		CATEGORY_PLATINUM							20000
#define		CATEGORY_DISPOSABLE							30000
#define		CATEGORY_COSTUME							40000
#define		CATEGORY_PET								50000
#define		CATEGORY_SERVICE							60000
#define		CATEGORY_PACKAGE							70000
// type
#define		TYPE_HOTNNEW_NONE							10000	//TYPE �̺з�
#define		TYPE_HOTNNEW_NEW							10100
#define		TYPE_HOTNNEW_DISCOUNT						10200
#define		TYPE_HOTNNEW_HOT							10300
#define		TYPE_PLATINUM_NONE							20000
#define		TYPE_DISPOSABLE_NONE						30000
#define		TYPE_DISPOSABLE_CHARACTER_GROW				30100
#define		TYPE_DISPOSABLE_ABILITY_BUILDUP				30200
#define		TYPE_DISPOSABLE_POTION						30300
#define		TYPE_EQUIP_NONE								40000
#define		TYPE_EQUIP_EQUIPMENT						40100
#define		TYPE_EQUIP_BUILDUP							40200
#define		TYPE_EQUIP_COSTUME							40300
#define		TYPE_AVATAR_NONE							50000
#define		TYPE_AVATAR_PET								50100
#define		TYPE_AVATAR_MERCENARY						50200
#define		TYPE_SERVICE_NONE							60000
#define		TYPE_SERVICE_CONVENIENCE					60100
#define		TYPE_SERVICE_ETC							60200
#define		TYPE_PACKAGE_NONE							70000
//�̱��� ���� �߰���
#define		TYPE_PACKAGE_BOOSTERS						70100
#define		TYPE_PACKAGE_ENHANCEMENTS					70200
#define		TYPE_PACKAGE_POTIONS						70300
#define		TYPE_PACKAGE_VANITY							70400
#define		TYPE_PACKAGE_UPGRADE						70500
#define		TYPE_PACKAGE_PETS							70600
#define		TYPE_PACKAGE_MERCENARY						70700
#define		TYPE_PACKAGE_CONVENIENCE					70800
#define		TYPE_PACKAGE_OTHERS							70900
//�̱��� ���� �߰���
#define 	TYPE_OLD_GOODS								90000
#define		TYPE_LIST_START								0
#define		TYPE_MAX_COUNT								50
// subtype
#define		SUBTYPE_HOTNNEW_NONE_NONE					10000 // TYPE, SUBTYPE �̺з�
#define		SUBTYPE_HOTNNEW_NEW_NONE					10100
#define		SUBTYPE_HOTNNEW_DISCOUNT_NONE				10200
#define		SUBTYPE_PLATINUM_NONE_NONE					20000
#define		SUBTYPE_DISPOSABLE_NONE_NONE				30000
#define		SUBTYPE_DISPOSABLE_CHARACTER_GROW_NONE		30100
#define		SUBTYPE_DISPOSABLE_CHARACTER_GROW_EXP		30101
#define		SUBTYPE_DISPOSABLE_CHARACTER_GROW_SP		30102
#define		SUBTYPE_DISPOSABLE_CHARACTER_GROW_DROP		30103
#define		SUBTYPE_DISPOSABLE_CHARACTER_GROW_MIX		30104
#define		SUBTYPE_DISPOSABLE_ABILITY_BUILDUP_NONE		30200
#define		SUBTYPE_DISPOSABLE_ABILITY_BUILDUP_HPEXT	30201
#define		SUBTYPE_DISPOSABLE_ABILITY_BUILDUP_MPEXT	30202
#define		SUBTYPE_DISPOSABLE_ABILITY_BUILDUP_VOL		30203	// VOL = Velocity of Light
#define		SUBTYPE_DISPOSABLE_POTION_NONE				30300
#define		SUBTYPE_DISPOSABLE_POTION_HPRECOVER			30301
#define		SUBTYPE_DISPOSABLE_POTION_MPRECOVER			30302
#define		SUBTYPE_DISPOSABLE_POTION_DUALRECOVER		30303
#define		SUBTYPE_EQUIP_NONE_NONE						40000
#define		SUBTYPE_EQUIP_EQUIPMENT_NONE				40100
#define		SUBTYPE_EQUIP_EQUIPMENT_WEAPON				40101
#define		SUBTYPE_EQUIP_EQUIPMENT_ARMOR				40102
#define		SUBTYPE_EQUIP_EQUIPMENT_ACCESSORY			40103
#define		SUBTYPE_EQUIP_BUILDUP_NONE					40200
#define		SUBTYPE_EQUIP_BUILDUP_MELDING				40201
#define		SUBTYPE_EQUIP_BUILDUP_SOCKET				40202
#define		SUBTYPE_EQUIP_BUILDUP_BLOOD					40203
#define 	SUBTYPE_EQUIP_BUILDUP_REFINE				40204
#define		SUBTYPE_EQUIP_COSTUME_NONE					40300
#define		SUBTYPE_EQUIP_COSTUME_TITAN					40301
#define		SUBTYPE_EQUIP_COSTUME_KNIGHT				40302
#define		SUBTYPE_EQUIP_COSTUME_HEALER				40303
#define		SUBTYPE_EQUIP_COSTUME_MAGE					40304
#define		SUBTYPE_EQUIP_COSTUME_ROGUE					40305
#define		SUBTYPE_EQUIP_COSTUME_SORCERER				40306
#define		SUBTYPE_EQUIP_COSTUME_NIGHTSHADOW			40307
#define		SUBTYPE_AVATAR_NONE_NONE					50000
#define		SUBTYPE_AVATAR_PET_NONE						50100
#define		SUBTYPE_AVATAR_PET_PET						50101
#define		SUBTYPE_AVATAR_PET_PETITEM					50102
#define		SUBTYPE_AVATAR_MERCENARY_NONE				50200
#define		SUBTYPE_AVATAR_MERCENARY_MONSTER			50201
#define		SUBTYPE_SERVICE_NONE_NONE					60000
#define		SUBTYPE_SERVICE_CONVENIENCE_NONE			60100
#define		SUBTYPE_SERVICE_CONVENIENCE_SCROLL			60101
#define		SUBTYPE_SERVICE_CONVENIENCE_CARD			60102
#define		SUBTYPE_SERVICE_CONVENIENCE_ETC_NONE		60200
#define		SUBTYPE_PACKAGE_NONE_NONE					70000
//�̱��� ���� �߰���
#define		SUBTYPE_PACKAGE_BOOSTERS_NONE				70100
#define		SUBTYPE_PACKAGE_BOOSTERS_XP					70101
#define		SUBTYPE_PACKAGE_BOOSTERS_SP					70102
#define		SUBTYPE_PACKAGE_BOOSTERS_DROP				70103
#define		SUBTYPE_PACKAGE_BOOSTERS_MIXED				70104
#define		SUBTYPE_PACKAGE_ENHANCEMENTS_NONE			70200
#define		SUBTYPE_PACKAGE_ENHANCEMENTS_HPMP			70201
#define		SUBTYPE_PACKAGE_ENHANCEMENTS_MIXED			70202
#define		SUBTYPE_PACKAGE_POTIONS_NONE				70300
#define		SUBTYPE_PACKAGE_POTIONS_HPRECOVERY			70301
#define		SUBTYPE_PACKAGE_POTIONS_MPRECOVERY			70302
#define		SUBTYPE_PACKAGE_POTIONS_MIXED				70303
#define		SUBTYPE_PACKAGE_VANITY_NONE					70400
#define		SUBTYPE_PACKAGE_VANITY_TITAN				70401
#define		SUBTYPE_PACKAGE_VANITY_KNIGHT				70402
#define		SUBTYPE_PACKAGE_VANITY_HEALER				70403
#define		SUBTYPE_PACKAGE_VANITY_MAGE					70404
#define		SUBTYPE_PACKAGE_VANITY_ROGUE				70405
#define		SUBTYPE_PACKAGE_VANITY_SORCERER				70406
#define		SUBTYPE_PACKAGE_VANITY_NIGHTSHADOW			70407
#define		SUBTYPE_PACKAGE_UPGRADE_NONE				70500
#define		SUBTYPE_PACKAGE_UPGRADE_MELDING				70501
#define		SUBTYPE_PACKAGE_UPGRADE_STONENRUNES			70502
#define		SUBTYPE_PACKAGE_UPGRADE_SOCKETS				70503
#define		SUBTYPE_PACKAGE_PETS_NONE					70600
#define		SUBTYPE_PACKAGE_PETS_PETS					70601
#define		SUBTYPE_PACKAGE_PETS_PETSITEM				70602
#define		SUBTYPE_PACKAGE_MERCENARY_NONE				70700
#define		SUBTYPE_PACKAGE_CONVENIENCE_NONE			70800
#define		SUBTYPE_PACKAGE_CONVENIENCE_SCROLLS			70801
#define		SUBTYPE_PACKAGE_CONVENIENCE_CARDS			70802
#define		SUBTYPE_PACKAGE_OTHERS_NONE					70900
//�̱��� ���� �߰���
#define		SUBTYPE_LIST_START							1
#define		SUBTYPE_MAX_COUNT							500
// ��ǰ �÷���
#define		CATALOG_FLAG_NEW						(1 << 0)			// �Ż�ǰ
#define		CATALOG_FLAG_POPULAR					(1 << 1)			// �α��ǰ
#define		CATALOG_FLAG_DISCOUNT					(1 << 2)			// Ư����ǰ
#define		CATALOG_FLAG_RECOMM_1					(1 << 3)			// ��õ ������1
#define		CATALOG_FLAG_RECOMM_2					(1 << 4)			// ��õ ������2
#define		CATALOG_FLAG_RECOMM_3					(1 << 5)			// ��õ ������3
#define		CATALOG_FLAG_RECOMM_4					(1 << 6)			// ��õ ������4
#define		CATALOG_FLAG_RECOMM_5					(1 << 7)			// ��õ ������5
#define		CATALOG_FLAG_NOGIFT						(1 << 8)			// ��������
#define		CATALOG_FLAG_RESV2						(1 << 9)			// ���� �÷���
#define		CATALOG_FALG_TO_LIMIT(a, b)				(b = 0 | (a >> 10))	// īŻ�α� FLAG ���
#define		CATALOG_FALG_FROM_LIMIT(a, b)			(a = a | (b << 10))	// īŻ�α� FLAG �Է�
#define		CATALOG_FLAG_MAX_LIMIT					(2000000)			// īŻ�α� �÷��� LIMIT MAX

// Item Flag : �ֻ��� 1��Ʈ�� ��� �Ұ�!!!
// 6��Ʈ���� �ɸ�, ��, �Ϲ� ���ü��� ������, �÷�Ƽ�� ���ü��� �ٸ� �������� ������ ���
#define		PLATINUM_MAX_PLUS				127
#define		FLAG_ITEM_PLATINUM_GET(a, b)	(b = a & PLATINUM_MAX_PLUS)
#define		FLAG_ITEM_PLATINUM_SET(a, b)	( (a &~ PLATINUM_MAX_PLUS) | b )
#define		FLAG_ITEM_OPTION_ENABLE			(1 << 7)	// ������ �÷��׿� �ɼ��� ���� �� �ִ� ���¸� ����, Bit ����
#define		FLAG_ITEM_SEALED				(1 << 8)	// ������ ����
#define		FLAG_ITEM_SUPER_STONE_USED		(1 << 9)	// ���۰����� ���׷��̵� ����..//0627
#define		FLAG_ITEM_BOOSTER_ADDED			(1 << 10)	// �ν��� ���� ����
#define		FLAG_ITEM_SILVERBOOSTER_ADDED	(1 << 11)	// �ǹ��ν��� ���� ����
#define		FLAG_ITEM_GOLDBOOSTER_ADDED		(1 << 12)	// ���ν��� ���� ����
#define		FLAG_ITEM_PLATINUMBOOSTER_ADDED	(1 << 13)	// ���ν��� ���� ����
#define		FLAG_ITEM_COMPOSITION			(1 << 14)	// ������ �ռ� ����
#define		FLAG_ITEM_LENT					(1 << 15)	// �뿩�� ������
#define		FLAG_ITEM_LEVELDOWN				(1 << 16)	// ���� �ٿ�� ������
#define		FLAG_ITEM_BELONG				(1 << 17)	// �ͼ� �� ������
#define		FLAG_ITEM_SOCKET				(1 << 18)
#define		FLAG_ITEM_SUPER_RUNE_USED		(1 << 19)	// �ʰ��޷� ��� ����.
#define		FLAG_ITEM_TRANSMOGRIFY			(1 << 20)
#define     FLAG_ITEM_OPAL_MINUS_USED       (1 << 21)
#define		FLAG_ITEM_PVP_RUNE_USED			(1 << 22)
#define		FLAG_ITEM_RESERVED				(1 << 31)	// ����� �� ����ϸ� ���� �ȵ�!

// Item Proto flag
#define		ITEM_FLAG_COUNT					((LONGLONG)1 << 0)	// �� �� �ִ� �������ΰ�
#define		ITEM_FLAG_DROP					((LONGLONG)1 << 1)	// ���  ���� �������ΰ���
#define		ITEM_FLAG_UPGRADE				((LONGLONG)1 << 2)	// ���׷��̵� ������ �������ΰ�
#define		ITEM_FLAG_EXCHANGE				((LONGLONG)1 << 3)	// ��ȯ ���� �������ΰ���
#define		ITEM_FLAG_TRADE					((LONGLONG)1 << 4)	// �Ÿ� ���� �������ΰ���
#define		ITEM_FLAG_BORKEN				((LONGLONG)1 << 5)	// �ı� ���� �������ΰ���
#define		ITEM_FLAG_MADE					((LONGLONG)1 << 6)	// ���� ���� �������ΰ���
#define		ITEM_FLAG_MIX					((LONGLONG)1 << 7)	// ���� ������ : DB�� ����ȵ�
#define		ITEM_FLAG_CASH					((LONGLONG)1 << 8)	// ���� ������
#define		ITEM_FLAG_LORD					((LONGLONG)1 << 9)	// ���� ���� ������
#define		ITEM_FLAG_NO_STASH				((LONGLONG)1 << 10)	// â�� ���� �Ұ��� ������
#define		ITEM_FLAG_CHANGE				((LONGLONG)1 << 11)	// �ٸ� ������ ���������� ��ȯ ���� ����
#define		ITEM_FLAG_COMPOSITE				((LONGLONG)1 << 12)	// ������ �ռ� ���� ����
#define		ITEM_FLAG_DUPLICATE				((LONGLONG)1 << 13)	// �ߺ� Ȯ��
#define		ITEM_FLAG_LENT					((LONGLONG)1 << 14)	// �뿩�� ����
#define		ITEM_FLAG_RARE					((LONGLONG)1 << 15)	// ���� ������
#define		ITEM_FLAG_ABS					((LONGLONG)1 << 16)	// �ð��� ������
#define		ITEM_FLAG_NOTREFORM				((LONGLONG)1 << 17)	// ���� �Ұ� ������
#define		ITEM_FLAG_ZONEMOVE_DEL			((LONGLONG)1 << 18) // ���̵� �� ������ ����
#define     ITEM_FLAG_ORIGIN				((LONGLONG)1 << 19)	// �������� �ɼ�
#define     ITEM_FLAG_TRIGGER				((LONGLONG)1 << 20)	// Ʈ���� �̺�Ʈ�� ���Ǵ� ������
#define     ITEM_FLAG_RAIDSPECIAL			((LONGLONG)1 << 21)	// ���� ��� ����(���� �ٸ� ������ ���)
#define		ITEM_FLAG_QUEST					((LONGLONG)1 << 22) // ����Ʈ
#define		ITEM_FLAG_BOX					((LONGLONG)1 << 23) //  ��Ű��ο�ڽ�
#define		ITEM_FLAG_NOTTRADEAGENT			((LONGLONG)1 << 24)	// �ŷ������� �Ұ�
#ifdef DURABILITY
#define     ITEM_FLAG_DURABILITY			((LONGLONG)1 << 25)	// ��� ������
#endif
#define		ITEM_FLAG_COSTUME2				((LONGLONG)1 << 26)
#define		ITEM_FLAG_SOCKET				((LONGLONG)1 << 27)		// ���� ���� ���� ������
#define		ITEM_FLAG_SELLER				((LONGLONG)1 << 28)		// ���ο� ������
#define		ITEM_FLAG_CASTLLAN				((LONGLONG)1 << 29)		// ���ָ� ���� ������ ������
#define		ITEM_FLAG_LETSPARTY				((LONGLONG)1 << 30)		// ��Ƽ�������� ( ��Ƽ�� �޼��� ���� )
#define		ITEM_FLAG_NONRVR				((LONGLONG)1 << 31)		// RVR��� �Ұ�
#define		ITEM_FLAG_QUESTGIVE				((LONGLONG)1 << 32)		// ����Ʈ ��� ���� ������
#define		ITEM_FLAG_TOGGLE				((LONGLONG)1 << 33)		// ��� �÷���
#define		ITEM_FLAG_COMPOSE				((LONGLONG)1 << 34)		// �ռ� ��� �÷���
#define		ITEM_FLAG_NOTSINGLE				((LONGLONG)1 << 35)		// �̱۴��� ���Ұ� �÷���
#define		ITEM_FLAG_INVISIBLE_COSTUME		((LONGLONG)1 << 36)		// ���� �ڽ�Ƭ �÷���
#define 	ITEM_FLAG_PHOENIX	((LONGLONG)1 << 37)	
//���� ������ ����
#define		ITEM_NORMAL			0	//�Ϲ� ���� ������
#define		ITEM_COSTUM			1	//���� �ڽ�Ƭ ������
#define		ITEM_COSTUM_SUIT	2	//�ڽ�Ƭ ��Ʈ ������

// ������ �з� TYPE
#define		ITYPE_WEAPON			0		// ����
#define		ITYPE_WEAR				1		// ��
#define		ITYPE_ONCE				2		// ��ȸ��
#define		ITYPE_SHOT				3		// źȯ
#define		ITYPE_ETC				4		// ��Ÿ
#define		ITYPE_ACCESSORY			5		// �Ǽ��縮
#define		ITYPE_POTION			6		// ����

// SUBTYPE : ����  --
#define		IWEAPON_NIGHT			0		// ��絵		����Ʈ
#define		IWEAPON_CROSSBOW		1		// ����			�α�
#define		IWEAPON_STAFF			2		// ������		������
#define		IWEAPON_BIGSWORD		3		// ���			Ÿ��ź
#define		IWEAPON_AXE				4		// ����			Ÿ��ź
#define		IWEAPON_SHORTSTAFF		5		// ��������		������
#define		IWEAPON_BOW				6		// Ȱ			����
#define		IWEAPON_SHORTGUM		7		// �ܰ�			�α�
#define		IWEAPON_MINING			8		// ä������		-
#define		IWEAPON_GATHERING		9		// ä������		-
#define		IWEAPON_CHARGE			10		// ��������		-
#define		IWEAPON_TWOSWORD		11		// �̵���		����Ʈ
#define		IWEAPON_WAND			12		// �ϵ�			����
#define		IWEAPON_SCYTHE			13		// ���̵�		�Ҽ���
#define		IWEAPON_POLEARM			14		// ����			�Ҽ���
#define		IWEAPON_SOUL			15		// �ҿ�(ȥ)		����Ʈ������

// SUBTYPE : �� --
#define		IWEAR_HELMET			0		// �Ӹ�
#define		IWEAR_ARMOR				1		// ����
#define		IWEAR_PANTS				2		// ����
#define		IWEAR_GLOVE				3		// �尩
#define		IWEAR_SHOES				4		// �Ź�
#define		IWEAR_SHIELD			5		// ����
#define		IWEAR_BACKWING			6		// ��¦
#define		IWEAR_SUIT				7		// �ѹ�

// SUBTYPE : ��ȸ�� --
#define		IONCE_WARP				0		// �̵�
#define		IONCE_PROCESS_DOC		1		// ���� ����
#define		IONCE_MAKE_TYPE_DOC		2		// ����� ���� ����
#define		IONCE_BOX				3		// ����
#define		IONCE_MAKE_POTION_DOC	4		// ���� ���� ����
#define		IONCE_CHANGE_DOC		5		// ���� �ֹ���
#define		IONCE_QUEST_SCROLL		6		// ����Ʈ ����
#define		IONCE_CASH				7		// ĳ�� ������
#define		IONCE_SUMMON			8		// ���� ��ȯ��
#define		IONCE_ETC				9		// ��Ÿ �ϵ��ڵ� ��ȸ�� ������
#define		IONCE_TARGET			10		// Ÿ�Ͽ� ����������
#define		IONCE_TITLE				11		// ȣĪ �ý���
#define		IONCE_REWARD_PACKAGE	12		// ���� ��Ű�� -> ������ ��Ű���� ���� : �� Ÿ���� �������� ����ϸ� ������ ��Ű�� ������ ���޵ȴ�.
#define		IONCE_JUMPING_POTION	13		// ���� ���� : ����ϸ� ĳ���� ������ Ư�� ������ �÷��ִ� ������
#define		IONCE_EXTEND_CHARACTER_SLOT	14 // ĳ���� Ȯ�� ���� ������
#define		IONCE_SERVER_TRANS		15		//���� ���� ������
#define		IONCE_REMOTE_EXPRESS	16		// ���� â�� ������
#define		IONCE_JEWEL_POCKET			17	// �Ϲ� ���� �ָӴ�
#define		IONCE_CHAOS_JEWEL_POCKET	18	// ī���� ���� �ָӴ�
#define		IONCE_CASH_INVENTORY		19	// �κ� ���� (���� ����)
#define		IONCE_PET_STASH				20	// �� â�� �̿��
#define		IONCE_GPS			21		//	gps ������
#define		IONCE_HOLY_WATER	22		//	���� ������
#define		IONCE_PROTECT_PVP	23		//PVP ��ȣ
#define		IONCE_SEAL			24

// IONCE_WARP : ����
#define		IONCE_WARP_RETURN		0		// Ư�� �� ��ȯ ��ġ
#define		IONCE_WARP_MEMPOS		1		// ���� ��ҷ� �̵�
#define		IONCE_WARP_MARGADUM_PVP	2		// �޶�ũ pvp �̵�
#define		IONCE_WARP_PARTYRECALL	3		// 060227 : bs : ��Ƽ����
#define		IONCE_WARP_MEMPOSPLUS	4		// ���� ������ �̵�
#define		IONCE_WARP_NPC_PORTAL_SCROLL 30 // NpcPortalScroll �� �ӽ� ���� �������� ������� �ʴ´�.

// IONCE_BOX : ����
#define		IONCE_BOX_REMAKE		0		// ��Ȱ�ǻ���
#define		IONCE_BOX_ARCANE		1		// ����ǻ���
#define		IONCE_BOX_COLLECT_BUG	2		// ���� ä�� ����

// SUBTYPE : źȯ --
#define		ISHOT_ATKBULLET		0	// ���ú���
#define		ISHOT_MPBULLET		1	// ��������
#define		ISHOT_ARROW			2	// ȭ��

// SUBTYPE : ��Ÿ --
#define		IETC_QUEST			0	// ����Ʈ��
#define		IETC_EVENT			1	// �̺�Ʈ��
#define		IETC_SKILLUP		2	// ��ų ���
#define		IETC_UPGRADE		3	// ����
#define		IETC_MATERIAL		4	// ���
#define		IETC_MONEY			5	// ��
#define		IETC_PRODUCT		6	// ����ǰ
#define		IETC_PROCESS		7	// ����ǰ
#define		IETC_OPTION			8	// �ɼ�
#define		IETC_SAMPLE			9	// �÷�
#define		IETC_TEXTURE		10	// �ؽ��� For Client
#define		IETC_MIX_TYPE1		11	// ��������1
#define		IETC_MIX_TYPE2		12	// ��������2
#define		IETC_MIX_TYPE3		13	// ��������3
#define		IETC_PET_AI			14	// ��
#define		IETC_QUEST_TRIGGER	15	// ����Ʈ Ʈ����
#define		IETC_JEWEL			16	// ����
#define		IETC_STABILIZER		17	// ������
#define		IETC_PROCESS_SCROLL	18	// ���� ��ũ��
#define		IETC_MONSTER_MERCENARY_CARD 19 // ���� �뺴 ī��
#define		IETC_GUILD_MARK		20
#define		IETC_REFORMER		21
#define		IETC_CHAOSJEWEL		22	//ī���� ����
#define		IETC_FUNCTIONS		23	//��ɼ�
#define		IETC_RVR_JEWEL		24	//â���� ����

// IETC_PROCESS ����1
#define		IETC_PROCESS_STONE			0	// ���� ����ǰ
#define		IETC_PROCESS_PLANT			1	// �Ĺ� ����ǰ
#define		IETC_PROCESS_ELEMENT		2	// ���� ����ǰ

// IETC_PROCESS ����2
#define		IETC_PROCESS_STONE_0		0	// ���� �� ����ǰ
#define		IETC_PROCESS_STONE_1		1	// ���� ���� ����ǰ
#define		IETC_PROCESS_STONE_2		2	// ���� ���� ����ǰ
#define		IETC_PROCESS_STONE_3		3	// ���� ��Ʈ ����ǰ
#define		IETC_PROCESS_STONE_4		4	// ���� ������ ����ǰ

#define		IONCE_PROCESS_PLANT_0		0	// ũ���� ����� ����ǰ
#define		IONCE_PROCESS_PLANT_1		1	// ũ���� �ٱ� ����ǰ
#define		IONCE_PROCESS_PLANT_2		2	// ũ���� �Ķ��� ����ǰ
#define		IONCE_PROCESS_PLANT_3		3	// ũ���� ���� ����ǰ
#define		IONCE_PROCESS_PLANT_4		4	// ũ���� �� ����ǰ

#define		IONCE_PROCESS_ELEMENT_0		0	// E��� ���� ����ǰ
#define		IONCE_PROCESS_ELEMENT_1		1	// D��� ���� ����ǰ
#define		IONCE_PROCESS_ELEMENT_2		2	// C��� ���� ����ǰ
#define		IONCE_PROCESS_ELEMENT_3		3	// B��� ���� ����ǰ
#define		IONCE_PROCESS_ELEMENT_4		4	// A��� ���� ����ǰ

// IETC_OPTION ����
#define		IETC_OPTION_TYPE_BLOOD	0	// ������ ��
#define		IETC_OPTION_TYPE_CLEAR	1	// ��ȭ��

// IETC_UPGRADE ����
#define		IETC_UPGRADE_GENERAL		0	// �Ϲ����ü�
#define		IETC_UPGRADE_SPECIAL		1	// �������ü�
#define		IETC_UPGRADE_SPECIAL_SUPER	2	// ���۰������ü�//0627
#define		IETC_UPGRADE_BOOSTER		3	// �ν���
#define		IETC_UPGRADE_LUCKY			4	// ����� ���� ���ü�
#define		IETC_UPGRADE_PLATINUM		5	// �÷�Ƽ�� ���ü�
#define		IETC_UPGRADE_CHAOS			6	// Ư�� ���ü�
#define		IETC_UPGRADE_PURITY_RUNE	7   // ��ȭ�� ��
#define		IETC_UPGRADE_DEVIL_RUNE		8   // �Ǹ��� ��
#define		IETC_UPGRADE_CHAOS_RUNE		9	// ī���� ��
#define		IETC_UPGRADE_SUPER_RUNE		10	// �ʰ��� ��
#define		IETC_UPGRADE_LUCKY_RUNE		11	// ��� ��
#define 	IETC_OPAL_RUNE				12
#define     IETC_UPGRADE_LETSPLAY_RUNE	13
#define		IETC_PVP_RUNE				14
// IETC_REFORMER ����
#define		IETC_REFORMER_MID_GRADE		0	// �߱� ������
#define		IETC_REFORMER_HIGH_GRADE	1	// ��� ������
#define     IETC_MEGA_REFORMER_GRADE	2

// SUBTYPE : �Ǽ��縮
#define		IACCESSORY_CHARM		0	// ����
#define		IACCESSORY_MAGICSTONE	1	// ���ü�
#define		IACCESSORY_LIGHTSTONE	2	// ��¦�̴µ�
#define		IACCESSORY_EARING		3	// �Ͱ���
#define		IACCESSORY_RING			4	// ����
#define		IACCESSORY_NECKLACE		5	// �����
#define		IACCESSORY_PET			6	// ��
#define		IACCESSORY_ATTACK_PET	7	// ������ ��
#define		IACCESSORY_ARTIFACT		8	// ����

// SUBTYPE : ����
#define		IPOTION_STATE			0	// ����ġ��
#define		IPOTION_HP				1	// HPȸ��
#define		IPOTION_MP				2	// MPȸ��
#define		IPOTION_DUAL			3	// ���ȸ��
#define		IPOTION_STAT			4	// Stat���
#define		IPOTION_ETC				5	// ��Ÿ (�̵����)
#define		IPOTION_UP				6	// �������
#define		IPOTION_TEARS			7	// ����
#define		IPOTION_CRYSTAL			8	// ����
#define		IPOTION_NPC_PORTAL		9	// npc��Ż��ũ�� Ÿ�� (NHN ä�θ� ����)
#define		IPOTION_HP_SPEEDUP		10	// hpȸ���ӵ�����
#define		IPOTION_MP_SPEEDUP		11  // mpȸ���ӵ�����
#define		IPOTION_PET_HP			12  // ��hpȸ��
#define		IPOTION_PET_SPEEDUP		13  // ���̼���
#define		IOPTION_TOTEM			14	
#define		IPOTION_PET_MP			15  // ��hpȸ��


// IPOTION_TEARS ����
#define		IPOTION_TEARS_TYPE_SAFE		0	// ������ ����
#define		IPOTION_TEARS_TYPE_FORGIVE	1	// �뼭�� ����

#define MAX_INVENTORY_SIZE			100							// �� �� �ִ� ������ ����
#define ITEMS_PER_ROW				5							// �� �ٴ� �ִ� ������ ����
#define MAX_INVENTORY_ROWS			(MAX_INVENTORY_SIZE / ITEMS_PER_ROW)	// �ټ�
#define MAX_SERIAL_LENGTH			20							// �ø��� ��ȣ ����
#define MAX_ITEM_BUY				20							// �������� �ִ� �� �� �ִ� ������ ������ ��
#define MAX_ITEM_SELL				20							// ������ �ִ� �� �� �ִ� ������ ������ ��
#define	GROUND_ITEM_PULSE			(5 * PULSE_REAL_MIN)		// ���� ������ �������� �ð� 60s
#define	ITEM_PREPERENCE_PULSE		(30 * PULSE_REAL_SEC)		// ������ �켱�� ���� �ð� 10s

#define MAX_QUEST_INVENTORY_ROWS	(MAX_INVENTORY_SIZE / 20)
#define MAX_EVENT_INVENTORY_ROWS	(MAX_INVENTORY_SIZE / 20)

// ������ ���׷��̵� ����
#define	ITEM_UPGRADE_RESULT_PLUS		0		// +1
#define	ITEM_UPGRADE_RESULT_MINUS		1		// -1
#define	ITEM_UPGRADE_RESULT_NOCHANGE	2		// 0
#define	ITEM_UPGRADE_RESULT_BROKEN		3		// ����
#define	ITEM_UPGRADE_PLATINUM_RESULT_PLUS 4		// �÷�Ƽ�� �÷����� �߶���
#define ITEM_UPGRADE_RUNE_PROTECTION_ITEM 5		// HIGH_RUNE_PROTECTION_ITEM ��� Rune item ���
#define ITEM_UPGRADE_RUNE_ENCHANTMENT	6		//Adding this for messages regarding the "enchantment runes"

#define ITEM_UPGRADE_PROB_PLUS_VALUE		12			// 12���� ���� �Ǵ� ��ġ
#define ITEM_UPGRADE_PROB_PLUS_PENALTY_LEV	200			// ���׷��̵� ��ġ�� �������� Ȯ��
#define ITEM_UPGRADE_PROB_PLUS_PENALTY_MAX	4000		// ���׷��̵� �ִ� �������� Ȯ�� (40%) -> �ּ� ���� Ȯ�� ������ ���� ��
#define	ITEM_UPGRADE_PROB_GENERAL_PLUS		5000		// �Ϲ� ���ü� Ȯ�� 50%
#define ITEM_UPGRADE_PROB_SPECIAL_NOCHANGE	2000		// ���� ���ü� ���� Ȯ�� 20% (1 ~ 20)
#define ITEM_UPGRADE_PROB_SPECIAL_BROKEN	2700		// ���� ���ü� �ı� Ȯ�� 7% (21 ~ 30)
#define ITEM_UPGRADE_PROB_SPECIAL_PLUS		7700		// ���� ���ü� ���� �ִ� Ȯ�� 50% (31 ~ 80)

#define ITEM_UPGRADE_PENALTY_BROKEN			3			// �����ų� -1 ���� ������ ����� �Ѱ�

#define ITEM_UPGRADE_GENERAL_MINLEVEL		1			// �Ϲ����ü� �ּ� 1���� ����
#define ITEM_UPGRADE_GENERAL_MAXLEVEL		146			// �Ϲ� ���ü��� �ִ� ���� (Ȯ���� ���ʹ� 146�̻��� ������ ���׷��̵�)

#define ITEM_REFINE_RESULT_TWO				0			// ���� �Ϲ� ���ü� 2��
#define ITEM_REFINE_RESULT_ONE				1			// �� �Ϲ� ���ü� 1��
#define ITEM_REFINE_RESULT_SPECIAL			2			// ���� ���ü� 1��

// ���� ����
#define MAX_WEARING					28	// ĳ���� �� �ִ� ���� ��� �� : ���� ���� ���� ���� ���� �尩 �Ź� �Ǽ�1 �Ǽ�2 �Ǽ�3 �ֿϵ��� ��
#define WEARING_NONE				-1	// ���� ����

#define WEARING_SHOW_START			0	// �ܺη� ���̴� ���� ��� ���� �ε���
#define WEARING_SHOW_END			9	// �ܺη� ���̴� ���� ��� �� �ε���

#define WEARING_HELMET				0	// ���� ��� ����
#define WEARING_ARMOR_UP			1
#define WEARING_WEAPON				2
#define WEARING_ARMOR_DOWN			3
#define WEARING_SHIELD				4
#define WEARING_GLOVE				5
#define WEARING_BOOTS				6
#define WEARING_ACCESSORY1			7
#define WEARING_ACCESSORY2			8
#define WEARING_ACCESSORY3			9
#define WEARING_PET					10

#define WEARING_BACKWING			11
#define WEARING_ACCESSORY4			12 // newslot - alanssoares
#define WEARING_SPECIAL_ACCESSORY1	13 // newslot - alanssoares
#define WEARING_SPECIAL_ACCESSORY2	14 // newslot - alanssoares
#define WEARING_SPECIAL_ACCESSORY3	15 // newslot - alanssoares
#define WEARING_SPECIAL_ACCESSORY4	16 // newslot - alanssoares
#define WEARING_SPECIAL_ACCESSORY5	17 // newslot - alanssoares

#define COSTUME2_WEARING_HELMET				20	// ���� ��� ����
#define COSTUME2_WEARING_ARMOR_UP			21
#define COSTUME2_WEARING_WEAPON				22
#define COSTUME2_WEARING_ARMOR_DOWN			23
#define COSTUME2_WEARING_SHIELD				24
#define COSTUME2_WEARING_GLOVE				25
#define COSTUME2_WEARING_BOOTS				26
#define COSTUME2_WEARING_BACK				27

#define COSTUME2_WEARING_SUIT				30

#define COSTUME2_WEARING_START				20 // COSTUME2 WEARING START NUMBER.
#define MAX_COSTUME_WEARING					8
#define DEFAULT_MAX_WEARING					18 // newslot - alanssoares

// [110207:selo] �� �� �ǻ�
#define COSTUME2_SUIT_MAX_WEARING			5	// �� �� �ǻ󿡼� ������ ���� ����

/////////////////
// ��Ʈ ������ ����
#define MAX_SET_ITEM_OPTION			11			// ��Ʈ �����ۿ� �ٴ� �ִ� �ɼ� ����

#define SET_ITEM_OPTION_NONE		-1
#define SET_ITEM_OPTION				0			// ��Ʈ �����ۿ� �ٴ� �ɼ�
#define SET_ITEM_SKILL				1			// ��Ʈ �����ۿ� �ٴ� ��ų

/////////////////
// ���� �ý��� ����
#define		MAX_FACTORY_ITEM_STUFF	5			// ���� ������ �ִ� ��� ��
#define		MAX_SEAL_TYPE_SKILL		10			// ���� ��ų ����

/////////////////
// ��ȯ ���� ���

#define		MAX_EXCHANGE_ITEMS		10		// �ִ� ��ȯ ����

//////////////////////////
// ���� ����

#define		HATE_DECREASE_UNIT		100						// HATE ���� ����
#define		HATE_FIRST_ATTACK		1500					// ������ HATE ��ġ�� 1/10000 ����
#define		NPC_DISABLE_TIME		(PULSE_REAL_SEC * 3)	// npc ���� �� �Ⱥ��̸鼭 �����̴� �ð� : 3 sec
#define		NPC_ACTIVITY_DELAY		10						// npc �ൿ ������ 10 : 1��
#define		MAX_PENALTY_EXP_LEVEL	(7.01f)					// �������� ���� �ִ� ���Ƽ ����ġ : 7����
#define		MAX_PENALTY_SP_LEVEL	10						// �������� ���� �ִ� ���Ƽ SP : 10����
#define		DOWN_LEVEL_EXP			10						// ���� ���� ���� ������� ����ġ �϶� ��ġ %
#define		DOWN_LEVEL_SP			10						// ���� ���� ���� ������� SP �϶� ��ġ %
#define		UP_LEVEL_SP				5						// ���� ���� ���� ������� SP ��� ��ġ %
#define		MONEY_DROP_PROB			8000					// pc -> npc npc������ �� ��� Ȯ��
#define		UNIT_CEHCK_BLOCK		0.5f					// ���� ���ݽ� ���� üũ ���� : 0.5m
#define		NPC_ATTACK_DELETE_PULSE	(PULSE_REAL_MIN * 3)	// ��������Pulse �ش�ð����� ���ݾ����� �� ���ø���Ʈ���� ����

#define		ACCESSORY_USED_ATTACK		10			// ���� �� �Ǽ��縮 ������ 10 ����
#define		ACCESSORY_USED_DEFENSE		10			// ��� �� �Ǽ��縮 ������ 10 ����
#define		ACCESSORY_USED_DEATH		200			// ��� �� �Ǽ��縮 ������ 200 ����

// ����� ����ġ �г�Ƽ
#define		DEATH_PENALTY_EXP_1		((double)0.00)			// 1 ~ 10
#define		DEATH_PENALTY_EXP_2		((double)0.05)			// 11 ~ 20
#define		DEATH_PENALTY_EXP_3		((double)0.03)			// 21 ~ 35
#define		DEATH_PENALTY_EXP_4		((double)0.02)			// 36 ~

// ����� SP �г�Ƽ
#define		DEATH_PENALTY_SP_1		((double)0.00)			// 1 ~ 10
#define		DEATH_PENALTY_SP_2		((double)0.05)			// 11 ~ 20
#define		DEATH_PENALTY_SP_3		((double)0.03)			// 21 ~ 35
#define		DEATH_PENALTY_SP_4		((double)0.02)			// 36 ~

// ���� �÷���
#define		HITTYPE_MISS			(1 << 0)		// ȸ��
#define		HITTYPE_WEAK			(1 << 1)		// ���ϰ�
#define		HITTYPE_NORMAL			(1 << 2)		// ����
#define		HITTYPE_STRONG			(1 << 3)		// ���ϰ�
#define		HITTYPE_HARD			(1 << 4)		// �ſ� ���ϰ�
#define		HITTYPE_CRITICAL		(1 << 5)		// ũ��Ƽ��
#define		HITTYPE_DEADLY			(1 << 6)		// �׵��� ���ϰ�

#define		HITTYPE_MAX_PROB_MISS		5000		// �̽�
#define		HITTYPE_MAX_PROB_WEAK		3000		// ��ũ
#define		HITTYPE_MAX_PROB_STRONG		3000		// ��Ʈ��
#define		HITTYPE_MAX_PROB_HARD		2000		// �ϵ�
#define		HITTYPE_MAX_PROB_CRITICAL	1500		// ũ��
#define		HITTYPE_MAX_PROB_DEADLY		1000		// ���鸮

// �⺻ ���� �Ÿ�
#define		ATTACK_RANGE_TITAN				2.3f	// Ÿ��ź
#define		ATTACK_RANGE_KNIGHT				2.3f	// ����Ʈ
#define		ATTACK_RANGE_HEALER				20.0f	// ����
#define		ATTACK_RANGE_MAGE				15.0f	// ������
#define		ATTACK_RANGE_ROGUE_1			2.3f	// �α� : �ܰ�
#define		ATTACK_RANGE_ROGUE_2			15.0f	// �α� : ����
#define		ATTACK_RANGE_SORCERER			3.0f	// �Ҽ���
#define		ATTACK_RANGE_SORCERER_HELLOUND	15.0f	// �Ҽ��� : ���� : ����
#define		ATTACK_RANGE_SORCERER_ELENEN	3.0f	// �Ҽ��� : ���� : ������
#define		ATTACK_RANGE_NIGHTSHADOW		15.0f	// ����Ʈ ������

///////////////////////////
// ��Ƽ ����

#define		MAX_PARTY_MEMBER		8			// �ִ� ��Ƽ �ο�
#define		PARTY_PLUS_EXP			10			// ��Ƽ ��ɽ� �߰� ����ġ : 10%
#define		PARTY_PLUS_SP			10			// ��Ƽ ��ɽ� �߰� SP : 10%
#define		PARTY_PLUS_EXP_COUNT	5			// ��Ƽ �ο��� ���� �߰� ����ġ : 5%
#define		PARTY_PLUS_SP_COUNT		5			// ��Ƽ �ο��� ���� �߰� SP : 5%

// ��Ƽ ����ġ ��н�
#define		PARTY_EXP_DAMAGE		60			// ������ ���� ����ġ
#define		PARTY_EXP_SAME			20			// ��Ƽ �յ� ����ġ
#define		PARTY_EXP_LEVEL			20			// ���� ���� ����ġ
// ��Ƽ SP ��н�
#define		PARTY_SP_DAMAGE			60			// ������ ���� SP
#define		PARTY_SP_SAME			20			// ��Ƽ �յ� SP
#define		PARTY_SP_LEVEL			20			// ���� ���� SP

/////////////////////////
// character ���� ����

#define		NPC_RECOVER_PULSE		(PULSE_REAL_SEC * 3)		// npc ���� ȸ�� : 3��
#define		PC_RECOVER_PULSE		(PULSE_REAL_SEC * 3)		// pc ���� ȸ�� : 3��

#define		ASSIST_TYPE_SKILL		0		// ���� ���� : ��ų
#define		ASSIST_TYPE_ITEM		1		// ���� ���� : ������

#define		PLAYER_STATE_RESET			(0 << 0)	// �ʱ�ȭ
#define		PLAYER_STATE_SITDOWN		(1 << 0)	// �ɱ�/����
#define		PLAYER_STATE_MOVING			(1 << 1)	// �̵�/����
#define		PLAYER_STATE_WARP			(1 << 2)	// ��ȯ ��
#define		PLAYER_STATE_PKMODE			(1 << 3)	// PK ���				// ADULT_SERVER -> PK ������
#define		PLAYER_STATE_PKMODEDELAY	(1 << 4)	// PK ��� ���� ������	// ADULT_SERVER -> ������
#define		PLAYER_STATE_RAMODE			(1 << 5)	// ������� ���
#define		PLAYER_STATE_CHANGE			(1 << 6)	// ������
#define		PLAYER_STATE_BILLITEM		(1 << 7)	// ���������� ������
#define		PLAYER_STATE_CASHITEM		(1 << 8)	// ĳ�������� ������
#define		PLAYER_STATE_SUPPORTER		(1 << 9)	// ���� ������ �÷��� : Ư�� ������ ����� ����Ʈ
#define		PLAYER_STATE_OTHERZONE		(1 << 10)	// �ٸ� �Ӽ� ��
#define		PLAYER_CRISTAL_RESPOND		(1 << 11)	// ���� ũ����Ż�� ������
#define		PLAYER_STATE_FLYING			(1 << 12)	// ������(����Ʈ������)
#define		PLAYER_STATE_DARKNESS		(1 << 13)	// �絵���(����Ʈ������)
#define		PLAYER_STATE_SKILL			(1 << 14)	// ��ų�ߵ����(����Ʈ������)
#define		PLAYER_STATE_CASH_ZONE_MOVE (1 << 15)	// ĳ��������(��ȯ, ã�ư���, ��Ƽ����)
#define		PLAYER_STATE_INVINCIBILITY	(1 << 16)	// ���� ����

#define		RAMODE_USE_PULSE			(3 * TIME_ONE_MIN)	// ������� ���� �ð� 3min

#define		RAMODE_DELAY_PULSE			(5 * TIME_ONE_MIN)	// ������� ���� �˸� 5s
#define		RAMODE_MAX_TARGET			8			// ������� ���� �ִ� 8
#define		MAX_PK_COUNT				150			// �ִ� PK ���� ��ġ
#define		PK_HUNTER_POINT_MAX			 32000		// ���� �ƽ� ��ġ
#define		PK_HUNTER_POINT_2			 19000		// ���� 2�ܰ�
#define		PK_HUNTER_POINT_1			  6000		// ���� 1�ܰ�
#define		PK_CHAOTIC_POINT_1			 -6000		// ī�� 1�ܰ�
#define		PK_CHAOTIC_POINT_2			-19000		// ī�� 2�ܰ�
#define		PK_CHAOTIC_POINT_MAX		-32000		// ī�� �ƽ� ��ġ

#ifdef PKMODE_LIMIT_LEVEL
#else
#define		PKMODE_LIMIT_LEVEL			15			// ���� ���� PK ����
#endif

#define     PK_NAME_CHAOSLEGION         (-5)
#define     PK_NAME_NECROKNIGHT         (-4)
#define     PK_NAME_OUTLAW              (-3)
#define     PK_NAME_FEARCASTER          (-2)
#define     PK_NAME_MURDERER            (-1)
#define     PK_NAME_NORMAL              ( 0)
#define     PK_NAME_AVENGER             (+1)
#define     PK_NAME_LIGHTPORTER         (+2)
#define     PK_NAME_GUARDIAN            (+3)
#define     PK_NAME_SAINTKNIGHT         (+4)
#define     PK_NAME_DIVINEPROTECTOR     (+5)

/////////////////////////
// Quick Slot ����

#define		QUICKSLOT_PAGE_NUM		4		// 3������
#define		QUICKSLOT_MAXSLOT		12		// 10�� ����â F1-F10

#define		QUICKSLOT_TYPE_EMPTY		-1		// ���� �����
#define		QUICKSLOT_TYPE_SKILL		0		// ��ųŸ��
#define		QUICKSLOT_TYPE_ACTION		1		// �׼�Ÿ��
#define		QUICKSLOT_TYPE_ITEM			2		// ������Ÿ��
#define		QUICKSLOT_TYPE_ITEM_WEAR	3	    // ���� ������ Ÿ��

///////////////////////
// �޼��� ������ ��ũ��
#define SEND_Q(msg, desc)		{ if (desc != NULL) (desc)->WriteToOutput(msg); }

////////////////////////
// ������ ���� ���� ����
#define CONN_WAIT_IDEN			0			// ���� �ý��� ���� ���
#define CONN_PLAYING			1			// �÷�����
#define CONN_CHANGE_SERVER		2			// ���� �̵� ��

#define LOGIN_STATE_FAIL		-1
#define LOGIN_STATE_NOT			0
#define LOGIN_STATE_SUCCESS		1
#define LOGIN_STATE_NOPLAY		2

///////////////////////
// ����, ȸ�� ���� ���
#define		MIN_HITRATE		1000		// �ּ� ���� 10%
#define		MAX_HITRATE		9500		// �ִ� ���� 95%
#define		MIN_CRITICAL	500			// �ּ� ũ��Ƽ�� 5%
#define		MAX_CRITICAL	6600		// �ִ� ũ��Ƽ�� 66%

// ��Ÿ ����Ʈ Ÿ��
#define	EFFECT_ETC_LEVELUP		0	// ������ ����Ʈ
#define	EFFECT_ETC_GOZONE		1	// go_zone ����Ʈ

// �׼� ����
#define ACTION_GENERAL			0	// �Ϲ�
#define ACTION_SOCIAL			1	// �Ҽ�
#define ACTION_PARTY			2	// ��Ƽ
#define ACTION_GUILD			3	// ���
#define ACTION_PET				4	// ��
#define ACTION_TITLE			5	// ȣĪ �ý���

#define	AGT_SITDOWN				3	// �ɱ⼭��
#define	AGT_PKMODE				23	// PK ����
#define AGT_PET_SITDOWN			37	// �� �ɱ�
#define AGT_THROW_WATER			42	// ���Ѹ���
#define AGT_FACTORY				46	// ����

///////////////////////
// �� ��ȣ
#define ZONE_START						0		// ���� ����
#define ZONE_DUNGEON1					1		// ���� 1
#define ZONE_SINGLE_DUNGEON1			2		// �̱� ���� 1
#define ZONE_DUNGEON2					3		// ���� 2
#define ZONE_DRATAN						4		// �ʵ� 2 ���ź
#define ZONE_SINGLE_DUNGEON2			5		// �̱� ���� 2
#define	ZONE_SINGLE_DUNGEON_TUTORIAL	6		// �̱� ���� 1 Ʃ�丮����
#define	ZONE_MERAC						7		// �޶�ũ
#define	ZONE_GUILDROOM					8		// ����
#define	ZONE_DUNGEON3					9		// ���� 3
#define	ZONE_SINGLE_DUNGEON3			10		// �̱� ���� 3
#define	ZONE_SINGLE_DUNGEON4			11		// �̱� ���� 4
#define ZONE_DUNGEON4					12		// ���� 4: ���ź
#define ZONE_FREE_PK_DUNGEON			13		// PK ����
#define ZONE_OXQUIZROOM					14		// OX �����
#define ZONE_EGEHA						15		// ������
#define ZONE_EGEHA_PK					16		// ������ PK��
#define ZONE_EGEHA_DUNGEON_1			17		// ������ ���� 1F~7F
#define ZONE_EGEHA_DUNGEON_8			18		// ������ ���� 8F
#define ZONE_EGEHA_DUNGEON_9			19		// ������ ���� 9F
#define ZONE_EGEHA_DUNGEON_10			20		// ������ ���� 10F

#define ZONE_DRATAN_CASTLE_DUNGEON		21		// ���ź ���� ���� ����
#define ZONE_COMBO_DUNGEON				22		// ���� �޺� ����
#define ZONE_STREIANA					23		// ��Ʈ���̾Ƴ�
#define ZONE_PK_TOURNAMENT				24		// �����𷡹ٶ� ������
#define ZONE_EXTREME_CUBE				25		// ť��
#define ZONE_SPRIT_CAVE					26		// ��ȥ�� ����
#define ZONE_QUANIAN_CAVE				27		// ��Ͼ��� ����
#define ZONE_GOLEM_CAVE					28		// ���� ����
#define ZONE_EBONY_MINE					29		// ������ź��
#define ZONE_MISTY_CANYON				30		// �̽�Ƽ����
#define ZONE_FLORAIM_CAVE				31		// �÷ζ��� ����
#define ZONE_MONDSHINE					32		// ������
#define ZONE_CAPPELLA_1					33		// ����� 1��
#define ZONE_CAPPELLA_2					34		// ����� 2��
#define ZONE_ALTER_OF_DARK				35		// ������ ����
#define ZONE_AKAN_TEMPLE				36		// ��ĭ��� ��
#define ZONE_TRIVIA_CANYON				37		// Ʈ�����
#define ZONE_ROYAL_RUMBLE				38		// �ξⷳ�� ��
#define ZONE_TARIAN						39		// Ÿ����
#define ZONE_BLOODYMIR					40		// ������̸�
#define ZONE_TARIAN_DUNGEON				41		// �������� ���ϴ��� - Ÿ���� ����
#define ZONE_RVR						42		// RVR Test ����
#define ZONE_WARFARE_BATTLE				43
#define ZONE_MISTY_CANYON_EXTREME		44
#define ZONE_ENCHANTED_DUNGEON          45
#define ZONE_MAGMA_CANYON               46

#define FUN_ZONE				47 //new farm

#define CLOUD_EXPEDITION_PARTY_DUNGEONS
//#define CLOUD_EXPEDITION_SOLO_DUNGEONS
#define CLOUD_EXPEDITION_REWORK

#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
#define ZONE_PARTY_DUNGEON0				48
#define ZONE_PARTY_DUNGEON1				49
#define ZONE_PARTY_DUNGEON2				50
#define ZONE_PARTY_DUNGEON3				51
#define ZONE_PARTY_DUNGEON4				52
#endif
#define ZONE_DARK_TEOS 53
#define ZONE_AWAKE_TEOS 54
#define ZONE_RLGL 55
#define	WANDERLUST 56
#define	CUSTOM24 57
#define	EXTREME_DRATAN 58
#define	SPIDER_PYRA 59
///////////////////////////////////////
// Quest ����

// ������ Ÿ��
#define		QTYPE_KIND_REPEAT				0		// �ݺ��� ����Ʈ
#define		QTYPE_KIND_COLLECTION			1		// ������ ����Ʈ
#define		QTYPE_KIND_DELIVERY				2		// ������ ����Ʈ
#define		QTYPE_KIND_DEFEAT				3		// ���� ����Ʈ(�̱۴���1)
#define		QTYPE_KIND_SAVE					4		// ���� ����Ʈ(�̱۴���2)
#define		QTYPE_KIND_MINING_EXPERIENCE	5		// ä�� ü�� ����Ʈ
#define		QTYPE_KIND_GATHERING_EXPERIENCE	6		// ä�� ü�� ����Ʈ
#define		QTYPE_KIND_CHARGE_EXPERIENCE	7		// ���� ü�� ����Ʈ
#define		QTYPE_KIND_PROCESS_EXPERIENCE	8		// ���� ü�� ����Ʈ
#define		QTYPE_KIND_MAKE_EXPERIENCE		9		// ���� ü�� ����Ʈ
#define		QTYPE_KIND_TUTORIAL				10		// Ʃ�丮�� ����Ʈ
#define		QTYPE_KIND_PK					11		// PK ����Ʈ
#define		QTYPE_KIND_SEARCH				12		// Ž�� ����Ʈ

// ��Ƽ������
#define		QTYPE_SCALE_PERSONAL		0
#define		QTYPE_SCALE_PARTY			1
#define     QTYPE_SCALE_BATTLEGROUP		2

// ���ະ Ÿ��
#define		QTYPE_REPEAT_ONCE			0		// 1ȸ�� ����Ʈ
#define		QTYPE_REPEAT_UNLIMITED		1		// ���� ����Ʈ
#define		QTYPE_REPEAT_DAY			2		// ���� ����Ʈ
#define		QTYPE_REPEAT_WEEK			3 //dethunter12 repeat quest weekly.

// ���� Ÿ��
#define		QSTART_NPC					0		// NPC�� ���� ����
#define		QSTART_ITEM					1		// �������� ���� ����
#define		QSTART_LEVEL				2		// ���� ���� ���� ����
#define		QSTART_AREA					3		// Ư�������� �����Ͽ� ����

// ����Ʈ ���� ����
#define		QCONDITION_NPC				0		// NPC
#define		QCONDITION_ITEM				1		// ������
#define		QCONDITION_ITEM_NORMAL		2		// ������(�Ϲ�)
#define		QCONDITION_PC				3		// PC (ĳ���� PK)
#define		QCONDITION_AREA				4
#define		QCONDITION_ITEM_USE			5		// ������(���)
#define		QCONDITION_TRIGGER			6		// Ʈ���� �ߵ�

// ����Ʈ ���� ����
#define		QPRIZE_ITEM					0		// ������
#define		QPRIZE_MONEY				1		// ����
#define		QPRIZE_EXP					2		// ����ġ
#define		QPRIZE_SP					3		// ��ų����Ʈ
#define		QPRIZE_SKILL				4		// ��ų
#define		QPRIZE_SSKILL				5		// Ư����ų
#define		QPRIZE_STATPOINT			6		// ��������Ʈ
#define		QPRIZE_RVRPOINT				7		// RVR ����Ʈ
#define		QPRIZE_EXP_RATE				8

#define		QUEST_MAX_PC				16		// Dethunter12 Max quest Limit
#define		QUEST_MAX_NEED_ITEM			5		// ����Ʈ �� �ʿ������ �ִ� 5

#define		QUEST_MAX_CONDITION			3		// ����Ʈ �������� �ִ� 3
#define		QUEST_MAX_CONDITION_DATA	4		// ����Ʈ �������� �ϳ��� �ΰ� ����Ÿ �ִ� 4
#define		QUEST_MAX_ITEM_DROP_MONSTER	3		// ���� ����Ʈ : ������ ��� ���� �ִ� 3

#define		QUEST_MAX_PRIZE				5		// ����Ʈ ���� �ִ� 5

#define		QUEST_MAX_OPTPRIZE			7

#define		QUEST_MAX_NPC				50		// npc �ϳ��� �ִ� ����Ʈ ���� �� 50
#define		QUEST_MAX_PC_COMPLETE		100		// pc�� �Ϸ��� 1ȸ�� ����Ʈ �ִ� �� 100

// ����Ʈ ���� ���
#define		QUEST_STATE_ALL				0		// ��ü ����Ʈ �˻���
#define		QUEST_STATE_INIT			1		// ����Ʈ �ʱ� ����
#define		QUEST_STATE_RUN				2		// ����Ʈ ���� ��
#define		QUEST_STATE_DONE			3		// ����Ʈ �Ϸ� ���� (���� �Ϸ�)
#define		QUEST_STATE_ABANDON			4		// ����Ʈ ���� ����

#define		S2_TICKET_MOB_START			165		// �̱۴���2 ����� �ֱ� (���������) ������ ����
#define		S2_TICKET_MOB_END			175		// �̱۴���2 ����� �ֱ� (���������) ������ ��

#define		S2_TICKET_LEVEL_START		165		// �̱۴���2 ����� �ֱ� (������) pc���� ����
#define		S2_TICKET_LEVEL_END			175		// �̱۴���2 ����� �ֱ� (������) pc���� ��

#define		S2_TICKET_DROP_PROB			50		// �̱۴���2 ����� ��� Ȯ��

#define		S2_TICKET_QUEST_DONE		5		// 5ȸ ����Ʈ �Ϸ��ϸ� ����� ����

////////////////////////////
// ������ ��� Ȯ��
#define		DROP_PHOENIX_MEMBERS_TICKET		10		// �Ǵн� ���Ա� ��� Ȯ��  0.1%

/////////////////////
// �̺�Ʈ ���� �����
// #define BETAEVENT						// Ŭ�� �̺�Ʈ

/////////////////////
// �ɼ� ���� �׸��
//
#define		OPTION_STR_UP				0		// �� ���
#define		OPTION_DEX_UP				1		// ��ø ���
#define		OPTION_INT_UP				2		// ���� ���
#define		OPTION_CON_UP				3		// ü�� ���
#define		OPTION_HP_UP				4		// ������ ���
#define		OPTION_MP_UP				5		// ���� ���

#define		OPTION_DAMAGE_UP			6		// ���� ���ݷ� ���
#define		OPTION_MELEE_DAMAGE_UP		7		// ���� �ٰŸ� ���ݷ� ���
#define		OPTION_RANGE_DAMAGE_UP		8		// ���� ���Ÿ� ���ݷ� ���
#define		OPTION_MELEE_HIT_UP			9		// ���� ���� ���߷� ���
#define		OPTION_RANGE_HIT_UP			10		// ���� ���Ÿ� ���߷� ���

#define		OPTION_DEFENSE_UP			11		// ���� ���� ���
#define		OPTION_MELEE_DEFENSE_UP		12		// ���� �ٰŸ� ���� ���
#define		OPTION_RANGE_DEFENSE_UP		13		// ���� ���Ÿ� ���� ���
#define		OPTION_MELEE_AVOID_UP		14		// ���� ���� ȸ���� ���
#define		OPTION_RANGE_AVOID_UP		15		// ���� ���Ÿ� ȸ���� ���

#define		OPTION_MAGIC_UP				16		// ���� ���ݷ� ���
#define		OPTION_MAGIC_HIT_UP			17		// ���� ���߷� ���
#define		OPTION_RESIST_UP			18		// ���� ���� ���
#define		OPTION_RESIST_AVOID_UP		19		// ���� ȸ���� ���

#define		OPTION_ALL_DAMAGE_UP		20		// ��ü ���ݷ� ��� (��������, ���ݹ���, ����)
#define		OPTION_ALL_HIT_UP			21		// ��ü ���߷� ��� (��������, ���ݹ���, ����)

#define		OPTION_ALL_DEFENSE_UP		22		// ��ü ���� ��� (��������, ���ݹ���, ����)
#define		OPTION_ALL_AVOID_UP			23		// ��ü ȸ���� ��� (��������, ���ݹ���, ����)

#define		OPTION_NOT_USED_24			24		// ��� ����
#define		OPTION_NOT_USED_25			25		// ��� ����

#define		OPTION_ATTR_FIRE			26
#define		OPTION_ATTR_WATER			27
#define		OPTION_ATTR_WIND			28
#define		OPTION_ATTR_EARTH			29
#define		OPTION_ATTR_DARK			30
#define		OPTION_ATTR_LIGHT			31

// ���� ���� �����ۿ� �ɼ�
#define		OPTION_MIX_STR				36		// ��
#define		OPTION_MIX_DEX				37		// ��ø
#define		OPTION_MIX_INT				38		// ����
#define		OPTION_MIX_CON				39		// ü��

#define		OPTION_MIX_ATTACK			40		// ����
#define		OPTION_MIX_MAGIC			41		// ����
#define		OPTION_MIX_DEFENSE			42		// ����
#define		OPTION_MIX_RESIST			43		// ����

#define		OPTION_MIX_STURN			44		// ����
#define		OPTION_MIX_BLOOD			45		// ������
#define		OPTION_MIX_MOVE				46		// ����
#define		OPTION_MIX_POISON			47		// ������
#define		OPTION_MIX_SLOW				48		// ���ο�
// -- ���� ���� �����ۿ� �ɼ�

// 2006 �Ϲݱ� �ű� �ɼ�
#define		OPTION_DOWN_LIMITLEVEL		49		// �������� ���� �ٿ�
#define		OPTION_INCREASE_INVEN		50		// HPȸ�� ������ (2013 07���������� ������ ��������)
#define		OPTION_STEAL_MP				51		// ���� ����
#define		OPTION_STEAL_HP				52		// ������ ����
#define		OPTION_ATTACK_BLIND			53		// ���� ����
#define		OPTION_ATTACK_POISON		54		// �� ����
#define		OPTION_ATTACK_CRITICAL		55		// ũ��Ƽ�� Ȯ�� ����
#define		OPTION_RECOVER_HP			56		// HP ȸ���� ���
#define		OPTION_RECOVER_MP			57		// MP ȸ���� ���
#define		OPTION_DECREASE_SKILL_DELAY	58		// ��ų ��Ÿ�� ����
#define		OPTION_DECREASE_SKILL_MP	59		// MP �Ҹ� ����
#define		OPTION_RESIST_STONE			60		// ���� ���� ����
#define		OPTION_RESIST_STURN			61		// ���� ���� ����
#define		OPTION_RESIST_SILENT		62		// ħ�� ���� ����
#define		OPTION_BLOCKING				63		// ������ ����
#define		OPTION_MOVESPEED			64		// �̵� �ӵ� ���
// --- 2006 �Ϲݱ� �ű� �ɼ�
#define		OPTION_FLYSPEED				65		// ���� �ӵ� ���
#define     OPTION_ATTACK_DEADLY        66      // ���鸮 Ȯ�� ����

#define		OPTION_STR_UP_RATE			67
#define		OPTION_DEX_UP_RATE			68
#define		OPTION_INT_UP_RATE			69
#define		OPTION_CON_UP_RATE			70
#define		OPTION_HP_UP_RATE			71
#define		OPTION_MP_UP_RATE			72
#define		OPTION_WEAPON_UP_RATE		73
#define		OPTION_ARMOR_UP_RATE		74
#define		OPTION_MELEE_HIT_UP_RATE	75
#define		OPTION_MAGIC_HIT_UP_RATE	76
#define		OPTION_MELEE_AVOID_RATE		77
#define		OPTION_MAGIC_AVOID_RATE		78
#define		OPTION_RECOVER_HP_RATE		79
#define		OPTION_RECOVER_MP_RATE		80
#define		OPTION_TEST_QUEST			81
#define		OPTION_EXP_UP_RATE			82
#define		OPTION_SP_UP_RATE			83
#define		OPTION_APET_TRANS_END		84
//���� �������� ���鼭 �߰��� ������ �ɼ� Ÿ��
#define		OPTION_APET_ELEMENT_HPUP	85
#define		OPTION_APET_ELEMENT_ATTUP	86
#define		OPTION_ATT_FIRE_UP			87		// ȭ�� �Ӽ� ���� ���� ���
#define		OPTION_ATT_WATER_UP			88		// ���� �Ӽ� ���� ���� ���
#define		OPTION_ATT_WIND_UP			89		// ��ǳ �Ӽ� ���� ���� ���
#define		OPTION_ATT_EARTH_UP			90		// ���� �Ӽ� ���� ���� ���
#define		OPTION_ATT_DARK_UP			91		// ��� �Ӽ� ���� ���� ���
#define		OPTION_ATT_LIGHT_UP			92		// �� �Ӽ� ���� ���� ���
#define		OPTION_DEF_FIRE_UP			93		// ȭ�� �Ӽ� ��� ���� ���
#define		OPTION_DEF_WATER_UP			94		// ���� �Ӽ� ��� ���� ���
#define		OPTION_DEF_WIND_UP			95		// ��ǳ �Ӽ� ��� ���� ���
#define		OPTION_DEF_EARTH_UP			96		// ���� �Ӽ� ��� ���� ���
#define		OPTION_DEF_DARK_UP			97		// ��� �Ӽ� ��� ���� ���
#define		OPTION_DEF_LIGHT_UP			98		// �� �Ӽ� ��� ���� ���
#define		OPTION_ALL_STAT_UP			99		// ��� ����(4��) ���
#define		OPTION_PVP_DAMAGE_ABSOLB	100		// PVP ������ ����(%)
#define		OPTION_DEBUF_DECR_TIME		101		// ����� �ð� ����(%)
#define		OPTION_RECOVER_HP_NOTRATE	102		// HPȸ�� ������
#define		OPTION_RECOVER_MP_NOTRATE	103		// MPȸ�� ������
#define		OPTION_INCREASE_STRONG		104		// ������ ����
#define		OPTION_INCREASE_HARD		105		// �ϵ� ���ߵ� ����
#define		OPTION_INCREASE_HP			106		// hp ȸ���� ���
#define		OPTION_CLIENT_1				107		// Ŭ���̾�Ʈ lod�� ���� ������(����� �ϵ��ڵ��Ǿ�����)
#define		OPTION_CLIENT_2				108		// Ŭ���̾�Ʈ lod�� ���� ������(����� �ϵ��ڵ��Ǿ�����)
#define		OPTION_CLIENT_3				109		// Ŭ���̾�Ʈ lod�� ���� ������(����� �ϵ��ڵ��Ǿ�����)
#define		OPTION_CLIENT_4				110		// Ŭ���̾�Ʈ lod�� ���� ������(����� �ϵ��ڵ��Ǿ�����)
#define		OPTION_CLIENT_5				111		// Ŭ���̾�Ʈ lod�� ���� ������(����� �ϵ��ڵ��Ǿ�����)
#define		OPTION_CLIENT_6				112		// Ŭ���̾�Ʈ lod�� ���� ������(����� �ϵ��ڵ��Ǿ�����)

#define     OPTION_NAS_UP_RATE			113
#define     OPTION_BOSS_DAMAGE_UP_RATE			114

#define		MAX_NUM_OPTION				120

#define		OPTION_VALUE_SHIFT			8		// 2byte ���� ���� 1Byte �ɼ� ��ȣ ������ 1Byte �ɼ� ����
#define		OPTION_MAX_LEVEL			7		// �ɼ� �ִ� ���� ���� 7

#define		MAX_ITEM_OPTION				5		// �����ۿ� �ٴ� �ִ� �ɼ�
#define		MAX_ACCESSORY_OPTION		5		// �Ǽ��縮�� ���� �� �ִ� �ִ� �ɼ� ��
#define		MAX_WEAPON_OPTION			5		// ���⿡ ���� �� �ִ� �ִ� �ɼ� ��
#define		MAX_ARMOR_OPTION			3		// ���� ���� �� �ִ� �ִ� �ɼ� ��
#define		MAX_ITEM_OPTION_DEL			3		// �ɼ��� ���� �� �ִ� �ɼ� ��
#define		MAX_TITLE_OPTION			5		// ȣĪ�� �ٴ� �ִ� �ɼ� ��

/////////////////
// ���� �ɼ� ����

// ���� ���
#define RARE_OPTION_GRADE_A			0
#define RARE_OPTION_GRADE_B			1
#define RARE_OPTION_GRADE_C			2
#define RARE_OPTION_GRADE_D			3
#define RARE_OPTION_GRADE_E			4

// ���� Ÿ��
#define RARE_OPTION_TYPE_WEAPON		0
#define RARE_OPTION_TYPE_ARMOR		1
#define RARE_OPTION_TYPE_ACCESSORY	2

/////////////////
// �������� �ɼ� ����
#define MAX_ORIGIN_OPTION			6
#define MAX_ORIGIN_SKILL			3
#define MAX_ORIGIN					MAX_ORIGIN_OPTION + MAX_ORIGIN_SKILL

#define ORIGIN_OPTION_BELONG_NONE	-1
#define ORIGIN_OPTION_BELONG_WEAR	0			// ���� �� �ͼ�

/////////////////////////////
// Blood Point ����

#define		PC_BLOOD_POINT				5000	// �⺻ Blood Point
#define		ATTACK_BLOOD_POINT			15		// ���ݽ� ���� Blood Point
#define		DEFENSE_BLOOD_POINT			3		// ���� ���� Blood Point

///////////////////////////////
// ���� ���� �׸��
//
#define		MAX_PRODUCTS_FROM_NPC		5		// npc�� ����� ����ǰ �ִ� ��
#define		MAX_ACCEPTABLE				4		// npc �Ѹ����� ä�� ���� �ο�
#define		PER_DAMAGE_GET_PRODUCT		5		// 5 ������ ���� ����ǰ ���
#define		MAX_MAKE_ITEM_MATERIAL		10		// ������ ���۽� �ִ� ��� ��
#define		NPC_PRODUCE_DELETE_PULSE	(PULSE_REAL_SEC * 4)	// ���� ����Pulse �ش�ð����� ��������� �� ���ø���Ʈ���� ����

#define		MAX_ACCESSORY_MIX			3		// ��Ȱ�� ���ڿ� ���� ������ ��
#define		MAX_ARCANE_MIX				3		// ����� ���ڿ� ���� ������ ��

#define		ITEM_ARCANE_MATERIAL_UPGRADE		0	// ����� ���� ��� 0�� ���ü�
#define		ITEM_ARCANE_MATERIAL_ACCESSORY		1	// ����� ���� ��� 1�� �Ǽ��縮
#define		ITEM_ARCANE_MATERIAL_SAMPLE			2	// ����� ���� ��� 2�� �÷�

#define		MAKE_SAMPLE_ON_PROCESS_PROB		600		// ������ ������� ����� Ȯ��

#define		MAX_ITEM_MAKE_SUCCESS_PROB	8000	// ������ ���� �ִ� ������ 80%

#define		ETERNAL_PENALTY_PROB		30		// ������ �������� 20% ������
#define		PUBLIC_PENALTY_PROB			60		// �������� �������� 60% ������

#define		GetMakeProb(limitLevel, itemLevel) (limitLevel - itemLevel) * 250

/////////////////////////////
// Special Skill ����
//

// Special Skill Ÿ��
#define		SSKILL_MINING		0	// ä��
#define		SSKILL_GATHERING	1	// ä��
#define		SSKILL_CHARGE		2	// ����
#define		SSKILL_STONE		3	// �������ü�
#define		SSKILL_PLANT		4	// �Ĺ�������
#define		SSKILL_ELEMENT		5	// ����������

#define		SSKILL_MAKE_WEAPON	6	// ���� ���� ���
#define		SSKILL_MAKE_WEAR	7	// �� ���� ���
#define		SSKILL_MAKE_G_B		8	// �尩 ���� ���� ���
#define		SSKILL_MAKE_ARMOR	9	// ���� ���� ���� ���
#define		SSKILL_MAKE_H_S		10	// ���� ���� ���� ���

#define		SSKILL_MAX_LEVEL	5	// Special Skill �ִ� ����

//////////////////////////////////////
// ���� �ý��� ����
//

#define		TEACH_MAX_STUDENTS			10			// �ִ� �߽��� ��
#define		TEACH_LEVEL_TEACHER			50			// �İ��� ���� ����
#define		TEACH_LEVEL_STUDENT			30			// �߽��� ���� ����
#define		TEACH_LEVEL_SUCCESS			50			// ���� ���� ����
#define		TEACH_LIMIT_DAY				10			// 10�� ���� �߽����� ������ ���ϸ� ���� ���踦 ���´�.
#define		TEACH_SP_STUDENT			5			// �߽����� ��ɽ� ���ڰ� ��� ���ʽ� SP 5%
#define		TEACH_SP_TEACHER			2			// �߽����� ��ɽ� ������ ��� ���ʽ� SP 2%
#define		TEACH_STUDENT_MAX_GIVEUP	3			// �߽����� ���� ������ �ִ� Ƚ��

#define		TEACH_FAME_PRIZE			10			// ���� ����ġ

#define		CANCELTEACHER				(1 << 0)	// ������ ����
#define		CANCELSTUDENT				(1 << 1)	// �л��� ����

///////////////
// �� ���� ���

#define MAX_OWN_PET							2				// ���� ���� �Ҽ� �ִ� ����
#define PET_HORSE_QUEST_INDEX				106				// ������Ʈ �ε���
#define PET_DRAGON_QUEST_INDEX				109				// ������Ʈ �ε���
#define PET_BLUE_HORSE_QUEST_INDEX			145				// �Ķ� ������Ʈ �ε���
#define PET_PINK_DRAGON_QUEST_INDEX			146				// ��ũ ������Ʈ �ε���
#define PET_UNKOWN_HORSE_QUEST_INDEX		147				// �Ұ��縮 ������Ʈ �ε���
#define PET_UNKOWN_DRAGON_QUEST_INDEX		148				// �Ұ��縮 ������Ʈ �ε���

#define PET_CRYSTAL_LARGE				11404
#define PET_CRYSTAL_SMALL				11405
#define PET_MINOR_ELIXER				12290
#define PET_MAJOR_ELIXER				12291
#define	PET_HORSE_EGG_INDEX				948				// �� �� �ε���
#define	PET_DRAGON_EGG_INDEX			949				// �� �� �ε���
#define	PET_BLUE_HORSE_EGG_INDEX		1707			// ���縻 �� �ε���
#define	PET_PINK_DRAGON_EGG_INDEX		1706			// ��ũ�� �� �ε���
#define	PET_UNKOWN_HORSE_EGG_INDEX		1709			// �Ұ����Ǹ� �� �ε���
#define	PET_UNKOWN_DRAGON_EGG_INDEX		1708			// �Ұ����ǿ� �� �ε���

#define PET_HORSE_ITEM_INDEX			871				// �� ������ �ε���
#define PET_DRAGON_ITEM_INDEX			872				// �� ������ �ε���
#define PET_BLUE_HORSE_ITEM_INDEX		1710			// �� ������ �ε���
#define PET_PINK_DRAGON_ITEM_INDEX		1711			// �� ������ �ε���
#define PET_UNKOWN_HORSE_ITEM_INDEX		1713			// �� ������ �ε���
#define PET_UNKOWN_DRAGON_ITEM_INDEX	1712			// �� ������ �ε���

#define PET_TYPE_HORSE					(0x10)		// ��
#define PET_TYPE_DRAGON					(0x20)		// ��
#define PET_TYPE_BLUE_HORSE				(0x30)		// �Ķ� ��
#define PET_TYPE_PINK_DRAGON			(0x40)		// ��ũ ��
#define PET_TYPE_UNKOWN_HORSE			(0x50)		// �Ұ����Ǹ�
#define PET_TYPE_UNKOWN_DRAGON			(0x60)		// �Ұ����ǿ�

#define PET_GRADE_CHILD		(0X01)		// �����
#define PET_GRADE_ADULT		(0X02)		// ������
#define PET_GRADE_MOUNT		(0X03)		// Ż��

#define PET_TYPE_MASK		(0xf0)		// Ÿ�� ����ũ
#define PET_GRADE_MASK		(0x0f)		// ��� ����ũ

#define PET_DEFAULT_HUNGRY		50		// ���� ����� ��ġ
#define PET_DEFAULT_SYMPATHY	50		// ���� ������ ��ġ
#define PET_DEFAULT_RUNSPEED	15.0f	// �⺻ �޸��� �ӵ�
#define PET_MAX_HUNGRY			100		// �ִ� ����� ��ġ
#define PET_MAX_SYMPATHY		100		// �ִ� ������
#define PET_MAX_HP				100		// �ִ� HP
#define PET_ADULT_LEVEL			16		// ������ ���� ����
#define PET_MOUNT_LEVEL			31		// Ż�� ���� ����

#define PET_MAX_LEVEL			100		// �� �ְ� ���� 100
#define MAX_APET_LEVEL			165		// ������ �� �ְ� ���� 165

typedef enum _markGuildEmblem
{
	MARK_GUILD_DRATAN = 1,
	MARK_GUILD_MERAC,
	MARK_GUILD_RANKING

} MARK_GUILD_EMBLEM;

typedef enum _tagPetColorType
{
	NON_COLOR		= 0,	// �⺻
	RED_COLOR		= 1,	// ����
	SCARLET_COLOR	= 2,	// ��ȫ
	YELLOW_COLOR	= 3,	// ���
	GREEN_COLOR		= 4,	// �ʷ�
	BLUE_COLOR		= 5,	// �Ķ�
	DEEP_BLUE_COLOR	= 6,	// ����
	VIOLET_COLOR	= 7,	// ����
	BLACK_COLOR		= 8,	// ����
	WHITE_COLOR		= 9,	// ��
	PHOENIX_COLOR	= 10,	// �Ǵн� �̺�Ʈ
	BLACK_HEART_COLOR	= 11,	// ���� ��Ʈ
	WHITE_HEART_COLOR	= 12,	// �Ͼ� ��Ʈ
	YELLOW_HEART_COLOR	= 13,	// ��� ��Ʈ
	BLACK_DIAMOND_COLOR		= 14,	// ���� ���̾�
	BLACK_CLOVER_COLOR		= 15,	// ���� Ŭ�ι�
	BLACK_SPADE_COLOR		= 16,	// ���� �����̵�
	BLACK_SKELETON_COLOR	= 17,	// ���� �ذ�
	WHITE_DIAMOND_COLOR		= 18,	// ��� ���̾�
	WHITE_CLOVER_COLOR		= 19,	// ��� Ŭ�ι�
	WHITE_SPADE_COLOR		= 20,	// ��� �����̵�
	WHITE_SKELETON_COLOR	= 21,	// ��� �ذ�
	YELLOW_DIAMOND_COLOR	= 22,	// ��� ���̾�
	YELLOW_CLOVER_COLOR		= 23,	// ��� Ŭ�ι�
	YELLOW_SPADE_COLOR		= 24,	// ��� �����̵�
	YELLOW_SKELETON_COLOR	= 25,	// ��� �ذ�
	RED_HEART_COLOR		= 26,	// ���� ��Ʈ
	RED_CLOVER_COLOR		= 27,	// ���� Ŭ�ι�
	RED_DIAMOND_COLOR		= 28,	// ���� ���̾�
	RED_SPADE_COLOR		= 29,	// ���� �����̵�
	RED_SKELETON_COLOR		= 30,	// ���� �ذ�
	SCARLET_HEART_COLOR		= 31,	// ��Ȳ ��Ʈ
	SCARLET_CLOVER_COLOR		= 32,	// ��Ȳ Ŭ�ι�
	SCARLET_DIAMOND_COLOR		= 33,	// ��Ȳ ���̾�
	SCARLET_SPADE_COLOR		= 34,	// ��Ȳ �����̵�
	SCARLET_SKELETON_COLOR	= 35,	// ��Ȳ �ذ�
	GREEN_HEART_COLOR		= 36,	// �ʷ� ��Ʈ
	GREEN_CLOVER_COLOR		= 37,	// �ʷ� Ŭ�ι�
	GREEN_DIAMOND_COLOR		= 38,	// �ʷ� ���̾�
	GREEN_SPADE_COLOR		= 39,	// �ʷ� �����̵�
	GREEN_SKELETON_COLOR		= 40,	// �ʷ� �ذ�
	BLUE_HEART_COLOR		= 41,	// �Ķ� ��Ʈ
	BLUE_CLOVER_COLOR		= 42,	// �Ķ� Ŭ�ι�
	BLUE_DIAMOND_COLOR		= 43,	// �Ķ� ���̾�
	BLUE_SPADE_COLOR		= 44,	// �Ķ� �����̵�
	BLUE_SKELETON_COLOR		= 45,	// �Ķ� �ذ�
	DEEP_BLUE_HEART_COLOR		= 46,	// ���� ��Ʈ
	DEEP_BLUE_CLOVER_COLOR	= 47,	// ���� Ŭ�ι�
	DEEP_BLUE_DIAMOND_COLOR	= 48,	// ���� ���̾�
	DEEP_BLUE_SPADE_COLOR		= 49,	// ���� �����̵�
	DEEP_BLUE_SKELETON_COLOR	= 50,	// ���� �ذ�
	VIOLET_HEART_COLOR			= 51,	// ���� ��Ʈ
	VIOLET_CLOVER_COLOR			= 52,	// ���� Ŭ�ι�
	VIOLET_DIAMOND_COLOR		= 53,	// ���� ���̾�
	VIOLET_SPADE_COLOR			= 54,	// ���� �����̵�
	VIOLET_SKELETON_COLOR		= 55,	// ���� �ذ�
	HORSE_WILLIAM_COLOR			= 56,	// Ÿ�¸� ���� WILLIAM ������
	HORSE_ALBER_COLOR			= 57,	// Ÿ�¸� ���� ALBER ������
	HORSE_REDEYE_COLOR			= 58,	// Ÿ�¸� ���� REDEYE ������
	HORSE_ZEBRA_COLOR			= 59,	// Ÿ�¸� ���� ZEBRA  ������
	HORSE_HAROLD_COLOR			= 60,	// Ÿ�¸� ���� HAROLD  ������
	HORSE_VIOLET_COLOR			= 61,	// Ÿ�¸� ���� VIOLET  ������
} PET_COLOR_TYPE;

///////////////////
// ��ȯ�� ���� ���

#define ELEMENTAL_FIRE			0		// ���� ����
#define ELEMENTAL_WIND			1		// �ٶ��� ����
#define ELEMENTAL_EARTH			2		// ������ ����
#define ELEMENTAL_WATER			3		// ���� ����
#define ELEMENTAL_GUARD			4		// ��ȯ ���(�ӽ�)

#define ELEMENTAL_ATTACK_SPEED	20		// �⺻ ����
#define ELEMENTAL_RUN_SPEED		8.0f	// �⺻ �̼�
#define ELEMENTAL_RECOVER_HP	1		// 3�ʿ� ��ȯ�� ü�� ȸ����

#define ELEMENTAL_ATTACK_RANGE_FIRE		2.0f	// ���ݰŸ� : ��������
#define ELEMENTAL_ATTACK_RANGE_WIND		7.0f	// ���ݰŸ� : �ٶ�������
#define ELEMENTAL_ATTACK_RANGE_EARTH	3.0f	// ���ݰŸ� : ����������
#define ELEMENTAL_ATTACK_RANGE_WATER	7.0f	// ���ݰŸ� : ��������
#define ELEMENTAL_ATTACK_RANGE_GUARD	5.0f	// ���ݰŸ� : ���(�ӽ�)

#if defined(LC_KOR) || defined(LC_USA) || defined (LC_GAMIGO) || defined(LC_BILA) || defined(LC_RUS) || defined(LC_TLD)
#define SUMMON_DELAY			(PULSE_REAL_SEC * 5)	// ��ȯ ������
#else
#define SUMMON_DELAY			(PULSE_REAL_MIN * 5)	// ��ȯ ������
#endif
#define SUMMON_DURATION			(TIME_ONE_MIN * 20)	// ��ȯ ���ӽð�

/////////////////
// ���� ���� ���
#define EVOCATION_NONE			0		// ���� ����
#define EVOCATION_HELLOUND		313		// ���� ����
#define EVOCATION_ELENEN		309		// ������ ����

#if defined (LC_RUS)
#define EVOCATION_DELAY			(PULSE_REAL_MIN * 0)	// ���� ������
#else
#define EVOCATION_DELAY			(PULSE_REAL_MIN * 5)	// ���� ������
#endif
#define EVOCATION_DURATION		(PULSE_REAL_MIN * 30)	// ���� ���ӽð�

////////////////////////////////////
// Event ����

////////////////////
// Latto Event ����
#define		LATTO_EVENT_UPGRADE_PROB		3000		// 10%
#define		LATTO_EVENT_BLOOD_PROB			3000		// 10%
#define		LATTO_EVENT_PARTY_PROB			5000		// 50%
#define		LATTO_EVENT_PROCESS_PROB		3000		// 30%
#define		LATTO_EVENT_EXPSP_PROB			3000		// 30%

#define		LATTO_EVENT_EXPSP_LEVEL			15			// 15 ����
#define		LATTO_EVENT_EXP_PERCENT			30			// ���� : 30%
#define		LATTO_EVENT_PARTY_LEVEL_MIN		5			// 5 ����
#define		LATTO_EVENT_PARTY_LEVEL_MAX		15			// 15 ����

#define		CHANGE_26LEVEL_GENERAL_STONE_PROB	800			// 26���� �Ϲ� ���ü� ���� Ȯ��
#define		CHANGE_SPECIAL_STONE_PROB			900			// �������ü� ���� Ȯ��
#define		CHANGE_22LEVEL_EVENT_WEAPON_PROB	1000		// 22���� �̺�Ʈ ���� (������) ���� Ȯ��
#define		CHANGE_31LEVEL_ARMOR_PROB			1100		// 31���� �� ���� (������) ���� Ȯ��
#define		CHANGE_ATTACK_UP_PROB				5300		// ���ݷ� ����� ���� Ȯ��
#define		CHANGE_DEFENSE_UP_PROB				9500		// ���� ����� ���� Ȯ��
#define		CAHNGE_50000NAS_PROB				10000		// 5�� ���� ���� Ȯ��

///////////////////////
// New Year Evnet ����
#define		NEWYEAR_EVENT_RICESOUP_DROP_PROB	1000	// 10%
#define		NEWYEAR_EVENT_RICEMANDO_DROP_PROB	1000	// 10%
#define		NEWYEAR_EVENT_RICESOUP_UP_EXP		12		// 120%
#define		NEWYEAR_EVENT_RICEMANDO_UP_SP		13		// 130%

#define CLIENT_OPTION_EFFECT	( 1 << 0 )
#define CLIENT_OPTION_WARP		( 1 << 1 )

#define GOLDENBALL_STATUS_NOTHING		0
#define GOLDENBALL_STATUS_VOTE			1
#define GOLDENBALL_STATUS_GIFT			2
#define GOLDENBALL_STATUS_VOTE_END		3
#define GOLDENBALL_TEAM_NAME_LENGTH		32
#define GOLDENBALL_BALL_INDEX			1482
#define GOLDENBALL_CARD_INDEX			1483

#define APET_WEAR_HEAD		0
#define APET_WEAR_BODY		1
#define APET_WEAR_WEAPON	2
#define APET_WEAR_ACCE		3
#define APET_WEARPOINT		4

#define APET_MAX_AI			6	// �ִ� AI slot


// t_cashItemdate �ʵ��
#define CASH_ITEM_DATE_FIELD_MEMPOS			"a_mempos_new"
#define CASH_ITEM_DATE_FIELD_CHAR_SLOT0		"a_charslot0_new"
#define CASH_ITEM_DATE_FIELD_CHAR_SLOT1		"a_charslot1_new"
#define CASH_ITEM_DATE_FIELD_STASHEXT		"a_stashext_new"

#if defined (LC_KOR)
#define WAR_CASTLE_SUBNUMBER_MERAC	1	// ������ ������ ���꼭�� ��ȣ
#define RAID_SUBNUMBER		1			// ������ ���̵� ���� ä�� ����
#elif defined(LC_GAMIGO) || defined (LC_BILA) || defined (LC_USA) || defined (LC_RUS)
#define WAR_CASTLE_SUBNUMBER_MERAC  1   // ������ ������ ���꼭�� ��ȣ
#define RAID_SUBNUMBER		1			// ������ ���̵� ���� ä�� ����
#else
#define WAR_CASTLE_SUBNUMBER_MERAC	1	// ������ ������ ���꼭�� ��ȣ
#define RAID_SUBNUMBER		1			// ������ ���̵� ���� ä�� ����
#endif

typedef struct _TimeStruct
{
	int		year;		// ���� �� ���ڸ� % 62
	int		month;		// ��
	int		day;		// ��
	int		hour;		// ��
	int		min;		// ��
	int		sec;		// ��
} TIMESTRUCT;

#define HACK_LIMIT 0.06f
#define HACK_TYPE_PULSE		0
#define HACK_TYPE_CLIENT	1
#define HACK_TYPE_MOVE_SPEED	2
#define HACK_TYPE_ATTACK_SPEED	3

#define STATE_MONSTER_TAMING			(1 << 0)	// ���� ���̹� ����
#define STATE_MONSTER_CONFUSION			(1 << 1)	// ���� ȥ�� ����
#define STATE_MONSTER_NO_SOUL			(1 << 3)	// ���Ͱ� ��ȥ�� ���ѱ� ����
#define STATE_MONSTER_MERCENARY			(1 << 4)	// ���� �뺴 ī�� ��� ����
#define STATE_MONSTER_TOTEM_BUFF		(1 << 5)	// ���Ͱ� �����̵Ǿ� ������ ���� �Ѹ���.
#define STATE_MONSTER_TOTEM_ATTK		(1 << 6)	// ���Ͱ� �����̵��� ������ �ϳ�.
#define STATE_MONSTER_TRAP				(1 << 7)	// ���Ͱ� Ʈ���̴�.
#define STATE_MONSTER_PARASITE			(1 << 9)	// ���Ͱ� ����� ���� ����.
#define STATE_MONSTER_SUICIDE			(1 << 10)	// ���Ͱ� �ڻ� ������ �Ѵ�.
#define STATE_MONSTER_TOTEM_ITEM_BUFF	(1 << 11)	// ���������� ��ȯ�� ����
#define STATE_MONSTER_TOTEM_ITEM_ATTK	(1 << 12)	// ���������� ��ȯ�� ����

#define TRIGGER_MAX_ARRAYCOUNT				10		// Ʈ���� �ɹ� ���� �� �迭�� ���� �ִ� �� ����

//////////triggerSet_type///////
#define TRIGGERSET_ALTER_OF_DARK			1			// ������ ����
#define TRIGGERSET_CAPPELLA_1				2			// ����� 1��
#define TRIGGERSET_CAPPELLA_2				3			// ����� 1��
#define TRIGGERSET_TESTRAID					4			// �׽�Ʈ Raid
#define TRIGGERSET_MONDSHINE				5			// ������
#define TRIGGERSET_STREIANA					6			// ��Ʈ���̾Ƴ�
#define TRIGGERSET_EGEHA					7			// ������
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
#define TRIGGERSET_PARTY_DUNGEON0			8
#define TRIGGERSET_PARTY_DUNGEON1			9
#define TRIGGERSET_PARTY_DUNGEON2			10
#define TRIGGERSET_PARTY_DUNGEON3			11
#define TRIGGERSET_PARTY_DUNGEON4			12
#endif
//////////trigger_type///////
#define TRIGGER_ITEM_COMPOSITION			1			// ������ ����
#define TRIGGER_ITEM_DROP					2			// ������ ���
#define TRIGGER_OPEN_THE_DOOR				3			// �� ����
#define TRIGGER_START_RAID					4			// ���̵� ����(���� �ð� ���� ����)
#define TRIGGER_MESSAGE_PRINT				5			// ���� �޼��� ���
#define TRIGGER_SUMMON_NPC					6			// npc ��ȯ
#define TRIGGER_USE_DEBUF					7			// ����� �ɸ�
#define TRIGGER_ACTIVE_OBJECT				8			// Object Ȱ��ȭ
#define TRIGGER_REMOVE_NPC					9			// npc �ڵ� ����
#define TRIGGER_TIME_LIMIT					10			// �ð� ����
#define TRIGGER_QUEST_COMPLETE				11			// ����Ʈ �Ϸ�
#define TRIGGER_ITEM_GET_INVEN				12			// ������ ȹ��
#define TRIGGER_CONSECUTIVE_DIALOGUE		13			// ���̾�α� ��ȭ
#define TRIGGER_ACTIVE_EFFECT				14			// ����Ʈ �߻�

//////////trigger_Subtype_OpenTheDoor///////
#define TRIGGER_SUBTYPE_NONE_OPEN_THE_DOOR	0
#define TRIGGER_SUBTYPE_NPC_OPEN_THE_DOOR	1
#define TRIGGER_SUBTYPE_ITEM_OPEN_THE_DOOR	2

//////////trigger_Subtype_OpenTheDoor///////
#define TRIGGER_SUBTYPE_NONE_REMOVE_NPC		0
#define TRIGGER_SUBTYPE_ITEM_REMOVE_NPC		1

////////// triggerflag ////////
#define TRIGGER_FLAG_NAMEDNPC_DEATH1					(1 << 0)	// ������ ���� 1�� ���ӵ� NPC ���� �� ����
#define TRIGGER_FLAG_ACTIVE_OBJECT1						(1 << 1)	// ������ ���� 3�� ������Ʈ1 �ߵ� ����
#define TRIGGER_FLAG_ACTIVE_OBJECT2						(1 << 2)	// ������ ���� 3�� ������Ʈ2 �ߵ� ����
#define TRIGGER_FLAG_ACTIVE_OBJECT3						(1 << 3)	// ������ ���� 3�� ������Ʈ3 �ߵ� ����
#define TRIGGER_FLAG_ACTIVE_OBJECT4						(1 << 4)	// ������ ���� 3�� ������Ʈ4 �ߵ� ����
#define TRIGGER_FLAG_NAMEDNPC_SUMMON1					(1 << 5)	// ������ ���� 3�� ���ӵ� NPC ��ȯ �Ǿ����� ����
#define TRIGGER_FLAG_NAMEDNPC_DEATH2					(1 << 6)	// ������ ���� 3�� ���ӵ� NPC ���� �� ����
#define TRIGGER_FLAG_NAMEDNPC_DEATH1_DOOR_SAVE			(1 << 7)	// ������ ���� 1�� ���ӵ� NPC ������ ������ �� Ȱ��ȭ ���� ��Ű��
#define TRIGGER_FLAG_NAMEDNPC_DEATH2_DOOR_SAVE			(1 << 8)	// ������ ���� 3�� ���ӵ� NPC ������ ������ �� Ȱ��ȭ ���� ��Ű��
#define TRIGGER_FLAG_NAMEDNPC_SUMMON_1003				(1 << 9)	// ������ ���� 3�� ���ӵ� NPC ��ȯ�ϴ� ���� Ȱ��ȭ ���� ��Ű��
#define TRIGGER_FLAG_NAMEDNPC_DEATH1002_BEFORE			(1 << 10)	// ������ ���� 1�� ���ӵ� NPC ���� �׾������� ����
#define TRIGGER_FLAG_NAMEDNPC_DEATH1003_BEFORE			(1 << 11)	// ������ ���� 3�� ���ӵ� NPC ���� �׾������� ����
#define TRIGGER_FLAG_NAMEDNPC_DEATH1018_BEFORE			(1 << 12)	// ������ ���� 5�� ���ӵ� NPC ���� �׾������� ����

////////// saveTriggerInfo ////////////
#define TRIGGER_SAVE_ALTER_OF_DARK_NONE		0			// ������ ���� Ʈ���� ���� �ʱ�ȭ
#define TRIGGER_SAVE_ALTER_OF_DARK_1002		1			// npc 1002�� ���� ������ Ʈ���� ����
#define TRIGGER_SAVE_ALTER_OF_DARK_1003		2			// npc 1003�� ���� ������ Ʈ���� ����
#define TRIGGER_SAVE_ALTER_OF_DARK_1018		3			// npc 1018�� ���� ������ Ʈ���� ����, ������ ���� Ŭ����

////////// TriggerSaveMode ////////////
#define TRIGGER_MODE_NONE					0			// DB �۾��� ��ŵ
#define TRIGGER_MODE_SAVE					1			// DB ������ �����ϱ�
#define TRIGGER_MODE_DELLETE				2			// DB ������ �����

////////// Trigger_state_flag ////////////
#define TRIGGER_PROTO_FLAG_CONTINUE			(1 << 0)	// ���� ����
#define TRIGGER_PROTO_FLAG_DOMINO			(1 << 1)	// ���̳� ���� Ʈ���� �ߵ�
#define TRIGGER_PROTO_FLAG_PLAY_ONE_PC		(1 << 2)	// �Ϲ� �ʵ忡�� �� �����Ը� ������ �Ѵ�

#define RAID_JOIN_LEVEL_LIMIT_CAPPELLA					140			// ����� ���� ���� ����
#define RAID_JOIN_LEVEL_LIMIT_ALTER_OF_DARK				160			// ���� ���� ���� ����
#define RAID_JOIN_LEVEL_LOW_LIMIT_AKAN_TEMPLE			165			// ��ĭ��� ���� ���� ����
#define RAID_JOIN_LEVEL_HIGH_LIMIT_AKAN_TEMPLE			175			// ��ĭ��� ���� ���� ����
#define RAID_JOIN_LEVEL_LOW_LIMIT_AKAN_TEMPLE_NORMAL	165			// ��ĭ��� ���� ���� ���� ��� ���̵�
#define RAID_JOIN_LEVEL_HIGH_LIMIT_AKAN_TEMPLE_NORMAL	175			// ��ĭ��� ���� ���� ���� ��� ���̵�
#define RAID_JOIN_LEVEL_LOW_LIMIT_AKAN_TEMPLE_HELL		165			// ��ĭ��� ���� ���� ���� HELL ���̵�
#define RAID_JOIN_LEVEL_HIGH_LIMIT_AKAN_TEMPLE_HELL		185			// ��ĭ��� ���� ���� ���� HELL ���̵�
#define RAID_JOIN_LEVEL_LOW_LIMIT_TARIAN_DUNGEON		175			// Ÿ���� ���� ���� ����
#define RAID_JOIN_LEVEL_HIGH_LIMIT_TARIAN_DUNGEON		175			// Ÿ���� ���� ���� ����

#define TITLE_SYSTEM_NO_TITLE				0			// ȣĪ�� ���� ���� 0
#define TITLE_SYSTEM_OPTION_NUM				0			// CTitle�� Option�� ���� �迭 index
#define TITLE_SYSTEM_OPTION_LEVEL			1			// CTitle�� option�� ���� �迭 index

// ����Ʈ Ʈ����
#define QUESTITEM_MAX_ARRAYCOUNT			10		// ����Ʈ Ʈ���� ������ �ɹ� ���� �� �迭�� ���� �ִ� �� ����

#define MAX_NORMAL_SOCKET_COUNT	6
#define MAX_CHAOS_SOCKET_COUNT	1 
#define MAX_SOCKET_COUNT		(MAX_NORMAL_SOCKET_COUNT + MAX_CHAOS_SOCKET_COUNT)
#define SOCKET_DB_LENGTH	50

#define GUILD_ACTIVE_SKILL_START	-1
#define GUILD_PASSIVE_SKILL_START	-2
#define GUILD_ETC_SKILL_START		-3
#define SKILL_TYPE_ACTIVE			0
#define SKILL_TYPE_PASSIVE			1
#define SKILL_TYPE_ETC				2

// TODO
#define TOUCH_FIELD					0
#define KILL_NPC					1
#define TAKE_ITEM					2
#define ALL_IN_AREA					3
#define NO_IN_AREA					4
#define MOVE_IN_AREA				5
#define MOVE_OUT_AREA				6
#define COUNT_DOWN					7
#define START_RAID					8
#define ITEM_USE					9
#define TODO_MAX_NUM				10

// OUTPUT
#define TOUCH_FIELD					0
#define SUMMON_EXTRA				1
#define SUMMON_DISTRICT				2
#define SUMMON_MBOSS				3
#define SUMMON_BOSS					4
#define GROUND_EFFECT_ON			5
#define GROUND_EFFECT_OFF			6
#define TOGGLE_GATE					7
#define TOGGLE_PORTAL				8
#define CREATE_ITEM_OBJECT			9
#define DEBUFF_SKILL				10
#define END_RAID					11
#define PAUSE_AREA					12
#define BUFF_SKILL					13
#define TOGGLE_CAMERA				14
#define COUNT_DOWN_START			15
#define SAVE_POINT					16
#define MODEL_HOLDER_PADOX			17
#define	NPC_SAY						18
#define APPLY_SKILL					19
#define	CURE_SKILL					20
#define OUTPUT_MAX_NUM				21

#define OBJECT_DATA_FLAG_AUTO_ATTACK (1 << 0)

// OBJECT_TYPE
#define OBJECT_TYPE_TODO			0
#define OBJECT_TYPE_OUTPUT			1
#define OBJECT_TYPE_OBJECT_STATE	2
#define OBJECT_TYPE_OBJECT_REFRESH	3

#define RAID_DATA_STATE_READY		0
#define RAID_DATA_STATE_COMPLETE	1

// OBJECT_LIST
#define OBJECT_TOUCH_FIELD			0
#define OBJECT_GATE					1
#define OBJECT_PORTAL				2
#define OBJECT_ITEM					3
#define OBJECT_PADOX_MODEL			4
#define OBJECT_CAMERA				5

#define DUNGEON_DIFFICULTY_NORMAL	0
#define DUNGEON_DIFFICULTY_HARD		1
#define DUNGEON_DIFFICULTY_HELL		2

#define GUILD_MAX_GRADE_EX		29

#define RAID_RESET_TIME_HOUR		3	// ���� ���� hour
#define RAID_RESET_TIME_MIN			0	// ���� ���� min
// �� ���ú��� ���ϸ��� �ʱ�ȭ �� ������, �����Ͽ� �ѹ��� ������ ���� �� �ִ�.
#define RAID_RESET_TIME_DAY			7	// allday ���ϸ��� �ʱ�ȭ. �̺κ��� �� ���� ���� �������־ �ȴ�.
//#define RAID_RESET_TIME_DAY			0	// sun�� �ʱ�ȭ
//#define RAID_RESET_TIME_DAY			1	// mon�� �ʱ�ȭ
//#define RAID_RESET_TIME_DAY			2	// tue�� �ʱ�ȭ
//#define RAID_RESET_TIME_DAY			3	// wed�� �ʱ�ȭ
//#define RAID_RESET_TIME_DAY			4	// thu�� �ʱ�ȭ
//#define RAID_RESET_TIME_DAY			5	// fri�� �ʱ�ȭ
//#define RAID_RESET_TIME_DAY			6	// sat�� �ʱ�ȭ

#define TREASUREBOX_DROP_LIMIT_RECT	6	// �������� ��� RECT �ȿ� max ����
#define TREASUREBOX_DROP_LIMIT_ZONE	36	// �������� ��� zone �ȿ� max ����
// zonedata flag
#define ZONE_FLAG_TREASUREBOX		(1<<0) // �������� ���

#define TREASURE_BOX_NPC_REGEN 1*60*60	// �������� npc regen �ð�. 1�ð� �ڿ��� npc�� �������.

#define TREASURE_BOX_NPC_INDEX 1255		// �������� npc �ε���
#define TREASURE_MAP_ITEM_INDEX 6941	// �������� ������ �ε���
#define TREASURE_KEY_ITEM_INDEX 6939	// �������� �Ϲ� ���� ������ �ε���

#if defined(LC_GAMIGO) || defined (LC_USA) || defined (LC_BILA) || defined (LC_RUS)
#define WAR_GROUND_CHANNEL			1
#else
#define WAR_GROUND_CHANNEL			2
#endif
#define	MAX_ROYAL_RUMBLE_PLAYER		40
#define	MIN_ROYAL_RUMBLE_PLAYER		10
#define	MIN_ROOKIE_LEVEL			50
#define	MAX_ROOKIE_LEVEL			89
#define MIN_SENIOR_LEVEL			90
#define MAX_SENIOR_LEVEL			120
#define	MIN_MASTER_LEVEL			121
#define	MAX_MASTER_LEVEL			MAX_LEVEL
#define LEVEL_TYPE_ROOKIE			0
#define	LEVEL_TYPE_SENIOR			1
#define LEVEL_TYPE_MASTER			2
#define LEVEL_TYPE_ALL				3
#define ROOKIE_REGIST_NEED_PRICE	1000000
#define	SENIOR_REGIST_NEED_PRICE	10000000
#define	MASTER_REGIST_NEED_PRICE	100000000
#define ROOKIE_REGIST_ITEM			7340
#define SENIOR_REGIST_ITEM			7341
#define MASTER_REGIST_ITEM			7342
#define PLAYER_NOT_SORT				0 // �̺з�
#define PLAYER_SELECTED				1 // ���õ�
#define PLAYER_DROP					2 // Ż��
#define PLAYER_DRAW					3 // ��� ��ο�
#define PLAYER_GREATER_THEN_MAX		0 // ��û�ڰ� maximum���� ũ��
#define PLAYER_SMALLER_THEN_MIN		1 // ��û�ڰ� minimum���� �۴�
#define PLAYER_BETWEEN_MIN_AND_MAX	2 // ��û�ڰ� min~max�̴�.
#define DEBUFF_TYPE_20MINUTE		0
#define DEBUFF_TYPE_8PLAYER			1
#define DEBUFF_TYPE_PEACEZONE		2
#define ROYAL_RUMBLE_DEBUFF_SKILL	1355 // �����ʿ� 1�� �ƴ�
#define WARGROUND_MAX_POINT			1000000
#define WARGROUND_MAX_ACC_POINT		10000000
#define ROYAL_RUMBLE_SCHEDULE		5	// �Ϸ� �ټ����
#if defined (LC_TLD)
#define ROYAL_RUMBLE_START_HOUR		21
#elif defined (LC_USA)
#define ROYAL_RUMBLE_START_HOUR		16
#else
#define ROYAL_RUMBLE_START_HOUR		22
#endif

#define LEVEL_COUNT		2

#ifdef DEV_GUILD_MARK
#define GUILD_MARK_SKILL_INDEX	1378
#endif

#ifdef DEV_GUILD_STASH
#define GUILD_STASH_KEEP_LOG	0
#define GUILD_STASH_TAKE_LOG	1
#endif // DEV_GUILD_STASH
#define MAX_TITLE_COUNT	200

#define RANKING_REFRESH_DAY 1	// ��ŷ ���� ���� (0:�Ͽ��� ~ 6:�����)
#define RANKING_REFRESH_HOUR 6	// ��ŷ ���� �ð�

typedef enum _tagRankingTypeEx
{
	RANKTYPE_LEVELMASTER	= 0,
	RANKTYPE_JOBRANKER		= 1,
} RANKING_TYPE_EX;

//////////////////////////////////////////////////////////////////////////
typedef enum _eventLogType
{
	EVENT_LOGTYPE_AFFINITY_LAKIN	= 0,
	EVENT_LOGTYPE_KILL_EREBUS		= 1,
	EVENT_LOGTYPE_KOKO_MYUN			= 2,
} EVENT_LOG_TYPE;

typedef enum _tagProgressType
{
	PROGRESS_TYPE_NONE = -1,
	PROGRESS_TYPE_CRAFT = 0,
	PROGRESS_TYPE_DECOMPOSE,
	PROGRESS_TYPE_PRODUCE
} PROGRESS_TIME_TYPE;

typedef enum _tagNpcProdceState
{
	NPC_PRODUCE_STATE_ALIVE,	// ä�� ���� ����
	NPC_PRODUCE_STATE_LOOT,		// �� ���� ����
	NPC_PRODUCE_STATE_DEAD,		// ���� ����
} NPC_PRODUCE_STATE;

typedef enum _tagLootType
{
	LOOT_TYPE_PC  = 1,	// CPcLootManager
	LOOT_TYPE_MOB,		// CMobLootManager
} LOOT_TYPE;

#define KICK_RESERVE_TIME			86400	// 1��
#define LAST_CONNECT_TIME_FOR_KICK	604800	// 7��
enum _eKickStatus
{
	GMKS_NORMAL		=	0,
	GMKS_RESERVE	=	1,
};

#if defined (GUILD_REMOTE_INVITE)
enum _eRemoteInviteType
{
	GRI_MASTER		=	0,		// �渶�� ���� ����
	GRI_JOINER		=	1,		// ������ ���� ��û
};
#endif // GUILD_REMOTE_INVITE

typedef enum  _eventAutomationType
{
	A_EVENT_SEPTEMBER		= 5,	// 9�� ���� ���� �̺�Ʈ
	A_EVENT_RAIN_DROP		= 20,	// ����� �Ϻ�Ʈ
	A_EVENT_COLLECT_BUG		= 22,	// ���� ä�� �̺�Ʈ
	A_EVENT_CHUSUK			= 25,	// �߼� �̺�Ʈ
	A_EVENT_PANDORA_BOX		= 26,	// �ǵ����� ���� (�ҷ��� 2006 �̺�Ʈ, �̱� ��� �̺�Ʈ)
	A_EVENT_VALENTINE_DAY	= 29,	// �߷�Ÿ�� ���� �̺�Ʈ
	A_EVENT_WHITE_DAY		= 31,	// ȭ��Ʈ ����
	A_EVENT_SONGKRAN		= 32,	// ��ũ�� �̺�Ʈ
	A_EVENT_EGGS_HUNT		= 33,	// ��Ȱ�� �̺�Ʈ
	A_EVENT_BEAR_DOLL		= 35,	// ������ �̺�Ʈ
	A_EVENT_INDEPENDENCE_DAY= 40,	// ���������
	A_EVENT_HALLOWEEN		= 49,	// �ҷ���
	A_EVENT_XMAS			= 50,	// ũ�������� �̺�Ʈ
	A_EVENT_GOLDEN_WEEK		= 62,	// ��� ��ũ �̺�Ʈ
	A_EVENT_MAGIC_CARD		= 74,	// ���� ī�� �̺�Ʈ // 2008 ���� �̺�Ʈ�� ����.
	A_EVENT_APRIL_FOOL		= 75,	// 4�� ������
	A_EVENT_WORLDCUP_TOTO	= 80,
	A_EVENT_WORLDCUP_TOTO_STATUS = 81,
	A_EVENT_WORLDCUP_TOTO_GIFT = 82,
	A_EVENT_ARTIFACT_HUNTER	= 84,
	A_EVENT_DOUBLE_GOLD = 85,
	A_EVENT_CUSTOM_ITEM = 86,
	A_EVENT_DOUBLE_AFFINITY = 87,
	A_EVENT_DOUBLE_EXP = 88,
	A_EVENT_DOUBLE_EXP_PET = 89,
	A_EVENT_MONSTER_COMBO  = 90,
	A_EVENT_DOUBLE_QUEST_EXP = 91,
	A_EVENT_DOUBLE_RVR = 92,
	A_EVENT_INCREASE_DAMAGE = 93,
	A_EVENT_CASH_INCREASE_WEEKEND = 94,
	A_EVENT_EASTERDROP = 95,
} EVENT_AUTOMATION_TYPE;

typedef enum _indexDataType
{
	INDEX_DATA_EXP_RATIO = 0,
	INDEX_DATA_SP_RATIO,
	INDEX_DATA_MAX,
} INDEX_DATA_TYPE;

#define PC_MIN_RUNSPEED	2.0f		// ĳ���� ���� ���ǵ�

#define SERVER_TRANS_ERROR_SUCCESS				(0 << 0)
#define	SERVER_TRANS_ERROR_EXIST_GUILD		(1 << 0)		//	��尡 �ִ� ���
#define	SERVER_TRANS_ERROR_EXIST_GUARDIAN	(1 << 1)		//	�İ����� �ִ� ���
#define	SERVER_TRANS_ERROR_30DAYS				(1 << 2)		//	������� 30���� �ȵȰ��
#define	SERVER_TRANS_ERROR_BLOCK_SERVER		(1 << 3)		//	������ ���� ������ ���
#define	SERVER_TRANS_ERROR_INVALID_SERVER	(1 << 4)
#define SERVER_TRANS_ERROR_DB_INSERT			(1 << 5)
#define SERVER_TRANS_ERROR_NOT_EXIST_ITEM	(1 << 6)		//  ����� ������ �̵�
#define SERVER_TRANS_ERROR_ROLLBACK_SUCCESS (1 << 7)		//  �ѹ� ����

#define GOLD_MAGNIFIER			1839	// Ȳ�� ������ ������ �ε���
#define MAX_VARIATION_COUNT		6

enum eITEM_GRADE
{
	eITEM_GRADE_NORMAL		= -1,	//�Ϲ� ���
	eITEM_GRADE_RARE_HERO,			//���� �������
	eITEM_GRADE_RARE_UNIQUE,		//���� Ư�����
	eITEM_GRADE_RARE_RARE,			//���� ���ѵ��
	eITEM_GRADE_RARE_MAGIC,			//���� ���޵��
	eITEM_GRADE_RARE_BASIC,			//���� �⺻���
	eITEM_GRADE_RARE_NOTOPEN,		//���� �̰��� ���
	eITEM_GRADE_ORIGIN,				//���� ���

	eITEM_GRADE_MAX
};

#define AFFINITY_INFOTAB_SUCCESS			(0 << 0)		//ģȭ�� ����â ����
#define AFFINITY_INFOTAB_ERROR_NOTEXIST		(1 << 0)		//����� ģȭ�� ����
#define AFFINITY_INFOTAB_NOT_REWARD			(1 << 1)		//���� ������ ����

#define JEWEL_COMPOSITE_POSITION_WEAPON		(1 << 0)
#define JEWEL_COMPOSITE_POSITION_HELMET		(1 << 1)
#define JEWEL_COMPOSITE_POSITION_ARMOR		(1 << 2)
#define JEWEL_COMPOSITE_POSITION_PANTS		(1 << 3)
#define JEWEL_COMPOSITE_POSITION_GLOVES		(1 << 4)
#define JEWEL_COMPOSITE_POSITION_SHOES		(1 << 5)
#define JEWEL_COMPOSITE_POSITION_SHIELD		(1 << 6)
#define JEWEL_COMPOSITE_POSITION_BACKWING	(1 << 7)
#define JEWEL_COMPOSITE_POSITION_ACCESSORY	(1 << 8)
#define JEWEL_COMPOSITE_POSITION_ALL		511

#define JEWEL_MAX_LEVEL						15		//���� �ִ� ����
#define JEWEL_POCKET_MAX_LEVEL				14		//���� �ָӴ� �ִ� ����
#ifdef CIRCLE_WINDOWS
typedef __int64 GoldType_t;
#else
typedef long long GoldType_t;
#endif

#define MAX_MONEY					999999999999LL		// max NAS a player can hold

#define MAX_PET_STASH_KEEP_COUNT	20		//�� â�� ���� �ִ� ����
#define PET_STASH_INCREASE_POINT	1		//�� â�������� ȸ�� ��ġ(�����, �漺��)
#define MAX_EFFECT_COUNT			5		//�� â�� ������ ���� ���� �� �ִ� ����Ʈ ���� ����

#define IMMUN_SKILL_MCT_TIME		120

#define NAS_ITEM_DB_INDEX			(19)

#define SYDICATE_QUEST_LIST_PERCENT 30		// ���� ����Ʈ ���� Ȯ��
#define SYNDICATE_OUT_NEEDNAS		10000000

namespace SYNDICATE
{
enum eSYNDICATE_TYPE
{
	eSYNDICATE_NONE		= 0	,		// ���Ҽ�
	eSYNDICATE_KAILUX		,		// ī�̷轺	: PC �� NPC ���� ����
	eSYNDICATE_DEALERMOON	,		// ����	: PC �� NPC ���� ����
	eSYNDICATE_FLOR			,		// �÷θ�	: NPC�θ� ����
	eSYNDICATE_MAX			,		// max value
};

enum eSYNDICATE_HISTORY_TYPE
{
	JOIN,			// ����
	REMOVE,			// Ż��
	DEGRADE,		// ����
	PROMOTION,		// �±�
	WIN,			// �¸�
	LOSE,			// ����
};

enum eSYNDICATE_GRADE
{
	SQUIRE		= 1	,		// �߽� ��� ī�̷轺
	KNIGHT			,		// ���� ���
	GENTOR			,		// ��� ���
	HONORISE		,		// ���ְ�
	BARONE			,		// ����
	VISCONTE		,		// ����
	CONTE			,		// ����
	MARQUISE		,		// ����
	DUKA			,		// ����
	PRINCIPE		,		// ����

	NEOPTYE		= 1	,		// �ʽ��� ����
	ZELATOR			,		// �߽���
	THEORICUS		,		// ������
	PHILOSOPHUS		,		// ��������
	ADEPTUS			,		// ���Ǹ� ������ ��
	MAGUS			,		// ������ ȹ���� ��
	IPSISSIMUS		,		// �������� ���� ��
};

#define		SQUIRE_POINT		104999
#define		KNIGHT_POINT		188999
#define		GENTOR_POINT		256199
#define		HONORISE_POINT		310799
#define		BARONE_POINT		352799
#define		VISCONTE_POINT		382199
#define		CONTE_POINT			403199
#define		MARQUISE_POINT		5000000

#define		NEOPTYE_POINT		146999
#define		ZELATOR_POINT		251999
#define		THEORICUS_POINT		335999
#define		PHILOSOPHUS_POINT	377999
#define		ADEPTUS_POINT		5000000

#if defined(_WIN64) || defined(WIN32)
inline int getSyndicateGrade(int syndicateType, __int64 point)
#else
inline int getSyndicateGrade(int syndicateType, long long point)
#endif
{
	switch(syndicateType)
	{
	case eSYNDICATE_KAILUX:
		{
			if (0 <= point && point <= SQUIRE_POINT)
				return SQUIRE;
			else if (SQUIRE_POINT < point && point <= KNIGHT_POINT)
				return KNIGHT;
			else if (KNIGHT_POINT < point && point <= GENTOR_POINT)
				return GENTOR;
			else if (GENTOR_POINT < point && point <= HONORISE_POINT)
				return HONORISE;
			else if (HONORISE_POINT < point && point <= BARONE_POINT)
				return BARONE;
			else if (BARONE_POINT < point && point <= VISCONTE_POINT)
				return VISCONTE;
			else if (VISCONTE_POINT < point && point <= CONTE_POINT)
				return CONTE;
			else if (CONTE_POINT < point && point <= MARQUISE_POINT)
				return MARQUISE;
			else
				return DUKA;
		}
		break;
	case eSYNDICATE_DEALERMOON:
		{
			if (0 <= point && point <= NEOPTYE_POINT)
				return NEOPTYE;
			else if (NEOPTYE_POINT < point && point <= ZELATOR_POINT)
				return ZELATOR;
			else if (ZELATOR_POINT < point && point <= THEORICUS_POINT)
				return THEORICUS;
			else if (THEORICUS_POINT < point && point <= PHILOSOPHUS_POINT)
				return PHILOSOPHUS;
			else if (PHILOSOPHUS_POINT < point && point <= ADEPTUS_POINT)
				return ADEPTUS;
			else
				return MAGUS;
		}
		break;
	default:
		return 0;
	}
}

#if defined(_WIN64) || defined(WIN32)
inline __int64	getSyndicateGradeMaxPoint(int syndicateType, int grade)
#else
inline long long getSyndicateGradeMaxPoint(int syndicateType, int grade)
#endif
{
	switch(syndicateType)
	{
	case eSYNDICATE_KAILUX:
		{
			if (grade == SQUIRE)
				return SQUIRE_POINT;
			else if (grade == KNIGHT)
				return KNIGHT_POINT;
			else if (grade == GENTOR)
				return GENTOR_POINT;
			else if (grade == HONORISE)
				return HONORISE_POINT;
			else if (grade == BARONE)
				return BARONE_POINT;
			else if (grade == VISCONTE)
				return VISCONTE_POINT;
			else if (grade == CONTE)
				return CONTE_POINT;
			else if (grade == MARQUISE)
				return MARQUISE_POINT;
			else
				return 0;
		}
		break;
	case eSYNDICATE_DEALERMOON:
		{
			if (grade == NEOPTYE)
				return NEOPTYE_POINT;
			else if (grade == ZELATOR)
				return ZELATOR_POINT;
			else if (grade == THEORICUS)
				return THEORICUS_POINT;
			else if (grade == PHILOSOPHUS)
				return PHILOSOPHUS_POINT;
			else if (grade == ADEPTUS)
				return ADEPTUS_POINT;
			else
				return 0;
		}
		break;
	default:
		return 0;
	}
}
}

#define PS_MAX_SHOPNAME				100		// ���� �̸� �ִ� ���� 100 ����Ʈ

enum
{
	TOGGLE_SKILL = 0,
	TOGGLE_ITEM,
};

enum
{
	ITEM_CASTLE_WAR_FLAG_DONE,
	ITEM_CASTLE_WAR_FLAG_ALL,
	ITEM_CASTLE_WAR_FLAG_MERAC,
	ITEM_CASTLE_WAR_FLAG_DRATAN,
};

#define CASTLE_DUNGEON_ENV_CHANGE_NEED_NAS_OWNER	500000
#define CASTLE_DUNGEON_ENV_CHANGE_NEED_NAS_NORMAL	1000000	


enum
{
	MOVE_TO_GUILDROOM = 0,
};

#define ARTIFACT_FIND_GPS_ITEM_INDEX	10954

enum MasterStone
{
	LOWER_MASTERSTONE = 6111,
	LOW_MASTERSTONE = 6112,
	NORMAL_MASTERSTONE = 6113,
	HIGH_MASTERSTONE = 6114,
	HIGHER_MASTERSTONE = 6115,
	MASTERSTONE = 6124,
	ARMOR_MASTERSTONE = 6120,

	LOWER_MASTERTONE2 = 7730,
	LOW_MASTERSTONE2 = 7731,
	NORMAL_MASTERSTONE2 = 7732,
	HIGH_MASTERSTONE2 = 7733,
	MASTERSTONE2 = 7734,
	MASTERSTONE3 = 7735,
	MASTERSTONE4 = 10970,
	MASTERSTONE5 = 10971,

	SPECIAL_MASTERSTONE30 = 40929
};

#define MASTERSTONE_SUCCESS_START_PROB		3300
#define MASTERSTONE_SUCCESS_NOCHANGE_PROB	3400
#define MASTERSTONE_SUCCESS_FAIL_PROB		3300

#define CUSTOM_TITLE_DUMMY_INDEX			199

#define CUSTOM_TITLE_ITEM_INDEX				11037

#define CASH_ITEM_10	12090
#define CASH_ITEM_15	12091
#define CASH_ITEM_50	11315
#define CASH_ITEM_100	11316
#define CASH_ITEM_1000  20593  //pwesty
#define CASH_ITEM_5000  20594  //pwesty
#define CASH_ITEM_10000 20595  //pwesty

#define MAGIC_SOUL_WITCH 1034
#define MAGIC_SOUL_WIZARD 1033
//pwesty shit
//#define MONSTER_COMBO_FIX
#define EXTENDER_ITEM_INDEX 11317
#define REFORGE_HAMMER_INDEX 11318
#define STAT_POINT_ITEM_INDEX 11319
#define STAT_POINT5_ITEM_INDEX 12329
#define PREMIUM_NAME_CHANGE_ITEM 11313
#define PREMIUM_GUILD_NAME_CHANGE_ITEM 11314
#define MAX_TITLE_SEAL 5
#define MAX_GOLD_POTION	70000000
#define MAX_HONOR_PTS 5000000
#define RVRPOTIONID 12565
#define		QUICK_PANEL
#define LUCKDRAW_RELOAD
#define REWARD_RELOAD
#define OPTION_RELOAD
#define QUEST_AUTO_EVENT_06062022
#define PRESTIGE_SYSTEM
#ifdef PRESTIGE_SYSTEM
#define MAX_PRESTIGE_LEVEL 10
#define PRESTIGE_PREMIUM_ITEM_INDEX 12368
//#define ENABLE_NPC_PRESTIGE
#endif
//#define ROYALRUMBLE_MOD
#define RANKING_SYSTEM_ASSASINPL


#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS

// Quest indices for dungeon instructions (sequential: base 1293, 5 parts per dungeon, 5 dungeons)
// Usage: PARTY_DG_QUEST_IDX(dungeon, part) where dungeon=0..4, part=0..4
#define PARTY_DG_QUEST_BASE_IDX			1293
#define PARTY_DG_PARTS_PER_DUNGEON		5
#define PARTY_DG_QUEST_IDX(dg, part)	(PARTY_DG_QUEST_BASE_IDX + (dg) * PARTY_DG_PARTS_PER_DUNGEON + (part))

// Required mob kill counts per dungeon phase
// KILL_COUNT  = kills to spawn first boss
// KILL_COUNT1 = kills to spawn second boss (DG1-4 only)
// KILL_COUNT2 = kills to spawn final boss
//                                          Boss1    Boss2    Final
#define PARTY_DG0_REQUIRED_MOB_KILL_COUNT	210
#define PARTY_DG0_REQUIRED_MOB_KILL_COUNT2	(PARTY_DG0_REQUIRED_MOB_KILL_COUNT + 70)

#define PARTY_DG1_REQUIRED_MOB_KILL_COUNT	70
#define PARTY_DG1_REQUIRED_MOB_KILL_COUNT1	60
#define PARTY_DG1_REQUIRED_MOB_KILL_COUNT2	(PARTY_DG1_REQUIRED_MOB_KILL_COUNT + PARTY_DG1_REQUIRED_MOB_KILL_COUNT1 + 41)

#define PARTY_DG2_REQUIRED_MOB_KILL_COUNT	105
#define PARTY_DG2_REQUIRED_MOB_KILL_COUNT1	70
#define PARTY_DG2_REQUIRED_MOB_KILL_COUNT2	(PARTY_DG2_REQUIRED_MOB_KILL_COUNT + PARTY_DG2_REQUIRED_MOB_KILL_COUNT1 + 55)

#define PARTY_DG3_REQUIRED_MOB_KILL_COUNT	60
#define PARTY_DG3_REQUIRED_MOB_KILL_COUNT1	120
#define PARTY_DG3_REQUIRED_MOB_KILL_COUNT2	(PARTY_DG3_REQUIRED_MOB_KILL_COUNT + PARTY_DG3_REQUIRED_MOB_KILL_COUNT1 + 40)

#define PARTY_DG4_REQUIRED_MOB_KILL_COUNT	105
#define PARTY_DG4_REQUIRED_MOB_KILL_COUNT1	110
#define PARTY_DG4_REQUIRED_MOB_KILL_COUNT2	(PARTY_DG4_REQUIRED_MOB_KILL_COUNT + PARTY_DG4_REQUIRED_MOB_KILL_COUNT1 + 90)

#endif


#endif // __GAME_Config_H__ 0
