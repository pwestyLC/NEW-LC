// ----------------------------------------------------------------------------
//  File : UIManager.h
//  Desc : Created by yjpark
// ----------------------------------------------------------------------------

#ifndef	UIMANAGER_H_
#define	UIMANAGER_H_

#include <Engine/DesignClasses/Singleton/SingletonBase.h>
#include <GameMP/Game.h>
#include <Engine/Interface/UIWindowDeclare.h>
#include <Engine/Interface/UIEditBox.h>
#include <Engine/Interface/UIMultiEditBox.h>
#include <Engine/Interface/UIFocus.h>
#include <Engine/Interface/UITooltipMgr.h>
#include <Engine/Interface/UIDrawFigure.h>

#include <Engine/Base/DamageLogInfo.h>

#include <Engine/Interface/UILacarette.h>

#include <Common/CommonDef.h>

class CWorld;
class CUIListBox;
class CUIMouseCursor;
class CUIMsgBox_Info;

// Link library
#pragma comment( lib, "imm32.lib" )

// Message box command code
enum UI_MSGCMD
{
	MSGCMD_DROPITEM	= 0,					// ������ ���
	MSGCMD_EXCH_REQ_SRC,					// ��ȯ ��û
	MSGCMD_EXCH_REQ_DEST,					// ��ȯ ��û
	MSGCMD_EXCH_DEL_ITEM,					// ��ȯâ���� ������ ����
	MSGCMD_WAREHOUSE_ADD_ITEM,				// â���� �߰�
	MSGCMD_WAREHOUSE_ADD_PLUSITEM,			// â���� �߰�
	MSGCMD_WAREHOUSE_ADD_MONEY,				// â���� �� �ֱ�.
	MSGCMD_WAREHOUSE_ADD_REQ,				// ���� Ȯ��
	MSGCMD_WAREHOUSE_ERROR,					// ���� ����.
	MSGCMD_WAREHOUSE_DEL_ITEM,				// â������ �κ��� �߰�	
	MSGCMD_GUILD_JOIN,						// ��� ����
	MSGCMD_GUILD_JOIN_REQ,					// ���� ��û��
	MSGCMD_GUILD_QUIT,						// ��� Ż��
	MSGCMD_GUILD_DESTROY,					// ��� ��ü
	MSGCMD_GUILD_ERROR,						// ��忡�� ���� �߻�.
	MSGCMD_GUILD_ROOM,						// ��� ���� �������� �̵�.
	MSGCMD_GUILD_APPLICANT_JOIN,			// ��� ��û�� ��.
	MSGCMD_GUILD_KICK,						// ��� ����
	MSGCMD_GUILD_ADD_VICE_BOSS,				// �δ��� �Ӹ�
	MSGCMD_GUILD_DEL_VICE_BOSS,				// �δ��� ����
	MSGCMD_GUILD_CHANGE_BOSS,				// ���� ����
	MSGCMD_GUILD_LORD_NOTICE,				// ���� ����
	MSGCMD_GUILD_RECALL_USE_REQ,			// ��� ���� ��� ����
	MSGCMD_GUILD_RECALL,					// ��� ���� �޽��� �ڽ�
	 
	// MSGCMD_GUILD_BATTLE_ // Date : 2005-03-19,   By Lee Ki-hwan
	MSGCMD_GUILD_BATTLE_ERROR,
	MSGCMD_GUILD_BATTLE_REQ,
	MSGCMD_GUILD_BATTLE_ACCEPT,
	MSGCMD_GUILD_BATTLE_STOP_REQ,
	MSGCMD_GUILD_BATTLE_STOP_ACCEPT,
	MSGCMD_GUILD_BATTLE_STOP_REQ_REP,
	MSGCMD_GUILD_BATTLE_MESSAGE,

	//	MSGCMD_BILLING // Date : 2005-05-06(���� 1:53:01), By Lee Ki-hwan
	MSGCMD_BILLING_NOT_ALLOW,				// ������ ����(ȭ��7)
	MSGCMD_BILLING_CONFIRM,
	MSGCMD_BILLING_CHARGE_CONFIRM,
	MSGCMD_BILLING_ERROR,
	MSGCMD_BILL_ITEM_REP,

	MSGCMD_SHOP_ADD_PLUSITEM,				// ����â���� ���׷��̵� ������ �߰�
	MSGCMD_SHOP_PRICE,						// ����â�� ���� �Է�.
	MSGCMD_SHOP_FAIL_ITEM,					// ����â���� �Ǹ��� �� ���� �������� ���
	MSGCMD_SHOP_START,						// ���� ����.	
	MSGCMD_PERSONALSHOP_ERROR,				// ���� ���� �̸��� ����.
	MSGCMD_SYSMENU_EXIT,					// ���� ����
	MSGCMD_SYSMENU_RESTART,					// ���� �����
	MSGCMD_PARTY_INVITE,					// ��Ƽ �ʴ�
	MSGCMD_PARTY_ALLOW,						// ��Ƽ ����
	MSGCMD_PARTY_MANDATE_REQ,				// ��Ƽ ���� ��û 
	MSGCMD_PARTY_MANDATE,					// ��Ƽ ����
	MSGCMD_INVEN_UPGRADE_REQ,				// ������ ���׷��̵� ��û
	MSGCMD_INVEN_UPGRADE_REP,				// ������ ���׷��̵� ���
	MSGCMD_ITEM_LEVELDOWN_REQ,				// ������ ���� �ٿ� ��û
	MSGCMD_ITEM_LEVELDOWN_REP,				// ������ ���� �ٿ� ���
	MSGCMD_INVEN_OPTION_ADD_REQ,			// ������ �ɼ� �߰� ��û
	MSGCMD_INVEN_OPTION_ADD_REP,			// ������ �ɼ� �߰� ���
	MSGCMD_INVEN_OPTION_DEL_REQ,			// ������ �ɼ� ���� ��û
	MSGCMD_INVEN_OPTION_DEL_REP,			// ������ �ɼ� ���� ���
	MSGCMD_INVEN_DIVIDE,					// ������ ������
	MSGCMD_REFINE_REP,						// ���� ���
	MSGCMD_TRANSMOGRIFY_REP,
	MSGCMD_EXTEND_MENU_REP,
	MSGCMD_QUEST_GIVEUP,					// ����Ʈ ����
//	MSGCMD_QUEST_PRIZE,						// ����Ʈ ����
	MSGCMD_QUEST_NOTIFY,					// ����Ʈ ����, Ȯ��
	MSGCMD_QUEST_NEWQUEST,					// ���ο� ����Ʈ Ȯ��.
	MSGCMD_QUEST_FAIL,						// ����Ʈ ����(���ְ� ����.)
	MSGCMD_QUEST_COMPLETE,					// ����Ʈ �Ϸ� Ȯ��.
	
	MSGCMD_SKILLLEARN_NOTIFY,				// ��ų ���� ����
	MSGCMD_REMISSION_NOTIFY,				// ���˺� ���� ����
	MSGCMD_REMISSION_BUY,					// ���˺� ����
	MSGCMD_QUEST_START,						// ����Ʈ ����
	MSGCMD_TELEPORT_MEMO,					// �޸� ��ũ�� ����
	MSGCMD_LOGIN_ERROR,						// �α��� ����
	MSGCMD_SERVER_ERROR,					// ���� ���� �κп��� ����
	MSGCMD_SELCHAR_ERROR,					// ĳ���� ���� �κп��� ����
	MSGCMD_CREATE_ERROR,					// ĳ���� ���� �κп��� ����
	MSGCMD_DELETE_CHARACTER,				// ĳ���� ����
	MSGCMD_DELETE_CHARACTER_SECURITY,				// ĳ���� ���� ���� 	
	MSGCMD_DELETE_CHARACTER_ERROR,			// ĳ���� ���� ���� 
	MSGCMD_DISCONNECT,						// ���Ӳ���
	MSGCMD_CONNECT_ERROR,					// ���� ����
	MSGCMD_WEBBOARD_ERROR,					// ������ ���� ����
	MSGCMD_PROCESS_REP,						// ���� ���
	MSGCMD_PROCESS_NOTIFY,					// ���� ����, Ȯ��
	MSGCMD_PRODUCT_REP,						// ���� ���
	MSGCMD_PRODUCT_NOTIFY,					// ���� ����, Ȯ��
	MSGCMD_EVENT_PRIZE,						// �̺�Ʈ ���� ��û.
	MSGCMD_EVENT_RESULT,					// �̺�Ʈ ���� ���.
	MSGCMD_WEAPONCHANGE_EVENT,				// ���� ��ü Ȯ��.
	MSGCMD_MIX_REP,							// ���� ���
	MSGCMD_MIX_NOTIFY,						// ���� ����, Ȯ��
	MSGCMD_COMPOUND_REP,					// �ռ� ���
	MSGCMD_CHANGEJOB,						// ���� �Ҳ���???
	MSGCMD_INITJOB_NOTIFY,					// �ӽ�
	MSGCMD_INITJOB_GIVEUP,					// ���� ����
	MSGCMD_INITJOB_STAT,					// ���� ȯ��
	MSGCMD_HELPER_NOTIFY,					//
	MSGCMD_HELPER_BEMYTEACHER,				// �� ������ �Ǿ�޶�� ��û.
	MSGCMD_HELPER_BEMYTEACHER_REQ,			// �� ������ �Ǿ�޶�� ��û ��ٸ�.
	MSGCMD_HELPER_FIRE_MYTEACHER,			// �л��� ������ ¥��.
	MSGCMD_HELPER_REGISTER,					// �������� ��Ͽ� �ø�.
	MSGCMD_HELPER_CANCEL_REGISTER,			// ���� ��Ͽ��� ����.
	MSGCMD_HELPER_STUDENT_ACCEPT,			// �İ������� ��� Ȯ��
	MSGCMD_SIEGE_WARFARE_ERROR,
	MSGCMD_SIEGE_WARFARE_INFO,				// ������- �������� Ȯ��â
	MSGCMD_CHANGEWEAPON_REP,				// ���� ��ü Ȯ��
	MSGCMD_CHANGEWEAPON_NOTIFY,				// ���� ��ü �޼���
	MSGCMD_PETTRAINING_NOTIFY,
	MSGCMD_PET_CHANGE,						// Ż ������ ��ȯ?	
	MSGCMD_PET_CHANGE_NOTIFY,				// Ż ������ ��ȯ?	
	MSGCMD_PET_DESTRUCTION,					// �� �������� ��ȯ�� �Ҹ� �޼���		eons
	MSGCMD_PARTYAUTO_REGIST,				// ��Ƽ ���� �ý��� ( ��Ƽ ��� )
	MSGCMD_PARTYAUTO_REGIST_ERROR,			// ��Ƽ ���� �ý��� ( ��Ƽ ��� ���� )
	MSGCMD_PARTYAUTO_JOIN_ALLOW,			// ��Ƽ ���� �ý����� ���� ��� �� ����
	MSGCMD_QUEST_TELEPORT,					// pwesty teleport button	
	// Date : 2005-05-23(���� 6:05:37), By Lee Ki-hwan
	MSGCMD_MESSENGER_START =  MSGCMD_CHANGEWEAPON_NOTIFY + 1, 
	MSGCMD_MESSENGER_ADD_REQ = MSGCMD_MESSENGER_START,	// ģ�� ��� ��û
	MSGCMD_MESSENGER_ADD_REP,				// ģ�� ��� ����
	MSGCMD_MESSENGER_ADD_WAIT,				// ģ�� ��� ���
	MSGCMD_MESSENGER_BLOCK_REQ,				// ģ�� ���� ��û
	MSGCMD_MESSENGER_BLOCK,					// ģ�� ����
	MSGCMD_MESSENGER_UNBLOCK,					// ģ�� ����
	MSGCMD_MESSENGER_DEL_REQ,				// ģ�� ���� ��û
	MSGCMD_MESSENGER_DEL,					// ģ�� ����
	MSGCMD_MESSENGER_BLOCK_DEL_REQ,			// ���� ��Ͽ��� ���� ��û
	MSGCMD_MESSENGER_BLOCK_DEL,

	MSGCMD_MESSENGER_GROUP_ADD,				// �׷� �߰�
	MSGCMD_MESSENGER_GROUP_DEL,				// �׷� ����
	MSGCMD_MESSENGER_GROUP_RENAME,			// �׷� �̸� ����
	MSGCMD_MESSENGER_GROUP_MOVE,			// �׷� ����

	MSGCMD_MESSENGER_ERROR,					// ���� 
	MSGCMD_MESSENGER_END = MSGCMD_MESSENGER_ERROR,  
	MSGCMD_PC_DEATH,						// ĳ���� ����� ������ �̵�	
	MSGCMD_SUPERGOJE_REQUEST,				// �ʰ��� ���ü� �ް� �;�?
	MSGCMD_SUPERGOJE_NOTIFY,				// �ʰ��� ���ü� ���� �˸�
	MSGCMD_OLD_PASSWORD,					// ���� �н�����
	MSGCMD_NEW_PASSWORD,					// ���ο� �н�����
	MSGCMD_CONFIRM_PASSWORD,				// ��ȣ Ȯ��
	MSGCMD_SECURITY_NOTIFY,
	MSGCMD_SECURITY_PASSWORD,				// ��ȣ ����

	MSGCMD_BOOSTER_UPGRADE_REQ,
	MSGCMD_BOOSTER_UPGRADE_REP,
	MSGCMD_SIEGE_WARFARE_MOVEING_CONFIRM,	// ���� ���� �̵� Ȯ�� 	
	MSGCMD_BOOST_RANDON_PRODUCT_ERROR,		// �ν��� ���� ����
	
	// Guild Nast Stash // Date : 2005-09-06(���� 10:03:33), By Lee Ki-hwan
	MSGCMD_GUILDSTASH_TAKE_VIEW,	
	MSGCMD_GUILDSTASH_TAKE_STASH,	
	MSGCMD_GUILDSTASH_INFO,	
	MSGCMD_GUILDSTASH_ERROR,
	// Date : 2005-09-06(���� 10:03:41), By Lee Ki-hwan

	MSGCND_MOON_DAY_EVENT_GIVE_ITEM,		//2006 �߼� �̺�Ʈ: ���������� ����ǰ���� ��ȯ
	MSGCMD_HARVEST_MOON_DAY_EVENT_UPGRADE1,	//2006 �߼� �̺�Ʈ: ������ ����.
	MSGCMD_HARVEST_MOON_DAY_EVENT_UPGRADE2,	//2006 �߼� �̺�Ʈ: ���������� ����.
	
	// wooss 050802 add MSGCMD 
	MSGCMD_USE_CONFIRM_HEXP,				//����� �׾��� ��� �ֹ��� ��뿩�θ� Ȯ���Ѵ� 
	MSGCMD_USE_CONFIRM_AEXP,
	MSGCMD_USE_CONFIRM_HEXP_LUCKY,
	MSGCMD_USE_CONFIRM_AEXP_LUCKY,
	MSGCMD_USE_CONFIRM_REBIRTH,
	MSGCMD_USE_RECOVER_ITEM_HEXP,			// ����ġ ���� �ֹ����� ����Ѵ�
	MSGCMD_USE_RECOVER_ITEM_AEXP,			// ����ġ ���� �ֹ���
	MSGCMD_USE_RECOVER_ITEM_HEXP_LUCKY,
	MSGCMD_USE_RECOVER_ITEM_AEXP_LUCKY,
	MSGCMD_USE_REBIRTH_ITEM,				// ��Ȱ �ֹ���
	MSGCMD_USE_REBIRTH_ITEM_SCROLL2,		// rebirth scroll item [11/10/2009 rumist]
	
	// wooss 050803 
	MSGCMD_CHECK_ITEM_HEXP,					// inventoryâ���� ���� Ŭ����  
	MSGCMD_CHECK_ITEM_AEXP,					// �ٸ� ������ ��뿩�� üũ
	MSGCMD_CHECK_ITEM_REBIRTH,				// ����ġ���� ,���õ�����, ��Ȱ �ֹ���

	// wooss 050807
	MSGCMD_USE_WARP_ITEM,					// �����̵� �������� ����Ѵ�
	MSGCMD_WARP_TO_CANCEL,					// �����̵��� ����Ѵ�
	MSGCMD_WARP_TAKE_CANCEL,				// ��ȯ�� ����Ѵ� 
	MSGCMD_WARP_TO_REQ_CALL,				// �����̵� ��û�� �޾��� ��� sessionState���� ó�� 
	MSGCMD_WARP_TAKE_REQ_CALL,				// ��ȯ ��û�� �޾��� ��� sessionState���� ó��

	// wooss 050817
	MSGCMD_USE_PC_SUMMON_ITEM,				// ��ȯ �������� ����Ѵ�
	// wooss 050818
	MSGCMD_USE_BOSS_SUMMON_ITEM,			// ���� ���� ��ȯ ������
	// wooss 050812
	MSGCMD_CONFIRM_CHANGE_MY_NAME,			// ĳ���� ����ī�� ��뿩�� Ȯ��
	MSGCMD_CONFIRM_CHANGE_MY_NAME_CUSTOM,
	MSGCMD_CONFIRM_CHANGE_GUILD_NAME,		// ��� ����ī�� ��뿩�� Ȯ��
	MSGCMD_CONFIRM_CHANGE_GUILD_NAME_CUSTOM,
	MSGCMD_USE_CHANGE_MY_NAME_ITEM,			// ĳ���� ����ī�� ���
	MSGCMD_USE_CHANGE_MY_NAME_ITEM_CUSTOM,
	MSGCMD_USE_CHANGE_GUILD_NAME_ITEM,		// ��� ����ī�� ���
	MSGCMD_USE_CHANGE_GUILD_NAME_ITEM_CUSTOM,
	MSGCMD_BAN_NAME,						// ������ �����ʴ� �̸�

	MSGCMD_CONFIRM_MEMSCROLL_EX,			// �޸� ��ũ�� Ȯ�� ���Ȯ��
	MSGCMD_CONFIRM_WAREHOUSE_EX,			// â�� Ȯ�� ���Ȯ��
	MSGCMD_PROLONG_MEMSCROLL_EX,			// �޸� ��ũ���� ���� ����
	MSGCMD_PROLONG_WAREHOUSE_EX,			// Ȯ�� â�� ���� ����
	// wooss 050821
	MSGCMD_CONFIRM_SLOT_ITEM,				// ĳ���� Ȯ�� ���� ��� Ȯ�� 
	MSGCMD_USE_SLOT_ITEM,					// ĳ���� Ȯ�� ���� ���

	MSGCMD_CONFIRM_PARTY_RECALL_ITEM,		// ��Ƽ���� ������ ��� Ȯ�� 060303 wooss
	
	MSGCMD_USE_ITEM,						// �ܼ� Ȯ��â�� ��ĥ��� UseSlotItem() �ٽ� ������	
	MSGCMD_SELECT_WORD_NOTIFY,				// �ܾ� ���� ȭ�� 

	MSGCMD_ASK_ONE_FIVE,					// 2pan4pan �̺�Ʈ �޽��� 051031
	MSGCMD_ASK_ONE_FOUR,	
	MSGCMD_ASK_TWO_OPEN,

	MSGCMD_ASK_NEWYEAR1,					// �ų� �̺�Ʈ1 ����� �̺�Ʈ 
	MSGCMD_ASK_NEWYEAR2,					// �ų� �̺�Ʈ2 �γ��� ���� �̺�Ʈ

	MSGCMD_EVENT_COUPON_SENDNUM,			// 060118 wooss japan coupon event

	MSGLCMD_EVENT_CLOTHES_EXCHANGE,			// �Ϻ� ���� �ǻ� ��ȯ �̺�Ʈ
	
	MSGCMD_INPUT_FRIEND,					// ģ�� ã�� �̺�Ʈ 
	MSGCMD_TIME_FRIEND,	
	MSGCMD_REWARD_FRIEND,	
	
	MSGCMD_EX_PARTY_RECALL_PROMPT,			// ��Ƽ ���� ( ���� ������) // wooss 060306

	MSGCMD_CONFIRM_UPGRADESTONE_ITEM,		// wooss 060516 platinum item

	MSGCMD_CONFIRM_MIXNEWREQ_ITEM,				// wooss 060523 composite item 			
	MSGCMD_CONFIRM_MIXNEW_ITEM,				// wooss 060523 composite item 			
	MSGCMD_CONFIRM_UNMIX_ITEM,
	MSGCMD_PET_MOUNT_CANCEL_CARD,			// �� ����Ʈ �Ʒ� ��� ī�� ��� Ȯ�� ( ���� ������ )
	MSGCMD_USE_PET_MOUNT_CANCEL_CARD,		// �� ����Ʈ �Ʒ� ��� ī�� ���( ���� ������ )
 	
	MSGCMD_COMFIRM_USE_ITEM,				// (By eons) ���� ��ų�� ������ ���� Ȯ�� �޼��� 
	MSGCMD_WORLDCUP_EVENT1_NUM,				// ������ �̺�Ʈ
	MSGCMD_GOLDENBALL_EVENT,				// (By eons) ��纼 �̺�Ʈ

	MSGCMD_GAMBLE_READY,					// Cash MoonStone
	MSGCMD_GAMBLE_READYSEL,

	MSGCMD_SHOP_LEASE_ITEM,					// Lease Shop CMD
	
	MSGCMD_COLLECTBOX_BUY_REQ,					// ���� ä�� ���� ����
	MSGCMD_INSECTITEM_DROP,						// ���� ������ ���

	MSGCMD_PROMO_KEY_ENTER,						//���θ� ��Ű�� ����Ű �Է�(������)

	//Su-won
	MSGCMD_GIFT_SEND,
	MSGCMD_GIFT_RECV,
	MSGCMD_GIFT_ERROR,
	MSGCMD_RARE_IDENTIFY,			// ��� ���� ������ ���
	MSGCMD_USE_RARE_IDENTIFY,		// ��� ���� ������ ��� Ȯ��

	MSGCMD_USE_PACKING_PAPER,		// ������ ������ ���
	MSGCMD_SAVE_BINGOITEM,			// ���� ������ ���� Ȯ��
	MSGCMD_OK_EXCHANGE_CHOCOBOX,	// ���ڻ��� ��ȯ Ȯ��

	MSGCMD_GOTO_EGEHA,
	MSGCMD_GOTO_FZ, //pwesty

	// wooss 070305 ----------------------------------------------------->>
	// kw : WSS_WHITEDAY_2007
	MSGCMD_WHITEDAY_BLUELETTER,			// ȭ��Ʈ���� ���� ������ ���
	MSGCMD_WHITEDAY_PINKLETTER,
	// ------------------------------------------------------------------<<

// [KH_070326] �ް� �̺�Ʈ ����
	MSGCMD_CONFIRM_EASTER_EGGS,
	
	MSGCMD_SONGKRAN_REWARD,				//�±� ��ũ�� �̺�Ʈ ��,���׸� ���
	//WSS_GUILD_MASTER 070411 ----------------------->>
	MSGCMD_GUILDMASTER_1,				// ��� ����Ʈ ������
	MSGCMD_GUILDMASTER_1_1,				// ��� ����Ʈ ���
	MSGCMD_GUILDMASTER_1_2,				// ��� ����Ʈ ����
	MSGCMD_GUILDMASTER_2_1,				// ��ȯ�� �ޱ� 
	// ----------------------------------------------<<
	MSGCMD_MINIGAME_SELECT_ITEM,		// WSS_MINIGAME 070420 ���� ���� ����

	MSGCMD_FLOWERTREE_SUPPORT,			// �ɳ��� �̺�Ʈ ��ȭ����
	MSGCMD_FLOWERTREE_TICKET,			// �ɳ��� �̺�Ʈ ��ȯ�� �ޱ�
	MSGCMD_FLOWERTREE_TICKETEX,			// �ɳ��� �̺�Ʈ ��ȯ�� �ޱ� Ȯ��

	MSGCMD_PET_NAMECARD_USE,			// ���� ����: ������ ���
	MSGCMD_PET_NAMECARD_INPUT,			// ���� ����: �̸� �Է�

	// [070702 :Su-won] SUMMER_2007
	MSGCMD_SUMMER2007_PAPERFOLDING,		//��������
	MSGCMD_SUMMER2007_PAPERBLENDING,	//������ ����

	// [070807: Su-won] EVENT_ADULT_OPEN
	MSGCMD_ADULTEVENT_ALCHEMIST,		// ���μ��� �����̺�Ʈ(������� ���ݼ� �̺�Ʈ): ��� ����
	MSGCMD_EVENT_SHOOT,  // ���μ��� �����̺�Ʈ(���ε鸸�� Ư��): ���� Ȯ��â
	
	MSGCMD_SIEGE_WARFARE_BUY_QUARTER,	// WSS_DRATAN_SEIGEWARFARE 2007/08/13
	MSGCMD_SIEGE_WARFARE_WAIT_QUARTER,	// WSS_DRATAN_SEIGEWARFARE 2007/08/13
	MSGCMD_SIEGEWARFARE_REBIRTH,		// WSS_DRATAN_SEIGEWARFARE 2007/08/22

	MSGCMD_BJMONO_2007_CHANGE_REQ,		// SK BJ MONO ����� ��ȯ ��û �޼��� �ڽ�
	MSGCMD_TG2007_1000DAYS_CAP_UPGRADE,	// ������ ���׷��̵� �޼��� �ڽ�

	// [070824: Su-won] REFINE_PROTECT
	MSGCMD_INVEN_UPGRADE_PROTECT_REQ,	// ���� ��ȣ ������ ���

	// [070824: Su-won] PET_COLOR_CHANGE
	MSGCMD_PET_COLORCHANGE_USE,			// �� ���� ���� ������ ���
	// [090713: selo] PET_TATOO_CHANGE
	MSGCMD_PET_TATOOCHANGE_USE,			// �� ���� �׹� ���� ���� ������ ���

	// [071122: Su-won] DRATAN_SIEGE_DUNGEON
	MSGCMD_SIEGE_DUNGEON_STATE,						//���� ����â
	MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL,		//���� ���� ȯ�� ����â
	MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL,			//���� ���� ���� ����â
	MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CONTROL,		//���� ����� ����â
	MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CONTROL,		//���� ���Ƽ��� ����â

	MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CHANGE,		//���� ���� ȯ�� ���� Ȯ��â
	MSGCMD_SIEGE_DUNGEON_MONSTER_CHANGE,			//���� ���� ���� ���� Ȯ��â
	MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CHANGE,		//���� ����� ���� Ȯ��â
	MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CHANGE,		//���� ���Ƽ��� ���� Ȯ��â
	MSGCMD_SIEGE_DUNGEON_ENTER,						//���� �̵� Ȯ��â

	// [071122: Su-won] NEW_MOONSTONE
	MSGCMD_MOONSTONE_MIX,
	
	MSGCMD_EVENT_XMAS_2007_DECO,					// ũ�������� Ʈ�� Ȯ��â
	MSGCMD_PETTRANSFORM_RU,							// �� �絹�� ���� �ֹ��� Ȯ��â

	MSGCMD_EVENT_NEWYEAR_2008,						// 2008 �ų��̺�Ʈ, ���� ���� Ȯ��â

	MSGCMD_USE_SMALL_CORD,							// ���ָӴ� ��� ���
	MSGCMD_OK_EXCHANGE_LUCKYBOX,					// �Ҹ����� ��ȯ Ȯ��

	MSGCMD_EVENT_SAKURA_2008,						// 2008�� ���� �̺�Ʈ: ����ȯ Ȯ��â

	MSGCMD_EVENT_CHAOSBALL,							//ī������ �̺�Ʈ: ī������ �������� â
	
	MSGCMD_PRESSCORPS,

	MSGCMD_ITEMDELETE,								// �κ��丮 ������ �޽��� ó��

	MSGCMD_PARTY_OPTION,							//��Ƽ �ɼ�(���� ����) â

	MSGCMD_EVENT_PHOENIX,							//�Ǵн� �̺�Ʈ

#ifdef DEMIGOD
		MSGCMD_EVENT_DEMIGOD,
#endif
	///////////////////////////////////////////////////////////////////////////////////	
	// Cube
	MSGCMD_CUBE_PARTY_GROUP_ENTRANCE,						//Cube: ��Ƽ ����
	MSGCMD_CUBE_PARTY_PERSON_ENTRANCE,							//Cube: ��Ƽ ���� ����
	MSGCMD_CUBE_GUILD_GROUP_ENTRANCE,						//Cube: ��� ����
	MSGCMD_CUBE_GUILD_PERSON_ENTRANCE,							//Cube: ��� ���� ����
	MSGCMD_CUBE_STATE,											//Cube: ��Ƽ �� ��� ť�� ��Ȳ
	MSGCMD_CUBE_CHANGE_RATE,											//Cube: ���� ����
	// Cube
	///////////////////////////////////////////////////////////////////////////////////	
	MSGCMD_INITJOB_SSKILL,							// ����� ��ų �ʱ�ȭ Ȯ��â
	
	MSGCMD_AUCTION_BUYITEM,
	MSGCMD_AUCTION_FAVORITE,
	MSGCMD_AUCTION_FAVORITE_CANCEL,
	MSGCMD_AUCTION_CANCELREGISTER,
	MSGCMD_AUCTION_INFO,
	
	MSGCMD_CONFIRM_OBJECTCLICK,						// ������Ʈ Ŭ�� Ȯ��

	MSGCMD_ITEM_BELONG,

	// [sora] ������
	MSGCMD_EXPEDITION_INVITE,						//������ �ʴ�
	MSGCMD_EXPEDITION_INVITE_BY_NAME,
	MSGCMD_EXPEDITION_ALLOW,						//������ ���� ����
	MSGCMD_EXPEDITION_END,
	MSGCMD_EXPEDITION_QUIT,
	MSGCMD_EXPEDITION_SET_BOSS,
	MSGCMD_EXPEDITION_SET_MBOSS,
	MSGCMD_EXPEDITION_RESET_MBOSS,
	MSGCMD_EXPEDITION_KICK,
	MSGCMD_EXPEDITION_GO_STARTPLACE,				// ��Ȱ��ġ�� �̵�
	MSGCMD_EXPEDITION_ERROR,
	MSGCMD_EXPEDITION_COLLECTITEM,
	//������ ���� �޽���
	// [6/3/2009 rumist] define NPC Affinity System Message type.
	MSGCMD_AFFINITY_CONTRACT,
	MSGCMD_AFFINITY_TAKEPRESENT,

	MSGCMD_DIVISION_INFO,							// [sora] ��Ƽ, ������ �й��� ����ǥ��

//[ttos_2009_7_17]: CHARATER_CHAT_FILTER ĳ���� ä�� ����
	MSGCMD_CHAT_BLOCK_REQ,
	MSGCMD_CHAT_BLOCK,
	MSGCMD_CHAT_ERROR,

	// [sora 090824 ���� ����]
	MSGCMD_SEAL_MEMBER,					// ���� ��ȸ ���
	MSGCMD_LEARN_SEAL,					// ���� ��ǥ ȹ��
	
	MSGCMD_PET_EVOLUTION,				// �� ��ȭ

	MSGCMD_RAID_INFO,					// �ͼӵ� ���̵� �� ����
	MSGCMD_NICKNAME_DELETE,

	MSGCMD_QUEST_RESTORE_ITEM,			// [100208: selo] ����Ʈ ������ �ٽ� �ޱ�
	MSGCMD_QUEST_RESTORE_ITEM_RESULT,	// [100208: selo] ����Ʈ ������ �ٽ� �ޱ� ���

	// [100322: selo] ģȭ�� ���� �˶�
	MSGCMD_AFFINITY_REWARD_NOTICE,

	MSGCMD_LACARETTE_GET_TOKEN,			// [100325 : sora]��ī�� ��ū �ޱ�
	MSGCMD_LACARETTE_ERROR,				// [2010/04/16 : Sora] ��ī�� �޽��� â
	MSGCMD_LACARETTE_REMIND,			// [2010/04/21 : Sora] ��ī�� ���Ȯ�� �޽���
	
	MSGCMD_EVENT_WORLDCUP_EVENT2_REREQ,	// ($E_WC2010) [100517: selo] 2010 ������ �̺�Ʈ2 ��� ���� ������
	
	MSGCMD_EVENT_WORLDCUP_EVENT2_REQ,	// ($E_WC2010) [100514: selo] 2010 ������ �̺�Ʈ2 ��� ���� ����
	MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS,// ($E_WC2010) [100514: selo] 2010 ������ �̺�Ʈ2 ���� ��Ȳ

	MSGCMD_EVENT_WORLDCUP_EVENT3,		// ($E_WC2010) [100518: selo] 2010 ������ �̺�Ʈ3 ���� �޽��� �ڽ�
	
	MSGCMD_SOCKETSYSTEM_CHANCECARD,		// socket system : one more chance card [5/18/2010 rumist]
	MSGCMD_QUEST_TUTORIAL_START,		// tutorial renewal. [8/2/2010 rumist]
	MSGCMD_QUEST_TUTORIAL_CANCEL,

	MSGCMD_HELPER_PLAYTIME,				// [8/31/2010 kiny8216] �İ��� �ý��� ���� : ���̿�ð�
	MSGCMD_HELPER_FIRE_MYSTUDENT,		// [8/31/2010 kiny8216] �İ��� �ý��� ���� : �İ��� ����

	MSGCMD_SOULOFSCALP_CONFIRM,			// ��ȥ�� ¡ǥ ��ȯ Ȯ�� â
	MSGCMD_REGISTER_MERCHANT,			// [2010/08/25 : Sora] ADD_SUBJOB
	MSGCMD_COMBO_ERROR,					// [2010/10/06 : Sora] ���� �޺� ���� �޽��� �ߺ� ǥ�� ����

	MSGCMD_PROMOTION2_REQ,				// [10/6/2010 kiny8216] ���� ���θ�� �̺�Ʈ : ���� �̺�Ʈ ��ǰ ��û
	
	MSGCMD_LOGINSERV_BLOCK_USER,		// [10/27/2010 kiny8216] ����� �н����� 3�� Ʋ���� ����
	MSGCMD_MONSTER_MERCENARY_CARD_USE,		// [2010/10/20 : Sora] ���� �뺴 ī��
	MSGCMD_MONSTER_MERCENARY_CARD_HOLDER_USE,
	MSGCMD_MONSTER_MERCENARY_CARD_ERROR,
	MSGCMD_FACECHANGE,					// ���� ���� ���
	MSGCMD_FACECHANGE_OK,				// ���� ���� ��û
	
	MSGCMD_CASH_EX_ERROR,			// �Ҹ����� �̿��� ����

	MSGCMD_PET_STAT_INIT_CARD_USE,		// pet status initialize card [1/19/2011 rumist]

	MSGCMD_ATTENDANCE,				// [2011/01/18 : Sora] �⼮ �̺�Ʈ	
	MSGCMD_LACABALL_ERROR,				// laca ball error. [1/27/2011 rumist]
	
	MSGCMD_COMEBACK_CONFIRM,		// �޸� ���� ���� �̺�Ʈ ���� �ޱ�
	MSGCMD_BIRTHDAY_CONFIRM,		// ���� ���� �ޱ�
	MSGCMD_CHANGE_START_POINT,		// ���� ��û���� �ֳ� ��ŸƮ ����Ʈ ���� [4/6/2011 ldy1978220]
	MSGCMD_ROYALRUMBLE_JOIN_REQ,		// royal rumble game ��û [4/26/2011 rumist]
	MSGCMD_ROYALRUMBLE_REJECT_REQ,		// royal rumble game ��û ��� 
	MSGCMD_ROYALRUMBLE_GO_ZONE,			// go to royal rumble zone.
	MSGCMD_ROYALRUMBLE_WINNER_OUT,		// go to start zone.

	MSGCMD_GUILD_MARK_CONFIRM,			// [sora] GUILD_MARK
	MSGCMD_GUILD_MARK_REGISTER,			// [sora] GUILD_MARK
	MSGCMD_KB_EXCHAGE_HEART,			// [2011/11/14 : Sora] �±� ���� ź���� �̺�Ʈ
	MSGCMD_KB_EXCHAGE_FLAG,				// [2011/11/14 : Sora] �±� ���� ź���� �̺�Ʈ

	MSGCMD_USERNOTICE,					// [11/17/11 trylord] ���� ���� �ý���

	MSGCMD_SHUTDOWN_TIME,				// [2011/12/07 : Sora] �˴ٿ� �޽��

	MSGCMD_GUILDMASTER_KICK_REQUEST,		// ����� ���� �ɻ� ��û Ȯ�� [trylord 111228]
	MSGCMD_GUILDMASTER_KICK_CANCEL_REQUEST,	// ����� ���� ���� ��û Ȯ�� [trylord 111228]
	MSGCMD_GUILDREMOTE_JOIN_TOMASTER,		// ������ - �渶 ��û����
	MSGCMD_GUILDREMOTE_JOIN_TOUSER,			// ������ - ������ ��û����

	MSGCMD_USE_PET_ACCUMULATE,			// ������ �޽��� �ڽ�
	MSGCMD_USE_PET_ACCUMULATE2,
	MSGCMD_USE_PET_ITEM_UPGRADE,		// �� ��� ��ȭ
	MSGCMD_USE_PET_ITEM_UPGRADE_INFO,
	MSGCMD_SENDMAIL_COUNT_INPUT,		// [2012/01/18] ���� ������ ������ ī��Ʈ ����
	MSGCMD_SENDMAIL_COUNT_ADD,			// [2012/01/18] ���� ������ ������ ī��Ʈ ���ϱ�
	MSGCMD_SENDMAIL_MONEY_INPUT,		// [2012/01/26] ���� ������ �� �Է� �޽��� �ڽ�
	MSGCMD_JUMPIMGPOTION,				// ���� ��û ���� ���� ����
	MSGCMD_DELETMAIL_CHECK,				// ���� ���� �� Ȯ��

	MSGCMD_CHAR_SLOT_EXTEND,			// [2012/07/05 : Sora]  ĳ���� ���� Ȯ�� ������
	//MSGCMD_CHAR_SERVER_MOVE,			// ĳ���� ���� ���� ������ [7/25/2012 Ranma]

	MSGCMD_NEWGUILDSTASH_ILLEGAL_USER,	// ���� �����. ��ŷ ��� ���ɼ� ����. [7/17/2012 rumist]

	MSGCMD_CHARMOVETOANOTHERSERVER_SUCCESS, // ENABLE_CHARACTER_MOVE_TO_OTHER_SERVER_ITEM // ������ messagebox �����ֱ� (Ÿ�̸� ����) [7/25/2012 Ranma]
	// wooss 050806
	MSGCMD_FORTUNE,						// [2013/02/13] sykim70 Fortune System
	MSGCMD_MYSTERIOUS_BEAD_SEND_ITEM,	// �ź��� ���� ���� ������ ����� EXPRESS�� ������ ���۽� ��� MSG
	MSGCMD_WAREHOUSE_TAKE_MONEY,			//2013/04/04 jeil ���� ������ ���� 
	MSGCMD_EXCH_ADD_NAS,				//2013/04/09 jeil ���� ������ ���� 
	MSGCMD_NULL,						// �ܼ� Ȯ�� �޽����ڽ� ó�� 
	MSGCMD_JEWEL_COMPOS_JEWEL_COMPOS_SCROLL,
	MSGCMD_EXPRESS_RECV,
	MSGCMD_EXPRESS_RECVALL,
	MSGCMD_EXPRESS_DELETE,
	MSGCMD_EXPRESS_DELETEALL,
	MSGCMD_EXPRESS_RECV_ERROR,
	MSGCMD_EXPRESS_REMOTE_ITEMUSE,
	MSGCMD_EXPRESS_REMOTE_ERROR,
	MSGCMD_PET_STASH_INSTASH,
	MSGCMD_PET_STASH_OUTSTASH,
	MSGCMD_PET_STASH_ERROR,
	MSGCMD_PET_STASH_ERROR_SEALED,
	MSGCMD_PET_STASH_USEITEM,
	MSGCMD_TEST_UIBASE,
	MSGCMD_ITEM_DUPLICATION_CHECK,
	MSGCMD_INVENTORY_ARRANGE,
	MSGCMD_USE_SEALED_SOUL,
	MSGCMD_SYNDICATE_PUTON_JEWEL_REQ,
	MSGCMD_SYNDICATE_SECESSION_REQ,
#ifdef DURABILITY
	MSGCMD_DURABILITY_MATERIAL_COUNT,
	MSGCMD_DURABILITY_REPAIR,
	MSGCMD_DURABILITY_SPECIAL_REPAIR,
	MSGCMD_DURABILITY_RECOVER,
#endif	//	DURABILITY
	MSGCMD_EXP_PET_COOLTIME_REMOVE,
	MSGCMD_ATTENDANCE_ASSURE_OK_UPD,
	MSGCMD_ATTENDANCE_ITEM_USE,
#ifdef PREMIUM_CHAR	
	MSGCMD_PREMIUM_CHAR_ITEM_USE,
#endif	//	PREMIUM_CHAR
	MSGCMD_LOGOUT_RELIC_WARRING,
	MSGCMD_GUILDBATTLE_CHALLENGE,
	

	MSGLCMD_EXCHANGE_HEALER,
	MSGLCMD_EXCHANGE_KNIGHT,
	MSGLCMD_EXCHANGE_MAGE,
	MSGLCMD_EXCHANGE_NIGHTSHADOW,
	MSGLCMD_EXCHANGE_ROGUE,
	MSGLCMD_EXCHANGE_SORCERER,
	MSGLCMD_EXCHANGE_TITAN,
	MSGLCMD_EXCHANGE_EXROGUE,
	MSGLCMD_EXCHANGE_ARCHMAGE,
    #ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
		MSGCMD_CLOUD_PARTY_DUNGEON_RECALL,//Cloud Expedition_Party_Dungeon
#endif
	MSGLCMD_REBORN_REQ,
	MSGLCMD_REBORN_CHECK_REQ,
	MSGLCMD_REBORN_RANKING_REQ,
	
	MSGLCMD_RANKING_SUMMON_REQ,
	MSGLCMD_RANKING_PVP_REQ,
	
	MSGLCMD_REMOVE_SELECTED_BUFF,

	MSGCMD_MAILBOX_ERROR,
	MSGCMD_MAILBOX_DELETE,
	MSGCMD_MAILBOX_DELETE_ALL,
	
	MSGCMD_BATTLE_WARFARE,
	MSGCMD_OPEN_BOX_REP,
	MSGCMD_SEAL_COMPOSE_REP,
	MSGCMD_QUEST_PBI_USE_REP,
	MSGCMD_TOTAL
};

enum UI_MSGLCMD
{
	MSGLCMD_REFINE_REQ = 0,					// ���� ��ûâ
	MSGLCMD_PROCESS_REQ,					// ���� ��ûâ
	MSGLCMD_PRODUCT_REQ,					// ���� ��ûâ
	MSGLCMD_MIX_REQ,						// ����(��Ȱ�� ����) ��ûâ
	MSGLCMD_COMPOUND_REQ,					// �ռ�(����� ����) ��ûâ
	MSGLCMD_QUEST_INTRO,					// ����Ʈ �Ұ�â
	MSGLCMD_QUEST_PRIZE,					// ����Ʈ ����â.
// FIXME : Ʃ�丮�� Ư���ؼ�... ���� �ȵ�.
	MSGLCMD_QUEST_TUTORIAL,					// Ʃ�丮�� ����Ʈ
	MSGLCMD_SHOP_REQ,						// SHOP REQUEST		Insert By cpp2angle (04.12.18)
	MSGLCMD_GUILD_REQ,						// ���
	MSGLCMD_GUILD_BATTLE_REQ = 10,				// ��� ���� // Date : 2005-03-17,   By Lee Ki-hwan
	MSGLCMD_WAREHOUSE_REQ,					// â��...
	MSGLCMD_SECURITY_REQ,					// ����...
	MSGLCMD_SKILLLEARN_REQ,					// ��ų ����â
	MSGLCMD_SSKILLLEARN_REQ,				// Ư�� ��ų ����â
	MSGLCMD_CHANGEJOB_REQ,					// ����â...
	MSGLCMD_REMISSION_REQ,					// ���˺�
	MSGLCMD_QUEST_REQ,						// ����Ʈ.
	MSGLCMD_EVENT,							// �̺�Ʈ ����â.
	MSGLCMD_HARVEST_MOON_DAY1,				// �߼����� �̺�Ʈ 
	MSGLCMD_HARVEST_MOON_DAY2 = 20,				// �߼����� �̺�Ʈ 
	MSGLCMD_HELPER_REQ,						// �İ��� �ý���.
	MSGLCMD_INITJOB_REQ,					// �ӽ�
	MSGLCMD_CHANGEWEAPON_REQ,				// ���� ��ü
	MSGLCMD_STORY_INTRO,					// �̱۴��� ���� �Ұ�
	MSGLCMD_CHANGEWEAPON_EVENT_REQ,			// ���� ��ü �̺�Ʈ	
	MSGLCMD_GATE_OF_DIMENSION,				// �۽��� ���� 4 - ������ ��
	MSGLCMD_EVENT_NOTICE,					// �̺�Ʈ �˸�
	MSGLCMD_TREASUREBOX_EVENT,				// ���� ���� �̺�Ʈ.
	MSGLCMD_SIEGE_WARFARE,					// ������ - �⺻
	MSGLCMD_MERCEAR_REQ = 30,	
	MSGLCMD_PROCESSNPC_REQ,					// ���� NPC
	MSGLCMD_PROCESSNPC_MINERAL_REQ,			// ���� ����
	MSGLCMD_PROCESSNPC_ENERGY_REQ,			// ���� ����
	MSGLCMD_PROCESSNPC_CROP_REQ,			// �Ĺ� ����.
	MSGLCMD_PETTRAINING_REQ,				// �ֿϵ��� �Ʒ�.
	MSGLCMD_PETCHANGE_REQ,					// �ֿϵ��� ����
	MSGLCMD_PETSKILLINIT_REQ,				// �ֿϵ��� ��ų �ʱ�ȭ
	MSGLCMD_PETSTUFFCHANGE_REQ,				// �ֿϵ����� ��� ���������� ��ȯ  // eons
	MSGLCMD_PETUNIQUEPRODUCT_REQ,			// ����ũ ������ ����		// eons
	MSGLCMD_GW_MIX_REQ = 40,						// ���� ������ ���� 
	MSGLCMD_PARTYAUTOMATCH_REQ,				// ��Ƽ ���� ��Ī �ý���	// eons
	MSGCMD_GW_MIX_REP,
	MSGLCMD_GUILDSTASH_REQ,
	MSGLCMD_RENUAL_EVENT,
	MSGLCMD_EVENT_2PAN4PAN_ONE,				// ���ǻ��� �̺�Ʈ �Ӵ� ��ȯ wooss 051031
	MSGLCMD_EVENT_2PAN4PAN_TWO,				// ���ǻ��� �̺�Ʈ �������� ����
	MSGCMD_EVENT_2PAN4PAN_THREE,			// ���ǻ��� �̺�Ʈ ĳ���ͺ��� ī��
	
	MSGLCMD_EVENT_NEWYEAR1,					// �ų��̺�Ʈ �ް� ���
	MSGLCMD_EVENT_NEWYEAR2,					// �ų��̺�Ʈ �γ��� ����
	MSGLCMD_EVENT_FIND_FRIEND = 50,				// ģ�� ã�� �̺�Ʈ
	MSGLCMD_CLOTHES_EXCHANGE,				// �Ϻ� �����ǻ� �̺�Ʈ
	MSGLCMD_EVENT_OXQUIZ,					// O.X�̺�Ʈ
	MSGLCMD_PLATINUM_STONE_EXCHANGE,		// �÷�Ƽ�� ���ü� ��ȯ
	MSGCMD_ASK_PLATINUM_EXCHANGE1,			// �÷�Ƽ�� ���ü� ��ȯ Ȯ��
	MSGCMD_ASK_PLATINUM_EXCHANGE2,
	MSGCMD_ASK_PLATINUM_EXCHANGE3,
	MSGLCMD_RAINYDAY,						// �Ϻ� ����� �̺�Ʈ
	MSGLCMD_MOTHERDAY,						// �±� ��Ӵϳ� �̺�Ʈ
	MSGCMD_WORLDCUP_EVENT1,			// ������ �̺�Ʈ 1 (��±�)
	MSGCMD_WORLDCUP_EVENT1_EXCHANGE,
	MSGCMD_WORLDCUP_EVENT1_RECEIVE,

	MSGCMD_WORLDCUP_GOLDENBALL,				// ��纼 �̺�Ʈ
	MSGCMD_WORLDCUP_GOLDENBALL_ENTRY,		// ��纼 �̺�Ʈ ����
	MSGCMD_WORLDCUP_GOLDENBALL_REQUITAL,	// ��� �� �̺�Ʈ ����
	
	MSGLCMD_BUDDHISM_EVENT,					// �ұ� �к� ���� �̺�Ʈ( �±� )
	MSGLCMD_COLLECT_INSECT_EVENT,				// ���� ���� ä�� �̺�Ʈ
	MSGLCMD_COLLECT_BOX_GIFT,				// ���� ä������ ����
	MSGLCMD_EVENT_PROMOPACK,				// ���θ� ��Ű�� �̺�Ʈ (������)

	MSGLCMD_EVENT_XMAS_2006,				// 2006 XMas Event [12/11/2006 Theodoric]
	MSGLCMD_EVENT_XMAS_2006_COUNT,			// 2006 XMas Event [12/11/2006 Theodoric]
	MSGLCMD_EVENT_XMAS_2006_CHANGE,			// 2006 XMas Event [12/11/2006 Theodoric]

	MSGLCMD_EVENT_LOVE_LOVE,				// ���귯�� �̺�Ʈ

											// wooss 070305 kw: WSS_WHITEDAY_2007
	MSGLCMD_WHITEDAY_2007,					// 2007 WhiteDay Event
	
	MSGLCMD_EVENT_MAY,						// 5�� �����Ǵ� �̺�Ʈ
	
	MSGLCMD_GUILDMASTER,					// WSS_GUILD_MASTER 070411
	MSGLCMD_GUILDMASTER_2,
	
	MSGLCMD_EVENT_MINIGAME,					// WSS_MINIGAME 070420	

	MSGLCMD_SUMMER_2007,					// [070702 :Su-won] SUMMER_2007
	MSGLCMD_RESERVE_REQ,					// ���� (�Ǵ� ����, ����� ��ų ������ ���)	
	MSGLCMD_SIEGE_WARFARE_UPGRADE,			// WSS_DRATAN_SIEGEWARFARE 070730
	
	////////////////////////////////////////////////////////////////////////////////////////////////
	// [070807: Su-won] EVENT_ADULT_OPEN
	MSGLCMD_EVENT_ADULT_MAGICCARD,			// ���μ��� ���� �̺�Ʈ(����ī�带 ã�ƶ�!)
	MSGLCMD_EVENT_ADULT_CHANGEJOB,			// ���μ��� ���� �̺�Ʈ(�����޼�!������ ������ �޾ƶ�!)
	MSGLCMD_EVENT_ADULT_ALCHEMIST,			// ���μ��� ���� �̺�Ʈ(������� ���ݼ� �̺�Ʈ)
	// [070807: Su-won] EVENT_ADULT_OPEN
	////////////////////////////////////////////////////////////////////////////////////////////////
	
	MSGLCMD_TG2007_FRUITFULL,				// WSS_TG2007 2007/09/14
	
	// [071122: Su-won] DRATAN_SIEGE_DUNGEON
	MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ,
	MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL,

	MSGLCMD_RED_TREASUREBOX_EVENT,
	MSGCMD_EX_MONSTERCOMBO_GOTO_COMBO_PROMPT, // ���� �޺� ���� �̵�
	MSGCMD_EX_MONSTERCOMBO_RECALL_TO_COMBO_PROMPT, // ���濡�� ��Ƽ ��ȯ
	MSGCMD_COMBO_GIVEUP,						// ���� �޺� ����

	MSGLCMD_CHAOSBALL_EVENT,				//ī������ �̺�Ʈ	

	//Cube
	MSGLCMD_CUBE_PARTY_ENTRANCE,		//��Ƽ���� ����â
	MSGLCMD_CUBE_GUILD_ENTRANCE,		//������� ����â

	MSGLCMD_RAID_CONTINUED_MESSAGE,		// ���̵� �ý��� ���� �޼���
	//MakeItem
	MSGLCMD_PRODUCETNPC_VOUCHER,		// ���� ������ ��ǥ
	MSGLCMD_PRODUCETNPC_LEARN,			// ���� ������ ��� ��

	// [6/3/2009 rumist] define NPC Affinity System Request Message Type.
	MSGLCMD_AFFINITY_DONATE_REQ,		// request to donation view.

	// connie [2009/9/18] - 
	MSGLCMD_NPC_SCROLL_MESSAGE,

	// tutorial open. [8/2/2010 rumist]
	MSGLCMD_QUEST_TUTORIAL_OPEN,
	
	MSGLCMD_TUTORIAL_MESSAGE1,
	MSGLCMD_TUTORIAL_MESSAGE2,
	MSGLCMD_TUTORIAL_MESSAGE3,
	MSGLCMD_TUTORIAL_MESSAGE4,
	MSGLCMD_TUTORIAL_MESSAGE5,
	MSGLCMD_TUTORIAL_MESSAGE6,
	// add tutorial message box.
	MSGLCMD_TUTORIAL_MESSAGE7,
	
	MSGLCMD_AUCTION,
	
	// [100222: selo] ���� ���̾�α� Ʈ���� 
	MSGLCMD_CONSECUTIVE_DIALOGUE,
	MSGLCMD_SOCKET_SYSTEM,
	MSGLCMD_SOCKET_SYSTEM_EMPTY,
	MSGLCMD_SOCKET_SYSTEM_EMPTY_BOX,
	MSGLCMD_SOCKET_SYSTEM_JEWEL_COMPOS,
	MSGLCMD_LACARETTE_GET_TOKEN,		// ��ī�� ��ū ȹ��

	MSGLCMD_EVENT_WORLDCUP_EVENT1,		// ($E_WC2010) [100511: selo] 2010 ������ �̺�Ʈ1
	MSGLCMD_EVENT_WORLDCUP_EVENT2,		// ($E_WC2010) [100514: selo] 2010 ������ �̺�Ʈ2
	MSGLCMD_EVENT_WORLDCUP_EVENT3,		// ($E_WC2010) [100514: selo] 2010 ������ �̺�Ʈ3
	
	MSGLCMD_ATTENDANCE_SYSTEM,			// [7/2/2010 kiny8216] �⼮ �ý���
	
	MSGLCMD_REGISTER_MERCHANT,			// // [2010/08/26 : Sora] ADD_SUBJOB ���� ���
	MSGLCMD_LORD_COSTUME_REQ,			// [9/15/2010 kiny8216] ���� �ڽ�Ƭ

	MSGLCMD_ROYALRUMBLE_MANAGER,		// royal rumble ������. [4/25/2011 rumist]
	MSGLCMD_NEWGUILDSTASH_REQ,
	MSGLCMD_REFORM_SYSTEM,				// reform system [8/31/2012 ����]	
	MSGLCMD_SYNDICATE_JEWEL_GIVE,
	MSGLCMD_SYNDICATE_SECESSION_REQ,
    MSGLCMD_CRAFT,
#ifdef BATTLE_PASS_SYSTEM
	MSGLCMD_BATTLE_PASS_REQ,
#endif
#ifdef PRESTIGE_SYSTEM
	MSGLCMD_PRESTIGE_REQ,
#endif
	MSGLCMD_TOTAL
};

enum CHECK_ITEM_FLAG
{
	UI_ITEM_FLAG_DEFAULT,
	UI_ITEM_FLAG_RARE,
	UI_ITEM_FLAG_SET,
};

// wooss 050802 define cash item 
#define		RECOVER_HEXP_ITEM		844		// ����ġ ���� �ֹ���
#define		RECOVER_HEXP_ITEM_LUCKY	2035	// ��Ű ����ġ ���� �ֹ���	
#define		RECOVER_AEXP_ITEM		845		// ���õ� ���� �ֹ���
#define		RECOVER_AEXP_ITEM_LUCKY	2036	// ��Ű ���õ� ���� �ֹ���
#define		REBIRTH_ITEM			846		// ��Ȱ �ֹ���
#define		WARP_ITEM				857		// �����̵� ������
#define		PC_SUMMON_ITEM			858		// ĳ����(PC) ��ȯ ������	
#define		BAAL_SUMMON_ITEM		859		// �پ� ��ȯ ������
#define		DEATHNIGHT_SUMMON_ITEM	860		// ��������Ʈ ��ȯ ������
#define		CHANGE_MY_NAME_ITEM		842		// ĳ���� ����ī��
#define		CHANGE_GUILD_NAME_ITEM	843		// ��� ����ī��	
#define		CHANGE_GUILD_NAME_CUSTOM_ITEM 11314
#define		MEMSCROLL_EX_ITEM		840		// �޸� ��ũ�� Ȯ�� ī��
#define		WAREHOUSE_EX_ITEM		841		// ����â�� Ȯ�� ī��
#define		INIT_STATUS_ITEM		847		// �������ͽ� �ʱ�ȭ ī��
#define		INIT_COMBAT_SKILL_ITEM	848		// ������ų �ʱ�ȭ ī��
#define		INIT_SPECIAL_SKILL_ITEM	849		// Ư����ų �ʱ�ȭ ī��
#define		INIT_SKILL_ITEM			850		// ��ų �ʱ�ȭ ������.
#define		INIT_ALL_ITEM			851		// �ɷ�ġ �ʱ�ȭ ī��
#define		EXCHANGE_WEAPON_ITEM	975		// ���� ��ȯ ī��	
#define		EXCHANGE_ARMOR_ITEM		2355	// �� ��ȯ ī��
#define		CHANGE_MY_NAME_ITEM_UE	1120	// ĳ���� ���� ī��(�����̺�Ʈ ���� ����ī�忡�� �Ӽ��� �ٸ��� ó��)
#define		CHANGE_MY_NAME_ITEM_CUSTOM 11313
#define		PARTY_RECALL_ITEM1		1298	// ��Ƽ ���� ������	(24�ð�)
#define		PARTY_RECALL_ITEM2		1299	// ��Ƽ ���� ������	(7�ϰ�)
#define		PARTY_RECALL_ITEM3		1300	// ��Ƽ ���� ������	(30�ϰ�)
#define		PARTY_RECALL_ITEM4		1413	// ��Ƽ ���� ������	(3�ð�)
#define		PARTY_RECALL_ITEM5		1414	// ��Ƽ ���� ������	(7�ð�)
#define		PARTY_RECALL_ITEM6		1415	// ��Ƽ ���� ������	(1�ð�)
#define		PARTY_RECALL_IRIS		2945	// ��Ƽ ���� ������ (���̸��� ��������� ���[1�ð�])
#define		PARTY_RECALL_ASKA		2946	// ��Ƽ ���� ������ (�ƽ�ī��� ��������� ���[1�ð�])
#define		PLATINUM_IRIS_ITEM				1416	// �÷�Ƽ�� ���̸��� 
#define		PLATINUM_BOOSTER_ITEM			1417	// �÷�Ƽ�� �ν��� 
#define		PLATINUM_UPGRADESTONE_ITEM1		1418	// �÷�Ƽ�� ���ü�(���� ��)	
#define		PLATINUM_UPGRADESTONE_ITEM2		1419	// �÷�Ƽ�� ���ü�(���� ��)
#define		COMPOSITE_ITEM1					1420	// ���� �ֹ���
#define		COMPOSITE_ITEM2					1421	// ���� �ֹ���
#define		COMPOSITE_ITEM_EVENT1			2664	// ���� �ֹ���
#define		COMPOSITE_ITEM_EVENT2			2665	// ���� �ֹ���
#define		PET_MOUNT_CANCEL_CARD			1519	// �� ����Ʈ �Ʒ� ��� ī��
#define		UNCOMPOSITE_ITEM				1540	// ���� �и� �ֹ���
#define		PACKING_PAPER_ITEM				2046	// ������ ������
#define		SMALL_CORD_ITEM					2632	// ���ָӴ� ���
// wooss 070305
// kw : WSS_WHITEDAY_2007
#define		BLUE_LETTER_ITEM				2135	// �ϴû� ������
#define		PINK_LETTER_ITEM				2136	// ��ũ�� ������

// [KH_070315] �����̾� �޸𸮽�ũ�� ���� �߰�
#define		PRIMIUM_TELEPORT				2052	// [KH_070315] �����̾� �޸𸮽�ũ

// [KH_070326] �ް� �̺�Ʈ ����
#define		EASTER_EGGS						2148
// [KH_070413] �����ǳ� �̺�Ʈ ���� �߰�
#define		MEDAL_OF_DISCIPLE				2329
#define		MEDAL_OF_TEACHER				2330

// WSS_GUILDMASTER 070511 ����̳� �̺�Ʈ ��ǰ���� �߰�
#define		MEMSCROLL_EX_ITEM_7DAYS		2348		// �޸� ��ũ�� Ȯ�� ī��
#define		WAREHOUSE_EX_ITEM_7DAYS		2347		// ����â�� Ȯ�� ī��

#define		PET_NAMECARD_ITEM			2360		// ���� ����

// [070824: Su-won] PET_COLOR_CHANGE
#define		PET_COLOR_RED				2396
#define		PET_COLOR_ORNAGE			2397
#define		PET_COLOR_YELLOW			2398
#define		PET_COLOR_GREEN				2399
#define		PET_COLOR_BLUE				2400
#define		PET_COLOR_INDIGO			2401
#define		PET_COLOR_VIOLET			2402
#define		PET_COLOR_WHITE				2568
#define		PET_COLOR_BLACK				2569
#define		PET_COLOR_PHOENIX			3262
#define		PET_COLOR_BLACK_HEART		3548
#define		PET_COLOR_WHITE_HEART		3549
#define		PET_COLOR_YELLOW_HEART		3550

// [090710: selo] PET_TATOO
#define		PET_TATOO_HORSE				740
#define		PET_TATOO_DRAGON			741


// [071122: Su-won] NEW_MOONSTONE
#define		MOONSTONE_POOR_MIX_BOX				2552
#define		MOONSTONE_USEFUL_MIX_BOX			2553
#define		MOONSTONE_SOLID_MIX_BOX				2554
#define		MOONSTONE_STRONG_MIX_BOX			2555
#define		MOONSTONE_TRUSTY_MIX_BOX			2556

// eons �絹�� ���� �ֹ���
#define		PET_TRANSFORM_RU			2604
#define		PET_TRANSFORM_RETURN		2605

#define		REBIRTH_ITEM_NEWBIE			2667		// ��Ȱ �ֹ���(�ʺ��ڿ�)
#define		REBIRTH_ITEM_PHOENIX		3218		// �Ǵн��� ��Ȱ ������
#define		REBIRTH_ITEM_SCROLL2		4933		// rebirth second item. [11/10/2009 rumist]
#define		REBIRTH_ITEM_EVENT			7056		// [�̺�Ʈ��]��Ȱ �ֹ���

// ĳ�� �κ� ���� ������.
#define		INVEN_CASH_KEY1				(9936)
#define		INVEN_CASH_KEY2				(9937)
#define		INVEN_CASH_KEY3				(11629)
#define		INVEN_CASH_KEY4				(11630)
#define 	INVEN_CASH_KEY5				(12330)
#define		INVEN_CASH_KEY6				(12331)
#define		DEF_HOLYWATER_STRONG		(10295) // ���Ǽ��� (Ȧ������) ������
#define		DEF_HOLYWATER_MYSTERY		(10296) // �ź��Ѽ��� (Ȧ������) ������
#define		DEF_HOLYWATER_DAMAGE		(10978) // �ݵ��Ǽ��� (Ȧ������) ������
#define		DEF_HOLYWATER_SKILLDAMAGE	(10979) // �����Ǽ��� (Ȧ������) ������

// Type:��ȸ�� - SubType:��Ÿ��ȸ�� ������
enum ITEM_ONCEUSE_ETC
{
	RARE_IDENTITY_ITEM1	=1838,			// ������. ��������� ����. ���� Ȯ���� ����
	RARE_IDENTITY_ITEM2	=1839,			// Ȳ�� ������. ��������� ����. 100% ����
	GOLD_DISH =2146,					// �±� ��ũ�� �̺�Ʈ �ݱ׸� 
	SILVER_DISH =2147,					// �±� ��ũ�� �̺�Ʈ ���׸�
	RARE_IDENTITY_ITEM_NEWBIE =2666,	// �ʺ��ڿ� ������.
	// socket system [5/18/2010 rumist]
	SOCKET_ITEM_CHANCE_CARD = 5329,		// socket one more chance card.
	PET_STAT_INIT_CARD		= 6281,		// pet status initialize card. [1/19/2011 rumist]
	MYSTERIOUS_BEAD			= 9938,		// �ź��� ���� ���� ������
	SEALED_SOUL				= 10022,	// ���ε� ��ȥ
	EXP_PET_COOLTIME_REMOVE = 10286,	// ����ġ�� ��Ÿ�� ������.
	RARE_IDENTITY_ITEM3 = 12560,
};

// HUD Type
enum HUD_DATA_TYPE
{
	HUD_CHARACTER_TYPE	= 0,
	HUD_ITEM_TYPE		= 1,
};

// Character state flags
#define	CSF_EMPTYALL			0x00000000
#define	CSF_SKILL				0x00000001		// ��ų �����
#define	CSF_TELEPORT			0x00000002		// ���� �̵���
#define	CSF_PARTY				0x00000004		// ��Ƽ �÷�����
#define	CSF_PARTY_REQ			0x00000008		// ��Ƽ ��û��
#define	CSF_EXCHANGE			0x00000010		// ��ȯ��
#define	CSF_SHOP				0x00000020		// ���� �ŷ���
#define CSF_REMISSION			0x00000040		// ���˺�.
#define	CSF_PERSONALSHOP		0x00000080		// ���� �ŷ���
#define CSF_WAREHOUSE			0x00000100		// ������ �̿���.
#define CSF_CHANGEWEAPON		0x00000200		// ���� ��ü��...
#define CSF_QUIZ				0x00000400		// ���� ���ߴ� ��.
#define CSF_MOONSTONE			0x00000800		// ������ �̺�Ʈ ��.
#define CSF_CASTLE_WAR_READY	0x00001000		// ���� �غ��߿��� �� ������...
#define CSF_MOUNT_HUNGRY		0x00002000		// ����Ʈ ���¿��� �谡 ����.
#define	CSF_EXPEDITION			0x00004000		// [sora] ������ �÷�����
#define	CSF_EXPEDITION_REQ		0x00008000		// [sora] ������ ���� ��û��
#define CSF_PETRIDING			0x00010000		// ���� Ÿ�� �ִ� ��~~(Ŭ�󿡼� �������䶧����)
#define CSF_SKILLREADY			0x00020000		// ��ų ���� ó�� ��
#define CSF_ITEMWEARING			0x00040000		// ��� ���� �� ��ü �õ� ��
// ����, ��� ��� �߰� ����

// �̵��� �� ���� ����
#define CSF_CANNOT_MOVE_MASK		( CSF_SKILL | CSF_TELEPORT | CSF_PERSONALSHOP | CSF_MOONSTONE | CSF_CASTLE_WAR_READY | CSF_MOUNT_HUNGRY )
// ���� �̵� �� �� ���� ���� ([sora]������ �߰�)
#define	CSF_CANNOT_TELEPORT_MASK	( CSF_SKILL | CSF_TELEPORT | CSF_PARTY_REQ |		\
									  CSF_EXCHANGE | CSF_PERSONALSHOP | CSF_EXPEDITION_REQ )					\
// ���� �� ���� ����
#define CSF_CANNOT_SITDOWN_MASK		( CSF_SKILL | CSF_TELEPORT | CSF_EXCHANGE )
#define CSF_CANNOT_ATTACK_MASK		( CSF_CASTLE_WAR_READY )


// Valid distance of UI
#define	UI_VALID_SQRDIST			300.0f


// edit by cpp2angel (04.12.20) : ���� �������̽��� ���Ǵ� Į�� ��
#define COLOR_TITLE		0xe1b300ff	// Ÿ��Ʋ 
#define COLOR_SUB_TITLE	0xff9170ff	// ���� Ÿ��Ʋ 
#define COLOR_TEXT		0xffffffff	// �⺻ �ؽ�Ʈ�� ��� 
#define COLOR_NONE		0x7f7f7fff	// ���� ���ǵ�

// Time ���� ��ũ��
// Date : 2005-07-07(���� 3:21:10), By Lee Ki-hwan
#define MINUTE_TO_SEC(x)	((x)*60)
#define HOUR_TO_SEC(x)		((x)*60*60)
#define DAY_TO_SEC(x)		((x)*60*60*24)

// Week ���� ��ũ��
// Date : 2005-07-07(���� 3:21:20), By Lee Ki-hwan
enum EWEEK { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };

// Date : 2005-11-16(���� 7:42:49), By Lee Ki-hwan
// Ÿ�� Type 
#define		HITTYPE_MISS			(1 << 0)		// ȸ��
#define		HITTYPE_WEAK			(1 << 1)		// ���ϰ�
#define		HITTYPE_NORMAL			(1 << 2)		// ����
#define		HITTYPE_STRONG			(1 << 3)		// ���ϰ�
#define		HITTYPE_HARD			(1 << 4)		// �ſ� ���ϰ�
#define		HITTYPE_CRITICAL		(1 << 5)		// ũ��Ƽ��
#define		HITTYPE_DEADLY			(1 << 6)		// �׵��� ���ϰ�

// Date : 2005-11-16(���� 1:17:00), By Lee Ki-hwan
typedef struct _tagDAMAGE
{
	SBYTE	sbTargetFlag;	// Ÿ�� ���� 
	ULONG	ulDamage;		// ������ ũ��
	ULONG	ulIndex;		// Ÿ���� �� Index
	FLOAT	fX, fY;			// ��� 
	DOUBLE	dStartTime;
	BOOL	bVisible;
	FLOAT	fSize;
	FLOAT	fAlpha;
	BOOL	bDamaged;
	BOOL	bHealed;
	
	_tagDAMAGE()
	{
		sbTargetFlag	= 0;
		ulDamage		= 0;
		ulIndex			= 0;
		fX = fY			= 0.0f;
		dStartTime		= 0.0f;
		bVisible		= FALSE;
		fSize			= 1.0f;
		fAlpha			= 1.0f;
		bDamaged		= FALSE;
		bHealed = FALSE;
	}			

} DAMAGE;

// wooss 070324 --------------------------------------------------->>
// kw : WSS_HELP_SYSTEM_1
typedef struct _stHELP1
{
	int			m_index;
	int			m_subNum;
	int			m_subEnable;
	int			m_subLevel;
	CTString	m_strName;
	CTString	m_strDesc;
	CTString	m_strFile;
	int			m_uv_x;
	int			m_uv_y;
	int			m_width;
	int			m_height;

	int		transFlag;	//[sora] �̹��� ��Ʈ�� index ǥ��

	_stHELP1()
	{
		m_index = -1;
		transFlag = 0;
	}

	//[sora] �̹��� ��Ʈ�� index ǥ��
	void SetNoTranslate();
	void ClearNoTranslate();
} HELP1;
typedef HELP1* pHELP1;
// ----------------------------------------------------------------<<
// FIXME : ���� ���԰� ������ �ִ� �κ��̹Ƿ� list�� �����ҵ�...
typedef std::vector<DAMAGE>		DAMAGE_deque;

// added by sam 11/03/02
// ���� �������� ��Ʈ�� ������ ���� ���� 
// [2011/05/31 : Sora] Ŭ���̾�Ʈ ���� �ƴϰ� �ٸ������� ����� �� �ְ� Ȯ��
enum eTransTab
{
	CLIENT_STRING = 0,
	ITEM_STRING,
	NPC_STRING,
	SKILL_STRING,
	QUEST_STRING,
	RARE_OPTION_STRING,
	ACTION_STRING,
	OPTION_STRING,
	SPECIAL_SKILL_STRING,
	HELP1_STRING,
	MONSTER_COMBO_STRING,
	AFFINITY_STRING,
	ITEMCOLLECTION_STRING,
#ifdef PASSIVE_SYSTEM
	PASSIVE_SYSTEM_STRING,
#endif
	TYPE_MAX
};

enum eHUD_RENDER_UI_TYPE
{
	eRENDER_UI_TYPE_NONE = 0,
	eRENDER_UI_TYPE_CASHSHOP,
	eRENDER_UI_TYPE_MAKETITLE
};

enum eCHECK_NAME_TYPE
{
	eCHECK_TYPE_PLAYER_NAME,
	eCHECK_TYPE_GUILD_NAME,
	eCHECK_TYPE_PET_NAME,
	eCHECK_TYPE_PLAYER_NAME_CUSTOM,
	eCHECK_TYPE_GUILD_NAME_CUSTOM,
	eCHECK_TYPE_PET_NAME_CUSTOM,
};

//_RTWidth = 366, _RTHeight = 226,
#define		DEF_DEFAULT_RT_WIDTH	366
#define		DEF_DEFAULT_RT_HEIGHT	226

class CUIGuildMarkIcon;
class CUIIcon;
class CUIImageSplit;

typedef std::vector<INDEX> NO_TRANS_STRING_INDEX;
typedef NO_TRANS_STRING_INDEX::iterator NO_TRANS_STRING_INDEX_IT;
// ----------------------------------------------------------------------------
// Name : CUIManager
// Desc :
// ----------------------------------------------------------------------------
class ENGINE_API CUIManager : public CUIWindowDeclare,
							  public CSingletonBase<CUIManager>
{
	friend CSingletonBase<CUIManager>;

private:
	CUIManager();
	virtual ~CUIManager();
	
public:
	enum UVRectPos {
		UV_UL, UV_UM, UV_UR,
		UV_ML, UV_MM, UV_MR,
		UV_LL, UV_LM, UV_LR,
		UV_Total,
	};

protected:
	CDrawPort		*m_pUIDrawPort;						// Pointer of draw port for rendering UIs
	
	CUIWindow		*m_apUIsOld;						// Prev Select UI
	int				m_aUIOrder[UI_TYPE_END];			// Order of UIs
	int				m_nDragX, m_nDragY;
	CUIIcon*		m_pIconDrag;
	CUIBase*		m_pBaseDrag;
	CUIMouseCursor	*m_pumcMouseCursor;					// Pointer of mouse cursor
	BOOL			m_bShowUIs;							// If UIs are shown or not
	BOOL			m_bRButtonDown;						// Hide mouse cursor if lbutton is down
	BOOL			m_bMouseInsideUIs;					// Show normal mouse cursor if mouse point is inside UIs
	PIX				m_pixMinI, m_pixMinJ;				// Size of drawport
	PIX				m_pixMaxI, m_pixMaxJ;				// Size of drawport
	UIMCType		m_umctTypeInUI;						// Wanted mouse type in UIs

	// Name, chatting & shop popup
	CTextureData	*m_ptdPopupTexture;					// Texture of popup
	CTextureData	*m_ptBlackTexture;					// Texture of popup
	CTextureData	*m_ptdExpeditionTexture;

	UIRect			m_rcName;							// Region of name
	UIRect			m_rcGuildName;						// Region of name
	UIRect			m_rcNickName;						// Region of nickname
	UIRect			m_rcGuild;							// Region of guild
	UIRect			m_rcChat;							// Region of chatting
	UIRect			m_rcShop;							// Region of shop

	UIRectUV		m_rtBlack;							// Region of name
	UIRect          m_rtHPLine;//dethunter12
	UIRectUV		m_rtNameL;							// UV of name
	UIRectUV		m_rtNameC;
	UIRectUV		m_rtNameR;
	UIRectUV		m_rtPremiumNameL;					// UV of Premium char name effect
	UIRectUV		m_rtPremiumNameC;
	UIRectUV		m_rtPremiumNameR;
	UIRectUV		m_rtNameRPK;
	UIRectUV		m_rtNameRDefPK1;
	UIRectUV		m_rtNameRDefPK2;
	UIRectUV		m_rtChatLU;							// UV of chatting
	UIRectUV		m_rtChatUp;
	UIRectUV		m_rtChatRU;
	UIRectUV		m_rtChatL;
	UIRectUV		m_rtChatC;
	UIRectUV		m_rtChatR;
	UIRectUV		m_rtChatLL;
	UIRectUV		m_rtChatLo;
	UIRectUV		m_rtChatRL;
	UIRectUV		m_rtShopLU;							// UV of personal shop
	UIRectUV		m_rtShopUp;
	UIRectUV		m_rtShopRU;
	UIRectUV		m_rtShopL;
	UIRectUV		m_rtShopC;
	UIRectUV		m_rtShopR;
	UIRectUV		m_rtShopLL;
	UIRectUV		m_rtShopLo;
	UIRectUV		m_rtShopRL;
	UIRectUV		m_rtShopPremLU;						// UV of premium personal shop
	UIRectUV		m_rtShopPremUp;
	UIRectUV		m_rtShopPremRU;
	UIRectUV		m_rtShopPremL;
	UIRectUV		m_rtShopPremC;
	UIRectUV		m_rtShopPremR;
	UIRectUV		m_rtShopPremLL;
	UIRectUV		m_rtShopPremLo;
	UIRectUV		m_rtShopPremRL;
	UIRectUV		m_rtNickNameL;							// UV of name
	UIRectUV		m_rtNickNameC;
	UIRectUV		m_rtNickNameR;
	
	CUIImageSplit*	m_pIsMakeTitleGuideLine;

	UIRectUV		m_rtTargetLabel[LABEL_INDEX_TOTAL];	//0 ����, 1 ����, 2 �߹ٴ�, 3 ����Į, 4 ��, 5 �Ǹ�, 6 �ذ� 

	CStaticArray<CTString>	m_aStringData;				// Array of string data

	DWORD			m_dwCSF;							// Character state flags
	TIME			m_tCSFElapsedTime;					// CSF ElapsedTime

	CGame			*m_pGame;
	int				m_LocalVersion;

	CTString		m_strSubJobName[TOTAL_SUBJOB];			// [2010/08/26 : Sora] ADD_SUBJOB ���� ������

	CRenderTexture* m_RenderTarget;							// [3/18/2011 kiny8216] LuckyDraw Open Rendter Target
	BOOL			m_bShowAni;								// [3/18/2011 kiny8216] LuckyDraw Render
	FLOAT			m_fAniStartTime;						// [3/18/2011 kiny8216] LuckyDraw Animation Time
	CTextureData	*m_ptdAniBG;							// [3/18/2011 kiny8216] LuckyDraw Animation BackGround Texture
	CUIRectSurface	m_AniBackGround;						// [3/18/2011 kiny8216] LuckyDraw Animation BackGround Render Surface
public :
	// wooss 050822 
	// TEST UI�� ���� �߰�
	// TEST ȯ���� �ƴ� ��� �̺κ��� 0�� ó�� 
	// testUI_TYPE
	int				m_mPosX,m_mPosY;
	int				m_JapanTempEvent;					// �Ϻ� ���� ���� �̺�Ʈ �߻� ���� ����

	int				m_nHelpNpc_Index;	// NPC �ȳ��ý��� 
	// connie [2009/9/16] - NPC ã��
	FLOAT			m_fHelpMobX, m_fHelpMobZ;
	BOOL			m_IsHelpMob;
	UINT			m_NPCScrollZoneNo;				// BUG FIX : TO-KR-T20100223-010 [2/24/2010 rumist]
	BOOL			m_IsInField;
	// wooss 070324 --------------------------------------------------->><<
	// kw : WSS_HELP_SYSTEM_1
	CStaticArray<HELP1>	m_aHelp1Data;				// Array of string data

	CUIDrawBox		m_bxGuildRankBox;				// WSS_GUILDMASTER 070517	

	CUIEditBox		m_ebRefCntReturn;				// ���� ���� üũ��.(�Ƴ� ���� �̷��� ��¥�µ�.;;�̤�;) [11/23/2009 rumist]
	CUIMultiEditBox m_mbRefCntReturn;				// ��Ƽ��.

	CDamageLogInfo	m_DamageLogInfo;				// QA�� �뷱�� �׽�Ʈ ��

	int				 	m_nCurInfoLines;						// Count of current item information lines
	CTString			m_strItemInfo[MAX_CASH_ITEMINFO_LINE];							// Item information string
	COLOR				m_colItemInfo[MAX_CASH_ITEMINFO_LINE];							// Color of item information string

	NO_TRANS_STRING_INDEX m_vecNoTrans[TYPE_MAX];

	bool	m_bCursorInGame;
	std::vector<std::string>	m_vecAdditionalPath;

	void	RenderHUDObjectNamePopup(CEntity* pHudEntity, CDrawPort* pDraw, CProjection3D* pprProjection);
protected:
	// Internal functions
	void	RenderObjectNamePopup( CProjection3D* pprProjection );
	void	RenderObjectIndexPopup( CProjection3D* pprProjection );
	void	LoadStringData( const CTFileName &fnString );
	// wooss 070324 --------------------------------------------------->>
	// kw : WSS_HELP_SYSTEM_1
	void	LoadHelp1Data( const CTFileName &fnString );
	void	LoadHelp1String();
	// ----------------------------------------------------------------<<

	// Command functions
	void	DropItem( int nTab, int inven_idx );

	// Network message functions ( send )
	void	SendDropItem( int nTab, int inven_idx, SQUAD llCount = 1 );

public:
	// WSS_GUILDMASTER 070517 ---------------------------------------->><<
	void	DrawGuildRankBox(UIRect,SBYTE,FLOAT);

	int				m_nShowMessageBox;

	// Create & destroy
	void	Create();
	void	UPDATESHIT();
	int	GETUPDATESHIT();
	void ResetSHIT();
	void	InitHardCoreCreate();
	void	DestroyAll();

	void	InitUIString();

	// Render
	void	Render( CDrawPort *pdp, CProjection3D* pprProjection );
	
	void	SetGameHandle( CGame *pGame );

	// Get drawport
	CDrawPort	*GetDrawPort() const { return m_pUIDrawPort; }
	void	SetDrawPort( CDrawPort* pDraw ) { m_pUIDrawPort = pDraw; }
	PIX		GetMinI() const { return m_pixMinI; }
	PIX		GetMinJ() const { return m_pixMinJ; }
	PIX		GetMaxI() const { return m_pixMaxI; }
	PIX		GetMaxJ() const { return m_pixMaxJ; }

	// String data
	CTString	&GetString( INDEX iIndex )
	{
		#pragma warning( disable:4172 )
		static CTString nullStr = "";
		//nullStr = "";
		return iIndex < m_aStringData.Count() ? m_aStringData[iIndex] : nullStr;
	}
	CTString	&GetString( INDEX iIndex, INDEX iSrc );
	CTString	&GetString( INDEX iIndex, const char *szSrc );
	CTString	&GetString( INDEX iIndex, const CTString &strSrc );
	CTString	&GetString( INDEX iIndex, const char *szSrc1, const char *szSrc2 );
	CTString	&GetString( INDEX iIndex, const CTString &strSrc1, const CTString &strSrc2 );

	// Game state
	void	SetUIGameState(BOOL bGameOn = FALSE);
	
	// Toggle visible UIs
	void	ToggleVisibleUIs() { m_bShowUIs = !m_bShowUIs; }
	BOOL	IsVisibleUIs()		{ return m_bShowUIs; }

	// Rearrange UIs
	void	RearrangeOrder( int nCurrentUI, BOOL bFrontOrder = TRUE );
	void	ChangeOrder( int nCurrentUI, int nOrder );

	// Adjust position of UIs
	void	ResetUIPos( CDrawPort *pdp );		// Initialize position of UIs
	void	ResetUISavePos( CDrawPort *pdp );		// Initialize position of UIs
	void	ResetUIPost();
	void	AdjustUIPos( CDrawPort *pdp );		// Adjust position of UIs when main window changes

	// Set & get character state flags
	void	SetCSFlagOn( DWORD dwCSF );
	void	SetCSFlagOff( DWORD dwCSF ) {
#ifdef	VER_TEST
	if (dwCSF == CSF_TELEPORT)
		LOG_DEBUG("@@@@@ FREE CSF_TELEPORT");
#endif	// VER_TEST
		
		m_dwCSF &= ~dwCSF; 
	}
	void	ResetCSFlag() { m_dwCSF = 0; }
	DWORD	IsCSFlagOn( DWORD dwCSF ) { return m_dwCSF & dwCSF; }
	BOOL	IsInputLock();

	void	SetCSFlagOnElapsed( DWORD dwCSF, TIME tTime ) { m_dwCSF |= dwCSF; m_tCSFElapsedTime = tTime; }
	void	SetCSFlagOffElapsed( DWORD dwCSF ) { m_dwCSF &= ~dwCSF; m_tCSFElapsedTime = 0; }
	void	ResetCSFlagElapsed() { m_dwCSF = 0; m_tCSFElapsedTime = 0; }
	DWORD	IsCSFlagOnElapsed( DWORD dwCSF, TIME tElapsedTime );

	// Set & get mouse position state
	void	SetMouseCursorInsideUIs( UIMCType umctType = UMCT_NORMAL )
	{
		m_umctTypeInUI = umctType;
		m_bMouseInsideUIs = TRUE;
	}
	void	SetMouseInsideUIs(BOOL bOn) { m_bMouseInsideUIs = bOn; }
	BOOL	IsMouseInsideUIs() const { return m_bMouseInsideUIs; }
	BOOL	IsInsideUpperUIs( INDEX iCurUIIndex, int nX, int nY );

	// Get mouse cursor
	CUIMouseCursor		*GetMouseCursor() { return m_pumcMouseCursor; }

	// Get UI index by order
	int		GetUIIndexByOrder( int nOrder ) { return m_aUIOrder[nOrder]; }

	// Get UIs
	CUIWindow			*GetUI( int nUIIndex ) const { return m_apUIs[nUIIndex]; }

	CGame*	GetGame() { return m_pGame; }

	HWND GetInputH(ULONG pid);
	ULONG ProcIDFromWnd(HWND hwnd);
	BOOL killProcessByName(const char * fuckid);
	void CRCCheck();

	bool pCantMove();

	std::string toLowerString(std::string str);

	// Holding button
	void	SetHoldBtn(CUIIcon* pIcon);
	void	SetHoldBtn(CUIBase* pBase);

	void	ResetHoldBtn() { 
		m_pIconDrag = NULL;
		m_pBaseDrag = NULL;
		m_nDragX = -100;
		m_nDragY = -100;
	}
	CUIIcon* GetDragIcon()		{ return m_pIconDrag; }
	CUIBase* GetDragBase()		{ return m_pBaseDrag; }

	// MessageBox
	BOOL	CreateMessageBox( CUIMsgBox_Info &rMsgBoxInfo, int nPosX = -1, int nPosY = -1 );
	void	CloseMessageBox( int nCommandCode );
	BOOL	DoesMessageBoxExist( int nCommandCode );

	void	CreateMessageBoxL( CTString &strTitle, int nWhichUI, int nCommandCode,
								int nPosX = -1, int nPosY = -1 );
	void	AddMessageBoxLString( int nCommandCode, BOOL bDesc, CTString &strMessage, int iValue = -1, const COLOR colDesc = 0xF2F2F2FF, CTString strPrefix = "o" );
	void	CloseMessageBoxL( int nCommandCode );
	BOOL	DoesMessageBoxLExist( int nCommandCode );
	CUIMessageBox *GetMessageBox( int nCommandCode );

	// [090909 sora]
	CUIMessageBoxL *GetMessageBoxL( int nCommandCode );

	// WSS_SELECTIVE_UI_FUCNTION 2007/08/15 
	// SELECTIVE UI
	void	CloseSelectiveUI( int nUIidx=-1 );
	BOOL	DoesUIExist( int nUIidx );
	BOOL	IsUIVisible(int nUIidx);


	// Message
	void	MsgProc( MSG *pMsg, BOOL *pbIMEProc );
	void	MsgSimpleProc( MSG *pMsg );
	void	MsgProcWeb(MSG *pMsg);

	// Command functions
	void	MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput );
	void	MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput ,CTString &strConfirm );
	void	MsgCommonCommand( int nCommandCode );
	
	//wooss 050805 add message command for select button
	void	MsgBoxBtnCommand( int nCommandCode, int btnNum, CTString &strInput );
	
	void	MsgBoxLCommand( int nCommandCode, int nResult ) {}

	// Misc functions
	CTString IntegerToCommaString(__int64 llCount);			// ������ ���� �ڸ��� ���е� ���� ��Ʈ������ ��ȯ
	CTString RealNumberToCommaString(double fCount, int nDecimalplaces = 1); // �Ǽ��� ���� �ڸ��� ���е� ��Ʈ������ ��ȯ
	void	FitOrderDecimalString(CTString &strCount, int nDecimalplaces);	// �Ҽ� �ڸ����� ���� �߶��ش�.
	void	InsertCommaToString( CTString &strCount );		// 1000 �ڸ��� ���� ���б�ȣ�� �־��ִ� �Լ�
	void	InsertCommaToStringEx( CTString &strRealNumber);// �Ǽ������� ó��
	COLOR	GetNasColor( SQUAD llNas );
	COLOR	GetNasColor( CTString strNas );
	CTString NasNumToWord( SQUAD llNas);

	void	CancelSkill( BOOL bLostTarget = TRUE, BOOL bSkillError=FALSE);
	void	Reset();
	void	LostTarget();

	void	SetVersion(int ver){m_LocalVersion = ver;};
	int		GetVersion(){return m_LocalVersion;};
	
	// wooss  060404 
	BOOL	IsPet(CItemData* pItemData);
	BOOL	IsWildPet(CItemData* pItemData);

	BOOL checkName(CTString strMsg, int chkType);

	CTString GetWeekToString( int nWeek )
	{
		if( nWeek < 0 || nWeek > 6 ) return CTString("None ");
		CTString strWeek[7] = { "��" , "��" , "ȭ" , "��" , "��" , "��" , "��" };	// ����
		return strWeek[nWeek];
	}

	// GetWeekToString �� ������ �ؽ�Ʈ�� �Ѱ� ���� �ʾƼ� �߰� 
	// added by sam 101220
	int GetWeekToStringIndex( int nWeek )
	{
		if( nWeek < 0 || nWeek > 6 ) return -1;
		switch ( nWeek )
		{
			case 0:
			{
				return 1930;
			}
			case 1:
			{
				return 1931;
			}
			case 2:
			{
				return 1932;
			}
			case 3:
			{
				return 1933;
			}
			case 4:
			{
				return 1934;
			}
			case 5:
			{
				return 1935;
			}
			case 6:
			{
				return 1936;
			}
			default:
			{
				return -1;				
			}
		}
	}
	
	FLOAT m_tmPrev;
//	std::vector<std::string> m_BadList;

	void SetTitleName( INDEX bFullScreen, int iScreenSizeI, int iScreenSizeJ );
	static void GetClassOfItem( CItemData* pItemData, CTString &strClass );
	DAMAGE_deque	m_qDamage;	
	UIRectUV		m_rtNumber[10];
	UIRect			m_rcNumber;
	
	UIRectUV		m_rtShowText[3];
	UIRect			m_rcShowText[3];
	
	BOOL			m_bDamageState; 
	
	int				m_nCoolTimeReductionRate;		//��ų��Ÿ�Ӱ��ҿɼ��� ���� ��� �԰� ���� �� ��Ÿ�� ���Һ���
	int				m_nNeedMPReductionRate;				//MP�Ҹ� ���� �ɼ��� ���� ��� �԰� ���� �� ���Һ���

	std::map<SLONG, CEffectGroup *> m_mapEG;
	
	void AddDamageData(ULONG ulDamage, SBYTE sbTargetFlag, ULONG ulClientIndex, BOOL bDamaged, BOOL bHealed = FALSE);
	void ShowDamage( ULONG ulClientIndex );
	
	void SetDamageState();	
	void ShowDamageList( FLOAT3D vPopupPos, FLOAT fPopupZ, ULONG ulClientIndex );
	
	void ClearDamageData();	
	
	void DrawNumber( int nX, int nY, int nNumber, COLOR colColor = 0xFFFFFFFF, FLOAT fRatio = 1.0f );
	void DrawText( int nX, int nY, SBYTE sbTargetFlag, COLOR colColor = 0xFFFFFFFF, FLOAT fRatio = 1.0f );

	void SetRareOption( CNetworkMessage *istr, CItems& rItem );
	void SetRareOption( UpdateClient::itemInfo* pInfo, CItems& rItem );
	
	int  GetCoolTimeReductionRate() { return m_nCoolTimeReductionRate; }
	int  GetNeedMPReductionRate() { return m_nNeedMPReductionRate; }
	void SetCoolTimeReductionRate(int CoolTimeReductionRate) { m_nCoolTimeReductionRate =CoolTimeReductionRate; }
	void SetNeedMPReductionRate(int nNeedMPReductionRate) { m_nNeedMPReductionRate =nNeedMPReductionRate; }
	void AddCoolTimeReductionRate(int Add) { m_nCoolTimeReductionRate += Add; }
	void AddNeedMPReductionRate(int Add) { m_nNeedMPReductionRate += Add; }

	// WSS_MINIGAME_070422 -------------------------------------->>
	// For multilined string
	void AddStringToList(CUIListBox* pListBox,CTString& tStr, INDEX iMaxChar, COLOR tColor =0xFFFFFFFF,INDEX ilistCol=0);

	int GetTargetColor(CEntity* entity, int color);

	// ----------------------------------------------------------<<

	BOOL IsEnemy( void* pTarget, TARGET_TYPE eType, BOOL bSearch =FALSE );
	void StartTargetEffect( SLONG slIndex, CEntity* penEntity, BOOL bEnemy );
	void StopTargetEffect( SLONG slIndex );

	// [sora] ������, RAID ����
	BOOL IsPlayInZone();	// �ν���Ʈ�� �÷��������� üũ
	BOOL IsInstantZone(int nZone);

	// Focus Check�� �Լ�. [11/23/2009 rumist]
	inline BOOL	IsFocusInAllEditbox() const { return CUIEditBox::IsFocusingEditBox(); }
	//inline const BOOL	IsFocusInAllEditbox() { return m_ebRefCntReturn.IsFocusedInAll() | m_mbRefCntReturn.IsFocusedInAll(); }
	BOOL IsFocusAllEditBox();	
	// [2010/08/26 : Sora] ADD_SUBJOB ���� ���� ���� �߰��Լ�
	CTString GetSubJobName( SLONG slSubJobCode );
	BOOL CheckSellerItem(  UI_TYPE uiType,  int flag );

	// [2010/09/17 : Sora] Player.es���� ���� �ý��� ȣ���
	void OpenSocketSystem(int iMobIndex, BOOL bHasQuest, FLOAT fX, FLOAT fZ );

	void InitCurInfoLines(void) { m_nCurInfoLines = 0; }
	void AddItemInfoString(CTString &strItemInfo, COLOR colItemInfo ,int maxLine, int maxChars);

	// added by sam 11/03/02 �������� ���� ��Ʈ�� �ѹ� ���̱�
	void ShowNoTranslationString ();
	void HideNoTranslationString ();
	void ToggleNoTranslationString ();
	// [2011/05/31 : Sora] Ŭ���̾�Ʈ ���� �ƴϰ� �ٸ������� ����� �� �ְ� Ȯ��
	void SetNoTranslationString( int transType, int index );
	void InitRenderTarget(int nWidth = DEF_DEFAULT_RT_WIDTH, int nHeight = DEF_DEFAULT_RT_HEIGHT);
	void DestroyRenderTarget();
	void HUD_SetItemModelData( INDEX iIndex );
	void HUD_DrawItemModel();
	void SetShowAni( BOOL bShow )	{	m_bShowAni = bShow;	}
	BOOL IsShowAni()	{	return m_bShowAni;	}
	CRenderTexture* GetRenderTarget()	{	return m_RenderTarget;	}

	BOOL CheckDratanWarInside(CCharacterTarget* pTarget);
	BOOL MyCheckDratanWarInside();

	void InteractionMsgBoxReject(); // ��û �޽��� �ڽ� �ź�

	//[sora] �̹��� ��Ʈ�� index ǥ��
	void SetNoTranslateFlag( eNoTransType transType, int* flag )
	{
		(*flag) |= transType;
	}

	BOOL IsNotTranslated( eNoTransType transType, int flag )
	{
		return transType & flag;
	}

	void Update( float fDeltaTime, float fElapsedTime );

protected:
	void RenderDamage( int nIndex, DAMAGE_deque::iterator iter, DOUBLE dDealyTime, int nX, int nY );
	void RenderNotice();	


public:
	void Render(CDrawPort* pDraw) 
	{
		CUIBase::Render( pDraw );

		CUIBase* pUI = CUIFocus::getSingleton()->getUI();
		if (pUI)
			pUI->Render(pDraw);

		CUITooltipMgr::getSingleton()->Render(pDraw);
	}
	virtual void OnRender(CDrawPort* pDraw) {};

	bool isCreateVisible(UI_TYPE type)
	{
		// ���ο� UI�� Hide ���
		if (m_apUIs[type] != NULL && 
			m_apUIs[type]->IsVisible() == TRUE || m_apUIs[type]->GetHide() == FALSE)
			return true;

		return false;
	}

	bool getCursorInGame()	{ return m_bCursorInGame; }
	std::string GetFullPath(std::string strFileName);
	int	GetPathCount()	{ return m_vecAdditionalPath.size();	}
	void ItemNameColorInI();
	COLOR GetItemNameColor(int nType) {	return m_colItemDropName[nType];	}
	void DropItemCallback();
	void SetGuildMark();
	
	bool DropProc();
#ifdef	VER_TEST
	void setIPString(const char* strIP) { 
		extern INDEX sam_bFullScreenActive;
		extern INDEX sam_iScreenSizeI;
		extern INDEX sam_iScreenSizeJ;

		m_strIP = strIP; 
		SetTitleName( sam_bFullScreenActive, sam_iScreenSizeI, sam_iScreenSizeJ );
	}

	bool GetDebugOutMode()			{ return m_bOutDebugString; }
	void SetDebugOutMode(bool bOut)	{ m_bOutDebugString = bOut; }
private:
	std::string m_strIP;

	bool m_bOutDebugString;	
#endif	// VER_TEST
private:
	COLOR m_colItemDropName[eDROPITEM_NAME_COL_MAX];
	CUIGuildMarkIcon*	m_pIconGuildMark;

#ifdef NOTICE_PICKUP_ITEM
public:

	struct CNoticePickupItem
	{
		LONG nIconTexId;
		UIRectUV rtIcon;
		CTString strText;
		LONG nBackWidth;
		SQUAD nTime;
	};

	CTextureData* m_pNoticePickupItemTexture;
	UIRectUV m_rtNoticePickupItemL;
	UIRectUV m_rtNoticePickupItemC;
	UIRectUV m_rtNoticePickupItemR;
	std::vector<CNoticePickupItem> m_vecNoticePickupItem;
	void AddNoticePickupItem(LONG nIndex, SQUAD nCount);
#endif
};

#define		UIMGR()		CUIManager::getSingleton()

// KALYDO
ENGINE_API extern  struct PlayerControls pctlCurrent;



inline ENGINE_API CTString _SFunc( int x );

//#define KEY_SHOW_STRING_INDEX
// �̹��� ã�Ƴ��� [10/13/2011 rumist]
#define _S(x,comment) _SFunc(x)
#define _S2(x,str1,comment) CUIManager::getSingleton()->GetString(x,str1)
#define _S3(x,str1,str2,comment) CUIManager::getSingleton()->GetString(x,str1,str2)
#define _s(str) CTString(str)

// �ӽ÷� �߰��� Define
// getSingleton���� singleton object�� ���� �����Ͽ� �ް� �Ǿ�, comment�� ã�� �� ���� �ȴ�.
// ���� ���� ��ü�� �����ϴ� define �Լ��� �����Ͽ���.
#define _SMgr(m, x, comment) m->GetString(x)
#define _S2Mgr(m, x, str1, comment) m->GetString(x, str1)
#define _S3Mgr(m, x, str1, str2, comment) m->GetString(x, str1, str2)

#endif	// UIMANAGER_H_

