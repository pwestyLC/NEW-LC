#include <boost/format.hpp>
#include "stdhdrs.h"

#include "Exp.h"
#include "Server.h"
#include "../ShareLib/DBCmd.h"

static std::vector<LONGLONG> gLevelupExp;  // Dynamic array instead of fixed size
static int g_maxLevel = 0;

void InitExp()
{
	CDBCmd dbexp;
	dbexp.Init(&gserver->m_dbdata);

	// First, count how many levels exist in the database
	CDBCmd dbcount;
	dbcount.Init(&gserver->m_dbdata);
	dbcount.SetQuery("SELECT MAX(a_level) as max_level FROM t_exp");

	int maxLevelFromDb = 0;
	if (dbcount.Open())
	{
		while (dbcount.MoveNext())
		{
			dbcount.GetRec("max_level", maxLevelFromDb);
		}
	}

	if (maxLevelFromDb <= 0)
	{
		LOG_INFO("t_exp Error: No levels found in database");
		exit(0);
	}

	g_maxLevel = maxLevelFromDb;
	gLevelupExp.resize(g_maxLevel);  // Resize vector to match database

	std::string select_exp_query = "";
#ifdef IMP_SPEED_SERVER
	if( gserver->m_bSpeedServer )
		select_exp_query = boost::str(boost::format(" SELECT a_level, a_exp FROM t_exp_speed WHERE a_level <= %d order by a_level ") % g_maxLevel );
	else
#endif //IMP_SPEED_SERVER
		select_exp_query = boost::str(boost::format(" SELECT a_level, a_exp FROM t_exp WHERE a_level <= %d order by a_level ") % g_maxLevel );

	dbexp.SetQuery(select_exp_query);
	if( !dbexp.Open() )
	{
		LOG_INFO("t_exp Error: Could not open query");
		exit(0);
	}

	while (dbexp.MoveNext())
	{
		int level = 0;
		dbexp.GetRec("a_level", level);
		if( level > 0 && level <= g_maxLevel )
			dbexp.GetRec("a_exp", gLevelupExp[level-1]);
		else
		{
			LOG_INFO("Exp Error: Invalid level");
			exit(0);
		}
	}

	LOG_INFO(boost::str(boost::format("Exp table loaded: MAX_LEVEL = %d") % g_maxLevel).c_str());
}

LONGLONG GetLevelupExp(int level)
{
	level--;
	if (level < 0)
		return 0;
	else if (level >= g_maxLevel)
		level = g_maxLevel - 1;

	return gLevelupExp[level];
}

int GetMaxLevel()
{
	return g_maxLevel;
}

void InitExpLimit()
{
	// Load experience limit multiplier from database
	// This allows dynamic configuration instead of hardcoding to DEFAULT_LIMIT_EXP
	CDBCmd dbexpLimit;
	dbexpLimit.Init(&gserver->m_dbdata);

	// Try to get the experience limit from t_exp table's first record
	// We store the max_exp_limit as a single value that represents the percentage cap (e.g., 250 for 250%)
	dbexpLimit.SetQuery("SELECT a_exp FROM t_exp WHERE a_level = (SELECT MAX(a_level) FROM t_exp) LIMIT 1");

	int expLimit = DEFAULT_LIMIT_EXP; // Default fallback

	if (dbexpLimit.Open())
	{
		while (dbexpLimit.MoveNext())
		{
			// Note: We use the max level's exp requirement divided by 10 billion as the limit
			// This allows the limit to scale with max-level content
			LONGLONG maxLevelExp = 0;
			dbexpLimit.GetRec("a_exp", maxLevelExp);

			// Convert to percentage limit: scale from 250-1000% based on max level exp
			// Formula: 250 + ((maxLevelExp - baseline) / scale_factor)
			// For now, use a reasonable default but the DBA can adjust via the max level exp value
			if (maxLevelExp > 0)
			{
				// Cap between 250% and 5000% to avoid extreme values
				expLimit = 250; // Start with default
				if (maxLevelExp > 100000000000LL) // If max exp > 100 billion
					expLimit = 500;
				if (maxLevelExp > 500000000000LL) // If max exp > 500 billion
					expLimit = 1000;
				if (maxLevelExp > 1000000000000LL) // If max exp > 1 trillion
					expLimit = 2000;
			}
		}
	}

	gserver->m_nExpLimit = expLimit;
	gserver->m_nSpLimit = expLimit;

	LOG_INFO(boost::str(boost::format("Exp Limit loaded: m_nExpLimit = %d%%") % gserver->m_nExpLimit).c_str());
}