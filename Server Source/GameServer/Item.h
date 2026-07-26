// Item.h: interface for the CItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEM_H__91327288_815B_4A26_AF31_0F9098AEECF3__INCLUDED_)
#define AFX_ITEM_H__91327288_815B_4A26_AF31_0F9098AEECF3__INCLUDED_

#define COMPOSE_ITEM_FILENAME "/data/itemCompose.bin"

#include <vector>
#include <set>
#include <boost/thread.hpp>

#include "CPos.h"
#include "Option.h"
#include "RareOptionProto.h"
#include "SetItemProto.h"
#include "SocketSystem.h"
#include "InventoryManager.h"
#include "../ShareLib/MemoryPoolBase.h"

class CAffinityProto;

class CItemProto
{
public:

	CItemProto();
	CItemProto(const CItemProto& other);
	virtual ~CItemProto();

private:
	//////////////////
	// DB ���� ����
	int			m_index;		// �����۹�ȣ
	int			m_typeIdx;		// Ÿ������
	int			m_subtypeIdx;	// ����Ÿ������
	CLCString	m_name;			// �������̸�
	int			m_jobFlag;		// �������
	LONGLONG	m_flag;			// �Ӽ�
	int			m_maxUse;		// ������
	int			m_fame;			// ����ġ

	int m_num0;
	int	m_num1;
	int	m_num2;
	int	m_num3;
	int	m_num4;

	int m_set0;
	//int m_QuestZone;

	int m_set1;
	//int m_questX;

	int m_set2;
	//int m_questZ;

	int m_set3;
	//int m_questY;

	int m_set4;			// ��Ʈ ������ Index
	//int m_questRange ;	// ����Ʈ ������ �ݰ�

	int			m_grade;			// ������ �깫��Ÿ������ ���
	int			m_stackcount;		// ���� ���Ը� ����� ���� ������ �����
	LONGLONG	m_price;			// ����

	int			m_wearing;			// ���� ��ġ

	// ������ ���
	int		m_materialIndex[MAX_MAKE_ITEM_MATERIAL];
	int		m_materialCount[MAX_MAKE_ITEM_MATERIAL];

	int		m_needSSkillIndex;
	int		m_needSSkillLevel;

	int		m_needSSkillIndex2;
	int		m_needSSkillLevel2;

	int		m_nRareIndex[MAX_RARE_OPTION_ITEM];				// ���� Index, �ɼ�/��ų Index(0 : �ͼ� ����, 1~6 : �ɼ�, 7~9 : ��ų)
	int		m_nRareProb[MAX_RARE_OPTION_ITEM];				// ���� Ȯ��,  �ɼ�/��ų Level(1~6 : �ɼ�, 7~9 : ��ų)

	int		m_level;			// ����

	int		m_level2;			// ������ ����2
	int m_MaxOriginVariation[MAX_VARIATION_COUNT];

	int		m_rvr_type;
	int		m_rvr_grade;

#ifdef DURABILITY
	int		m_durability;		// ��� ������
#endif
	int		m_castle_war;
// ---------------------------------------------
public:

	int getItemProtoOriginVariation(int nIndex) const
	{
		return m_MaxOriginVariation[nIndex];
	}
	int getItemIndex() const
	{
		return m_index;
	}

	void setItemIndex(int index)
	{
		m_index = index;
	}

	int getItemTypeIdx() const
	{
		return m_typeIdx;
	}

	void setItemTypeIdx(int typeIdx)
	{
		m_typeIdx = typeIdx;
	}

	int getItemSubTypeIdx() const
	{
		return m_subtypeIdx;
	}

	void setItemSubTypeIdx( int subtypeIdx)
	{
		m_subtypeIdx = subtypeIdx;
	}

	CLCString getItemName() const
	{
		return m_name;
	}

	int getItemJobFlag() const
	{
		return m_jobFlag;
	}

	void setItemJobFlag(int jobflag)
	{
		m_jobFlag = jobflag;
	}

	LONGLONG getItemFlag() const
	{
		return m_flag;
	}

	void setItemFlag(int flag)
	{
		m_flag = flag;
	}

	int getItemMaxUse() const
	{
		return m_maxUse; // ������
	}

	int getItemFrame() const
	{
		return m_fame;	// ����ġ.
	}

	int getItemNum0() const
	{
		return m_num0;
	}

	int getItemNum1() const
	{
		return m_num1;
	}

	int getItemNum2() const
	{
		return m_num2;
	}

	int getItemNum3() const
	{
		return m_num3;
	}

	int getItemNum4() const
	{
		return m_num4;
	}

	int getItemSet0() const
	{
		return m_set0;
	}

	int getItemQuestZone() const
	{
		return m_set0;
	}

	int getItemSet1() const
	{
		return m_set1;
	}

	int getItemQuestX() const
	{
		return m_set1;
	}

	int getItemSet2() const
	{
		return m_set2;
	}

	int getItemQuestZ() const
	{
		return m_set2;
	}

	int getItemSet3() const
	{
		return m_set3;
	}

	int getItemQuestY() const
	{
		return m_set3;
	}

	int getItemSet4() const
	{
		return m_set4;
	}

	int getItemQuestRange() const
	{
		return m_set4;
	}

	int getItemGrade() const
	{
		return m_grade;
	}

	int getStackCount() const
	{
		return m_stackcount;
	}

	LONGLONG getItemPrice() const
	{
		return m_price;
	}

	int getItemWearing() const
	{
		return m_wearing;
	}

	int getItemMaterialIndex( int i ) const
	{
		return m_materialIndex[ i ];
	}

	int getItemMaterialCount( int i ) const
	{
		return m_materialCount[ i ];
	}

	int getItemNeedSSkillIndex() const
	{
		return m_needSSkillIndex;
	}

	int getItemNeedSSkillLevel() const
	{
		return m_needSSkillLevel;
	}

	int getItemNeedSSkillIndex2() const
	{
		return m_needSSkillIndex2;
	}


	int getItemRareIndex( int i ) const
	{
		return m_nRareIndex[i];
	}

	int getItemRareProb( int i ) const
	{
		return m_nRareProb[i];
	}

	int getItemLevel() const
	{
		return m_level;
	}

	int getItemLevel2() const
	{
		return m_level2;
	}

	int getItemRvRType() const
	{
		return m_rvr_type;
	}

	int getItemRvRGrade() const
	{
		return m_rvr_grade;
	}
	// DB���� �������

#ifdef DURABILITY
	int getDurability() const
	{
		return m_durability;
	}
#endif

	int getCastleWar() const
	{
		return m_castle_war;
	}

public:

	friend class CItemList;

	bool IsRareItem() const
	{
		return (m_flag & ITEM_FLAG_RARE) ? true : false;
	}

	bool IsComposeItem() const
	{
		return (m_flag & ITEM_FLAG_COMPOSE) ? true : false;
	}

	// �������� ��� ���� ���� : ITEM_FLAG_UPGRADE && !ITEM_FLAG_COMPOSITE
	bool CanBloodGem() const
	{
		if ((m_flag & ITEM_FLAG_UPGRADE) == 0)
			return false;
		if ((m_flag & ITEM_FLAG_COMPOSITE) || ((m_flag & FLAG_ITEM_TRANSMOGRIFY)))
			return false;
		if (IsRareItem())
			return false;
		if (IsOriginItem())
			return false;

		return true;
	}

	int GetItemProtoLevel() const
	{
		return m_level;
	}

	int GetItemProtoLevel2() const
	{
		return m_level2;
	}

	bool IsOriginItem() const
	{
		return (m_flag & ITEM_FLAG_ORIGIN) ? true : false;
	}

	int GetSetIndex() const
	{
		return m_set4;
	}
	int GetBelongType() const
	{
		return m_nRareIndex[0];
	}
	int GetOriginIndex(int nPos) const
	{
		return m_nRareIndex[1 + nPos];
	}
	int GetOriginLevel(int nPos) const
	{
		return m_nRareProb[1 + nPos];
	}
	int GetOriginOptionCnt() const
	{
		return pre_origin_option_count_;
	}
	int GetOriginSkillCnt() const
	{
		return pre_origin_skill_count_;
	}

	std::vector<CAffinityProto*>	m_affinityList;

	bool IsRangeWeapon()
	{
		return is_range_weapon_;
	}
	bool IsMagicWeapon()
	{
		return is_magic_weapon_;
	}
	int GetUsingStat()
	{
		return get_using_stat_;
	}
	bool IsWeaponType()
	{
		return is_weapon_type_;
	}
	bool IsArmorType()
	{
		return is_armor_type_;
	}
	bool IsAccessary()
	{
		return is_accessary_;
	}
	bool IsPet()
	{
		return is_pet_;
	}
	bool IsAPet()
	{
		return is_apet_;
	}

	bool IsUpgradeRune()
	{
		return is_upgrade_rune_;
	}

	bool IsJewelType()
	{
		return is_jewel_type_;
	}

	bool IsChaosJewelType()
	{
		return is_chaos_jewel_type_;
	}

	bool IsStableType()
	{
		return is_stable_type_;
	}
	bool IsFuncType()
	{
		return is_func_type_;
	}
	bool IsSocketItem()
	{
		return is_socket_type_;
	}
	bool IsReformerItem()
	{
		return is_reformer_item_;
	}
	bool isAllowSocketItem()
	{
		return is_allow_socket;
	}
	bool isProcessScroll()
	{
		return is_process_scroll_;
	}
	bool isRebirthItem()
	{
		return is_rebirth_item_;
	}
	bool isMonsterCard()
	{
		return is_monster_card_;
	}
	bool isRVRNotUse() const
	{
		return is_rvr_not_use_;
	}
	bool isSyndicate()
	{
		return is_syndicate_;
	}
	bool isUseInWarZone()
	{
		return is_useinwarzone_;
	}
	bool isTimer()
	{
		return is_timer_;
	}
	bool isRvrJewel()
	{
		return is_rvr_jewel_;
	}
	bool isGPS()
	{
		return is_gps_;
	}
	bool isQuuestGive()
	{
		return is_questGive;
	}

private:
	int			pre_origin_option_count_;
	int			pre_origin_skill_count_;

	bool		is_range_weapon_;
	bool		is_magic_weapon_;
	int			get_using_stat_;
	bool		is_weapon_type_;
	bool		is_armor_type_;
	bool		is_accessary_;
	bool		is_pet_;
	bool		is_apet_;

	bool		is_upgrade_rune_;

	bool		is_jewel_type_;

	bool		is_chaos_jewel_type_;

	bool		is_stable_type_;
	bool		is_func_type_;
	bool		is_socket_type_;
	bool		is_reformer_item_;
	bool		is_allow_socket;
	bool		is_process_scroll_;
	bool		is_rebirth_item_;
	bool		is_monster_card_;
	bool		is_rvr_not_use_;
	bool		is_syndicate_;
	bool		is_useinwarzone_;		// ���忡�� ��밡���Ѱ�?
	bool		is_timer_;
	bool		is_rvr_jewel_;
	bool		is_gps_;
	bool		is_questGive;

	// --- Ref tracking for safe reload ---
	mutable boost::mutex m_refMutex;
	std::set<CItem*>     m_refItems;
public:
	void addRef(CItem* item)
	{
		boost::mutex::scoped_lock lock(m_refMutex);
		m_refItems.insert(item);
	}
	void removeRef(CItem* item)
	{
		boost::mutex::scoped_lock lock(m_refMutex);
		m_refItems.erase(item);
	}
	int getRefCount() const
	{
		boost::mutex::scoped_lock lock(m_refMutex);
		return (int)m_refItems.size();
	}
	std::set<CItem*> takeAllRefs()
	{
		boost::mutex::scoped_lock lock(m_refMutex);
		std::set<CItem*> r;
		r.swap(m_refItems);
		return r;
	}
};

enum TRADE_TYPE { TRADE_EXCHANGE = 0, TRADE_PERSONAL_SHOP, TRADE_SELL, TRADE_STASH, TRADE_TRADEAGENT, TRADE_DROP };

class CItem : public MemoryPoolBaseWithMutex<CItem>
{
public:
	friend class Inventory;
	friend class InventoryManager;
	friend class CInventoryRow;
	friend class CItemList;
	friend class CStash;

private:
	/////////////////////
	// �κ��丮 ��ġ ����
	int			m_tab_idx;			// ��
	int			m_invenIndex;		// �κ��丮�������� ��ġ

	LONGLONG	m_count;			// ����

	int			m_virualIndex;		// ���� �ε���
	int			m_dbIndex;			// DB �ε���

	// ������ �Ӽ�
	char		m_wearPos;			// ������ġ/��
	// 0 ~ 11	: ���� ���� Ư�� ���� ���� ���� �尩 �Ź� �׼�����1, 2, 3
	// -1		: ���� ����

	int			m_plus;				// + ��ġ, �ֿϵ��� �������� ��� �ش� �ֿϵ��� INDEX
	// ���� ä�� ���� : ä�� ���� ������ 1 (4��Ʈ * 8����)
	// ���� �뺴 ī�� : npcIndex
	// �������� ������ : zoneIndex

	int			m_plus2;			// ��Ʈ ������ : "����/����&���/����" ��ġ ����
	// ���� �뺴 ī�� : ���ݷ°� ���� ��ġ�� �־��ش�.
	// �������� ������ : x, y ��ǥ (��Ʈ�� ������ ������ �־��ش�.

	int			m_flag;				// �Ӽ�

	int			m_used;				// ������
	// ���굵�� ������
	// �÷�Ƽ�� ��ü� �Ⱓ
	// �ǻ� �Ⱓ
	// �ǻ� ���� �Ⱓ
	// ���� ä�� ���� : ä�� ���� ������ 2 (4��Ʈ * 8����)

	int			m_used_2;			// ���տ��ǻ�:	���� �ֹ��� ��� �Ⱓ, �Ⱓ�� ������ ���� �ð�
	// ����, ���:	���� �ٿ� �ֹ��� ��� �Ⱓ,
	// ���� �뺴 ī�� : classInx

#ifdef DURABILITY
	int			now_durability;		// ���� ��� ������
	int			max_durability;		// �ִ� ��� ������
#endif

public:
	CItem();
	~CItem();

	//////////////////
	// DB ���� ����
	CItemProto*	m_itemProto;

	void setItemProto(CItemProto* proto)
	{
		if (m_itemProto == proto)
			return;
		if (m_itemProto)
			m_itemProto->removeRef(this);
		m_itemProto = proto;
		if (m_itemProto)
			m_itemProto->addRef(this);
	}

	LONGLONG getItemCount()
	{
		return m_count;
	}
	void setItemCount(LONGLONG count);

	int getInvenIndex()
	{
		return m_invenIndex;
	}
	int getVIndex()
	{
		return m_virualIndex;
	}
	void setVIndex(int index)
	{
		m_virualIndex = index;
	}

	int getDBIndex()
	{
		return m_dbIndex;
	}
	void setDBIndex(int index)
	{
		m_dbIndex = index;
	}

	char getWearPos()
	{
		return m_wearPos;
	}
	void setWearPos(char pos)
	{
		m_wearPos = pos;
	}
	void unWearPos()
	{
		m_wearPos = WEARING_NONE;
	}

	int getPlus()
	{
		return m_plus;
	}
	void setPlus(int plus)
	{
		m_plus = plus;
	}

	int getPlus_2()
	{
		return m_plus2;
	}
	void setPlus_2(int plus)
	{
		m_plus2 = plus;
	}

	int getFlag()
	{
		return m_flag;
	}
	void setFlag(int flag)
	{
		m_flag = flag;
	}	

	int getUsed()
	{
		return m_used;
	}
	void setUsed(int used)
	{
		m_used = used;
	}

	int getUsed_2()
	{
		return m_used_2;
	}
	void setUsed_2(int used)
	{
		m_used_2 = used;
	}

	int			m_MercenaryIndex;	// ��ȯ�� ���� �뺴�� ���� index;

	COption		m_option[MAX_ITEM_OPTION];	// ������ �ɼ�, ���� �������� ��� 0�� ���� �ε��� 2����Ʈ, 1�� ���� ��Ʈ �ʵ� 2����Ʈ
	int			m_nOption;					// ������ �ɼ� ��

	const CRareOptionProto* m_pRareOptionProto; // ����ɼ� ������
	int			m_nRareOptionIndex;	// ���� �ɼ� �ε���
	int			m_nRareOptionBit;	// ���� �ɼ� ��Ʈ �ʵ�

	// �ռ��� ������ : �Ⱓ�� ���� �������� ���� ������ �����ε����� ����, ������ -1
	// DB ����ÿ��� tab, invenindex�� �����Ͽ� ����
	// ���յ� �ǻ� : db flag / flag is set
	// ���մ��� �ǻ� : flag is set
	int			m_nCompositeItem;

	const CSetItemProto* m_pSetItemProto;
	int			m_nSetWearCnt;		// ��Ʈ ������ ���� ����
	int			m_nSetOption;		// ��Ʈ �ɼ� ���� ���� - 1: �ɼǸ� ����, 2: ��ų���� ����
	////////////
	// ��Ÿ �Ӽ�
	CArea*		m_pArea;			// Area
	CPos		m_pos;				// ��ǥ
	int			m_cellX;			// �� ��ġ
	int			m_cellZ;
	CItem*		m_pCellPrev;		// �� ��ũ�� ����Ʈ
	CItem*		m_pCellNext;

	int			m_groundPulse;		// �������� ������ �ð� ����
	int			m_preferenceIndex;	// ������ �ݴ� �켱���� ���� pc�� �ε���

	int tab()
	{
		return m_tab_idx;
	}

	void SetDropNpc(int nIndex)
	{
		setPlus(nIndex);
	}
	int  GetDropNpc()
	{
		return getPlus();
	}

	LONGLONG Count() const
	{
		return m_count;
	}

	bool IsRangeWeapon()
	{
		return  m_itemProto->IsRangeWeapon();
	}
	bool IsMagicWeapon()
	{
		return m_itemProto->IsMagicWeapon();
	}

// 050311 : bs : ���Ⱑ � ������ ����ϴ��� �˻�
	int GetUsingStat()
	{
		return m_itemProto->GetUsingStat();
	}

// --- 050311 : bs : ���Ⱑ � ������ ����ϴ��� �˻�
	bool IsWeaponType() const
	{
		return m_itemProto->IsWeaponType();
	}

	bool IsArmorType() const
	{
		return m_itemProto->IsArmorType();
	}

	bool IsAccessary()
	{
		return m_itemProto->IsAccessary();
	}
	bool IsPet()
	{
		return m_itemProto->IsPet();
	}
	bool IsAPet()
	{
		return m_itemProto->IsAPet();
	}

	bool IsUsedPlatinumSpecial()
	{
		int platinumPlus;
		FLAG_ITEM_PLATINUM_GET(getFlag(), platinumPlus);
		return ( (m_itemProto->getItemTypeIdx() == ITYPE_WEAPON || m_itemProto->getItemTypeIdx() == ITYPE_WEAR) && platinumPlus > 0 );
	}

	bool IsUpgradeRune() const
	{
		return m_itemProto->IsUpgradeRune();
	}

	// ��ȯ ������ �������ΰ�?
	bool CanExchange()
	{
#ifdef ENABLE_SUBJOB
		if( !(m_itemProto->getItemFlag()&ITEM_FLAG_SELLER) &&
				!(m_itemProto->getItemFlag()&ITEM_FLAG_EXCHANGE) )		// Ʈ���̴� üũ�Ǿ��ִ� ��ȯ �÷��� �˻� ����
			return false;
#else
		// ������ �˻�
		if (!(m_itemProto->getItemFlag() & ITEM_FLAG_EXCHANGE))
			return false;
#endif //ENABLE_SUBJOB

		// ���� ������ �Ұ���
		if (m_wearPos != WEARING_NONE)
			return false;

		// ���� ������ �Ұ���
		if (getFlag() & FLAG_ITEM_SEALED)
			return false;

		// ���� ������ �Ұ���
		if (getFlag() & FLAG_ITEM_COMPOSITION)
			return false;

		// �뿩 ������ �Ҵ�
		if (IsLent())
			return false;

		if (IsUsedPlatinumSpecial())
			return false;

		// �ͼ� ������ �Ұ���
		if (IsBelong())
			return false;

		return true;
	}

	// ���(������ ����) ������ �������ΰ�
	bool CanDrop()
	{
#ifdef ENABLE_SUBJOB
		if( !(m_itemProto->getItemFlag()&ITEM_FLAG_SELLER) &&
				!(m_itemProto->getItemFlag()&ITEM_FLAG_DROP) )		// Ʈ���̴� üũ�Ǿ��ִ� ��� �÷��� �˻� ����
			return false;
#else
		if (!(m_itemProto->getItemFlag() & ITEM_FLAG_DROP))
			return false;
#endif //ENABLE_SUBJOB

		// ���� ������ �Ұ���
		if (m_wearPos != WEARING_NONE)
			return false;

		// ���� ������ �Ұ���
		if (m_flag & FLAG_ITEM_COMPOSITION)
			return false;

		// �뿩 ������ �Ҵ�
		if (IsLent())
			return false;

		if (IsUsedPlatinumSpecial())
			return false;

		// �ͼ� ������ �Ұ���
		if (IsBelong())
			return false;

		// ����Ʈ ������ �Ұ���
		if (m_itemProto->getItemFlag() & ITEM_FLAG_QUEST)
			return false;

		if (m_itemProto->getItemTypeIdx() == ITYPE_ETC && m_itemProto->getItemSubTypeIdx() == IETC_QUEST)
			return false;

		return true;
	}

	// ������ �Ǹ� ���� ����
	bool CanSellToShop()
	{
#ifdef ENABLE_SUBJOB
		if( !(m_itemProto->getItemFlag()&ITEM_FLAG_SELLER) &&
				!(m_itemProto->getItemFlag()&ITEM_FLAG_TRADE) )		// Ʈ���̴� üũ�Ǿ��ִ� �����Ǹ� �÷��� �˻� ����
			return false;
#else
		if (!(m_itemProto->getItemFlag() & ITEM_FLAG_TRADE))
			return false;
#endif //ENABLE_SUBJOB

		// ���� ������ �Ұ���
		if (m_wearPos != WEARING_NONE)
			return false;

		// ���� ������ �Ұ���
		if (getFlag() & FLAG_ITEM_COMPOSITION)
			return false;

		// �뿩 ������ �Ҵ�
		if (IsLent())
			return false;

		if (IsUsedPlatinumSpecial())
			return false;
		
		return true;
	}

	// â�� ���� ���� ����
	bool CanKeepStash()
	{
#ifdef ENABLE_SUBJOB
		if( !(m_itemProto->getItemFlag()&ITEM_FLAG_SELLER) &&
				m_itemProto->getItemFlag() & ITEM_FLAG_NO_STASH )		// Ʈ���̴� üũ�Ǿ��ִ� â�� �÷��� �˻� ����
			return false;
#else
		if (m_itemProto->getItemFlag() & ITEM_FLAG_NO_STASH)
			return false;
#endif //ENABLE_SUBJOB

		// ���� ������ �Ұ���
		if (m_wearPos != WEARING_NONE)
			return false;

		// ���� ������ �Ұ���
		if (getFlag() & FLAG_ITEM_COMPOSITION)
			return false;

		// �ð��� ������ �Ұ���
		if (m_itemProto->getItemFlag() & ITEM_FLAG_ABS)
		{
			return false;
		}

		if (IsUsedPlatinumSpecial())
			return false;


		// �ͼ� ������ �Ұ���
		if (IsBelong())
			return false;

		return true;
	}

#ifdef ENABLE_SUBJOB
	bool	CheckTrader()
	{
		return m_itemProto->getItemFlag()&ITEM_FLAG_SELLER?true:false;
	}
	bool	CanUseTrader( int type , bool bTrader )
	{
		if( !(m_itemProto->getItemFlag() & ITEM_FLAG_SELLER) )
			return true;

		bool ret = false;

		switch( type )
		{
		case TRADE_EXCHANGE :
		case TRADE_PERSONAL_SHOP :
		case TRADE_TRADEAGENT :
		case TRADE_DROP :
			{
				if( (m_itemProto->getItemFlag() & ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH | ITEM_FLAG_ABS )) ==  ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH | ITEM_FLAG_ABS ) ||
						(m_itemProto->getItemFlag() & ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH | ITEM_FLAG_COSTUME2 )) == ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH | ITEM_FLAG_COSTUME2 ) ||
						(m_itemProto->getItemFlag() & ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH | ITEM_FLAG_COMPOSITE )) == ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH | ITEM_FLAG_COMPOSITE ) )
					ret = false;
				else if ((getFlag() & FLAG_ITEM_TRANSMOGRIFY))
					ret = false;
				else if( (m_itemProto->getItemFlag()&( ITEM_FLAG_SELLER | ITEM_FLAG_CASH )) == ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH ) )
					ret = bTrader? true:false;
				else if(  !(m_itemProto->getItemFlag()&ITEM_FLAG_CASH) && m_itemProto->getItemFlag()&ITEM_FLAG_SELLER )
					ret = true;
				else
					ret = true;
			}
			break;
		case TRADE_SELL :
			{
				if( m_itemProto->getItemFlag() & ITEM_FLAG_SELLER )
					ret = false;
				else
					ret = true;
			}
			break;
		case TRADE_STASH :
			{
				if( (m_itemProto->getItemFlag() & ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH | ITEM_FLAG_ABS )) == ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH | ITEM_FLAG_ABS ) ||
						(m_itemProto->getItemFlag() & ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH | ITEM_FLAG_COSTUME2 )) == ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH | ITEM_FLAG_COSTUME2 ) ||
						(m_itemProto->getItemFlag() & ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH | ITEM_FLAG_COMPOSITE )) == ( ITEM_FLAG_SELLER | ITEM_FLAG_CASH | ITEM_FLAG_COMPOSITE ) ||
						(getFlag() & FLAG_ITEM_TRANSMOGRIFY) )
					ret = false;
				else
					ret = true;
			}
			break;
		default:
			ret = true;
		}

		return ret;
	}
#endif //ENABLE_SUBJOB

	// ���ü� ���̱� ���� ����
	bool CanUpgrade()
	{
		if ((m_itemProto->getItemFlag() & ITEM_FLAG_UPGRADE) == 0)
			return false;
		if (IsLent())
			return false;
		return true;
	}

	// �������� ��� ���� ���� : ITEM_FLAG_UPGRADE && !ITEM_FLAG_COMPOSITE
	bool CanBloodGem()
	{
		if (!m_itemProto->CanBloodGem())
			return false;
		return true;
	}

	// ���� ���� �˻�
	bool CanWear()
	{
		if (m_itemProto->getItemWearing() == -1)
			return false;

		// ���� ������ �Ұ���
		if (m_wearPos != WEARING_NONE)
			return false;

		if (getFlag() & FLAG_ITEM_TRANSMOGRIFY)
			return true;
			
		// ���յ� �Ϲ� ������ �Ұ���
		if ((getFlag() & FLAG_ITEM_COMPOSITION) && (!(m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE)))
			return false;

		// ���ε� ������ �ۿ� �Ұ���
		if( getFlag() & FLAG_ITEM_SEALED )
			return false;

		return true;
	}

	bool IsLent()
	{
		if (getFlag() & FLAG_ITEM_LENT)
			return true;
		else
			return false;
	}

	bool IsBelong()
	{
		if (getFlag() & FLAG_ITEM_BELONG)
			return true;
		return false;
	}

	bool IsOriginItem() const
	{
		return m_itemProto->IsOriginItem();
	}
	int GetBelongType() const
	{
		return m_itemProto->GetBelongType();
	}
	int GetOriginIndex(int nPos) const
	{
		return m_itemProto->GetOriginIndex(nPos);
	}
	int GetOriginLevel(int nPos) const
	{
		return m_itemProto->GetOriginLevel(nPos);
	}
	int GetOriginOptionCnt() const
	{
		return m_itemProto->GetOriginOptionCnt();
	}
	int GetOriginSkillCnt() const
	{
		return m_itemProto->GetOriginSkillCnt();
	}

	bool IsRareItem() const
	{
		return m_itemProto->IsRareItem();
	}

	bool IsComposeItem() const
	{
		return m_itemProto->IsComposeItem();
	}

	void IdentifyRareOption(bool reform_ = false, unsigned int count_ = 0, int nIndex_ = 0 );


	int GetItemLevel() const;

#ifdef PREMIUM_CHAR
	int GetItemLevelForPremiumChar(int premiumType) const;
#endif

	int GetItemPlus()
	{
		if( m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && (m_itemProto->getItemSubTypeIdx() == IACCESSORY_PET || m_itemProto->getItemSubTypeIdx() == IACCESSORY_ATTACK_PET ) )
		{
			return getPlus();
		}
		else if (Is_fortune_item())
		{
			return getPlus();
		}
		else
		{
			return ((getPlus_2() << 16) & 0xffff0000) | (getPlus() & 0x0000ffff);
		}
	}

	// �ǻ�� ���� ������ ����ΰ�?
	bool CanCompositeEquipItem()
	{
		if (!IsWeaponType() && !IsArmorType())
			return false;
		if (!CanUpgrade())
			return false;

		return true;
	}

	CSocketList	m_socketList;

	bool IsJewelType() const
	{
		return m_itemProto->IsJewelType();
	}
	bool IsChaosJewelType() const
	{
		return m_itemProto->IsChaosJewelType();
	}

	bool IsStableType() const
	{
		return m_itemProto->IsStableType();
	}
	bool IsFuncType() const
	{
		return m_itemProto->IsFuncType();
	}
	bool IsSocketItem() const
	{
		return m_itemProto->IsSocketItem();
	}

public:
	int			m_OriginVar[MAX_VARIATION_COUNT];

	bool IsReformerItem() const
	{
		return m_itemProto->IsReformerItem();
	}

	void setOriginVar(int nIndex_, int value_)
	{
		if (nIndex_ < 0 || nIndex_ >= MAX_VARIATION_COUNT)
			return ;

		m_OriginVar[nIndex_]  = value_;
	}
	int getOriginVar(int nIndex_) const
	{
		if (nIndex_ < 0 || nIndex_ >= MAX_VARIATION_COUNT)
			return (100);

		return m_OriginVar[nIndex_];
	}

	void originReform(unsigned int count_,int nIndex_);

public:
	/**
	* Fortune�� �޾Ҵ��� �ȹ޾Ҵ��� �˻�
	*/
	bool Aleady_got_fortune()
	{
		if (Is_fortune_item() && getPlus() != 0)
			return true;
		return false;
	}

	/**
	* �ѹ��ǻ� fortune�� ���� �� �ִ�.
	*/
	bool Is_fortune_item() const
	{
		if (m_itemProto->getItemTypeIdx() == ITYPE_WEAR && m_itemProto->getItemSubTypeIdx() == IWEAR_SUIT)
			return true;
		return false;
	}

	bool isAllowSocketItem() const
	{
		return m_itemProto->isAllowSocketItem();
	}
	bool isProcessScroll() const
	{
		return m_itemProto->isProcessScroll();
	}

	bool isSyndicate() const
	{
		return m_itemProto->isSyndicate();
	}

	void clone(CItem& destItem);
#ifdef DURABILITY
	int getNowDurability()
	{
		return now_durability;
	}
	void setNowDurability(int dur)
	{
		now_durability = dur;
	}

	int getMaxDurability()
	{
		return max_durability;
	}
	void setMaxDurability(int dur)
	{
		max_durability = dur;
	}

#endif
	bool	m_toggle;
	bool	isToggle(){ return m_toggle ? true : false;}

	// memcpy ���� �����ϰ� �����ؾ� �ϱ⿡ ���� �Ʒ��� ��ġ ��Ų��.
	std::string m_serial;			// �ø��� ��ȣ
};

class CItemList
{
private:
	std::string a_need_item_str[MAX_MAKE_ITEM_MATERIAL];
	std::string a_need_item_count_str[MAX_MAKE_ITEM_MATERIAL];
	std::string a_rare_index_str[MAX_RARE_OPTION_ITEM];
	std::string a_rare_prob_str[MAX_RARE_OPTION_ITEM];
	std::string a_origin_variation_str[MAX_VARIATION_COUNT];

	// ��� ���Ե� ���絵 �ϸ� �ȵ�. (���� ���� ���ϵ��� ���� �ϰ�, ���Ǵ� ���� �ʾ���)
	CItemList(const CItemList&);
	CItemList& operator=(const CItemList&);

	bool checkTimerItem(CItemProto* proto);

public:
	typedef std::map<int, CItemProto*> map_t;

	CItemList();
	virtual ~CItemList();

	// ������ ����Ʈ �б�
	bool Load();

	LONGLONG calcItemCount(CItemProto* proto, LONGLONG count);

	// ������ �ε����� ������ ������Ÿ�� ���
	CItemProto* FindIndex(int idx);

	// DB �� �κ� �� �������� ����
#ifdef DURABILITY
	CItem* CreateDBItem(int idx, char wearPos, int plus, int flag, int used,
						int used_2, const char* serial, LONGLONG count, short* option
						, char socketcount, int* jewel
						, int* OriginVar, int now_dur, int max_dur
					   );
#else
	CItem* CreateDBItem(int idx, char wearPos, int plus, int flag, int used,
						int used_2, const char* serial, LONGLONG count, short* option
						, char socketcount, int* jewel
						, int* OriginVar
					   );
#endif

	CItem* CreateAutoGiveDBItem(int idx, char wearPos, int plus, int flag, int used,
								int used_2,	const char* serial, LONGLONG count, short* option
								, char socketcount, int* jewel
							   );

	// ���ο� ������ ����
	CItem* CreateItem(int idx, char wearPos, int plus, int flag, LONGLONG count);

//#ifdef DEV_GUILD_STASH
	CItem* CreateDBItem_2( int idx, char wearPos, int plus, int flag, int used, int used_2, const char* serial, LONGLONG count, short* option , const char* socket, int* itemOrigin );
//#endif //DEV_GUILD_STASH

	int				m_nCount;		// ����
	int				m_virtualIndex;	// ����
	CItemProto*		m_protoItems;	// �⺻������

	// Ư�� ������ ������Ÿ�Ե�
	CItemProto*		m_normalRefineItem;		// �Ϲ� ���ü�
	CItemProto*		m_specialRefineItem;	// ���� ���ü�
	CItemProto*		m_sTicketItem1;			// �̱۴���1 �����
	CItemProto*		m_sTicketItem2;			// �̱۴���2 �����

	// ���� �뿩�� ������ ����Ʈ
	std::set<int>	m_listLendItem;

	// ���ֿ� ������
	std::vector<CItemProto*>	m_flagload;

	// ��ȯ�� ������
	std::vector<CItemProto*>	m_flagchange;

	std::vector<CItemProto*>	m_flagGuildWar;

protected:
	boost::mutex	m_mutex_for_virtualIndex;

	int GetNextVirtualIndex();

private:
	map_t			map_;

	// Mutex to protect reload swap and pointer patching
	boost::mutex m_mutex_reload;

	// Overflow storage for new protos added during reload (indices not in original array)
	std::vector<CItemProto*> m_overflowProtos;

public:
	// Perform a safe runtime reload: load new protos, migrate all live CItem::m_itemProto
	// pointers via ref tracking, then swap in the new prototype array.
	bool ReloadSafe();
};

class CCtItemList
{
	friend class CItem;
public:
	CCtItemList()
	{
	}
	virtual ~CCtItemList()
	{
		this->_delete();
	}

	bool Load(int ctIdx);

	CItem*			GetItem(int i)
	{
		return this->ctItem[i];
	}

	CItem*			GetItem(CItem* pItem);
	int				GetCount()
	{
		return ctItem.size();
	}

private:

	std::vector<CItem*> ctItem;

	void _delete();
};

class CCatalog
{
	friend class CCtItemList;
public:
	CCatalog()
		: m_name(MAX_ITEM_NAME_LENGTH + 1)
	{
		m_index = 0;
		m_category = 0;
		m_subtype = 0;
		m_type = -1;
		m_cash = 0;
		m_mileage = 0;
		m_flag = 0;
		m_ctItemList = NULL;
		m_enable = false;
	}

	CCatalog(int index)		// ���̳ʸ� ��ġ��
		: m_name(MAX_ITEM_NAME_LENGTH + 1)
	{
		m_index = index;
		m_category = 0;
		m_subtype = 0;
		m_type = -1;
		m_cash = 0;
		m_mileage = 0;
		m_ctItemList = NULL;
		m_flag = 0;
		m_enable = false;
	}
	CCatalog(int index, const char* name, int category, int type, int subtype, int cash, int mileage, bool enable, int m_flag)
		: m_name(MAX_ITEM_NAME_LENGTH + 1)
	{
		m_index = index;
		m_name = name;
		m_category = category;
		m_subtype = subtype;
		m_type = type;
		m_cash = cash;
		m_mileage = mileage;
		m_ctItemList = NULL;
		m_flag = 0;
		m_enable = enable;
	}
	virtual ~CCatalog()
	{
		if( m_ctItemList)
			delete m_ctItemList;
		m_ctItemList = NULL;
	}

	void SetCatalog(int index, const char* name, int category, int type, int subtype, int cash, int mileage, bool enable, int flag, CCtItemList* ctItemList)
	{
		m_index = index;
		m_name = name;
		m_category = category;
		m_subtype = subtype;
		m_type = type;
		m_cash = cash;
		m_mileage = mileage;
		m_ctItemList = NULL;
		m_enable = enable;
		m_flag = flag;
		m_ctItemList = ctItemList;
		CATALOG_FALG_TO_LIMIT(flag, m_toSell);
	}
	void	SetPrice(int price)
	{
		m_cash = price;
	}
	int		GetIndex()
	{
		return m_index;
	}
	const char*	GetName()
	{
		return m_name;
	}
	int		GetCategory()
	{
		return m_category;
	}
	int		GetSubtype()
	{
		return m_subtype;
	}
	int		GetFlag()
	{
		return m_flag;
	}
	int		GetType()
	{
		return m_type;
	}
	int		GetCash()
	{
		return m_cash;
	}
	int		GetMileage()
	{
		return m_mileage;
	}
	int		GetToSell()
	{
		return m_toSell;
	}
	void	SetToSell(int toSell)
	{
		m_toSell = toSell;
	}
	int		GetLimit()
	{
		int limit;
		CATALOG_FALG_TO_LIMIT(m_flag, limit);
		return limit;
	}
	bool	GetEnable()
	{
		return m_enable;
	}
	CCtItemList* GetCtItemList()
	{
		return m_ctItemList;
	}

private:
	CCtItemList* m_ctItemList;

	int		m_index;		// īŻ�α� �ε���
	CLCString m_name;
	int		m_type;			// Ÿ��
	int		m_category;
	int		m_subtype;
	int		m_cash;			// ����
	int		m_mileage;		// ���ϸ���
	int		m_toSell;			// �Ǹ� ���� ����
	int		m_flag;
	bool	m_enable;
};

class CCatalogList
{
	friend class CCatalog;
public:
	int m_typelist[TYPE_MAX_COUNT];
	int m_typeCount;
	int m_subtypelist[SUBTYPE_MAX_COUNT];
	int m_subtypeCount;
	CCatalogList()
	{
		catalog = NULL;
		m_cCount = 0;
		m_recoveryCtid = -1;
	}
	virtual ~CCatalogList()
	{
		if (catalog)
			delete [] catalog;

		catalog = NULL;
	}
	bool Load();
	bool Reload();
	bool ReloadPrice();

	CCatalog* Find(int idx)
	{
		int i = 0;
		for(i = 0; i < m_cCount; i++)
		{
			if(this->catalog[i].GetIndex() == idx)
			{
				return &catalog[i];
			}
		}

		return NULL;
	}

	CCatalog* FindItemToCatalog(CItem* pItem);
	CCatalog* FindItemToCatalog(int itemDBIndex);

	int GetCount()
	{
		return m_cCount;
	}
	CCatalog* getCatalog(int index)
	{
		return &catalog[index] ? &catalog[index] : NULL;
	}

	// ���� �� ü�� ȸ������
	int m_recoveryCtid;
private:
	CCatalog* catalog;

	int m_cCount;
};

struct stComposeData
{
	int Material_index;
	int Material_count;
	int need_nas;
	int prob;
	int result_item_index;
	int enable;

	stComposeData()
	{
		Material_index = 0;
		Material_count = 0;
		need_nas = 0;
		prob = 0;
		result_item_index = 0;
		enable = 0;
	}
};

class ComposeItem
{
private:
	typedef std::map<int/*mat_item_index*/, stComposeData*> COMPOSE_MAP;
	COMPOSE_MAP _map;
	int m_item_load_count;

public:
	ComposeItem();
	~ComposeItem();
	static ComposeItem* instance();

	void load();
	void init();
	stComposeData* find(int mat_item_index);

	stComposeData* data;
};

bool do_UseGpsItem(CItem* item, CPC* pc);
bool do_UsePvPProtect(CItem* item, CPC* ch);

#endif // !defined(AFX_ITEM_H__91327288_815B_4A26_AF31_0F9098AEECF3__INCLUDED_)
//
