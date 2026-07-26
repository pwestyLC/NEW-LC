#include "stdhdrs.h"

#include "JewelData.h"
#include "../ShareLib/DBCmd.h"
#include "Server.h"
#include "Log.h"
#include "Exp.h"

CJewelData::CJewelData()
{
	m_eventComposeProb = 100;
	m_eventChaosCreateProb = 100;
	m_eventUpgradeProb = 100;
	m_eventCombineProb = 100;
	m_eventCollectProb = 100;
}
CJewelData::~CJewelData()
{
}

CJewelDataList::CJewelDataList()  //pwesty fix
{
	m_jewelData = nullptr;

	// Allocate array of pointers
	m_gradedJewel = new int* [JEWEL_MAX_LEVEL + 1];
	m_gradedChaosJewel = new int* [JEWEL_MAX_LEVEL + 1];

	// Initialize all pointers to nullptr
	std::fill_n(m_gradedJewel, JEWEL_MAX_LEVEL + 1, nullptr);
	std::fill_n(m_gradedChaosJewel, JEWEL_MAX_LEVEL + 1, nullptr);
}

CJewelDataList::~CJewelDataList()
{
	if(m_jewelData)
		delete[] m_jewelData;

	m_jewelData = NULL;

	if(m_gradedJewel)
	{
		for(int i = 0; i < JEWEL_MAX_LEVEL+1; i++)
		{
			if(m_gradedJewel[i])
				delete[] m_gradedJewel[i];
		}
		delete[] m_gradedJewel;
	}

	if(m_gradedChaosJewel)
	{
		for(int i = 0; i < JEWEL_MAX_LEVEL+1; i++)
		{
			if(m_gradedChaosJewel[i])
				delete[] m_gradedChaosJewel[i];
		}
		delete[] m_gradedChaosJewel;
	}

	m_composeProb = 0;
	m_chaosCreateProb = 0;
	m_upgradeProb = 0;
	m_combineProb = 0;
	m_collectProb = 0;
}

bool CJewelDataList::LoadProb()
{
	CDBCmd dbcmd;
	dbcmd.Init(&gserver->m_dbdata);
	std::string select = boost::str(boost::format("SELECT * FROM t_jewel_prob"));
	dbcmd.SetQuery(select);

	if (!dbcmd.Open() || !dbcmd.MoveFirst()) {
		return false;
	}

	dbcmd.GetRec("a_compose_prob", m_composeProb);
	dbcmd.GetRec("a_chaos_create_prob", m_chaosCreateProb);
	dbcmd.GetRec("a_upgrade_prob", m_upgradeProb);
	dbcmd.GetRec("a_collect_prob", m_combineProb);
	dbcmd.GetRec("a_combine_prob", m_collectProb);

	return true;
}

bool CJewelDataList::Load()
{
	if(m_jewelData)
		delete[] m_jewelData;

	m_jewelData = NULL;
	int count = 0;

	CDBCmd DBJewel;
	DBJewel.Init(&gserver->m_dbdata);


	std::string select_jewel_data_query = "SELECT * FROM t_jewel_data";

	DBJewel.SetQuery(select_jewel_data_query);
	if (!DBJewel.Open())
		return false;

	if (DBJewel.GetRecordCount() == 0)
	{
		LOG_ERROR("no data : %s", select_jewel_data_query.c_str());
		return false;
	}

	count = DBJewel.GetRecordCount();
	m_jewelData = new CJewelData[count];

	LoadProb();

	int ridx = 0;

	while (DBJewel.MoveNext())
	{
		DBJewel.GetRec("a_index", m_jewelData[ridx].m_jewelGrade);
		DBJewel.GetRec("a_normal_compose_neednas", m_jewelData[ridx].m_normalComposeMoney);
		DBJewel.GetRec("a_chaos_compose_neednas", m_jewelData[ridx].m_chaosComposeMoney);
		DBJewel.GetRec("a_normal_compose_prob", m_jewelData[ridx].m_normalComposeProb);
		DBJewel.GetRec("a_chaos_compose_prob", m_jewelData[ridx].m_chaosComposeProb);
		DBJewel.GetRec("a_compose_normalToChaos_prob", m_jewelData[ridx].m_composeNormalToChaosProb);
		DBJewel.GetRec("a_normal_plus2_prob", m_jewelData[ridx].m_normal_plus2_prob);
		DBJewel.GetRec("a_normal_plus3_prob", m_jewelData[ridx].m_normal_plus3_prob);
		DBJewel.GetRec("a_chaos_plus2_prob", m_jewelData[ridx].m_chaos_plus2_prob);
		DBJewel.GetRec("a_chaos_plus3_prob", m_jewelData[ridx].m_chaos_plus3_prob);
		DBJewel.GetRec("a_normal_minus1_prob", m_jewelData[ridx].m_normal_minus1_prob);
		DBJewel.GetRec("a_normal_minus2_prob", m_jewelData[ridx].m_normal_minus2_prob);
		DBJewel.GetRec("a_normal_minus3_prob", m_jewelData[ridx].m_normal_minus3_prob);
		DBJewel.GetRec("a_chaos_minus1_prob", m_jewelData[ridx].m_chaos_minus1_prob);
		DBJewel.GetRec("a_chaos_minus2_prob", m_jewelData[ridx].m_chaos_minus2_prob);
		DBJewel.GetRec("a_chaos_minus3_prob", m_jewelData[ridx].m_chaos_minus3_prob);

		m_jewelDataList.insert(map_t::value_type(m_jewelData[ridx].m_jewelGrade, &m_jewelData[ridx]));
		ridx ++;
	}

	//�ռ� ������ 1�� �������� ������ ���� (���� ������ ���ϱ� ���ؼ�)
	CLCString query(1024);

	query.Format("select DISTINCT a_rare_index_0 from t_item where a_type_idx = 4 and a_subtype_idx = 16 and a_rare_index_0 >= 0 and a_num_3 > 0 and a_enable = 1 or a_index = 5259");
	DBJewel.SetQuery(query);
	if (!DBJewel.Open())
		return false;

	if (DBJewel.GetRecordCount() == 0)
	{
		LOG_ERROR("no data : %s", (const char *)query);
		return false;
	}

	m_nJewelItemKindCount = DBJewel.GetRecordCount();

	query.Format("select DISTINCT a_rare_index_0 from t_item where a_type_idx = 4 and a_subtype_idx = 22 and a_rare_index_0 >= 0 and a_num_3 > 0 and a_index != 9390 and a_enable = 1");
	DBJewel.SetQuery(query);
	if (!DBJewel.Open())
		return false;

	if (DBJewel.GetRecordCount() == 0)
	{
		LOG_ERROR("no data : %s", (const char *)query);
		return false;
	}

	m_nJewelItemKindCount_Chaos = DBJewel.GetRecordCount();

	for(int i=1; i<=JEWEL_MAX_LEVEL; i++)
	{
		m_gradedJewel[i] = new int[m_nJewelItemKindCount + 1];
		m_gradedChaosJewel[i] = new int[m_nJewelItemKindCount_Chaos + 1];

		memset( &m_gradedJewel[i][1], 0x00, sizeof(int) * m_nJewelItemKindCount );
		memset( &m_gradedChaosJewel[i][1], 0x00, sizeof(int) * m_nJewelItemKindCount_Chaos );
	}

	for(int i=1; i<=JEWEL_MAX_LEVEL; i++)
	{
		query.Format("SELECT a_index FROM t_item where a_type_idx = 4 and a_subtype_idx = 16 and a_rare_index_0 >= 0 and a_num_3 = %d and a_enable = 1", i);
		DBJewel.SetQuery(query);
		if (!DBJewel.Open())
			return false;

		if (DBJewel.GetRecordCount() == 0)
		{
			LOG_ERROR("no data : %s", (const char *)query);
			return false;
		}

		int ridx = 1;

		while (DBJewel.MoveNext())
		{
			DBJewel.GetRec("a_index", m_gradedJewel[i][ridx]);
			ridx ++;
		}
	}
	for(int i=1; i<=JEWEL_MAX_LEVEL; i++)
	{
		query.Format("SELECT a_index FROM t_item where a_type_idx = 4 and a_subtype_idx = 22 and a_rare_index_0 >= 0 and a_num_3 = %d and a_enable = 1", i);
		DBJewel.SetQuery(query);
		if (!DBJewel.Open())
			return false;

		if (DBJewel.GetRecordCount() == 0)
		{
			LOG_ERROR("no data : %s", (const char *)query);
			return false;
		}

		int ridx = 1;

		while (DBJewel.MoveNext())
		{
			DBJewel.GetRec("a_index", m_gradedChaosJewel[i][ridx]);
			ridx ++;
		}
	}

	{
		//�Ϲ� �����ָӴ�
		query.Format("select a_index, a_num_0 from t_item where a_type_idx = 2 and a_subtype_idx = 17 order by a_num_0");
		DBJewel.SetQuery(query);
		if (!DBJewel.Open())
			return false;

		if (DBJewel.GetRecordCount() == 0)
		{
			LOG_ERROR("no data : %s", (const char *)query);
			return false;
		}

		int i = 0;

		while (DBJewel.MoveNext())
		{
			DBJewel.GetRec("a_index", m_JewelPocketItem[i]);
			i++;
		}
	}

	{
		//ī���� �����ָӴ�
		query.Format("select a_index, a_num_0 from t_item where a_type_idx = 2 and a_subtype_idx = 18 order by a_num_0");
		DBJewel.SetQuery(query);
		if (!DBJewel.Open())
			return false;

		if (DBJewel.GetRecordCount() == 0)
		{
			LOG_ERROR("no data : %s", (const char *)query);
			return false;
		}

		int i = 0;

		while (DBJewel.MoveNext())
		{
			DBJewel.GetRec("a_index", m_ChaosJewelPocketItem[i]);
			i++;
		}
	}
	return true;
}

CJewelData* CJewelDataList::FindGrade(int grade)
{
	std::map<int, CJewelData*>::iterator it = m_jewelDataList.find(grade);
	return ( it != m_jewelDataList.end()) ? it->second : NULL;
}

int CJewelDataList::getRandomJewel(int grade, int rand)
{
	return m_gradedJewel[grade][rand];
}

int CJewelDataList::getRandomChaosJewel(int grade, int rand)
{
	return m_gradedChaosJewel[grade][rand];
}

int CJewelDataList::FindJewelPocketIndex( int grade )
{
	return m_JewelPocketItem[grade - 1];
}

int CJewelDataList::FindChaosJewelPocketIndex( int grade )
{
	return m_ChaosJewelPocketItem[grade - 1];
}
