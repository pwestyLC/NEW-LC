#ifndef		UI_WINDOW_DECLARE_H_
#define		UI_WINDOW_DECLARE_H_
#include <Common/CommonDef.h>
#include <Engine/Interface/UIBase.h>
// User interface types
enum UI_TYPE
{
	UI_NONE					= -1,
	UI_TYPE_START			= 0,

	UI_ALWAYS_SHOW_START	= UI_TYPE_START,				// �׻� ���̴� �������̽� |<--
	UI_PLAYERINFO			= UI_ALWAYS_SHOW_START,
	//UI_CHATTING,
	UI_CHATTING_NEW,
	UI_PET_TARGETINFO,
	UI_WILDPET_TARGETINFO,
	UI_QUICKSLOT,
	UI_SUMMON_START,
	UI_SUMMON_FIRST	= UI_SUMMON_START,
	UI_SUMMON_SECOND,
	UI_SUMMON_END	= UI_SUMMON_SECOND,
	UI_RADAR,
	UI_NOTICE,
	UI_TARGETINFO,	
	UI_HELP_ICON,	
#ifdef USE_UIAD
	UI_AD,													// ���� ���� ǥ��(for japan)
#endif
	UI_SIMPLE_PLAYER_INFO,
	UI_ALWAYS_SHOW_END,										// �׻� ���̴� �������̽�     -->|

	UI_SELECTIVE_SHOW_START	= UI_ALWAYS_SHOW_END,			// ���������� ���̴� �������̽� |<--
	UI_INVENTORY			= UI_SELECTIVE_SHOW_START,
	UI_INVEN_SLOT1,
	UI_INVEN_SLOT2,
	UI_INVEN_SLOT3,
	UI_INVEN_CASH1,
	UI_INVEN_CASH2,
	UI_INVEN_CASH3,
	UI_INVEN_CASH4,
	UI_INVEN_CASH5,
	UI_INVEN_CASH6,
	UI_QUICKSLOT2,
	UI_QUICKSLOT3,
	UI_QUICKSLOT4,
	UI_CHARACTERINFO,
	UI_EXCHANGE,
	UI_PORTAL,
	UI_SHOP,
	UI_SHOP_UI,
	UI_PERSONALSHOP,
	UI_CASHEXCHANGE,
	UI_WARE_HOUSE,
	UI_SECURITY,
	UI_SYSTEMMENU,
	UI_PARTY,
	UI_EXPEDITION,
	UI_EXPEDITION_VIEW,
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	UI_EXPEDITION_PARTY_DUNGEON,//Cloud Expedition_Party_Dungeon
#endif
	UI_GUILD,
	UI_HELP,
	UI_HELP3,
	UI_CRAFT,
#ifdef PASSIVE_SYSTEM
	UI_PASSIVE_SYSTEM_RST,
#endif
	UI_SINGLE_BATTLE,
	UI_GUILD_BATTLE, // Date : 2005-03-17,   By Lee Ki-hwan
	UI_SIEGE_WARFARE,	// ������ // Date : 2005-06-27(���� 10:46:11), By Lee Ki-hwan
	UI_SIEGE_WARFARE_NEW,	// �Ű����� // WSS_DRATAN_SIEGEWARFARE 070727
	UI_GUILDWARPORTAL,
//	UI_BILLING,			// �븸 ����ȭ(����) Date : 2005-04-30(���� 3:55:19), By Lee Ki-hwan
//	UI_BILL_ITEM,		// �븸 ����ȭ ������ ���� �ý���
	UI_MAP,
	UI_MAP_OPTION,
	UI_OPTION,
	UI_REFINE,
	UI_PROCESS,
	UI_PRODUCT,		// �̱�ȯ(12.7)	
	UI_MIX,
	UI_MIXNEW,		//  wooss 060523
	UI_COMPOUND,	// Date : 2005-01-12,   By Lee Ki-hwan
//	UI_REMISSION,
	UI_QUEST,
	UI_QUESTBOOK_LIST,
	UI_QUESTBOOK_COMPLETE,
	UI_QUEST_ACCEPT,
	UI_QUEST_RESTORE,
	UI_QUEST_VIEW,
	UI_SKILLLEARN,
	UI_SSKILLLEARN,
	UI_CHANGEWEAPON,
	UI_CHANGE_EQUIPMENT,
	UI_HELPER,
	UI_INITJOB,
	UI_TELEPORT,
	UI_MESSENGER,
	UI_WEBBOARD,
//	UI_QUIZ,
	UI_PET_TRAINING,
	UI_PETINFO,
	UI_RANKING,
    	#ifdef PRESTIGE_SYSTEM
	UI_PRESTIGE,
	#endif	
	UI_RANKING_SUMMON,
	UI_RANKING_REBORN,
	UI_RANKING_PVP,
	UI_GAMBLE,
	UI_PROCESSNPC,
	UI_SELECTRESOURCE,
//	UI_CASH_SHOP,			//wooss 050820 
	UI_GW_MIX, // ���� ������ ���� 
	UI_GUILDSTASH,	// ��� ���� ������ 
	UI_SELECTWORD,
	UI_SELECTLIST,	// ģ��ã���̺�Ʈ 060126
	UI_PET_ITEM_MIX,	// �� ������ ����( ����ũ ������ ���� )
	UI_PETFREE,			// �� ���� ����
	UI_QUIZEVENT,		// O.X QUIZ EVENT
	UI_PARTYAUTO,
	UI_PARTYAUTO_REG,	// �����Ī ���â
	UI_PARTYAUTO_REG_PB,// ��Ƽ���� ���â
	UI_PARTYAUTO_INVITE_LIST,	// �ʴ밡�� ����Ʈ
	UI_PARTYAUTO_PARTY_LIST,
	UI_INSECTCOLLECT,		// ���� ä�� �ڽ� 
	UI_BINGOBOX,		// ���귯�� �̺�Ʈ ���ڷ� ä�� �ڽ�
	UI_NPCHELP,			// NPC �ȳ� �ý���
	UI_SIMPLE_POP,		// [KH_070419] ���� �˾� ���� �߰�
	UI_MINIGAME,		// WSS_MINIGAME 070418
	UI_FLOWERTREE,		// �ɳ��� �������̽�	

	UI_GUILD_NOTICE,	// WSS_NEW_GUILD_SYSTEM 070715 
	UI_MONSTER_COMBO,	// ttos_080116 : ���� �޺�
	UI_WILDPET_INFO,	// ���� �� Info
	UI_AUCTION,			// �ŷ�����
	UI_TATOO,			// [090709: selo] �� ���� �ý���
	UI_PRODUCT2,		// ������ ����
	UI_PRODUCTNPC,		// ������ ���� NPC
	UI_NPC_AFFINITYINFO,	// [5/29/2009 rumist] npc affinity. ( npc ģȭ��. ) 
	UI_ITEMPRODUCT,		// ģȭ�� UI���� ���� UI �и� [2/25/2013 Ranma]
	UI_NPC_AFFINITY,	// [6/3/2009 rumist] npc affinity donation. ���. 
	UI_RESURRECTION,	// resurrection ui [11/2/2009 rumist]
	UI_CHAT_FILTER,		//[ttos_2009_7_17]: CHARATER_CHAT_FILTER ĳ���� ä�� ����
	UI_NPC_SCROLL,		// connie [2009/9/9] - NPC ã��
	UI_NICKNAME,		//[12/9/2009 kiny] ȣĪ 
	//	UI_TITLESYSTEM,		// Title System UI [11/20/2009 rumist]
	UI_SOCKETSYSTEM,	// Socket System UI [5/11/2010 rumist]
	UI_SOCKET_CREATE,
	UI_SOCKET_REMOVE_ALL, // SocketRemoveAll UI
	UI_SOCKET_REMOVE_SINGLE,
	UI_SOCKET_COMBINE,
	UI_JEWEL_COMPOS,
	UI_CUBERANK,
	UI_LACABALL,
	UI_CASHSHOP_EX,

	UI_MONSTER_MERCENARY,	// [2010/10/20 : Sora] ���� �뺴 ī��
	UI_SIEGE_WARFARE_INFO,	// [2010/11/01 : Sora] ���� ����

	UI_TREASURE_MAP,	// ��������
	UI_ROYALRUMBLE_ICON,			// royal rumble UI [5/11/2011 rumist]
	UI_NEWGUILDSTASH,				// renewal guild stash [6/16/2011 rumist]
	UI_GUILD_MARK,					// [sora] GUILD_MARK
	UI_REFORM_SYSTEM,				// reform system [8/28/2012 ����]
	UI_FORTUNE,						// [2013/02/13] sykim70 Fortune System
	UI_LCE_SYSTEM,
	UI_CALENDAR,
#ifdef	DAILY_LOGIN
	UI_DAILY_LOGIN,
#endif
#ifdef REZABOT
	UI_REZABOT,
#endif
	UI_RLGL,
	UI_CALENDAR_EVENT_INFO,
	UI_MYSTERYOUSBEAD,
	UI_PET_STASH_SELECT_EFFECT,
	UI_PET_STASH,
	UI_INVEN_CASH_BAG_BOX,
	UI_SKILL_NEW,
	UI_HARDCORE_WARNING,
	UI_MYSYNDICATE_INFO, // ���� ���� ü�� �� ����
#ifdef	DURABILITY
	UI_DURABILITY,
#endif	//	DURABILITY
	UI_TRADE,
	UI_GPS,
	UI_COMPASS,
	UI_MSGBOX_NUMERIC_ONLY,
	UI_ITEMCOLLECTION, 
	UI_PREMIUM_CHAR,
	UI_SIMPLE_PLAYER_MENU,
	UI_NEWS,
	UI_NEWS_WEB,
	UI_ITEM_COMPOSE,
	UI_HELP_WEB,
#ifdef QUICK_PANEL
	UI_QuickPanel,
#endif
	UI_CUSTOM_TITLE,
	UI_GS_USE_RECORD,	// ��� â�� ��� ���� ui
	UI_HELPER_GUARDIAN_INFO,
	UI_HELPER_STUDENT,
	UI_GUILD_BATTLE_MATCH,					// ������ ��Ī ����â
	UI_GUILD_BATTLE_MATCH_REG,				// ���â
	UI_GUILD_BATTLE_MATCH_CHALLENGE,		// ��ûâ
	UI_TRANSMOGRIFY,
	UI_EXTEND_MENU,
	UI_MAIL_BOX, // dethunter13
	UI_LETTER,
	UI_INVENTORY_OPTIONS,
	UI_DONATION_TIER_MINI,
	UI_DONATION_TIER,
	UI_BOX_OPEN,
	UI_PRS_REMOVE,
	UI_SEAL_COMPOSE,
	#ifdef BATTLE_PASS_SYSTEM
	UI_BATTLE_PASS,
	#endif
	UI_AUTOFUNC,											// Val add auto igni/pickup
	UI_PROMO_KEY_INPUT_RST,
	UI_LOOT_FILTER_MENU,
	UI_SELECTIVE_SHOW_END,

	UI_LOGIN_SHOW_START		= UI_SELECTIVE_SHOW_END,		// �α��� �������̽� |<--
	UI_LOGIN				= UI_LOGIN_SHOW_START,
	UI_CREATE_CHAR,
	UI_SERVER_SELECT,
	UI_CHARACTER_SELECT,
	UI_LOGIN_SHOW_END,										// �α��� �������̽�     -->|

	UI_MESSENGER_TALK_START = UI_LOGIN_SHOW_END,			// �޽��� ��ȭ ����     -->|
	UI_MESSENGER_TALK1		= UI_MESSENGER_TALK_START,
	UI_MESSENGER_TALK2,
	UI_MESSENGER_TALK3,
	UI_MESSENGER_TALK4,
	UI_MESSENGER_TALK5,
	UI_MESSENGER_TALK6,
	UI_MESSENGER_TALK7,
	UI_MESSENGER_TALK8,
	UI_MESSENGER_TALK9,
	UI_MESSENGER_TALK10,
	UI_MESSENGER_TALK_END,									// �޽��� ��ȭ ���� |<--

	UI_MESSAGEBOX_START		= UI_MESSENGER_TALK_END,		// �޼��� �ڽ� �������̽� |<--
	UI_MESSAGEBOX1			= UI_MESSAGEBOX_START,
	UI_MESSAGEBOX2,
	UI_MESSAGEBOX3,
	UI_MESSAGEBOX4,
	UI_MESSAGEBOX5,
	UI_MESSAGEBOX6,
	UI_MESSAGEBOX7,
	UI_MESSAGEBOX8,
	UI_MESSAGEBOX9,
	UI_MESSAGEBOX10,
	UI_MESSAGEBOX11,
	UI_MESSAGEBOX12,
	UI_MESSAGEBOX13,
	UI_MESSAGEBOX14,
	UI_MESSAGEBOX15,
	UI_MESSAGEBOX_END,										// �޼��� �ڽ� �������̽�     -->|

	UI_MESSAGEBOXL_START	= UI_MESSAGEBOX_END,			// ��ȭ ���� �������̽� |<--
	UI_MESSAGEBOXL1			= UI_MESSAGEBOXL_START,
	UI_MESSAGEBOXL2,
	UI_MESSAGEBOXL3,
	UI_MESSAGEBOXL4,
	UI_MESSAGEBOXL5,
	UI_MESSAGEBOXL_END,										// ��ȭ ���� �������̽�     -->|

	UI_RANKINGVIEW_START	= UI_MESSAGEBOXL_END,
	UI_RANKINGVIEW_RENEWAL,
	UI_RANKINGVIEW_END,

	UI_TYPE_END = UI_RANKINGVIEW_END,
};

class CUIBase;
class CUITextBox;
class CUIWindow;

class CAffinityUI;
class CAffinityInfoUI;
class CUIAuctionNew;
class CBingoBoxUI;
class CUICalendar;
#ifdef DAILY_LOGIN
class DailyLogin;
#endif
#ifdef REZABOT
class ReZaBotUI;
#endif
class RLGL;
class CUICalendarEventInfo;
class CUICashShopEX;
class CCashExchangeUI;
class CUIChangeWeapon;
class CUIChangeEquipment;
class CUICharacterCreateNew;
class CUICharacterInfo;
class CUICharacterSelect;
class CUICharServerMove;
class CChatBlockListUI;
//class CUIChatting;
class CUIChildInvenSlot;
class CUIChildQuickSlot;
class CInsectCollectUI;
class CUICompass;
class CCompoundUI;
class CUIDurability;
class CExchangeUI;
class CExtendMenuUI;
class CUIExpressSystem;
class CUIExpManage;
class CUIFlowerTree;
class CUIGamble;
class CUIGPS;
class CUIGuild;
class CUIGuildBattle;
class GuildBattleMatchChallengeUI;
class GuildBattleMatchRegUI;
class GuildBattleMatchUI;
class CUIGuildMark;
class CUIGuildNotice;
class CGuildStashUI;
class CUIGuildWarPortal;
class CGuildWarMixUI;
class CUIHardCoreWarning;
class CUIHelp;
class CUIHelp3;
class CHelperUI;
class CUIHelpIcon;
class CUIInitJob;
class CUIInvenCashBag;
class CUIInvenCashBagBox;
class CUIInventory;
class CItemProductUI;
class CUILacaball;
class CUILootFilterMenu;
class CUILoginNew;
class CUIMap;
class CUIMapOption;
class CUIMessageBox;
class CUIMessageBoxL;
class CUIMessenger;
class CUIMinigame;
class CUIMix;
class CUIMixNew;
class CUIMonsterCombo;
class CUIMonsterMercenary;
class CUIMsgBoxNumericOnly;
class CUIMysteriousBead;
class CUIMySyndicateInfo;
class CUINewGuildStash;
class CUINickName;
class CUINoticeNew;
class CUINpcHelp;
class CUINpcScroll;
class CUIOption;
class CUIOXQuizEvent;
class CUIParty;
class CUIPartyAuto;
class CUIPartyAutoReg;
class CUIPartyAutoRegBoss;
class CUIPartyAutoInviteList;
class CUIPartyAutoPartyList;
class CUIPersonalshopNew;
class CPetFreeUI;
class CUIPetInfo;
class CUIPetItemMix;
class CPetItemMixUI;
class CUIPetStash;
class CUIPetStashSelectEffect;
class CPetTargetUI;
class CPetTrainingUI;
class CUIPlayerInfo;
class CUIPortal;
class CUIProcess;
class CUIProcessNPC;
class CUIProduct;
class CUIProduct2;
class CUIProductNPC;
class CUIQuest;
class CUIQuestBook;
class CUIQuestAccept;
class CUIQuestComplete;
class CUIQuestRestore;
class CUIQuestView;
class CUIQuickSlot;
class CUIRadar;
class CUIRanking;
class CUIRankingSummon;
class CUIRankingReborn;
class CUIRankingPvP;
class CUIRankingSystem;
class CUIRefine;
class CUIReformSystem;
class CUIResurrectionMsgBox;
class CUIRoyalRumbleIcon;
class CUISecurity;
class CUISelectList;
class CUISelectResource;
class CUISelectWord;
class CUIServerSelect;
class CUIShop;
class CShopUI;
class CUISiegeWarfare;
class CUISiegeWarfareInfo;
class CUISiegeWarfareNew;
class CUISimplePop;
class CSingleBattleUI;
class CUISkillLearn;
class CSSkillLearnUI;
class CUISkillNew;
class CUISocketSystem;
class CSocketRemoveAllUI;
class CSocketRemoveSingleUI;
class CSocketCreateUI;
class CSocketCombineUI;
class CJewelComposUI;
class CSummonUI;
class CSystemMenuUI;
class CTalkUI;
class CTargetInfoUI;
class CTatooUI;
class CTeleportUI;
class CUITrade;
class CTransmogrifyUI;
class CTreasureMapUI;
class CUIViewDetail;
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
class CUIExpeditionPartyDungeon;//Cloud Expedition_Party_Dungeon
#endif
class CWareHouseUI;
class CUIWebBoard;
class CUIWildPetInfo;
class CWildPetInfoUI;
class CWildPetTargetUI;
class CItemCollectionUI;
class CPremiumCharUI;
class CSimplePlayerInfoUI;
class CSimplePlayerMenuUI;
class CChattingUI;
class CNewsUI;
class CNewsWebUI;
class CItemComposeUI;
class CHelpWebUI;
#ifdef QUICK_PANEL
class CUIQuickPanel;
#endif
class CCustomTitleUI;
class CCubeRankingUI;
class CGuildStashUseRecordUI;
class CUICraft;				// RomeoST [add 13.12.2016] //Craft system
class CUIPassiveSystemRST;
class CHelper_GuardianInfoUI;
class CHelper_StudentUI;
class CUIMailBox;
class CUILetter;
class CUIInventoryOptions;
class CUIDonationTierMini;
class CUIDonationTier;
class CBoxOpenUI;
class CPRSRemoveUI;
class CSealComposeUI;
#ifdef BATTLE_PASS_SYSTEM
class CUIBattlePass;
#endif
#ifdef PRESTIGE_SYSTEM
class CUIPrestige;
#endif
class CAutoFuncUI; // Val add auto igni/pickup
class CUIPromoKeyInputRST;


class CUIWindowDeclare : public CUIBase
{
public:

#ifdef	USE_UIAD
	CUIAD*					GetAD() { return (CUIAD*)m_apUIs[UI_AD]; }
#endif	// USE_UIAD
	CAffinityUI*			GetAffinity()	{ return (CAffinityUI*)m_apUIs[UI_NPC_AFFINITY];}
	CAffinityInfoUI*		GetAffinityInfo() { return (CAffinityInfoUI*)m_apUIs[UI_NPC_AFFINITYINFO];	}
	CUIAuctionNew*			GetAuction() { return (CUIAuctionNew*)m_apUIs[UI_AUCTION]; }
	CBingoBoxUI*			GetBingoBox() { return (CBingoBoxUI*)m_apUIs[UI_BINGOBOX]; } // ���ڷ� ���� ����
	CUICalendar*			GetCalendar() { return (CUICalendar*)m_apUIs[UI_CALENDAR]; }
#ifdef DAILY_LOGIN
	DailyLogin* GetRezaDailyLogin() { return (DailyLogin*)m_apUIs[UI_DAILY_LOGIN]; }
#endif
#ifdef REZABOT
	ReZaBotUI*				GetReZaBotUI() { return(ReZaBotUI*)m_apUIs[UI_REZABOT]; }
#endif
	RLGL*					GetRLGL() { return (RLGL*)m_apUIs[UI_RLGL]; }
    CUICalendarEventInfo*	GetCalendarEventInfo()	{ return (CUICalendarEventInfo*)m_apUIs[UI_CALENDAR_EVENT_INFO];	}
    CUICashShopEX*			GetCashShopEX() { return (CUICashShopEX*) m_apUIs[UI_CASHSHOP_EX]; }
    CCashExchangeUI*		GetCashExchange() { return (CCashExchangeUI*)m_apUIs[UI_CASHEXCHANGE]; }
    CUIChangeWeapon*		GetChangeWeapon() { return (CUIChangeWeapon*)m_apUIs[UI_CHANGEWEAPON]; }
	CUIChangeEquipment*		GetChangeEquipment() { return (CUIChangeEquipment*)m_apUIs[UI_CHANGE_EQUIPMENT]; }
    CUICharacterCreateNew*	GetCreateChar() { return (CUICharacterCreateNew*)m_apUIs[UI_CREATE_CHAR]; }
    CUICharacterInfo*		GetCharacterInfo() { return (CUICharacterInfo*)m_apUIs[UI_CHARACTERINFO]; }
    CUICharacterSelect*		GetCharacterSelect()	{ return (CUICharacterSelect*)m_apUIs[UI_CHARACTER_SELECT];	}
    CChatBlockListUI*		GetChatFilter()	{ return (CChatBlockListUI*)m_apUIs[UI_CHAT_FILTER]; }
    //CUIChatting*			GetChatting() { return (CUIChatting*)m_apUIs[UI_CHATTING]; }
    CInsectCollectUI*		GetInsectCollect() { return (CInsectCollectUI*)m_apUIs[UI_INSECTCOLLECT]; } // ���� ä������
	CUICompass*				GetCompass()	{ return (CUICompass*)m_apUIs[UI_COMPASS]; }
	CCompoundUI*			GetCompound() { return (CCompoundUI*)m_apUIs[UI_COMPOUND]; }
    CCubeRankingUI*			GetCubeRank()	{ return (CCubeRankingUI*) m_apUIs[UI_CUBERANK]; }
#ifdef	DURABILITY
    CUIDurability*			GetDurability()		{ return (CUIDurability*)m_apUIs[UI_DURABILITY]; }
#endif	// DURABILITY
    CExchangeUI*			GetExchange() { return (CExchangeUI*)m_apUIs[UI_EXCHANGE]; }
    CUIExpressSystem*		GetLCESystem()	{ return (CUIExpressSystem*) m_apUIs[UI_LCE_SYSTEM];		}
	CUIExpManage*			GetExpedition() {return (CUIExpManage*)m_apUIs[UI_EXPEDITION]; }
    CUIFlowerTree*			GetFlowerTree() {return (CUIFlowerTree*)m_apUIs[UI_FLOWERTREE];} // �ɳ��� �������̽�
    CUIGamble*				GetGamble() { return (CUIGamble*)m_apUIs[UI_GAMBLE]; }	
	CUIGPS*					GetGPS()	{ return (CUIGPS*)m_apUIs[UI_GPS]; }
	CUIGuild*				GetGuild() { return (CUIGuild*)m_apUIs[UI_GUILD]; }
    CUIGuildBattle*			GetGuildBattle() { return (CUIGuildBattle*)m_apUIs[UI_GUILD_BATTLE]; }
    CUIGuildMark*			GetGuildMark()			{ return (CUIGuildMark*) m_apUIs[UI_GUILD_MARK]; }
    CUIGuildNotice*			GetGuildNotice() {return (CUIGuildNotice*)m_apUIs[UI_GUILD_NOTICE];}// WSS_NEW_GUILD_SYSTEM 070715
	CGuildStashUI*			GetGuildStash() { return (CGuildStashUI*)m_apUIs[UI_GUILDSTASH]; }
    CUIGuildWarPortal*		GetGuildWarPortal() { return (CUIGuildWarPortal*)m_apUIs[UI_GUILDWARPORTAL]; }
    CGuildWarMixUI*			GetGWMix() { return (CGuildWarMixUI*)m_apUIs[UI_GW_MIX]; }
    CUIHardCoreWarning*		GetHardCoreWarning()		{ return (CUIHardCoreWarning*)m_apUIs[UI_HARDCORE_WARNING]; }
    CUIHelp*				GetHelp() { return (CUIHelp*)m_apUIs[UI_HELP]; }
    CUIHelp3*				GetHelp3() { return (CUIHelp3*)m_apUIs[UI_HELP3]; }
    CHelperUI*				GetHelper() { return (CHelperUI*)m_apUIs[UI_HELPER]; }
    CUIHelpIcon*			GetHelpIcon() { return (CUIHelpIcon*)m_apUIs[UI_HELP_ICON]; }		// ���� �ý��� �߰�
    CUIInitJob*				GetInitJob() { return (CUIInitJob*)m_apUIs[UI_INITJOB]; }
    CUIInvenCashBagBox*		GetInvenCashBagBox()		{ return (CUIInvenCashBagBox*)m_apUIs[UI_INVEN_CASH_BAG_BOX]; }
    CUIInventory*			GetInventory() { return (CUIInventory*)m_apUIs[UI_INVENTORY]; }
    CItemProductUI*			GetItemProduct() { return (CItemProductUI*)m_apUIs[UI_ITEMPRODUCT];	}
    CUILacaball*			GetLacaBall()	{ return (CUILacaball*)(m_apUIs[UI_LACABALL]);	}
    CUILootFilterMenu*		GetLootFilterMenu() { return (CUILootFilterMenu*)m_apUIs[UI_LOOT_FILTER_MENU]; }
    CUILoginNew*			GetLogin() { return (CUILoginNew*)m_apUIs[UI_LOGIN]; }
    CUIMap*					GetMap() { return (CUIMap*)m_apUIs[UI_MAP]; }
	CUIMapOption*			GetMapOption() { return (CUIMapOption*)m_apUIs[UI_MAP_OPTION]; }
	CUIMsgBoxNumericOnly*	GetMsgBoxNumOnly()		{ return (CUIMsgBoxNumericOnly*)m_apUIs[UI_MSGBOX_NUMERIC_ONLY]; }
    CUIMessenger*			GetMessenger() { return (CUIMessenger*)m_apUIs[UI_MESSENGER]; }
    CUIMinigame*			GetMinigame() {return (CUIMinigame*)m_apUIs[UI_MINIGAME];} //WSS_MINIGAME 070418
    CUIMix*					GetMix() { return (CUIMix*)m_apUIs[UI_MIX]; }
    CUIMixNew*				GetMixNew() { return (CUIMixNew*)m_apUIs[UI_MIXNEW]; }
    CUIMonsterCombo*		GetCombo() {return (CUIMonsterCombo*)m_apUIs[UI_MONSTER_COMBO]; }
    CUIMonsterMercenary*	GetMonsterMercenary()	{ return (CUIMonsterMercenary*) m_apUIs[UI_MONSTER_MERCENARY]; }
    CUIMysteriousBead*		GetMysteryousBead()	{ return (CUIMysteriousBead*)m_apUIs[UI_MYSTERYOUSBEAD]; }
    CUIMySyndicateInfo*		GetMySyndiInfo()		{ return (CUIMySyndicateInfo*)m_apUIs[UI_MYSYNDICATE_INFO]; }
    CUINewGuildStash*		GetGuildStash_N()		{ return (CUINewGuildStash*) m_apUIs[UI_NEWGUILDSTASH];			}
    CUINickName*			GetNickName() { return (CUINickName*) m_apUIs[UI_NICKNAME]; }
    CUINoticeNew*			GetNotice() { return (CUINoticeNew*)m_apUIs[UI_NOTICE]; }
    CUINpcHelp*				GetNpcHelp() {return (CUINpcHelp*)m_apUIs[UI_NPCHELP];} //Npc �ȳ��ý���
    CUINpcScroll*			GetNpcScroll() { return (CUINpcScroll*) m_apUIs[UI_NPC_SCROLL]; }
    CUIOption*				GetOption() { return (CUIOption*)m_apUIs[UI_OPTION]; }
    CUIOXQuizEvent*			GetOXQuizEvent() { return (CUIOXQuizEvent*)m_apUIs[UI_QUIZEVENT]; } // O.X ���� �̺�Ʈ
    CUIParty*				GetParty() { return (CUIParty*)m_apUIs[UI_PARTY]; }
    CUIPartyAuto*			GetPartyAuto() { return (CUIPartyAuto*)m_apUIs[UI_PARTYAUTO]; } // party auto matching
	CUIPartyAutoReg*		GetPartyAutoReg() { return (CUIPartyAutoReg*)m_apUIs[UI_PARTYAUTO_REG]; }
	CUIPartyAutoRegBoss*	GetPartyAutoRegBoss() { return (CUIPartyAutoRegBoss*)m_apUIs[UI_PARTYAUTO_REG_PB]; }
	CUIPartyAutoInviteList*	GetPartyAutoInvite() { return (CUIPartyAutoInviteList*)m_apUIs[UI_PARTYAUTO_INVITE_LIST]; }
	CUIPartyAutoPartyList*	GetPartyAutoParty() { return (CUIPartyAutoPartyList*)m_apUIs[UI_PARTYAUTO_PARTY_LIST]; }
    CUIPersonalshopNew*		GetPersonalShop() { return (CUIPersonalshopNew*)m_apUIs[UI_PERSONALSHOP]; }
    CPetFreeUI*				GetPetFree()	{ return (CPetFreeUI*)m_apUIs[UI_PETFREE]; } // �� ���� ����
    CUIPetInfo*				GetPetInfo() { return (CUIPetInfo*)m_apUIs[UI_PETINFO]; }
	CPetItemMixUI*			GetPetItemMixUI() { return (CPetItemMixUI*)m_apUIs[UI_PET_ITEM_MIX]; } // ������� ����( ����ũ )
    CUIPetStash*			GetPetStash()				{ return (CUIPetStash*)m_apUIs[UI_PET_STASH]; }
    CUIPetStashSelectEffect*	GetPetStashSelectEffect()	{ return (CUIPetStashSelectEffect*)m_apUIs[UI_PET_STASH_SELECT_EFFECT]; }
	CPetTargetUI*			GetPetTargetUI() { return (CPetTargetUI*)m_apUIs[UI_PET_TARGETINFO]; }
	CPetTrainingUI*			GetPetTrainingUI() { return (CPetTrainingUI*)m_apUIs[UI_PET_TRAINING]; }
    CUIPlayerInfo*			GetPlayerInfo() { return (CUIPlayerInfo*)m_apUIs[UI_PLAYERINFO]; }
    CUIPortal*				GetPortal() { return (CUIPortal*)m_apUIs[UI_PORTAL]; }
#ifdef QUICK_PANEL
	CUIQuickPanel* GetQuickPanel() { return (CUIQuickPanel*)m_apUIs[UI_QuickPanel]; }
#endif

    CUIProcess*				GetProcess() { return (CUIProcess*)m_apUIs[UI_PROCESS]; }
    CUIProcessNPC*			GetProcessNPC() { return (CUIProcessNPC*)m_apUIs[UI_PROCESSNPC]; }
    CUIProduct*				GetProduct() { return (CUIProduct*)m_apUIs[UI_PRODUCT]; }
    CUIProduct2*			GetProduct2()	{return (CUIProduct2*)m_apUIs[UI_PRODUCT2]; }
    CUIProductNPC*			GetProductNPC() { return (CUIProductNPC*)m_apUIs[UI_PRODUCTNPC]; }
    CUIQuest*				GetQuest() { return (CUIQuest*)m_apUIs[UI_QUEST]; }
	CUIQuestBook*			GetQuestBookList() { return (CUIQuestBook *)m_apUIs[UI_QUESTBOOK_LIST]; }
	CUIQuestComplete*		GetQuestBookComplete() { return (CUIQuestComplete*)m_apUIs[UI_QUESTBOOK_COMPLETE]; }
	CUIQuestAccept*			GetQuestAccept() { return (CUIQuestAccept *)m_apUIs[UI_QUEST_ACCEPT]; }
	CUIQuestRestore*		GetQuestRestore() { return (CUIQuestRestore *)m_apUIs[UI_QUEST_RESTORE]; }
	CUIQuestView*			GetQuestView() { return (CUIQuestView *)m_apUIs[UI_QUEST_VIEW]; }
    CUIQuickSlot*			GetQuickSlot() { return (CUIQuickSlot*)m_apUIs[UI_QUICKSLOT]; }
    CUIRadar*				GetRadar() { return (CUIRadar*)m_apUIs[UI_RADAR]; }
    CUIRanking*				GetRanking() { return (CUIRanking*)m_apUIs[UI_RANKING]; }
    #ifdef PRESTIGE_SYSTEM
	CUIPrestige*			GetPrestigeUI()		{ return (CUIPrestige*)m_apUIs[UI_PRESTIGE]; }
#endif
	CUIRankingSummon*		GetRankingSummon() { return (CUIRankingSummon*)m_apUIs[UI_RANKING_SUMMON]; }
	CUIRankingReborn*		GetRankingReborn() { return (CUIRankingReborn*)m_apUIs[UI_RANKING_REBORN]; }
	CUIRankingPvP*			GetRankingPvP() { return (CUIRankingPvP*)m_apUIs[UI_RANKING_PVP]; }
    CUIRankingSystem*		GetRankingViewEx()		{ return (CUIRankingSystem*)m_apUIs[UI_RANKINGVIEW_RENEWAL]; }
    CUIRefine*				GetRefine() { return (CUIRefine*)m_apUIs[UI_REFINE]; }
    CUIReformSystem*		GetReformSystem()		{ return (CUIReformSystem*) m_apUIs[UI_REFORM_SYSTEM];		}
    CUIResurrectionMsgBox*	GetResurrectionMsgBox()	{ return (CUIResurrectionMsgBox*)m_apUIs[UI_RESURRECTION];	}
    CUIRoyalRumbleIcon*		GetRoyalRumbleIcon()	{ return (CUIRoyalRumbleIcon*) m_apUIs[UI_ROYALRUMBLE_ICON];	}
    CUISecurity*			GetSecurity() { return (CUISecurity*)m_apUIs[UI_SECURITY]; }
    CUISelectList*			GetSelectList() { return (CUISelectList*)m_apUIs[UI_SELECTLIST]; } // ģ��ã�� �̺�Ʈ 060126
    CUISelectResource*		GetSelectResource() { return (CUISelectResource*)m_apUIs[UI_SELECTRESOURCE]; }
    CUISelectWord*			GetSelectWord() { return (CUISelectWord*)m_apUIs[UI_SELECTWORD]; }
    CUIServerSelect*		GetServerSelect()	{ return (CUIServerSelect*)m_apUIs[UI_SERVER_SELECT];	}
    CUIShop*				GetShop() { return (CUIShop*)m_apUIs[UI_SHOP]; }
	CShopUI*				GetShopUI() { return (CShopUI*)m_apUIs[UI_SHOP_UI]; }
    CUISiegeWarfare*		GetSiegeWarfare() { return (CUISiegeWarfare*)m_apUIs[UI_SIEGE_WARFARE]; }
    CUISiegeWarfareInfo*	GetSiegeWarfareInfo()	{ return (CUISiegeWarfareInfo*) m_apUIs[UI_SIEGE_WARFARE_INFO]; }
    CUISiegeWarfareNew*		GetSiegeWarfareNew() { return (CUISiegeWarfareNew*)m_apUIs[UI_SIEGE_WARFARE_NEW]; }  // WSS_DRATAN_SIEGEWARFARE 070727
    CUISimplePop*			GetSimplePop() { return (CUISimplePop*)m_apUIs[UI_SIMPLE_POP]; }	// [KH_070419] ���� �˾� ���� �߰�
	CSingleBattleUI*		GetSingleBattle() { return (CSingleBattleUI*)m_apUIs[UI_SINGLE_BATTLE]; }
    CUISkillLearn*			GetSkillLearn() { return (CUISkillLearn*)m_apUIs[UI_SKILLLEARN]; }
	CSSkillLearnUI*			GetSSkillLearn() { return (CSSkillLearnUI*)m_apUIs[UI_SSKILLLEARN]; }
    CUISkillNew*			GetSkillNew()				{ return (CUISkillNew*)m_apUIs[UI_SKILL_NEW]; }
    CUISocketSystem*		GetSocketSystem()	{ return (CUISocketSystem*) m_apUIs[UI_SOCKETSYSTEM]; }
	CSocketRemoveAllUI*		GetSocketRemoveAll()	{ return (CSocketRemoveAllUI*) m_apUIs[UI_SOCKET_REMOVE_ALL]; }
	CSocketRemoveSingleUI*	GetSocketRemoveSingle()	{ return (CSocketRemoveSingleUI*) m_apUIs[UI_SOCKET_REMOVE_SINGLE]; }
	CSocketCreateUI*		GetSocketCreate()	{ return (CSocketCreateUI*) m_apUIs[UI_SOCKET_CREATE]; }
	CSocketCombineUI*		GetSocketCombine()	{ return (CSocketCombineUI*) m_apUIs[UI_SOCKET_COMBINE]; }
	CJewelComposUI*			GetSocketJewelCompos()	{ return (CJewelComposUI*) m_apUIs[UI_JEWEL_COMPOS]; }
	CSummonUI*				GetSummonFirst() { return (CSummonUI*)m_apUIs[UI_SUMMON_FIRST]; }
	CSummonUI*				GetSummonSecond() { return (CSummonUI*)m_apUIs[UI_SUMMON_SECOND]; }
    CSystemMenuUI*			GetSystemMenu() { return (CSystemMenuUI*)m_apUIs[UI_SYSTEMMENU]; }
    CTalkUI*				GetTalk(int iUIIndex) { return (CTalkUI*)m_apUIs[iUIIndex]; }
    CTargetInfoUI*			GetTargetInfoUI() { return (CTargetInfoUI*)m_apUIs[UI_TARGETINFO]; }
    CTatooUI*				GetTatoo() { return (CTatooUI*)m_apUIs[UI_TATOO]; }	// [090709: selo] �� ���� �ý���
    CTeleportUI*			GetTeleport() { return (CTeleportUI*)m_apUIs[UI_TELEPORT]; }
    CUITrade*				GetTrade()				{ return (CUITrade*)m_apUIs[UI_TRADE];	}
    CTreasureMapUI*			GetTreasureMapUI()		{ return (CTreasureMapUI*) m_apUIs[UI_TREASURE_MAP]; }
	CUIViewDetail*			GetExpeditionView() {return (CUIViewDetail*)m_apUIs[UI_EXPEDITION_VIEW]; }
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	CUIExpeditionPartyDungeon* GetExpeditionPartyDungeon() { return (CUIExpeditionPartyDungeon*)m_apUIs[UI_EXPEDITION_PARTY_DUNGEON]; }//Cloud Expedition_Party_Dungeon
#endif
	CWareHouseUI*			GetWareHouseUI() { return (CWareHouseUI*)m_apUIs[UI_WARE_HOUSE]; }
    CUIWebBoard*			GetWebBoard() { return (CUIWebBoard*)m_apUIs[UI_WEBBOARD]; }
   	CWildPetInfoUI*			GetWildPetInfoUI() { return (CWildPetInfoUI*)m_apUIs[UI_WILDPET_INFO]; }
    CWildPetTargetUI*		GetWildPetTargetInfo() { return (CWildPetTargetUI*)m_apUIs[UI_WILDPET_TARGETINFO]; }
	CItemCollectionUI*		GetItemCollection()		{ return (CItemCollectionUI*)m_apUIs[UI_ITEMCOLLECTION];	}
	CPremiumCharUI*			GetPremiumChar()		{ return (CPremiumCharUI*)m_apUIs[UI_PREMIUM_CHAR];	}
	CSimplePlayerInfoUI*	GetSimplePlayerInfo()	{ return (CSimplePlayerInfoUI*)m_apUIs[UI_SIMPLE_PLAYER_INFO];	}
	CSimplePlayerMenuUI*	GetSimplePlayerMenuUI()	{ return (CSimplePlayerMenuUI*)m_apUIs[UI_SIMPLE_PLAYER_MENU];	}
	CChattingUI*			GetChattingUI()			{ return (CChattingUI*)m_apUIs[UI_CHATTING_NEW];	}
	CNewsUI*				GetNewsUI()				{ return (CNewsUI*)m_apUIs[UI_NEWS];	}
	CNewsWebUI*				GetNewsWebUI()			{ return (CNewsWebUI*)m_apUIs[UI_NEWS_WEB];	}
	CItemComposeUI*			GetItemCompose()		{ return (CItemComposeUI*)m_apUIs[UI_ITEM_COMPOSE]; }
	CHelpWebUI*				GetHelpWebUI()			{ return (CHelpWebUI*)m_apUIs[UI_HELP_WEB];	}
	CCustomTitleUI*			GetCustomTitle()		{ return (CCustomTitleUI*)m_apUIs[UI_CUSTOM_TITLE]; }
    CUICraft*				GetCraft()				{ return (CUICraft*)m_apUIs[UI_CRAFT]; } //Craft system						// RomeoST [add 13.12.2016]
#ifdef PASSIVE_SYSTEM
	CUIPassiveSystemRST* GetPassiveSystem() { return (CUIPassiveSystemRST*)m_apUIs[UI_PASSIVE_SYSTEM_RST]; }
#endif
	CGuildStashUseRecordUI* GetGSUseRecord()		{ return (CGuildStashUseRecordUI*)m_apUIs[UI_GS_USE_RECORD];	}
	CHelper_GuardianInfoUI* GetHelper_GuardianInfo()	{ return (CHelper_GuardianInfoUI*)m_apUIs[UI_HELPER_GUARDIAN_INFO]; }
	CHelper_StudentUI*		GetHelper_Student()		{ return (CHelper_StudentUI*)m_apUIs[UI_HELPER_STUDENT];	}
	GuildBattleMatchChallengeUI*	GetGuildBattleMatchChallenge()	{ return (GuildBattleMatchChallengeUI*)m_apUIs[UI_GUILD_BATTLE_MATCH_CHALLENGE]; }
	GuildBattleMatchRegUI*			GetGuildBattleMatchReg()		{ return (GuildBattleMatchRegUI*)m_apUIs[UI_GUILD_BATTLE_MATCH_REG]; }
	GuildBattleMatchUI*				GetGuildBattleMatch()			{ return (GuildBattleMatchUI*)m_apUIs[UI_GUILD_BATTLE_MATCH]; }
	
	CTransmogrifyUI*				GetTransmogrifyUI()	{ return (CTransmogrifyUI*)m_apUIs[UI_TRANSMOGRIFY]; }
	CExtendMenuUI*					GetExtendMenuUI()	{ return (CExtendMenuUI*)m_apUIs[UI_EXTEND_MENU]; }
 	CUIMailBox*				GetMailBox()			{ return (CUIMailBox*)m_apUIs[UI_MAIL_BOX]; } // dethunter13
	CUILetter*				GetLetterBox()			{ return (CUILetter*)m_apUIs[UI_LETTER]; }
	CUIInventoryOptions*	GetInventoryOptions()	{ return (CUIInventoryOptions*)m_apUIs[UI_INVENTORY_OPTIONS]; }
	CUIDonationTierMini*	GetDonationTierMini()	{ return (CUIDonationTierMini*)m_apUIs[UI_DONATION_TIER_MINI]; }
	CUIDonationTier*		GetDonationTier()		{ return (CUIDonationTier*)m_apUIs[UI_DONATION_TIER]; }
	CBoxOpenUI*				GetBoxOpenUI()		{ return (CBoxOpenUI*)m_apUIs[UI_BOX_OPEN]; }
	CPRSRemoveUI*			GetPRSRemoveUI()		{ return (CPRSRemoveUI*)m_apUIs[UI_PRS_REMOVE]; }
	CSealComposeUI*			GetSealComposeUI()		{ return (CSealComposeUI*)m_apUIs[UI_SEAL_COMPOSE]; }
#ifdef BATTLE_PASS_SYSTEM
	CUIBattlePass*			GetBattlePassUI()		{ return (CUIBattlePass*)m_apUIs[UI_BATTLE_PASS]; }
#endif
//Val add auto pick/igni
	CAutoFuncUI*			GetAutoFunc()			{ return (CAutoFuncUI*)m_apUIs[UI_AUTOFUNC]; }
	CUIPromoKeyInputRST*	GetPromoKeyInputUI()	{ return (CUIPromoKeyInputRST*)m_apUIs[UI_PROMO_KEY_INPUT_RST]; }

	void					InitRankSystem();

	bool ENGINE_API LoadXML( const char* strPath);
	bool LoadXML( const char* strPath, CUIBase* parent );

protected:
	void			initUI();

	CUIWindow		*m_apUIs[UI_TYPE_END];				// Pointers of UIs
};


#endif		// UI_WINDOW_DECLARE_H_
