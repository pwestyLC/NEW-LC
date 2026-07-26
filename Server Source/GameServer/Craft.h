#ifndef _CRAFT_HEADER_20090924_
#define _CRAFT_HEADER_20090924_

#define MAX_CRAFT_ITEM_NEED 6

void do_CraftSystem(CPC* ch, CNetMsg::SP& msg);

typedef struct __tagCraft
{
	int			index;
	int			itemIdx;
	int			countItem;
	int			itemNeed[MAX_CRAFT_ITEM_NEED];
	int			countNeed[MAX_CRAFT_ITEM_NEED];
	LONGLONG    price;

	__tagCraft()
	{
		index		= 0;
		itemIdx		= 0;
		countItem	= 1;
		for(int i = 0; i < MAX_CRAFT_ITEM_NEED;i++)
		{
			itemNeed[i] = -1;
			countNeed[i] = 0;
		}
		price		= 0;
	}
} CraftData;

class CCraft
{
public:
	typedef std::map<int, CraftData *> map_t;

	CCraft();
	~CCraft();

protected:
	map_t			map_;
	CraftData * m_DataList;
	int	m_nCount;

public:

	bool Load();
	void RemoveAll();

	int GetCount()
	{
		return m_nCount;
	}
	CraftData * GetData(int craftIdx);
};

#endif // #ifndef _CRAFT_HEADER_20090924_
//
