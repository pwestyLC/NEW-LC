#include "stdhdrs.h"

#include "Server.h"
#include "Battle.h"
#include "WarCastle.h"
#include "DratanCastle.h"

// of�� df�� ������ ��, ���� ���ϴ� ���� ó��
bool IsAvailableAttack(CCharacter* of, CCharacter* df)
{
	CPC*		opc				= NULL;
	CPC*		dpc				= NULL;
	CNPC*		onpc			= NULL;
	CNPC*		dnpc			= NULL;
	CPet*		opet			= NULL;
	CPet*		dpet			= NULL;
	CElemental*	oelemental		= NULL;
	CElemental*	delemental		= NULL;
	CAPet*		oapet			= NULL;
	CAPet*		dapet			= NULL;

#ifdef BUGFIX_DEAD_AGAIN_DEAD
	// ������ 3�ʳ��� ���� ���� ������ �Ұ��Ѵ�.
	if(IS_PC(df) && (mktime(&gserver->m_tRealSystemTime) - df->m_deadTime < BUGFIX_DEAD_SECONDS))
	{
		GAMELOG << init("DEAD AGAIN DEAD") << (LONGLONG)mktime(&gserver->m_tRealSystemTime) << delim << (LONGLONG)df->m_deadTime << end;
		return false;
	}
#endif

	// ���� ����� ���̻� ���� �Ұ�
	if (DEAD(df))
		return false;

	// �ǽ��������� ���� �Ұ�
	if (of->IsInPeaceZone(true) || df->IsInPeaceZone(true))
		return false;

	// ����� �Ⱥ��̸� ���� �Ұ�
	if (!of->CanVisible(df))
		return false;

	// �����ڿ� ����ڰ� rvr���� �ְ� ���� �ε��� ������ ���� �Ұ�
	if (of->m_pZone->isRVRZone() &&	df->m_pZone->isRVRZone() &&	of->getSyndicateType() == df->getSyndicateType())
	{
		return false;
	}

	switch (of->m_type)
	{
	case MSG_CHAR_PC:
		opc = TO_PC(of);
		break;

	case MSG_CHAR_NPC:
		onpc = TO_NPC(of);
		break;

	case MSG_CHAR_PET:
		opet = TO_PET(of);
		opc = opet->GetOwner();
		if (opc == NULL)
			return false;
		break;

	case MSG_CHAR_ELEMENTAL:
		oelemental = TO_ELEMENTAL(of);
		opc = oelemental->GetOwner();
		if (opc == NULL)
			return false;
		break;
	case MSG_CHAR_APET:
		oapet	= TO_APET(of);
		opc		= oapet->GetOwner();
		if( opc == NULL )
			return false;
		if( !oapet->IsProtoFlag( APET_FLAG_ATTACK ) )
			return false;
		break;

	default:
		return false;
	}

	switch (df->m_type)
	{
	case MSG_CHAR_PC:
		dpc = TO_PC(df);
		break;

	case MSG_CHAR_NPC:
		dnpc = TO_NPC(df);
		if( dnpc->m_proto->CheckFlag1(NPC1_DONT_ATTACK) ) // ���� ���� ���ϴ� �÷��װ� ���������� ������ �� ����.
			return false;
		break;

	case MSG_CHAR_PET:
		dpet = TO_PET(df);
		dpc = dpet->GetOwner();
		if (dpc == NULL)
			return false;
		break;

	case MSG_CHAR_ELEMENTAL:
		delemental = TO_ELEMENTAL(df);
		dpc = delemental->GetOwner();
		if (dpc == NULL)
			return false;
		break;
	case MSG_CHAR_APET:
		dapet = TO_APET(df);
		dpc = dapet->GetOwner();
		if(dapet == NULL)
			return false;
		if( !dapet->IsProtoFlag( APET_FLAG_ATTACK ) )
			return false;
		break;

	default:
		return false;
	}
	// opc�� immortal �˻�
	if (opc && opc->m_bImmortal && opc->m_bFirstDoIt == false)
	{
		DelAttackList(of);
		return false;
	}

	// dpc�� immortal �˻�
	if (dpc && dpc->m_bImmortal)
	{
		DelAttackList(df);
		return false;
	}

	// PC�� disable �˻�
	if ((opc && opc->IsDisable()) || (dpc && dpc->IsDisable()))
		return false;

	if(opc && opc->m_assist.FindByType(MT_OTHER, MST_OTHER_PEACE) && dpc)
		return false;

	// ����� Ÿ�Կ� ���� ó��
	switch (df->m_type)
	{
	case MSG_CHAR_NPC:

		// ���� �ȴ��ϴ� NPC �� �˻�
		if (!(IS_NPC(of) && of->m_pZone->IsPersonalDungeon()) && dnpc->m_proto->CheckFlag(NPC_SHOPPER | NPC_ZONEMOVER | NPC_REFINER | NPC_QUEST | NPC_PEACEFUL | NPC_MINERAL | NPC_CROPS | NPC_ENERGY | NPC_REMISSION))
		{
			if (of->m_pZone->m_index == ZONE_DRATAN)
			{
				CDratanCastle * pCastle = CDratanCastle::CreateInstance();
				if( pCastle->GetState() == WCSF_NORMAL )
				{
					return false;
				}
			}
			if( dnpc->m_proto->CheckFlag(NPC_ZONEMOVER) &&
					!( opc && opc->GetJoinFlag(opc->m_pZone->m_index) & (WCJF_ATTACK_GUILD | WCJF_ATTACK_CHAR) ) )
			{
				return false;
			}
		}

		// ȣ�ڸӸ�(2470~2475)�� �������� �ʾ�����
		if( IS_PC(of) && dnpc->m_proto->m_index == 454 && gserver->isActiveEvent(A_EVENT_HALLOWEEN))
		{
			CItem * pHelmet = TO_PC(of)->m_wearInventory.wearItemInfo[WEARING_HELMET] ;
			if( pHelmet == NULL )
				return false;

			if( !( (pHelmet->m_itemProto->getItemIndex() >= 4927 && pHelmet->m_itemProto->getItemIndex() <= 4932) || pHelmet->m_itemProto->getItemIndex() == 6228 ) )
				return false;
		}

		// ���´� ���ݴ����� ����
		if (dnpc->m_proto->CheckFlag(NPC_LORD_SYMBOL))
			return false;

		// ��ȣ���� �������� ������������ ���� ����
		if (dnpc->m_proto->CheckFlag(NPC_CASTLE_GUARD | NPC_CASTLE_TOWER))
		{
			// ���� ���� �˻�
			if ( !(of->GetMapAttr() & MATT_WAR) )
				return false;

			// ���������� �˻�

			if(of->m_pZone->m_index == ZONE_MERAC)
			{
				CWarCastle * pCastle = CWarCastle::GetCastleObject(ZONE_MERAC);
				if (pCastle == NULL)
				{
					return false;
				}

				if ( pCastle->GetState() == WCSF_NORMAL)
				{
					return false;
				}
			}
			else if (of->m_pZone->m_index == ZONE_DRATAN)
			{
				CDratanCastle * pCastle = CDratanCastle::CreateInstance();
				if (pCastle->GetState() == WCSF_NORMAL)
				{
					return false;
				}
			}

			// ���� ���� ���� �˻�
			if (dpc)
			{
				switch (dpc->GetJoinFlag(df->m_pZone->m_index))
				{
				case WCJF_NONE:
				case WCJF_OWNER:
				case WCJF_DEFENSE_GUILD:
				case WCJF_DEFENSE_CHAR:
					return false;
				default:
					break;
				}
			}
		}

#ifdef EXTREME_CUBE
		// ����� ����
		if(dnpc->m_proto->m_index == 529)
		{
			if(opc)
			{
				if(gserver->m_extremeCube.IsGuildCubeTime())		// ��� ť��Ÿ���� ��
				{
					if(opc->m_guildInfo
							&& opc->m_guildInfo->guild()
							&& opc->m_guildInfo->guild()->m_cubeUniqueIdx != -1)
					{
						int cubeidx;
						CBattleSpace* battlespace;
						CCubeMemList* memlist = gserver->m_extremeCube.FindMemList(opc->m_guildInfo->guild());
						if(!memlist)
							return false;

						memlist->GetCubeNum(cubeidx);
						CCubeSpace* space = gserver->m_extremeCube.GetExtremeCube(cubeidx);
						if(!space)
						{
							return false;
						}

						if(!space->IsBattleCubeSpace())
						{
							return false;
						}

						battlespace = (CBattleSpace*)space;

						if(!battlespace->WinMemList()
								|| battlespace->WinMemList() != memlist
								|| battlespace->m_crystal !=  dnpc)
							return false;
					}
				}
				else
				{
					if(opc->m_party && opc->m_party->m_cubeUniqueIdx != -1)
					{
						int cubeidx;
						CBattleSpace* battlespace;
						CCubeMemList* memlist = gserver->m_extremeCube.FindMemList(opc->m_party);
						if(!memlist)
							return false;

						memlist->GetCubeNum(cubeidx);
						CCubeSpace* space = gserver->m_extremeCube.GetExtremeCube(cubeidx);
						if(!space)
						{
							return false;
						}

						if(!space->IsBattleCubeSpace())
						{
							return false;
						}

						battlespace = (CBattleSpace*)space;

						if(!battlespace->WinMemList()
								|| battlespace->WinMemList() != memlist
								|| battlespace->m_crystal != dnpc)
							return false;
					}
				}

				if(gserver->m_extremeCube.GetAvailableBossCube() == -1)
					return false;
			}
		}
#endif // EXTREME_CUBE

		break;	// case MSG_CHAR_NPC:

	case MSG_CHAR_PC:
	case MSG_CHAR_PET:
	case MSG_CHAR_ELEMENTAL:
	case MSG_CHAR_APET:

		// �����ڿ� ���� ó��
		switch (of->m_type)
		{
		case MSG_CHAR_PC:
		case MSG_CHAR_ELEMENTAL:		// kj : ��ȯ���� ���ݽÿ��� PVP ���� �˻�
		case MSG_CHAR_APET:
			{
				// PvP ���� �˻�
				// Ÿ���� ���� ���� �κ����� ������� ������ ���� �����ϵ��� ����.
				bool bIgnoreInvisible = false;
				if ( IS_APET(df) )
					bIgnoreInvisible = true;

				if (!opc->CanPvP(dpc, bIgnoreInvisible))
					return false;
			}
			break;

		default:
			break;
		} // switch (of->m_type)

		break;	// case MSG_CHAR_PC:

	default:
		return false;
	} // switch (df->m_type)

	return true;
}
//