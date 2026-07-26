#include "StdH.h"
#include <boost/foreach.hpp>

#include <Engine/DesignClasses/Singleton/SingletonBase.h>
#include "DonationTierManager.h"

#include <Engine/Network/CNetwork.h>

DonationTierManager::DonationTierManager()
	: m_isActive(false)
{

}

DonationTierManager::~DonationTierManager()
{
	m_tiersInfo.clear();
}

void DonationTierManager::LoadInfo()
{
	CNetworkMessage msg(MSG_EXTEND);
	msg << (ULONG)MSG_EX_GET_DONATION_TIER_INFO;

	_pNetwork->SendToServerNew(msg);
}

void DonationTierManager::RecvInfo(CNetworkMessage* istr)
{
	m_tiersInfo.clear();

	int isActive;
	(*istr) >> isActive;

	if (isActive)
	{
		LONGLONG finishTime;
		(*istr) >> finishTime;
		(*istr) >> m_myInfo.Level;
		(*istr) >> m_myInfo.Points;

		m_myInfo.FinishTime = _pTimer->GetHighPrecisionTimer().GetSeconds() + finishTime;

		int tierCount;
		(*istr) >> tierCount;
		for (int i = 0; i < tierCount; i++)
		{
			TierInfo tier;
			(*istr) >> tier.Level
				>> tier.LevelUpPoints;

			int giftsCount;
			(*istr) >> giftsCount;
			for (int k = 0; k < giftsCount; k++)
			{
				DonationTierGift gift;
				(*istr) >> gift.ItemIndex >> gift.ItemCount;
				tier.Gifts.push_back(gift);
			}

			m_tiersInfo.push_back(tier);
		}
	}

	m_isActive = isActive;
	BOOST_FOREACH(std::function<void()> callback, m_callbackVec)
	{
		if (callback) callback();
	}
}

bool DonationTierManager::TryGetTierInfo(TierInfo& tier, int Level)
{
	auto iter = std::find_if(m_tiersInfo.begin(), m_tiersInfo.end(), 
		[&Level](const TierInfo& t1) { return t1.Level == Level; });

	bool founded = iter != m_tiersInfo.end();
	if(founded) tier = *iter;
	return founded;
}

int DonationTierManager::getMaxPoints() const
{
	int points = 0;
	BOOST_FOREACH(TierInfo tierInfo, m_tiersInfo)
	{
		points += tierInfo.LevelUpPoints;
	}
	return points;
}

int DonationTierManager::getUserGlobalPoints() const
{
	int points = 0;
	BOOST_FOREACH(TierInfo tierInfo, m_tiersInfo)
	{
		if (tierInfo.Level < m_myInfo.Level)
			points += tierInfo.LevelUpPoints;
		else if (tierInfo.Level == m_myInfo.Level)
			points += m_myInfo.Points;
	}
	return points;
}
