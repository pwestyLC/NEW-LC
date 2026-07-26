#ifdef PROMO_KEY_03312023
#include "PromoKey.h"
#include <boost/format.hpp>
#include <boost/static_assert.hpp>
#include <boost/foreach.hpp>
#include "stdhdrs.h"

#include "Character.h"
#include "Server.h"
#include "CmdMsg.h"
#include "Log.h"
#include "DBManager.h"
#define MAX_PROMO_KEYS 25
#define MAX_ITEM_REWARD 5
cPromoKey::cPromoKey()
{
}

cPromoKey::~cPromoKey()
{
	promoKeys.clear();
	promoKeyRewards.clear();
	promoKeyUses.clear();
}

bool cPromoKey::LoadPromo()
{
    std::string promoKeyQuery = "SELECT * FROM t_promo_keys";
    promoKeys.clear();
    CDBCmd cmd;

    cmd.Init(&gserver->m_dbdata);
    cmd.SetQuery(promoKeyQuery.c_str());
    if (!cmd.Open() || !cmd.MoveFirst())
        return false;
    do
    {
        PromoKey promoKey;
        cmd.GetRec("a_index", promoKey.keyIdx);
        cmd.GetRec("a_key", promoKey.key);
        cmd.GetRec("a_use_remain", promoKey.keyUseRemain);
        cmd.GetRec("a_key_expire", promoKey.keyExpireDate);
        promoKeys.push_back(promoKey);
    } while (cmd.MoveNext());

    return true;
}

bool cPromoKey::LoadReward()
{
    promoKeyRewards.clear();

    std::string promoKeyRewardQuery = "SELECT * FROM t_promo_key_reward";
    CDBCmd cmdReward;
    cmdReward.Init(&gserver->m_dbchar);
    // Load PromoKeyRewards
    cmdReward.SetQuery(promoKeyRewardQuery.c_str());
    if (!cmdReward.Open() || !cmdReward.MoveFirst())
        return false;
    do
    {
        PromoKeyReward promoKeyReward;
        cmdReward.GetRec("a_key_index", promoKeyReward.keyIdx);
        for (int i = 0; i < MAX_ITEM_REWARD; i++)
        {
            cmdReward.GetRec(boost::str(boost::format("a_item_index%d") % i).c_str(), promoKeyReward.itemIndex[i]);
            cmdReward.GetRec(boost::str(boost::format("a_item_count%d") % i).c_str(), promoKeyReward.itemCount[i]);
        }
        promoKeyRewards.push_back(promoKeyReward);
    } while (cmdReward.MoveNext());
    return true;
}

void cPromoKey::AddPromoKeyUseToDB(int keyIdx, int userId, int charId, CLCString charName)
{

    {
        std::string query = boost::str(boost::format("INSERT INTO t_promo_key_use (a_key_id, a_user_id, a_char_id, a_char_name, a_use_date) VALUES (%d, %d, %d,'%s', NOW())") % keyIdx % userId % charId % (const char*)charName);
        CDBCmd cmd;
        cmd.Init(&gserver->m_dbchar);
        cmd.SetQuery(query.c_str());
        cmd.Update();
    }
}

int cPromoKey::GetKeyIndex(char key)
{
    CDBCmd cmd;
    cmd.Init(&gserver->m_dbchar);

    std::string query = boost::str(boost::format("SELECT a_index FROM t_promo_keys WHERE a_key='%s'") % key);
    cmd.SetQuery(query.c_str());

    if (!cmd.Open() || !cmd.MoveFirst())
        return -1;

    int index = -1;
    cmd.GetRec("a_index", index);

    return index;
}

bool cPromoKey::HasValidKey(char key)
{
    int keyIdx = GetKeyIndex(key);

    if (keyIdx == -1)
    {
        return false; // key is not valid
    }

    // Check if the key has expired
    time_t now;
    time(&now);

    if (now > promoKeys[keyIdx].keyExpireDate)
    {
        LOG_INFO("Debug :Time %d: Expire Time %d", now, promoKeys[keyIdx].keyExpireDate); //lets debug and see if its doing the calculation correctly.
        return false; // key has expired
    }

    return true; // key is valid
}

bool cPromoKey::HasCharacterUsedKey(char key, int charIdx)
{
    int keyIdx = GetKeyIndex(key);

    if (keyIdx == -1)
    {
        return false; // key is not valid
    }

    std::string promoKeyUseQuery = boost::str(boost::format("SELECT * FROM t_promo_key_use WHERE a_key_idx = %d AND a_char_id = %d") % keyIdx % charIdx);
    CDBCmd cmd;
    cmd.Init(&gserver->m_dbchar);
    cmd.SetQuery(promoKeyUseQuery.c_str());
    if (!cmd.Open() || !cmd.MoveFirst())
    {
        return false;
    }
    if (cmd.m_nrecords == 0)
    { // check if query returned any rows
        return false;
    }
    return true;
}


bool cPromoKey::RedeemPromoCheck()
{
	return false;
}

int cPromoKey::GetRewardPromoCount(int keyIdx)
{
    int count = 0;
    for (size_t i = 0; i < promoKeyRewards.size(); i++) {//interate through te promokeyreward ID and find an item index that isnt -1 then return the total count
        if (promoKeyRewards[i].keyIdx == keyIdx) {
            for (int j = 0; j < MAX_ITEM_REWARD; j++) {
                if (promoKeyRewards[i].itemIndex[j] != -1) {
                    count++;
                }
            }
        }
    }
    return count;
}
extern ExpressSystemItemInfo* makeExpressSystemItemInfo(CItem* pItem, int itemCount, int sendType, const char* sendName);

void cPromoKey::SendRewardInventory(CPC* ch, int keyIdx)
{
    if (!ch)
        return;
    
    // Find the reward for the given key index
    PromoKeyReward reward;

    for (std::vector<PromoKeyReward>::iterator it = promoKeyRewards.begin(); it != promoKeyRewards.end(); ++it)
    {
        if ((*it).keyIdx == keyIdx)
        {
            reward = (*it);
            break;
        }
    }

    // Add the items to the player's inventory
    for (int i = 0; i < MAX_ITEM_REWARD; ++i)
    {
        if (reward.itemIndex[i] != -1 && reward.itemCount[i] != 0)
        {
            CItem* item = gserver->m_itemProtoList.CreateItem(reward.itemIndex[i], -1, 0, 0, reward.itemCount[i]);
            if (item == NULL)
                continue;

            if (!ch->m_inventory.addItem(item))
            {
                delete item;
                continue;
            }

            LOG_INFO("Added Item Reward Success: %s Player %d : item", ch->GetName(), reward.itemIndex[i]);
        }
    }
}
void cPromoKey::SendRewardMail(CPC* ch, int keyIdx)
{

}
#endif