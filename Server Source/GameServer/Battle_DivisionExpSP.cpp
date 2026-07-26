#include "stdhdrs.h"

#include "Server.h"
#include "CmdMsg.h"
#include "Exp.h"
#include "Log.h"
#include "Battle.h"
#include "Party.h"

LONGLONG GetTeachSPBonus(CPC* ch, LONGLONG sp);

// ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½
typedef struct __tagExpList
{
	CPC* pc;		// ï¿½ï¿½ï¿½Þ¹ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½
	struct __tagExpList* next;	// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
} EXP_LIST;

// ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½Ð³ï¿½Æ¼ ï¿½ï¿½ï¿½Ìºï¿½ [%] : 1ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ 6ï¿½ï¿½ï¿½ï¿½
static const int levelPenalty[6] = { 95, 90, 75, 60, 45, 10 };

// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½
void DivisionExpSPParty(CParty* party, CNPC* npc, CPC* pPreferencePC, LONGLONG nTotalDamage);

// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½
void DivisionExpSPExped(CExpedition* Exped, CNPC* npc, CPC* pPreferencePC, LONGLONG nTotalDamage);

// ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
int GetExpLevelPenalty(int nLevelDiff);
// SP ï¿½ï¿½ï¿½ï¿½ ï¿½Ð³ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
int GetSPLevelPenalty(int nLevelDiff);

int GetExpSPLevelPenaltyNew(int nLevelDiff);

// npc ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½
// ï¿½Û½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½Ìµï¿½ ï¿½ß»ï¿½ï¿½Ã¿ï¿½ï¿½ï¿½ trueï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
bool DivisionExpSP(CNPC* npc, CPC* pPreferencePC, LONGLONG nTotalDamage)
{
#ifdef PREMIUM_CHAR
	LONGLONG		nExpNPC;
	LONGLONG		nSPNPC;
	if (pPreferencePC != NULL)
	{
		nExpNPC = npc->m_proto->getExpForPremiumChar(pPreferencePC->m_premiumChar.getPremiumType());			// ï¿½ï¿½ï¿½Þµï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡
		nSPNPC = npc->m_proto->getSkillPointForPremiumChar(pPreferencePC->m_premiumChar.getPremiumType());	// ï¿½ï¿½ï¿½Þµï¿½ SP
	}
	else
	{
		nExpNPC = npc->m_proto->getExp();			// ï¿½ï¿½ï¿½Þµï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡
		nSPNPC = npc->m_proto->getSkillPoint();	// ï¿½ï¿½ï¿½Þµï¿½ SP
	}
#else
	LONGLONG		nExpNPC = npc->m_proto->getExp();			// ï¿½ï¿½ï¿½Þµï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡
	LONGLONG		nSPNPC = npc->m_proto->getSkillPoint();	// ï¿½ï¿½ï¿½Þµï¿½ SP
#endif

#ifdef GRIND_EXP_LEVEL
	if (pPreferencePC != NULL) {
		if (pPreferencePC->m_level + gserver->m_serverConfig.min_exp_level < npc->m_level) {
			nExpNPC -= nExpNPC * 0.6;
			if (nExpNPC < 0) nExpNPC = 0;
		}
	}
#endif

	EXP_LIST* expList = NULL;							// ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®
	EXP_LIST* expNode = NULL;							// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½
	CAttackChar* pAttackChar = NULL;						// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	CAttackChar* pAttackCharNext = npc->m_attackList;	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	CPC* pExpPC = NULL;							// ï¿½ï¿½ï¿½Þ¹ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½

	if (nTotalDamage < 1)
		return false;

	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ PCï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	while ((pAttackChar = pAttackCharNext))
	{
		pAttackCharNext = pAttackCharNext->m_next;

		if (!pAttackChar->ch)
			continue;

		// ï¿½ï¿½Ã³ï¿½ï¿½ ï¿½Ö¾ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		if (!CheckInNearCellExt(npc, pAttackChar->ch))
			continue;

		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö¾ï¿½ï¿½ ï¿½ï¿½
		if (pAttackChar->m_damage < 1)
			continue;

		// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ PCï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		switch (pAttackChar->ch->m_type)
		{
		case MSG_CHAR_PC:
			pExpPC = TO_PC(pAttackChar->ch);
			break;
		case MSG_CHAR_PET:
			pExpPC = TO_PC(TO_PET(pAttackChar->ch)->GetOwner());
			break;
		case MSG_CHAR_ELEMENTAL:
			pExpPC = TO_PC(TO_ELEMENTAL(pAttackChar->ch)->GetOwner());
			break;
		case MSG_CHAR_APET:
			pExpPC = TO_PC(TO_APET(pAttackChar->ch)->GetOwner());
			break;
		case MSG_CHAR_NPC:
			pExpPC = TO_PC(TO_NPC(pAttackChar->ch)->GetOwner());
			break;
		default:
			pExpPC = NULL;
			break;
		}

		// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö¾ï¿½ï¿½ ï¿½ï¿½
		if (pExpPC == NULL)
			continue;

		// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : ï¿½ï¿½/ï¿½ï¿½È¯ï¿½ï¿½ï¿½î¿¡ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ PCï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		if (pExpPC->m_nExpDamage + pAttackChar->m_damage > 1)
			pExpPC->m_nExpDamage += pAttackChar->m_damage;

		// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ß°ï¿½
		expNode = new EXP_LIST;
		expNode->pc = pExpPC;
		expNode->next = expList;
		expList = expNode;
	}
	// -- ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½Û¼ï¿½ ï¿½ï¿½

	// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½é¼­ ï¿½Ø´ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½
	expNode = expList;
	while (expNode)
	{
		// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ë»ï¿½
		if (expNode->pc->m_nExpDamage > 0)
		{
			// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½Î¿ï¿½ ï¿½ï¿½ï¿½ï¿½ Ã³ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
			if (expNode->pc->IsParty())
			{
				// ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ Ã³ï¿½ï¿½ : expNode ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½å¸¸ Ã³ï¿½ï¿½
				DivisionExpSPParty(expNode->pc->m_party, npc, pPreferencePC, nTotalDamage);
			}
			else if (expNode->pc->IsExped())
			{
				DivisionExpSPExped(expNode->pc->m_Exped, npc, pPreferencePC, nTotalDamage);
			}

			else
			{
				// ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½Æ´Ï¸ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Â°ï¿½ ï¿½ï¿½ï¿½ï¿½

				// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
				int nLevelDiff = expNode->pc->m_level - npc->m_level;

				// ï¿½ï¿½ï¿½ï¿½Ä¡/SP ï¿½Ð³ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½
				LONGLONG nExpPenalty = GetExpLevelPenalty(nLevelDiff);
				LONGLONG nSPPenalty = GetSPLevelPenalty(nLevelDiff);

				// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½ : (NPCï¿½ï¿½ * ï¿½Ð³ï¿½Æ¼ * ï¿½ï¿½ï¿½ï¿½ï¿½) / (100 * ï¿½ï¿½Ã¼ ï¿½ï¿½ï¿½ï¿½ï¿½)
				// Divide early to prevent 64-bit overflow: (A*B/100) * (C/TotalDmg) maintains precision while avoiding overflow
				LONGLONG nGiveExp = ((nExpNPC * nExpPenalty) / 100LL) * ((LONGLONG)expNode->pc->m_nExpDamage / nTotalDamage);
				LONGLONG nGiveSP = ((nSPNPC * nSPPenalty) / 100LL) * ((LONGLONG)expNode->pc->m_nExpDamage / nTotalDamage);

				// DEBUG LOG FOR EXPERIENCE CALCULATION
				/* {
					GAMELOG << init("EXP_DEBUG", expNode->pc)
						<< "PC_Level:" << delim << expNode->pc->m_level << delim
						<< "NPC_Level:" << delim << npc->m_level << delim
						<< "LevelDiff:" << delim << nLevelDiff << delim
						<< "ExpPenalty%:" << delim << nExpPenalty << delim
						<< "NPC_BaseExp:" << delim << nExpNPC << delim
						<< "PlayerDamage:" << delim << expNode->pc->m_nExpDamage << delim
						<< "TotalDamage:" << delim << nTotalDamage << delim
						<< "Calc_Step1(NPC*Penalty):" << delim << (nExpNPC * nExpPenalty) << delim
						<< "Calc_Step2(*PlayerDamage):" << delim << (nExpNPC * nExpPenalty * (LONGLONG)expNode->pc->m_nExpDamage) << delim
						<< "Calc_Step3(/(100*TotalDmg)):" << delim << nGiveExp << delim
						<< "FINAL_EXP_GIVEN:" << delim << nGiveExp << end;
				}*/

				// ï¿½ï¿½ï¿½ï¿½ +- 10% ï¿½ï¿½ï¿½ï¿½
				nGiveExp = nGiveExp + (nGiveExp * GetRandom(-10, 10) / 100);
				nGiveSP = nGiveSP + (nGiveSP * GetRandom(-10, 10) / 100);

				nGiveSP += GetTeachSPBonus(expNode->pc, nGiveSP);

				// EP = ( NPCï¿½ï¿½ï¿½ï¿½  * ï¿½ï¿½Å¸(1) ) + ( NPCï¿½ï¿½ï¿½ï¿½ * ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ / NPC HP ) / 2
				char lastAttack = 0;
				if (pPreferencePC == expNode->pc)
					lastAttack = 1;
				// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
				int	recalcDamage = (int)expNode->pc->m_nExpDamage;
				if (recalcDamage > npc->m_maxHP)
					recalcDamage = npc->m_maxHP;

#ifdef PREMIUM_CHAR
				LONGLONG nGetEnergy;
				if (pPreferencePC != NULL)
				{
					nGetEnergy = (LONGLONG)npc->m_proto->getSkillPointForPremiumChar(pPreferencePC->m_premiumChar.getPremiumType()) * (LONGLONG)recalcDamage / (LONGLONG)npc->m_maxHP;
				}
				else
				{
					nGetEnergy = (LONGLONG)npc->m_proto->getSkillPoint() * (LONGLONG)recalcDamage / (LONGLONG)npc->m_maxHP;
				}
#else
				LONGLONG nGetEnergy = (LONGLONG)npc->m_proto->getSkillPoint() * (LONGLONG)recalcDamage / (LONGLONG)npc->m_maxHP;
#endif

				int ep = (npc->m_proto->m_level * lastAttack) + ((int)nGetEnergy) / 2;

				if (expNode->pc->m_level <= 160)
					ep *= 4;

				if (ABS(npc->m_level - expNode->pc->m_level) < gserver->m_serverConfig.min_ep_level)
				{
					expNode->pc->AddEP(ep);
				}

				expNode->pc->CalcStatus(true);

				int GuildExp = 0;
				if (expNode->pc->m_guildInfo && expNode->pc->m_guildInfo->guild())
				{
					int guildindex = expNode->pc->m_guildInfo->guild()->index();
					CGuild* guild = gserver->m_guildlist.findguild(guildindex);

					if (expNode->pc->m_guildInfo->GetcontributeExp() != 0)
					{
						GuildExp = nGiveExp * expNode->pc->m_guildInfo->GetcontributeExp() / 100;
						expNode->pc->m_GuildExp += GuildExp;
						nGiveExp = nGiveExp - GuildExp;  // ï¿½ï¿½ï¿½ ï¿½â¿©ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½È¯
						LONGLONG GP = 0;
						if (expNode->pc->m_GuildExp >= 10000)
						{
							GP = expNode->pc->m_GuildExp / 10000;
							expNode->pc->m_GuildExp = expNode->pc->m_GuildExp % 10000;
							guild->AddGuildPoint(GP);
							expNode->pc->m_guildInfo->AddCumulatePoint(GP);

							{
								CNetMsg::SP rmsg(new CNetMsg);
								HelperNewGuildPointUpdate(rmsg, expNode->pc->m_index, guild->index(), GP);
								SEND_Q(rmsg, gserver->m_helper);
							}

							{
								CNetMsg::SP rmsg(new CNetMsg);
								HelperSaveGuildMemberPointMsg(rmsg, guild->index(), expNode->pc->m_index, GP);
								SEND_Q(rmsg, gserver->m_helper);
							}
						}
					}
				}

				// ï¿½ï¿½ï¿½ï¿½
				if (nGiveExp < 1)	nGiveExp = 1;
				if (nGiveSP < 1)	nGiveSP = 1;

				// SPï¿½ï¿½ MAX_SKILLPOINTï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
				if (nGiveSP > MAX_SKILLPOINT) nGiveSP = MAX_SKILLPOINT;

				// 9ï¿½ï¿½ ï¿½Ìºï¿½Æ® : ï¿½ï¿½ï¿½ï¿½Ú°ï¿½ ï¿½ì¼±ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½
				bool bArtifact = false;
				if (expNode->pc == pPreferencePC)
				{
					// ï¿½ï¿½ï¿½ï¿½Ä¡ 4ï¿½ï¿½
					if (expNode->pc->m_assist.m_avAddition.hcSepExp)
					{
						expNode->pc->m_assist.CureByItemIndex(882);	// ï¿½ï¿½ï¿½ï¿½Ä¡
						nGiveExp = nGiveExp * 4;
						CNetMsg::SP rmsg(new CNetMsg);
						EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_EXP);
						SEND_Q(rmsg, expNode->pc->m_desc);

						//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Êµï¿½ï¿½ï¿½ Ã³ï¿½ï¿½
						bArtifact = true;
					}
					// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ 4ï¿½ï¿½
					else if (expNode->pc->m_assist.m_avAddition.hcSepExp_Cash)
					{
						expNode->pc->m_assist.CureByItemIndex(6094);	// ï¿½ï¿½ï¿½ï¿½Ä¡
						nGiveExp = nGiveExp * 4;
						CNetMsg::SP rmsg(new CNetMsg);
						EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_EXP);
						SEND_Q(rmsg, expNode->pc->m_desc);

						//ìœ ë¬¼ ì•„ì´í…œ ì ìš©í•˜ì§€ ì•Šë„ë¡ ì²˜ë¦¬
						bArtifact = true;
					}

					else if (expNode->pc->m_assist.m_avAddition.hcSepExp_Prem)
					{
						expNode->pc->m_assist.CureByItemIndex(12057);	// ï¿½ï¿½ï¿½ï¿½Ä¡
						nGiveExp = nGiveExp * 6;
						CNetMsg::SP rmsg(new CNetMsg);
						EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_EXP);
						SEND_Q(rmsg, expNode->pc->m_desc);

						//ìœ ë¬¼ ì•„ì´í…œ ì ìš©í•˜ì§€ ì•Šë„ë¡ ì²˜ë¦¬
						bArtifact = true;
					}

					else if (expNode->pc->m_assist.m_avAddition.hcSepExp)
					{
						expNode->pc->m_assist.CureByItemIndex(20590);	// ï¿½ï¿½ï¿½ï¿½Ä¡
						nGiveExp = nGiveExp * 4;
						CNetMsg::SP rmsg(new CNetMsg);
						EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_EXP);
						SEND_Q(rmsg, expNode->pc->m_desc);

						//ìœ ë¬¼ ì•„ì´í…œ ì ìš©í•˜ì§€ ì•Šë„ë¡ ì²˜ë¦¬
						bArtifact = true;
					}

					else if (expNode->pc->m_assist.m_avAddition.hcRandomExpUp > 0 && GetRandom(0, 100) <= expNode->pc->m_assist.m_avAddition.hcRandomExpUp)
					{
						nGiveExp = nGiveExp * 4;

						CNetMsg::SP rmsg(new CNetMsg);
						EffectEtcMsg(rmsg, expNode->pc, MSG_EFFECT_ETC_RANDOM_EXP);
						expNode->pc->m_pArea->SendToCell(rmsg, expNode->pc, true);

						bArtifact = true;
					}

					// 9ï¿½ï¿½ ï¿½Ìºï¿½Æ® : SP 4ï¿½ï¿½
					if (expNode->pc->m_assist.m_avAddition.hcSepSP)
					{
						expNode->pc->m_assist.CureByItemIndex(883);	// ï¿½ï¿½ï¿½Ãµï¿½
						nGiveSP = nGiveSP * 4;
						CNetMsg::SP rmsg(new CNetMsg);
						EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_SP);
						SEND_Q(rmsg, expNode->pc->m_desc);
					}
					// ï¿½ï¿½ï¿½ï¿½ SP 4ï¿½ï¿½
					else if (expNode->pc->m_assist.m_avAddition.hcSepSP_Cash)
					{
						expNode->pc->m_assist.CureByItemIndex(6095);	// ï¿½ï¿½ï¿½Ãµï¿½
						nGiveSP = nGiveSP * 4;
						CNetMsg::SP rmsg(new CNetMsg);
						EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_SP);
						SEND_Q(rmsg, expNode->pc->m_desc);
					}

					else if (expNode->pc->m_assist.m_avAddition.hcSepSP)
					{
						expNode->pc->m_assist.CureByItemIndex(20591);	// ï¿½ï¿½ï¿½Ãµï¿½
						nGiveSP = nGiveSP * 4;
						CNetMsg::SP rmsg(new CNetMsg);
						EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_SP);
						SEND_Q(rmsg, expNode->pc->m_desc);
					}

					else if (expNode->pc->m_assist.m_avAddition.hcRandomSpUp > 0 && GetRandom(0, 100) <= expNode->pc->m_assist.m_avAddition.hcRandomSpUp)
					{
						nGiveSP = nGiveSP * 4;

						CNetMsg::SP rmsg(new CNetMsg);
						EffectEtcMsg(rmsg, expNode->pc, MSG_EFFECT_ETC_RANDOM_SP);
						expNode->pc->m_pArea->SendToCell(rmsg, expNode->pc, true);
					}
				}

#ifdef NEW_ACCERY_ADD
				if (expNode->pc->m_AddProb)
				{
					nGiveExp = nGiveExp + (nGiveExp * expNode->pc->m_AddProb / 100);
					nGiveSP = nGiveSP + (nGiveSP * expNode->pc->m_AddProb / 100);
				}
#endif //NEW_ACCERY_ADD

				CAPet* apet = expNode->pc->GetAPet();
				if (apet && apet->m_bSummon == true)
				{
					LONGLONG petexp = (npc->m_level) / 5 * (npc->m_proto->CheckFlag(NPC_MBOSS | NPC_BOSS) ? 4 : 1);
					apet->AddExpSP(petexp, 0);

					//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ì°ï¿½, ï¿½ë¸®ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ÏµÇ¾ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½
					if (expNode->pc->m_petStashManager.getProxyPetItemvIndex() > -1)
					{
						int petVIndex = expNode->pc->m_petStashManager.getProxyPetItemvIndex();
						int petPlus = expNode->pc->m_petStashManager.getProxyPetItemPlus();
						if (expNode->pc->GetAPet(petPlus))
						{
							CAPet* proxyPet = expNode->pc->m_petStashManager.getProxyAPet();
							if (proxyPet != NULL)
							{
								petexp /= 10;
								proxyPet->AddExpSP(petexp, 0);
							}
						}
						else if (expNode->pc->GetPet(petPlus))
						{
							CPet* proxyPet = expNode->pc->m_petStashManager.getProxyPet();
							if (proxyPet != NULL)
							{
								if (proxyPet->m_level < PET_MAX_LEVEL
									&& proxyPet->GetHungryPoint() > 0)
								{
									petexp /= 10;
									proxyPet->m_exp += petexp;
									if (proxyPet->m_exp > proxyPet->GetNeedExp())
									{
										proxyPet->m_level++;
										proxyPet->IncreaseAbilityPoint(1);
										proxyPet->LevelUp();
										proxyPet->m_exp = 0;
									}
								}
							}
						}
						expNode->pc->m_petStashManager.UpdatePetData(petPlus);
					}
				}

				// ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½ : ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ìµï¿½ï¿½Ã¿ï¿½ trueï¿½ï¿½ ï¿½ï¿½È¯ï¿½È´ï¿½
				if (expNode->pc->AddExpSP(nGiveExp, (int)nGiveSP, true, false, false, bArtifact))
				{
					// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½Þ¸ï¿½ ï¿½ï¿½ï¿½ï¿½
					while (expList)
					{
						expNode = expList;
						expList = expList->next;
						expNode->pc->m_nExpDamage = 0;
						delete expNode;
					}
					return true;
				}

				// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ PC ï¿½Ê±ï¿½È­
				expNode->pc->m_nExpDamage = 0;
			} // --- ï¿½ï¿½Æ¼ ï¿½Æ´ï¿½ ï¿½ï¿½ï¿½ Ã³ï¿½ï¿½ ï¿½ï¿½
		} // --- ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ Ã³ï¿½ï¿½ ï¿½ï¿½

		expNode = expNode->next;
	}

	// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½Þ¸ï¿½ ï¿½ï¿½ï¿½ï¿½
	while (expList)
	{
		expNode = expList;
		expList = expList->next;
		expNode->pc->m_nExpDamage = 0;
		delete expNode;
	}

	return false;
}

// ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½é¿¡ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ SP ï¿½Ð¹ï¿½	(ï¿½ï¿½Æ¼, NPC, ï¿½ì¼±ï¿½ï¿½, ï¿½ï¿½Ã¼ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½)
void DivisionExpSPParty(CParty* party, CNPC* npc, CPC* pPreferencePC, LONGLONG nTotalDamage)
{
	// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½Ê½ï¿½ ï¿½ï¿½ï¿½Ìºï¿½ [%] : 1ï¿½Îºï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	static const int countBonus[MAX_PARTY_MEMBER] = { 20, 35, 50, 65, 80, 95, 105, 115 };

	EXP_LIST* expParty = NULL;		// ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®
	EXP_LIST* expPartyNode = NULL;	// ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½ï¿½ï¿½
	EXP_LIST* expNode = NULL;			// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	EXP_LIST* expNodeNext = NULL;		// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½

	LONGLONG			nPartyDamage = 0;		// ï¿½ï¿½Æ¼ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½
	int					nParty = 0;				// ï¿½ï¿½ï¿½ ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½ï¿½
	int					nPartyLevelTotal = 0;	// ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½
	int					nPartyLevelMax = 0;		// ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½Ö´ï¿½ ï¿½ï¿½ï¿½ï¿½
	int					nPartyLevel = 0;		// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	int					nPartyLevelNew = 0;		// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ new
	LONGLONG			nExpParty = 0;			// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½Ä¡
	LONGLONG			nSPParty = 0;			// ï¿½ï¿½Æ¼ SP
	LONGLONG			nExpPenalty;			// ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½Ð³ï¿½Æ¼
	LONGLONG			nSPPenalty;				// SP ï¿½Ð³ï¿½Æ¼
	int					i;						// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	int					nHavePetCount = 0;			// ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½

	if (nTotalDamage < 1)
		return;

	if (party == NULL)
		return;

	if (npc == NULL)
		return;

	// ï¿½ï¿½Æ¼ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ï±ï¿½
	// ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½Ï±ï¿½
	// ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½ï¿½ ï¿½Ø´ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½
	for (i = 0; i < MAX_PARTY_MEMBER; i++)
	{
		CPC* pMember = party->GetNearMember(npc, i);
		if (pMember == NULL)
			continue;
		if (DEAD(pMember))
			continue;
		// ï¿½ï¿½Ã¼ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ß°ï¿½
		nPartyDamage += pMember->m_nExpDamage;
		// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ß°ï¿½
		expPartyNode = new EXP_LIST;
		expPartyNode->pc = pMember;
		expPartyNode->next = expParty;
		expParty = expPartyNode;
		nParty++;
		// ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		nPartyLevelTotal += pMember->m_level;
		// ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½Ö´ï¿½ ï¿½ï¿½ï¿½ï¿½
		if (nPartyLevelMax < pMember->m_level)
			nPartyLevelMax = pMember->m_level;

		// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Ä«ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½
		if (pMember->GetAPet())
			nHavePetCount++;
	}

	// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½Ð¹ï¿½ ï¿½ï¿½ï¿½ï¿½
	// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	// ï¿½ï¿½ï¿½ ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½ 1ï¿½ï¿½ ï¿½Ì»ï¿½
	// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 1 ï¿½Ì»ï¿½
	if (nPartyDamage > 0 && nParty > 0 && nPartyLevelTotal > 0)
	{
		int basic_party_plus_exp;
		int basic_party_plus_sp;

		// bw : 060817 : ï¿½ï¿½Æ¼ ï¿½Ã½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Îºï¿½, ï¿½Î¿ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ê½ï¿½ï¿½ï¿½ ï¿½Ñ¸ï¿½ï¿½Ï¶ï¿½ 0ï¿½Ìµï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		/*
		if( nParty == 1 )
		{
			basic_party_plus_exp = 0;
			basic_party_plus_sp = 0;
		}
		else
		*/
		{
			basic_party_plus_exp = PARTY_PLUS_EXP;
			basic_party_plus_sp = PARTY_PLUS_SP;
		}

		// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		nPartyLevel = (nPartyLevelMax - (nPartyLevelTotal / nParty) > 5) ? (nPartyLevelMax - 5) : (nPartyLevelTotal / nParty);

		nPartyLevelNew = nPartyLevelTotal / nParty;

		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ï±ï¿½
		int nLevelDiff = nPartyLevel - npc->m_level;

		// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½ ï¿½Ð³ï¿½Æ¼ ï¿½ï¿½ï¿½Ï±ï¿½
		nExpPenalty = GetExpLevelPenalty(nLevelDiff);
		nSPPenalty = GetSPLevelPenalty(nLevelDiff);

		// ï¿½ï¿½Æ¼	ï¿½ï¿½ï¿½Ê½ï¿½ ï¿½ï¿½ï¿½Ï±ï¿½
		LONGLONG nExpBonus = 100;
		LONGLONG nSPBonus = 100;

		if (nParty > 1)
		{
			nExpBonus = 100 + basic_party_plus_exp + countBonus[nParty - 1];
			nSPBonus = 100 + basic_party_plus_sp + 6 * (nParty - 1);
		}

		// ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡/SP ï¿½ï¿½ï¿½Ï±ï¿½
#ifdef PREMIUM_CHAR
		LONGLONG nExpNPC;
		if (pPreferencePC != NULL)
		{
			nExpNPC = npc->m_proto->getExpForPremiumChar(pPreferencePC->m_premiumChar.getPremiumType());
		}
		else
		{
			nExpNPC = npc->m_proto->getExp();
		}
#else
		LONGLONG nExpNPC = npc->m_proto->getExp();
#endif

#ifdef GRIND_EXP_LEVEL
		if (pPreferencePC != NULL) {
			if (pPreferencePC->m_level + gserver->m_serverConfig.min_exp_level < npc->m_level) {
				nExpNPC -= nExpNPC * 0.6;
				if (nExpNPC < 0) nExpNPC = 0;
			}
		}
#endif

		//nExpParty		= nExpNPC * nExpBonus * nExpPenalty * nPartyDamage / (100 * 100 * nTotalDamage);
		// Divide early to prevent 64-bit overflow: (A*B/100/100) * (C*D/TotalDmg) maintains precision while avoiding overflow
		nExpParty = (((nExpNPC * nExpBonus) / 100LL) * nExpPenalty / 100LL) * (nPartyDamage / nTotalDamage);
		if (nExpNPC >= 0 && nExpParty <= 0)
			nExpParty = (nExpNPC * nExpBonus / 100 * nExpPenalty / 100 * nPartyDamage) / nTotalDamage;

		nExpParty = nExpParty * GetExpSPLevelPenaltyNew(nLevelDiff) / 100;

#ifdef PREMIUM_CHAR
		int tSkillPoint;
		if (pPreferencePC != NULL)
		{
			tSkillPoint = npc->m_proto->getSkillPointForPremiumChar(pPreferencePC->m_premiumChar.getPremiumType());
		}
		else
		{
			tSkillPoint = npc->m_proto->getSkillPoint();
		}
#else
		int tSkillPoint = npc->m_proto->getSkillPoint();
#endif
		nSPParty = tSkillPoint * nSPBonus * nSPPenalty * nPartyDamage / (100 * 100 * nTotalDamage);
		if (tSkillPoint > 0 && nSPParty <= 0)
			nSPParty = tSkillPoint * nSPBonus / 100 * nSPPenalty / 100 * nPartyDamage / nTotalDamage;

		nSPParty = nSPParty * GetExpSPLevelPenaltyNew(nLevelDiff) / 100;

		// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		nExpParty = nExpParty + (nExpParty * GetRandom(-10, 10) / 100);
		nSPParty = nSPParty + (nSPParty * GetRandom(-10, 10) / 100);
	}
	else
	{
		// ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½Ê±ï¿½È­
		while (expParty)
		{
			expPartyNode = expParty;
			expParty = expParty->next;
			expPartyNode->pc->m_nExpDamage = 0;
			delete expPartyNode;
		}
		return;
	}

	// ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡/SP ï¿½ï¿½ï¿½ï¿½
	LONGLONG nGiveExp = 0;		// ï¿½ï¿½ï¿½Þµï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡
	LONGLONG nGiveSP = 0;		// ï¿½ï¿½ï¿½Þµï¿½ SP
	LONGLONG nExpPartyForGive = 0;			// ï¿½ï¿½ï¿½Þ¿ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½Ä¡ : nExpParty or nExpParty_CA
	expNodeNext = expParty;
	while ((expNode = expNodeNext))
	{
		expNodeNext = expNodeNext->next;

		nExpPartyForGive = nExpParty;

		// ï¿½ï¿½Æ¼ Å¸ï¿½Ô¿ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡
		switch (party->GetPartyType(MSG_DIVITYPE_EXP))
		{
		case MSG_PARTY_TYPE_RANDOM:			// ï¿½Õµï¿½
		case MSG_PARTY_TYPE_FIRSTGET:		// ï¿½Ô¼ï¿½ ï¿½ì¼±
			//   ( (ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½Ä¡ 75%) * (ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½) / (ï¿½ï¿½Æ¼ï¿½Ñ·ï¿½ï¿½ï¿½) )
			// + ( (ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½Ä¡ 25%) / (ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½) )
			nGiveExp = (nExpPartyForGive * 75 * expNode->pc->m_level / nPartyLevelTotal)
				+ (nExpPartyForGive * 25 / nParty);
			// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : ï¿½Ð¹ï¿½%
			nGiveExp /= 100;
			if (nExpPartyForGive > 0 && nGiveExp <= 0)
			{
				nGiveExp = (nExpPartyForGive * 75 / 100 * expNode->pc->m_level / nPartyLevelTotal)
					+ (nExpPartyForGive * 25 / 100 / nParty);
			}
			break;

		default:
		case MSG_PARTY_TYPE_BATTLE:			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			//   ( (ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½Ä¡ 70%) * (ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½) / (ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½ï¿½) )
			// + ( (ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½Ä¡ 30%) * (ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½) / (ï¿½ï¿½Æ¼ ï¿½ï¿½Ã¼ï¿½ï¿½ï¿½ï¿½) )
			nGiveExp = (nExpPartyForGive * 70 * expNode->pc->m_nExpDamage / nPartyDamage)
				+ (nExpPartyForGive * 30 * expNode->pc->m_level / nPartyLevelTotal);
			// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : ï¿½Ð¹ï¿½%
			nGiveExp /= 100;
			if (nExpPartyForGive > 0 && nGiveExp <= 0)
			{
				nGiveExp = (nExpPartyForGive * 70 / 100 * expNode->pc->m_nExpDamage / nPartyDamage)
					+ (nExpPartyForGive * 30 / 100 * expNode->pc->m_level / nPartyLevelTotal);
			}
			break;
		}

		// ï¿½ï¿½Æ¼ Å¸ï¿½Ô¿ï¿½ ï¿½ï¿½ï¿½ï¿½ SP
		switch (party->GetPartyType(MSG_DIVITYPE_SP))
		{
		case MSG_PARTY_TYPE_RANDOM:			// ï¿½Õµï¿½
		case MSG_PARTY_TYPE_BATTLE:			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			// (ï¿½ï¿½Æ¼ SP) / (ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½)
			nGiveSP = nSPParty / nParty;
			break;

		default:
		case MSG_PARTY_TYPE_FIRSTGET:		// ï¿½Ô¼ï¿½ï¿½ì¼±
			// Ä³ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ð³ï¿½Æ¼
			nSPPenalty = GetSPLevelPenalty(expNode->pc->m_level - npc->m_level);

			//   ( (ï¿½ï¿½Æ¼SP 20%) / (ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½) )
			// + ( (ï¿½ï¿½Æ¼SP 60%) * (ï¿½ï¿½ï¿½ï¿½Ú´ï¿½ï¿½ï¿½ï¿½) / (ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½ï¿½) )
			// + ( (ï¿½ï¿½Æ¼SP 20%) * (ï¿½ï¿½ï¿½ï¿½Ú·ï¿½ï¿½ï¿½) / (ï¿½ï¿½Æ¼ï¿½Ñ·ï¿½ï¿½ï¿½) )
			nGiveSP = (nSPParty * 20 * nSPPenalty / nParty)
				+ (nSPParty * 60 * nSPPenalty * expNode->pc->m_nExpDamage / nPartyDamage)
				+ (nSPParty * 20 * nSPPenalty * expNode->pc->m_level / nPartyLevelTotal);
			// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : ï¿½Ð¹ï¿½%, ï¿½Ð³ï¿½Æ¼
			nGiveSP /= 10000;
			if (nSPParty > 0 && nGiveSP <= 0)
			{
				nGiveSP = (nSPParty * 20 / 100 * nSPPenalty / 100 / nParty)
					+ (nSPParty * 60 / 100 * nSPPenalty / 100 * expNode->pc->m_nExpDamage / nPartyDamage)
					+ (nSPParty * 20 / 100 * nSPPenalty / 100 * expNode->pc->m_level / nPartyLevelTotal);
			}
			break;
		}

		nGiveSP += GetTeachSPBonus(expNode->pc, nGiveSP);

		// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ð³ï¿½Æ¼ : ï¿½Ö°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 15ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 5%ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		if (nPartyLevelMax - 15 > expNode->pc->m_level)
		{
			nGiveExp /= 20;
			nGiveSP /= 20;
		}

		// ï¿½ï¿½ï¿½ï¿½
		if (nGiveExp < 1)	nGiveExp = 1;
		if (nGiveSP < 1)	nGiveSP = 1;

		// SPï¿½ï¿½ MAX_SKILLPOINTï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		if (nGiveSP > MAX_SKILLPOINT) nGiveSP = MAX_SKILLPOINT;

		// 9ï¿½ï¿½ ï¿½Ìºï¿½Æ® : ï¿½ï¿½ï¿½ï¿½Ú°ï¿½ ï¿½ì¼±ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½
		bool bArtifact = false;

		if (expNode->pc == pPreferencePC)
		{
			// ï¿½ï¿½ï¿½ï¿½Ä¡ 4ï¿½ï¿½
			if (expNode->pc->m_assist.m_avAddition.hcSepExp)
			{
				expNode->pc->m_assist.CureByItemIndex(882);	// ê²½í—˜ì¹˜
				nGiveExp = nGiveExp * 4;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_EXP);
				SEND_Q(rmsg, expNode->pc->m_desc);

				bArtifact = true;
			}
			else if (expNode->pc->m_assist.m_avAddition.hcSepExp_Cash)	// ï¿½ï¿½ï¿½ï¿½Ä¡ 4ï¿½ï¿½
			{
				expNode->pc->m_assist.CureByItemIndex(6094);	// ï¿½ï¿½ï¿½ï¿½Ä¡
				nGiveExp = nGiveExp * 4;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_EXP);
				SEND_Q(rmsg, expNode->pc->m_desc);

				bArtifact = true;
			}

			else if (expNode->pc->m_assist.m_avAddition.hcSepExp_Prem)	// ï¿½ï¿½ï¿½ï¿½Ä¡ 4ï¿½ï¿½
			{
				expNode->pc->m_assist.CureByItemIndex(12057);	// ï¿½ï¿½ï¿½ï¿½Ä¡
				nGiveExp = nGiveExp * 6;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_EXP);
				SEND_Q(rmsg, expNode->pc->m_desc);

				bArtifact = true;
			}

			else if (expNode->pc->m_assist.m_avAddition.hcSepExp)	// ï¿½ï¿½ï¿½ï¿½Ä¡ 4ï¿½ï¿½
			{
				expNode->pc->m_assist.CureByItemIndex(20590);	// ï¿½ï¿½ï¿½ï¿½Ä¡
				nGiveExp = nGiveExp * 4;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_EXP);
				SEND_Q(rmsg, expNode->pc->m_desc);

				bArtifact = true;
			}

			else if (expNode->pc->m_assist.m_avAddition.hcRandomExpUp > 0 && GetRandom(0, 100) <= expNode->pc->m_assist.m_avAddition.hcRandomExpUp)
			{
				nGiveExp = nGiveExp * 4;

				CNetMsg::SP rmsg(new CNetMsg);
				EffectEtcMsg(rmsg, expNode->pc, MSG_EFFECT_ETC_RANDOM_EXP);
				expNode->pc->m_pArea->SendToCell(rmsg, expNode->pc, true);

				bArtifact = true;
			}

			// 9ï¿½ï¿½ ï¿½Ìºï¿½Æ® : SP 4ï¿½ï¿½
			if (expNode->pc->m_assist.m_avAddition.hcSepSP)
			{
				expNode->pc->m_assist.CureByItemIndex(883);	// ï¿½ï¿½ï¿½Ãµï¿½
				nGiveSP = nGiveSP * 4;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_SP);
				SEND_Q(rmsg, expNode->pc->m_desc);
			}
			// ï¿½ï¿½ï¿½ï¿½ SP 4ï¿½ï¿½
			else if (expNode->pc->m_assist.m_avAddition.hcSepSP_Cash)
			{
				expNode->pc->m_assist.CureByItemIndex(6095);	// ï¿½ï¿½ï¿½Ãµï¿½
				nGiveSP = nGiveSP * 4;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_SP);
				SEND_Q(rmsg, expNode->pc->m_desc);
			}

			else if (expNode->pc->m_assist.m_avAddition.hcSepSP)
			{
				expNode->pc->m_assist.CureByItemIndex(20591);	// ï¿½ï¿½ï¿½Ãµï¿½
				nGiveSP = nGiveSP * 4;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_SP);
				SEND_Q(rmsg, expNode->pc->m_desc);
			}



			else if (expNode->pc->m_assist.m_avAddition.hcRandomSpUp > 0 && GetRandom(0, 100) <= expNode->pc->m_assist.m_avAddition.hcRandomSpUp)
			{
				nGiveSP = nGiveSP * 4;

				CNetMsg::SP rmsg(new CNetMsg);
				EffectEtcMsg(rmsg, expNode->pc, MSG_EFFECT_ETC_RANDOM_SP);
				expNode->pc->m_pArea->SendToCell(rmsg, expNode->pc, true);
			}
		}

#ifdef	NEW_ACCERY_ADD
		if (expNode->pc->m_AddProb)
		{
			nGiveExp = nGiveExp + (nGiveExp * expNode->pc->m_AddProb / 100);
			nGiveSP = nGiveSP + (nGiveSP * expNode->pc->m_AddProb / 100);
		}
#endif // NEW_ACCERY_ADD

		int GuildExp = 0;
		if (expNode->pc->m_guildInfo && expNode->pc->m_guildInfo->guild())
		{
			CGuild* guild = expNode->pc->m_guildInfo->guild();
			if (expNode->pc->m_guildInfo->GetcontributeExp() != 0)
			{
				GuildExp = nGiveExp * expNode->pc->m_guildInfo->GetcontributeExp() / 100;
				expNode->pc->m_GuildExp += GuildExp;
				nGiveExp = nGiveExp - GuildExp;
				LONGLONG GP = 0;
				if (expNode->pc->m_GuildExp >= 10000)
				{
					GP = expNode->pc->m_GuildExp / 10000;
					expNode->pc->m_GuildExp = expNode->pc->m_GuildExp % 10000;
					guild->AddGuildPoint(GP);
					expNode->pc->m_guildInfo->AddCumulatePoint(GP);

					{
						CNetMsg::SP rmsg(new CNetMsg);
						HelperNewGuildPointUpdate(rmsg, expNode->pc->m_index, guild->index(), GP);
						SEND_Q(rmsg, gserver->m_helper);
					}

					{
						CNetMsg::SP rmsg(new CNetMsg);
						HelperSaveGuildMemberPointMsg(rmsg, guild->index(), expNode->pc->m_index, GP);
						SEND_Q(rmsg, gserver->m_helper);
					}
				}

			}
		}

		// EP = ( NPCï¿½ï¿½ï¿½ï¿½  * ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½ ) + ( NPCï¿½ï¿½ï¿½ï¿½ * ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ / NPC HP ) / 2
		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½

		int	recalcDamage = (int)expNode->pc->m_nExpDamage;
		if (recalcDamage > npc->m_maxHP)
			recalcDamage = npc->m_maxHP;

#ifdef PREMIUM_CHAR
		LONGLONG nGetEnergy;
		if (pPreferencePC != NULL)
		{
			nGetEnergy = (LONGLONG)npc->m_proto->getSkillPointForPremiumChar(pPreferencePC->m_premiumChar.getPremiumType()) * (LONGLONG)recalcDamage / (LONGLONG)npc->m_maxHP;
		}
		else
		{
			nGetEnergy = (LONGLONG)npc->m_proto->getSkillPoint() * (LONGLONG)recalcDamage / (LONGLONG)npc->m_maxHP;
		}
#else
		LONGLONG nGetEnergy = (LONGLONG)npc->m_proto->getSkillPoint() * (LONGLONG)recalcDamage / (LONGLONG)npc->m_maxHP;
#endif

		int ep = (npc->m_proto->m_level * nParty) + ((int)nGetEnergy) / 2;

		if (expNode->pc->m_level <= 160)
			ep *= 4;

		if (ABS(npc->m_level - expNode->pc->m_level) < gserver->m_serverConfig.min_ep_level)
		{
			expNode->pc->AddEP(ep);
		}
		expNode->pc->CalcStatus(true);

		//ï¿½ï¿½ï¿½ï¿½ï¿½Æ¼ ï¿½Ð½Ãºï¿½ ï¿½ï¿½ï¿½ï¿½
		int member_count = party->getGuildMemberCountInParty(expNode->pc);
		if (member_count >= 2)
		{
			if (expNode->pc->m_avPassiveAddition.guild_party_exp > 0)
			{
				nGiveExp += (expNode->pc->m_avPassiveAddition.guild_party_exp * member_count);
			}
			if (expNode->pc->m_avPassiveRate.guild_party_exp > 0)
			{
				nGiveExp += nGiveExp * (expNode->pc->m_avPassiveRate.guild_party_exp - 100) * member_count / SKILL_RATE_UNIT;
			}

			if (expNode->pc->m_avPassiveAddition.guild_party_sp > 0)
			{
				nGiveSP += expNode->pc->m_avPassiveAddition.guild_party_sp * member_count;
			}
			if (expNode->pc->m_avPassiveRate.guild_party_sp > 0)
			{
				nGiveSP += nGiveSP * (expNode->pc->m_avPassiveRate.guild_party_sp - 100) * member_count / SKILL_RATE_UNIT;
			}
		}


		//ï¿½ï¿½ï¿½Î¿ï¿½ ï¿½ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		if (expNode->pc->m_level < nPartyLevelNew)
		{
			nGiveExp = nGiveExp * GetExpSPLevelPenaltyNew(nPartyLevelNew - expNode->pc->m_level) / 100;
			nGiveSP = nGiveSP * GetExpSPLevelPenaltyNew(nPartyLevelNew - expNode->pc->m_level) / 100;
		}

		// ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½
		expNode->pc->AddExpSP(nGiveExp, (int)nGiveSP, true, false, false, bArtifact);
		if (expNode->pc->m_party != NULL)
			expNode->pc->m_party->calcGuildSkillExp(expNode->pc, nGiveExp);

		CAPet* apet = expNode->pc->GetAPet();
		if (apet)
		{
			if (nHavePetCount == 0)
				nHavePetCount = 1;

			LONGLONG petexp = (npc->m_level) / 5 / nHavePetCount * (npc->m_proto->CheckFlag(NPC_MBOSS | NPC_BOSS) ? 4 : 1);
			apet->AddExpSP(petexp, 0);

			if (expNode->pc->m_petStashManager.getProxyPetItemvIndex() > -1)
			{
				int petVIndex = expNode->pc->m_petStashManager.getProxyPetItemvIndex();
				int petPlus = expNode->pc->m_petStashManager.getProxyPetItemPlus();
				if (expNode->pc->GetAPet(petPlus))
				{
					CAPet* proxyPet = expNode->pc->m_petStashManager.getProxyAPet();
					if (proxyPet != NULL)
					{
						petexp /= 10;
						proxyPet->AddExpSP(petexp, 0);
					}
				}
				else if (expNode->pc->GetPet(petPlus))
				{
					CPet* proxyPet = expNode->pc->m_petStashManager.getProxyPet();
					if (proxyPet != NULL)
					{
						if (proxyPet->m_level < PET_MAX_LEVEL)
						{
							petexp /= 10;
							proxyPet->m_exp += petexp;
							if (proxyPet->m_exp > proxyPet->GetNeedExp())
							{
								proxyPet->m_level++;
								proxyPet->IncreaseAbilityPoint(1);
								proxyPet->LevelUp();
								proxyPet->m_exp = 0;
							}
						}
					}
				}
				expNode->pc->m_petStashManager.UpdatePetData(petPlus);
			}
		}

		// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ PC ï¿½Ê±ï¿½È­
		expNode->pc->m_nExpDamage = 0;
	} // -- ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½Ð¹ï¿½ ï¿½ï¿½Æ¾ ï¿½ï¿½

	// ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½Ê±ï¿½È­
	while (expParty)
	{
		expPartyNode = expParty;
		int guild_skill_exp = 0;

		if (expPartyNode->pc->m_party != NULL)
		{
			guild_skill_exp = expPartyNode->pc->m_party->getGuildSkillExp(expPartyNode->pc);
		}

		if (guild_skill_exp != 0)
		{
			expPartyNode->pc->AddExpSP_Direct(guild_skill_exp, 0);

			{
				// Exp, SP ï¿½Þ½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
				CNetMsg::SP rmsg(new CNetMsg);
				ExpSPMsg(rmsg, guild_skill_exp, 0);
				SEND_Q(rmsg, expParty->pc->m_desc);
			}
		}

		expParty = expParty->next;
		expPartyNode->pc->m_nExpDamage = 0;
		delete expPartyNode;
	}

	party->m_guild_skill_exp.clear();
}

// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½é¿¡ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ SP ï¿½Ð¹ï¿½	(ï¿½ï¿½Æ¼, NPC, ï¿½ì¼±ï¿½ï¿½, ï¿½ï¿½Ã¼ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½)
void DivisionExpSPExped(CExpedition* Exped, CNPC* npc, CPC* pPreferencePC, LONGLONG nTotalDamage)
{
	// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½Ê½ï¿½ ï¿½ï¿½ï¿½Ìºï¿½ [%] : 1ï¿½Îºï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	static const int countBonus[MAX_PARTY_MEMBER] = { 20, 35, 50, 65, 80, 95, 105, 115 };

	EXP_LIST* expExped = NULL;		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®
	EXP_LIST* expExpedNode = NULL;	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½
	EXP_LIST* expNode = NULL;			// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	EXP_LIST* expNodeNext = NULL;		// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½

	LONGLONG			nExpedDamage = 0;		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½
	int					nExped = 0;				// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½
	int					nExpedLevelTotal = 0;	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½
	int					nExpedLevelMax = 0;		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ ï¿½ï¿½ï¿½ï¿½
	int					nExpedLevel = 0;		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	LONGLONG			nExpExped = 0;			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡
	LONGLONG			nSPExped = 0;			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ SP
	LONGLONG			nExpPenalty;			// ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½Ð³ï¿½Æ¼
	LONGLONG			nSPPenalty;				// SP ï¿½Ð³ï¿½Æ¼
	int					i;						// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	int					j;						// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	int					nHavePetCount = 0;			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½

	if (nTotalDamage < 1)
		return;

	if (Exped == NULL)
		return;

	if (npc == NULL)
		return;

	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ï±ï¿½
	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½Ï±ï¿½
	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½Ø´ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½
	for (i = 0; i < MAX_EXPED_GROUP; i++)
	{
		for (j = 0; j < MAX_EXPED_GMEMBER; j++)
		{
			CPC* pMember = Exped->GetNearMember(npc, i, j);
			if (pMember == NULL)
				continue;
			if (DEAD(pMember))
				continue;
			// ï¿½ï¿½Ã¼ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ß°ï¿½
			nExpedDamage += pMember->m_nExpDamage;
			// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ß°ï¿½
			expExpedNode = new EXP_LIST;
			expExpedNode->pc = pMember;
			expExpedNode->next = expExped;
			expExped = expExpedNode;
			nExped++;
			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			nExpedLevelTotal += pMember->m_level;
			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ ï¿½ï¿½ï¿½ï¿½
			if (nExpedLevelMax < pMember->m_level)
				nExpedLevelMax = pMember->m_level;

			// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Ä«ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½
			if (pMember->GetAPet())
				nHavePetCount++;
		}
	}

	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½Ð¹ï¿½ ï¿½ï¿½ï¿½ï¿½
	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½ 1ï¿½ï¿½ ï¿½Ì»ï¿½
	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 1 ï¿½Ì»ï¿½
	if (nExpedDamage > 0 && nExped > 0 && nExpedLevelTotal > 0)
	{
		int basic_Exped_plus_exp;
		int basic_Exped_plus_sp;

		// bw : 060817 : ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ã½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Îºï¿½, ï¿½Î¿ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ê½ï¿½ï¿½ï¿½ ï¿½Ñ¸ï¿½ï¿½Ï¶ï¿½ 0ï¿½Ìµï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		/*
		if( nParty == 1 )
		{
			basic_party_plus_exp = 0;
			basic_party_plus_sp = 0;
		}
		else
		*/
		{
			basic_Exped_plus_exp = PARTY_PLUS_EXP;
			basic_Exped_plus_sp = PARTY_PLUS_SP;
		}

		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		nExpedLevel = (nExpedLevelMax - (nExpedLevelTotal / nExped) > 5) ? (nExpedLevelMax - 5) : (nExpedLevelTotal / nExped);

		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ï±ï¿½
		int nLevelDiff = nExpedLevel - npc->m_level;

		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ð³ï¿½Æ¼ ï¿½ï¿½ï¿½Ï±ï¿½
		nExpPenalty = GetExpLevelPenalty(nLevelDiff);
		nSPPenalty = GetSPLevelPenalty(nLevelDiff);

		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ê½ï¿½ ï¿½ï¿½ï¿½Ï±ï¿½
		// 8ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½ï¿½ï¿½Ê½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½Ì»ï¿½ï¿½Ì¸ï¿½ 8ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		int tempExpBonus = 0;
		if (nExped > 8)
			tempExpBonus = countBonus[7];
		else
			tempExpBonus = countBonus[nExped - 1];

		LONGLONG nExpBonus = 100 + basic_Exped_plus_exp + tempExpBonus;

		int tempSPBonus = 0;
		if (nExped > 8)
			tempSPBonus = 35;
		else
			tempSPBonus = 6 * (nExped - 1);

		LONGLONG nSPBonus = 100 + basic_Exped_plus_sp + tempSPBonus;

		// ï¿½ï¿½ï¿½ï¿½ï¿½ë°¡ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡/SP ï¿½ï¿½ï¿½Ï±ï¿½
#ifdef PREMIUM_CHAR
		LONGLONG nExpNPC;
		if (pPreferencePC != NULL)
		{
			nExpNPC = npc->m_proto->getExpForPremiumChar(pPreferencePC->m_premiumChar.getPremiumType());
		}
		else
		{
			nExpNPC = npc->m_proto->getExp();
		}
#else
		LONGLONG nExpNPC = npc->m_proto->getExp();
#endif

#ifdef GRIND_EXP_LEVEL
		if (pPreferencePC != NULL) {
			if (pPreferencePC->m_level + gserver->m_serverConfig.min_exp_level < npc->m_level) {
				nExpNPC -= nExpNPC * 0.6;
				if (nExpNPC < 0) nExpNPC = 0;
			}
		}
#endif

		//nExpExped		= nExpNPC * nExpBonus * nExpPenalty * nExpedDamage / (100 * 100 * nTotalDamage);
		// Divide early to prevent 64-bit overflow: (A*B/100/100) * (C*D/TotalDmg) maintains precision while avoiding overflow
		nExpExped = (((nExpNPC * nExpBonus) / 100LL) * nExpPenalty / 100LL) * (nExpedDamage / nTotalDamage);
		if (nExpNPC >= 0 && nExpExped <= 0)
			nExpExped = (nExpNPC * nExpBonus / 100 * nExpPenalty / 100 * nExpedDamage) / nTotalDamage;

		// [2010-10-18 derek] ï¿½ï¿½Ä­ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ï¿½ï¿½ 1ï¿½ï¿½ ï¿½ï¿½ï¿½Í¼ï¿½ È®ï¿½ï¿½ ï¿½ï¿½ï¿½
		// ï¿½Ø¿ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½Ö¾î¼­ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½. ï¿½ï¿½ ï¿½É¾ï¿½ï¿½ï¿½ï¿½ï¿½? ï¿½ï¿½ï¿½ï¿½ï¿½Ñ°Í±ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ì³ï¿½ï¿½Âµï¿½ ï¿½ï¿½ ï¿½ß´ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½Ê³ï¿½.
		// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ã»ï¿½Ì¿ï¿½ï¿½ï¿½ï¿½ï¿½?
#ifdef PREMIUM_CHAR
		int tSkillPoint;
		if (pPreferencePC != NULL)
		{
			tSkillPoint = npc->m_proto->getSkillPointForPremiumChar(pPreferencePC->m_premiumChar.getPremiumType());
		}
		else
		{
			tSkillPoint = npc->m_proto->getSkillPoint();
		}
#else
		int tSkillPoint = npc->m_proto->getSkillPoint();
#endif
		nSPExped = tSkillPoint * nSPBonus * nSPPenalty * nExpedDamage / (100 * 100 * nTotalDamage);
		if (tSkillPoint > 0 && nSPExped <= 0)
			nSPExped = tSkillPoint * nSPBonus * nSPPenalty / 100 * nExpedDamage / nTotalDamage;

		// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
#if defined (LC_USA) || defined(LC_BILA)
		if (nExped >= 2)
		{
			nExpExped = nExpExped + (nExpExped * GetRandom(-10, 10) / 100);
			nSPExped = nSPExped + (nSPExped * GetRandom(-10, 10) / 100);
		}
#else
		nExpExped = nExpExped + (nExpExped * GetRandom(-10, 10) / 100);
		nSPExped = nSPExped + (nSPExped * GetRandom(-10, 10) / 100);
#endif // #if defined (LC_USA) || defined (LC_BILA)
	}
	else
	{
		// ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½Ê±ï¿½È­
		while (expExped)
		{
			expExpedNode = expExped;
			expExped = expExped->next;
			expExpedNode->pc->m_nExpDamage = 0;
			delete expExpedNode;
		}
		return;
	}

	// ï¿½ï¿½ï¿½ï¿½ï¿½ë¿¡ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡/SP ï¿½ï¿½ï¿½ï¿½
	LONGLONG nGiveExp = 0;		// ï¿½ï¿½ï¿½Þµï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡
	LONGLONG nGiveSP = 0;		// ï¿½ï¿½ï¿½Þµï¿½ SP
	LONGLONG nExpExpedForGive = 0;			// ï¿½ï¿½ï¿½Þ¿ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½Ä¡ : nExpParty or nExpParty_CA
	expNodeNext = expExped;
	while ((expNode = expNodeNext))
	{
		expNodeNext = expNodeNext->next;
		nExpExpedForGive = nExpExped;

		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Å¸ï¿½Ô¿ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡
		switch (Exped->GetExpedType(MSG_DIVITYPE_EXP))
		{
		case MSG_EXPED_TYPE_RANDOM:			// ï¿½Õµï¿½
		case MSG_EXPED_TYPE_FIRSTGET:		// ï¿½Ô¼ï¿½ ï¿½ì¼±
			//   ( (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä¡ 75%) * (ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½) / (ï¿½ï¿½Æ¼ï¿½Ñ·ï¿½ï¿½ï¿½) )
			// + ( (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä¡ 25%) / (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½) )
			nGiveExp = (nExpExpedForGive * 75 * expNode->pc->m_level / nExpedLevelTotal)
				+ (nExpExpedForGive * 25 / nExped);
			// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : ï¿½Ð¹ï¿½%
			nGiveExp /= 100;
			if (nExpExpedForGive > 0 && nGiveExp <= 0)
			{
				nGiveExp = (nExpExpedForGive * 75 / 100 * expNode->pc->m_level / nExpedLevelTotal)
					+ (nExpExpedForGive * 25 / 100 / nExped);
			}
			break;

		default:
		case MSG_EXPED_TYPE_BATTLE:			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			//   ( (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ 70%) * (ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½) / (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½) )
			// + ( (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ 30%) * (ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½) / (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ã¼ï¿½ï¿½ï¿½ï¿½) )
			nGiveExp = (nExpExpedForGive * 70 * expNode->pc->m_nExpDamage / nExpedDamage)
				+ (nExpExpedForGive * 30 * expNode->pc->m_level / nExpedLevelTotal);
			// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : ï¿½Ð¹ï¿½%
			nGiveExp /= 100;
			if (nExpExpedForGive > 0 && nGiveExp <= 0)
			{
				nGiveExp = (nExpExpedForGive * 70 / 100 * expNode->pc->m_nExpDamage / nExpedDamage)
					+ (nExpExpedForGive * 30 / 100 * expNode->pc->m_level / nExpedLevelTotal);
			}
			break;
		}

		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Å¸ï¿½Ô¿ï¿½ ï¿½ï¿½ï¿½ï¿½ SP
		switch (Exped->GetExpedType(MSG_DIVITYPE_SP))
		{
		case MSG_EXPED_TYPE_RANDOM:			// ï¿½Õµï¿½
		case MSG_EXPED_TYPE_BATTLE:			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			// (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ SP) / (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½)
			nGiveSP = nSPExped / nExped;
			break;

		default:
		case MSG_EXPED_TYPE_FIRSTGET:		// ï¿½Ô¼ï¿½ï¿½ì¼±
			// Ä³ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ð³ï¿½Æ¼
			nSPPenalty = GetSPLevelPenalty(expNode->pc->m_level - npc->m_level);

			//   ( (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½SP 20%) / (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½) )
			// + ( (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½SP 60%) * (ï¿½ï¿½ï¿½ï¿½Ú´ï¿½ï¿½ï¿½ï¿½) / (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½) )
			// + ( (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½SP 20%) * (ï¿½ï¿½ï¿½ï¿½Ú·ï¿½ï¿½ï¿½) / (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ñ·ï¿½ï¿½ï¿½) )
			nGiveSP = (nSPExped * 20 * nSPPenalty / nExped)
				+ (nSPExped * 60 * nSPPenalty * expNode->pc->m_nExpDamage / nExpedDamage)
				+ (nSPExped * 20 * nSPPenalty * expNode->pc->m_level / nExpedLevelTotal);
			// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : ï¿½Ð¹ï¿½%, ï¿½Ð³ï¿½Æ¼
			nGiveSP /= 10000;
			if (nSPExped > 0 && nGiveSP <= 0)
			{
				nGiveSP = (nSPExped * 20 / 100 * nSPPenalty / 100 / nExped)
					+ (nSPExped * 60 / 100 * nSPPenalty / 100 * expNode->pc->m_nExpDamage / nExpedDamage)
					+ (nSPExped * 20 / 100 * nSPPenalty / 100 * expNode->pc->m_level / nExpedLevelTotal);
			}
			break;
		}
		nGiveSP += GetTeachSPBonus(expNode->pc, nGiveSP);

		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ð³ï¿½Æ¼ : ï¿½Ö°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 15ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 5%ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		if (nExpedLevelMax - 15 > expNode->pc->m_level)
		{
			nGiveExp /= 20;
			nGiveSP /= 20;
		}

		// ï¿½ï¿½ï¿½ï¿½
		if (nGiveExp < 1)	nGiveExp = 1;
		if (nGiveSP < 1)	nGiveSP = 1;

		// SPï¿½ï¿½ MAX_SKILLPOINTï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		if (nGiveSP > MAX_SKILLPOINT) nGiveSP = MAX_SKILLPOINT;

		// 9ï¿½ï¿½ ï¿½Ìºï¿½Æ® : ï¿½ï¿½ï¿½ï¿½Ú°ï¿½ ï¿½ì¼±ï¿½ï¿½ï¿½ï¿½ï¿½Ì¸ï¿½
		bool bArtifact = false;
		if (expNode->pc == pPreferencePC)
		{
			// ï¿½ï¿½ï¿½ï¿½Ä¡ 4ï¿½ï¿½
			if (expNode->pc->m_assist.m_avAddition.hcSepExp)
			{
				expNode->pc->m_assist.CureByItemIndex(882);	// ï¿½ï¿½ï¿½ï¿½Ä¡
				nGiveExp = nGiveExp * 4;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_EXP);
				SEND_Q(rmsg, expNode->pc->m_desc);

				bArtifact = true;
			}
			// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡ 4ï¿½ï¿½
			else if (expNode->pc->m_assist.m_avAddition.hcSepExp_Cash)
			{
				expNode->pc->m_assist.CureByItemIndex(6094);	// ê²½í—˜ì¹˜
				nGiveExp = nGiveExp * 4;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_EXP);
				SEND_Q(rmsg, expNode->pc->m_desc);

				bArtifact = true;
			}

			else if (expNode->pc->m_assist.m_avAddition.hcSepExp)
			{
				expNode->pc->m_assist.CureByItemIndex(20590);	// ê²½í—˜ì¹˜
				nGiveExp = nGiveExp * 4;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_EXP);
				SEND_Q(rmsg, expNode->pc->m_desc);

				bArtifact = true;
			}

			else if (expNode->pc->m_assist.m_avAddition.hcSepExp_Prem)
			{
				expNode->pc->m_assist.CureByItemIndex(12057);	// ê²½í—˜ì¹˜
				nGiveExp = nGiveExp * 6;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_EXP);
				SEND_Q(rmsg, expNode->pc->m_desc);

				bArtifact = true;
			}

			else if (expNode->pc->m_assist.m_avAddition.hcRandomExpUp > 0 && GetRandom(0, 100) <= expNode->pc->m_assist.m_avAddition.hcRandomExpUp)
			{
				nGiveExp = nGiveExp * 4;

				CNetMsg::SP rmsg(new CNetMsg);
				EffectEtcMsg(rmsg, expNode->pc, MSG_EFFECT_ETC_RANDOM_EXP);
				expNode->pc->m_pArea->SendToCell(rmsg, expNode->pc, true);

				bArtifact = true;
			}

			// 9ï¿½ï¿½ ï¿½Ìºï¿½Æ® : SP 4ï¿½ï¿½
			if (expNode->pc->m_assist.m_avAddition.hcSepSP)
			{
				expNode->pc->m_assist.CureByItemIndex(883);	// ï¿½ï¿½ï¿½Ãµï¿½
				nGiveSP = nGiveSP * 4;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_SP);
				SEND_Q(rmsg, expNode->pc->m_desc);
			}
			// ï¿½ï¿½ï¿½ï¿½ SP 4ï¿½ï¿½
			else if (expNode->pc->m_assist.m_avAddition.hcSepSP_Cash)
			{
				expNode->pc->m_assist.CureByItemIndex(6095);	// ï¿½ï¿½ï¿½Ãµï¿½
				nGiveSP = nGiveSP * 4;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_SP);
				SEND_Q(rmsg, expNode->pc->m_desc);
			}

			else if (expNode->pc->m_assist.m_avAddition.hcSepSP)
			{
				expNode->pc->m_assist.CureByItemIndex(20591);	// ï¿½ï¿½ï¿½Ãµï¿½
				nGiveSP = nGiveSP * 4;
				CNetMsg::SP rmsg(new CNetMsg);
				EventErrorMsg(rmsg, MSG_EVENT_ERROR_SEPTEMBER_SP);
				SEND_Q(rmsg, expNode->pc->m_desc);
			}

			else if (expNode->pc->m_assist.m_avAddition.hcRandomSpUp > 0 && GetRandom(0, 100) <= expNode->pc->m_assist.m_avAddition.hcRandomSpUp)
			{
				nGiveSP = nGiveSP * 4;

				CNetMsg::SP rmsg(new CNetMsg);
				EffectEtcMsg(rmsg, expNode->pc, MSG_EFFECT_ETC_RANDOM_SP);
				expNode->pc->m_pArea->SendToCell(rmsg, expNode->pc, true);
			}
		}

#ifdef	NEW_ACCERY_ADD
		if (expNode->pc->m_AddProb)
		{
			nGiveExp = nGiveExp + (nGiveExp * expNode->pc->m_AddProb / 100);
			nGiveSP = nGiveSP + (nGiveSP * expNode->pc->m_AddProb / 100);
		}
#endif // NEW_ACCERY_ADD

		int GuildExp = 0;
		if (expNode->pc->m_guildInfo && expNode->pc->m_guildInfo->guild())
		{
			CGuild* guild = expNode->pc->m_guildInfo->guild();
			if (expNode->pc->m_guildInfo->GetcontributeExp() != 0)
			{
				GuildExp = nGiveExp * expNode->pc->m_guildInfo->GetcontributeExp() / 100;
				expNode->pc->m_GuildExp += GuildExp;
				nGiveExp = nGiveExp - GuildExp;
				LONGLONG GP = 0;
				if (expNode->pc->m_GuildExp >= 10000)
				{
					GP = expNode->pc->m_GuildExp / 10000;
					expNode->pc->m_GuildExp = expNode->pc->m_GuildExp % 10000;
					guild->AddGuildPoint(GP);
					expNode->pc->m_guildInfo->AddCumulatePoint(GP);

					{
						CNetMsg::SP rmsg(new CNetMsg);
						HelperNewGuildPointUpdate(rmsg, expNode->pc->m_index, guild->index(), GP);
						SEND_Q(rmsg, gserver->m_helper);
					}

					{
						CNetMsg::SP rmsg(new CNetMsg);
						HelperSaveGuildMemberPointMsg(rmsg, guild->index(), expNode->pc->m_index, GP);
						SEND_Q(rmsg, gserver->m_helper);
					}
				}

			}
		}

		// EP = ( NPCï¿½ï¿½ï¿½ï¿½  * ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Î¿ï¿½ ) + ( NPCï¿½ï¿½ï¿½ï¿½ * ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ / NPC HP ) / 2
		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
		int	recalcDamage = (int)expNode->pc->m_nExpDamage;
		if (recalcDamage > npc->m_maxHP)
			recalcDamage = npc->m_maxHP;

#ifdef PREMIUM_CHAR
		LONGLONG nGetEnergy;
		if (pPreferencePC != NULL)
		{
			nGetEnergy = (LONGLONG)npc->m_proto->getSkillPointForPremiumChar(pPreferencePC->m_premiumChar.getPremiumType()) * (LONGLONG)recalcDamage / (LONGLONG)npc->m_maxHP;
		}
		else
		{
			nGetEnergy = (LONGLONG)npc->m_proto->getSkillPoint() * (LONGLONG)recalcDamage / (LONGLONG)npc->m_maxHP;
		}
#else
		LONGLONG nGetEnergy = (LONGLONG)npc->m_proto->getSkillPoint() * (LONGLONG)recalcDamage / (LONGLONG)npc->m_maxHP;
#endif
		int ep = (npc->m_proto->m_level * nExped) + ((int)nGetEnergy) / 2;

		if (expNode->pc->m_level <= 160)
			ep *= 4;

		if (ABS(npc->m_level - expNode->pc->m_level) < gserver->m_serverConfig.min_ep_level)
		{
			expNode->pc->AddEP(ep);
		}
		expNode->pc->CalcStatus(true);

		// ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½
		expNode->pc->AddExpSP(nGiveExp, (int)nGiveSP, true, false, false, bArtifact);

		CAPet* apet = expNode->pc->GetAPet();
		if (apet)
		{
			if (nHavePetCount == 0)
				nHavePetCount = 1;

			LONGLONG petexp = (npc->m_level) / 5 / nHavePetCount * (npc->m_proto->CheckFlag(NPC_MBOSS | NPC_BOSS) ? 4 : 1);
			apet->AddExpSP(petexp, 0);

			if (expNode->pc->m_petStashManager.getProxyPetItemvIndex() > -1)
			{
				int petVIndex = expNode->pc->m_petStashManager.getProxyPetItemvIndex();
				int petPlus = expNode->pc->m_petStashManager.getProxyPetItemPlus();
				if (expNode->pc->GetAPet(petPlus))
				{
					CAPet* proxyPet = expNode->pc->m_petStashManager.getProxyAPet();
					if (proxyPet != NULL)
					{
						petexp /= 10;
						proxyPet->AddExpSP(petexp, 0);
					}
				}
				else if (expNode->pc->GetPet(petPlus))
				{
					CPet* proxyPet = expNode->pc->m_petStashManager.getProxyPet();
					if (proxyPet != NULL)
					{
						if (proxyPet->m_level < PET_MAX_LEVEL)
						{
							petexp /= 10;
							proxyPet->m_exp += petexp;
							if (proxyPet->m_exp > proxyPet->GetNeedExp())
							{
								proxyPet->m_level++;
								proxyPet->IncreaseAbilityPoint(1);
								proxyPet->LevelUp();
								proxyPet->m_exp = 0;
							}
						}
					}
				}
				expNode->pc->m_petStashManager.UpdatePetData(petPlus);
			}
		}

		// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ PC ï¿½Ê±ï¿½È­
		expNode->pc->m_nExpDamage = 0;
	} // -- ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ð¹ï¿½ ï¿½ï¿½Æ¾ ï¿½ï¿½

	// ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½Ê±ï¿½È­
	while (expExped)
	{
		expExpedNode = expExped;
		expExped = expExped->next;
		expExpedNode->pc->m_nExpDamage = 0;
		delete expExpedNode;
	}
}

int GetExpLevelPenalty(int nLevelDiff)
{
	int nExpPenalty = 100;
	if (nLevelDiff > 0)
	{
		// ï¿½ï¿½ï¿½ï¿½Ä¡ ï¿½Ð³ï¿½Æ¼ Ã³ï¿½ï¿½ : ï¿½Ö´ï¿½ 6ï¿½ï¿½ï¿½ï¿½
		if (nLevelDiff > 6)
			nExpPenalty = levelPenalty[5];
		else
			nExpPenalty = levelPenalty[nLevelDiff - 1];
	}
	return nExpPenalty;
}

int GetSPLevelPenalty(int nLevelDiff)
{
	int nSPPenalty = 100;
	if (nLevelDiff > 0)
	{
		// SP ï¿½Ð³ï¿½Æ¼ Ã³ï¿½ï¿½ : MAX_PENALTY_SP_LEVELï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 1
		if (nLevelDiff > MAX_PENALTY_SP_LEVEL)
			nSPPenalty = 0;
		else
			nSPPenalty = 100 - (nLevelDiff * DOWN_LEVEL_SP);
	}

	return nSPPenalty;
}

LONGLONG GetTeachSPBonus(CPC* ch, LONGLONG sp)
{
	if (ch->m_teachType == MSG_TEACH_STUDENT_TYPE)
	{
		if (ch->m_teachIdx[0] != -1) // ï¿½Ä°ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö¾ï¿½ï¿½ ï¿½Ñ´ï¿½ ï¿½ï¿½ï¿½Ê½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½Ö¶ï¿½.
		{
			CPC* tpc = PCManager::instance()->getPlayerByCharIndex(ch->m_teachIdx[0]);
			if (tpc != NULL)
			{
				// ï¿½Ä°ï¿½ï¿½Î¿ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ê½ï¿½ SP 2% ï¿½ï¿½ï¿½ï¿½
				LONGLONG tpcGiveSP = sp * TEACH_SP_TEACHER / 100;
				tpc->AddExpSP(0, (int)tpcGiveSP, false);

				// ï¿½ß½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ê½ï¿½ sp 5% ï¿½ï¿½ï¿½ï¿½
				return (sp * TEACH_SP_STUDENT / 100);
			}
		}
	}
	return 0;
}

int GetExpSPLevelPenaltyNew(int nLevelDiff)
{
	int value = 100;

	if (nLevelDiff >= 150)
	{
		value = 30;
	}
	else if (nLevelDiff >= 100)
	{
		value = 50;
	}
	else if (nLevelDiff >= 50)
	{
		value = 80;
	}
	else if (nLevelDiff >= 30)
	{
		value = 90;
	}

	return value;
}
