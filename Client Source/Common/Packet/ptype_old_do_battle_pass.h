#ifndef __PTYPE_OLD_DO_BATTLE_PASS_H__
#define __PTYPE_OLD_DO_BATTLE_PASS_H__

#include "ptype_base.h"


#pragma pack(push, 1)
//////////////////////////////////////////////////////////////////////////
namespace RequestClient
{
struct battlePass : public pTypeBase
{
	int			npcIndex;	// memory index
	int			page;
};
}

namespace ResponseClient
{
struct battlePassError : public pTypeBase
{
	char		errorCode;
};
struct		battlePassItem {
	//int			type;
	int			level;
	int			points;
	char 		name[50];
	int			item_index;
	int			item_count;
	int			premium_item_index;
	int			premium_item_count;
};
struct battlePassInfo
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
	battlePassItem	list[0];
};

#ifndef _CLIENT_
inline void makeBattlePassError(CNetMsg::SP& msg, int subType)
{
	battlePassError* packet = reinterpret_cast<battlePassError*>(msg->m_buf);
	packet->type = MSG_BATTLE_PASS;
	packet->subType = subType;
	msg->setSize(sizeof(battlePassError));
}

inline void makeBattlePass(CNetMsg::SP& msg, int subType, int nIndex, int progress, int level)
{
	battlePassInfo* packet = reinterpret_cast<battlePassInfo*>(msg->m_buf);
	packet->type = MSG_BATTLE_PASS;
	packet->subType = subType;
	packet->nIndex = nIndex;
	packet->progress = progress;
	packet->level = level;
	msg->setSize(sizeof(battlePassInfo));
}

#endif
}
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif
