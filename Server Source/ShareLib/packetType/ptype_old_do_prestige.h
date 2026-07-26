#ifndef __PTYPE_OLD_DO_PRESTIGE_H__
#define __PTYPE_OLD_DO_PRESTIGE_H__

#include "ptype_base.h"

#ifdef PRESTIGE_SYSTEM
#pragma pack(push, 1)
//////////////////////////////////////////////////////////////////////////
namespace RequestClient
{
struct prestige : public pTypeBase
{
	int			npcIndex;	// memory index
	int			page;
};
}

namespace ResponseClient
{
struct prestigeError : public pTypeBase
{
	char		errorCode;
};
struct		prestigeItem {
	int			level;
	int			points;
	char 		name[50];
	int			item_index;
	int			item_count;
	int			premium_item_index;
	int			premium_item_count;
};
struct prestigeInfo : public pTypeBase
{
	int			nIndex;	// memory index
	int			level;
	int			progress;
	int			points;
	int			premium;
	int			total;
	int			page;
	char		next;	
	int         season;//Cloud add Season
	prestigeItem	list[0];
};

#ifndef _CLIENT_
inline void makePrestigeError(CNetMsg::SP& msg, int subType)
{
	prestigeError* packet = reinterpret_cast<prestigeError*>(msg->m_buf);
	packet->type = MSG_PRESTIGE;
	packet->subType = subType;
	msg->setSize(sizeof(prestigeError));
}

inline void makePrestige(CNetMsg::SP& msg, int subType, int nIndex, int progress, int level)
{
	prestigeInfo* packet = reinterpret_cast<prestigeInfo*>(msg->m_buf);
	packet->type = MSG_PRESTIGE;
	packet->subType = subType;
	packet->nIndex = nIndex;
	packet->progress = progress;
	packet->level = level;
	msg->setSize(sizeof(prestigeInfo));
}

#endif
}
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif

#endif
