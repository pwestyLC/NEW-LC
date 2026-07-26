#include "stdhdrs.h"

#include "Server.h"
#include "Character.h"
#include "CmdMsg.h"
#include "Log.h"
#include "doFunc.h"
#include "../ShareLib/packetType/ptype_old_do_item.h"

CPet::CPet(CPC* owner, int index, char petTypeGrade, int level) : CCharacter()
{
	// ���� 1�� ���·� �����
	m_type = MSG_CHAR_PET;
	m_index = index;
	m_level = level;
	m_exp = 0;

	m_owner = owner;
	m_petTypeGrade = petTypeGrade;
	m_hungry = PET_DEFAULT_HUNGRY;
	m_pulseHungry = 0;
	m_sympathy = PET_DEFAULT_SYMPATHY;
	m_pulseSympathy = gserver->m_pulse;
	m_petStashSeconds = gserver->m_nowseconds;
	m_petStashHungrySeconds = gserver->m_nowseconds;
	m_abilityPoint = 0;
	m_pulseExpUp = 0;
	m_petColorType = 0;
	m_nTurnToNpcIndex = 0;
	m_nTurnToNpcSize = 10;

	m_bSummon = false;
	m_bMount = false;
	m_wasnear = true;

	// 060221 : bs : �� ��� �ð�
	m_nRemainRebirth = 0;

	InitStat();

	m_prevPet = NULL;
	m_nextPet = NULL;
}

CPet::~CPet()
{
	DelAttackList(this);
}

bool CPet::UpdateSympathyPoint(bool bnear)
{
	int oldval = GetSympathyPoint();
	//���� ��â���� �ð��� �ִ� ���¶��
	if(this->GetOwner()->m_petStashManager.GetPetItemByPlus(this->m_index))
	{
		if(m_petStashSeconds + (60 * 60 /*sec*/) < gserver->m_nowseconds)
		{
			m_petStashSeconds = gserver->m_nowseconds;
			++m_sympathy;
			this->GetOwner()->m_petStashManager.UpdatePetData(this->m_index);
			//â�� �޽��� ����Ļ��¸� �����ϰ� �����Ѵ�.
		}
	}
	else if (IsWearing())
	{
		// 5�� + �г�Ƽ
		int needTime = PULSE_PET_SYMPATHY_INCREASE;
		if (m_owner->m_level < m_level)
			needTime += (m_level - m_owner->m_level) / 2;
		if (m_pulseSympathy + needTime > gserver->m_pulse)
			return false;

		m_pulseSympathy = gserver->m_pulse;

		// ����� : 5�и��� ������ 1����Ʈ �϶� 050309: bw
		if (!IsActive())
		{
			m_sympathy--;
			if( m_sympathy < 0 )
				m_sympathy = 0;

			if (m_sympathy == oldval)
				return false;
			else
				return true;
		}

		// 050309: bw
		// ��� ������ ��ó�� ���� ������ ������ ��� ����
		if( !bnear )
			return false;

		m_sympathy++;

		if (m_sympathy > PET_MAX_SYMPATHY)
			m_sympathy = PET_MAX_SYMPATHY;
	}
	else
	{
		// 1�ð�
		if (m_pulseSympathy + PULSE_PET_SYMPATHY_DECREASE > gserver->m_pulse)
			return false;

		m_pulseSympathy = gserver->m_pulse;

		m_sympathy--;

		if (m_sympathy < 0)
			m_sympathy = 0;
	}

	if (m_sympathy == oldval)
		return false;

	return true;
}

bool CPet::IncreaseHungryPoint(int val)
{
	int oldval = GetHungryPoint();

	m_hungry += val;

	if (m_hungry > PET_MAX_HUNGRY)
		m_hungry = PET_MAX_HUNGRY;

	if (m_hungry == oldval)
		return false;

	return true;
}

bool CPet::DecreaseHungryPoint()
{
	// ó���� �׳� �޽��� �����ϰ� ���� || ���� ��â���� �ִ� ��쿡�� ����
	if (m_pulseHungry == 0 || this->GetOwner()->m_petStashManager.GetPetItemByPlus(this->m_index))
	{
		m_pulseHungry = gserver->m_pulse;
		return false;
	}

	int oldval = GetHungryPoint();
	if (IsWearing())
	{
		// 5�� + �г�Ƽ
		if (m_pulseHungry + PULSE_PET_HUNGRY_DECREASE > gserver->m_pulse)
			return false;

		m_pulseHungry = gserver->m_pulse;

		m_hungry -= GetUnitForHungry();

		if (m_hungry < 0)
			m_hungry = 0;
	}

	if (m_hungry == oldval)
		return false;

	return true;
}

void CPet::InitStat()
{
	m_hp = m_maxHP = PET_MAX_HP;
	m_mp = m_maxMP = 0;

	m_str = m_dex = m_int = m_con = 1;

	m_walkSpeed = PET_DEFAULT_RUNSPEED;
	//m_runSpeed = PET_DEFAULT_RUNSPEED;
	SetRunSpeed(PET_DEFAULT_RUNSPEED);

	if (m_level < PET_ADULT_LEVEL)
		m_petTypeGrade = (m_petTypeGrade & ~PET_GRADE_MASK) | PET_GRADE_CHILD;
	else if (GetPetGrade() == PET_GRADE_CHILD)
		m_petTypeGrade = (m_petTypeGrade & ~PET_GRADE_MASK) | PET_GRADE_ADULT;

	if (GetPetGrade() == PET_GRADE_MOUNT)
	{
		//m_runSpeed = 15.0f;
		SetRunSpeed(15.0f);
		m_walkSpeed = 10.0f;
	}
}

bool CPet::AddExp()
{
	// LOG_INFO("Pet");

	int addexp = 0;
	if (m_owner == NULL)
		return false;

	if (m_level >= PET_MAX_LEVEL)
		return false;

	if (IsMountType())
		return false;

	if (!IsWearing())
		return false;

	if(this->GetHungryPoint() <= 0)
		return false;

	// LOG_INFO("Pet Check pulse");

	// ���� ���� ó���̰ų� �� 3�ʸ���
	if (m_pulseExpUp == 0 || m_pulseExpUp + PULSE_REAL_SEC * 3 < gserver->m_pulse)
	{
		m_pulseExpUp = gserver->m_pulse;

		// �����ڰ� ���� ���̰�
		if (IsWearing())
		{
			// LOG_INFO("Pet Wearing: %d %d %d", 
			// (int)m_owner->IsCombatMode(), 
			// (int)((gserver->m_pulse - m_owner->m_pulseLastAttackSkill) < PULSE_ATTACKMODE_DELAY),
			// (int)m_owner->m_bNotMiss);

			// �����ڰ� ���� ��
			if (m_owner->IsCombatMode()
					&& (gserver->m_pulse - m_owner->m_pulseLastAttackSkill) < PULSE_ATTACKMODE_DELAY
					&& m_owner->m_bNotMiss)
			{
				//p2 pet multiplier config
			CLCString sP1PetMult(15);//Reza 
	int dwP1PetMult = 0;//Reza 
			sP1PetMult.Format("P1XPONHIT");
			
			if(  strcmp(gserver->m_config.Find("Rates", (const char*)sP1PetMult),"")!= 0 )
			{
				
				dwP1PetMult = atoi(gserver->m_config.Find("Rates", (const char*)sP1PetMult));
			}
		//Reza 
				addexp = dwP1PetMult;
#ifdef DOUBLE_PET_EXP
				if( gserver->m_bDoublePetExpEvent == true )
					addexp = addexp * gserver->m_PetExpPercent / 100;
#endif // DOUBLE_PET_EXP

				if( m_owner->m_assist.m_avAddition.hcCashPetExpUp_2358 == true )
					m_exp += 2 * addexp;
				else if( m_owner->m_assist.m_avAddition.hcCashPetExpUp_2359 == true )
					m_exp += 3 * addexp;
				else if( m_owner->m_assist.m_avAddition.hcCashPetExpUp_12077 == true )
					m_exp += 6 * addexp;
				else
					m_exp += addexp;

				m_owner->m_bNotMiss = false;

				// LOG_INFO("PetExp %d", m_exp);

				if (m_exp >= GetNeedExp())
				{
					m_exp -= GetNeedExp();
					m_level++;
					m_abilityPoint++;

					// TODO : petlog
					GAMELOG << init("PET LEVEL UP", m_owner)
							<< "OWNER" << delim
							<< m_owner->m_index << delim
							<< m_owner->GetName() << delim
							<< "PET" << delim
							<< m_index << delim
							<< GetPetType() << delim
							<< GetPetGrade() << delim
							<< "LEVEL" << delim
							<< m_level << delim
							<< "AP" << delim
							<< m_abilityPoint
							<< end;

					LevelUp();
				}

				return true;
			}
		}
	}
	return false;
}

void CPet::Appear(bool bIncludeOwner)
{
	if (m_owner == NULL)
		return ;

	if (IsSummon())
		return ;

	if (IsMountType())
		return ;

	CArea* area = m_owner->m_pArea;
	if (area == NULL)
		return ;

	// ��ȯ�� �� �ִ� ���϶�
	if (!area->m_zone->m_bCanSummonPet)
	{
		CNetMsg::SP rmsg(new CNetMsg);
		SysMsg(rmsg, MSG_SYS_PET_CANT_SUMMON);
		SEND_Q(rmsg, GetOwner()->m_desc);
		return ;
	}

	// ���� �ֱ�
	m_pZone = area->m_zone;
	m_pArea = area;
	m_pos = m_owner->m_pos;
	int cx, cz;
	area->PointToCellNum(GET_X(this), GET_Z(this), &cx, &cz);
	area->CharToCell(this, GET_YLAYER(this), cx, cz);

	{
		// ��Ÿ���� �˸�
		CNetMsg::SP rmsg(new CNetMsg);
		AppearMsg(rmsg, this, true);
		area->SendToCell(rmsg, this, bIncludeOwner);
	}

	m_bSummon = true;
}

void CPet::Disappear()
{
	CArea* area = m_pArea;
	if (area == NULL)
		return ;

	if (!IS_IN_CELL(this))
		return ;

	if (!IsSummon())
		return ;

	// ���� ����Ʈ �����
	DelAttackList(this);

	{
		// ������� �˸���
		CNetMsg::SP rmsg(new CNetMsg);
		DisappearMsg(rmsg, this);
		area->SendToCell(rmsg, this, true);
	}

	// ������ ����
	area->CharFromCell(this, true);
	m_pZone = NULL;
	m_pArea = NULL;

	m_bSummon = false;
}

CSkill* CPet::FindSkill(int skillindex)
{
	return m_skillList.Find(skillindex);
}

void CPet::AddSkill(CSkill*& skill)
{
	m_skillList.Add(skill);
}

bool CPet::ResetSkill()
{
	int spendPoint = 0;
	void* p = m_skillList.GetHeadPosition();
	while (p)
	{
		CSkill* skill = m_skillList.GetNext(p);
		if (skill)
		{
			const CSkillProto* proto = skill->m_proto;
			if (proto == NULL)
				return false;
			int i;
			for (i = 1; i <= skill->m_level; i++)
			{
				const CSkillLevelProto* levelproto = proto->Level(i);
				if (levelproto == NULL)
					return false;
				spendPoint += levelproto->m_learnSP;
			}
		}
	}

	m_skillList.Clear();
	IncreaseAbilityPoint(spendPoint);

	return true;
}

void CPet::Mount(bool bMount)
{
	// Ż�� �ִ� ���̰�
	if (!IsMountType())
		return ;

	// Ÿ�� ��Ÿ���� ���°� ����� �ٸ���
	if (IsMount() == bMount)
		return ;

	// ������ �ְ�
	if (!GetOwner() || GetOwner()->m_pZone == NULL)
		return ;

	{
		CNetMsg::SP rmsg(new CNetMsg);

		if (bMount)
		{
			// Ż �� �ִ� ���϶�
			if (!GetOwner()->m_pZone->m_bCanMountPet)
			{
				CNetMsg::SP tmsg(new CNetMsg);
				SysMsg(tmsg, MSG_SYS_PET_CANT_MOUNT);
				SEND_Q(tmsg, GetOwner()->m_desc);
				return ;
			}

			// Ÿ��
			m_bMount = true;
			ExPetMountMsg(rmsg, GetOwner()->m_index, GetPetTypeGrade());

			while (GetOwner()->m_elementalList)
				GetOwner()->UnsummonElemental(GetOwner()->m_elementalList);
		}
		else
		{
			// ������
			m_bMount = false;
			ExPetMountMsg(rmsg, GetOwner()->m_index, 0);
		}
		RefMsg(rmsg) << m_petColorType;

		GetOwner()->m_pArea->SendToCell(rmsg, GetOwner(), false);
	}

	GetOwner()->m_bChangeStatus = true;
}

bool CPet::IncreaseSympathyPoint(int val)
{
	int oldval = m_sympathy;
	m_sympathy += val;

	if (m_sympathy > PET_MAX_SYMPATHY)
		m_sympathy = PET_MAX_SYMPATHY;

	return (m_sympathy != oldval);
}
 //new2022
#ifdef PET_BUFF_ALL_SYSTEM
void CPet::ApplyAllBuffs()
{
	void* p = m_skillList.GetHeadPosition();
	while (p)
	{
		CSkill* skill = m_skillList.GetNext(p);
		if (skill)
		{
			const CSkillProto* proto = skill->m_proto;
			if (proto == NULL)
				return;
			int i;
			for (i = 1; i <= skill->m_level; i++)
			{
				const CSkillLevelProto* levelproto = proto->Level(i);
				if (levelproto == NULL)
					return;
				bool bApply = false;
				ApplySkill(m_owner, m_owner, skill, -1, bApply);
			}
		}
	}
}
#endif
 //new2022//
void CPet::LevelUp()
{
	if (m_owner == NULL)
		return ;

	InitStat();

	if (IsMount())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ExPetLevelupMsg(rmsg, this);
		m_owner->m_pArea->SendToCell(rmsg, m_owner, true);
	}
	else if (IsSummon())
	{
		CNetMsg::SP rmsg(new CNetMsg);
		ExPetLevelupMsg(rmsg, this);
		m_pArea->SendToCell(rmsg, this, true);
	}

	const int nHorseStartIndex = 0;		// ���̺����� �� ��ų ���� �ε���
	const int nHorseCount = 3;			// ���̺����� �� ��ų ����
	const int nDragonStartIndex = 3;	// ���̺����� �巡�� ��ų ���� �ε���
	const int nDragonCount = 5;			// ���̺����� �� ��ų ����
	const int nAutoLearn = nDragonStartIndex + nDragonCount;
	const int autoTable[nAutoLearn][2] =
	{
		// ��
		{271, 4},		// ���� ���� : ����4
		{272, 8},		// �޹��� : ����8
		{273, 12},		// ������ : ����12

		// ��
		{284, 3},		// �ξ� : ����3
		{285, 6},		// �ֱ� : ����6
		{286, 9},		// ������ : ����9
		{287, 12},		// �һձ� : ����12
		{288, 15}		// ���� : ����15
	};

	if( GetPetGrade() != PET_GRADE_MOUNT )
	{
		// �ڵ�����
		int nStartIndex = nAutoLearn + 1;
		int nCount = 0;
		if (GetPetType() == PET_TYPE_HORSE
				|| GetPetType() == PET_TYPE_BLUE_HORSE
				|| GetPetType() == PET_TYPE_UNKOWN_HORSE)
		{
			nStartIndex = nHorseStartIndex;
			nCount = nHorseCount;
		}
		else if (GetPetType() == PET_TYPE_DRAGON
				 || GetPetType() == PET_TYPE_PINK_DRAGON
				 || GetPetType() == PET_TYPE_UNKOWN_DRAGON )
		{
			nStartIndex = nDragonStartIndex;
			nCount = nDragonCount;
		}

		CSkill* skill = NULL;

		int i;
		for (i = nStartIndex; i < nAutoLearn && i < nStartIndex + nCount; i++)
		{
			if (m_level >= autoTable[i][1])
			{
				skill = FindSkill(autoTable[i][0]);
				if (skill == NULL)
				{
					skill = gserver->m_skillProtoList.Create(autoTable[i][0]);
					if (skill)
					{
						// ���� �α�
						// TODO : petlog
						GAMELOG << init("PET SKILL LEARN AUTO", m_owner)
								<< "PET" << delim
								<< m_index << delim
								<< GetPetTypeGrade() << delim
								<< "SKILL" << delim
								<< skill->m_proto->m_index << delim
								<< skill->m_level
								<< end;

						AddSkill(skill);

						CNetMsg::SP rmsg(new CNetMsg);
						ExPetLearnMsg(rmsg, skill->m_proto->m_index, skill->m_level, MSG_EX_PET_LEARN_ERROR_AUTO);
						SEND_Q(rmsg, m_owner->m_desc);
					}
				}
			}
		}
	}

	if( (this->GetPetType() == PET_TYPE_UNKOWN_HORSE
			|| this->GetPetType() == PET_TYPE_UNKOWN_DRAGON )
			&& (m_level == 5 || m_level == 10) )
	{
		// 25������ Ȯ���� ����Ǵµ�
		int ran = GetRandom(0, 1000);
		if( ran <= 250 )
		{
			ChangePetType();
		}
	}
}

void CPet::SetRemainRebirthTime(int nRemainRebirth)
{
	if (nRemainRebirth < 0)
	{
		if (m_level >= 41)
			nRemainRebirth = 17 * 60 * 60;		// 41�̻� 17�ð�
		else if (m_level >= 21)
			nRemainRebirth = 12 * 60 * 60;		// 21�̻� 12�ð�
		else
			nRemainRebirth = 5 * 60 * 60;		// 20���� 5�ð�
	}

	m_nRemainRebirth = nRemainRebirth;

	if (m_nRemainRebirth > 0)
		m_hp = 0;
}

// 050309: bw ���ʿ� �Ÿ� ���ϱ� �Լ�
float CPet::GetDistanceFromOwner()
{
	if (!IS_IN_CELL(this))
		return 0.0f;

	CPC* owner = this->GetOwner();
	if( !owner )
		return (float) INT_MAX;

	if (!IS_IN_CELL(owner))
		return (float) INT_MAX;

	return GetDistance(this, owner);
}

void CPet::ChangePetType()
{
	CPC* owner = this->GetOwner();

	if( !owner )
		return;

	int deleteItemdbIndex;
	int giveItemdbIndex;

	GAMELOG << init("PET TYPE CHANGE", owner)
			<< "PRE" << delim << GetPetType() << delim;
	switch(this->GetPetType())
	{
	case PET_TYPE_UNKOWN_HORSE:
		deleteItemdbIndex = PET_UNKOWN_HORSE_ITEM_INDEX;
		giveItemdbIndex = PET_BLUE_HORSE_ITEM_INDEX;
		m_petTypeGrade = (m_petTypeGrade & PET_GRADE_MASK) | PET_TYPE_BLUE_HORSE;
		break;
	case PET_TYPE_UNKOWN_DRAGON:
		deleteItemdbIndex = PET_UNKOWN_DRAGON_ITEM_INDEX;
		giveItemdbIndex = PET_PINK_DRAGON_ITEM_INDEX;
		m_petTypeGrade = (m_petTypeGrade & PET_GRADE_MASK) | PET_TYPE_PINK_DRAGON;
		break;
	default:
		return;
	}

	// ��ȯ�Ǿ� �ִ� ���� ������ ����
	if (this->IsSummon())
	{
		this->Disappear();
	}
	// Ÿ�� ������ ������
	else if (this->IsMount())
	{
		this->Mount(false);
	}

	// Item ���� ����
	CItem* item = owner->m_inventory.FindByDBIndex(deleteItemdbIndex, this->m_index, 0);
	if (item == NULL)
		return;

	GAMELOG << itemlog(item) << delim
			<< "NEXT" << GetPetType() << delim;


	owner->m_inventory.decreaseItemCount(item, 1);

	owner->GiveItem(giveItemdbIndex, this->m_index, 0, 1 );

	item = owner->m_inventory.FindByDBIndex(giveItemdbIndex, this->m_index, 0);
	if( item == NULL)
		return;

	GAMELOG << itemlog(item) << end;

	{
		unsigned short tab = 0;
		unsigned short invenIndex = 0;

		CNetMsg::SP rmsg(new CNetMsg);
		insideServer_do_Item_Wear(rmsg, WEARING_PET, tab, invenIndex, item->getVIndex());
		do_Item(owner, rmsg);
	}
}
//#endif

float CPet::GetHitrate(CCharacter* df, MSG_DAMAGE_TYPE type)
{
	return 0.0f;
}

float CPet::GetAvoid(CCharacter* of, MSG_DAMAGE_TYPE type)
{
	return 0.0f;
}
