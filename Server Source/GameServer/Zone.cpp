#include <boost/format.hpp>
#include "stdhdrs.h"

#include "Log.h"
#include "Zone.h"
#include "Server.h"
#include "../ShareLib/DBCmd.h"
#include "CmdMsg.h"

CZone::CZone()
	: m_remoteIP(HOST_LENGTH + 1)
#ifdef IMP_SPEED_SERVER
	, m_zone_exp(100), m_zone_sp(100), m_zone_drop(100)
#endif //IMP_SPEED_SERVER
{
	m_index = -1;
	m_bRemote = false;
	m_remotePort = 0;
	m_countY = 0;
	m_attrMap = NULL;
	m_area = NULL;
	m_countArea = 0;
	m_weather = 0;

	m_zonePos = NULL;

	m_shopList = NULL;
	m_nShopCount = 0;
	m_sellRate = 100;
	m_buyRate = 100;

	m_bCanMemPos = false;
	m_bCanSummonPet = false;
	m_bCanMountPet = false;
//#endif
#ifdef CONTINENT_PARTY_RECALL
	m_iContinent_no = -1;
#endif //CONTINENT_PARTY_RECALL

#ifdef SYSTEM_TREASURE_MAP
	m_flag = 0;
	m_treasureAreaCnt = 0;
	m_treasureAreaRotate = 0;
	m_treasureLinkZoneCnt = 0;
	m_treasureLinkZoneIdx = NULL;
	m_pTreasureBoxInfo = NULL;
#endif
    // regen raid init
    m_CNpcRegenRaidList = NULL;
    m_MaxLevelNpcRegen = 0;
}

CZone::~CZone()
{
    // Free regen raid list if allocated
    if (m_CNpcRegenRaidList)
    {
        for (int i = 0; i < m_MaxLevelNpcRegen; ++i)
        {
            if (m_CNpcRegenRaidList[i].m_regenList_InstantDoungen)
            {
                delete [] m_CNpcRegenRaidList[i].m_regenList_InstantDoungen;
                m_CNpcRegenRaidList[i].m_regenList_InstantDoungen = NULL;
            }
        }
        delete [] m_CNpcRegenRaidList;
        m_CNpcRegenRaidList = NULL;
        m_MaxLevelNpcRegen = 0;
    }

	if (m_area)
		delete[] m_area;
	if (m_attrMap)
		delete[] m_attrMap;

	if (m_zonePos)
	{
		for (int i = 0; i < m_countZonePos; i++)
		{
			delete [] m_zonePos[i];
		}
		delete [] m_zonePos;
		m_zonePos = NULL;
	}

	m_index = -1;
	m_bRemote = false;
	m_remotePort = 0;
	m_countY = 0;
	m_attrMap = NULL;
	m_area = NULL;

	if(m_shopList)
		delete [] m_shopList;
	m_shopList = NULL;

	m_nShopCount = 0;
	m_weather = 0;
	m_sellRate = 100;
	m_buyRate = 100;

#ifdef SYSTEM_TREASURE_MAP
	if( m_treasureLinkZoneIdx )
		delete m_treasureLinkZoneIdx;
	if( m_pTreasureBoxInfo )
		delete [] m_pTreasureBoxInfo;
#endif
}

bool CZone::LoadZone(int seq)
{
    // If reloading zone data, free previous allocations to avoid leaks and stale pointers
    if (m_attrMap)
    {
        delete [] m_attrMap;
        m_attrMap = NULL;
    }

    if (m_area)
    {
        delete [] m_area;
        m_area = NULL;
    }

    if (m_zonePos)
    {
        for (int _i = 0; _i < m_countZonePos; _i++)
        {
            delete [] m_zonePos[_i];
        }
        delete [] m_zonePos;
        m_zonePos = NULL;
        m_countZonePos = 0;
    }

#ifdef SYSTEM_TREASURE_MAP
    if (m_pTreasureBoxInfo)
    {
        delete [] m_pTreasureBoxInfo;
        m_pTreasureBoxInfo = NULL;
    }
    if (m_treasureLinkZoneIdx)
    {
        delete [] m_treasureLinkZoneIdx;
        m_treasureLinkZoneIdx = NULL;
    }
    m_treasureAreaCnt = 0;
    m_treasureLinkZoneCnt = 0;
#endif

    // Clear shop list and map if present (LoadShop will repopulate)
    if (m_shopList)
    {
        delete [] m_shopList;
        m_shopList = NULL;
        m_nShopCount = 0;
    }
    map_.clear();

	if (seq < 0 || seq >= gserver->m_numZone)
		return false;

	GAMELOG << init("SYSTEM")
			<< "Loading zone ";

	CLCString zonegroup(100);
	zonegroup.Format("Zone_%d", seq);

	const char* p;
	int i;

	if (!(p = gserver->m_config.Find(zonegroup, "No")))
		return false;
	m_index = atoi(p);

	GAMELOG << m_index
			<< end;

	CDBCmd cmd;
	cmd.Init(&gserver->m_dbdata);
	std::string select_zonedata_query = boost::str(boost::format("SELECT * FROM t_zonedata WHERE a_zone_index = %d") % m_index);
	cmd.SetQuery(select_zonedata_query);
	if (!cmd.Open() || !cmd.MoveFirst())
		return false;

	p = gserver->m_config.Find(zonegroup, "Remote");
	if (!p || strcmp(p, "FALSE") == 0)
	{
		m_bRemote = false;

		int sizex, sizez;
		if (!cmd.GetRec("a_width", sizex))
			return false;
		if (!cmd.GetRec("a_height", sizez))
			return false;

		if (!cmd.GetRec("a_ylayer", m_countY))
			return false;

		CLCString attrmaps(65536);
		CLCString heightmaps(65536);

		if (!cmd.GetRec("a_attrmap", attrmaps))
			return false;
		if (!cmd.GetRec("a_heightmap", heightmaps))
			return false;

		if (!cmd.GetRec("a_minlevel", m_minLevel))
			return false;
		if (!cmd.GetRec("a_maxlevel", m_maxLevel))
			return false;

		const char* pattr = attrmaps;
		const char* pheight = heightmaps;

		m_attrMap = new CMapAttr[m_countY];
		char tmpBuf[1024] = {0,};
		char tmpBuf1[1024] = {0,};
		for (i = 0; i < m_countY; i++)
		{
			pattr = AnyOneArg(pattr, tmpBuf);
			pheight = AnyOneArg(pheight, tmpBuf1);

			if (!m_attrMap[i].Load(seq, i, sizex, sizez, tmpBuf, tmpBuf1))
				return false;
		}

#ifdef SYSTEM_TREASURE_MAP
		CLCString treasureArea(256);
		CLCString treasureDungeon(256);
		if( !cmd.GetRec("a_flag", m_flag))
			return false;
		if( !cmd.GetRec("a_treasurecount", m_treasureAreaCnt))
			return false;
		if( !cmd.GetRec("a_treasurecount_dungeon", m_treasureLinkZoneCnt))
			return false;
		if( m_treasureAreaCnt > 0)
		{
			if( !cmd.GetRec("a_treasure_area", treasureArea))
				return false;
			m_pTreasureBoxInfo = new TREASUREBOXINFO[m_treasureAreaCnt];

			const char* ta = treasureArea;
			char left[8];
			char top[8];
			char right[8];
			char bottom[8];
			char regenMax[8];
			int i=0;

			for(i=0; i<m_treasureAreaCnt; i++)
			{
				ta = AnyOneArg(ta, left);
				ta = AnyOneArg(ta, top);
				ta = AnyOneArg(ta, right);
				ta = AnyOneArg(ta, bottom);
				ta = AnyOneArg(ta, regenMax);

				m_pTreasureBoxInfo[i].rect.left = atof(left);
				m_pTreasureBoxInfo[i].rect.top = atof(top);
				m_pTreasureBoxInfo[i].rect.right = atof(right);
				m_pTreasureBoxInfo[i].rect.bottom = atof(bottom);
				m_pTreasureBoxInfo[i].max = atoi(regenMax);
			}
		}

		if( m_treasureLinkZoneCnt == 0)
		{
			m_treasureLinkZoneIdx = NULL;
		}
		else
		{
			if( !cmd.GetRec("a_treasure_dengeon", treasureDungeon))
				return false;

			m_treasureLinkZoneIdx = new int[m_treasureLinkZoneCnt];
			int i=0;
			const char* td = treasureDungeon;
			char dIdx[8];
			for(i=0; i<m_treasureLinkZoneCnt; i++)
			{
				td = AnyOneArg(td, dIdx);
				m_treasureLinkZoneIdx[i] = atoi(dIdx);
			}
		}

#endif
		if( !cmd.GetRec("a_areacount", m_countArea) )
			return false;
		if( m_countArea < 1 )
			return false;

		if(m_index != ZONE_GUILDROOM && m_index != ZONE_SINGLE_DUNGEON_TUTORIAL)
		{
			if( m_countArea > MAX_AREA_COUNT)
			{
				LOG_ERROR("a_areacount over flow... areaCount[%d], maxCount[%d]", m_countArea, MAX_AREA_COUNT);
				return false;
			}
		}
		
		m_area = new CArea[m_countArea];
		for (i = 0; i < m_countArea; i++)
			m_area[i].Init(this, i, sizex, sizez, m_countY);
	}
	else
	{
		m_bRemote = true;

		p = gserver->m_config.Find(zonegroup, "Remote_IP");
		if (!p)
			return false;
		m_remoteIP = p;

		p = gserver->m_config.Find(zonegroup, "Remote_Port");
		if (!p)
			return false;
		m_remotePort = (unsigned short)atoi(p);
	}

	char canusemempos;
	if (!cmd.GetRec("a_canusemempos", canusemempos))
		return false;
	m_bCanMemPos = (canusemempos) ? true : false;

	char cansummonpet;
	if (!cmd.GetRec("a_cansummonpet", cansummonpet))
		return false;
	m_bCanSummonPet = (cansummonpet) ? true : false;

	char canmountpet;
	if (!cmd.GetRec("a_canmountpet", canmountpet))
		return false;
	m_bCanMountPet = (canmountpet) ? true : false;

#ifdef CONTINENT_PARTY_RECALL
	int continent_no;
	if(!cmd.GetRec("a_continent_no", continent_no))
		return false;
	m_iContinent_no = continent_no;
#endif //CONTINENT_PARTY_RECALL

	// ���� ���� ��ġ �б�
	char poscount;
	CLCString posylayer(256);
	CLCString posleft(256);
	CLCString postop(256);
	CLCString posright(256);
	CLCString posbottom(256);

	if (!cmd.GetRec("a_poscount", poscount))
		return false;
	if (!cmd.GetRec("a_posylayer", posylayer))
		return false;
	if (!cmd.GetRec("a_posleft", posleft))
		return false;
	if (!cmd.GetRec("a_postop", postop))
		return false;
	if (!cmd.GetRec("a_posright", posright))
		return false;
	if (!cmd.GetRec("a_posbottom", posbottom))
		return false;

	const char* pylayer = posylayer;
	const char* pleft = posleft;
	const char* ptop = postop;
	const char* pright = posright;
	const char* pbottom = posbottom;

	m_countZonePos = poscount;
	if (m_index == ZONE_MERAC && m_countZonePos < 17)
	{
		GAMELOG << init("ERROR")
				<< "ZONE MERAC MUST HAVE 17 REGEN POSITION"
				<< end;
		return false;
	}
	m_zonePos = new int*[m_countZonePos];
	for (i = 0; i < m_countZonePos; i++)
	{
		m_zonePos[i] = new int[5];

		char sy[256];
		char sl[256];
		char st[256];
		char sr[256];
		char sb[256];

		pylayer = AnyOneArg(pylayer, sy);
		pleft = AnyOneArg(pleft, sl);
		ptop = AnyOneArg(ptop, st);
		pright = AnyOneArg(pright, sr);
		pbottom = AnyOneArg(pbottom, sb);

		m_zonePos[i][0] = atoi(sy);
		m_zonePos[i][1] = (int)(atof(sl) * 2);
		m_zonePos[i][2] = (int)(atof(st) * 2);
		m_zonePos[i][3] = (int)(atof(sr) * 2);
		m_zonePos[i][4] = (int)(atof(sb) * 2);
	}

	// ���̵� ���� npc ���� ����Ʈ�� ���� �����ȴ�.
	if ( m_index == ZONE_CAPPELLA_1 || m_index == ZONE_ALTER_OF_DARK || m_index == ZONE_AKAN_TEMPLE
			|| m_index == ZONE_DUNGEON4
			|| m_index == ZONE_TARIAN_DUNGEON
			|| m_index == ZONE_ENCHANTED_DUNGEON
	   #ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
		|| m_index == ZONE_PARTY_DUNGEON0
		|| m_index == ZONE_PARTY_DUNGEON1
		|| m_index == ZONE_PARTY_DUNGEON2
		|| m_index == ZONE_PARTY_DUNGEON3
		|| m_index == ZONE_PARTY_DUNGEON4
#endif
		)
	{
		GAMELOG << init("SYSTEM")
				<< m_index << delim
				<< " : Load_NpcRegenRaidList()"
				<< end;
		if(!Load_NpcRegenRaidList())
		{
			GAMELOG << init("ERROR")
					<< m_index << delim
					<< " : Load_NpcRegenRaidList() error"
					<< end;
			return false;
		}
	}

#ifdef IMP_SPEED_SERVER
	std::string select_speed_zone_query = boost::str(boost::format("SELECT a_exp, a_sp, a_drop FROM t_speed_zone WHERE a_zone_index = %d") % m_index);
	cmd.SetQuery( select_speed_zone_query );
	if( cmd.Open() && cmd.MoveFirst() )
	{
		cmd.GetRec("a_exp",m_zone_exp);
		cmd.GetRec("a_sp",m_zone_sp);
		cmd.GetRec("a_drop",m_zone_drop);
	}
#endif //IMP_SPEED_SERVER

	return true;
}


bool CZone::LoadNPC()
{
    // If reloading NPC data, free previous regen raid list to avoid leaks
    if (m_CNpcRegenRaidList)
    {
        for (int _i = 0; _i < m_MaxLevelNpcRegen; ++_i)
        {
            if (m_CNpcRegenRaidList[_i].m_regenList_InstantDoungen)
            {
                delete [] m_CNpcRegenRaidList[_i].m_regenList_InstantDoungen;
                m_CNpcRegenRaidList[_i].m_regenList_InstantDoungen = NULL;
            }
        }
        delete [] m_CNpcRegenRaidList;
        m_CNpcRegenRaidList = NULL;
        m_MaxLevelNpcRegen = 0;
    }

	if (m_bRemote)
		return true;

	std::vector<tag_npc_regen_info> vecNormal;
	std::vector<tag_boss_regen_info> vecBoss;

	
	{
		CDBCmd dbNpcRegen;
		dbNpcRegen.Init(&gserver->m_dbdata);

		std::string qry = boost::str(boost::format(
			"SELECT * FROM t_npc_regen WHERE a_zone_num = %d ORDER BY a_index") % this->m_index);

		dbNpcRegen.SetQuery(qry);
		if (dbNpcRegen.Open() == false)
			return false;

		vecNormal.reserve(dbNpcRegen.GetRecordCount());

		tag_npc_regen_info info;

		while (dbNpcRegen.MoveNext())
		{
			dbNpcRegen.GetRec("a_index", info.index);
			dbNpcRegen.GetRec("a_npc_idx", info.npcIndex);
			dbNpcRegen.GetRec("a_pos_x", info.x);
			dbNpcRegen.GetRec("a_y_layer", info.yLayer);
			dbNpcRegen.GetRec("a_pos_z", info.z);
			dbNpcRegen.GetRec("a_pos_r", info.r);


			dbNpcRegen.GetRec("a_regen_sec", info.regenSec);
			dbNpcRegen.GetRec("a_total_num", info.totalNum);

			info.pNPCProto = gserver->m_npcProtoList.FindProto(info.npcIndex);
			if (info.pNPCProto == NULL)
				continue;

			// Check if NPC is enabled in t_npc table
			CDBCmd dbNpc;
			dbNpc.Init(&gserver->m_dbdata);
			std::string npcQry = boost::str(boost::format(
				"SELECT a_enable FROM t_npc WHERE a_index = %d") % info.npcIndex);
			dbNpc.SetQuery(npcQry);

			if (dbNpc.Open())
			{
				int enabled = 0;
				if (dbNpc.MoveNext())
				{
					dbNpc.GetRec("a_enable", enabled);
				}
				// Skip disabled NPCs
				if (enabled == 0)
					continue;
			}

#if defined (LC_GAMIGO) || defined (LC_BILA) || defined (LC_USA) || defined (LC_RUS)
			if ((info.npcIndex == 1624 || info.npcIndex == 1620) && gserver->m_subno != 1)
				continue;

			if ((info.npcIndex == 1734) && gserver->m_subno != 1)
				continue;
#endif

			vecNormal.push_back(info);
		}
	}

	// -------------------------
	// 2) Load boss regen (NEW)
	// -------------------------
	{
		CDBCmd dbBoss;
		dbBoss.Init(&gserver->m_dbdata);

		std::string qry = boost::str(boost::format(
			"SELECT * FROM t_regen_boss WHERE a_zone_num = %d AND a_enabled = 1 ORDER BY a_index") % this->m_index);

		dbBoss.SetQuery(qry);
		if (dbBoss.Open() == false)
			return false;

		vecBoss.reserve(dbBoss.GetRecordCount());

		tag_boss_regen_info b;

		while (dbBoss.MoveNext())
		{
			int respawnSec = 0;

			dbBoss.GetRec("a_index", b.index);
			dbBoss.GetRec("a_npc_idx", b.npcIndex);
			dbBoss.GetRec("a_pos_x", b.x);
			dbBoss.GetRec("a_y_layer", b.yLayer);
			dbBoss.GetRec("a_pos_z", b.z);
			dbBoss.GetRec("a_pos_r", b.r);
			dbBoss.GetRec("a_total_num", b.totalNum);
			dbBoss.GetRec("a_respawn_sec", respawnSec);

			
			b.regenPulse = respawnSec * PASSES_PER_SEC;

			// safety: default to 30 minutes if DB is bad
			if (b.regenPulse <= 0)
				b.regenPulse = PULSE_REAL_HALF;

			b.pNPCProto = gserver->m_npcProtoList.FindProto(b.npcIndex);
			if (!b.pNPCProto)
				continue;

			vecBoss.push_back(b);

			GAMELOG << init("BOSS REGEN LOAD")
				<< "NPC_IDX" << delim << b.npcIndex
				<< "ZONE" << delim << this->m_index
				<< "RESPAWN_SEC" << delim << respawnSec
				<< "RESPAWN_PULSE" << delim << b.regenPulse
				<< "X" << delim << b.x
				<< "Z" << delim << b.z
				<< "Y" << delim << (int)b.yLayer
				<< end;
		}
	}


	bool setenable_flag = false;

#ifdef EXTREME_CUBE
	if (IsExtremeCube())
		setenable_flag = true;
#endif

	if (IsWarGroundZone())
		setenable_flag = true;

	for (int i = 0; i < m_countArea; i++)
	{
		m_area[i].LoadNPC(vecNormal);       // normal regen
		m_area[i].LoadBossNPC(vecBoss);     // boss regen (NEW)

		if (setenable_flag)
			m_area[i].SetEnable();

		if (CanFreezeZone())
			m_area[i].SetFreeze(gserver->m_pulse);
	}

	if (m_countArea == 1)
		m_area[0].SetEnable();

	return true;
}


bool CZone::LoadShop()
{
	bool bRet = true;

	if (m_bRemote)
		return true;

    // Clear existing shop map so we don't leave dangling pointers
    map_.clear();

	if (m_shopList)
		delete [] m_shopList;
	m_shopList = NULL;

	GAMELOG << init("SYSTEM")
			<< "Shop Loading Zone "
			<< m_index
			<< end;

	// area�� ���� �ش� �� �ѹ��� Shop���� READ
	CDBCmd dbShop;
	dbShop.Init(&gserver->m_dbdata);
	std::string select_shop_query = boost::str(boost::format("SELECT * FROM t_shop WHERE a_zone_num = %d ORDER BY a_keeper_idx") % m_index);
	dbShop.SetQuery(select_shop_query);
    if (!dbShop.Open())
    {
        GAMELOG << init("ERROR") << "LoadShop: failed to open shop query for zone " << m_index << end;
        m_nShopCount = 0;
        return false;
    }

	m_nShopCount = dbShop.GetRecordCount();

    if (m_nShopCount < 1)
    {
        // nothing to load, map_ already cleared
        return true;
    }

	m_shopList = new CShop[m_nShopCount];

	int idx = 0;

	CDBCmd dbShopItem;
	dbShopItem.Init(&gserver->m_dbdata);

	//CNPC* npc;
	while (dbShop.MoveNext())
	{
		dbShop.GetRec("a_keeper_idx",	m_shopList[idx].m_keeperIdx);
		dbShop.GetRec("a_sell_rate",	m_shopList[idx].m_sellRate);
		dbShop.GetRec("a_buy_rate",		m_shopList[idx].m_buyRate);

		dbShop.GetRec("a_pos_x",		m_shopList[idx].m_x);
		dbShop.GetRec("a_pos_z",		m_shopList[idx].m_z);
		dbShop.GetRec("a_pos_r",		m_shopList[idx].m_r);
		dbShop.GetRec("a_pos_h",		m_shopList[idx].m_h);
		dbShop.GetRec("a_y_layer",		m_shopList[idx].m_yLayer);

		CLCString sql(2048);

#ifdef LC_KOR
		sql.Format(
			"SELECT * FROM t_shopitem where a_keeper_idx = %d ORDER BY a_item_idx"
			, m_shopList[idx].m_keeperIdx);
#elif defined (LC_GAMIGO)
		//���̰��� ���� ���� �������� shop �������� �����Ѵ�.
		sql.Format(
			"SELECT * FROM t_shopitem where a_keeper_idx = %d ORDER BY a_item_idx"
			, m_shopList[idx].m_keeperIdx, 13);			//LC_GER = 13
#else
		sql.Format(
			"SELECT * FROM t_shopitem where a_keeper_idx = %d and !(a_national & (1 << %d) ) ORDER BY a_item_idx"
			, m_shopList[idx].m_keeperIdx, gserver->m_national);
#endif
        dbShopItem.SetQuery(sql);
        if (!dbShopItem.Open())
        {
            // failed to load items for this shop, set to empty
            m_shopList[idx].m_itemCount = 0;
            m_shopList[idx].m_itemDBIdx = NULL;
        }
        else
        {
            // load items
            m_shopList[idx].m_itemCount = dbShopItem.GetRecordCount();
            if (m_shopList[idx].m_itemCount > 0)
            {
                m_shopList[idx].m_itemDBIdx = new int[m_shopList[idx].m_itemCount];
                int itemDBIdx = 0;
                while(dbShopItem.MoveNext())
                    m_shopList[idx].m_itemDBIdx[itemDBIdx++] = atoi(dbShopItem.GetRec("a_item_idx"));
            }
            else
            {
                m_shopList[idx].m_itemDBIdx = NULL;
            }
        }

		if (m_shopList[idx].m_sellRate < 0 || m_shopList[idx].m_buyRate < 0)
		{
			GAMELOG << init("ERROR: SHOP SELL/BUY RATE")
					<< m_index << delim
					<< m_shopList[idx].m_keeperIdx << delim
					<< m_shopList[idx].m_sellRate << delim
					<< m_shopList[idx].m_buyRate
					<< end;
			bRet = false;
		}

		map_.insert(map_t::value_type(m_shopList[idx].m_keeperIdx, &m_shopList[idx]));

		idx++;
	}

	// Update existing NPC instances positions for shop keepers so reload takes effect immediately
	for (int s = 0; s < m_countArea; ++s)
	{
		if (!m_area)
			break;
		CNPC* p = m_area[s].m_npcList;
		while (p)
		{
			CNPC* next = p->m_pNPCNext;
			if (p->m_proto)
			{
				// find matching shop entry
				for (int si = 0; si < m_nShopCount; ++si)
				{
					if (p->m_proto->m_index == m_shopList[si].m_keeperIdx)
					{
						// remove from current cell if in one
						if (IS_IN_CELL(p) && p->m_pArea)
							p->m_pArea->CharFromCell(p, false);

						// update coords
						GET_X(p) = m_shopList[si].m_x;
						GET_Z(p) = m_shopList[si].m_z;
						GET_R(p) = m_shopList[si].m_r;
						GET_YLAYER(p) = (char)m_shopList[si].m_yLayer;
						p->m_pos.m_h = m_shopList[si].m_h;

						// re-insert into area cell
						int cx, cz;
						if (p->m_pArea)
						{
							p->m_pArea->PointToCellNum(GET_X(p), GET_Z(p), &cx, &cz);
							p->m_pArea->CharToCell(p, GET_YLAYER(p), cx, cz);
							// notify clients around the NPC
							{
								CNetMsg::SP rmsg(new CNetMsg);
								AppearMsg(rmsg, p);
								p->m_pArea->SendToCell(rmsg, p, true);
							}
						}
						break; // matched shop entry
					}
				}
			}
			p = next;
		}
	}

	return bRet;
}

int CZone::SetEnableArea()
{
	int idx;
	for (idx = 0; idx < m_countArea; idx++)
	{
		if (!m_area[idx].m_bEnable)
			break;
	}
	if (idx == m_countArea)
	{
		LOG_INFO("AREA_LOG. ENABLE_ERROR : CountArea[%d], ZoneIndex[%d], AreaIndex[%d]", m_countArea, this->m_index, idx);
		return -1;
	}

	m_area[idx].SetEnable();
	LOG_INFO("AREA_LOG. ENABLE_AREA : CountArea[%d], ZoneIndex[%d], AreaIndex[%d]", m_countArea, this->m_index, idx);

	return idx;
}

void CZone::SetDisableArea(int idx)
{
	if (idx < 0  || idx >= m_countArea)
	{
		LOG_INFO("AREA_LOG. DISABLE_ERROR : CountArea[%d], ZoneIndex[%d], AreaIndex[%d]", m_countArea, this->m_index, idx);
		return ;
	}
	m_area[idx].SetDisable();
	LOG_INFO("AREA_LOG. DISABLE_AREA : CountArea[%d], ZoneIndex[%d], AreaIndex[%d]", m_countArea, this->m_index, idx);
}

// npc index�� ���� shop ã��
CShop* CZone::FindShop(int npcIdx)
{
	map_t::iterator it = map_.find(npcIdx);
	return (it != map_.end()) ? it->second : NULL;
}

void CZone::ChangeWeather()
{
	int i;
	unsigned char before = m_weather;

	switch (m_weather)
	{
	case 0:// ����
		if (!GetRandom(0, 5))
			m_weather = 1;
		break;
	case 1: // �帲
		i = GetRandom(0, 2);
		if (i == 0)
			m_weather = 0;
		else if (i == 1)
			m_weather = 2;
		break;
	case 2:
		if (!GetRandom(0, 1))
			m_weather = 1;
		else
			m_weather = 3;
		break;
	case 3: // �� �ɱ� ��...
		if (!GetRandom(0, 1))
			m_weather = 2;
		else
			m_weather = 4;
		break;
	case 4: //�� ��â ��....
		if (!GetRandom(0, 1))
			m_weather = 3;
		break;
	default:
		m_weather = 2;
		break;
	}

	if (before != m_weather)
	{
		for (i=0; i < m_countArea; i++)
		{
			CNetMsg::SP rmsg(new CNetMsg);
			EnvWeatherMsg(rmsg, this->m_index);
			this->m_area[i].SendToAllClient(rmsg);
		}
	}
}

int CZone::FindEmptyArea()
{
	int idx;

	for (idx = 0; idx < m_countArea; idx++)
	{
		if (!m_area[idx].m_bEnable)
			return idx;
	}

	return -1;
}

int CZone::FindComboArea(int comboidx)
{
	if(m_index != ZONE_COMBO_DUNGEON)
		return -1;

	int i;
	for(i = 0 ; i < m_countArea; ++i)
	{
		if(!m_area[i].m_bEnable)
			continue;

		if(!m_area[i].m_monsterCombo)
			continue;

		if(m_area[i].m_monsterCombo->m_nIndex == comboidx)
			return i;
	}

	return -1;
}

int CZone::GetExtra(int x, int z)
{
	for (int i = 0; i < m_countZonePos; i++)
	{
		if ((m_zonePos[i][1] / 2) < x && (m_zonePos[i][2] / 2) < z && (m_zonePos[i][3] / 2) > x && (m_zonePos[i][4] / 2) > z)
		{
			return i;
		}
	}

	return -1;
}

bool CZone::isRVRZone()
{
	if(m_index == ZONE_RVR)
		return true;

	return false;
}

#ifdef WARCASTLE_MOVE_MESSAGE_LIMIT
bool CZone::InExtra(int x, int z, int extra)
{
	if( extra < 0 || extra >= m_countZonePos)
		return false;

	if( m_zonePos == NULL )
		return false;

	if (   (m_zonePos[extra][1] / 2) <= x && (m_zonePos[extra][2] / 2) <= z
			&& (m_zonePos[extra][3] / 2) >= x && (m_zonePos[extra][4] / 2) >= z)
		return true;

	return false;
}
#endif // #ifdef WARCASTLE_MOVE_MESSAGE_LIMIT

bool CZone::Load_NpcRegenRaidList()
{
	int i, j;
	CDBCmd dbcmd;
	dbcmd.Init(&gserver->m_dbdata);

	// 1. ���� ���� ����Ʈ���� ������ ������ ���Ѵ�.
	std::string select_npc_regen_raid_query = boost::str(boost::format("SELECT count(a_store_middle) as level FROM t_npc_regen_raid WHERE a_zone_num= %d GROUP BY a_store_middle") % m_index);
	dbcmd.SetQuery(select_npc_regen_raid_query);
	if (!dbcmd.Open())
	{
		GAMELOG << init("LoadNpcRegen_Raid step 1")
				<< end;
		return false;
	}
	if(!dbcmd.MoveFirst())
	{
		GAMELOG << init("LoadNpcRegen_Raid : ZERO")
				<< end;
		return false;
	}

	m_MaxLevelNpcRegen = dbcmd.GetRecordCount();
	m_CNpcRegenRaidList = new CNpc_Regen_Raid[m_MaxLevelNpcRegen];

	// 2. �� zone�� �ش��ϴ� regen ������ ���� ���� �޾Ƽ� �����Ѵ�.
	for (i=0; i < m_MaxLevelNpcRegen; i++)
	{
		std::string select_npc_regen_raid_queyr = boost::str(boost::format(
					"SELECT a_npc_idx, a_pos_x, a_pos_z, a_pos_h, a_pos_r, a_y_layer, a_store_middle FROM t_npc_regen_raid WHERE a_zone_num= %d AND a_store_middle = %d")
				% m_index % i);
		dbcmd.SetQuery(select_npc_regen_raid_queyr);
		if (!dbcmd.Open())
		{
			GAMELOG << init("LoadNpcRegen_Raid step 2")
					<< end;
			return false;
		}
		dbcmd.MoveFirst();

		m_CNpcRegenRaidList[i].m_nCount_regen = dbcmd.GetRecordCount();
		int regenCount = dbcmd.GetRecordCount();
		m_CNpcRegenRaidList[i].m_regenList_InstantDoungen = new NPC_REGEN_FOR_RAID[regenCount];

		for (j=0; j < regenCount; j++)
		{
			dbcmd.GetRec("a_npc_idx",		m_CNpcRegenRaidList[i].m_regenList_InstantDoungen[j].m_npcIdx);
			dbcmd.GetRec("a_pos_x",			m_CNpcRegenRaidList[i].m_regenList_InstantDoungen[j].m_pos_x);
			dbcmd.GetRec("a_pos_z",			m_CNpcRegenRaidList[i].m_regenList_InstantDoungen[j].m_pos_z);
			dbcmd.GetRec("a_pos_h",			m_CNpcRegenRaidList[i].m_regenList_InstantDoungen[j].m_pos_h);
			dbcmd.GetRec("a_pos_r",			m_CNpcRegenRaidList[i].m_regenList_InstantDoungen[j].m_pos_r);
			dbcmd.GetRec("a_y_layer",		m_CNpcRegenRaidList[i].m_regenList_InstantDoungen[j].m_y_layer);
			dbcmd.GetRec("a_store_middle",	m_CNpcRegenRaidList[i].m_regenList_InstantDoungen[j].m_storeMiddle);

			dbcmd.MoveNext();
		}
	}

	return true;
}


#ifdef SYSTEM_TREASURE_MAP
void CZone::RemoveTreasureBoxNpc(CNPC * pNpc)
{
	if( pNpc == NULL)
		return ;

	if( !m_pTreasureBoxInfo  )
		return ;

	int i;
	for(i=0; i<m_treasureAreaCnt; i++)
	{
		m_pTreasureBoxInfo[i].RemoveTreasureBoxNpc( pNpc );
	}
}

int CZone::NextAreaNum()
{
	if( m_treasureAreaCnt == 0 )
		return -1;
	m_treasureAreaRotate ++;
	if( m_treasureAreaRotate >= m_treasureAreaCnt )
		m_treasureAreaRotate = 0;

	return m_treasureAreaRotate;
}

bool CZone::SummonTreaseureBoxNpc(int& x, int& z, int& zoneNum)
{
	if( !IsFieldZone() )
		return false;

	CZone * pZone = this;

	// ���� ���� ����� ������ ������ ����������� ������.
	// ���� ���� ������ ���������� 10% Ȯ���� ������.
	if( gserver->bTreasureMapLinkZoneDrop && m_treasureLinkZoneIdx
			&& ( m_treasureAreaCnt == 0
				 || ( m_treasureLinkZoneCnt > 0 && GetRandom(0, 10000) < 1000 ) ) )
	{
		int LinkZoneIndex = GetRandom(0, m_treasureLinkZoneCnt-1 );

		// ���� ���� �ε����� �����´�.
		LinkZoneIndex = m_treasureLinkZoneIdx[LinkZoneIndex];
		pZone = gserver->FindZone(LinkZoneIndex);
		if (pZone == NULL)
			return false;

		// �������ε� ���� �� ���� �������� ������ ��� ���� ó��
		if( !pZone->CheckTreasureDropFlag() )
		{
			//return false; // ����ó���ϸ� ���� Ȯ���� �������ϱ�. ���� �ʿ��� �������� ó��������.
			pZone = this;
		}
	}

	// ���� ���� ���� ������ ã�ƺ���.
	int areaNum = pZone->NextAreaNum();
	if( areaNum == -1 )
		return false;

	// ���� ������ ŭ �� ã�ٸ� �����ϰ� �ϳ��� ��ǥ�� �ݳ� ����.
	if( pZone->m_pTreasureBoxInfo && pZone->m_pTreasureBoxInfo[areaNum].GetEmptyRegenCount() <= 0 )
	{
		int rndNpcNum = GetRandom(0,pZone->m_pTreasureBoxInfo[areaNum].max -1 );
		if (rndNpcNum >= pZone->m_pTreasureBoxInfo[areaNum].listNpc.size())
		{
			return false;
		}

		CNPC* pNpc = pZone->m_pTreasureBoxInfo[areaNum].listNpc[rndNpcNum];
		x = (int)GET_X(pNpc);
		z = (int)GET_Z(pNpc);
		zoneNum = pZone->m_index;
		return true;
	}

	// npc summon
	CNPC* pTBoxNpc = gserver->m_npcProtoList.Create( TREASURE_BOX_NPC_INDEX , NULL);
	if( !pTBoxNpc )
		return false;

	GET_YLAYER(pTBoxNpc) = 0;

	int repeat = 0;
	while(1)
	{
		GET_X(pTBoxNpc) = GetRandom((int)pZone->m_pTreasureBoxInfo[areaNum].rect.left, (int)pZone->m_pTreasureBoxInfo[areaNum].rect.right);
		GET_Z(pTBoxNpc) = GetRandom((int)pZone->m_pTreasureBoxInfo[areaNum].rect.top, (int)pZone->m_pTreasureBoxInfo[areaNum].rect.bottom);

		if( m_area->GetAttr(0, GET_X(pTBoxNpc), GET_Z(pTBoxNpc)) & MATT_WALKABLE
				&& !(m_area->GetAttr(0, GET_X(pTBoxNpc), GET_Z(pTBoxNpc)) & MATT_PEACE)
				&& !(m_area->GetAttr(0, GET_X(pTBoxNpc), GET_Z(pTBoxNpc)) & MATT_PRODUCT_PUBLIC)
				&& !(m_area->GetAttr(0, GET_X(pTBoxNpc), GET_Z(pTBoxNpc)) & MATT_PRODUCT_PRIVATE)
				&& !(m_area->GetAttr(0, GET_X(pTBoxNpc), GET_Z(pTBoxNpc)) & MATT_STAIR_UP)
				&& !(m_area->GetAttr(0, GET_X(pTBoxNpc), GET_Z(pTBoxNpc)) & MATT_STAIR_DOWN)
				&& !(m_area->GetAttr(0, GET_X(pTBoxNpc), GET_Z(pTBoxNpc)) & MATT_WAR)
				&& !(m_area->GetAttr(0, GET_X(pTBoxNpc), GET_Z(pTBoxNpc)) & MATT_FREEPKZONE)	)
			break;

		repeat ++;
		if( repeat > 1000 ) // Ȥ�ó�.... ������ �̻��� ������ �����ؼ� ���� ������ ���� �𸣴�... �Ѥ�;;
		{
			GAMELOG << init("TBNPC REGEN error" )
					<< "zonenum : " << pZone->m_index << delim << "areanum : " << areaNum << end;
			delete pTBoxNpc;
			pTBoxNpc = NULL;
			return false;
		}
	}

	pTBoxNpc->m_regenX = GET_X(pTBoxNpc);
	pTBoxNpc->m_regenZ = GET_Z(pTBoxNpc);
	pTBoxNpc->m_regenY = GET_YLAYER(pTBoxNpc);

	x = (int)pTBoxNpc->m_regenX;
	z = (int)pTBoxNpc->m_regenZ;
	zoneNum = pZone->m_index;

	int cx, cz;
	pZone->m_area->AddNPC(pTBoxNpc);
	pTBoxNpc->m_pArea->PointToCellNum(GET_X(pTBoxNpc), GET_Z(pTBoxNpc), &cx, &cz);
	pTBoxNpc->m_pArea->CharToCell(pTBoxNpc, GET_YLAYER(pTBoxNpc), cx, cz);

	{
		CNetMsg::SP rmsg(new CNetMsg);
		AppearMsg(rmsg, pTBoxNpc, true);
		pTBoxNpc->m_pArea->SendToCell(rmsg, GET_YLAYER(pTBoxNpc), cx, cz);
	}

	pZone->m_pTreasureBoxInfo[areaNum].listNpc.push_back( pTBoxNpc );
	return true;
}

bool CZone::SetTresaureMapInfo(CItem * pItem)
{
	int plus = pItem->getPlus();
	int plus2 = pItem->getPlus_2();
	int used2 = pItem->getUsed_2();

	bool retbool = SummonTreaseureBoxNpc(plus, plus2, used2);

	pItem->setPlus(plus);
	pItem->setPlus_2(plus2);
	pItem->setUsed_2(used2);

	return retbool;
}

TREASUREBOXINFO::TREASUREBOXINFO()
{
	max=0;
}

TREASUREBOXINFO::~TREASUREBOXINFO()
{
}

int	TREASUREBOXINFO::GetEmptyRegenCount()
{
	return max - listNpc.size();
}
bool TREASUREBOXINFO::SetTreasureBoxNpc(CNPC* pNpc)
{
	if( listNpc.size() >= max )
		return false;

	listNpc.push_back(pNpc);
	return true;
}

void TREASUREBOXINFO::RemoveTreasureBoxNpc(CNPC * pNpc)
{
// 	vec_t::iterator it = listNpc.begin();
// 	vec_t::iterator endit = listNpc.end();
// 	for (; it != endit;)
// 	{
// 		if ((*it) == pNpc)
// 		{
// 			it = listNpc.erase(it);
// 			endit = listNpc.end();
// 		}
// 		else
// 		{
// 			++it;
// 		}
// 	}
	listNpc.erase(std::remove(listNpc.begin(), listNpc.end(), pNpc), listNpc.end());
}

#endif // SYSTEM_TREASURE_MAP
//
