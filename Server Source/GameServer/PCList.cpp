#include <boost/lambda/lambda.hpp>
#include "stdhdrs.h"

#include "PCList.h"
#include "Descriptor.h"
#include "WarCastle.h"
#include "Zone.h"
#include "CmdMsg.h"
#include "Battle.h"

PCManager* PCManager::instance()
{
	static PCManager __instance;
	return &__instance;
}

void PCManager::addPlayer(CPC* pPlayer)
{
	PlayerInfo playInfo;
	playInfo.userIndex		= pPlayer->m_desc->m_index;
	playInfo.charIndex		= pPlayer->m_index;
	playInfo.charName		= pPlayer->m_name;
	playInfo.charNickName	= pPlayer->m_nick;
	playInfo.pPlayer		= pPlayer;

	playerMap_.insert(playInfo);

	LOG_INFO("Player Add Data : userIndex[%d], charIndex[%d] charName[%s]",
			 playInfo.userIndex, playInfo.charIndex, playInfo.charName.c_str());
}

CPC* PCManager::getPlayerByUserIndex(int userIndex)
{
	map_t::index<Key_User_Index>::type& p = playerMap_.get<Key_User_Index>();
	map_t::index<Key_User_Index>::type::iterator it = p.find(userIndex);
	if (it == p.end())
		return NULL;

	if (it->pPlayer->m_bPlaying == false)
		return NULL;

	return (*it).pPlayer;
}


CPC* PCManager::getPlayerByCharIndex(int charIndex)
{
	map_t::index<Key_Char_Index>::type& p = playerMap_.get<Key_Char_Index>();
	map_t::index<Key_Char_Index>::type::iterator it = p.find(charIndex);
	if (it == p.end())
		return NULL;

	if (it->pPlayer->m_bPlaying == false)
		return NULL;

	return (*it).pPlayer;
}

CPC* PCManager::getPlayerByName(const char* name, bool isNickName)
{
	CPC * pc = NULL;

	pc = getPlayerByCharNickName(name);
	if (pc == NULL)
	{
		pc = getPlayerByCharName(name);
	}
	return pc;
}

CPC* PCManager::getPlayerByCharName(const char* charName)
{
	map_t::index<Key_Char_Name>::type& p = playerMap_.get<Key_Char_Name>();
	map_t::index<Key_Char_Name>::type::iterator it = p.find(charName);
	if (it == p.end())
		return NULL;

	if (it->pPlayer->m_bPlaying == false)
		return NULL;

	return (*it).pPlayer;
}

CPC* PCManager::getPlayerByCharNickName(const char* charName)
{
	map_t::index<Key_Char_Nick_Name>::type& p = playerMap_.get<Key_Char_Nick_Name>();
	map_t::index<Key_Char_Nick_Name>::type::iterator it = p.find(charName);
	if (it == p.end())
		return NULL;

	if (it->pPlayer->m_bPlaying == false)
		return NULL;

	return (*it).pPlayer;
}

void PCManager::deletePlayerByPC(CPC* pc)
{
	if (pc == NULL)
		return;

	deletePlayerByCharIndex(pc->m_index);
}

void PCManager::deletePlayerByUserIndex(int userIndex)
{
	auto& idx = playerMap_.get<Key_User_Index>();
	auto it = idx.find(userIndex);
	if (it != idx.end())
	{
		idx.erase(it);
	}
}

void PCManager::deletePlayerByCharIndex(int charIndex)
{
	auto& idx = playerMap_.get<Key_Char_Index>();
	auto it = idx.find(charIndex);
	if (it != idx.end())
	{
		idx.erase(it);  // erase by iterator, safe for multi-index
	}
}

void PCManager::deletePlayerByCharName(const char* charName)
{
	auto& idx = playerMap_.get<Key_Char_Name>();
	auto it = idx.find(charName); // assuming your index supports const char* comparison
	if (it != idx.end())
	{
		idx.erase(it); // erase by iterator
	}
}


void PCManager::deletePlayerByCharNickName(const char* charName)
{
	auto& idx = playerMap_.get<Key_Char_Nick_Name>();
	auto it = idx.find(charName);  // works if index key type is std::string
	if (it != idx.end())
	{
		idx.erase(it);  // erase safely by iterator
	}
}


bool PCManager::isPlaying(CPC *ch)
{
	if (ch == NULL || ch->m_name[0] == '\0')
	{
		return false;
	}

	CPC* findPlayer = getPlayerByCharIndex(ch->m_index);
	if (findPlayer != ch)
		return false;

	return true;
}

void PCManager::sendToAll(CNetMsg::SP& msg)
{
	map_t::iterator iter = playerMap_.begin();
	map_t::iterator endIter = playerMap_.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc)
		{
			SEND_Q(msg, pc->m_desc);
		}
	}
}

void PCManager::sendGuildWarPointMsg(CWarCastle* castle, int zoneindex)
{
	map_t::iterator iter = playerMap_.begin();
	map_t::iterator endIter = playerMap_.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc && pc->GetJoinFlag(zoneindex) != WCJF_NONE && pc->m_pZone && pc->m_pZone->m_index == zoneindex)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			GuildWarPointMsg(rmsg, pc, castle);
			SEND_Q(rmsg, pc->m_desc);
		}
	}
}

void PCManager::sendToWarJoinUser(CNetMsg::SP& msg, int zoneindex, bool bInZone)
{
	map_t::iterator iter = playerMap_.begin();
	map_t::iterator endIter = playerMap_.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc && pc->GetJoinFlag(zoneindex) == WCJF_NONE)
		{
			continue;
		}

		if (pc && (!bInZone || (pc->m_pZone && pc->m_pZone->m_index == zoneindex)))
		{
			SEND_Q(msg, pc->m_desc);
		}
	}
}

void PCManager::sendToAllTeacher(CNetMsg::SP& msg)
{
	map_t::iterator iter = playerMap_.begin();
	map_t::iterator endIter = playerMap_.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc && pc->m_bTeacher)
		{
			SEND_Q(msg, pc->m_desc);
		}
	}
}

void PCManager::sendToAlliesInCell(CNetMsg::SP& rmsg, CPC* pc) //dethunter12
{
	if (pc->IsParty())
	{
		CParty* pcParty = pc->m_party;
		for (int i = 0; i < MAX_PARTY_MEMBER; i++)
		{
			if (!pcParty->m_listMember[i])
				continue;

			CPC* partyMember = pcParty->m_listMember[i]->GetMemberPCPtr();
			if (CheckInNearCellExt(pc, partyMember))
			{
				SEND_Q(rmsg, partyMember->m_desc);
			}
		}
	}
	else if (pc->IsExped())
	{
		CExpedition* pcExped = pc->m_Exped;
		for (int nGroup = 0; nGroup < MAX_EXPED_GROUP; nGroup++)
		{
			for (int nIndex = 0; nIndex < MAX_EXPED_GMEMBER; nIndex++)
			{
				CExpedMember* expedMember = pcExped->GetMemberByListIndex(nGroup, nIndex);
				
				if (!expedMember) continue;

				CPC* expedPC = expedMember->GetMemberPCPtr();
				
				if (!expedPC) continue;

				if (CheckInNearCellExt(pc, expedPC))
				{
					SEND_Q(rmsg, expedPC->m_desc);
				}
			}
		}
	}

	if (pc->m_guildInfo && pc->m_guildInfo->guild())
	{
		CGuild* guild = pc->m_guildInfo->guild();
		int guildMaxMember = guild->maxmember();
		for (int i = 0; i < guildMaxMember; i++)
		{
			if (guild->member(i) && guild->member(i)->GetPC() && CheckInNearCellExt(pc, guild->member(i)->GetPC()))
			{
				SEND_Q(rmsg, guild->member(i)->GetPC()->m_desc);
			}
		}
	}
}

void PCManager::sendToZone(CNetMsg::SP& msg, int zoneIndex)
{
	map_t::iterator iter = playerMap_.begin();
	map_t::iterator endIter = playerMap_.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		if (pc && pc->m_pZone
				&& (pc->m_pZone->m_index == zoneIndex || zoneIndex == -1))
		{
			SEND_Q(msg, pc->m_desc);
		}
	}
}

void PCManager::changeNickName( const char* oldname, const char* newname )
{
	map_t::index<Key_Char_Nick_Name>::type& p = playerMap_.get<Key_Char_Nick_Name>();
	map_t::index<Key_Char_Nick_Name>::type::iterator it = p.find(oldname);
	if (it == p.end())
		return;

	p.modify_key(it, boost::lambda::_1=newname);
}

#ifdef PREMIUM_CHAR
void PCManager::resetPremiumCharJumpCount()
{
	map_t::iterator iter = playerMap_.begin();
	map_t::iterator endIter = playerMap_.end();
	for (; iter != endIter; ++iter)
	{
		CPC* pc = (*iter).pPlayer;
		pc->m_premiumChar.setJumpCount(0);
	}
}
#endif

