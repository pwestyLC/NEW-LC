#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "Server.h"
#include "CmdMsg.h"
#include "doFunc.h"
void do_PassiveSystem(CPC* ch, CNetMsg::SP& msg)
{
	msg->MoveFirst();

	unsigned char subtype;
	RefMsg(msg) >> subtype;

	switch (subtype)
	{
	case MSG_PASSIVE_SYSTEM_LIST:
		do_PassiveSystemList(ch, msg);
		break;
	case MSG_PASSIVE_SYSTEM_SLOT_LIST:
		do_PassiveSystemSlotList(ch, msg);
		break;
	case MSG_PASSIVE_SYSTEM_EQUIP_REQ:
		do_PassiveSystemEquip(ch, msg);
		break;
	case MSG_PASSIVE_SYSTEM_UNEQUIP_REQ:
		do_PassiveSystemUnequip(ch, msg);
		break;
	}
}

void do_PassiveSystemList(CPC* ch, CNetMsg::SP& msg)
{
	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_PASSIVE_SYSTEM);
	RefMsg(rmsg) << (unsigned char)MSG_PASSIVE_SYSTEM_LIST
		<< ch->m_passiveSystemList.GetCount();

	PassiveSystemListMsg(rmsg, ch);
	SEND_Q(rmsg, ch->m_desc);
}

void do_PassiveSystemSlotList(CPC* ch, CNetMsg::SP& msg)
{
	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_PASSIVE_SYSTEM);
	RefMsg(rmsg) << (unsigned char)MSG_PASSIVE_SYSTEM_SLOT_LIST
		<< ch->m_passiveSystemSlot.GetCount();

	PassiveSystemSlotListMsg(rmsg, ch);
	SEND_Q(rmsg, ch->m_desc);
}

bool do_PassiveSystemLearn(CPC* ch, const CItemProto* pItemProto)
{
	int passiveId = pItemProto->getItemNum0();

	CPassiveSystem* passive = gserver->m_passiveSystemList.FindPassiveSkill(passiveId);
	if (passive == NULL)
	{
		GAMELOG << init("PASSIVE SYSTEM ERROR", ch) << "(Learn) Not found id:" << passiveId << end;
		return false;
	}

	CPassiveSystem* passiveInList = ch->m_passiveSystemList.Find(passiveId);
	if (passiveInList != NULL)
	{
		return false;
	}

	ch->m_passiveSystemList.Add(passive->m_index, passive->Copy());

	GAMELOG << init("PASSIVE SYSTEM", ch) << "Passive learn: " << passiveId << end;

	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_PASSIVE_SYSTEM);
	RefMsg(rmsg) << (unsigned char)MSG_PASSIVE_SYSTEM_LEARN;
	SEND_Q(rmsg, ch->m_desc);

	return true;
}

void do_PassiveSystemEquip(CPC* ch, CNetMsg::SP& msg)
{
	int passiveIdx, slot;

	RefMsg(msg) >> passiveIdx >> slot;

	if (slot < 0 || slot > 2) return;

	CPassiveSystem* passiveInList = ch->m_passiveSystemList.Find(passiveIdx);
	if (passiveInList == NULL)
	{
		GAMELOG << init("PASSIVE SYSTEM ERROR", ch) << "(Equip) Not found id:" << passiveIdx << end;
		return;
	}

	CPassiveSystem* passiveInSlot = ch->m_passiveSystemSlot.Find(passiveIdx);
	if (passiveInSlot != NULL && passiveInSlot->m_slot != -1)
	{
		return;
	}

	ch->m_passiveSystemSlot.Add(slot, passiveInList->Copy(slot));

	ch->CalcStatus(true);

	GAMELOG << init("PASSIVE SYSTEM", ch)
		<< "Passive equipped: id:" << passiveIdx
		<< " slot: " << slot << end;

	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_PASSIVE_SYSTEM);
	RefMsg(rmsg) << (unsigned char)MSG_PASSIVE_SYSTEM_EQUIP_REP;
	SEND_Q(rmsg, ch->m_desc);
}

void do_PassiveSystemUnequip(CPC* ch, CNetMsg::SP& msg)
{
	int passiveIdx;

	RefMsg(msg) >> passiveIdx;

	CPassiveSystem* passiveInSlot = ch->m_passiveSystemSlot.Find(passiveIdx);
	if (passiveInSlot == NULL)
	{
		GAMELOG << init("PASSIVE SYSTEM ERROR", ch) << "(Unequipped) Not found in slot id:" << passiveIdx << end;
		return;
	}

	int slot = passiveInSlot->m_slot;
	const bool result = ch->m_passiveSystemSlot.Remove(passiveInSlot->m_index);

	ch->CalcStatus(true);

	if (result)
	{
		GAMELOG << init("PASSIVE SYSTEM", ch)
			<< "Passive unequipped: id:" << passiveIdx
			<< " slot: " << slot << end;

		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_PASSIVE_SYSTEM);
		RefMsg(rmsg) << (unsigned char)MSG_PASSIVE_SYSTEM_UNEQUIP_REP << passiveIdx;
		SEND_Q(rmsg, ch->m_desc);
	}
}