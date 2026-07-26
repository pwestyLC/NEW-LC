#include "StdH.h"
#include "PassiveSystem.h"
#include <Engine/Base/CTString.h>

std::vector<stPassiveSystem> CPassiveSystem::m_vecPassive;

bool CPassiveSystem::loadEx(const char* szFileName)
{
	FILE* fp = NULL;

	if ((fp = fopen(szFileName, "rb")) == NULL)
	{
		{ CTString msg; msg.PrintF("File is not Exist: %s", szFileName); MessageBox(NULL, msg, "error!", MB_OK); }
		return FALSE;
	}

	fflush(fp);

	auto _count = 0;

	auto _readByte = fread(&_count, sizeof(int), 1, fp);

	ASSERT(_readByte > 0 && "Invalid PassiveSystem data");

#define LOADINT(d) _readByte = fread(&d,sizeof(int), 1, fp);

	for (auto i = 0; i < _count; i++)
	{
		stPassiveSystem pdata;
		LOADINT(pdata.index)
		LOADINT(pdata.OptionId)
		LOADINT(pdata.OptionLevel)
		LOADINT(pdata.IcoRow)
		LOADINT(pdata.IcoCol)

		m_vecPassive.push_back(pdata);
	}
#undef LOADINT

	fclose(fp);
	return true;
}

stPassiveSystem CPassiveSystem::GetPassiveById(int id)
{
	auto s_iter = m_vecPassive.begin();
	auto e_iter = m_vecPassive.end();
	while (s_iter < e_iter)
	{
		if (s_iter->index == id)
			return *s_iter;
		++s_iter;
	}
	stPassiveSystem result;
	result.index = -1;
	return result;
}
