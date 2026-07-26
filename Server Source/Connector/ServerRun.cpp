#include "stdhdrs.h"

#include "Log.h"
#include "Server.h"
#include "../ShareLib/DBCmd.h"
#include <boost/format.hpp>

void CServer::Close()
{
	int i;
	i = 0;
	CDBCmd cmd;
	cmd.Init(&gserver.m_dbauth);

	std::string replaceQuery = boost::str(boost::format(
			"REPLACE INTO t_event_gomdori_count (a_server, a_count, a_updatedate) VALUES (%d, %d, NOW())")
										  % gserver.m_serverno % gserver.m_nEventGomdori2007StatusCurServer);

	cmd.SetQuery(replaceQuery);
	cmd.Update();

	// ������ ����Ʈ�� ��� �����
	cmd.BeginTrans();

	std::string deleteQuery = boost::str(boost::format(
			"DELETE FROM t_ct_limit WHERE a_server = %d ")
										 % gserver.m_serverno);
	cmd.SetQuery(deleteQuery);
	cmd.Update();

	// ���� ��ǰ�� �ȸ� ������ ��� ����
	bool bSuccess = true;
	CServer::map_limitsell_t::iterator it = gserver.m_limitSell.begin();
	CServer::map_limitsell_t::iterator endit = gserver.m_limitSell.end();
	std::string insertQuery = "INSERT INTO t_ct_limit (a_server, a_ct_id, a_sell) VALUES ";

	for(; it != endit; ++it)
	{
		CLimitSell* limit = it->second;
		insertQuery += boost::str(boost::format(
									  "( %d, %d, %d),") % gserver.m_serverno % limit->GetIndex() % limit->GetSell());
	}

	int pos = insertQuery.rfind(",");
	insertQuery.erase(pos);

	cmd.SetQuery(insertQuery);

	if( !cmd.Update() )
	{
		bSuccess = false;
	}

	if( bSuccess )
	{
		cmd.Commit();
		GAMELOG << init("SYSTEM")
				<< "t_ct_limt UPDATED" << end;
	}
	else
	{
		cmd.Rollback();
		GAMELOG << init("SYSTEM")
				<< "t_ct_limit INSERT FAILED ROLLBACK" << end;
	}

	CDescriptor* d;
	CDescriptor* dNext = m_desclist;

	while ((d = dNext))
	{
		dNext = d->m_pNext;
		CloseSocket(d);
	}

	GAMELOG << init("SYSTEM") << "Closing all sockets." << end;

	InitUserData();

	GAMELOG << init("SYSTEM") << "Normal termination of game." << end;

	LOG_INFO("Normal termination of game.");
}

// This function is called approximately every 1 second
void CServer::HeartBeat()
{
	static int _time_to_db_ping = 0;
	static int _time_to_stale_check = 0;

	SavePlayersCount();

	if (_time_to_db_ping >= 15) // 15 seconds
	{
		_time_to_db_ping = 0;
		mysql_ping(&m_dbauth);
		mysql_ping(&m_dbuser);
	}
	else
	{
		_time_to_db_ping++;
	}

	// Stale session cleanup: every 60 seconds, check for sessions older than 24 hours
	if (_time_to_stale_check >= 60)
	{
		_time_to_stale_check = 0;
		const int STALE_SESSION_TIMEOUT = 900; // 15 minutes in seconds
		time_t now;
		time(&now);

		for (int s = 0; s < m_maxSubServer; s++)
		{
			for (int i = 0; i <= m_userList[s].m_last; i++)
			{
				CUser* user = m_userList[s].m_users[i];
				if (user && user->m_state == CONN_PLAYING)
				{
					int elapsed = (int)(now - user->m_timestamp);
					if (elapsed > STALE_SESSION_TIMEOUT)
					{
						GAMELOG << init("STALE_SESSION", user->m_name)
								<< "Auto-purging stale session after" << delim << elapsed << delim << "seconds"
								<< end;
						ProcessLogout(user);
					}
				}
			}
		}
	}
	else
	{
		_time_to_stale_check++;
	}
	struct tm tmCur = NOW();
	int nTimeDiff = tmCur.tm_min - gserver.m_nEventGomdori2007LastUpdate;
	if (nTimeDiff < 0)
		nTimeDiff += 60;
	if (nTimeDiff >= 5)
	{
		gserver.m_nEventGomdori2007LastUpdate = tmCur.tm_min;
		CDBCmd cmd;
		cmd.Init(&gserver.m_dbauth);
		std::string replaceQuery = boost::str(boost::format(
				"REPLACE INTO t_event_gomdori_count (a_server, a_count, a_updatedate) VALUES (%d, %d, NOW())")
											  % gserver.m_serverno % gserver.m_nEventGomdori2007StatusCurServer);
		cmd.SetQuery( replaceQuery );
		cmd.Update();
	}

	struct tm currentTime = NOW();
	int nXMasTreeTimeDiff = currentTime.tm_min - gserver.m_nEventXmasTreeLastUpdate;
	if (nXMasTreeTimeDiff < 0)
		nXMasTreeTimeDiff += 60;
	if ( nXMasTreeTimeDiff >= 5)
	{
		gserver.m_nEventXmasTreeLastUpdate = currentTime.tm_min;
		CDBCmd cmd;
		cmd.Init(&gserver.m_dbauth);
		std::string replaceQuery = boost::str(boost::format(
				"REPLACE INTO t_event_xmastree_point (a_server, a_point,  a_lastupdate) VALUES (%d, %d, NOW())")
											  % gserver.m_serverno % gserver.m_unEventXmasTreePoint);
		cmd.SetQuery( replaceQuery );
		cmd.Update();
	}

	TimerToGameServer();
}
