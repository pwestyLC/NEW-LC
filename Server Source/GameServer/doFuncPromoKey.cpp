#ifdef PROMO_KEY_03312023
#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "Server.h"
#include "CmdMsg.h"
#include "doFunc.h"
#include "WarCastle.h"
#include "PromoKey.h"

bool do_PromoKeyUse(CPC* ch, CNetMsg::SP& msg);

void do_PromoKey(CPC* ch, CNetMsg::SP& msg)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(msg->m_buf);

	switch (pBase->subType)
	{
	case MSG_PROMO_KEY_USE: // Sent From Client (when trying to press enter)
		do_PromoKeyUse(ch, msg);
		break;

	default:
	{
		LOG_INFO("HACKING? : invalid subtype(%d)", pBase->subType);
		ch->m_desc->Close("invalid subtype");
	}
	break;
	}
}

bool do_PromoKeyUse(CPC* ch, CNetMsg::SP& msg)
{
    // Read key from message
    char key;
    RefMsg(msg) >> key;

    // Check if player is valid
    if (!ch)
        return false;

    // Check if key is valid
    if (!gserver->m_promoKey.HasValidKey(key))
    {
        CNetMsg::SP rmsg(new CNetMsg);
        PromoErrorMsg(rmsg, MSG_PROMO_KEY_NOT_VALID);
        SEND_Q(rmsg, ch->m_desc);
        return false;
    }

    // Get key index from promo key table
    int keyIdx = gserver->m_promoKey.GetKeyIndex(key);
    if (keyIdx == -1)
    {
        CNetMsg::SP rmsg(new CNetMsg);
        PromoErrorMsg(rmsg, MSG_PROMO_KEY_NOT_VALID);
        SEND_Q(rmsg, ch->m_desc);
        return false;
    }

    // Check if key has already been used by this character
    if (gserver->m_promoKey.HasCharacterUsedKey(keyIdx, ch->m_index))
    {
        CNetMsg::SP rmsg(new CNetMsg);
        PromoErrorMsg(rmsg, MSG_PROMO_KEY_ALREADY_USED);
        SEND_Q(rmsg, ch->m_desc);
        return false;
    }

    // Check if player's inventory has enough space for reward
    int rewardCount = gserver->m_promoKey.GetRewardPromoCount(keyIdx);
    if (ch->m_inventory.getEmptyCount() < rewardCount)
    {
        gserver->m_promoKey.SendRewardInventory(ch, keyIdx);
        LOG_INFO("Send Reward Inventory: character ID %d", ch->m_index);
    }
    else 
    {
        //They dont have enough inventory space lets send it to the mail marble instead 
        gserver->m_promoKey.SendRewardMail(ch, keyIdx);
        LOG_INFO("Send Reward Mail: character ID %d", ch->m_index);

    }
    // Log key use in database
    gserver->m_promoKey.AddPromoKeyUseToDB(keyIdx, ch->m_desc->m_index, ch->m_index, ch->GetName());

    LOG_INFO(" %s : Used Key Successfuly",ch->GetName());

    return true;
}
#endif
