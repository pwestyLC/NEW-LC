#ifndef INCL_PASSIVE_SYSTEM_H
#define INCL_PASSIVE_SYSTEM_H

#ifdef PRAGMA_ONCE
#pragma once
#endif

#include <Common/header/def_passive_system.h>

struct stPassiveSystem;

class ENGINE_API CPassiveSystem
{
public:
	static bool	loadEx(const char* FileName);

	static std::vector<stPassiveSystem> m_vecPassive;
	typedef std::vector<stPassiveSystem>::iterator vecCraftIter;

	static stPassiveSystem GetPassiveById(int id);
	static int GetPassiveCount() { return m_vecPassive.size(); }
private:
	static stPassiveSystem* _data;
};

#endif

