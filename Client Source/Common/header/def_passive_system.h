
#ifndef		PASSIVE_SYSTEM_DATA_H_
#define		PASSIVE_SYSTEM_DATA_H_

#include "def_base.h"
#pragma pack(push, 1)

struct stPassiveSystem : public stTbl_base
{
	int OptionId;
	int OptionLevel;
	int IcoRow;
	int IcoCol;
	std::string	name;
	std::string	description;
};

#pragma pack(pop)
#endif		// PASSIVE_SYSTEM_DATA_H_