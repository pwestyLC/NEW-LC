#ifndef __AAREA_H__
#define __AAREA_H__

#include <vector>
#include <set>

#include "Env.h"
#include "Cell.h"
#include "MonsterCombo.h"

#include "TrigerSet.h"
#include "RaidData.h"

typedef std::vector<CNPCRegenInfo*> vec_raidnpcrregenlist_t;
typedef std::set<int> set_int_t;

#define MAX_AREA_COUNT 300

class CZone;

struct tag_npc_regen_info 
{
	int			index;
	int			npcIndex;
	float		x;
	float		z;
	float		r;
	int			yLayer;
	int			regenSec;
	int			totalNum;

	CNPCProto*	pNPCProto;
};

struct tag_boss_regen_info  //new shit boss spawn IE kamira GGD GRD ETC pwesty carlos
{
	int index;
	int npcIndex;
	float x;
	float z;
	float r;
	char yLayer;

	int regenPulse;   
	int totalNum;

	CNPCProto* pNPCProto;
};

class CArea
{
public:
	CArea();
	~CArea();
	CGroundEffect2 m_GroundEffect2;
	CPC* m_AkanPCList[8];
	int m_nCountDown;
	int m_nObjectIndex;
	int m_nPauseMobActivity;
	int m_nPauseIndex;
	CNPC* m_pBossAppearNPC;
	int m_nDelayOpenGate;
	int m_nRaidRoomNo;
	
	bool		m_bEnable;			// Ȱ��ȭ ����
	CZone*		m_zone;				// �Ҽ� ��
	int			m_index;			// ���� ��ȣ

	int			m_size[2];			// �迭 ũ��: 0: width, 1: height: �� ����
	int			m_ycnt;
	CEnv***		m_env;				// ȯ�� �迭
	CCell**		m_cell;				// �� �迭

	CNPCRegenList m_npcRegenList;	// NPC ���� ���� ����Ʈ
	vec_raidnpcrregenlist_t m_raidNPCRegenList;		// RAID MONSTER ���� ���� ����Ʈ

	set_int_t m_NpcPortal_NpcList;	// mob �� �ε���
	set_int_t m_NpcPortal_MobList;	// mob �� �ε���
	bool IsNpcPortalList_Npc(int index);
	bool IsNpcPortalList_Mob(int index);

	CNPC*		m_npcList;			// NPC ����Ʈ
	int			m_nCountNPC;		// NPC ��
	int			m_pulseNPCAI;		// NPC AI pulse
	int			m_pulseNPCRegen;	// NPC regen pulse
	// int			m_nMaxCountNPC;		// NPC �ִ� ��
	int			m_nJunkItems;		// ����� ������ ��

	int			m_nMakeNPC;		// �̱۴������� ���� �� ��
	bool		m_bBoss;		//  �߷Ϲ� �ѹ� ��ġ�е� ����ߴ°�? : 2��° ����� �߷Ϲ�, ù��°�� 2��
	int*		m_regenList;	// �̱۴������� �����Ǿ��� ����Ʈ(regen�� a_index)

	int			m_guildIndex;		// ������ ��� ��� �ε���

	int			m_nNPC_Killed_NPC;

	// �ʱ�ȭ
	void Init(CZone* z, int index, int w, int h, int ycnt);

	// x, z���� �� ��ȣ ����
	void PointToCellNum(float x, float z, int* cx, int* cz);

	// ĳ���� ���� �ֱ�
	void CharToCell(CCharacter* ch, char cy, int cx, int cz);
	void CharToCellForSummonNpc(CCharacter* owner, CCharacter* ch, char cy, int cx, int cz);

	// ������ ĳ�� ����
	void CharFromCell(CCharacter* ch, bool bDeleteAttackList);

	// ĳ�� �̵�
	bool MoveChar(CCharacter* ch, char y, float x, float z, float h, float r, MSG_MOVE_TYPE movekind, CCharacter* target = NULL);

	// ĳ�� �̵� �ÿ� �����Ǵ��� �˻�
private:
	bool IsNotBlocked(char sy, float sx, float sz, float tx, float tz, bool bCastleNPC, char& ty);		// s���� t�� �̵� ���� ���� �˻� : ���� ĳ���Ϳ� InNotBlocked()���� ���

public:
	bool IsNotBlocked(CCharacter* ch, CCharacter* tch, bool battack, char& outYlayer);
	bool IsNotBlocked(CCharacter* ch, char y, float x, float z, bool battack, char& outYlayer);

	// Ư�� ��ġ�� Attribute�� ����
	unsigned short GetAttr(char y, float x, float z);
	// ���� �� ���
	float GetHeight(char y, float x, float z);

	// ch ��ó���� tch_type ������ idx ĳ���� ��ȯ
	CCharacter* FindCharInCell(CCharacter* ch, int idx, MSG_CHAR_TYPE tchType, bool bIncludeDead = false);
	CNPC* FindProtoNPCInCell(float x, float z, int nData, bool bIsFlagMask, int findNumCell, bool bIncludeDead = false);
	CNPC* FindProtoNPCInCell(CCharacter* ch, int nData, bool bIsFlagMask, int findNumCell = 2, bool bIncludeDead = false);

	

	// area�� tch�� ã��
	CCharacter* FindChar(int idx, MSG_CHAR_TYPE tchType);

	// ���� �޽��� ���� : ������ CELL_EXT �ݰ���� ��� PC���� �����Ѵ�
	bool SendToCell(CNetMsg::SP& msg, CCharacter* ch, bool withme = false, int cellext = CELL_EXT);
	bool SendToCell(CNetMsg::SP& msg, char y, int cx, int cz, int cellext = CELL_EXT);
	// �ش� area�� ��� PC���� msg ����
	void SendToAllClient(CNetMsg::SP& msg);

	// ���� ������ ch���� ����
	// bool bExcludeOwnPetElemental : ch�� ������ ��� ��ȯ���� ����
	void SendCellInfo(CPC* ch, bool bExcludeOwnPetElemental);

	// Ư�� ���� ���� ������ PC ���� ��ȯ
	int GetPCCount(CCharacter* ch, int findArea = CELL_EXT);
	int GetPCCount(int cx, int cz, int findArea = CELL_EXT);
	int	GetPCCount();

	// ���� ���� ����
	void LoadNPC(std::vector<tag_npc_regen_info>& vec);
	void LoadBossNPC(const std::vector<tag_boss_regen_info>& vecBoss);  //new shit boss spawn IE kamira GGD GRD ETC pwesty carlos
	// NPC�� �߰��Ѵ�
	void AddNPC(CNPC* npc);

	// NPC�� ����
	void DelNPC(CNPC* npc);

	// Mob�� ���� �̻� ���� ����
	CNPC* MobTimeCheck(CNPC* npc);

	// ���� Ȱ��ȭ
	void SetEnable(int nRaidRoomNum=-1, int nDifficulty = -1);

	// ���� ��Ȱ��ȭ
	void SetDisable();

	// �� �ൿ
	void MobActivity();

	// �� ����
	void MobRegen();
	// ���̵� ���� ����, �ϳ��� �����Ǹ� true, �ƴϸ� false
	bool RaidMobRegen(float x, float z, float r, char y);

	// npc�� ����� ���ݴ���� ã��
	CCharacter* FindNearestTarget(CNPC* npc, float* dist);

	// ���ֵ̹� npc�� ����� npc�� ã��
	CCharacter*	FindNearestTarget_Taming_or_Confused(CNPC* npc, float* dist);

	// ���� �ൿ ��ƾ ���������� ����
	void	MobActivity_Taming(CNPC* npc);
	void	MobActivity_Confused(CNPC* npc);

	// m_npcList�� ���̴� ���� ���� ����ȭ
	void	Monster_synchronization( int nCount );
	void MobActivity_Mercenary(CNPC* npc);
	void MobActivity_Totem(CNPC *npc);
	void MobActivity_Suicide(CNPC *npc);
	void MobActivity_Item_Totem(CNPC* npc);

	// �������� ���� �ֱ�
	void ItemToCell(CItem* item, char cy, int cx, int cz);

	// �����ۿ��� ĳ�� ����
	void ItemFromCell(CItem* item);

	// ������ ���� ������
	CItem* DropItem(int item_db_idx, CCharacter* ch, int plus, int flag, LONGLONG count, bool bOption = false);
	CItem* DropItem(CItem* item, CCharacter* ch);

	// ������ ������ ����
	void GroundItemControl();

	// aitype�� �ش��ϴ� ���� ã��, aitype�� -1�̸� ����, hpParam�̸��� ü���� ���� ���(������%)
	CNPC* FindNearestFamily(CNPC* npc, int aitype = -1, int hpParam = 100);

	// �����ȿ� �ִ� ĳ���� ��� �̵� ��Ű��
	void MoveAllChar(int nIndex, int nExtra);

	CMonsterCombo* m_monsterCombo;
	void RunComboZone();
	int  CountPCInExtra(int extra, bool bDead);
	int	 CountMobInCombo();
	void CloseComboZone();

	bool			m_bUseTriggerEvent;		// Ʈ���Ÿ� ����մϱ�?
	CTrigger_List	m_CTriggerList;			// �ش� area�� ���Ǵ� Ʈ���� ����Ʈ
	int				m_pulseProcTrigger;		// �ʴ� �����ؾ� �ϴ� Ʈ���Ÿ� ���� �޽�

	void Change_NpcRegenRaid(int level, int exceptingNpcIndex = 0);	// ���̵� npc regen ���� ����Ͽ� Ȱ��ȭ, regen save�� ���� ��
	int	 GetAllClientCount_Area();									// Area�� �����ϴ� ��� pc�� ���ڸ� ����.
	void GotoAllClient_StartPoint();							// area�� ��� ������ ���� �������� ����(��Ʈ����)
	void ApplySkillToAllClient(CSkill* skill, bool &bApply);	// area�� ��� �������� ������� �����Ѵ�.

	CAreaRaidInfoList m_RaidInfoList[LEVEL_COUNT];
	int m_RaidDifficulty;

private:
	int m_mobAISeq;
	bool m_bFreeze;
	int m_freezePulse;
public:
	int GetMobAISeq(void)
	{
		return m_mobAISeq;
	}
	int GetMobAIVec(void)
	{
		return (1 << m_mobAISeq);
	}
	void SetFreeze(int m_pulse);
	void SetMelted(void);
	bool IsFreeze(int m_pulse);

	int findNpcVIndex(int dbIndex);

	int m_inCount;

public:
	static void checkLifeTime();

private:
	static std::set<CNPC*> m_lifetime_set;

};

#define GoZone(ch,zone,layer,x,z)		GoZoneBase(ch,zone,layer,x,z,__FILE__,__LINE__)
#define GoZoneForce(ch,zone,layer,x,z)		GoZoneForceBase(ch,zone,layer,x,z,__FILE__,__LINE__)

bool GoZoneBase(CPC* ch, int zone, char ylayer, float x, float z, const char* fname, const int line);
void GoTo(CCharacter* ch, char y, float x, float z, float h, float r, char bHack = 0);
bool _GMGoZone(CPC* ch, CPC* pc);
void GMGoZone(CPC* ch, CPC* pc);
void GoZoneForceBase(CPC* ch, int zone, char ylayer, float x, float z, const char* fname, const int line);

#endif
//
