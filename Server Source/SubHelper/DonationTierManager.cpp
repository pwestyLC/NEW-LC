#include "stdhdrs.h"

#include "Server.h"
#include "DonationTierManager.h"

DonationTierManager::DonationTierManager()
{

}

DonationTierManager::~DonationTierManager()
{

}

bool DonationTierManager::Load()
{
	CDBCmd dbData;
	dbData.Init(&gserver.m_dbData);

	std::string sql = "SELECT UNIX_TIMESTAMP(a_start_date) as a_start_date, "
		"UNIX_TIMESTAMP(a_finish_date) as a_finish_date, a_enable "
		"FROM t_donation_event LIMIT 1";
	dbData.SetQuery(sql);
	if (!dbData.Open() || !dbData.MoveFirst())
	{
		LOG_ERROR("DonationTierManager :: Load() > read from t_donation_event failed");
		return false;
	}

	int isEnable;
	LONGLONG startTime = 0, finishTime = 0;
	DonationEventInfo eventInfo;
	dbData.GetRec("a_start_date", startTime);
	dbData.GetRec("a_finish_date", finishTime);
	dbData.GetRec("a_enable", isEnable);

	eventInfo.StartTime = (time_t) startTime;
	eventInfo.FinishTime = (time_t) finishTime;

	if (isEnable)
		eventInfo.IsEnable = true;
		
	m_eventInfo = eventInfo;
	return true;
}

void DonationTierManager::Tick()
{
	time_t ctime = time(NULL);
	if (!m_eventInfo.IsActive && ctime >= m_eventInfo.StartTime && ctime < m_eventInfo.FinishTime)
	{
		m_eventInfo.IsActive = true;
		LOG_INFO("Donation event : started!");
	}
	else if (m_eventInfo.IsActive && ctime >= m_eventInfo.FinishTime)
	{
		m_eventInfo.IsActive = false;
		FinishEvent();
		LOG_INFO("Donation event : finished!");
	}
}

void DonationTierManager::FinishEvent()
{
	CDBCmd db;
	db.Init(&gserver.m_dbAuth);

	std::string sql = "UPDATE t_donation_info SET a_level = 0, a_levelup_transaction_index = 0, a_remain_points = 0;";
	db.SetQuery(sql);
	if (!db.Update())
	{
		LOG_ERROR("DB ERROR : RESET DONATION EVENT : RESET LEVEL : %s", mysql_error(&gserver.m_dbAuth));
		return;
	}

	sql = "DELETE FROM t_donation_history;";
	db.SetQuery(sql);
	if (!db.Update())
	{
		LOG_ERROR("DB ERROR : RESET DONATION EVENT : DELETE HISTORY : %s", mysql_error(&gserver.m_dbAuth));
		return;
	}

	LOG_INFO("RESET DONATION EVENT DATA SUCCESS");
}

void DonationTierManager::UpdateStatus(bool isActive, time_t startTime, time_t endTime)
{
	m_eventInfo.IsEnable = true;
	m_eventInfo.StartTime = startTime;
	m_eventInfo.FinishTime = endTime;
}