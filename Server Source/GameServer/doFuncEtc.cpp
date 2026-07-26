#include "stdhdrs.h"
#include <boost/foreach.hpp>

#include "Log.h"
#include "Cmd.h"
#include "Character.h"
#include "Server.h"
#include "CmdMsg.h"
#include "doFunc.h"
#include "DratanCastle.h"
#include "InventoryManager.h"
#include "Notice.h"
#include "../ShareLib/packetType/ptype_old_do_item.h"
#include "../ShareLib/packetType/ptype_old_extend.h"
#include "../ShareLib/packetType/ptype_old_do_move.h"
#include "../ShareLib/packetType/ptype_old_do_sskill.h"
#include "../ShareLib/packetType/ptype_attendance.h"
#include "../ShareLib/packetType/ptype_notice.h"
#include "../ShareLib/packetType/ptype_server_to_server.h"

#include "GuildBattleManager.h"

#ifdef QUICK_PANEL
#include "DBManager.h"
#include "../ShareLib/packetType/ptype_old_do_skill.h"
#endif

extern CCmdList gexcmdlist;

void do_StatPoint(CPC* ch, CNetMsg::SP& msg)
{
	unsigned char subtype = (unsigned char)-1;
	msg->MoveFirst();
	RefMsg(msg) >> subtype;

	switch (subtype)
	{
	case MSG_STATPOINT_USE:
		do_StatPointUse(ch, msg);
		break;

	case MSG_STATPOINT_RESET:
		do_StatPointReset(ch, msg);
		break;
	}
}

void do_StatPointUse(CPC* ch, CNetMsg::SP& msg)
{
	unsigned char type;

	RefMsg(msg) >> type;

	// ���� ����Ʈ �ֳ� ����
	if (ch->m_statpt_remain < 1)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		StatPointErrorMsg(rmsg, MSG_STATPOINT_ERROR_NOTENOUGH);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	int val;
	if (ch->UseStatPoint((MSG_STATPOINT_USE_TYPE)type, &val))
	{
		GAMELOG << init("STATPOINT USE", ch)
				<< "TYPE" << delim
				<< type << end;

		CNetMsg::SP rmsg(new CNetMsg);
		StatPointUseMsg(rmsg, ch, (MSG_STATPOINT_USE_TYPE)type, val);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	else
	{
		CNetMsg::SP rmsg(new CNetMsg);
		StatPointErrorMsg(rmsg, MSG_STATPOINT_ERROR_CANTUSE);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
}

void do_StatPointReset(CPC* ch, CNetMsg::SP& msg)
{
#ifndef LC_KOR
	if (ch->m_job2 == 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		StatPointErrorMsg(rmsg, MSG_STATPOINT_ERROR_WRONGPACKET);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
#endif

	int reset_str = 0;
	int reset_dex = 0;
	int reset_int = 0;
	int reset_con = 0;
	int reset_all = 0;

#ifdef NPC_CHECK
	int npcIndex;
	CNPC *npc;
	RefMsg(msg) >> npcIndex
				>> reset_str
				>> reset_dex
				>> reset_int
				>> reset_con;
	npc = ch->m_pArea->FindProtoNPCInCell(ch, npcIndex, false, 2);
	if(!npc)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		StatPointErrorMsg(rmsg, MSG_STATPOINT_ERROR_NOT_EXIST_NPC);
		SEND_Q(rmsg, ch->m_desc);
		GAMELOG << init("STATPOINT RESET FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
	if( !npc->IsFlag(NPC_RESETSTAT) )
	{
		GAMELOG << init("STATPOINT RESET FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
#else
	RefMsg(msg) >> reset_str
				>> reset_dex
				>> reset_int
				>> reset_con;
#endif
	if (reset_str < 0 || reset_dex < 0 || reset_int < 0 || reset_con < 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		StatPointErrorMsg(rmsg, MSG_STATPOINT_ERROR_WRONGPACKET);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	if (reset_str > ch->m_statpt_str || reset_dex > ch->m_statpt_dex || reset_int > ch->m_statpt_int || reset_con > ch->m_statpt_con)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		StatPointErrorMsg(rmsg, MSG_STATPOINT_ERROR_WRONGPACKET);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	reset_all = reset_str + reset_dex + reset_int + reset_con;

	if (reset_all < 1)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		StatPointErrorMsg(rmsg, MSG_STATPOINT_ERROR_WRONGPACKET);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
	LONGLONG needmoney = 20000;		// 1 ����Ʈ�� �ʿ� ����
	needmoney *= reset_all;

	if (ch->m_inventory.getMoney() < needmoney)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		StatPointErrorMsg(rmsg, MSG_STATPOINT_ERROR_NOMONEY);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
	else
	{
		ch->m_inventory.decreaseMoney(needmoney);
	}

	GAMELOG << init("STATPOINT RESET", ch)
			<< "MONEY" << delim
			<< needmoney << delim
			<< "RESET POINT" << delim
			<< reset_str << delim
			<< reset_dex << delim
			<< reset_int << delim
			<< reset_con << delim;

	ch->m_statpt_str -= reset_str;
	ch->m_statpt_dex -= reset_dex;
	ch->m_statpt_int -= reset_int;
	ch->m_statpt_con -= reset_con;
	ch->m_statpt_remain += reset_all;

	GAMELOG << "RESULT" << delim
			<< ch->m_statpt_str << delim
			<< ch->m_statpt_dex << delim
			<< ch->m_statpt_int << delim
			<< ch->m_statpt_con << end;

	ch->InitStat();

	{
		CNetMsg::SP rmsg(new CNetMsg);
		StatPointRemainMsg(rmsg, ch);
		SEND_Q(rmsg, ch->m_desc);
	}

#ifdef NPC_CHECK
	{
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_STATPOINT);
		RefMsg(rmsg) << (unsigned char)MSG_STATPOINT_RESET
					 << reset_str
					 << reset_dex
					 << reset_int
					 << reset_con;
		SEND_Q(rmsg, ch->m_desc);
	}
#else
	SEND_Q(msg, ch->m_desc);
#endif
	ch->CalcStatus(true);
}

void do_Pulse(CPC* ch, CNetMsg::SP& msg)
{
	int pulse;
	unsigned char nation;

	msg->MoveFirst();

	RefMsg(msg) >> pulse
				>> nation;

#ifdef DISCONNECT_HACK_CHARACTER  // �� ���α׷� ���� ����

	float tickDelayTime;
	// �����̰� 0.06 �ʰ��̸� �� ������ ó��
	RefMsg(msg) >> tickDelayTime;

	if ( tickDelayTime > HACK_LIMIT )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperDisconnectHackCharacter(rmsg, ch->m_desc->m_index, (const char*)ch->m_desc->m_idname, ch->m_index, (const char*)ch->m_name, HACK_TYPE_PULSE, tickDelayTime);
		SEND_Q(rmsg, gserver->m_helper);
	}

#endif // DISCONNECT_HACK_CHARACTER

#if defined (INTERGRATION_SERVER)
	if ( !gserver->m_intergrationInfo.Check(nation) )
#else
	if( nation != gserver->m_national )
#endif
	{
		LOG_ERROR("invalid nation. nation is %d. gserver->m_national is %d", nation, gserver->m_national);
		ch->m_desc->Close("invalid nation");
		return;
	}
	ch->m_desc->CheckHackPulse(pulse);
}

#ifdef DISCONNECT_HACK_CHARACTER  // �� ���α׷� ���� ����
void do_Disconnect_Hack_Character(CPC* ch, CNetMsg::SP& msg)
{
	float delay;

	//msg->MoveFirst();

	RefMsg(msg) >> delay;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HelperDisconnectHackCharacter(rmsg, ch->m_desc->m_index, (const char*)ch->m_desc->m_idname, ch->m_index, (const char*)ch->m_name, HACK_TYPE_CLIENT, delay);
		SEND_Q(rmsg, gserver->m_helper);
	}

	GAMELOG << init("HACK_USER_DISCONNECT", ch)
			<< "Name" << delim
			<< ch->m_name << delim
			<< HACK_TYPE_CLIENT << delim
			<< delay << end;

	// �ش� ĳ���� DIS
	LOG_ERROR("hack user is dis.");
	ch->m_desc->Close("hack user is dis.");
	return;
}
#endif // DISCONNECT_HACK_CHARACTER

void do_Change(CPC* ch, CNetMsg::SP& msg)
{
	unsigned char subtype;

	msg->MoveFirst();

	RefMsg(msg) >> subtype;

	if (subtype != MSG_CHANGE_CANCEL)
		return;

	if (ch->IsSetPlayerState(PLAYER_STATE_CHANGE) && ch->m_changeIndex != -1)
		ch->CancelChange();
}

void do_UI(CPC* ch, CNetMsg::SP& msg)
{
	unsigned char subtype;
	char plusEffect;

	msg->MoveFirst();

	RefMsg(msg) >> subtype
				>> plusEffect;

	if (subtype != MSG_UI_PLUS_EFFECT_REQ)
		return;

	ch->m_plusEffect = plusEffect;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		UIPlusEffectRep(rmsg, ch);
		ch->m_pArea->SendToCell(rmsg, ch, true);
	}
}

void do_Extend(CPC* ch, CNetMsg::SP& msg)
{
	msg->MoveFirst();

	int debug_type = msg->m_mtype;
	int subtype;
	unsigned char thirdtype = 0;

	RefMsg(msg) >> subtype;

	if (gexcmdlist.Find(subtype) == false)
	{
		// ����Ʈ ��Ʈ������ ����ü�� ����� ��Ŷ�� ó���ϱ� ����
		pTypeThirdBase* pThird = reinterpret_cast<pTypeThirdBase*>(msg->m_buf);
		subtype = pThird->subType;
		thirdtype = pThird->thirdType;

		if (gexcmdlist.Find(subtype) == false)
		{
			LOG_ERROR("HACKING : invalid extend command[%d]. charIndex[%d]", subtype, ch->m_index);
			ch->m_desc->Close("Invalid extend command");
			return;
		}
	}
	else
	{
		RefMsg(msg) >> thirdtype;

		msg->MoveFirst();
		RefMsg(msg) >> subtype;
	}

	//LOG_INFO("DEBUG_FUNC : START : type : %d : subtype : %d : thirdType : %d", debug_type, subtype, thirdtype);
	gexcmdlist.Run(subtype, ch, msg);
	//LOG_INFO("DEBUG_FUNC : END : type : %d : subtype : %d : thirdType : %d", debug_type, subtype, thirdtype);
}

void do_ExPromoKey(CPC* ch, CNetMsg::SP& msg)
{
	unsigned char subType;
	RefMsg(msg) >> subType;

	switch(subType)
	{
	case MSG_EX_PROMO_KEY_USE_REQ:
		{
			CLCString key(256);
			RefMsg(msg) >> key;

			gserver->m_promoKeyManager.UsePromoKey(ch, key);
		}
		break;
	}
}

void do_Ex_NameChange(CPC* ch, CNetMsg::SP& msg)
{
	// TODO : BS : ���� ĳ������ ���̰� �޶��� ��� ������ �ʿ�
	// �̸� ���� ������	: tab_idx(uc) row_idx(uc) col_idx(uc) item_idx(n) name(str)

	//msg->MoveFirst();

	int itemindex;
	CLCString name(MAX_CHAR_NAME_LENGTH + 1);

	RefMsg(msg) >> itemindex
				>> name;
	int r, c;

	const CItemProto * itemProto = gserver->m_itemProtoList.FindIndex(itemindex);

	if (itemProto == NULL)
		return;

	int maxLength = itemProto->getItemNum0() > 0 ? itemProto->getItemNum0() : MAX_NAME_LENGTH;

	LOG_INFO("Length name %d", maxLength);

	// �̸��� 0 ���� ������ �ȵȴ�.
	if (strlen(name) < 4 || strlen(name) > maxLength)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		FailMsg(rmsg, MSG_FAIL_WRONG_CHAR);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	// �̸��� ' �� ��� ������ �ȵȴ�.
	if (strinc(name, "'") || strinc(name, " "))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		FailMsg(rmsg, MSG_FAIL_WRONG_CHAR);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if(findPercentChar(name.GetBuffer()) != NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		FailMsg(rmsg, MSG_FAIL_WRONG_CHAR);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if( ch && ( ch->IsParty() || ch->IsExped() ) )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		NameChangeRepMsg(rmsg, MSG_EX_NAMECHANGE_ERROR_PARTY, name, 0);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	switch(itemindex)
	{
	// �ɸ� �̸� ����
	case 842:
	case 1120:
	case PREMIUM_NAME_CHANGE_ITEM:
		{
			if (ch->m_inventory.FindByDBIndex(842, 0, 0) || 
				ch->m_inventory.FindByDBIndex(1120, 0, 0) ||
				ch->m_inventory.FindByDBIndex(PREMIUM_NAME_CHANGE_ITEM, 0, 0))
			{
				if(gserver->isRunHelper())
				{
					CNetMsg::SP rmsg(new CNetMsg);
					HelperNameChangeReqMsg(rmsg, 0, ch->m_index, name, itemindex);
					SEND_Q(rmsg, gserver->m_helper);
				}
				else
				{
					// �̸��� �������� ���ؿ�
					CNetMsg::SP rmsg(new CNetMsg);
					NameChangeRepMsg(rmsg, MSG_EX_NAMECHANGE_ERROR_HELPER, name, 0);
					SEND_Q(rmsg, ch->m_desc);
				}
			}
		}
		break;
	// ��� �̸� ����
	case 843:
	case PREMIUM_GUILD_NAME_CHANGE_ITEM:
		{
			if (ch->m_inventory.FindByDBIndex(843, 0, 0) == NULL &&
				ch->m_inventory.FindByDBIndex(PREMIUM_GUILD_NAME_CHANGE_ITEM, 0, 0) == NULL)
			{
				return;
			}
			if(ch->m_guildInfo == NULL || ch->m_guildInfo->guild() == NULL)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				NameChangeRepMsg(rmsg, MSG_EX_NAMECHANGE_ERROR_NOTGUILDBOSS, name, 1);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}
			if( ch->m_index != ch->m_guildInfo->guild()->boss()->charindex() )
			{
				CNetMsg::SP rmsg(new CNetMsg);
				NameChangeRepMsg(rmsg, MSG_EX_NAMECHANGE_ERROR_NOTGUILDBOSS, name, 1);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}

			if(gserver->isRunHelper())
			{
				CNetMsg::SP rmsg(new CNetMsg);
				HelperNameChangeReqMsg(rmsg, 1, ch->m_guildInfo->guild()->index(), name, itemindex);
				SEND_Q(rmsg, gserver->m_helper);
			}
			else
			{
				// �̸��� �������� ���ؿ�
				CNetMsg::SP rmsg(new CNetMsg);
				NameChangeRepMsg(rmsg, MSG_EX_NAMECHANGE_ERROR_HELPER, name, 1);
				SEND_Q(rmsg, ch->m_desc);
			}
		}
		break;
	}
}

void do_ExPartyRecall(CPC* ch, CNetMsg::SP& msg)
{
	int subtype;
	RefMsg(msg) >> subtype;

	switch (subtype)
	{
	case MSG_EX_PARTY_RECALL_CONFIRM:
		{
			int reqcharindex = 0;
			char yesno = 0;
			CLCString reqcharname(MAX_CHAR_NAME_LENGTH + 1);
			RefMsg(msg) >> reqcharindex
						>> reqcharname
						>> yesno;

			if (!ch->IsParty())
			{
				CNetMsg::SP rmsg(new CNetMsg);
				HelperPartyRecallConfirmFail(rmsg);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}

			if (ch->m_index == reqcharindex)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				HelperPartyRecallConfirmFail(rmsg);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}

			if (ch->m_pZone->IsPersonalDungeon() || ch->m_pZone->IsGuildRoom())
			{
				//�̵��� ���ϴ� ��� ���� ����Ʈ���� ���Ÿ� ���ش�.
				ch->m_party->deletePartyRecallMember(ch->m_index);
				
				CNetMsg::SP rmsg(new CNetMsg);
				HelperPartyRecallConfirmFail(rmsg);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}

			if (ch->m_party->FindMember(reqcharindex) == -1)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				HelperPartyRecallConfirmFail(rmsg);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}

			if(ch->m_nJoinInzone_ZoneNo >= 0 && ch->m_nJoinInzone_RoomNo >= 0)
			{
				//�̵��� ���ϴ� ��� ���� ����Ʈ���� ���Ÿ� ���ش�.
				ch->m_party->deletePartyRecallMember(ch->m_index);

				CNetMsg::SP rmsg(new CNetMsg);
				HelperPartyRecallConfirmFail(rmsg);
				SEND_Q(rmsg, ch->m_desc);
				return ;
			}

			if (ch->m_bHasFlagItem)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				HelperPartyRecallConfirmFail(rmsg);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}

			{
				CNetMsg::SP rmsg(new CNetMsg);
				HelperPartyRecallConfirmMsg(rmsg, ch->m_party->GetBossIndex(), reqcharindex, reqcharname, ch->m_index, ch->GetName(), yesno);
				SEND_Q(rmsg, gserver->m_helper);
			}

			if(!yesno)
			{
				// �ź�
				CNetMsg::SP rmsg(new CNetMsg);
				ExPartyRecallCancelMsg(rmsg, reqcharindex, reqcharname, ch->m_index, ch->GetName());
				SEND_Q(rmsg, ch->m_desc);
			}
		}
		break;

	default:
		break;
	}
}

void do_ExMessenger(CPC* ch, CNetMsg::SP& msg)
{
	char subtype;

	RefMsg(msg) >> subtype;

	switch(subtype)
	{
	case MSG_EX_MESSENGER_ONE_VS_ONE:	// 1:1��ȭ : sCharIndex(n) tCharIndex(x) chat(str)
		{
			int sCharIndex, tCharIndex;
			CLCString chat(1000);

			RefMsg(msg) >> sCharIndex
						>> tCharIndex
						>> chat;

			// ģ�� �¶��� ���� Ȯ��
			CFriendMember * pMember = ch->m_Friend->FindFriendMember(tCharIndex);
			if( pMember == NULL ||
					pMember->GetCondition() == MSG_FRIEND_CONDITION_OFFLINE )
			{
				LOG_INFO("HACKING? invalid offline state : charIndex[%d]", ch->m_index);
				ch->m_desc->Close("invalid offline state");
				return;
			}
			else if(ch->m_nCondition == MSG_FRIEND_CONDITION_OFFLINE)
			{
				LOG_INFO("HACKING? invalid offline state : charIndex[%d]", ch->m_index);
				ch->m_desc->Close("invalid offline state");
				return;
			}
			else
			{
				{
					CNetMsg::SP rmsg(new CNetMsg);
					MsgrMessengerChatMsg(rmsg, MSG_MSGR_MESSENGER_ONE_VS_ONE, sCharIndex, tCharIndex,
										 ch->m_Friend->GetChatColor(), ch->GetName(), chat );
					SEND_Q(rmsg, gserver->m_messenger);
				}

				{
					CNetMsg::SP rmsg(new CNetMsg);
					ChatOneMessengerMsg(rmsg, sCharIndex, ch->GetName(), tCharIndex, "",
										ch->m_Friend->GetChatColor(), chat );
					SEND_Q( rmsg, ch->m_desc );
				}
			}
		}
		break;
	case MSG_EX_MESSENGER_INVITE:	// �ش� �ɸ��� �ʴ� : makeCharIndex(n) chatIndex(n) charindex(n)	// chatIndex �� -1�̸� ��ȭ�� �߰�
		{
			int chatIndex, makeCharIndex, charIndex;
			RefMsg(msg) >> makeCharIndex
						>> chatIndex
						>> charIndex;

			GAMELOG << init( "MESSENGER_INVITE", ch )
					<< makeCharIndex << delim
					<< chatIndex << delim
					<< charIndex
					<< end;

			if( chatIndex == -1 )
			{
				// ��ȭ�� ������ ���
				// ��ȭ�� ����
				makeCharIndex = ch->m_index;
				chatIndex = gserver->GetMaxChatIndexPerPC(makeCharIndex) + 1;
				//if ( result != -1 )
				//	gserver->SendChatGroup( (MSG_EX_MESSENGER_TYPE) MSG_EX_MESSENGER_INVITE , makeCharIndex, chatIndex, 0, ch->GetName(), "" );
				{
					CNetMsg::SP rmsg(new CNetMsg);
					MsgrMessengerChatMsg(rmsg, MSG_MSGR_MESSENGER_ADD, makeCharIndex, chatIndex, 0, ch->GetName() );
					SEND_Q(rmsg, gserver->m_messenger);
				}
			}

			// �ʴ� �ɸ��� �߰�
			{
				// �޽����� ������ �ŽñⰡ �˾Ƽ� �Ҳ���
				CNetMsg::SP rmsg(new CNetMsg);
				MsgrMessengerChatMsg(rmsg, MSG_MSGR_MESSENGER_ADD_CONFIRM, makeCharIndex, chatIndex, 0, charIndex);
				SEND_Q(rmsg, gserver->m_messenger);
			}
		}
		break;
	case MSG_EX_MESSENGER_OUT:		// �ش� �ɸ��� ��ȭ�濡�� ���� : chatIndex(n) charName(str)
		{
			int chatIndex, makeCharIndex;

			RefMsg(msg) >> makeCharIndex
						>> chatIndex;

			{
				// �޽����� ������ �ŽñⰡ �˾Ƽ� �Ҳ���
				CNetMsg::SP rmsg(new CNetMsg);
				MsgrMessengerChatMsg(rmsg, MSG_MSGR_MESSENGER_DEL, makeCharIndex, chatIndex, 0, ch->GetName() );
				SEND_Q(rmsg, gserver->m_messenger);
			}
		}
		break;
	case MSG_EX_MESSENGER_CHAT:		// �ش� �ɸ��� ��ȭ�濡�� ���� : chatIndex(n) chat(str)
		{
			CLCString chat(1000);
			int chatIndex, makeCharIndex;

			RefMsg(msg) >> makeCharIndex
						>> chatIndex
						>> chat;

			if( ch->m_Friend )
			{
				CNetMsg::SP rmsg(new CNetMsg);
				MsgrMessengerChatMsg(rmsg, MSG_MSGR_MESSENGER_CHAT, makeCharIndex, chatIndex, ch->m_Friend->GetChatColor(), ch->GetName(), chat);

				SEND_Q(rmsg, gserver->m_messenger);
			}
		}
		break;

	case MSG_EX_MESSENGER_GROUP_ADD:	// ģ�� �׷� �߰�	: groupName(str)
		{
			CLCString groupName(MAX_GROUP_NAME_LENGTH+1);
			RefMsg(msg) >> groupName;

			int gIndex = ch->m_Friend->addGroup(groupName);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_EXTEND);
				RefMsg(rmsg) << MSG_EX_MESSENGER
							 << (unsigned char) subtype
							 << gIndex
							 << groupName;

				SEND_Q(rmsg, ch->m_desc);
			}
		}
		break;
	case MSG_EX_MESSENGER_GROUP_DEL:	// ģ�� �׷� ����	: gIndex(n)
		{
			int gIndex;
			RefMsg(msg) >> gIndex;

			if( gIndex == 0 )
			{
				gIndex = -1;
			}
			else
				gIndex = ch->m_Friend->delGroup(gIndex);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_EXTEND);
				RefMsg(rmsg) << MSG_EX_MESSENGER
							 << (unsigned char) subtype
							 << gIndex;

				SEND_Q(rmsg, ch->m_desc);
			}
		}
		break;
	case MSG_EX_MESSENGER_GROUP_CHANGE:	// ģ�� �׷� �̸����� : gIndex(n) newName(str)
		{
			int gIndex;
			CLCString newName(MAX_GROUP_NAME_LENGTH+1);
			RefMsg(msg) >> gIndex
						>> newName;
			gIndex = ch->m_Friend->changeGroupName(gIndex, newName);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_EXTEND);
				RefMsg(rmsg) << MSG_EX_MESSENGER
							 << (unsigned char) subtype
							 << gIndex
							 << newName;

				SEND_Q(rmsg, ch->m_desc);
			}
		}
		break;
	case MSG_EX_MESSENGER_GROUP_MOVE:	// ģ�� �׷� �̵�	  : charName(str) gIndex(n)
		{
			int gIndex, charIndex;

			RefMsg(msg) >> gIndex
						>> charIndex;

			gIndex = ch->m_Friend->moveGroupFriend(gIndex, charIndex);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_EXTEND);
				RefMsg(rmsg) << MSG_EX_MESSENGER
							 << (unsigned char) subtype
							 << gIndex
							 << charIndex;

				SEND_Q(rmsg, ch->m_desc);
			}
		}
		break;
	case MSG_EX_MESSENGER_CHATCOLOR_CHANGE:
		{
			int color = 0;
			RefMsg(msg) >> color;

			ch->m_Friend->SetChatColor(color);
		}
		break;
	case MSG_EX_MESSENGER_BLOCK:		// �ش����� ����	: name(str)
		// GS->C			: errcode(c) charIndex(n) name(str)
		{
			CLCString name(MAX_CHAR_NAME_LENGTH + 1);
			RefMsg(msg) >> name;

			if( strinc(name, "'") || strinc(name, "%") || strinc(name, " ") )
			{
				CNetMsg::SP rmsg(new CNetMsg);
				BlockPCRepMsg(rmsg, MSG_EX_MESSENGER_BLOCK_INVALIDNAME, -1, name);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}

			// �ִ� ���� �ο��� 20��
			if( ch->m_listBlockPC.size() >= BLOCK_MAX_MEMBER )
			{
				CNetMsg::SP rmsg(new CNetMsg);
				BlockPCRepMsg(rmsg, MSG_EX_MESSENGER_NOMORE_BLOCK, -1, name);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}

			// ���۷� ���� ��û�ϰ� ���ۿ��� �ε����� �̸��� �޴´�
			{
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_HELPER_COMMAND);
				RefMsg(rmsg) << MSG_HELPER_BLOCKPC_REQ
							 << ch->m_index
							 << name;

				SEND_Q(rmsg, gserver->m_helper);
			}
		}
		break;
	case MSG_EX_MESSENGER_RELEASE_BLOCK:	// �ش����� ����: charIndex(n)
		// GS->C			: errcode(c) charIndex(n) name(str)
		{
			int charIndex;

			RefMsg(msg) >> charIndex;
			CLCString name(MAX_CHAR_NAME_LENGTH + 1 );
			ch->ReleaseBlockPC(charIndex, name);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_EXTEND);
				RefMsg(rmsg) << MSG_EX_MESSENGER
							 << (unsigned char) MSG_EX_MESSENGER_RELEASE_BLOCK;
				if( strcmp( name, "" ) == 0 )
					RefMsg(rmsg) << (unsigned char) MSG_EX_MESSENGER_BLOCK_NOTCHAR;
				else
					RefMsg(rmsg) << (unsigned char) MSG_EX_MESSENGER_SUCCESS;

				RefMsg(rmsg) << charIndex
							 << name;

				SEND_Q(rmsg, ch->m_desc);
			}

			if( ch->m_Friend )
			{
				CNetMsg::SP rmsg(new CNetMsg);
				HelperFriendSetConditionMsg(rmsg, ch->m_index, ch->m_nCondition, -1, ch);
				SEND_Q(rmsg, gserver->m_helper);
			}
		}
		break;
	}
}
void do_ExCastleWar(CPC * ch, CNetMsg::SP& msg)
{
	char subtype;

	RefMsg(msg) >> subtype;

	switch(subtype)
	{
	case MSG_CASTLE_CRISTAL_RESPOND_START:	// ���� ����
		do_ExCastleCristalRespondStart(ch, msg);
		break;

	case MSG_CASTLE_CRISTAL_RESPOND_END:	// ���� �Ϸ�
		do_ExCastleCristalRespondEnd(ch, msg);
		break;
	case MSG_CASTLE_TOWER_CONTRAL_LIST:		// Ÿ�� ����Ʈ
		do_ExCastleTowerList(ch, msg);
		break;

	case MSG_CASTLE_TOWER_CONTRAL:			// Ÿ�� ����Ʈ �߰�
		do_ExcastleTowerAdd(ch, msg);
		break;

	case MSG_CASTLE_TOWER_REINFORCE:			// ������ Ÿ�� ��ȭ ����		type(c), step(c)
		do_ExCastleTowerReinforce(ch, msg);
		break;

	case MSG_CASTLE_TOWER_REINFORCE_LIST:	// ������ Ÿ�� ��ȭ ����Ʈ		(type(c), step(c))
		do_ExCastleTowerReinforceList(ch, msg);
		break;

	case MSG_CASTLE_TOWER_REPAIRE:			// ���� Ÿ�� ����				cl->gs idx(n) | gs->cl	idx(n)
		do_ExCastleTowerRepaire(ch, msg);
		break;

	case MSG_CASTLE_TOWER_REPAIRE_LIST:		// ���� Ÿ�� ���� ����			cl->gs idx(n) | gs->cl	money(n)
		do_ExCastleTowerRepaireList(ch, msg);
		break;

	case MSG_CASTLE_TOWER_WARP_LIST:		// ���� Ÿ�� ����Ʈ ��û
		do_ExCastleTowerWarpList(ch, msg);
		break;

	case MSG_CASTLE_QUARTERS_INSTALL:		// ��Ȱ���� ��ġ
		do_ExCastleQuartersInstall(ch, msg);
		break;
	}
}

void do_ExCastleCristalRespondStart(CPC * ch, CNetMsg::SP& msg)
{
	// ������ ���� Ȯ��
	if (ch->GetJoinFlag(ZONE_DRATAN) == WCJF_NONE)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NOT_JOIN);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ������ Ȯ��
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if( pCastle->GetState() == WCSF_NORMAL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NOT_WAR);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ��ġ Ȯ��
	if(ch->m_pZone->m_index != ZONE_DRATAN)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_POS_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// �ο� Ȯ�� �ִ� 5��
#ifdef BUGFIX_DRATAN_CRISTAL_RESPOND
	if(pCastle->GetRespondCount() >= 5)
#else
	if(pCastle->GetRespondCount() > 5)
#endif // BUGFIX_DRATAN_CRISTAL_RESPOND
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_MEM_5_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CNPC* pLordSymbol = pCastle->GetLordSymbol();
	if (pLordSymbol && (GetDistance(GET_X(pLordSymbol), GET_Z(pLordSymbol), GET_H(pLordSymbol), ch) > 12
		|| GET_YLAYER(ch) != GET_YLAYER(pLordSymbol)))
	{
		LOG_INFO("Characyer Ylayer: %d LordSymbol yLayer %d", GET_YLAYER(ch), GET_YLAYER(pLordSymbol));
		//CNetMsg::SP rmsg(new CNetMsg);
		//CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_POS_FAIL);
		//SEND_Q(rmsg, ch->m_desc);
		//ch->m_desc->IncreaseHackCount(3);
		//return;
	}
	if(pCastle->GetOwnerGuildIndex() == ch->m_guildInfo->guild()->index())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NOT_OWNER);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// NPC(�ܼ��� ����� ��:388) �ı� üũ
	if( pCastle->m_gateNPC[0] && !DEAD(pCastle->m_gateNPC[0])
		&& pCastle->m_gateNPC[3] && !DEAD(pCastle->m_gateNPC[3])
		&& pCastle->m_gateNPC[4] && !DEAD(pCastle->m_gateNPC[4]))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_CASTLE_CRISTAL_RESPOND_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// NPC(������ ����� ��:389,404) �ı� üũ
	if( (pCastle->m_gateNPC[1] && !DEAD(pCastle->m_gateNPC[1]))
			&& ( pCastle->m_gateNPC[2] && !DEAD(pCastle->m_gateNPC[2])) )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_CASTLE_CRISTAL_RESPOND_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// �κ�������Ƽ ���¿����� ũ����Ż ���� �Ұ���
	if ( ch->IsInvisible() )
	{
		// �κ�������Ƽ ���¸� ���ּ� �ٱ����ϰ� ��..
		ch->CancelInvisible();
		/*ch->m_assist.CureAssist(MST_ASSIST_INVISIBLE, 99);*/

		return;
	}

	// ������ 15���� ������ ũ����Ż ���� �Ұ���
	if ( ch->m_level <= PKMODE_LIMIT_LEVEL )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_CASTLE_CRISTAL_RESPOND_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// �׾����� ũ����Ż ���� �Ұ���
	if (DEAD(ch))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_CASTLE_CRISTAL_RESPOND_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ĳ���� ���� ��ȭ
	ch->SetPlayerState(PLAYER_CRISTAL_RESPOND);

	// ���� ���� �ð� ����
//	ch->SetRespondTime(gserver->m_pulse);
	time_t curTime;
	time(&curTime);

	ch->SetRespondTime(curTime);

	// ���� ���� �ο� �߰�
	pCastle->SetRespondMember(ch);

	{
		// ������ ����
		CNetMsg::SP rmsg(new CNetMsg);
		CastleCristalRespondStartMsg(rmsg, ch);
		ch->m_pArea->SendToCell(rmsg, ch, true);
	}
}

void do_ExCastleCristalRespondEnd(CPC * ch, CNetMsg::SP& msg)
{
	// ������ ���� Ȯ��
	if (ch->GetJoinFlag(ZONE_DRATAN) == WCJF_NONE)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NOT_JOIN);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ������ Ȯ��
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if( pCastle->GetState() == WCSF_NORMAL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NOT_WAR);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ��ġ Ȯ��
	if(ch->m_pZone->m_index != ZONE_DRATAN)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_POS_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ĳ���� ���� Ȯ��
	if(ch->IsSetPlayerState(PLAYER_CRISTAL_RESPOND) == false)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NOT_RESPOND);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
///===
	// ���� �ð� Ȯ�� 3��
//	if(ch->GetRespondTime() == 0  //���� ���� �ð��� ���ų�
//		|| gserver->m_pulse	- ch->GetRespondTime() < 3*PULSE_REAL_MIN) // 3���̳���
//	{
//		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NOT_RESPOND_TIME);
//		SEND_Q(rmsg, ch->m_desc);
//		return;
//	}

	// ���� �ð� Ȯ�� 3��
	time_t curTime;
	time(&curTime);

	if(ch->GetRespondTime() == 0  //���� ���� �ð��� ���ų�
			|| curTime	- ch->GetRespondTime() < 175 ) // 2�� 55���̳���
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NOT_RESPOND_TIME);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ���� ���� ����
	pCastle->InitRespond();

	{
		// ������ ����
		CNetMsg::SP rmsg(new CNetMsg);
		CastleCristalRespondEndMsg(rmsg, ch);
		//	ch->m_pArea->SendToCell(rmsg, ch, true);
		ch->m_pArea->SendToAllClient(rmsg);
	}

	// ���� �ٲ�
	CGuildMember * pMember = ch->m_guildInfo;
	if (pMember == NULL)
	{
		return;
	}
	CGuild * pGuild = pMember->guild() ;
	if (pGuild == NULL)
	{
		return;
	}

	GAMELOG << init("DRATAN CASTLE CHANGE OWNER")
			<< "before " << delim << pCastle->GetOwnerGuildIndex() << delim
			<< "after " << delim  << pGuild->index() << delim << "char " << delim << ch->m_index << end;

	// ���� ����
	// ���� ��Ȱ���� ����  -071016 - whs25 �߰� �۾�
	pCastle->RegenCastleControlNPC();

	// �ش� ��� ��Ȱ ���� ���� -> ��Ȱ ���� ����
	for(int i=0; i<7; i++)
	{
		if (pCastle->m_nRebrithGuild[i] == pGuild->index())
		{
			pCastle->m_nRebrithGuild[i] = -1;
			memset((void *)pCastle->m_strRebrithGuild[i], 0, 51);
			break;
		}
	}

	{
		// ��Ȱ ���� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		CastletowerQuartersListMsg(rmsg, pCastle);
		ch->m_pArea->SendToAllClient(rmsg);
	}

	// ���� ��� �÷��� <=> ���� ��� �÷��� ��ȯ
	pCastle->ChangeSide(pGuild->index());

	// ���� ��� ��ȯ
	pCastle->SetOwner(pGuild);

	//  NPC_CASTLE_TOWER hp 1/2�� ����
	pCastle->RegenCastleTowerHalf();

	//  �ش� ��� �̿� ĳ���� ��Ȱ����, ���̸����� �̵�
	pCastle->GetOutNonDefense();

	{
		//	���� ���� ����
		CNetMsg::SP rmsg(new CNetMsg);
		GuildWarCastleStateMsg(rmsg, ZONE_DRATAN, ch, pCastle);
		ch->m_pArea->SendToAllClient(rmsg);
	}
}

void do_ExCastleTowerList(CPC * ch, CNetMsg::SP& msg)
{
	// ����Ʈ ��û
	// ĳ���� Ȯ��
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if( pCastle->GetState() == WCSF_NORMAL				// �������� �ƴҶ�
			&& pCastle->GetOwnerCharIndex() == ch->m_index		// ���� �� ���
			&& ch->m_pZone->m_index == ZONE_DRATAN)				// ĳ���Ͱ� ���ź�� ������
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleTowerListMsg(rmsg, pCastle);
		SEND_Q(rmsg, ch->m_desc);
	}
}

void do_ExcastleTowerAdd(CPC * ch, CNetMsg::SP& msg)
{
	char status[7];
	memset(status, 0, 7);

	for(int i = 0; i < 7; i++)
	{
		RefMsg(msg) >> status[i];
	}

	// ĳ���� Ȯ��
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if( pCastle->GetState() == WCSF_NORMAL				// �������� �ƴҶ�
			&& pCastle->GetOwnerCharIndex() == ch->m_index		// ���� �� ���
			&& ch->m_pZone->m_index == ZONE_DRATAN)				// ĳ���Ͱ� ���ź�� ������
	{
		// ��Ȯ��
		int nMoney = 1000000;
		int total_money = 0;

		int change_status = 0;
		for(int i = 0; i< 7; i++)
		{
			change_status = status[i] - pCastle->GetTowerStatus(i);
			if (change_status > 0)
			{
				// ��ȭ üũ
				int count = status[i];
				for(int j = pCastle->GetTowerStatus(i); j < count; j++)
				{
					total_money += (j+1) * nMoney;
				}
			}
		}

		if (ch->m_inventory.getMoney() >= total_money)
		{
			ch->m_inventory.decreaseMoney(total_money);
		}
		else
		{
			// ������ �޼��� ����
			CNetMsg::SP rmsg(new CNetMsg);
			CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_MONEY);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}

		// ����
		for(int k = 0; k < 7; k++)
		{
			pCastle->SetTowerStatus(k, status[k]);
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			HelperCastleTowerAddMsg(rmsg, ZONE_DRATAN, pCastle);
			SEND_Q(rmsg, gserver->m_helper);
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			CastleTowerAddMsg(rmsg, pCastle);
			SEND_Q(rmsg, ch->m_desc);
		}
	}
}

void do_ExCastleTowerReinforce(CPC * ch, CNetMsg::SP& msg)
{
	// Ÿ�� ��ȭ
	// ���� �������� Ȯ��
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if (pCastle->GetOwnerGuildIndex() != ch->m_guildInfo->guild()->index())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NOT_ATTACK);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	char type = 0, step = 0;
	RefMsg(msg) >> type >> step;

	// type : 0. ������ Ÿ�� 1. ������ Ÿ�� 2. ����
	// step 1 - 3
	if (type < 0 || type > 3 || step <= 0 || step > 3)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_SAME_DATA);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ������ ��
	char before_step = pCastle->GetReinforceStep((int)type);
	char diff = step - before_step;
	if (diff <= 0 || step > 3)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_DIFFER);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ���� ��
	int total_money = 0;
	int price[3][3] =
	{
		{ 1000000, 1000000, 2000000 },
		{ 2000000, 2000000, 2000000 },
		{ 3000000, 3000000, 3000000 },
	};

	for(char i = step; i > before_step; i--)
	{
		total_money += price[(int)i-1][(int)type];
	}

	if(ch->m_inventory.getMoney() >= total_money)
	{
		ch->m_inventory.decreaseMoney(total_money);
	}
	else
	{
		// ������ �޼��� ����
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_MONEY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ����
	pCastle->SetReinforceStep(type, step);

	{
		// ����
		CNetMsg::SP rmsg(new CNetMsg);
		HelperCastleReinforceMsg(rmsg, type, step, ZONE_DRATAN);
		SEND_Q(rmsg, gserver->m_helper);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleTowerReinforceMsg(rmsg, type, pCastle);
		SEND_Q(rmsg, ch->m_desc);
	}

	///=== ���� �޼��� �ʿ�
}

void do_ExCastleTowerReinforceList(CPC * ch, CNetMsg::SP& msg)
{
	// ������ Ÿ�� ��ȭ ����Ʈ
	char type = 0;
	RefMsg(msg) >> type;
	if( type < 0 || type > 2)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_DATA);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if (pCastle->GetOwnerGuildIndex() == ch->m_guildInfo->guild()->index())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleTowerReinforceListMsg(rmsg, type, pCastle);
		SEND_Q(rmsg, ch->m_desc);
	}
}

void do_ExCastleTowerRepaire(CPC * ch, CNetMsg::SP& msg)
{
	// ���� ��û
	int idx = 0;
	RefMsg(msg) >> idx;

	if (idx < 351 || idx > 381)	// ������ Ÿ�� ����
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_DATA);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// npc����Ʈ���� �˻�
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if (pCastle->CheckBuyTower(idx) == false)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NOT_BUY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CNPCProto * pProto = gserver->m_npcProtoList.FindProto(idx);
	if( pProto == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_NPC);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CZone* pZone = gserver->FindZone(ZONE_DRATAN);
	if (pZone == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_POS_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CArea * pArea = pZone->m_area;
	if( pArea == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_POS_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ��� �ִ��� �˻�
	CNPC * pNpc = pArea->FindProtoNPCInCell( ch, idx, false, 9, true);
	if (pNpc == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_NPC);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if(DEAD(pNpc))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_DEAD_NPC);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if( ch->m_guildInfo == NULL && ch->m_guildInfo->guild() == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_PERMISSION_DENIED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if( ch->m_guildInfo->pos() != MSG_GUILD_POSITION_BOSS
			&& ch->m_guildInfo->pos() != MSG_GUILD_POSITION_OFFICER )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_PERMISSION_DENIED);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ������� �˻�
	LONGLONG total_money = 0;
	if (idx == 351)
	{
		// ������ Ÿ��
		total_money = 10000000;
	}
	else
	{
		total_money = ( ( (idx - 352) % 5) + 1 ) * 1000000;
	}

	total_money = total_money - (total_money * pNpc->m_hp) / (pNpc->m_maxHP);

	if(ch->m_inventory.getMoney() >= total_money)
	{
		ch->m_inventory.decreaseMoney(total_money);
	}
	else
	{
		// ������ �޼��� ����
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_MONEY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ����
	pNpc->m_hp = pNpc->m_maxHP;
	pNpc->m_mp = pNpc->m_maxMP;

	{
		// �ֺ��� ����
		CNetMsg::SP rmsg(new CNetMsg);
		CharStatusMsg(rmsg, pNpc, 0);
		ch->m_pArea->SendToCell(rmsg, ch, true);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleTowerRepaireMsg(rmsg, idx, total_money);
		SEND_Q(rmsg, ch->m_desc);
	}
}

void do_ExCastleTowerRepaireList(CPC * ch, CNetMsg::SP& msg)
{
	// ���� ��� ����
	int idx = 0;
	RefMsg(msg) >> idx;

	if (idx < 351 || idx > 381)	// ������ Ÿ�� ����
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_DATA);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// npc����Ʈ���� �˻�
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if (pCastle->CheckBuyTower(idx) == false)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NOT_BUY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CNPCProto * pProto = gserver->m_npcProtoList.FindProto(idx);
	if( pProto == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_NPC);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CZone* pZone = gserver->FindZone(ZONE_DRATAN);
	if (pZone == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_POS_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CArea * pArea = pZone->m_area;
	if (pArea == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_POS_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ��� �ִ��� �˻�
	CNPC * pNpc = pArea->FindProtoNPCInCell(ch, idx, false, 9, true);
	if (pNpc == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_NPC);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if(DEAD(pNpc))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_DEAD_NPC);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ������� �˻�
	LONGLONG total_money = 0;
	if (idx == 351)
	{
		// ������ Ÿ��
		total_money = 10000000;
	}
	else
	{
		total_money = ( ( (idx - 352) % 5) + 1 ) * 1000000;
	}

	total_money = total_money - (total_money * pNpc->m_hp) / (pNpc->m_maxHP);

	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleTowerRepaireListMsg(rmsg, idx, total_money);
		SEND_Q(rmsg, ch->m_desc);
	}
}

void do_ExCastleTowerWarpList(CPC * ch, CNetMsg::SP& msg)
{
	int curindex = 0;
	RefMsg(msg) >> curindex;

	// ����Ÿ�� ��ȣ Ȯ��
	if (curindex < 382 || curindex > 386)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_DATA);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	// �������� ���� Ÿ�� Ȯ��
	unsigned char total = 0;
	int aliveindex[5];
	for(unsigned char i = 0; i < 5; i++)
	{
		if(pCastle->m_pWarpNPC[i] == NULL)
		{
			continue;
		}

		CNPCProto * pProto = pCastle->m_pWarpNPC[i]->m_proto;
		if (pProto == NULL)
		{
			continue;
		}
		aliveindex[total] = pCastle->m_pWarpNPC[i]->m_proto->m_index;
		total++;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleTowerWarpListMsg(rmsg, aliveindex, total);
		SEND_Q(rmsg, ch->m_desc);
	}
}

void do_ExCastleQuartersInstall(CPC * ch, CNetMsg::SP& msg)
{
	int qindex = 0;

	RefMsg(msg) >> qindex;

	// ����Ȯ��
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	// ��Ȱ���� ��ȣ Ȯ��
	if(qindex < 390 || qindex > 396)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_DATA);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ĳ������ ��� Ȯ��
	CGuildMember * pMember = ch->m_guildInfo;
	if (pMember == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_HAVE_NO_GUILD);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CGuild * pGuild = pMember->guild();
	if (pGuild == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_HAVE_NO_GUILD);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	int gindex = pGuild->index();
	if (gindex < 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_HAVE_NO_GUILD);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ������� Ȯ��
	if (ch->GetJoinFlag(ZONE_DRATAN) != WCJF_ATTACK_GUILD)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NOT_ATTACK);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ������ ��Ȱ���� ����ִ��� Ȯ��
	int idx = qindex - 390;
	if (pCastle->m_pRebrithNPC[idx] == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_NPC2);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	if (DEAD(pCastle->m_pRebrithNPC[idx]))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_DEAD_NPC2);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ������ ��Ȱ ���� ����� Ȯ��
	if (pCastle->m_nRebrithGuild[idx] != -1)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_USE_NPC);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// �ٸ� ��Ȱ���� ����� Ȯ��
	for(int i=0; i<7; i++)
	{
		if (pCastle->m_nRebrithGuild[i] == gindex)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_USE_NPC_OTHER);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}
	}

	const int nNeedMoney[10] = { 3000000, 2000000, 2000000, 2000000, 2000000,
								 1000000, 1000000, 1000000, 1000000, 1000000
							   };

	if( ch->m_inventory.getMoney() < nNeedMoney[idx] )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CastleErrorMsg(rmsg, MSG_EX_CASTLE_ERROR_NO_MONEY); 	// ���� �����մϴ�. c
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	else
	{
		ch->m_inventory.decreaseMoney(nNeedMoney[idx]);
	}

	// ���� ����Ʈ �ε���
	int list_index = 0;
	list_index = pCastle->m_pRebrithNPC[idx]->m_index;

	// ��Ȱ ���� ��ġ
	pCastle->m_nRebrithGuild[idx] = gindex;
	strncpy(pCastle->m_strRebrithGuild[idx], pGuild->name(), 51);

	{
		CNetMsg::SP rmsg(new CNetMsg);
		HeplerCastleRebrithInstallMsg(rmsg, qindex, gindex, pGuild->name());
		SEND_Q(rmsg, gserver->m_helper);
	}

	{
		// 090106 yhj  �Լ� ������..�Ű����� �Ѱ� �߰�
		CNetMsg::SP rmsg(new CNetMsg);
		CastleTowerRebrithInstallMsg(rmsg, qindex, gindex, pGuild->name(), list_index);
		ch->m_pArea->SendToAllClient(rmsg);
	}

	// ��Ȱ ���� ��� �α�
	GAMELOG << init("WAR CASTLE : BUY QUARTERS") << delim << "QUARTER index" << delim << qindex
			<< delim << "GUILD index" << delim << gindex << delim << "GUILD name" << delim << pGuild->name() << end;
}

void do_DVD(CPC * ch, CNetMsg::SP& msg)
{
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if (pCastle->m_dvd.GetZone() == 0)
	{
		// ���ź ���� ���� ������ ������
		return;
	}

	char subtype;
	RefMsg(msg) >> subtype;

	switch(subtype)
	{
	case MSG_DUNGEON_ENTER:
		do_dvdDungenEnter( ch, msg );
		break;

	case MSG_DUNGEON_INFO :
		do_dvdInfo(ch, msg);
		break;

	case MSG_MANAGEMENT:
		do_dvdManagement( ch, msg );
		break;
	}
}

void do_dvdManagement(CPC * ch, CNetMsg::SP& msg)
{
	char	subType;
	int		nRate;

#ifdef NPC_CHECK
	int npcIndex;
	CNPC *npc;
	RefMsg(msg) >> subType
				>> npcIndex;
	npc = ch->m_pArea->FindProtoNPCInCell(ch, npcIndex, false, 2);
	if(!npc)
	{
		GAMELOG << init("DVD Management FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
	if( !npc->IsFlag(NPC_ZONEMOVER) && !npc->IsFlag(NPC_WARCASTLE) )
	{
		GAMELOG << init("DVD Management FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
#else
	RefMsg(msg) >> subType;
#endif

	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if( ch == NULL )
	{
		// ERROR
		CNetMsg::SP rmsg(new CNetMsg);
		DVDManagementMsg( rmsg, MSG_MANAGEMENT_ETC );
		RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_ZONE;
		SEND_Q( rmsg, ch->m_desc );
		return;
	}

	//�Ϲ� ���� �޴� �߰�
	if( subType != MSG_MANAGEMENT_ENV_INFO 
		&& subType != MSG_MANAGEMENT_STATE_INFO 
		&& subType != MSG_MANAGEMENT_ENV_CHANGE 
		&& subType != MSG_MANAGEMENT_STATE_CHANGE 
		&& subType != MSG_MANAGEMENT_MANAGER_CONFIRM_NORMAL)
	{
		if( ch->m_guildInfo == NULL)
		{
			// ERROR ��� ����
			CNetMsg::SP rmsg(new CNetMsg);
			DVDManagementMsg( rmsg, MSG_MANAGEMENT_MANAGER_CONFIRM );
			RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_CONFIRM;
			SEND_Q( rmsg, ch->m_desc );
			return;
		}
	}
	
	switch(subType)
	{
	case MSG_MANAGEMENT_MANAGER_CONFIRM :
		{
			if( gserver->m_subno != WAR_CASTLE_SUBNUMBER_DRATAN )
			{
				// ERROR CONFIRM FAIL
				CNetMsg::SP rmsg(new CNetMsg);
				DVDManagementMsg( rmsg, MSG_MANAGEMENT_MANAGER_CONFIRM );
				RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_ZONE;
				SEND_Q( rmsg, ch->m_desc );
				break;
			}

			if( ch->m_guildInfo == NULL )
			{
				LOG_ERROR("HACKING? : GuildInfo is NULL. charIndex[%d]", ch->m_index);
				ch->m_desc->Close("GuildInfo is NULL");
				return;
			}

			if( ch->m_guildInfo->guild()->index() == pCastle->GetOwnerGuildIndex()
					&& ch->m_guildInfo->pos() < 2 )
			{
				if(pCastle->m_dvd.GetOwnerMode() == false)
				{
					GoldType_t nas = 0;

					int time = gserver->getNowSecond() - pCastle->m_dvd.GetChangeNormalTime();
					nas = ((LONGLONG)time / (60 * 60) + 1) * 3000000;

					if( nas >= 36000000 )
						nas = 36000000;

					pCastle->m_dvd.setChangeNeedNas(nas);

					CNetMsg::SP rmsg(new CNetMsg);
					DVDManagementMsg( rmsg, MSG_MANAGEMENT_MANAGER_CONFIRM );
					RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_NORMAL_MODE
						<< nas;
					SEND_Q( rmsg, ch->m_desc );
				}
				else
				{
					// ERROR OK
					CNetMsg::SP rmsg(new CNetMsg);
					DVDManagementMsg( rmsg, MSG_MANAGEMENT_MANAGER_CONFIRM );
					RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_OK;
					SEND_Q( rmsg, ch->m_desc );
				}
			}
			else
			{
				// ERROR CONFIRM FAIL
				CNetMsg::SP rmsg(new CNetMsg);
				DVDManagementMsg( rmsg, MSG_MANAGEMENT_MANAGER_CONFIRM );
				RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_CONFIRM;
				SEND_Q( rmsg, ch->m_desc );
			}
		}
		break;
		// INFO REQ
	case MSG_MANAGEMENT_ENV_INFO :
		{
			CNetMsg::SP rmsg(new CNetMsg);
			DVDManagementMsg( rmsg, MSG_MANAGEMENT_ENV_INFO );
			RefMsg(rmsg) << pCastle->m_dvd.GetEnvRate();
			if(pCastle->m_dvd.GetOwnerMode() == false)
			{
				RefMsg(rmsg) << (LONGLONG)CASTLE_DUNGEON_ENV_CHANGE_NEED_NAS_NORMAL;
			}
			else
			{
				RefMsg(rmsg) << (LONGLONG)CASTLE_DUNGEON_ENV_CHANGE_NEED_NAS_OWNER;
			}
			SEND_Q( rmsg, ch->m_desc );
		}
		break;
	case MSG_MANAGEMENT_STATE_INFO :
		{
			CNetMsg::SP rmsg(new CNetMsg);
			DVDManagementMsg( rmsg, MSG_MANAGEMENT_STATE_INFO );
			RefMsg(rmsg) << pCastle->m_dvd.GetMobRate();
			if(pCastle->m_dvd.GetOwnerMode() == false)
			{
				RefMsg(rmsg) << (LONGLONG)CASTLE_DUNGEON_ENV_CHANGE_NEED_NAS_NORMAL;
			}
			else
			{
				RefMsg(rmsg) << (LONGLONG)CASTLE_DUNGEON_ENV_CHANGE_NEED_NAS_OWNER;
			}
			SEND_Q( rmsg, ch->m_desc );
		}
		break;
	case MSG_MANAGEMENT_TAX_INFO :
		{
			CNetMsg::SP rmsg(new CNetMsg);
			DVDManagementMsg( rmsg, MSG_MANAGEMENT_TAX_INFO );
			RefMsg(rmsg) << pCastle->m_dvd.GetFeeRate();
			SEND_Q( rmsg, ch->m_desc );
		}
		break;
	case MSG_MANAGEMENT_HUNTER_TAX_INFO :
		{
			CNetMsg::SP rmsg(new CNetMsg);
			DVDManagementMsg( rmsg, MSG_MANAGEMENT_HUNTER_TAX_INFO );
			RefMsg(rmsg) << pCastle->m_dvd.GetHuntRate();
			SEND_Q( rmsg, ch->m_desc );
		}
		break;

		// CHANGE REQ
	case MSG_MANAGEMENT_ENV_CHANGE :
		{
			RefMsg(msg) >> nRate;

			if( ch->m_guildInfo != NULL
				&& ch->m_guildInfo->guild()->index() != pCastle->GetOwnerGuildIndex())
			{
				if(pCastle->m_dvd.GetOwnerMode() == true)
				{
					LOG_ERROR("HACKING? Invalid ENV CHANGE INFO EnvRate : %d, MobRate : %d",  pCastle->m_dvd.GetEnvRate(), pCastle->m_dvd.GetMobRate());
					ch->m_desc->Close("Invalid ENV CHANGE INFO");
					return;
				}
			}

			if (nRate <= 0)
				return ;

			LONGLONG needMoney = 0;

			if(pCastle->m_dvd.GetOwnerMode() == true)
			{
				needMoney = nRate/10 * 500000;
			}
			else
			{
				needMoney = nRate/10 * 1000000;
			}

			if(	ch->m_inventory.getMoney() < needMoney || needMoney <= 0)
			{
				// ERROR �� ����
				CNetMsg::SP rmsg(new CNetMsg);
				DVDManagementMsg( rmsg, MSG_MANAGEMENT_ENV_CHANGE );
				RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_MONEY;
				SEND_Q( rmsg, ch->m_desc );
				return;
			}
			else
			{
				ch->m_inventory.decreaseMoney(needMoney);
			}

			pCastle->m_dvd.ChangeEnvRate(nRate);

			{
				// ���ۿ� ���� ��û nRate
				CNetMsg::SP rmsg(new CNetMsg);
				HelperDVDRateChangeMsg(rmsg, MSG_MANAGEMENT_ENV_CHANGE , pCastle->m_dvd.GetEnvRate(), pCastle->m_dvd.GetOwnerMode() );
				SEND_Q(rmsg, gserver->m_helper);
			}

			{
				// ���� �Ϸ� �޼���
				CNetMsg::SP rmsg(new CNetMsg);
				DVDManagementMsg( rmsg, MSG_MANAGEMENT_ENV_CHANGE );
				RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_OK;
				SEND_Q( rmsg, ch->m_desc );
			}

			GAMELOG << init(" DRATAN DYNAMIC DUNGEON ENVIRONMENT CHANGE " , ch ) << delim
				<< "CHNAGE RATE : " << nRate << delim
				<< "CURRENT RATE : " << pCastle->m_dvd.GetEnvRate() << delim
				<< "Spend Money : " << needMoney << end;
		}
		break;

	case MSG_MANAGEMENT_STATE_CHANGE :
		{
			// ���˻� 10%�� 1000000
			RefMsg(msg) >> nRate;
			if (nRate <= 0)
				return ;

			if(ch->m_guildInfo != NULL 
				&& ch->m_guildInfo->guild()->index() != pCastle->GetOwnerGuildIndex())
			{
				if(pCastle->m_dvd.GetOwnerMode() == true)
				{
					LOG_ERROR("HACKING? Invalid ENV CHANGE INFO EnvRate : %d, MobRate : %d",  pCastle->m_dvd.GetEnvRate(), pCastle->m_dvd.GetMobRate());
					ch->m_desc->Close("Invalid ENV CHANGE INFO");
					return;
				}
			}

			LONGLONG needMoney = 0;

			if(pCastle->m_dvd.GetOwnerMode() == true)
			{
				needMoney = nRate/10 * 500000;
			}
			else
			{
				needMoney = nRate/10 * 1000000;
			}

			if(ch->m_inventory.getMoney() < needMoney || needMoney <=0)
			{
				// ERROR �� ����
				CNetMsg::SP rmsg(new CNetMsg);
				DVDManagementMsg( rmsg, MSG_MANAGEMENT_ENV_CHANGE );
				RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_MONEY;
				SEND_Q( rmsg, ch->m_desc );
				return;
			}
			else
			{
				ch->m_inventory.decreaseMoney(needMoney);
			}

			{
				// ���ۿ� ���� ��û nRate
				pCastle->m_dvd.ChangeMobRate(nRate);
				CNetMsg::SP rmsg(new CNetMsg);
				HelperDVDRateChangeMsg(rmsg, MSG_MANAGEMENT_STATE_CHANGE , pCastle->m_dvd.GetMobRate(), pCastle->m_dvd.GetOwnerMode() );
				SEND_Q(rmsg, gserver->m_helper);
			}

			{
				CNetMsg::SP rmsg(new CNetMsg);
				DVDManagementMsg( rmsg, MSG_MANAGEMENT_STATE_CHANGE );
				RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_OK;
				SEND_Q( rmsg, ch->m_desc );
			}

			GAMELOG << init(" DRATAN DYNAMIC DUNGEON MONSTER RATE CHANGE " , ch ) << delim
				<< "CHNAGE RATE : " << nRate << delim
				<< "CURRENT RATE : " << pCastle->m_dvd.GetMobRate() << delim
				<< "Spend Money : " << needMoney << end;
		}
		break;

	case MSG_MANAGEMENT_TAX_CHANGE :
		{
			RefMsg(msg) >> nRate;
			if (nRate <= 0)
				return ;
			pCastle->m_dvd.ChangeFeeRate(nRate);

			{
				// ���ۿ� ���� ��û nRate
				CNetMsg::SP rmsg(new CNetMsg);
				HelperDVDRateChangeMsg(rmsg, MSG_MANAGEMENT_TAX_CHANGE , pCastle->m_dvd.GetFeeRate(), pCastle->m_dvd.GetOwnerMode() );
				SEND_Q(rmsg, gserver->m_helper);
			}

			{
				CNetMsg::SP rmsg(new CNetMsg);
				DVDManagementMsg( rmsg, MSG_MANAGEMENT_TAX_CHANGE );
				RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_OK;
				SEND_Q( rmsg, ch->m_desc );
			}

			GAMELOG << init(" DRATAN DYNAMIC DUNGEON TAX CHANGE " , ch ) << delim
				<< "CHNAGE RATE : " << nRate << end;
		}
		break;

	case MSG_MANAGEMENT_HUNTER_TAX_CHANGE :
		{
			RefMsg(msg) >> nRate;
			if (nRate <= 0)
				return ;
			pCastle->m_dvd.ChangeHuntRate(nRate);

			{
				// ���ۿ� ���� ��û nRate
				CNetMsg::SP rmsg(new CNetMsg);
				HelperDVDRateChangeMsg(rmsg, MSG_MANAGEMENT_HUNTER_TAX_CHANGE , pCastle->m_dvd.GetHuntRate(), pCastle->m_dvd.GetOwnerMode() );
				SEND_Q(rmsg, gserver->m_helper);
			}

			{
				CNetMsg::SP rmsg(new CNetMsg);
				DVDManagementMsg( rmsg, MSG_MANAGEMENT_HUNTER_TAX_CHANGE );
				RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_OK;
				SEND_Q( rmsg, ch->m_desc );
			}

			GAMELOG << init(" DRATAN DYNAMIC DUNGEON HUNTER TAX CHANGE " , ch ) << delim
					<< "CHNAGE RATE : " << nRate << end;
		}
		break;
		
	case MSG_MANAGEMENT_MANAGER_CONFIRM_NORMAL:
		{
			if( gserver->m_subno != WAR_CASTLE_SUBNUMBER_DRATAN )
			{
				// ERROR CONFIRM FAIL
				CNetMsg::SP rmsg(new CNetMsg);
				DVDManagementMsg( rmsg, MSG_MANAGEMENT_MANAGER_CONFIRM_NORMAL );
				RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_ZONE;
				SEND_Q( rmsg, ch->m_desc );
				break;
			}

			if( ch->m_guildInfo != NULL 
				&& ch->m_guildInfo->guild()->index() == pCastle->GetOwnerGuildIndex()
				&& ch->m_guildInfo->pos() < 2 )
			{
				if(pCastle->m_dvd.GetOwnerMode() == false)
				{
					// ERROR CONFIRM NORMAL SUCCESS
					CNetMsg::SP rmsg(new CNetMsg);
					DVDManagementMsg( rmsg, MSG_MANAGEMENT_MANAGER_CONFIRM_NORMAL );
					RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_NORMAL_MODE;
					SEND_Q( rmsg, ch->m_desc );
					break;
				}
				else
				{
					// ERROR CONFIRM NORMAL FAIL
					CNetMsg::SP rmsg(new CNetMsg);
					DVDManagementMsg( rmsg, MSG_MANAGEMENT_MANAGER_CONFIRM_NORMAL );
					RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_CONFIRM;
					SEND_Q( rmsg, ch->m_desc );
					break;
				}
			}

			if(pCastle->m_dvd.GetOwnerMode() == false)
			{
				// ERROR CONFIRM NORMAL SUCCESS
				CNetMsg::SP rmsg(new CNetMsg);
				DVDManagementMsg( rmsg, MSG_MANAGEMENT_MANAGER_CONFIRM_NORMAL );
				RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_OK;
				SEND_Q( rmsg, ch->m_desc );
				break;
			}
			else
			{
				// ERROR CONFIRM NORMAL FAIL
				CNetMsg::SP rmsg(new CNetMsg);
				DVDManagementMsg( rmsg, MSG_MANAGEMENT_MANAGER_CONFIRM_NORMAL );
				RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_CONFIRM;
				SEND_Q( rmsg, ch->m_desc );
				break;
			}
		}
	case MSG_NAMAGEMENT_CHANGE_OWNER_MODE:
		
		if(ch->m_guildInfo == NULL)
		{
			LOG_ERROR("HACKING? : GuildInfo is NULL. charIndex[%d]", ch->m_index);
			ch->m_desc->Close("GuildInfo is NULL");
			return;
		}
		if( ch->m_guildInfo->guild()->index() == pCastle->GetOwnerGuildIndex()
			&& ch->m_guildInfo->pos() < 2 )
		{
			GoldType_t needNas = pCastle->m_dvd.getChangeNeedNas();

			if(	ch->m_inventory.getMoney() < needNas)
			{
				// ERROR �� ����
				CNetMsg::SP rmsg(new CNetMsg);
				DVDManagementMsg( rmsg, MSG_NAMAGEMENT_CHANGE_OWNER_MODE );
				RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_MONEY;
				SEND_Q( rmsg, ch->m_desc );
				return;
			}
			else
			{
				ch->m_inventory.decreaseMoney(needNas);
			}
		}
		else
		{
			CNetMsg::SP rmsg(new CNetMsg);
			DVDManagementMsg( rmsg, MSG_NAMAGEMENT_CHANGE_OWNER_MODE );
			RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_CONFIRM;
			SEND_Q( rmsg, ch->m_desc );
			return;
		}
		
		pCastle->m_dvd.setOwnerMode(true);
		
		{
			// ���ۿ� ���� ��û nRate
			pCastle->m_dvd.ChangeMobRate(100);
			CNetMsg::SP rmsg(new CNetMsg);
			HelperDVDRateChangeMsg(rmsg, MSG_MANAGEMENT_STATE_CHANGE , pCastle->m_dvd.GetMobRate(), pCastle->m_dvd.GetOwnerMode() );
			SEND_Q(rmsg, gserver->m_helper);
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			DVDManagementMsg( rmsg, MSG_MANAGEMENT_STATE_CHANGE );
			RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_OK;
			SEND_Q( rmsg, ch->m_desc );
		}

		{
			// ���ۿ� ���� ��û nRate
			pCastle->m_dvd.ChangeEnvRate(100);
			CNetMsg::SP rmsg(new CNetMsg);
			HelperDVDRateChangeMsg(rmsg, MSG_MANAGEMENT_ENV_CHANGE , pCastle->m_dvd.GetEnvRate(), pCastle->m_dvd.GetOwnerMode() );
			SEND_Q(rmsg, gserver->m_helper);
		}

		{
			// ���� �Ϸ� �޼���
			CNetMsg::SP rmsg(new CNetMsg);
			DVDManagementMsg( rmsg, MSG_MANAGEMENT_ENV_CHANGE );
			RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_OK;
			SEND_Q( rmsg, ch->m_desc );
		}

		{
			//���ָ�� ���� �Ϸ� �޽���
			CNetMsg::SP rmsg(new CNetMsg);
			DVDManagementMsg( rmsg, MSG_NAMAGEMENT_CHANGE_OWNER_MODE);
			RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_OK;
			SEND_Q( rmsg, ch->m_desc );
		}		
		break;
	}
}

void do_dvdDungenEnter( CPC *ch, CNetMsg::SP& msg )
{
	LONGLONG needMoney=0;

	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if (pCastle->m_dvd.GetZone() == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		DVDManagementMsg( rmsg, MSG_MANAGEMENT_ETC );
		RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_ZONE;
		SEND_Q( rmsg, ch->m_desc );
		return;
	}

#ifdef LC_TLD
	time_t curTime;
	time(&curTime);
	int nextTime = pCastle->GetNextWarTime();
	if(curTime + 60 > nextTime)
	{
		GAMELOG << init("DRATAN DYNAMIC DUNGEON TIME ERROR", ch)
				<< "NOW" << delim << (int)curTime << delim
				<< "NEXT WARTIME" << delim << nextTime
				<< end;
		return ;
	}
#endif // LC_TLD

	unsigned char subType;
	RefMsg(msg) >> subType;

	if( ch->m_guildInfo != NULL )
	{
		// ���� ����̸� 0��
		if( ch->m_guildInfo->guild()->index() == pCastle->GetOwnerGuildIndex() )
		{
			needMoney = 0;
		}
		else
		{
			needMoney = ( ch->m_level * 1000 ) * 2 * ( pCastle->m_dvd.GetFeeRate() ) / 100 ;
		}
	}
	else
	{
		needMoney = ( ch->m_level * 1000 ) * 2 * ( pCastle->m_dvd.GetFeeRate() ) / 100;
	}

	switch( subType )
	{
	case MSG_DUNGEON_ENTER_FEE :
		{
			CNetMsg::SP rmsg(new CNetMsg);
			DVDDungeonEnterMsg( rmsg, MSG_DUNGEON_ENTER_FEE );
			RefMsg(rmsg) <<  needMoney;
			SEND_Q( rmsg, ch->m_desc );
		}
		break;

	case MSG_DUNGEON_GO :
		{
			if( needMoney > 0 )
			{
				if(	ch->m_inventory.getMoney() < needMoney)
				{
					// ERROR �� ����
					CNetMsg::SP rmsg(new CNetMsg);
					DVDDungeonEnterMsg( rmsg, MSG_DUNGEON_GO );
					RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_MONEY;
					SEND_Q( rmsg, ch->m_desc );
					return;
				}
				else
				{
					ch->m_inventory.decreaseMoney(needMoney);
				}

				//���� ����
				LONGLONG nTax = needMoney - ( ch->m_level * 1000 );
				if( nTax > 0 )
					gserver->AddTaxItemDratan( needMoney - ( nTax ) );
			}

			CZone* pZone = gserver->FindZone( ZONE_DRATAN_CASTLE_DUNGEON );
			if( pZone )
			{
				int extra = 0;
				GoZone(ch, pZone->m_index ,
					   pZone->m_zonePos[extra][0],														// ylayer
					   GetRandom(pZone->m_zonePos[extra][1], pZone->m_zonePos[extra][3]) / 2.0f,		// x
					   GetRandom(pZone->m_zonePos[extra][2], pZone->m_zonePos[extra][4]) / 2.0f);		// z
			}
		}
		break;
	}
}

void do_dvdInfo(CPC * ch, CNetMsg::SP& msg)
{
#ifdef NPC_CHECK
	int npcIndex;
	CNPC *npc;
	RefMsg(msg) >> npcIndex;
	npc = ch->m_pArea->FindProtoNPCInCell(ch, npcIndex, false, 2);
	if(!npc)
	{
		GAMELOG << init("DVD Info FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
	if( !npc->IsFlag(NPC_WARCASTLE) && !npc->IsFlag(NPC_ZONEMOVER) )
	{
		GAMELOG << init("DVD Info FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
#endif
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	if (pCastle->m_dvd.GetZone() == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		DVDManagementMsg( rmsg, MSG_MANAGEMENT_ETC );
		RefMsg(rmsg) << (unsigned char) MSG_DVD_ERROR_ZONE;
		SEND_Q( rmsg, ch->m_desc );
		return;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		DVDInfoMsg(ch, rmsg, pCastle->m_dvd.GetEnvRate(), pCastle->m_dvd.GetMobRate() );
		SEND_Q(rmsg, ch->m_desc);
	}
}

void do_ClientRestart( CPC* ch, CNetMsg::SP& msg )
{
	GAMELOG << init( "CLIENT_RESTART", ch ) << end;

	{
		// Ŭ���̾�Ʈ�� restart MSG ����
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeExRestart(rmsg, 0);
		SEND_Q( rmsg, ch->m_desc );
	}
	//�̺����̼� ���� Ǯ��
	if(ch->m_evocationIndex > EVOCATION_NONE)
	{
		ch->Unevocation();
	}


#ifdef CAPTURE_THE_FLAG_10282021
			if (ch->m_inventory.FindByDBIndex(12272) != NULL && !ch->IsInPeaceZone(true))
			{
				CItem* pitem11272 = NULL;
				pitem11272 = ch->m_inventory.FindByDBIndex(12272, 0, 0);

				item_search_t vec_pvpflagitem;

				int sc = ch->m_inventory.searchItemByCondition(12272, 0, 0, vec_pvpflagitem);
				// make sure the user doesnt have more then he should of the item
				if (sc == 0 || sc < 1)
					return;
				//delete item from inventory user died
				ch->m_inventory.deleteItem(vec_pvpflagitem, 1);
				//check quest conditions 
				CQuest* pQuest = ch->m_questList.FindQuest(818);
			    if (pQuest && pQuest->GetQuestState() == QUEST_STATE_RUN)
			    {
				    ch->m_questList.SetQuestState(pQuest, QUEST_STATE_ABANDON);
				    {
				    	CNetMsg::SP rmsg(new CNetMsg);
					    QuestForceGiveUpMsg(rmsg, pQuest);
					    ch->m_questList.DelQuest(ch, pQuest);
					    SEND_Q(rmsg, ch->m_desc);
				    }
				ch->m_questList.DecreaseQuestComepleteCount();
			    }
				
				ch->m_bHasFlagItem = false;

				int npcindex = 1704;
				//make sure the npc isn't null (crash)
				CNPC* npc = gserver->m_npcProtoList.Create(npcindex, NULL);
				if (!npc)
					return;
				//grab the information for the mob from the dead player
				GET_X(npc) = GET_X(ch);
				GET_Z(npc) = GET_Z(ch);
				GET_YLAYER(npc) = GET_YLAYER(ch);
				GET_R(npc) = GetRandom(0, (int)(PI_2 * 10000)) / 10000;

				if (ch->m_pArea->GetAttr(GET_YLAYER(npc), GET_X(npc), GET_Z(npc)) & MATT_WALKABLE) {}


				npc->m_regenX = GET_X(npc);
				npc->m_regenY = GET_YLAYER(npc);
				npc->m_regenZ = GET_Z(npc);

				int cx, cz;
				ch->m_pArea->AddNPC(npc);
				ch->m_pArea->PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
				ch->m_pArea->CharToCell(npc, GET_YLAYER(npc), cx, cz);

				{
					CNetMsg::SP rmsg(new CNetMsg);
					AppearMsg(rmsg, npc, true);
					ch->m_pArea->SendToCell(rmsg, GET_YLAYER(npc), cx, cz);
				}

				{
					//annouce message to all with flag position
					CNetMsg::SP rmsg(new CNetMsg);
					SysMsgFlagDC(rmsg, ch->m_nick, ch->m_pos.m_x, ch->m_pos.m_z);
					PCManager::instance()->sendToAll(rmsg);
				}
			}
#endif

	if(ch->m_guildInfo != NULL && ch->m_guildInfo->guild())
	{
		CGuild* guild = ch->m_guildInfo->guild();
		if(guild->boss()->GetPC() == ch)
		{
			GuildBattleManager::instance()->delete_banish(guild->index());
			if( GuildBattleManager::instance()->cancel(guild->index()) == true)
			{
				guild->m_isUseTheStashAndSkill = true;

				CNetMsg::SP rmsg(new CNetMsg);
				ServerToServerPacket::makeGuildBattleStashLockOff(rmsg, guild->index());
				SEND_Q(rmsg, gserver->m_helper);
			}
		}

		if (guild->battleState() == GUILD_BATTLE_STATE_ING)
		{
			//����� ���� ó��
			GuildBattleManager::instance()->giveup(ch->m_index);
		}
	}

	ch->m_desc->returnToCharacterSelectMode();
}

void do_ExInitSSkill( CPC* ch, CNetMsg::SP& msg )
{
	if(!ch->InitSSkill())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		InitSSkillMsg(rmsg, MSG_EX_INIT_SSkill_ERROR_FAIL);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	ch->CalcStatus(true);

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeSSkillList(rmsg, ch);
		SEND_Q(rmsg, ch->m_desc);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		InitSSkillMsg(rmsg, MSG_EX_INIT_SSkill_ERROR_SUCCESS);
		SEND_Q(rmsg, ch->m_desc);
	}

	GAMELOG << init("INIT SSKILL", ch) << end;
}

void  do_NpcPortalScroll(CPC* ch, CNetMsg::SP& msg)
{
	if (ch == NULL || DEAD(ch))
		return ;

#ifdef CAPTURE_THE_FLAG_10282021
	if (ch->m_bHasFlagItem)
		return;
#endif

	int msgType = -1;
	int index = -1;
	static CLCString buf(MAX_MESSAGE_SIZE);
	RefMsg(msg) >> msgType;

	switch( msgType )
	{
	case MSG_NPC_PORTAL_GO:
	case MSG_NPC_PORTAL_LOCATION:
		RefMsg(msg) >> index;
		do_NpcportalScrollGoNPC(ch, index, msgType);
		break;
	}
	return;
}

void do_NpcportalScrollGoNPC(CPC* ch, int index, int msgType)
{
	CArea* area = NULL;

	if( ch && ch->m_pArea )
		area = ch->m_pArea;
	else
		return;

	int i, j;

	int sx = 0;
	int ex = area->m_size[0] - 1;
	int sz = 0;
	int ez = area->m_size[1] - 1;
	float retdist = GetDistance(0, 0, 0, area->m_size[0] * CELL_SIZE, area->m_size[1] * CELL_SIZE, 0);

	CCharacter* p;
	CNPC* npc;
	CNPC* ret = NULL;
	float dist;

	switch( msgType )
	{
	case MSG_NPC_PORTAL_GO:
		if( !ch->m_pArea->IsNpcPortalList_Npc( index ) )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			NpcPortalListErrorMsg(rmsg, MSG_NPC_PORTAL_ERROR_MOB);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
		break;
	case MSG_NPC_PORTAL_LOCATION:
		if( !ch->m_pArea->IsNpcPortalList_Mob( index ) )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			NpcPortalListErrorMsg(rmsg, MSG_NPC_PORTAL_ERROR_MOB);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}
		break;
	}

	// �ڽ� �ֺ�����
	for (i = sx; i <= ex; i++)
	{
		if (i < 0 || i >= area->m_size[0])
			continue ;

		for (j = sz; j <= ez; j++)
		{
			if (j < 0 || j >= area->m_size[1])
				continue ;

			// NPC�� ã��
			p = area->m_cell[i][j].m_listChar;

			while (p)
			{
				if (IS_NPC(p))
				{
					npc = TO_NPC(p);
					if ((index != -1 && npc->m_idNum == index))
					{
						// �Ÿ��� ���ؼ� ����� ������
						dist = GetDistance(ch, npc);
						if (dist < retdist)
						{
							retdist = dist;
							ret = npc;
						}
					}
				}
				p = p->m_pCellNext;
			}
		}
	}

	if (ret == NULL)
	{
		// �ش� ���Ͱ� �ʵ忡 ������ ������.
		CNetMsg::SP rmsg(new CNetMsg);
		NpcPortalListErrorMsg(rmsg, MSG_NPC_PORTAL_ERROR_MOB);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	switch( msgType )
	{
	case MSG_NPC_PORTAL_GO:
		// 10���� �̵��ϰ� �ϱ�
		ch->m_reqWarpType = IONCE_WARP_NPC_PORTAL_SCROLL;
		ch->m_reqWarpData = -1;
		ch->m_reqWarpTime = PULSE_WARPDELAY;
		ch->SetPlayerState(PLAYER_STATE_WARP);

		ch->m_Npc_Portal_x = GET_X(ret);
		ch->m_Npc_Portal_z = GET_Z(ret);
		ch->m_Npc_Portal_y = GET_YLAYER(ret);

		{
			// ��������� �˸���
			CNetMsg::SP rmsg(new CNetMsg);
			WarpStartMsg(rmsg, ch);
			ch->m_pArea->SendToCell(rmsg, ch, true);
		}
		//GoZone(ch, ch->m_pArea->m_zone->m_index, ch->m_pos.m_yLayer, GET_X(ret), GET_Z(ret)+1.0f);
		//GoTo(ch, GET_YLAYER(ret), GET_X(ret), GET_Z(ret)+1.0f, ch->m_pArea->GetHeight(GET_YLAYER(ret), GET_X(ret), GET_Z(ret)), GET_R(ch));

		{
			// GO_ZONE ȿ�� �޽��� ����
			CNetMsg::SP rmsg(new CNetMsg);
			EffectEtcMsg(rmsg, ch, MSG_EFFECT_ETC_GOZONE);
			area->SendToCell(rmsg, ch, true);
		}
		break;

	case MSG_NPC_PORTAL_LOCATION:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			rmsg->Init(MSG_EXTEND);
			RefMsg(rmsg) << MSG_EX_NPC_PORTAL_SCROLL;
			RefMsg(rmsg) << MSG_NPC_PORTAL_LOCATION;
			RefMsg(rmsg) << GET_X(ret);
			RefMsg(rmsg) << GET_Z(ret);
			SEND_Q(rmsg, ch->m_desc);
		}
		break;
	}
}

void do_ExRaidInfo(CPC* ch, CNetMsg::SP& msg)
{
	if (!ch || DEAD(ch))
		return;

	long subtype;
	msg->MoveFirst();
	RefMsg(msg) >> subtype;

	{
		// �ͼӵ� ���̵� ������ �˻��Ϸ� ���۷� ����.
		CNetMsg::SP rmsg(new CNetMsg);
		HelperRaidInfoMsg(rmsg, ch->m_index);
		SEND_Q(rmsg, gserver->m_helper);
	}
}


void do_SaveSettings(CPC* ch, CNetMsg::SP& msg)
{
    double ap, ai, as;
    RefMsg(msg)
        >> ap
        >> ai
		>> as;
        
    int autopickup = (static_cast<int>(ap));
    int autoigni = (static_cast<int>(ai));
    int autosell = (static_cast<int>(as));
        
    if (ch == NULL)
    {
        return;
    }
    else
    {
        ch->m_autopickup = autopickup;
        ch->m_autoigni = autoigni;
        ch->m_autosell = autosell;
        
        char update_character_query[MAX_MESSAGE_SIZE] = "";
        sprintf(update_character_query, "UPDATE t_characters SET a_autopickup = %d, a_autoigni = %d, a_autosell = %d WHERE a_index = %d", ch->m_autopickup, ch->m_autoigni, ch->m_autosell, ch->m_index);
        CDBCmd charUpd;
        charUpd.Init(&gserver->m_dbcharingame);
        charUpd.SetQuery(update_character_query);
        if (!charUpd.Update())
        {
            DBLOG << init("DB ERROR : Save Settings", ch)
                << mysql_error(charUpd.GetDbConn()) << delim
                << "INDEX" << delim << ch->m_index
                << end;
            CNetMsg::SP msg1(new CNetMsg);
			GAMELOG << init("Update Auto Pickup/Auto Ignition/Auto Sell") << MSG_EX_STRING_OUTPUT_WINDOW << "Error Settings!";
            SEND_Q(msg1, ch->m_desc);
            return;
        }
        
        CNetMsg::SP rmsg(new CNetMsg);
        UpdateClient::updateSettings(rmsg, ch->m_autopickup, ch->m_autoigni, ch->m_autosell);
        SEND_Q(rmsg, ch->m_desc);
        
        CNetMsg::SP msg1(new CNetMsg);
		GAMELOG << init("Update Auto Pickup/Ignition") << MSG_EX_STRING_OUTPUT_WINDOW << "Settings saved!";
        SEND_Q(msg1, ch->m_desc);
        return;
    }
}
// ����Ʈ ������ �ٽ� �޴� ���
void do_ExTakeAgainQuestItem(CPC* ch, CNetMsg::SP& msg)
{
	if (!ch || DEAD(ch))
		return;

	long subtype;

	msg->MoveFirst();
	RefMsg(msg) >> subtype;

	// �κ��丮�� �������� �����ϴ� �� Ȯ��
	if ( ch->m_inventory.FindByDBIndex(4659, 0, 0) )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		TakeAgainQuestItemMsg(rmsg, MSG_EX_TAKE_AGAIN_QUEST_ITEM_ERROR_ALREADY_EXIST);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// �κ��丮 ���� �˻�
	else if ( ch->m_inventory.getEmptyCount() < 1 )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		TakeAgainQuestItemMsg(rmsg, MSG_EX_TAKE_AGAIN_QUEST_ITEM_ERROR_FULL_INVENTORY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ����Ʈ�� �Ϸᰡ �ȵǾ� ������ ������ ���� �Ұ�
	bool questComplete = ch->m_questList.FindQuest(248, QUEST_STATE_DONE);
	if(!questComplete)
		return;

	CItem* pItem = gserver->m_itemProtoList.CreateItem(4659, -1, 0, 0, 1);

	if(pItem == NULL)
		return;

	if (ch->m_inventory.addItem(pItem) == false)
	{
		delete pItem;
		return;
	}

	{
		// �����ߴٴ� �޼��� ������
		CNetMsg::SP rmsg(new CNetMsg);
		TakeAgainQuestItemMsg(rmsg, MSG_EX_TAKE_AGAIN_QUEST_ITEM_SUCCESS);
		SEND_Q(rmsg, ch->m_desc);
	}
}

#ifdef LACARETTE_SYSTEM

void do_ExLacaretteSystem(CPC* ch, CNetMsg::SP& msg)
{
#ifdef LC_RUS
	return;
#endif // LC_RUS

	if( !ch )
		return;

	unsigned char sybType;
	RefMsg(msg) >> sybType;

	switch( sybType )
	{
	case MSG_EX_LACARETTE_TOKEN_READY_REQ:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ConnLacaretteTokenReadyMsg(rmsg, ch->m_desc->m_index, ch->m_index);
			SEND_Q(rmsg, gserver->m_connector);
			return;
		}
		break;
	case MSG_EX_LACARETTE_TOKEN_REQ:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ConnLacaretteTokenMsg(rmsg, ch->m_desc->m_index, ch->m_index);
			SEND_Q(rmsg, gserver->m_connector);
			return;
		}
		break;

	case MSG_EX_LACARETTE_RETTE_REQ:
		{
			int cosArrNum;
			int cosIndex;
			int tokenIndex;

			RefMsg(msg) >> cosArrNum
						>> cosIndex
						>> tokenIndex;

			CNetMsg::SP rmsg(new CNetMsg);
			ConnLacaretteRepeatMsg(rmsg, ch->m_desc->m_index, ch->m_index, cosArrNum, cosIndex, tokenIndex);
			SEND_Q(rmsg, gserver->m_connector);
			return;
		}
		break;

	case MSG_EX_LACARETTE_RESULT_REQ: // �������� ���� ������.
		{
			// ���� DB�� Ƚ�� ���� ��Ų��.
			int giveitemindex;
			RefMsg(msg) >> giveitemindex;

			CNetMsg::SP rmsg(new CNetMsg);
			ConnLacaretteRepeatAddMsg(rmsg ,ch->m_desc->m_index, ch->m_index, giveitemindex );
			SEND_Q(rmsg, gserver->m_connector);
		}
		break;

	case MSG_EX_LACARETTE_UI_REQ:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ConnLacaretteUIMsg(rmsg, ch->m_desc->m_index, ch->m_index, 0, 0, 0);
			SEND_Q(rmsg, gserver->m_connector);
			return;
		}
		break;
	case MSG_EX_LACARETTE_UI_COLSE:
		ch->m_lacaretteCosArrNum	= -1;
		ch->m_lacaretteItemArrNum	= -1;
		ch->m_lacaretteTokenArrNum	= -1;
		ch->m_lacaretteRepeat		= -1;
		break;
	}
}
#endif

void do_FuncAttendanceExp ( CPC* ch, CNetMsg::SP& msg )
{
	unsigned char thirdtype;

	pTypeThirdBase* pThird = reinterpret_cast<pTypeThirdBase*>(msg->m_buf);
	thirdtype = pThird->thirdType;

	switch( thirdtype )
	{
	case MSG_SUB_ATTENDANCE_CHECK_REQ:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::makeAttendanceCheckMsg(rmsg, ch->m_attendanceManager.getAccCount(), ch->m_nAttendance_exp);
			SEND_Q(rmsg, ch->m_desc);
		}
		break;
	case MSG_SUB_ATTENDANCE_REWARD_REQ:
		{
			ch->m_attendanceManager.reward();
		}
		break;
	case MSG_SUB_ATTENDANCE_ASSURE_CANCEL_OK_REQ:
		{
			//���� �ϰڴ�.
			ch->m_attendanceManager.assureOk();
		}
		break;
	}
}

#ifdef XTRAP
void do_FuncXtrap ( CPC* ch, CNetMsg::SP& msg )
{
	char subtype;

	RefMsg(msg) >> subtype;

	if( ch == NULL )
		return;

	switch( subtype )
	{
	case 0x002: //XTRAP_CMD_STEP_TWO
		{
			char msgbuffer[128];
			msg->Read( msgbuffer, 128 );
#ifdef XTRAP_DUMP
			char filename[128];
			sprintf( filename, "%d.xtrap.log" , ch->m_index );
			HexaDump4XTrap_Std( filename, msgbuffer, 128 , "Step3_Before" );
#endif // XTRAP_DUMP
			XTrap_CS_Step3( ch->m_xtrapSessionBuf, msgbuffer );
		}
		break;
	case 0x00f:	// XTRAP_MAP_FILE_CHANGE
		{
			FILE*	fp;
			fp = fopen("data/map1.cs3","rb");
			if( fp == NULL )
				return;

			fread( gserver->m_XTrapMap[0], XTRAP_CS4_BUFSIZE_MAP, 1 ,fp );
			fclose(fp);
		}
	}
}
#else
void do_FuncXtrap ( CPC* ch, CNetMsg::SP& msg )
{
	return;
}
#endif //XTRAP

void do_ExFuncTutorialRenewer(CPC* ch, CNetMsg::SP& msg)
{
	if (!ch)
		return;
if (ch->m_newtutoComplete == 1 || ch->m_inventory.FindByDBIndex(6085) != NULL) 
		return;
	GAMELOG << init("DANGEROUS USER: Title Hack", ch) << "NAME:" <<ch->m_nick << end; 
	CItem* pItem = gserver->m_itemProtoList.CreateItem(6085, -1, 0, 0, 1);
	if(pItem == NULL)
		return;

	if (ch->m_inventory.addItem(pItem))
	{
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::ItemUseMsg(rmsg, pItem->tab(), pItem->getInvenIndex(), pItem->getVIndex(), pItem->getDBIndex());
			do_Item(ch, rmsg);
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			tutorialrenewerMsg(rmsg, pItem->m_itemProto->getItemNum0());
			SEND_Q(rmsg, ch->m_desc);
		}

		ch->m_newtutoComplete = 1;
	}
	else
	{
		delete pItem;
		return;
	}
}

void do_ExFaceOff(CPC* ch, CNetMsg::SP& msg)
{
	unsigned char subtype;
#ifdef NPC_CHECK
	int npcIndex;
	CNPC *npc;
	RefMsg(msg) >> subtype
				>> npcIndex;
	npc = ch->m_pArea->FindProtoNPCInCell(ch, npcIndex, false, 2);
	if(!npc)
	{
		GAMELOG << init("STASH_KEEP FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
	if( !npc->IsFlag(NPC_RESETSTAT) )
	{
		GAMELOG << init("STASH_KEEP FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
#else
	RefMsg(msg) >> subtype;
#endif

	switch( subtype )
	{
	case MSG_EX_FACEOFF_UIOPEN_REQ:
		{
			if (ch->m_inventory.getEmptyCount() <= 0)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::ItemTakeoffMsg(rmsg, ResponseClient::WEAR_ERR_NOT_ENOUGH_INVEN);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}

			CItem * pItem = ch->m_wearInventory.wearItemInfo[WEARING_HELMET];
			if( pItem )
			{
				if (pItem->getWearPos() != WEARING_NONE)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					insideServer_do_Item_Wear_TakeOff(rmsg, pItem->getWearPos());
					do_Item(ch, rmsg);
				}
			}
			pItem = ch->m_wearInventory.wearItemInfo[COSTUME2_WEARING_HELMET];
			if( pItem )
			{
				if (pItem->m_itemProto->getItemFlag() & ITEM_FLAG_COSTUME2 && pItem->getWearPos() != WEARING_NONE)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					insideServer_do_Item_Costume(rmsg, pItem->getWearPos());
					do_Item(ch, rmsg);
				}
			}
		}
		break;
	case MSG_EX_FACEOFF_REQ:
		{
			unsigned char hairStyle, faceStyle;
			RefMsg(msg) >> hairStyle >> faceStyle;
			if(ch->m_hairstyle != hairStyle || ch->m_facestyle != faceStyle)
			{
				bool success_flag = false;
				CItem * pItem = NULL;

#ifdef PREMIUM_CHAR
				//XX - �����̾�ĳ���� : ���� ����� ������ ��� ���� ���� ����
				if (ch->m_premiumChar.isActive())
				{
					success_flag = true;
					pItem = NULL;
				}
				else
#endif
				{
					pItem = NULL;

					static const int needItem[2] = {7055, 5969}; // ���� ī��
					for(int i = 0; i < 2; i++)
					{
						pItem = ch->m_inventory.FindByDBIndex(needItem[i], 0, 0);
						if (pItem)
						{
							success_flag = true;
							break;
						}
					}
				}

				if (success_flag)
				{
					if (pItem)
						ch->m_inventory.decreaseItemCount(pItem, 1);

					if (hairStyle < 1 || hairStyle > 5)
						hairStyle = 1;
					if (faceStyle < 1 || faceStyle > 5)
						faceStyle = 1;	
					ch->m_hairstyle = hairStyle;
					ch->m_facestyle = faceStyle;

					{
						CNetMsg::SP rmsg(new CNetMsg);
						rmsg->Init(MSG_HELPER_COMMAND);
						RefMsg(rmsg) << MSG_HELPER_FACEOFF_REQ
									 << ch->m_index
									 << ch->m_hairstyle
									 << ch->m_facestyle;
						SEND_Q(rmsg, gserver->m_helper);
					}

					GAMELOG << init("FACE OFF", ch)
							<< "hairStyle : " << hairStyle << delim
							<< "faceStyle : " << faceStyle << end;

					{
						CNetMsg::SP rmsg(new CNetMsg);
						rmsg->Init(MSG_EXTEND);
						RefMsg(rmsg) << MSG_EX_FACEOFF
									 << (unsigned char) MSG_EX_FACEOFF_REP
									 << (unsigned char) MSG_EX_FACEOFF_ERROR_SUC
									 << (unsigned char)ch->m_hairstyle
									 << (unsigned char)ch->m_facestyle;
						RefMsg(rmsg) << ch->m_index;
						ch->m_pArea->SendToCell(rmsg, ch, true );
					}
					return;
				}

				{
					CNetMsg::SP rmsg(new CNetMsg);
					rmsg->Init(MSG_EXTEND);
					RefMsg(rmsg) << MSG_EX_FACEOFF
								 << (unsigned char) MSG_EX_FACEOFF_REP
								 << (unsigned char) MSG_EX_FACEOFF_ERROR_FAIL;
					SEND_Q(rmsg, ch->m_desc);
				}
			}
			else
			{
				CNetMsg::SP rmsg(new CNetMsg);
				rmsg->Init(MSG_EXTEND);
				RefMsg(rmsg) << MSG_EX_FACEOFF
							 << (unsigned char) MSG_EX_FACEOFF_REP
							 << (unsigned char) MSG_EX_FACEOFF_ERROR_PLZ_CHOISE;
				SEND_Q(rmsg, ch->m_desc);
			}
		}
		break;
	}
}

void do_ExLCBall( CPC* ch, CNetMsg::SP& msg )
{
	char type;
	int		coinIndex = 0;
	char	courseIndex = 0;

	RefMsg(msg) >> type ;
	RefMsg(msg) >> coinIndex >> courseIndex;

	switch( type )
	{
	case MSG_EX_LCBALL_INFO:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperLCBallinfoMsg( rmsg, ch->m_index, coinIndex, courseIndex );
			SEND_Q( rmsg, gserver->m_subHelper );
		}
		break;

	case MSG_EX_LCBALL_USE:
		{
			// �κ��˻�
			if( ch->m_inventory.getEmptyCount() < 1 ) // ����� ����
			{
				CNetMsg::SP rmsg(new CNetMsg);
				LCBallUseMsg( rmsg, 1, 0 );
				SEND_Q(rmsg, ch->m_desc );
				return;
			}
			// ����(��ū)�� �ִ���
			if (ch->m_inventory.FindByDBIndex(coinIndex) == NULL)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				LCBallUseMsg( rmsg, 2 , coinIndex );	// ������ �����ϴ�.
				SEND_Q(rmsg, ch->m_desc );
				return ;
			}
			if (DEAD(ch) || ch->m_exchange != NULL || ch->m_personalshop != NULL)//liquid lacaball
			{
				CNetMsg::SP rmsg(new CNetMsg);
				LCBallUseMsg(rmsg, 3, 0);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}
			{
				CNetMsg::SP rmsg(new CNetMsg);
				SubHelperLCBalluseMsg( rmsg, ch->m_index, coinIndex, courseIndex );
				SEND_Q( rmsg, gserver->m_subHelper );
			}
		}
		break;
	}
	return;
}



void do_ExRoyalRumble(CPC* ch, CNetMsg::SP& msg)
{
	// MSG_EXTEND
	// MSG_EX_ROYAL_RUMBLE
	// (uc)MSG_EX_ROYAL_RUMBLE_PLAYER_REQ
	unsigned char subtype;
	RefMsg(msg) >> subtype;
	switch(subtype)
	{
	case MSG_EX_ROYAL_RUMBLE_PLAYER_REQ:
		{
			// �������
			do_ExRoyalRumblePlayerReq(ch, msg);
		}
		break;
	case MSG_EX_ROYAL_RUMBLE_PLAYER_UNREGIST_REQ:
		{
			do_ExRoyalRumblePlayerUnRegReq(ch, msg);
		}
		break;
	case MSG_EX_ROYAL_RUMBLE_REWARD_REQ:
		{
			do_ExRoyalRumbleRewardReq(ch, msg);
		}
		break;
	case MSG_EX_ROYAL_RUMBLE_POINT_REQ:
		{
			do_ExRoyalRumblePointReq(ch, msg);
		}
		break;
	case MSG_EX_ROYAL_RUMBLE_TIME_REQ:
		{
			do_ExRoyalRumbleTimeReq(ch, msg);
		}
		break;
	case MSG_EX_ROYAL_RUMBLE_GO_ZONE:
		{
			do_ExRoyalRumbleGoZone(ch, msg);
		}
		break;
	}
}
void do_ExRoyalRumblePlayerReq(CPC* ch, CNetMsg::SP& msg)
{
	if(!ch)
		return ;
	int leveltype = 0;	// 0:rookie, 1:senior, 2:master, 3:other
	LONGLONG neednas = 0;
	int finditem = -1;
	bool bInspection = true;
	if(ch->m_level >= MIN_ROOKIE_LEVEL && ch->m_level <= MAX_ROOKIE_LEVEL)
	{
		leveltype = LEVEL_TYPE_ROOKIE;
		neednas = ROOKIE_REGIST_NEED_PRICE;		// �鸸
		finditem = ROOKIE_REGIST_ITEM;
	}
	else if(ch->m_level >= MIN_SENIOR_LEVEL && ch->m_level <= MAX_SENIOR_LEVEL)
	{
		leveltype = LEVEL_TYPE_SENIOR;
		neednas = SENIOR_REGIST_NEED_PRICE;		// õ��
		finditem = SENIOR_REGIST_ITEM;
	}
	else if(ch->m_level >= MIN_MASTER_LEVEL)
	{
		leveltype = LEVEL_TYPE_MASTER;
		neednas = MASTER_REGIST_NEED_PRICE;	// �Ͼ�
		finditem = MASTER_REGIST_ITEM;
	}
	else
		leveltype = -1;

	if(leveltype == -1)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleRegist(rmsg, 2);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	// �������� ã�Ƽ� ������ ���˻�� �κ� ���� �˻縦 ���Ѵ�.
	if(ch->m_inventory.FindByDBIndex(finditem, 0, 0))
	{
		bInspection = false;
	}

	if(bInspection && (ch->m_inventory.getMoney() < neednas))
	{
		// ���� �����ϴ�.
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleRegist(rmsg, 1);
		SEND_Q(rmsg, ch->m_desc);
		GAMELOG << init("ROYAL RUMBLE REGIST", ch) << "NO MONEY" << end;
		return ;
	}
	if(bInspection && ch->m_inventory.getEmptyCount() < 1) // �κ��丮�� ���� �� ������...
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysFullInventoryMsg(rmsg, 0);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	bool b = false;
	//b = gserver->m_RoyalRumble.GetRookiePlaying();
	//b = gserver->m_RoyalRumble.GetSeniorPlaying();
	//b = gserver->m_RoyalRumble.GetMasterPlaying();

	if( gserver->m_RoyalRumble.GetRookiePlaying() ||
			gserver->m_RoyalRumble.GetSeniorPlaying() ||
			gserver->m_RoyalRumble.GetMasterPlaying() )
	{
		b = true;
	}

	if(b)
	{
		// ���� leveltype���� ������̴ϱ� ��û�� �ȵ�.
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleRegist(rmsg, 2);
		SEND_Q(rmsg, ch->m_desc);
		GAMELOG << init("ROYAL RUMBLE REGIST", ch) << "GAME IS PLAYING CANNOT REGIST" << end;
		return ;
	}

	// �̹̽�û �ϼ̽��ϴ�.
	if(gserver->m_RoyalRumble.m_WGPlayerList.FindNode(ch->m_index))
	{
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleRegist(rmsg, 3);
		SEND_Q(rmsg, ch->m_desc);
		GAMELOG << init("ROYAL RUMBLE REGIST", ch) << "ALREADY REGIST" << end;
		return ;
	}

	CWGPlayer* pWGp = NULL;

	pWGp = new CWGPlayer(ZONE_ROYAL_RUMBLE, ch->m_index, leveltype);

	if(!pWGp)
		return ;

	gserver->m_RoyalRumble.m_WGPlayerList.AddNode(pWGp);

	if(bInspection)
	{
		// �������� �־��ش�.
		CItem* pItem = gserver->m_itemProtoList.CreateItem(finditem, -1, 0, 0, 1);
		if(pItem == NULL)
			return ;

		if (ch->m_inventory.addItem(pItem) == false)
		{
			delete pItem;

			// �κ��� �������� ������ ���� �Ұ�.
			CNetMsg::SP rmsg(new CNetMsg);
			SysFullInventoryMsg(rmsg, 0);
			SEND_Q(rmsg, ch->m_desc);
			return ;
		}

		{
			// ��û�� �޴� ���� ����
			if(ch->m_inventory.getMoney() >= neednas)
			{
				ch->m_inventory.decreaseMoney(neednas);
			}
			else
			{
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg(rmsg, MSG_SYS_NOT_ENOUGH_MONEY);
				SEND_Q(rmsg, ch->m_desc);
			}
			// ��û�� �޴� ���� ��
		}
	}

	{
		// ����� �Ϸ�Ǿ����ϴ�.
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleRegist(rmsg, 0);
		GAMELOG << init("ROYAL RUMBLE REGIST", ch) << "COMPLETE REGIST" << end;
		SEND_Q(rmsg, ch->m_desc);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleRegistMenu(rmsg, 0);
		SEND_Q(rmsg, ch->m_desc);
	}
}
void do_ExRoyalRumblePlayerUnRegReq(CPC* ch, CNetMsg::SP& msg)
{
	if(!ch)
		return ;
#ifdef NPC_CHECK
	int npcIndex;
	CNPC *npc;
	RefMsg(msg) >> npcIndex;
	npc = ch->m_pArea->FindProtoNPCInCell(ch, npcIndex, false, 2);
	if(!npc)
	{
		GAMELOG << init("RoyalRumblePlayerunReg FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
	if( !npc->IsFlag(NPC_QUEST) )
	{
		GAMELOG << init("RoyalRumblePlayerunReg FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
#endif
	// ��� �ð��ΰ�?
	if(!gserver->m_RoyalRumble.GetRoyalRumbleNotice())
	{
		//����� �� �ִ� �ð��� �ƴմϴ�.
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleUnRegist(rmsg, 1);
		SEND_Q(rmsg, ch->m_desc);
		GAMELOG << init("ROYAL RUMBLE UNREGIST", ch) << "CANNOT THIS TIME UNREGIST" << end;
		return ;
	}
	// ����� ���ܿ� �ֳ�?
	if(!gserver->m_RoyalRumble.m_WGPlayerList.FindNode(ch->m_index))
	{
		//����� ���ܿ� �����ϴ�.
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleUnRegist(rmsg, 2);
		SEND_Q(rmsg, ch->m_desc);
		GAMELOG << init("ROYAL RUMBLE UNREGIST", ch) << "NOT REGIST" << end;
		return ;
	}

	gserver->m_RoyalRumble.m_WGPlayerList.DelNode(ch->m_index);

	{
		// ��Ұ� �Ϸ�Ǿ����ϴ�.
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleUnRegist(rmsg, 0);
		GAMELOG << init("ROYAL RUMBLE UNREGIST", ch) << "COMPLETE UNREGIST" << end;
		SEND_Q(rmsg, ch->m_desc);
	}

	if(gserver->m_RoyalRumble.GetRoyalRumbleNotice())
	{
		if(gserver->m_subno == WAR_GROUND_CHANNEL)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			RoyalRumbleRegistMenu(rmsg, 1);
			SEND_Q(rmsg, ch->m_desc);
		}
	}
}
void do_ExRoyalRumbleRewardReq(CPC* ch, CNetMsg::SP& msg)
{
	// �����û
	if(!ch)
		return ;
#ifdef NPC_CHECK
	int npcIndex;
	CNPC *npc;
	RefMsg(msg) >> npcIndex;
	npc = ch->m_pArea->FindProtoNPCInCell(ch, npcIndex, false, 2);
	if(!npc)
	{
		GAMELOG << init("RoyalRumbleReward FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
	if( !npc->IsFlag(NPC_QUEST) )
	{
		GAMELOG << init("RoyalRumbleReward FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
#endif
	int nReward = 0;
	int LevelType = -1;
	if(gserver->m_RoyalRumble.GetWinner(LEVEL_TYPE_ROOKIE) == ch->m_index)
	{
		if(gserver->m_RoyalRumble.GetRewarded(LEVEL_TYPE_ROOKIE))
		{
			// �̹� �޾ҽ��ϴ�.
			CNetMsg::SP rmsg(new CNetMsg);
			RoyalRumbleReward(rmsg, 1);
			SEND_Q(rmsg, ch->m_desc);
			GAMELOG << init("ROYAL RUMBLE REWARD", ch) << "ALREADY REWARD" << end;
			return ;
		}
		// TODO: �����ʿ�
		nReward = 5974;
		LevelType = LEVEL_TYPE_ROOKIE;
	}
	else if(gserver->m_RoyalRumble.GetWinner(LEVEL_TYPE_SENIOR) == ch->m_index)
	{
		if(gserver->m_RoyalRumble.GetRewarded(LEVEL_TYPE_SENIOR))
		{
			// �̹� �޾ҽ��ϴ�.
			CNetMsg::SP rmsg(new CNetMsg);
			RoyalRumbleReward(rmsg, 1);
			SEND_Q(rmsg, ch->m_desc);
			GAMELOG << init("ROYAL RUMBLE REWARD", ch) << "ALREADY REWARD" << end;
			return ;
		}
		// TODO: �����ʿ�
		nReward = 6997;
		LevelType = LEVEL_TYPE_SENIOR;
	}
	else if(gserver->m_RoyalRumble.GetWinner(LEVEL_TYPE_MASTER) == ch->m_index)
	{
		if(gserver->m_RoyalRumble.GetRewarded(LEVEL_TYPE_MASTER))
		{
			// �̹� �޾ҽ��ϴ�.
			CNetMsg::SP rmsg(new CNetMsg);
			RoyalRumbleReward(rmsg, 1);
			SEND_Q(rmsg, ch->m_desc);
			GAMELOG << init("ROYAL RUMBLE REWARD", ch) << "ALREADY REWARD" << end;
			return ;
		}
		// TODO: �����ʿ�
		nReward = 6998;
		LevelType = LEVEL_TYPE_MASTER;
	}
	else
	{
		// ����� �ƴ�
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleReward(rmsg, 0);
		SEND_Q(rmsg, ch->m_desc);
		GAMELOG << init("ROYAL RUMBLE REWARD", ch) << "NOT WINNER" << end;
		return ;
	}

	// ������ ����
	if(ch->m_inventory.getEmptyCount() < 1)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysFullInventoryMsg(rmsg, 0);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
	CItem* pItem = gserver->m_itemProtoList.CreateItem(nReward, -1, 0, 0, 1);
	if(!pItem)
		return;

	if (ch->m_inventory.addItem(pItem))
	{
		gserver->m_RoyalRumble.SetRewarded(LevelType, ch);
	}
	else
	{
		delete pItem;
	}
}
void do_ExRoyalRumblePointReq(CPC* ch, CNetMsg::SP& msg)
{
#ifdef NPC_CHECK
	int npcIndex;
	CNPC *npc;
	RefMsg(msg) >> npcIndex;
	npc = ch->m_pArea->FindProtoNPCInCell(ch, npcIndex, false, 2);
	if(!npc)
	{
		GAMELOG << init("RoyalRumble PointReq FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
	if( !npc->IsFlag(NPC_QUEST) )
	{
		GAMELOG << init("RoyalRumble PointReq FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
#endif

	{
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleWarPoint(rmsg, ch->GetWarGroundPoint(), ch->GetWarGroundAccPoint());
		SEND_Q(rmsg, ch->m_desc);
	}
}

void do_ExRoyalRumbleTimeReq(CPC* ch, CNetMsg::SP& msg)
{
	bool b = false;
	//b = gserver->m_RoyalRumble.GetRookiePlaying();
	//b = gserver->m_RoyalRumble.GetSeniorPlaying();
	//b = gserver->m_RoyalRumble.GetMasterPlaying();

#ifdef NPC_CHECK
	int npcIndex;
	CNPC *npc;
	RefMsg(msg) >> npcIndex;
	npc = ch->m_pArea->FindProtoNPCInCell(ch, npcIndex, false, 2);
	if(!npc)
	{
		GAMELOG << init("RoyalRumble TimeReq FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
	if( !npc->IsFlag(NPC_QUEST) )
	{
		GAMELOG << init("RoyalRumble TimeReq FAIL: NOT EXIST NPC (Dangerous User)", ch) << end;
		return ;
	}
#endif

	if( gserver->m_RoyalRumble.GetRookiePlaying() ||
			gserver->m_RoyalRumble.GetSeniorPlaying() ||
			gserver->m_RoyalRumble.GetMasterPlaying() )
	{
		b = true;
	}
	if(gserver->m_RoyalRumble.GetRoyalRumbleTime() != 0)
	{
		b = true;
	}
	if(b)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleTimeReq(rmsg, -1);
		SEND_Q(rmsg, ch->m_desc);
	}
	else
	{
		int h = gserver->m_tRealSystemTime.tm_hour;
		int i;
		int nexttime = -1;
		for(i = 0; i < ROYAL_RUMBLE_SCHEDULE; i++)
		{
			if(gserver->m_RoyalRumble.m_RoyalRumbleTime[i] > h)
			{
				nexttime = gserver->m_RoyalRumble.m_RoyalRumbleTime[i];
				break;
			}
		}
		if(nexttime == -1)
			nexttime = gserver->m_RoyalRumble.m_RoyalRumbleTime[0];
		// m_RoyalRumbleTime ���� �ð� ������ �ϴٰ� 22�÷� �����Ǿ� ���۽ð��� ���ó��
		// �׷��� ���� �ð��� ������ 22�÷� ����. ���� ������ �ʿ��� �� ������ �ʿ���.
		nexttime = gserver->m_RoyalRumble.getStartHour();

		{
			CNetMsg::SP rmsg(new CNetMsg);
			RoyalRumbleTimeReq(rmsg, nexttime, gserver->m_RoyalRumble.getStartMinute());
			SEND_Q(rmsg, ch->m_desc);
		}
	}
}

void do_ExRoyalRumbleGoZone(CPC* ch, CNetMsg::SP& msg)
{
	int finditem;
	int r, c;
	// Ŭ���̾�Ʈ���� ������ �����Դ�.
	// �׷��� ������ ������ üũ �ϰ�..�������� ���ְ�..������ ���ش�......
	CWaitPlayer* wp = gserver->m_RoyalRumble.m_WaitPlayerList.GetNode(ch->m_index);
	if(wp == NULL)
	{
		// ��û�� ��Ͽ� ����.
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleNotfoundItem(rmsg);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}

	switch(wp->GetLevelType())
	{
	case LEVEL_TYPE_ROOKIE:
		{
			finditem = ROOKIE_REGIST_ITEM;
		}
		break;

	case LEVEL_TYPE_SENIOR:
		{
			finditem = SENIOR_REGIST_ITEM;
		}
		break;

	case LEVEL_TYPE_MASTER:
		{
			finditem = MASTER_REGIST_ITEM;
		}
		break;

	default:
		return;
		break;
	}
	CItem* pItem = ch->m_inventory.FindByDBIndex(finditem, 0, 0);
	if (pItem)
	{
		// �������� ã������ ����.
		ch->m_inventory.decreaseItemCount(pItem, 1);

		// ������ ���־����� ������ �����ش�.
		CNetMsg::SP rmsg(new CNetMsg);
		RequestClient::makeGoZone(rmsg, ZONE_ROYAL_RUMBLE, 0, -1);
		do_GoZone(ch, rmsg);
	}
	else
	{
		// �������� ������ �̵��� ���Ѵ�.
		CNetMsg::SP rmsg(new CNetMsg);
		RoyalRumbleNotfoundItem(rmsg);
		SEND_Q(rmsg, ch->m_desc);
		return ;
	}
}

#ifdef GAMIGO_CASH_AUTHENTICATION_CODE_USE
void do_ExCashAuthenticationCode(CPC* ch, CNetMsg::SP& msg)
{
	CLCString sql(1024);
	CLCString md5AuthCode;
	sql.Format("select MD5( CONCAT( UPPER('%s'),'%s') ) as md5AuthCode" , (const char*)ch->m_desc->m_idname, LOCAL_AUTHENTICATION_SECRETCODE );
	CDBCmd cmd;
	cmd.Init(&gserver->m_dbdata);
	cmd.SetQuery(sql);

	unsigned char bAuthCode = 1;

	if( !cmd.Open() || !cmd.MoveFirst() )
	{
		bAuthCode = 0;
		md5AuthCode ="FAIL";
	}
	else
	{
		cmd.GetRec("md5AuthCode", md5AuthCode);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		rmsg->Init(MSG_EXTEND);
		RefMsg(rmsg) << MSG_EX_CASH_AUTHENTICATION_CODE
					 << bAuthCode;
		if( bAuthCode == 1 )
		{
			RefMsg(rmsg) << ch->m_desc->m_idname
						 << (unsigned char) LCOAL_GAMIGO_GROUP_ID
						 << md5AuthCode;
		}
		SEND_Q(rmsg, ch->m_desc);
	}
}
#endif

#ifdef SYSTEM_TREASURE_MAP
#ifdef SYSTEM_TREASURE_MAP_GAMIGO
void do_ExTreasureMapKeyExchange(CPC* ch, CNetMsg::SP& msg)
{
	if( !ch )
		return;

	// �������� ���谡 100�� �ִ��� üũ����

	// �κ� �ڸ��� Ȯ������.
	if( ch->m_inventory.getEmptyCount() < 1 )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_FULL_INVENTORY);
		SEND_Q(rmsg, ch->m_desc );
		return;
	}

	item_search_t vec;
	int sc = ch->m_inventory.searchItemByCondition(TREASURE_KEY_ITEM_INDEX, 0, 0, vec);
	if (sc == 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		MsgTreaserMapKeyExchangeError(rmsg, MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_FAIL);
		SEND_Q(rmsg, ch->m_desc );
		return;
	}

	// ����Ȯ��
	int deleteCnt = 1000;
	if (sc < deleteCnt)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		MsgTreaserMapKeyExchangeError(rmsg, MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_COUNT);
		SEND_Q(rmsg, ch->m_desc );
		return;
	}

	// ������ �������� ��������.
	CItem * pAddItem = gserver->m_itemProtoList.CreateItem(TREASURE_KEY_ITEM_INDEX+1, -1, 0, 0, 1);
	if (pAddItem == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		MsgTreaserMapKeyExchangeError(rmsg, MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_FAIL);
		SEND_Q(rmsg, ch->m_desc );
		return;
	}

	// �������� �־�����.
	if (ch->m_inventory.addItem(pAddItem))
	{
		ch->m_inventory.deleteItem(vec, deleteCnt);
	}
	else
	{
		delete pAddItem;

		CNetMsg::SP rmsg(new CNetMsg);
		MsgTreaserMapKeyExchangeError(rmsg, MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_FAIL);
		SEND_Q(rmsg, ch->m_desc );

		return;
	}

	{
		// ���� �ߴ� ���� �޽����� ��������.
		CNetMsg::SP rmsg(new CNetMsg);
		MsgTreaserMapKeyExchangeError(rmsg, MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_SUC);
		SEND_Q(rmsg, ch->m_desc );
	}
}
#endif
#endif

void do_rankingSystem(CPC* ch, CNetMsg::SP& msg)
{
	if ( !ch )
		return;

	unsigned char msgType, type, subtype;
	CLCString name(20);

	RefMsg(msg) >> msgType >> type >> subtype;

	switch ( msgType )
	{
	case MSG_EX_RANKING_LIST:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperRankingListReqEx(rmsg, type, subtype, ch->m_index);
			SEND_Q(rmsg, gserver->m_subHelper);
		}
		break;
	case MSG_EX_RANKING_SEARCH:
		{
			RefMsg(msg) >> name;

			if(findPercentChar(name.GetBuffer()) != NULL)
				return ;

			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperRankingSearchReqEx(rmsg, type, subtype, ch->m_index, name);
			SEND_Q(rmsg, gserver->m_subHelper);
		}
		break;
	}
}

#ifdef REFORM_PK_PENALTY_201108 // 2011-08 PK �г�Ƽ ���� :: Ŭ�� ���� ��û �ߴ�.
void do_ExPKPeneltyReform(CPC* ch, CNetMsg::SP& msg)
{
	unsigned char subType;
	int rewardNum;

	RefMsg(msg) >> subType
				>> rewardNum;

	if( subType != MSG_EX_PKPENALTY_REFORM_REWARD_REQ )
		return;

	// Ŭ�� ��û�� ������ �������� �˻�.
	/*if( ch->GetPKPenaltyRewardNum() != rewardNum )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		MsgPKPenaltyRewardRep(rmsg, rewardNum, MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_FAIL );
		SEND_Q(rmsg, ch->m_desc);
		return;
	}*/

	// Ÿ��Ʋ ���� ���� Ȯ��
	if(ch->m_titleList.m_nCount >= MAX_TITLE_COUNT)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		MsgPKPenaltyRewardRep(rmsg, rewardNum, MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_COUNT);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// ���� Ÿ��Ʋ �ε��� ������
	int titleIndex = -1;
	titleIndex = 85 + rewardNum;

	// �̹� ������ �޾ҳ� Ȯ��
	if( ch->CheckPKPenaltyReward(rewardNum) || ch->m_titleList.Find(titleIndex) != NULL )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		MsgPKPenaltyRewardRep(rmsg, rewardNum, MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_ONCE);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// Ÿ��Ʋdl ���� �������� Ȯ��
	CTitleProto * titleProto = gserver->m_titleProtoList.FindProto(titleIndex);
	if( !titleProto )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		MsgPKPenaltyRewardRep(rmsg, rewardNum, MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_FAIL );
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	// DB ����� ���ؼ�...
	if( gserver->isRunSubHelper() )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		MsgSubHelperPKPenaltyRewardReq(rmsg, ch->m_index, rewardNum, titleProto->m_index, titleProto->m_time );
		SEND_Q(rmsg, gserver->m_subHelper);
		return;
	}
	else
	{
		// subhelper�� ���� �ʵǾ����� ������ ������.
		CNetMsg::SP rmsg(new CNetMsg);
		MsgPKPenaltyRewardRep(rmsg, rewardNum, MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_FAIL );
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
}

#endif // REFORM_PK_PENALTY_201108 // 2011-08 PK �г�Ƽ ����

#ifdef NOTICE_SYSTEM
void do_UserNotice(CPC* ch, CNetMsg::SP& msg)
{
	int _type;
	RefMsg(msg) >> _type;

	switch (_type)
	{
	case MSG_EX_USER_NOTICE_REG_REQ:
		{
			CLCString _contents(81);
			RefMsg(msg) >> _contents;

			if ( _contents.Length() <= 0 )
			{
				CNetMsg::SP rmsg(new CNetMsg);
				UserNoticeErrorMsg(rmsg, MSG_EX_USER_NOTICE_ERROR_LENGTH);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}

			// TODO :: ������ ������ �ִ��� �˻�
			const int _noticeItem = 7736;
			CItem* _item = ch->m_inventory.FindByDBIndex(_noticeItem, 0, 0);
			if (_item)
			{
				ch->m_inventory.decreaseItemCount(_item, 1);
			}
			else
			{
				CNetMsg::SP rmsg(new CNetMsg);
				UserNoticeErrorMsg(rmsg, MSG_EX_USER_NOTICE_ERROR_NOITEM);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}

			if ( gserver->isRunSubHelper() )
			{
				CNetMsg::SP rmsg(new CNetMsg);
				SubHelperUserNoticeRegMsg(rmsg, ch->m_index, ch->GetName(), _contents);
				SEND_Q(rmsg, gserver->m_subHelper);

				GAMELOG << init("[USER NOTICE] REGIST REQ") << delim
					<< ch->GetName() << delim
					<< _contents << end;
			}
		}
		break;
	}
}
#endif // NOTICE_SYSTEM


void do_serverTime(CPC *ch, CNetMsg::SP& msg)
{
	if (ch == NULL)
		return ;

	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_EXTEND);
	RefMsg(rmsg) << MSG_EX_SERVER_TIME
				 << (int)gserver->m_nowseconds;
	SEND_Q(rmsg, ch->m_desc);
}

void do_setTarget(CPC* ch, CNetMsg::SP& msg)
{
	if(ch == NULL)
		return;

	RequestClient::doSetTargetInfo *packet = reinterpret_cast<RequestClient::doSetTargetInfo*>(msg->m_buf);

	if(packet->charIndex <= -1)
		ch->m_targetPC = NULL;
	else
	{
		CPC* pc = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);
		if(pc == NULL)
		{
			// Check if this is an offline shop vendor
			CPersonalShop::SP offlineShop = gserver->GetOfflineShopByCharIndex(packet->charIndex);
			if (!offlineShop)
			{
				LOG_ERROR("HACKING? Invalid charIndex. targetIndex[%d]", packet->charIndex);
			}
		}

		ch->m_targetPC = pc;
	}
}

void do_noticeExtend(CPC* ch, CNetMsg::SP& rmsg)
{
	if(ch == NULL)
		return ;

	pTypeThirdBase* pThird = reinterpret_cast<pTypeThirdBase*>(rmsg->m_buf);
	int thirdtype = pThird->thirdType;

	switch(thirdtype)
	{
	case MSG_EX_NOTICE_LIST:
		Notice::instance()->SendNoticeList(ch->m_index, rmsg);
		break;
	}
}
//
void do_ExInventoryOption(CPC* ch, CNetMsg::SP& msg)
{
	int optionType;
	int isActive;
	RefMsg(msg) >> optionType 
				>> isActive;
	
	switch (optionType)
	{
		case INVENTORY_OPTION_INVENTORY_OPTION:
		{
			ch->m_inventory.m_inventoryOptions.SetOption(INVENTORY_OPTION_INVENTORY_OPTION, isActive > 0);

			if (isActive)
			{
				{
					CNetMsg::SP rmsg(new CNetMsg);
					WearingMsg(rmsg, ch, WEARING_HELMET, -1, 0);
					ch->m_pArea->SendToCell(rmsg, ch, false);
				}

				{
					CNetMsg::SP rmsg(new CNetMsg);
					CostumeWearingMsg(rmsg, ch, WEARING_HELMET, -1);
					ch->m_pArea->SendToCell(rmsg, ch, false);
				}
			}
			else
			{
				CItem* pHelmetItem = ch->m_wearInventory.getWearItem(WEARING_HELMET);
				CItem* pCosHelmetItem = ch->m_wearInventory.getCosWearItem(WEARING_HELMET);

				if (pHelmetItem)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					WearingMsg(rmsg, ch, WEARING_HELMET, pHelmetItem->getDBIndex(), pHelmetItem->getPlus());
					ch->m_pArea->SendToCell(rmsg, ch, false);
				} else {
					CNetMsg::SP rmsg(new CNetMsg);
					WearingMsg(rmsg, ch, WEARING_HELMET, -1, 0);
					ch->m_pArea->SendToCell(rmsg, ch, false);
				}

				if (pCosHelmetItem)
				{
					CNetMsg::SP rmsg(new CNetMsg);
					CostumeWearingMsg(rmsg, ch, WEARING_HELMET, pCosHelmetItem->getDBIndex());
					ch->m_pArea->SendToCell(rmsg, ch, false);
				} else {
					CNetMsg::SP rmsg(new CNetMsg);
					CostumeWearingMsg(rmsg, ch, WEARING_HELMET, -1);
					ch->m_pArea->SendToCell(rmsg, ch, false);
				}
			}

			{
				CNetMsg::SP rmsg(new CNetMsg);
				WearingInvisibleMsg(rmsg, ch, isActive);
				SEND_Q(rmsg, ch->m_desc);
			}

			ch->CalcStatus(true);

		}break;
	}
}
void do_ExGiveDonationTierInfo(CPC* ch, CNetMsg::SP& msg)
{
	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_EXTEND);
	RefMsg(rmsg) << (int)MSG_EX_GET_DONATION_TIER_INFO;
	const DonationEventInfo& eventInfo = gserver->m_donationTierManager.GetEventInfo();
	if (!eventInfo.IsActive)
	{
		RefMsg(rmsg) << (int)0;
		SEND_Q(rmsg, ch->m_desc);
		return;
	}
	gserver->m_donationTierManager.CalcProgress(ch);
	const DonationTierUserInfo info = gserver->m_donationTierManager.LoadUserInfo(ch);
	RefMsg(rmsg) << (int)1
		<< (LONGLONG)(eventInfo.FinishTime - time(0))
		<< info.Level
		<< info.Points + info.RemainPoints;
	int maxLevel = gserver->m_donationTierManager.GetMaxLevel();
	RefMsg(rmsg) << maxLevel + 1;
	DonationTierInfo* tierInfo;
	for (int i = 0; i <= maxLevel; i++)
	{
		tierInfo = gserver->m_donationTierManager.findTierInfo(i);
		if (!tierInfo) continue;
		RefMsg(rmsg) << i
			<< tierInfo->LevelUpPoints;
		std::vector<DonationTierGift>& gifts = tierInfo->Gifts;
		RefMsg(rmsg) << (int)gifts.size();
		BOOST_FOREACH(DonationTierGift & gift, gifts)
		{
			RefMsg(rmsg) << gift.ItemIndex
				<< gift.ItemCount;
		}
	}
	SEND_Q(rmsg, ch->m_desc);
}

void do_BattleWarfareMove(CPC* ch, CNetMsg::SP& msg)
{
	if (!gserver->m_BattleWarfare.IsActive())
		return;
		
	CZone* pBattleZone = gserver->FindZone(ZONE_WARFARE_BATTLE);
	if (pBattleZone == NULL)
		return;

	unsigned short old_map_attr = ch->GetMapAttr();
	int old_extra = ch->m_pZone->GetExtra(GET_X(ch), GET_Z(ch));

	bool old_war_zone = ch->isWarZone();

	GoZone(ch, ZONE_WARFARE_BATTLE, pBattleZone->m_zonePos[1][0],								// ylayer
	GetRandom(pBattleZone->m_zonePos[1][1], pBattleZone->m_zonePos[1][3]) / 2.0f,		// x
	GetRandom(pBattleZone->m_zonePos[1][2], pBattleZone->m_zonePos[1][4]) / 2.0f);	// z

	unsigned short new_map_attr = ch->GetMapAttr();
	int new_extra = ch->m_pZone->GetExtra(GET_X(ch), GET_Z(ch));

	bool new_war_zone = ch->isWarZone();

	if(old_war_zone != new_war_zone)
	{
		ch->CalcStatus(true);
	}

	if(old_map_attr != new_map_attr)
	{
		ch->m_bChangeStatus = true;
	}
}

#ifdef CLOUD_AUTO_QUEST_DELIVERY
void do_cloud_auto_quest(CPC* ch, CNetMsg::SP& rmsg)//Cloud auto quest
{
	if(ch == NULL)
		return;

	int questIndex;
	RefMsg(rmsg) >> questIndex;


	CQuest* pQuest = ch->m_questList.FindQuest(questIndex);

	if (pQuest == NULL)
		return;

	if (pQuest->GetQuestIndex() == 818)//bug fix tutorial
		return;

	if ( pQuest->GetQuestState() != QUEST_STATE_RUN)
	{// Quest FAIL Log
		GAMELOG << init("QUEST FAIL 1", ch)
			<< pQuest->GetQuestIndex()
			<< end;
		return ;
	}
	

	if (!pQuest->IsCompleted())
	{// Quest FAIL Log
		GAMELOG << init("QUEST FAIL 2", ch)
			<< pQuest->GetQuestIndex()
			<< end;
		return ;
	}

	if(ch->m_inventory.getEmptyCount() < 5)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_FULL_INVENTORY);
		SEND_Q(rmsg, ch->m_desc );
		return;
	}

	bool bSyndicate = ch->isSyndicate();
	if (questIndex == 684)
	{
		// ī�̷轺 ����
		if (!bSyndicate)
			ch->m_syndicateManager.joinSyndicate(SYNDICATE::eSYNDICATE_KAILUX);
	}
	else if (questIndex == 685)
	{
		// ���� ����
		if (!bSyndicate)
			ch->m_syndicateManager.joinSyndicate(SYNDICATE::eSYNDICATE_DEALERMOON);
	}

	const CQuestProto* pQuestProto = pQuest->GetQuestProto();
				
	bool boptPrize = false;
	int i;

	for (i=0; i < QUEST_MAX_OPTPRIZE; i++)
	{
		if (pQuest->GetQuestProto()->m_optPrizeType[i] != -1)
		{
			boptPrize = true;
		}
	}
	if (boptPrize == true)
	{// Quest FAIL Log
		GAMELOG << init("QUEST FAIL 3", ch)
			<< pQuest->GetQuestIndex()
			<< end;
		return ;
	}

	if (boptPrize == false)
	{
		//Quest Prize Log
		GAMELOG << init("CLOUD_AUTO_QUEST_PRIZE",  ch->m_nick, ch->m_nick)
			<< pQuest->GetQuestIndex() << delim
			<< QPRIZE_MONEY //<< delim
			<< end;

		ch->do_QuestAutoPrize(ch, pQuest);
	}//Cloud auto quest
}
#endif
//Val add auto pickup/igni buttons and shit
void do_SaveAutoOption(CPC* ch, CNetMsg::SP& msg)
{
	int pickupSelect;
	int igniSelect;
	int sellSelect;

	RefMsg(msg) >> pickupSelect >> igniSelect >> sellSelect;

	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init(MSG_AUTO_SETTING);

	if ( (pickupSelect < 0 && pickupSelect) || (igniSelect < 0 && igniSelect > 5) || (sellSelect < 0 && sellSelect))
	{
		RefMsg(rmsg) << 0;
	}
	else
	{
		ch->m_autopickup = pickupSelect;
		ch->m_autoigni = igniSelect;
		ch->m_autosell = sellSelect;
        // persist to DB so settings survive relog
        char update_character_query[MAX_MESSAGE_SIZE] = "";
        sprintf(update_character_query, "UPDATE t_characters SET a_autopickup = %d, a_autoigni = %d, a_autosell = %d WHERE a_index = %d", ch->m_autopickup, ch->m_autoigni, ch->m_autosell, ch->m_index);
        CDBCmd charUpd;
        charUpd.Init(&gserver->m_dbcharingame);
        charUpd.SetQuery(update_character_query);
        if (!charUpd.Update())
        {
            DBLOG << init("DB ERROR : Save Auto Options", ch)
                << mysql_error(charUpd.GetDbConn()) << delim
                << "INDEX" << delim << ch->m_index
                << end;
            RefMsg(rmsg) << 0;
        }
        else
        {
            RefMsg(rmsg) << 1;
        }

        // also send explicit settings update so client UI can refresh
        CNetMsg::SP upd(new CNetMsg);
        UpdateClient::updateSettings(upd, ch->m_autopickup, ch->m_autoigni, ch->m_autosell);
        SEND_Q(upd, ch->m_desc);
	}

	SEND_Q(rmsg, ch->m_desc);
}
#ifdef QUICK_PANEL
void do_Cloud_Usebuff(CPC* ch, CNetMsg::SP& rmsg)
{
	if (ch == NULL)
		return;

	int nSkillIndex;
	int nSkillLevel;
	RefMsg(rmsg) >> nSkillIndex;
	RefMsg(rmsg) >> nSkillLevel;

	//if(skillIndex == IMMOTAL_BUF || skillIndex == 1060 || skillIndex == 590 || skillIndex == 492 || skillIndex == 489 || skillIndex == 490 || skillIndex == 641 || skillIndex == 5046)
		//return;

	if (nSkillIndex == 5046 || nSkillIndex == 31 || nSkillIndex == 32 || nSkillIndex == 33 || nSkillIndex == 50 || nSkillIndex == 39
		|| nSkillIndex == 177 || nSkillIndex == 178 || nSkillIndex == 548 || nSkillIndex == 549 || nSkillIndex == 621 || nSkillIndex == 622
		|| nSkillIndex == 640 || nSkillIndex == 641 || nSkillIndex == 723 || nSkillIndex == 724 || nSkillIndex == 1117 || nSkillIndex == 317
		|| nSkillIndex == 318 || nSkillIndex == 320 || nSkillIndex == 321 || nSkillIndex == 293 || nSkillIndex == 294 || nSkillIndex == 300
		|| nSkillIndex == 301 || nSkillIndex == 131 || nSkillIndex == 191

		)
		return;

	if (ch->m_inventory.getMoney() > 0)
	{
		if (ch->m_inventory.getMoney() < 100000)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_SHORT_MONEY);
			SEND_Q(rmsg, ch->m_desc);
			return;
		}
		else if (ch->m_inventory.getMoney() >= 100000)
		{
			ch->m_inventory.decreaseMoney(100000);
		}
	}
	else
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_SHORT_MONEY);
		SEND_Q(rmsg, ch->m_desc);
		return;
	}

	CSkill* skill;

	if (ch->m_guildInfo && ch->m_guildInfo->guild()->m_activeSkillList.Find(nSkillIndex))
	{
		skill = ch->m_guildInfo->guild()->m_activeSkillList.Find(nSkillIndex);
		if (skill != NULL)
		{
			CSkill* pSkill = gserver->m_skillProtoList.Create(nSkillIndex, nSkillLevel);
			if (pSkill == NULL)
			{
				LOG_ERROR("not found skill[%d]. charIndex[%d]", nSkillIndex, ch->m_index);
				return;
			}

			if (!skill->IsReady(ch))
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeSkillErrorMsg(rmsg, MSG_SKILL_ERROR_NOTREADY, nSkillIndex, -1);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}


			if (ch->CanApplySkill(pSkill->m_proto, pSkill->m_proto->Level(pSkill->m_level)))
			{
				bool bApply = false;
				ApplySkill(ch, ch, pSkill, -1, bApply);

				skill->m_usetime = gserver->m_pulse;

			}
			else
				return;
		}
	}
	else if (ch->m_activeSkillList.Find(nSkillIndex))
	{
		skill = ch->m_activeSkillList.Find(nSkillIndex);
		if (skill != NULL)
		{
			CSkill* pSkill = gserver->m_skillProtoList.Create(nSkillIndex, nSkillLevel);
			if (pSkill == NULL)
			{
				LOG_ERROR("not found skill[%d]. charIndex[%d]", nSkillIndex, ch->m_index);
				return;
			}

			if (!skill->IsReady(ch))
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ResponseClient::makeSkillErrorMsg(rmsg, MSG_SKILL_ERROR_NOTREADY, nSkillIndex, -1);
				SEND_Q(rmsg, ch->m_desc);
				return;
			}


			if (ch->CanApplySkill(pSkill->m_proto, pSkill->m_proto->Level(pSkill->m_level)))
			{
				bool bApply = false;
				ApplySkill(ch, ch, pSkill, -1, bApply);

				skill->m_usetime = gserver->m_pulse;

			}
			else
				return;
		}
	}
	else
	{
		{
			return;
		}
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		EffectEtcMsg(rmsg, ch, MSG_EFFECT_ETC_FIRECRACKER);
		SEND_Q(rmsg, ch->m_desc);
	}
}

void do_Cloud_SaveItens(CPC* ch, CNetMsg::SP& rmsg)
{
	if (ch == NULL)
		return;

	int type;
	int idx;

	std::string CharInfo = "";
	std::string tmpString = "";
	CharInfo = "UPDATE t_cloud_quick_panel SET a_panel = ";

	for (int i = 0; i < 25; i++)
	{
		RefMsg(rmsg) >> type >> idx;

		tmpString += boost::str(boost::format("%d %d ") % type % idx);

		ch->m_QuickPanelBtnType[i] = type;
		ch->m_QuickPanelBtnIdx[i] = idx;
	}

	CharInfo += boost::str(boost::format("'%s'") % tmpString);

	char tbuffer[10] = { 0 };
	CharInfo += " WHERE a_index =";
	sprintf(tbuffer, "%d", ch->m_index);
	CharInfo += tbuffer;
	CharInfo += ";";

	DBManager::instance()->pushQuery(ch->m_index, CharInfo);

	GAMELOG << init("QUICK_PANEL_SAVED", ch)
		<< end;

	/*{
		CNetMsg::SP rmsg(new CNetMsg);
		EffectEtcMsg(rmsg, ch, MSG_EFFECT_ETC_FIRECRACKER);
		SEND_Q(rmsg, ch->m_desc);
	}*/

	ch->CalcStatus(true);
}
#endif