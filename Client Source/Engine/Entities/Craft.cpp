#include "stdh.h"
#include "Craft.h"

#include <Engine/Templates/StaticArray.cpp>

std::vector<stCraft> CCraft::m_vecCraft;
std::vector<stCraftType> CCraft::m_vecCraftType;
std::vector<stCraftSubType> CCraft::m_vecCraftSubType;
stCraft* CCraft::_data;

bool CCraft::loadEx(const char* szFileName)
{
	FILE*	fp = NULL;

	if ((fp = fopen(szFileName, "rb")) == NULL)
	{
		{ CTString msg; msg.PrintF("File is not Exist: %s", szFileName); MessageBox(NULL, msg, "error!", MB_OK); }
		return FALSE;
	}

	fflush(fp);

	auto _countType = 0;
	auto _countSubType = 0;
	auto _countCraft = 0;

	auto _readByte = fread(&_countType, sizeof(int), 1, fp);
	ASSERT(_readByte > 0 && "Invalid CraftLod data");

#define LOADINT(d) _readByte = fread(&d,sizeof(int), 1, fp);
#define LOADSTR(d) {int iLen;LOADINT(iLen);_readByte = fread(&d,iLen,1,fp);d[iLen]='\0';}
	for(auto i = 0; i < _countType; i++)
	{
		stCraftType pdata;
		LOADINT(pdata.type);
		LOADSTR(pdata.name);
		LOADSTR(pdata.english_name);

		m_vecCraftType.push_back(pdata);
	}
	fread(&_countSubType, sizeof(int), 1, fp);
	for(auto i = 0; i < _countSubType; i++)
	{
		stCraftSubType pdata;
		LOADINT(pdata.subType);
		LOADINT(pdata.type);
		LOADSTR(pdata.name);
		LOADSTR(pdata.english_name);

		m_vecCraftSubType.push_back(pdata);
	}
	fread(&_countCraft, sizeof(int), 1, fp);
	if (_countCraft == 0)
		return FALSE;

	stCraft craft;
	for(auto i = 0; i < _countCraft; i++)
	{
		LOADINT(craft.index);
		LOADINT(craft.itemIdx);
		LOADINT(craft.itemCount);
		LOADINT(craft.itemType);
		LOADINT(craft.itemSubType);
		LOADINT(craft.price);
		fread(&craft.itemNeed, sizeof(int) * MAX_CRAFT_ITEM_NEED, 1, fp);
		fread(&craft.countNeed, sizeof(int) * MAX_CRAFT_ITEM_NEED, 1, fp);
		m_vecCraft.push_back(craft);
	}
#undef LOADINT
#undef LOADSTR

	fclose(fp);
	return true;
}

stCraft CCraft::GetCraftByItem(int itemId)
{
	auto s_iter = m_vecCraft.begin();
	auto e_iter = m_vecCraft.end();
	while (s_iter < e_iter)
	{
		if (s_iter->itemIdx == itemId)
			return *s_iter;
		++s_iter;
	}
	stCraft result;
	result.itemIdx = -1;
	return result;
}

std::vector<stCraft> CCraft::GetCraftByItems(int itemId)
{
	auto s_iter = m_vecCraft.begin();
	auto e_iter = m_vecCraft.end();
	std::vector<stCraft> found;
	while (s_iter < e_iter)
	{
		if (s_iter->itemIdx == itemId)
			found.push_back(*s_iter);
		++s_iter;
	}
	return found;
}

stCraft CCraft::GetCraftById(int id)
{
	auto s_iter = m_vecCraft.begin();
	auto e_iter = m_vecCraft.end();
	while (s_iter < e_iter)
	{
		if (s_iter->index == id)
			return *s_iter;
		++s_iter;
	}
	stCraft result;
	result.itemIdx = -1;
	return result;
}

stCraft CCraft::GetFirstCraftItemNeed(int id)
{
	auto s_iter = m_vecCraft.begin();
	auto e_iter = m_vecCraft.end();
	while (s_iter < e_iter)
	{
		for(auto i = 0; i < MAX_CRAFT_ITEM_NEED; i++)
		{
			if (s_iter->itemNeed[i] == id)
				return *s_iter;
		}
		++s_iter;
	}
	stCraft result;
	result.itemIdx = -1;
	return result;
}

bool CCraft::IsNeedCraftItem(int idItem, int idNeedItem)
{
	auto s_iter = m_vecCraft.begin();
	auto e_iter = m_vecCraft.end();
	while (s_iter < e_iter)
	{
		if(s_iter->itemIdx == idItem)
			for (auto i = 0; i < MAX_CRAFT_ITEM_NEED; i++)
			{
				if (s_iter->itemNeed[i] == idNeedItem)
					return true;
			}
		++s_iter;
	}
	return false;
}

std::vector<stCraft> CCraft::GetCraftBySubType(int type, int subType)
{
	auto s_iter = m_vecCraft.begin();
	auto e_iter = m_vecCraft.end();
	std::vector<stCraft> found;
	while (s_iter < e_iter)
	{
		if (s_iter->itemSubType == subType && s_iter->itemType == type)
			found.push_back(*s_iter);
		++s_iter;
	}
	return found;
}

int CCraft::GetCountSubTypeByType(int type)
{
	auto s_iter = m_vecCraftSubType.begin();
	auto e_iter = m_vecCraftSubType.end();
	int count = 0;
	while(s_iter != e_iter)
	{
		if (s_iter->type == type)
			count++;
		++s_iter;
	}
	return count;
}

int CCraft::GetTypeByName(char * name)
{
	auto s_iter = m_vecCraftType.begin();
	auto e_iter = m_vecCraftType.end();
	while (s_iter != e_iter)
	{
		if (!strcmp( s_iter->name , name))
			return s_iter->type;
		++s_iter;
	}
	return -1;
}

std::vector<stCraftSubType> CCraft::GetSubTypeByType(int type)
{
	auto s_iter = m_vecCraftSubType.begin();
	auto e_iter = m_vecCraftSubType.end();
	std::vector<stCraftSubType> found;
	while(s_iter < e_iter)
	{
		if (s_iter->type == type)
			found.push_back(*s_iter);
		++s_iter;
	}
	return found;
}

std::vector<stCraftSubType> CCraft::GetSubTypeByType(char* name)
{
	auto s_iter = m_vecCraftSubType.begin();
	auto e_iter = m_vecCraftSubType.end();
	std::vector<stCraftSubType> found;
	auto type = GetTypeByName(name);
	if(type == -1)
		return m_vecCraftSubType;
	while (s_iter < e_iter)
	{
		if (s_iter->type == type)
			found.push_back(*s_iter);
		++s_iter;
	}
	return found;
}
