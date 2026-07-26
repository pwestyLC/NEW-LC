#include "stdhdrs.h"
#include "AutoEventScheduler.h"
#include "Server.h"
#include "../ShareLib/DBCmd.h"
#include "Log.h"

CAutoEventScheduler::CAutoEventScheduler()
{
	m_lastCheckMinute = 0;
	m_serverStartTime = 0;
}

CAutoEventScheduler::~CAutoEventScheduler()
{
}

bool CAutoEventScheduler::Load()
{
	m_events.clear();

	CDBCmd dbcmd;
	dbcmd.Init(&gserver->m_dbdata);
	dbcmd.SetQuery("SELECT a_index, a_event_type, a_day_of_week, a_hour, a_minute, a_interval_min, a_startup_delay_min, a_enabled FROM t_auto_event WHERE a_enabled = 1");

	if (!dbcmd.Open())
	{
		GAMELOG << init("AUTO_EVENT") << "Could not open t_auto_event" << end;
		return false;
	}

	// Track server start time on first load (or reload)
	if (m_serverStartTime == 0)
	{
		m_serverStartTime = time(NULL);
		GAMELOG << init("AUTO_EVENT") << "Server start time recorded for startup delay calculations" << end;
	}

	int idx = 0, dow = 0, hr = 0, mn = 0, en = 0, interval = 0, startupDelay = 0;
	CLCString evtype(33);

	while (dbcmd.MoveNext())
	{
		dbcmd.GetRec("a_index", idx);
		dbcmd.GetRec("a_event_type", evtype);
		dbcmd.GetRec("a_day_of_week", dow);
		dbcmd.GetRec("a_hour", hr);
		dbcmd.GetRec("a_minute", mn);
		dbcmd.GetRec("a_interval_min", interval);
		dbcmd.GetRec("a_startup_delay_min", startupDelay);
		dbcmd.GetRec("a_enabled", en);

		AutoEventEntry entry;
		entry.index = idx;
		entry.dayOfWeek = dow;
		entry.hour = hr;
		entry.minute = mn;
		entry.intervalMin = interval;
		entry.startupDelayMin = startupDelay;
		entry.enabled = (en != 0);
		entry.lastFired = 0;

		if (strcmp(evtype.GetBuffer(), "RLGL") == 0)
			entry.eventType = AUTO_EVENT_RLGL;
		else
		{
			GAMELOG << init("AUTO_EVENT") << "Unknown event type: " << evtype.GetBuffer() << " at index " << idx << end;
			continue;
		}

		m_events.push_back(entry);
	}

	GAMELOG << init("AUTO_EVENT") << "Loaded " << (int)m_events.size() << " scheduled events" << end;
	return true;
}

void CAutoEventScheduler::Reload()
{
	Load();
}

void CAutoEventScheduler::Tick()
{
	if (m_events.empty())
		return;

	time_t now = time(NULL);

	// Only check once per minute to avoid spam
	time_t currentMinute = now / 60;
	if (currentMinute == m_lastCheckMinute)
		return;
	m_lastCheckMinute = currentMinute;

	struct tm tmNow;
	memcpy(&tmNow, localtime(&now), sizeof(tmNow));

	int nowDow = tmNow.tm_wday;   // 0=Sun..6=Sat
	int nowHour = tmNow.tm_hour;
	int nowMin = tmNow.tm_min;

	for (size_t i = 0; i < m_events.size(); ++i)
	{
		AutoEventEntry& entry = m_events[i];
		if (!entry.enabled)
			continue;

		// Check if startup delay has passed
		if (entry.startupDelayMin > 0 && entry.lastFired == 0)
		{
			time_t delaySeconds = entry.startupDelayMin * 60;
			if (now - m_serverStartTime < delaySeconds)
			{
				// Startup delay not yet elapsed, skip this event
				continue;
			}
		}

		// Check day of week (-1 means every day)
		if (entry.dayOfWeek != -1 && entry.dayOfWeek != nowDow)
			continue;

		bool shouldFire = false;

		if (entry.intervalMin > 0)
		{
			// Interval mode: fire every X minutes
			if (entry.lastFired == 0)
			{
				// First run - check if we should start now
				// If hour is set, only start firing from that hour onward
				if (entry.hour >= 0 && nowHour < entry.hour)
					continue;
				if (entry.hour >= 0 && nowHour == entry.hour && nowMin < entry.minute)
					continue;

				shouldFire = true;
			}
			else
			{
				// Check if enough minutes have elapsed since last fire
				time_t elapsed = now - entry.lastFired;
				if (elapsed >= entry.intervalMin * 60)
					shouldFire = true;
			}
		}
		else
		{
			// One-shot mode: fire at exact hour:minute
			if (entry.hour != nowHour || entry.minute != nowMin)
				continue;

			// Check if already fired this minute
			time_t firedMinute = entry.lastFired / 60;
			if (firedMinute == currentMinute)
				continue;

			shouldFire = true;
		}

		if (shouldFire)
		{
			entry.lastFired = now;
			FireEvent(entry);
		}
	}
}

void CAutoEventScheduler::FireEvent(AutoEventEntry& entry)
{
	switch (entry.eventType)
	{
	case AUTO_EVENT_RLGL:
	{
		if (gserver->m_RLGL.m_bevent_on)
		{
			GAMELOG << init("AUTO_EVENT") << "RLGL event already running, skipping scheduled start" << end;
			return;
		}
		GAMELOG << init("AUTO_EVENT") << "Auto-starting RLGL event (schedule index " << entry.index << ")" << end;
		gserver->m_RLGL.MoveToRegenPoint();
	}
	break;

	default:
		break;
	}
}
