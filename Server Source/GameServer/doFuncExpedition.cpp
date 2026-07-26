#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "Server.h"
#include "CmdMsg.h"
#include "doFunc.h"
#include "WarCastle.h"
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
#include "CloudThings.h"
#include "../ShareLib/packetType/ptype_old_do_move.h"
#endif

/////////////////
// ������ ���� �Լ�
void do_Expedition(CPC* ch, CNetMsg::SP& msg)
{
	// �Ⱥ��̸� ����
	if (!ch->m_bVisible)
		return ;

	unsigned char subtype;

	msg->MoveFirst();

	RefMsg(msg) >> subtype;

	switch (subtype)
	{
	case MSG_CREATE_REQ:						// ��Ƽ => ������ ��ȯ
		do_ExpedCreateReq(ch, msg);
		break;

	case MSG_INVITE_REQ:						// �ʴ� ��û
		do_ExpedInviteReq(ch, msg);
		break;

	case MSG_ALLOW_REQ:							// �ʴ� ����
		do_ExpedAllowReq(ch, msg);
		break;

	case MSG_REJECT_REQ:						// �ʴ� �ź� ��û
		do_ExpedRejectReq(ch, msg);
		break;

	case MSG_QUIT_REQ:							// Ż�� ��û
		do_ExpedQuitReq(ch, msg);
		break;

	case MSG_ENDEXPED_REQ:						// ������ ��ü
		do_ExpedEndExpedReq(ch, msg);
		break;

	case MSG_KICK_REQ:							// �߹� ��û
		do_ExpedKickReq(ch, msg);
		break;

	case MSG_CHANGETYPE_REQ:					// ������ Ÿ�� ����
		do_ExpedChangeTypeReq(ch, msg);
		break;

	case MSG_CHANGEBOSS_REQ:					// ���� ���� ����(����)
		do_ExpedChangeBossReq(ch, msg);
		break;

	case MSG_SETMBOSS_REQ:						// �δ��� �Ӹ�
		do_ExpedSetMBossReq(ch, msg);
		break;

	case MSG_RESETMBOSS_REQ:					// �δ��� �Ӹ� ����
		do_ExpedResetMBossReq(ch, msg);
		break;

	case MSG_MOVEGROUP_REQ:						// �׷� �̵�
		do_ExpedMoveGroupReq(ch, msg);
		break;

	case MSG_ADDMEMBER_REQ:						// ��� �߰�
		do_ExpedAddMemberReq(ch, msg);
		break;

	case MSG_VIEWDETAIL_REQ:					// ���캸��
		do_ExpedViewDetailReq(ch, msg);
		break;

	case MSG_SET_LABEL_REQ:						// ǥ�� ����
		do_ExpedSetLabelReq(ch, msg);
		break;
	case MSG_QUESTITEM_CHECK_REQ:
		do_ExpedSearchItemReq(ch, msg);			// Collect Trigger item - ������ Trigger ������ ����(�������� ���� ���)
		break;

	case MSG_EXPEND_OFFLINE:
		do_ExpendOffline(ch, msg);
		break;
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	case MSG_PARTYDUNGEON_JOIN:					//Cloud Expedition_Party_Dungeon
		do_ExpedPartyDungeonJoinReq(ch, msg);
		break;

	case MSG_PARTYDUNGEON_JOIN_MEMBER:					//Cloud Expedition_Party_Dungeon
		do_ExpedPartyDungeonJoinMember(ch, msg);
		break;

	case MSG_PARTYDUNGEON_RECALL_REQ:					//Cloud Expedition_Party_Dungeon
		do_ExpedPartyDungeonRecallReq(ch, msg);
		break;

	case MSG_PARTYDUNGEON_REWARD:					//Cloud Expedition_Party_Dungeon
		do_ExpedPartyDungeonRewardReq(ch, msg);
		break;
#ifdef CLOUD_EXPEDITION_REWORK
	case MSG_PARTYDUNGEON_DETAIL:					//Cloud Expedition_Party_Dungeon
		do_ExpedPartyDungeonDetailReq(ch, msg);
		break;
#endif
#endif
	}
}

//������ ����(��Ƽ ��ȯ)(����)
void do_ExpedCreateReq(CPC* ch, CNetMsg::SP& msg)
{
	GAMELOG << init("EXPED DEBUG CREATE REQ", ch)
			<< end;

	if(ch->m_Exped)
		return ;
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	if (ch->m_pZone->IsPartyRaidZone())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_CREATE_INVALIDZONE);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
#endif
#ifdef BLOCK_CHANGE_EXPED_IN_PARTY_RAID_ZONE
	if(ch->m_pZone->IsPartyRaidZone())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_CREATE_INVALIDZONE);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
#endif
	//��Ƽ�� �ҼӵǾ� �ִ°�?
	if (ch->m_party == NULL)
	{
		// ��Ƽ�� �Ҽӵ��� ����(��Ƽ ��ȯ �Ұ�)
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_PARTY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	//��Ƽ���ΰ�?
	if(ch->m_party->GetBossIndex() != ch->m_index)
	{
		// ��Ƽ���� �ƴϴ�.	(��Ƽ��ȯ �Ұ�)
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_PARTYBOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

#ifdef EXTREME_CUBE
	if ( ch->m_party->m_cubeUniqueIdx > 0 )
	{
		return ;
	}
#endif

	//��Ƽ �ɹ� �� �Ѹ��̶� �α׾ƿ� �Ǿ� ������ ������ ��ȯ �Ұ�.
	int onlineCount = ch->m_party->GetMemberCountOnline();
	int totalCount = ch->m_party->GetMemberCount();
	if( onlineCount != totalCount )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_EXIST_LOGOUT_MEMBER);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpedCreateReqMsg(rmsg, ch->m_party->GetBossIndex(),ch->GetName());
		SEND_Q(rmsg, gserver->m_helper);
	}
}

//������ �ʴ�(����)
void do_ExpedInviteReq(CPC* ch, CNetMsg::SP& msg)
{
	int destindex;

	RefMsg(msg) >>  destindex;

	GAMELOG << init("EXPED DEBUG INVITE REQ", ch)
			<< "DESTINDEX" << delim << destindex
			<< end;

	if (ch->m_index == destindex)
		return ;

	CPC * pTargetPC = PCManager::instance()->getPlayerByCharIndex(destindex);
	if(pTargetPC == NULL)
		return;

	if(pTargetPC->m_party != NULL)
	{
		//����: �ٸ� �׷쿡 �ҼӵǾ� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_ALREADY_JOIN_OTHER);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	if (ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	if(ch->m_Exped->GetMemberCount() >= MAX_EXPED_MEMBER)
	{
		//����: �� �̻� ������� �߰��� �� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_FULL_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	if(ch->IsSetPlayerState(PLAYER_STATE_PKMODE) || pTargetPC->IsSetPlayerState(PLAYER_STATE_PKMODE))
	{
		return ;
	}

	//���� üũ
	//-->
	CExpedMember* pMember = NULL;
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	if(!pMember)
		return;

	if(pMember && ((pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_BOSS) && (pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_MBOSS)) )
	{
		//����: ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	//<--

	if(pTargetPC->m_Exped  && ch->m_Exped != pTargetPC->m_Exped)
	{
		//����: �̹� �����뿡 �ҼӵǾ� �ֽ��ϴ�.
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_ALREADY_JOIN_ME);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CPC* pBossPC = ch;
	// ��û ĳ���Ͱ� �δ����̸� �������� ã�Ƽ� pBossPC�� ����
	if (pMember->GetMemberType() == MSG_EXPED_MEMBERTYPE_MBOSS)
	{
		int nBossIndex = ch->m_Exped->GetBossIndex();
		pBossPC = PCManager::instance()->getPlayerByCharIndex(nBossIndex);

		if( !pBossPC )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpedInviteReqMsg(rmsg, pBossPC->m_index, pBossPC->GetName(), destindex,pTargetPC->GetName());
		SEND_Q(rmsg, gserver->m_helper);
	}
}

//�ʴ� ����(���)
void do_ExpedAllowReq(CPC* ch, CNetMsg::SP& msg)
{
	// ������ ������ �ְ�
	GAMELOG << init("EXPED DEBUG ALLOW REQ", ch)
			<< end;

	if(ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpedAllowReqMsg(rmsg, ch->m_Exped->GetBossIndex(), ch->m_index, ch->GetName(), ch->m_level );
		SEND_Q(rmsg, gserver->m_helper);
	}

	{
		// ��Ƽ ��Ī���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_EXTEND);
		RefMsg(rmsg) << MSG_EX_PARTY_MATCH
					 << MSG_EX_PARTY_MATCH_DEL_REQ;
		do_Extend(ch, rmsg);
	}
}

//�ʴ� �ź�(���)
void do_ExpedRejectReq(CPC* ch, CNetMsg::SP& msg)
{
	GAMELOG << init("EXPED DEBUG REJECT REQ", ch)
			<< end;

	if(ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CNetMsg::SP rmsg(new CNetMsg);
	HelperExpedRejectReqMsg(rmsg, ch->m_Exped->GetBossIndex(), ch->m_index);
	SEND_Q(rmsg, gserver->m_helper);
}

//Ż��(���)
void do_ExpedQuitReq(CPC* ch, CNetMsg::SP& msg)
{
	int nQuitMode;			// ����,������ ����

	RefMsg(msg) >> nQuitMode;

	GAMELOG << init("EXPED DEBUG QUIT REQ", ch)
			<< "QUITMODE" << delim << nQuitMode
			<< end;

	if(ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpedQuitReqMsg(rmsg, ch->m_Exped->GetBossIndex(), ch->m_index, nQuitMode);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

//������ ��ü(����)(20�� ���)
void do_ExpedEndExpedReq(CPC* ch, CNetMsg::SP& msg)
{
	GAMELOG << init("EXPED DEBUG ENDEXPED REQ", ch)
			<< end;

	if (ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	//���� üũ
	//-->
	CExpedMember* pMember = NULL;
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	if(!pMember)
		return;

	if(pMember && (pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_BOSS))
	{
		//����: ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	//<--

	// ������ ��ü �ð� ����
	//-->
	time_t t_now;
	t_now = time(NULL);

	ch->m_Exped->SetEndExpedTime(t_now);
	//<--

	{
		// ������� ��ü���� 20�� �Ŀ� ��ü �� �˸�
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedEndExpedStartMsg(rmsg);
		ch->m_Exped->SendToAllPC(rmsg);
	}
}

//�߹�(����,�δ���)
void do_ExpedKickReq(CPC* ch, CNetMsg::SP& msg)
{
	int nTargetIndex;
	RefMsg(msg) >> nTargetIndex;

	GAMELOG << init("EXPED DEBUG KICK REQ", ch)
			<< "TARGETINDEX" << delim << nTargetIndex
			<< end;

	if (ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if (ch->m_index == nTargetIndex)
		return ;

	//���� üũ
	//-->
	CExpedMember* pMember = NULL;
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	if(!pMember)
		return;
	if(pMember && (pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_BOSS && pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_MBOSS ))
	{
		//����: ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	if(ch->m_Exped->GetBossIndex() == nTargetIndex)
	{
		//����: ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpedKickReqMsg(rmsg, ch->m_Exped->GetBossIndex(), nTargetIndex);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

//���� ���� ����(����)
void do_ExpedChangeBossReq(CPC* ch, CNetMsg::SP& msg)
{
	int nChangeMode, nNewBossIndex;

	RefMsg(msg) >> nChangeMode						// ����,�ڵ�
				>> nNewBossIndex;					// �ڵ�(-1)

	GAMELOG << init("EXPED DEBUG CHANGEBOSS REQ", ch)
			<< "CHANGEMODE" << delim << nChangeMode << delim
			<< "NEWBOSSINDEX" << delim << nNewBossIndex << delim
			<< end;

	if (ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	//���� üũ
	//-->
	CExpedMember* pMember = NULL;
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	if(!pMember)
		return;

	if(pMember && (pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_BOSS))
	{
		//����: ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	//<--

	//�ڱ� �ڽ� ���� üũ
	if(ch->m_index == nNewBossIndex)
		return;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpedChangeBossReqMsg(rmsg, ch->m_index, nChangeMode, nNewBossIndex);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

//Ÿ�� ����(����)
void do_ExpedChangeTypeReq(CPC* ch, CNetMsg::SP& msg)
{
	char cExpedType, cDiviType;
	RefMsg(msg) >> cExpedType
				>> cDiviType;

	GAMELOG << init("EXPED DEBUG CHANGETYPE REQ", ch)
			<< "EXPEDTYPE" << delim << cExpedType << delim
			<< "DIVITYPE" << delim << cDiviType << delim
			<< end;

	if (cExpedType > MSG_EXPED_TYPE_OPENBOX || cExpedType < 0 || cDiviType > MSG_DIVITYPE_SP || cDiviType < 0) //new2022
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if (ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	//���� üũ
	//-->
	CExpedMember* pMember = NULL;
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	if(!pMember)
		return;

	if(pMember && (pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_BOSS))
	{
		//����: ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	//<--

	if(ch->m_Exped->GetExpedType(cDiviType) ==  cExpedType)
		return ;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpedChangeTypeReqMsg(rmsg, ch->m_index, cExpedType, cDiviType);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

//�δ��� �Ӹ�(����)
void do_ExpedSetMBossReq(CPC* ch, CNetMsg::SP& msg)
{
	int nNewMBossIndex;

	RefMsg(msg) >> nNewMBossIndex;

	GAMELOG << init("EXPED DEBUG SETMBOSS REQ", ch)
			<< "NEW MBOSS INDEX" << delim << nNewMBossIndex
			<< end;

	if (ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	//���� üũ
	//-->
	CExpedMember* pMember = NULL;
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	if(!pMember)
		return;

	if(pMember && (pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_BOSS))
	{
		//����: ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	//<--

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpedSetMBossReqMsg(rmsg, ch->m_index, nNewMBossIndex);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

//�δ��� ����(����)
void do_ExpedResetMBossReq(CPC* ch, CNetMsg::SP& msg)
{
	int nNewMBossIndex;

	RefMsg(msg) >> nNewMBossIndex;

	GAMELOG << init("EXPED DEBUG RESETMBOSS REQ", ch)
			<< "NEW MBOSS INDEX" << delim << nNewMBossIndex
			<< end;

	if (ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	//���� üũ
	//-->
	CExpedMember* pMember = NULL;
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	if(!pMember)
		return;

	if(pMember && (pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_BOSS))
	{
		//����: ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	//<--

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpedResetMBossReqMsg(rmsg, ch->m_index, nNewMBossIndex);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

//�׷� �̵�(����)
void do_ExpedMoveGroupReq(CPC* ch, CNetMsg::SP& msg)
{
	int nSourceGroup, nMoveCharIndex, nTargetGroup, nTargetListindex;

	RefMsg(msg) >> nSourceGroup
				>> nMoveCharIndex
				>> nTargetGroup
				>> nTargetListindex;

	GAMELOG << init("EXPED DEBUG MOVEGROUP REQ", ch)
			<< "SOURCE GROUP" << delim << nMoveCharIndex << delim
			<< "MOVE CHAR INDEX" << delim << nMoveCharIndex << delim
			<< "TARGET GROUP" << delim << nTargetGroup << delim
			<< "TARGET CHAR INDEX" << delim << nTargetListindex
			<< end;
 //new2022 ?
	if ((nSourceGroup <  0 ||nSourceGroup >= MSG_EXPED_GROUP_COUNT || nTargetGroup < 0 || nTargetGroup >= MSG_EXPED_GROUP_COUNT))
	{
		return;
	}
 //new2022 ?
	if (nSourceGroup >= MSG_EXPED_GROUP_COUNT || nTargetGroup >= MSG_EXPED_GROUP_COUNT)
	{
		LOG_INFO("Crash teste ????????");
		return;
	}

	if (ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	//���� üũ
	//-->
	CExpedMember* pMember = NULL;
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	if(!pMember)
		return;

	if(pMember && (pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_BOSS))
	{
		//����: ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	//<--

	//�̵� ��� ���� üũ
	//-->
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(nMoveCharIndex);
	if(!pMember)
		return;

	if(pMember && (pMember->GetMemberType() == MSG_EXPED_MEMBERTYPE_BOSS || (pMember->GetMemberType() == MSG_EXPED_MEMBERTYPE_MBOSS)))
	{
		//����: ��������, �δ��� �̵� �Ұ�
		return;
	}
	//<--

	// ����� ��� �ִ��� üũ
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByListIndex(nTargetGroup, nTargetListindex);
	if(pMember)
	{
		//����: ��� ���� ����
		return;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpedMoveGroupReqMsg(rmsg, ch->m_index, nSourceGroup, nMoveCharIndex, nTargetGroup, nTargetListindex);
		SEND_Q(rmsg, gserver->m_helper);
	}
}

//��� �߰�(����)
void do_ExpedAddMemberReq(CPC* ch, CNetMsg::SP& msg)
{
	CLCString addCharName(MAX_CHAR_NAME_LENGTH + 1);

	RefMsg(msg) >>	addCharName;

	GAMELOG << init("EXPED DEBUG ADDMEMBER REQ", ch)
			<< "ADDCHARNAME" << delim << addCharName
			<< end;

	CPC * pTargetPC = PCManager::instance()->getPlayerByName(addCharName,false);
	if(pTargetPC == NULL)
		return;

	if(ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	//���� üũ
	//-->
	CExpedMember* pMember = NULL;
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	if(!pMember)
		return;

	if(pMember && (pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_BOSS))
	{
		//����: ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	//<--

	// Ÿ���� EXPED_TYPE_BATTLE �̸� tch�� ch�� ���� ���̸� �˻�
	// ���̰� +- 10�̻��̸� ERROR;
	if (ch->m_Exped->GetExpedType(MSG_DIVITYPE_EXP) == MSG_EXPED_TYPE_BATTLE)
	{
		if (ABS(pTargetPC->m_level - ch->m_level) > 10)
		{
			return ;
		}
	}

	{
		//�ʴ� ��û
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpedInviteReqMsg(rmsg, ch->m_index, ch->GetName(), pTargetPC->m_index,pTargetPC->GetName());
		SEND_Q(rmsg, gserver->m_helper);
	}
}

//���� ����(����,�δ���)
void do_ExpedViewDetailReq(CPC* ch, CNetMsg::SP& msg)
{
	int nGroup;
	int nDestIndex;

	RefMsg(msg) >> nGroup
				>> nDestIndex;

	GAMELOG << init("EXPED DEBUG VIEWDETAIL REQ", ch)
			<< "GROUP" << delim << nGroup << delim
			<< "DEST INDEX" << delim << nDestIndex
			<< end;

	// if(ch->m_Exped == NULL)
	// {
	// 	//����: �����뿡 �Ҽ� �Ǿ� ���� ����
	// 	CNetMsg::SP rmsg(new CNetMsg);
	// 	ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
	// 	SEND_Q(rmsg, ch->m_desc);
	// 	return;
	// }

	//���� üũ
	//-->
	// CExpedMember* pMember = NULL;
	// pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	// if(!pMember)
	// 	return;

	// if(pMember && (pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_BOSS && pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_MBOSS ))
	// {
	// 	//����: ���� ����
	// 	CNetMsg::SP rmsg(new CNetMsg);
	// 	ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
	// 	SEND_Q(rmsg, ch->m_desc);
	// 	return;
	// }
	//<--

	CPC * pPC = PCManager::instance()->getPlayerByCharIndex(nDestIndex);
	if(pPC == NULL)
		return;

	// ������
	//-->
	CPet* pet = pPC->m_petList;
	while (pet)
	{
		if(pet->IsWearing())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ExpedViewDail_ExPetMsg(rmsg, pet);
			SEND_Q(rmsg, ch->m_desc);
		}

		pet = pet->m_nextPet;
	}

	CAPet* apet = pPC->m_pApetlist;
	while ( apet )
	{
		if(apet->IsWearing())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ExpedViewDail_ExAPetMsg(rmsg, apet);
			SEND_Q(rmsg, ch->m_desc);
		}
		apet = apet->m_pNextPet;
	}

	{
		//�κ��丮 ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedViewDail_InvenMsg(msg, pPC);
		SEND_Q(msg, ch->m_desc);
	}
}

//ǥ�� ����
void do_ExpedSetLabelReq(CPC* ch, CNetMsg::SP& msg)
{
	int nType,nMode,nLabel,nDestIndex;

	RefMsg(msg) >> nType				// pc,npc ����
				>> nMode				// ����,���� ����
				>> nLabel				// �� Ÿ��
				>> nDestIndex;			// ���� ��� �ε���(charindex,mob index)

	GAMELOG << init("EXPED DEBUG SETLABEL REQ", ch)
			<< "TYPE" << delim << nType << delim
			<< "MODE" << delim << nMode << delim
			<< "LABEL" << delim << nLabel << delim
			<< "DESTINDEX" << delim << nDestIndex
			<< end;

	if(!ch->IsExped())
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if(ch->m_nJoinInzone_ZoneNo == -1 &&  ch->m_nJoinInzone_RoomNo == -1)
	{
		// ���� ���ΰ� �ƴϾ ǥ�� ���� �Ұ�.
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_SETLABEL_NOTINZONE);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if(nType == MSG_EXPED_SETLABEL_TYPE_NPC)
	{
		CArea* area = ch->m_pArea;
		if(!area)	return;

		CCharacter* tch = area->FindCharInCell(ch, nDestIndex, (MSG_CHAR_TYPE)MSG_CHAR_NPC);
		if(tch == NULL || !IS_NPC(tch))	return;

		if(nMode == MSG_EXPED_SETLABEL_MODE_SET)
		{
			tch->SetExpedLabel(nLabel);
		}
		else if(nMode == MSG_EXPED_SETLABEL_MODE_RESET)
		{
			tch->SetExpedLabel(-1);
		}
	}

	else if(nType == MSG_EXPED_SETLABEL_TYPE_PC)
	{
		CArea* area = ch->m_pArea;
		if(!area)	return;

		CCharacter* tch = area->FindCharInCell(ch, nDestIndex, (MSG_CHAR_TYPE)MSG_CHAR_PC);
		if(tch == NULL || !IS_PC(tch))	return;

		if(nMode == MSG_EXPED_SETLABEL_MODE_SET)
		{
			tch->SetExpedLabel(nLabel);
		}
		else if(nMode == MSG_EXPED_SETLABEL_MODE_RESET)
		{
			tch->SetExpedLabel(-1);
		}
	}

	{
		//����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedSetLabelRepMsg(rmsg, nType,nMode,nLabel,nDestIndex);
		ch->m_Exped->SendToAllPC(rmsg);
	}
}

// Write : �ǻ��
// Date : 20090825
// �̵����� ���� Trigger Item�� ���������� �������� �������� ��ư�� ���� Item�� �������� �Լ�
void do_ExpedSearchItemReq(CPC* ch, CNetMsg::SP& msg) //
{
	GAMELOG << init("EXPED DEBUG SEARCH TRIGGER ITEM REQ", ch)
			<< "BOSS CHARACTER INDEX" << delim
			<< ch->m_index << end;

	// �Ѿ�� �ɸ��Ͱ� NULL���� Ȯ��.
	if( ch == NULL )
		return ;

	// ���� �ɸ��Ͱ� �����뿡 �ҼӵǾ� �ִ��� Ȯ��
	// �����뿡 �ҼӵǾ� ���� ������ MSG_EXPED_ERROR_NOT_EXPED �߼�
	// TODO:

	if (ch->m_Exped == NULL)
	{
		//����: �����뿡 �Ҽ� �Ǿ� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPED);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	// ���� �ɸ��Ͱ� ������ list���� ������������ Ȯ��
	// ���������� �ƴ϶�� MSG_EXPED_ERROR_NOT_EXPEDBOSS �߼�
	// TODO:

	CExpedMember* pMember = NULL;
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	if(!pMember)
		return;

	if(pMember && (pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_BOSS))
	{
		//����: ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedErrorMsg(rmsg, MSG_EXPED_ERROR_NOT_EXPEDBOSS);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ����������� ����Ʈ ������ �κ� ����
	pMember = NULL;
	bool DidCollect = false;			// �ѹ��̶� Trigger Item�� ���������� TRUE, �ƴϸ� FALSE
	bool UsualProcess = true;			// ���� �� ������������ ���� ���μ����� ����� ���FALSE, ���������� ����� ��� TRUE;
	int GroupNumber = 0;				// �� �������� Group�� ī��Ʈ �ϱ� ���� ����
	int CountMemberEachbyGroup = 0;		// �� �׷�� �ο����� ī��Ʈ �ϱ� ���� ����
	CPC* FromChar;
	CPC* BossChar;

	BossChar = ch;

	for( GroupNumber = 0; GroupNumber < MAX_EXPED_GROUP; GroupNumber++ )
	{
		for( CountMemberEachbyGroup = 0; CountMemberEachbyGroup < MAX_EXPED_GMEMBER; CountMemberEachbyGroup++ )
		{
			pMember = BossChar->m_Exped->GetMemberByListIndex(GroupNumber, CountMemberEachbyGroup);	// �����ɸ��Ϳ��� ���� �ִ� ����������� ������ ����Ʈ���� ����.

			if( pMember != NULL && pMember->GetMemberType() != MSG_EXPED_MEMBERTYPE_BOSS )			// ��������� NULL�ƴϰ�, ���������� �ƴҶ�,
			{
				FromChar = PCManager::instance()->getPlayerByCharIndex(pMember->GetCharIndex());						// ���Ӽ��� �÷��̾� ����Ʈ���� �ɸ��� �ε����� ���� �÷��̾� ������ ����.
				if( FromChar )
					SearchTriggerItem(FromChar, BossChar, DidCollect, UsualProcess);					// ��������� ���� �ִ� Trigger Item�� ����
			}
		}
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		if( (DidCollect == true) && (UsualProcess == true) )											// �Ѱ��� �������̶� ������ �����ϰ�, ���������� ���� ���μ����� ���ᰡ �Ǹ�
		{
			ExpedSearchTriggerItemMsg(rmsg, MSG_GET_QUESTITEM_SUCCESS_REP);								// ���� ���� �޽��� �߼�
			GAMELOG << init("EXPED DEBUG COLLECT TRIGGER ITEM SUCCESS", ch)
					<< "BOSS CHARACTER INDEX" << delim
					<< ch->m_index << end;
		}
		else																							// �׿��� ���
		{
			// 1. ������ ����Ʈ �κ��� ���� ���־� �������� �; ���������� ���
			ExpedSearchTriggerItemMsg(rmsg, MSG_GET_QUESTITEM_FAILED_REP);								// 2. �ý����� ������ ���� ���
			GAMELOG << init("EXPED DEBUG COLLECT TRIGGER ITEM FAILED", ch)								// 3. ����������� ���� ������ Trigger Item�� ���� ���
					<< "BOSS CHARACTER INDEX" << delim
					<< ch->m_index << end;
		}
		SEND_Q(rmsg, BossChar->m_desc);
	}
}

void SearchTriggerItem(CPC* FromChar, CPC* BossChar, bool& DidCollect, bool& UsualProcess)												// ������� TriggerItem üũ
{
	item_search_t vec;
	FromChar->m_inventory.searchFlagByItemProto(ITEM_FLAG_TRIGGER, vec);

	item_search_t::iterator it = vec.begin();
	item_search_t::iterator endit = vec.end();
	for (; it != endit; ++it)
	{
		GiveTriggerItemMemberToBoss(FromChar, BossChar, *it, DidCollect, UsualProcess);
	}
}

void GiveTriggerItemMemberToBoss(CPC* FromChar, CPC* BossChar, item_search_pair_t& p, bool& DidCollect, bool& UsualProcess)
{
	if( !BossChar )														// �������� �ɸ��Ͱ� NULL�� ��
	{
		UsualProcess = false;
		return ;
	}

	CItem* item = p.pItem;
	if (item == NULL)
	{
		UsualProcess = false;
		return ;
	}

	if(item->Count() < 1)												// ������ ������ 0������ �� ���� false
	{
		UsualProcess = false;
		return ;
	}

	CItem* bossitem = gserver->m_itemProtoList.CreateItem(item->getDBIndex(), -1, 0, 0, item->getItemCount());

	if (BossChar->m_inventory.addItem(bossitem))
	{
		//�����ϸ� ���� �κ��丮������ ���Ÿ� ����� �Ѵ�.
		{
			FromChar->m_inventory.deleteItemByItem(item);
		}

		DidCollect = true;
		GAMELOG << init("EXPED DEBUG GIVE TRIGGER ITEM SUCCESS") << end;
		GAMELOG	<< init("FROM MEMBER") << delim << FromChar->m_name << delim
				<< "CHARACTER INDEX" << delim << FromChar->m_index << end;
		GAMELOG << init("TO BOSS") << delim << BossChar->m_name << delim
				<< "CHARACTER INDEX" << delim << BossChar->m_index << end;

		GAMELOG	<< init("GIVE ITEM") << bossitem->m_itemProto->getItemName() << bossitem->Count() << "EA" << end;
	}
	else
	{
		delete bossitem;

		GAMELOG << init("EXPED DEBUG GIVE TRIGGER ITEM FAILED") << end;
		GAMELOG	<< init("FROM MEMBER") << delim << FromChar->m_name << delim
				<< "CHARACTER INDEX" << delim << FromChar->m_index << end;
		GAMELOG << init("TO BOSS") << delim << BossChar->m_name << delim
				<< "CHARACTER INDEX" << delim << BossChar->m_index << end;
		GAMELOG	<< init("GIVE ITEM") << bossitem->m_itemProto->getItemName() << bossitem->Count() << "EA" << end;

		UsualProcess = false;
	}
}

void do_ExpendOffline(CPC* ch, CNetMsg::SP& msg)
{
	if( !ch || ch->m_Exped != NULL )
		return;	
	
	// ������� �α� �ƿ� ó��
	CExpedMember* pMember = NULL;
	pMember = (CExpedMember*) ch->m_Exped->GetMemberByCharIndex(ch->m_index);
	if(pMember) pMember->m_nLevel = 0;

	// ���۷� �α� �ƿ� ó��
	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperExpendOfflineMsg( rmsg, ch->m_Exped->GetBossIndex() , ch->m_index );
		SEND_Q(rmsg, gserver->m_helper);
	}
	return;
}
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
void do_ExpedPartyDungeonJoinReq(CPC* ch, CNetMsg::SP& msg)
{
	if (ch == NULL)
		return;

	int nAmendIndex;
	int zone;
	int difficulty;
	int finditem = -1;

	RefMsg(msg) >> nAmendIndex;
	RefMsg(msg) >> difficulty;
	RefMsg(msg) >> zone;

#ifdef CLOUD_EXPEDITION_REWORK
	int nCount = gserver->m_PartyConfig.GetZoneCount(difficulty);
#endif

	if (nAmendIndex < 0 || nAmendIndex > nCount)
	{
		GAMELOG << init("HACKING INVALID AMEND INDEX JOIN", ch)
			<< "AMEND INDEX" << delim << nAmendIndex
			<< "COUNT INDEX" << delim << nCount
			<< end;
		ch->m_desc->Close("hack user is dis invalid amend index.");
		return;
	}

	if (difficulty < 0 || difficulty > 2)
	{
		GAMELOG << init("HACKING INVALID DIFFICULTY", ch)
			<< "difficulty" << delim << difficulty
			<< end;
		ch->m_desc->Close("hack user is dis invalid difficulty.");
		return;
	}

	finditem = gserver->m_PartyConfig.GetDungeonNeedItem(zone, difficulty);

	if (ch->m_pZone->m_index == zone)
	{
		GAMELOG << init("ERROR MOVE TO PARTY ZONE ALREADY", ch)
			<< end;
		return;
	}


	if (zone >= 50 && finditem == -1 || finditem != gserver->m_PartyConfig.GetDungeonNeedItem(zone, difficulty))
	{
		GAMELOG << init("ERROR MOVE TO PARTY WORNG ITEM IDX", ch)
			<< end;
		return;
	}


#ifdef CLOUD_EXPEDITION_SOLO_DUNGEONS	
	//if(ch->m_nSoloDifficulty != -1)
	if (((ch->m_level < (int)gserver->m_PartyConfig.GetDungeonLevel(zone, difficulty))))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		RaidErrorMsg(rmsg, MSG_RAID_ERROR_INZONE_JOIN_INVALIDELEVEL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	ch->m_nSoloDifficulty = difficulty;
#endif

#ifndef CLOUD_EXPEDITION_SOLO_DUNGEONS	
	if (ch->m_party == NULL || !ch->IsParty())
		return;

	if (ch->m_party->GetBossIndex() != ch->m_index)
		return;

	CParty* party = gserver->FindPartyByBossIndex(ch->m_index);
	if (!party)
		return;

	int ret = party->FindMember(ch->m_index);
	if (ret == -1)
		return;

	if (ch->m_party->m_nDifficulty != -1)
		ch->m_party->m_nDifficulty = difficulty;


#ifdef CLOUD_EXPEDITION_REWORK
	int MemberCount = ((int)gserver->m_PartyConfig.GetDungeonMember(zone, difficulty) + 1);

		if (party->GetMemberCount() < MemberCount)
#else
	if (party->GetMemberCount() < 3)
#endif
	{
		GAMELOG << init("JOIN TO PARTY DUNGEON AREA MEMBER COUNT", ch)
			<< "MEMBER COUNT" << delim << party->GetMemberCount()
			<< end;
		return;
	}


	GAMELOG << init("JOIN TO PARTY DUNGEON AREA MEMBER COUNT", ch)//debug
		<< "MEMBER COUNT" << delim << party->GetMemberCount()
		<< end;
#endif

	GAMELOG << init("EXPED PARTY DUNGEON JOIN REQ", ch)
		<< "AMEND INDEX" << delim << nAmendIndex
		<< end;

	if (gserver->m_eventAutomationMgr.isActiveEvent(707) == false)
	{
#ifdef CLOUD_EXPEDITION_REWORK		
		item_search_t vec;
		int nKeyCount = ch->m_inventory.searchItemByCondition(finditem, 0, 0, vec);
		int nServerCount = (int)gserver->m_PartyConfig.GetDungeonNeedCount(zone, difficulty);

		if (nKeyCount < nServerCount)
		{
			GAMELOG << init("ERROR MISSING ITEM TO PARTY DUNGEON JOIN", ch)
				<< end;
			//CNetMsg::SP rmsg(new CNetMsg);
			//EventSummerVacation2007FigureMsg(rmsg, MSG_EVENT_SUMMER_VACATION_2007_ERROR_NOITEM, 0, finditem, nServerCount);
			//SEND_Q(rmsg, ch->m_desc);
			return;
		}

		ch->m_inventory.deleteItem(vec, nServerCount);

#ifndef CLOUD_EXPEDITION_SOLO_DUNGEONS	
		do_ExpedPartyDungeonRecallReq(ch, msg);

		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_RAID);
			RefMsg(rmsg) << (unsigned char)MSG_RAID_INZONE_JOIN
				<< (int)zone
				<< difficulty;
			do_Raid(ch, rmsg);
			GAMELOG << init("JOIN TO PARTY DUNGEON AREA", ch)
				<< end;
		}
#else
		{
			CNetMsg::SP rmsg(new CNetMsg);
			RequestClient::makeGoZone(rmsg, (int)zone, 0, -1);
			do_GoZone(ch, rmsg);
			GAMELOG << init("JOIN TO SOLO DUNGEON AREA", ch)
				<< end;
		}
#endif
	}
#else
		CItem* pItem = ch->m_inventory.FindByDBIndex(finditem, 0, 0);
		if (pItem)
		{
			ch->m_inventory.decreaseItemCount(pItem, 1);
#ifndef CLOUD_EXPEDITION_SOLO_DUNGEONS	
			do_ExpedPartyDungeonRecallReq(ch, msg);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_RAID);
				RefMsg(rmsg) << (unsigned char)MSG_RAID_INZONE_JOIN
					<< (int)zone
					<< difficulty;
				do_Raid(ch, rmsg);
				GAMELOG << init("JOIN TO PARTY DUNGEON AREA", ch)
					<< end;
			}
#else
			{
				CNetMsg::SP rmsg(new CNetMsg);
				RequestClient::makeGoZone(rmsg, (int)zone, 0, -1);
				do_GoZone(ch, rmsg);
				GAMELOG << init("JOIN TO SOLO DUNGEON AREA", ch)
					<< end;
			}
#endif
		}
		else
		{
			GAMELOG << init("ERROR MISSING ITEM TO PARTY DUNGEON JOIN", ch)
				<< end;
			CNetMsg::SP rmsg(new CNetMsg);
			EventSummerVacation2007FigureMsg(rmsg, MSG_EVENT_SUMMER_VACATION_2007_ERROR_NOITEM, 0, finditem, 1);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}
}
#endif
	else
	{
#ifndef CLOUD_EXPEDITION_SOLO_DUNGEONS	
		do_ExpedPartyDungeonRecallReq(ch, msg);

		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_RAID);
			RefMsg(rmsg) << (unsigned char)MSG_RAID_INZONE_JOIN
				<< (int)zone
				<< difficulty;
			do_Raid(ch, rmsg);
			GAMELOG << init("JOIN TO PARTY DUNGEON AREA", ch)
				<< end;
		}
#else
		{
			CNetMsg::SP rmsg(new CNetMsg);
			RequestClient::makeGoZone(rmsg, (int)zone, 0, -1);
			do_GoZone(ch, rmsg);
			GAMELOG << init("JOIN TO SOLO DUNGEON AREA", ch)
				<< end;
		}
#endif
	}
}

void do_ExpedPartyDungeonJoinMember(CPC* ch, CNetMsg::SP& msg)
{
#ifdef CLOUD_EXPEDITION_SOLO_DUNGEONS	
	return;
#endif

	if (ch == NULL)
		return;

	if (ch->m_party == NULL || !ch->IsParty())
		return;

	CParty* party = gserver->FindPartyByBossIndex(ch->m_party->GetBossIndex());
	if (!party)
		return;

	CPC* pPC = PCManager::instance()->getPlayerByCharIndex(party->GetBossIndex());
	if (pPC == NULL)
		return;

	int zone = pPC->m_pZone->m_index;
	int difficulty;

	difficulty = pPC->m_pArea->m_RaidDifficulty;//party->m_nDifficulty; pPC->m_pArea->m_RaidDifficulty;

	if (difficulty < 0 || difficulty > 2)
	{
		GAMELOG << init("HACKING INVALID DIFFICULTY", ch)
			<< "difficulty" << delim << difficulty
			<< end;
		ch->m_desc->Close("hack user is dis invalid difficulty.");
		return;
	}

	
#ifdef CLOUD_EXPEDITION_REWORK
	int MemberCount = ((int)gserver->m_PartyConfig.GetDungeonMember(zone, difficulty) + 1);

	if (party->GetMemberCount() < MemberCount)
#else
	if (party->GetMemberCount() < 3)
#endif
	{
		GAMELOG << init("JOIN TO PARTY DUNGEON AREA MEMBER COUNT", ch)
			<< "MEMBER COUNT" << delim << party->GetMemberCount()
			<< end;
		return;
	}

	GAMELOG << init(" MEMBER EXPED PARTY DUNGEON JOIN REQ", ch)
		<< "AMEND INDEX" << delim << zone
		<< end;

	
	if (ch->m_pZone->m_index == pPC->m_pZone->m_index)
	{
		GAMELOG << init("MEMBER MOVE TO PARTY LEADER AREA", ch)
			<< end;
		GoTo(ch, GET_YLAYER(pPC), GET_X(pPC), GET_Z(pPC), ch->m_pArea->GetHeight(GET_YLAYER(pPC), GET_X(pPC), GET_Z(pPC)), GET_R(ch));
	}
	else
	{
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_RAID);
		RefMsg(rmsg) << (unsigned char)MSG_RAID_INZONE_JOIN
			<< (int)zone
			<< difficulty;
		do_Raid(ch, rmsg);
		GAMELOG << init("MEMBER JOIN TO PARTY DUNGEON AREA", ch)
			<< end;
	}
}

void do_ExpedPartyDungeonRecallReq(CPC* ch, CNetMsg::SP& msg)
{
#ifdef CLOUD_EXPEDITION_SOLO_DUNGEONS	
	return;
#endif	

	if (ch == NULL)
		return;

	int zone;

	RefMsg(msg) >> zone;


	if (ch->m_party == NULL || !ch->IsParty())
		return;

	if (ch->m_party->GetBossIndex() != ch->m_index)
		return;

	GAMELOG << init("EXPED PARTY DUNGEON RECALL REQ", ch)
		<< end;

	//if(ch->m_pZone->m_index != ZONE_COMBO_DUNGEON)
		//return ;

	//if(!ch->m_pArea)
		//return ;

	//if(ch->m_pArea->GetPCCount() >= MAX_PARTY_MEMBER)
		//return ;

	CParty* party = gserver->FindPartyByBossIndex(ch->m_party->GetBossIndex());
	if (!party)
		return;

	//GAMELOG << init("EXPED PARTY RECALL ON JOIN", ch)
			//<< end;
	if (party)
	{//Cloud callmembers

		for (int i = 0; i < MAX_PARTY_MEMBER; ++i)
		{
			if (party->GetMemberByListIndex(i) &&
				party->GetMemberByListIndex(i)->GetMemberPCPtr())
			{
				CPC* pc = party->GetMemberByListIndex(i)->GetMemberPCPtr();
				//if(pc->m_pZone->m_index != zone)//ZONE_COMBO_DUNGEON
				if (pc)
				{
					if (/*pc->m_pZone->m_index != zone ||*/ pc->m_party->GetBossIndex() != pc->m_index)
					{
						CNetMsg::SP rmsg(new CNetMsg);
						ExpedPartyDungeon_CallMembersMsg(msg, ch, zone);
						SEND_Q(msg, pc->m_desc);//party->GetMemberByListIndex(i)->GetMemberPCPtr()->m_desc
						GAMELOG << init("EXPED PARTY RECALL MEMBER", pc)
							<< end;
					}
				}
			}
		}
	}

}

void do_ExpedPartyDungeonRewardReq(CPC* ch, CNetMsg::SP& msg)
{
	if (ch == NULL)
		return;

	int nAmendIndex;
	int nProgressMax;
	int nZone;

	RefMsg(msg) >> nAmendIndex;
	RefMsg(msg) >> nZone;

#ifdef CLOUD_EXPEDITION_REWORK
	int nCount = gserver->m_PartyConfig.GetZoneCount(0);
#endif

	if (nAmendIndex < 0 || nAmendIndex > nCount)
	{
		GAMELOG << init("HACKING INVALID AMEND INDEX", ch)
			<< "AMEND INDEX" << delim << nAmendIndex
			<< end;
		ch->m_desc->Close("hack user is dis invalid amend index.");
		return;
	}

	GAMELOG << init("EXPED PARTY DUNGEON REWARD REQ", ch)
		<< "AMEND INDEX" << delim << nAmendIndex
		<< end;

	if (ch->m_PartyDGTitleRewardData[nAmendIndex] == 0)
		nProgressMax = (int)gserver->m_PartyConfig.GetDungeonDomination0(nZone);
	else if (ch->m_PartyDGTitleRewardData[nAmendIndex] == 1)
		nProgressMax = (int)gserver->m_PartyConfig.GetDungeonDomination1(nZone);

	if (nProgressMax < (int)gserver->m_PartyConfig.GetDungeonDomination1(nZone))
		return;

	if (ch->m_PartyDGCompleteData[nAmendIndex] < nProgressMax)
	{
		GAMELOG << init("ERROR DUNGEON REWARD REQ", ch)
			<< "AMEND INDEX" << delim << nAmendIndex
			<< "REWARD TYPE" << delim << ch->m_PartyDGTitleRewardData[nAmendIndex]
			<< "COMPLETE TIMES" << delim << ch->m_PartyDGCompleteData[nAmendIndex]
			<< "PROGRESS MAX" << delim << nProgressMax
			<< end;
		return;
	}

	if (ch->m_inventory.getEmptyCount() < 1)//12
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysFullInventoryMsg(rmsg, 0);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if (ch->m_PartyDGTitleRewardData[nAmendIndex] == 0 && nProgressMax == (int)gserver->m_PartyConfig.GetDungeonDomination0(nZone))
	{
	
		int nTitleRewardList = (int)gserver->m_PartyConfig.GetDungeonTitle(nZone);
		int reward_nCount = 1;
		CItem* item = gserver->m_itemProtoList.CreateItem(nTitleRewardList, -1, 0, 0, reward_nCount);

		if (!item)
			return;

		if (ch->m_inventory.getEmptyCount() < 1)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysFullInventoryMsg(rmsg, 0);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}

		if (ch->m_inventory.addItem(item) == false)
		{
			GAMELOG << init("ERROR REWARD TITLE INVEN FULL", ch)
				<< end;
			delete item;
			item = NULL;
			return;
		}

		ch->m_PartyDGCompleteData[nAmendIndex] = 0;
		ch->m_PartyDGTitleRewardData[nAmendIndex] = 1;
		UpdatePartyDungeonInfo(ch);
		ch->CalcStatus(true);
		return;
	}
	else if (ch->m_PartyDGTitleRewardData[nAmendIndex] == 1 && nProgressMax == (int)gserver->m_PartyConfig.GetDungeonDomination1(nZone))
	{
			
		int nBoxRewardList = (int)gserver->m_PartyConfig.GetDungeonBox(nZone);
		int reward_nCount = (int)gserver->m_PartyConfig.GetDungeonBoxCount(nZone);
		CItem* item = gserver->m_itemProtoList.CreateItem(nBoxRewardList, -1, 0, 0, reward_nCount);


		if (!item)
			return;

		if (ch->m_inventory.getEmptyCount() < 1)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysFullInventoryMsg(rmsg, 0);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}

		if (ch->m_inventory.addItem(item) == false)
		{
			GAMELOG << init("ERROR REWARD BOX INVEN FULL", ch)
				<< end;
			delete item;
			item = NULL;
			return;
		}

		ch->m_PartyDGCompleteData[nAmendIndex] = 0;
		UpdatePartyDungeonInfo(ch);
		ch->CalcStatus(true);
	}
}
#ifdef CLOUD_EXPEDITION_REWORK
void do_ExpedPartyDungeonDetailReq(CPC* ch, CNetMsg::SP& msg)
{
	if (ch == NULL)
		return;

	int nAmendIndex;

	RefMsg(msg) >> nAmendIndex;

	if (nAmendIndex < 0 || nAmendIndex > 2)
	{
		GAMELOG << init("HACKING INVALID AMEND INDEX", ch)
			<< "AMEND INDEX" << delim << nAmendIndex
			<< end;
		ch->m_desc->Close("hack user is dis invalid amend index.");
		return;
	}

	GAMELOG << init("PARTY DUNGEON UI REQUEST", ch)
		<< end;
	{
		//�κ��丮 ����
		CNetMsg::SP rmsg(new CNetMsg);
		ExpedDungeonDetail_Msg(msg, ch, nAmendIndex);
		SEND_Q(msg, ch->m_desc);
	}
}
#endif
#endif