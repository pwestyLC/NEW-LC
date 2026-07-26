#include <string>
#include <boost/format.hpp>
#include "stdhdrs.h"

#include "Character.h"
#include "Item.h"
#include "Descriptor.h"
#include "Server.h"
#include "DBManager.h"
#include "CmdMsg.h"
#include "doFunc.h"
#include "WearInvenManager.h"
#include "Artifact_Manager.h"
#include "../ShareLib/packetType/ptype_old_do_skill.h"

std::set<int>	CWearInvenManager::warePos_set_;
int				CWearInvenManager::m_suitWearingPos[6];

CWearInvenManager::CWearInvenManager(CPC* pc)
	: _owner(pc)
	, _lastError(0)
	,dressCostumCount(0)
	,wearSuitItem(NULL)
{
	wearItemInfo.reserve(MAX_WEARING);
	for(int i = 0; i < MAX_WEARING; ++i)
	{
		wearItemInfo.push_back(static_cast<CItem*>(NULL));
	}
}


CWearInvenManager::~CWearInvenManager(void)
{
	for(int i = 0; i < MAX_WEARING; ++i)
	{
		if(wearItemInfo[i] != NULL)
		{
			delete wearItemInfo[i];
			wearItemInfo[i] = NULL;
		}
	}

	delete wearSuitItem;
}

bool CWearInvenManager::IsWearingSomething() {
	for(int i = 0; i < MAX_WEARING; ++i)
	{
		if(wearItemInfo[i] != NULL)
		{
			return true;
		}
	}
	return false;
}

bool CWearInvenManager::AddNormalItem( CItem* item, int wearPos )
{
	if (CanDressNormal(item, wearPos) == false)
		return false;

	char mountPetType = 0;
	bool bChangeMountPet = false;
	CPet* pet1 = NULL;
	CPet* pet2 = NULL;

	// ����� �Ա�
	CItem* takeOffWearItem = NULL;
	if ( wearItemInfo[wearPos] != NULL )	//�����Ϸ��� �ڸ��� �������� �̹� �����Ѵٸ�
	{
		takeOffWearItem = getWearItem(wearPos);		//���� ������

		if (!takeOffWearItem->IsAPet() &&	takeOffWearItem->getFlag() & FLAG_ITEM_SEALED)
			return false;

		if (takeOffWearItem->IsPet())
		{
			// ���� �����ۿ� �ش��ϴ� ���� ã�´�
			CPet* pet = _owner->GetPet(takeOffWearItem->getPlus());
			if (pet)
			{
				if (pet->IsMount())
				{
					bChangeMountPet = true;
					mountPetType = 0;
					pet2 = pet;
				}
				else
				{
					pet->Disappear();
				}
			}
		}
		if( takeOffWearItem->IsAPet() )
		{
			CAPet* pet = _owner->GetAPet(takeOffWearItem->getPlus());
			if( pet )
			{
				if( pet && pet->IsMount() )
					pet->Mount(false);
				pet->m_nDelay = pet->m_pProto->m_nDelay ;
				pet->Disappear();
			}
		}

		CItem *pItemNormal = takeOffWearItem;
		//���� �������� ���
		if (((pItemNormal->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (pItemNormal->getFlag() & FLAG_ITEM_TRANSMOGRIFY)) 
			&& (pItemNormal->getFlag() & FLAG_ITEM_COMPOSITION))
		{
			pItemNormal = _owner->m_inventory.FindByVirtualIndex(pItemNormal->m_nCompositeItem);
		}
		//������ �ɼ� �� ���
		if ( pItemNormal != NULL && pItemNormal->IsOriginItem() )
		{
			// �������� �ɼ� �� ��Ʈ �������� ��ų ����
			for (int i = MAX_ORIGIN_OPTION; i < MAX_ORIGIN; i++)
			{
				int nIndex = pItemNormal->GetOriginIndex(i);
				if (nIndex <= 0)
					continue;

				CSkill * pSkill = gserver->m_skillProtoList.Create(nIndex, pItemNormal->GetOriginLevel(i));
				if(pSkill)
				{
					if (pSkill->m_proto->IsActive())
					{
						//������ ��ų ��Ÿ���� ����
						{
							CSkill* skill = _owner->m_activeSkillList.Find(pSkill->m_proto->m_index);
							if(skill == NULL)
							{
								LOG_ERROR("invalid Skill Info. charIndex[%d], skillIndex[%d]", _owner->m_index, pSkill->m_proto->m_index);
								return false;
							}

							CPC::map_t::iterator it = _owner->itemSkill.find(pSkill->m_proto->m_index);
							if(it != _owner->itemSkill.end())
							{
								it->second = skill->m_usetime;
							}
							else
							{
								_owner->itemSkill.insert(std::pair<int, int>(pSkill->m_proto->m_index, skill->m_usetime));
							}
						}

						pSkill->Cancel(_owner);

						{
							CNetMsg::SP rmsg(new CNetMsg);
							ResponseClient::makeSkillCancelMsg(rmsg, _owner);
							_owner->m_pArea->SendToCell(rmsg, _owner, true);
						}

						_owner->RemoveSkillFromQuickSlot(pSkill);
						_owner->m_activeSkillList.Remove(pSkill);
					}
					else if (pSkill->m_proto->IsPassive())
					{
						_owner->m_passiveSkillList.Remove(pSkill);
					}
					else
					{
						_owner->m_etcSkillList.Remove(pSkill);
					}
				}
			}

			// ��Ʈ ������ ���� ���� ���� �� ��Ʈ ȿ�� ��ų ����
			if (pItemNormal->m_itemProto->GetSetIndex())
			{
				_owner->CountSetItem(pItemNormal, false);
				_owner->RemoveSetItemValue(pItemNormal);

				pItemNormal->m_nSetWearCnt = 0;
				pItemNormal->m_nSetOption = 0;
			}

			{
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeSkillListMsg(rmsg, _owner);
				SEND_Q(rmsg, _owner->m_desc);
			}
		}
		_owner->m_optionAttSkillList.Clear();
		_owner->m_optionDefSkillList.Clear();
	}

	// ��չ���� ���и� ���� �������� ���ϰ�
	switch (item->m_itemProto->getItemTypeIdx())
	{
	case ITYPE_WEAPON:
		switch (item->m_itemProto->getItemSubTypeIdx())
		{
		case IWEAPON_CROSSBOW:
		case IWEAPON_STAFF:
		case IWEAPON_BIGSWORD:
		case IWEAPON_AXE:
		case IWEAPON_BOW:
		case IWEAPON_MINING:
		case IWEAPON_GATHERING:
		case IWEAPON_CHARGE:
		case IWEAPON_TWOSWORD:
		case IWEAPON_SCYTHE:
		case IWEAPON_POLEARM:
		case IWEAPON_SOUL:
			if (wearItemInfo[WEARING_SHIELD] != NULL)
			{
				CItem* pitem = wearItemInfo[WEARING_SHIELD];

				if (pitem->m_itemProto->getItemTypeIdx() == ITYPE_WEAR && pitem->m_itemProto->getItemSubTypeIdx() == IWEAR_SHIELD)
				{
					if( DelNormalItem(WEARING_SHIELD) == false)
					{
						return false;
					}
				}
			}
			break;
		}
		break;
	case ITYPE_WEAR:
		switch (item->m_itemProto->getItemSubTypeIdx())
		{
		case IWEAR_SHIELD:
			if (wearItemInfo[WEARING_WEAPON] != NULL)
			{
				CItem* pitem = wearItemInfo[WEARING_WEAPON];
				if (pitem->getFlag() & FLAG_ITEM_SEALED)
					return false;

				switch (pitem->m_itemProto->getItemTypeIdx())
				{
				case ITYPE_WEAPON:
					switch (pitem->m_itemProto->getItemSubTypeIdx())
					{
					case IWEAPON_CROSSBOW:
					case IWEAPON_STAFF:
					case IWEAPON_BIGSWORD:
					case IWEAPON_AXE:
					case IWEAPON_BOW:
					case IWEAPON_MINING:
					case IWEAPON_GATHERING:
					case IWEAPON_CHARGE:
					case IWEAPON_TWOSWORD:
					case IWEAPON_SCYTHE:
					case IWEAPON_POLEARM:
					case IWEAPON_SOUL:
						if( DelNormalItem(WEARING_WEAPON) == false)
						{
							return false;
						}
					}
					break;
				}
			}
			break;
		}
		break;

	case ITYPE_ACCESSORY:
		{
			if(item->m_itemProto->getItemIndex() == 2371
					|| item->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
					|| item->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
					|| item->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
					|| item->m_itemProto->getItemIndex() == 2610
					|| item->m_itemProto->getItemIndex() == 4940
					|| item->m_itemProto->getItemIndex() == 4941
					|| item->m_itemProto->getItemIndex() == 4942
			  )
			{
				CSkill* pSkill;
				bool bApply;
				pSkill = gserver->m_skillProtoList.Create(item->m_itemProto->getItemNum0(), item->m_itemProto->getItemNum1());
				if(pSkill)
				{
					ApplySkill(_owner, _owner, pSkill, item->m_itemProto->getItemIndex(), bApply);
					delete pSkill;
					pSkill = NULL;
				}
				GAMELOG << init("ITEM WEAR AUTO POTION") << delim << item->m_itemProto->getItemIndex() << end;
			}
		}
		break;
	}
	// --- ��չ���� ���и� ���� �������� ���ϰ�

	CItem *pItemNormal = item;
	if(((pItemNormal->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (pItemNormal->getFlag() & FLAG_ITEM_TRANSMOGRIFY)) 
	&& (pItemNormal->getFlag() & FLAG_ITEM_COMPOSITION))
	{
		pItemNormal = _owner->m_inventory.FindByVirtualIndex(item->m_nCompositeItem);
	}
	if (pItemNormal && pItemNormal->IsOriginItem())
	{
		// �ͼ� ����
		if (pItemNormal->GetBelongType() != ORIGIN_OPTION_BELONG_NONE && !pItemNormal->IsBelong())
		{
			pItemNormal->setFlag(pItemNormal->getFlag());
			GAMELOG << init("ITEM WEAR BELONG", _owner) << itemlog(pItemNormal) << end;
		}

		// ���� ����, �ɼ� ����
		if (pItemNormal->m_itemProto->GetSetIndex())
		{
			_owner->CountSetItem(pItemNormal);
		}
	}

	if( pItemNormal && ((pItemNormal->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (pItemNormal->getFlag() & FLAG_ITEM_TRANSMOGRIFY)) 
	&& (pItemNormal->getFlag() & FLAG_ITEM_COMPOSITION) )
	{
		pItemNormal = _owner->m_inventory.FindByVirtualIndex(item->m_nCompositeItem);
	}
#ifdef HACKING_PET_FIX
	if (item->IsAPet() || item->IsPet())
	{
		if (wearPos != WEARING_PET)
		{
			LOG_ERROR("HACKING? : invalid wear pos[%d]. charIndex[%d]",wearPos, _owner->m_index);
			_owner->m_desc->Close("HACKING PET");
			return false;
		}
	}
#endif
	// �ֿϵ��� ���� ������ �ֿϵ����� Appear
	if (item->IsPet())
	{
		// ���� �����ۿ� �ش��ϴ� ���� ã�´�
		CPet* pet = _owner->GetPet(item->getPlus());
		if (pet)
		{
			if (pet->IsMountType())
			{
				bChangeMountPet = true;
				mountPetType = pet->GetPetTypeGrade();
				pet1 = pet;
			}
			else
			{
				pet->Appear(true);
			}
			//�꿡�Ե� ���� ���� Ÿ���� ����
			pet->setSyndicateType(_owner->getSyndicateType());
		}
	}

	if (bChangeMountPet)
	{
		if (pet2)
		{
			pet2->Mount(false);
		}
		if (pet1)
		{
			pet1->Mount(true);
		}
	}

	this->DressNormal(item, wearPos);

	_owner->CalcStatus(true);

	if( item->IsAPet() )	// ������ �ֿϵ��� Appear
	{
		CAPet* apet = _owner->GetAPet(item->getPlus());

		if( !( item->getFlag() & FLAG_ITEM_SEALED ) && apet && DEAD(apet) )
		{
			apet->m_hp = 1;
			apet->m_mp = 1;
		}

		if( apet && !DEAD(apet) )
		{
			apet->Appear(true,true);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				ExAPetFuntionMsg(rmsg, MSG_SUB_SKILLLIST, apet, 0);
				SEND_Q(rmsg, apet->GetOwner()->m_desc);
			}
			{
				CNetMsg::SP rmsg(new CNetMsg);
				APetAIOnOffMsg(rmsg, apet, MSG_APET_ERROR_OK);
				SEND_Q(rmsg, apet->GetOwner()->m_desc);
			}
			{
				CNetMsg::SP rmsg(new CNetMsg);
				APetAIListMsg(rmsg, apet);
				SEND_Q(rmsg, apet->GetOwner()->m_desc);
			}

			apet->setSyndicateType(_owner->getSyndicateType());
		}
	}

	_owner->m_assist.CheckApplyConditions();

	if(_owner->GetAPet(0))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ExAPetStatusMsg(rmsg, _owner->GetAPet(0));
		_owner->m_pArea->SendToCell(rmsg, _owner, true);
		SEND_Q(rmsg, _owner->m_desc);
	}

	if (pItemNormal && (pItemNormal->GetOriginSkillCnt() > 0 || pItemNormal->m_nSetOption == 2))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeSkillListMsg(rmsg, _owner);
		SEND_Q(rmsg, _owner->m_desc)
	}

	if(pItemNormal != NULL)
	{
		switch(pItemNormal->getDBIndex())
		{
		case ARTIFACT_LEVEL1_ITEM_INDEX:
		case ARTIFACT_LEVEL2_ITEM_INDEX:
		case ARTIFACT_LEVEL3_ITEM_INDEX:
			if(_owner->IsParty() == true)
				_owner->m_party->updateCalcMember();
			break;
		}

	}

	return true;
}

bool CWearInvenManager::AddCostumItem( CItem* item, int wearPos )
{
	if(wearPos == 11 ) 
		wearPos = 7; 
	//��ȿ�� �˻�
	if( CanDressCostum(item, wearPos) == false )
		return false;

	//�ѹ� �ǻ��� �԰� �ִ� ���
	if( NULL != getCosWearSuitItem() )
	{
		if(DelCostumSuitItem() == false)
		{
			return false;
		}
	}
	
	//���� �ڽ�Ƭ ������ ����
	this->DressCostum(item, wearPos);

	return true;
}

bool CWearInvenManager::DelNormalItem( int wearPos, short tab /*= -1*/, short invenIndex /*= -1*/ )
{
	CItem* item = _owner->m_wearInventory.wearItemInfo[wearPos];

	if(item == NULL)
		return false;

	//���� �� �ִ����� ���� ��ȿ�� �˻�
	if (CanUndressNormal(item, wearPos) == false)
	{
		/*CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::doItemWearError *packet = reinterpret_cast<ResponseClient::doItemWearError*>(rmsg->m_buf);
		ResponseClient::ItemTakeoffMsg(rmsg, GetLastError());
		SEND_Q(rmsg, _owner->m_desc);*/

		return false;
	}

	//���� �������� ��ġ������ �ִ� ���
	if( tab >= 0 && invenIndex >= 0)
	{
		//�巡�� �� ������� �������� ���� ��쿡�� �κ��丮���� �ش� ��ġ�� �������� �����ͼ� �� �� �� ó��
		CItem* dressItem = _owner->m_inventory.getItem(tab, invenIndex);
		if(dressItem == NULL)
		{
			this->UndressNormal(item, wearPos);
			_owner->m_inventory.addItemToInvenIndex(item, tab, invenIndex);
		}
		else if (dressItem->m_itemProto->getItemWearing() == item->m_itemProto->getItemWearing() && dressItem->m_itemProto->getItemJobFlag() & (1 << _owner->m_job))
		{
			AddNormalItem(dressItem, dressItem->m_itemProto->getItemWearing());
		}
		else
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::ItemTakeoffMsg(rmsg, ResponseClient::WEAR_ERR_CANNOT_WEAR);
			SEND_Q(rmsg, _owner->m_desc);
			return false;
		}
	}
	else
	{
		if(_owner->m_inventory.getEmptyCount() <= 0)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::ItemTakeoffMsg(rmsg, ResponseClient::WEAR_ERR_NOT_ENOUGH_INVEN);
			SEND_Q(rmsg, _owner->m_desc);
			return false;
		}

		this->UndressNormal(item, wearPos);
		_owner->m_inventory.addItem(item);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::ItemTakeoffMsg(rmsg, ResponseClient::WEAR_ERR_OK);
		SEND_Q(rmsg, _owner->m_desc);
	}

	//���� ������ �����۵鿡 ���� �ɼ� ���� ����
	ApplyDeleteItem(item, wearPos);
	//���� ������ �����۵��� �� ���� �����͸� ���������ش�. (�κ��丮 ������ ����)
	_owner->ChangeQuickSlot(item, QUICKSLOT_TYPE_ITEM);

	switch(item->getDBIndex())
	{
	case ARTIFACT_LEVEL1_ITEM_INDEX:
	case ARTIFACT_LEVEL2_ITEM_INDEX:
	case ARTIFACT_LEVEL3_ITEM_INDEX:
		if(_owner->IsParty() == true)
			_owner->m_party->updateCalcMember();
		break;
	}

	return true;
}

bool CWearInvenManager::DelCostumItem( int wearPos, short tab /*= -1*/, short invenIndex /*= -1*/ )
{
	if( wearPos == 11) wearPos = 7;

	if (isValidWarePos(wearPos + COSTUME2_WEARING_START) == false)
	{
		LOG_ERROR("HACKING? : invalid wear pos[%d]. charIndex[%d]", wearPos + COSTUME2_WEARING_START, _owner->m_index);
		_owner->m_desc->Close("invalid wear pos");
		return false;
	}

	CItem* TakeOffItem = _owner->m_wearInventory.wearItemInfo[wearPos + COSTUME2_WEARING_START];

	//��ȿ�� �˻�
	if (CanUndressCostum(TakeOffItem, wearPos) == false)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::doItemWearError *packet = reinterpret_cast<ResponseClient::doItemWearError*>(rmsg->m_buf);
		ResponseClient::ItemTakeoffMsg(rmsg, GetLastError());
		SEND_Q(rmsg, _owner->m_desc);
		return false;
	}

	if (tab >= 0 && invenIndex >= 0)
	{
		//�巡�� �� ������� �������� ���� ��쿡�� �κ��丮���� �ش� ��ġ�� �������� �����ͼ� �� �� �� ó��
		CItem* dressItem = _owner->m_inventory.getItem(tab, invenIndex);
		if(dressItem == NULL)
		{
			this->UndressCostum(TakeOffItem, wearPos);
			_owner->m_inventory.addItemToInvenIndex(TakeOffItem, tab, invenIndex);
		}
		else if( dressItem->m_itemProto->getItemFlag() & ITEM_FLAG_COSTUME2 )
		{
			return false;
		}
		else if( dressItem && (dressItem->m_itemProto->getItemWearing() == TakeOffItem->m_itemProto->getItemWearing()) && dressItem->m_itemProto->getItemJobFlag() & (1 << _owner->m_job) )
		{
			this->UndressCostum(TakeOffItem, wearPos);
			AddCostumItem(dressItem, dressItem->m_itemProto->getItemWearing());
			if(_owner->m_inventory.isUsable(tab) == true)
			{
				_owner->m_inventory.addItemToInvenIndex(TakeOffItem, tab, invenIndex);
			}
			else
			{
				_owner->m_inventory.addItem(TakeOffItem);
			}
		}
		else
		{
			this->_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}
	else
	{
		this->UndressCostum(TakeOffItem, wearPos);
		_owner->m_inventory.addItem(TakeOffItem);
	}

	_owner->ChangeQuickSlot(TakeOffItem, QUICKSLOT_TYPE_ITEM);

	return true;
}

CItem* CWearInvenManager::getWearItem( int wearPos )
{
	if (isValidWarePos(wearPos) == false)
	{
		LOG_ERROR("HACKING? : invalid wear pos[%d]. charIndex[%d]", wearPos, _owner->m_index);
		_owner->m_desc->Close("invalid wear pos");
		return NULL;
	}

	return wearItemInfo[wearPos];
}

CItem* CWearInvenManager::getCosWearItem( int wearPos )
{
	if(wearPos == 11) wearPos = 7;
	wearPos += COSTUME2_WEARING_START;

	if (isValidWarePos(wearPos) == false)
	{
		LOG_ERROR("HACKING? : invalid wear pos[%d]. charIndex[%d]", wearPos, _owner->m_index);
		_owner->m_desc->Close("invalid wear pos");
		return NULL;
	}

	return wearItemInfo[wearPos];
}

bool CWearInvenManager::CanDressNormal( CItem* item, int wearPos )
{
	if( item == NULL )
	{
		_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
		return false;
	}
	if (isValidWarePos(wearPos) == false)
		return false;

	if (item->m_itemProto->getItemRvRType() != SYNDICATE::eSYNDICATE_NONE)
	{
		if(_owner->getSyndicateType() != item->m_itemProto->getItemRvRType())
		{
			return false;
		}
		if(_owner->m_syndicateManager.getSyndicateGrade(_owner->getSyndicateType()) < item->m_itemProto->getItemRvRGrade())
		{
			return false;
		}
	}

	if(item->m_itemProto->getItemFlag() & ITEM_FLAG_CASTLLAN)
	{
		int zonenum;
		char castellan;
		bool ret = _owner->CheckCastellanType(zonenum, castellan);

		if(item->m_itemProto->getItemNum3() & 0xffff0000)  // ���ָ���� ������
		{
			if(!ret || castellan)
			{
				// ���ָ���� �ƴϴ�.
				CNetMsg::SP rmsg(new CNetMsg);
				CastllanErrorMsg(rmsg, MSG_EX_CASTLLAN_ERROR_NOT_CASTLLAN_GUILD);
				SEND_Q(rmsg, _owner->m_desc);

				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			}

			if(zonenum != (item->m_itemProto->getItemNum3() & 0xffff))
			{
				// �Ҽӵ� ���� �������� �ƴ�
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			}
		}
		else		// ���ֿ� ������
		{
			if(!ret || !castellan)
			{
				// ���ָ���� �ƴϴ�.
				CNetMsg::SP rmsg(new CNetMsg);
				CastllanErrorMsg(rmsg, MSG_EX_CASTLLAN_ERROR_NOT_CASTLLAN);
				SEND_Q(rmsg, _owner->m_desc);
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			}
			if(zonenum != (item->m_itemProto->getItemNum3() & 0xffff))
			{
				// �Ҽӵ� ���� �������� �ƴ�
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			}
		}
	}

	//������ ���� �˻�
	if (!(item->m_itemProto->getItemJobFlag() & (1 << _owner->m_job)))
	{
		_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
		return false;
	}

	// ����ġ �˻�
	if (item->m_itemProto->getItemFrame() != -1)
	{
		if (_owner->m_fame < item->m_itemProto->getItemFrame())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_SHORT_FAME);
			SEND_Q(rmsg, _owner->m_desc);
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}

	if(item->IsAPet() || item->IsPet())
	{
		if( gserver->m_subno == 4 )
		{
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}

	if( item->IsAPet() )	// ����ð��� ���� ������
	{
		CAPet *pet = _owner->GetAPet(item->getPlus());
		if( pet && pet->m_nDelay > 0 )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ExAPetFuntionMsg( rmsg, MSG_SUB_SUMMON_ERROR, pet , (unsigned char)pet->m_nDelay );
			SEND_Q( rmsg,  pet->GetOwner()->m_desc );
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}

	// ���� ��ġ�� �ùٸ��� �˻�
	if (item->m_itemProto->getItemWearing() != wearPos)
	{
		// �ùٸ��� ���� ���� ��ġ�̸� ���� �������� �Ǽ����� �˻�
		// �Ǽ��縮�� �ùٸ��� ���� ���� ��ġ�� ���� �������� ������
		if (item->IsAccessary())
		{
			int i;
			for (i = WEARING_ACCESSORY1; i <= WEARING_ACCESSORY3; i++)
			{
				if (_owner->m_wearInventory.wearItemInfo[i] == NULL)
					break;
			}

			if (i > WEARING_ACCESSORY3)
				wearPos = WEARING_ACCESSORY1;
			else
				wearPos = i;

			// newslot - alanssoares
			if (_owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4] == NULL &&
				item->m_itemProto->getItemWearing() == WEARING_ACCESSORY4)
				wearPos = WEARING_ACCESSORY4;
			
			// newslot - alanssoares
			if (_owner->m_wearInventory.wearItemInfo[WEARING_SPECIAL_ACCESSORY5] == NULL &&
				item->m_itemProto->getItemWearing() == WEARING_SPECIAL_ACCESSORY5)
				wearPos = WEARING_SPECIAL_ACCESSORY5;
			
			// newslot - alanssoares
			for (int w = WEARING_SPECIAL_ACCESSORY1; w <= WEARING_SPECIAL_ACCESSORY4; w++)
			{
				if (_owner->m_wearInventory.wearItemInfo[w] == NULL &&
					item->m_itemProto->getItemWearing() == w)
				{
					wearPos = w;
					break;
				}
				//this shit
				// block use same acc
				/*if (_owner->m_wearInventory.wearItemInfo[w] &&
					_owner->m_wearInventory.wearItemInfo[w]->m_itemProto->getItemIndex() == item->m_itemProto->getItemIndex())
				{
					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::ItemWearMsg(rmsg, ResponseClient::WEAR_ERR_INVALID_POS);
					SEND_Q(rmsg, _owner->m_desc);
					_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
					return false;
				}*/
			}
		}
		else
		{
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}
	
	// �Դ� �������� ���յ� �������̸� �Ұ���
	if (item->CanWear() == false)
	{
		_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
		return false;
	}

	// 060221 : bs : �� ����� �ֱ� ���� �ð��� �˻�
	if (item->IsPet())
	{
		CPet* pet = _owner->GetPet(item->getPlus());
		if (!pet)
		{
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}

#ifdef BLOCK_MOUNT_NIGHTSHADOW
		if( _owner->m_job == JOB_NIGHTSHADOW && pet->IsMountType() )
		{
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
#endif

		if (_owner->m_pZone)
		{
			if(pet->IsMountType() == false && !_owner->m_pZone->m_bCanSummonPet)
			{
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			}

			else if(pet->IsMountType() && !_owner->m_pZone->m_bCanMountPet)
			{
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			}
		}
		else
			return true;

		if (pet->GetRemainRebirthTime() > 0)
		{
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}

		CItem* oldpet = getWearItem(WEARING_PET);//pet fix
		if (oldpet != NULL)
		{
			if (DelNormalItem(WEARING_PET) == false)
				return false;
		}
	}

	if(_owner->m_pZone)
	{
		if(item->IsAPet() && !_owner->m_pZone->m_bCanSummonPet)
		{
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}

	CItem* pCompositItem = NULL;
	// ���� �������� ���뷹���� ������ �˻��Ѵ�

	CItem* pEquip = item;
	if (item->getFlag() & FLAG_ITEM_COMPOSITION)
	{
		if ((item->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (item->getFlag() & FLAG_ITEM_TRANSMOGRIFY))
		{
			pEquip = _owner->m_inventory.FindByVirtualIndex(item->m_nCompositeItem);
			pCompositItem = pEquip;
		}
	}
	
	if (pCompositItem &&  (pCompositItem->IsRareItem() || pCompositItem->IsOriginItem()))
	{
		/** ���� �������� ���� üũ
		* ���� ������, �������� �ɼ� �������� ��쿡�� ���� üũ
		**/
#ifdef PREMIUM_CHAR
		int itemLevel = pCompositItem->GetItemLevelForPremiumChar(_owner->m_premiumChar.getPremiumType());
#else
		int itemLevel = pCompositItem->GetItemLevel();
#endif

		if (itemLevel > _owner->m_level)
		{
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}

	//���� �������� ��쿡�� ���� üũ �Ѵ�. (�����̾� ĳ���� ���� X)
	if(item->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && item->m_itemProto->getItemSubTypeIdx() == IACCESSORY_ARTIFACT)
	{
		int itemLevel = item->GetItemLevel();

		if (itemLevel > _owner->m_level)
		{
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}

	if (item != NULL && item->IsRareItem())
	{
#ifdef PREMIUM_CHAR
		int itemLevel = item->GetItemLevelForPremiumChar(_owner->m_premiumChar.getPremiumType());
#else
		int itemLevel = item->GetItemLevel();
#endif

		if (itemLevel > _owner->m_level)
		{
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}

	if (item->IsOriginItem())
	{
#ifdef PREMIUM_CHAR
		int itemLevel = item->GetItemLevelForPremiumChar(_owner->m_premiumChar.getPremiumType());
#else
		int itemLevel = item->GetItemLevel();
#endif

		if (itemLevel > _owner->m_level)
		{
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}

	switch(item->m_itemProto->getItemIndex())
	{
	case 2669:	// Ÿ��ź �����
	case 2670:	// ����Ʈ �����
	case 2671:	// ���� �����
	case 2672:	// ������ �����
	case 2673:	// �α� �����
	case 2674:	// �Ҽ��� �����

		if(_owner->m_level > 45)		// 45���� �ʰ��� ������
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_CANNOT_WEAR);
			SEND_Q(rmsg, _owner->m_desc);
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	default:
		break;
	}

	if ( (item->tab() == INVENTORY_TAB_CASH_1 && _owner->m_inventory.isUsable(INVENTORY_TAB_CASH_1) == false) ||
			(item->tab() == INVENTORY_TAB_CASH_2 && _owner->m_inventory.isUsable(INVENTORY_TAB_CASH_2) == false) ||
			(item->tab() == INVENTORY_TAB_CASH_3 && _owner->m_inventory.isUsable(INVENTORY_TAB_CASH_3) == false) ||
			(item->tab() == INVENTORY_TAB_CASH_4 && _owner->m_inventory.isUsable(INVENTORY_TAB_CASH_4) == false) || 
			(item->tab() == INVENTORY_TAB_CASH_5 && _owner->m_inventory.isUsable(INVENTORY_TAB_CASH_5) == false) || 
			(item->tab() == INVENTORY_TAB_CASH_6 && _owner->m_inventory.isUsable(INVENTORY_TAB_CASH_6) == false) )
	{
		_lastError = ResponseClient::WEAR_ERR_CANNOT_SWAP_ITEM_CASH_INVEN;
		return false;
	}

	CItem * item2 = _owner->m_wearInventory.wearItemInfo[wearPos];		// ���� ������

	// ���� ���� ���·� �԰ų� ���� �Ұ�
	if (_owner->IsSetPlayerState(PLAYER_STATE_SITDOWN) && ((item->IsPet()) || (item2 && item2->IsPet())))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_CANNOT_WEAR);
		SEND_Q(rmsg, _owner->m_desc);
		_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
		return false;
	}

	// ����Ʈ ������� ����Ʈ Ÿ�� ���� �Ұ�
#ifdef BLOCK_MOUNT_NIGHTSHADOW
	if ( _owner->m_job == JOB_NIGHTSHADOW && item->IsPet() )
	{
		CPet *pet = _owner->GetPet( item->getPlus() );
		if( pet && pet->IsMountType() )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_CANNOT_WEAR);
			SEND_Q(rmsg, _owner->m_desc);
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}
#endif

	// �Ѵ� NULL �̸� ����
	if (!item && !item2)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_CANNOT_WEAR);
		SEND_Q(rmsg, _owner->m_desc);
		_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
		return false;
	}

	// �����̸� ������ ��ġ�� �ùٸ��� ���޵Ǿ� ��
	if (item2 != NULL && item2->m_itemProto->getItemWearing() != wearPos)
	{
		// newslot - alanssoares
		if (item2->IsAccessary())
		{
			if (item2->m_itemProto->getItemWearing() == WEARING_ACCESSORY4 && wearPos != WEARING_ACCESSORY4) {
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg(rmsg, MSG_SYS_CANNOT_WEAR);
				SEND_Q(rmsg, _owner->m_desc);
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			} // newslot - alanssoares
			else if (item2->m_itemProto->getItemWearing() == WEARING_SPECIAL_ACCESSORY5 && wearPos != WEARING_SPECIAL_ACCESSORY5) {
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg(rmsg, MSG_SYS_CANNOT_WEAR);
				SEND_Q(rmsg, _owner->m_desc);
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			} // newslot - alanssoares
			else if ((item2->m_itemProto->getItemWearing() >= WEARING_SPECIAL_ACCESSORY1 && item2->m_itemProto->getItemWearing() <= WEARING_SPECIAL_ACCESSORY4)
			&& (wearPos < WEARING_SPECIAL_ACCESSORY1 || wearPos > WEARING_SPECIAL_ACCESSORY4))
			{
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg(rmsg, MSG_SYS_CANNOT_WEAR);
				SEND_Q(rmsg, _owner->m_desc);
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			}
			else if (wearPos < WEARING_ACCESSORY1 || wearPos > WEARING_ACCESSORY3)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg(rmsg, MSG_SYS_CANNOT_WEAR);
				SEND_Q(rmsg, _owner->m_desc);
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			}
		}
		else
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_CANNOT_WEAR);
			SEND_Q(rmsg, _owner->m_desc);
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}

	return true;
}

bool CWearInvenManager::CanUndressNormal( CItem* item, int wearPos )
{
	if (isValidWarePos(wearPos) == false)
	{
		_lastError = ResponseClient::WEAR_ERR_INVALID_POS;
		return false;
	}

	// ���� ������ �Ұ���
	if ( item->IsAPet() == false
			&& item->getFlag() & FLAG_ITEM_SEALED )
	{
		_lastError = ResponseClient::WEAR_ERR_ITEM_SEAL;
		return false;
	}

	// ����ڵ� : ���� �������µ� �� ������ �Ϲ� ����
	if (item->getWearPos() == WEARING_NONE)
	{
		_lastError = ResponseClient::WEAR_ERR_CANNOT_TAKEOFF;
		return false;
	}

	return true;
}

void CWearInvenManager::Init()
{
	warePos_set_.insert(WEARING_HELMET);
	warePos_set_.insert(WEARING_ARMOR_UP);
	warePos_set_.insert(WEARING_WEAPON);
	warePos_set_.insert(WEARING_ARMOR_DOWN);
	warePos_set_.insert(WEARING_SHIELD);
	warePos_set_.insert(WEARING_GLOVE);
	warePos_set_.insert(WEARING_BOOTS);
	warePos_set_.insert(WEARING_ACCESSORY1);
	warePos_set_.insert(WEARING_ACCESSORY2);
	warePos_set_.insert(WEARING_ACCESSORY3);
	warePos_set_.insert(WEARING_PET);
	warePos_set_.insert(WEARING_BACKWING);
	warePos_set_.insert(WEARING_ACCESSORY4); // newslot - alanssoares
	warePos_set_.insert(WEARING_SPECIAL_ACCESSORY1); // newslot - alanssoares
	warePos_set_.insert(WEARING_SPECIAL_ACCESSORY2); // newslot - alanssoares
	warePos_set_.insert(WEARING_SPECIAL_ACCESSORY3); // newslot - alanssoares
	warePos_set_.insert(WEARING_SPECIAL_ACCESSORY4); // newslot - alanssoares
	warePos_set_.insert(WEARING_SPECIAL_ACCESSORY5); // newslot - alanssoares
	warePos_set_.insert(COSTUME2_WEARING_HELMET);
	warePos_set_.insert(COSTUME2_WEARING_ARMOR_UP);
	warePos_set_.insert(COSTUME2_WEARING_WEAPON);
	warePos_set_.insert(COSTUME2_WEARING_ARMOR_DOWN);
	warePos_set_.insert(COSTUME2_WEARING_SHIELD);
	warePos_set_.insert(COSTUME2_WEARING_GLOVE);
	warePos_set_.insert(COSTUME2_WEARING_BOOTS);
	warePos_set_.insert(COSTUME2_WEARING_BACK);


	m_suitWearingPos[0] = WEARING_HELMET;
	m_suitWearingPos[1] = WEARING_ARMOR_UP;
	m_suitWearingPos[2] = WEARING_WEAPON;
	m_suitWearingPos[3] = WEARING_ARMOR_DOWN;
	m_suitWearingPos[4] = WEARING_SHIELD;
	m_suitWearingPos[5] = WEARING_SHIELD;


}

bool CWearInvenManager::isValidWarePos( int pos )
{
	std::set<int>::iterator it = warePos_set_.find(pos);
	if (it == warePos_set_.end())
	{
		_lastError = ResponseClient::WEAR_ERR_INVALID_POS;
		return false;
	}

	return true;
}

void CWearInvenManager::DressNormal( CItem* item, int wearPos )
{
	//if(wearPos == 11) wearPos = 7;
	if (isValidWarePos(wearPos) == false)
	{
		LOG_ERROR("HACKING? : invalid wear pos[%d]. charIndex[%d]", wearPos, _owner->m_index);
		_owner->m_desc->Close("invalid wear pos");
		return;
	}

	if(wearItemInfo[wearPos] != NULL)
	{
		short tab = item->tab();
		short invenIndex = item->getInvenIndex();

		CItem *takeOffItem = getWearItem(wearPos);
		takeOffItem->unWearPos();
		_owner->m_wearInventory.UndressNormal(takeOffItem, wearPos);
		_owner->m_wearInventory.DressNormal(item, wearPos);
		
		if(_owner->m_inventory.isUsable(tab) == true)
		{
			_owner->m_inventory.addItemToInvenIndex(takeOffItem, tab, invenIndex);
		}
		else
		{
			_owner->m_inventory.addItem(takeOffItem);
		}
		
		_owner->ChangeQuickSlot(takeOffItem, QUICKSLOT_TYPE_ITEM);

		return ;
	}
	else
	{
		item->setWearPos(wearPos);
		wearItemInfo[wearPos] = item;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		UpdateClient::doItemWear* packet = reinterpret_cast<UpdateClient::doItemWear*>(rmsg->m_buf);
		UpdateClient::ItemWearMsg(rmsg);
		_owner->m_wearInventory.makeItemInfo(&packet->info, item);
		SEND_Q(rmsg, _owner->m_desc);
	}

	if ( (wearPos >= WEARING_SHOW_START && wearPos <= WEARING_SHOW_END)
			|| wearPos == WEARING_BACKWING )
	{
		bool isInvisibleHelmet = _owner->m_inventory.m_inventoryOptions.GetOptionValue<bool>(INVENTORY_OPTION_INVENTORY_OPTION);
		if (!(isInvisibleHelmet && wearPos == WEARING_HELMET))
		{
		CNetMsg::SP rmsg(new CNetMsg);
		WearingMsg(rmsg, _owner, wearPos, item->getDBIndex(), item->getPlus());
		_owner->m_pArea->SendToCell(rmsg, _owner, false);
		}
	}

	if(item->tab() != -1)
		_owner->m_inventory.eraseNotFree(item);
}

void CWearInvenManager::UndressNormal( CItem* item, int wearPos )
{
	//if(wearPos == 11) wearPos = 7;
	if (isValidWarePos(wearPos) == false)
	{
		LOG_ERROR("HACKING? : invalid wear pos[%d]. charIndex[%d]", wearPos, _owner->m_index);
		_owner->m_desc->Close("invalid wear pos");
		return;
	}

	item->unWearPos();
	wearItemInfo[(int)wearPos] = NULL;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		UpdateClient::ItemTakeoffMsg(rmsg, wearPos);
		SEND_Q(rmsg, _owner->m_desc);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		WearingMsg(rmsg, _owner, wearPos, -1, 0);
		_owner->m_pArea->SendToCell(rmsg, _owner, false);
	}

	if(wearPos == WEARING_WEAPON)
	{
		if(_owner->m_evocationIndex > EVOCATION_NONE)
		{
			_owner->changeToggleState(_owner->m_evocationIndex, TOGGLE_SKILL);
			_owner->ChangeEvocationState(_owner->m_evocationIndex);
		}
	}
}

void CWearInvenManager::makeItemInfo( UpdateClient::itemInfo* info, CItem* pitem)
{
	memset(info, 0x00, sizeof(*info));
	info->virtualIndex = pitem->getVIndex();
	info->dbIndex = pitem->getDBIndex();
	info->wearPos = pitem->getWearPos();
	info->plus = pitem->getPlus();
	info->plus_2 = pitem->getPlus_2();
	info->flag = pitem->getFlag();
	info->nCompositeItem = pitem->m_nCompositeItem;
	info->used = pitem->getUsed();
	info->used_2 = pitem->getUsed_2();
	info->itemCount = pitem->Count();

	if (pitem->IsOriginItem())
	{
		for (int i = 0; i < MAX_ORIGIN_OPTION; ++i)
		{
			info->origin_var[i] = pitem->getOriginVar(i);
		}
	}
	else
	{
		info->option_count = pitem->m_nOption;

		for (int i = 0; i < MAX_ITEM_OPTION; ++i)
		{
			info->option_type[i] = pitem->m_option[i].m_type;
			info->option_level[i] = pitem->m_option[i].m_level;
		}
	}

	for (int i = 0; i < MAX_SOCKET_COUNT; ++i)
	{
		info->socket[i] = pitem->m_socketList.GetJewelAt(i);
	}

#ifdef DURABILITY
	info->now_durability = pitem->getNowDurability();
	info->max_durability = pitem->getMaxDurability();
#endif
}

void CWearInvenManager::SaveWearInvenInfo(std::vector<std::string>& vec)
{
	std::string deletestr = boost::str(boost::format(
										   "delete from t_wear_inven where a_char_index = %1%") % _owner->m_index);

	vec.push_back(deletestr);

	std::string insertstr;
	insertstr.reserve(2048);

#ifdef DURABILITY
	insertstr = "INSERT INTO t_wear_inven("
				"a_char_index, a_wear_pos, a_item_idx, a_plus, a_flag, a_serial, a_used, a_used2, a_item_option0, a_item_option1, a_item_option2, a_item_option3, a_item_option4,"
				"a_item_origin_var0, a_item_origin_var1, a_item_origin_var2, a_item_origin_var3, a_item_origin_var4, a_item_origin_var5,"
				"a_socket0, a_socket1, a_socket2, a_socket3, a_socket4, a_socket5, a_socket6, a_now_dur, a_max_dur) VALUES";
#else
	insertstr = "INSERT INTO t_wear_inven("
				"a_char_index, a_wear_pos, a_item_idx, a_plus, a_flag, a_serial, a_used, a_used2, a_item_option0, a_item_option1, a_item_option2, a_item_option3, a_item_option4,"
				"a_item_origin_var0, a_item_origin_var1, a_item_origin_var2, a_item_origin_var3, a_item_origin_var4, a_item_origin_var5,"
				"a_socket0, a_socket1, a_socket2, a_socket3, a_socket4, a_socket5, a_socket6) VALUES";
#endif

	int count = 0;
	CItem* wearItem;
	//�Ϲ� ��� ���� ���̰�
	// newslot - alanssoares
	for(int i = 0; i <= WEARING_SPECIAL_ACCESSORY5; i++)
	{
		wearItem = this->wearItemInfo[i];
		makeSaveInfo( &insertstr, wearItem, &count, i );
	}
	//�ڽ�Ƭ ������ ����
	CItem* wearCostItem = _owner->m_wearInventory.getCosWearSuitItem();
	if ( wearCostItem != NULL )
	{
		makeSaveInfo( &insertstr, wearCostItem, &count, COSTUME2_WEARING_SUIT );
	}
	else
	{
		for(int i = COSTUME2_WEARING_START; i < COSTUME2_WEARING_START + MAX_COSTUME_WEARING; i++)
		{
			wearItem = this->wearItemInfo[i];
			makeSaveInfo( &insertstr, wearItem, &count, i );
		}
	}
	if (count == 0)
		return;

	int index = insertstr.rfind(",");
	insertstr.erase(index);

	vec.push_back(insertstr);
}

bool CWearInvenManager::CanDressCostum( CItem* item, int wearPos )
{
	if (item == NULL)	// �Դ� �����۵� ���� �����۵� ����.
	{
		this->_lastError = ResponseClient::WEAR_ERR_INVALID_ITEM_INFO;
		return false;
	}
	//romeost /reza
	if (wearPos < WEARING_HELMET ||  wearPos > (COSTUME2_WEARING_BACK -20)) //  wearPos > 7) //WEARING_BOOTS)
	{
	//	if(wearPos ==  WEARING_BACKWING) {
		//	wearPos = 7;  
		//}
		_lastError = ResponseClient::WEAR_ERR_INVALID_ITEM_INFO;
		return false;
	}
	/*
	if (wearPos == WEARING_WEAPON || wearPos == WEARING_SHIELD)
	{
		_lastError = ResponseClient::WEAR_ERR_INVALID_ITEM_INFO;
		return false;
	}
	*/
	/////////////////////////////////// RETURN �Ǵ� ���� �˻� ///////////////////////////////////

	if(item && item->m_itemProto->getItemFlag() & ITEM_FLAG_CASTLLAN)
	{
		int zonenum;
		char castellan;
		bool ret;
		ret = _owner->CheckCastellanType(zonenum, castellan);

		if(item->m_itemProto->getItemNum3() & 0xffff0000)  // ���ָ���� ������
		{
			if(!ret || castellan)
			{
				// ���ָ���� �ƴϴ�.
				CNetMsg::SP rmsg(new CNetMsg);
				CastllanErrorMsg(rmsg, MSG_EX_CASTLLAN_ERROR_NOT_CASTLLAN_GUILD);
				SEND_Q(rmsg, _owner->m_desc);
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			}
			if(zonenum != (item->m_itemProto->getItemNum3() & 0xffff))
			{
				// �Ҽӵ� ���� �������� �ƴ�
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			}
		}
		else		// ���ֿ� ������
		{
			if(!ret || !castellan)
			{
				// ���ָ���� �ƴϴ�.
				CNetMsg::SP rmsg(new CNetMsg);
				CastllanErrorMsg(rmsg, MSG_EX_CASTLLAN_ERROR_NOT_CASTLLAN);
				SEND_Q(rmsg, _owner->m_desc);
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			}
			if(zonenum != (item->m_itemProto->getItemNum3() & 0xffff))
			{
				// �Ҽӵ� ���� �������� �ƴ�
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
				return false;
			}
		}
	}

	if (!(item->m_itemProto->getItemFlag() & ITEM_FLAG_COSTUME2))												// �Դ¾������� COSTUME2 Flag�� �ƴϸ�.
	{
		_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
		return false;
	}

	if ((item->getFlag() & FLAG_ITEM_COMPOSITION) && 
	((item->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (item->getFlag() & FLAG_ITEM_TRANSMOGRIFY)))	// �Դ¾������� ���� �Ǿ��ų� ���� ������ �������̸�.
	{
		_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
		return false;
	}

	if (wearPos != item->m_itemProto->getItemWearing())													// �Դ� �������� �Դ� ��ġ�� wear_pos�� Ʋ����.
	{
		if(wearPos == 7 ){
			if(WEARING_BACKWING != item->m_itemProto->getItemWearing())
			{
				_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
						return false;
			}
		}
		else 
		{
			_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
									return false;
		}

		
	}

	if (!(item->m_itemProto->getItemJobFlag() & (1 << _owner->m_job)))
	{
		_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
		return false;
	}
	if ( item->getFlag() & FLAG_ITEM_SEALED )
	{
		_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
		return false;
	}
	if (item->getWearPos() != WEARING_NONE)
	{
		_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
		return false;
	}

	return true;
}

bool CWearInvenManager::CanUndressCostum( CItem* item, int wearPos )
{
	if (item == NULL)
	{
		_lastError = ResponseClient::WEAR_ERR_INVALID_ITEM_INFO;
		return false;
	}

	if (_owner->m_inventory.getEmptyCount() < 1 )
	{
		_lastError = ResponseClient::WEAR_ERR_NOT_ENOUGH_INVEN;
		return false;
	}

	if( !(item->m_itemProto->getItemFlag() & ITEM_FLAG_COSTUME2) )
	{
		this->_lastError = ResponseClient::WEAR_ERR_INVALID_ITEM_INFO;
		return false;
	}

	return true;
}

void CWearInvenManager::ApplyDeleteItem( CItem* item, int wearPos )
{
	if (isValidWarePos(wearPos) == false)
	{
		LOG_ERROR("HACKING? : invalid wear pos[%d]. charIndex[%d]", wearPos, _owner->m_index);
		_owner->m_desc->Close("invalid wear pos");
		return;
	}

	CItem* pItemNormal = item;
	if(((pItemNormal->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (pItemNormal->getFlag() & FLAG_ITEM_TRANSMOGRIFY))
	&& (pItemNormal->getFlag() & FLAG_ITEM_COMPOSITION))
	{
		pItemNormal = _owner->m_inventory.FindByVirtualIndex(pItemNormal->m_nCompositeItem);
	}
	if (pItemNormal && pItemNormal->IsOriginItem())
	{
		// �������� �ɼ� �� ��Ʈ �������� ��ų ����
		for (int i = MAX_ORIGIN_OPTION; i < MAX_ORIGIN; i++)
		{
			int nIndex = pItemNormal->GetOriginIndex(i);
			if (nIndex <= 0)
				continue;

			CSkill * pSkill = gserver->m_skillProtoList.Create(nIndex, pItemNormal->GetOriginLevel(i));
			if(pSkill)
			{
				if (pSkill->m_proto->IsActive())
				{
					//������ ��ų ��Ÿ���� ����
					{
						CSkill* skill = _owner->m_activeSkillList.Find(pSkill->m_proto->m_index);

						if(skill == NULL)
						{
							LOG_ERROR("HACKING? : invalid Skill Info. charIndex[%d], skillIndex[%d]", _owner->m_index, pSkill->m_proto->m_index);
							_owner->m_desc->Close("invalid Skill Info.");
							return;
						}

						CPC::map_t::iterator it = _owner->itemSkill.find(pSkill->m_proto->m_index);						
						if(it != _owner->itemSkill.end())
						{
							it->second = skill->m_usetime;
						}
						else
						{
							_owner->itemSkill.insert(std::pair<int, int>(pSkill->m_proto->m_index, skill->m_usetime));
						}
					}

					pSkill->Cancel(_owner);

					{
						CNetMsg::SP rmsg(new CNetMsg);
						ResponseClient::makeSkillCancelMsg(rmsg, _owner);
						_owner->m_pArea->SendToCell(rmsg, _owner, true);
					}

					_owner->RemoveSkillFromQuickSlot(pSkill);
					_owner->m_activeSkillList.Remove(pSkill);
				}
				else if (pSkill->m_proto->IsPassive())
				{
					_owner->m_passiveSkillList.Remove(pSkill);
				}
				else
				{
					_owner->m_etcSkillList.Remove(pSkill);
				}
			}
		}

		// ��Ʈ ������ ���� ���� ���� �� ��Ʈ ȿ�� ��ų ����
		if (pItemNormal->m_itemProto->GetSetIndex())
		{
			_owner->CountSetItem(pItemNormal, false);
			_owner->RemoveSetItemValue(pItemNormal);

			pItemNormal->m_nSetWearCnt = 0;
			pItemNormal->m_nSetOption = 0;
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeSkillListMsg(rmsg, _owner);
			SEND_Q(rmsg, _owner->m_desc);
		}
	}

	// �ֿϵ��� ���� ������ �ֿϵ����� disappear ��Ų��
	if (item->IsPet())
	{
		// ���� �����ۿ� �ش��ϴ� ���� ã�´�
		CPet* pet = _owner->GetPet(item->getPlus());
		if (pet)
		{
			if (pet->IsMount())
			{
				pet->Mount(false);
			}
			else
			{
				pet->Disappear();
			}
		}
	}

	if( item->IsAPet() )
	{
		CAPet* pet = _owner->GetAPet(item->getPlus());
		if( pet )
		{
			if( pet->IsMount() )
			{
				pet->Mount(false);
			}
			pet->m_nDelay = pet->m_pProto->m_nDelay ;
			// ��Ȯ�� �߻��ϴ� ��ų ���-- Ŭ���̾�Ʈ ó��
			pet->Disappear();
		}
	}

	if( item->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
			|| item->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
			|| item->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
			|| item->m_itemProto->getItemIndex() == 2610
			|| item->m_itemProto->getItemIndex() == 4940
			|| item->m_itemProto->getItemIndex() == 4941
			|| item->m_itemProto->getItemIndex() == 4942
	  )
	{
		bool bClear = true;
		for( int nAcc = 0 ; nAcc < 3 ; nAcc++ )
		{
			CItem* pAcc = _owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY1+nAcc];
			if( pAcc && ( pAcc->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM ||
						  pAcc->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM ||
						  pAcc->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM ||
						  pAcc->m_itemProto->getItemIndex() == 2610 ||
						  pAcc->m_itemProto->getItemIndex() == 4940 ||
						  pAcc->m_itemProto->getItemIndex() == 4941 ||
						  pAcc->m_itemProto->getItemIndex() == 4942 ) )
			{
				bClear = false;
				break;
			}
		}

		// newslot - alanssoares
		CItem* pAcc = _owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4];
		if ( pAcc && ( pAcc->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM ||
						pAcc->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM ||
						pAcc->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM ||
						pAcc->m_itemProto->getItemIndex() == 2610 ||
						pAcc->m_itemProto->getItemIndex() == 4940 ||
						pAcc->m_itemProto->getItemIndex() == 4941 ||
						pAcc->m_itemProto->getItemIndex() == 4942 ) )
		{
			bClear = false;
		}

		// newslot - alanssoares
		for( int nAcc = 0 ; nAcc < 5 ; nAcc++ )
		{
			CItem* pAcc = _owner->m_wearInventory.wearItemInfo[WEARING_SPECIAL_ACCESSORY1+nAcc];
			if( pAcc && ( pAcc->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM ||
						  pAcc->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM ||
						  pAcc->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM ||
						  pAcc->m_itemProto->getItemIndex() == 2610 ||
						  pAcc->m_itemProto->getItemIndex() == 4940 ||
						  pAcc->m_itemProto->getItemIndex() == 4941 ||
						  pAcc->m_itemProto->getItemIndex() == 4942 ) )
			{
				bClear = false;
				break;
			}
		}

		if( bClear )
			_owner->m_assist.CureByItemIndex(item->m_itemProto->getItemIndex());
	}
	//�˻� ��~�ϰ� ĳ������ ���� ��ų �ɼ� ����� �ʱ�ȭ ���ش�
	_owner->m_optionAttSkillList.Clear();
	_owner->m_optionDefSkillList.Clear();

	_owner->CalcStatus(true);
	//���� HP,MP�� �÷��� �� �ִ� ������ �� ���� ���� �� �ִٰ� ��.
	if(_owner->GetAPet(0))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ExAPetStatusMsg(rmsg, _owner->GetAPet());
		_owner->m_pArea->SendToCell(rmsg, _owner, true);
		SEND_Q(rmsg, _owner->m_desc);
	}
}

bool CWearInvenManager::RemoveItem( char wearPos )
{
	if (isValidWarePos(wearPos) == false)
	{
		LOG_ERROR("HACKING? : invalid wear pos[%d]. charIndex[%d]", wearPos, _owner->m_index);
		_owner->m_desc->Close("invalid wear pos");
		return false;
	}

	CItem* item = _owner->m_wearInventory.wearItemInfo[wearPos];

	if(item == NULL)
		return false;

	if(wearPos < COSTUME2_WEARING_START)
	{
		ApplyDeleteItem(item, wearPos);
		this->UndressNormal(item, wearPos);
	}
	else if(_owner->m_wearInventory.getCosWearSuitItem() != NULL)
	{
		item = this->getCosWearSuitItem();
		this->UndressCostumeSuit();
	}
	else
	{
		this->UndressCostum(item, wearPos - COSTUME2_WEARING_START);
	}

	_owner->RemoveItemFromQuickSlot(item);
	delete item;

	return true;
}

void CWearInvenManager::sendWearInfoToClient()
{
	{
		CNetMsg::SP rmsg(new CNetMsg);
		UpdateClient::doItemWearList* packet = reinterpret_cast<UpdateClient::doItemWearList*>(rmsg->m_buf);
		UpdateClient::ItemWearListMsg(rmsg);

		packet->count = 0;

		for(int i = 0; i < DEFAULT_MAX_WEARING; i++)
		{
			if( wearItemInfo[i] != NULL )
			{
				makeItemInfo(&packet->info_list[packet->count], wearItemInfo[i]);
				packet->count++;
			}
		}

		rmsg->setSize(sizeof(UpdateClient::doItemWearList) + (packet->count * sizeof(UpdateClient::itemInfo)));
		SEND_Q(rmsg, _owner->m_desc);
	}

	{
		if(this->getCosWearSuitItem() != NULL)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			UpdateClient::doItemWearCostumeSuit* packet = reinterpret_cast<UpdateClient::doItemWearCostumeSuit*>(rmsg->m_buf);
			UpdateClient::ItemWearCostumeSuitMsg(rmsg, this->getCosWearSuitItem());

			for(int i = 0, j = 0; i < MAX_COSTUME_WEARING; i++)
			{
				//LOG_INFO("i %d : j %d : MCW %d ",i, j, MAX_COSTUME_WEARING);
				switch(i) {
					case COSTUME2_WEARING_HELMET:
					break;
					case COSTUME2_WEARING_ARMOR_UP:
					break;
					case COSTUME2_WEARING_WEAPON:
					break;
					case COSTUME2_WEARING_ARMOR_DOWN:
					break;
					case COSTUME2_WEARING_SHIELD:
					break;
					case COSTUME2_WEARING_GLOVE:
					break;
					case COSTUME2_WEARING_BOOTS:
					break;
					case COSTUME2_WEARING_BACK:
					break;
				}
				if ( wearItemInfo[i + COSTUME2_WEARING_START] != NULL )
				{
					makeItemInfo(&packet->info_list[j], wearItemInfo[i + COSTUME2_WEARING_START]);
					j++;
				}
			}

			rmsg->setSize(sizeof(UpdateClient::doItemWearCostumeSuit) + COSTUME2_SUIT_MAX_WEARING * sizeof(UpdateClient::itemInfo));
			SEND_Q(rmsg, _owner->m_desc);
		}
		else
		{
			CNetMsg::SP rmsg(new CNetMsg);
			UpdateClient::doItemWearCostumeList* packet = reinterpret_cast<UpdateClient::doItemWearCostumeList*>(rmsg->m_buf);
			UpdateClient::ItemWearCostumeListMsg(rmsg);

			packet->count = 0;

			for(int i = COSTUME2_WEARING_START; i < COSTUME2_WEARING_START + MAX_COSTUME_WEARING; i++)
			{
				if ( wearItemInfo[i] != NULL )
				{
					makeItemInfo(&packet->info_list[packet->count], wearItemInfo[i]);
					packet->count++;
				}
			}

			rmsg->setSize(sizeof(UpdateClient::doItemWearCostumeList) + packet->count * sizeof(UpdateClient::itemInfo));
			SEND_Q(rmsg, _owner->m_desc);
		}
	}
}

CItem* CWearInvenManager::FindByVirtualIndex( int vIndex )
{
	for(int i = 0; i < MAX_WEARING; i++)
	{
		if(wearItemInfo[i] == NULL)
			continue;

		if(wearItemInfo[i]->getVIndex() == vIndex)
		{
			return wearItemInfo[i];
		}
	}
	return NULL;
}

void CWearInvenManager::DressCostumSuit(CItem* pSuit)
{
	//������ ����
	setCosWearSuitItem(pSuit);
	//������ ����
	getCosWearSuitItem()->setWearPos(COSTUME2_WEARING_SUIT);


	//�����ǻ��� �������� �����Ͽ� ������ �ɼ� ���� �� ���� ���� ������Ʈ
	CItem* pItem = NULL;
	int itemIndex = -1;
	bool bWearing = false;
	for( int i = 0; i < COSTUME2_SUIT_MAX_WEARING; i++ )
	{
		itemIndex = pSuit->GetOriginIndex(i-1);
		CItemProto* proto = gserver->m_itemProtoList.FindIndex(itemIndex);
		if (!proto)
		{
			GAMELOG << init("SYS_ERR")
					<< "DressCostumeSuit proto NULL"
					<< pSuit->getDBIndex()
					<< itemIndex;
			continue;
		}

		pItem = new CItem();
		pItem->setItemProto(proto);
		pItem->setDBIndex(proto->getItemIndex());
		pItem->setWearPos(proto->getItemWearing());
		pItem->setUsed(pSuit->getUsed());
		if (pItem->IsOriginItem())
		{
			for (int i = 0; i < MAX_ORIGIN_OPTION; i++)
			{
				if(pItem->GetOriginIndex(i) >= 0)
				{
					pItem->setOriginVar(i, 100);
				}
			}
		}
		wearItemInfo[pItem->getWearPos() + COSTUME2_WEARING_START] = pItem;
		bWearing = true;
	}

	//���� ���� ����
	if (bWearing)
	{
		int skill_index = 0, skill_level = 0;
		gserver->m_Fortunelist.Resolve_fortune_value(skill_index, skill_level, pSuit->getPlus());
		CSkill *pSkill = gserver->m_skillProtoList.Create(skill_index, skill_level);
		bool bApply = false;
		if(pSkill)
		{
			ApplySkill(_owner, _owner, pSkill, -1, bApply);
			if(!bApply && pSkill)
			{
				delete pSkill;
				pSkill = NULL;
			}
		}
	}

	//��Ŷ ����
	{
		CNetMsg::SP rmsg(new CNetMsg);
		UpdateClient::ItemWearCostumeSuitMsg(rmsg, pSuit);
		prepareSuitMsg(rmsg, _owner);
		SEND_Q(rmsg, _owner->m_desc);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		CostumeWearingSuitMsg(rmsg, _owner);
		_owner->m_pArea->SendToCell(rmsg, _owner, false);
	}
}

void CWearInvenManager::UndressCostumeSuit()
{
	//���� �������� ���� �ɼ� ����
	int skill_index = 0, skill_level = 0;
	gserver->m_Fortunelist.Resolve_fortune_value(skill_index, skill_level, getCosWearSuitItem()->getPlus());
	_owner->m_assist.CureBySkillIndex(skill_index);

	getCosWearSuitItem()->unWearPos();
	setCosWearSuitItem(NULL);

	for( int i = COSTUME2_WEARING_START; i < COSTUME2_WEARING_START + MAX_COSTUME_WEARING; i++ )
	{
		if( wearItemInfo[i] == NULL )
			continue;

		ApplyDeleteItem(wearItemInfo[i], i);

		delete wearItemInfo[i];
		wearItemInfo[i] = NULL;
	}

	//���� ���� ��Ŷ ����
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::CostSuitItemTakeOffMsg(rmsg, GetLastError());
		SEND_Q(rmsg, _owner->m_desc);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		CostumeWearingSuitMsg(rmsg, _owner);
		_owner->m_pArea->SendToCell(rmsg, _owner, false);
	}
}

void CWearInvenManager::UndressCostumeAll()
{
	for( int i = COSTUME2_WEARING_START; i < COSTUME2_WEARING_START + MAX_COSTUME_WEARING; i++ )
	{
		if( wearItemInfo[i] == NULL )
			continue;

		ApplyDeleteItem(wearItemInfo[i], i);
		_owner->m_inventory.addItem(wearItemInfo[i]);
		UndressCostum(wearItemInfo[i], wearItemInfo[i]->getWearPos());

		_owner->ChangeQuickSlot(wearItemInfo[i], QUICKSLOT_TYPE_ITEM);
	}
}

void CWearInvenManager::DressCostum( CItem* item, int wearPos )
{
	if(wearPos == 11) 
		wearPos = 7;

	if (isValidWarePos(wearPos + COSTUME2_WEARING_START) == false)
	{
		LOG_ERROR("HACKING? : invalid wear pos[%d]. charIndex[%d]", wearPos + COSTUME2_WEARING_START, _owner->m_index);
		_owner->m_desc->Close("invalid wear pos");
		return;
	}

	if(wearItemInfo[wearPos + COSTUME2_WEARING_START] != NULL)
	{
		short tab = item->tab();
		short invenIndex = item->getInvenIndex();

		CItem* takeOffItem = getWearItem(wearPos + COSTUME2_WEARING_START);
		takeOffItem->unWearPos();

		_owner->m_wearInventory.UndressCostum(takeOffItem, wearPos);
		_owner->m_wearInventory.DressCostum(item, wearPos);
		
		if(_owner->m_inventory.isUsable(tab) == true)
		{
			_owner->m_inventory.addItemToInvenIndex(takeOffItem, tab, invenIndex);
		}
		else
		{
			_owner->m_inventory.addItem(takeOffItem);
		}
		
		_owner->ChangeQuickSlot(takeOffItem, QUICKSLOT_TYPE_ITEM);

		return;
	}
	else
	{
		item->setWearPos(wearPos);
		wearItemInfo[(int)wearPos + COSTUME2_WEARING_START] = item;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		UpdateClient::doItemWearCostume* packet = reinterpret_cast<UpdateClient::doItemWearCostume*>(rmsg->m_buf);
		UpdateClient::ItemWearCostumeMsg(rmsg);
		_owner->m_wearInventory.makeItemInfo(&packet->info, item);
		SEND_Q(rmsg, _owner->m_desc);
	}

	bool isInvisibleHelmet = _owner->m_inventory.m_inventoryOptions.GetOptionValue<bool>(INVENTORY_OPTION_INVENTORY_OPTION);
	if(!(isInvisibleHelmet && wearPos == WEARING_HELMET))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CostumeWearingMsg(rmsg, _owner, wearPos, item->getDBIndex());
		_owner->m_pArea->SendToCell(rmsg, _owner, false);
	}
	this->dressCostumCount++;

	if(item->tab() != -1)
		_owner->m_inventory.eraseNotFree(item);
}

void CWearInvenManager::UndressCostum( CItem* item, int wearPos )
{


	if (wearPos == 11 ) wearPos= 7 ;

	if (isValidWarePos(wearPos + COSTUME2_WEARING_START) == false)
	{
		LOG_ERROR("HACKING? : invalid wear pos[%d]. charIndex[%d]", wearPos + COSTUME2_WEARING_START, _owner->m_index);
		_owner->m_desc->Close("invalid wear pos");
		return;
	}

	item->unWearPos();
	wearItemInfo[(int)wearPos + COSTUME2_WEARING_START] = NULL;

	//���� ���� ������ �ɼ� ����
	ApplyDeleteItem(item, wearPos);

	{
		CNetMsg::SP rmsg(new CNetMsg);
		UpdateClient::ItemWearCostumeTakeoffMsg(rmsg, wearPos);
		SEND_Q(rmsg, _owner->m_desc);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		CostumeWearingMsg(rmsg, _owner, wearPos, -1);
		_owner->m_pArea->SendToCell(rmsg, _owner, false);
	}

	//�����ϰ� �ִ� �ڽ�Ƭ ���� ���� ����
	this->dressCostumCount--;
}

bool CWearInvenManager::AddCostumSuitItem( CItem *item )
{
	//��ȿ�� �˻�
	if(CanDressCostumSuit(item) == false)
	{
		return false;
	}

	//�ѹ� �ǻ��� �԰� �ִ� ���
	if( NULL != getCosWearSuitItem() )
	{
		//�ѹ��ǻ� ����
		if(DelCostumSuitItem(item->tab(), item->getInvenIndex()) == false)
		{
			return false;
		}
	}
	//���� �ڽ�Ƭ �ǻ��� �԰� �ִ� ���(�ϴ� ȸ��)
	else if( dressCostumCount > 0 )
	{
		//���� ������ �Ϸ��� �κ��丮 �˻�
		if(_owner->m_inventory.getEmptyCount() < dressCostumCount )
		{
			return false;
		}
		//�����ǻ� ��� ���� ����
		UndressCostumeAll();
		DressCostumSuit(item);
		_owner->m_inventory.eraseNotFree(item);
	}
	else
	{
		DressCostumSuit(item);
		_owner->m_inventory.eraseNotFree(item);
	}

	_owner->CalcStatus(true);

	return true;
}

bool CWearInvenManager::DelCostumSuitItem(short tab, short invenIndex)
{
	CItem* item = wearSuitItem;

	if (CanUndressCostumSuit(item) == false)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::doItemWearError *packet = reinterpret_cast<ResponseClient::doItemWearError*>(rmsg->m_buf);
		ResponseClient::ItemTakeoffMsg(rmsg, GetLastError());
		SEND_Q(rmsg, _owner->m_desc);
		return false;
	}

	if (tab >= 0 && invenIndex >= 0)
	{
		//�巡�� �� ������� �������� ���� ��쿡�� �κ��丮���� �ش� ��ġ�� �������� �����ͼ� �� �� �� ó��
		CItem* dressItem = _owner->m_inventory.getItem(tab, invenIndex);
		if(dressItem == NULL)
		{
			UndressCostumeSuit();
			_owner->m_inventory.addItemToInvenIndex(item, tab, invenIndex);
		}
		else if( (dressItem->m_itemProto->getItemFlag() & ITEM_FLAG_COSTUME2) == false )
		{
			UndressCostumeSuit();
			_owner->m_inventory.addItem(item);
		}
		else if( (dressItem->m_itemProto->getItemWearing() == item->m_itemProto->getItemWearing()) && dressItem->m_itemProto->getItemJobFlag() & (1 << _owner->m_job) )
		{
			UndressCostumeSuit();
			DressCostumSuit(dressItem);
			_owner->m_inventory.eraseNotFree(dressItem);

			if(_owner->m_inventory.isUsable(tab) == true)
			{
				_owner->m_inventory.addItemToInvenIndex(item, tab, invenIndex);
			}
			else
			{
				_owner->m_inventory.addItem(item);
			}
		}
		else
		{
			this->_lastError = ResponseClient::WEAR_ERR_CANNOT_WEAR;
			return false;
		}
	}
	else
	{
		UndressCostumeSuit();
		_owner->m_inventory.addItem(item);
	}

	_owner->ChangeQuickSlot(item, QUICKSLOT_TYPE_ITEM);

	_owner->CalcStatus(true);

	return true;
}

CItem* CWearInvenManager::getCosWearSuitItem()
{
	return wearSuitItem;
}

void CWearInvenManager::setCosWearSuitItem( CItem* item )
{
	wearSuitItem = item;
}

void CWearInvenManager::makeSaveInfo( std::string* insertstr, CItem* wearItem, int* count, int wearPos )
{
	//wearItem = _owner->m_wearInventory.wearItemInfo[i];
	if(wearItem != NULL)
	{
		int used = 0;
		if (wearItem->m_itemProto->getItemFlag() & ITEM_FLAG_ABS)
		{
			// �ð��� ������
			if( wearItem->m_itemProto->getItemTypeIdx() == ITYPE_ETC
					&& wearItem->m_itemProto->getItemSubTypeIdx() == IETC_MONSTER_MERCENARY_CARD )
			{
				used = wearItem->getUsed();
			}
			else
			{
				used = wearItem->getUsed() - gserver->getNowSecond();
			}

		}
		else
		{
			used = wearItem->getUsed();
		}

		*insertstr += boost::str(boost::format(
									 "(%1%, %2%, %3%, %4%, %5%,"
									 " '%6%', %7%, %8% ")
								 % _owner->m_index % wearPos % wearItem->getDBIndex() % wearItem->GetItemPlus() % wearItem->getFlag()
								 % wearItem->m_serial % used % wearItem->getUsed_2()
								);
		if (((wearItem->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (wearItem->getFlag() & FLAG_ITEM_TRANSMOGRIFY))
		&& (wearItem->getFlag() & FLAG_ITEM_COMPOSITION))
		{
			// ���յ� �ǻ� �������� ���յ� �Ϲ� �������� virtualIndex�� ������ ����
			CItem* pItemEquip = _owner->m_inventory.FindByVirtualIndex(wearItem->m_nCompositeItem);
			if (pItemEquip)
			{
				// option 0 : row, option 1 : col
				int row = pItemEquip->tab();
				int col = pItemEquip->getInvenIndex();
				*insertstr += boost::str(boost::format(", %d, %d") % row % col);
			}
			else
			{
				*insertstr += ", 0, 0";

				LOG_ERROR("Not found item [%d]", wearItem->m_nCompositeItem);
			}

			for (int j = 2; j < MAX_ITEM_OPTION; ++j)
			{
				*insertstr += ", 0";
			}
		}
		else
		{
			bool bIsRare = (wearItem->IsRareItem()) ? true : false;

			if (bIsRare)
			{
				int start = 0;
				if (wearItem->m_nOption == 2)
				{
					*insertstr += boost::str(boost::format(", %d, %d")
											 % wearItem->m_nRareOptionIndex % wearItem->m_nRareOptionBit);

					start = 2;
				}

				for (int j = start; j < MAX_ITEM_OPTION; ++j)
				{
					*insertstr += ",0";
				}
			}
			else
			{
				for (int j = 0; j < MAX_ITEM_OPTION; ++j)
				{
					int temp = 0;
					if (wearItem->m_option[j].m_level > 0)
					{
						wearItem->m_option[j].SetDBValue();
						temp = wearItem->m_option[j].m_dbValue;
					}

					*insertstr += boost::str(boost::format(", %d") % temp);
				}
			}
		}
		for (int j = 0; j < MAX_VARIATION_COUNT; ++j)
		{
			*insertstr += boost::str(boost::format(", %d") % wearItem->getOriginVar(j));
		}
		for (int j = 0; j < MAX_SOCKET_COUNT; ++j)
		{
			if(wearItem->m_socketList.m_socketpos != NULL)
			{
				*insertstr += boost::str(boost::format(", %d") % wearItem->m_socketList.m_socketpos[j].GetJewelDBIdx());
			}
			else
				*insertstr += ", -1";

		}

#ifdef DURABILITY
		*insertstr += boost::str(boost::format(",%d,%d") % wearItem->getNowDurability() % wearItem->getMaxDurability());
#endif

		*insertstr += "), ";
		(*count) ++;
	}
}

bool CWearInvenManager::CanDressCostumSuit( CItem* item )
{
	if(item == NULL)
	{
		_lastError = ResponseClient::WEAR_ERR_INVALID_ITEM_INFO;
		return false;
	}
	if( !(item->m_itemProto->getItemFlag() & ITEM_FLAG_COSTUME2) )
	{
		_lastError = ResponseClient::WEAR_ERR_INVALID_ITEM_INFO;
		return false;
	}
	return true;
}

bool CWearInvenManager::CanUndressCostumSuit( CItem* item )
{
	if(item == NULL)
	{
		this->_lastError = ResponseClient::WEAR_ERR_CANNOT_TAKEOFF;
		return false;
	}

	if(_owner->m_inventory.getEmptyCount() < 1)
	{
		this->_lastError = ResponseClient::WEAR_ERR_NOT_ENOUGH_INVEN;
		return false;
	}

	if( !(item->m_itemProto->getItemFlag() & ITEM_FLAG_COSTUME2) )
	{
		this->_lastError = ResponseClient::WEAR_ERR_INVALID_ITEM_INFO;
		return false;
	}
	return true;
}

CItem* CWearInvenManager::FindByDBIndex( int index )
{
	for (int i = 0; i < MAX_WEARING; i++)
	{
		if (wearItemInfo[i] == NULL)
			continue;

		CItem* pItem = wearItemInfo[i];
		if(pItem->getDBIndex() == index)
		{
			return pItem;
		}
	}

	return NULL;
}

bool CWearInvenManager::isSyndicateEquipment()
{
	for (int i = 0; i < MAX_WEARING; ++i)
	{
		if (wearItemInfo[i] == NULL)
			continue;

		CItem* pItem = wearItemInfo[i];
		if (pItem->isSyndicate())
		{
			return true;
		}
	}
	return false;
}

CItem* CWearInvenManager::getCalcWear( int index )
{
	CItem* item = wearItemInfo[index];
	if (item == NULL)
		return NULL;

	if (item->getFlag() & FLAG_ITEM_SEALED) // ����
		return NULL;

#ifdef DURABILITY
	if (item->m_itemProto->getItemFlag() & ITEM_FLAG_DURABILITY)
	{
		if (item->getNowDurability() < 10)
			return NULL;
	}
#endif

	// ���� �˻�
	if (((item->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (item->getFlag() & FLAG_ITEM_TRANSMOGRIFY))
	&& (item->getFlag() & FLAG_ITEM_COMPOSITION))
	{
#ifdef DURABILITY
		CItem* tItem = _owner->m_inventory.FindByVirtualIndex(item->m_nCompositeItem);
		if (tItem == NULL)
			return NULL;

		if (tItem->m_itemProto->getItemFlag() & ITEM_FLAG_DURABILITY)
		{
			if (tItem->getNowDurability() < 10)
				return NULL;
		}
#else
		if (_owner->m_inventory.FindByVirtualIndex(item->m_nCompositeItem) == NULL)
			return NULL;
#endif
	}

	return item;
}

void CWearInvenManager::searchWearItem( wearItem_search_t& vec )
{
	for (int i = 0; i < DEFAULT_MAX_WEARING; ++i)
	{
		if (wearItemInfo[i] == NULL)
			continue;

		if(wearItemInfo[i]->getWearPos() == WEARING_NONE)
			continue;

		wearItem_search_pair_t pair;
		pair.wearpos = i;
		pair.pItem = wearItemInfo[i];
		vec.push_back(pair);
	}
}

#ifdef HARDCORE_SERVER

extern ExpressSystemItemInfo* makeExpressSystemItemInfo(CItem* pItem, int itemCount, int sendType, const char* sendName);

void CWearInvenManager::sendToLCE_Only_hardcore()
{
	for(int i = 0; i < MAX_WEARING; ++i)
	{
		if(wearItemInfo[i] == NULL)
			continue;

		CItem* pItem = wearItemInfo[i];

		// LCE�� ������ ���ƾ��� ������
		// �Ⱓ��
		if (pItem->m_itemProto->isTimer())
			continue;

		// ĳ��
		if (pItem->m_itemProto->getItemFlag() & ITEM_FLAG_CASH)
			continue;

		// ����
		if (((pItem->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (pItem->getFlag() & FLAG_ITEM_TRANSMOGRIFY))
		&& (pItem->getFlag() & FLAG_ITEM_COMPOSITION))
			continue;

		// ��ȭ
		if (pItem->getPlus() > 0)
			continue;

		// ��
		if (pItem->IsPet() || pItem->IsAPet())
			continue;

		// �뿩
		if (pItem->IsLent())
			continue;

		// ����
		if (pItem->m_itemProto->getItemFlag() & FLAG_ITEM_SEALED)
			continue;

		{
			// ����
			if (pItem->m_itemProto->getItemFlag() & ITEM_FLAG_LORD)
				continue;

			if (pItem->m_itemProto->getItemFlag() & ITEM_FLAG_CASTLLAN)
				continue;
		}

		pItem->unWearPos();

		ExpressSystemItemInfo* expressItem = makeExpressSystemItemInfo(pItem, pItem->Count(), EXPRESS_SEND_UNSEARCHABLE_STONESTATUS, "HARDCORE");
		DBManager::instance()->PushExpressSendItemToNickName(_owner->m_desc, expressItem, (const char *)_owner->m_nick, EXPRESS_SENDER_TYPE_WEAR_INVENTORY);

		delete wearItemInfo[i];
		wearItemInfo[i] = NULL;
	}
}
#endif

void CWearInvenManager::sendOneItemInfo( int wearPos )
{
	if (isValidWarePos(wearPos) == false)
	{
		LOG_ERROR("HACKING? : invalid wear pos[%d]. charIndex[%d]", wearPos, _owner->m_index);
		_owner->m_desc->Close("invalid wear pos");
		return;
	}

	CNetMsg::SP rmsg(new CNetMsg);
	UpdateClient::doItemWearChangeInfo* packet = reinterpret_cast<UpdateClient::doItemWearChangeInfo*>(rmsg->m_buf);
	packet->type = MSG_UPDATE_DATA_FOR_CLIENT;
	packet->subType = MSG_SUB_UPDATE_WEAR_CHANGE_INFO;
	this->makeItemInfo(&packet->info, wearItemInfo[wearPos]);
	rmsg->setSize(sizeof(UpdateClient::doItemWearChangeInfo));
	SEND_Q(rmsg, _owner->m_desc);
}

void CWearInvenManager::checkItemTime()
{
	for (int i = 0; i < MAX_WEARING; ++i)
	{
		CItem* pItem = wearItemInfo[i];
		if (pItem == NULL)
			continue;

		if ((pItem->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE )
				&& pItem->m_itemProto->getItemNum4() == - 1)
		{
			// �Ⱓ ������ ������
			continue;
		}

		if((pItem->getDBIndex() >= 4927 && pItem->getDBIndex() <= 4932) || pItem->getDBIndex() == 6228)
		{
			// �ҷ��� �̺�Ʈ ȣ�ڸӸ� �Ⱓ ������ ����
			if((pItem->m_itemProto->getItemFlag() & ITEM_FLAG_ABS) &&
					(pItem->getUsed() < gserver->getNowSecond()))
			{
				GAMELOG << init("CLOTHES EXPIRE", _owner)
						<< itemlog(pItem)
						<< end;

				_owner->m_wearInventory.RemoveItem(i);
				continue;
			}
		}
		else if (pItem->m_itemProto->getItemFlag() & ITEM_FLAG_COSTUME2)
		{
			if(pItem->getUsed() < gserver->getNowSecond())
			{
				GAMELOG << init("COSTUME2 CLOTHES EXPIRE", _owner)
						<< itemlog(pItem)
						<< end;

				{
					CNetMsg::SP rmsg(new CNetMsg);
					SysExpireCostumeItem(rmsg, pItem->getDBIndex());
					SEND_Q(rmsg, _owner->m_desc);
				}

				_owner->m_wearInventory.RemoveItem(i);

				continue;
			}
		}
		// �뿩 ����
		else if (pItem->IsLent())
		{
			if (pItem->getUsed() < gserver->getNowSecond())
			{
				// ������ ���� �� ����
				GAMELOG << init("ITEM USE TIMEOUT", _owner)
						<< "ITEM" << delim
						<< itemlog(pItem)
						<< end;

				{
					CNetMsg::SP rmsg(new CNetMsg);
					ItemLendWeaponMsg(rmsg, pItem->getDBIndex(), MSG_ITEM_LEND_TIMEOUT);
					SEND_Q(rmsg, _owner->m_desc);
				}

				_owner->m_wearInventory.RemoveItem(i);
				continue;
			}
		}// �뿩 ����
		// ���� �ǻ�
		else if ((pItem->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (pItem->getFlag() & FLAG_ITEM_TRANSMOGRIFY))
		{
			// ���� �ǻ� üũ�� �÷�Ƽ������ ���� �־�� ��
			// �ǻ� �÷�Ƽ�� �ƽ� �÷��� ��� -_-;
			// ���տ� �ǻ� ������
			// ���յ� ������
			if (!(pItem->m_itemProto->getItemFlag() & ITEM_FLAG_ABS))
			{
				// �Ⱓ��
				if (pItem->getUsed_2() > 0
						&& pItem->getUsed_2() < gserver->getNowSecond())
				{
					// ���� �ֹ��� �ð� ����
					// ������ �������� �ִ°�?
					// ������ ������ �����ϰ�
					// ���� ���̸� ���� �����ϰ�
					// �κ��� ����
					if (pItem->getFlag() & FLAG_ITEM_COMPOSITION)
					{
						CItem * pItemEquip = _owner->m_inventory.FindByVirtualIndex(pItem->m_nCompositeItem);
						if (pItemEquip)
						{
							pItemEquip->setFlag(pItemEquip->getFlag() & ~FLAG_ITEM_COMPOSITION);
							_owner->m_inventory.sendOneItemInfo(pItemEquip);

							GAMELOG << init("ITEM SEPARATE", _owner)
									<< "CLOTHES" << delim
									<< itemlog(pItem) << delim
									<< "EQUIP" << delim
									<< itemlog(pItemEquip)
									<< end;
						}

						GAMELOG << init("COMPOSITE_TIME EXPIRE", _owner)
								<< itemlog(pItem)
								<< end;

						{
							CNetMsg::SP rmsg(new CNetMsg);
							SysExpireItemcompositeMsg(rmsg, pItem->getDBIndex());
							SEND_Q(rmsg, _owner->m_desc);
						}
						RemoveItem(i);
					}
				}	// ���յ� ������
			}

			if (pItem->getUsed() < gserver->getNowSecond())
			{
				// ���� �ǻ� �ð� ����
				// ������ �������� �ִ°�?
				// ������ ������ �����ϰ�
				// ���� ���̸� ���� �����ϰ�
				// �κ����� ����
				if (pItem->getFlag() & FLAG_ITEM_COMPOSITION)
				{
					pItem->setFlag(pItem->getFlag() & ~FLAG_ITEM_COMPOSITION);

					CItem* pItemEquip = _owner->m_inventory.FindByVirtualIndex(pItem->m_nCompositeItem);
					if (pItemEquip)
					{
						pItemEquip->setFlag(pItemEquip->getFlag() & ~FLAG_ITEM_COMPOSITION);

						_owner->m_inventory.sendOneItemInfo(pItemEquip);

						GAMELOG << init("ITEM SEPARATE", _owner)
								<< "CLOTHES" << delim
								<< itemlog(pItem) << delim
								<< "EQUIP" << delim
								<< itemlog(pItemEquip)
								<< end;
					}
				}
				GAMELOG << init("CLOTHES EXPIRE", _owner)
						<< itemlog(pItem)
						<< end;

				{
					CNetMsg::SP rmsg(new CNetMsg);
					SysExpireItemcompositeMsg(rmsg, pItem->getDBIndex());
					SEND_Q(rmsg, _owner->m_desc);
				}

				this->RemoveItem(i);
				continue;
			}
		} //���� �ǻ�
		else if( pItem->IsUsedPlatinumSpecial() )
		{
			if (pItem->getUsed() < gserver->getNowSecond())
			{
				// ���� �� ����
				int platinumPlus = pItem->getFlag() & PLATINUM_MAX_PLUS;
				pItem->setPlus(pItem->getPlus() - platinumPlus);

				if(pItem->getPlus() <= 0) // LC-TR-P20100428-018 ���� ���� ���� ( �÷�Ƽ�� �Ⱓ ����� 0 ���� �۰� �Ǵ� ��� ����)
				{
					pItem->setPlus(0);
				}

				pItem->setUsed(-1);

				GAMELOG << init("PLATINUM USE TIMEOUT", _owner)
					<< "ITEM" << delim
					<< itemlog(pItem) << delim
					<< platinumPlus << delim
					<< end;

				pItem->setFlag(FLAG_ITEM_PLATINUM_SET(pItem->getFlag(), 0));

				this->sendOneItemInfo(pItem->getWearPos());

				{
					CNetMsg::SP rmsg(new CNetMsg);
					ResponseClient::ItemNotUseMsg(rmsg, MSG_ITEM_USE_ERROR_PLATINUM_SPECIAL_EXPIRE, 0, 0, pItem->m_itemProto->getItemIndex());
					SEND_Q(rmsg, _owner->m_desc);
				}

				bool isInvisibleHelmet = _owner->m_inventory.m_inventoryOptions.GetOptionValue<bool>(INVENTORY_OPTION_INVENTORY_OPTION);
				if (!(isInvisibleHelmet && pItem->m_itemProto->getItemWearing() == WEARING_HELMET))
				{
					CNetMsg::SP rmsg(new CNetMsg);
					WearingMsg(rmsg, _owner, pItem->getWearPos(), pItem->getDBIndex(), pItem->getPlus());
					_owner->m_pArea->SendToCell(rmsg, _owner, false);
				}

				_owner->m_assist.CheckApplyConditions();
				_owner->CalcStatus(true);

				continue;
			}
		} // �÷�Ƽ��

		switch (pItem->m_itemProto->getItemIndex())
		{
		case ONE_PERIOD_ITEM:
		case SEVEN_PERIOD_ITEM:
		case THIRTY_PERIOD_ITEM:
		case 2610:
		case 4940:
		case 4941:
		case 4942:
			{
				if( pItem->getUsed() != -1
						&& pItem->getUsed() < gserver->getNowSecond())
				{
					// �Ⱓ ����
					// ������ ���� �� ����
					GAMELOG << init("ITEM USE TIMEOUT", _owner)
							<< "ITEM" << delim
							<< itemlog(pItem)
							<< end;
					for( int k = WEARING_ACCESSORY1; k <= WEARING_ACCESSORY3; k++ )
					{
						if (_owner->m_wearInventory.wearItemInfo[k])
						{
							if( _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
									|| _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
									|| _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
									|| _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 2610
									|| _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4940
									|| _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4941
									|| _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4942
							  )
							{
								char wear_pos = _owner->m_wearInventory.wearItemInfo[k]->getWearPos();
								_owner->m_assist.CureByItemIndex(_owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex());
								_owner->m_wearInventory.RemoveItem(k);
							}
						}
					}

					// newslot - alanssoares
					if (_owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4])
					{
						if( _owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
								|| _owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
								|| _owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
								|| _owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 2610
								|| _owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 4940
								|| _owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 4941
								|| _owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex() == 4942
							)
						{
							char wear_pos = _owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->getWearPos();
							_owner->m_assist.CureByItemIndex(_owner->m_wearInventory.wearItemInfo[WEARING_ACCESSORY4]->m_itemProto->getItemIndex());
							_owner->m_wearInventory.RemoveItem(WEARING_ACCESSORY4);
						}
					}

					// newslot - alanssoares
					for( int k = WEARING_SPECIAL_ACCESSORY1; k <= WEARING_SPECIAL_ACCESSORY5; k++ )
					{
						if (_owner->m_wearInventory.wearItemInfo[k])
						{
							if( _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == ONE_PERIOD_ITEM
									|| _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == SEVEN_PERIOD_ITEM
									|| _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == THIRTY_PERIOD_ITEM
									|| _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 2610
									|| _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4940
									|| _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4941
									|| _owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex() == 4942
							  )
							{
								char wear_pos = _owner->m_wearInventory.wearItemInfo[k]->getWearPos();
								_owner->m_assist.CureByItemIndex(_owner->m_wearInventory.wearItemInfo[k]->m_itemProto->getItemIndex());
								_owner->m_wearInventory.RemoveItem(k);
							}
						}
					}

					continue;
				}
			}
			break;
		}

		// ATTACK_PET  ���� ������ �ð� üũ
		if( ( pItem->m_itemProto->getItemJobFlag()&(1<<JOB_APET) ) &&
				( pItem->m_itemProto->getItemFlag()&ITEM_FLAG_ABS) )
		{
			if (pItem->getUsed() < gserver->getNowSecond())
			{
				// AI �������� AI ����Ʈ������ ����
				if (pItem->m_itemProto->getItemTypeIdx() == ITYPE_ETC && pItem->m_itemProto->getItemSubTypeIdx() == IETC_PET_AI)
				{
					CAPet * pAPetNetxt = _owner->m_pApetlist;
					CAPet * pAPet;
					while((pAPet = pAPetNetxt))
					{
						pAPetNetxt = pAPet->m_pNextPet;
						pAPet->DelAIList(pItem);
					}

					pAPet = _owner->GetAPet();
					if (pAPet)
					{
						CNetMsg::SP rmsg(new CNetMsg);
						APetAIListMsg(rmsg, pAPet);
						SEND_Q(rmsg, _owner->m_desc);
					}
				}
				// ������ ���� �� ����
				GAMELOG << init("ITEM USE TIMEOUT ATTACK_PET", _owner)
						<< "ITEM" << delim
						<< itemlog(pItem)
						<< end;

				RemoveItem(i);
				continue;
			}
		}

		if( (pItem->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY) && (pItem->m_itemProto->getItemNum4() > 0) )
		{
			if (pItem->getUsed() < gserver->getNowSecond())
			{
				GAMELOG << init("ACCESSORY DELETE", _owner)
						<< itemlog(pItem)
						<< end;

				switch(pItem->getDBIndex())
				{
				case ARTIFACT_LEVEL1_ITEM_INDEX:
				case ARTIFACT_LEVEL2_ITEM_INDEX:
				case ARTIFACT_LEVEL3_ITEM_INDEX:
					{
						ArtifactManager::instance()->expire_time(pItem);
					}
					break;
				}

				_owner->m_wearInventory.wearItemInfo[(int)pItem->getWearPos()] = NULL;
				RemoveItem(i);
				continue;
			}
		}

		if((pItem->m_itemProto->getItemFlag() & ITEM_FLAG_TRIGGER))
		{
			if (pItem->getUsed() < gserver->getNowSecond() && _owner->m_pZone )
			{
				GAMELOG << init("TRIGGER ITEM DELETE", _owner)
						<< itemlog(pItem)
						<< end;

				RemoveItem(i);
				continue;
			}
		}

#if defined(LC_TLD)
		if (!gserver->isActiveEvent(A_EVENT_HALLOWEEN) && (pItem->getDBIndex() >= 2482 && pItem->getDBIndex() <= 2491))
		{
			GAMELOG << init("HALLOWEEN EVENT END DELETE ITEM", _owner) << itemlog(pItem) << end;

			RemoveItem(i);
			continue;
		}

#elif defined(LC_GAMIGO)
		if (!gserver->isActiveEvent(A_EVENT_HALLOWEEN) && ((pItem->getDBIndex() >= 2464 && pItem->getDBIndex() <= 2475) || (pItem->getDBIndex() >= 2488 && pItem->getDBIndex() <= 2491)))
		{
			GAMELOG << init("HALLOWEEN EVENT END DELETE ITEM", _owner) << itemlog(pItem) << end;

			RemoveItem(i);
			continue;
		}
#else
		if (!gserver->isActiveEvent(A_EVENT_HALLOWEEN) && (pItem->getDBIndex() >= 2488 && pItem->getDBIndex() <= 2491))
		{
			GAMELOG << init("HALLOWEEN EVENT END DELETE ITEM", _owner) << itemlog(pItem) << end;

			RemoveItem(i);
			continue;
		}
#endif // HALLOWEEN ITEM DELETE
		if (!gserver->isActiveEvent(A_EVENT_XMAS) && ((pItem->getDBIndex() >= 2584 && pItem->getDBIndex() <= 2589) || (pItem->getDBIndex() >= 2604 && pItem->getDBIndex() <= 2605) || (pItem->getDBIndex() >= 2607 && pItem->getDBIndex() <= 2608)))
		{
			GAMELOG << init("XMAS EVENT END DELETE ITEM", _owner) << itemlog(pItem) << end;

			RemoveItem(i);
			continue;
		}
	} // end for
}

void CWearInvenManager::initCostumSuitItem( CItem* item )
{
	//������ ����
	setCosWearSuitItem(item);
	//������ ����
	getCosWearSuitItem()->setWearPos(COSTUME2_WEARING_SUIT);


	//�����ǻ��� �������� �����Ͽ� ������ �ɼ� ���� �� ���� ���� ������Ʈ
	CItem* pItem = NULL;
	int itemIndex = -1;
	bool bWearing = false;
	for( int i = 0; i < COSTUME2_SUIT_MAX_WEARING; i++ )
	{
		itemIndex = item->GetOriginIndex(i-1);
		CItemProto* proto = gserver->m_itemProtoList.FindIndex(itemIndex);
		if (!proto)
		{
			GAMELOG << init("SYS_ERR")
				<< "DressCostumeSuit proto NULL"
				<< item->getDBIndex()
				<< itemIndex;
			continue;
		}

		pItem = new CItem();
		pItem->setItemProto(proto);
		pItem->setDBIndex(proto->getItemIndex());
		pItem->setWearPos(proto->getItemWearing());
		pItem->setUsed(item->getUsed());
		if (pItem->IsOriginItem())
		{
			for (int i = 0; i < MAX_ORIGIN_OPTION; i++)
			{
				if(pItem->GetOriginIndex(i) >= 0)
				{
					pItem->setOriginVar(i, 100);
				}
			}
		}
		wearItemInfo[pItem->getWearPos() + COSTUME2_WEARING_START] = pItem;
		bWearing = true;
	}

	//���� ���� ����
	if (bWearing)
	{
		int skill_index = 0, skill_level = 0;
		gserver->m_Fortunelist.Resolve_fortune_value(skill_index, skill_level, item->getPlus());
		CSkill *pSkill = gserver->m_skillProtoList.Create(skill_index, skill_level);
		bool bApply = false;
		if(pSkill)
		{
			ApplySkill(_owner, _owner, pSkill, -1, bApply);
			if(!bApply && pSkill)
			{
				delete pSkill;
				pSkill = NULL;
			}
		}
	}
	_owner->CalcStatus(true);
}

void CWearInvenManager::initCostumItem( CItem* item, int wearPos )
{

	item->setWearPos(wearPos);
	
	if(wearPos == 11) 
		wearPos = 7;

	wearItemInfo[(int)wearPos + COSTUME2_WEARING_START] = item;
	dressCostumCount++;
}

int CWearInvenManager::getWearItemPlusSumCount()
{
	int getCount = 0;
	static int armors[] = {WEARING_HELMET, WEARING_ARMOR_UP, WEARING_ARMOR_DOWN, WEARING_SHIELD, WEARING_GLOVE, WEARING_BOOTS, WEARING_BACKWING };
	CItem* item = nullptr;
	for (int i = 0; i < sizeof(armors) / sizeof(armors[0]); i++)
	{
		item = getCalcWear(armors[i]);
		if (item && item->IsArmorType())
		{
			getCount += item->getPlus();
		}
	}

	return getCount;
}

