#ifndef __PASSIVE_SYSTEM_H__
#define __PASSIVE_SYSTEM_H__

#include <map>
struct PassiveData
{
	int slotPos = -1;
	int slotId = -1;
	std::string passiveList;

};
class CPassiveSystemProtoList;

class CPassiveSystem
{
	friend class CPassiveSystemList;
public:
	CPassiveSystem();
	~CPassiveSystem();

	CPassiveSystem* Copy(int slot = -1) const;

	int m_index;
	int m_optionId;
	int m_optionLevel;

	COptionProto* optionProto;
	int m_slot;
};

class CPassiveSystemProtoList
{
public:
	typedef std::map<int, CPassiveSystem*> map_t;

	CPassiveSystemProtoList();
	~CPassiveSystemProtoList();

	map_t		map_;
	CPassiveSystem* m_passiveSystemList;
	int			m_nCount;

	bool Load();
	CPassiveSystem* FindPassiveSkill(int passiveSkillId);
};

class CPassiveSystemList
{
public:
	CPassiveSystemList();
	~CPassiveSystemList();

public:
	typedef boost::shared_ptr<CPassiveSystem> PassiveSystem;
	typedef std::map<int, PassiveSystem> map_t;
	map_t m_listItem;
public:
	int GetCount() const
	{
		return m_listItem.size();
	}

	bool Add(int nIndex, CPassiveSystem* pPassive);
	bool Remove(int nIndex);
	bool IsExists(int nIndex);
	CPassiveSystem* Find(int nIndex);

	void ApplyOptions(CPC* ch);

	map_t& getList()
	{
		return m_listItem;
	}

	void clear();
};
#endif

