#include "stdhdrs.h"

#include "PromoKeyManager.h"

#include "CmdMsg.h"
#include "../ShareLib/LCString.h"
#include "Server.h"
#include "DBManager.h"

constexpr int PROMO_KEY_LENGTH = 16;

CPromoKeyManager::CPromoKeyManager()
{
}

CPromoKeyManager::~CPromoKeyManager()
{
}

bool CPromoKeyManager::Load()
{
	CDBCmd cmd;
	cmd.Init(&gserver->m_dbdata);
	cmd.SetQuery("SELECT a_index, a_key, a_reward_index, a_reward_count, UNIX_TIMESTAMP(a_date_end) AS a_date_unix_time FROM t_promo_key WHERE a_enable = 1");
	if (!cmd.Open())
	{
		GAMELOG << init("PROMO KEY LOAD FAIL") << end;
		return false;
	}

	while (cmd.MoveNext())
	{
		SPromoKeyModel model;
		cmd.GetRec("a_index", model.index);
		cmd.GetRec("a_key", model.key);
		cmd.GetRec("a_reward_index", model.rewardIndex);
		cmd.GetRec("a_reward_count", model.rewardCount);
		cmd.GetRec("a_date_unix_time", model.dateEnd);
		m_promoKeyList.push_back(model);
	}

	return true;
}

void CPromoKeyManager::UsePromoKey(CPC* pc, const CLCString& keyStr)
{
	const std::string key{ keyStr };
	if (key.length() > PROMO_KEY_LENGTH)
	{
		CNetMsg::SP msg(new CNetMsg);
		SayMsg(msg, MSG_CHAT_NOTICE, 0, "", "", "Promo key is invalid");
		SEND_Q(msg, pc->m_desc);
	}

	const auto promo = GetPromoKeyModel(pc, key);
	if (promo.index == -1)
	{
		CNetMsg::SP msg(new CNetMsg);
		SayMsg(msg, MSG_CHAT_NOTICE, 0, "", "", "Promo key is invalid");
		SEND_Q(msg, pc->m_desc);
	}

	if (promo.dateEnd > 0)
	{
		if (promo.dateEnd < gserver->getNowSecond())
		{
			CNetMsg::SP msg(new CNetMsg);
			SayMsg(msg, MSG_CHAT_NOTICE, 0, "", "", "Promo key is expired");
			SEND_Q(msg, pc->m_desc);
		}
	}

	if (std::find(pc->m_vecUsePromoKey.begin(), pc->m_vecUsePromoKey.end(), promo.index) != pc->m_vecUsePromoKey.end())
	{
		CNetMsg::SP msg(new CNetMsg);
		SayMsg(msg, MSG_CHAT_NOTICE, 0, "", "", "Promo key is already used");
		SEND_Q(msg, pc->m_desc);
	}

	const int emptyInventory = pc->m_inventory.getEmptyCount();
	const int emptyWarehouse = pc->m_inventory.getEmptyCountInStash();

	if (emptyInventory == 0 && emptyWarehouse == 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysFullInventoryMsg(rmsg, 0);
		SEND_Q(rmsg, pc->m_desc);
		return;

	}

	if (emptyInventory > 0)
	{
		if (!AddPromoKeyToUser(pc, promo))
		{
			LOG_ERROR("PROMO KEY ADD FAIL TO USER : %d", promo.index);
			return;
		}

		CItem* pItem = gserver->m_itemProtoList.CreateItem(promo.rewardIndex, -1, 0, 0, promo.rewardCount);
		if (!pc->m_inventory.addItem(pItem))
		{
			delete pItem;
			pItem = NULL;

			LOG_ERROR("PROMO KEY REWARD ITEM ADD FAIL TO INVENTORY : %d", promo.rewardIndex);
			return;
		}

		
		CNetMsg::SP msg(new CNetMsg);
		SayMsg(msg, MSG_CHAT_NOTICE, 0, "", "", "Promo key has been used. Gift added to inventory");
		SEND_Q(msg, pc->m_desc);
	}
	else if (emptyWarehouse > 0)
	{
		if (!AddPromoKeyToUser(pc, promo))
		{
			LOG_ERROR("PROMO KEY ADD FAIL TO USER : %d", promo.index);
			return;
		}

		CItem* pItem = gserver->m_itemProtoList.CreateItem(promo.rewardIndex, -1, 0, 0, promo.rewardCount);
		if (!pc->m_inventory.addItemInStash(pItem))
		{
			delete pItem;
			pItem = NULL;

			LOG_ERROR("PROMO KEY REWARD ITEM ADD FAIL TO STASH : %d", promo.rewardIndex);
			return;
		}


		CNetMsg::SP msg(new CNetMsg);
		SayMsg(msg, MSG_CHAT_NOTICE, 0, "", "", "Promo key has been used. Gift added to stash");
		SEND_Q(msg, pc->m_desc);
	}
}

bool CPromoKeyManager::AddPromoKeyToUser(CPC* pc, SPromoKeyModel promo)
{
	CDBCmd cmd;
	cmd.Init(&gserver->m_dbauth);

	const std::string query = boost::str(boost::format("INSERT INTO t_promo_key_user_use (a_user_index, a_promo_key_index, a_date) VALUES ('%1%', %2%, NOW())")
		% pc->m_desc->m_index
		% promo.index);
	cmd.SetQuery(query.c_str());

	if (!cmd.Update())
	{
		GAMELOG << init("PROMO KEY ADD FAIL")
			<< "UserIndex" << delim << pc->m_desc->m_index << delim
			<< "PromoKeyIndex" << delim << promo.index << end;
		return false;
	}

	pc->m_vecUsePromoKey.push_back(promo.index);
	return true;
}

SPromoKeyModel CPromoKeyManager::GetPromoKeyModel(CPC* pc, const std::string& key) const
{
	SPromoKeyModel model;
	model.index = -1;
	model.key = key;
	model.dateEnd = 0;

	for (auto& it : m_promoKeyList)
	{
		if (it.key == key)
		{
			model = it;
			break;
		}
	}

	return model;
}
