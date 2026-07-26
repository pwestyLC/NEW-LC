#pragma once

#include <vector>
#include <functional>
#include <Engine/DesignClasses/Singleton/SingletonBase.h>

struct MyDonationTierInfo
{
	int Level;
	int Points;
	time_t FinishTime;

	MyDonationTierInfo()
	{
		Level = 0;
		Points = 0;
		FinishTime = 0;
	}
};

struct DonationTierGift
{
	int			ItemIndex;
	LONGLONG	ItemCount;
};

struct TierInfo
{
	int Level;
	int LevelUpPoints;
	int PeriodDays;

	std::vector<DonationTierGift> Gifts;
};

class DonationTierManager : public CSingletonBase<DonationTierManager>
{
public:
	DonationTierManager();
	~DonationTierManager();

	void LoadInfo();
	void RecvInfo(CNetworkMessage* istr);

	const MyDonationTierInfo& getMyTierInfo() const {
		return m_myInfo;
	}

	bool TryGetTierInfo(TierInfo& tier, int Level);
	const std::vector<TierInfo>& getTiersInfoVec() const {
		return m_tiersInfo;
	}

	int getMaxPoints() const;
	int getUserGlobalPoints() const;
	bool isEventActive() const {
		return m_isActive;
	}

public:
	void RegisterCallback(std::function<void()> callback_)
	{
		m_callbackVec.push_back(callback_);
	}

private:
	bool m_isActive;
	MyDonationTierInfo m_myInfo;
	std::vector<TierInfo> m_tiersInfo;
	std::vector<std::function<void()>> m_callbackVec;
};