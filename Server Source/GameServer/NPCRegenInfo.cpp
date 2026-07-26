#include "stdhdrs.h"

#include "NPCRegenInfo.h"
#include "Zone.h"
#include "Area.h"
#include "Server.h"
#include "../ShareLib/DBCmd.h"

///////////////////////
// CNPCRegenInfo member

CNPCRegenInfo::CNPCRegenInfo()
	: m_index(-1)
	, m_npcIdx(-1)
	, m_zoneNo(-1)
	, m_regenX(0.0f)
	, m_regenY(0)
	, m_regenZ(0.0f)
	, m_regenR(0.0f)
	, m_regenSec(0)
	, m_totalNum(0)
	, m_bAlive(false)
	, m_lastDieTime(0)
	, m_numRegen(0)
	, m_paramHP(0)
	, m_bRaidMoveRandom(false)
	, m_bRegen(true)
    , m_npcProto(nullptr)
{
}

CNPCRegenInfo::~CNPCRegenInfo()
{
}

void CNPCRegenInfo::clean()
{
	m_index = -1;
	m_npcIdx = -1;
	m_zoneNo = -1;
	m_regenX = 0.0f;
	m_regenY = 0;
	m_regenZ = 0.0f;
	m_regenR = 0.0f;
	m_regenSec = 0;
	m_totalNum = 0;
	m_bAlive = false;
	m_lastDieTime = 0;
	m_numRegen = 0;
	m_paramHP = 0;
	m_bRaidMoveRandom = false;
	m_bRegen = true;
	m_npcProto = nullptr;

    // scripted movement fields removed
}

///////////////////////
// CNPCRegenList member

CNPCRegenList::CNPCRegenList()
	: m_type(-1)
	, m_nCount(0)
	, m_wPos(0)
{
}

CNPCRegenList::~CNPCRegenList()
{
}

void CNPCRegenList::Init()
{
	m_infoList.clear();
	m_type = -1;
	m_nCount = 0;
	m_wPos = 0;
}

void CNPCRegenList::SetCount(int n)
{
	m_infoList.resize(n);
	m_nCount = n;
	m_wPos = 0;
}

void CNPCRegenList::AddRegenInfo(int index, int npc_index, int regenSec,
	float regenX, int yLayer, float regenZ, float regenR,
	int totalNum, int zoneNo, bool bRegen, CNPCProto* pNpcProto)
{
	if (m_wPos >= static_cast<int>(m_infoList.size()))
		m_infoList.resize(m_wPos + 1);

	CNPCRegenInfo& info = m_infoList[m_wPos];
	info.m_index = index;
	info.m_npcIdx = npc_index;
	info.m_zoneNo = zoneNo;
	info.m_regenSec = regenSec;
	info.m_regenX = regenX;
	info.m_regenY = yLayer;
	info.m_regenZ = regenZ;
	info.m_regenR = regenR;
	info.m_totalNum = totalNum;
	info.m_bAlive = false;
	info.m_lastDieTime = 0;
	info.m_numRegen = 0;
	info.m_bRegen = bRegen;
	info.m_npcProto = pNpcProto ? pNpcProto : gserver->m_npcProtoList.FindProto(npc_index);

	if (!info.m_npcProto)
	{
		LOG_ERROR("Missing proto for NPC ID %d (zone %d)", npc_index, zoneNo);
		return;
	}

	m_wPos++;
}

CNPCRegenInfo* CNPCRegenList::GetNpcRegenInfo(int idx)
{
	if (idx < 0 || idx >= static_cast<int>(m_infoList.size()))
		return nullptr;

	return &m_infoList[idx];
}

bool CNPCRegenList::DelRegenInfo(CNPCRegenInfo* p)
{
	auto it = std::find_if(m_infoList.begin(), m_infoList.end(),
		[&](CNPCRegenInfo& info) { return &info == p; });

	if (it != m_infoList.end())
	{
		m_infoList.erase(it);
		m_nCount = static_cast<int>(m_infoList.size());
		m_wPos = m_nCount;
		return true;
	}
	return false;
}
bool CNPCRegenList::Find(int npcIdx, int zoneNo, bool pdZone, float x, int y, float z)
{
	for (size_t i = 0; i < m_infoList.size(); ++i)
	{
		CNPCRegenInfo& info = m_infoList[i];
		if (info.m_npcIdx == npcIdx && info.m_zoneNo == zoneNo)
		{
			if (!pdZone)
				return true;

			if (fabs(info.m_regenX - x) < 1.0f &&
				info.m_regenY == y &&
				fabs(info.m_regenZ - z) < 1.0f)
			{
				return true;
			}
		}
	}
	return false;
}

bool CNPCRegenList::SetRegened(CArea* pArea, int npcIdx, int zoneNo, float x, int y, float z)
{
	if (!pArea)
		return false;

	for (size_t i = 0; i < m_infoList.size(); ++i)
	{
		CNPCRegenInfo& info = m_infoList[i];
		if (info.m_npcIdx == npcIdx && info.m_zoneNo == zoneNo)
		{
			if (fabs(info.m_regenX - x) < 1.0f &&
				info.m_regenY == y &&
				fabs(info.m_regenZ - z) < 1.0f)
			{
				// Match found: mark this regen as already used
				for (int j = 0; j < pArea->m_nCountNPC; ++j)
				{
					if (info.m_index == pArea->m_regenList[j])
					{
						pArea->m_regenList[j] = -1; // mark as consumed
						return true;
					}
				}
			}
		}
	}
	return false;
}

