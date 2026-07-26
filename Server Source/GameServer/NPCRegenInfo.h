#ifndef __NPCREGENINFO_H__
#define __NPCREGENINFO_H__

#include <vector>

class CNPCProto;
class CArea;

class CNPCRegenInfo
{
public:
	CNPCRegenInfo();
	~CNPCRegenInfo();

	// Data loaded from DB
	int		m_index;
	int		m_npcIdx;
	int		m_zoneNo;
	float	m_regenX;
	int		m_regenY;
	float	m_regenZ;
	float	m_regenR;
	int		m_regenSec;
	int		m_totalNum;

	// Runtime state
	bool	m_bAlive;
	int		m_lastDieTime;
	int		m_numRegen;

	// Extra parameters
	int		m_paramHP;
	bool	m_bRaidMoveRandom;
	bool	m_bRegen;
    // (scripted movement fields removed)

	CNPCProto* m_npcProto;

	void SetHPParam(int val) { m_paramHP = val; }
	void clean();
};

class CNPCRegenList
{
public:
	CNPCRegenList();
	~CNPCRegenList();

	int m_type;

	// Actual regen list
	std::vector<CNPCRegenInfo> m_infoList;

	// Legacy support
	int m_nCount;	// Total expected entries
	int m_wPos;		// Current write index

	void Init();

	void SetCount(int n); // Resizes vector and sets count

	void AddRegenInfo(
		int index, int npc_index, int regenSec,
		float regenX, int yLayer, float regenZ, float regenR,
		int totalNum, int zoneNo,
		bool bRegen = true, CNPCProto* pNpcProto = nullptr);

	CNPCRegenInfo* GetNpcRegenInfo(int idx);
	bool DelRegenInfo(CNPCRegenInfo* p);
	bool Find(int npcIdx, int zoneNo, bool pdZone = false, float x = 0.0f, int y = 0, float z = 0.0f);
	bool SetRegened(CArea* pArea, int npcIdx, int zoneNo, float x = 0.0f, int y = 0, float z = 0.0f);
};

#endif // __NPCREGENINFO_H__
