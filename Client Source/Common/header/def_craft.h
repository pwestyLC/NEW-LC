
#ifndef		CRAFT_DATA_H_
#define		CRAFT_DATA_H_

#include "def_base.h"
#pragma pack(push, 1)

#define MAX_CRAFT_ITEM_NEED 6

struct stCraft : public stTbl_base
{
	int itemIdx;
	int itemCount;
	int itemType;
	int itemSubType;
	int itemNeed[MAX_CRAFT_ITEM_NEED];
	int countNeed[MAX_CRAFT_ITEM_NEED];
	int price;
};

struct stCraftType
{
	int type;
	char name[64];
	char english_name[64];
};

struct stCraftSubType : stCraftType
{
	int subType;
};
#pragma pack(pop)
#endif		// CRAFT_DATA_H_