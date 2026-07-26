#include "stdh.h"
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Network/CNetwork.h>
#include <Engine/Network/Server.h>
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Network/SessionState.h>
#include <Engine/Network/MessageDefine.h>
#include <Engine/GlobalDefinition.h>
#include <Engine/GameState.h>
#include <Engine/SlaveInfo.h>
#include <Engine/Interface/UIManager.h>
#include <Engine/Interface/UIAutoHelp.h>
#include <Engine/Interface/UISiegeWarfareDoc.h>
#include <Engine/Contents/function/PetTrainingUI.h>
#include <Engine/Interface/UIPetInfo.h>
#include <Engine/Contents/function/SummonUI.h>
#include <Engine/Interface/UIShop.h>
#include <Engine/Contents/Base/UINoticeNew.h>
#include <Engine/Templates/DynamicContainer.cpp>
#include <Engine/Contents/Base/UIPetStash.h>
#include <Engine/Interface/UICashShopEX.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Interface/UIRadar.h>
#include <Engine/Interface/UIGamble.h>
#include <Engine/Interface/UIMessenger.h>
#include <Engine/Interface/UIGuild.h>
#include <Engine/Contents/Base/UIPartyNew.h>
#include <Engine/Interface/UIMap.h>
#include <Engine/Interface/UIPartyAuto.h>
#include <Engine/Contents/Base/PartyAutoUIInviteList.h>
#include <Engine/Contents/Base/PartyAutoUIPartyList.h>
#include <Engine/Interface/UISiegeWarfareNew.h>
#include <Engine/Interface/UIPlayerInfo.h>
#include <Engine/Interface/UIGuildWarPortal.h>
#include <Engine/Interface/UIMonsterCombo.h>
#include <Engine/Contents/function/UIPortalNew.h>
#include <Engine/Interface/UIHelp.h>
#include <Engine/Interface/UIRanking.h>
#include <Engine/Interface/UIOption.h>
#include <Engine/Contents/function/WildPetInfoUI.h>
#include <Engine/Interface/UIReformSystem.h>
#include <Engine/Interface/UINickName.h>
#include <Engine/Interface/UINpcScroll.h>
#include <Engine/Contents/function/PetFreeUI.h>
#include <Engine/Interface/UISocketSystem.h>
#include <Engine/Contents/function/SocketCreateUI.h>
#include <Engine/Contents/function/SocketCombineUI.h>
#include <Engine/Contents/function/JewelComposUI.h>
#include <Engine/Contents/function/PetItemMixUI.h>
#include <Engine/Contents/function/AffinityUI.h>
#include <Engine/Contents/function/AffinityInfoUI.h>
#include <Engine/Interface/UIMonsterMercenary.h>
#include <Engine/Interface/UIInitJob.h>
#include <Engine/Interface/UIQuickSlot.h>
#include <Engine/Contents/Base/UIRankingSystem.h>
#include <Engine/Contents/function/DonationTierManager.h>
#include <Engine/Interface/UIMixNew.h>
#include <Engine/LoginJobInfo.h>
#include <Engine/Contents/Login/BackImageManager.h>
#include <Engine/Object/ActorMgr.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/Base/Notice.h>
#include <Engine/Contents/Base/Quest.h>
#include <Engine/Info/MyInfo.h>
#include <Engine/Contents/Base/Party.h>
#include <Engine/Contents/function/SimplePlayerInfoUI.h>
#include <Engine/Info/ServerInfo.h>
#include <Engine/Contents/Base/ChattingUI.h>
#include <Common/Packet/ptype_old_do_item.h>
#include <Engine/Contents/Login/LoginNew.h>
#include <Engine/Contents/function/PetTargetUI.h>
#include <Engine/Contents/function/CubeRankingUI.h>
#include <Engine/Contents/function/RoyalrumbleUI.h>
#include <Engine/Contents/function/InventoryOptions.h>
#include <Engine/Contents/Base/UICalendar.h>

#ifdef BATTLE_PASS_SYSTEM
#include <Common/Packet/ptype_old_do_battle_pass.h>
#include <Engine/Interface/UIBattlePass.h>
#endif
#ifdef PRESTIGE_SYSTEM
#include <Common/Packet/ptype_old_do_prestige.h>
#include <Engine/Interface/UIPrestige.h>
#endif

// socket system. [5/11/2010 rumist]
//#include <Engine/Interface/UISocketSystem.h>
#define MODEL_TREASURE	("Data\\Item\\Common\\ITEM_treasure02.smc")
// #include <map>
// #include <algorithm>
//#define XTRAP_LOG_ENABLE
// ----------------------------------------------------------------------------
// Name : CheckDratanSiegewarfareError()
// Desc : 
// ----------------------------------------------------------------------------
void CheckDratanSiegewarfareError(UBYTE errcode)
{
	CTString tStr;
	switch(errcode)
	{
		case MSG_EX_CASTLE_ERROR_NOT_JOIN:    // ���� �������� �ƴ�
				tStr = _S( 3739,"���� �������� �ƴմϴ�.");
				break;
		case MSG_EX_CASTLE_ERROR_NOT_WAR:    // ������ ���� �ƴ�
				tStr = _S( 3740,"�������� �ƴմϴ�.");
				break;
		case MSG_EX_CASTLE_ERROR_POS_FAIL:    // ��ġ �̻�
				tStr = _S( 3741,"���� ������ �ƴմϴ�.");
				break;
		case MSG_EX_CASTLE_ERROR_MEM_5_FAIL:    // ���� �ο� �ڸ� ����
				tStr = _S( 3742,"���� �ο��� �ʰ��Ǿ����ϴ�.");
				break;
		case MSG_EX_CASTLE_ERROR_NOT_OWNER:    // ���� ��� �ƴ�
				tStr = _S( 3743,"���� ��尡 �ƴմϴ�.");
				break;
		case MSG_EX_CASTLE_ERROR_NOT_RESPOND:   // ���� ���� �ƴ�
				tStr = _S( 3744,"�������� �ƴմϴ�.");
				break;
		case MSG_EX_CASTLE_ERROR_NOT_RESPOND_TIME:  // ���� �ð� ����
				tStr = _S( 3745,"���� �ð��� �����մϴ�.");
				break;
		case MSG_EX_CASTLE_ERROR_NO_MONEY:    // �� ����
				tStr = _S(306,"������ �����մϴ�.");
				break;
		case MSG_EX_CASTLE_ERROR_NOT_ATTACK:    // ���� ��� �ƴ�
				tStr = _S( 3746,"���� ��尡 �ƴմϴ�.");
				break;
		case MSG_EX_CASTLE_ERROR_NO_DATA:    // ������ �̻�
				tStr.PrintF("Error %d",errcode);
				break;
		case MSG_EX_CASTLE_ERROR_NO_DIFFER:    // ���� �����Ϳ� ����				
				tStr = _S( 3747,"�̹� ��ȭ�� �ܰ��Դϴ�.");				
				break;
		case MSG_EX_CASTLE_ERROR_NOT_BUY:    // �������� �ʾ���				
				tStr.PrintF("Error %d",errcode);
				break;
		case MSG_EX_CASTLE_ERROR_NO_NPC:     // ���� Ÿ��
				tStr.PrintF("Error %d",errcode);
				break;
		case MSG_EX_CASTLE_ERROR_DEAD_NPC:    // ���� Ÿ�� 
				tStr.PrintF("Error %d",errcode);
				break;
		case MSG_EX_CASTLE_ERROR_HAVE_NO_GUILD:   // ��� ���� �ƴ�
				tStr = _S(985,"�ش� ������ ã�� �� �����ϴ�.");
				break;				
		case MSG_EX_CASTLE_ERROR_USE_NPC:    // ����� ��Ȱ ����
				tStr = _S(3749,"������� ��Ȱ�����Դϴ�.");
				break;
		case MSG_EX_CASTLE_ERROR_USE_NPC_OTHER:   // �̹� �ٸ� ��Ȱ���� �����
				tStr = _S(3750,"�ٸ� ��Ȱ������ ������Դϴ�.");
				break;
		case MSG_EX_CASTLE_ERROR_NO_NPC2:     // ���� ��Ȱ ����
				tStr.PrintF("Error %d",errcode);
				break;
		case MSG_EX_CASTLE_ERROR_DEAD_NPC2:    // ���� ��Ȱ����
				tStr.PrintF("Error %d",errcode);
				break;				
		case MSG_EX_CASTLE_ERROR_SAME_DATA:	   // ���� ������ - Ÿ�԰� �ܰ谡 �ȸ�����...
				tStr.PrintF("Error %d",errcode);
				break;
		case MSG_EX_CASTLE_ERROR_NOT_BUY_NPC:  // ���̻� NPC�� ���� �Ҽ� �����ϴ�,
				tStr = _S(3812, "���̻� ������ �� �����ϴ�.");
				break;
		case MSG_EX_CASTLE_ERROR_PERMISSION_DENIED: // ������ �����ϴ�.
				tStr = _S( 973, "������ �����ϴ�.");
				break;
	}
	
	if(tStr.Length()>0 )
		CUIManager::getSingleton()->GetChattingUI()->AddSysMessage( tStr , SYSMSG_ERROR );	
	
}

// ----------------------------------------------------------------------------
// Name : CheckCashMoonStoneMessage()
// Desc : 
// ----------------------------------------------------------------------------
BOOL CheckCashMoonStone(UBYTE errcode)
{
	if( errcode == MSG_EX_CASHITEM_MOONSTONE_ERROR_SUCCESS )	// ����
		return TRUE;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch(errcode)
	{
		case MSG_EX_CASHITEM_MOONSTONE_ERROR_NOITEM:		
			pUIManager->GetChattingUI()->AddSysMessage( _S(2908, "��ȯ�� �������� �����ϴ�." ), SYSMSG_ERROR );	
			break;
		case MSG_EX_CASHITEM_MOONSTONE_ERROR_INVEN:		
			pUIManager->GetChattingUI()->AddSysMessage( _S(265, "�κ��丮�� �����մϴ�." ), SYSMSG_ERROR );	
			break;
		case MSG_EX_CASHITEM_MOONSTONE_ERROR_CANTUSE_CASHMOON:			
			pUIManager->GetChattingUI()->AddSysMessage( _S(2907, "�̿� ������ �������� �ƴմϴ�." ), SYSMSG_ERROR );	
			break;
	}

	return FALSE;

}

// ----------------------------------------------------------------------------
// Name : CheckCashItemMessage()
// Desc : 
// ----------------------------------------------------------------------------
BOOL CheckCashItemMessage(UBYTE errcode)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	switch(errcode)
	{
		case MSG_EX_CASHITEM_ERROR_SUCCESS:				// ����
			pUIManager->GetChattingUI()->AddSysMessage( _S(2408,  "��û�� �۾��� �����Ͽ����ϴ�." ), SYSMSG_ERROR );	
			return TRUE;
			
		case MSG_EX_CASHITEM_ERROR_LACKCASH:			// ����ĳ�� ����
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(191, "Ȯ��"), _S(2409, "���� ĳ���� ���� �մϴ�."), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_NOTUSER:				// �ش����� ����
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(191, "Ȯ��"), _S(2410, "�ش� ������ �������� �ʽ��ϴ�."), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_NOTITEM:				// �������� �ʴ� ��ǰ�Դϴ�
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(191, "Ȯ��"), _S(2411, "�������� �ʴ� ��ǰ�Դϴ�."), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_DB:					// DB����
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(191, "Ȯ��"), _S(1843, "������ ������ �� �����ϴ�.(B)"), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_PACKET:				// ��Ŷ ����
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(191, "Ȯ��"), _S(854, "��Ŷ ������ �߻��Ͽ����ϴ�."), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_ETC:					// ��Ÿ ����
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(191, "Ȯ��"), _S(1094, "�� �� ���� ������ �߻��Ͽ����ϴ�."), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_OVERITEM:				// ���� ��ǰ ���� �ʰ�(10��)
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(191, "Ȯ��"), _S(2413, "���� ��ǰ�� 10���� �ʰ��Ͽ����ϴ�."), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_NOSPACE:				// ���Ź�ǰ �������� ���� ����
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(191, "Ȯ��"), _S(2414, "���Ź�ǰ �������� ������ �����մϴ�."), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_LACKINVEN:			// �ɸ��� �κ� ����
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(191, "Ȯ��"), _S(265, "ĳ���� �κ��丮 ������ �����մϴ�."), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_CONN:					// Ŀ���� ���� ����
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(191, "Ȯ��"), _S(2415, "Ŀ���� ���� �����Դϴ�."), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_BILL:					// ���� ���� ����
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(191, "Ȯ��"), _S(2416, "���� ���� �����Դϴ�."), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_NOTHAVECT :
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(191, "Ȯ��"), _S(2769, "ǰ���� ��ǰ �Դϴ�."), UMBS_OK);
			break;


		// ���� ���� :Su-won	|---------->
		case MSG_EX_CASHITEM_ERROR_GIFT_SUCCESS:
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(3102, "���� ������"), _S(3106, "���� �����Ⱑ �Ϸ�Ǿ����ϴ�."), UMBS_OK);
			return TRUE;
		case MSG_EX_CASHITEM_ERROR_GIFT_WRONGCHAR:
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(3107, "���� ������ ����"), _S(3108, "�ش� ĳ���Ϳ��Է� ������ ���� �� �����ϴ�. ĳ���� ���� ��Ȯ�ϰ� �Է��� �ּ���."), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_CANT_GIFT:
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(3107, "���� ������ ����"), _S(5366, "�̺�Ʈ ��ǰ�� ������ �Ұ����մϴ�."), UMBS_OK);
			break;
		case MSG_EX_CASHITEM_ERROR_GIFTRECV_SUCCESS:
			pUIManager->GetCashShopEX()->Message(MSGCMD_CASH_EX_ERROR, _S(3109, "���� �ޱ�"), _S(3110, "���� ���� ��ǰ���� ĳ���� ������ �κ��丮�� �Ű������ϴ�."), UMBS_OK);
			pUIManager->GetCashShopEX()->SetLoadDataState(FALSE);
			return TRUE;
		// ���� ���� :Su-won	<----------|
	}

	pUIManager->GetCashShopEX()->SetLoadDataState(FALSE);
	return FALSE;

}
void CheckSocketSystemError(UBYTE errcode);

#ifdef XTRAP_SECURE_CKBANG_2010_07_20
    #include <Engine/XTrapInterface/XTrapInterface.h>
#endif

void CheckTimerEvent()
{
	if (IS_EVENT_ON(A_EVENT_SONGKRAN))
	{
		_pNetwork->ga_World.loadTradeItem();
	}

	if (IS_EVENT_ON(A_EVENT_HOLLOWEEN))
	{
		g_fGWTime = 30*3600; // �ҷ�������2007�̺�Ʈ������ ��� ���� ���� �Ѵ�.
		g_fGWTimeMul = 0.0f;
	}
	else
	{
		g_fGWTime = CUIManager::getSingleton()->GetRadar()->GetHour() * 3600;
		g_fGWTimeMul = 1.0f;
	}

	FOREACHINDYNAMICCONTAINER( _pNetwork->ga_World.wo_cenEntities, CEntity, iten) 
	{
		if( iten->GetName() == CTString("Color controller") || iten->GetName() == CTString("SunMoon") )
		{
			iten->Initialize();
		}
	}

	if (!_pUIBuff->IsBuffBySkill(564))
	{
		if (CUIManager::getSingleton()->GetInventory()->GetWearingBtn(WEAR_HELMET)->IsEmpty() == false)
		{
			int iItemIndex = CUIManager::getSingleton()->GetInventory()->GetWearingBtn(WEAR_HELMET)->getIndex();
			if ((( ( iItemIndex >= 4927 && iItemIndex <= 4932 ) || iItemIndex == 6228) && IS_EVENT_ON(A_EVENT_HOLLOWEEN))// ȣ��Ż �Ⱓ���� �߰��Ǿ���.
				|| (iItemIndex >= 7253 && iItemIndex <= 7259)) // [ldy1978220 2011/5/31] ���̰� 10�ֳ� �̺�Ʈ ���� �߰� ������
			{ // ȣ��Ż�� hidden �Ӽ��� npc�� �� �� �ִ�.
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetFlagOn(ENF_SHOWHIDDEN);
			}
			else
			{
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetFlagOff(ENF_SHOWHIDDEN);
			}
		}
	}


	LoginNew* pInfo = GAMEDATAMGR()->GetLoginData();

	if (pInfo != NULL)
	{
		if (IS_EVENT_ON(A_EVENT_HOLLOWEEN))
			pInfo->SetLogoType(eLOGO_HOLLOWEEN);
		else if (IS_EVENT_ON(TEVENT_XMAS_2007))
			pInfo->SetLogoType(eLOGO_XMAS);
		else
			pInfo->SetLogoType(eLOGO_NORMAL);
	}
}

// ----------------------------------------------------------------------------
// Name : ReceiveArtifactMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveArtifactMessage( CNetworkMessage *istr )
{
	LONG	lType;
	(*istr) >> lType;

	CUIManager* pUIManager = CUIManager::getSingleton();

    if (!pUIManager)
        return;

    switch (lType)
    {
    case MSG_ARTIFACT_DEBUG_ON:
        pUIManager->GetChattingUI()->AddSysMessage(CTString("Switched on."), SYSMSG_NOTIFY);
        break;

    case MSG_ARTIFACT_DEBUG_OFF:
        pUIManager->GetChattingUI()->AddSysMessage(CTString("Switched off."), SYSMSG_NOTIFY);
        break;

    case MSG_ARTIFACT_ARTIFACT_NOTICE_3MIN:
        pUIManager->GetChattingUI()->AddSysMessage(CTString("You have 3 minutes left to leave the peace zone before your artifact expires."), SYSMSG_NOTIFY);
        break;

    case MSG_ARTIFACT_ARTIFACT_NOTICE_1MIN:
        pUIManager->GetChattingUI()->AddSysMessage(CTString("You have 1 minute left to leave the peace zone before your artifact expires."), SYSMSG_NOTIFY);
        break;

    case MSG_ARTIFACT_ARTIFACT_NOTICE_TIMEOUT:
        pUIManager->GetChattingUI()->AddSysMessage(CTString("Your artifact expired after not leaving a peace zone for 10 minutes."), SYSMSG_NOTIFY);
        break;

    case MSG_ARTIFACT_ARTIFACT_NOTICE_REMAINING:
        {
            int nRemaining;
            (*istr) >> nRemaining;
            CTString strPrint; strPrint.PrintF("Remaining Artifact Time: %d seconds.", nRemaining);
            pUIManager->GetChattingUI()->AddSysMessage(strPrint, SYSMSG_NORMAL);
        } break;
    }
}

// ----------------------------------------------------------------------------
// Name : ReceiveExtendMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveExtendMessage( CNetworkMessage *istr )
{
	int		i;
	LONG	lType;
	UBYTE	errcode;
	UBYTE	exType;
	SLONG	nServerTime;
	(*istr) >> lType;
	CTString		strTitle,strMessage,newName;
	ULONG			nIndex;
	UBYTE			nJob;
	BYTE			bIsGuildName;
	CUIMsgBox_Info	MsgBoxInfo;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch(lType)
	{
	case MSG_EX_PET_STATUS:
		ReceivePetStatusMessage(istr);
		break;
	case MSG_EX_PET_MOUNT:
		ReceivePetMountMessage(istr);
		break;
	case MSG_EX_PET_LEARN:			// �� ����			: skillindex(n) level(c:server) errorcode(n:server)
		ReceivePetLearnMessage(istr);
		break;
	case MSG_EX_PET_SKILLLIST:		// �� ��ų ����Ʈ	: index(n) count(n) [skillindex(n) skilllevel(c)] ...
		ReceivePetSkillListMessage(istr);
		break;
	case MSG_EX_PET_RESET_SKILL:	// �� ��ų �ʱ�ȭ
		ReceivePetResetSkillMessage(istr);
		break;
	case MSG_EX_PET_SELL_INFO:		// �� ��ȯ/�Ǹ� ����: ownerindex(n) petindex(n) petTypeGrade(c) level(n) exp(ll) needexp(ll) hp(n) maxhp(n) ability(n) hungry(n) maxhugry(n) sympathy(n) maxsympathy(n)
		ReceivePetSellInfoMessage(istr);
		break;
	case MSG_EX_PET_CHANGE_MOUNT:	// �� Ÿ�� ����		: errorcode(n:server)
		ReceivePetChangeMountMessage(istr);
		break;	

	case MSG_EX_SET_AGGRESSIVE_MOB:
		ReceiveSetAggressiveMobMessage(istr);
		break;
	
	case MSG_EX_PET_COMMAND:		// �� �米����		: pet_index(n) command_skill_index(n) targettype(c) targetindex(n)
		{
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->Read_net_Pet(MSG_EX_PET_COMMAND, &(*istr));			
		}
		break;
	case MSG_EX_PET_LEVELUP: // �� ������ petindex(n) typegrade(c) level(n)
		ReceivePetLevelUpMessage(istr);
		break;
	case MSG_EX_PET_MIX_ITEM:		// �� �̾��� ����	: 
		ReceviePetItemMixMessage(istr);
		break;
	case MSG_EX_PET_CHANGE_ITEM:	// �� ������ ��ȯ  
		ReceviePetItemChangeMessage(istr);
		break;
	case MSG_EX_PET_REBIRTH:
		ReceviePetRebirthMessage(istr); // �� ���� ����
		break;
	
	case MSG_EX_PARTY_RECALL:
		ReceivePartyRecall(istr);	// CashItem 060306
		break;

	case MSG_EX_INVENTORY_OPTION:
		{
			UCHAR optionType;
			(*istr) >> optionType;
			switch (optionType)
			{
			case INVENTORY_OPTION_INVENTORY_OPTION:
				{
					INDEX isActive;
					(*istr) >> isActive;
					pUIManager->GetInventoryOptions()->SetInvisibleHelmet((BOOL)isActive);
					pUIManager->GetInventoryOptions()->OnInvisibleHelmetChange();
				}break;
			}
		}break;
	case MSG_EX_GET_DONATION_TIER_INFO:
		DonationTierManager::getSingleton()->RecvInfo(istr);
		break;
	case MSG_EX_BATTLE_WARFARE_REP:
		ReceiveBattleWarfareMsg(istr);
		break;
	case MSG_EX_NAMECHANGE :
		(*istr) >> errcode;
		switch(errcode)
		{
			case MSG_EX_NAMECHANGE_ERROR_SUCCESS:
				(*istr) >> newName;
				(*istr) >> bIsGuildName;
				if(bIsGuildName)
				{
					_pNetwork->MyCharacterInfo.strGuildName=newName;
					if(pUIManager->DoesMessageBoxExist(MSG_EX_NAMECHANGE_ERROR_SUCCESS)) return;
					strTitle	=	_S(191,"Ȯ��");
					strMessage	=_S( 2131, 	"����忡 ���� ��� �̸��� ����Ǿ����ϴ�" ); 
					MsgBoxInfo.SetMsgBoxInfo(strTitle,UMBS_OK,UI_NONE,MSGCMD_NULL);
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
					
				}
				else 
				{
					_pNetwork->MyCharacterInfo.name=newName;
					if(pUIManager->DoesMessageBoxExist(MSG_EX_NAMECHANGE_ERROR_SUCCESS)) return;
					strTitle	=	_S(191,"Ȯ��");
					strMessage	=_S( 2132, 	"�̸��� ���������� ����Ǿ����ϴ�" ); 
					MsgBoxInfo.SetMsgBoxInfo(strTitle,UMBS_OK,UI_NONE,MSGCMD_NULL);
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
					
					//wooss 051004 ������ �޽����� �̸��� ����
					pUIManager->GetMessenger()->SetMyInfo(-1,newName);
					
				}
				break;
				
			case MSG_EX_NAMECHANGE_ERROR_DUPLICATE:
				if(pUIManager->DoesMessageBoxExist(MSG_EX_NAMECHANGE_ERROR_DUPLICATE)) return;
				strTitle	=	_S(191,"Ȯ��");
				strMessage	=_S(12,"�ߺ��� �̸� �Դϴ�."); 
				MsgBoxInfo.SetMsgBoxInfo(strTitle,UMBS_OK,UI_NONE,MSGCMD_NULL);
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
				break;
				
			case MSG_EX_NAMECHANGE_ERROR_HELPER:
				if(pUIManager->DoesMessageBoxExist(MSG_EX_NAMECHANGE_ERROR_HELPER)) return;
				strTitle	=	_S(191,"Ȯ��");
				strMessage	=	_S( 2133, "���ۼ��� ���� �Դϴ�" ); 
				MsgBoxInfo.SetMsgBoxInfo(strTitle,UMBS_OK,UI_NONE,MSGCMD_NULL);
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
				break;
				
			case MSG_EX_NAMECHANGE_ERROR_INVALID:
				if(pUIManager->DoesMessageBoxExist(MSG_EX_NAMECHANGE_ERROR_INVALID)) return;
				strTitle	=	_S(191,"Ȯ��");
				strMessage	=_S( 2134, 	"�ùٸ� ������ �̸��� �ƴմϴ�" ); 
				MsgBoxInfo.SetMsgBoxInfo(strTitle,UMBS_OK,UI_NONE,MSGCMD_NULL);
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
				break;
				
			case MSG_EX_NAMECHANGE_ERROR_NOTGUILDBOSS:
				if(pUIManager->DoesMessageBoxExist(MSG_EX_NAMECHANGE_ERROR_NOTGUILDBOSS)) return;
				strTitle	=	_S(191,"Ȯ��");
				strMessage	=_S( 2136, 	"����̸��� ����常�� ������ �� �ֽ��ϴ�" ); 
				MsgBoxInfo.SetMsgBoxInfo(strTitle,UMBS_OK,UI_NONE,MSGCMD_NULL);
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
				break;	

			case MSG_EX_NAMECHANGE_ERROR_PARTY:
				if(pUIManager->DoesMessageBoxExist(MSG_EX_NAMECHANGE_ERROR_PARTY)) return;
				strTitle	=	_S(191,"Ȯ��");
				strMessage	=_S(4718, "��Ƽ�߿��� �̸��� ������ �� �����ϴ�." ); 
				MsgBoxInfo.SetMsgBoxInfo(strTitle,UMBS_OK,UI_NONE,MSGCMD_NULL);
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
				break;
			}
			break;

		case MSG_EX_CASHITEM:			// ������ ����		: subtype(uc) ...
			{
				ULONG tv_cash,nCount;
				(*istr) >> exType;
				
				switch(exType)
				{
				case MSG_EX_CASHITEM_TYPE_LIST_REP:
					{ // max type count�� �������� ����ϴ� index�� ��� �ʴ� index�� �к��Ѵ�
						pUIManager->GetCashShopEX()->SetCashType(istr);
					}
					break;
				case MSG_EX_CASHITEM_LIST_REP:
					{
						pUIManager->GetCashShopEX()->SetGoodsList(istr);
					}
					break;
				case MSG_EX_CASHITEM_RECOMMAND_REP:
					{
						pUIManager->GetCashShopEX()->SetRecommandList(istr);
					}
					break;
				case MSG_EX_CASHITEM_WISHLIST_REP:
					{
						pUIManager->GetCashShopEX()->SetWishList(istr);
					}
					break;

					case MSG_EX_CASHITEM_BALANCE_REP :		// ĳ��				: errorCode(uc) cashBalance(n)
						{
							(*istr) >> errcode;
							if(CheckCashItemMessage(errcode))
							{
								(*istr) >> 	tv_cash;
								pUIManager->GetCashShopEX()->SetMyCash(static_cast<SQUAD>(tv_cash));
							}
						}
						break;			
					case MSG_EX_CASHITEM_PURCHASE_REP :		// ����				: errorCode(uc) cashBalance(n)
					case MSG_EX_CASHITEM_PURCHASE_WITH_COUPON_REP : // ���� ���� ���� : errorCode(uc) cashBalance(n)
						{							
							(*istr) >> errcode;
							if(CheckCashItemMessage(errcode))
							{
								(*istr) >> 	tv_cash;
								pUIManager->GetCashShopEX()->SetMyCash(static_cast<SQUAD>(tv_cash));
								pUIManager->GetCashShopEX()->CompletePurchase();
							}
						}
						break;
					case MSG_EX_CASHITEM_BRING_REP:			// ����				: errorCode(uc) 
						{
							(*istr) >> errcode;
							if(CheckCashItemMessage(errcode)){
								pUIManager->GetCashShopEX()->CompleteBringItems();
							}
						}
						break;	
					case MSG_EX_CASHITEM_PURCHASELIST_REP:   // ����				: count(n) idx(n) ctid(n)
						{
							(*istr) >> errcode;
							if(CheckCashItemMessage(errcode))
							{
								pUIManager->GetCashShopEX()->SetPurchaseItemList(istr);
							}
						}
						break;
					case MSG_EX_CASHITEM_PURCHASEHISTORY_REP:// ����				: errorcode(uc) count(n) ctid(n)
						{
							(*istr) >> errcode;
							if(CheckCashItemMessage(errcode)){
								(*istr >> nCount);
								if( nCount > 0){
// 									pUIManager->GetCashShop()->m_abtnHistoryItems.New(nCount);
// 									pUIManager->GetCashShop()->m_sbHistory.SetScrollPos( 0 );
// 									pUIManager->GetCashShop()->m_sbHistory.SetScrollRange(nCount);
// 									pUIManager->GetCashShop()->m_sbHistory.SetCurItemCount(nCount);
// 									for( int i=0; i < nCount ;i++){
// 										CUIButtonEx tv_btn;
// 										ULONG nItemCnt;
// 										(*istr) >> nItemCnt;
// 										(*istr) >> nCtid;
// 										pUIManager->GetCashShop()->m_abtnHistoryItems[i].Create(NULL,-1,-1,BTN_SIZE,BTN_SIZE,UI_CASH_SHOP);
// 										if(pUIManager->GetCashShop()->SetCashIndexToBtn(nCtid,-1,tv_btn)){
// 											pUIManager->GetCashShop()->m_abtnHistoryItems[i] = tv_btn;
// 											pUIManager->GetCashShop()->m_abtnHistoryItems[i].Copy(tv_btn);
// 											pUIManager->GetCashShop()->m_abtnHistoryItems[i].SetItemCount(nItemCnt);
// 										}
// 									}
								}
							}						
						}
						break;
					case MSG_EX_CASHITEM_MOONSTONE_START :
						{
							(*istr) >> errcode;
							if(CheckCashMoonStone(errcode)){
								UBYTE grade;
								(*istr) >> grade;
								grade =5-grade;
								pUIManager->GetGamble()->SetSelectedMarker( grade, grade );
								pUIManager->GetGamble()->Start();
							}						
						}
						break;

					// ���� ���� :Su-won	|--------------------------------------------------->
					case MSG_EX_CASHITEM_GIFT_REP:					//����	: errcode(uc) 
						{
							(*istr) >> errcode;
							if(CheckCashItemMessage(errcode))
							{
								pUIManager->GetCashShopEX()->CompleteBringItems();
							}
						}
						break;
					case MSG_EX_CASHITEM_WISHLIST_SAVE_REP: // �Ҹ����� ������ ��� ���
						{
							//(*istr) >> errcode;
							pUIManager->GetCashShopEX()->RevWishList(istr, TRUE);
						}
						break;
					case MSG_EX_CASHITEM_WISHLIST_DEL_REP:
						{
							pUIManager->GetCashShopEX()->RevWishList(istr, FALSE);
						}
						break;
					case MSG_EX_CASHITEM_GIFT_SENDHISTORY_REP:		// ����	: errorcode(uc) count(n) ctid(n) recvcharName(str)
						{
							(*istr) >> errcode;
							if(CheckCashItemMessage(errcode))
							{
								(*istr >> nCount);
								if( nCount > 0)
								{
// 									pUIManager->GetCashShop()->m_abtnSendHistoryItems.New(nCount);
// 									pUIManager->GetCashShop()->m_sbGift.SetScrollPos( 0 );
// 									pUIManager->GetCashShop()->m_sbGift.SetScrollRange(nCount);
// 									pUIManager->GetCashShop()->m_sbGift.SetCurItemCount(nCount);
// 
// 									pUIManager->GetCashShop()->m_astrSendChar.New(nCount);
// 									for( int i=0; i < nCount ;i++)
// 									{
// 										CUIButtonEx tv_btn;
// 										//ULONG nItemCnt;
// 										(*istr) >> nCtid;
// 										(*istr) >> newName;
// 										pUIManager->GetCashShop()->m_abtnSendHistoryItems[i].Create(NULL,-1,-1,BTN_SIZE,BTN_SIZE,UI_CASH_SHOP);
// 										if(pUIManager->GetCashShop()->SetCashIndexToBtn(nCtid,-1,tv_btn))
// 										{
// 											pUIManager->GetCashShop()->m_abtnSendHistoryItems[i] = tv_btn;
// 											pUIManager->GetCashShop()->m_abtnSendHistoryItems[i].Copy(tv_btn);
// 											//pUIManager->GetCashShop()->m_abtnSendHistoryItems[i].SetItemCount(nItemCnt);
// 											pUIManager->GetCashShop()->m_astrSendChar[i] =newName;
// 										}
// 									}
								}
							}
						}
						break;
					case MSG_EX_CASHITEM_GIFT_RECVHISTORY_REP:// ����				: errorcode(uc) count(n) ctid(n) recvcharName(str)
						{
							(*istr) >> errcode;
							if(CheckCashItemMessage(errcode))
							{
								(*istr >> nCount);
								if( nCount > 0)
								{
// 									pUIManager->GetCashShop()->m_abtnRecvHistoryItems.New(nCount);
// 									pUIManager->GetCashShop()->m_sbGift.SetScrollPos( 0 );
// 									pUIManager->GetCashShop()->m_sbGift.SetScrollRange(nCount);
// 									pUIManager->GetCashShop()->m_sbGift.SetCurItemCount(nCount);
// 
// 									pUIManager->GetCashShop()->m_astrReceiveChar.New(nCount);
// 									for( int i=0; i < nCount ;i++)
// 									{
// 										CUIButtonEx tv_btn;
// 										//ULONG nItemCnt;
// 										//(*istr) >> nItemCnt;
// 										(*istr) >> nCtid;
// 										(*istr) >> newName;
// 										pUIManager->GetCashShop()->m_abtnRecvHistoryItems[i].Create(NULL,-1,-1,BTN_SIZE,BTN_SIZE,UI_CASH_SHOP);
// 										if(pUIManager->GetCashShop()->SetCashIndexToBtn(nCtid,-1,tv_btn))
// 										{
// 											pUIManager->GetCashShop()->m_abtnRecvHistoryItems[i] = tv_btn;
// 											pUIManager->GetCashShop()->m_abtnRecvHistoryItems[i].Copy(tv_btn);
// 											//pUIManager->GetCashShop()->m_abtnReceiveHistoryItems[i].SetItemCount(nItemCnt);
// 											pUIManager->GetCashShop()->m_astrReceiveChar[i] =newName;
// 										}										
// 									}
								}
							}
						}
						break;
					case MSG_EX_CASHITEM_GIFT_RECVLIST_REP:// ����
						{
							pUIManager->GetCashShopEX()->RevGiftList(istr);
						}
						break;
					case MSG_EX_CASHITEM_GIFT_RECV_REP:		// ����				: errCode(uc)
						{
							(*istr) >> errcode;
							if (CheckCashItemMessage(errcode))
							{
								pUIManager->GetCashShopEX()->RevResultGetGift();
							}
						}
						break;
					case MSG_EX_CASHITEM_GIFT_NOTICE: // ĳ�� ������ ���� ���� �޼���
						{
							BYTE bGift;

							(*istr) >> bGift;
							// MSG_EX_CASHITEM_GIFT_NOTICE�� Party �� ������ ���� �������� �׻� �ް� �Ǵ� �޼������ ��������
							// �� �̵� �� ��Ƽ �� �����밡 ��ü �Ǿ��� �� ������ ���� ������ ���� ������ �Ǵ��Ͽ� ��ü ó��
							Party* pParty = GAMEDATAMGR()->GetPartyInfo();

							if (pParty == NULL)
								return;

							if( pParty->GetIsPartyPlay() == FALSE)
							{
								if( pUIManager->IsCSFlagOn(CSF_EXPEDITION) )
								{
									pParty->ExpeditionEnd();
									pUIManager->GetChattingUI()->AddSysMessage( _S( 4665, "�����밡 ��ü�Ǿ����ϴ�." ) );
								}
								
								if( pUIManager->IsCSFlagOn(CSF_PARTY) )
									pParty->PartyEnd();
							}
							//////////////////////////////////////////////////////////////////////////
							pUIManager->GetQuickSlot()->SetGiftRecv(bGift);
						}
						break;
					// ���� ���� :Su-won	<---------------------------------------------------|
					case MSG_EX_CASHITEM_CUPON_REP: // ���� ���� ����Ʈ ����
						{
							(*istr) >> errcode;

							if (CheckCashItemMessage(errcode))
							{ // pUIManager->GetCashShop()->m_pConfirmInfo NULL üũ ���� 
								// ���� ����Ʈ�� ����
								SLONG slCuponCout;
								(*istr) >> slCuponCout;

								//pUIManager->GetCashShop()->m_pConfirmInfo->ClearCuponData(); // ������ ����Ʈ Ŭ����

								if (slCuponCout > 0) // ���� �����
								{
									int i;

									for (i=0; i<slCuponCout; i++)
									{
										CTString strCuponName;
										SLONG slCuponID;
										SLONG slDCPoint;
										SLONG slLimitPoint = 0;

										(*istr) >> strCuponName; // ���� �̸�
										(*istr) >> slCuponID; // ���� ���̵�
										(*istr) >> slDCPoint; // ���� �ݾ�
										(*istr) >> slLimitPoint; // ���� ���� �ݾ�

										//pUIManager->GetCashShop()->m_pConfirmInfo->AddCuponData(strCuponName, slCuponID, slDCPoint, slLimitPoint);
									}
								}

								//pUIManager->GetCashShop()->m_pConfirmInfo->SetEnable(TRUE);
								//pUIManager->GetCashShop()->m_pConfirmInfo->SetVisible(TRUE);
							}
						}
					case MSG_EX_CASHITEM_SHOP_LOCK:
						{
							pUIManager->GetCashShopEX()->ForcedExit();
						}
						break;
					case MSG_EX_CASHITEM_SHOP_UNLOCK:
						{
							pUIManager->GetCashShopEX()->SetCashShopLock(FALSE);
						}
						break;
				}
			}
			break;

		// wooss 051004 ������ �޽��� ���
		case MSG_EX_FRIENDNAMECHANGE :
			(*istr) >> nIndex;
			(*istr) >> newName;
			(*istr) >> nJob;
			pUIManager->GetMessenger()->DeleteMember(nIndex);
			pUIManager->GetMessenger()->AddFriendList(nIndex, 0, newName,(eJob)nJob);
			break;

		case MSG_EX_CASTLE_MAP_RECENT:
			{
				FLOAT	fLordX, fLordZ;
				FLOAT	nLordHP, nLordMaxHP;
				
				LONG	lTowerCount;
				
				LONG	lTowerIndex;
				FLOAT	fTowerX, fTowerZ;
				LONG	nTowerHP, nTowerMaxHP;

				FLOAT	fRegenX, fRegenY;
				LONG	nSenderFlag;
				LONG	nSenderIndex;
				FLOAT	fSignalX, fSignalY;
				
				extern SLONG	g_slZone;

				if( _pUISWDoc->IsWar() ) 
				{
					pUIManager->GetMap()->SetCurrentWorldMap( _pNetwork->MyCharacterInfo.zoneNo, 1 );
					pUIManager->GetMap()->ReSetData();
				}
				else
				{
					pUIManager->GetMap()->SetCurrentWorldMap( _pNetwork->MyCharacterInfo.zoneNo, 0 );
					return;
				}

				pUIManager->GetMap()->InitCastleData();
				// ����
				(*istr) >> fLordX;
				(*istr) >> fLordZ;
				(*istr) >> nLordHP;
				(*istr) >> nLordMaxHP;
				
				pUIManager->GetMap()->AddCastleData( CASTLE_LORD, fLordX, fLordZ, -1, nLordHP, nLordMaxHP );

				// ���� ž 
				(*istr) >> lTowerCount;

				for( int i = 0; i < lTowerCount; i++ )
				{
					(*istr) >> lTowerIndex;
					(*istr) >> fTowerX;
					(*istr) >> fTowerZ;
					(*istr) >> nTowerHP;
					(*istr) >> nTowerMaxHP;

					pUIManager->GetMap()->AddCastleData( CASTLE_TOWER, fTowerX, fTowerZ, lTowerIndex, nTowerHP, nTowerMaxHP );
				}

				// ���� ����Ʈ
				(*istr) >> fRegenX;
				(*istr) >> fRegenY;
				
				pUIManager->GetMap()->AddCastleData( CASTLE_REGEN, fRegenX, fRegenY );
				
				// Final Signal... 
				(*istr) >> nSenderFlag;
				(*istr) >> nSenderIndex;
				(*istr) >> fSignalX;
				(*istr) >> fSignalY;
					
				pUIManager->GetMap()->AddSignal( fSignalX, fSignalY, nSenderFlag, nSenderIndex );

			}
			break;

		case MSG_EX_CASTLE_MAP_SIGNAL:
			{
				LONG	nSenderFlag;
				LONG	nSenderIndex;
				FLOAT	fSignalX, fSignalY;
								 
				(*istr) >> fSignalX;
				(*istr) >> fSignalY;
				(*istr) >> nSenderFlag;
				(*istr) >> nSenderIndex;
				
				pUIManager->GetMap()->AddSignal( fSignalX, fSignalY, nSenderFlag, nSenderIndex );
			}
			break;

		case MSG_EX_ELEMENTAL_DELETE:
			{
				ReceiveElementalDeleteMessage( istr );
			}
			break;

		case MSG_EX_EVOCATION_START:
			{
				ReceiveEvocationStart( istr );
			}
			break;

		case MSG_EX_EVOCATION_STOP:
			{
				ReceiveEvocationStop( istr );
			}
			break;
			
		case MSG_EX_GUILDMEMBERNAMECHANGE :
			{
				ULONG	 charIndex; 
				(*istr) >> charIndex;
				(*istr) >> newName;
			//	if(_pNetwork->MyCharacterInfo.index == charIndex)
				pUIManager->GetGuild()->SetMemberName(charIndex,newName);

			}
			break;
		case MSG_EX_PARTY_MATCH :		// Date : 2006-05-09(���� 5:43:02), By eons
			{
				ULONG	ErrorType;
				ULONG	MatchType;
				(*istr) >> MatchType;

				switch( MatchType )
				{
				case MSG_EX_PARTY_MATCH_REG_MEMBER_REP:
					{
						(*istr) >> ErrorType;
						
						pUIManager->GetPartyAuto()->MatchRegMemberRep( ErrorType );
					}
					break;
				case MSG_EX_PARTY_MATCH_REG_PARTY_REP:
					{
						(*istr) >> ErrorType;

						pUIManager->GetPartyAuto()->MatchRegPartyRep( ErrorType );
					}
					break;
				case MSG_EX_PARTY_MATCH_MEMBER_LIST_REP:
					{
						pUIManager->GetPartyAutoInvite()->ReceiveMemberData(istr);						
					}
					break;
				case MSG_EX_PARTY_MATCH_PARTY_LIST_REP:
					{
						pUIManager->GetPartyAutoParty()->ReceivePartyData(istr);
					}
					break;
				case MSG_EX_PARTY_MATCH_DEL_REP:
					{
						strMessage = _S( 2732, "����� ���� �Ǿ����ϴ�." );
						MsgBoxInfo.SetMsgBoxInfo( _S( 2733, "��� ����" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
						MsgBoxInfo.AddString( strMessage );
						pUIManager->CreateMessageBox( MsgBoxInfo );						
					}
					break;
				case MSG_EX_PARTY_MATCH_INVITE_REP:
					{
						(*istr) >> ErrorType;

						pUIManager->GetPartyAutoInvite()->ReceivePartyInviteMessage(ErrorType, istr);
					}
					break;
				case MSG_EX_PARTY_MATCH_JOIN_REP:
					{
						(*istr) >> ErrorType;

						pUIManager->GetPartyAutoParty()->ReceivePartyJoinMessage(ErrorType, istr);
					}
					break;
				}
			}
			break;
		case MSG_EX_STRING :
			{
				BYTE	outType;
				LONG	strIdx,argCnt,argType;
				(*istr) >> outType >> strIdx >> argCnt;

				if(argCnt>0)
				{
					for(int i=0;i<argCnt;i++)
					{
						(*istr) >> argType;

						// arg 1
						if(argCnt==1){
							switch(argType)
							{
								case MSG_EX_STRING_CHAR : 		// char
									{
										BYTE arg1;
										(*istr) >> arg1;
										strMessage.PrintF(_S(strIdx,""),arg1);
									}
									break;
								case MSG_EX_STRING_INT :			// int
									{
										LONG arg1;
										(*istr) >> arg1;
										strMessage.PrintF(_S(strIdx,""),arg1);
									}
									break;
								case MSG_EX_STRING_LONGLONG :	// LONGLONG
									{
										LONGLONG arg1;
										(*istr) >> arg1;
										strMessage.PrintF(_S(strIdx,""),arg1);
									}
									break;
								case MSG_EX_STRING_STR :			// str(50)
									{
										CTString arg1;
										(*istr) >> arg1;
										strMessage.PrintF(_S(strIdx,""),arg1);
									}
									break;
							}

						}
				/*		// arg 2
						if(argCnt==2){
							if(i==1)
							switch(argType)
							{
								case MSG_EX_STRING_CHAR : 		// char
									{
										BYTE arg1;
										arg1 = new BYTE;
										(*istr) >> ((BYTE)(*arg1));
									}
									break;
								case MSG_EX_STRING_INT :			// int
									{
										static LONG arg1;
										(*istr) >> arg1;
									}
									break;
								case MSG_EX_STRING_LONGLONG :	// LONGLONG
									{
										static LONGLONG arg1;
										(*istr) >> arg1;
									}
									break;
								case MSG_EX_STRING_STR :			// str(50)
									{
										static CTString arg1;
										(*istr) >> arg1;
									}
									break;
							}
							if(i==2)
							switch(argType)
							{
								case MSG_EX_STRING_CHAR : 		// char
									{
										BYTE arg2;
										(*istr) >> arg2;
										strMessage.PrintF(_S(strIdx,""),arg1,arg2);
									}
									break;
								case MSG_EX_STRING_INT :			// int
									{
										LONG arg2;
										(*istr) >> arg2;
										strMessage.PrintF(_S(strIdx,""),arg1,arg2);
									}
									break;
								case MSG_EX_STRING_LONGLONG :	// LONGLONG
									{
										LONGLONG arg2;
										(*istr) >> arg2;
										strMessage.PrintF(_S(strIdx,""),arg1,arg2);
									}
									break;
								case MSG_EX_STRING_STR :			// str(50)
									{
										CTString arg2;
										(*istr) >> arg2;
										strMessage.PrintF(_S(strIdx,""),arg1,arg2);
									}
									break;
							}

							
						}*/
						
					}
				}
				else strMessage=_S(strIdx,"���� ȣ�� ��Ʈ��");

				if (strIdx == 8534)
				{

#ifdef BATTLE_PASS_SYSTEM
					CUIManager* pUIManager = CUIManager::getSingleton();

					if (pUIManager->GetBattlePassUI()->IsVisible())
					{
						_pNetwork->SendBattlePassInfoReq(NONE);
					}

#endif
#ifdef PRESTIGE_SYSTEM

					if (pUIManager->GetPrestigeUI()->IsVisible())
					{
						_pNetwork->SendPrestigeReq(NONE);
					}
#endif
				}
#ifdef BATTLE_PASS_SYSTEM
				if (strIdx == 9429)
				{
					strMessage = _S(9429, "You have a Battle Pass reward ready to claim!");
				}
#endif

				switch(outType)
				{
					case MSG_EX_STRING_OUTPUT_WINDOW :		// â
						{
							MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
							MsgBoxInfo.AddString(strMessage);
							pUIManager->CreateMessageBox(MsgBoxInfo);

						}
						break;
					case MSG_EX_STRING_OUTPUT_SYS :			// �ý���â
						pUIManager->GetChattingUI()->AddSysMessage(strMessage);
						break;
					case MSG_EX_STRING_OUTPUT_NOTICE :		// ����
						_UIAutoHelp->SetGMNotice ( strMessage );
						break;
					case MSG_EX_STRING_OUTPUT_CHAT :		// êâ
						 pUIManager->GetChattingUI()->AddChatMessage(MSG_CHAT_SAY,
							 _pNetwork->MyCharacterInfo.index,_pNetwork->MyCharacterInfo.name,strMessage);
						break;
				}
				
			}
			break;

		case MSG_EX_MESSENGER:
				ReceiveMessengerExMessage( istr );
				break;
		
		case MSG_EX_HAIR_CHANGE:
			{
				ReceiveExHairChange(istr);
			}
			break;
		case MSG_EX_PLAYER_STATE_CHANGE:
			{
				ReceiveExPlayerStateChange(istr);
			}
			break;
		case MSG_EX_NPROTECT:
			{
#ifndef NO_GAMEGUARD
				ReceiveExnProtect(istr);
#endif
			}
			
			break;
		case MSG_EX_PET_CHANGE_NAME:
			{
				ReceiveExPetNameChange(istr);
			}
			break;
			
		case MSG_EX_CASTLE_WAR: // WSS_DRATAN_SEIGEWARFARE 2007/07/30
		{
			UBYTE bType;
			ULONG charIdx;
			CTString tStr, tStrtmp;
			(*istr) >> bType;
			switch (bType)
			{
				case MSG_CASTLE_CRISTAL_RESPOND_WAIT:
					(*istr) >> charIdx;
					pUIManager->GetSiegeWarfareNew()->WaitConsensus(charIdx);
				case MSG_CASTLE_CRISTAL_RESPOND_START:
					(*istr) >> charIdx;
					pUIManager->GetSiegeWarfareNew()->StartConsensus(charIdx);
					break;
				case MSG_CASTLE_CRISTAL_RESPOND_END:	// ���� �Ϸ�								
					(*istr) >> charIdx;
					(*istr) >> tStrtmp;
					tStr.PrintF(_S(3898,"[%s]���� ũ����Ż ������ �����Ͽ����ϴ�."), tStrtmp);
					pUIManager->GetChattingUI()->AddSysMessage( tStr, SYSMSG_ERROR );
					pUIManager->GetSiegeWarfareNew()->CompleteConsensus(charIdx);
					break;
				case MSG_CASTLE_CRISTAL_RESPOND_FAIL:	// ���� ����
					(*istr) >> charIdx;
					if( _pNetwork->MyCharacterInfo.index == charIdx)
					{
						//pUIManager->GetChattingUI()->AddSysMessage( _S( 3751,"������ �����Ͽ����ϴ�."), SYSMSG_ERROR );
						//CUIMsgBox_Info	MsgBoxInfo;
						MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
						MsgBoxInfo.AddString(_S(3751,"������ �����Ͽ����ϴ�."), 0xE28769FF);
						pUIManager->CreateMessageBox( MsgBoxInfo );
					}
					pUIManager->GetSiegeWarfareNew()->StopConsensus(charIdx);					
					break;
				case MSG_CASTLE_TOWER_CONTRAL:
					{
						pUIManager->GetChattingUI()->AddSysMessage( _S( 3752,"���������� �����Ǿ����ϴ�." ), SYSMSG_ERROR );
					}
					break;
				case MSG_CASTLE_TOWER_CONTRAL_LIST:		// ����Ʈ Ÿ�� ���� ����Ʈ
					{
						UBYTE tSet[DRATAN_TOWER_KIND_MAX];
						for(int i=0;i<DRATAN_TOWER_KIND_MAX;i++)
						{
							(*istr) >> tSet[i];
							pUIManager->GetSiegeWarfareNew()->SetTowerSet(i,tSet[i]);
						}
						
						pUIManager->GetSiegeWarfareNew()->SetCBFromTowerSet();
						pUIManager->GetSiegeWarfareNew()->OpenCheckTower();						
						
					}
					break;
				case MSG_CASTLE_TOWER_REINFORCE:
					{
						CTString tStr,tStr2;
						UBYTE tType,tLevel;
						(*istr) >> tType >> tLevel;
						switch(tType)
						{
						case 0:
							tStr = _S( 3753,"������ Ÿ��");
							break;
						case 1:
							tStr = _S( 3754,"������ Ÿ��");
							break;
						case 2:
							tStr = _S( 3755,"����");
							break;
						}						
						tStr2.PrintF("%d %s",(int)tLevel, _S( 3756,"�ܰ谡 ���������� ��ȭ�Ǿ����ϴ�." ));
						tStr += tStr2;
						pUIManager->GetChattingUI()->AddSysMessage( tStr, SYSMSG_ERROR );
					}
					break;
				case MSG_CASTLE_TOWER_REINFORCE_LIST:
					{					
						UBYTE tType,tLevel;
						(*istr) >> tType >> tLevel;		
						if( (int)tType == pUIManager->GetSiegeWarfareNew()->GetUpgradeType())
						{								
							
							pUIManager->GetSiegeWarfareNew()->SetUpgradedLevel(int(tLevel));
							pUIManager->GetSiegeWarfareNew()->SetUpgradePos(int(tLevel));
							pUIManager->GetSiegeWarfareNew()->SetUpgradeLevel((int)tLevel );
							pUIManager->GetSiegeWarfareNew()->OpenUpgradeTower();
						}
						else 
							pUIManager->GetChattingUI()->AddSysMessage( _S( 3757,"��ȭ�� Ÿ���� �ùٸ��� �ʽ��ϴ�." ), SYSMSG_ERROR );	
					}
					break;
				case MSG_CASTLE_TOWER_REPAIRE:			// ���� Ÿ�� ����    cl->gs idx(n) | gs->cl idx(n)
					{
						ULONG tIdx;
						(*istr) >> tIdx;
						pUIManager->GetChattingUI()->AddSysMessage( _S( 3758,"���������� �����Ǿ����ϴ�." ), SYSMSG_ERROR );	
						
					}
					break;
				case MSG_CASTLE_TOWER_REPAIRE_LIST:		// ���� Ÿ�� ���� ����   cl->gs idx(n) | gs->cl money(n)
					{
						ULONG tNpcIdx;
						SQUAD tMoney;

						(*istr) >> tNpcIdx >> tMoney;
						pUIManager->GetSiegeWarfareNew()->SetRepairMoney( tNpcIdx,tMoney );
						pUIManager->GetSiegeWarfareNew()->OpenRepairTower();
					}
					break;
				case MSG_CASTLE_TOWER_WARP_LIST:
					{
						UBYTE tCnt;
						ULONG tNpcIdx;

						(*istr) >> tCnt;
						for( int i=0;i<tCnt ;i++)
						{
							(*istr) >> tNpcIdx;
							pUIManager->GetGuildWarPortal()->SetDratanPortalFlag((int)tNpcIdx);
						}
						pUIManager->GetGuildWarPortal()->OpenGuildWarPortalDratan();
					}
					break;				
				case MSG_CASTLE_QUARTERS_INSTALL:		// ��Ȱ���� ��ġ cl->gs idx(n) | gs->cl  idx(n), gidx(n)
					{
						CTString tStr,tGuildName;
						ULONG tNpcIdx,tGuildIdx;
						SLONG tNpcUniIndex;
						(*istr) >> tNpcIdx >> tGuildIdx >> tGuildName >> tNpcUniIndex;
						tStr.PrintF(_S( 3759,"[%s]��尡 [%d]�� ��Ȱ������ �����߽��ϴ�." ),tGuildName,tNpcIdx-389); // TEMP
						_pNetwork->MyCharacterInfo.mQuarter[tNpcIdx] = tGuildIdx;
						_pNetwork->MyCharacterInfo.mQuarterName[tNpcIdx] = tGuildName;						
						pUIManager->GetChattingUI()->AddSysMessage( tStr, SYSMSG_ERROR );

						// �� �̸� ����
						CMobData* MD = CMobData::getData(tNpcIdx);
						if(MD->GetMobIndex()>0 && tGuildName.Length() >0 && tGuildIdx != -1)
						{							
							tStr = tGuildName + CTString(" ") + _S( 3760,"���� ��Ȱ����");;
							MD->SetName(tStr);

							tStr = MD->GetName();
							MD = CMobData::getData(tNpcIdx);
							tStr = MD->GetName();
						}

						if (!MD->IsNPC())
						{
							CEntity* pEntity = NULL;

							int		i;

							for (i = 0; i < eOBJ_MAX; ++i)
							{
								pEntity = ACTORMGR()->GetEntityByIndexServer((eOBJ_TYPE)i, tNpcUniIndex);
								// �Ϲ� npc���� ���ͷ� ���� ����(���� ���� ���� ������ npc�� )
								if (pEntity != NULL)
								{
									pEntity->SetFirstExtraFlagOff(ENF_EX1_NPC);
									break;
								}
							}
						}
					}
					break;
				case MSG_CASTLE_QUARTERS_CRUSH:			// ��Ȱ ���� �ı� gs->cl idx(n)
					{
						CTString tStr;
						ULONG tNpcIdx;
						(*istr) >> tNpcIdx;
						tStr.PrintF(_S( 3705,"%d�� ��Ȱ������ �ı��Ǿ����ϴ�." ),tNpcIdx-389); // TEMP
						_pNetwork->MyCharacterInfo.mQuarter[tNpcIdx] = -1;
						_pNetwork->MyCharacterInfo.mQuarterName[tNpcIdx] = CTString("");
						pUIManager->GetChattingUI()->AddSysMessage( tStr, SYSMSG_ERROR );

						// Hard Cording ^^;; ��¿�� ����....
						// �� �̸� ����
						CMobData* MD = CMobData::getData(tNpcIdx);
						if(MD->GetMobIndex()>0)
						{
							tStr.PrintF(_S( 3685,"���� ��Ȱ����%d"),tNpcIdx-389);
							MD->SetName(tStr);
						}						
					}
					break;
				case MSG_CASTLE_QUARTERS_LIST:			// ��Ȱ ���� ����Ʈ gs->cl 7*(nindex(n), gindex(n))
					{		
						CTString tGuildName;
						LONG tNpcIdx,tGuildIdx;

						for(int i=0;i<7;i++)
						{	
							(*istr) >> tNpcIdx >> tGuildIdx >> tGuildName;						
							// ���� ��尡 �����ϸ�...
							if (tGuildIdx!=-1)
							{
								_pNetwork->MyCharacterInfo.mQuarter[tNpcIdx] = tGuildIdx;
								_pNetwork->MyCharacterInfo.mQuarterName[tNpcIdx] = tGuildName;

								// �� �̸� ����
								CMobData* MD = CMobData::getData(tNpcIdx);
								if(MD->GetMobIndex()>0 && tGuildName.Length() >0 && tGuildIdx != -1)
								{
									tStr = tGuildName +CTString(" ") +_S( 3760,"���� ��Ȱ����");
									MD->SetName(tStr);
								}
							}
							// ���� ��尡 ���ٸ�...
							else 
							{
								// Hard Cording ^^;; ��¿�� ����....
								// �� �̸� ����
								CMobData* MD = CMobData::getData(tNpcIdx);
								if(MD->GetMobIndex()>0)
								{
									tStr.PrintF(_S( 3685,"���� ��Ȱ����%d"),tNpcIdx-389);
									MD->SetName(tStr);
								}						
							}
						}
					}
					break;

				case MSG_CASTLE_WAIT_TIME:				// ��Ȱ ��� �ð�
					{
						LONG tWaitTime;
						(*istr) >> tWaitTime;						
						pUIManager->GetSiegeWarfareNew()->SetWaitTime(tWaitTime);
						pUIManager->GetSiegeWarfareNew()->SetTimeReply(TRUE);

					}
					break;
				case MSG_EX_CASTLE_ERROR:				// ���� ����
					{
						UBYTE errcode;
						(*istr) >> errcode;
						CheckDratanSiegewarfareError(errcode);
					}

			}
		}
		break;
	
		case MSG_EX_PET_CHANGE_COLOR:
			{
				ReceiveExPetColorChange(istr);
			}
			break;
// EDIT : BS : 070413 : �ű� ��Ŷ ��ȣȭ			
#ifdef CRYPT_NET_MSG
#ifdef CRYPT_NET_MSG_MANUAL
	case MSG_EX_KEYCHANGE:		// EDIT : BS : ��Ŷ ��ȣȭ : Ű ����
		{
			ULONG nKey;
			(*istr) >> nKey;
			CNM_CopyKey(&_pNetwork->cnmKey, (CNM_KEY_TYPE*)&nKey);
		}
		break;
#endif // CRYPT_NET_MSG_MANUAL
#else
	case MSG_EX_KEYCHANGE:
		{
			ULONG nKey;
			(*istr) >> nKey;
			_pNetwork->cnmKey = nKey;
		}
#endif // #ifdef CRYPT_NET_MSG

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//[071123: Su-won] DRATAN_SIEGE_DUNGEON
	case MSG_EX_DVD:
		{
			UBYTE sbSubType;
			
			(*istr) >> sbSubType;

			switch(sbSubType)
			{
			case MSG_DUNGEON_INFO:
				{
					ULONG ulEnvRate, ulMonRate;
					
					(*istr) >> ulEnvRate;
					(*istr) >> ulMonRate;

					pUIManager->GetPortal()->Create_SiegeDungeon_State_MsgBox( ulEnvRate, ulMonRate);
				}
				break;
			case MSG_MANAGEMENT:
				{
					UBYTE sbSubSubType, ubError;

					(*istr) >> sbSubSubType;
					switch( sbSubSubType )
					{
					case MSG_MANAGEMENT_MANAGER_CONFIRM:				//���� ��û
						{
							(*istr) >> ubError;

							if( ubError == MSG_DVD_ERROR_OK )
							{
								pUIManager->CreateMessageBoxL( _S(3908, "���� ����"),UI_PORTAL, MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL);
								pUIManager->AddMessageBoxLString(MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL,TRUE, _S(3940, "�ȳ��Ͻʴϱ�? ���ִ�."),-1,0xa3a1a3ff);
								pUIManager->AddMessageBoxLString(MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL,TRUE, _S(3941, "������ � �κ��� �����Ͻðڽ��ϱ�?"),-1,0xa3a1a3ff);

								pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL, FALSE, _S(3921, "���� ���� ȯ�� ����" ), DRATAN_SIEGE_DUNGEON_CONTROL_ENVIRONMENT);
								pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL, FALSE, _S(3926, "���� ���� ���� ����" ), DRATAN_SIEGE_DUNGEON_CONTROL_MONSTER);
								pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL, FALSE, _S(3931, "���� ����� ����" ), DRATAN_SIEGE_DUNGEON_CONTROL_ADMISSION_FEE);
								pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL, FALSE, _S(3935, "���� ���Ƽ��� ����" ), DRATAN_SIEGE_DUNGEON_CONTROL_HUNTING_FEE);
								pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL, FALSE, _S( 1220, "����Ѵ�." ) );

								SERVER_INFO()->SetDG_Mode(eDUNGEON_MODE_LORD);
							}
							else if( ubError == MSG_DVD_ERROR_CONFIRM )
							{
								pUIManager->CloseMessageBox(MSGCMD_NULL);
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(3942, "���� ����� ������, �Ǵ� �α�帶���͸� ������ �� �ֽ��ϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );
							}
							else if (ubError == MSG_DVD_ERROR_ZONE)
							{
								pUIManager->CloseMessageBox(MSGCMD_NULL);
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(6275, "���� ä�ο����� �̿��� �����մϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );
							}
							else if (ubError == MSG_DVD_ERROR_NORMAL_MODE)
							{
								LONGLONG llNas = 0;
								(*istr) >> llNas;
								CTString strString;
								CTString strTemp;
								strTemp.PrintF("%I64d", llNas);
								pUIManager->InsertCommaToString(strTemp);

								strString.PrintF(_S(7065, "�˼������� ���ִ� ������ �Ϲ� ���� ��� �Դϴ�. %s ������ ������"), strTemp);
								pUIManager->CreateMessageBoxL( _S(3908, "���� ����"),UI_PORTAL, MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL);
								pUIManager->AddMessageBoxLString(MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL,TRUE, strString, -1, 0xa3a1a3ff);
								pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL, FALSE, _S(191, "Ȯ��" ), DRATAN_SIEGE_DUNGEON_CHANGE_LORDMODE);
								pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL, FALSE, _S( 139, "���" ) );
							}
						}
						break;
					case MSG_MANAGEMENT_MANAGER_ENV_INFO:				//���� ���� ȯ�� ���� ��û
						{
							ULONG ulCurRate;
							LONGLONG llNas;
							(*istr) >> ulCurRate;
							(*istr) >> llNas;

							if( ulCurRate >90)
							{
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(3943, "���̻� ��½�ų �� �����ϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );

								return;
							}
														
							SERVER_INFO()->SetDG_EnvNas(llNas / 10); // 10% ��½� �����ϴ� �ݾ��� ���⿡ ����
							pUIManager->GetPortal()->Create_SiegeDungeon_EnvCtr_MsgBox(ulCurRate);
						}
						break;
					case MSG_MANAGEMENT_MANAGER_MONSTER_INFO:			//���� ���� ���� ���� ��û
						{
							ULONG ulCurRate;
							LONGLONG llNas;
							(*istr) >> ulCurRate;
							(*istr) >> llNas;

							SERVER_INFO()->SetDG_MonsterNas(llNas / 10); // 10% ��½� �����ϴ� �ݾ��� ���⿡ ����

							if( ulCurRate >90)
							{
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(3943, "���̻� ��½�ų �� �����ϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );

								return;
							}

							pUIManager->GetPortal()->Create_SiegeDungeon_MonCtr_MsgBox(ulCurRate);
						}
						break;
					case MSG_MANAGEMENT_MANAGER_TAX_INFO:				//����� ���� ���� ��û
						{
							ULONG ulCurFee;
							(*istr) >> ulCurFee;

							pUIManager->GetPortal()->Create_SiegeDungeon_AdmissionCtr_MsgBox(ulCurFee);
						}
						break;
					case MSG_MANAGEMENT_MANAGER_HUNTER_TAX_INFO:		//���Ƽ� ���� ��û
						{
							ULONG ulCurFee;
							(*istr) >> ulCurFee;

							pUIManager->GetPortal()->Create_SiegeDungeon_HuntingCtr_MsgBox(ulCurFee);
						}
						break;
					case MSG_MANAGEMENT_MANAGER_ENV_CHANGE:				//���� ����ȯ�� ����
					case MSG_MANAGEMENT_MANAGER_MONSTER_CHANGE:			//���� ���� ���� ���� ����
					case MSG_MANAGEMENT_MANAGER_TAX_CHANGE:				//����� ���� ����
					case MSG_MANAGEMENT_MANAGER_HUNTER_TAX_CHANGE:		//���Ƽ� ����
						{
							(*istr) >> ubError;
							if( ubError == MSG_DVD_ERROR_OK )
							{
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(3944, "������ ���°� ����Ǿ����ϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );
							}
							else if( ubError == MSG_DVD_ERROR_MONEY)
							{
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(967, "������ �����մϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );
							}
						}
						break;
					case MSG_MANAGEMENT_MANAGER_CONFIRM_NORMAL:
						{
							(*istr) >> ubError;

							if( ubError == MSG_DVD_ERROR_OK )
							{
								pUIManager->CreateMessageBoxL( _S(3908, "���� ����"),UI_PORTAL, MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL);
								pUIManager->AddMessageBoxLString(MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL,TRUE, _S(7060, "���� �׿��� ������ ... ���� ��� ������ ���� �Ҽ� �ִ� ������ �帮�ڽ��ϴ�."),-1,0xa3a1a3ff);
								pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL, FALSE, _S(3921, "���� ���� ȯ�� ����" ), DRATAN_SIEGE_DUNGEON_CONTROL_ENVIRONMENT);
								pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL, FALSE, _S(3926, "���� ���� ���� ����" ), DRATAN_SIEGE_DUNGEON_CONTROL_MONSTER);
								pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL, FALSE, _S( 1220, "����Ѵ�." ) );

								SERVER_INFO()->SetDG_Mode(eDUNGEON_MODE_NOMAL);
							}
							else if( ubError == MSG_DVD_ERROR_CONFIRM )
							{
								pUIManager->CloseMessageBox(MSGCMD_NULL);
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(7074, "������ ���� ������ �� �̷������ �ִ� ���·�, ���� ���� ������ ���ֿ��� �ֽ��ϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );
							}
							else if( ubError == MSG_DVD_ERROR_NORMAL_MODE )
							{
								pUIManager->CloseMessageBox(MSGCMD_NULL);
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(7071, "������ �Ϲ� ���� ���� ���� ������ ���ִ��� �ƴ� ������ �̿��ϴ� �÷��̾���� ���� ������ �ϰ� �ֽ��ϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );
							}							
							else if (ubError == MSG_DVD_ERROR_ZONE)
							{
								pUIManager->CloseMessageBox(MSGCMD_NULL);
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(6275, "���� ä�ο����� �̿��� �����մϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );
							}
						}
						break;
					case MSG_NAMAGEMENT_CHANGE_OWNER_MODE:
						{
							(*istr) >> ubError;

							if( ubError == MSG_DVD_ERROR_OK )
							{
								pUIManager->CloseMessageBox(MSGCMD_NULL);
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(7069, "���������� ������ �����ϼż� ���ݺ��� ���ִ��� ���� �Ͻ� �� �����ʴϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );
							}
							else if( ubError == MSG_DVD_ERROR_CONFIRM )
							{
								pUIManager->CloseMessageBox(MSGCMD_NULL);
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(3942, "���� ����� ������, �Ǵ� �α�帶���͸� ������ �� �ֽ��ϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );
							}
							else if (ubError == MSG_DVD_ERROR_MONEY)
							{
								pUIManager->CloseMessageBox(MSGCMD_NULL);
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(7070, "������ ���� �Ͽ� ������ �Ͻ� �� �����ϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );
							}
						}
						break;
					}
				}
				break;
			case MSG_DUNGEON_ENTER:
				{
					UBYTE ubSubSubType;
					(*istr) >> ubSubSubType;

					switch( ubSubSubType )
					{
					case MSG_DUNGEON_ENTER_FEE:
						{
							__int64 ulNeedNas;
							(*istr) >> ulNeedNas;

							if( ulNeedNas <= 0 )
							{
								_pNetwork->SendDratanSiegeDungeonMSG(MSG_DUNGEON_ENTER, MSG_DUNGEON_GO);
								return;
							}

							if( pUIManager->DoesMessageBoxExist(MSGCMD_SIEGE_DUNGEON_ENTER) )
								pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_ENTER);
							
							strMessage.PrintF( _S( 191, "Ȯ��" ) );
							MsgBoxInfo.SetMsgBoxInfo(strMessage,UMBS_YESNO,UI_PORTAL,MSGCMD_SIEGE_DUNGEON_ENTER);

							CTString strNas;
							strNas.PrintF("%I64d", ulNeedNas);
							pUIManager->InsertCommaToString(strNas);
							strMessage.PrintF( _S(3945, "�������� �̵��ϱ� ���ؼ��� %s������ �ʿ��մϴ�. �̵� �Ͻðڽ��ϱ�?" ), strNas );
							MsgBoxInfo.AddString(strMessage);

							pUIManager->CreateMessageBox(MsgBoxInfo);
						}
						break;
					case MSG_DUNGEON_GO:
						{
							UBYTE ubError;
							(*istr) >> ubError;

							if( ubError == MSG_DVD_ERROR_MONEY )
							{
								MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
								MsgBoxInfo.AddString( _S(967, "������ �����մϴ�.") );
								pUIManager->CreateMessageBox( MsgBoxInfo );

								pUIManager->SetCSFlagOff(CSF_TELEPORT);
							}
						}
					}
				}
				break;
			case MSG_GUILD_NAME_COLOR:
				{
					ULONG ulCharIndex;
					UBYTE ubCol;

					(*istr) >> ulCharIndex;
					(*istr) >> ubCol;

					if( ulCharIndex == _pNetwork->MyCharacterInfo.index)
					{				
						_pNetwork->MyCharacterInfo.ubGuildNameColor = ubCol;		
					}
					else
					{
						ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, ulCharIndex);

						if (pObject != NULL)
						{
							CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);

							pTarget->cha_ubGuildNameColor = ubCol;
						}
					}
				}
				break;

			case MSG_CHANGE_NORMAL_NOTICE: // �Ϲݸ�� ��ȯ
				{
					strMessage = _S(7067, "���ݺ��� �׿����� ������ ���� �������� �Ϲ� ������ ��ȯ�Ǿ� ���ָ� ���� �� ������ �׿����� ������ ���� �Ͻ� �� �ֽ��ϴ�. ");
					_UIAutoHelp->SetGMNotice(strMessage);
					_pNetwork->ClientSystemMessage(strMessage);
				}
				break;

			case MSG_CHANGE_NORMAL_NOTICE_TO_OWNER:
				{
					MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString( _S(7068, "���ݺ��� �׿����� ������ �Ϲ� ������ ��ȯ�Ǿ� ���� ���� ���� �����۰� ������ ���� ���� �����, ���Ƽ��� ���� ���� ���մϴ�. ������ ������ �ٽ� ��ã���ø��� ���� �������� ã�ư� ��������� ���� ������ �����ؾ� ������ ã�� �� �ֽ��ϴ�.") );
					pUIManager->CreateMessageBox( MsgBoxInfo );
				}
				break;
			}
		}
		break;
		//[071123: Su-won] DRATAN_SIEGE_DUNGEON
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case MSG_EX_PET_TURNTO_NPC: // �� ����
		{
			SLONG slPetIndex;
			SLONG slNpcIndex;
			SLONG slCharIndex;
			SLONG slNpcSize;

			(*istr) >> slPetIndex >> slNpcIndex >> slCharIndex >> slNpcSize;

			CEntity* penEntity = NULL;

			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_PET, slPetIndex);
			CPetTargetInfom* pPetInfo = INFO()->GetMyPetInfo();

			if (pObject != NULL)
			{
				penEntity = pObject->GetEntity();
			}

			if (penEntity != NULL)
			{
				if (penEntity == pPetInfo->pen_pEntity) // �ڽ��� ������ ���� ���
					pPetInfo->TransformIndex = slNpcIndex;

				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->TransfromPet(penEntity, slNpcIndex, slNpcSize); // 10�� ������ 1��
			}
		}
		break;
	
	// [080422: Su-won] EVENT_CHAOSBALL
	case MSG_EX_CHAOSBALL:
		{
			(*istr) >> errcode;

			switch(errcode)
			{
			case MSG_CHAOSBALL_ERROR_SUCCESS:
				break;
			case MSG_CHAOSBALL_ERROR_ITEM_COUNT:
				break;
			case MSG_CHAOSBALL_ERROR_NOSPACE:
				pUIManager->GetChattingUI()->AddSysMessage( _S( 265,  "ĳ���� �κ��丮 ������ �����մϴ�." ), SYSMSG_ERROR );
				break;
			case MSG_CHAOSBALL_ERROR_ITEM_FAULT:
				break;
			}			
		}
	case MSG_EX_ATTACK_PET:
		{
			UBYTE ubSubType;
			(*istr) >> ubSubType;

			ReceiveExWildPetMessage(ubSubType, &(*istr));

		}break;

	///////////////////////////////////////////////////////////////////////////////////	
	// Cube
	case MSG_EX_EXTREME_CUBE:
		{
			UBYTE ubSubType;
			(*istr) >> ubSubType;

			switch( ubSubType )
			{
			case MSG_EX_EXTREME_CUBE_STATE_REP:
				{
					pUIManager->GetCubeRank()->CreateCubeState(istr, TRUE);
				}
				break;
			case MSG_EX_EXTREME_CUBE_STATE_PERSONAL_REP:
				{
					pUIManager->GetCubeRank()->CreateCubeState(istr, FALSE);
				}
				break;
			case MSG_EX_EXTREME_CUBE_COMPLETE:
				{
					INDEX ubCnt;
					(*istr) >> ubCnt;

					//pUIManager->GetCombo()->SetComboCount(ubCnt);
					pUIManager->GetCombo()->StageComplete(ubCnt,1);
					pUIManager->GetCombo()->SetSysImage(SYS_STAGE, TRUE, CUBE_TYPE);
				}
				break;
			case MSG_EX_EXTREME_CUBE_ERROR:
				{
					UBYTE ubErrorType;
					(*istr) >> ubErrorType;

					BOOL bShowBox = TRUE;

					switch( ubErrorType )
					{
					case MSG_EX_EXTREME_CUBE_ERROR_NOITEM:
						{
							strMessage = _S(1330, "�������� �����մϴ�.");
							pUIManager->SetCSFlagOff(CSF_TELEPORT);
						}
						break;
					case MSG_EX_EXTREME_CUBE_ERROR_OVERCOUNT:
						{
							strMessage = _S(4374, "���� �� �� �ִ� ���� �������� �ʽ��ϴ�. ��� �� �ٽ� �õ��Ͽ� �ֽʽÿ�.");
							pUIManager->SetCSFlagOff(CSF_TELEPORT);
						}
						break;
					case MSG_EX_EXTREME_CUBE_ERROR_CANNOT_MOVE:
						{
							strMessage = _S(4375, "���� ť�꿡 �� �� �����ϴ�. ��� �� �ٽ� �õ��Ͽ� �ֽʽÿ�.");
							pUIManager->SetCSFlagOff(CSF_TELEPORT);
						}
						break;
					case MSG_EX_EXTREME_CUBE_ERROR_CANNOT_CAHNGE_RATE:
						{
							strMessage = _S(4376, "����ť�� ������ ������ �� �����ϴ�.");
						}
						break;
					case MSG_EX_EXTREME_CUBE_ERROR_NOT_GUILD_CUBE_TIME:
						{
							strMessage = _S(4377, "��� ť�� ���� �ð��� �ƴմϴ�.");
							pUIManager->SetCSFlagOff(CSF_TELEPORT);
						}
						break;
					case MSG_EX_EXTREME_CUBE_ERROR_NOT_PARTY_CUBE_TIME:
						{
							strMessage = _S(4397, "��Ƽ ť�� ���� �ð��� �ƴմϴ�.");
							pUIManager->SetCSFlagOff(CSF_TELEPORT);
						}
						break;
					case MSG_EX_EXTREME_CUBE_ERROR_PARTYCUBE:
						{ // ��Ƽ ť�� ����
							strMessage = _S(4398, "��Ƽ ť�꿡 �����Ͽ����ϴ�.");
							_pNetwork->MyCharacterInfo.EntranceType = CURRENT_ENTER_PARTYCUBE;
							bShowBox = FALSE;
						}
						break;
					case MSG_EX_EXTREME_CUBE_ERROR_GUILDCUBE:
						{ // ��� ť�� ����
							strMessage = _S(4399, "��� ť�꿡 �����Ͽ����ϴ�.");
							_pNetwork->MyCharacterInfo.EntranceType = CURRENT_ENTER_GUILDCUBE;
							bShowBox = FALSE;
						}
						break;
					case MSG_EX_EXTREME_CUBE_ERROR_START_NOTICE: // ���ť�� ���۸޽���
						{
							strMessage = _S(4401, "���ť�갡 ���۵ǰ� ��Ƽť�갡 ����Ǿ����ϴ�.");
							_UIAutoHelp->SetGMNotice(strMessage);
							bShowBox = FALSE;
						}
						break;
					case MSG_EX_EXTREME_CUBE_ERROR_END_NOTICE: // ���ť�� ����޽���
						{
							strMessage = _S(4402, "���ť�갡 ����ǰ� ��Ƽť�갡 ���۵Ǿ����ϴ�.");
							_UIAutoHelp->SetGMNotice(strMessage);
							bShowBox = FALSE;
						}
						break;
					case MSG_EX_EXTREME_CUBE_ERROR_START_REMAINTIME: // ���ť�� ���� 1���� �޽��� 
						{
							strMessage = _S(4403, "1�� �� ���ť�갡 ���۵ǰ� 1�� �� ��Ƽť�갡 ����˴ϴ�.");
							_UIAutoHelp->SetGMNotice(strMessage);
							bShowBox = FALSE;
						}
						break;
					case MSG_EX_EXTREME_CUBE_ERROR_END_REMAINTIME: // ���ť�� ���� 1���� �޽���
						{
							strMessage = _S(4404, "1�� �� ��Ƽť�갡 ���۵ǰ� 1�� �� ���ť�갡 ����˴ϴ�.");
							_UIAutoHelp->SetGMNotice(strMessage);
							bShowBox = FALSE;
						}
						break;
					case MSG_EX_EXTREME_CUBE_ERROR_INVEN_NOSPACE:		// �κ� ��������
						{
							strMessage = _S(265, "�κ��丮 ������ �����մϴ�.");
						}break;
					case MSG_EX_EXTREME_CUBE_ERROR_REWARD_PERSONAL_CANNOT:	// ���κ��� ���� �ȸ���
						{
							strMessage = _S(1722, "������ ������ �� �ִ� ������ �ƴմϴ�");
						}break;
					case MSG_EX_EXTREME_CUBE_ERROR_REWARD_PERSONAL_ALREADY:	// ���κ��� �̹� �޾���	
						{
							strMessage = _S(1755, "�̹� ������ �޾ҽ��ϴ�.");
						}break;
					}
					
					if (bShowBox)
					{
						MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
						MsgBoxInfo.AddString(strMessage);
						pUIManager->CreateMessageBox(MsgBoxInfo);
					}
					else
					{
						_pNetwork->ClientSystemMessage(strMessage);
					}
				}
				break;
			}
		}
		break;
	// Cube
	///////////////////////////////////////////////////////////////////////////////////	
	case MSG_EX_INIT_SSKILL:
		{
			UBYTE ubSubType;
			(*istr) >> ubSubType;

			MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

			switch(ubSubType)
			{
			case MSG_EX_INIT_SSkill_ERROR_SUCCESS:
				{
					MsgBoxInfo.AddString(_S(4247, "����� ��ų �ʱ�ȭ�� �����Ͽ����ϴ�."));
				}
				break;
			case MSG_EX_INIT_SSkill_ERROR_FAIL:
				{
					MsgBoxInfo.AddString(_S(4248, "����� ��ų �ʱ�ȭ�� �����Ͽ����ϴ�."));
				}
				break;
			}

			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;
	case MSG_EX_TRIGGER_EVENT:
		{
			UBYTE ubSubType;
			INDEX iTouchID, iPlayID, iContinued;
			(*istr) >> ubSubType;
			(*istr) >> iTouchID >> iPlayID >> iContinued;

			switch(ubSubType)
			{
			case MSG_EX_TRIGGER_EVENT_ERROR: // ���� ����
				break;
			case MSG_EX_TRIGGER_EVENT_ALREADY_PLAY: // �̹� Ȱ��ȭ ��
				break;
			case MSG_EX_TRIGGER_EVENT_NO_CONDITION: // ������ ������ �ȵ� (� ������ �������� Ŭ�� �˻��ؾ� �ϳ�?)
				break;
			case MSG_EX_TRIGGER_EVENT_TRIGER_EXIST_AREA: // �� �̵��� �̹� ���۵� ȯ�� ������Ʈ�� ������ ������Ʈ �Ѵ�.(Sub Info : 1. Obj count, 2. Objects ID
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ReceiveTriggerEvent(iTouchID, iPlayID, iContinued, istr);
				break;
			case MSG_EX_TRIGGER_EVENT_ITEM_COMPOSITION: // ������ ���� �Ϸ�
				pUIManager->GetChattingUI()->AddSysMessage(_S(4669, "������ ���� �Ϸ�"));
				break;
			case MSG_EX_TRIGGER_EVENT_ITEM_DROP: // �������� �����( � �������� ����� �Ǵ��� Ŭ�� �˾ƾ� �˷��ֳ�?)
				pUIManager->GetChattingUI()->AddSysMessage(_S(4670, "������ ��� �Ϸ�"));
				break;
			case MSG_EX_TRIGGER_EVENT_OPEN_THE_DOOR: // Door object�� ���� ����.(�浹����)
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ReceiveTriggerEvent(iTouchID, iPlayID, iContinued, NULL);
				break;
			case MSG_EX_TRIGGER_EVENT_START_RAID: // ���̵� ������ �÷��� ����
				{				
					//pUIManager->GetChattingUI()->AddSysMessage(_s("���̵� �÷��� ����"));					
				}
				break;
			case MSG_EX_TRIGGER_EVENT_MESSAGE_PRINT: // ���� �޼����� ���(� �޼����� ������� Ŭ�� �˾Ƽ��ؾ� ��)
				{				
					// [090709: selo] ��Ʈ�� �ε����� �޾� ����Ʈ�Ͽ� ���̵� �޽����� �߰��Ѵ�
					INDEX iStringIndex = 0;
					(*istr) >> iStringIndex;
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
					if (iStringIndex == -1)
					{
						GAMEDATAMGR()->GetQuest()->RemoveRaidMessageAll();
					}
#endif					
					if (iStringIndex > 0)
					{
						GAMEDATAMGR()->GetQuest()->AddRaidMessage(iStringIndex);
					}
				}
				break;
			case MSG_EX_TRIGGER_EVENT_SUMMON_NPC: // npc�� ��ȯ�Ѵ�.(� npc�� ��ȯ���� Ŭ�� �˾Ƽ� �ؾ� �Ѵ�.)
				//pUIManager->GetChattingUI()->AddSysMessage(_s("npc��ȯ �Ϸ�"));
				break;
			case MSG_EX_TRIGGER_EVENT_USE_DEBUF: // ĳ���Ͱ� ������� �ɷȴ�.(�ڽ��� ĳ���͸�)
				//pUIManager->GetChattingUI()->AddSysMessage(_s("�� ������� �ɷȴ�~"));
				break;
			case MSG_EX_TRIGGER_EVENT_ACTIVE_OBJECT: // ������Ʈ�� Ȱ��ȭ(�ִϸ��̼��� �����Ѵ�.)
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ReceiveTriggerEvent(iTouchID, iPlayID, iContinued, NULL);
				break;
			case MSG_EX_TRIGGER_EVENT_REMOVE_NPC: // npc �ڵ� ���� (npc�� �����Ѵ�. �� �ʿ��ұ�?)
				//pUIManager->GetChattingUI()->AddSysMessage(_s("npc ����~"));
				break;
			case MSG_EX_TRIGGER_EVENT_TIME_LIMIT:
				{
					// [090707: selo] 
					// ���� �ð��� �޾Ƽ� 0 �̻��̸� ���� �ð��� �����Ѵ�.
					INDEX iRemainTime = 0;
					(*istr) >> iRemainTime;

					// 0 �̸� �ð��� �ٵǼ� ���� ��
					if( 0 == iRemainTime )
					{
						GAMEDATAMGR()->GetQuest()->RaidEnd();
					}
					// -1 �̸� ���ӵ� ���͸� ��Ƽ� ���� ��
					else if( -1 == iRemainTime )
					{
						GAMEDATAMGR()->GetQuest()->RaidEnd();
					}
					else
					{
						// [090907: selo] ���̵� ���� �ð��� �˸���.
						GAMEDATAMGR()->GetQuest()->SetRaidRemainTime(iRemainTime);	
				}	}
				break;
			case MSG_EX_TRIGGER_EVENT_RESTORE_OBJECT:
				{
					CEntity *tmpEntity = NULL;

					tmpEntity = _pNetwork->ga_World.EntityFromID(iPlayID);

					if (tmpEntity != NULL)
					{
						tmpEntity->Precache();
					}
				}
				break;
			}
		}
		break;
	case MSG_EX_AFFINITY:
		{
			ReceiveAffinityMessage( istr );
		}
		break;
		
	case MSG_EX_TUTORIAL:
		{
			pUIManager->GetHelp()->OpenTutorial();
		}	
		break;
		
	case MSG_EX_LOADING_END:
		{
			ReceiveExLoadingEndMessage( istr );
		}
		break;

	case MSG_EX_NPC_PORTAL_SCROLL:
		{
			ReceiveNPCPortalMessage( istr);
		}
		break;
		
	case MSG_EX_RAID_INFO:
		{
			SLONG nRaidCount = 0;
			SLONG nZoneNum = 0;
			SLONG nRoomNum = 0;

			(*istr) >> nRaidCount;

			if(pUIManager->DoesMessageBoxExist(MSGCMD_RAID_INFO))
				pUIManager->CloseMessageBox(MSGCMD_RAID_INFO);

			MsgBoxInfo.SetMsgBoxInfo( _S(4754, "�ͼӵ� ���̵� �� ����"), UMBS_OK, UI_NONE, MSGCMD_RAID_INFO);

			if(nRaidCount > 0)
			{
				for( i = 0; i < nRaidCount; i++ )
				{
					(*istr) >> nZoneNum;
					(*istr) >> nRoomNum;

					strMessage.PrintF(_S(4755, "�ͼӵ� ���̵� �� �̸� : %s"),CZoneInfo::getSingleton()->GetZoneName(nZoneNum));
					MsgBoxInfo.AddString(strMessage);
					strMessage.PrintF(_S(4756, "�ͼӵ� ���̵� �� ID : %d"), nRoomNum);
					MsgBoxInfo.AddString(strMessage);
				}
			}
			else
			{
				MsgBoxInfo.AddString(_S(4757, "�ͼӵ� ���� �����ϴ�."));
			}

			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;	
		
	case MSG_EX_TAKE_AGAIN_QUEST_ITEM:
		{
			ReceiveTakeAgainQuestItem( istr);						
		}
		break;
	case MSG_EX_COSTUME2:
		{
			UCHAR ucType;
			(*istr) >> ucType;
			if ( ucType == MSG_EX_COSTUME2_SYSTEM_ERROR )
			{
				RecieveCostume2Message( istr );
			}
			else if ( ucType == MSG_EX_COSTUEM2_WEARING )
			{
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->WearingCostumeArmor( istr );
			}
			// added by sam 11/02/01 [SAM]
			else if ( ucType == MSG_EX_COSTUME2_WEARING_SUIT )
			{
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->WearingCostumeArmorOneSuit( istr );
			}
			else if ( ucType == MSG_EX_COSTUME2_PREINVENINFO )
			{
				SBYTE	wear_type;	
				INDEX	uni_index;
				INDEX	item_index;
				CEntity			*penPlEntity;
				CPlayerEntity	*penPlayerEntity;

				penPlEntity = CEntity::GetPlayerEntity(0);		// ĳ���� �ڱ� �ڽ�
				penPlayerEntity = static_cast<CPlayerEntity *>(penPlEntity);
				
				CModelInstance *pMI	= penPlayerEntity->GetModelInstance();

				if( _pNetwork->MyCharacterInfo.bPetRide || _pNetwork->MyCharacterInfo.bWildPetRide)
				{
					CModelInstance *pMITemp = penPlayerEntity->GetModelInstance();
					
					INDEX ctmi = pMITemp->mi_cmiChildren.Count();
					if( ctmi > 0 )
					{
						pMI = &pMITemp->mi_cmiChildren[0];
					}
					else
					{
						pMI	= penPlayerEntity->GetModelInstance();
					}
				}
				
				for (int i=0; i<WEAR_COSTUME_TOTAL; ++i)
				{
					(*istr) >> wear_type; // 0 ~ 6, 11
					(*istr) >> uni_index;
					(*istr) >> item_index;
					
					if ( item_index >= 0 )
					{	// �ڽ�Ƭ �Ա�
						_pNetwork->MyWearCostItem[i].Item_Index = item_index;
						_pNetwork->MyWearCostItem[i].Item_UniIndex = uni_index;
						
						// BUGFIX : ITS(#0002472) �ڽ�Ƭ 2 ���� �� ���� -> ���̵��� �� ���� ���� ����. [6/9/2011 rumist]
						if( _pNetwork->MyCharacterInfo.nEvocationIndex == 0 )
						{
							if ( !( wear_type == WEAR_HELMET && (CTString)_pNetwork->GetItemData(item_index)->GetItemSmcFileName() == MODEL_TREASURE) )
							{
								((CPlayerEntity*)CEntity::GetPlayerEntity(0))->DeleteDefaultArmor(wear_type);
								_pGameState->WearingArmor(pMI, *_pNetwork->GetItemData(item_index));
							}
							if(!((static_cast<CPlayerEntity*>(CEntity::GetPlayerEntity(0)))->IsSitting() && _pNetwork->MyCharacterInfo.job == NIGHTSHADOW))
								_pNetwork->MyCharacterInfo.itemEffect.Change(_pNetwork->MyCharacterInfo.job, _pNetwork->GetItemData(item_index), wear_type,
								0, &pMI->m_tmSkaTagManager, 1, _pNetwork->GetItemData(item_index)->GetSubType());
						}
					}
				}
			}
		}
		break;
	case MSG_EX_DUNGEONTIME:
		{
			UCHAR ucType;
			SLONG slStart, slEnd, slAddExp;
			CTString strMessage;
			(*istr) >> ucType;

			if (ucType == MSG_EX_DUNGEONTIME_NOTICE)
			{
				(*istr) >> slStart >> slEnd >> slAddExp;
				strMessage.PrintF(_S(4956, "���� Ÿ���� ���۵Ǿ����ϴ�. (%d�� ~ %d��, ���� ����ġ %d%%�߰� ȹ��)"), slStart, slEnd, slAddExp);
				_UIAutoHelp->SetGMNotice(strMessage);
				pUIManager->GetSimplePlayerInfo()->StartDungeonTime();
				pUIManager->GetSimplePlayerInfo()->SetDungeonList(slAddExp);
			}
			else if (ucType == MSG_EX_DUNGEONTIME_START)
			{
				(*istr) >> slStart >> slEnd >> slAddExp;
			//TO.DO ���� Ÿ��
				strMessage.PrintF(_S(4957, "���� Ÿ���� ���� ���Դϴ�. (%d�� ~ %d��, ���� ����ġ %d%%�߰� ȹ��)"), slStart, slEnd, slAddExp);
				_UIAutoHelp->SetGMNotice(strMessage);
				pUIManager->GetSimplePlayerInfo()->StartDungeonTime();
				pUIManager->GetSimplePlayerInfo()->SetDungeonList(slAddExp);
			}
			else if (ucType == MSG_EX_DUNGEONTIME_END)
			{
				_UIAutoHelp->SetGMNotice( _S(4958, "����Ÿ���� ���� �Ǿ����ϴ�.") );
				pUIManager->GetSimplePlayerInfo()->StopDungeonTime();
				pUIManager->GetSimplePlayerInfo()->SetDungeonList(0);
			}
		}
		break;
	case MSG_EX_SOCKET:
		{
			RecieveSocketSystemMessage( istr );
		}
		break;
#ifdef XTRAP_SECURE_CKBANG_2010_07_20
    case MSG_EX_XTRAP:
        {
            if (g_pXTrap_CS_Step2Func)
            {
                CNetworkMessage nmMessageTest(MSG_EXTEND);
                #define XTRAP_CMD_STEP_TWO  0x002
                nmMessageTest << (ULONG)MSG_EX_XTRAP;
                nmMessageTest << (BYTE)XTRAP_CMD_STEP_TWO;
                char szBuf[128] , szSendBuf[128];
                
				istr->Read(szBuf, 128);
#ifdef XTRAP_LOG_ENABLE
				g_pHexaDump4XTrap_V1("TestXtrapLog.txt", szBuf, 128, "XTrap_stap1_RecBufData");
#endif
                g_pXTrap_CS_Step2Func(szBuf, szSendBuf);

                nmMessageTest.Write(szSendBuf , 128 );
#ifdef XTRAP_LOG_ENABLE
				g_pHexaDump4XTrap_V1("TestXtrapLog.txt", szSendBuf, 128, "XTrap_stap2_SendBufData");
#endif
                _pNetwork->SendToServerNew( nmMessageTest );
            }
        }
        break;
#endif
		case MSG_EX_TUTORIAL_RENEWER_2010:
		{
			pUIManager->GetHelp()->RepBeginnerTitle( istr );
		}
		break;
	case MSG_EX_RAID_SCENE: // ��ĭ��� ���̵�
		{
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ReceiveRaidScene(istr);
		}
		break;

	case MSG_EX_CASTLLAN:
		{
			(*istr) >> errcode;
			if ( errcode == MSG_EX_CASTLLAN_ERROR )
			{
				RecieveLordCostumeMessage( istr );
			}
		}
		break;

	case MSG_EX_SUBJOB:	// [2010/08/25 : Sora] ADD_SUBJOB ���� ���� �޽���
		{
			RecieveSubJobMessage(istr);
		}
		break;
	case MSG_EX_RANKING_SYSTEM_EX:		// ��ŷ �ý��� ���� [trylord : 110825]
		{
			RecieveRankingListExMessage(istr);
		}
	// [2010/10/20 : Sora] ���� �뺴 ī��
	case MSG_EX_MONSTER_MERCENARY:
		{
			RecieveMonsterMercenaryCardMessage( istr );
		}
		break;
	case MSG_EX_FACEOFF:
		{
			(*istr) >> errcode;
			if ( errcode == MSG_EX_FACEOFF_REP )
			{
				RecieveFaceOffMessage( istr );
			}
		}
		break;
	case MSG_EX_LUCKYDRAW_BOX:
		{
			RecieveLuckyDrawBoxMessage( istr );
		}
		break;
		// �޽��� �ڽ� ��� �޽��� �߰� added by sam 11/01/04
	case MSG_EX_MSGBOX:
		{	
			RecieveMsgBoxShow( istr );					
		}
		break;

	case MSG_EX_LCBALL:
		{
			pUIManager->GetLacaBall()->ReceiveLcBallMessage( istr );
		}
		break;
	// royal rumble [4/19/2011 rumist]
	case MSG_EX_ROYAL_RUMBLE:
		{
			RecieveRoyalrumbleMessage( istr );
		}
		break;
	case MSG_EX_CASH_AUTHENTICATION_CODE:
		{
			CTString strUserID;
			CTString strCode;
			UBYTE nGrupID,nAuthCode;
			(*istr) >> nAuthCode;
			

			if (nAuthCode)
			{
				(*istr) >> strUserID;
				(*istr) >> nGrupID;
				(*istr) >> strCode;

				CTString temURL;
				extern ENGINE_API INDEX sam_bFullScreenActive;				
				
				if ( IsFullScreen( sam_bFullScreenActive))
				{												 
					 pUIManager->GetOption()->ChangeWindowMode();
					 pUIManager->DestroyRenderTarget();
					 pUIManager->InitRenderTarget();
				}
				
				temURL.PrintF("http://shop.gamigo.com/game_%d/login/user/%s/hash/%s/", nGrupID, strUserID, strCode);
				ShellExecute( NULL, "open", temURL, NULL,NULL, SW_SHOWNORMAL );
			}else
			{
				MsgBoxInfo.SetMsgBoxInfo( _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
				MsgBoxInfo.AddString( _S( 3257, "��û�� �۾��� ���� �Ͽ����ϴ�." ) );
				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
			
		}break;
	case MSG_EX_TREASURE_MAP_SYSTEM_KEY_EXCHANGE:
		{
			UBYTE ubErrorcode;
			(*istr) >> ubErrorcode;
			
			if (ubErrorcode == MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_SUC) // ����
			{
				MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL );
				MsgBoxInfo.AddString( _S( 159, "��ȯ�� ���������� �̷�������ϴ�." ) );
				pUIManager->CreateMessageBox( MsgBoxInfo );

			}else if (ubErrorcode == MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_FAIL) 
			{
				MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL );
				MsgBoxInfo.AddString( _S( 3257, "��û�� �۾��� ���� �Ͽ����ϴ�." ) );
				pUIManager->CreateMessageBox( MsgBoxInfo );

			}else if (ubErrorcode == MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_ITEM) 
			{
				MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL );
				MsgBoxInfo.AddString( _S( 5099, "��ȯ ������ �������� �����ϴ�" ) );
				pUIManager->CreateMessageBox( MsgBoxInfo );

			}else if (ubErrorcode == MSG_EX_TRS_MAP_KEY_EXCHANGE_ERROR_COUNT) 
			{
				MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL );
				MsgBoxInfo.AddString( _S( 5100, "��ȯ ������ �������� �����մϴ�" ) );
				pUIManager->CreateMessageBox( MsgBoxInfo );

			}

		}break;
	case MSG_EX_PKPENALTY_REFORM:
		{
			UBYTE ubinx;
			CTString strSysMessage;
			CUIMsgBox_Info	MsgBoxInfo;

			(*istr) >> ubinx;
			if(ubinx == MSG_EX_PKPENALTY_REFORM_REWARD_INFO)
			{
				ULONG pkSysRewardFlag;
				(*istr) >> pkSysRewardFlag;
				_pNetwork->MyCharacterInfo.pkSysRewardFlag = pkSysRewardFlag;
				_pNetwork->MyCharacterInfo.bpkSysRewardLate= FALSE;
			}
			else if(ubinx == MSG_EX_PKPENALTY_REFORM_REWARD_REP)
			{
				INDEX pkSysRewardFlag;
				UBYTE errcode;
				(*istr) >> pkSysRewardFlag;
				(*istr) >> errcode;
				switch(errcode)
				{
				case MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_SUC:
					_pNetwork->MyCharacterInfo.bpkSysRewardLate= FALSE;
					break;
				case MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_COUNT:
					strSysMessage = _S(2237, "���޹��� ������ �����մϴ�.");
					break;
				case MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_ONCE:
					//strSysMessage = _S(4827, "�̹� ��ϵǾ� �ִ� ȣĪ�Դϴ�.");
				    break;
				case MSG_EX_PKPENALTY_REFORM_REWARD_ERROR_FAIL:
					strSysMessage = _S(1745, "������ ���� �ʽ��ϴ�.");
				    break;
				default:
				    break;
				}
				
			}
			if (strSysMessage != CTString(""))
			{
				MsgBoxInfo.SetMsgBoxInfo(strTitle,UMBS_OK,UI_NONE,MSGCMD_NULL);
				MsgBoxInfo.AddString(strSysMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
		}break;

	case MSG_EX_SHUTDOWN:
		{
			UCHAR type;
			SLONG arg;
			CTString strMessage;
			(*istr) >> type;
			(*istr) >> arg;
			
			switch( type )
			{
				case MSG_EX_SHUTDOWN_REMAIN:
					{
						strMessage.PrintF( _s("Shut Down �ð����� %d�� ���ҽ��ϴ�."), arg );
						pUIManager->GetChattingUI()->AddSysMessage( strMessage, SYSMSG_USER, 0xFFFF00FF );
					}
					break;
				case MSG_EX_SHUTDOWN_COUNTDOWN:
					{
						strMessage.PrintF( _s("Shut Down ���۱��� %d�� ���ҽ��ϴ�. �ش�ǽô� ���� �е��� ĳ���͸� ������ �������� �Ű��ֽñ� �ٶ��ϴ�."), arg );
						pUIManager->GetChattingUI()->AddSysMessage( strMessage, SYSMSG_USER, 0xFFFF00FF );
					}
					break;
				case MSG_EX_SHUTDOWN_START:
					{
						strMessage.PrintF( _s("Shut Down�� ���� �Ǿ����ϴ�.") );
						pUIManager->GetChattingUI()->AddSysMessage( strMessage, SYSMSG_USER, 0xFFFF00FF );
					}
					break;
				case MSG_EX_SHUTDOWN_END:
					{
						strMessage.PrintF( _s("Shut Down�� ���� �Ǿ����ϴ�.") );
						pUIManager->GetChattingUI()->AddSysMessage( strMessage, SYSMSG_USER, 0xFFFF00FF );
					}
					break;
				case MSG_EX_SHUTDOWN_DISCONNECT:
					{
						CUIMsgBox_Info	MsgBoxInfo;
						
						strMessage.PrintF( _s("�˴ٿ��� ���۵Ǿ����ϴ�. �˴ٿ� ���� �ð� ���Ŀ� �ٽ� �������ּ���. Ȯ���� ���� Ŭ���̾�Ʈ�� �����Ͻñ� �ٶ��ϴ�. (�˴ٿ� ����ð� : 24:00-06:00)") );
						MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_DISCONNECT );
						MsgBoxInfo.AddString( strMessage );
						pUIManager->CreateMessageBox(MsgBoxInfo);
					}
					break;
			}

		}break;
#ifdef	IMPROV1107_NOTICESYSTEM
	case MSG_EX_USER_NOTICE:
		{
			LONG	retCode;

			(*istr) >> retCode;
			switch(retCode)
			{
			case MSG_EX_USER_NOTICE_REG_REP:		// ����
				{
					pUIManager->GetChattingUI()->AddSysMessage(_S( 5611 ,"���������� ��ϵǾ����ϴ�."), SYSMSG_NORMAL);
				}
				break;

			case MSG_EX_USER_NOTICE_PRINT:
				{
					CTString	strName;
					CTString	strMessage;

					(*istr) >> strName;
					(*istr) >> strMessage;
					pUIManager->GetChattingUI()->AddUserNotice(strName, strMessage);
				}
				break;

			case MSG_EX_USER_NOTICE_ERROR:
				{
					LONG		errcode;
					CTString	strSysMessage;

					(*istr) >> errcode;
					if(errcode == MSG_EX_USER_NOTICE_ERROR_NOITEM)
					{
						strSysMessage	= _S( 1330 ,"�������� �����մϴ�." );
					}
					else if(errcode == MSG_EX_USER_NOTICE_ERROR_LENGTH)
					{
						strSysMessage	= _S( 5609 ,"������ ������ �Է��ϼ���." );
					}

					if (strSysMessage.Length() > 0)
					{
						MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL );
						MsgBoxInfo.AddString(strSysMessage);
						pUIManager->CreateMessageBox( MsgBoxInfo );
					}

				}
				break;
			}
		}
		break;
#endif	// #ifdef	IMPROV1107_NOTICESYSTEM

//////////////////////////////////////////////////////////////////////////
// �̺�Ʈ �ý��� ����
//////////////////////////////////////////////////////////////////////////
	case MSG_EX_EVENT_AUTOMATION_SYSTEM:
		{
			extern ENGINE_API std::map<int,int> g_mapEvent;

			UCHAR type;
			SLONG nEventIndex;
			(*istr) >> type;

			switch( type )
			{
			case MSG_EX_EVENT_AUTOMATION_LIST:
				{
					SLONG nCount;
					(*istr) >> nCount;

					for( int i=0; i<nCount; i++ )
					{
						(*istr) >> nEventIndex;
						g_mapEvent[nEventIndex] = 1;
					}

					CheckTimerEvent();
				}
				break;
			case MSG_EX_EVENT_AUTOMATION_ADD:
				(*istr) >> nEventIndex;
				g_mapEvent[nEventIndex] = 1;

				CheckTimerEvent();
				break;
			case MSG_EX_EVENT_AUTOMATION_REMOVE:
				(*istr) >> nEventIndex;
				g_mapEvent.erase(nEventIndex);

				CheckTimerEvent();
				break;
			}
		}
		break;
	case MSG_EX_JUMPING_SYSTEM:
		{
			UCHAR type;
			CTString	strSysMessage;
			INDEX nJumpingLevel;

			(*istr) >> type;

			switch( type )
			{
			case MSG_EX_JUMPING_SUCCESS:
				{
					strSysMessage.PrintF(_S(5689, "���������� ���� �Ǿ����ϴ�."));
				}break;
			case MSG_EX_JUMPING_ERROR_LEVEL:
				{
					strSysMessage.PrintF(_S(5685, "������ ���� �ʾ� ����Ͻ� �� �����ϴ�."));
				}break;
			case MSG_EX_JUMPING_ERROR_NOT_EXIST_CHAR:
				{
					(*istr) >> nJumpingLevel;
					strSysMessage.PrintF(_S(5690, "�ش� ���� Ȥ�� �ش� ���� ���� %d ���� �̻��� ĳ���Ͱ� �������� �ʽ��ϴ�."), nJumpingLevel);
				}break;
			}

			MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL );
			MsgBoxInfo.AddString(strSysMessage);
			pUIManager->CreateMessageBox( MsgBoxInfo );

		}break;

	//REFORM_SYSTEM
	case MSG_EX_REFORMER_SYSTEM:
		{
			pUIManager->GetReformSystem()->RecvReformSystemResult(istr);
		}break;

	case MSG_EX_SERVER_TIME:
		{
			(*istr) >> nServerTime;

			_pNetwork->slServerTime = nServerTime;
			_pNetwork->slServerTimeGap = (SLONG)time(NULL) - nServerTime;
		}break;
	}
}

void CSessionState::ReceiveExWildPetMessage(UBYTE index, CNetworkMessage *istr)
{	
//	CEntity* penPlEntity;
	CPlayerEntity* penPlayerEntity;
// 	penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
// 	penPlayerEntity = (CPlayerEntity*) penPlEntity;
	
	penPlayerEntity = static_cast<CPlayerEntity*>( CEntity::GetPlayerEntity(0) );

	CUIManager* pUIManager = CUIManager::getSingleton();
	ObjInfo* pInfo = ObjInfo::getSingleton();

	switch(index)	
	{
	case MSG_SUB_ITEM_WEAR:
		{
			SBYTE wear_pos;
			INDEX wear_item,takeoff_item;

			(*istr) >> wear_pos;
			(*istr) >> wear_item;
			(*istr) >> takeoff_item;

			// �� ���� ������ ���� ����̴�.
			if (pInfo->GetMyApetInfo() == NULL)
				return;

			CWildPetTarget* pTarget = pInfo->GetMyApetInfo();
			
			if (pTarget->bIsActive == FALSE)
			{
				break;
			}

			if(pTarget->m_nPetWearIndex[wear_pos] == takeoff_item)
			{
				if (pTarget->GetEntity() != NULL)
					_pGameState->TakeOffArmorTest(pTarget->GetEntity()->GetModelInstance(), takeoff_item);
				
				pTarget->m_nPetWearIndex[wear_pos] = -1;
			}

			if (pTarget->m_nPetWearIndex[wear_pos] > 0)
			{
				if (pTarget->GetEntity() != NULL)
					_pGameState->TakeOffArmorTest(pTarget->GetEntity()->GetModelInstance(), pTarget->m_nPetWearIndex[wear_pos]);
			}			
						
			pTarget->m_nPetWearIndex[wear_pos] = wear_item;

			if (pTarget->GetEntity() != NULL)
				_pGameState->WearingArmorTest(pTarget->GetEntity()->GetModelInstance(), wear_item);
			
			pUIManager->GetWildPetInfoUI()->PetWearItemReSet();
			pUIManager->GetWildPetInfoUI()->updateBaseTab();
		}
		break;
	case MSG_SUB_ITEM_WEARING:
		{
			INDEX OwenerIndex,petID;
			INDEX wearIndex[WILDPET_WEAR_TOTAL] = {0,};
			INDEX wearPlus[WILDPET_WEAR_TOTAL] = {0,};

			(*istr) >> OwenerIndex;
			(*istr) >> petID;

			for (int i = 0; i < WILDPET_WEAR_TOTAL; i++)
			{
				(*istr) >> wearIndex[i];
				(*istr) >> wearPlus[i];
			}

			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_WILDPET, petID);

			if (pObject != NULL)
			{
				CWildPetTarget* pTarget = static_cast< CWildPetTarget* >(pObject);

				for (int i = 0; i < WILDPET_WEAR_TOTAL; i++)
				{
					if (pTarget->GetEntity() != NULL)
						_pGameState->TakeOffArmorTest(pTarget->GetEntity()->GetModelInstance(), pTarget->m_nPetWearIndex[i]);

					pTarget->m_nPetWearIndex[i] = wearIndex[i];
					pTarget->m_nPetWearPlus[i] = wearPlus[i];

					if (pTarget->GetEntity() != NULL)
						_pGameState->WearingArmorTest(pTarget->GetEntity()->GetModelInstance(), pTarget->m_nPetWearIndex[i]);
				}

				// �� �������� (&_WildPetInfo != &_pNetwork->ga_srvServer.srv_actWildPet)
				if (pTarget->m_nOwnerIndex == _pNetwork->MyCharacterInfo.index)
				{
					pInfo->SetMyApet(pTarget);
					pUIManager->GetWildPetInfoUI()->PetWearItemReSet();
					pUIManager->GetWildPetInfoUI()->updateBaseTab();
				}
			}
		}
		break;

	case MSG_SUB_SKILLLEAN:
		{
			CTString	strMessage;
			UBYTE code;
			(*istr) >> code;

			switch(code)
			{
			case 0:
				{	LONG nSkillIndex;
					UBYTE nSkillLevel;
				
					(*istr) >> nSkillIndex;
					(*istr) >> nSkillLevel;
					
					pUIManager->GetPetTrainingUI()->LearnSkill( 0, nSkillIndex, nSkillLevel );

					CSkill		&rSkill = _pNetwork->GetSkillData( nSkillIndex );
					strMessage.PrintF( _S( 277, "%s ��ų�� �����Ͽ����ϴ�" ), rSkill.GetName() );

				}break;
			case 1:
				{
					//���� �� ����
					strMessage = _S(2203, "�ֿϵ����� �������� �ʾ� ��ų�� ������ �� �����ϴ�." );
				}break;
			case 2:
				{
					//������ �ƴ�
					strMessage = _S( 278, "������ �����Ͽ� ��ų�� ������ �� �����ϴ�." );
				}break;
			case 3:
				{
					//��ų ����
					strMessage = _S( 281, "��ų ������ ���� �ʾ� ��ų�� ������ �� �����ϴ�." );
				}break;
			case 4:
				{
					//�ʿ� ������ ����
					strMessage = _S( 280, "�������� �������� �ʾ� ��ų�� ������ �� �����ϴ�." );
				}break;
			case 5:
				{
					//�ʿ� ������ ����
					strMessage = _S(4214, "�ʿ� �������� �������� ��ų�� ������ �� �����ϴ�. ");
					
				}break;

			}
			// Close message box of skill learn
		pUIManager->CloseMessageBox( MSGCMD_PETTRAINING_NOTIFY );

		// Create message box of skill learn
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo( _S( 270, "��ų" ), UMBS_OK,
									UI_PET_TRAINING, MSGCMD_PETTRAINING_NOTIFY );
		MsgBoxInfo.AddString( strMessage );
		pUIManager->CreateMessageBox( MsgBoxInfo );


		}break;
	case MSG_SUB_SKILLLIST:
		{
			INDEX nSkillCont;
			INDEX nSkillIndex;
			UBYTE nSkillLevel;
			int nSkillTime;
			(*istr) >> nSkillCont;
			
			pUIManager->GetWildPetInfoUI()->SkillClear();
			
			for(int con = 0; con < nSkillCont; con++)
			{
				(*istr) >> nSkillIndex;
				(*istr) >> nSkillLevel;
				(*istr) >> nSkillTime;

				pUIManager->GetPetTrainingUI()->LearnSkill(0, nSkillIndex, nSkillLevel, FALSE, false);

				CSkill& rSkill = _pNetwork->GetSkillData(nSkillIndex);
				if ( nSkillTime <= 0 )
				{
					rSkill.ResetStartTime();
					continue;
				}
				SLONG slRemainTime = ((SLONG)time(NULL) - _pNetwork->slServerTimeGap) - nSkillTime; 

				if ( slRemainTime > 0 )
					rSkill.SetStartTime(slRemainTime);
			}

		}break;
	case MSG_SUB_REBIRTH:
		{
			CTString	strMessage;
			CUIMsgBox_Info	MsgBoxInfo;
			UBYTE code;
			(*istr) >> code;
			switch(code)
			{
			case 0:
				{
					pUIManager->GetPetFree()->closeUI(); //����
					MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_PETFREE, UI_NONE );
					strMessage.PrintF( _S( 2450, "���� ������ �����ϴµ� �����Ͽ����ϴ�.") );
					MsgBoxInfo.AddString( strMessage );
					pUIManager->CreateMessageBox( MsgBoxInfo );
				}break;
			case 1:
				{
					//�˸��� ���� ������
					pUIManager->GetChattingUI()->AddSysMessage( 
						_S( 2452, "������ ������ ���� �������� �ʽ��ϴ�." ), SYSMSG_ERROR );
					pUIManager->GetPetFree()->ResetUI();
				}break;
			case 2:
				{
					//������ ���ڶ�
					pUIManager->GetChattingUI()->AddSysMessage( 
						_S( 2451, "���� ������ �����ϱ� ���� ����� �����մϴ�." ), SYSMSG_ERROR );
				}break;
			case 3:
				{
					//���ε��� ���� ������
					pUIManager->GetChattingUI()->AddSysMessage( 
						_S( 2452, "������ ������ ���� �������� �ʽ��ϴ�." ), SYSMSG_ERROR );
					pUIManager->GetPetFree()->ResetUI();
				}break;
			}
		}break;
	case MSG_SUB_LEVELUP:
		{
			pUIManager->GetChattingUI()->AddSysMessage( 
						_S( 2253, "���� ������ �Ͽ����ϴ�." ), SYSMSG_NORMAL );
			
			if (pInfo->GetMyApetInfo() != NULL)
				WildPetStartEffectGroup("pet_levelup", pInfo->GetMyApetInfo()->m_nIdxServer, pInfo->GetMyApetInfo()->m_pEntity);

		}break;
	case MSG_SUB_DELETE_EQUIP:
		{
			pUIManager->GetWildPetInfoUI()->ReceiveDeleteEquip(istr);
		}break;

	case MSG_SUB_ADDITEM_MSG: // �̰� ���� ���� �� ������ ������ ���ؼ� UI Update�� �Ǿ�� �Ѵ�.
		{
			pUIManager->GetWildPetInfoUI()->ReceiveWearItemData(istr);	
		}break;

	case MSG_SUB_AI_LIST_NTF:
		{
			INDEX nPetAICount;
			INDEX nAIMaxCount;
			INDEX nSlotnum;
			UBYTE bActive;
			sWildPet_AI_Slot temAI;

			pUIManager->GetWildPetInfoUI()->AIClear();

			(*istr) >> nAIMaxCount;

			pUIManager->GetWildPetInfoUI()->SetPetAISlotCount(nAIMaxCount);

			(*istr) >> nPetAICount;

			for (int ncnt = 0; ncnt < nPetAICount; ncnt++)
			{
				(*istr) >> nSlotnum;
				(*istr)	>> temAI.m_nTargetSlot;
				(*istr)	>> temAI.m_nActionSlot;
				(*istr)	>> temAI.m_nSillType;
				(*istr)	>> bActive;

				temAI.m_bActive = bActive;

				pUIManager->GetWildPetInfoUI()->AddAIData(nSlotnum, temAI);

			}

			pUIManager->GetWildPetInfoUI()->PetAIReSet();
			pUIManager->GetWildPetInfoUI()->CloseAISetUI();

		}break;
	case MSG_SUB_AI_UPDATE_REP:
		{
			UBYTE ubErrorcode;
			(*istr) >> ubErrorcode;

			pUIManager->GetWildPetInfoUI()->ErrorMessage(ubErrorcode);

		}break;
	case MSG_SUB_AI_ONOFF_REP:
		{
			UBYTE bActive;
			UBYTE ubErrorCode;

			(*istr) >> bActive;
			(*istr) >> ubErrorCode;

			pUIManager->GetWildPetInfoUI()->SetPetAIActive(bActive);
			pUIManager->GetWildPetInfoUI()->ErrorMessage(ubErrorCode);			

		}break;
	case MSG_SUB_EVOLUTION: // ���� ���� �� ���� �޼��� ó��
		{
			UBYTE ubErrorCode;

			(*istr) >> ubErrorCode;

			pUIManager->GetPetTrainingUI()->EvolutionError(ubErrorCode);
		}break;
	case MSG_SUB_MOUNT_REP:
		{
			UBYTE ubErrorCode;	// 0: ����, 1: ����

			(*istr) >> ubErrorCode;

			pUIManager->SetCSFlagOff(CSF_PETRIDING);
		}
		break;
	case MSG_SUB_SUMMON_ERROR:
		{
			UBYTE ubErrorCode;
			CTString strMessage;

			(*istr) >> ubErrorCode;

			strMessage.PrintF( _S(5212, "��ȯ���ɽð� %d�� ���ҽ��ϴ�." ), ubErrorCode );						
			pUIManager->GetChattingUI()->AddSysMessage( strMessage, SYSMSG_ERROR );
		}break;
		// cash item �߰� : p2��. [1/19/2011 rumist]
	case MSG_SUB_STATINIT:
		{
			UBYTE ubErrorCode;
			CTString strMessage;
			CUIMsgBox_Info MsgBoxInfo;
			(*istr) >> ubErrorCode;
			
			MsgBoxInfo.SetMsgBoxInfo( _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
			switch( ubErrorCode )
			{
				case 0:
					MsgBoxInfo.AddString( _S( 5322, "�ɷ�ġ �ʱ�ȭ�� �Ϸ� �Ǿ����ϴ�." ) );
				break;
				case 1:
					MsgBoxInfo.AddString( _S( 2189,"�ֿϵ����� ���Կ� �����Ͽ��߸� �մϴ�.") );
				break;
				case 2:
					MsgBoxInfo.AddString( _S( 2444, "�� ���� ����." ) );
				break;
				case 3:
					MsgBoxInfo.AddString( _S( 5320, "�ʱ�ȭ �� ����Ʈ�� �������� �ʽ��ϴ�." ) );
				break;
			}
			
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}break;
	case MSG_SUB_EXPUSE:
		{
			UBYTE ubErrorCode;
			CTString strMessage;
			CUIMsgBox_Info MsgBoxInfo;
			(*istr) >> ubErrorCode;

			MsgBoxInfo.SetMsgBoxInfo( _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
			switch( ubErrorCode )
			{
			case 0:
				MsgBoxInfo.AddString( _S( 5651, "������ ����ġ�� ���������� ����Ǿ����ϴ�." ) );
				break;
			case 1:
				MsgBoxInfo.AddString( _S( 5673,"���� �� ����ġ�� ��� �� �� ���� ���� �Դϴ�.") );
				break;
			case 2:
				MsgBoxInfo.AddString( _S( 4981, "�������� �������̰ų�, �ùٸ� �������� �ƴմϴ�. Ȯ�� �� �ٽ� �õ��� �ֽñ� �ٶ��ϴ�." ) );
				break;
			case 3:
				MsgBoxInfo.AddString( _S( 2445, "�� �����۸� �����մϴ�." ) );
				break;
			}
			pUIManager->CreateMessageBox( MsgBoxInfo );

		}break;
	case MSG_SUB_ERROR_NOT_EXIST_NPC:
		{
			CTString strMessage;
			strMessage.PrintF( _S( 5913, "���డ���� NPC�� ������ �������� �ʽ��ϴ�.") );
			_pNetwork->ClientSystemMessage(strMessage, SYSMSG_ERROR);
		}
		break;
	case MSG_SUB_INIT_COOLTIME:
		{
			UBYTE ubErrorCode;
			CTString strMessage;
			CUIMsgBox_Info MsgBoxInfo;
			(*istr) >> ubErrorCode;

			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

			switch(ubErrorCode)
			{
			case 0:
				MsgBoxInfo.AddString(_S(6288, "���� ���� ����ġ ���� ��Ÿ���� �����Ǿ� ����ġ ������ ���۵˴ϴ�."));
				break;
			case 1:
			case 2:
				MsgBoxInfo.AddString(_S(6289, "��Ÿ���� �����ϰ��� �ϴ� ����ġ ���� �����Ͽ� �ֽñ� �ٶ��ϴ�."));
				break;
			default:
				return;
			}

			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
		break;
	case MSG_SUB_DELETE_ITEM:
		{
			UBYTE	error;
			ULONG	wearpos;
			(*istr) >> error;
			(*istr) >> wearpos;

			pUIManager->GetWildPetInfoUI()->DeleteEquip(wearpos);
		}
		break;
	}
}

// ----------------------------------------------------------------------------
// Name : ReceivePetStatusMessage()
// Desc : �ֿϵ��� ����.
// ----------------------------------------------------------------------------
void CSessionState::ReceivePetStatusMessage( CNetworkMessage *istr )
{
	// �ֿϵ��� ����	: index(n) petTypeGrade(c) level(n) exp(ll) needexp(ll) hp(n) maxhp(n) hungry(n) maxhugry(n) sympathy(n) maxsympathy(n) x(f) z(f) h(f) r(f) y(c) mapatt(uc)
	LONG		lIndex;
	SBYTE		sbPetTypeGrade;
	LONG		lLevel;
	__int64		llExp;
	__int64		llNeedExp;
	LONG		lHP;
	LONG		lMaxHP;
	LONG		lAbility;
	LONG		lHungry;
	LONG		lMaxHungry;
	LONG		lSympathy;
	LONG		lMaxSympathy;
	FLOAT		fX;
	FLOAT		fZ;
	FLOAT		fH;
	FLOAT		fR;	
	SBYTE		sbYLayer;
	UWORD		sbMapAttribute;
	LONG		remainRebirth;
	CTString	strNameCard;

	(*istr) >> lIndex;
	(*istr) >> sbPetTypeGrade;
	(*istr) >> lLevel;
	(*istr) >> llExp;
	(*istr) >> llNeedExp;
	(*istr) >> lHP;
	(*istr) >> lMaxHP;
	(*istr) >> lAbility;
	(*istr) >> lHungry;
	(*istr) >> lMaxHungry;
	(*istr) >> lSympathy;
	(*istr) >> lMaxSympathy;
	(*istr) >> fX;
	(*istr) >> fZ;
	(*istr) >> fH;
	(*istr) >> fR;
	(*istr) >> sbYLayer;
	(*istr) >> sbMapAttribute;
#ifdef PET_SEAL_TIME
	(*istr) >> remainRebirth;
#endif

	(*istr) >> strNameCard;

	CNetworkLibrary::sPetInfo	TempPet;
	TempPet.lIndex				= lIndex;
	TempPet.sbPetTypeGrade		= sbPetTypeGrade;
	TempPet.lLevel				= lLevel;
	TempPet.llExp				= llExp;
	TempPet.llNeedExp			= llNeedExp;
	TempPet.lHP					= lHP;
	TempPet.lMaxHP				= lMaxHP;
	TempPet.lAbility			= lAbility;
	TempPet.lHungry				= lHungry;
	TempPet.lMaxHungry			= lMaxHungry;
	TempPet.lSympathy			= lSympathy;
	TempPet.lMaxSympathy		= lMaxSympathy;
	TempPet.fX					= fX;
	TempPet.fZ					= fZ;
	TempPet.fH					= fH;
	TempPet.fR					= fR;	
	TempPet.sbMapAttribute		= sbMapAttribute;
#ifdef PET_SEAL_TIME
	TempPet.lRemainRebirth		= remainRebirth;
#endif
	TempPet.strNameCard			= strNameCard;

	std::vector<CNetworkLibrary::sPetInfo>::iterator iter = 
		std::find_if(_pNetwork->m_vectorPetList.begin(), _pNetwork->m_vectorPetList.end(), CNetworkLibrary::FindPet(TempPet) );
	
	// �� ������ �� ã���� �߰���.
	if( iter == _pNetwork->m_vectorPetList.end() )
	{
		_pNetwork->m_vectorPetList.push_back(TempPet);
	}	
	// �� ������ ������.
	else
	{		
		(*iter).sbPetTypeGrade	= TempPet.sbPetTypeGrade;
		(*iter).lLevel			= TempPet.lLevel;
		(*iter).llExp			= TempPet.llExp;
		(*iter).llNeedExp		= TempPet.llNeedExp;
		(*iter).lHP				= TempPet.lHP;
		(*iter).lMaxHP			= TempPet.lMaxHP;
		(*iter).lHungry			= TempPet.lHungry;
		(*iter).lMaxHungry		= TempPet.lMaxHungry;
		(*iter).lSympathy		= TempPet.lSympathy;
		(*iter).lMaxSympathy	= TempPet.lMaxSympathy;
		(*iter).fX				= TempPet.fX;
		(*iter).fZ				= TempPet.fZ;
		(*iter).fH				= TempPet.fH;
		(*iter).fR				= TempPet.fR;		
		(*iter).sbMapAttribute	= TempPet.sbMapAttribute;
		(*iter).lAbility		= TempPet.lAbility;
#ifdef PET_SEAL_TIME
		(*iter).lRemainRebirth	= TempPet.lRemainRebirth;
#endif
		(*iter).strNameCard		= TempPet.strNameCard;
	}
	_pNetwork->UpdatePetTargetInfo( TempPet.lIndex );
	CUIManager::getSingleton()->GetPetInfo()->GetPetDesc();	
}

// ----------------------------------------------------------------------------
// Name : ReceivePetMountMessage()
// Desc : �ֿϵ��� Ÿ��.
// ----------------------------------------------------------------------------
// FIXME : ReceivePetAppearMessage, ReceiveStatusMessage, ReceivePetMountMessage �ߺ��Ǵ� �ڵ� ���� ���� �ʿ�.
void CSessionState::ReceivePetMountMessage( CNetworkMessage *istr )
{
	// �ֿϵ����� Ÿ��	: owner_index(n) mountPetTypeGrade(c)
	LONG	lOwnerIndex;
	SBYTE	sbMountPetTypeGrade;

	(*istr) >> lOwnerIndex;
	(*istr) >> sbMountPetTypeGrade;

	// [070824: Su-won] PET_COLOR_CHANGE
	SBYTE	sbPetColor =0;
	(*istr) >> sbPetColor;

	INDEX iPetType;
	INDEX iPetAge;
	_pNetwork->CheckPetType( sbMountPetTypeGrade, iPetType, iPetAge );
	
	const BOOL bPetRide = PetInfo().IsRide(iPetType, iPetAge);
	
	// [070824: Su-won] PET_COLOR_CHANGE
	INDEX iPetColoredType = iPetType | (sbPetColor<<8);
	
	// �� ���ΰ��...
	if( lOwnerIndex == _pNetwork->MyCharacterInfo.index )
	{			
		// ���� Ÿ���� �����ؾ� �ϴ� ���...
		if( iPetType != -1 && 
			iPetAge != -1 && 
			bPetRide )
		{
			
			if( _pNetwork->MyWearItem[WEAR_PET].IsEmptyItem() == FALSE )
			{
				const INDEX iPetIndex = _pNetwork->MyWearItem[WEAR_PET].Item_Plus;
				CNetworkLibrary::sPetInfo	TempPet;
				TempPet.lIndex				= iPetIndex;

				ObjInfo* pInfo = ObjInfo::getSingleton();
				CPetTargetInfom* pPetInfo = pInfo->GetMyPetInfo();
				
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
					pPetInfo->iType			= iPetType;
					pPetInfo->iAge			= iPetAge;
					pPetInfo->lIndex		= iPetIndex;
					pPetInfo->strNameCard	= (*iter).strNameCard;
					
					// �� Ÿ�� ����. [11/18/2010 rumist]
					pPetInfo->pen_pEntity	= NULL;
					
					CUIManager* pUIMgr = CUIManager::getSingleton();
					pUIMgr->GetPetInfo()->GetPetDesc();
					pUIMgr->GetPetTargetUI()->openUI();
				}
			}

			// ������ ������ �񱳸� �ؼ�, ���� �����ؾ� �ϴ���? �ƴϸ� �����ؾ� �ϴ��� �Ǵ�...
			_pNetwork->RidePet( (CPlayerEntity*)CEntity::GetPlayerEntity(0), NULL, iPetColoredType );
		}
		// �꿡�� �������� �����ؾ� �ϴ� ���...
		else
		{
			_pNetwork->LeavePet( (CPlayerEntity*)CEntity::GetPlayerEntity(0) );
		}
		//		_pNetwork->MyCharacterInfo.bPetRide = bPetRide;		
	}
	// Ÿ ĳ������ ���� ���...
	else
	{
		ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lOwnerIndex);

		if (pObject != NULL)
		{
			CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);

			pTarget->cha_iPetType = iPetType;
			pTarget->cha_iPetAge	= iPetAge;
			if( pTarget->cha_bPetRide != bPetRide )
			{
				// ���� Ÿ���� �����ؾ� �ϴ� ���...
				if( iPetType != -1 && 
					iPetAge != -1 && 
					bPetRide )
				{	
					_pNetwork->RidePet( pTarget->GetEntity(), NULL, iPetColoredType );
				}
				// �꿡�� �������� �����ؾ� �ϴ� ���...
				else
				{
					_pNetwork->LeavePet( pTarget->GetEntity() );
				}
				pTarget->cha_bPetRide = bPetRide;
			}
		}
	}	
}

// ----------------------------------------------------------------------------
// Name : ReceivePetLearnMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceivePetLearnMessage( CNetworkMessage *istr )
{
	LONG nSkillIndex;
	BYTE nSkillLevel;
	LONG nErrorcode;

	(*istr) >> nSkillIndex;
	(*istr) >> nSkillLevel;
	(*istr) >> nErrorcode;

	CUIManager* pUIManager = CUIManager::getSingleton();
	ObjInfo* pInfo = ObjInfo::getSingleton();
	CPetTargetInfom* pPetInfo = pInfo->GetMyPetInfo();

	if( nErrorcode == MSG_EX_PET_LEARN_ERROR_OK || nErrorcode == MSG_EX_PET_LEARN_ERROR_AUTO  )
	{	
		pUIManager->GetPetTrainingUI()->LearnSkill( pPetInfo->lIndex, nSkillIndex, nSkillLevel );
	}
	else if( nErrorcode == MSG_EX_PET_LEARN_ERROR_AUTO ) // ���� ��ų ���� 
	{
		pUIManager->GetPetTrainingUI()->LearnSkill( pPetInfo->lIndex, nSkillIndex, nSkillLevel, TRUE );
	}
	else 
	{
		pUIManager->GetPetTrainingUI()->LearnSkillError( nErrorcode );
	}

}

// ----------------------------------------------------------------------------
// Name : ReceivePetSkillListMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceivePetSkillListMessage( CNetworkMessage *istr )
{
	LONG nPetIndex, nCount;
	LONG nSkillIndex;
	BYTE nSkillLevel;
	int nSkillTime;

	(*istr) >> nPetIndex;
	(*istr) >> nCount;

	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->GetPetInfo()->ClearSkills( nPetIndex );
	
	for( int i = 0; i < nCount; i++ )
	{
		(*istr) >> nSkillIndex;
		(*istr) >> nSkillLevel;
		(*istr) >> nSkillTime;

		if (MY_PET_INFO()->lIndex < 0)
		{
			MY_INFO()->SetPetSkill(nPetIndex, nSkillIndex, nSkillLevel);
			pUIManager->GetPetInfo()->AddSkill(nPetIndex, nSkillIndex, nSkillLevel);

			CSkill& rSkill = _pNetwork->GetSkillData(nSkillIndex);
			if ( nSkillTime <= 0 )
			{
				rSkill.ResetStartTime();
				continue;
			}
			SLONG slRemainTime = ((SLONG)time(NULL) - _pNetwork->slServerTimeGap) - nSkillTime; 

			if ( slRemainTime > 0 )
				rSkill.SetStartTime(slRemainTime);

		}
		else
		{
			pUIManager->GetPetTrainingUI()->LearnSkill(nPetIndex, nSkillIndex, nSkillLevel, FALSE, false);
		}
	}
}

// ----------------------------------------------------------------------------
// Name : ReceivePetResetSkillMessage()
// Desc : ���� �����ϰ� �ִ� ���� ��ų �ʱ�ȭ
// ----------------------------------------------------------------------------
void CSessionState::ReceivePetResetSkillMessage( CNetworkMessage *istr )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->GetPetInfo()->ClearSkills( MY_PET_INFO()->lIndex );
	
	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
	strMessage.PrintF( _S(2565,"�ֿϵ��� ��ų �ʱ�ȭ�� �Ϸ� �Ǿ����ϴ�." ) );
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );
}

// ----------------------------------------------------------------------------
// Name : ReceivePetSellInfoMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceivePetSellInfoMessage( CNetworkMessage *istr )
{
	SPetExchangInfo temp;

	(*istr) >> temp.lOwnerIndex;
	(*istr) >> temp.lPetIndex;
	(*istr) >> temp.sbPetTypeGrade;
	(*istr) >> temp.lLevel;
	(*istr) >> temp.llExp;
	(*istr) >> temp.llNeedExp;
	(*istr) >> temp.lHP;
	(*istr) >> temp.lMaxHP;
	(*istr) >> temp.lAbility;
	(*istr) >> temp.lHungry;
	(*istr) >> temp.lMaxHungry;
	(*istr) >> temp.lSympathy;
	(*istr) >> temp.lMaxSympathy;
#ifdef PET_SEAL_TIME
	(*istr) >> temp.lRemainRebirth;	
#endif

	(*istr) >> temp.strNameCard;

	CUIManager::getSingleton()->GetPetInfo()->AddPetExchangeInfo( temp );
	
}

// ----------------------------------------------------------------------------
// Name : ReceivePetChangeMountMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceivePetChangeMountMessage( CNetworkMessage *istr )
{
	LONG	lResult;
	(*istr) >> lResult;
	CUIManager::getSingleton()->GetPetInfo()->PetExchangeMount( lResult );
}
//------------------------------------------------------------------------------
// CSessionState::ReceivePetLevelUpMessage
// Explain:  
// Date : 2005-10-07,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CSessionState::ReceivePetLevelUpMessage( CNetworkMessage *istr )
{
	LONG	lPetIndex;
	SBYTE	sbTypeGrade;
	LONG	lLevel;

	(*istr) >> lPetIndex;
	(*istr) >> sbTypeGrade;
	(*istr) >> lLevel;

	// [070824: Su-won] PET_COLOR_CHANGE
	SBYTE	sbPetColor =0;
	(*istr) >> sbPetColor;

	INDEX iPetType;
	INDEX iPetAge;
	_pNetwork->CheckPetType( sbTypeGrade, iPetType, iPetAge );

	ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_PET, lPetIndex);

	if (pObject != NULL)
	{
		CPetTarget* pTarget = static_cast< CPetTarget* >(pObject);

		if (pTarget->m_nIdxServer == MY_PET_INFO()->lIndex )
		{
			_pNetwork->ClientSystemMessage( _S(2253, "���� ������ �Ͽ����ϴ�." ) );
		}

		// ���� ���̰� ��������...
		if (pTarget->pet_iAge != iPetAge )
		{
			CEntity	*penEntity = pTarget->GetEntity();

			if (penEntity != NULL)
			{
				pTarget->m_nType	= iPetType;
				pTarget->pet_iAge	= iPetAge;

				// Date : 2005-11-08(���� 4:04:21), By Lee Ki-hwan
				// _s �� ó���� �ȵǳ���?���� 
				CTString strPetName = pTarget->pet_OwnerName + _S( 2228, "��" ) + CTString(" ") + PetInfo().GetName(iPetType, iPetAge);	
				pTarget->m_strName	= strPetName;
				penEntity->SetSkaModel(PetInfo().GetFileName(iPetType, iPetAge));					
				//((CPlayerEntity*)CEntity::GetPlayerEntity(0))->PetIdleAnim( penEntity );
				PetInfo().SetPetDataToEntity(iPetType, iPetAge, penEntity, FALSE);
				penEntity->GetModelInstance()->RefreshTagManager();
				//penEntity->GetModelInstance()->StopAllAnimations(0.1f);

				if( sbPetColor > 0 )
				{
					CTString strTexFile =PetInfo().GetColoredTexFileName(iPetType, iPetAge, sbPetColor);
					penEntity->GetModelInstance()->mi_aMeshInst[0].mi_tiTextures[0].ti_toTexture.SetData_t( strTexFile );
				}
			}
		}
	}

	CTString strEffect;
	strEffect = "pet_levelup";
	
	if( iPetAge >= 2 )
		strEffect = "pet_levelup_mount";
	
	// �� ��� ���� ...?? 
	PetStartEffectGroup( strEffect, lPetIndex );
}

// ----------------------------------------------------------------------------
// Name : ReceviePetItemMixMessage()
// Desc : ����ũ ������ ���� eons
// ----------------------------------------------------------------------------
void CSessionState::ReceviePetItemMixMessage( CNetworkMessage *istr )
{
	LONG	lResult;
	(*istr) >> lResult;
	CUIManager::getSingleton()->GetPetItemMixUI()->PetItemMixRep( lResult );	
}

// ----------------------------------------------------------------------------
// Name : ReceviePetItemChangeMessage()
// Desc : �� ����ũ ��� ���������� ��ȯ eons
// ----------------------------------------------------------------------------
void CSessionState::ReceviePetItemChangeMessage( CNetworkMessage *istr )
{
	LONG	lResult;
	(*istr) >> lResult;
	CUIManager::getSingleton()->GetPetTrainingUI()->PetChangeItemError( lResult );
}

// ----------------------------------------------------------------------------
// Name : ReceviePetRebirthMessage()
// Desc : eons( ���� ���� )
// ----------------------------------------------------------------------------
void CSessionState::ReceviePetRebirthMessage( CNetworkMessage *istr )
{
	LONG	lPetIndex;
	LONG	lResult;
	(*istr) >> lPetIndex;
	(*istr) >> lResult;

	CUIManager::getSingleton()->GetPetFree()->PetFreeError( lPetIndex, lResult );
}


void CSessionState::ReceiveBattleWarfareMsg( CNetworkMessage *istr )
{
	CUIMsgBox_Info	Msg_Info;
	int index;

	(*istr) >> index;

	if (UIMGR()->GetMessageBox(MSGCMD_BATTLE_WARFARE))
		return;

	if (_pNetwork->MyCharacterInfo.index == index) {
		CTString strTemp;
		Msg_Info.SetMsgBoxInfo( CTString("Warfare Battle"), UMBS_OKCANCEL, UI_NONE, MSGCMD_BATTLE_WARFARE );
		Msg_Info.AddString(_S(8451,"Do you want to move to Warfare Battle?"));
		UIMGR()->CreateMessageBox( Msg_Info );
	}
}

// ----------------------------------------------------------------------------
// Name : ReceivePartyRecall()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceivePartyRecall( CNetworkMessage *istr )
{
	CUIMsgBox_Info	MsgBoxInfo;
	LONG subType;
	(*istr) >> subType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch(subType)
	{

		case MSG_EX_PARTY_RECALL_NOTICE :
			pUIManager->CloseMessageBox(MSGCMD_NULL);
			MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
			MsgBoxInfo.AddString( _S(2516, "��Ƽ������ ��ȯ �޽����� ���½��ϴ�." ) );
			pUIManager->CreateMessageBox( MsgBoxInfo );
			break;
		case  MSG_EX_PARTY_RECALL_PROMPT :
			{
			if (_pNetwork->MyCharacterInfo.pk_mode == CHA_PVP_STATE_PK)
				return;
				CTString tv_str;
				(*istr) >> _pNetwork->m_tmp_idx;
				(*istr) >> _pNetwork->m_tmp_str;

				if( pUIManager->DoesMessageBoxExist(MSGCMD_EX_PARTY_RECALL_PROMPT) )
					pUIManager->CloseMessageBox(MSGCMD_EX_PARTY_RECALL_PROMPT); // ������ �޽��� �ڽ��� ����� ���ο� �޽����� ����
				
				MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��" ), UMBS_YESNO, UI_NONE, MSGCMD_EX_PARTY_RECALL_PROMPT );
				tv_str.PrintF(_S(2517,"%s��Ƽ���Բ��� ��ȯ�޽����� ���� �Խ��ϴ�. ��ȯ�� ���Ͻðڽ��ϱ�?"),_pNetwork->m_tmp_str.str_String);
				MsgBoxInfo.AddString(tv_str);
				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
			break;
	
		case MSG_EX_PARTY_RECALL_CANCEL :
			{
			   LONG nReq_char,nTgt_char;
			   CTString strReq_char,strTgt_char,tv_str;
			   (*istr) >> nReq_char;
			   (*istr) >> strReq_char;
			   (*istr) >> nTgt_char;
			   (*istr) >> strTgt_char;
			   if(nReq_char == _pNetwork->MyCharacterInfo.index)
			   {
			   		pUIManager->CloseMessageBox(MSGCMD_NULL);
					MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
					tv_str.PrintF(_S(2518, "%s��Ƽ������ ��ȯ�� �����Ͽ����ϴ�."), strTgt_char);
					MsgBoxInfo.AddString(tv_str);
					pUIManager->CreateMessageBox( MsgBoxInfo );
			   }
			   else {
				   pUIManager->CloseMessageBox(MSGCMD_NULL);
					MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
					tv_str.PrintF(_S(2519, "%s��Ƽ������ ��ȯ�� �����Ͽ����ϴ�."), strReq_char);
					MsgBoxInfo.AddString( tv_str );
					pUIManager->CreateMessageBox( MsgBoxInfo );				   
			   }
			}
			break;
		case MSG_EX_PARTY_RECALL_ERROR_NOT_FOUND_PARTY_PLAYER :
			{
				_pNetwork->ClientSystemMessage(_S(4802, "���� ����� �ִ� ��Ƽ ����� �����ϴ�."), SYSMSG_ERROR);
			}
			break;
		case MSG_EX_PARTY_RECALL_ERROR_CANT_USE_INSTANT_DUNGEON :
			{
				_pNetwork->ClientSystemMessage(_S(4504, "�ν���Ʈ�� ���ο����� ����� �� �����ϴ�."), SYSMSG_ERROR);
			}
			break;
		case MSG_EX_PARTY_RECALL_ERROR_CANT_USE_THIS_CONTINENT :
			{
				_pNetwork->ClientSystemMessage(_S(4803, "���� ������� ����� �� �����ϴ�."), SYSMSG_ERROR);
			}
			break;
		case MSG_EX_PARTY_RECALL_ERROR_NOT_PARTY:
			{
				_pNetwork->ClientSystemMessage(_S(3408, "��ȯ�� ��Ƽ������ �����ϴ�."), SYSMSG_ERROR);
			}
			break;
		case MSG_EX_PARTY_RECALL_ERROR_CANT_USE_EXPEND:
			{
				_pNetwork->ClientSystemMessage(_S(4752, "�������߿��� ����� �� �����ϴ�."), SYSMSG_ERROR);
			}
			break;
		case MSG_EX_PARTY_RECALL_CONFIRM_FAIL:
			{// ���� ���� �� �̵��� �� ���� ��� Ŭ�� ���� Ǯ�� ���� �޽���
				pUIManager->CloseMessageBox(MSGCMD_NULL);
				MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
				MsgBoxInfo.AddString( _S(340, "�̵��� ��ҵǾ����ϴ�." ) );
				pUIManager->CreateMessageBox( MsgBoxInfo );

				if(pUIManager->IsCSFlagOn(CSF_TELEPORT))
				{
					pUIManager->SetCSFlagOff( CSF_TELEPORT );
				}			
			}
			break;
		case MSG_EX_PARTY_RECALL_AREADY:
			{
				_pNetwork->ClientSystemMessage(_S(556, "�̹� ������� ������ �Դϴ�."), SYSMSG_ERROR);
			}
			break;

	}
}

// ----------------------------------------------------------------------------
// Name : ReceiveElementalDeleteMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveElementalDeleteMessage( CNetworkMessage *istr )
{
	// MSG_EX_ELEMENTAL_DELETE,	// ��ȯ�� ����		: index(n)
	LONG lIndex;
	(*istr) >> lIndex;

	CUIManager* pUIManager = CUIManager::getSingleton();

	ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_SLAVE, lIndex);

	if (pObject != NULL)
	{
		CSlaveTarget* pTarget = static_cast< CSlaveTarget* >(pObject);

		// �� ��ȯ���� ���...
		if( pTarget->slave_OwnerIndex == _pNetwork->MyCharacterInfo.index )
		{
			for (int i = UI_SUMMON_START; i <= UI_SUMMON_END; ++i)
			{
				CSummonUI* pSummonUI = (CSummonUI*)pUIManager->GetUI(i);

				if( pSummonUI->GetSummonEntity() && pSummonUI->GetSummonIndex() == lIndex )
				{
					pSummonUI->ResetSummon();
					break;
				}
			}			
		}

		SlaveInfo().StopIdleEffect( lIndex );

		//�ش� ��ȯ���� Ÿ�� ����Ʈ�� ����...
		pUIManager->StopTargetEffect( lIndex );

		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ClearTargetInfo(pTarget->GetEntity());

		ACTORMGR()->RemoveObject(eOBJ_SLAVE, lIndex);
	}
}

// ----------------------------------------------------------------------------
// Name : ReceiveEvocationStart()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveEvocationStart( CNetworkMessage *istr )
{
	// charindex(n) type(c)
	LONG	lCharIndex;
	INDEX	iType;

	(*istr) >> lCharIndex;
	(*istr) >> iType;

	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->EvocationStart( lCharIndex, iType);	
}

// ----------------------------------------------------------------------------
// Name : ReceiveEvocationStop()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveEvocationStop( CNetworkMessage *istr )
{
	// charindex(n)
	LONG	lCharIndex;	
	(*istr) >> lCharIndex;	
	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->EvocationStop( lCharIndex );	
}


//////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
//  Name 	: 
//  Desc 	: 
// ----------------------------------------------------------------------------
void AffinityErrChk( UBYTE errType )
{
	CUIMsgBox_Info MsgBoxInfo;
	CTString		MsgBoxMsg;
	MsgBoxInfo.SetMsgBoxInfo( _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch( errType )
	{
		case MSG_EX_AFFINITY_ERROR_CONNECT_SUCCESS:
		{
			MsgBoxMsg.PrintF( _S( 4671, "���������� ģ���� �ξ����ϴ�." ) );
		}
			break;
		case MSG_EX_AFFINITY_ERROR_CONNECT_NOMONEY:			// ��������
		{
			MsgBoxMsg.PrintF( _S(306, "������ �����մϴ�.") );
		}
			break;
		case MSG_EX_AFFINITY_ERROR_CONNECT_ALREADY:			// �̹̼��� ģ������
		{
			MsgBoxMsg.PrintF( _S( 4672, "�̹� ���°� ģ���� �ξ����ϴ�." ) );
		}
			break;
		case MSG_EX_AFFINITY_ERROR_ITEM_CONTRIBUTE_MAX:		// ģȭ�� ����Ʈ �ִ�� á��
		{
			MsgBoxMsg.PrintF( _S( 4673, "ģȭ���� ���� á���ϴ�. ���̻� ģȭ���� ���� �� �����ϴ�." ) );
		}
			break;
		case MSG_EX_AFFINITY_ERROR_ITEM_CONTRIBUTE_MISSMATCH:	// ��� ������ ������
		{
			MsgBoxMsg.PrintF( _S( 4674, "����� �� ���� �������Դϴ�. Ȯ���ϰ� �ٽ� �õ��Ͽ� �ֽʽÿ�." ) );
		}
			break;
		case MSG_EX_AFFINITY_ERROR_USESHOP_POINT:			// �����̿� ����Ʈ ����
		{
			MsgBoxMsg.PrintF( _S( 4675, "���� ��ſ��Դ� �� ������ �����ϴ�. �츮 %s �� ���ؼ� ���ݴ� ����� �� �ֽʽÿ�." ), 
			_pNetwork->GetAffinityData()->GetAffinityName( pUIManager->GetAffinity()->GetNPCIndex() ) );	// [2010/12/07 : Sora] ģȭ�� ���� 2��
		}
			break;
		case MSG_EX_AFFINITY_ERROR_GIFTINFO_NOITEM:			// ������� �������� ����
		{
			MsgBoxMsg.PrintF( _S( 4676, "��� ������ �޾ҽ��ϴ�. ���̻� ������� �������� �����ϴ�." ) );
		}
			break;
		case MSG_EX_AFFINITY_ERROR_GIFTINFO_NOPOINT:			// ����Ʈ�������� ���� ������
		{
			MsgBoxMsg.PrintF( _S( 4677, "ģȭ���� �����մϴ�." ) );
		}
			break;
		case MSG_EX_AFFINITY_ERROR_GIFT_NOSPACE:			// �κ��� ������ ���� ������ ����.
		{
			MsgBoxMsg = _S(2850, "�κ��丮�� ���� á���ϴ�.");
		}
			break;
		case MSG_EX_AFFINITY_ERROR_NOT_CONNECTED:
		{
			MsgBoxMsg = _S( 4678, "���� ģ���� ���� �ʾҽ��ϴ�. ���� ģ���� �ξ��ּ���." );
		}
			break;
		case MSG_EX_AFFINITY_ERROR_CONNECT_PCLEVEL:
		{
			MsgBoxMsg = _S( 965, "������ �����մϴ�." );
		}
			break;
		case MSG_EX_AFFINITY_ERROR_CONNECT_NOITEM:
		{
			MsgBoxMsg = _S( 1330 ,"�������� �����մϴ�." );
		}
			break;
	}
	MsgBoxInfo.AddString( MsgBoxMsg );
	pUIManager->CreateMessageBox( MsgBoxInfo );
}

// ----------------------------------------------------------------------------
//  Name 	: ReceiveAffinityMessage()
//  Desc 	: 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveAffinityMessage( CNetworkMessage *istr )
{
	UBYTE	ubType;
	UBYTE	errCode;
	(*istr) >> ubType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch( ubType )
	{
		case MSG_EX_AFFINITY_ITEM_CONTRIBUTE_REP:
		{
			CPrintF("Affinity Contribute success!!\n" );
		}
			break;
		case MSG_EX_AFFINITY_SHOPUSE_REP:
		{
			SLONG		npc_idx = 0;
			(*istr) >> npc_idx;
			pUIManager->GetAffinity()->OpenShop( npc_idx );
		}
			break;
		case MSG_EX_AFFINITY_GIFT_REP:
		{
			// [100324: selo] ���� ���� npc �� �˸� �׸񿡼� ���� �Ѵ�.
			SLONG npc_idx = 0;
			(*istr) >> npc_idx;

			_pNetwork->RemoveAffinityRewardNPC(npc_idx);

			if( npc_idx > 0)
			{
				Notice* pNotice = GAMEDATAMGR()->GetNotice();

				if (pNotice != NULL)
					pNotice->DelFromNoticeList(npc_idx, Notice::NOTICE_AFFINITY);
			}
		}
			break;
		case MSG_EX_AFFINITY_GIFTINFO_REP:
		{
			SLONG		gift_point = 0;
			SLONG		gift_item_index = 0;
			SLONG		gift_item_count = 0;
			CTString	MsgTemp;
			CUIMsgBox_Info	Msg_Info;

			(*istr) >> gift_point;
			(*istr) >> gift_item_index;
			(*istr) >> gift_item_count;

			CTString strTemp;
			strTemp.PrintF("%d", gift_point);
			pUIManager->InsertCommaToString(strTemp);

			MsgTemp.PrintF( _S( 5302, "%s ������ ���� ���� ����� ���ּż� ģȭ���� %s���� �Ǿ� ���� ������ �غ��߽��ϴ�. \n%s  %d���� �����ðڽ��ϱ�?" ),
				_pNetwork->GetAffinityData()->GetAffinityName( pUIManager->GetAffinity()->GetNPCIndex() ), strTemp, _pNetwork->GetItemData( gift_item_index )->GetName(), gift_item_count );
			
			Msg_Info.SetMsgBoxInfo( _S(4680, "���� �ޱ�"), UMBS_OKCANCEL, UI_NPC_AFFINITY, MSGCMD_AFFINITY_TAKEPRESENT );
			Msg_Info.AddString( MsgTemp );
			pUIManager->CreateMessageBox( Msg_Info );
		}
			break;
		case MSG_EX_AFFINITY_UPDATE_POINT:
		{
			SLONG	affinity_index = 0;
			SLONG	affinity_point = 0;
			SLONG	affinity_point_bonus = 0;
			
			(*istr) >> affinity_index;
			(*istr) >> affinity_point; // total (��彺ų�� �����Ⱦ��� ���ԵȰ�)
			(*istr) >> affinity_point_bonus; // ��彺ų�� ������ ��

			CNetworkLibrary::_AffinityInfo::mapAffIter iter;

			iter = _pNetwork->AffinityInfo.mapAffinityList.find( affinity_index );
			if( iter != _pNetwork->AffinityInfo.mapAffinityList.end() )
			{
				CTString MsgTemp;
				int ndelta = affinity_point - (*iter).second.current; // ���� ģȭ������ ������ ���
				
				CTString strAp;
				
				// [2010/12/07 : Sora] ģȭ�� ���� 2��
				if (affinity_point_bonus > 0)
				{
					CTString strBonus;

					strAp.PrintF("%d", ndelta - affinity_point_bonus);
					pUIManager->InsertCommaToString(strAp);

					strBonus.PrintF("%d", affinity_point_bonus);
					pUIManager->InsertCommaToString(strBonus);

					MsgTemp.PrintF( _S(6445, "%s(+%s)��ŭ %sģȭ���� ��µǾ����ϴ�."), strAp, strBonus,
						_pNetwork->GetAffinityData()->GetAffinityNameByIndex(affinity_index) );
				}
				else
				{
					strAp.PrintF("%d", ndelta);
					pUIManager->InsertCommaToString(strAp);

					MsgTemp.PrintF( _S(4681, "%s��ŭ %sģȭ���� ��µǾ����ϴ�."), strAp,
						_pNetwork->GetAffinityData()->GetAffinityNameByIndex(affinity_index) );
				}				

				((*iter).second).current = affinity_point;
				pUIManager->GetChattingUI()->AddSysMessage( MsgTemp );

				//2012/11/09 jeil ģȭ�� �ν��� �����ư��� üũ �Ͽ� �޽��� ��� �߰� 
				if(_pUIBuff->IsBuff(9189)){	//���� ��ȣ üũ 
					MsgTemp.PrintF(_S(5815, "(ģȭ�� �ν��� ����)"));	//��Ʈ���� �޽��� ���
					pUIManager->GetChattingUI()->AddSysMessage( MsgTemp );	//�޽��� ä��â�� ���
				}
				//2012/11/09 jeil �ӽ� ģȭ�� ������ �÷��� üũ�Ͽ� �޽��� ��� 
				//ģȭ�� �ν��� ������ ���������� üũ �ʿ� -> �����
				//ģȭ�� �ν��� ���� ��Ʈ�� �ʿ� ->�Ҿ�� 
//				MsgTemp.PrintF("(ģȭ�� �ν��� ����)");	//��Ʈ���� �޽��� ���
//				pUIManager->GetChattingUI()->AddSysMessage( MsgTemp );	//�޽��� ä��â�� ���

			}
			else
				CPrintF("Affinity Index Error !!\n" );
		}
			break;
		case MSG_EX_AFFINITY_LISTINFO:
		{
			SLONG	affinity_cnt = 0;
			SLONG	affinity_index = 0;
			SLONG	affinity_point = 0;
			SLONG	affinity_max = 0;
			CNetworkLibrary::_AffinityInfo::_AffinityPoint AfPoint;
			(*istr) >> affinity_cnt;

			_pNetwork->AffinityInfo.count = affinity_cnt;

			for( int i = 0; i < affinity_cnt; ++i )
			{
				(*istr) >> affinity_index;
				(*istr) >> affinity_point;
				(*istr) >> affinity_max;

				AfPoint.current = affinity_point;
				AfPoint.max		= affinity_max;

				_pNetwork->AffinityInfo.mapAffinityList.insert( std::make_pair( affinity_index, AfPoint ) );
			}
		}
			break;
		case MSG_EX_AFFINITY_ADDINFO:
		{
			// [6/8/2009 rumist] if server was accept that connect to npc forces, called this message.
			SLONG affinity_index;
			SLONG affinity_max = 0;
			CNetworkLibrary::_AffinityInfo::_AffinityPoint AfPoint;
			AfPoint.current = 0;
			(*istr) >> affinity_index;

			(*istr) >> affinity_max;
			AfPoint.max = affinity_max;

			// ģȭ�� ����2 ģȭ�� ���� ������ ����Ʈ ������Ʈ [2/14/2013 Ranma]
			CNetworkLibrary::_AffinityInfo::mapAffIter iter = _pNetwork->AffinityInfo.mapAffinityList.find( affinity_index );
		
			if ( iter == _pNetwork->AffinityInfo.mapAffinityList.end() )
			{
				_pNetwork->AffinityInfo.mapAffinityList.insert( std::make_pair( affinity_index, AfPoint ) );
			}
			else
			{
				((*iter).second).max = affinity_max;
			}
			
			// [2013/02/05] sykim70 ģȭ�� ��� UI ����
			_pNetwork->AffinityInfo.count = _pNetwork->AffinityInfo.mapAffinityList.size();
		}
			break;
		case MSG_EX_AFFINITY_ERROR:
		{
			(*istr) >> errCode;
			AffinityErrChk( errCode );
		}	
			break;
			
		// [100322: selo] ģȭ�� ���� �˶�		
		case MSG_EX_AFFINITY_REWARD_NOTICE:
		{					 
			INDEX noticecount = 0;
			INDEX npcidx = 0;

			(*istr) >> noticecount;

			if( noticecount > 0 )
			{
				Notice* pNotice = GAMEDATAMGR()->GetNotice();

				for( int i = 0; i < noticecount; i++ )
				{
					(*istr) >> npcidx;
					_pNetwork->AddAffinityRewardNPC(npcidx);

					if (pNotice != NULL && npcidx > 0)
						pNotice->AddToNoticeList(npcidx, Notice::NOTICE_AFFINITY);
				}
			}
		}
		break;

		// ģȭ�� ����2 ���� ���� ���� [2/13/2013 Ranma]		
		case MSG_EX_AFFINITY_INFOTAB_REP:
			{					 
				pUIManager->GetAffinityInfo()->RecvAffinity_RewardInfo(istr);
			}
		break;
	}
}

// ----------------------------------------------------------------------------
//  Name 	: ReceiveExLoadingEndMessage()
//  Desc 	: 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveExLoadingEndMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;

	switch( ubType )
	{
		case MSG_EX_LODING_END_NPC_PORTAL_USE:
		{
			CUIManager::getSingleton()->GetNpcScroll()->UseNPCScroll();
		}
			break;
	}
}

// ----------------------------------------------------------------------------
// [100208: selo] 
//  Name 	: ReceiveTakeAgainQuestItem()
//  Desc 	: ����Ʈ ������ �ٽ� �ޱ� ( �׸��� ���� ���� )
// ----------------------------------------------------------------------------
void CSessionState::ReceiveTakeAgainQuestItem(CNetworkMessage* istr)
{
	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;

	SLONG	slType;
	(*istr) >> slType;

	switch( slType )
	{
	case MSG_EX_TAKE_AGAIN_QUEST_ITEM_SUCCESS:
		{
			strMessage.PrintF( _S( 4820, "���������� �������� ���޵Ǿ����ϴ�.") );
		}
		break;
	case MSG_EX_TAKE_AGAIN_QUEST_ITEM_ERROR_ALREADY_EXIST:
		{
			strMessage.PrintF( _S( 4821, "�κ��丮�� �������� �����մϴ�.") );
		}
		break;
	case MSG_EX_TAKE_AGAIN_QUEST_ITEM_ERROR_FULL_INVENTORY:
		{
			strMessage.PrintF( _S( 3796, "�κ��丮�� �������� �������� ���� �� �����ϴ�.") );
		}
		break;
	}

	CUIManager* pUIManager = CUIManager::getSingleton();

	if (pUIManager->DoesMessageBoxExist(MSGCMD_QUEST_RESTORE_ITEM_RESULT))
		pUIManager->CloseMessageBox(MSGCMD_QUEST_RESTORE_ITEM_RESULT);

	MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_QUEST, MSGCMD_QUEST_RESTORE_ITEM_RESULT );
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );	
}

// ----------------------------------------------------------------------------
//  [4/15/2010 kiny8216] �ڽ�Ƭ �ý���2 �޽���
//  Name 	: RecieveCostume2Message()
//  Desc 	: �ڽ�Ƭ �ý���2 �޽���
// ----------------------------------------------------------------------------
void CSessionState::RecieveCostume2Message(CNetworkMessage* istr)
{
	UCHAR ucType;
	CTString	strMessage;

	(*istr) >> ucType;

	switch( ucType )
	{
	case 0:
		strMessage.PrintF( _S( 4868, "�����Ϸ��� ���Ⱑ �ڽ�Ƭ ����� Ÿ���� Ʋ���ϴ�.") );
		break;
	case 1:
	case 3:
		strMessage.PrintF( _S( 4869, "���и� ������ ���¿����� ������ �� �����ϴ�.") );
		break;
	case 2:
		strMessage.PrintF( _S( 4870, "�����Ϸ��� �ڽ�Ƭ ���Ⱑ ���� Ÿ���� Ʋ���ϴ�.") );
		break;
	case 4:
		strMessage.PrintF( _S( 4871, "�ڽ�Ƭ ���ҵ带 ������ ���¿����� ���и� ������ �� �����ϴ�.") );
		break;
	case 5:
		strMessage.PrintF( _S( 4872, "���ҵ带 ������ ���¿����� �ڽ�Ƭ ���и� ������ �� �����ϴ�.") );
		break;
	case 6:
		strMessage.PrintF("Please Equipt a Suitable Weapon Cover"); //RomeoST
		break;
	case 7:
		strMessage.PrintF("Cant Take off Cover"); //RomeoST
		break;
	}
	

	if(strMessage.Length()>0 )
		CUIManager::getSingleton()->GetChattingUI()->AddSysMessage( strMessage , SYSMSG_ERROR );	

	// ��� ���� �õ� ���� ����
	CUIManager::getSingleton()->SetCSFlagOffElapsed( CSF_ITEMWEARING );
}

// SOCKET_SYSTEM_S2 ���� �ý��� ���� �޽��� �޴� �κ� [4/3/2013 Ranma]
void CSessionState::RecieveSocketSystemMessage(CNetworkMessage* istr )
{
	UBYTE	slType;
	(*istr) >> slType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch( slType )
	{
		case MSG_EX_SOCKET_MAKE_REP:
			{
				SLONG idx;
				SBYTE socketCount;
				(*istr) >> idx;
				(*istr) >> socketCount;

				// ������ ui ������Ʈ�� �ʿ���.
				// ���Ἲ ������ ���ؼ� �����κ��� idx�� �޴´�.
				pUIManager->GetSocketCreate()->ShowResultSuccess(idx);
			}
			break;
		case MSG_EX_SOCKET_COMBINE_JEWEL_REP:
			{
				SLONG idx;
				(*istr) >> idx;
				pUIManager->GetSocketCombine()->ShowResultSuccess(idx);
			}
			break;

		case MSG_EX_SOCKET_UPGRADE_JEWEL_REP:
		case MSG_EX_SOCKET_UPGRADE_JEWEL_CHAOS_REP:
			{
				SLONG jewelIdx;
				(*istr) >> jewelIdx;
				pUIManager->GetSocketJewelCompos()->SetResultJewelUI(jewelIdx);
			}
			break;

		case MSG_EX_SOCKET_INFO_REP:
			{
			}
			break;

		case MSG_EX_SOCKET_CLEAN_JEWEL_REP:
			{
				SLONG idx;
				(*istr) >> idx;
				CUIMsgBox_Info MsgInfo;
				MsgInfo.SetMsgBoxInfo( _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
				MsgInfo.AddString( _S( 5000, "���� ���� �۾��� ���������� �Ϸ��Ͽ����ϴ�.") );
				pUIManager->CreateMessageBox( MsgInfo );
				pUIManager->GetSocketSystem()->CloseSocketSystem();
			}
			break;

		case MSG_EX_SOCKET_ERROR:
			{
				UBYTE errcode;
				(*istr) >> errcode;
				CheckSocketSystemError( errcode );
			}
			break;
	}
}	

// ���� ����� �޽����� �Ұ��� �ڽ��� ó���Ұ��� ���� �ʿ�. [5/4/2010 rumist]	
void CheckSocketSystemError(UBYTE errcode)
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString tStr;

	switch(errcode)
	{
		case MSG_EX_SOCKET_ERROR_ITEM_MISSMATCH:    // �ùٸ� �������� �ƴմϴ�.
				tStr = _S( 4981, "�ùٸ� �������� �ƴմϴ�. Ȯ�� �� �ٽ� �õ��� �ֽñ� �ٶ��ϴ�." );
				pUIManager->GetSocketSystem()->CloseSocketSystem();
				break;
		case MSG_EX_SOCKET_ERROR_FAILED_MAKE:		// ���� ���� ����
				tStr = _S( 5001, "���� ���� ����." );
				// ���нÿ��� ��ũ���� ���ŵǾ�� �ϹǷ� update�� �ʿ�.
				pUIManager->GetSocketCreate()->ShowResultFail();
				break;
		case MSG_EX_SOCKET_ERROR_NOMONEY:			// �� ����	
				tStr = _S( 306, "������ �����մϴ�." );
				pUIManager->GetSocketSystem()->CloseSocketSystem();
				break;
		case MSG_EX_SOCKET_ERROR_MAX_SOCKET:		// ���� ���ս� ���� ���� �ʰ�
				tStr = _S( 5002, "���� ������ �����մϴ�." );
				pUIManager->GetSocketSystem()->CloseSocketSystem();
				break;
		case MSG_EX_SOCKET_ERROR_INVEN_NOSPACE:		// �κ����� ����
				tStr = _S( 265, "�κ��丮 ������ �����մϴ�." );
				pUIManager->GetSocketSystem()->CloseSocketSystem();
				break;
		case MSG_EX_SOCKET_ERROR_NOWEARITEM:		// ���� ������ �� �ִ� �۾��Դϴ�.
				tStr = _S( 520, "���⳪ ���� �����մϴ�." );
				pUIManager->GetSocketSystem()->CloseSocketSystem();
				break;
		case MSG_EX_SOCKET_ERROR_NOSPACE:			// ������ ���� ���������δ� �۾��� ������ �� �����ϴ�
				tStr = _S( 4998, "������ �������� ���� �������Դϴ�." );
				pUIManager->GetSocketSystem()->CloseSocketSystem();
				break;
		case MSG_EX_SOCKET_ERROR_NOJEWEL:			// ������ ����ִ� �������� �۾��� ������ �� �����ϴ�
				tStr = _S( 5003, "�̹� ������ ���յǾ� �ִ� �������Դϴ�." );
				pUIManager->GetSocketSystem()->CloseSocketSystem();
				break;

		case MSG_EX_SOCKET_ERROR_FAILED_COMBINE: // ���� ���� ����
				pUIManager->GetSocketCombine()->ShowResultFail();
				break;
	}
	
	if(tStr.Length()>0 )
		pUIManager->GetChattingUI()->AddSysMessage( tStr , SYSMSG_ERROR );	
}


// ----------------------------------------------------------------------------
// [9/29/2010 kiny8216] ���� �ڽ�Ƭ
//  Name 	: RecieveCostume2Message()
//  Desc 	: ���� �ڽ�Ƭ �޽���
// ----------------------------------------------------------------------------
void CSessionState::RecieveLordCostumeMessage( CNetworkMessage* istr )
{
	UBYTE ubType;
	CTString strMessage;
	CUIMsgBox_Info MsgBoxInfo;

	(*istr) >> ubType;
	switch( ubType )
	{
	case MSG_EX_CASTLLAN_ERROR_GIVE_ITEM_ERROR:
		{	// ������ �������� ����
			strMessage = _S(2502, "���� ���� �������� �����ϴ�.");
		}
		break;
	case MSG_EX_CASTLLAN_ERROR_GIVE_ITEM_SUC:
		{	// ���� ����
			strMessage = _S(1840, "�������� ���������� ���� �Ǿ����ϴ�");
		}
		break;
	case MSG_EX_CASTLLAN_ERROR_NOT_CASTLLAN:
		{	// ���ְ� �ƴ�
			strMessage = _S(1722, "������ ������ �� �ִ� ������ �ƴմϴ�");
		}
		break;
	case MSG_EX_CASTLLAN_ERROR_NOT_CASTLLAN_GUILD:
		{
			// ���ֱ�尡 �ƴ�
			strMessage = _S( 3743, "���� ��尡 �ƴմϴ�." );
		}break;
	}

	if ( strMessage.Length() > 0)
	{
		MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString( strMessage );
		CUIManager::getSingleton()->CreateMessageBox( MsgBoxInfo );
	}
}

// ----------------------------------------------------------------------------
//  [2010/08/25 : Sora] ADD_SUBJOB
//  Name 	: RecieveSubJobMessage()
//  Desc 	: �������� �޽��� ó��
// ----------------------------------------------------------------------------
void CSessionState::RecieveSubJobMessage(CNetworkMessage* istr)
{
	SLONG	slType;
	(*istr) >> slType;

	switch( slType )
	{
		case MSG_EX_SUBJOB_ERROR_SUCESS:
			{
				SLONG subJobCode;
				(*istr) >> subJobCode;
				CTString strMessage;
				strMessage.PrintF( _S( 5083, "[%s]���� ��� �Ǿ����ϴ�." ), CUIManager::getSingleton()->GetSubJobName(subJobCode) );
				_pNetwork->ClientSystemMessage(strMessage, SYSMSG_NORMAL);
				_pNetwork->MyCharacterInfo.slSubJob = subJobCode;
			}
			break;
		case MSG_EX_SUBJOB_ERROR_FAIL:
			{
				SLONG errcode;
				(*istr) >> errcode;
				switch( errcode )
				{
					case 1:
						{
							_pNetwork->ClientSystemMessage(_S( 965, "������ �����մϴ�." ), SYSMSG_ERROR);
						}
						break;
					case 2:
						{
							_pNetwork->ClientSystemMessage(_S( 1217, "����ġ�� �����մϴ�." ), SYSMSG_ERROR);
						}
						break;
					case 3:
						{
							_pNetwork->ClientSystemMessage(_S( 966, "SP�� �����մϴ�." ), SYSMSG_ERROR);
						}
						break;
					case 4:
						{
							_pNetwork->ClientSystemMessage(_S( 967, "������ �����մϴ�." ), SYSMSG_ERROR);
						}
						break;
				}
			}		
			break;
		case MSG_EX_SUBJOB_ERROR_NOT_TRADER:
			{
				CUIMsgBox_Info MsgInfo;
				MsgInfo.SetMsgBoxInfo( _S( 1748, "�ȳ�" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
				MsgInfo.AddString( _S( 5050, "�������� ��ϵǾ� ���� �ʽ��ϴ�.") );
				CUIManager::getSingleton()->CreateMessageBox( MsgInfo );			
			}
			break;
	}
}

// ----------------------------------------------------------------------------
// [2010/10/20 : Sora] ���� �뺴 ī��
//  Name 	: RecieveMonsterMercenaryCardMessage()
//  Desc 	: 
// ----------------------------------------------------------------------------
void CSessionState::RecieveMonsterMercenaryCardMessage(CNetworkMessage* istr)
{
	UBYTE ubType;
	CTString strMessage;
	CUIMsgBox_Info MsgBoxInfo;

	CUIManager* pUIManager = CUIManager::getSingleton();
	pUIManager->CloseMessageBox(MSGCMD_MONSTER_MERCENARY_CARD_ERROR);

	(*istr) >> ubType;

	switch( ubType )
	{
		case MSG_EX_MERCENARY_SUMMON:		// ��ȯ/ ���� ����
			{
				SLONG uniqItemIndex;
				SBYTE toggle;
				//�뺴â ���
				(*istr) >> uniqItemIndex;
				(*istr) >> toggle;

				if( toggle > 0 )
				{
					CUIIcon* pIcon = pUIManager->GetInventory()->GetItemIcon(uniqItemIndex);

					if (pIcon != NULL)
						pUIManager->GetMonsterMercenary()->SetUseItemData(pIcon->getIndex());
				}
				pUIManager->GetMonsterMercenary()->ToggleMonsterMercenary( toggle );
			}
			break;
		case MSG_EX_MERCENARY_LIMIT_TIME:	// ���� �ð� ����
			{
				SLONG time;
				SLONG tab, nInvenIdx;

				(*istr) >> tab;
				(*istr) >> nInvenIdx;
				(*istr) >> time;

				CItems	&rItems = _pNetwork->MySlotItem[tab][nInvenIdx];

				strMessage.PrintF(_S( 5158, "[%s]%s�뺴 ��� �Ⱓ ������� %d�� ���ҽ��ϴ�."), 
									pUIManager->GetMonsterMercenary()->GetMonsterGrade(rItems.Item_Used2),
									CMobData::getData(rItems.Item_Plus)->GetName(), time);

				pUIManager->GetChattingUI()->AddSysMessage( strMessage, SYSMSG_ERROR );
				return;
			}
			break;
		case MSG_EX_MERCENARY_ERROR:
			{
				UBYTE errcode;
				
				(*istr) >> errcode;

				switch( errcode )
				{
					case MSG_EX_MERCENARY_ERROR_USE_FAIL:		// ��� ����
						{
							strMessage = _S( 5159, "�뺴�� ��ȯ �� �� �����ϴ�. Ȯ�� �� �ٽ� ����Ͻʽÿ�.");
						}
						break;
					case MSG_EX_MERCENARY_ERROR_SUMMON_ALREADY:	// �̹� �ٸ����� ��ȯ�Ǿ� �־� ����� �� ����
						{
							strMessage = _S( 5160, "�̹� �뺴�� ��ȯ�Ǿ� �ֽ��ϴ�.");
						}
						break;
					case MSG_EX_MERCENARY_ERROR_DONT_SUMMON:	// ��ȯ �Ұ�
						{
							strMessage = strMessage = _S( 5159, "�뺴�� ��ȯ �� �� �����ϴ�. Ȯ�� �� �ٽ� ����Ͻʽÿ�.");
						}
						break;
					case MSG_EX_MERCENARY_ERROR_MON_AUTO_DEL:	// ���� �ڵ� ����(�Ÿ��� �־����ų� �ð��� �ٵǾ)
						{
							pUIManager->GetMonsterMercenary()->ToggleMonsterMercenary( -1 );

							strMessage = _S( 5161, "�뺴 ��ȯ�� �����Ǿ����ϴ�.");

							pUIManager->GetChattingUI()->AddSysMessage( strMessage, SYSMSG_ERROR );
							return;
						}
						break;
					case MSG_EX_MERCENARY_ERROR_AREA:	// �� ���������� �뺴�� ��ȯ �� �� �����ϴ�. 
						{
							// �뺴â ����
							strMessage = _S( 5162, "�ش� ���������� �뺴�� ��ȯ �� �� �����ϴ�.");
						}
						break;
					default:
						{
							strMessage = _S( 5159, "�뺴�� ��ȯ �� �� �����ϴ�. Ȯ�� �� �ٽ� ����Ͻʽÿ�.");
						}
						break;
				}
			}
			break;
	}

	if ( strMessage.Length() > 0)
	{
		MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_MONSTER_MERCENARY_CARD_ERROR);
		MsgBoxInfo.AddString( strMessage );
		pUIManager->CreateMessageBox( MsgBoxInfo );
	}
}

void CheckFaceOffError(UBYTE ubError)
{
	CTString strMessage;
	CUIMsgBox_Info	MsgBoxInfo;

	switch( ubError )
	{
	case MSG_EX_FACEOFF_ERROR_FAIL:
		{
			strMessage.PrintF( _S( 5186, "����ī�尡 ���ų� ������ �����Ͽ����ϴ�. ��� �� �ٽ� �õ��� �ּ���."));
		}
		break;
	case MSG_EX_FACEOFF_ERROR_PLZ_CHOISE:
		{
			strMessage.PrintF( _S( 5187, "�����Ͻ� �ܸ�� ���� �ܸ�� �����մϴ�."));
		}
		break;
	default:
		{
			strMessage.PrintF( _S( 5188, "���� ���濡 �����Ͽ����ϴ�."));
		}
		break;
	}

	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->GetInitJob()->CloseInitJob();

	if ( strMessage.Length() > 0 )
	{
		MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString( strMessage );
		pUIManager->CreateMessageBox( MsgBoxInfo );
	}
}
void CSessionState::RecieveFaceOffMessage( CNetworkMessage* istr )
{
	UBYTE ubType;
	INDEX iCharIndex;
	UBYTE ubFaceStyle, ubHairStyle;
	CUIMsgBox_Info	MsgBoxInfo;
	CTString strMessage;

	(*istr) >> ubType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch( ubType )
	{
	case MSG_EX_FACEOFF_ERROR_SUC:
		{
			(*istr) >> ubHairStyle;
			(*istr) >> ubFaceStyle;
			(*istr) >> iCharIndex;

			if ( iCharIndex == _pNetwork->MyCharacterInfo.index )
			{	// �� ĳ���Ͱ� face, hair change�� ������ ���,
				_pNetwork->MyCharacterInfo.faceStyle = ubFaceStyle;
				_pNetwork->MyCharacterInfo.hairStyle = ubHairStyle;
				pUIManager->GetInitJob()->CloseInitJob();
				strMessage.PrintF( _S( 5185, "���� ���濡 �����߽��ϴ�."));
			}
			else
			{	// �ٸ� ĳ���Ͱ� face, hair change�� ������ ���,
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, iCharIndex);

				if (pObject != NULL)
				{
					if (((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsHelmet(iCharIndex) == TRUE)
						return;

					CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);

					CModelInstance* pMI = pTarget->GetEntity()->en_pmiModelInstance;

					INDEX iJob = pTarget->GetType();
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetAppearanceData( pTarget->GetEntity()->en_ulID, ubHairStyle, ubFaceStyle);
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ChangeHairMesh( pMI, iJob, ubHairStyle - 1);
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ChangeFaceMesh( pMI, iJob, ubFaceStyle - 1);
					pTarget->cha_itemEffect.Refresh(&pMI->m_tmSkaTagManager, 1);
					pTarget->cha_statusEffect.Refresh(&pMI->m_tmSkaTagManager, CStatusEffect::R_NONE);
				}
			}
			PCStartEffectGroup("squid", iCharIndex);
		}
		break;
	default :
		{
			CheckFaceOffError( ubType );
		}
		break;
	}
	if ( strMessage.Length() > 0 )
	{
		MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString( strMessage );
		pUIManager->CreateMessageBox( MsgBoxInfo );
	}
}

void CSessionState::RecieveLuckyDrawBoxMessage( CNetworkMessage* istr )
{
	CUIMsgBox_Info	MsgBoxInfo;
	CTString strMessage;
	SLONG slErrorType;

	(*istr) >> slErrorType;

	switch( slErrorType )
	{
		case MSG_LUCKYDRAWBOX_ERROR_SUCESS:
			return;
		case MSG_LUCKYDRAWBOX_ERROR_NEED:
			{
				strMessage.PrintF( _S( 5311, "���ڸ� ���� ���ؼ��� �������� �ʿ��մϴ� Ȯ�� �� �ٽ� �õ��Ͽ� �ֽʽÿ�."));
			}
			break;
		case MSG_LUCKYDRAWBOX_ERROR_INVEN:
			{
				strMessage.PrintF( _S(4237, "�κ��丮�� ������ ���� �մϴ�. �κ��丮�� ��� �� �ٽ� �õ����ֽñ� �ٶ��ϴ�."));
			}
			break;
		case MSG_LUCKYDRAWBOX_ERROR_USE:
			{
				strMessage.PrintF( _S(5312, "�������� ����� �� �����ϴ�."));
			}
			break;
		case MSG_LUCKYDRAWBOX_ERROR_OVER_WEIGHT:
			{
				strMessage.PrintF( _S(4237, "�κ��丮�� ������ ���� �մϴ�. �κ��丮�� ��� �� �ٽ� �õ����ֽñ� �ٶ��ϴ�."));
			}
			break;
		default:
			{
				strMessage.PrintF( _S(5312, "�������� ����� �� �����ϴ�."));
			}
	}

	if ( strMessage.Length() > 0 )
	{
		MsgBoxInfo.SetMsgBoxInfo( _S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString( strMessage );
		CUIManager::getSingleton()->CreateMessageBox( MsgBoxInfo );
	}
}


//added by sam 11/01/04 �޽��� �ڽ��� ���� �� �޽����� �������� �����ش�. 
void CSessionState::RecieveMsgBoxShow ( CNetworkMessage* istr )
{
	CUIMsgBox_Info	MsgBoxInfo;
	CTString strMessage;
	UCHAR chrErrorType;
	(*istr) >> chrErrorType;

	INDEX nTitle = 191;
	switch ( chrErrorType )
	{
		case MSG_EX_MSGBOX_INVEN_FULL:				// �κ��丮 ������
			{
				strMessage.PrintF( _S( 265, "�κ��丮 ������ �����մϴ�." ));			
				
				break;			
			}
		case MSG_EX_MSGBOX_CHANGE_START_POINT:
			{
				MsgBoxInfo.SetMsgBoxInfo( _S(nTitle,"Ȯ��"), UMBS_YESNO, UI_NONE, MSGCMD_CHANGE_START_POINT, 200);
				MsgBoxInfo.AddString( _S(5376, "��Ʈ ī������ ���� ���� ȯ���մϴ�.") );
				MsgBoxInfo.AddString( _S(5377, "�̰��� ��� ������ ���� �� �Դϴ�.") );
				MsgBoxInfo.AddString( _S(5378, "���谡���� �޽� �������ν�, ������ ���� Ȱ���� ���Դϴ�.") );
				MsgBoxInfo.AddString( _S(5379, "õõ�� �ѷ� ���ð� �ʺ��������� ������ ���Ͻø� Ȯ�� ��ư�� �����ּ���.") );
				MsgBoxInfo.AddString( _S(5380, "(��, ��Ҹ� ���� �� �ʺ��������� ���� �� �� �����ϴ�.)") );
				MsgBoxInfo.AddString( _S(5381, "�ʺ��������� �̵� �Ͻðڽ��ϱ�?") );
				CUIManager::getSingleton()->CreateMessageBox(MsgBoxInfo);
				return;
			}
			break;
		case MSG_EX_SHOW_CALENDER:
			{
				CUIManager::getSingleton()->GetCalendar()->OpenCalendar();
			}
			break;
	}	

	if ( strMessage.Length() > 0 )
	{
		MsgBoxInfo.SetMsgBoxInfo( _S(nTitle,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString( strMessage );
		CUIManager::getSingleton()->CreateMessageBox( MsgBoxInfo );
	}
}

void	CSessionState::RecieveUsedPartyItemMessage(CNetworkMessage* istr )
{
	INDEX		iItemIdx = -1;
	CTString	strNickName;

	(*istr) >> iItemIdx;
	(*istr) >> strNickName;

	CUIManager::getSingleton()->GetNotice()->ShowUsedPartyItemNotice( iItemIdx, strNickName );
}


void	CSessionState::RecieveRoyalrumbleMessage(CNetworkMessage* istr )
{
	CUIMsgBox_Info	MsgBoxInfo;
	CTString strMessage;
	UBYTE msgIdx				= 0;
	(*istr) >> msgIdx;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch( msgIdx )
	{
		case MSG_EX_ROYAL_RUMBLE_NOTICE:						// ����
			{
				UBYTE uResult = 0;
				(*istr) >> uResult;
				pUIManager->GetNotice()->ShowRoyalRumbleNotice( uResult );
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_REG_MENU:						// ��û�޴� Ȱ��ȭ.
			{
				UBYTE uType = 0;
				(*istr) >> uType;
				pUIManager->GetRadar()->SetRoyalRumbleStatus( uType );
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_PLAYER_REP:					// ��� ��û ���.
			{
				MsgBoxInfo.SetMsgBoxInfo( _s(""), UMBS_OK, UI_NONE, MSGCMD_NULL);
				UBYTE uResult = 0;
				(*istr) >> uResult;
				if( uResult == 0 )
				{
					MsgBoxInfo.AddString( _S(5414, "�ξ� ������ ������û�� �Ϸ��Ͽ����ϴ�.") );
				}
				else if( uResult == 1 )
				{
					MsgBoxInfo.AddString( _S(5415, "������ �����Ͽ� �ξⷳ���� �����Ͻ� �� �����ϴ�.") );
				}
				else if( uResult == 2 )
				{
					MsgBoxInfo.AddString( _S(5416, "��������� �Ұ����մϴ�.") );
				}
				else if( uResult == 3 )
				{
					MsgBoxInfo.AddString( _S(5417, "�̹� ��û�Ͽ����ϴ�.") );
				}
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_PLAYER_UNREGIST_REP:			// ��� ���.
			{
				MsgBoxInfo.SetMsgBoxInfo( _S(5405, "�ξⷳ�� ��û ���"), UMBS_OK, UI_NONE, MSGCMD_NULL);
				UBYTE uResult = 0;
				(*istr) >> uResult;
				if( uResult == 0 )
				{
					MsgBoxInfo.AddString( _S(5418, "���������� ��ҵǾ����ϴ�.") );
				}
				else if( uResult == 1 )
				{
					MsgBoxInfo.AddString( _S(5419, "����� �� �ִ� �ð��� �ƴմϴ�.") );
				}
				else if( uResult == 2 )
				{
					MsgBoxInfo.AddString( _S(5420, "����� ���ܿ� �����ϴ�.") );
				}
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_PLAYER_REG_RESULT:				// ���� ���� ���.
			{
				MsgBoxInfo.SetMsgBoxInfo( _S(5407, "�ξⷳ�� ������û"), UMBS_OK, UI_NONE, MSGCMD_NULL);
				UBYTE uResult = 0;
				(*istr) >> uResult;
				if( uResult == 0 )
				{
					MsgBoxInfo.AddString( _s("��û�� �� ����") );
				}
				else if( uResult == 1 )
				{
					MsgBoxInfo.AddString( _S(5421, "���ϵ帳�ϴ�. �ξⷳ���� ���ߵǼ̽��ϴ�. ��� �����Ͽ� ���ʸ� ��ٷ� �ּ���.") );
				}
				else if( uResult == 2 )
				{
					MsgBoxInfo.AddString( _S(5422, "��Ÿ���Ե� �ξⷳ���� ���ߵ��� ���ϼ̽��ϴ�. ���� �ξⷳ���� ������ �ּ���.") );
				}
				else if( uResult == 3 )
				{
					MsgBoxInfo.AddString( _S(5423, "�˼��մϴ�. ��Ⱑ ��ҵǾ����ϴ�.") );
				}
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_GO_ZONE:						// �̵��ϱ�
			{
				MsgBoxInfo.SetMsgBoxInfo( _S(5424, "���� �̵�"), UMBS_OK|UMBS_USE_TIMER, UI_RADAR, MSGCMD_ROYALRUMBLE_GO_ZONE);
								
				MsgBoxInfo.AddString( _S(5425,	"�ξⷳ�� ���Ƿ� �̵��մϴ�."
												"�̵��Ϸ��� Ȯ�� ��ư�� ��������."
												"(���ѽð��� ������ �ǰ�ó�� �˴ϴ�.)" ) );
// 				MsgBoxInfo.AddString( _s("�̵��Ϸ��� Ȯ�� ��ư�� ��������.") );
// 				MsgBoxInfo.AddString( _s("(���ѽð��� ������ �ǰ�ó�� �˴ϴ�.)") );
				MsgBoxInfo.SetMsgBoxTimer( 30, FALSE );			// 30 seconds.
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_ENTER_NEXT_PLAYER:				// ���� ���� ���� ���� �ð�
			{
				INDEX iLeftTime = 0;
				(*istr) >> iLeftTime;
				pUIManager->GetNotice()->ShowRoyalRumbleNextPlayerTime( iLeftTime );
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_HOLD:							// ��� ���� 
			{
				;
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_WINNER:						// ����� ��ü ����
			{
			INDEX iLevelType = 0;
			INDEX iCharIdx = 0;
			INDEX iZoneidx = 0;
			CTString strNickName;
			(*istr) >> iLevelType;
			(*istr) >> iCharIdx;
			(*istr) >> strNickName;
			(*istr) >> iZoneidx;
				pUIManager->GetNotice()->ShowRoyalRumbleWinner( iLevelType, strNickName, iZoneidx);
				if( _pNetwork->MyCharacterInfo.index == iCharIdx )
				{
					pUIManager->GetRadar()->ShowRoyalRumbleTrophy();
				}
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_REWARD_REP:					// ���� ����
			{
				UBYTE uResult = 0;
				(*istr) >> uResult;
				MsgBoxInfo.SetMsgBoxInfo( _s(""), UMBS_OK, UI_NONE, MSGCMD_NULL);
				if( uResult == 0 )
				{
					MsgBoxInfo.AddString( _S(5427, "���� ����ڰ� �ƴմϴ�.") );
				}
				else if( uResult == 1 )
				{
					MsgBoxInfo.AddString( _S(1755, "�̹� ������ �޾ҽ��ϴ�.") );
				}
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_POINT_REP:						// ��������Ʈ ��ȸ ����.
			{
				INDEX iWarPoint = 0, iWarAccPoint = 0;
				(*istr) >> iWarPoint;
				(*istr) >> iWarAccPoint;
				MsgBoxInfo.SetMsgBoxInfo( _S(5412, "���� ����Ʈ ��ȸ"), UMBS_OK, UI_NONE, MSGCMD_NULL);
				CTString strTemp;
				MsgBoxInfo.AddString( _S(5428, "���� ���� ����Ʈ"), 0xF2F2F2FF, TEXT_CENTER );
				MsgBoxInfo.AddString( _s(" ") );
				strTemp.PrintF( "%d", iWarPoint );
				MsgBoxInfo.AddString( strTemp, 0xF2F2F2FF, TEXT_CENTER );
				MsgBoxInfo.AddString( _s(" ") );
				MsgBoxInfo.AddString( _s(" ") );
				MsgBoxInfo.AddString( _S(5429, "���� ���� ����Ʈ"), 0xF2F2F2FF, TEXT_CENTER );
				MsgBoxInfo.AddString( _s(" ") );
				strTemp.PrintF( "%d", iWarAccPoint );
				MsgBoxInfo.AddString( strTemp, 0xF2F2F2FF, TEXT_CENTER );
				MsgBoxInfo.AddString( _s(" ") );
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_TIME_REP:
			{
				INDEX iTime = -1;
				INDEX iTimeMinute = -1;
				(*istr) >> iTime >> iTimeMinute;
				MsgBoxInfo.SetMsgBoxInfo( _S(5430, "�ξⷳ�� ��� ����"), UMBS_OK, UI_NONE, MSGCMD_NULL );
				CTString strTemp;
				if( iTime < 0 )
				{
					strTemp.PrintF( _S(5431, "���� ��Ⱑ �������Դϴ�.") );
				}
				else
				{
					strTemp.PrintF( _S(5432, "���� ���� %d�� 00�п� ����˴ϴ�."), iTime, iTimeMinute );
				}
				MsgBoxInfo.AddString( strTemp, 0xF2F2F2FF, TEXT_CENTER );
				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_LEFT_COUNT:
			{
				INDEX iLeftCount = 0;
				(*istr) >> iLeftCount;
				pUIManager->GetRoyalRumbleIcon()->SetLeftCount( iLeftCount );
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_TIME_NOTICE:
			{
				UBYTE uType = 0;
				INDEX iLeftTime = -1;
				(*istr) >> uType;
				(*istr) >> iLeftTime;

				pUIManager->GetRadar()->SetRoyalRumbleSandglass(uType, iLeftTime );
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_NOTFOUND_ITEM:
			{	
				MsgBoxInfo.SetMsgBoxInfo( _S( 5576, "�ξⷳ�� �����"), UMBS_OK, UI_NONE, MSGCMD_NULL );
				CTString strTemp;
				strTemp.PrintF( _S( 5577, "�ش� �ξⷳ�� ������ ������� �������� �ʽ��ϴ�.") );
				MsgBoxInfo.AddString( strTemp, 0xF2F2F2FF, TEXT_CENTER );
				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
			break;
		case MSG_EX_ROYAL_RUMBLE_KILL_PLAYER:
			{
				CTString strAttacker;
				CTString strVictim;
				CTString strTemp;
				(*istr) >> strAttacker >> strVictim;
				// ADD-Contents : ITS#3620 ������ ������ ����� �޽��� �߰�.  [8/22/2011 rumist]
				if( strAttacker == strVictim )
					strTemp.PrintF( _S( 5580, "%���� �ƿ��Ǿ����ϴ�."), strAttacker );
				else
					strTemp.PrintF( _S( 5578, "%s���� %s���� �ƿ����׽��ϴ�."), strAttacker, strVictim );
				pUIManager->GetChattingUI()->AddSysMessage( strTemp, SYSMSG_ERROR );
			}
			break;
	}
}

void CSessionState::RecieveMasterStoneMessage( CNetworkMessage* istr )
{
	ResponseClient::doItemUseMasterStoneUSA* pPacket = reinterpret_cast<ResponseClient::doItemUseMasterStoneUSA*>(istr->GetBuffer());

	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->GetMixNew()->MixNewMasterStoneRep(pPacket->error, pPacket->success_type, pPacket->percent);
}

void CSessionState::RecieveRankingListExMessage( CNetworkMessage* istr )
{
	CUIManager::getSingleton()->GetRankingViewEx()->RecvRankingList(*istr);
}
void CSessionState::ReceiveSetAggressiveMobMessage(CNetworkMessage* istr)
{
	SLONG netIndex;
	BOOL isAggressive;
	(*istr) >> netIndex
			>> isAggressive;

	CMobTarget* pMT = dynamic_cast<CMobTarget*>(ACTORMGR()->GetObject(eOBJ_MOB, netIndex));
	if (!pMT) return;

	pMT->mob_bIsAggressive = isAggressive;
}