#include <boost/tokenizer.hpp>
#include "stdhdrs.h"

#include "Server.h"
#include "doFunc.h"
#include "Log.h"
#include "../ShareLib/gm_command.h"
#include "dofuncAdmin.h"
#include "GMCmdList.h"
#include "CmdMsg.h"

typedef boost::tokenizer<boost::char_separator<char> > stokenizer;
static boost::char_separator<char> sep(" ", NULL, boost::drop_empty_tokens);

//////////////////////////////////////////////////////////////////////////
CGMCmd::CGMCmd(std::string command, int level, GMFunction fun)
	: m_command(command), m_level(level), m_function(fun)
{
}

CGMCmd::~CGMCmd(void)
{
}

void CGMCmd::run(CPC* pc, const char* arg, std::vector<std::string>& vec)
{
	m_function(pc, arg, vec);
}

std::string& CGMCmd::getCommand(void)
{
	return m_command;
}

int CGMCmd::getLevel(void) const
{
	return m_level;
}

GMFunction CGMCmd::getFunction(void) const
{
	return m_function;
}
//////////////////////////////////////////////////////////////////////////

CGMCmdList* CGMCmdList::m_instance = NULL;

CGMCmdList::CGMCmdList(void)
{
}

CGMCmdList::~CGMCmdList(void)
{
}

CGMCmdList* CGMCmdList::getInstance(void)
{
	if ( m_instance == NULL )
		m_instance = new CGMCmdList();

	return m_instance;
}

void CGMCmdList::load(void)
{
	add(new CGMCmd(GM_CMD_UPDATE_EVENT, GM_LEVEL_ROLE_ADMIN, do_GMUpdateEvent));
	add(new CGMCmd(GM_CMD_RELOAD_BATTLE_WARFARE, GM_LEVEL_ROLE_ADMIN, do_GMReloadBattleWarfare));
	add(new CGMCmd(GM_CMD_SERVER_CONFIG, GM_LEVEL_ROLE_ADMIN, do_GMServerConfig));
	add(new CGMCmd(GM_CMD_HPMP, GM_LEVEL_ROLE_GAME_SERVER, do_GM_hpmp));
	add(new CGMCmd(GM_CMD_HP, GM_LEVEL_ROLE_GAME_SERVER, do_GM_hp));
	add(new CGMCmd(GM_CMD_MP, GM_LEVEL_ROLE_GAME_SERVER, do_GM_mp));
	add(new CGMCmd(GM_CMD_GUILD_POINT, GM_LEVEL_ROLE_ADMIN, do_GM_guildPoint));
	add(new CGMCmd(GM_CMD_EVENT_COLLECT, GM_LEVEL_ROLE_ADMIN, do_GM_eventCollect));
	add(new CGMCmd(GM_CMD_BLOCK, GM_LEVEL_ROLE_ADMIN, do_GM_block));
	add(new CGMCmd(GM_CMD_RELEASE, GM_LEVEL_ROLE_ADMIN, do_GM_release));
	add(new CGMCmd(GM_CMD_COUPON, GM_LEVEL_ROLE_ADMIN, do_GM_coupon));
	add(new CGMCmd(GM_CMD_PROMOTION, GM_LEVEL_ROLE_ADMIN, do_GM_promotion));
	add(new CGMCmd(GM_CMD_SETWARTIME, GM_LEVEL_ROLE_ADMIN, do_GM_setWarTime));
	add(new CGMCmd(GM_CMD_SETWARTIME2, GM_LEVEL_ROLE_ADMIN, do_GM_setWarTime2));
	add(new CGMCmd(GM_CMD_SETWARTIMEEND, GM_LEVEL_ROLE_ADMIN, do_GM_setWarTimeEnd));
	add(new CGMCmd(GM_CMD_SETWARTIME2END, GM_LEVEL_ROLE_ADMIN, do_GM_setWarTime2End));
	add(new CGMCmd(GM_CMD_LOADHP5, GM_LEVEL_ROLE_ADMIN, do_GM_loadhp5));
	add(new CGMCmd(GM_CMD_GUILDCUBESTART, GM_LEVEL_ROLE_ADMIN, do_GM_guildCubeStart));
	add(new CGMCmd(GM_CMD_GUILDCUBEEND, GM_LEVEL_ROLE_ADMIN, do_GM_guildCubeEnd));
	add(new CGMCmd(GM_CMD_GUILDCUBESTATE, GM_LEVEL_ROLE_ADMIN, do_GM_guildCubeState));
	add(new CGMCmd(GM_CMD_GUILDCUBETIMECHECK, GM_LEVEL_ROLE_ADMIN, do_GM_guildCubeTimeCheck));
	add(new CGMCmd(GM_CMD_SETOWNER, GM_LEVEL_ROLE_ADMIN, do_GM_setOwner));
	add(new CGMCmd(GM_CMD_LORDCHAT, GM_LEVEL_ROLE_ADMIN, do_GM_lordChat));
	add(new CGMCmd(GM_CMD_CREATEPET, GM_LEVEL_ROLE_ADMIN, do_GM_createPet));
	add(new CGMCmd(GM_CMD_APETSTAT, GM_LEVEL_ROLE_ADMIN, do_GM_apetStat));
	add(new CGMCmd(GM_CMD_APETHPMP, GM_LEVEL_ROLE_ADMIN, do_GM_apetHPMP));
	add(new CGMCmd(GM_CMD_APETEXP, GM_LEVEL_ROLE_ADMIN, do_GM_apetExp));
	add(new CGMCmd(GM_CMD_APETLEVELUP, GM_LEVEL_ROLE_ADMIN, do_GM_apetLevelUp));
	add(new CGMCmd(GM_CMD_APETUSE, GM_LEVEL_ROLE_ADMIN, do_GM_apetUse));
	add(new CGMCmd(GM_CMD_APETCOOLTIME, GM_LEVEL_ROLE_ADMIN, do_GM_apetCoolTime));
	add(new CGMCmd(GM_CMD_APETACCEXP, GM_LEVEL_ROLE_ADMIN, do_GM_apetAccExp));
	add(new CGMCmd(GM_CMD_SVRINFO, GM_LEVEL_ROLE_ADMIN, do_GM_svrInfo));
	add(new CGMCmd(GM_CMD_EP, GM_LEVEL_ROLE_GAME_SERVER, do_GM_ep));
	add(new CGMCmd(GM_CMD_RANKREFRESH0831, GM_LEVEL_ROLE_ADMIN, do_GM_rankRefresh0831));
	add(new CGMCmd(GM_CMD_PETLEVELUP, GM_LEVEL_ROLE_ADMIN, do_GM_petLevelUp));
	add(new CGMCmd(GM_CMD_PETDEADTIME, GM_LEVEL_ROLE_ADMIN, do_GM_petDeadTime));
	add(new CGMCmd(GM_CMD_PETRESET, GM_LEVEL_ROLE_ADMIN, do_GM_petReset));
	add(new CGMCmd(GM_CMD_PETEXPUP, GM_LEVEL_ROLE_ADMIN, do_GM_petExpUp));
	add(new CGMCmd(GM_CMD_PETMOUNTRESET, GM_LEVEL_ROLE_ADMIN, do_GM_petMountReset));
	add(new CGMCmd(GM_CMD_PETCHANGENAME, GM_LEVEL_ROLE_ADMIN, do_GM_petChangeName));
	add(new CGMCmd(GM_CMD_PKCOUNT, GM_LEVEL_ROLE_ADMIN, do_GM_pkCount));
	add(new CGMCmd(GM_CMD_PKPENALTY, GM_LEVEL_ROLE_ADMIN, do_GM_pkPenalty));
	add(new CGMCmd(GM_CMD_SHOWHP, GM_LEVEL_ROLE_GAME_SERVER, do_GM_showHP));
	add(new CGMCmd(GM_CMD_GOPOS, GM_LEVEL_ROLE_GAME_SERVER, do_GM_goPOS));
	add(new CGMCmd(GM_CMD_PDNPC, GM_LEVEL_ROLE_ADMIN, do_GM_pdNPC));
	add(new CGMCmd(GM_CMD_CASHBALANCE, GM_LEVEL_ROLE_ADMIN, do_GM_cashBalance));
	add(new CGMCmd(GM_CMD_CASHPURCHASE, GM_LEVEL_ROLE_ADMIN, do_GM_cashPurchase));
	add(new CGMCmd(GM_CMD_CASHPURCHASELIST, GM_LEVEL_ROLE_ADMIN, do_GM_cashPurchaseList));
	add(new CGMCmd(GM_CMD_CASHPURCHASEHISTORY, GM_LEVEL_ROLE_ADMIN, do_GM_cashPurchaseHistory));

	add(new CGMCmd(GM_CMD_ECHO, GM_LEVEL_ROLE_GAME_SERVER, do_GMEcho));
	add(new CGMCmd(GM_CMD_GO_ZONE, GM_LEVEL_ROLE_GAME_SERVER, do_GMGoZone));
	add(new CGMCmd(GM_CMD_GOTO, GM_LEVEL_ROLE_GAME_SERVER, do_GMGoto));
	add(new CGMCmd(GM_CMD_ITEMDROP, GM_LEVEL_ROLE_ADMIN, do_GMItemDrop));
	add(new CGMCmd(GM_CMD_COUNT_PC, GM_LEVEL_ROLE_GAME_SERVER, do_GMCountPC));
	add(new CGMCmd(GM_CMD_LOOPCOUNT, GM_LEVEL_ROLE_ADMIN, do_GMLoopCount));
	add(new CGMCmd(GM_CMD_IMMORTAL, GM_LEVEL_ROLE_GAME_SERVER, do_GMImmortal));
	add(new CGMCmd(GM_CMD_SHUTDOWN, GM_LEVEL_ROLE_ADMIN, do_GMShutdown));
	add(new CGMCmd(GM_CMD_REBOOT, GM_LEVEL_ROLE_ADMIN, do_GMReboot));
	add(new CGMCmd(GM_CMD_COUNT_NPC, GM_LEVEL_ROLE_GAME_SERVER, do_GMCountNPC));
	add(new CGMCmd(GM_CMD_VISIBLE, GM_LEVEL_ROLE_GAME_SERVER, do_GMVisible));
	add(new CGMCmd(GM_CMD_GO_PC, GM_LEVEL_ROLE_GAME_SERVER, do_GMGoPC));
	add(new CGMCmd(GM_CMD_GO_NPC, GM_LEVEL_ROLE_GAME_SERVER, do_GMGoNPC));
	add(new CGMCmd(GM_CMD_LEVELUP, GM_LEVEL_ROLE_ADMIN, do_GMLevelUP));
	add(new CGMCmd(GM_CMD_KICK, GM_LEVEL_ROLE_GAME_SERVER, do_GMKICK));
	add(new CGMCmd(GM_CMD_COMON, GM_LEVEL_ROLE_ADMIN, do_GMComon));
	add(new CGMCmd(GM_CMD_SUMMON, GM_LEVEL_ROLE_ADMIN, do_GMSummon));
	add(new CGMCmd(GM_CMD_SILENCE, GM_LEVEL_ROLE_GAME_SERVER, do_GMSilence));
	add(new CGMCmd(GM_CMD_WHERE_AM_I, GM_LEVEL_ROLE_GAME_SERVER, do_GMWhereAmI));
	add(new CGMCmd(GM_CMD_QUEST_COMPLETE, GM_LEVEL_ROLE_ADMIN, do_GMQuestComplete));
	add(new CGMCmd(GM_CMD_STATPOINT, GM_LEVEL_ROLE_GAME_SERVER, do_GMStatPoint));
	add(new CGMCmd(GM_CMD_SKILLPOINT, GM_LEVEL_ROLE_GAME_SERVER, do_GMSkillPoint));
	add(new CGMCmd(GM_CMD_SET_REGENSEC, GM_LEVEL_ROLE_ADMIN, do_GMSetRegenSec));
	add(new CGMCmd(GM_CMD_NPC_REGEN, GM_LEVEL_ROLE_ADMIN, do_GMNPCRegen));
	add(new CGMCmd(GM_CMD_KILL_NPC, GM_LEVEL_ROLE_GAME_SERVER, do_GMKillNPC));
	add(new CGMCmd(GM_CMD_EXPUP, GM_LEVEL_ROLE_ADMIN, do_GMExpUp));
	add(new CGMCmd(GM_CMD_BLOODPOINT, GM_LEVEL_ROLE_GAME_SERVER, do_GMBloodPoint));
	add(new CGMCmd(GM_CMD_ENDGAME, GM_LEVEL_ROLE_ADMIN, do_GMEndGame));
	add(new CGMCmd(GM_CMD_OBSERVE, GM_LEVEL_ROLE_ADMIN, do_GMObserve));
	add(new CGMCmd(GM_CMD_CHATMONITOR, GM_LEVEL_ROLE_ADMIN, do_GMChatMonitor));
	add(new CGMCmd(GM_CMD_DOUBLE_EVENT, GM_LEVEL_ROLE_ADMIN, do_GMDoubleEvent));
	add(new CGMCmd(GM_CMD_LATTO_EVENT, GM_LEVEL_ROLE_ADMIN, do_GMLattoEvent));
	add(new CGMCmd(GM_CMD_DOUBLE_EXP_EVENT, GM_LEVEL_ROLE_ADMIN, do_GMDoubleExpEvent));
	add(new CGMCmd(GM_CMD_NEWYEAR_EVENT, GM_LEVEL_ROLE_ADMIN, do_GMNewYearEvent));
	add(new CGMCmd(GM_CMD_VALENTINE_EVENT, GM_LEVEL_ROLE_ADMIN, do_GMValentineEvent));
	add(new CGMCmd(GM_CMD_WHITEDAY_EVENT, GM_LEVEL_ROLE_ADMIN, do_GMWhiteDayEvent));
	add(new CGMCmd(GM_CMD_RELOAD_GMIP, GM_LEVEL_ROLE_ADMIN, do_GMReloadGMIP));

	add(new CGMCmd(GM_CMD_SPEEDUP, GM_LEVEL_ROLE_ADMIN, do_GMSpeedUp));
	add(new CGMCmd(GM_CMD_FAMEUP, GM_LEVEL_ROLE_ADMIN, do_GMFameUp));
	add(new CGMCmd(GM_CMD_EVENT, GM_LEVEL_ROLE_ADMIN, do_GMEvent));
	add(new CGMCmd(GM_CMD_PD4, GM_LEVEL_ROLE_ADMIN, do_GMPD4));
	add(new CGMCmd(GM_CMD_KICK_ID, GM_LEVEL_ROLE_GAME_SERVER, do_GMKickID));
	add(new CGMCmd(GM_CMD_RESURRECTION, GM_LEVEL_ROLE_ADMIN, do_GMResurrection));
	add(new CGMCmd(GM_CMD_RECOMMEND, GM_LEVEL_ROLE_ADMIN, do_GMRecommend));
	add(new CGMCmd(GM_CMD_SETLIMIT, GM_LEVEL_ROLE_ADMIN, do_GMSetLimit));
	add(new CGMCmd(GM_CMD_DISGUISE, GM_LEVEL_ROLE_ADMIN, do_GMDisguise));
	add(new CGMCmd(GM_CMD_LOGINSERVER, GM_LEVEL_ROLE_ADMIN, do_GMLoginServer));
	add(new CGMCmd(GM_CMD_KICK_CHAR_INDEX, GM_LEVEL_ROLE_GAME_SERVER, do_GMKickCharIndex));
	add(new CGMCmd(GM_GMD_EVENTSHOW, GM_LEVEL_ROLE_ADMIN, do_GMEventShow));
	add(new CGMCmd(GM_CMD_EVENTSETTING, GM_LEVEL_ROLE_ADMIN, do_GMEventSetting));
	add(new CGMCmd(GM_CMD_CHANCE_EVENT, GM_LEVEL_ROLE_ADMIN, do_GMChanceEvent));
	add(new CGMCmd(GM_CMD_GMCHATMONITOR, GM_LEVEL_ROLE_ADMIN, do_GMToolChatMonitor));
	add(new CGMCmd(GM_CMD_DOUBLE_ITEM_DROP, GM_LEVEL_ROLE_ADMIN, do_GMDoubleItemEvent));
	add(new CGMCmd(GM_CMD_DOUBLE_PET_EXP, GM_LEVEL_ROLE_ADMIN, do_GMDoublePetExpEvent));
	add(new CGMCmd(GM_CMD_DOUBLE_ATTACK, GM_LEVEL_ROLE_ADMIN, do_GMDoubleAttackEvent));
	add(new CGMCmd(GM_CMD_EVENT_DROPITEM, GM_LEVEL_ROLE_ADMIN, do_GMDropItemEvent));
	add(new CGMCmd(GM_CMD_KICK_PC_MULTI, GM_LEVEL_ROLE_GAME_SERVER, do_GMKickMulti));
	add(new CGMCmd(GM_CMD_SILENCE_PC_MULTI, GM_LEVEL_ROLE_GAME_SERVER, do_GMSilenceMulti));
	add(new CGMCmd(GM_CMD_SET_EXPLIMIIT, GM_LEVEL_ROLE_ADMIN, do_GMExpLimit));
	add(new CGMCmd(GM_CMD_DOUBLE_EVENT_AUTO, GM_LEVEL_ROLE_ADMIN, do_GMDoubleEventAuto));
	add(new CGMCmd(GM_CMD_UPGRADE_EVENT, GM_LEVEL_ROLE_GAME_SERVER, do_GMUpgradeEvent));
	add(new CGMCmd(GM_CMD_KICK_GUILDMEMBER, GM_LEVEL_ROLE_ADMIN, do_GMKickGuildMember));
	add(new CGMCmd(GM_CMD_APPLY_SKILL, GM_LEVEL_ROLE_ADMIN, do_GMApplySkill));
	add(new CGMCmd(GM_CMD_STATE_FLAG, GM_LEVEL_ROLE_ADMIN, do_GMStateFlag));
	add(new CGMCmd(GM_CMD_DATE, GM_LEVEL_ROLE_GAME_SERVER, do_GMDate));
	add(new CGMCmd(GM_CMD_PLAY_TRIGGER, GM_LEVEL_ROLE_ADMIN, do_GMPlayTrigger));
	add(new CGMCmd(GM_CMD_BATTLE_START, GM_LEVEL_ROLE_GAME_SERVER, do_GMBattleStart));
	add(new CGMCmd(GM_CMD_BATTLE_STOP, GM_LEVEL_ROLE_GAME_SERVER, do_GMBattleStop));
	add(new CGMCmd(GM_CMD_RESET_RAID, GM_LEVEL_ROLE_ADMIN, do_GMResetRaid));
	add(new CGMCmd(GM_CMD_SET_SEAL_EXP, GM_LEVEL_ROLE_ADMIN, do_GMSetSealExp));
	add(new CGMCmd(GM_CMD_END_SUBHELPER, GM_LEVEL_ROLE_ADMIN, do_GMEndSubHelper));
	add(new CGMCmd(GM_CMD_MY_ADMIN, GM_LEVEL_ROLE_GAME_SERVER, do_GMMyAdmin));
	add(new CGMCmd(GM_CMD_DT_TIMESET, GM_LEVEL_ROLE_ADMIN, do_GMDTTimeSet));
	add(new CGMCmd(GM_CMD_DT_EXPSET, GM_LEVEL_ROLE_ADMIN, do_GMDTExpSet));
	add(new CGMCmd(GM_CMD_DT_TIMEINTERVAL, GM_LEVEL_ROLE_ADMIN, do_GMDTTimeInterval));
	add(new CGMCmd(GM_CMD_DT_TOGGLE, GM_LEVEL_ROLE_ADMIN, do_GMDTToggle));
	add(new CGMCmd(GM_CMD_RELOAD_CATALOG, GM_LEVEL_ROLE_ADMIN, do_GMReloadCatalog));
	add(new CGMCmd(GM_CMD_NPC_DROP, GM_LEVEL_ROLE_ADMIN, do_GMNPCDrop));
	add(new CGMCmd(GM_CMD_GODBLESS, GM_LEVEL_ROLE_GAME_SERVER, do_GMGodBless));
	add(new CGMCmd(GM_CMD_ENCHANT, GM_LEVEL_ROLE_ADMIN, do_GMEnchant));
	add(new CGMCmd(GM_CMD_MODIFY_CASHSHOP, GM_LEVEL_ROLE_ADMIN, do_GMModifyCashShop));
	add(new CGMCmd(GM_CMD_LCBALL_RESET, GM_LEVEL_ROLE_GAME_SERVER, do_GMLCBallReset));
	add(new CGMCmd(GM_CMD_ATTEVENT_2011, GM_LEVEL_ROLE_ADMIN, do_GMAttEvent));
	add(new CGMCmd(GM_CMD_FUNC, GM_LEVEL_ROLE_ADMIN, do_GMFunc));
	add(new CGMCmd(GM_CMD_ECHONPC, GM_LEVEL_ROLE_ADMIN, do_GMEchoNpc));
	add(new CGMCmd(GM_CMD_CASTLE_STATE_CYNC, GM_LEVEL_ROLE_ADMIN, do_GMCastleStateCync));
	add(new CGMCmd(GM_CMD_TREASURE_MAP_DROP, GM_LEVEL_ROLE_ADMIN, do_GMTreasureMapDrop));
	add(new CGMCmd(GM_CMD_DEATH_EVENT, GM_LEVEL_ROLE_ADMIN, do_GMDeathEvent));
	add(new CGMCmd(GM_CMD_ATTENDANCE_CHANGE, GM_LEVEL_ROLE_ADMIN, do_GMAttendanceChange));
	add(new CGMCmd(GM_CMD_SET, GM_LEVEL_ROLE_ADMIN, do_GMSet));
	add(new CGMCmd(GM_CMD_CRAFTPOINT, GM_LEVEL_ROLE_ADMIN, do_CraftPoint));
	add(new CGMCmd(GM_CMD_EVENTAOUTOMATON, GM_LEVEL_ROLE_ADMIN, do_GMEventAutomation));
	add(new CGMCmd(GM_CMD_SKILLLEARN, GM_LEVEL_ROLE_ADMIN, do_GMSkillLearn));
	add(new CGMCmd(GM_CMD_APET_HUNGRY, GM_LEVEL_ROLE_ADMIN, do_GMApetHungry));
	add(new CGMCmd(GM_CMD_APET_FAITH, GM_LEVEL_ROLE_ADMIN, do_GMApetFaith));
	add(new CGMCmd(GM_CMD_COMPARE_BOXITEM, GM_LEVEL_ROLE_ADMIN, do_GMCompareBoxItem));
	add(new CGMCmd(GM_CMD_GUILDMASTER_KICK_RESET, GM_LEVEL_ROLE_ADMIN, do_GMGuildMasterKickReset));
	add(new CGMCmd(GM_CMD_GUILDMASTER_CHANGE, GM_LEVEL_ROLE_ADMIN, do_GMGuildChangeBoss));
	add(new CGMCmd(GM_CMD_JOBRESET, GM_LEVEL_ROLE_ADMIN, do_GMJobReset));
	add(new CGMCmd(GM_CMD_JOBCHANGE, GM_LEVEL_ROLE_ADMIN, do_GMJobChange));
	add(new CGMCmd(GM_CMD_ITEMGET, GM_LEVEL_ROLE_ADMIN, do_GMItemGet));
	add(new CGMCmd(GM_CMD_ITEMGETRANGE, GM_LEVEL_ROLE_ADMIN, do_GMItemGetRange));
	add(new CGMCmd(GM_CMD_XMAS_PUZZLE, GM_LEVEL_ROLE_ADMIN, do_GMXMASPuzzle));
	add(new CGMCmd(GM_CMD_ROYAL_RUMBLE_SETTING, GM_LEVEL_ROLE_ADMIN, doGMRoyalRumbleSetting));
	add(new CGMCmd(GM_CMD_AFFINITY_SET, GM_LEVEL_ROLE_ADMIN, do_GMAffinitySet));
	add(new CGMCmd(GM_CMD_AFFINITY_REWARD_INIT, GM_LEVEL_ROLE_ADMIN, do_GMAffinityRewardInit));
	add(new CGMCmd(GM_CMD_NAS_SET, GM_LEVEL_ROLE_ADMIN, do_GMNasSet));
	add(new CGMCmd(GM_CMD_JEWELRYE, GM_LEVEL_ROLE_ADMIN, do_GMJewelEvent));
	add(new CGMCmd(GM_CMD_JEWEL_LOAD, GM_LEVEL_ROLE_ADMIN, do_GMJewelLoad));
#ifdef LC_KOR
	add(new CGMCmd(GM_CMD_CRASH, GM_LEVEL_ROLE_ADMIN, do_Crash));
#endif
	add(new CGMCmd(GM_CMD_NOT_GM, GM_LEVEL_ROLE_ADMIN, do_NotGM));
	add(new CGMCmd(GM_CMD_TRADEAGENT_FEE, GM_LEVEL_ROLE_ADMIN, do_TradeAgent_Fee));
	add(new CGMCmd(GM_CMD_TRADEAGENT_DEPOSIT, GM_LEVEL_ROLE_ADMIN, do_TradeAgent_Deposit));
	add(new CGMCmd(GM_CMD_GO_ZONE_FINDNPC, GM_LEVEL_ROLE_GAME_SERVER, do_FindNpcAndGoZone));

	add(new CGMCmd(GM_CMD_STASHGETRANGE, GM_LEVEL_ROLE_ADMIN, do_StashGetRange));
	add(new CGMCmd(GM_CMD_STASHDEL, GM_LEVEL_ROLE_ADMIN, do_StashDel));

	add(new CGMCmd(GM_CMD_TIMERITEM_SET, GM_LEVEL_ROLE_ADMIN, do_GMTimerItemSet));
	add(new CGMCmd(GM_CMD_PICKUP_ITEM, GM_LEVEL_ROLE_ADMIN, do_PickupItem));
	add(new CGMCmd(GM_CMD_MONSTER_MERCEARY, GM_LEVEL_ROLE_ADMIN, do_MonsterCard));
	add(new CGMCmd(GM_CMD_VIEW_ALL_SHOP_LIST, GM_LEVEL_ROLE_ADMIN, do_ViewAllShopList));
	add(new CGMCmd(GM_CMD_DEL_CHARACTER, GM_LEVEL_ROLE_ADMIN, do_DelCharacter));
	add(new CGMCmd(GM_CMD_LOGOUT, GM_LEVEL_ROLE_ADMIN, do_Logout));
	add(new CGMCmd(GM_CMD_EXP, GM_LEVEL_ROLE_ADMIN, do_Exp));
	add(new CGMCmd(GM_CMD_GO_NEXT_PC, 8, do_GoNextPC));
	add(new CGMCmd(GM_CMD_VIRTUAL_REFORM, GM_LEVEL_ROLE_ADMIN, do_VirtualReform));
	add(new CGMCmd(GM_CMD_ROCK_PAPER_SCISSORS_WIN, GM_LEVEL_ROLE_ADMIN, do_RockPaperScissorsWin));

	add(new CGMCmd(GM_CMD_RVR_INCREASE_POINT, GM_LEVEL_ROLE_ADMIN, do_GMIncreaseRVRPoint));
	add(new CGMCmd(GM_CMD_RVR_DECREASE_POINT, GM_LEVEL_ROLE_ADMIN, do_GMDecreaseRVRPoint));

	add(new CGMCmd(GM_CMD_THEOS_CHECK_REWARD_ITEM, GM_LEVEL_ROLE_ADMIN, do_GMTheosCheckTime));
	add(new CGMCmd(GM_CMD_THEOS_CHECK_POLLUTION, GM_LEVEL_ROLE_ADMIN, do_GMTheosChangePollution));
	add(new CGMCmd(GM_CMD_THEOS_CHECK_DIFFICULTY, GM_LEVEL_ROLE_ADMIN, do_GMTheosChangeDifficulty));

#ifdef DURABILITY
	add(new CGMCmd(GM_CMD_DURABILITY, GM_LEVEL_ROLE_ADMIN, do_GM_Durability));
#endif
#ifdef REZAPCHA
	add(new CGMCmd(GM_CMD_REZAP, 10, do_rezap));
#endif
	add(new CGMCmd(GM_CMD_RVR_APPLYSKILL, GM_LEVEL_ROLE_ADMIN, do_GMRVRApplySkill));
	add(new CGMCmd(GM_CMD_RVR_SHOWJEWELPOINT, GM_LEVEL_ROLE_ADMIN, do_GMRVRShowJewelPoint));
	add(new CGMCmd(GM_CMD_RVR_SET_USERCOUNT, GM_LEVEL_ROLE_ADMIN, do_GMRVRSetUserCount));
	add(new CGMCmd(GM_CMD_RVR_SHOW_USERCOUNT, GM_LEVEL_ROLE_ADMIN, do_GMRVRShowUserCount));
	add(new CGMCmd(GM_CMD_ALL_ITEM_TIME_SET, GM_LEVEL_ROLE_ADMIN, do_GM_ItemUsed_Set));
	add(new CGMCmd(GM_CMD_GET_EXCHANGE_ITEM, GM_LEVEL_ROLE_ADMIN, do_GM_GetExchangeItem));
	add(new CGMCmd(GM_CMD_NO_SPECIAL_BOX_COOLTIME, GM_LEVEL_ROLE_ADMIN, do_GM_NoCoolBoxItem));

#ifdef PREMIUM_CHAR
	add(new CGMCmd(GM_CMD_PRIMIUM_CHAR_RESET, GM_LEVEL_ROLE_ADMIN, do_GM_PremiumChar_Reset));
	add(new CGMCmd(GM_CMD_PRIMIUM_CHAR_SET_EXPIRE_TIME, GM_LEVEL_ROLE_ADMIN, do_GM_PremiumChar_set_expire_time));
	add(new CGMCmd(GM_CMD_PRIMIUM_CHAR_SET_JUMP_COUNT, GM_LEVEL_ROLE_ADMIN, do_GM_PremiumChar_set_jump_count));
	add(new CGMCmd(GM_CMD_PRIMIUM_CHAR_SET_TYPE, GM_LEVEL_ROLE_ADMIN, do_GM_PremiumChar_set_type));
#endif
	add(new CGMCmd(GM_CMD_ATTENDANCE_ASSURE_EXPIRE_TIME, GM_LEVEL_ROLE_ADMIN, do_GM_Attendance_assure_set_expire_time));
	add(new CGMCmd(GM_CMD_RAID_CHANGE_MAX_AREA_COUNT, GM_LEVEL_ROLE_ADMIN, do_raid_changeMaxAreaCount));
	add(new CGMCmd(GM_CMD_POPUP_NOTICE, GM_LEVEL_ROLE_ADMIN, do_popup_notice));
	add(new CGMCmd(GM_CMD_POPUP_NOTICEOFF, GM_LEVEL_ROLE_ADMIN, do_popup_noticeoff));
	add(new CGMCmd(GM_CMG_MASTERSTONE_PROB, GM_LEVEL_ROLE_ADMIN, do_masterstone_prob_test));
	add(new CGMCmd(GM_CMD_GUILD_BATTLE_CORE, GM_LEVEL_ROLE_ADMIN, do_guild_battle_score));
	add(new CGMCmd(GM_CMD_GUILD_BATTLE_LIST, GM_LEVEL_ROLE_ADMIN, do_guild_battle_list));
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	add(new CGMCmd(GM_CMD_SPAWN_RAID_NPC, 10, do_spawnRAIDNPC));
#endif
	add(new CGMCmd(GM_CMD_TEST_COMMAND, GM_LEVEL_ROLE_ADMIN, do_test));
	
	add(new CGMCmd(GM_CMD_GUILD_MEMBER_OUT_TIME, GM_LEVEL_ROLE_ADMIN, do_GM_Guild_Memberout_Time));
	add(new CGMCmd(GM_CMD_GUILD_CREATE_TIME, GM_LEVEL_ROLE_ADMIN, do_GM_Guild_Create_time));

	add(new CGMCmd(GM_CMD_RESERVED_GM_COMMAND, GM_LEVEL_ROLE_ADMIN, do_GM_reserve_command));
	add(new CGMCmd(GM_CMD_DONATION_EVENT, GM_LEVEL_ROLE_ADMIN, do_GM_donationEvent));
	add(new CGMCmd(GM_CMD_SPAWN_NPC, GM_LEVEL_ROLE_ADMIN, do_spawnNPC)); // rrbkmz
	add(new CGMCmd(GM_CMD_SPAWN_SHOP, GM_LEVEL_ROLE_ADMIN, do_spawnSHOP)); // //dethunter12 spawn shop 
	
	add(new CGMCmd("do_debug", GM_LEVEL_ROLE_ADMIN, do_debug));
	add(new CGMCmd(GM_CMD_BAN_PLAYER, 10, do_banPlayer));
	add(new CGMCmd(GM_CMD_BLOCK_PLAYER, 10, do_blockPlayer));
	add(new CGMCmd(GM_CMD_TOGGLE_BUFF, 10, do_buff_system));
	add(new CGMCmd(GM_CMD_RLGL, 10, do_RLGLCMD));
	add(new CGMCmd(GM_CMD_HACK_WATCH, 10, do_WATCH));

    //pwesty shit
    add(new CGMCmd("reload_shop", GM_LEVEL_ROLE_ADMIN, do_GMReloadShop));
    // reload quest prototypes
    add(new CGMCmd("reload_quest", GM_LEVEL_ROLE_ADMIN, do_GMReloadQuest));
    // reload zone data
    add(new CGMCmd("reload_zone", GM_LEVEL_ROLE_ADMIN, do_GMReloadZone));
    // reload npc data
    add(new CGMCmd("reload_npc", GM_LEVEL_ROLE_ADMIN, do_GMReloadNPC));
	// reload item prototypes
	add(new CGMCmd("reload_item", GM_LEVEL_ROLE_ADMIN, do_GMReloadItem));
	// reload scripted NPC movements
	add(new CGMCmd("reload_scripted_movements", GM_LEVEL_ROLE_ADMIN, do_GMReloadScriptedMovements));

}

void CGMCmdList::add(CGMCmd* gmcmd)
{
	// ���ɾ� ���̰� 1���� ������ ����
	if ( gmcmd->getCommand().length() < 1 )
		return;

	// ���ɾ� ������ 0���� ������ ����
	if ( gmcmd->getLevel() < 0 )
		return;

	// �Լ� �����Ͱ� NULL�̸� ����
	if ( gmcmd->getFunction() == NULL )
		return;

	// ���
	m_GMCmdList.insert(map_t::value_type(gmcmd->getCommand(), gmcmd));
}

void CGMCmdList::run(CPC* pc, const char* arg)
{
	std::string str(arg);
	stokenizer token(str, sep);
	std::vector<std::string> vec;
	vec.assign(token.begin(), token.end());

	if (vec.empty())
		return;

	std::string p = arg;
	char command[512];
	if (p.length() > 511 || p.length() < 0) //dethunter12 gmcmdlist hack
		return;
	p = AnyOneArg(p.c_str(), command, true);

	// �����ϴ��� �˻�
	CGMCmd* pGMCmd = find(vec[0]);
	if ( pGMCmd == NULL )
	{
		//system msg
		if(pc->m_admin > 0)
		{
			std::string message = boost::str(boost::format("Not found gm command"));
			CNetMsg::SP rmsg(new CNetMsg);
			SayMsg(rmsg, MSG_CHAT_GM, 0, "", "", message.c_str());
			SEND_Q(rmsg, pc->m_desc);
		}
		return;
	}

	// ������ �� �ִ��� �˻�
	if ( !canRun( pGMCmd, pc ) )
	{
		if(pc->m_admin > 0)
		{
			//system msg
			std::string message = boost::str(boost::format("Not enough gm level"));
			CNetMsg::SP rmsg(new CNetMsg);
			SayMsg(rmsg, MSG_CHAT_GM, 0, "", "", message.c_str());
			SEND_Q(rmsg, pc->m_desc);
		}
		return;
	}
	

	if(p.empty() == true)
	{
		p = " ";
	}

	char* buf = (char*)p.c_str();
	char* name = pc->m_name.GetBuffer();
	char* nick = pc->m_nick.GetBuffer();
	
	LOG_INFO("GM COMMAND : %s : %s : %d : %s : %s ", command, buf, pc->m_index, name, nick);

	{
		CDBCmd dbcmd;
		dbcmd.Init(&gserver->m_dbchar);
		std::string query = boost::str(
		boost::format("INSERT INTO t_gmlog (a_char_idx,a_char_nick,a_name,a_admin,a_datestamp,a_gm_command) VALUES (%d,'%s','%s',%d,NOW(),'%s')")
		% pc->m_index % nick % pc->m_name % pc->m_admin % command );
		dbcmd.SetQuery(query);
		dbcmd.Update();
	}

	// ����
	vec.erase(vec.begin());
	pGMCmd->run(pc, p.c_str(), vec);
}

CGMCmd* CGMCmdList::find(std::string& command)
{
	map_t::iterator it = m_GMCmdList.find(command);
	return (it != m_GMCmdList.end()) ? it->second : NULL;
}

bool CGMCmdList::canRun(CGMCmd* gmcmd, CPC* pc)
{
	if ( pc->m_admin < gmcmd->getLevel() )
		return false;

	return true;
}

