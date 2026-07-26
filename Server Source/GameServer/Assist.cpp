/************************************
  ��������
  ������ ���: bs
  ������: 2004-11-18 ���� 3:37:20
  ����: ���� ��ȭ ����
 ************************************/
#include <boost/format.hpp>
#include "stdhdrs.h"

#include "Server.h"
#include "Skill.h"
#include "Assist.h"
#include "CmdMsg.h"
#include "Log.h"
#include "Artifact_Manager.h"
#include "../ShareLib/packetType/ptype_old_do_skill.h"

#define APPVAL(v)		{ \
							switch (mp->m_damagetype) \
							{ \
							case MDT_ADDITION: \
								addition->v += mlp->m_nPowerValue * CalcSkillParam(ch, ch, SPARAM_NONE, mp->m_ptp) / 100; \
								break; \
							case MDT_RATE: \
								rate->v += mlp->m_nPowerValue * CalcSkillParam(ch, ch, SPARAM_NONE, mp->m_ptp) / 100; \
								if( rate->v < -90 ) rate->v = -90; \
								break; \
							} \
						}
////////////////////
// class CAssistData

CAssistData::CAssistData(MSG_CHAR_TYPE spellertype, int spellerindex, int itemidx, const CSkillProto* proto, int level, int remain,
						 int remainCount,
						 bool bHit[MAX_SKILL_MAGIC])
						 : attr_rand(0)
{
	if (itemidx < 0)
		m_index = -1;
	else
		m_index = itemidx;

	m_proto = proto;
	m_level = level;
	m_remain = remain;
	memcpy(m_bHit, bHit, sizeof(bool) * MAX_SKILL_MAGIC);

	m_prev = NULL;
	m_next = NULL;

	m_spellerType = spellertype;
	m_spellerIndex = spellerindex;
#ifdef ASSIST_DECREASE_TIME_BUG_FIX
	m_prevtime = 0;
#endif
	m_remainCount = remainCount;
}

////////////////////
// class CAssistList

CAssistList::CAssistList()
{
	m_head = NULL;
	m_tail = NULL;
	m_max = 0;
	m_count = 0;
	m_abscount = 0;
}

CAssistList::~CAssistList()
{
	while (m_head)
	{
		CAssistData* p = m_head->m_next;
		delete m_head;
		m_head = p;
	}

	m_head = NULL;
	m_tail = NULL;
}

void CAssistList::Max(int n)
{
	m_max = n;
}

bool CAssistList::Add(CCharacter* spellchar, int itemidx, const CSkillProto* proto, int level, bool bHit[MAX_SKILL_MAGIC], int& remain,
					  int &remainCount,
					  int param, int nBlessAdd, int nBlessRate, int decreaseDBufRemain)
{

	

	if (proto && (proto->m_flag & SF_ABSTIME) && m_abscount >= MAX_ASSIST_ABS )
		return false;

	if (m_count >= m_max && !(proto->m_flag & SF_ABSTIME))
		return false;

	const CSkillLevelProto* levelproto = proto->Level(level);

	if (levelproto == NULL)
		return false;

	if (remain == -1 && decreaseDBufRemain > 0 && proto->m_flag == SF_NOTHELP)
	{
		remain = levelproto->m_durtime;
		remain = remain * (param / 100);
		remain += nBlessAdd
				  + remain * nBlessRate / SKILL_RATE_UNIT;
		remain = remain - remain * decreaseDBufRemain / 10000;
	}
	else if (remain == -1)
	{
		remain = levelproto->m_durtime;
		remain = remain * (param / 100);
		remain += nBlessAdd
				  + remain * nBlessRate / SKILL_RATE_UNIT;
	}
	else if ( itemidx>0 && remain > levelproto->m_durtime )
	{
		GAMELOG << init("ASSIST_HUGE_LUCKY ") << "ITEM :"
				<< itemidx << delim << remain << delim << levelproto->m_durtime << end;
		remain = levelproto->m_durtime;
	}
#ifdef BUGFIX_HUGE_SKILL_ABSTIME
	else if ( proto && (proto->m_flag & SF_ABSTIME) && (remain > levelproto->m_durtime * 2) )
	{
		GAMELOG << init("ASSIST_HUGE_ABSTIME ") << "ITEM :"
				<< itemidx << delim << remain << delim << levelproto->m_durtime << end;
		remain = levelproto->m_durtime * 2;
	}
#endif

#ifdef ENABLE_ROGUE_SKILL125_BRZ
	else
	{
		if(proto->m_index == 125)
		{
			remain = remain * (param / 100);
			remain += nBlessAdd
					  + remain * nBlessRate / SKILL_RATE_UNIT;
		}
	}
#endif // ENABLE_ROGUE_SKILL125_BRZ

	if (remainCount < 0)
	{
		remainCount = levelproto->m_useCount;
	}

	MSG_CHAR_TYPE spellertype = (spellchar) ? spellchar->m_type : MSG_CHAR_UNKNOWN;
	int spellerindex = (spellchar) ? spellchar->m_index : 0;
	CAssistData* p = new CAssistData(spellertype, spellerindex, itemidx, proto, level, remain,
									 remainCount,
									 bHit);

#ifdef ASSIST_DECREASE_TIME_BUG_FIX
	p->m_prevtime = gserver->getNowSecond();
#endif

	if (m_head == NULL)
	{
		// �ϳ��� ������
		m_head = m_tail = p;
	}
	else
	{
		m_tail->m_next = p;
		p->m_prev = m_tail;
		m_tail = p;
	}

	if (proto && (proto->m_flag & SF_ABSTIME) )
		m_abscount++;
	else
		m_count++;

	return true;
}

bool CAssistList::CanApply(const CSkillProto* proto, int level)
{
	const CSkillLevelProto* inlevelproto = proto->Level(level);
	if (inlevelproto == NULL)
		return false;

	CAssistData* data;
	const CSkillLevelProto* listlevelproto;
	const CMagicProto* inmagic;
	const CMagicProto* listmagic;
	int i, j;

	// ����Ʈ ����
	for (data = m_head; data; data = data->m_next)
	{
		listlevelproto = data->m_proto->Level(data->m_level);
		if (listlevelproto == NULL)
			continue ;

		// ����Ʈ�� ��ų ����
		for (i = 0; i < MAX_SKILL_MAGIC; i++)
		{
			listmagic = listlevelproto->m_magic[i];
			if (listmagic == NULL)
				continue ;

			// �Է� ��ų ����
			for (j = 0; j < MAX_SKILL_MAGIC; j++)
			{
				inmagic = inlevelproto->m_magic[j];
				if (inmagic == NULL)
					continue ;

				// ��
				if (inmagic->m_index != listmagic->m_index)
					continue ;
				if( (inmagic->m_index == 518 || inmagic->m_index == 519 ) && gserver->isActiveEvent(A_EVENT_HALLOWEEN))
					continue;

				if( proto->m_index == 1756 ||  proto->m_index == 1757 )
					continue;

				if (inlevelproto->m_magicLevel[j] < listlevelproto->m_magicLevel[i])
					return false;
			}
		}
	}

	return true;
}

// 060227 : bs : ����ð� ���� �߰�
void CAssistList::DelDuplicate(const CSkillProto* proto, int level, bool bSend, CCharacter* ch, bool bNoCancelType)
{
	const CSkillLevelProto* inlevelproto = proto->Level(level);
	if (inlevelproto == NULL)
		return ;

	CAssistData* data;
	CAssistData* dataNext;
	const CSkillLevelProto* listlevelproto;
	const CMagicProto* inmagic;
	const CMagicProto* listmagic;
	int i, j;
	bool bDelete;
	bool statusUpdate = true;

	// ����Ʈ ����
	dataNext = m_head;
	while ((data = dataNext))
	{
		dataNext = data->m_next;

		listlevelproto = data->m_proto->Level(data->m_level);
		if (listlevelproto == NULL)
			continue ;

		bDelete = false;

		// ����Ʈ�� ��ų ����
		for (i = 0; i < MAX_SKILL_MAGIC && !bDelete; i++)
		{
			listmagic = listlevelproto->m_magic[i];
			if (listmagic == NULL)
				continue ;

			// �Է� ��ų ����
			for (j = 0; j < MAX_SKILL_MAGIC; j++)
			{
				inmagic = inlevelproto->m_magic[j];
				if (inmagic == NULL)
					continue ;

				// ��
				if (inmagic->m_index != listmagic->m_index)
					continue ;

				if (inmagic->m_type == MT_STAT && inmagic->m_subtype == MST_STAT_MAXHP || inmagic->m_subtype == MST_STAT_MAXMP)
				{
					statusUpdate = false;
				}

				if ( proto->m_index == 1756 || proto->m_index == 1757 )
				{
					bDelete = true;
					break;
				}

				if (listlevelproto->m_magicLevel[i] <= inlevelproto->m_magicLevel[j])
				{
					bDelete = true;
					break;
				}
			}
		}

		if (!bDelete)
			continue ;

		DelAssist(data, bSend, ch, bNoCancelType, statusUpdate);
	}
}

bool CAssistList::DecreaseTime(CCharacter* ch, LONGLONG* changestate)
{
	bool ret = false;

	CAssistData* data;
	CAssistData* dataNext = m_head;

	const CSkillProto* sp;
	const CSkillLevelProto* slp;
	const CMagicProto* mp;
	const CMagicLevelProto* mlp;
	bool bCancel;
	int i;

	while ((data = dataNext))
	{
		dataNext = data->m_next;

		bool bSkip = false;
		// �������� �ð� ���� ����
		switch (data->m_index)
		{
		case 882:
		case 883:
		case 884:
		case 885:
		case 2875:
		case 2855:
		//[100823: selo] ���� ������
		case 6094:
		case 6095:
		case 6096:
		case 7344:		// �� ����ġ ������
		case 7345:
		case 7346:		// ���̸����� ����
#ifdef REFORM_PK_PENALTY_201108 // ���� ��ġ ��� �������� �ð� ���� ����.
		case 7474:	// ���� ��ġ ��� ������
		case 7475:	// ���� ��ġ ��� ������
		case 7476:	// ���� ��ġ ��� ������
#endif
		case 10804:	
		case 12057:
		case 12195:
		case 12429:
		case 20590:
		case 20591:
			bSkip = true;
			break;
		}

		switch (data->m_proto->m_index)
		{
		case 1756:
		case 1757:
			bSkip = true;
			break;
		}

		if(data->m_proto->m_flag & SF_COMBO)		// �ð����Ҿ��½�ų
			continue;

		// dethunter12 siege blessings (1872,1873)
		if ( data->m_proto->m_index == 516 || data->m_proto->m_index == 2059)
		{
			// ���� 100 ������ ���
			#ifdef PHOENIX_BUFF_LEVEL_REQUIRED
			if( ch->m_level < 100 )
			#endif
				bSkip = true;
		}

		if (bSkip)
			continue ;

		// �Ź� ����Ǵ� ���� �˻�
		sp = data->m_proto;
		if (!sp)
			continue;
		slp = sp->Level(data->m_level);
		if (!slp)
			continue;
		i = 0;
		bCancel = false;
		while (i < MAX_SKILL_MAGIC && !bCancel)
		{
			mp = slp->m_magic[i];
			if (mp)
			{
				mlp = mp->Level(slp->m_magicLevel[i]);
				if (mlp)
				{
					int nPowerValue = mlp->m_nPowerValue * CalcSkillParam(ch, ch, SPARAM_NONE, mp->m_ptp) / 100;

					switch (slp->m_magic[i]->m_type)
					{
					case MT_ASSIST:
						{
							switch (slp->m_magic[i]->m_subtype)
							{
							// FREEZE ���¿� �ɸ��� ���� ����
							case MST_ASSIST_FREEZE:
								{
									// CDratanCastle * pCastle = CDratanCastle::CreateInstance();
									// if (IS_PC(ch) && TO_PC(ch) != NULL)
									// {
									// 	pCastle->CheckRespond(TO_PC(ch));
									// }
								}
								break;
							// Dot Damage ������ �ʴ� �ð��� ������
							case MST_ASSIST_POISON:
							case MST_ASSIST_BLOOD:
							case MST_ASSIST_DISEASE:
							case MST_ASSIST_CURSE:
							case MST_ASSIST_HP_DOT:
								{
									if (ch->m_hp > 1)
									{
										switch (mp->m_damagetype)
										{
										case MDT_RATE:
											{
												// yhj  090305   ������ ������� �ɾ��� ��� �ð��� �������� 1/5 ��..
												switch( ch->m_type )
												{
												case MSG_CHAR_PC:
													ch->m_hp -= (int)ch->m_maxHP * ( (nPowerValue / SKILL_RATE_UNIT / 20) ) ;
													break;

												// yhj  090305   ������ ������ ���� ������� �ɾ��� ��� �ʴ� ������ �״����..
												case MSG_CHAR_NPC:
												case MSG_CHAR_PET:
												case MSG_CHAR_ELEMENTAL:
												case MSG_CHAR_APET:
												default:
													{
#ifdef TLD_EVENT_SONG
														int minusHp = (int)ch->m_maxHP * nPowerValue / SKILL_RATE_UNIT;

														if (ch->m_type == MSG_CHAR_NPC)
														{
															CNPC* pNpc = TO_NPC(ch);
															if (pNpc->m_proto->m_index == 1622 || pNpc->m_proto->m_index == 1623)
															{
																minusHp = 1;
															}
														}

														ch->m_hp -= minusHp;
#else
														ch->m_hp -= (int)ch->m_maxHP * nPowerValue / SKILL_RATE_UNIT;
#endif
													}
													break;
												}
											}
											break;

										default:
											{
												switch( ch->m_type )
												{
												case MSG_CHAR_PC:
													ch->m_hp -=  (int)( nPowerValue/20 );
													break;

												// yhj  090305   ������ ������ ���� ������� �ɾ��� ��� �ʴ� ������ �״����..
												case MSG_CHAR_NPC:
												case MSG_CHAR_PET:
												case MSG_CHAR_ELEMENTAL:
												case MSG_CHAR_APET:
												default:
													{
#ifdef TLD_EVENT_SONG

														int minusHp = nPowerValue;

														if (ch->m_type == MSG_CHAR_NPC)
														{
															CNPC* pNpc = TO_NPC(ch);
															if (pNpc->m_proto->m_index == 1622 || pNpc->m_proto->m_index == 1623)
															{
																minusHp = 1;
															}
														}

														ch->m_hp -=  minusHp;
#else
														ch->m_hp -=  nPowerValue;
#endif
													}
													break;
												}
											}
											break;
										}

										if (ch->m_hp <= 0)
										{
											if(sp->m_index == ROYAL_RUMBLE_DEBUFF_SKILL)
											{
												ch->m_hp = 0;
												if(IS_PC(ch))
												{
													CPC* evoPC = NULL;
													evoPC = TO_PC(ch);
													if(evoPC)
													{
														if(evoPC->m_evocationIndex != EVOCATION_NONE)
															evoPC->Unevocation();
														// ���� �ð� �ʱ�ȭ
														evoPC->m_pulseEvocation[0] = 0;
														evoPC->m_pulseEvocation[1] = 0;
													}
													GAMELOG << init("ROYAL RUMBLE DEAD PC", TO_PC(ch)) << "SKILL INDEX" << delim << sp->m_index << end;
													CWaitPlayer* p = NULL;
													p = gserver->m_RoyalRumble.m_WaitPlayerList.GetNode(TO_PC(ch)->m_index);
													if(p)
													{
														int leveltype = p->GetLevelType();
														int leftcount = 0;
														CWaitPlayer* player = NULL;
														CWaitPlayer* playern = NULL;
														playern = gserver->m_RoyalRumble.m_WaitPlayerList.GetHead();
														while((player = playern))
														{
															playern = playern->GetNext();
															if( player->GetLevelType() == leveltype &&
																	player->GetCheckIn() == true )
																leftcount++;
														}
														leftcount -= 2;
														{
															CNetMsg::SP rmsg(new CNetMsg);
															RoyalRumbleLeftCount(rmsg, leftcount);

															CNetMsg::SP killmsg(new CNetMsg);
															RoyalRumbleKillPlayer(killmsg, TO_PC(ch), TO_PC(ch));
															switch(leveltype)
															{
															case LEVEL_TYPE_ROOKIE:
																{
																	gserver->m_RoyalRumble.m_pRookieArea->SendToAllClient(rmsg);
																	gserver->m_RoyalRumble.m_pRookieArea->SendToAllClient(killmsg);
																}
																break;
															case LEVEL_TYPE_SENIOR:
																{
																	gserver->m_RoyalRumble.m_pSeniorArea->SendToAllClient(rmsg);
																	gserver->m_RoyalRumble.m_pSeniorArea->SendToAllClient(killmsg);
																}
																break;
															case LEVEL_TYPE_MASTER:
																{
																	gserver->m_RoyalRumble.m_pMasterArea->SendToAllClient(rmsg);
																	gserver->m_RoyalRumble.m_pMasterArea->SendToAllClient(killmsg);
																}
																break;
															default:
																break;
															}
														}
													}
													gserver->m_RoyalRumble.m_WaitPlayerList.DelNode(TO_PC(ch)->m_index);
												}
											}
											else
												ch->m_hp = 1;
										}

										switch (slp->m_magic[i]->m_subtype)
										{
										case MST_ASSIST_POISON:
											*changestate |= AST_POISON;
											break;
										case MST_ASSIST_BLOOD:
											*changestate |= AST_BLOOD;
											break;
										case MST_ASSIST_DISEASE:
											*changestate |= AST_DISEASE;
											break;
										case MST_ASSIST_CURSE:
											*changestate |= AST_CURSE;
											break;
										case MST_ASSIST_HP_DOT:
											*changestate |= AST_HP_DOT;
											break;
										default:
											break;
										}
									}
								}
								break;
							/*
														case MST_ASSIST_POISON:
															if (ch->m_hp > 1)
															{
																switch (mp->m_damagetype)
																{
																case MDT_RATE:
																	ch->m_hp -= (int)ch->m_maxHP * nPowerValue / SKILL_RATE_UNIT;
																	break;
																default:
																	ch->m_hp -=  nPowerValue;
																	break;
																}
																if (ch->m_hp <= 0)
																	ch->m_hp = 1;
																*changestate |= AST_POISON;
															}
															break;

														case MST_ASSIST_BLOOD:
															if (ch->m_hp > 1)
															{
																switch (mp->m_damagetype)
																{
																case MDT_RATE:
																	ch->m_hp -= (int)ch->m_maxHP * nPowerValue / SKILL_RATE_UNIT;
																	break;
																default:
																	ch->m_hp -=  nPowerValue;
																	break;
																}
																if (ch->m_hp <= 0)
																	ch->m_hp = 1;
																*changestate |= AST_BLOOD;
															}
															break;
							*/
							case MST_ASSIST_HP:
								
								if (DEAD(ch))
									break;

								switch (mp->m_damagetype)
								{
								case MDT_RATE:
									ch->m_hp += (int)ch->m_maxHP * nPowerValue / SKILL_RATE_UNIT;
									break;
								default:
									ch->m_hp +=  nPowerValue;
									break;
								}
								if (ch->m_hp > ch->m_maxHP)
									ch->m_hp = ch->m_maxHP;
								if (ch->m_hp <= 0)
									ch->m_hp = 1;
								*changestate |= AST_HP;
								break;

							case MST_ASSIST_MP:
								switch (mp->m_damagetype)
								{
								case MDT_RATE:
									ch->m_mp += (int)ch->m_maxMP * nPowerValue / SKILL_RATE_UNIT;
									break;
								default:
									ch->m_mp +=  nPowerValue;
									break;
								}
								if (ch->m_mp > ch->m_maxMP)
									ch->m_mp = ch->m_maxMP;
								if (ch->m_mp < 0)
									ch->m_mp = 0;
								*changestate |= AST_MP;
								break;

							case MST_ASSIST_HP_CANCEL:

								if (DEAD(ch))
									break;

								switch (mp->m_damagetype)
								{
								case MDT_RATE:
									ch->m_hp += (int)ch->m_maxHP * nPowerValue / SKILL_RATE_UNIT;
									break;
								default:
									ch->m_hp +=  nPowerValue;
									break;
								}
								if (ch->m_hp > ch->m_maxHP)
								{
									ch->m_hp = ch->m_maxHP;
									bCancel = true;
								}
								if (ch->m_hp <= 0)
								{
									ch->m_hp = 1;
									bCancel = true;
								}
								*changestate |= AST_HP_CANCEL;
								break;

							case MST_ASSIST_MP_CANCEL:
								switch (mp->m_damagetype)
								{
								case MDT_RATE:
									ch->m_mp += (int)ch->m_maxMP * nPowerValue / SKILL_RATE_UNIT;
									break;
								default:
									ch->m_mp +=  nPowerValue;
									break;
								}
								if (ch->m_mp > ch->m_maxMP)
								{
									ch->m_mp = ch->m_maxMP;
									bCancel = true;
								}
								if (ch->m_mp < 0)
								{
									ch->m_mp = 0;
									bCancel = true;
								}
								*changestate |= AST_MP_CANCEL;
								break;
							case MST_ASSIST_INVINCIBILITY:
								if ( IS_PC(ch) )
								{
									CPC*  pPC =	 TO_PC(ch);
									pPC->SetPlayerState( PLAYER_STATE_INVINCIBILITY );
								}
								break;
							}
						}
					default:
						break;
					}
				}
			}
			i++;
		}
#ifdef ASSIST_DECREASE_TIME_BUG_FIX
		data->m_remain -= ((gserver->getNowSecond() - data->m_prevtime) * 10);
		data->m_prevtime = gserver->getNowSecond();
#else
		data->m_remain -= PULSE_ASSIST_CHECK;
#endif
		if( IS_NPC(ch) && TO_NPC(ch)->GetOwner() &&
				( TO_NPC(ch)->Check_MobFlag(STATE_MONSTER_TOTEM_BUFF) || TO_NPC(ch)->Check_MobFlag(STATE_MONSTER_TOTEM_ATTK)) )
		{
			if( data->m_proto->Level(1)->m_magic[0] && data->m_proto->Level(1)->m_magic[0]->m_type == MT_ASSIST &&
					( data->m_proto->Level(1)->m_magic[0]->m_subtype == MST_ASSIST_SOUL_TOTEM_BUFF
					  || data->m_proto->Level(1)->m_magic[0]->m_subtype == MST_ASSIST_SOUL_TOTEM_ATTK ) )
			{
				ch->m_hp = data->m_remain * ch->m_maxHP / data->m_proto->Level(1)->m_durtime ;
				if( ch->m_hp < 0 )
					ch->m_hp = 0;
			}
		}

		if (data->m_remain <= 0 || bCancel
				|| (slp->m_useCount > 0 && data->m_remainCount <= 0)
		   )
		{
			// 경험치 부활 숙련도 주문서일 경우 버프를 삭제하지 않는다.
			if( data->m_index == 844
					|| data->m_index == 845
					|| data->m_index == 846		// ��Ȱ �ֹ���
					|| data->m_index == 7056	// �̺�Ʈ ��Ȱ �ֹ���
					|| data->m_index == 2667	// �ʺ��ڿ� ��Ȱ �ֹ���
					|| data->m_index == 2371
					|| data->m_index == ONE_PERIOD_ITEM
					|| data->m_index == SEVEN_PERIOD_ITEM
					|| data->m_index == THIRTY_PERIOD_ITEM
					|| data->m_index == 2610
					|| data->m_index == 4940
					|| data->m_index == 4941
					|| data->m_index == 4942
					|| data->m_index == 3218
			  )
			{
				data->m_remain = 0;
			}
			else
			{
				int old_skillIndex;
				// �ð��� ���� ũ�������� ��ų ���� ( SkillIndex : 490 )
				// NPC�� ��ȯ �Ѵ�
				old_skillIndex = data->m_proto->m_index;
				if( old_skillIndex == 491 ) //pwesty changed to sunrise skill was 490
				{
					if( gserver->isActiveEvent( A_EVENT_XMAS) )
					{
						if( !ch->m_pZone->IsPersonalDungeon() 
							&& !(ch->GetMapAttr() & MATT_FREEPKZONE) && !(ch->GetMapAttr() & MATT_PEACE)
							&& !ch->m_pZone->IsGuildRoom() && !ch->m_pZone->IsOXQuizRoom() )
						{
							CNPC* pBoxNpc = gserver->m_npcProtoList.Create( 483/*ũ�������� ���� ����*/, NULL );
							if ( pBoxNpc )
							{
								GET_X(pBoxNpc) = GET_X(ch) + (GetRandom(0, 1) ? -1 : 1) * GetRandom(20, 50) / 10.0f;
								GET_Z(pBoxNpc) = GET_Z(ch) + (GetRandom(0, 1) ? -1 : 1) * GetRandom(20, 50) / 10.0f;
								GET_YLAYER(pBoxNpc) = GET_YLAYER(ch);
								GET_R(pBoxNpc) = GetRandom(0, (int) (PI_2 * 10000)) / 10000;

								if (ch->m_pArea->GetAttr(GET_YLAYER(pBoxNpc), GET_X(pBoxNpc), GET_Z(pBoxNpc)) & MATT_WALKABLE )
								{
									pBoxNpc->m_regenX = GET_X(pBoxNpc);
									pBoxNpc->m_regenY = GET_YLAYER(pBoxNpc);
									pBoxNpc->m_regenZ = GET_Z(pBoxNpc);

									pBoxNpc->m_regenTimeXmas2007 = gserver->m_pulse;

									int cx, cz;
									ch->m_pArea->AddNPC(pBoxNpc);
									ch->m_pArea->PointToCellNum(GET_X(pBoxNpc), GET_Z(pBoxNpc), &cx, &cz);
									ch->m_pArea->CharToCell(pBoxNpc, GET_YLAYER(pBoxNpc), cx, cz);

									{
										CNetMsg::SP rmsg(new CNetMsg);
										AppearMsg(rmsg, pBoxNpc, true);
										ch->m_pArea->SendToCell(rmsg, GET_YLAYER(pBoxNpc), cx, cz);
									}

									GAMELOG << init(" EVENT XMAS XMAS BOX REGEN " ) << ch->m_name << end;	// ��ų ���� ����
								}
							}
						}
					}
				}

				old_skillIndex = data->m_proto->m_index;

				if( old_skillIndex == 1060 )		// �⼮��� ������ �⼮ üũ subtype 2
				{
					//�⼮������ �����ٸ� �⼮ �������ֱ�
					CPC* pc = TO_PC(ch);
					pc->m_attendanceManager.finish();
				}

				bool	bInfinite = false;
				int		old_skillLevel = data->m_level;
				int		old_itemIndex = data->m_index;

				if( data->m_proto->m_flag & SF_INFINITE )
				{
					bInfinite = true;
				}

				i = 0;
				while (i < MAX_SKILL_MAGIC )
				{
					if( !slp->m_magic[i] )
						break;

					int nPowerValue = -1;

					mp = slp->m_magic[i];
					if (mp)
					{
						mlp = mp->Level(slp->m_magicLevel[i]);
						if (mlp)
						{
							nPowerValue = mlp->m_nPowerValue * CalcSkillParam(ch, ch, SPARAM_NONE, mp->m_ptp) / 100;
						}
					}

					if( nPowerValue < 1 )
					{
						if ( IS_PC(ch) && TO_PC(ch)->IsSetPlayerState(PLAYER_STATE_INVINCIBILITY))
						{
							CPC*  pPC =	 TO_PC(ch);
							pPC->ResetPlayerState( PLAYER_STATE_INVINCIBILITY );
						}
						break;
					}

					if(slp->m_magic[i]->m_type == MT_OTHER )
					{
						switch (slp->m_magic[i]->m_subtype )
						{
						case MST_OTHER_ITEMDROP:
							{
								if( GetRandom(0,10000) < mlp->m_nHitrateValue )
								{
									CItem* pdropItem = gserver->m_itemProtoList.CreateItem( nPowerValue , -1, 0, 0, 1 );
									if( pdropItem && ch )
									{
										pdropItem->m_pos = CPos(GET_X(ch), GET_Z(ch), ch->m_pos.m_h, GET_R(ch), GET_YLAYER(ch));

										// ��ǥ ����
										if (GET_X(pdropItem) < 0)		GET_X(pdropItem) = 0;
										if (GET_Z(pdropItem) < 0)		GET_Z(pdropItem) = 0;
										// 050207 - bs : ���� ������� ������� 0�� ������ ����
										if (GET_X(pdropItem) >= ch->m_pArea->m_zone->m_attrMap[0].m_size[0])
											GET_X(pdropItem) = ch->m_pArea->m_zone->m_attrMap[0].m_size[0];
										if (GET_Z(pdropItem) >= ch->m_pArea->m_zone->m_attrMap[0].m_size[1])
											GET_Z(pdropItem) = ch->m_pArea->m_zone->m_attrMap[0].m_size[1];

										// ���� �ֱ�
										pdropItem->m_pArea = ch->m_pArea;
										pdropItem->m_groundPulse = gserver->m_pulse;

										int cx, cz;
										ch->m_pArea->PointToCellNum(GET_X(pdropItem), GET_Z(pdropItem), &cx, &cz);
										ch->m_pArea->ItemToCell(pdropItem, GET_YLAYER(pdropItem), cx, cz);

										{
											CNetMsg::SP rmsg(new CNetMsg);
											ItemDropMsg( rmsg, ch, pdropItem );
											pdropItem->m_pArea->SendToCell( rmsg, GET_YLAYER( pdropItem ), pdropItem->m_cellX, pdropItem->m_cellZ );
										}
									}
								}
							}
							break;
						case MST_OTHER_SKILL:
							{
								CSkill *pSkill = gserver->m_skillProtoList.Create( nPowerValue , mlp->m_nHitrateValue );
								if( pSkill )
								{
									bool bApply = false ;
									ApplySkill( ch, ch, pSkill, -1 , bApply );
									if(bApply == true)
										return ret;
								}
							}
							break;
						case MST_OTHER_INSTANTDEATH:
							{
								ch->m_hp = 0;
							}
							break;
#ifdef REFORM_PK_PENALTY_201108
						case MST_OTHER_PK_DISPOSITION:
							switch( slp->m_magic[i]->m_damagetype )
							{
							case MDT_ADDITION:
								ch->m_assist.m_avAddition.pkDispositionPointValue = 0;
								break;
							case MDT_RATE:
								ch->m_assist.m_avRate.pkDispositionPointValue = 0;
								break;
							}
							break;
#endif // REFORM_PK_PENALTY_201108
						}
					}
					else if(slp->m_magic[i]->m_type == MT_ATTRIBUTE && slp->m_magic[i]->m_subtype == AT_RANDOM)
					{
						if(slp->m_magic[i]->m_damagetype == MDT_ATTACK)
						{
							ch->m_assist.m_avAddition.attratt_item = 0;

							if(IS_PC(ch) == true)
							{
								CPC* pc = TO_PC(ch);
								pc->m_bChangeStatus = true;
							}
							else if(IS_NPC(ch) == true)
							{
								CNPC* npc = TO_NPC(ch);
								unsigned char attr;

								if(ch->m_assist.getAttrAtt() > 0)
									attr = ch->m_assist.getAttrAtt();
								else
									attr = npc->m_proto->m_attratt;
								
								CNetMsg::SP rmsg(new CNetMsg);
								UpdateClient::AttrNpcStateMsg(rmsg, MDT_ATTACK, attr, ch->m_index);
								ch->m_pArea->SendToCell(rmsg, ch);
							}
						}
						else if(slp->m_magic[i]->m_damagetype == MDT_DEFENCE)
						{
							ch->m_assist.m_avAddition.attrdef_item = 0;

							if(IS_PC(ch) == true)
							{
								CPC* pc = TO_PC(ch);
								pc->m_bChangeStatus = true;
							}
							else if(IS_NPC(ch) == true)
							{
								CNPC* npc = TO_NPC(ch);
								unsigned char attr;

								if(ch->m_assist.getAttrDef() > 0)
									attr = ch->m_assist.getAttrDef();
								else
									attr = npc->m_proto->m_attrdef;

								CNetMsg::SP rmsg(new CNetMsg);
								UpdateClient::AttrNpcStateMsg(rmsg, MDT_DEFENCE, attr, ch->m_index);
								ch->m_pArea->SendToCell(rmsg, ch);
							}
						}
					}
					i++;
				}

				if(data->m_proto->m_index == 1759)
				{
					CPC* pc = TO_PC(ch);
					pc->m_gpsManager.deleteTarget();
				}

				DelAssist(data, true, ch, true);
				ret = true;

				if( bInfinite )
				{
					CSkill *pSkill = gserver->m_skillProtoList.Create( old_skillIndex , old_skillLevel );
					if( pSkill )
					{
						bool bApply = false ;
						ApplySkill( ch, ch, pSkill, old_itemIndex , bApply );
						if(bApply == true)
							return ret;
					}
				}

				if( old_skillIndex == 491 && gserver->isActiveEvent( A_EVENT_XMAS)  ) //pwesty changed to sunrise skill was 490
				{
					CSkill *pSkill = gserver->m_skillProtoList.Create( old_skillIndex , 1 );
					if( pSkill )
					{
						bool bApply = false ;
						ApplySkill( ch, ch, pSkill, -1 , bApply );
						if( !bApply )
						{
							GAMELOG << init(" EVENT XMAS SKILL FAILED " ) << ch->m_name << end;	// ��ų ���� ����
						}
					}
				}				
			}
			//�ð��� ������ ��� ������
			if( sp->m_index == 1751 )
			{
				if(IS_NPC(ch))
				{
					CNPC* npc = TO_NPC(ch);
					npc->m_ctTime = IMMUN_SKILL_MCT_TIME;
					gserver->m_npc_ctTime.insert(std::pair<int, CNPC*>(npc->m_index, npc));
				}
			}

			if( sp->m_index == PVP_PROTECT_SKILL_INDEX )
			{
				CPC* pc = TO_PC(ch);
				CNetMsg::SP rmsg(new CNetMsg);
				SysMsg(rmsg, MSG_SYS_PVP_PROTECT_ITEM_END);
				SEND_Q(rmsg, pc->m_desc);
			}
		}
	}
	return ret;
}

void CAssistList::Apply(CCharacter* ch, ASSISTVALUE* addition, ASSISTVALUE* rate, LONGLONG* state)
{
	CAssistData* p;
	const CSkillProto* sp;
	const CSkillLevelProto* slp;
	const CMagicProto* mp;
	const CMagicLevelProto* mlp;
	int i;

	for (p = m_head; p; p = p->m_next)
	{
		sp = p->m_proto;
		if (sp == NULL)
			continue;
		slp = sp->Level(p->m_level);
		if (slp == NULL)
			continue;

		// TODO : �ϵ��ڵ���

		bool bSkip = false;

		// ������ �ε��� �ϵ� �ڵ�
		switch (p->m_index)
		{
		case 2388:
			addition->hcExpPlus_2388 += 100;
			bSkip = true;
			break;	// Poem book
		case 2389:
			addition->hcExpPlus_2389 += 50;
			bSkip = true;
			break;	// Blessing of Mother( Blue )
		case 2390:
			addition->hcSPPlus_2390 += 100;
			bSkip = true;
			break;	// Blessing of Mother( Yellow )
		case 2391:
			addition->hcDropPlus_2391 = true;
			bSkip = true;
			break;	// Blessing of Mother( Red )
		case 671:
		case 7271:
			addition->hcDeathExpPlus = 1;
			bSkip = true;
			break ;		// �ϱ� ������ ����
		case 672:
		case 7272:
			addition->hcDeathExpPlus = 2;
			bSkip = true;
			break ;		// �߱� ������ ����
		case 673:
		case 7273:
			addition->hcDeathExpPlus = 3;
			bSkip = true;
			break ;		// ��� ������ ����
		case 674:
			addition->hcDeathSPPlus = true;
			bSkip = true;
			break ;		// ����� ����
		case 508:
			addition->hcExpPlus = true;
			bSkip = true;
			break ;		// ����
		case 509:
			addition->hcSPPlus = true;
			bSkip = true;
			break ;		// �����α�
		case 836:
			addition->hcExpPlus_836 = true;
			bSkip = true;
			break ;		// ����
		case 5082:
		case 837:
			addition->hcSPPlus_837 = true;
			bSkip = true;
			break ;		// ����
		case 838:
			addition->hcDropPlus_838 = true;
			bSkip = true;
			break ;		// �ڵ�
		case 884:
			addition->hcSepDrop = true;
			bSkip = true;
			break ;
		case 882:
		case 20590: //bound boosters
			addition->hcSepExp = true;
			bSkip = true;
			break ;
		case 883:
		case 20591: //bound boosters
			addition->hcSepSP = true;
			bSkip = true;
			break ;
		case 885:
			addition->hcSepNas = true;
			bSkip = true;
			break;
		// >> [100823: selo] ���� ������
		case 6094:
		
			addition->hcSepExp_Cash = true;
			bSkip = true;
			break;
		case 12057:
			addition->hcSepExp_Prem = true;
			bSkip = true;
			break;
		case 6095:
		
			addition->hcSepSP_Cash = true;
			bSkip = true;
			break;
		case 6096:
			addition->hcSepDrop_Cash = true;
			bSkip = true;
			break;
		case 12429:
			addition->hcSepDropPrem = true;
			bSkip = true;
			break;
		// << [100823: selo] ���� ������
		case 971:		// �����ǽ�ũ��
		case 2499:		// �Ϻ� �����ǽ�ũ�� ���纻
			addition->hcScrollExp = true;
			bSkip = true;
			break;
		case 5081:
			addition->hcScrollDrop_5081 = true;
			bSkip = true;
			break;	// ������ ��ũ��
		case 5080: // 5080������ ��ũ�Ѱ� ������ ���� ����Ѵ�.
		case 972:
		case 11330:
			addition->hcScrollDrop = true;
			bSkip = true;
			break;		// ����ǽ�ũ��
		case 11340:
			addition->hcScrollDrop_11340 = true;
			bSkip = true;
			break;
		case 12427:
			addition->hcScrollDropCube = true;
			bSkip = true;
			break;
		case 973:
			addition->hcScrollSP = true;
			bSkip = true;
			break;		// ����ǽ�ũ��

		case 792:
			addition->hcAttackTower = true;
			bSkip = true;
			break;		// ���� ���ݽ� ����� 2��

		case 1628:
			addition->hcSPPlusPer100 += 50;
			bSkip = true;
			break;		// ������ ����
		case 1629:
			addition->hcDropPlusPer100 += 100;
			bSkip = true;
			break;		// ������ �ڵ�
		case 1627:
		case 2494:		// �Ϻ� ������ ���� ���纻
			addition->hcExpPlusPer100 += 20;
			bSkip = true;
			break;		// ������ ����
		case 1630:
			addition->hcExpPlusPer100 += 20;
			bSkip = true;
			break;		// �ູ�� ����
		case 1975:		// ����ũ
		case 2495:		// �Ϻ� ����ũ ���纻
		case 5084:
			addition->hcExpPlus_1975 = 30;
			bSkip = true;
			break ;		// ����ũ : 2006 ũ��������
		case 1976:		// �����
		case 2498:		// �Ϻ� ����� ���纻
		case 5083:
			addition->hcExpPlus_1976 = 100;
			bSkip = true;
			break;		// ����� : 2006 ũ��������

		case 2582:
		case 2583: // �Ʒ� �ֹ����� ������ 15% ���.
		case 2139:
			addition->hcSPPlusPer100 += 15;
			bSkip = true;
			break;		// �Ʒ��ֹ���
		case 2140:
			addition->hcSPPlusPer100 += 50;
			bSkip = true;
			break;		// �÷�Ƽ�� �Ʒ��ֹ���
		case 4937:
			addition->hcSPPlusPer100 += 50;
			bSkip = true;
			break;		// (�̺�Ʈ��)�÷�Ƽ�� �Ʒ��ֹ���
		case 2141:
		case 11329: //dethunter12 lsb 1 Day
			addition->hcDropPlus_2141 = true;
			bSkip = true;
			break;		// ��� �ֹ���
		case 11339:
			addition->hcDropPlus_11339 = true;
			bSkip = true;
			break;

#ifdef PLATINUM_SKILL_POTION_ITEM
		case 2453:
			addition->hcSPPlusPer100 += 200;
			bSkip = true;
			break;		// �÷�Ƽ�� ���� ����
#endif // PLATINUM_SKILL_POTION_ITEM
		case 2659:
			addition->hcSPPlusPer100 += 200;
			bSkip = true;
			break;		// �ʺ��ڿ� �÷�Ƽ�� ������ ����
		case 5088:
			addition->hcSPPlusPer100 += 200;
			bSkip = true;
			break;		// �÷�Ƽ�� ������ ���� (LV1)
		case 5089:
			addition->hcSPPlusPer100 += 200;
			bSkip = true;
			break;		// �÷�Ƽ�� ������ ���� (LV31)
		case 5090:
			addition->hcSPPlusPer100 += 200;
			bSkip = true;
			break;		// �÷�Ƽ�� ������ ���� (LV61)
		case 6595:
			addition->hcSPPlusPer100 += 200;
			bSkip = true;
			break;
		case 7611:
			addition->hcSPPlusPer100 += 200;
			bSkip = true;
			break;		// [�̺�Ʈ]�÷�Ƽ�� ������ ����
#ifdef SKILL_POTION_ITEM
		case 2452:
			addition->hcSPPlusPer100 += 100;
			bSkip = true;
			break;		// ������ ����
#endif // SKILL_POTION_ITEM
		case 2358:
			addition->hcCashPetExpUp_2358 = true;
			bSkip = true;
			break;		// �� ������ ����
		case 2359:
			addition->hcCashPetExpUp_2359 = true;
			bSkip = true;
			break;
		case 12077:
			addition->hcCashPetExpUp_12077 = true;
			bSkip = true;
			break;		// �÷�Ƽ�� �� ������ ����
		case 2356:
		case 2841:
		case 6596:
		case 11331:
			addition->hcMPSteelPotion = true;
			bSkip = true;
			break;			// �Ϲ� ���ݽ� 30%�� Max MP �� 10% ���� �ǰ� ���� MP ����
		case 2357:
		case 2842:
		case 6597:
		case 11332:
			addition->hcHPSteelPotion = true;
			bSkip = true;
			break;			// �Ϲ� ���ݽ� 30%�� Ma
		case 11333:
		case 21021:
		case 20640:			//pwesty
			addition->hcHPSteelPotion = true;
			addition->hcMPSteelPotion = true;
			bSkip = true;
			break;
		case 2410:
		case 2354:
			addition->hcExpSPPlus_2354	= true;
			bSkip = true;
			break;		// �ٹ��� ������(����� ����): 50% EXP + 50% SP
		case 2853:
			addition->hcAttackBerserker = true;
			bSkip = true;
			break;		// 10% Ȯ���� 2�� ������
		case 12052:
		    addition->hcAttackBerserkerPrem = true;
			break;
		case 2870:
			addition->hcExplimitPlus	= 50;
			bSkip = true;
			break;		// 50% ����ġ ���� 50% ����
		case 2855:
			addition->hcPlatinumDrop	= true;
			bSkip = true;
			break;		// ����� 20�� ����
		case 2856:
			addition->hcPlatinumScroll	= true;
			bSkip = true;
			break;
		case 7054:
			addition->hcCashPetExpUp_2359 = true;
			bSkip = true;
			break;	// [�̺�Ʈ] �÷�Ƽ�� �� ������ ����
		case 7344:
			addition->hcPetExpBoost = true;
			bSkip = true;
			break;	// �� ����ġ ������
		case 7345:
		case 7346:
			addition->hcIrisFervor = true;
			bSkip = true;
			break;	// ���̸����� ����
		case 12558:
			addition->hcFactionUP = true;
			bSkip = true;
			//dethunter12
			break;
		}

		// 060227 : bs : ��ų �ε��� �ϵ� �ڵ�
		switch (p->m_proto->m_index)
		{
		case 348:
		case 349:
			mp = slp->m_magic[0];											// 060227 : bs : ��������� ����ġ ���
			if (mp)
			{
				mlp = mp->Level(slp->m_magicLevel[0]);
				if (mlp)
				{
					if (rate->hcCashExpUp < mlp->m_nPowerValue)
						rate->hcCashExpUp = mlp->m_nPowerValue;
				}
			}
			bSkip = true;
			break;

		case 350:
			mp = slp->m_magic[0];											// 060227 : bs : ��������� HP Ȯ��
			if (mp)
			{
				mlp = mp->Level(slp->m_magicLevel[0]);
				if (mlp)
				{
					if (rate->hcCashMaxHPUp < mlp->m_nPowerValue)
						rate->hcCashMaxHPUp = mlp->m_nPowerValue;
				}
			}
			bSkip = true;
			break;

		case 351:
			mp = slp->m_magic[0];											// 060227 : bs : ��������� MP Ȯ��
			if (mp)
			{
				mlp = mp->Level(slp->m_magicLevel[0]);
				if (mlp)
				{
					if (rate->hcCashMaxMPUp < mlp->m_nPowerValue)
						rate->hcCashMaxMPUp = mlp->m_nPowerValue;
				}
			}
			bSkip = true;
			break;

		case 352:
			for (i = 0; i < 2; i++)											// 060227 : bs : ��������� HP/MP Ȯ��
			{
				mp = slp->m_magic[i];
				if (mp)
				{
					mlp = mp->Level(slp->m_magicLevel[i]);
					if (mlp)
					{
						switch (mp->m_subtype)
						{
						case MST_STAT_MAXHP:
							if (rate->hcCashMaxHPUp < mlp->m_nPowerValue)
								rate->hcCashMaxHPUp = mlp->m_nPowerValue;
							break;
						case MST_STAT_MAXMP:
							if (rate->hcCashMaxMPUp < mlp->m_nPowerValue)
								rate->hcCashMaxMPUp = mlp->m_nPowerValue;
							break;
						default:
							break;
						}
					}
				}
			}
			bSkip = true;
			break;

		case 354:
			addition->hcExpPlus_S354 = true;								// ����ġ ���� : ��ų 354, 1.5�� ���
			bSkip = true;
			break;

		case 355:
			addition->hcExpPlus_S355 = true;								// ��õ ���� ���� ����ġ ���
			bSkip = true;
			break;

		case 356:
			addition->hcSPPlus_S356 = true;									// ��õ ���� ���� SP ���
			bSkip = true;
			break;

		case 360:
			addition->hcDropPlus_S360 = true;								// ��õ ���� ���� ����� ���
			bSkip = true;
			break;

		case 379:
			mp = slp->m_magic[0];											// �±� ����ġ ��� ����
			if (mp)
			{
				mlp = mp->Level(slp->m_magicLevel[0]);
				if (mlp)
				{
					addition->hcExpPlusPer100 += mlp->m_nPowerValue;				// �±� ����ġ ��� ����
				}
			}
			bSkip = true;
			break;

		case 398:
			mp = slp->m_magic[0];											// (����)����ġ ���� : 1840, 1841, 1842
			if (mp)
			{
				mlp = mp->Level(slp->m_magicLevel[0]);
				if (mlp)
				{
					addition->hcExpPlus_398 = mlp->m_nPowerValue;
				}
			}
			bSkip = true;
			break;

		case 418:
			mp = slp->m_magic[0];							// ��Ű �ҿ� �н�
			if( mp )
			{
				mlp = mp->Level(slp->m_magicLevel[0]);
				if( mlp )
				{
					addition->HitRate_2033 = mlp->m_nPowerValue;
				}
			}
			bSkip = true;
			break;
		case 419:
			mp = slp->m_magic[0];		//��Ű ���� �Ǿ�
			if( mp )
			{
				mlp = mp->Level(slp->m_magicLevel[0]);
				if( mlp )
				{
					addition->Avoid_2034 = mlp->m_nPowerValue;
				}
			}
			bSkip = true;
			break;
		case 424 :		//���� �������
			if( gserver->isActiveEvent(A_EVENT_WHITE_DAY) || gserver->isActiveEvent(A_EVENT_MAGIC_CARD) )
				COption::ApplyOptionValue( (CPC*)ch, OPTION_STR_UP, 20, NULL);
			bSkip = true;
			break;
		case 425 :		//��ø�� �������
			if( gserver->isActiveEvent(A_EVENT_WHITE_DAY) || gserver->isActiveEvent(A_EVENT_MAGIC_CARD) )
				COption::ApplyOptionValue( (CPC*)ch, OPTION_DEX_UP, 20, NULL);
			bSkip = true;
			break;
		case 426 :		//������ �������
			if( gserver->isActiveEvent(A_EVENT_WHITE_DAY) || gserver->isActiveEvent(A_EVENT_MAGIC_CARD) )
				COption::ApplyOptionValue( (CPC*)ch, OPTION_INT_UP, 20, NULL);
			bSkip = true;
			break;
		case 427 :		//ü���� �������
			if( gserver->isActiveEvent(A_EVENT_WHITE_DAY) || gserver->isActiveEvent(A_EVENT_MAGIC_CARD) )
				COption::ApplyOptionValue( (CPC*)ch, OPTION_CON_UP, 50, NULL);
			bSkip = true;
			break;
		case 428 :
			if( gserver->isActiveEvent(A_EVENT_WHITE_DAY) || gserver->isActiveEvent(A_EVENT_MAGIC_CARD) )
				addition->bRorainOfLoveMagic = true;
			bSkip = true;
			break;

		case 433:	// �ǰ��� ����
			ch->cooltime_2142 = gserver->getNowSecond() + 2*60*60;
			break;
		case 434:	// ������ ����
			ch->cooltime_2143 = gserver->getNowSecond() + 2*60*60;
			break;
		case 465:
			ch->m_cooltime_Competition = 0; //gserver->getNowSecond() + 30 * 60;
			break;
		case 470:	// �ҷ��� �̺�Ʈ �ִ� HP ��ȭ
			if( gserver->isActiveEvent(A_EVENT_HALLOWEEN) )
			{
				mp = slp->m_magic[0]; // �ִ� HP ����
				if (mp)
				{
					mlp = mp->Level(slp->m_magicLevel[0]);
					if (mlp)
					{
						rate->hcEventHalloweenMaxHP = mlp->m_nPowerValue;
					}
				}

				mp = slp->m_magic[1]; // �̵��ӵ� ����
				if (mp)
				{
					mlp = mp->Level(slp->m_magicLevel[1]);
					if (mlp)
					{
						rate->hcEventHalloweenSpeed = mlp->m_nPowerValue;
					}
				}
				bSkip = true;
			}
			break;
		case 471:
			if( gserver->isActiveEvent(A_EVENT_HALLOWEEN) )
			{
				mp = slp->m_magic[0]; // �̵��ӵ� ����
				if (mp)
				{
					mlp = mp->Level(slp->m_magicLevel[0]);
					if (mlp)
					{
						rate->hcEventHalloweenSpeed = mlp->m_nPowerValue;
					}
				}
				bSkip = true;
			}
			break;
		case 485:
		case 486:
		case 487:
		case 488:
			{
				mp = slp->m_magic[0];
				if (mp)
				{
					mlp = mp->Level(slp->m_magicLevel[0]);
					if (mlp)
					{
						// ����� ����
						addition->hcDropPlus_Xmas2007 = mlp->m_nPowerValue / 100;
					}
				}
				bSkip = true;
			}
			break;
		case 550:
			{
				mp = slp->m_magic[0];											// 060227 : bs : ��������� ����ġ ���
				if (mp)
				{
					mlp = mp->Level(slp->m_magicLevel[0]);
					if (mlp)
					{
						if (addition->hcCashExpUp < mlp->m_nPowerValue)
							addition->hcCashExpUp = mlp->m_nPowerValue;
					}
				}
				bSkip = true;
				break;
			}
			break;
		}

		if (bSkip == true)
			continue ;

		// --- TODO : �ϵ��ڵ���

		for (i = 0; i < MAX_SKILL_MAGIC; i++)
		{
			if (!p->m_bHit[i])
				continue ;

			mp = slp->m_magic[i];
			if (mp == NULL)
				continue ;
			mlp = mp->Level(slp->m_magicLevel[i]);
			if (mlp == NULL)
				continue ;

			// --- TODO : ASSIST �ϵ� �ڵ�
			switch( mp->m_index )
			{
			case 841:
				addition->hcLimitEXP = mlp->m_nPowerValue;
				continue;
				break;
			case 842:
				addition->hcLimitSP = mlp->m_nPowerValue;
				continue;
				break;
			case 843:
				addition->hcRandomExpUp = mlp->m_nPowerValue;
				continue;
				break;
			case 844:
				addition->hcRandomSpUp = mlp->m_nPowerValue;
				continue;
				break;
			case 845:
				addition->hcRandomDropUp = mlp->m_nPowerValue;
				continue;
				break;
			case 971:
				addition->hcHPSteelPotion = true;
				continue;
				break;
			}

			switch (mp->m_type)
			{
			case MT_STAT:
				switch (mp->m_subtype)
				{
				case MST_STAT_ATTACK:
					APPVAL(attack);
					break;
				case MST_STAT_DEFENSE:
					APPVAL(defense);
					break;
				case MST_STAT_MAGIC:
					APPVAL(magic);
					break;
				case MST_STAT_RESIST:
					APPVAL(resist);
					break;
				case MST_STAT_HITRATE:
					APPVAL(hitrate);
					break;
				case MST_STAT_AVOID:
					APPVAL(avoid);
					break;
				case MST_STAT_CRITICAL:
					APPVAL(critical);
					break;
				case MST_STAT_ATTACKSPD:
					APPVAL(attackspeed);
					break;
				case MST_STAT_MAGICSPD:
					APPVAL(magicspeed);
					break;
				case MST_STAT_MOVESPD:
					APPVAL(movespeed);
					break;
				case MST_STAT_RECOVERHP:
					APPVAL(recoverhp);
					break;
				case MST_STAT_RECOVERMP:
					APPVAL(recovermp);
					break;
				case MST_STAT_MAXHP:
					APPVAL(maxhp);
					break;
				case MST_STAT_MAXMP:
					APPVAL(maxmp);
					break;
				case MST_STAT_DEADLY:
					APPVAL(deadly);
					break;
				case MST_STAT_MAGICHITRATE:
					APPVAL(magichitrate);
					break;
				case MST_STAT_MAGICAVOID:
					APPVAL(magicavoid);
					break;
				case MST_STAT_ATTACKDIST:
					APPVAL(attackdist);
					break;
				case MST_STAT_ATTACK_MELEE:
					APPVAL(attack_dam_melee);
					break;
				case MST_STAT_ATTACK_RANGE:
					APPVAL(attack_dam_range);
					break;
				case MST_STAT_HITRATE_SKILL:
					APPVAL(hitrate_skill);
					break;
				case MST_STAT_ATTACK_80:
					APPVAL(attack80);
					break;
				case MST_STAT_MAXHP_450:
					APPVAL(maxhp450);
					break;
				case MST_STAT_HARD:
					APPVAL(hard);
					break;
				case MST_STAT_SKILLSPD:
					APPVAL(skillspd);
					break;
				case MST_STAT_NPCATTACK:
					APPVAL(npcAttack);
					break;
				case MST_STAT_NPCMAGIC:
					APPVAL(npcMagic);
					break;
				case MST_STAT_SKILLCOOLTIME:
					APPVAL(SkillCooltime);
					break;
#ifdef ASSIST_DECREASE_SKILL_MP
				case MST_STAT_DECREASE_MANA_SPEND:
					APPVAL(decreaseskillmp);
					break;
#endif
				case MST_STAT_ABSORB:
					APPVAL(pvpabsorbrate);
					break;

				case MST_STAT_VALOR:
					{
						if( IS_PC(ch) )
						{
							CPC *pc = TO_PC(ch);
							if( pc->IsParty() && pc->m_party->GetNearPartyMemberCount(pc) > 1)
							{
								addition->attack += (mlp->m_nPowerValue * CalcSkillParam(ch, ch, SPARAM_NONE, mp->m_ptp) / 100) * pc->m_party->GetNearPartyMemberCount(pc) / 10;
							}
							else if( pc->IsExped() && pc->m_Exped->GetNearExpeditionMemberCount(pc) > 1 )
							{
								const CExpedMember *member = pc->m_Exped->GetMemberByCharIndex(pc->m_index);
								int group_type = 0;
								if( member )
									group_type = member->GetGroupType();
								addition->attack += (mlp->m_nPowerValue * CalcSkillParam(ch, ch, SPARAM_NONE, mp->m_ptp) / 100) * pc->m_Exped->GetGroupMemberCount(group_type)  / 10;
							}
						}
					}
					break;
				case MST_STAT_STATPALL:
					APPVAL(statpall);
					break;
				// << 071211 kjban add
				case MST_STAT_ATTACK_PER:
					{
						switch (mp->m_damagetype)
						{
						case MDT_ADDITION:
							addition->attack += ch->m_eqMelee * mlp->m_nPowerValue / 100;
							addition->attack += ch->m_eqRange * mlp->m_nPowerValue / 100;
							addition->magic += ch->m_eqMagic * mlp->m_nPowerValue / 100;
							break;
						case MDT_RATE:
							rate->attack += ch->m_eqMelee * mlp->m_nPowerValue / 100;
							rate->attack += ch->m_eqRange * mlp->m_nPowerValue / 100;
							rate->magic += ch->m_eqMagic * mlp->m_nPowerValue / 100;
							break;
						}
					}
					break;

				case MST_STAT_DEFENSE_PER:
					{
						switch (mp->m_damagetype)
						{
						case MDT_ADDITION:
							addition->defense += ch->m_eqDefense * mlp->m_nPowerValue / 100;
							break;
						case MDT_RATE:
							rate->defense += ch->m_eqDefense * mlp->m_nPowerValue / 100;
							break;
						}
					}
					break;

				case MST_STAT_STATPALL_PER:
					{
						switch (mp->m_damagetype)
						{
						case MDT_ADDITION:
							addition->statpall_per += mlp->m_nPowerValue;
							break;
						case MDT_RATE:
							rate->statpall_per += mlp->m_nPowerValue;
							break;
						}
					}
					break;
				//  [5/15/2008 KwonYongDae]
				case MST_STAT_STR:
					{
						COption::ApplyOptionValue( (CPC*)ch, OPTION_STR_UP, mlp->m_nPowerValue, NULL);
					}
					break;
				case MST_STAT_DEX:
					{
						COption::ApplyOptionValue( (CPC*)ch, OPTION_DEX_UP, mlp->m_nPowerValue, NULL);
					}
					break;
				case MST_STAT_INT:
					{
						COption::ApplyOptionValue( (CPC*)ch, OPTION_INT_UP, mlp->m_nPowerValue, NULL);
					}
					break;
				case MST_STAT_CON:
					{
						COption::ApplyOptionValue( (CPC*)ch, OPTION_CON_UP, mlp->m_nPowerValue, NULL);
					}
					break;
				case MST_STAT_STONE:
					{
						COption::ApplyOptionValue( (CPC*)ch, OPTION_RESIST_STONE, mlp->m_nPowerValue, NULL);
					}
					break;
				case MST_STAT_SILEN:
					{
						COption::ApplyOptionValue( (CPC*)ch, OPTION_RESIST_SILENT, mlp->m_nPowerValue, NULL);
					}
					break;
				case MST_STAT_STURN:
					{
						COption::ApplyOptionValue( (CPC*)ch, OPTION_RESIST_STURN, mlp->m_nPowerValue, NULL);
					}
					break;
				}
				break;

// OLD ATTRIBUTE VARIABLE REUSE, Elenoa 2013.01.09

			case MT_ATTRIBUTE:
				if (mp->m_subtype < 0 || mp->m_subtype > AT_RANDOM)
					break;

				switch(mp->m_subtype)
				{
				case AT_RANDOM:
					{
						int rand = p->attr_rand;
						
						if(p->attr_rand <= 0)
						{
							rand = GetRandom(AT_FIRE, AT_LIGHT);
							p->attr_rand = rand;
						}

						if(mp->m_damagetype == MDT_ATTACK)
							addition->attratt_item = AT_MIX(rand, mlp->m_nPowerValue);						
						else if(mp->m_damagetype == MDT_DEFENCE)
							addition->attrdef_item = AT_MIX(rand, mlp->m_nPowerValue);
					}
					break;
				default:
					switch (mp->m_damagetype)
					{
					case MDT_ATTACK: /* attr attack */
						addition->attratt =
							AT_MIX(mp->m_subtype, mlp->m_nPowerValue);
						break;

					case MDT_DEFENCE: /* attr defend */
						addition->attrdef =
							AT_MIX(mp->m_subtype, mlp->m_nPowerValue);
						break;
					}
					break;
				}
				break;
				

			case MT_ASSIST:
				switch (mp->m_subtype)
				{
				case MST_ASSIST_POISON:
					*state |= AST_POISON;
					break;
				case MST_ASSIST_HOLD:
					*state |= AST_HOLD;
					break;
				case MST_ASSIST_CONFUSION:
					*state |= AST_CONFUSION;
					break;
				case MST_ASSIST_STONE:
#ifdef RAID_MONSTER_SKIP_STONE		// ���̵� �� ���� ����
					if( IS_NPC(ch) )
					{
						CNPC * pNpc = TO_NPC(ch);
						if( pNpc != NULL )
						{
							if( pNpc->m_proto->CheckFlag(NPC_RAID) )
							{
								break;
							}
						}
					}
#endif	// RAID_MONSTER_SKIP_STONE
					*state |= AST_STONE;
					break;

				case MST_ASSIST_SILENT:
					*state |= AST_SILENT;
					break;
				case MST_ASSIST_BLOOD:
					*state |= AST_BLOOD;
					break;
				case MST_ASSIST_BLIND:
					*state |= AST_BLIND;
					if(IS_PC(ch))
					{
						CPC* pc = TO_PC(ch);
						if( ch->m_currentSkill != NULL )
						{
							ch->m_currentSkill->Cancel(ch);
							ch->m_currentSkill = NULL;
							CNetMsg::SP rmsg(new CNetMsg);
							ResponseClient::makeSkillCancelMsg(rmsg, ch);
							ch->m_pArea->SendToCell(rmsg, ch, true);
						}
					}
					break;
				case MST_ASSIST_STURN:
#ifdef RAID_MONSTER_SKIP_STURN		// ���̵� �� ���� ����
					if( IS_NPC(ch) )
					{
						CNPC * pNpc = TO_NPC(ch);
						if( pNpc != NULL )
						{
							if( pNpc->m_proto->CheckFlag(NPC_BOSS | NPC_RAID) )
							{
								break;
							}
						}
					}
#endif	// RAID_MONSTER_SKIP_STURN
					*state |= AST_STURN;
					break;
				case MST_ASSIST_SLEEP:
					*state |= AST_SLEEP;
					break;
				case MST_ASSIST_HP:
					*state |= AST_HP;
					break;
				case MST_ASSIST_MP:
					*state |= AST_MP;
					break;
				case MST_ASSIST_MOVESPD:
					*state |= AST_MOVESPD;
					APPVAL(movespeed);
					break;
				case MST_ASSIST_DIZZY:
					*state |= AST_DIZZY;
					APPVAL(movespeed);
					break;
				case MST_ASSIST_INVISIBLE:
					*state |= AST_INVISIBLE;
					break;
				case MST_ASSIST_SLOTH:
					*state |= AST_SLOTH;
					APPVAL(attackspeed);
					break;
				case MST_ASSIST_FEAR:
					*state |= AST_FEAR;
					addition->hcFearType = p->m_spellerType;
					addition->hcFearIndex = p->m_spellerIndex;
					break;
				case MST_ASSIST_FAKEDEATH:
					*state |= AST_FAKEDEATH;
					break;
				case MST_ASSIST_PERFECTBODY:
					*state |= AST_PERFECTBODY;
					APPVAL(defense);
					break;
				case MST_ASSIST_FRENZY:
					*state |= AST_FRENZY;
					APPVAL(attack);
					break;
				case MST_ASSIST_DAMAGELINK:
					*state |= AST_DAMAGELINK;
					break;
				case MST_ASSIST_BERSERK:
					*state |= AST_BERSERK;
					APPVAL(attackspeed);
					break;
				case MST_ASSIST_DESPAIR:
					*state |= AST_DESPAIR;
					APPVAL(despair);
					break;
				case MST_ASSIST_MANASCREEN:
					*state |= AST_MANASCREEN;
					APPVAL(manascreen);
					break;
				case MST_ASSIST_BLESS:
					*state |= AST_BLESS;
					APPVAL(bless);
					break;
				case MST_ASSIST_SAFEGUARD:
					*state |= AST_SAFEGUARD;
					if(IS_PC(ch))
					{
						CPC* pc = TO_PC(ch);
						pc->m_bImmortal = true;
					}
					break;
				case MST_ASSIST_MANTLE:
					*state |= AST_MANTLE;
					break;
				case MST_ASSIST_GUARD:
					*state |= AST_GUARD;
					break;
				case MST_ASSIST_CHARGEATC:
					//���� �������� ������̶�� 
					if(IS_PC(ch))
					{
						CPC* pc = TO_PC(ch);
						if(pc->holy_water_item != NULL)
						{
							//��� ����
							pc->changeToggleState(pc->holy_water_item->getVIndex(), TOGGLE_ITEM);
							//���� ������ ����
							pc->SendHolyWaterStateMsg(NULL);
						}
					}
					APPVAL(charge_attack);
					break;
				case MST_ASSIST_CHARGEMGC:
					//���� �������� ������̶�� ��� ����
					if(IS_PC(ch))
					{
						CPC* pc = TO_PC(ch);
						if(pc->holy_water_item != NULL)
						{
							//��� ����
							pc->changeToggleState(pc->holy_water_item->getVIndex(), TOGGLE_ITEM);
							//���� ������ ����
							pc->SendHolyWaterStateMsg(NULL);
						}
					}
					APPVAL(charge_magic);
					break;
				case MST_ASSIST_DISEASE:
					*state |= AST_DISEASE;
					break;
				case MST_ASSIST_CURSE:
					*state |= AST_CURSE;
					break;
				case MST_ASSIST_CONFUSED:
					*state |= AST_CONFUSED;
					break;
				case MST_ASSIST_TAMING:
					*state |= AST_TAMING;
					break;
				case MST_ASSIST_FREEZE:
					*state |= AST_FREEZE;
					
					if (IS_PC(ch)) {
						CPC* pc = TO_PC(ch);
						if (pc->IsSetPlayerState(PLAYER_CRISTAL_RESPOND) && p->m_proto->m_index == 681) {
							CNetMsg::SP rmsg(new CNetMsg);
							CastleCristalRespondWaitMsg(rmsg, pc);
							SEND_Q(rmsg, pc->m_desc);
						}
					}

					break;
				case MST_ASSIST_INVERSE_DAMAGE:
					*state |= AST_INVERSE_DAMAGE;
					APPVAL(inverse_damage);
					break;
				case MST_ASSIST_HP_DOT:
					*state |= AST_HP_DOT;
					break;
				case MST_ASSIST_DARKNESS_MODE:
					*state |= AST_DARKNESS_MODE;
					break;
				case MST_ASSIST_AURA_DARKNESS:
					*state |= AST_AURA_DARKNESS;
					break;
				case MST_ASSIST_AURA_WEAKNESS:
					*state |= AST_AURA_WEAKNESS;
					break;
				case MST_ASSIST_AURA_ILLUSION:
					*state |= AST_AURA_ILUSYON;
					break;
				case MST_ASSIST_MERCENARY:
					*state |= AST_MERCENARY;
					break;
				case MST_ASSIST_SOUL_TOTEM_BUFF:
					*state |= AST_SOUL_TOTEM_BUFF;
					break;
				case MST_ASSIST_SOUL_TOTEM_ATTK:
					*state |= AST_SOUL_TOTEM_ATTK;
					break;
				case MST_ASSIST_TRAP:
					*state |= AST_TRAP;
					break;
				case MST_ASSIST_PARASITE:
					*state |= AST_PARASITE;
					break;
				case MST_ASSIST_SUICIDE:
					*state |= AST_SUICIDE;
					break;
				case MST_ASSIST_INVINCIBILITY:
					*state |= AST_INVINCIBILITY;
					break;
				case MST_ASSIST_GPS:
					if(IS_PC(ch))
					{
						CPC* pc = TO_PC(ch);
						if(sp->m_index == 1759)
							pc->m_gpsManager.setIsGps(true);
						else if(sp->m_index == 1760)
							pc->m_gpsManager.setIsGpsInterrupt(true);
					}
					break;
				case MST_ASSIST_ATTACK_TOWER:
					*state |= AST_TOWER_ATTACK;
					APPVAL(tower_attack);
					break;
				case MST_ASSIST_ARTIFACT_GPS:
					{
						if(IS_PC(ch))
						{
							CPC* pc = TO_PC(ch);
							pc->m_arti_gpsManager.setIsGps(true);
						}
					}
					break;
				#ifdef HP_REDUCE_10222021
				case MSG_ASSIST_HEAL_REDUCE:
					*state |= AST_HEAL_REDUCE;
					APPVAL(hp_recover_reduce);
					break;
				#endif
				}
				break;

			case MT_OTHER:
				switch (mp->m_subtype)
				{
				case MST_OTHER_AFFINITY:
					{
						switch (mp->m_damagetype)
						{
						case MDT_ADDITION:
							addition->affinity += mlp->m_nPowerValue;
							break;
						case MDT_RATE:
							rate->affinity_rate += mlp->m_nPowerValue;
							break;
						default:
							break;
						}
					}
					break;
				case MST_OTHER_REFLEX:
					APPVAL(hcReflex);
					addition->hcReflexProb += mlp->m_nHitrateValue;
					break;
				case MST_OTHER_EXP:
					switch (mp->m_damagetype)
					{
					case MDT_ADDITION:
						addition->exp += mlp->m_nPowerValue;
						break;
					case MDT_RATE:
						addition->exp_rate += mlp->m_nPowerValue;
						break;
					}
					break;
				case MST_OTHER_SP:
					switch (mp->m_damagetype)
					{
					case MDT_ADDITION:
						addition->sp += mlp->m_nPowerValue;
						break;
					case MDT_RATE:
						addition->sp_rate += mlp->m_nPowerValue;
						break;
					}
					break;
#ifdef REFORM_PK_PENALTY_201108 // PK �г�Ƽ ����
				case MST_OTHER_PK_DISPOSITION:
					switch (mp->m_damagetype)
					{
					case MDT_ADDITION:
						{
							int durHour = sp->m_levelproto[0]->m_durtime / (60*60*10) ;
							int PkPointPerHour = ( PK_HUNTER_POINT_MAX * mlp->m_nPowerValue / 100 ) / durHour;
							addition->pkDispositionPointValue = PkPointPerHour;
						}
						break;
					case MDT_RATE:
						rate->pkDispositionPointValue = mlp->m_nPowerValue;
						break;
					}
					break;
#endif // REFORM_PK_PENALTY_201108
				}
				break;

			case MT_REDUCE:
				switch (mp->m_subtype)
				{
				case MST_REDUCE_MELEE:
					APPVAL(reduceMelee);
					addition->reduceMeleeProb += mlp->m_nHitrateValue;
					break;
				case MST_REDUCE_RANGE:
					APPVAL(reduceRange);
					addition->reduceRangeProb += mlp->m_nHitrateValue;
					break;
				case MST_REDUCE_MAGIC:
					APPVAL(reduceMagic);
					addition->reduceMagicProb += mlp->m_nHitrateValue;
					break;
#ifdef ASSIST_REDUCE_SKILL
				case MST_REDUCE_SKILL:
					APPVAL(reduceSkill);
					addition->reduceSkillProb += mlp->m_nHitrateValue;
					break;
#endif
				}
				break;

			case MT_IMMUNE:
				switch (mp->m_subtype)
				{
				case MST_IMMUNE_BLIND:
					addition->immune_blind = true;
					break;
				}
				break;

			case MT_CASTLE_WAR:
				switch (mp->m_subtype)
				{
				case MST_WAR_REDUCE_MELEE:
					APPVAL(war_reduce_melee);
					addition->war_reduce_melee_prob += mlp->m_nHitrateValue;
					break;
				case MST_WAR_REDUCE_RANGE:
					APPVAL(war_reduce_range);
					addition->war_reduce_range_prob += mlp->m_nHitrateValue;
					break;
				case MST_WAR_REDUCE_MAGIC:
					APPVAL(war_reduce_magic);
					addition->war_reduce_magic_prob += mlp->m_nHitrateValue;
					break;
				case MST_WAR_MAX_HP:
					APPVAL(war_max_hp);
					break;
				case MST_WAR_DEFENCE:
					APPVAL(war_defence);
					break;
				case MST_WAR_RESIST:
					APPVAL(war_resist);
					break;
				case MST_WAR_TOWER_ATTACK:
					APPVAL(war_tower_attack);
					break;
				}
				break;
			}
		}
	}
}

// 060227 : bs : ����ð� ���� �߰�
void CAssistList::DelAssist(CAssistData* d, bool bSend, CCharacter* ch, bool bNoCancelType, bool statusUpdate)
{
	// 060317 : bs : SF_NOCANCEL �˻�
	// bNoCancelType �� false
	if (!bNoCancelType && (d->m_proto->m_flag & SF_NOCANCEL))
		return ;

	// data ����
	// ��������� ����
	if (m_head == d)		m_head = m_head->m_next;
	// ���������� ����
	if (m_tail == d)		m_tail = m_tail->m_prev;
	// prev ��ũ ����
	if (d->m_prev)			d->m_prev->m_next = d->m_next;
	// next ��ũ ����
	if (d->m_next)			d->m_next->m_prev = d->m_prev;
	// ��ũ ����
	d->m_prev = NULL;
	d->m_next = NULL;

	bool bIsDamageLink = false;
	const CSkillLevelProto* pSkillLevelProto = d->m_proto->Level(d->m_level);
	if (pSkillLevelProto)
	{
		int i;
		for (i = 0; i < MAX_SKILL_MAGIC; i++)
		{
			if (pSkillLevelProto->m_magic[i])
			{
				if (pSkillLevelProto->m_magic[i]->m_type == MT_ASSIST && pSkillLevelProto->m_magic[i]->m_subtype == MST_ASSIST_DAMAGELINK)
				{
					bIsDamageLink = true;
					break;
				}
				if (pSkillLevelProto->m_magic[i]->m_type == MT_ASSIST
						&& pSkillLevelProto->m_magic[i]->m_subtype == MST_ASSIST_SAFEGUARD)
				{
					CPC * pc = TO_PC(ch);
					if (pc != NULL)
					{
						pc->m_bImmortal = false;
						pc->m_assist.m_state &= ~AST_SAFEGUARD;
					}
				}
				if (pSkillLevelProto->m_magic[i]->m_type == MT_ASSIST
						&& pSkillLevelProto->m_magic[i]->m_subtype == MST_ASSIST_GUARD)
				{
					CPC * pc = TO_PC(ch);
					if (pc != NULL)
					{
						CElemental* pElemental = NULL;
						CElemental* pElementalNext = pc->m_elementalList;
						while ((pElemental = pElementalNext))
						{
							pElementalNext = pElemental->m_nextElemental;
							if(pElemental->GetElementalType() == ELEMENTAL_GUARD)
								pc->UnsummonElemental(pElemental);
						}
					}
				}
				if (pSkillLevelProto->m_magic[i]->m_type == MT_ASSIST
					&& pSkillLevelProto->m_magic[i]->m_subtype == MST_ASSIST_GPS)
				{
					CPC * pc = TO_PC(ch);
					if (pc != NULL)
					{
						if(d->m_proto->m_index == 1759)
						{
							pc->m_gpsManager.setIsGps(false);
						}
						else if(d->m_proto->m_index == 1760)
						{
							pc->m_gpsManager.setIsGpsInterrupt(false);
						}
					}
				}

				if (pSkillLevelProto->m_magic[i]->m_type == MT_ASSIST
					&& pSkillLevelProto->m_magic[i]->m_subtype == MST_ASSIST_ARTIFACT_GPS)
				{
					CPC * pc = TO_PC(ch);
					if (pc != NULL)
					{
						pc->m_arti_gpsManager.setIsGps(false);
					}
				}

				if (pSkillLevelProto->m_magic[i]->m_index == 520)
				{
					CPC * pc = TO_PC(ch);
					if (pc != NULL)
					{
						pc->setSearchLife(false);
					}
				}
				// ȥ���̳� ���̹� ���� �����̸� �ð��� ������ Ǯ���ش�.
				if (pSkillLevelProto->m_magic[i]->m_type == MT_ASSIST
						&& pSkillLevelProto->m_magic[i]->m_subtype == MST_ASSIST_CONFUSED)
				{
					if (IS_NPC(ch))
					{
						CNPC* pNPC = TO_NPC(ch);
						if (pNPC)
						{
							pNPC->reSet_MobFlag( STATE_MONSTER_CONFUSION );
							DelAttackList(pNPC);
						}
					}
				}
				if (pSkillLevelProto->m_magic[i]->m_type == MT_ASSIST
						&& pSkillLevelProto->m_magic[i]->m_subtype == MST_ASSIST_TAMING)
				{
					if (IS_NPC(ch))
					{
						CNPC* pNPC = TO_NPC(ch);
						if (pNPC)
						{
							pNPC->reSet_MobFlag( STATE_MONSTER_TAMING );
							DelAttackList(pNPC);

							// ������ ã�´�.
							CPC* owner = pNPC->GetOwner();
							if(owner != NULL)
							{
								owner->DeleteSlave( pNPC );
								// npc�� ���ε� ���� ��
								pNPC->SetOwner(NULL);
							}
						}
					}
				}

				if (pSkillLevelProto->m_magic[i]->m_type == MT_ASSIST && IS_NPC(ch) )
				{
					switch(pSkillLevelProto->m_magic[i]->m_subtype )
					{
					case MST_ASSIST_SOUL_TOTEM_BUFF:
					case MST_ASSIST_SOUL_TOTEM_ATTK:
					case MST_ASSIST_TRAP:
					case MST_ASSIST_SUICIDE:
						{
							// ������ �������� ���ϸ� NPC�� ����Ʈ���� �����Ѵ�.
							if( TO_NPC(ch)->GetOwner() )
								TO_NPC(ch)->GetOwner()->SummonNpcRemove(TO_NPC(ch));
						}
						break;
					}
				}
			}
		}
	}

	if (bIsDamageLink/*(ch->m_assist.m_state & AST_DAMAGELINK) != 0*/)
	{
		CCharacter* plinkSource = ch->m_linkSource;
		CCharacter* plinkTarget = ch->m_linkTarget;
		ch->m_linkSource = NULL;
		ch->m_linkTarget = NULL;
		if (plinkSource)
		{
			plinkSource->m_linkTarget = NULL;
			plinkSource->CancelDamageLink();
		}
		if (plinkTarget)
		{
			plinkTarget->m_linkSource = NULL;
			plinkTarget->CancelDamageLink();
		}
	}

	if( d->m_proto->m_flag & SF_ABSTIME )
		m_abscount--;
	else
		m_count--;

	if(statusUpdate == true)
		ch->CalcStatus(bSend);

	if( d->m_index != -1 )
	{
		if( IS_PC(ch) )
		{
			CItemProto* proto = gserver->m_itemProtoList.FindIndex(d->m_index);
			if( proto && proto->getItemFlag() & ITEM_FLAG_CASH )
			{
				GAMELOG << init("CASH_ASSIST_DEL", TO_PC(ch))
						<< proto->getItemIndex() << delim
						<< proto->getItemName() << delim
						<< d->m_index << delim
						<< d->m_remain << delim
						<< d->m_proto->m_index << delim
						<< (d->m_proto->m_flag & SF_ABSTIME) << end;
			}
		}
	}

	switch(d->m_proto->m_index)
	{
	case 1062:
	case 1063:
	case 1064:
	case 1065:
		{
			GAMELOG << init("EP SKILL END", TO_PC(ch))
					<< "Skill Index" << delim << d->m_proto->m_index << delim
					<< "Skill Level" << delim << d->m_level << end;
		}
		break;
	default:
		break;
	}

	if (bSend)
	{
		{
			CNetMsg::SP rmsg(new CNetMsg);
			AssistDelMsg(rmsg, ch, d->m_index, d->m_proto->m_index);
			ch->m_pArea->SendToCell(rmsg, ch, true);
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			CharStatusMsg(rmsg, ch, 0);
			ch->m_pArea->SendToCell(rmsg, ch, true);
		}

		// �ֽ�ų ���� �� �������ͽ��� ������.
		if( IS_APET(ch) )
		{
			CAPet * pApet = TO_APET(ch);
			if(pApet->GetOwner() != NULL)
			{
				CNetMsg::SP rmsg(new CNetMsg);
				ExAPetStatusMsg( rmsg, pApet );
				SEND_Q( rmsg, pApet->GetOwner()->m_desc );
			}
		}
	}

	delete d;
}

////////////////
// class CAssist

CAssist::CAssist()
{
	m_ch = NULL;

	m_help.Max(MAX_ASSIST_HELP);
	m_curse.Max(MAX_ASSIST_CURSE);

	m_delaycheck = gserver->getNowSecond();

	memset(&m_avAddition, 0, sizeof(m_avAddition));
	memset(&m_avRate, 0, sizeof(m_avRate));
	m_state = 0;
}

void CAssist::Init(CCharacter* ch)
{
	m_ch = ch;
}

bool CAssist::Add(CCharacter* spellchar, int itemidx, const CSkillProto* proto, int level, bool bHit[MAX_SKILL_MAGIC], bool bSend, int remain,
				  int remainCount,
				  int param, int nBlessAdd, int nBlessRate)
{
	if (!CanApply(proto, level))
		return false;

	CAssistList* list = NULL;

	if (proto->m_flag & SF_HELP)
		list = &m_help;
	else
		list = &m_curse;

	bool bCancelBlind = false;
	bool isStone = false;
	bool isDamageLink = false;

	int i;
	int j = 0;
	for (i = 0; i < MAX_SKILL_MAGIC; i++)
	{
		if (bHit[i] && proto->Level(level)->m_magic[i])
		{
			j++;

			switch (proto->Level(level)->m_magic[i]->m_type)
			{
			case MT_IMMUNE:
				switch (proto->Level(level)->m_magic[i]->m_subtype)
				{
				case MST_IMMUNE_BLIND:
					bCancelBlind = true;
					break;
				}
				break;

			case MT_ASSIST:
				switch (proto->Level(level)->m_magic[i]->m_subtype)
				{
				case MST_ASSIST_HOLD:
				case MST_ASSIST_SILENT:
				case MST_ASSIST_STONE:
				case MST_ASSIST_STURN:
				case MST_ASSIST_SLEEP:
					if( IS_NPC(m_ch) )
					{
						CNPC* pNpc = TO_NPC(m_ch);
						//Ȧ�忡 ���� �鿪 ��ų �ߵ� �÷��װ� ���� ���
						if(pNpc->m_proto->CheckStateFlag( (1 << proto->Level(level)->m_magic[i]->m_subtype)) )
						{
							//npc ���� ���� Ȧ�� �鿪 ������ �ɷ��ִ� ���
							if(pNpc->m_assist.FindBySkillIndex(1751))		//1751 : ���̾� �� (NPC �鿪 ��ų �ε���)
							{
								return false;
							}
							const CSkillProto* proto = gserver->m_skillProtoList.Find(1751);
							const CSkillLevelProto* levelproto = proto->Level(1);
							bool bHit[MAX_SKILL_MAGIC] = {true, false, false};
							pNpc->m_assist.Add(m_ch, -1, proto, 1, bHit, true, ((pNpc->m_ctCount * 15) + 20) * 10, levelproto->m_useCount, 0, 0, 0);
							pNpc->m_ctCount++;
							if(pNpc->m_ctCount == 20)
								pNpc->m_ctCount = 20;
						}
					}
					if (proto->Level(level)->m_magic[i]->m_subtype == MST_ASSIST_STONE)
						isStone = true;
					break;
				case MST_ASSIST_FEAR:
					if (spellchar == NULL)
						return false;
					break;

				case MST_ASSIST_DAMAGELINK:
					if (spellchar == NULL)
						return false;
					else
						isDamageLink = true;
					break;
				}
				break;
			}
		}
	}
	if (j == 0)
		return false;

	if (isStone)
		ClearAssist(bSend, true, true, true, false);
//	else if (m_state & AST_STONE)
//		return false;

	// �Ҽ����� �ҳ�� �극��ũ �̸鼭 ��ȭ�� �����ߴٸ� ����� �޼����� ���� �ʴ´�.   yhj
	if ( proto->m_index == 311 && !isStone )
	{
		return false;
	}

	if (isDamageLink)
	{
		if (m_ch->m_linkSource || m_ch->m_linkTarget)
			m_ch->CancelDamageLink();

		if (spellchar != m_ch)
		{
			int nTemp = remain;
			int nTemp2 = remainCount;
			if (!spellchar->m_assist.Add(spellchar, itemidx, proto, level, bHit, bSend, nTemp,
										 nTemp2,
										 param, nBlessAdd, nBlessRate))
				return false;
		}
	}

//	DelDuplicate(proto, level, bSend, false);
	DelDuplicate(proto, level, bSend, true);
	CheckApplyConditions();

	if (bCancelBlind)
		CureAssist(MST_ASSIST_BLIND, 99);

	if (!list->Add(spellchar, itemidx, proto, level, bHit, remain,
				   remainCount,
				   param, nBlessAdd, nBlessRate, m_ch->m_decreaseDBufTimeRate))
		return false;

	if (isDamageLink)
	{
		if (spellchar != m_ch)
		{
			m_ch->m_linkSource = spellchar;
			spellchar->m_linkTarget = m_ch;
		}
	}

	m_ch->CalcStatus(true);

	if (bSend)
	{
		{
			CNetMsg::SP rmsg(new CNetMsg);
			AssistAddMsg(rmsg, m_ch, itemidx, proto->m_index, level, remain
						 , remainCount
						);
			m_ch->m_pArea->SendToCell(rmsg, m_ch, true);
		}

		{
			CNetMsg::SP rmsg(new CNetMsg);
			CharStatusMsg(rmsg, m_ch, 0);
			m_ch->m_pArea->SendToCell(rmsg, m_ch, true);
		}

		// �ֽ�ų ���� �� �������ͽ��� ������.
		if( IS_APET(m_ch) )
		{
			CAPet * pApet = TO_APET(m_ch);
			CNetMsg::SP rmsg(new CNetMsg);
			ExAPetStatusMsg( rmsg, pApet );
			SEND_Q( rmsg, pApet->GetOwner()->m_desc );
		}
	}

	return true;
}

bool CAssist::CanApply(const CSkillProto* proto, int level)
{
	if (proto == NULL)
		return false;
	const CSkillLevelProto* levelproto = proto->Level(level);
	if (levelproto == NULL)
		return false;

	CPC * pc = NULL;
	if (m_ch != NULL && IS_PC(m_ch)) {
		pc = TO_PC(m_ch);
	}

	int i;
	for (i = 0; i < MAX_SKILL_MAGIC; i++)
	{
		if (levelproto->m_magic[i])
		{
			switch (levelproto->m_magic[i]->m_type)
			{
			case MT_ASSIST:
				switch (levelproto->m_magic[i]->m_subtype)
				{
				case MST_ASSIST_SILENT:
					if (IS_PC(m_ch) && GetRandom(1, 100) < pc->m_opResistSilent)
						return false;
					break;
				case MST_ASSIST_STURN:
					if (IS_PC(m_ch) && GetRandom(1, 100) < pc->m_opResistSturn)
						return false;
					break;
				case MST_ASSIST_FREEZE:
				case MST_ASSIST_STONE:
					if (IS_PC(m_ch) && GetRandom(1, 100) < pc->m_opResistStone)
						return false;
					break;
				case MST_ASSIST_BLIND:
					if (FindByType(MT_IMMUNE, MST_IMMUNE_BLIND) || m_ch->m_avPassiveAddition.immune_blind)
					{
						//100% ���� ���� its : 18842 -> 80%Ȯ���� �����ϵ��� ����
						int rand = GetRandom(1, 10000);
						if(rand > 2000)
							return false;
					}
					break;
				case MST_ASSIST_AURA_DARKNESS:
				case MST_ASSIST_AURA_WEAKNESS:
				case MST_ASSIST_AURA_ILLUSION:
					// AURA�� �Ѱ����� ����� �� �ִ�.
					// ������ ����ϰ� �ִ��� Ȯ��
					if(FindByType(MT_ASSIST, MST_ASSIST_AURA_DARKNESS)
							||FindByType(MT_ASSIST, MST_ASSIST_AURA_WEAKNESS)
							||FindByType(MT_ASSIST, MST_ASSIST_AURA_ILLUSION))
						return false;
					break;
				}
				break;
			}
		}
	}

	return (m_help.CanApply(proto, level) && m_curse.CanApply(proto, level));
}

// 060227 : bs : ����ð� ���� �߰�
void CAssist::DelDuplicate(const CSkillProto* proto, int level, bool bSend, bool bNoCancelType)
{
	m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);
	m_curse.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

	// �̼ӹ���� ��ũ��ǵ�� ���������Ʈ�� ���� ���� �ȵȴ�
	switch (proto->m_index)
	{
	case 155:		// ���������Ʈ
		proto = gserver->m_skillProtoList.Find(70);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);
		m_curse.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(62);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);
		m_curse.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);
		break;
	case 70:		// �̼ӹ���
	case 62:		// íũ��
		proto = gserver->m_skillProtoList.Find(155);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);
		m_curse.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);
		break;
	case 470:
		if( !gserver->isActiveEvent(A_EVENT_HALLOWEEN) )
			break;
		proto = gserver->m_skillProtoList.Find(471);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(472);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(473);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(474);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);
		break;
	case 471:
		if( !gserver->isActiveEvent(A_EVENT_HALLOWEEN) )
			break;
		proto = gserver->m_skillProtoList.Find(470);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(472);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(473);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(474);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);
		break;
	case 472:
		if( !gserver->isActiveEvent(A_EVENT_HALLOWEEN) )
			break;
		proto = gserver->m_skillProtoList.Find(470);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(471);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(473);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(474);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);
		break;
	case 473:
		if( !gserver->isActiveEvent(A_EVENT_HALLOWEEN) )
			break;
		proto = gserver->m_skillProtoList.Find(470);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(471);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(472);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(474);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);
		break;
	case 474:
		if( !gserver->isActiveEvent(A_EVENT_HALLOWEEN) )
			break;
		proto = gserver->m_skillProtoList.Find(470);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(471);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(472);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);

		proto = gserver->m_skillProtoList.Find(473);
		m_help.DelDuplicate(proto, level, bSend, m_ch, bNoCancelType);
		break;
	}
}

bool CAssist::DecreaseTime()
{
	if ( m_delaycheck == gserver->getNowSecond())
		return false;

	m_delaycheck = gserver->getNowSecond();

	LONGLONG changestate = 0;

	bool bret = m_help.DecreaseTime(m_ch, &changestate);
	if (m_curse.DecreaseTime(m_ch, &changestate))
		bret = true;

	if (bret || changestate)
	{
		m_ch->CalcStatus(true);

		CNetMsg::SP rmsg(new CNetMsg);
		CharStatusMsg(rmsg, m_ch, changestate);

		m_ch->m_pArea->SendToCell(rmsg, m_ch, true);
	}

	return bret;
}

void CAssist::Apply()
{
	memset(&m_avAddition, 0, sizeof(m_avAddition));
	memset(&m_avRate, 0, sizeof(m_avRate));
	m_state = 0;
	m_help.Apply(m_ch, &m_avAddition, &m_avRate, &m_state);
	m_curse.Apply(m_ch, &m_avAddition, &m_avRate, &m_state);

	m_ch->ApplyAssistData(&m_avAddition, &m_avRate);
}

// 060317 : bs : SF_NOCANCEL �˻� �߰�

void CAssist::ClearAssist(bool bSend, bool bByStone, bool bHelp, bool bCurse, bool bNoCancelType)
{
	CAssistData* pAssist;
	CAssistData* pAssistNext;

	if(bHelp)
	{
		pAssistNext = m_help.m_head;
		while ((pAssist = pAssistNext))
		{
			pAssistNext = pAssistNext->m_next;
			// 060317 : bs : SF_NOCANCEL �˻�
			if (!bNoCancelType && (pAssist->m_proto->m_flag & SF_NOCANCEL))
				continue ;

			if (bByStone)
			{
				switch (pAssist->m_index)
				{
				case 671:		// �ϱ� ������ ����
				case 672:		// �߱� ������ ����
				case 673:		// ��� ������ ����
				case 674:		// ����� ����
					break;
				default:
					m_help.DelAssist(pAssist, bSend, m_ch, bNoCancelType);
					break;
				}
			}
			else
				m_help.DelAssist(pAssist, bSend, m_ch, bNoCancelType);
		}
	}
	if(bCurse)
	{
		pAssistNext = m_curse.m_head;
		while ((pAssist = pAssistNext))
		{
			pAssistNext = pAssistNext->m_next;
			if (bByStone)
			{
				switch (pAssist->m_index)
				{
				case 671:		// �ϱ� ������ ����
				case 672:		// �߱� ������ ����
				case 673:		// ��� ������ ����
				case 674:		// ����� ����
					break;
				default:
					m_curse.DelAssist(pAssist, bSend, m_ch, bNoCancelType);
					break;
				}
			}
			else
				m_curse.DelAssist(pAssist, bSend, m_ch, bNoCancelType);
		}
	}

	m_ch->CalcStatus(bSend);

	if (bSend)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		CharStatusMsg(rmsg, m_ch, 0);
		m_ch->m_pArea->SendToCell(rmsg, m_ch, true);
	}


}

void  CAssist::GetListString(bool bHelp, char* item, char* index, char* level, char* remain,
							 char* remainCount,
							 char* hit0, char* hit1, char* hit2)
{
	*item = *index = *level = *remain =
								  *remainCount =
									  *hit0 = *hit1 = *hit2 = '\0';

	CAssistData* p;

	if (bHelp)
		p = m_help.m_head;
	else
		p = m_curse.m_head;

	while (p)
	{
		bool bSkip = false;

		// 060227 : bs : ����ð� ��� ��ų�� t_assist�� ���� ����
		if (p->m_proto->m_flag & SF_ABSTIME)
			bSkip = true;
		// 060227 : bs : ����ð� ��� ��ų�� t_assist�� ���� ����

		if(p->m_proto->m_flag & SF_COMBO)
			bSkip = true;

#ifdef EVENT_PCBANG_2ND
		if(p->m_proto->m_index == 493 )
		{
			// PC�� ���� ���� ����
			bSkip = true;
		}
#endif // EVENT_PCBAG_2ND

		if( p->m_proto->m_index == 516 || p->m_proto->m_index == 2059)
		{
			// �Ǵн� ���� ���� ����
			bSkip = true;
		}

		// ��ũ�Ͻ� ��� ��ų(682)�� ���� ����
		if( p->m_proto->m_index == 682 )
		{
			bSkip = true;
		}

		if (!bSkip)
		{
			IntCat(item, p->m_index, true);
			IntCat(index, p->m_proto->m_index, true);
			IntCat(level, p->m_level, true);
			IntCat(remain, p->m_remain, true);
			IntCat(remainCount, p->m_remainCount, true);
			IntCat(hit0, (p->m_bHit[0]) ? 1 : 0, true);
			IntCat(hit1, (p->m_bHit[1]) ? 1 : 0, true);
			IntCat(hit2, (p->m_bHit[2]) ? 1 : 0, true);
		}

		p = p->m_next;
	}
}


void  CAssist::GetListString(bool bHelp, std::string& item, std::string& index, std::string& level, std::string& remain,
							 std::string& remainCount,
							 std::string& hit0, std::string& hit1, std::string& hit2)
{
	item = "";
	index = "";
	level = "";
	remain = "";
	remainCount = "";
	hit0 = "";
	hit1 = "";
	hit2 = "";

	CAssistData* pAssist;

	if (bHelp)
		pAssist = m_help.m_head;
	else
		pAssist = m_curse.m_head;

	while (pAssist)
	{
		bool bSkip = false;

		// 060227 : bs : ����ð� ��� ��ų�� t_assist�� ���� ����
		if (pAssist->m_proto->m_flag & SF_ABSTIME)
			bSkip = true;
		// 060227 : bs : ����ð� ��� ��ų�� t_assist�� ���� ����

		if(pAssist->m_proto->m_flag & SF_COMBO)
			bSkip = true;

#ifdef EVENT_PCBANG_2ND
		if(pAssist->m_proto->m_index == 493 )
		{
			// PC�� ���� ���� ����
			bSkip = true;
		}
#endif // EVENT_PCBAG_2ND

		if( pAssist->m_proto->m_index == 516 || pAssist->m_proto->m_index == 2059)
		{
			// �Ǵн� ���� ���� ����
			bSkip = true;
		}
		
		// ��ũ�Ͻ� ��� ��ų(682)�� ���� ����
		if( pAssist->m_proto->m_index == 682 )
		{
			bSkip = true;
		}

		if (!bSkip)
		{
			item += boost::str(boost::format(" %d") % pAssist->m_index);
			index += boost::str(boost::format(" %d") % pAssist->m_proto->m_index);
			level += boost::str(boost::format(" %d") % pAssist->m_level);
			remain += boost::str(boost::format(" %d") % pAssist->m_remain);
			remainCount += boost::str(boost::format(" %d") % pAssist->m_remainCount);
			hit0 += boost::str(boost::format(" %d") % ((pAssist->m_bHit[0]) ? 1 : 0));
			hit1 += boost::str(boost::format(" %d") % ((pAssist->m_bHit[1]) ? 1 : 0));
			hit2 += boost::str(boost::format(" %d") % ((pAssist->m_bHit[2]) ? 1 : 0));
		}

		pAssist = pAssist->m_next;
	}
}

void CAssist::AppendAssistToNetMsg(CNetMsg::SP& msg)
{
	CAssistData* p;

	RefMsg(msg) << m_state
				<< (char)GetAssistCount();

	p = m_help.m_head;
	while (p)
	{
		RefMsg(msg) << p->m_index
					<< p->m_proto->m_index
					<< (char)p->m_level
					<< p->m_remain
					<< p->m_remainCount;

		p = p->m_next;
	}

	p = m_curse.m_head;
	while (p)
	{
		RefMsg(msg) << p->m_index
					<< p->m_proto->m_index
					<< (char)p->m_level
					<< p->m_remain
					<< p->m_remainCount;

		p = p->m_next;
	}
}

void CAssist::AppendAssistToNetStructMsg(struct tag_assistinfo& info)
{
	int itemcount = 0;
	int listcount = 0;
	
	bool loaddroplist = false;
		if (m_ch->m_type == MSG_CHAR_NPC && !loaddroplist)
		{
			CNPC* pNpc = TO_NPC(m_ch);
			int i;
			for(i = 0; i < MAX_NPC_DROPITEM && !(pNpc->m_proto->CheckFlag(NPC_CASTLE_GUARD | NPC_CASTLE_TOWER)); i++)
			{
				if (pNpc->m_proto->m_item[i] == -1 )
					continue;

				int itemindex = pNpc->m_proto->m_item[i];

				if(itemindex < 0)
					continue;


					info.list[listcount].index = itemindex;
					info.list[listcount].dbIndex = 249;
					info.list[listcount].level = -1;
					info.list[listcount].remain = -1;
					info.list[listcount].remainCount = -1;
					++itemcount;
					++listcount;
			}

			int j;
			for(j = 0; j < MAX_NPC_DROPITEM; j++)
			{
				if (pNpc->m_proto->m_dropallitem[j] < 1 )
					continue;

				int itemindex = pNpc->m_proto->m_dropallitem[j];

				if(itemindex < 0)
					continue;

					info.list[listcount].index = itemindex;
					info.list[listcount].dbIndex = 249;
					info.list[listcount].level = -1;
					info.list[listcount].remain = -1;
					info.list[listcount].remainCount = -1;
					++itemcount;
					++listcount;
				
			}

			vec_raiddropdata_t::iterator it = pNpc->m_proto->m_listRaidDrop.begin();
			vec_raiddropdata_t::iterator endit = pNpc->m_proto->m_listRaidDrop.end();
			for(; it != endit; ++it)
			{
				RAIDDROPDATA& rdd = *(it);
				if (rdd.itemindex > 0 && rdd.itemindex != NAS_ITEM_DB_INDEX)
				{
					if(rdd.itemindex == -1)
						continue;
					
					int itemindex = rdd.itemindex;

				   if(itemindex < 0)
					continue;

						info.list[listcount].index = itemindex;
						info.list[listcount].dbIndex = 249;
						info.list[listcount].level = -1;
						info.list[listcount].remain = -1;
						info.list[listcount].remainCount = -1;
						++itemcount;
						++listcount;
				}
			}
			loaddroplist = true;
		}
	
	info.state = m_state;
	info.count = GetAssistCount();

    if(itemcount > 0)
	info.count += itemcount;

	if (info.count == 0)
		return;

	//int listcount = 0;
	CAssistData* p = m_help.m_head;
	while (p)
	{
		info.list[listcount].index = p->m_index;
		info.list[listcount].dbIndex = p->m_proto->m_index;
		info.list[listcount].level = p->m_level;
		info.list[listcount].remain = p->m_remain;
		info.list[listcount].remainCount = p->m_remainCount;
		++listcount;

		p = p->m_next;
	}

	p = m_curse.m_head;
	while (p)
	{
		info.list[listcount].index = p->m_index;
		info.list[listcount].dbIndex = p->m_proto->m_index;
		info.list[listcount].level = p->m_level;
		info.list[listcount].remain = p->m_remain;
		info.list[listcount].remainCount = p->m_remainCount;
		++listcount;

		p = p->m_next;
	}
}

bool CAssist::Find(int magicindex, int magiclevel)
{
	CAssistData* p;
	const CSkillLevelProto* slp;
	int i;

	p = m_help.m_head;
	while (p)
	{
		slp = p->m_proto->Level(p->m_level);
		if (slp)
		{
			i = 0;
			while (i < MAX_SKILL_MAGIC)
			{
				if (slp->m_magic[i] && slp->m_magic[i]->m_index == magicindex && slp->m_magicLevel[i] >= magiclevel)
					return true;
				i++;
			}
		}
		p = p->m_next;
	}

	p = m_curse.m_head;
	while (p)
	{
		slp = p->m_proto->Level(p->m_level);
		if (slp)
		{
			i = 0;
			while (i < MAX_SKILL_MAGIC)
			{
				if (slp->m_magic[i] && slp->m_magic[i]->m_index == magicindex && slp->m_magicLevel[i] >= magiclevel)
					return true;
				i++;
			}
		}
		p = p->m_next;
	}

	return false;
}

void CAssist::CancelSleep()
{
	CureAssist(MST_ASSIST_SLEEP, 99);
}
void CAssist::CancelMantle()
{
	CureAssist(MST_ASSIST_MANTLE, 99);
}

void CAssist::CureAssist(int flag)
{
	CAssistData* p;
	CAssistData* pNext;

	pNext = m_help.m_head;
	while((p = pNext))
	{
		pNext = pNext->m_next;
		if(p->m_proto->m_flag & flag)
			m_help.DelAssist(p, true, m_ch, true);
	}

	pNext = m_curse.m_head;
	while((p = pNext))
	{
		pNext = pNext->m_next;
		if(p->m_proto->m_flag & flag)
			m_curse.DelAssist(p, true, m_ch, true);
	}
}

void CAssist::CureAssist(int type, int level)
{
	CAssistData* p;
	CAssistData* pNext;
	const CSkillLevelProto* slp;
	const CMagicProto* mp;
	int i;

	pNext = m_help.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		slp = p->m_proto->Level(p->m_level);
		if (slp)
		{
			i = 0;
			while (i < MAX_SKILL_MAGIC)
			{
				mp = slp->m_magic[i];
				if (mp && mp->m_type == MT_ASSIST && mp->m_subtype == type && slp->m_magicLevel[i] <= level)
				{
					m_help.DelAssist(p, true, m_ch, true);
					break;
				}
				i++;
			}
		}
	}

	pNext = m_curse.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		slp = p->m_proto->Level(p->m_level);
		if (slp)
		{
			i = 0;
			while (i < MAX_SKILL_MAGIC)
			{
				mp = slp->m_magic[i];
				if (mp && mp->m_type == MT_ASSIST && mp->m_subtype == type && slp->m_magicLevel[i] <= level)
				{
					m_curse.DelAssist(p, true, m_ch, true);
					break ;
				}
				i++;
			}
		}
	}
}

void CAssist::CureOtherAssist(int type, int subtype, int level)
{
	CAssistData* p;
	CAssistData* pNext;
	const CSkillLevelProto* slp;
	const CMagicProto* mp;
	int i;

	pNext = m_help.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		slp = p->m_proto->Level(p->m_level);
		if (slp)
		{
			i = 0;
			while (i < MAX_SKILL_MAGIC)
			{
				mp = slp->m_magic[i];
				if (mp && mp->m_type == type && mp->m_subtype == subtype && slp->m_magicLevel[i] <= level)
				{
					m_help.DelAssist(p, true, m_ch, true);
					break;
				}
				i++;
			}
		}
	}

	pNext = m_curse.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		slp = p->m_proto->Level(p->m_level);
		if (slp)
		{
			i = 0;
			while (i < MAX_SKILL_MAGIC)
			{
				mp = slp->m_magic[i];
				if (mp && mp->m_type == type && mp->m_subtype == subtype && slp->m_magicLevel[i] <= level)
				{
					m_curse.DelAssist(p, true, m_ch, true);
					break ;
				}
				i++;
			}
		}
	}
}

void CAssist::CancelInvisible()
{
	CureAssist(MST_ASSIST_INVISIBLE, 99);
}

void CAssist::CheckApplyConditions()
{
	m_help.CheckApplyConditions(m_ch);
	m_curse.CheckApplyConditions(m_ch);
}

void CAssistList::CheckApplyConditions(CCharacter* ch)
{
	CAssistData* p;
	CAssistData* pNext;
//	bool bFinish = false;

//	while (!bFinish)
//	{
//		bFinish = true;
	pNext = m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;

		if (!ch->CanApplySkill(p->m_proto, p->m_proto->Level(p->m_level)))
		{
			DelAssist(p, true, ch, false);
//				bFinish = false;
		}
	}
//	}
}

int CAssist::FindByType(int type, int subtype, bool* outHelp, CAssistData** outData)
{
	CAssistData* p;
	CAssistData* pNext;
	const CSkillLevelProto* slp;
	const CMagicProto* mp;
	int i;

	pNext = m_help.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		slp = p->m_proto->Level(p->m_level);
		if (slp)
		{
			i = 0;
			while (i < MAX_SKILL_MAGIC)
			{
				mp = slp->m_magic[i];
				if (mp && mp->m_type == type && mp->m_subtype == subtype)
				{
					if (outHelp)
						*outHelp = true;
					if (outData)
						*outData = p;
					return slp->m_magicLevel[i];
				}
				i++;
			}
		}
	}

	pNext = m_curse.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		slp = p->m_proto->Level(p->m_level);
		if (slp)
		{
			i = 0;
			while (i < MAX_SKILL_MAGIC)
			{
				mp = slp->m_magic[i];
				if (mp && mp->m_type == type && mp->m_subtype == subtype)
				{
					if (outHelp)
						*outHelp = false;
					if (outData)
						*outData = p;
					return slp->m_magicLevel[i];
				}
				i++;
			}
		}
	}

	if (outHelp)
		*outHelp = false;
	if (outData)
		*outData = NULL;
	return 0;
}

int CAssist::GetSummonNpcIndex()
{
	CAssistData* p;
	CAssistData* pNext;
	const CSkillLevelProto* slp;
	const CMagicProto* mp;
	int i;

	pNext = m_help.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		slp = p->m_proto->Level(p->m_level);
		if (slp)
		{
			i = 0;
			while (i < MAX_SKILL_MAGIC)
			{
				mp = slp->m_magic[i];
				if (mp && mp->m_type == MT_ASSIST && mp->m_subtype == MST_ASSIST_PARASITE)
				{
					return mp->m_levelproto[slp->m_magicLevel[0]-1]->GetSummonNpcIndex();
				}
				i++;
			}
		}
	}

	pNext = m_curse.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		slp = p->m_proto->Level(p->m_level);
		if (slp)
		{
			i = 0;
			while (i < MAX_SKILL_MAGIC)
			{
				mp = slp->m_magic[i];
				if (mp && mp->m_type == MT_ASSIST && mp->m_subtype == MST_ASSIST_PARASITE)
				{
					return mp->m_levelproto[slp->m_magicLevel[0]-1]->GetSummonNpcIndex();
				}
				i++;
			}
		}
	}

	return 0;
}

void CAssist::CancelFear()
{
	CureAssist(MST_ASSIST_FEAR, 99);
}

void CAssist::CancelFakeDeath()
{
	CureAssist(MST_ASSIST_FAKEDEATH, 99);
}

void CAssist::CureByItemIndex(int itemindex)
{
	CAssistData* p;
	CAssistData* pNext;

	pNext = m_help.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		if (p->m_index != -1 && p->m_index == itemindex)
			m_help.DelAssist(p, true, m_ch, true);
	}

	pNext = m_curse.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		if (p->m_index != -1 && p->m_index == itemindex)
			m_curse.DelAssist(p, true, m_ch, true);
	}
}

void CAssist::CureAllRecovery(CPC* ch)
{
	ch->m_assist.CureBySkillIndex(1165);
	ch->m_assist.CureBySkillIndex(347);
	ch->m_assist.CureByItemIndex(1281);
	ch->m_assist.CureByItemIndex(1282);
	ch->m_assist.CureByItemIndex(4967);
	ch->m_assist.CureByItemIndex(6370);
}

void CAssist::CureBySkillIndex(int nSkillIndex)
{
	CAssistData* p;
	CAssistData* pNext;

	pNext = m_help.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		if (p->m_proto && p->m_proto->m_index == nSkillIndex)
			m_help.DelAssist(p, true, m_ch, true);
	}

	pNext = m_curse.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		if (p->m_proto && p->m_proto->m_index == nSkillIndex)
			m_curse.DelAssist(p, true, m_ch, true);
	}
}

bool CAssist::FindByItemIndex(int itemindex, CAssistData** outData)
{
	CAssistData* p;
	CAssistData* pNext;

	pNext = m_help.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		if (p->m_index != -1 && p->m_index == itemindex)
		{
			if (outData)
				*outData = p;
			return true;
		}
	}

	pNext = m_curse.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		if (p->m_index != -1 && p->m_index == itemindex)
		{
			if (outData)
				*outData = p;
			return true;
		}
	}

	return false;
}

int CAssist::FindBySkillIndex(int skillindex)
{
	CAssistData* p;
	CAssistData* pNext;

	pNext = m_help.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		if (p->m_proto->m_index == skillindex)
			return p->m_level;
	}

	pNext = m_curse.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		if (p->m_proto->m_index == skillindex)
			return p->m_level;
	}

	return 0;
}

// 060227 : bs : ����ð� ��� ����ȿ�� ����Ʈ
int CAssist::GetABSTimeTypeList(int* nAssistABSItemIndex, int* nAssistABSSkillIndex, int* nAssistABSSkillLevel, char* nAssistABSHit0, char* nAssistABSHit1, char* nAssistABSHit2, int* nAssistABSEndTime)
{
	int ret = 0;

	CAssistData* p;

	p = m_help.m_head;
	while (p)
	{
		if (p->m_proto && (p->m_proto->m_flag & SF_ABSTIME))
		{
			if (nAssistABSItemIndex)
			{
#ifdef EVENT_PCBANG_2ND
				if(p->m_proto->m_index != 493)
				{
					// PC�� ���� ���� ����
#endif // EVENT_PCBANG_2ND

					if( p->m_proto->m_index != 516 || p->m_proto->m_index != 2059)
					{
						// �Ǵн� ���� ���� ����

						nAssistABSItemIndex[ret] = p->m_index;
						nAssistABSSkillIndex[ret] = p->m_proto->m_index;
						nAssistABSSkillLevel[ret] = p->m_level;
						nAssistABSHit0[ret] = p->m_bHit[0];
						nAssistABSHit1[ret] = p->m_bHit[1];
						nAssistABSHit2[ret] = p->m_bHit[2];
						nAssistABSEndTime[ret] = gserver->getNowSecond() + (p->m_remain / PULSE_ASSIST_CHECK);

					}

#ifdef EVENT_PCBANG_2ND
				}
#endif // EVENT_PCBAG_2ND
			}
			ret++;
		}
		p = p->m_next;
	}

	p = m_curse.m_head;
	while (p)
	{
		if (p->m_proto && (p->m_proto->m_flag & SF_ABSTIME))
		{
			if (nAssistABSItemIndex)
			{
#ifdef EVENT_PCBAG_2ND
				if(p->m_proto->m_index != 493)
				{
					// PC�� ���� ���� ����
#endif // EVENT_PCBAG_2ND

					//			if( p->m_proto->m_index != 516 )
					//			{	// �Ǵн� ���� ���� ����

					nAssistABSItemIndex[ret] = p->m_index;
					nAssistABSSkillIndex[ret] = p->m_proto->m_index;
					nAssistABSSkillLevel[ret] = p->m_level;
					nAssistABSHit0[ret] = p->m_bHit[0];
					nAssistABSHit1[ret] = p->m_bHit[1];
					nAssistABSHit2[ret] = p->m_bHit[2];
					nAssistABSEndTime[ret] = gserver->getNowSecond() + (p->m_remain / PULSE_ASSIST_CHECK);

#ifdef EVENT_PCBAG_2ND
				}
#endif // EVENT_PCBAG_2ND
			}
			ret++;
		}
		p = p->m_next;
	}

	return ret;
}
// 060227 : bs : ����ð� ��� ����ȿ�� ����Ʈ

void CAssist::CancelDespair()
{
	CureAssist(MST_ASSIST_DESPAIR, 99);
}

void CAssist::CancelManaScreen()
{
	CureAssist(MST_ASSIST_MANASCREEN, 99);
}

void CAssist::CancelBless()
{
	CureAssist(MST_ASSIST_BLESS, 99);
}

void CAssist::DecreaseCount(int type, int subtype)
{
	CAssistData* p;
	CAssistData* pNext;
	const CSkillProto* sp;
	const CSkillLevelProto* slp;
	const CMagicProto* mp;
	int i;

	pNext = m_help.m_head;
	while((p = pNext))
	{
		pNext = pNext->m_next;

		sp = p->m_proto;
		if (sp == NULL)
			continue;

		slp = sp->Level(p->m_level);
		if (slp == NULL)
			continue;

		for (i = 0; i < MAX_SKILL_MAGIC; i++)
		{
			if (!p->m_bHit[i])
				continue;

			mp = slp->m_magic[i];
			if (mp == NULL)
				continue;

			if (mp->m_type == type && mp->m_subtype == subtype)
			{
				p->m_remainCount --;
				break;
			}
		}

		if (i >= MAX_SKILL_MAGIC)
			continue;

		if (p->m_remainCount <= 0)
			m_help.DelAssist(p, true, m_ch, true);

		{
			CNetMsg::SP rmsg(new CNetMsg);
			AssistModifyMsg(rmsg, m_ch, p->m_index, sp->m_index,
							p->m_level, p->m_remain, p->m_remainCount);
			m_ch->m_pArea->SendToCell(rmsg, m_ch, true);
		}
	}

	pNext = m_curse.m_head;
	while((p = pNext))
	{
		pNext = pNext->m_next;

		sp = p->m_proto;
		if (sp == NULL)
			continue;

		slp = sp->Level(p->m_level);
		if (slp == NULL)
			continue;

		for (i = 0; i < MAX_SKILL_MAGIC; i++)
		{
			if (!p->m_bHit[i])
				continue;

			mp = slp->m_magic[i];
			if (mp == NULL)
				continue;

			if (mp->m_type == type && mp->m_subtype == subtype)
			{
				p->m_remainCount --;
				break;
			}
		}

		if (i >= MAX_SKILL_MAGIC)
			continue;

		if (p->m_remainCount <= 0)
			m_curse.DelAssist(p, true, m_ch, true);

		{
			CNetMsg::SP rmsg(new CNetMsg);
			AssistModifyMsg(rmsg, m_ch, p->m_index, sp->m_index,
							p->m_level, p->m_remain, p->m_remainCount);
			m_ch->m_pArea->SendToCell(rmsg, m_ch, true);
		}
	}
}

void CAssist::CureByPetSkill()
{
	CAssistData* p;
	CAssistData* pNext;

	pNext = m_help.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		if (p->m_proto && (p->m_proto->getJob() == JOB_PET || p->m_proto->getJob() == JOB_APET))
			m_help.DelAssist(p, true, m_ch, true);
	}

	pNext = m_curse.m_head;
	while ((p = pNext))
	{
		pNext = pNext->m_next;
		if (p->m_proto && (p->m_proto->getJob() == JOB_PET || p->m_proto->getJob() == JOB_APET))
			m_curse.DelAssist(p, true, m_ch, true);
	}
}

unsigned char CAssist::getAttrAtt()
{
	if(this->m_avAddition.attratt_item > 0)
	{
		return m_avAddition.attratt_item;
	}
	else if(GET_AT_ATT(this->m_avAddition.attratt) > 0)
	{
		return m_avAddition.attratt;
	}
	else
	{
		return AT_NONE;
	}
}

unsigned char CAssist::getAttrDef()
{
	if(this->m_avAddition.attrdef_item > 0)
	{
		return m_avAddition.attrdef_item;
	}
	else if(this->m_avAddition.attrdef > 0)
	{
		return m_avAddition.attrdef;
	}
	else
	{
		return AT_NONE;
	}
}
