#ifndef __DRATAN_CASTLE_H__
#define __DRATAN_CASTLE_H__


#include "Server.h"
#include "Log.h"
#include "CmdMsg.h"
#include "WarCastle.h"

class CDungeon
{
private:
	int m_nEnterFeeRate;
	int m_nHuntRate;

	int m_nMobRate;
	int m_nEnvRate;

	CZone * m_pZone;
	int m_nChangeTime;

	bool m_owner_mode;		//true : ���� ���� ���, false : �Ϲ� ���� ���
	int m_changeNormal_time;
	GoldType_t m_changeNeedNas;

public:
	CDungeon();
	~CDungeon();

	void SetFeeRate(int nRate)
	{
		m_nEnterFeeRate = nRate;
	}
	void SetHuntRate(int nRate)
	{
		m_nHuntRate = nRate;
	}

	void SetMobRate(int nRate)
	{
		m_nMobRate = nRate;
	}
	void SetEnvRate(int nRate)
	{
		m_nEnvRate = nRate;
	}

	void setOwnerMode(bool ownerMode);

	void setChangeNormalTime(int time)
	{
		m_changeNormal_time = time;
	}
	
	void setChangeNeedNas(GoldType_t nas)
	{
		m_changeNeedNas = nas;
	}

	int GetFeeRate()
	{
		return m_nEnterFeeRate;
	}
	int	GetHuntRate()
	{
		return m_nHuntRate;
	}

	int GetMobRate()
	{
		return m_nMobRate;
	}
	int GetEnvRate()
	{
		return m_nEnvRate;
	}

	bool GetOwnerMode()
	{
		return m_owner_mode;
	}

	int GetChangeNormalTime()
	{
		return m_changeNormal_time;
	}

	GoldType_t getChangeNeedNas()
	{
		return m_changeNeedNas;
	}

	void ChangeFeeRate(int nRate);
	void ChangeHuntRate(int nRate);

	void ChangeEnvRate(int nRate);
	void ChangeMobRate(int nRate);

	void SetChangeTime(int nTime);
	int GetChangeTime();

	void SetZone(CZone * pZone);
	CZone * GetZone();

	void ChangeSetting();

	bool checkOwnerMode();
};

typedef struct _tagGuard
{
	int mobindex;
	float pos_z;
	float pos_x;
	float pos_h;
} GUARD;

class CGuardList
{
public:
	CGuardList();
	~CGuardList();
	CGuardList(int kind, int count);

private:
	int maxkind;
	int maxcount;
	int m_cnt;
	int m_maxcnt;

	GUARD * m_pGardList;

public:
	void init(int kind, int count);
	bool InsertGuard(int idx, float x, float z, float h);
	int GetCount(int idx);
	int GetCount();
	int GetMaxCount();
	int GetMaxKindCount()
	{
		return maxcount;
	}
	void clean();
};

class CDratanCastle : public CWarCastle
{
public:
	static CDratanCastle * CreateInstance();

	enum
	{
		TOWER_WARP = 6,
	};

private:
	CDratanCastle();
	CDratanCastle(const CDratanCastle & rhs);

	static CDratanCastle * pInstance;

	enum
	{
		COUNT_DRATAN_GATE_NPC = 5,
		WAR_TIME = 1 * 60 * 60,

		REGEN_REBIRTH_NPC_TIME = 20 * 60
	};

	int m_respondCnt;			// ũ����Ż�� �����ϰ� �ִ� ĳ����
	int m_RespondMember[5];		// ���� ĳ���� �ε���
	char m_nMasterTower[7];		//
	// ������ Ÿ��	�ٰŸ� ������, ���Ÿ� ������, ���� ������, ������ Ÿ�� �ӵ� �϶���, �ɷ�ġ �϶���, �� �ߵ���, ������ ���� ����

	char m_reinforce[3];	// ��ȭ��ġ
	bool m_bMaster;

public:
	CNPC *  m_gateNPC[COUNT_DRATAN_GATE_NPC];		// ���� ��Ű�� ��ȣ��
	CGuardList  m_GuardList;	// 3����, ������ 10���̻� ��ġ �Ұ�
	CNPC *		m_pWarpNPC[5];		// ���� NPC
	CNPC *		m_pRebrithNPC[7];	// ��Ȱ ���� NPC
	int			m_nRebrithGuild[7];		// ��Ȱ ���� ���� ��� �ε���
	char *		m_strRebrithGuild[7];	// ��Ȱ ���� ���� ��� �̸�
	bool		m_bLoop;				// ��� �������� ���� ����
	CNPC*		m_pDungeonNPC;			// ���ϴ��� NPC

	bool		m_isNotChange;				//��� ���ɾ ���� ����(true �� �ð����� �������� �ʴ´�.)

	CDungeon	m_dvd;					// ���� ����

// virtual function ����
protected:
	void SetGateNPC(CNPC* npc);
	void InitGateNPC();
	void InitRegenPosition();

public:
	int GetZoneIndex()
	{
		return ZONE_DRATAN;
	}
	void SetNextWarTime(int nextWarTime);
	bool SetNextWarTime(int wday, int hour);
	bool IsJoinTime();
	void GetJoinTime(struct tm* nextJoinTime, bool bHumanable);
	int GetRegenPoint(int joinflag, CPC* ch);
	void UpdateGateState(CNPC* npc);
	bool IsOpenGate();
	bool GiveLordItem(CPC* pc);
	bool TakeLordItem(CPC* pc);
	int GetLordItemIndex(char job1, char job2);
	bool IsDefenseWarpPoint(int pos);
	int GetGateNPCCount()
	{
		return (GetGateNPC(0) == NULL) ? 0 : COUNT_DRATAN_GATE_NPC;
	}
	CNPC* GetGateNPC(int idx)
	{
		return (idx < 0 || idx >= COUNT_DRATAN_GATE_NPC) ? NULL : m_gateNPC[idx];
	}
	void GetInnerCastleRect(char* nYlayer, int* nX0x2, int* nZ0x2, int* nX1x2, int* nZ1x2);
// --- virtual function ����

	void CheckWarCastle();
	bool CheckSubServer();
	int GetCurSubServerCastleZoneIndex();
	int CheckJoin(CPC* ch);
	void CheckWarCastleNotice();
	void CheckWarCastleStartWar();
	void CheckWarCastleStartWarCastle();
	void GetNextWarTime(struct tm* nextWarTime, bool bHumanable);
	int GetNextWarTime()
	{
		return m_nextWarTime;
	}
	void CheckWarCastleEnd();

	void CheckWarCastleNPC();
	void RegenCastleNPC();
	void RemoveCastleNPC();
	void RemoveDungeonNPC();

	void SetRegenPoint(int nRegenPos, int nGuildIndex);
	void RegenLordSymbol();

	void RegenCastleTower();
	void RegenShop();
	void RemoveCastleTower();
	void RemoveLordSymbol();
	void RegenGuardNPC();
	void RemoveGuardNPC();
	bool LoadCastleData();

	int GetRespondCount()
	{
		return m_respondCnt;
	}
	void SetRespondCount(int cnt)
	{
		m_respondCnt = cnt;
	}

	void InitMasterTower();

	char GetTowerStatus(int i);
	bool SetTowerStatus(int i, char values);

	void SetOwner(CGuild* guild);
	void ResetOwner();

	void CheckRespond(CPC * ch);
	bool SetRespondMember(CPC * ch);
	void ResetRespondMeber(CPC * pc);
	void InitRespond();
	char GetReinforceStep(int i);
	void SetReinforceStep(char i, char v);
	bool CheckBuyTower(int index);
	void InitReinforce();
	void SetTowerReinforce(CNPC * npc);
	void CheckCastleControlNPC();
	void RegenCastleControlNPC();

	void InitWarpNPC();
	void SetWarpNPC(CNPC * npc);
	void SetRebrithNPC(CNPC* npc);
	void InitRebrithNPC();
	void ResetRebrithNPC();

	void ChangeSide(int gindex);
	void RegenCastleTowerHalf();
	int GetRemainWarTime();

	void GetOutNonDefense();
	bool IsInInnerCastle(CCharacter* pChar);
	bool CanLordChat(CPC* pc);

	void ChangeAttackGuild(int gindex);

	bool AddAttackGuild(int index);
	bool AddDefenseGuild(int index);
	bool IsAttackGuild(int index);
	bool IsDefenseGuild(int index);

	void RemoveCastleControlNPC();
	void MoveToRegenPoint();

	void RemoveRebirthNPC();
	void RegenRebirthNPC();

	void StopCastleTower();

	// ���� ������ ĳ�� �̵� ��Ű��
	void MoveingDVD();

	// ���� ���̵� �϶�
	void CheckDVD();

	void ChangeGuildNameColor();

	int	GetWarTime()
	{
		return WAR_TIME;
	}

	int		m_nRegenTimeRebirthNPC[7];
	void	CheckRegenRebirthNPC();
	int		GetRegenNPCRebirthTime()
	{
		return REGEN_REBIRTH_NPC_TIME;
	}
};
#endif // __DRATAN_CASTLE_H__
//
