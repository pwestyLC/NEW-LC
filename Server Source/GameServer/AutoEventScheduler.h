#ifndef __AUTO_EVENT_SCHEDULER_H__
#define __AUTO_EVENT_SCHEDULER_H__

#include <vector>
#include <string>

enum eAutoEventType
{
	AUTO_EVENT_RLGL = 0,

	AUTO_EVENT_MAX
};

struct AutoEventEntry
{
	int index;
	eAutoEventType eventType;
	int dayOfWeek;      // 0=Sun..6=Sat, -1=every day
	int hour;           // 0-23, -1=ignore (for interval mode)
	int minute;         // 0-59
	int intervalMin;    // repeat every X minutes (0=one-shot at hour:minute)
	int startupDelayMin; // delay in minutes before first fire after server startup (0=no delay)
	bool enabled;
	time_t lastFired;   // unix time of last trigger (in-memory only)
};

class CAutoEventScheduler
{
public:
	CAutoEventScheduler();
	~CAutoEventScheduler();

	bool Load();
	void Reload();
	void Tick();

private:
	void FireEvent(AutoEventEntry& entry);
	std::vector<AutoEventEntry> m_events;
	time_t m_lastCheckMinute;
	time_t m_serverStartTime;  // unix time when server started (set during first Load())
};

#endif
