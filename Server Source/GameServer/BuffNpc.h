#ifndef __BUFF_NPC__H__
#define __BUFF_NPC__H__

#include <vector>
#include <time.h>


struct BUFFNPCDATA {
	int skillID;
	int level;
};

class BuffNPC {
public:
	BuffNPC();
	~BuffNPC();

	void do_EventBuffNpc(CPC* ch, CNetMsg::SP& msg);

	bool Init();

	void ReloadTable();
	
	bool Started() { return m_bInit; }

	std::vector<BUFFNPCDATA> m_npcbuff;

	bool m_bInit;
};

#endif // __AUTO_BUFFER_H__