#pragma once

#include <boost/unordered_map.hpp>
#include <boost/thread/mutex.hpp>

class MailBoxLocker
{
public:
	MailBoxLocker() { }

	void Lock(int charId) { ChangeLockStatus(charId, true); }
	void Unlock(int charId) { ChangeLockStatus(charId, false); }
	bool IsLock(int charId)
	{
		boost::mutex::scoped_lock lock(m_mutex);
		boost::unordered_map<int, bool>::iterator iter = m_map.find(charId);
		if (iter == m_map.end())
			return false;
		else
			return (*iter).second;			
	}

private:
	void ChangeLockStatus(int charId, bool isLock)
	{
		boost::mutex::scoped_lock lock(m_mutex);
		if (m_map.find(charId) == m_map.end())
		{
			m_map.insert(std::make_pair(charId, isLock));
		}
		else
		{
			m_map[charId] = isLock;
		}
	}

private:
	boost::unordered_map<int, bool> m_map;
	boost::mutex m_mutex;
};