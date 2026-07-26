#include <boost/format.hpp>
#include "stdhdrs.h"

#include "Log.h"
#include "Exp.h"
#include "Server.h"
#include "CmdMsg.h"
#include "doFunc.h"
#include "../ShareLib/DBCmd.h"
//#include "RewardEventItem.h"
#include "DBManager.h"
#include "../ShareLib/packetType/ptype_express_system.h"
#include "../ShareLib/packetType/ptype_tradeAgent_system.h"
#include "../ShareLib/packetType/ptype_old_do_item.h"
#include "../ShareLib/packetType/ptype_server_to_server.h"
#include "../ShareLib/packetType/ptype_old_do_title.h"
#include "../ShareLib/packetType/ptype_mail_box.h"

// Definietion
void ProcSubHelperTradeAgentErrorRep( CNetMsg::SP& msg );
void ProcSubHelperTradeAgentRegListRep( CNetMsg::SP& msg);
void ProcSubHelperTradeAgentRegRep( CNetMsg::SP& msg);
void ProcSubHelperTradeAgentRegCancelRep( CNetMsg::SP& msg);
void ProcSubHelperTradeAgentSearchRep( CNetMsg::SP& msg);
void ProcSubHelperTradeAgentBuyRep( CNetMsg::SP& msg);
void ProcSubHelperTradeAgentLikeListRep( CNetMsg::SP& msg);
void ProcSubHelperTradeAgentLikeRegRep( CNetMsg::SP& msg);
void ProcSubHelperTradeAgentLikeCancelRep( CNetMsg::SP& msg);
void ProcSubHelperTitleSystemInsertTitleRep(CNetMsg::SP& msg);
void ProcSubHelperTitleSystemDisableRep(CNetMsg::SP& msg);
void ProcSubHelperTitleSystemDeleteRep(CNetMsg::SP& msg);
// [selo: 101105] ���� �ð� ���� ����
void ProcSubHelperTitleSystemForceChangeTime(CNetMsg::SP& msg);

void ProcSubHelperLCBallinfo( CNetMsg::SP& msg);
void ProcSubHelperLCBalluse( CNetMsg::SP& msg);
void ProcSubHelperLCBall_sucess( CNetMsg::SP& msg);

void ProcSubHelperRakingList(CNetMsg::SP& msg);
void ProcSubHelperRankingSearch(CNetMsg::SP& msg);
void ProcSubHelperRankingRefresh(CNetMsg::SP& msg);
void ProcSubHelperRankingError(CNetMsg::SP& msg);

#ifdef REFORM_PK_PENALTY_201108 // 2011-08 PK �г�Ƽ ����
void ProcSubHelperPKPenaltyReformRep(CNetMsg::SP& msg);
void ProcSubHelperPKPenaltyReformRewardInfoRep(CPC* pc, CNetMsg::SP& msg);
void ProcSubHelperPKPenaltyReformRewardRep(CPC* pc, CNetMsg::SP& msg);
#endif

#ifdef NOTICE_SYSTEM
void ProcSubHelperNoticeSystem(CNetMsg::SP& msg);
void ProcSubHelperNoticeSystemRegRep(CNetMsg::SP& msg);
void ProcSubHelperUserNoticePrint(CNetMsg::SP& msg);
#endif // NOTICE_SYSTEM

void ProcSubHelperMailBoxError(CNetMsg::SP& msg);
void ProcSubHelperMailBoxList(CNetMsg::SP& msg);
void ProcSubHelperMailBoxDelete(CNetMsg::SP& msg);
void ProcSubHelperMailBoxDeleteAll(CNetMsg::SP& msg);
void ProcSubHelperMailBoxOpenLetter(CNetMsg::SP& msg);
void ProcSubHelperMailBoxCollectLetter(CNetMsg::SP& msg);
void ProcSubHelperMailBoxSendLetter(CNetMsg::SP& msg);
void ProcSubHelperMailBoxUpdateStatus(CNetMsg::SP& msg);
void ProcSubHelperExtCharSlotItemUseRep(CNetMsg::SP& msg);
void ProcSubHelperUpdateDonationEventStatus(CNetMsg::SP& msg);
void ProcSubHelperUpdateDonationEventReward(CNetMsg::SP& msg);

extern void ProcSubHelperReservedGMCommand(CNetMsg::SP& msg);

extern float g_TradeAgent_Fee;
extern int g_TradeAgent_Deposit;

// Command
void CServer::ProcessSubHelperMessage(CNetMsg::SP& msg)
{
	msg->MoveFirst();

	switch (msg->m_mtype)
	{
	case MSG_TRADEAGENT:
		{
			ResponseClient::TradeAgentSystemList* packet = reinterpret_cast<ResponseClient::TradeAgentSystemList*>(msg->m_buf);
			
			int subtype = packet->subType;			
			//LOG_INFO("DEBUG_FUNC : START : type : %d, subtype : %d", msg->m_mtype, subtype);
			
			switch(packet->subType)
			{
			case MSG_TRADEAGENT_LIST:
				ProcSubHelperTradeAgentSearchRep(msg);
				break;
			case MSG_TRADEAGENT_REG_LIST:
				ProcSubHelperTradeAgentRegListRep(msg);
				break;
			case MSG_TRADEAGENT_REG:
				ProcSubHelperTradeAgentRegRep(msg);
				break;
			case MSG_TRADEAGENT_REG_CANCEL:
				ProcSubHelperTradeAgentRegCancelRep(msg);
				break;
			case MSG_TRADEAGENT_BUY:
				ProcSubHelperTradeAgentBuyRep(msg);
				break;
			case MSG_TRADEAGENT_LIKE_LIST:
				ProcSubHelperTradeAgentLikeListRep(msg);
				break;
			case MSG_TRADEAGENT_LIKE_REG:
				ProcSubHelperTradeAgentLikeRegRep(msg);
				break;
			case MSG_TRADEAGENT_LIKE_CANCEL:
				ProcSubHelperTradeAgentLikeCancelRep(msg);
				break;
			case MSG_TRADEAGENT_ERROR:
				ProcSubHelperTradeAgentErrorRep(msg);
				break;
			case MSG_TRADEAGENT_AFTER_SELL:
				{
					ResponseClient::TradeAgentAfterSell* packet = reinterpret_cast<ResponseClient::TradeAgentAfterSell*>(msg->m_buf);
					CPC* ch = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);
					if (ch)
					{
						SEND_Q(msg, ch->m_desc);
					}
				}
				break;
			case MSG_TRADEAGENT_AFTER_RETURNED:
				{
					ResponseClient::TradeAgentAfterReturned* packet = reinterpret_cast<ResponseClient::TradeAgentAfterReturned*>(msg->m_buf);
					CPC* ch = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);
					if (ch)
					{
						SEND_Q(msg, ch->m_desc);
					}
				}
				break;
			case MSG_TRADEAGENT_CHANGE_FEE:
				{
					ResponseClient::TradeAgentChangeFee* packet = reinterpret_cast<ResponseClient::TradeAgentChangeFee*>(msg->m_buf);
					g_TradeAgent_Fee = packet->fee;

					PCManager::instance()->sendToAll(msg);
				}
				break;
			case MSG_TRADEAGENT_CHANGE_DEPOSIT:
				{
					ResponseClient::TradeAgentChangeDeposit* packet = reinterpret_cast<ResponseClient::TradeAgentChangeDeposit*>(msg->m_buf);
					g_TradeAgent_Deposit = packet->deposit;

					PCManager::instance()->sendToAll(msg);
				}
				break;
			case MSG_TRADEAGENT_RETURN_NAS:
				{
					ResponseClient::TradeAgentReturnMoney* packet = reinterpret_cast<ResponseClient::TradeAgentReturnMoney*>(msg->m_buf);
					CPC* pc = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);
					if(pc == NULL)
					{
						std::string tstr = boost::str(boost::format(
														  "TradeAgent Return Nas - Not Found char : charIndex : %1% : nas : %2%") % packet->charIndex % packet->nas);
						LOG_INFO(tstr.c_str());
					}
					else
					{
						pc->m_inventory.increaseMoney(packet->nas);

						std::string tstr = boost::str(boost::format(
														  "TradeAgent Return Nas - OK : charIndex : %1% : nas : %2%") % packet->charIndex % packet->nas);
						LOG_INFO(tstr.c_str());
					}
				}
			}
			//LOG_INFO("DEBUG_FUNC : END : type : %d, subtype : %d", msg->m_mtype, subtype);
		}
		break;

	case MSG_MAIL_BOX:
	{
		pTypeBase* packet = reinterpret_cast<pTypeBase*>(msg->m_buf);
		switch (packet->subType)
		{
		case MSG_SUB_MAILBOX_LIST_FINISH:
			ProcSubHelperMailBoxList(msg);
			break;
		case MSG_SUB_MAILBOX_DELETE:
			ProcSubHelperMailBoxDelete(msg);
			break;
		case MSG_SUB_MAILBOX_DELETE_ALL:
			ProcSubHelperMailBoxDeleteAll(msg);
			break;
		case MSG_SUB_MAILBOX_ERROR:
			ProcSubHelperMailBoxError(msg);
			break;
		case MSG_SUB_MAILBOX_OPEN_LETTER:
			ProcSubHelperMailBoxOpenLetter(msg);
			break;
		case MSG_SUB_MAILBOX_LETTER_COLLECT:
			ProcSubHelperMailBoxCollectLetter(msg);
			break;
		case MSG_SUB_MAILBOX_SEND_LETTER:
			ProcSubHelperMailBoxSendLetter(msg);
			break;
		case MSG_SUB_MAILBOX_UPDATE_STATUS:
			ProcSubHelperMailBoxUpdateStatus(msg);
			break;
		}
	}break;
	case MSG_RESERVED_GM_COMMAND:
		//LOG_INFO("DEBUG_FUNC : START : type : %d", msg->m_mtype);
		ProcSubHelperReservedGMCommand(msg);
		//LOG_INFO("DEBUG_FUNC : END : type : %d", msg->m_mtype);
		break;

	case MSG_EXPRESS_SYSTEM:
		{
			pTypeBase* pBase = reinterpret_cast<pTypeBase*>(msg->m_buf);
			
			int subtype = pBase->subType;
			//LOG_INFO("DEBUG_FUNC : START : type : %d, subtype : %d", msg->m_mtype, subtype);
			
			switch (pBase->subType)
			{
			case MSG_SUB_EXPRESS_ONE_USER:
				{
					RequestGMTool::sendItemToOneUser* packet = reinterpret_cast<RequestGMTool::sendItemToOneUser*>(msg->m_buf);
					CPC* ch = PCManager::instance()->getPlayerByCharIndex(packet->char_index);
					if (ch == NULL)
						return;

					DBManager::instance()->PushExpressExist(ch->m_desc, packet->send_type);
				}
				break;

			default:
				LOG_ERROR("Express system : invalid subtype[%d]", pBase->subType);
				break;
			}
			//LOG_INFO("DEBUG_FUNC : END : type : %d, subtype : %d", msg->m_mtype, subtype);
		}
		break;

	case MSG_SUBHELPER_COMMAND :
		{
			int subtype;
			RefMsg(msg) >> subtype;
			//LOG_INFO("DEBUG_FUNC : START : type : %d, subtype : %d", msg->m_mtype, subtype);
			switch (subtype)
			{
			case MSG_SUBHELPER_TITLESYSTEM_INSERT_TITLE_REP:
				ProcSubHelperTitleSystemInsertTitleRep(msg);
				break;
			case MSG_SUBHELPER_TITLESYSTEM_CHECK_EXPIRE_TITLE_REP:
				ProcSubHelperTitleSystemDisableRep(msg); // ȣĪ ����Ʈ ���� �ð� Ȯ�� �� disable��.
				break;
			case MSG_SUBHELPER_TITLE_SYSTEM_TITLE_DELETE_REP:
				ProcSubHelperTitleSystemDeleteRep(msg); // ����ڰ� ���������� �Ҷ� disable��.
				break;
			case MSG_SUBHELPER_TITLE_SYSTEM_FORCE_CHANGE_TIME:
				ProcSubHelperTitleSystemForceChangeTime(msg);	// [selo: 101105] ���� �ð� ���� ����
				break;
			case MSG_SUBHELPER_LCBALL_INFO:
				ProcSubHelperLCBallinfo( msg );
				break;
			case MSG_SUBHELPER_LCBALL_USE:
				ProcSubHelperLCBalluse( msg );
				break;
			case MSG_SUBHELPER_LCBALL_USE_SUCCESS:
				ProcSubHelperLCBall_sucess( msg );
				break;
			case MSG_SUBHELPER_RANKING_EX_LIST:
				ProcSubHelperRakingList(msg);
				break;
			case MSG_SUBHELPER_RANKING_EX_SEARCH:
				ProcSubHelperRankingSearch(msg);
				break;
			case MSG_SUBHELPER_RANKING_EX_REFRESH:
				ProcSubHelperRankingRefresh(msg);
				break;
			case MSG_SUBHELPER_RANKING_EX_ERROR:
				ProcSubHelperRankingError(msg);
				break;
#ifdef REFORM_PK_PENALTY_201108 // 2011-08 PK �г�Ƽ ����
			case MSG_SUBHELPER_PKPENALTY_REFORM:
				ProcSubHelperPKPenaltyReformRep(msg);
				break;
#endif
			case MSG_SUBHELPER_EXT_CHAR_SLOT_ITEM_USE_REP:
				ProcSubHelperExtCharSlotItemUseRep(msg);
				break;
			case MSG_SUBHELPER_DONATION_EVENT_UPDATE_STATUS:
				ProcSubHelperUpdateDonationEventStatus(msg);
				break;
			case MSG_SUBHELPER_DONATION_EVENT_UPDATE_REWARD:
				ProcSubHelperUpdateDonationEventReward(msg);
				break;
			default:
				break;
			}
			//LOG_INFO("DEBUG_FUNC : END : type : %d, subtype : %d", msg->m_mtype, subtype);
		}
		break;
#ifdef NOTICE_SYSTEM
	case MSG_SUBHELPER_NOTICE:
		{
			//LOG_INFO("DEBUG_FUNC : START : type : %d", msg->m_mtype);
			ProcSubHelperNoticeSystem(msg);
			//LOG_INFO("DEBUG_FUNC : END : type : %d", msg->m_mtype);
		}
		break;
#endif // NOTICE_SYSTEM

	default:
		break;
	}
}

// Description
//���� �޼���
void ProcSubHelperTradeAgentErrorRep( CNetMsg::SP& msg )
{
	ResponseClient::TradeAgentSystemError *p = reinterpret_cast<ResponseClient::TradeAgentSystemError*>(msg->m_buf);
	CPC* pChar = PCManager::instance()->getPlayerByCharIndex(p->charIndex);
	if( pChar == NULL)
		return;

	SEND_Q(msg, pChar->m_desc);
}

void ProcSubHelperTradeAgentRegListRep( CNetMsg::SP& msg )
{
	ResponseClient::TradeAgentSystemRegList *p = reinterpret_cast<ResponseClient::TradeAgentSystemRegList*>(msg->m_buf);
	CPC* pChar = PCManager::instance()->getPlayerByCharIndex(p->charIndex);

	if(pChar == NULL)
		return;

	pChar->m_tradeAgentRegCount = p->count;	//���� ����� ������ ������ ���� ������ �ñ�ÿ� �� ó�� �˻��ϱ� ���ؼ�

	SEND_Q(msg, pChar->m_desc);
}

//���
void ProcSubHelperTradeAgentRegRep( CNetMsg::SP& msg )
{
	ResponseClient::TradeAgentSystemRegWithServer *sp = reinterpret_cast<ResponseClient::TradeAgentSystemRegWithServer*>(msg->m_buf);
	CPC* pChar = PCManager::instance()->getPlayerByCharIndex(sp->charIndex);

	if( pChar == NULL)
	{
		GAMELOG << init("TRADE AGENT REGIST") << delim
				<< "not found user. char index" << delim
				<< sp->charIndex << end;
		return;
	}

	GAMELOG << init("TRADE AGENT REGIST",  pChar)
			<< " CHAR INDEX : "	<< pChar->m_index << delim
			<< " ITEM INDEX : "  << sp->itemIndex << delim
			<< " ITEM SERIAL: "  << sp->serial << delim
			<< " ITEM COUNT : "  << sp->quantity << delim
			<< " TOTAL MONEY: "  << sp->TotalMoney << delim
			<< " GUARANTY:"  << sp->Guarantee << end;

	pChar->m_bTradeAgentRegIng = false;

	//�ŷ����� ��Ŷ ����
	msg->setSize(sizeof(ResponseClient::TradeAgentSystemReg));
	SEND_Q(msg, pChar->m_desc);
}

//��� ���
void ProcSubHelperTradeAgentRegCancelRep( CNetMsg::SP& msg )
{
	ResponseClient::TradeAgentSystemRegCancelWithServer *sp = reinterpret_cast<ResponseClient::TradeAgentSystemRegCancelWithServer*>(msg->m_buf);
	CPC* pChar = PCManager::instance()->getPlayerByCharIndex(sp->charIndex);

	if(pChar == NULL)
	{
		GAMELOG << init("TRADE AGENT REGIST CANCEL") << delim
				<< "not found user. char index" << delim
				<< sp->charIndex << end;
		return;
	}

	GAMELOG << init("TRADE AGENT REGIST CANCEL", pChar )
			<< " CHAR INDEX: " << pChar->m_index << delim
			<< "ITEM INDEX : " << sp->itemIndex << delim
			<< "ITEM SERIAL: " << sp->serial << delim
			<< "ITEM COUNT : " << sp->itemCount
			<< end;

	msg->setSize(sizeof(ResponseClient::TradeAgentSystemRegCancel));
	SEND_Q(msg, pChar->m_desc);
}

//��ȸ
void ProcSubHelperTradeAgentSearchRep( CNetMsg::SP& msg )
{
	ResponseClient::TradeAgentSystemList* packet = reinterpret_cast<ResponseClient::TradeAgentSystemList*>(msg->m_buf);
	CPC* pChar = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);
	if (pChar == NULL)
		return;

	//ĳ������ �� ����Ʈ�� �����ϱ�.
	pChar->m_tradeAgentViewMap.clear();
	for( int i = 0; i< packet->count; i++)
	{
		pChar->m_tradeAgentViewMap.insert(std::pair<int, GoldType_t>(packet->list[i].index, packet->list[i].nas));
	}

	//���� ���� �� �ϰ����� �޾ƿ� ��Ŷ �״�� ����
	SEND_Q(msg, pChar->m_desc);
}

//����
void ProcSubHelperTradeAgentBuyRep( CNetMsg::SP& msg )
{
	ResponseClient::TradeAgentSystemBuyWithServer* sp = reinterpret_cast<ResponseClient::TradeAgentSystemBuyWithServer*>(msg->m_buf);
	CPC* pChar = PCManager::instance()->getPlayerByCharIndex(sp->charIndex);

	if (pChar == NULL)
	{
		GAMELOG << init("TRADE AGENT ITEM BUY") << delim
				<< "not found user. char index" << delim
				<< sp->charIndex << delim
				<< "Need Decrease Money" << delim
				<< sp->needNas << end;

		std::string query = boost::str(boost::format("update t_characters set a_nas = a_nas - %1% where a_index = %2%") % sp->needNas % sp->charIndex);
		DBManager::instance()->pushQuery(0, query);
		return;
	}

	pChar->m_inventory.sendMoneyInfo();

	GAMELOG << init("TRADE AGENT ITEM BUY", pChar )
			<< " CHAR INDEX: " << pChar->m_index << delim
			<< " ITEM_INDEX : " << sp->itemIndex << delim
			<< " ITEM_SERIAL : " << sp->itemSerial << delim
			<< " ITEM_COUNT : " << sp->itemCount << delim
			<< " ITEM_PRICE : " << sp->itemPrice << delim
			<< " SELLER : " << sp->sellerName
			<< end;

	msg->setSize(sizeof(ResponseClient::TradeAgentSystemBuy));
	SEND_Q(msg, pChar->m_desc);
}

void ProcSubHelperTradeAgentLikeListRep( CNetMsg::SP& msg)
{
	ResponseClient::TradeAgentSystemLikeList *p = reinterpret_cast<ResponseClient::TradeAgentSystemLikeList*>(msg->m_buf);
	CPC* pChar = PCManager::instance()->getPlayerByCharIndex(p->charIndex);

	if(pChar == NULL)
		return;

	//ĳ������ �� ����Ʈ�� �����ϱ�.
	pChar->m_tradeAgentViewMap2.clear();
	for( int i = 0; i< p->count; i++)
	{
		pChar->m_tradeAgentViewMap2.insert(std::pair<int, GoldType_t>(p->list[i].index, p->list[i].nas));
	}

	SEND_Q(msg, pChar->m_desc);
}
void ProcSubHelperTradeAgentLikeRegRep( CNetMsg::SP& msg)
{
	ResponseClient::TradeAgentSystemLikeReg *p = reinterpret_cast<ResponseClient::TradeAgentSystemLikeReg*>(msg->m_buf);
	CPC* pChar = PCManager::instance()->getPlayerByCharIndex(p->charIndex);

	if(pChar == NULL)
		return;

	SEND_Q(msg, pChar->m_desc);
}
void ProcSubHelperTradeAgentLikeCancelRep( CNetMsg::SP& msg)
{
	ResponseClient::TradeAgentSystemLikeCancel *p = reinterpret_cast<ResponseClient::TradeAgentSystemLikeCancel*>(msg->m_buf);
	CPC* pChar = PCManager::instance()->getPlayerByCharIndex(p->charIndex);

	if(pChar == NULL)
		return;

	SEND_Q(msg, pChar->m_desc);
}

void ProcSubHelperTitleSystemInsertTitleRep(CNetMsg::SP& msg)
{
	int char_index = 0;
	int title_index = 0;
	int endtime = -1;
	int errortype = 0;
	int tab, invenIndex;
	CPC* ch;
	CTitle* title;
	CItem* item;
	CLCString serial;
	int custom_title_index;

	RefMsg(msg) >> char_index >> title_index >> endtime >> errortype >> tab >> invenIndex >> serial >> custom_title_index;

	if( errortype == 0 ) // DB insert error
		return ;

	else if(errortype == 1)
	{
		ch = PCManager::instance()->getPlayerByCharIndex(char_index);
		if(ch == NULL)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperTitleSystemTitleDelReq(rmsg, char_index, title_index, custom_title_index);
			SEND_Q(rmsg, gserver->m_subHelper);

			return ;
		}
		title = gserver->m_titleProtoList.Create(title_index, endtime);

		if(title == NULL)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperTitleSystemTitleDelReq(rmsg, char_index, title_index, custom_title_index);
			SEND_Q(rmsg, gserver->m_subHelper);

			return ;
		}
		
		title->m_custom_title_index = custom_title_index;
		
		item = ch->m_inventory.getItem(tab, invenIndex);

		if(item == NULL)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperTitleSystemTitleDelReq(rmsg, char_index, title_index, custom_title_index);
			SEND_Q(rmsg, gserver->m_subHelper);

			return ;
		}

		if(item->Count() < 1)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperTitleSystemTitleDelReq(rmsg, char_index, title_index, custom_title_index);
			SEND_Q(rmsg, gserver->m_subHelper);

			return ;
		}

		if (item->m_serial != (const char *)serial)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperTitleSystemTitleDelReq(rmsg, char_index, title_index, custom_title_index);
			SEND_Q(rmsg, gserver->m_subHelper);

			return ;
		}

		if(ch->m_titleList.m_nCount >= MAX_TITLE_COUNT)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperTitleSystemTitleDelReq(rmsg, char_index, title_index, custom_title_index);
			SEND_Q(rmsg, gserver->m_subHelper);

			return ;
		}

		if(custom_title_index > 0)
		{
			CTitle* delete_title = ch->m_titleList.Find(CUSTOM_TITLE_DUMMY_INDEX);
			ch->m_titleList.Remove(delete_title);
		}

		if(ch->m_titleList.Add(title))
		{
			ch->m_inventory.deleteItemByItem(item);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				TitleUseMsg(rmsg, title->m_proto->m_index, title->m_endtime, title->m_custom_title_index);
				SEND_Q(rmsg, ch->m_desc);
			}

			GAMELOG << init("TITLE ITEM USE", ch)
					<< "ITEM INDEX" << delim
					<< item->getDBIndex() << end;
		}
	}
	// [selo: 101109] �������� ���� �߰�
	else if( errortype == 2 )
	{
		ch = PCManager::instance()->getPlayerByCharIndex(char_index);
		if(ch == NULL)
			return ;
		title = gserver->m_titleProtoList.Create(title_index, endtime);
		title->m_custom_title_index = custom_title_index;

		if(title == NULL)
			return ;

		if(custom_title_index > 0)
		{
			CTitle* delete_title = ch->m_titleList.Find(CUSTOM_TITLE_DUMMY_INDEX);
			ch->m_titleList.Remove(delete_title);
		}

		if(ch->m_titleList.Add(title))
		{
			CNetMsg::SP rmsg(new CNetMsg);
			TitleUseMsg(rmsg, title->m_proto->m_index, title->m_endtime, title->m_custom_title_index);
			SEND_Q(rmsg, ch->m_desc);
			GAMELOG << init("TITLE FORCE INSERT", ch)
					<< "TITLE INDEX" << delim
					<< title->m_proto->m_index << end;
		}
	}
}

void ProcSubHelperTitleSystemDisableRep(CNetMsg::SP& msg)
{
	int char_index = 0;
	int disable_count = 0;
	CPC* ch = NULL;
	RefMsg(msg) >> char_index;
	RefMsg(msg) >> disable_count;

	ch = PCManager::instance()->getPlayerByCharIndex(char_index);
	if(!ch)
		return ;

	if( disable_count == 0 )
	{
		// LIST ����
		CTitleNode* temp;
		temp = ch->m_titleList.m_head;
		if(!temp)
			return ;

		{
			CNetMsg::SP rmsg(new CNetMsg);
			TitleSystemListMsg(rmsg, MSG_EX_TITLE_SYSTEM_LIST_REP_EXIST_LIST, ch->m_titleList.m_nCount);
			ResponseClient::TitleSystemList* packet = reinterpret_cast<ResponseClient::TitleSystemList*>(rmsg->m_buf);

			int count = 0;

			while(temp)
			{
				packet->data[count].index = temp->m_title->m_proto->m_index;
				packet->data[count].end_time = temp->m_title->m_endtime;
				packet->data[count].custom_title_index = temp->m_title->m_custom_title_index;
				count ++;
				temp = temp->m_next;
			}
			packet->title_count = count;
			rmsg->setSize(sizeof(ResponseClient::TitleSystemList) + sizeof(ResponseClient::TitleSystemData) * count);

			SEND_Q(rmsg, ch->m_desc);
		}
	}
	else
	{
		int title_index = 0;

		{
			CNetMsg::SP rmsg(new CNetMsg);
			SysMsg(rmsg, MSG_SYS_TITLE_EXPIRED);
			RefMsg(rmsg) << disable_count;
			for(int i = 0; i < disable_count; i++)
			{
				RefMsg(msg) >> title_index;
				RefMsg(rmsg) << title_index;
				ch->m_titleList.Remove(ch->m_titleList.Find(title_index));
			}
			SEND_Q(rmsg, ch->m_desc);
		}

		if(ch->m_titleList.m_nCount == 0)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			TitleSystemListMsg(rmsg, MSG_EX_TITLE_SYSTEM_LIST_REP_NO_LIST, ch->m_titleList.m_nCount);
			SEND_Q(rmsg, ch->m_desc);
		}
		else
		{
			CTitleNode* temp;
			temp = ch->m_titleList.m_head;
			if(!temp)
				return ;

			{
				int count = 0;
				CNetMsg::SP rmsg(new CNetMsg);
				TitleSystemListMsg(rmsg, MSG_EX_TITLE_SYSTEM_LIST_REP_EXIST_LIST, ch->m_titleList.m_nCount);

				ResponseClient::TitleSystemList* packet = reinterpret_cast<ResponseClient::TitleSystemList*>(rmsg->m_buf);
				while(temp)
				{
					
					packet->data[count].index = temp->m_title->m_proto->m_index;
					packet->data[count].end_time = temp->m_title->m_endtime;
					packet->data[count].custom_title_index = temp->m_title->m_custom_title_index;
					count++;					
					temp = temp->m_next;
				}
				packet->title_count = count;
				rmsg->setSize(sizeof(ResponseClient::TitleSystemList) + sizeof(ResponseClient:: TitleSystemData) * count);

				SEND_Q(rmsg, ch->m_desc);
			}
		}
	}
}

void ProcSubHelperTitleSystemDeleteRep(CNetMsg::SP& msg)
{
	int char_index;
	int title_index;
	int errortype;
	CPC* ch;
	CTitle* title;
	bool bAppear = false;

	RefMsg(msg) >> char_index >> title_index >> errortype;

	ch = PCManager::instance()->getPlayerByCharIndex(char_index);
	if(!ch)
		return ;

	if((ch->m_nCurrentTitle == title_index) && errortype)
	{
		ch->m_nCurrentTitle = TITLE_SYSTEM_NO_TITLE;
		ch->m_custom_title_index = -1;
		bAppear = true;
	}

	title = ch->m_titleList.Find(title_index);
	if(!title)
		return ;

	if(ch->m_titleList.Remove(title) && errortype)
	{
		GAMELOG << init("TITLE REMOVE TO LIST", ch) << delim
				<< "TITLE LIST" << delim << title_index << end;
		ch->CalcStatus(true);
		
		{
			CNetMsg::SP rmsg(new CNetMsg);
			TitleSystemMsg(rmsg, MSG_EX_TITLE_SYSTEM_TITLE_DELETE_SUCCESS, title_index, ch->m_index, title->m_custom_title_index);
			if(bAppear)
			{
				ch->m_pArea->SendToCell(rmsg, ch);
			}
			SEND_Q(rmsg, ch->m_desc);
		}

		if(title_index == CUSTOM_TITLE_DUMMY_INDEX)
		{
			std::map<int, MAKE_TITLE*>::iterator it = ch->_map_title.find(title->m_custom_title_index);
			if( it != ch->_map_title.end() )
			{
				std::string query = boost::str(boost::format("DELETE FROM t_title_make where a_index = %d") % it->second->title_index);
				DBManager::instance()->pushQuery(0, query);

				{
					CNetMsg::SP rmsg(new CNetMsg);
					TitleDeleteInfoMsg(rmsg, it->second->title_index);
					SEND_Q(rmsg, ch->m_desc);
				}

				{
					CNetMsg::SP rmsg(new CNetMsg);
					TitleUserInfoMsg(rmsg, ch->m_index, -1, -1, -1, "");
					ch->m_pArea->SendToCell(rmsg, ch, true);
				}

				delete[] it->second->option_index;
				delete[] it->second->option_level;
				delete it->second;

				ch->_map_title.erase(title->m_custom_title_index);
			}
		}

		GAMELOG << init("TITLE DELETE SUCCESS(user delete)", ch) << delim
				<< "TITLE INDEX" << delim << title_index << end;
	}
	else if(!errortype)
	{
		GAMELOG << init("TITLE CANT REMOVE TO LIST", ch) << delim
				<< "TITLE LIST" << delim << title_index << end;
	}
}

// [selo: 101105] ���� �ð� ���� ����
void ProcSubHelperTitleSystemForceChangeTime(CNetMsg::SP& msg)
{
	int char_index;
	int title_index;
	int endtime;
	CPC* ch;
	CTitle* title;

	RefMsg(msg) >> char_index >> title_index >> endtime;

	ch = PCManager::instance()->getPlayerByCharIndex(char_index);
	if( !ch )
		return;

	title = ch->m_titleList.Find(title_index);
	if(!title)
		return;

	title->m_endtime = endtime;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		TitleSystemForceChangeTimeMsg(rmsg, MSG_EX_TITLE_SYSTEM_TITLE_CHANGE_TIME, title_index, endtime);
		SEND_Q(rmsg, ch->m_desc);
	}

	GAMELOG << init("TITLE FORCE CHANGE TIME SUCCESS", ch) << delim
			<< "TITLE INDEX" << delim << title_index
			<< "END TIME" << delim << endtime << end;
}

void ProcSubHelperLCBallinfo( CNetMsg::SP& msg)
{
	// Ŭ�� �޼��� ���� ������
	int charIndex=0 , curCoinInex = 0;
	char coinCount=0, courseCount=0, itemCount=0, curCourseIndex = 0;

	RefMsg(msg) >> charIndex ;

	// PC ã��
	CPC* pc = PCManager::instance()->getPlayerByCharIndex(charIndex);
	if( !pc )
		return;

	CNetMsg::SP rmsg(new CNetMsg);
	rmsg->Init( MSG_EXTEND );
	RefMsg(rmsg) << MSG_EX_LCBALL
				 << (char)MSG_EX_LCBALL_INFO;

	int idx=0;
	// ��ū ��� ����
	RefMsg(msg) >> coinCount;
	RefMsg(rmsg) << coinCount;
	for( idx=0; idx < coinCount; idx++ )
	{
		int coinIndex = 0;
		RefMsg(msg) >> coinIndex;
		RefMsg(rmsg) << coinIndex;
	}
	// �ڽ� ��ü ���� ����
	int nItem=0, nRemain = 0 , nMax =0;
	unsigned int nItemCount = 0;

	RefMsg(msg) >> courseCount;
	RefMsg(rmsg) << courseCount;
	for( idx=0; idx < courseCount; idx++ )
	{
		RefMsg(msg) >> nItem >> nItemCount >> nMax >> nRemain;
		RefMsg(rmsg) << nItem << nItemCount << nMax << nRemain;
	}
	// ���� ��ū�ε��� , �ڽ� �ε���
	RefMsg(msg) >> curCoinInex >> curCourseIndex;
	RefMsg(rmsg) << curCoinInex << curCourseIndex;

	// ���� ������ ��������
	RefMsg(msg) >> itemCount;
	RefMsg(rmsg) << itemCount;
	for( idx=0; idx < itemCount; idx++ )
	{
		RefMsg(msg) >> nItem >> nItemCount >> nMax >> nRemain;
		RefMsg(rmsg) << nItem << nItemCount << nMax << nRemain;
	}
	// ��û�ڿ��� ������
	SEND_Q( rmsg , pc->m_desc );
}

void ProcSubHelperLCBalluse( CNetMsg::SP& msg)
{
	// �ݵ�� �������۷� ���� �������� ( ���� BeginTrans ���� )
	// �κ� �˻��Ͽ� ������ ����
	int			charIndex=0, coinIndex=0, itemIndex=0;
	unsigned int itemCount=0;
	char		courseIndex=0 , cOrder = 0;

	RefMsg(msg) >> charIndex >> coinIndex >> courseIndex >> cOrder >> itemIndex >> itemCount;

	// PC ã��
	CPC* pc = PCManager::instance()->getPlayerByCharIndex(charIndex);
	if( !pc )
	{
		CLCString	strVNick(20);
		strVNick.Format("dummy");
		CNetMsg::SP rmsg(new CNetMsg);
		SubHelperLCBalluse_successMsg( rmsg, 1, strVNick, coinIndex, courseIndex, cOrder, itemIndex ); // �ѹ�
		SEND_Q( rmsg, gserver->m_subHelper );
		return;
	}

	// DB UPDATE ERROR at SubHelper
	if( coinIndex < 0 || itemIndex < 0 ) //new2022 ?
	{
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperLCBalluse_successMsg( rmsg, 1, pc->m_nick, coinIndex, courseIndex, cOrder, itemIndex ); // �ѹ�
			SEND_Q( rmsg, gserver->m_subHelper )
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			LCBallUseMsg( rmsg, 1 , 0 );
			SEND_Q(rmsg, pc->m_desc);
		}

		return;
	}

	// ����� Ȯ�� ����Ȯ��
	if( pc->m_inventory.getEmptyCount() < 1 )
	{
		{
			// ����� ����
			CNetMsg::SP rmsg(new CNetMsg);
			LCBallUseMsg( rmsg, 1 , itemIndex );
			SEND_Q(rmsg, pc->m_desc );
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperLCBalluse_successMsg( rmsg, 1, pc->m_nick, coinIndex, courseIndex, cOrder, itemIndex ); // �ѹ�
			SEND_Q( rmsg, gserver->m_subHelper );
		}

		return;
	}

	CItem *pCoinItem = pc->m_inventory.FindByDBIndex(coinIndex);
	if( pCoinItem == NULL )
	{
		{
			CNetMsg::SP rmsg(new CNetMsg);
			LCBallUseMsg( rmsg, 2 , itemIndex );	// ������ �����ϴ�.
			SEND_Q(rmsg, pc->m_desc );
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperLCBalluse_successMsg( rmsg, 1, pc->m_name, coinIndex, courseIndex, cOrder, itemIndex ); // �ѹ�
			SEND_Q( rmsg, gserver->m_subHelper );
		}

		return;
	}

	// ������(itemIndex) ����
	CItem * pItem = gserver->m_itemProtoList.CreateItem( itemIndex, -1 , 0, 0, itemCount );
	if (pItem == NULL)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SubHelperLCBallinfoMsg( rmsg, pc->m_index, coinIndex, courseIndex );
		SEND_Q( rmsg, gserver->m_subHelper );

		return;
	}

	if (pc->m_inventory.addItem(pItem))
	{
		pc->m_inventory.decreaseItemCount(pCoinItem, 1);

		CNetMsg::SP rmsg(new CNetMsg);
		SubHelperLCBalluse_successMsg( rmsg, 0, pc->m_nick,  coinIndex , courseIndex, cOrder, itemIndex ); // ���� ������ ���� �޼��� ������
		SEND_Q( rmsg , gserver->m_subHelper );

		if(cOrder == 0)
		{
			//ĳ���� ����, ������ ���� �α� �����
			if(pc && pItem)
				GAMELOG << init("LacaBall First Place", pc) << itemlog(pItem) << end;
		}
		else
		{
			if(pc && pItem && pCoinItem)
				GAMELOG << init("LACA BALL SYSTEM", pc)
						<< pCoinItem->getDBIndex() << " ==> " << pItem->getDBIndex() << end;
		}
	}
	else
	{
		delete pItem;

		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperLCBalluse_successMsg( rmsg, 1, pc->m_nick, coinIndex, courseIndex, cOrder, itemIndex ); // �ѹ�
			SEND_Q( rmsg, gserver->m_subHelper );
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			LCBallUseMsg( rmsg, 1 , itemIndex );
			SEND_Q(rmsg, pc->m_desc);
		}
	}

	{
		// �������� ��û
		CNetMsg::SP rmsg(new CNetMsg);
		SubHelperLCBallinfoMsg( rmsg, pc->m_index, coinIndex, courseIndex );
		SEND_Q( rmsg, gserver->m_subHelper );
	}
}

void ProcSubHelperLCBall_sucess( CNetMsg::SP& msg)
{
	// ��������� ��÷�޼��� �Ѹ���
	CLCString name(MAX_CHAR_NAME_LENGTH + 1);
	int	itemIndex=0;

	RefMsg(msg) >> name >> itemIndex ;

	CNetMsg::SP rmsg(new CNetMsg);
	// �޼��� ����
	LCBallSuccessMsg( rmsg, name, itemIndex );
	PCManager::instance()->sendToAll(rmsg);
	// ��� ĳ���Ϳ� ����
}

void ProcSubHelperRakingList(CNetMsg::SP& msg)
{
	CLCString name(20), levelup_date(20);
	int total_count, list_count, charIdx, rank, rank_pre, exp, exp_pre, level;
	unsigned char type, subtype, job;

	RefMsg(msg) >> type
				>> subtype
				>> charIdx
				>> total_count
				>> list_count;

	CPC* ch = PCManager::instance()->getPlayerByCharIndex(charIdx);
	if (ch == NULL)
		return;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		RankingEXList(rmsg, MSG_EX_RANKING_LIST, type, subtype);
		RefMsg(rmsg) << total_count
					 << list_count;

		for (int i=0 ; i<list_count; ++i)
		{
			RefMsg(msg) >> name
						>> rank
						>> rank_pre
						>> exp
						>> exp_pre
						>> level
						>> job
						>> levelup_date;

			RefMsg(rmsg) << name
						 << rank
						 << rank_pre
						 << exp
						 << exp_pre
						 << level
						 << job
						 << levelup_date;
		}
		SEND_Q(rmsg, ch->m_desc);
	}
}
void ProcSubHelperRankingSearch(CNetMsg::SP& msg)
{
	CLCString name(20), levelup_date(20);
	int total_count, charIdx, rank, rank_pre, exp, exp_pre, level;
	unsigned char type, subtype, job;

	RefMsg(msg) >> type
				>> subtype
				>> charIdx
				>> total_count;

	CPC* ch = PCManager::instance()->getPlayerByCharIndex(charIdx);
	if (ch == NULL)
		return;

	{
		CNetMsg::SP rmsg(new CNetMsg);
		RankingEXList(rmsg, MSG_EX_RANKING_SEARCH, type, subtype);
		RefMsg(rmsg) << total_count;
		for (int i=0 ; i<total_count; ++i)
		{
			RefMsg(msg) >> name
						>> rank
						>> rank_pre
						>> exp
						>> exp_pre
						>> level
						>> job
						>> levelup_date;

			RefMsg(rmsg) << name
						 << rank
						 << rank_pre
						 << exp
						 << exp_pre
						 << level
						 << job
						 << levelup_date;
		}
		SEND_Q(rmsg, ch->m_desc);
	}
}
void ProcSubHelperRankingRefresh(CNetMsg::SP& msg)
{
	// ���� ���ӿ� ������ ��� ������ m_exp_weekly���� �ʱ�ȭ�Ѵ�.
	// �� ��ƾ�� ������, �����ϰ� �ִ� �������� m_exp_weekly���� �����Ǿ� �߸��� ��ŷ�� �����ϰԵȴ�.
	PCManager::map_t& playerMap			= PCManager::instance()->getPlayerMap();
	PCManager::map_t::iterator it		= playerMap.begin();
	PCManager::map_t::iterator endit	= playerMap.end();
	for (; it != endit; ++it)
	{
		CPC* pChar = (*it).pPlayer;
		if (pChar == NULL)
			continue;
		pChar->m_exp_weekly = 0;
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		RankingEXRefresh(rmsg);
		PCManager::instance()->sendToAll(rmsg);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		int endTime = gserver->getNowSecond() + (7 * 24 * 60 * 60);
		SubHelperRankingRewardReqEx(rmsg, endTime);
		SEND_Q(rmsg, gserver->m_subHelper);
	}
}
void ProcSubHelperRankingError(CNetMsg::SP& msg)
{
	int type, char_index;
	RefMsg(msg) >> type >> char_index;

	CPC* ch = PCManager::instance()->getPlayerByCharIndex(char_index);
	if ( ch )
	{
		CNetMsg::SP rmsg(new CNetMsg);
		RankingEXError(rmsg, type);
		SEND_Q(rmsg, ch->m_desc);
	}
}

#ifdef REFORM_PK_PENALTY_201108 // 2011-08 PK �г�Ƽ ����
void ProcSubHelperPKPenaltyReformRep(CNetMsg::SP& msg)
{
	unsigned char subType;
	int charIndex;
	RefMsg(msg) >> subType
				>> charIndex;

	CPC* pc = PCManager::instance()->getPlayerByCharIndex(charIndex);

	if( !pc )
		return;

	switch( subType )
	{
	case MSG_SUBHELPER_PKPENALTY_REFORM_REWARD_INFO_REP:
		ProcSubHelperPKPenaltyReformRewardInfoRep(pc, msg);
		break;

	case MSG_SUBHELPER_PKPENALTY_REFORM_REWARD_REP:
		ProcSubHelperPKPenaltyReformRewardRep(pc, msg);
		break;
	}
}

void ProcSubHelperPKPenaltyReformRewardInfoRep(CPC* pc, CNetMsg::SP& msg)
{
	int rewardFlag;
	RefMsg(msg) >> rewardFlag;

	pc->m_pkPenaltyReward = rewardFlag;
	CNetMsg::SP rmsg(new CNetMsg);
	MsgPKPenaltyRewardInfoRep(rmsg, rewardFlag);
	SEND_Q(rmsg, pc->m_desc);
}

void ProcSubHelperPKPenaltyReformRewardRep(CPC* pc, CNetMsg::SP& msg)
{
	int rewardNum;
	int titleIndex;
	unsigned char errorType;

	RefMsg(msg) >> rewardNum
				>> titleIndex
				>> errorType;

	if( errorType == MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_SUC )
	{
		if( pc->m_titleList.m_nCount > MAX_TITLE_COUNT )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			MsgPKPenaltyRewardRep(rmsg, rewardNum, MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_COUNT);
			SEND_Q(rmsg, pc->m_desc);
			return;
		}

		CTitleProto * titleProto =  gserver->m_titleProtoList.FindProto( titleIndex );

		if( !titleProto )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			MsgPKPenaltyRewardRep(rmsg, rewardNum, MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_FAIL);
			SEND_Q(rmsg, pc->m_desc);
			return;
		}

		CTitle * title = gserver->m_titleProtoList.Create(titleProto->m_index, titleProto->m_time);

		if( !title )
		{
			CNetMsg::SP rmsg(new CNetMsg);
			MsgPKPenaltyRewardRep(rmsg, rewardNum, MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_FAIL);
			SEND_Q(rmsg, pc->m_desc);
			return;
		}

		if( !pc->m_titleList.Add(title) )
		{
			delete title;
			title = NULL;

			CNetMsg::SP rmsg(new CNetMsg);
			MsgPKPenaltyRewardRep(rmsg, rewardNum, MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_FAIL);
			SEND_Q(rmsg, pc->m_desc);
			return;
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			TitleUseMsg(rmsg, title->m_proto->m_index, title->m_endtime, -1);
			SEND_Q(rmsg, pc->m_desc);
		}

		GAMELOG << init("PK PENALTY REWARD : TITLE INSERT", pc)
				<< "REWARD NUM" << delim << rewardNum
				<< "TITLE INDEX" << delim << title->m_proto->m_index << end;

		// ���� ���� ����
		pc->SetPKPenaltyReward( rewardNum );

		{
			CNetMsg::SP rmsg(new CNetMsg);
			MsgPKPenaltyRewardInfoRep( rmsg, pc->m_pkPenaltyReward );
			SEND_Q(rmsg, pc->m_desc);
		}
	}

	{
		// ��� �޽���
		CNetMsg::SP rmsg(new CNetMsg);
		MsgPKPenaltyRewardRep(rmsg, rewardNum, errorType);
		SEND_Q(rmsg, pc->m_desc);
	}
}
#endif // REFORM_PK_PENALTY_201108 // 2011-08 PK �г�Ƽ ����

#ifdef NOTICE_SYSTEM
void ProcSubHelperNoticeSystem(CNetMsg::SP& msg)
{
	int _type;

	RefMsg(msg) >> _type;

	switch ( _type )
	{
	case MSG_SUBHELPER_USER_NOTICE_REG_REP:
		ProcSubHelperNoticeSystemRegRep(msg);
		break;
	case MSG_SUBHELPER_USER_NOTICE_PRINT:
		ProcSubHelperUserNoticePrint(msg);
		break;
	}
}

void ProcSubHelperNoticeSystemRegRep(CNetMsg::SP& msg)
{
	//unsigned char _result = '0';	// default : fail ( 0 : fail, 1 : success )
	int _characterIndex = 0;

	RefMsg(msg) >> _characterIndex;

	CPC* pc = PCManager::instance()->getPlayerByCharIndex(_characterIndex);
	if ( !pc )
		return;

	CNetMsg::SP rmsg(new CNetMsg);
	UserNoticeRegRepMsg(rmsg);
	SEND_Q(rmsg, pc->m_desc);

	GAMELOG << init("[USER NOTICE] REGIST SUCCESS") << delim
		<< pc->GetName() << end;
}

void ProcSubHelperUserNoticePrint(CNetMsg::SP& msg)
{
	CLCString _name, _contents(81);
	int _count;

	RefMsg(msg) >> _name
		>> _contents
		>> _count;

	if ( _name.Length() <= 0 || _contents.Length() <= 0 )
		return;

	CNetMsg::SP rmsg(new CNetMsg);
	UserNoticePrintMsg(rmsg, _name, _contents);
	PCManager::instance()->sendToAll(rmsg);

	GAMELOG << init("[USER NOTICE] PRINT") << delim
		<< _name << delim
		<< _contents << delim
		<< _count << end;
}
#endif // NOTICE_SYSTEM

void ProcSubHelperExtCharSlotItemUseRep(CNetMsg::SP& msg)
{
	unsigned char _cmd;
	int _userIndex;
	int _charIndex;
	int _tab;
	int _invenIndex;
	CLCString _serial;
	long _time;

	RefMsg(msg) >> _cmd >> _userIndex >> _charIndex >> _tab >> _invenIndex >> _serial >> _time;

	CPC* ch = PCManager::instance()->getPlayerByCharIndex(_charIndex);

	if(!ch)
	{
		GAMELOG << init("ERROR") << "CANNOT FIND PLAYER" << delim << _charIndex << end;
		if(_cmd == 1)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			SubHelperCharSlotExtUseResult(rmsg, _userIndex);
			SEND_Q(rmsg, gserver->m_subHelper);
		}
		return ;
	}

	switch((int)_cmd)
	{
	case 0:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ItemUseCharSlotExt(rmsg, _cmd);
			SEND_Q(rmsg, ch->m_desc);
			GAMELOG << init("ERROR") << "CANNOT USE EXTEND CHARACTERS SLOT ITEM" << end;
		}
		break;
	case 1:
		{
			CItem* item = ch->m_inventory.getItem(_tab, _invenIndex);
			if(item == NULL || item->Count() < 1 || (item->m_serial != (const char *)_serial))
			{
				{
					CNetMsg::SP rmsg(new CNetMsg);
					ItemUseCharSlotExt(rmsg, 0); /* ������� ������ �������� �־�� �ϴµ� ��������! ���� ó�� */
					SEND_Q(rmsg, ch->m_desc);
				}

				{
					// roll back
					CNetMsg::SP rmsg(new CNetMsg);
					SubHelperCharSlotExtUseResult(rmsg, ch->m_desc->m_index);
					SEND_Q(rmsg, gserver->m_subHelper);
				}
			}
			else
			{
				{
					CNetMsg::SP rmsg(new CNetMsg);
					ItemUseCharSlotExt(rmsg, _cmd);
					SEND_Q(rmsg, ch->m_desc);
				}

				ch->m_inventory.decreaseItemCount(item, 1);
				ch->m_desc->setExtendCharacterSlotTime(_time);
				GAMELOG << init("USE EXTEND CHARACTER SLOT ITEM", ch) << end;
			}
		}
		break;
	case 2:
		{
			CNetMsg::SP rmsg(new CNetMsg);
			ResponseClient::ItemNotUseMsg(rmsg, MSG_ITEM_USE_ERROR_EXT_CHAR_SLOT);
			SEND_Q(rmsg, ch->m_desc);
			GAMELOG << init("CANNOT USE EXTEND CHARACTER SLOT ITEM") << delim << "ALREADY USED" << end;
		}
		break;
	default:
		break;
	}
}

void ProcSubHelperMailBoxList(CNetMsg::SP& msg)
{
	CNetMsg::SP rmsg(new CNetMsg);
	ResponseClient::MailBoxListGS* packet = reinterpret_cast<ResponseClient::MailBoxListGS*>(msg->m_buf);
	CPC* ch = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);
	if (ch == NULL)
		return;
	if (packet->error == Ok)
	{
		ResponseClient::MailBoxList* rpacket = reinterpret_cast<ResponseClient::MailBoxList*>(rmsg->m_buf);
		rpacket->type = MSG_MAIL_BOX;
		rpacket->subType = MSG_SUB_MAILBOX_LIST_FINISH;
		rpacket->listCount = packet->listCount;
		for (int i = 0; i < rpacket->listCount; i++)
		{
			rpacket->list[i].index = packet->list[i].index;
			rpacket->list[i].senderType = packet->list[i].senderType;
			rpacket->list[i].targetIndex = packet->list[i].targetIndex;
			rpacket->list[i].pageType = packet->list[i].pageType;
			rpacket->list[i].recvTime = packet->list[i].recvTime;
			rpacket->list[i].haveAttachment = packet->list[i].haveAttachment;
			rpacket->list[i].isRead = packet->list[i].isRead;
			strcpy(rpacket->list[i].targetUser, packet->list[i].targetUser);
			strcpy(rpacket->list[i].subject, packet->list[i].subject);
		}
		rmsg->setSize(sizeof(*rpacket) + (sizeof(rpacket->list[0]) * rpacket->listCount));
		SEND_Q(rmsg, ch->m_desc);
	}
	else
	{
		ResponseClient::MailBoxError* rpacket = reinterpret_cast<ResponseClient::MailBoxError*>(rmsg->m_buf);
		rmsg->setSize(sizeof(*rpacket));
		SEND_Q(rmsg, ch->m_desc);
	}
}
void ProcSubHelperMailBoxDelete(CNetMsg::SP& msg)
{
	ResponseClient::MailBoxDeleteMailGS* packet = reinterpret_cast<ResponseClient::MailBoxDeleteMailGS*>(msg->m_buf);
	CPC* ch = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);
	if (ch == NULL)
		return;
	if (packet->error == Ok)
	{
		ResponseClient::MailBoxDeleteMail* rpacket = reinterpret_cast<ResponseClient::MailBoxDeleteMail*>(msg->m_buf);
		msg->setSize(sizeof(*rpacket));
		SEND_Q(msg, ch->m_desc);
	}
	else
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::MailBoxError* rpacket = reinterpret_cast<ResponseClient::MailBoxError*>(rmsg->m_buf);
		rmsg->setSize(sizeof(*rpacket));
		SEND_Q(rmsg, ch->m_desc);
	}
}
void ProcSubHelperMailBoxDeleteAll(CNetMsg::SP& msg)
{
	ResponseClient::MailBoxDeleteAllMailsGS* packet = reinterpret_cast<ResponseClient::MailBoxDeleteAllMailsGS*>(msg->m_buf);
	CPC* ch = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);

	LOG_INFO("Mail - subtype %d ", packet->subType);

	if (ch == NULL)
		return;
	if (packet->error == Ok)
	{
		ResponseClient::MailBoxDeleteAll* rpacket = reinterpret_cast<ResponseClient::MailBoxDeleteAll*>(msg->m_buf);
		msg->setSize(sizeof(*rpacket));
		SEND_Q(msg, ch->m_desc);
	}
	else
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::MailBoxError* rpacket = reinterpret_cast<ResponseClient::MailBoxError*>(rmsg->m_buf);
		rmsg->setSize(sizeof(*rpacket));
		SEND_Q(rmsg, ch->m_desc);
	}
}
void ProcSubHelperMailBoxError(CNetMsg::SP& msg)
{
	ResponseClient::MailBoxErrorGS* packet = reinterpret_cast<ResponseClient::MailBoxErrorGS*>(msg->m_buf);
	CPC* ch = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);
	if (ch == NULL)
		return;
	msg->setSize(sizeof(ResponseClient::MailBoxError));
	SEND_Q(msg, ch->m_desc);
}
void ProcSubHelperMailBoxOpenLetter(CNetMsg::SP& msg)
{
	CNetMsg::SP rmsg(new CNetMsg);
	ResponseClient::MailBoxOpenLetterGS* packet = reinterpret_cast<ResponseClient::MailBoxOpenLetterGS*>(msg->m_buf);
	CPC* ch = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);
	if (ch == NULL)
		return;
	if (packet->error == Ok)
	{
		ResponseClient::MailBoxOpenLetter* rpacket = reinterpret_cast<ResponseClient::MailBoxOpenLetter*>(rmsg->m_buf);
		rpacket->type = packet->type;
		rpacket->subType = packet->subType;
		memcpy(&rpacket->letter, &packet->letter, (sizeof(packet->letter) + sizeof(packet->letter.list[0]) * packet->letter.itemsCount));
		rmsg->setSize(sizeof(*rpacket) + sizeof(rpacket->letter.list[0]) * rpacket->letter.itemsCount);
		SEND_Q(rmsg, ch->m_desc);
	}
	else
	{
		ResponseClient::MailBoxError* rpacket = reinterpret_cast<ResponseClient::MailBoxError*>(rmsg->m_buf);
		rmsg->setSize(sizeof(*rpacket));
		SEND_Q(rmsg, ch->m_desc);
	}
}
void ProcSubHelperMailBoxCollectLetter(CNetMsg::SP& msg)
{
	CNetMsg::SP rmsg(new CNetMsg);
	ResponseClient::MailBoxCollectLetterGS* packet = reinterpret_cast<ResponseClient::MailBoxCollectLetterGS*>(msg->m_buf);
	CPC* ch = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);
	if (ch == NULL)
	{
		RequestClient::MailBoxCollectLetterGS* rpacket = reinterpret_cast<RequestClient::MailBoxCollectLetterGS*>(rmsg->m_buf);
		rpacket->type = MSG_MAIL_BOX;
		rpacket->subType = MSG_SUB_MAILBOX_LETTER_COLLECT_ROLLBACK;
		rpacket->mailId = packet->mailId;
		rpacket->charIndex = packet->charIndex;
		rmsg->setSize(sizeof(*rpacket));
		SEND_Q(rmsg, gserver->m_subHelper);
		return;
	}
	if (packet->error == Ok)
	{
		if (ch->m_inventory.getEmptyCount() < packet->itemsCount)
		{
			ResponseClient::MailBoxError* rpacket = reinterpret_cast<ResponseClient::MailBoxError*>(rmsg->m_buf);
			rpacket->errorCode = FullInventory;
			rmsg->setSize(sizeof(*rpacket));
			SEND_Q(rmsg, ch->m_desc);
			RequestClient::MailBoxCollectLetterGS* rollbackPacket = reinterpret_cast<RequestClient::MailBoxCollectLetterGS*>(rmsg->m_buf);
			rollbackPacket->type = MSG_MAIL_BOX;
			rollbackPacket->subType = MSG_SUB_MAILBOX_LETTER_COLLECT_ROLLBACK;
			rollbackPacket->mailId = packet->mailId;
			rollbackPacket->charIndex = packet->charIndex;
			rmsg->setSize(sizeof(*rollbackPacket));
			SEND_Q(rmsg, gserver->m_subHelper);
			return;
		}
		if (packet->nas > 0)
		{
			ch->m_inventory.increaseMoney(packet->nas);
			GAMELOG << init("MAILBOX COLLECT. NAS", ch)
				<< "MONEY" << delim << packet->nas << delim
				<< "NEW MONEY AMOUNT" << delim << ch->m_inventory.getMoney()
				<< end;
		}
		for (int i = 0; i < packet->itemsCount; i++)
		{
			ExpressSystemItemInfo itemInfo = packet->list[i];
			int socket_count = 0;
			for (int i = 0; i < MAX_SOCKET_COUNT; ++i, ++socket_count)
			{
				if (itemInfo.socket[i] == -1)
					break;
			}
			short item_option[MAX_ITEM_OPTION] = { 0, };
			for (int i = 0; i < MAX_ITEM_OPTION; ++i)
			{
				item_option[i] = COption::SetDBValue(itemInfo.option_type[i], itemInfo.option_level[i]);
			}
#ifdef DURABILITY
			CItem* pItem = gserver->m_itemProtoList.CreateDBItem(
				itemInfo.item_index,
				-1, // wearPos
				itemInfo.plus,
				itemInfo.flag,
				0, // used
				0, // used_2
				itemInfo.serial,
				(LONGLONG)itemInfo.item_count,
				item_option,
				socket_count,
				itemInfo.socket,
				itemInfo.item_origin,
				itemInfo.now_durability,
				itemInfo.max_durability
			);
#else
			CItem* pItem = gserver->m_itemProtoList.CreateDBItem(
				itemInfo.item_index,
				-1, // wearPos
				itemInfo.plus,
				itemInfo.flag,
				0, // used
				0, // used_2
				itemInfo.serial,
				(LONGLONG)itemInfo.item_count,
				item_option,
				socket_count,
				itemInfo.socket,
				itemInfo.item_origin
			);
#endif
			if (pItem == NULL)
			{
				LOG_FATAL("MAILBOX COLLECT. NOT CREATE ITEM. item_index[%d] / item_plus[%d] / item_serial[%s]",
					itemInfo.item_index, itemInfo.plus, itemInfo.serial);
				continue;
			}
			if (itemInfo.serial[0] == '\0' && !(pItem->m_itemProto->getItemFlag() & ITEM_FLAG_COUNT))
			{
				pItem->m_serial = GetSerial();
			}
			pItem->setPlus_2(itemInfo.plus2);
			if (ch->m_inventory.addItem(pItem))
			{
				GAMELOG << init("MAILBOX COLLECT. ITEM", ch)
						<< itemlog(pItem) 
						<< end;
			}
			else
			{
				delete pItem;
				pItem = NULL;
				LOG_ERROR("MAILBOX COLLECT. Inven is Full. charIndex : %d", ch->m_index);
			}
		}
		ResponseClient::MailBoxCollectLetter* rpacket = reinterpret_cast<ResponseClient::MailBoxCollectLetter*>(rmsg->m_buf);
		rpacket->type = packet->type;
		rpacket->subType = packet->subType;
		rpacket->mailId = packet->mailId;
		rmsg->setSize(sizeof(*rpacket));
		SEND_Q(rmsg, ch->m_desc);
	}
	else
	{
		ResponseClient::MailBoxError* rpacket = reinterpret_cast<ResponseClient::MailBoxError*>(rmsg->m_buf);
		rmsg->setSize(sizeof(*rpacket));
		SEND_Q(rmsg, ch->m_desc);
	}
}
void ProcSubHelperMailBoxSendLetter(CNetMsg::SP& msg)
{
	CNetMsg::SP rmsg(new CNetMsg);
	ResponseClient::MailBoxSendGS* packet = reinterpret_cast<ResponseClient::MailBoxSendGS*>(msg->m_buf);
	CPC* ch = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);
	if (ch == NULL)
		return;
	if (packet->error == Ok)
	{
		pTypeBase* rpacket = reinterpret_cast<pTypeBase*>(rmsg->m_buf);
		rpacket->type = MSG_MAIL_BOX;
		rpacket->subType = MSG_SUB_MAILBOX_SEND_LETTER;
		rmsg->setSize(sizeof(*rpacket));
		SEND_Q(rmsg, ch->m_desc);
	}
	else
	{
		ResponseClient::MailBoxError* rpacket = reinterpret_cast<ResponseClient::MailBoxError*>(rmsg->m_buf);
		rmsg->setSize(sizeof(*rpacket));
		SEND_Q(rmsg, ch->m_desc);
	}
}
void ProcSubHelperMailBoxUpdateStatus(CNetMsg::SP& msg)
{
	ResponseClient::MailBoxCheckLettersGS* packet = reinterpret_cast<ResponseClient::MailBoxCheckLettersGS*>(msg->m_buf);
	CPC* ch = PCManager::instance()->getPlayerByCharIndex(packet->charIndex);
	if (ch == NULL) return;
	CNetMsg::SP rmsg(new CNetMsg);
	UpdateClient::MailBoxUpdateStatus* rpacket = reinterpret_cast<UpdateClient::MailBoxUpdateStatus*>(rmsg->m_buf);
	rpacket->type = MSG_MAIL_BOX;
	rpacket->subType = MSG_SUB_MAILBOX_UPDATE_STATUS;
	rpacket->gotNewMails = packet->newMailsCount;
	rmsg->setSize(sizeof(*rpacket));
	SEND_Q(rmsg, ch->m_desc);
}

void ProcSubHelperUpdateDonationEventStatus(CNetMsg::SP& msg)
{
	bool isActive;
	time_t startTime = 0, endTime = 0;
	RefMsg(msg) >> isActive >> startTime >> endTime;
	gserver->m_donationTierManager.UpdateStatus(isActive, startTime, endTime);
	LOG_INFO("Donation event status update >> is_active : %s, start_time : %lld, end_time : %lld",
		isActive ? "true" : "false", startTime, endTime);
}

void ProcSubHelperUpdateDonationEventReward(CNetMsg::SP& msg)
{
	int playerId;
	RefMsg(msg) >> playerId;

	gserver->m_donationTierManager.LoadReward();
	LOG_INFO("Donation event reward update");

	CPC* ch = PCManager::instance()->getPlayerByCharIndex(playerId);
	if (ch == NULL)
		return;

	CNetMsg::SP rmsg(new CNetMsg);
	SayMsg(rmsg, MSG_CHAT_GM, ch->m_index, "", "", "Donation event reward reloaded");
	SEND_Q(rmsg, ch->m_desc);
}
