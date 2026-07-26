#ifndef __PTYPE_AUTHENTICATION_H__
#define __PTYPE_AUTHENTICATION_H__

#include "ptype_base.h"

#pragma pack(push, 1)
//////////////////////////////////////////////////////////////////////////
namespace Authentication
{
	struct auth  : public pTypeBase
	{
		unsigned char	nation;
		char			ip[16];
		unsigned short	port;
		char			mac[18];
	};
}
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif
