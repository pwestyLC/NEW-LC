#ifndef __EVENT_AUTOMATION_H__
#define __EVENT_AUTOMATION_H__

#include "NPCRegenInfo.h"
#include "mysql.h"

class CEventInfo
{
public:

	CEventInfo() : m_index(-1), m_prob(0), m_enable(false), m_notice(false)
	{
		m_rewardList.clear();
		m_npcList.clear();
		m_dropList.clear();
		m_npcRegenList.clear();
		m_dateStart = 0;
		m_dateEnd = 0;
	}
	~CEventInfo()
	{
		m_rewardList.clear();
		m_npcList.clear();
		m_dropList.clear();
		m_npcRegenList.clear();
	}

	void setEventIndex(int _index)
	{
		m_index = _index;
	}
	void setProb(int _prob)
	{
		m_prob = _prob;
	}
	void setEnable(bool _enable)
	{
		m_enable = _enable;
	}
	void setNotice(bool _notice)
	{
		m_notice = _notice;
	}
	void addRewardIndex(int _rewardIndex)
	{
		m_rewardList.push_back(_rewardIndex);
	}

	void setDateStart(int _dateStart)
	{
		m_dateStart = _dateStart;
	}

	void setDateEnd(int _dateEnd)
	{
		m_dateEnd = _dateEnd;
	}

	void setName(const char* _name)
	{
		m_name = _name;
	}

	int getEventIndex() const
	{
		return m_index;
	}
	bool getEnable() const
	{
		return m_enable;
	}
	int getProb() const
	{
		return m_prob;
	}
	bool getNotice() const
	{
		return m_notice;
	}
	int  getRewardIndexCount() const
	{
		return static_cast<int>(m_rewardList.size());
	}
	int  getRewardIndex(int _pos) const
	{
		if (_pos < 0 || m_rewardList.empty() || (int)m_rewardList.size() <= _pos)
			return -1;

		return m_rewardList[_pos];
	}

	void addNpc(int _npcDBIndex)
	{
		m_npcList.push_back(_npcDBIndex);
	}
	int getNpcCount() const
	{
		return (int)m_npcList.size();
	}
	bool isEventNpc(int _npcDBIndex) const
	{
		int i, listSize;
		if (m_npcList.empty())
			return false;
		else
			listSize = (int)m_npcList.size();

		for (i = 0; i < listSize; i++)
		{
			if (getNpcDBIndex(i) == _npcDBIndex)
				return true;
		}
		return false;
	}

	int getNpcDBIndex(int _pos) const
	{
		if (_pos < 0 || m_npcList.empty() || (int)m_npcList.size() <= _pos)
			return -1;

		return m_npcList[_pos];
	}

	void addDrop(int _npcDBIndex)
	{
		m_dropList.push_back(_npcDBIndex);
	}
	int getDropCount() const
	{
		return (int)m_dropList.size();
	}
	int getDropIndex(int _pos) const
	{
		if (_pos < 0 || m_dropList.size() == 0 || (int)m_dropList.size() <= _pos)
			return -1;

		return m_dropList[_pos];
	}

	int getDateStart() const
	{
		return m_dateStart;
	}

	int getDateEnd() const
	{
		return m_dateEnd;
	}

	CLCString getName() const
	{
		return m_name;
	}

	void addNpcRegenInfo(CNPCRegenInfo* _pNpcRegen)
	{
		m_npcRegenList.push_back(_pNpcRegen);
	}
	void setRegenDisable()
	{
		setRegen(false);
	}
	void setRegenEnable()
	{
		setRegen(true);
	}

private:

	void setRegen(bool _bRegen);

private:
	int m_index;
	CLCString m_name;
	int m_prob;
	bool m_enable;
	bool m_notice;
	int m_dateStart;
	int m_dateEnd;

	std::vector<int> m_rewardList;

	std::vector<int> m_npcList;

	std::vector<int> m_dropList;

	std::vector<CNPCRegenInfo*> m_npcRegenList;
};

class CEventAutomationManager
{
public:

	CEventAutomationManager()
	{}
	~CEventAutomationManager()
	{
		m_eventList.clear();
		m_activeList.clear();
	}

	bool reloadEvents();

	bool loadEvent();

	void checkEventTime();

	// �̺�Ʈ ã��
	CEventInfo* getEventInfo(int _eventIndex);
	// �������� �̺�Ʈ ã�ƿ���
	CEventInfo* getActiveEventInfo(int _eventIndex);

	// �������� �̺�Ʈ�� ����ϱ�
	bool addActiveEvent(int _eventIndex, bool _dbUpdate = false);

	// �������� ��Ͽ��� �̺�Ʈ ����
	bool removeActiveEvent(int _eventIndex, bool _dbUpdate = false);

	// �������� �̺�Ʈ ���� Ȯ��
	bool isActiveEvent(int _eventIndex);

	// �̺�Ʈ ���� npc Ȯ��
	bool isEventNpc(int _npcDBIndex, int& _eventIndex, bool& _bEnabel);

	// �������� �̺�Ʈ npc���� Ȯ��
	bool isActiveEventNpc(int _npcDBIndex, int& eventIndex);

	// npc���� ���� �ֱ�
	void addNpcRegenInfo(CNPCRegenInfo* _pNpcRegenInfo);

	std::map<int, CEventInfo*>* getActiveEvenList();
	std::map<int, CEventInfo>* getEvenList();

	int getActiveEventCount()
	{
		return (int)m_activeList.size();
	}

	void sendEventList(CPC* pc);
	void sendEventListToAll();
	void sendEventInfoActive(int _eventIndex);
	void sendEventInfoDisable(int _eventIndex);
private:
	bool dbUpdate(int _eventIndex, bool _enable);

	// �̺�Ʈ ��ü ����Ʈ // first : eventIndex
	std::map<int, CEventInfo> m_eventList;
	// �������� �̺�Ʈ ����Ʈ // first : eventIndex
	std::map<int, CEventInfo*> m_activeList;
};

#endif
