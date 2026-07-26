#include "stdhdrs.h"

#include "Server.h"
#include "doFunc.h"
#include "CmdMsg.h"

void do_Request(CNetMsg::SP& msg, CDescriptor* dest)
{
	msg->MoveFirst();

	int seq;
	int serverno, subno, zone;
	unsigned char subtype;

	RefMsg(msg) >> seq
				>> serverno >> subno >> zone
				>> subtype;

	CMsgListNode* node;
	if (seq == -1)
	{
		node = gserver.m_msgList.Add(-1, false, dest, msg);
	}
	else
	{
		node = gserver.m_msgList.Add(gserver.GetNextSeqNo(), true, dest, msg);
	}

	CDescriptor* pDesc;
	CDescriptor* pNext = gserver.m_desclist;
	while ((pDesc = pNext))
	{
		pNext = pDesc->m_pNext;

		if (STATE(pDesc) != CON_PLAYING)
			continue ;

		// serverno�� -1(���)�̰ų�
		// �ش� ������ �̰�
		// �� ������ �����ϴ� ���̰ų�
		// ��� ���̸� �߰�
		if (((serverno == -1/* && pDesc->m_serverNo != LOGIN_SERVER_NUM && pDesc->m_serverNo != CONNECTOR_SERVER_NUM*/)	// ������, �α��μ��� ������
				|| pDesc->m_serverNo == serverno) && (subno == -1 || pDesc->m_subNo == subno) && (zone == -1 || pDesc->FindZone(zone) != -1))
		{
			// ���ǿ��� �޽��� ����, ó���� �� GameServer�� ���
			SEND_Q(msg, pDesc);

			if (node->m_bReq)
			{
				node->Add(pDesc);
			}
		}
	}

	// ������ �ʿ���� �޽����� ��� �������� �ʰ� �ٷ� ����
	if (node->m_bReq == false)
	{
		gserver.m_msgList.Remove(node);
	}
}

void do_Reply(CNetMsg::SP& msg, CDescriptor* dest)
{
	msg->MoveFirst();

	int seq;
	int serverno, subno;
	int zoneno;
	unsigned char subtype;

	RefMsg(msg) >> seq
				>> serverno
				>> subno
				>> zoneno
				>> subtype;

	// seq�� ã��
	CMsgListNode* node;
	CMsgListNode* nodeNext = gserver.m_msgList.m_head;
	CDescriptor* pServer = NULL;
	while ((node = nodeNext))
	{
		nodeNext = node->m_pNext;

		if (node->m_seq == seq)
		{
			bool bAllReceived = true;
			// ������ ã��
			CMsgListNodeServerNode* snode;
			CMsgListNodeServerNode* snodeNext = node->m_head;
			while ((snode = snodeNext))
			{
				snodeNext = snode->m_pNext;
				if (snode->m_server->m_serverNo == dest->m_serverNo && snode->m_server->m_subNo == dest->m_subNo)
				{
					// ���� ���� �������� ����
					snode->m_recieved = true;
					pServer = snode->m_server;
					continue ;
				}

				// ��� ���� �޾Ҵ��� �˻�
				if (!snode->m_recieved)
					bAllReceived = false;
			}

			// ��û�� ������ ������
			if (!pServer)
				continue ;

			switch (subtype)
			{
			case MSG_HELPER_WHISPER_REP:
				{
					// �����ڰ� �־ ����� �޾Ҵ�
					int sidx, isItem;
					CLCString sname(MAX_CHAR_NAME_LENGTH + 1);
					CLCString rname(MAX_CHAR_NAME_LENGTH + 1);
					CLCString chat(1000);

					RefMsg(msg)	>> sidx >> sname
								>> rname
								>> chat
								>> isItem;

					CNetMsg::SP rmsg(new CNetMsg);
					HelperWhisperRepMsg(rmsg, seq, serverno, subno, zoneno, sidx, sname, rname, chat, isItem);
					SEND_Q(rmsg, node->m_reqServer);

					// ����� �޾����� ����������
					bAllReceived = true;
				}
				break ;

			case MSG_HELPER_WHISPER_NOTFOUND:
				if (bAllReceived)
				{
					// �� �޾Ҵµ� �Ӹ� ����� ������
					int sidx;
					CLCString sname(MAX_CHAR_NAME_LENGTH + 1);

					RefMsg(msg) >> sidx
								>> sname;

					CNetMsg::SP rmsg(new CNetMsg);
					HelperWhisperNotfoundMsg(rmsg, seq, serverno, subno, zoneno, sidx, sname);
					SEND_Q(rmsg, node->m_reqServer);
				}
				break ;
			}

			// �� �޾����� ��忡�� ����
			if (bAllReceived)
			{
				gserver.m_msgList.Remove(node);
			}

			break;
		}
	}
}
//