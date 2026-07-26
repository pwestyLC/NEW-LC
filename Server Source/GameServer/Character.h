#ifndef __ACHARACTER_H__
#define __ACHARACTER_H__

#include <math.h>
#include <map>
#include <vector>
#include <set>

#include "../ShareLib/MemoryPoolBase.h"
#include "../ShareLib/gm_command.h"
#include "NPCProto.h"

#include "APetProto.h"

#include "NPCRegenInfo.h"
#include "Item.h"
#include "CPos.h"
#include "ExchangeItems.h"
#include "MemPos.h"
#include "Party.h"
#include "Skill.h"
#include "Assist.h"
#include "Quest.h"
#include "SSkill.h"
#include "PersonalShop.h"
#include "Expedition.h"
#include "TimerItemManager.h"
#include "InventoryManager.h"
#include "WearInvenManager.h"
#include "GPSManager.h"
#include "LootFilterSystem.h"

#include "Factory.h"            // ���� �ý���

#include "Affinity.h"

#include "TitleSystem.h"
#include "MonsterMercenary.h"

#include "RockPaperScissorsInfo.h"

#include "PetStashManager.h"

#include "SyndicateManager.h"
#include "ItemCollection.h"
#include "attendanceManager.h"

#ifdef PREMIUM_CHAR
#include "PremiumChar.h"
#endif

#include "../ShareLib/packetType/ptype_old_do_title.h"

//PASSIVE_SYSTEM
#include "PassiveSystem.h" //new 16-08-2022

#include "../ShareLib/packetType/ptype_old_do_title.h"
#include "../ShareLib/Config.h"
typedef struct _HonorKill
{
	int char_index;
	time_t  tm_kill;
} HonorKill;
typedef struct __tagAutoGiveData
{
	int         nIndex;
	int         nPlus;
	int         nUsed;
	int         nFlag;
	LONGLONG    nCount;
	short       nOption[MAX_ITEM_OPTION];
	char        strSerial[MAX_SERIAL_LENGTH + 1];
} AUTO_GIVE_DATA;

typedef struct __tagBloodBugData
{
	int         nIndex;
	int         nFlag;
	int         nOptionCount;
	short       nOption[MAX_ITEM_OPTION];
	char        strSerial[MAX_SERIAL_LENGTH + 1];
} BLOOD_BUG_DATA;

typedef struct __tagMonsterComboData
{
	int         nIndex;
	int         nStep;
} MONSTER_COMBO_DATA;

typedef struct __tagSealSkillData
{
	int         nSkillIdx;
	CSkill *    pSkill;
	LONGLONG    llExp;
} SEAL_SKILL_DATA;

struct MAKE_TITLE
{
	int			title_index;
	char		color;
	char		background_color;
	int			effect;
	char		name[CUSTOM_TITLE_NAME_LENGTH];
	int*		option_index;
	int*		option_level;
};

typedef std::set<CNPC*>	set_npc_t;
typedef std::vector<MONSTER_COMBO_DATA> vec_monster_combo_data_t;

class CDescriptor;
class CZone;
class CArea;
class CNetMsg;
class CGuild;
class CGuildMember;
class CWarCastle;
class CPet;
class CElemental;
class CAPet;
class CFriend;
class CFriendMember;

extern void DelAttackList(CCharacter* ch);
extern void DelRaList(CPC* pc, bool bForce = false);

#define SUMMON_NPC_MERCENARY_MAX	1		// ���� �뺴
#define SUMMON_NPC_TOTEM_MAX		1		// ������
#define SUMMON_NPC_BOMB_MAX			3		// Ʈ����, ������ ���� ����Ѵ�.
#define SUMMON_NPC_ITEM_TOTEM_MAX	1		// ������ ������
#define SUMMON_NPC_MAX				SUMMON_NPC_TOTEM_MAX + SUMMON_NPC_MERCENARY_MAX + SUMMON_NPC_BOMB_MAX + SUMMON_NPC_ITEM_TOTEM_MAX

#define PC_MAX_RUNSPEED 40.0f

typedef enum _tagSummonNpcType
{
	SUMMON_NPC_TYPE_MERCENARY = 0,
	SUMMON_NPC_TYPE_TOTEM,
	SUMMON_NPC_TYPE_BOMB_1,	// Ʈ��, ������.
	SUMMON_NPC_TYPE_BOMB_2,	// Ʈ��, ������.
	SUMMON_NPC_TYPE_BOMB_3,	// Ʈ��, ������.
	SUMMON_NPC_TYPE_TOTEM_ITEM,	//�������� �̿��� ��ȯ ����
} SUMMON_NPC_TYPE;

class CBlockPC
{
	int m_index;
	CLCString m_name;

public:
	CBlockPC(int index, const char* name) : m_name(MAX_CHAR_NAME_LENGTH +1)
	{
		m_index = index;
		m_name = name;
	}
	~CBlockPC() {};

	int GetIndex()
	{
		return m_index;
	}
	const char* GetName()
	{
		return m_name;
	}
	void SetName(const char* name)
	{
		m_name = name;
	}
};

class CQuickSlot
{
public:
	CQuickSlot()
	{
		clear();
	}

	// ���� Ÿ�� : �׼�, ��ų, ������ �� �ϳ�
	int     m_slotType[QUICKSLOT_MAXSLOT];

	// ������ ����
	int     m_skillType[QUICKSLOT_MAXSLOT]; // ��ų Ÿ��
	int     m_actionType[QUICKSLOT_MAXSLOT];// �׼� Ÿ��
	CItem*  m_item[QUICKSLOT_MAXSLOT];      // ������ ����

	void clear()
	{
		memset(m_slotType, -1, sizeof(m_slotType));
		memset(m_skillType, -1, sizeof(m_skillType));
		memset(m_actionType, -1, sizeof(m_actionType));
		memset(m_item, 0, sizeof(m_item));
	}
};

class CHackCheck
{
public:
	CHackCheck()
	{
		m_df = NULL;
		m_of = NULL;
		m_hackAttackCount = 0;
		m_AttackServerTime = 0;
		m_AttackClientTime = 0;
		m_lastAttackPulse = 0;
		m_hackCount = 0;
	}

	bool IncreaseHackCount(int n);

	CPC* m_of;
	CPC* m_df;
	int m_hackAttackCount;
	int m_AttackServerTime;
	int m_AttackClientTime;
	int m_lastAttackPulse;
	int m_hackCount;
};


class CReturnReward
{
public:
	CReturnReward()
	{
		m_index = 0;
		m_item_index = 0;
		m_catalog_index = 0;
	}
	~CReturnReward(){}

	int m_index;
	int	m_item_index;
	int	m_catalog_index;
};
#ifdef QUEST_AUTO_EVENT_06062022

class CQuestReward
{
public:
	CQuestReward()
	{
		m_index = 0;
		m_zone_num = 0;
		m_mob_index = 0;
		m_mob_kill_count = 0;
		m_item_index = 0;
		m_item_count = 0;
	}
	~CQuestReward() {}

	int m_index;
	int m_zone_num;
	int m_mob_index;
	int m_mob_kill_count;
	int	m_item_index;
	int	m_item_count;
	
};
#endif
// Attack List Class
class CAttackChar
{
public:
	CAttackChar()
	{
		ch = NULL;
		pc = NULL;
		npc = NULL;

		m_next = NULL;
		m_prev = NULL;

		m_damage = 0;
		m_targetHate = 0;
		m_targetPulse = 0;

		m_bGiveExpSP = false;
		m_bFirstAttack = false;
	}
	~CAttackChar()
	{
	}

	// pc
	int         m_damage;       // ������
	int         m_targetHate;   // Ÿ�� ��ġ : NPC�� ���ݽ� ���� ��
	// Ÿ���� ������ : �־����ų� ���ݾ��ϸ� �پ�

	int         m_targetPulse;  // Ÿ�� �޽� : 3�е��� ĳ���Ͱ� ������ ������ ���ø���Ʈ���� ����
	bool        m_bGiveExpSP;   // ����ġ�� SP�� �޾Ҵ°�
	bool        m_bFirstAttack; // ch�� ���� ���ȳ�?

	union
	{
		CCharacter* ch;
		CPC*        pc;
		CNPC*       npc;
	};

	CAttackChar*    m_next;
	CAttackChar*    m_prev;
};

// ������� List Class
class CRaChar
{
public:
	CRaChar()
	{
		m_raTarget = NULL;
		m_raPulse = 0;
		m_bAttacker = false;
	}
	~CRaChar()
	{
	}

	CPC*        m_raTarget;
	int         m_raPulse;
	bool        m_bAttacker;    // ������ : true ������ false

	CRaChar*    m_next;
	CRaChar*    m_prev;
};

//////////////////
// Character class
class CCharacter
{
private:

	float   m_nFinalHitrate;            // ���� ������  ( �ݵ�� ���Ϸᰡ ����Ǿ��� �� ��� )
	float   m_nFinalAvoidrate;          // ���� ȸ����  ( �ݵ�� ���Ϸᰡ ����Ǿ��� �� ��� )

public:
	typedef std::map<int/*index*/, GoldType_t/*nas*/> tradestash_t;

    // When true, NPC is driven by scripted movement tasks and other AI/regen
    // logic should skip modifying its position. Set by movement manager.
    bool m_bScriptedMovement;

	CCharacter();
	virtual ~CCharacter();

	MSG_CHAR_TYPE   m_type;     // ����

	// NPC, PC ���� ������
	int         m_index;        // ������ȣ
	CLCString   m_name;         // �̸�
	int         m_level;        // ��
	int         m_level_original;

	LONGLONG    m_exp;          // ����ġ
	LONGLONG    m_exp_original;

	int			m_color_name;

#ifdef BATTLE_PASS_SYSTEM
	int			m_battlePassPoints;
	int			m_battlePassLevel;
	int			m_battlePassPremium;
#endif

#ifdef QUICK_PANEL
	int				m_QuickPanelBtnType[25];
	int				m_QuickPanelBtnIdx[25];
#endif

	LONGLONG	m_skillPoint;   // ��ų����Ʈ

	int         m_hp;           // ü��
	int         m_maxHP;
	int         m_mp;           // ����
	int         m_maxMP;

	int         m_str;          // ��
	int         m_dex;          // ��ø
	int         m_int;          // ����
	int         m_con;          // ü��

	int         m_eqMelee;      // ���� ��ġ    : �ٰŸ�    : NUM0
	int         m_eqRange;      // ���� ��ġ    : ���Ÿ�    : NUM0 : IWEAPON_BOW
	int         m_eqMagic;      // ���� ��ġ    : ����      : NUM1
	int         m_eqDefense;    // �� ��ġ  : ����      : NUM0
	int         m_eqResist;     // �� ��ġ  : ����      : NUM1

	char        m_attackSpeed;  // ���ݼӵ� : ������ ���� ���� : 0.1�� ���� : ���ݴ� �ҿ�Ǵ� �ð� : +�� �ð��� ����
	char        m_magicSpeed;   // �����ӵ� : ���� ���� �ð� �ٰ� ��: 0.1�� ���� : -�� �ð��� ����
	int         m_skillSpeed;   // ��ų�ӵ� : ��ų ���� �ӵ��� �ٰ� ��
	int			m_skillCooltime; // 0 ~ 100%
#ifdef BUGFIX_DEAD_AGAIN_DEAD
	time_t		m_deadTime;
#endif
	int         m_statPall;
	// << 071226 kjban add
	int         m_statPall_per;
	// >>

	float       m_walkSpeed;    // �ȱ� �ӵ�
	int			m_attackSpeed_hack; //reza hack
	int			m_skillcd_hack;
	int			m_skillspeed_hack;
	int			m_Skill_hack; //reza hack
	int			m_runSpeed_hack; //reza hack

	float       m_runSpeed;     // �ٱ� �ӵ�
public:
	float       m_flySpeed;     // ���� �ӵ�
	float       m_attackRange;  // ���ݰŸ�

	int         m_recoverHP;    // ü�� ȸ��
	int         m_recoverMP;    // ���� ȸ��
	int         m_recoverPulse; // ����ȸ�� pulse : HP, MP

	CPos        m_pos;          // ��ǥ (x, z, h, r, yLayer)

	int         m_cellX;        // �� ��ġ
	int         m_cellZ;

	CAssist     m_assist;       // ����ȿ��
	ASSISTVALUE m_avPassiveAddition;    // �нú� ȿ�� : add
	ASSISTVALUE m_avPassiveRate;        // �нú� ȿ�� : rate

	CAttackChar* m_attackList;  //  ���� ����Ʈ

	CCharacter* m_pCellPrev;    // �� ����Ʈ ��ũ
	CCharacter* m_pCellNext;
	CZone*      m_pZone;        // ��
	CArea*      m_pArea;        // ����

	bool        m_bVisible;     // ���̰� �Ⱥ��̰�
	
	bool		m_bBattleWarfare;

	unsigned char m_attratt;
	unsigned char m_attrdef;

	unsigned char m_attratt_by_item;	//�����ۿ� ���� �Ӽ�
	unsigned char m_attrdef_by_item;	//�����ۿ� ���� �Ӽ�

	CSkill*     m_currentSkill;     // ���� ������� ��ų
	CCharacter* m_linkSource;   // ������ ��ũ �� ĳ��
	CCharacter* m_linkTarget;   // ���� ��ũ �� ĳ��

	////////////////////////////////
	// Artifact Value
	int			m_artiStr;			// �� ����
	int			m_artiDex;			// ��ø ����
	int			m_artiInt;			// ���� ����
	int			m_artiCon;			// ü�� ����
	int			m_artiExp;			// ����ġ ����
	int			m_artiGold;			// ���ȹ�� ����

	////////////////////////////////
	// Option Value
	int         m_opStr;            // �� ����
	int         m_opDex;            // ��ø ����
	int         m_opInt;            // ���� ����
	int         m_opCon;            // ü�� ����

	int         m_opMelee;          // ���� ���� ����
	int         m_opRange;          // ���� ���� ����
	int         m_opMeleeHitRate;   // ���� ���߷� ����
	int         m_opRangeHitRate;   // ���� ���߷� ����

	int         m_opDMelee;         // ���� ���� ����
	int         m_opDRange;         // ���� ���� ����
	int         m_opMeleeAvoid;     // ���� ���߷� ����
	int         m_opRangeAvoid;     // ���� ���߷� ����

	int         m_opMagic;          // ���� ���� ����
	int         m_opMagicHitRate;   // ���� ���߷� ���

	int         m_opResist;         // ���� ���� ����
	int         m_opResistAvoid;    // ���� ���߷� ����

	int			m_opExpRate;		// EXP ����
	int			m_opSPRate;			// SP ����
	#ifdef CUSTOM_OPTIONS_11182021
	int 		m_opNasRate; //dethunter12
	int			m_opBossDamRate;
	#endif
	int			m_opStrong;			// ������ ����
	unsigned char m_opAttratt;
	unsigned char m_opAttrdef;

	int			m_reborn;
	
	// ���� �˻� ����
	int     m_hackAttackCount;      // ���ø޼��� �� �� ����
	int     m_AttackServerTime;     // ���ӿ� ���� �ִ� ���� �ð�
	int     m_AttackClientTime;     // Ŭ���̾�Ʈ�� ���� ���ýð�
	int     m_lastAttackPulse;      // �ֱ� ���� �޽��� �� �ð�

	int     m_pulseDisable;         // ĳ���� �ൿ �Ҵ� �ð� ���� : ������ �ð� ���ķ� �ൿ ����
#ifdef PRESTIGE_SYSTEM
	//int			m_prestige;
	int			m_prestigePoints;
	int			m_prestigeLevel;
	int			m_prestigePremium;
#endif
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	int				m_nSoloDifficulty;
	int				m_PartyDGCompleteData[5];   //pwesty was 5
	int				m_PartyDGTitleRewardData[5];//pwesty was 5
#endif
#ifdef NEW_ACCERY_ADD
	////////////////////////////////////
	// �Ǽ��縮 ����ġ sp �߰���
	LONGLONG    m_AddProb;
#endif //NEW_ACCERY_ADD
	int             cooltime_2142;          // �ǰ��� ����
	int             cooltime_2143;          // ������ ����

	int     m_cooltime_Competition; // ������ ������

	int MobScroll;                      // �� ��ȯ�� ��� ����

	char    m_attacktype;
	char    m_attackcount;
	bool    ChekAttackType();           // ����Ÿ�Կ����� ���ǵ��� �˻� ����

	int		m_ep;						// attack Point
	int		m_maxEP;

	int		m_absorbPVPDamageRate;		// PVP�� ������ ������
	int		m_decreaseDBufTimeRate;		// ������ð� ������

	int		m_tradeAgentRegCount;		// �ŷ����� ��� ����
	tradestash_t m_tradeAgentViewMap;	//�ŷ����� ���� ������ ����
	tradestash_t m_tradeAgentViewMap2;	//�ŷ����� ���� ������ ����

	bool		m_bFirstDoIt;			//������忡 ���� �ൿ ���� (true : 15��, false = 3�� ���� �����ؼ� ���)

	int			m_syndicateType;			// ���� �ε���
#ifdef REZABOT 
	char	m_botting;
#endif 
	std::map<int, CHackCheck*> m_mapHack_check;

	void Move(float tx, float tz, float th, float tr, int ylayer)   // �̵�
	{
		m_pos = CPos(tx, tz, th, tr, ylayer);
	}

	void InitPointsToMax()      // hp, mp, ep, st�� �ִ�ġ�� ����
	{
		m_hp = m_maxHP;
		m_mp = m_maxMP;
	}

	void SetVisible();          // ���̰� �Ⱥ��̴� ���¸� ��۽�Ŵ

	/////////////////////
	// Function name    : SendDisappearAllInCell
	// Description      : ĳ���� �ֺ��� ��� ĳ����+�������� ��������� �˸�
	// Argument         : bool bSendOtherDisappear
	//                  : �ٸ� ����� ������� �ڽſ��� �˸� ������ ����
	void SendDisappearAllInCell(bool bSendOtherDisappear);

	//Ŭ���̾�Ʈ ����Ʈ ����� �ϱ����� npc���� ��Ŷ(��ȯ npc�� ���ۿ����� ���)
	void SendRemoveAllInCellForClientEffect(CPC* owner);

	////////////////////
	// Function name    : CanApplySkill
	// Description      : ��ų ���� ���� �˻�
	bool CanApplySkill(const CSkillProto* proto, const CSkillLevelProto* levelproto);

	////////////////////
	// Function name    : CanMove
	// Description      : �̵� ���� �˻�
	virtual bool CanMove();

	////////////////////
	// Function name    : CanAttack
	// Description      : ���� ���� �˻�
	virtual bool CanAttack();

	////////////////////
	// Function name    : CanSpell
	// Description      : ���� ���� �˻�
	virtual bool CanSpell();

	////////////////////
	// Function name    : GetAttackLevel
	// Description      : ���ⷹ�� ���
	virtual int GetAttackLevel() = 0;

	////////////////////
	// Function name    : GetDefenseLevel
	// Description      : �� ���� ���
	virtual int GetDefenseLevel() = 0;

	////////////////////
	// Function name    : GetAttackType
	// Description      : ���� Ÿ�� ���, ��ų �����䰡 ������ ��ų�� Ÿ��, NULL�̸� �⺻ Ÿ��
	virtual MSG_DAMAGE_TYPE GetAttackType(const CSkillProto* proto) const = 0;

	////////////////////
	// Function name    : ApplyAssistData
	// Description      : assist value�� ����
	void ApplyAssistData(ASSISTVALUE* add, ASSISTVALUE* rate);

	////////////////////
	// Function name    : IsInPeaceZone
	// Description      : �ǽ��� ������ �˻�, bBlockAsPeace�̸� MAPATT_BLOCK�� �ǽ������� ����
	bool IsInPeaceZone(bool bBlockAsPeace);

	////////////////////
	// Function name    : IsInRaidZone
	// Description      : ���̵� ������ �˻�
	bool IsInRaidZone();

	////////////////////
	// Function name    : GetSize
	// Description      : ĳ���� ũ�� ��ȯ
	virtual float GetSize() = 0;

	////////////////////
	// Function name    : GetUsingStat
	// Description      : ���ݽ� ����ϴ� ����
	virtual int GetUsingStat() const = 0;

	bool IsInvisible()
	{
		return (m_assist.m_state & AST_INVISIBLE) ? true : false;
	}
	bool IsEnemy(CCharacter* tch);
	bool CanVisible(CCharacter* tch);

	void CancelInvisible();
	void CancelDamageLink();

	int GetDefenseLevelBonus() const
	{
		return (m_type == MSG_CHAR_PC) ? (m_level * 3) : 0;
	}
	virtual int GetResistLevelBonus() const
	{
		return (m_type == MSG_CHAR_PC) ? (m_level / 2) : 0;
	}
	int GetMeleeLevelBonus() const;
	int GetRangeLevelBonus() const;
	int GetMagicLevelBonus() const;

	void AddEP( int ep_ );

	bool IsBlind()
	{
		return (m_assist.m_state & AST_BLIND) ? true : false;
	}

	bool IsBattleWarfare() { return m_bBattleWarfare; }

	bool IsZoneBattleWarfare();

	unsigned short GetMapAttr();

	virtual CSkill* FindSkill(int skillindex) = 0;

	// �нú� ��ų ����
	virtual void ApplyPassive() = 0;
	void ApplyPassiveSkill(CSkill* skill, int param);

	// ���� ����
	virtual void CalcStatus(bool bSend) = 0;

	// ���� �˻� : PC, ��, Elemental
	// ������ �Ǵܽ� true
	bool CheckHackAttack(CPC* of);

	// alan check hack client
	bool CheckHackAttack(CPC* of, CPC* df, int targets);

	virtual float GetHitrate(CCharacter* df, MSG_DAMAGE_TYPE type) = 0;
	virtual float GetAvoid(CCharacter* of, MSG_DAMAGE_TYPE type) = 0;

	// �Ʒ� �Լ��� ȸ�� ��� �� ��� �ؾ� �մϴ�.  �ٸ����� ��� ����...
	float   GetFinalHitRate()
	{
		return m_nFinalHitrate;
	}
	float   GetFinalAvoidRate()
	{
		return m_nFinalAvoidrate;
	}
	void    SetFinalHitRate( float FinalHitRate )
	{
		m_nFinalHitrate = (FinalHitRate<0 ? 0:FinalHitRate);
	}
	void    SetFinalAvoidRate( float FinalAvoidRate )
	{
		m_nFinalAvoidrate = (FinalAvoidRate<0 ? 0:FinalAvoidRate);
	}

	// ������ ǥ��
	int		m_nExpedLabel;
	void	SetExpedLabel(int nType);
	int		GetExpedLabel();

	LONGLONG GetRequiredLevelExp();

	// disable ����, ���� ������ �� �������� ����
	void SetDisableTime(int sec);
	// disable ���� ��ȯ
	bool IsDisable();

	void SetRunSpeedAdmin(float speed)
	{
		m_runSpeed = speed;
	}

	void SetRunSpeed(float speed)
	{
		( speed < PC_MIN_RUNSPEED ) ? m_runSpeed = PC_MIN_RUNSPEED : m_runSpeed = speed;
		
		if (IS_APET(this) || IS_PET(this)) {
			m_runSpeed = speed;
		} else if ( speed > PC_MAX_RUNSPEED ) {
			m_runSpeed = PC_MAX_RUNSPEED;
		}
	}

	float GetRunSpeed(void)
	{
		return m_runSpeed;
	}

	float GetHpPercentage(void)
	{
		if (m_maxHP == 0) return 0.0f;
		return ((float)m_hp / (float)m_maxHP) * 100;
	}

	void applyAuraSkill(CCharacter* ch, int& auraCount, int level, CAssistData* outData);

	void setSyndicateType(int syndicateType);
	int	getSyndicateType()
	{
		return m_syndicateType;
	}

	//������ ��ų �� Ÿ�� ���� �����̳�
private:
	std::map<int/*������ �ε���*/, int/*�� Ÿ��*/> m_itemCoolMap;
public:
	void addItemCoolTime(int item_index);
	bool checkItemCoolTime(int item_index, CSkill* skill);
};

///////////
// PC class
class PartyRecallInfo
{
public:
	PartyRecallInfo()
	{
		resetPartyRecallInfo();
	}
	~PartyRecallInfo() {};
	void	setPartyRecallInfo(int zoneID, CPos& pos, int guildIndex, char cIsInCastle)
	{
		zoneID_ = zoneID;
		pos_ = pos;
		guildIndex_ = guildIndex;
		cIsInCastle_ = cIsInCastle;
	}

	void	resetPartyRecallInfo()
	{
		zoneID_ = -1;
		pos_ = CPos(0, 0, 0, 0, 0);
		guildIndex_ = 0;
		cIsInCastle_ = 0;
	}
	int		getZoneID()
	{
		return zoneID_ ;
	}
	CPos*	getPos()
	{
		return &pos_;
	}
	int		getGuildIndex()
	{
		return guildIndex_;
	}
	char	getIsInCastle()
	{
		return cIsInCastle_;
	}

private:
	int		zoneID_;
	int		guildIndex_;
	char	cIsInCastle_;
	CPos	pos_;
};

typedef std::map<int, CBlockPC*> map_listblock_t;
class CPC : public CCharacter, public MemoryPoolBaseWithMutex<CPC>
{
	int             m_state;            // pc ����

	int             m_joinMerac;        // �޶�ũ ���� ��������

	int             m_joinDratan;

	int     m_pulseDisable;             // ĳ���� �ൿ �Ҵ� �ð� ���� : ������ �ð� ���ķ� �ൿ ����

public:
#ifdef LOGINREWARDNEW
	
#define DAYCOUNT 35
	int				m_DLdaycount;
	int				m_DLddaycheck[DAYCOUNT];

#endif

#ifdef KILLMEDALS
	int				m_lKTime;
	int				m_KillChain;
	int				m_KillMedalData[OVERKILLSTART - 1];
	int				m_KillOverKillStreak;
#endif

#ifdef REZABOT
	char			m_botting;
#endif
	int				m_jailed_time;
	int				m_jailed_count;
	int				m_jailed;
	void reviseHPMP();
	bool AddExpUseGP(LONGLONG exp);
	void ApplyTitle();					// ȣĪ�� �پ� �ִ� �ɼ� ���� �Լ�.
	void TitleCurrentSkillCure(int titleIndex = -1, bool bListDelete = true );  // ���� ���� ���� Ÿ��Ʋ ȿ�� ����
	void CastllanTitleDelete(int castleZoneindex, bool bExclude, char bCastellan = 0);

	CPC();
	virtual ~CPC();

	bool is_valid_cash_purchase_list(int purchaseindex, int ctid);
	void erase_cash_purchase_list(int purchaseindex, int ctid);

	bool is_valid_cash_gift_list(int purchaseindex, int ctid);
	void erase_cash_gift_list(int purchaseindex, int ctid);

	////////////
	// �⺻ ����
#ifdef STASH_PASSWORDS
	std::string		m_stash_password;			// â�� �н�����
	std::string		m_a_cid;					// �±� a_cid 7���ڸ�
#endif

	TimerItemManager	m_TimerItem;	// �Ⱓ�� ������ ����
	int     m_listIdx;          // ����Ʈ���� �ε���
	bool    m_bPlaying;         // �÷��� ����
	bool    m_bChangeStatus;    // SendStatus()�� ���� ������ ����

	unsigned int m_saveDirtyFlags;
	void SetSaveDirty(unsigned int flags) { m_saveDirtyFlags |= flags; }
	void ClearSaveDirty()                 { m_saveDirtyFlags = 0; }
	bool IsSaveDirty(unsigned int flags) const { return (m_saveDirtyFlags & flags) != 0; }

	bool    m_bImmortal;        // ������ ���� ���ϴ°�? ��� ���ɾ�� ����
	bool    m_bChatMonitor;     // ä�� ����͸� ����
	bool    m_bLoadChar;        // ĳ���� �ε� ����
	CLCString m_nick;           // ����(�̸� ����ī��)
	int     m_billReqTime;      // ���� ������ ���� Ÿ��
	int 	m_autopickup;
    int 	m_autoigni;
	int 	m_autosell;

	int		m_eventSummonCount;

	std::vector<std::pair<int, int> > m_cash_purchase_list;	// �ڽ��� ������ �������� īŻ�α� ����Ʈ
	std::vector<std::pair<int, int> > m_cash_gift_list;	// ���� ���� īŻ�α� ����Ʈ

	std::vector<HonorKill>	m_lastHonorKills;

	int     m_speedup;          // ��� ���ɾ� : speedup
	int     m_autoSkillTime;
	int     m_SkillTime_511;
	int		m_SkillTime_theos;  //pwesty
	int     m_cashBalance;      // ���� ĳ��

	unsigned short m_recentAtt;  // �ֱ� ��ġ �Ӽ��� ��

	int     m_nflag;            // ĳ���� flag - ä�ñ���

	bool            m_bTradeAgentRegIng;    //���� ��� ó�����ΰ�(�ŷ�����)
	bool            m_bTradeAgentCalcIng;   //���� ���� ó�����ΰ�(�ŷ�����)
	bool			m_bTradeAgentBuyIng;	//���� ���� ó�����ΰ�(�ŷ�����)
	int             m_nCalcPageNo;          //����(����Ʈ)���� ������ ��ȣ

#ifdef RANKER_NOTICE
	bool    m_bRanker;          // ��Ŀ �ΰ�.
#endif

	int     m_pd3Count;         // �۽��δ���3 ���� ��
	int     m_pd3Time;          // �۽��δ���3 ������ ���� �ð�
	int     m_pd4Count;         // �۽��δ���4 ���� ��
	int     m_pd4Time;          // �۽��δ���4 ������ ���� �ð�

	int m_etcEvent;

#ifdef GMTOOL
	bool    m_bGmMonitor;           // ������ ä�� ����͸� ����
#endif // GMTOOL

	int     m_secretkey;
	/////////////////////////////////////////////
	// BANGWALL : 2005-06-27 ���� 7:10:37
	// Comment :
	// pd4 ���� Ÿ��
	int m_pd4StartTime;

	LONGLONG m_loseexp;         // ��� ����ġ ����
	LONGLONG m_losesp;          // ��� sp ����

	CFriend* m_Friend;
	int m_nRegFriend;
	int m_nCondition;
	map_listblock_t  m_listBlockPC;

	////////////
	// �ܾ� ����
	unsigned char    m_job;              // ����
	unsigned char    m_job2;             // 2�� ����

#ifdef ENABLE_SUBJOB
	int	m_jobSub;			// ������
	bool			IsSubJob( int subjob )
	{
		return  m_jobSub & subjob ? true : false ;
	}
#endif //ENABLE_SUBJOB

	char    m_hairstyle;        // �Ӹ����
	// 1�� �ڸ� : ���� �췯
	// 10�� �ڸ� : ��Ÿ ����
	char    m_facestyle;        // �󱼸��

#ifdef GER_LOG
	//private:
	//	time_t m_loginTime;				// �α����� �ð�.

	//public:
	//	time_t GetLoginTime()
	//	{
	//		return m_loginTime;
	//	}
	//	void SetLoginTime();
	//	void GetCalcInGameTime(char *_buf, const int _size);
#endif // END : GER_LOG
	////////////
	// ��ų ����
	CSkillList  m_activeSkillList;
	CSkillList  m_passiveSkillList;
	CSkillList  m_etcSkillList;
	CSkillList	m_optionAttSkillList;
	CSkillList	m_optionDefSkillList;

	CSkillList          m_sealSkillList;                            // ���� ��ų
	SEAL_SKILL_DATA     m_sealSkillExp[MAX_SEAL_TYPE_SKILL];        // ���� ��ų ���õ�

	//PASSIVE_SYSTEM
	CPassiveSystemList m_passiveSystemSlot; //new 16-08-2022
	CPassiveSystemList m_passiveSystemList; //new 16-08-2022


	//////////////////
	// Special Skill
	CSSkillList m_sSkillList;   // Special Skill List
	//////////////
	// ����Ǵ� ��
	int     m_admin;            // ������ ���

// 050401 : bs : plus�� ���� Ȯ�� ���� �߰� : PC�� ���
	int     m_plusStrong;
	int     m_plusHard;
	int     m_plusWeak;
// --- 050401 : bs : plus�� ���� Ȯ�� ���� �߰�

	///////////////////
	// ���� ����Ʈ ����
	int     m_statpt_remain;    // ���� ��
	int     m_statpt_str;       // ��
	int     m_statpt_dex;       // ��ø
	int     m_statpt_int;       // ����
	int     m_statpt_con;       // ü��

	////////////////////
	// Blood Point
	int     m_bloodPoint;       // Blood Point

	////////////////////
	// PC ���� �ɼ� ����
	int         m_opSturnLevel;     // ���� : ����
	int         m_opBloodLevel;     // ���� : ������
	int         m_opPoisonLevel;    // ���� : ������
	int         m_opSlowLevel;      // ���� : ���ο�
	int         m_opMoveLevel;      // ���� : ����

	int         m_opSturnIndex;     // ��ų ��ȣ : ����
	int         m_opBloodIndex;     // ��ų ��ȣ : ������
	int         m_opPoisonIndex;    // ��ų ��ȣ : ������
	int         m_opSlowIndex;      // ��ų ��ȣ : ���ο�
	int         m_opMoveIndex;      // ��ų ��ȣ : ����

	bool        m_bCreateMixItem;   // �������� ������ ���� ����
//#endif

	int         m_opIncreaseInven;      // �ִ� ���� ���� : ���� %
	int         m_opMPSteal;            // ���� ���� : ���� %
	int         m_opHPSteal;            // ������ ���� : ���� %
	int         m_opAttackBlind;        // ���� ���� 415 : ���� ��ų ����
	int         m_opAttackPoison;       // �� ���� 414 : ���� ��ų ����
	int         m_opAttackCritical;     // ũ��Ƽ�� Ȯ�� ���� : ���� %
	int         m_opAttackDeadly;       // ���鸮 Ȯ�� ���� : ���� %
	int         m_opRecoverHP;          // ü��ȸ�� ���� : ���� %
	int         m_opRecoverMP;          // ü��ȸ�� ���� : ���� %
	int         m_opDecreaseSkillDelay; // ��ų ��Ÿ�� ���� : ���� %
	int         m_opDecreaseSkillMP;    // MP �Ҹ� ���� : ���� %
	int         m_opResistStone;        // ���� ���� ���� : ���� %
	int         m_opResistSturn;        // ���� ���� ���� : ���� %-
	int         m_opResistSilent;       // ħ�� ���� ���� : ���� %
	int         m_opBlocking;           // ������ ���� ���� (��ų ����) : ���� %
	int			m_opRecoverHP_NoRate;	// ü��ȸ�� ��������
	int			m_opRecoverMP_NoRate;	// ����ȸ�� ��������
	int			m_wins;
	int			m_loses;
	int			m_stats_addition;
	int			m_honor;				//honor points pvp
	int			m_opJewelElementPetHPUP;		//���� �ɼ� ��ȯ�� �� �� HP����
	int			m_opJewelElementAttUP;		//���� �ɼ� ��ȯ�� ���ݷ� ����
	int			m_opJewelElementMagicAttUP;	//���� �ɼ� ��ȯ�� �������ݷ� ����
	//////////////
	// ����Ǵ� ��
	int     m_dbStr;                    // ��
	int     m_dbDex;                    // ��ø
	int     m_dbInt;                    // ����
	int     m_dbCon;                    // ü��

	int     m_dbHP;                     // ü��
	int     m_dbMP;                     // ����
	int		m_tempHP;
	int		m_tempMP;

	////////////
	// ���� ����
	CDescriptor* m_desc;                // ��ũ����

	////////////
	// �ð� ����
	int     m_silencePulse;             // ä�� ���� �ð� ���� ����
	int     m_lastProducePulse;         // �ֱ� ���� �޽��� �� �ð�
	int     m_hackProduceCount;         // ����޼��� �� �� ����
	int     m_ProduceClientTime;        // Ŭ���̾�Ʈ�� ���� ����ð�

#ifdef CHAT_BLOCK_USA
	int     m_shoutPulse;
	int     m_sayPulse;
	int     m_guildPulse;
	int     m_partyPulse;
	int     m_lordPulse;
	int     m_expiditionPulse;
#endif // CHAT_BLOCK_USA
	int    m_personalShopBuyPulse; //dethunter12 add prevent personal shop exploit

	bool    m_bProcDisconnect;          // ���� ����� ProcDisconnect()�� ȣ�� �ߴ��� ����
	CNPC*   m_pPendingVendorNpc;        // offline vendor NPC: AppearMsg sent after CPC removed from cell

	//////////////
	// ������ ����
	InventoryManager	m_inventory;	// ���� + ���� â���� �����ϴ� Ŭ����
	CWearInvenManager	m_wearInventory;

	bool        m_bChangeStash;         // â�� ���� ���� �ִ��� �˻�
	CNetMsg     m_stashMsg;             // â�� ��û �޽���

	std::vector<AUTO_GIVE_DATA>     m_listAutoGive;     // �ڵ� ������ ������ ����
	std::vector<BLOOD_BUG_DATA>     m_listBloodBug;     // ���׷��̵� �Ұ� �����ۿ� �ɼ� �ٴ� ���� ������ ���� �ɼ� ���ŵ� ������ ����
	std::vector<CItem*>				m_removingItemList;

	////////////
	// ��ȯ ����
	CExchangeItems*     m_exchange;

	// ���� ����
	CPersonalShop::SP	m_personalshop;

	/////////////////
	// ��� ��� ����
	CMemPos             m_mempos;               // ���� ��� ����Ʈ
	int                 m_reqWarpTime;          // �����̵� ���� �ð�
	int                 m_reqWarpType;          // �̵� ���(��ȯ/��ұ��)
	int                 m_reqWarpData;          // ��ȯ�� ����ȣ/��ұ��� ���Թ�ȣ

	int                 m_reqWarpTime_skill;          // �����̵� ���� �ð�
	int					m_reqWarpType_skill;	// ��ų�� �̿��� �̵� ���
	int					m_reqWarpData_skill;	// ��ų�� �̿��� ��ȯ�� ����ȣ

	float	m_Npc_Portal_x;
	float	m_Npc_Portal_z;
	char	m_Npc_Portal_y;
	void GoNpcPortalScroll();

	////////////
	// ��Ƽ ����
	CParty*             m_party;
	PartyRecallInfo		m_partyRecallInfo;

	PartyRecallInfo* getPartyRecallInfo()
	{
		return & m_partyRecallInfo;
	}

	// ������ ����
	CExpedition*        m_Exped;

	int m_nJoinInzone_ZoneNo;                       //���� ���� �� ��ȣ
	int m_nJoinInzone_RoomNo;                       //���� ���� �� ��ȣ
	int m_nJoinInzone_AreaNo;                       //���� ���� Area ��ȣ

	int m_nRaidBoxItemTime;											//���̵� �ڽ� ȹ�� �ð� üũ
	void SetRaidBoxItemTime(int nTime)
	{
		m_nRaidBoxItemTime = nTime;
	};	//���̵� �ڽ� ȹ�� �ð� ����
	int  GetRaidBoxItemTime()
	{
		return m_nRaidBoxItemTime;
	};				//���̵� �ڽ� ȹ�� �ð� ȹ��

	//////////////
	// Quick Slot
	CQuickSlot      m_quickSlot[QUICKSLOT_PAGE_NUM];    // ������ 3������ ����
	void recalcByItem(CItem* pItem);

	//////////////
	// pc ���װ���
	int             m_pkPenalty;                // PK ����
	int             m_pkCount;                  // PK ��
	int             m_pkRecoverPulse;           // ���� ��ġ ȸ�� ���� �ð�
	int             m_pkmodedelay;              // PKMODE ��ȯ ������
	int             m_pkPenaltyHP;              // HP ����
	int             m_pkPenaltyMP;              // MP ����
	int             m_pkRecoverNPCCount;        // ��� ��

#ifdef RESTRICT_PVP_SKILL
	int             m_nRestrictPvPSkillDelaySec;    // ���� ���� Ÿ���� ���� ��ȿ �ð�
#endif // RESTRICT_PVP_SKILL

	// ������� ����
	CRaChar*        m_raList;

	///////////////////
	// ������ ��� ����
	int             m_recoverHPItemTime;        // HP ȸ�� ���� �ð�
	int             m_recoverHPItemValue;       // HP �ʴ� ȸ����
	int             m_recoverMPItemTime;        // HP ȸ�� ���� �ð�
	int             m_recoverMPItemValue;       // MP �ʴ� ȸ����

	///////////////////
	// ����Ʈ ����
	CQuestList      m_questList;                // ����Ʈ ����Ʈ
	int             m_nLastCollectRequest;      // ������ MSG_QUEST_COLLECT ���� �ð�
	int             m_nCollectRequestNPCIndex;  // ������ MSG_QUEST_COLLECT ���� NPC �ε���
	int             m_nCollectRequestCount;     // ��������Ʈ ���� ��

	////////////
	// ��� ����
	CGuildMember*   m_guildInfo;                // ��� ����, ���������̸鼭 ������� ��� �ڽ��� ��� ���� ��� ����
	int             m_regGuild;
	int             m_guild_in_date;             // ��� ���� ��
	bool			m_guildStashLock;

	////////////////
	// �յ���Ƽ�� �������� �������� �ִ°�?
	bool            m_bGiveItem;

	////////////////////
	// ���� ����
	int             m_changePulse;          // ���� �ð�
	int             m_changeIndex;          // ���� �� �ε���

	////////////////////
	// ������ ����Ʈ �ɼ�
	char            m_plusEffect;           // ������ �÷��� ����Ʈ �ɼ�

	/////////////////////
	// ���� �ý���

	// ���� �ʿ� ����
	int     m_teachIdx[TEACH_MAX_STUDENTS];     // ���� �ε���
	int     m_teachLevel[TEACH_MAX_STUDENTS];   // ���� ����
	char    m_teachJob[TEACH_MAX_STUDENTS];     // ���� ����
	char    m_teachJob2[TEACH_MAX_STUDENTS];    // ���� ����
	char    m_teachName[TEACH_MAX_STUDENTS][MAX_CHAR_NAME_LENGTH + 1];// ���� �̸�
	int     m_teachTime[TEACH_MAX_STUDENTS];    // ���� ������ �ð� : sec

	// ��������
	int     m_teachWait;                // ��û���� ĳ������ �ε���
	char    m_teachType;                // none -1 teacher 0 student 1
	bool    m_bTeacher;                 // ������ ��������Ʈ�� ��� ����

	int     m_fame;                     // ����ġ
	int     m_cntTeachingStudent;       //0627
	int     m_cntCompleteStudent;
	int     m_cntFailStudent;
	int     m_superstone;               //���� �ʰ��� ����
	int     m_guardian;                 //�İ��� �ý������� ������ ĳ�������� üũ.
	bool    m_displayCanSstone;         // �ʰ����� ������ �ִ����� display�ߴ°�?

//0502 kwon
	int m_nMoonStoneDigit;              //���� ���� ������ ������ ����
	int m_nMoonStoneSum;                //������ ���� ����

#ifdef LACARETTE_SYSTEM // �ӽ÷� ������ �ѵ�... �Ѥ�;; �� �ٸ� ���� ����� ������?
	int	m_lacaretteCosArrNum;
	int m_lacaretteItemArrNum;
	int	m_lacaretteTokenArrNum;
	int	m_lacaretteRepeat;
#endif
	int m_nMSIndex;
	int m_nMSGiftIndex;

	///////////
	// �ֿϵ���
	CPet*   m_petList;
	int     m_pulseLastAttackSkill;

	// pc�� ���� ������ �̽��� �ƴҶ��� ����ġ �߰�
	bool    m_bNotMiss;
	bool    m_bHasFlagItem;
	bool    m_bIsQuestExpCheck;
	CElemental*     m_elementalList;        // ��ȯ�� ����Ʈ
	int             m_pulseElemental[4];    // �� ��ȯ���� ��ȯ �ð�

	int             m_pulseEvocation[2];    // ������ �ð� : ����, ������
	int	            m_evocationIndex;        // ���� Ÿ��

	int             m_memposTime;           // �޸� ��ũ�� Ȯ�� ���ð�
	int             m_stashextTime;         // â�� Ȯ�� ���ð�

	// 2005 ũ�������� �̺�Ʈ ����
	int     m_pulseTakeEventXMas2005;

	// 2006 �ų� �̺�Ʈ
	int     m_nTimeEventNewYear2006;        // ��ɽð�
	int     m_pulseEventNewYear2006;        // �ֱٻ�ɽð�

	// ����ġ �й���� �߰� ���� : 051228 : BS
	int				m_nExpDamage;           // ���� �����

	int     m_nGoldenBallNoticeStatus;                  // ��纼 �̺�Ʈ ���� ���� ����

	char    m_nEventGomdori2007Win;             // ���� �¼�
	char    m_nEventGomdori2007Game;            // ���� ���� ���������� �õ� ��
	char    m_nEventGomdori2007FirstLose;       // ó�� �� ���� ���� ����
	char    m_nEventGomdori2007FirstWin;        // ó�� 1�� ���� ���� ����
	bool    m_bEventGomdori2007Start;           // ���� ���� ����
	int     m_nEventGomdori2007Total;           // ���� ���� ��
	bool    m_bEventGomdori2007CanSelect;       // ���� ���� ����
	int     m_bEventGomdori2007Drop;            // ��� ����

	CRockPaperScissorsInfo m_RockPaperScissorsInfo;
	void StartRockPaperScissors();
	bool CanRockPaperScissors();

	int		m_nAttendance_exp;						// �⼮ ����ġ

	int     m_bEventIndependenceDay2007drop;

	int     m_GuildExp;                                             // �������Ʈ�� ��ȯ�� ����ġ
	int     m_GuildFame;                                            // ��� ����Ʈ�� ��ȯ�� ����ġ

	long        m_nRespondTime;                                     // ���� �ð� ����

	CAPet*      m_pApetlist;

	float m_runSpeed_org;
	char m_attackSpeed_org;
	int m_maxHP_org;
	int m_maxMP_org;

	int m_bPhoenix_Char;
    int m_bPremium_Phoenix;
#ifdef DEMIGOD
    int m_DemiGod;
#endif
	GM_GOZONE_TYPE m_gmGoZoneType;

	CFactoryList    m_listFactory;                                  // ���� ���� ������ list

	bool        m_bTaming_npc;                                      // ���̹� ��ų�� ����ϰ� �ִ��� ����
	CNPC*		m_Slave_npc;				                        // ���̹��� ����
	int         m_nSoul_Count;                                      // ����Ʈ������ ������ ��ȥ
	CCharacter* m_Owners_target;
	CCharacter* GetOwners_target()
	{
		return m_Owners_target;
	}
	void        SetOwners_target(CCharacter* target)
	{
		m_Owners_target = target;
	}
	int         GetSoul_Count()
	{
		return m_nSoul_Count;
	}
	void        SetSoul_Count(int count)
	{
		m_nSoul_Count = count;
	}

	// ������ �Ǵ� ��ų�� ���� ó��
	char		m_skillTargetCount;									// ���ӽð��� �� ��ų�� Ÿ�� ����
	char*		m_targettype;										// ���ӽð��� �� ��ų�� Ÿ�� Ÿ�� �迭
	int*		m_targetindex;										// ���ӽð��� �� ��ų�� Ÿ�� �ε��� �迭

	// Appear�ż����� ���� �� ��ų ���� ���̸� skillfireMsg�� �����°� üũ
	bool		m_bCheckAppear;

	set_npc_t	m_listTaming;
	void DeleteSlave( CNPC* npc );
	bool AddSlave( CNPC* npc);
	bool IsTaming()
	{
		return m_bTaming_npc;
	}


	CAffinityList	m_affinityList;

	int m_nCurrentTitle;											// ���� �Ӹ����� �ް� �ٴϴ� ȣĪ �ε��� ���� ����
	CTitleList m_titleList;											// ĳ���Ͱ� �����ϰ� �ִ� ȣĪ ����Ʈ

#ifdef XTRAP
	int			m_xtrapCheckPulse;			// XTrap Ȯ�� �ֱ�
#endif // XTRAP

	int			m_newtutoComplete;

	LONGLONG m_exp_weekly;

	CNPC* m_pSummnonNpc[SUMMON_NPC_MAX];
	CCharacter* m_SummonOwners_target;
	int			m_nBombSummonCnt; // ���� ����Ѵ�.

	void        SetSummonOwners_target(CCharacter* target)
	{
		m_SummonOwners_target = target;
	}
	CCharacter* GetSummonOwners_target()
	{
		return  m_SummonOwners_target;
	}
	void		SetSummonNpc(SUMMON_NPC_TYPE summonType, CNPC* pNPC);
	CNPC*		GetSummonNpc(int index, int idNum);
	CNPC*		GetSummonNpc(SUMMON_NPC_TYPE summonType);
	CNPC*		GetSummonNpc(CNPC* pNPC);
	void		SummonNpcRemove(CNPC* pNpc, bool bAutoDelete = true);
	void		SummonNpcRemove(SUMMON_NPC_TYPE summonType, bool bAutoDelete = true);
	void		SummonNpcRemoveAll(bool bAutoDelete = true);
	int			GetSummonNpcType(CNPC* pNpc);
	int			GetBombSummonCont()
	{
		return m_nBombSummonCnt;
	}
	bool		SetBombSummonNPC( CNPC* pNPC );
	///////////////////////////////////////////////////////////////////
	// �Լ� ����

	///////////////////
	// ĳ���� ���� ����
	void SendStatus();                                                  // ���� ������
	void Send(CNetMsg::SP& msg);                                            // �޽��� ������
	void SendQuickSlot();                                               // ������ ����

	void Restore();                                                     // ���� ȸ��

	bool AddExpSP(LONGLONG exp, LONGLONG sp, bool bUseEvent, bool IsQuestExp = false, bool bNoEffect = false, bool bArtifact = false);                // + sp, + exp

	void AddExpSP_Direct( LONGLONG exp, LONGLONG sp );						// �ٸ�ȿ�� ������� ����ġ ����
	void CalcLevelup();													// ���� �ִ� exp �� ������ �˻� ��ƾ����

	void LevelUp(bool bSendEffect);                                     // ������ ȿ��
	void InitStat();                                                    // ������ �������� ���� �ʱ�ȭ
	void CalcStatus(bool bSend);                                        // ������, ��ų�� ���� ���� ��ȭ
	void AddItemToRemovingList(CItem* item);
	void RemoveItemFromList(bool bAdd);

	bool InitSkill(CSkillList* skillList, bool isPassive = false);      // ��ų �ʱ�ȭ
	bool InitSSkill();                                                  // Ư�� ��ų �ʱ�ȭ

	void resetCoolTime(CSkillList* skillList);

	void RecoverPC();                                                   // �ڵ�ȸ��, HP MP
	void ApplyItemValue(bool bSend);
	void ApplyItemPlusValue(CItem* pItem, int NormalPlus);                              // plus���� �����ۿ� ����Ǵ� ��ġ ��ȭ �� ���ʽ� �ɷ�
	void ApplyStoneValue(CItem* pItem);
	int ItemUpgradeFuckingFunction( int itemPlus, int itemLevel, int itemAttack );	// 2011 ������ ���� ��� ��þƮ ���� ����

	int CanChange();

	const char* GetName();
	//{
	//    if( IsNick() )
	//        return m_nick;
	//    return m_name;
	//}

	void ChangeName(const char* name);

	bool IsNick();
	//{
	//    if (m_nick != NULL && strcmp(m_nick, "") != 0)
	//        return true;
	//    else
	//        return false;
	//}

	////////////////////
	// Function name    : SettingItemOption
	// Description      : ���� ������ �ɼ� ����
	// Return type      : int
	//                  : �ɼ� ���õ� ��Ʈ ��ȣ
	int SettingItemOption();

	//////////////////////////////
	// �����Կ��� Ư�� ������ ����
	void RemoveItemFromQuickSlot(CItem* item);

	//////////////////////////////
	// �����Կ��� Ư�� ��ų ����
	void RemoveSkillFromQuickSlot(CSkill* pSkill);
	void RemovePetSkillFromQuickSlot();
	void RemoveApetSkillFromQuickSlot();
	void RemoveAllGuildSkillFromQuickSlot();

	void ChangeQuickSlot(CItem* item, int itemSlotType);

	/////////////////////
	// Function name    : GoMemPos
	// Description      : ���� ��ҷ� �̵�
	// Argument         : int slot
	//                  : �̵��� ��� ��� ��ġ
	void GoMemPos(int slot);

	/////////////////////
	// Function name    : UseStatPoint
	// Description      : ���� ����Ʈ ���
	// Return type      : bool
	//                  : ���� ����
	// Argument         : MSG_STATPOINT_USE_TYPE type
	//                  : ������ ����
	// Argument         : int* val
	//                  : ��ȭ�� ���� ��ġ
	bool UseStatPoint(MSG_STATPOINT_USE_TYPE type, int* val);

	/////////////////////
	// Function name    : CanWarp
	// Description      : ���� �������� ����� �� �ִ��� �˻�
	// Return type      : int
	//                  : ����� �� ������ 0, �ƴϸ� �ý��� �޽���
	int CanWarp();

	/////////////////////
	// Function name    : FindSkill
	// Description      : ��ų ã��
	CSkill* FindSkill(int index);

	////////////////////
	// Function name    : GetAttackLevel
	// Description      : ���� ���� ���ϱ�
	virtual int GetAttackLevel();

	////////////////////
	// Function name    : GetDefenseLevel
	// Description      : �� ��� ���� ���ϱ�
	virtual int GetDefenseLevel();

	////////////////////
	// Function name    : GetAttackType
	// Description      : �⺻ ������ ���� ���Ÿ� ���� ������ ������
	virtual MSG_DAMAGE_TYPE GetAttackType(const CSkillProto* proto) const;

	////////////////////
	// Function name    : GetPKName
	// Description      : ���⿡ ���� Īȣ�� ��ȯ
	// Return type      : int
	//                  : -5 ���� +5���� ������� ī��������,��ũ�γ���Ʈ,�ƿ���,�ǽ�ĳ����,�Ӵ���,�Ϲ�,���,����Ʈ����,�����,����Ʈ����Ʈ,�������������
	int GetPKName();

	////////////////////
	// Function name    : IsSetPlayerState
	// Description      : ���� �ʵ尡 �� �Ǿ� �ִ��� �˻�
	bool IsSetPlayerState(int checkstate)
	{
		return ((m_state & checkstate) ? true : false);
	}

	////////////////////
	// Function name    : SetPlayerState
	// Description      : ���� �ʵ� ����
	void SetPlayerState(int checkstate)
	{
		m_state |= checkstate;
	}

	////////////////////
	// Function name    : ResetPlayerState
	// Description      : ���� �ʵ� ����
	void ResetPlayerState(int checkstate)
	{
		if(checkstate == ~0)
		{
			//������ ��ų�� ����, ��ũ�Ͻ� ���´� ��� �ʱ�ȭ�� ���ش�.(�ʱ�ȭ �Ǵ� ��ų�� �ְ� �ȵǴ� ��ų�� �־� �������� �ϵ��ڵ��� ��. �����ʿ�)
			if(IsSetPlayerState(PLAYER_STATE_FLYING))
			{
				toggleOff(FLY_SKILL, TOGGLE_SKILL);
			}
			if(IsSetPlayerState(PLAYER_STATE_DARKNESS))
			{
				toggleOff(DARKNESS_SKILL, TOGGLE_SKILL);
			}
		}
		
		m_state &= ~checkstate;
		return;
	}

	////////////////////
	// Function name    : TogglePlayerState
	// Description      : ���� �ʵ� ���
	void TogglePlayerState(int checkstate)
	{
		m_state ^= checkstate;
	}

	////////////////////
	// Function name    : GetPlayerState
	// Description      : ���� ��ȯ
	int GetPlayerState()
	{
		return m_state;
	}

	////////////////////
	// Function name    : IsCombatMode
	// Description      : ���� ���� �˻�, �ֱ� ������ ���� �ð�(PULSE_ATTACKMODE_DELAY)�� �����°�
	bool IsCombatMode();

	////////////////////
	// Function name    : CanMove
	// Description      : �̵� ���� �˻�
	virtual bool CanMove();

	////////////////////
	// Function name    : CanAttack
	// Description      : ���� ���� �˻�
	virtual bool CanAttack();

	////////////////////
	// Function name    : CanSpell
	// Description      : ���� ���� �˻�
	virtual bool CanSpell();

	////////////////////
	// FN : GiveItem
	// ������ ���� / ����
	bool GiveItem(int itemIndex, int plus, int flag, LONGLONG itemNum, bool bdrop = false , bool bOption = false );

	////////////////////
	// Function name    : GetSize
	// Description      : ĳ���� ũ�� ��ȯ
	virtual float GetSize()
	{
		return 0.0f;
	}

	bool IsParty()
	{
		return (m_party && m_party->GetRequestIndex() != m_index && m_party->GetMemberCount() > 1) ? true : false;
	}

	bool	IsExped()
	{
		return (m_Exped && m_Exped->GetRequestIndex() != m_index && m_Exped->GetMemberCount() > 1) ? true : false;
	}

	virtual int GetUsingStat() const
	{
		if (m_wearInventory.wearItemInfo[WEARING_WEAPON]) return m_wearInventory.wearItemInfo[WEARING_WEAPON]->GetUsingStat();
		else return USING_STR;
	}

	void SetMessengerCondition(int condition)
	{
		m_nCondition = condition;
	}
	bool AddBlockPC(int charIndex, const char* name);
	void ReleaseBlockPC(int charIndex, CLCString& name);
	// ����Ʈ�� �̸��� �ֽ����� �����Ҽ� �����Ƿ� ���� ������ ȣ���Ҷ� �ֽ����� �����Ѵ�
	bool IsBlockPC(int charIndex, const char* name );
	void GetBlockListString(CLCString& blockIndexList, CLCString& blockNameList);
#ifdef CLOUD_AUTO_QUEST_DELIVERY
	void do_QuestAutoPrize(CPC* ch, CQuest* pQuest);//Cloud auto quest
#endif
	void do_QuestGiveUp(CPC* ch, CQuest* quest);//레벨업에 의한 퀘스트 강제 포기.

	bool CheckDungeonData(int zone);

	virtual int GetResistLevelBonus()
	{
		switch (m_job)
		{
		case JOB_MAGE:
		case JOB_HEALER:
		case JOB_SORCERER:
		case JOB_NIGHTSHADOW:
			return m_level;
		default:
			return m_level / 2;
		}
	}

	// ���� ���� �÷��� ���ϱ�
	int GetJoinFlag(int zoneindex);

	// ���� ���� �÷��� ����
	void SetJoinFlag(int zoneindex, int value);

#ifdef REFORM_PK_PENALTY_201108 // PK �г�Ƽ ����
	int m_pkPenaltyReward;
	void SetPKPenaltyReward(int titleNum)
	{
		m_pkPenaltyReward |= ( 1 << titleNum );
	}
	int  CheckPKPenaltyReward(int titleNum)
	{
		return m_pkPenaltyReward & ( 1 << titleNum );
	}
	int	 GetPKPenaltyRewardNum();

	int	m_pkDispositionRateValue;	// PK ���� ��ġ ��� ������ %
	int	m_pkDispositionAddValue;	// PK ���� ��ġ ��� ������ %

	bool IsChaotic()
	{
		return (m_pkPenalty < 0 ) ? true : false;    // ī��ƽ ĳ���� �Ǻ�
	}
	void AddPkPenalty(int penalty);
#else
	bool IsChaotic()
	{
		return (m_pkPenalty < -9) ? true : false;    // ī��ƽ ĳ���� �Ǻ�
	}
#endif

	// ���� �����/������/����ġ ���� �����Ѵ�
	void UpdatePetValue();
	// �� ����Ʈ���� Ư�� INDEX�� ���� ã�´�
	CPet* GetPet(int index = 0);
	// �� ����
	void DelPet(int petIndex);
//#endif

	// ���� �����/������/����ġ ���� �����Ѵ�
	void UpdateAPetValue();
	// �� ����Ʈ���� Ư�� INDEX�� ���� ã�´�
	CAPet* GetAPet(int index = 0);          // 0 �̸� ���� ������ ��
	// �� ����
	void DelAPet(int petIndex);

	// target���� pvp ���� ���� �˻�, �������ϸ� ������� ����
	bool CanPvP(CCharacter* target, bool bIgnoreInvisible);

	// ���� ����
	void CancelChange();

	// ��ȯ
	CElemental* SummonElemental(char elementalType);
	// ��ȯ ����
	void UnsummonElemental(CElemental* elemental);
	// ��ȯ ���� �˻� : �ߺ�, ���ü�ȯ, ��ȯ�ð�
	bool CanSummonElemental(char newElementalType, char* duplicationType, int* nRemainTimeSummon, bool* errElementalType);
	// ��ȯ�� ���
	CElemental* GetElemental(int elementalindex);
	// ��ȯ�� �������� ������ : ����� �͸�
	void SendElementalStatus();

	// ����
	void ChangeEvocationState(int skillIndex);
	// ���� ����
	void Unevocation();

	void changeToggleState(int index, int toggle_type);
	void toggleOff(int index, int toggle_type);	
	void SendToggleState(int index, bool toggle, int toggle_type);

	void SendHolyWaterStateMsg(CItem* item);

	// ���� ���� �ð�
	int GetRemainEvocation(bool bSec);
	// �нú� ��ų ����
	void ApplyPassive();

	////////////////////
	// Function name    : ProcDisconnect
	// Description      : ���̵�, ���� ���� ��� ��Ƽ, ��ȯ, ���� �� ó��
	// Argument         : bool bDisconnect
	//                  : ���� ���� ����, ����� ���̾� ���� ������ ���� ������ ����
	// Argument         : bool bGoto
	//                  : ���� ���� �̵����� ȣ�� �� ���
	void ProcDisconnect(bool bDisconnect, bool bGoto);

	// �ڵ� ����, ������ɼ� ���� �α� �����
	void OutputDBItemLog();

	virtual float GetHitrate(CCharacter* df, MSG_DAMAGE_TYPE type);
	virtual float GetAvoid(CCharacter* of, MSG_DAMAGE_TYPE type);

	void SetRespondTime(long time)
	{
		m_nRespondTime = time;
	}
	long GetRespondTime()
	{
		return m_nRespondTime;
	}

	vec_monster_combo_data_t	m_listSaveComboData;

	char m_bPressCorps;
	void ApplySetItemValue(CItem * pItem);
	void ApplyOriginOption(CItem * pItem);
	void RemoveSetItemValue(CItem * pItem);
	void CountSetItem(CItem* pItem, bool bPlus = true);

	int GetSealPos(int nSkillIdx)
	{
		for (int i = 0; i < MAX_SEAL_TYPE_SKILL; i++)
		{
			if (m_sealSkillExp[i].nSkillIdx == nSkillIdx)
				return i;
		}
		return -1;
	}

	LONGLONG GetSealExp(int nSkillIdx)
	{
		int nPos = GetSealPos(nSkillIdx);
		if (nPos > -1 && nPos < MAX_SEAL_TYPE_SKILL)
			return m_sealSkillExp[nPos].llExp;

		return 0;
	}

	void SetSealExp(int nSkillIdx, LONGLONG llExp)
	{
		int nPos = GetSealPos(nSkillIdx);
		if (nPos > -1 && nPos < MAX_SEAL_TYPE_SKILL)
			m_sealSkillExp[nPos].llExp = llExp;
	}

	void AddSealSkill(int nSkillIdx)
	{
		int nPos = -1;
		for (int i = 0; i < MAX_SEAL_TYPE_SKILL; i++)
		{
			if (m_sealSkillExp[i].nSkillIdx < 0)
			{
				nPos = i;
				break;
			}
		}

		if (nPos > -1 && nPos < MAX_SEAL_TYPE_SKILL)
		{
			m_sealSkillExp[nPos].nSkillIdx  = nSkillIdx;
			m_sealSkillExp[nPos].llExp      = 1;
		}
	}


// [101214: selo] ���� ������ ��� ����
	bool CheckInvenForQuestPrize(const CQuestProto* pQuestProto, const int& optItemIndex);
	bool CheckInvenForProduceNoramlPrize(const int& itemdbIndex, const int& grade, const int& boost);
	bool CheckInvenForProduceRandomPrize();
	bool CheckInvenForProcessPrize(CItemProto* pItemProto);
	bool CheckInvenForTresureBoxPrize(CItem* pItem);
	bool CheckInvenForPrize(int nItemIndex, int plus, int flag, int count=1);
	bool CheckInvenForPrize(CItemProto* pItemProto, int plus, int flag, int count=1);

	void GuildGradeSkill( bool apply );
	void ApplyGuildGradeSkill()
	{
		GuildGradeSkill(true);
	}
	void CureGuildGradeSkill()
	{
		GuildGradeSkill(false);
	}

	bool	CheckCastellanType(int& zonenum, char& castellan);

// [110207:selo] �� �� �ǻ�
	const int GetSuitWearingPos(const int& pos)
	{
		return m_suitWearingPos[pos];
	}
	int m_suitWearingPos[COSTUME2_SUIT_MAX_WEARING];

private:
	void Clean();
	void CleanSummonNPC();
	void CleanTaming();
	void CleanParty();
	void CleanExchange();
	void CleanExtreamCube();

private:
	int m_nKillCount;
	int m_nTotalKillCount;
	int m_nDeathCount;
	int m_nTotalDeathCount;
	int m_nWarGroundPoint;
	int m_nWarGroundAccPoint;
public:
	int GetKillCount();
	int GetTotalKillCount();
	int GetDeathCount();
	int GetTotalDeathCount();
	int GetWarGroundPoint();
	int GetWarGroundAccPoint();

	void InitKillCount();
	void AddKillCount(int n);
	void SetTotalKillCount(int n);
	//void AddTotalKillCount(int n);
	void InitDeathCount();
	void AddDeathCount(int n);
	void SetTotalDeathCount(int n);
	//void AddTotalDeathCount(int n);
	void SetWarGroundPoint(int n);
	void AddWarGroundPoint(int n);
	void SetWarGroundAccPoint(int n);
	//void AddWarGroundAccPoint(int n);

public:
	CPetStashManager m_petStashManager;

public:
	bool m_bRockPaperScissorsFlag;
	void setRockPaperScissorsFlag();
	bool getRockPaperScissorsFlag();
#ifdef XTRAP
	char		m_xtrapSessionBuf[320];
	void xTrapSessionInit();
#endif

public:
	SyndicateManager  m_syndicateManager;
	bool isSyndicate();

#ifdef DURABILITY
	void calcDurability_for_weapon();
	void calcDurability_for_armor();
#endif

	bool m_first_inmap;
	
	typedef std::map<int, int> map_t;
	map_t itemSkill;

	CGPSManager m_gpsManager;
	ArtifactGPSManager m_arti_gpsManager;

	CPC* m_targetPC;				//���� ������ Ÿ���� �ε���

	//��ġ ������
private:
	bool m_isSearchLife;
public:
	void setSearchLife(bool isSearchLife) { m_isSearchLife = isSearchLife; }
	bool IsSearchLife() { return m_isSearchLife; }

public:
	
	CItem* holy_water_item;
	std::vector<CItem*> m_deadnpc_toggle_item;

	ItemCollectionManager m_itemCollectionManager;
	
	//��� ���ɾ� ����
	bool	m_isNotCoolBoxItem;
	CAttendanceManager m_attendanceManager;

#ifdef PREMIUM_CHAR
public:
	PremiumChar m_premiumChar;
#endif

	//���ӽ� ������ ���� ����
	bool m_firstSendData;
	//���� ��ų üũ ����
	bool m_isWarSkillCheck;

	// Loot Filter System
	CLootFilter m_lootFilter;

	bool isWarZone();

	bool bMoveInsDunFinish;		// �ν��Ͻ� ���� ����� ������ ������ �Ǿ������� �Ǵ��ϱ� ���� ���� (�ٽ� ������ �ʴ� �̻� �ʿ���...)

	std::map<int, MAKE_TITLE*> _map_title;
	int	m_custom_title_index;

	std::vector<int> m_vecUsePromoKey;

	bool use_express_flag;
	bool m_bDebugMode;
};

////////////
// NPC class
class CNPC : public CCharacter, public MemoryPoolBaseWithMutex<CNPC>
{
public:
	CNPC();
	virtual ~CNPC();

	CNPCProto*  m_proto;        // DB ����ġ

	int         m_idNum;        // �� ���̵� ��ȣ(DB index)
	int         m_flag;         // Flag
	int         m_flag1;        // Flag1(Ȯ�� �÷���)
	float       m_regenX;
	int         m_regenY;
	float       m_regenZ;
	int         m_disableTime;  // ���� ���� �� ���̴� �ð�
	int         m_delay;        // ������ ����

// 050322 : bs : ���� ���� ������ ���� �߰�
	int         m_pulseAttack;  // �ֱ� ���� �ð� : gserver->m_pulse�� ���� ��
// --- 050322 : bs : ���� ���� ������ ���� �߰�

	char        m_attackType;   // �⺻���ݹ��
	int         m_postregendelay;   // ���� ���� ���� �ϱ� �������� �ð� ������

	// �̵�����
	bool        m_bMoveRun;     // �ٴ°� true �ȴ°� false
	int         m_nBlockRegen;  // ������ġ�� ���� �ִµ� �������ؼ� �� �� ��� ī��Ʈ
	// ������ �ູ���� ������ PC �ε���
	bool        m_bStop;        // ���ִ°�
	int         m_moveArea;     // �̵� ����

	// AI ����
	int         m_aipulse;      // NPC AI Pulse
	int         m_moveDir;      // �̵� ���� ������ : 1 ���� : -1 ���� : 0
	int         m_nBlockAI;     // AI ����� �̵���ο��� �������� ��
	bool        m_bChangeDir;   // �̵������� �ٲ��� �ϴ°�
	bool        m_bFail45;      // 45�� ���Ⱑ �����ΰ�

	int         m_quest[QUEST_MAX_NPC];         // ����Ʈ NPC ����Ʈ ��ȣ ����
	int         m_nQuestCount;                  // ����Ʈ ����

	// 050221 : bs : NPC ��ų
	CSkill*     m_skills[MAX_NPC_SKILL];
	// --- 050221 : bs : NPC ��ų

	int         m_regenTime;	//#if defined(SYSTEM_TREASURE_MAP)

	int         m_regenTimeXmas2007;

	CNPC*       m_pNPCPrev;     // NPC ����Ʈ ��ũ
	CNPC*       m_pNPCNext;     //

	CNPCRegenInfo* m_regenInfo;

	int         m_nRaidMoveTime;            // ������ ���� �ð�
	int         m_bRaidNPCSummon;           // ���̵� ���� ��ȯ�ߴ��� ����

	int			m_ctCount;					// �����̻� �鿪 ī��Ʈ ����(������ �غ���)
	int			m_ctTime;					// �����̻� �鿪 ȸ�� �ð� ����

	int m_MobScrollType;
	int m_NextMobIndex;
	int m_UseCharIndex;

	int     m_coinidx;
	int     m_coincount;

#ifdef MONSTER_AI
	float   m_nOldDist;                     // ������ �̵� �� ��ġ
	bool    m_bMoveLock;                    // ���� ���� ����
	int     m_pulseMoveLock;                // ���� �ð�
	int     m_bMoveToRegen;                 // ���� ��ġ�� �̵� ����
#endif

	int     m_Mob_State;                    // ���Ͱ� ���̹��� �Ǿ��°�? �ƴϸ� ȥ���ΰ�?
	CPC*    m_owner;                        // ���͸� ���̹��� ĳ����
	int		m_pulseSoulRecover;				// ���Ͱ� ��ȥ�� ���ѱ� �� �ٽ� ����� ������
	int		m_lifetime;

	CPC*    GetOwner();
	void    SetOwner(CPC* pc)
	{
		m_owner = pc;    // ������ ����
	}

	int     Check_MobFlag(int mask) const
	{
		return m_Mob_State & mask;
	}
	void    Set_MobFlag(int state)
	{
		m_Mob_State |= state;
	}
	void    reSet_MobFlag(int state)
	{
		m_Mob_State &= ~state;
	}

	void        DeleteNPC();    // npc�� Ÿ�ϸ���Ʈ�� ���ø���Ʈ���� �����θ� �����ϰ� �޸� ����
	void        InitAIVar();    // AI ���� ���� �ʱ�ȭ
	void        ResetStat();    // �������� ������ ��ġ�� �ʱ�ȭ

	////////////////////
	// Function name    : CanMove
	// Description      : �̵� ���� �˻�
	virtual bool CanMove();

	////////////////////
	// Function name    : CanAttack
	// Description      : ���� ���� �˻�
	virtual bool CanAttack();

	////////////////////
	// Function name    : GetAttackLevel
	// Description      : ���� ���� ���ϱ�
	virtual int GetAttackLevel();

	////////////////////
	// Function name    : GetDefenseLevel
	// Description      : �� ��� ���� ���ϱ�
	virtual int GetDefenseLevel();

	////////////////////
	// Function name    : GetAttackType
	// Description      : �⺻ ������ ���� ���Ÿ� ���� ������ ������
	virtual MSG_DAMAGE_TYPE GetAttackType(const CSkillProto* proto) const;

	////////////////////
	// Function name    : GetSize
	// Description      : ĳ���� ũ�� ��ȯ
	virtual float GetSize()
	{
		if (m_proto)
			return m_proto->m_bound;
		return 0;
	}

	virtual int GetUsingStat() const
	{
		if (GetAttackType(NULL) == MSG_DAMAGE_RANGE) return USING_DEX;
		else return USING_STR;
	}

	CSkill* FindSkill(int idx);

	// �нú� ��ų ���� : NPC�� ����
	void ApplyPassive() {}

	// ���� ����
	void CalcStatus(bool bSend);

	// �ڽ��� ������ ������ �� ������ ������ ��ȯ
	LONGLONG GetTotalDamage();

	virtual float GetHitrate(CCharacter* df, MSG_DAMAGE_TYPE type);
	virtual float GetAvoid(CCharacter* of, MSG_DAMAGE_TYPE type);

#ifdef EXTREME_CUBE
	bool m_bCubeRegen;
#endif // EXTREME_CUBE

#ifdef MONSTER_AI
	float GetDistToRegen();                 // ������ġ�� �Ÿ�
#endif

	MonsterMercenaryData * m_pMercenaryClassData;
	void SetMercenaryClassData(MonsterMercenaryData * pClass)
	{
		m_pMercenaryClassData=pClass;
	}
	MonsterMercenaryData * GetMercenaryClassData()
	{
		return m_pMercenaryClassData;
	}

	int IsFlag(int npcflag)
	{
		return m_flag & npcflag;
	}
	int IsFlag1(int npcflag)
	{
		return m_flag1 & npcflag;
	}
	int GetFlag()
	{
		return m_flag;
	}
};

class CPet : public CCharacter, public MemoryPoolBaseWithMutex<CPet>
{
	friend class DBManager;
	friend class DBProcess;

	CPC*    m_owner;            // �� ����
	char    m_petTypeGrade;     // �� ���� + ���

	int     m_hungry;           // �����
	int     m_pulseHungry;      // ����� �޽�
	int     m_sympathy;         // ������
	int     m_pulseSympathy;    // ������ �޽�
	int     m_abilityPoint;     // ��� ����Ʈ

	int     m_pulseExpUp;       // ����ġ ȹ�� �޽�

	char    m_petColorType;
	int     m_nTurnToNpcIndex;
	int     m_nTurnToNpcSize;

	bool    m_bSummon;          // ��ȯ�Ǿ����� ����
	bool    m_bMount;           // Ÿ�� �ִ��� ����
	bool    m_wasnear;          // 050309: bw 20���� ���� �ִ��� �ۿ� �ִ����� ��ȭ

	// 060221 : bs : �� ����� �����ð� ����Ҵ�����
	int     m_nRemainRebirth;   // ��Ȱ ���� �ð�

	CSkillList m_skillList;     // ��ų ����Ʈ

public:

	CPet*   m_prevPet;
	CPet*   m_nextPet;
	time_t	m_petStashSeconds;	// �� â�� �޽�
	time_t	m_petStashHungrySeconds; // �� â�� ����� ����

	CPet(CPC* owner, int index, char petTypeGrade, int level);
	~CPet();

	////////////
	// �⺻ ����
	void resetStashTimer();

	// ������ ��ȯ
	CPC* GetOwner()
	{
		return m_owner;
	}

	// ������ ����
	void SetOwner(CPC* pc)
	{
		m_owner = pc;
	}

	// �� ���� ���ϱ�
	char GetPetType()
	{
		return (m_petTypeGrade & PET_TYPE_MASK);
	}

	// �� ��� ���ϱ�
	char GetPetGrade()
	{
		return (m_petTypeGrade & PET_GRADE_MASK);
	}

	// ���� Ż�� �ִ��� �˻�
	bool IsMountType()
	{
		return (GetPetGrade() == PET_GRADE_MOUNT);
	}

	// �� ���� + ��� ���ϱ�
	char GetPetTypeGrade()
	{
		return m_petTypeGrade;
	}

	// ������ ������ �°� �ʱ�ȭ : HP/MP �� ��ġ �ִ�ġ ����
	void InitStat();

	// ���� ����Ǿ� �ִ��� �˻�
	bool IsWearing()
	{
		return (m_owner && m_owner->m_wearInventory.wearItemInfo[WEARING_PET] != NULL && m_owner->m_wearInventory.wearItemInfo[WEARING_PET]->getPlus() == m_index);
	}

	// ���� ��ȯ �Ǿ� �ִ��� �˻�
	bool IsSummon()
	{
		return m_bSummon;
	}

	// ���� Ÿ�� �ִ��� �˻�
	bool IsMount()
	{
		return m_bMount;
	}

	// ��ȯ/Ÿ�� ���� ����
	void ResetSummonMountFlag()
	{
		m_bSummon = false;
		m_bMount = false;
	}

	// �ֿϵ����� ��Ÿ���� ��
	void Appear(bool bIncludeOwner);

	// �ֿϵ����� ������� ��
	void Disappear();

	// Ÿ�� ���⸮
	void Mount(bool bMount);

	// 060221 : bs : �� ��Ȱ ���� �ð� ����
	void SetRemainRebirthTime(int nRemainRebirth = -1);

	// 060221 : bs : �� ��Ȱ ���� �ð� ��ȯ
	int GetRemainRebirthTime()
	{
		return m_nRemainRebirth;
	}

	// 060309 : bw : ���� ������ �Ÿ� ����
	void SetWasNear(bool bnear)
	{
		m_wasnear = bnear;
	}
	bool WasNear()
	{
		return m_wasnear;
	}
	float GetDistanceFromOwner();
	void ChangePetType();

	//////////////
	// ����� ����

	// �ൿ �Ҵ� �˻�
	bool IsActive()
	{
		return (m_hungry > 0);
	}

	// ����� ��ġ ��ȯ
	int GetHungryPoint()
	{
		return m_hungry;
	}

	// ����� ��ġ ����, ��ġ ����� true ��ȯ
	bool DecreaseHungryPoint();

	// 1ȸ�� ����� ��ġ �������� �� ���ϱ�
	int GetUnitForHungry()
	{
		return (m_owner->m_level < m_level) ? (m_level - m_owner->m_level) / 2 + 1 : 1;
	}

	// ����� ��ġ ����, ��ġ ����� true ��ȯ
	bool IncreaseHungryPoint(int val);

	//////////////
	// ������ ����

	// ������ ��ġ ��ȯ
	int GetSympathyPoint()
	{
		return m_sympathy;
	}

	// ������ ��ġ ����, ��ġ ����� true ��ȯ, 050309: bw ��ó�� ���� ������ ���Ҹ���
	bool UpdateSympathyPoint(bool bnear = false);

	// ������ ��ġ �ö󰡴� ���� �ð� ���ϱ�
	int GetUnitForSympathy()
	{
		return (m_owner->m_level < m_level) ? (m_level - m_owner->m_level) / 2 + PULSE_PET_SYMPATHY_INCREASE : PULSE_PET_SYMPATHY_INCREASE;
	}

	// ������ ���
	bool IncreaseSympathyPoint(int val);
	#ifdef PET_BUFF_ALL_SYSTEM
	void ApplyAllBuffs();
	#endif
	////////////
	// ���� ����

	// ������ �ʿ� ����ġ ��ȯ
	LONGLONG GetNeedExp()
	{
		if( m_level <= 100 )
			return (LONGLONG)(600 * pow(1.09, m_level));
		else
			return (LONGLONG)(65000 * pow(1.04, m_level));
	}

	// ����ġ ����, ��ġ ����/������ �ÿ� true
	bool AddExp();

	void SetPetColor( char colorType = 0 )
	{
		m_petColorType = colorType;
	}
	char GetPetColor( void )
	{
		return m_petColorType;
	}

	void SetPetTurnToNpc( int npcIndex =0 )
	{
		m_nTurnToNpcIndex = npcIndex;
	}
	int GetPetTurnToNpc( void )
	{
		return m_nTurnToNpcIndex;
	}
	void SetPetTurnToNpcSize( int size = 10 )
	{
		m_nTurnToNpcSize = size;
	}
	int GetPetTurnToNpcSize( void )
	{
		return m_nTurnToNpcSize;
	}

	// ������ ó�� : ���� �������� ó��, ����/����ġ/AP ���� ������ ȣ���ؾ� ��
	void LevelUp();

	// ��� ����Ʈ ��ȯ
	int GetAbilityPoint()
	{
		return m_abilityPoint;
	}
	void SetAbilityPoint(int value)
	{
		m_abilityPoint = value;
	}


	// ��� ����Ʈ ����
	int DecreaseAbilityPoint(int val)
	{
		m_abilityPoint -= val;
		if (m_abilityPoint < 0) m_abilityPoint = 0;
		return m_abilityPoint;
	}

	// ��� ����Ʈ ����
	int IncreaseAbilityPoint(int val)
	{
		m_abilityPoint += val;
		return m_abilityPoint;
	}

	// ����Ʈ Ÿ������ ����
	void ChangeToMount()
	{
		m_petTypeGrade = GetPetType() | PET_GRADE_MOUNT;
		InitStat();
	}

	// �� ����Ʈ Ÿ�� ���
	void ResetMountType()
	{
		m_petTypeGrade = GetPetType() | PET_GRADE_ADULT;
		InitStat();
	}

	////////////
	// ��ų ����

	// Ư�� �ε��� ��ų ���ϱ�
	CSkill* FindSkill(int skillindex);

	// ��ų �߰�
	void AddSkill(CSkill*& skill);

	// ��ų ����Ʈ ��ȯ
	CSkillList* GetSkillList()
	{
		return &m_skillList;
	}

	// ��ų �ʱ�ȭ
	bool ResetSkill();

	/////////////////////////////
	// virtual function implement
	virtual int GetAttackLevel()
	{
		return 1;
	}
	virtual int GetDefenseLevel()
	{
		return 1;
	}
	virtual MSG_DAMAGE_TYPE GetAttackType(const CSkillProto* proto) const
	{
		return MSG_DAMAGE_MELEE;
	}
	virtual float GetSize()
	{
		return 0.5f;
	}
	virtual int GetUsingStat() const
	{
		return USING_STR;
	}

	// �нú� ��ų ���� : Pet�� ����
	void ApplyPassive() {}

	// ���� ���� : Pet�� ����
	void CalcStatus(bool bSend) {}

	virtual float GetHitrate(CCharacter* df, MSG_DAMAGE_TYPE type);
	virtual float GetAvoid(CCharacter* of, MSG_DAMAGE_TYPE type);
};

class CElemental : public CCharacter, public MemoryPoolBaseWithMutex<CElemental>
{
	static int  m_nVirtualIndex;            // ���� �ε���

	CPC*        m_owner;                    // ������

	char        m_elementalType;            // ��ȯ�� ����

	int         m_defStr;                   // �⺻ ����
	int         m_defDex;
	int         m_defInt;
	int         m_defCon;

	int         m_defHP;                    // �⺻ HP

	int         m_defAttackLevel;           // �⺻ ����
	int         m_defDefenseLevel;

	int         m_pulseRemain;              // ��ȯ ���� �ð�

	CSkillList  m_skillList;                // ���� ��ų ����Ʈ (��Ƽ��/�нú�)

public:
	bool        m_bChangeStatus;            // ���º�ȭ����

	CElemental* m_prevElemental;
	CElemental* m_nextElemental;

public:
	CElemental(CPC* owner, char elementalType);

	// ������ ��ȯ
	CPC* GetOwner()
	{
		return m_owner;
	}

	// ��ȯ�� Ÿ�� ��ȯ
	char GetElementalType()
	{
		return m_elementalType;
	}

	// ��ȯ�� ���� �ð� ��ȯ
	int GetRemainTime()
	{
		return m_pulseRemain;
	}

	// ��ȯ�� ���� �ð� ���� : ��ȯ �ٵǸ� true ��ȯ
	bool DecreaseRemainTime()
	{
		m_pulseRemain--;
		if (m_pulseRemain < 0) m_pulseRemain = 0;
		return (m_pulseRemain <= 0) ? true : false;
	}

	// ��ȯ�� ��ų �߰�
	void AddSkill(int skillindex, int level);

	// ��ȯ�� �ɷ�ġ �ʱ�ȭ : ���� hp ���� ����
	void ResetStat();

	// �ɷ�ġ ����
	void CalcStatus(bool bSend);

private:
	int GetVirtualIndex()
	{
		if (m_nVirtualIndex < 1) m_nVirtualIndex = 1;
		return CElemental::m_nVirtualIndex++;
	}

	// virtual functions
public:
	int GetAttackLevel()
	{
		return m_defAttackLevel;
	}
	int GetDefenseLevel()
	{
		return m_defDefenseLevel;
	}
	MSG_DAMAGE_TYPE GetAttackType(const CSkillProto* proto) const;
	float GetSize()
	{
		return 0.0f;
	}
	int GetUsingStat() const
	{
		return USING_DEX;
	}
	CSkill* FindSkill(int skillindex);
	void ApplyPassive();

	virtual float GetHitrate(CCharacter* df, MSG_DAMAGE_TYPE type);
	virtual float GetAvoid(CCharacter* of, MSG_DAMAGE_TYPE type);
};


typedef struct __tagApetAIData
{
	int     nItemNum;       // DB index
//  int     nItemIdx;       // Unique index
	CItem * pItem;
	int     nSkillIdx;
	int     nSkillType;     // skill - 0, action - 1
	char    cUse;
} APET_AI_DATA;

class CAPet : public CCharacter, public MemoryPoolBaseWithMutex<CAPet>
{
private:
	CPC* m_pOwner;

	int     m_nHpMpPulse;
	int     m_nStmPulse;
	int     m_nDStmPluse;
	int     m_nFaithPulse;
	int     m_nDFaithPulse;
	time_t	m_nPetStashSeconds;

	int m_nFaith;
	int m_nStm;

	LONGLONG	m_llAccExp;
	int			m_nRemainCooltime;

public:

	CAPet();
	~CAPet();

	// List
	CAPet*      m_pPrevPet;
	CAPet*      m_pNextPet;

	bool m_bSummon;         // ��ȯ�Ǿ����� ����
	LONGLONG m_nSP;
	int m_nRemainStat;

	int m_nSeal;

	int m_nPlusStr;
	int m_nPlusCon;
	int m_nPlusDex;
	int m_nPlusInt;

	int m_nAttack;
	int m_nMagicAttack;
	int m_nDefence;
	int m_nMagicDefence;

	int m_nHitPoint;
	int m_nMagicHitPoint;
	int m_nAvoid;
	int m_nMagicAvoid;

	int m_nJewelAttack;
	int m_nJewelMagicAttack;
	int m_nJewelDefence;
	int m_nJewelMagicDefence;

	CAPetProto* m_pProto;
	CSkillList  m_skillList;            // Skill only  Active

	CSkillList m_passiveSkillList;

	CItem*      m_wearing[APET_WEARPOINT];

	char m_cAI;
	int  m_nAICount;
	int  m_nAISlot;
	APET_AI_DATA m_tAIData[APET_MAX_AI];

	int				m_nDelay;					// �� ���� ������ �����ð�
	unsigned int	m_nAccStemina;				// �������Ҷ� ���� ä��
	unsigned int	m_nAccFaith;				// �������Ҷ� ���� �漺��
	int				m_optTransEnd;				// ���� ������ ���� ���� �ɼǰ�
	char			m_cTransSate;				// ���� ���� 0:�Ϲ� 1:����
	bool			m_bMount;					// Ÿ�����
	char			m_cSendTransMsg;			// �����غ� �޼��� �˸� ��Ȳ
	char			m_cForceTrans;				// ���� ���� ����

	bool			TransFormationCheck();
	void			Mount( bool bMount );
	bool			IsMount()
	{
		return m_bMount;
	}

	// Function
	void	resetStashTimer();

	void    SetOwner(CPC* pc)
	{
		m_pOwner = pc;    // ������ ����
	}
	void    SetFaith(int faith)
	{
		m_nFaith = faith;    // �漺�� ����
	}
	void    SetStamina(int stm)
	{
		m_nStm = stm;    // ���׹̳� ����
	}
	void    AddFaith(int faith); // �漺�� ���� ( ����ó�� )
	void    AddStamina(int stm); // ���׹̳� ���� ( ����ó�� )

	CPC*    GetOwner()
	{
		return m_pOwner;    // ������ ��ȯ
	}
	int     GetFaith()
	{
		return m_nFaith;    // �漺��
	}
	int     GetStamina()
	{
		return m_nStm;    // ���׹̳�
	}
	int     GetStmLevel();                                  // ��ƻ���
	int     GetFaithLevel();                                // �漺�� ����

	bool    IsSummon()
	{
		return m_bSummon;    // �ۿ� ��ȯ ����
	}

	CItem*  AddToWearItem( CItem* item );                   // Pet ���� ����
	void    Appear(bool bIncludeOwner , bool bAction = false );
	void    Disappear();

	bool    IsWearing()
	{
		return ( m_pOwner && m_pOwner->m_wearInventory.wearItemInfo[WEARING_PET] != NULL && m_pOwner->m_wearInventory.wearItemInfo[WEARING_PET]->getPlus() == m_index);
	}
	bool    IsPetEquip()
	{
		return ( m_wearing[APET_WEAR_HEAD] || m_wearing[APET_WEAR_BODY] || m_wearing[APET_WEAR_WEAPON] || m_wearing[APET_WEAR_ACCE] )? true : false;
	}

	bool    IncreaseStat();         // �ð��� ���� �����Ǵ� ��ġ
	bool    DecreaseStat();         // �ð��� ���� ���ҵǴ� ��ġ
	void    CheckItemTime();        // ����� ������ �ð� Ȯ��

	void    UpdateStatPlus( int nStr, int nDex, int nInt , int nCon );

	LONGLONG    GetNeedExp()
	{
		if( m_level <= 100 )
			return (LONGLONG)(600 * pow(1.09, m_level));
		else
			return (LONGLONG)(65000 * pow(1.04, m_level));
	}

	bool        AddExpSP(LONGLONG exp, LONGLONG sp, bool bDirect = false);
	void        LevelUp(bool bSendEffect);  // ������ ȿ��
	void		AddExpSP_Direct(LONGLONG _exp, LONGLONG _sp);
	void		CalcLevelup();

	void        ApplyItemValue();           // ������ �ɷ�ġ ����
 //new2022
	#ifdef PET_BUFF_ALL_SYSTEM
	void ApplyAllBuffs();
	#endif
 //new2022//
	// Virtual Function
	////////////////////
	// Function name    : GetAttackLevel
	// Description      : ���ⷹ�� ���.
	virtual int GetAttackLevel();

	////////////////////
	// Function name    : GetDefenseLevel
	// Description      : �� ���� ���
	virtual int GetDefenseLevel();

	////////////////////
	// Function name    : GetAttackType
	// Description      : ���� Ÿ�� ���, ��ų �����䰡 ������ ��ų�� Ÿ��, NULL�̸� �⺻ Ÿ��
	virtual MSG_DAMAGE_TYPE GetAttackType(const CSkillProto* proto) const ;

	////////////////////
	// Function name    : GetSize
	// Description      : ĳ���� ũ�� ��ȯ
	virtual float GetSize()
	{
		return 0;
	}

	////////////////////
	// Function name    : GetUsingStat
	// Description      : ���ݽ� ����ϴ� ����
	virtual int GetUsingStat() const
	{
		if( m_wearing[WEARING_WEAPON]) return m_wearing[WEARING_WEAPON]->GetUsingStat();
		else return USING_STR;
	}

	virtual CSkill* FindSkill(int skillindex);
	// �нú� ��ų ����
	void AddSkill( CSkill* pSkill );
	void ApplyPassive();
	// ���� ����
	virtual void CalcStatus(bool bSend);

	// ��ȭ ( ����� �κ� )
	void Evolution( CAPet* copy );

	void InitStat();

	virtual float GetHitrate(CCharacter* df, MSG_DAMAGE_TYPE type);
	virtual float GetAvoid(CCharacter* of, MSG_DAMAGE_TYPE type);

	bool IsAI()
	{
		return (m_cAI == '1') ? true:false;
	}
	bool IsEmptyAILine(int nIndex)
	{
		return (!m_tAIData[nIndex].pItem || m_tAIData[nIndex].nSkillIdx < 0) ? true:false;
	}

	bool DelAIList(CItem * pItem);
	void CheckAIList();

private:
	void		SendStatusMsg();

public:
	bool		IsProtoFlag(const int _flag);
	LONGLONG	GetAccExp();			// ���� ������ ����ġ
	void		SetAccExp(LONGLONG _accExp)
	{
		m_llAccExp = _accExp;    // ����ġ ����. ��� ���ɾ���� ���
	}
	int			GetCooltime();				// ���� ���� ��Ÿ�� ( �� )
	void		SetCooltime(int _min);		// ��Ÿ�� ���� ( �� )
	void		ResetCooltime();

	double		GetAccRate(	int _petLevel );
	LONGLONG	GetMaxAccExp( int _petLevel, LONGLONG _charMaxExp );

	// ĳ���Ͱ� �Դ� ���� ����ġ, ĳ���Ͱ� �������� �ʿ��� ����ġ
	void AddAccExp( LONGLONG _exp , LONGLONG _charLevelupExp );
	void UseAccExp( CPC* _pc );
	bool UseAccExp( CAPet* _apet, bool bDirect = false );

	// DB ���� �ε��ϴ� �κ�
	void	LoadCooltime(int _cooltime )
	{
		m_nRemainCooltime = _cooltime;
	}
	void	LoadAccExp(LONGLONG _accexp )
	{
		m_llAccExp = _accexp;
	}

	void	applyItemPlusValue(int& value, int plus);
};

void CheckQuestCondition(CPC* ch, CItem* item, LONGLONG itemSum);

#endif
//
