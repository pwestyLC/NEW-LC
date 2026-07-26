#include <boost/format.hpp>
#include "stdhdrs.h"

#include "../ShareLib/DBCmd.h"
#include "Server.h"
#include "Log.h"
#include "CmdMsg.h"
#include "EventAutomation.h"

void CEventInfo::setRegen(bool _bRegen)
{
	int i;
	int regenListSize = (int)m_npcRegenList.size();
	for (i = 0; i < regenListSize; i++)
	{
		if (!m_npcRegenList[i])
			continue;
		m_npcRegenList[i]->m_bRegen = _bRegen;
		m_npcRegenList[i]->m_lastDieTime = 10;
	}
}

bool CEventAutomationManager::reloadEvents()
{
	LOG_INFO("GM COMMAND RELOAD EVENTS");

	m_eventList.clear();
	m_activeList.clear();
	loadEvent();
	return true;
}

bool CEventAutomationManager::loadEvent()
{
	CDBCmd cmd;
	cmd.Init(&gserver->m_dbdata);
	cmd.SetQuery("SELECT *, UNIX_TIMESTAMP(a_date_start) as unix_a_date_start,"
		"UNIX_TIMESTAMP(a_date_finish) as unix_a_date_end "
		"FROM t_event "
		"ORDER BY a_index; ");

	if (!cmd.Open() || !cmd.MoveFirst())
	{
		GAMELOG << init("EVENT_AUTOMATION_WARN") << "NO EXIST TABLE t_event" << end;
		return false;
	}

	if (cmd.GetRecordCount() < 1)
	{
		GAMELOG << init("EVENT_AUTOMATION_WARN") << "EMPTY TABLE t_event" << end;
		return false;
	}

	const int TOTAL_DROP = 10;
	int index;
	int enable, notice, dateStart, dateEnd;
	int drop[TOTAL_DROP];
	int prob;
	CLCString name;
	CLCString npclist;
	do
	{
		if (!cmd.GetRec("a_index", index)
			|| !cmd.GetRec("a_enable", enable)
			|| !cmd.GetRec("a_desc", name)
			|| !cmd.GetRec("a_notice", notice)
			|| !cmd.GetRec("a_npclist", npclist)
			|| !cmd.GetRec("a_prob", prob)
			|| !cmd.GetRec("a_drop_1", drop[0])
			|| !cmd.GetRec("a_drop_2", drop[1])
			|| !cmd.GetRec("a_drop_3", drop[2])
			|| !cmd.GetRec("a_drop_4", drop[3])
			|| !cmd.GetRec("a_drop_5", drop[4])
			|| !cmd.GetRec("a_drop_6", drop[5])
			|| !cmd.GetRec("a_drop_7", drop[6])
			|| !cmd.GetRec("a_drop_8", drop[7])
			|| !cmd.GetRec("a_drop_9", drop[8])
			|| !cmd.GetRec("a_drop_10", drop[9])
			)
		{
			GAMELOG << init("EVENT_AUTOMATION_WARN") << "NOT MATCHING FIELD TABLE t_event" << end;
			return false;
		}

		if (!cmd.GetRec("unix_a_date_start", dateStart) || !cmd.GetRec("unix_a_date_end", dateEnd))
		{
			dateStart = 0;
			dateEnd = 0;
		}
		else
		{
			if (dateStart > dateEnd)
			{
				GAMELOG << init("EVENT_AUTOMATION_WARN") << "INVALID DATE INDEX" << delim << index << end;
				return false;
			}
		}

		CEventInfo EInfo;

		EInfo.setProb(prob);
		EInfo.setEventIndex(index);
		EInfo.setEnable((enable != 0 ? true : false));
		EInfo.setDateStart(dateStart);
		EInfo.setDateEnd(dateEnd);
		EInfo.setName(name);

		// alanssoares
		// force event only channel war castle
		//if (gserver->m_serverno == WAR_CASTLE_SUBNUMBER_DRATAN &&
		//	(index == A_EVENT_ARTIFACT_HUNTER)) {
		//	EInfo.setEnable(true);
		//}
		//else {
		//	EInfo.setEnable(false);
		//}

		EInfo.setNotice((notice != 0 ? true : false));

		const char* pNpcIndex = npclist;
		char buf[8] = { 0, };
		int npcIndex = 0;
		while (*pNpcIndex)
		{
			pNpcIndex = AnyOneArg(pNpcIndex, buf);
			npcIndex = atoi(buf);
			if (npcIndex > 0)
				EInfo.addNpc(npcIndex);
		}

		int i = 0;
		for (i = 0; i < TOTAL_DROP; i++)
		{
			if (drop[i] > 0)
				EInfo.addDrop(drop[i]);
		}

		m_eventList.insert(std::map<int, CEventInfo>::value_type(index, EInfo));
		if (enable)
		{
			std::map<int, CEventInfo>::iterator itr;
			itr = m_eventList.find(index);
			if (itr != m_eventList.end())
				m_activeList.insert(std::map<int, CEventInfo*>::value_type(index, &itr->second));
		}
	} while (cmd.MoveNext());

	sendEventListToAll();

	return true;
}

// check event time for enable or disable
void CEventAutomationManager::checkEventTime()
{
	if (m_eventList.empty())
		return;

	const std::map<int, CEventInfo>::iterator itrEnd = m_eventList.end();
	for (auto itr = m_eventList.begin(); itr != itrEnd; ++itr)
	{
		if (itr->second.getEnable())
		{
			if (itr->second.getDateStart() > 0 && itr->second.getDateEnd() > 0)
			{
				if (itr->second.getDateStart() > gserver->getNowSecond() || itr->second.getDateEnd() < gserver->getNowSecond())
				{
					removeActiveEvent(itr->first, true);
					sendEventInfoDisable(itr->first);
				}
			}
		}
		else
		{
			if (itr->second.getDateStart() > 0 && itr->second.getDateEnd() > 0)
			{
				if (itr->second.getDateStart() < gserver->getNowSecond() && itr->second.getDateEnd() > gserver->getNowSecond())
				{
					addActiveEvent(itr->first, true);
					sendEventInfoActive(itr->first);
				}
			}
		}
	}
}

CEventInfo* CEventAutomationManager::getActiveEventInfo(int _eventIndex)
{
	if (m_eventList.empty())
		return NULL;
	const std::map<int, CEventInfo*>::iterator itr = m_activeList.find(_eventIndex);
	if (itr == m_activeList.end())
		return NULL;

	return itr->second;
}

CEventInfo* CEventAutomationManager::getEventInfo(int _eventIndex)
{
	if (m_eventList.empty())
		return NULL;
	const std::map<int, CEventInfo>::iterator itr = m_eventList.find(_eventIndex);
	if (itr == m_eventList.end())
		return NULL;

	return &itr->second;
}

void CEventAutomationManager::sendEventList(CPC* pc)
{
	if (m_activeList.empty())
		return;

	int countActiveEvent = 0;
	countActiveEvent = (int)m_activeList.size();
	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_EVENT);
	RefMsg(rmsg) << (unsigned char)MSG_EVENT_NEW_LIST
		<< countActiveEvent;

	for (auto itr = m_activeList.begin(); itr != m_activeList.end(); ++itr)
	{
		RefMsg(rmsg) << itr->second->getEventIndex()
			<< itr->second->getName()
			<< itr->second->getDateStart()
			<< itr->second->getDateEnd();
	}

	SEND_Q(rmsg, pc->m_desc);
}

void CEventAutomationManager::sendEventListToAll()
{
	if (m_activeList.empty())
		return;

	int countActiveEvent = 0;
	countActiveEvent = (int)m_activeList.size();
	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_EVENT);
	RefMsg(rmsg) << (unsigned char)MSG_EVENT_NEW_LIST
		<< countActiveEvent;

	for (auto itr = m_activeList.begin(); itr != m_activeList.end(); ++itr)
	{
		RefMsg(rmsg) << itr->second->getEventIndex()
			<< itr->second->getName()
			<< itr->second->getDateStart()
			<< itr->second->getDateEnd();
	}

	PCManager::instance()->sendToAll(rmsg);
}

void CEventAutomationManager::sendEventInfoActive(int _eventIndex)
{
	if (m_eventList.empty())
		return;

	CEventInfo* pEventInfo = getActiveEventInfo(_eventIndex);
	if (!pEventInfo)
		return;

	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_EVENT);
	RefMsg(rmsg) << (unsigned char)MSG_EVENT_NEW_ACTIVATED
		<< pEventInfo->getEventIndex()
		<< pEventInfo->getName()
		<< pEventInfo->getDateStart()
		<< pEventInfo->getDateEnd();

	PCManager::instance()->sendToAll(rmsg);
}

void CEventAutomationManager::sendEventInfoDisable(int _eventIndex)
{
	if (m_eventList.empty())
		return;

	CEventInfo* pEventInfo = getEventInfo(_eventIndex);
	if (!pEventInfo)
		return;

	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_EVENT);
	RefMsg(rmsg) << (unsigned char)MSG_EVENT_NEW_DEACTIVATED
		<< pEventInfo->getEventIndex();

	PCManager::instance()->sendToAll(rmsg);
}

bool CEventAutomationManager::dbUpdate(int _eventIndex, bool _enable)
{
	CDBCmd cmd;
	cmd.Init(&gserver->m_dbdata);
	std::string update_event_query = boost::str(boost::format("UPDATE t_event SET a_enable=%d WHERE a_index=%d") % (int)_enable % _eventIndex);
	cmd.SetQuery(update_event_query);

	if (!cmd.Update())
	{
		GAMELOG << init("EVENT_AUTOMATION_WARN") << update_event_query.c_str() << end;
		return false;
	}
	return true;
}

bool CEventAutomationManager::addActiveEvent(int _eventIndex, bool _dbUpdate)
{
	if (m_eventList.empty())
	{
		GAMELOG << init("EVENT_AUTOMATION_WARN") << "EMPTY EVENT DATA" << end;
		return false;
	}

	const std::map<int, CEventInfo*>::iterator pItr = m_activeList.find(_eventIndex);
	if (pItr != m_activeList.end())
	{
		GAMELOG << init("EVENT_AUTOMATION_WARN") << _eventIndex << " IS ALREADY ENABLED" << end;
		return false;
	}

	const std::map<int, CEventInfo>::iterator itr = m_eventList.find(_eventIndex);
	if (itr == m_eventList.end())
	{
		GAMELOG << init("EVENT_AUTOMATION_WARN") << "CANNOT FIND EVENT NO. " << _eventIndex << end;
		return false;
	}

	if (_dbUpdate)
	{
		if (!dbUpdate(_eventIndex, true))
		{
			GAMELOG << init("EVENT_AUTOMATION_WARN") << "DB UPDATE FAILED" << end;
			return false;
		}
	}

	itr->second.setEnable(true);
	m_activeList.insert(std::map<int, CEventInfo*>::value_type(_eventIndex, &itr->second));

	return true;
}

bool CEventAutomationManager::removeActiveEvent(int _eventIndex, bool _dbUpdate)
{
	if (m_activeList.empty())
	{
		GAMELOG << init("EVENT_AUTOMATION_WARN") << "EMPTY EVENT DATA" << end;
		return false;
	}

	std::map<int, CEventInfo*>::iterator itr;
	itr = m_activeList.find(_eventIndex);
	if (itr == m_activeList.end())
	{
		GAMELOG << init("EVENT_AUTOMATION_WARN") << _eventIndex << " IS ALREADY DISABLED" << end;
		return false;
	}

	if (_dbUpdate)
	{
		if (!dbUpdate(_eventIndex, false))
		{
			GAMELOG << init("EVENT_AUTOMATION_WARN") << "DB UPDATE FAILED" << end;
			return false;
		}
	}

	itr->second->setEnable(false);
	m_activeList.erase(_eventIndex);
	return true;
}

bool CEventAutomationManager::isActiveEvent(int _eventIndex)
{
	if (m_eventList.size() == 0)
	{
		//		GAMELOG << init("EVENT_AUTOMATION_WARN") << "EMPTY EVENT DATA" << end;
		return false;
	}

	std::map<int, CEventInfo*>::iterator itr;
	itr = m_activeList.find(_eventIndex);
	if (itr == m_activeList.end())
	{
		//GAMELOG << init("EVENT_AUTOMATION_WARN") << "EVENT IS NOT ENABLED" << end;
		return false;
	}

	return true;
}

std::map<int, CEventInfo*>* CEventAutomationManager::getActiveEvenList()
{
	if (m_activeList.size() == 0)
		return NULL;

	return  &m_activeList;
}

std::map<int, CEventInfo>* CEventAutomationManager::getEvenList()
{
	if (m_eventList.size() == 0)
		return NULL;

	return  &m_eventList;
}

bool CEventAutomationManager::isEventNpc(int _npcDBIndex, int& _eventIndex, bool& _bEnable)
{
	bool bFind = false;
	_eventIndex = -1;
	if (m_eventList.size() == 0)
		return false;

	std::map<int, CEventInfo>::iterator itr;
	std::map<int, CEventInfo>::iterator itrEnd = m_eventList.end();
	for (itr = m_eventList.begin(); itr != itrEnd; itr++)
	{
		if (itr->second.getNpcCount() == 0)
			continue;

		if (itr->second.isEventNpc(_npcDBIndex))
		{
			_eventIndex = itr->first;
			_bEnable = itr->second.getEnable();
			if (_bEnable)
				return true;
			else
				bFind = true;
		}
	}
	return bFind;
}

bool CEventAutomationManager::isActiveEventNpc(int _npcDBIndex, int& _eventIndex)
{
	_eventIndex = -1;
	if (m_activeList.size() == 0)
		return false;

	std::map<int, CEventInfo*>::iterator itr;
	std::map<int, CEventInfo*>::iterator itrEnd = m_activeList.end();
	for (itr = m_activeList.begin(); itr != itrEnd; itr++)
	{
		if (itr->second->getNpcCount() == 0)
			return false;

		if (itr->second->isEventNpc(_npcDBIndex))
		{
			_eventIndex = itr->first;
			return true;
		}
	}
	return false;
}

void CEventAutomationManager::addNpcRegenInfo(CNPCRegenInfo* _pNpcRegenInfo)
{
	if (!_pNpcRegenInfo)
		return;  // safely ignore null pointers

	int eventIndex;
	if (isEventNpc(_pNpcRegenInfo->m_npcIdx, eventIndex, _pNpcRegenInfo->m_bRegen))
	{
		CEventInfo* pEvent = getEventInfo(eventIndex);
		if (pEvent)
			pEvent->addNpcRegenInfo(_pNpcRegenInfo);
	}
}


