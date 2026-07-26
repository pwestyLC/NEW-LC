#ifndef __GM_COMMAND_H__
#define __GM_COMMAND_H__

// ��� ���ɾ� ����
#define		GM_CMD_HPMP								"hpmp"
#define		GM_CMD_HP								"hp"
#define		GM_CMD_MP								"mp"

#define		GM_CMD_GUILD_POINT						"guildpoint"
#define		GM_CMD_EVENT_COLLECT					"event_collect"
#define		GM_CMD_BLOCK							"block"
#define		GM_CMD_RELEASE							"release"
#define		GM_CMD_COUPON							"coupon"
#define		GM_CMD_PROMOTION						"promotion"
#define		GM_CMD_SETWARTIME						"setwartime"
#define		GM_CMD_SETWARTIME2						"setwartime2"
#define		GM_CMD_SETWARTIMEEND					"setwartimeend"
#define		GM_CMD_SETWARTIME2END					"setwartime2end"
#define		GM_CMD_LOADHP5							"loadhp5"
#define		GM_CMD_GUILDCUBESTART					"guildcubestart"
#define		GM_CMD_GUILDCUBEEND						"guildcubeend"
#define		GM_CMD_GUILDCUBESTATE					"guildcubestate"
#define		GM_CMD_GUILDCUBETIMECHECK				"guildcubetimecheck"
#define		GM_CMD_SETOWNER							"setowner"
#define		GM_CMD_LORDCHAT							"lordchat"
#define		GM_CMD_CREATEPET						"create_pet"
#define		GM_CMD_APETSTAT							"apet_stat"
#define		GM_CMD_APETHPMP							"apet_hpmp"
#define		GM_CMD_APETEXP							"apet_exp"
#define		GM_CMD_APETLEVELUP						"apet_levelup"
#define		GM_CMD_APETUSE							"apet_use"
#define		GM_CMD_APETCOOLTIME						"apet_cooltime"
#define		GM_CMD_APETACCEXP						"apet_accexp"
#define		GM_CMD_SVRINFO							"svrinfo"
#define		GM_CMD_EP								"ep"
#define		GM_CMD_RANKREFRESH0831					"rankrefresh0831"
#define		GM_CMD_PETLEVELUP						"petlevelup"
#define		GM_CMD_PETDEADTIME						"petdeadtime"
#define		GM_CMD_PETRESET							"petreset"
#define		GM_CMD_PETEXPUP							"petexpup"
#define		GM_CMD_PETMOUNTRESET					"petmountreset"
#define		GM_CMD_PETCHANGENAME					"petchangename"
#define		GM_CMD_PKCOUNT							"pkcount"
#define		GM_CMD_PKPENALTY						"pkpenalty"
#define		GM_CMD_SHOWHP							"showhp"
#define		GM_CMD_GOPOS							"gopos"
#define		GM_CMD_PDNPC							"pd_npc"
#define		GM_CMD_CASHBALANCE						"cashbalance"
#define		GM_CMD_CASHPURCHASE						"cashpurchase"
#define		GM_CMD_CASHPURCHASELIST					"cashpurchaselist"
#define		GM_CMD_CASHPURCHASEHISTORY				"cashpurchasehistory"

// echo <zone | server | all / subserver> <chat>
#define     GM_CMD_ECHO								"echo"          // ��� �˸� �޽���
#define     GM_CMD_ECHO_ZONE						"zone"          // �� �˸� �޽���
#define     GM_CMD_ECHO_SERVER						"server"        // ������ �˸� �޽���
#define     GM_CMD_ECHO_ALL							"all"           // ��� ���� �˸� �޽���
#define     GM_CMD_ECHO_SUBSERVER					"subserver"     // ������ ���꼭�� �˸� �޽���
#define     GM_CMD_ECHO_ALLZONE						"allzone"       // ��� �������� ���� �˸�
// go_zone <zone> <extra>
#define     GM_CMD_GO_ZONE							"go_zone"       // �� �̵�
// goto <x> <z> <y>
#define     GM_CMD_GOTO								"goto"          // ��� �̵�
// itemdrop <index> <plus> <flag> <count> <option_count> <option_type> <option_level>
#define     GM_CMD_ITEMDROP							"itemdrop"      // ������ ���� ���
// count_pc
#define     GM_CMD_COUNT_PC							"count_pcc"     // ����� �� ����
// loopcount
#define     GM_CMD_LOOPCOUNT						"loopcount"     // ���� ī��Ʈ ����
// immortal
#define     GM_CMD_IMMORTAL							"immortal"      // ������ ���� ������ ����: ���
// shutdown <time:sec> <msg>
#define     GM_CMD_SHUTDOWN							"shutdown"      // �˴ٿ�: �ڵ� ����� ����(������ �ٿ�)
// reboot <all | server | subserver><time:sec> <msg>
#define     GM_CMD_REBOOT							"reboot"        // ����Ʈ: �ڵ� ����� ��
// count_npc
#define     GM_CMD_COUNT_NPC						"count_npc"     // npc �� ����
// visible
#define     GM_CMD_VISIBLE							"visible"       // ����/������ ����
// go_pc <char name>
#define     GM_CMD_GO_PC							"go_pc"         // ������ ĳ���� ������ �̵�
// go_npc <name or index>
#define     GM_CMD_GO_NPC							"go_npc"        // ������ �� ������ �̵�
// levelup <level>
#define     GM_CMD_LEVELUP							"levelup"       // ������ ������ ����
// kick <char name>
#define     GM_CMD_KICK								"kick"          // ĳ���͸� �����κ��� ƨ�ܳ�
// comon <char name>
#define     GM_CMD_COMON							"common"        // ĳ���͸� ��� ĳ���� ������
// summon <name or index>
#define     GM_CMD_SUMMON							"summon"        // ������ �� ��� ĳ���� ������ ��ȯ
// silence <char name> <time:sec>
#define     GM_CMD_SILENCE							"silence"       // ĳ���Ϳ��� �ð����� ä�� ����
// whereami
#define     GM_CMD_WHERE_AM_I						"whereami"      // ĳ������ zone, area ��ȣ
// QuestComplete <QuestTypeNum>
#define     GM_CMD_QUEST_COMPLETE					"questcomplete" // ����Ʈ ���� �Ϸ�
// statpoint <remain> [<str> <dex> <int> <con>]
#define     GM_CMD_STATPOINT						"statpoint"     // ���� ����Ʈ ���� ����
// skillpoint <count>
#define     GM_CMD_SKILLPOINT						"skillpoint"    // ��ų ����Ʈ ���� ����
// set_regensec <index> <time:1/10sec>
#define     GM_CMD_SET_REGENSEC						"set_regensec"  // �ش� npc regensec ����
// npc_regen <index>
#define     GM_CMD_NPC_REGEN						"npc_regen"     // �ش� npc �� ���� �Ǿ� �ϴ°͵� ��� ���� ����
// kill_npc <meter :m>
#define     GM_CMD_KILL_NPC							"kill_npc"      // ��ڿ� �Ÿ��ȿ� �ִ� npc�� ��� ���� ����
// expup <exp%>
#define     GM_CMD_EXPUP							"expup"         // ĳ���� ����ġ ����
// bloodpoint <bloodpoint>
#define     GM_CMD_BLOODPOINT						"bloodpoint"    // ĳ���� ���� Blood Point ����
// endgame <time:sec> <msg>
#define     GM_CMD_ENDGAME							"endgame"       // �޽����� ������ ��� ���� �ٿ�
// observe
#define     GM_CMD_OBSERVE							"observe"       // ������ ����
// chatmonitor <character name>
#define     GM_CMD_CHATMONITOR						"chatmonitor"   // ä�� ����
// double_event <"start" or "stop" or "ing">
#define     GM_CMD_DOUBLE_EVENT						"double_event"  // ����ġ, ����, SP, ����ǰ 2�� �̺�Ʈ
// latto_event <"start" or "stop" or "ing">
#define     GM_CMD_LATTO_EVENT						"latto_event"   // ��� �̺�Ʈ
// doubleexp_event <serverno | all | cur> <start | stop | ing> <0~200%>
#define     GM_CMD_DOUBLE_EXP_EVENT					"doubleexp_event"   // ����ġ 2�� �̺�Ʈ(�ۼ�Ƽ���� ���� �ٲٴ� ������ ����)
// newyear_event <"start" or "stop" or "ing">
#define     GM_CMD_NEWYEAR_EVENT					"newyear_event" // ���� �̺�Ʈ
// valentine_event <"start" or "stop" or "ing">
#define     GM_CMD_VALENTINE_EVENT					"valentine_event"   // �߷�Ÿ�ε��� �̺�Ʈ
// whiteday_event <"start" or "stop" or "ing">
#define     GM_CMD_WHITEDAY_EVENT					"whiteday_event"    // ȭ��Ʈ���� �̺�Ʈ
// letter_event <"start" or "stop" or "ing">
#define     GM_CMD_LETTER_EVENT						"letter_event"  // ���� ���߱� �̺�Ʈ
// reloadgmip
#define     GM_CMD_RELOAD_GMIP						"reloadgmip"    // GM IP ���� ���̺� �ٽ� �б�
#define     GM_CMD_RELOAD_ALL						"reload_dmg" 
// speedup
#define     GM_CMD_SPEEDUP							"speedup"       // ���� �޸���
// fameup
#define     GM_CMD_FAMEUP							"fameup"        // ����ġ ����
// event <name> <start | stop | ing>
#define     GM_CMD_EVENT							"event"         // �̺�Ʈ ����
// pd4 <rankinit | rewardinit | rewardend>
#define     GM_CMD_PD4								"pd4"           // �����ǹ� ��ũ
// kickid <id>
#define     GM_CMD_KICK_ID							"kickid"        // id�� ���� ���� ����
// resurrection <name>
#define     GM_CMD_RESURRECTION						"resurrection"  // �ش� �ɸ��� ��Ȱ
// recommend <server no>
#define     GM_CMD_RECOMMEND						"recommend"     // �ش� ������ ��õ ����, -1�̸� ��� ��õ �ƴ� ������
// setlimit  <ctid> <sellNo>
#define     GM_CMD_SETLIMIT							"setlimit"      // �ش� �������� �ǸŻ�ǰ ����, sellNo �� �Ǹ��� ����. ĳ������ ������ ����Ʈ���� �������� ����
// disguise
#define     GM_CMD_DISGUISE							"disguise"      // �ش� �������� �ǸŻ�ǰ ����, sellNo �� �Ǹ��� ����. ĳ������ ������ ����Ʈ���� �������� ����
// loginserver <open | close | reboot>
#define     GM_CMD_LOGINSERVER						"loginserver"   // �α��� ���� ����
// caltime
#define     GM_CMD_CALTIME							"caltime"       // ���� �ð� ����
// kickchar <charindex>
#define     GM_CMD_KICK_CHAR_INDEX					"kickcharidx"       // id�� ���� ���� ����

#define     GM_GMD_EVENTSHOW						"eventshow"         // ���� �̺�Ʈ ���� �̸�, �������ε���

#define     GM_CMD_EVENTSETTING						"eventsetting"  // �̺�Ʈ ����
#define     GM_CMD_CHANCE_EVENT						"chance_event"  // �������� ������ ���� ����
#define     GM_CMD_GMCHATMONITOR					"gmchatmonitor"

// doubleitem_event <zone | server | all / subserver> <chat>
#define     GM_CMD_DOUBLE_ITEM_DROP					"doubleitem_event"          // ��� �˸� �޽���

// doublepetexp_event <serverno | all | cur> <start | stop | ing> <0~200%>
#define     GM_CMD_DOUBLE_PET_EXP					"doublepetexp_event"    // �� ����ġ 2��
// doubleattack_event <serverno | all | cur> <start | stop | ing> <0~200%>
#define     GM_CMD_DOUBLE_ATTACK					"doubleattack_event"    // ����, ���� ���ݷ� 2��

// event_dropitem <serverno | all | cur> <start | stop | ing> <npcidx> <itemidx> <prob>
#define     GM_CMD_EVENT_DROPITEM					"event_dropitem"

// kick_multi   <meter :m>
#define     GM_CMD_KICK_PC_MULTI					"kick_pc"

// silence_multi <meter :m>  <sec>
#define     GM_CMD_SILENCE_PC_MULTI					"silence_pc"

// set exp limit
#define     GM_CMD_SET_EXPLIMIIT					"exp_limit"

#define     GM_CMD_DOUBLE_EVENT_AUTO				"double_event_auto"

// upgrade_event <all | cur | serverno> <start | ing | stop> <100 | 125 | 150 | 175 | 200>
#define     GM_CMD_UPGRADE_EVENT					"upgrade_event"

// kickguildmember <guildname> <charname>
#define     GM_CMD_KICK_GUILDMEMBER					"kickguildmember"

// applyskill <skill index> <char name>
#define     GM_CMD_APPLY_SKILL						"applyskill"

// stateflag <state flag>
#define     GM_CMD_STATE_FLAG						"stateflag"

// date
#define		GM_CMD_DATE								"date"

// playtrigger <count> <playID> <playID> <playID> ...
#define     GM_CMD_PLAY_TRIGGER						"playtrigger"

// guildbattlestart <guildindex1> <guildindex2> <time>
#define		GM_CMD_BATTLE_START						"guildbattlestart"

// guildbattlestop <guildindex1> <guildindex2>
#define		GM_CMD_BATTLE_STOP						"guildbattleend"

// resetraid
#define     GM_CMD_RESET_RAID						"resetraid"

// setsealexp <level>
#define		GM_CMD_SET_SEAL_EXP						"setsealexp"

// endsubhelper // �������۸� ����
#define		GM_CMD_END_SUBHELPER					"endsubhelper"

// date
#define		GM_CMD_MY_ADMIN							"myadmin"

#define		GM_CMD_DT_TIMESET						"dt_timeset"
#define		GM_CMD_DT_EXPSET						"dt_expset"
#define		GM_CMD_DT_TIMEINTERVAL					"dt_timeinterval"
#define		GM_CMD_DT_TOGGLE						"dt_toggle"

#define     GM_CMD_RELOAD_CATALOG					"reload_catalog"
//#define		GM_CMD_RAID_TODO						"raidtodo"
#define		GM_CMD_NPC_DROP							"npcdrop"

#define     GM_CMD_GODBLESS							"godbless"
#define		GM_CMD_ENCHANT							"enchant"
#define		GM_CMD_RELOAD_PRICE						"reload_price"
#define		GM_CMD_MODIFY_CASHSHOP					"modifycashshop"
#define		GM_CMD_LCBALL_RESET						"lcball_reset"
#define		GM_CMD_ATTEVENT_2011					"attevent"
#define		GM_CMD_FUNC								"func"
#define		GM_CMD_ECHONPC							"echo_npc"
#define		GM_CMD_CASTLE_STATE_CYNC				"warcastlestatecync" // �������������� �ٸ� ä�� ��ũ�ϴ� ���ɾ�
#define		GM_CMD_TREASURE_MAP_DROP				"treasuremapdrop"
#define		GM_CMD_DEATH_EVENT						"deathevent"
#define		GM_CMD_ATTENDANCE_CHANGE				"attendance_change"
#define		GM_CMD_SET				                "set"
#define		GM_CMD_CRAFTPOINT		                "craftpoint"
#define		GM_CMD_EVENTAOUTOMATON	                "automationevent"
#define		GM_CMD_SKILLLEARN		                "skilllearn"
#define		GM_CMD_APET_HUNGRY		                "apet_hungry"
#define		GM_CMD_APET_FAITH		                "apet_faith"
#define		GM_CMD_COMPARE_BOXITEM	                "compare_boxitem"
#define		GM_CMD_GUILDMASTER_KICK_RESET			"kickreset"
#define		GM_CMD_GUILDMASTER_CHANGE				"changeboss"
// itemget <index> <plus> <flag> <count> <option_count> <option_type> <option_level>
#define		GM_CMD_JOBRESET							"jobreset"
// jobchange <jobtype> <2ndjobtype>
#define		GM_CMD_JOBCHANGE						"jobchange"
#define     GM_CMD_ITEMGET							"itemget"      // ������ ���� �κ� ����
// itemget <indexfrom> <indexto> <plus> <flag> <count> <option_count> <option_type> <option_level>
#define		GM_CMD_ITEMGETRANGE						"itemgetrange"	// �ε��� ���� ������ ���� �κ� ����
#define		GM_CMD_SERVER_TRANS_BLOCK				"trans_block" // ���� ���� �Ұ��� ���� ����
#define		GM_CMD_XMAS_PUZZLE						"xmaspuzzle"
#define		GM_CMD_ROYAL_RUMBLE_SETTING				"royalrumble"
#define		GM_CMD_AFFINITY_SET						"affinity_set"			//ģȭ�� ī��Ʈ ����
#define		GM_CMD_AFFINITY_REWARD_INIT				"affinity_reward_init"	//ģȭ�� ���� �ʱ�ȭz
#define		GM_CMD_NAS_SET							"nas_set"				//���� ����
#define		GM_CMD_JEWELRYE							"jewelrye"				//���� ���� �̺�Ʈ�� ����
#define     GM_CMD_JEWEL_LOAD						"jewel_load"
#define		GM_CMD_CRASH							"scrash"				// �׽�Ʈ�� ���� ������ ������ ũ������Ŵ
#define		GM_CMD_NOT_GM							"notgm"					// ���������� GM�� �ƴ� ���·� �����. �ٽ� GM�� �Ƿ��� �� ����
#define		GM_CMD_TRADEAGENT_FEE					"fee"					// �ŷ����� ������
#define		GM_CMD_TRADEAGENT_DEPOSIT				"deposit"				// �ŷ����� ������
#define		GM_CMD_GO_ZONE_FINDNPC					"go_zone_npc"			// npc�� �����ϴ� ������ �̵�
#define		GM_CMD_STASHGETRANGE					"stashgetrange"			// â�� ä���
#define		GM_CMD_STASHDEL							"stashdel"				// â�� ����
#define		GM_CMD_TIMERITEM_SET					"timeritem_set"			// �Ⱓ�� �������� �ð��� ����
#define		GM_CMD_PICKUP_ITEM						"pickupitem"			// ĳ���� �ֺ��� �������� �ڵ����� �ݱ�
#define		GM_CMD_MONSTER_MERCEARY					"monstercard"
#define		GM_CMD_VIEW_ALL_SHOP_LIST				"sshoplist"				// NPC�� ����ִ� �Ǹ� ����� ������
#define		GM_CMD_DEL_CHARACTER					"delchar"				// �ڽ� ������ �ٸ� ĳ���͸� �ٷ� �����ش�.
#define		GM_CMD_LOGOUT							"logout"				// ĳ���� ����â���� �̵�
#define		GM_CMD_EXP								"exp"					// ���� exp�� �����Ѵ�.
#define		GM_CMD_GO_NEXT_PC						"go_nextpc"				// ���� ���� �����ϴ� �ٸ� ĳ���Ϳ��� �����ϰ� �̵� (���̰� ��û)
#define		GM_CMD_VIRTUAL_REFORM					"vreform"				// �������� ������ ������
#define		GM_CMD_ROCK_PAPER_SCISSORS_WIN			"rpswin"				// ���������� ���ӿ��� ������ �̱�� ��

#define		GM_CMD_RVR_INCREASE_POINT				"rvr_inc"				// �⿩�� ����
#define		GM_CMD_RVR_DECREASE_POINT				"rvr_dec"				// �⿩�� ����

#define		GM_CMD_THEOS_CHECK_REWARD_ITEM			"timeset_theos"			// ���� üũ �ð� ����(���� �ð�)
#define		GM_CMD_THEOS_CHECK_POLLUTION			"theos_pollution"		// ���� ������ ���� ����
#define		GM_CMD_THEOS_CHECK_DIFFICULTY			"theos_difficulty"		// ���� �¼��� ���� ����

#ifdef DURABILITY
#define		GM_CMD_DURABILITY						"dur"					// ��� ������ : tab_no, invenIndex, now_dur, max_dur
#endif

#define		GM_CMD_RVR_APPLYSKILL					"rvr_applyskill"		// 1�ð����� �ɸ��� ���� �ٷ� �ֱ�
#define		GM_CMD_RVR_SHOWJEWELPOINT				"rvr_show"				// 1�ð����� �ɸ��� ���� �ٷ� �ֱ�
#define		GM_CMD_RVR_SET_USERCOUNT				"rvr_setuser"			// ���� �����ڼ� ������ ����
#define		GM_CMD_RVR_SHOW_USERCOUNT				"rvr_showuser"			// ����ī��Ʈ ��ȸ

#define		GM_CMD_ALL_ITEM_TIME_SET				"itemused_set"			// �κ��丮�� �ִ� ��� �������� used ���� �ٲپ� �ش�.
#define		GM_CMD_GET_EXCHANGE_ITEM				"exchangeitem"			// ��ȯ�� �ʿ��� �������� �ѹ��� ���
#define		GM_CMD_NO_SPECIAL_BOX_COOLTIME			"nocoolbox"				// ����� �ڽ� ������ �ݱ� ��Ÿ�� ����

#ifdef PREMIUM_CHAR
#define		GM_CMD_PRIMIUM_CHAR_RESET				"pc_reset"				// �����̾� ĳ���� �ʱ�ȭ
#define		GM_CMD_PRIMIUM_CHAR_SET_EXPIRE_TIME		"pc_expiretime"			// �����̾� ĳ���� ��ȿ �ð� ����
#define		GM_CMD_PRIMIUM_CHAR_SET_JUMP_COUNT		"pc_jumpcount"			// ĳ������ ���� ���� ����
#define		GM_CMD_PRIMIUM_CHAR_SET_TYPE			"pc_type"				// �����̾� Ÿ�� ����
#endif

#define		GM_CMD_ATTENDANCE_ASSURE_EXPIRE_TIME	"at_expiretime"			// �⼮ �������� ���� �ð� ����
#define		GM_CMD_RAID_CHANGE_MAX_AREA_COUNT		"change_area_max"		// area MaxCount ����
#define		GM_CMD_POPUP_NOTICE						"popup"
#define		GM_CMD_POPUP_NOTICEOFF					"popupoff"
#define		GM_CMG_MASTERSTONE_PROB					"masterstoneprob"
#define		GM_CMD_GUILD_BATTLE_CORE				"g_battle_score"
#define		GM_CMD_GUILD_BATTLE_LIST				"g_battle_ing"

#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
#define            GM_CMD_SPAWN_RAID_NPC            "spawn_raid_npc"
#endif
#define		GM_CMD_TEST_COMMAND						"test"					// �׽�Ʈ ���ɾ�

#define		GM_CMD_GUILD_MEMBER_OUT_TIME			"g_m_out_time"
#define		GM_CMD_GUILD_CREATE_TIME				"g_c_time"
#define		GM_CMD_RESERVED_GM_COMMAND				"reserve_gm"
#define		GM_CMD_TOGGLE_BUFF						"autobuff"
#define     GM_CMD_RELOAD_JOB_DAMAGE                "reload_job_damage"
#define     GM_CMD_SERVER_CONFIG                    "server_config"
#define     GM_CMD_UPDATE_EVENT                     "update_event"
#define     GM_CMD_RELOAD_BATTLE_WARFARE            "battle_warfare"
#define		GM_CMD_DONATION_EVENT					"donation_event"
#define     GM_CMD_SPAWN_NPC                        "spawn_npc"
#define     GM_CMD_SPAWN_SHOP                       "spawn_shop" //dethunter12 spawn shop
#define     GM_CMD_BAN_PLAYER                       "ban_player"
#define     GM_CMD_BLOCK_PLAYER                     "block_player"
#define		GM_CMD_RLGL								"rlgl"
#define     GM_CMD_REZAP                            "rezap" //poplock reza pwesty
#define     GM_CMD_HACK_WATCH						"reload_hackwatch"
// �� ���� ���� ��� ���� ���� ����

#define     GM_LEVEL_ROLE_ADMIN              10
#define     GM_LEVEL_ROLE_GAME_SERVER        3

#define     GM_LEVEL_RELOAD_JOB_DAMAGE  10
#define     GM_LEVEL_UPDATE_EVENT       10

#define		GM_LEVEL_MY_ADMIN			1
#define		GM_LEVEL_DT_TIMESET			10
#define		GM_LEVEL_DT_TIMEINTERVAL	10
#define		GM_LEVEL_DT_TOGGLE			10
#define     GM_LEVEL_RELOAD_CATALOG     10
//#define		GM_LEVEL_RAID_TODO			10
#define		GM_LEVEL_NPC_DROP			10
#define     GM_LEVEL_GODBLESS           5
#define		GM_LEVEL_ENCHANT			10
#define		GM_LEVEL_MODIFY_CASHSHOP	10
#define		GM_LEVEL_RAIDINZONE			10
#define		GM_LEVEL_ATTEVENT_2011		10
#define		GM_LEVEL_FUNC				10
#define		GM_LEVEL_CASTLE_STATE_CYNC	10
#define		GM_LEVEL_TREASURE_MAP_DROP	10
#define		GM_LEVEL_DEATH_EVENT		10
#define		GM_LEVEL_ATTENDANCE_CHANGE	7
#define		GM_LEVEL_SET				10
#define		GM_LEVEL_CRAFTPOINT			10
#define		GM_LEVEL_EVENTAOUTOMATON	10
#define		GM_LEVEL_SKILLLEARN			10
#define		GM_LEVEL_APET_HUNGRY		10
#define		GM_LEVEL_APET_FAITH			10
#define		GM_LEVEL_COMPARE_BOXITEM	10
#define		GM_LEVEL_GUILD_MASTER_KICK_RESET	10
#define		GM_LEVEL_GUILD_MASTER_CHANGE		10
#define		GM_LEVEL_TRANS_BLOCK		10
#define		GM_LEVEL_XMAS_PUZZLE		10
#define		GM_LEVEL_ROYAL_RUMBLE_SETTING 10
#define		GM_LEVEL_AFFINITY_SET			10
#define		GM_LEVEL_AFFINITY_REWARD_INIT	10
#define		GM_LEVEL_NAS_SET				10
#define		GM_LEVEL_JEWEL_EVENT			10
#define		GM_LEVEL_CRASH					10
#define		GM_LEVEL_NOT_GM					10
#define		GM_LEVEL_TRADEAGENT_FEE					10
#define		GM_LEVEL_TRADEAGENT_DEPOSIT				10


//�˾� ���� ���� ����
#define		GM_POPUP_NOTICE_ALL			"all"
#define		GM_POPUP_NOTICE_SERVER		"servernumber"
#define		GM_POPUP_NOTICE_SUB_SERVER	"subserver"
#endif
