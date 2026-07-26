#ifndef __REZABOT__H
	#define __REZABOT__H
	
#include <vector>
#include <time.h>



enum REZABOTMSG
{
	REZABOT_OPEN =68 ,
	REZABOT_START,
	REZABOT_STOP,
	REZABOT_CHECK,

};

class ReZaBot
{
private:
public:
	ReZaBot();
	~ReZaBot();
	void	InterpretMsg(CPC* ch, CNetMsg::SP& msg);
	
	void RezaBotMSG(CNetMsg::SP& msg);
	
	
	void ReplyOpen(CPC* ch, CNetMsg::SP& msg);

	void ReplyStart(CPC* ch, CNetMsg::SP& msg);

	void ReplyStop(CPC* ch, CNetMsg::SP& msg);

	void ReplyCheck(CPC* ch, CNetMsg::SP& msg);

	
};


#endif
