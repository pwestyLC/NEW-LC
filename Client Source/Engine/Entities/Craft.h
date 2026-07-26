#ifndef INCL_CRAFT_H
#define INCL_CRAFT_H
#ifdef PRAGMA_ONCE
#pragma once
#endif

#include <Engine/Help/LoadLod.h>
#include <Common/header/def_craft.h>
struct stCraft;
struct stCraftType;
struct stCraftSubType;
class ENGINE_API CCraft
{
public:
	static void Destroy();
	static bool	loadEx(const char* FileName);

	static std::vector<stCraft> m_vecCraft;
	typedef std::vector<stCraft>::iterator vecCraftIter;

	static std::vector<stCraftType> m_vecCraftType;
	typedef std::vector<stCraftType>::iterator vecCraftTypeIter;

	static std::vector<stCraftSubType> m_vecCraftSubType;
	typedef std::vector<stCraftSubType>::iterator vecCraftSubTypeIter;

	static stCraft GetCraftByItem(int itemId);
	static std::vector<stCraft> GetCraftByItems(int itemId);
	static stCraft GetCraftByItem(std::string itemName);
	static stCraft GetCraftById(int id);
	static stCraft GetFirstCraftItemNeed(int id);

	static bool IsNeedCraftItem(int idItem, int idNeedItem);

	static std::vector<stCraft> GetCraftBySubType(int type, int subType);

	static int GetCraftCount() { return m_vecCraft.size(); }
	static int GetTypeCount() { return m_vecCraftType.size(); }
	static int GetSubTypeCount() { return m_vecCraftSubType.size(); }
	
	static int GetCountSubTypeByType(int type);
	static int GetTypeByName(char* name);

	static std::vector<stCraftSubType> GetSubTypeByType(int type);
	static std::vector<stCraftSubType> GetSubTypeByType(char* name);
private:
	static stCraft* _data;
};

#endif

