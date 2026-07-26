#ifndef __PTYPE_CRAFT_H__
#define __PTYPE_CRAFT_H__

#include "ptype_base.h"

#pragma pack(push, 1)

#define MAX_CRAFT_ITEM_NEED 6

//////////////////////////////////////////////////////////////////////////
namespace RequestClient
{
struct doCraft : public pTypeThirdBase
{
	int itemCount;
	int itemNeed[MAX_CRAFT_ITEM_NEED];
	int countNeed[MAX_CRAFT_ITEM_NEED];
	int price;
};
}
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif
