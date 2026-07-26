#ifndef __PTYPE_OLD_DO_REBORN_H__
#define __PTYPE_OLD_DO_REBORN_H__

#include "ptype_base.h"

#pragma pack(push, 1)
//////////////////////////////////////////////////////////////////////////
namespace RequestClient
{
struct reborn : public pTypeBase
{
	int			npcIndex;	// memory index
};
}

namespace ResponseClient
{
struct rebornError : public pTypeBase
{
	char		errorCode;
};

struct reborn : public pTypeBase
{
	int			nIndex;
	int			maxReborn;
	int			currentReborn;
};

#ifndef _CLIENT_
inline void makeRebornError(CNetMsg::SP& msg, int subType)
{
	rebornError* packet = reinterpret_cast<rebornError*>(msg->m_buf);
	packet->type = MSG_REBORN;
	packet->subType = subType;
	msg->setSize(sizeof(rebornError));
}

inline void makeReborn(CNetMsg::SP& msg, int nIndex, int maxReborn, int currentReborn)
{
	reborn* packet = reinterpret_cast<reborn*>(msg->m_buf);
	packet->type = MSG_REBORN;
	packet->subType = MSG_REBORN_REP;
	packet->nIndex = nIndex;
	packet->maxReborn = maxReborn;
	packet->currentReborn = currentReborn;
	msg->setSize(sizeof(reborn));
}

#endif
}
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif
