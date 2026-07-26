#ifndef SE_INCL_NETWORK_H
#define SE_INCL_NETWORK_H
#ifdef PRAGMA_ONCE
	#pragma once
#endif

#include <Engine/Base/Stream.h>
#include <Engine/World/World.h>
#include <Engine/Templates/StaticArray.h>
#include <Engine/GlobalDefinition.h>
#include <Engine/Network/ChatMsgBuffer.h>
#include <Engine/Network/MultiTarget.h>
#include <Engine/Network/MessageDispatcher.h>
#include <Engine/Network/MessageDefine.h>

// EDIT : BS : 070413 : �ű� ��Ŷ ��ȣȭ
// EDIT : BS : ��Ŷ ��ȣȭ
#ifdef CRYPT_NET_MSG
#include <LCCrypt.h>
#else
#include <Engine/Network/CryptNetMsg.h>
#endif

// 110802 : ��Ŷ 2�� ��ȣȭ
#ifdef	CRYPT_NET_MSG_LEVEL2
#include <Engine/Network/CryptNetMsg.h>
#endif

// ���� ���� ����(status, appear )
#define WCJF_NONE   0  // ������
#define WCJF_OWNER   1  // ���� ���
#define WCJF_DEFENSE_GUILD 2  // ���� ���
#define WCJF_DEFENSE_CHAR 3  // ������ �뺴
#define WCJF_ATTACK_GUILD 4  // ���� ���
#define WCJF_ATTACK_CHAR 5  // ������ �뺴


#include <Engine/Entities/StatusEffect.h>
#include <Engine/Entities/ItemEffect.h>
#include <Engine/Entities/CharacterAnimation.h>
//0603 kwon 
#include <Engine/Entities/Items.h>
#include <Engine/Entities/Craft.h> //Craft system
#include <Engine/Entities/TargetInfo.h>
#include <Engine/Entities/SmcParser.h> // eons 071005 : SmcParser Ŭ����

// [6/17/2009 rumist] include definition stat.
#include <Engine/LocalDefine.h> 
#include <Engine/Entities/AffinityData.h>
#include <Engine/Entities/Lacarette.h>
#include <Engine/Interface/UIGuildMark.h>
#include <Common/Packet/ptype_inventory.h>
#include <Engine/Contents/function/TitleData.h>
#include "Interface/UIEditBox.h"


#ifndef CNM_INIT_KEY
#define CNM_INIT_KEY		((unsigned int)(1852535664))
#endif


#define NET_MAXGAMECOMPUTERS SERVER_CLIENTS		// max overall computers in game
#define NET_MAXGAMEPLAYERS			1			// max overall players in game
#define NET_MAXLOCALPLAYERS			1			// max players on a single machine

#define NET_WAITMESSAGE_DELAY		50			// wait time between receive message attempts

#define NET_MAXSESSIONPROPERTIES	2048		// size of buffer for custom use by CGame and entities

// demo synchronization constants
#define DEMOSYNC_REALTIME			(0.0f)
#define DEMOSYNC_STOP				(-1.0f)

//[ttos_2009_1_20]: ä�� ���� flag
#define CHAT_FLAG_NO_SAY  (1 << 0)  // �Ϲ� ä�� ����
#define CHAT_FLAG_NO_PARTY  (1 << 1)  // ��Ƽ ä�� ����
#define CHAT_FLAG_NO_GUILD  (1 << 2)  // ��� ä�� ����
#define CHAT_FLAG_NO_TRADE  (1 << 3)  // �Ÿ� ä�� ����
#define CHAT_FLAG_NO_WHISPER (1 << 4)  // �ӼӸ� ����
#define CHAT_FLAG_NO_SHOUT  (1 << 5)  // ��ġ�� ����

#define PK_SYS_CHAO_1	(1 << 0)	//���� ���۳�
#define PK_SYS_CHAO_2	(1 << 1)	//�� �� ���۳�
#define PK_SYS_CHAO_3	(1 << 2)	//���� �ȳ��۳�
#define PK_SYS_CHAO_4	(1 << 3)	//���� �����ѳ�
#define PK_SYS_CHAO_5	(1 << 4)	//�� �� ���ѳ�
#define PK_SYS_CHAO_6	(1 << 5)	//���� ���ѳ�
 
extern ENGINE_API INDEX net_bLocalPrediction;

enum NetGraphEntryType {
	NGET_ACTION = 0,
	NGET_NONACTION,
	NGET_MISSING,
	NGET_SKIPPEDACTION,
	NGET_REPLICATEDACTION,
};

enum CurEnterType { // ���� ���� ���� Ÿ��(���� �ǰ� �ִ� ���?)
	CURRENT_ENTER_NORMAL,
	CURRENT_ENTER_PARTYCUBE,
	CURRENT_ENTER_GUILDCUBE,
};

struct NetGraphEntry {
	enum NetGraphEntryType nge_ngetType;	// type of packet/event
	FLOAT nge_fLatency;						// latency in seconds
	void Clear(void);
};

struct JewelInfo
{
	int Jewel_idx;
	int Jewel_composGrade;
};

typedef		std::vector<JewelInfo>		_vecJewelInfo;
//added by sam 11/02/01 [SAM] �ѹ� 
typedef std::vector<INDEX> VEC_ONESUIT_OPTION_TYPE;
typedef VEC_ONESUIT_OPTION_TYPE::iterator VEC_ONESUIT_OPTION_TYPE_IT;

typedef std::vector<INDEX> VEC_ONESUIT_OPTION_LEVEL;
typedef VEC_ONESUIT_OPTION_LEVEL::iterator VEC_ONESUIT_OPTION_LEVEL_IT;

#define NONCE_SIZE 8

struct CNeedItems;

/*
 * Network session description.
 */
class ENGINE_API CNetworkSession {
public:
	CListNode ns_lnNode;				// for linking in list of available sessions
	CTString ns_strAddress;				// session address

	CTString ns_strSession;				// session name
	CTString ns_strWorld;				// world name
	TIME     ns_tmPing;					// current players
	INDEX    ns_ctPlayers;				// current players
	INDEX    ns_ctMaxPlayers;			// max number of players
	CTString ns_strGameType;			// game type
	CTString ns_strMod;					// active mod
	CTString ns_strVer;					// version
	TIME     ns_tmLastSeen;				// time of the last rewponse to enumeration
	ULONG    ns_ulAddress;				// server's address
	UWORD    ns_uwPort;					// server's port
	
public:
	void Copy(const CNetworkSession &nsOriginal);

	/* Default constructor. */
	CNetworkSession(void);
	/* Construct a session for connecting to certain server. */
	CNetworkSession(const CTString &strAddress);
};

/*
 * Game, used for general game initialization/manipulation
 */
class ENGINE_API CNetworkLibrary : public CMessageDispatcher 
{	
public:
	// EDIT : BS : BEGIN
	DWORD m_tickSendMoveList;
	// EDIT : BS : END
	BOOL ga_IsServer;								// set if this is a server computer
	CServer &ga_srvServer;							// server (active only if this is server computer)

	CTCriticalSection ga_csNetwork;					// critical section for access to network data

	CSessionState &ga_sesSessionState;				// local session state
	CStaticArray<CPlayerSource> ga_aplsPlayers;		// local players
	CTString ga_strSessionName;						// name of current session
	CTString ga_strServerAddress;					// address of game server (if joined)
	CTFileName ga_fnmWorld;							// filename of current world
	CTString ga_strGameType;						// game type (cooperative, scorematch, deathmatch)
	CTString ga_strMod;								// name of the mod
	CTString ga_strVer;								// version

	UBYTE *ga_pubDefaultState;						// default state for connecting (server only)
	SLONG ga_slDefaultStateSize;
	UBYTE ga_aubDefaultProperties[NET_MAXSESSIONPROPERTIES];
	UBYTE *ga_pubCRCList;							// list of files for CRC checking (server only)
	SLONG ga_slCRCList;
	ULONG ga_ulCRC;									// CRC of CRCs of all files in the list

	BOOL ga_bLocalPause;							// local pause for single player/demo
	BOOL ga_bDemoRec;								// set if currently recording a demo
	CTFileStream ga_strmDemoRec;					// currently recorded demo file
	BOOL ga_bDemoPlay;								// set if currently playing a demo
	BOOL ga_bDemoPlayFinished;						// set if currently playing demo has finished
	CTFileStream ga_strmDemoPlay;					// currently played demo file
	CTimerValue ga_tvDemoTimerLastTime;				// real time timer for demo synchronization
	CTimerValue ga_tvGameFinished;					// time when the game was finished
	TIME ga_tmNextDemoTick;							// time of the next tick to be read from stream for demo play

	CTFileName ga_fnmNextLevel;						// world for next level
	BOOL  ga_bNextRemember;							// remember old levels when changing to new one
	INDEX ga_iNextLevelUserData;					// user data for next level
	UBYTE ga_ubNumLevelChanges;						// how many times has levelchange occured

	CListHead ga_lhEnumeratedSessions;				// list of sessions found after last enumeration was triggered
	FLOAT ga_fEnumerationProgress;					// enumeration progress percentage (0-1)
	CTString ga_strEnumerationStatus;				// description of current operation
	BOOL ga_bEnumerationChange;						// this is raised if something was changed in the list
	BOOL ga_bGuildWar;								// ��� ���� ���ΰ�?


	CTString ga_strRequiredMod;						// set if connection failed due to a different mod running on the server

	CTimerValue ga_tvLastMainLoop;					// when was the main loop last run - for tick sync
	BOOL  ga_bFirstMainLoop;						// has the main loop been run before

	// buffer for custom use by CGame and entities
	UBYTE ga_aubProperties[NET_MAXSESSIONPROPERTIES];

	BOOL IsServer(void) { return ga_IsServer;};

	// make actions packet for local players and send to server
	void SendActionsToServer(void);

	/* Loop executed in timer interrupt, every game tick. */
	void TimerLoop(void);

	// really do the level change
	void ChangeLevel_internal(void);
	void ChangeLevel_client_internal_t(void);

	// save current version of engine
	void WriteVersion_t(CTStream &strm);
	// load version of engine saved in file and check against current
	void CheckVersion_t(CTStream &strm, BOOL bAllowReinit, BOOL &bNeedsReinit);

	// add a value to the netgraph
	void AddNetGraphValue(enum NetGraphEntryType nget, FLOAT fLatency);

	// add a value to the bandwidth graph
	void AddBandwidthGraphValue(ULONG ulBandwidth);

	// call this while game is not running - to update server enumeration lists
	void GameInactive(void);

	// automatically adjust network settings
	void AutoAdjustSettings(void);

	// initialize gathering of file CRCs to CRC table
	void InitCRCGather(void);
	// finish gathering of file CRCs to CRC table (call for server only!)
	void FinishCRCGather(void);
	
public:
	CWorld ga_World;										// local copy of world
	FLOAT ga_fDemoTimer;									// timer for demo playback (in seconds)
	FLOAT ga_fDemoRealTimeFactor;							// slow/fast playback factor (for DEMOSYNC_REALTIME only)
	FLOAT ga_fGameRealTimeFactor;							// game time accelerator
	FLOAT ga_fDemoSyncRate;									// demo sync speed in FPS (or realtime/stop)
	CStaticArray<struct NetGraphEntry> ga_angeNetGraph;		// array of netgraph entries
	CStaticArray<ULONG> ga_aulBandwidthGraph;				// array of bandwidth entries

	//0603 kwon 
	CItems MySlotItem[INVEN_SLOT_TAB][ITEM_COUNT_IN_INVENTORY_NORMAL];
	CItems MyWearItem[WEAR_TOTAL];
	CItems MyWearCostItem[WEAR_COSTUME_TOTAL];
	bool m_bInvisibleHelmet;
		
	//int		MyCurrentSkill[50];
	//int		MySkillNum;
	int						wo_iNumOfSkill;			// yjpark
	int						wo_iNumOfJewelGradeData;

	CStaticArray<JewelComosInfo>	wo_aJewelData;		// ���� �Ҹ� ���� �� ������ ����
	CStaticArray<CMakeItemData>		wo_aMakeItemData;	// ���� ������ ������
	CSmcParserList					wo_aItemSmcInfo;	// ������ Smc ����
	CStaticArray<CAffinityData>		wo_aAffinityData;
	CStaticArray<CLacarette>		wo_aLacaretteData;	// ��ī��
	
	std::map<int, _vecJewelInfo> wo_mapJewelGradeInfo;
	std::map<int, _vecJewelInfo> wo_mapChaosJewelGradeInfo;
	
	int						wo_iNumOfAffinity;
	int						wo_dwEnemyCount;		// ���ʹ��� ����.
	int						wo_dwKilledEnemyCount;
	int						wo_iNomOfMakeItemData;	// ���� ������ ������
	struct CHECKPOINT{								// �ش� üũ ����Ʈ ���� ����
		int m_iQuestIndex;
		int m_iMaxCheckFlag;				
		int m_iCheckFlag;
	} ;
	CHECKPOINT wo_stCheckPoint;

	//0917
	CTString	m_strUserID;
	CTString	m_strUserPW;
	CTString	m_strUserCID; // ������ ������Ʈ �ĺ���	
	int			m_iServerGroup;
	int			m_iServerCh;
	int			m_iServerType;
	int			m_iNetworkResponse[MSG_END];			// ��Ʈ��ũ ���� �÷���
	int			m_iNetworkResponseEx[MSG_EX_END];
	

	BOOL	m_bIsPvp;
	void	SetPvpMode();
	#ifdef ARENA_TIME_SYSTEM
	void	SendPvPBuff();
	#endif
	LONG	m_lLoadingZone;

	BOOL	IsRvrZone()	{ return m_bIsRvr;	}	// ���� RVR��(42)�� �ֳ�.
	void	SetRvrZone(BOOL bRvr)	{ m_bIsRvr = bRvr;	}

	// interface
	/* Default constructor. */
	CNetworkLibrary(void);
	~CNetworkLibrary(void);
	DECLARE_NOCOPYING(CNetworkLibrary);

	/* Initialize game management. */
	void Init(const CTString &strGameID);
	/* Start a peer-to-peer game session. */
	void StartPeerToPeer_t(const CTString &strSessionName,
		const CTFileName &fnmWorld, ULONG ulSpawnFlags, 
		INDEX ctMaxPlayers, BOOL bWaitAllPlayers,
		void *pvSessionProperties); // throw char *

	/* Start numeration of existing sessions. */
	void EnumSessionsStart(BOOL bInternet);
	/* Continue numeration of existing sessions. */
	void EnumSessionsContinue();
	/* Stop numeration of existing sessions. */
	void EnumSessionsStop();

	/* Join a running multi-player game. */
	void JoinSession_t(const CNetworkSession &nsSesssion, INDEX ctLocalPlayers); // throw char *
	/* Start playing a demo. */
	//void StartDemoPlay_t(const CTFileName &fnDemo); // throw char *
	/* Test if currently playing a demo. */
	BOOL IsPlayingDemo(void);
	/* Test if currently recording a demo. */
	//BOOL IsRecordingDemo(void);
	/* Test if currently playing demo has finished. */
	//BOOL IsDemoPlayFinished(void);
	/* Stop currently running game. */
	void StopGame(void);


	// pause/unpause game
	void TogglePause(void);
	// test if game is paused
	BOOL IsPaused(void);
	// test if game is waiting for more players to connect
	BOOL IsWaitingForPlayers(void);
	// test if game is waiting for server
	BOOL IsWaitingForServer(void);
	// mark that the game has finished -- called from AI
	void SetGameFinished(void);
	BOOL IsGameFinished(void);
	// manipulation with realtime factor for slower/faster time -- called from AI
	void SetRealTimeFactor(FLOAT fSpeed);
	FLOAT GetRealTimeFactor(void);   
	// test if having connnection problems (not getting messages from server regulary)
	BOOL IsConnectionStable(void);
	// test if completely disconnected and why
	BOOL IsDisconnected(void);
	const CTString &WhyDisconnected(void);

	// set/get server side pause (for single player or demo only)
	void SetLocalPause(BOOL bPause);
	BOOL GetLocalPause(void);

	// get server/client name and address
	void GetHostName(CTString &strName, CTString &strAddress);

	// test if playing in network or locally
	BOOL IsNetworkEnabled(void);

	// initiate level change
	void ChangeLevel(const CTFileName &fnmNextLevel, BOOL bRemember, INDEX iUserData);

	/* Obtain file name of world that is currently loaded. */
	CTFileName &GetCurrentWorld(void) { return ga_fnmWorld;};

	/* Start recording a demo. */
	//void StartDemoRec_t(const CTFileName &fnDemo); // throw char *
	/* Stop recording a demo. */
	//void StopDemoRec(void);

	/* Read current game situation from a stream. */
	void Read_t(CTStream *pstr);   // throw char *
	/* Write current game situation into a stream. */
	void Write_t(CTStream *pstr);  // throw char *

	/* Save the game. */
	void Save_t(const CTFileName &fnmGame); // throw char *
	/* Load the game. */
	void Load_t(const CTFileName &fnmGame); // throw char *

	/* Save a debugging game. */
	void DebugSave(void);   // this doesn't throw anything

	/* Add a new player to game. */
	CPlayerSource *AddPlayer_t(CPlayerCharacter &pcCharacter);  // throw char *

	/* Loop executed in main application thread. */
	void MainLoop(void);

	/* Get count of local players. */
	INDEX GetLocalPlayerCount(void);
	/* Get player entity for a given local player. */
	CEntity *GetLocalPlayerEntity(CPlayerSource *ppls);
	/* Get player entity for a given player by name. */
	CEntity *GetPlayerEntityByName(const CTString &strName);

	/* Get number of entities with given name. */
	INDEX GetNumberOfEntitiesWithName(const CTString &strName);
	/* Get n-th entity with given name. */
	CEntity *GetEntityWithName(const CTString &strName, INDEX iEntityWithThatName);
	/* Get number of player entities with given name. */
	INDEX GetNumberOfPlayerEntitiesWithName(const CTString &strName);
	/* Get n-th player entity with given name. */
	CPlayerEntity *GetNthPlayerEntityWithName(const CTString &strName, INDEX iEntityWithThatName);
	/* Get n-th player entity. */
	CPlayerEntity *GetNthPlayerEntity(INDEX iEntity);
																			 
	/* Get n-th entity of given class. */
	CEntity *GetEntityOfClass(const CTString &strClass, INDEX iEntityOfThatClass);
	/* Test if a given player is local to this computer. */
	BOOL IsPlayerLocal(CEntity *pen);
	// get player source for a given player if it is local to this computer
	CPlayerSource *GetPlayerSource(CEntity *pen);

	// get game time in currently running game
	TIME GetGameTime(void);

	/* Get session properties for current game. */
	void *GetSessionProperties(void);

	/* Send chat message from some players to some other players. */
	void SendChat(ULONG ulFrom, ULONG ulTo, const CTString &strMessage);
	void SendChatMessage(int index, CTString& strRecvName, CTString& strMessage, std::list<ItemChat> list, SLONG nExpChatType = -1);//0616 kwon
//0105
	void SendMessagetoServer(char *msg);
	//BOOL IsTcpServer;					// by seo-40225 �θ�Ŭ���� CMessageDispatcher�� ���� ��ġ �ű�.
	BOOL m_bReadyStart; //0311 kwon serverloop()�� ������ �غ� �Ǿ��°�.
	BOOL IsReadyStart(){return m_bReadyStart;}
	void SetReadyStart(BOOL bstart){ m_bReadyStart = bstart;}
	BOOL m_bSingleMode;

	CEntity* GetEntityByTypeIndex(SBYTE sbType, SLONG slIndex);
	
	int ReturnCCC(int iSCC);
	
	//-----------------------------------------
	// Pet ���� ����ü.
	struct sPetInfo
	{
		sPetInfo()
		{
			lIndex			= -1;
			sbPetTypeGrade	= -1;
			lLevel			= -1;
			llExp			= -1;
			llNeedExp		= -1;
			lHP				= -1;
			lMaxHP			= 0;
			lAbility		= 0;
			lHungry			= -1;
			lMaxHungry		= -1;
			lSympathy		= -1;
			lMaxSympathy	= -1;
			fX				= 0.0f;
			fZ				= 0.0f;
			fH				= 0.0f;
			fR				= 0.0f;			
			sbMapAttribute	= 0;
			lRemainRebirth	= 0;
			strNameCard		= CTString("");
		};

		LONG		lIndex;
		SBYTE		sbPetTypeGrade;
		LONG		lLevel;
		__int64		llExp;
		__int64		llNeedExp;
		LONG		lHP;
		LONG		lMaxHP;
		LONG		lHungry;
		LONG		lMaxHungry;
		LONG		lAbility;
		LONG		lSympathy;
		LONG		lMaxSympathy;
		FLOAT		fX;
		FLOAT		fZ;
		FLOAT		fH;
		FLOAT		fR;		
		UWORD		sbMapAttribute;
		LONG		lRemainRebirth;
		CTString	strNameCard;
	};

	// Function Object
	struct FindPet
	{
		SLONG lIndex;
		FindPet(sPetInfo& info) : lIndex(info.lIndex) {};
		bool operator() (const sPetInfo& info)
		{
			if(info.lIndex == lIndex)
			{
				return true;
			}
			else
				return false;
		}
	};

	// FIXME : ��Ʈ��ũ�� �ִ°� ��...-_-;;;
	struct sMoveInfo
	{
		sMoveInfo()
		{
			iIndex	= -1;
			fX		= 0.0f;
			fZ		= 0.0f;
			fH		= 0.0f;
			fAngle	= 0.0f;
		};

		INDEX	iIndex;
		FLOAT	fX;
		FLOAT	fZ;
		FLOAT	fH;
		FLOAT	fAngle;
	};

	// FIXME : ��Ʈ��ũ�� �ִ°� ��...-_-;;;
	struct sAttackInfo
	{
		sAttackInfo()
		{
			iAttackIndex	= -1;
			iTargetIndex	= -1;
			ubAttackType	= 0;
			ubTargetType	= 0;
		};

		UBYTE	ubAttackType;
		UBYTE	ubTargetType;
		INDEX	iAttackIndex;
		INDEX	iTargetIndex;
	};

	// FIXME : ��Ʈ��ũ�� �ִ°� ��...-_-;;;
	struct sRegenInfo
	{
		sRegenInfo()
		{
			iIndex		= -1;
			iMobType	= -1;
			fX			= 0.0f;
			fY			= 0.0f;
			fZ			= 0.0f;
			fAngle		= 0.0f;
			iYLayer		= 0;
			iEntityID	= -1;
		};
		INDEX	iIndex;
		INDEX	iMobType;
		FLOAT	fX;
		FLOAT	fY;
		FLOAT	fZ;
		FLOAT	fAngle;
		INDEX	iYLayer;
		INDEX	iEntityID;
	};

	std::vector<sPetInfo>		m_vectorPetList;
	std::vector<sMoveInfo>		m_vectorMoveList;
	std::vector<sAttackInfo>	m_vectorAttackNPCList;		// NPC�� �����ϴ� ����Ʈ.
	std::vector<sAttackInfo>	m_vectorAttackPCList;		// PC�� �����ϴ� ����Ʈ.
	std::vector<sAttackInfo>	m_vectorAttackSummonList;	// ��ȯ���� �����ϴ� ����Ʈ.
	std::vector<sAttackInfo>	m_vectorAttackPetList;	// ��ȯ���� �����ϴ� ����Ʈ.
	std::vector<sRegenInfo>		m_vectorRegenList;
	std::vector<int>			m_vectorLegitList; // ������� ���� ���
	std::list<int>				m_listAffinityRewardNPCList;	// [100322: selo] ģȭ�� ���� NPC ����Ʈ
	// FIXME : ��Ʈ��ũ�� �ִ°� ��...-_-;;;
	//0527 kwon struct �߰�.
	struct MyChaInfo 
	{
		CTString name;
		SLONG	 index;
		UBYTE	 job;
		SBYTE	 job2;					// ������...
		ULONG	 zoneNo;
		ULONG	 areaNo;
		ULONG	 LocalNo;				// ���� ���� ( show signboard )
		FLOAT	 x;
		FLOAT	 h;
		FLOAT	 z;
		FLOAT	 r; //����
		SBYTE	 yLayer;
		SLONG    userIndex;
		SBYTE	 hairStyle, faceStyle;

		SLONG level, hp, mp, str, dex, intel, con, opt_str, opt_dex, maxMP, maxHP, opt_intel, opt_con;
		SLONG weight, maxweight;
		FLOAT walkspeed, runspeed,attackrange;
		SBYTE attackspeed;
		SQUAD sp, money, curExp, needExp;
		SLONG StatPoint;//1013
		SLONG StatPointAddition;
		SBYTE sbJoinFlagMerac;			// ���� ������ ��.
		SBYTE sbJoinFlagDratan;			// WSS_DRATAN_SIEGEWARFARE 070720
		UWORD sbAttributePos;			// �Ӽ��� ��.
		SBYTE sbMountPet;
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
		SLONG cloud_partydgdata[5];
		SLONG cloud_partydgtitle[5];
#endif
		FLOAT camera_angle;

		SBYTE pktitle;
		SLONG pkpenalty, pkcount;
		SBYTE pk_mode;
		SLONG fame;						// ����.

#ifdef QUICK_PANEL
		SLONG cloud_QuickPanelBtnType[25];
		SLONG cloud_QuickPanelBtnIdx[25];
#endif

		BOOL  bOtherZone;
		BOOL  bConsensus;							// WSS_DRATAN_SEIGEWARFARE 2007/08/01 ������
		std::map<int,int> mQuarter;					// WSS_DRATAN_SEIGEWARFARE 2007/08/09 ��Ȱ����
		std::map<int,CTString> mQuarterName;		// WSS_DRATAN_SEIGEWARFARE 2007/08/09 ��Ȱ���� �̸�(���� ����̸� �߰�)

		SBYTE			sbShopType;		
		LONG			lGuildIndex;		// �ӽ�	����� �ε���
		LONG			lGuildLevel;		// �ӽ� ����� ����
		LONG			lGuildPosition;		// �ӽ� ��忡���� ĳ������ ����
		CTString		strGuildName;		// ����.
		int				iGuildMasterKickStatus;		// ��� �߹� ����		0 : ���� �̻� ����, 1 : �߹� ��û ���� ����		[trylord 11/12/28]
		UBYTE			ubGuildNameColor;	//[071123: Su-won] DRATAN_SIEGE_DUNGEON
		SBYTE			sbGuildRank;
		BOOL			bExtension;			// �ι�° Ÿ���� ���⸦ �� ���...

		INDEX			iPetType;			// �ֿϵ��� ����...(?)
		INDEX			iPetAge;			// �ֿϵ��� ����...(?)
		BOOL			bPetRide;			// �ֿϵ����� Ÿ�� �ֳ�?
		BOOL			bWildPetRide;		// ������ �� ����Ʈ
		
		int 			nEvocationIndex;		// ���� Ÿ��.

		int                autopickup;  //auto system
        int                autoigni;
        int                autosell;

		LONG			lTeacherIndex;		// �� ������ �ε���
		CTString		strTeacherName;		// �� ������ �̸�.

		ChatMsgBuffer	ChatMsg;		// yjpark
		ChatMsgBuffer	ShopMsg;		// yjpark
		FLOAT			fWaterHeight;	// yjpark - �ӽ÷� �߰��� ����. ������ ��ġ�� ������ �������� ���� ����..

		SLONG	magicspeed;
		SLONG	skillSpeed;
		CStatusEffect statusEffect;
		CItemEffect itemEffect;
		SBYTE	sbItemEffectOption;
//0707
		SLONG secretkey;
		SLONG lLocation;// Date : 2006-04-27(���� 2:33:10), By eons( NetCafe )

		SLONG lWarpZone;
		SLONG lWarpPos;


// �Ӽ� �ý��� [1/17/2013 Ranma]
		UBYTE attrdef, attratt;
		UBYTE attrdefLv, attrattLv;
		// ����ü�� ������ �����ǵ���...
		MyChaInfo()
		{
			autopickup = 0;
			autoigni = 0;
			autosell = 0;
			

			nEvocationIndex = 0;
			LocalNo = 0;
			sbJoinFlagDratan = WCJF_NONE;			// WSS_DRATAN_SIEGEWARFARE 070720

			slLabel = -1;
			slSubJob = 0;							// [2010/08/25 : Sora] ADD_SUBJOB
			runspeed = 1.0f;

			iGuildMasterKickStatus = 0;
// �Ӽ� �ý��� [1/17/2013 Ranma]
			attrdef = 0;
			attratt = 0;

			zoneNo = 0;
			areaNo = 0;
			
			x = 0.0f;
			h = 0.0f;
			z = 0.0f;
			yLayer = 0;
#ifdef REZABOT
			char_botting = 0;
#endif
			bExtension = FALSE;
			useTotem = false;
		};
		
		// WSS_VISIBLE 070511
		// ��� ��� ĳ��Ʈ ������ ó��
		// visible ���ɾ� ���� ���õ�
		COLOR m_ModelColor;

		// 080623 ��ī ���ڴ� ����
		SBYTE			sbPresscorps;
		SBYTE			sbSoulCount;

		SLONG			slLabel;	  // [sora] ��� ǥ��
//#ifdef REZABOT
		char char_botting; 
//#endif
		// 080901 UI����
		SLONG			baseHP, baseMP, addedAttack, addedMagic, addedDefense, addedResist;
		SLONG			dodgeRate, baseDodgeRate, magicDodgeRate, baseMagicDodgeRate, hitRate, baseHitRate, magicHitRate, baseMagicHitRate;
		SLONG			critical, baseCritical, deadly, baseDeadly;
		FLOAT			baseRunSpeed;
		SBYTE           baseAttackSpeed;
		CTString		guildPosName;
		ULONG			ChatFlag, ulPlayerState;
		CurEnterType	EntranceType; // ������ ���� �� ���� ���� or ���� ��� ����(Ư���� ���·� ���� �������� ������ ���� �κ�)(��:�ͽ�Ʈ�� ť��)
		
		INDEX			iNickType;	  // ȣĪ Ÿ�� ( 0 : ȣĪ ����)
		SQUAD			iGP;		  // ��� ����Ʈ
		
		INDEX			ep, maxEP;			  // [7/15/2010 kiny8216] Monseter Energy Point

		INDEX 			a_wins;
		INDEX 			a_loses;
		INDEX			a_honor;

		INDEX 			reborn;
		INDEX			colorName;

		INDEX 			opResistStone;
		INDEX 			opResistSturn;
		INDEX 			opResistSilent;
		INDEX 			opabsorbPVPDamageRate;
		INDEX 			opDecreaseSkillMP;

		INDEX			iStudentGiveUpCnt;

		BOOL			bOneSuit;		  // �ѹ� �ǻ��� �԰� �ִ��� �Ǵ�.
		INDEX			iOneSuitDBIndex;
		INDEX			iOneSuitUniIndex;
		CTString GetPlayerName(void) { return name; }

		SLONG			slSubJob;		// [2010/08/25 : Sora] ADD_SUBJOB
		
		ULONG			pkSysRewardFlag;
		BOOL			bpkSysRewardLate;
		INDEX			iSyndicateType;	// ���� Ÿ�� : 0 ���Ҽ�, 1 ī�̷轺, 2 ����, 3 �÷η�
		INDEX			iSyndicateGrade;
		LONGLONG		lSyndicateAccPoint;
		INDEX			iHitEffectType;
		bool			useTotem;

		stCustomTitleStatForPc stCustomTitle;
		// ����/���� ���� �÷���
		typedef enum	_eMORPHSTATUS
		{
			eMORPH_END		= 0,				// ��ȭ ����
			eMORPH_EVOCATION_BEGIN,				// ���� ��ȭ �غ� (��Ʈ��ũ ��û)
			eMORPH_EVOCATION_CONVERTING,		// ���� ��
			eMORPH_EVOCATION,					// ���� �Ϸ� ����
			eMORPH_TRANSFORMATION_BEGIN,		// ���� ��ȭ �غ� (��Ʈ��ũ ��û)
			eMORPH_TRANSFORMATION_CONVERTING,	// ���� ��
			eMORPH_TRANSFORMATION,				// ���� �Ϸ� ����
		}eMORPHSTATUS;
		eMORPHSTATUS	eMorphStatus;
#ifndef	ISEVOCATION
#define	ISEVOCATION(t)		(t >= CNetworkLibrary::MyChaInfo::eMORPH_EVOCATION_BEGIN && t <= CNetworkLibrary::MyChaInfo::eMORPH_EVOCATION ? 1 : 0)
#endif
#ifndef	ISTRANSFORMATION
#define	ISTRANSFORMATION(t)	(t >= CNetworkLibrary::MyChaInfo::eMORPH_TRANSFORMATION_BEGIN && t <= CNetworkLibrary::MyChaInfo::eMORPH_TRANSFORMATION ? 1 : 0)
#endif

	};
	
	MyChaInfo			MyCharacterInfo;


	struct _AffinityInfo
	{
		struct _AffinityPoint
		{
			SLONG	current;
			SLONG	max;
			_AffinityPoint()
			{
				current = 0;
				max = 0;
			};
		};
		typedef std::map<int, _AffinityPoint> mapAffinity;
		typedef	std::map<int, _AffinityPoint>::iterator mapAffIter;
		SLONG			point;
		SLONG			count;
		std::map< int, _AffinityPoint>		mapAffinityList;

		_AffinityInfo()
		{
			point = 0;
			count = 0;
			//vecAffinityList.clear();
			mapAffinityList.clear();
		};
		~_AffinityInfo()
		{
			mapAffinityList.clear();
		}
	};

	_AffinityInfo		AffinityInfo;
	
	struct _MonsterMercenaryInfo // [2010/10/20 : Sora] ���� �뺴 ī��
	{
		INDEX	index;
		SLONG	grade;
		SLONG	attack;
		SLONG	defence;
		SLONG	magicAttack;
		SLONG	magicDefence;
		SLONG	hp;
		SLONG	mp;
		SLONG	maxHp;
		SLONG	maxMp;

		_MonsterMercenaryInfo()
		{
			Init();
		}

		void Init()
		{
			index = 0;
			grade	= 0;
			attack	= 0;
			defence	= 0;
			magicAttack	= 0;
			magicDefence = 0;
			hp = 0;
			mp = 0;
			maxHp = 0;
			maxMp = 0;
		}
	};

	_MonsterMercenaryInfo MonsterMercenaryInfo;

	// EDIT : BS : 070413 : �ű� ��Ŷ ��ȣȭ		
	// EDIT : BS : ��Ŷ ��ȣȭ
#ifdef CRYPT_NET_MSG
	CNM_KEY_TYPE cnmKey;
#ifndef CRYPT_NET_MSG_MANUAL
	CNM_KEY_TYPE cnmKeyServer;
#endif // #ifndef CRYPT_NET_MSG_MANUAL
#else
	ULONG cnmKey;
#endif // #ifdef CRYPT_NET_MSG

//helper���� ��Ŷ ��ȣȭ Ű ����
#ifdef CRYPT_NET_MSG
	CNM_KEY_TYPE subHelperKey;
#ifndef CRYPT_NET_MSG_MANUAL
	CNM_KEY_TYPE subHelperKeyServer;
#endif // #ifndef CRYPT_NET_MSG_MANUAL
#else
	ULONG subHelperKey;
#endif // #ifdef CRYPT_NET_MSG

	// ���� Ÿ�� ����� ����
	SLONG slServerTimeGap;
	SLONG slServerTime;
	struct tm tServer;

	// ĳ���� ����â���� �̵�
	BOOL bMoveCharacterSelectUI;

/*
	//0729 kwon ��ų �ִϸ��̼� ���̵�.
	struct SkillAnimationID
	{
		BOOL bIsBuff;
		INDEX idPlayer_Anim_Skill[3];
	};
	
	SkillAnimationID	_SkillAnimID[300];//�켱 ��ų 300���� ����.
*/
	void SendLoginMessage(CTString& strID, CTString& strPW, ULONG ulVersion);
	

	void SendSecurityMessage(CTString& strSecurity);							//070901_ttos: ����ī�� UI
	void SendDeleteCharacter(ULONG ulIndex, BYTE del = FALSE);
	void SendDeleteCharacter(ULONG ulIndex, CTString& strSecuNum, BYTE del);
	void SendGameStart(ULONG ulIndex);
	void SendStopChange();
	void SendCreateCharacter( CTString& strName, UBYTE ubJob, UBYTE ubHair, UBYTE ubFace );

	void SendItemUse( SWORD nTab, SWORD nInvenIdx, LONG lIndex, LONG lEtc );
	// Ÿ���� �ʿ��� ������ ���
	void SendtargetItemUse( SWORD nTab, SWORD nInvenIdx, LONG lIndex, SBYTE sbType, LONG lMobIndex );	
	// ���� �ֹ��� ���
	void SendMixItemUse( SWORD nTab, SWORD nInvenIdx, LONG lMixItemidx, LONG lCashItemIdx, LONG lgameItemIdx);
	// �и� �ֹ��� ���
	void SendUnMixItemUse( SWORD nTab, SWORD nIdx, LONG lMixItemidx, LONG lCashItemIdx);
	
	// Inventory
	void UseSlotItem( int tabId, int inven_idx, SBYTE sbWearType = -1 );
	void DropItem(int tabId, int inven_idx, SQUAD cnt =1);
	void SwapItem(int tabId, int inven_idx, int tabId2, int inven_idx2);
	void DivideItem(SWORD nTabS, SWORD nIdxS, SWORD nTabT, SWORD nIdxT, int count);
	void ArrangeItem(int tab);
	BOOL IsExtensionState( int iJob, CItemData& ID );
	
	bool IsLord();

	// yjpark |<--
	// Teleport
	void SendWarpCancel();
// [KH_070316] ���� �����̾� �޸� ����
	void SendTeleportWrite( UBYTE sendMSG, UBYTE ubSlot, CTString &strComment );
	void SendTeleportWriteRus( UBYTE sendMSG, UBYTE ubSlot, CTString &strComment );
	void SendTeleportMove( UBYTE sendMSG, UBYTE ubSlot );
	void SendWarpTeleport( int iTeleportIndex );
	// Learn skill
	void SendSkillLearn( SLONG slIndex, int NpcVirIdx);
	void SendSSkillLearn( SLONG slIndex, int NpcVirIdx);
	// Stat point
	void SendUseStatPoint( UBYTE ubStatType );

	// HP, MP ȸ��
	void SendRecoverHPMP( SBYTE sbHPCount, SBYTE sbMPCount );
	void SendRecoverItemSeal( SWORD nTab, SWORD nIdx, SLONG slIndex);

	// �̺�Ʈ ����.
	void SendEventPrize();

	// ������ ������ ������ ���� ����� ����.
	void SendEventTreasureList();

	// ������ �������ڸ� ���ڴٰ� �޼����� ����.
	void SendEventOpenTreasure();
	
	// ũ��������,���� �̺�Ʈ 
	void SendEventNewyear(int tv_event);

// [KH_070413] �����ǳ� �̺�Ʈ ���� �߰�
	void SendEventMaster();

	void SendReqServerTime();

	// Upgrade
	void UpgradeItem( SLONG nWearPos, SLONG VirIndex, SLONG slPlus, SWORD nTab2, SWORD inven_idx2, SLONG slLevel, INDEX iProtect =-1, SWORD nTab3 =-1, SWORD inven_idx3 =-1);
	
	// Item Level Down
	void ItemLevelDown(SWORD inven_idx1, SWORD inven_idx2);

	// ������ ������ & ��ȭ��.
	void OptionAddItem(UWORD slWearPos, int WearVirIdx, SWORD nTab, SWORD inven_idx, int JemVirIdx);
	void OptionDelItem(UWORD slWearPos, int WearVirIdx, SWORD nTab, SWORD inven_idx, int JemVirIdx);
	
	void RemovePlatinumStone( SWORD nTab, SWORD inven_idx );
	
	void SealComposeReq( SWORD nTab, SWORD inven_idx, ULONG count );

	// Refine
	void RefineReq( SWORD nTab, SWORD inven_idx );

	void OpenBoxReq( SWORD nTab, SWORD inven_idx, ULONG count );

	void TransmogrifyReq( SWORD nTab, SWORD inven_idx );

	void ExtendMenuReq( SWORD nTab, SWORD inven_idx, int days );

	// Process
	void ProcessReq( SWORD nTab, SWORD inven_idx, SLONG slResultIndex, SLONG slResultCount, CNeedItems* NeedItems );

	// �̱�ȯ �߰� ( 12. 6 ) : ���� �޼��� 
	void ProductReq( SWORD nTab, SWORD inven_idx, SLONG slResultIndex, SLONG slResultCount, CNeedItems* NeedItems );

	// �̱�ȯ �߰� ( 12. 8 ) : ���� �޼��� 
	void MixReq( SWORD nTab, SWORD inven_idx, SWORD* arrTab, SWORD* arrIdx );
	
	// Date : 2005-01-12,   By Lee Ki-hwan
	void CompoundReq( SWORD nTab, SWORD nInvenIdx, SWORD* arrTab, SWORD* arrIdx );
	/****   WareHouse **********************************************************/
	void	SendWareHouseChangePassword( const CTString& strOld, const CTString& strNew );
	void	SendWareHouseIsSetPassword();
	void	SendWareHouseSeal();
	void	SendWareHouseListReq( const CTString& strPW );
	void	SendWareHouseDeletePassWord( const CTString& strID );
	void	SendWareHouseSetupPassWord( const CTString& strPW, const CTString& strOldPW );

	/****   Guild   ***********************************************************/
	void GuildJoin( SLONG slGuildIndex, SLONG slSrcIndex, SLONG slDestIndex );				// ���� ��û
	void GuildQuit( );									// Ż�� ��û

	void GuildCreate( const CTString &strGuildName );	// ��� ����
	void GuildUpgrade();								// ��� �±�
	void GuildDestroy();								// ��� ��ü
	void GuildChangeBoss( SLONG slDestIndex );			// ���� ����
	void GuildAddViceBoss( SLONG slDestIndex );			// �δ��� �Ӹ�
	void GuildDelViceBoss( SLONG slDestIndex );			// �δ��� ����
	void GuildMemberFire( SLONG slDestIndex );			// ��� ����

	void GuildApplicantAccept( SLONG slDestIndex );		// ���� ����
	void GuildApplicantReject( SBYTE sbWhoCancel );		// ���� �ź�

	// Date : 2005-03-18,   By Lee Ki-hwan
	void GBReq( SLONG nCharIndex, SLONG nPrize, SLONG nTime );	
	void GBReqReject();	
	void GBReqAccept();	
	void GBStopReq( SLONG nCharIndex );		
	void GBStopReqReject();	
	void GBStopReqAccept();
	/****   Teach   ***********************************************************/
	void TeachTeacherRegister(SBYTE sbStartPlayTime = -1, SBYTE sbEndPlayTime = -1);			// ���� ��Ͽ� �߰�
	void TeachTeacherCancelRegister();		// ���� ��Ͽ��� ����
	void TeachRefreshTeacherList();			// �İ��� ��� ����
	void TeachTeacherRequest( SLONG slCharIndex, CTString& strName );				// ������ �Ǿ�޶�� ��û��.
	void TeachTeacherReject( BOOL bStudent, SLONG slCharIndex, CTString& strName );	// ���� ���ҷ�.
	void TeachTeacherAccept( SLONG slTeacherIndex, CTString& strTeacherName, SLONG slStudentIndex, CTString& strStudentName );	// ���� ���ٲ�.
	void TeachTeacherGiveUp( SLONG slTeacherIndex, CTString& strTeacherName, SLONG slStudentIndex, CTString& strStudentName );	// ���� �ʿ����~!!!

	/****   ChangeJob ***********************************************************/
	void ChangeJobReq( SBYTE sbJob, int nNpcVirIdx );		// ���� ��û
	void ChangeJobGiveUp(int nNpcVirIdx);					// ���� ����
	void SendClassChange(SBYTE sbJob, int nNpcVirIdx);

	void SendRebornReq(int nNpcVirIdx);

	void SendWrongCaptcha();

#ifdef BATTLE_PASS_SYSTEM
	void SendBattlePassReq(int nNpcVirIdx);
	void SendBattlePassInfoReq(int nNpcVirIdx, int page = 0);
#endif

	void SendBattleWarfareMove();

	/****   ChangeWeapon ********************************************************/
	void ChangeWeaponReq( SWORD nTab, SWORD inven_idx, LONG lItemVirIndex, LONG lTradeIndex, LONG lChangeType, LONG lTokenVirIndex = -1, LONG lTokenCount = -1 );
	void ChangeWeaponEventReq( LONG lItemIndex, LONG lChangeType );

	// ���� �ʱ�ȭ
	void StatReset( int iStr, int iDex, int iInt, int iCon );

	// ���� ��ȯ �̺�Ʈ
	void SendChangeWeaponEvent();

	/************************************************************************/
	bool SendItemWearingMSG(SBYTE sbType, SBYTE sbWearPos, SWORD nTab, SWORD inven_idx, char take, int nVirIndex = -1);
	/************************************************************************/

	/****   MoonStone   ********************************************************/
	void SendMoonStoneStartReq();
	void SendMoonStoneTryReq();
	void SendMoonStoneResultReq();

	/****   MoonStone   ********************************************************/
	void SendCashMoonStoneReward();
	/****   Pet System   ********************************************************/
	void SendPetChangeRide();
	void SendPetSkillInit();
	void SendPetWarpTown();
	void SendPetDestruction();	// eons	�� �Ҹ�
	void SendPetItemMix( SLONG slPetItemIndex, SLONG slmethod );		// eons �� ����
	void SendPetRebirth( SLONG slPetIndex );		// eons �� ���� ���� ��û �޼���
	void SendWildPetRebirth( int nTab, int nIdx, int nNpcIdx );
	void SendPetitemInfo(SLONG slOwnerIndex,int nitemIndex);		//�κ��� �� ������ ������
 //new2022	
#ifdef PET_BUFF_ALL_SYSTEM
	void UsePetAllBuffs(SWORD nTab, SWORD inven_idx);
#endif
#ifdef PRESTIGE_SYSTEM
	void SendPrestigeReq(int nNpcVirIdx);
	void SendPrestigeInfoReq(int nNpcVirIdx, int page = 1);
#endif
	/****   Exchange   ********************************************************/
	void ExchangeReq_Req( SLONG slDestIndex, CTString &strDestName );
	void ExchangeReq_Rep();
	void ExchangeReq_Rej();
	void ExchangeReq_Ready();
	void ExchangeReq_Ok();
	void ExchangeItem_Add( int nUniIndex, SQUAD llCount );
	void ExchangeItem_Del( int nUniIndex, SQUAD llCount );
	// Quick slot
	void AddQuickSlot( int nPage, int nSlotNum, int nSlotType, int nData0, int nData1 );
	void SwapQuickSlot( int nPage1, int nSlot1, int nPage2, int nSlot2 );
	// Party
	// TO-KR-T20090903-005 ���� ��Ƽ ��û ����. [11/27/2009 rumist]
	//void PartyInvite( SBYTE sbType, SLONG slIndex );
	void PartyInvite( SBYTE sbType, SLONG slIndex, CTString strName ="" );
	void PartyAllow();
	void PartyReject();
	void PartyQuit();
	void PartyKick( SLONG slIndex );
	// Item plus effect
	void ItemPlusEffectReq( SBYTE sbOption );
	// yjpark     -->|

	// ��ī ���ڴ� ���� �̺�Ʈ
	void SendPresscorpsMessage(ULONG ulItemIndex, CTString Sendstr);
	
	void SendInput(void); // SendUsingSpeedHack --> SendInput �۸� ���� // ���ǵ��� ����� �뺸 

	// [2010/08/25 : Sora] ADD_SUBJOB
	BOOL IsMySubJob( SLONG slSubJob ) { return MyCharacterInfo.slSubJob & slSubJob; }
	
	// PLAYTIME 10�а������� ����
	void SendUpdatePlayTime(ULONG nTime);
	void SendInitSSkillReq(void);
#ifdef CLOUD_AUTO_QUEST_DELIVERY
	void Send_auto_quest(INDEX iQuestIndex);//Cloud auto quest
#endif
//안태훈 수정 시작	//(Zone Change System)(0.1)
	void GoZone(int zone, int extra, int NpcIdx = -1 );
//������ ���� ��	//(Zone Change System)(0.1)

	void ResetSkillDelayTime(); // ��ų ��Ÿ�� �ʱ�ȭ
	void ResetItemDelayTime(); // ������ ��Ÿ�� �ʱ�ȭ
	
	//-------------------Item Data---------------------------
	inline CItemData*	GetItemData(int iIndex)
	{
		return CItemData::getData(iIndex);
	}

	inline const char* GetItemName(int iIndex)
	{
		return CItemData::getData(iIndex)->GetName();
	}

	inline const char* GetItemDesc(int iIndex)
	{
		return CItemData::getData(iIndex)->GetDesc();
	}
 //Craft system
	//------------------Craft Data---------------------------
	inline CCraft*	GetCraftData(int iIndex)
	{
		/*auto it = CCraft::_vecdata.begin();
		auto endit = CCraft::_vecdata.end();
		for (; it != endit; ++it)
		{
			auto itCraft = *(it);
			if (itCraft->item1 == iIndex)
				return itCraft;
		}*/
		return NULL;
	}

	//------------------Jewel Data---------------------------

	int  GetJewelComposNas( int nGrade, bool bChaos)
	{
		if (bChaos)
			return wo_aJewelData[nGrade - 1].ca_comp_nas;
		else
			return wo_aJewelData[nGrade - 1].nor_comp_nas;
	}

	BOOL GetJewelGradeInfo( int GradeKey, _vecJewelInfo& Info )
	{
		std::map<int, _vecJewelInfo>::iterator	iterJewelGradeInfo = wo_mapJewelGradeInfo.find(GradeKey);
		std::map<int, _vecJewelInfo>::iterator	iterJewelGradeInfoEnd = wo_mapJewelGradeInfo.end();
		
		if (iterJewelGradeInfo == iterJewelGradeInfoEnd)
			return FALSE;
		
		Info = iterJewelGradeInfo->second;		
		return TRUE;
	}
	
	BOOL GetChaosJewelGradeInfo( int GradeKey, _vecJewelInfo& Info )
	{
		std::map<int, _vecJewelInfo>::iterator	iterChaosJewelGradeInfo = wo_mapChaosJewelGradeInfo.find(GradeKey);
		std::map<int, _vecJewelInfo>::iterator	iterChaosJewelGradeInfoEnd = wo_mapChaosJewelGradeInfo.end();
		
		if (iterChaosJewelGradeInfo == iterChaosJewelGradeInfoEnd)
			return FALSE;
		
		Info = iterChaosJewelGradeInfo->second;		
		return TRUE;
	}

	//------------------Skill Data---------------------------
	inline CSkill	&GetSkillData( const int iIndex )
	{
		if( iIndex > wo_iNumOfSkill || iIndex < 0 )
		{
			//ASSERTALWAYS("Invalid Skill Index!!!");
			return ga_World.wo_aSkillData[0];
		}
		return ga_World.wo_aSkillData[iIndex];
	}

	inline CShopData&	GetShopData(const int iIndex)
	{
		if(iIndex > ga_World.wo_iNumOfShop || iIndex < 0)
		{
			//ASSERTALWAYS("Invalid Shop Index!!!");
			return ga_World.wo_aShopData[0];
		}
		return ga_World.wo_aShopData[iIndex];
	}

	//-------------------Cash Shop Data-----------------------
	// wooss 050903
	inline CCashShopData& GetCashShopData(void)
	{
		return ga_World.wo_aCashGoodsData;
	}

	inline CCashShopData& GetCashShopData(const int iIndex)
	{
		if( iIndex < 0 ) 
		{
			//ASSERTALWAYS("Invalid Shop Index!!!");
			return ga_World.wo_aCashShopData[0];
		}
		return ga_World.wo_aCashShopData[iIndex];
	}

	inline CMakeItemData& GetMakeItemData(int iIndex)
	{
		for(int i =0; i < wo_iNomOfMakeItemData; i++)
		{
			if (wo_aMakeItemData[i].GetFactoryIndex() == iIndex)
			{
				return wo_aMakeItemData[i];
			}
		}
		return wo_aMakeItemData[0]; 
	}

	CTString GetWearingEffect(eEquipment Type, INDEX subType);	// ��� �������� ����Ʈ �̸��� �����´�.

	void SendLeaseItem(int iItemIdx);
	void SendEventItem(int iItemIdx, int iItemcont);
	void BuyItem(int iShopID, int iNumOfItem, __int64 iTotalPrice);			// ������ �Ȱ� �ִ� �������� ������.
	void SellItem(int iShopID, int iNumOfItem, __int64 iTotalPrice);		// �ڽ��� ������ �ִ� �������� �Ǹ���.
	void FieldShopBuyItem( int iNumOfItem, __int64 iTotalPrice);			// ttos : ��ȭ�� �̿� �ֹ��� ����
	void FieldShopSellItem(int iNumOfItem, __int64 iTotalPrice);			// ttos : ��ȭ�� �̿� �ֹ��� ����
	void SendWhoAmI();
	void SendGMCommand(const char *szCommand);

// ������ ���� ����		// 2nd Single Dungeon
void SendCraftItem(int idxCraft, int countItem); //Craft system
	void AddRescueNPC(CEntity* pEntity);	
	void UpdateRescueNPC(CEntity* pEntity, int iHP, int iMP);	
	void EndRescueNPC();
	UBYTE	m_ubGMLevel;
#ifdef PASSIVE_SYSTEM
	void SendPassiveSystemList();
	void SendPassiveSystemSlotList();
	void SendPassiveSystemEquip(int nIndex, int slot);
	void SendPassiveSystemUnequip(int nIndex);
#endif
// ������ ���� ��		// 2nd Single Dungeon

// ������ ���� ����
	// NOTE : �޼����� ���� �ð�.
	// NOTE : Ÿ�� �ƿ��� üũ�ϱ� ���� �κ�.
	unsigned int	m_uiSendedTime;		// �޼����� ���������� �ð�.
	BOOL			m_bSendMessage;		// �޼����� ��������(TRUE), �׿� ���� ������ ������(FALSE)
// ������ ���� ��	//(GM Command)(0.1)
	
	//0701 kwon	
	SLONG SearchClientChaIndex(ULONG Index);

	BOOL SearchEntityByNetworkID( long lIndex, SBYTE sbType, CEntity* &pEntity );
	void SendPickMessage( CEntity *pEntity, ULONG ItemIndex, BOOL bLayerCheck = TRUE );
	void SendStopMessage(CEntity *pEntity, CPlacement3D MyPlacement);
	void SendMoveMessage(CEntity *pEntity, CPlacement3D plPlacement, SLONG speed);
	void SendAttackMessage(CEntity *pAttackerEntity, CEntity *pTargetEntity, BOOL bPvp=FALSE);	
	void SendAttackSymbol();
	void SendProduceMessage(ULONG Index, SBYTE sbKind);
	void SendCollectProduceMessage(LONG npc_client_index);
	void SendSelectProduceMessage(LONG npc_client_index, LONG item_db_index);
	void SendNPCProcessMessage(LONG processItemDBIndex, LONG count);
	void SendBoosterUpgrade(LONG itemServerIndex);
	void SendCancelSkillMessage();
	void SendAttackMessageInContainer(CSelectedEntities& dcEntities);
	void SendSkillMessage(int nSkillIndex, CEntity *pEntity, int nTargetIndex, BOOL bFire, UBYTE ubMove=0);
	void SendPetSkillMessage(int nSkillIndex, CEntity *pSourceEntity, CEntity *pTargetEntity, BOOL bFire);
	void SendPetCommandMessage( int nSkillIndex, CEntity *pSourceEntity );

	// ��ȯ���� ��ų �޼���.
	void SendSlaveSkillMessage(int nSkillIndex, CEntity *pSourceEntity, CEntity *pTargetEntity, BOOL bFire);
	void SendSlaveSkillMessageInContainer(int nSkillIndex, CEntity *pSourceEntity, CSelectedEntities &dcEntities, BOOL bFire);
	
	void SendSkillMessageInContainer(int nSkillIndex, CSelectedEntities& dcEntities, BOOL bFire);	
	void InitSkillID();
	void SetMyPosition(CPlacement3D plPlacement, FLOAT camera_angle);

	// 0 = SYSMSG_NORMAL
	void ClientSystemMessage( CTString &strSysMessage, int nSysType = 0 );
	void SendRebirthMessage();
	void DeleteAllMob();
	
	//wooss 050805
	//Ȯ��� ������ �޽��� 
	void SendRebirthMessageEx(int, BOOL ,BOOL);
	//wooss 050808
	//send warp message
	void SendWarpItemMessage(UBYTE warpType,CTString charName=CTString(""),BOOL allow=FALSE);
	void SendProlongMessage(int tabId, int inven_idx);
	//wooss 050817
	//send chang name message
	void SendChangMyName(CTString strMsg, int itemCardName);
	void SendChangGuildName(CTString strMsg, int itemCardName);
	//wooss 050820
	void SendExSlotMessage(int slotNum);
	//wooss 051031 
	//send 2pan4pan event message
	void SendEvent24(int sel,SBYTE eventType);
	
	// send find friend 060201
	void SendFindFriend(int tv_event, void * tv_input = NULL);
	void SendCashItemMessage(int nType);
	void SendCashItemMessage(int nType, INDEX searchType, INDEX ReqPage = 1);

	void SaveSettings(int autopickup, int autoigni, int autosell); // MSG_EX_SETTINGS
	void SendAutoFunc(int type, int option); // Val adding auto igni/pickup

	void SendActionMessage(SBYTE action_type, SBYTE action_id, SBYTE state, CEntityPointer epTarget = NULL );
	void DelMobTarget(ULONG ClientIndex);
	void ResetMobStatus(ULONG ClientIndex);
	void DelChaTarget(ULONG ClientIndex);
	void ResetChaStatus(ULONG ClientIndex);
	void DelWildPetTarget(ULONG ulSIndex);

	void SendQuestMessage(UBYTE msgQuestType, INDEX data);
	void SendQuestPrizeMessage(UBYTE msgType, INDEX iQuestIndex, INDEX iNpcIndex, INDEX iOptionItemIndex, INDEX iOptionItemPlus);
	void SendQuestTeleportMessage(UBYTE msgType, INDEX iQuestIndex, INDEX iNpcIndex);

	// Ranking
	void Ranking_RequestList( SBYTE sbJob );
	void Ranking_RequestPrizeList();
	void Ranking_Prize();
	void RankingSummonReq();
	void RankingRebornReq();
	void RankingPvPReq();

	// �̱۴������� �޼����� ��� ������ ���ؼ� �ʿ��� �κ�.
	void AddAttackList( UBYTE ubAttackType, INDEX iAttackIndex, UBYTE ubTargetType, INDEX iTargetIndex );
	void SendAttackList();
	void ClearAttackList();

	void AddMoveList( INDEX iIndex, FLOAT fX, FLOAT fZ, FLOAT FH, FLOAT fAngle );
	// EDIT : BS : BEGIN
	void AddMoveList(CEntity &en);
	void SendMoveList(bool bForce = false);
	// EDIT : BS : END
	void ClearMoveList();

	void AddRegenList(INDEX iIndex, INDEX iMobType, FLOAT fX, FLOAT fY, FLOAT fZ, FLOAT fAngle, INDEX iYLayer, INDEX iEntityID);
	void SendRegenList();
	void ClearRegenList();

	// ������� ����Ʈ ����
	void AddLegitList(int Index);
	BOOL SearchLegitList(int Index, BOOL bDel = FALSE);
	void DelLegitList(int Index);

	// [100322: selo] ģȭ�� ���� NPC ����Ʈ ����
	void AddAffinityRewardNPC(int iIndex);
	void RemoveAffinityRewardNPC(int iIndex);
	void ClearAffinityRewardNPC();
	const int GetAffinityRewardNPCListCount();
	const std::list<int>& GetAffinityRewardNPCList();

	// ��Ƽ Ÿ���� ���ؼ� �������� ������ ��� ã�Ƴ��ϴ�.
	void FindTargetsInRange(
								 CEntity* pPlayer, 
								 CEntity* pCenter,
								 CSelectedEntities &cen, 
								 FLOAT fFallOffRange, 
								 INDEX iMaxEnemies,
								 FLOAT fAngle = 360.0f,
								 INDEX iSkillIndex = -1,
								 INDEX	iTargetType = CSkill::STT_TARGET_D120 );
	
	void FindTargetsInRangeEx(CEntity* pCenter,	CSelectedEntities& cen, FLOAT fFallOffRange, INDEX iMaxEnemies);

	void CheckAttackTarget( INDEX iSkillIndex, CEntity* pTargetEntity, FLOAT fDist = 0.0f, BOOL bElementalAttack = FALSE ); 
	// ��ų ������ �Ҽ� �ִ��� �Ǵ��մϴ�.
	BOOL CheckSkillAttack( INDEX iSkillIndex, CEntity* pEntity );

	// Date : 2005-05-19(���� 8:25:50), By Lee Ki-hwan
	void MgrRegistReq( int nCharIndex, CTString strCharName );
	void MgrRegistAllow( int nCharIndex, CTString strReqCharName );
	void MgrSetCondition( int nCharIndex, int nCondition );
//	void MgrChatting();
	void MgrRegistCancel(int nCharIndex, CTString strReqName);
	void MgrFriendDeleteBlock(int nCharIndex);
	void MgrDeleteMember( int nCharIndex, int nTargetIndex, CTString strName );
	void SendFriendCatting( int nCharIndex, CTString strName, CTString strTargetName, CTString strMessage );
	//�޽��� �߰� ���
	void MgrFriendInvite( int nCharIndex, int nChatIndex, int nTargetIndex);
	void MgrFriendOut( int nCharIndex, int nChatIndex );
	void MgrFriendChat( int nCharIndex, int nChatIndex, CTString strChat);
	void MgrBlock( CTString strTarget );
	void MgrUnBlock( int nCharIndex);
	void MgrGroupAdd( CTString strName);
	void MgrGroupDel( int nGroupIndex);
	void MgrGroupRename( int nGroupIndex, CTString strNewName);
	void MgrGroupMove( int nGroupIndex, int nCharIndex);
	void MgrSetChatColor( int nColIndex);
	void MgrOneVsOneConnect( int nCharIndex, int nOtherCharIndex, CTString strChat );
	
	// Date : 2005-07-06(���� 2:36:01), By Lee Ki-hwan
	//  ���� ���� �޼��� 
	void SetTimeReq( int nDay, int nHour, int nZone ); // �����ð� ���� ��û	// [2010/11/01 : Sora] ���� ����
	void GetTimeReq();						// ���� �ð� Ȯ�� ��û
	void AttackReq();						// ���� ��û 
	void DefenseGuildReq();					// ���� ��û 
	void AttackCharReq();					// ���� �뺴��û
	void AttackGuildReq();					// ���� �뺴 ��û 
	void WarItemMixReq( SWORD* arrTab, SWORD* arrIdx ); // ���� ������ ���� ��û 

	// �ֿϵ��� ����...
	void CallPet( LONG lIndex );													// ���� ȣ����.
	void CheckPetType( SBYTE sbPetTypeGrade, INDEX &iPetType, INDEX &iPetAge );		// �� Ÿ�԰� ���̸� ����.
	void RidePet( CEntity *pCharacter, CEntity *pPet, INDEX iPetType );		// �ֿϵ����� Ÿ���� ó��.
	void LeavePet( CEntity *pCharacter );									// �ֿϵ������� �������� ó��.
	// wildpet riding functions [12/21/2010 rumist]
	void RideWildPet( CEntity *pCharacter, CEntity* pWildPet, CTString strFileName );
	void LeaveWildPet( CEntity *pCharacter );
	void UpdatePetTargetInfo( INDEX iPetIndex );						// �ֿϵ����� ������ ������.
	void ClearPetList();
	void SendMovingGuildWarArea();

	// Date : 2005-09-06(���� 11:22:30), By Lee Ki-hwan
	void SendGuildStashHistroyReq();
	void SendGuildStashViewReq();
	void SendGuildStashTakeReq( LONGLONG llMoney );
	// ���â�� �̿볻�� ����Ʈ ��û.
	void SendGuildStashUseRecord(INDEX iLastIdx = 0);
	
	// Date : 2005-09-08(���� 5:59:52), By Lee Ki-hwan
	void SendChuseokUpgrade();
	void SendChuseokExchange();

	///////////////////////////////////////////////////////////////////////////////////
	// 2006 �߼� �̺�Ʈ :Su-won	|---------->
	
	//���� �����
	void Send2006ChuseokRicecakeMake();
	void Send2006ChuseokRainbowMake();
	//�������� ����ǰ���� ��ȯ�ϱ�
	void Send2006ChuseokExchange();
	
	// 2006 �߼� �̺�Ʈ :Su-won	<----------|
	///////////////////////////////////////////////////////////////////////////////////
	
	// 2006 X-Mase Event [12/12/2006 Theodoric]
	void Send2006XMasEvent( SLONG nCakeCount);
		
	void SendSuperStoneReq();
// 060118 wooss japan package item....
	void SendCouponItemReq(CTString strNum);
// 060223 wooss japan connect item....
	void SendConnectItemReq();
// 060321 eons japan clothes exchange event
	void SendClothesExchange( int nValue );

// 060601 wooss japan rainyday event
	void SendRainyDayExchange();

	void SendRemoveBuffReq(int itemIndex, int skillIndex);
	
	void Send2p4pLetter( LONG lGameIndex );

	// 060306 wooss Party Recall CashItem
	void SendPartyRecallConfirm(CTString tmp_str,LONG tmp_idx,BOOL tmp_answer);
	// Date : 2006-04-27(���� 2:36:02), By eons
	void SendNetCafeOpenBox( void );

	// Date : 2006-11-16(���� 11:08:04), By eons
	void SendUsaOpenBetaGift(void);

	// Date : 2006-05-09(���� 5:08:22), By eons
	//��Ƽ ��Ī ����
	void SendPartyRegistNormal( int nType );
	void SendPartyRegistParty( CTString strComment, DWORD JobFlag, int LimitLevel );
	void SendPartyListReq( int nPage, int nJob, int nLimitLv, int nPtType, BOOL bState );
	void SendPartyRegistDelete( void );
	void SendPartyInviteReq( int nCharIndex );
	void SendPartyJoinReq( int nBossIndex );
	void SendPartyJoinAllow( int nReqIndex );
	void SendPartyJoinReject( int nReqIndex );
	
	// 060601	wooss worldcup event 1
	void SendWorldCupEvent( int msgCmd, int iSelCountry );
	void SendWorldCupGoldenBallEvent( int nSendType, int nTeamAScore, int nTeamBScore );

	// Date : 2006-06-27(���� 10:42:39), By eons
	void SendBuddhismEvent( BYTE nType );

	// Date : 2006-06-28(���� 4:18:06), By eons
	// ���� ä�� �̺�Ʈ
	void SendBuyCollectBox( void );
	void SendGiftCollectBox( void );
	void SendDropInsect( int nInsect, LONG lBoxVIndex );

	//Request PBI USE
	void CNetworkLibrary::SendQuestResult(void);

	// ���� ���� �̺�Ʈ( 2007 �߷�Ÿ�� ���� )
	void SendSaveBingoItem(BYTE nPos, int nGiftItemIndex, int nBoxItemIndex);
	void SendReqGiftChocoBox(int nUniItemIndex);

	int		m_iLastError;

	void LearnPetSkill( LONG nSkillIndex ); 
	void LearnWildPetSkill(LONG nSkillIndex);
	void MandateBossReq( CTString strMandateCharName );
	void SendCastleMapRecent();
	void SendCastleMapSignal( FLOAT fX, FLOAT fY, LONG lSenderFlag, LONG lSenderIndex );

	void CreateSlave( int iOwnerIndex, CEntity* pEntity, int iType );
	void SendGameStart();
	void SetLoadingZone( LONG lZone = -1 );
	LONG GetLoadingZone();

	// check point for dungeon quest
	void SetCheckPointData(int questIdx,int chkNumFlag, int maxChkflag=-1);

	// wooss 070307 --------------------------------------------------->>
	// kw : WSS_WHITEDAY_2007
	void SendWhiteday2007(UBYTE ubType);
	void SendWhiteday2007Letter(int itemIdx,COLOR colMsg,CTString tStr);
	// ----------------------------------------------------------------<<

	// WSS_GUILDMASTER 070416 ----------------------------------------->>
	void SendRequestParentsday(int reqIdx);
	void SendParentsdayAddPoint(int charIdx);
	// ----------------------------------------------------------------<<		

	/*
#ifndef NO_GAMEGUARD
	// WSS_NPROTECT 070402 -------------------------------------------->>
    void SendnProtectAuth2(DWORD dwArg);
	BOOL Init_nProtect();
	void SetHwnd_nProtect(HWND _hwndMain);
	void Check_nProtect();
	BOOL NPGameMonCallbackErrChk( DWORD dwMsg, DWORD dwArg);
	// ----------------------------------------------------------------<<		
#endif
	/**/
	// WSS_MINIGAME 070420 -------------------------------------------->>
	void SendMinigameDefaultMessage(UBYTE eventType, UBYTE subType);
	void SendMinigameSelect(UBYTE eventType, UBYTE subType, UBYTE cSelect);
	void SendMinigameSelectGift(ULONG cSelect);
	// ----------------------------------------------------------------<<

	/*** FLOWERTREE2007 ****************************************************/
	void SendFlowerTreeReq(UBYTE subType);
	/***********************************************************************/

	//////////////////////////////////////////////////////////////////////////
	// �Ǵн� �̺�Ʈ

	void SendPhoenixCharacterCondition();		//�Ǵн� ĳ���� ���� ���ɿ���
	void SendCreatePhoenixCharacter();	//�Ǵн� ĳ���� ����

#ifdef DEMIGOD
	void SendDemiGodCharacterCondition();		//�Ǵн� ĳ���� ���� ���ɿ���
	void SendCreateDemiGodCharacter();	//�Ǵн� ĳ���� ����
#endif

	//////////////////////////////////////////////////////////////////////////
	// [sora] ������ �ý���
	
	void ExpeditionCreateReq();																			// ������ ����
	void ExpeditionInviteReq( SLONG slIndex );
	void ExpeditionAllowReq();
	void ExpeditionRejectReq();
	void ExpeditionQuitReq();
	void ExpeditionKickReq( SLONG slIndex );
	void ExpeditionEndReq();
	void ExpeditionChangeDivisionTypeReq(UBYTE msgType, SBYTE sbExpedType, SBYTE sbDiviType);
	void ExpeditionChangeLeaderReq( SLONG slIndex );
	void ExpeditionChangeSubLeaderReq( BOOL bIsSubLeader, SLONG slIndex );
	void ExpeditionChangeGroupReq( SLONG slGroupSrc, SLONG slIndex, SLONG slGroupDesc, SLONG slPos );
	void ExpeditionAddCharReq( CTString &strCharName );
	void ExpeditionViewDetailReq( SLONG slGroup, SLONG slIndex );
	void ExpeditionSetLabelReq(SLONG slCharType, SLONG slMode, SLONG slLabelType, SLONG slIndex);
	
	void ExpeditionCollectQuestItemReq(SLONG slIndex);													// ������ ����Ʈ ������ ����
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	void ExpeditionTeamJoinReq(SLONG slIndex, SLONG sldifficulty, SLONG slpzone);//Cloud Expedition_Party_Dungeon
	void ExpeditionTeamJoinMember();//Cloud Expedition_Party_Dungeon
	void ExpeditionTeamRecallReq(SLONG slIndex);//Cloud Expedition_Party_Dungeon
	void ExpeditionTeamRewardReq(SLONG slIndex, SLONG slpzone);//Cloud Expedition_Party_Dungeon
#ifdef CLOUD_EXPEDITION_REWORK
	void ExpeditionDungeonDetailReq(SLONG Mode);
#endif
#endif
	// [sora] ��Ƽ ���̵�
	void PartyEndReq();							// ��Ƽ ��ü
	void InitInZoneReq();						// �δ� �ʱ�ȭ

	// [sora] ���� �̵�
	void RaidInzoneJoinReq(SLONG slZoneNo, SLONG exParam = -1);
	void RaidInzoneQuitReq(SLONG slZoneNo = -1, SLONG slExtraNo = -1);
	
	// [sora] �ν���Ʈ �� �ͼ�������û
	void SendRaidInfoReq();
	//////////////////////////////////////////////////////////////////////////

	// [070613: Su-won]
	// ����,�� ��ȯī�� ��� ��û
	void UseChangeWeaponItem( SWORD nTab, SWORD inven_idx, LONG lItemIndex, LONG lChangeType, LONG lTradeItemIndex );
	// �� ���� ������ ��� ��û
	void SendPetNameChageReq( int nPetIndex, CTString strPetName );

	/////////////////////////////////////////////////////////////////////////////
	// [070705: Su-won] EVENT_SUMMBER_2007
	void SendPaperFoldingReq(int nItemIndex0, int nItemIndex1, int nItemIndex2);
	void SendPaperBlendingReq(int nItemIndex);
	// [070705: Su-won] EVENT_SUMMBER_2007
	/////////////////////////////////////////////////////////////////////////////

	// Eons 070905
	void SendBJMono2007Req(UBYTE subType, ULONG ulNum=0); // SK BJ Mono Event
	void SendLC1000DayHatUpgradeReq(SWORD nIdx, LONG lItemIndex); // 1000�� �̺�Ʈ ������ ���׷��̵�
	void SendLC1000DayTakeHatReq();
	void SendTakeFireCracker();

	// [070807: Su-won] EVENT_ADULT_OPEN
	// ���μ��� ���� �̺�Ʈ ���� ���� ��û
	void SendAdultOpenEventReq( int iEvent, int tv_tab=-1, int tv_row=-1, int tv_col=-1);
	
	// WSS_TG2007 2007/09/14
	// ��ũ���� �̺�Ʈ
	void SendTG2007ScreenshotReq();
	void SendTG2007RichYearReq(int subType);
	
	// Eons 071012 �ҷ��� �̺�Ʈ 2007
	void SendHalloween2007Req(UBYTE subType);
	void SendBuffNPCReq(UBYTE subType);
	
	// [071122: Su-won] NEW_MOONSTONE
	void SendMoonStoneMix(INDEX iMoonStone, INDEX iMoonStoneBox);

	//[071123: Su-won] DRATAN_SIEGE_DUNGEON
	void SendDratanSiegeDungeonMSG(UBYTE ubSubType, UBYTE ubSubSubType =-1, int nValue =-1);
	
	////////////////////////////////////////////////////////////
	void SendCashPersonShop(UBYTE subType);

	// Eons 071204
	void SendXMAS2007DecoReq(UBYTE subType);

	void SendRestartGame();
	void SendReceiveRestartGame();
	
	void SendUseGoDungeon(INDEX iItemIndex);

	void SendItemDelete(SWORD iTab, SWORD inven_idx, INDEX UniIndex, SQUAD count);
	//���� �� ��� ������ ����
	void SendUseWildPetItem(int posId, int tabId, int inven_idx, int item_index);
	
	void SendSupportSkill(UBYTE ubMsg); // �ʺ� �� �������� ������ ��ų �޽��� ��û(������ �������߰��� ���� ���)

	void SendHanaposEvent(int nNpcVirIdx);
	
	void SendEventRequital(int nRequital);

	// ���̵� �ý��� ������Ʈ �Ҽ�ȭ �޼���(Ŭ�� �� ����)
	void SendRaidObjectEvent(ULONG iObjectID);

	void SendMakeItemList(ULONG sealtype, UBYTE UItype);		//��� ���� ����Ʈ ��û

	inline _AffinityInfo*		GetAffinityPointer() { return (&AffinityInfo);	}
	void SendAffinityConnectReq( SLONG npcIdx );
	void SendAffinityShopReq( SLONG npcIdx );
	void SendAffinityGiftInfoReq( SLONG npcIdx );
	void SendAffinityGiftReq( SLONG npcIdx );
	void SendAffinityInfoTabReq( SLONG npcIdx ); // ģȭ�� ����2 ģȭ�� ���� ��û [2/13/2013 Ranma]
	inline CAffinityData*		GetAffinityData()	{ return &wo_aAffinityData[0]; }
	void ClearAffinityData();
	
	// connie [2009/9/15] - NPC ã��
	void SendNPCPortalGoReq(SLONG slIndex);
	void SendNPCPortalLocationReq(SLONG slIndex);

	// [091028 sora] �ǻ� �����۰� ����� �������� ã�� ��û
	void SendCheckComposition(SWORD nTab, SWORD nInvenIdx, SLONG slUniIndex);

	// [100208: selo] ���� ����Ʈ ����
	void SendRestoreAbandonQuest(SQUAD llMoney);

	// [100208: selo] ����Ʈ ������ �ٽ� �ޱ� ��û
	void SendTakeAgainQuestItem();

	// [100324 : sora] ��ī��
	void SendLacaretteTokenReq();
	void SendLacaretteRetteReq( SLONG courseNum, SLONG couseIndex, SLONG tokenIndex );
	void SendLacaretteUseCountReq();
	void SendLacaretteResultReq( INDEX itemIndex );
	void SendLacaretteCloseReq();
	void SendLacaretteTokenReadyReq();
	
	// [2010/08/25 : Sora] ADD_SUBJOB ���� ���� ���
	void SendSubJobRegister( SLONG subJobCode );

	// [100513: selo] ($E_WC2010) 2010 ���ư� ������
	void SendWorldCup2010_Event(MSG_EVENT_WORLDCUP2010_TYPE e_Type, INDEX iParam = 0);
	
	// [2010/06/30 : Sora] ���� ��� �����ο�
	void SendOwnerGuildBuffReq();

	//  [7/2/2010 kiny8216] ATTENDANCE_SYSTEM : �⼮ �ý���
	void SendAttendanceReq( INDEX subType );

	// [7/15/2010 kiny8216] MONSTER_ENERGY_IGNITION_SYSTEM
	void SendEnergySkillMessage();

	// [8/31/2010 kiny8216] �İ��� �ý��� ����
	void TeachGiftReq();
	
	// [9/29/2010 kiny8216] ���� �ڽ�Ƭ
	void LordCostumeReq();
	// ���� ��� �ڽ�Ƭ [1/21/2011 ldy1978220]
	void LordGuildCostumeReq();
	void LordGuildTitleReq();

	// [10/6/2010 kiny8216] ���� ���θ�� �̺�Ʈ
	void SendPromotionEventReq(CTString strNum);
	// [2010/11/01 : Sora] ���� ����
	void SendGuildWarTimeMenu();
	void SendGuildWarTimeReq();
	
	// [2011/01/18 : Sora] �⼮ �̺�Ʈ
	void SendAttendanceRewardReq();

	// [2011/02/09 : Sora] ����Ʈ ������ �ٽ� �ޱ�
	void SendRestoreQuestItem( SLONG questIndex );

	void SendFaceOffMessage( UBYTE ubType, UBYTE ubFaceType = -1, UBYTE ubHairType = -1 );
	//////////////////////////////////////////////////////////////////////////
	// void SendEventMsg()�� �̺�Ʈ �޼��� �Լ��� ��� �þ�°��� ȸ���ϱ� ���Ͽ� ���� ó���� �ϵ��� �սô�.
	// CNetwork class���� �̺�Ʈ ���� �Ķ���͸� �޾Ƽ� �ѹ��� SendEventMsg()�� �����ϵ��� �սô�.
	// ���� �Ķ���ʹ� �� ���� Ÿ�� ����, ULONG, UBYTE, CTString 3���� Ÿ�Ը����� ���� ó���� �����ϹǷ�(type casting),
	// ���� �Ķ���� ������ static_Array<ULONG>, static_array<UBYTE>, static_array<CTString>���� �սô�.
	// �̺�Ʈ �޼��� ��Ŷ ���������� ������ �����Ͽ� ���ߵ��� �սô�.
	// ���� �ȵǸ� �ٺ�~
	void SendEventMsg(UBYTE ubEventType);
	
	void SendRaidScene(INDEX ObjType, INDEX Id, INDEX iData = -1);

	void SendNetworkMessage(CNetworkMessage& NetworkMsg) { SendToServerNew(NetworkMsg); }	
		//added by sam 10/11/11
	void SendRankingLsit ( INDEX iIndex, INDEX iPageIndex );
	void SendWildPetMountReq( const BOOL bMount );
	void SendComebackMessage();
	void SendBirthdayMessage( INDEX index );
	// royal rumble [4/19/2011 rumist]
	void SendRoyalRumbleJoinReq();			// ����
	void SendRoyalRumbleRejectReq();		// ���� ���.
	void SendRoyalRumbleRewardReq();		// ���� ��û
	void SendRoyalRumblePointReq();			// ����Ʈ ��ȸ.
	void SendRoyalRumbleNextTimeReq();		// ���� ��� ���� ��ȸ.
	void SendRoyalRumbleStartReq();			// ���� ���� ��û.

	void SendMasterStoneUseReq(SWORD nMStoneTab, SWORD ubMStoneIdx, SLONG slMStone, 
		SWORD nTargetTab, SWORD ubItemTgtIdx, SLONG slItemTgt);
	// Temp Message str, int
	// add wooss 060306 for message argument
	CTString	m_tmp_str;
	LONG		m_tmp_idx;

	void SendGuildMarkWndOpenReq();	// [sora] GUILD_MARK
	void SendGuildMarkEditEndReq( SBYTE gm_row, SBYTE gm_col, SBYTE bg_row, SBYTE bg_col, SWORD nTab, SWORD nInvenIdx ); // [sora] GUILD_MARK

	// ��ŷ �ý��� ���� [trylord : 110825]
	void SendRankingListEx(UCHAR ucType, UCHAR ucSubType);
	void SendRankingSearchListEx(UCHAR ucType, UCHAR ucSubType, CTString pcstrSearch);

	void pkPenaltyReformRewardReq(LONG titlenum);

	void SendEventKrathongReq();
	void SendUserNotice(CTString strMessage);
	// [2011/11/14 : Sora] �±� ���� ź���� �̺�Ʈ
	void SendKBRewardReq( UCHAR commandNum );
	// ��� �ý��� ���� [trylord 111227]
	void SendGuildMasterKickReq(INDEX idxGuild);				// �渶 �߹� ��û [trylord 111228]
	void SendGuildMasterKickCancelReq(INDEX idxGuild);		// �渶 �߹� �������� [trylord 111228]
	void SendGuildRemoteJoinReq(CTString strTargetName, LONG lType);
	void SendGuildRemoteJoinOKReq(CTString strTargetName, LONG lType);
	void SendGuildRemoteJoinNOReq();
	void SendGuildRecallReq();

	void SendPetAccumulateUse(SBYTE scType, LONG lIndex);

	// Ÿ�ٴ���� ������ �˷��ش�. (����� pc��)
	void SendClickObject(int charIndex);

	// �����̾� ĳ���� ����
	void SendPremiumCharItemUse(SWORD tab, SWORD invenIdx, int VirtualIdx);
	void SendPremiumCharJumpReq(CTString strCharName);

	//	FD_TEST �迵ȯ : ����Լ� �߰�
	void	Set_MyChar_MorphStatus_EVOCATION_CONVERTING();
	void	Set_MyChar_MorphStatus_EVOCATION();
	void	Set_MyChar_MorphStatus_MORPH_END();
	void	Set_MyChar_MorphStatus_TRANSFORMATION();
	void	Set_MyChar_MorphStatus_EVOCATION_BEGIN();
	bool	Is_MyChar_MorphStatus_MORPH_END();
	int		Get_MyChar_MorphStatus();
	bool	IsAttackMe( int targetID ); // TO.DO HP
	bool	Get_MyChar_Attack(int targetID,LONG	targetHP);
	void	Set_MyChar_Effect(int item_E, int statusEffect);
	SBYTE	Get_MyChar_faceStyle();
	SBYTE	Get_MyChar_hairStyle();
	UBYTE	Get_MyChar_Job();

	void	SendReformItemReq( UCHAR reformerGrade, 
		SWORD reformerTab, SWORD reformerIdx, 
		SWORD magnifierTab, SWORD magnifierIdx, ULONG magnifierCount, 
		SWORD reformItemTab, SWORD reformItemIdx, int nNPCVIdx );

	UINT	getSeq()	{ return ++m_seq; }		// ������ ��Ŷ�� ������ �� ������Ŵ.
	void	resetSeq()	{ m_seq = 0; }			// ���� ����ÿ� �ʱ�ȭ ��Ŵ.

	void	RestartGame();
private:
	// Low-level packet sender (already exists)
	void SendPacket(const void* data, size_t size);
	bool	CheckSendSkill(INDEX nIndex);

	UINT	m_seq;
	BOOL	m_bIsRvr;
	INDEX	m_nLastSkillIndex;
	__int64	m_nSkillSendTime;
};

// pointer to global instance of the only network object in the application
ENGINE_API extern CNetworkLibrary *_pNetwork;

// convert string address to a number
ENGINE_API extern ULONG StringToAddress(const CTString &strAddress);
// convert address to a printable string
ENGINE_API extern CTString AddressToString(ULONG ulHost);

#endif  /* include-once check. */

