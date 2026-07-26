// Item.cpp: implementation of the CItem class.
//
//////////////////////////////////////////////////////////////////////

#include <boost/format.hpp>
#include "stdhdrs.h"

#include "Item.h"
#include "../ShareLib/DBCmd.h"
#include "Server.h"
#include "Log.h"
#include "Exp.h"
#include "../ShareLib/packetType/ptype_char_status.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItem::CItem()
{
	//////////////////
	// DB ���� ����
	m_itemProto = NULL;

	/////////////////////
	// �κ��丮 ��ġ ����
	m_tab_idx = -1;								// ��
	m_invenIndex = -1;							// �κ� �ε���

	//////////////
	// ������ �Ӽ�
	m_virualIndex = -1;								// ���� �ε���
	m_dbIndex = -1;								// DB �ε���
	m_wearPos = -1;								// ���� ���� ����
	m_plus = 0;									// + ��ġ
	m_flag = 0;									// �Ӽ�
	m_count = 0;								// ����
	m_used = -1;								// ������
	m_used_2 = -1;								// ���� �ð�

	////////////
	// ��Ÿ �Ӽ�
	m_pArea = NULL;
	m_pos = CPos(0, 0, 0, 0, 0);				// ��ǥ
	m_cellX = NO_CELL;							// �� ��ġ
	m_cellZ = NO_CELL;
	m_pCellPrev = NULL;							// �� ��ũ�� ����Ʈ
	m_pCellNext = NULL;

	m_groundPulse = 0;							// �������� ������ �ð� ����
	m_preferenceIndex = -1;						// �� �����ۿ� �켱���� �ִ� pc�� �ε��� ���� ������ -1

	m_nOption = 0;								// ������ �ɼ� ��

	m_nCompositeItem = -1;

	m_pRareOptionProto = NULL;
	m_nRareOptionIndex = 0;
	m_nRareOptionBit = 0;

	m_plus2 = 0;
	m_pSetItemProto = 0;
	m_nSetWearCnt = 0;
	m_nSetOption = 0;
	m_MercenaryIndex = -1;;	// ��ȯ�� ���� �뺴�� index;
	memset(m_OriginVar, 0, sizeof(int) * MAX_VARIATION_COUNT);

#ifdef DURABILITY
	now_durability = 0;
	max_durability = 0;
#endif
	m_toggle = false;
}

bool CItemList::ReloadSafe()
{
	// Phase 1: Load new prototypes from DB into a fresh array (no locks needed)
	CDBCmd DBItem;
	DBItem.Init(&gserver->m_dbdata);

	std::string sql = "SELECT * FROM t_item WHERE a_enable=1 ORDER BY a_index";
	DBItem.SetQuery(sql);
	if (!DBItem.Open())
		return false;

	if (DBItem.GetRecordCount() == 0)
	{
		LOG_ERROR("item db is empty.");
		return false;
	}

	int newCount = DBItem.GetRecordCount();
	CItemProto* newProtos = new CItemProto[newCount];
	map_t newMap;

	// Temporary auxiliary lists built from new protos
	std::vector<CItemProto*> newFlagload;
	std::vector<CItemProto*> newFlagchange;
	std::vector<CItemProto*> newFlagGuildWar;
	std::set<int> newListLendItem;
	CItemProto* newNormalRefineItem = NULL;
	CItemProto* newSpecialRefineItem = NULL;
	CItemProto* newSTicketItem1 = NULL;
	CItemProto* newSTicketItem2 = NULL;

	newFlagload.reserve(newCount);
	newFlagchange.reserve(newCount);
	newFlagGuildWar.reserve(newCount);

	int check_flag = ITEM_FLAG_RARE | ITEM_FLAG_COUNT;
	int ridx = 0;
	while (DBItem.MoveNext())
	{
		CItemProto* pItemProto = &newProtos[ridx];
		LONGLONG nFlag;

		DBItem.GetRec("a_flag", nFlag);
		if ((nFlag & check_flag) == check_flag)
			continue;

		pItemProto->m_flag = nFlag;

		DBItem.GetRec("a_index",		pItemProto->m_index);
		DBItem.GetRec("a_type_idx",		pItemProto->m_typeIdx);
		DBItem.GetRec("a_subtype_idx",	pItemProto->m_subtypeIdx);
		DBItem.GetRec(ITEM_NAME_FIELD,	pItemProto->m_name, true);
		DBItem.GetRec("a_job_flag",		pItemProto->m_jobFlag);
		DBItem.GetRec("a_num_0",		pItemProto->m_num0);
		DBItem.GetRec("a_num_1",		pItemProto->m_num1);
		DBItem.GetRec("a_num_2",		pItemProto->m_num2);
		DBItem.GetRec("a_num_3",		pItemProto->m_num3);
		DBItem.GetRec("a_num_4",		pItemProto->m_num4);
		DBItem.GetRec("a_weight",		pItemProto->m_stackcount);
		DBItem.GetRec("a_level",		pItemProto->m_level);
		DBItem.GetRec("a_level2",		pItemProto->m_level2);
		DBItem.GetRec(ITEM_PRICE_FIELD,	pItemProto->m_price);
		DBItem.GetRec("a_wearing",		pItemProto->m_wearing);
		DBItem.GetRec("a_max_use",		pItemProto->m_maxUse);
		DBItem.GetRec("a_fame",			pItemProto->m_fame);

		DBItem.GetRec("a_set_0",		pItemProto->m_set0);
		DBItem.GetRec("a_set_1",		pItemProto->m_set1);
		DBItem.GetRec("a_set_2",		pItemProto->m_set2);
		DBItem.GetRec("a_set_3",		pItemProto->m_set3);
		DBItem.GetRec("a_set_4",		pItemProto->m_set4);
		DBItem.GetRec("a_grade",		pItemProto->m_grade);

		for (int i = 0; i < MAX_MAKE_ITEM_MATERIAL; i++)
		{
			DBItem.GetRec(a_need_item_str[i].c_str(), pItemProto->m_materialIndex[i]);
			DBItem.GetRec(a_need_item_count_str[i].c_str(), pItemProto->m_materialCount[i]);
		}

		DBItem.GetRec("a_need_sskill",			pItemProto->m_needSSkillIndex);
		DBItem.GetRec("a_need_sskill_level",	pItemProto->m_needSSkillLevel);
		DBItem.GetRec("a_need_sskill2",			pItemProto->m_needSSkillIndex2);
		DBItem.GetRec("a_need_sskill_level2",	pItemProto->m_needSSkillLevel2);

		for (int i = 0; i < MAX_RARE_OPTION_ITEM; i++)
		{
			if (!DBItem.GetRec(a_rare_index_str[i].c_str(), pItemProto->m_nRareIndex[i]))
			{
				delete[] newProtos;
				return false;
			}
			if (!DBItem.GetRec(a_rare_prob_str[i].c_str(), pItemProto->m_nRareProb[i]))
			{
				delete[] newProtos;
				return false;
			}
		}
		unsigned char val;
		for (int i = 0; i < MAX_VARIATION_COUNT; i++)
		{
			if (!DBItem.GetRec(a_origin_variation_str[i].c_str(), val))
			{
				delete[] newProtos;
				return false;
			}
			pItemProto->m_MaxOriginVariation[i] = (int)(val * 10);
		}

		DBItem.GetRec("a_rvr_value",	pItemProto->m_rvr_type);
		DBItem.GetRec("a_rvr_grade",	pItemProto->m_rvr_grade);
#ifdef DURABILITY
		DBItem.GetRec("a_durability",	pItemProto->m_durability);
#endif
		DBItem.GetRec("a_castle_war",	pItemProto->m_castle_war);

		if (pItemProto->m_castle_war != 0)
			newFlagGuildWar.push_back(pItemProto);

		// Special item pointers
		switch (pItemProto->m_index)
		{
		case 84:  newNormalRefineItem = pItemProto; break;
		case 85:  newSpecialRefineItem = pItemProto; break;
		case 141: newSTicketItem2 = pItemProto; break;
		case 142: newSTicketItem1 = pItemProto; break;
		default: break;
		}

		if (pItemProto->getItemFlag() & ITEM_FLAG_LORD)
			newFlagload.push_back(pItemProto);
		if (pItemProto->getItemFlag() & ITEM_FLAG_CHANGE)
			newFlagchange.push_back(pItemProto);

		// lent items
		static const int nNormalWeaponFlag = ITEM_FLAG_LENT;
		if (pItemProto->m_typeIdx == ITYPE_WEAPON && (pItemProto->m_flag & nNormalWeaponFlag) == nNormalWeaponFlag && pItemProto->m_price > 0)
		{
			switch (pItemProto->m_subtypeIdx)
			{
				case IWEAPON_NIGHT: case IWEAPON_CROSSBOW: case IWEAPON_STAFF: case IWEAPON_BIGSWORD:
				case IWEAPON_AXE: case IWEAPON_SHORTSTAFF: case IWEAPON_BOW: case IWEAPON_SHORTGUM:
				case IWEAPON_TWOSWORD: case IWEAPON_WAND: case IWEAPON_SCYTHE: case IWEAPON_POLEARM:
					switch (pItemProto->m_level)
					{
						case 37: case 41: case 45: case 49: case 53: case 57: case 61: case 65:
							newListLendItem.insert(pItemProto->m_index);
							break;
						default: break;
					}
					break;
				default: break;
			}
		}

		// Compute derived boolean flags
		{
			pItemProto->pre_origin_option_count_ = 0;
			for (int i = 0; i < MAX_ORIGIN_OPTION; i++)
			{
				if (pItemProto->GetOriginIndex(i) > -1)
					++pItemProto->pre_origin_option_count_;
			}
		}
		{
			pItemProto->pre_origin_skill_count_ = 0;
			for (int i = MAX_ORIGIN_OPTION; i < MAX_ORIGIN; i++)
			{
				if (pItemProto->GetOriginIndex(i) > -1)
					++pItemProto->pre_origin_skill_count_;
			}
		}
		{
			pItemProto->is_range_weapon_ = false;
			if (pItemProto->getItemTypeIdx() == ITYPE_WEAPON)
			{
				switch (pItemProto->getItemSubTypeIdx())
				{
				case IWEAPON_CROSSBOW:
				case IWEAPON_BOW:
					pItemProto->is_range_weapon_ = true;
					break;
				}
			}
		}
		{
			pItemProto->is_magic_weapon_ = false;
			if (pItemProto->getItemTypeIdx() == ITYPE_WEAPON)
			{
				switch (pItemProto->getItemSubTypeIdx())
				{
				case IWEAPON_SHORTSTAFF:
				case IWEAPON_STAFF:
				case IWEAPON_WAND:
				case IWEAPON_SCYTHE:
				case IWEAPON_POLEARM:
				case IWEAPON_SOUL:
					pItemProto->is_magic_weapon_ = true;
					break;
				}
			}
		}
		{
			pItemProto->get_using_stat_ = -1;
			if (pItemProto->getItemTypeIdx() == ITYPE_WEAPON)
			{
				switch (pItemProto->getItemSubTypeIdx())
				{
				case IWEAPON_CROSSBOW:
				case IWEAPON_BOW:
				case IWEAPON_SHORTGUM:
					pItemProto->get_using_stat_ = USING_DEX;
					break;
				case IWEAPON_SOUL:
				case IWEAPON_WAND:
				case IWEAPON_POLEARM:
				case IWEAPON_SCYTHE:
				case IWEAPON_SHORTSTAFF:
				case IWEAPON_STAFF:
					pItemProto->get_using_stat_ = USING_INT;
					break;
				default:
					pItemProto->get_using_stat_ = USING_STR;
					break;
				}
			}
		}
		{
			pItemProto->is_weapon_type_ = false;
			if (pItemProto->getItemTypeIdx() == ITYPE_WEAPON)
			{
				switch (pItemProto->getItemSubTypeIdx())
				{
				case IWEAPON_NIGHT:
				case IWEAPON_CROSSBOW:
				case IWEAPON_STAFF:
				case IWEAPON_BIGSWORD:
				case IWEAPON_AXE:
				case IWEAPON_SHORTSTAFF:
				case IWEAPON_BOW:
				case IWEAPON_SHORTGUM:
				case IWEAPON_TWOSWORD:
				case IWEAPON_WAND:
				case IWEAPON_SCYTHE:
				case IWEAPON_POLEARM:
				case IWEAPON_SOUL:
					pItemProto->is_weapon_type_ = true;
					break;
				}
			}
		}
		{
			pItemProto->is_armor_type_ = false;
			if (pItemProto->getItemTypeIdx() == ITYPE_WEAR)
			{
				switch (pItemProto->getItemSubTypeIdx())
				{
				case IWEAR_HELMET:
				case IWEAR_ARMOR:
				case IWEAR_PANTS:
				case IWEAR_GLOVE:
				case IWEAR_SHOES:
				case IWEAR_SHIELD:
				case IWEAR_BACKWING:
					pItemProto->is_armor_type_ = true;
					break;
				}
			}
		}

		pItemProto->is_accessary_ = (pItemProto->getItemTypeIdx() == ITYPE_ACCESSORY && pItemProto->getItemSubTypeIdx() != IACCESSORY_PET );
		pItemProto->is_pet_ = (pItemProto->getItemTypeIdx() == ITYPE_ACCESSORY && pItemProto->getItemSubTypeIdx() == IACCESSORY_PET );
		pItemProto->is_apet_ = (pItemProto->getItemTypeIdx() == ITYPE_ACCESSORY && pItemProto->getItemSubTypeIdx() == IACCESSORY_ATTACK_PET );

		{
			pItemProto->is_upgrade_rune_ = false;
			if (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_UPGRADE)
			{
				switch (pItemProto->getItemNum0())
				{
				case IETC_UPGRADE_PURITY_RUNE:
				case IETC_UPGRADE_DEVIL_RUNE:
				case IETC_UPGRADE_CHAOS_RUNE:
				case IETC_UPGRADE_SUPER_RUNE:
				case IETC_UPGRADE_LUCKY_RUNE:
				case IETC_UPGRADE_LETSPLAY_RUNE:
				case IETC_PVP_RUNE:
					pItemProto->is_upgrade_rune_ = true;
					break;
				}
			}
		}

		pItemProto->is_jewel_type_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_JEWEL );
		pItemProto->is_chaos_jewel_type_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_CHAOSJEWEL);
		pItemProto->is_stable_type_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_STABILIZER );
		pItemProto->is_func_type_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_FUNCTIONS );
		pItemProto->is_reformer_item_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_REFORMER);

		if(pItemProto->getItemTypeIdx() == ITYPE_WEAPON || pItemProto->getItemTypeIdx() == ITYPE_WEAR)
		{
			pItemProto->is_allow_socket = true;
		}
		else if(pItemProto->getItemTypeIdx() == ITYPE_ACCESSORY)
		{
			switch(pItemProto->getItemSubTypeIdx())
			{
			case IACCESSORY_CHARM:
			case IACCESSORY_MAGICSTONE:
			case IACCESSORY_LIGHTSTONE:
			case IACCESSORY_EARING:
			case IACCESSORY_RING:
			case IACCESSORY_NECKLACE:
				pItemProto->is_allow_socket = true;
				break;
			}
		}

		{
			pItemProto->is_socket_type_ = true;
			if( !(pItemProto->getItemFlag() & ITEM_FLAG_SOCKET) )
				pItemProto->is_socket_type_ = false;
			if (pItemProto->isAllowSocketItem() == false)
				pItemProto->is_socket_type_ = false;
			if ((pItemProto->getItemTypeIdx() == ITYPE_WEAPON) &&
					 (pItemProto->getItemSubTypeIdx() == IWEAPON_MINING || pItemProto->getItemSubTypeIdx() == IWEAPON_GATHERING || pItemProto->getItemSubTypeIdx() == IWEAPON_CHARGE))
				pItemProto->is_socket_type_ = false;
			if (pItemProto->getItemJobFlag() & (1<<JOB_APET))
				pItemProto->is_socket_type_ = false;
			if (pItemProto->getItemFlag() & FLAG_ITEM_TRANSMOGRIFY || pItemProto->getItemFlag() & ITEM_FLAG_COMPOSITE || pItemProto->getItemFlag() & ITEM_FLAG_COSTUME2 || pItemProto->getItemFlag() & ITEM_FLAG_LORD)
				pItemProto->is_socket_type_ = false;
		}

		pItemProto->is_allow_socket = (pItemProto->getItemTypeIdx() == ITYPE_WEAPON || pItemProto->getItemTypeIdx() == ITYPE_WEAR);
		pItemProto->is_process_scroll_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_PROCESS_SCROLL);

		pItemProto->is_rebirth_item_ = false;
		switch (pItemProto->getItemIndex())
		{
		case 846:
		case 2667:
		case 3218:
		case 4933:
		case 5958:
		case 7056:
		case 9194:
		case 9195:
		case 9196:
			pItemProto->is_rebirth_item_ = true;
			break;
		}

		switch(pItemProto->getItemIndex())
		{
		case 6252:
		case 6253:
		case 6254:
		case 6255:
			pItemProto->is_monster_card_ = true;
			break;
		default:
			pItemProto->is_monster_card_ = false;
			break;
		}

		pItemProto->is_rvr_not_use_ = false;
		switch(pItemProto->getItemIndex())
		{
		case 2407:
		case 2408:
		case 2500:
		case 2609:
		case 5018:
		case 5019:
		case 47:
		case 858:
		case 857:
		case 1298:
		case 1299:
		case 1300:
		case 1413:
		case 1415:
		case 2945:
		case 2946:
		case 6252:
		case 6253:
		case 6254:
		case 6255:
		case 6805:
		case 6985:
		case 6986:
		case 6987:
			pItemProto->is_rvr_not_use_ = true;
			break;
		default:
			pItemProto->is_rvr_not_use_ = false;
			break;
		}

		if( pItemProto->getItemTypeIdx() == ITYPE_ONCE && pItemProto->getItemSubTypeIdx() == IONCE_WARP
				|| pItemProto->getItemTypeIdx() == ITYPE_ONCE && pItemProto->getItemSubTypeIdx() == IONCE_SUMMON
				|| pItemProto->getItemTypeIdx() == ITYPE_ACCESSORY && pItemProto->getItemSubTypeIdx() == IACCESSORY_PET
				|| pItemProto->getItemTypeIdx() == ITYPE_ACCESSORY && pItemProto->getItemSubTypeIdx() == IACCESSORY_ATTACK_PET
				|| pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_MONSTER_MERCENARY_CARD
		  )
		{
			pItemProto->is_useinwarzone_ = false;
		}
		else
		{
			pItemProto->is_useinwarzone_ = true;
		}

		pItemProto->is_rvr_jewel_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_RVR_JEWEL) ? true : false;
		pItemProto->is_timer_ = checkTimerItem(pItemProto);
		pItemProto->is_syndicate_ = (pItemProto->getItemRvRType() > 0) ? true : false;
		pItemProto->is_gps_ = (pItemProto->getItemTypeIdx() == ITYPE_ONCE && pItemProto->getItemSubTypeIdx() == IONCE_GPS) ? true : false;
		pItemProto->is_questGive = (pItemProto->getItemFlag() & ITEM_FLAG_QUESTGIVE) ? true : false;

		newMap[pItemProto->m_index] = pItemProto;
		++ridx;
	}
	int actualNewCount = ridx;

	// Phase 2: Lock, migrate all live CItem* pointers from old protos to new protos, then swap
	{
		boost::mutex::scoped_lock lock(m_mutex_reload);

		// For each old proto, take its ref set and re-point each CItem to the matching new proto
		int migratedItems = 0;
		int orphanedItems = 0;
		for (int i = 0; i < m_nCount; ++i)
		{
			CItemProto* oldProto = &m_protoItems[i];
			std::set<CItem*> refs = oldProto->takeAllRefs();
			if (refs.empty())
				continue;

			// Find matching new proto by item index
			map_t::iterator it = newMap.find(oldProto->m_index);
			if (it != newMap.end())
			{
				CItemProto* matchingNew = it->second;
				for (std::set<CItem*>::iterator ri = refs.begin(); ri != refs.end(); ++ri)
				{
					CItem* item = *ri;
					// Direct assignment: old ref already cleared by takeAllRefs
					item->m_itemProto = matchingNew;
					matchingNew->addRef(item);
					++migratedItems;
				}
			}
			else
			{
				// Proto removed from DB — items become orphaned, keep pointing to old (will be in overflow)
				for (std::set<CItem*>::iterator ri = refs.begin(); ri != refs.end(); ++ri)
				{
					CItem* item = *ri;
					// Re-add ref back to old proto since we took it; old proto will live in overflow
					oldProto->addRef(item);
					++orphanedItems;
				}
			}
		}

		// Also migrate refs from any previous overflow protos
		for (size_t oi = 0; oi < m_overflowProtos.size(); ++oi)
		{
			CItemProto* oldOverflow = m_overflowProtos[oi];
			std::set<CItem*> refs = oldOverflow->takeAllRefs();
			if (refs.empty())
			{
				delete oldOverflow;
				continue;
			}

			map_t::iterator it = newMap.find(oldOverflow->m_index);
			if (it != newMap.end())
			{
				CItemProto* matchingNew = it->second;
				for (std::set<CItem*>::iterator ri = refs.begin(); ri != refs.end(); ++ri)
				{
					CItem* item = *ri;
					item->m_itemProto = matchingNew;
					matchingNew->addRef(item);
					++migratedItems;
				}
				delete oldOverflow;
			}
			else
			{
				// Still orphaned — keep in overflow
				for (std::set<CItem*>::iterator ri = refs.begin(); ri != refs.end(); ++ri)
				{
					oldOverflow->addRef(*ri);
					++orphanedItems;
				}
			}
		}
		m_overflowProtos.clear();

		// Check if any old protos still have refs (orphaned items whose proto was removed)
		// Move them to overflow so they stay alive
		for (int i = 0; i < m_nCount; ++i)
		{
			CItemProto* oldProto = &m_protoItems[i];
			if (oldProto->getRefCount() > 0)
			{
				// This proto still has live items referencing it — can't delete the old array yet
				// Copy it to a heap-allocated proto and re-point items
				CItemProto* saved = new CItemProto(*oldProto);
				std::set<CItem*> refs = oldProto->takeAllRefs();
				for (std::set<CItem*>::iterator ri = refs.begin(); ri != refs.end(); ++ri)
				{
					CItem* item = *ri;
					item->m_itemProto = saved;
					saved->addRef(item);
				}
				m_overflowProtos.push_back(saved);
			}
		}

		// Phase 3: Swap in the new data
		CItemProto* oldProtos = m_protoItems;

		m_protoItems = newProtos;
		m_nCount = actualNewCount;
		map_.swap(newMap);

		m_flagload.swap(newFlagload);
		m_flagchange.swap(newFlagchange);
		m_flagGuildWar.swap(newFlagGuildWar);
		m_listLendItem.swap(newListLendItem);
		m_normalRefineItem = newNormalRefineItem;
		m_specialRefineItem = newSpecialRefineItem;
		m_sTicketItem1 = newSTicketItem1;
		m_sTicketItem2 = newSTicketItem2;

		// Delete old array — safe because all refs have been migrated or saved to overflow
		delete[] oldProtos;

		GAMELOG << init("RELOAD_ITEM") << "Migrated " << migratedItems << " items, orphaned " << orphanedItems << " items, overflow " << (int)m_overflowProtos.size() << end;
	}

	return true;
}

CItem::~CItem()
{
	if (m_itemProto)
		m_itemProto->removeRef(this);
}


void CItem::IdentifyRareOption(bool reform_, unsigned int count_, int nIndex_)
{
	if (m_nOption && reform_ == false)
		return ;

	int nRandom = GetRandom(1, 10000);
	int i;
	for (i = 0; i < MAX_RARE_OPTION_ITEM; i++)
	{
		if (m_itemProto->getItemRareIndex(i) > 0)
		{
			if (nRandom <= m_itemProto->getItemRareProb(i))
			{
				const CRareOptionProto* pRareProto = gserver->m_rareOptionList.Find(m_itemProto->getItemRareIndex(i));
				if (pRareProto)
				{
					int nRareIndex = pRareProto->GetIndex();
					int nRareBit = 0;
					int j;
					for (j = 0; j < MAX_RARE_OPTION_SETTING; j++)
					{
						const RAREOPTIONDATA* rod = pRareProto->GetData(j);
						if (rod && rod->optiontype != -1)
						{
							int finalProb = (10 * count_) + rod->optionprob;
							if (nIndex_ == 9005)
							finalProb = (10 * count_) + rod->optionprob;
							else if (nIndex_ == 12293)
							finalProb = (20 * count_) + rod->optionprob;
							if (finalProb > 10000)
								finalProb = 10000;
							if (GetRandom(1, 10000) <= finalProb)
							{
								nRareBit |= rod->rarebit;
							}
						}
					}

					m_nOption = 2;
					m_option[0].GetDBValue((short)nRareIndex);
					m_option[1].GetDBValue((short)nRareBit);
					m_pRareOptionProto = pRareProto;
					m_nRareOptionIndex = nRareIndex;
					m_nRareOptionBit = nRareBit;
					return ;
				}
			}
			nRandom -= m_itemProto->getItemRareProb(i);
		}
	}
}

#ifdef PREMIUM_CHAR
//XX - �����̾�ĳ���� : ��� ��� 3���� ���� �ۿ�
int CItem::GetItemLevelForPremiumChar(int premiumType) const
{
	int get_level = this->GetItemLevel();
	int pre_level = m_itemProto->GetItemProtoLevel();

	if (premiumType > 0)
	{
		pre_level -= 3;
	}

	if (pre_level < 1)
		pre_level = 1;

	return (get_level < pre_level) ? get_level : pre_level;
}
#endif

int CItem::GetItemLevel() const
{
	int nItemLevel = m_itemProto->GetItemProtoLevel();
	int i;

	if (m_nOption == 0 && !IsOriginItem())
	{
		if(IsSocketItem() && m_socketList.GetJewelOptionAt(0) && m_socketList.GetJewelOptionAt(0)->m_type == OPTION_DOWN_LIMITLEVEL)
		{
			nItemLevel -= m_socketList.GetJewelOptionAt(0)->m_value;
		}

		if (nItemLevel < 1)
			nItemLevel = 1;

		return nItemLevel;
	}
	#ifdef OPAL_MINUS_11132021
	if (IsOriginItem() && m_itemProto->getItemFlag() & FLAG_ITEM_OPAL_MINUS_USED)
	{
		nItemLevel -= 10;

		if (nItemLevel < 1)
			nItemLevel = 1;

		return nItemLevel;
	}
	#endif
	if (IsRareItem())
	{
		for (i = 0; i < MAX_RARE_OPTION_SETTING; i++)
		{
			const RAREOPTIONDATA* rod = m_pRareOptionProto->GetData(i);
			if (m_nRareOptionBit & rod->rarebit)
			{
				switch (rod->optiontype)
				{
				case OPTION_DOWN_LIMITLEVEL:
					if (m_itemProto->GetItemProtoLevel() - rod->optionval < nItemLevel)
						nItemLevel = m_itemProto->GetItemProtoLevel() - rod->optionval;
					break;
				default:
					break;
				}
			}
		}
	}
	else if (IsOriginItem())
	{
		for (i = 0; i < MAX_ORIGIN_OPTION; i++)
		{
			switch (m_itemProto->GetOriginIndex(i))
			{
			case OPTION_DOWN_LIMITLEVEL:
				{
					COptionProto * pOptionProto = gserver->m_optionProtoList.FindProto(m_itemProto->GetOriginIndex(i));
					int nLevel = m_itemProto->GetOriginLevel(i);
					int nValue = 0;
					if (pOptionProto && pOptionProto->m_levelValue[nLevel - 1])
					{
						nValue = pOptionProto->m_levelValue[nLevel -1];
					}

					if (m_itemProto->GetItemProtoLevel() - nValue < nItemLevel)
						nItemLevel = m_itemProto->GetItemProtoLevel() - nValue;
				}
				break;
			default:
				break;
			}
		}
	}
	else
	{
		for (i = 0; i < MAX_WEAPON_OPTION; i++)
		{
			if (m_option[i].m_level <= 0)
				continue;
			switch (m_option[i].m_type)
			{
			case OPTION_DOWN_LIMITLEVEL:
				if (m_itemProto->GetItemProtoLevel() - m_option[i].m_value < nItemLevel)
					nItemLevel = m_itemProto->GetItemProtoLevel() - m_option[i].m_value;
				break;
			default:
				break;
			}
		}
	}

	if(IsSocketItem() && m_socketList.GetJewelOptionAt(0) && m_socketList.GetJewelOptionAt(0)->m_type == OPTION_DOWN_LIMITLEVEL)
	{
		nItemLevel -= m_socketList.GetJewelOptionAt(0)->m_value;
	}

	if (nItemLevel < 1)
		nItemLevel = 1;

	return nItemLevel;
}

CItemProto::CItemProto()
{
	m_index = -1;
	m_typeIdx = -1;
	m_subtypeIdx = -1;
	m_jobFlag = 0;
	m_flag = 0;
	m_maxUse = -1;
	m_fame = -1;

	m_num0 = 0;
	m_num1 = 0;
	m_num2 = 0;
	m_num3 = 0;
	m_num4 = 0;
	m_stackcount = 0;
	m_level = 0;
	m_level2 = 0;
	m_price = 0;
	m_wearing = -1;

	memset(m_materialIndex, -1, sizeof(int) * MAX_MAKE_ITEM_MATERIAL);
	memset(m_materialCount, 0, sizeof(int) * MAX_MAKE_ITEM_MATERIAL);

	m_needSSkillIndex = -1;
	m_needSSkillLevel = 0;

	m_needSSkillIndex2 = -1;
	m_needSSkillLevel2 = 0;

	m_set4 = 0;
	m_set0 = -1;
	memset(m_MaxOriginVariation, 0, sizeof(int) * MAX_VARIATION_COUNT);
	is_syndicate_ = false;
}

CItemProto::CItemProto(const CItemProto& other)
	: m_name(other.m_name)
{
	m_index = other.m_index;
	m_typeIdx = other.m_typeIdx;
	m_subtypeIdx = other.m_subtypeIdx;
	m_jobFlag = other.m_jobFlag;
	m_flag = other.m_flag;
	m_maxUse = other.m_maxUse;
	m_fame = other.m_fame;
	m_num0 = other.m_num0;
	m_num1 = other.m_num1;
	m_num2 = other.m_num2;
	m_num3 = other.m_num3;
	m_num4 = other.m_num4;
	m_set0 = other.m_set0;
	m_set1 = other.m_set1;
	m_set2 = other.m_set2;
	m_set3 = other.m_set3;
	m_set4 = other.m_set4;
	m_grade = other.m_grade;
	m_stackcount = other.m_stackcount;
	m_price = other.m_price;
	m_wearing = other.m_wearing;
	memcpy(m_materialIndex, other.m_materialIndex, sizeof(m_materialIndex));
	memcpy(m_materialCount, other.m_materialCount, sizeof(m_materialCount));
	m_needSSkillIndex = other.m_needSSkillIndex;
	m_needSSkillLevel = other.m_needSSkillLevel;
	m_needSSkillIndex2 = other.m_needSSkillIndex2;
	m_needSSkillLevel2 = other.m_needSSkillLevel2;
	memcpy(m_nRareIndex, other.m_nRareIndex, sizeof(m_nRareIndex));
	memcpy(m_nRareProb, other.m_nRareProb, sizeof(m_nRareProb));
	m_level = other.m_level;
	m_level2 = other.m_level2;
	memcpy(m_MaxOriginVariation, other.m_MaxOriginVariation, sizeof(m_MaxOriginVariation));
	m_rvr_type = other.m_rvr_type;
	m_rvr_grade = other.m_rvr_grade;
#ifdef DURABILITY
	m_durability = other.m_durability;
#endif
	m_castle_war = other.m_castle_war;
	pre_origin_option_count_ = other.pre_origin_option_count_;
	pre_origin_skill_count_ = other.pre_origin_skill_count_;
	is_range_weapon_ = other.is_range_weapon_;
	is_magic_weapon_ = other.is_magic_weapon_;
	get_using_stat_ = other.get_using_stat_;
	is_weapon_type_ = other.is_weapon_type_;
	is_armor_type_ = other.is_armor_type_;
	is_accessary_ = other.is_accessary_;
	is_pet_ = other.is_pet_;
	is_apet_ = other.is_apet_;
	is_upgrade_rune_ = other.is_upgrade_rune_;
	is_jewel_type_ = other.is_jewel_type_;
	is_chaos_jewel_type_ = other.is_chaos_jewel_type_;
	is_stable_type_ = other.is_stable_type_;
	is_func_type_ = other.is_func_type_;
	is_socket_type_ = other.is_socket_type_;
	is_reformer_item_ = other.is_reformer_item_;
	is_allow_socket = other.is_allow_socket;
	is_process_scroll_ = other.is_process_scroll_;
	is_rebirth_item_ = other.is_rebirth_item_;
	is_monster_card_ = other.is_monster_card_;
	is_rvr_not_use_ = other.is_rvr_not_use_;
	is_syndicate_ = other.is_syndicate_;
	is_useinwarzone_ = other.is_useinwarzone_;
	is_timer_ = other.is_timer_;
	is_rvr_jewel_ = other.is_rvr_jewel_;
	is_gps_ = other.is_gps_;
	is_questGive = other.is_questGive;
	// m_refMutex is default-initialized (fresh mutex)
	// m_refItems starts empty (no refs copied — this is a new proto)
	// m_affinityList is not copied (managed separately)
}

CItemProto::~CItemProto()
{
}

//////////////////////////////////////////////////////////////////////
// CItemList Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemList::CItemList()
{
	m_protoItems = NULL;
	m_virtualIndex = 1;
	m_nCount = 0;

	m_normalRefineItem = NULL;
	m_specialRefineItem = NULL;

	m_sTicketItem1 = NULL;
	m_sTicketItem2 = NULL;

	for (int i = 0; i < MAX_MAKE_ITEM_MATERIAL; ++i)
	{
		a_need_item_str[i] = boost::str(boost::format("a_need_item%d") % i);
		a_need_item_count_str[i] = boost::str(boost::format("a_need_item_count%d") % i);
	}

	for (int i = 0; i < MAX_RARE_OPTION_ITEM; i++)
	{
		a_rare_index_str[i] = boost::str(boost::format("a_rare_index_%d") % i);
		a_rare_prob_str[i] = boost::str(boost::format("a_rare_prob_%d") % i);
	}

	for (int i = 0; i < MAX_VARIATION_COUNT; i++)
	{
		a_origin_variation_str[i] = boost::str(boost::format("a_origin_variation%d") % (i + 1));
	}
}

CItemList::~CItemList()
{
	if (m_protoItems)
		delete [] m_protoItems;

	for (size_t i = 0; i < m_overflowProtos.size(); ++i)
		delete m_overflowProtos[i];
	m_overflowProtos.clear();

	m_protoItems = NULL;
	m_nCount = 0;
}

bool CItemList::Load()
{
	bool bRet = true;

	CDBCmd DBItem;
	DBItem.Init(&gserver->m_dbdata);

	std::string sql = "SELECT * FROM t_item WHERE a_enable=1 ORDER BY a_index";

	DBItem.SetQuery(sql);
	if (!DBItem.Open())
		return false;

    if (DBItem.GetRecordCount() == 0)
	{
		LOG_ERROR("item db is empty.");
		return false;
	}
    // Clear previous loaded data to avoid duplicates when reloading at runtime.
    if (m_protoItems)
    {
        // clear maps/vectors that reference proto pointers first
        map_.clear();
        m_flagload.clear();
        m_flagchange.clear();
        m_flagGuildWar.clear();
        m_listLendItem.clear();

        // delete previous prototypes to avoid leaking memory on reload
        delete [] m_protoItems;
        m_protoItems = NULL;
        m_nCount = 0;

        m_normalRefineItem = NULL;
        m_specialRefineItem = NULL;
        m_sTicketItem1 = NULL;
        m_sTicketItem2 = NULL;
    }

    m_nCount = DBItem.GetRecordCount();
    m_protoItems = new CItemProto[m_nCount];
	m_flagload.reserve(DBItem.GetRecordCount());
	m_flagchange.reserve(DBItem.GetRecordCount());
	m_flagGuildWar.reserve(DBItem.GetRecordCount());

	int ridx = 0;
	int check_flag = ITEM_FLAG_RARE | ITEM_FLAG_COUNT;
	while (DBItem.MoveNext())
	{
		CItemProto* pItemProto = &m_protoItems[ridx];
		LONGLONG nFlag;

		DBItem.GetRec("a_flag",			nFlag);
		if ( (nFlag & check_flag) == check_flag)
			continue ;

		pItemProto->m_flag = nFlag;

		DBItem.GetRec("a_index",		pItemProto->m_index);
		DBItem.GetRec("a_type_idx",		pItemProto->m_typeIdx);
		DBItem.GetRec("a_subtype_idx",	pItemProto->m_subtypeIdx);
		DBItem.GetRec(ITEM_NAME_FIELD,	pItemProto->m_name, true);
		DBItem.GetRec("a_job_flag",		pItemProto->m_jobFlag);
		DBItem.GetRec("a_num_0",		pItemProto->m_num0);
		DBItem.GetRec("a_num_1",		pItemProto->m_num1);
		DBItem.GetRec("a_num_2",		pItemProto->m_num2);
		DBItem.GetRec("a_num_3",		pItemProto->m_num3);
		DBItem.GetRec("a_num_4",		pItemProto->m_num4);
		DBItem.GetRec("a_weight",		pItemProto->m_stackcount);
		DBItem.GetRec("a_level",		pItemProto->m_level);
		DBItem.GetRec("a_level2",		pItemProto->m_level2);
		DBItem.GetRec(ITEM_PRICE_FIELD,	pItemProto->m_price);
		DBItem.GetRec("a_wearing",		pItemProto->m_wearing);
		DBItem.GetRec("a_max_use",		pItemProto->m_maxUse);
		DBItem.GetRec("a_fame",			pItemProto->m_fame);

		DBItem.GetRec("a_set_0",		pItemProto->m_set0);
		DBItem.GetRec("a_set_1",		pItemProto->m_set1);
		DBItem.GetRec("a_set_2",		pItemProto->m_set2);
		DBItem.GetRec("a_set_3",		pItemProto->m_set3);
		DBItem.GetRec("a_set_4",		pItemProto->m_set4);
		DBItem.GetRec("a_grade",		pItemProto->m_grade);	// �깫��Ÿ������ ���.

		for (int i = 0; i < MAX_MAKE_ITEM_MATERIAL; i++)
		{
			DBItem.GetRec(a_need_item_str[i].c_str(), pItemProto->m_materialIndex[i]);
			DBItem.GetRec(a_need_item_count_str[i].c_str(), pItemProto->m_materialCount[i]);
		}

		DBItem.GetRec("a_need_sskill",			pItemProto->m_needSSkillIndex);
		DBItem.GetRec("a_need_sskill_level",	pItemProto->m_needSSkillLevel);

		DBItem.GetRec("a_need_sskill2",			pItemProto->m_needSSkillIndex2);
		DBItem.GetRec("a_need_sskill_level2",	pItemProto->m_needSSkillLevel2);

		for (int i = 0; i < MAX_RARE_OPTION_ITEM; i++)
		{
			if (!DBItem.GetRec(a_rare_index_str[i].c_str(), pItemProto->m_nRareIndex[i]))
				return false;

			if (!DBItem.GetRec(a_rare_prob_str[i].c_str(),	pItemProto->m_nRareProb[i]))
				return false;
		}
		unsigned char val;
		for (int i = 0; i < MAX_VARIATION_COUNT; i++)
		{
			if (!DBItem.GetRec(a_origin_variation_str[i].c_str(), val))
				return false;

			pItemProto->m_MaxOriginVariation[i] = (int)(val * 10);
		}

		DBItem.GetRec("a_rvr_value", pItemProto->m_rvr_type);
		DBItem.GetRec("a_rvr_grade", pItemProto->m_rvr_grade);

#ifdef DURABILITY
		DBItem.GetRec("a_durability", pItemProto->m_durability);
#endif
		DBItem.GetRec("a_castle_war", pItemProto->m_castle_war);

		if(pItemProto->m_castle_war != 0)
		{
			m_flagGuildWar.push_back(&m_protoItems[ridx]);
		}

		// Ư�� ������ ã�� : �ε�����
		switch (pItemProto->m_index)
		{
		case 84:	// �Ϲ� ���ü�
			m_normalRefineItem = m_protoItems + ridx;
			break;

		case 85:	// ���� ���ü�
			m_specialRefineItem = m_protoItems + ridx;
			break;

		case 141:	// �̱۴���2 �����
			m_sTicketItem2 = m_protoItems + ridx;
			break;

		case 142:	// �̱۴���1 �����
			m_sTicketItem1 = m_protoItems + ridx;
			break;

		default:
			break;
		}

		// ���� �뿩�� ������ ����Ʈ �����
		// ���� Ÿ�� ��
		// ITEM_FLAG_LENT
		// ������ ���� �Ǿ� ���� ��
		// ���� 37/41/45/49/53/57/61/65
		static const int nNormalWeaponFlag = ITEM_FLAG_LENT;
		if (pItemProto->m_typeIdx == ITYPE_WEAPON && (pItemProto->m_flag & nNormalWeaponFlag) == nNormalWeaponFlag && pItemProto->m_price > 0)
		{
			switch (pItemProto->m_subtypeIdx)
			{
			case IWEAPON_NIGHT:
			case IWEAPON_CROSSBOW:
			case IWEAPON_STAFF:
			case IWEAPON_BIGSWORD:
			case IWEAPON_AXE:
			case IWEAPON_SHORTSTAFF:
			case IWEAPON_BOW:
			case IWEAPON_SHORTGUM:
			case IWEAPON_TWOSWORD:
			case IWEAPON_WAND:
			case IWEAPON_SCYTHE:
			case IWEAPON_POLEARM:
				switch (pItemProto->m_level)
				{
				case 37:
				case 41:
				case 45:
				case 49:
				case 53:
				case 57:
				case 61:
				case 65:
					m_listLendItem.insert(pItemProto->m_index);
					break;

				default:
					break;
				} // ����
				break;

			case IWEAPON_MINING:
			case IWEAPON_GATHERING:
			case IWEAPON_CHARGE:
			default:
				break;
			} // ���� Ÿ��
		} // ���� && �Ϲ��÷���

		if (pItemProto->m_price < 0)
		{
			GAMELOG << init("ERROR: ITEM PRICE")
					<< pItemProto->m_index << delim
					<< pItemProto->m_name << delim
					<< pItemProto->m_price
					<< end;
			bRet = false;
		}

		{
			pItemProto->pre_origin_option_count_ = 0;
			for (int i = 0; i < MAX_ORIGIN_OPTION; i++)
			{
				if (pItemProto->GetOriginIndex(i) > -1)
					++pItemProto->pre_origin_option_count_;
			}
		}

		{
			pItemProto->pre_origin_skill_count_ = 0;
			for (int i = MAX_ORIGIN_OPTION; i < MAX_ORIGIN; i++)
			{
				if (pItemProto->GetOriginIndex(i) > -1)
					++pItemProto->pre_origin_skill_count_;
			}
		}

		{
			pItemProto->is_range_weapon_ = false;

			if (pItemProto->getItemTypeIdx() == ITYPE_WEAPON)
			{
				switch (pItemProto->getItemSubTypeIdx())
				{
				case IWEAPON_CROSSBOW:
				case IWEAPON_BOW:
					pItemProto->is_range_weapon_ = true;
					break;
				}
			}
		}

		{
			pItemProto->is_magic_weapon_ = false;

			if (pItemProto->getItemTypeIdx() == ITYPE_WEAPON)
			{
				switch (pItemProto->getItemSubTypeIdx())
				{
				case IWEAPON_SHORTSTAFF:
				case IWEAPON_STAFF:
				case IWEAPON_WAND:
				case IWEAPON_SCYTHE:
				case IWEAPON_POLEARM:
				case IWEAPON_SOUL:
					pItemProto->is_magic_weapon_ = true;
					break;
				}
			}
		}

		{
			pItemProto->get_using_stat_ = -1;

			if (pItemProto->getItemTypeIdx() == ITYPE_WEAPON)
			{
				switch (pItemProto->getItemSubTypeIdx())
				{
				case IWEAPON_CROSSBOW:
				case IWEAPON_BOW:
				case IWEAPON_SHORTGUM:
					pItemProto->get_using_stat_ = USING_DEX;
					break;

				case IWEAPON_SOUL:
				case IWEAPON_WAND:
				case IWEAPON_POLEARM:
				case IWEAPON_SCYTHE:
				case IWEAPON_SHORTSTAFF:
				case IWEAPON_STAFF:
					pItemProto->get_using_stat_ = USING_INT;
					break;

				default:
					pItemProto->get_using_stat_ = USING_STR;
					break;
				}
			}
		}

		{
			pItemProto->is_weapon_type_ = false;

			if (pItemProto->getItemTypeIdx() == ITYPE_WEAPON)
			{
				switch (pItemProto->getItemSubTypeIdx())
				{
				case IWEAPON_NIGHT:
				case IWEAPON_CROSSBOW:
				case IWEAPON_STAFF:
				case IWEAPON_BIGSWORD:
				case IWEAPON_AXE:
				case IWEAPON_SHORTSTAFF:
				case IWEAPON_BOW:
				case IWEAPON_SHORTGUM:
				case IWEAPON_TWOSWORD:
				case IWEAPON_WAND:
				case IWEAPON_SCYTHE:
				case IWEAPON_POLEARM:
				case IWEAPON_SOUL:
					pItemProto->is_weapon_type_ = true;
					break;
				}
			}
		}

		{
			pItemProto->is_armor_type_ = false;

			if (pItemProto->getItemTypeIdx() == ITYPE_WEAR)
			{
				switch (pItemProto->getItemSubTypeIdx())
				{
				case		IWEAR_HELMET	:
				case		IWEAR_ARMOR		:
				case		IWEAR_PANTS		:
				case		IWEAR_GLOVE		:
				case		IWEAR_SHOES		:
				case		IWEAR_SHIELD	:
				case		IWEAR_BACKWING	:
					pItemProto->is_armor_type_ = true;
					break;
				}
			}
		}

		pItemProto->is_accessary_ = (pItemProto->getItemTypeIdx() == ITYPE_ACCESSORY && pItemProto->getItemSubTypeIdx() != IACCESSORY_PET );
		pItemProto->is_pet_ = (pItemProto->getItemTypeIdx() == ITYPE_ACCESSORY && pItemProto->getItemSubTypeIdx() == IACCESSORY_PET );
		pItemProto->is_apet_ = (pItemProto->getItemTypeIdx() == ITYPE_ACCESSORY && pItemProto->getItemSubTypeIdx() == IACCESSORY_ATTACK_PET );

		{
			pItemProto->is_upgrade_rune_ = false;

			if (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_UPGRADE)
			{
				switch (pItemProto->getItemNum0())
				{
				case IETC_UPGRADE_PURITY_RUNE:
				case IETC_UPGRADE_DEVIL_RUNE:
				case IETC_UPGRADE_CHAOS_RUNE:
				case IETC_UPGRADE_SUPER_RUNE:
				case IETC_UPGRADE_LUCKY_RUNE:
				case IETC_UPGRADE_LETSPLAY_RUNE:
				case IETC_PVP_RUNE:
					pItemProto->is_upgrade_rune_ = true;
					break;
				}
			}
		}

		pItemProto->is_jewel_type_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_JEWEL );

		pItemProto->is_chaos_jewel_type_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_CHAOSJEWEL);

		pItemProto->is_stable_type_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_STABILIZER );
		pItemProto->is_func_type_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_FUNCTIONS );

		pItemProto->is_reformer_item_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_REFORMER);
		if(pItemProto->getItemTypeIdx() == ITYPE_WEAPON || pItemProto->getItemTypeIdx() == ITYPE_WEAR)
		{
			pItemProto->is_allow_socket = true;
		}
		else if(pItemProto->getItemTypeIdx() == ITYPE_ACCESSORY)
		{
			switch(pItemProto->getItemSubTypeIdx())
			{
			case IACCESSORY_CHARM:
			case IACCESSORY_MAGICSTONE:
			case IACCESSORY_LIGHTSTONE:
			case IACCESSORY_EARING:
			case IACCESSORY_RING:
			case IACCESSORY_NECKLACE:
				pItemProto->is_allow_socket = true;
				break;
			}
		}

		{
			pItemProto->is_socket_type_ = true;

			if( !(pItemProto->getItemFlag() & ITEM_FLAG_SOCKET) )
			{
				pItemProto->is_socket_type_ = false;
			}
			if (pItemProto->isAllowSocketItem() == false)
			{
				pItemProto->is_socket_type_ = false;
			}
			if ((pItemProto->getItemTypeIdx() == ITYPE_WEAPON) &&
					 (pItemProto->getItemSubTypeIdx() == IWEAPON_MINING || pItemProto->getItemSubTypeIdx() == IWEAPON_GATHERING || pItemProto->getItemSubTypeIdx() == IWEAPON_CHARGE))
			{
				pItemProto->is_socket_type_ = false;
			}
			if (pItemProto->getItemJobFlag() & (1<<JOB_APET))
			{
				pItemProto->is_socket_type_ = false;
			}
			if (pItemProto->getItemFlag() & FLAG_ITEM_TRANSMOGRIFY || pItemProto->getItemFlag() & ITEM_FLAG_COMPOSITE || pItemProto->getItemFlag() & ITEM_FLAG_COSTUME2 || pItemProto->getItemFlag() & ITEM_FLAG_LORD)
			{
				pItemProto->is_socket_type_ = false;
			}
		}
		
		pItemProto->is_allow_socket = (pItemProto->getItemTypeIdx() == ITYPE_WEAPON || pItemProto->getItemTypeIdx() == ITYPE_WEAR);
		pItemProto->is_process_scroll_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_PROCESS_SCROLL);

		pItemProto->is_rebirth_item_ = false;
		switch (pItemProto->getItemIndex())
		{
		case 846:
		case 2667:
		case 3218:
		case 4933:
		case 5958:
		case 7056:
		case 9194:
		case 9195:
		case 9196:
			pItemProto->is_rebirth_item_ = true;
			break;
		}

		switch(pItemProto->getItemIndex())
		{
		case 6252:
		case 6253:
		case 6254:
		case 6255:
			pItemProto->is_monster_card_ = true;
			break;

		default:
			pItemProto->is_monster_card_ = false;
			break;
		}

		// RVR �������� ����� �� ���� ������
		pItemProto->is_rvr_not_use_ = false;
		switch(pItemProto->getItemIndex())
		{
		case 2407:	// ���� 5��
		case 2408:	// ���� 30��
		case 2500:	// �̺�Ʈ ���� 5��
		case 2609:	// ũ�������� ���� 5��
		case 5018:	// ����2 5��
		case 5019:	// ����2 30��
		case 47:	// �޸� ��ũ��
		case 858:	// ��ȯ ������
		case 857:	// ���� �̵� ������
		case 1298:	// ��Ƽ ���� 1�� ���ױ�
		case 1299:	// ��Ƽ ���� 7�� ���ױ�
		case 1300:	// ��Ƽ ���� 30�� ���ױ�
		case 1413:	// ��Ƽ ���� 3�ð� ���ױ�
		case 1415:	// ��Ƽ ���� 1�ð� ���ױ�
		case 2945:	// ���̸��� ��Ƽ ���� ���ױ�
		case 2946:	// �ƽ�ī��� ��Ƽ ���� ���ױ�
		case 6252:	// ���� �뺴 ī�� 1�ð�
		case 6253:	// ���� �뺴 ī�� 3�ð�
		case 6254:	// ���� �뺴 ī�� 9�ð�
		case 6255:	// ���� �뺴 ī�� 24�ð�
		case 6805:	// �ʺ��� ���� �뺴 ī��
		case 6985:	// ���� �뺴 ī�� 1��
		case 6986:	// ���� �뺴 ī�� 7��
		case 6987:	// ���� �뺴 ī�� 30��
			pItemProto->is_rvr_not_use_ = true;
			break;

		default:
			pItemProto->is_rvr_not_use_ = false;
			break;
		}

		if (m_protoItems[ridx].getItemFlag() & ITEM_FLAG_LORD)
		{
			m_flagload.push_back(&m_protoItems[ridx]);
		}

		if (m_protoItems[ridx].getItemFlag() & ITEM_FLAG_CHANGE)
		{
			m_flagchange.push_back(&m_protoItems[ridx]);
		}

		// ���忡�� ��밡���� ���������� ����
		if( pItemProto->getItemTypeIdx() == ITYPE_ONCE && pItemProto->getItemSubTypeIdx() == IONCE_WARP
				|| pItemProto->getItemTypeIdx() == ITYPE_ONCE && pItemProto->getItemSubTypeIdx() == IONCE_SUMMON
				|| pItemProto->getItemTypeIdx() == ITYPE_ACCESSORY && pItemProto->getItemSubTypeIdx() == IACCESSORY_PET
				|| pItemProto->getItemTypeIdx() == ITYPE_ACCESSORY && pItemProto->getItemSubTypeIdx() == IACCESSORY_ATTACK_PET
				|| pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_MONSTER_MERCENARY_CARD
		  )
		{
			pItemProto->is_useinwarzone_ = false;
		}
		else
		{
			pItemProto->is_useinwarzone_ = true;
		}


		pItemProto->is_rvr_jewel_ = (pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_RVR_JEWEL) ? true : false;

		pItemProto->is_timer_ = checkTimerItem(pItemProto);

		pItemProto->is_syndicate_ = (pItemProto->getItemRvRType() > 0) ? true : false;

		pItemProto->is_gps_ = (pItemProto->getItemTypeIdx() == ITYPE_ONCE && pItemProto->getItemSubTypeIdx() == IONCE_GPS) ? true : false;

		pItemProto->is_questGive = (pItemProto->getItemFlag() & ITEM_FLAG_QUESTGIVE) ? true : false;

		map_.insert(map_t::value_type(pItemProto->m_index, &m_protoItems[ridx]));

		ridx++;
	}

	m_nCount = ridx;

	return bRet;
}

CItemProto* CItemList::FindIndex(int idx)
{
	map_t::iterator it = map_.find(idx);
	return (it != map_.end()) ? it->second : NULL;
}

#ifdef DURABILITY
CItem* CItemList::CreateDBItem( int idx, char wearPos, int plus, int flag, int used,
								int used_2, const char* serial, LONGLONG count, short* option
								, char socketcount, int* jewel
								, int* OriginVar, int now_dur, int max_dur
							  )
#else
CItem* CItemList::CreateDBItem( int idx, char wearPos, int plus, int flag, int used,
								int used_2, const char* serial, LONGLONG count, short* option
								, char socketcount, int* jewel
								, int* OriginVar
							  )
#endif
{
	if (count == 0)
		return NULL;

	if (idx == 0)
		idx = NAS_ITEM_DB_INDEX;

	// ������ Ÿ�� ã��
	CItemProto* proto = FindIndex(idx);
	if (!proto)
	{
		return NULL;
	}

	// ������ ����
	CItem* item = new CItem;

	item->setItemProto(proto);

	item->m_tab_idx = -1;

	item->m_virualIndex = GetNextVirtualIndex();
	item->m_dbIndex = proto->m_index;
	item->setWearPos(wearPos);
	if (idx == 1577 || idx == 1578 || idx == 2047)
		item->setPlus(plus);
	else if( proto->getItemTypeIdx() == ITYPE_ACCESSORY && ( proto->getItemSubTypeIdx() == IACCESSORY_PET || proto->getItemSubTypeIdx() == IACCESSORY_ATTACK_PET ) )
	{
		item->setPlus(plus);
		item->setPlus_2(0);
	}
	else if (item->Is_fortune_item())
	{
		item->setPlus(plus);
	}
	else
	{
		item->setPlus(plus & 0x0000ffff);
		item->setPlus_2((plus >> 16) & 0x0000ffff);
	}
	item->setFlag(flag);
	item->setUsed(used);
	item->setUsed_2(used_2);

	if(serial == NULL)
	{
		item->m_serial = GetSerial();
	}
	else if(strcmp(serial, "") == 0)
	{
		item->m_serial = GetSerial();
	}
	else
	{
		item->m_serial = serial;
	}

	item->setItemCount(this->calcItemCount(proto, count));

	bool bRareItem = false;

	if (item->IsRareItem())
		bRareItem = true;

	if (bRareItem)
	{
		if (option[1] != 0)
		{
			item->m_pRareOptionProto = gserver->m_rareOptionList.Find(option[0]);
			if (item->m_pRareOptionProto)
			{
				item->m_nRareOptionIndex = option[0];
				item->m_nRareOptionBit = option[1];
				item->m_nOption = 2;
				item->m_option[0].GetDBValue(option[0]);
				item->m_option[1].GetDBValue(option[1]);
			}
		}
	}
	else if (item->IsOriginItem())
	{
		item->m_pSetItemProto = gserver->m_setItemProtoList.Find(item->m_itemProto->GetSetIndex());
	}
	else
	{
		// Option Setting
		int i;
		for (i=0; i < MAX_ITEM_OPTION; i++)
		{
			item->m_option[i].GetDBValue(option[i]);

			if (item->m_option[i].m_level <= 0)
				continue;

			item->m_option[i].m_proto = gserver->m_optionProtoList.FindProto(item->m_option[i].m_type);

			if (!item->m_option[i].m_proto)
				continue;

			item->m_option[item->m_nOption].m_value = item->m_option[i].m_proto->m_levelValue[item->m_option[i].m_level - 1];
			++item->m_nOption;
		}
	}

	if( ( proto->m_index == 2047 || proto->m_index == 2633 )
			&& item->getUsed() == -1)					// ���ڼ������� or ���� �Ҹ�����
	{
		item->setUsed(0);
	}

	if (proto->m_index == 1577 || proto->m_index == 1578)
	{
		// ���� ä�� ���ڵ��� m_used���� �ٸ�������� ����ϹǷ�
		// -1�� ������ 0���� �ʱ�ȭ
		if(item->getUsed() == -1)
		{
			item->setUsed(0);
		}
	}

	if(proto->getItemTypeIdx() == ITYPE_ETC &&
			proto->getItemSubTypeIdx() == IETC_JEWEL &&
			proto->getItemSet1() == 0 &&
			proto->m_nRareIndex[0] >= 0 && proto->m_nRareProb[0] > 0)
	{
		COptionProto* OptionProto = gserver->m_optionProtoList.FindProto(proto->m_nRareIndex[0]);
		if(OptionProto)
		{
			item->m_option[0].m_proto = OptionProto;
			item->m_option[0].m_type = OptionProto->m_type;
			item->m_option[0].m_level = proto->m_nRareProb[0];
			item->m_option[0].m_value = OptionProto->m_levelValue[item->m_option[0].m_level - 1];
			item->m_option[0].SetDBValue();
			item->m_nOption = 1;
		}
	}

	if(item->IsSocketItem())
	{
		int flag = item->getFlag();
		item->m_socketList.InitSocketFromDB(proto->getItemTypeIdx(), proto->getItemSubTypeIdx(), socketcount, jewel, &flag);
		item->setFlag(flag);
	}
	if (item->IsOriginItem() && OriginVar != NULL)
	{
		for (int i = 0; i < MAX_ORIGIN_OPTION; i++)
		{
			if (OriginVar[i] > 0 && item->GetOriginIndex(i) >= 0)
			{
				item->setOriginVar(i, OriginVar[i]);
			}
			else if (OriginVar[i] == 0 && item->GetOriginIndex(i) >= 0)
			{
				item->setOriginVar(i, 100);
			}
			else item->setOriginVar(i, 0);
		}
	}

#ifdef DURABILITY
	item->setNowDurability(now_dur);
	item->setMaxDurability(max_dur);
#endif

	return item;
}

CItem* CItemList::CreateItem(int idx, char wearPos, int plus, int flag, LONGLONG count)
{
	if (count == 0)
		return NULL;

	if (idx == 0)
		idx = NAS_ITEM_DB_INDEX;

	// ������ Ÿ�� ã��
	CItemProto* proto = FindIndex(idx);
	if (!proto)
	{
		GAMELOG << init("SYS_ERR")
				<< "Can't Create Item Index"
				<< idx << delim
				<< plus << delim
				<< flag << delim
				<< count
				<< end;
		return NULL;
	}

	CItem* item = new CItem;

	item->setItemProto(proto);

	item->m_tab_idx = -1;

	item->m_virualIndex = GetNextVirtualIndex();
	item->setDBIndex(proto->m_index);
	item->setWearPos(wearPos);
	item->setPlus(plus);
	item->setFlag(flag);

	// 
	if (item->getDBIndex() == NAS_ITEM_DB_INDEX)
	{
		item->setItemCount(count);
		return item;
	}

	item->setUsed(proto->getItemMaxUse());

	if (item->IsWeaponType() || item->IsArmorType())
	{
		if (item->m_itemProto->getItemSet0() > 0)
		{
			int nRandom = GetRandom(item->m_itemProto->getItemNum0(), item->m_itemProto->getItemSet0());
			item->setPlus_2(nRandom - item->m_itemProto->getItemNum0());
		}
		else if (item->m_itemProto->getItemSet1() > 0)
		{
			int nRandom = GetRandom(item->m_itemProto->getItemNum1(), item->m_itemProto->getItemSet1());
			item->setPlus_2(nRandom - item->m_itemProto->getItemNum1());
		}
		else
		{
			item->setPlus_2(0);
		}
	}

	if (item->IsOriginItem())
	{
		item->m_pSetItemProto = gserver->m_setItemProtoList.Find(item->m_itemProto->GetSetIndex());
	}

	if (proto->m_index == 1577 || proto->m_index == 1578)
	{
		// ���� ä�� ���ڵ��� m_used���� �ٸ�������� ����ϹǷ�
		// ������ 0���� �ʱ�ȭ
		item->setUsed(0);
	}

	item->m_serial = GetSerial();

	item->setItemCount(this->calcItemCount(proto, count));

	// 060227 : bs : ��Ƽ����
	if (proto->getItemTypeIdx() == ITYPE_ONCE && proto->getItemSubTypeIdx() == IONCE_WARP && proto->getItemNum0() == IONCE_WARP_PARTYRECALL)
	{
		item->setUsed(gserver->getNowSecond() + proto->getItemNum3() * 60 * 60);
	}

// â�� �̿� �ֹ���
	if( proto->getItemTypeIdx() == ITYPE_ONCE && proto->getItemSubTypeIdx() == IONCE_CASH && proto->getItemNum3() > 0)
		item->setUsed(gserver->getNowSecond() + proto->getItemNum3() * 60 * 60);

	if (proto->m_index == ONE_PERIOD_ITEM || proto->m_index == 2610 || proto->m_index == 4940 )
	{
		item->setUsed(gserver->getNowSecond() + 1 * 24 * 60 * 60);
	}

	if (proto->m_index == SEVEN_PERIOD_ITEM || proto->m_index == 4941 )
	{
		item->setUsed(gserver->getNowSecond() + 7 * 24 * 60 * 60);
	}

	if (proto->m_index == THIRTY_PERIOD_ITEM || proto->m_index == 4942 )
	{
		item->setUsed(gserver->getNowSecond() + 30 * 24 * 60 * 60);
	}

	// ���� ������ : num4�� �ϴ���
	if (proto->getItemFlag() & ITEM_FLAG_COMPOSITE)
	{
#ifdef CHARGE_ITEM_PERIOD
		int nItemNo = item->m_dbIndex;
		if( ( 1631 < nItemNo && nItemNo < 1704 ) || ( 1721 < nItemNo && nItemNo < 1794 ) )
		{
			item->setUsed(gserver->getNowSecond() + 7 * 24 * 60 * 60);
		}
		else
#endif	// CHARGE_ITEM_PERIOD
#ifdef NO_PERIOD_COMPOSITE
			if(proto->getItemNum4() != -1)
#endif
				item->setUsed(gserver->getNowSecond() + proto->getItemNum4() * 24 * 60 * 60);
	}

	if (item->getFlag() & FLAG_ITEM_TRANSMOGRIFY)
		item->setUsed(gserver->getNowSecond() + 1 * 24 * 60 * 60);

	if (proto->getItemFlag() & ITEM_FLAG_COSTUME2)
	{
		if(proto->getItemNum4() != -1)
		{
			item->setUsed(gserver->getNowSecond() + proto->getItemNum4() * 24 * 60 * 60);	// ���� �Ϸ�
		}
	}

	if (proto->getItemFlag() & ITEM_FLAG_ABS)
	{
		// �ð��� �������� m_num4�� �ð��� ����
#ifdef SYSTEM_TREASURE_MAP
		if(proto->m_index == TREASURE_MAP_ITEM_INDEX ) // �̳��� ������ ����Ѵ�.
			item->setUsed(gserver->getNowSecond() + proto->getItemNum4() * 60);
		else
#endif
		//â���� ������ �д����� ����Ѵ�.
		if(proto->m_typeIdx == ITYPE_ETC && proto->m_subtypeIdx == IETC_RVR_JEWEL)
			item->setUsed(gserver->getNowSecond() + proto->getItemNum4() * 60);
		else
			item->setUsed(gserver->getNowSecond() + proto->getItemNum4() * 60 * 60);
	}

	// ��纼 �̺�Ʈ ����� : GOLDENBALL_CARD_INDEX
	// used�� ��� ���� �ð�(���� ���� �ð�)�� ����
	if (proto->m_index == GOLDENBALL_CARD_INDEX)
	{
		item->setUsed(gserver->m_clGoldenBall.GetVoteEndTime());
	}

	if (item->IsLent())
	{
		item->setUsed(gserver->getNowSecond() + 24 * 60 * 60);
	}

	if( proto->m_index == 2047 || proto->m_index == 2633 )	// ���ڼ������� or ���� �Ҹ�����
	{
		item->setUsed(0);
	}

	if (proto->m_index == 2137)		// gpara �Ǽ�
	{
		short nGparaOption[5] =
		{
			((20 << OPTION_VALUE_SHIFT) & 0xff00) | (1 & 0x00ff),
			((21 << OPTION_VALUE_SHIFT) & 0xff00) | (1 & 0x00ff),
			(( 7 << OPTION_VALUE_SHIFT) & 0xff00) | (1 & 0x00ff),
			((16 << OPTION_VALUE_SHIFT) & 0xff00) | (1 & 0x00ff),
			(( 8 << OPTION_VALUE_SHIFT) & 0xff00) | (1 & 0x00ff),
		};
		item->m_nOption = 0;
		for (int i=0; i < MAX_ITEM_OPTION; i++)
		{
			item->m_option[i].GetDBValue(nGparaOption[i]);

			if (item->m_option[i].m_level <= 0)
				continue;

			item->m_option[i].m_proto = gserver->m_optionProtoList.FindProto(item->m_option[i].m_type);

			if (!item->m_option[i].m_proto)
				continue;

			item->m_option[item->m_nOption].m_value = item->m_option[i].m_proto->m_levelValue[item->m_option[i].m_level - 1];
			++item->m_nOption;
		}
	}

	// hc ��ī���ڴ� Ȯ���� �Ⱓ 30��
	if(proto->m_index == 2882)
	{
		item->setUsed(gserver->getNowSecond() + 30 * 24 * 60 * 60);
	}

	// �Ǵн� ���� �������� ��� �Ⱓ ������
	if( proto->m_index >= 3006 && proto->m_index <= 3011 )
	{
		item->setUsed(-1);
	}

	if( (proto->getItemTypeIdx() == ITYPE_ACCESSORY) && (proto->getItemNum4() > 0) )
	{
		item->setUsed(gserver->getNowSecond() + proto->getItemNum4() * 24 * 60 * 60);
	}

	if(proto->getItemTypeIdx() == ITYPE_ETC &&
			proto->getItemSubTypeIdx() == IETC_JEWEL &&
			proto->getItemSet0() == 0 &&
			proto->m_nRareIndex[0] >= 0 && proto->m_nRareProb[0] > 0)
	{
		COptionProto* OptionProto = gserver->m_optionProtoList.FindProto(proto->m_nRareIndex[0]);
		if(OptionProto)
		{
			item->m_option[0].m_proto = OptionProto;
			item->m_option[0].m_type = OptionProto->m_type;
			item->m_option[0].m_level = proto->m_nRareProb[0];
			item->m_option[0].m_value = OptionProto->m_levelValue[item->m_option[0].m_level - 1];
			item->m_option[0].SetDBValue();
			item->m_nOption = 1;
		}
	}

	if(item->m_itemProto->getItemTypeIdx() == ITYPE_ETC && item->m_itemProto->getItemSubTypeIdx() == IETC_MONSTER_MERCENARY_CARD  )
	{
#ifdef SYSTEM_MONSTER_MERCENARY_CARD_EX
		if( !gserver->m_MonsterMercenary.SetMercenaryData( item ) )
			return nullptr; //pwesty c++17
#else
		MonsterMercenaryInfo * mmd = gserver->m_MonsterMercenary.GetClassInfo();
		if( mmd == NULL )
		{
			GAMELOG << init("MOSTER MERCENARY FAIL : get MercenaryInfo") << end;
			return nullptr; //pwesty c++17
		}

		item->setUsed(-1);
		item->setPlus(gserver->m_MonsterMercenary.GetMercenaryIndex(mmd->nClassIdx)); // Mercenary npc index
		item->setUsed_2(mmd->nClassIdx);  // classIdx
		item->setPlus_2(0); // ���� 16 ��Ʈ�� ���ݷ��� �ִ´�. ���� 16��Ʈ�� ������ �ִ´�.
		int att=0, def=0;

		int nRand = GetRandom(0,1);
		switch( nRand )
		{
		case 0: // ���ݸ� ���ʽ��ش�.
			att = GetRandom(mmd->nBonusMini, mmd->nBonusMax);
			break;
		case 1: // ���� ���潺�� �ش�.
			def = GetRandom(mmd->nBonusMini, mmd->nBonusMax);
			break;
		}
		item->setPlus_2(item->getPlus_2() + (att << 8));
		item->setPlus_2(item->getPlus_2() + def);

		if( item->getUsed_2() == -1 )
		{
			GAMELOG << init("MOSTER MERCENARY FAIL : get MercenaryNpcIndex") << end;
			return false;
		}
#endif
	}
	if (item->IsOriginItem())
	{
		for (int i = 0; i < MAX_ORIGIN_OPTION; i++)
		{
			if(item->GetOriginIndex(i) >= 0)
			{
				item->setOriginVar(i, 100);
			}
		}
	}

#ifdef DURABILITY
	item->setNowDurability(proto->getDurability());
	item->setMaxDurability(proto->getDurability());
#endif

	return item;
}

CItem* CItemList::CreateAutoGiveDBItem(int idx, char wearPos, int plus, int flag, int used,
									   int used_2,	const char* serial, LONGLONG count, short* option
									   ,char socketcount, int* jewelidx
									  )
{
	if (count == 0)
		return NULL;

	if (idx == 0)
		idx = NAS_ITEM_DB_INDEX;

	// ������ Ÿ�� ã��
	CItemProto* proto = FindIndex(idx);
	if (!proto)
	{
		return NULL;
	}

	// ������ ����
	CItem* item = new CItem;

	item->setItemProto(proto);

	item->m_tab_idx = -1;

	item->m_virualIndex = GetNextVirtualIndex();
	item->setDBIndex(proto->m_index);
	item->setWearPos(wearPos);
	item->setPlus(plus);
	item->setFlag(flag);
	item->setUsed(used);
	item->setUsed_2(used_2);
	item->m_serial = serial;
	item->setItemCount(this->calcItemCount(proto, count));
	item->setPlus_2(0);

	bool bRareItem = false;

	if (item->IsRareItem())
		bRareItem = true;

	if (bRareItem)
	{
		if (option[1] != 0)
		{
			item->m_pRareOptionProto = gserver->m_rareOptionList.Find(option[0]);
			if (item->m_pRareOptionProto)
			{
				item->m_nRareOptionIndex = option[0];
				item->m_nRareOptionBit = option[1];
				item->m_nOption = 2;
				item->m_option[0].GetDBValue(option[0]);
				item->m_option[1].GetDBValue(option[1]);
			}
		}
	}
	else
	{
		// Option Setting
		int i;
		for (i=0; i < MAX_ITEM_OPTION; i++)
		{
			item->m_option[i].GetDBValue(option[i]);

			if (item->m_option[i].m_level <= 0)
				continue;

			item->m_option[i].m_proto = gserver->m_optionProtoList.FindProto(item->m_option[i].m_type);

			if (!item->m_option[i].m_proto)
				continue;
			item->m_option[item->m_nOption].m_value = item->m_option[i].m_proto->m_levelValue[item->m_option[i].m_level - 1];
			++item->m_nOption;
		}
	}

	if (item->IsOriginItem())
	{
		item->m_pSetItemProto = gserver->m_setItemProtoList.Find(item->m_itemProto->GetSetIndex());
	}

	if( ( proto->m_index == 2047 || proto->m_index == 2633 )
			&& item->getUsed() == -1)					// ���ڼ������� or ���� �Ҹ�����
	{
		item->setUsed(0);
	}

	if (proto->m_index == 1577 || proto->m_index == 1578)
	{
		// ���� ä�� ���ڵ��� m_used���� �ٸ�������� ����ϹǷ�
		// -1�� ������ 0���� �ʱ�ȭ
		if(item->getUsed() == -1)
		{
			item->setUsed(0);
		}
	}

	// ���� ������ : num4�� �ϴ���
	if (proto->getItemFlag() & ITEM_FLAG_COMPOSITE)
	{
#ifdef CHARGE_ITEM_PERIOD
		int nItemNo = item->m_dbIndex;
		if( ( 1631 < nItemNo && nItemNo < 1704 ) || ( 1721 < nItemNo && nItemNo < 1794 ) )
		{
			item->setUsed(gserver->getNowSecond() + 7 * 24 * 60 * 60);
		}
		else
#endif	// CHARGE_ITEM_PERIOD
#ifdef NO_PERIOD_COMPOSITE
			if(proto->getItemNum4() != -1)
#endif
			{
				item->setUsed(gserver->getNowSecond() + proto->getItemNum4() * 24 * 60 * 60);
			}
	}
	
	if (item->getFlag() & FLAG_ITEM_TRANSMOGRIFY) {
		item->setUsed(gserver->getNowSecond() + 1 * 24 * 60 * 60);
	}

	// hc ��ī���ڴ� Ȯ���� �Ⱓ 30��
	if(proto->m_index == 2882)
	{
		item->setUsed(gserver->getNowSecond() + 30 * 24 * 60 * 60);
	}

	// �Ǵн� ���� �������� ��� �Ⱓ ������
	if( proto->m_index >= 3006 && proto->m_index <= 3011 )
	{
		item->setUsed(-1);
	}

	if (proto->getItemTypeIdx() == ITYPE_ONCE && proto->getItemSubTypeIdx() == IONCE_WARP && proto->getItemNum0() == IONCE_WARP_PARTYRECALL)
	{
		item->setUsed(gserver->getNowSecond() + proto->getItemNum3() * 60 * 60);
	}
	// â�� �̿� �ֹ���
	if( proto->getItemTypeIdx() == ITYPE_ONCE && proto->getItemSubTypeIdx() == IONCE_CASH && proto->getItemNum3() > 0)
		item->setUsed(gserver->getNowSecond() + proto->getItemNum3() * 60 * 60);

	// ��ȭ�� �̿� �ֹ���
	if( proto->getItemTypeIdx() == ITYPE_ONCE && proto->getItemSubTypeIdx() == IONCE_CASH && proto->getItemNum3() > 0)
		item->setUsed(gserver->getNowSecond() + proto->getItemNum3() * 60 * 60);

	// ��ġ ������
	if( proto->getItemTypeIdx() == ITYPE_ONCE && proto->getItemSubTypeIdx() == IONCE_CASH && proto->getItemNum3() > 0)
		item->setUsed(gserver->getNowSecond() + proto->getItemNum3() * 60 * 60);
	if (proto->m_index == ONE_PERIOD_ITEM || proto->m_index == 2610 || proto->m_index == 4940 )
	{
		item->setUsed(gserver->getNowSecond() + 1 * 24 * 60 * 60);
	}

	if (proto->m_index == SEVEN_PERIOD_ITEM || proto->m_index == 4941 )
	{
		item->setUsed(gserver->getNowSecond() + 7 * 24 * 60 * 60);
	}

	if (proto->m_index == THIRTY_PERIOD_ITEM || proto->m_index == 4942 )
	{
		item->setUsed(gserver->getNowSecond() + 30 * 24 * 60 * 60);
	}

	if (proto->getItemFlag() & ITEM_FLAG_COSTUME2)
	{
		if(proto->m_num4 != -1)
		{
			item->setUsed(gserver->getNowSecond() + proto->getItemNum4() * 24 * 60 * 60);	// ���� �Ϸ�
		}
	}

	if (proto->getItemFlag() & ITEM_FLAG_ABS)
	{
		// �ð��� �������� m_num4�� �ð��� ����
#ifdef SYSTEM_TREASURE_MAP
		if(proto->m_index == TREASURE_MAP_ITEM_INDEX ) // �̳��� ������ ����Ѵ�.
			item->setUsed(gserver->getNowSecond() + proto->getItemNum4() * 60);
		else
#endif
			item->setUsed(gserver->getNowSecond() + proto->getItemNum4() * 60 * 60);
	}

	if (proto->m_index == GOLDENBALL_CARD_INDEX)
	{
		item->setUsed(gserver->m_clGoldenBall.GetVoteEndTime());
	}

	if (item->IsLent())
	{
		item->setUsed(gserver->getNowSecond() + 24 * 60 * 60);
	}

	if( (proto->getItemTypeIdx() == ITYPE_ACCESSORY) && (proto->getItemNum4() > 0) )
	{
		item->setUsed(gserver->getNowSecond() + proto->getItemNum4() * 24 * 60 * 60);
	}

	if(proto->getItemTypeIdx() == ITYPE_ETC &&
			proto->getItemSubTypeIdx() == IETC_JEWEL &&
			proto->m_nRareIndex[0] >= 0 && proto->m_nRareProb[0] > 0)
	{
		COptionProto* OptionProto = gserver->m_optionProtoList.FindProto(proto->m_nRareIndex[0]);
		if(OptionProto)
		{
			item->m_option[0].m_proto = OptionProto;
			item->m_option[0].m_type = OptionProto->m_type;
			item->m_option[0].m_level = proto->m_nRareProb[0];
			item->m_option[0].m_value = OptionProto->m_levelValue[item->m_option[0].m_level - 1];
			item->m_option[0].SetDBValue();
			item->m_nOption = 1;
		}
	}

	if(item->IsSocketItem())
	{
		int flag = item->getFlag();
		item->m_socketList.InitSocketFromDB(proto->getItemTypeIdx(), proto->getItemSubTypeIdx(), socketcount, jewelidx, &flag);
		item->setFlag(flag);
	}
	if (item->IsOriginItem())
	{
		for (int i = 0; i < MAX_ORIGIN_OPTION; i++)
		{
			if(item->GetOriginIndex(i) >= 0)
			{
				item->setOriginVar(i, 100);
			}
		}
	}

#ifdef DURABILITY
	item->setNowDurability(proto->getDurability());
	item->setMaxDurability(proto->getDurability());
#endif

	return item;
}

//#ifdef DEV_GUILD_STASH
CItem* CItemList::CreateDBItem_2( int idx, char wearPos, int plus, int flag, int used, int used_2, const char* serial, LONGLONG count, short* option , const char* socket, int* itemOrigin )
{
	const char* pSocketInfo = socket;
	int socketcount = 0;
	int jewelidx[MAX_SOCKET_COUNT];
	if(*pSocketInfo)
	{
		char buf[10];
		pSocketInfo = AnyOneArg(pSocketInfo, buf);
		jewelidx[0] = atoi(buf);

		pSocketInfo = AnyOneArg(pSocketInfo, buf);
		socketcount = atoi(buf);
		if(socketcount >= 1 && socketcount <= MAX_SOCKET_COUNT)
		{
			int i;
			for(i = 1; i < MAX_SOCKET_COUNT && *pSocketInfo; i++)
			{
				pSocketInfo = AnyOneArg(pSocketInfo, buf);
				jewelidx[i] = atoi(buf);
			}
		}
		else
		{
			socketcount = 0;
			memset(jewelidx, -1, MAX_SOCKET_COUNT);
		}
	}
	else
	{
		socketcount = 0;
		memset(jewelidx, -1, MAX_SOCKET_COUNT);
	}

#ifdef DURABILITY
	return CreateDBItem( idx, wearPos, plus, flag, used, used_2, serial, count, option, socketcount, jewelidx, itemOrigin, 0, 0 );
#else
	return CreateDBItem( idx, wearPos, plus, flag, used, used_2, serial, count, option, socketcount, jewelidx, itemOrigin );
#endif
}

int CItemList::GetNextVirtualIndex()
{
	boost::mutex::scoped_lock lock(m_mutex_for_virtualIndex);

	++m_virtualIndex;

	if (m_virtualIndex < 1)
		m_virtualIndex = 1;

	return m_virtualIndex;
}

LONGLONG CItemList::calcItemCount( CItemProto* proto, LONGLONG count )
{
	if (proto->getItemFlag() & ITEM_FLAG_COUNT)
	{
		if (proto->getStackCount() < count)
			count = proto->getStackCount();
	}
	else
	{
		count = 1;
	}

	return count;
}

bool CItemList::checkTimerItem( CItemProto* proto )
{
	if (proto->getItemFlag() & ITEM_FLAG_ABS)
		return true;

	if (proto->getItemTypeIdx() == ITYPE_ONCE && proto->getItemSubTypeIdx() == IONCE_CASH && proto->getItemNum3() > 0)
		return true;

	if (proto->getItemTypeIdx() == ITYPE_ONCE && proto->getItemSubTypeIdx() == IONCE_WARP && proto->getItemNum0() == IONCE_WARP_PARTYRECALL)
		return true;

	switch (proto->m_index)
	{
	case ONE_PERIOD_ITEM:
	case 2610:
	case 4940:
	case SEVEN_PERIOD_ITEM:
	case 4941:
	case THIRTY_PERIOD_ITEM:
	case 4942:
	case GOLDENBALL_CARD_INDEX:
	case 2047:
	case 2633:
#ifdef SYSTEM_TREASURE_MAP
	case TREASURE_MAP_ITEM_INDEX:
#endif
	case 2882:
	case 3006:
	case 3007:
	case 3008:
	case 3009:
	case 3010:
	case 3011:
	case 2455:
	case 2456:
	case 2457:
	case 2458:
	case 2459:
	case 2460:
	case 2607:
	case 2608:
	case 2868:
	case 2461:
	case 2462:
	case 2463:
	case 2606:
	case EXPERIENCE_COMPETITION_ITEM:
	case PERIOD_COMPETITION_ITEM:
	case 2609:
	case 5018:
	case 5019:
	case 4913:

		return true;
	}

	if (proto->isRvrJewel())
		return true;

	if (proto->getItemFlag() & ITEM_FLAG_COSTUME2 && proto->getItemNum4() > 0)
		return true;

	if (proto->getItemTypeIdx() == ITYPE_ACCESSORY && proto->getItemNum4() > 0)
		return true;

	if (proto->getItemFlag() & FLAG_ITEM_TRANSMOGRIFY)
		return true;

	if (proto->getItemFlag() & ITEM_FLAG_COMPOSITE && proto->getItemNum4() > 0)
		return true;

	if (proto->getItemFlag() & ITEM_FLAG_TRIGGER)
		return true;

	if (proto->getItemTypeIdx() == ITYPE_ETC && proto->getItemSubTypeIdx() == IETC_MONSTER_MERCENARY_CARD)
		return true;

	return false;
}

//#endif //DEV_GUILD_STASH

CCatalog* CCatalogList::FindItemToCatalog(int itemDBIndex)
{
	int i;
	int count = this->GetCount();

	CCtItemList* itemList = NULL;
	for( i = 0; i < count; i++ )
	{
		if( !catalog[i].GetEnable()
				|| catalog[i].GetCategory() == CATEGORY_PACKAGE
				|| catalog[i].GetType() == TYPE_EQUIP_EQUIPMENT )
			continue;

		itemList = this->catalog[i].GetCtItemList();
		if( itemList )
		{
			CItem* item = itemList->GetItem(0);
			if( !item || !item->m_itemProto )
				continue;

			if( item->m_itemProto->getItemIndex() == itemDBIndex && item->getPlus() == 0 && item->getFlag() == 0 && item->Count() == 1 )
				return &catalog[i];
		}
	}

	return NULL;
}

CCatalog* CCatalogList::FindItemToCatalog(CItem* pItem)
{
	int i;
	int count = this->GetCount();

	CCtItemList* itemList = NULL;
	for( i = 0; i < count; i++ )
	{
		if( !catalog[i].GetEnable()
				|| catalog[i].GetCategory() == CATEGORY_PACKAGE
				|| catalog[i].GetType() == TYPE_EQUIP_EQUIPMENT )
			continue;

		itemList = this->catalog[i].GetCtItemList();
		if( itemList )
		{
			CItem* item = itemList->GetItem(0);

			if( !item || !item->m_itemProto || !pItem || !pItem->m_itemProto )
				continue;

			if( item->getDBIndex() == pItem->getDBIndex() && item->getPlus() == pItem->getPlus() && item->getFlag() == pItem->getFlag() && item->Count() == 1 )
				return &catalog[i];
		}
	}

	return NULL;
}

bool CCatalogList::Load()
{
	memset(m_typelist, 0, sizeof(int)*TYPE_MAX_COUNT);
	memset(m_subtypelist, 0, sizeof(int)*SUBTYPE_MAX_COUNT);
	if (this->catalog)
		delete [] this->catalog;

	this->catalog = NULL;
	this->m_cCount = 0;

	CDBCmd cmd;

	CLCString sql(4096);

#if defined(USE_TENTER_BILLING)
	cmd.Init(&gserver->m_dbcatal);
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		sql.Format("select * from t_catalog_hardcore order by a_ctid DESC", GAMEID);
	}
	else
	{
		sql.Format("select * from t_catalog_%d order by a_ctid DESC", GAMEID);
	}
#else
	cmd.Init(&gserver->m_dbdata);
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		sql.Format("select * from t_catalog_hardcore order by a_ctid DESC");
	}
	else
	{
		sql.Format("select * from t_catalog order by a_ctid DESC");
	}
#endif
	cmd.SetQuery(sql);

	if( !cmd.Open() )
	{
		GAMELOG << init("CATALOGLIST_LOAD_ERROR") << end;
		return false;
	}

	this->m_cCount = cmd.GetRecordCount();
	this->catalog = new CCatalog[m_cCount];

	if( !cmd.MoveFirst() )
	{
		GAMELOG << init("CATALOGLIST_LOAD_ERROR") << end;
		return false;
	}

	int i = 0;
	char enable = 0;

	do
	{
		//int		m_index;		// īŻ�α� �ε���
		//CLCString m_name;
		//int		m_type;			// Ÿ��
		//int		m_cash;			// ����
		//int		m_mileage;		// ���ϸ���
		//int		m_toSell;			// �Ǹ� ���� ����
		//int		m_flag;
		//bool		m_enable;
		int index, type, cash, mileage, flag;
		int category, subtype;
		CLCString name(MAX_ITEM_NAME_LENGTH+1);

		if( !cmd.GetRec("a_ctid", index)
				|| !cmd.GetRec("a_ctname", name)
				|| !cmd.GetRec("a_type", type)
				|| !cmd.GetRec("a_category", category)
				|| !cmd.GetRec("a_subtype", subtype)
				|| !cmd.GetRec("a_cash", cash)
				|| !cmd.GetRec("a_mileage", mileage)
				|| !cmd.GetRec("a_flag", flag)
				|| !cmd.GetRec("a_enable", enable)
		  )
		{
			GAMELOG << init("CATALOGLIST_LOAD_ERROR") << end;
			return false;
		}
		CCtItemList* ctItemList = new CCtItemList;
		ctItemList->Load(index);
		if(category != CATEGORY_PACKAGE && ctItemList && ctItemList->GetCount() == 1 && ctItemList->GetItem(0) && ctItemList->GetItem(0)->m_itemProto->getItemIndex() == 855 && ctItemList->GetItem(0)->Count() == 1)
			m_recoveryCtid = i;

		catalog[i].SetCatalog(index, name, category, type, subtype, cash, mileage, enable == 1 ? true : false, flag, ctItemList);

		if(catalog[i].GetToSell() > CATALOG_FLAG_MAX_LIMIT || catalog[i].GetToSell() < 0 )
		{
			GAMELOG << init("CATALOGLIST_LOAD_FLAG_LIMIT_ERROR") << end;
			return false;
		}
#if defined( LC_USA ) || defined( LC_TLD )
		if( catalog[i].GetToSell() != 0 || catalog[i].GetCategory() == CATEGORY_PLATINUM )
#else
		if(catalog[i].GetToSell() != 0 )
#endif
		{
			gserver->m_limitCT.insert(catalog[i].GetIndex());
		}

		i++;
	}
	while( cmd.MoveNext() );
#if defined (USE_TENTER_BILLING)
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		sql.Format("select a_type from t_catalog_hardcore where a_enable = 1  group by a_type order by a_type asc", GAMEID);
	}
	else
	{
		sql.Format("select a_type from t_catalog_%d where a_enable = 1  group by a_type order by a_type asc", GAMEID);
	}
#else
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		sql.Format("select a_type from t_catalog_hardcore where a_enable = 1  group by a_type order by a_type asc");
	}
	else
	{
		sql.Format("select a_type from t_catalog where a_enable = 1  group by a_type order by a_type asc");
	}
#endif
	int temp = 0;
	int typelist = 0;
	cmd.SetQuery(sql);
	if(!cmd.Open())
		return false;
	if(!cmd.MoveFirst())
		return false;

	do
	{
		if(cmd.GetRec("a_type", typelist))
		{
			if(typelist != 0)
			{
				if(typelist % 10000 != 0)
				{
					m_typelist[temp] = typelist;
					temp++;
				}
			}
		}
	}
	while(cmd.MoveNext());
	m_typeCount = temp;

#if defined (USE_TENTER_BILLING)
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		sql.Format("select a_subtype from t_catalog_hardcore where a_enable = 1  group by a_subtype order by a_subtype asc", GAMEID);
	}
	else
	{
		sql.Format("select a_subtype from t_catalog_%d where a_enable = 1  group by a_subtype order by a_subtype asc", GAMEID);
	}
#else
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		sql.Format("select a_subtype from t_catalog_hardcore where a_enable = 1  group by a_subtype order by a_subtype asc");
	}
	else
	{
		sql.Format("select a_subtype from t_catalog where a_enable = 1  group by a_subtype order by a_subtype asc");
	}
#endif
	temp = 0;
	int subtypelist = 0;
	cmd.SetQuery(sql);
	if(!cmd.Open())
		return false;
	if(!cmd.MoveFirst())
		return false;

	do
	{
		if(cmd.GetRec("a_subtype", subtypelist))
		{
			if(subtypelist != 0)
			{
				if(subtypelist % 100 != 0)
				{
					m_subtypelist[temp] = subtypelist;
					temp++;
				}
			}
		}
	}
	while(cmd.MoveNext());
	m_subtypeCount = temp;

	return true;
}

bool CCatalogList::Reload()
{
	CDBCmd cmd;
	CLCString sql(1024);

	GAMELOG << init("CATALOG RELOAD TEST : BEFORE ") << m_cCount << delim << catalog[0].GetName() << delim << catalog[0].GetCash()
			<< delim << itemlog(catalog[0].GetCtItemList()->GetItem(0),false) << end;

	int			cNewCount=0;
	CCatalog*	pNewcatalog;

#if defined(USE_TENTER_BILLING)
	cmd.Init(&gserver->m_dbcatal);
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		sql.Format("select * from t_catalog_hardcore order by a_ctid DESC", GAMEID);
	}
	else
	{
		sql.Format("select * from t_catalog_%d order by a_ctid DESC", GAMEID);
	}
#else
	cmd.Init(&gserver->m_dbdata);
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		sql.Format("select * from t_catalog_hardcore order by a_ctid DESC");
	}
	else
	{
		sql.Format("select * from t_catalog order by a_ctid DESC");
	}
#endif
	cmd.SetQuery(sql);

	if( !cmd.Open() )
	{
		GAMELOG << init("CATALOGLIST_RELOAD_ERROR") << end;
		return false;
	}

	if( !cmd.MoveFirst() )
	{
		GAMELOG << init("CATALOGLIST_RELOAD_ERROR") << end;
		return false;
	}

	cNewCount = cmd.GetRecordCount();
	pNewcatalog = new CCatalog[cNewCount];

	int i = 0;
	char enable = 0;

	gserver->m_limitCT.clear();

	do
	{
		int index, type, cash, mileage, flag;
		int category, subtype;
		CLCString name(MAX_ITEM_NAME_LENGTH+1);

		if( !cmd.GetRec("a_ctid", index)
				|| !cmd.GetRec("a_ctname", name)
				|| !cmd.GetRec("a_type", type)
				|| !cmd.GetRec("a_category", category)
				|| !cmd.GetRec("a_subtype", subtype)
				|| !cmd.GetRec("a_cash", cash)
				|| !cmd.GetRec("a_mileage", mileage)
				|| !cmd.GetRec("a_flag", flag)
				|| !cmd.GetRec("a_enable", enable)
		  )
		{
			GAMELOG << init("CATALOGLIST_LOAD_ERROR") << end;
			delete[] pNewcatalog;
			return false;
		}

		CCtItemList* ctItemList = new CCtItemList;
		ctItemList->Load(index);
		if( category != CATEGORY_PACKAGE && ctItemList && ctItemList->GetCount() == 1 && ctItemList->GetItem(0) &&
				ctItemList->GetItem(0)->m_itemProto->getItemIndex() == 855 && ctItemList->GetItem(0)->Count() == 1)
		{
			m_recoveryCtid = i;
		}

		if(pNewcatalog[i].GetToSell() > CATALOG_FLAG_MAX_LIMIT || pNewcatalog[i].GetToSell() < 0 )
		{
			GAMELOG << init("CATALOGLIST_RELOAD_FLAG_LIMIT_ERROR") << end;
			delete[] pNewcatalog;
			return false;
		}
#if defined( LC_USA ) || defined( LC_TLD )
		if( pNewcatalog[i].GetToSell() != 0 || pNewcatalog[i].GetCategory() == CATEGORY_PLATINUM )
#else
		if(pNewcatalog[i].GetToSell() != 0 )
#endif
		{
			gserver->m_limitCT.insert(pNewcatalog[i].GetIndex());
		}

		i++;
	}
	while( cmd.MoveNext() );

	// �ε��� �ٲ�ġ��
	CCatalog* temp = catalog;
	catalog = pNewcatalog;
	delete[]	temp;
	m_cCount = cNewCount;

	GAMELOG << init("CATALOG RELOAD TEST : AFTER ") << m_cCount << delim << catalog[0].GetName() << delim << catalog[0].GetCash()
			<< delim << itemlog(catalog[0].GetCtItemList()->GetItem(0),false) << end;

	return true;
}
bool CCatalogList::ReloadPrice()
{
	GAMELOG << init("PRICE RELOADING START") << end;
	CDBCmd cmd;
	CLCString sql(1024);
	int ctid = 0;
	int price = 0;
#if defined(USE_TENTER_BILLING)
	cmd.Init(&gserver->m_dbcatal);
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		sql.Format("select a_ctid, a_cash from t_catalog_hardcore order by a_ctid DESC", GAMEID);
	}
	else
	{
		sql.Format("select a_ctid, a_cash from t_catalog_%d order by a_ctid DESC", GAMEID);
	}
#else
	cmd.Init(&gserver->m_dbdata);
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		sql.Format("select a_ctid, a_cash from t_catalog_hardcore order by a_ctid DESC");
	}
	else
	{
		sql.Format("select a_ctid, a_cash from t_catalog order by a_ctid DESC");
	}
#endif
	cmd.SetQuery(sql);
	CCatalog* pCatal;
	if(!cmd.Open())
	{
		GAMELOG << init("PRICE RELOADING ERROR") << "Table Open Error" << end;
		GAMELOG << init("PRICE RELOADING END") << end;
		return false;
	}
	if(!cmd.MoveFirst())
	{
		GAMELOG << init("PRICE RELOADING ERROR") << "MoveFirst Error" << end;
		GAMELOG << init("PRICE RELOADING END") << end;
		return false;
	}
	do
	{
		if( !cmd.GetRec("a_ctid", ctid) || !cmd.GetRec("a_cash", price) )
		{
			continue;
		}
		else
		{
			pCatal = gserver->m_catalogList.Find(ctid);
			if(pCatal)
			{
				pCatal->SetPrice(price);
			}
		}
	}
	while(cmd.MoveNext());
	GAMELOG << init("PRICE RELOADING END") << end;
	return true;
}

bool CCtItemList::Load(int ctIdx)
{ 
	_delete();

	int itemindex, itemflag, itemplus, itemnum;

	CLCString sql(4096);
	CDBCmd cmd;
#if defined(USE_TENTER_BILLING)
	cmd.Init(&gserver->m_dbcatal);
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		sql.Format("select * from t_ct_item_hardcore where a_ctid=%d", GAMEID, ctIdx);
	}
	else
	{
		sql.Format("select * from t_ct_item_%d where a_ctid=%d", GAMEID, ctIdx);
	}
#else
	cmd.Init(&gserver->m_dbdata);
	if (gserver->m_hardcore_flag_in_gameserver)
	{
		sql.Format("select * from t_ct_item_hardcore where a_ctid=%d", ctIdx);
	}
	else
	{
		sql.Format("select * from t_ct_item where a_ctid=%d", ctIdx);
	}
#endif
	cmd.SetQuery(sql);

	if( !cmd.Open() )
	{
		GAMELOG << init("CATALOGLIST_LOAD_ERROR") << end;
		return false;
	}

	if( !cmd.MoveFirst() )
	{
		GAMELOG << init("CATALOGLIST_LOAD_ERROR") << end;
		return false;
	}

	int i =0;
	do
	{
		if( !cmd.GetRec("a_item_idx", itemindex)
				|| !cmd.GetRec("a_item_flag", itemflag)
				|| !cmd.GetRec("a_item_plus", itemplus)
				|| !cmd.GetRec("a_item_num", itemnum) )
		{
			GAMELOG << init("CATALOGLIST_LOAD_ERROR") << end;
			return false;
		}

		CItem *item = gserver->m_itemProtoList.CreateItem(itemindex, -1, itemplus, itemflag, itemnum);
		ctItem.push_back(item);
		i++;
	}
	while( cmd.MoveNext() );

	return true;
}

CItem* CCtItemList::GetItem(CItem* pItem)
{
	int i;
	int count = this->GetCount();

	for(i = 0; i < count; i++)
	{
		if( this->GetItem(i) && GetItem(i) == pItem )
		{
			return GetItem(i);
		}
	}

	return NULL;
}

void CCtItemList::_delete()
{
	if(this->ctItem.empty() == false)
	{
		std::vector<CItem*>::iterator it = this->ctItem.begin();
		std::vector<CItem*>::iterator it_end = this->ctItem.end();

		for(; it != it_end; it++)
		{
			if((*it) != NULL)
				delete (*it);
		}

		ctItem.clear();
	}
}

void CItem::originReform(unsigned int count,int nIndex_)
{
	if (!this->IsOriginItem())
		return ;

	const int nRandomloop = 5;

	int i, j, min = 50, max, variation = 0;

	if (nIndex_ == 9006 )
	min = min + (count * 5 / 10);	// Ȳ�� ������ �ϳ��� 0.5% �� ���� 50�� minimum

#ifdef PREMIUM_REFORMER_11072021
	if (nIndex_ == 12293)
		min = min + (count * 7 / 10);
#endif

	for (i = 0; i < MAX_ORIGIN_OPTION; i++)
	{
		if (this->GetOriginIndex(i) < 0)
			continue;
		max = this->m_itemProto->getItemProtoOriginVariation(i);
		if (max == 0)
			this->setOriginVar(i, 100);
		else if (min >= max)
			this->setOriginVar(i, max);
		else
		{
			for (j = 0; j < nRandomloop; j++)
			{
				variation = GetRandom(min, max);
				if (j == 0)
					this->setOriginVar(i, variation);
				else
				{
					if (variation < this->getOriginVar(i))
					{
						this->setOriginVar(i, variation);
					}
				}
			}
		}
	}
}

void CItem::setItemCount(LONGLONG count)
{
	if(count < 0) return ;
	m_count = count;
}

void CItem::clone( CItem& destItem )
{
	CItemProto* destOldProto = destItem.m_itemProto;
	memcpy(&destItem, this, sizeof(*this) - sizeof(m_serial));
	destItem.m_serial = this->m_serial;
	// memcpy copied this->m_itemProto into destItem; fix ref tracking
	if (destOldProto)
		destOldProto->removeRef(&destItem);
	if (destItem.m_itemProto)
		destItem.m_itemProto->addRef(&destItem);
}

ComposeItem::ComposeItem()
{
	m_item_load_count = 0;
}

ComposeItem::~ComposeItem()
{
	delete[] data;
}

ComposeItem* ComposeItem::instance()
{
	static ComposeItem _instance;
	return &_instance;
}

void ComposeItem::load()
{
	FILE* fp = NULL;

	CLCString strTemp(1024);

	strTemp.Format("%s%s", gserver->m_serverpath, COMPOSE_ITEM_FILENAME);

	fp = fopen(strTemp, "rb");

	if(fp == NULL)
	{
		LOG_ERROR("ComposeItem Data Load Fail.....");
		return;
	}

	fread(&m_item_load_count, sizeof(int), 1, fp);

	if(m_item_load_count <= 0)
	{
		fclose(fp);
		return ;
	}

	data = new stComposeData[m_item_load_count];
	fread(data, sizeof(stComposeData) * m_item_load_count, 1, fp);
	fclose(fp);

	init();
}

void ComposeItem::init()
{
	LONGLONG key;
	int dummy_index;
	for(int i = 0; i < m_item_load_count; i++)
	{
		_map.insert(COMPOSE_MAP::value_type(data[i].Material_index, &data[i]));
	}
}

stComposeData* ComposeItem::find( int mat_item_index )
{
	COMPOSE_MAP::iterator it;
	it = _map.find(mat_item_index);

	if(it == _map.end())
		return NULL;

	return it->second;
}
