#ifndef __PERSONAL_SHOP_H__
#define __PERSONAL_SHOP_H__

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "../ShareLib/MemoryPoolBase.h"

// SHOP CONF
#define PS_MAX_NORMAL_ITEM			20		// �Ϲ� ������ �ŷ� �ִ� ��
#define PS_MAX_PACKAGE_ITEM			5		// ��Ű�� �Ǹ� �ŷ� �ִ� ��
//#define PS_NEED_MONEY_PREMIUM		5000	// �����̾� ���� ���� �ʿ� ����
#define PS_TEX_PREMIUM				200		// ����: �����̾�: 2%

#define PS_TEX_NORMAL				0		// ����: �Ϲ�: 0%

// PERSONAL SHOP TYPE
#define PST_NOSHOP			0
#define PST_SELL			(1 << 0)		// �Ǹ�
#define PST_BUY				(1 << 1)		// ����
#define PST_PREMIUM			(1 << 2)		// �����̾�
#define PST_PACKAGE			(1 << 3)		// ��Ű��
#define PST_SOLDOUT			(1 << 4)		// �Ǹ� ����
#define PST_OFFLINE			(1 << 5)		// ���λ��� ߴ

#ifdef OFFLINE_SHOPS
// Offline shop persistence constants
#define PS_OFFLINE_PERSIST_HOURS	24		// How long offline shops remain active (24 hours)
#define PS_OFFLINE_CLEANUP_PULSE	36000	// Cleanup pulse timer (3600 ticks = ~1 hour)

// Full item-fidelity record for lossless offline shop persistence.
// Mirrors the arguments of CItemProtoList::CreateDBItem so a rebuilt vendor
// can reconstruct the exact CItem (enchant/sockets/options/durability) after
// a server restart. Populated from the personal_shop_items fidelity columns.
struct PSItemFidelity
{
	bool	valid;						// true when loaded from DB fidelity columns
	int		wearPos;
	int		plus;
	int		flag;
	int		used;
	int		used_2;
	char	serial[MAX_SERIAL_LENGTH + 1];
	char	socketCount;
	short	option[MAX_ITEM_OPTION];
	int		jewel[MAX_SOCKET_COUNT];
	int		origin[MAX_VARIATION_COUNT];
	int		nowDurability;
	int		maxDurability;
};
#endif // OFFLINE_SHOPS

class CPersonalShop : public MemoryPoolBaseWithMutex<CPersonalShop>
{
	char			m_type;
	CLCString		m_name;
	int				m_sellerUserCode;			// Account user_code for cash transactions

	int				m_normalitemindex[PS_MAX_NORMAL_ITEM];
	int				m_normalitemdbindex[PS_MAX_NORMAL_ITEM];		// Item database index (type ID)
	int				m_normalitemid[PS_MAX_NORMAL_ITEM];			// personal_shop_items.item_id (for sale tracking)
	LONGLONG		m_normalCount[PS_MAX_NORMAL_ITEM];
	LONGLONG		m_normalPrice[PS_MAX_NORMAL_ITEM];

	// Full item fidelity for offline persistence (lossless restart restore).
	// Parallel to the m_normal* arrays; only meaningful for offline shops
	// loaded from / saved to personal_shop_items fidelity columns.
#ifdef OFFLINE_SHOPS
	PSItemFidelity	m_normalFidelity[PS_MAX_NORMAL_ITEM];
#endif

	int				m_packageitemindex[PS_MAX_PACKAGE_ITEM];
	int				m_packageitemdbindex[PS_MAX_PACKAGE_ITEM];	// Item database index (type ID)
	int				m_packageitemid[PS_MAX_PACKAGE_ITEM];		// personal_shop_items.item_id (for sale tracking)
	LONGLONG		m_packageCount[PS_MAX_PACKAGE_ITEM];
	LONGLONG		m_packagePrice;

	// Full item fidelity for package items (offline persistence)
#ifdef OFFLINE_SHOPS
	PSItemFidelity	m_packageFidelity[PS_MAX_PACKAGE_ITEM];

	// Offline mode and persistence fields
	bool			m_bOfflineMode;				// Whether shop is in offline mode
	int				m_shopId;					// Database shop_id (0 if not yet persisted)
	int				m_charIndex;				// Character ID for reference
	int				m_mapId;					// Map/zone where shop is located
	float			m_posX;						// X coordinate of shop location
	float			m_posY;						// Y coordinate (height)
	float			m_posZ;						// Z coordinate
	time_t			m_createdTime;				// When shop was created
	time_t			m_expiresTime;				// When offline shop expires (for 24-hour auto-close)
	LONGLONG		m_totalSales;				// Total NAS earned
	int				m_totalItemsSold;			// Total items sold count
#endif // OFFLINE_SHOPS

public:

	typedef boost::shared_ptr<CPersonalShop> SP;
	typedef boost::weak_ptr<CPersonalShop> WSP;

	CPersonalShop(char type, const char* name);

	bool AddItem(bool bNormal, int itemindex, int itemdbindex, LONGLONG count, LONGLONG price);

	int FindItem(bool bNormal, int itemindex);
	void RemoveNormalItem(int itemindex, LONGLONG count);
	void RemovePackage();

	char GetType()
	{
		return m_type;
	}
	const char* GetName()
	{
		return (const char*)m_name;
	}
	int GetSellerUserCode() const
	{
		return m_sellerUserCode;
	}
	void SetSellerUserCode(int userCode)
	{
		m_sellerUserCode = userCode;
	}
	char GetNormalCount();
	int GetNextNormalItem(int pos);
	int GetNormalItemIndex(int pos)
	{
		return (pos < 0 || pos >= PS_MAX_NORMAL_ITEM) ? -1 : m_normalitemindex[pos];
	}
	int GetNormalItemDBIndex(int pos)
	{
		return (pos < 0 || pos >= PS_MAX_NORMAL_ITEM) ? -1 : m_normalitemdbindex[pos];
	}
	LONGLONG GetNormalItemCount(int pos)
	{
		return (pos < 0 || pos >= PS_MAX_NORMAL_ITEM) ? -1 : m_normalCount[pos];
	}
	LONGLONG GetNormalItemPrice(int pos)
	{
		return (pos < 0 || pos >= PS_MAX_NORMAL_ITEM) ? -1 : m_normalPrice[pos];
	}

	// Full item-fidelity accessors for lossless offline persistence.
	// Returns NULL when the slot is empty or has no fidelity data.
#ifdef OFFLINE_SHOPS
	const PSItemFidelity* GetNormalItemFidelity(int pos) const
	{
		if (pos < 0 || pos >= PS_MAX_NORMAL_ITEM)
			return NULL;
		return &m_normalFidelity[pos];
	}
	void SetNormalItemFidelity(int pos, const PSItemFidelity& fid)
	{
		if (pos < 0 || pos >= PS_MAX_NORMAL_ITEM)
			return;
		m_normalFidelity[pos] = fid;
	}

	// Package item fidelity accessors
	const PSItemFidelity* GetPackageItemFidelity(int pos) const
	{
		if (pos < 0 || pos >= PS_MAX_PACKAGE_ITEM)
			return NULL;
		return &m_packageFidelity[pos];
	}
	void SetPackageItemFidelity(int pos, const PSItemFidelity& fid)
	{
		if (pos < 0 || pos >= PS_MAX_PACKAGE_ITEM)
			return;
		m_packageFidelity[pos] = fid;
	}
#endif // OFFLINE_SHOPS

	LONGLONG GetPackagePrice()
	{
		return m_packagePrice;
	}
	char GetPackageCount();
	int GetNextPackageItem(int pos);
	int GetPackageItemIndex(int pos)
	{
		return (pos < 0 || pos >= PS_MAX_PACKAGE_ITEM) ? -1 : m_packageitemindex[pos];
	}
	int GetPackageItemDBIndex(int pos)
	{
		return (pos < 0 || pos >= PS_MAX_PACKAGE_ITEM) ? -1 : m_packageitemdbindex[pos];
	}
	LONGLONG GetPackageItemCount(int pos)
	{
		return (pos < 0 || pos >= PS_MAX_PACKAGE_ITEM) ? 0 : m_packageCount[pos];
	}

	int GetNormalItemId(int pos)
	{
		return (pos < 0 || pos >= PS_MAX_NORMAL_ITEM) ? 0 : m_normalitemid[pos];
	}
	void SetNormalItemId(int pos, int itemid)
	{
		if (pos >= 0 && pos < PS_MAX_NORMAL_ITEM)
			m_normalitemid[pos] = itemid;
	}

	int GetPackageItemId(int pos)
	{
		return (pos < 0 || pos >= PS_MAX_PACKAGE_ITEM) ? 0 : m_packageitemid[pos];
	}
	void SetPackageItemId(int pos, int itemid)
	{
		if (pos >= 0 && pos < PS_MAX_PACKAGE_ITEM)
			m_packageitemid[pos] = itemid;
	}

	// Offline mode accessors
#ifdef OFFLINE_SHOPS
	bool IsOfflineMode() const { return m_bOfflineMode; }
	void SetOfflineMode(bool bOffline) { m_bOfflineMode = bOffline; }

	// Database persistence accessors
	int GetShopId() const { return m_shopId; }
	void SetShopId(int shopId) { m_shopId = shopId; }

	int GetCharIndex() const { return m_charIndex; }
	void SetCharIndex(int charIndex) { m_charIndex = charIndex; }

	int GetMapId() const { return m_mapId; }
	void SetMapId(int mapId) { m_mapId = mapId; }

	float GetPosX() const { return m_posX; }
	float GetPosY() const { return m_posY; }
	float GetPosZ() const { return m_posZ; }
	void SetPosition(float x, float y, float z) { m_posX = x; m_posY = y; m_posZ = z; }

	time_t GetCreatedTime() const { return m_createdTime; }
	void SetCreatedTime(time_t t) { m_createdTime = t; }

	time_t GetExpiresTime() const { return m_expiresTime; }
	void SetExpiresTime(time_t t) { m_expiresTime = t; }

	LONGLONG GetTotalSales() const { return m_totalSales; }
	void AddSales(LONGLONG amount) { m_totalSales += amount; }

	int GetTotalItemsSold() const { return m_totalItemsSold; }
	void IncrementItemsSold(int count) { m_totalItemsSold += count; }
#endif // OFFLINE_SHOPS
};

#endif
