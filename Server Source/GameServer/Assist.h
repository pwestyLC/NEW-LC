/************************************
  ��������
  ������ ���: bs
  ������: 2004-11-18 ���� 10:57:23
  ����: ��ų�� ȿ�� ���뿡�� �̸� ���� Ȯ�� �� ���
 ************************************/

/************************************
  ��������
  ������ ���: bs
  ������: 2004-11-17 ���� 3:22:34
  ����: CAssistList�� Apply �߰� - �� ���� �Լ�
 ************************************/

#ifndef __ASSIST_H__
#define __ASSIST_H__

#include "../ShareLib/packetType/ptype_appear.h"

class CNetMsg;

typedef struct _tagAssistValue
{
	int	attack;
	int	defense;
	int	magic;
	int	resist;
	int	hitrate;
	int	avoid;
	int	critical;
	int	attackspeed;
	int	magicspeed;
	int	movespeed;
	int	recoverhp;
	int	recovermp;
	int	maxhp;
	int	maxmp;
	int	deadly;
	unsigned char attratt;
	unsigned char attrdef;
	unsigned char attratt_item;
	unsigned char attrdef_item;
	int magichitrate;
	int magicavoid;
	int attackdist;
	int reduceMelee;
	int reduceRange;
	int reduceMagic;
#ifdef ASSIST_REDUCE_SKILL
	int reduceSkill;
#endif
	int reduceMeleeProb;
	int reduceRangeProb;
	int reduceMagicProb;
#ifdef ASSIST_REDUCE_SKILL
	int reduceSkillProb;
#endif
	int attack_dam_melee;
	int attack_dam_range;
	int hitrate_skill;
	bool immune_blind;
	int attack80;
	int maxhp450;
	int	hard;
	/////////////////////////////////////////////
	// BANGWALL : 2005-07-18 ���� 2:24:26
	// Comment : skill spd
	int skillspd;
	int statpall;
	// << 071226 kjban add
	int statpall_per;
	// >>
	int stronger_skill;
	int despair;
	int manascreen;
	int bless;
	int inverse_damage;
	int affinity;
	int affinity_rate;
	LONGLONG exp;
	int sp;
	LONGLONG exp_rate;
	int sp_rate;
#ifdef ASSIST_DECREASE_SKILL_MP
	int decreaseskillmp;
#endif
	int pvpabsorbrate;

	int		npcAttack;					// NPC���� ����/���Ÿ� ���ݷ� ����	/ PC���ݽ� ������
	int		npcMagic;					// NPC���� ���� ���ݷ� ����		/ PC���ݽ� ������
	int		SkillCooltime;

	// TODO : �ϵ��ڵ���
	bool hcExpPlus;
	bool hcSPPlus;
	int hcReflex;
	int hcReflexProb;			// addition������
	int hcDeathExpPlus;
	bool hcDeathSPPlus;
	MSG_CHAR_TYPE hcFearType;	// �Ǿ�
	int hcFearIndex;
	bool hcAttackTower;			// ���� ���ݽ� ����� 2��
	bool hcExpPlus_836;			// ����
	bool hcSPPlus_837;			// ����
	bool hcDropPlus_838;		// �ڵ�
	bool hcSepDrop;				// ��ӷ� ���
	bool hcSepDropPrem;	
	bool hcSepAffinityMob;
	bool hcSepExp;				// ����ġ ���
	bool hcSepSP;				// ��ų����Ʈ ���
	bool hcSepNas;				// ���� ���
// >> [100823: selo] ���� ������
	bool hcSepDrop_Cash;		// ��ӷ� ���
	bool hcSepExp_Cash;			// ����ġ ���
	bool hcSepExp_Prem;
	bool hcSepSP_Cash;			// ��ų����Ʈ ���
	//dethunter12
// << [100823: selo] ���� ������
	bool hcScrollDrop;			// ����ǽ�ũ�� : ��ӷ� ��� // ������ ��ũ�Ѱ� ������ ���� �����
	bool hcScrollDrop_11340;
	bool hcScrollDropCube;
	bool hcScrollSP;			// ����ǽ�ũ�� : SP ���
	bool hcScrollExp;			// �����ǽ�ũ�� : ����ġ ���
	bool hcExpPlus_S354;		// ����ġ ����
	bool hcScrollDrop_5081;
	int	hcDropPlus_Xmas2007;	// ũ���� ���� �̺�Ʈ ��� ��·�

	bool hcDropPlus_2141;		// ��� �ֹ���
	bool hcDropPlus_11339;
	int hcCashExpUp;			// 060227 : bs : ��������� ����ġ ���
	int hcCashMaxHPUp;			// 060227 : bs : ��������� HP Ȯ��
	int hcCashMaxMPUp;			// 060227 : bs : ��������� MP Ȯ��

	bool hcExpPlus_S355;		// ��õ�������� ����ġ ���
	bool hcSPPlus_S356;			// ��õ�������� SP ���
	bool hcDropPlus_S360;		// ��õ�������� ����� ���

	int hcExpPlusPer100;		// ����ġ ��� %���� ����
	int hcSPPlusPer100;			// ���õ� ��� %���� ����
	int hcDropPlusPer100;		// ����� ��� %���� ����

	int hcExpPlus_398;			// �����̽þ� ����ġ ���� : ���� ������ : 1840, 1841, 1842 : ������ %
	int hcExpPlus_1975;			// ����ũ : 2006 ũ��������
	int hcExpPlus_1976;			// ����� : 2006 ũ��������
	int HitRate_2033;			// ��Ű �ҿ� �н�  - ���߷� ��� 20%
	int	Avoid_2034;				// ��Ű ���� �Ǿ� - ȸ���� ��� 10%

	bool hcCashPetExpUp_2358;	// �� ������ ���� - ���� �ð� 3�ʴ� 2����Ʈ ����
	bool hcCashPetExpUp_2359;	// �÷�Ƽ�� �� ������ ���� - ���� �ð� 3�ʴ� 3����Ʈ ����
	bool hcCashPetExpUp_12077;

	bool bRorainOfLoveMagic;	// �η����� ������� :  ���� Ȯ���� ������ 10��

	bool hcMPSteelPotion;		// MP ��ƿ ���� : �Ϲ� ���ݽ� 30% Ȯ���� ������ Max MP �� 10% ���� ���� MP�� ����
	bool hcHPSteelPotion;		// HP ��ƿ ���� : �Ϲ� ���ݽ� 30% Ȯ���� ������ Max HP �� 5% ���� ���� HP�� ����

	bool hcExpSPPlus_2354;

	int hcExpPlus_2388;
	int hcExpPlus_2389;
	int hcSPPlus_2390;
	bool hcDropPlus_2391;

	int hcEventHalloweenMaxHP;
	int hcEventHalloweenSpeed;

	int		charge_attack;
	int		charge_magic;
	bool	hcAttackBerserker;
	bool	hcAttackBerserkerPrem;
	int		hcExplimitPlus;
	bool	hcPlatinumDrop;				// ��ӷ� 20�� ���
	bool	hcPlatinumScroll;			// 10�� ���� ��ӷ� 4����

	int		hcLimitSP;					// ���õ� ���� ����
	int		hcLimitEXP;					// ����ġ ���� ����
	int		hcRandomExpUp;				// ���� ����ġ 4�� Ȯ��
	int		hcRandomSpUp;				// ���� ���õ� 4�� Ȯ��
	int		hcRandomDropUp;				// ���� ����ġ 4�� Ȯ��
	// --- TODO : �ϵ��ڵ���
	bool	hcPetExpBoost;				// �� ����ġ ����
	bool	hcIrisFervor;				// ���̸����� ����
	bool 	hcFactionUP;

#ifdef REFORM_PK_PENALTY_201108 // PK �г�Ƽ ����
	int		pkDispositionPointValue;	// pk ���� ��ġ
#endif
	int		tower_attack;

	int		war_reduce_melee_prob;			//�������� ���� ������ ���� Ȯ��
	int		war_reduce_range_prob;			//�������� ���Ÿ� ������ ���� Ȯ��
	int		war_reduce_magic_prob;			//�������� ���� ������ ���� Ȯ��

	int		war_reduce_melee;			//�������� ���� ������ ����
	int		war_reduce_range;			//�������� ���Ÿ� ������ ����
	int		war_reduce_magic;			//�������� ���� ������ ����
	int		war_max_hp;					//�������� �ִ� hp ����
	int		war_defence;				//�������� ���� ����
	int		war_resist;					//�������� ���� ���� ����
	int		war_tower_attack;			//�������� ���� Ÿ�� ���ݷ� �Ͻ�����

	int		money_buy;
	int		money_sell;
	int		money_nas;

	int		affinity_quest;
	int		affinity_monster;
	int		affinity_item;
	
	int		quest_exp;

	int		guild_party_exp;
	int		guild_party_sp;
	#ifdef HP_REDUCE_10222021
	int	    hp_recover_reduce;
	#endif
} ASSISTVALUE;

/////////////////////
// Class name	    : CAssistData
// Description	    : ����ȿ��������
class CAssistData
{
public:
	int						m_index;		// �������� ��� ������ �ε���, �׿ܴ� -1
	const CSkillProto*		m_proto;		// ��ų
	int						m_level;		// ����
	int						m_remain;		// �����ð�
	int						m_remainCount;	// remain proc count
	bool					m_bHit[MAX_SKILL_MAGIC];	// ��ų�� ȿ�� ���� ����

	


	MSG_CHAR_TYPE			m_spellerType;	// ��ų ���� ĳ���� Ÿ��
	int						m_spellerIndex;	// ��ų ���� ĳ���� �ε���

	CAssistData*			m_prev;			// ��ũ
	CAssistData*			m_next;			// ��ũ
#ifdef ASSIST_DECREASE_TIME_BUG_FIX
	int						m_prevtime;
#endif
	//�Ӽ� ��ų�� ���� ���� ������
	int						attr_rand;

	CAssistData(MSG_CHAR_TYPE spellertype, int spellerindex, int itemidx, const CSkillProto* proto, int level, int remain,
				int remainCount,
				bool bHit[MAX_SKILL_MAGIC]);
};

/////////////////////
// Class name	    : CAssistList
// Description	    : ����ȿ������Ʈ
class CAssistList
{
	friend class CAssist;

public:
	CAssistList();
	~CAssistList();

public:
	CAssistData* getHead()
	{
		return m_head;
	}

private:
	CAssistData*			m_head;			// ���
	CAssistData*			m_tail;			// ����
	int						m_max;			// �ִ� ��
	int						m_count;		// ����
	int						m_abscount;		// ����ð� ���� ����

	/////////////////////
	// Function name	: max
	// Description	    : �ִ� �� ����
	void Max(int n);

	/////////////////////
	// Function name	: Add
	// Description	    : ����Ʈ�� �߰�
	// Argument         : CCharacter* spellchar
	//                  : ������ ĳ����
	// Argument         : int itemidx
	//                  : �������� ��� �ε���, �׿ܴ� -1
	// Argument         : const CSkillProto* proto
	//                  : �߰��� ��ų
	// Argument         : int level
	//                  : �߰��� ��ų�� ����
	// Argument         : bool bHit[MAX_SKILL_MAGIC]
	//                  : ȿ�� ���� ����
	// Argument         : int& remain
	//                  : ���� �ð�, -1�� ��ų ��ü �ð� ���
	// Argument         : int &remainCount
	//                  : remain proc trigger count. -1 use skill own count
	bool Add(CCharacter* spellchar, int itemidx, const CSkillProto* proto, int level, bool bHit[MAX_SKILL_MAGIC], int& remain,
			 int &remainCount,
			 int param, int nBlessAdd, int nBlessRate, int decreaseDBufTime);

	/////////////////////
	// Function name	: CanApply
	// Description	    : ��ų ���� ���ɼ� �˻�
	// Argument         : const CSkillProto* proto
	//                  : ��ų
	// Argument         : int level
	//                  : ����
	bool CanApply(const CSkillProto* proto, int level);

	/////////////////////
	// Function name	: DelDuplicate
	// Description	    : �ߺ��Ǵ� ȿ�� ����
	// Argument         : const CSkillProto* proto
	//                  : �ߺ� �˻� ��� ��ų
	// Argument         : int level
	//                  : ����
	// Argument         : bool bSend
	//                  : ���� ������ �޽����� ���������� ����
	// Argument         : bool bNoCancelType
	// 060317 : bs      : SF_NOCANCEL �˻� ����
	void DelDuplicate(const CSkillProto* proto, int level, bool bSend, CCharacter* ch, bool bNoCancelType);

	/////////////////////
	// Function name	: DecreaseTime
	// Description	    : �ð� ����
	// Return type		: bool
	//            		: �����Ǵ� ��ų�� �ִ��� ����
	bool DecreaseTime(CCharacter* ch, LONGLONG* changestate);

	////////////////////
	// Function name	: Apply
	// Description	    : ȿ�� ����
	// Argument         : ASSISTVALUE* addition
	//                  : �������� ����Ǵ� ��ġ
	// Argument         : ASSISTVALUE* rate
	//                  : ������ ����Ǵ� ��ġ
	// Argument         : int* state
	//                  : ���� ��ȭ

	void Apply(CCharacter* ch, ASSISTVALUE* addition, ASSISTVALUE* rate, LONGLONG* state);

	/////////////////////
	// Function name	: DelAssist
	// Description	    : ����ȿ�� ����
	// Argument         : CAssistData* d
	//                  :
	// Argument         : bool bNoCancelType
	// 060317 : bs      : SF_NOCANCEL �˻� ����
public:
	void DelAssist(CAssistData* d, bool bSend, CCharacter* ch, bool bNoCancelType, bool statusUpdate = true);

	////////////////////
	// Function name	: CheckApplyConditions
	// Description	    : ���� ���� �ٽ� �˻�
	void CheckApplyConditions(CCharacter* ch);
};

/////////////////////
// Class name	    : CAssist
// Description	    : ����ȿ��
class CAssist : public MemoryPoolBaseWithMutex<CAssist>
{
public:
	CCharacter*				m_ch;			// ȿ�������ϴ� ĳ����
	CAssistList				m_help;			// �̷ο� ��
	CAssistList				m_curse;		// �طο� ��
	int						m_delaycheck;	// �˻� ������
	ASSISTVALUE				m_avAddition;	// �����Ǵ� ȿ�� ��ġ
	ASSISTVALUE				m_avRate;		// ������ ����Ǵ� ȿ�� ��ġ
// �� ���� �޽���
	LONGLONG				m_state;		// ���� ��ȭ(���� ���)

	CAssist();

	/////////////////////
	// Function name	: Init
	// Description	    : �ʱ�ȭ
	void Init(CCharacter* ch);

	int GetAssistCount()
	{
		return m_help.m_count + m_curse.m_count + m_help.m_abscount;
	}

	int GetAssistHelpMax()
	{
		return m_help.m_max;
	}
	int GetAssistHelpCount()
	{
		return m_help.m_count;
	}

	int	GetAssistCurseCount()
	{
		return m_curse.m_count + m_curse.m_abscount;
	}

	/////////////////////
	// Function name	: Add
	// Description	    : ��ų ȿ�� �߰�
	// Argument         : CCharacter* spellchar
	//                  : ������ ĳ����
	// Argument         : int itemidx
	//                  : �������� ��� �ε���, �׿ܴ� -1
	// Argument         : const CSkillProto* proto
	//                  : ��ų
	// Argument         : int level
	//                  : ����
	// Argument         : bool bHit[MAX_SKILL_MAGIC]
	//                  : ȿ�� ���� ����
	// Argument         : bool bSend
	//                  : ���� ������ �޽����� ���������� ����
	// Argument         : int remain
	//                  : ���� �ð�, -1�� ��ų ��ü �ð� ���
	// Argument         : int remainCount
	//                  : remain proc trigger count. -1 use skill own count
	bool Add(CCharacter* spellchar, int itemidx, const CSkillProto* proto, int level, bool bHit[MAX_SKILL_MAGIC], bool bSend, int remain,
			 int remainCount,
			 int param, int nBlessAdd, int nBlessRate);

	/////////////////////
	// Function name	: DecreaseTime
	// Description	    : �ð� ����
	bool DecreaseTime();

	/////////////////////
	// Function name	: Apply
	// Description	    : ȿ�� ����
	void Apply();

	////////////////////
	// Function name	: ClearAssist
	// Description	    : ȿ�� ����
	// Argument         : bool bNoCancelType
	// 060317 : bs      : SF_NOCANCEL �˻� ����
	void ClearAssist(bool bSend, bool bByStone, bool bHelp, bool bCurse, bool bNoCancelType);

	////////////////////
	// Function name	: Find
	// Description	    : Ư�� ȿ���� ����Ǿ� �ִ��� �˻�
	bool Find(int magicindex, int magiclevel);

	void GetListString(bool bHelp, char* item, char* index, char* level, char* remain,
					   char *remainCount,
					   char* hit0, char* hit1, char* hit2);

	void GetListString(bool bHelp, std::string& item, std::string& index, std::string& level, std::string& remain,
					   std::string& remainCount,
					   std::string& hit0, std::string& hit1, std::string& hit2);

	void AppendAssistToNetMsg(CNetMsg::SP& msg);
	void AppendAssistToNetStructMsg(struct tag_assistinfo& info);

	// 060227 : bs : ����ð� ��� ����Ʈ
	////////////////////
	// Function name	: GetABSTimeTypeList
	// Description	    : ���� �ð� Ÿ���� ���� ����Ʈ�� �����´�
	// Return type		: int
	//                  : �� ����
	// Argument         : int* nAssistABSItemIndex
	//                  : ������ �ε��� ����, NULL�̸� �����ʹ� ���� ������ ���Ѵ�
	// Argument         : int* nAssistABSSkillIndex = NULL
	//                  : ��ų �ε��� ����
	// Argument         : int* nAssistABSSkillLevel = NULL
	//                  : ��ų ���� ����
	// Argument         : char* nAssistABSHit0 = NULL
	//                  : ���� 0 ����
	// Argument         : char* nAssistABSHit1 = NULL
	//                  : ���� 1 ����
	// Argument         : char* nAssistABSHit2 = NULL
	//                  : ���� 2 ����
	// Argument         : int* nAssistABSEndTime = NULL
	//                  : ����ð� ����
	int GetABSTimeTypeList(int* nAssistABSItemIndex, int* nAssistABSSkillIndex = NULL, int* nAssistABSSkillLevel = NULL, char* nAssistABSHit0 = NULL, char* nAssistABSHit1 = NULL, char* nAssistABSHit2 = NULL, int* nAssistABSEndTime = NULL);

	////////////////////
	// Function name	: CancelSleep
	// Description	    : �������� ���
	void CancelSleep();

	////////////////////
	// Function name	: CureAssist
	// Description	    : level������ type�� �ش��ϴ� ��ų ���
	void CureAssist(int type, int level);
	void CureAssist(int flag);
	void CureOtherAssist(int type, int subtype, int level);			// ASSIST���� �ٸ� ������ ���� ����

	////////////////////
	// Function name	: CancelInvisible
	// Description	    : �κ���� Ǯ��
	void CancelInvisible();

	////////////////////
	// Function name	: CheckApplyConditions
	// Description	    : ���� ���� �ٽ� �˻�
	void CheckApplyConditions();

	/////////////////////
	// Function name	: CanApply
	// Description	    : ��ų ���� ���ɼ� �˻�
	// Argument         : const CSkillProto* proto
	//                  : ��ų
	// Argument         : int level
	//                  : ����
	bool CanApply(const CSkillProto* proto, int level);

	////////////////////
	// Function name	: FindByType
	// Description	    : Ư�� Ÿ���� ȿ���� ã��
	// Return type		: int
	//                  : ã�� ȿ���� ����, ��ã���� 0
	// Argument         : int type
	//                  : ȿ�� Ÿ��
	// Argument         : int subtype
	//                  : ȿ�� ���� Ÿ��
	// Argument         : bool* outHelp = NULL
	//                  : help ����Ʈ���� ã������ true, �ƴϸ� false
	// Argument         : CAssistData** outData = NULL
	//                  : ã�� ȿ���� �ش��ϴ� CAssistdata*�� ����
	int FindByType(int type, int subtype, bool* outHelp = NULL, CAssistData** outData = NULL);
	int GetSummonNpcIndex(); // �� ������ Ʈ���� �䷯����Ʈ ��ȯ npc index �� �����´�.

	////////////////////
	// Function name	: CancelFear
	// Description	    : MST_ASSIST_FEAR ����
	void CancelFear();

	////////////////////
	// Function name	: CancelFakeDeath
	// Description	    : MST_ASSIST_FAKEDEATH ����
	void CancelFakeDeath();

	// Ư�� ������ �ε����� ���� ������ ���
	void CureByItemIndex(int itemindex);

	// Ư�� ������ �ε����� ���� ������ �ִ��� ã��
	bool FindByItemIndex(int itemindex, CAssistData** outData = NULL);

	// Ư�� ��ų�ε����� ���� ã��, ��ų�� ������ 0, ������ ��ų���� ��ȯ
	int FindBySkillIndex(int skillindex);

	// Ư�� ��ų �ε����� ���� ������ ���
	void CureBySkillIndex(int nSkillIndex);

	void CureAllRecovery(CPC * ch);

	// pet, apet �� ���� ������ ���
	void CureByPetSkill();

	void CancelDespair();
	void CancelManaScreen();
	void CancelBless();
	void CancelMantle();
	void DecreaseCount(int type, int subtype);

	unsigned char getAttrAtt();
	unsigned char getAttrDef();

private:

	/////////////////////
	// Function name	: DelDuplicate
	// Description	    : �ߺ��Ǵ� ȿ�� ����
	// Argument         : const CSkillProto* proto
	//                  : �ߺ� �˻� ��� ��ų
	// Argument         : int level
	//                  : ����
	// Argument         : bool bSend
	//                  : ���� ������ �޽����� ���������� ����
	// Argument         : bool bNoCancelType
	// 060317 : bs      : SF_NOCANCEL �˻� ����
	void DelDuplicate(const CSkillProto* proto, int level, bool bSend, bool bNoCancelType);
};

#endif //__ASSIST_H__
//
