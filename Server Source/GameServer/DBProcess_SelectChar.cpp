#define __DB_PROCESS_SELECT_CHAR_CPP__

#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include "stdhdrs.h"

#include "Server.h"
#include "CmdMsg.h"
#include "EventProcessWithThread.h"
#include "../ShareLib/DBCmd.h"
#include "doFunc.h"
#include "attendanceManager.h"

#include "DBManager.h"
#include "DescManager.h"

#include "SyndicateManager.h"

#ifdef PREMIUM_CHAR
#include "PremiumChar.h"
#endif

#include "Artifact_Manager.h"
#include "../ShareLib/packetType/ptype_old_do_title.h"
#ifndef _WIN64 // reza linux wtf
#include "Character.h"
#endif

typedef boost::tokenizer<boost::char_separator<char> > stokenizer;
static boost::char_separator<char> sep(" ", NULL, boost::drop_empty_tokens);

//XX ĳ���ͼ��� 3
void DBProcess::SelectChar( boost::any& argv )
{
	selectchar_t data = boost::any_cast<selectchar_t>(argv);
	LONGLONG seq_index = boost::tuples::get<0>(data);
	int& m_index = boost::tuples::get<1>(data);
	int& char_index = boost::tuples::get<2>(data);
	int& m_playmode = boost::tuples::get<3>(data);
	std::string& m_proSite = boost::tuples::get<4>(data);
	std::string& user_id = boost::tuples::get<5>(data);
	void* guild = boost::tuples::get<6>(data);

	int table_no = char_index % 10;
	int m_notice[MAX_NOTICE] = {0,};			//�̺�Ʈ ���� (�ִ� 5��), main thread�� ���������

	CDBCmd dbChar;
	dbChar.Init(char_db_.getMYSQL());

	if (char_index <= 0) return; //crash fix

	std::string select_charactesr_query = boost::str(boost::format(
			"SELECT * FROM t_characters WHERE a_user_index=%1% AND a_server=%2% AND a_index=%3%")
										  % m_index % gserver->m_serverno % char_index);
	select_charactesr_query += " AND a_enable=1 LIMIT 1";

	dbChar.SetQuery(select_charactesr_query.c_str());
	dbChar.Open();

	if (dbChar.MoveNext() == false)
	{
		LOG_ERROR("query erro : %s", select_charactesr_query.c_str());
		return;
	}

	int nDeleteDelay = 0;
	dbChar.GetRec("a_deletedelay", nDeleteDelay);
	if (nDeleteDelay != 0)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		FailMsg(rmsg, MSG_FAIL_DB_DELETE_DELAY_CHAR);
		SendMessageToClient(seq_index, m_index, rmsg);
		return;
	}

	CPC* pChar = new CPC;

	pChar->m_first_inmap = true;
	pChar->m_guildInfo = NULL;

	dbChar.GetRec("a_name", pChar->m_name, true);
	dbChar.GetRec("a_nick", pChar->m_nick, true);
	dbChar.GetRec("a_index",			pChar->m_index);
	dbChar.GetRec("a_level",			pChar->m_level);
	dbChar.GetRec("a_level_original",	pChar->m_level_original);
	dbChar.GetRec("a_skill_point",		pChar->m_skillPoint);
	dbChar.GetRec("a_admin",			pChar->m_admin);
	if (pChar->m_admin >= 1)
		pChar->m_gpsManager.setIsGpsInterrupt(true);
#ifdef REZABOT
	pChar->m_botting = 0;
#endif 
	dbChar.GetRec("a_was_x",			GET_X(pChar));
	dbChar.GetRec("a_was_z",			GET_Z(pChar));
	dbChar.GetRec("a_was_r",			GET_R(pChar));
	dbChar.GetRec("a_blood_point",		pChar->m_bloodPoint);
#ifdef PRESTIGE_SYSTEM
	//dbChar.GetRec("a_prestige",			pChar->m_prestige);
	dbChar.GetRec("a_prestige_level", pChar->m_prestigeLevel);
	dbChar.GetRec("a_prestige_points", pChar->m_prestigePoints);
	dbChar.GetRec("a_prestige_premium", pChar->m_prestigePremium);
#endif
	dbChar.GetRec("a_jailed_count", pChar->m_jailed_count);
	dbChar.GetRec("a_jailed_time", pChar->m_jailed_time);
	dbChar.GetRec("a_jailed", pChar->m_jailed);
	LONGLONG tnas = 0;
	dbChar.GetRec("a_nas",				tnas);
	pChar->m_inventory.InitMoney(tnas);

	if( pChar->m_skillPoint < 0 )
		pChar->m_skillPoint = 0;

	dbChar.GetRec("a_job",				pChar->m_job);
	dbChar.GetRec("a_job2",				pChar->m_job2);

#ifdef DAILY_LOGIN
	
	dbChar.GetRec("a_day_counter", pChar->m_DLdaycount);

	std::string colval = "-1 -1 -1 -1";
	dbChar.GetRec("a_weeks_concurrent",	colval);
	sscanf(colval.c_str(),"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d"
		,&(pChar->m_DLddaycheck[0]),&(pChar->m_DLddaycheck[1]),&(pChar->m_DLddaycheck[2]),&(pChar->m_DLddaycheck[3]),&(pChar->m_DLddaycheck[4]) ,&(pChar->m_DLddaycheck[5]) ,&(pChar->m_DLddaycheck[6])
		,&(pChar->m_DLddaycheck[7]),&(pChar->m_DLddaycheck[8]),&(pChar->m_DLddaycheck[9]),&(pChar->m_DLddaycheck[10]),&(pChar->m_DLddaycheck[11]) ,&(pChar->m_DLddaycheck[12]) ,&(pChar->m_DLddaycheck[13])
		,&(pChar->m_DLddaycheck[14]),&(pChar->m_DLddaycheck[15]),&(pChar->m_DLddaycheck[16]),&(pChar->m_DLddaycheck[17]),&(pChar->m_DLddaycheck[18]) ,&(pChar->m_DLddaycheck[19]) ,&(pChar->m_DLddaycheck[20])
		,&(pChar->m_DLddaycheck[21]),&(pChar->m_DLddaycheck[22]),&(pChar->m_DLddaycheck[23]),&(pChar->m_DLddaycheck[24]),&(pChar->m_DLddaycheck[25]) ,&(pChar->m_DLddaycheck[26]) ,&(pChar->m_DLddaycheck[27])
		,&(pChar->m_DLddaycheck[28]),&(pChar->m_DLddaycheck[29]),&(pChar->m_DLddaycheck[30]),&(pChar->m_DLddaycheck[31]),&(pChar->m_DLddaycheck[32]) ,&(pChar->m_DLddaycheck[33]) ,&(pChar->m_DLddaycheck[34])
		
		
		);
	for(int i = 0 ; i < 35 ; i++ ){
		if(pChar->m_DLddaycheck[i]> 1 || pChar->m_DLddaycheck[i] < 0){

			pChar->m_DLddaycheck[i] = 0;
		}
	}

#endif

#ifdef ENABLE_SUBJOB
	dbChar.GetRec("a_subjob",			pChar->m_jobSub);
	pChar->m_jobSub = 1; //dethunter12 so the user can use merchant items without being a merchant automatic merchant
#endif

	dbChar.GetRec("a_hair_style",		pChar->m_hairstyle);
	dbChar.GetRec("a_face_style",		pChar->m_facestyle);
	dbChar.GetRec("a_exp",				pChar->m_exp);
	dbChar.GetRec("a_exp_original",		pChar->m_exp_original);
	dbChar.GetRec("a_color_name",		pChar->m_color_name);

#ifdef BATTLE_PASS_SYSTEM
	dbChar.GetRec("a_battle_pass_level",		pChar->m_battlePassLevel);
	dbChar.GetRec("a_battle_pass_points",		pChar->m_battlePassPoints);
	dbChar.GetRec("a_battle_pass_premium",		pChar->m_battlePassPremium);
#endif

	dbChar.GetRec("a_str",				pChar->m_dbStr);
	pChar->m_str = pChar->m_dbStr;
	dbChar.GetRec("a_dex",				pChar->m_dbDex);
	pChar->m_dex = pChar->m_dbDex;
	dbChar.GetRec("a_int",				pChar->m_dbInt);
	pChar->m_int = pChar->m_dbInt;
	dbChar.GetRec("a_con",				pChar->m_dbCon);
	pChar->m_con = pChar->m_dbCon;
	dbChar.GetRec("a_statpt_remain",	pChar->m_statpt_remain);
	dbChar.GetRec("a_statpt_str",		pChar->m_statpt_str);
	dbChar.GetRec("a_statpt_dex",		pChar->m_statpt_dex);
	dbChar.GetRec("a_statpt_int",		pChar->m_statpt_int);
	dbChar.GetRec("a_statpt_con",		pChar->m_statpt_con);
	dbChar.GetRec("a_hp",				pChar->m_hp);
	pChar->m_tempHP = pChar->m_hp;
	dbChar.GetRec("a_max_hp",			pChar->m_dbHP);
	dbChar.GetRec("a_mp",				pChar->m_mp);
	pChar->m_tempMP = pChar->m_mp;
	dbChar.GetRec("a_max_mp",			pChar->m_dbMP);
	dbChar.GetRec("a_ep",				pChar->m_ep);
	dbChar.GetRec("a_silence_pulse",	pChar->m_silencePulse);
	pChar->m_silencePulse += gserver->m_pulse;
	dbChar.GetRec("a_pkpenalty",		pChar->m_pkPenalty);
	dbChar.GetRec("a_pkcount",			pChar->m_pkCount);
	dbChar.GetRec("a_pkrecover",		pChar->m_pkRecoverPulse);
	dbChar.GetRec("a_pkpenaltyhp",		pChar->m_pkPenaltyHP);
	dbChar.GetRec("a_pkpenaltymp",		pChar->m_pkPenaltyMP);
	dbChar.GetRec("a_guildindate",		pChar->m_guild_in_date);
	dbChar.GetRec("a_pluseffect_option",	pChar->m_plusEffect);
	dbChar.GetRec("a_loseexp",			pChar->m_loseexp);
	dbChar.GetRec("a_losesp",			pChar->m_losesp);
	dbChar.GetRec("a_reborn",			pChar->m_reborn);

	dbChar.GetRec("a_wins",				pChar->m_wins);
	dbChar.GetRec("a_loses",			pChar->m_loses);
	dbChar.GetRec("a_honor",			pChar->m_honor);
	dbChar.GetRec("a_stats_addition",	pChar->m_stats_addition);

	dbChar.GetRec("a_phoenix",			pChar->m_bPhoenix_Char);
	dbChar.GetRec("a_premium_phoenix_active", pChar->m_bPremium_Phoenix);
#ifdef DEMIGOD
	dbChar.GetRec("a_demigod_active",	pChar->m_DemiGod);
#endif
	dbChar.GetRec("a_title_index",		pChar->m_nCurrentTitle);

#ifdef NO_CHATTING
	dbChar.GetRec("a_flag",				pChar->m_nflag);
#endif

	dbChar.GetRec("a_newtuto_complete",	pChar->m_newtutoComplete);

	dbChar.GetRec("a_exp_weekly",		pChar->m_exp_weekly);

	dbChar.GetRec("a_autopickup",		pChar->m_autopickup);
	dbChar.GetRec("a_autoigni",			pChar->m_autoigni);
	dbChar.GetRec("a_autosell",			pChar->m_autosell);

	// event fields
	dbChar.GetRec("a_event_summon_count",	pChar->m_eventSummonCount);

	int nZone, nArea, nYlayer;
	dbChar.GetRec("a_was_zone",			nZone);
	dbChar.GetRec("a_was_area",			nArea);
	dbChar.GetRec("a_was_yLayer",		nYlayer);

	int	lcstamptime;
	dbChar.GetRec("a_lcdatestamp", lcstamptime);

	if(pChar->m_ep > 0 && (lcstamptime + (60 * 10) < gserver->m_nowseconds))
	{
		pChar->m_ep = -1;
	}

#ifdef QUICK_PANEL
	//check db for exisiting data
	CDBCmd cmdquickpanel;
	cmdquickpanel.Init(char_db_.getMYSQL());
	char sel_quickpanel[255];
	sprintf(sel_quickpanel, "SELECT * FROM t_cloud_quick_panel where a_index = %d", pChar->m_index);
	cmdquickpanel.SetQuery(sel_quickpanel);
	cmdquickpanel.Open();

	if (cmdquickpanel.MoveNext() == false)
	{
		//init db with default data for this user
		CDBCmd cmdInitquickpanel;
		cmdInitquickpanel.Init(char_db_.getMYSQL());
		char init_quickpanel[255];
		sprintf(init_quickpanel, "insert into t_cloud_quick_panel  (a_index) values (%d); ", pChar->m_index);
		cmdInitquickpanel.SetQuery(init_quickpanel);
		cmdInitquickpanel.Update();

		//set default data in memory
		for (int i = 0; i < 25; i++)
		{
			pChar->m_QuickPanelBtnType[i] = -1;
			pChar->m_QuickPanelBtnIdx[i] = -1;
			//LOG_ERROR("CLOUD PANEL FIRST : %d : %d", pChar->m_QuickPanelBtnType[i], pChar->m_QuickPanelBtnIdx[i]);
		}
	}
	else
	{
		char tbuf[256];
		// has db info already so use it directly in memory
		//for(int i = 0 ; i < 25; i ++ ) 
		{
			int slot = 0;
			const char* pch = cmdquickpanel.GetRec("a_panel");

			while (*pch && slot < 25)
			{
				// slot type
				pch = AnyOneArg(pch, tbuf);
				pChar->m_QuickPanelBtnType[slot] = atoi(tbuf);

				pch = AnyOneArg(pch, tbuf);
				pChar->m_QuickPanelBtnIdx[slot] = atoi(tbuf);

				//LOG_ERROR("CLOUD PANEL : %d : %d", pChar->m_QuickPanelBtnType[slot], pChar->m_QuickPanelBtnIdx[slot]);
				slot++;
			}
		}
	}

#endif
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS

	//check db for exisiting data
	CDBCmd cmdPartyDungeonStat;
	cmdPartyDungeonStat.Init(char_db_.getMYSQL());
	char sel_PartyDungeonStat[255];
	sprintf(sel_PartyDungeonStat, "SELECT * FROM t_cloud_party_dungeon where a_index = %d", pChar->m_index);
	cmdPartyDungeonStat.SetQuery(sel_PartyDungeonStat);
	cmdPartyDungeonStat.Open();

	if (cmdPartyDungeonStat.MoveNext() == false)
	{
		//init db with default data for this user
		CDBCmd cmdInitPartyDungeon;
		cmdInitPartyDungeon.Init(char_db_.getMYSQL());
		char init_PartyDungeon[255];
		sprintf(init_PartyDungeon, "insert into t_cloud_party_dungeon  (a_index) values (%d); ", pChar->m_index);
		cmdInitPartyDungeon.SetQuery(init_PartyDungeon);
		cmdInitPartyDungeon.Update();

		//set default data in memory
		for (int i = 0; i < 5; i++)
		{
			pChar->m_PartyDGCompleteData[i] = 0;
			pChar->m_PartyDGTitleRewardData[i] = 0;

		}
	}
	else
	{
		// has db info already so use it directly in memory
		for (int i = 0; i < 5; i++)
		{
			char buffer[255] = { 0 };
			sprintf(buffer, "a_completetimes%d", i);
			cmdPartyDungeonStat.GetRec(buffer, pChar->m_PartyDGCompleteData[i]);

			sprintf(buffer, "a_titlereward%d", i);
			cmdPartyDungeonStat.GetRec(buffer, pChar->m_PartyDGTitleRewardData[i]);
		}
	}

#endif

#ifdef KILLMEDALS
	{
		// INSPECT LATER
		//check db for exisiting data
		CDBCmd cmdKillStat;
		cmdKillStat.Init(char_db_.getMYSQL());
		char sel_KillStat[255];
		sprintf(sel_KillStat, "SELECT * FROM t_killmedalstats where a_index = %d", pChar->m_index);
		cmdKillStat.SetQuery(sel_KillStat);
		cmdKillStat.Open();

		if (cmdKillStat.MoveNext() == false)
		{
			//init db with default data for this user
			CDBCmd cmdInitKillMedal;
			cmdInitKillMedal.Init(char_db_.getMYSQL());
			char init_KillMedal[255];
			sprintf(init_KillMedal, "insert into t_killmedalstats  (a_index) values (%d); ", pChar->m_index);
			cmdInitKillMedal.SetQuery(init_KillMedal);
			cmdInitKillMedal.Update();

			//set default data in memory
			for (int i = 0; i < OVERKILLSTART - 1; i++)
			{
				pChar->m_KillMedalData[i] = 0;


			}
			pChar->m_KillOverKillStreak = 0;
		}
		else
		{
			// has db info already so use it directly in memory
			for (int i = 0; i < OVERKILLSTART - 1; i++)
			{
				char buffer[255] = { 0 };
				sprintf(buffer, "a_medal%d", i);
				cmdKillStat.GetRec(buffer, pChar->m_KillMedalData[i]);

			}
			cmdKillStat.GetRec("a_overkillstreak", pChar->m_KillOverKillStreak);
		}



	}
#endif 
	int attendance = 0;
	dbChar.GetRec("a_attendance_assure", attendance);
	pChar->m_attendanceManager.setUseAssure(attendance);

	CDBCmd dbGuild;
	dbGuild.Init(char_db_.getMYSQL());

	std::string select_guildpoint_query = boost::str(boost::format(
			"SELECT * FROM t_characters_guildpoint WHERE a_char_index = %1%") % char_index);
	dbGuild.SetQuery(select_guildpoint_query);
	dbGuild.Open();
	if (!dbGuild.MoveNext())
	{
		std::string insert_guildpoint_query = boost::str(boost::format(
				"INSERT t_characters_guildpoint(a_char_index) VALUES (%1%)") % char_index);
		dbGuild.SetQuery(insert_guildpoint_query.c_str());
		if( !dbGuild.Update() )
			return;
		pChar->m_GuildExp = 0;
		pChar->m_GuildFame = 0;
	}
	else
	{
		dbGuild.GetRec( "a_guild_exp", pChar->m_GuildExp );
		dbGuild.GetRec( "a_guild_fame", pChar->m_GuildFame );
	}

	if (m_playmode != MSG_LOGIN_RE)
	{
		nZone = -1;
		nArea = -1;
		nYlayer = -1;
	}

	bool bValidZone = false;
	CZone* pRemoteZone = NULL;
	// ���� ã�Ƽ�
	CZone* pZone = gserver->FindZone(nZone);
	if (pZone != NULL)
	{
		// ���� ������ ����
		if (pZone->m_bRemote)
			pRemoteZone = pZone;
		bValidZone = true;
	}
	if (!bValidZone)
	{
		// �߸��� �� ��ȣ�϶�
		nZone = ZONE_START;		// TODO : ���� ���� ������/�������� �ٸ� ��� ���� �ʿ�
		
		if(pChar->m_job == JOB_NIGHTSHADOW)
		 	nZone = ZONE_EGEHA;
		
		pZone = gserver->FindZone(nZone);
		// ���� ���� ã�Ƽ�
		bValidZone = true;
	}

	if (!bValidZone)
		return;

	// ��ȿ�� �˻�
	if (pRemoteZone == NULL)
	{
		if (pZone == NULL)
		{
			// ���� �� ����
			pChar->m_pZone		= gserver->FindZone(ZONE_START);
			pChar->m_pArea		= pChar->m_pZone->m_area;
			GET_YLAYER(pChar)	= pChar->m_pZone->m_zonePos[0][0];
			GET_R(pChar)		= 0.0f;
			int nTry = 10;

			while (nTry--)
			{
				GET_X(pChar)		= GetRandom(pChar->m_pZone->m_zonePos[0][1], pChar->m_pZone->m_zonePos[0][3]) / 2.0f;
				GET_Z(pChar)		= GetRandom(pChar->m_pZone->m_zonePos[0][2], pChar->m_pZone->m_zonePos[0][4]) / 2.0f;
				if ( !(pChar->m_pArea->GetAttr(GET_YLAYER(pChar), GET_X(pChar), GET_Z(pChar)) & MATT_UNWALKABLE) )
					break;
			}
		}
		// yLayer ����
		else if (nYlayer < 0 || nYlayer > ((pZone->m_countY - 1) * 2) || pZone->m_countArea != 1)
		{
			// ���� ����� ����
			int nearZone;
			int nearPos;
			pZone = gserver->FindNearestZone(nZone, GET_X(pChar), GET_Z(pChar), &nearZone, &nearPos);
			if (pZone == NULL)
				pZone = gserver->FindNearestZone(ZONE_START, -1.0f, -1.0f, &nearZone, &nearPos);

			pChar->m_pZone		= pZone;
			pChar->m_pArea		= pChar->m_pZone->m_area;
			GET_YLAYER(pChar)	= pChar->m_pZone->m_zonePos[nearPos][0];
			GET_R(pChar)		= 0.0f;
			int nTry = 10;
			while (nTry--)
			{
				GET_X(pChar)		= GetRandom(pChar->m_pZone->m_zonePos[nearPos][1], pChar->m_pZone->m_zonePos[nearPos][3]) / 2.0f;
				GET_Z(pChar)		= GetRandom(pChar->m_pZone->m_zonePos[nearPos][2], pChar->m_pZone->m_zonePos[nearPos][4]) / 2.0f;
				if ( !(pChar->m_pArea->GetAttr(GET_YLAYER(pChar), GET_X(pChar), GET_Z(pChar)) & MATT_UNWALKABLE) )
					break;
			}
		}
		else
		{
			// ���� ��ġ �״��
			if (pZone == NULL)
			{
				pZone = gserver->FindZone(ZONE_START);
				nYlayer = 0;
			}
			pChar->m_pZone		= pZone;
			pChar->m_pArea		= pChar->m_pZone->m_area;
			GET_YLAYER(pChar)	= nYlayer;
		}

		// ���� ���̸� ���� ������ �ٽ� �����϶�� �ϰ� �ѱ��
		if (pChar->m_pZone->m_bRemote)
			pRemoteZone = gserver->FindZone(pChar->m_pZone->m_index);
		else
			pRemoteZone = NULL;
	}

	if (pRemoteZone != NULL)
	{
		// �ٸ� ������ �̵��� �� �� �ֵ��� �޽��� ����
		CNetMsg::SP rmsg(new CNetMsg);
		DBOtherServerMsg(rmsg, pRemoteZone->m_index, pRemoteZone->m_remoteIP, pRemoteZone->m_remotePort);
		SendMessageToClient(seq_index, m_index, rmsg);

		// main thread���� ���������� �� �ֵ��� ��ġ
		EventProcessForDB::moveOtherZone retVal;
		retVal.m_index = m_index;
		retVal.m_seq_index = seq_index;
		EventProcessForDB::instance()->pushSelectCharacterOtherZone(retVal);

		// ���ư������� ���� ������ CPC* �� ������
		delete pChar;

		return;
	}

	char tbuf[256];
	static CLCString skillIndex(256);
	static CLCString skillLevel(256);
	const char* pIndex = skillIndex;
	const char* pLevel = skillLevel;
	dbChar.GetRec("a_active_skill_index", skillIndex);
	dbChar.GetRec("a_active_skill_level", skillLevel);
	while (*pIndex && *pLevel)
	{
		int i, l;
		pIndex = AnyOneArg(pIndex, tbuf);
		i = atoi(tbuf);
		pLevel = AnyOneArg(pLevel, tbuf);
		l = atoi(tbuf);
		CSkill* s = gserver->m_skillProtoList.Create(i, l);
		if (s)
		{
			if (s->m_proto->IsActive())
				pChar->m_activeSkillList.Add(s);
			else if (s->m_proto->IsPassive())
				pChar->m_passiveSkillList.Add(s);
			else
				pChar->m_etcSkillList.Add(s);
		}
	}

	skillIndex = "";
	skillLevel = "";
	pIndex = skillIndex;
	pLevel = skillLevel;
	dbChar.GetRec("a_passive_skill_index", skillIndex);
	dbChar.GetRec("a_passive_skill_level", skillLevel);
	while (*pIndex && *pLevel)
	{
		int i, l;
		pIndex = AnyOneArg(pIndex, tbuf);
		i = atoi(tbuf);
		pLevel = AnyOneArg(pLevel, tbuf);
		l = atoi(tbuf);
		CSkill* s = gserver->m_skillProtoList.Create(i, l);
		if (s)
		{
			if (s->m_proto->IsActive())
				pChar->m_activeSkillList.Add(s);
			else if (s->m_proto->IsPassive())
				pChar->m_passiveSkillList.Add(s);
			else
				pChar->m_etcSkillList.Add(s);
		}
	}
	skillIndex = "";
	skillLevel = "";
	pIndex = skillIndex;
	pLevel = skillLevel;
	dbChar.GetRec("a_etc_skill_index", skillIndex);
	dbChar.GetRec("a_etc_skill_level", skillLevel);
	while (*pIndex && *pLevel)
	{
		int i, l;
		pIndex = AnyOneArg(pIndex, tbuf);
		i = atoi(tbuf);
		pLevel = AnyOneArg(pLevel, tbuf);
		l = atoi(tbuf);
		CSkill* s = gserver->m_skillProtoList.Create(i, l);
		if (s)
		{
			if (s->m_proto->IsActive())
				pChar->m_activeSkillList.Add(s);
			else if (s->m_proto->IsPassive())
				pChar->m_passiveSkillList.Add(s);
			else
				pChar->m_etcSkillList.Add(s);
		}
	}

	skillIndex = "";
	skillLevel = "";
	pIndex = skillIndex;
	pLevel = skillLevel;
	dbChar.GetRec("a_seal_skill_index", skillIndex);
	dbChar.GetRec("a_seal_skill_exp",	skillLevel);
	int nSeal = 0;
	while (*pIndex && *pLevel)
	{
		int i;
		LONGLONG l;
		pIndex = AnyOneArg(pIndex, tbuf);
		i = atoi(tbuf);
		pLevel = AnyOneArg(pLevel, tbuf);
		l = atoi(tbuf);

		CSkill* s = gserver->m_skillProtoList.Create(i);
		if (s && s->m_proto->IsSeal() && nSeal < MAX_SEAL_TYPE_SKILL)
		{
			pChar->m_sealSkillList.Add(s);
			pChar->m_sealSkillExp[nSeal].pSkill	= s;
			pChar->m_sealSkillExp[nSeal].nSkillIdx	= i;
			pChar->m_sealSkillExp[nSeal].llExp		= l;

			nSeal++;
		}
	}

	// �ش� ��ų�� ���� ��� load
	CDBCmd dbFactory;
	dbFactory.Init(char_db_.getMYSQL());

	std::string select_character_factory_query = boost::str(boost::format(
				"SELECT * FROM t_characters_factory WHERE a_char_idx = %1%") % char_index);
	dbFactory.SetQuery(select_character_factory_query.c_str());
	dbFactory.Open();
	if (dbFactory.MoveNext())
	{
		CLCString factoryIdx(2048);
		const char * pFactoryIdx;
		pFactoryIdx		= factoryIdx;
		dbFactory.GetRec("a_factory_idx", factoryIdx);

		int nIndex = 0;
		while (*pFactoryIdx)
		{
			pFactoryIdx = AnyOneArg(pFactoryIdx, tbuf);
			nIndex = atoi(tbuf);

			//if (!(*pIndex))
			//    break;

			CFactoryProto* f = gserver->m_factoryItemProtoList.Find(nIndex);
			pChar->m_listFactory.Add(f);
		}
	}

	//PASSIVE_SYSTEM
	//new 16-08-2022
	CDBCmd dbPassive;
	dbPassive.Init(char_db_.getMYSQL());

	std::string select_character_passive_query = boost::str(boost::format(
		"SELECT * FROM t_characters_passive WHERE a_char_index = %1%") % char_index);
	dbPassive.SetQuery(select_character_passive_query.c_str());
	dbPassive.Open();
	if (dbPassive.MoveNext())
	{
		CLCString passiveSlotPos(64);
		const char* pPassivePos;
		pPassivePos = passiveSlotPos;
		dbPassive.GetRec("a_passive_slot_pos", passiveSlotPos);

		CLCString passiveSlotIdx(64);
		const char* pPassiveIdx;
		pPassiveIdx = passiveSlotIdx;
		dbPassive.GetRec("a_passive_slot_id", passiveSlotIdx);

		CLCString passiveListIdx(64);
		const char* pPassiveListIdx;
		pPassiveListIdx = passiveListIdx;
		dbPassive.GetRec("a_passive_list", passiveListIdx);

		int nIndex = 0;
		int slot = 0;
		while (*pPassiveIdx)
		{
			pPassiveIdx = AnyOneArg(pPassiveIdx, tbuf);
			nIndex = atoi(tbuf);

			pPassivePos = AnyOneArg(pPassivePos, tbuf);
			slot = atoi(tbuf);

			CPassiveSystem* f = gserver->m_passiveSystemList.FindPassiveSkill(nIndex);
			if (f == NULL || slot == -1)
				continue;

			pChar->m_passiveSystemSlot.Add(slot, f->Copy(slot));
		}

		nIndex = 0;
		while (*pPassiveListIdx)
		{
			pPassiveListIdx = AnyOneArg(pPassiveListIdx, tbuf);
			nIndex = atoi(tbuf);

			CPassiveSystem* f = gserver->m_passiveSystemList.FindPassiveSkill(nIndex);
			if (f == NULL)
				continue;

			pChar->m_passiveSystemList.Add(f->m_index, f->Copy());
		}
	}
	
	/////////////////////
	// ����Ʈ �б�

	// �ϵ��ڵ� : Ʃ�丮�� ���� ��ŸƮ���� �ٲ��� �ϴ°�?
	bool bGotoTutorial = false;

	static CLCString		questIndex(256);
	static CLCString		questValue(256);
	static CLCString		questComplete(256);
	static CLCString		questAbandon(256);

	const char* pQIndex		= questIndex;
	const char* pQValue		= questValue;
	const char* pQComplete	= questComplete;
	const char* pQAbandon	= questAbandon;

	dbChar.GetRec("a_quest_index",		questIndex);
	dbChar.GetRec("a_quest_value",		questValue);
	dbChar.GetRec("a_quest_complete",	questComplete);
	dbChar.GetRec("a_quest_abandon",	questAbandon);

	// ���� �ʵ忡�� �б�, ���ο� ���̺����� �б�� ����
	int		nQuestIndex;
	char	nQuestState;
	int		nQuestValue[QUEST_MAX_CONDITION];
	int		nCompleteTime;
	int		nQuestFailValue;

	while (*pQIndex)
	{
		pQIndex = AnyOneArg(pQIndex, tbuf);
		nQuestIndex = atoi(tbuf);

		CQuest* pQuest = pChar->m_questList.AddQuest(nQuestIndex);
		if (pQuest == NULL)
		{
			for (int i = 0; *pQValue && i < QUEST_MAX_CONDITION; i++)
				pQValue = AnyOneArg(pQValue, tbuf);
			continue ;
		}

		// �ϵ��ڵ� : �̱۴���1 Ʃ�丮����
		if (pQuest->IsTutorialQuest())
			bGotoTutorial = true;

		for (int i = 0; *pQValue && i < QUEST_MAX_CONDITION; i++)
		{
			pQValue = AnyOneArg(pQValue, tbuf);
			int value = atoi(tbuf);
			pQuest->SetQuestValue(i, value);
		}

		pChar->m_questList.SetQuestState(pQuest, QUEST_STATE_RUN);
	}
	while (*pQComplete)
	{
		pQComplete = AnyOneArg(pQComplete, tbuf);
		nQuestIndex = atoi(tbuf);
		CQuest* pQuest = pChar->m_questList.AddQuest(nQuestIndex);
		if (pQuest)
			pChar->m_questList.SetQuestState(pQuest, QUEST_STATE_DONE);
	}
	while (*pQAbandon)
	{
		pQAbandon = AnyOneArg(pQAbandon, tbuf);
		nQuestIndex = atoi(tbuf);
		CQuest* pQuest = pChar->m_questList.AddQuest(nQuestIndex);
		if (pQuest)
			pChar->m_questList.SetQuestState(pQuest, QUEST_STATE_ABANDON);
	}


	/////////////////////
	// Special Skill�б�

	static CLCString strSSkill(256);
	const char* psskill = strSSkill;

	dbChar.GetRec("a_sskill", strSSkill);

	while (*psskill)
	{
		psskill = AnyOneArg(psskill, tbuf);
		int index = atoi(tbuf);
		psskill = AnyOneArg(psskill, tbuf);
		int level = atoi(tbuf);

		CSSkillProto* proto = gserver->m_sSkillProtoList.FindProto(index);

		if (!proto)
		{
			continue;
		}

		CSSkill* sskill = new CSSkill(proto, level);

		if (!sskill)
			continue;

		pChar->m_sSkillList.Add(sskill);
	}

// �̺�Ʈ ���̺� �б�
	dbChar.GetRec("a_etc_event", pChar->m_etcEvent);
	

	// ���ο� ���̺����� ����Ʈ �б�
	std::string select_questdata_query = boost::str(boost::format(
			"SELECT * FROM t_questdata%02d WHERE a_char_index=%d ORDER BY a_state, a_quest_index")
										 % table_no % pChar->m_index);
	dbChar.SetQuery(select_questdata_query.c_str());
	if (!dbChar.Open())
	{
		LOG_ERROR("DB ERROR : LOAD CHARACTER QUEST TABLE / char_index[%d] / query[%s] / error[%s]",
				  pChar->m_index, select_questdata_query.c_str(), mysql_error(dbChar.GetDbConn()));
	}
	else
	{
		int nLoopValue;
		while (dbChar.MoveNext())
		{
			dbChar.GetRec("a_quest_index",			nQuestIndex);
			dbChar.GetRec("a_state",				nQuestState);
			dbChar.GetRec("a_quest_failvalue",	nQuestFailValue);
			dbChar.GetRec("a_complete_time", nCompleteTime);

			CQuest* pQuest = pChar->m_questList.AddQuest(nQuestIndex);
			if (pQuest == NULL)
				continue ;

			// �ϵ��ڵ� : �̱۴���1 Ʃ�丮����
			if (nQuestState == QUEST_STATE_RUN && pQuest->IsTutorialQuest())
				bGotoTutorial = true;

			for (nLoopValue = 0; nQuestState == QUEST_STATE_RUN && nLoopValue < QUEST_MAX_CONDITION; nLoopValue++)
			{
				std::string tstr = boost::str(boost::format("a_value%d") % nLoopValue);
				dbChar.GetRec(tstr.c_str(), nQuestValue[nLoopValue]);
				pQuest->SetQuestValue(nLoopValue, nQuestValue[nLoopValue]);
			}

			pQuest->SetFailValue(nQuestFailValue);
			pQuest->SetCompleteTime(nCompleteTime);

			pChar->m_questList.SetQuestState(pQuest, nQuestState);

			if((pQuest->GetQuestProto()->m_failValue > 0) && nQuestFailValue < gserver->getNowSecond())
			{
				pChar->m_questList.DelQuest(pChar, pQuest); // Ÿ�� ���� ����Ʈ ���� (����Ʈ���� ����)
				continue;
			}

			if((pQuest->GetQuestProto()->m_type[1] == QTYPE_REPEAT_DAY))
			{
				if( pQuest->GetQuestState() == QUEST_STATE_DONE)
				{
					time_t nowtime;
					time(&nowtime);
					if( nowtime >= pQuest->GetCompleteTime() )
						pChar->m_questList.DelQuest(pChar, pQuest, QUEST_STATE_DONE ); // ���� ����Ʈ ���� (����Ʈ���� ����)
				}
			}
			else if ((pQuest->GetQuestProto()->m_type[1] == QTYPE_REPEAT_WEEK))
			{
				if (pQuest->GetQuestState() == QUEST_STATE_DONE)
				{
					time_t nowtime;
					time(&nowtime);
					if (nowtime >= pQuest->GetCompleteTime())
						pChar->m_questList.DelQuest(pChar, pQuest, QUEST_STATE_DONE); // 일일 퀘스트 실패 (리스트에서 삭제)
				}
			}
		}
	}

	std::string select_affinity_keep_query = boost::str(boost::format(
				"SELECT * FROM t_affinity_keep WHERE a_charidx = %1%") % pChar->m_index);
	dbChar.SetQuery(select_affinity_keep_query.c_str());
	if(!dbChar.Open()) {}
	else
	{
		while(dbChar.MoveNext())
		{
			int affinityidx, point;
			dbChar.GetRec("a_affinity_idx", affinityidx);
			dbChar.GetRec("a_point", point);

			if(!pChar->m_affinityList.AddAffinity(affinityidx, point))
			{
				// ģȭ�� �߰� ����
			}
		}

		std::string select_affinity_reward_step_query = boost::str(boost::format(
					"SELECT * FROM t_affinity_reward_step WHERE a_charidx = %1%") % pChar->m_index);
		dbChar.SetQuery(select_affinity_reward_step_query.c_str());
		if(!dbChar.Open()) {}
		else
		{
			while(dbChar.MoveNext())
			{
				int npcidx = 0, point = 0;
				dbChar.GetRec("a_npcidx", npcidx);
				dbChar.GetRec("a_reward_step", point);

				if(!pChar->m_affinityList.UpdateRewardPoint(npcidx, point))
				{
					// �������� ���� ������
				}
			}
		}
	}

	////////////////
	// ����ȿ�� �б�
	std::string select_assist_query = boost::str(boost::format(
										  "SELECT * FROM t_assist WHERE a_char_index=%1%") % pChar->m_index);
	dbChar.SetQuery(select_assist_query.c_str());
	if (dbChar.Open() && dbChar.MoveFirst())
	{
		const char* p1;
		const char* p2;
		const char* p3;
		const char* p4;
		const char* p5;
		const char* p6;
		const char* p7;
		const char* p8;

		int nitem;
		int nskill;
		int nlevel;
		int nremain;
		int nremaincount;
		bool bHit[MAX_SKILL_MAGIC];
		const CSkillProto* sp;

		CLCString assistitem(256);
		CLCString assistskill(256);
		CLCString assistlevel(256);
		CLCString assistremain(256);
		CLCString assistremaincount(256);
		CLCString assisthit0(256);
		CLCString assisthit1(256);
		CLCString assisthit2(256);
		char m_t_buf[512];

		// help
		dbChar.GetRec("a_help_item", assistitem);
		p1 = assistitem;
		dbChar.GetRec("a_help_skill", assistskill);
		p2 = assistskill;
		dbChar.GetRec("a_help_level", assistlevel);
		p3 = assistlevel;
		dbChar.GetRec("a_help_remain", assistremain);
		p4 = assistremain;
		dbChar.GetRec("a_help_hit0", assisthit0);
		p5 = assisthit0;
		dbChar.GetRec("a_help_hit1", assisthit1);
		p6 = assisthit1;
		dbChar.GetRec("a_help_hit2", assisthit2);
		p7 = assisthit2;
		dbChar.GetRec("a_help_remaincount", assistremaincount);
		p8 = assistremaincount;

		bool bStop = false;
		while (!bStop)
		{
			*m_t_buf = '\0';
			p1 = AnyOneArg(p1, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			nitem = atoi(m_t_buf);
			*m_t_buf = '\0';
			p2 = AnyOneArg(p2, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			nskill = atoi(m_t_buf);
			*m_t_buf = '\0';
			p3 = AnyOneArg(p3, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			nlevel = atoi(m_t_buf);
			*m_t_buf = '\0';
			p4 = AnyOneArg(p4, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			nremain = atoi(m_t_buf);
			*m_t_buf = '\0';
			p5 = AnyOneArg(p5, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			bHit[0] = (atoi(m_t_buf)) ? true : false;
			*m_t_buf = '\0';
			p6 = AnyOneArg(p6, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			bHit[1] = (atoi(m_t_buf)) ? true : false;
			*m_t_buf = '\0';
			p7 = AnyOneArg(p7, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			bHit[2] = (atoi(m_t_buf)) ? true : false;
			*m_t_buf = '\0';
			p8 = AnyOneArg(p8, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			nremaincount = atoi(m_t_buf);

			if (nskill == 408)
				continue ;

#ifdef EVENT_PCBANG_2ND
			if(nskill == 493)
			{
				// PC�� ������ ���� �ȵ� �׷��Ƿ� �о� �� ���� ��ŵ
				continue;
			}
#endif // EVENT_PCBANG_2ND

			if( nskill == 516 )
			{
				// �Ǵн� ������ ���� �ȵ� �׷��Ƿ� �о� �� ���� ��ŵ
				continue;
			}
			if (nskill == 2059)
			{
				// �Ǵн� ������ ���� �ȵ� �׷��Ƿ� �о� �� ���� ��ŵ
				continue;
			}

			

			sp = gserver->m_skillProtoList.Find(nskill);
			if (sp == NULL)
				continue ;

			if (nitem > 0 && gserver->m_itemProtoList.FindIndex(nitem) == NULL)
				continue ;

			pChar->m_assist.Add(NULL, nitem, sp, nlevel, bHit, false, nremain,
								nremaincount,
								10000, 0, 0);
		}

		// curse
		dbChar.GetRec("a_curse_item", assistitem);
		p1 = assistitem;
		dbChar.GetRec("a_curse_skill", assistskill);
		p2 = assistskill;
		dbChar.GetRec("a_curse_level", assistlevel);
		p3 = assistlevel;
		dbChar.GetRec("a_curse_remain", assistremain);
		p4 = assistremain;
		dbChar.GetRec("a_curse_hit0", assisthit0);
		p5 = assisthit0;
		dbChar.GetRec("a_curse_hit1", assisthit1);
		p6 = assisthit1;
		dbChar.GetRec("a_curse_hit2", assisthit2);
		p7 = assisthit2;
		dbChar.GetRec("a_curse_remaincount", assistremaincount);
		p8 = assistremaincount;

		bStop = false;
		while (!bStop)
		{
			*m_t_buf = '\0';
			p1 = AnyOneArg(p1, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			nitem = atoi(m_t_buf);
			*m_t_buf = '\0';
			p2 = AnyOneArg(p2, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			nskill = atoi(m_t_buf);
			*m_t_buf = '\0';
			p3 = AnyOneArg(p3, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			nlevel = atoi(m_t_buf);
			*m_t_buf = '\0';
			p4 = AnyOneArg(p4, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			nremain = atoi(m_t_buf);
			*m_t_buf = '\0';
			p5 = AnyOneArg(p5, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			bHit[0] = (atoi(m_t_buf)) ? true : false;
			*m_t_buf = '\0';
			p6 = AnyOneArg(p6, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			bHit[1] = (atoi(m_t_buf)) ? true : false;
			*m_t_buf = '\0';
			p7 = AnyOneArg(p7, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			bHit[2] = (atoi(m_t_buf)) ? true : false;
			*m_t_buf = '\0';
			p8 = AnyOneArg(p8, m_t_buf);
			if (!(*m_t_buf))
			{
				bStop = true;
				break;
			}
			nremaincount = atoi(m_t_buf);

			if (nskill == 408)
				continue ;

			sp = gserver->m_skillProtoList.Find(nskill);
			if (sp == NULL)
				continue ;

			if (nitem > 0 && gserver->m_itemProtoList.FindIndex(nitem) == NULL)
				continue ;

			pChar->m_assist.Add(NULL, nitem, sp, nlevel, bHit, false, nremain, 10000,
								nremaincount,
								0, 0);
		}
	}


	//////////////////////////////////////////
	// 060227 : bs : ���� ȿ�� �б� : ����ð�
	std::string select_assist_abstime_query = boost::str(boost::format(
				"SELECT * FROM t_assist_abstime WHERE a_char_index=%1%") % pChar->m_index);
	dbChar.SetQuery(select_assist_abstime_query.c_str());
	if (dbChar.Open())
	{
		while (dbChar.MoveNext())
		{
			int nAssistABSItemIndex = 0;
			int nAssistABSSkillIndex = 0;
			int nAssistABSSkillLevel = 0;
			int nAssistABSHit0 = 0;
			int nAssistABSHit1 = 0;
			int nAssistABSHit2 = 0;
			int nAssistABSEndTime = 0;
			bool bAssistABSHit[3] = {false, false, false};

			if (   dbChar.GetRec("a_item_index", nAssistABSItemIndex)
					&& dbChar.GetRec("a_skill_index", nAssistABSSkillIndex)
					&& dbChar.GetRec("a_skill_level", nAssistABSSkillLevel)
					&& dbChar.GetRec("a_hit0", nAssistABSHit0)
					&& dbChar.GetRec("a_hit1", nAssistABSHit1)
					&& dbChar.GetRec("a_hit2", nAssistABSHit2)
					&& dbChar.GetRec("a_end_time", nAssistABSEndTime)
			   )
			{
				bAssistABSHit[0] = (nAssistABSHit0) ? true : false;
				bAssistABSHit[1] = (nAssistABSHit1) ? true : false;
				bAssistABSHit[2] = (nAssistABSHit2) ? true : false;

#ifdef REFORM_PK_PENALTY_201108 // ���� ���� ��ġ�� �α� �ƿ� �Ǿ� �־��� �ð� ��ŭ  pk ���� ����Ʈ ���� ����������Ѵ�.
				if( nAssistABSItemIndex >= 7477 && nAssistABSItemIndex <= 7479 )
				{
					const CSkillProto* sp = gserver->m_skillProtoList.Find(nAssistABSSkillIndex);
					if( sp )
					{
						const CMagicProto * mp = sp->Level( nAssistABSSkillLevel )->m_magic[0];
						if( !mp )
							continue;

						char magicLevel = sp->Level( nAssistABSSkillLevel )->m_magicLevel[0];

						const CMagicLevelProto * mlp = mp->Level(magicLevel );
						if( !mlp )
							continue;

						int currentTime;
						if( nAssistABSEndTime > gserver->getNowSecond() )
							currentTime = gserver->getNowSecond() ;
						else
							currentTime = nAssistABSEndTime;

						int rewardHours = ( (currentTime-(currentTime%(60*60))) - (lcstamptime-(lcstamptime%(60*60))) ) / (60*60);
						if( rewardHours > 0  )
						{
							int durHour = sp->m_levelproto[0]->m_durtime / (60*60*10) ;
							int PkPointPerHour = ( PK_HUNTER_POINT_MAX * mlp->m_nPowerValue / 100 ) / durHour;
							int rewardPkPoint = PkPointPerHour * rewardHours;

							pChar->AddPkPenalty( rewardPkPoint );
						}
						int remain = (nAssistABSEndTime - gserver->getNowSecond()) * PULSE_ASSIST_CHECK;
						pChar->m_assist.Add(NULL, nAssistABSItemIndex, sp, nAssistABSSkillLevel, bAssistABSHit, false, remain,
											-1,
											10000, 0, 0);
					}
				}
				else if(nAssistABSSkillIndex == 1771)
				{
					//���� �ð����� ������
					if( nAssistABSEndTime < gserver->getNowSecond() )
					{
						//��¥�� ���ð� ���ٸ�
						if(isToday(nAssistABSEndTime) == true)
						{
							//����� ���¸� false�� �����
							pChar->m_attendanceManager.setUseAssure(false);
							//�⼮���¸� ������ ������Ʈ ���ش�.
							CDBCmd dbChar_se;
							dbChar_se.Init(char_db_.getMYSQL());
							std::string query = boost::str(boost::format("UPDATE t_attendance_exp_system SET a_last_date = (CURDATE() - INTERVAL 1 DAY) WHERE a_char_index = %d") % pChar->m_index);
							dbChar_se.SetQuery(query);
							if( dbChar_se.Update() == false )
							{
								LOG_ERROR("query error : error[%s], query[%s]", mysql_error(&gserver->m_dbchar), query.c_str());
							}
							pChar->m_attendanceManager.setSysMsg(ATTENDANCE_SYS_MSG_CASE2);
						}
						else
						{
							pChar->m_attendanceManager.setSysMsg(ATTENDANCE_SYS_MSG_CASE3);
						}
					}
					else
					{
						int remain = (nAssistABSEndTime - gserver->getNowSecond()) * PULSE_ASSIST_CHECK;

						const CSkillProto* sp = gserver->m_skillProtoList.Find(nAssistABSSkillIndex);

						if (sp)
						{
							if (sp->Level(nAssistABSSkillLevel))
							{
								if (nAssistABSItemIndex <= 0 || gserver->m_itemProtoList.FindIndex(nAssistABSItemIndex))
								{
									if (remain > sp->Level(nAssistABSSkillLevel)->m_durtime)
										remain = sp->Level(nAssistABSSkillLevel)->m_durtime;
									pChar->m_assist.Add(NULL, nAssistABSItemIndex, sp, nAssistABSSkillLevel, bAssistABSHit, false, remain,
										-1,
										10000, 0, 0);
								}
							}
						}
					}
				}
				else
#endif

					// ���� �ð� ���
					if (nAssistABSEndTime > gserver->getNowSecond())
					{
						int remain = (nAssistABSEndTime - gserver->getNowSecond()) * PULSE_ASSIST_CHECK;

						const CSkillProto* sp = gserver->m_skillProtoList.Find(nAssistABSSkillIndex);

						if (sp)
						{
							if (sp->Level(nAssistABSSkillLevel))
							{
								if (nAssistABSItemIndex <= 0 || gserver->m_itemProtoList.FindIndex(nAssistABSItemIndex))
								{
									if (remain > sp->Level(nAssistABSSkillLevel)->m_durtime)
										remain = sp->Level(nAssistABSSkillLevel)->m_durtime;
									pChar->m_assist.Add(NULL, nAssistABSItemIndex, sp, nAssistABSSkillLevel, bAssistABSHit, false, remain,
														-1,
														10000, 0, 0);
								}
							}
						}
					}
			}
		}
	}
	// 060227 : bs : ���� ȿ�� �б� : ����ð�
	//////////////////////////////////////////

	// 060221 : bs : �� ��� �ð� �б� �߰�
	// �ֿϵ��� �б�
	// �� ������ ����Ʈ : ���⿡ ���� ���� ����������
	std::vector<CItem*> listPetItem;
	std::string select_pet_query = boost::str(boost::format(
									   " SELECT p.*, pn.a_pet_name as a_pet_name"
									   " FROM t_pet AS p LEFT JOIN t_pet_name AS pn ON pn.a_pet_index = p.a_index "
									   " WHERE p.a_owner = %1% AND p.a_enable = 1 ORDER BY p.a_index ") % pChar->m_index );
	dbChar.SetQuery(select_pet_query.c_str());
	if (dbChar.Open())
	{
		int index;
		int owner;
		int lastupdate;
		char type;
		int level;
		int hp;
		int hungry;
		int sympathy;
		LONGLONG exp;
		int ability;
		CLCString petSkillIndex(256);
		CLCString petSkillLevel(256);
		const char* pPetSkillIndex;
		const char* pPetSkillLevel;
		char tmp[256];
		int nRemainRebirth;
		CLCString petName(30);

		char colorType;
		int nTurntoNpc;
#ifdef PET_TURNTO_NPC_ITEM
		int nTurntoNpcSize;
#endif

		while (dbChar.MoveNext())
		{
			if (dbChar.GetRec("a_index", index) &&
					dbChar.GetRec("a_owner", owner) &&
					dbChar.GetRec("a_lastupdate", lastupdate) &&
					dbChar.GetRec("a_type", type) &&
					dbChar.GetRec("a_level", level) &&
					dbChar.GetRec("a_hp", hp) &&
					dbChar.GetRec("a_hungry", hungry) &&
					dbChar.GetRec("a_sympathy", sympathy) &&
					dbChar.GetRec("a_exp", exp) &&
					dbChar.GetRec("a_ability", ability) &&
					dbChar.GetRec("a_skill_index", petSkillIndex) &&
					dbChar.GetRec("a_skill_level", petSkillLevel) &&
					dbChar.GetRec("a_time_rebirth", nRemainRebirth)
					&& dbChar.GetRec("a_color", colorType)
					&& dbChar.GetRec("a_pet_turnto_npc", nTurntoNpc)
#ifdef PET_TURNTO_NPC_ITEM
					&& dbChar.GetRec("a_pet_size", nTurntoNpcSize )
#endif
			   )
			{
				if( !dbChar.GetRec( "a_pet_name", petName ) )
					petName = "";

				CPet* pet = new CPet(pChar, index, type, level);
				if (pet)
				{
					pet->m_hp = hp;
					pet->m_hungry = hungry;
					pet->m_sympathy = sympathy;
					pet->m_exp = exp;
					pet->m_abilityPoint = ability;
					pet->SetRemainRebirthTime(nRemainRebirth);

					pPetSkillIndex = petSkillIndex;
					pPetSkillLevel = petSkillLevel;
					for(;;)
					{
						tmp[0] = '\0';
						pPetSkillIndex = AnyOneArg(pPetSkillIndex, tmp);
						if (strlen(tmp) < 1)
							break;
						int skillindex = atoi(tmp);
						tmp[0] = '\0';
						pPetSkillLevel = AnyOneArg(pPetSkillLevel, tmp);
						if (strlen(tmp) < 1)
							break;
						int skilllevel = atoi(tmp);
						CSkill* skill = gserver->m_skillProtoList.Create(skillindex, skilllevel);
						if (skill)
							pet->AddSkill(skill);
					}
					pet->m_name = petName;
					pet->SetPetColor( colorType );
					if(!gserver->isActiveEvent(A_EVENT_XMAS) && nTurntoNpc == 485)
						nTurntoNpc = 0;
					pet->SetPetTurnToNpc( nTurntoNpc );
#ifdef PET_TURNTO_NPC_ITEM
					pet->SetPetTurnToNpcSize( nTurntoNpcSize );
#endif //PET_TURNTO_NPC_ITEM

					// ����Ʈ�� �߰�
					ADD_TO_BILIST(pet, pChar->m_petList, m_prevPet, m_nextPet);
				}
			}
		}
	}


	// DB���� PET Loading
	CDBCmd dbChar2;
	dbChar2.Init(char_db_.getMYSQL());

	std::vector<CItem*> listAPetItem;
	std::string select_apet_query = boost::str(boost::format(
										"SELECT * FROM t_apets WHERE a_owner=%1% AND a_enable=1 ORDER BY a_index") % pChar->m_index);
	dbChar.SetQuery(select_apet_query.c_str());
	if( dbChar.Open() )
	{
		int			apet_index;
		int			apet_seal;
		int			apet_proto_idx;
		CLCString	apet_name(21);
		int			apet_level;
		LONGLONG	apet_exp;
		int			apet_remain_stat;
		int			apet_plus_str;
		int			apet_plus_con;
		int			apet_plus_dex;
		int			apet_plus_int;
		int			apet_sp;
		CLCString	apet_skill(256);
		CLCString	apet_skillLevel(256);
		int			apet_hp;
		int			apet_mp;
		int			apet_faith;
		int			apet_stm;
		char		tmp[256];

		char	apet_ai;
		int		apet_ai_slot;

		unsigned int accFaith;
		unsigned int accStm;
		LONGLONG	apet_acc_exp;
		int			apet_cooltime;

		char	apet_socketcount;
		int		apet_socket[MAX_SOCKET_COUNT];

		apet_socketcount = 0;
		memset(apet_socket, 0, sizeof(apet_socket));

		while (dbChar.MoveNext())
		{
			if (dbChar.GetRec("a_index", apet_index) &&
					dbChar.GetRec("a_seal", apet_seal) &&
					dbChar.GetRec("a_proto_index", apet_proto_idx) &&
					dbChar.GetRec("a_name", apet_name) &&
					dbChar.GetRec("a_level", apet_level) &&
					dbChar.GetRec("a_exp", apet_exp) &&
					dbChar.GetRec("a_remain_stat", apet_remain_stat) &&
					dbChar.GetRec("a_plus_str", apet_plus_str) &&
					dbChar.GetRec("a_plus_con", apet_plus_con) &&
					dbChar.GetRec("a_plus_dex", apet_plus_dex) &&
					dbChar.GetRec("a_plus_int", apet_plus_int) &&
					dbChar.GetRec("a_skill_point", apet_sp) &&
					dbChar.GetRec("a_skill_index", apet_skill) &&
					dbChar.GetRec("a_skill_level", apet_skillLevel) &&
					dbChar.GetRec("a_hp", apet_hp) &&
					dbChar.GetRec("a_mp", apet_mp) &&
					dbChar.GetRec("a_faith", apet_faith) &&
					dbChar.GetRec("a_stm", apet_stm)
					&& dbChar.GetRec("a_ai_enable", apet_ai)
					&& dbChar.GetRec("a_ai_slot", apet_ai_slot)
					&& dbChar.GetRec("a_accFaith", accFaith )
					&& dbChar.GetRec("a_accStm", accStm )
					&& dbChar.GetRec("a_accExp", apet_acc_exp )
					&& dbChar.GetRec("a_cooltime", apet_cooltime )
			   )
			{
				CAPet* apet = gserver->m_pApetlist.Create( pChar, apet_index, apet_proto_idx );
				apet->m_name	= apet_name;
				apet->m_level	= apet_level;
				apet->m_exp		= apet_exp;

				apet->m_nSeal	= apet_seal;

				apet->m_nRemainStat	= apet_remain_stat;
				apet->m_nSP		= apet_sp;

				apet->m_nPlusStr	= apet_plus_str;
				apet->m_nPlusCon	= apet_plus_con;
				apet->m_nPlusDex	= apet_plus_dex;
				apet->m_nPlusInt	= apet_plus_int;
				apet->UpdateStatPlus( apet_plus_str, apet_plus_dex, apet_plus_int, apet_plus_con );

				apet->m_hp = apet_hp;
				apet->m_mp = apet_mp;
				apet->SetFaith(apet_faith);
				apet->SetStamina(apet_stm);
				apet->m_cAI = apet_ai;
				apet->m_nAISlot = apet_ai_slot;
				apet->m_nAccFaith = accFaith;
				apet->m_nAccStemina = accStm;
				apet->LoadAccExp(apet_acc_exp);
				apet->LoadCooltime(apet_cooltime);
				for(;;)
				{
					tmp[0] = '\0';
					apet_skill = AnyOneArg(apet_skill, tmp);
					if (strlen(tmp) < 1)
						break;
					int skillindex = atoi(tmp);
					tmp[0] = '\0';
					apet_skillLevel = AnyOneArg(apet_skillLevel, tmp);
					if (strlen(tmp) < 1)
						break;
					int skilllevel = atoi(tmp);
					CSkill* skill = gserver->m_skillProtoList.Create(skillindex, skilllevel);
					if (skill)
						apet->AddSkill(skill);
					// ��ų Ȯ��
				}
				ADD_TO_BILIST(apet, pChar->m_pApetlist, m_pPrevPet, m_pNextPet);

				// �� �κ� Ȯ��	dbChar2
				std::string select_apet_inven_query = boost::str(boost::format(
						"SELECT * FROM t_apets_inven WHERE a_apet_idx=%1%") % apet_index);
				dbChar2.SetQuery(select_apet_inven_query.c_str());
				if( dbChar2.Open() && dbChar2.MoveFirst() )
				{
					int pet_inven = 0;
					int idx;
					char wearPos;
					int plus;
					int flag;
					int used;
					int used_2;
					CLCString serial(MAX_SERIAL_LENGTH + 1);
					LONGLONG count;
					short option[MAX_ITEM_OPTION];

					for( pet_inven=0 ; pet_inven< APET_WEARPOINT; pet_inven++)
					{
						char field[128];
						sprintf(field,"a_item_idx%d", pet_inven );
						dbChar2.GetRec(field, idx );
						sprintf(field,"a_wear_pos%d", pet_inven );
						dbChar2.GetRec(field, wearPos );
						sprintf(field,"a_plus%d", pet_inven );
						dbChar2.GetRec(field, plus );
						sprintf(field,"a_flag%d", pet_inven );
						dbChar2.GetRec(field, flag );
						sprintf(field,"a_used%d", pet_inven );
						dbChar2.GetRec(field, used );
						sprintf(field,"a_used%d_2", pet_inven );
						dbChar2.GetRec(field, used_2 );
						sprintf(field,"a_serial%d", pet_inven );
						dbChar2.GetRec(field, serial );
						sprintf(field,"a_count%d", pet_inven );
						dbChar2.GetRec(field, count );

						char ibuf[128];
						for (int k = 0; k < MAX_ITEM_OPTION; k++)
						{
							// option
							ibuf[0] = '\0';
							IntCat(ibuf, pet_inven, false);
							strcpy(tbuf, "a_item");
							strcat(tbuf, ibuf);
							ibuf[0] ='\0';
							IntCat(ibuf, k ,false);
							strcat(tbuf, "_option");
							strcat(tbuf, ibuf);

							if (!dbChar2.GetRec(tbuf, option[k]))				continue;
						}
#ifdef DURABILITY
						CItem* item = gserver->m_itemProtoList.CreateDBItem(idx, wearPos, plus, flag, used, used_2, serial, count, option
									  ,apet_socketcount, apet_socket
									  , NULL, 0, 0
																		   );
#else
						CItem* item = gserver->m_itemProtoList.CreateDBItem(idx, wearPos, plus, flag, used, used_2, serial, count, option
									  ,apet_socketcount, apet_socket
									  , NULL
																		   );
#endif
						apet->m_wearing[pet_inven] = item;
					}
				}

				// ������ �� AI
				std::string select_apet_ai_query = boost::str(boost::format(
													   "SELECT * FROM t_apets_ai WHERE a_apet_idx=%d and a_char_idx=%d") % apet_index % pChar->m_index);
				dbChar2.SetQuery(select_apet_ai_query.c_str());
				if( dbChar2.Open() && dbChar2.MoveFirst() )
				{
					char field[128];
					int nItemNum, nSkillIdx, nSkillType;
					char cUse;

					for (int i = 0; i < apet->m_nAISlot; i++)
					{
						sprintf(field,"a_item_idx%d", i);
						dbChar2.GetRec(field, nItemNum);
						sprintf(field,"a_skill_idx%d", i);
						dbChar2.GetRec(field, nSkillIdx);
						sprintf(field,"a_skill_type%d", i);
						dbChar2.GetRec(field, nSkillType);
						sprintf(field,"a_use%d", i);
						dbChar2.GetRec(field, cUse);

						apet->m_tAIData[i].nItemNum		= nItemNum;
						apet->m_tAIData[i].nSkillIdx	= nSkillIdx;
						apet->m_tAIData[i].nSkillType	= nSkillType;
						apet->m_tAIData[i].cUse			= cUse;

						if (apet->m_tAIData[i].cUse)
							apet->m_nAICount++;
					}
				}// dbChar2.Open() - t_apet_ai
			}
		}
	}

	GoldType_t nBugFixMoney = 0;
	std::vector<int> listCompositedItem;

	////////////////
	// �κ��丮 �б�
	std::string select_inven_query = boost::str(boost::format(
										 "SELECT * FROM t_inven%02d WHERE a_char_idx=%d ORDER BY a_tab_idx, a_row_idx") % table_no % pChar->m_index);
	dbChar.SetQuery(select_inven_query.c_str());
	if (dbChar.Open())
	{
		int tabidx;
		int rowidx;
		int itemidx;
		char wearPos;
		int dbPlus;
		int flag;
		int	used;
		int used_2;

		CLCString serial(MAX_SERIAL_LENGTH + 1);
		LONGLONG count;
		short option[MAX_ITEM_OPTION];
		int OriginVar[MAX_VARIATION_COUNT];

		char socketcount = 0;
		int jewelidx[MAX_SOCKET_COUNT] = {-1,};

#ifdef DURABILITY
		int now_durability;
		int max_durability;
#endif

		for (int i = 0; i < dbChar.GetRecordCount() && dbChar.MoveNext(); i++)
		{
			// tab
			if (!dbChar.GetRec("a_tab_idx", tabidx))
				continue ;

			// row
			if (!dbChar.GetRec("a_row_idx", rowidx))
				continue ;

			// row loop
			for (int j = 0; j < ITEMS_PER_ROW; j++)
			{
				// itemidx
				if (!dbChar.GetRec(a_item_idx_str[j].c_str(), itemidx))
					continue ;

				if (itemidx <= 0)
					continue;

				CItemProto* pItemProto = gserver->m_itemProtoList.FindIndex(itemidx);
				if (pItemProto == NULL)
				{
					LOG_ERROR("Inventory : not found item[%d]. charIndex[%d]", itemidx, pChar->m_index);
					continue;
				}

				wearPos = -1;

				// plus
				if (!dbChar.GetRec(a_plus_str[j].c_str(), dbPlus))
					continue ;

				// flag
				if (!dbChar.GetRec(a_flag_str[j].c_str(), flag))
					continue ;

				// used
				if (!dbChar.GetRec(a_used_str[j].c_str(), used))
					continue ;

				if (!dbChar.GetRec(a_used2_str[j].c_str(), used_2))
					continue ;

				// serial
				if (!dbChar.GetRec(a_serial_str[j].c_str(), serial))
					continue ;

				// count
				if (!dbChar.GetRec(a_count_str[j].c_str(), count))
					continue ;
				if (count < 1)
					continue ;

				// option
				for (int k = 0; k < MAX_ITEM_OPTION; k++)
				{
					if (!dbChar.GetRec(a_item_option_str[j][k].c_str(), option[k]))
						continue;
				}
				for (int k = 0; k < MAX_VARIATION_COUNT; k++)
				{
					if(!dbChar.GetRec(a_item_origin_str[j][k].c_str(), OriginVar[k]))
						continue;
				}

#ifdef DURABILITY
				dbChar.GetRec(a_now_durability_str[j].c_str(), now_durability);
				dbChar.GetRec(a_max_durability_str[j].c_str(), max_durability);
#endif
				/* OnPlayCharDB from inven
				 * need processing chaos jewel
				 * need processing normal jewel
				 */
				static CLCString socketstring(256);
				dbChar.GetRec(a_socket_str[j].c_str(), socketstring);
				const char* pSocketInfo = socketstring;

				if(*pSocketInfo)
				{
					char buf[32];
					pSocketInfo = AnyOneArg(pSocketInfo, buf);
					jewelidx[0] = atoi(buf);

					pSocketInfo = AnyOneArg(pSocketInfo, buf);
					socketcount = atoi(buf);
					if(socketcount >= 1 && socketcount <= MAX_SOCKET_COUNT)
					{
						int i;
						for(i = 1; i < MAX_SOCKET_COUNT && *pSocketInfo; i++)
						{
							pSocketInfo = AnyOneArg(pSocketInfo, buf);
							jewelidx[i] = atoi(buf);
						}
						//Start bugFix
						if (socketcount < MAX_SOCKET_COUNT)
						{
							if(jewelidx[0] >= 0 && jewelidx[socketcount] >= 0)
							{
								socketcount++;
							}
						}
						if(jewelidx[0] >= 0 && socketcount == 1)
						{
							socketcount++;
							jewelidx[1] = 0;
						}
						//End bugFix
					}
					else
					{
						socketcount = 0;
						memset(jewelidx, -1, sizeof(jewelidx));
					}
				}
				else
				{
					socketcount = 0;
					memset(jewelidx, -1, sizeof(jewelidx));
				}

				// 050521 : bs : �ɸ� �� ���� ���� �� 12������
				switch (itemidx)
				{
				case 498:
				case 499:
				case 500:
				case 501:
					if (flag == 0)
					{
// 						DBLOG	<< init("SET LEVEL KER/NEN", pChar)
// 								<< "ITEM INDEX" << delim
// 								<< itemidx << delim
// 								<< "SERIAL" << delim
// 								<< serial << delim
// 								<< "LEVEL" << delim
// 								<< 12
// 								<< end;
						flag = 12;
					}
					break;
				}
				// --- 050521 : bs : �ɸ� �� ���� ���� �� 12������
#if defined(EVENT_WORLDCUP_2010) || defined(EVENT_WORLDCUP_2010_TOTO)
#else

				if( ( 1485 <= itemidx && itemidx <= 1516 ) || ( 5331 <= itemidx && itemidx <= 5344 ) )
				{
// 					DBLOG << init("FIFACUP END ITEM DELETE", pChar )
// 						  << "ITEM INDEX" << delim
// 						  << itemidx << delim
// 						  << "SERIAL" << delim
// 						  << serial
// 						  << end;
					continue;
				}
#endif

				if( !gserver->isActiveEvent( A_EVENT_COLLECT_BUG) && (1577 <= itemidx && itemidx <= 1578) )
				{
// 					DBLOG << init("COLLECT BUG END ITEM DELETE", pChar )
// 						  << "ITEM INDEX" << delim
// 						  << itemidx << delim
// 						  << "SERIAL" << delim
// 						  << serial
// 						  << end;
					continue;
				}

				switch (itemidx)
				{
				//case 1228:
				//case 1229:
				//case 1230:
				//case 1231:
				//case 1232:
				//case 1233:
				//case 1234:
				//case 1235:
				//case 1236:
				//case 1237:
				//case 1239:
				//case 1240:
				//case 1241:
				//case 1242:
				//case 1243:
				//case 1244:
				//case 1245:
				//case 1246:
				//case 1247:
				//case 1248:
				//case 1249:
				//case 1250:
				//case 1251:
				//case 1252:
				//case 1253:
				//case 1308:
				//case 1309:
				//case 1310:
				//case 1311:
				case 1312:
					//case 2642:
					//case 2643:
					//case 2644:
					//case 2645:
					//case 2646:
					continue ;

				default:
					break;
				}

#ifdef LC_KOR
				// ������ �Ϻ� ������ ����
				switch (itemidx)
				{
				case 1228:
				case 1229:
				case 1230:
				case 1231:
				case 1232:
				case 1233:
				case 1234:
				case 1235:
				case 1236:
				case 1237:
				case 1239:
				case 1240:
				case 1241:
				case 1242:
				case 1243:
				case 1244:
				case 1245:
				case 1246:
				case 1247:
				case 1248:
				case 1249:
				case 1250:
				case 1251:
				case 1252:
				case 1253:
				case 1254:
				case 1255:
				case 1256:
				case 1257:
				case 1258:
				case 1259:
				case 1260:
				case 1261:
				case 1262:
				case 1263:
				case 1264:
				case 1265:
				case 1266:
				case 1267:
				case 1268:
				case 1269:
				case 1270:
				case 1271:
				case 1272:
				case 1273:
				case 1274:
				case 1275:
				case 1276:
				case 1277:
				case 1278:
// 					DBLOG	<< init("JAPAN ITEM DELETE", pChar)
// 							<< "ITEM INDEX" << delim
// 							<< itemidx << delim
// 							<< "SERIAL" << delim
// 							<< serial
// 							<< end;
					continue ;

				default:
					break;
				}
#endif

#ifdef LC_KOR
				if( itemidx == 8551 )
				{
// 					DBLOG	<< init("VALENTINE RING ITEM DELETE ", pChar)
// 						<< "ITEM INDEX" << delim
// 						<< itemidx << delim
// 						<< "SERIAL" << delim
// 						<< serial
// 						<< end;
					continue;
				}
#endif //LC_KOR

#ifdef LC_KOR // 9�� �̺�Ʈ ������ ����
				if( (itemidx >= 876 && itemidx <= 879) ||
						(itemidx >= 2418 && itemidx <= 2422) ||
						(itemidx >= 836 && itemidx <= 838) ||
						(itemidx >= 2435 && itemidx <= 2445) ||
						itemidx == 2403 )
				{
// 					DBLOG	<< init("SEPTEMBER EVENT ITEM DELETE ", pChar)
// 						<< "ITEM INDEX" << delim
// 						<< itemidx << delim
// 						<< "SERIAL" << delim
// 						<< serial
// 						<< end;
					continue ;
				}
#endif // LC_KOR

				if( (itemidx >= 2435 && itemidx <= 2445) )
				{
// 					DBLOG	<< init("LC1000DAY EVENT ITEM DELETE ", pChar)
// 						<< "ITEM INDEX" << delim
// 						<< itemidx << delim
// 						<< "SERIAL" << delim
// 						<< serial
// 						<< end;
					continue ;
				}

// #ifdef LC_TLD
// 				switch (itemidx)
// 				{
// 				case 876:
// 				case 877:
// 				case 878:
// 				case 879:
// 				case 2418:
// 				case 2419:
// 				case 2420:
// 				case 2421:
// 				case 2422:
// 					DBLOG << init("RICHYEAR EVENT ITEM DELETE", pChar)
// 						  << "ITEM INDEX" << delim
// 						  << itemidx << delim
// 					 	  << "SERIAL" << delim
// 						  << serial
// 						  << end;
// 					continue;
// 				default:
// 					break;
// 				}
// #endif // LC_TLD

				/*
				#ifdef LC_TLD
								// �±� �𽺹� �� ���ġ �� �𽺹β� ����
								switch (itemidx)
								{
								case 1704:
								case 1705:

									DBLOG	<< init("TAI JASMIN  ITEM DELETE", pChar)
											<< "ITEM INDEX" << delim
											<< itemidx << delim
											<< "SERIAL" << delim
											<< serial
											<< end;
									continue ;

								default:
									break;
								}
				#endif // LC_TLD
				*/

#if defined (LC_TLD)
				if( itemidx >= 1571 && itemidx <= 1574 )
				{
// 					DBLOG << init( "EVENT TLD BUDDHIST", pChar )
// 						   << "ITEM INDEX" << delim
// 						   << itemidx << delim
// 						   << "SERIAL" << delim
// 						   << serial
// 						   << end;
					continue;
				}
#endif // defined (LC_TLD)

				if(!gserver->isActiveEvent(A_EVENT_BEAR_DOLL) &&  (itemidx > 2334 && itemidx < 2344))
				{
// 					DBLOG << init( "Gomdori item delete", pChar )
// 						   << "ITEM INDEX" << delim
// 						   << itemidx << delim
// 						   << "SERIAL" << delim
// 						   << serial
// 						   << end;
					continue;
				}

#if defined(LC_KOR)
				switch( itemidx )		// ��̳�, ����̳�, �����ǳ� �̺�Ʈ ������ ����
				{
				case 2329:
				case 2330:
				case 2331:
				case 2344:
				case 2349:
//				case 2345:				// ���		//������ �� �� ����
				case 2346:				// ��ȭ��
				case 2351:				// ��ȯ��	// �ɳ����̺�Ʈ �߰�
// 					DBLOG << init( "May Event item delete", pChar )
// 						   << "ITEM INDEX" << delim
// 						   << itemidx << delim
// 						   << "SERIAL" << delim
// 						   << serial
// 						   << end;
					continue;
				}
#endif // LC_KOR

#if  defined(LC_BILA)
				switch( itemidx )		// ��̳�, ����̳�, �����ǳ� �̺�Ʈ ������ ����
				{
				case 2329:
				case 2330:
				case 2331:
				case 2344:
				case 2349:
				case 2347:				// ��ȭ��
				case 2348:				// ��ȯ��	// �ɳ����̺�Ʈ �߰�
// 					DBLOG << init( "May Event item delete", pChar )
// 						<< "ITEM INDEX" << delim
// 						<< itemidx << delim
// 						<< "SERIAL" << delim
// 						<< serial
// 						<< end;
					continue;
				}
#endif // LC_BILA

#if defined (LC_TLD) || defined(LC_KOR)
				//������ ����
				switch( itemidx )
				{
				case 2135:
				case 2136:
// 					DBLOG	<< init("DELETE LETTER PAPER", pChar)
// 								<< "ITEM INDEX" << delim
// 								<< itemidx << delim
// 								<< "SERIAL" << delim
// 								<< serial
// 								<< end;
					continue ;
				default:
					break;
				}
#elif defined (LC_GAMIGO)

				switch( itemidx )
				{
				case 2133:
				case 2134:
				case 2135:
				case 2136:
// 					DBLOG	<< init("DELETE WHITEDAY EVENT ITEM", pChar)
// 								<< "ITEM INDEX" << delim
// 								<< itemidx << delim
// 								<< "SERIAL" << delim
// 								<< serial
// 								<< end;
					continue ;
				default:
					break;
				}
#endif //  if defined ( LC_KOR ) || defined ( LC_TLD )

#if defined ( LC_KOR )
				//������ �������� ����
				switch( itemidx )
				{
				case 2660:
				case 2661:
				case 2662:
// 					DBLOG	<< init("DELETE EVENT TREASUREBOX RED", pChar)
// 								<< "ITEM INDEX" << delim
// 								<< itemidx << delim
// 								<< "SERIAL" << delim
// 								<< serial
// 								<< end;
					continue ;
				default:
					break;
				}
#endif // LC_KOR

				switch( itemidx )
				{
				case 7253:
				case 7254:
				case 7255:
				case 7256:
				case 7257:
				case 7258:
				case 7259:
					continue;
				}

				if( !gserver->isActiveEvent(A_EVENT_HALLOWEEN) )
				{
#if defined LC_TLD
					if((itemidx >= 2482 && itemidx <= 2491) || (4927 <= itemidx && itemidx <= 4932) || itemidx == 6228 || itemidx == 7544)
					{
						// �ҷ��� �̺�Ʈ ������
// 						DBLOG	<< init("DELETE HALLOWEEN EVENT 2007", pChar)
// 								<< "ITEM INDEX" << delim
// 								<< itemidx << delim
// 								<< "SERIAL" << delim
// 								<< serial
// 								<< end;
						continue;
					}
#elif defined (LC_GAMIGO)
					switch( itemidx )
					{
					case 2464:
					case 2465:
					case 2466:
					case 2467:
					case 2468:
					case 2469:
					case 2470:
					case 2471:
					case 2472:
					case 2473:
					case 2474:
					case 2475:
					case 2488:
					case 2489:
					case 2490:
					case 2491:
						// �ҷ��� �̺�Ʈ ������
// 						DBLOG	<< init("DELETE HALLOWEEN EVENT 2007", pChar)
// 							<< "ITEM INDEX" << delim
// 							<< itemidx << delim
// 							<< "SERIAL" << delim
// 							<< serial
// 							<< end;
						continue;
					}
#else
					switch( itemidx )
					{
					case 2488:
					case 2489:
					case 2490:
					case 2491:
// 						DBLOG	<< init("DELETE HALLOWEEN EVENT 2007", pChar)
// 								<< "ITEM INDEX" << delim
// 								<< itemidx << delim
// 								<< "SERIAL" << delim
// 								<< serial
// 								<< end;
						continue;
					default:
						break;
					}
#endif
				}

				if( !gserver->isActiveEvent( A_EVENT_XMAS) )
				{
					switch( itemidx )
					{
					case 2584:
					case 2585:
					case 2586:
					case 2587:
					case 2588:
					case 2589:
					case 2604:
					case 2605:
					case 2607:
					case 2608:
// 						DBLOG	<< init("DELETE XMAS EVENT 2007", pChar)
// 							<< "ITEM INDEX" << delim
// 							<< itemidx << delim
// 							<< "SERIAL" << delim
// 							<< serial
// 							<< end;
						continue;
					default:
						break;
					}
				}

#if defined(LC_BILA)
				switch( itemidx )
				{
				case 2619:
				case 2620:
				case 2621:
				case 2622:
				case 2623:
				case 2624:
				case 2625:
				case 2626:
				case 2627:
				case 2628:
				case 2637:
				case 2638:
				case 2639:
				case 2640:
				case 2641:
// 				DBLOG	<< init("DELETE CARNIVAL EVENT 2008", pChar)
// 						<< "ITEM INDEX" << delim
// 						<< itemidx << delim
// 						<< "SERIAL" << delim
// 						<< serial
// 						<< end;
					continue;
				default:
					break;
				}
#endif // LC_BILA
				if( !gserver->isActiveEvent(A_EVENT_EGGS_HUNT) )
				{
					switch( itemidx )
					{
					case 2148:
					case 6231:
// 					DBLOG	<< init("DELETE EASTER EGG EVENT ", pChar)
// 							<< "ITEM INDEX" << delim
// 							<< itemidx << delim
// 							<< "SERIAL" << delim
// 							<< serial
// 							<< end;
						continue;
					default:
						break;
					}
				}

				//���� �������� �����ϸ� ����
				switch(itemidx)
				{
				case ARTIFACT_LEVEL1_ITEM_INDEX:
				case ARTIFACT_LEVEL2_ITEM_INDEX:
				case ARTIFACT_LEVEL3_ITEM_INDEX:
					continue;
				}

#ifdef DEV_EVENT_AUTO
				if(gserver->m_fathersDay.getEventStart() == false && gserver->m_fathersDay.getEventDeleteItem() == true) // �̺�Ʈ �Ⱓ�� �ƴ϶�� ����
				{
					std::vector<int> items;
					bool bFind = false;
					CEventKingsBirthdayRewardItem& rewardItem = gserver->m_fathersDay.getHeartRewardItem();
					CEventKingsBirthdayDropItemManager& dropItem = gserver->m_fathersDay.getDropItemManager();
					CEventKingsBirthdayFlagReward& flagReward = gserver->m_fathersDay.getFlagRewardItem();

					items.push_back(rewardItem.getItemIndex());

					int dropItemCount = dropItem.getDropItemCount();

					for(int i = 0; i < dropItemCount; i++)
					{
						if(dropItem.getDropItem(i))
							items.push_back(dropItem.getDropItem(i)->getDropItemIndex());
					}

					int rewardCount = flagReward.getCount();

					for(int i = 0; i < rewardCount; i++)
					{
						if(flagReward.getFlagRewardItem(i)->getItemIndex())
							items.push_back(flagReward.getFlagRewardItem(i)->getItemIndex());
					}

					std::vector<int>::const_iterator cit;
					std::vector<int>::const_iterator citEnd = items.end();
					for(cit = items.begin(); cit != citEnd; cit++)
					{
						if(itemidx == *cit)
						{
							bFind = true;
							break;
						}
					}
					if(bFind)
					{
// 					DBLOG << init("DELETE FathersDay Event Item", pChar)
// 						<< "ITEM INDEX" << delim
// 						<< itemidx << delim
// 						<< "SERIAL" << delim
// 						<< serial
// 						<< end;
						continue;
					}
				}
				if(gserver->m_DropEvent.getEnable() == false)
				{
					std::vector<int> itemList;
					//std::vector<CDropItem*>::iterator it;  //gserver->m_DropEvent.getDropItemManager().m_DropItem.begin()
					CDropItemManager& dropItem = gserver->m_DropEvent.getDropItemManager();
					if(dropItem.getCount() == 1)
					{
						CItem* pItem = dropItem.getItem();
						if(pItem)
						{
							bool bFind = false;
							itemList.push_back(pItem->m_itemProto->getItemIndex());
							std::vector<int>::iterator it;
							std::vector<int>::iterator itEnd = itemList.end();
							for(it = itemList.begin(); it != itEnd; it++)
							{
								if(itemidx == *it)
								{
									bFind = true;
									break;
								}
							}
							if(bFind)
							{
// 							DBLOG << init("DELETE KOKO Event Item", pChar)
// 								<< "ITEM INDEX" << delim
// 								<< itemidx << delim
// 								<< "SERIAL" << delim
// 								<< serial
// 								<< end;
								continue;
							}
						}
					}
				}
#endif
				if(pItemProto->getItemTypeIdx() == ITYPE_ETC && pItemProto->getItemSubTypeIdx() == IETC_MONSTER_MERCENARY_CARD )
				{
				}
				else if (pItemProto->getItemFlag() & ITEM_FLAG_ABS )
				{
					// �ð��� ������
					used += gserver->getNowSecond();	// used�� ���� �ð�
				}

				// �������� ���տ� �ǻ��̰� ���յ� �����̸� �ɼ��� tab, invenindex�� �и��Ͽ� ����Ѵ�
				// option[0] : tab
				// option[1] : invenindex
				int nIndexEquip = -1;
				if ((pItemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (flag & FLAG_ITEM_TRANSMOGRIFY))
				{
					if (flag & FLAG_ITEM_COMPOSITION)
					{
						nIndexEquip = ((int)option[0] << 16) | (int)option[1];
					}
					memset(option, 0, sizeof(option));

					// used_2�� -1�� ���(COMPOSITE_TIME�� ���� ���� ������ �ð� ����)
					if ((flag & FLAG_ITEM_COMPOSITION)
							&& (used_2 == -1) )
					{
						static const int one_month = 60*60*24*30;
						if (used - gserver->getNowSecond() < one_month)
						{
							// 1���� �̸��� ��� ���սð��� ���� ������ ���� �ð��� ����
							used_2 = used;
						}
						else
						{
							// 1���� �̻��� ��� ���սð��� 1�����̴�.
							used_2 = gserver->getNowSecond() + one_month;
						}
					}
				}

				// upgrade �ȵǴ� �����ۿ� ������ �ɼ� ���� �� ���� ����
				if ((pItemProto->getItemTypeIdx() == ITYPE_WEAPON || pItemProto->getItemTypeIdx() == ITYPE_WEAR)
						&& !pItemProto->CanBloodGem()
						&& !pItemProto->IsRareItem()
						&& !pItemProto->IsOriginItem()
						&& !( pItemProto->getItemIndex() >=2423 && pItemProto->getItemIndex() <= 2434 )
						&& !( pItemProto->getItemIndex() >=3012 && pItemProto->getItemIndex() <= 3017 )
				   )
				{

					BLOOD_BUG_DATA bugdata;
					memset(&bugdata, 0, sizeof(bugdata));
					bugdata.nIndex = itemidx;
					strcpy(bugdata.strSerial, serial);
					bugdata.nFlag = (flag & FLAG_ITEM_OPTION_ENABLE);
					bugdata.nOptionCount = 0;
					for (int k = 0; k < MAX_ITEM_OPTION; k++)
					{
						bugdata.nOption[k] = option[k];
						if (option[k] != 0)
						{
							bugdata.nOptionCount++;
							nBugFixMoney += 1000;
							option[k] = 0;
						}
					}
					if (bugdata.nOptionCount > 0)
					{
						pChar->m_listBloodBug.push_back(bugdata);
// 						DBLOG	<< init("UNIQIE OPTION BUG", pChar)
// 								<< "ITEM INDEX" << delim
// 								<< itemidx << delim
// 								<< "SERIAL" << delim
// 								<< serial << delim
// 								<< bugdata.nOptionCount
// 								<< end;
					}
					flag &= ~FLAG_ITEM_OPTION_ENABLE;
				}

				// Item ����
#ifdef DURABILITY
				CItem* item = gserver->m_itemProtoList.CreateDBItem(itemidx, wearPos, dbPlus, flag, used,
							  used_2, serial, count, option
							  , socketcount, jewelidx
							  , OriginVar, now_durability, max_durability
																   );
#else
				CItem* item = gserver->m_itemProtoList.CreateDBItem(itemidx, wearPos, dbPlus, flag, used,
							  used_2, serial, count, option
							  , socketcount, jewelidx
							  , OriginVar
																   );
#endif
				if (!item)
				{
					continue ;
				}

				if(item->IsRareItem() // ���� ����̰�
						&& item->GetItemLevel() > pChar->m_level	// ������ ���� ���� ���
						&& item->getWearPos() != WEARING_NONE)	// ���� ��
				{
					// �������� �����.
					pChar->m_wearInventory.wearItemInfo[(int)item->getWearPos()] = NULL;
					item->unWearPos();
				}

				// ���յ� �ǻ� �������� ������ tab, invenindex ���� �����ϰ�, �κ��� ��� �а� ���� index�� �����Ѵ�
				item->m_nCompositeItem = nIndexEquip;
				if (nIndexEquip != -1)
				{
					listCompositedItem.push_back(item->getVIndex());
				}

				// �� ����Ʈ�� ������ ������ ����
				if (item->IsPet())
				{
					if (!pChar->GetPet(item->getPlus()))
					{
						delete item;
						continue ;
					}
				}

				// APet �˻�
				if ( item->IsAPet() )
				{
					if (!pChar->GetAPet(item->getPlus()))
					{
						delete item;
						continue ;
					}
				}

				// �ɼ� ���� �Ǽ��縮 �ɼ� ���̱�
				if (item->IsAccessary() && item->m_nOption == 0)
				{
					OptionSettingItem(pChar, item);
				}
				// --- �ɼ� ���� �Ǽ��縮 �ɼ� ���̱�

				// TODO : DELETE �̱۴���1,2 ����� ����Ʈ �κ����� �Ϲ� �κ����� �̵� �ڵ�
				int	tab = tabidx;
				int invenIndex = (rowidx * ITEMS_PER_ROW) + j;

				// TODO : �������

				// Item�� �κ�����
				{
					FixItemUsedTime(item);

					if (pChar->m_inventory.insertItem(tab, invenIndex, item) == false)
					{
						delete item;
						continue;
					}

					// �� �������̸� ����Ʈ�� �߰�
					if (item->IsPet())
						listPetItem.push_back(item);
					if (item->IsAPet())
						listAPetItem.push_back(item);
				}
			} // for (j = 0; j < ITEMS_PER_ROW; j++)
		} // for (i = 0; i < dbChar.m_nrecords && dbChar.MoveNext(); i++)
	} // if (dbChar.Open())

	// �ڵ� ���� ���̺� �б�
	std::vector<int> listDeleteAutoGive;
	pChar->m_listAutoGive.clear();

	std::string select_auto_give_query = boost::str(boost::format("SELECT * FROM t_auto_give WHERE a_char_index=%1%") % pChar->m_index);
	dbChar.SetQuery(select_auto_give_query.c_str());
	if (dbChar.Open())
	{
		int			nSeqIndex;
		int			nItemIndex;
		int			nItemPlus;
		int			nItemFlag;
		int			nItemUsed;
		int			nItemUsed_2;

		LONGLONG	nItemCount;
		short		nItemOption[MAX_ITEM_OPTION];
		std::string strSerial;

		char		socketcount;
		int			jewelidx[MAX_SOCKET_COUNT] = {-1,};
		static		CLCString socketstring(50);

		while (dbChar.MoveNext())
		{
			if (
				dbChar.GetRec("a_index",			nSeqIndex)
				&& dbChar.GetRec("a_item_index",	nItemIndex)
				&& dbChar.GetRec("a_item_plus",		nItemPlus)
				&& dbChar.GetRec("a_item_flag",		nItemFlag)
				&& dbChar.GetRec("a_item_used",		nItemUsed)
				&& dbChar.GetRec("a_item_used_2",		nItemUsed_2)
				&& dbChar.GetRec("a_item_count",	nItemCount)
				&& dbChar.GetRec("a_item_option0",	nItemOption[0])
				&& dbChar.GetRec("a_item_option1",	nItemOption[1])
				&& dbChar.GetRec("a_item_option2",	nItemOption[2])
				&& dbChar.GetRec("a_item_option3",	nItemOption[3])
				&& dbChar.GetRec("a_item_option4",	nItemOption[4])
				&& dbChar.GetRec("a_item_socket", socketstring)
			)
			{
				const char* pSocketInfo = socketstring;
				if(*pSocketInfo)
				{
					char buf[10];
					pSocketInfo = AnyOneArg(pSocketInfo, buf);
					jewelidx[0] = atoi(buf);

					pSocketInfo = AnyOneArg(pSocketInfo, buf);
					socketcount = atoi(buf);
					if(socketcount >= 1 && socketcount <= MAX_SOCKET_COUNT)
					{
						int i;
						for(i = 1; i < MAX_SOCKET_COUNT && *pSocketInfo; i++)
						{
							pSocketInfo = AnyOneArg(pSocketInfo, buf);
							jewelidx[i] = atoi(buf);
						}
						//Start bugFix
						if (socketcount < MAX_SOCKET_COUNT)
						{
							if(jewelidx[0] >= 0 && jewelidx[socketcount] >= 0)
							{
								socketcount++;
							}
						}
						if(jewelidx[0] >= 0 && socketcount == 1)
						{
							socketcount++;
							jewelidx[1] = 0;
						}
						//End bugFix
					}
					else
					{
						socketcount = 0;
						memset(jewelidx, -1, sizeof(jewelidx));
					}
				}
				else
				{
					socketcount = 0;
					memset(jewelidx, -1, sizeof(jewelidx));
				}

				strSerial = GetSerial();

				bool bDeleteAutoGive = true;

				// Item ����
				CItem* item = gserver->m_itemProtoList.CreateAutoGiveDBItem(nItemIndex, -1, nItemPlus, nItemFlag, nItemUsed,
							  nItemUsed_2, strSerial.c_str(), nItemCount, nItemOption
							  ,socketcount, jewelidx
																		   );

				if (item)
				{
					// �� ����Ʈ�� ������ ������ ����
					if (item->IsPet())
					{
						delete item;
						continue ;
					}
					if (item->IsAPet())
					{
						delete item;
						continue ;
					}

					// �ɼ� ���� �Ǽ��縮 �ɼ� ���̱�
					if (item->IsAccessary() && item->m_nOption == 0)
					{
						OptionSettingItem(pChar, item);
					}
					// --- �ɼ� ���� �Ǽ��縮 �ɼ� ���̱�

					// Item�� �κ�����
					if (pChar->m_inventory.addItem(item) == false)
					{
						bDeleteAutoGive = false;
						delete item;
					}
				} // item

				if (bDeleteAutoGive)
				{
					AUTO_GIVE_DATA agdItem;
					agdItem.nIndex = nItemIndex;
					agdItem.nPlus = nItemPlus;
					agdItem.nUsed = nItemUsed;
					agdItem.nFlag = nItemFlag;
					agdItem.nCount = nItemCount;
					agdItem.nOption[0] = nItemOption[0];
					agdItem.nOption[1] = nItemOption[1];
					agdItem.nOption[2] = nItemOption[2];
					agdItem.nOption[3] = nItemOption[3];
					agdItem.nOption[4] = nItemOption[4];
					strcpy(agdItem.strSerial, strSerial.c_str());

					pChar->m_listAutoGive.push_back(agdItem);

					listDeleteAutoGive.push_back(nSeqIndex);
				}
			} // GetRec
		} // MoveNext
	} // Open

	if (listDeleteAutoGive.empty() == false)
	{
		std::vector<int>::iterator it = listDeleteAutoGive.begin();
		std::vector<int>::iterator endit = listDeleteAutoGive.end();
		for (; it != endit; ++it)
		{
			int nSeqIndex = *(it);
			std::string delete_auto_give_query = boost::str(boost::format("DELETE FROM t_auto_give WHERE a_index=%1%") % nSeqIndex);
			dbChar.SetQuery(delete_auto_give_query.c_str());
			dbChar.Update();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// â�� �б�
	{
		// â�� �� �б�
		pChar->m_inventory.InitMoneyInStash(0); // �ʱ�ȭ

		std::string select_stash_money_query = boost::str(boost::format(
				"SELECT a_stash_money FROM t_stash_money WHERE a_user_index=%1% LIMIT 1") % m_index);
		dbChar.SetQuery(select_stash_money_query);
		if (dbChar.Open() == false)
			return;

		if (dbChar.GetRecordCount() > 0) // �����Ͱ� �ִٸ� â�� �Ӵϸ� �о����
		{
			dbChar.MoveFirst();
			LONGLONG money = 0;
			dbChar.GetRec("a_stash_money", money);
			pChar->m_inventory.InitMoneyInStash(money);
		}
		else
		{
			// �����Ͱ� ���ٸ� insert���� ó��, ��� â�� �Ӵϴ� UPDATE �������� ó���ϱ� ����
			std::string insert_stash_money_query = boost::str(boost::format(
					"INSERT INTO t_stash_money(a_user_index, a_stash_money) VALUES(%1%, 0)") % m_index);
			dbChar.SetQuery(insert_stash_money_query);
			dbChar.Update();
		}
	}

	std::string select_stash_query = boost::str(boost::format(
										 "SELECT * FROM t_stash%02d WHERE a_user_idx=%d ORDER BY a_index") % (m_index % 10) % m_index);
	dbChar.SetQuery(select_stash_query.c_str());

	if (dbChar.Open())
	{
		int itemidx;
		int dbPlus;
//		int plus;
		int flag;
		CLCString serial(MAX_SERIAL_LENGTH + 1);
		LONGLONG count;
		int	used;
		int	used_2;
		short option[MAX_ITEM_OPTION];
		int OriginVar[MAX_VARIATION_COUNT];
		char socketcount;
		int jewelidx[MAX_SOCKET_COUNT];
		GoldType_t nas;

#ifdef DURABILITY
		int now_durability;
		int max_durability;
#endif

		for (int i = 0; i < dbChar.GetRecordCount() && dbChar.MoveNext(); i++)
		{
			// itemidx
			if (!dbChar.GetRec("a_item_idx", itemidx) || itemidx < 0)
				continue ;

			// plus
			//int tplus = 0;
			if (!dbChar.GetRec("a_plus", dbPlus))						continue ;

			// flag
			if (!dbChar.GetRec("a_flag", flag))							continue ;

			// serial
			if (!dbChar.GetRec("a_serial", serial))						continue ;

			// count
			if (!dbChar.GetRec("a_count", count))						continue ;
			if (count < 1)												continue ;

			// used
			if (!dbChar.GetRec("a_used", used))							continue ;
			if (!dbChar.GetRec("a_used_2", used_2))						continue ;

			for (int k = 0; k < MAX_ITEM_OPTION; k++)
			{
				// option
				std::string tstr = boost::str(boost::format("a_item_option%1%") % k);
				if (!dbChar.GetRec(tstr.c_str(), option[k]))					continue;
			}

#ifdef DURABILITY
			dbChar.GetRec("a_now_dur", now_durability);
			dbChar.GetRec("a_max_dur", max_durability);
#endif
			/*
			 * OnPlayCharDB from t_stash
			 * Need processing chaos jewel
			 * Need processing normal jewel
			 */
			static CLCString socketstring(50);
			if(!dbChar.GetRec("a_socket", socketstring))
				continue;

			const char* pSocketInfo = socketstring;
			if(*pSocketInfo)
			{
				char buf[10];
				pSocketInfo = AnyOneArg(pSocketInfo, buf);
				jewelidx[0] = atoi(buf);

				pSocketInfo = AnyOneArg(pSocketInfo, buf);
				socketcount = atoi(buf);
				if(socketcount >= 1 && socketcount <= MAX_SOCKET_COUNT)
				{
					int i;
					for(i = 1; i < MAX_SOCKET_COUNT && *pSocketInfo; i++)
					{
						pSocketInfo = AnyOneArg(pSocketInfo, buf);
						jewelidx[i] = atoi(buf);
					}
				}
				else
				{
					socketcount = 0;
					memset(jewelidx, -1, sizeof(jewelidx));
				}
			}
			else
			{
				socketcount = 0;
				memset(jewelidx, -1, sizeof(jewelidx));
			}

			for (int k = 0; k < MAX_VARIATION_COUNT; k++)
			{
				// option
				std::string tstr = boost::str(boost::format("a_item_origin_var%1%") % k);
				if (!dbChar.GetRec(tstr.c_str(), OriginVar[k]))					continue;
			}
			// 050521 : bs : �ɸ� �� ���� ���� �� 12������
			switch (itemidx)
			{
			case 498:
			case 499:
			case 500:
			case 501:
				if (flag == 0)
				{
// 					DBLOG	<< init("SET LEVEL KER/NEN", pChar)
// 							<< "ITEM INDEX" << delim
// 							<< itemidx << delim
// 							<< "SERIAL" << delim
// 							<< serial << delim
// 							<< "LEVEL" << delim
// 							<< 12
// 							<< end;
					flag = 12;
				}
				break;
			}
			// --- 050521 : bs : �ɸ� �� ���� ���� �� 12������

			switch (itemidx)
			{
			//case 1228:
			//case 1229:
			//case 1230:
			//case 1231:
			//case 1232:
			//case 1233:
			//case 1234:
			//case 1235:
			//case 1236:
			//case 1237:
			//case 1239:
			//case 1240:
			//case 1241:
			//case 1242:
			//case 1243:
			//case 1244:
			//case 1245:
			//case 1246:
			//case 1247:
			//case 1248:
			//case 1249:
			//case 1250:
			//case 1251:
			//case 1252:
			//case 1253:
			//case 1308:
			//case 1309:
			//case 1310:
			//case 1311:
			case 1312:
				//case 2642:
				//case 2643:
				//case 2644:
				//case 2645:
				//case 2646:
				continue ;

			default:
				break;
			}

#ifdef LC_KOR
			// ������ �Ϻ� ������ ����
			switch (itemidx)
			{
			case 1228:
			case 1229:
			case 1230:
			case 1231:
			case 1232:
			case 1233:
			case 1234:
			case 1235:
			case 1236:
			case 1237:
			case 1239:
			case 1240:
			case 1241:
			case 1242:
			case 1243:
			case 1244:
			case 1245:
			case 1246:
			case 1247:
			case 1248:
			case 1249:
			case 1250:
			case 1251:
			case 1252:
			case 1253:
			case 1254:
			case 1255:
			case 1256:
			case 1257:
			case 1258:
			case 1259:
			case 1260:
			case 1261:
			case 1262:
			case 1263:
			case 1264:
			case 1265:
			case 1266:
			case 1267:
			case 1268:
			case 1269:
			case 1270:
			case 1271:
			case 1272:
			case 1273:
			case 1274:
			case 1275:
			case 1276:
			case 1277:
			case 1278:
// 					DBLOG	<< init("JAPAN ITEM DELETE", pChar)
// 							<< "ITEM INDEX" << delim
// 							<< itemidx << delim
// 							<< "SERIAL" << delim
// 							<< serial
// 							<< end;
				continue ;

			default:
				break;
			}
#endif // LC_KOR

#ifdef LC_KOR
			if( itemidx == 8551 )
			{
// 					DBLOG	<< init("VALENTINE RING ITEM DELETE ", pChar)
// 						<< "ITEM INDEX" << delim
// 						<< itemidx << delim
// 						<< "SERIAL" << delim
// 						<< serial
// 						<< end;
				continue;
			}
#endif //LC_KOR

#ifdef LC_KOR // 9�� �̺�Ʈ ������ ����
			if( (itemidx >= 876 && itemidx <= 879) ||
					(itemidx >= 2418 && itemidx <= 2422) ||
					(itemidx >= 836 && itemidx <= 838) ||
					(itemidx >= 2435 && itemidx <= 2445) ||
					itemidx == 2403 )
			{
// 					DBLOG	<< init("SEPTEMBER EVENT ITEM DELETE ", pChar)
// 						<< "ITEM INDEX" << delim
// 						<< itemidx << delim
// 						<< "SERIAL" << delim
// 						<< serial
// 						<< end;
				continue ;
			}
#endif // LC_KOR

			if( (itemidx >= 2435 && itemidx <= 2445) )
			{
// 					DBLOG	<< init("LC1000DAY EVENT ITEM DELETE ", pChar)
// 						<< "ITEM INDEX" << delim
// 						<< itemidx << delim
// 						<< "SERIAL" << delim
// 						<< serial
// 						<< end;
				continue ;
			}

#if defined (LC_TLD)
			if( itemidx >= 1571 && itemidx <= 1574 )
			{
// 					DBLOG << init( "EVENT TLD BUDDHIST", pChar )
// 						   << "ITEM INDEX" << delim
// 						   << itemidx << delim
// 						   << "SERIAL" << delim
// 						   << serial
// 						   << end;
				continue;
			}
#endif // defined (LC_TLD)

#ifdef LC_KOR
			switch( itemidx )		// ��̳�, ����̳�, �����ǳ� �̺�Ʈ ������ ����
			{
			case 2329:
			case 2330:
			case 2331:
			case 2344:
			case 2349:
//				case 2345:				// ���
			case 2346:				// ��ȭ��
			case 2351:				// ��ȯ��	// �ɳ����̺�Ʈ �߰�
// 					DBLOG << init( "May Event item delete", pChar )
// 						   << "ITEM INDEX" << delim
// 						   << itemidx << delim
// 						   << "SERIAL" << delim
// 						   << serial
// 						   << end;
				continue;
			}
#endif // LC_KOR

#if defined (LC_USA) || defined(LC_BILA)
			switch( itemidx )		// ��̳�, ����̳�, �����ǳ� �̺�Ʈ ������ ����
			{
			case 2329:
			case 2330:
			case 2331:
			case 2344:
			case 2349:
			case 2347:				// ��ȭ��
			case 2348:				// ��ȯ��	// �ɳ����̺�Ʈ �߰�
// 					DBLOG << init( "May Event item delete", pChar )
// 						<< "ITEM INDEX" << delim
// 						<< itemidx << delim
// 						<< "SERIAL" << delim
// 						<< serial
// 						<< end;
				continue;
			}
#endif // defined (LC_BILA) || defined (LC_USA)

#if defined (LC_TLD) || defined (LC_KOR)
			// ������ ����
			switch( itemidx )
			{
			case 2135:
			case 2136:
// 					DBLOG	<< init("DELETE LETTER PAPER", pChar)
// 								<< "ITEM INDEX" << delim
// 								<< itemidx << delim
// 								<< "SERIAL" << delim
// 								<< serial
// 								<< end;
				continue ;
			default:
				break;
			}
#endif // #if  defined ( LC_KOR ) || defined ( LC_TLD )

#if defined ( LC_KOR )
			//������ �������� ����
			switch( itemidx )
			{
			case 2660:
			case 2661:
			case 2662:
// 					DBLOG	<< init("DELETE EVENT TREASUREBOX RED", pChar)
// 								<< "ITEM INDEX" << delim
// 								<< itemidx << delim
// 								<< "SERIAL" << delim
// 								<< serial
// 								<< end;
				continue ;
			default:
				break;
			}
#endif // LC_KOR

			if( !gserver->isActiveEvent(A_EVENT_HALLOWEEN) )
			{
#if defined LC_TLD
				if((itemidx >= 2482 && itemidx <= 2491) || (4927 <= itemidx && itemidx <= 4932) || itemidx == 6228 || itemidx == 7544)
				{
					// �ҷ��� �̺�Ʈ ������
// 						DBLOG	<< init("DELETE HALLOWEEN EVENT 2007", pChar)
// 							<< "ITEM INDEX" << delim
// 							<< itemidx << delim
//
// 							<< "SERIAL" << delim
// 							<< serial
// 							<< end;
					continue;
				}
#elif defined (LC_GAMIGO)
				switch( itemidx )
				{
				case 7253:
				case 7254:
				case 7255:
				case 7256:
				case 7257:
				case 7258:
				case 7259:
					continue;
				}

				switch( itemidx )
				{
				case 2464:
				case 2465:
				case 2466:
				case 2467:
				case 2468:
				case 2469:
				case 2470:
				case 2471:
				case 2472:
				case 2473:
				case 2474:
				case 2475:
				case 2488:
				case 2489:
				case 2490:
				case 2491:
					// �ҷ��� �̺�Ʈ ������
// 						DBLOG	<< init("DELETE HALLOWEEN EVENT 2007", pChar)
// 							<< "ITEM INDEX" << delim
// 							<< itemidx << delim
// 							<< "SERIAL" << delim
// 							<< serial
// 							<< end;
					continue;
				}
#else
				switch( itemidx )
				{
				case 2488:
				case 2489:
				case 2490:
				case 2491:
// 						DBLOG	<< init("DELETE HALLOWEEN EVENT 2007", pChar)
// 							<< "ITEM INDEX" << delim
// 							<< itemidx << delim
// 							<< "SERIAL" << delim
// 							<< serial
// 							<< end;
					continue;
				default:
					break;
				}
#endif
			}

			if( !gserver->isActiveEvent( A_EVENT_XMAS) )
			{
				switch( itemidx )
				{
				case 2584:
				case 2585:
				case 2586:
				case 2587:
				case 2588:
				case 2589:
				case 2604:
				case 2605:
				case 2607:
				case 2608:
					continue;
				default:
					break;
				}
			}

#if defined(LC_BILA)
			switch( itemidx )
			{
			case 2619:
			case 2620:
			case 2621:
			case 2622:
			case 2623:
			case 2624:
			case 2625:
			case 2626:
			case 2627:
			case 2628:
			case 2637:
			case 2638:
			case 2639:
			case 2640:
			case 2641:
// 				DBLOG	<< init("DELETE CARNIVAL EVENT 2008", pChar)
// 						<< "ITEM INDEX" << delim
// 						<< itemidx << delim
// 						<< "SERIAL" << delim
// 						<< serial
// 						<< end;
				continue;
			default:
				break;
			}
#endif // LC_BILA

			if( !gserver->isActiveEvent(A_EVENT_EGGS_HUNT) )
			{
				switch( itemidx )
				{
				case 2148:
				case 6231:
// 					DBLOG	<< init("DELETE EASTER EGG EVENT ", pChar)
// 							<< "ITEM INDEX" << delim
// 							<< itemidx << delim
// 							<< "SERIAL" << delim
// 							<< serial
// 							<< end;
					continue;
				default:
					break;
				}
			}

#ifdef DEV_EVENT_AUTO
			if(gserver->m_fathersDay.getEventStart() == false && gserver->m_fathersDay.getEventDeleteItem() == true) // �̺�Ʈ �Ⱓ�� �ƴ϶�� ����
			{
				std::vector<int> items;
				bool bFind = false;
				CEventKingsBirthdayRewardItem& rewardItem = gserver->m_fathersDay.getHeartRewardItem();
				CEventKingsBirthdayDropItemManager& dropItem = gserver->m_fathersDay.getDropItemManager();
				CEventKingsBirthdayFlagReward& flagReward = gserver->m_fathersDay.getFlagRewardItem();

				items.push_back(rewardItem.getItemIndex());

				int dropItemCount = dropItem.getDropItemCount();

				for(int i = 0; i < dropItemCount; i++)
				{
					if(dropItem.getDropItem(i))
						items.push_back(dropItem.getDropItem(i)->getDropItemIndex());
				}

				int rewardCount = flagReward.getCount();

				for(int i = 0; i < rewardCount; i++)
				{
					if(flagReward.getFlagRewardItem(i)->getItemIndex())
						items.push_back(flagReward.getFlagRewardItem(i)->getItemIndex());
				}

				std::vector<int>::const_iterator cit;
				std::vector<int>::const_iterator citEnd = items.end();
				for(cit = items.begin(); cit != citEnd; cit++)
				{
					if(itemidx == *cit)
					{
						bFind = true;
						break;
					}
				}
				if(bFind)
				{
// 					DBLOG << init("DELETE FathersDay Event Item", pChar)
// 						<< "ITEM INDEX" << delim
// 						<< itemidx << delim
// 						<< "SERIAL" << delim
// 						<< serial
// 						<< end;
					continue;
				}
			}
#endif

			CItemProto* pItemProto = gserver->m_itemProtoList.FindIndex(itemidx);

			// upgrade �ȵǴ� �����ۿ� ������ �ɼ� ���� �� ���� ����
			if (   pItemProto
					&& (pItemProto->getItemTypeIdx() == ITYPE_WEAPON || pItemProto->getItemTypeIdx() == ITYPE_WEAR)
					&& !pItemProto->CanBloodGem()
					&& !pItemProto->IsRareItem()
					&& !pItemProto->IsOriginItem()
					&& !( pItemProto->getItemIndex() >=2423 && pItemProto->getItemIndex() <= 2434 )
					&& !( pItemProto->getItemIndex() >=3012 && pItemProto->getItemIndex() <= 3017 )
			   )
			{
				BLOOD_BUG_DATA bugdata;
				memset(&bugdata, 0, sizeof(bugdata));
				bugdata.nIndex = itemidx;
				strcpy(bugdata.strSerial, serial);
				bugdata.nFlag = (flag & FLAG_ITEM_OPTION_ENABLE);
				bugdata.nOptionCount = 0;
				for (int k = 0; k < MAX_ITEM_OPTION; k++)
				{
					bugdata.nOption[k] = option[k];
					if (option[k] != 0)
					{
						bugdata.nOptionCount++;
						nBugFixMoney += 1000;
						option[k] = 0;
					}
				}
				if (bugdata.nOptionCount > 0)
				{
					pChar->m_listBloodBug.push_back(bugdata);
// 						DBLOG	<< init("UNIQIE OPTION BUG", pChar)
// 								<< "ITEM INDEX" << delim
// 								<< itemidx << delim
// 								<< "SERIAL" << delim
// 								<< serial << delim
// 								<< bugdata.nOptionCount
// 								<< end;
				}
				flag &= ~FLAG_ITEM_OPTION_ENABLE;
			}

			// Item ����
#ifdef DURABILITY
			CItem* item = gserver->m_itemProtoList.CreateDBItem(itemidx, -1, dbPlus, flag, used,
						  used_2,	serial, count, option
						  , socketcount, jewelidx
						  , OriginVar, now_durability, max_durability
															   );
#else
			CItem* item = gserver->m_itemProtoList.CreateDBItem(itemidx, -1, dbPlus, flag, used,
						  used_2,	serial, count, option
						  , socketcount, jewelidx
						  , OriginVar
															   );
#endif
			if (!item)
			{
				continue ;
			}

			// �ɼ� ���� �Ǽ��縮 �ɼ� ���̱�
			if (item->IsAccessary() && item->m_nOption == 0)
			{
				OptionSettingItem(pChar, item);
			}
			// --- �ɼ� ���� �Ǽ��縮 �ɼ� ���̱�

			FixItemUsedTime(item);

			if (pChar->m_inventory.inserItemInStash(item) == false)
			{
				delete item;
			}
		} // for (i = 0; i < dbChar.m_nrecords && dbChar.MoveNext(); i++)
	} // if (dbChar.Open())

	if (nBugFixMoney > 0)
	{
		// ĳ���͸� �о���̴� ���̹Ƿ� ��Ŷ�� �������� �ʴ� ������� ���� ������Ŵ
		LONGLONG nowMoney = pChar->m_inventory.getMoney();
		pChar->m_inventory.InitMoney(nowMoney + nBugFixMoney);
	}

	// ���� ������ ���ð� �б�
	std::string select_cashItemdate_query = boost::str(boost::format(
			"SELECT a_mempos_new, a_charslot0_new, a_charslot1_new, a_stashext_new FROM t_cashitemdate WHERE a_portal_idx=%1%") % m_index);
	dbChar.SetQuery(select_cashItemdate_query.c_str());
	if (dbChar.Open())
	{
		if (dbChar.MoveNext())
		{
			dbChar.GetRec(CASH_ITEM_DATE_FIELD_MEMPOS, pChar->m_memposTime);
			dbChar.GetRec(CASH_ITEM_DATE_FIELD_STASHEXT, pChar->m_stashextTime);
		}
	}

	// ��� ��� �б�
	std::string select_mempos_query = boost::str(boost::format("SELECT * FROM t_mempos WHERE a_char_idx=%1%") % pChar->m_index);
	dbChar.SetQuery(select_mempos_query.c_str());
	if (dbChar.Open())
	{
		if (dbChar.MoveNext())
		{
			for (int i = 0; i < MAX_MEMPOS; i++)
			{
				std::string tstr = dbChar.GetRec(a_mempos_comment[i].c_str());
				stokenizer tok(tstr, sep);
				std::vector<std::string> tvec(tok.begin(), tok.end());
				if (tvec.empty() || tvec.size() < 4)
					continue;

				if (tvec.size() != 5)
					tvec.push_back("");

				int zone = atoi(tvec[0].c_str());
				float x = atof(tvec[1].c_str());
				float z = atof(tvec[2].c_str());
				char ylayer = (char)atoi(tvec[3].c_str());

				// �ش� ���� ���ų�
				// ��� ��� �Ұ��� ���̸�
				// ������ ����������
				CZone* pZone = gserver->FindZone(zone);
				if (pZone == NULL || pZone->m_bCanMemPos == false)
					continue ;

				std::string comment = "";
				for(int j = 4; j <= tvec.size() - 1; j++)
				{
					comment += boost::str(boost::format("%s ") % tvec[j]);
				}

				pChar->m_mempos.Write(i, zone, x, z, ylayer, comment.c_str());
			}
		}
	}

	std::string select_pddata_query = boost::str(boost::format("SELECT * FROM t_pddata%02d WHERE a_char_index=%d") % table_no % pChar->m_index);
	dbChar.SetQuery(select_pddata_query.c_str());
	if (dbChar.Open() && dbChar.MoveFirst())
	{
		int pd3count, pd3time;
		int pd4count, pd4time;

		if (dbChar.GetRec("a_pd3_count", pd3count) && dbChar.GetRec("a_pd3_time", pd3time))
		{
			pChar->m_pd3Count = pd3count;
			pChar->m_pd3Time = pd3time;
		}

		if (dbChar.GetRec("a_pd4_count", pd4count) && dbChar.GetRec("a_pd4_time", pd4time))
		{
			pChar->m_pd4Count = pd4count;
			pChar->m_pd4Time = pd4time;
		}
	}
//#endif
// TODO : DELETE
//	// ������/��ų ȿ�� ����
//	pChar->CalcStatus(false);

	// �׷� ����Ʈ �ҷ�����
	CLCString gIndexList(255+1);
	CLCString gNameList(255+1);
	int chatColor = 0;

	std::string select_messenger_opt_query = boost::str(boost::format("Select a_group_index, a_group_name, a_chat_color from t_messenger_opt where a_char_idx = %1%") % pChar->m_index);
	dbChar.SetQuery(select_messenger_opt_query.c_str());

	if( dbChar.Open() && dbChar.MoveFirst() )
	{
		dbChar.GetRec("a_group_index", gIndexList);
		dbChar.GetRec("a_group_name", gNameList);
		dbChar.GetRec("a_chat_color", chatColor);
	}
// ���⼭ DB���� ģ������Ʈ �ҷ�����.
	std::string select_friend_query = boost::str(boost::format(
										  "SELECT * FROM t_friend%02d WHERE a_char_index=%d") % table_no % pChar->m_index);
	dbChar.SetQuery(select_friend_query.c_str());

	if (dbChar.Open())
	{
		int friend_index;

		CLCString name(MAX_CHAR_NAME_LENGTH + 1);
		int job, condition;

		pChar->m_Friend = new CFriend;
		int gIndex = 0;
		pChar->m_Friend->SetChatColor(chatColor);
		pChar->m_Friend->addGroup("NoGroup", 0);
		CLCString groupName(MAX_GROUP_NAME_LENGTH+1);
		const char* pgName = (const char*) gNameList;
		const char* pgIndex = (const char*) gIndexList;

		char m_buf[256];
		while(*pgIndex && *pgName)
		{
			pgIndex = AnyOneArg(pgIndex, m_buf);
			gIndex = atoi(m_buf);
			m_buf[0] = '\0';
			pgName = AnyOneArg(pgName, m_buf);
			if ( gIndex != 0 )
				pChar->m_Friend->addGroup(m_buf, gIndex);
			m_buf[0] = '\0';
		}
		CLCString Block(2);
		for (int i = 0; i < dbChar.GetRecordCount() && dbChar.MoveNext(); i++)
		{
			//	if (!dbChar.GetRec("a_index", index) || index < 0)	continue ; //��¼�� �����������...
			//ģ�� �ε���
			if (!dbChar.GetRec("a_friend_index", friend_index) || friend_index < 0)
				continue ;

			// �̸�
			if (!dbChar.GetRec("a_friend_name", name))
				continue ;

			// ����
			if (!dbChar.GetRec("a_friend_job", job))
				continue ;

			// �׷� �ε���
			if (!dbChar.GetRec("a_group_index", gIndex))
				continue ;

			condition = 0;
			CPC* pc = PCManager::instance()->getPlayerByCharIndex(friend_index);
			if (pc)
			{
				condition = pc->m_nCondition;
			}

			CFriend* pFriend = pChar->m_Friend;
			if (pFriend == NULL)
			{
				continue;
			}

			pFriend->AddFriend(friend_index, name, job, MSG_FRIEND_CONDITION_OFFLINE, gIndex);
		}
	}
	// ���� ����Ʈ �ҷ�����
	CLCString blockIndexList(255+1);
	CLCString blockNameList(255+1);

	std::string select_block_friend_query = boost::str(boost::format(
			"select * from t_block_friend where a_char_idx = %d ") % pChar->m_index );
	dbChar.SetQuery(select_block_friend_query);

	if( dbChar.Open() && dbChar.MoveFirst() )
	{
		dbChar.GetRec("a_block_idx_list", blockIndexList);
		dbChar.GetRec("a_block_name_list", blockNameList);

		const char* pblockIndex = (const char*) blockIndexList;
		const char* pblockName = (const char*) blockNameList;

		int blockIndex = -1;
		char m_buf[256];
		while(*pblockIndex && *pblockName)
		{
			pblockIndex = AnyOneArg(pblockIndex, m_buf);
			blockIndex = atoi(m_buf);
			m_buf[0] = '\0';
			pblockName = AnyOneArg(pblockName, m_buf);

			pChar->AddBlockPC(blockIndex, m_buf);
			m_buf[0] = '\0';
		}
	}

//0704
#ifdef NOTICE_EVENT
	int cnt = 0;
	for (int i = 0; i < MAX_NOTICE; i++)
	{
		if (gserver->m_aNotice[i] != 0)
		{
			std::string select_notice_query = boost::str(boost::format(
												  "SELECT * FROM t_notice WHERE a_char_idx=%d AND a_event_idx=%d") % pChar->m_index % gserver->m_aNotice[i]);

			bool bsuccess = false;
			dbChar.SetQuery(select_notice_query.c_str());

			if (dbChar.Open())
			{
				if(dbChar.MoveNext())
				{
					int count;

					if (!dbChar.GetRec("a_count", count))		continue ;

					if(count >= 3)
						continue;

					m_notice[cnt] = gserver->m_aNotice[i];
					cnt++;//ī��Ʈ ����

					count++;

					if (pChar->m_admin < 2)
					{
						std::string update_notice_query = boost::str(boost::format(
															  "UPDATE t_notice SET a_count=%1% WHERE a_char_idx=%2% AND a_event_idx=%3%")
														  % count % pChar->m_index % gserver->m_aNotice[i]);
						dbChar.SetQuery(update_notice_query.c_str());
						if (!dbChar.Update())
						{
							bsuccess = false;
						}
					}
				}
				else if (pChar->m_admin < 2) //���̺��� ���ٸ� �����Ѵ�.
				{
					std::string insert_notice_query = boost::str(boost::format(
														  "INSERT INTO t_notice (a_char_idx, a_event_idx, a_count) VALUES(%1%, %2%, 1)")
													  % pChar->m_index % gserver->m_aNotice[i]);
					dbChar.SetQuery(insert_notice_query.c_str());
					if (!dbChar.Update())
					{
						bsuccess = false;
					}

					m_notice[cnt] = gserver->m_aNotice[i];
					cnt++;//ī��Ʈ ����
				}
				else
				{
					m_notice[cnt] = gserver->m_aNotice[i];
					cnt++;//ī��Ʈ ����
				}
			}
		}
	}
#endif

#ifdef GER_SERIAL_PROMOTION
	if( m_proSite == GER_SERIAL_PROMOTION )
	{
		std::string select_proSite_query = boost::str(boost::format("select a_user_idx from t_proSite where a_user_idx=%1%") % m_index);
		dbChar.SetQuery(select_proSite_query.c_str());
		if( dbChar.Open() && dbChar.m_nrecords < 1 )
		{
			PromotionGive(m_index, pChar, 3, false);
		}
	}
#endif // GER_SERIAL_PROMOTION

	if( gserver->isActiveEvent(A_EVENT_BEAR_DOLL))
	{
		std::string select_event_gomdory_2007_query = boost::str(boost::format("SELECT * FROM t_event_gomdori_2007 WHERE a_char_index=%1%") %pChar->m_index);
		dbChar.SetQuery(select_event_gomdory_2007_query.c_str());
		pChar->m_nEventGomdori2007FirstLose = 0;
		pChar->m_nEventGomdori2007FirstWin = 0;
		if (dbChar.Open())
		{
			if (dbChar.MoveFirst())
			{
				int nLose = -1;
				int nWin = -1;
				dbChar.GetRec("a_first_lose", nLose);
				dbChar.GetRec("a_first_win", nWin);
				dbChar.GetRec("a_total", pChar->m_nEventGomdori2007Total);
				if (nLose == 0)
				{
					pChar->m_nEventGomdori2007FirstLose = 1;
				}
				if (nWin == 0)
				{
					pChar->m_nEventGomdori2007FirstWin = 1;
				}
			}
			else
			{
				pChar->m_nEventGomdori2007FirstLose = 1;
				pChar->m_nEventGomdori2007FirstWin = 1;
			}
		}
	}


	std::string select_titlelist_query = boost::str(boost::format("SELECT * from t_titlelist where a_char_index=%1%") % pChar->m_index);			// ����Ÿ��Ʋ �ε�
	dbChar.SetQuery(select_titlelist_query.c_str());

	int titleidx = 0;
	int endtime = 0;
	int custom_title_index = -1;
	if(dbChar.Open())
	{
		if(dbChar.GetRecordCount() > 0)
		{
			if(dbChar.MoveFirst())
			{
				for(int i = 0; i < dbChar.GetRecordCount(); i++)
				{
					dbChar.GetRec("a_title_index",		titleidx);
					dbChar.GetRec("a_endtime",			endtime);
					dbChar.GetRec("a_custom_title_index", custom_title_index);

					CTitle* title = gserver->m_titleProtoList.Create(titleidx, endtime);
					title->m_custom_title_index = custom_title_index;
					pChar->m_titleList.Add(title);
					dbChar.MoveNext();
				}
			}
		}
	}

	std::string select_custom_titlelist_query = boost::str(boost::format("SELECT * from t_title_make where a_char_index=%1%") % pChar->m_index);			// ����Ÿ��Ʋ �ε�
	dbChar.SetQuery(select_custom_titlelist_query.c_str());

	std::string name;
	int use;

	if(dbChar.Open())
	{
		if(dbChar.GetRecordCount() > 0)
		{
			if(dbChar.MoveFirst())
			{
				for(int i = 0; i < dbChar.GetRecordCount(); i++)
				{
					MAKE_TITLE* title = new MAKE_TITLE;
					title->option_index = new int[MAX_TITLE_OPTION];
					title->option_level = new int[MAX_TITLE_OPTION];

					dbChar.GetRec("a_index", title->title_index);
					dbChar.GetRec("a_color", title->color);
					dbChar.GetRec("a_background", title->background_color);
					dbChar.GetRec("a_effect", title->effect);
					dbChar.GetRec("a_name", name);
					strncpy(title->name, name.c_str(), CUSTOM_TITLE_NAME_LENGTH);
					dbChar.GetRec("a_option1", title->option_index[0]);
					dbChar.GetRec("a_option1_level", title->option_level[0]);
					dbChar.GetRec("a_option2", title->option_index[1]);
					dbChar.GetRec("a_option2_level", title->option_level[1]);
					dbChar.GetRec("a_option3", title->option_index[2]);
					dbChar.GetRec("a_option3_level", title->option_level[2]);
					dbChar.GetRec("a_option4", title->option_index[3]);
					dbChar.GetRec("a_option4_level", title->option_level[3]);
					dbChar.GetRec("a_option5", title->option_index[4]);
					dbChar.GetRec("a_option5_level", title->option_level[4]);
					dbChar.GetRec("a_use", use);

					if(use != 0)
					{
						//������� �� Ÿ��Ʋ ����Ʈ�� ��ϵ� Ŀ���� Ÿ��Ʋ�� �ƴ϶�� ����
						if(pChar->m_titleList.FindCustomTitle(title->title_index) == NULL)
						{
							std::string query = boost::str(boost::format("DELETE FROM t_title_make where a_index = %d and a_char_index = %d") % title->title_index % pChar->m_index );
							DBManager::instance()->pushQuery(0, query);
							pChar->m_nCurrentTitle = TITLE_SYSTEM_NO_TITLE;
							delete title;
							continue;
						}
						pChar->m_custom_title_index = title->title_index;
					}
					
					pChar->_map_title.insert(std::pair<int, MAKE_TITLE*>(title->title_index, title));

					dbChar.MoveNext();
				}
			}
		}
	}

	pChar->ApplyTitle();


	std::string select_warground_query = boost::str(boost::format("SELECT * FROM t_warground WHERE a_char_index = %1%") % pChar->m_index);
	dbChar.SetQuery(select_warground_query.c_str());

	int totalkillcount;
	int totaldeathcount;
	int wargroundpoint;
	int wargroundaccpoint;
	if(dbChar.Open() && dbChar.GetRecordCount() > 0 && dbChar.MoveFirst())
	{
		dbChar.GetRec("a_total_kill_count", totalkillcount);
		dbChar.GetRec("a_total_death_count", totaldeathcount);
		dbChar.GetRec("a_warground_point", wargroundpoint);
		dbChar.GetRec("a_warground_acc_point", wargroundaccpoint);

		pChar->SetTotalKillCount(totalkillcount);
		pChar->SetTotalDeathCount(totaldeathcount);
		pChar->SetWarGroundPoint(wargroundpoint);
		pChar->SetWarGroundAccPoint(wargroundaccpoint);
	}
	dbChar.Close();

	{
		// �Ⱓ�� ������ ������ ����
		std::string select_timer_item_query = boost::str(boost::format(
				"SELECT a_type_index, UNIX_TIMESTAMP(a_expire_time) as a_et FROM t_timer_item WHERE a_char_index=%1%")
											  % pChar->m_index);
		dbChar.SetQuery(select_timer_item_query.c_str());
		if (dbChar.Open() == false)
			return;

		while(dbChar.MoveNext())
		{
			int type = 0;
			int expire_time = 0;
			dbChar.GetRec("a_type_index", type);
			dbChar.GetRec("a_et", expire_time);
			pChar->m_TimerItem.insert(pChar->m_index, type, expire_time);
		}
	}

	{
		int itemIndex, plus, isProxy;
		CLCString serial;
		std::vector<CItem*> vec;

		std::string select_pet_stash_query = boost::str(boost::format(
				"select * from t_pet_stash where a_char_idx = %1%")
											 % pChar->m_index);
		dbChar.SetQuery(select_pet_stash_query.c_str());

		if( dbChar.Open() == false )
			return;

		pChar->m_petStashManager.setCount(dbChar.GetRecordCount());

		while(dbChar.MoveNext())
		{
			dbChar.GetRec("a_item_idx", itemIndex);
			dbChar.GetRec("a_plus", plus);
			dbChar.GetRec("a_proxy", isProxy);

			CItem *item = gserver->m_itemProtoList.CreateItem(itemIndex, WEARING_NONE, plus, 0, 1);
			if (item == NULL)
			{
				LOG_INFO("not found item in pet stash. char index : %d : item id : %d : plus : %d : proxy : %d", 
					pChar->m_index, itemIndex, plus, isProxy);
				continue;
			}

			if(isProxy > 0)
			{
				pChar->m_petStashManager.SelProxyPet(item);
			}
			vec.push_back(item);
		}
		pChar->m_petStashManager.Insert(vec);
	}

	{
		int effectNo;

		std::string select_pet_stash_info_query = boost::str(boost::format(
					"select * from t_pet_stash_info where a_char_index = %1%")
				% pChar->m_index);
		dbChar.SetQuery(select_pet_stash_info_query.c_str());

		if( dbChar.Open() == false )
			return;

		while(dbChar.MoveNext())
		{
			dbChar.GetRec("a_effect", effectNo);
			pChar->m_petStashManager.setEffect(effectNo);
		}
	}

	{
		std::string select_skill_cooltime_query = boost::str(boost::format(
					"select * from t_skill_cooltime where a_char_index = %1%")
				% pChar->m_index);
		dbChar.SetQuery(select_skill_cooltime_query.c_str());

		if( dbChar.Open() == false )
			return;

		int skillIndex;
		int use_time;
		while(dbChar.MoveNext())
		{
			dbChar.GetRec("a_skill_index", skillIndex);
			dbChar.GetRec("a_use_time", use_time);

			CSkill* skill = pChar->m_activeSkillList.Find(skillIndex);
			if(skill != NULL)
			{
				skill->m_usetime = gserver->m_pulse - (((int)gserver->m_nowseconds - use_time) * 10);
			}
		}
	}

	{
		std::string select_wear_inven_query = boost::str(boost::format(
				"select * from t_wear_inven where a_char_index = %1%")
											  % pChar->m_index);
		dbChar.SetQuery(select_wear_inven_query.c_str());

		if( dbChar.Open() == false )
			return;

		int itemidx;
		char wearPos;
		int dbPlus;
		int flag;
		int	used;
		int used_2;

		CLCString serial(MAX_SERIAL_LENGTH + 1);
		LONGLONG count;
		short option[MAX_ITEM_OPTION];
		int OriginVar[MAX_VARIATION_COUNT];

		char socketcount = 0;
		int jewelidx[MAX_SOCKET_COUNT] = {-1,};

#ifdef DURABILITY
		int now_durability;
		int max_durability;
#endif

		for (int i = 0; i < dbChar.GetRecordCount() && dbChar.MoveNext(); i++)
		{
			// itemidx
			if (!dbChar.GetRec("a_item_idx", itemidx))
				continue ;

			if (itemidx <= 0)
				continue;

			CItemProto* pItemProto = gserver->m_itemProtoList.FindIndex(itemidx);
			if (pItemProto == NULL)
			{
				LOG_ERROR("wearInven : not found item[%d]. charIndex[%d]", itemidx, pChar->m_index);
				continue;
			}

			// wear position
			if (!dbChar.GetRec("a_wear_pos", wearPos))
				continue ;

			// plus
			if (!dbChar.GetRec("a_plus", dbPlus))
				continue ;

			// flag
			if (!dbChar.GetRec("a_flag", flag))
				continue ;

			// used
			if (!dbChar.GetRec("a_used", used))
				continue ;

			if (!dbChar.GetRec("a_used2", used_2))
				continue ;

			// serial
			if (!dbChar.GetRec("a_serial", serial))
				continue ;

			// count
			count = 1;

			// option
			char st_buf[32];
			for (int k = 0; k < MAX_ITEM_OPTION; k++)
			{
				sprintf(st_buf, "a_item_option%d", k);
				if (!dbChar.GetRec(st_buf, option[k]))
					continue;
			}

			for (int k = 0; k < MAX_VARIATION_COUNT; k++)
			{
				sprintf(st_buf, "a_item_origin_var%d", k);
				if(!dbChar.GetRec(st_buf, OriginVar[k]))
					continue;
			}

			socketcount = 0;
			for (int k = 0; k < MAX_SOCKET_COUNT; k++)
			{
				sprintf(st_buf, "a_socket%d", k);
				if(!dbChar.GetRec(st_buf, jewelidx[k]))
					continue;

				if(jewelidx[k] >= 0)
					socketcount++;
			}

			if(socketcount >= 1 && socketcount <= MAX_SOCKET_COUNT)
			{
				//Start bugFix
				if (socketcount < MAX_SOCKET_COUNT)
				{
					if(jewelidx[0] >= 0 && jewelidx[socketcount] >= 0)
					{
						socketcount++;
					}
				}
				if(jewelidx[0] >= 0 && socketcount == 1)
				{
					socketcount++;
					jewelidx[1] = 0;
				}
				//End bugFix
			}
			else
			{
				socketcount = 0;
				memset(jewelidx, -1, sizeof(jewelidx));
			}

#ifdef DURABILITY
			dbChar.GetRec("a_now_dur", now_durability);
			dbChar.GetRec("a_max_dur", max_durability);
#endif

			if(!gserver->isActiveEvent(A_EVENT_BEAR_DOLL) &&  (itemidx > 2334 && itemidx < 2344))
			{
				continue;
			}

			switch( itemidx )
			{
			case 7253:
			case 7254:
			case 7255:
			case 7256:
			case 7257:
			case 7258:
			case 7259:
				continue;
			}

			if( !gserver->isActiveEvent(A_EVENT_HALLOWEEN) )
			{
#if defined LC_TLD
				if((4927 <= itemidx && itemidx <= 4932) || itemidx == 6228)
				{
					continue;
				}
#elif defined (LC_GAMIGO)
				switch( itemidx )
				{
				case 2464:
				case 2465:
				case 2466:
				case 2467:
				case 2468:
				case 2469:
				case 2470:
				case 2471:
				case 2472:
				case 2473:
				case 2474:
				case 2475:
				case 2488:
				case 2489:
				case 2490:
				case 2491:
					continue;
				}
#endif
			}

#if defined(LC_BILA)
			switch( itemidx )
			{
			case 2619:
			case 2620:
			case 2621:
			case 2622:
			case 2623:
			case 2624:
			case 2625:
			case 2626:
			case 2627:
			case 2628:
			case 2637:
			case 2638:
			case 2639:
			case 2640:
			case 2641:
				continue;
			default:
				break;
			}
#endif // LC_BILA

			//���� �������� �����ϸ� ����
			switch(itemidx)
			{
			case ARTIFACT_LEVEL1_ITEM_INDEX:
			case ARTIFACT_LEVEL2_ITEM_INDEX:
			case ARTIFACT_LEVEL3_ITEM_INDEX:
				continue;
			}

#ifdef DEV_EVENT_AUTO
			if(gserver->m_fathersDay.getEventStart() == false && gserver->m_fathersDay.getEventDeleteItem() == true) // �̺�Ʈ �Ⱓ�� �ƴ϶�� ����
			{
				std::vector<int> items;
				bool bFind = false;
				CEventKingsBirthdayRewardItem& rewardItem = gserver->m_fathersDay.getHeartRewardItem();
				CEventKingsBirthdayDropItemManager& dropItem = gserver->m_fathersDay.getDropItemManager();
				CEventKingsBirthdayFlagReward& flagReward = gserver->m_fathersDay.getFlagRewardItem();

				items.push_back(rewardItem.getItemIndex());

				int dropItemCount = dropItem.getDropItemCount();

				for(int i = 0; i < dropItemCount; i++)
				{
					if(dropItem.getDropItem(i))
						items.push_back(dropItem.getDropItem(i)->getDropItemIndex());
				}

				int rewardCount = flagReward.getCount();

				for(int i = 0; i < rewardCount; i++)
				{
					if(flagReward.getFlagRewardItem(i)->getItemIndex())
						items.push_back(flagReward.getFlagRewardItem(i)->getItemIndex());
				}

				std::vector<int>::const_iterator cit;
				std::vector<int>::const_iterator citEnd = items.end();
				for(cit = items.begin(); cit != citEnd; cit++)
				{
					if(itemidx == *cit)
					{
						bFind = true;
						break;
					}
				}
				if(bFind)
				{
					continue;
				}
			}
			if(gserver->m_DropEvent.getEnable() == false)
			{
				std::vector<int> itemList;
				CDropItemManager& dropItem = gserver->m_DropEvent.getDropItemManager();
				if(dropItem.getCount() == 1)
				{
					CItem* pItem = dropItem.getItem();
					if(pItem)
					{
						bool bFind = false;
						itemList.push_back(pItem->m_itemProto->getItemIndex());
						std::vector<int>::iterator it;
						std::vector<int>::iterator itEnd = itemList.end();
						for(it = itemList.begin(); it != itEnd; it++)
						{
							if(itemidx == *it)
							{
								bFind = true;
								break;
							}
						}
						if(bFind)
						{
							continue;
						}
					}
				}
			}
#endif

			if (pItemProto->getItemFlag() & ITEM_FLAG_ABS )
			{
				// �ð��� ������
				used += gserver->getNowSecond();	// used�� ���� �ð�
			}

			int nIndexEquip = -1;
			if ((pItemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (flag & FLAG_ITEM_TRANSMOGRIFY) )
			{
				if (flag & FLAG_ITEM_COMPOSITION)
				{
					nIndexEquip = ((int)option[0] << 16) | option[1];
					//nIndexEquip = (option[0] * ITEMS_PER_ROW) + option[1];
				}
				memset(option, 0, sizeof(option));

				// used_2�� -1�� ���(COMPOSITE_TIME�� ���� ���� ������ �ð� ����)
				if ((flag & FLAG_ITEM_COMPOSITION)
						&& (used_2 == -1) )
				{
					static const int one_month = 60*60*24*30;
					if (used - gserver->getNowSecond() < one_month)
					{
						// 1���� �̸��� ��� ���սð��� ���� ������ ���� �ð��� ����
						used_2 = used;
					}
					else
					{
						// 1���� �̻��� ��� ���սð��� 1�����̴�.
						used_2 = gserver->getNowSecond() + one_month;
					}
				}
			}

			// upgrade �ȵǴ� �����ۿ� ������ �ɼ� ���� �� ���� ����
			if ((pItemProto->getItemTypeIdx() == ITYPE_WEAPON || pItemProto->getItemTypeIdx() == ITYPE_WEAR)
					&& !pItemProto->CanBloodGem()
					&& !pItemProto->IsRareItem()
					&& !pItemProto->IsOriginItem()
					&& !( pItemProto->getItemIndex() >=2423 && pItemProto->getItemIndex() <= 2434 )
					&& !( pItemProto->getItemIndex() >=3012 && pItemProto->getItemIndex() <= 3017 )
			   )
			{

				BLOOD_BUG_DATA bugdata;
				memset(&bugdata, 0, sizeof(bugdata));
				bugdata.nIndex = itemidx;
				strcpy(bugdata.strSerial, serial);
				bugdata.nFlag = (flag & FLAG_ITEM_OPTION_ENABLE);
				bugdata.nOptionCount = 0;
				for (int k = 0; k < MAX_ITEM_OPTION; k++)
				{
					bugdata.nOption[k] = option[k];
					if (option[k] != 0)
					{
						bugdata.nOptionCount++;
						nBugFixMoney += 1000;
						option[k] = 0;
					}
				}
				if (bugdata.nOptionCount > 0)
				{
					pChar->m_listBloodBug.push_back(bugdata);
				}
				flag &= ~FLAG_ITEM_OPTION_ENABLE;
			}

			// Item ����
#ifdef DURABILITY
			CItem* item = gserver->m_itemProtoList.CreateDBItem(itemidx, -1, dbPlus, flag, used,
						  used_2, serial, count, option
						  , socketcount, jewelidx
						  , OriginVar, now_durability, max_durability
															   );
#else
			CItem* item = gserver->m_itemProtoList.CreateDBItem(itemidx, -1, dbPlus, flag, used,
						  used_2, serial, count, option
						  , socketcount, jewelidx
						  , OriginVar
															   );
#endif
			if (!item)
			{
				continue ;
			}

			// ���յ� �ǻ� �������� ������ row, col ���� �����ϰ�, �κ��� ��� �а� ���� index�� �����Ѵ�
			item->m_nCompositeItem = nIndexEquip;
			if (nIndexEquip != -1)
			{
				listCompositedItem.push_back(item->getVIndex());
			}

			// �ɼ� ���� �Ǽ��縮 �ɼ� ���̱�
			if (item->IsAccessary() && item->m_nOption == 0)
			{
				OptionSettingItem(pChar, item);
			}
			// --- �ɼ� ���� �Ǽ��縮 �ɼ� ���̱�

			// Item�� �κ�����
			{
				FixItemUsedTime(item);

				if(wearPos >= COSTUME2_WEARING_START)
				{
					wearPos -= COSTUME2_WEARING_START;
				}

				// �� ����Ʈ�� ������ ������ ����
				if (item->IsPet())
				{
					if (!pChar->GetPet(item->getPlus()))
					{
						delete item;
						continue ;
					}
					else
					{
						listPetItem.push_back(item);
					}
				}

				// APet �˻�
				if ( item->IsAPet() )
				{
					if (!pChar->GetAPet(item->getPlus()))
					{
						delete item;
						continue ;
					}
					else
					{
						listAPetItem.push_back(item);
					}
				}
					
				//�ѹ� �ǻ��� ���
				if (item->m_itemProto->getItemTypeIdx() == ITYPE_WEAR && item->m_itemProto->getItemSubTypeIdx() == IWEAR_SUIT && wearPos != WEARING_NONE)
				{
					pChar->m_wearInventory.initCostumSuitItem(item);
				}
				else if (item->m_itemProto->getItemFlag() & ITEM_FLAG_COSTUME2)
				{
					if(wearPos == 11 ) wearPos = 7;
					if(wearPos >= WEARING_HELMET && wearPos < MAX_WEARING
							&& !pChar->m_wearInventory.wearItemInfo[wearPos + COSTUME2_WEARING_START])
					{
						pChar->m_wearInventory.initCostumItem(item, item->m_itemProto->getItemWearing());
						if(item->IsOriginItem() && item->m_itemProto->GetSetIndex())
						{
							pChar->CountSetItem(item);
						}
					}
					else
						item->unWearPos();
				}
				// ������ ������ �˻� -> ���� ���� ����
				else if(wearPos >= 0 && wearPos < MAX_WEARING	// �ùٸ� ��ȣ�̰�
						&& !pChar->m_wearInventory.wearItemInfo[wearPos])					// �ߺ� ������ �ƴϸ�
				{
					item->setWearPos(wearPos);
					pChar->m_wearInventory.wearItemInfo[wearPos] = item;
				}
				else
				{
					item->unWearPos();
				}
			}
		}
	}

	// Quick Slot �ҷ�����
	std::string select_quickslot_query = boost::str(boost::format(
			"SELECT * FROM t_quickslot%02d WHERE a_char_idx=%d ORDER BY a_char_idx, a_page_idx") % table_no % pChar->m_index);
	dbChar.SetQuery(select_quickslot_query.c_str());

	if (dbChar.Open())
	{
		for (int i = 0; i < dbChar.GetRecordCount() && dbChar.MoveNext(); i++)
		{
			int page = 0;
			int slot = 0;

			// page read
			dbChar.GetRec("a_page_idx", page);
			// slot loop
			const char* pch = dbChar.GetRec("a_slot");

			while (*pch && slot < QUICKSLOT_MAXSLOT)
			{
				// slot type
				pch = AnyOneArg(pch, tbuf);
				pChar->m_quickSlot[page].m_slotType[slot] = atoi(tbuf);

				switch (pChar->m_quickSlot[page].m_slotType[slot])
				{
				// �����
				case QUICKSLOT_TYPE_EMPTY:
					break;
				// Skill type
				case QUICKSLOT_TYPE_SKILL:
					{
						pch = AnyOneArg(pch, tbuf);
						if (pChar->m_activeSkillList.Find(atoi(tbuf)) != NULL)
							pChar->m_quickSlot[page].m_skillType[slot] = atoi(tbuf);
						else
							pChar->m_quickSlot[page].m_slotType[slot] = QUICKSLOT_TYPE_EMPTY;
					}
					break;
				// Action type
				case QUICKSLOT_TYPE_ACTION:
					{
						pch = AnyOneArg(pch, tbuf);
#ifdef DONT_USE_ATTACK_ACTION // �����û���� �� ���� ���� ���� �׼��� ������ ����. ���� �׼��� ����.
						if( atoi(tbuf)  ==  1 )
						{
							pChar->m_quickSlot[page].m_slotType[slot] = QUICKSLOT_TYPE_EMPTY;
							break;
						}
#endif
#ifdef BUGFIX_DONT_USE_GET_FIRST_PARTY	// ��Ű��û���� �� ���� ���� �Լ��켱 ��Ƽ �׼��� ����.
						if( atoi(tbuf)  ==  7 )
						{
							pChar->m_quickSlot[page].m_slotType[slot] = QUICKSLOT_TYPE_EMPTY;
							break;
						}
#endif
#ifdef LC_RUS
						if( atoi(tbuf)  ==  44 || atoi(tbuf) == 45 )
						{
							pChar->m_quickSlot[page].m_slotType[slot] = QUICKSLOT_TYPE_EMPTY;
							break;
						}
#endif

#ifdef HARDCORE_SERVER
						if(gserver->m_hardcore_flag_in_gameserver)
						{
							// �ϵ��ھ� ���������� �İ����� ������
							if( atoi(tbuf)  ==  30 )
							{
								pChar->m_quickSlot[page].m_slotType[slot] = QUICKSLOT_TYPE_EMPTY;
								break;
							}
						}
#endif
						pChar->m_quickSlot[page].m_actionType[slot] = atoi(tbuf);
					}
					break;

				// Item type : tab row col
				case QUICKSLOT_TYPE_ITEM:
					{
						int tab = -1;
						int invenIndex = -1;
						pch = AnyOneArg(pch, tbuf);
						tab = atoi(tbuf);
						pch = AnyOneArg(pch, tbuf);
						invenIndex = atoi(tbuf);

						pChar->m_quickSlot[page].m_item[slot] = pChar->m_inventory.getItem(tab, invenIndex);

						if (pChar->m_quickSlot[page].m_item[slot] == NULL)
							pChar->m_quickSlot[page].m_slotType[slot] = QUICKSLOT_TYPE_EMPTY;
					}
					break;

				case QUICKSLOT_TYPE_ITEM_WEAR:
					{
						int wearItemType = -1;
						int wearpos = 0;
						int costumePlusValue = 0;
						pch = AnyOneArg(pch, tbuf);
						wearItemType = atoi(tbuf);
						pch = AnyOneArg(pch, tbuf);
						wearpos = atoi(tbuf);

						if(wearpos < WEARING_HELMET || wearpos > COSTUME2_WEARING_SUIT)
						{
							pChar->m_quickSlot[page].m_slotType[slot] = QUICKSLOT_TYPE_EMPTY;
							break;
						}

						switch(wearItemType)
						{
						case 0:
							pChar->m_quickSlot[page].m_item[slot] = pChar->m_wearInventory.getWearItem(wearpos);
							break;
						case 1:
							pChar->m_quickSlot[page].m_item[slot] = pChar->m_wearInventory.getCosWearItem(wearpos);
							break;
						case 2:
							pChar->m_quickSlot[page].m_item[slot] = pChar->m_wearInventory.getCosWearSuitItem();
							break;
						default:
							pChar->m_quickSlot[page].m_item[slot] = NULL;
							break;
						}

						if (pChar->m_quickSlot[page].m_item[slot] == NULL)
							pChar->m_quickSlot[page].m_slotType[slot] = QUICKSLOT_TYPE_EMPTY;
					}
					break;

				default:
					{
						pChar->m_quickSlot[page].m_slotType[slot] = QUICKSLOT_TYPE_EMPTY;
					}
					break;
				}
				slot++;
			} // end while
		} // for (i = 0; i < dbChar.m_nrecords && dbChar.MoveNext(); i++)
	} // if (dbQuickSlot.Open())

	// �κ��丮���� ���յ� �ǻ� �������� ã�� row, col ���� index�� ����
	{
		std::string sql = boost::str(boost::format("SELECT * FROM t_inventory_options WHERE a_char_idx = %d") % pChar->m_index);
		dbChar.SetQuery(sql);
		if (!dbChar.Open())
			return;
		while (dbChar.MoveNext())
		{
			int optionType;
			int isActive;
			dbChar.GetRec("a_type", optionType);
			dbChar.GetRec("a_value", isActive);
			if (optionType == INVENTORY_OPTION_INVENTORY_OPTION)
			{
				pChar->m_inventory.m_inventoryOptions.SetOption(optionType, isActive != 0);
			}
		}
	}
	std::vector<int>::iterator it = listCompositedItem.begin();
	std::vector<int>::iterator endit = listCompositedItem.end();
	for(; it != endit; ++it)
	{
		int nIndexClothes = *(it);

		CItem* pItemClothesOfWearInven = pChar->m_wearInventory.FindByVirtualIndex(nIndexClothes);
		CItem* pItemClothesOfInven = pChar->m_inventory.FindByVirtualIndex(nIndexClothes);

		if(pItemClothesOfInven != NULL)
		{
			int tab = pItemClothesOfInven->m_nCompositeItem >> 16;
			int invenIndex = pItemClothesOfInven->m_nCompositeItem & 0x00FFFF;
			CItem* pItemEquip = pChar->m_inventory.getItem(tab, invenIndex);
			if (pItemEquip)
			{
				pItemClothesOfInven->m_nCompositeItem = pItemEquip->getVIndex();
			}
			else
			{
				pItemClothesOfInven->m_nCompositeItem = -1;
				pItemClothesOfInven->setFlag(pItemClothesOfInven->getFlag() & ~FLAG_ITEM_COMPOSITION);
			}

		}

		else if(pItemClothesOfWearInven != NULL)
		{
			int tab = pItemClothesOfWearInven->m_nCompositeItem >> 16;
			int invenIndex = pItemClothesOfWearInven->m_nCompositeItem & 0x00FFFF;
			CItem* pItemEquip = pChar->m_inventory.getItem(tab, invenIndex);
			if (pItemEquip)
			{
				pItemClothesOfWearInven->m_nCompositeItem = pItemEquip->getVIndex();
			}
			else
			{
				pItemClothesOfWearInven->m_nCompositeItem = -1;
				pItemClothesOfWearInven->setFlag(pItemClothesOfWearInven->getFlag() & ~FLAG_ITEM_COMPOSITION);
			}
		}
	}
	listCompositedItem.clear();

	CItem *originItem;
	for (int i = 0; i < MAX_WEARING ; i++ )
	{
		if (pChar->m_wearInventory.wearItemInfo[i])
		{
			if (pChar->m_wearInventory.wearItemInfo[i]->IsOriginItem() && pChar->m_wearInventory.wearItemInfo[i]->m_itemProto->GetSetIndex())
			{
				originItem = pChar->m_wearInventory.wearItemInfo[i];
			}
			else if (((pChar->m_wearInventory.wearItemInfo[i]->m_itemProto->getItemFlag() & ITEM_FLAG_COMPOSITE) || (pChar->m_wearInventory.wearItemInfo[i]->getFlag() & FLAG_ITEM_TRANSMOGRIFY))
			&& (pChar->m_wearInventory.wearItemInfo[i]->getFlag() & FLAG_ITEM_COMPOSITION))
			{
				originItem = pChar->m_inventory.FindByVirtualIndex(pChar->m_wearInventory.wearItemInfo[i]->m_nCompositeItem);
			}
			else
				originItem = NULL;
			if (originItem)
			{
				pChar->CountSetItem(originItem);
			}
		}
	}

	pChar->InitStat();
	pChar->CalcStatus(false);

	if (pChar->m_pApetlist)
	{
		CAPet* pAPet;
		CAPet* pAPetNext = pChar->m_pApetlist;
		while ((pAPet = pAPetNext))
		{
			pAPetNext = pAPetNext->m_pNextPet;
			CItem* result_pPetItem = NULL;
			std::vector<CItem*>::iterator it = listAPetItem.begin();
			std::vector<CItem*>::iterator endit = listAPetItem.end();
			for(; it != endit; ++it)
			{
				CItem* pPetItem = *(it);
				if (pPetItem && pPetItem->getPlus() == pAPet->m_index)
				{
					pAPet->CheckAIList();
					result_pPetItem = pPetItem;
					break;
				}
			}
			std::vector<CItem*>::iterator it_petStash = pChar->m_petStashManager.m_petItem.begin();
			std::vector<CItem*>::iterator it_petStash_end = pChar->m_petStashManager.m_petItem.end();

			for(; it_petStash != it_petStash_end; it_petStash++)
			{
				CItem* pPetItem = *(it_petStash);
				if(pPetItem && pPetItem->getPlus() == pAPet->m_index)
				{
					pAPet->CheckAIList();
					result_pPetItem = pPetItem;
					break;
				}
			}
			if (!result_pPetItem)
			{
				// 				DBLOG	<< init("PET DELETE (NOT FOUND ITEM)", pChar)
				// 						<< "PET"					<< delim
				// 						<< pAPet->m_index			<< delim
				// 						<< pAPet->m_level
				// 						<< end;
				REMOVE_FROM_BILIST(pAPet, pChar->m_pApetlist, m_pPrevPet, m_pNextPet);
				delete pAPet;
				pAPet = NULL;
			}
		}
	}
	if (pChar->m_petList)
	{
		CPet* pPet;
		CPet* pPetNext = pChar->m_petList;
		while ((pPet = pPetNext))
		{
			pPetNext = pPetNext->m_nextPet;
			CItem* result_pPetItem = NULL;
			std::vector<CItem*>::iterator it = listPetItem.begin();
			std::vector<CItem*>::iterator endit = listPetItem.end();
			for(; it != endit; ++it)
			{
				CItem* pPetItem = *(it);
				if (pPetItem->getPlus() == pPet->m_index)
				{
					result_pPetItem = pPetItem;
					break;
				}
			}
			std::vector<CItem*>::iterator it_petStash = pChar->m_petStashManager.m_petItem.begin();
			std::vector<CItem*>::iterator it_petStash_end = pChar->m_petStashManager.m_petItem.end();

			for(; it_petStash != it_petStash_end; it_petStash++)
			{
				CItem* pPetItem = *(it_petStash);
				if (pPetItem->getPlus() == pPet->m_index)
				{
					result_pPetItem = pPetItem;
					break;
				}
			}
			if (!result_pPetItem)
			{
				// 				DBLOG	<< init("PET DELETE (NOT FOUND ITEM)", pChar)
				// 						<< "PET"					<< delim
				// 						<< pPet->m_index			<< delim
				// 						<< pPet->GetPetTypeGrade()	<< delim
				// 						<< pPet->m_level
				// 						<< end;
				REMOVE_FROM_BILIST(pPet, pChar->m_petList, m_prevPet, m_nextPet);
				delete pPet;
				pPet = NULL;
			}
		}
	}

	CDBCmd authPromoDb;
	authPromoDb.Init(auth_db_.getMYSQL());
	std::string select_promo_query = boost::str(boost::format(
			"SELECT * FROM t_promo_key_user_use WHERE a_user_index = %d") % m_index);
	authPromoDb.SetQuery(select_promo_query.c_str());
	authPromoDb.Open();

	int countUserPromoKey = 0;
	while (authPromoDb.MoveNext())
	{
		int usePromoKeyIndex = 0;
		authPromoDb.GetRec("a_promo_key_index", usePromoKeyIndex);
		pChar->m_vecUsePromoKey.push_back(usePromoKeyIndex);
		countUserPromoKey++;
	}

	LOG_INFO("The player[%s][%d] used promo keys: %d", pChar->m_nick.GetBuffer(), pChar->m_index, countUserPromoKey);

#ifdef STASH_PASSWORDS
	{
		CDBCmd authDb;
		authDb.Init(auth_db_.getMYSQL());

		std::string query = boost::str(boost::format(
										   "SELECT a_stash_password FROM t_users WHERE a_idname='%s' LIMIT 1") % user_id);

		authDb.SetQuery(query.c_str());
		authDb.Open();

		if (authDb.MoveNext() == false)
		{
			LOG_ERROR("not found row in t_users. user_id[%s]", user_id.c_str());
			return;
		}

		authDb.GetRec("a_stash_password", pChar->m_stash_password);

		//////////////////////////////////////////////////////////////////////////
#ifdef JUMIN_DB_CRYPT
		pChar->m_a_cid = "1111";		// �ӽ÷� KOR ������ ó����. ������ �ֹε�Ϲ�ȣ ���ڸ� 7�ڸ��ε� ���߹���(KOR)������ �����Ƿ� �ӽ÷� ó����
#else
		{
			query = boost::str(boost::format("SELECT RIGHT(a_cid, 7) as a_cid FROM bg_user WHERE a_idname = '%s' LIMIT 1") % user_id);
			authDb.SetQuery(query.c_str());
			authDb.Open();

			if (authDb.MoveNext() == false)
			{
				LOG_ERROR("not found row in bg_user. user_id[%s]", user_id.c_str());
				return;
			}

			authDb.GetRec("a_cid", pChar->m_a_cid);
		}
#endif
	}
#endif

	// rvr ���� �о����
	select_rvr_info_query(pChar);
	// gps
	pChar->m_gpsManager.load(this->char_db_.getMYSQL());
	// item collection
	pChar->m_itemCollectionManager.load(this->char_db_.getMYSQL());

#ifdef PREMIUM_CHAR
	pChar->m_premiumChar.load(this->char_db_.getMYSQL());
#endif

	{
		// �о���� ĳ���� ������ main thread�� �����ش�.
		EventProcessForDB::selectChar rdata;
		rdata.m_index = m_index;
		rdata.m_seq_index = seq_index;
		rdata.pChar = pChar;
		memcpy(rdata.m_notice, m_notice, sizeof(m_notice));

		EventProcessForDB::instance()->pushSelectCharacter(rdata);
	}

	{
		CNetMsg::SP rmsg(new CNetMsg);
		// �ϵ��ڵ� : Ʃ�丮�� ����Ʈ�� �������̸� ��ŸƮ���� ZONE_SINGLE_DUNGEON_TUTORIAL�� ��ü�Ѵ�
		if (bGotoTutorial)
			DBOKMsg(rmsg, ZONE_SINGLE_DUNGEON_TUTORIAL);
		else
			DBOKMsg(rmsg, pChar->m_pZone->m_index);

		SendMessageToClient(seq_index, m_index, rmsg);
	}

	pChar->m_attendanceManager.load(this->char_db_.getMYSQL());
}

//////////////////////////////////////////////////////////////////////////
#ifdef GER_SERIAL_PROMOTION
void DBProcess::PromotionGive(int m_index, CPC* pChar, int partner_id, bool lucky)
{
	// 1706, 2360 ����
	int pro_item[2][2] =
	{
		{ 1706, 1, },
		{ 2360, 1, },
	};

	int i;
	for(i = 0; i < 2; i++)
	{
		if( !pChar->GiveItem(pro_item[i][0], 0, 0, pro_item[i][1]) )
		{
			for( ; i > 0; i--)
			{
				CItem* item = pChar->m_inventory.FindByVirtualIndex(pro_item[i][0]);
				if( item == NULL)
					continue;

				// Item ���� ����
				pChar->m_inventory.decreaseItemCount(item, pro_item[i][1]);
			}

			break;
		}
	}

	//������ �����ϰ� , �ش� userIndex insert
	if( i == 2 )
	{
		CDBCmd dbdata;
		dbdata.Init(char_db_.getMYSQL());

		std::string tstr = boost::str(boost::format("insert into t_prosite_ger(a_user_idx, a_char_idx) values(%1%, %2%)") % m_index % pChar->m_index);
		dbdata.SetQuery(tstr.c_str());

		if(!dbdata.Update() )
		{
			// �θ����� �ؾ�¡
			for( ; i > 0; i--)
			{
				CItem* item = pChar->m_inventory.FindByVirtualIndex(pro_item[i][0]);
				if (item == NULL)
					continue;

				// Item ���� ����
				pChar->m_inventory.decreaseItemCount(item, pro_item[i][1]);
			}
		}
	}
}
#else
void DBProcess::PromotionGive(int m_index, CPC* pChar, int partner_id, bool lucky)
{
	int i = 0;
	//4G ������ 1�� , �ݸ��� 5000nas �߱�ȸ���� 15��
	// ������ 300���� 1���� 4G ������3, �ݸ��� 10000nas �߱�ȸ���� 20 ������ 1
	// ��Ʈ�� ���̵�, ��Ű, �����ۼ�
	// �ٽ� CL �̳� NM ��ǰ : 5000������ ������1�� �߱�ȸ����10��

	// ���� �ø��� �Է� �� ����
	int pro_item[2][2][3] =
	{
		{ { 723, -1, -1 }, { 723, -1, -1 } },
		{ { 19, 44, 723 }, { 19, 44, 723 } }
	};

	LONGLONG pro_count[2][2][3] =
	{
		{ { 1, 0, 0 }, { 3, 0, 0 } },
		{ { 5000, 10, 1 }, { 10000, 20, 1 } }
	};

	CDBCmd dbChar;
	dbChar.Init(char_db_.getMYSQL());

	for(i = 0; i < 3; i++)
	{
		if( pro_item[partner_id][lucky][i] == -1 ) continue;

		if( !pChar->GiveItem(pro_item[partner_id][lucky][i], 0, 0, pro_count[partner_id][lucky][i]) )
		{
			// �ѹ�
			for( ; i > 0; i--)
			{
				CItem* item = pChar->m_inventory.FindByVirtualIndex(pro_count[partner_id][lucky][i]);
				if (item == NULL)
					continue;

				// Item ���� ����
				pChar->m_inventory.decreaseItemCount(item, pro_count[partner_id][lucky][i]);
			}

			break;
		}
	}
	//������ �����ϰ� , �ش� userIndex insert
	if( i == 3 )
	{
		std::string tstr = boost::str(boost::format("insert into t_proSite (a_user_idx, a_char_idx) values (%1%, %2%)") % m_index % pChar->m_index);
		dbChar.SetQuery(tstr.c_str());

		if(!dbChar.Update() )
		{
			// �θ����� �ؾ�¡
			for( ; i > 0; i--)
			{
				CItem* item = pChar->m_inventory.FindByVirtualIndex(pro_item[partner_id][lucky][i]);
				if (item == NULL)
					continue;

				// Item ���� ����
				pChar->m_inventory.decreaseItemCount(item, pro_count[partner_id][lucky][i]);
			}
		}
	}
}
#endif

void DBProcess::select_rvr_info_query(CPC* pChar)
{
	CDBCmd dbChar;
	dbChar.Init(char_db_.getMYSQL());

	// ���� �⿩�� �о� ����
	std::string select_rvr_contripoint = boost::str(boost::format("SELECT a_syndicate_type, a_syndicate_point_k, a_syndicate_point_d, a_syndicate_join_bit FROM t_characters where a_index = %1%") % pChar->m_index);


	dbChar.SetQuery(select_rvr_contripoint.c_str());
	if (!dbChar.Open())
	{
		LOG_ERROR("DB ERROR : LOAD CHARACTER SYNDICATE_CONTRIBUTION TABLE / char_index[%d] / query[%s] / error[%s]",
				  pChar->m_index, select_rvr_contripoint.c_str(), mysql_error(dbChar.GetDbConn()));
	}
	else
	{
		while (dbChar.MoveNext())
		{
			SYNDICATE_DATA *data = &(pChar->m_syndicateManager.syndicateData_);
			memset(data, 0, sizeof(SYNDICATE_DATA));
			dbChar.GetRec("a_syndicate_type", data->syndicateType);
			dbChar.GetRec("a_syndicate_point_k", data->syndicate_point_k);
			dbChar.GetRec("a_syndicate_point_d", data->syndicate_point_d);
			dbChar.GetRec("a_syndicate_join_bit", data->syndicate_join_bit);

			data->syndicate_grade_k = SYNDICATE::getSyndicateGrade(data->syndicateType, data->syndicate_point_k);
			data->syndicate_grade_d = SYNDICATE::getSyndicateGrade(data->syndicateType, data->syndicate_point_d);

			if (data->syndicate_join_bit & (1 << data->syndicateType))
			{
				pChar->m_syndicateManager.setSyndicateType(data->syndicateType);

				if(SyndicateInfoDataManager::instance()->getKingIndex(data->syndicateType) == pChar->m_index)
				{
					if(data->syndicateType == SYNDICATE::eSYNDICATE_DEALERMOON)
					{
						pChar->m_syndicateManager.syndicateData_.syndicate_grade_d = SYNDICATE::IPSISSIMUS;
					}
					else if(data->syndicateType == SYNDICATE::eSYNDICATE_KAILUX)
					{
						pChar->m_syndicateManager.syndicateData_.syndicate_grade_k = SYNDICATE::PRINCIPE;
					}
				}
			}
		}
	}

	// ���� �����丮 �о� ����
	std::string select_rvr_history = boost::str(boost::format("SELECT a_syndicate_type, a_enum, a_grade, a_target_syndicate_type, a_target_name, UNIX_TIMESTAMP(a_time) as a_time  FROM t_syndicate_history WHERE a_char_index = %1% order by a_time LIMIT %2%") % pChar->m_index % SYNDICATE_HISTORY_MAX);
	dbChar.SetQuery(select_rvr_history.c_str());
	if (!dbChar.Open())
	{
		LOG_ERROR("DB ERROR : LOAD CHARACTER SYNDICATE_HISTORY TABLE / char_index[%d] / query[%s] / error[%s]",
				  pChar->m_index, select_rvr_history.c_str(), mysql_error(dbChar.GetDbConn()));
	}
	else
	{
		while (dbChar.MoveNext())
		{
			SYNDICATE_HISTORY historyData;

			dbChar.GetRec("a_syndicate_type", historyData.syndicateType);
			dbChar.GetRec("a_enum", historyData.type);
			dbChar.GetRec("a_grade", historyData.grade);
			dbChar.GetRec("a_target_syndicate_type", historyData.targetSyndicateType);
			dbChar.GetRec("a_target_name", historyData.targetName);
			dbChar.GetRec("a_time", historyData.time);

			pChar->m_syndicateManager.initHistoryDBLoading(historyData.syndicateType, historyData);
		}
	}
}
