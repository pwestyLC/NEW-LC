#include "stdhdrs.h"
#include "CmdMsg.h"
#include "Server.h"
#include "HunterCode.h"
#include "Log.h"

#ifdef LOG_DB_10292021
void SaveHackUser(const char* idname, int charIndex)
{
	int userCode;
	CLCString nick(20 + 1);

	CDBCmd dbauth;
	dbauth.Init(&gserver->m_dbauth);
	std::string selectAcc = boost::str(boost::format("SELECT user_code FROM bg_user c WHERE user_id like '%s'") % idname);
	dbauth.SetQuery(selectAcc.c_str());
	if (dbauth.Open()) {
		dbauth.MoveFirst();
		dbauth.GetRec("user_code", userCode);
	}

	if (charIndex) {
		CDBCmd dbcmd;
		dbcmd.Init(&gserver->m_dbchar);
		std::string selectCharacter = boost::str(boost::format("SELECT a_nick FROM t_characters WHERE a_index = %d") % charIndex);
		dbcmd.SetQuery(selectCharacter.c_str());
		if (dbcmd.Open()) {
			dbcmd.MoveFirst();
			dbcmd.GetRec("a_nick", nick, true);
		}

		LOG_INFO("SAVE HACK %d %s %d %s", userCode, idname, charIndex, nick.getBuffer());

		CDBCmd DB_cmd1;
		DB_cmd1.Init(&gserver->m_dbchar);
		std::string sqlhack = boost::str(boost::format("insert into t_hack_user (a_user_idx, a_user_id, a_char_idx, a_char_name, a_time, a_hacktype) values (%d, '%s', %d, '%s', NOW(), '%s')")
			% userCode % idname % charIndex % (const char*)nick % "Modify Null");
		DB_cmd1.SetQuery(sqlhack.c_str());
		DB_cmd1.Update();
	}
}
#endif
#ifdef CAPTURE_THE_FLAG_10282021
void ProcFlagCarrier(CPC* df, CCharacter* of)
{
	if (df == NULL || of == NULL)	
		return;
	const char* strOFType = "UNKNOWN";
	const char* strOFName = "UNKNOWN";
	int strOFIndex = 0;

	CPC* opc = NULL;
	CNPC* onpc = NULL;
	CPet* opet = NULL;
	CElemental* oelemental = NULL;
	CAPet* oapet = NULL;

	switch (of->m_type)
	{
	case MSG_CHAR_PC:
		opc = TO_PC(of);
		strOFType = "PC";
		strOFName = opc->GetName();
		strOFIndex = opc->m_index;
		break;

	case MSG_CHAR_NPC:
		onpc = TO_NPC(of);
		strOFType = "NPC";
		strOFName = onpc->m_name;
		strOFIndex = onpc->m_idNum;
		break;

	case MSG_CHAR_PET:
		opet = TO_PET(of);
		opc = opet->GetOwner();
		if (opc == NULL)
			return;
		strOFType = "PET";
		strOFName = opc->GetName();
		strOFIndex = opc->m_index;
		break;

	case MSG_CHAR_ELEMENTAL:
		oelemental = TO_ELEMENTAL(of);
		opc = oelemental->GetOwner();
		if (opc == NULL)
			return;
		strOFType = "ELEMENTAL";
		strOFName = opc->GetName();
		strOFIndex = opc->m_index;
		break;
	case MSG_CHAR_APET:
		oapet = TO_APET(of);
		opc = oapet->GetOwner();
		if (opc == NULL)
			return;
		strOFType = "APET";
		strOFName = opc->GetName();
		strOFIndex = opc->m_index;
		break;

	default:
		return;
	}


	if (DEAD(df)) 
	{
		if (df->m_inventory.FindByDBIndex(12272) != NULL)
		{

			CItem* pitem11272 = NULL;
			pitem11272 = df->m_inventory.FindByDBIndex(12272, 0, 0);

			item_search_t vec_pvpflagitem;

			int sc = df->m_inventory.searchItemByCondition(12272, 0, 0, vec_pvpflagitem);
			// make sure the user doesnt have more then he should of the item
			if (sc == 0 || sc < 1)
				return;
			//delete item from inventory user died
			df->m_inventory.deleteItem(vec_pvpflagitem, 1);
			df->m_bHasFlagItem = false;

			int npcindex = 1704;
			//make sure the npc isn't null (crash)
			CNPC* npc = gserver->m_npcProtoList.Create(npcindex, NULL);
			if (!npc)
				return;
			//grab the information for the mob from the dead player
			GET_X(npc) = GET_X(df);
			GET_Z(npc) = GET_Z(df);
			GET_YLAYER(npc) = GET_YLAYER(df);
			GET_R(npc) = GetRandom(0, (int)(PI_2 * 10000)) / 10000;

			if (df->m_pArea->GetAttr(GET_YLAYER(npc), GET_X(npc), GET_Z(npc)) & MATT_WALKABLE) {}


			npc->m_regenX = GET_X(npc);
			npc->m_regenY = GET_YLAYER(npc);
			npc->m_regenZ = GET_Z(npc);

			int cx, cz;
			df->m_pArea->AddNPC(npc);
			df->m_pArea->PointToCellNum(GET_X(npc), GET_Z(npc), &cx, &cz);
			df->m_pArea->CharToCell(npc, GET_YLAYER(npc), cx, cz);

			{
				CNetMsg::SP rmsg(new CNetMsg);
				AppearMsg(rmsg, npc, true);
				df->m_pArea->SendToCell(rmsg, GET_YLAYER(npc), cx, cz);
			}

			{
				//annouce message to all with flag position
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsgFlagDead(rmsg, df->m_desc->m_pChar->m_nick, df->m_pos.m_x, df->m_pos.m_z);
				PCManager::instance()->sendToAll(rmsg);
			}

		}
	}




}

bool HasFlagCarrierItem(CPC* pc)
{
	return true;
}
#endif
