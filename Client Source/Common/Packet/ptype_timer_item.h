#ifndef __PTYPE_TIMER_ITEM_H__
#define __PTYPE_TIMER_ITEM_H__

#include "ptype_base.h"

// �Ⱓ�� ������
enum
{
	TIMERITEM_NON,
	TIMETITEM_TYPE_REMOTE_EXPRESS_SYSTEM,		// ���� â��NPC

	TIMERITEM_TYPE_CASH_INVENTORY_1,
	TIMERITEM_TYPE_CASH_INVENTORY_2,
	TIMERITEM_TYPE_CASH_INVENTORY_3,
	TIMERITEM_TYPE_CASH_INVENTORY_4,
	TIMERITEM_TYPE_CASH_INVENTORY_5,
	TIMERITEM_TYPE_CASH_INVENTORY_6,
	TIMERITEM_TYPE_PET_STASH,

	TIMERITEM_MAX,
};

// ��Ŷ sub type
enum
{
	MSG_SUB_TIMER_ITEM_LIST,		// �Ⱓ�� ������ ����Ʈ
	MSG_SUB_TIMER_ITEM_MODIFY,		// �Ⱓ�� ������ �߰� �� �ð� ����
	MSG_SUB_TIMER_ITEM_DELETE,		// �Ⱓ�� ������ ����
};

#pragma pack(push, 1)

namespace ResponseClient
{
	struct listTimerItem : public pTypeBase
	{
		int count;
		struct _list
		{
			int type;
			int expire_time;	// unix time
		} list[0];
	};

	struct modifyTimerItem : public pTypeBase
	{
		int item_type;
		int expire_time;
	};

	struct deleteTimerItem : public pTypeBase
	{
		int item_type;
	};

#ifndef _CLIENT_
	inline void makeTimerItemModify(CNetMsg::SP& msg, int type, int expire_time)
	{
		modifyTimerItem* p = reinterpret_cast<modifyTimerItem*>(msg->m_buf);
		p->type = MSG_TIMER_ITEM;
		p->subType = MSG_SUB_TIMER_ITEM_MODIFY;
		p->item_type = type;
		p->expire_time = expire_time;
		msg->setSize(sizeof(modifyTimerItem));
	}

	inline void makeTiemrItemDelete(CNetMsg::SP& msg, int type)
	{
		deleteTimerItem* p = reinterpret_cast<deleteTimerItem*>(msg->m_buf);
		p->type = MSG_TIMER_ITEM;
		p->subType = MSG_SUB_TIMER_ITEM_DELETE;
		p->item_type = type;
		msg->setSize(sizeof(deleteTimerItem));
	}
#endif
}

#pragma pack(pop)

#endif
