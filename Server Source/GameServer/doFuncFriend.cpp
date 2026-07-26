#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "Server.h"
#include "CmdMsg.h"
#include "doFunc.h"
#include "../ShareLib/DBCmd.h"
#include "../ShareLib/packetType/ptype_old_do_friend.h"
//#include "Friend.h"

//Ŭ���̾�Ʈ�κ��� �޽��� �޴� �κ�...
void do_Friend(CPC* ch, CNetMsg::SP& msg)
{
	unsigned char subtype;
	msg->MoveFirst();
	RefMsg(msg) >> subtype;

	switch (subtype)
	{
	case MSG_FRIEND_REGIST_REQUEST://ģ�� ��� ��û
		do_FriendRegistRequest(ch, msg);
		break;

	case MSG_FRIEND_REGIST_ALLOW: // ��� ����
		do_FriendRegistAllow(ch, msg);
		break;

	case MSG_FRIEND_REGIST_CANCEL: // ��� ����
		do_FriendRegistRefuse(ch, msg);
		break;

	case MSG_FRIEND_DELETE_MEMBER:
		do_FriendDeleteMember(ch, msg);
		break;
	
	case MSG_FRIEND_SET_CONDITION: //���º���
		do_FriendSetCondition(ch, msg);
		break;

	case MSG_FRIEND_DELETE_BLOCK:
		do_FriendDeleteBlock(ch, msg);
		break;

	default:
		break;
	}
}

//Ŭ����Ʈ�κ��� ģ����� ��û �޽����� ������...
void do_FriendRegistRequest(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::doFriendRegReq *packet = reinterpret_cast<RequestClient::doFriendRegReq*>(msg->m_buf);
	packet->name[MAX_CHAR_NAME_LENGTH] = '\0';

	if( strncmp(ch->m_name, packet->name, ch->m_name.Length()) == 0 || strncmp(ch->m_nick, packet->name, ch->m_nick.Length()) == 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_FRIENDNAME);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	// �̸� �˻�
	int lenname = strlen(packet->name);
	if (lenname < 2 || lenname > MAX_NAME_LENGTH)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_FRIENDNAME);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
	if (strchr(packet->name, '\'') || strchr(packet->name, ' ') /* || strchr(name, '\\') || strchr(name, '\"') || strchr(name, '%') || strchr(name, '_')*/)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_FRIENDNAME);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
	if (findPercentChar(packet->name) != NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_FRIENDNAME);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	CPC* pPc = PCManager::instance()->getPlayerByName(packet->name, true);

	//�ش� ĳ���� �������� �ʴ´ٸ�...
	if (pPc == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_NOT_EXIST);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if( pPc->IsSetPlayerState(PLAYER_STATE_PKMODE) )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_REGIST_REFUSE_PVP);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if( pPc->IsBlockPC(ch->m_index, ch->GetName() ) )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_ALREADY_BLOCK);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	//���� �ʰ��ߴ��� üũ...
	int friendcnt;
	friendcnt = pPc->m_Friend->GetFriendSum();

	if(friendcnt >= FRIEND_MAX_MEMBER)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_FULLMEMBER);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	friendcnt = ch->m_Friend->GetFriendSum();

	if(friendcnt >= FRIEND_MAX_MEMBER)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_FULLMEMBER);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
//��û�ڰ� �̹� ��ϵǾ� �ִ��� üũ..
	CFriendMember* pFriendMem = pPc->m_Friend->FindFriendMember(packet->requesterindex);
	if(pFriendMem != NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_ALREADY_EXIST);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
//�̹� �ٸ� ����� ģ����û�� �亯�� ��ٶ�� ���¶��,,
	if (pPc->m_nRegFriend != 0 && pPc->m_nRegFriend  != ch->m_index)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_WAIT_OTHER);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	pPc->m_nRegFriend = ch->m_index;
	ch->m_nRegFriend = pPc->m_index;

	{
		//�޽��� �״�� ������.
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendRegReqMsg(rmsg, packet->requesterindex, ch->GetName());		
		SEND_Q(rmsg, pPc->m_desc); //��� ���ϴ��ڿ��� ������.
	}
}

//ģ������� ����ߴ�...
void do_FriendRegistAllow(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::doFriendRegAllow *packet = reinterpret_cast<RequestClient::doFriendRegAllow*>(msg->m_buf);

	CPC* pPc;
	pPc= PCManager::instance()->getPlayerByCharIndex(packet->charIndex);

	if (!pPc)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendRegistCancelMsg(rmsg);
		SEND_Q(rmsg, ch->m_desc);
		ch->m_nRegFriend = 0;
		return ;
	}
//������ �ε����� ���� �ʴ´ٸ�..
	if (pPc->m_nRegFriend != ch->m_index || ch->m_nRegFriend != pPc->m_index)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_NOT_MATCH_INDEX);
		SEND_Q(rmsg, ch->m_desc);
		SEND_Q(rmsg, pPc->m_desc);
		ch->m_nRegFriend = 0;
		pPc->m_nRegFriend = 0;
		return ;
	}

	if (gserver->isRunHelper())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		UpdateServer::HelperFriendAddReqMsg(rmsg, ch->m_index, ch->GetName(), ch->m_job, pPc->m_index, pPc->GetName(), pPc->m_job);
		SEND_Q(rmsg, gserver->m_helper);
	}
	else
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_HELPER_SERVER);
		SEND_Q(rmsg, ch->m_desc);
		SEND_Q(rmsg, pPc->m_desc);
		ch->m_nRegFriend = 0;
		pPc->m_nRegFriend = 0;
		return ;
	}
}
//ģ�� ����� �����ߴ�...
void do_FriendRegistRefuse(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::doFriendRegCancel *packet = reinterpret_cast<RequestClient::doFriendRegCancel*>(msg->m_buf);
	
	CPC* pPc;
	pPc= PCManager::instance()->getPlayerByCharIndex(packet->charIndex);

	if(pPc)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendRegistCancelMsg(rmsg);
		SEND_Q(rmsg, pPc->m_desc);

		pPc->m_nRegFriend = 0;
	}

	ch->m_nRegFriend = 0;
}

void do_FriendDeleteMember(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::doFriendDeleteMember *packet = reinterpret_cast<RequestClient::doFriendDeleteMember*>(msg->m_buf);
	packet->name[MAX_CHAR_NAME_LENGTH] = '\0';
	
	//�ڽ��� ������� �߰ų�, ��û�ڰ� �ڽ��� �ƴ϶��...
	if (packet->targetIndex == ch->m_index || packet->requestIndex != ch->m_index)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_PACKET);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if (packet->targetIndex == -1)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_PACKET);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	int lenname = strlen(packet->name);
	if (lenname < 2 || lenname > MAX_CHAR_NAME_LENGTH)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_FRIENDNAME);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
	if (findPercentChar(packet->name) != NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_FRIENDNAME);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		UpdateServer::HelperFriendDelReqMsg(rmsg, ch->m_index, packet->targetIndex, packet->name);
		SEND_Q(rmsg, gserver->m_helper);
	}
}


// ���� �����ϱ�..
void do_FriendSetCondition(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::doFriendSetCondition* packet = reinterpret_cast<RequestClient::doFriendSetCondition*>(msg->m_buf);

	ch->m_nCondition = packet->condition;
//0521
	if(ch->m_Friend)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperFriendSetConditionMsg(rmsg, ch->m_index, packet->condition, -1, ch);
		SEND_Q(rmsg, gserver->m_helper);
	}

	{
		//�ӽ�..������.
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendSetConditionMsg(rmsg, packet->charIndex, packet->condition);
		SEND_Q(rmsg, ch->m_desc);
	}
}

//���� ��� ����
void do_FriendDeleteBlock(CPC* ch, CNetMsg::SP& msg)
{
	RequestClient::doFriendDeleteBlock* packet = reinterpret_cast<RequestClient::doFriendDeleteBlock*>(msg->m_buf);

	map_listblock_t::iterator it = ch->m_listBlockPC.find(packet->charIndex);
	if (it != ch->m_listBlockPC.end())
	{
		{
			CNetMsg::SP rmsg(new CNetMsg);
			UpdateServer::HelperFriendDelReqMsg(rmsg, ch->m_index, it->second->GetIndex(), it->second->GetName());
			SEND_Q(rmsg, gserver->m_helper);
		}
		
		ch->m_listBlockPC.erase(it);

		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendDeleteBlockMsg(rmsg);
		SEND_Q(rmsg, ch->m_desc);
	}
	else
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::FriendErrorMsg(rmsg, MSG_FRIEND_ERROR_NOT_EXIST);
		SEND_Q(rmsg, ch->m_desc);
	}
}