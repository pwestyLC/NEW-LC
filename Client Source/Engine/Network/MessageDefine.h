#ifndef SE_INCL_MESSAGEDEFINE_H
#define SE_INCL_MESSAGEDEFINE_H
#ifdef PRAGMA_ONCE
  #pragma once
#endif

#define SUCCESS_OK          0
#define ERR_FAIL            1
#define ERR_NOTHING_TO_DO   2
  
// message type 
// transmitted as 6-bit value
// up to 64 values allowed
// upper 2 bits are used to indicate compression used

// ADD NEW MESSAGE TYPES TO THE END!!!
typedef enum NetworkMessageType {

//0522 kwon �߰�.
	MSG_UNKNOWN		= 0,		// unknown

	// ���� �޽���
	MSG_FAIL,					// ���� �߻� �˸�	: errcode(uc)
	MSG_DB,						// DB ����			: errcode(uc) ...


	// LOGIN ����
	MSG_LOGIN,					// LOGIN			: version(n) mode(uc) id(str) pw(str) nation(c) seed(n)
	MSG_MENU,					// MENU ȭ��		: mode(uc) ...
	MSG_START_GAME,				// ���� ����		:


	// ĳ���� ����
	MSG_STATUS,					// ĳ���� ����		: level(n) exp(ll) need_exp(ll) hp(n) addhp(n) maxhp(n) // ������� mp(n) addmp(n) maxmp(n) // ������� str(n) dex(n) int(n) con(n) opstr(n) opdex(n) opint(n) opcon(n) attack(n) addattack(n) // ������� magic(n) addmagic(n) // ������� defense(n) adddefense(n) // ������� resist(n) addresist(n) // ������� skillpoint(n) weight(n) maxweight(n) walkspeed(f) runspeed(f) attackspeed(c) magicspeed(c) pktitle(c) pkpenalty(n) pkcount(n) fame(n) attackrange(f) join_flag_merac(c) skillspeed(n) attrmap(uc) mountPet(c) evocationType(c) evocationRemain(n) presscorps(c)(���ڴܿ���)

	MSG_APPEAR,					// ��Ÿ��			: PC : isNew(uc) type(c) index(n) name(str) job(c) job2(c) hairstyle(c) facestyle(c) x(f) z(f) h(f) r(f) yLayer(n) hp(n) maxHP(n) state(c) pkstate(c) pktitle(c) pluseffect(c) [wear_item_index(n) wear_item_plus(n)]:6 assist_state(n) assist_count(c) [itemidx(n) index(n) level(c) remain(n)]:count shoptype(c) shopname(str) guildindex(n) guildname(str) guildposition(n) mobindex(n) map_attr(uc) join_flag_merac(c) mountPet(c) evocationType(c) issupporter(c)
								//					: NPC: isNew(uc) type(c) index(n) vnum(n) x(f) z(f) h(f) r(f) yLayer(n) hp(n) maxHP(n) assist_state(n) assist_count(c) [itemidx(n) index(n) level(c) remain(n)]:count map_attr(uc)
								//					: Pet: isNew(uc) type(c) index(n) owner_index(n) owner_name(str) petTypeGrade(c) x(f) z(f) h(f) r(f) yLayer(n) hp(n) maxHP(n) map_attr(uc)
								//					: ��ȯ��: isNew(uc) type(c) index(n) elemental_type(c) owner_index(n) owner_name(str) x(f) z(f) h(f) r(f) yLayer(n) hp(n) maxHP(n) assist_state(n) assist_count(c) [itemidx(n) index(n) level(c) remain(n)]:count map_attr(uc) isbigsize(c)
	MSG_DISAPPEAR,				// �����			: type(c) index(n)
	MSG_AT,						// ��ġ ����		: index(n) name(str) job(c) job2(c) hair(c) face(c) zoneNo(n) areaNo(n) x(f) z(f) h(f) r(f) yLayer(n) userindex(n) guildoutdate(n) pluseffect(c) map_attr(uc)

	// 10
	MSG_INVENTORY,				// �κ��丮 ����	: resultArrange(c) tab_idx(c) row_idx(c) [item_idx(n) item_type(n) wear_pos(c) plus(n) flag(n) used(n) used_2(n) count(ll) option_count(c) {(option_type(c) option_level(c)} * option_count] * 5 socketcreatecount(c) socketcount(c) [optionindex(n) optionlevel(c)]
								// ��ĭ�� item_idx�� -1�̰� ���Ĵ� ����, resultArrange ��Ʈ �ʵ�(0��Ʈ-����, 1��Ʈ-��)
								// used_2(n) �� COMPOSITE_TIME ���ø�
	MSG_WEARING,				// ���� ���� ����	: char_index(n) wear_pos(c) item_db_index(n) item_plus(n)

	// ĳ���� ����
	MSG_MOVE,					// �̵�				: chartype(c) movetype(uc) index(n) speed(f) x(f) z(f) h(f) r(f) y(n) map_attr(uc)

	// ���� ����
	MSG_ATTACK,					// ����				: attackchartype(c) attackcharindex(n) targetchartype(c) targetindex(n) attackType(c) multicount(c) multiindex(n:multicount)
	MSG_DAMAGE,					// ������ ����		: attackchartype(c) attackcharindex(n) attackerattacktype(c) targetcount(n) [targetchartypc(c) targetindex(n) hp(n) mp(n) damage(n) flag(c)] * targetcount �ݺ�

	// ä��
	MSG_CHAT,					// ä��				: chat_type(c) sender_index(n) sender_name(str) receiver_name(str) chat(str)

	// ������
	MSG_ITEM,					// ������ ����		: sub_type(uc) ...

	// �ý��� �޽���
	MSG_SYS,					// �ý��� �޽���	: sub_type(uc) ...

	// ���̵�
	MSG_GO_ZONE,				// ���̵�			: zone_no(n) extra(n) ip(str) port(n)
	MSG_GOTO,					// ���� ���� �̵�	: zone_no(n) x(f) z(f) h(f) r(f) y(n)

	// 20
	// ��ȯ
	MSG_EXCHANGE,				// ��ȯ ����		: sub_type(uc) ...

	// ��� ��� ����
	MSG_MEMPOS,					// ��� ��� ����	: sub_type(uc) ...

	// ȯ�� ����
	MSG_ENV,					// ȯ�� ����		: sub_type(uc) ...

	// ��� ���� ����
	MSG_GM,						// ��� ���� ����	: sub_type(uc) ...

	// ��Ƽ ����
	MSG_PARTY,					// ��Ƽ ����		: sub_type(uc) ...

	// Quick Slot ����
	MSG_QUICKSLOT,				// ������ ����		: sub_type(uc) ...

	// �̱۴��� NPC ����
	MSG_NPC_REGEN,				// NPC ���� ����	: index(n) dbIndex(n) x(f) z(f) h(f) r(f) yLayer(int) entityindex(n)

	// ��ų �޽���
	MSG_SKILL,					// ��ų ����		: subtype(uc) ...

	// ����/���� ���� �޽���
	MSG_ASSIST,					// ���� ���� �޽���	: subtype(uc) ...

	// PC ���� �޽���
	MSG_CHAR_STATUS,			// PC ���� �޽���	: chartype(c) inedx(n) hp(n) maxHP(n) mp(n) maxMP(n) pkstate(c) pktitle(c) state(n) state2(n)

	// 30
	// ĳ���� ��Ȱ �޽���
	MSG_PC_REBIRTH,				// pc ��Ȱ �޽���	:

	// ����Ʈ �޽���
	MSG_EFFECT,					// ����Ʈ �޽���	: subtype(uc) ...

	// EXP, SP �޽���
	MSG_EXP_SP,					// EXP,SP ȹ��		: exp(n) sp(n)

	// �׼�
	MSG_ACTION,					// �׼� ���		: charindex(n) type(c) action(n) state(c),
								//						targetcharindex(n) -> #ifdef EVENT_TLD_2007_SONGKRAN �϶��� ����

	// �α伭��
	MSG_LOGINSERV_PLAYER,		// ����ڼ� ����	: recentserver(n) recentsubnum(n) count(n) seqNo(n) serverno(n) subservercount(n) isrecommendserver(c) [subnum(n) playernum(n) ip_addr(str) portno(n)]... subservercount��ŭ �ݺ�

	// ����Ʈ
	MSG_QUEST,					// ����Ʈ ����		: subtype(uc) ...

	// ���� ����Ʈ ���
	MSG_STATPOINT,				// ��������Ʈ ���	: subtype(uc) ...

	// ���� �̵� ����
	MSG_WARP,					// �����̵� ����	: subtype(uc) ...

	// �޽� �˻� ����
	MSG_PULSE,					// �޽� ����		: pulse(n), nationalcodetype(c), tickDelayTime(f)

	// ������ ����
	MSG_RANDOM_PRODUCE,			// ������ ����		: npcindex(n)

	// 40
	// Special Skill ����
	MSG_SSKILL,					// Ư����ų ����	: subtype(uc) .....

	// PK ����
	MSG_PK,						// PK ����			: subtype(uc) ...

	// ��� ����
	MSG_GUILD,					// ��� ����		: subtype(uc) ...

	// �̺�Ʈ ����
	MSG_EVENT,					// �̺�Ʈ ����		: subtype(uc) ...

	// ���λ���
	MSG_PERSONALSHOP,			// ���� ����		: subtype(uc) ...

	// �������
	MSG_RIGHT_ATTACK,			// �������			: subtype(uc) target_type(c) target_index(n) 

	// â��
	MSG_STASH,					// â��				: subtype(uc) ...

	// ����
	MSG_CHANGE,					// ����				: subtype(uc) ...

	// �������̽� �ɼ�
	MSG_UI,						// UI �ɼǰ���		: subtype(uc) ...

	// ���� �ý���
	MSG_TEACH,					// ����				: subtype(uc) ...

	// 50
	// ��������
	MSG_CHANGEJOB,				// ���� ����		: subtype(uc) ...

	MSG_FRIEND,					//�޽��� ����.

	// �۽��� ������ ��Ƽ ���� �� ����(NPC)
	MSG_PD_ATTACK,				//����				: targetchartype(c) targetindex(n) attackType(c) multicount(c) multiindex(n:multicount) 
	MSG_PD_MOVE,				//����				: movetype(uc) speed(f) multicount(c) multiindex(n:multicount) x(f) z(f) h(f) r(f) y(n)

	// ���� ����
	MSG_SELECT_PRODUCE,			// ���� ����		: npc_server_index(n) itemdbindex(n)

	//wooss050817
	// ���� �޽����� ���� �޽����� ���� Ÿ������
	MSG_EXTEND,					// �޽��� Ȯ��(55)		: exmsg(n) ...
								// do_Extend���� Movefirst�� exmsg�� �����Ƿ� ����Ÿ�� ó�� ��ƾ������ MoveFirst�� �ϸ� �ȵ�

	MSG_RECOVER_EXP_SP,			// [2012/08/10 : Sora] ��Ȱ �ֹ��� ���� ������ ����ġ, ���õ� �� ����(56)

	//2013/04/03 jeil ���� ������ ���� 
	MSG_MONEY,					//���� ������ ���� : subtype(uc) ...

#ifdef HP_PERCENTAGE
	MSG_DAMAGE_REAL = 58,
	XXXMSG_MEMPOSPLUS = MSG_DAMAGE_REAL,
#else	//	HP_PERCENTAGE
	XXXMSG_MEMPOSPLUS,	// 55 �����̾� �޸� �� : sub_type(uc) ...
	// ���� Ÿ���� ������ �޸𸮺ϰ� ���� ���
#endif	//	HP_PERCENTAGE 
// [KH_070316] �߰�
	// (�븸)���� 
	MSG_BILLINFO = 60,			// ���� ����		: SUBTYPE(UC) ...

	MSG_TRADEAGENT,				// �ŷ� ����
	
	MSG_EXPEDITION,				// [sora] ������(�߰�) 

	MSG_FACTORY,    // ���� �ý���

	MSG_RAID, // [sora] ���� ����
	MSG_PET_STASH,				// 65
	MSG_RVR,
#ifdef DURABILITY
	MSG_DURABILITY,
#endif	//	DURABILITY
	MSG_GPS,
	MSG_ITEMCOLLECTION,
    MSG_CRAFT,					 //Craft system
	MSG_GUILD_BATTLE,			// ����Ʋ Ȯ��
	MSG_REZA = 71,

	MSG_REBORN,
	MSG_MAIL_BOX, //Dethunter13
	MSG_ARTIFACT,
#ifdef BATTLE_PASS_SYSTEM
	MSG_BATTLE_PASS,
#endif
#ifdef PRESTIGE_SYSTEM
	MSG_PRESTIGE,
#endif

	MSG_AUTO_SETTING,	//Val add new auto igni/pickup to chat
	MSG_HONOR, //dethunter12 add honor point display
#ifdef PASSIVE_SYSTEM
	MSG_PASSIVE_SYSTEM,  //new 16-08-2022
#endif
#ifdef PREMIUM_CHAR
	MSG_PREMIUM_CHAR = 95,
#endif
	MSG_UPDATE_DATA_FOR_CLIENT = 96,

	MSG_RESERVED_GM_COMMAND = 97,	// Calendar �̺�Ʈ ���� ��Ŷ.
	MSG_TIMER_ITEM = 98,

	MSG_EXPRESS_SYSTEM = 99,	// â��NPC (Express system)�� ��Ŷ�� ó���ϴ� �κ�
	//MSG_NPC_PORTAL_SCROLL,

	MSG_CASHEXCHANGE = 100,		// Cash exchange system (list/buy/sell cash)

	MSG_MAX,

// ���� �޼����� Ŭ���̾�Ʈ�� ��� �޼���
/* //0522 kwon  ����.
  // broadcast requesting server infos
  MSG_REQ_ENUMSERVERS,
  MSG_SERVERINFO,

  MSG_KEEPALIVE,  // sent when there's nothing else to send - just to keep connections valid

  // disconnection explanation from server
  MSG_INF_DISCONNECTED,
	
  // info message with pings of all players
  MSG_INF_PINGS,
*/
  // main session state connecting to server
  MSG_REQ_CONNECTLOCALSESSIONSTATE = 50,
  MSG_REP_CONNECTLOCALSESSIONSTATE,
/* //0522 kwon ����.
  // remote session state connecting to server
  MSG_REQ_CONNECTREMOTESESSIONSTATE,
  MSG_REP_CONNECTREMOTESESSIONSTATE,

  // remote session requesting full game state info from server
  MSG_REQ_GAMESTATE,
  MSG_REP_GAMESTATE,

  // client initialing CRC check
  MSG_REQ_CRCLIST,
  MSG_REQ_CRCCHECK,
  MSG_REP_CRCCHECK,
*/
  // player connecting to server
  MSG_REQ_CONNECTPLAYER,
  MSG_REP_CONNECTPLAYER,
/* //0522 kwon ����.
  MSG_REQ_PAUSE,  // request pause/unpause game
*/
  // request character change for a player
  MSG_REQ_CHARACTERCHANGE,

  // action packet from client to server
  MSG_ACTIONS,
/* //0522 kwon ����.
  // data to check for lost synchronization (client to server) - NO LONGER USED
  MSG_SYNCCHECK,     
  // a copy of action stored for prediction
  MSG_ACTIONPREDICT,
*/
  // sequenced packets from server to session states
  MSG_SEQ_ALLACTIONS,    // packed actions of all players from server to clients
/* //0522 kwon ����.
  MSG_SEQ_ADDPLAYER,     // instructions for adding a new player to session states
  MSG_SEQ_REMPLAYER,     // instructions for removing a new player from session states
  MSG_SEQ_PAUSE,         // game was paused/unpaused
*/
  MSG_SEQ_CHARACTERCHANGE, // a player has changed character

  MSG_GAMESTREAMBLOCKS,         // packet with one or more game stream messages
  MSG_REQUESTGAMESTREAMRESEND,  // request for resend of a game stream message

  
/* //0522 kwon ����.
  // chat messages
  MSG_CHAT_IN,    // chat request from client to server
  MSG_CHAT_OUT,   // chat message routed to certain clients

  // parameter setting messages
  MSG_SET_CLIENTSETTINGS,     // adjust server side settings of a client

  // remote administration 
  MSG_ADMIN_COMMAND,     // c2s incoming console command request
  MSG_ADMIN_RESPONSE,    // s2c results of the console command

  MSG_EXTRA = '/',      // used for special communications like rcon and similar


  // added to the end so that it would not mess up old numbering - that would corrupt demo playing
  // disconnection confirmation from the client
	MSG_REP_DISCONNECTED,

 //0522 kwon ����.
  // server/client messages
  MSG_TICK_DATA,         // incoming server tick data (client side)
  MSG_TICK_ACKNOWLEDGE,  // incoming tick acknowledge (server side)
  
  MSG_CHANGE_LEVEL,      // server order to clients to change level played
*/
//0322 kwon
/*
  MSG_MOB_CREATE,  //52
  MSG_MOB_MOVE,  //53
  MSG_MOB_ANI, //54
  MSG_PLAYER_ADD, //55
  MSG_PLAYER_MOVE, //56
  MSG_PLAYER_INDEX, //57
  MSG_PLAYER_ATTACK, //58
  //MSG_PLAYER_STOP, //59
  MSG_MOB_STATUS, //0421 kwon
  MSG_PLAYER_DEL,//60

  MSG_MOB_DEL,//61
  MSG_MOB_DIE,//62
  MSG_SERVER_TEST,//63
*/	
	MSG_END

} MESSAGETYPE;

// Cash Exchange Message Subtypes
typedef enum __tagMsgCashExchangeType
{
	MSG_CASHEXCHANGE_CREATE_LISTING = 1,
	MSG_CASHEXCHANGE_BUY_LISTING = 2,
	MSG_CASHEXCHANGE_LIST_REQUEST = 3,
	MSG_CASHEXCHANGE_CANCEL_LISTING = 4,
	MSG_CASHEXCHANGE_CREATE_LISTING_RESULT = 1,
	MSG_CASHEXCHANGE_BUY_LISTING_RESULT = 2,
	MSG_CASHEXCHANGE_LIST_RESPONSE = 3,
	MSG_CASHEXCHANGE_CANCEL_LISTING_RESULT = 4,
} MSG_CASHEXCHANGE_TYPE;

#ifdef PROMO_KEY_03312023
typedef enum __tagMsgPromoKeyType
{
	MSG_PROMO_KEY_USE,
	MSG_PROMO_KEY_NO_SPACE,
	MSG_PROMO_KEY_ALREADY_USED,
}MSG_PROMO_TYPE;
#endif

typedef enum __tagMsgArctifactType
{
	MSG_ARTIFACT_GENERAL,
	MSG_ARTIFACT_DEBUG_ON,
	MSG_ARTIFACT_DEBUG_OFF,
	MSG_ARTIFACT_ARTIFACT_NOTICE_3MIN,
	MSG_ARTIFACT_ARTIFACT_NOTICE_1MIN,
	MSG_ARTIFACT_ARTIFACT_NOTICE_TIMEOUT,
	MSG_ARTIFACT_ARTIFACT_NOTICE_REMAINING,
} MSG_ARTIFACT_TYPE;

#ifdef BATTLE_PASS_SYSTEM
typedef enum _tagBattlePassType
{
	MSG_BATTLE_PASS_REQ,
	MSG_BATTLE_PASS_REP,
	MSG_BATTLE_PASS_INFO_REQ,
	MSG_BATTLE_PASS_INFO_REP,
	MSG_BATTLE_PASS_ERROR_LIMIT,
	MSG_BATTLE_PASS_LEVEL_UP,
	MSG_BATTLE_PASS_ERROR_EXP_NEEDED,
	MSG_BATTLE_PASS_ERROR_NOT_EXIST_NPC,
	MSG_BATTLE_PASS_ERROR_NOCONDITION_LEVEL,
	MSG_BATTLE_PASS_ERROR_EMPTY_SLOT,
} MSG_BATTLE_PASS_TYPE;
#endif

// ���̵� ����
typedef enum __tagMsgRaidType
{
	MSG_RAID_ERROR,							// ����

	MSG_RAID_INZONE_JOIN,					// ���� �� 
	MSG_RAID_INZONE_QUIT,					// ���� ����
}MSG_RAID_TYPE;

typedef enum __tagMsgRaidInzoneMisCompleteType
{
	MSG_RAID_INZONE_MISCLEAR_INCOMPLETE,	// ���� �̼� Ŭ���� �̿Ϸ�
	MSG_RAID_INZONE_MISCLEAR_COMPLETE,		// ���� �̼� Ŭ���� �Ϸ�
}MSG_RAID_INZONE_MISCOMPLETE_TYPE;


//���̵� ����
typedef enum __tagMsgRaidErrorType
{
	MSG_RAID_ERROR_SUCESS=0,       // ����
	MSG_RAID_ERROR_INZONE_JOIN_CLEAR_COMPLETE,   // ���� ���� �Ұ�(���� Ŭ���� �Ϸ�) - %�� %�� �ڿ� ���尡��
	MSG_RAID_ERROR_INZONE_JOIN_ROOMCOUNT_FULL,   // ���� �ν��Ͻ� �ʹ� ���� ���̻� ���� �Ұ�
	MSG_RAID_ERROR_INZONE_JOIN_ALREADY,     // ���� �̹� �α��� 
	MSG_RAID_ERROR_INZONE_JOIN_MEMBER_FULL,    // ���� ���� ������ �ִ� �ο��� �ʰ�
	MSG_RAID_ERROR_INZONE_JOIN_ALREADY_OTHERTEAM,  // �ش� ���� �ٸ� ��Ƽ,�����밡 �ֽ��ϴ�.
	MSG_RAID_ERROR_INZONE_JOIN_THISZONE_PARTYZONE,  // ��Ƽ ���¿����� ���� ���� �մϴ�
	MSG_RAID_ERROR_INZONE_JOIN_THISZONE_EXPEDZONE,  // ������ ���¿����� ���� ���� �մϴ�  
	MSG_RAID_ERROR_INZONE_JOIN_NOTJOIN_PARTYOREXPED, // ��Ƽ�� �����뿡 ���� �Ǿ�  ���� ����
	MSG_RAID_ERROR_INZONE_QUIT_NOTINZONEJOINED,   // �ش� ������ ���� ���� �ʾ��� 
	MSG_RAID_ERROR_INZONE_NOT_5MIN_GETBOX,    // �� �̻� ���� �ֿ� �� ����(ȹ�� �ð� 5��) 
	MSG_RAID_ERROR_INZONE_ALREADY_GETBOX,    // ������ ���� ���� ���� �ϰ� �ٽ� �õ�
	MSG_RAID_ERROR_INZONE_JOIN_INVALIDELEVEL,			// ���� �������� �����Ҽ� ����
	MSG_RAID_ERROR_INZONE_JOIN_NOTSAMEBOSSROOMNO,		// �ͼӵ� ���� ������ �������� �޶� ���� �Ұ� (�߰� ���� �޼���)
	MSG_RAID_ERROR_INZONE_NOT_EXPED_RAID_SUBNUMBER,		// ������ ������ ���̵� ä���� �ƴ϶� ���� �Ұ�
	MSG_RAID_ERROR_INZONE_NOT_JOIN_BOSS,				// ���������� ���� ���̵忡 �������� �ʾҴ�.
	MSG_RAID_ERROR_INZONE_INVALID_DIFFICULTY,			// ���� ������ ���̵��� �����Ϸ��� ���̵��� Ʋ��.
	MSG_RAID_ERROR_INZONE_INIT_TIME,       // (17) ���̵� ���� �ʱ�ȭ ���Դϴ�.\n ����� �ٽ� �õ��Ͽ� �ֽʽÿ�.(���� �õ��� �޽��� �ڽ�)
	MSG_RAID_ERROR_INZONE_NOT_QUEST,		// 18 ���̵� ���� �������� ���� : ����Ʈ �̼���
	MSG_RAID_ERROR_INZONE_NOT_FOUND_ZONE_INFO,			// �ν��Ͻ� �� ������ ã�� �� ����

}MSG_RAID_ERROR_TYPE;

//////////////////////////////////////////////////////////////////////////
//  [sora] ������ ����
//////////////////////////////////////////////////////////////////////////
typedef enum _tagMsgExpedType			//������ ���� �޼��� 
{
	MSG_EXPED_ERROR,						// ����
	
	MSG_CREATE_REQ,							// ������ ����(��Ƽ��ȯ) ��û			
	MSG_CREATE_REP,							// ������ ����(��Ƽ��ȯ) ����	

	MSG_INVITE_REQ,							// �ʴ� ��û
	MSG_INVITE_REP,							// �ʴ� ����

	MSG_EXPED_ADD,							// ĳ�� �߰� 
	MSG_EXPED_MEMBER_INFO,					// ��� ����

	MSG_ALLOW_REQ,							// �ʴ� ����
	MSG_ALLOW_REP,							// �ʴ� ����

	MSG_REJECT_REQ,							// �ʴ� �ź� ��û
	MSG_REJECT_DEST,						// �Ź�	
	MSG_REJECT_SRC,

	MSG_QUIT_REQ,							// Ż�� ��û
	MSG_QUIT_REP,							// Ż�� ����

	MSG_ENDEXPED_REQ,						// ������ ��ü
	MSG_ENDEXPED_START,      // ������ ��ü ���� �˸�(20�� �Ŀ�) (�߰�)
	MSG_ENDEXPED_REP,						// ������ ��ü	

	MSG_KICK_REQ,							// �߹� ��û
	MSG_KICK_REP,							// �߹� ����

	MSG_CHANGETYPE_REQ,						// ������ Ÿ�� ����(����ġ, ����, �Ϲ� ������, ����� ������ �й� ���)
	MSG_CHANGETYPE_REP,		

	MSG_MEMBERINFO_REQ,						// ������ ���(U.I)
	MSG_MEMBERINFO_REP,		

	MSG_ADMIN_REQ,							// ������ ����(U.I)
	MSG_ADMIN_REP,

	MSG_CHANGEBOSS_REQ,						// ���� ���� ����(����)
	MSG_CHANGEBOSS_REP,						// ���� ���� ����

	MSG_SETMBOSS_REQ,						// �δ��� �Ӹ�
	MSG_SETMBOSS_REP,

	MSG_RESETMBOSS_REQ,						// �δ��� �Ӹ� ����
	MSG_RESETMBOSS_REP,	

	MSG_MOVEGROUP_REQ,						// �׷� �̵� 
	MSG_MOVEGROUP_REP,						

	MSG_ADDMEMBER_REQ,						// ��� �߰�
	MSG_ADDMEMBER_REP,

	MSG_VIEWDETAIL_REQ,						// ���캸��
	MSG_VIEWDETAIL_INVEN,					// �κ�����
	MSG_VIEWDETAIL_PET,						// ������
	MSG_VIEWDETAIL_APET,					// ������
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	MSG_PARTYDUNGEON_JOIN,                    //Cloud Expedition_Party_Dungeon
	MSG_PARTYDUNGEON_JOIN_MEMBER,             //Cloud Expedition_Party_Dungeon
	MSG_PARTYDUNGEON_RECALL_REQ,              //Cloud Expedition_Party_Dungeon
	MSG_PARTYDUNGEON_RECALL_RECV,             //Cloud Expedition_Party_Dungeon
	MSG_PARTYDUNGEON_REWARD,                  //Cloud Expedition_Party_Dungeon
#ifdef CLOUD_EXPEDITION_REWORK
	MSG_PARTYDUNGEON_DETAIL,
	MSG_PARTYDUNGEON_SEND,
#endif
#endif
	MSG_SET_LABEL_REQ,						// ǥ�� ����
	MSG_SET_LABEL_REP,

	MSG_EXPED_TYPEINFO,						// ������ Ÿ�� ����

	MSG_QUESTITEM_CHECK_REQ,				//�߰�(Ŭ���̾�Ʈ���� ������ ����Ʈ������ �˻� ��û
	MSG_GET_QUESTITEM_SUCCESS_REP,			//���������� ����Ʈ�������� �˻��Ͽ� ���������� ����
	MSG_GET_QUESTITEM_FAILED_REP,			//���������� ����Ʈ�������� �˻����� ����.

	MSG_EXPED_ADD_SYSMSG,					// [110609 selo] ������� �߰� SysMSG

	MSG_EXPEND_OFFLINE,						// ������ �������� //���������� ��
} MSG_EXPEDITION_TYPE;
 //Craft system
typedef enum _tagMsgCraftType
{
	MSG_CRAFT_NOT_MONEY,
	MSG_CRAFT_NOT_ITEM,
	MSG_CRAFT_NOT_ENOUGHT_ITEM,
	MSG_CRAFT_ERROR,
	MSG_CRAFT_ITEM,
} MSG_Craft_TYPE;
typedef enum __tagMsgExpedSetLabelIndex	// [sora] ǥ�� 
{
	MSG_EXPED_SETLABEL_INDEX_1,			// ����
	MSG_EXPED_SETLABEL_INDEX_2,			// ���� 
	MSG_EXPED_SETLABEL_INDEX_3,			// �߹ٴ� 
	MSG_EXPED_SETLABEL_INDEX_4,			// ����Į
	MSG_EXPED_SETLABEL_INDEX_5,			// �� 
	MSG_EXPED_SETLABEL_INDEX_6,			// �Ǹ� 
	MSG_EXPED_SETLABEL_INDEX_7,			// �ذ�	
}MSG_EXPEDITION_SETLABEL_INDEX;

typedef enum __tagMsgExpedSetLabelType	// [sora] ��� Ÿ��
{
	MSG_EXPED_SETLABEL_TYPE_PC,			
	MSG_EXPED_SETLABEL_TYPE_NPC,		
}MSG_EXPEDITION_SETLABEL_TYPE;

typedef enum __tagMsgExpedSetLabelMode	 // [sora] ���� Ÿ��
{
	MSG_EXPED_SETLABEL_MODE_SET,			
	MSG_EXPED_SETLABEL_MODE_RESET,		
}MSG_EXPEDITION_SETLABEL_MODE;



// [sora] ������ ����(��ȯ ���� ���� �޼��� �߰�)
typedef enum __tagMsgExpedErrorType
{
	MSG_EXPED_ERROR_NORMAL,     // �Ϲ�

	MSG_EXPED_ERROR_ALREADY_REQUEST,  // �ٸ� ������� �̹� ��û ��

	MSG_EXPED_ERROR_ALLOW_OK,    // �ʴ� ���� ����(������ ���� �޼���)  
	MSG_EXPED_ERROR_ALLOW_NOT_EXPED,      // ����(������ ���� �޼���)  

	MSG_EXPED_ERROR_REJECT_OK,    // ���� ����(������ ����)  
	MSG_EXPED_ERROR_REJECT_FAIL,   // ���� ����(������ ����)

	MSG_EXPED_ERROR_QUIT_OK,    // Ż�� ����(������ ���� �޼���)  
	MSG_EXPED_ERROR_QUIT_END,    // Ż�� ����, ������ ��ü(������ ���� �޼���)  

	MSG_EXPED_ERROR_KICK_OK,    // ���� ����(������ ���� �޼���)  
	MSG_EXPED_ERROR_KICK_END,    // ���� ����, ������ (������ ���� �޼���)  

	MSG_EXPED_ERROR_INVITE_PVP,    // ��û�ڳ� ����ڰ� PVP ��
	MSG_EXPED_ERROR_NOT_PARTY,    // ��Ƽ�� �Ҽӵ��� ����(��Ƽ ��ȯ �Ұ�)
	MSG_EXPED_ERROR_NOT_EXPED,    // ������ �Ҽӵ��� ����
	MSG_EXPED_ERROR_NOT_PARTYBOSS,   // ��Ƽ���� �ƴϴ�. (��Ƽ��ȯ �Ұ�) 
	MSG_EXPED_ERROR_NOT_EXPEDBOSS,   // ���������� �ƴϴ�.
	MSG_EXPED_ERROR_ALREADY_JOIN_ME,  // �̹� �����뿡 �ҼӵǾ� ����
	MSG_EXPED_ERROR_ALREADY_JOIN_OTHER,  // �ٸ� �����뿡 �ҼӵǾ� ����
	MSG_EXPED_ERROR_NOT_BE_CHAR,   // ���� ĳ���� 
	MSG_EXPED_ERROR_FULL_EXPED,    // �� �̻� ������� �߰��� �� ����) 
	MSG_EXPED_ERROR_INVALID_LEVEL,   // ������ ���� ����
	MSG_EXPED_ERROR_CREATE_INVALIDZONE,  // ������ ��ȯ ���� ������ �ƴմϴ�.
	MSG_EXPED_ERROR_SETLABEL_NOTINZONE,  // ���� ���ΰ� �ƴϾ ǥ�� ���� �Ұ�.
	MSG_EXPED_ERROR_EXIST_LOGOUT_MEMBER, // �������� ����� ����
}MSG_EXPEDITION_ERROR_TYPE;

// [sora] ������ �׷� Ÿ�� 
typedef enum _tagMsgExpedGroupType
{
	MSG_EXPED_GROUP_1,						// �׷� 1
	MSG_EXPED_GROUP_2,						// �׷� 2	
	MSG_EXPED_GROUP_3,						// �׷� 3
	MSG_EXPED_GROUP_4,						// �׷� 4

	MSG_EXPED_GROUP_COUNT,

} MSG_EXPED_GROUP_TYPE;

// [sora] ������ ������ Ÿ��
typedef enum _tagMsgExpedMemberType
{
	MSG_EXPED_MEMBERTYPE_BOSS,				// ���� ���� 
	MSG_EXPED_MEMBERTYPE_MBOSS,				// ���� �δ���
	MSG_EXPED_MEMBERTYPE_NORMAL,			// ���� ���
	
	MSG_EXPED_MEMBERTYPE_COUNT,
}MSG_EXPED_MEMBER_TYPE;

// [sora] ������ ����,������ Ż�� Ÿ��
typedef enum _tagMsgExpedQuitMode
{
	MSG_EXPED_QUITMODE_NORMAL,				// ���� ���� 
	MSG_EXPED_QUITMODE_UNUSUAL,				// ������ ����
}MSG_EXPED_QUIT_MODE;

// [sora] ���� ����(����,�ڵ�) ���
typedef enum _tagMsgExpedChangeBossMode
{
	MSG_EXPED_CHANGEBOSS_MANUAL,			// ���� ����
	MSG_EXPED_CHANGEBOSS_AUTO,				// �ڵ� ����
}MSG_EXPED_CHANGEBOSS_MODE;

// [sora] �й���
typedef enum _tagMsgDiviType
{
    MSG_DIVITYPE_EXP=0,      // �й� ���(����ġ)
    MSG_DIVITYPE_ITEM,        // �й� ���(������)
	MSG_DIVITYPE_SPECIAL,        // �й� ���(����� ������)
}MSG_DIVI_TYPE;

typedef enum _tagMsgExpedDiviStyle // [sora]�й� ��� (��Ƽ ������ ���� ���)
{
  MSG_EXPED_TYPE_RANDOM=0,   // �յ� ��Ƽ
  MSG_EXPED_TYPE_FIRSTGET,  // �Լ� �켱
  MSG_EXPED_TYPE_BATTLE,   // ������
  MSG_EXPED_TYPE_OPENBOX,   // ���ڿ���
}MSG_EXPED_DIVISTYLE;

// [sora] ��Ƽ Ÿ�� ���� ���
typedef enum _tagMsgPartySetAllOneType
{
  MSG_PARTY_SETALLONE_ALL=1,   // ��Ƽ Ÿ�� ���� ALL(��ü ��Ƽ ���)  
  MSG_PARTY_SETALLONE_ONE,   // ��Ƽ Ÿ�� ���� ONE
}MSG_PARTY_SETALLONE_TYPE;

//////////////////////////////////////////////////////////////////////////

typedef enum __tagMsgTradeAgentAlignType	// ����Ʈ ���� Ÿ��
{	
	MSG_TRADEAGENT_ALIGN_NAME_ASC,			// ������ �̸�(���� ����)
	MSG_TRADEAGENT_ALIGN_NAME_DESC,			// ������ �̸�(���� ����)

	MSG_TRADEAGENT_ALIGN_QUANTITY_ASC,		// ���� (���� ����)
	MSG_TRADEAGENT_ALIGN_QUANTITY_DESC,		// ���� (���� ����)

	MSG_TRADEAGENT_ALIGN_TOTALMONEY_ASC,	// �ѱݾ� (���� ����)
	MSG_TRADEAGENT_ALIGN_TOTALMONEY_DESC,	// �ѱݾ� (���� ����)

	MSG_TRADEAGENT_ALIGN_LEVEL_ASC,			// ���� (���� ����)
	MSG_TRADEAGENT_ALIGN_LEVEL_DESC,		// ���� (���� ����)
}MSG_TRADEAGENT_ALIGN_TYPE;

typedef enum __tagMsgTradeAgentErrorType
{
	MSG_TRADEAGENT_ERROR_NORMAL,    // �Ϲ��� ����
	MSG_TRADEAGENT_ERROR_NOT_TRADEITEM,   // �ŷ� �Ұ� ������
	MSG_TRADEAGENT_ERROR_NOT_ITEMCOUNT,   // ������ ���� ����Ȯ 
	MSG_TRADEAGENT_ERROR_NOT_SELL_TOTALMONEY, // �Ǹ� �� �ݾ� ����Ȯ
	MSG_TRADEAGENT_ERROR_NOT_ENUGH_GUARANTY, // ������ ����

	MSG_TRADEAGENT_ERROR_NOT_ENUGH_MONEY,  // ������(����) ����
	MSG_TRADEAGENT_ERROR_ALREADY_SELLITEM,  // �̹� �ĸŵ� ������
	MSG_TRADEAGENT_ERROR_FULL_INVENTORY,  // �κ��丮�� ���� ��(���� �Ұ�)
	MSG_TRADEAGENT_ERROR_NOT_BE_ITEM,   // �������� ����
	MSG_TRADEAGENT_ERROR_MAXREGCOUNT_FULL,  // �ִ� ��� �� �ʰ�
	MSG_TRADEAGENT_ERROR_CHAR_MAXREGCOUNT_FULL , // ĳ���ʹ� �ִ� ��� �� �ʰ�
	MSG_TRADEAGENT_ERROR_CALCULATE_ING_NOCALC,	// ���� ���� ó�����̶� û�� �Ҽ� ����(���� ���� ó����)
}MSG_TRADEAGENT_ERROR_TYPE;

typedef enum __tagMsgTradeAgentErrorPart
{
	MSG_TRADEAGENT_ERROR_PART_SEARCH,   // ���� ��Ʈ: ��ȸ
	MSG_TRADEAGENT_ERROR_PART_REGIST,   // ���� ��Ʈ: ��� 
	MSG_TRADEAGENT_ERROR_PART_CALCULATE, // ���� ��Ʈ: ����
	MSG_TRADEAGENT_ERROR_PART_BUY,    // ���� ��Ʈ: ����
	MSG_TRADEAGENT_ERROR_PART_SELLCANCEL, // ���� ��Ʈ: ��� ��� 
}MSG_TRADEAGENT_ERROR_PART;

typedef enum __tagMsgTradeAgentStateType		// ��ǰ ����
{	
	MSG_TRADEAGENT_STATE_SELL_BEFORE,			// �Ǹ� �� 
	MSG_TRADEAGENT_STATE_SELL_COMPLETE,			// �Ǹ� �Ϸ�
	MSG_TRADEAGENT_STATE_SELL_RETURNED,			// �Ǹ� ���� ����(�ݼ�)
	MSG_TRADEAGENT_STATE_CALCULATE_COMPLETE,	// ���� �Ͽ���
	MSG_TRADEAGENT_STATE_CALCULATE_OVERTIME,	// ���� ���� �ʰ�
	MSG_TRADEAGENT_STATE_BUY,			        // ����
}MSG_TRADEAGENT_STATE_TYPE;

typedef enum __tagMsgTradeAgentFinishDayType	// ��ǰ ������ ���� 
{	
	MSG_TRADEAGENT_FINISH_DAY,					// ��
	MSG_TRADEAGENT_FINISH_HOUR,					// �ð�
	MSG_TRADEAGENT_FINISH_MIN,					// ��
}MSG_TRADEAGENT_FINISHDAY_TYPE;


// wooss 050817
// MSG_EXTEND
typedef enum __tagMsgExtendType
{
	MSG_EX_PET_STATUS,			// �ֿϵ��� ����	: index(n) petTypeGrade(c) level(n) exp(ll) needexp(ll) hp(n) maxhp(n) ability(n) hungry(n) maxhugry(n) sympathy(n) maxsympathy(n) x(f) z(f) h(f) r(f) y(n) mapatt(uc) remainRebirth(n)
								// Ŭ���̾�Ʈ ����Ʈ�� �ش� ���� ������ �߰� ������ ������Ʈ �ϵ��� �� ��
	MSG_EX_PET_CALL,			// �ֿϵչ� ȣ��	: index(n)
								// Client->Server
	MSG_EX_PET_MOUNT,			// �ֿϵ����� Ÿ��	: owner_index(n) mountPetTypeGrade(c)
								// Server->Client
	MSG_EX_PET_LEARN,			// �� ����			: skillindex(n) level(c:server) errorcode(n:server)
	MSG_EX_PET_SKILLLIST,		// �� ��ų ����Ʈ	: index(n) count(n) [skillindex(n) skilllevel(c)] ...
	MSG_EX_PET_RESET_SKILL,		// �� ��ų �ʱ�ȭ
	MSG_EX_PET_SELL_INFO,		// �� ��ȯ/�Ǹ� ����: ownerindex(n) petindex(n) petTypeGrade(c) level(n) exp(ll) needexp(ll) hp(n) maxhp(n) ability(n) hungry(n) maxhugry(n) sympathy(n) maxsympathy(n) remainRebirth(n)
	MSG_EX_PET_CHANGE_MOUNT,	// �� Ÿ�� ����		: errorcode(n:server)
	//<--�߰�
	//wooss 050926 
	MSG_EX_NAMECHANGE,			// �̸� ����c->s	: item_idx(n) name(str)
								//			s->c	: errorcode(c) name(str) bguild(c)
	MSG_EX_CASHITEM,			// ������ ����		: subtype(uc) ...
	MSG_EX_PET_COMMAND,			// �� �米����		: pet_index(n) command_skill_index(n) targettype(c) targetindex(n)
	MSG_EX_PET_MIX_ITEM,		// �� �̾��� ����	: 
								// Client->Server	: itemdbindex(n), method(n)
								// Server->Client	: errcode(n)
	MSG_EX_FRIENDNAMECHANGE,	// �̸����濡 ���� �޽��� �̸� ���� s->c : charindex(n) name(str)
	MSG_EX_PET_LEVELUP,			// �� ������		: petindex(n) typegrade(c) level(n)
	MSG_EX_PET_WARPTOWN,		// ������ ��ȯ		: 

	MSG_EX_CASTLE_MAP_RECENT,	// ������ �ֱ� ����	: lord_x(f) lord_z(f) lord_hp(n) lord_maxhp(n) tower_count(n) [tower_dbindex(n) tower_x(f) tower_z(f) tower_hp(n) tower_maxhp(n)]*count regen_x(f) regen_z(f) signal_sender_flag(n) signal_sender_index(n) signal_x(f) signal_z(f)
								// Ŭ���̾�Ʈ���� �������� �޽��� Ÿ�Ը�
								// sender_flag �� MSG_GUILD_POSITION_TYPE
	MSG_EX_CASTLE_MAP_SIGNAL,	// ������ �ñ׳�	: x(f) z(f) sender_flag(n:server) sender_index(n:server)

	MSG_EX_ELEMENTAL_STATUS,	// ��ȯ�� ����		: index(n) elementaltype(c) remain(n) hp(n) maxhp(n) attackspeed(c) magicspeed(c) skillspeed(n) walkspeed(f) runspeed(f) attackrange(f) x(f) z(f) h(f) r(f) ylayer(c) mapattr(uc) assist_state(n) assist_count(c) [itemidx(n) index(n) level(c) remain(n)]:count
	MSG_EX_ELEMENTAL_DELETE,	// ��ȯ�� ����		: index(n)

	MSG_EX_EVOCATION_START,		// ���� ����		: charindex(n) type(c)
	MSG_EX_EVOCATION_STOP,		// 20 ���� ��			: charindex(n)

	MSG_EX_GUILDMEMBERNAMECHANGE,// �̸����濡 ���� ��������� �̸� ���� s->c : charindex(n) name(str)

	MSG_EX_KEYCHANGE,			// ��ȣŰ ����		: key(unsigned int)

	MSG_EX_PET_CHANGE_ITEM,		// �� ������ ��ȯ	: errorcode(n:server)

	MSG_EX_PET_REBIRTH,			// �� ���� ����		: pet_index(n) errcode(n:server)

	MSG_EX_PARTY_RECALL,		// ��Ƽ ����		: subtype(n) ... 060306 wooss
	
	MSG_EX_PARTY_MATCH,			// ��Ƽ ��Ī		: subtype(n) ... // Date : 2006-05-09(���� 5:03:37), By eons
	
	MSG_EX_STRING,				// Ŭ���̾�Ʈ �޼������ : outputtype(uc) stringIndex(n) argcount(n) argtype(n) arg
								// GS->C�� ���Ҷ��� : 
	MSG_EX_MESSENGER,			// �޽��� �߰� ��� : subtype(c)
	
	MSG_EX_HAIR_CHANGE,			// ��� ���� �޽��� : charindex(n) hairstyle(c)

	MSG_EX_PLAYER_STATE_CHANGE, // �÷��̾� ���� ���� : charindex(n) state(n)

	MSG_EX_PLAYER_REALIP,			// User real IP ���� : user_ip(s)

	MSG_EX_MEMPOSPLUS,			// �����̾� �޸� �� : sub_type(uc) ...									

	MSG_EX_NPROTECT,			// NPROTECT ���� �޽��� : gg_auth_index(n) gg_auth_val1(n) gg_auth_val2(n) gg_auth_val3(n)

	MSG_EX_PET_CHANGE_NAME,		// �� �̸� ���� : pet_index(n), name(str)
	MSG_EX_PET_CHANGE_COLOR,		// �� ����  ���� : pet_index(n), color( c );

	MSG_EX_GO_ZONE,				// �� �̵���� �߰� ��� : subtype(c) ...
	
	MSG_EX_CASTLE_WAR,			// ���ź ���� : subtype(uc) ...

	MSG_EX_SECURE_CARD,			// ȫ�� ���� ī�� : gs->cl s1(c), s2(c), s3(c), s4(c)   cl->gs s1(c), s2(c), s3(c), s4(c)

	MSG_EX_DVD,					// ���ź ���� ���� : subtype(uc), subsubtype(uc)...

	MSG_EX_ALTERNATE_MERCHANT,	// �븮 ���� : subtype( uc ) ....

	MSG_EX_PET_TURNTO_NPC,		// (int)(nPetIndex, nToNPC, nOwnerCharIndex )
	
	MSG_EX_MONSTERCOMBO,		// ���� �޺�
	
	MSG_EX_RESTART,				// Connector �� �ӽ��н����� ����� �α׾ƿ� ��� 15�ʸ� ������ Ŭ���̾�Ʈ�� Connection ����

	MSG_EX_CHAOSBALL,			//ī���� �� ��ȯ : row(n), col(n)
	
	MSG_EX_UPDATE_PLAYTIME,		// Client���� 10�� �������� PLAYTME ���� ��û

	MSG_EX_ATTACK_PET,			// attack pet ���� (c)subtype

	MSG_EX_EXTREME_CUBE,		//�ͽ�Ʈ�� ť�� ����

	MSG_EX_INIT_SSKILL,  // Ư����ų�ʱ�ȭ

	MSG_EX_DISCONNECT_HACK_CHARACTER,	// �� ���� ���� : 
	
	MSG_EX_TRIGGER_EVENT,		// Ʈ���� �̺�Ʈ �ý���

	MSG_EX_AFFINITY,			// ����

	MSG_EX_TUTORIAL,			// Ʃ�丮�� �ý���
	
	MSG_EX_LOADING_END,			// �ε��� �����κ��� �޴� �޽����� ���� �����ϴ� �κ�.	

	MSG_EX_RAID_INFO,			// �ͼӵ� �� ���� ǥ��

	MSG_EX_NPC_PORTAL_SCROLL,		// connie [2009/9/8] - NPC ã�� 
	
	MSG_EX_LUCKYDRAW_BOX,

	MSG_EX_TITLE_SYSTEM,			// ȣĪ

	MSG_EX_TAKE_AGAIN_QUEST_ITEM,	// [100208: selo] ����Ʈ ������ �ٽ� �ޱ�
	
	MSG_EX_LACARETTE,				// [100324 : sora] ��ī�� �ý���

	MSG_EX_COSTUME2,				// [100421 : kiny8216]�ڽ�Ƭ2 �ý���
	
	MSG_EX_DUNGEONTIME,				// ���� Ÿ��

	MSG_EX_SOCKET,					// socket system. [4/8/2010 rumist]
	
	MSG_EX_ATTENDANCE_EXP_SYSTEM,	// �⼮ �ý��� : �����⼮�ϼ�������ġREQ : (c)subtype 0:Ȯ��, 1:��������ޱ�/ REP (c) subtype 0:��������1:Ȯ��2:�⼮�Ϸ�3:����d������(n)accCount ������, (c)upExp �߰�����ġ

	MSG_EX_XTRAP,
	
	MSG_EX_TUTORIAL_RENEWER_2010,	// Ʃ�丮�� ����
	
	MSG_EX_RAID_SCENE,				// ��ĭ��� ���̵�

	MSG_EX_SUBJOB,					// [2010/08/25 : Sora] ADD_SUBJOB ��������(����ĳ��)
	
	MSG_EX_CASTLLAN,				// ���� �ڽ�Ƭ ����
	
	MSG_EX_MONSTER_MERCENARY,		// ���� �뺴 ���� ��Ŷ
	
	MSG_EX_FACEOFF,						// ��� �� �� ��ü
	
	MSG_EX_RANKING_SYSTEM,			// [selo: 101104] ��ŷ �ý���	

	MSG_EX_MSGBOX,					// [selo: 110104] �޽��� �ڽ�

	MSG_EX_LCBALL,					// lacaball system [1/11/2011 rumist]

	MSG_EX_ROYAL_RUMBLE,			// royal rumble [4/19/2011 rumist]

	MSG_EX_CASH_AUTHENTICATION_CODE, // ���̰���û ���� ������ ������ ���� AUTHENTICATION_CODE ����

	MSG_EX_TREASURE_MAP_SYSTEM_KEY_EXCHANGE, // ���̰� ��û : 100���� ��������Ű�� Ȳ�ݿ���Ű 1���� ��ȯ.

	MSG_EX_RANKING_SYSTEM_EX,		// ��ŷ �ý��� ���� : [trylord 110817]

	MSG_EX_PKPENALTY_REFORM,				 // REFORM_PK_PENALTY_201108

	MSG_EX_SHUTDOWN,				// �˴ٿ� �޽���

	MSG_EX_USER_NOTICE,				// ���� ����

	MSG_EX_CRAFT_SYSTEM,			// ����2 �ý���

	MSG_EX_DECOMPOSE_SYSTEM,		// ���� �ý���

	MSG_EX_PRODUCE_SYSTEM,			// ä�� �ý���

	MSG_EX_LOOT_SYSTEM,				// ���� �ý���

	MSG_EX_CRAFT_POINT,				// ũ������ ����Ʈ
	
	MSG_EX_PROGRESS_CANCEL,			// Ŭ���̾�Ʈ ���α׷��� ���� ���� ���.

	MSG_EX_POST_SYSTEM,				// ���� �ý���

	MSG_EX_EVENT_AUTOMATION_SYSTEM,	// �̺�Ʈ �ڵ�ȭ

	MSG_EX_JUMPING_SYSTEM,			 // ���� �ý���

	MSG_EX_REFORMER_SYSTEM,			// REFORM_SYSTEM

	MSG_EX_SERVER_TIME,		//  ���� �ð�

	MSG_EX_SET_TARGET,				// Ÿ�� ������Ʈ�� �������� �˷��ش�. ( ����� PC�� )

	MSG_EX_NOTICE,				// GM ���� �ý���

	MSG_EX_SETTINGS,

	MSG_EX_INVENTORY_OPTION,
	MSG_EX_SET_AGGRESSIVE_MOB,

	
	MSG_EX_BATTLE_WARFARE_REP,
	MSG_EX_BATTLE_WARFARE_REQ,
	#ifdef PET_BUFF_ALL_SYSTEM
	MSG_EX_PET_USE_ALL_BUFF,
	#endif
	MSG_EX_GET_DONATION_TIER_INFO,
#ifdef CLOUD_AUTO_QUEST_DELIVERY
	MSG_EX_CLOUD_AUTO_QUEST,//Cloud auto quest
#endif
#ifdef QUICK_PANEL
		MSG_EX_CLOUD_SKILLS_USE,
		MSG_EX_CLOUD_SAVE_QUICKPANEL,
#endif
    MSG_EX_PROMO_KEY,
	MSG_EX_END,
} MSG_EXTEND_TYPE;

typedef enum _tagMsgReformSystemType
{
	MSG_EX_REFORMER_SYSTEM_REQ,						// ������ ���
	MSG_EX_REFORMER_SYSTEM_NOT_GRADE_REP,			// ������ ����� �����Ӱ� �ƴ�
	MSG_EX_REFORMER_SYSTEM_NOT_GOLD_MAGNIFIER_REP,	// Ȳ�� �����Ⱑ �ƴ�
	MSG_EX_REFORMER_SYSTEM_NOT_REFORM_ITEM_REP,		// ���� ������ �������� �ƴ�
	MSG_EX_REFORMER_SYSTEM_NOT_MID_ITEM_REP,		// �߱� �������� �ƴ�
	MSG_EX_REFORMER_SYSTEM_NOT_HIGH_ITEM_REP,		// ���� �������� �ƴ�
	MSG_EX_REFORMER_SYSTEM_EXCEPTION_ERROR_REP,		// �׿� ���� �߻�
	MSG_EX_REFORMER_SYSTEM_REFORM_SUCCESS_REP,		// ���� ����sdfsdf
}MSG_EX_REFORMER_SYSTEM_TYPE;

typedef enum _tagMsgExJumpingSystemType
{
	MSG_EX_JUMPING_SUCCESS,     // ���� ����
	MSG_EX_JUMPING_ERROR_LEVEL,    // ���� ���� : ���� ĳ���� ������ �����Ϸ��� �������� ���ų� ����
	MSG_EX_JUMPING_ERROR_NOT_EXIST_CHAR, // ���� ���� : ���� �� �����Ϸ��� �������� ���ų� ���� ĳ���Ͱ� ����
}MSG_EX_JUMPING_SYSTEM_TYPE;

typedef enum _tagMsgExPkPenaltyReformType // REFORM_PK_PENALTY_201108
{
	MSG_EX_PKPENALTY_REFORM_REWARD_INFO,		// (s->c) ������ Ÿ��Ʋ ���� ������ ������. : titleInfo(n)
	MSG_EX_PKPENALTY_REFORM_REWARD_REQ,			// (c->s) Ÿ��Ʋ ���� ��û. : titleNum(n)	
	MSG_EX_PKPENALTY_REFORM_REWARD_REP,			// (s->c) Ÿ��Ʋ ���� �亯 : titleNum(n), MSG_EX_PKPENALTY_REFORM_ERROR_TYPE

}MSG_EX_PKPENALTY_REFORM_TYPE;

typedef enum _tagMsgExPkPenaltyReformErrorType // REFORM_PK_PENALTY_201108
{	
	MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_SUC,	// ����.
	MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_COUNT,	// Ÿ��Ʋ ���� ���ѿ� �ɸ� 
	MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_ONCE,	// �̹� ���� ����
	MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_FAIL,	// ��Ÿ ����

}MSG_EX_PKPENALTY_REFORM_ERROR_TYPE;


// [2010/12/10 : Sora] ��Ű ��ο� �ڽ� �����޽��� ó��
typedef enum __tagMsgLuckyDrowBoxErrorType
{
	MSG_LUCKYDRAWBOX_ERROR_SUCESS=0,
	MSG_LUCKYDRAWBOX_ERROR_NEED,			// "���ڸ� ���� ���ؼ��� �������� �ʿ��մϴ� Ȯ�� �� �ٽ� �õ��Ͽ� �ֽʽÿ�."
	MSG_LUCKYDRAWBOX_ERROR_INVEN,			// "������ �����մϴ� Ȯ�� �� �ٽ� �õ��Ͽ� �ֽʽÿ�"
	MSG_LUCKYDRAWBOX_ERROR_USE,				// "�� �������� ����� �� �����ϴ�."
	MSG_LUCKYDRAWBOX_ERROR_OVER_WEIGHT,		// "���԰� 100%�� �Ѿ����ϴ�. Ȯ�� �� �ٽ� �õ��Ͽ� �ֽʽÿ�."
}MSG_EX_LUCKYDRAW_BOX_ERROR_TYPE;

typedef enum _tagMsgExMonsterMercenaryType // (unsigned char)
{	
	MSG_EX_MERCENARY_SUMMON,			// ��ȯ ���� �޽��� uniqItemIndex(n) toggle(char 1:���� -1: ��ȯ ����)
	MSG_EX_MERCENARY_LIMIT_TIME,		// ���� �ð� ���� time(n)
	MSG_EX_MERCENARY_ERROR				// (unsigned char)MSG_EX_MONSTER_MERCENARY_ERROR_TYPE
}MSG_EX_MONSTER_MERCENARY_TYPE;

typedef enum _tagMsgExMonsterMercenaryErrorType // (unsigned char)
{	
	MSG_EX_MERCENARY_ERROR_USE_FAIL,		// ��� ����
	MSG_EX_MERCENARY_ERROR_SUMMON_ALREADY,	// �̹� �ٸ����� ��ȯ�Ǿ� �־� ����� �� ����
	MSG_EX_MERCENARY_ERROR_DONT_SUMMON,		// ��ȯ �Ұ�
	MSG_EX_MERCENARY_ERROR_MON_AUTO_DEL,	// ���� �ڵ� ����(�Ÿ��� �־����ų� �ð��� �ٵǾ
	MSG_EX_MERCENARY_ERROR_AREA,			// �� ���������� �뺴�� ��ȯ �� �� �����ϴ�. 
}MSG_EX_MONSTER_MERCENARY_ERROR_TYPE;

typedef enum _tagMsgExRaidInfoType
{
	MSG_EX_RAID_SCENE_SEND_OUTPUT,		//(0)
	MSG_EX_RAID_SCENE_SEND_PADOX_SKILL,	//(1)
	MSG_EX_RAID_SCENE_SEND_OBJECT_REFRESH,
	MSG_EX_RAID_SCENE_SEND_OBJECT_ALL_STATE,
	MSG_EX_RAID_SCENE_SEND_COUNT_DOWN,					// %d�� �� �ĵ����� ��ó�� ���� �����ϴ�. (4)	
} MSG_EX_RAID_INFO_TYPE;

typedef enum __tagMsgExSubJob		// [2010/08/25 : Sora] ADD_SUBJOB
{
	MSG_EX_SUBJOB_REGIST,			// �����������(n)subJobCode 1:����(Ʈ���̴�)
	MSG_EX_SUBJOB_ERROR_SUCESS,		// ����������ϼ���(n) subJobCode 1: ����(Ʈ���̴�)
	MSG_EX_SUBJOB_ERROR_FAIL,		// ����������Ͻ���(n) error 1:��������, 2:����ġ����, 3: ��ų����Ʈ����4: ��������

	MSG_EX_SUBJOB_ERROR_NOT_TRADER,	// �����̾ƴմϴ�
}MSG_EX_SUBJOB_TYPE;

typedef enum _tagMsgDungeonTimeType
{
	// �޼����� unsigned char ������ �߼۵ȴ�.
	MSG_EX_DUNGEONTIME_NOTICE,		// ���̵� �� �α��� �� ���� Ÿ�� ���϶� ������ �޽���
	MSG_EX_DUNGEONTIME_END,			// ���� Ÿ�� ������ ������ �޽���
	MSG_EX_DUNGEONTIME_START,		// ���� Ÿ�� ���� �Ҷ� ������ �޽���
} MSG_EX_DUNGEONTIME_TYPE;

typedef enum _tagMsgLacaretteSystemType
{
	MSG_EX_LACARETTE_TOKEN_READY_REQ,	// ��ū ���� ���� Ȯ�� ��û
	MSG_EX_LACARETTE_TOKEN_READY_REP,	// ��ū ���� ���� Ȯ�� �亯
	MSG_EX_LACARETTE_TOKEN_REQ,		// ��ū ���� ��û
	MSG_EX_LACARETTE_TOKEN_REP,		// ��ū ���� �亯 : MSG_EX_LACARETTE_TOKEN_ERROR_TYPE
	MSG_EX_LACARETTE_RETTE_REQ,		// ��÷ ���� ��û : courseArrNum(n), courseIndex(n), tokenItemIndex(n)
	MSG_EX_LACARETTE_RETTE_REP,		// ��÷ ���� �亯 : MSG_EX_LACARETTE_RETTE_ERROR_TYPE
	MSG_EX_LACARETTE_RESULT_REQ,	// ������ ���� ��û : itemIndex(int)
	MSG_EX_LACARETTE_RESULT_REP,	// ������ ���� Ȯ�� : MSG_EX_LACARETTE_RESULT_ERROR_TYPE
	MSG_EX_LACARETTE_UI_REQ,		// �̿� Ƚ�� ��û
	MSG_EX_LACARETTE_UI_REP,		// �̿� Ƚ�� �亯 : repeatcount(n)
	MSG_EX_LACARETTE_JACKPOT,		// ���� �޽��� (s -> c) : itemindex(n), char_name(str)
	MSG_EX_LACARETTE_UI_COLSE,		// â�� �ݴ´�.
} MSG_EX_LACARETTE_SYSTEM_TYPE;

typedef enum _tagMsgLacaretteTokenErrorType
{
	MSG_EX_LACARETTE_TOKEN_ERROR_SUC,
	MSG_EX_LACARETTE_TOKEN_ERROR_ALREADY,	// �̹� ���� �Ǿ��� 
	MSG_EX_LACARETTE_TOKEN_ERROR_INVEN,		// �κ� �� ��
	MSG_EX_LACARETTE_TOKEN_ERROR_TOKEN_OVER, // 100�� �̻� �����Ұ�
	MSG_EX_LACARETTE_TOKEN_ERROR,			// ��Ÿ
} MSG_EX_LACARETTE_TOKEN_ERROR_TYPE;

typedef enum _tagMsgLacaretteRetteErrorType
{
	MSG_EX_LACARETTE_RETTE_ERROR_SUC,			// ���� : giveItemArrNum(n), giveItemIndex(n)
	MSG_EX_LACARETTE_RETTE_ERROR_TOKEN,			// ��ū����
	MSG_EX_LACARETTE_RETTE_ERROR_WEIGHT,		// ���� �ʰ�
	MSG_EX_LACARETTE_RETTE_ERROR,				// ��Ÿ 
} MSG_EX_LACARETTE_RETTE_ERROR_TYPE;

typedef enum _tagMsgLacaretteResultErrorType
{
	MSG_EX_LACARETTE_RESULT_ERROR_SUC,			// ���� ���� : repeatcount(n), tokenItemIndex(n), tokenDelCount(n)
	MSG_EX_LACARETTE_RESULT_ERROR_TOKEN,		// ��ū����
	MSG_EX_LACARETTE_RESULT_ERROR_INVEN,		// �κ� �� ��
	MSG_EX_LACARETTE_RESULT_ERROR_WEIGHT,		// ���� �ʰ�
	MSG_EX_LACARETTE_RESULT_ERROR,				// ��Ÿ 
} MSG_EX_LACARETTE_RESULT_ERROR_TYPE;

typedef enum __tagMsgExTrigerEventType
{
	MSG_EX_TRIGGER_EVENT_ERROR,			// ����	
	MSG_EX_TRIGGER_EVENT_ALREADY_PLAY,		// �̹� ���� ��
	MSG_EX_TRIGGER_EVENT_NO_CONDITION,		// ������ ������ �ȵ�
	MSG_EX_TRIGGER_EVENT_TRIGER_EXIST_AREA,  // Ʈ���Ű� �����ϴ� ������ �����ϸ� ������ �����ش�.
	MSG_EX_TRIGGER_EVENT_ITEM_COMPOSITION,		// ������ ����
	MSG_EX_TRIGGER_EVENT_ITEM_DROP,			// ������ ���
	MSG_EX_TRIGGER_EVENT_OPEN_THE_DOOR,		// �� ����
	MSG_EX_TRIGGER_EVENT_START_RAID,			// ���̵� ����
	MSG_EX_TRIGGER_EVENT_MESSAGE_PRINT,		// ���� �޼��� ���
	MSG_EX_TRIGGER_EVENT_SUMMON_NPC,			// npc ��ȯ
	MSG_EX_TRIGGER_EVENT_USE_DEBUF,			// ����� �ɸ�
	MSG_EX_TRIGGER_EVENT_ACTIVE_OBJECT,		// object Ȱ��ȭ
	MSG_EX_TRIGGER_EVENT_REMOVE_NPC,			// npc �ڵ� ����
	MSG_EX_TRIGGER_EVENT_TIME_LIMIT,		// �ð����� (subtype : long(-1)[Secondtime])
	MSG_EX_TRIGGER_EVENT_RESTORE_OBJECT,		// ������Ʈ �ʱ�ȭ
	
	// [100222: selo] Ʈ���� �̺�Ʈ �߰�
	MSG_EX_TRIGGER_EVENT_ITEM_GET_INVEN,		// ������ �κ��丮�� ���� = 15
	MSG_EX_TRIGGER_EVENT_CONSECUTIVE_DIALOGUE,	// ���� ��ȭ = 16
	MSG_EX_TRIGGER_EVENT_ACTIVE_EFFECT,			// ����Ʈ ��Ÿ���� = 17
}MSG_EX_TRIGER_EVENT_TYPE;

typedef enum __tagMsgExInitSSkillErrorType
{
 MSG_EX_INIT_SSkill_ERROR_SUCCESS, // ����
 MSG_EX_INIT_SSkill_ERROR_FAIL,  // ����
} MSG_EX_INIT_SSkill_ERROR_TYPE;

typedef enum _tagMsgExExtremeCubeType
{
	MSG_EX_EXTREME_CUBE_PARTY,					// ��Ƽť�� ��ü�����
	MSG_EX_EXTREME_CUBE_PARTY_PERSON,			// ��Ƽť�� ���������
	MSG_EX_EXTREME_CUBE_GUILD,							// ���ť�� ��ü�����
	MSG_EX_EXTREME_CUBE_GUILD_PERSON,			// ���ť�� ���������
	MSG_EX_EXTREME_CUBE_STATE_REQ,					// ť����Ȳ â ȣ���
	MSG_EX_EXTREME_CUBE_STATE_REP,					// ť����Ȳ ����, �Ҽ�ť������Ʈ(n), (���� ����) count(c), rank(c), guildname(s), guildmaster(s), cubepoint(n) 
													// (������ ����) count(c), rank(c), guildname(s), guildmaster(s), cubepoint(n)  (�߰��κ�)
	MSG_EX_EXTREME_CUBE_COMPLETE,					// �Ϸ�ī��Ʈ count(c)
	MSG_EX_EXTREME_CUBE_ERROR,							// errortype
	MSG_EX_EXTREME_CUBE_STATE_PERSONAL_REQ,     
	//(�߰��κ�)
	MSG_EX_EXTREME_CUBE_STATE_PERSONAL_REP,   // ť�� ��������Ʈ Ȯ�ν� ���� , ����ť������(n) (���� ����)count(c) rank(c) guildname(s) charname(s) cubepoint(n) 
												// (������ ����)count(c) rank(c) guildname(s) charname(s) cubepoint(n)
	MSG_EX_EXTREME_CUBE_REWARD_GUILDPOINT_REP, // �������� �������Ʈ ������ �˸�, rank(c) guildpoint(n)
	MSG_EX_EXTREME_CUBE_REWARD_PERSONAL_REQ,   // ����ť�꺸�� ��û	
}MSG_EX_EXTREME_CUBE_TYPE;


typedef enum _tagMsgExExtremeCubeErrorType
{
	MSG_EX_EXTREME_CUBE_ERROR_NOITEM,							// �������� ����
	MSG_EX_EXTREME_CUBE_ERROR_OVERCOUNT,					// ������������ ����
	MSG_EX_EXTREME_CUBE_ERROR_CANNOT_MOVE,						// �̵��Ұ�
	MSG_EX_EXTREME_CUBE_ERROR_CANNOT_CAHNGE_RATE,		// ��������Ұ�
	MSG_EX_EXTREME_CUBE_ERROR_NOT_GUILD_CUBE_TIME, // ���ť��ð��ƴ�
	MSG_EX_EXTREME_CUBE_ERROR_NOT_PARTY_CUBE_TIME, // ��Ƽť��ð��ƴ�
	MSG_EX_EXTREME_CUBE_ERROR_PARTYCUBE,   // ��Ƽť�� ��
	MSG_EX_EXTREME_CUBE_ERROR_GUILDCUBE,   // ���ť�� ��
	MSG_EX_EXTREME_CUBE_ERROR_START_NOTICE, // ���ť�� ���۸޽���
	MSG_EX_EXTREME_CUBE_ERROR_END_NOTICE,     // ���ť�� ����޽���
	MSG_EX_EXTREME_CUBE_ERROR_START_REMAINTIME, // ���ť�� ���� 1���� �޽���
	MSG_EX_EXTREME_CUBE_ERROR_END_REMAINTIME,    // ���ť�� ���� 1���� �޽���	
	//(�߰��κ�)
	MSG_EX_EXTREME_CUBE_ERROR_INVEN_NOSPACE,		// �κ� ��������
	MSG_EX_EXTREME_CUBE_ERROR_REWARD_PERSONAL_CANNOT,	// ���κ��� ���� �ȸ���
	MSG_EX_EXTREME_CUBE_ERROR_REWARD_PERSONAL_ALREADY,	// ���κ��� �̹� �޾���	
}MSG_EX_EXTREME_CUBE_ERROR_TYPE;


typedef enum __tagMsgExAttackPetErrorType
{
	MSG_SUB_STAT,					// CAHR STAT MSG
	MSG_SUB_ITEM_WEAR,				// ������ �Ա� �������
	MSG_SUB_ITEM_WEARING,				// ���� ��� ��ȭ �˸���	
	MSG_SUB_REBIRTH,				// Req item, Rep errorcode ��Ȱ��û
	MSG_SUB_SKILLLIST,				// ��ų����Ʈ ��û
	MSG_SUB_SKILLLEAN,				// ��ų ����
	MSG_SUB_STATUP,					// ���� �ø���
	MSG_SUB_LEVELUP,
	MSG_SUB_DELETE_EQUIP,			// �� ��� �Ⱓ ����
	MSG_SUB_APET_INFO,				// �� ����
	MSG_SUB_ADDITEM_MSG,
	MSG_SUB_AI_LIST_REQ,
	MSG_SUB_AI_LIST_NTF,
	MSG_SUB_AI_ONOFF_REQ,
	MSG_SUB_AI_ONOFF_REP,
	MSG_SUB_AI_UPDATE_REQ,
	MSG_SUB_AI_UPDATE_REP,
	MSG_SUB_EVOLUTION,				//��ȭ ��û row(n),col(n) /���� errcode(uc)
	MSG_SUB_MOUNT_REQ,				// ��Ÿ��(c)type 0:������, 1:Ÿ��
	MSG_SUB_MOUNT_REP,				// ��Ÿ������error code (c)error 0:��û���� 1:��û���� , (c) ���缭���󸶿�Ʈ����, (n) ����Index, (n) ���ε���
	MSG_SUB_SUMMON_ERROR,			// ���ȯ����(c) error ��
	MSG_SUB_STATINIT,			// �� ���� �ʱ�ȭ (c) error 0:����, 1:�����, 2:����ϰų�����, 3:�ʱ�ȭ�� ���� ����
	MSG_SUB_EXPINFO,
	MSG_SUB_EXPUSE,
	MSG_SUB_ERROR_NOT_EXIST_NPC,// NPC�� ������ ����
	MSG_SUB_INIT_COOLTIME,		// �� ��Ÿ�� ����
	MSG_SUB_DELETE_ITEM,		// �� ��� ����

} MSG_EX_ATTACK_PET_ERRORTYPE;

typedef enum _tagMsgAPetErrorType
{
	 MSG_APET_ERROR_OK,
	 MSG_APET_ERROR,
	 MSG_APET_ERR_NOT_HAVE_ITEM,  // ���� ���� ���� ������ : ai_index(n)
	 MSG_APET_ERR_WRONG_AI   // �߸��� AI ���� : ai_index(n)
}MSG_APET_ERROR_TYPE;

typedef enum __tagMsgExChaosBallErrorType
{
	MSG_CHAOSBALL_ERROR_SUCCESS,		// ī���� �� ������ ����
	MSG_CHAOSBALL_ERROR_ITEM_COUNT,		// ������ ���� ����
	MSG_CHAOSBALL_ERROR_NOSPACE,		// �κ��丮�� �� ������ ����.
	MSG_CHAOSBALL_ERROR_ITEM_FAULT,		// ī���� �� ������ ����
} MSG_EX_CHAOSBALL_ERRORTYPE;

typedef enum __tagMsgDVDInfoType
{
	MSG_DUNGEON_INFO,		//���� ���� ��û
	MSG_MANAGEMENT,			//���� ����
	MSG_DUNGEON_ENTER,		//�������� �̵�
	MSG_GUILD_NAME_COLOR,	//���� ��� �̸� ��
	MSG_CHANGE_NORMAL_NOTICE, // ���� �Ϲ� ��� ����
	MSG_CHANGE_NORMAL_NOTICE_TO_OWNER	// ���� �Ϲ� ��� ����(���ֿ��Ը�)
} MSG_DVD_INFO_TYPE;

typedef enum __tagMsgDVDInfoSubType
{
	MSG_MANAGEMENT_MANAGER_CONFIRM,					//���� ��û
	MSG_MANAGEMENT_MANAGER_ENV_INFO,				//���� ���� ȯ�� ���� ��û
	MSG_MANAGEMENT_MANAGER_ENV_CHANGE,				//���� ����ȯ�� ����
	MSG_MANAGEMENT_MANAGER_MONSTER_INFO,			//���� ���� ���� ���� ��û
	MSG_MANAGEMENT_MANAGER_MONSTER_CHANGE,			//���� ���� ���� ���� ����
	MSG_MANAGEMENT_MANAGER_TAX_INFO,				//����� ���� ���� ��û
	MSG_MANAGEMENT_MANAGER_TAX_CHANGE,				//����� ���� ����
	MSG_MANAGEMENT_MANAGER_HUNTER_TAX_INFO,			//���Ƽ� ���� ��û
	MSG_MANAGEMENT_MANAGER_HUNTER_TAX_CHANGE,		//���Ƽ� ����
	MSG_MANAGEMENT_MANAGER_ETC,						//��Ÿ ����
	MSG_DUNGEON_ENTER_FEE,							//���� ����� 
	MSG_DUNGEON_GO,									//�������� �̵�
	MSG_MANAGEMENT_MANAGER_CONFIRM_NORMAL,			// ���� ��û(�Ϲ�)
	MSG_NAMAGEMENT_CHANGE_OWNER_MODE,				// ���� ���� ���� ���� ��û
} MSG_DVD_INFO_SUBTYPE;

typedef enum __tagMsgDVDInfoErrorType
{
	MSG_DVD_ERROR_OK,			//����
	MSG_DVD_ERROR_CONFIRM,		//���� ���� ���� ����
	MSG_DVD_ERROR_MONEY,		//���� ����� ����� ����
	MSG_DVD_ERROR_ZONE,			//�����̳� ���� ���� ����
	MSG_DVD_ERROR_GUILD,		//��尡 ���ų�, ã�� �� ���� ��
	MSG_DVD_ERROR_NORMAL_MODE,	// �Ϲݸ�� �����̴�.
}MSG_DVD_INFO_ERROR_TYPE;

typedef enum __tagMsgExCastleWarType
{
	MSG_CASTLE_CRISTAL_RESPOND_WAIT,
	MSG_CASTLE_CRISTAL_RESPOND_START,	// ���� ����	charindex(n), starttime(ll)	
	MSG_CASTLE_CRISTAL_RESPOND_END,		// ���� �Ϸ�	charindex(n)
	MSG_CASTLE_CRISTAL_RESPOND_FAIL,	// ���� ����	charindex(n)
	MSG_CASTLE_TOWER_CONTRAL,			// ������ Ÿ�� ����
	MSG_CASTLE_TOWER_CONTRAL_LIST,		// ����Ʈ Ÿ�� ���� ����Ʈ
	MSG_CASTLE_TOWER_REINFORCE,			// ������ Ÿ�� ��ȭ ����		type(c), step(c)
	MSG_CASTLE_TOWER_REINFORCE_LIST,	// ������ Ÿ�� ��ȭ ����Ʈ		3*(type(c), step(c))
	MSG_CASTLE_TOWER_REPAIRE,			// ���� Ÿ�� ����				cl->gs idx(n) | gs->cl	idx(n)
	MSG_CASTLE_TOWER_REPAIRE_LIST,		// ���� Ÿ�� ���� ����			cl->gs idx(n) | gs->cl	money(n)
	MSG_CASTLE_TOWER_WARP_LIST,			// ���� ���� Ÿ�� ��ȿ ����Ʈ   cl->gs idx(n) | gs->cl  cnt(c) * idx(n)	
	MSG_CASTLE_QUARTERS_INSTALL,		// ��Ȱ���� ��ġ		cl->gs idx(n) | gs->cl  idx(n), gidx(n)
	MSG_CASTLE_QUARTERS_CRUSH,			// ��Ȱ ���� �ı�		gs->cl idx(n)
	MSG_CASTLE_QUARTERS_LIST,			// ��Ȱ ���� ����Ʈ		gs->cl 7*(nindex(n), gindex(n))
	MSG_CASTLE_WAIT_TIME,				// ��Ȱ ��� �ð�		gs->cl wait_time(n) sec  
	MSG_EX_CASTLE_ERROR,				// ���� ���� subtype(c)
} MSG_EX_CASTLE_WAR_TYPE;

typedef enum __tagMsgExCastleErrorType
{
 MSG_EX_CASTLE_ERROR_NOT_JOIN,    // ���� �������� �ƴ�
 MSG_EX_CASTLE_ERROR_NOT_WAR,    // ������ ���� �ƴ�
 MSG_EX_CASTLE_ERROR_POS_FAIL,    // ��ġ �̻�
 MSG_EX_CASTLE_ERROR_MEM_5_FAIL,    // ���� �ο� �ڸ� ����
 MSG_EX_CASTLE_ERROR_NOT_OWNER,    // ���� ��� �ƴ�
 MSG_EX_CASTLE_ERROR_NOT_RESPOND,   // ���� ���� �ƴ�
 MSG_EX_CASTLE_ERROR_NOT_RESPOND_TIME,  // ���� �ð� ����
 MSG_EX_CASTLE_ERROR_NO_MONEY,    // �� ����
 MSG_EX_CASTLE_ERROR_NOT_ATTACK,    // ���� ��� �ƴ�
 MSG_EX_CASTLE_ERROR_NO_DATA,    // ������ �̻�
 MSG_EX_CASTLE_ERROR_NO_DIFFER,    // ���� �����Ϳ� ����
 MSG_EX_CASTLE_ERROR_NOT_BUY,    // �������� �ʾ���
 MSG_EX_CASTLE_ERROR_NO_NPC,     // ���� Ÿ��
 MSG_EX_CASTLE_ERROR_DEAD_NPC,    // ���� Ÿ�� 
 MSG_EX_CASTLE_ERROR_HAVE_NO_GUILD,   // ��� ���� �ƴ�
 MSG_EX_CASTLE_ERROR_USE_NPC,    // ����� ��Ȱ ����
 MSG_EX_CASTLE_ERROR_USE_NPC_OTHER,   // �̹� �ٸ� ��Ȱ���� �����
 MSG_EX_CASTLE_ERROR_NO_NPC2,     // ���� ��Ȱ ����
 MSG_EX_CASTLE_ERROR_DEAD_NPC2,    // ���� ��Ȱ����
 MSG_EX_CASTLE_ERROR_SAME_DATA,	   // ���� ������
 MSG_EX_CASTLE_ERROR_NOT_BUY_NPC,   // ���̻� NPC�� ���� �Ҽ� �����ϴ�,
 MSG_EX_CASTLE_ERROR_PERMISSION_DENIED, // ������ �����ϴ�.
} MSG_EX_CASTLE_ERROR_TYPE;

typedef enum __tagMsgExMessengerType
{
	MSG_EX_MESSENGER_INVITE,	// �ش� �ɸ��� �ʴ� : makeCharIndex(n) chatIndex(n) charIndex(n)
								// chatIndex �� -1�̸� ��ȭ�� �߰�,
								// GS->C			: makeCharIndex(n) chatIndex(n) charName(str) 
	MSG_EX_MESSENGER_OUT,		// �ش� �ɸ��� ��ȭ�濡�� ���� : makeCharIndex(n) chatIndex(n)
								// GS->C			: makeCharIndex(n) chatIndex(n) charName(str) 
	MSG_EX_MESSENGER_CHARLIST,	// �ʴ���� �ɸ��Ϳ��� ����� ����Ʈ�� ���� 
								// GS->C			: makeCharIndex(n) chatIndex(n) count(n) charName(str)
	MSG_EX_MESSENGER_CHAT,		// charName�� ä�� �޼��� ���� : makeCharIndex(n) chatIndex(n) chat(str)
								// GS->C			: makeCharIndex(n) chatIndex(n) color(n) charName(str) chat(str) 
	MSG_EX_MESSENGER_GROUP_ADD,	// ģ�� �׷� �߰�	: groupName(str)
								// GS->C			: gIndex(n) groupName(str)  : gIndex �� -1�̸� �ߺ��� �̸� 
	MSG_EX_MESSENGER_GROUP_DEL,	// ģ�� �׷� ����	: gIndex(n)
								// GS->C			: gIndex(n) : gIndex �� -1�̸� �������� �ʴ� �׷�
	MSG_EX_MESSENGER_GROUP_CHANGE,	// ģ�� �׷� �̸����� : gIndex(n) newName(str)
								// GS->C			: gIndex(n) groupName(str)  : gIndex�� -1�̸� �ߺ��� �̸� 
	MSG_EX_MESSENGER_GROUP_MOVE,	// ģ�� �׷� �̵�	  : gIndex(n) charName(str) 
								// GS->C			: gIndex(n) charName(str)   : gIndex�� -1�̸� �������� �ʴ� �׷� 
	MSG_EX_MESSENGER_GROUP_LIST, // �׷� ����Ʈ ������ : count(n) gIndex(n) gName(str)

	MSG_EX_MESSENGER_CHATCOLOR_CHANGE, // Į�� ���� : color(n)
	MSG_EX_MESSENGER_BLOCK,		// �ش����� ����	: name(str)
								// GS->C			: errcode(c) charIndex(n) name(str)
	MSG_EX_MESSENGER_RELEASE_BLOCK,	// �ش����� ����: charIndex(n)
								// GS->C			: errcode(c) charIndex(n) name(str)
	MSG_EX_MESSENGER_BLOCK_LIST, // ������ ����Ʈ   : count(n) charIndex(n) name(str)

	MSG_EX_MESSENGER_ONE_VS_ONE,	// 1:1 ��ȭ : sCharIndex(n) tCharIndex(n) chat(str)
	MSG_EX_MESSENGER_ONE_OFF_LINE,	// ���� ����������: sCharIndex(n), tCharIndex(n)
} MSG_EX_MESSENGER_TYPE;

typedef enum __tagMsgEMessengerErrorType
{
	MSG_EX_MESSENGER_SUCCESS,			// ����
	MSG_EX_MESSENGER_BLOCK_NOTCHAR,		// �ش� �ɸ��Ͱ� �����ϴ�
	MSG_EX_MESSENGER_BLOCK_INVALIDNAME,	// �̸��� �߸� �Է� �Ǿ����ϴ�
	MSG_EX_MESSENGER_NOMORE_BLOCK,		// ���̻� �����Ҽ� �����ϴ�
	MSG_EX_MESSENGER_ALREADY_BLOCK,		// �̹� �����Ǿ����ϴ�

} MSG_EX_MESSENGER_ERROR_TYPE;

typedef enum __tagMsgExStringOutputType
{
	MSG_EX_STRING_OUTPUT_WINDOW,		// â
	MSG_EX_STRING_OUTPUT_SYS,			// �ý���â
	MSG_EX_STRING_OUTPUT_NOTICE,		// ����
	MSG_EX_STRING_OUTPUT_CHAT,			// êâ
} MSG_EX_STRING_Output_TYPE;

typedef enum __tagMsgExStringArgType
{
	MSG_EX_STRING_CHAR,			// char
	MSG_EX_STRING_INT,			// int
	MSG_EX_STRING_LONGLONG,		// LONGLONG
	MSG_EX_STRING_STR,			// str(50)
} MSG_EX_STRING_ARG_TYPE;

typedef enum __tagMsgExPartyMatchType
{
	MSG_EX_PARTY_MATCH_REG_MEMBER_REQ,		// ��Ƽ ��Ī �Ϲ� ��� ��û : partyType(c)
	MSG_EX_PARTY_MATCH_REG_MEMBER_REP,		// ��Ƽ ��Ī �Ϲ� ��� ���� : errorcode(n)

	MSG_EX_PARTY_MATCH_REG_PARTY_REQ,		// ��Ƽ ��Ī ��Ƽ ��� ��û : comment(str) jobFlag(n) limitlevel(c)
	MSG_EX_PARTY_MATCH_REG_PARTY_REP,		// ��Ƽ ��Ī ��Ƽ ��� ���� : errorcode(n)

	MSG_EX_PARTY_MATCH_MEMBER_LIST_REQ,		// ��Ƽ ��Ī �Ϲ� ����Ʈ ��û : pageno(n) job(c) limitlevel(c) partytype(c)
											// job�� -1�̸� ��� ����, partytype�� -1�̸� ��� ������ ��Ƽ, pageno�� 0-based index
	MSG_EX_PARTY_MATCH_MEMBER_LIST_REP,		// ��Ƽ ��Ī �Ϲ� ����Ʈ ���� : pageno(n) count(n) [charindex(n) charname(str) leveldiff(c) zone(n) job(c) partytype(c)] * count
											// leveldiff�� 0�̸� +-2 ����, 1�̸� +-3�̻�

	MSG_EX_PARTY_MATCH_PARTY_LIST_REQ,		// ��Ƽ ��Ī ��Ƽ ����Ʈ ��û : pageno(n) job(c) limitlevel(c) partytype(c)
											// job�� -1�̸� ��� ����, partytype�� -1�̸� ��� ������ ��Ƽ, pageno�� 0-based index
	MSG_EX_PARTY_MATCH_PARTY_LIST_REP,		// ��Ƽ ��Ī ��Ƽ ����Ʈ ���� : pageno(n) count(n) [bossindex(n) leveldiff(c) zone(n) jobflag(n) partytype(c) limitlevel(c) comment(str)] * count
											// leveldiff�� 0�̸� +-2 ����, 1�̸� +-3�̻�

	MSG_EX_PARTY_MATCH_DEL_REQ,				// ��Ƽ ��Ī ��� ���� ��û
	MSG_EX_PARTY_MATCH_DEL_REP,				// ��Ƽ ��Ī ��� ���� ����

	MSG_EX_PARTY_MATCH_INVITE_REQ,			// ��Ƽ ��Ī �Ϲ� �ʴ� ��û : charindex(n)
	MSG_EX_PARTY_MATCH_INVITE_REP,			// ��Ƽ ��Ī �Ϲ� �ʴ� ���� : errorcode(n) partytype(c) bossindex(n) bossname(str) destindex(n) destname(str)

	MSG_EX_PARTY_MATCH_JOIN_REQ,			// ��Ƽ ��Ī ��Ƽ ���� ��û : bossindex(n)
	MSG_EX_PARTY_MATCH_JOIN_REP,			// ��Ƽ ��Ī ��Ƽ ���� ���� : errorcode(n) partytype(c) bossindex(n) bossname(str) charindex(n) charname(str) charjob(c)
	MSG_EX_PARTY_MATCH_JOIN_ALLOW,			// ��Ƽ ��Ī ��Ƽ ���� ��� : reqindex(n)
	MSG_EX_PARTY_MATCH_JOIN_REJECT,			// ��Ƽ ��Ī ��Ƽ ���� ���� : reqindex(n)
											// reqindex�� ������ ��û�� ����� ��� �ڽ��� index, ��Ƽ���� ��� ������ ��û�� ����� �ε��� �̴�

} MSG_EX_PARTY_MATCH_TYPE;

typedef enum __tagMsgExPartyMatchErrorType
{
	MSG_EX_PARTY_MATCH_ERROR_REG_MEMBER_OK,					// ��Ƽ ��Ī �Ϲ� ��� ����
	MSG_EX_PARTY_MATCH_ERROR_REG_MEMBER_ALREADY_PARTY,		// �̹� ��Ƽ �����ڰ� ��� ��û
	MSG_EX_PARTY_MATCH_ERROR_REG_MEMBER_ALREADY_REG,		// �̹� ��ϵ� ĳ��

	MSG_EX_PARTY_MATCH_ERROR_REG_PARTY_OK,					// ��Ƽ ��Ī ��Ƽ ��� ����
	MSG_EX_PARTY_MATCH_ERROR_REG_PARTY_NO_BOSS,				// ��Ƽ���� �ƴ� ����� ��û��
	MSG_EX_PARTY_MATCH_ERROR_REG_PARTY_FULL,				// ��Ƽ �ο� ������
	MSG_EX_PARTY_MATCH_ERROR_REG_PARTY_ALREADY_REG,			// �̹� ��ϵ� ��Ƽ

	MSG_EX_PARTY_MATCH_ERROR_INVITE_OK,
	MSG_EX_PARTY_MATCH_ERROR_INVITE_NOT_FOUND,				// ��Ƽ ��Ī�� ���� ����� �ʴ�
	MSG_EX_PARTY_MATCH_ERROR_INVITE_LEVEL,					// ��Ƽ Ÿ���� PARTY_TYPE_BATTLE �϶� ���� �˻翡 ��������
	MSG_EX_PARTY_MATCH_ERROR_INVITE_NOBOSS,					// ��Ƽ���� �ƴ� ����� ��û��
	MSG_EX_PARTY_MATCH_ERROR_INVITE_DIFF_TYPE,				// ��Ƽ Ÿ���� ���� ����
	MSG_EX_PARTY_MATCH_ERROR_INVITE_ALREADY_TARGET,			// ����� �̹� ��Ƽ ��
	MSG_EX_PARTY_MATCH_ERROR_INVITE_FULL,					// ��Ƽ �ο��� �ʰ�
	MSG_EX_PARTY_MATCH_ERROR_INVITE_ALREADY_REQUEST,		// �ٸ� ������� ��û ���϶�

	MSG_EX_PARTY_MATCH_ERROR_JOIN_OK,
	MSG_EX_PARTY_MATCH_ERROR_JOIN_ALREADY_TARGET,			// ������ ��û�� ���� �̹� �ٸ� ��Ƽ�� ���� ��
	MSG_EX_PARTY_MATCH_ERROR_JOIN_NOT_FOUND,				// ���� �Ϸ��� �ϴ� ��Ƽ�� ��Ī ���̺��� ����
	MSG_EX_PARTY_MATCH_ERROR_JOIN_LEVEL,					// ��Ƽ Ÿ���� PARTY_TYPE_BATTLE�̰� ���� �˻翡 ������
	MSG_EX_PARTY_MATCH_ERROR_JOIN_LIMIT_LEVEL,				// ���� ���� ���ǿ� ������
	MSG_EX_PARTY_MATCH_ERROR_JOIN_JOB,						// ���� ������
	MSG_EX_PARTY_MATCH_ERROR_JOIN_FULL,						// �ο� ������
	MSG_EX_PARTY_MATCH_ERROR_JOIN_ALREADY_REQUEST,			// ���� �ʴ� ��û�ڰ� �־ �Ұ���

} MSG_EX_PARTY_MATCH_ERROR_TYPE;

typedef enum __tagMsgExPartyRecallType
{
	MSG_EX_PARTY_RECALL_NOTICE,				// ���ݿ�û�� Ȯ�� �޽���, ��Ƽ���鿡�� ��ȯ�޽����� ���½��ϴ�.
	MSG_EX_PARTY_RECALL_PROMPT,				// ���ݴ���� Ȯ�� �޽���	: request_char_index(n) request_char_name(str)
											// XXXX��Ƽ������ ��ȯ�޽����� �����Խ��ϴ�. ��ȯ�� ���Ͻðڽ��ϱ�?
	MSG_EX_PARTY_RECALL_CONFIRM,			// ���� ����				: request_char_index(n) request_char_name(str) yes_or_no(c)
											// yes_or_no - yes(1), no(0)
	MSG_EX_PARTY_RECALL_CANCEL,				// ���� �źν�				: request_char_index(n) request_char_name(str) target_char_index(n) target_char_name(str)
	MSG_EX_PARTY_RECALL_ERROR_NOT_FOUND_PARTY_PLAYER,	// ��Ƽ�� �������� �ʾ��� ���
	MSG_EX_PARTY_RECALL_ERROR_CANT_USE_INSTANT_DUNGEON,	// �ν���Ʈ �������� ����� ��� ���� �߼�.
	MSG_EX_PARTY_RECALL_ERROR_CANT_USE_THIS_CONTINENT,	// �ش� ��Ƽ���� �������� �� ������� ������� �ʾ��� ���.
	MSG_EX_PARTY_RECALL_ERROR_NOT_PARTY,				// ��Ƽ ���°� �ƴմϴ�.
	MSG_EX_PARTY_RECALL_ERROR_CANT_USE_EXPEND,			// ������� ����� �� �����ϴ�.
	MSG_EX_PARTY_RECALL_CONFIRM_FAIL,					// ���� ���� �� �̵��� �� ���� ��� Ŭ�� ���� Ǯ�� ���� �޽���
	MSG_EX_PARTY_RECALL_AREADY,							// �̹� ������� �����Դϴ�.
} MSG_EX_PARTY_RECALL_TYPE;

typedef enum __tagMsgExPetRebirthErrorType
{
	MSG_EX_PET_REBIRTH_ERROR_OK,			// ����
	MSG_EX_PET_REBIRTH_ERROR_NOMONEY,		// ���� ����
	MSG_EX_PET_REBIRTH_ERROR_NOPET,			// �� ���� ����
	MSG_EX_PET_REBIRTH_ERROR_NODEAD,		// �� �������
} MSG_EX_PET_REBIRTH_ERROR_TYPE;

typedef enum __tagMsgExPetChangeItem
{
	MSG_EX_PET_CHANGE_ITEM_ERROR_OK,		// ������ ȹ��
	MSG_EX_PET_CHANGE_ITEM_ERROR_NOITEM,	// ������ ȹ�� ����, �길 ������
	MSG_EX_PET_CHANGE_ITEM_ERROR_FAIL,		// ��ȯ ���� : ���� �̴�
} MSG_EX_PET_CHANGE_ITEM_ERROR_TYPE;

typedef enum _tagMsgExPetChangeName
{
	MSG_EX_PET_CHANGE_NAME_ERROR_OK,	// �̸� ���� ����
	MSG_EX_PET_CHANGE_NAME_ERROR_FAIL,	// Pet �̸� ���� ����
	MSG_EX_PET_CHANGE_NAME_ERROR_ITEM,	// �������� ����
	MSG_EX_PET_CHANGE_NAME_ERROR_NOPET, // Pet ���� ����
	MSG_EX_PET_CHANGE_NAME_ERROR_DUPLICATE, // Pet �̸� �ߺ�
}MSG_EX_PET_CHANGE_NAME_ERROR_TYPE;

typedef enum __tagMsgExPetMixItemErrorType
{
	MSG_EX_PET_MIX_ITEM_ERROR_OK,		// ����
	MSG_EX_PET_MIX_ITEM_ERROR_FAIL,		// ����
	MSG_EX_PET_MIX_ITEM_ERROR_NOITEM,	// ������
	MSG_EX_PET_MIX_ITEM_ERROR_NOMIX,	// ���չ� ����
} MSG_EX_PET_MIX_ITEM_ERROR_TYPE;

typedef enum __tagMsgExCashItemType
{
	MSG_EX_CASHITEM_BALANCE_REQ,		// ĳ�� ���� ��û
	MSG_EX_CASHITEM_BALANCE_REP,		// ĳ��				: errorCode(uc) cashBalance(n)
	MSG_EX_CASHITEM_PURCHASE_REQ,		// ���� ��û		: count(n) ctid(n) 
	MSG_EX_CASHITEM_PURCHASE_REP,		// ����				: errorCode(uc) cashBalance(n)
	MSG_EX_CASHITEM_BRING_REQ,			// ��������			: count(n) idx(n) ctid(n)
	MSG_EX_CASHITEM_BRING_REP,			// ����				: errorCode(uc) 
	MSG_EX_CASHITEM_PURCHASELIST_REQ,	// ������ ��ǰ ���
	MSG_EX_CASHITEM_PURCHASELIST_REP,   // ����				: count(n) idx(n) ctid(n)
	MSG_EX_CASHITEM_PURCHASEHISTORY_REQ,// ���ų���			: y(n) m(c) d(c)
	MSG_EX_CASHITEM_PURCHASEHISTORY_REP,// ����				: errorcode(uc) count(n) ctid(n)
	MSG_EX_CASHITEM_MOONSTONE_START,	// �������� ���� Ȯ��: tab_idx(c) row_idx(c) col_idx(c) item_idx(n)
										//					   result(uc) grade(c)
	MSG_EX_CASHITEM_MOONSTONE_STOP,		// �������� �����ϰ� ���޿�û							   
	MSG_EX_CASHITEM_GIFT_REQ,			// ���� ������ ��û	: charName(str) Msg(str) count(n) idx(n) ctid(n)
	MSG_EX_CASHITEM_GIFT_REP,			//			����	: errcode(uc) 
	MSG_EX_CASHITEM_GIFT_SENDHISTORY_REQ,  // ���� ���� ����Ʈ ��û : y(n) m(c) d(c)
	MSG_EX_CASHITEM_GIFT_SENDHISTORY_REP,  // ����				: errorcode(uc) count(n) ctid(n) recvcharName(str)
	MSG_EX_CASHITEM_GIFT_RECVHISTORY_REQ,  // ���� ���� ����Ʈ ��û : y(n) m(c) d(c)
	MSG_EX_CASHITEM_GIFT_RECVHISTORY_REP,  // ����				: errorcode(uc) count(n) ctid(n) sendcharName(str)
	MSG_EX_CASHITEM_GIFT_RECVLIST_REQ,	   // ���� ���� ����Ʈ ��û
	MSG_EX_CASHITEM_GIFT_RECVLIST_REP,		// ����				: listflag(c) count(n) idx(n) ctid(n) date(un) sendcharName(str) msg(str)
	MSG_EX_CASHITEM_GIFT_RECV_REQ,			// ���� �ޱ�		: count(n) idx(n) ctid(n)
	MSG_EX_CASHITEM_GIFT_RECV_REP,			// ���� �ޱ�		: errCode(uc)
	MSG_EX_CASHITEM_GIFT_NOTICE,			// ������ �����Ͽ����ϴ�
	// <----------->  �����ý��� ����
	MSG_EX_CASHITEM_CUPON_REQ ,	// ���� ���� ����Ʈ ��û   
	MSG_EX_CASHITEM_CUPON_REP,	// ���� ���� ����Ʈ ����  : error code(n) ���� ���� ��(n) { ���� �̸�(str), ����ID(n), ���� �ݾ�(n) } ...
	MSG_EX_CASHITEM_PURCHASE_WITH_COUPON_REQ ,	// �������� ���� �ϱ� : ����ID(n) Count(n) { ctid(n) }...
	MSG_EX_CASHITEM_PURCHASE_WITH_COUPON_REP, 	// �������� �����ϱ� ���� : error code(c) cashBalance(n)
	// <----------->  �����ý��� ��
	
	// MSG_EX_CASHITEM_TYPE_LIST_REQ,		// cash first subtype �� second subtype list ��û
	MSG_EX_CASHITEM_TYPE_LIST_REP,		// cash first subtype �� second subtype list ���� 
										// : first subtype start(uc), Count(n), firstsubType(n) * Count
										// second subtype start(uc), Count(n), secondsubType(n) * Count
	MSG_EX_CASHITEM_LIST_REQ,			// cash shop page(1 page per 8 goods) ��û // Search type(n), Req_page(n)
	MSG_EX_CASHITEM_LIST_REP,			// Search type(n), catalog count(uc), [CTID(n), Remain_count(n), Price(n)]*catalog count,
										// current page(n), total page(n)
	MSG_EX_CASHITEM_RECOMMAND_REQ,		// category(n)
	MSG_EX_CASHITEM_RECOMMAND_REP,		// catalog count(uc) [CTID(n),Remain_count(n),Price(n)] * catalog count
	MSG_EX_CASHITEM_WISHLIST_REQ,		// �Ҹ�����(wish list) �� ��û
	MSG_EX_CASHITEM_WISHLIST_REP,
	MSG_EX_CASHITEM_SHOP_OPEN_REQ,		// SHOP Open message
	MSG_EX_CASHITEM_WISHLIST_SAVE_REQ,	// �Ҹ����� ��ǰ ��� ��û
	MSG_EX_CASHITEM_WISHLIST_SAVE_REP,
	MSG_EX_CASHITEM_WISHLIST_DEL_REQ,	// �Ҹ����� ��ǰ ���� ��û
	MSG_EX_CASHITEM_WISHLIST_DEL_REP,
	MSG_EX_CASHITEM_SHOP_LOCK,		// (39) ĳ�������� ���� ��
	MSG_EX_CASHITEM_SHOP_UNLOCK,		// (40) ĳ�������� ���� ���
} MSG_EX_CASHITEM_TYPE;

typedef enum _tagExCashItemMoonstoneErrorType
{
	MSG_EX_CASHITEM_MOONSTONE_ERROR_SUCCESS,				// ���������� ����
	MSG_EX_CASHITEM_MOONSTONE_ERROR_NOITEM,					// ��ȯ�� �������� �����ϴ�.
	MSG_EX_CASHITEM_MOONSTONE_ERROR_INVEN,					// �κ��丮�� �����մϴ�
	MSG_EX_CASHITEM_MOONSTONE_ERROR_CANTUSE_CASHMOON,		// ĳ�� �������� ����Ҽ� �ִ� �������� �ƴմϴ�.
} MSG_EX_CASHITEM_MOONSTONE_ERROR_TYPE;

typedef enum __tagMsgExCashItemErrorType
{
	MSG_EX_CASHITEM_ERROR_SUCCESS,				// ����
	MSG_EX_CASHITEM_ERROR_LACKCASH,				// ����ĳ�� ����
	MSG_EX_CASHITEM_ERROR_NOTUSER,				// �ش����� ����
	MSG_EX_CASHITEM_ERROR_NOTITEM,				// �������� �ʴ� ��ǰ�Դϴ�
	MSG_EX_CASHITEM_ERROR_DB,					// DB����
	MSG_EX_CASHITEM_ERROR_PACKET,				// ��Ŷ ����
	MSG_EX_CASHITEM_ERROR_ETC,					// ��Ÿ ����
	MSG_EX_CASHITEM_ERROR_OVERITEM,				// ���� ��ǰ ���� �ʰ�(10��)
	MSG_EX_CASHITEM_ERROR_NOSPACE,				// ���Ź�ǰ �������� ���� ����
	MSG_EX_CASHITEM_ERROR_LACKINVEN,			// �ɸ��� �κ� ����
	MSG_EX_CASHITEM_ERROR_CONN,					// Ŀ���� ���� ����
	MSG_EX_CASHITEM_ERROR_BILL,					// ���� ���� ����
	MSG_BILLITEM_ERROR_NOTACCOUNT	= 12,		// ���� ���� ���� 
	MSG_EX_CASHITEM_ERROR_NOTHAVECT,			// ���� ������ ǰ�� wooss 060516 for platinum item
	MSG_EX_CASHITEM_ERROR_GIFT_WRONGCHAR,		// �����ÿ� �ش� �ɸ��Ͱ� �����ϴ�
	MSG_EX_CASHITEM_ERROR_GIFT_SUCCESS,			// ���������� ����
	MSG_EX_CASHITEM_ERROR_GIFTRECV_SUCCESS,		// ���� ���� ��ǰ���� �κ��丮�� �Ű�����
	MSG_EX_CASHITEM_ERROR_GIFT_NOCTID,			// ���� ��ǰ�� �����ϴ�
	MSG_EX_CASHITEM_ERROR_CANT_GIFT,			// �̺�Ʈ ��ǰ�� ������ �Ұ����մϴ�.
} MSG_EX_CASHITEM_ERROR_TYPE;

typedef enum __tagMsgExNamechangeErrorType
{
	MSG_EX_NAMECHANGE_ERROR_SUCCESS,		// ����
	MSG_EX_NAMECHANGE_ERROR_DUPLICATE,		// �ߺ��̸�
	MSG_EX_NAMECHANGE_ERROR_HELPER,			// ���� ���� ����
	MSG_EX_NAMECHANGE_ERROR_INVALID,		// �߸��� �Է�
	MSG_EX_NAMECHANGE_ERROR_NOTGUILDBOSS,	// ������� �ƴ�
	MSG_EX_NAMECHANGE_ERROR_PARTY,			// ��Ƽ�߿��� �̸��� ������ �� �����ϴ�.
} MSG_EX_NAMECHANGE_ERROR_TYPE;

typedef enum __tagMsgExPetLearnErrorType
{
	MSG_EX_PET_LEARN_ERROR_OK,		// ����
	MSG_EX_PET_LEARN_ERROR_WEAR,	// �� ������
	MSG_EX_PET_LEARN_ERROR_POINT,	// �������Ʈ ����
	MSG_EX_PET_LEARN_ERROR_LEVEL,	// ���� ����
	MSG_EX_PET_LEARN_ERROR_ITEM,	// ������ ����
	MSG_EX_PET_LEARN_ERROR_AUTO,	// �ڵ� �����
} MSG_EX_PET_LEARN_ERROR_TYPE;

typedef enum __tagMsgExPetChangeMountErrorType
{
	MSG_EX_PET_CHANGE_MOUNT_ERROR_OK,		// ����
	MSG_EX_PET_CHANGE_MOUNT_ERROR_LEVEL,	// ���� ����
	MSG_EX_PET_CHANGE_MOUNT_ERROR_WEAR,		// �������
	MSG_EX_PET_CHANGE_MOUNT_ERROR_GRADE,	// �̹� ����Ʈ Ÿ���� ��
	MSG_EX_PET_CHANGE_MOUNT_ERROR_JOB,  // ����Ʈ�� �Ҽ� ���� �����Դϴ�.
} MSG_EX_PET_CHANGE_MOUNT_ERROR_TYPE;

extern struct ErrorTable MessageTypes;

//0524 kwon �߰�.
typedef enum _tagMsgMemposPlusType
{
	MSG_EX_MEMPOSPLUS_LIST,		// ������ ����Ʈ ����	: count(uc) [slot(c) zone(n) x(f) z(f) comment(str)] �ݺ� busetime(n)
	MSG_EX_MEMPOSPLUS_WRITE,	// ������ ����		: slot(c) comment(str) zone(n) x(f) z(f)
	MSG_EX_MEMPOSPLUS_MOVE,		// ��� ��ҷ� �̵�		: slot(c)
} MSG_MEMPOSPLUS_TYPE;

// ���� �޽��� ����
typedef enum __tagMsgFailType
{
	// �Ϲ�
	MSG_FAIL_MANY_CONNECT,					// ���� ��û�� ����
	MSG_FAIL_WRONG_VERSION,					// ���� ����
	MSG_FAIL_WRONG_CHAR,					// �߸��� ���� ����
	MSG_FAIL_WRONG_PASSWORD,				// ��ȣ�� �߸��� ���� ����
	MSG_FAIL_ALREADY_CONNECT,				// �̹� ������ ���̵� (�� ������ �� ����)
	MSG_FAIL_CONNECT_SERVER,				// ���� ����
	MSG_FAIL_BLOCK_CHAR,					// ĳ���� ����
	MSG_FAIL_CHECK_CHAR,					// ���� ����
	MSG_FAIL_SYSTEM_ERROR,					// �ý��� ����
	MSG_FAIL_NOT_EXIST_CHAR,				// ĳ���� ����

	// �����ͺ��̽� ����
	MSG_FAIL_DB_ALREADY_NAME,				// �ߺ��� �̸�
	MSG_FAIL_DB_NEW_CHAR,					// �� ĳ���� ���� ����
	MSG_FAIL_DB_FULL_CHAR,					// ���Կ� ���ڸ� ����
	MSG_FAIL_DB_NOT_EXIST_CHAR,				// �ش� ���Կ� ĳ�� ����
	MSG_FAIL_DB_UNKNOWN,					// �˼����� ����

	// ���� ����
	MSG_FAIL_BILLING_NOT_PAY,				// �̿� ���� Ȯ�� �ȵ�
	MSG_FAIL_BILLING_NOT_RIGHT,				// ��� ���� ����
	MSG_FAIL_BILLING_TIME_OUT,				// ���� �Ⱓ ������ ����
	MSG_FAIL_BILLING_ALREADY_CONNECT,		// �ߺ� ���� (�ټ��� ������ ���� ��)
	MSG_FAIL_BILLING_OVER_IP,				// ���ӹ� ��� ���� ������ ���� �ʰ�
	MSG_FAIL_BILLING_TIME_NOT_ENOUGH,		// ���� �Ⱓ ����
	MSG_FAIL_BILLING_TIME_OUT_DISCONNECT,	// ���� �ð� ����
	MSG_FAIL_BILLING_OTHER,					// �׿�
	MSG_FAIL_BILLING_WRONGPW,				// ���̵� �н����� ����
	MSG_FAIL_BILLING_BLOCKED,				// ���� ����


	// �޽��� ����
	MSG_FAIL_MSGR_TIMEOUT_WHISPER,			// �ӼӸ� Ÿ�� �ƿ�
	MSG_FAIL_MSGR_NOT_FOUND_CHAR,			// �Ӹ� ��ȭ ��밡 ����

	// �α伭�� ����
	MSG_FAIL_LOGIN_SERVER,					// ���� ����
	MSG_FAIL_LOGINSERV_MANY_CONNECT,		// ���� ��û�� ����
	MSG_FAIL_LOGINSERV_WRONG_VERSION,		// ���� ����
	MSG_FAIL_LOGINSERV_WRONG_CHAR,			// �߸��� ���� ����
	MSG_FAIL_LOGINSERV_WRONG_PASSWORD,		// ��ȣ�� �߸��� ���� ����
	MSG_FAIL_LOGINSERV_ALREADY_CONNECT,		// �̹� ������ ���̵� (�� ������ �� ����)
	MSG_FAIL_LOGINSERV_BLOCK_CHAR,			// ĳ���� ����
	MSG_FAIL_LOGINSERV_CHECK_CHAR,			// ���̵�/��ȣ Ʋ��
	MSG_FAIL_LOGINSERV_SYSTEM_ERROR,		// �ý��� ����
	MSG_FAIL_LOGINSERV_NOT_EXIST_CHAR,		// ĳ���� ����
	MSG_FAIL_LOGINSERV_NO_SERVICE,			// ���� �Ⱓ�� �ƴ�
	
	MSG_FAIL_WRONG_IDENTIFICATION,			// �ֹι�ȣ Ʋ��
	//�׽�Ʈ ����
	MSG_FAIL_TEST_WRONG,					// Test �޼���  ��,���� �̵� ����
	MSG_NOT_IN_ZONE,						// ĳ���Ͱ� ���� ����
	MSG_FAIL_ENABLE_AREA,					// Enable area msg error
	MSG_FAIL_CANNT_ENABLE_AREA,				// area can't enable msg error

	MSG_FAIL_LOGINSERV_NOT_ADULT,			// �̼����ڴ� �����Ҽ� ���� �ð��Դϴ�
	MSG_FAIL_NOTLEVEL_FORDELETE,			// ����� �ִ� ������ �ƴ� 

	MSG_FAIL_DB_DELETE_DELAY_CHAR,			// ���� ��� ĳ���ͷ� ���� ���� ��û��

	MSG_FAIL_SCARD_NOT_MATCHING,			// ���� ī�� ���� ����

	MSG_FAIL_LOGINSERV_BLOCK_USER,			// �н�����3�� Ʋ���� ����
	MSG_FAIL_LOGINSERV_EMAIL_SENT,				// email verify pwesty

	MSG_FAIL_LOGINSERV_BLOCK_ACCOUNT,		// ��������
	MSG_FAIL_LOGINSERV_USE_SECURE_SYSTEM,	// ��ȭ���� �ý��� ���
	MSG_FAIL_CANNOT_CREATE_NS,				// ���������� �����ʾ� ĳ���͸� ���� �� �� �����ϴ�.
	MSG_FAIL_DOESNOT_LASTCHAOSID,			// ��Ʈī������ ID�� �������� �ʽ��ϴ�.	
	MSG_FAIL_CANNOT_CONNECT_UNDER_FIFTEEN,  // ���� ���� �޼���(15�� ���� ���� ����)
	MSG_FAIL_CANNOT_CONNECT_SOUTH_AMERICA,		// �������� ���� ����.
	MSG_FAIL_CANNOT_CONNECT_SHUTDOWN_TIME,		// (54)�˴ٿ� �ð� ���� ���� "ID���� �˴ٿ��� ���� ��� �������� Ȯ�εǾ� ���� ������ �Ұ��� �մϴ�.(00:00~06:00) ���ǻ����� �����������ͷ� ���� �ֽʽÿ�.
	MSG_FAIL_DB_CANNOT_DEL_CHAR,			// [2012/07/05 : Sora]  ĳ���� ���� Ȯ�� (���� Ȯ�� ����� ĳ���� ���� �Ұ�) (55)
	MSG_TIME_OUT,							// �ð� �ʰ�
	MSG_FAIL_END_MSG,
} MSG_FAIL_TYPE;


// �α��� ����
typedef enum __tagMsgLoginType
{
	MSG_LOGIN_NEW,				// ó�� ����
	MSG_LOGIN_RE,				// ���� �̵�
	MSG_LOGIN_GM,				// GMTOOL ����
} MSG_LOGIN_TYPE;


// �޴� ����
typedef enum __tagMsgMenuType
{
	MSG_MENU_NEW,				// NEW CHARACTER		: mode(uc) name(str) job(c) hairstyle(c) facestyle(c)
	MSG_MENU_DEL,				// DELETE CHARACTER		: mode(uc) index(n) ident(str) bcanceldelete(c)
								// ident				: �ֹι�ȣ
								// bcanceldelete		: ���� ��ҽ� 1, ������ 0
	MSG_MENU_START,				// START				: mode(uc) index(n)
	MSG_RETURN_TO_SELECT_CHANNEL,	// ĳ���� ����â���� ��������â���� �̵� �Ѵٴ� ��Ŷ.
} MSG_MENU_TYPE;


// �̵� ����
typedef enum __tagMsgMoveType
{
	MSG_MOVE_WALK,				// �ȱ�
	MSG_MOVE_RUN,				// �ٱ�
	MSG_MOVE_PLACE,				// ��ǥ
	MSG_MOVE_STOP,				// ����
	MSG_MOVE_FLY,				// [2012/08/22 : Sora] ����
} MSG_MOVE_TYPE;


// ĳ���� ���� ����
typedef enum __tagMsgCharType
{
	MSG_CHAR_UNKNOWN = -1,		// �� �� ����
	MSG_CHAR_PC = 0,			// �÷��̾� ĳ����
	MSG_CHAR_NPC,				// NPC
	MSG_CHAR_PET,				// �ֿϵ���
	MSG_CHAR_ELEMENTAL,			// ������Ż ��ȯ��
	MSG_CHAR_WILDPET			// ������ ��
} MSG_CHAR_TYPE;


// DB ���� �޽���
typedef enum __tagMsgDBType
{
	MSG_DB_SUCCESS,				// ��û ó�� ����			: 
	MSG_DB_OK,					// ĳ���� ���� �б� ����	: zone(n)
	MSG_DB_CHAR_EXIST,			// ĳ���� ����				: index(n) name(str) job(c) job2(c) hair(c) face(c) level(n) exp(ll) needexp(ll) sp(n) hp(n) maxHP(n) mp(n) maxMP(n) [wearing_index(n) wearing_plus(n)]:6 deletedelayremain(n)
								// deletedelay : time_t�� ���, 0�� �ƴϸ� ���� ����� ĳ����, 0�̸� �Ϲ� ĳ����
	MSG_DB_CHAR_END,			// ĳ���� ���� ��			: slot1remain(n) slot2remain(n) seed(n)
	MSG_DB_OTHER_SERVER,		// �ٸ� ���� ���� ĳ��		: zone(n) ip(str) port(n)

	MSG_DB_NSCREATE,			// NS Creatable [11/6/2009 rumist]
	MSG_DB_CHAR_SLOT_TIME,		// [2012/07/05 : Sora]  ĳ���� ���� Ȯ�� ������ ���� ����
} MSG_DB_TYPE;


// ä�ð���
typedef enum __tagMsgChatType
{ // UIChatting.h�� Ŭ���̾�Ʈ������ ChattingMsgType���� enum���� �����Ͽ� ���
	MSG_CHAT_SAY,				// �Ϲ� ä��
	MSG_CHAT_PARTY,				// ��Ƽ ��ȭ
	MSG_CHAT_GUILD,				// ��� ��ȭ
	MSG_CHAT_TRADE,				// �Ÿ� ��ȭ
	MSG_CHAT_WHISPER,			// �Ϳ���
	MSG_CHAT_SHOUT,				// ��ġ��
	MSG_CHAT_NOTICE,			// ��� �˸� �޽��� : ���� �� ���� ��� ĳ������ ����
	MSG_CHAT_GM,				// ��� ä��
	MSG_CHAT_MESSENGER,			// �޽��� ü��
	MSG_CHAT_LOAD,				// ���� ���� : // ���� ���� �۾� 2005-09-01 �̱�ȯ 
	MSG_CHAT_RANKER,   // ��Ŀ ��
	MSG_CHAT_RANKER_CONN,  // ��Ŀ ���� job(c) name(str)
	MSG_CHAT_NOTICE_SERVERDOWN = 12,	// ���� �ٿ� �޽��� 060420
	
	MSG_CHAT_GM_WHISPER,		// GM_TOOL �޽��� Ÿ��(������) WSS_GMTOOL 070517
	MSG_CHAT_GM_SAY,			// GM_TOOL �޽��� Ÿ��(������)
	MSG_CHAT_GMTOOL =15,			// GM_TOOL �޽��� Ÿ��(Ŭ���̾�Ʈ��)

	MSG_CHAT_NOTICE_PRESSCORPS,		// ���ڴ� ����
	MSG_CHAT_EXPEDITION,			// ������
	MSG_CHAT_NPCNOTICE,				// NPC ����
	MSG_CHAT_CHANNEL_LEVEL,			// ä�� ���� ä��
	MSG_CHAT_CHANNEL_TRADE = 20,			// ä�� �Ÿ� ä��
} MSG_CHAT_TYPE;

typedef enum __tagMsgMoneyType
{
	MSG_MONEY_COUNT = 0,	//���� ��ȭ : count(ll) change_count(ll)
} MSG_MONEY_TYPE;

// ������ ����
typedef enum __tagMsgItemType
{
	MSG_ITEM_USE,				// ������ ���		: tab_idx(uc) row_idx(uc) col_idx(uc) item_idx(n)
	MSG_ITEM_TAKE,				// ������ �ݱ�		: char_idx(n) item_idx(n)
	MSG_ITEM_THROW,				// ������ ������	: tab_idx(uc) row_idx(uc) col_idx(uc) item_idx(n) count(ll)
	MSG_ITEM_ARRANGE,			// ������ ����		: tab_idx(uc)
	MSG_ITEM_DELETE,			// ������ ����		: tab_idx(uc) row_idx(uc) col_idx(uc) item_idx(n) count(ll)
	MSG_ITEM_WEAR,				// ������ ����		: wear_pos(uc) tab_idx1(uc) row_idx1(uc) col_idx1(uc) item_idx1(n) tab_idx2(uc) row_idx2(uc) col_idx2(uc) item_idx2(n)
	MSG_ITEM_WEAR_TAKE_OFF,		// ������ ����
	MSG_ITEM_SWAP,				// ������ ��ġ ����	: tab_idx(uc) row_idx1(uc) col_idx1(uc) row_idx2(uc) col_idx2(uc)
	MSG_ITEM_ADD,				// ������ ����		: tab_idx(uc) row_idx(uc) col_idx(uc) item_idx(n) item_db_idx(n) wear_pos(uc) plus(n) flag(n) count(ll) option_count(c) [option_type(c) option_level(c)] socketcreatecount(c) socketcount(c) [optionindex(n) optionlevel(c)]
	MSG_ITEM_UPDATE,			// ������ ����		: tab_idx(uc) row_idx(uc) col_idx(uc) item_idx(n) plus(n) flag(n) count(ll) change_count(ll) option_count(c) [option_type(c) option_level(c)] socketcreatecount(c) socketcount(c) [optionindex(n) optionlevel(c)]
	MSG_ITEM_DROP,				// ������ ���		: item_idx(n) item_db_idx(n) count(ll) x(f) z(f) h(f) r(f) ylayer(n) char_type(uc) char_index(n)
	MSG_ITEM_APPEAR,			// ������ �þ� ��	: item_idx(n) item_db_idx(n) count(ll) x(f) z(f) h(f) r(f) ylayer(n)
	MSG_ITEM_DISAPPEAR,			// ������ �þ� ��	: item_idx(n)
	MSG_ITEM_BUY,				// ������ ����		: npc_idx(n) price(ll) item_count(n) item_db_idx(n) count(ll)....�ݺ�
	MSG_ITEM_SELL,				// ������ �Ǹ�		: npc_idx(n) price(ll) item_count(n) tab_idx(uc) row_idx(uc) col_idx(uc) count(ll)...�ݺ�
	MSG_ITEM_REMOVE_PRS_REQ,
	MSG_ITEM_UPGRADE_REQ,		// ������ ���� ��û	: row_idx1(uc) col_idx1(uc) plus(n) row_idx2(uc) col_idx2(uc) level(n)
	MSG_ITEM_UPGRADE_REP,		// ������ ���� ����	: result(uc)
	MSG_ITEM_REFINE_REQ,		// ���ü� ��ȯ ��û : row(uc) col(uc)
	MSG_ITEM_REFINE_REP,		// ���ü� ��ȯ ���� : result(uc)
	MSG_ITEM_TRANSMOGRIFY_REQ,
	MSG_ITEM_TRANSMOGRIFY_REP,
	MSG_ITEM_OPEN_BOX_REQ,
	MSG_ITEM_OPEN_BOX_REP,
	MSG_ITEM_SEAL_COMPOSE_REQ,
	MSG_ITEM_SEAL_COMPOSE_REP,
	MSG_ITEM_EXTEND_MENU_REQ,
	MSG_ITEM_EXTEND_MENU_REP,
	MSG_ITEM_OPTION_ADD_REQ,	// ������ �ɼ� ��û : row_idx1(uc) col_idx1(uc) wear_pos(c) row_idx2(uc) col_idx2(uc)
	MSG_ITEM_OPTION_ADD_REP,	// ������ �ɼ� ��� : result(uc)
	MSG_ITEM_OPTION_DEL_REQ,	// ������ �ɼ� ��û : row_idx1(uc) col_idx1(uc) wear_pos(c) row_idx2(uc) col_idx2(uc)
	MSG_ITEM_OPTION_DEL_REP,	// ������ �ɼ� ��� : result(uc)
	MSG_ITEM_PROCESS_REQ,		// ������ ���� ��û : use_row_idx(uc) use_col_idx(uc) make_db_idx(n) material_count(n) [tab(uc) row(uc) col(uc) count(ll)].. �ݺ�
	MSG_ITEM_PROCESS_REP,		// ������ ���� ��� : result(uc)
	MSG_ITEM_MAKE_REQ,			// ������ ���� ��û : use_row_idx(uc) use_col_idx(uc) make_db_idx(n) material_count(n) [tab(uc) row(uc) col(uc) count(ll)].. �ݺ�
	MSG_ITEM_MAKE_REP,			// ������ ���� ��� : result(uc)
	MSG_ITEM_MIX_REQ,			// ������ ���� ��û : [use_row_idx(uc) use_col_idx(uc)].. �ݺ�
	MSG_ITEM_MIX_REP,			// ������ ���� ��� : result(uc)
	MSG_ITEM_GET,				// ������ ������(ǥ��)	: char_name(str) item_db_idx(N) item_count(ll)
	MSG_ITEM_ARCANE_REQ,		// ����� ���� ��û		: use_row_idx(uc) use_col_idx(uc) row_idx1(uc) col_idx1(uc) row_idx2(uc) col_idx2(uc) row_idx3(uc) col_idx3(uc)
	MSG_ITEM_ARCANE_REP,		// ����� ���� ���		: result (uc)
	MSG_ITEM_CHANGEWEAPON_REQ,	// ���� ��ȯ ��û		: row(c) col(c) itemindex(n) changetype(n)
	MSG_ITEM_CHANGEWEAPON_REP,	// ���� ��ȯ ����		: old_itemdbindex(n) new_itemdbindex(n)
								// ���� ���ڶ�� ��� old == -1
								// �߸��� ��ȯ�� ��û�ϸ� new == -1
	MSG_ITEM_PROCESS_NPC,		// NPC�� ���� ����		: processItemDBIndex(n) count(n) errcode(n:s)
	MSG_ITEM_ADD_BOOSTER,		// ���� ������ �ν��� ���� : flag(n)
								// Ŭ���̾�Ʈ->����		: �ν��� ������ ���� �ε���
								// ����->Ŭ���̾�Ʈ		: �����ڵ�
	MSG_ITEM_MIX_WARITEM,		// ���� ������ ����		: Ŭ���̾�Ʈ -> ����	: row_type1(c) col_type1(c) row_type2(c) col_type2(c) row_type3(c) col_type3(c)
								//						: ���� -> Ŭ���̾�Ʈ	: errcode(n)
	MSG_ITEM_USE_PROLONG,		// c->s ������ ���Ⱓ ����	: tab_idx(uc) row_idx(uc) col_idx(uc) item_idx(n) extra1(n)
								// s->c						?	: item_idx(n)
	MSG_ITEM_USE_ERROR,			// ��Ȱ�ֹ������� ����: errorcode(c)	wooss 050818 ������ ��� ����
	MSG_ITEM_LEND_WEAPON,		// ���� �뿩			: itemdbindex(n) errorcode(n:s)

	MSG_ITEM_LEVELDOWN,			// ���� �ж�		   :  row1(c) col1(c) row2(c) col2(c)
								// MSG_ITEM_LEVELDOWN_ERROR_TYPE : errorcode(n)
	MSG_ITEM_TARGET,			// Ÿ���ϴ� ������ ��� : tab_idx(c) row_idx(c) col_idx(c) item_idx(n) chartype(c) charindex(n)
	
	MSG_ITEM_EXCHANGE_EQUIP_REQ,	// ���� ��ȯ ��û		: row(c) col(c) itemindex(n) changetype(n)
	MSG_ITEM_EXCHANGE_EQUIP_REP,	// ���� ��ȯ ����		: old_itemdbindex(n) new_itemdbindex(n)

	MSG_ITEM_USE_GROCERY_BUY,  // ��ȭ�� �������� �̿��� ������ ���� : price(ll) item_count(n) item_db_idx(n) count(ll)....�ݺ�
 
	MSG_ITEM_USE_GROCERY_SELL,  // ��ȭ�� �������� �̿��� ������ �Ǹ� : price(ll) item_count(n) tab_idx(c) row_idx(c) col_idx(c) count(ll)...�ݺ�
	MSG_ITEM_USE_WARPDOC,		// �̵��ֹ��� ����ϱ� zone(n), npcidx(n) 

	MSG_ITEM_USE_PRESSCORPS,	// ��ī���ڴ� Ȯ���� subtype(c) >> item_idx(n) >> msg(str)
	MSG_ITEM_CHECK_COMPOSITION,	// ���վ����� ��ũ ������ ã��  REQ <�ڽ�Ƭ> : (c)row , (c)col, (n)item_index REP <��ũ> : (c)row, (c)col, (n) item_index
	MSG_ITEM_WEAR_COSTUME,		// �ڽ�Ƭ ������ �Ա�/����(48)	: wear_pos(uc), wear_item_unique_idx(n), wear_item_db_idx(n), takeoff_item_unique_idx(n), takeoff_item_db_idx(n)
	MSG_ITEM_WEAR_COSTUME_TAKEOFF,
	MSG_ITEM_WEAR_COSTUME_SUIT, // �ѹ��ǻ� �Ա�/���� added by sam 11/02/01 [SAM]
	MSG_ITEM_WEAR_COSTUME_SUIT_TAKEOFF,
	MSG_ITEM_LETSPARTY_USE,		// ��Ƽ ���� ������ ���� �޽���ó��. [4/21/2011 rumist]
	MSG_ITEM_MASTERSTONE_USE,	// ������ ���� ���

	MSG_ITEM_USE_CHAR_SLOT_EXT, // [2012/07/05 : Sora]  ĳ���� ���� Ȯ�� ������
	MSG_ITEM_USE_CHAR_MOVE,		// ĳ���� �̵� ������ ��� ���� [7/19/2012 rumist]
	MSG_ITEM_COSTUME_SUIT_FORTUNE,	// [2013/02/13] sykim70 Fortune System
									// ��û: sbTab, sbRow, sbCol : �κ��丮 tab, row, col
									// ����: nRet, nItemIndex, nSkillIndex, nSkillLevel
									//       nRet	0 - ���� �ο��ޱ� ����
									//				1 - �������� ����
									//				2 - ������ Ÿ�� ����
									//				3 - ���� ��� ���� ����
									//				4 - ���� ������ ���� ����
									//				5 - �̹� ���� ����
	MSG_ITEM_AMOUNT,				// ������ ���� ����
	MSG_ITEM_DIVIDE,				// ������ ������
	MSG_ITEM_SORT_INVENTORY,
	MSG_ITEM_EXCHANGE,			// ������ ��ȯ (61)
	MSG_ITEM_COMPOSE,			// ������ �ռ�
	MSG_ITEM_UPGRADE_PET,		// �� ������ ��ȭ
	MSG_ITEM_END_MSG,			// MSG_ITEM_TYPE ������ �޽���

} MSG_ITEM_TYPE;

typedef enum _tagItemLendWeaponErrorType
{
	MSG_ITEM_LEND_WEAPON_ERROR_OK,				// ���� �뿩 : ����
	MSG_ITEM_LEND_WEAPON_ERROR_FULLINVEN,		// ���� �뿩 : �κ� ���� ����
	MSG_ITEM_LEND_WEAPON_ERROR_NOMONEY,			// ���� �뿩 : ������ ����
	MSG_ITEM_LEND_WEAPON_ERROR_FAIL,			// ���� �뿩 : ���� ( �߸��� DB �ε��� ��û�� Ŭ���̾�Ʈ ���� )
	MSG_ITEM_LEND_TIMEOUT,						// ���� �뿩 : ����
} MSG_ITEM_LEND_WEAPON_ERROR_TYPE;	

typedef enum _tagItemUseErrorType
{
	MSG_ITEM_USE_ERROR_REVIVAL_EXP,			// ��Ȱ �ֹ��� ������ ����ġ ���� �ֹ��� ��� �Ҽ� ����
	MSG_ITEM_USE_ERROR_REVIVAL_SP,			// ��Ȱ �ֹ��� ������ ���õ� ���� �ֹ����� ����Ҽ� ����
	MSG_ITEM_USE_ERROR_SUMMON_NOTALLOWZONE, // �ǽ����̹Ƿ� ���� ���� �ֹ����� ����Ҽ� ����
	MSG_ITEM_USE_ERROR_EXP_SP,				// ����ġ �ֹ��� ������ ���õ� ��� ����
	MSG_ITEM_USE_ERROR_SP_EXP,				// ���õ� ������ ����ġ ��� ����.
	MSG_ITEM_USE_ERROR_PLATINUM_SPECIAL,	// �÷�Ƽ�� ���ü� ������ �Ϸ� 
	MSG_ITEM_USE_ERROR_PLATINUM_SPECIAL_EXPIRE, // ���Ⱓ�� ���� �Ǿ ȿ���� �����
	MSG_ITEM_USE_ERROR_EXPUP,				// ������ ������ ������Դϴ�. �׷��� ����Ͻðڽ��ϱ�?
	MSG_ITEM_USE_ERROR_IDENTIFY_RARE_OK,	// ���� ������ �ɼ� Ȯ�� ����
	MSG_ITEM_USE_ERROR_IDENTIFY_RARE_FAIL,	// ���� ������ �ɼ� Ȯ�� ����
	MSG_ITEM_USE_ERROR_WARN_PARTYRECALL,	// ���� �� ���� �������� ��Ƽ���� ���� �Ϻ� ���� �ȵ��� ���
	MSG_ITEM_USE_ERROR_SUMMON_GUARD,		// ��ȯ���� ���� ��� ��ȯ ������ ���� 
	MSG_ITEM_USE_ERROR_FLYING,    // �����߿��� ����� �� �����ϴ�.
	MSG_ITEM_USE_ERROR_PARTY_OR_EXPED,		// ��Ƽ�� ������ ���¿��� ����� �� �����ϴ�.  13
	MSG_ITEM_USE_ERROR_RAIDZONE,			// ������ ���̵� �� ���� ����� �� �����ϴ�.   14
	MSG_ITEM_USE_ERROR_LOWLEVEL,			// ������ ���Ƽ� ����� �� �����ϴ�.
	MSG_ITEM_USE_ERROR_NS_CARD_USE_OK,		// NS ���� ī�� ��� ����. [11/6/2009 rumist]
	MSG_ITEM_USE_ERROR_NS_CARD_INSUFF,		// NS ����ī�� ��� ���� ���� ���� [11/6/2009 rumist]
	MSG_ITEM_USE_ERROR_DUPLICATE,			// ȣĪ ������ �ߺ������� ��� ���� 2009-12-16 finwell added
	// ���� �ձ� �ѹ� �� ���� ī�� �����۰��� �߰��Ǵ� �κ�
	MSG_ITEM_USE_ERROR_SOCKET_CARD_USE_OK,		// ���� �ձ� �ѹ� �� ���� ī�� ��� ����
	MSG_ITEM_USE_ERROR_NOT_SELECT,			// [sora] GUILD_MARK
	MSG_ITEM_USE_ERROR_NOITEM,				// [sora] GUILD_MARK
	MSG_ITEM_USE_ERROR_CANNOT_USE_ZONE,		// ������ ��� �Ұ��� ����. [4/26/2011 rumist]
	MSG_ITEM_USE_ERROR_CANNOT_USE_COMP,		// (23) �����ֹ����� ��� �Ͻ� �� ���� �����Դϴ�.
	MSG_ITEM_USE_ERROR_DUP_COMP_PREFINE,	// (24) �÷�Ƽ�� ���ü��� �����ֹ����� �ߺ��Ͽ� ��� �Ͻ� �� �����ϴ�.
	MSG_ITEM_USE_ERROR_EXT_CHAR_SLOT,		// [2012/07/05 : Sora]  ĳ���� ���� Ȯ�� ������ (25)
	MSG_ITEM_USE_ERROR_DEATH_PENALTY,		// [2012/08/10 : Sora] ��Ȱ �ֹ��� �ÿ�� ������ �г�Ƽ�� ���� ���(26)
	MSG_ITEM_USE_ERROR_GUARDIAN,			// [2012/12/05 : Sora] �İ��� ���谡 ���� ��� ������ ��� �Ұ�(27)
	MSG_ITEM_USE_ERROR_EXPIRE_CASH_INVEN,	// ĳ���κ� ����.
	MSG_ITEM_USE_DO_NOT_MEET_CONDITION,		// ������ ��� ���ǿ� �������� ���ϴ�.
	MSG_ITEM_USE_PVP_PROTECT_SUCCESS,		// PVP ������ ��� ����
	MSG_ITEM_USE_TOO_FAR_DISTANCE,			// �Ÿ��� �ٴϴ�.
	MSG_ITEM_NOT_CORRECT_PET_TYPE,
} MSG_ITEM_USE_ERROR_TYPE;

typedef enum _tagItemMixWarItemErrorType
{
	MSG_ITEM_MIX_WARITEM_ERROR_OK,			// ���� ����
	MSG_ITEM_MIX_WARITEM_ERROR_NOTFOUND,	// ��� ����
} MSG_ITEM_MIX_WARITEM_ERROR_TYPE;

typedef enum _tagMSG_ITEM_LEVELDOWN_ERROR_TYPE	// ���� �϶� �ֹ���
{
	MSG_ITEM_LEVELDOWN_ERROR_OK,			// ����
	MSG_ITEM_LEVELDOWN_ERROR_ALREADY,		// �̹� ���� �϶�
	MSG_ITEM_LEVELDOWN_ERROR_NOEQUIP,		// ��� �ƴ�
	MSG_ITEM_LEVELDOWN_ERROR_SCROLL,		// �ֹ��� �ƴ�
}MSG_ITEM_LEVELDOWN_ERROR_TYPE;

typedef enum _tagItemAddBoosterErrorType
{
	MSG_ITEM_ADD_BOOSTER_ERROR_OK,		// ����
	MSG_ITEM_ADD_BOOSTER_ERROR_USED,	// ������ ����
	MSG_ITEM_ADD_BOOSTER_ERROR_ALREADY,	// �̹� �پ� ����
} MSG_ITEM_ADD_BOOSTER_ERROR_TYPE;

typedef enum _tagProcessNPCErrorType
{
	MSG_ITEM_PROCESS_NPC_ERROR_OK,		// ����
	MSG_ITEM_PROCESS_NPC_ERROR_FAIL,	// ����
	MSG_ITEM_PROCESS_NPC_ERROR_COUNT,	// ī��Ʈ ����
	MSG_ITEM_PROCESS_NPC_ERROR_NOHAVE,	// ��� ����
	MSG_ITEM_PROCESS_NPC_ERROR_MONEY,	// ���� ����
} MSG_ITEM_PROCESS_NPC_ERROR_TYPE;

typedef enum _tagProcessResult
{
	MSG_PROCESS_FAIL_SYSTEM,			// �־�� �ȵǴ� ������ ����
	MSG_PROCESS_FAIL_MATERIAL,			// ��� ���� ����
	MSG_PROCESS_FAIL_NO_SSKILL,			// ���� ��ų ����
	MSG_PROCESS_FAIL_OVER_WEIGHT,		// ���� �ʰ��� ���� ���� ����
	MSG_PROCESS_FAIL_PROB,				// Ȯ�� ����
	MSG_PROCESS_SUCCESS,				// ���� ����
} MSG_ITEM_PROCESS_RESULT;

typedef enum _tagMakeResult
{
	MSG_MAKE_FAIL_SYSTEM,				// �־�� �ȵǴ� ������ ����
	MSG_MAKE_FAIL_MATERIAL,				// ��� ���� ����
	MSG_MAKE_FAIL_NO_SSKILL,			// ���� ��ų ����
	MSG_MAKE_FAIL_ITEM_LEVEL,			// ���� ��ų�� ���� �Ұ��� ������ (����)
	MSG_MAKE_FAIL_OVER_WEIGHT,			// ���� �ʰ��� ���� ���� ����
	MSG_MAKE_FAIL_PROB,					// Ȯ�� ����
	MSG_MAKE_SUCCESS,					// ���� ����
} MSG_ITEM_MAKE_RESULT;

typedef enum _tagItemMixResult
{
	MSG_MIX_FAIL_SYSTEM,				// �־�� �ȵǴ� ����
	MSG_MIX_FAIL_REMAKEBOX,				// ��Ȱ�� ���� ���� ����
	MSG_MIX_FAIL_ACCESSORY,				// ���� �Ǽ��縮 ������ ���� ����
	MSG_MIX_SUCCESS,					// ���� ����
} MSG_ITEM_MIX_RESULT;

typedef enum _tagItemArcaneResult
{
	MSG_ARCANE_FAIL_SYSTEM,				// �־�� �ȵǴ� ����
	MSG_ARCANE_FAIL_ARCANEBOX,			// ����� ���� ���� ����
	MSG_ARCANE_FAIL_MATERIAL,			// ��� ���� ���� (��ᰡ ��ġ�� ���ų� ������)
	MSG_ARCANE_FAIL_UPGRADE,			// ���ü� ����
	MSG_ARCANE_FAIL_ACCESSORY,			// �Ǽ��縮 ����
	MSG_ARCANE_FAIL_SAMPLE,				// �÷� ����
	MSG_ARCANE_SUCCESS,					// ���� ����
} MSG_ITEM_ARCANE_RESULT;

typedef enum _tagItemOptionAddResult
{
	MSG_OPTION_ADD_ERROR_SYSTEM,		// �־�� �ȵǴ� ����
	MSG_OPTION_ADD_ERROR_WEAR,			// ������ �����۾����
	MSG_OPTION_ADD_ERROR_KIND,			// ���⳪ ���� �����ϴ�
	MSG_OPTION_ADD_ERROR_ENABLE,		// �ɼ��� ���� �� �ִ� �������� �ƴϴ�
	MSG_OPTION_ADD_ERROR_MAX,			// �ִ� �ɼ� �� �ʰ�
	MSG_OPTION_ADD_SUCCESS,				// �ɼ� ���̱� ����
	MSG_OPTION_BLOOD_SWEAT_FRUIT_ADD_SUCCESS //�ǿ� ���� ������ ����Ͽ� ������ �ɼ� ���̱⿡ ����
} MSG_ITEM_OPTION_ADD_RESULT;

typedef enum _tagItemOptionDelResult
{
	MSG_OPTION_DEL_ERROR_SYSTEM,		// �־�� �ȵǴ� ����
	MSG_OPTION_DEL_ERROR_WEAR,			// ������ �����۾����
	MSG_OPTION_DEL_ERROR_KIND,			// ���⳪ ���� �����ϴ�
	MSG_OPTION_DEL_ERROR_NUM,			// �ɼ�3�� �̻� �־�� ����� �ִ�
	MSG_OPTION_DEL_SUCCESS,				// �ɼ� ����� ����
} MSG_ITEM_OPTION_DEL_RESULT;

typedef enum _tagItemComposeErrortype
{
	MSG_ITEM_COMPOSE_ERROR_OK,			//����
	MSG_ITEM_COMPOSE_ERROR_NOT_RESULT,	//���ǿ� �����ϴ� �������� ����
	MSG_ITEM_COMPOSE_ERROR_NOT_ENOUGH_MAT,	//��� ����
	MSG_ITEM_COMPOSE_ERROR_NOT_ENOUGH_NAS,	//���� ����
	MSG_ITEM_COMPOSE_ERROR_FAIL,		//�ռ� ����
};

typedef enum _tagItemExtendMenuErrortype
{
	MSG_ITEM_EXTEND_MENU_OK,
	MSG_ITEM_EXTEND_MENU_ERROR_NOCONDITION,
	MSG_ITEM_EXTEND_MENU_ERROR_NO_ITEM,
	MSG_ITEM_EXTEND_MENU_ERROR_WRONG_TYPE,
	MSG_ITEM_EXTEND_MENU_ERROR_WEARING,
	MSG_ITEM_EXTEND_MENU_ERROR_COUNT,
} MSG_ITEM_EXTEND_MENU_ERROR_TYPE;

typedef enum _tagItemTransmogrifyErrortype
{
	MSG_ITEM_TRANSMOGRIFY_OK,
	MSG_ITEM_TRANSMOGRIFY_ERROR_NOCONDITION,
	MSG_ITEM_TRANSMOGRIFY_ERROR_WRONG_TYPE,
	MSG_ITEM_TRANSMOGRIFY_ERROR_WEARING,
	MSG_ITEM_TRANSMOGRIFY_ERROR_NO_MONEY,
} MSG_ITEM_TRANSMOGRIFY_ERROR_TYPE;

typedef enum _tagItemOpenBoxErrortype
{
	MSG_ITEM_OPEN_BOX_OK,
	MSG_ITEM_OPEN_BOX_NOSPACE,
	MSG_ITEM_OPEN_BOX_ERROR,
} MSG_ITEM_OPEN_BOX_ERROR_TYPE;

typedef enum _tagItemSealComposeErrortype
{
	MSG_ITEM_SEAL_COMPOSE_OK,
	MSG_ITEM_SEAL_COMPOSE_NOSPACE,
	MSG_ITEM_SEAL_COMPOSE_ERROR_AMOUNT,
	MSG_ITEM_SEAL_COMPOSE_ERROR,
} MSG_ITEM_SEAL_COMPOSE_ERROR_TYPE;

//0803
typedef enum _tagMsgSysType
{
	MSG_SYS_WHISPER_NOTFOUND,		// �Ӹ� ��� ����		:
	MSG_SYS_TIMEOUT,				// Ÿ�� �ƿ� �߻�		:
	MSG_SYS_CANNOT_WEAR,			// ���� ����			:
	MSG_SYS_FULL_INVENTORY,			// �κ��丮 ���� ��		: tab_index(c)
	MSG_SYS_CUSTOM,					// Ŀ���� �޽���		: msg(str)
	MSG_SYS_SHORT_MONEY,			// �� ���� ������		:
	MSG_SYS_SHOP_CANCEL,			// ���� �ŷ� ���		:
	MSG_SYS_EXCHANGE_NOTFOUND,		// ��ȯ ��� ����		:
	MSG_SYS_EXCHANGE_ALREADY,		// �̹� ��ȯ ��			:
	MSG_SYS_NOT_OWNER_ITEM,			// ������ �켱���� ����
	MSG_SYS_OVER_WEIGHT,			// ���԰� ���� ����
	MSG_SYS_UPGRADE_NOCONDITION,	// ������ �ȸ¾� ���׷��̵� ���� (�Ϲ����ü� ������ ���� ����)
	MSG_SYS_MAKE_REFINE_KIND,		// ���⳪ ���� �ƴ� �ٸ��� ���ü����� ��ȯ�Ϸ��� ��
	MSG_SYS_MAKE_REFINE_WEARING,	// �԰� �ִ� ���������� ���ü� ��ȯ �Ұ���
	MSG_SYS_MAKE_REFINE_PLUS,		// Plus ���� ���õǾ� �ִ� ������ ���ü� ��ȯ �Ұ���
	MSG_SYS_MEMPOS_CANT_WRITE,		// ��� ��� ��ġ ��� �Ұ��� ��
	MSG_SYS_LAYERDUNGEON_FULL,		// ���̾� �� ���� ���� ���� �Ұ�
	MSG_SYS_CANT_WARP_STATE,		// �̵� ��ġ �Ұ��� : ĳ���� ����(���/�ɱ�/��ų����/��Ƽ��û/��ȯ)
	MSG_SYS_CANT_WARP_OTHER,		// �̵� ��ġ �Ұ��� : �ٸ���ġ�̿�
	MSG_SYS_MEMPOS_OTHERZONE,		// �ٸ� �����δ� ��� ��� �̵� �Ұ�
	MSG_SYS_SINGLEDUNGEON_FULL,		// �̱۴��� �� ����
	MSG_SYS_MAKE_REFINE_SHORT,		// ���ü� ���鶧 �� ������
	MSG_SYS_PRODUCE_NOTOOL,			// ���굵���� ����
	MSG_SYS_PRODUCE_WEAR_TOOL,		// ���굵���� �����Ͻÿ�
	MSG_SYS_PRODUCE_MATCH_TOOL,		// �´� ���굵���� �����Ͻÿ�
	MSG_SYS_PRODUCE_MAXUSE_TOOL,	// ���굵�� �� ����
	MSG_SYS_PRODUCE_MAX_ACCEPTABLE,	// ���� ���� �ο� �ʰ�
	MSG_SYS_PRODUCE_NO_SSKILL,		// �ش��ϴ� ���� ��ų�� ����!!
	MSG_SYS_PROCESS_DOC_NOT_SSKILL,	// �������� ���µ� ������ų�� ����
	MSG_SYS_WARNING_WEIGHT,			// ���� �ʰ� ���
	MSG_SYS_BLOODITEM,				// ������ �ɼ� ���� ����	: itemdbindex(n)
	MSG_SYS_MAKE_REFINE_CANNOT,		// ��� �������� ���ü� ��ȯ �Ұ���
	MSG_SYS_PKMODE_LIMITLEVEL,		// PK ������ �Ұ����� ����
	MSG_SYS_CANTCHAT_INVISIBLE,		// �κ����� ���¿����� �Ϲ� ä�� �Ұ�
	MSG_SYS_SHORT_FAME,				// ����ġ ����.
	MSG_SYS_FRIEND_NOTFOUND,		// ��ȭ��븦 ã�� �� ����. 
	MSG_SYS_UPGRADE_CANT_SUPERSTONE,// �ʰ��� ���ü��� �̹� ����� ������
	MSG_SYS_UPGRADE_CANT_14LEVEL,   // 14���� �����ۿ��� �ʰ��� ���ü��� ������
	MSG_SYS_FAME_NOT_ENOUGH,		// ����ġ �����ؼ� �ʰ��� ���ü� ���޹��� ����
	MSG_SYS_INVEN_NOT_ENOUGH,		// �κ��� �������� �ʰ��� ���ü� ���޹��� ����
	MSG_SYS_NO_MORE_SUPERSTONE,		// ���̻� �ʰ��� ���ü��� ���޹��� ����(7�� �� ���� ����)
	MSG_SYS_CAN_RECEIVE_SUPERSTONE, // Ư�� ����ġ�� �����ؼ� �ʰ��� ���ü��� ������ ����.
	MSG_SYS_APPEAR_NOVICE,			// �ʺ��ڰ� ��������.
	MSG_SYS_NOTICE,					// ���ӳ� �̺�Ʈ ����  <-- NEW
	MSG_SYS_MEMPOS_CASTLE,			// �������߿��� ������������ ���̵� �Ұ�
	MSG_SYS_PET_CANT_SUMMON,		// ��ȯ �Ұ��� ����
	MSG_SYS_PET_CANT_MOUNT,			// ����Ʈ �Ұ��� ����
	MSG_SYS_PRODUCE_NO_MONEY,		// ����� ���� �Ұ�
	MSG_SYS_PRODUCE_CANNT_BOOST,	// �ν��ͷδ� ���� ���� �Ұ�
	MSG_SYS_INVALID_CHAR,			// �߸��� ���ڰ� ���ԵǾ����ϴ� 050830
	MSG_SYS_CANNOT_DUPLICATION,		// ������ �ߺ� ��� �Ұ� : new_item(n) cur_item(n)
	MSG_SYS_UPGRADE_CANT_6LEVEL_LUCKY, // ����� ���ü��� 6�̻��� �����ۿ� �߸��� ����. //wooss 051024
	MSG_SYS_PET_NOT_HAVE_ONEMORE,	// �ϳ� �̻��� ���� �����Ҽ� �����ϴ�.
	MSG_SYS_TARGET_PKLIMITLEVEL,	// Ÿ���� PVP ������ ���� �ʾƼ� �����Ҽ� ����
	MSG_SYS_NOT_ADULT,				// ������ �ƴϸ� 10�ÿ� �����Ѵ� �޼���
	MSG_SYS_NOTTIME_GOZONE,			// ������ �̵��Ҽ� �ִ� �ð��� �ƴմϴ�.
	MSG_SYS_CANNOT_WEAR_DEADPET,	// 060221 : bs : ����� �� ���� �Ұ� : petindex(n) remainRebirth(n)
	MSG_SYS_ITEMCOMPOSITED,			// ������ �ռ� ����
	MSG_SYS_EXPIRE_ITEMCOMPOSITE,	// ������ �ռ� ���� : itemdbindex(n)
	MSG_SYS_CANNOT_RESET_MOUNT,		// �� ����Ʈ Ÿ�� ��� �Ұ�
	MSG_SYS_RESET_MOUNT,			// �� ����Ʈ Ÿ�� ���
	MSG_SYS_CANNOT_SEPARATE_ITEM,	// ���յ� �ǻ��� �ƴ� ������ �и� ��û��
	MSG_SYS_SEPARATE_ITEM,			// ���յ� �ǻ� ���� : itemdbindex(n)
	MSG_SYS_RAIDMOB_REGEN,			// ���̵� ���� ���� �˸� : npcdbindex(n) x(f) z(f)
	MSG_SYS_TIMEOUT_LUCKY_ACCESSORY,// ��Ű �Ǽ����� ���Ⱓ ���� : itemdbindex(n)
	MSG_SYS_CHANGE_LUCKY_BOX,		// ��Ű ��ο� ���� ��ȯ ���� : itemdbindex(n)	
	MSG_SYS_CANNOT_HAVE_DUPLICATE,	// �ߺ��ؼ� ���� �� �� ���� ������
	// wooss 070307 -------------------------------------------------------------------->><<
	// kw : WSS_WHITEDAY_2007
	MSG_SYS_MATCHSEX,				// ������ ���� �ʽ��ϴ�.  [3/8/2007 KwonYongDae]

	MSG_SYS_MEMPOSPLUS_OPEN,		// �����̾� �޸𸮺� ����
	MSG_SYS_PKMODE_CANDO,			// PK�� ������ ������ �Ǿ����ϴ�.
	MSG_SYS_NO_AUTO_ITEM,			// ����Ҽ� �ִ� ������ �����ϴ�.
	MSG_SYS_EGEHA_MINLEVEL,			// ������ �̵��Ҽ� �ִ� �ּҷ���
	MSG_SYS_IRISPOINT_ALARM,		// ���̸��� �Ŵ��� %d �� ȹ���Ͽ����ϴ�. (n)Count	
	MSG_SYS_FACTORY_EXP,			// ���õ��� xxx����Ͽ����ϴ�. (ll)sealskill_exp
	MSG_SYS_CHANGE_RAID_BOX,		// ���̵� ���� ��ȯ ���� : itemdbindex(n) 						(���̵� �߰�)
	MSG_SYS_CANNOT_DESTROY,			// �ı� �Ұ����� ������.
	MSG_SYS_TITLE_EXPIRED,			// ȣĪ �Ⱓ���� �޼���(76)
	MSG_SYS_IRISPOINT_DROPMEDAL,	// 1�ð��� ����Ǿ� ���̸��� �޴��� ����˴ϴ�.
	MSG_SYS_CANNOT_GOZONE_LEVEL,	// �̵��Ҽ��ִ������Ƿ������ǰ��ٸ��ϴ�.
	MSG_SYS_COSTUME2_ITEM_EXPIRED,	// �ڽ�Ƭ2 ������ �Ⱓ�� ����Ǿ����ϴ�. : item_db_idx(uc)
	MSG_SYS_TRANSLATE_START,		// �꺯�Ž���
	MSG_SYS_CANT_MOUNT_EVOCATION,	// (81)������ ����Ʈ �Ұ���
	MSG_SYS_CANT_MAKE_PET_EVOCATION, // (82)������ �� Ż�� ����� ����.
	MSG_SYS_FULL_INVENTORY_AND_DROP, // �κ��丮�� �������� �������� �����
	MSG_SYS_ENTER_RAID_ZONE_REMAIN,       // (84) %d�� �� ���̵� ������ �ʱ�ȭ �˴ϴ�. (���� �޽���)
	MSG_SYS_RAID_RESET_COMPLETE,          // (85) ���̵� ���� �ʱ�ȭ�� �Ϸ�Ǿ����ϴ�. (���� �޽���)
	MSG_SYS_NO_ENTER_RAID_ZONE,           // (86) ���̵� ���� �ʱ�ȭ ���Դϴ�. (���� �޽���) 
	MSG_SYS_GMCOMMAND_NOTICE,		// GM Command(kick, ä�ñ���) ��� ��, ��ü ���� : Command Type(uc), GM Name(str), User Name(str)
	MSG_SYS_PET_CANT_MOUNT_ETC,		// ����Ʈ�� �Ұ����մϴ�.(����Ʈ ������ ������ ���� �ƴ� ��)	// �� ž�� �Ұ� ó��. [5/18/2011 rumist]
	MSG_SYS_DUP_PREFINE_COMPOSITE,	//  (89) �÷�Ƽ�� ���ü��� �����ֹ����� �ߺ��Ͽ� ��� �Ͻ� �� �����ϴ�.
	MSG_SYS_NPC_PORTAL_EXPIRED = 93, //���� NPC��Ż ��ũ�� ������ �ð� ���� [8/22/2012 Ranma]
	MSG_SYS_NOT_EXIST_NPC,			// NPC�� �������� ����
	MSG_SYS_NOT_ENOUGH_MONEY,		//2013/04/09 jeil ���� ������ ���� (5902)���� ������ �ִ� ���� ���� ���� ������ ��ȯ �� �� �����ϴ�.
	MSG_SYS_DO_NOT_ATTACK_IMMOTAL,	// ����� ���� ��� �����̹Ƿ� ���� �� �� �����ϴ�.
	MSG_SYS_DO_NOT_ATTACK_DO_MOVE,	// ���� ���� ��� �����̹Ƿ� ������ �Ŀ� ���� �� �� �ֽ��ϴ�.
	MSG_SYS_DO_NOT_CHANGE_PK_MODE,	// pk���� ��ȯ�� �� �����ϴ�.	
	MSG_SYS_DO_NOT_SYSTEM_NOT_EQ_RVRTYPE,	//�ٸ� ����� ������ ��� �� �� ���� �ý���.
	MSG_SYS_DO_NOT_PARTY_THISZONE,	// �� �������� ��Ƽ �ý����� ����� �� �����ϴ�.
	MSG_SYS_DO_NOT_USE_DURING_IMMORTAL,			// �������� ���¿����� ����� �� �����ϴ�.
	MSG_SYS_DO_NOT_USE_ITEM_STATE,	//�������� ����� �� �ִ� ���°� �ƴմϴ�.
	MSG_SYS_DO_NOT_GO_ZONE_GMORDER,	//��� ���ɾ�δ� �̵��� �� �����ϴ�.
	MSG_SYS_DO_NOT_PLAY_PVP,		// PVP�� �� �� ���� �����Դϴ�.
	MSG_SYS_DO_NOT_ATTACK_PROTECT_PVP, // PVP��ȣ �����̹Ƿ� ������ �� �����ϴ�.
	MSG_SYS_PVP_PROTECT_ITEM_END,	// PVP��ȣ ������ ���Ⱓ�� ����Ǿ� PVP�� ������ ���°� �Ǿ����ϴ�.
	MSG_SYS_AREADY_USE,				// �̹� ����� �Դϴ�.
	MSG_SYS_WAR_BUF_NOT_IN_ZONE,	// ���� ������ ����� ����ȿ���� ������ϴ�.
	MSG_SYS_WAR_BUF_END_WAR,		// ���� �ð��� ���� �Ǿ� ����ȿ���� ������ϴ�.
	MSG_SYS_ARTIFACT_DONT_IN_DUNGEON, //���� �������� ������ ���·� ������ ���� �� �� �����ϴ�.
	MSG_SYS_ARTIFACT_PVP_GET_ITEM,	// PVP�� �Ұ����� ĳ���ʹ� ���� �������� ȹ�� �� �� �����ϴ�.
	MSG_SYS_ARTIFACT_ITEM_DELETE_EVENT_OFF,	//�̺�Ʈ�� ����Ǿ� �������� �����
	MSG_SYS_ARTIFACT_ITEM_DO_NOT_USE_PVPPROTECT,	//���� �������� ���� �ִ� ���¿����� PVP��ȣ���и� ����� �� �����ϴ�.
	MSG_SYS_ARTIFACT_USE_PVPPROTECT,	//PVP��ȣ ���и� ������Դϴ�.
	MSG_SYS_SUMMON_TOTEM_NPC, 
	MSG_SYS_NOT_CONDITION_ITEM_ALL_USER,	// �������� ȹ���� �� �ִ� ������ �����ϴ�.
	MSG_SYS_BELONG_ITEM,					// �ͼӵǾ� �ִ� ������ �Դϴ�.
	MSG_SYS_REZA = 123,
	MSG_SYS_BOSS_DEAD,
	MSG_SYS_PLAYER_DEAD,
	MSG_SYS_BOSS_REGEN,
	MSG_SYS_EVENT_SUMMON_NPC_DEAD,
	MSG_SYS_NOT_ENCHANTED_FOREST,
	MSG_SYS_FLAG_PICKUP,
	MSG_SYS_FLAG_DEAD,
	MSG_SYS_FLAG_DC,
	MSG_CASH_ZONE_FAG,
					// MSG_SYS_TYPE�� ������ �޽���
	MSG_SYS_CANNOT_USE_LETSPLAY_RUNE,
    MSG_SYS_PROMO_KEY_INVALID,
	MSG_SYS_PROMO_KEY_EXPIRED,
	MSG_SYS_PROMO_KEY_ALREADY_USE,
	MSG_SYS_PROMO_KEY_ADDED_TO_INVENTORY,
	MSG_SYS_PROMO_KEY_ADDED_TO_STASH,
	MSG_SYS_DONATION_MAIL_REWARD,
	MSG_SYS_END_MSG,
} MSG_SYS_TYPE;

typedef enum _tagMsgExchangeType
{
	MSG_EXCHANGE_REQ,			// ��ȯ �ൿ 		: req_type(uc) src_index(n) src_name(str) dest_index(n) dest_name(str)
	MSG_EXCHANGE_ITEM,			// ������ ���/����	: action(uc) item_index(n) item_db_index(n) plus(n) flag(n) used(n) used_2(n) count(ll)
								// COMPOSITE_TIME ���� used_2(n) �߰�
} MSG_EXCHANGE_TYPE;

typedef enum _tagMsgExchangeReqType
{
	MSG_EXCHANGE_REQ_REQ,			// ��ȯ ��û	
	MSG_EXCHANGE_REQ_REP,			// ��ȯ ����
	MSG_EXCHANGE_REQ_REJECT,		// ��ȯ ����/���
	MSG_EXCHANGE_REQ_REJECT_SRC,	// ��ȯ ����/��� - ��û�� ���
	MSG_EXCHANGE_REQ_REJECT_DEST,	// ��ȯ ����/��� - ��û���� ���
	MSG_EXCHANGE_REQ_READY,			// �غ� �Ϸ�
	MSG_EXCHANGE_REQ_READY_SRC,		// �غ� �Ϸ� - ��û�� ���
	MSG_EXCHANGE_REQ_READY_DEST,	// �غ� �Ϸ� - ��û���� ���
	MSG_EXCHANGE_REQ_FULL_SRC,		// �κ��丮 ���� - ��û�� ���
	MSG_EXCHANGE_REQ_FULL_DEST,		// �κ��丮 ���� - ��û���� ���
	MSG_EXCHANGE_REQ_OK,			// Ȯ��
	MSG_EXCHANGE_REQ_OK_SRC,		// Ȯ�� - ��û�� ���
	MSG_EXCHANGE_REQ_OK_DEST,		// Ȯ�� - ��û���� ���
	MSG_EXCHANGE_REQ_SRC_PET_ANYMORE,		// �� ���� ���� - ��û�� ���
	MSG_EXCHANGE_REQ_DEST_PET_ANYMORE,		// �� ���� ���� - ��û���� ���
} MSG_EXCHANGE_REQ_TYPE;

typedef enum _tagMsgExchangeItemAction
{
	MSG_EXCHANGE_ITEM_ADD,			// ������ �߰� - ��� �ʵ� ���
	MSG_EXCHANGE_ITEM_ADD_SRC,		// ������ �߰� - ��û�� ���, ��� �ʵ� ���
	MSG_EXCHANGE_ITEM_ADD_DEST,		// ������ �߰� - ��û���� ���, ��� �ʵ� ���
	MSG_EXCHANGE_ITEM_DEL,			// ������ ���� - ACTION/ITEM INDEX/COUNT
	MSG_EXCHANGE_ITEM_DEL_SRC,		// ������ ���� - ��û�� ���, ACTION/ITEM INDEX/COUNT ���
	MSG_EXCHANGE_ITEM_DEL_DEST,		// ������ ���� - ��û���� ���, ACTION/ITEM INDEX/COUNT ���
	MSG_EXCHANGE_ITEM_UPDATE_SRC,	// ������ ���� ���� - ��û�� ���, ACTION/ITEM INDEX/COUNT ���
	MSG_EXCHANGE_ITEM_UPDATE_DEST,	// ������ ���� ���� - ��û���� ���, ACTION/ITEM INDEX/COUNT ���
} MSG_EXCHANGE_ITEM_ACTION;

typedef enum _tagMsgMemposType
{
	MSG_MEMPOS_LIST,			// ������ ����Ʈ ����	: count(uc) [slot(c) zone(n) x(f) z(f) comment(str)] �ݺ� busetime(n)
	MSG_MEMPOS_WRITE,			// ������ ����		: slot(c) comment(str) zone(n) x(f) z(f)
	MSG_MEMPOS_MOVE,			// ��� ��ҷ� �̵�		: slot(c)
} MSG_MEMPOS_TYPE;

typedef enum _tagMsgEnvType
{
	MSG_ENV_TAX_CHANGE,			// ���� ����	: zone(n) sellrate(n) buyrate(n)
	MSG_ENV_WEATHER,			// ���� ����	: weather(n)
	MSG_ENV_TIME,				// �ð� �˸�	: year(n) mon(c) day(c) hour(c) min(c) sec(c)
} MSG_ENV_TYPE;

typedef enum _tagMsgGMType
{
	MSG_GM_WHOAMI,				// ��� ���� Ȯ�� : level(uc)
	MSG_GM_COMMAND,				// ��� ����	: command(str)
} MSG_GM_TYPE;

typedef enum _tagMsgPartyType
{
	MSG_PARTY_INVITE,			// ��Ƽ �ʴ�			: party_type(c) src_index(n) src_name(str) : Ŭ���̾�Ʈ���� ������ �ö��� dest�� ����
	MSG_PARTY_ALLOW,			// �ʴ� ����			: 
	MSG_PARTY_REJECT,			// �ʴ� ����/��� ��û	: 
	MSG_PARTY_REJECT_SRC,		// �ʴ� ����/��� ����	: 
	MSG_PARTY_REJECT_DEST,		// �ʴ� ����/��� ����	: 
	MSG_PARTY_ADD,				// ��Ƽ�� �߰�			: is_boss(c) char_index(n) char_name(str) job(c) job2(c) level(n) cur_hp(n) max_hp(n) cur_mp(n) max_mp(n) x(f) z(f) ylayer(c) zone(n)
	MSG_PARTY_QUIT,				// ��Ƽ Ż��			: char_index(n)
	MSG_PARTY_KICK,				// ��Ƽ�� �߹�			: char_index(n)
	MSG_PARTY_END,				// ��Ƽ ��ü			: 
	MSG_PARTY_MEMBER_INFO,		// ��Ƽ�� ����			: char_index(n) level(n) cur_hp(n) max_hp(n) cur_mp(n) max_mp(n) x(f) z(f) h(f) r(f) ylayer(c) zone(n)
	MSG_PARTY_ERROR,			// ��Ƽ ���� ����		: errorcode(c)
	MSG_PARTY_ASSISTINFO,		// ��Ƽ�� ���� ȿ�� ����: char_index(n) assist_state(n:s) assist_count(c:s) [itemidx(n:s) index(n:s) level(c:s) remain(n:s)]:count
	MSG_PARTY_CHANGEBOSS,		// ��Ƽ�� ����	C->S	: charname(str)
								// S->C			        : bossname(str) newbossindex(n) newname(str) bmandate(c)
	MSG_PARTY_EMPTY,			// ��Ƽ ����			: 
	MSG_PARTY_CHANGETYPE,		// ��Ƽ ���� ����		: party_type(c)
	MSG_PARTY_ENDPARTY_REQ,		// ��Ƽ ���� ��û
	MSG_PARTY_ENDPARTY_START,  // ��Ƽ ��ü ���� �˸�(20�� �Ŀ�)
	MSG_PARTY_INZONE_CLEAR_REQ, // ��Ƽ �ν���Ʈ �� �ʱ�ȭ
	MSG_PARTY_INZONE_CLEAR_REP,  // ��Ƽ �ν���Ʈ �� �ʱ�ȭ ����
	MSG_PARTY_TYPEINFO,						// ��ƼŸ�� ���� 
} MSG_PARTY_TYPE;

typedef enum _tagMsgPartyErrorType
{
	MSG_PARTY_ERROR_NOTFOUND,			// ����� ����			:
	MSG_PARTY_ERROR_ALREADY_ME,			// ���� �̹� ��Ƽ ��	:
	MSG_PARTY_ERROR_FULL,				// ��Ƽ ������			:
	MSG_PARTY_ERROR_ALREADY_TARGET,		// ����� �̹� ��Ƽ ��	:
	MSG_PARTY_ERROR_ALREADY_REQUEST,	// �̹� ��Ƽ ��û ��	:
	MSG_PARTY_ERROR_DIFF_TYPE,			// ��Ƽ ���°� Ʋ��		:
	MSG_PARTY_ERROR_NOT_BOSS,			// ��Ƽ���� �ƴ϶� ���� �Ұ�
	MSG_PARTY_ERROR_INVALID_LEVEL,      // ������ ���� �ʾ� ��Ƽ �Ұ�
	MSG_PARTY_ERROR_NOT_PARTY,			// ��Ƽ���� �ƴմϴ�
	MSG_PARTY_ERROR_NOT_PARTY_MEMBER,	// ��Ƽ���� �ƴմϴ�.
	MSG_PARTY_ERROR_PVP,				// PVP �߿��� ��Ƽ �Ұ�
	MSG_PARTY_ERROR_INZONECLEAR_FAIL,	// ���� Ŭ���� ����
	MSG_PARTY_ERROR_DO_NOT_CHANGE_BOSS,	// [090728: selo] ���� �޺� �߿� ��Ƽ�� ���� �Ұ�
	MSG_PARTY_ERROR_LEVEL_CHANGE_BOSS,	// ������ ���� �ʾ� ��Ƽ�� ������ �� �� �����ϴ�.
	
} MSG_PARTY_ERROR_TYPE;

typedef enum _tagMsgQuickSlotType
{
	MSG_QUICKSLOT_LIST,			// ������ ����Ʈ		: page(uc) [slottype(c) skilltype(n) or actiontype(n) or  row(c) col(c)] 10ȸ�ݺ�
	MSG_QUICKSLOT_ADD,			// ������ �߰�, ����	: page(uc) slot(uc) slottype(c) skilltype(n) or actiontype(n) or row(c) col(c)
	MSG_QUICKSLOT_SWAP,			// ������ ����			: page(uc) slotNum1(uc) slotNum2(uc)
} MSG_QUICKSLOT_TYPE;

typedef enum _tagMsgSkillType
{
	MSG_SKILL_LIST,				// ��ų ����Ʈ			: count(n) [skill_index(n) skill_level(c)] * count
	MSG_SKILL_LEARN,			// ��ų ����			: skill_index(n) is_new(uc) skill_level(c)
	MSG_SKILL_READY,			// ��ų ����			: char_type(c) char_index(n) skill_index(n) target_type(c) target_index(n) skillspeed(n)
	MSG_SKILL_FIRE,				// ��ų �ߵ�			: char_type(c) char_index(n) skill_index(n) target_type(c) target_index(n) count(n) [target_type(c) target_index(n)] * count skillspeed(n) movechar(c) x(z) z(f) h(f) r(f) y(c)
	MSG_SKILL_CANCEL,			// ��ų ���			: char_type(c) char_index(n)
	MSG_SKILL_LEARN_ERROR,		// ���� ���� �߻�		: errorcode(uc)
	MSG_SKILL_ERROR,			// ��ų ���� ����		: errorcode(c) skillindex(n) extraInfo(n)
	MSG_SKILL_AUTO_USE,		// ��ų �ڵ� ����û C->S: skillindex(n)
	MSG_SKILL_NEWYEAR_2008,		// 2008�� �ų� �̺�Ʈ ��ų : charindex1(n), charindex2(n)
	MSG_SKILL_HANARO_EVENT,  // �ϳ��� ���� �̺�Ʈ( �ʺ� ������ ��ų)
	MSG_SKILL_LEARN_SEAL,		// ������ ���� ��ų ����
	MSG_SKILL_SOUL,				// ���� ��ȥ�� ����		: soulCount(n)           11����
	MSG_SKILL_MIDLEVEL_SUPPORT,		// �������� ������ ��ų
	MSG_SKILL_HIGHLEVEL_SUPPORT,		// ������ ������ ��ų
	MSG_SKILL_USEEP,				// EP�� �̿��� ��ų ���
	MSG_SKILL_ERROR_NOT_EXIST_NPC,	// NPC�� �ʹ� ��
	MSG_SKILL_RESET_COOLTIME,		// ��Ÿ�� �ʱ�ȭ
	MSG_SKILL_TOGGLE,				// ��� On/Off
	MSG_SKILL_REMOVE_BUFF,
	#ifdef ARENA_TIME_SYSTEM
	MSG_SKILL_PVP_BUFF,
	#endif
	MSG_SKILL_RECOVER_HP,
} MSG_SKILL_TYPE;

typedef enum _tagMsgSkillErrorType
{
// 050401 : bs : ��ų ��� �Ұ� ����
	MSG_SKILL_ERROR_ALREADY_USE,			// �ٸ� ��ų �����
	MSG_SKILL_ERROR_NOTFOUND,				// �׷� ��ų �����
	MSG_SKILL_ERROR_NOTREADY,				// ��ų �غ� ��... ��, ���� ��ų ������ ���� ��ų ���� �ð��� �ȵǾ�����
	MSG_SKILL_ERROR_INVAL_TARGET,			// Ÿ���� �߸��Ǿ���
	MSG_SKILL_ERROR_INSUFF_HP,				// ������ ������ HP
	MSG_SKILL_ERROR_INSUFF_MP,				// ������ ������ MP
	MSG_SKILL_ERROR_INSUFF_ITEM,			// ������ ������ Item
	MSG_SKILL_ERROR_LONG,					// �־ �ȵ�
	MSG_SKILL_ERROR_INVAL_STATE_DEATH,		// ���� �Ҹ��� : �׾�� ����
	MSG_SKILL_ERROR_INVAL_STATE_WEAPON,		// ���� �Ҹ��� : ���� ���ø� ����
	MSG_SKILL_ERROR_INVAL_STATE_SITDOWN,	// ���� �Ҹ��� : �ɾƼ��� ����
	MSG_SKILL_ERROR_INVAL_STATE_PEACEZONE,	// ���� �Ҹ��� : �ǽ��� �Ұ���
	MSG_SKILL_ERROR_INVAL_STATE_STAND,		// ���� �Ҹ��� : ������ ����
	MSG_SKILL_ERROR_INVAL_STATE_SHIELD,		// ���� �Ҹ��� : ���� ������
	MSG_SKILL_ERROR_INVAL_STATE_MAGIC,		// ���� �Ҹ��� : �ʿ� ���� �����
	MSG_SKILL_ERROR_STATPOINT_STR,			// �� ����
	MSG_SKILL_ERROR_STATPOINT_DEX,			// ��ø ����
	MSG_SKILL_ERROR_STATPOINT_INT,			// ���� ����
	MSG_SKILL_ERROR_STATPOINT_CON,			// ü�� ����
	MSG_SKILL_ERROR_CANNOT_SPELL,			// ��ų ��� �Ұ��� ����
	MSG_SKILL_ERROR_TARGET_PKLIMITLEVEL,	// ��ų�� ������ �� ���� ���� ( pvp )
// --- 050401 : bs : ��ų ��� �Ұ� ����
	MSG_SKILL_ERROR_ELEMENTAL_TIME,			// ��ȯ �Ұ��� : ��ȯ�� ����� 5�е��� ��ȯ �Ұ�
	MSG_SKILL_ERROR_ELEMENTAL_FIRE,			// ��ȯ �Ұ��� : �������ɰ� �ߺ� �Ұ�
	MSG_SKILL_ERROR_ELEMENTAL_WIND,			// ��ȯ �Ұ��� : �ٶ������ɰ� �ߺ� �Ұ�
	MSG_SKILL_ERROR_ELEMENTAL_EARTH,		// ��ȯ �Ұ��� : ���������ɰ� �ߺ� �Ұ�
	MSG_SKILL_ERROR_ELEMENTAL_WATER,		// ��ȯ �Ұ��� : �������ɰ� �ߺ� �Ұ�
	MSG_SKILL_ERROR_EVOCATION_ALREADY,		// ���� �Ұ��� : �̹� ���Ż���
	MSG_SKILL_ERROR_EVOCATION_TIME,			// ���� �Ұ��� : ���� ������ 5�е��� �Ұ�

	MSG_SKILL_ERROR_CANNOT_INVISIBLE,		// ������ Ÿ���� �Ǿ� �κ�������Ƽ �Ұ���
	MSG_SKILL_ERROR_CANNOT_DEATHMOTION_ANOTHER_PC,	// 15���� �̳��� �ٸ� ������ �־� ������� �Ұ���
	MSG_SKILL_ERROR_MISS_ROGUE_SKILL,		// ���ϵ� ��� ��ų(index 125) ����
	MSG_SKILL_ERROR_COMPETITION,			// ������ ������ ��� �ð��� �ȵǾ���
	MSG_SKILL_ERROR_INVAL_STATE_DARKNESS,	// �絵����϶� ��� �Ұ� ��ų
	MSG_SKILL_ERROR_WARP_CAN_NOT_GO_THERE,		// �߰��� ���θ����ų� �� �� ���� ���̴�
	MSG_SKILL_ERROR_SOUL_COUNT_ALREADY_FULL,	// ��ȥ ���� ������ �ִ��̴�.    34
	MSG_SKILL_ERROR_CANNOT_TO_PC,			// PC���� ��� �Ұ����ϴ�.(PK ���� �Ұ���)   35
	MSG_SKILL_ERROR_DONT_HAS_SOUL,			// �̹� ��ȥ�� ���Ѱܼ� ��ȥ�� ����.	36
	MSG_SKILL_ERROR_INSUFF_GP,	 			// GP�� �����Ͽ� ��ų ����� �Ұ�����. (37)
	MSG_SKILL_ERROR_NOT_GUILD_MASTER,		// ��ų����ڰ� ��帶���Ͱ� �ƴ� (38)
	MSG_SKILL_ERROR_INVAL_STATE_PSERSONAL_DUNGEON,  // �̱� �������� ����� �� �����ϴ�.
	MSG_SKILL_ERROR_DUPLICATE,					// ������ �ߺ����
	MSG_SKILL_ERROR_CANNOT_ZONE,				// ���� �������� ����� �� �����ϴ�.
	MSG_SKILL_ERROR_NON_MSG,					// ��ų ��� ����, ���X
	//MSG_SKILL_ERROR_CANNOT_USE_AFFINITY_BOOSTER,  //ģȭ�� �ν��ʹ� �ߺ� ����� �Ұ��� �մϴ�.(40)	2012/11/13 jeil ģȭ�� �ν��� �����ư��� �߰� 
// --- 050401 : bs : ��ų ��� �Ұ� ����
} MSG_SKILL_ERROR_TYPE;

typedef enum _tagMsgAssistType
{
	MSG_ASSIST_ADD,				// ���� ��ȭ �߰�		: chartype(c) charidx(n) itemidx(n) index(n) level(c) time(n)
	MSG_ASSIST_DEL,				// ���� ��ȭ ����		: chartype(c) charidx(n) itemidx(n) index(n)
	MSG_ASSIST_LIST,			// ����Ʈ ����(�ڽſ���): state(n) count(c) [itemidx(n) index(n) level(c) time(n)]:count
	MSG_ASSIST_MODIFY,			//2012/11/12 jeil �߰� 1119���� ��ųȮ�� ����/����� ���� : chartype(c) charidx(n) itemidx(n) index(n) level(c) time(n) count(n)
} MSG_ASSIST_TYPE;

typedef enum _tagMsgEffectType
{
	MSG_EFFECT_SKILL,			// ��ų ����Ʈ			: skill_index(n) targettype(c) target_index(n)
	MSG_EFFECT_ETC,				// ��Ÿ ����Ʈ			: type(c) chartype(c) char_index(n) effect_type(uc)
	MSG_EFFECT_PRODUCE,			// ���� ����Ʈ			: type(c) chartype(c) char_index(n) target_chartype(c) target_index(n) target_hp(n)
	MSG_EFFECT_ITEM,			// ������ ��� ����Ʈ	: type(c) chartype(c) char_index(n) item_db_idx(n)
	MSG_EFFECT_FIRE,			// �ұ�� ����Ʈ		: type(c) 
} MSG_EFFECT_TYPE;

typedef enum _tagMsgEffectEtcType
{
	MSG_EFFECT_ETC_LEVELUP,				// ������ ����Ʈ
	MSG_EFFECT_ETC_GOZONE,				// Gozone ����Ʈ
	MSG_EFFECT_ETC_PRODUCE_MINING,		// ���� ���� ����Ʈ
	MSG_EFFECT_ETC_PRODUCE_GATHERING,	// �Ĺ� ���� ����Ʈ
	MSG_EFFECT_ETC_PRODUCE_CHARGE,		// ���� ���� ����Ʈ
	MSG_EFFECT_ETC_ITEM_PROCESS,		// ���� ���� ����Ʈ
	MSG_EFFECT_ETC_ITEM_MAKE,			// ���� ���� ����Ʈ
	MSG_EFFECT_ETC_MP_STEEL,			// MP ��ƿ ���� ����Ʈ
	MSG_EFFECT_ETC_HP_STEEL,			// HP ��ƿ ���� ����Ʈ
	MSG_EFFECT_ETC_FIRECRACKER,			// ���� ������ 
	MGS_EFFECT_ETC_COMPETITION,			// ������ ������ ����Ʈ
	MSG_EFFECT_ETC_RANDOM_EXP,			// ���� ����ġ ���� 
	MSG_EFFECT_ETC_RANDOM_SP,			// ���� SP ����
	MSG_EFFECT_ETC_RANDOM_DROP,			// ���� ����� ����
	MSG_EFFECT_FLAG_KILL_TARGET,
} MSG_EFFECT_ETC_TYPE;

typedef enum _tagQuestType
{
	MSG_QUEST_PC_LIST,			// ����Ʈ ����Ʈ(PC)	: quest_count(n) [quest_index(n) current_count0-2(n)] quest_count ��ŭ �ݺ�
	MSG_QUEST_REQUEST,			// ����Ʈ ��û			: npc_index(n)
	MSG_QUEST_NPC_LIST,			// ����Ʈ ����Ʈ(NPC)	: quest_count(n) [quest_index(n) flag(c)]
	MSG_QUEST_CREATE_LIST,		// ����Ʈ ����Ʈ(����)	: quest_count(n) [quest_index(n)]
	MSG_QUEST_START,			// ����Ʈ ����			: quest_index(n)
	MSG_QUEST_COMPLETE,			// ����Ʈ �Ϸ�			: quest_index(n)
	MSG_QUEST_STATUS,			// ����Ʈ ��Ȳ			: quest_index(n) current_count0-2(n)
	MSG_QUEST_PRIZE,			// ����Ʈ ����			: quest_index(n)
	MSG_QUEST_GIVEUP,			// ����Ʈ ����			: quest_index(n)
	MSG_QUEST_FAIL,				// ����Ʈ ����			: quest_index(n)
	MSG_QUEST_ERROR,			// ����Ʈ ����			: error_type(c)
	MSG_QUEST_DONE_LIST,		// ����Ϸ� ����Ʈ ����Ʈ : quest_count(n) [quest_index(n)]
	MSG_QUEST_ABANDON_LIST,		// �������� ����Ʈ ����Ʈ : quest_count(n) [quest_index(n)]
	MSG_QUEST_FORCE_GIVEUP,		// ����Ʈ ���� ����(�������� ����..) : quest_index(n)
	MSG_QUEST_UNCOMPLETE,		// ����Ʈ �Ϸ�->�̿Ϸ�	: quest_index(n)

	// �۽��� ���� 4�� �޼���
	MSG_QUEST_PD4_RANK_VIEW_REQ,		// ��ũ ���û	: charjob(c)
	MSG_QUEST_PD4_RANK_VIEW_REP,		// ��ũ ������	: multicount(c) charname(str) bclear(c) deadmon(n) time(ll)   
	MSG_QUEST_PD4_RANK_REWARD_RANK_REQ,	// ���� ���û
	MSG_QUEST_PD4_RANK_REWARD_RANK_REP,	// ���� ������	: multicount(c) charname(str) itemindex(n) itemnum(c) breward(c)
	MSG_QUEST_PD4_REWARD,				// ���� ��û
	MSG_QUEST_PD4_ERROR,

	MSG_QUEST_RANKING_SUMMON_REQ,
	MSG_QUEST_RANKING_SUMMON_REP,
	MSG_QUEST_RANKING_REBORN_REQ,
	MSG_QUEST_RANKING_REBORN_REP,
	MSG_QUEST_RANKING_PVP_REQ,
	MSG_QUEST_RANKING_PVP_REP,

	MSG_QUEST_COLLECT,			// ���� ����Ʈ			: npcserverindex(n:c,s) charindex(n:s) itemdbindex(n:s)
								// C->S�� MSG_QUEST_COLLECT�� 8�ʿ� ���� 4ȸ���� ����Ʈ �������� ������
								// itemdbindex > 0  : NPC�� ����ϰ� itemdbindex�� ������
								// itemdbindex == 0 : NPC�� ����ϰ� ������ ���� ����
								// itemdbindex < 0  : NPC�� �״�� �ְ� ������ ���� ����
	
	MSG_QUEST_RESTORE_ABANDON ,	// ���� ����Ʈ ����
	MSG_QUEST_ITEM_REQ,			// �Ϸ�� ����Ʈ ������ �ٽ� �ޱ� : nQuestIndex(n)
	MSG_QUEST_PBI_USE_REQ,
} MSG_QUEST_TYPE;

typedef enum _tagQuestListFlag
{
	MSG_QUEST_FLAG_NOT_LEVEL,		// ���� �Ұ��� : ����
	MSG_QUEST_FLAG_NOT_JOB,			// ���� �Ұ��� : ����
	MSG_QUEST_FLAG_NOT_ITEM,		// ���� �Ұ��� : ������
	MSG_QUEST_FLAG_CAN,				// ���� ����
	MSG_QUEST_FLAG_ING,				// ���� ��
	MSG_QUEST_FLAG_COMPLETE,		// ���� �Ϸ�
	MSG_QUEST_FLAG_NOT_EXP,			// ���� �Ұ��� : ����ġ ����.
	MSG_QUEST_FLAG_NOT_PREQUEST,	// ���� �Ұ��� : ���� ����Ʈ �̿Ϸ�.
	MSG_QUEST_FLAG_NOTENOUGH_AREA,	// ���� �Ұ��� : �۽��� ���� ������ ����
	MSG_QUEST_FLAG_OVERCOUNT,		// ���� �Ұ��� : �۽��� ���� ���� ���� �ʰ�
	MSG_QUEST_FLAG_NOT_PENALTY	,	// ���� �Ұ��� : ����ġ ����
} MSG_QUEST_LIST_FLAG;

typedef enum _tagMsgQuestErrorType
{
	MSG_QUEST_ERR_START_ONCE,		// ����Ʈ ���۽� ���� : �̹� ������ 1ȸ�� ����Ʈ
	MSG_QUEST_ERR_START_ALREADY,	// ����Ʈ ���۽� ���� : �̹� ��������
	MSG_QUEST_ERR_START_LEVEL,		// ����Ʈ ���۽� ���� : ���� ���� �ȸ���
	MSG_QUEST_ERR_START_JOB,		// ����Ʈ ���۽� ���� : ���� ���� �ȸ���
	MSG_QUEST_ERR_START_ITEM,		// ����Ʈ ���۽� ���� : ������ ���� �ȸ���
	MSG_QUEST_ERR_START_MAX,		// ����Ʈ ���۽� ���� : �ִ� ���� ���� �� �ʰ�
	MSG_QUEST_ERR_START_FULL,		// ����Ʈ ���۽� ���� : �̱۴����� ��� �̱۴��� ����

	MSG_QUEST_ERR_DELIVERY_FULL,	// ���� ����Ʈ �� : �κ��丮�� ������ ������ ����Ʈ ����
	MSG_QUEST_ERR_PRIZE_FULL,		// ���� ������ �κ� �� ���� ���� ����
	MSG_QUEST_ERR_PRZIE_ITEM,		// ���� ������ ������ ������ ����
	MSG_QUEST_ERR_PET_NOT_HAVE_ONEMORE,		// �� �ϳ� �̻� ���� ����
	MSG_QUEST_ERR_START_PENALTY	,	// ����Ʈ ���۽� ���� : ���Ƽ ���� �ȸ���
	MSG_QUEST_ERR_NOT_EXIST_ABANDON_QUEST,	// ���� ����Ʈ ���� ���� : ������ ����Ʈ�� ����.
	MSG_QUEST_ERR_DONT_HAVE_NAS,	// ���� ����Ʈ ���� ���� : ������ �����ϴ�.
	MSG_QUEST_ERR_NOT_EXIST_NPC,	// ������ ���డ���� NPC�� ����.
	MSG_QUEST_ERR_CHECK_DONE_ING,	// ���� ���̰ų�, �Ϸᰡ �ƴ�
	MSG_QUEST_ERR_DONT_HAVE_SPACE,

} MSG_QUEST_ERROR_TYPE;

typedef enum _tagMsgQuestPD4ErrorType
{

	MSG_QUEST_ERR_REWARD_NOT_RANK,	// ����� ��Ŀ�� �ƴ�
	MSG_QUEST_ERR_BREWARD,			// �̹� ���� �޾���

} MSG_QUEST_PD4_ERROR_TYPE;


typedef enum _tagStatPointType
{
	MSG_STATPOINT_REMAIN,			// ���� ���� ����Ʈ : statpoint_remain(n)
	MSG_STATPOINT_USE,				// ���� ����Ʈ ��� : dest_stat(uc:client,server) change_value1(int:server:�ɷ�ġ��ȭ��) change_value2(int:server:�ɷ�ġ��ȭ��) statpoint_remain(uc:server:������)
	MSG_STATPOINT_ERROR,			// ����				: errorcode(c)
	MSG_STATPOINT_RESET,			// ����Ʈ �ʱ�ȭ	: reset_str(n) reset_dex(n) reset_int(n) reset_con(n)
} MSG_STATPOINT_TYPE;


typedef enum _tagStatPointUseType
{
	MSG_STATPOINT_USE_STR,
	MSG_STATPOINT_USE_DEX,
	MSG_STATPOINT_USE_INT,
	MSG_STATPOINT_USE_CON,
	MSG_STATPOINT_USE_STR_10,
	MSG_STATPOINT_USE_DEX_10,
	MSG_STATPOINT_USE_INT_10,
	MSG_STATPOINT_USE_CON_10,
} MSG_STATPOINT_USE_TYPE;


typedef enum _tagStatPointErrorType
{
	MSG_STATPOINT_ERROR_NOTENOUGH,		// ���� ����Ʈ ����
	MSG_STATPOINT_ERROR_CANTUSE,		// ���� ����Ʈ ��� �Ұ�
	MSG_STATPOINT_ERROR_WRONGPACKET,	// Ŭ���̾�Ʈ���� �̻��� ��Ŷ�� �Դ�
	MSG_STATPOINT_ERROR_NOMONEY,		// ���� ���� �ʱ�ȭ ��û
} MSG_STATPOINT_ERROR_TYPE;


typedef enum _tagSkillLearnErrorType
{
	MSG_SKILL_LEARN_ERROR_LEVEL,		// ���� ����
	MSG_SKILL_LEARN_ERROR_SP,			// ����Ʈ ����
	MSG_SKILL_LEARN_ERROR_ITEM,			// ������ ����
	MSG_SKILL_LEARN_ERROR_SKILL,		// ��ų ����
	MSG_SKILL_LEARN_ERROR_SYSTEM,		// �׿� �ý��� ����(��ų �ִ� ��ġ�� ���� ���� ���, ������ �߻��ϸ� �ȵǴ� ���!)
	MSG_SKILL_LEARN_ERROR_STR,			// �� ����
	MSG_SKILL_LEARN_ERROR_DEX,			// ���� ����
	MSG_SKILL_LEARN_ERROR_INT,			// ���� ����
	MSG_SKILL_LEARN_ERROR_CON,			// ü�� ����
} MSG_SKILL_LEARN_ERROR_TYPE;

typedef enum _tagAttackDamageType //1013
{
	MSG_DAMAGE_UNKNOWN = -1,			// �˼����� ����!
	MSG_DAMAGE_MELEE = 0,				// �ٰŸ� ���� ����
	MSG_DAMAGE_RANGE,					// ���Ÿ� ���� ����
	MSG_DAMAGE_MAGIC,					// ��ų ����
	MSG_DAMAGE_REFLEX,					// �ݻ� ����
	MSG_DAMAGE_LINK,					// ������ ��ũ�� ���� ����
	MSG_DAMAGE_COMBO,					// ���� �޺� ������ ����
} MSG_ATTACK_DAMAGE_TYPE;

typedef enum _tagWarpType
{
	MSG_WARP_START,						// �̵���ġ ��� ����
	MSG_WARP_CANCEL,					// �̵���ġ ��� ����
	MSG_WARP_END,						// �̵���ġ ��� ��(10�� ������ ��)
	MSG_WARP_TELEPORT,					// ���� �̵�				: pos(n) x(f:s) z(f:s) h(f:s) r(f:s) ylayer(c:s)
	MSG_WARP_PROMPT,					// �̵� Ȯ��				: zone(n) pos(n)

										// ��ȯ������ ������� �߰��� �޽��� wooss 050808
	MSG_WARP_TO_REQING,					// gs->c :�����̵� ���θ� ���� ����
	MSG_WARP_TO_REQ,					// PC�� �����̵���û : charname(str)
										// gs-> c charname���� ����? : charname(str)
	MSG_WARP_TO,						// C->GS charname���� ���ο��ο� ���� ���� : charname(str) ballow(c)
	MSG_WARP_TAKE_REQ,					// pc�� ��ȯ ��û	 : charname(str)
										// gs-> c charname���� ����? : charname(str)
	MSG_WARP_TAKE_REQING,				// gs->c ��ȯ ���� 
	MSG_WARP_TAKE,						// C->GS charname���� ���ο��ο� ���� ��ȯ : charname(str) ballow(c)
	MSG_WARP_ERROR,						// errorcode(c)
} MSG_WARP_TYPE;


//wooss 050808
//warp ���� �޽���
typedef enum _tagWarpErrorType
{
	MSG_WARP_ERROR_NOTCHAR,				// �������� �ƴϰų� �������� ����
	MSG_WARP_ERROR_NOTALLOW,			// �̵��� �������� ����
	MSG_WARP_ERROR_NOTALLOWZONE,		// �̵��Ҽ� ���� ���� �ֽ��ϴ�
	MSG_WARP_ERROR_CANCEL,				// ��û�ڰ� ���
} MSG_WARP_ERROR_TYPE;



typedef enum _tagProduceKind
{
	MSG_PRODUCE_MINING,					// ä��
	MSG_PRODUCE_GATHERING,				// ä��
	MSG_PRODUCE_CHARGE,					// ����
} MSG_PRODUCE_KIND;

typedef enum _tagProcessKind
{
	MSG_PROCESS_STONE,					// ���� ����
	MSG_PROCESS_PLANT,					// �Ĺ� ����
	MSG_PROCESS_ELEMENT,				// ���� ����
} MSG_PROCESS_KIND;

typedef enum _tagMsgSSkillType
{
	MSG_SSKILL_LIST,					// Ư�� ��ų ����Ʈ			: count(n) [sskill_index(n) sskill_level(c)] * count
	MSG_SSKILL_LEARN,					// Ư�� ��ų ����			: sskill_index(n) is_new(uc) sskill_level(c)
	MSG_SSKILL_LEARN_ERROR,				// ���� ���� �߻�			: errorcode(uc)
} MSG_SSKILL_TYPE;

typedef enum _tagSSkillLearnErrorType
{
	MSG_SSKILL_LEARN_ERROR_LEVEL,		// ���� ����
	MSG_SSKILL_LEARN_ERROR_SP,			// SP ����Ʈ ����
	MSG_SSKILL_LEARN_ERROR_SSKILL,		// SSkill �ƿ� ����
	MSG_SSKILL_LEARN_ERROR_SSKILL_LEVEL,// SSkill Level�� �ȵ�
	MSG_SSKILL_LEARN_ERROR_SYSTEM,		// �׿� �ý��� ����(��ų �ִ� ��ġ�� ���� ���� ���, ������ �߻��ϸ� �ȵǴ� ���!)
} MSG_SSKILL_LEARN_ERROR_TYPE;

typedef enum _tagPKType
{
	MSG_PK_PENALTY_HPMP,				// hp, mp �г�Ƽ ī��Ʈ ���� : hp_count(n) mp_count(n)
	MSG_PK_ITEMSEAL,					// item ���� ��				 : tab(c) row(c) col(c) itemindex(n) flag(n)
	MSG_PK_RECOVER_HPMP,				// hp, mp ���� ��û/����	 : hp_request(c) mp_request(c)
	MSG_PK_RECOVER_ITEMSEAL,			// item ���� ���� ��û/����	 : tab(c) row(c) col(c) itemindex(n) flag(n:s)
	MSG_PK_ERROR,						// ���� ����				 : errorcode(c)
										//							 : 0 - �� ����, 1 - hp ����, 2 - mp ����, 3 - ������ ����
	MSG_PK_FREE,						// Free PK SYSTEM
	MSG_PK_CHANGE_KING,					// ī��ŷ ���� �޼��� : bChao(c) 0-���� 1-ī��, CharIndex(n) ĳ���� �ε��� 
	MSG_PK_MYZONE_ATT,					// REQ : NONE, REP : ZoneAtt(c) ( 0-Normal, 1-���� , 2-ī�� )
	MSG_PK_REMOVE_PENALTY,				// REQ : type(c) 0-����, 1-1�ܰ� , REP : succecc(c) : 0-����, 1-���� 
	MSG_PK_OTHERZONE_ALRAM,				// REQ : NONE , REP : bAram(c) 0-OFF 1-ON, charIndex(n) ĳ���� ���ؽ� 
	MSG_PK_TARGET_SHOWHP,				// REQ : On(c) 0-OFF 1-ON REP : NONE
} MSG_PK_TYPE;

typedef enum _tagEventType
{
	MSG_EVENT_ERROR,							// �����ڵ�					: errcode(uc)
	MSG_EVENT_PREOPEN_GIFT,						// �������� ���� ���� �ֱ�	: itemdbindex(n:s)
	MSG_EVENT_LATTO,							// ��� �̺�Ʈ ����			: subtype(uc)
	MSG_EVENT_LETTER,							// ���� ���߱� �̺�Ʈ		: subtype(uc)
	MSG_EVENT_CHANGEWEAPON,						// ���� ��ȯ �̺�Ʈ			: olddbindex(n:s) newdbindex(n:s)
	MSG_EVENT_MOONSTONE,						// ������ �̺�Ʈ.
	MSG_EVENT_TREASUREBOX,						// �������� �̺�Ʈ.
	MSG_EVENT_SUPERSTONE,						// ���۰��� �̺�Ʈ.//0627
	MSG_EVENT_CHUSEOK_UPGRADE,					// �߼� �̺�Ʈ ���׷��̵�	: 
	MSG_EVENT_CHUSEOK_EXCHANGE,					// �߼� �̺�Ʈ ��ȯ			: 
	MSG_EVENT_CHANGE_WITHOUT_OPTION,			// 2��4�� ������ ���� ��ü �̺�Ʈ : old_itemindex(n) new_subtype(n)
	MSG_EVENT_2PAN4PAN_LETTER,					// 2��4�� ������ ���� �̺�Ʈ : MSG_EVENT_2PAN4PAN_WORD_TYPE(n)
	
	MSG_EVENT_2PAN4PAN_GOODS_CHECK,				// 2��4�� ������ ������ ����Ʈ ��û : count(n:server) wooss 051031
	MSG_EVENT_2PAN4PAN_GOODS_REQ,				// 2��4�� ������ ������ �ޱ� ��û :
	MSG_EVENT_2PAN4PAN_GOODS_REP,				// 2��4�� ������ ������ �ޱ� ���� : MSG_EVENT_2PAN4PAN_GOODS_ERROR_TYPE(n) count(n) [itemdbindex(n) itemcount(ll)]*count

	MSG_EVENT_2PAN4PAN_MONEY_REQ,				// 2��4�� �Ӵ� ī�� ��ȯ ��û : type(n)
												// type : 1 - �°�, 2 - ��Ŀ
	MSG_EVENT_2PAN4PAN_MONEY_REP,				// 2��4�� �Ӵ� ī�� ��ȯ ���� : success(n)
												// success : 0 - ����, 1 - ����

	MSG_EVENT_2PAN4PAN_BOX_CHECK,				// 2��4�� ���� ��ȯ �˻�	: flag(n:server)
												// flag : 0 - ����, 1 - ����
	MSG_EVENT_2PAN4PAN_BOX_REQ,					// 2��4�� ���� ��ȯ ��û	: 
	MSG_EVENT_2PAN4PAN_BOX_REP,					// 2��4�� ���� ��ȯ ����	: MSG_EVENT_2PAN4PAN_BOX_ERROR_TYPE(n) count(n)  [itemdbindex(n) itemcount(ll)]*count
	
	MSG_EVENT_XMAS_2005,						// 2005 ũ�������� �̺�Ʈ :  MSG_EVENT_XMAS_2005_ERROR_TYPE(n:server)
	MSG_EVENT_NEWYEAR_2006_CHECK,				// 2006 �ų� �̺�Ʈ �ð� ��û : time_sec(n:server)
	MSG_EVENT_NEWYEAR_2006_GOODS,				// 2006 �ų� �̺�Ʈ ����  : MSG_EVENT_NEWYEAR_2006_GOODS_ERROR_TYPE(n:server)
	
	MSG_EVENT_SEARCHFRIEND_ADD_CHECK,			// �޸��ɸ� ��� üũ :
	MSG_EVENT_SEARCHFRIEND_ADDSELECT_LIST,		// ����� ����Ʈ �κ� : listCount , [requestindex , reqnick(char)]*listCount
	MSG_EVENT_SEARCHFRIEND_ADDSELECT_CHECK,		// ����� ����Ʈ�� �����ϴ� �κ� :  requestindex , MSG_EVENT_SEARCHFRIEND_ERROR_TYPE 
	MSG_EVENT_SEARCHFRIEND_TIME_CHECK,		// ��ɽð� üũ : time_sec(n:server)
	MSG_EVENT_SEARCHFRIEND_ONETIME_CHECK,		// ��ɽð� �ѽð� ���� üũ : time_sec(n:server)
	MSG_EVENT_SEARCHFRIEND_LIST_GOODS,		// ��ϵ� ģ�� ���󰡴ɿ��� : request_listmember(n), (MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_TYPE)errcode,[reqnick[n], request_index[n], request_time[n], item_good[n]]*request_listmember
	MSG_EVENT_SEARCHFRIEND_GOODS_CHECK,		// ������ ���� ���� :MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_TYPE(n)

	MSG_EVENT_PACKAGE_ITEM_GIVE,				// ��Ű�� ������ ���� ��û  : couponNo(str)
												// gs->client				: errorcode(str)
	MSG_EVENT_OPENBETA_CONN,					// ���º�Ÿ ������ ���� ��û: 
												// gs->client		
	MSG_EVENT_SAKURABUD,						// �ɺ����� ������ ���� ��û : cmd(c) : 0-��������,1-�尩�Ź�,2-���� 

	MSG_EVENT_OXQUIZ,							// OX ���� �̺�Ʈ			: subtype(n) ...

	MSG_EVENT_RECOMMEND,						// ��õ����					: subtype(n) ...
	MSG_EVENT_PCBANG,							// �Ǿ��� (�ݱ��� ķ����)	: ���� ����Ȥ�� ��ȯ ����  GS->C : itemindex(n)    -1�̸� ����(���ڰ� ����)
												//							: ��ȯ ��û�� C->GS :

	MSG_EVENT_WORLDCUP,							// ������ �̺�Ʈ			: subtype(n) ...
	MSG_EVENT_GOLDENBALL,						// ��纼 �̺�Ʈ			: subtype(n) ...

	MSG_EVENT_RAIN_2006,						// �帶 �̺�Ʈ				: errorcode(n:s) // �Ϻ� ����

	MSG_EVENT_TLD_BUDDHIST,						// �ұ� �к� �̺�Ʈ			: requesttype(c) errorcode(n:s)
												// requesttype				: 0 - ����, 1 - ������ // �±� ����

	MSG_EVENT_COLLECT_BUG,						// ���� ä��				: subtype(n) ...

	MSG_EVENT_CHUSEOK_2006,						// 2006�� �߼� �̺�Ʈ		: subtype(n) ...

	MSG_EVENT_OPEN_BETA_GIFT,					// ���� ��Ÿ ����ǰ �ֱ�
	
	MSG_EVENT_XMAS_2006,						// 2006 ũ�������� �̺�Ʈ ��ȯ : cakecount( n ) errcode(n: s)
	
	MSG_EVENT_VALENTINE_2007,					// 2007 �߷�Ÿ�ε��� �̺�Ʈ : subtype(n) ...

	MSG_EVENT_WHITEDAY_2007,					// 2007 ȭ��Ʈ���� �̺�Ʈ WSS_WHITEDAY_2007
	MSG_EVENT_SONGKRAN_2007,					// [KH_070328]  ��� �߰�
	MSG_EVENT_EGGS_HUNT_2007,					// [KH_070328]  2007 �̱� ��Ȱ�� �̺�Ʈ

	MSG_NEW_EVENT_PACKAGE_ITEM_GIVE,			// NEW ��Ű�� ������ ���� ��û  : couponNo(str)
												// gs->client				: errorcode(c)
	MSG_EVENT_PARENTSDAY_2007,					// 2007 ����̳� �̺�Ʈ WSS_GUILDMASTER 070416

	MSG_EVENT_TEACH_2007,						// 2007�� �����ǳ� �̺�Ʈ

	MSG_EVENT_GOMDORI_2007,						// 2007�� ������ �̺�Ʈ		: subtype(uc) ...

	MSG_EVENT_CHILDRENSDAY_2007,				// 2007 ��̳� �̺�Ʈ

	MSG_EVENT_FLOWERTREE_2007,					// 2007�� �ɳ��� �̺�Ʈ : subtype(uc) ...
	
	MSG_EVENT_SUMMER_VACATION_2007,				// 2007�� ���� ���� �̺�Ʈ : subtype(uc)....

	MSG_EVENT_TLD_MOTHERDAY_2007,				// ��Ӵϳ� �̺�Ʈ			: requesttype(c) errorcode(n:s)
												// requesttype				: 1 - ���� ���ü� ��ȯ , 2 - Poem Book ��ȯ ,3Blessing of mother(red),
												//							: 4.Blessing of mother(yellow),5.Blessing of mother(blue)

	MSG_EVENT_OPEN_ADULT_SERVER,				// ���μ��� ����ī���̺�Ʈ

	MSG_EVENT_GIFT_2007,						// 2007�� �̺�Ʈ �Ⱓ ���� �����鿡�� ������ ��������
	MSG_EVENT_BJMONO_2007,						// SK bj mono �̺�Ʈ : subtype(uc)
	
	MSG_EVENT_SSHOT_2007,					    // Screen Shot Event : Subtype(uc) // WSS_TG2007 2007/09/14
	MSG_EVENT_RICHYEAR,							// ǳ�� �̺�Ʈ 
	MSG_EVENT_LC_1000DAY,						// ��Ʈī���� 1000�� �̺�Ʈ 	
	MSG_EVENT_HALLOWEEN_2007,					// 2007�� �ҷ��� �̺�Ʈ 

	MSG_EVENT_NEW_MOONSTONE,					// ������ ����

	MSG_EVENT_XMAS_2007,						// 2007�� ũ�������� �̺�Ʈ

	MSG_EVENT_NEWYEAR_2008,						// 2008 �ų� �̺�Ʈ gs->cl, cl->gs   charindex(n), charname(s)

	MSG_EVENT_TREASUREBOX_RED,					// ���� ���� ���� �̺�Ʈ

	MSG_EVENT_SAKURA_2008,						// 2008 ���� �̺�Ʈ

	MSG_EVENT_NOM,								// ���� ��ȭ �̺�Ʈ

	MSG_EVENT_PHOENIX,							// �Ǵн� �̺�Ʈ
#ifdef DEMIGOD
	MSG_EVENT_DEMIGOD,							// �Ǵн� �̺�Ʈ // yhj   081105  �Ǵн�
#endif
	MSG_EVENT_PHOENIX_SUCCESS,					// �Ǵн� �̺�Ʈ �¶�// yhj   081105  �Ǵн�
#ifdef DEMIGOD
	MSG_EVENT_DEMIGOD_SUCCESS,					// �Ǵн� �̺�Ʈ �¶�// yhj   081105  �Ǵн�
#endif
	
	MSG_EVENT_REQUITAL,							// ���� �̺�Ʈ
	MSG_EVENT_NEW_AFRON_2009,					// afron �������� ���� �̺�Ʈ
	
	MSG_EVENT_WORLDCUP_2010,					// ($E_WC2010) [100511: selo] ���� ���� �̺�Ʈ (2010 ���ư� ������)
	MSG_EVENT_AKAN_TEMPLE,	// (74)
	MSG_EVENT_PROMOTION2,						// ���θ�� �̺�Ʈ :: ������ �Ѱ��� ���� ��� ���� 
	MSG_EVENT_ATTENDANCE_2011,					// [2011/01/18 : Sora] �⼮ �̺�Ʈ
	MSG_EVENT_ENCHANT_RATE,						// [2011/01/18 : Sora] �⼮ �̺�Ʈ ��þƮ ������
	
	MSG_EVENT_USER_COMEBACK,					// �޸� ���� �̺�Ʈ	(78)
	MSG_EVENT_CHAR_BIRTHDAY,					// ĳ���� 1�ֳ� �̺�Ʈ

	MSG_EVENT_EUR2_PROMOTION,					// #define EVENT_EUR2_PROMOTION

	MSG_EVENT_MUSICAL_ZORRO,					// ���� ������ �̺�Ʈ(81)

	MSG_EVENT_LOI_KRATHONG,						// (82) �±� ũ���� �̺�Ʈ

	MSG_EVENT_KB_REWARD,						// (83)	�±� ���� ź���� �̺�Ʈ
    MSG_BUFF_NPC_REQ,

	MSG_EVENT_NEW_LIST,
	MSG_EVENT_NEW_ACTIVATED,
	MSG_EVENT_NEW_DEACTIVATED,

	MSG_EVENT_END_MSG,							// ��� �̺�Ʈ ���� �޽����� �̺��� �տ�
	
} MSG_EVENT_TYPE;

typedef enum _tagMsgEventEUR2PromotionErrorType
{
    MSG_EVENT_EUR2_PROMOTION_SUCCESS,                       // ����
    MSG_EVENT_EUR2_PROMOTION_WRONG_KEY,                     // Ű�� �߸� �Է��Ͽ���.
    MSG_EVENT_EUR2_PROMOTION_ALREADY_USED,                  // Ű�� �̹� ����Ͽ���.
    MSG_EVENT_EUR2_PROMOTION_LACK_INVENTORY,                // �κ� ��ã��.
    MSG_EVENT_EUR2_PROMOTION_SYS_ERROR_NOT_USED,            // DB�� ������Ʈ�� �ȵǾ� ������ ��. �׷��� �����Ѱ����� ó��
    MSG_EVENT_EUR2_PROMOTION_CANT_USE_USER,                 // ������ �̹� �ٸ� Ű�� ����Ͽ���.
    MSG_EVENT_EUR2_PROMOTION_HEAVY_WEIGHT,                  // �κ� ���ſ�.
}MSG_EVENT_EUR2_PROMOTION_ERROR_TYPE;

typedef enum _tagMsgEventAttendance2011Type
{
	MSG_EVENT_ATTENDANCE_2011_NOTICE,					// �̺�Ʈ ����â ����
	MSG_EVENT_ATTENDANCE_2011_CALC_RATE,				// �̺�Ʈ �ý���+���� �޽���
	MSG_EVENT_ATTENDANCE_2011_INDIVIDUAL_REWARD_REQ,	// ���κ��� ��û �޽���
	MSG_EVENT_ATTENDANCE_2011_INDIVIDUAL_REWARD_REP,	// ���κ��� ���� �޽���
}MSG_EVENT_ATTENDANCE_2011_TYPE;


// ($E_WC2010)
typedef enum _tagMsgEventWorldcup2010Type
{
	MSG_EVENT_WORLDCUP2010_TRADE_REQ,			// �౸�� ��ȯ : �౸�� -> 1.Ȳ���౸�� -> 2.���� ���� ���� ��ȯ : tradeType(n)
	MSG_EVENT_WORLDCUP2010_TRADE_REP,			// �౸�� ��ȯ �亯 MSG_EVENT_WORLDCUP2010_ERROR_TYPE

	MSG_EVENT_WORLDCUP2010_TOTO_REQ,			// �¸����� TOTO ��� : countryItem1(n)
	MSG_EVENT_WORLDCUP2010_TOTO_REP,			// �¸����� TOTO ��� �亯 : MSG_EVENT_WORLDCUP2010_ERROR_TYPE
	MSG_EVENT_WORLDCUP2010_TOTO_STATUS_REQ,		// TOTO ���� ��Ȳ  : resultType(n)
	MSG_EVENT_WORLDCUP2010_TOTO_STATUS_REP,		// TOTO ���� ��Ȳ �亯 : MSG_EVENT_WORLDCUP2010_ERROR_TYPE
	MSG_EVENT_WORLDCUP2010_TOTO_GIFT_REQ,		// TOTO ��ǰ ��û 
	MSG_EVENT_WORLDCUP2010_TOTO_GIFT_REP,		// TOTO ��ǰ ��û �亯 : MSG_EVENT_WORLDCUP2010_ERROR_TYPE

	MSG_EVENT_WORLDCUP2010_ATTENDANCE_REQ,		// �⼮ �̺�Ʈ : 
	MSG_EVENT_WORLDCUP2010_ATTENDANCE_REP,		// �⼮ �̺�Ʈ �亯 : MSG_EVENT_WORLDCUP2010_ERROR_TYPE

	MSG_EVENT_WORLDCUP2010_SUPPORTCARD_REQ,		// ���� ī�� ��ȯ : supportType(n)
	MSG_EVENT_WORLDCUP2010_SUPPORTCARD_REP,		// ���� ī�� ��ȯ �亯 : MSG_EVENT_WORLDCUP2010_ERROR_TYPE

	MSG_EVENT_WORLDCUP2010_KOREA_REQ,			// �ѱ� 16�� ���� ��û
	MSG_EVENT_WORLDCUP2010_KOREA_REP,			// �ѱ� 16�� ���� ��û �亯 : MSG_EVENT_WORLDCUP2010_ERROR_TYPE	
}MSG_EVENT_WORLDCUP2010_TYPE;

// ($E_WC2010)
typedef enum _tagMsgEventWorldcup2010ErrorType
{
	MSG_EVENT_WORLDCUP2010_TRADE_ERROR_SUC,				// �౸�� ��ȯ ���� : totoType(n)
	MSG_EVENT_WORLDCUP2010_TRADE_ERROR_BALL,			// �౸�� ���� ���� : totoType(n)
	MSG_EVENT_WORLDCUP2010_TRADE_ERROR_FAIL,			// �౸�� ��ȯ ����

	MSG_EVENT_WORLDCUP2010_TOTO_ERROR_SUC,				// �¸����� TOTO ��� ����
	MSG_EVENT_WORLDCUP2010_TOTO_ERROR_FAIL,				// �¸����� TOTO ��� ����
	
	MSG_EVENT_WORLDCUP2010_TOTO_STATUS_ERROR_SUC,		// ���� ��Ȳ ���� : resultType(n), countryItem1(n)
	MSG_EVENT_WORLDCUP2010_TOTO_STATUS_ERROR_FAIL,		// ���� ���� �ʾ��� : resultType(n)
	
	MSG_EVENT_WORLDCUP2010_TOTO_GIFT_ERROR_SUC,			// ��ǰ ��û ����
	MSG_EVENT_WORLDCUP2010_TOTO_GIFT_ERROR_WEIGHT,		// ���� �ʰ�
	MSG_EVENT_WORLDCUP2010_TOTO_GIFT_ERROR_INVEN,		// �κ� ���� ����
	MSG_EVENT_WORLDCUP2010_TOTO_GIFT_ERROR_FAIL,		// ���� ��ǰ ���� 

	MSG_EVENT_WORLDCUP2010_ATTENDANCE_ERROR_SUC,		// �⼮ üũ ����
	MSG_EVENT_WORLDCUP2010_ATTENDANCE_ERROR_ALREADY,	// �̹� �⼮ ��	
	MSG_EVENT_WORLDCUP2010_ATTENDANCE_ERROR_FAIL,		// �⼮ üũ ����

	MSG_EVENT_WORLDCUP2010_SUPPORTCARD_ERROR_SUC,		// ���� ī�� ��ȯ ����
	MSG_EVENT_WORLDCUP2010_SUPPORTCARD_ERROR_CARD,		// ���� ī�� ���� ����
	MSG_EVENT_WORLDCUP2010_SUPPORTCARD_ERROR_FAIL,		// ���� ī�� ��ȯ ����

	MSG_EVENT_WORLDCUP2010_KOREA_ERROR_SUC,				// �ѱ� 16�� ���� ��ȯ ����
	MSG_EVENT_WORLDCUP2010_KOREA_ERROR_ALREADY,			// �̹� �޾���
	MSG_EVENT_WORLDCUP2010_KOREA_ERROR_WEIGHT,			// ���� �ʰ�
	MSG_EVENT_WORLDCUP2010_KOREA_ERROR_INVEN,			// �κ� ���� ����
	MSG_EVENT_WORLDCUP2010_KOREA_ERROR_FAIL,			// �ѱ� 16�� ���� ��ȯ ����
}MSG_EVENT_WORLDCUP2010_ERROR_TYPE;

typedef enum __tagMsgEventNewAfron2009Type
{
	MSG_EVENT_GIVE_ITEM_SUCCESS,				// SERVER -> CLIENT ������ ���� �� ���� �޽���
	MSG_EVENT_GIVE_ITEM_NO_TARGET,				// SERVER -> CLIENT ������ ���� ����� �ƴ�
	MSG_EVENT_GIVE_ITEM_ALREADY_RECEIVE,		// SERVER -> CLIENT �������� �̹� ���� �������.
}MSG_EVENT_NEW_AFRON_2009_TYPE;

typedef enum _tagEventRequitalErroType
{
	MSG_EVENT_REQUITALM_OK,						// ���� ����
	MSG_EVENT_REQUITAL_FAIL,					// ���� ����
	MSG_EVENT_REQUITAL_ERROR_ALREADY_APPLY,		// �̹� ���� ��
	MSG_EVENT_REQUITAL_FAIL_TIME,				// ���� �ð��� ������
	MSG_EVENT_REQUITAL_ERROR_FULL_INVEN,		// �κ��丮�� ����
	MSG_EVENT_REQUITAL_ERROR_TOO_HEAVY_INVEN,	// �κ��丮�� �ʹ� ���ſ�
	MSG_EVENT_REQUITAL_FAIL_TIME_NOPLAY,		// �ش� ��¥�� ������ ���� �ʾƼ� ����
	MSG_EVENT_REQUITAL_FAIL_CREATE_TIME,		// ������ ������ ������ ��¥�� �ʹ� �̸�

}MSG_EVENT_REQUITAL_ERROR_TYPE;

typedef enum _tagEventPhoenixErrorType
{
	MSG_EVENT_PHOENIX_OK,
    MSG_EVENT_PHOENIX_ERROR_ALREADY_APPLY,
	MSG_EVENT_PHOENIX_ERROR_FULL_INVENTORY,
    MSG_EVENT_PHOENIX_ERROR_REQUIREMENT,	
} MSG_EVENT_PHOENIX_ERROR_TYPE;

#ifdef DEMIGOD
typedef enum _tagEventDemiGodErrorType
{
	MSG_EVENT_DEMIGOD_OK,
	MSG_EVENT_DEMIGOD_ERROR_ALREADY_APPLY,
	MSG_EVENT_DEMIGOD_ERROR_FULL_INVENTORY,
	MSG_EVENT_DEMIGOD_ERROR_REQUIREMENT,
} MSG_EVENT_DEMIGOD_ERROR_TYPE;
#endif

typedef enum _tagEventNomErrorType
{
 MSG_EVENT_NOM_OK,						// ���� ����
 MSG_EVENT_NOM_ERROR_ALREADY_APPLY,		// �̹� ���� ��
 MSG_EVENT_NOM_ERROR_FULL_INVEN,		// �κ��丮�� ����
 MSG_EVENT_NOM_ERROR_ITEM_FAIL,			// ������ ����
 MSG_EVENT_NOM_LOTTERY_USE_OK,			// ���� ��� ����
 MSG_EVENT_NOM_MOVIE_TICKET_OK,			// Ƽ�� ��� ����
} MSG_EVENT_NOM_ERROR_TYPE;

typedef enum _tagEventSakura2008Type
{
	MSG_EVENT_SAKURAEVENT_2008,					//���� ������ ��ȯ
	MSG_EVENT_SAKURAEVENT_2008_ERROR,			//���� ������ ��ȯ ��� errorcode(c) 0:success, 1: failed
	MSG_EVENT_SAKURAEVENT_2008_ITEMCHANGE,		//���� ������ ȹ�� ���� charName(str), itemindex(n)
} MSG_EVENT_SAKURA_2008_TYPE;

typedef enum _tagEventNewMoonStoneType
{
	MSG_EVENT_NEW_MOONSTONE_START_REQ,		// ������ ���ۿ�û
	MSG_EVENT_NEW_MOONSTONE_START_REP,		// ������ ��������		nas(n)

	MSG_EVENT_NEW_MOONSTONE_TRY_REQ,		// ������ ���� ��û		moonstone_idx(n)
	MSG_EVENT_NEW_MOONSTONE_TRY_REP,		// ������ ���� ����		giftitemindex(n) , nas(n)

	MSG_EVENT_NEW_MOONSTONE_RESULT_REQ,		// ������ ���� ��� ��û	
	MSG_EVENT_NEW_MOONSTONE_RESULT_REP,		// ������ ���� ��� ����	giftitemidx(n), giftitemcount(n)

	MSG_EVENT_NEW_MOONSTONE_JACK_POT,		// ����	

	MSG_EVENT_NEW_MOONSTONE_OK,			// ���������		moonstone idx(n)

	MSG_EVENT_NEW_MOONSTONE_NO_MOONSTONE,		// ������ ����		itemindex(���¹�����index)
	MSG_EVENT_NEW_MOONSTONE_FULLINVEN,		// �κ�������	

	MSG_EVENT_NEW_MOONSTONE_MIX_REQ,			// ������ ���� ��û	moonstone_idx(n)
	MSG_EVENT_NEW_MOONSTONE_MIX_SUCCESS,		// ������ ���� ����	new_moonstone_idx(n),
	MSG_EVENT_NEW_MOONSTONE_MIX_FAILED,			// ������ ���� ����
	MSG_EVENT_NEW_MOONSTONE_MIX_MISS			// ������ ���� ���Ŀ� ��߳�
} MSG_EVENT_NEW_MOONSTONE_TYPE;

typedef enum _tagEventXMas2007Type
{
	MSG_EVENT_XMASTREE_ADD_POINT,		// REQ: NOT , REP (c)error 0:����, 1:������ ����
	MSG_EVENT_XMASTREE_GET_BLESS,		// REQ: NOT , REP (c)error 0:����, 1:������ ����
	MSG_EVENT_XMASTREE_DROP_ITEM,		// REQ: NONE, REP (n)remainTime ���� �ð�(��)

	MSG_EVENT_XMAS_PUZZLE_CHECKITEM_REQ,	// �������� �����ϴ��� Ȯ�� ��û
	MSG_EVENT_XMAS_PUZZLE_CHECKITEM_REP,	// �������� �����ϴ��� Ȯ�� ����: ucResult(0:����, 1:����)
	MSG_EVENT_XMAS_PUZZLE_START_REQ,		// ���� ���� ��û
	MSG_EVENT_XMAS_PUZZLE_START_REP,		// ���� ���� ���� ���� ����     : ucResult(0:����, 1:����)
	MSG_EVENT_XMAS_PUZZLE_SELECT_REQ,		// ����, ����, �� ���� ��û     : ucChoice(0:����, 1:����, 2:��)
	MSG_EVENT_XMAS_PUZZLE_SELECT_REP,		// ����, ����, �� ���          : ucResult(0:�¸�, 1:���, 2:�й�), ucWinCount(�¸� Ƚ��), ucUserSelection(���� ���ð�(0:����, 1:����, 2:��)), ucServerSelection(���� ���ð�(0:����, 1:����, 2:��))
	MSG_EVENT_XMAS_PUZZLE_CONTINUE_REQ,		// ������ ��� ���� ��û
	MSG_EVENT_XMAS_PUZZLE_CONTINUE_REP,		// ���� ��� ���� ����
	MSG_EVENT_XMAS_PUZZLE_END_REQ,			// ���� �׸��ϰ� ���� ��û
	MSG_EVENT_XMAS_PUZZLE_END_REP,			// ���� ���� �� ���� �Ϸ� �޽���: ucWinCount(�¸� Ƚ��), nGiftItemIndex(���� ������ �ε���), llGiftItemCount(���� ������ ����)
} MSG_EVENT_XMAS_2007_TYPE;

typedef enum _tagMsgEventHallowWeen2007
{
	MSG_EVENT_TAKE_DEVILHEAIR,						// �Ǹ����� �Ӹ��� �ޱ� REQ: , REP: 0(SUCCESS), 1(����������)
	MSG_EVENT_CHANGE_CANDYBASKET,					// �����ٱ��Ͽ� ���� �ޱ� REQ: , REP: 0(SUCCESS), 1(�ٱ��� ����)
	MSG_EVENT_CHANGE_PUMKINHEAD,					// ȣ�ڸӸ� Ż ��ȯ�ޱ� REQ: , REP: 0(SUCCESS) , 1(�������ڶ�)
	MSG_EVENT_CHANGE_WITCHHAT,						// ������� ��ȯ�ޱ� REQ: , REP: 0(SUCCESS), 1(��ǥ����)
	MSG_EVENT_CHANGE_PUMKIN,						// ȣ�� ��ȯ �ޱ� REQ: , REP: 0(SUCCESS), 1(ȣ�ھ���)
	MSG_EVENT_TASTE_CANDY,							// ���� �� REQ:NONE , REP : 0(�������θ�),1(�䳪���¸�),2(�׷�����),3(��������),4(õ���Ǹ�)
	MSG_EVENT_FULL_INVEN,							// �κ� ������
} MSG_EVENT_HALLOWEEN_2007_TYPE;

typedef enum _tagMsgEventLC1000Day
{
	MSG_EVENT_LC_1000DAY_HAT,						// 1000�� �̺�Ʈ ���� ��û 
	MSG_EVENT_LC_1000DAY_HAT_UPDATE,				// ���� �ɼ� ������Ʈ ��û 
	MSG_EVENT_LC_1000DAY_FIRECRACKER,				// ���� ��û
	MSG_EVENT_LC_1000DAY_FULLINVEN,					// �κ��� ���� ��
	MSG_EVENT_LC_1000DAY_HAT_UPDATE_SUCCESS,		// ���� �ɼ� ������Ʈ ����
	MSG_EVENT_LC_1000DAY_HAT_UPDATE_FAIL,			// ���� �ɼ� ������Ʈ ����
	MSG_EVENT_LC_1000DAY_FIRECRACKER_DUPLICATION,	// ���� �������� �κ��� ����
	MSG_EVENT_LC_1000DAY_NOITEM,				    // ������ ���� 
} MSG_EVENT_LC_1000DAY_TYPE;

typedef enum _tagMsgEventRichYear
{
	MSG_EVENT_RICHYEAR_UPGRADE,						// ������ ���׷��̵� ��û
	MSG_EVENT_RICHYEAR_EXCHANGE,					// ����ǰ ��ȯ
	MSG_EVENT_RICHYEAR_ERROR_UPGRADE_NOITEM,		// ���׷��̵��� ��� ����
	MSG_EVENT_RICHYEAR_ERROR_UPGRADE_FAILED,		// ���׷��̵� ����
	MSG_EVENT_RICHYEAR_ERROR_NOCROP,				// �۹��� ���� ���
	MSG_EVENT_RICHYEAR_ERROR_ALREADY_UPGRADE,		// ���̻� ���׷��̵� �Ұ���
	MSG_EVENT_RICHYEAR_ERROR_FULLINVEN,				// �κ�����
	MSG_EVENT_RICHYEAR_UPGRADE_OK,					// ���׷��̵� ����
	MSG_EVENT_RICHYEAR_EXCHAGE_OK,					// ���� ����
}MSG_EVENT_RICHYEAR_TYPE;


typedef enum _tagMsgEventSshot
{
	MSG_EVENT_SSHOT_2007_RECIVE,					// ���� �ޱ� REQ : ��û - REP : ����
	MSG_EVENT_SSHOT_2007_ALREADY,					// ������ �������� �ִ�.
	MSG_EVENT_SSHOT_2007_NOSSHOT,					// �������� ����
	MSG_EVENT_SSHOT_2007_FULLINVEN					// �κ��� ���� ��
} MSG_EVENT_SSHOT_2007_TYPE;

typedef enum _tagMsgEventBjMono
{
	MSG_EVENT_BJMONO_2007_TICKET_REQ,			// ����� �ޱ� REQ : ��û - REP : ���� count 
	MSG_EVENT_BJMONO_2007_CHANGE_TICKET_REQ,	// ����� ��ȯ REQ : ��û - REP : ���� itemIndex(n)
	MSG_EVENT_BJMONO_2007_NO_TICKET,			// ���� ����� ����
	MSG_EVENT_BJMONO_2007_DONT_CHANGE_TICKET,	// ��ȯ�� ������� ����
	MSG_EVENT_BJMONO_2007_PRICE_FULLINVEN,		// �κ��� �������� ������ ���� ����
} MSG_EVENT_BJMONO_2007_TYPE;

typedef enum _tagMSgConnEventGift2007Type
{
	MSG_CONN_EVENT_GIFT_2007_CHECK,
	MSG_CONN_EVENT_GIFT_2007_GIVE,			//����
	MSG_CONN_EVENT_GIFT_2007_CHECK_ALLOW,
	MSG_CONN_EVENT_GIFT_2007_CHECK_DBERROR,	//�̺�Ʈ DB ����
	MSG_CONN_EVENT_GIFT_2007_CHECK_DENY,	//�̹� ����
	MSG_CONN_EVENT_GIFT_2007_GIVE_DBERROR,	//DB ����
	MSG_CONN_EVENT_GIFT_2007_GIVE_FULL,		//�κ� ����
} MSG_CONN_EVENT_GIFT_2007_TYPE;

typedef enum _tagMsgEventOpenAdultServer
{
	// ����ī�����
	MSG_EVENT_OPEN_ADULT_SERVER_MAGIC_REQ,		// ����ī�庸��ޱ�
	MSG_EVENT_OPEN_ADULT_SERVER_MAGIC_OK,		// ��ų���󼺰�			exchangeType(b) 
											// exchangeType			0 : �ٶ��� �������
											//						1 : ���� �������
											//						2 : ��ø�� �������
											//						3 : ������ �������
											//						4 : ü���� �������
											//						5 : �η����� �������

	MSG_EVENT_OPEN_ADULT_SERVER_MAGIC_FAILED,	// ��ȯ ���� ( ��ų���� �������� ��)
	MSG_EVENT_OPEN_ADULT_SERVER_MAGIC_NOITEM,	// ������ ����			

	// ��������
	MSG_EVENT_OPEN_ADULT_SERVER_CHABGEJOB_EXCHANGE,		// ������ �����û
	MSG_EVENT_OPEN_ADULT_SERVER_CHABGEJOB_EXCHANGE_OK,		// ���󼺰�	: ���(n), �����Ǻ��� ���󰳼�(n)
	MSG_EVENT_OPEN_ADULT_SERVER_CHABGEJOB_ERROR_ALREADY,	// ��ǰ�̹� �޾���
	MSG_EVENT_OPEN_ADULT_SERVER_CHABGEJOB_ERROR_FAILED,		// ������ ���ؼ� ����		
	MSG_EVENT_OPEN_ADULT_SERVER_CHABGEJOB_ERROR_FULLINVEN, // �κ�����


	// ������ ���ݼ� �̺�Ʈ ����
	MSG_EVENT_OPEN_ADULT_SERVER_UPGRADE_REQ,			// ������ ���׷��̵� ��û : tab(n), row(n), col(n)
	MSG_EVENT_OPEN_ADULT_SERVER_UPGRADE_OK,
	MSG_EVENT_OPEN_ADULT_SERVER_UPGRADE_ERROR_NOT_FOUND,	// ��� ����
	MSG_EVENT_OPEN_ADULT_SERVER_UPGRADE_ERROR_FAILED,		// ���׷��̵� ����
	MSG_EVENT_OPEN_ADULT_SERVER_UPGRADE_ERROR_FULLINVEN, // �κ�����

}MSG_EVENT_OPEN_ADULT_SERVER_TYPE;

typedef enum _tagMsgEventSummerVacation_2007
{
 MSG_EVENT_SUMMER_VACATION_2007_PAPER_FIGURES, // ���� ���� ��û REQ: papaerindex(n) papaerindex(n) papaerindex(n)
             //  REP : errorcode(n) figuretype(n)
 MSG_EVENT_SUMMER_VACATION_2007_INCHEN,   // ��þ ��û : count(n) paperindex(uc) 
             // REP : err(n) itemname(str)
 
 MSG_EVENT_SUMMER_VACATION_2007_ERROR_INCHEN_FALIL, // ��þ ����
 MSG_EVENT_SUMMER_VACATION_2007_ERROR_INCHEN_OK,
 MSG_EVENT_SUMMER_VACATION_2007_ERROR_NOITEM,  // ������ ����
 MSG_EVENT_SUMMER_VACATION_2007_ERROR_MAKE_FAIL,
 MSG_EVENT_SUMMER_VACATION_2007_ERROR_MAKE_OK,
 MSG_EVENT_SUMMER_VACATION_2007_ERROR_FULLINVENTORY, // �κ��丮 �������� ������ ���� �Ұ���
 MSG_EVENT_SUMMER_VACATION_2007_ERROR_NOMONEY,   // �� ����
} MSG_EVENT_SUMMER_VACATION_2007_TYPE;

typedef enum _tagMsgEventFlowerTree_2007
{
	MSG_EVENT_FLOWERTREE_2007_POINT, 			// ���� �ɳ��� ���� ����Ʈ   REQ : not REP: point(un)
	MSG_EVENT_FLOWERTREE_2007_POINT_RANK,		// ������ �ɳ��� ���� ����Ʈ REQ : not REP: servercnt(n) point0 (un) point1(un)...
	MSG_EVENT_FLOWERTREE_2007_GROWUP,			// �������� ����Ͽ� ��ȭ ���� REQ : not REP: givePoint(un)	
	MSG_EVENT_FLOWERTREE_2007_MY_POINT,			// ���� �⿩�� ����Ʈ REQ : not REP: point(un)
	MSG_EVENT_FLOWERTREE_2007_RECV_TICKET,		// ��ȯ�� �ޱ� REQ : not REP: count(n) 
	MSG_EVENT_FLOWERTREE_2007_OPEN_TICKET,		// ��ȯ�� Ȯ�� REQ : not REP: error(uc) 0-Ƽ�Ͼ���, 1-Ƽ�ϻ��;
	MSG_EVENT_FLOWERTREE_2007_PRICE_MSG,		// ��÷ �޼��� REP : charIndex(n), itemindex(n)
} MSG_EVENT_FLOWERTREE_2007_TYPE;

typedef enum _tagMsgEventChildrensDay_2007
{
	MSG_EVENT_CHILDRENSDAY_2007_REQ,		// ��ȯ ��û	(n)ItemIndex, (n)������ ����
	MSG_EVENT_CHILDRENSDAY_2007_REP,		// �����ڵ�		(n) 0- ��ȯ ���� (n)ItemIndex, 1-������ ���� ����, 2-�̹� ���� ��� , 3-Unknown
}MSG_EVENT_CHILDRENSDAY_2007_TYPE;

typedef enum _tagMsgBuffNpc_2021
{
	MSG_BUFF_2021_REQ,		// ��ȯ ��û	(n)ItemIndex, (n)������ ����
	MSG_BUFF_FRAG_2021_REQ,		// �����ڵ�		(n) 0- ��ȯ ���� (n)ItemInd
	MSG_BUFF_FULL_INVEN,
}MSG_BUFF_NPC_2021_TYPE;

// WSS_MINIGAME 070420 ------------------------------------------------------------->>
typedef enum _tagMsgEventGomdori2007
{
	MSG_EVENT_GOMDORI_2007_CHECKITEM,			// ���������� ������ �˻�
	MSG_EVENT_GOMDORI_2007_START,				// ���������� �����ϱ�
	MSG_EVENT_GOMDORI_2007_SELECT,				// ���������� �����ϱ�	: type(c)
												// type					: ����-0, ����-1, ��-2
	MSG_EVENT_GOMDORI_2007_RESULT_WIN,			// ���������� �¸� �˸�	: wincount(c) usersel(c) npcsel(c)
	MSG_EVENT_GOMDORI_2007_RESULT_LOSE,			// ���������� �й� �˸�	: wincount(c) usersel(c) npcsel(c)
	MSG_EVENT_GOMDORI_2007_RESULT_DRAW,			// ���������� ��� �˸�	: wincount(c) usersel(c) npcsel(c)
	MSG_EVENT_GOMDORI_2007_CONTINUE,			// ���������� ��� �ϱ�
	MSG_EVENT_GOMDORI_2007_END,					// ���������� �׸� �ϱ�	: wincount(c:s) prompttype(c:s) extar1(n:s) extar2(n:s)
												// prompttype			: 0 - �Ϲ� ����: extra1(����������ε���) extra2(��������ۼ���)
												//						: 1 - ü�豳�� ����: extra1(������) extra2(������)
												//						: 2 - ���� ���� ���� �ʿ�: extra1(���þ�����1) extra2(���þ�����2)
	MSG_EVENT_GOMDORI_2007_SELECT_GIFT,			// ���⹫�� ����		: itemdbindex(n)
	MSG_EVENT_GOMDORI_2007_VIEW_STATUS,			// ��Ȳ ����			: curserver(n:s) count(n:s) [server(n:s)]:count
	MSG_EVENT_GOMDORI_2007_ERROR_NOITEM,		// ������ ������ ����
	MSG_EVENT_GOMDORI_2007_ERROR_FULLINVENTORY,	// �κ��丮 �������� ������ ���� �Ұ���
} MSG_EVENT_GOMDORI_2007_TYPE;
// -----------------------------------------------------------------------------------<<

// WSS_GUILDMASTER 070420 ------------------------------------------------------------>>

typedef enum _tagMsgEventParentsDay2007
{
	MSG_EVENT_PARENTSDAY_2007_ACCUMULATEPOINT_RANKING_LIST, // ����̳� ���� ����Ʈ ����Ʈ ���� ��û  c->s��  MessageType��
				  // s->c : error(c) count( n ) rankig( c ) savepoint( n ) gildname(str)
	MSG_EVENT_PARENTSDAY_2007_ADD_POINT,    // ����Ʈ ���
				  // c->s : CharIndex(n) echangeItemIndex(n)
				  // s->c : errorcode(c) point(n) totalpoint(n)
	MSG_EVENT_PARENTSDAY_2007_EXCHANGE_TICKET,   // ���� ����Ʈ�� ���� ��ȯ�� ��û
				  // s->c : errorcode(c) changeTicketCount(n)
	MSG_EVENT_PARENTSDAY_2007_EXCHANGE_ITEM,   // ��ȯ������ ������ ��ȯ ��û
	// s->c: errcode(c)
	MSG_EVENT_PARENTSDAY_2007_NOTICE, // ����	//s-c : guildName(str) itemName(str)

	MSG_EVENT_PARENTSDAY_2007_RESULT, // s->c : ranking(n)

}MSG_EVENT_PARENTSDAY_2007_TYPE;

typedef enum _tagParentsDay2007ErrorType
{
	MSG_ERROR_PARENTSDAY_2007_FULLINVEN,			// �κ� ���� ��
	MSG_ERROR_PARENTSDAY_2007_NO_EXCHAGNE_ITEM,		// ��ȯ�� ����
	MSG_ERROR_PARENTSDAY_2007_NOT_GUILD_OWNER,		// ������� �ƴմϴ�.
	MSG_ERROR_ACCUMULATEPOINT_NOT_RANKING,			// ��ŷ ����Ÿ�� �����ϴ�.
	MSG_ERROR_ADD_POINT,							// ����Ʈ ���� ����
	MSG_ERROR_NOT_ENOUGH_POINT,						// ����Ʈ ����
	MSG_ERROR_NOT_FOUND_ACCUMULATEPOINT_LIST,		// ���� ����Ʈ ������ �����ϴ�.
	MSG_ERROR_PARENTSDAY_2007_ERROR_NOITEM,			// ������ ����
	MSG_PARENTSDAY_2007_SUCCESS,					// ����
}MSG_PARENTSDAY_2007_ERROR_TYPE;


typedef enum _tagMsgEventSongkran2007
{
	MSG_EVENT_SONGKRAN_2007_EXCHANGE_OK,		// ��ȯ ����			exchangeType(b) 0-Silver,1-Gold	
	MSG_EVENT_SONGKRAN_2007_EXCHANGE_NOITEM,	// ������ ����			
	MSG_EVENT_SONGKRAN_2007_EXCHANGE_FULLINVEN,	// �κ� ���� ��
}MSG_EVENT_SONGKRAN_2007_TYPE;
	


typedef enum _tagMsgEventEggsHunt2007Type
{
	MSG_EVENT_EGGS_HUNT_2007_GIFT_REP_OK,					// ������ ���� ����
	MSG_EVENT_EGGS_HUNT_2007_ERROR_ALREADY_EXIST,			// ������ �ߺ� ���� �ȵ�
	MSG_EVENT_EGGS_HUNT_2007_ERROR_GIFT_FULLINVEN,			// �κ��丮 ����
	MSG_EVENT_EGGS_HUNT_2007_ERROR_NOITEM,					// ������ ����
} MSG_EVENT_EGGS_HUNT_2007_TYPE;


typedef enum _tagEventEggsHunt2007ChangeType
{
		MSG_EGGS_HUNT_CHANGE_50_NAS,				// 50���� 
		MSG_EGGS_HUNT_CHANGE_500_NAS,				// 500����
		MSG_EGGS_HUNT_CHANGE_QUALITY_STONE,			// ���� ����
		MSG_EGGS_HUNT_CHANGE_GAMMA_WAVE_ENERGY,		// C��� ����
		MSG_EGGS_HUNT_CHANGE_HERB,					// ũ���� �ٱ�
		MSG_EGGS_HUNT_CHANGE_PORTION_SPEED,			// �ӵ���� ����
		MSG_EGGS_HUNT_CHANGE_BOOSTER,				// �ν���
		MSG_EGGS_HUNT_CHANGE_GREEN_STONE,			// Ǫ����
		MSG_EGGS_HUNT_CHANGE_MAGIC_STONE,			// ������
		MSG_EGGS_HUNT_CHANGE_HEAVEN_STONE,			// �������ü�
		MSG_EGGS_HUNT_CHANGE_EXPERIENCE_SCROLL,		// ������ ��ũ��
		MSG_EGGS_HUNT_CHANGE_PLATINUM_BOOSTER,		// �÷�Ƽ�� �ν���
		MSG_EGGS_HUNT_CHANGE_CAKE,					// ����ũ
		MSG_EGGS_HUNT_CHANGE_CACAO_90,				// īī�� 90
		MSG_EGGS_HUNT_CHANGE_SNOWMAN,				// ����� ����
		MSG_EGGS_HUNT_CHANGE_GREATEST_EXP_PORTION,	// ���������� ����
		MSG_EGGS_HUNT_CHANGE_25000_NAS,				// 25000 ����
		MSG_EGGS_HUNT_CHANGE_END,
}MSG_EVENT_EGGS_HUNT_2007_CHANGE_TYPE;


typedef enum _tagMsgEventWhiteday2007
{
	MSG_EVENT_WHITEDAY_2007_EXCHANGE_REQ,		// ��ȯ ��û			exchangeType(b) 0-Skill,1-SkyLetter,2-PinkLetter 
	MSG_EVENT_WHITEDAY_2007_EXCHANGE_OK,		// ��ȯ ����			exchangeType(b) 0-Skill,1-SkyLetter,2-PinkLetter  if(0) skillIdx(n)-SkillIndex
	MSG_EVENT_WHITEDAY_2007_EXCHANGE_FAILED,	// ��ȯ ���� ( ��ų�� �����ϰų�, ���� ������ ������ ���� �Ҷ�)
	MSG_EVENT_WHITEDAY_2007_EXCHANGE_NOITEM,	// ������ ����			
	MSG_EVENT_WHITEDAY_2007_EXCHANGE_FULLINVEN,	// �κ� ���� ��
	MSG_EVENT_WHITEDAY_2007_EXCHANGE_MAXITEM,	// ������ ���� �ִ밹�� �ʰ�
	MSG_EVENT_WHITEDAY_2007_LETTER_REQ,			// ������ ��� ��û		itemIndex(n), colorIndex(n), msg(str)
	MSG_EVENT_WHITEDAY_2007_LETTER_REP,			// ������ ��� ����		colorIndex(n), msg(str)
} MSG_EVENT_WHITEDAY_2007_TYPE;


typedef enum _tagMsgEventXmas2006
{
	MSG_EVENT_XMAS_2006_ERROR_OK,				// ����
	MSG_EVENT_XMAS_2006_ERROR_FULLINVEN,		// �κ� ���� ��
	MSG_EVENT_XMAS_2006_ERROR_NOITEM,			// ������ ����
} MSG_EVENT_XMAS_2006_ERROR_TYPE;


typedef enum _tagMsgEventValentine2007Type
{
	MSG_EVENT_VALENTINE_2007_PACKAGE_OK,					// ���ڷ� ������ ���� ����			errcode(n)
	MSG_EVENT_VALENTINE_2007_PACKAGE_FULLINVEN,				// �κ�����							errcode(n)

	MSG_EVENT_VALENTINE_2007_BINGO_ITEM_ARRANGE,			// ���ڷ� ���� ��û					itempos(b), itemindex(n), bingoitemindex(n)
	MSG_EVENT_VALENTINE_2007_BINGO_ITEM_ARRANGE_OK,			// ���ڷ� ���� ����					errcode(n) score(n)
	MSG_EVENT_VALENTINE_2007_BINGO_ITEM_ARRANGE_NOTPACKAGE,	// ����� ���ڷ� �������� �ƴ�		errcode(n)
	MSG_EVENT_VALENTINE_2007_BINGO_ITEM_ARRANGE_ALREADY,	// �̹� ����� �ڸ�					errcode(n)

	MSG_EVENT_VALENTINE_2007_BINGO_GIFT,					// �����û							bingoindex(n)
	MSG_EVENT_VALENTINE_2007_BINGO_GIFT_OK,					// ���󼺰�							errcode(n), num(n)
	MSG_EVENT_VALENTINE_2007_BINGO_GIFT_NOITEM,				// ������ �ϳ��� ����				errcode(n)

	MSG_EVENT_VALENTINE_2007_BINGO_ITEM_NOTFOUND,			// �����ڽ� ������ ����				errcode(n)
} MSG_EVENT_VALENTINE_TYPE;


typedef enum _tagMsgEventChuseok2006Type
{
	MSG_EVENT_CHUSEOK_2006_MAKE_RICECAKE,					// ���� ����� ��û
	MSG_EVENT_CHUSEOK_2006_MAKE_RICECAKE_OK,				// ���� ����� ����
	MSG_EVENT_CHUSEOK_2006_MAKE_RICECAKE_FAIL,				// ���� ����� ����
	MSG_EVENT_CHUSEOK_2006_MAKE_RICECAKE_NOITEM,			// ���� ��� ����
	MSG_EVENT_CHUSEOK_2006_MAKE_RICECAKE_FULLINVEN,			// �κ��丮 ����

	MSG_EVENT_CHUSEOK_2006_MAKE_RAINBOW_CAKE,				// ���� ���� ����� ��û
	MSG_EVENT_CHUSEOK_2006_MAKE_RAINBOW_CAKE_OK,			// ���� ���� ����� ����
	MSG_EVENT_CHUSEOK_2006_MAKE_RAINBOW_CAKE_FAIL,			// ���� ���� ����� ����
	MSG_EVENT_CHUSEOK_2006_MAKE_RAINBOW_CAKE_NOITEM,		// ���� ���� ��� ����
	MSG_EVENT_CHUSEOK_2006_MAKE_RAINBOW_CAKE_FULLINVEN,		// �κ��丮 ����

	MSG_EVENT_CHUSEOK_2006_GIFT,							// ���� ���� ��ȯ ��û
	MSG_EVENT_CHUSEOK_2006_GIFT_OK,							// ���� ���� ��ȯ ����
	MSG_EVENT_CHUSEOK_2006_GIFT_OK_NOITEM,					// ���� ���� ����
	MSG_EVENT_CHUSEOK_2006_GIFT_OK_FULLINVEN,				// �κ��丮 ����

} MSG_EVENT_CHUSEOK_2006_TYPE;

typedef enum _tagMsgEventCollectBugType
{
	MSG_EVENT_COLLECT_BUG_BUY_BOX_REQ,					// [C]���� ���� ��û
	MSG_EVENT_COLLECT_BUG_BUY_BOX_REP_OK,				// [S]���� ���� ���� 1�̸� ���: isgoldenbox(n)
	MSG_EVENT_COLLECT_BUG_BUY_BOX_REP_ERROR_DUPLICATE,	// [S]�̹� ������ ����
	MSG_EVENT_COLLECT_BUG_BUY_BOX_REP_ERROR_FULLINVEN,	// [S]�κ� ���� ����
	MSG_EVENT_COLLECT_BUG_BUY_BOX_REP_ERROR_MONEY,		// [S]�� ����

	MSG_EVENT_COLLECT_BUG_GIFT_REQ,						// [C]���� ��û
	MSG_EVENT_COLLECT_BUG_GIFT_REP_OK,					// [S]���� 0���� 11����: gifttype(n)
	MSG_EVENT_COLLECT_BUG_GIFT_REP_ERROR_FULLINVEN,		// [S]�κ� ���� ����
	MSG_EVENT_COLLECT_BUG_GIFT_REP_ERROR_NOITEM,		// [S]���� ���� ���� ����
	MSG_EVENT_COLLECT_BUG_GIFT_REP_ERROR_NOTFULL,		// [S]���ڿ� ������ ����

	MSG_EVENT_COLLECT_BUG_PICK_OK,						// [S]���� ���� : bugitemdbindex(n)
	MSG_EVENT_COLLECT_BUG_PICK_NOITEM,					// [S]ä�� ���� ����
	MSG_EVENT_COLLECT_BUG_PICK_FULL,					// [S]ä�� ���� ���� ��

	MSG_EVENT_COLLECT_BUG_DROP,							// [C,S]���� ���ڿ��� n�� ���� ���� : position(n)
														// plus -> 0 ~ 7, used 8 ~ 15
} MSG_EVENT_COLLECT_BUG_TYPE;

typedef enum _tagMsgEventTldMotherday2007ErrorType
{
	MSG_EVENT_TLD_MOTHERDAY_2007_ERROR_OK,			// ��ȯ ����
	MSG_EVENT_TLD_MOTHERDAY_2007_ERROR_FULLINVEN,	// inven full
	MSG_EVENT_TLD_MOTHERDAY_2007_ERROR_NOITEM,		// itemd not exist
}MSG_EVENT_TLD_MOTHERDAY_2007_ERROR_TYPE;

typedef enum _tagMsgEventTldBuddhistErrorType
{
	MSG_EVENT_TLD_BUDDHIST_ERROR_OK,
	MSG_EVENT_TLD_BUDDHIST_ERROR_FULLINVEN,
	MSG_EVENT_TLD_BUDDHIST_ERROR_NOITEM,
} MSG_EVENT_TLD_BUDDHIST_ERROR_TYPE;

typedef enum _tagMsgEventRain2006ErrorType
{
	MSG_EVENT_RAIN_2006_ERROR_OK,				// ���� ����
	MSG_EVENT_RAIN_2006_ERROR_NOITEM,			// �����/������ ����
	MSG_EVENT_RAIN_2006_ERROR_FULLINVEN,		// �κ��丮 ������
} MSG_EVENT_RAIN_2006_ERROR_TYPE;

typedef enum _tagMsgEventGoldenballType
{
	MSG_EVENT_GOLDENBALL_VOTE_START,			// ���� ����(���̵��õ� ����)	: team1(str) team2(str) yyyy(n) mm(n) dd(n) hh(n) min(n)
	MSG_EVENT_GOLDENBALL_VOTE_END,				// ���� ����					: team1(str) team2(str)
	MSG_EVENT_GOLDENBALL_GIFT_START,			// ���� ����(���̵��õ� ����)	: team1(str) team1score(n) team2(str) team2score(n) yyyy(n) mm(n) dd(n) hh(n) min(n)
	MSG_EVENT_GOLDENBALL_GIFT_END,				// ���� ����					: team1(str) team2(str)

	MSG_EVENT_GOLDENBALL_VOTE,					// ����							: team1score(n) team2score(n) errorcode(n:s)
	MSG_EVENT_GOLDENBALL_GIFT,					// ����							: errorcode(n:s)
} MSG_EVENT_GOLDENBALL_TYPE;

typedef enum _tagMsgEventGoldenballErrorType
{
	MSG_EVENT_GOLDENBALL_ERROR_VOTE_OK,			// ��纼 ���� - ����
	MSG_EVENT_GOLDENBALL_ERROR_VOTE_ALREADY,	// ��纼 ���� - �̹� ������
	MSG_EVENT_GOLDENBALL_ERROR_VOTE_NOITEM,		// ��纼 ���� - �౸�� ����
	MSG_EVENT_GOLDENBALL_ERROR_VOTE_FULLINVEN,	// ��纼 ���� - �κ� ���� ��
	MSG_EVENT_GOLDENBALL_ERROR_VOTE_TIME,		// ��纼 ���� - ���� �Ⱓ �ƴ�

	MSG_EVENT_GOLDENBALL_ERROR_GIFT_OK_EXACT,	// ��纼 ���� - �¸���/���� ���� ���� ����
	MSG_EVENT_GOLDENBALL_ERROR_GIFT_OK_WINNER,	// ��纼 ���� - �¸��� ���� ���� ����
	MSG_EVENT_GOLDENBALL_ERROR_GIFT_OK_NONE,	// ��纼 ���� - ������ ���� ����
	MSG_EVENT_GOLDENBALL_ERROR_GIFT_FULLINVEN,	// ��纼 ���� - �κ� ���� ��
	MSG_EVENT_GOLDENBALL_ERROR_GIFT_NOITEM,		// ��纼 ���� - ���� ī�� ����
	MSG_EVENT_GOLDENBALL_ERROR_GIFT_TIME,		// ��纼 ���� - ���� �Ⱓ �ƴ�
} MSG_EVENT_GOLDENBALL_ERROR_TYPE;

typedef enum _tagMsgEventWorldcupType
{
	MSG_EVENT_WORLDCUP_VOTE,					// �¸����� ����			: country(n) errorcode(n:s)
	MSG_EVENT_WORLDCUP_GIFT,					// ��÷ ���� �ޱ�			: rank(n) errorcode(n:s)
												// rank : 1, 2, 3 - �� ���� �� ����, 4 - �׿�
} MSG_EVENT_WORLDCUP_TYPE;

typedef enum _tagMsgEventWorldcupErrorType
{
	MSG_EVENT_WORLDCUP_ERROR_VOTE_OK,			// �¸� ���� ���� : ����
	MSG_EVENT_WORLDCUP_ERROR_VOTE_NOITEM,		// �¸� ���� ���� : FIFA �� ����
	MSG_EVENT_WORLDCUP_ERROR_VOTE_NOTCHANGE,	// �¸� ���� ���� : ���� �Ⱓ �ƴ�
	MSG_EVENT_WORLDCUP_ERROR_VOTE_FULLINVEN,	// �¸� ���� ���� : �κ� ���� ����
	MSG_EVENT_WORLDCUP_ERROR_VOTE_ALREADY,		// �¸� ���� ���� : �̹� ������ ����

	MSG_EVENT_WORLDCUP_ERROR_GIFT_OK,			// �¸� ���� ���� ��÷ Ȯ�� : ���� ����
	MSG_EVENT_WORLDCUP_ERROR_GIFT_NOTCHANGE,	// �¸� ���� ���� ��÷ Ȯ�� : ��ȯ �Ⱓ �ƴ�
	MSG_EVENT_WORLDCUP_ERROR_GIFT_NOITEM,		// �¸� ���� ���� ��÷ Ȯ�� : ���� ������ ����
	MSG_EVENT_WORLDCUP_ERROR_GIFT_FULLINVEN,	// �¸� ���� ���� ��÷ Ȯ�� : �κ� ���� ����
} MSG_EVENT_WORLDCUP_ERROR_TYPE;

typedef enum _tagMsgEventRecommendType
{
	MSG_EVENT_RECOMMEND_SET,					// ��õ ���� ����			: flag(c)
	MSG_EVENT_RECOMMEND_POTION,					// ���� ���
	MSG_EVENT_RECOMMEND_MOONSTONE,				// ������ ��÷				: charindex(n) charname(str)
} MSG_EVENT_RECOMMEND_TYPE;

typedef enum _tagMsgEventOXQuizType
{
	MSG_EVENT_OXQUIZ_INVALID_TIME,				// ���� ���� �ð��� �ƴѵ� ������ �� ���
	MSG_EVENT_OXQUIZ_START,						// OX ���� ����
	MSG_EVENT_OXQUIZ_QUIZ,						// ���� ����				: quizno(n) limitsec(n) quiz(str)
	MSG_EVENT_OXQUIZ_ANSWER,					// ���� �˸�				: quizno(n) isAnswerO(c)
} MSG_EVENT_OXQUIZ_TYPE;

//�޸� �ɸ� �̺�Ʈ
typedef enum _tagEventSearchFriendErrorType
{
	MSG_EVENT_SEARCHFRIEND_ERROR_OK,				 //����.(ģ�����OK, ���� OK)
	MSG_EVENT_SEARCHFRIEND_ERROR_PACKET,			 //��Ŷ����
	MSG_EVENT_SEARCHFRIEND_ERROR_NOT_EXIST,			 //�������� �ʴ´�.
	MSG_EVENT_SEARCHFRIEND_ERROR_FULLMEMBER,		 //ģ�� ���� �ʰ�.
	MSG_EVENT_SEARCHFRIEND_ERROR_ALREADY_EXIST,		 //�̹� ģ������Ʈ�� ����.
	MSG_EVENT_SEARCHFRIEND_ERROR_NOT_MATCH_INDEX,	 //���ΰ�  ��û,���� ���̵� ��ġ�ϸ� �ȵ�.
	MSG_EVENT_SEARCHFRIEND_ERROR_HELPER_SERVER,		 //���ۼ������� ���ӿ���.
	MSG_EVENT_SEARCHFRIEND_ERROR_GAMESERVER,		 //�Ⱓ�� ������.
	MSG_EVENT_SEARCHFRIEND_ERROR_FRIENDNAME,		 //�̸��� �߸��Ǿ���.
} MSG_EVENT_SEARCHFRIEND_ERROR_TYPE;

typedef enum _tagEventSearchFriendGoodsErrorType
{
	MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_OK,				// ���� ����
	MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_TIME,			// ���� ���� : �ð� ����
	MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_END,				// ���� ���� : �Ⱓ �ƴ�
	MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_SOMEREMAIN,		// ���� ����, �Ϻ� ������ ������
	MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_NOGOODS,			// ���� ����, ���� ������ ����
	MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_NOSPACE,			// ���� ���� : ������ ĭ�� ���ڸ�.
	MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_HELPER,			// ���� ���� ����.
} MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_TYPE;

typedef enum _tagEventNewYear2006ErrorType
{
	MSG_EVENT_NEWYEAR_2006_GOODS_ERROR_OK,				// ���� ����
	MSG_EVENT_NEWYEAR_2006_GOODS_ERROR_TIME,			// ���� ���� : �ð� ����
	MSG_EVENT_NEWYEAR_2006_GOODS_ERROR_END,				// ���� ���� : �Ⱓ �ƴ�
	MSG_EVENT_NEWYEAR_2006_GOODS_ERROR_ALREADY,			// ���� ���� : �̹� ����
} MSG_EVENT_NEWYEAR_2006_GOODS_ERROR_TYPE;

typedef enum _tagEventXMas2005ErrorType
{
	MSG_EVENT_XMAS_2005_ERROR_OK,				// ���� ����
	MSG_EVENT_XMAS_2005_ERROR_NO_ITEM,			// ���� ����
} MSG_EVENT_XMAS_2005_ERROR_TYPE;

typedef enum _tagEvent2pan4panGoodsErrorType
{
	MSG_EVENT_2PAN4PAN_GOODS_ERROR_OK,			// ���� ����
	MSG_EVENT_2PAN4PAN_GOODS_ERROR_SOMEREMAIN,	// ���� ����, �Ϻ� ������ ������
	MSG_EVENT_2PAN4PAN_GOODS_ERROR_NOGOODS,		// ���� ����, ���� ������ ����
	MSG_EVENT_2PAN4PAN_GOODS_ERROR_NOSPACE,		// ���� ����
} MSG_EVENT_2PAN4PAN_GOODS_ERROR_TYPE;

typedef enum _tagEvent2pan4panBoxErrorType
{
	MSG_EVENT_2PAN4PAN_BOX_ERROR_OK,			// ���� ����
	MSG_EVENT_2PAN4PAN_BOX_ERROR_SOMEREMAIN,	// ���� ����, �Ϻ� ������ ������
	MSG_EVENT_2PAN4PAN_BOX_ERROR_NOBOX,			// ���� ����, ���� ������ ����
	MSG_EVENT_2PAN4PAN_BOX_ERROR_NOSPACE,		// ���� ����
} MSG_EVENT_2PAN4PAN_BOX_ERROR_TYPE;

typedef enum _tagEvent2pan4panWordType
{
	MSG_EVENT_2PAN4PAN_WORD_SSAWAR,				// �ڹ;׼ǽο�
	MSG_EVENT_2PAN4PAN_WORD_2PAN4PAN,			// ���ǻ���
	MSG_EVENT_2PAN4PAN_WORD_LASTCHAOS,			// ��Ʈī����
	MSG_EVENT_2PAN4PAN_WORD_LAGHAIM,			// �������
	MSG_EVENT_2PAN4PAN_WORD_NORABA,				// ����

	// ������ʹ� ���� �ڵ�
	MSG_EVENT_2PAN4PAN_WORD_OK,					// ���޼���
	MSG_EVENT_2PAN4PAN_WORD_NOITEM,				// �����ۺ���
	MSG_EVENT_2PAN4PAN_WORD_ALREADY,			// �̹� ����
} MSG_EVENT_2PAN4PAN_WORD_TYPE;

typedef enum _tagEventErrorType
{
	MSG_EVENT_ERROR_ALREADY_GIVE,				// �̹� ���޵Ǿ���
	MSG_EVENT_ERROR_INSUFF_CONDITION,			// ���� ����� : ��������(��������) : ���� ��Ÿ ( �������� )
	MSG_EVENT_ERROR_FULLINVENTORY,				// �κ��丮 ������
	MSG_EVENT_ERROR_WRONG_PACKET,				// ���ⱳȯ : ��Ŷ ����
	MSG_EVENT_ERROR_NO_MATCH,					// ���ⱳȯ : ������ ��ȯ ��� ������ ����
	MSG_EVENT_ERROR_CANT_OPTION,				// ���ⱳȯ : �ɼ� �̵� �Ҵ�
	MSG_EVENT_ERROR_WEIGHT_OVER,				// ���� �ʰ�	

	MSG_EVENT_ERROR_CHUSEOK_NO_CROP,			// �߼� �̺�Ʈ, �۹� ����
	MSG_EVENT_ERROR_CHUSEOK_NO_SOIL,			// �߼� �̺�Ʈ, ����� ����
	MSG_EVENT_ERROR_CHUSEOK_ALREADY_UPGRADE,	// �߼� �̺�Ʈ, ���̻� ���׷��̵� �Ұ���
	MSG_EVENT_ERROR_CHUSEOK_UPGRADE_OK,			// �߼� �̺�Ʈ, ���׷��̵� ����
	MSG_EVENT_ERROR_CHUSEOK_UPGRADE_FAIL,		// �߼� �̺�Ʈ, ���׷��̵� ����
	MSG_EVENT_ERROR_CHUSEOK_EXCHANGE_OK,		// �߼� �̺�Ʈ, ��ȯ ����
	MSG_EVENT_ERROR_SEPTEMBER_NAS,				// 9�� �̺�Ʈ, ���� ��÷
	MSG_EVENT_ERROR_SEPTEMBER_DROP,				// 9�� �̺�Ʈ, ����� ��÷
	MSG_EVENT_ERROR_SEPTEMBER_EXP,				// 9�� �̺�Ʈ, ����ġ ��÷
	MSG_EVENT_ERROR_SEPTEMBER_SP,				// 9�� �̺�Ʈ, ���õ� ��÷
	MSG_EVENT_GUILD_REWARD,						// �±� ��� ���� ������ ���� : nas(ll) sp(ll) 
	MSG_EVENT_ERROR_NOT_COUPON,					// ��Ű�� ������ ����, ���� �ø���
	MSG_EVENT_ERROR_ALREADY_USE_COUNPON,		// ��Ű�� ������ ����, �̹� ���� ���� ����
	MSG_EVENT_ERROR_COUPON_SUCCESS,				// ��Ű�� ������ ����, ���� ����
	MSG_EVENT_ERROR_OPENBETA_SUCCESS,			// ���º�Ÿ ������ ���� ���� : �Ϻ�  : �̱�
	MSG_EVENT_ERROR_SAKURABUD_SUCCESS,			// �ɺ����� ������ ���� ���� : cmd(c)
	MSG_EVENT_ERROR_SAKURABUD_LEAKITEM,			// �ɺ����� ������ ���� ���� �ɺ����� ���� : �Ϻ�
	MSG_EVENT_AKAN_TEMPLE_ERROR_NO_ITEM,		// (24) ��ȥ�� ¡ǥ �������� �����ϴ�.
	MSG_EVENT_AKAN_TEMPLE_ERROR_LACK_ITEM,		// (25) ��ȥ�� ¡ǥ �������� ������ ���� �մϴ�.
	MSG_EVENT_ERROR_LOI_KRATHONG_NO_ITEM,		// (26) ũ���� ���������� �����Ͽ� �̺�Ʈ �������� ���� �� ����
	MSG_EVENT_ERROR_KB_NO_ITEM,					// (27)	���� ź���� ������ �������� ��ȯ �Ұ�
} MSG_EVENT_ERROR_TYPE;

typedef enum _tagEventLetterType
{
	MSG_EVENT_LETTER_REQ,						// ��ȯ ��û	: count(n) itemdbindex(n):count		: C -> S
	MSG_EVENT_LETTER_LASTCHAOS,					// ��Ʈī���� ��÷								: S -> C
	MSG_EVENT_LETTER_NAKO,						// ���� ��÷										: S -> C
	MSG_EVENT_LETTER_KNIGHT,					// ����Ʈ ��÷										: S -> C
	MSG_EVENT_LETTER_MERAC,						// �޶�ũ ��÷										: S -> C
	MSG_EVENT_LETTER_CRIS,						// ũ���� ��÷										: S -> C
	MSG_EVENT_LETTER_LAMIAN,					// ��̾� ��÷										: S -> C
	MSG_EVENT_LETTER_ARCHWAND,					// ��ũ�ϵ� ��÷									: S -> C
	MSG_EVENT_LETTER_NOMATCH,					// ���� ���߱� ����									: S -> C
	MSG_EVENT_LETTER_WRONGPACKET,				// �̻��� ��Ŷ ����
} MSG_EVENT_LETTER_TYPE;

typedef enum _tagEventLattoType
{
	MSG_EVENT_LATTO_UPGRADE_SUCCESS,			// "��þƮ ���� ��� ������ +2�� ��÷ �Ǿ����ϴ�"
	MSG_EVENT_LATTO_BLOOD_SUCCESS,				// "������ ���� ��� ������ �ɼǿ� ��÷ �Ǿ����ϴ�"
	MSG_EVENT_LATTO_PROCESS_SUCCESS,			// "���� ���� ��� �����ۿ� ��÷ �Ǿ����ϴ�"
	MSG_EVENT_LATTO_EXPSP_SUCCESS,				// "���� ���� ��� (����ġ *%, ���õ� *)�� ��÷ �Ǿ����ϴ�" : exp(n) sp(n)
	MSG_EVENT_LATTO_PARTY_SUCCESS,				// "��Ƽ ���� ��� ������ ���ָӴϿ� ��÷ �Ǿ����ϴ�" : �ý��� â���� msg ó��
	MSG_EVENT_LATTO_CHANGE_LUCKYBAG_REQ,		// ���ָӴ� ��ȯ ��û
	MSG_EVENT_LATTO_CHANGE_LUCKYBAG_REP,		// ���ָӴ� ��ȯ ����		: type (c)
} MSG_EVENT_LATTO_TYPE;

typedef enum _tagEventLattoChangeLuckyBagType
{
	MSG_CHANGE_26LEVEL_GENERAL_STONE,			// 26���� �Ϲ� ���ü�
	MSG_CHANGE_SPECIAL_STONE,					// �������ü�
	MSG_CHANGE_22LEVEL_EVENT_WEAPON,			// 22���� �̺�Ʈ ���� (������)
	MSG_CHANGE_31LEVEL_ARMOR,					// 31���� �� ���� (������)
	MSG_CHANGE_ATTACK_UP,						// ���ݷ� �����
	MSG_CHANGE_DEFENSE_UP,						// ���� �����
	MSG_CHANGE_50000NAS,						// 5�� ����
	MSG_CHANGE_NO_LUCKYBAG,						// ��ȯ�� ���ָӴϰ� ����
} MSG_EVENT_LATTO_CHANGE_LUCKYBAG_TYPE;

typedef enum _tagPersonalShopType
{
	MSG_PERSONALSHOP_ERROR,						// ���λ��� ���� ����		: errorcode(uc)
	MSG_PERSONALSHOP_CHANGE,					// ���� ���� ��ȭ			: charindex(n) shoptype(c)
	MSG_PERSONALSHOP_SELL_START,				// �ǸŽ���					: charindex(n) shoptype(c) shopname(str) [normal_count(c) normal_item(v:normal_count) pack_price(ll) pack_count(c) pack_item(v:pack_count)]:client
												// normal_item				: row(c) col(c) item_idx(n) item_db_idx(n) count(ll) price(ll)
												// pack_item				: row(c) col(c) item_idx(n) item_db_idx(n) count(ll)
	MSG_PERSONALSHOP_SELL_LIST,					// �ǸŸ���Ʈ ��û			: charindex(n) [ shoptype(c) normal_count(c) normal_item(v:normal_count) pack_price(ll) pack_count(c) pack_item(v:pack_count)]:server
												// normal_item				: item_idx(n) item_db_idx(n) plus(n) flag(n) option_count(c) ([option_type(c) option_level(c)]:option_count) count(ll) price(ll)
												// pack_item				: item_idx(n) item_db_idx(n) plus(n) flag(n) option_count(c) ([option_type(c) option_level(c)]:option_count) count(ll)
	MSG_PERSONALSHOP_BUY,						// ���ſ�û					: charindex(n) pack_buy(c) normal_count(c) ([normal_item_index(n) normal_item_count(ll)]:normal_count)
	
} MSG_PERSONALSHOP_TYPE;

typedef enum _tagPersonalShopErrorType
{
	MSG_PERSONALSHOP_ERROR_OK,					// ����
	MSG_PERSONALSHOP_ERROR_INSUFF_SKILL,		// ��û ĳ���Ͱ� ��ų ��� ���϶�
	MSG_PERSONALSHOP_ERROR_INSUFF_WARP,			// ��û ĳ���Ͱ� ����(�̵���ġ) ���϶�
	MSG_PERSONALSHOP_ERROR_INSUFF_EXCHANGE,		// ��û ĳ���Ͱ� ��ȯ ���϶�
	MSG_PERSONALSHOP_ERROR_INSUFF_ALREADY,		// ��û ĳ���Ͱ� �̹� ���λ��� ���϶�
	MSG_PERSONALSHOP_ERROR_INSUFF_MONEY,		// ������ ���λ������� �ŷ��ϰ��� �Ҷ�
	MSG_PERSONALSHOP_ERROR_INSUFF_ETC,			// �׿� ������ ���� ���� ����(��Ŷ������� ��)
	MSG_PERSONALSHOP_ERROR_AREA,				// ���� ���� �Ұ��� �����϶�
	MSG_PERSONALSHOP_ERROR_DUPLICATION,			// �ϳ��� �������� ���� �� ����Ϸ� �� ��
	MSG_PERSONALSHOP_ERROR_NOTFOUND,			// ��� ĳ���Ͱ� ���� ��
	MSG_PERSONALSHOP_ERROR_NOTSELL,				// ��� ĳ���Ͱ� �Ǹ� ������ �ƴ� ��
	MSG_PERSONALSHOP_ERROR_NOTPACKAGE,			// ��� ĳ���Ͱ� ��Ű�� �ǸŰ� �ƴ� ��
	MSG_PERSONALSHOP_ERROR_MONEY,				// ������ ����
	MSG_PERSONALSHOP_ERROR_COUNT,				// ��� ���λ������� ��û �Ǹ�/���� ī��Ʈ�� Ŭ��
	MSG_PERSONALSHOP_ERROR_CANTPREMIUM,			// ������ �������� ��Ű�� ���� ���� �Ұ�
	MSG_PERSONALSHOP_ERROR_BUY_FULLINVENTORY,	// �κ��丮 �������� �� ��
	MSG_PERSONALSHOP_ERROR_ANYMORE_PET,			// �� ���� ������ �Ѿ ���
	MSG_PERSONALSHOP_ERROR_NOSPACE,				// �ǸŴ���� �Ա� ���� ������ ��� �Ǹ� ���ϰ� �Ǿ�����
	MSG_PERSONALSHOP_ERROR_CANNOT_USE,			// �̿��� �� ���� ���λ��� �Դϴ�
	MSG_PERSONALSHOP_ERROR_DELAY,
} MSG_PERSONALSHOP_ERROR_TYPE;

typedef enum __tagMsgExAlternateMerchant
{
	MSG_ALTERNATEMERCHANT_ERROR,				// ���λ��� ���� ����		: errorcode(uc)
	MSG_ALTERNATEMERCHANT_CHANGE,				// ���� ���� ��ȭ(����)		: charindex(n) shoptype(c)
	MSG_ALTERNATEMERCHANT_SELL_START,			// �ǸŽ���					: charindex(n) shoptype(c) shopname(str) [normal_count(c) normal_item(v:normal_count) pack_price(ll) pack_count(c) pack_item(v:pack_count)]:client
												// normal_item				: row(c) col(c) item_idx(n) item_db_idx(n) count(ll) price(ll)
												// pack_item				: row(c) col(c) item_idx(n) item_db_idx(n) count(ll)
	MSG_ALTERNATEMERCHANT_SELL_LIST,			// �ǸŸ���Ʈ ��û			: charindex(n) [ shoptype(c) normal_count(c) normal_item(v:normal_count) pack_price(ll) pack_count(c) pack_item(v:pack_count)]:server
												// normal_item				: item_idx(n) item_db_idx(n) plus(n) flag(n) option_count(c) ([option_type(c) option_level(c)]:option_count) count(ll) price(ll)
												// pack_item				: item_idx(n) item_db_idx(n) plus(n) flag(n) option_count(c) ([option_type(c) option_level(c)]:option_count) count(ll)
	MSG_ALTERNATEMERCHANT_BUY,					// ���ſ�û					: charindex(n) pack_buy(c) normal_count(c) ([normal_item_index(n) normal_item_count(ll)]:normal_count)
	
	MSG_ALTERNATEMERCHANT_END,					// �ǸŻ� ����
	MSG_ALTERNATEMERCHANT_PRODUCT_RECOVERY,		// ��ǰ ȸ�� :  
	MSG_ALTERNATEMERCHANT_PRODUCT_NAS,			// ���� ȸ�� :

}MSG_EX_ALTERNATE_MERCHANT_TYPE;

typedef enum __tagMsgExAlternateMerchatErrorType
{
	MSG_ALTERNATEMERCHANT_ERROR_OK,						// ����
	MSG_ALTERNATEMERCHANT_ERROR_INSUFF_SKILL,			// ��û ĳ���Ͱ� ��ų ��� ���϶�
	MSG_ALTERNATEMERCHANT_ERROR_INSUFF_WARP,			// ��û ĳ���Ͱ� ����(�̵���ġ) ���϶�
	MSG_ALTERNATEMERCHANT_ERROR_INSUFF_EXCHANGE,		// ��û ĳ���Ͱ� ��ȯ ���϶�
	MSG_ALTERNATEMERCHANT_ERROR_INSUFF_MONEY,			// ������ ���λ������� �ŷ��ϰ��� �Ҷ�
	MSG_ALTERNATEMERCHANT_ERROR_INSUFF_ETC,				// �׿� ������ ���� ���� ����(��Ŷ������� ��)
	MSG_ALTERNATEMERCHANT_ERROR_AREA,					// ���� ���� �Ұ��� �����϶�
	MSG_ALTERNATEMERCHANT_ERROR_DUPLICATION,			// �ϳ��� �������� ���� �� ����Ϸ� �� ��
	MSG_ALTERNATEMERCHANT_ERROR_NOTFOUND,				// ��� ĳ���Ͱ� ���� ��
	MSG_ALTERNATEMERCHANT_ERROR_NOTSELL,				// ��� ĳ���Ͱ� �Ǹ� ������ �ƴ� ��
	MSG_ALTERNATEMERCHANT_ERROR_NOTPACKAGE,				// ��� ĳ���Ͱ� ��Ű�� �ǸŰ� �ƴ� ��
	MSG_ALTERNATEMERCHANT_ERROR_MONEY,					// ������ ����
	MSG_ALTERNATEMERCHANT_ERROR_COUNT,					// ��� ���λ������� ��û �Ǹ�/���� ī��Ʈ�� Ŭ��
	MSG_ALTERNATEMERCHANT_ERROR_CANTPREMIUM,			// ������ �������� ��Ű�� ���� ���� �Ұ�
	MSG_ALTERNATEMERCHANT_ERROR_BUY_FULLINVENTORY,		// �κ��丮 �������� �� ��
	MSG_ALTERNATEMERCHANT_ERROR_ANYMORE_PET,			// �� ���� ������ �Ѿ ���
	MSG_ALTERNATEMERCHANT_ERROR_NOSPACE,				// �κ��� �������� �Ǹ� �Ұ� : �� ���� ���� ������ ����
	MSG_ALTERNATEMERCHANT_ERROR_NOCOLLECT_ITEM,			// ȸ�� �ȵ� �������� ����
	MSG_ALTERNATEMERCHANT_ERROR_TIMEOVER,				// �ð� ����
	
}MSG_EX_ALTERNATE_MERCHANT_ERROR;

typedef enum _tagRightAttackType
{
	MSG_RIGHT_ATTACK_ADD,						// ������� ����Ʈ �߰�
	MSG_RIGHT_ATTACK_DELAY,						// ������� ����Ʈ ���� ���� : 5s
	MSG_RIGHT_ATTACK_DEL,						// ������� ����Ʈ ����
} MSG_RIGHT_ATTACK_TYPE;

typedef enum _tagStashType
{
	MSG_STASH_ERROR_CODE,						// â�� ���� ����			: errorcode(uc)
	MSG_STASH_ISSETPASSWORD,					// â�� ��ȣ ���� ���� �˻�	: isset(c:s)
	MSG_STASH_LIST_REQ,							// â�� ������ ����Ʈ ��û	: password(str)
	MSG_STASH_LIST_REP, 						// â�� ������ ����Ʈ		: listflag(c) item_idx(n) plus(n) flag(n) used(n), used_2(n) option_count(c) ([option_type(c) option_level(c)]:option_count) count(ll) remain(n)
												// listflag					: (1 << 0): start, (1 << 1): end, (1 << 2): empty
												// COMPOSITE_TIME ���� used_2(n) �߰�
	MSG_STASH_KEEP_REQ,							// â���� ���� �ñ��		: password(str) keepcount(n) [row(c) col(c) item_idx(n) count(ll)]:keepcount
												// keepcount				: 1 ~ 10
	MSG_STASH_KEEP_REP,							// �ñ�� ���				: keepcount(n) [itemdbindex(n) count(ll)]:keepcount
	MSG_STASH_TAKE_REQ,							// ã�� ��û				: password(str) takecount(n) [item_idx(n) count(ll)]:takecount
												// takecount				: 1 ~ 10
	MSG_STASH_TAKE_REP,							// ã�� ���				: takecount(n) [itemdbindex(n) count(ll)]:keepcount
	MSG_STASH_CHANGE_PASSWORD_REQ,				// �н����� ���� ��û		: old(str) new(str)
	MSG_STASH_CHANGE_PASSWORD_REP,				// �н����� ���� ���		: isset(c:s)
	MSG_STASH_SEAL,								// ��� ��û/���

	MSG_STASH_DELETE_PASSWORD_REQ,				// ��ȣ�нǽ� ���� ��û		: idnum(str)
	MSG_STASH_DELETE_PASSWORD_REP,				// ��ȣ�н� ���			: success  :0 ���� 1: Ʋ�� �ֹι�ȣ 2:��Ÿ
	MSG_STASH_CHECK_PASSWORD_REQ,				// ��ȣ Ȯ��				: pass(str)
	MSG_STASH_CHECK_PASSWORD_REP,				// ���						
	MSG_STASH_SETTING_NEWPASSWORD_REQ,			// ��ȣ ����				: pass(str)	
	MSG_STASH_SETTING_NEWPASSWORD_REP,			// ���						: bsuccess 
	MSG_STASH_KEEP_MONEY,						//â�� ���� �ñ�� password(str) count(ll)
	MSG_STASH_TAKE_MONEY,						//â�� ���� ã�� password(str) count(ll)
	MSG_STASH_SEARCH_MONEY_REQ,					//â�� ���� ��ȸ 
	MSG_STATS_SEARCH_MONEY_REP,					//â�� ���� ��ȸ ��� count(ll)
												//	bsuccess 0: ���� 1: ���� 2: ��ȣ
} MSG_STASH_TYPE;

typedef enum _tagStashErrorType
{
	MSG_STASH_ERROR_OK,							// ����
	MSG_STASH_ERROR_CANNOT_STATE,				// â�� �̿��� �Ҽ� ���� ����: ���� ����, ������, ��ų ������, ������, ���λ���, ��ȯ�߿����� �Ұ���
	MSG_STASH_ERROR_NOTCOMPLETE,				// ���� â�� ��û�� ������ ���� �ʾ���
	MSG_STASH_ERROR_SEALED,						// â�� ��� ��� ����
	MSG_STASH_ERROR_WRONG_PASSWORD,				// ��ȣ Ʋ��
	MSG_STASH_ERROR_WRONG_PACKET,				// ��Ŷ ���� ����
	MSG_STASH_ERROR_MONEY,						// �� ����
	MSG_STASH_ERROR_STASH_FULL,					// â�� ���� ��
	MSG_STASH_ERROR_WEIGHT_OVER,				// ���� �ʰ��� ã�� �� ����
	MSG_STASH_ERROR_INVENTORY_FULL,				// �κ��丮 ���� �ʰ��� ã�� �� ����
	MSG_STASH_ERROR_WRONG_CHAR,					// ��ȣ�� �߸��� ���ڰ� ��
	MSG_STASH_ERROR_CANNOT_SEAL,				// ��ۼ� ����
	MSG_STASH_ERROR_ALREADY_SEAL,				// �̹� ���
} MSG_STASH_ERROR_TYPE;

typedef enum _tagGuildType
{
	MSG_GUILD_ERROR,						// ��� ���� ����		: errorcode(c)
	MSG_GUILD_CREATE,						// ��� ����			: name(str)
	MSG_GUILD_INFO,							// �� ��� ���� ������	: guildindex(n) guildname(str) guildlevel(n) mypos(n) battle_guildindex(n) battle_killcount(n) battle_prize(n) battle_zone(n) battle_time(n)
											// ��� ������ guildindex == -1, ���� �׸� ����
	MSG_GUILD_MEMBERLIST,					// ��� ����Ʈ			: guildindex(n) count(n) [index(n) name(str) position(n) online(c)]:count
	MSG_GUILD_ONLINE,						// ���� �¶��� ����	: guildindex(n) charindex(n) charname(str) online(c)
	MSG_GUILD_LEVELUP,						// ��� �±�			: 
	MSG_GUILD_LEVELINFO,					// ��� ���� ����		: guildindex(n) guildlevel(n)
	MSG_GUILD_BREAKUP,						// �ػ� ��û			: 
	MSG_GUILD_BREAKUP_NOTIFY,				// ��� �ػ��� �˸�		: guildindex(n) guildname(str)
	MSG_GUILD_REGIST_REQ,					// ���� ��û ��û		: guildindex(n) bossindex(n) requesterindex(n)
	MSG_GUILD_REGIST_ALLOW,					// ���� ��û ���		: guildindex(n) requesterindex(n)
	MSG_GUILD_REGIST_CANCEL,				// ���� ��û ���		: bCancelTarget(c)
	MSG_GUILD_OUT_REQ,						// Ż��					: guildindex(n)
	MSG_GUILD_CHANGE_BOSS,					// ���� ����			: guildindex(n) current(n) newboss(n)
	MSG_GUILD_APPOINT_OFFICER,				// �δ��� �Ӹ�			: guildindex(n) charindex(n)
	MSG_GUILD_FIRE_OFFICER,					// �δ��� ����			: guildindex(n) charindex(n)
	MSG_GUILD_KICK,							// ����	��û			: guildindex(n) charindex(n)
	MSG_GUILD_MEMBER_ADD,					// ��� �߰� �˸�		: guildindex(n) charindex(n) charname(str)
	MSG_GUILD_MEMBER_OUT,					// ��� Ż�� �˸�		: guildindex(n) charindex(n) charname(str)
	MSG_GUILD_MEMBER_KICK,					// ��� ���� �˸�		: guildindex(n) bossindex(n) charindex(n) charname(str)
	MSG_GUILD_INFO_CHANGE,					// ��� ���� ����		: charindex(n) guildindex(n) guildname(str) pos(n)

	MSG_GUILD_BATTLE_REQ_REQ,				// ����� ��û ��û		: charindex(n) or guildindex(n) guildname(n) prize(n) time(n)
	MSG_GUILD_BATTLE_REQ_REJECT,			// ����� ��û ����		: reject_charindex(n)
	MSG_GUILD_BATTLE_REQ_ACCEPT,			// ����� ��û ���		: guildindex1(n) guildname1(n) guildindex2(n) guildname2(n) prize(n) zone(n) time(n)
	MSG_GUILD_BATTLE_STOP_REQ,				// ����� �ߴ� ��û		: charindex(n) or guildindex(n) guildname(n) 
	MSG_GUILD_BATTLE_STOP_REJECT,			// ����� �ߴ� ����		: reject_charindex(n)
	MSG_GUILD_BATTLE_STOP_ACCEPT,			// ����� �ߴ� ���		:
	MSG_GUILD_BATTLE_START,					// ����� ���� �˸�		: guildindex1(n) guildname1(n) guildindex2(n) guildname2(n) prize(n) zone(n) time(n)
	MSG_GUILD_BATTLE_STATUS,				// ����� ��Ȳ			: guildindex1(n) guildname1(str) killcount1(n)guildindex2(n) guildname2(str) killcount2(n) battletime(n)
	MSG_GUILD_BATTLE_END,					// ����� ����			: winner_guildindex(n) guildindex1(n) guildname1(n) guildindex2(n) guildname2(n) prize(n)
	MSG_GUILD_BATTLE_SCORE_INIT,			// ����� ��� �̺�Ʈ ���ھ�� off

	MSG_GUILD_WAR_SET_TIME_REQ,				// ���� �ð� ���� ��û	: wday(n) hour(n)
	MSG_GUILD_WAR_GET_TIME,					// ���� �ð� Ȯ��		: warerrorcode(n:s) guildindex(n:s) guildname(n:s) month(c:s) day(c:s) hour(c:s) min(c:s)
	MSG_GUILD_WAR_NOTICE_TIME,				// ���� �ð� Ȯ�� �˸�	: zoneindex(n) month(c) day(c) hour(c) min(c)
	MSG_GUILD_WAR_NOTICE_TIME_REMAIN,		// ���� ���� ���� �ð� �˸�	: zoneindex(n) min(c)
	MSG_GUILD_WAR_START,					// ���� ���� �˸�		: zoneindex(n) remainSec(n)
	MSG_GUILD_WAR_JOIN_ATTACK_GUILD,		// ���� ��� ��û ��û	: warerrorcode(n:s) month(c:s) day(c:s) hour(c:s) min(c:s)
	MSG_GUILD_WAR_JOIN_DEFENSE_GUILD,		// ���� ��� ��û ��û	: warerrorcode(n:s) month(c:s) day(c:s) hour(c:s) min(c:s)
	MSG_GUILD_WAR_JOIN_ATTACK_CHAR,			// ���� �뺴 ��û ��û	: warerrorcode(n:s) month(c:s) day(c:s) hour(c:s) min(c:s)
	MSG_GUILD_WAR_JOIN_DEFENSE_CHAR,		// ���� �뺴 ��û ��û	: warerrorcode(n:s) month(c:s) day(c:s) hour(c:s) min(c:s)
	MSG_GUILD_WAR_POINT,					// ���� ��� ����Ʈ �˸�: remain_sec(n) guild1_index(n) guild1_name(str) guild1_point(n) guild2_index(n) guild2_name(str) guild2_point(n) guild3_index(n) guild3_name(str) guild3_point(n) my_guild_point(n) defense_point(n)
	MSG_GUILD_WAR_NOTICE_START_CASTLE,		// ������ ���� ���� �˸�: zoneindex(n) remain_sec(n) guildindex1(n) guildname1(str) guildindex2(n) guildname2(str) guildindex3(n) guildname3(str)
	MSG_GUILD_WAR_NOTICE_REMAIN_FIELD_TIME,	// ���� ���� �ð� �˸�	: zoneindex(n) remainSec(n)
	MSG_GUILD_WAR_CASTLE_STATE,				// ���� ���� ��Ȳ �˸�	: zoneindex(n) state(n) gatestate(n) remain_sec(n) guild1_index(n) guild1_name(str) guild1_point(n) guild2_index(n) guild2_name(str) guild2_point(n) guild3_index(n) guild3_name(str) guild3_point(n) my_guild_point(n) defense_point(n)
											// state				: 0 - �Ϲ�, 1 - ����, 2 - ����
	MSG_GUILD_WAR_GATE_STATE,				// ���� ���� ������ �˸�: old_gate_state(n) new_gate_state(n)
	MSG_GUILD_WAR_ATTACK_SYMBOL,			// ���� ���� ��û		: 
	MSG_GUILD_WAR_END,						// ���� ����			: zoneindex(n) bWinDefense(c) owner_index(n) owner_name(str) char_index(n) char_name(str) nextMonth(n) nextDay(n) nextHour(n) wDay(n)
	MSG_GUILD_WAR_SET_TIME_REP,				// ���� �ð� ���� ����	: warerrorcode(n) month(c:s) day(c:s) hour(c:s) min(c:s)
	MSG_GUILD_WAR_INVALID_COMMAND,			// ������ �Ұ����� ��� ������ ��û : req_msg_type(uc)
											// req_msg_type : MSG_GUILD_TYPE

	MSG_GUILD_STASH_HISTORY_REQ,			// �Աݳ��� ��û		: 
	MSG_GUILD_STASH_HISTORY_REP,			// �Աݳ��� ����		: errcode(n) [month(n) day(n) money(ll)]:7
	MSG_GUILD_STASH_VIEW_REQ,				// ����� �ܾ� ��û		: 
	MSG_GUILD_STASH_VIEW_REP,				// �ܾ� ����			: errcode(n) money(ll)
	MSG_GUILD_STASH_TAKE_REQ,				// ��� ��û			: money(ll)
	MSG_GUILD_STASH_TAKE_REP,				// ��� ����			: errcode(n)
	// Date : 2005-09-06(���� 10:57:55), By Lee Ki-hwan
	
	// WSS_NEW_GUILD_SYSTEM 070704 --------------------------------------------------------------------------------->>
	MSG_NEW_GUILD_INCLINE_ESTABLISH,			// ��� ���� ���� : errocode(n:s), guildindex(n:s),guildinline(c:s), guildincline(c)
	MSG_NEW_GUILD_MEMBER_ADJUST,				// ���� ���� ���� : (n)charIndex (s)name (n)exp (n)fame ,errocode(c:s), (c)stash(0:�Ұ�,1:����)		
	MSG_NEW_GUILD_INFO,							// ����� ���ο� ���� : guildname(str) guildlevel(n) bossname(str) membercount(n) maxmembercount(n) avelevel(n) guildpoint(n) contributepoint(n)
	MSG_NEW_GUILD_MEMBERLIST,					// ���ο� ����� ��� ����Ʈ : maxmembercount(n) charname(str) positionname(str) charlevel(n) bplaying(b) zoneindex(n) contributepoint(n) job
	MSG_NEW_GUILD_SKILL,						// ��� ��ų skillcount(n) skillindex(n) skillLeanLevel(n) skillMaxLevel(n) - s
	MSG_NEW_GUILD_NOTICE,				// ����� ���� ���� ��û  
	MSG_NEW_GUILD_NOTICE_UPDATE,		// ��� ���� ���� ������Ʈ : title(str) text(str) , errorcode(c:s)
	MSG_NEW_GUILD_NOTICE_REQUEST,		// ����� ���� ��û
	MSG_NEW_GUILD_NOTICE_TRANSMISSION,	// ��� ���� �ޱ� : guildname(str) title(str) text(str) -s
	MSG_NEW_GUILD_MANAGE,				// ����� ���ο� �Ŵ��� :firstlistmember(c) membercount(n), [guildpos(n), membername(str) positionname(str) charlevel(n) contributeExp(n) contributeFame(n) index(n) stash(c) ] guildGrade(n) guildGrade_point(n)
	MSG_NEW_GUILD_SKILL_LEARN,			// ��� ��ų ���� c->s: skillindex(n) // s->c: skill_index(n) is_new(uc) skill_level(c)
	MSG_NEW_GUILD_POINT_RANKING,		// ��� ��ŷ ���� charindex(n) guildindex(n) ranking(n) 
	// ---------------------------------------------------------------------------------------------------------------<<
	//////////////////////////////////////////////////////////////////////////
	// ���� 4���� �޼����� ���������� ���(����� ������ ����ϴ� �޼����� ���� Ÿ���� �����Ұ�
	MSG_GUILD_BATTLE_COMMAND_REQ,			// ����� ���ɾ� �غ� : guildindex(n) time(n) 
	MSG_GUILD_BATTLE_COMMAND_START,			// ����� ���ɾ� ���� : guildindex1(n) guildname1(str) guildindex2(n) guildname2(str) zone(n) time(n)
	MSG_GUILD_BATTLE_COMMAND_STOP,			// ����� ���ɾ� �����غ� : guildindex1(n), guildindex2(n)
	MSG_GUILD_BATTLE_COMMAND_END,			// ����� ���ɾ� ���� : winner_guildindex(n) guildindex1(n) guildname1(str) guildindex2(n) guildname2(str)
	//////////////////////////////////////////////////////////////////////////
	MSG_GUILD_BATTLE_KILL_MASTER,			// ����� �����޼���(��帶���� ����� �׿�����)
	MSG_GUILD_BATTLE_NOW_SCORE,				// ����� �����޼���(��� ����Ʈ �ȳ�)
	MSG_GUILD_BATTLE_BEFORE,				// ����� �����޼���(��ʸ�Ʈ 1���� ���۾ȳ� �޼���)
	MSG_GUILD_BATTLE_END_NOTICE_SAME_ZONE,	// ����� �����޼���(��ʸ�Ʈ ���� �޼���)
	MSG_GUILD_BATTLE_START_NOTICE_SAME_ZONE, // ����� �����޼���(��ʸ�Ʈ ���� �޼���)
	MSG_GUILD_GP_INFO,							// ��彺ų���ñ渶��GP���������÷ξ˾ƾ��ϴµ�, GP���ٲ𶧸��ٺ�������GP������.
	MSG_CASTLE_BUFF,
	MSG_GUILD_WAR_SET_TIME_MENU,  	  		// ���� �ð� ���� �޴� : count(c), zone(c), wday(c), hour(c)
	MSG_GUILD_WAR_GET_TIME_UNI_REQ,			// ���� �ð� Ȯ�� ��û : zone(c)
	MSG_GUILD_WAR_GET_TIME_UNI_REP,	  		// ���� �ð� Ȯ�� ���� : zone(c), month(c), day(c), hour(c), wday(c), count(c), joinflag(c), guildname(s), guildbossname(s)
	MSG_NEW_GUILD_MARK_EDIT_WND,            // [sora] GUILD_MARK
	MSG_NEW_GUILD_MARK_EDIT_FIN,            // [sora] GUILD_MARK
	MSG_NEW_GUILD_MARK_EXPIRE,              // [sora] GUILD_MARK
	// guild stash renewal [6/20/2011 rumist]
	MSG_NEW_GUILD_STASH_LIST,				// (n)totalpage, (n)curpage , itemCount < stashIndex , itemIndex, plus, flag, a_used, a_used2, (short) option[5],  (str) socket >
	MSG_NEW_GUILD_STASH_KEEP,				// (n)itemCount [ (n)itemIndex, (n)row, (n)col , count ]
	MSG_NEW_GUILD_STASH_TAKE,				// (n)itemCount [ (n)itemIndex, (c) row, (c) col , (_64) count ]
	MSG_NEW_GUILD_STASH_LOG,				// (n)logcount [(n)log-index (_64)time, (str)name, (c)action( 0:�Ա�, 1:��� ), (n)itemindex , (n)plus, (_64)count]
	MSG_NEW_GUILD_STASH_ERROR,				// error
	MSG_NEW_GUILD_STASH_LIST_MONEY,		//��� â�� �� ��ȸ	//�������̶� ����
	MSG_GUILD_MASTER_KICK_REQ,				// C -> S	(int)guild index	��帶���� �߹� ��û
	MSG_GUILD_MASTER_KICK_REP,				// S -> C	(int)guild index (str)guild master	��帶���� �߹� ����
	MSG_GUILD_MASTER_KICK_CANCEL_REQ,		// C -> S	(int)guild index	��帶���� �߹� ��������
	MSG_GUILD_MASTER_KICK_CANCEL_REP,		// S -> C	(int)guild index ��帶���� �߹� �������� ����
	MSG_GUILD_MASTER_KICK_STATUS,			// S -> C	(int)guild index (int)status	��帶���� �߹� ���°�

	MSG_GUILD_REMOTE_JOIN_REQ,				// (str)target name (int)type : 0 - �渶�� ��û, 1 - ����ĳ���Ͱ� ��û ��� ���� ���� ��û : �渶�� �Ϲ����� ��� ��� �����ϴ�.
	MSG_GUILD_REMOTE_JOIN_OK,				// (str)target name (int)type : 0 - �渶�� ��û, 1 - ����ĳ���Ͱ� ��û ��� ���� ���� ��û ���
	MSG_GUILD_REMOTE_JOIN_NO,				// ��� ���� ���� ����
	MSG_GUILD_ROOM_RECALL,					// ���� ����
	MSG_GUILD_CONTRIBUTE_DATA,			
	MSG_GUILD_CONTRIBUTE_SET,			
	MSG_GUILD_CONTRIBUTE_SETALL
} MSG_GUILD_TYPE;

typedef enum _tagGuildStashErrorType
{
	MSG_GUILD_STASH_ERROR_OK,				// ����
	MSG_GUILD_STASH_ERROR_NOHISTORY,		// �����丮 ����
	MSG_GUILD_STASH_ERROR_NOTBOSS,			// �����/�ΰ� �ƴ�
	MSG_GUILD_STASH_ERROR_NOTENOUGH,		// �ܾ� ����
	MSG_GUILD_STASH_ERROR_FAIL_DB,			// �ý��� ����

	// ���� �޽����� ������ ��� â�� ������ �����ؾ���
	MSG_GUILD_STASH_ERROR_NOSPACE,			// �κ��丮 ���� �������� ���� �Ұ�
} MSG_GUILD_STASH_ERROR_TYPE;



typedef enum _tagGuildErrorType
{
	MSG_GUILD_ERROR_OK,							// ����
	MSG_GUILD_ERROR_PACKET,						// ��Ŷ ���� ����
	MSG_GUILD_ERROR_GUILDNAME,					// �̸� ����(2~16)�� �߸��Ǿ��ų�, ��� �̸��� �߸��� ����(\'"%_) ����
	MSG_GUILD_ERROR_ALREADYBOSS,				// ������̳� ������ ��� â�� �Ұ���
	MSG_GUILD_ERROR_CHARLEVEL,					// ĳ���� ���� ����
	MSG_GUILD_ERRRO_SKILLPOINT,					// ��ų ����Ʈ ����
	MSG_GUILD_ERROR_MONEY,						// ���� ����
	MSG_GUILD_ERROR_GAMESERVER,					// ���Ӽ��� ������ ���ؼ� ���� �Ұ�
	MSG_GUILD_ERROR_DUPNAME,					// �̸� �ߺ�
	MSG_GUILD_ERROR_NOGUILD,					// ��� ���µ� ��� ���� �޽����� ��û�� ��
	MSG_GUILD_ERROR_NOTBOSS,					// ������� �ƴѵ� ���� �޽����� ��û�� ��
	MSG_GUILD_ERROR_MAXLEVEL,					// �̹� �ְ����� ����ε� �±� ��û�� ��
	MSG_GUILD_ERROR_CREATE_OK,					// ����� ����
	MSG_GUILD_ERROR_LEVELUP_OK,					// ������ ����
	MSG_GUILD_ERROR_BREAKUP_OK,					// �ػ� ����
	MSG_GUILD_ERROR_TARGET_NOBOSS,				// ����� ������� �ƴϾ ���� ��û�� �� �� ����
	MSG_GUILD_ERROR_TARGET_BUSY,				// ����� �ٸ� ������� ��û�� ����
	MSG_GUILD_ERROR_SOURCE_BUSY,				// ���� �ٸ� ������� ��û�� �� ���� �ȵ� ���¿��� �ٽ� ��3�ڿ��� ��û
	MSG_GUILD_ERROR_FULLMEMBER,					// ��� ������ �ʰ�
	MSG_GUILD_ERROR_REGIST_OK,					// ���� ���� �Ϸ�
	MSG_GUILD_ERROR_OUTBOSS,					// ������� Ż���Ϸ��� ����
	MSG_GUILD_ERROR_OUT_OK,						// Ż�� ����
	MSG_GUILD_ERROR_NOTFOUNDMEMBER,				// ����, �Ӹ�, ���ӵ�� ��� ����� ������
	MSG_GUILD_ERROR_CANTKICKBOSS,				// ������ ���� �Ҵ�
	MSG_GUILD_ERROR_KICK_OK,					// ���� ����
	MSG_GUILD_ERROR_CHANGE_BOSS_OK,				// ���� ���� ����
	MSG_GUILD_ERROR_CANTOFFICER,				// ������̳� �ΰ��� �ٽ� �ΰ����� �Ӹ���
	MSG_GUILD_ERROR_APPOINT_OFFICER_OK,			// �ΰ� �Ӹ� ����
	MSG_GUILD_ERROR_FULLOFFICER,				// �ΰ� ���� ��
	MSG_GUILD_ERROR_NOTOFFICER,					// �ΰ��� �ƴ϶� ���� �Ұ�
	MSG_GUILD_ERROR_FIRE_OFFICER_OK,			// ���� ����S
	MSG_GUILD_ERROR_REGDELAY,					// ������ 10���� ������ �ʾ� Ż�� �Ұ�
	MSG_GUILD_ERROR_CANTKICK,					// ���� �Ұ���(�δ����� �δ��� �����)
	MSG_GUILD_ERROR_CANNOT_REGIST_REQ_BATTLE,	// ����� �߿��� ���Խ�û �Ұ�
	MSG_GUILD_ERROR_CANNOT_BREAK_BATTLE,		// ������ - ����� �� ��� ��ü �Ұ�
	MSG_GUILD_ERROR_CANNOT_KICK_BATTLE,			// ������ - ����� �� ���� �Ұ�
	MSG_GUILD_ERROR_CANNOT_OUT_BATTLE,			// ������ - ����� �� Ż�� �Ұ�

	MSG_GUILD_ERROR_BATTLE,						// ����� ����		: errtype(uc)
	MSG_GUILD_ERROR_CANNOT_BREAK_WAR,			// ����� ���� ��� ��ü�� �Ұ���
	// WSS_NEW_GUILD_SYSTEM 070704 --------------------------------------------------------------------------------->>
	MSG_NEW_GUILD_ERRROR_GUILDPOINT,			// ��� �������� ��� ����Ʈ ���� 
	MSG_NEW_GUILD_ERROR_SAME_INCLNE,			// ��� ������ ����
	MSG_NEW_GUILD_ERROR_CHANG_INCLINE,			// ��� ���� ���� ����
	MSG_NEW_GUILD_ERROR_INCLINE_OK,				// ��� ���� ���� ����
	MSG_NEW_GUILD_ERROR_ADJUST_FAIL,			// ��� �������  ���� ���� ����
	MSG_NEW_GUILD_ERROR_ADJUST_OK,	
	MSG_NEW_GUILD_INFO_ERROR_OK,				// ���ο� ��� ���� ��û ����
	MSG_NEW_GUILD_MEMBERLIST_ERROR_OK,			// ���ο� ��� ��� ����Ʈ ��û ����
	MSG_NEW_GUILD_MANAGE_ERROR_OK,				// ���ο� ��� �Ŵ��� ��û ����
	MSG_NEW_GUILD_NOTICE_ERROR_OK,				// ���ο� ��� ���� ��û ����
	MSG_NEW_GUILD_NOTICE_UPDATE_ERROR_OK,		// ���ο� ��� ���� ������Ʈ ����
	MSG_NEW_GUILD_NOTICE_UPDATE_ERROR_FAIL,		// ���ο� ��� ���� ������Ʈ ����
	MSS_NEW_GUILD_NOTICE_TRANSMISSION_ERROR_OK,
	MSS_NEW_GUILD_NOTICE_TRANSMISSION_ERROR_FAIL,
	MSG_NEW_GUILD_SKILL_ERROR_OK,				// ��� ��ų ����
	MSG_NEW_GUILD_SKILL_ERROR_NOTEXIST,			// ��� ��ų�� ����
	MSG_NEW_GUILD_NOTICE_ERROR_NOT_MESSAGE,		// �޼����� ����.
	MSG_NEW_GUILD_SKILL_LEARN_ERROR_OK,	
	MSG_NEW_GUILD_SKILL_LEARN_ERROR_LEVEL,		// ���� ����
	MSG_NEW_GUILD_SKILL_ALEADY_LEARN,			// �̹� ��� ��ų
	MSG_NEW_GUILD_STASH_AREADY_USE_NAS,			// 6511 ������� �ý����� ������̾ â������ ����� �� �����ϴ�.
	MSG_NEW_GUILD_POINT_AREADY_USE,				// 6510 ������� �ý����� ������̾ ��� ����Ʈ�� ����� �� �����ϴ�.
	MSG_GUILD_GRADE_EX_ERROR_WARCASTLE,			// ���� �߿��� ������ �� �����ϴ�.
	MSG_GUILD_GRADE_EX_ERROR_COUNT_OEVER,		// ������ �� �ִ� �ο� ���� �ʰ� �Ͽ����ϴ�.
	MSG_GUILD_ERROR_CANNOT_BOSSCHANGE_FAIL,		// ���(��)���� ������ �� �����ϴ�.
	MSG_NEW_GUILD_ERROR_SYSTEM,             // [sora] GUILD_MARK
	MSG_NEW_GUILD_ERROR_OK_MARK_WND,        // [sora] GUILD_MARK
	MSG_NEW_GUILD_ERROR_MASTER_KICK_RESERVE,			// �渶 ���� ��� �����Դϴ�.
	MSG_NEW_GUILD_ERROR_MASTER_KICK_LAST_CONNECT,		// �渶 �ֱ� ���� �������� 7���� ���� �ʾ� ������ �� �����ϴ�.
	MSG_NEW_GUILD_ERROR_MASTER_KICK_LAST_CHANGE,		// �渶 �ֱ� ���� ���� 7���� ���� �ʾ� ������ �� �����ϴ�.
	MSG_NEW_GUILD_ERROR_MASTER_KICK_CANCEL_NOT_RESERVE,	// ���� ��� ���°� �ƴ϶� ����� �� �����ϴ�.
	MSG_NEW_GUILD_ERROR_MASTER_KICK_DATA,				// ��� ���� ������ ����
	MSG_NEW_GUILD_ERROR_NOT_EXIST_CHAR,					// ������ ĳ���Ͱ� �߸��Ǿ����ϴ�.
	MSG_NEW_GUILD_ERROR_EXIST_GUILD,					// ������ ĳ���Ͱ� ��尡 �ֽ��ϴ�.
	MSG_GUILD_ERROR_CANNOT_REGIST_REQ_SERVERTRANS, // ĳ���� ���������� ��� ���� �Ұ� [7/25/2012 Ranma]
	MSG_GUILD_ERROR_NOT_EXIST_NPC,						// ������ NPC�� ����.
	MSG_GUILD_ERROR_CANNOT_REGISTER_REQ_ZONE,			// �� ���������� ��� ���� �Ұ�
	MSG_GUILD_ERROR_ITEM,								// ������ ����
	MSG_GUILD_ERROR_CANNOT_BREAK_10DAYS,				// �����Ϸκ��� 10���� ������ �ʾ� ��带 ������ �� �����ϴ�.
	MSG_GUILD_ERROR_CONTRIBUTE_SET_SUCCESS,				// �ڽ��� ������� ���� ����
	MSG_GUILD_ERROR_CONTRIBUTE_SET_FAIL,				// �ڽ��� ������� ���� ����
	MSG_GUILD_ERROR_CONTRIBUTE_SET_ALL_SUCCESS,			// ��� ���� ������� ���� ����
	MSG_GUILD_ERROR_CONTRIBUTE_SET_ALL_FAIL,			// ��� ���� ������� ���� ����
	MSG_GUILD_ERROR_CONTRIBUTE_INVALID_VALUE,			// ��ġ�� �߸� �Է�
	// --------------------------------------------------------------------------------------------------------------<<
} MSG_GUILD_ERROR_TYPE;

typedef enum _tagGuildErrorBattleType
{
	MSG_GUILD_ERROR_BATTLE_NOGUILD,				// ����� - ���� ��尡 ����
	MSG_GUILD_ERROR_BATTLE_NOTBOSS,				// ����� - ������� ����
	MSG_GUILD_ERROR_BATTLE_MEMBERCOUNT,			// ����� - �ο� �� ����
	MSG_GUILD_ERROR_BATTLE_ZONE,				// ����� - ���� ���� �ƴ�
	MSG_GUILD_ERROR_ALREADY_BATTLE,				// ����� - �̹� ����� ��
	MSG_GUILD_ERROR_BATTLE_PRIZE,				// ����� - ���ñݾ� ��ü ���� (����� ���� ���ݾ��� �ƴ�)
	MSG_GUILD_ERROR_BATTLE_NOT_REQ,				// ����� - ��û���� ����
	MSG_GUILD_ERROR_BATTLE_SHORT_PRIZE,			// ����� - ���ñݾ� ������
	MSG_GUILD_ERROR_BATTLE_NOT_BATTLE,			// ����� = ����� ���� �ƴ�

	MSG_GUILD_ERROR_BATTLE_TIME,				// ����� - �ð��� �߸� ��

} MSG_GUILD_EROOR_BATTLE_TYPE;

typedef enum _tagGuildPositionType
{
	MSG_GUILD_POSITION_BOSS,				// 0 ��� ������
	MSG_GUILD_POSITION_OFFICER,				// 1 ��� �ΰ�
	MSG_GUILD_POSITION_MEMBER,				// 2 �Ϲ� ����
	MSG_GUILD_POSITION_RUSH_CAPTAIN,		// 3 ������ ����
	MSG_GUILD_POSITION_SUPPORT_CAPTAIN,		// 4 ������ ����
	MSG_GUILD_POSITION_RECON_CAPTAIN,		// 5 ������ ����
	MSG_GUILD_POSITION_RUSH_MEMBER,			// 6 ��������
	MSG_GUILD_POSITION_SUPPORT_MEMBER,		// 7 ��������
	MSG_GUILD_POSITION_RECON_MEMBER,		// 8 ��������
	MSG_GUILD_POSITION_UNKNOWN = 99,
} MSG_GUILD_POSITION_TYPE;

typedef enum _tagGuildWarErrorType
{
	MSG_GUILD_WAR_ERROR_OK,						// ����
	MSG_GUILD_WAR_ERROR_PROGRESS_WAR,			// ���� ���� ��
	MSG_GUILD_WAR_ERROR_JOIN_OWNER_GUILD,		// �������� �����ϰڴٰ� ��� ��
	MSG_GUILD_WAR_ERROR_JOIN_NOT_GUILD,			// ��� ���� ���� ���� ��û�ϰڴٰ� ��� ��
	MSG_GUILD_WAR_ERROR_JOIN_ALREADY,			// �̹� ��û�� ���� �ڲ� �ϰڴٰ� �� ��
	MSG_GUILD_WAR_ERROR_JOIN_TIME,				// ��û ���� �ð��� �ƴ� ��
	MSG_GUILD_WAR_ERROR_JOIN_GUILDLEVEL,		// ��� ���� �����ؼ� ���� ��û �Ұ�
	MSG_GUILD_WAR_ERROR_JOIN_GUILDMEMBER,		// ���� �����ؼ� ���� ��û �Ұ�
	MSG_GUILD_WAR_ERROR_JOIN_ITEM,				// ������ ��ǥ ����
	MSG_GUILD_WAR_ERROR_JOIN_MONEY,				// �� ���� ���� ��û
	MSG_GUILD_WAR_ERROR_JOIN_NO_OWNER,			// ���� ���� ������ �����뺴 �Ұ�
	MSG_GUILD_WAR_ERROR_JOIN_ALREADY_GUILD,		// ����� ��ħ�� ���� ���� �뺴 ��û �Ұ�
	MSG_GUILD_WAR_ERROR_JOIN_CHARLEVEL,			// ĳ������ ����
	MSG_GUILD_WAR_ERROR_NOT_OWNER,				// ���ֵ� �ƴϸ鼭 ������ �ٲٷ� �Ҷ�
	MSG_GUILD_WAR_ERROR_NOT_SETTIME,			// ���� ���� �ð��� �ƴ�
	MSG_GUILD_WAR_ERROR_INVALID_TIME,			// ���� �Ұ��� �ð���
	MSG_GUILD_WAR_ERROR_JOIN_NOT_GUILD_BOSS,	// �Ϲ� ������ ���� ��û �Ұ�
	MSG_GUILD_WAR_ERROR_TOTAL,
} MSG_GUILD_WAR_ERROR_TYPE;

typedef enum _tagMsgHelperType
{
	MSG_HELPER_WHISPER_REQ,				// �Ӹ� ��û		: sender_index(n) sender_name(str) receiver_index(n) receiver_name(str) chat(str)
	MSG_HELPER_WHISPER_REP,				// �Ӹ� ����		: sender_index(n) sender_name(str) receiver_index(n) receiver_name(str) chat(str)
	MSG_HELPER_WHISPER_TIMEOUT,			// �Ӹ� Ÿ�Ӿƿ�	: sender_index(n) sender_name(str)
	MSG_HELPER_WHISPER_NOTFOUND,		// ��� ����		: sender_index(n) sender_name(str)
	MSG_HELPER_WAR_NOTICE_TIME,			// ������ �ð� �˸�	: zoneindex(n) month(c) day(c) hour(c) min(c)
	MSG_HELPER_WAR_NOTICE_TIME_REMAIN,	// ���� ���� �ð� �˸�	: zoneindex(n) min(c)
	MSG_HELPER_WAR_NOTICE_START,		// ������ ���� �˸�	: zoneindex(n) remainSec(n)
	MSG_HELPER_WAR_JOIN_ATTACK_GUILD,	// ���� ��� �߰�	: zoneindex(n) guildindex(n)
	MSG_HELPER_WAR_JOIN_DEFENSE_GUILD,	// ���� ��� �߰�	: zoneindex(n) guildindex(n)
	MSG_HELPER_WAR_NOTICE_START_ATTACK_CASTLE,	// ���� ���� : zoneindex(n) remainSec(n) guildindex1(n) guildname1(str) guildindex2(n) guildname2(str) guildindex3(n) guildname3(str)
	MSG_HELPER_WAR_NOTICE_REMAIN_FIELD_TIME,	// ���� ���� �ð� �˸�	: zoneindex(n) remainSec(n)
	MSG_HELPER_WAR_NOTICE_END,			// ���� ����		: zoneindex(n) bWinDefense(c) owner_index(n) owner_name(str) char_index(n) char_name(str) nextMonth(n) nextDay(n) nextHour(n) wDay(n)

	MSG_HELPER_PARTY_MEMBER_CHANGE_JOB,	// ��Ƽ�� ���� ���� �˸� : bossindex(n) charindex(n) job1(c) job2(c)
	MSG_HELPER_PARTY_CHAT,				// ��Ƽ ä��		: bossindex(n) charindex(n) charname(str) chat(str)
	MSG_HELPER_PARTY_RECALL_PROMPT,		// ��Ƽ ���� ��û	: bossindex(n) charindex(n) charname(str) isincastle(c) guildindex(n)
	MSG_HELPER_PARTY_RECALL_CONFIRM,	// ��Ƽ���� Ȯ��	: bossindex(n) reqcharindex(n) reqcharname(str) repcharindex(n) repcharname(str) yesno(c)
	MSG_HELPER_PARTY_RECALL_PROC,		// ��Ƽ���� ����	: bossindex(n) repcharindex(n) zone(n) x(f) z(f) y(c) isincastle(c) guildindex(n)

	MSG_HELPER_END_MSG,					// ���� REQ, REP �޽����� �� �޽������� �ڿ� ���� �ȵ�
} MSG_HELPER_TYPE;

typedef enum _tagMsgHelperCommandType
{
	MSG_HELPER_SHUTDOWN,				// 0 ���۸� �ٿ�

	MSG_HELPER_GUILD_CREATE_REQ,		// ��� ���� ��û	: charindex(n) charname(str) guildname(str)
	MSG_HELPER_GUILD_CREATE_REP,		// ��� ���� ����	: charindex(n) errorcode(uc)
	MSG_HELPER_GUILD_CREATE_NTF,		// ��� �߰� �˸�	: guildindex(n) guildlevel(n) guildname(str) bossindex(n) bossname(str)
	MSG_HELPER_GUILD_ONLINE_NTF,		// ���� �¶���	: guildindex(n) charindex(n) online(c)
	MSG_HELPER_GUILD_MEMBER_LIST,		// ���� ����Ʈ	: guildindex(n) count(n) [charindex(n) charname(str) pos(n) online(c)]
	MSG_HELPER_GUILD_ONLINE,			// �¶��� ����		: guildindex(n) charindex(n) online(c)
	MSG_HELPER_GUILD_LOAD_REQ,			// ������� ��û	: idname(str) charindex(n)
	MSG_HELPER_GUILD_LOAD_REP,			// ������� ����	: idname(str) charindex(n) errorcode(uc)
	MSG_HELPER_GUILD_LEVELUP_REQ,		// ��� ��� ��û	: guildindex(n) charindex(n)
	MSG_HELPER_GUILD_LEVELUP_REP,		// 10 ��� ��� ����	: guildindex(n) charindex(n) errorcode(uc)
	MSG_HELPER_GUILD_LEVELUP_NTF,		// ��� ��� �˸�	: guildindex(n) guildlevel(n)
	MSG_HELPER_GUILD_BREAKUP_REQ,		// ��� �ػ� ��û	: bossindex(n) guildindex(n)
	MSG_HELPER_GUILD_BREAKUP_REP,		// ��� �ػ� ����	: charindex(n) errcode(uc)
	MSG_HELPER_GUILD_BREAKUP_NTF,		// ��� �ػ� �˸�	: guildindex(n)
	MSG_HELPER_GUILD_MEMBER_ADD_REQ,	// ��� �߰� ��û	: guildindex(n) boss(n) requester(n)
	MSG_HELPER_GUILD_MEMBER_ADD_NTF,	// �߰� �˸�		: guildindex(n) index(n) name(str) position(n)
	MSG_HELPER_GUILD_MEMBER_ADD_REP,	// �߰� ����		: guildindex(n) boss(n) requester(n) errcode(n)
	MSG_HELPER_GUILD_MEMBER_OUT_REQ,	// Ż�� ��û		: guildindex(n) charindex(n)
	MSG_HELPER_GUILD_MEMBER_OUT_NTF,	// Ż�� �˸�		: guildindex(n) charindex(n) charname(str)
	MSG_HELPER_GUILD_MEMBER_OUT_REP,	// 20 Ż�� ����		: guildindex(n) charindex(n) errcode(uc)
	MSG_HELPER_GUILD_MEMBER_KICK_REQ,	// ���� ��û		: guildindex(n) bossindex(n) charindex(n)
	MSG_HELPER_GUILD_MEMBER_KICK_REP,	// ���� ����		: guildindex(n) bossindex(n) charindex(n) errcode(uc)
	MSG_HELPER_GUILD_MEMBER_KICK_NTF,	// ���� ���� �˸�	: guildindex(n) bossindex(n) charindex(n)
	MSG_HELPER_GUILD_CHANGE_BOSS_REQ,	// ���� ���� ��û	: guildindex(n) current(n) change(n)
	MSG_HELPER_GUILD_CHANGE_BOSS_NTF,	// ���� ���� �˸�	: guildindex(n) current(n) change(n)
	MSG_HELPER_GUILD_CHANGE_BOSS_REP,	// ���� ���� ����	: guildindex(n) current(n) change(n) errcode(uc)
	MSG_HELPER_GUILD_APPOINT_OFFICER_REQ, // �ΰ� ���� ��û : guildindex(n) boss(n) officer(n)
	MSG_HELPER_GUILD_APPOINT_OFFICER_REP, // �ΰ� ���� ���� : guildindex(n) boss(n) officer(n) errcode(uc)
	MSG_HELPER_GUILD_APPOINT_OFFICER_NTF, // �ΰ� ���� �˸� : guildindex(n) boss(n) officer(n)
	MSG_HELPER_GUILD_CHAT,				// 30 ��� ä��		: guildindex(n) charindex(n) charname(str) chat(str)
	MSG_HELPER_GUILD_FIRE_OFFICER_REQ,	// �ΰ� ���� ��û	: guildindex(n) boss(n) officer(n)
	MSG_HELPER_GUILD_FIRE_OFFICER_REP,	// �ΰ� ���� ����	: guildindex(n) boss(n) officer(n) errcode(uc)
	MSG_HELPER_GUILD_FIRE_OFFICER_NTF,	// �ΰ� ���� �˸�	: guildindex(n) boss(n) officer(n)
	MSG_HELPER_GUILD_LOAD_NTF,			// ��� �б� ����	: guildindex(n) guildlevel(n) guildname(str) bossindex(n) bossname(str) battle_guildindex(n) battle_name(str) battle_prize(n) battle_time(n) battle_zone(n) battle_killcount(n) battle_state(c)

	MSG_HELPER_CHAR_DEL,				// ĳ���� ����		: charindex(n)

	MSG_HELPER_GUILD_BATTLE_REQ,		// ����� ��û		: guildindex1(n) guildindex2(n) prize(n) zone(n) time(n)
	MSG_HELPER_GUILD_BATTLE_REP,		// ����� ����		: guildindex1(n) guildname1(str) guildindex2(n) guildname2(str) prize(n) zone(n) time(n)
	MSG_HELPER_GUILD_BATTLE_START,		// ����� ����		: guildindex1(n) guildindex2(n)
	MSG_HELPER_GUILD_BATTLE_STATUS,		// ����� ��Ȳ		: guildindex1(n) guildname1(str) killcount1(n) guildindex2(n) guildname2(str) killcount2(n) battletime(n) battlezone(n)
	MSG_HELPER_GUILD_BATTLE_STOP_REQ,	// 40 ����� ���� ��û	: guildindex1(n) guildindex2(n)
	MSG_HELPER_GUILD_BATTLE_STOP_REP,	// ����� ���� ����	: winner_index(n) guildindex1(n) guildname1(str) guildindex2(n) guildname2(str) prize(n) zone(n)
	MSG_HELPER_GUILD_BATTLE_PEACE_REQ,	// ����� ��ȭ ��û	: guildindex(n)
	MSG_HELPER_GUILD_BATTLE_PEACE_REP,	// ����� ��ȭ ����	: guildindex(n)
	MSG_HELPER_GUILD_BATTLE_KILL_REQ,	// ����� ų ����	: of_guildindex(n) df_guildindex(n)

	MSG_HELPER_EVENT_MOONSTONE_LOAD,
	MSG_HELPER_EVENT_MOONSTONE_UPDATE_REQ,
	MSG_HELPER_EVENT_MOONSTONE_UPDATE_REP,
	MSG_HELPER_EVENT_MOONSTONE_JACKPOT_REQ,
	MSG_HELPER_EVENT_MOONSTONE_JACKPOT_REP,

	MSG_HELPER_FRIEND_MEMBER_ADD_REQ,		// 50 ģ�� �߰� ��û.
	MSG_HELPER_FRIEND_MEMBER_ADD_REP,		//ģ�� �߰� ����.
	MSG_HELPER_FRIEND_MEMBER_DEL_REQ,		//ģ�� ���� ��û.
	MSG_HELPER_FRIEND_MEMBER_DEL_REP,		//ģ�� ���� ��û.
	MSG_HELPER_FRIEND_SET_CONDITION_REQ,	//���º����û.
	MSG_HELPER_FRIEND_SET_CONDITION_NOTIFY, //���º�������

	MSG_HELPER_PD4_RANK_INIT,			// pd4 rank DB init 
	MSG_HELPER_PD4_RANK_ADD,			// pd4 rank ����	 : charIndex(n) 
	MSG_HELPER_PD4_RANK_END,			// pd4 ����			 : charIndex(n) deadmonNum(n) bclear(c)
	MSG_HELPER_PD4_RANK_VIEW_REQ,		// : charindex(n) charjob(c)
	MSG_HELPER_PD4_RANK_VIEW_REP,		// 60 : charindex(n) multicount(c), charname(str), bclear(c), deadmon(n), ctime(ll);
	MSG_HELPER_PD4_REWARD_VIEW_REQ,		// : charindex(n) charjob(c)
	MSG_HELPER_PD4_REWARD_VIEW_REP, 	// : charindex(n) multicount(c), charname(str) breward(c)
	MSG_HELPER_PD4_REWARD_REQ,			// : charindex(n)
	MSG_HELPER_PD4_REWARD_REP,			// : charindex(n) charrank(c) breward(c)
	MSG_HELPER_PD4_REWARD_INIT,			// pd4 reward�� 0�� ����
	MSG_HELPER_PD4_REWARD_END,			// pd4 reward�� 1�� ���� 

	MSG_HELPER_PET_CREATE_REQ,			// �� ���� ��û		: owner(n) type_grade(c)
	MSG_HELPER_PET_CREATE_REP,			// �� ���� ����		: index(n) owner(n) type_grade(c)
	MSG_HELPER_PET_DELETE_REQ_RESERVE,	// �̻�� : �� ���� ��û		: index(n) owner(n)
	MSG_HELPER_PET_DELETE_REP_RESERVE,	// 70 �̻�� : �� ���� ����	: index(n) owner(n)

	MSG_HELPER_GUILD_STASH_HISTORY_REQ,	// �Աݳ��� ��û	: guildindex(n) charindex(n)
	MSG_HELPER_GUILD_STASH_HISTORY_REP,	// �Աݳ��� ����	: charindex(n) errcode(n) [month(n) day(n) money(ll)]:7
	MSG_HELPER_GUILD_STASH_VIEW_REQ,	// �ܾ� ��û		: guildindex(n) charindex(n)
	MSG_HELPER_GUILD_STASH_VIEW_REP,	// �ܾ� ����		: charindex(n) errcode(n) money(ll)
	MSG_HELPER_GUILD_STASH_TAKE_REQ,	// ��� ��û		: guildindex(n) charindex(n) money(ll)
	MSG_HELPER_GUILD_STASH_TAKE_REP,	// ��� ����		: guildindex(n) charindex(n) errcode(n) money(ll) balance(ll)
	MSG_HELPER_GUILD_STASH_ROLLBACK,	// ��� ���		: guildindex(n) money(ll)
	MSG_HELPER_GUILD_STASH_SAVE_TAX_REQ,// ���� �Ա�		: guildindex(n) taxItem(ll) taxProduct(ll)
	MSG_HELPER_GUILD_STASH_SAVE_TAX_REP,// ���� �Ա� ����	: errcode(n) guildindex(n) taxItem(ll) taxProduct(ll)
	
	MSG_HELPER_NAME_CHANGE_REQ,			// �̸� ����ī�� ��� : gs -> hs: bguild(c) charindex(n) nickname(str) 
	MSG_HELPER_NAME_CHANGE_REP,			// bguild : 0 �ɸ��� 1 ������ hs->gs : bguild(c) charindex(n) error(c)

	MSG_HELPER_TEACHER_FAMEUP_REQ,			// ���� ����ġ ��(����, �л�): charindex(n) charindex(n) fame(n)
	MSG_HELPER_TEACHER_FAMEUP_REP,			

	MSG_HELPER_TEACHER_REGISTER_REQ,	// ���� ��� ��û	: teacheridx(n) bteacher(c) studentidx(n)
	MSG_HELPER_TEACHER_GIVEUP_REQ,		// ���� ��û		: teacheridx(n) studentidx(n)
	MSG_HELPER_TEACHER_REQ,				// ��������Ʈ		: charindex(n) bteacher(c)

	MSG_HELPER_TEACHER_TIMEOVER_REQ,	// �ð� ���� ����	: bteacher(c) teacheridx(n) studentidx(n)
	MSG_HELPER_TEACHER_SUPERSTONERECIEVE,// �ʰ��� �ޱ�		: charindex(c)

	MSG_HELPER_TEACHER_LOAD_REQ,		// ���� �ý��� �б� : idname(str) charindex(n)
	MSG_HELPER_TEACHER_LOAD_REP,		// ���� �ʿ�����

	MSG_HELPER_MARGADUM_PVP_RANK,		// �������� ��ŷ : count(n) charindex(n) damage(ll)

	MSG_HELPER_SEARCHFRIEND_ADD_REQ,	// �޸� �߰���û	: approvalindex(n) appnick(str) appjob(n) appuserindex(n) appserverold(n) reqnick(str)  			
	MSG_HELPER_SEARCHFRIEND_ADD_REP,	// �޸� �߰�����	: approvalindex(n) appnick(str) appjob(n) requestindex(n) reqnick(str) reqjob(n) errcode(uc)
	MSG_HELPER_SEARCHFRIEND_SELECT_ADD_REQ,	// �޸� ���� ��� ��û		: approvalindex(n) requestindex(n)
	MSG_HELPER_SEARCHFRIEND_SELECT_ADD_REP,	// �޸� ���� ��� ����		: approvalindex(n) requestindex(n) errcode(uc)
	MSG_HELPER_SEARCHFRIEND_ONETIME_ADD_REQ,	// �ѽð� ���������û		: timesec(n) appDormantindex(n) appDormantgood(n)
	MSG_HELPER_SEARCHFRIEND_ONETIME_ADD_REP,	// �ѽð� ������������		: timesec(n) appDormantindex(n) appDormantgood(n) errcode(uc)
	MSG_HELPER_SEARCHFRIEND_LISTGOOD_REQ,	// ���� ���󰡴ɿ��� ��û	: approvalindex(n)
	MSG_HELPER_SEARCHFRIEND_LISTGOOD_REP,	// ���� ���󰡴ɿ��� ����	: approvalindex(n) request_listmember(n) startIndex(n) nTotal(n) requestnick(char)[] requestindex(n)[] approvalgood(n)[] 
	MSG_HELPER_SEARCHFRIEND_GOOD_REQ,		// ���� ������ ��û : approvalindex(n) ndormantindex(n) itemgood(n)
	MSG_HELPER_SEARCHFRIEND_GOOD_REP,		// ���� ������ ���� : approvalindex(n) errcode(uc)

	MSG_HELPER_PARTY_INVITE_REQ,		// ��Ƽ �ʴ� ��û	: bossindex(n) bossname(str) bosslevel(n) targetindex(n) partytype(c)
	MSG_HELPER_PARTY_INVITE_REP,		// ��Ƽ �ʴ� ����	: bossindex(n) bossname(str) targetindex(n) targetname(str) partytype(c) errorcode(n)
	MSG_HELPER_PARTY_ALLOW_REQ,			// ��Ƽ ���� ��û	: bossindex(n) targetindex(n) targetname(str)
	MSG_HELPER_PARTY_ALLOW_REP,			// ��Ƽ ���� ����	: bossindex(n) targetindex(n) targetname(str) errcode(n)
	MSG_HELPER_PARTY_REJECT_REQ,		// ��Ƽ �ź� ��û	: bossindex(n) targetindex(n)
	MSG_HELPER_PARTY_REJECT_REP,		// ��Ƽ �ź� ����	: bossindex(n) targetindex(n) errcode(n)
	MSG_HELPER_PARTY_QUIT_REQ,			// ��Ƽ Ż�� ��û	: bossindex(n) targetindex(n)
	MSG_HELPER_PARTY_QUIT_REP,			// ��Ƽ Ż�� ����	: bossindex(n) targetindex(n) errcode(n) newbossindex(n) newbossname(str)
	MSG_HELPER_PARTY_KICK_REQ,			// ��Ƽ ���� ��û	: bossindex(n) targetindex(n)
	MSG_HELPER_PARTY_KICK_REP,			// ��Ƽ ���� ����	: bossindex(n) targetindex(n) errcode(n)
	MSG_HELPER_PARTY_CHANGE_BOSS_REQ,	// ��Ƽ�� ���� ��û	: bossindex(n) newbossname(str)
	MSG_HELPER_PARTY_CHANGE_BOSS_REP,	// ��Ƽ�� ���� ����	: bossindex(n) bossname(str) newbossindex(n) newbossname(str)

	MSG_HELPER_PARTY_MATCH_REG_MEMBER_REQ,		// ��Ƽ ��Ī �Ϲ� ��� ��û : charIndex(n) charName(str) level(n) zone(n) job(c) partytype(c)
	MSG_HELPER_PARTY_MATCH_REG_MEMBER_REP,		// ��Ƽ ��Ī �Ϲ� ��� ���� : errorcode(n) charIndex(n) charName(str) level(n) zone(n) job(c) partytype(c)

	MSG_HELPER_PARTY_MATCH_REG_PARTY_REQ,		// ��Ƽ ��Ī ��Ƽ ��� ��û : bossindex(n) bossname(str) bosslevel(n) zone(n) jobflag(n) limitlevel(c) comment(str)
	MSG_HELPER_PARTY_MATCH_REG_PARTY_REP,		// ��Ƽ ��Ī ��Ƽ ��� ���� : errorcode(n) bossindex(n) bossname(str) bosslevel(n) zone(n) jobflag(n) limitlevel(c) partytype(c) comment(str)

	MSG_HELPER_PARTY_MATCH_DEL_REQ,				// ��Ƽ ��Ī ��� ���� ��û : charindex(n)
	MSG_HELPER_PARTY_MATCH_DEL_REP,				// ��Ƽ ��Ī ��� ���� ��û : charindex(n) errorcode(n)

	MSG_HELPER_PARTY_MATCH_INVITE_REQ,			// ��Ƽ ��Ī �Ϲ� �ʴ� ��û : bossindex(n) bossname(str) bosslevel(n) charindex(n) partytype(c)
	MSG_HELPER_PARTY_MATCH_INVITE_REP,			// ��Ƽ ��Ī �Ϲ� �ʴ� ���� : errorcode(n) bossindex(n) bossname(str) charindex(n) charname(str) partytype(c)

	MSG_HELPER_PARTY_MATCH_JOIN_REQ,			// ��Ƽ ��Ī ��Ƽ ���� ��û : bossindex(n) charindex(n) charname(str) charlevel(n) charjob(c)
	MSG_HELPER_PARTY_MATCH_JOIN_REP,			// ��Ƽ ��Ī ��Ƽ ���� ���� : errorcode(n) partytype(c) bossindex(n) bossname(str) charindex(n) charname(str) charjob(c)
	MSG_HELPER_PARTY_MATCH_JOIN_ALLOW_REQ,		// ��Ƽ ��Ī ��Ƽ ���� ���� : bossindex(n) charindex(n)
	MSG_HELPER_PARTY_MATCH_JOIN_ALLOW_REP,		// ��Ƽ ��Ī ��Ƽ ���� ��� : errorcode(n) bossindex(n) targetindex(n) targetname(str)

	MSG_HELPER_PARTY_MATCH_JOIN_REJECT_REQ,		// ��Ƽ ��Ī ��Ƽ ���� ���� : joincharindex(n) rejectcharindex(n)
	MSG_HELPER_PARTY_MATCH_JOIN_REJECT_REP,		// ��Ƽ ��Ī ��Ƽ ���� ��� : errorcode(n) joincharindex(n) rejectcharindex(n)

	MSG_HELPER_PARTY_MATCH_MEMBER_CHANGE_INFO,	// ��Ƽ �Ϲ� ��� ���� ���� : charindex(n) type(n) ...

	MSG_HELPER_PARTY_INFO_PARTY,				// ��Ƽ ���� ����			: partytype(c) requestindex(n) requestname(str) membercount(n) [charindex(n) charname(str)] * membercount
	MSG_HELPER_PARTY_INFO_PARTY_MATCH_MEMBER,	// ��Ƽ ��Ī �Ϲ� ��� ����	: charindex(n) charname(str) level(n) zone(n) job(c) partytype(c)
	MSG_HELPER_PARTY_INFO_PARTY_MATCH_PARTY,	// ��Ƽ ��Ī ��Ƽ ��� ����	: bossindex(n) bossname(str) bosslevel(n) zone(n) jobflag(n) partytype(c) limitlevel(c) comment(str)
	MSG_HELPER_PARTY_INFO_END,					// ��Ƽ ���� ���� �Ϸ�

	MSG_HELPER_BLOCKPC_REQ,						// ������û, �ش��ɸ��͸� ã�Ƽ� ������ ������ : reqIndex(n) blockName(str)
	MSG_HELPER_BLOCKPC_REP,						//							: reqIndex(n) blockIndex(n) blockName(str)

	MSG_HELPER_GIFT_RECVCHARNAME_REQ,			// ���ۿ� �ش� �ɸ��Ͱ� �ִ� : sendCharIndex(n) recvCharName(str) msg(str) count(n) idx(n) ctid(n)
	MSG_HELPER_GIFT_RECVCHARNAME_REP,			//							: sendCharIndex(n) recvUserIdx(n) recvCharIndex(n) revCharName(str) msg(str) count(n) idx(n) ctid(n)

	MSG_HELPER_SAVE_EXP_GUILD,					// ���� ���� ����ġ ����	: guildindex(n) exp(d)

	MSG_HELPER_PARENTSDAY_2007_ACCUMULATEPOINT_RANKING_LIST,	//����̳� ���� ����Ʈ ����Ʈ ���� ��û gs->hs charindex
																// hs->gs :errorcode(n) charindex(n) count( n ) rankig( c ) savepoint( n ) gildname(str)
	MSG_HELPER_PARENTSDAY_2007_ADD_POINT,						// ����Ʈ ��� gc->hs : CharIndex(n) CarnationCount(n)
																// hs->gs : errorcode(c) CharIndex(n) Carnationcount(n) totalpoint(n)
	MSG_HELPER_PARENTSDAY_2007_EXCHANGE_TICKET,					// ���� ����Ʈ�� ���� ��ȯ�� ��û  gs->hs : GuildIndex( n ) CharIndex(n)
																// hs->gs : errorcode(c) CharIndex(n) GiftTicket(n)
	
	MSG_HELPER_CHILDRENSDAY_2007,				// subtype (uc)	
	
	MSG_HELPER_PARENTSDAY_2007_EXCHANGE_ITEM,					// ��ȯ������ ITEM ��ȯ  gs->hs : GuildIndex( n ) CharIndex(n)
																// hs->gs : errorcode(c) CharIndex(n) GiftItemIndex(n)
	MSG_HELPER_TEACH_2007,
	MSG_HELPER_TEACH_2007_ADDFLOWER,							// ��� ī���̼� �����ض� gs->hs : charindex(n)
	MSG_HELPER_PARENTSDAY_2007_EXCHANGE_ITEM_INSERT,			// Item Insert ����  gs->hs : Charindex(n) GiftItemIndex(n)
	MSG_HELPER_PARENTSDAY_2007_NOTICE,
	MSG_HELPER_TEACH_2007_RECEIVE_FLOWER,						// ��� ī���̼� �޾��� gs->hs : charindex(n)

	MSG_HELPER_FLOWERTREE_2007,					// subtype (uc) , Charindex(n)

	MSG_HELPER_PET_NAME_CHANGE,					// gs->hs : charindex(n) petindex(n) petname(str)
												// hs->gs : errorcode(c) charindex(n) petindex(n) petname(str)
	MSG_HELPER_GUILD_MARK_TABLE,				// hs->gs : index1(n), index2(n), index3(n)
	MSG_HELPER_LEVELUP_LOG,						// gs->hs : charstr(str), level(n)
	MSG_HELPER_PET_COLOR_CHANGE,				// gs->hs : charindex(n) petindex(n) petcolor(c)

	MSG_HELPER_NEW_GUILD_MARK_REGIST,       // [sora] GUILD_MARK
	MSG_HELPER_NEW_GUILD_MARK_EXPIRE,       // [sora] GUILD_MARK
												
} MSG_HELPER_COMMAND_TYPE;

typedef enum _tagHelperChildrensDay2007Type
{
	MSG_HELPER_CHILDRENSDAY_2007_CHECK,			// ������ ���� �ߺ��˻� : charindex(n), itemindex(n) ,needFlower(n) : �ʿ��� ���� ����, columnindex(c)
												//						: charindex(n), itemindex(n), needFlower(n), request(c) : 0-����, 1-���  
	MSG_HELPER_CHILDRENSDAY_2007_UPDATE,		// ������ ���� ������Ʈ : charindex(n), itemindex(n) 
} MSG_HELPER_CHILDRENSDAY_2007_TYPE;

typedef enum _tagHelperFlowerTree2007Type
{
	MSG_HELPER_FLOWERTREE_2007_MYPOINT,				// REQ : not / REP: point(un)....
	MSG_HELPER_FLOWERTREE_2007_ADDMYPOINT,			// REQ : point(un)
	MSG_HELPER_FLOWERTREE_2007_RECV_TICKET,			// REQ : not / rep : count(n)
	MSG_HELPER_FLOWERTREE_2007_TICKET_UPDATE,		// REQ : count(n) 
	MSG_HELPER_FLOWERTREE_2007_PRICEITEM,			// REQ : not / REP : itemindex(n), count(n)
	MSG_HELPER_FLOWERTREE_2007_PRICEITEM_INSERT,	// REQ : isGM(uc) itemindex(n)
	MSG_HELPER_FLOWERTREE_2007_PRICEMSG,			// REP : itemindex(n)
}MSG_HELPER_FLOWERTREE_2007_TYPE;

typedef enum _tagHelperPartyMatchMemberChangeInfoType
{
	MSG_HELPER_PARTY_MATCH_MEMBER_CHANGE_INFO_NAME,				// �̸� ����	: charname(str)
	MSG_HELPER_PARTY_MATCH_MEMBER_CHANGE_INFO_LEVEL,			// ���� ����	: level(n)
	MSG_HELPER_PARTY_MATCH_MEMBER_CHANGE_INFO_ZONE,				// ���̵�		: level(n) zone(n)
} MSG_HELPER_PARTY_MATCH_MEMBER_CHANGE_INFO_TYPE;

typedef enum _tagHelperPartyMatchErrorType
{
	MSG_HELPER_PARTY_MATCH_ERROR_REG_MEMBER_OK,					// 0 ��� ����
	MSG_HELPER_PARTY_MATCH_ERROR_REG_MEMBER_ALREADY_PARTY,		// 1 ��Ƽ ��
	MSG_HELPER_PARTY_MATCH_ERROR_REG_MEMBER_ALREADY_REG,		// 2 ���� �����

	MSG_HELPER_PARTY_MATCH_ERROR_REG_PARTY_OK,					// 3 ��Ƽ ��Ī ��Ƽ ��� ����
	MSG_HELPER_PARTY_MATCH_ERROR_REG_PARTY_NO_BOSS,				// 4 ��Ƽ���� �ƴ� ����� ��û��
	MSG_HELPER_PARTY_MATCH_ERROR_REG_PARTY_FULL,				// 5 ��Ƽ�ο� ������
	MSG_HELPER_PARTY_MATCH_ERROR_REG_PARTY_ALREADY_REG,			// 6 �̹� ��ϵ� ��Ƽ

	MSG_HELPER_PARTY_MATCH_ERROR_DEL_MEMBER,					// 7 �Ϲ� ��Ͽ��� ������
	MSG_HELPER_PARTY_MATCH_ERROR_DEL_PARTY,						// 8 ��Ƽ ��Ͽ��� ������

	MSG_HELPER_PARTY_MATCH_ERROR_INVITE_OK,						// 9 ����
	MSG_HELPER_PARTY_MATCH_ERROR_INVITE_NOT_FOUND,				// 10 ��Ƽ ��Ī�� ���� ����� �ʴ�
	MSG_HELPER_PARTY_MATCH_ERROR_INVITE_LEVEL,					// 11 ��Ƽ Ÿ���� PARTY_TYPE_BATTLE �϶� ���� �˻翡 ��������
	MSG_HELPER_PARTY_MATCH_ERROR_INVITE_NOBOSS,					// 12 ��Ƽ���� �ƴ� ����� ��û��
	MSG_HELPER_PARTY_MATCH_ERROR_INVITE_DIFF_TYPE,				// 13 ��Ƽ Ÿ���� ���� ����
	MSG_HELPER_PARTY_MATCH_ERROR_INVITE_ALREADY_TARGET,			// 14 ����� �̹� ��Ƽ ��
	MSG_HELPER_PARTY_MATCH_ERROR_INVITE_FULL,					// 15 ��Ƽ �ο��� �ʰ�
	MSG_HELPER_PARTY_MATCH_ERROR_INVITE_ALREADY_REQUEST,		// 16 �ٸ� ������� ��û ���϶�

	MSG_HELPER_PARTY_MATCH_ERROR_JOIN_OK,						// 17 ���� ����
	MSG_HELPER_PARTY_MATCH_ERROR_JOIN_ALREADY_TARGET,			// 18 ������ ��û�� ���� �̹� �ٸ� ��Ƽ�� ���� ��
	MSG_HELPER_PARTY_MATCH_ERROR_JOIN_NOT_FOUND,				// 19 ���� �Ϸ��� �ϴ� ��Ƽ�� ��Ī ���̺��� ����
	MSG_HELPER_PARTY_MATCH_ERROR_JOIN_LEVEL,					// 20 ��Ƽ Ÿ���� PARTY_TYPE_BATTLE�̰� ���� �˻翡 ������
	MSG_HELPER_PARTY_MATCH_ERROR_JOIN_LIMIT_LEVEL,				// 21 ���� ���� ���ǿ� ������
	MSG_HELPER_PARTY_MATCH_ERROR_JOIN_JOB,						// 22 ���� ������
	MSG_HELPER_PARTY_MATCH_ERROR_JOIN_FULL,						// 23 �ο� ������
	MSG_HELPER_PARTY_MATCH_ERROR_JOIN_ALREADY_REQUEST,			// 24 ���� �ʴ� ��û�ڰ� �־ �Ұ���

	MSG_HELPER_PARTY_MATCH_ERROR_JOIN_ALLOW_OK,					// 25 ��Ƽ ���� ����
	MSG_HELPER_PARTY_MATCH_ERROR_JOIN_ALLOW_NOT_PARTY,			// 26 ��Ƽ�� ����

	MSG_HELPER_PARTY_MATCH_ERROR_JOIN_REJECT_OK,				// 27 ��Ƽ ���� ���� ����
	MSG_HELPER_PARTY_MATCH_ERROR_JOIN_REJECT_FAIL,				// 28 ��Ƽ ���� ���� ����

} MSG_HELPER_PARTY_MATCH_ERROR_TYPE;

typedef enum _tagHelperPartyErrorType
{
	MSG_HELPER_PARTY_ERROR_INVITE_OK,				// 0 ����
	MSG_HELPER_PARTY_ERROR_INVITE_ALREADY_ME,		// 1 ��û�ڰ� ��Ƽ ��
	MSG_HELPER_PARTY_ERROR_INVITE_DIFF_TYPE,		// 2 ��Ƽ Ÿ���� ������ �ٸ�
	MSG_HELPER_PARTY_ERROR_INVITE_LEVEL,			// 3 ����� ���� ���� �ȵ�
	MSG_HELPER_PARTY_ERROR_INVITE_ALREADY_TARGET,	// 4 ����ڰ� ��Ƽ ��
	MSG_HELPER_PARTY_ERROR_INVITE_FULL,				// 5 ��Ƽ �ο� �ʰ�
	MSG_HELPER_PARTY_ERROR_INVITE_ALREADY_REQUEST,	// 6 �ٸ� ������� �̹� ��û ��

	MSG_HELPER_PARTY_ERROR_ALLOW_OK,				// 7 ����
	MSG_HELPER_PARTY_ERROR_ALLOW_NOT_PARTY,			// 8 ��Ƽ ���� �ƴҶ�

	MSG_HELPER_PARTY_ERROR_REJECT_OK,				// 9 ����
	MSG_HELPER_PARTY_ERROR_REJECT_FAIL,				// 10 ����

	MSG_HELPER_PARTY_ERROR_QUIT_OK,					// 11 ����
	MSG_HELPER_PARTY_ERROR_QUIT_END,				// 12 ����, ��Ƽ ��ü

	MSG_HELPER_PARTY_ERROR_KICK_OK,					// 13 ����
	MSG_HELPER_PARTY_ERROR_KICK_END,				// 14 ����, ��Ƽ ��ü

	MSG_HELPER_PARTY_ERROR_INVITE_PVP,				// 15 ��û�ڳ� ����ڰ� PVP ��

} MSG_HELPER_PARTY_ERROR_TYPE;

typedef enum _tagHelperGuildStashErrorType
{
	MSG_HELPER_GUILD_STASH_ERROR_OK,			// ����
	MSG_HELPER_GUILD_STASH_ERROR_NOHISTORY,		// �����丮 ����
	MSG_HELPER_GUILD_STASH_ERROR_NOTBOSS,		// �����/�ΰ� �ƴ�
	MSG_HELPER_GUILD_STASH_ERROR_NOTENOUGH,		// �ܾ� ����
	MSG_HELPER_GUILD_STASH_ERROR_FAIL_DB,		// �ý��� ����
} MSG_HELPER_GUILD_STASH_ERROR_TYPE;


//typedef enum _tagHelperParentsDay2007Type
//{
//	MSG_HELPER_PARENTSDAY_2007_ACCUMULATEPOINT_RANKING_LIST,	//����̳� ���� ����Ʈ ����Ʈ ���� ��û gs->hs
//																// hs->gs :count( n ) rankig( c ) savepoint( n ) gildname(str) gildmaster(str)
//	MSG_HELPER_PARENTSDAY_2007_ADD_POINT,						// ����Ʈ ��� gc->hs : CharIndex(n) echangeItemIndex(n)
//																// hs->gs : errorcode(c) point(n) totalpoint(n)
//	MSG_HELPER_PARENTSDAY_2007_EXCHANGE_TICKET,					// ���� ����Ʈ�� ���� ��ȯ�� ��û  s->c : errorcode(c) changeTicketCount(n)
//}MSG_HELPER_PARENTSDAY_2007_TYPE;




typedef enum _tagMsgChangeType
{
	MSG_CHANGE_START,					// ���ż��� ����	: charindex(n) mobindex(n)
	MSG_CHANGE_STOP,					// ���� ����		: charindex(n)
	MSG_CHANGE_CANCEL,					// ���� ��� ��û	: 
	MSG_CHANGE_ERR,						// ���� ��û�� ����	: errtype(uc)
} MSG_CHANGE_TYPE;

typedef enum _tagMsgChangeErrType
{
	MSG_CHANGE_ERR_DEAD,				// ���ſ���			: �׾����� ���� �Ұ�
	MSG_CHANGE_ERR_SITDOWN,				// ���ſ���			: �ɾ������� ���� �Ұ�
	MSG_CHANGE_ERR_WRAP,				// ���ſ���			: �̵���ġ ����� �϶� ���� �Ұ�
	MSG_CHANGE_ERR_SKILL,				// ���ſ���			: ��ų ����� �϶� ���� �Ұ�
	MSG_CHANGE_ERR_EXCHANGE,			// ���ſ���			: ��ȯ���϶� ���� �Ұ�
	MSG_CHANGE_ERR_PARTY,				// ���ſ���			: ��Ƽ ��û ���϶� ���� �Ұ�
	MSG_CHANGE_ERR_PK,					// ���ſ���			: PK ���϶� ���� �Ұ�
	MSG_CHANGE_ERR_LEVEL,				// ���ſ���			: ������ ������ ���� �Ұ�
	MSG_CHANGE_ERR_ZONE,				// ���ſ���			: ���� Ʋ�� ���� �Ұ�
	MSG_CHANGE_ERR_BATTLE,				// ���ſ���			: ������ ���� �Ұ�
	MSG_CHANGE_ERR_PERSONAL_SHOP,		// ���ſ���			: ���λ����� ���� �Ұ�
} MSG_CHANGE_ERR_TYPE;

typedef enum _tagMsgUIType
{
	MSG_UI_PLUS_EFFECT_REQ,				// �÷�������Ʈ��û	: pluseffect(c)
	MSG_UI_PLUS_EFFECT_REP,				// �÷�������Ʈ����	: pluseffect(c) charindex(n)
} MSG_UI_TYPE;

#ifdef PRESTIGE_SYSTEM
typedef enum _tagPrestigeType
{
	MSG_PRESTIGE_REQ,
	MSG_PRESTIGE_REP,
	MSG_PRESTIGE_INFO_REQ,
	MSG_PRESTIGE_INFO_REP,
	MSG_PRESTIGE_ERROR_LIMIT,
	MSG_PRESTIGE_ERROR_EXP_NEEDED,
	MSG_PRESTIGE_ERROR_NOT_EXIST_NPC,
	MSG_PRESTIGE_ERROR_NOCONDITION_LEVEL,
	MSG_PRESTIGE_ERROR_EMPTY_SLOT,
} MSG_PRESTIGE_TYPE;
#endif

typedef enum _tagMsgTeachType
{
	MSG_TEACH_TEACHER_LIST,				// ���� ����Ʈ		: subtype(uc)
	MSG_TEACH_TEACHER_REQ,				// ���� ��û ����	: subtype(uc)
	MSG_TEACH_END,						// ����				: teacher_index(n) teacher_name(str) student_index(n) student_name(str) end_type(uc)
	MSG_TEACH_INFO,						// ���� ����		: bteacher_list(c) char_type(c) teacher_index(n) teach_level(n) teacher_name(str) teacher_job(c) teacher_job2(c) or [student_index(n) student_level(n) student_name(str) student_job(c) student_job2(c)] * 8
	MSG_TEACH_STUDENT_LEVELUP,			// �л� ������		: student_index(n) student_level(n) student_name(str) student_job(c) student_job2(c)

	MSG_TEACH_ERR,						// ����				: errtype(uc)

	MSG_TEACH_RENEWER_TEACH_GIFT,		// ���� ��û		: subtype(uc)
	MSG_TEACH_LOGIN,					// �α��� �޽���	: teachType(n) charIndex(n) charName(str)

} MSG_TEACH_TYPE;

typedef enum _tagMsgTeachTeacherListType
{
	MSG_TEACH_TEACHER_LIST_UP,			// ����Ʈ ���
	MSG_TEACH_TEACHER_LIST_DN,			// ����Ʈ ��� ���
	MSG_TEACH_TEACHER_LIST_SHOW,		// ����Ʈ ���		: [char_index(n) char_name(str) char_job(c) char_job2(c)] * 20

} MSG_TEACH_TEACHER_LIST_TYPE;

typedef enum _tagMsgTeachTeacherReqType
{
	MSG_TEACH_TEACHER_REQ_REQ,			// ���� ��û		: charindex(n) char_name(str)
	MSG_TEACH_TEACHER_REQ_REJECT,		// ���� ��û ����	: reject_charindex(n) reject_charname(str)
	MSG_TEACH_TEACHER_REQ_ACCEPT,		// ���� ���		: teacher_index(n) teacher_name(str) student_index(n) student_name(str)
	MSG_TEACH_TEACHER_GIVEUP,			// �л� ���� ��û	: teacher_index(n) teacher_name(str) student_index(n) student_name(str)

} MSG_TEACH_TEACHER_REQ_TYPE;

typedef enum _tagMsgTeachCharType
{
	MSG_TEACH_NO_TYPE = -1,				// ���� ���� ����				
	MSG_TEACH_TEACHER_TYPE = 0,			// ����
	MSG_TEACH_STUDENT_TYPE,				// �л�
	MSG_TEACG_NO_STUDENT_TYPE,			// �ѹ� ���� �ߴ� �л� : ���̻� �Ұ���

} MSG_TEACH_CHAR_TYPE;

typedef enum _tagMsgTeachEndType
{
	MSG_TEACH_END_FAIL,					// ����
	MSG_TEACH_END_SUCCESS,				// ����
} MSG_TEACH_END_TYPE;

typedef enum _tagMsgTeachErrType
{
	MSG_TEACH_ERR_SYSTEM,					// ������ �ȵǴ� ����
	MSG_TEACH_ERR_TEACHER_LEVEL,			// ���� ���ɷ����� �ƴ�
	MSG_TEACH_ERR_TEACHER_LIST_ALREADY,		// �̹� ���� ����Ʈ�� ����
	MSG_TEACH_ERR_TEACHER_LIST_NOT,			// ���� ����Ʈ�� ���� ����
	MSG_TEACH_ERR_TEACHER_REQ_ALREADY,		// �̹� ��û��
	MSG_TEACH_ERR_STUDENT_LEVEL,			// �л� ���ɷ����� �ƴ�
	MSG_TEACH_ERR_HAVE_TEACHER,				// �̹� ������ ����
	MSG_TEACH_ERR_TEACHER_NOT_CONNECT,		// ������ �������� �ƴ�
	MSG_TEACH_ERR_STUDENT_NOT_CONNECT,		// �л��� �������� �ƴ�
	MSG_TEACH_ERR_TEACHER_FULL,				// ���ڰ� �� �� ����
	MSG_TEACH_ERR_NOE_REQ,					// ��û�� �� ����
	MSG_TEACH_ERR_NOMORE_STUDENT,			// ���̻� �л� �� �� ����
	MSG_TEACH_ERR_FAME,						// ����ġ �������� �İ��� ���� ����
} MSG_TEACH_ERR_TYPE;

typedef enum _tagMsgChangeJobType
{
	MSG_CHANGEJOB_ERROR,					// ����				: errcode(c)
	MSG_CHANGEJOB_REQ,						// ���� ��û		: job2(c)
	MSG_CHANGEJOB_REP,						// ���� �˸�		: charindex(n) job(c) job2(c)
	MSG_CHANGEJOB_RESET_REQ,				// ���� ���� ��û	: 
	MSG_CHANGEJOB_RESET_REP,				// ���� ���� �˸�	: charindex(n) job(c)
	MSG_CHANGECLASS_REQ,
} MSG_CHANGEJOB_TYPE;

typedef enum _tagMsgRebornType
{
	MSG_REBORN_ERROR,
	MSG_REBORN_ERROR_NOCONDITION_LEVEL,
	MSG_REBORN_ERROR_NOCONDITION_MAX_REBORN,
	MSG_REBORN_ERROR_NOCONDITION_WEARING_ITEM,
	MSG_REBORN_ERROR_NOT_EXIST_NPC,
	MSG_REBORN_REQ,
	MSG_REBORN_REP
} MSG_REBORN_TYPE;

typedef enum _tagMsgChangeJobErrorType
{
	MSG_CHANGEJOB_ERROR_OK,							// RESERVED
	MSG_CHANGEJOB_ERROR_WRONGMSG,					// Ŭ���̾�Ʈ�� �̻��ϴ�
	MSG_CHANGEJOB_ERROR_ALREADY,					// �̹� ��������
	MSG_CHANGEJOB_ERROR_NOCONDITION_LEVEL,			// ���� ���� ����� : ���� ����
	MSG_CHANGEJOB_ERROR_NOCONDITION_SKILL,			// ���� ���� ����� : ��ų ����
	MSG_CHANGEJOB_ERROR_NOCONDITION_SKILLLEVEL,		// ���� ���� ����� : ��ų ���� ����
	MSG_CHANGEJOB_ERROR_NOMONEY,					// ���� ������
	MSG_CHANGEJOB_ERROR_NOT_EXIST_NPC,				// ������ ���డ���� NPC�� ����
	MSG_CHANGEJOB_ERROR_NOITEM
} MSG_CHANGEJOB_ERROR_TYPE;

// Date : 2005-05-06(���� 9:18:18), By Lee Ki-hwan
typedef enum _tagMsgBillInfoType
{
	MSG_BILLINFO_USERINFO,					// ���� ���� ���� ����			: billguid(str) billviewname(str) billsection(n) surpluspoint(n) year(n) month(n) day(n) hour(n) min(n) remaintime(n) existreserve(n) rb_guid(str) rb_value(n) rb_name(str) iswarn(n) istimeout(n) first(n)

	MSG_BILLINFO_SECTION_LIST_REQ,			// ����� ���� ��û
	MSG_BILLINFO_SECTION_LIST_REP,			// ����� ���� ����				: flag(n), bill_guid(str), bill_section(n), bill_hour(n), bill_value(n), bill_viewname(str)
											// flag: bit0:start, bit1:end, bit2:empty
	MSG_BILLINFO_USERINFO_REQ,				// ���� ���� ���� ��û

	MSG_BILLINFO_PAY_RESERVE_REQ,			// ����(����)������� ����		:
	MSG_BILLINFO_PAY_OTHER_REQ,				// Ư�� ������� ����			: billguid(str)
	MSG_BILLINFO_PAY_REP,					// ���� ����					: errcode(n) billguid(str) billviewname(str) billsection(n) surpluspoint(n) year(n) month(n) day(n) hour(n) min(n) remaintime(n) existreserve(n) rb_guid(str) rb_value(n) rb_name(str) fromauto(n)
	// MSG_BILLINFO_PAY_REQ,
	// ����ȭ ���� ������ 
	MSG_BILLINFO_ITEM_LIST_REQ,		// ���� �������� ���� ������ ����Ʈ ��û
	MSG_BILLINFO_ITEM_LIST_REP,		// ������ ����Ʈ		: billcount(n) bill_guid(str) itemcount(n) itemindex(n) itemplus(n) itemflag(n) itemnum(n)
	MSG_BILLINFO_ITEM_REQ,			// ���������� ��û
	MSG_BILLINFO_ITEM_REP,			// ���� �亯			: error(c)			

} MSG_BILLINFO_TYPE;

typedef enum _tagMsgBillInfoItemErrorType
{
	MSG_BILLINFO_ERROR_SUCCESS,		// ���� ����
	MSG_BILLINFO_ERROR_NOTLIST,		// ����Ʈ�� ����
	MSG_BILLINFO_ERROR_CONN,		// Ŀ���� ���� ����
	MSG_BILLINFO_ERROR_BILL,		// �������� ����
	MSG_BILLINFO_ERROR_NOT_GIVE,	// �������� ���޵� �Ŀ� ���������� ó�� ���� ����.
} MSG_BILLINFO_ITEM_ERROR_TYPE;


typedef enum _tagMsgBillInfoPayErrorType
{
	MSG_BILLINFO_PAY_ERROR_UNKNOWN = -1,	// UNKNOWN
	MSG_BILLINFO_PAY_ERROR_OK = 0,			// OK
	MSG_BILLINFO_PAY_ERROR_NOTFOUND,		// NOT FOUND PREPAY INFO
	MSG_BILLINFO_PAY_ERROR_NOPOINT,			// NOT ENOUGH POINT
} MSG_BILLINFO_PAY_ERROR_TYPE;

typedef enum _tagEventMoonStoneType
{
	MSG_EVENT_MOONSTONE_START_REQ,		// ������ ���ۿ�û
	MSG_EVENT_MOONSTONE_START_REP,		// ������ ��������

	MSG_EVENT_MOONSTONE_TRY_REQ,		// ������ ���� ��û
	MSG_EVENT_MOONSTONE_TRY_REP,		// ������ ���� ����

	MSG_EVENT_MOONSTONE_RESULT_REQ,		// ������ ���� ��� ��û
	MSG_EVENT_MOONSTONE_RESULT_REP,		// ������ ���� ��� ����
	
} MSG_EVENT_MOONSTONE_TYPE;

typedef enum _tagEventMoonStoneChangeType
{
//5�� ��ġ.
	MSG_CHANGE_JACK_POT,					// ����.
	MSG_CHANGE_5PLUS_41LEVEL_WEAPON,			// 41���� +5 ����(������)	
	MSG_CHANGE_3PLUS_41LEVEL_WEAPON,			// 41���� +3 ����(������)	
	MSG_CHANGE_41LEVEL_WEAPON,				// 41���� ���� (������)
	MSG_CHANGE_3_SPECIAL_STONE,				// �������ü� 3��
	MSG_CHANGE_2_SPECIAL_STONE,				// �������ü� 2��
	MSG_CHANGE_1_SPECIAL_STONE,				// �������ü� 1��
//4����ġ
	MSG_CHANGE_CRYSTAL_OF_EFFORT,				// ����� ����.
	MSG_CHANGE_HIGH_CRYSTAL_OF_EXPERIMENCE,			// ��� ������ ����.
	MSG_CHANGE_150000_EXP,					// ����ġ 150,000
	MSG_CHANGE_MIDDLE_CRYSTAL_OF_EXPERIMENCE,		// �߱� ������ ����
	MSG_CHANGE_10_PURE_STONE,				// ��ȭ�� 10��
	MSG_CHANGE_70000_EXP,					// ����ġ 70,000
	MSG_CHANGE_3_MIDDLE_CRYSTAL_OF_EXPERIMENCE,		// �ϱ� ������ ���� 3��
//3����ġ
	MSG_CHANGE_5_12GRADE_RED_KER,				//12���� ���� �ɸ� 5��
	MSG_CHANGE_5_12GRADE_RED_NEN,				//12���� ���� �� 5��
    MSG_CHANGE_5_12GRADE_BLUE_KER,				//12���� Ǫ�� �ɸ� 5��
	MSG_CHANGE_5_BIG_MP_POTION,				//���� MP���� 5��
	MSG_CHANGE_5_12GRADE_BLUE_NEN,				//12���� Ǫ�� �� 5��
	MSG_CHANGE_5_MOONSTONE,					//������ 5��
	MSG_CHANGE_25000_EXP,					// ����ġ 25,000

//2����ġ
	MSG_CHANGE_3_6GRADE_RED_KER,				//6���� ���� �ɸ� 3�� 
	MSG_CHANGE_3_6GRADE_RED_NEN,				//6���� ���� �� 3��
	MSG_CHANGE_3_6GRADE_BLUE_KER,				//6���� Ǫ�� �ɸ� 3��
	MSG_CHANGE_3_BIG_HEAL_POTION,				//���� HP���� 3��
	MSG_CHANGE_3_6GRADE_BLUE_NEN,				//6���� Ǫ���� 3��
	MSG_CHANGE_3_MIDDLE_MP_POTION,				//���� MP���� 3��
	MSG_CHANGE_3_MEMORY_SCROLL,				//�޸� ��ũ�� 3��
//1��
	MSG_CHANGE_3_C_GRADE_ELEMENTAL,				//c��� ���� 3��
	MSG_CHANGE_3_CRAK_BLUE_LEAF,			 	//ũ�� �Ķ��� 3��
	MSG_CHANGE_3_STONE_WEAVER,				//���� ���� 3��
	MSG_CHANGE_3_D_GRADE_ELEMENTAL,				//D��� ���� 3��
	MSG_CHANGE_3_MIDIUM_HEAL_POTION,			//����ȸ������ 5��
	MSG_CHANGE_3_CRAK_BRANCH,				//ũ�� �ٱ� 3��
	MSG_CHANGE_3_STONELISE,					//���� ����

	MSG_CHANGE_NO_MOONSTONE,				// �������� ����.	
	MSG_CHANGE_MOONSTONE_RULLET,				// 5���� �귿���� ������.	
	MSG_CHANGE_MOONSTONE_ACC_NAS,   			//���� ����.

} MSG_EVENT_MOONSTONE_CHANGE_TYPE;

typedef enum _tagFriendType
{
	MSG_FRIEND_ERROR,
	MSG_FRIEND_REGIST_REQUEST,
	MSG_FRIEND_REGIST_ALLOW,
	MSG_FRIEND_SET_CONDITION, 
	MSG_FRIEND_CHATTING,
	MSG_FRIEND_REGIST_CANCEL,
	MSG_FRIEND_DELETE_MEMBER,
	MSG_FRIEND_REGIST_MEMBER_NOTIFY,
	MSG_FRIEND_DELETE_MEMBER_NOTIFY,
	MSG_FRIEND_MEMBERLIST,
	MSG_FRIEND_DELETE_BLOCK
} MSG_FRIEND_TYPE;


typedef enum _tagFriendErrorType
{
	MSG_FRIEND_ERROR_OK,		//����.(ģ�����OK, ���� OK)
	MSG_FRIEND_ERROR_PACKET,    //��Ŷ����
	MSG_FRIEND_ERROR_NOT_EXIST, //�������� �ʴ´�.
	MSG_FRIEND_ERROR_FULLMEMBER, //ģ�� ���� �ʰ�.
	MSG_FRIEND_ERROR_ALREADY_EXIST, //�̹� ģ������Ʈ�� ����.
	MSG_FRIEND_ERROR_WAIT_OTHER, //�ٸ� ������κ��� ģ������� ��û���� ����..
	MSG_FRIEND_ERROR_NOT_MATCH_INDEX, //���ΰ� ģ�� ��û,���� ���̵� ��ġ���� �ʴ´�.
	MSG_FRIEND_ERROR_HELPER_SERVER, //���ۼ������� ���ӿ���.
	MSG_FRIEND_ERROR_GAMESERVER,
	MSG_FRIEND_ERROR_FRIENDNAME, //�̸��� �߸��Ǿ���..
	MSG_FRIEND_ERROR_ALREADY_BLOCK, //�̹� ���� �Ǿ���.
	MSG_FRIEND_ERROR_NOT_BLOCK, //�̹� ���� ���� ���� �ɸ��� 
	MSG_FRIEND_ERROR_REGIST_REFUSE_PVP		// pvp ������ ģ����� �ź�
} MSG_FRIEND_ERROR_TYPE;

typedef enum _tagTreasureBoxType
{
	MSG_EVENT_TREASUREBOX_TRY_REQ,		
	MSG_EVENT_TREASUREBOX_TRY_REP,		

	MSG_EVENT_TREASUREBOX_OPEN_REQ,
	MSG_EVENT_TREASUREBOX_OPEN_REP,

	MSG_EVENT_TREASUREBOX_RED_TRY_REQ,		
	MSG_EVENT_TREASUREBOX_RED_TRY_REP,		

	MSG_EVENT_TREASUREBOX_RED_OPEN_REQ,
	MSG_EVENT_TREASUREBOX_RED_OPEN_REP,
} MSG_EVENT_TREASUREBOX_TYPE;

typedef enum _tagEventTreasureBoxLevelType
{
	MSG_EVENT_TREASUREBOX_10LEVEL,
	MSG_EVENT_TREASUREBOX_14LEVEL,
	MSG_EVENT_TREASUREBOX_18LEVEL,
	MSG_EVENT_TREASUREBOX_22LEVEL,
	MSG_EVENT_TREASUREBOX_26LEVEL,
	MSG_EVENT_TREASUREBOX_30LEVEL,

	MSG_EVENT_TREASUREBOX_ERROR_NOT_LEVEL,  
	MSG_EVENT_TREASUREBOX_ERROR_NO_BOX, 
	
	MSG_EVENT_TREASUREBOX_RED_5LEVEL,
	MSG_EVENT_TREASUREBOX_RED_12LEVEL,
	MSG_EVENT_TREASUREBOX_RED_16LEVEL,

	MSG_EVENT_TREASUREBOX_RED_ERROR_NOT_LEVEL,  
	MSG_EVENT_TREASUREBOX_RED_ERROR_NO_BOX,
} MSG_EVENT_TREASUREBOX_LEVEL_TYPE;

typedef enum _tagEventTreasureBoxChangeType
{
	MSG_EVENT_CHANGE_13LEVEL_WEAPON,
	MSG_EVENT_CHANGE_21LEVEL_WEAPON,
	MSG_EVENT_CHANGE_29LEVEL_WEAPON,
	MSG_EVENT_CHANGE_NAS,
	MSG_EVENT_CHANGE_CANDY,
	MSG_EVENT_CHANGE_ATTACK_POTION,
	MSG_EVENT_CHANGE_DEFENSE_POTION,

	MSG_EVENT_CHANGE_NO_TREASUREBOX,


	MSG_EVENT_CHANGE_HP_POTION,			// ����  HP Ȯ�� ����
	MSG_EVENT_CHANGE_MP_POTION,			// ����  MP Ȯ�� ����
	MSG_EVENT_CHANGE_EX_MEMORY,			// �޸� ��ũ�� Ȯ�� ī��
	MSG_EVENT_CHANGE_HPMP_POTION,		// ����  HP/MP Ȯ�� ����
	MSG_EVEVNT_CHAGE_EX_STAT,			// ���� â�� Ȯ�� ī��

	MSG_EVENT_CHANGE_PINK_DRAGON,		// ��ũ �巹��ũ �� ��ȯ - �±� 30���� ���� ����
	MSG_EVENT_CHANGE_BLUE_HORSE,		// �Ķ� ���� �Ǹ� ��ȯ - �±� 30���� ���� ����
} MSG_EVENT_TREASUREBOX_CHANGE_TYPE;

//0627
typedef enum _tagEventSuperStoneType
{
	MSG_EVENT_SUPERSTONE_REQ,		
	MSG_EVENT_SUPERSTONE_REP,		
			
} MSG_EVENT_SUPERSTONE_TYPE;

typedef enum __tagMsgExGoZoneType
{
	MSG_EX_GO_ZONE_FIND_REQ,		// �����̵���� �߰� ��û	: npcIdx(n)
	MSG_EX_GO_ZONE_SAVE_REQ,		// ������ ��ġ ����			: npcIdx(n)
	MSG_EX_GO_ZONE_MAP_REQ,			// ����� ��� ��û			: npcIdx(n)
	MSG_EX_GO_ZONE_MAP_REP,			// ����� ��� ���� 		: count(n) npcidx(n) tax(n)
	MSG_EX_GO_ZONE_MOVE_REQ,		// ���̵���û				: zone(n) extra(n) npcIdx(n)
	MSG_EX_GO_ZONE_FIELD_DOUNGEON_TAX_REQ,	// �ʵ���� �̵��� ��ݿ�û	: zone(n) extra(n) npcIdx(n)
	MSG_EX_GO_ZONE_FIELD_DOUNGEON_TAX_REP,	// �ʵ���� �̵��� �������	: zone(n) extra(n) tax(n)
	MSG_EX_GO_ZONE_FIELD_DOUNGEON_MOVE_REQ, // �ʵ���� �̵� ��û		: npcIdx(n)
	MSG_EX_GO_ZONE_ERROR,			// �����޽���				: error(n)
}MSG_EX_GO_ZONE_TYPE;

typedef enum __tagMsgExGoZoneErrorType
{
	MSG_EX_GO_ZONE_FIND_ERROR_OK,				// ���ο� ��� �߰� ����	npcidx(n)
	MSG_EX_GO_ZONE_FIND_ERROR_ALREADY_EXIST,	// �̹� �߰ߵ� ���			npcidx(n)
	MSG_EX_GO_ZONE_SAVE_ERROR_OK,				// ��ġ���� ����			npcidx(n)
	MSG_EX_GO_ZONE_SAVE_ERROR_FAILED,			// ��ġ���� ����			npcidx(n)
	MSG_EX_GO_ZONE_MOVE_ERROR_NOMONEY,			// ������					npcidx(n)
	MSG_EX_GO_ZONE_MOVE_ERROR_CANNOT_MOVE,		// �̵��Ұ��� ����			npcidx(n)
	MSG_EX_GO_ZONE_MOVE_ERROR_OK,				// �̵�����					zone(n)	extra(n)
}MSG_EX_GO_ZONE_ERROR_TYPE;

// ���� �޺� 
typedef enum __tagMsgExMonsterComboType
{
 MSG_EX_MONSTERCOMBO_EDIT_COMPLETE,   // �̼����̽� �����Ϸ�� count(c), index(n)
 MSG_EX_MONSTERCOMBO_EDIT_CANCEL,   // ��ҽ�
 MSG_EX_MONSTERCOMBO_EDIT_CONTEXT_REQ,  // ������ ���뺸���û
 MSG_EX_MONSTERCOMBO_EDIT_CONTEXT_REP,  // ������ ���뺸������ count(c), index(n)
 MSG_EX_MONSTERCOMBO_GOTO_COMBO,   // �����Ϸ��� �������� �� ��
 MSG_EX_MONSTERCOMBO_GOTO_COMBO_PROMPT,  // Ȯ�θ޽���
 MSG_EX_MONSTERCOMBO_GOTO_COMBO_CONFIRM,  // ��Ƽ���� Ȯ��, ��ҹ�ư ������ �� yesno(c): (yes 1 no 0),  bossindex(n)
 MSG_EX_MONSTERCOMBO_RECALL_TO_COMBO,  // ���濡�� ��Ƽ������ ��
 MSG_EX_MONSTERCOMBO_RECALL_TO_STAGE,  // ���������� ��������
 MSG_EX_MONSTERCOMBO_GIVEUP,   // ���� �޺� ����   zone(n), extra(n), npcidx(n)
 MSG_EX_MONSTERCOMBO_START,    // ���� �޺� ����
 MSG_EX_MONSTERCOMBO_MISSION_COMPLETE,  // 0: �̼ǽ���, 1: �̼Ǽ���
 MSG_EX_MONSTERCOMBO_GOTO_STAGE,   // ���濡�� ����������
 MSG_EX_MONSTERCOMBO_GOTO_WAITROOM,   // ������������ �������� ��
 MSG_EX_MONSTERCOMBO_NOTICE_STAGE,  // stage(n) ���۽� stage �ѹ��޽��� ����
 MSG_EX_MONSTERCOMBO_ERROR,    // ���� �޺� �������� error(c)
}MSG_EX_MONSTERCOMBO_TYPE;

 
typedef enum __tagMsgExMonserComboErrorType
{
 MSG_EX_MONSTERCOMBO_ERROR_EDIT_COMPLETE_OK, // �����Ϸ�
 MSG_EX_MONSTERCOMBO_ERROR_EDIT_COMPLETE_FAIL, // �����Ϸ� ����
 MSG_EX_MONSTERCOMBO_ERROR_MONEY,   // ��������
 MSG_EX_MONSTERCOMBO_ERROR_FULL,   // �޺��� ������ ���� ���
 MSG_EX_MONSTERCOMBO_ERROR_NOT_EDIT,  // �����Ϸᰡ �ȵ�
 MSG_EX_MONSTERCOMBO_ERROR_NOT_COMPLETE_STAGE, // �������� �Ϸ���� �ʾ���
 MSG_EX_MONSTERCOMBO_ERROR_DEAD_CHAR,	// ���� ĳ���Ͱ� �־ �������� ������ �� ����
 MSG_EX_MONSTERCOMBO_ERROR_ALREADY_START, // ���������� �̹� ���۵Ǿ� ��ȯ�� �� ����
 MSG_EX_MONSTERCOMBO_ERROR_NOT_EXIST_NPC, 
MSG_EX_MONSTERCOMBO_ERORR_NOT_HIGH_LEVEL,
}MSG_EX_MONSTERCOMBO_ERROR_TYPE;

typedef enum _tagMsgEffectFireType
{
	MSG_EFFECT_FIRE_READY,
	MSG_EFFECT_FIRE_ACT,
} MSG_EFFECT_FIRE_TYPE;

typedef enum __tagMsgFactoryType
{
	MSG_FACTORY_ERROR,
	MSG_FACTORY_LEARN,
	MSG_FACTORY_ITEM_LIST,
	MSG_FACTORY_ITEM_MAKE_REQ,
	MSG_FACTORY_ITEM_MAKE_REP,
	MSG_FACTORY_ITEM_MAKE,

}MSG_FACTORY_TYPE;
#ifdef PASSIVE_SYSTEM
typedef enum _tagPassiveSystemType
{
	MSG_PASSIVE_SYSTEM_ERROR,
	MSG_PASSIVE_SYSTEM_LIST,
	MSG_PASSIVE_SYSTEM_SLOT_LIST,
	MSG_PASSIVE_SYSTEM_LEARN,
	MSG_PASSIVE_SYSTEM_EQUIP_REQ,
	MSG_PASSIVE_SYSTEM_EQUIP_REP,
	MSG_PASSIVE_SYSTEM_UNEQUIP_REQ,
	MSG_PASSIVE_SYSTEM_UNEQUIP_REP,
} MSG_PASSIVE_SYSTEM_TYPE;
#endif
typedef enum __tagMsgFactoryErrorType
{
	MSG_FACTORY_ERROR_MAKE_OK,
	MSG_FACTORY_ERROR_SYSTEM,
	MSG_FACTORY_ERROR_ALREADY_REG,
	MSG_FACTORY_ERROR_SKILL,
	MSG_FACTORY_ERROR_NAS,
	MSG_FACTORY_ERROR_EXP,
	MSG_FACTORY_ERROR_ITEM,
	MSG_FACTORY_ERROR_INVEN,

}MSG_FACTORY_ERROR_TYPE;

typedef enum __tagMsgExAffinityType
{
	MSG_EX_AFFINITY_CONNECT_REQ,		// ���� ģ�� �α�		: npcidx(n)
	MSG_EX_AFFINITY_ITEM_CONTRIBUTE_REQ,	// ģȭ�� ������ ���	: npcidx(n) clientPoint(n) item_count(n) tab_idx(c) row_idx(c) col_idx(c) count(n) 												
	MSG_EX_AFFINITY_ITEM_CONTRIBUTE_REP,	// ģȭ�� ������ ��� ����	: affinityidx(n) point(n)	
	MSG_EX_AFFINITY_SHOPUSE_REQ,		// ���� �̿��û		: npcidx(n) 
	MSG_EX_AFFINITY_SHOPUSE_REP,		// ���� �̿�����		: npcidx(n) 
	MSG_EX_AFFINITY_GIFTINFO_REQ,		// ������������ ��û	: npcidx(n)
	MSG_EX_AFFINITY_GIFTINFO_REP,		// ������������ ����	: point(n) itemidx(n) item_count(n)
	MSG_EX_AFFINITY_GIFT_REQ,			// �����ޱ� ��û		: npcidx(n)
	MSG_EX_AFFINITY_GIFT_REP,			// �����ޱ� ����	
	MSG_EX_AFFINITY_UPDATE_POINT,		// ����Ʈ����		: affinityidx(n) poiny(n)
	MSG_EX_AFFINITY_LISTINFO,			// ģȭ�� ����Ʈ ����	: affinity_count(n) affinityidx(n) point(n)
	MSG_EX_AFFINITY_ADDINFO,			// ģȭ�� �߰� ����		: affinityidx(n)
	MSG_EX_AFFINITY_ERROR,				// ģȭ������ ERROR �޽��� : errortype(uc)
	MSG_EX_AFFINITY_REWARD_NOTICE,		// ���� �˸� : noticecount(c) npcidx(n)		[100322: selo] �߰���
	MSG_EX_AFFINITY_INFOTAB_REQ = 14,		// ģȭ�� ����2 ģȭ�� ���� ���� ��û [2/13/2013 Ranma]
	MSG_EX_AFFINITY_INFOTAB_REP = 15,		// ģȭ�� ����2 ģȭ�� ���� ���� ���� [2/13/2013 Ranma]
}MSG_EX_AFFINITY_TYPE;

typedef enum __tagMsgExAffinityErrorType
{
 MSG_EX_AFFINITY_ERROR_CONNECT_SUCCESS,   // ģȭ�� ���� ����
 MSG_EX_AFFINITY_ERROR_CONNECT_NOMONEY,   // ��������
 MSG_EX_AFFINITY_ERROR_CONNECT_ALREADY,   // �̹̼��� ģ������
 
 MSG_EX_AFFINITY_ERROR_ITEM_CONTRIBUTE_MAX,  // ģȭ�� ����Ʈ �ִ�� á��
 MSG_EX_AFFINITY_ERROR_ITEM_CONTRIBUTE_MISSMATCH, // ��� ������ ������
 
 MSG_EX_AFFINITY_ERROR_USESHOP_POINT,   // �����̿� ����Ʈ ����
 MSG_EX_AFFINITY_ERROR_GIFTINFO_NOITEM,   // ������� �������� ����
 MSG_EX_AFFINITY_ERROR_GIFTINFO_NOPOINT,   // ����Ʈ�������� ���� ������
 MSG_EX_AFFINITY_ERROR_GIFT_NOSPACE,   // �κ��� ������ ���� ������ ����.
 MSG_EX_AFFINITY_ERROR_GIFT_MAXWEIGHT,   // �κ� ���� �ʰ�

 MSG_EX_AFFINITY_ERROR_NOT_CONNECTED,   // ģȭ���� ����Ǿ����� �ʴ�.
 MSG_EX_AFFINITY_ERROR_CONNECT_PCLEVEL,			// ��������
 MSG_EX_AFFINITY_ERROR_CONNECT_NOITEM,			// �����۾���
}MSG_EX_AFFINITY_ERROR_TYPE;

// connie [2009/9/8] - NPC ã�� 

typedef enum __tagNpcPortalScroll
{
	MSG_NPC_PORTAL_LIST = 0,			// ����Ʈ�� �����ش�. 
	MSG_NPC_PORTAL_LOCATION,		// ������ NPC�� ��ġ�� �Ѱ��ش�.
	MSG_NPC_PORTAL_GO,				// �̵��� NPC m_npcIdx �� �����ش�.
	MSG_NPC_PORTAL_ERROR,
} MSG_NPC_PORTAL_SCROLL_TYPE;

typedef enum __tagNpcPortalScrollErrorType
{
	MSG_NPC_PORTAL_ERROR_SUCESS = 0,
	MSG_NPC_PORTAL_ERROR_MOB,				// ���� �ʵ忡 �ش� ���Ͱ� �������� �ʽ��ϴ�.
	MSG_NPC_PORTAL_ERROR_LIST,				// �� �������� ���� �������� ����� �� �����ϴ�.
} MSG_NPC_PORTAL_SCROLL_ERROR_TYPE;

typedef enum __tagMsgExLoadingEnd
{
	MSG_EX_LODING_END_NPC_PORTAL_USE,		// NPC ��ũ�� ���.
}MSG_EX_LOADING_END_TYPE;

// [100208: selo] ����Ʈ ������ �ٽ� �ޱ�
typedef enum __tagMsgExTakeAgainQuestItemType
{
	MSG_EX_TAKE_AGAIN_QUEST_ITEM_SUCCESS,	// ������ �ޱ� ����

	MSG_EX_TAKE_AGAIN_QUEST_ITEM_ERROR_ALREADY_EXIST,	// �������� ���� ��

	MSG_EX_TAKE_AGAIN_QUEST_ITEM_ERROR_FULL_INVENTORY,	// �κ��丮�� ���� ��
}MSG_EX_TAKE_AGAIN_QUEST_ITEM_TYPE;

// socket system message define. [4/8/2010 rumist]
typedef enum __tagMsgExSocketType
{
// ���� ����
	MSG_EX_SOCKET_MAKE_REQ,	// ���� ���� ��û row1(c) col1(c) item_idx1(n) (��������) row2(c) col2(c) item_idx2(n)(������ũ��) 
	MSG_EX_SOCKET_MAKE_REP, // ���� ���� ���� count(c)(���ϻ��� ��������)

// ���� ����
	MSG_EX_SOCKET_COMBINE_JEWEL_REQ, // ���� ���� ��û row(c) col(c) item_idx(n) (��������) count(c) pos(c) row(c) col(c) item_idx(n) (����������)
	MSG_EX_SOCKET_COMBINE_JEWEL_REP, // ���� ���� ����

// ���� ���׷��̵�
	MSG_EX_SOCKET_UPGRADE_JEWEL_REQ,	// ���� ���׷��̵� row1(c) col1(c) item_idx1(n) (����������1) row2(c) col2(c) item_idx2(n) (����������2) row3(c) col3(c) item_idx3(n) (������)
	MSG_EX_SOCKET_UPGRADE_JEWEL_REP,	// ���� ���׷��̵� ���� item_db_idx(n) (���׷��̵�� ����)

	MSG_EX_SOCKET_UPGRADE_JEWEL_CHAOS_REQ,   //(6)ī���� ���� ���׷��̵�
	MSG_EX_SOCKET_UPGRADE_JEWEL_CHAOS_REP,   //(7)ī���� ���� ���׷��̵� ����

// ���� ���� ��û
	MSG_EX_SOCKET_INFO_REQ,		// row(c) col(c) item_idx(n)
	MSG_EX_SOCKET_INFO_REP,		// count(c) pos(c) (������ġ) jeweldbidx(n) (�����ε���)

// ���� ���� ��û
	MSG_EX_SOCKET_CLEAN_JEWEL_REQ,	// row(c) col(c) item_idx(n)
	MSG_EX_SOCKET_CLEAN_JEWEL_REP,  // ���� ���� ����

// �����޽���
	MSG_EX_SOCKET_ERROR,		// �����޽��� errorcode(c)
	MSG_EX_SOCKET_CLEAN_ONE_JEWEL_REQ, // B0418 ��Ĺ �ý��� ���� ���� �ϳ� ���� [3/28/2013 Ranma]
}MSG_EX_SOCKET_TYPE;


typedef enum __tagMsgExSocketErrorType
{
	MSG_EX_SOCKET_ERROR_ITEM_MISSMATCH,	// �ùٸ� �������� �ƴմϴ�.
	MSG_EX_SOCKET_ERROR_FAILED_MAKE,	// ���� ���� ����
	MSG_EX_SOCKET_ERROR_NOMONEY,		// �� ����	
	MSG_EX_SOCKET_ERROR_MAX_SOCKET,		// ���� ���ս� ���� ���� �ʰ�
	MSG_EX_SOCKET_ERROR_INVEN_NOSPACE,	// �κ����� ����
	MSG_EX_SOCKET_ERROR_NOWEARITEM,		// ���� ������ �� �ִ� �۾��Դϴ�.
	MSG_EX_SOCKET_ERROR_NOSPACE,		// ������ ���� ���������δ� �۾��� ������ �� �����ϴ�
	MSG_EX_SOCKET_ERROR_NOJEWEL,		// ������ ����ִ� �������� �۾��� ������ �� �����ϴ�
	MSG_EX_SOCKET_ERROR_FAILED_COMBINE = 9, // ���� ���� ����
}MSG_EX_SOCKET_ERROR_TYPE;

typedef enum __tagMsgCostume2SystemType
{	
	MSG_EX_COSTUME2_SYSTEM_ERROR,	// �ڽ�Ƭ2 ���� : (uc)ErrorType
	MSG_EX_COSTUEM2_WEARING,		// �ٸ� ĳ������ �ڽ�Ƭ2 ������ �Ա�/���� : (n)cha_index, (uc)wear_pos, (n)item_index
	MSG_EX_COSTUME2_PREINVENINFO,	// �ڽ�Ƭ2 ���� ���� ��ü �ޱ�(�κ��丮 �޽��� �ޱ����� ����) : (uc)wear_pos, (n)uni_index, (n)item_index
	MSG_EX_COSTUME2_WEARING_SUIT,	// �ѹ��ǻ� �Ա� added by sam 11/02/01[SAM]
	MSG_EX_COSTUME2_PREINVENINFO_SUIT,// �ѹ��ǻ� �����κ� added by sam 11/02/01[SAM]
} MSG_EX_COSTUME2_SYSTEM_TYPE;

typedef enum _tagMsgTeachRenewerGiftErrorType
{
	MSG_TEACH_GIFT_ERROR,			// �İ��� �ý��� : ���� ����
	MSG_TEACH_GIFT_SUC,				// �İ��� �ý��� : ���� ����
	MSG_TEACH_GIFT_NOMORE,			// �İ��� �ý��� : �̹� ���� �Ϸ�
} MSG_TEACH_RENEWER_GIFT_ERROR_TYPE;

typedef enum _tagMsgEventPromotion2Type
{
	MSG_EVENT_PROMOTION2_COUPON_USE_REQ,		// ���� ��� : str(cuponKey)
	MSG_EVENT_PROMOTION2_COUPON_USE_REP,		// ���� ��� �亯: MSG_EVENT_PROMOTIN2_REP_ERROR_TYPE
}MSG_EVENT_PROMOTIN2_TYPE;

typedef enum _tagMsgEventPromotion2RepErrorType
{
	MSG_EVENT_PROMOTION2_REP_ERROR_FAIL,		// ���� ( ������ ���� �߱� �ý����� ����� �� �����ϴ�. )
	MSG_EVENT_PROMOTION2_REP_ERROR_SUC,			// ���� ��� ���� (�ٷ� ��ǰ ���� )
	MSG_EVENT_PROMOTION2_REP_ERROR_KEY,			// ��ϵ��� ���� ����
	MSG_EVENT_PROMOTION2_REP_ERROR_USED,		// �̹� ����� ����.
	MSG_EVENT_PROMOTION2_REP_ERROR_USER,		// ������ ����� �� ���� ������ ���.
	MSG_EVENT_PROMOTION2_REP_ERROR_DATE,		// ��� �Ⱓ�� ������.
}MSG_EVENT_PROMOTION2_REP_ERROR_TYPE;

typedef enum _tagMsgExCastllanType
{
	MSG_EX_CASTLLAN_GIVE_ITEM_REQ,		// ���� ������ ��û. 
	MSG_EX_CASTLLAN_GIVE_ITEM_REP,		// ���� ������ ��û �亯
	MSG_EX_CASTLLAN_ERROR,				// ���� �ڽ�Ƭ ����
	MSG_EX_CASTLLAN_GIVE_ITEM_GUILD_COSTUME_REQ,	// ���� ��� �ڽ�Ƭ ������ ��û(�߰�)
	MSG_EX_CASTLLAN_GIVE_ITEM_GUILD_TITLE_REQ,	// ���� ��� ȣĪ ������ ��û(�߰�)
	
}MSG_EX_CASTLLAN_TYPE;

typedef enum _tagMsgExCastllanErrorType
{
	MSG_EX_CASTLLAN_ERROR_GIVE_ITEM_ERROR,	// ������ �������� �����ϴ�.
	MSG_EX_CASTLLAN_ERROR_GIVE_ITEM_SUC,	// ���� ������ ���� ����.
	MSG_EX_CASTLLAN_ERROR_NOT_CASTLLAN,		// ���ְ� �ƴմϴ�.	
	MSG_EX_CASTLLAN_ERROR_NOT_CASTLLAN_GUILD, 	// ���ֱ�尡 �ƴմϴ�. (�߰�)
}MSG_EX_CASTLLAN_ERROR_TYPE;

typedef enum __tagMsgExRankingType
{
	MSG_EX_RANKING_LIST_REQ,				// ����Ʈ ��û type(n)
	MSG_EX_RANKING_ERROR_LIST_SUCCESS,		// ����Ʈ ��û ���� type(n), count(n), rank(n), name(s), job(n), job2(n), date(un), extra(n)
	MSG_EX_RANKING_ERROR_LIST_FAIL,			// ����Ʈ ��û ���� 
	MSG_EX_RANKING_ERROR_MSG_RANKED,		// ��ũ �Ǿ��� �޽��� 
}MSG_EX_RANKING_TYPE;


// ��ŷ �ý��� ���� : ��Ŷ �з�
typedef enum _tagRankingSystemEx
{
	MSG_EX_RANKING_LIST,					// (c->s) (uc)type(����������, ������Ŀ), (uc)subtype(����)
											// (s->c) (uc)type, (uc)subtype, (int)total_count, (int)list_count, (str)name, (int)ranking, (int)ranking_pre, (int)exp, (int)exp_pre, (int)level, (uc)job, (str)date.....
	MSG_EX_RANKING_SEARCH,					// (c->s) (uc)type(����������, ������Ŀ), (uc)subtype(����), (string)name(�̸�)
											// (s->c) (uc)type, (uc)subtype, (int)list_count, (str)name, (int)ranking, (int)ranking_pre, (int)exp, (int)exp_pre, (int)level, (uc)job, (str)date.....
	MSG_EX_RANKING_REFRESH,					// (s->c)
	MSG_EX_RANKING_ERROR,					// (c->s) (uc)type
}MSG_EX_RANKING_SYSTEM_EX_TYPE;

// ��ŷ �ý��� ���� : ��ŷ ����
typedef enum _tagRankingSystemExError						
{						
	MSG_EX_RANKING_SYSTEM_ERROR,				// (s->c) DB ����
	MSG_EX_RANKING_SYSTEM_ERROR_NOT_EXIST,		// (s->c) �˻��� ������ �������� ����
	MSG_EX_RANKING_SYSTEM_ERROR_REFRESH_TIME,	// (s->c) ���� ��ŷ ���� ���� ��
}MSG_EX_RANKING_SYSTEM_EX_ERROR_TYPE;

typedef enum _tagMsgExFaceOffType
{
	MSG_EX_FACEOFF_UIOPEN_REQ,
	MSG_EX_FACEOFF_REQ,		// hairStyle(u char), faceStyle(u char)
	MSG_EX_FACEOFF_REP,		// ���� (1, hairStyle(u char), faceStyle(u char)) ����(-1)
}MSG_EX_FACEOFF_TYPE;

typedef enum _tagMsgExFaceOffErrorType
{
	MSG_EX_FACEOFF_ERROR_SUC,			// hairStyle(u char), faceStyle(u char)
	MSG_EX_FACEOFF_ERROR_PLZ_CHOISE,	// ����� ������ �ܸ� ���� ��,
	MSG_EX_FACEOFF_ERROR_FAIL,			// ���� �������� ���� ��, 
}MSG_EX_FACEOFF_ERROR_TYPE;

// [selo: 110104] �޽��� �ڽ�
typedef enum __tagMsgExMsgBoxType
{
	MSG_EX_MSGBOX_INVEN_FULL,				// �κ��丮 ������
	MSG_EX_MSGBOX_INVEN_WEIGHT_100,			// �κ��丮 ���԰� 100 ���� ����
	MSG_EX_MSGBOX_CHANGE_START_POINT,	// req(c) Ȯ��(1), ���(0): �ű�ĳ���� �������� �����û
	MSG_EX_SHOW_CALENDER,
}MSG_EX_MSGBOX_TYPE;

// lacaball meesage type. [1/11/2011 rumist]
typedef enum __tagMsgExMsgLCBall
{
  MSG_EX_LCBALL_INFO,          // ���� ���¸� ��û or ����
  MSG_EX_LCBALL_USE,           // ��ī�� ����ϱ�
  MSG_EX_LCBALL_MSG,           // ��ī�� ���λ�ǰ�� ��÷�Ǿ����� �� ���� ����
}MSG_EX_LCBALL_TYPE;

// �޸� ���� ���� �̺�Ʈ
typedef enum _tagMsgEventUserComebackErrorType
{
	MSG_EVENT_USER_COMEBACK_ERROR_SUC,					// ���� 
	MSG_EVENT_USER_COMEBACK_ERROR_NO_MORE,				// ���� �޾���.
	MSG_EVENT_USER_COMEBACK_ERROR_NOT_USER,				// �ش� ������ �ƴ�.
	MSG_EVENT_USER_COMEBACK_ERROR_NOT_CHANNEL,			// ���� ���� �� �ִ� ä���� �ƴմϴ�.

}MSG_EVENT_USER_COMEBACK_ERROR_TYPE;

// ���� �̺�Ʈ
typedef enum _tagMsgEventCharBirthdayType
{
	MSG_EVENT_CHAR_BIRTHDAY_GIFT_REQ,					// ���� ��û 
	MSG_EVENT_CHAR_BIRTHDAY_GIFT_REP,					// ���� ��û �亯 MSG_EVENT_CHAR_BIRTHDAY_ERROR_TYPE(char)
	MSG_EVENT_CHAR_BIRTHDAY_BDAY_REQ,					// ���� ��û 
	MSG_EVENT_CHAR_BIRTHDAY_BDAY_REP,					// ���� ��û �亯 year(int), month(char), day(char), giftflag(char)
}MSG_EVENT_CHAR_BIRTHDAY_TYPE;

typedef enum _tagMsgEventCharBirthdayErrorType
{
	MSG_EVENT_CHAR_BIRTHDAY_ERROR_SUC,					// ����
	MSG_EVENT_CHAR_BIRTHDAY_ERROR_FAIL,					// �̹� �޾Ұų�. ���� ���� ������ ���� �� �����ϴ�.
}MSG_EVENT_CHAR_BIRTHDAY_ERROR_TYPE;

typedef enum __tagMsgExMsgRoyalRumble
{
    MSG_EX_ROYAL_RUMBLE_PLAYER_REQ,            // (0)(c->s) ������� ��û 
    MSG_EX_ROYAL_RUMBLE_PLAYER_REP,            // (1)(s->c) ������� ���� 0:����, 1:������, 2:��������� �Ұ��� �մϴ�. 
    MSG_EX_ROYAL_RUMBLE_NOTICE,                // (2)(s->c) (uc)command 0:��û�ð��Դϴ�. 1:5�г��ҽ��ϴ�. 2:����Ǿ����ϴ�.
    MSG_EX_ROYAL_RUMBLE_REG_MENU,              // (3)(s->c) ������� �ð� �˸� �޴� charpreplay���� ����
    MSG_EX_ROYAL_RUMBLE_PLAYER_UNREGIST_REQ,   // (4)(c->s) ������� ��� ��û
    MSG_EX_ROYAL_RUMBLE_PLAYER_UNREGIST_REP,   // (5)(s->c) ������� ��� ���� (uc)command 0:��Ҽ���, 1:����� �� �ִ� �ð��� �ƴմϴ�., 2:����ڸ��ܿ� �����ϴ�
    MSG_EX_ROYAL_RUMBLE_PLAYER_REG_RESULT,     // (6)(s->c) (uc)command 0:�ƹ��͵��ƴѻ���, 1:���õǾ���, 2:Ż��, 3:���DRAW
    MSG_EX_ROYAL_RUMBLE_GO_ZONE,               // (7)(s->c) ������ 1�� �� royal rumble ������ �̵��϶�� �޽��� �߼�
    MSG_EX_ROYAL_RUMBLE_ENTER_NEXT_PLAYER,     // (8)(s->c) (n)second n���� ���� ������ ���Ե˴ϴ�.
    MSG_EX_ROYAL_RUMBLE_HOLD,                  // (9)(s->c) (uc) boolean 0:not hold 1:hold
    MSG_EX_ROYAL_RUMBLE_WINNER,                // (10)(s->c) (n)leveltype 0:rookie, 1:senior, 2:master, (str)nick
    MSG_EX_ROYAL_RUMBLE_REWARD_REQ,            // (11)(c->s) �����û
    MSG_EX_ROYAL_RUMBLE_REWARD_REP,            // (12)(s->c) �������� ����� ����ڰ� �ƴմϴ�.
    MSG_EX_ROYAL_RUMBLE_POINT_REQ,             // (13)(c->s) ��������Ʈ ��ȸ ��û
    MSG_EX_ROYAL_RUMBLE_POINT_REP,             // (14)(s->c) ��������Ʈ ��ȸ ����
	MSG_EX_ROYAL_RUMBLE_TIME_REQ,              // (15)(c->s) �ξⷳ�� ���ð�Ȯ�� ��û
    MSG_EX_ROYAL_RUMBLE_TIME_REP,              // (16)(s->c) �ξⷳ�� ���ð�Ȯ�� ����
	MSG_EX_ROYAL_RUMBLE_LEFT_COUNT,            // (s->c) �ξⷳ�� ���� �ο� ī��Ʈ �޽���
    MSG_EX_ROYAL_RUMBLE_TIME_NOTICE,           // (s->c) �ξⷳ�� ���� �ð� 
	MSG_EX_ROYAL_RUMBLE_NOTFOUND_ITEM,         // (s->c) ������ ��� ���̵��� ���ؿ�~              (�ű��߰�)
    MSG_EX_ROYAL_RUMBLE_KILL_PLAYER,           // (s->c) ���� ������ �׿����� �����޽��� â�� ǥ��   (�ű��߰�)
}MSG_EX_ROYAL_RUMBLE_TYPE;

typedef enum _tagMsgGMCommandNoticeType
{
	MSG_GM_COMMAND_NOTICE_KICK,			// ű(���� ����)
	MSG_GM_COMMAND_NOTICE_SILENCE,		// ä�� ����
}MSG_GM_COMMAND_NOTICE_TYPE;

typedef enum _tagMsgExTreasureMapKeyExchangeError
{
	MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_SUC, // ��ȯ ����
	MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_FAIL,	// ������ ��ȯ�� �� �����ϴ�. (�������� ���� �� �� ������
	MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_ITEM,	// ��ȯ�� ���� �������� �����ϴ�.
	MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_COUNT,// ��ȯ�� ���� �������� ������ ������.
}MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_TYPE;
typedef enum _tagMsgPostSystemType
{
	MSG_USERSERVER_POST_SYSTEM_MAIL_LIST_REQ,	// ���� ����Ʈ ��û
	MSG_USERSERVER_POST_SYSTEM_MAIL_LIST_REP,	// ���� ����Ʈ ����
	MSG_USERSERVER_POST_SYSTEM_MAIL_SEND_REQ,	// ���� ������ ��û
	MSG_USERSERVER_POST_SYSTEM_MAIL_SEND_REP,	// ���� ������ ����
	MSG_USERSERVER_POST_SYSTEM_MAIL_READ_REQ,	// ���� �б� ��û
	MSG_USERSERVER_POST_SYSTEM_MAIL_READ_REP,	// ���� �б� ����
	MSG_USERSERVER_POST_SYSTEM_MAIL_DEL_REQ,	// ���� ���� ��û
	MSG_USERSERVER_POST_SYSTEM_MAIL_DEL_REP,	// ���� ���� ����

	MSG_USERSERVER_POST_SYSTEM_MAIL_ATTACH_ACK,	// ���� ÷������ ����
	MSG_USERSERVER_POST_SYSTEM_MAIL_ATTACH_REQ,	// ��÷ ������ �κ� �ֱ�
	MSG_USERSERVER_POST_SYSTEM_MAIL_ATTACH_REP,	// ���� ÷������ �κ� �ֱ� ����
	MSG_USERSERVER_POST_SYSTEM_MAIL_DISCONNECT, // SubHelper�� ���� ����
}MSG_POST_SYSTEM_TYPE;
typedef enum _tagMsgEXPostSystemType
{
	MSG_EX_POST_SYSTEM_SERVER_INFO,	// (str)ip, (int)port
}MSG_EX_POST_SYSTEM_TYPE;
typedef enum _tagMsgExShutdownType // SHUTDOWN
{
	MSG_EX_SHUTDOWN_REMAIN,							// Shut Down �ð����� %d�� ���ҽ��ϴ�.
	MSG_EX_SHUTDOWN_COUNTDOWN,						// Shut Down ���۱��� %d�� ���ҽ��ϴ�. �ش�ǽô� ���� �е��� ĳ���͸� ������ �������� �Ű��ֽñ� �ٶ��ϴ�.
	MSG_EX_SHUTDOWN_START,							// Shut Down�� ���� �Ǿ����ϴ�.
	MSG_EX_SHUTDOWN_END,							// Shut Down�� ���� �Ǿ����ϴ�.
	MSG_EX_SHUTDOWN_DISCONNECT,						// Shut Down�� ���۵Ǿ����ϴ�. �˴ٿ� ���� �ð� ���Ŀ� �ٽ� �������ּ���. Ȯ���� ���� Ŭ���̾�Ʈ�� �����Ͻñ� �ٶ��ϴ�.(�˴ٿ� ����ð� : 00:00 ~ 06:00)

}MSG_EX_SHUTDOWN_TYPE;

typedef enum _tagMsgExUserNoticeType
{
	MSG_EX_USER_NOTICE_REG_REQ,		// ���� ���� ��� ��û : (str) contents
	MSG_EX_USER_NOTICE_REG_REP,		// ���� ���� ��� ���� ���� (�����ÿ���)
	MSG_EX_USER_NOTICE_PRINT,		// ���� ���� ��� �˸� : (str) name, (str) contents
	MSG_EX_USER_NOTICE_ERROR,		// ���� ���� ���� : (unsigned char) error type
}MSG_EX_USER_NOTICE_TYPE;

typedef enum _tagMsgExUserNoticeErrorType
{
	MSG_EX_USER_NOTICE_ERROR_NOITEM,	// ���� ���� ��� ����(�������� ��� ��� �Ұ���)
	MSG_EX_USER_NOTICE_ERROR_LENGTH,	// ���� ���� ��� ����(���� ����)
}MSG_EX_USER_NOTICE_ERROR_TYPE;

typedef enum _tagMsgSubHelperUserNoticeType
{
	MSG_SUBHELPER_USER_NOTICE_REG_REQ,		// ���� ���� ��� ��û : (int) character index, (str) name, (str) contents
	MSG_SUBHELPER_USER_NOTICE_REG_REP,		// ���� ���� ��� ���� : (int) character index, (unsigned char) success(0 : ����, 1 : ����)
	MSG_SUBHELPER_USER_NOTICE_PRINT,		// ���� ���� ��� �˸� : (str) name, (str) contents
}MSG_SUBHELPER_USER_NOTICE_TYPE;

typedef enum _tagUserServerMsgType
{
	MSG_USERSERVER_UNKNOWN,
	MSG_USERSERVER_AUTH,				// ���� ���� ���� ��û
	MSG_USERSERVER_POST_SYSTEM,			// ���� �ý���

}MSG_USERSERVER_TYPE;
typedef enum _tagMsgExEventAutomationSystemType
{
	MSG_EX_EVENT_AUTOMATION_LIST=0,		// S �� C �������� �̺�Ʈ ����Ʈ nCount(int) { eventIndex(int) �� }
	MSG_EX_EVENT_AUTOMATION_ADD,		// S �� C �������� �̺�Ʈ �߰� eventIndex(int)
	MSG_EX_EVENT_AUTOMATION_REMOVE,		// S �� C �������� �̺�Ʈ ���� eventIndex(int)
}MSG_EX_EVENT_AUTOMATION_SYSTEM_TYPE;
typedef enum _tagMsgExPromoKeyType
{
	MSG_EX_PROMO_KEY_USE_REQ,
}MSG_EX_PROMO_KEY_TYPE;
#endif	// SE_INCL_MESSAGEDEFINE_H
