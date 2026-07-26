#include "stdhdrs.h"
#include "Server.h"
#include "../ShareLib/DBCmd.h"

#include "PassiveSystem.h"
CPassiveSystem::CPassiveSystem()
{
	m_index = -1;
	m_optionId = -1;
	m_optionLevel = 0;
	m_slot = -1;
}

CPassiveSystem::~CPassiveSystem()
{
}

CPassiveSystem* CPassiveSystem::Copy(int slot) const
{
	CPassiveSystem* newItem = new CPassiveSystem();
	newItem->m_index = m_index;
	newItem->m_optionId = m_optionId;
	newItem->m_optionLevel = m_optionLevel;
	newItem->m_slot = slot;
	newItem->optionProto = optionProto;

	return newItem;
}

CPassiveSystemProtoList::CPassiveSystemProtoList()
{
	m_passiveSystemList = NULL;
	m_nCount = 0;
}

CPassiveSystemProtoList::~CPassiveSystemProtoList()
{
	if (m_passiveSystemList)
		delete[] m_passiveSystemList;
	m_passiveSystemList = NULL;
	m_nCount = 0;
}

bool CPassiveSystemProtoList::Load()
{
	if (m_passiveSystemList)
		delete[] m_passiveSystemList;
	m_passiveSystemList = NULL;
	m_nCount = 0;

	CDBCmd dbNpc;
	dbNpc.Init(&gserver->m_dbdata);
	std::string sql = "SELECT * FROM t_passive_system";
	dbNpc.SetQuery(sql);
	dbNpc.Open();
	m_nCount = dbNpc.GetRecordCount();
	m_passiveSystemList = new CPassiveSystem[m_nCount];

	int i = 0;

	while (dbNpc.MoveNext())
	{
		dbNpc.GetRec("a_index", m_passiveSystemList[i].m_index);
		dbNpc.GetRec("a_option_id", m_passiveSystemList[i].m_optionId);
		dbNpc.GetRec("a_option_level", m_passiveSystemList[i].m_optionLevel);

		m_passiveSystemList[i].optionProto = gserver->m_optionProtoList.FindProto(m_passiveSystemList[i].m_optionId);

		map_.insert(map_t::value_type(m_passiveSystemList[i].m_index, &m_passiveSystemList[i]));
		i++;
	}

	m_nCount = i;

	return true;
}

CPassiveSystem* CPassiveSystemProtoList::FindPassiveSkill(int passiveSkillId)
{
	map_t::iterator it = map_.find(passiveSkillId);
	return (it != map_.end()) ? it->second : NULL;
}

CPassiveSystemList::CPassiveSystemList()
{
}

CPassiveSystemList::~CPassiveSystemList()
{
	m_listItem.clear();
}

bool CPassiveSystemList::Add(int nIndex, CPassiveSystem* pPassive)
{
	if (!pPassive)
		return false;
	m_listItem[nIndex] = boost::shared_ptr<CPassiveSystem>(pPassive);
	return true;
}

bool CPassiveSystemList::Remove(int nIndex)
{
	if (nIndex < 0)
		return false;

	map_t::iterator it = m_listItem.begin();
	map_t::iterator endit = m_listItem.end();
	for (; it != endit; ++it)
	{
		const PassiveSystem p = it->second;

		if (p->m_index == nIndex)
		{
			m_listItem.erase(it);
			return true;
		}
	}

	return false;
}

bool CPassiveSystemList::IsExists(int nIndex)
{
	map_t::iterator it = m_listItem.find(nIndex);
	return (it != m_listItem.end()) ? true : false;
}

CPassiveSystem* CPassiveSystemList::Find(int nIndex)
{
	if (nIndex < 0)
		return NULL;

	map_t::iterator it = m_listItem.begin();
	map_t::iterator endit = m_listItem.end();
	for (; it != endit; ++it)
	{
		const PassiveSystem p = it->second;

		if (p->m_index == nIndex)
		{
			return p.get();
		}
	}

	return NULL;
}

void CPassiveSystemList::ApplyOptions(CPC* ch)
{
	map_t::iterator it = m_listItem.begin();
	map_t::iterator endit = m_listItem.end();
	for (; it != endit; ++it)
	{
		const PassiveSystem p = it->second;

		if (p->optionProto == NULL || p->m_slot == -1) continue;

		COption::ApplyOptionValue(
			ch,
			p->optionProto->m_type,
			p->optionProto->m_levelValue[p->m_optionLevel],
			NULL);
	}
}

void CPassiveSystemList::clear()
{
	m_listItem.clear();
}