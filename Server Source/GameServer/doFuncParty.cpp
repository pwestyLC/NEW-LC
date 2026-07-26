#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "Server.h"
#include "CmdMsg.h"
#include "doFunc.h"
#include "WarCastle.h"

/////////////////
// ��Ƽ ���� �Լ�
void do_Party(CPC* ch, CNetMsg::SP& msg)
{
	// �Ⱥ��̸� ����
	if (!ch->m_bVisible)
		return ;

	unsigned char subtype;

	msg->MoveFirst();

	RefMsg(msg) >> subtype;

	switch (subtype)
	{
	case MSG_PARTY_INVITE:
		do_PartyInvite(ch, msg);
		break;
	case MSG_PARTY_ALLOW:
		do_PartyAllow(ch, msg);
		break;
	case MSG_PARTY_REJECT:
		do_PartyReject(ch, msg);
		break;
	case MSG_PARTY_QUIT:
		do_PartyQuit(ch, msg);
		break;
	case MSG_PARTY_KICK:
		do_PartyKick(ch, msg);
		break;
	case MSG_PARTY_ASSISTINFO:
		do_PartyAssistInfo(ch, msg);
		break;
	case MSG_PARTY_CHANGEBOSS:
		do_PartyChangeBoss(ch, msg);
		break;
	case MSG_PARTY_CHANGETYPE:
		do_PartyChangeType(ch, msg);
		break;
	case MSG_PARTY_ENDPARTY_REQ:
		do_PartyEndPartyReq(ch, msg);
		break;

	case MSG_PARTY_OFFLINE:
		do_PartyOffline(ch, msg);
	}
}

void do_PartyInvite(CPC* ch, CNetMsg::SP& msg)
{
	if(ch->m_pZone->IsPersonalDungeon()
			|| ch->m_pZone->IsWarGroundZone()
			|| ch->m_pZone->IsPersonalRaid()
	  )
	{
		LOG_INFO("I is dungeon zone.");
		return ;
	}

	char partyType;
	int destindex;
	CLCString name(MAX_CHAR_NAME_LENGTH);

	RefMsg(msg) >> partyType >> destindex  >> name;

	GAMELOG << init("PARTY DEBUG INVITE", ch)
			<< partyType << delim
			<< destindex
			<< end;

#if defined (LC_GAMIGO)
	if(partyType == MSG_PARTY_TYPE_BATTLE)
	{
		LOG_INFO("Party type is MSG_PARTY_TYPE_BATTLE");
		return ;
	}
#endif

#ifdef LC_GAMIGO
	if(partyType == MSG_PARTY_TYPE_FIRSTGET)
	{
		LOG_INFO("Party type is MSG_PARTY_TYPE_FIRSTGET");
		return ;
	}
#endif // LC_GAMIGO

	if(destindex == -1)
	{
		CPC* tPC = PCManager::instance()->getPlayerByName(name, true);
		if(tPC == NULL)
		{
			LOG_INFO("Target(%s) is not hear.", (const char *)name);
			return ;
		}
		destindex = tPC->m_index;
	}

	if (ch->m_index == destindex)
	{
		LOG_ERROR("Target is me. charIndex[%d]", ch->m_index);
		ch->m_desc->Close("Target is me");
		return ;
	}

// << kjban 080110 ������ ������ ���
	CPC * pPC = PCManager::instance()->getPlayerByCharIndex(destindex);
	if(pPC == NULL)
	{
		LOG_INFO("Target(%s) is not hear.", (const char *)name);
		return;
	}

	if(pPC->m_pZone->IsPersonalDungeon()
			|| pPC->m_pZone->IsWarGroundZone()
			|| pPC->m_pZone->IsPersonalRaid()
	  )
	{
		LOG_INFO("Target is dungeon.");
		return ;
	}

	if(pPC->m_Exped != NULL)
	{
		LOG_INFO("Target is exped");
		return ;
	}

	// ���� ���� ��� �� ��Ƽ ����
	switch(ch->GetJoinFlag(ZONE_MERAC))
	{
	case WCJF_ATTACK_GUILD:
	case WCJF_ATTACK_CHAR:
		if(pPC->GetJoinFlag(ZONE_MERAC) == WCJF_DEFENSE_GUILD
				|| pPC->GetJoinFlag(ZONE_MERAC) == WCJF_OWNER
				|| pPC->GetJoinFlag(ZONE_MERAC) == WCJF_DEFENSE_CHAR)
		{
			LOG_INFO("Target is another team.");
			return;
		}
		break;

	case WCJF_DEFENSE_GUILD:
	case WCJF_OWNER:
	case WCJF_DEFENSE_CHAR:
		if(pPC->GetJoinFlag(ZONE_MERAC) == WCJF_ATTACK_GUILD
				|| pPC->GetJoinFlag(ZONE_MERAC) == WCJF_ATTACK_CHAR)
		{
			LOG_INFO("Target is another team.");
			return;
		}
		break;
	}

// ���� ���� ��� �� ��Ƽ ����
	switch(ch->GetJoinFlag(ZONE_DRATAN))
	{
	case WCJF_ATTACK_GUILD:
	case WCJF_ATTACK_CHAR:
		if(pPC->GetJoinFlag(ZONE_DRATAN) == WCJF_DEFENSE_GUILD
				|| pPC->GetJoinFlag(ZONE_DRATAN) == WCJF_OWNER
				|| pPC->GetJoinFlag(ZONE_DRATAN) == WCJF_DEFENSE_CHAR)
		{
			LOG_INFO("Target is another team.");
			return;
		}
		break;

	case WCJF_DEFENSE_GUILD:
	case WCJF_OWNER:
	case WCJF_DEFENSE_CHAR:
		if(pPC->GetJoinFlag(ZONE_DRATAN) == WCJF_ATTACK_GUILD
				|| pPC->GetJoinFlag(ZONE_DRATAN) == WCJF_ATTACK_CHAR)
		{
			LOG_INFO("Target is another team.");
			return;
		}
		break;
	}
	// ���� ���� RVR ���̶�� ���� ���� �ҼӸ� ����
	if (ch->m_pZone->isRVRZone())
	{
		if (!pPC->m_pZone->isRVRZone())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_DO_NOT_SYSTEM_NOT_EQ_RVRTYPE);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}

		if (ch->getSyndicateType() != pPC->getSyndicateType())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_DO_NOT_SYSTEM_NOT_EQ_RVRTYPE);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyInviteReqMsg(rmsg, ch->m_index, ch->GetName(), ch->m_level, destindex, partyType);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

void do_PartyAllow(CPC* ch, CNetMsg::SP& msg /* msg */)
{
	// ��Ƽ ������ �ְ�
	GAMELOG << init("PARTY DEBUG ALLOW", ch)
			<< end;

	if (ch->m_party == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_NOT_PARTY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	// ���� ��û ���� ����̸�
	if (ch->m_party->GetRequestIndex() != ch->m_index)
		return ;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyAllowReqMsg(rmsg, ch->m_party->GetBossIndex(), ch->m_index, ch->GetName(), ch->m_level );
		SEND_Q(rmsg, gserver->m_helper);
	}
}

void do_PartyReject(CPC* ch, CNetMsg::SP& msg /* msg */)
{
	GAMELOG << init("PARTY DEBUG REJECT", ch)
			<< end;

	// ��Ƽ ������ �ְ�
	if (ch->m_party == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_NOT_PARTY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if( ch->m_party->GetRequestIndex() < 1 )
		return;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyRejectReqMsg(rmsg, ch->m_party->GetBossIndex(), ch->m_index);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

void do_PartyQuit(CPC* ch, CNetMsg::SP& msg /* msg */)
{
	GAMELOG << init("PARTY DEBUG QUIT", ch)
			<< end;

	CParty* pParty = gserver->FindPartyByMemberIndex(ch->m_index, false);
	if (ch->m_party == NULL && pParty == NULL)
	{
		GAMELOG << init("PARTY_BUG_GER QUIT: NOT_PARTY", ch)
				<< end;
		return ;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyQuitReqMsg(rmsg, ch->m_party->GetBossIndex(), ch->m_index);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

void do_PartyKick(CPC* ch, CNetMsg::SP& msg)
{
	int index;
	RefMsg(msg) >> index;

	GAMELOG << init("PARTY DEBUG KICK", ch)
			<< index
			<< end;

	// ��Ƽ ���̰�
	if (ch->m_party == NULL)
	{
		GAMELOG << init("PARTY_BUG_GER KICK: NOT_PARTY", ch)
				<< index
				<< end;
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_NOT_PARTY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// �����̰�
	if (ch->m_party->GetBossIndex() != ch->m_index)
	{
		GAMELOG << init("PARTY_BUG_GER KICK: NOT_BOSS", ch)
				<< "BOSSINDEX" << delim << ch->m_party->GetBossIndex() << delim
				<< "TARGETINDEX" << delim << index
				<< end;
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_NOT_BOSS);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	// �ڽ��� �ƴϰ�
	if (ch->m_index == index)
		return ;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyKickReqMsg(rmsg, ch->m_party->GetBossIndex(), index);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

void do_PartyAssistInfo(CPC* ch, CNetMsg::SP& msg)
{
	if (ch->m_party == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_NOT_PARTY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	int tindex;
	RefMsg(msg) >> tindex;

	int nListIndex = ch->m_party->FindMember(tindex);
	if (nListIndex == -1)
		return ;

	if(!ch->m_party->GetMemberByListIndex(nListIndex)->GetMemberPCPtr())
		return;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		PartyAssistInfoMsg(rmsg, ch->m_party->GetMemberByListIndex(nListIndex)->GetMemberPCPtr());
		SEND_Q(rmsg, ch->m_desc);
	}
}

void do_PartyChangeBoss(CPC* ch, CNetMsg::SP& msg)
{
	CLCString name(MAX_CHAR_NAME_LENGTH + 1);
	RefMsg(msg) >> name;

	GAMELOG << init("PARTY DEBUG CHANGEBOSS", ch)
			<< name
			<< end;

	if (ch->m_party == NULL)
	{
		GAMELOG << init("PARTY_BUG_GER CHANGEBOSS: NOT_PARTY", ch)
				<< name
				<< end;
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_NOT_PARTY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if (ch->m_party->GetBossIndex() != ch->m_index)
	{
		// ��Ƽ���� �ƴ� �޼��� ������
		GAMELOG << init("PARTY_BUG_GER CHANGEBOSS: NOT_BOSS", ch)
				<< "BOSSINDEX" << delim << ch->m_party->GetBossIndex() << delim
				<< "CHARINDEX" << delim << ch->m_index
				<< end;
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_NOT_BOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if (ch->m_pZone && ch->m_pZone->IsComboZone())
	{
		// �޺� �������� ��Ƽ�� ���ӿ� �ȵȴ�.
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_DO_NOT_CHANGE_BOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

#ifdef BATTLE_PARTY_BOSS_CHANGE
	if(ch->m_party->GetPartyType(0) == MSG_PARTY_TYPE_BATTLE &&
			ch->m_party->GetPartyType(3) == MSG_PARTY_TYPE_BATTLE &&
			ch->m_party->GetPartyType(4) == MSG_PARTY_TYPE_BATTLE)
	{
		int i;
		int min = -1;
		int max = -1;
		int memberLevel[8];
		memset(memberLevel, -1, 8*sizeof(int));
		for(i = 0; i < MAX_PARTY_MEMBER; i++)
		{
			CPartyMember* member = ch->m_party->GetMemberByListIndex(i);
			if(member)
			{
				if(member->GetMemberPCPtr())
				{
					memberLevel[i] = member->GetMemberPCPtr()->m_level;
				}
				else if(member && !member->GetMemberPCPtr())
				{
					memberLevel[i] = member->m_nLevel;
				}
			}
			if(memberLevel[i] > 0)
			{
				if(min == -1)
					min = memberLevel[i];
				else if(min > memberLevel[i])
					min = memberLevel[i];
				if(max == -1)
					max = memberLevel[i];
				else if(max < memberLevel[i])
					max = memberLevel[i];
			}
		}
		CPC* pc = PCManager::instance()->getPlayerByName(name, true);
		if(pc == NULL)
			return ;
		if(ABS(pc->m_level - min) > 10 || ABS(pc->m_level - max) > 10)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PartyErrorMsg(rmsg, MSG_PARTY_ERROR_LEVEL_CHANGE_BOSS);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
	}
#endif // BATTLE_PARTY_BOSS_CHANGE

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyChangeBossReqMsg(rmsg, ch->m_index, name);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

void do_PartyChangeType(CPC* ch, CNetMsg::SP& msg)
{
	GAMELOG << init("PARTY DEBUG CHNAGETYPE", ch)
			<< end;

	char cPartyType, cDiviType, cAllOneSet;

	RefMsg(msg) >> cPartyType      // �Ϲ�(�յ�),�Լ��켱,������,���ڿ��� ����
				>> cDiviType	   // ����ġ,������,����� ������ ����
				>> cAllOneSet;

 //new2022 ?
	if ((cPartyType > MSG_PARTY_TYPE_OPENBOX || cPartyType < 0  || cDiviType < 0 ||cDiviType > MSG_DIVITYPE_SPECIAL || cAllOneSet < 0  || cAllOneSet > MSG_PARTY_SETALLONE_ONE))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_NOT_PARTY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if (ch->m_party == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_NOT_PARTY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if (ch->m_party->GetBossIndex() != ch->m_index)
	{
		// ��Ƽ���� �ƴ� �޼��� ������
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_NOT_BOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if(cAllOneSet==MSG_PARTY_SETALLONE_ONE)
	{
		if(ch->m_party->GetPartyType(cDiviType) == cPartyType)
			return ;
	}

#if defined (LC_GAMIGO)
	if(cPartyType == MSG_PARTY_TYPE_BATTLE)
	{
		return ;
	}
#endif

	// ������ ��Ƽ
	if(cPartyType == MSG_PARTY_TYPE_BATTLE)
	{
		int bosslevel;

		if(ch->m_party->m_nRequest != -1)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PartyErrorMsg(rmsg, MSG_PARTY_ERROR_INVALID_LEVEL);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}

		bosslevel = ch->m_level;

		int i;

		for(i = 0; i < MAX_PARTY_MEMBER; ++i)
		{
			const CPartyMember* member = ch->m_party->GetMemberByListIndex(i);

			if(member && member->GetMemberPCPtr() && (member->GetMemberPCPtr()->m_index != ch->m_index) )
			{
				if(ABS(member->GetMemberPCPtr()->m_level - bosslevel) > 10)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					PartyErrorMsg(rmsg, MSG_PARTY_ERROR_INVALID_LEVEL);
					SEND_Q(rmsg, ch->m_desc);
					return ;
				}
			}
			else if(member && !member->GetMemberPCPtr())
			{
				if(ABS(member->m_nLevel - bosslevel) > 10)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					PartyErrorMsg(rmsg, MSG_PARTY_ERROR_INVALID_LEVEL);
					SEND_Q(rmsg, ch->m_desc);
					return ;
				}
			}
		}
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyChangeTypeReqMsg(rmsg, ch->m_index, cPartyType,cDiviType,cAllOneSet);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

//��Ƽ ��ü(20�� ���)
void do_PartyEndPartyReq(CPC* ch, CNetMsg::SP& msg)
{
	if (ch->m_party == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_NOT_PARTY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if (ch->m_party->GetBossIndex() != ch->m_index)
	{
		// ��Ƽ���� �ƴ� �޼��� ������
		CNetMsg::SP rmsg(new CNetMsg);
		PartyErrorMsg(rmsg, MSG_PARTY_ERROR_NOT_BOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ��Ƽ ��ü �ð� ����
	//-->
	time_t t_now;
	t_now = time(NULL);

	ch->m_party->SetEndPartyTime(t_now);
	//<--

	{
		// ��Ƽ�� ��ü���� 20�� �Ŀ� ��ü �� �˸�
		CNetMsg::SP rmsg(new CNetMsg);
		PartyEndPartyStartMsg(rmsg);
		ch->m_party->SendToAllPC(rmsg);
	}
}

void do_PartyOffline(CPC* ch, CNetMsg::SP& msg)
{

	if ( ( !ch && (ch->m_party != NULL)) || (ch->m_party == NULL) || (ch->m_bProcDisconnect == 0))
	{
		return;
	}

	CParty *pParty = ch->m_party;
	CPartyMember *member =  pParty->GetMemberByListIndex(pParty->FindMember(ch->m_index));
	if( member ) member->m_nLevel = 0;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperPartyOffline( rmsg, ch->m_party->GetBossIndex() , ch->m_index );
		SEND_Q(rmsg, gserver->m_helper);
	}
}

