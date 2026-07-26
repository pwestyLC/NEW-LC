#include "stdhdrs.h"

#include "Server.h"
#include "../ShareLib/DBCmd.h"
#include "CmdMsg.h"
#include "Craft.h"
#include "Log.h"

CCraft::CCraft()
{
	m_DataList = NULL;
	m_nCount = 0;
}

CCraft::~CCraft()
{
	RemoveAll();
}

void CCraft::RemoveAll()
{
	if( m_DataList )
	{
		delete [] m_DataList;
		m_DataList = NULL;
	}

	m_nCount = 0;
}

bool CCraft::Load()
{
	RemoveAll();
	CDBCmd dbCraft;
	dbCraft.Init(&gserver->m_dbdata);
	dbCraft.SetQuery("SELECT * FROM t_craft");

	if ( !dbCraft.Open() )
		return false;

	if( !dbCraft.MoveFirst() )
		return true;

	if(dbCraft.GetRecordCount() <= 0)
		return false;

	m_nCount = dbCraft.GetRecordCount();
	CraftData * td = new CraftData[dbCraft.GetRecordCount()];
	int j=0;
	do
	{
		dbCraft.GetRec("a_idx",		   td[j].index);
		dbCraft.GetRec("a_idx_item",   td[j].itemIdx);
		dbCraft.GetRec("a_count_item", td[j].countItem);
		dbCraft.GetRec("a_item1",	td[j].itemNeed[0]);
		dbCraft.GetRec("a_item2",	td[j].itemNeed[1]);
		dbCraft.GetRec("a_item3",	td[j].itemNeed[2]);
		dbCraft.GetRec("a_item4",	td[j].itemNeed[3]);
		dbCraft.GetRec("a_item5",	td[j].itemNeed[4]);
		dbCraft.GetRec("a_item6",	td[j].itemNeed[5]);
		dbCraft.GetRec("a_count1",	td[j].countNeed[0]);
		dbCraft.GetRec("a_count2",	td[j].countNeed[1]);
		dbCraft.GetRec("a_count3",	td[j].countNeed[2]);
		dbCraft.GetRec("a_count4",	td[j].countNeed[3]);
		dbCraft.GetRec("a_count5",	td[j].countNeed[4]);
		dbCraft.GetRec("a_count6",	td[j].countNeed[5]);
		dbCraft.GetRec("a_price",	td[j].price);

		map_.insert(map_t::value_type(td[j].index, &td[j]));

		j++;
	}
	while(dbCraft.MoveNext() );
	m_DataList = td;
	return true;
}

CraftData * CCraft::GetData(int craftIdx)
{
	map_t::iterator it = map_.find(craftIdx);
	return (it != map_.end()) ? it->second : NULL;
}

void do_CraftSystem(CPC* ch, CNetMsg::SP& msg)
{
	msg->MoveFirst();
	unsigned char subtype;

	RefMsg(msg) >> subtype;

	switch (subtype)
	{
	case MSG_CRAFT_ITEM:
		int needCreateIdx = -1;
		int needCreateCount = 0;

		RefMsg(msg) >> needCreateIdx >> needCreateCount;

		CNetMsg::SP rmsg(new CNetMsg);

		CraftData  *craft = gserver->m_craft.GetData(needCreateIdx);
		// Существует ли предмет в крафт системе
		if (craft == NULL)
		{
			MsgCraftResult(rmsg, MSG_CRAFT_NOT_ITEM);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}

		// Проверка на ограничение количества создания за 1 раз
		if (needCreateCount > 10000 || needCreateCount <= 0)
		{
			MsgCraftResult(rmsg, MSG_CRAFT_ERROR);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}

		LONGLONG price_max = craft->price * (LONGLONG)needCreateCount;

		if (price_max <= -1 || price_max == 0)
		{
			MsgCraftResult(rmsg, MSG_CRAFT_ERROR);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}

		// Проверка на доступность голды у персонажа
		if(craft->price * (LONGLONG) needCreateCount > ch->m_inventory.getMoney())
		{
			MsgCraftResult(rmsg, MSG_CRAFT_NOT_MONEY);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}
		
		for (int i = 0; i < MAX_CRAFT_ITEM_NEED; i++)
		{
			if (craft->itemNeed[i] == -1)
				continue;

			item_search_t vec;
			if (ch->m_inventory.searchItemByDBIndex((unsigned int)craft->itemNeed[i], vec) < craft->countNeed[i] * needCreateCount)
			{
				MsgCraftResult(rmsg, MSG_CRAFT_NOT_ENOUGHT_ITEM);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}
		}

		CItem* pItem = gserver->m_itemProtoList.CreateItem(craft->itemIdx, -1, 0, 0, needCreateCount * craft->countItem);
		if (pItem == NULL)
		{
			MsgCraftResult(rmsg, MSG_CRAFT_ERROR);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}

		if (!ch->m_inventory.addItem(pItem))
		{
			MsgCraftResult(rmsg, MSG_CRAFT_ERROR);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}
		
		for(int i = 0; i < MAX_CRAFT_ITEM_NEED; i++)
		{
			if(craft->itemNeed[i] == -1)
				continue;
			ch->m_inventory.deleteItemByDBIndex((unsigned int)craft->itemNeed[i], craft->countNeed[i] * needCreateCount);
		}

		ch->m_inventory.decreaseMoney(craft->price * (LONGLONG) needCreateCount);

		MsgCraftResult(rmsg, MSG_CRAFT_ITEM);
		SEND_Q(rmsg, ch->m_desc);
		break;
	}
}