#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "Server.h"
#include "CmdMsg.h"
#include "doFunc.h"
#include "Item.h"
#include "../ShareLib/packetType/ptype_old_do_reform_system.h"

void do_Reform(CPC *ch_, CNetMsg::SP& msg);
void do_MidReform(CPC *ch_, CItem *reformerItem_, CItem *magnifierItem_, CItem *reformItem_, unsigned int count_);
void do_HighReform(CPC *ch_, CItem *reformerItem_, CItem *magnifierItem_, CItem *reformItem_, unsigned int count_);
#ifdef PREMIUM_REFORMER_11072021
void do_MegaReform(CPC *ch_, CItem *reformerItem_, CItem *magnifierItem_, CItem *reformItem_, unsigned int count_);
#endif
int canProgress(CNetMsg::SP& msg, CPC *ch_, CItem *pReformerItem_, CItem *pMagnifierItem_, CItem *pReformItem_, unsigned int count_, unsigned char reformerGrade_);
void useItemFromInventory(CPC *ch_, CNetMsg::SP& msg, CItem *pItem_, const int itemCount_);

void do_ReformSystem(CPC *ch, CNetMsg::SP& msg)
{
	if (ch == NULL)
		return ;

	if (DEAD(ch))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ReformerSystemRep(rmsg, MSG_EX_REFORMER_SYSTEM_EXCEPTION_ERROR_REP);
		SEND_Q(rmsg, ch->m_desc);
	}

	do_Reform(ch, msg);
}

void do_Reform(CPC *ch, CNetMsg::SP& msg)
{
	RequestClient::doReform* packet = reinterpret_cast<RequestClient::doReform*>(msg->m_buf);

	{
		std::set<int> checkdup;
		int key = 0;

		key = makeCheckDupKey(packet->reformer_tab, packet->reformer_invenIndex);
		if (checkdup.insert(key).second == false)
		{
			LOG_ERROR("HACKING? : dup index. charIndex[%d]", ch->m_index);
			ch->m_desc->Close("dup index");
			return;
		}

		key = makeCheckDupKey(packet->magnifire_tab, packet->magnifire_invenIndex);
		if (checkdup.insert(key).second == false)
		{
			LOG_ERROR("HACKING? : dup index. charIndex[%d]", ch->m_index);
			ch->m_desc->Close("dup index");
			return;
		}

		key = makeCheckDupKey(packet->reform_tab, packet->reform_invenIndex);
		if (checkdup.insert(key).second == false)
		{
			LOG_ERROR("HACKING? : dup index. charIndex[%d]", ch->m_index);
			ch->m_desc->Close("dup index");
			return;
		}
	}

	CNPC* npc = (CNPC*)ch->m_pArea->FindCharInCell(ch, packet->npcIndex, MSG_CHAR_NPC, false);
	if (npc == NULL)
	{
		LOG_ERROR("REFORM FAIL: NOT EXIST NPC. char_index[%d]", ch->m_index);
		ch->m_desc->Close("REFORM FAIL: NOT EXIST NPC");
		return ;
	}

	if (ch->m_inventory.isValidNormalInventory(packet->reformer_tab, packet->reformer_invenIndex) == false)
	{
		LOG_ERROR("HACKING? : invalid packet. char_index[%d] tab[%d] invenIndex[%d]",
				  ch->m_index, packet->reformer_tab, packet->reformer_invenIndex);
		ch->m_desc->Close("invalid packet");
		return;
	}

	if (ch->m_inventory.isValidNormalInventory(packet->magnifire_tab, packet->magnifire_invenIndex) == false)
	{
		LOG_ERROR("HACKING? : invalid packet. char_index[%d] tab[%d] invenIndex[%d]",
				  ch->m_index, packet->magnifire_tab, packet->magnifire_invenIndex);
		ch->m_desc->Close("invalid packet");
		return;
	}

	if (ch->m_inventory.isValidNormalInventory(packet->reform_tab, packet->reform_invenIndex) == false)
	{
		LOG_ERROR("HACKING? : invalid packet. char_index[%d] tab[%d] invenIndex[%d]",
				  ch->m_index, packet->reform_tab, packet->reform_invenIndex);
		ch->m_desc->Close("invalid packet");
		return;
	}

	// ������ ������ ���ϱ�, Ȳ�ݵ����� ������ ���ϱ�, ������ ������ ���ϱ�
	CItem *pReformerItem = ch->m_inventory.getItem(packet->reformer_tab, packet->reformer_invenIndex);
	CItem *pMagnifierItem = ch->m_inventory.getItem(packet->magnifire_tab, packet->magnifire_invenIndex);
	CItem *pReformItem = ch->m_inventory.getItem(packet->reform_tab, packet->reform_invenIndex);

	{
		CNetMsg::SP rmsg(new CNetMsg);
		int result = canProgress(rmsg, ch, pReformerItem, pMagnifierItem, pReformItem, packet->count, packet->grade);

		if ( result < 0)
		{
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}

		if (result == IETC_REFORMER_MID_GRADE)
		{
			do_MidReform(ch, pReformerItem, pMagnifierItem, pReformItem, packet->count);
		}
		else if (result == IETC_REFORMER_HIGH_GRADE)
		{
			do_HighReform(ch, pReformerItem, pMagnifierItem, pReformItem, packet->count);
		}
	#ifdef PREMIUM_REFORMER_11072021
		else if (result == IETC_MEGA_REFORMER_GRADE)
		{
			do_MegaReform(ch, pReformerItem, pMagnifierItem, pReformItem, packet->count);
		}
	#endif
		else
		{
			ReformerSystemRep(rmsg, MSG_EX_REFORMER_SYSTEM_EXCEPTION_ERROR_REP);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
	}
	// ������� ������ �۾� �Ϸ�. �Ʒ� �����۵��� ���Ϸ�� ���� �Ǿ��� ���� �־� NULLó�� ��. �׷��ٰ� ������ �������� ���� �۾����� ����.
	pReformerItem = NULL;
	pMagnifierItem = NULL;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ReformerSystemRep(rmsg, MSG_EX_REFORMER_SYSTEM_REFORM_SUCCESS_REP, pReformItem);
		SEND_Q(rmsg, ch->m_desc);
	}
}

void do_MidReform(CPC *ch_, CItem *reformerItem_, CItem *magnifierItem_, CItem *reformItem_, unsigned int count_)
{
	const int needReformerItem = 1;
	int nIndex_ = reformerItem_->m_itemProto->getItemIndex();
	// ������ �Ѱ� ����
	{
		CNetMsg::SP rmsg(new CNetMsg);
		useItemFromInventory(ch_, rmsg, reformerItem_, needReformerItem);
		SEND_Q(rmsg, ch_->m_desc);
	}

	// Ȳ�� ������ count_ ��ŭ ����
	{
		CNetMsg::SP rmsg(new CNetMsg);
		useItemFromInventory(ch_, rmsg, magnifierItem_, count_);
		SEND_Q(rmsg, ch_->m_desc);
	}

	// ������� ������ �۾� �Ϸ�. �Ʒ� �����۵��� ���Ϸ�� ���� �Ǿ��� ���� �־� NULLó�� ��. �׷��ٰ� ������ �������� ���� �۾����� ����.
	reformerItem_ = NULL;
	magnifierItem_ = NULL;

	// ������ ����
	reformItem_->IdentifyRareOption(true, count_, nIndex_);

	ch_->m_inventory.sendOneItemInfo(reformItem_);

	GAMELOG << init("RARE ITEM REFORM SUCCESS", ch_) << itemlog(reformItem_) << end;
}

void do_HighReform(CPC *ch_, CItem *reformerItem_, CItem *magnifierItem_, CItem *reformItem_, unsigned int count_)
{
	const int needReformerItem = 1;
	int nIndex = reformerItem_->m_itemProto->getItemIndex(); //Cloud Modify
	{
		CNetMsg::SP rmsg(new CNetMsg);
		useItemFromInventory(ch_, rmsg, reformerItem_, needReformerItem);
		SEND_Q(rmsg, ch_->m_desc);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		useItemFromInventory(ch_, rmsg, magnifierItem_, count_);
		SEND_Q(rmsg, ch_->m_desc);
	}

	reformerItem_ = NULL;
	magnifierItem_ = NULL;


	reformItem_->originReform(count_,nIndex);

	ch_->m_inventory.sendOneItemInfo(reformItem_);

	GAMELOG << init("ORIGIN ITEM REFORM SUCCESS", ch_) << itemlog(reformItem_) << end;

	if (ch_->m_admin > 0)
	{
		char tmpBuf[1024] = {0,};
		sprintf(tmpBuf, "ITEM REFORM SUCCESS [OPTION IDX : OPTION VARIATION], [%d : %d], [%d : %d], [%d : %d], [%d : %d], [%d : %d], [%d : %d]",
				reformItem_->GetOriginIndex(0), reformItem_->getOriginVar(0),
				reformItem_->GetOriginIndex(1), reformItem_->getOriginVar(1),
				reformItem_->GetOriginIndex(2), reformItem_->getOriginVar(2),
				reformItem_->GetOriginIndex(3), reformItem_->getOriginVar(3),
				reformItem_->GetOriginIndex(4), reformItem_->getOriginVar(4),
				reformItem_->GetOriginIndex(5), reformItem_->getOriginVar(5));
		CNetMsg::SP rmsg(new CNetMsg);
		SayMsg(rmsg, MSG_CHAT_NOTICE, 0, "", "", tmpBuf);
		SEND_Q(rmsg, ch_->m_desc);

		LOG_INFO("%s", tmpBuf);
	}
}

#ifdef PREMIUM_REFORMER_11072021
void do_MegaReform(CPC *ch_, CItem *reformerItem_, CItem *magnifierItem_, CItem *reformItem_, unsigned int count_)
{
	const int needReformerItem = 1;
	int nIndex = reformerItem_->m_itemProto->getItemIndex(); //cloud modify
	{
		CNetMsg::SP rmsg(new CNetMsg);
		useItemFromInventory(ch_, rmsg, reformerItem_, needReformerItem);
		SEND_Q(rmsg, ch_->m_desc);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		useItemFromInventory(ch_, rmsg, magnifierItem_, count_);
		SEND_Q(rmsg, ch_->m_desc);
	}

	reformerItem_ = NULL;
	magnifierItem_ = NULL;

	reformItem_->originReform(count_,nIndex);

	ch_->m_inventory.sendOneItemInfo(reformItem_);

	GAMELOG << init("ORIGIN ITEM REFORM SUCCESS", ch_) << itemlog(reformItem_) << end;

	if (ch_->m_admin > 0)
	{
		char tmpBuf[1024] = {0,};
		sprintf(tmpBuf, "ITEM REFORM SUCCESS [OPTION IDX : OPTION VARIATION], [%d : %d], [%d : %d], [%d : %d], [%d : %d], [%d : %d], [%d : %d]",
				reformItem_->GetOriginIndex(0), reformItem_->getOriginVar(0),
				reformItem_->GetOriginIndex(1), reformItem_->getOriginVar(1),
				reformItem_->GetOriginIndex(2), reformItem_->getOriginVar(2),
				reformItem_->GetOriginIndex(3), reformItem_->getOriginVar(3),
				reformItem_->GetOriginIndex(4), reformItem_->getOriginVar(4),
				reformItem_->GetOriginIndex(5), reformItem_->getOriginVar(5));
		CNetMsg::SP rmsg(new CNetMsg);
		SayMsg(rmsg, MSG_CHAT_NOTICE, 0, "", "", tmpBuf);
		SEND_Q(rmsg, ch_->m_desc);

		LOG_INFO("%s", tmpBuf);
	}
}
#endif

int canProgress(CNetMsg::SP& msg, CPC *ch_, CItem *pReformerItem_, CItem *pMagnifierItem_, CItem *pReformItem_, unsigned int count_, unsigned char reformerGrade_)
{
	// ������ ������ �ϳ��� ����.
	if (!pReformerItem_ || !pMagnifierItem_ || !pReformItem_)
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_EXCEPTION_ERROR_REP);
		return (-1);
	}
	// Ŭ���̾�Ʈ���� ������ �������̶�� �ذ� ������ �������� �ƴϴ�.
	if (!pReformerItem_->IsReformerItem())
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_NOT_GRADE_REP);
		return (-1);
	}

	if (pReformerItem_->Count() < 1)
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_EXCEPTION_ERROR_REP);
		return (-1);
	}

	// Ȳ�� ������ �������� �ƴϸ� ����, Ŭ���̾�Ʈ�� ���� ��� ������ ������������ ������ ����
	if (pMagnifierItem_->getDBIndex() != GOLD_MAGNIFIER)
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_NOT_GOLD_MAGNIFIER_REP);
		return (-1);
	}
	else if (pMagnifierItem_->Count() < count_ || count_ < 1 || count_ > 100)
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_EXCEPTION_ERROR_REP);
		return (-1);
	}

	// ������ �������� ���� ���� ��
	if (pReformItem_->getWearPos() != WEARING_NONE)
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_EXCEPTION_ERROR_REP);
		return (-1);
	}

	// ������ �������� �߱��ε� ������ �������� ����������� �ƴϸ� ����, ������ �������� ������ �ȵ� �������̶�� ����, ������ �������� �����Ұ� �÷��װ� üũ�Ǿ� ������ ����,
	if (pReformerItem_->m_itemProto->getItemNum0() == IETC_REFORMER_MID_GRADE && !pReformItem_->IsRareItem())
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_NOT_MID_ITEM_REP);
		return (-1);
	}
	else if (pReformerItem_->m_itemProto->getItemNum0() == IETC_REFORMER_MID_GRADE && pReformItem_->IsRareItem() && pReformItem_->m_nOption == 0)
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_NOT_REFORM_ITEM_REP);
		return (-1);
	}
	else if (pReformItem_->m_itemProto->getItemFlag() & ITEM_FLAG_NOTREFORM)
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_NOT_REFORM_ITEM_REP);
		return (-1);
	}
	else if (pReformerItem_->m_itemProto->getItemNum0() == IETC_REFORMER_MID_GRADE && pReformItem_->IsRareItem() && reformerGrade_ == IETC_REFORMER_MID_GRADE)
	{
		return IETC_REFORMER_MID_GRADE;
	}

	// ������ �������� ����ε� ������ �������� ������ �������� �ƴϸ� ����
	if (pReformerItem_->m_itemProto->getItemNum0() == IETC_REFORMER_HIGH_GRADE && !pReformItem_->IsOriginItem())
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_NOT_HIGH_ITEM_REP);
		return (-1);
	}
	else if (pReformItem_->m_itemProto->getItemFlag() & ITEM_FLAG_NOTREFORM)
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_NOT_REFORM_ITEM_REP);
		return (-1);
	}
	else if (pReformerItem_->m_itemProto->getItemNum0() == IETC_REFORMER_HIGH_GRADE && pReformItem_->IsOriginItem() && reformerGrade_ == IETC_REFORMER_HIGH_GRADE)
	{
		return IETC_REFORMER_HIGH_GRADE;
	}

 #ifdef PREMIUM_REFORMER_11072021
	if (pReformerItem_->m_itemProto->getItemNum0() == IETC_MEGA_REFORMER_GRADE && !pReformItem_->IsOriginItem())
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_NOT_HIGH_ITEM_REP);
		return (-1);
	}
	else if (pReformItem_->m_itemProto->getItemFlag() & ITEM_FLAG_NOTREFORM)
	{
		ReformerSystemRep(msg, MSG_EX_REFORMER_SYSTEM_NOT_REFORM_ITEM_REP);
		return (-1);
	}
	else if (pReformerItem_->m_itemProto->getItemNum0() == IETC_MEGA_REFORMER_GRADE && pReformItem_->IsOriginItem() && reformerGrade_ == IETC_MEGA_REFORMER_GRADE)
	{
		return IETC_MEGA_REFORMER_GRADE;
	}
#endif

	return (-1);
}

void useItemFromInventory(CPC *ch_, CNetMsg::SP& msg, CItem *pItem_, const int itemCount_)
{
	GAMELOG << init("USE ITEM FOR ITEM REFORM", ch_) << itemlog(pItem_) << end;

	ch_->m_inventory.decreaseItemCount(pItem_, itemCount_);
}
