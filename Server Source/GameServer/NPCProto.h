#ifndef __ANPCPROTO_H__
#define __ANPCPROTO_H__

#include <vector>
#include "../ShareLib/LCString.h"
#include "Skill.h"

class CNPCProtoList;

class CAffinityProto;

// t_npc_dropraid
typedef struct __tagRaidDropData
{
	int			itemindex;
	int			flag;
	int			count;
	int			prob;


#ifdef BUGFIX_SPECIALBOX_DROPRATE
	int			spec_itemindex[14];
#else
	int			spec_itemindex1;     // ����� ������
	int			spec_itemindex2;
	int			spec_itemindex3;
	int			spec_itemindex4;
	int			spec_itemindex5;
	int			spec_itemindex6;
	int			spec_itemindex7;
	int			spec_itemindex8;
	int			spec_itemindex9;
	int			spec_itemindex10;
	int			spec_itemindex11;
	int			spec_itemindex12;
	int			spec_itemindex13;
	int			spec_itemindex14;
#endif //BUGFIX_SPECIALBOX_DROPRATE
	int			spec_Min;
	int			spec_Max;
	int			spec_count;
	int			spec_flag;
	int			spec_prob;

} RAIDDROPDATA;
inline int Comp_RAIDDROPDATA(RAIDDROPDATA d1, RAIDDROPDATA d2)
{
	return d1.itemindex - d2.itemindex;
}

typedef std::vector<RAIDDROPDATA> vec_raiddropdata_t;
typedef std::vector<CAffinityProto*> vec_affinityList_t;

class CNPCProto
{
	friend class CNPCProtoList;

public:
	CNPCProto();
	~CNPCProto();

	/////////////////////////////////////
	// DB ���� �о���� NPC�� ���� ������
	int		m_index;			// �� ��ȣ
	CLCString m_name;			// �̸�

	int		m_level;			// ��
	int		m_price;			// ��
	float	m_sight;			// �þ�
	float	m_walkSpeed;		// �ȱ��̵��ӵ�
	float	m_runSpeed;			// �ٱ��̵��ӵ�
	float	m_size;				// ũ��(������)
	LONGLONG		m_hp;		// PWESTY MORE HP!!!
	int		m_mp;				// ����

	LONGLONG getExp()				{ return m_exp; }
	void	setExp(LONGLONG exp)			{ m_exp = exp; }
	int		getSkillPoint()			{ return m_skillPoint; }
	void	setSkillPoint(int sp)	{ m_skillPoint = sp; }

#ifdef PREMIUM_CHAR
	int		getExpForPremiumChar(int premium_type);
	int		getSkillPointForPremiumChar(int premium_type);
#endif

	bool 	IsBossInList();

private:
	LONGLONG		m_exp;				// ����ġ
	int		m_skillPoint;		// ��ų����Ʈ

	int		m_flag;				// �Ӽ�
	int		m_flag1;			// �Ӽ�(Ȯ��)
	int		m_stateFlag;		// �����̻� �÷���

public:
	int		m_family;			// ������ȣ ������ -1
	int		m_recoverHP;		// ȸ��HP
	int		m_recoverMP;		// ȸ��MP
	int		m_item[MAX_NPC_DROPITEM];			// ��Ӿ�����
	int		m_itemPercent[MAX_NPC_DROPITEM];	// ������ ��� Ȯ��
	int		m_itemCount;		// ��� ���̺��� ��
	int		m_product[MAX_NPC_PRODUCT];		// ����ǰ

// 050303 : bs : ���Ϳ��Լ� plus ���� ������ �����
	int		m_minplus;			// �ּ� �÷��� ��ġ
	int		m_maxplus;			// �ִ� �÷��� ��ġ
	int		m_probplus;			// �÷��� ���� Ȯ��
// --- 050303 : bs : ���Ϳ��Լ� plus ���� ������ �����

	int		m_str;				// ��
	int		m_dex;
	int		m_int;
	int		m_con;

	int		m_attack;			// ����
	int		m_magic;			// ����
	int		m_defense;			// ���
	int		m_resist;			// ����

	int		m_attacklevel;		// ���ݷ���
	int		m_defenselevel;		// ����

	// �������� ��
	char	m_attackType;
	char	m_attackSpeed;		// ���ݴ� �ð�(0.1��)
	float	m_attackArea;		// �ɸ����� �����Ÿ�

	// ��ų ��
	int		m_nSkill;
	int		m_skillIndex[MAX_NPC_SKILL];
	int		m_skillLevel[MAX_NPC_SKILL];
	int		m_skillProb[MAX_NPC_SKILL];

	int		m_moveArea;			// �̵�����

	// ai ����
	int		m_aitype;
	int		m_aiflag;
	int		m_aileader_flag;
	int		m_ai_summonHp;
	int		m_aileader_idx;
	int		m_aileader_count;

	int		m_nHit;
	int		m_nDodge;
	int		m_nMagicAvoid;

	unsigned char m_attrdef;
	unsigned char m_attratt;

	vec_raiddropdata_t		m_listRaidDrop;

#ifdef EXTREME_CUBE
	int		m_jobAttr;
#endif // EXTREME_CUBE

	vec_affinityList_t	m_affinityList;

	int		m_jewel[MAX_NPC_DROPITEM];			// ��Ӿ�����
	int		m_jewelPercent[MAX_NPC_DROPITEM];	// ������ ��� Ȯ��
	int		m_jewelCount;
	int		m_jobdropitem[JOBCOUNT];
	int		m_jobdropitemprob[JOBCOUNT];

	int		m_dropallitem[MAX_NPC_DROPITEM];
	int		m_dropallitemprob[MAX_NPC_DROPITEM];

	int		m_summonIdx;

	LONGLONG		m_zone_flag;			//�����̵��� ������ npc�ϰ���� �̵����� �� �� �ִ� ������
	LONGLONG		m_extra_flag;			//�����̵��� ������ npc�� �̵������� ���� ���� ����

	int		m_rvr_value;
	int		m_rvr_grade;

	float	m_bound;
	
	int		m_lifetime;

	bool			m_bSydicateJoinGiveQuestNPC;	// ���� ���� ����Ʈ �ο� NPC
	// m_flag �˻�
	int		CheckFlag(int mask) const
	{
		return m_flag  & mask;
	}
	int		CheckFlag1(int mask) const
	{
		return m_flag1 & mask;
	}
	int		CheckStateFlag(int mask) const
	{
		return m_stateFlag & mask;
	}

	int		GetFlag() const
	{
		return m_flag;
	}
	int		GetFlag1() const
	{
		return m_flag1;
	}
	int		GetStateFlag() const
	{
		return m_stateFlag;
	}

	// m_aiflag �˻� : bit��ȣ
	int		CheckAIBit(int bit)
	{
		return m_aiflag & (1 << bit);
	}

	// m_aileader_flag �˻� : bit��ȣ
	int		CheckLeaderBit(int bit)
	{
		return m_aileader_flag & (1 << bit);
	}
};

class CNPC;
class CNPCRegenInfo;

class CNPCProtoList
{
public:
	typedef std::map<int, CNPCProto*> map_t;

	CNPCProtoList();
	~CNPCProtoList();

	map_t		map_;
	CNPCProto*	m_npcProtoList;		// NPC �⺻ ���� ����Ʈ
	int			m_nCount;			// ����
	int			m_virtualIndex;		// ���� �ε���

	bool Load();						// NPC �⺻ ���� �б�

	CNPC* Create(int npcindex, CNPCRegenInfo* regenInfo);			// �ش� idx�� NPC �����ϱ�
	CNPCProto* FindProto(int npc_idx);	// �ش� idx�� ���� ��ȯ

private:
	std::vector<std::string> a_item_str;
	std::vector<std::string> a_item_percent_str;

	std::vector<std::string> a_jewel_str;
	std::vector<std::string> a_jewel_percent_str;

	std::vector<std::string> a_product_str;

	std::vector<std::string> a_skill_str;
};

#endif
//
