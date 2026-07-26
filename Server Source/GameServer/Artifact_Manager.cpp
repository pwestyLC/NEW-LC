#include "stdhdrs.h"
#include "Character.h"
#include "PCList.h"
#include "Item.h"
#include "Area.h"
#include "Artifact_Manager.h"
#include "CmdMsg.h"

#include "../ShareLib/packetType/ptype_artifact.h"
#include "../ShareLib/packetType/ptype_gps.h"
#define ARTIFACT_201605_SAFETIME			600
extern int levelup_hp[JOBCOUNT][4];
extern int levelup_mp[JOBCOUNT][4];

ArtifactItemData::ArtifactItemData()
{
	pc = NULL;
	item = NULL;
	item_level = 1;
	remaining = ARTIFACT_201605_SAFETIME;
}
ArtifactManager::~ArtifactManager()
{
	std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	for(; it != it_end; it++)
	{
		delete *it;
	}
}

ArtifactManager* ArtifactManager::instance()
{
	static ArtifactManager __instance;
	return &__instance;
}

int ArtifactManager::getCount()
{
	int count = 0;

	std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	for(; it != it_end; it++)
	{
		count += (*it)->item_level;
	}
	
	return count + drop_count;
}

void ArtifactManager::_insert( int char_index, CItem* item )
{
	CPC* pc = PCManager::instance()->getPlayerByCharIndex(char_index);

	ArtifactItemData* data = new ArtifactItemData();
	data->item = item;
	data->pc = pc;

	switch (item->getDBIndex())
	{
	case ARTIFACT_LEVEL1_ITEM_INDEX:
		data->item_level = ARTIFACT_ITEM_LEVEL_1;
		break;
	case ARTIFACT_LEVEL2_ITEM_INDEX:
		data->item_level = ARTIFACT_ITEM_LEVEL_2;
		break;
	case ARTIFACT_LEVEL3_ITEM_INDEX:
		data->item_level = ARTIFACT_ITEM_LEVEL_3;
		break;
	}

	_vec.push_back(data);
}

void ArtifactManager::_delete( CItem* item )
{
	if(item == NULL)
		return ;

	std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	for( ; it != it_end; it++)
	{
		if( (*it)->item == item )
		{
			it = _vec.erase(it);
			return ;
		}
	}
}

bool ArtifactManager::isOwnerPC( int char_index )
{
	std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	for(; it != it_end; it++)
	{
		if((*it)->pc->m_index == char_index)
			return true;
	}
	return false;
}

//PVP ��� ���� ��
void ArtifactManager::hunt( CPC* owner, CPC* target )
{
	if(owner == NULL || target == NULL)
		return;

	if(isOwnerPC(owner->m_index) == false)
		return ;

	std::vector<ArtifactItemData*>::iterator it = _vec.begin();

	for( ; it != _vec.end(); )
	{
		if((*it)->pc == owner)
		{
			int item_db_index = (*it)->item->getDBIndex();
			//owner���� �����
			{
				if(owner->m_inventory.FindByVirtualIndex((*it)->item->getVIndex()) != NULL)
					owner->m_inventory.deleteItemByItem((*it)->item);

				else if(owner->m_wearInventory.FindByVirtualIndex((*it)->item->getVIndex()) != NULL)
					owner->m_wearInventory.RemoveItem((*it)->item->getWearPos());

				else
				{
					//������ ���� �������� ������ �� �߸��Ǿ� ����
					//�α� �����
					return ;
				}

			}

			//target�� �ش�.
			{
				CItem* item = gserver->m_itemProtoList.CreateItem(item_db_index, -1, 0, 0, -1);
				if(target->m_assist.FindBySkillIndex(PVP_PROTECT_SKILL_INDEX) != 0 || target->m_inventory.addItem(item) == false)
				{
					//�������� ����߸��� �����̳ʿ��� ���� �ϰ� it�������ش�.
					owner->m_pArea->DropItem(item, target);

					CNetMsg::SP rmsg(new CNetMsg);
					(*it)->item->m_preferenceIndex = target->m_index;
					ItemDropMsg(rmsg, target, item);
					(*it)->item->m_pArea->SendToCell(rmsg, target, true);

					it = _vec.erase(it);
				}
				else
				{
					(*it)->pc = target;
					sendToAllSysMsg(target, item->getDBIndex(), ARTIFACT_SYSMSG_TAKE);
				}
			}
		}
		else
			it++;
	}
}

void ArtifactManager::changeOnwer( CPC* newOwner, CItem* item )
{
	if(item == NULL)
		return ;

	std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	for(; it != it_end; it++)
	{
		if((*it)->item == item)
		{
			(*it)->pc = newOwner;
			sendToAllSysMsg(newOwner, item->getDBIndex(), ARTIFACT_SYSMSG_TAKE);
			return ;
		}
	}
}

void ArtifactManager::addOwner( CPC* owner, CItem* item, bool isTake )
{
	_insert(owner->m_index, item);
	sendToAllSysMsg(owner, item->getDBIndex(), ARTIFACT_SYSMSG_TAKE);

	if(isTake == true)
	{
		calcDropCount(item, true);
	}
}

void ArtifactManager::compose( CPC* owner, CItem* mat_item1, CItem* mat_item2,  CItem* result_item )
{
	_delete(mat_item1);
	_delete(mat_item2);
	_insert(owner->m_index, result_item);

	sendToAllSysMsg(owner, result_item->getDBIndex(), ARTIFACT_SYSMSG_COMPOSE);
}

void ArtifactManager::sendToAllSysMsg( CPC* owner, int item_index, int systype, int zone_index )
{
	if(owner == NULL)
		return ;

	if(owner->m_pZone == NULL)
		return ;

	int zone;
	if(zone_index == -1)
		zone = owner->m_pZone->m_index;
	else
		zone = zone_index;

	CNetMsg::SP rmsg(new CNetMsg);
	UpdateClient::makeArtifact_SysMsg(rmsg, item_index, zone, owner->GetName(), systype);
	PCManager::instance()->sendToAll(rmsg);
}

void ArtifactManager::sendOwnerGPSData( CPC* ch )
{
	if(ch == NULL)
		return;

	if(ch->m_pZone == NULL)
		return ;

	std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	CNetMsg::SP rmsg(new CNetMsg);
	int count = 0;
	UpdateClient::ArtifactGPSData *packet = reinterpret_cast<UpdateClient::ArtifactGPSData*>(rmsg->m_buf);
	packet->type = MSG_GPS;
	packet->subType = MSG_SUB_ARTIFACT_GPS_DATA;
	for(; it != it_end; it++, count++)
	{
		if((*it)->pc == NULL)
		{
			//artifact manager�� ���������� ���� Ȥ�� ���� ĳ������ ������ �ִ�. �α׳��ܾ� ������ ���ֵ����� ��ƾ�̹Ƿ� �ϴ� �����Ѵ�.
			//LOG_ERROR("INVALID ARTIFACT USER INFO. WARNING... ARTIFACT COUNT IS [%d]", this->drop_count);
			continue;
		}

		if((*it)->pc->m_pZone->m_index == ch->m_pZone->m_index)
		{
			packet->info[count].char_index = (*it)->pc->m_index;
			packet->info[count].x = (*it)->pc->m_pos.m_x;
			packet->info[count].z = (*it)->pc->m_pos.m_z;
			packet->info[count].h = (*it)->pc->m_pos.m_h;
			packet->info[count].yLayer = (*it)->pc->m_pos.m_yLayer;
		}
	}
	packet->_count = count;
	rmsg->setSize(sizeof(UpdateClient::ArtifactGPSData) + (sizeof(UpdateClient::ArtifactUserInfo) * count));
	SEND_Q(rmsg, ch->m_desc);
}

CItem* ArtifactManager::FindWearItem( CPC* pc )
{
	if( pc == NULL )
		return NULL;

	std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	for(; it != it_end; it++)
	{
		if((*it)->pc == NULL || (*it)->item == NULL)
		{
			//artifact manager�� ���������� ���� Ȥ�� ���� ĳ������ ������ �ִ�.
			LOG_ERROR("INVALID ARTIFACT USER INFO. WARNING... ARTIFACT COUNT IS [%d]", this->drop_count);
			continue;
		}

		if((*it)->pc == pc
			&& (*it)->item->getWearPos() != -1)
		{
			return (*it)->item;
		}
	}

	return NULL;
}

void ArtifactManager::disconnect( CPC* pc )
{
	if( pc == NULL )
		return ;

	std::vector<ArtifactItemData*>::iterator it = _vec.begin();

	for(; it != _vec.end(); )
	{
		if((*it)->pc == NULL || (*it)->item == NULL)
		{
			//artifact manager�� ���������� ���� Ȥ�� ���� ĳ������ ������ �ִ�.
			LOG_ERROR("INVALID ARTIFACT USER INFO. WARNING... ARTIFACT COUNT IS [%d]", this->drop_count);
			continue;
		}

		if((*it)->pc == pc)
		{
			CItem* item = (*it)->item;
			if(item != NULL)
			{
				sendToAllSysMsg(pc, (*it)->item->getDBIndex(), ARTIFACT_SYSMSG_LOGOUT);

				if(item->getWearPos() > 0)
				{
					pc->m_wearInventory.RemoveItem(item->getWearPos());
				}
				else
				{
					pc->m_inventory.deleteItemByItem(item);
				}
			}

			it = _vec.erase(it);
		}
		else
			it++;
	}
}

void ArtifactManager::dead( CPC* owner )
{
	std::vector<ArtifactItemData*>::iterator it = _vec.begin();

	for(; it != _vec.end(); )
	{
		if((*it)->pc == NULL || (*it)->item == NULL)
		{
			//artifact manager�� ���������� ���� Ȥ�� ���� ĳ������ ������ �ִ�.
			LOG_ERROR("INVALID ARTIFACT USER INFO. WARNING... ARTIFACT COUNT IS [%d]", this->drop_count);
			continue;
		}
		
		if((*it)->pc == owner)
		{
			CItem* item = (*it)->item;
			if(item != NULL)
			{
				sendToAllSysMsg(owner, (*it)->item->getDBIndex(), ARTIFACT_SYSMSG_DIE_TO_NPC);

				if(item->getWearPos() > 0)
				{
					owner->m_wearInventory.RemoveItem(item->getWearPos());
				}
				else
				{
					owner->m_inventory.deleteItemByItem(item);
				}
			}
			
			it = _vec.erase(it);
		}
		else
			it++;
	}
}

void ArtifactManager::move_zone( CPC* pc, int zone_index )
{
	if(pc == NULL)
		return ;

	std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	//���� ���� set
	std::set<int> _set;

	for(; it != it_end; it++)
	{
		if((*it)->pc == pc && _set.find(pc->m_index) == _set.end())
		{
			CItem* item = (*it)->item;
			if(item != NULL)
			{
				sendToAllSysMsg(pc, (*it)->item->getDBIndex(), ARTIFACT_SYSMSG_MOVE_ZONE, zone_index);
				_set.insert(pc->m_index);
			}
		}
	}

	_set.clear();
}

void ArtifactManager::expire_time( CItem* item )
{
	if(item == NULL)
		return ;

	std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	for(; it != it_end; it++)
	{
		if((*it)->item == item)
		{
			if(item != NULL)
			{
				sendToAllSysMsg((*it)->pc, item->getDBIndex(), ARTIFACT_SYSMSG_EXPIRE_TIME);
			}
			_vec.erase(it);
			return ;
		}
	}
}

void ArtifactManager::item_drop( CItem* item )
{
	this->_delete(item);
}

bool ArtifactManager::isArtifactParty( CParty* party )
{
	if(party == NULL)
		return false;

	std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	for(; it != it_end; it++)
	{
		if((*it)->pc->m_party == party)
			return true;
	}

	return false;
}



void ArtifactManager::ApplyArtifact( CPC* pc )
{
	if(pc == NULL)
		return ;

	if(pc->IsInPeaceZone(true))
		return ;

	CItem* owner_item = NULL;
	bool isOwner = false;
	
	int owner_status = 0, party_status = 0;
	LONGLONG owner_exp = 0, party_exp = 0, owner_gold = 0, party_gold = 0;

	for(int i = 0; i < _vec.size(); i++)
	{
		if(_vec[i]->pc == NULL || _vec[i]->item == NULL)
		{
			//artifact manager�� ���������� ���� Ȥ�� ���� ĳ������ ������ �ִ�.
			LOG_ERROR("INVALID ARTIFACT USER INFO. WARNING... ARTIFACT COUNT IS [%d]", this->drop_count);
			continue;
		}

		if(_vec[i]->pc == pc
			&& _vec[i]->item->getWearPos() != -1)
		{
			switch(_vec[i]->item->getDBIndex())
			{
			case ARTIFACT_LEVEL1_ITEM_INDEX:
				owner_status += 200;		owner_exp += 200;		owner_gold += 20;
				break;
			case ARTIFACT_LEVEL2_ITEM_INDEX:
				owner_status += 500;		owner_exp += 400;		owner_gold += 30;
				break;
			case ARTIFACT_LEVEL3_ITEM_INDEX:
				owner_status += 1200;	owner_exp += 600;		owner_gold += 170;
				break;
			}
		}
	}
	
	for(int i = 0; i < _vec.size(); i++)
	{
		if(_vec[i]->pc == NULL || _vec[i]->item == NULL)
		{
			//artifact manager�� ���������� ���� Ȥ�� ���� ĳ������ ������ �ִ�.
			LOG_ERROR("INVALID ARTIFACT USER INFO. WARNING... ARTIFACT COUNT IS [%d] - ApplyArtifact", this->drop_count);
			continue;
		}

		if(pc->m_party != NULL
			&& _vec[i]->pc->m_party == pc->m_party
			&& _vec[i]->pc != pc
			&& _vec[i]->item->getWearPos() != -1)
		{
			if(_vec[i]->pc->IsInPeaceZone(true) == true)
				continue ;

			if(_vec[i]->pc->m_pZone == NULL || pc->m_pZone == NULL)
				continue ;

			if(_vec[i]->pc->m_pZone->m_index != pc->m_pZone->m_index)
				continue ;

			switch(_vec[i]->item->getDBIndex())
			{
			case ARTIFACT_LEVEL1_ITEM_INDEX:
				party_status += 100;		party_exp += 100;		party_gold += 20;
				break;
			case ARTIFACT_LEVEL2_ITEM_INDEX:
				party_status += 200;		party_exp += 200;		party_gold += 30;
				break;
			case ARTIFACT_LEVEL3_ITEM_INDEX:
				party_status += 500;		party_exp += 300;		party_gold += 120;
				break;	
			}
		}
	}

	pc->m_artiStr += (owner_status + party_status);
	pc->m_artiDex += (owner_status + party_status);
	pc->m_artiInt += (owner_status + party_status);
	pc->m_artiCon += (owner_status + party_status);
	pc->m_artiExp += (owner_exp + party_exp);
	
	pc->m_artiGold += (owner_gold + party_gold);

	pc->m_str += (owner_status + party_status);

	pc->m_dex += (owner_status + party_status);

	pc->m_int += (owner_status + party_status);
	pc->m_maxMP += (owner_status + party_status) * levelup_mp[pc->m_job][2];

	pc->m_con += (owner_status + party_status);
	pc->m_maxHP += (owner_status + party_status) * levelup_hp[pc->m_job][3];
	pc->m_maxMP += (owner_status + party_status) * levelup_mp[pc->m_job][3];
}

int ArtifactManager::getSameZoneCount(CPC* pc)
{
	if(pc == NULL)
		return 0;

	if(pc->m_pZone == NULL)
		return 0;

	std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	//���� ���� set
	std::set<int> _set;

	int count = 0;
	for(; it != it_end; it++)
	{
		if((*it)->pc == NULL || (*it)->item == NULL)
		{
			//artifact manager�� ���������� ���� Ȥ�� ���� ĳ������ ������ �ִ�.
			LOG_ERROR("INVALID ARTIFACT USER INFO. WARNING... ARTIFACT COUNT IS [%d]", this->drop_count);
			continue;
		}

		if((*it)->pc->m_pZone->m_index == pc->m_pZone->m_index
			&& _set.find(pc->m_index) == _set.end())
		{
			count++;
			_set.insert(pc->m_index);
		}
	}
	_set.clear();

	return count;
}

void ArtifactManager::calcDropCount( CItem* item, bool isTake )
{
	if(item == NULL)
		return ;

	if(item->m_itemProto == NULL)
		return ;
	
	if(item->m_itemProto->getItemTypeIdx() == ITYPE_ACCESSORY && item->m_itemProto->getItemSubTypeIdx() == IACCESSORY_ARTIFACT)
	{
		int itemLevel = 0;

		switch(item->getDBIndex())
		{
		case ARTIFACT_LEVEL1_ITEM_INDEX:
			itemLevel = ARTIFACT_ITEM_LEVEL_1;
			break;
		case ARTIFACT_LEVEL2_ITEM_INDEX:
			itemLevel = ARTIFACT_ITEM_LEVEL_2;
			break;
		case ARTIFACT_LEVEL3_ITEM_INDEX:
			itemLevel = ARTIFACT_ITEM_LEVEL_3;
			break;
		}
		//�������� �ֿ�����
		if(isTake == true)
		{
			drop_count -= itemLevel;
		}
		//�������� ����߸���
		else
		{
			drop_count += itemLevel;
		}
	}
}

void ArtifactManager::eventOff()
{
	//�̺�Ʈ�� ����Ǹ� �ý��� �޽����� �Բ� �������� �κ��丮���� �������ش�.
	std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	for(; it != it_end; it++)
	{
		if((*it)->pc == NULL || (*it)->item == NULL)
		{
			//artifact manager�� ���������� ���� Ȥ�� ���� ĳ������ ������ �ִ�.
			LOG_ERROR("INVALID ARTIFACT USER INFO. WARNING... ARTIFACT COUNT IS [%d]", this->drop_count);
			continue;
		}

		if((*it)->item->getWearPos() >= 0)
			(*it)->pc->m_wearInventory.RemoveItem((*it)->item->getWearPos());
		else
			(*it)->pc->m_inventory.deleteItemByItem((*it)->item);
		
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_ARTIFACT_ITEM_DELETE_EVENT_OFF);
			SEND_Q(rmsg, (*it)->pc->m_desc);
		}
	}

	_vec.clear();
}

bool ArtifactManager::canMove(int zone_index)
{
	switch(zone_index)
	{
	case ZONE_SINGLE_DUNGEON1:
	case ZONE_DUNGEON2:
	case ZONE_SINGLE_DUNGEON2:
	case ZONE_SINGLE_DUNGEON_TUTORIAL:
	case ZONE_GUILDROOM:
	case ZONE_SINGLE_DUNGEON3:
	case ZONE_SINGLE_DUNGEON4:
	case ZONE_DUNGEON4:
	case ZONE_OXQUIZROOM:
	case ZONE_EGEHA_DUNGEON_1:
	case ZONE_EGEHA_DUNGEON_8:
	case ZONE_EGEHA_DUNGEON_9:
	case ZONE_EGEHA_DUNGEON_10:
	case ZONE_COMBO_DUNGEON:
	case ZONE_EXTREME_CUBE:
	case ZONE_SPRIT_CAVE:
	case ZONE_QUANIAN_CAVE:
	case ZONE_GOLEM_CAVE:
	case ZONE_CAPPELLA_1:
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	case ZONE_PARTY_DUNGEON0:
	case ZONE_PARTY_DUNGEON1:
	case ZONE_PARTY_DUNGEON2:
	case ZONE_PARTY_DUNGEON3:
	case ZONE_PARTY_DUNGEON4:
#endif
	case ZONE_CAPPELLA_2:
	case ZONE_ALTER_OF_DARK:
	case ZONE_AKAN_TEMPLE:
	case ZONE_ROYAL_RUMBLE:
	case ZONE_TARIAN_DUNGEON:
	case ZONE_ENCHANTED_DUNGEON:	//Val make so they cant go to new raid with artifact
		return false;
	}
	return true;
}

bool ArtifactManager::canDrop(int zone_index)
{
	switch(zone_index)
	{
	case ZONE_START:
	case ZONE_DUNGEON1:
	case ZONE_SINGLE_DUNGEON1:
	case ZONE_DUNGEON2:
	case ZONE_SINGLE_DUNGEON2:
	case ZONE_SINGLE_DUNGEON_TUTORIAL:
	case ZONE_GUILDROOM:
	case ZONE_DUNGEON3:
	case ZONE_SINGLE_DUNGEON3:
	case ZONE_SINGLE_DUNGEON4:
	case ZONE_DUNGEON4:
	case ZONE_FREE_PK_DUNGEON:
	case ZONE_OXQUIZROOM:
	case ZONE_EGEHA_PK:
	case ZONE_EGEHA_DUNGEON_1:
	case ZONE_EGEHA_DUNGEON_8:
	case ZONE_EGEHA_DUNGEON_9:
	case ZONE_EGEHA_DUNGEON_10:
	case ZONE_DRATAN_CASTLE_DUNGEON:
	case ZONE_COMBO_DUNGEON:
	case ZONE_PK_TOURNAMENT:
	case ZONE_EXTREME_CUBE:
	case ZONE_SPRIT_CAVE:
	case ZONE_QUANIAN_CAVE:
	case ZONE_GOLEM_CAVE:
	case ZONE_EBONY_MINE:
	case ZONE_MISTY_CANYON:
	case ZONE_FLORAIM_CAVE:
	case ZONE_CAPPELLA_1:
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	case ZONE_PARTY_DUNGEON0:
	case ZONE_PARTY_DUNGEON1:
	case ZONE_PARTY_DUNGEON2:
	case ZONE_PARTY_DUNGEON3:
	case ZONE_PARTY_DUNGEON4:
#endif
	case ZONE_CAPPELLA_2:
	case ZONE_ALTER_OF_DARK:
	case ZONE_AKAN_TEMPLE:
	case ZONE_TRIVIA_CANYON:
	case ZONE_ROYAL_RUMBLE:
	case ZONE_TARIAN_DUNGEON:
	case ZONE_RVR:
	case ZONE_MISTY_CANYON_EXTREME:
	case ZONE_ENCHANTED_DUNGEON:
	case ZONE_MAGMA_CANYON: 
		return false;
	}
	return true;
}

int ArtifactManager::checkValidUser( CPC* ch )
{
	if(ch->m_level <= PKMODE_LIMIT_LEVEL)
	{
		return MSG_SYS_ARTIFACT_PVP_GET_ITEM;
	}
	else if(ch->m_assist.FindBySkillIndex(PVP_PROTECT_SKILL_INDEX) != 0)
	{
		return MSG_SYS_ARTIFACT_USE_PVPPROTECT;
	}
	else
		return 0;
}
void ArtifactManager::_proc()
{
	// loop through artifact list to find timed out instances
	ArtifactItemData* pArtifact = NULL;
	CPC* ch = NULL;
	unsigned short sMapAttr;
	//std::vector<ArtifactItemData*>::iterator it = _vec.begin();
	//std::vector<ArtifactItemData*>::iterator it_end = _vec.end();

	for (int i = 0; i < _vec.size();)
	{
		// assign to control instance
		pArtifact = _vec[i];
		if (!pArtifact)
		{
			i++;
			continue;
		}
		ch = pArtifact->pc;

		// let the standard routine take care of it
		if (!pArtifact->item || !ch || !ch->m_pArea)
		{
			i++;
			continue;
		}

		// check map attributes
		bool bIsField = false;
#ifdef ARTIFACT_NOT_INCREASE_TIME
		sMapAttr = ch->m_pArea->GetAttr(GET_YLAYER(ch), GET_X(ch), GET_Z(ch));
		if (sMapAttr & MATT_PEACE || sMapAttr & MATT_UNWALKABLE)
#endif
		{
			// player is in a safezone
			bIsField = false;
			//count down remaining artifact time
			pArtifact->remaining--;
		}
#ifdef ARTIFACT_NOT_INCREASE_TIME
		else
		{
			// player is somewhere he can be attacked
			bIsField = true;
			// count up remaining artifact time if not at max already
			if (pArtifact->remaining < ARTIFACT_201605_SAFETIME)
				pArtifact->remaining++;
		}
#endif
		// send exact timer to admins
		if (ch->m_bDebugMode)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_ARTIFACT);
			RefMsg(rmsg)	<< (unsigned char)MSG_ARTIFACT_GENERAL
							<< (unsigned char)MSG_ARTIFACT_ARTIFACT_NOTICE_REMAINING
							<< pArtifact->remaining;
			SEND_Q(rmsg, ch->m_desc);
		}

		// check remaining time
		if (pArtifact->remaining <= 0)
		{
			// artifact timed out, remove it
			char nWearPos = pArtifact->item->getWearPos();
			if (ch->m_wearInventory.isValidWarePos(nWearPos) == true)
				ch->m_wearInventory.RemoveItem(nWearPos);
			else
				ch->m_inventory.deleteItemByItem(pArtifact->item);

			// send info to player
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_ARTIFACT);
			RefMsg(rmsg)	<< (unsigned char)MSG_ARTIFACT_GENERAL
							<< (unsigned char)MSG_ARTIFACT_ARTIFACT_NOTICE_TIMEOUT;
			SEND_Q(rmsg, ch->m_desc);
			// send info to everyone
			sendToAllSysMsg(ch, pArtifact->item->getDBIndex(), ARTIFACT_SYSMSG_EXPIRE_TIME);
			// delete artifact from list
			_vec.erase(_vec.begin() + i);
			continue;
		}
		else if (bIsField == false && pArtifact->remaining == 180)
		{
			// warn player that he has 3 mins left to return to a field zone
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_ARTIFACT);
			RefMsg(rmsg)	<< (unsigned char)MSG_ARTIFACT_GENERAL
							<< (unsigned char)MSG_ARTIFACT_ARTIFACT_NOTICE_3MIN;
			SEND_Q(rmsg, ch->m_desc);
		}
		else if (bIsField == false && pArtifact->remaining == 60)
		{
			// warn player that he has 1 min left to return to a field zone
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_ARTIFACT);
			RefMsg(rmsg)	<< (unsigned char)MSG_ARTIFACT_GENERAL
							<< (unsigned char)MSG_ARTIFACT_ARTIFACT_NOTICE_1MIN;
			SEND_Q(rmsg, ch->m_desc);
		}

		// advance position
		i++;
	}
}