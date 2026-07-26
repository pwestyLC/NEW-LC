#pragma once

struct DonationEventInfo
{
	time_t StartTime;
	time_t FinishTime;
	bool IsActive;
	bool IsEnable;

	DonationEventInfo()
	{
		StartTime = 0;
		FinishTime = 0;
		IsActive = false;
		IsEnable = false;
	}
};

class DonationTierManager
{
public:
	DonationTierManager();
	~DonationTierManager();

	bool Load();
	void Tick();

	void UpdateStatus(bool isActive, time_t startTime = 0, time_t endTime = 0);
	void FinishEvent();

private:
	DonationEventInfo m_eventInfo;
};