#include "stdhdrs.h"
#include <boost/foreach.hpp>

#include "Cmd.h"
#include "Server.h"
#include "doFunc.h"
#include "MailBoxManager.h"
#include "DonationTierManager.h"

#include "CmdMsg.h"

DonationTierManager::DonationTierManager()
	: m_maxLevel(0)
	, m_lastTimeCheckProgress(0)
{
}

DonationTierManager::~DonationTierManager()
{
	m_tiersInfo.clear();
}

bool DonationTierManager::Load()
{
	m_tiersInfo.clear();

	CDBCmd dbData;
	dbData.Init(&gserver->m_dbdata);

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

	eventInfo.StartTime = (time_t)startTime;
	eventInfo.FinishTime = (time_t)finishTime;

	if (isEnable)
		eventInfo.IsEnable = true;

	m_eventInfo = eventInfo;

	if (!LoadReward())
	{
		LOG_ERROR("DonationTierManager :: Load() > load reward failed");
		return false;
	}

	return true;
}

bool DonationTierManager::LoadReward()
{
	std::string sql = "SELECT * FROM t_donation_levels ORDER BY a_level";
	CDBCmd dbData, dbData2;
	dbData.Init(&gserver->m_dbdata);
	dbData2.Init(&gserver->m_dbdata);
	dbData.SetQuery(sql);

	if (!dbData.Open() || !dbData.MoveFirst())
	{
		LOG_ERROR("DonationTierManager :: Load() > read from t_donation_levels failed");
		return false;
	}

	m_tiersInfo.clear();
	do
	{
		DonationTierInfo tierInfo;
		dbData.GetRec("a_level", tierInfo.Level);
		dbData.GetRec("a_max_points", tierInfo.LevelUpPoints);

		if (tierInfo.Level > m_maxLevel)
			m_maxLevel = tierInfo.Level;

		sql = boost::str(boost::format("SELECT * FROM t_donation_items WHERE a_level = %1% AND a_enable = 1 LIMIT %2%") % tierInfo.Level % DONATION_TIER_MAX_GIFTS);
		dbData2.SetQuery(sql);
		if (!dbData2.Open())
		{
			LOG_ERROR("DonationTierManager :: Load() > read from t_donation_items failed");
			return false;
		}

		while (dbData2.MoveNext())
		{
			DonationTierGift giftInfo;
			dbData2.GetRec("a_item_index", giftInfo.ItemIndex);
			dbData2.GetRec("a_item_count", giftInfo.ItemCount);
			dbData2.GetRec("a_item_flag", giftInfo.ItemFlag);
			dbData2.GetRec("a_item_plus", giftInfo.ItemPlus);

			tierInfo.Gifts.push_back(giftInfo);
		}

		m_tiersInfo.insert(std::make_pair(tierInfo.Level, tierInfo));
	} while (dbData.MoveNext());

	LOG_INFO("Donation levels: %d", m_tiersInfo.size());

	return true;
}

void DonationTierManager::InsertToHistory(CPC* pc, int spentMoney)
{
	if (pc == NULL)
	{
		LOG_ERROR("DonationTierManager :: InsertToHistory > cant find player : %d", spentMoney);
		return;
	}

	CDBCmd dbAuth;
	dbAuth.Init(&gserver->m_dbauth);

	std::string sql = boost::str(boost::format("INSERT INTO t_donation_history (a_user_index, a_sum, a_date) VALUES (%1%, %2%, NOW())") % pc->m_desc->m_index % spentMoney);
	dbAuth.SetQuery(sql);
	if (!dbAuth.Update())
	{
		LOG_ERROR("DonationTierManager :: InsertToHistory > insert to history failed : %d", pc->m_desc->m_index);
		return;
	}

	CalcProgress(pc);

	CNetMsg::SP msg(new CNetMsg);
	do_ExGiveDonationTierInfo(pc, msg);
}

void DonationTierManager::CalcProgress(CPC* pc)
{
	const DonationTierUserInfo userInfo = LoadUserInfo(pc);
	if (userInfo.Player == NULL) return;

	DonationTierInfo* tierInfo = findTierInfo(userInfo.Level);
	if (tierInfo == NULL)
	{
		LOG_ERROR("DonationTierManager :: CalcProgress > not found level data : %d", userInfo.Level);
		return;
	}

	CDBCmd dbAuth;
	dbAuth.Init(&gserver->m_dbauth);

	int sumPoints = userInfo.sumPoints();

	LOG_INFO("Sum %d Remain %d LevelPts %d", sumPoints, userInfo.RemainPoints, tierInfo->LevelUpPoints);

	if (sumPoints >= tierInfo->LevelUpPoints && userInfo.Level <= m_maxLevel)
	{
		std::string sql;

		dbAuth.BeginTrans();

		// check if remain point of the last transaction and increase level
		if (userInfo.RemainPoints >= tierInfo->LevelUpPoints)
		{
			sql = boost::str(boost::format("UPDATE t_donation_info SET a_remain_points = %1% WHERE a_user_index = %2%")
				% (userInfo.RemainPoints - tierInfo->LevelUpPoints) % pc->m_desc->m_index);

			dbAuth.SetQuery(sql);
			if (!dbAuth.Update())
			{
				LOG_ERROR("DonationTierManager :: CalcProgress > update remain points failed");
				dbAuth.Rollback();
				return;
			}
		}
		else
		{
			/**
			 * This part check the new transaction and increase the level.
			 * Also if there is remain point, update the remain info.
			 * */
			sql = boost::str(boost::format("SELECT a_transaction_index FROM t_donation_history WHERE a_user_index = %1% ORDER BY a_transaction_index DESC")
				% pc->m_desc->m_index);

			dbAuth.SetQuery(sql);
			if (!dbAuth.Open() || !dbAuth.MoveFirst())
			{
				LOG_ERROR("DonationTierManager :: CalcProgress > transactions load failed");
				dbAuth.Rollback();
				return;
			}

			int lastTransactionId = 0;
			int remainPoints = 0;

			dbAuth.GetRec("a_transaction_index", lastTransactionId);

			if (lastTransactionId > 0)
			{
				remainPoints = sumPoints - tierInfo->LevelUpPoints;
				sql = boost::str(boost::format("UPDATE t_donation_info info JOIN t_donation_history history ON history.a_transaction_index = %1% "
					"SET info.a_levelup_transaction_index = %1%, info.a_levelup_transaction_datetime = history.a_date, info.a_remain_points = %2% "
					"WHERE info.a_user_index = %3%") % lastTransactionId % remainPoints % pc->m_desc->m_index);

				dbAuth.SetQuery(sql);
				if (!dbAuth.Update())
				{
					LOG_ERROR("DonationTierManager :: CalcProgress > cant set last transaction index and set remain points");
					dbAuth.Rollback();
					return;
				}
			}
		}

		sql = boost::str(boost::format("UPDATE t_donation_info SET a_level = %2% WHERE a_user_index = %1%")
			% pc->m_desc->m_index % (userInfo.Level + 1));

		dbAuth.SetQuery(sql);
		if (!dbAuth.Update())
		{
			LOG_ERROR("DonationTierManager :: CalcProgress > update db level failed");
			dbAuth.Rollback();
			return;
		}

		dbAuth.Commit();
		TierUp(userInfo);

		sumPoints -= tierInfo->LevelUpPoints;
		tierInfo = findTierInfo(userInfo.Level + 1);
		if (tierInfo && sumPoints >= tierInfo->LevelUpPoints)
		{
			CalcProgress(pc);
		}
	}
}

DonationTierInfo* DonationTierManager::findTierInfo(int level)
{
	donation_tier_map::iterator iter = m_tiersInfo.find(level);
	if (iter == m_tiersInfo.end())
	{
		return NULL;
	}

	return &iter->second;
}

void DonationTierManager::TierUp(const DonationTierUserInfo& userInfo)
{
	int currentLevel = userInfo.Level;
	DonationTierInfo* tierInfo = findTierInfo(currentLevel);
	if (!tierInfo)
	{
		LOG_ERROR("DonationTierManager :: TierUp > cant find level info : %d", currentLevel);
		return;
	}

	int i = 0;
	SendingSystemMailInfo mailInfo;
	mailInfo.Receiver = userInfo.Player;
	mailInfo.Subject = "Donation tier bonus";
	mailInfo.Message = "Example message";

	BOOST_FOREACH(DonationTierGift & giftInfo, tierInfo->Gifts)
	{
		if (giftInfo.ItemIndex == 19)
		{
			mailInfo.Nas += giftInfo.ItemCount;
		}
		else
		{
			CItem* pItem = gserver->m_itemProtoList.CreateItem(giftInfo.ItemIndex, WEARING_NONE, giftInfo.ItemPlus, giftInfo.ItemFlag, giftInfo.ItemCount);
			if (pItem == NULL)
			{
				LOG_INFO("DonationTierManager :: TierUp > cant create gift item, skipping : item_id[%d]", giftInfo.ItemIndex);
			}
			else
			{
				mailInfo.Items[i++] = pItem;
				mailInfo.ItemCount = i;
			}
		}
	}

	DistributeDonationRewards(userInfo, mailInfo);
}

void DonationTierManager::DistributeDonationRewards(const DonationTierUserInfo& userInfo, SendingSystemMailInfo& mailInfo)
{
	const int emptyInventory = userInfo.Player->m_inventory.getEmptyCount();

	if (emptyInventory >= mailInfo.ItemCount)
	{
		for (const auto& item : mailInfo.Items)
		{
			if (item && !userInfo.Player->m_inventory.addItem(item))
			{
				LOG_INFO("DonationTierManager :: TierUp > cant add item to inventory, skipping : item_id[%d]", item->getDBIndex());
				delete item;
			}
		}

		if (mailInfo.Nas > 0)
			userInfo.Player->m_inventory.setMoney(mailInfo.Nas);
	}
	else
	{
		gserver->m_mailBoxManager.SendSystemMail((const SendingSystemMailInfo&)mailInfo);

		CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_DONATION_MAIL_REWARD);
		SEND_Q(rmsg, userInfo.Player->m_desc);

		for (auto& item : mailInfo.Items)
		{
			delete item;
			item = NULL;
		}
	}
}

const DonationTierUserInfo DonationTierManager::LoadUserInfo(CPC* pc)
{
	DonationTierUserInfo info;

	CDBCmd dbAuth;
	dbAuth.Init(&gserver->m_dbauth);

	std::string sql = boost::str(boost::format("SELECT a_level FROM t_donation_info WHERE a_user_index = %1% LIMIT 1")
		% pc->m_desc->m_index);

	dbAuth.SetQuery(sql);
	if (!dbAuth.Open())
	{
		LOG_ERROR("DonationTierManager :: LoadUserInfo > can't open db connection");
		return DonationTierUserInfo();
	}

	if (!dbAuth.MoveFirst())
	{
		sql = boost::str(boost::format("INSERT INTO t_donation_info (a_user_index, a_level) VALUES (%d, 0)") % pc->m_desc->m_index);
		dbAuth.SetQuery(sql);
		if (!dbAuth.Update())
		{
			LOG_ERROR("DonationTierManager :: LoadUserInfo > can't create donation tier info for user : %d", pc->m_desc->m_index);
			return DonationTierUserInfo();
		}

		info.Level = 0;
	}
	else
	{
		dbAuth.GetRec("a_level", info.Level);
	}

	time_t eventDuration = m_eventInfo.FinishTime - m_eventInfo.StartTime;
	sql = boost::str(boost::format("SELECT SUM(history.a_sum) as Points FROM t_donation_history history "
		"JOIN t_donation_info info ON info.a_user_index = history.a_user_index "
		"WHERE history.a_user_index = %1% AND history.a_transaction_index > info.a_levelup_transaction_index AND history.a_date > DATE_SUB(NOW(), INTERVAL %2% SECOND) "
		"UNION ALL SELECT info.a_remain_points as Points FROM t_donation_info info "
		"WHERE info.a_levelup_transaction_datetime > DATE_SUB(NOW(), INTERVAL %2% SECOND)")
		% pc->m_desc->m_index % eventDuration);
	dbAuth.SetQuery(sql);
	if (!dbAuth.Open())
	{
		LOG_ERROR("DonationTierManager :: LoadUserInfo > cant get user points : %d", pc->m_desc->m_index);
		return DonationTierUserInfo();
	}

	if (dbAuth.MoveFirst())
	{
		dbAuth.GetRec("Points", info.Points);
	}

	if (dbAuth.MoveNext())
	{
		dbAuth.GetRec("Points", info.RemainPoints);
	}

	info.Player = pc;
	return DonationTierUserInfo(info);
}

void DonationTierManager::Tick()
{
	time_t ctime = time(NULL);
	if (!m_eventInfo.IsActive && ctime >= m_eventInfo.StartTime && ctime < m_eventInfo.FinishTime)
	{
		m_eventInfo.IsActive = true;
		SendNofifyMessage();
		LOG_INFO("Donation event : started!");
	}
	else if (m_eventInfo.IsActive && ctime >= m_eventInfo.FinishTime)
	{
		m_eventInfo.IsActive = false;
		SendNofifyMessage();
		LOG_INFO("Donation event : finished!");
	}

	if (m_eventInfo.IsActive && ctime - m_lastTimeCheckProgress >= PULSE_REAL_MIN)
	{
		PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
		BOOST_FOREACH(PCManager::map_t::value_type i, playerMap)
		{
			LOG_INFO("Donation event auto progress calculation started");

			if (i.pPlayer)
			{
				CalcProgress(i.pPlayer);
			}

			LOG_INFO("Donation event auto progress calculation finished");
		}

		m_lastTimeCheckProgress = ctime;
	}
}

void DonationTierManager::UpdateStatus(bool isActive, time_t startTime, time_t endTime)
{
	m_eventInfo.IsEnable = true;
	m_eventInfo.StartTime = startTime;
	m_eventInfo.FinishTime = endTime;
}

void DonationTierManager::SendNofifyMessage()
{
	// only for save method signature
	CNetMsg::SP msg(new CNetMsg);

	PCManager::map_t& playerMap = PCManager::instance()->getPlayerMap();
	BOOST_FOREACH(PCManager::map_t::value_type i, playerMap)
	{
		if (i.pPlayer)
		{
			do_ExGiveDonationTierInfo(i.pPlayer, msg);
		}
	}
}