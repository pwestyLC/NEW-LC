
#include "StdH.h"
#include <Engine/Network/CNetwork.h>
#include <Engine/Network/Server.h>
#include <Engine/Interface/UIInternalClasses.h>
#include "SessionState.h"
#include <Engine/Ska/Render.h>
#include <Engine/SlaveInfo.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Interface/UIManager.h>
#include <Engine/Interface/UIAutoHelp.h>
#include <Engine/Interface/UIPlayerInfo.h>
#include <Engine/Contents/Base/UINoticeNew.h>
#include <Engine/Interface/UISiegeWarfareDoc.h>
#include <Engine/Interface/UISiegeWarfareNew.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Interface/UINpcScroll.h>
#include <Engine/Interface/UIGuild.h>
#include <Engine/Interface/UIGuildBattle.h>
#include <Engine/Interface/UIMessenger.h>
#include <Engine/Interface/UIMap.h>
#include <Engine/Interface/UIFlowerTree.h>
#include <Engine/Contents/Base/UIPartyNew.h>
#include <Engine/Interface/UIPetInfo.h>
#include <Engine/Contents/function/PremiumChar.h>
#include <Engine/Contents/function/PremiumCharUI.h>
#include <Engine/Contents/function/SummonUI.h>
#include <Engine/Contents/function/WildPetInfoUI.h>
#include <Engine/Contents/Base/UISkillNew.h>
#include <Engine/Contents/Base/UICharacterInfoNew.h>
#include <Engine/Contents/Base/ExpressSystem.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Templates/Stock_CEntityClass.h>
#include <Engine/Templates/DynamicContainer.cpp>
#include <Engine/GameState.h>
#include <Engine/Object/ActorMgr.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/GameStageManager/StageMgr.h>
#include <Engine/Contents/Base/PersonalshopUI.h>

#include <Common/Packet/ptype_char_status.h>
#include <Common/Packet/ptype_appear.h>
#include <Common/Packet/ptype_premium_char.h>
#include <Engine/Interface/UIGuildWarPortal.h>
#include <Engine/Contents/Base/Quest.h>
#include <Engine/Contents/Base/Party.h>
#include <Engine/Contents/function/SimplePlayerInfoUI.h>
#include <Engine/Contents/function/TargetInfoNewUI.h>
#include <Engine/Contents/function/News.h>
#include <Engine/Contents/function/ItemCompose.h>
#include <Engine/Contents/function/WildPetTargetUI.h>
#include <Engine/Contents/function/PetTargetUI.h>
#include <Engine/Contents/Base/UIMsgBoxMgr.h>
#include <Engine/Interface/UIRadar.h>

#ifdef XTRAP_SECURE_CKBANG_2010_07_20
	#include <Engine/XTrapInterface/XTrapInterface.h>
#endif
#include <Engine/Info/MyInfo.h>
#include <Engine/Reza.h>
extern INDEX g_iCountry;

// �Ӽ� �ý��� �Ӽ� ���� ������
#define ATTRIBUTE_ATT_MAX 7
#define ATTRIBUTE_DEF_MAX 7

// �Ӽ� �ý��� ��� ����
#define AT_MASK          0xFL
#define AT_LVVEC          4
#define GET_AT_VAR(m)   ((m) & AT_MASK)
#define GET_AT_LV(m)     (((m) >> AT_LVVEC) & AT_MASK)

#define IS_FLAG_ON(flagAll, flagVal) ( (flagAll) & (static_cast<SQUAD>((1L))<<(flagVal)) )

DECLARE_MSG_UPDATE(StatusAPetSmall);
DECLARE_MSG_UPDATE(UpdateSettings);
DECLARE_MSG_UPDATE(UpdateLevel);
DECLARE_MSG_UPDATE(UpdateTargetHPInfo);
DECLARE_MSG_UPDATE(UpdateCharHitType);
DECLARE_MSG_UPDATE(updateDisappearEffect);
DECLARE_MSG_UPDATE(updateDisappearAll);
DECLARE_MSG_UPDATE(ClearTarget);
DECLARE_MSG_UPDATE(updatePremiumCharInfo);
DECLARE_MSG_UPDATE(updatePremiumJumpCount);
DECLARE_MSG_UPDATE(updatePremiumCharEnd);
DECLARE_MSG_UPDATE(PremiumFlag);
DECLARE_MSG_UPDATE(updateAttrPc);
DECLARE_MSG_UPDATE(updateAttrNpc);
DECLARE_MSG_UPDATE(updateNewsGmNoti);
DECLARE_MSG_UPDATE(updateNewsWebNoti);
DECLARE_MSG_UPDATE(updateNewsWebClose);
DECLARE_MSG_UPDATE(updateNewsWebClear);
DECLARE_MSG_UPDATE(updateItemCompose);
DECLARE_MSG_UPDATE(updateRelicGpsSysMsg);
DECLARE_MSG_UPDATE(updateGuildRecall);
DECLARE_MSG_UPDATE(updateEPReset);
DECLARE_MSG_UPDATE(charHPMP);
DECLARE_MSG_UPDATE(charHP);

void CSessionState::reg_packet_info()
{
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_STATUS, updateStatus);			// ĳ���� ����(���)		
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_AT, updateAt);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_APPEAR_PC, updatePcAppear);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_APPEAR_NPC, updateNpcAppear);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_APPEAR_PET, updatePetAppear);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_APPEAR_ELEMENTAL, updateElementalAppear);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_APPEAR_APET, updateAPetAppear);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_DISAPPERAR, updateDisappear);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_DISAPPERAR_FOR_CLIENT_EFFECT, updateDisappearEffect);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_DISAPPERAR_ALL, updateDisappearAll);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_TARGET_CLEAR, ClearTarget);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_ELEMENTAL_STATUS, updateElementalStatus);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_EXPED_INFO, updateExpedMemberInfo);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_PARTY_INFO, updatePartyMemberInfo);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_CHAR_STATUS_PC, updateStatusPC);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_CHAR_STATUS_NPC, updateStatusNPC);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_CHAR_STATUS_PET, updateStatusPet);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_CHAR_STATUS_ELEMENTAL, updateStatusElemental);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_CHAR_STATUS_APET, updateStatusAPet);
	REG_PACKET_R(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_DAMAGE, updateDamage);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_APET_SMALL_STATUS, StatusAPetSmall);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_LEVELUP_INFO, UpdateLevel);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_TARGET_HP_INFO, UpdateTargetHPInfo);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_HOLYWATER_STATE, UpdateCharHitType);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_SETTINGS, UpdateSettings);
#ifdef PREMIUM_CHAR
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_PREMIUM_CHAR_INFO, updatePremiumCharInfo);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_PREMIUM_CHAR_JUMP_COUNT, updatePremiumJumpCount);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_PREMIUM_CHAR_END, updatePremiumCharEnd);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_PREMIUM_CHAR_CHANGE_FLAG, PremiumFlag);
#endif	//	PREMIUM_CHAR
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_ATTR_ITEM_USE, updateAttrPc);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_ATTR_STATE_FOR_NPC, updateAttrNpc);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_CHECK_NOTICE, updateNewsGmNoti);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_CHECK_POPUP_NOTICE, updateNewsWebNoti);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_CLOSE_POPUP_NOTICE, updateNewsWebClose);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_CLEAR_POPUP_NOTICE, updateNewsWebClear);

	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_ARTIFACT_SYSMSG, updateItemCompose);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_ARTIFACT_FIND_USER_COUNT_MSG, updateRelicGpsSysMsg);	
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_REQUEST_GUILD_RECALL, updateGuildRecall);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_EP_INIT, updateEPReset);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_CHAR_HPMP, charHPMP);
	REG_PACKET_UPDATE(MSG_UPDATE_DATA_FOR_CLIENT, MSG_SUB_UPDATE_CHAR_CURR_HP, charHP); //Update HP status Target
}


void CSessionState::updateStatus( CNetworkMessage* istr )
{
	UpdateClient::charStatus* pPack = reinterpret_cast<UpdateClient::charStatus*>(istr->GetBuffer());

	// edit by cpp2angel (044.12.20) : �ڵ� ����
	if ( _pNetwork->MyCharacterInfo.sp < pPack->skillPoint )
	{
		_UIAutoHelp->SetInfo ( AU_GET_SKILL_POINT );
	}

	if (_pNetwork->MyCharacterInfo.sp != pPack->skillPoint)
		CUIManager::getSingleton()->GetSkillNew()->UpdateSPointAndMoney(pPack->skillPoint);

	_pNetwork->MyCharacterInfo.level = pPack->level;
	static int iOldLevel = -1;
	if(iOldLevel != pPack->level)
	{
		ACTORMGR()->RefreshQuestMark();		
		iOldLevel = pPack->level;
	}
	_pNetwork->MyCharacterInfo.curExp = pPack->exp; 
	_pNetwork->MyCharacterInfo.needExp = pPack->levelupExp; 
	_pNetwork->MyCharacterInfo.hp = pPack->hp; 
	_pNetwork->MyCharacterInfo.maxHP = pPack->maxHp;
	_pNetwork->MyCharacterInfo.mp = pPack->mp; 
	_pNetwork->MyCharacterInfo.maxMP = pPack->maxMp; 
	_pNetwork->MyCharacterInfo.str = pPack->str; 
	_pNetwork->MyCharacterInfo.dex = pPack->dex;
	_pNetwork->MyCharacterInfo.intel = pPack->intl; 
	_pNetwork->MyCharacterInfo.con = pPack->con; 
	_pNetwork->MyCharacterInfo.opt_str = pPack->opStr + pPack->party_arti[eArti_Str]; 
	_pNetwork->MyCharacterInfo.opt_dex = pPack->opDex + pPack->party_arti[eArti_Dex];
	_pNetwork->MyCharacterInfo.opt_intel = pPack->opInt + pPack->party_arti[eArti_Int]; 
	_pNetwork->MyCharacterInfo.opt_con = pPack->opCon + pPack->party_arti[eArti_Con]; 
	_pNetwork->MyCharacterInfo.sp = pPack->skillPoint; 
	_pNetwork->MyCharacterInfo.weight = 0; 
	_pNetwork->MyCharacterInfo.maxweight = 0; 
	_pNetwork->MyCharacterInfo.walkspeed = pPack->walkSpeed; 
	_pNetwork->MyCharacterInfo.runspeed = pPack->run_or_fly_speed; 
	_pNetwork->MyCharacterInfo.attackspeed = pPack->attackSpeed; 
	_pNetwork->MyCharacterInfo.magicspeed = pPack->magicSpeed;
	_pNetwork->MyCharacterInfo.pktitle			= pPack->pkName; 
	_pNetwork->MyCharacterInfo.pkpenalty		= pPack->pkPenalty; 
	_pNetwork->MyCharacterInfo.pkcount			= pPack->pkCount;
	_pNetwork->MyCharacterInfo.fame				= pPack->fame;
	_pNetwork->MyCharacterInfo.attackrange		= pPack->attackRange;
	_pNetwork->MyCharacterInfo.sbJoinFlagMerac	= pPack->joinForMerac;
	_pNetwork->MyCharacterInfo.sbJoinFlagDratan	= pPack->joinForDratan; // WSS_DRATAN_SIEGEWARFARE 070720
#ifdef QUICK_PANEL
	for (int i = 0; i <= 24; i++)
{
	_pNetwork->MyCharacterInfo.cloud_QuickPanelBtnType[i] = pPack->m_cloud_m_QuickPanelBtnType[i];
	_pNetwork->MyCharacterInfo.cloud_QuickPanelBtnIdx[i] = pPack->m_cloud_m_QuickPanelBtnIdx[i];
}
#endif
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	for (int i = 0; i <= 4; i++)
	{
		_pNetwork->MyCharacterInfo.cloud_partydgdata[i] = pPack->m_cloud_PartyDGCompleteData[i];
		_pNetwork->MyCharacterInfo.cloud_partydgtitle[i] = pPack->m_cloud_PartyDGTitleRewardData[i];
	}
#endif
	// �Ӽ� �ý��� [1/17/2013 Ranma]
	UBYTE nAttrdef = GET_AT_VAR(pPack->attrDef);
	UBYTE nAttrdefLv = GET_AT_LV(pPack->attrDef);
	UBYTE nAttratt = GET_AT_VAR(pPack->attrAtt);
	UBYTE nAttrattLv = GET_AT_LV(pPack->attrAtt);

	if (nAttratt <= 0 || nAttratt >= ATTRIBUTE_ATT_MAX)
	{
		nAttratt = 0; 
		nAttrattLv = 1;
	}

	if (nAttrdef <= 0 || nAttrdef >= ATTRIBUTE_ATT_MAX)
	{
		nAttrdef = 0;	
		nAttrdefLv = 1;
	}

	_pNetwork->MyCharacterInfo.attrdef			= nAttrdef; // ��� �Ӽ�
	_pNetwork->MyCharacterInfo.attrdefLv		= nAttrdefLv;  // ��� �Ӽ� Level
	_pNetwork->MyCharacterInfo.attratt			= nAttratt; // ���� �Ӽ�
	_pNetwork->MyCharacterInfo.attrattLv		= nAttrattLv;  // ���� �Ӽ� Level

	_pNetwork->MyCharacterInfo.skillSpeed		= pPack->skillSpeed;
	_pNetwork->MyCharacterInfo.sbAttributePos	= pPack->mapAttr;
	_pNetwork->MyCharacterInfo.sbMountPet		= pPack->mountPet;
	_pNetwork->MyCharacterInfo.nEvocationIndex	= pPack->evocationIndex;

	// 080623 ��ī ���ڴ� ����
	_pNetwork->MyCharacterInfo.sbPresscorps		= pPack->bPressCorps;
//#ifdef REZABOT
	_pNetwork->MyCharacterInfo.char_botting = pPack->a_botting;
//#endif
	_pNetwork->MyCharacterInfo.baseHP			= pPack->maxHpOrg;
	_pNetwork->MyCharacterInfo.baseMP			= pPack->maxMpOrg;
	_pNetwork->MyCharacterInfo.addedAttack 		= pPack->attack_diff;
	_pNetwork->MyCharacterInfo.addedMagic 		= pPack->magic_diff;
	_pNetwork->MyCharacterInfo.addedDefense 	= pPack->defense_diff;
	_pNetwork->MyCharacterInfo.addedResist 		= pPack->resist_diff;

	_pNetwork->MyCharacterInfo.dodgeRate		= pPack->avoid_melee;
	_pNetwork->MyCharacterInfo.baseDodgeRate 	= pPack->avoid_melee_org;
	_pNetwork->MyCharacterInfo.magicDodgeRate 	= pPack->avoid_magic;
	_pNetwork->MyCharacterInfo.baseMagicDodgeRate	= pPack->avoid_magic_org;
	_pNetwork->MyCharacterInfo.hitRate 			= pPack->fhitrate_melee;
	_pNetwork->MyCharacterInfo.baseHitRate 		= pPack->fhitrate_melee_org;

	_pNetwork->MyCharacterInfo.magicHitRate		= pPack->fhitrate_magic;
	_pNetwork->MyCharacterInfo.baseMagicHitRate = pPack->fhitrate_magic_org;
	_pNetwork->MyCharacterInfo.critical 		= pPack->critical;
	_pNetwork->MyCharacterInfo.baseCritical 	= pPack->critical_org;
	_pNetwork->MyCharacterInfo.deadly 			= pPack->deadly;
	_pNetwork->MyCharacterInfo.baseDeadly 		= pPack->deadly_org;

	_pNetwork->MyCharacterInfo.baseRunSpeed 	= pPack->run_or_fly_speed_org;
	_pNetwork->MyCharacterInfo.baseAttackSpeed 	= pPack->attackSpeedOrg;

	_pNetwork->MyCharacterInfo.ep				= pPack->ep;
	_pNetwork->MyCharacterInfo.maxEP			= pPack->maxEp;

    _pNetwork->MyCharacterInfo.autopickup = 	pPack->autopickup;
    _pNetwork->MyCharacterInfo.autoigni = 		pPack->autoigni;
    _pNetwork->MyCharacterInfo.autosell = 		pPack->autosell;

	_pNetwork->MyCharacterInfo.a_wins			= pPack->a_wins;
	_pNetwork->MyCharacterInfo.a_loses			= pPack->a_loses;
	_pNetwork->MyCharacterInfo.a_honor			= pPack->a_honor;
	_pNetwork->MyCharacterInfo.reborn			= pPack->reborn;
	_pNetwork->MyCharacterInfo.StatPointAddition = pPack->stats_addition;
	_pNetwork->MyCharacterInfo.colorName		= pPack->color_name;

	_pNetwork->MyCharacterInfo.opResistStone			= pPack->opResistStone;
	_pNetwork->MyCharacterInfo.opResistSturn			= pPack->opResistSturn;
	_pNetwork->MyCharacterInfo.opResistSilent			= pPack->opResistSilent;
	_pNetwork->MyCharacterInfo.opabsorbPVPDamageRate	= pPack->opabsorbPVPDamageRate;
	_pNetwork->MyCharacterInfo.opDecreaseSkillMP		= pPack->opDecreaseSkillMP;

	MyInfo* pInfo = MY_INFO();
	pInfo->SetBuyAddition(pPack->opMoney_buy_addition);
	pInfo->SetBuyRate(pPack->opMoney_buy_rate);
	pInfo->SetSellAddition(pPack->opMoney_sell_addition);
	pInfo->SetSellRate(pPack->opMoney_sell_rate);

	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->GetSimplePlayerInfo()->UpdatePlayerBaseInfo();
	pUIManager->GetCharacterInfo()->UpdateStatus( pPack->attack, pPack->magic, pPack->defense, pPack->resist);		// yjpark

#ifdef XTRAP_SECURE_CKBANG_2010_07_20
	if (g_pXTrap_C_SetUserInfoEx_Interface)
	{
		g_pXTrap_C_SetUserInfoEx_Interface("ssss",
			"",
			"",
			"",
			0,
			0);
	}
#endif

	//[ttos_2009_1_15]:��Ÿ�� ���� �� MP�� ���� �ɼ��� Ŭ�󿡼� ������� �ʰ� �������� ����
	pUIManager->SetCoolTimeReductionRate(pPack->prob);
	pUIManager->SetNeedMPReductionRate(pPack->opDecreaseSkillMP);

	// [100107: selo] Ʈ���̳� ���ϱ� ���� �߿� �� ����	
	CPlayerEntity* penPlayerEntity = (CPlayerEntity*)CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
	penPlayerEntity->SetImportantValues(pPack->walkSpeed, pPack->run_or_fly_speed, pPack->attackRange, pPack->attackSpeed, pPack->magicSpeed);	 

	// Date : 2005-09-07(���� 5:31:54), By Lee Ki-hwan
	// sbMountPet : ���� Ÿ���ִ����� ���� ����
	// 0 Ÿ�� ���� ����, 
	// �׿� PetType�� Age�� bit������ ��.
	if( pPack->mountPet ) 
	{
		//-----------------------------------------------------------	
		INDEX iPetType	= -1;
		INDEX iPetAge	= -1;
		_pNetwork->CheckPetType( pPack->mountPet, iPetType, iPetAge );

		// NOTE : Ż�� �ִ� �ֿϵ������� �Ǵ��Ͽ�, ĳ���͸� �¿�ϴ�.
		// NOTE : �ֿϵ����� Ÿ�� ���� ��쿡��, PetŸ�� ������ �߰����� ����(�� �ֿϵ����϶��� �� Ÿ�� ����â �����Ұ�...)
		const BOOL bPetRide = PetInfo().IsRide(iPetType, iPetAge);		

		if( bPetRide )
		{
			//-----------------------------------------------------------
			if( !((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsRidePet(CEntity::GetPlayerEntity(0)) )
			{				
				CNetworkLibrary::sPetInfo	TempPet;
				CPetTargetInfom* pPetInfo = INFO()->GetMyPetInfo();

				
				TempPet.lIndex = pPetInfo->lIndex;
				pPetInfo->bIsActive	= TRUE;
				pPetInfo->pen_pEntity	= NULL;
				pPetInfo->iType			= iPetType;
				pPetInfo->iAge			= iPetAge;

				std::vector<CNetworkLibrary::sPetInfo>::iterator iter = 
					std::find_if(_pNetwork->m_vectorPetList.begin(), _pNetwork->m_vectorPetList.end(), CNetworkLibrary::FindPet(TempPet) );

				if( iter != _pNetwork->m_vectorPetList.end() )
				{
					pPetInfo->iLevel		= (*iter).lLevel;
					pPetInfo->fHealth		= (*iter).lHP;
					pPetInfo->fMaxHealth	= (*iter).lMaxHP;
					pPetInfo->fMaxHungry	= (*iter).lMaxHungry;
					pPetInfo->fHungry		= (*iter).lHungry;
					pPetInfo->lAbility		= (*iter).lAbility;
					pPetInfo->bIsActive		= TRUE;
					pPetInfo->lIndex		= TempPet.lIndex;
					pPetInfo->iType			= iPetType;
					pPetInfo->iAge			= iPetAge;						
					pPetInfo->strNameCard	= (*iter).strNameCard;
				}

				// [070824: Su-won] PET_COLOR_CHANGE
				INDEX iPetColoredType = iPetType | (pPack->colorType<<8);
				_pNetwork->RidePet( (CPlayerEntity*)CEntity::GetPlayerEntity(0), NULL, iPetColoredType );
				CUIManager::getSingleton()->GetPetTargetUI()->openUI();
			}
		}
		//_pNetwork->MyCharacterInfo.bPetRide = bPetRide;
	}

	if(_pNetwork->MyCharacterInfo.hp==0)
	{		
		CEntity* penPlEntity;
		CPlayerEntity* penPlayerEntity;
		penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
		penPlayerEntity = (CPlayerEntity*) penPlEntity;
		if(!penPlayerEntity->IsAlreadyDie())
		{
			//	penPlayerEntity->DeathYou();
			penPlayerEntity->SetDie();
			_pNetwork->MyCharacterInfo.statusEffect.Reset();
		}
		// WSS_DRATAN_SIEGEWARFARE 2007/10/17
		// ���� ��Ȱ���� �׾��� ��� ó��		
		if( !pUIManager->GetSiegeWarfareNew()->GetWarState()&&
			(pUIManager->GetSiegeWarfareNew()->GetWaitTime()>=0))
		{			
			penPlayerEntity->DeathYou();
		}

		// [090908: selo]
		// ��ȯ�ֹ��� ��� �� ���� ���� �־
		// ���� ���� �� �κ��丮 Lock�� Ǯ���ش�.
		pUIManager->SetCSFlagOff( CSF_TELEPORT );
		pUIManager->GetInventory()->Lock( FALSE, FALSE, LOCK_WARP );

		// connie [2009/10/1] - NPC ã�� 
		pUIManager->GetNpcScroll()->CloseNpcScroll();
	}
#ifdef NEW_CHAO_SYS
	if (pPack->pkPenalty  == 32000)
	{
		if (!(PK_SYS_CHAO_6 & _pNetwork->MyCharacterInfo.pkSysRewardFlag))
		{
			if(_pNetwork->MyCharacterInfo.bpkSysRewardLate == FALSE)
			{//��û ��Ŷ
				_pNetwork->pkPenaltyReformRewardReq(5);
				_pNetwork->MyCharacterInfo.bpkSysRewardLate= TRUE;
			}
		}
	}
	else if(pPack->pkPenalty  >= 19000 && pPack->pkPenalty  < 32000)
	{
		if (!(PK_SYS_CHAO_5&_pNetwork->MyCharacterInfo.pkSysRewardFlag))
		{
			if(_pNetwork->MyCharacterInfo.bpkSysRewardLate == FALSE)
			{//��û ��Ŷ
				_pNetwork->pkPenaltyReformRewardReq(4);
				_pNetwork->MyCharacterInfo.bpkSysRewardLate= TRUE;
			}
		}
	}
	else if(pPack->pkPenalty  >= 6000 && pPack->pkPenalty  < 19000)
	{
		if (!(PK_SYS_CHAO_4&_pNetwork->MyCharacterInfo.pkSysRewardFlag))
		{
			if(_pNetwork->MyCharacterInfo.bpkSysRewardLate == FALSE)
			{	//��û ��Ŷ
				_pNetwork->pkPenaltyReformRewardReq(3);
				_pNetwork->MyCharacterInfo.bpkSysRewardLate= TRUE;
			}
		}
	}
	else if(pPack->pkPenalty  > -19000 && pPack->pkPenalty  <= -6000)
	{
		if (!(PK_SYS_CHAO_3&_pNetwork->MyCharacterInfo.pkSysRewardFlag))
		{
			if(_pNetwork->MyCharacterInfo.bpkSysRewardLate == FALSE)
			{	//��û ��Ŷ
				_pNetwork->pkPenaltyReformRewardReq(2);
				_pNetwork->MyCharacterInfo.bpkSysRewardLate= TRUE;
			}
		}
	}
	else if(pPack->pkPenalty  > -32000 && pPack->pkPenalty  <= -19000)
	{
		if (!(PK_SYS_CHAO_2&_pNetwork->MyCharacterInfo.pkSysRewardFlag))
		{
			if(_pNetwork->MyCharacterInfo.bpkSysRewardLate == FALSE)
			{	//��û ��Ŷ
				_pNetwork->pkPenaltyReformRewardReq(1);
				_pNetwork->MyCharacterInfo.bpkSysRewardLate= TRUE;
			}
		}
	}
	else if(pPack->pkPenalty  == -32000)
	{
		if (!(PK_SYS_CHAO_1&_pNetwork->MyCharacterInfo.pkSysRewardFlag))
		{
			if(_pNetwork->MyCharacterInfo.bpkSysRewardLate == FALSE)
			{	//��û ��Ŷ
				_pNetwork->pkPenaltyReformRewardReq(0);
				_pNetwork->MyCharacterInfo.bpkSysRewardLate= TRUE;
			}
		}
	}
#endif //NEW_CHAO_SYS
#ifdef FIX_EFFECT_CHAR
	CEntity* penPlEntity;
	penPlEntity = CEntity::GetPlayerEntity(0);
	penPlayerEntity = static_cast<CPlayerEntity*>(penPlEntity);

	CModelInstance* pMI = NULL;
	if (_pNetwork->MyCharacterInfo.bPetRide || _pNetwork->MyCharacterInfo.bWildPetRide)
	{
		CModelInstance* pMITemp = penPlayerEntity->GetModelInstance();

		INDEX ctmi = pMITemp->mi_cmiChildren.Count();
		if (ctmi > 0)
			pMI = &pMITemp->mi_cmiChildren[0];
		else
			pMI = penPlayerEntity->GetModelInstance();
	}
	else
	{
		pMI = penPlayerEntity->GetModelInstance();
	}

	_pNetwork->MyCharacterInfo.itemEffect.Refresh(&pMI->m_tmSkaTagManager, 1);
	_pNetwork->MyCharacterInfo.statusEffect.Refresh(&pMI->m_tmSkaTagManager, CStatusEffect::R_NONE);
#endif
}
void CSessionState::updateAt( CNetworkMessage* istr )
{
	UpdateClient::charAtMsg* pPack = reinterpret_cast<UpdateClient::charAtMsg*>(istr->GetBuffer());
	
	CUIManager* pUIManager = CUIManager::getSingleton();

	//0707
#ifdef SECRET_KEY
	pPack->key = (pPack->key >> 1) - pPack->charIndex; 
	_pNetwork->MyCharacterInfo.secretkey = (SLONG)pPack->key;
#endif

#ifdef USE_UIAD
	if( pUIManager->GetAD() )
	{
		pUIManager->GetAD()->ClearListQ();
		pUIManager->GetAD()->AddListQ(0);
	}
#endif


	CGame* _pGame			= pUIManager->GetGame();
	CPlayerCharacter &pc	= _pGame->gm_apcPlayers[0];
	pc.pc_iPlayerType		= pPack->job;

	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->CharacterChanged(pc);

	_pNetwork->MyCharacterInfo.index = pPack->charIndex;
	_pNetwork->MyCharacterInfo.name = pPack->charName;
	_pNetwork->MyCharacterInfo.job = pPack->job;
	_pNetwork->MyCharacterInfo.job2 = pPack->job2;
	_pNetwork->MyCharacterInfo.zoneNo = pPack->zoneIndex;
	_pNetwork->MyCharacterInfo.areaNo = pPack->areaIndex;
	_pNetwork->MyCharacterInfo.x = pPack->x;
	_pNetwork->MyCharacterInfo.z = pPack->z; 
	_pNetwork->MyCharacterInfo.h = pPack->h;
	_pNetwork->MyCharacterInfo.r = pPack->r;	
	_pNetwork->MyCharacterInfo.yLayer = pPack->yLayer;
	_pNetwork->MyCharacterInfo.userIndex = pPack->userIndex;
	_pNetwork->MyCharacterInfo.hairStyle = pPack->hairstyle;
	_pNetwork->MyCharacterInfo.faceStyle = pPack->facestyle;
	_pNetwork->MyCharacterInfo.pk_mode   = 0; 
	_pNetwork->MyCharacterInfo.sbShopType		= PST_NOSHOP;
	_pNetwork->MyCharacterInfo.lGuildIndex		= -1;
	_pNetwork->MyCharacterInfo.lGuildLevel		= -1;
	_pNetwork->MyCharacterInfo.lGuildPosition	= GUILD_MEMBER_NOMEMBER;
	_pNetwork->MyCharacterInfo.sbGuildRank		= 0;
	_pNetwork->MyCharacterInfo.lTeacherIndex	= -1;	
	_pNetwork->MyCharacterInfo.fame				= 0;	
	_pNetwork->MyCharacterInfo.strTeacherName.Clear();
	_pNetwork->MyCharacterInfo.bExtension = FALSE;

	STAGEMGR()->SetNextStage(eSTAGE_GAMEPLAY);
	pUIManager->SetUIGameState(TRUE);

	Sleep(500); //cloud fix ep1 loading
	
	pUIManager->GetMessenger()->SetMyInfo( pPack->charIndex, pPack->charName,	(eJob)pPack->job, ONLINE );
	
#ifdef	VER_TEST
	extern INDEX		sam_bFullScreenActive;
	extern INDEX		sam_iScreenSizeI;
	extern INDEX		sam_iScreenSizeJ;

	pUIManager->SetTitleName( sam_bFullScreenActive, sam_iScreenSizeI, sam_iScreenSizeJ );
#endif	// VER_TEST

	_pNetwork->MyCharacterInfo.sbItemEffectOption = pPack->plusEffect;	

	if ( !(pPack->mapAttr & MATT_UNWALKABLE) )
	{
		_pNetwork->MyCharacterInfo.sbAttributePos = pPack->mapAttr;
	}
	//[ttos_2009_1_23]:ä�� ����
	_pNetwork->MyCharacterInfo.ChatFlag = pPack->chatingFlag;
	//������ ���� ����	//(Zone Change System)(0.1)
	g_slZone = pPack->zoneIndex;
	pUIManager->GetRadar()->updateZone();
	_pNetwork->ga_sesSessionState.ses_bWantPause = FALSE;
	//������ ���� ��	//(Zone Change System)(0.1)

	CEntity::GetPlayerEntity(0)->SetNetworkID(pPack->charIndex);
	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->Read_net_Character(MSG_AT, 0, &(*istr));	 

	if(_pUISWDoc->IsWar())
	{
		pUIManager->GetMap()->SetCurrentWorldMap( pPack->zoneIndex, 1 );		// yjpark
	}
	else
	{
		pUIManager->GetMap()->SetCurrentWorldMap( pPack->zoneIndex, pPack->yLayer );		// yjpark
	}

	if( pUIManager->IsCSFlagOn( CSF_PARTY ) )
	{
		pUIManager->GetParty()->open();
	}

	// [090715: selo] ���̵忡�� �������� ����Ʈ ���� ���̵� �޽����� ����
	if(!pUIManager->IsPlayInZone()) //�ν���Ʈ�����ο��� �������
	{		
		GAMEDATAMGR()->GetQuest()->RemoveRaidMessageAll();
	}

	_pNetwork->SendRegenList();

	_pNetwork->MyCharacterInfo.iNickType = pPack->currentTitle;
	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetNickNameDamageEffect(pPack->currentTitle, CEntity::NICKNAME_ATTACH_EFFECT);

	pUIManager->GetCharacterInfo()->RegisterActions(); // ĳ���� ����â ����

	MY_INFO()->_guildmark.remove();

#ifdef ADD_SUBJOB
	_pNetwork->MyCharacterInfo.slSubJob = pPack->jobSub;
#endif
	
	
}

	void CSessionState::updateNpcAppear(CNetworkMessage * istr)
	{
		UpdateClient::appearNpc* pPack = reinterpret_cast<UpdateClient::appearNpc*>(istr->GetBuffer());

		CPlacement3D	plPlacement;
		CTString		name;
		INDEX			Ownerindex = -1;
		CTString		Ownername = "";
		CTString		Ownershopname = "";

		CEntity* penEntity;
		CEntity* penPlEntity;
		CPlayerEntity* penPlayerEntity;
		penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
		penPlayerEntity = (CPlayerEntity*)penPlEntity;

		plPlacement.pl_PositionVector(1) = pPack->x;
		plPlacement.pl_PositionVector(2) = pPack->h + 1.0f;
		plPlacement.pl_PositionVector(3) = pPack->z;
		plPlacement.pl_OrientationAngle(1) = pPack->r;
		plPlacement.pl_OrientationAngle(2) = 0;
		plPlacement.pl_OrientationAngle(3) = 0;

		CMobData* MD = CMobData::getData(pPack->charDbIndex);
		if (MD->GetMobIndex() == -1)
		{
			OutputDebugString("Cannot find Mob Data!!!\n");
			return;
		}

		UBYTE ubAttrdef = GET_AT_VAR(pPack->attrdef);
		UBYTE ubAttratt = GET_AT_VAR(pPack->attratt);
		UBYTE ubAttrdefLv = GET_AT_LV(pPack->attrdef);
		UBYTE ubAttrattLv = GET_AT_LV(pPack->attratt);

		if (ubAttratt <= 0 || ubAttratt >= ATTRIBUTE_ATT_MAX)
		{
			ubAttratt = 0;
			ubAttrattLv = 1;
		}

		if (ubAttrdef <= 0 || ubAttrdef >= ATTRIBUTE_ATT_MAX)
		{
			ubAttrdef = 0;
			ubAttrdefLv = 1;
		}

		MD->SetAttribute(ubAttratt, ubAttrdef, ubAttrattLv, ubAttrdefLv);

		DeleteObject(MSG_CHAR_NPC, pPack->charVirtualIndex);
		CMobTarget* pMT = new CMobTarget;

		penEntity = _pNetwork->ga_World.CreateEntity_t(plPlacement, CLASS_ENEMY, -1, TRUE);
		penEntity->SetNetworkID(pPack->charVirtualIndex);

		BOOL bNpc = FALSE;
		if (MD->IsSkillMaster() || MD->IsSSkillMaster() || MD->IsNPC())
		{
			bNpc = TRUE;
		}

		BuffInfo	sBuff;
		sBuff.m_llStartTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();

		ASSERT(pMT->mob_BuffCount == 0);
		pMT->mob_BuffCount = 0;
		for (int i = 0; i < pPack->assistInfo.count; i++)
		{
			sBuff.m_slItemIndex = pPack->assistInfo.list[i].index;
			sBuff.m_slSkillIndex = pPack->assistInfo.list[i].dbIndex;
			sBuff.m_sbLevel = pPack->assistInfo.list[i].level;
			sBuff.m_slRemain = pPack->assistInfo.list[i].remain;
			sBuff.m_slRemainCount = pPack->assistInfo.list[i].remainCount;
			pMT->AddBuff(sBuff);
		}

		// [sora] ������ �ý��� ��� ǥ�� index
		pMT->mob_Label = pPack->expedLabel;
		pMT->mob_hp = pPack->hp; //dethunter12
		pMT->mob_maxhp = pPack->maxHp; //dethunter12
		pMT->mob_Label = pPack->expedLabel;
		if (!(pPack->mapAttr & MATT_UNWALKABLE))
		{
			pMT->mob_sbAttributePos = pPack->mapAttr;
		}

		const char* szMobName = CMobData::getData(pPack->charDbIndex)->GetName();
		CTString strMobName;

		if (MD->IsTotemItem())
		{
			if (pPack->ownerIndex == _pNetwork->MyCharacterInfo.index)
			{
				Ownername = _pNetwork->MyCharacterInfo.name;
				_pNetwork->MyCharacterInfo.useTotem = true;
			}
			else
			{
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pPack->ownerIndex);
				if (pObject != NULL)
					Ownername = pObject->m_strName.c_str();
			}
			strMobName.PrintF("%s%s %s", Ownername, _S(2228, "��"), szMobName);
		}
		else
		{
			strMobName = szMobName;
		}

		pMT->SetData(pPack->charVirtualIndex, pPack->charDbIndex, strMobName, MD->GetLevel(), penEntity, bNpc, pPack->yLayer);
		pMT->SetSyndicateData(MD->GetSyndicateType(), MD->GetSyndicateGrade());

		penEntity->InitAsSkaModel();
		pMT->m_nIdxClient = penEntity->en_ulID;

		// �Ӽ� �߰�
		pMT->SetAttribute(eATTR_ATT, ubAttratt, ubAttrattLv);
		pMT->SetAttribute(eATTR_DEF, ubAttrdef, ubAttrdefLv);

		ACTORMGR()->AddObject(pMT);

		// ������ �����϶�....
		if (pPack->charDbIndex == LORD_SYMBOL_INDEX)
		{
			if (pPack->hp <= pPack->maxHp * 0.25f)
			{
				penEntity->SetSkaModel("data\\npc\\Gguard\\sword04.smc");
			}
			else if (pPack->hp <= pPack->maxHp * 0.50f)
			{
				penEntity->SetSkaModel("data\\npc\\Gguard\\sword03.smc");
			}
			else if (pPack->hp <= pPack->maxHp * 0.75f)
			{
				penEntity->SetSkaModel("data\\npc\\Gguard\\sword02.smc");
			}
			else
			{
				penEntity->SetSkaModel(MD->GetMobSmcFileName());
			}
		}
		else
		{
			penEntity->SetSkaModel(MD->GetMobSmcFileName());
		}

		penPlayerEntity->SetMobData(penEntity, pPack->hp, pPack->maxHp, MD->GetLevel(), bNpc, pPack->charDbIndex);
		CMobData::SetMobDataToNPC(penEntity, MD, szMobName);
		penEntity->Initialize();
		penEntity->en_pMobTarget = pMT;
		penEntity->FallDownToFloor();
		penEntity->GetModelInstance()->m_tmSkaTagManager.SetOwner(penEntity);

		// ���� ���õǼ�... hp�� 0�̶��...
		// ���� NPC������ ��������� �ʴ� NPC��...(�׸��� Ÿ���õ� �ȵǵ���...)
		if ((MD->IsCastleTower()) && pPack->hp <= 0)
		{
			penEntity->SetFlagOff(ENF_ALIVE);
		}

		if (MD->IsShadowNPC())
		{
			penEntity->SetFlagOn(ENF_HIDDEN);
		}

		if (pMT->m_nType == 491)
		{
			penEntity->SetFlagOff(ENF_ALIVE);
		}

		if (pMT->m_nType == 1152)
		{
			penEntity->SetFlagOff(ENF_ALIVE);
		}

		// assist_state ���� ���ؿ� ���� �ο��� ���� ����Ʈ�� �߰��Ѵ�.
		// ������ ���������� ���� ����� �����ϴ� ����Ʈ�� ���⼭ ���̰�,
		// �ǳ� ���� �վ��� ������ �Ͱ� ���� ����Ʈ�� MSG_CHAR_STATUS���� ���δ�.
		if (penEntity->en_pmiModelInstance)
		{
			pMT->ChangeStatus(&penEntity->en_pmiModelInstance->m_tmSkaTagManager, pPack->assistInfo.state);
		}
		else
		{
			ASSERTALWAYS("Mob must have ska model and tag manager.");
		}

		if (bNpc)
		{
			ACTORMGR()->RefreshNPCQuestMark(pPack->charDbIndex);
		}

		//hardcoding effect
		if (penEntity->en_pmiModelInstance == NULL) return;

		if (pPack->charDbIndex == MOB_FLOWERTREE_INDEX || pPack->charDbIndex == MOB_XMAS_TREE_CENTER || pPack->charDbIndex == MOB_XMAS_TREE_DECO || pPack->charDbIndex == GAMIGO_10TH_CAKE)
		{ //�ɳ���, ũ�������� Ʈ��(��Ŀ�, �����)
			CUIManager* pUIManager = CUIManager::getSingleton();

			pUIManager->GetFlowerTree()->SetMobFlowerTree(pMT); // �ɳ��� MobTarget���� ����
			pUIManager->GetFlowerTree()->FlowerTreeUpdate(pPack->hp);
		}
		pMT->BuffsStartGroupEffect();

		pMT->mob_iOwnerIndex = pPack->ownerIndex;

		if (IS_FLAG_ON(pPack->assistInfo.state, EST_ASSIST_MERCENARY))
		{
			pMT->SetSubType(CMobTarget::MST_MERCENARY);
			penEntity->SetFirstExtraFlagOn(ENF_EX1_MONSTER_MERCENARY);
		}
		else if (IS_FLAG_ON(pPack->assistInfo.state, EST_ASSIST_SOUL_TOTEM_BUFF))
		{
			pMT->SetSubType(CMobTarget::MST_BUFF_TOTEM);
			penEntity->SetFirstExtraFlagOn(ENF_EX1_TOTEM);
		}
		else if (IS_FLAG_ON(pPack->assistInfo.state, EST_ASSIST_SOUL_TOTEM_ATTK))
		{
			pMT->SetSubType(CMobTarget::MST_ATTACK_TOTEM);
			penEntity->SetFirstExtraFlagOn(ENF_EX1_TOTEM);
		}
		else if (IS_FLAG_ON(pPack->assistInfo.state, EST_ASSIST_TRAP))
		{
			pMT->SetSubType(CMobTarget::MST_TRAP);
			// ������ �׻� üũ�Ͽ��� �����ϹǷ� ������ ��� �����.
			// ������ ���������� Ǯ����.
			penEntity->SetFirstExtraFlagOn(ENF_EX1_TRAP);
			if (pPack->ownerIndex == _pNetwork->MyCharacterInfo.index)
			{
				penEntity->SetFlagOff(ENF_HIDDEN);
			}
		}
		else if (IS_FLAG_ON(pPack->assistInfo.state, EST_ASSIST_SUICIDE))
		{
			pMT->SetSubType(CMobTarget::MST_SUICIDE);
			penEntity->SetFirstExtraFlagOn(ENF_EX1_SUICIDE);
		}
		else
		{
			pMT->SetSubType(CMobTarget::MST_NONE);

			if (MD->IsTotemItem())
			{
				penEntity->SetFirstExtraFlagOn(ENF_EX1_TOTEM_ITEM);
			}
		}
		// [2011/03/24 : Sora] ���� �뺴 ������ ����
		if (pPack->ownerIndex > 0)
		{
			if (pPack->mercenarySize > 0.0f)
			{
				penEntity->GetModelInstance()->StretchModel(FLOAT3D(pPack->mercenarySize, pPack->mercenarySize, pPack->mercenarySize));
			}
		}

		CTString strStateEffectName;

		if (pMT->m_nType == 1374)
		{
			GameDataManager* pGameDataManager = GameDataManager::getSingleton();
			if (pGameDataManager)
			{
				ExpressSystem* pExpressData = pGameDataManager->GetExpressData();

				if (pExpressData)
				{
					if (pExpressData->GetNoticeFlag() > 0)
					{
						pExpressData->ChangeMailNpc(MAIL_NPC_STATE_APPEAR);
						return;
					}
					else
					{
						pExpressData->ChangeMailNpc(MAIL_NPC_STATE_NONE);
					}
				}
			}
		}

		switch (pMT->m_nType)
		{
		case 190: { strStateEffectName = "DK Normal State"; } break; //��������Ʈ
		case 236: { strStateEffectName = "npcGolem01"; } break; //������ ���̾�Ʈ
		case 454: { strStateEffectName = "halloween_mon"; penEntity->SetFlagOn(ENF_HIDDEN); } break; // ȣ�� �ͽ�
		case 455: { strStateEffectName = "halloween_crow"; } break; // ȣ�� ���� ����ƺ�
		case 1116: { strStateEffectName = "padocs_appear"; } break; // �ĵ��� ���� ����Ʈ
		default:
			return;
		}

		pMT->mob_pNormalEffect = StartEffectGroup(strStateEffectName, &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());//
	}

void CSessionState::updatePcAppear( CNetworkMessage *istr )
{
	UpdateClient::appearPc* pPack = reinterpret_cast<UpdateClient::appearPc*>(istr->GetBuffer());

	CPlacement3D	plPlacement;

	CEntity* penEntity;
	CEntity* penPlEntity;
	CPlayerEntity* penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
	penPlayerEntity = (CPlayerEntity*) penPlEntity;
		
	plPlacement.pl_PositionVector(1) = pPack->x;
	plPlacement.pl_PositionVector(2) = pPack->h + 1.0f;
	plPlacement.pl_PositionVector(3) = pPack->z;
	plPlacement.pl_OrientationAngle(1) = pPack->r;
	plPlacement.pl_OrientationAngle(2) = 0;
	plPlacement.pl_OrientationAngle(3) = 0;

	DeleteObject(MSG_CHAR_PC, pPack->charIndex);
	// FIXME : Factory�� �ٲܱ�???
	CCharacterTarget* pTarget = new CCharacterTarget;
	penEntity = _pNetwork->ga_World.CreateEntity_t(plPlacement,CTFILENAME("Classes\\Character.ecl"),-1,TRUE);

	CTString strName = pPack->charName;
	pTarget->SetData( pPack->charIndex, pPack->job, strName, penEntity, pPack->yLayer,pPack->playerState,pPack->pkPenalty, pPack->a_wins, pPack->a_loses, pPack->reborn, pPack->color_name);//0826
	pTarget->cha_hp = pPack->hp; //dethunter12
	pTarget->cha_maxhp = pPack->maxHp;//dethunter12
	pTarget->cha_iJob2 = pPack->job2;
	penEntity->InitAsSkaModel();
	pTarget->m_nIdxClient = penEntity->en_ulID;

#ifdef PREMIUM_CHAR
	if (pPack->isPremiumChar == true)
		pTarget->SetPremiumType(PREMIUM_CHAR_TYPE_FIRST);
	else
		pTarget->SetPremiumType(PREMIUM_CHAR_TYPE_NONE);
#endif	//	PREMIUM_CHAR

	ACTORMGR()->AddObject(pTarget);
	
	penPlayerEntity->SetChaData(penEntity->en_ulID, pPack->job, pPack->hp, pPack->maxHp, pPack->hairStyle, pPack->faceStyle, strName, pPack->playerState,pPack->pkName, pPack->pkPenalty);
	pTarget->SetItemEffectOption( pPack->plusEffect );
	
	penEntity->Initialize();
	penEntity->SetNetworkID(pPack->charIndex);
	penEntity->FallDownToFloor();
	penEntity->en_pCharacterTarget = pTarget;
	
	penPlayerEntity->SetCharCostumeWearing(pTarget, penEntity, &(*istr));
	penPlayerEntity->SetChaWearing(pTarget, penEntity, &(*istr));

	BuffInfo	sBuff;
	sBuff.m_llStartTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();

	ASSERT( pTarget->cha_BuffCount == 0 );
	pTarget->cha_BuffCount = 0;

	CEffectGroup* pEG=NULL;
	for( int k = 0; k < pPack->assistInfo.count; k++ )
	{
		sBuff.m_slItemIndex = pPack->assistInfo.list[k].index;
		sBuff.m_slSkillIndex = pPack->assistInfo.list[k].dbIndex;
		sBuff.m_sbLevel = pPack->assistInfo.list[k].level;
		sBuff.m_slRemain = pPack->assistInfo.list[k].remain;
		sBuff.m_slRemainCount = pPack->assistInfo.list[k].remainCount;
	
		CItemData* pItemData = _pNetwork->GetItemData(sBuff.m_slItemIndex);
		// wooss 070305 ------------------------------------>>
		// kw : WSS_WHITEDAY_2007
		// 6�� ������� ��ų
		// 423 424 425 426 427 428
		if( sBuff.m_slSkillIndex >= 423 && sBuff.m_slSkillIndex <= 428 )
		{
			// ó���̸� ����Ʈ�� ������...
			if(pEG==NULL)
			{
				// ���� ����Ʈ - ���� ������ ��������� ����...
				pEG = StartEffectGroup( "STATE_LOVE", &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
				//		penEntity->GetModelInstance()->m_pEG = pEG;
			}

			sBuff.m_pEG =  pEG;
		}
		// -------------------------------------------------<<
		else if (pItemData && pItemData->GetType() == CItemData::ITEM_POTION && strlen(pItemData->GetArmorEffectName()) > 0)
		{
			pEG = StartEffectGroup(pItemData->GetArmorEffectName(), &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
			sBuff.m_pEG = pEG;
		}

		// wooss 070310 ----------------------->><<
		// kw : WSS_WHITEDAY_2007
		// Add lovemagic buff (wind - skill index 423 )
		if(sBuff.m_slItemIndex ==391||sBuff.m_slItemIndex == 1226||sBuff.m_slItemIndex ==1227 || sBuff.m_slSkillIndex == 423	//�̼���� �����϶� ������Ʈ�� ���� �ϵ��ڵ�..�Ѥ�;
			|| sBuff.m_slItemIndex ==2407 || sBuff.m_slItemIndex ==2408	|| sBuff.m_slItemIndex ==2609 || sBuff.m_slItemIndex == 2845	//���� ������, �ٶ��� �ӵ� ����
			|| sBuff.m_slItemIndex == 2500
			|| sBuff.m_slItemIndex == 5018 || sBuff.m_slItemIndex == 5019 // ���� 2 ������
			)	
		{
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetSpeedUp(FALSE, pTarget->m_nIdxClient, TRUE);
		}

		pTarget->AddBuff( sBuff );
	}

	if (_pNetwork->SearchLegitList(pPack->charIndex))
	{
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetRepairLegit(pPack->charIndex, pTarget);
	}

	pTarget->cha_sbShopType = pPack->personalshop.type;		

	if(pPack->personalshop.type != PST_NOSHOP)
	{
		CTString strShopName = pPack->personalshop.name;
		pTarget->ShopMsg.SetChatMsg( strShopName );
		penPlayerEntity->SetShopData( pTarget->m_nIdxClient, pPack->personalshop.type );
	}
	// ��� ����.

	pTarget->cha_sbGuildRank = pPack->guildinfo.guildMark;

	pTarget->cha_lGuildIndex	= pPack->guildinfo.index;
	pTarget->cha_strGuildName	= pPack->guildinfo.name;
	pTarget->cha_lGuildPosition	= pPack->guildinfo.pos;
	pTarget->cha_reborn 		= pPack->reborn;
	pTarget->cha_color_name 	= pPack->color_name;

#ifdef GUILD_MARK
	if( pPack->guildinfo.guildMark_row >= 0 )
	{
		if (pTarget->pGuildmark == NULL)
		{
			pTarget->pGuildmark = new CUIGuildMarkIcon;
			pTarget->pGuildmark->Create(NULL, 0, 0, 15, 15);
		}

		pTarget->pGuildmark->CalcUV(pPack->guildinfo.guildMark_row, pPack->guildinfo.guildMark_col, true);
		pTarget->pGuildmark->CalcUV(pPack->guildinfo.guildMark_bg_row, pPack->guildinfo.guildMark_bg_col, false);
	}
#endif

	// WSS_DRATAN_SEIGEWARFARE 2007/08/01
	// ���� �ִ� ����
	if(pPack->playerState & PLAYER_STATE_CRISTAL_RESPOND)
	{
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetConsensus(pTarget->m_nIdxServer);
		_pUISWDoc->StartConsensusEffect(pTarget->m_nIdxServer, pTarget->m_pEntity); // WSS_DRATAN_SIEGEWARFARE 2007/10/14		
	}

	CUIManager* pUIManager = CUIManager::getSingleton();

	// assist_state ���� ���ؿ� ���� �ο��� ���� ����Ʈ�� �߰��Ѵ�.
	// ������ ���������� ���� ����� �����ϴ� ����Ʈ�� ���⼭ ���̰�,
	// �ǳ� ���� �վ��� ������ �Ͱ� ���� ����Ʈ�� MSG_CHAR_STATUS���� ���δ�.
	if(penEntity->en_pmiModelInstance)
	{
		CStatusEffect::eRelation rel = CStatusEffect::R_NONE;
		if(GAMEDATAMGR()->GetPartyInfo()->IsPartyMember(pTarget->m_nIdxServer))
		{
			// 051203 ��Ƽ ����� ���.  �÷��׸� ����.
			penEntity->SetSecondExtraFlagOn( ENF_EX2_MYPARTY );
			rel = CStatusEffect::R_PARTY;
		}
		pTarget->ChangeStatus(&penEntity->en_pmiModelInstance->m_tmSkaTagManager, pPack->assistInfo.state, rel);			
	}
	else
	{
		ASSERTALWAYS("Character must have ska model and tag manager.");
	}

	int nGMLevel = 2;

	if (g_iCountry == RUSSIA)
		nGMLevel = 7;

	if(IS_FLAG_ON(pPack->assistInfo.state, EST_ASSIST_INVISIBLE) && _pNetwork->m_ubGMLevel < nGMLevel)
	{
		penEntity->SetFlags(penEntity->GetFlags() | ENF_HIDDEN);
	}
	else
	{
		penEntity->SetFlags(penEntity->GetFlags()&~ENF_HIDDEN);
	}

	if(IS_FLAG_ON(pPack->assistInfo.state, EST_ASSIST_FAKEDEATH))
	{
		INDEX animID = ska_StringToID("ro_die_01");//Hardcoding
		penEntity->GetModelInstance()->AddAnimation(animID, AN_CLEAR, 1.0f, 0);
		//hardcoding, CCharacterBase�� m_bIdleAnim property�� �����´�.
		if(penEntity->en_pecClass)
		{
			CDLLEntityClass *pdecDLLBaseClass	= penEntity->GetClass()->ec_pdecDLLClass->dec_pdecBase;
			CEntityProperty *pEP = pdecDLLBaseClass->PropertyForTypeAndID(CEntityProperty::EPT_BOOL, 250);
			if(pEP)
			{
				ENTITYPROPERTY( &*penEntity, pEP->ep_slOffset, BOOL) = FALSE;
			}
		}
	}
	//0221 ���ŷ�ƾ
	pTarget->cha_nChangeMobId = pPack->changeIndex;

	if(pPack->changeIndex != -1)
	{
		penPlayerEntity->AppearChaPolymoph(penEntity, pPack->changeIndex);
	}

	pTarget->cha_nFame = pPack->fame;

	if ( !(pPack->mapAttr & MATT_UNWALKABLE) )
	{
		pTarget->cha_sbAttributePos = pPack->mapAttr;
	}

	pTarget->cha_sbJoinFlagMerac = pPack->merac_join_flag;
	pTarget->cha_sbJoinFlagDratan = pPack->dratan_join_flag;
	pTarget->cha_nTransformIndex = pPack->evocationIndex;

	if(pTarget->cha_nTransformIndex != 0)
	{
		penPlayerEntity->AppearChaTransform(penEntity, pTarget->cha_nTransformIndex);
	}

	if( pPack->pet.grade )
	{		
		INDEX iPetType;
		INDEX iPetAge;
		_pNetwork->CheckPetType( pPack->pet.grade, iPetType, iPetAge );				
		const BOOL bPetRide = PetInfo().IsRide(iPetType, iPetAge);

		pTarget->cha_iPetType = iPetType;
		pTarget->cha_iPetAge	= iPetAge;
		if( pTarget->cha_bPetRide != bPetRide )
		{
			// ���� Ÿ���� �����ؾ� �ϴ� ���...
			if( iPetType != -1 && iPetAge != -1 && bPetRide )			
			{
				// [070824: Su-won] PET_COLOR_CHANGE
				INDEX iPetColoredType = iPetType | (pPack->pet.color<<8);
				_pNetwork->RidePet( pTarget->m_pEntity, NULL, iPetColoredType );
			}
			pTarget->cha_bPetRide = bPetRide;
		}
	}

	if (pPack->isPlayerStateSupporter)
	{
		penPlayerEntity->PlAddAccessoryEffect(penEntity, pTarget);
	}

	pTarget->cha_sbPresscorps = pPack->pressCorps;	
#ifdef REZABOT 
	pTarget->cha_botting = pPack->a_botting;
#endif
	pTarget->cha_Label = pPack->expedLabel;
	pTarget->cha_NickType = pPack->currentTitle;

	if ( pPack->currentTitle > 0)	// ȣĪ�� �ִٸ�
	{
		penEntity->SetNickNameDamageEffect(pPack->currentTitle, CEntity::NICKNAME_ATTACH_EFFECT);
	}

	if (pPack->mountApetIndex > 0)
	{
		CEntity* tempOtherEntity = NULL;
		tempOtherEntity = _pNetwork->GetEntityByTypeIndex(MSG_CHAR_WILDPET, pPack->mountApetIndex);

		if (tempOtherEntity && tempOtherEntity->en_EntityUseType == CEntity::EU_NORMAL) // �� ���� ���� ������ �� �¿� ���´�.
		{
			CWildPetTarget* pWild = tempOtherEntity->en_pWildPetTarget;
			pWild->m_bMount = TRUE;
			CTString szModelFileName = CWildPetData::getData(pWild->m_nIndex)->smcFile[pWild->m_sbTransStat];
			_pNetwork->RideWildPet( penEntity, tempOtherEntity, szModelFileName );
		}
	}

	if ( pPack->merac_join_flag > 0 )
	{
		// Date : 2005-07-13(���� 5:29:49), By Lee Ki-hwan
		// ���� Effect
		_pUISWDoc->StartEffect( pPack->charIndex, penEntity, pPack->merac_join_flag, pPack->guildinfo.index );

		// ����� ����Ʈ �߰� // Date : 2005-11-18(���� 3:43:49), By Lee Ki-hwan
		_pUISWDoc->StartGuildMasterEffect( pPack->charIndex, penEntity, pPack->merac_join_flag, pPack->guildinfo.index, pPack->guildinfo.pos );
	}	
	// WSS_DRATAN_SEIGEWARFARE 2007/08/29
	// ���� ����Ʈ ó��
	if( pPack->dratan_join_flag > 0 )
	{
		// TODO :: ����Ʈ ������ ���� ó��...
		_pUISWDoc->StartEffect( pPack->charIndex, penEntity, pPack->dratan_join_flag, pPack->guildinfo.index );
		_pUISWDoc->StartGuildMasterEffect( pPack->charIndex, penEntity, pPack->dratan_join_flag, pPack->guildinfo.index, pPack->guildinfo.pos );
	}

	// Date : 2005-04-06(���� 5:04:54), By Lee Ki-hwan
	// ��� ���� ���̶�� ��� Index�� üũ�ؼ� Effect�� �ѷ���
	if ( pUIManager->GetGuildBattle()->IsInBattle() )
	{
		int nEnemyGuild = pUIManager->GetGuildBattle()->IsEnemyGuild( pPack->guildinfo.index );
		if( nEnemyGuild == 1 ) // ���� (����)
		{
			pUIManager->GetGuildBattle()->StartGuildEffect( pPack->charIndex, penEntity, TRUE );
		}
		else if( nEnemyGuild == -1 ) // �Ʊ� (û��)
		{
			pUIManager->GetGuildBattle()->StartGuildEffect( pPack->charIndex, penEntity, FALSE );
		}
	}

	pTarget->cha_itemEffect.AddPetStashEffect( pPack->petStashManagerEffect, &penEntity->en_pmiModelInstance->m_tmSkaTagManager );

	pTarget->cha_iSyndicateType = pPack->syndicate.type;
	pTarget->cha_iSyndicateGrade = pPack->syndicate.grade;


}

void CSessionState::updatePetAppear( CNetworkMessage *istr )
{
	UpdateClient::appearPet* pPack = reinterpret_cast<UpdateClient::appearPet*>(istr->GetBuffer());

	CPlacement3D	plPlacement;	

	plPlacement.pl_PositionVector(1)	= pPack->x;
	plPlacement.pl_PositionVector(2)		= pPack->h + 1.0f;
	plPlacement.pl_PositionVector(3)	= pPack->z;
	plPlacement.pl_OrientationAngle(1)	= 0.0f ;
	plPlacement.pl_OrientationAngle(2)	= 0.0f;
	plPlacement.pl_OrientationAngle(3)	= 0.0f;

	INDEX iPetType	= -1;
	INDEX iPetAge	= -1;
	_pNetwork->CheckPetType( pPack->grade, iPetType, iPetAge );

	// NOTE : Ż�� �ִ� �ֿϵ������� �Ǵ��Ͽ�, ĳ���͸� �¿�ϴ�.
	// NOTE : �ֿϵ����� Ÿ�� ���� ��쿡��, PetŸ�� ������ �߰����� ����(�� �ֿϵ����϶��� �� Ÿ�� ����â �����Ұ�...)
	const BOOL bPetRide = PetInfo().IsRide(iPetType, iPetAge);	

	//-----------------------------------------------------------
	CEntity* penEntity = _pNetwork->ga_World.CreateEntity_t(plPlacement, CLASS_PET, -1, TRUE);

	if (bPetRide == FALSE)
	{
		// NOTE : �ֿϵ����� Ÿ���ִ� ��쿡��, �� ��ƼƼ�� ĳ���ͷ� ��޵Ǳ� ������,
		// NOTE : ��Ÿ���� �߰��ϸ� �ȵȴ�.
		// NOTE : ���࿡ �߰��ϰ� �Ǹ�, DISAPPEAR���� ��ƼƼ�� Destroy�ϱ� ������
		// NOTE : �ִϸ��̼ǽ� ��ƼƼ�� ��ȿ���� �ʰ� �Ǿ ������ ��.
		// FIXME : Factory�� �ٲܱ�???
		DeleteObject(MSG_CHAR_PET, pPack->charIndex);
		CPetTarget* pTarget = new CPetTarget;
		CTString strPetName = pPack->ownerName + _S(2228,"�� ") + CTString(" ") + PetInfo().GetName(iPetType, iPetAge);
		CTString strPetCardName = pPack->name;
		CTString strPetOwnerName = pPack->ownerName;
		pTarget->SetData( pPack->charIndex, strPetName, strPetOwnerName, pPack->ownerIndex, iPetType, iPetAge, penEntity, pPack->yLayer, strPetCardName);	
		pTarget->m_nIdxClient = penEntity->en_ulID;
		penEntity->SetNetworkID(pPack->charIndex);
		penEntity->en_pPetTarget = pTarget;

		ACTORMGR()->AddObject(pTarget);
	}

	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetPetData( penEntity, pPack->hp, pPack->maxHp );

	BOOL bUseAI		= FALSE;

	// �� ���̸�, �κ��丮�� �����ؼ� ������ �ٴϴ� ���� ���.
	if( pPack->ownerIndex == _pNetwork->MyCharacterInfo.index )
	{
		// �� Ÿ�� ����â ������ �����մϴ�.
		bUseAI		= TRUE;
		penEntity->SetFirstExtraFlagOn(ENF_EX1_CURRENT_PET);
		CPetTargetInfom* pPetInfo = INFO()->GetMyPetInfo();
		pPetInfo->lIndex		= pPack->charIndex;
		pPetInfo->bIsActive		= TRUE;
		pPetInfo->TransformIndex = pPack->turnToNpc; // �� ���� NPC �ε���
		pPetInfo->pen_pEntity	= penEntity;

		_pNetwork->UpdatePetTargetInfo( pPack->charIndex );
		CUIManager::getSingleton()->GetPetTargetUI()->openUI();
	}	

	penEntity->InitAsSkaModel();
	penEntity->SetSkaModel(PetInfo().GetFileName(iPetType, iPetAge));
	PetInfo().SetPetDataToEntity(iPetType, iPetAge, penEntity, bUseAI);
	penEntity->SetNetworkID(pPack->charIndex);
	penEntity->Initialize();
	penEntity->FallDownToFloor();

	// �� ���� ���� �������� ����� ���¶�� �ؽ��� ������ �ٲ���...
	if( pPack->color >0 )
	{
		CTString strTexFile =PetInfo().GetColoredTexFileName(iPetType, iPetAge, pPack->color);
		penEntity->GetModelInstance()->mi_aMeshInst[0].mi_tiTextures[0].ti_toTexture.SetData_t( strTexFile );
	}

	// eons �� ����
	// �ϴ� �� �� ������ ��ģ �� ������ ����.
	if (pPack->turnToNpc > 0)
	{
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->TransfromPet(penEntity, pPack->turnToNpc, pPack->turnToNpcSize);
	}

	if( pPack->mapAttr & MATT_WAR || pPack->mapAttr & MATT_PEACE)
		penEntity->SetFlagOn(ENF_HIDDEN);

	if(pPack->bNew){
		CTString strEffect;
		strEffect.PrintF( "pet_%c%d_summon", (iPetType==0)?'h':'d', iPetAge+1 );
		PetStartEffectGroup( strEffect, pPack->charIndex );
	}

}

void CSessionState::updateElementalAppear( CNetworkMessage *istr )
{
	UpdateClient::appearElemental* pPack = reinterpret_cast<UpdateClient::appearElemental*>(istr->GetBuffer());

	CPlacement3D	plPlacement;

	plPlacement.pl_PositionVector(1)	= pPack->x;
	plPlacement.pl_PositionVector(2)		= pPack->h + 1.0f;
	plPlacement.pl_PositionVector(3)	= pPack->z;
	plPlacement.pl_OrientationAngle(1)	= 0.0f;
	plPlacement.pl_OrientationAngle(2)	= 0.0f;
	plPlacement.pl_OrientationAngle(3)	= 0.0f;	

	CEntity* penEntity = NULL;
	if( _pNetwork->m_bSingleMode )
	{
		penEntity = _pNetwork->ga_World.CreateEntity_t(CEntity::GetPlayerEntity(0)->GetPlacement(), CLASS_SUMMON, -1, TRUE);
		if( penEntity )
			_pNetwork->ga_World.m_vectorTargetNPC.push_back(penEntity);
	}
	else
	{
		penEntity = _pNetwork->ga_World.CreateEntity_t(plPlacement, CLASS_SUMMON, -1, TRUE);
	}
	penEntity->InitAsSkaModel();	
	penEntity->SetSkaModel( SlaveInfo().GetFileName(pPack->elementalType) );		
	SlaveInfo().SetSlaveDataToEntity( pPack->elementalType, penEntity, pPack->ownerIndex == _pNetwork->MyCharacterInfo.index );
	penEntity->SetNetworkID(pPack->charIndex);
	penEntity->Initialize();
	//penEntity->FallDownToFloor();	
	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetElementalData(penEntity, pPack->hp, pPack->maxHp);
	
	ObjInfo* pInfo = ObjInfo::getSingleton();
	CSlaveTargetInfom* pSlaveInfo = NULL;
	// �� ��ȯ����� ǥ������.
	if( pPack->ownerIndex == _pNetwork->MyCharacterInfo.index )
	{
		CUIManager* pUIManager = CUIManager::getSingleton();
		penEntity->SetFirstExtraFlagOn(ENF_EX1_CURRENT_SLAVE);

		for( int i = UI_SUMMON_START; i <= UI_SUMMON_END; ++i )
		{
			CSummonUI* pUISummon = (CSummonUI*)pUIManager->GetUI(i);

			pSlaveInfo = pInfo->GetMySlaveInfo(i - UI_SUMMON_START);
			if( !pUISummon->GetSummonEntity() && pSlaveInfo != NULL )
			{
				pUISummon->SetSummonIndex(pPack->charIndex);
				pUISummon->SetSummonEntity( penEntity );
				pUISummon->SetSummonType( pPack->elementalType );
				pUISummon->openUI();
				//pUISummon->SetCommand(CSlaveInfo::COMMAND_PROTECTION);
				pSlaveInfo->fHealth	= pPack->hp;
				pSlaveInfo->fMaxHealth = pPack->maxHp;
				break;
			}
		}
	}

	// NOTE : �ֿϵ����� Ÿ���ִ� ��쿡��, �� ��ƼƼ�� ĳ���ͷ� ��޵Ǳ� ������,
	// NOTE : ��Ÿ���� �߰��ϸ� �ȵȴ�.
	// NOTE : ���࿡ �߰��ϰ� �Ǹ�, DISAPPEAR���� ��ƼƼ�� Destroy�ϱ� ������
	// NOTE : �ִϸ��̼ǽ� ��ƼƼ�� ��ȿ���� �ʰ� �Ǿ ������ ��.
	// FIXME : Factory�� �ٲܱ�???
	DeleteObject(MSG_CHAR_ELEMENTAL, pPack->charIndex);	

	CSlaveTarget* pTarget = new CSlaveTarget;
	
	CTString strSlaveName = pPack->ownerName + _S(2228,"�� ") + CTString(" ") + SlaveInfo().GetName(pPack->elementalType);		// ����
	CTString strOwnerName = pPack->ownerName;
	pTarget->SetData( pPack->charIndex, strSlaveName, strOwnerName, pPack->ownerIndex, pPack->elementalType, penEntity, pPack->yLayer );	
	pTarget->m_nIdxClient = penEntity->en_ulID;
	penEntity->en_pSlaveTarget	= pTarget;
	
	ACTORMGR()->AddObject(pTarget);

	BuffInfo	sBuff;
	sBuff.m_llStartTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();
	
	ASSERT( pTarget->slave_BuffCount == 0 );
	pTarget->slave_BuffCount = 0;
	for( int i = 0; i < pPack->assistInfo.count; i++ )
	{
		sBuff.m_slItemIndex = pPack->assistInfo.list[i].index;
		sBuff.m_slSkillIndex = pPack->assistInfo.list[i].dbIndex;
		sBuff.m_sbLevel = pPack->assistInfo.list[i].level;
		sBuff.m_slRemain = pPack->assistInfo.list[i].remain;
		sBuff.m_slRemainCount = pPack->assistInfo.list[i].remainCount;
		pTarget->AddBuff( sBuff );
	}

	// assist_state ���� ���ؿ� ���� �ο��� ���� ����Ʈ�� �߰��Ѵ�.
	// ������ ���������� ���� ����� �����ϴ� ����Ʈ�� ���⼭ ���̰�,
	// �ǳ� ���� �վ��� ������ �Ͱ� ���� ����Ʈ�� MSG_CHAR_STATUS���� ���δ�.
	if(penEntity->en_pmiModelInstance)
	{
		pTarget->ChangeStatus(&penEntity->en_pmiModelInstance->m_tmSkaTagManager, pPack->assistInfo.state);
	}
	else
	{
		ASSERTALWAYS("Character must have ska model and tag manager.");
	}

	SlaveInfo().StartIdleEffect( pPack->charIndex, pPack->elementalType, penEntity );		
	// ��ȯ�� ������ ���� ( ĳ�� ������ �۰� )
	if(!pPack->isBigSize)
	{
		penEntity->en_pmiModelInstance->StretchModel(FLOAT3D( 0.7f,0.7f,0.7f ));
	}

//#ifdef SORCERER_SUMMON_VILLAGE_VISIBLE_NA_20081008//IsFlagOn(ENF_HIDDEN)
	if (IsGamigo(g_iCountry) == TRUE)
	{
		if (pPack->mapAttr & MATT_PEACE)
			penEntity->SetFlagOn(ENF_HIDDEN);
	}
//#endif	// SORCERER_SUMMON_VILLAGE_VISIBLE_NA_20081008
}

void CSessionState::updateAPetAppear( CNetworkMessage *istr )
{
	UpdateClient::appearApet* pPack = reinterpret_cast<UpdateClient::appearApet*>(istr->GetBuffer());

	CPlacement3D	plPlacement;	
	INDEX			nItemIndex[APET_WEARPOINT], nItemPlus[APET_WEARPOINT];

	int				i;
	for( i = 0; i < APET_WEARPOINT; ++i )
	{
		nItemIndex[i] = pPack->weaponList[i].dbIndex;
		nItemPlus[i] = pPack->weaponList[i].plus;
	}
	
	plPlacement.pl_PositionVector(1)	= pPack->x;
	plPlacement.pl_PositionVector(2)		= pPack->h + 1.0f;
	plPlacement.pl_PositionVector(3)	= pPack->z;
	plPlacement.pl_OrientationAngle(1)	= 0.0f ;
	plPlacement.pl_OrientationAngle(2)	= 0.0f;
	plPlacement.pl_OrientationAngle(3)	= 0.0f;
	
	// ���� ������ �� ���� ���� �ȱ׸����� ���
	// ����Ʈ ���°� �ƴҰ�쿡�� üũ(����Ʈ �����϶��� ���� ���Ǿ �ѹ� ���Ե�)
	if (pPack->ownerIndex == _pNetwork->MyCharacterInfo.index && _pNetwork->MyCharacterInfo.bWildPetRide == FALSE)
	{
		if (_pNetwork->MyWearItem[WEAR_PET].IsEmptyItem() == TRUE)
			return; // �׻� �������� ���� ������ �� ���� �׷���		

		if (_pNetwork->MyWearItem[WEAR_PET].GetItemPlus() != pPack->charIndex)
			return; // ����� ��� �ٸ� ���� ���� �� ����
	}
	
	CTString strFile = CWildPetData::getData(pPack->dbIndex)->smcFile[pPack->transSate];

	if (strFile.IsEmpty() == TRUE)
	{
		LOG_DEBUG("Error : updateAPetAppear No Pet Name!!!");
		return;
	}

	CEntity* penEntity = _pNetwork->ga_World.CreateEntity_t(plPlacement, CLASS_WILDPET, -1, TRUE);

	penEntity->InitAsSkaModel();
	penEntity->SetSkaModel(strFile);
	penEntity->SetNetworkID(pPack->charIndex);

	DeleteObject(MSG_CHAR_WILDPET, pPack->charIndex);

	CWildPetTarget* pTarget = new CWildPetTarget;

	CTString strWildPetName = pPack->name;
	pTarget->m_nIndex = pPack->dbIndex;
	pTarget->m_nLevel = pPack->level;
	pTarget->m_strName = strWildPetName;

	pTarget->m_sbTransStat = pPack->transSate;
	pTarget->m_bMount = pPack->isMount;
	// [ldy1978220 2011/7/6] ITS-1243 ���� appear ���� ���� �� ����� ������ �ٷ� ���� �ʱ� ������ 
	// ����� �ִϸ��̼��� ��µǴ� ������ ��Ÿ������ �ּҰ� 1�� ���� 
	pTarget->m_nStm = 1;	
	pTarget->m_nHP = pPack->hp;
	pTarget->m_nMaxHP = pPack->maxHp;
	pTarget->m_nIdxServer = pPack->charIndex;
	pTarget->m_nType = pPack->type;
	pTarget->m_nOwnerIndex = pPack->ownerIndex;
	pTarget->m_yLayer = pPack->yLayer;
	pTarget->m_sbAttributePos = pPack->mapAttr;
	pTarget->m_nIdxClient = penEntity->en_ulID;
	pTarget->SetWildPetToEntity(penEntity, pPack->dbIndex, nItemIndex, nItemPlus);

	ACTORMGR()->AddObject(pTarget);

	for( i = 0; i < 4; ++i )
	{
		pTarget->m_nPetWearIndex[i] = nItemIndex[i];
		pTarget->m_nPetWearPlus[i] = nItemPlus[i];
		_pGameState->WearingArmorTest(penEntity->GetModelInstance(), pTarget->m_nPetWearIndex[i]);
	}

	penEntity->en_pWildPetTarget	= pTarget;

	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetWildPetData( penEntity, pPack->hp, pPack->maxHp );

	if (pTarget->m_nOwnerIndex == _pNetwork->MyCharacterInfo.index)
	{
		_pNetwork->MyCharacterInfo.bWildPetRide = pPack->isMount;
		pTarget->bIsActive = TRUE;
		penEntity->SetFirstExtraFlagOn(ENF_EX1_CURRENT_WILDPET);
		INFO()->SetMyApet(pTarget);
		CUIManager::getSingleton()->GetWildPetTargetInfo()->openUI();
	}

	penEntity->Initialize();
	// ������ ���� �Դ´�.
	if( pPack->isMount )
	{
		CTString szModelFileName = CWildPetData::getData(pPack->dbIndex)->smcFile[pPack->transSate];
		if( pPack->ownerIndex == _pNetwork->MyCharacterInfo.index )
		{
			_pNetwork->RideWildPet( CEntity::GetPlayerEntity(0), penEntity, szModelFileName );
		}
		else
		{
			CEntity* tempOtherEntity = NULL;
			tempOtherEntity = _pNetwork->GetEntityByTypeIndex(MSG_CHAR_PC, pPack->ownerIndex);

			if( NULL != tempOtherEntity )
				_pNetwork->RideWildPet( tempOtherEntity, penEntity, szModelFileName );
			else	// ���� ����Ʈ�� �õ��ߴµ� ������ ��� ���� �⺻ �𵨸� ���´�.
			{
				pTarget->m_bMount = FALSE;
			}
		}
	}
	else
	{
		// �޸����� �ƴ϶�� ������ ���´�. [3/24/2011 rumist]
		if( 1 != CWildPetData::getData(pPack->dbIndex)->type )
		{
			if( pPack->ownerIndex == _pNetwork->MyCharacterInfo.index )
				_pNetwork->LeaveWildPet( CEntity::GetPlayerEntity(0) );
			else
			{
				// �� �ƴ� ���� ��Ī.
				CEntity* tempOtherEntity = NULL;
				tempOtherEntity = _pNetwork->GetEntityByTypeIndex(MSG_CHAR_PC, pPack->ownerIndex);

				if( NULL != tempOtherEntity )
					_pNetwork->LeaveWildPet( tempOtherEntity );
			}
		}
	}
	// pet appear skill. �̰� ���� �����ؼ� �����Ҷ��� ����ϴ� ��ų. [12/1/2010 rumist]
	ASSERT( 0 < pPack->dbIndex );
	int temSummonSkill = CWildPetData::getData(pPack->dbIndex)->nSummonSkill[pPack->transSate];
	
	if (pPack->isAction && temSummonSkill > 0 &&
		pPack->ownerIndex == _pNetwork->MyCharacterInfo.index )
	{
		CSelectedEntities m_dcEnemies;
		CSkill &SkillData = _pNetwork->GetSkillData(temSummonSkill);

		m_dcEnemies.Clear();
		m_dcEnemies.Add(penEntity);

		_pNetwork->SendSlaveSkillMessageInContainer(temSummonSkill, penEntity, m_dcEnemies, FALSE);

		int lv = MY_INFO()->GetSkillLevel(temSummonSkill) + 1;
		_pNetwork->FindTargetsInRange(penEntity, penEntity, m_dcEnemies, 
							SkillData.GetAppRange(), SkillData.GetTargetNum(lv) - 1, 360.0f, temSummonSkill );

		_pNetwork->SendSlaveSkillMessageInContainer(temSummonSkill, penEntity, m_dcEnemies, TRUE);
	}
	penEntity->FallDownToFloor();
}

void CSessionState::updateDisappear( CNetworkMessage *istr )
{
	UpdateClient::charDisappear* pPack = reinterpret_cast<UpdateClient::charDisappear*>(istr->GetBuffer());

	DeleteObject(pPack->charType, pPack->charIndex);
}

IMPLEMENT_MSG_UPDATE(updateDisappearEffect)
{
	UpdateClient::charDisappearForClientEffect* pPack = reinterpret_cast<UpdateClient::charDisappearForClientEffect*>(istr->GetBuffer());

	CEntity* penPlEntity;
	CPlayerEntity* penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
	penPlayerEntity = static_cast<CPlayerEntity*>(penPlEntity);

	if (penPlayerEntity != NULL)
	{
		penPlayerEntity->Read_net_DissappearEffect(istr);
	}

	if (pPack->owner_index == _pNetwork->MyCharacterInfo.index)
		_pNetwork->MyCharacterInfo.useTotem = false;
}
IMPLEMENT_MSG_UPDATE(updateDisappearAll)
{
	INFO()->TargetClear();
	ACTORMGR()->RemoveAll();
}

IMPLEMENT_MSG_UPDATE(ClearTarget)
{
	UpdateClient::targetClear* pPack = reinterpret_cast<UpdateClient::targetClear*>(istr->GetBuffer());
	ObjInfo* pInfo = ObjInfo::getSingleton();
	
	if (pPack->targetIndex == -1 || 
		(pInfo->GetTargetServerIdx(eTARGET) == pPack->targetIndex))
	{
		pInfo->TargetClear();
	}	
}

void CSessionState::updateElementalStatus( CNetworkMessage* istr )
{
	UpdateClient::elementalStatus* pPack = reinterpret_cast<UpdateClient::elementalStatus*>(istr->GetBuffer());

	CUIManager* pUIManager = CUIManager::getSingleton();

	ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_SLAVE, pPack->charIndex);
	ObjInfo* pInfo = ObjInfo::getSingleton();
	CSlaveTargetInfom* pSlaveInfo = NULL;

	if (pObject != NULL)
	{
		CSlaveTarget* pTarget = static_cast< CSlaveTarget* >(pObject);

		if (pTarget->GetEntity())
		{
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetElementalData(pTarget->GetEntity(), pPack->hp, pPack->maxHp);
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetElementalStatus(
				pTarget->GetEntity(), pPack->attackSpeed, pPack->magicSpeed, pPack->skillSpeed, pPack->walkSpeed, pPack->runSpeed, pPack->attackRange);
		}

		pTarget->m_yLayer = pPack->yLayer;

		// �� ��ȯ���� ���...
		if (pTarget->slave_OwnerIndex == _pNetwork->MyCharacterInfo.index)
		{
			for( int i = UI_SUMMON_START; i <= UI_SUMMON_END; ++i )
			{
				CSummonUI* pUISummon = (CSummonUI*)pUIManager->GetUI(i);
				pSlaveInfo = pInfo->GetMySlaveInfo(i - UI_SUMMON_START);

				if( pUISummon->GetSummonEntity() && pUISummon->GetSummonIndex() == pPack->charIndex && pSlaveInfo != NULL )
				{
					pUISummon->SetMaxTime(pPack->remainTime);		// MaxTime�� �ѹ��� �����˴ϴ�.
					pSlaveInfo->fHealth	= pPack->hp;
					pSlaveInfo->fMaxHealth = pPack->maxHp;
					pUISummon->SetLeftTime(pPack->remainTime);
				}
			}
		}
		BuffInfo	sBuff;
		sBuff.m_llStartTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();	

		pTarget->slave_BuffCount = 0;
		for( int i = 0; i < pPack->assistinfo.count; i++ )
		{
			//(*istr) >> sBuff.m_slItemIndex >> sBuff.m_slSkillIndex >> sBuff.m_sbLevel >> sBuff.m_slRemain;	//����
			sBuff.m_slItemIndex = pPack->assistinfo.list[i].index;
			sBuff.m_slSkillIndex = pPack->assistinfo.list[i].dbIndex;
			sBuff.m_sbLevel = pPack->assistinfo.list[i].level;
			sBuff.m_slRemain = pPack->assistinfo.list[i].remain;
			sBuff.m_slRemainCount = pPack->assistinfo.list[i].remainCount;	//2012/11/12 jeil ��ųȮ����� �߰�
			pTarget->AddBuff( sBuff );
		}
	}
}

void CSessionState::updatePartyMemberInfo( CNetworkMessage* istr )
{
	UpdateClient::partyInfo* pPack = reinterpret_cast<UpdateClient::partyInfo*>(istr->GetBuffer());
	GAMEDATAMGR()->GetPartyInfo()->PartyMemberInfo( pPack->charIndex, pPack->level, pPack->hp, pPack->maxHp, pPack->mp, pPack->maxMp, pPack->x, pPack->z, pPack->yLayer, pPack->zoneIndex, pPack->isOnline );
}

void CSessionState::updateExpedMemberInfo( CNetworkMessage* istr )
{
	UpdateClient::expedInfoForChar* pPack = reinterpret_cast<UpdateClient::expedInfoForChar*>(istr->GetBuffer());
	GAMEDATAMGR()->GetPartyInfo()->ExpeditionMemberInfo(pPack->charIndex, pPack->group, pPack->level, pPack->hp, pPack->maxHp, pPack->mp, pPack->maxMp, pPack->x, pPack->z, pPack->yLayer, pPack->zoneIndex, pPack->isOnline);
}

void CSessionState::updateStatusPC( CNetworkMessage *istr )
{
	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->Read_net_StatusPC(istr);
}

void CSessionState::updateStatusNPC( CNetworkMessage *istr )
{
	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->Read_net_StatusNPC(istr);
}

void CSessionState::updateStatusPet( CNetworkMessage *istr )
{	
	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->Read_net_StatusPet(istr);
}

void CSessionState::updateStatusElemental( CNetworkMessage *istr )
{
	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->Read_net_StatusElemental(istr);
}

void CSessionState::updateStatusAPet( CNetworkMessage* istr )
{
	UpdateClient::attackPetStatus* pPack = reinterpret_cast<UpdateClient::attackPetStatus*>(istr->GetBuffer());
	CUIManager* pUIManager = CUIManager::getSingleton();

	CPlayerEntity* penPlayerEntity;
	penPlayerEntity = static_cast<CPlayerEntity*>( CEntity::GetPlayerEntity(0) );

	ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_WILDPET, pPack->charIndex);

	if (pObject != NULL)
	{
		CWildPetTarget* pTarget = static_cast< CWildPetTarget* >(pObject);

		pTarget->m_strName = pPack->charName;
		pTarget->m_nLevel = pPack->level;
		pTarget->m_nType = pPack->protoType;
		pTarget->m_exp = pPack->exp;
		pTarget->m_next_exp = pPack->needExp;
		pTarget->m_nHP = pPack->hp;
		pTarget->m_nMaxHP = pPack->maxHp;
		pTarget->m_nMP = pPack->mp;
		pTarget->m_nMaxMP = pPack->maxMp;
		pTarget->m_nFaith = pPack->faith;
		pTarget->m_nMaxFaith = pPack->maxFaith;
		pTarget->m_nStm = pPack->stamina;
		pTarget->m_nMaxStm = pPack->maxStamina;
		pTarget->m_nLevelupPoint = pPack->remainStat;
		pTarget->m_sbAttributePos = pPack->mapAttr;
		pTarget->m_yLayer = pPack->yLayer;
		pTarget->m_nStr = pPack->str;
		pTarget->m_nStrPlus = pPack->addStr;
		pTarget->m_nCon = pPack->con;
		pTarget->m_nConPlus = pPack->addCon;
		pTarget->m_nDex = pPack->dex;
		pTarget->m_nDexPlus = pPack->addDex;
		pTarget->m_nInt = pPack->intl;
		pTarget->m_nIntPlus = pPack->addIntl;

		pTarget->m_nWildPetState[STATE_ATTACK] = pPack->attack;
		pTarget->m_nWildPetState[STATE_MAGIC_ATTACK] = pPack->magicAttack;
		pTarget->m_nWildPetState[STATE_DEFENCE] = pPack->defence;
		pTarget->m_nWildPetState[STATE_MAGIC_DEFENCE] = pPack->maxDefence;
		pTarget->m_nWildPetState[STATE_HITPOINT] = pPack->hitPoint;
		pTarget->m_nWildPetState[STATE_AVOID] = pPack->avoid;
		
		pTarget->m_sbTransStat = pPack->transSate;
		pTarget->m_bMount = pPack->isMount;

		if (penPlayerEntity && pTarget->GetEntity())
		{
			penPlayerEntity->SetWildPetData(pTarget->GetEntity(), pPack->hp, pPack->maxHp);
		}

		if (pTarget->m_nOwnerIndex == _pNetwork->MyCharacterInfo.index)
		{
			INFO()->SetMyApet(pTarget);

			sPetItem_Info TemPet;

			TemPet.pet_index = pPack->charIndex;
			TemPet.pet_name = pPack->charName;
			TemPet.pet_level = pPack->level;
			TemPet.pet_str = pPack->str;
			TemPet.pet_con = pPack->con;
			TemPet.pet_dex = pPack->dex;
			TemPet.pet_int = pPack->intl;
			if (pPack->coolTime > 0)
			{
				TemPet.pet_cooltime = (unsigned int)_pTimer->GetLerpedCurrentTick() + pPack->coolTime;
			}else
			{
				TemPet.pet_cooltime = 0;
			}

			TemPet.pet_accexp = pPack->accExp;
			pUIManager->GetWildPetInfoUI()->AddWildPetInfo(TemPet);
			pUIManager->GetWildPetTargetInfo()->updateUI();
		}
	}
}

void CSessionState::updateDamage( CNetworkMessage* istr )
{
	UpdateClient::charDamage* pPack = reinterpret_cast<UpdateClient::charDamage*>(istr->GetBuffer());

	CEntity* penPlEntity;
	CPlayerEntity* penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
	penPlayerEntity = static_cast<CPlayerEntity*>(penPlEntity);

	if (pPack->charType == MSG_CHAR_PC)
	{
		penPlayerEntity->Read_net_Damage_Character(istr);
	}
	else
	{
		// �÷��̾ ������ �ٸ� ��ƼƼ�� ���.
		penPlayerEntity->Read_net_Damage(pPack->charType, &(*istr));
	}	

	// ��� ������ ��Ż�� Ÿ���� �ϴµ� ������ ������ ��� 
	CUIManager::getSingleton()->GetGuildWarPortal()->PortalCancel();
}

IMPLEMENT_MSG_UPDATE(StatusAPetSmall)
{
	UpdateClient::attackPetSmallStatus* pPack = reinterpret_cast<UpdateClient::attackPetSmallStatus*>(istr->GetBuffer());

	// MSG_SUB_APET_INFO: 
	// �� �޼��� ó����, �������� �� ������ UI�� �� ������ ��߳��� �ȴ�.(�ʿ伺�� ����)

	CUIManager* pUIManager = CUIManager::getSingleton();
	
	sPetItem_Info temPetInfo;

	temPetInfo.pet_index = pPack->charIndex;
	temPetInfo.pet_name = pPack->charName;
	temPetInfo.pet_level = pPack->level;
	temPetInfo.pet_str = pPack->str;
	temPetInfo.pet_con = pPack->con;
	temPetInfo.pet_dex = pPack->dex;
	temPetInfo.pet_int = pPack->intl;
	temPetInfo.pet_accexp = pPack->accExp;
	if (pPack->coolTime > 0)
	{
		temPetInfo.pet_cooltime = (unsigned int)_pTimer->GetLerpedCurrentTick() + pPack->coolTime;
	}
	else
	{
		temPetInfo.pet_cooltime = 0;
	}
	pUIManager->GetWildPetInfoUI()->AddWildPetInfo(temPetInfo);

}



IMPLEMENT_MSG_UPDATE(UpdateLevel)
{
	UpdateClient::LevelupInfo* pPack = reinterpret_cast<UpdateClient::LevelupInfo*>(istr->GetBuffer());

	_pNetwork->MyCharacterInfo.level = pPack->level;

	CTString strMessage;
	strMessage.PrintF(_S(6225, "�����մϴ�. [%d]������ �Ǿ����ϴ�."), pPack->level);

	CUIManager::getSingleton()->GetChattingUI()->AddSysMessage( strMessage, SYSMSG_USER);

	_UIAutoHelp->GetLvGuidString(pPack->level);
	_UIAutoHelp->LearnTheSkill(pPack->level);

	if (_UIAutoHelp->GetUpStatpoint() > 0)
	{
		strMessage.PrintF(_S(6212, "���� ����Ʈ %d���� ���� �Ǿ����ϴ�."), _UIAutoHelp->GetUpStatpoint());
		CUIManager::getSingleton()->GetChattingUI()->AddSysMessage( strMessage, SYSMSG_USER);
	}

}

IMPLEMENT_MSG_UPDATE(UpdateSettings)
{
    UpdateClient::settings* pPack = reinterpret_cast<UpdateClient::settings*>(istr->GetBuffer());

    _pNetwork->MyCharacterInfo.autopickup = pPack->autopickup;
    _pNetwork->MyCharacterInfo.autoigni = pPack->autoigni;
    _pNetwork->MyCharacterInfo.autosell = pPack->autosell;
}

IMPLEMENT_MSG_UPDATE(UpdateTargetHPInfo)
{
	UpdateClient::charHpInfo* pPack = reinterpret_cast<UpdateClient::charHpInfo*>(istr->GetBuffer());

	ObjInfo* pInfo = ObjInfo::getSingleton();
	
	if (pInfo->GetTargetServerIdx(eTARGET) == pPack->charIndex)
	{
		pInfo->SetTargetHealth(pPack->hp, pPack->maxHp);
	}
}

IMPLEMENT_MSG_UPDATE(UpdateCharHitType)
{
	UpdateClient::holyWaterState* pRecv = reinterpret_cast<UpdateClient::holyWaterState*>(istr->GetBuffer());

	if (pRecv == NULL)
		return;

	int nCharIndex = pRecv->charIndex;

	// 0 : �Ϲ�, 1 : ���Ǽ���, 2 : �ź��� ����
	int nType = 0;

	switch(pRecv->holyWaterItemIndex)
	{
	case DEF_HOLYWATER_STRONG:
		nType = 1;
		break;
	case DEF_HOLYWATER_MYSTERY:
		nType = 2;
		break;
	case DEF_HOLYWATER_DAMAGE:
		nType = 3;
		break;
	case DEF_HOLYWATER_SKILLDAMAGE:
		nType = 4;
		break;
	default:
		nType = 0;
		break;
	}

	if (_pNetwork->MyCharacterInfo.index == nCharIndex)
	{
		CEntity			*penPlEntity;
		penPlEntity = CEntity::GetPlayerEntity( 0 );
		
		_pNetwork->MyCharacterInfo.iHitEffectType = nType;
		_pNetwork->MyCharacterInfo.itemEffect.AddHolyWaterEffect(nType, &(penPlEntity->en_pmiModelInstance->m_tmSkaTagManager));
	}
	else
	{
		ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, nCharIndex);

		if (pObject != NULL)
		{
			CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);
			
			pTarget->cha_iHitType = nType;
			pTarget->cha_itemEffect.AddHolyWaterEffect(nType, &(pTarget->m_pEntity->en_pmiModelInstance->m_tmSkaTagManager));
		}
	}	
}

IMPLEMENT_MSG_UPDATE(updatePremiumCharInfo)
{
#ifdef PREMIUM_CHAR
	UpdateClient::premiumCharInfo* pRecv = reinterpret_cast<UpdateClient::premiumCharInfo*>(istr->GetBuffer());

	CPremiumChar* pChar = GAMEDATAMGR()->GetPremiumChar();
	
	if (pChar == NULL)
		return;

	pChar->updateInfo(pRecv->premiumType, pRecv->jumpCount, pRecv->expireTime);
#endif	//	PREMIUM_CHAR

}

IMPLEMENT_MSG_UPDATE(updatePremiumJumpCount)
{
#ifdef PREMIUM_CHAR
	UpdateClient::premiumCharJumpCount* pRecv = reinterpret_cast<UpdateClient::premiumCharJumpCount*>(istr->GetBuffer());

	CUIManager* pUImgr = CUIManager::getSingleton();
	CPremiumChar* pChar = GAMEDATAMGR()->GetPremiumChar();

	if (pChar == NULL)
		return;

	pChar->setCount(pRecv->jumpCount);

	pUImgr->GetPremiumChar()->updateAc_Jump();
	pUImgr->GetMessenger()->UpdateMemberMenu();
#endif	//	PREMIUM_CHAR
}

IMPLEMENT_MSG_UPDATE(updatePremiumCharEnd)
{
#ifdef PREMIUM_CHAR
	CPremiumChar* pChar = GAMEDATAMGR()->GetPremiumChar();

	if (pChar == NULL)
		return;

	pChar->Clear();
	UIMGR()->GetPremiumChar()->CloseUI();

	CTString strErrorMsg;
	strErrorMsg.PrintF(_S( 6326, "�����̾� ������ ���Ⱓ�� ���� �Ǿ����ϴ�."));
	_pNetwork->ClientSystemMessage(strErrorMsg, SYSMSG_ERROR);
#endif	//	PREMIUM_CHAR
}

IMPLEMENT_MSG_UPDATE(PremiumFlag)
{
#ifdef	PREMIUM_CHAR
	UpdateClient::changePremiumCharFlag* pRecv = reinterpret_cast<UpdateClient::changePremiumCharFlag*>(istr->GetBuffer());

	ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pRecv->charIndex);

	if (pObject == NULL)
		return;

	if (pRecv->flag == true)
		pObject->SetPremiumType(PREMIUM_CHAR_TYPE_FIRST);
	else
		pObject->SetPremiumType(PREMIUM_CHAR_TYPE_NONE);
#endif	// PREMIUM_CHAR
}

IMPLEMENT_MSG_UPDATE(updateAttrPc)
{
	// �Ӽ� ������Ʈ.
	UpdateClient::AttrItemUse* pRecv = reinterpret_cast<UpdateClient::AttrItemUse*>(istr->GetBuffer());

	CTString strAtt;
	int nMsgCode = 0;

	UBYTE ubAttr = GET_AT_VAR(pRecv->attr);

	switch(pRecv->state_type)
	{
	case 1:
		nMsgCode = 6351; // %s�� ���� �Ӽ����� �����Ǿ����ϴ�.
		break;
	case 2:
		nMsgCode = 6352; // %s�� ��� �Ӽ����� �����Ǿ����ϴ�.
		break;
	default:
		return;
	}

	strAtt = UtilHelp::getSingleton()->GetAttributeString(ubAttr);

	CTString strErrorMsg;
	strErrorMsg.PrintF(_S( nMsgCode, "%s �Ӽ� ���� "), strAtt);
	_pNetwork->ClientSystemMessage(strErrorMsg, SYSMSG_ERROR);
}

IMPLEMENT_MSG_UPDATE(updateAttrNpc)
{
	// �Ӽ� ������Ʈ.
	UpdateClient::AttrNpcStateInfo* pRecv = reinterpret_cast<UpdateClient::AttrNpcStateInfo*>(istr->GetBuffer());
	
	switch(pRecv->state_type)
	{
	case 1: // ���� �Ӽ� ����
	case 2: // ��� �Ӽ� ����
		break;
	default:
		return;
	}

	UBYTE ubAttr = GET_AT_VAR(pRecv->attr);
	UBYTE ubAttrLv = GET_AT_LV(pRecv->attr);

	if (ubAttr <= 0 || ubAttr >= ATTRIBUTE_ATT_MAX)
		ubAttrLv = 1;

	ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_MOB, pRecv->npc_index);

	if (pObject != NULL)
	{
		pObject->SetAttribute(pRecv->state_type, ubAttr, ubAttrLv);
	}

	if (INFO()->GetTargetEntity(eTARGET) != NULL && INFO()->GetTargetServerIdx(eTARGET) == pRecv->npc_index)
	{
		UIMGR()->GetTargetInfoUI()->UpdateAttrIcon();
	}
}

IMPLEMENT_MSG_UPDATE(updateNewsGmNoti)
{
	GAMEDATAMGR()->GetNews()->UpdateRevision(istr);
}

IMPLEMENT_MSG_UPDATE(updateNewsWebNoti)
{
	GAMEDATAMGR()->GetNews()->UpdateWebNoti(istr);
}

IMPLEMENT_MSG_UPDATE(updateNewsWebClose)
{
	GAMEDATAMGR()->GetNews()->UpdateWebClose(istr);
}

IMPLEMENT_MSG_UPDATE(updateNewsWebClear)
{
	GAMEDATAMGR()->GetNews()->UpdateWebClear(istr);
}

IMPLEMENT_MSG_UPDATE(updateItemCompose)
{
	GAMEDATAMGR()->GetItemCompose()->UpdateItemComposeMsg(istr);
}

IMPLEMENT_MSG_UPDATE(updateRelicGpsSysMsg)
{
	GAMEDATAMGR()->GetItemCompose()->UpdateGPSRelicMsg(istr);
}

IMPLEMENT_MSG_UPDATE(updateGuildRecall)
{
	CUIManager* pUIMgr = UIMGR();
	pUIMgr->CloseMessageBox( MSGCMD_GUILD_RECALL );

	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 865, "���" ), UMBS_OKCANCEL, UI_GUILD, MSGCMD_GUILD_RECALL );	
	strMessage.PrintF( _S( 6436, "����岲�� �� ������ �������� ��ȯ��û �Ͽ����ϴ�. ��ȯ�� ���Ͻðڽ��ϱ�?" ) );
	MsgBoxInfo.AddString( strMessage );

	pUIMgr->CreateMessageBox( MsgBoxInfo );		
}

IMPLEMENT_MSG_UPDATE(updateEPReset)
{
#ifdef ENABLE_IGNITION
	UpdateClient::EPInit* pRecv = reinterpret_cast<UpdateClient::EPInit*>(istr->GetBuffer());

	if (pRecv->isInit == true)
	{
		MSGBOX_OK(_S(1417, "Ȯ��"), 
			_S(7099, "�̱״ϼ� ���� �ð��� �ʰ��Ͽ� �̱״ϼ� ������ �ʱ�ȭ �Ǿ����ϴ�."));
	}
	else
	{
		MSGBOX_OK(_S(1417, "Ȯ��"), 
			_S(7100, "�̱״ϼ� ���� �ð��ȿ� ���� �Ͽ� �̱״ϼ� ������ ���� �˴ϴ�."));
	}
#endif
}

IMPLEMENT_MSG_UPDATE(charHPMP)
{
	UpdateClient::charStatusHPMP* pRecv = reinterpret_cast<UpdateClient::charStatusHPMP*>(istr->GetBuffer());

	if (pRecv->charIndex == _pNetwork->MyCharacterInfo.index)
	{
		_pNetwork->MyCharacterInfo.hp = pRecv->hp;
		_pNetwork->MyCharacterInfo.maxHP = pRecv->maxHp;
		_pNetwork->MyCharacterInfo.mp = pRecv->mp;
		_pNetwork->MyCharacterInfo.maxMP = pRecv->maxMp;
	}
}

IMPLEMENT_MSG_UPDATE(charHP)
{
	UpdateClient::charCurrHPMP* pRecv = reinterpret_cast<UpdateClient::charCurrHPMP*>(istr->GetBuffer());

	ObjInfo* pInfo = ObjInfo::getSingleton();

	if (pRecv->charIndex != _pNetwork->MyCharacterInfo.index)
	{
		ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pRecv->charIndex);

		if (pObject != NULL)
		{
			CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);
			pTarget->cha_hp = pRecv->hp;
			pTarget->cha_maxhp = pRecv->maxHp;

		}
	}
}
