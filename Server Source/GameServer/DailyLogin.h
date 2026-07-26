#ifndef __DAILY_LOGIN__H__
#define __DAILY_LOGIN__H__

#include <vector>
#include <time.h>

struct RewardData {
	int day;
	int itemidx;
	int plus;
	int flag;
	int count;

};
class DailyLogin {
public:
	enum DPACK {

		OpenD = 0,
		DClaim = 1, 
		DLError,

	};
		std::vector<RewardData> m_Rewards;
		bool m_bInit , m_bOn;

	DailyLogin();
	~DailyLogin();
	bool Init();
	void ReloadTable();
	
	void DailyLoginMsg(CNetMsg::SP& msg);
	void do_DailyLogin(CPC* ch, CNetMsg::SP& msg);


	void DayClaim(CPC* ch , CNetMsg::SP& msg);
	
	void AttendanceFin(CPC* pc);
	
	void giveEpicReward(CPC* ch);
	void giveWeekReward(CPC* ch , int v);
	void giveDayReward(CPC* ch , int v );

	
	
	bool Started() { return m_bInit; }

};

#endif // __AUTO_BUFFER_H__

