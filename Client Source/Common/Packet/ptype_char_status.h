#ifndef __PTYPE_CHAR_STATUS_H__
#define __PTYPE_CHAR_STATUS_H__

#include "ptype_base.h"
enum
{
	eArti_Str,
	eArti_Dex,
	eArti_Int,
	eArti_Con,
	eArti_MAX,
};

enum
{
	MSG_SUB_UPDATE_FIRST_MONENY,			// ��(����) ��ȭ
	MSG_SUB_UPDATE_FIRST_MONENY_IN_STASH,	// â�� ��(����) ��ȭ
	MSG_SUB_UPDATE_MONENY,				// ��(����) ��ȭ
	MSG_SUB_UPDATE_MONENY_IN_STASH,		// â�� ��(����) ��ȭ

	MSG_SUB_UPDATE_INVEN_LIST,			// ���� ������ ����Ʈ (Ŭ�󿡼��� ���� �����͸� ����� ������ �� ������ ����)

	MSG_SUB_UPDATE_ADD_ITEM,			// 1���� �������� �űԷ� �߰���
	MSG_SUB_UPDATE_DELETE_ITEM,			// 1���� ������ ����
	MSG_SUB_UPDATE_CHANGE_ITEM_COUNT,	// 1���� �������� ������ ��ȭ��
	MSG_SUB_UPDATE_CHANGE_ITEM_COUNT_WITH_SWAP,	// 1���� �������� ������ ��ȭ��

	MSG_SUB_UPDATE_CHANGE_ITEM_PLUS,
	MSG_SUB_UPDATE_CHANGE_ITEM_PLUS_2,
	MSG_SUB_UPDATE_CHANGE_ITEM_FLAG,
	MSG_SUB_UPDATE_CHANGE_ITEM_USED,
	MSG_SUB_UPDATE_CHANGE_ITEM_USED_2,
	MSG_SUB_UPDATE_CHANGE_ITEM_WEAR_POS,
	MSG_SUB_UPDATE_CHANGE_ITEM_OPTION,
	MSG_SUB_UPDATE_CHANGE_ITEM_SOCKET,
	MSG_SUB_UPDATE_CHANGE_ITEM_ORIGIN_VAR,
	MSG_SUB_UPDATE_CHANGE_ITEM_COMPOSITE_ITEM,

	MSG_SUB_UPDATE_NAS_DESC_REASON,			// �� ���� ����

	MSG_SUB_UPDATE_OLD_TIMER_ITEM,
	MSG_SUB_UPDATE_ERASE_ALL_ITEM,

	MSG_SUB_UPDATE_WEAR,					// ��� ����
	MSG_SUB_UPDATE_WEAR_TAKEOFF,			// ��� Ż��
	MSG_SUB_UPDATE_WEAR_LIST,				// ��� ����Ʈ
	MSG_SUB_UPDATE_WEAR_CHANGE_INFO,		// ��� ���� ����

	MSG_SUB_UPDATE_COST_WEAR,				// �ڽ�Ƭ ����
	MSG_SUB_UPDATE_COST_WEAR_TAKEOFF,		// �ڽ�Ƭ Ż��
	MSG_SUB_UPDATE_COST_WEAR_LIST,			// �ڽ�Ƭ ��� ����Ʈ

	MSG_SUB_UPDATE_COST_WEAR_SUIT,			// �ڽ�Ƭ �ѹ��ǻ� ����

	MSG_SUB_UPDATE_CHANGE_WEAR_ITEM_USED,	// ���� ������ USE ������Ʈ
	MSG_SUB_UPDATE_CHANGE_WEAR_ITEM_PLUS,	// ���� ������ PLUS ������Ʈ
	MSG_SUB_UPDATE_CHANGE_WEAR_ITEM_FLAG,	// ���� ������ FLAG ������Ʈ

	MSG_SUB_UPDATE_STASH_PASSWORD_FLAG,		// â�� �н����� ����

#ifdef DURABILITY
	MSG_SUB_UPDATE_ITEM_DURABILITY_FOR_INVENTORY,
	MSG_SUB_UPDATE_ITEM_DURABILITY_FOR_WEAR,
#endif

	MSG_SUB_UPDATE_STATUS = 100,		// ĳ���� ����(���)
	MSG_SUB_UPDATE_AT,
	MSG_SUB_UPDATE_APPEAR_PC,
	MSG_SUB_UPDATE_APPEAR_NPC,
	MSG_SUB_UPDATE_APPEAR_PET,
	MSG_SUB_UPDATE_APPEAR_ELEMENTAL,
	MSG_SUB_UPDATE_APPEAR_APET,
	
	MSG_SUB_UPDATE_DISAPPERAR,
	MSG_SUB_UPDATE_DISAPPERAR_FOR_CLIENT_EFFECT,
	MSG_SUB_UPDATE_DISAPPERAR_ALL,		//Ŭ���̾�Ʈ���� ĳ���͸� �������� ������ �ִ� ��� ���� ������ �ϴ� ���� �Ϲ����� DISAPPEAR�ʹ� �ٸ�
	MSG_SUB_UPDATE_TARGET_CLEAR,

	MSG_SUB_UPDATE_ELEMENTAL_STATUS,
	MSG_SUB_UPDATE_EXPED_INFO,
	MSG_SUB_UPDATE_PARTY_INFO,

	MSG_SUB_UPDATE_CHAR_STATUS_PC,
	MSG_SUB_UPDATE_CHAR_STATUS_NPC,
	MSG_SUB_UPDATE_CHAR_STATUS_PET,
	MSG_SUB_UPDATE_CHAR_STATUS_ELEMENTAL,
	MSG_SUB_UPDATE_CHAR_STATUS_APET,

	MSG_SUB_UPDATE_DAMAGE,
	MSG_SUB_UPDATE_APET_SMALL_STATUS,

	MSG_SUB_UPDATE_LEVELUP_INFO,

	MSG_SUB_UPDATE_TARGET_HP_INFO,

	MSG_SUB_UPDATE_HOLYWATER_STATE,

#ifdef PREMIUM_CHAR
	MSG_SUB_UPDATE_PREMIUM_CHAR_INFO,
	MSG_SUB_UPDATE_PREMIUM_CHAR_JUMP_COUNT,
	MSG_SUB_UPDATE_PREMIUM_CHAR_END,

	MSG_SUB_UPDATE_PREMIUM_CHAR_CHANGE_FLAG,		// �����̾� ĳ���� ���� ����
#endif


	MSG_SUB_UPDATE_ATTR_ITEM_USE,
	MSG_SUB_UPDATE_ATTR_STATE_FOR_NPC,

	MSG_SUB_UPDATE_CHECK_NOTICE,			//���� Ȯ�� ������
	MSG_SUB_UPDATE_CHECK_POPUP_NOTICE,		//�˾� ���� Ȯ��
	MSG_SUB_UPDATE_CLOSE_POPUP_NOTICE,		//�˿� ���� ����
	MSG_SUB_UPDATE_CLEAR_POPUP_NOTICE,		//�˾� ��ü ����

	MSG_SUB_UPDATE_ARTIFACT_SYSMSG,
	MSG_SUB_UPDATE_ARTIFACT_FIND_USER_COUNT_MSG,

	MSG_SUB_REQUEST_GUILD_RECALL,			//�������� �����鿡�� ���� ���� Ȯ�� ���� ��û ������Ʈ ��Ŷ

	MSG_SUB_UPDATE_SETTINGS,

	MSG_SUB_UPDATE_EP_INIT,					//�̱״ϼ� ����Ʈ �ʱ�ȭ

	MSG_SUB_UPDATE_CHAR_HPMP,

    MSG_SUB_UPDATE_CHAR_CURR_HP, //dethunter12 add update hp status
};

#pragma pack(push, 1)
//////////////////////////////////////////////////////////////////////////
struct tag_assistinfo // �� ����ü�� �����ϴ� ����ü������ �׻� �� �������� ����Ұ� (0�迭����)
{
	LONGLONG		state;
	int				count;
	struct tag_list
	{
		int			index;
		int			dbIndex;
		char		level;
		int			remain;
		int			remainCount;
	} list[0];
};

namespace UpdateClient
{
struct oldTimerItem : public pTypeBase
{
	int memposTime;		// �޸� ��ũ��
	int stashextTime;	// ����â�� Ȯ��
};

struct stashPasswordFlag : public pTypeBase
{
	unsigned char		flag;		// 0 - ���� , 1 - ����
};

struct charStatus : public pTypeBase
{
	int				level;
	LONGLONG		exp;
	LONGLONG		levelupExp;
	int				hp;
	int				maxHp;
	int				maxHpOrg;
	int				mp;
	int				maxMp;
	int				maxMpOrg;
	unsigned char	attrDef;
	unsigned char	attrAtt;
	int				str;
	int				dex;
	int				intl;
	int				con;
	int				stats_addition;
	int				opStr;
	int				opDex;
	int				opInt;
	int				opCon;
	int				attack;
	int				attack_diff;
	int				magic;
	int				magic_diff;
	int				defense;
	int				defense_diff;
	int				resist;
	int				resist_diff;
	int				avoid_melee;
	int				avoid_melee_org;
	int				avoid_magic;
	int				avoid_magic_org;
	int				fhitrate_melee;
	int				fhitrate_melee_org;
	int				fhitrate_magic;
	int				fhitrate_magic_org;
	int				critical;
	int				critical_org;
	int				deadly;
	int				deadly_org;
	LONGLONG		skillPoint;
	float			walkSpeed;

	float			run_or_fly_speed;
	float			run_or_fly_speed_org;

	char			attackSpeed;
	char			attackSpeedOrg;

	char			magicSpeed;
	char			pkName;
	int				pkPenalty;
	int				pkCount;
	int				fame;
	float			attackRange;

	char			joinForMerac;
	char			joinForDratan;
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	int				m_cloud_PartyDGCompleteData[5];
	int				m_cloud_PartyDGTitleRewardData[5];
#endif
#ifdef QUICK_PANEL
	int				m_cloud_m_QuickPanelBtnType[25];
	int				m_cloud_m_QuickPanelBtnIdx[25];
#endif
	int				skillSpeed;
	unsigned short	mapAttr;
	char			mountPet;
	char			colorType;
	int				evocationIndex;
	int				remainEvocation;
	
	char			bPressCorps;
	char			a_botting; //REZABOT
	int				prob;

	int				ep;
	int				maxEp;

	int				a_wins;
	int				a_loses;
	int				a_honor;
	int				autopickup;
	int				autoigni;
	int				autosell;
	int				reborn;
	int				color_name;
	
	int				opResistStone;
	int				opResistSturn;
	int				opResistSilent;
	int				opabsorbPVPDamageRate;
	int				opDecreaseSkillMP;

	int				party_arti[eArti_MAX];

	int				opMoney_buy_addition;
	int				opMoney_buy_rate;
	int				opMoney_sell_addition;
	int				opMoney_sell_rate;
};

struct charAtMsg : public pTypeBase
{
	int				charIndex;
	char			charName[MAX_CHAR_NAME_LENGTH + 1];
	unsigned char	job;
	unsigned char	job2;
	unsigned char	hairstyle;
	unsigned char	facestyle;
	int				zoneIndex;
	int				areaIndex;
	float			x;
	float			z;
	float			h;
	float			r;
	char			yLayer;
	int				userIndex;
	int				guildindate;
	char			plusEffect;
	unsigned short	mapAttr;

	int				key;
	int				currentTitle;

	int				chatingFlag;

#ifdef ENABLE_SUBJOB
	int				jobSub;
#endif
};

struct elementalStatus : public pTypeBase
{
	int				charIndex;
	char			charType;
	int				remainTime;
	int				hp;
	int				maxHp;
	char			attackSpeed;
	char			magicSpeed;
	int				skillSpeed;
	float			walkSpeed;
	float			runSpeed;
	float			attackRange;
	float			x;
	float			z;
	float			h;
	float			r;
	char			yLayer;
	unsigned short  mapAttr;

	tag_assistinfo	assistinfo;
};

struct expedInfoForChar : public pTypeBase
{
	int				charIndex;
	int				group;
	int				level;
	int				hp;
	int				maxHp;
	int				mp;
	int				maxMp;
	float			x;
	float			z;
	char			yLayer;
	int				zoneIndex;
	bool			isOnline;
};

struct partyInfo : public pTypeBase
{
	int				charIndex;
	int				level;
	int				hp;
	int				maxHp;
	int				mp;
	int				maxMp;
	float			x;
	float			z;
	char			yLayer;
	int				zoneIndex;
	bool			isOnline;
};

struct attackPetStatus : public pTypeBase
{
	int				charIndex;
	char			charName[MAX_CHAR_NAME_LENGTH + 1];
	int				level;
	int				protoType;
	bool			isMount;
	char			transSate;

	int				coolTime;
	LONGLONG		accExp;

	LONGLONG		exp;
	LONGLONG		needExp;
	int				hp;
	int				maxHp;
	int				mp;
	int				maxMp;
	int				faith;
	int				maxFaith;
	int				stamina;
	int				maxStamina;
	int				str;
	int				addStr;
	int				con;
	int				addCon;
	int				dex;
	int				addDex;
	int				intl;
	int				addIntl;
	int				remainStat;
	int				attack;
	int				magicAttack;
	int				defence;
	int				maxDefence;
	int				hitPoint;
	int				avoid;
	float			x;
	float			z;
	float			h;
	float			r;
	char			yLayer;
	unsigned short	mapAttr;
};

struct charStatusPc : public pTypeBase
{
	int			charIndex;
	int			hp;
	int			maxHp;
	int			mp;
	int			maxMp;
	int			pkPenalty;
	char		pkName;
	LONGLONG	state;
	LONGLONG	state2;
    char		botting;
	int				a_wins;
	int				a_loses;
};
struct charStatusHPMP : public pTypeBase
{
	int			charIndex;
	int			hp;
	int			maxHp;
	int			mp;
	int			maxMp;	
};

struct charCurrHPMP : public pTypeBase
{
	int			charIndex;
	int			hp;
	int			maxHp;
};

struct charStatusNpc : public pTypeBase
{
	int			charIndex;
	int			hp;
	int			maxHp;
	int			mp;
	int			maxMp;
	LONGLONG	state;
	LONGLONG	state2;

	int			ownerIndex;
	int			classIndex;
	int			melee;
	int			defence;
	int			magic;
	int			resist;
};

struct charStatusPet : public pTypeBase
{
	int			charIndex;
	int			hp;
	int			maxHp;
	int			mp;
	int			maxMp;
	LONGLONG	state;
	LONGLONG	state2;
};

struct charStatusElemental : public pTypeBase
{
	int			charIndex;
	int			hp;
	int			maxHp;
	int			mp;
	int			maxMp;
	LONGLONG	state;
	LONGLONG	state2;
};

struct charDamage : public pTypeBase
{
	char		damageType;

	char		charType;
	char		targetType;
	int			charIndex;
	int			targetIndex;

	int			skillIndex;
	int			targetHp;
	int			targetMp;
	int			damage;
	char		attackSpeed;
	char		flag;
	int			holyitemIndex;
};

struct charDisappear : public pTypeBase
{
	char		charType;
	int			charIndex;
};


struct charDisappearForClientEffect : public pTypeBase
{
	int			charIndex;
	int			owner_index;
};

struct charDisappearAll : public pTypeBase
{
};

struct targetClear : public pTypeBase
{
	int targetIndex;
};

struct attackPetSmallStatus : public pTypeBase
{
	int				charIndex;
	char			charName[MAX_CHAR_NAME_LENGTH + 1];
	int				level;
	int				str;
	int				con;
	int				dex;
	int				intl;

	int				coolTime;
	LONGLONG		accExp;
};

struct LevelupInfo : public pTypeBase
{
	int level;
};

struct charHpInfo : public pTypeBase
{
	int charIndex;
	int hp;
	int maxHp;
};

struct holyWaterState : public pTypeBase
{
	int charIndex;
	int holyWaterItemIndex;
};

struct settings : public pTypeBase
{
	int autopickup;
	int autoigni;
	int autosell;
};

struct AttrItemUse : public pTypeBase
{
	char state_type;			//0 NONE, 1 ATTACK, 2DEFENCE
	unsigned char attr;			//attribute
};

struct AttrNpcStateInfo : public pTypeBase
{
	int npc_index;
	char state_type;			//0 NONE, 1 ATTACK, 2DEFENCE
	unsigned char attr;			//attribute
};

struct GuildRoomRecall : public pTypeBase
{
};

struct EPInit : public pTypeBase
{
	bool isInit;				//true = �ʱ�ȭ, false = ����
};

#ifndef _CLIENT_
inline void makeOldTimerItem(CNetMsg::SP& msg, int mempos, int stashext)
{
	oldTimerItem* packet = reinterpret_cast<oldTimerItem*>(msg->m_buf);
	packet->type = MSG_UPDATE_DATA_FOR_CLIENT;
	packet->subType = MSG_SUB_UPDATE_OLD_TIMER_ITEM;
	packet->memposTime = mempos;
	packet->stashextTime = stashext;
	msg->setSize(sizeof(oldTimerItem));
}

inline void makeStashPasswordFlag(CNetMsg::SP& msg, unsigned char flag)
{
	stashPasswordFlag* packet = reinterpret_cast<stashPasswordFlag*>(msg->m_buf);
	packet->type = MSG_UPDATE_DATA_FOR_CLIENT;
	packet->subType = MSG_SUB_UPDATE_STASH_PASSWORD_FLAG;
	packet->flag = flag;
	msg->setSize(sizeof(stashPasswordFlag));
}

inline void makeLevelupInfo(CNetMsg::SP& msg, int level)
{
	LevelupInfo* packet = reinterpret_cast<LevelupInfo*>(msg->m_buf);
	packet->type = MSG_UPDATE_DATA_FOR_CLIENT;
	packet->subType = MSG_SUB_UPDATE_LEVELUP_INFO;
	packet->level = level;
	msg->setSize(sizeof(LevelupInfo));
}
inline void CharHpInfoMsg(CNetMsg::SP& msg, int charIndex, int maxHp, int hp)
{
	charHpInfo* packet = reinterpret_cast<charHpInfo*>(msg->m_buf);
	packet->type = MSG_UPDATE_DATA_FOR_CLIENT;
	packet->subType = MSG_SUB_UPDATE_TARGET_HP_INFO;
	packet->charIndex = charIndex;
	packet->maxHp = maxHp;
	packet->hp = hp;

	msg->setSize(sizeof(charHpInfo));
}
inline void holyWaterStateMsg(CNetMsg::SP& msg, int charIndex, int holyWaterItemIndex)
{
	holyWaterState* packet = reinterpret_cast<holyWaterState*>(msg->m_buf);
	packet->type = MSG_UPDATE_DATA_FOR_CLIENT;
	packet->subType = MSG_SUB_UPDATE_HOLYWATER_STATE;
	packet->charIndex = charIndex;
	packet->holyWaterItemIndex = holyWaterItemIndex;
	msg->setSize(sizeof(holyWaterState));
}
inline void AttrItemUseMsg(CNetMsg::SP& msg, int type, unsigned char attr)
{
	AttrItemUse* packet = reinterpret_cast<AttrItemUse*>(msg->m_buf);
	packet->type = MSG_UPDATE_DATA_FOR_CLIENT;
	packet->subType = MSG_SUB_UPDATE_ATTR_ITEM_USE;	//127
	packet->state_type = type;
	packet->attr = attr;
	msg->setSize(sizeof(AttrItemUse));
}
inline void AttrNpcStateMsg(CNetMsg::SP& msg, int type, unsigned char attr, int npc_index)
{
	AttrNpcStateInfo* packet = reinterpret_cast<AttrNpcStateInfo*>(msg->m_buf);
	packet->type = MSG_UPDATE_DATA_FOR_CLIENT;
	packet->subType = MSG_SUB_UPDATE_ATTR_STATE_FOR_NPC;	//128
	packet->state_type = type;
	packet->attr = attr;
	packet->npc_index = npc_index;
	msg->setSize(sizeof(AttrNpcStateInfo));
}
inline void GuildRoomRecallRequestMsg(CNetMsg::SP& msg)
{
	GuildRoomRecall* packet = reinterpret_cast<GuildRoomRecall*>(msg->m_buf);
	packet->type = MSG_UPDATE_DATA_FOR_CLIENT;
	packet->subType = MSG_SUB_REQUEST_GUILD_RECALL;
	msg->setSize(sizeof(GuildRoomRecall));
}

inline void EPInitMsg(CNetMsg::SP& msg, bool isInit)
{
	EPInit* packet = reinterpret_cast<EPInit*>(msg->m_buf);
	packet->type = MSG_UPDATE_DATA_FOR_CLIENT;
	packet->subType = MSG_SUB_UPDATE_EP_INIT;
	packet->isInit = isInit;
	msg->setSize(sizeof(EPInit));
}

inline void CharStatusHPMP(CNetMsg::SP& msg, int max_hp, int hp, int max_mp, int mp)
{
	charStatusHPMP* packet = reinterpret_cast<charStatusHPMP*>(msg->m_buf);
	packet->type = MSG_UPDATE_DATA_FOR_CLIENT;
	packet->subType = MSG_SUB_UPDATE_CHAR_HPMP;
	packet->maxHp = max_hp;
	packet->hp = hp;
	packet->maxMp = max_mp;
	packet->mp = mp;
	msg->setSize(sizeof(charStatusHPMP));
}
#endif
}
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif

