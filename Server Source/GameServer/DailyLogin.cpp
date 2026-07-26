#include "stdhdrs.h"
#include "Server.h"
#include "CmdMsg.h"
#include "Character.h" 
#include "RezasFunction.h"

#include "dofuncAdmin.h"
#include "DailyLogin.h"

int GetDaysInMonth() {
	time_t today =time(NULL) ;

	tm* t = localtime(&today);

	int month = t->tm_mon + 1;

	int year = t->tm_year+1900;


	int numberOfDays;

	if (month == 4 || month == 6 || month == 9 || month == 11)
		numberOfDays = 30;
	else if (month == 2)
	{
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (isLeapYear)
			numberOfDays = 29;
		else
			numberOfDays = 28;
	}
	else
		numberOfDays = 31;

	return numberOfDays;
}
int GetDaysInMonth(time_t fuck) {
	time_t today =fuck ;

	tm* t = localtime(&today);

	int month = t->tm_mon + 1;

	int year = t->tm_year+1900;


	int numberOfDays;

	if (month == 4 || month == 6 || month == 9 || month == 11)
		numberOfDays = 30;
	else if (month == 2)
	{
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (isLeapYear)
			numberOfDays = 29;
		else
			numberOfDays = 28;
	}
	else
		numberOfDays = 31;

	return numberOfDays;
}

DailyLogin::DailyLogin(): m_bInit(false) ,m_bOn(false)
{

}

DailyLogin::~DailyLogin()
{

}

bool DailyLogin::Init() 
{
	m_Rewards.clear();
	CDBCmd DBReward;
	DBReward.Init(&gserver->m_dbdata);

	std::string sql = "SELECT * FROM t_loginrewardnew order by a_day asc";

	DBReward.SetQuery(sql);
	if (!DBReward.Open())
		return false;

	if (DBReward.GetRecordCount() == 0)
	{
		LOG_INFO("No LoginRewardNew data Found");
		m_bOn = false;
		return false;
	}

	while(DBReward.MoveNext())
	{
		RewardData b;
		DBReward.GetRec("a_day", b.day);
		DBReward.GetRec("a_itemidx", b.itemidx);
		DBReward.GetRec("a_plus",b.plus);
		DBReward.GetRec("a_flag", b.flag);
		DBReward.GetRec("a_count", b.count);
		m_Rewards.push_back(b);
	}

	DBReward.Close();

	m_bInit = true;
	LOG_INFO("LoginRewardNew Init");
	
	return true;
}

void DailyLogin::ReloadTable() 
{
	
}


//  opcode 1 :  subtype : ETC 
void DailyLogin::DailyLoginMsg(CNetMsg::SP& msg)
{
	msg->Init(MSG_REZA);
	RefMsg(msg) << ((int)REZA_DAILY_LOGIN);
}

void DailyLogin::do_DailyLogin(CPC* ch, CNetMsg::SP& msg)
{
	msg->MoveFirst();

	unsigned int op;
	unsigned int subtype ;
	RefMsg(msg) >> op;
	RefMsg(msg) >> subtype;

	switch(subtype)
	{	
		case OpenD: // request open ui
		{

			//check if needs reset 
			time_t endofmon = time(NULL);
			
			tm * tieinfo;
			tieinfo = localtime(&endofmon);
			//timeinfo->tm_mon +=1;
			//if(timeinfo->tm_mon ==12)
			//timeinfo->tm_mon = 0;
			tieinfo->tm_mday= 1;
			tieinfo->tm_min = 0;
			tieinfo->tm_sec = 0;
			tieinfo->tm_hour= 0;
			endofmon = mktime(tieinfo);


			if(ch->m_DLdaycount < endofmon)
			{
				for(int i = 0 ; i < 35 ; i++)
				{
					ch->m_DLddaycheck[i]  =0 ;
				}
			}

			//
			CNetMsg::SP omsg(new CNetMsg); // open ui packet
			DailyLoginMsg(omsg);
			RefMsg(omsg) << ((int)OpenD);

			RefMsg(omsg) << ((int) ch->m_attendanceManager.getAccCount()); 
			RefMsg(omsg) << ((int) ch->m_attendanceManager.getAttendance());

			
			for (int i = 0 ; i < 35 ; i ++ ) 
			{
				RefMsg(omsg)<< (int)ch->m_DLddaycheck[i];
				RewardData* tempd = &gserver->m_DailyLogin.m_Rewards[i];
				RefMsg(omsg) << (int)tempd->itemidx;
				RefMsg(omsg) << (int) tempd->count;
				RefMsg(omsg) << (int) tempd->flag; 
				RefMsg(omsg) << (int) tempd->plus;

				//RefMsg(omsg) << ((int)85);
			}
			SEND_Q(omsg,ch->m_desc);
		
		}
		break;	
		case DClaim: 
			DayClaim(ch,msg) ; 
		break;
	}
}



void resetchreward(CPC* ch ) 
{
		ch->m_DLdaycount = time(NULL);
		
		for( int i = 0 ; i <  35 ; i ++ ) 
		{ 
			ch->m_DLddaycheck[i] = 0; 
		}
}

void DailyLogin::DayClaim(CPC* ch , CNetMsg::SP& msg) 
{ 


		//VARIABLES
	int DaysInMonth = GetDaysInMonth();  //	28-31

	time_t today = time(NULL);		// 
	tm* t = localtime(&today);

	int CurrentDay = t->tm_mday;   		//	1-31
	int remainder =  (CurrentDay  % 7 ); 	//		pass 1:1			pass 2: 2				pass 3: 6			pass 4: 0 
	int remainingdaysinweek = 7 - remainder;	//	pass 1: 6			pass 2: 5				pass 3: 1			pass 4: 0
	int currentweek = (CurrentDay- remainder) /7; //pass 1: 0			pass 2:	0				pass 3: 0			pass 4: 1
	

	int error = 0 ; 

	if(ch->m_DLddaycheck[CurrentDay-1] != 0 )
		error = 1; 

	
	if(error ==0 )
	{
		ch->m_DLddaycheck[CurrentDay-1] =  1 ;
		ch->m_DLdaycount = time(NULL);

		int sequential = 0; 
		for(int i = 0; i < 35; i ++) {
			
			if(i == CurrentDay-1)
			{
				switch(CurrentDay) 
				{
				case 28:
					if(sequential == i)
						giveDayReward( ch , CurrentDay-1); 
					else
						error=1;
					break;
				case 21:
				case 14:
				case 7:
					if(sequential >=6 )
						giveDayReward( ch , CurrentDay-1);
					else
						error=1;
					break;
				default:
						giveDayReward( ch , CurrentDay-1); 
					break;
				}
			}
			else{
				if(ch->m_DLddaycheck[i] == 1){
					sequential++;
				}
				else{
					sequential = 0;
				}
			}
		}
	}

	if(error == 1)
	{

		CNetMsg::SP omsg(new CNetMsg); // open ui packet
			DailyLoginMsg(omsg);
			RefMsg(omsg) << ((int)DLError);

			SEND_Q(omsg,ch->m_desc);
		/*CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_REZA);
		char buffer[255]  = {0};
			snprintf(buffer,255,"%s", _S(9339,"Not eligible" ) );
		
		RefMsg(rmsg) << buffer;
		RefMsg(rmsg) << SYSMSG_DIRTYELLOW; 
		RefMsg(rmsg) << 0;
	
		SEND_Q(rmsg, ch->m_desc) ;*/

	}


	
	 
} 

void DailyLogin::AttendanceFin(CPC* ch)
{ 

} 

void  DailyLogin::giveEpicReward(CPC* ch)
{

}

void DailyLogin::giveWeekReward(CPC* ch , int v)
{

}

void DailyLogin::giveDayReward(CPC* ch , int v )
{

	CItem * pItem = gserver->m_itemProtoList.CreateItem(
		m_Rewards[v].itemidx,
		-1,
		m_Rewards[v].plus,
		m_Rewards[v].flag,
		m_Rewards[v].count
		);

	if (ch->m_inventory.addItem(pItem))
	{
		GAMELOG 
		<< init("LOGINREWARDNEW", ch ) << "REWARD" 
		<< delim << ch->m_DLdaycount
		<< delim 
			<< itemlog(pItem) << end;
	}
}


