#include "AutoBuffer.h"
#include "stdhdrs.h"
#include "Server.h"
#include "dofuncAdmin.h"

AutoBuffSystem::AutoBuffSystem() : m_bOn(false), lastTime(0), m_iLoopTimeSeconds(600),
m_bInit(false)
{
}

AutoBuffSystem::~AutoBuffSystem() {
}

bool AutoBuffSystem::Init() {
	
	CDBCmd DBBuffs;
	DBBuffs.Init(&gserver->m_dbdata);

	std::string sql = "SELECT * FROM t_autobuffs WHERE a_enable=1 and a_type = 0";

	DBBuffs.SetQuery(sql);
	if (!DBBuffs.Open())
		return false;

	if (DBBuffs.GetRecordCount() == 0)
	{
		LOG_INFO("No Active Buffs Found");
		m_bOn = false;
		return false;
	}

	while(DBBuffs.MoveNext())
	{
		BuffData b;
		DBBuffs.GetRec("a_level", b.level);
		DBBuffs.GetRec("a_id", b.skillID);
		m_buffs.push_back(b);
	}

	m_bInit = true;
	LOG_INFO("AutoBuffs System - Started!");
	return true;
}

void AutoBuffSystem::TurnOff() {
	m_bOn = false;
	LOG_INFO("Buffs OFF!");
}

void AutoBuffSystem::TurnOn() {
	m_bOn = true;
	LOG_INFO("Buffs ON!");
}
int AutoBuffSystem::SetTime(int mins) {
	if ((mins * 60 ) >= 60)
	{
		m_iLoopTimeSeconds= mins*60;
		return m_iLoopTimeSeconds;
	}
	m_iLoopTimeSeconds = 60;
	return m_iLoopTimeSeconds; 

}
void AutoBuffSystem::TickSystem() {
	if(!m_bOn)
		return;

	// Get the current time
	time_t now;
	time(&now);

	int dif = difftime(now, lastTime);
	
	if(dif < m_iLoopTimeSeconds)
		return;

	char* buffer = (char*)malloc(256);
	memset(buffer, 0, 256);

	std::vector<std::string> strs;

	for(int i = 0; i < m_buffs.size(); i++) {
		sprintf(buffer, "%d %d", m_buffs[i].skillID, m_buffs[i].level);
		do_GMGodBless(0, buffer, strs);
		memset(buffer, 0, 256);
	}

	free(buffer);
	LOG_INFO("Finish buffing Players!");
	lastTime = now;
}

void AutoBuffSystem::ReloadTable() {
	m_bOn = false;
	m_buffs.clear();
	Init();
	m_bOn = true;
}