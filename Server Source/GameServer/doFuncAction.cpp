#include "stdhdrs.h"

#include "Log.h"
#include "Character.h"
#include "Server.h"
#include "DratanCastle.h"
#include "../ShareLib/packetType/ptype_old_do_action.h"

void do_Action(CPC* ch, CNetMsg::SP& msg)
{
	CDratanCastle * pCastle = CDratanCastle::CreateInstance();
	pCastle->CheckRespond(ch);

	RequestClient::action* packet = reinterpret_cast<RequestClient::action*>(msg->m_buf);

	//�����ȿ��� (��)�����̵� ��� �Ұ�
	if(ch->m_nJoinInzone_ZoneNo >=0 && ch->m_nJoinInzone_RoomNo >= 0)
	{
		if(packet->index == 38)
			return;
	}

	switch (packet->type)
	{
	case ACTION_GENERAL:
		{
			switch (packet->index)
			{
			case AGT_SITDOWN:				// �ɱ� ����
			case AGT_PET_SITDOWN:			// �� �ɱ� ����
				{
					// ���� ���¸� ����
					if (DEAD(ch) || ch->m_personalshop != NULL || ch->IsSetPlayerState(PLAYER_STATE_CHANGE))
						return ;

					// �� �ɱ� ���� ���� ���� Ÿ�� �־�� ��
					if (packet->index == AGT_PET_SITDOWN)
					{
						if (!ch->GetPet() || !ch->GetPet()->IsMount())
							return ;
					}

					if (!ch->IsSetPlayerState(PLAYER_STATE_SITDOWN))
					{
						if (ch->m_currentSkill)
						{
							ch->m_currentSkill->Cancel(ch);
							ch->m_currentSkill = NULL;
						}
						ch->ResetPlayerState(PLAYER_STATE_MOVING);
					}
					ch->TogglePlayerState(PLAYER_STATE_SITDOWN);
					ch->CalcStatus(true);
				}
				break;

			case AGT_PKMODE:			// ��ȭ/��� ���
				{
#ifdef BLOCK_PVP
					return;
#else
					if ( gserver->m_bNonPK )
						return;
					
					if (DEAD(ch) || ch->m_personalshop != NULL)
						return ;

					if (ch->m_pZone->m_index == ZONE_GUILDROOM)
						return;

					if (ch->m_assist.FindBySkillIndex(PVP_PROTECT_SKILL_INDEX) != 0)
					{
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsg(rmsg, MSG_SYS_DO_NOT_PLAY_PVP);
						SEND_Q(rmsg, ch->m_desc);
						return;
					}

					if (ch->m_level <= PKMODE_LIMIT_LEVEL)
					{
						bool bSkipLevel = false;
						// ���� ���� �� ���� ���� �������� �������� PK ����
						if (ch->m_pZone->m_index == CWarCastle::GetCurSubServerCastleZoneIndex() && ch->GetMapAttr() & MATT_WAR)
						{
							CWarCastle* castle = CWarCastle::GetCastleObject(ch->m_pZone->m_index);
							if (castle && castle->GetState() != WCSF_NORMAL)
							{
								bSkipLevel = true;
							}
						}

						if (!bSkipLevel)
						{
							CNetMsg::SP rmsg(new CNetMsg);
							SysMsg(rmsg, MSG_SYS_PKMODE_LIMITLEVEL);
							SEND_Q(rmsg, ch->m_desc);
							return;
						}
					}

					if (ch->IsSetPlayerState(PLAYER_STATE_PKMODEDELAY) || ch->IsSetPlayerState(PLAYER_STATE_RAMODE) || ch->IsSetPlayerState(PLAYER_STATE_CHANGE))
						return ;

					if (ch->IsInPeaceZone(true))
						return ;

					if (ch->GetMapAttr() & MATT_FREEPKZONE)
						return ;

					// PVP �Ʒ��� ���̸��� ���������� ���� ������ ��� pk��尡 �ȵǰ� ����..   yhj
					if ( !(ch->GetMapAttr() & MATT_FREEPKZONE)
							&& !(ch->GetMapAttr() & MATT_PEACE)
							&& ch->m_pZone->m_index == ZONE_PK_TOURNAMENT )
					{
						return ;
					}

					// ��Ʈ���̾Ƴ� ���� ��ܿ��� pk��尡 �ȵǰ� ����..   yhj
					// ���� ��ǥ�� ��Ʈ���̾Ƴ� ������ ������ǥ
					if ( (ch->GetMapAttr() & MATT_STAIR_UP || ch->GetMapAttr() & MATT_STAIR_DOWN )
							&& ch->m_pZone->m_index == ZONE_STREIANA
							&& GET_X(ch) >= 940.0 && GET_X(ch) <= 1090.0
							&& GET_Z(ch) >= 515.0 && GET_Z(ch) <= 695.0 )
					{
						return ;
					}

#ifdef CAPTURE_THE_FLAG_10282021
					if (ch->m_bHasFlagItem && !ch->IsInPeaceZone(true))
					{
						ch->m_assist.CureBySkillIndex(IMMOTAL_BUF);
						ch->m_assist.CureBySkillIndex(CUBE_BUF);
						ch->m_assist.CureBySkillIndex(IGNI1_BUF);
						ch->m_assist.CureBySkillIndex(IGNI2_BUF);
						ch->m_assist.CureBySkillIndex(IGNI3_BUF);
						ch->m_assist.CureBySkillIndex(IGNI4_BUF);
						ch->m_assist.CureBySkillIndex(CAST_POTION);
						ch->m_assist.CureBySkillIndex(VELOCITY_BUF);
						ch->m_assist.CureBySkillIndex(INVISIBILITY);
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsg(rmsg, MSG_SYS_DO_NOT_CHANGE_PK_MODE);
						SEND_Q(rmsg, ch->m_desc);
						return;
					}
#endif

					if (ch->m_pZone->IsOXQuizRoom())
					{
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsg(rmsg, MSG_SYS_DO_NOT_CHANGE_PK_MODE);
						SEND_Q(rmsg, ch->m_desc);
						return ;
					}

					if (ch->m_pZone->isRVRZone())
					{
						CNetMsg::SP rmsg(new CNetMsg);
						SysMsg(rmsg, MSG_SYS_DO_NOT_CHANGE_PK_MODE);
						SEND_Q(rmsg, ch->m_desc);
						return ;
					}

					if (ch->IsSetPlayerState(PLAYER_STATE_PKMODE))
					{
						ch->SetPlayerState(PLAYER_STATE_PKMODEDELAY);
						ch->m_pkmodedelay = PULSE_PKMODE_DELAY;
					}
					else
					{
						ch->TogglePlayerState(PLAYER_STATE_PKMODE);
						ch->CancelInvisible();
					}

					if (ch->GetPlayerState() == PLAYER_STATE_PKMODEDELAY || 
					ch->GetPlayerState() == PLAYER_STATE_PKMODE) {
						ch->m_assist.CureBySkillIndex(IMMOTAL_BUF);
						ch->m_assist.CureBySkillIndex(CUBE_BUF);
						ch->m_assist.CureBySkillIndex(IGNI1_BUF);
						ch->m_assist.CureBySkillIndex(IGNI2_BUF);
						ch->m_assist.CureBySkillIndex(IGNI3_BUF);
						ch->m_assist.CureBySkillIndex(IGNI4_BUF);
						ch->m_assist.CureBySkillIndex(CAST_POTION);
						ch->m_assist.CureBySkillIndex(VELOCITY_BUF);
						ch->m_assist.CureBySkillIndex(1742);
						ch->m_assist.CureBySkillIndex(975);
						ch->m_assist.CureBySkillIndex(1897);
						ch->m_assist.CureBySkillIndex(981);
						ch->m_assist.CureBySkillIndex(1903);
						ch->m_assist.CureBySkillIndex(988);
						ch->m_assist.CureBySkillIndex(1910);
						ch->m_assist.CureBySkillIndex(1172);
						ch->m_assist.CureBySkillIndex(1278);
						ch->m_assist.CureBySkillIndex(1310);
						ch->m_assist.CureBySkillIndex(1938);
						ch->m_assist.CureBySkillIndex(1174);
						ch->m_assist.CureBySkillIndex(1280);
						ch->m_assist.CureBySkillIndex(1312);
						ch->m_assist.CureBySkillIndex(1940);
						ch->m_assist.CureBySkillIndex(1188);
						ch->m_assist.CureBySkillIndex(1287);
						ch->m_assist.CureBySkillIndex(1319);
						ch->m_assist.CureBySkillIndex(1947);
						ch->m_assist.CureBySkillIndex(931);
						ch->m_assist.CureBySkillIndex(1037);
						ch->m_assist.CureBySkillIndex(1876);
						ch->m_assist.CureBySkillIndex(1918);
						ch->m_assist.CureBySkillIndex(936);
						ch->m_assist.CureBySkillIndex(1042);
						ch->m_assist.CureBySkillIndex(1881);
						ch->m_assist.CureBySkillIndex(1923);
						ch->m_assist.CureBySkillIndex(947);
						ch->m_assist.CureBySkillIndex(10553);
						ch->m_assist.CureBySkillIndex(1892);
						ch->m_assist.CureBySkillIndex(1934);
						ch->m_assist.CureBySkillIndex(946);
						ch->m_assist.CureBySkillIndex(1891);
						ch->m_assist.CureBySkillIndex(1052);
						ch->m_assist.CureBySkillIndex(1933);
						ch->m_assist.CureBySkillIndex(963);
						ch->m_assist.CureBySkillIndex(967);
						ch->m_assist.CureBySkillIndex(1186);
						ch->m_assist.CureBySkillIndex(1285);
						ch->m_assist.CureBySkillIndex(1317);
						ch->m_assist.CureBySkillIndex(1945);
						ch->m_assist.CureBySkillIndex(1036);
						ch->m_assist.CureBySkillIndex(1917);
						ch->m_assist.CureBySkillIndex(794);
						ch->m_assist.CureBySkillIndex(1896);
						ch->m_assist.CureBySkillIndex(980);
						ch->m_assist.CureBySkillIndex(1902);
						ch->m_assist.CureBySkillIndex(968);
						ch->m_assist.CureBySkillIndex(962);
						ch->m_assist.CureBySkillIndex(1093);
						ch->m_assist.CureBySkillIndex(229);
						ch->m_assist.CureBySkillIndex(323);
						ch->m_assist.CureBySkillIndex(1798);
						ch->m_assist.CureBySkillIndex(1871);
						ch->m_assist.CureBySkillIndex(1997);
						ch->m_assist.CureBySkillIndex(1998);
						ch->m_assist.CureBySkillIndex(1999);
						ch->m_assist.CureBySkillIndex(2000);
						ch->m_assist.CureBySkillIndex(2001);
						ch->m_assist.CureBySkillIndex(2002);
						ch->m_assist.CureBySkillIndex(2003);
						ch->m_assist.CureBySkillIndex(2013);
						ch->m_assist.CureBySkillIndex(2044);
						ch->m_assist.CureBySkillIndex(2045);
						ch->m_assist.CureBySkillIndex(2046);
						ch->m_assist.CureBySkillIndex(2047);
						ch->m_assist.CureBySkillIndex(987);
						ch->m_assist.CureBySkillIndex(1909);
						ch->m_assist.CureBySkillIndex(935);
						ch->m_assist.CureBySkillIndex(1880);
						ch->m_assist.CureBySkillIndex(1057);
						ch->m_assist.CureBySkillIndex(1058);
						ch->m_assist.CureBySkillIndex(1059);
						ch->m_assist.CureBySkillIndex(1077);
						ch->m_assist.CureBySkillIndex(1076);
						ch->m_assist.CureBySkillIndex(939);
						ch->m_assist.CureBySkillIndex(941);
						ch->m_assist.CureBySkillIndex(943);
						ch->m_assist.CureBySkillIndex(966);
						ch->m_assist.CureBySkillIndex(971);
						ch->m_assist.CureBySkillIndex(977);
						ch->m_assist.CureBySkillIndex(984);
						ch->m_assist.CureBySkillIndex(991);
						ch->m_assist.CureBySkillIndex(1045);
						ch->m_assist.CureBySkillIndex(1047);
						ch->m_assist.CureBySkillIndex(1049);
						ch->m_assist.CureBySkillIndex(1176);
						ch->m_assist.CureBySkillIndex(1190);
						ch->m_assist.CureBySkillIndex(1197);
						ch->m_assist.CureBySkillIndex(1282);
						ch->m_assist.CureBySkillIndex(1289);
						ch->m_assist.CureBySkillIndex(1296);
						ch->m_assist.CureBySkillIndex(1314);
						ch->m_assist.CureBySkillIndex(1321);
						ch->m_assist.CureBySkillIndex(1328);
						ch->m_assist.CureBySkillIndex(1369);
						ch->m_assist.CureBySkillIndex(1884);
						ch->m_assist.CureBySkillIndex(1886);
						ch->m_assist.CureBySkillIndex(1888);
						ch->m_assist.CureBySkillIndex(1899);
						ch->m_assist.CureBySkillIndex(1906);
						ch->m_assist.CureBySkillIndex(1913);
						ch->m_assist.CureBySkillIndex(1926);
						ch->m_assist.CureBySkillIndex(1928);
						ch->m_assist.CureBySkillIndex(1930);
						ch->m_assist.CureBySkillIndex(1942);
						ch->m_assist.CureBySkillIndex(1949);
						ch->m_assist.CureBySkillIndex(1956);
						ch->m_assist.CureBySkillIndex(1080);
						ch->m_assist.CureBySkillIndex(1834);
						ch->m_assist.CureBySkillIndex(1835);
						ch->m_assist.CureBySkillIndex(1836);
						ch->m_assist.CureBySkillIndex(1838);
						ch->m_assist.CureBySkillIndex(1839);
						ch->m_assist.CureBySkillIndex(1837);
						ch->m_assist.CureBySkillIndex(2057);
						ch->m_assist.CureBySkillIndex(1079);
						

						CNetMsg::SP rmsg(new CNetMsg);
						ResponseClient::makeAction(rmsg, ch, ACTION_GENERAL, AGT_PKMODE);
						ch->m_pArea->SendToCell(rmsg, ch, true);
					}
#endif
				}
				break;

			case AGT_THROW_WATER:
				{
					if( !gserver->isActiveEvent(A_EVENT_SONGKRAN) )
						return;

					CCharacter* tch = ch->m_pArea->FindCharInCell( ch, packet->targetIndex, MSG_CHAR_PC, true );
					if( tch == NULL )
					{
						return;
					}

					CSkill* skill = new CSkill( gserver->m_skillProtoList.Find( 436 ), 1 );
					bool bApply;
					ApplySkill( ch, tch, skill, -1, bApply );
					delete skill;
				}

				break;
			} // end switch
		}
		break;

	case ACTION_SOCIAL:
	case ACTION_PARTY:
	case ACTION_GUILD:
	case ACTION_TITLE:
		break;

	default:
		{
			LOG_ERROR("HACKING : invalid action type[%d]. charIndex[%d]", packet->type, ch->m_index);
			ch->m_desc->Close("invalid action type");
			return;
		}
	} // end switch

	{
		CNetMsg::SP rmsg(new CNetMsg);
		ResponseClient::makeAction(rmsg, ch, packet->type, packet->index);
		ch->m_pArea->SendToCell(rmsg, ch, true);
	}
}
//