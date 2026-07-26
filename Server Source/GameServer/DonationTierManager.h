#pragma once

#include <map>

#define DONATION_TIER_MAX_GIFTS	(5)


struct DonationTierUserInfo;
struct DonationTierInfo;
struct SendingSystemMailInfo;
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
	typedef std::map<int, DonationTierInfo> donation_tier_map;

public:
	DonationTierManager();
	~DonationTierManager();

	bool Load();
	bool LoadReward();
	void Tick();
	void UpdateStatus(bool isActive, time_t startTime = 0, time_t endTime = 0);

	int GetMaxLevel() const { return m_maxLevel; }
	void InsertToHistory(CPC* pc, int spentMoney);
	void CalcProgress(CPC* pc);
	const DonationEventInfo& GetEventInfo() const { return m_eventInfo; }
	const DonationTierUserInfo LoadUserInfo(CPC* pc);
	DonationTierInfo* findTierInfo(int level);

protected:
	virtual void TierUp(const DonationTierUserInfo& userInfo);
	void DistributeDonationRewards(const DonationTierUserInfo& userInfo, SendingSystemMailInfo& mailInfo);

private:
	void SendNofifyMessage();

private:
	donation_tier_map m_tiersInfo;
	DonationEventInfo m_eventInfo;
	int m_maxLevel;
	time_t m_lastTimeCheckProgress;
};

struct TransactionInfo
{
	int Points;
	time_t Time;
};

struct DonationTierUserInfo
{
	int		Level;
	int		Points;
	int		RemainPoints;
	CPC* Player;

	int sumPoints() const
	{
		return Points + RemainPoints;
	}

	DonationTierUserInfo()
	{
		Level = -1;
		Points = 0;
		RemainPoints = 0;
		Player = NULL;
	}
};

struct DonationTierGift
{
	int			ItemIndex;
	LONGLONG	ItemCount;
	int			ItemFlag;
	int			ItemPlus;

	DonationTierGift()
	{
		ItemIndex = -1;
		ItemCount = 0;
		ItemFlag = 0;
		ItemPlus = 0;
	}
};

struct DonationTierInfo
{
	int Level;
	int LevelUpPoints;
	std::vector<DonationTierGift> Gifts;

	DonationTierInfo()
	{
		Level = 0;
		LevelUpPoints = 0;
	}
};



