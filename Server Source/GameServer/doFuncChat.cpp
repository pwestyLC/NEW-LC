#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "Server.h"
#include "CmdMsg.h"
#include "WarCastle.h"
#include "doFunc.h" //disconnect
#include "Descriptor.h" //characterinfolog
bool BuidItemChat(CNetMsg::SP& msg, CNetMsg::SP& fromClient, CPC* ch, int offset, int chatLength);
/////////////////
// ä�� ���� �Լ�
bool ContainsSuspiciousTag(const std::string& text)
{
	static const std::vector<std::string> blockedPatterns = {
		"</>", "< 1>", "<1>", "<>", "<script", "</script", "<gm", "<lord", "<rank"
	};

	for (const auto& pattern : blockedPatterns)
	{
		if (text.find(pattern) != std::string::npos)
			return true;
	}

	// Generic bracket abuse check
	size_t open = text.find('<');
	while (open != std::string::npos)
	{
		size_t close = text.find('>', open);
		if (close == std::string::npos || close - open > 30)
			return true;

		open = text.find('<', close);
	}

	return false;
}

void do_Chat(CPC* ch, CNetMsg::SP& msg)
{
	// ch�� ���� ���� ���� ��, ���϶�
	if (!IS_IN_CELL(ch))
		return ;

	msg->MoveFirst();

	unsigned char chatType, isItem;
	int sender_index;
	CLCString sender_name(MAX_CHAR_NAME_LENGTH + 1);
	CLCString receiver_name(MAX_CHAR_NAME_LENGTH + 1);
	CLCString chat(1000);
	int	nGroupTyp=-1;  	//������ �׷�1(0), �׷� 2(1),  �׷� 3(2), �׷� 4(3) , ��ü(-1)
	int oldLength = 0, offset = 0;

	RefMsg(msg) >> chatType
				>> sender_index
				>> sender_name
				>> receiver_name
				>> chat
				>> nGroupTyp
				>> isItem;

	CLCString tmp(1000);

	oldLength = chat.Length();
	sender_name.Trim();
	receiver_name.Trim();
	chat.Trim();
	if (!isItem && ContainsSuspiciousTag(std::string(chat)))

	{
		GAMELOG << init("CHAT HACK BLOCK", ch)
			<< "Blocked Chat: " << chat
			<< end;

		// Optional: inform the player
		CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_WHISPER_NOTFOUND); // You can define this in your system messages
		SEND_Q(rmsg, ch->m_desc);

		return;
	}

	offset = oldLength - chat.Length();
	oldLength = oldLength + (chatType == MSG_CHAT_SAY ? 0 : 1);	
	
	if (chatType == MSG_CHAT_WHISPER && isItem)
	{
		oldLength += receiver_name.Length();
		offset += receiver_name.Length();
	}

	// ���� ���� ä���� ����
	if (chat.Length() < 1)
		return ;

	if (chat.Length() > CHAT_MESSAGE_MAX)
	{
		LOG_ERROR("chat message is too long. max size is %d", CHAT_MESSAGE_MAX);
		ch->m_desc->Close("chat message is too long.");
		return;
	}

	// ä�� ���� Check
	if (gserver->m_pulse - ch->m_silencePulse <= 0)
		return;

#ifdef NO_CHATTING

	switch (chatType)
	{
	case MSG_CHAT_SAY:		// �Ϲ�
		{
			if (ch->m_nflag & CHAT_FLAG_NO_SAY) return;
			tmp.Format("SAY: %s: %s", ch->GetName(), (const char*)chat);
		}
		break;
	case MSG_CHAT_SHOUT:	// ��ġ��
		{
			if (ch->m_nflag & CHAT_FLAG_NO_SHOUT) return;
			tmp.Format("SHOUT: %s: %s", ch->GetName(), (const char*)chat);
		}
		break;
	case MSG_CHAT_TRADE:	// �Ÿ�
		{
			if (ch->m_nflag & CHAT_FLAG_NO_TRADE) return;
			tmp.Format("TRADE: %s: %s", ch->GetName(), (const char*)chat);
		}
		break;
	case MSG_CHAT_WHISPER:	// �Ӹ�
		{
			if (ch->m_nflag & CHAT_FLAG_NO_WHISPER) return;
			tmp.Format("WHISPER: %s ==> %s: %s", ch->GetName(), (const char*)receiver_name, (const char*)chat);
		}
		break;
	case MSG_CHAT_PARTY:	// ��Ƽ
		{
			if (ch->m_nflag & CHAT_FLAG_NO_PARTY) return;
			tmp.Format("PARTYCHAT: %s: %s", ch->GetName(), (const char*)chat);
		}
		break;
	case MSG_CHAT_EXPEDITION:	// ������
		{
			if (ch->m_nflag & CHAT_FLAG_NO_EXPED) return;
			tmp.Format("EXPEDCHAT: %s: %s", ch->GetName(), (const char*)chat);
		}
		break;
	case MSG_CHAT_GUILD:	// ���
		{
			if (ch->m_nflag & CHAT_FLAG_NO_GUILD) return;
			tmp.Format("GUILDCHAT: %s: %s", ch->GetName(), (const char*)chat);
		}
		break;
	case MSG_CHAT_GM:		// GM �Ϲ�ä��
		{
			tmp.Format("GM SAY: %s: %s", ch->GetName(), (const char*)chat);
		}
		break;
	case MSG_CHAT_LORD:		// ���� ����
		{
			tmp.Format("LORD SAY: %s: %s", ch->GetName(), (const char*)chat);
		}
		break;

	case MSG_CHAT_CHANNEL_LEVEL:
		{
			if( ch->m_level < 50 ) return;		// 50���� ���� ä�� �Ұ�
			tmp.Format("CH_LEVEL SAY: %s: %s", ch->GetName(), (const char*)chat );
		}
		break;
	case MSG_CHAT_CHANNEL_TRADE:
		{
			if( ch->m_level < 10 )				return;		// 10���� ���� ä�� �Ұ�

			LONGLONG needMoney = chat.Length() * 10 ;

			if( ch->m_inventory.getMoney() >= needMoney )
			{
				ch->m_inventory.decreaseMoney(needMoney);
			}
			else
			{
				return;		// ������ �����Ͽ� ä�� �� �� ����
			}
			tmp.Format("CH_TRADE SAY: %s: %s", ch->GetName(), (const char*)chat );
		}
		break;
	default:
		return;
	}

	if (strlen(tmp) > 0 && ch->m_bChatMonitor)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SayMsg(rmsg, MSG_CHAT_NOTICE, 0, "", "", tmp);

		int i;
		for (i = 0; i < 20; i++)
		{
			if (gserver->m_chatmonitor[i])
				SEND_Q(rmsg, gserver->m_chatmonitor[i]);
		}

		tmp.Replace("%", "%%");

		GAMELOG << init("CHAT MONITOR", ch)
				<< tmp
				<< end;
	}

#else

	switch (chatType)
	{
	case MSG_CHAT_SAY:			// �Ϲ�
		tmp.Format("SAY: %s: %s", ch->GetName(), (const char*)chat);
		break;

	case MSG_CHAT_SHOUT:		// ��ġ��
		tmp.Format("SHOUT: %s: %s", ch->GetName(), (const char*)chat);
		break;

	case MSG_CHAT_TRADE:		// �Ÿ�
		tmp.Format("TRADE: %s: %s", ch->GetName(), (const char*)chat);
		break;

	case MSG_CHAT_WHISPER:		// �Ӹ�
		tmp.Format("WHISPER: %s ==> %s: %s", ch->GetName(), (const char*)receiver_name, (const char*)chat);
		break;

	case MSG_CHAT_PARTY:		// ��Ƽ
		tmp.Format("PARTYCHAT: %s: %s", ch->GetName(), (const char*)chat);
		break;
	case MSG_CHAT_EXPEDITION:	// ������
		tmp.Format("EXPEDCHAT: %s: %s", ch->GetName(), (const char*)chat);
		break;
	case MSG_CHAT_GUILD:		// ���
		tmp.Format("GUILDCHAT: %s: %s", ch->GetName(), (const char*)chat);
		break;

	case MSG_CHAT_GM:			// GM �Ϲ�ä��
		tmp.Format("GM SAY: %s: %s", ch->GetName(), (const char*)chat);
		break;

	case MSG_CHAT_LORD:			// ���� ����
		tmp.Format("LORD SAY: %s: %s", ch->GetName(), (const char*)chat);
		break;
	case MSG_CHAT_CHANNEL_LEVEL:
		{
			if( ch->m_level < 50 ) return;		// 50���� ���� ä�� �Ұ�
			tmp.Format("CH_LEVEL SAY: %s: %s", ch->GetName(), (const char*)chat );
		}
		break;
	case MSG_CHAT_CHANNEL_TRADE:
		{
			if( ch->m_level < 10 )				return;		// 10���� ���� ä�� �Ұ�

			LONGLONG needMoney = chat.Length() * 10 ;

			if( ch->m_inventory.getMoney() >= needMoney )
			{
				ch->m_inventory.decreaseMoney(needMoney);
			}
			else
			{
				return;		// ������ �����Ͽ� ä�� �� �� ����
			}
			tmp.Format("CH_TRADE SAY: %s: %s", ch->GetName(), (const char*)chat );
		}
		break;
	default:
		return ;
	}

	if (ch->m_bChatMonitor)
	{
		if (strlen(tmp) > 0)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SayMsg(rmsg, MSG_CHAT_NOTICE, 0, "", "", tmp);

			int i;
			for (i = 0; i < 20; i++)
			{
				if (gserver->m_chatmonitor[i])
					SEND_Q(rmsg, gserver->m_chatmonitor[i]);
			}

#ifndef LC_GAMIGO
			tmp.Replace("%", "%%");

			GAMELOG << init("CHAT MONITOR", ch)
					<< tmp
					<< end;
#endif
		}
	}
#endif // NO_CHATTING

#ifdef GMTOOL
	if(strlen(tmp) > 0 && ch->m_bGmMonitor)
	{
		switch (chatType)
		{
		case MSG_CHAT_SAY:			// �Ϲ�
		case MSG_CHAT_SHOUT:		// ��ġ��
		case MSG_CHAT_TRADE:		// �Ÿ�
		case MSG_CHAT_WHISPER:		// �Ӹ�
		case MSG_CHAT_GM:			// GM �Ϲ�ä��
		case MSG_CHAT_LORD:			// ���� ����
		case MSG_CHAT_GMTOOL:
			{
				CNetMsg::SP rmsg(new CNetMsg);
				MsgrNoticeGmChatMonitorMsg(rmsg, -1, 1, 1, 0, gserver->m_serverno, gserver->m_subno, -1, tmp, ch->m_index, ch->m_name, chatType);
				SEND_Q(rmsg, gserver->m_messenger);
			}
			break;
		case MSG_CHAT_PARTY:
		case MSG_CHAT_EXPEDITION:
		case MSG_CHAT_GUILD:
			break;
		default:
			return;
		}
	}
#endif // GMTOOL

	CDratanCastle  * pCastle = CDratanCastle::CreateInstance();

	switch (chatType)
	{
	case MSG_CHAT_SAY:			// �Ϲ�
		if (gserver->m_pulse - ch->m_sayPulse <= 0)
			return;

		ch->m_sayPulse = gserver->m_pulse + (3 * PULSE_REAL_SEC);  //pwesty chat limit 

		if (ch->IsInvisible())
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_CANTCHAT_INVISIBLE);
			SEND_Q(rmsg, ch->m_desc);
		}
		
#ifdef RANKER_NOTICE
		else if( ch->m_bRanker )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SayMsg(rmsg, MSG_CHAT_RANKER, ch->m_index, ch->GetName(), "", chat);
			ch->m_pArea->SendToCell(rmsg, GET_YLAYER(ch), ch->m_cellX, ch->m_cellZ);
		}	
#endif
		else
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SayMsg(rmsg, MSG_CHAT_SAY, ch->m_index, ch->GetName(), "", chat);
			if (isItem)
			{
				if (!BuidItemChat(rmsg, msg, ch, offset, oldLength))
				{
					SayMsg(rmsg, MSG_CHAT_SAY, ch->m_index, ch->GetName(), "", chat);
					RefMsg(rmsg) << (int)0;
				}
			}
			else
			{
				RefMsg(rmsg) << (int)0;
			}
			ch->m_pArea->SendToCell(rmsg, GET_YLAYER(ch), ch->m_cellX, ch->m_cellZ);
		}
		break;

	case MSG_CHAT_SHOUT:		// ��ġ��
	case MSG_CHAT_TRADE:		// �Ÿ�
		{
#ifdef CHAT_BLOCK_USA
			if (gserver->m_pulse - ch->m_shoutPulse <= 0)
				return;

			if (ch->m_level < CHAT_BLOCK_USA_LEVEL)
				return;

			ch->m_shoutPulse = gserver->m_pulse + (CHAT_BLOCK_USA_NEXT_TIME * PULSE_REAL_SEC);
#endif
			{
				CNetMsg::SP rmsg(new CNetMsg);
				SayMsg(rmsg, (MSG_CHAT_TYPE)chatType, ch->m_index, ch->GetName(), "", chat);
				if (isItem)
				{
					if (!BuidItemChat(rmsg, msg, ch, offset, oldLength))
					{
						SayMsg(rmsg, (MSG_CHAT_TYPE)chatType, ch->m_index, ch->GetName(), "", chat);
						RefMsg(rmsg) << (int)0;
					}
				}
				else
				{
					RefMsg(rmsg) << (int)0;
				}
				ch->m_pArea->SendToCell(rmsg, GET_YLAYER(ch), ch->m_cellX, ch->m_cellZ, CELL_EXT * 2);
			}
		}
		break;

	case MSG_CHAT_WHISPER:		// �Ӹ�
		{
			CNetMsg::SP rmsg(new CNetMsg);
			MsgrWhisperReqMsg(rmsg,
							0,
							gserver->m_serverno,
							gserver->m_subno,
							ch->m_index,
							ch->GetName(),
							receiver_name,
							chat);

			if (isItem)
			{
				if (!BuidItemChat(rmsg, msg, ch, offset, oldLength))
				{
					MsgrWhisperReqMsg(rmsg,
							0,
							gserver->m_serverno,
							gserver->m_subno,
							ch->m_index,
							ch->GetName(),
							receiver_name,
							chat);
					RefMsg(rmsg) << (int)0;
				}
			}
			else
			{
				RefMsg(rmsg) << (int)0;
			}
			SEND_Q(rmsg, gserver->m_messenger);
		}
		break;

	case MSG_CHAT_MESSENGER:		// �޽���.
		{
			CNetMsg::SP rmsg(new CNetMsg);
			MsgrFriendChatReqMsg(rmsg,
								 0,
								 gserver->m_serverno,
								 -1,
								 ch->m_index,
								 ch->GetName(),
								 receiver_name,
								 chat);
			SEND_Q(rmsg, gserver->m_messenger);
		}
		break;

	case MSG_CHAT_PARTY:		// ��Ƽ
		{
			if (ch->IsParty())
			{
				if (gserver->m_pulse - ch->m_partyPulse <= 0)
					return;

				ch->m_partyPulse = gserver->m_pulse + (3 * PULSE_REAL_SEC);

				CNetMsg::SP rmsg(new CNetMsg);
				HelperPartyChatMsg(rmsg, ch->m_party->GetBossIndex(), ch->m_index, ch->GetName(), chat);
				if (isItem)
				{
					if (!BuidItemChat(rmsg, msg, ch, offset, oldLength))
					{
						HelperPartyChatMsg(rmsg, ch->m_party->GetBossIndex(), ch->m_index, ch->GetName(), chat);
						RefMsg(rmsg) << (int)0;
					}
				}
				else
				{
					RefMsg(rmsg) << (int)0;
				}
				SEND_Q(rmsg, gserver->m_helper);
			}
		}
		break;

	case MSG_CHAT_EXPEDITION:		// ������
		{
			if (ch->IsExped())
			{
				if (gserver->m_pulse - ch->m_expiditionPulse <= 0)
					return;

				ch->m_expiditionPulse = gserver->m_pulse + (3 * PULSE_REAL_SEC);

				CNetMsg::SP rmsg(new CNetMsg);
				SayMsg(rmsg, MSG_CHAT_EXPEDITION, ch->m_index, ch->GetName(), "", chat, nGroupTyp);

				if(nGroupTyp == -1)	 //��ü
				{
					ch->m_Exped->SendToAllPC(rmsg,-1);
				}
				else				  //�׷�
				{
					ch->m_Exped->SendToPCInSameGroup(nGroupTyp,rmsg);
				}
			}
		}
		break;

	case MSG_CHAT_GUILD:		// ���
		{
			if (ch->m_guildInfo)
			{
				if (gserver->m_pulse - ch->m_guildPulse <= 0)
					return;

				ch->m_guildPulse = gserver->m_pulse + (3 * PULSE_REAL_SEC);

				CNetMsg::SP rmsg(new CNetMsg);
				HelperGuildChat(rmsg,
								ch->m_guildInfo->guild()->index(),
								ch->m_index,
								ch->GetName(),
								chat);

				if (isItem)
				{
					if (!BuidItemChat(rmsg, msg, ch, offset, oldLength))
					{
						HelperGuildChat(rmsg, ch->m_guildInfo->guild()->index(), ch->m_index, ch->GetName(), chat);
						RefMsg(rmsg) << (int)0;
					}
				}
				else
				{
					RefMsg(rmsg) << (int)0;
				}
				SEND_Q(rmsg, gserver->m_helper);
			}
		}
		break;

	case MSG_CHAT_GM:			// GM �Ϲ� ä��
		{
			if ( !IS_PC(ch) ) return; //dethunter12
			if( ch->m_admin < 10 )
			{
				
	GAMELOG << init("GM Chat Hack",ch)
		<< tmp
		<< end;
	ch->m_desc->Close("GM Chat Hack");
				return; //dethunter12
			}
			CNetMsg::SP rmsg(new CNetMsg);
			SayMsg(rmsg, (MSG_CHAT_TYPE)chatType, ch->m_index, ch->GetName(), "", chat);
			ch->m_pArea->SendToCell(rmsg, GET_YLAYER(ch), ch->m_cellX, ch->m_cellZ);
		}
		break;

	case MSG_CHAT_LORD:			// ���� ����
		if ( !IS_PC(ch) ) return; //dethunter12
		if (CWarCastle::CanLordChat(ch))
		{
			if (gserver->m_pulse - ch->m_lordPulse <= 0)
				return;

			ch->m_lordPulse = gserver->m_pulse + (2 * PULSE_REAL_SEC);

			CNetMsg::SP rmsg(new CNetMsg);
			MsgrChatLordMsg(rmsg,
							ch->m_index,
							ch->GetName(),
							chat);
			if (isItem)
			{
				if (!BuidItemChat(rmsg, msg, ch, offset, oldLength))
				{
					MsgrChatLordMsg(rmsg, ch->m_index, ch->GetName(), chat);
					RefMsg(rmsg) << (int)0;
				}
			}
			else
			{
				RefMsg(rmsg) << (int)0;
			}

			SEND_Q(rmsg, gserver->m_messenger);
		}

		if(pCastle->CanLordChat(ch) == true)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			MsgrChatLordMsg(rmsg,
							ch->m_index,
							ch->GetName(),
							chat);

			chat.Replace("%", "%%");

			GAMELOG << init("CHATLOAD CHATMSG SEND TO MESSENGER:",ch)
					<< " chat"  << delim <<  chat
					<< end;

			SEND_Q(rmsg, gserver->m_messenger);
		}
		break;

#ifdef GMTOOL
	case MSG_CHAT_GM_WHISPER:	// ������ ���� �Ӹ�
		{
			if( ch->m_admin < 10 )	return; //dethunter12
			if ( !IS_PC(ch) ) return; //dethunter12
			int server, sub;
			RefMsg(msg) >> server
						>> sub;

			CNetMsg::SP rmsg(new CNetMsg);
			MsgrGMWhisperReqMsg(rmsg,
								0,
								server,
								sub,
								ch->m_index,
								ch->GetName(),
								receiver_name,
								chat);
			SEND_Q(rmsg, gserver->m_messenger);
		}
		break;
	case MSG_CHAT_GMTOOL:		// ������ �������� ���� �Ӹ�
		{
			if ( !IS_PC(ch) ) return; //dethunter12
			if( ch->m_admin < 10 )	return; //dethunter12
			CNetMsg::SP rmsg(new CNetMsg);
			MsgrGMWhisperReqMsg(rmsg, 0, 1, 1, chat, ch->m_index, ch->m_name, gserver->m_serverno, gserver->m_subno, receiver_name);
			SEND_Q(rmsg, gserver->m_messenger);
		}
		break;
#endif // GMTOOL

	case MSG_CHAT_CHANNEL_LEVEL:
	case MSG_CHAT_CHANNEL_TRADE:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			MsgrChannelChatReqMsg( rmsg, gserver->m_serverno, ch->m_index,  ch->GetName(), (const char*) chat, chatType );
			if (isItem)
			{
				if (!BuidItemChat(rmsg, msg, ch, offset, oldLength))
				{
					MsgrChannelChatReqMsg(rmsg, gserver->m_serverno, ch->m_index, ch->GetName(), (const char*)chat, chatType);
					RefMsg(rmsg) << (int)0;
				}
			}
			else
			{
				RefMsg(rmsg) << (int)0;
			}
			SEND_Q(rmsg, gserver->m_messenger);
		}
		break;

	default:
		return ;
	}
}
bool BuidItemChat(CNetMsg::SP& msg, CNetMsg::SP& fromClient, CPC* ch, int offset, int chatLength)
{
	int count = 0;
	RefMsg(fromClient) >> count;
	if (count <= 0 || count > 5)
	{
		LOG_ERROR("HACKING? : Incorrect count value char_id[%d] count[%d]", ch->m_index, count);
		ch->m_desc->Close("Incorrect count value");
		return false;
	}

	RefMsg(msg) << (int)1
		<< (int)count;
	for (int i = 0; i < count; i++)
	{
		unsigned short tab = 0;
		unsigned short invenIndex = 0;
		int itemindex = -1;
		int itemdbindex = -1;
		int startPos = 0;
		int endPos = 0;
		RefMsg(fromClient) >> tab
			>> invenIndex
			>> itemindex
			>> itemdbindex
			>> startPos
			>> endPos;

		if (startPos < 0 || startPos > chatLength || endPos < 0 || endPos > chatLength
			|| startPos >= endPos || ABS(endPos - startPos) > 50)
		{
			LOG_ERROR("HACKING? : Incorrect offset value char_id[%d]. startPos[%d],endPos[%d]", ch->m_index, startPos, endPos);
			ch->m_desc->Close("Incorrect offset value");
			return false;
		}
		if (itemdbindex == NAS_ITEM_DB_INDEX)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_MONEY);
			SEND_Q(rmsg, ch->m_desc);
			return false;
		}
		if (ch->m_inventory.isValidNormalInventory(tab, invenIndex) == false)
		{
			LOG_ERROR("HACKING? : invalid packet. char_index[%d] tab[%d] invenIndex[%d]",
				ch->m_index, tab, invenIndex);
			ch->m_desc->Close("invalid packet");
			return false;
		}
		if (ch->m_inventory.isUsable(tab) == false)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			PersonalShopErrorMsg(rmsg, MSG_PERSONALSHOP_ERROR_INSUFF_ETC);
			SEND_Q(rmsg, ch->m_desc);
			return false;
		}
		CItem* item = ch->m_inventory.getItem(tab, invenIndex);
		if (item == NULL)
		{
			LOG_ERROR("HACKING? : not found item. char_index[%d] tab[%d] invenIndex[%d]",
				ch->m_index, tab, invenIndex);
			ch->m_desc->Close("not found item");
			return false;
		}
		RefMsg(msg) << (int)item->getVIndex()
			<< (int)item->getDBIndex()
			<< item->getWearPos()
			<< (int)item->getPlus()
			<< (int)item->m_itemProto->getItemFlag()
			<< (int)item->getFlag()
			<< (int)item->getUsed()
			<< (int)item->getUsed_2()
			<< (int)item->getNowDurability()
			<< (int)item->getMaxDurability()
			<< (int)startPos - offset
			<< (int)endPos - offset;
		ItemPublicMsg(msg, item);
		ItemSocketMsg(msg, item);
	}
	return true;
}
