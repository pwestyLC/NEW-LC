#include "stdhdrs.h"
#include "Server.h"
#include "CmdMsg.h"
#include "Character.h" 
//#include "ReZaBot.h"

#include "RezasFunction.h"




ReZaBot::ReZaBot(){

}
ReZaBot::~ReZaBot(){

}

void	ReZaBot::InterpretMsg(CPC* ch, CNetMsg::SP& msg)
{
	msg->MoveFirst();
	unsigned int op;
	unsigned int subtype ;
	RefMsg(msg) >> op;
	RefMsg(msg) >> subtype;

	switch(subtype)
	{	

	case REZABOT_OPEN:
		{
			ReplyOpen(ch , msg);
		}
		break;
	case REZABOT_START:
		{
			ReplyStart(ch,msg); 
		}
		break;

	case REZABOT_STOP:
		{
			ReplyStop(ch,msg);
		}
		break;
	case REZABOT_CHECK:
		{
			ReplyCheck(ch,msg);
		}
		break;
	default:
		{
			//fkplayer
		}
		break;

	}
}

void  ReZaBot::RezaBotMSG(CNetMsg::SP& msg){
	msg->Init(MSG_REZA);
	RefMsg(msg) << ((int)REZA_REZABOT);
}
void  ReZaBot::ReplyOpen(CPC* ch, CNetMsg::SP& msg){

	CNetMsg::SP omsg(new CNetMsg); // open ui packet
	RezaBotMSG(omsg);
	RefMsg(omsg) << ((int)REZABOT_OPEN);
	SEND_Q(omsg,ch->m_desc);
}

void  ReZaBot::ReplyStart(CPC* ch, CNetMsg::SP& msg) { 
	
	int DbIdx = 0;
	int ItemVID = 0;  
	RefMsg(msg) >> DbIdx;
	RefMsg(msg) >> ItemVID; 

	CItem* item = NULL;
	bool error = false;
	if((item = ch->m_inventory.FindByVirtualIndex(ItemVID)) == NULL) 
	{
		error = true;
	} 
	else if (item->m_itemProto->getItemTypeIdx() != ITYPE_ONCE )
	{
		error = true;
	}
	else if (item->m_itemProto->getItemSubTypeIdx() != IONCE_CASH )
	{
		error = true;
	}
	else if (item->m_itemProto->getItemNum2() != 555)
	{
		error = true;
	}
	else if( item->getUsed() < gserver->getNowSecond() )
	{
		ReplyStop(ch,msg);
		ch->m_inventory.deleteItemByItem(item);
		error = true;
	}
	if(error)
	{
			//header
		SendRezaMessage(ch,  "Missing Ticket or another error with ticket.", SystemMsgType::SYSMSG_ERROR);
		TO_PC(ch)->m_botting = 0;
		CNetMsg::SP omsg(new CNetMsg); // open ui packet
		RezaBotMSG(omsg);
		RefMsg(omsg) << ((int)REZABOT_STOP);
		SEND_Q(omsg,ch->m_desc);
	}
	else
	{
		


		if(ch->m_botting == 1)
		{
			TO_PC(ch)->m_botting = 0;
		}
		else
		{
			TO_PC(ch)->m_botting = 1;
		}
		
		CNetMsg::SP rmsg(new CNetMsg);
		CharStatusMsg(rmsg, ch, 0);
		ch->m_pArea->SendToCell(rmsg, ch, true);


		CNetMsg::SP omsg(new CNetMsg); // open ui packet
		RezaBotMSG(omsg);
		RefMsg(omsg) << ((int)REZABOT_START);
		SEND_Q(omsg,ch->m_desc);
	}



} 

void ReZaBot::ReplyStop(CPC* ch , CNetMsg::SP& msg) {
	
	TO_PC(ch)->m_botting = 0;
	CNetMsg::SP omsg(new CNetMsg);
	RezaBotMSG(omsg);
	RefMsg(omsg) << ((int)REZABOT_STOP);
	SEND_Q(omsg,ch->m_desc);
}

void ReZaBot::ReplyCheck(CPC* ch, CNetMsg::SP& msg)
{ 
	/*CNetMsg::SP omsg(new CNetMsg); // open ui packet
	RezaBotMSG(omsg);
	RefMsg(omsg) << ((int)REZABOT_CHECK);
	SEND_Q(omsg,ch->m_desc);
	*/
	int DbIdx = 0;
	int ItemVID = 0;  
	RefMsg(msg) >> DbIdx;
	RefMsg(msg) >> ItemVID; 

	CItem* item = NULL;
	bool error = false;
	if((item = ch->m_inventory.FindByVirtualIndex(ItemVID)) == NULL) 
	{
		error = true;
	} 
	else if (item->m_itemProto->getItemTypeIdx() != ITYPE_ONCE )
	{
		error = true;
	}
	else if (item->m_itemProto->getItemSubTypeIdx() != IONCE_CASH )
	{
		error = true;
	}
	else if (item->m_itemProto->getItemNum2() != 555)
	{
		error = true;
	}
	else if( item->getUsed() < gserver->getNowSecond() )
	{
		ReplyStop(ch,msg);
		ch->m_inventory.deleteItemByItem(item);
		error = true;
	}

	if(error)
	{
			//header
		SendRezaMessage(ch,  "Missing Ticket or another error with ticket, or Ticket Expired.", SystemMsgType::SYSMSG_ERROR);
		TO_PC(ch)->m_botting = 0;
		CNetMsg::SP omsg(new CNetMsg); // open ui packet
		RezaBotMSG(omsg);
		RefMsg(omsg) << ((int)REZABOT_CHECK);
		SEND_Q(omsg,ch->m_desc);
	}
	


}


