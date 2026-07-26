#include "stdh.h"
#include <Engine/Base/ErrorTable.h>
#include <Engine/Base/MemoryTracking.h>
#include <Engine/Base/Shell.h>
#include <Engine/Base/ListIterator.inl>
#include <Engine/Base/Synchronization.h>
#include <Engine/Math/Float.h>
#include <Engine/Network/CNetwork.h>
#include <Engine/Network/Server.h>
#include <Engine/Network/NetworkProfile.h>
#include <Engine/Network/ClientInterface.h>
#include <Engine/Network/SessionState.h>
#include <Engine/Ska/Render.h>
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Network/LevelChange.h>
#include <Engine/Network/tcpipconnection.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Sound/SoundObject.h>
#include <Engine/Sound/SoundLibrary.h>
#include <Engine/Templates/Stock_CEntityClass.h>
#include <Engine/Templates/DynamicContainer.cpp>
#include <Engine/GlobalDefinition.h>
#include <Engine/GameState.h>
#include <Engine/SlaveInfo.h>
#include <Engine/Interface/UIManager.h>
#include <Engine/Interface/UIPetInfo.h>
#include <Engine/Interface/UISelectWord.h>
#include <Engine/Contents/function/SingleBattleUI.h>
#include <Engine/Interface/UIAutoHelp.h>
#include <Engine/Interface/UISiegeWarfareDoc.h>
#include <Engine/Contents/Base/UINoticeNew.h>
#include <Engine/Contents/function/SummonUI.h>
#include <Engine/Contents/function/TeleportUI.h>
#include <Engine/Interface/UIShop.h>
#include <include/F_CSocket_Event.h>
#include <Engine/Interface/UICharServerMove.h>
#include <Engine/Interface/UIQuickSlot.h>
#include <Engine/Interface/UIChildQuickSlot.h>
#include <Engine/Interface/UIFortune.h>
#include <Engine/Interface/UISelectList.h>
#include <engine/Contents/function/SystemMenuUI.h>
#include <Engine/Interface/UIFlowerTree.h>
#include <Engine/Interface/UIGuildBattle.h>
#include <Engine/Interface/UIMap.h>
#include <Engine/Interface/UISkillLearn.h>
#include <Engine/Contents/function/SSkillLearnUI.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Interface/UIProduct.h>
#include <Engine/Contents/function/ExChangeUI.h>
#include <Engine/Contents/function/CashExchangeUI.h>
#include <Engine/Contents/function/GuildWarMixUI.h>
#include <Engine/Contents/function/WareHouseUI.h>
#include <Engine/Contents/Base/UIPartyNew.h>
#include <Engine/Contents/Base/UICharacterInfoNew.h>
#include <Engine/Contents/function/HelperUI.h>
#include <Engine/Contents/function/HelperManager.h>
#include <Engine/Contents/function/Helper_GuardianInfoUI.h>
#include <Engine/Contents/function/Helper_Student.h>
#include <Engine/Interface/UIPlayerInfo.h>
#include <Engine/Contents/Base/UIChangeWeaponNew.h>
#include <Engine/Contents/Base/UIChangeEquipment.h>
#include <Engine/Interface/UIGuildWarPortal.h>
#include <Engine/Interface/UIRefine.h>
#include <Engine/Contents/function/TargetInfoNewUI.h>
#include <Engine/Interface/UIGamble.h>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Interface/UIMinigame.h>
#include <Engine/Interface/UIRanking.h>
#include <Engine/Interface/UIRankingReborn.h>
#include <Engine/Interface/UIRankingSummon.h>
#include <Engine/Interface/UIRankingPvP.h>
#include <Engine/Contents/function/InsectCollectUI.h>
#include <Engine/Interface/UIGuild.h>
#include <Engine/Contents/function/GuildStashUI.h>
#include <Engine/Interface/UIInitJob.h>
#include <Engine/Interface/UIMessenger.h>
#include <Engine/Interface/UIMixNew.h>
#include <Engine/Contents/function/WildPetInfoUI.h>
#include <Engine/Interface/UISiegeWarfareNew.h>
#include <Engine/Interface/UINpcScroll.h>
#include <Engine/Interface/UINickName.h>
#include <Engine/Interface/UIRadar.h>
#include <Engine/Interface/UISocketSystem.h>
#include <Engine/Interface/UIMix.h>
#include <Engine/Contents/function/CompoundUI.h>
#include <Engine/Interface/UIProcessNPC.h>
#include <Engine/Interface/UIOXQuizEvent.h>
#include <Engine/Interface/UIBingoBox.h>
#include <Engine/Interface/UISelectResource.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Effect/CEffectGroupManager.h>
#include <Engine/Effect/CEffectGroup.h>
#include <Engine/Contents/Base/Auction.h>
#include <Engine/Contents/Base/UISkillNew.h>
#include <Engine/Contents/Base/ExpressSystem.h>
#include <Engine/Contents/function/MailBoxManager.h>
#include <Engine/Contents/Base/PetStash.h>
#include <Engine/Contents/Base/Calendar.h>
#include <Engine/Contents/Base/Syndicate.h>
#include <Engine/Contents/Base/Durability.h>
#include <Engine/Contents/Base/Notice.h>
#include <Engine/Contents/Base/Quest.h>
#include <Engine/Contents/Base/UIQuestBookNew.h>
#include <Engine/Contents/Base/UIQuestView.h>
#include <Engine/Contents/Base/UIQuestAccept.h>
#include <Engine/Contents/Base/UIQuestComplete.h>
#include <Engine/Contents/Base/UIQuestRestore.h>
#include <Engine/Contents/function/ItemCollection.h>
#include <Engine/Contents/function/PremiumChar.h>
#include <tlhelp32.h>

#include <Engine/Contents/Login/ServerSelect.h>
#include <Engine/Contents/Login/UIServerSelect.h>
#include <Engine/Contents/Login/UICharacterSelect.h>
#include <Engine/Contents/Login/CharacterSelect.h>
#include <Engine/Contents/Login/UICharacterSelect.h>
#include <Engine/Contents/Login/UILoginNew.h>

#include <Engine/LoginJobInfo.h>
#include <Engine/GameStageManager/StageMgr.h>
#include <Engine/Loading.h>
#include <Engine/Contents/Base/Quest.h>
#include <Engine/Contents/Base/Party.h>

#include <Engine/Contents/function/SimplePlayerInfoUI.h>
#include <Engine/Contents/function/ItemComposeUI.h>
#include <Engine/Contents/Base/PersonalshopUI.h>

#include <Engine/Contents/function/TransmogrifyUI.h>
#include <Engine/Contents/function/ExtendMenuUI.h>
#include <Engine/Contents/function/BoxOpenUI.h>
#include <Engine/Contents/function/SealComposeUI.h>

// WSS_NPROTECT 070402 ------------------------------->>
#ifndef NO_GAMEGUARD
	//#include <NPGameLib.h>
#include <Engine/GameGuardInterface.h>
#endif
// ---------------------------------------------------<<
#ifdef PRESTIGE_SYSTEM
#include <Common/Packet/ptype_old_do_prestige.h>
#include <Engine/Interface/UIPrestige.h>
#endif
#include "Reza.h"

#ifdef KALYDO
#include <Engine/Kalydo/PackageManager.h>
#endif

#include <Engine/Help/ItemHelp.h>
#include <Engine/Interface/UISecurity.h>

#ifdef BATTLE_PASS_SYSTEM
#include <Common/Packet/ptype_old_do_battle_pass.h>
#include <Engine/Interface/UIBattlePass.h>
#endif

#ifdef	STASH_PASSWORD
#include <Common/Packet/ptype_old_do_stash.h>
#endif	// STASH_PASSWORD

#include <Engine/Contents/Login/UICharacterCreateNew.h>
#include <Engine/Object/ActorMgr.h>

#include <Common/Packet/ptype_old_mempos.h>
#include <Common/Packet/ptype_old_mempos_rus.h>
#include <Common/Packet/ptype_old_do_changejob.h>
#include <Common/Packet/ptype_old_do_move.h>
#include <Common/Packet/ptype_old_do_skill.h>

// Debug logging helper
#define CASH_DEBUG_LOG(fmt, ...) \
	do { \
		FILE* pDebugLog = fopen("D:\\cash_exchange_debug.log", "a"); \
		if (pDebugLog) { \
			fprintf(pDebugLog, fmt, __VA_ARGS__); \
			fflush(pDebugLog); \
			fclose(pDebugLog); \
		} \
	} while(0)
#include <Common/Packet/ptype_old_do_sskill.h>
#include <Common/Packet/ptype_old_extend.h>
#include <Common/Packet/ptype_old_do_reborn.h>
#include <Engine/Info/MyInfo.h>
#include <Engine/Contents/function/gps.h>
#include <Engine/Contents/function/ItemCompose.h>
#include "Entities/TargetInfo.h"
#include <Engine/Contents/function/ProductNPCUI.h>
#include <Engine/Contents/function/Product2UI.h>
#include <Engine/Contents/function/UICraft.h>  //Craft system
#include "Contents/function/UIPassiveSystemRST.h"

#define SESSIONSTATEVERSION_OLD 1
#define SESSIONSTATEVERSION_WITHBULLETTIME 2
#define SESSIONSTATEVERSION_CURRENT SESSIONSTATEVERSION_WITHBULLETTIME



//---------------------------------------------------------------------

#define MODEL_MONEY		("Data\\Item\\Common\\item_money_01.smc")
#define MODEL_GIFT		("Data\\Item\\Common\\item_gift.smc")


#define MODEL_DROPIEM_TI_BU		("Data\\Item\\Common\\ti_bu_drop.smc")
#define MODEL_DROPIEM_TI_BD		("Data\\Item\\Common\\ti_bd_dorp.smc")
#define MODEL_DROPIEM_TI_FT		("Data\\Item\\Common\\ti_ft_drop.smc")
#define MODEL_DROPIEM_TI_HN		("Data\\Item\\Common\\ti_hn_drop.smc")

#define MODEL_DROPIEM_NI_BU		("Data\\Item\\Common\\ni_bu_drop.smc")
#define MODEL_DROPIEM_NI_BD		("Data\\Item\\Common\\ni_bd_drop.smc")
#define MODEL_DROPIEM_NI_FT		("Data\\Item\\Common\\ni_ft_drop.smc")
#define MODEL_DROPIEM_NI_HN		("Data\\Item\\Common\\ni_hn_drop.smc")

#define MODEL_DROPIEM_HW_BU		("Data\\Item\\Common\\hw_bu_drop.smc")
#define MODEL_DROPIEM_HW_BD		("Data\\Item\\Common\\hw_bd_drop.smc")
#define MODEL_DROPIEM_HW_FT		("Data\\Item\\Common\\hw_ft_drop.smc")
#define MODEL_DROPIEM_HW_HN		("Data\\Item\\Common\\hw_hn_drop.smc")

#define MODEL_DROPIEM_MA_BU		("Data\\Item\\Common\\ma_bu_drop.smc")
#define MODEL_DROPIEM_MA_BD		("Data\\Item\\Common\\ma_bd_drop.smc")
#define MODEL_DROPIEM_MA_FT		("Data\\Item\\Common\\ma_ft_drop.smc")
#define MODEL_DROPIEM_MA_HN		("Data\\Item\\Common\\ma_hn_drop.smc")

#define MODEL_DROPIEM_RO_BU		("Data\\Item\\Common\\ro_bu_drop.smc")
#define MODEL_DROPIEM_RO_BD		("Data\\Item\\Common\\ro_bd_drop.smc")
#define MODEL_DROPIEM_RO_FT		("Data\\Item\\Common\\ro_ft_drop.smc")
#define MODEL_DROPIEM_RO_HN		("Data\\Item\\Common\\ro_hn_drop.smc")

#define MODEL_DROPIEM_SO_BU		("Data\\Item\\Common\\so_bu_drop.smc")
#define MODEL_DROPIEM_SO_BD		("Data\\Item\\Common\\so_bd_drop.smc")
#define MODEL_DROPIEM_SO_FT		("Data\\Item\\Common\\so_ft_drop.smc")
#define MODEL_DROPIEM_SO_HN		("Data\\Item\\Common\\so_hn_drop.smc")

#define MODEL_DROPIEM_NS_HD		("Data\\Item\\Common\\ns_hood_drop.smc")
#define MODEL_DROPIEM_NS_BU		("Data\\Item\\Common\\ns_bu_drop.smc")
#define MODEL_DROPIEM_NS_BD		("Data\\Item\\Common\\ns_bd_drop.smc")
#define MODEL_DROPIEM_NS_FT		("Data\\Item\\Common\\ns_ft_drop.smc")
#define MODEL_DROPIEM_NS_HN		("Data\\Item\\Common\\ns_hn_drop.smc")
#define MODEL_DROPIEM_NS_WG		("Data\\Item\\Common\\ns_wing_drop.smc")

#define MODEL_DROP_WEAPON_NS	("Data\\Item\\Weapon\\Drop\\ns_weapon_drop.smc")

#define MODEL_DROPIEM_HW_BOW		("Data\\Item\\Common\\hw_bow_drop.smc")
#define MODEL_DROPIEM_HW_STAFF		("Data\\Item\\Common\\hw_staff_drop.smc")
#define MODEL_DROPIEM_MA_WAND		("Data\\Item\\Common\\ma_wand_drop.smc")
#define MODEL_DROPIEM_MA_STAFF		("Data\\Item\\Common\\ma_staff_drop.smc")
#define MODEL_DROPIEM_NI_SHIELD		("Data\\Item\\Common\\ni_shield_drop.smc")
#define MODEL_DROPIEM_NI_SWORD		("Data\\Item\\Common\\ni_sword_drop.smc")
#define MODEL_DROPIEM_RO_CBOW		("Data\\Item\\Common\\ro_crossbow_drop.smc")
#define MODEL_DROPIEM_RO_DAGGER		("Data\\Item\\Common\\ro_dagger_drop.smc")
#define MODEL_DROPIEM_TI_GSWORD		("Data\\Item\\Common\\ti_gsword_drop.smc")
#define MODEL_DROPIEM_TI_AXE		("Data\\Item\\Common\\ti_axe_drop.smc")
#define MODEL_DROPIEM_SO_SCYTHE		("Data\\Item\\Common\\so_scythe_001_drop.smc")
#define MODEL_DROPIEM_SO_STAFF		("Data\\Item\\Common\\so_staff_001_drop.smc")

//---------------------------------------------------------------------

#ifndef PROC_MESSAGE_COUNT_MAX
#define PROC_MESSAGE_COUNT_MAX 5
#endif

#define	ISNPCLIVE	1
//#define TEST_SERVER

extern INDEX net_bLerping;
extern FLOAT net_tmConnectionTimeout;
extern FLOAT net_tmProblemsTimeOut;
extern FLOAT net_tmDisconnectTimeout;
extern INDEX net_bReportClientTraffic;

extern CClientInterface cm_ciLocalClient;
extern TIME _tmLocalTick = -1.0f;
extern INDEX g_iCountry;

extern INDEX g_iQuestBookOpen;

FLOAT3D _vBasePosition;
BOOL    _bBasePositionSet;

#if DEBUG_LERPING

FLOAT avfStats[1000][4];
INDEX ctCounter = 0;
INDEX ctMax = sizeof(avfStats) / sizeof(avfStats[0]);

#endif // DEBUG_LERPING

// �÷��� Ÿ�� ���� ���� /////////////////////////////////////////////////
DWORD	_SetPlayStartTime = 0;
const DWORD	_IntervalTime = 60; // 60�� ����
const DWORD	_IntervalPlayCountTime = 1000 * 60 * _IntervalTime;
static DWORD _PlayTimeCount = 0;
//////////////////////////////////////////////////////////////////////////

// [100122: selo] ������ �ڵ��� ã�� ���μ��� ã�� ��ƾ
ULONG ProcIDFromWnd(HWND hwnd) // ������ �ڵ�� ���μ��� ���̵� ���  
{
	ULONG idProc;
	GetWindowThreadProcessId(hwnd, &idProc);
	return idProc;
}
// [100122: selo] �� �Լ��� ����Ǵ� �Լ� 
HWND GetWinHandle(ULONG pid) // ���μ��� ���̵�� ������ �ڵ� ���  
{
	HWND tempHwnd = FindWindow(NULL, NULL); // �ֻ��� ������ �ڵ� ã��  

	while (tempHwnd != NULL)
	{
		if (GetParent(tempHwnd) == NULL) // �ֻ��� �ڵ����� üũ, ��ư � �ڵ��� ���� �� �����Ƿ� �����ϱ� ����  
			if (pid == ProcIDFromWnd(tempHwnd))
				return tempHwnd;
		tempHwnd = GetWindow(tempHwnd, GW_HWNDNEXT); // ���� ������ �ڵ� ã��  
	}
	return NULL;
}
// [100122: selo] ��ŷ ���μ��� ã��
BOOL FindProcess(void)
{
	HANDLE      hProcessSnap = NULL;
	BOOL		Return = FALSE;

	PROCESSENTRY32 pe32 = { 0 };

	char buf[256];

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessSnap, &pe32))
	{
		do
		{
			HANDLE hProcess;
			// Get the actual priority class.            
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);

			if (hProcess != NULL)
			{
				HWND hWnd = GetWinHandle(pe32.th32ProcessID);

				GetClassName((HWND)hWnd, buf, 256);

				if (0 == strncmp(buf, "AutoIt", 6))
				{
					Return = TRUE;
					CPrintF("���� ������");
				}

				CloseHandle(hProcess);
			}
		} while (Process32Next(hProcessSnap, &pe32));
	}

	CloseHandle(hProcessSnap);

	return Return;
}

int LeaseWeaponErrChk(ULONG errType)
{
	CTString strMessage;
	BOOL nResult = FALSE;
	switch (errType)
	{
	case MSG_ITEM_LEND_WEAPON_ERROR_OK:
		strMessage = _S(3082, "������ ��� �뿩 �Ǿ����ϴ�.");
		nResult = TRUE;
		break;
	case MSG_ITEM_LEND_WEAPON_ERROR_FULLINVEN:
		strMessage = _S(265, "�κ��丮 ������ �����մϴ�.");
		break;
	case MSG_ITEM_LEND_WEAPON_ERROR_NOMONEY:
		strMessage = _S(306, "������ �����մϴ�.");
		break;
	case MSG_ITEM_LEND_WEAPON_ERROR_FAIL:
		strMessage = _S(16, "�˼� ���� ������ �߻��߽��ϴ�.");
		break;
	case MSG_ITEM_LEND_TIMEOUT:
		strMessage = _S(3064, "�뿩 �Ⱓ�� ����Ǿ����ϴ�.");
		break;
	}

	_pNetwork->ClientSystemMessage(strMessage);
	return nResult;
}

//wooss 050808 inner function
void ConfirmMsgProc(UBYTE subType, UBYTE errorType = NULL, CTString charName = CTString("PLAYER"))
{
	CTString		strTitle = _S(191, "Ȯ��");
	CTString		strMsg;
	CUIMsgBox_Info	msgInfo;

	switch (subType)
	{
	case MSG_WARP_TO_REQ:
	{
		CUIManager* pUIManager = CUIManager::getSingleton();

		if (pUIManager->DoesMessageBoxExist(MSGCMD_WARP_TO_REQ_CALL) == TRUE)
		{
			// �޽����� ��� ��û ���� �ݴ´�
			CTString PreCallName = pUIManager->GetMessageBox(MSGCMD_WARP_TO_REQ_CALL)->GetInputBox().GetString();
			_pNetwork->SendWarpItemMessage(MSG_WARP_TO, PreCallName, FALSE);
			pUIManager->CloseMessageBox(MSGCMD_WARP_TO_REQ_CALL);
		}

		strMsg.PrintF(_S(2124, "%s�Բ��� ��ſ��� �����̵��� �Ϸ��� �մϴ�. ���� �Ͻðڽ��ϱ�?"), charName);
		msgInfo.SetMsgBoxInfo(strTitle, UMBS_YESNO, UI_NONE, MSGCMD_WARP_TO_REQ_CALL);
		msgInfo.AddString(strMsg);
		pUIManager->CreateMessageBox(msgInfo);
		pUIManager->GetMessageBox(MSGCMD_WARP_TO_REQ_CALL)->GetInputBox().SetString(charName.str_String);
	}
	break;
	case MSG_WARP_TAKE_REQ:
	{
		CUIManager* pUIManager = CUIManager::getSingleton();

		if (pUIManager->DoesMessageBoxExist(MSGCMD_WARP_TAKE_REQ_CALL) == TRUE)
		{
			// �޽����� ��� ��û ���� �ݴ´�
			CTString PreCallName = pUIManager->GetMessageBox(MSGCMD_WARP_TAKE_REQ_CALL)->GetInputBox().GetString();
			_pNetwork->SendWarpItemMessage(MSG_WARP_TAKE, PreCallName, FALSE);
			pUIManager->CloseMessageBox(MSGCMD_WARP_TAKE_REQ_CALL);
		}

		strMsg.PrintF(_S(2125, "%s�Բ��� ����� ��ȯ�� ��û�ϼ̽��ϴ�. ���� �Ͻðڽ��ϱ�?"), charName);
		msgInfo.SetMsgBoxInfo(strTitle, UMBS_YESNO, UI_NONE, MSGCMD_WARP_TAKE_REQ_CALL);
		msgInfo.AddString(strMsg);
		pUIManager->CreateMessageBox(msgInfo);
		pUIManager->GetMessageBox(MSGCMD_WARP_TAKE_REQ_CALL)->GetInputBox().SetString(charName.str_String);
	}
	break;
	case MSG_WARP_ERROR:
	{
		switch (errorType)
		{
		case MSG_WARP_ERROR_NOTALLOW:
		{
			strMsg.PrintF(_S(2126, "%s�Բ��� �̵� ��û�� �����Ͽ����ϴ�. ���� �̵��� ��ҵ˴ϴ�."), charName);
			msgInfo.SetMsgBoxInfo(strTitle, UMBS_OK, UI_NONE, MSGCMD_NULL);
			msgInfo.AddString(strMsg);
			CUIManager::getSingleton()->CreateMessageBox(msgInfo);
			_pNetwork->SendWarpCancel();
		}
		break;

		case MSG_WARP_ERROR_NOTALLOWZONE:
		{
			strMsg = _S(2127, "���� �̵� ���� ������ �ƴմϴ�.(�ٸ� ���̰ų� �۽��δ��������� ����� �� �����ϴ�.)");
			msgInfo.SetMsgBoxInfo(strTitle, UMBS_OK, UI_NONE, MSGCMD_NULL);
			msgInfo.AddString(strMsg);
			CUIManager::getSingleton()->CreateMessageBox(msgInfo);
		}
		break;

		case MSG_WARP_ERROR_NOTCHAR:
		{
			strMsg = _S(1628, "�ش� �ɸ��Ͱ� ���� ���� �ʰų� [��������] �����Դϴ�.");
			msgInfo.SetMsgBoxInfo(strTitle, UMBS_OK, UI_NONE, MSGCMD_NULL);
			msgInfo.AddString(strMsg);
			CUIManager::getSingleton()->CreateMessageBox(msgInfo);
		}
		break;

		case MSG_WARP_ERROR_CANCEL:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();

			if (pUIManager->DoesMessageBoxExist(MSGCMD_WARP_TO_REQ_CALL))
				pUIManager->CloseMessageBox(MSGCMD_WARP_TO_REQ_CALL);
			if (pUIManager->DoesMessageBoxExist(MSGCMD_WARP_TAKE_REQ_CALL))
				pUIManager->CloseMessageBox(MSGCMD_WARP_TAKE_REQ_CALL);
			pUIManager->GetChattingUI()->AddSysMessage(_S(340, "�̵��� ��ҵǾ����ϴ�."));
		}
		break;
		}
		UIMGR()->SetCSFlagOff(CSF_TELEPORT);
	}
	break;
	}
}

// FIXME : ��ӵ� SMC ���� �ϵ� �ڵ��Ǿ��ִµ�...
ENGINE_API void SetDropItemModel(CEntity* penEntity, CItemData* pItemData, CItemTarget* pTarget)
{
	penEntity->InitAsSkaModel();
	char* szEffectName = NULL;
	INDEX animID = -1;

	if (pItemData->GetType() == CItemData::ITEM_ETC)
	{
		if (pItemData->GetSubType() == CItemData::ITEM_ETC_EVENT)		// �̺�Ʈ �������̶��,
		{
			if (pItemData->GetItemIndex() == 1393) {
				penEntity->SetSkaModel(pItemData->GetItemSmcFileName());
				szEffectName = "server_event_drop";
			}
			else penEntity->SetSkaModel(MODEL_GIFT);
		}
		else if (pItemData->GetSubType() != CItemData::ITEM_ETC_MONEY)
		{
			if (pItemData->GetItemIndex() == 723)//������
			{
				penEntity->SetSkaModel("data\\item\\common\\item_moonstone.smc");
				animID = penEntity->GetModelInstance()->FindFirstAnimationID();
				szEffectName = "Item MoonStone";
			}
			else if (pItemData->GetItemIndex() == 2844) // ī���� ���ü�
			{
				penEntity->SetSkaModel("data\\item\\common\\item_goje_twn.smc");
				szEffectName = "Item GOJE twn";
			}
			else if (pItemData->GetItemIndex() == 85)//�������ü�
			{
				penEntity->SetSkaModel("data\\item\\common\\item_goje.smc");
				szEffectName = "Item GOJE";
			}
			else if (pItemData->GetItemIndex() == 779)//�ʰ������ü�
			{
				penEntity->SetSkaModel("Data\\Item\\Common\\item_lightstone.smc");
				szEffectName = "Item SGOJE";
			}
			else if (pItemData->GetItemIndex() == 974)//����� ���ü� wooss 051026 -> �ҽ� ���� �븸 ����(060320)
			{
				penEntity->SetSkaModel("Data\\Item\\Common\\item_goje_lucky.smc");
				szEffectName = "Item LGOJE";
			}
			else if (pItemData->GetItemIndex() == 3888 || pItemData->GetItemIndex() == 6097 || pItemData->GetItemIndex() == 6650)
			{
				// ��ȭ�� �� �Ƹ� ����Ʈ �߰� ITS 15517
				penEntity->SetSkaModel(pItemData->GetItemSmcFileName());
				szEffectName = "Item GOJE_blue";
			}
			else if (pItemData->GetItemIndex() == 3889 || pItemData->GetItemIndex() == 4968 ||
				pItemData->GetItemIndex() == 6098 || pItemData->GetItemIndex() == 6649)
			{
				// �Ǹ��� �� �Ƹ� ����Ʈ �߰� ITS 15517
				penEntity->SetSkaModel(pItemData->GetItemSmcFileName());
				szEffectName = "Item GOJE_red";
			}
			// 1482 : �౸�� 1484 :�����
			else if (pItemData->GetItemIndex() == 1482 || pItemData->GetItemIndex() == 1484) {
				penEntity->SetSkaModel(pItemData->GetItemSmcFileName());
			}
			else if (pItemData->GetItemIndex() >= 1579 && pItemData->GetItemIndex() <= 1588)
			{// ���� �ڽ�
				penEntity->SetSkaModel(pItemData->GetItemSmcFileName());
			}
			// WSS_MINIGAME 070423 -------------------------------------------->>
			// 2329 �����ۺ��� smc ���ϴ�� �����Ŵ
			else if (pItemData->GetItemIndex() >= 2329)
			{
				penEntity->SetSkaModel(pItemData->GetItemSmcFileName());
			}
			// ----------------------------------------------------------------<<
			else
			{
				penEntity->SetSkaModel(MODEL_TREASURE);
			}
		}
	}
	else if (pItemData->GetType() == CItemData::ITEM_WEAPON)
	{
		if (pItemData->GetSubType() == CItemData::ITEM_WEAPON_TWOSWORD || pItemData->GetSubType() == CItemData::ITEM_WEAPON_DAGGER)
		{
			CTString tStr;
			tStr.PrintF("%s", pItemData->GetItemSmcFileName());

			if (tStr.ReplaceSubstr(CTString("Weapon"), CTString("Weapon\\Drop")) == FALSE)
				tStr.ReplaceSubstr(CTString("weapon"), CTString("Weapon\\Drop"));

			penEntity->SetSkaModel(tStr);
		}
		else if (pItemData->GetSubType() == CItemData::ITEM_WEAPON_SOUL)
		{
			penEntity->SetSkaModel(MODEL_DROP_WEAPON_NS);
			animID = penEntity->GetModelInstance()->FindFirstAnimationID();
		}
		else
			penEntity->SetSkaModel(pItemData->GetItemSmcFileName());
	}
	else if (pItemData->GetType() == CItemData::ITEM_SHIELD)
	{
		switch (pItemData->GetSubType())
		{
		case CItemData::ITEM_SHIELD_COAT:
           penEntity->SetSkaModel(MODEL_TREASURE);
			if (pItemData->GetJob() & MASK_TITAN)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_TI_BU);
			}
			else if (pItemData->GetJob() & MASK_HEALER)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_HW_BU);
			}
			else if (pItemData->GetJob() & MASK_KNIGHT)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_NI_BU);
			}
			else if (pItemData->GetJob() & MASK_MAGE)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_MA_BU);
			}
			else if (pItemData->GetJob() & MASK_ROGUE)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_RO_BU);
			}
			else if (pItemData->GetJob() & MASK_SOCERER)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_SO_BU);
			}
			else if (pItemData->GetJob() & MASK_NIGHTSHADOW)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_NS_BU);
			}
      #ifdef CHAR_EX_ROGUE
			else if (pItemData->GetJob() & MASK_EX_ROGUE)	// [2012/08/27 : Sora] EX�α� �߰�
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_RO_BU);
			}
        #endif
		#ifdef CHAR_EX_MAGE
			else if (pItemData->GetJob() & MASK_EX_MAGE)	// 2013/01/08 jeil EX������ �߰�
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_MA_BU);
			}
      #endif
			else if (pItemData->GetJob() & (1 << WILDPET_JOB))
			{
				penEntity->SetSkaModel(pItemData->GetItemSmcFileName());
			}
			break;
		case CItemData::ITEM_SHIELD_PANTS:
           penEntity->SetSkaModel(MODEL_TREASURE);
			if (pItemData->GetJob() & MASK_TITAN)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_TI_BD);
			}
			else if (pItemData->GetJob() & MASK_HEALER)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_HW_BD);
			}
			else if (pItemData->GetJob() & MASK_KNIGHT)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_NI_BD);
			}
			else if (pItemData->GetJob() & MASK_MAGE)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_MA_BD);
			}
			else if (pItemData->GetJob() & MASK_ROGUE)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_RO_BD);
			}
			else if (pItemData->GetJob() & MASK_SOCERER)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_SO_BD);
			}
			else if (pItemData->GetJob() & MASK_NIGHTSHADOW)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_NS_BD);
			}
      #ifdef CHAR_EX_ROGUE
			else if (pItemData->GetJob() & MASK_EX_ROGUE)	// [2012/08/27 : Sora] EX�α� �߰�
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_RO_BD);
			}
       #endif
		#ifdef CHAR_EX_MAGE
			else if (pItemData->GetJob() & MASK_EX_MAGE)	// 2013/01/08 jeil EX������ �߰� 
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_MA_BD);
			}
      #endif
			break;
		case CItemData::ITEM_SHIELD_GLOVE:
           penEntity->SetSkaModel(MODEL_TREASURE);
			if (pItemData->GetJob() & MASK_TITAN)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_TI_HN);
			}
			else if (pItemData->GetJob() & MASK_HEALER)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_HW_HN);
			}
			else if (pItemData->GetJob() & MASK_KNIGHT)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_NI_HN);
			}
			else if (pItemData->GetJob() & MASK_MAGE)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_MA_HN);
			}
			else if (pItemData->GetJob() & MASK_ROGUE)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_RO_HN);
			}
			else if (pItemData->GetJob() & MASK_SOCERER)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_SO_HN);
			}
			else if (pItemData->GetJob() & MASK_NIGHTSHADOW)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_NS_HN);
			}
      #ifdef CHAR_EX_ROGUE
			else if (pItemData->GetJob() & MASK_EX_ROGUE)	// [2012/08/27 : Sora] EX�α� �߰�
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_RO_HN);
			}
       #endif
		#ifdef CHAR_EX_MAGE
			else if (pItemData->GetJob() & MASK_EX_MAGE)	// 2013/01/08 jeil EX������ �߰� 
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_MA_HN);
			}
      #endif
			break;
		case CItemData::ITEM_SHIELD_SHOES:
           penEntity->SetSkaModel(MODEL_TREASURE);
			if (pItemData->GetJob() & MASK_TITAN)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_TI_FT);
			}
			else if (pItemData->GetJob() & MASK_HEALER)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_HW_FT);
			}
			else if (pItemData->GetJob() & MASK_KNIGHT)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_NI_FT);
			}
			else if (pItemData->GetJob() & MASK_MAGE)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_MA_FT);
			}
			else if (pItemData->GetJob() & MASK_ROGUE)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_RO_FT);
			}
			else if (pItemData->GetJob() & MASK_SOCERER)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_SO_FT);
			}
			else if (pItemData->GetJob() & MASK_NIGHTSHADOW)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_NS_FT);
			}
      #ifdef CHAR_EX_ROGUE
			else if (pItemData->GetJob() & MASK_EX_ROGUE)	// [2012/08/27 : Sora] EX�α� �߰�
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_RO_FT);
			}
        #endif
		#ifdef CHAR_EX_MAGE
			else if (pItemData->GetJob() & MASK_EX_MAGE)	// 2013/01/08 jeil EX������ �߰�
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_MA_FT);
			}
      #endif
			break;
		case CItemData::ITEM_SHIELD_HEAD:
		{
			if (pItemData->GetJob() & MASK_NIGHTSHADOW)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_NS_HD);
			}
			else
			{
				penEntity->SetSkaModel(MODEL_TREASURE);
			}
		}
		break;
		case CItemData::ITEM_SHIELD_BACKWING:
		{
			if (pItemData->GetJob() & MASK_NIGHTSHADOW)
			{
				penEntity->SetSkaModel(MODEL_DROPIEM_NS_WG);
			}
			else
			{
				penEntity->SetSkaModel(MODEL_TREASURE);
			}
		}
		break;
		case CItemData::ITEM_SHIELD_SHIELD:
			penEntity->SetSkaModel(MODEL_DROPIEM_NI_SHIELD);
			break;
		default:
			penEntity->SetSkaModel(MODEL_TREASURE);
			break;
		}
	}
	else if (pItemData->GetType() == CItemData::ITEM_ONCEUSE)
	{
		// [KH_070328] �ް� �̺�Ʈ ���� �߰�
		if (pItemData->GetItemIndex() == EASTER_EGGS || pItemData->GetItemIndex() == 6231)	// �Ϻ� 1�ֳ� ��� �ް� �߰�
		{
			penEntity->SetSkaModel(pItemData->GetItemSmcFileName());
			szEffectName = "Item LGOJE";
		}
		else if (pItemData->GetItemIndex() == 6593) // ���� �� [4/15/2011 ldy1978220]
		{
			penEntity->SetSkaModel(pItemData->GetItemSmcFileName());
			szEffectName = "egg";
		}
		else
		{
			penEntity->SetSkaModel(MODEL_TREASURE);
		}
	}
	else
	{
		penEntity->SetSkaModel(MODEL_TREASURE);
	}

	penEntity->Initialize();
	penEntity->FallDownToFloor();

	if (penEntity->GetModelInstance())
	{
		if (szEffectName)
		{
			CSkaTag tag;
			tag.SetName("__ROOT");
			penEntity->GetModelInstance()->m_tmSkaTagManager.Register(&tag);
			pTarget->item_pDropItemEffect = StartEffectGroup(szEffectName,
				&penEntity->GetModelInstance()->m_tmSkaTagManager,
				_pTimer->GetLerpedCurrentTick());
		}
		if (animID != -1)
		{
			penEntity->GetModelInstance()->AddAnimation(
				animID, AN_LOOPING | AN_CLEAR | AN_NORESTART, 1.0f, 0);
		}
	}
}

//0105
//CEntity* m_penEntity;

#define TOTAL_TAB	3
#define TOTAL_ROW	20
#define TOTAL_COL	5

#define ADDSERVERVALUE	1999

#define		ITEM_ARRANGE_START			(1 << 0)	// ������ ������ ����.
#define		ITEM_ARRANGE_END			(1 << 1)	// ������ ������ ��.

#define TEACHER_PRIZE_EVENT_2PAN4PAN				// �İ��� ���� ���� �̺�Ʈ

//#define RESTRICT_SOUND

// get a pseudo-random number (safe for network gaming)
ULONG CSessionState::Rnd(void) {
	//  ASSERTMSG(ses_bAllowRandom, "Use RND only in entity AI!");
		// NOTE: 
		// using multiplicative congruent method with Greanberger's lambda = 2^18+3
	ses_ulRandomSeed = ses_ulRandomSeed * 262147;
	ASSERT(ses_ulRandomSeed != 0);
	return ses_ulRandomSeed;
}

// reset random number generator (always randomizes to same sequence!)
void CSessionState::ResetRND(void)
{
	BOOL bOldAllow = ses_bAllowRandom;
	ses_bAllowRandom = TRUE;
	// random must start at a number different than zero!
	ses_ulRandomSeed = 0x87654321;
	// run rnd a few times to make it go random
	for (INDEX i = 0; i < 32; i++) {
		Rnd();
	}
	ses_bAllowRandom = bOldAllow;
}

/*
 * Constructor.
 */
CSessionState::CSessionState(void)
{
	TRACKMEM(Mem, "Network");
	ses_bKeepingUpWithTime = TRUE;
	ses_tmLastUpdated = -100;
	ses_bAllowRandom = TRUE;  // random allowed when not in game

	ses_bPause = FALSE;
	ses_bWantPause = FALSE;
	ses_bGameFinished = FALSE;
	ses_bWaitingForServer = FALSE;
	ses_strDisconnected = "";
	ses_ctMaxPlayers = 1;
	ses_bWaitAllPlayers = FALSE;
	ses_fRealTimeFactor = 1.0f;
	ses_ubNumLevelChanges = 0;

	// reset random number generator
	ResetRND();

	ses_tmLastTickTime = -1;
	ses_ulMsgId = 0;
	ses_bRestartLocalTime = FALSE;

	_tmLocalTick = -1.0f;
	//0105
	m_commIn[0] = NULL;
	m_commOut[0] = NULL;
	m_commInTmp[0] = NULL;
	m_pCmd = new CCmd(this);

	m_iRecentServer = -1;
	m_iRecentGroup = -1;

#ifdef	KALYDO
	int		i;
	for (i = 0; i < eKST_MAX; ++i)
	{
		m_pCmdKalydo[i] = NULL;
	}
#endif	// KALYDO	
	reg_packet();
	reg_packet_info();
	reg_packet_comm();
}

/*
 * Destructor.
 */
CSessionState::~CSessionState()
{
	//0105
	delete m_pCmd;
#ifdef	KALYDO
	int		i;
	for (i = 0; i < eKST_MAX; ++i)
	{
		if (m_pCmdKalydo[i] != NULL)
			delete m_pCmdKalydo[i];
		m_pCmdKalydo[i] = NULL;
	}
#endif	// KALYDO	
}

/*
 * Clear the object.
 */
void CSessionState::Stop(void)
{

	ses_bKeepingUpWithTime = TRUE;
	ses_tmLastUpdated = -100;
	ses_bAllowRandom = TRUE;  // random allowed when not in game
	ses_bPause = FALSE;
	ses_bWantPause = FALSE;
	ses_bGameFinished = FALSE;
	ses_bWaitingForServer = FALSE;
	ses_strDisconnected = "";
	ses_ctMaxPlayers = 1;
	ses_fRealTimeFactor = 1.0f;
	ses_bWaitAllPlayers = FALSE;
	ses_tmLastTickTime = -1;
	ses_ulMsgId = 0;

	// disable lerping
	_pTimer->DisableLerp();

#if DEBUG_LERPING

	CTFileStream f;
	f.Create_t(CTFILENAME("Temp\\Lerp.stats"), CTStream::CM_TEXT);
	for (INDEX i = 0; i < ctCounter; i++) {
		char strBuffer[256];
		sprintf(strBuffer, "%6.2f %6.2f %6.2f %6.2f",
			avfStats[i][0],
			avfStats[i][1],
			avfStats[i][2],
			avfStats[i][3]);
		f.PutLine_t(strBuffer);
	}
	f.Close();

#endif // DEBUG_LERPING
	/* //0522 kwon ����.
		CNetworkMessage nmConfirmDisconnect(MSG_REP_DISCONNECTED);
		if (_cmiComm.cci_bClientInitialized) {
		  _pNetwork->SendToServerReliable(nmConfirmDisconnect);
		}
	*/
	_cmiComm.Client_Close();

	// clear all old levels
	ForgetOldLevels();

	_pNetwork->ga_srvServer.srv_apltPlayers.Clear();
	_pNetwork->ga_srvServer.srv_apltPlayers.New(NET_MAXGAMEPLAYERS);
}

/*
 * Initialize session state and wait for game to be started.
 */
void CSessionState::Start_t(INDEX ctLocalPlayers)
{
	ses_bKeepingUpWithTime = TRUE;
	ses_tmLastUpdated = -100;
	// clear message stream
	ses_nsGameStream.Clear();
	ses_bAllowRandom = FALSE;  // random not allowed in game
	ses_bPause = FALSE;
	ses_bWantPause = FALSE;
	ses_bWaitingForServer = FALSE;
	ses_bGameFinished = FALSE;
	ses_strDisconnected = "";
	ses_ctMaxPlayers = 1;
	ses_fRealTimeFactor = 1.0f;
	ses_bWaitAllPlayers = FALSE;
	ses_iMissingSequence = -1;
	ses_tvMessageReceived.Clear();
	_pNetwork->ga_strRequiredMod = "";
	ses_tmLastTickTime = -1;
	ses_ulMsgId = 0;

	// reset random number generator
	ResetRND();

	// clear all old levels
	ForgetOldLevels();

#if DEBUG_LERPING
	// clear lerp stats
	ctCounter = 0;
#endif // DEBUG_LERPING

	// ses_LastProcessedTick and ses_LastReceivedTick tick counters are
	// irrelevant now, will be initialized when initialization message
	// from server is received, no need to set them here

	// if this computer is server
	if (_pNetwork->IsServer()) {
		// initialize local client
		_cmiComm.Client_Init_t(0UL);
		// connect as main session state
		try {
			Start_AtServer_t();
		}
		catch (char*) {
			_cmiComm.Client_Close();
			throw;
		}

		// if this computer is client
	}
	else {
		// connect client to server computer
		_cmiComm.Client_Init_t((char*)(const char*)_pNetwork->ga_strServerAddress);
	}
	ses_tvMessageReceived = _pTimer->GetHighPrecisionTimer();
}
//! ���� ��ŸƮ.
void CSessionState::Start_AtServer_t(void)     // throw char *
{
	//! ���� Ŭ���̾�Ʈ�� ������ ��û�Ѵ�.
	// send registration request
	CNetworkMessage nmRegisterMainSessionState((UBYTE)MSG_REQ_CONNECTLOCALSESSIONSTATE);
	ses_sspParams.Update();
	nmRegisterMainSessionState << ses_sspParams;
	//! ���Լ� �ȿ��� ���� ������Ʈ�� ����..
	_pNetwork->SendToServerReliable(nmRegisterMainSessionState);

	TIME tmTimeout = net_tmConnectionTimeout;
	if (_pNetwork->IsServer()) {
		tmTimeout = 5.0f;
	}
	//! 5�ʵ��� 0.05�� �������� 
	for (TIME tmWait = 0; tmWait < tmTimeout * 1000;
		Sleep(NET_WAITMESSAGE_DELAY), tmWait += NET_WAITMESSAGE_DELAY) {

		//! ���� ������Ʈ.
		// handle server messages
		_cmiComm.Server_Update();
		//! ������ ��ŸƮ �Ǿ��ٸ�,
		if (_pNetwork->ga_srvServer.srv_bActive) {
			// handle all incoming messages
			_pNetwork->ga_srvServer.HandleAll();
		}
		//! ���� ���� loop
		_pNetwork->ga_srvServer.ServerLoop();
		//! �� ���� ������Ʈ
		_cmiComm.Server_Update();
		//! ���� Ŭ���̾�Ʈ ������Ʈ.
		if (_cmiComm.Client_Update() == FALSE) {
			break;
		}

		//! ����Ŭ���̾�Ʈ�� ������ ������ �����̾�� �޽����� ��ٸ���.
		// wait for message to come
		CNetworkMessage nmReceived;
		if (!_pNetwork->ReceiveFromServerReliable(nmReceived)) {
			continue;
		}
		//! �� �޽����� �ʱ�ȭ �޽������,
		// if this is the init message
		if (nmReceived.GetType() == MSG_REP_CONNECTLOCALSESSIONSTATE) {
			// just adjust your tick counters
			nmReceived >> ses_tmLastProcessedTick;
			nmReceived >> ses_iLastProcessedSequence;
			ses_tmInitializationTick = -1.0f;
			ses_tmInitializationTick2 = -1.0f;
			ses_tvMessageReceived = _pTimer->GetHighPrecisionTimer();
			//! for�� ��������.
			// finish waiting
			return;
			// otherwise
		}
		else {
			// it is invalid message
			ThrowF_t(TRANS("Invalid message while waiting for server session registration"));
		}

		// if client is disconnected
		if (!_cmiComm.Client_IsConnected()) {
			// quit
			ThrowF_t(TRANS("Client disconnected"));
		}
	}
	ThrowF_t(TRANS("Timeout while waiting for server session registration"));
}

//������ ���� ����	//(5th Closed beta)(0.2)
BOOL PCStartEffectGroup(const char* szEffectGroupName, SLONG slPCIndex, CEntity* penPC, float fDelayTime)
{
	float fStartTime = _pTimer->GetLerpedCurrentTick() + fDelayTime;

	//�� ĳ���̸�
	if (_pNetwork->MyCharacterInfo.index == slPCIndex)
	{
		if (CEntity::GetPlayerEntity(0) != NULL
			&& CEntity::GetPlayerEntity(0)->en_pmiModelInstance != NULL)
		{
			StartEffectGroup(szEffectGroupName
				, &CEntity::GetPlayerEntity(0)->en_pmiModelInstance->m_tmSkaTagManager
				//, _pTimer->GetLerpedCurrentTick());
				, fStartTime);
			return TRUE;
		}
	}
	//�� ĳ���� �ƴϸ�
	else
	{
		if (penPC == NULL)
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, slPCIndex);

			if (pObject != NULL)
			{
				if (pObject->GetEntity() != NULL)
				{
					StartEffectGroup(szEffectGroupName
						, &(pObject->GetEntity()->en_pmiModelInstance->m_tmSkaTagManager)
						, fStartTime);
				}
				return TRUE;
			}
		}
		else
		{
			if (penPC != NULL && penPC->en_pmiModelInstance != NULL && penPC->en_pmiModelInstance->GetName() != "")
			{
				StartEffectGroup(szEffectGroupName, &(penPC->en_pmiModelInstance->m_tmSkaTagManager)
					//, _pTimer->GetLerpedCurrentTick() );
					, fStartTime);
				return TRUE;
			}
		}
	}
	return FALSE;
}
//������ ���� ��	//(5th Closed beta)(0.2)
BOOL ENGINE_API WildPetStartEffectGroup(const char* szEffectGroupName, SLONG slPetIndex, CEntity* penPet)
{
	if (penPet == NULL)
	{
		ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_WILDPET, slPetIndex);

		if (pObject != NULL)
		{
			CWildPetTarget* pTarget = static_cast<CWildPetTarget*>(pObject);

			if (pTarget->GetEntity() != NULL &&
				pTarget->GetEntity()->en_pmiModelInstance != NULL &&
				pTarget->GetEntity()->en_pmiModelInstance->GetName() != "")
			{
				StartEffectGroup(szEffectGroupName,
					&(pTarget->GetEntity()->en_pmiModelInstance->m_tmSkaTagManager),
					_pTimer->GetLerpedCurrentTick());

				return TRUE;
			}
		}
	}
	else
	{
		if (penPet != NULL && penPet->en_pmiModelInstance != NULL && penPet->en_pmiModelInstance->GetName() != "")
		{
			StartEffectGroup(szEffectGroupName, &(penPet->en_pmiModelInstance->m_tmSkaTagManager),
				_pTimer->GetLerpedCurrentTick());
			return TRUE;
		}
	}

	return FALSE;
}

// notify entities of level change
void CSessionState::SendLevelChangeNotification(CEntityEvent& ee)
{
	// for each entity in the world
	{
		FOREACHINDYNAMICCONTAINER(_pNetwork->ga_World.wo_cenEntities, CEntity, iten) {
			// if it should be notified
			if (iten->en_ulFlags & ENF_NOTIFYLEVELCHANGE) {
				// send the event
				iten->SendEvent(ee);
			}
		}
	}
}
//! �����κ��� ���� ��Ʈ���� ��ٸ���.
// wait for a stream to come from server
void CSessionState::WaitStream_t(CTMemoryStream& strmMessage, const CTString& strName,
	INDEX iMsgCode)
{

	// start waiting for server's response
	CallProgressHook_t(0.0f);
	SLONG slReceivedLast = 0;

	// repeat until timed out
	for (TIME tmWait = 0; tmWait < net_tmConnectionTimeout * 1000 / 3;
		Sleep(NET_WAITMESSAGE_DELAY), tmWait += NET_WAITMESSAGE_DELAY) {
		//!�������� �亯�� �ö����� ������.
		// update network connection sockets
		if (_cmiComm.Client_Update() == FALSE) {
			break;
		}



		// check how much is received so far
		SLONG slExpectedSize;
		SLONG slReceivedSize;
		//! ��Ŷ�� �����ִ� ���ۻ�����(slExpectedSize)�� 
	//! ������ ���ۿ� �����ϴ� �����̾�� ��Ŷ�� ������(slReceivedSize)�� ����.	
		_cmiComm.Client_PeekSize_Reliable(slExpectedSize, slReceivedSize);
		//! ���� ��Ŷ�� ���ۿ� �ȵ��Դٸ�,
			// if nothing received yet
		if (slExpectedSize == 0) {
			// progress with waiting
	  //! ��Ʈ��ũ ������Ʈ �Լ�����!!!
			CallProgressHook_t(tmWait / (net_tmConnectionTimeout * 1000));
			//! ���� ��Ŷ�� ���Դµ�,
				  // if something received
		}
		else {
			//! ���ο� ����Ÿ�� �޾Ҵٸ�,
				  // if some new data received
			if (slReceivedSize != slReceivedLast) {
				slReceivedLast = slReceivedSize;
				// reset timeout
				tmWait = 0;
			}
			// progress with receiving
			CallProgressHook_t((float)slReceivedSize / slExpectedSize);
		}

		//! ���࿡ ����� �� ���� ���ߴٸ�, continue.
			// if not everything received yet
		if (!_pNetwork->ReceiveFromServerReliable(strmMessage)) {
			// continue waiting
			continue;
		}
		//! ���� �޽����� �޾Ҵ�.�޽����� ù��° ��ġ�� �̵��Ͽ� ���̵� ����.
			// read message identifier
		strmMessage.SetPos_t(0);
		INDEX iID;
		strmMessage >> iID;
		//! �츮�� ��ٸ��� �޽��� �ڵ��̳�...ó���� MSG_REP_CONNECTREMOTESESSIONSTATE
			// if this is the message
		if (iID == iMsgCode) {
			// all ok
			CallProgressHook_t(1.0f);
			return;
			// if disconnected
		}
		/* //0522 kwon ����.
				else if (iID == MSG_INF_DISCONNECTED) {
				//! ��Ŀ��Ʈ Ȯ�� �޽��� ����.
				// confirm disconnect
				CNetworkMessage nmConfirmDisconnect(MSG_REP_DISCONNECTED);
				_pNetwork->SendToServerReliable(nmConfirmDisconnect);
				//! ��Ŀ��Ʈ ����
				// report the reason
				CTString strReason;
				strmMessage>>strReason;
				ses_strDisconnected = strReason;
				ThrowF_t(TRANS("Disconnected: %s\n"), strReason);
				// otherwise
				} */else {
				//! �̻��� �޽����� ����°���.
			   // it is invalid message
			ThrowF_t(TRANS("Invalid stream while waiting for %s"), strName);
		}

		// if client is disconnected
		if (!_cmiComm.Client_IsConnected()) {
			// quit
			ThrowF_t(TRANS("Client disconnected"));
		}
	}

	//	CNetworkMessage nmConfirmDisconnect(MSG_REP_DISCONNECTED);			
	//	_pNetwork->SendToServerReliable(nmConfirmDisconnect);


	ThrowF_t(TRANS("Timeout while waiting for %s"), strName);
}

// check if disconnected
BOOL CSessionState::IsDisconnected(void)
{
	return ses_strDisconnected != "";
}

// print an incoming chat message to console
void CSessionState::PrintChatMessage(ULONG ulFrom, const CTString& strFrom, const CTString& strMessage)
{
	CTString strSender;
	// if no sender players
	if (ulFrom == 0) {
		// take symbolic sender string
		strSender = strFrom;
		// if there are sender players
	}
	else {
		// for each sender player
		for (INDEX ipl = 0; ipl < _pNetwork->ga_srvServer.srv_apltPlayers.Count(); ipl++) {
			CPlayerTarget& plt = _pNetwork->ga_srvServer.srv_apltPlayers[ipl];
			if (plt.IsActive() && (ulFrom & (1UL << ipl))) {
				// add its name to the sender list
				if (strSender != "") {
					strSender += ", ";
				}
				strSender += plt.plt_penPlayerEntity->GetPlayerName();
			}
		}
	}

	// let eventual script addon process the message
	extern CTString cmd_strChatSender;
	extern CTString cmd_strChatMessage;
	extern CTString cmd_cmdOnChat;
	cmd_strChatSender = strSender;
	cmd_strChatMessage = strMessage;
	if (cmd_cmdOnChat != "") {
		_pShell->Execute(cmd_cmdOnChat);
	}

	// if proccessing didn't kill it
	if (cmd_strChatSender != "" && cmd_strChatMessage != "") {
		// print the message
		CPrintF("%s: ^o^cFFFFFF%s^r\n", (const char*)RemoveSpecialCodes(cmd_strChatSender), (const char*)RemoveSpecialCodes(cmd_strChatMessage));
	}
	extern INDEX net_ctChatMessages;
	net_ctChatMessages++;
}

/* NOTES:
1) New thinkers might be added by current ones, but it doesn't matter,
since they must be added forward in time and the list is sorted, so they
cannot be processed in this tick.
2) Thinkers/Movers can be removed during iteration, but the CEntityPointer
guarantee that they are not freed from memory.
*/

// do physics for a game tick
void CSessionState::HandleMovers(void)
{
	//  CPrintF("---- tick %g\n", _pTimer->CurrentTick());
		// put all movers in active list, pushing ones first
	CListHead lhActiveMovers, lhDoneMovers, lhDummyMovers;
	{
		FORDELETELIST(CMovableEntity, en_lnInMovers, _pNetwork->ga_World.wo_lhMovers, itenMover) {
			CMovableEntity* pen = itenMover;
			pen->en_lnInMovers.Remove();
			if (!(pen->en_ulFlags & ENF_DELETED)) {
				if ((pen->en_ulPhysicsFlags & EPF_ONBLOCK_MASK) == EPF_ONBLOCK_PUSH) {
					lhActiveMovers.AddHead(pen->en_lnInMovers);
				}
				else {
					lhActiveMovers.AddTail(pen->en_lnInMovers);
				}
			}
		}
	}


	// for each active mover
	{
		FORDELETELIST(CMovableEntity, en_lnInMovers, lhActiveMovers, itenMover) {
			// let it clear its temporary variables    

			if (itenMover->IsPlayer() && !itenMover->IsActionApplied()) {
				continue;
			}
			itenMover->ClearMovingTemp();
		}
	}

	// for each active mover
	{
		FORDELETELIST(CMovableEntity, en_lnInMovers, lhActiveMovers, itenMover) {
			// let it calculate its wanted parameters for this tick
			if (itenMover->IsPlayer() && !itenMover->IsActionApplied()) {
				continue;
			}
			itenMover->PreMoving();
		}
	}



	// while there are some active movers
	while (!lhActiveMovers.IsEmpty()) {
		// get first one
		CMovableEntity* penMoving = LIST_HEAD(lhActiveMovers, CMovableEntity, en_lnInMovers);
		CEntityPointer penCurrent = penMoving;  // just to keep it alive around the loop
		// first move it to done list (if not done, it will move back to world's movers)
		penMoving->en_lnInMovers.Remove();
		lhDoneMovers.AddTail(penMoving->en_lnInMovers);

		// let it do its own physics
		if (penMoving->IsPlayer() && !penMoving->IsActionApplied()) {
			//      lhActiveMovers.MoveList(_pNetwork->ga_World.wo_lhMovers);
			continue;
		}

		penMoving->DoMoving();

		// if any mover is re-added, put it to the end of active list
		lhActiveMovers.MoveList(_pNetwork->ga_World.wo_lhMovers);
	}


	// for each done mover
	{
		FORDELETELIST(CMovableEntity, en_lnInMovers, lhDoneMovers, itenMover) {
			// let it calculate its parameters after all movement has been resolved
			if (itenMover->IsPlayer() && !itenMover->IsActionApplied()) {
				continue;
			}
			itenMover->PostMoving();
		}
	}



	// for each done mover

	{
		FORDELETELIST(CMovableEntity, en_lnInMovers, lhDoneMovers, itenMover) {
			CMovableEntity* pen = itenMover;
			// if marked for removing from list of movers
			if (pen->en_ulFlags & ENF_INRENDERING) {
				// remove it
				pen->en_ulFlags &= ~ENF_INRENDERING;
				pen->en_lnInMovers.Remove();

				// this means that the entity has stopped moving, so 
				// force sending an update to the client
				if (pen->IsSentOverNet() && !pen->IsPlayer()) {
					ses_emEntityMessage.WritePlacementNotify(pen->en_ulID, TRUE);
					_pNetwork->ga_srvServer.SendMessage(ses_emEntityMessage);
				}

			}
			// let it clear its temporary variables
			if (itenMover->IsPlayer() && !itenMover->IsActionApplied()) {
				continue;
			}
			pen->ClearMovingTemp();
		}
	}

	// return all done movers to the world's list
	_pNetwork->ga_World.wo_lhMovers.MoveList(lhDummyMovers);
	_pNetwork->ga_World.wo_lhMovers.MoveList(lhDoneMovers);

	// handle all the sent events
	CEntity::HandleSentEvents();
}


// let the client move the entities around
void CSessionState::HandleMovers_client(void)
{
	ASSERT(!_pNetwork->IsServer());

	//  CPrintF("---- tick %g\n", _pTimer->CurrentTick());
		// put all movers in active list, pushing ones first
	CListHead lhActiveMovers, lhDoneMovers, lhDummyMovers;
	{
		FORDELETELIST(CMovableEntity, en_lnInMovers, _pNetwork->ga_World.wo_lhMovers, itenMover) {
			CMovableEntity* pen = itenMover;
			pen->en_lnInMovers.Remove();
			if (!(pen->en_ulFlags & ENF_DELETED)) {
				if ((pen->en_ulPhysicsFlags & EPF_ONBLOCK_MASK) == EPF_ONBLOCK_PUSH) {
					lhActiveMovers.AddHead(pen->en_lnInMovers);
				}
				else {
					lhActiveMovers.AddTail(pen->en_lnInMovers);
				}
			}
		}
	}

	// for each active mover
	{
		FORDELETELIST(CMovableEntity, en_lnInMovers, lhActiveMovers, itenMover) {
			// let it clear its temporary variables
			itenMover->ClearMovingTemp();
		}
	}

	// for each active mover
	{
		FORDELETELIST(CMovableEntity, en_lnInMovers, lhActiveMovers, itenMover) {
			// if this is the client and this is a locally created entity
			if (itenMover->IsSentOverNet()) {
				continue;
			}
			itenMover->PreMoving();
		}
	}

	// while there are some active movers
	while (!lhActiveMovers.IsEmpty()) {
		// get first one
		CMovableEntity* penMoving = LIST_HEAD(lhActiveMovers, CMovableEntity, en_lnInMovers);
		CEntityPointer penCurrent = penMoving;  // just to keep it alive around the loop
		// first move it to done list (if not done, it will move back to world's movers)
		penMoving->en_lnInMovers.Remove();
		lhDoneMovers.AddTail(penMoving->en_lnInMovers);

		//lhActiveMovers.MoveList(_pNetwork->ga_World.wo_lhMovers);

		// let it do its own physics                            
		if (penMoving->IsSentOverNet()) {
			penMoving->ApplyDeadReckoning();
			continue;
		}

		penMoving->DoMoving();

		// if any mover is re-added, put it to the end of active list
		lhActiveMovers.MoveList(_pNetwork->ga_World.wo_lhMovers);
	}

	// for each done mover
	{
		FORDELETELIST(CMovableEntity, en_lnInMovers, lhDoneMovers, itenMover) {
			// let it calculate its parameters after all movement has been resolved
			if (itenMover->IsSentOverNet()) {
				continue;
			}
			itenMover->PostMoving();
		}
	}


	// for each done mover
	{
		FORDELETELIST(CMovableEntity, en_lnInMovers, lhDoneMovers, itenMover) {
			CMovableEntity* pen = itenMover;
			// if marked for removing from list of movers
			if (pen->en_ulFlags & ENF_INRENDERING) {
				// remove it
				pen->en_ulFlags &= ~ENF_INRENDERING;
				pen->en_lnInMovers.Remove();
			}
			// let it clear its temporary variables
			pen->ClearMovingTemp();
		}
	}

	// return all done movers to the world's list
	_pNetwork->ga_World.wo_lhMovers.MoveList(lhDummyMovers);
	_pNetwork->ga_World.wo_lhMovers.MoveList(lhDoneMovers);
}


// do thinking for a game tick
void CSessionState::HandleTimers(TIME tmCurrentTick)
{
#define TIME_EPSILON 0.0001f
	IFDEBUG(TIME tmLast = 0.0f);

	// repeat
	CListHead& lhTimers = _pNetwork->ga_World.wo_lhTimers;
	FOREVER{
		// no entity found initially
		CRationalEntity * penTimer = NULL;
	// for each entity in list of timers
	FOREACHINLIST(CRationalEntity, en_lnInTimers, lhTimers, iten) {
		// if due after current time
		if (iten->en_timeTimer > tmCurrentTick + TIME_EPSILON) {
			// stop searching
			break;
		}
		// remember found entity, and stop searching
		penTimer = iten;
		break;
	}

	// if no entity is found
	if (penTimer == NULL) {
		// stop
		break;
	}

	// if this entity isn't locally created, remove it from the timer list and skip it
	if (!cm_ciLocalClient.ci_bClientLocal && cm_ciLocalClient.ci_bUsed && penTimer->IsSentOverNet() && penTimer->IsFlagOff(ENF_CLIENTHANDLING)) {
		// remove the timer from the list
		penTimer->en_timeTimer = THINKTIME_NEVER;
		penTimer->en_lnInTimers.Remove();
		continue;
	}

	extern INDEX net_bReportMiscErrors;
	// check that timers are propertly handled - client doesn't do thinking, so it doesn't check
//������ ���� ����	//(Zone Change System)(0.1)
		//if (_pNetwork->IsServer()) {
			//ASSERT(penTimer->en_timeTimer>tmCurrentTick-_pTimer->TickQuantum-TIME_EPSILON);
		//}
//������ ���� ��	//(Zone Change System)(0.1)
		//ASSERT(penTimer->en_timeTimer>=tmLast);
		IFDEBUG(tmLast = penTimer->en_timeTimer);

		// remove the timer from the list
		penTimer->en_timeTimer = THINKTIME_NEVER;
		penTimer->en_lnInTimers.Remove();
		// send timer event to the entity
		penTimer->SendEvent(ETimer());
	}

		// handle all the sent events
	CEntity::HandleSentEvents();
}


// do a warm-up run of the world for a few ticks
void CSessionState::WarmUpWorld(void)
{
#define WORLD_WORMUP_COUNT 20   // run 20 ticks to get stable
	ses_tmLastProcessedTick = _pNetwork->ga_srvServer.srv_tmLastProcessedTick = 0;
	ses_iLastProcessedSequence = _pNetwork->ga_srvServer.srv_iLastProcessedSequence = -1;
	// add a few empty all-action messages to the game stream
	for (INDEX iTick = 0; iTick < WORLD_WORMUP_COUNT; iTick++) {
		_pNetwork->ga_srvServer.srv_tmLastProcessedTick += _pTimer->TickQuantum;
		_pNetwork->ga_srvServer.srv_iLastProcessedSequence++;
		CNetworkStreamBlock nsbAllActions(MSG_SEQ_ALLACTIONS, _pNetwork->ga_srvServer.srv_iLastProcessedSequence);
		nsbAllActions << _pNetwork->ga_srvServer.srv_tmLastProcessedTick;
		nsbAllActions.Rewind();
		ses_nsGameStream.AddBlock(nsbAllActions);
	}

	// process the blocks
	ProcessGameStream();
}


/*
 * Process a game tick.
 */

void CSessionState::ProcessGameTick(CNetworkMessage& nmMessage, TIME tmCurrentTick)
{
	ASSERT(this != NULL);

	// copy the tick to process into tick used for all tasks
	_pTimer->SetCurrentTick(tmCurrentTick);
	_pfNetworkProfile.IncrementAveragingCounter();

	// random is allowed only here, during entity ai
	ses_bAllowRandom = TRUE;

	// clear the applied action flag for all players
	for (INDEX ctPlayers = 0; ctPlayers < NET_MAXGAMEPLAYERS; ctPlayers++) {
		if (_pNetwork->ga_srvServer.srv_apltPlayers[ctPlayers].plt_penPlayerEntity != NULL) {
			_pNetwork->ga_srvServer.srv_apltPlayers[ctPlayers].plt_penPlayerEntity->ClearActionApplied();
		}
	}

	// for all players in game
	INDEX iPlayer = 0;
	CPlayerAction paAction;
	FOREACHINSTATICARRAY(_pNetwork->ga_srvServer.srv_apltPlayers, CPlayerTarget, itplt)
	{
		// if player is active
		if (itplt->IsActive())
		{
			// while there are actions in this player's buffer
			while (itplt->HasBufferedActions())
			{
				itplt->GetActionPacket(paAction);

				CPlayerTarget* pptTarget = itplt;
				// if this is action number two for a certian player, perform it's moving operations      
				if (pptTarget->plt_penPlayerEntity->IsActionApplied())
				{
					pptTarget->plt_penPlayerEntity->ClearMovingTemp();
					pptTarget->plt_penPlayerEntity->PreMoving();
					pptTarget->plt_penPlayerEntity->DoMoving();
					pptTarget->plt_penPlayerEntity->PostMoving();
					pptTarget->plt_penPlayerEntity->ClearMovingTemp();
					CEntity::HandleSentEvents();
				}

				//Sleep(1);
				// apply the new action and mark it
				pptTarget->ApplyActionPacket(paAction);
				pptTarget->plt_penPlayerEntity->SetActionApplied();

				ses_emEntityMessage.WritePlayerAction(pptTarget->plt_penPlayerEntity->en_ulID, paAction);
				_pNetwork->ga_srvServer.SendMessage(ses_emEntityMessage);
			}
		}
		iPlayer++;
	}

	// handle all the sent events
	CEntity::HandleSentEvents();

	if (_pNetwork->IsServer() || _pNetwork->ga_bDemoPlay) {
		// do thinking
		HandleTimers(tmCurrentTick);

		// do physics
		HandleMovers();
	}

	// notify all entities of level change as needed
	if (_lphCurrent == LCP_INITIATED) {
		EPreLevelChange ePreChange;
		ePreChange.iUserData = _pNetwork->ga_iNextLevelUserData;
		SendLevelChangeNotification(ePreChange);
		CEntity::HandleSentEvents();
		_lphCurrent = LCP_SIGNALLED;
	}
	if (_lphCurrent == LCP_CHANGED) {
		EPostLevelChange ePostChange;
		ePostChange.iUserData = _pNetwork->ga_iNextLevelUserData;
		SendLevelChangeNotification(ePostChange);
		CEntity::HandleSentEvents();
		_lphCurrent = LCP_NOCHANGE;
	}

	// let the worldbase execute its tick function
	if (_pNetwork->ga_World.wo_pecWorldBaseClass != NULL
		&& _pNetwork->ga_World.wo_pecWorldBaseClass->ec_pdecDLLClass != NULL
		&& _pNetwork->ga_World.wo_pecWorldBaseClass->ec_pdecDLLClass->dec_OnWorldTick != NULL) {
		_pNetwork->ga_World.wo_pecWorldBaseClass->ec_pdecDLLClass->
			dec_OnWorldTick(&_pNetwork->ga_World);
	}
	// handle all the sent events
	CEntity::HandleSentEvents();

	ses_bAllowRandom = FALSE;

	// let eventual script do something on each tick
	extern FLOAT cmd_tmTick;
	extern CTString cmd_cmdOnTick;
	if (cmd_cmdOnTick != "") {
		cmd_tmTick = tmCurrentTick;
		_pShell->Execute(cmd_cmdOnTick);
	}
}

//! ���ӽ�Ʈ���� ó���Ѵ�.
/*
 * Process all eventual available gamestream blocks.
 */
void CSessionState::ProcessGameStream(void)
{

	// this is actually a compiler kludge - it messes up the stack pointer when compiling debug code 
	// this kludge gets rid of it 
#ifndef NDEBUG
	CSetFPUPrecision FPUPrecision(FPT_64BIT);
#endif 

	// repeat
	FOREVER{
		// calculate index of next expected sequence
		INDEX iSequence = ses_iLastProcessedSequence + 1;
	// get the stream block with that sequence
	CNetworkStreamBlock* pnsbBlock;
	//�����κ��� �� ���ӽ�Ʈ������ ������� ������ �о���δ�.
		CNetworkStream::Result res = ses_nsGameStream.GetBlockBySequence(iSequence, pnsbBlock);
		// if it is found
		if (res == CNetworkStream::R_OK)
		{
			// remember the message type
			int iMsgType = pnsbBlock->GetType();
			// remember the processed sequence
			ses_iLastProcessedSequence = iSequence;
			// process the stream block
			ProcessGameStreamBlock(*pnsbBlock);
			// remove the block from the stream
			pnsbBlock->RemoveFromStream();
			// delete network stream block
			DeleteNetworkStreamBlock(pnsbBlock);
			// remove eventual resent blocks that have already been processed
			ses_nsGameStream.RemoveOlderBlocksBySequence(ses_iLastProcessedSequence - 2);

			// if the message is all actions
			if (iMsgType == MSG_SEQ_ALLACTIONS) {
				// if playing a demo
				if (_pNetwork->ga_bDemoPlay) {
					// step demo sequence
					ses_tmLastDemoSequence += _pTimer->TickQuantum;
				}
			}

			// if it is not avaliable yet
			} if (res == CNetworkStream::R_BLOCKNOTRECEIVEDYET) {
				// finish
				return;
				//! ���� Ŭ���̾�Ʈ�� ���´�.
					// if it is missing
					}
			 else if (res == CNetworkStream::R_BLOCKMISSING) {

				// if it is a new sequence
				if (iSequence > ses_iMissingSequence) {
					ses_iMissingSequence = iSequence;
					// setup timeout
					ses_tvResendTime = _pTimer->GetHighPrecisionTimer();
					ses_tmResendTimeout = 0.1f;
				}

				// if timeout occured
				if (_pTimer->GetHighPrecisionTimer() > ses_tvResendTime + CTimerValue(ses_tmResendTimeout)) {

					_pNetwork->AddNetGraphValue(NGET_MISSING, 1.0f); // missing sequence

					// find how many are missing
					INDEX iNextValid = ses_nsGameStream.GetOldestSequenceAfter(iSequence);
					INDEX ctSequences = Max(iNextValid - iSequence, INDEX(1));

					// create a request for resending the missing packet
				CNetworkMessage nmResendRequest((UBYTE)MSG_REQUESTGAMESTREAMRESEND);
				nmResendRequest << iSequence;
				nmResendRequest << ctSequences;
				// send the request to the server
				_pNetwork->SendToServer(nmResendRequest);

				extern INDEX net_bReportMiscErrors;
				if (net_bReportMiscErrors) {
					CPrintF(TRANS("Session State: Missing sequences %d-%d(%d) timeout %g\n"),
						iSequence, iSequence + ctSequences - 1, ctSequences, ses_tmResendTimeout);
				}

				// increase the timeout
				ses_tvResendTime = _pTimer->GetHighPrecisionTimer();
				ses_tmResendTimeout *= 2.0f;
			}

				// finish
				return;
			}
	}

}

//! ���ӽ�Ʈ�� ������ ó��.
/*
 * Process a gamestream block.
 */
void CSessionState::ProcessGameStreamBlock(CNetworkMessage& nmMessage)
{
	// copy the tick to process into tick used for all tasks
	_pTimer->SetCurrentTick(ses_tmLastProcessedTick);

	// check message type
	switch (nmMessage.GetType())
	{
		/* //0522 kwon ����.
			// if removing a player
			case MSG_SEQ_REMPLAYER: {
					_pNetwork->AddNetGraphValue(NGET_NONACTION, 1.0f); // non-action sequence
					INDEX iPlayer;
					nmMessage>>iPlayer;      // player index

					if (_pNetwork->ga_srvServer.srv_apltPlayers[iPlayer].plt_penPlayerEntity == NULL) {
						extern INDEX net_bReportMiscErrors;
						if (net_bReportMiscErrors) {
							CPrintF(TRANS("Warning: trying to remove a non-existing player, index: %d\n"),iPlayer);
						}
						break;
					}

					// inform entity of disconnnection
					CPrintF(TRANS("%s left\n"), _pNetwork->ga_srvServer.srv_apltPlayers[iPlayer].plt_penPlayerEntity->GetPlayerName());
					_pNetwork->ga_srvServer.srv_apltPlayers[iPlayer].plt_penPlayerEntity->Disconnect();
					// deactivate the player
					_pNetwork->ga_srvServer.srv_apltPlayers[iPlayer].Deactivate();
					// handle all the sent events
					ses_bAllowRandom = TRUE;
					CEntity::HandleSentEvents();
					ses_bAllowRandom = FALSE;

				} break;
		*/
		// if changing character
	case MSG_SEQ_CHARACTERCHANGE:
	{
		_pNetwork->AddNetGraphValue(NGET_NONACTION, 1.0f); // non-action sequence
		INDEX iPlayer;
		CPlayerCharacter pcCharacter;
		nmMessage >> iPlayer >> pcCharacter;

		// change the character
		_pNetwork->ga_srvServer.srv_apltPlayers[iPlayer].plt_penPlayerEntity->CharacterChanged(pcCharacter);

		// handle all the sent events
		ses_bAllowRandom = TRUE;
		CEntity::HandleSentEvents();
		ses_bAllowRandom = FALSE;

		ses_emEntityMessage.WriteCharacterChange(_pNetwork->ga_srvServer.srv_apltPlayers[iPlayer].plt_penPlayerEntity->en_ulID, pcCharacter);
		_pNetwork->ga_srvServer.SendMessage(ses_emEntityMessage);

	} break;

	//! Ŭ���̾�Ʈ �׼��� �޾Ҵٸ�,
  // if receiving client actions
	case MSG_SEQ_ALLACTIONS:
	{
		// read time from packet
		TIME tmPacket;
		nmMessage >> tmPacket;    // packet time

		// time must be greater by one than that on the last packet received
		TIME tmTickQuantum = _pTimer->TickQuantum;
		TIME tmPacketDelta = tmPacket - ses_tmLastProcessedTick;
		if (!(Abs(tmPacketDelta - tmTickQuantum) < (tmTickQuantum / 10.0f))) {
			// report debug info

			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Session state: Mistimed MSG_ALLACTIONS: Last received tick %g, this tick %g\n"),
					ses_tmLastProcessedTick, tmPacket);
			}
		}
		// remember the received tick
		ses_tmLastProcessedTick = tmPacket;

		/* //0522 kwon ����.
					if (_pNetwork->IsServer() && _pNetwork->ga_srvServer.srv_bSendPause && _pNetwork->ga_srvServer.srv_bPauseValue) {
						ses_emEntityMessage.WritePause(_pNetwork->ga_srvServer.srv_bPauseValue,_pNetwork->ga_srvServer.srv_strPauser);
						_pNetwork->ga_srvServer.SendMessage(ses_emEntityMessage);
						_pNetwork->ga_srvServer.srv_bSendPause = FALSE;
						_pNetwork->ga_srvServer.srv_bPause = _pNetwork->ga_srvServer.srv_bPauseValue;
						CNetworkStreamBlock nsbPause(MSG_SEQ_PAUSE, ++_pNetwork->ga_srvServer.srv_iLastProcessedSequence);
						nsbPause<<(INDEX&)_pNetwork->ga_srvServer.srv_bPause;
						nsbPause<<_pNetwork->ga_srvServer.srv_strPauser;
						// put the message in buffer
						_pNetwork->ga_srvServer.srv_assoSessions[0].sso_nsBuffer.AddBlock(nsbPause);
					}
		*/
		INDEX iActiveSessions = 0;
		for (INDEX iSession = 1; iSession < _pNetwork->ga_srvServer.srv_assoSessions.Count(); iSession++) {
			if (_pNetwork->ga_srvServer.srv_assoSessions[iSession].sso_bTrackData) {
				iActiveSessions++;
			}
		}

		_pNetwork->ga_srvServer.StartNewTick(ses_tmLastProcessedTick);
		if (_pNetwork->ga_srvServer.srv_bRunning) {
			_pNetwork->ga_srvServer.srv_embSendBuffer.RequestTickAcknowledge(ses_tmLastProcessedTick, iActiveSessions);
		}

		// NOTE: if we got a tick, it means that all players have joined
		// don't wait for new players any more
		ses_bWaitAllPlayers = FALSE;

		// process the tick
		ProcessGameTick(nmMessage, tmPacket);

	} break;
	/* //0522 kwon ����.
		// if receiving pause message
		case MSG_SEQ_PAUSE:
		{
			_pNetwork->AddNetGraphValue(NGET_NONACTION, 1.0f); // non-action sequence

			BOOL bPauseBefore = ses_bPause;
			// read the pause state and pauser from it
			nmMessage>>(INDEX&)ses_bPause;
			CTString strPauser;
			nmMessage>>strPauser;
			// if paused by some other machine
			if (strPauser!=TRANS("Local machine")) {
				// report who paused
				if (ses_bPause!=bPauseBefore) {
					if (ses_bPause) {
						CPrintF(TRANS("Paused by '%s'\n"), strPauser);
					} else {
						CPrintF(TRANS("Unpaused by '%s'\n"), strPauser);
					}
				}
			}
			// must keep wanting current state
			ses_bWantPause = ses_bPause;
														} break;
	*/
	// otherwise
	default:
		// error
		ASSERT(FALSE);
	}
}

//-----------------------------------------------------------------------------
// Purpose: attach a player entity to this session 
// Input  : iPlayerIndex - 
//			&pcCharacter - 
//			&ulEntityID - 
//			&ulWeaponsID - 
//			&ulAnimatorID - 
//			iClient - 
//-----------------------------------------------------------------------------
void CSessionState::AddPlayer(
	INDEX iPlayerIndex,
	CPlayerCharacter& pcCharacter,
	ULONG& ulEntityID,
	ULONG& ulWeaponsID,
	ULONG& ulAnimatorID,
	INDEX iClient)
{
	ASSERT(iPlayerIndex >= 0);

	INDEX iPlayerWithName = 0;
	BOOL bFound = FALSE;
	CPlayerEntity* penNewPlayer = NULL;


	// if this is single player
	if (ses_ctMaxPlayers == 1)
	{
		// get the first player entity in the world
		penNewPlayer = _pNetwork->GetNthPlayerEntity(0);
		_pNetwork->ga_srvServer.srv_apltPlayers[0].plt_bActive = FALSE;
	}
	// if multiplayer
	else
	{
		// try to find a player entity with the same name as this player character
		// ���� �̸��� �÷��̾� ��ƼƼ�� �ִ��� ã�ƺ���.
		do
		{
			penNewPlayer = _pNetwork->GetNthPlayerEntityWithName(pcCharacter.pc_strName, iPlayerWithName);
			bFound = FALSE;
			if (penNewPlayer != NULL)
			{
				// if the names match, check if it's already active
				for (INDEX iTarget = 0; iTarget < NET_MAXGAMEPLAYERS; iTarget++)
				{
					// and if it is, skip it (someone is already playing with it)
					if (_pNetwork->ga_srvServer.srv_apltPlayers[iTarget].IsActive() &&
						_pNetwork->ga_srvServer.srv_apltPlayers[iTarget].plt_penPlayerEntity == penNewPlayer)
					{
						bFound = TRUE;
						break;
					}
				}
			}
			iPlayerWithName++;
		} while (bFound);
	}

	// activate the player target
	_pNetwork->ga_srvServer.srv_apltPlayers[iPlayerIndex].Activate(iClient);
	pcCharacter.pc_iPlayerIndex = iPlayerIndex;

	// if there is no entity with that character in the world
	// ���峻�� ĳ���� ��ƼƼ�� �������� �ʴ� ���.
	if (penNewPlayer == NULL)
	{
		// create an entity for it
		CPlacement3D pl(FLOAT3D(0.0f, 0.0f, 0.0f), ANGLE3D(0, 0, 0));
		try
		{
			CTFileName fnmPlayer = CTString("Classes\\Player.ecl"); // this must not be a dependency!
			penNewPlayer = (CPlayerEntity*)(_pNetwork->ga_World.CreateEntity_t(pl, fnmPlayer, ulEntityID, FALSE));
			// attach entity to client data
			_pNetwork->ga_srvServer.srv_apltPlayers[iPlayerIndex].AttachEntity(penNewPlayer);
			// attach the character to it
			penNewPlayer->en_pcCharacter = pcCharacter;
			// initialize the player      
			penNewPlayer->InitializePlayer(ulWeaponsID, ulAnimatorID);
		}
		catch (char* strError)
		{
			(void)strError;
			FatalError(TRANS("Cannot load Player class:\n%s"), strError);
		}
		if (!_pNetwork->IsPlayerLocal(penNewPlayer))
		{
			CPrintF(TRANS("%s joined\n"), (const char*)RemoveSpecialCodes(penNewPlayer->en_pcCharacter.GetNameForPrinting()));
		}
	}
	else
	{
		// attach entity to client data
		_pNetwork->ga_srvServer.srv_apltPlayers[iPlayerIndex].AttachEntity(penNewPlayer);
		// make it update its character
		penNewPlayer->CharacterChanged(pcCharacter);

		if (!_pNetwork->IsPlayerLocal(penNewPlayer))
		{
			CPrintF(TRANS("%s rejoined\n"), (const char*)RemoveSpecialCodes(penNewPlayer->en_pcCharacter.GetNameForPrinting()));
		}
	}

	ulEntityID = penNewPlayer->en_ulID;

}




// Set lerping factor for current frame.
void CSessionState::SetLerpFactor(CTimerValue tvNow)
{
	TIME tmLastTick;
	if (_pNetwork->IsServer())
	{
		tmLastTick = ses_tmLastProcessedTick;
	}
	else
	{
		tmLastTick = _tmLocalTick;
	}

	//������ ���� ���� �α��� ó�� �۾�	07.13
#ifndef FINALVERSION
	if (_pNetwork->IsPlayingDemo())
	{
		tvNow = CTimerValue(_pNetwork->ga_fDemoTimer);
		tmLastTick = _pNetwork->ga_tmNextDemoTick - _pTimer->TickQuantum;
	}
#endif	// FINALVERSION
	//������ ���� �� �α��� ó�� �۾�		07.13

		// if no lerping
	if (!net_bLerping)
	{
		// set lerping factor without lerping
		_pTimer->SetLerp(1.0f);
		_pTimer->SetCurrentTick(tmLastTick);
		return;
	}

	FLOAT fFactor = 0.0f;
	FLOAT fFactor2 = 0.0f;

	// ---- primary factor - used for prediction
	{
		// if lerping was never set before
		if (ses_tmInitializationTick < 0) {
			// initialize it
			ses_tvInitialization = tvNow;
			ses_tmInitializationTick = tmLastTick;
		}

		// get passed time from session state starting in precise time and in ticks
		FLOAT tmRealDelta = FLOAT((tvNow - ses_tvInitialization).GetSeconds())
			* _pNetwork->ga_fGameRealTimeFactor * _pNetwork->ga_sesSessionState.ses_fRealTimeFactor;
		FLOAT tmTickDelta = tmLastTick - ses_tmInitializationTick;
		// calculate factor
		fFactor = 1.0f - (tmTickDelta - tmRealDelta) / _pTimer->TickQuantum;

		// if the factor starts getting below zero
		if (fFactor < 0) {
			//CPrintF("Lerp=%.2f <0 @ %.2fs\n", fFactor, tmLastTick);
			// clamp it
			fFactor = 0.0f;
			// readjust timers so that it gets better
			ses_tvInitialization = tvNow;
			ses_tmInitializationTick = tmLastTick - _pTimer->TickQuantum;
		}
		if (fFactor > 1) {
			//CPrintF("Lerp=%.2f >1 @ %.2fs\n", fFactor, tmLastTick);
			// clamp it
			fFactor = 1.0f;
			// readjust timers so that it gets better
			ses_tvInitialization = tvNow;
			ses_tmInitializationTick = tmLastTick;
		}

#if DEBUG_LERPING

		avfStats[ctCounter][0] = tmRealDelta / _pTimer->TickQuantum;
		avfStats[ctCounter][1] = tmTickDelta / _pTimer->TickQuantum;
		avfStats[ctCounter][2] = fFactor;
		avfStats[ctCounter][3] = (tmLastTick / _pTimer->TickQuantum - 1.0f) + fFactor;
		ctCounter++;
		if (ctCounter >= ctMax) {
			ctCounter = 0;
		}
#endif // DEBUG_LERPING
	}

	// set lerping
	_pTimer->SetLerp(fFactor);
	_pTimer->SetLerp2(fFactor);
	_pTimer->SetCurrentTick(tmLastTick);

	static TIME tmOld = -1.0f;
	if (tmOld > 0 && fabs(tmLastTick - tmOld) > 0.01) {
		//    CPrintF("New tick: %7.4f\n",tmLastTick);
	}
	tmOld = tmLastTick;

}




/*
 * Read session state state from a stream.
 */
void CSessionState::Read_t(CTStream* pstr, BOOL bNetwork)  // throw char *
{
	// read time information and random seed

	//! ���� �б�
	INDEX iVersion = SESSIONSTATEVERSION_OLD;
	if (pstr->PeekID_t() == CChunkID("SESV")) {
		pstr->ExpectID_t("SESV");
		(*pstr) >> iVersion;
	}
	(*pstr) >> ses_tmLastProcessedTick;
	(*pstr) >> ses_iLastProcessedSequence;
	(*pstr) >> ses_ulRandomSeed;
	(*pstr) >> ses_ulSpawnFlags;
	(*pstr) >> ses_ctMaxPlayers;
	(*pstr) >> ses_bWaitAllPlayers;
	(*pstr) >> ses_bPause;
	(*pstr) >> ses_bGameFinished;
	if (iVersion >= SESSIONSTATEVERSION_WITHBULLETTIME) {
		(*pstr) >> ses_fRealTimeFactor;
	}
	ses_bWaitingForServer = FALSE;
	ses_bWantPause = ses_bPause;
	ses_strDisconnected = "";
	_pTimer->SetCurrentTick(ses_tmLastProcessedTick);

	// read session properties from stream
	(*pstr) >> _pNetwork->ga_strSessionName;
	pstr->Read_t(_pNetwork->ga_aubProperties, NET_MAXSESSIONPROPERTIES);

	//! bNetwork�� FALSE�� �ȵ����µ�? �Ѥ�?
	if (!bNetwork) {
		// read world and its state
		ReadWorldAndState_t(pstr);
	}
	else {
		//0130 //0203 ska��Ʈ�� ���̺����� ��� �ٽ� ��.
		ReadState_t(pstr);

	}

}


void CSessionState::ReadState_t(CTStream* pstr)   // throw char *
{

	//! ��� ��ƼƼ�� lock�Ǵ�.
	// prepare the world for loading 
	_pNetwork->ga_World.LockAll();
	//! ������ ���� ������Ʈ�� �о���δ�.
	// read world situation
	_pNetwork->ga_World.ReadState_net_t(pstr);
	//! �÷��̾� ���� �д´�.
		// read number of players
	INDEX ctPlayers;
	(*pstr) >> ctPlayers;
	ASSERT(ctPlayers == _pNetwork->ga_srvServer.srv_apltPlayers.Count());
	//! �÷��̾� ����ŭ ��Ʈ������ �÷��̾�Ÿ�� ������ �д´�.
	// for all clients
	FOREACHINSTATICARRAY(_pNetwork->ga_srvServer.srv_apltPlayers, CPlayerTarget, itclt) {
		// read from stream
		itclt->Read_t(pstr);
	}
	//! lock�� �����Ѵ�.
	_pNetwork->ga_World.UnlockAll();

};

void CSessionState::ReadWorldAndState_t(CTStream* pstr)   // throw char *
{
	// check engine build disallowing reinit
	BOOL bNeedsReinit;
	_pNetwork->CheckVersion_t(*pstr, FALSE, bNeedsReinit);
	ASSERT(!bNeedsReinit);

	// read world filename from stream
	(*pstr) >> _pNetwork->ga_fnmWorld;

	if (CTFileName(pstr->GetDescription()).FileExt() == ".dem" &&
		GetFileTimeStamp_t(pstr->GetDescription()) <= GetFileTimeStamp_t(_pNetwork->ga_fnmWorld)) {
		ThrowF_t(
			TRANS("Cannot play demo because file '%s'\n"
				"is older than file '%s'!\n"),
			CTString(pstr->GetDescription()),
			CTString(_pNetwork->ga_fnmWorld));
	}

	// prepare the world for loading
	_pNetwork->ga_World.Clear();
	_pNetwork->ga_World.LockAll();
	// load the world brushes from the world file
	_pNetwork->ga_World.LoadBrushes_t(_pNetwork->ga_fnmWorld);
	// read world situation
	_pNetwork->ga_World.ReadState_t(pstr);

	// create an empty list for relinking timers
	CListHead lhNewTimers;
	// read number of entities in timer list
	pstr->ExpectID_t("TMRS");   // timers
	INDEX ctTimers;
	*pstr >> ctTimers;
	//  ASSERT(ctTimers == _pNetwork->ga_World.wo_lhTimers.Count());
		// for each entity in the timer list
	{
		for (INDEX ienTimer = 0; ienTimer < ctTimers; ienTimer++) {
			// read its index in container of all entities
			INDEX ien;
			*pstr >> ien;
			// get the entity
			CRationalEntity* pen = (CRationalEntity*)_pNetwork->ga_World.EntityFromID(ien);
			// remove it from the timer list and add it at the end of the new timer list
			if (pen->en_lnInTimers.IsLinked()) {
				pen->en_lnInTimers.Remove();
				lhNewTimers.AddTail(pen->en_lnInTimers);
			}
		}
	}
	// use the new timer list instead the old one
	ASSERT(_pNetwork->ga_World.wo_lhTimers.IsEmpty());
	_pNetwork->ga_World.wo_lhTimers.MoveList(lhNewTimers);

	// create an empty list for relinking movers
	CListHead lhNewMovers;
	// read number of entities in mover list
	pstr->ExpectID_t("MVRS");   // movers
	INDEX ctMovers;
	*pstr >> ctMovers;
	ASSERT(ctMovers == _pNetwork->ga_World.wo_lhMovers.Count());
	// for each entity in the mover list
	{
		for (INDEX ienMover = 0; ienMover < ctMovers; ienMover++) {
			// read its index in container of all entities
			INDEX ien;
			*pstr >> ien;
			// get the entity
			CMovableEntity* pen = (CMovableEntity*)_pNetwork->ga_World.EntityFromID(ien);
			// remove it from the mover list and add it at the end of the new mover list
			if (pen->en_lnInMovers.IsLinked()) {
				pen->en_lnInMovers.Remove();
			}
			lhNewMovers.AddTail(pen->en_lnInMovers);
		}
	}
	// use the new mover list instead the old one
	ASSERT(_pNetwork->ga_World.wo_lhMovers.IsEmpty());
	_pNetwork->ga_World.wo_lhMovers.MoveList(lhNewMovers);

	// read number of players
	INDEX ctPlayers;
	(*pstr) >> ctPlayers;
	ASSERT(ctPlayers == _pNetwork->ga_srvServer.srv_apltPlayers.Count());
	// for all clients
	FOREACHINSTATICARRAY(_pNetwork->ga_srvServer.srv_apltPlayers, CPlayerTarget, itclt) {
		// read from stream
		itclt->Read_t(pstr);
	}

	_pNetwork->ga_World.UnlockAll();
}

void CSessionState::ReadRememberedLevels_t(CTStream* pstr)
{
	pstr->ExpectID_t("RLEV"); // remembered levels
	// read count of remembered levels
	INDEX ctLevels;
	(*pstr) >> ctLevels;
	// for each level
	for (INDEX iLevel = 0; iLevel < ctLevels; iLevel++) {
		// create it
		CRememberedLevel* prl = new CRememberedLevel;
		// read it
		(*pstr) >> prl->rl_strFileName;
		//prl->rl_strmSessionState.
		// use readstream() !!!! @@@@

	}

};

//! ��Ʈ���� ���� ������Ʈ�� ����.
/*
 * Write session state state into a stream.
 */
void CSessionState::Write_t(CTStream* pstr, BOOL bNetwork)  // throw char *
{
	pstr->WriteID_t("SESV");
	(*pstr) << INDEX(SESSIONSTATEVERSION_WITHBULLETTIME);
	// write time information and random seed
	(*pstr) << ses_tmLastProcessedTick;
	(*pstr) << ses_iLastProcessedSequence;
	(*pstr) << ses_ulRandomSeed;
	(*pstr) << ses_ulSpawnFlags;
	(*pstr) << ses_ctMaxPlayers;
	(*pstr) << ses_bWaitAllPlayers;
	(*pstr) << ses_bPause;
	(*pstr) << ses_bGameFinished;
	(*pstr) << ses_fRealTimeFactor;
	// write session properties to stream
	(*pstr) << _pNetwork->ga_strSessionName;
	pstr->Write_t(_pNetwork->ga_aubProperties, NET_MAXSESSIONPROPERTIES);


	if (!bNetwork) {
		// read world and its state
		WriteWorldAndState_t(pstr);
	}
	else {
		WriteState_t(pstr);
	}

}

//! Ŭ���̾�Ʈ�� ���� ���� ������Ʈ�� ����.
void CSessionState::WriteState_t(CTStream* pstr)   // throw char *
{
	// write world situation
	_pNetwork->ga_World.LockAll();
	//! ���� ������Ʈ�� ����.
	_pNetwork->ga_World.WriteState_net_t(pstr);

	//! �÷��̾� ���� ����.
	// write players - their number and data for each one
	// write number of clients
	(*pstr) << _pNetwork->ga_srvServer.srv_apltPlayers.Count();
	// for all clients
	FOREACHINSTATICARRAY(_pNetwork->ga_srvServer.srv_apltPlayers, CPlayerTarget, itclt) {
		// write to stream
		itclt->Write_t(pstr);
	}

	_pNetwork->ga_World.UnlockAll();
}

void CSessionState::WriteWorldAndState_t(CTStream* pstr)   // throw char *
{
	// save engine build
	_pNetwork->WriteVersion_t(*pstr);

	// write world filename to stream
	(*pstr) << _pNetwork->ga_fnmWorld;

	// write world situation
	_pNetwork->ga_World.LockAll();
	_pNetwork->ga_World.WriteState_t(pstr, TRUE);

	// write number of entities in timer list
	pstr->WriteID_t("TMRS");   // timers
	CListHead& lhTimers = _pNetwork->ga_World.wo_lhTimers;
	*pstr << lhTimers.Count();
	// for each entity in the timer list
	{
		FOREACHINLIST(CRationalEntity, en_lnInTimers, lhTimers, iten) {
			// save its index in container
			*pstr << iten->en_ulID;
		}
	}

	// write number of entities in mover list
	pstr->WriteID_t("MVRS");   // movers
	CListHead& lhMovers = _pNetwork->ga_World.wo_lhMovers;
	*pstr << lhMovers.Count();
	// for each entity in the mover list
	{
		FOREACHINLIST(CMovableEntity, en_lnInMovers, lhMovers, iten) {
			// save its index in container
			*pstr << iten->en_ulID;
		}
	}

	// write number of clients
	(*pstr) << _pNetwork->ga_srvServer.srv_apltPlayers.Count();
	// for all clients
	FOREACHINSTATICARRAY(_pNetwork->ga_srvServer.srv_apltPlayers, CPlayerTarget, itclt) {
		// write to stream
		itclt->Write_t(pstr);
	}

	_pNetwork->ga_World.UnlockAll();
}

void CSessionState::WriteRememberedLevels_t(CTStream* pstr)
{
	// use writestream() !!!! @@@@

};

// remember current level
void CSessionState::RememberCurrentLevel(const CTString& strFileName)
{
	// if level is already remembered
	for (;;) {
		CRememberedLevel* prlOld = FindRememberedLevel(strFileName);
		if (prlOld == NULL) {
			break;
		}
		// remove it
		prlOld->rl_lnInSessionState.Remove();
		delete prlOld;
	}

	// create new remembered level
	CRememberedLevel* prlNew = new CRememberedLevel;
	ses_lhRememberedLevels.AddTail(prlNew->rl_lnInSessionState);
	// remember it
	prlNew->rl_strFileName = strFileName;
	WriteWorldAndState_t(&prlNew->rl_strmSessionState);
}

// find a level if it is remembered
CRememberedLevel* CSessionState::FindRememberedLevel(const CTString& strFileName)
{
	{
		FOREACHINLIST(CRememberedLevel, rl_lnInSessionState, ses_lhRememberedLevels, itrl) {
			CRememberedLevel& rl = *itrl;
			if (rl.rl_strFileName == strFileName) {
				return &rl;
			}
		}
	}
	return NULL;
}

// restore some old level
void CSessionState::RestoreOldLevel(const CTString& strFileName)
{
	// find the level
	CRememberedLevel* prlOld = FindRememberedLevel(strFileName);
	// it must exist
	ASSERT(prlOld != NULL);
	// restore it
	try {
		prlOld->rl_strmSessionState.SetPos_t(0);
		_pTimer->SetCurrentTick(0.0f);
		ReadWorldAndState_t(&prlOld->rl_strmSessionState);
		_pTimer->SetCurrentTick(ses_tmLastProcessedTick);
	}
	catch (char* strError) {
		FatalError(TRANS("Cannot restore old level '%s':\n%s"), prlOld->rl_strFileName, strError);
	}
	// delete it
	delete prlOld;
}


// forget all remembered levels
void CSessionState::ForgetOldLevels(void)
{
	{
		FORDELETELIST(CRememberedLevel, rl_lnInSessionState, ses_lhRememberedLevels, itrl) {
			delete&* itrl;
		}
	}
}


//! Ŭ���̾�Ʈ�� ���� Ÿ���� �����Ѵ�.�׸��� Ŭ���̾�Ʈ ������Ʈ�� �Ѵ�. ������.
// this is used on client side of network game
// adjust the client's local game time and run client updates
void CSessionState::AdjustLocalTime() {
	static CTimerValue tvOld = _pTimer->GetHighPrecisionTimer();
	BOOL bPaused = _pNetwork->IsWaitingForPlayers() || ses_bPause;
	CTimerValue tvNow = _pTimer->GetHighPrecisionTimer();

	//! ���� �÷��� ���� TRUE
	if (ses_bRestartLocalTime) {
		ses_bRestartLocalTime = FALSE;
		tvOld = tvNow;
	}

	if (_pNetwork->IsGameFinished()) {
		return;
	}
	// how many ticks we have to run?
	ULONG ulNumTicks = (tvNow.GetSeconds() - tvOld.GetSeconds()) / _pTimer->TickQuantum;
	//! ClampUp:�������� �й��ϴ�.��, ���߿� �������� �����Ѵ�.
	ULONG ulClampedTicks = ClampUp(ulNumTicks, (ULONG)10);
	//! ���ο� �ð��� ���.
	// remember the new time
	tvOld += _pTimer->TickQuantum * ulNumTicks;

	if (ulClampedTicks > 0 && !bPaused) {
		// advance local time for that many ticks
		_tmLocalTick += _pTimer->TickQuantum * ulNumTicks;
		// update the current tick
		if (_pNetwork->IsPlayingDemo()) {
			_pTimer->SetCurrentTick(_pNetwork->ga_tmNextDemoTick - _pTimer->TickQuantum);
		}
		else {
			_pTimer->SetCurrentTick(_tmLocalTick);
		}

		if (_cmiComm.cci_bClientInitialized) {
			INDEX ctTicks = 0;
			// for each tick that has passed
			while (ctTicks < ulClampedTicks && !_pNetwork->IsPlayingDemo()) {
				//! ��� ���� �÷��̾ ���� �׼� ��Ŷ�� ����� ������ ������.
			   // make actions packet for all local players and send to server
				_pNetwork->SendActionsToServer();
				ctTicks++;
			}
		}
		extern INDEX cli_iFPSLimit;
		extern INDEX  cli_iCurrentFPS;
		if (cli_iFPSLimit && (cli_iCurrentFPS < cli_iFPSLimit)) {
			SetLerpFactor(_pTimer->GetHighPrecisionTimer());
		}
		// do time events
		if (!_pNetwork->IsPlayingDemo()) {
			HandleTimers(_tmLocalTick);
			// do movement - dead reckoning
			HandleMovers_client();
		}
	}

}


void Cludge_SetLerpFactor()
{
	// update the current tick
	{
		CTimerValue tvNow = _pTimer->GetHighPrecisionTimer();
		if (!_pNetwork->ga_bDemoPlay) {
			_pNetwork->ga_sesSessionState.SetLerpFactor(tvNow);
		}
		else {
			_pNetwork->ga_sesSessionState.SetLerpFactor(CTimerValue(_pNetwork->ga_fDemoTimer));
		}
	}
}

/*
void CSessionState::RunDemoTick()
{
	static UBYTE aubData[SERVER_MAX_MESSAGE_SIZE];
	SLONG slSize,slCompressedSize;

	ses_bWaitingForServer = FALSE;

	// if this is not an empty tick, read the data to the buffer
	extern UBYTE _aubCompData[SERVER_MAX_MESSAGE_SIZE];
	try {
		_pNetwork->ga_strmDemoPlay.ExpectID_t("DTCK");// demo tick
		_pNetwork->ga_strmDemoPlay >> slCompressedSize;
		if (slCompressedSize > 0) {
			_pNetwork->ga_strmDemoPlay.Read_t(_aubCompData,slCompressedSize);
		}
		_pNetwork->ga_bDemoPlayFinished = FALSE;
	} catch(char *strError) {
		_pNetwork->ga_bDemoPlayFinished = TRUE;
		CPrintF("Error while playing demo: %s\n",strError);
		return;
	}
	slSize = SERVER_MAX_MESSAGE_SIZE;
	CzlibCompressor comp;
	BOOL bOK = comp.Unpack(_aubCompData,slCompressedSize,aubData,slSize);
	ASSERT(bOK);

	// the compiler messes up the stack in debug if 64 bit integers and
	// try-catch are used in the same function (stack scope). This is a fix-up cludge.
	Cludge_SetLerpFactor();

	if (slCompressedSize > 0) {
		// clear the input buffer
		ses_embReceiveBuffer.Clear();

		// put the tick data into the buffer
		ReceiveTick(_pNetwork->ga_tmNextDemoTick,aubData,slSize);

		_vBasePosition    = FLOAT3D(0,0,0);
		_bBasePositionSet = FALSE;

		// if the tick received isn't empty
		if (slSize > 0) {
			// read and apply all received messages
			while (ReceiveMessage()){};
		}
	}

	// update session time
	ses_tmLastProcessedTick = _pNetwork->ga_fDemoTimer;//_tmLocalTick;
	ses_tmLastTickTime = _pNetwork->ga_fDemoTimer;//_tmLocalTick;

	try {
		CChunkID cid = _pNetwork->ga_strmDemoPlay.PeekID_t();
		if (cid == CChunkID("DTTM")) {
			_pNetwork->ga_strmDemoPlay.ExpectID_t("DTTM");
			_pNetwork->ga_strmDemoPlay>>_pNetwork->ga_tmNextDemoTick;
		} else {
			_pNetwork->ga_strmDemoPlay.ExpectID_t("DEND"); // demo end
			_pNetwork->ga_bDemoPlayFinished = TRUE;
			return;
		}
	} catch(char *strError) {
		_pNetwork->ga_bDemoPlayFinished = TRUE;
		CPrintF("Error while playing demo: %s\n",strError);
	}
};
*/

//0105 �Լ� �߰��ϱ�.
void CSessionState::ProcessOneSentence(char* msg)
{
	static char cmd[100];

	msg = AnyOneArg(msg, cmd);
	int cmd_num = m_pCmd->Find(cmd);
	if (cmd_num < 0)
		return;

	m_pCmd->Run(cmd_num, msg);

	return;
}

#define is_space(c)		(c == 0x20 || (c >= 0x09 && c <= 0x0D))
char* CSessionState::AnyOneArg(char* argument, char* first_arg)
{
	SkipSpaces(&argument);

	while (*argument && !is_space(*argument)) {
		*(first_arg++) = *argument;
		argument++;
	}

	*first_arg = '\0';

	return (argument);
}


void CSessionState::SkipSpaces(char** string)
{
	for (; **string && is_space(**string); (*string)++);
}


void CSessionState::StartGame()
{

	char Buf[1024];

	sprintf(Buf, "start 0 0\n");

	_tcpip.SendNetMessage(Buf, TRUE);

	return;
}
//..

/* Session state loop. */
void CSessionState::SessionStateLoop(void)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	_pfNetworkProfile.StartTimer(CNetworkProfile::PTI_SESSIONSTATE_LOOP);

	// while there is something to do
	BOOL bSomethingToDo = TRUE;

	while (bSomethingToDo && !IsDisconnected())
	{

		//Sleep(0);				// deleted by seo - 40830
		bSomethingToDo = FALSE;

		//! Ŭ���̾�Ʈ ������Ʈ
		_cmiComm.Client_Update();
		CNetworkMessage nmMessage;
		static FLOAT ResponseTime = _pTimer->CurrentTick();

#ifdef CEHACK
		//reza cheat
		static struct tm* st;
		time_t t = time((time_t*)NULL);
		st = localtime(&t);
#endif

		extern BOOL _bLoginProcess;

		// ---- Add national code ----------060711------------->>
		INDEX tv_idx;
		switch (g_iCountry)
		{
		case KOREA:			tv_idx = 0;		break;
		case THAILAND:		tv_idx = 4;		break;
		case USA:			tv_idx = 9;		break;
		case BRAZIL:		tv_idx = 10;	break;
		case ENGLAND:
		case GERMANY:		tv_idx = 13;	break;
		case SPAIN:			tv_idx = 14;	break;
		case FRANCE:		tv_idx = 15;	break;
		case POLAND:		tv_idx = 16;	break;
		case RUSSIA:		tv_idx = 17;	break;
		case ITALY:			tv_idx = 19;	break;
		case MEXICO:		tv_idx = 20;	break;
		default:			tv_idx = g_iCountry;	break;
		}
		// ---- Add national code ----------060711-------------<<

		if (!_bLoginProcess || STAGEMGR()->GetCurStage() == eSTAGE_CREATECHAR || STAGEMGR()->GetCurStage() == eSTAGE_SELCHAR)
		{
			static DWORD AliveTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();
			static DWORD SendTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();
			static BOOL bIsFirst = TRUE;

#ifdef CEHACK //reza cheat
			static DWORD GetThisTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();
			static INT CountTime = 0, counterEditer = 0;
#endif
			DWORD tmpTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();

#ifdef CEHACK
			DWORD tmpTime2 = _pTimer->GetHighPrecisionTimer().GetMilliseconds();
#endif  

			if (bIsFirst)
			{
				CNetworkMessage nmAliveMsg((UBYTE)MSG_PULSE);
				nmAliveMsg << (SLONG)(AliveTime / 100);
				// ---- Add national code ----------060711------------->>
				nmAliveMsg << (UBYTE)tv_idx;
				// ---- Add national code ----------060711-------------<<
				nmAliveMsg << (FLOAT)_pTimer->tmTimeDelay;
				_pNetwork->SendToServerNew(nmAliveMsg);

				bIsFirst = FALSE;
			}

#ifdef CEHACK
			if (tmpTime - AliveTime >= 3000) //fix dc idle
#else
			if (tmpTime - AliveTime >= 60000)
#endif
			{
				CNetworkMessage nmAliveMsg((UBYTE)MSG_PULSE);
				nmAliveMsg << (SLONG)(tmpTime / 100);
				// ---- Add national code ----------060711------------->>
				nmAliveMsg << (UBYTE)tv_idx;
				// ---- Add national code ----------060711-------------<<
				nmAliveMsg << (FLOAT)_pTimer->tmTimeDelay;

#ifdef CEHACK
				//reza  #### ANTIHACK SPEED CHECK
				if (STAGEMGR()->GetCurStage() == eSTAGE_GAMEPLAY) {
					CPlayerEntity* cpe = (CPlayerEntity*)CEntity::GetPlayerEntity(0);
					SBYTE atkent = 0, atknet = 0;
					atknet = (SBYTE)_pNetwork->MyCharacterInfo.attackspeed;
					atkent = (SBYTE)((CPlayerEntity*)CEntity::GetPlayerEntity(0))->GetAttackspeed();
					if (_pNetwork->MyCharacterInfo.bWildPetRide | _pNetwork->MyCharacterInfo.bPetRide) {
						nmAliveMsg << (SBYTE)_pNetwork->MyCharacterInfo.attackspeed;
						nmAliveMsg << (FLOAT)_pNetwork->MyCharacterInfo.runspeed;
					}
					else {
						nmAliveMsg << (SBYTE)((CPlayerEntity*)CEntity::GetPlayerEntity(0))->GetAttackspeed();//check attackspeed 
						nmAliveMsg << (FLOAT)((CPlayerEntity*)CEntity::GetPlayerEntity(0))->GetRunspeed(); //check runspeed

					}//nmAliveMsg<< (SBYTE)_pNetwork->MyCharacterInfo.attackspeed;
					//nmAliveMsg<< (FLOAT)_pNetwork->MyCharacterInfo.runspeed;
				}
				else {
					nmAliveMsg << (SBYTE)0;
					nmAliveMsg << (FLOAT)0.0;
				}

				nmAliveMsg << (DWORD)(_pNetwork->MyCharacterInfo.bExtension);
				nmAliveMsg << (BYTE)STAGEMGR()->GetCurStage();
				nmAliveMsg << (DWORD)(pUIManager->m_nCoolTimeReductionRate);
				nmAliveMsg << (DWORD)(_pNetwork->MyCharacterInfo.skillSpeed);

				//####END
#endif	

				_pNetwork->SendToServerNew(nmAliveMsg);
				CPrintF("Send Alive MSG...%d \n", tmpTime);

				AliveTime = tmpTime;
			}
#ifdef UPDATE_PLAYTIME
			DWORD tmpDeffTime = tmpTime - _SetPlayStartTime;

			if (tmpDeffTime >= _IntervalPlayCountTime)
			{
				// �÷��� Ÿ�� ������Ʈ
				++_PlayTimeCount;
				_pNetwork->SendUpdatePlayTime(_PlayTimeCount * _IntervalTime);
				_SetPlayStartTime = tmpTime;
			}
#endif
			// �̱۴��� ����� ��쿡...
			if (_pNetwork->m_bSingleMode)
			{
				if (tmpTime - SendTime >= 1000)
				{
					CPrintF("%ld SendAttack\n", tmpTime);
					//_pNetwork->SendMoveList();
					_pNetwork->SendAttackList();
					SendTime = tmpTime;
				}
			}

#ifdef CEHACK
			// By Ariel gamespeed check
			if ((DWORD)GetModuleHandleA("speedhac.dll"))
			{
				_pNetwork->SendInput();
			}
			if (_pTimer->tmTimeDelay > 0.07f)
			{
				if (tmpTime2 - GetThisTime >= 1500)
					_pNetwork->SendInput();
			}
			else {
				GetThisTime = tmpTime2;
			}
#endif
			if ((DWORD)GetModuleHandleA("speedhack.dll"))
			{
				_pNetwork->SendInput();
			}

			static int checktime = 0;

			if (tmpTime2 - GetThisTime >= 1500)
			{

				if (_pTimer->tmTimeDelay > 0.51f)
				{
					if (checktime < 10)
					{
						checktime++;
						if (_pNetwork->m_ubGMLevel == 10)
						{
							CTString debug;

							debug.PrintF("WARNING count %d %f", checktime, _pTimer->tmTimeDelay);//speedhack count %d %f
							pUIManager->GetChattingUI()->AddSysMessage(debug, SYSMSG_RED);
						}
					}
					else _pNetwork->SendInput();
				}
				else checktime = 0;

				GetThisTime = tmpTime2;
			}
			/*			if (_pTimer->tmTimeDelay > 0.07f)
						{ // ���ǵ� �� ����� �˸� (TickCount�� 0.05f�� �⺻�̹Ƿ� 0.05f���� �������ٸ� ���ǵ��� ����ڷ� ����.
							_pNetwork->SendUsingSpeedHack();
						}*/

		}

		if (_pNetwork->ReceiveFromServerNew(nmMessage))
		{
			bSomethingToDo = TRUE;//0820 �̳��� �÷��� m������ ��Ʈ��ũ�� �ʾ���..�Ѥ�;
			ResponseTime = _pTimer->CurrentTick();

#ifdef	VER_TEST
			{
				char* buf = (char*)nmMessage.GetBuffer();
				if (buf[0] != MSG_MOVE)
				{
					int		sub = buf[1];

					struct tm* st;
					time_t t = time((time_t*)NULL);
					st = localtime(&t);

					if (buf[0] == MSG_EXTEND)
					{
						sub = ntohl(*((int*)(&buf[1])));

						if (sub < 0 || sub >= MSG_EX_END)
							sub = htonl(sub);

						LOG_DEBUG("%02d:%02d:%02d Recv MSG(%s[%d] - %s[%d] - %d)",
							st->tm_hour, st->tm_min, st->tm_sec,
							strMSG_MAIN[buf[0]], buf[0], strMSG_EXTEND[sub], sub, buf[5]);
					}
					else if (buf[0] == MSG_UPDATE_DATA_FOR_CLIENT)
					{
						if (sub != MSG_SUB_UPDATE_STATUS)
							LOG_DEBUG("%02d:%02d:%02d Update MSG(%s[%d] - %s[%d])", st->tm_hour, st->tm_min, st->tm_sec, strMSG_MAIN[buf[0]], buf[0], strMSG_UPDATE[sub], sub);
					}
					else
					{
						LOG_DEBUG("%02d:%02d:%02d Recv MSG(%s[%d] - %d)", st->tm_hour, st->tm_min, st->tm_sec, strMSG_MAIN[buf[0]], buf[0], sub);
					}
				}
			}
#endif	// VER_TEST

			if (_bLoginProcess)
			{
				// NOTE : �α��� �ÿ��� ������ �Ʒ� �Լ��� ��.
				// NOTE : ĳ���� ���� ���н� MSG_FAIL ������ ĳ���� ���� ������ �ٷ� ���� ������
				// NOTE : ���� Ÿ�Ա��� �� ���� ������ ó���ؾ� ��.
				ReceiveLoginMessage(&nmMessage);
			}
			else
			{
				UBYTE msg = nmMessage.GetType();
				bool bProcess = false;

#if		!defined(WORLD_EDITOR)
				pTypeBase* pBase = reinterpret_cast<pTypeBase*>(nmMessage.GetBuffer());

				// DEBUG: Trace MSG_CASHEXCHANGE dispatch to file
				if (msg == 100) // MSG_CASHEXCHANGE
				{
					CASH_DEBUG_LOG("[SessionState] MSG_CASHEXCHANGE dispatch - type=%d, subType=%d\n", msg, pBase->subType);
				}

				_map_packet_iter iter = m_packet[msg].find(pBase->subType);

				if (iter != m_packet[msg].end())
				{
					if (iter->second != NULL)
					{
						// DEBUG: Handler found and called
						if (msg == 100) // MSG_CASHEXCHANGE
						{
							CASH_DEBUG_LOG("[SessionState] MSG_CASHEXCHANGE handler FOUND - calling handler\n");
						}
						iter->second(&nmMessage);
						bProcess = true;
					}
				}
				else if (msg == 100) // MSG_CASHEXCHANGE
				{
					CASH_DEBUG_LOG("[SessionState] MSG_CASHEXCHANGE handler NOT FOUND for subType=%d in m_packet map!\n", pBase->subType);
				}
#endif	// WORLD_EDITOR

				if (bProcess == false)
				{

					switch (msg)
					{
					case MSG_MOVE:
						ReceiveMoveMessage(&nmMessage);
						break;
					case MSG_ATTACK:
						ReceiveAttackMessage(&nmMessage);
						break;
					case MSG_CHAT:
						ReceiveChatMessage(&nmMessage);
						break;
					case MSG_SKILL:
						ReceiveSkillMessage(&nmMessage);
						break;
					case MSG_SSKILL:			// Ư�� ��ų
						ReceiveSSkillMessage(&nmMessage);
						break;
					case MSG_QUICKSLOT:
						ReceiveQuickSlotMessage(&nmMessage);
						break;
					case MSG_INVENTORY:
						ReceiveInventoryMessage(&nmMessage);
						break;
					case MSG_WEARING:
						((CPlayerEntity*)CEntity::GetPlayerEntity(0))->Read_net_Character(MSG_WEARING, 0, &nmMessage);
						break;
					case MSG_ITEM:
						ReceiveItemMessage(&nmMessage);
						break;
					case MSG_GOTO:
						ReceiveGoToMessage(&nmMessage);
						break;
					case MSG_MEMPOS:
						// [KH_070316] �����̾� �޸� ���� �߰� �� ����
					case XXXMSG_MEMPOSPLUS:
						ReceiveMemPosMessage(&nmMessage);
						break;
					case MSG_GM:
						ReceiveGmMessage(&nmMessage);
						break;
					case MSG_GO_ZONE:
						ReceiveGoZoneMessage(&nmMessage);
						break;
					case MSG_PARTY:
						ReceivePartyMessage(&nmMessage);
						break;
					case MSG_EXCHANGE:
						ReceiveExchangeMessage(&nmMessage);
						break;
					case MSG_QUEST:
						ReceiveQuestMessage(&nmMessage);
						break;
					case MSG_STATPOINT:
						ReceiveStatMessage(&nmMessage);
						break;
					case MSG_UI:
						ReceiveUIMessage(&nmMessage);
						break;
					case MSG_NPC_REGEN:
						ReceiveNpcRegenMessage(&nmMessage);
						break;
					case MSG_ASSIST:
						ReceiveAssistMessage(&nmMessage);
						break;
					case MSG_PC_REBIRTH:
						ReceiveRebirthMessage(&nmMessage);
						break;
					case MSG_EFFECT:
						ReceiveEffectMessage(&nmMessage);
						break;
					case MSG_SYS:
						ReceiveSystemMessage(&nmMessage);
						break;
					case MSG_EXP_SP:
						ReceiveEXPMessage(&nmMessage);
						break;
					case MSG_ACTION:
						ReceiveActionMessage(&nmMessage);
						break;
					case MSG_ENV://1013
						ReceiveEnvMessage(&nmMessage);
						break;
					case MSG_WARP:
						ReceiveWarpMessage(&nmMessage);
						break;
					case MSG_PK:
						ReceivePkMessage(&nmMessage);
						break;
					case MSG_EVENT:
						ReceiveEventMessage(&nmMessage);
						break;
					case MSG_PERSONALSHOP:
						ReceivePersonalShopMessage(&nmMessage);
						break;
					case MSG_RIGHT_ATTACK:
						ReceiveLegitimateMessage(&nmMessage);
						break;
					case MSG_STASH:
						ReceiveWareHouseMessage(&nmMessage);
						break;
					case MSG_GUILD:
						ReceiveGuildMessage(&nmMessage);
						break;
					case MSG_TEACH:
						ReceiveTeachMessage(&nmMessage);
						break;
					case MSG_CHANGEJOB:
						ReceiveChangeJobMessage(&nmMessage);
						break;
					case MSG_CHANGE:
						((CPlayerEntity*)CEntity::GetPlayerEntity(0))->Read_net_Character(MSG_CHANGE, 0, &nmMessage);
						break;
					case MSG_FRIEND:
						ReceiveMessengerMessage(&nmMessage);
						break;
					case MSG_TRADEAGENT:
					{
						Auction* pAuction = GameDataManager::getSingleton()->GetAuction();
						if (pAuction)
							pAuction->ReceiveTradeAgentMessage(&nmMessage);
					}
					break;
					case MSG_EXPEDITION: // [sora] ������ ����
						ReceiveExpeditionMessage(&nmMessage);
						break;

					case MSG_CRAFT:	 //Craft system
						ReceiveCraftMessage(&nmMessage);
						break;
					case MSG_RAID: // [sora] �ν���Ʈ�� �޽���
					{
						SBYTE	sbType;
						(nmMessage) >> sbType;

						if (MSG_RAID_ERROR == sbType)
						{
							GAMEDATAMGR()->GetPartyInfo()->RecvRaidError(&nmMessage);
						}
					}
					break;
					case MSG_FACTORY:
						ReceiveFactoryMessage(&nmMessage);
						break;
						//wooss 050818
					case MSG_EXTEND:
						if (RecvExtend(&nmMessage) == false)
						{
							ReceiveExtendMessage(&nmMessage);
						}
						break;
					case MSG_ARTIFACT:
						ReceiveArtifactMessage(&nmMessage);
						break;
					case MSG_FAIL:
						ReceiveFailMessage(&nmMessage);
						break;

					case MSG_RECOVER_EXP_SP:	// [2012/08/10 : Sora] ��Ȱ �ֹ��� ���� ������ ����ġ, ���õ�
					{
						SQUAD loseExp, loseSp;
						CTString strMessage;
						CTString strTemp;

						(nmMessage) >> loseExp;
						(nmMessage) >> loseSp;

						if (loseExp > 0)
						{
							strTemp.PrintF("%I64d", loseExp);
							pUIManager->InsertCommaToString(strTemp);
							strMessage.PrintF(_S(5768, "��Ȱ�ֹ���3�� �Ҹ��Ͽ� EXP %s �� ���� �Ͽ����ϴ�."), strTemp);
							pUIManager->GetChattingUI()->AddSysMessage(strMessage);
						}

						if (loseSp > 0)
						{
							strTemp.PrintF("%I64d", loseSp);
							pUIManager->InsertCommaToString(strTemp);
							strMessage.PrintF(_S(5769, "��Ȱ�ֹ���3�� �Ҹ��Ͽ� SP %s �� ���� �Ͽ����ϴ�."), strTemp);
							pUIManager->GetChattingUI()->AddSysMessage(strMessage);
						}
					}
					break;

					case MSG_MONEY:	//2013/04/03 jeil ���� ������ ����
						ReceiveMoneyMessage(&nmMessage);
						break;
#ifdef HP_PERCENTAGE
					case MSG_DAMAGE_REAL:
						ReceiveDamageRealStatMessage(&nmMessage);
						break;
#endif // HP_PERCENTAGE

					case MSG_TIMER_ITEM:
						ReceiveTimerItemMessage(&nmMessage);
						break;

					case MSG_EXPRESS_SYSTEM:
						ReceiveExpressMessage(&nmMessage);
						break;

					case MSG_MAIL_BOX:
						ReceiveMailBoxMessage(&nmMessage);
						break;
					case MSG_RESERVED_GM_COMMAND:
						ReceiveCalendarMessage(&nmMessage);
						break;
					case MSG_PET_STASH:
						ReceivePetStashMessage(&nmMessage);
						break;
					case MSG_RVR:
						ReceiveRVRMessage(&nmMessage);
						break;
#ifdef DURABILITY
					case MSG_DURABILITY:
						ReceiveDurabilityMessage(&nmMessage);
						break;
#endif	//	DURABILITY
					case MSG_ITEMCOLLECTION:
						ReceiveItemCollectionMessage(&nmMessage);
						break;

#ifdef DAILY_LOGIN
					case MSG_REZA:
					{
						/*RezaPVP* pRezaPVP = pUIManager->GetRezaPVP();
						if (pRezaPVP != NULL)

							pRezaPVP->do_Reza(&nmMessage);
					*/
						do_Reza(&nmMessage);
					}
					break;
#endif 


#ifdef PREMIUM_CHAR
					case MSG_PREMIUM_CHAR:
						ReceivePremiumCharMessage(&nmMessage);
						break;
#endif	//	PREMIUM_CHAR
					case MSG_REBORN:
						ReceiveRebornMessage(&nmMessage);
						break;
#ifdef BATTLE_PASS_SYSTEM
					case MSG_BATTLE_PASS:
						ReceiveBattlePassMessage(&nmMessage);
						break;
#endif
#ifdef PRESTIGE_SYSTEM
					case MSG_PRESTIGE:
						ReceivePrestigeMessage(&nmMessage);
						break;
#endif
					case MSG_HONOR:
						ReceiveHonorMessage(&nmMessage);
						break;
#ifdef PASSIVE_SYSTEM
					case MSG_PASSIVE_SYSTEM:
						pUIManager->GetPassiveSystem()->ReceiveMsg(&nmMessage);
						break;
#endif

					default:
					{
						pTypeBase* pBase = reinterpret_cast<pTypeBase*>(nmMessage.GetBuffer());
						CPrintF("Undefined data received!! msgType = %d (%d)\n", pBase->type, pBase->subType);
					}
					break;
					}
				}
			}
		}
		else
		{
			extern BOOL _bLoginProcess;
			if (_pNetwork->m_bSendMessage && (unsigned int(_pTimer->GetLerpedCurrentTick() * 1000)) - _pNetwork->m_uiSendedTime > 15000)
			{
				if (_bLoginProcess)
				{
					GameDataManager* pGameData = GameDataManager::getSingleton();
					CServerSelect* pServerSelect = NULL;

					if (pGameData != NULL)
						pServerSelect = pGameData->GetServerData();

					//if( pUIManager->GetUIGameState() == eSTAGE_LOGIN && !pUIManager->GetSelServer()->IsEmptyGroup() )
					if (STAGEMGR()->GetCurStage() == eSTAGE_LOGIN && pServerSelect != NULL && pServerSelect->GetServerCount() > 0)
					{
						_pSound->Mute();
						// NOTE : �α��� ���н� ������ �ݰ� �ٽ� �����ؾ��ϴ� �κ�.				
						_cmiComm.Disconnect();

						_pGameState->DisplayErrorMessage(MSG_TIME_OUT, UI_NONE, MSGCMD_LOGIN_ERROR);
						_pNetwork->m_bSendMessage = FALSE;

					}
					else
						//else if(_cmiComm.IsNetworkOn())
					{
						if (!_tcpip.IsConnected(_tcpip.Socket))
						{
							_pGameState->DisplayErrorMessage(MSG_FAIL_CONNECT_SERVER, UI_NONE, MSGCMD_LOGIN_ERROR);
						}
						else
						{
							_pGameState->DisplayErrorMessage(MSG_TIME_OUT, UI_NONE, MSGCMD_LOGIN_ERROR);
						}
						_pNetwork->m_bSendMessage = FALSE;
					}
				}
			}
		}


		// if there is some unreliable message
		if (_pNetwork->ReceiveFromServer(nmMessage))
		{
			bSomethingToDo = TRUE;
			//! ���� ��Ʈ�� �޽������, �����Ŀ� �о���δ�.���ø� �޴´�.
			// if it is a gamestream message
			if (nmMessage.GetType() == MSG_GAMESTREAMBLOCKS)
			{
				ses_tvMessageReceived = _pTimer->GetHighPrecisionTimer();
				ses_bWaitingForServer = FALSE;

				// unpack the message
				CNetworkMessage nmUnpackedBlocks((UBYTE)MSG_GAMESTREAMBLOCKS);
				nmMessage.UnpackDefault(nmUnpackedBlocks);

				// while there are some more blocks in the message
				while (!nmUnpackedBlocks.EndOfMessage())
				{
					// read a block to the gamestream
					ses_nsGameStream.ReadBlock(nmUnpackedBlocks);
				}
			}
			else
			{
				CPrintF(TRANS("Session state: Unexpected unreliable message during game: %s(%d)\n"),
					ErrorDescription(&MessageTypes, nmMessage.GetType()), nmMessage.GetType());
			}
		}
	}
	_pfNetworkProfile.StopTimer(CNetworkProfile::PTI_SESSIONSTATE_LOOP);
}

/* Get number of active players. */
INDEX CSessionState::GetPlayersCount(void)
{
	INDEX ctPlayers = 0;
	FOREACHINSTATICARRAY(_pNetwork->ga_srvServer.srv_apltPlayers, CPlayerTarget, itplt) {
		if (itplt->IsActive()) {
			ctPlayers++;
		}
	}
	return ctPlayers;
}


// probability (0.0 - 1.0) that the client will drop the tick data (bad network conditions emulation)
extern FLOAT cli_fTickDropRate;


// receive a message from the incoming tick data
BOOL CSessionState::ReceiveMessage()
{
	ULONG ulEntityID;
	UWORD aubData[1024];
	int   iErr;

	//	extern INDEX net_bReportClientTraffic;

		// read the message from the input buffer
	iErr = ses_embReceiveBuffer.ReadMessage(ses_emEntityMessage);

	if (iErr != EMB_SUCCESS_OK)
	{
		return FALSE;
	}

	// if this message is older than the last fully processed server tick, do not process it
	if ((ses_tmLastTickTime > (ses_emEntityMessage.em_tmMessageTime - (_pTimer->TickQuantum / 2))) && !_pNetwork->IsPlayingDemo())
	{
		if (net_bReportClientTraffic)
		{
			//0203 
			//	CPrintF(TRANS("MESSAGE REJECTED! Type: %d, Session time: %5.2f, Message time: %5.2f\n"),ses_emEntityMessage.em_ulType,ses_tmLastTickTime,ses_emEntityMessage.em_tmMessageTime);
		}
		return TRUE;
	}

	switch (ses_emEntityMessage.em_ulType)
	{
		// if adding a new player
	case EMT_ADDPLAYER:
	{
		INDEX iPlayerIndex, iClient;
		ULONG ulWeaponsID, ulAnimatorID;
		CPlayerCharacter pcCharacter;
		ses_ulMsgId++;
		CEntity* penPlayer;

		// extract neccessary data from the message
		ses_emEntityMessage.ReadAddPlayer(ulEntityID, iPlayerIndex, pcCharacter, ulWeaponsID, ulAnimatorID, iClient);

		if (_pNetwork->ga_World.EntityExists(ulEntityID, penPlayer))
		{
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors)
			{
				CPrintF("Warning: Repeated AddPlayer, EntityID: 0x%X\n", ulEntityID);
			}
			break;
		}

		// add the player to the game, forcing it to have a received entity ID for CPlayer, CPlayerWeapons and CPlayerAnimator
		// this is because we will need to process messages specifying those ID's later
		AddPlayer(iPlayerIndex, pcCharacter, ulEntityID, ulWeaponsID, ulAnimatorID, iClient);

		// report to console
		if (net_bReportClientTraffic)
		{
			CPrintF("ADDPLAYER:     %s  EntityID: 0x%X   %6.3f\n  ", (const char*)pcCharacter.pc_strName, ulEntityID, ses_emEntityMessage.em_tmMessageTime);
		}

		break;
	}
	//0203 
	/*
	// new placement received for an entity
	case EMT_SETPLACEMENT:
	{
	CEntity* penEntity;
	CPlacement3D plPlacement,plSpeed;
	ses_ulMsgId++;
	//        ASSERT(_bBasePositionSet);

	  // extract neccessary data from the message
	  ses_emEntityMessage.ReadPlacement(ulEntityID,plPlacement,plSpeed);
	  plPlacement.pl_PositionVector += _vBasePosition;

		// if placement received is for an entity that does not exist on the client,
		// print a warning to the console, and return
		if (!_pNetwork->ga_World.EntityExists(ulEntityID,penEntity)) {
		extern INDEX net_bReportMiscErrors;
		if (net_bReportMiscErrors) {
		CPrintF("Warning: SetPlacement for non existing entity, EntityID: 0x%X\n",ulEntityID);
		}
		break;
		}

		  // get the pointer to the specified entity
		  penEntity = _pNetwork->ga_World.EntityFromID(ulEntityID);

			// it it's a movable entity, adjust it's dead reckoning parameters - position, speed and extrapolation start time
			if (penEntity->en_ulPhysicsFlags & EPF_MOVABLE) {
			CMovableEntity* penMovable = (CMovableEntity*) penEntity;
			if (plSpeed.pl_OrientationAngle.Length() > 0.01 || plSpeed.pl_PositionVector.Length() > 0.01) {
			penMovable->AddToMovers();
			} else {
			if (penMovable->en_lnInMovers.IsLinked()) {
			penMovable->en_lnInMovers.Remove();
			}
			}
			penMovable->AdjustDeadReckoning(plPlacement,plSpeed,ses_emEntityMessage.em_tmMessageTime);
			// if it's not a movable entity, just put it in it's place
			} else {
			penEntity->SetPlacement(plPlacement);
			}

			  // report to console
			  if (net_bReportClientTraffic) {
			  CPrintF("%lu: SETPLACEMENT:     EntityID: 0x%X     Position: %f, %f, %f     ",ses_ulMsgId,ulEntityID,plPlacement.pl_PositionVector(1),plPlacement.pl_PositionVector(2),plPlacement.pl_PositionVector(3));
			  CPrintF("Angle: %f, %f, %f\n",plPlacement.pl_OrientationAngle(1),plPlacement.pl_OrientationAngle(2),plPlacement.pl_OrientationAngle(3));
			  }
			  break;
}*/
// a new entity should be created on the client
	case EMT_CREATE:
	{
		UWORD uwClassID;
		CPlacement3D plPlacement;
		CEntity* penEntity;
		EntityClassEntry* peceEntry;
		ses_ulMsgId++;

		// get the entity id, placement and class id
		ses_emEntityMessage.ReadEntityCreate(ulEntityID, plPlacement, uwClassID);

		// get the pointer to the entity class entry in the class container
		peceEntry = FindClassInContainer(uwClassID);
		// it really should be there
		ASSERT(peceEntry != NULL);
		if (peceEntry == NULL)
		{
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors)
			{
				CPrintF(TRANS("Warning: Create entity received for an unknown entity class, EntityID: 0x%X\n"), ulEntityID);
			}
			break;
		}

		// create the entity with specified data
		penEntity = _pNetwork->ga_World.CreateEntity_t(plPlacement, peceEntry->ece_fnmEntityClass, ulEntityID);

		// report to console
		if (net_bReportClientTraffic)
		{
			CPrintF("Class name: %s\n", peceEntry->ece_fnmEntityClass);
			CPrintF("%lu: CREATE:           EntityID: 0x%X     EntityClass: %ld", ses_ulMsgId, ulEntityID, uwClassID);
			CPrintF("     Position: %f, %f, %f     ", plPlacement.pl_PositionVector(1), plPlacement.pl_PositionVector(2), plPlacement.pl_PositionVector(3));
			CPrintF("Angle: %f, %f, %f\n", plPlacement.pl_OrientationAngle(1), plPlacement.pl_OrientationAngle(2), plPlacement.pl_OrientationAngle(3));
		}

		break;

	}
	// copy one entity to another
	case EMT_COPY:
	{
		ULONG ulTargetID;
		CPlacement3D plPlacementCopy;
		UBYTE ubWithDescentants = 0;
		CEntity* penOriginal;
		//        CEntity* penCopy;

		ses_ulMsgId++;

		// extract neccessary data from the message
		ses_emEntityMessage.ReadEntityCopy(ulEntityID, ulTargetID, plPlacementCopy, ubWithDescentants);

		if (!_pNetwork->ga_World.EntityExists(ulEntityID, penOriginal)) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF("Warning: Copy from non existing entity, EntityID: 0x%X\n", ulEntityID);
			}
			break;
		}
		ASSERT(penOriginal != NULL);
		if (penOriginal == NULL) {
			break;
		}

		_pNetwork->ga_World.CopyEntityInWorld(*penOriginal, plPlacementCopy, ubWithDescentants, ulTargetID);

		// report to console
		if (net_bReportClientTraffic) {
			CPrintF("%lu: COPY:           SourceEntityID: 0x%X     TargetEntityID: 0x%X     ", ses_ulMsgId, ulEntityID, ulTargetID);
			CPrintF("     Position: %f, %f, %f     ", plPlacementCopy.pl_PositionVector(1), plPlacementCopy.pl_PositionVector(2), plPlacementCopy.pl_PositionVector(3));
			CPrintF("Angle: %f, %f, %f\n", plPlacementCopy.pl_OrientationAngle(1), plPlacementCopy.pl_OrientationAngle(2), plPlacementCopy.pl_OrientationAngle(3));
		}

		break;
	}
	// entity needs to be destroyed
	case EMT_DESTROY:
	{
		CEntity* penEntity;

		ses_ulMsgId++;

		// get the entity id from themessage
		ses_emEntityMessage.ReadEntityDestroy(ulEntityID);

		// get the pointer to the entity
		if (!_pNetwork->ga_World.EntityExists(ulEntityID, penEntity)) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Warning: destroy message received for non existing entity, EntityID: 0x%X\n"), ulEntityID);
			}
			break;
		}

		ASSERT(penEntity != NULL);
		if (penEntity == NULL) break;
		// destroy the entity - this might not delete it from memory, depending on the number of references to it
		penEntity->Destroy();

		// report to console
		if (net_bReportClientTraffic)
		{
			//0205
			//			CPrintF("%lu: DESTROY:        EntityID: 0x%X\n", ses_ulMsgId,ulEntityID);
		}

		break;
	}

	// an event has been received for an entity (i.e. Explode, Damage, Die...)
	case EMT_EVENT:
	{
		SLONG slDataSize;
		SLONG slEventCode;
		UWORD uwClassID;
		UWORD uwEventID;
		EntityClassEntry* peceEntry;
		CEntityEvent* peeEvent;
		CEntity* penEntity;

		ses_ulMsgId++;
		// get the entity ID, event code and event data from the message
		ses_emEntityMessage.ReadEntityEvent(ulEntityID, slEventCode, (void*)aubData, slDataSize);
		// extract the entity class id and event id
		// an event is uniquely identified only if both of these ids are supplied
		uwEventID = slEventCode & 0x0000FFFF;
		uwClassID = (slEventCode & 0xFFFF0000) >> 16;

		// get the pointer to the entity class entry in the class container
		peceEntry = FindClassInContainer(uwClassID);
		// it really should be there
		ASSERT(peceEntry != NULL);
		if (peceEntry == NULL) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Warning: Event received for an unknown entity class, EntityID: 0x%X\n"), ulEntityID);
			}
			break;
		}

		// report to console
		if (net_bReportClientTraffic) {
			//			CPrintF("%lu: EVENT:            EntityID: 0x%X     EventCode: 0x%X     DataSize: %d\n",ses_ulMsgId,ulEntityID,slEventCode,slDataSize);
		}

		CEntityClass* pecClass;

		// obtain the class from the stock
		try
		{
			pecClass = _pEntityClassStock->Obtain_t(peceEntry->ece_fnmEntityClass);
		}
		catch (char* strError)
		{
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors)
			{
				CPrintF(TRANS("Warning: Unable to obtain entity class from stock, class name: %s\n"), peceEntry->ece_fnmEntityClass);
				CPrintF("%s\n", strError);
			}
			break;
		}
		BOOL bFound = FALSE;

		// try to find the event in the event table for this class, and when found, create a new empty event
		for (int iEvent = 0; iEvent < pecClass->ec_pdecDLLClass->dec_ctEvents; iEvent++) {
			if (slEventCode == pecClass->ec_pdecDLLClass->dec_adeeEvents[iEvent]->dee_slEvent) {
				peeEvent = pecClass->ec_pdecDLLClass->dec_adeeEvents[iEvent]->dee_New();
				bFound = TRUE;
				break;
			}
		}
		// if must be there
		ASSERT(bFound);

		if (!bFound)
		{
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Warning: Unable to find requested entity event, class name: %s, event: %d\n"), peceEntry->ece_fnmEntityClass, uwEventID);
			}
			_pEntityClassStock->Release(pecClass);
			break;
		}

		// fill in the event data
		memcpy(((UBYTE*)peeEvent) + sizeof(CEntityEvent), aubData, slDataSize);

		// get the pointer to the entity
		if (!_pNetwork->ga_World.EntityExists(ulEntityID, penEntity)) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Warning: event received for non existing entity, EntityID: 0x%X\n"), ulEntityID);
			}
			_pEntityClassStock->Release(pecClass);
			delete (UBYTE*)peeEvent;
			break;
		}

		if (penEntity->IsFlagOn(ENF_DELETED))
		{
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Warning: event received for deleted entity, EntityID: 0x%X\n"), ulEntityID);
			}
			_pEntityClassStock->Release(pecClass);
			delete (UBYTE*)peeEvent;
			break;
		}

		// sent the event to the entity
		penEntity->SendEvent(*peeEvent);

		// handle the event
		CEntity::HandleSentEvents();



		// release the entity class from the stock (remove a reference)
		_pEntityClassStock->Release(pecClass);

		delete (UBYTE*)peeEvent;

		break;
	}
	// an entity should be initialized
	case EMT_INITIALIZE:
	{
		SLONG slDataSize;
		SLONG slEventCode;
		EntityClassEntry* peceEntry;
		CEntityEvent* peeEvent;
		CEntity* penEntity;
		UWORD uwClassID;
		UWORD uwEventID;

		ses_ulMsgId++;

		// get the entity ID, event code and event data from the message
		ses_emEntityMessage.ReadEntityInitialize(ulEntityID, slEventCode, (void*)aubData, slDataSize);
		// extract the entity class id and event id
		// an event is uniquely identified only if both of these ids are supplied
		uwEventID = slEventCode & 0x0000FFFF;
		uwClassID = (slEventCode & 0xFFFF0000) >> 16;
		// get the pointer to the entity class entry in the class container
		peceEntry = FindClassInContainer(uwClassID);
		// it isn't neccessary to get a non-null pointer here - it will be null for an event
		// from 'BaseEvents.h'

		// report to console
		if (net_bReportClientTraffic) {
			CPrintF("%lu: INITIALIZE:            EntityID: 0x%X     EntityClass: %d      EventID: %d     DataSize: %d\n", ses_ulMsgId, ulEntityID, uwClassID, uwEventID, slDataSize);
		}

		// get the pointer to the entity
		if (!_pNetwork->ga_World.EntityExists(ulEntityID, penEntity)) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Warning: initialize received for non existing entity, EntityID: 0x%X\n"), ulEntityID);
			}
			break;
		}

		EVoid eVoidEvent;
		// if this is en EVoid, initialize with default
		if (slEventCode == eVoidEvent.ee_slEvent) {
			penEntity->Initialize();
		}
		else
		{
			// if it's not an EVoid, check if we got a valid class entry
			ASSERT(peceEntry != NULL);

			CEntityClass* pecClass;

			try
			{
				pecClass = _pEntityClassStock->Obtain_t(peceEntry->ece_fnmEntityClass);
			}
			catch (char* strError) {
				extern INDEX net_bReportMiscErrors;
				if (net_bReportMiscErrors) {
					CPrintF(TRANS("Warning: Unable to obtain entity class from stock, class name: %s\n"), peceEntry->ece_fnmEntityClass);
					CPrintF("%s\n", strError);
				}
				break;
			}

			BOOL bFound = FALSE;

			// find the event in this class, and create a new empty event
			for (int iEvent = 0; iEvent < pecClass->ec_pdecDLLClass->dec_ctEvents; iEvent++) {
				if (slEventCode == pecClass->ec_pdecDLLClass->dec_adeeEvents[iEvent]->dee_slEvent) {
					peeEvent = pecClass->ec_pdecDLLClass->dec_adeeEvents[iEvent]->dee_New();
					bFound = TRUE;
					break;
				}
			}
			// it must be there
			ASSERT(bFound);

			if (!bFound)
			{
				extern INDEX net_bReportMiscErrors;
				if (net_bReportMiscErrors) {
					CPrintF(TRANS("Warning: Unable to find requested entity event, class name: %s, event: %d\n"), peceEntry->ece_fnmEntityClass, uwEventID);
				}
				_pEntityClassStock->Release(pecClass);
				break;
			}

			// fill in the data
			memcpy(((UBYTE*)peeEvent) + sizeof(CEntityEvent), aubData, slDataSize);

			// initialize the entity
			penEntity->Initialize(*peeEvent);

			// release the class (remove reference)
			_pEntityClassStock->Release(pecClass);

			delete (UBYTE*)peeEvent;
		}

		break;
	}
	// make an entity start playing an animation
	case EMT_STARTANIM:
	{
		CEntity* penEntity;
		INDEX iNewModelAnim;
		ULONG ulFlags;

		ses_ulMsgId++;
		// get the entity id, animation index and flags
		ses_emEntityMessage.ReadStartAnim(ulEntityID, iNewModelAnim, ulFlags);

		// get the pointer to the entity
		if (!_pNetwork->ga_World.EntityExists(ulEntityID, penEntity)) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				//CPrintF(TRANS("Warning: Start anim (not ska) received for non existing entity, EntityID: 0x%X\n"),ulEntityID);
			}
			break;
		}

		// do not do this for local players
		if (penEntity->IsPlayer() && (_pNetwork->IsPlayerLocal(penEntity))) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				//CPrintF(TRANS("Warning: Start anim (not ska) received for local player, EntityID: 0x%X\n"),ulEntityID);
			}
			break;
		};

		// play the animation 
		penEntity->StartModelAnim(iNewModelAnim, ulFlags);

		// report to the console
		if (net_bReportClientTraffic) {
			CPrintF("STARTANIM:            EntityID: 0x%X     NewAnim: %ld     Flags: 0x%X\n", ulEntityID, iNewModelAnim, ulFlags);
		}

		break;
	}
	// update for player data
	case EMT_PLAYERUPDATE:
	{
		CPlayerEntity* penPlayerEntity;
		CNetworkMessage nmMessage;
		CEntity* penEntity;

		ses_ulMsgId++;
		// get the player entity id
		ses_emEntityMessage.ReadPlayerUpdate(ulEntityID, nmMessage);
		if (!_pNetwork->ga_World.EntityExists(ulEntityID, penEntity)) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Warning: update received for non existing player!\n"));
			}
			break;
		}
		ASSERT(penEntity->IsPlayer());
		if (!penEntity->IsPlayer()) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Warning: player update received with non-player entity id !\n"));
			}
			break;
		}

		// the pointer to the player entity
		penPlayerEntity = (CPlayerEntity*)penEntity;

		// report to the console
		if (net_bReportClientTraffic) {
			//0203
			//				CPrintF("PLAYERUPDATE:            EntityID: 0x%X \n",ulEntityID);
		}

		// find the PlayerSource for this entity - will produce a non null pointer only for local players
		CPlayerSource* pplsSource = _pNetwork->GetPlayerSource(penPlayerEntity);
		// if it's a local player and the game isn't paused
		// if it's a local player, read it's data and reapply local prediction
		if (_pNetwork->IsPlayerLocal(penEntity) || _pNetwork->IsPlayingDemo()) {
			if (!_pNetwork->IsPlayingDemo()) {
				ASSERT(pplsSource != NULL);
				if (pplsSource == NULL) {
					extern INDEX net_bReportMiscErrors;
					if (net_bReportMiscErrors) {
						CPrintF(TRANS("Warning: player source for local player does not exist!\n"));
					}
					break;
				}
			}//0202*/
			//0130 5line �����
			/*
			penPlayerEntity->Read_net(&nmMessage,ses_emEntityMessage.em_tmMessageTime);

			  if (!_pNetwork->IsPlayingDemo()) {
			  // apply all actions not executed by the server - local prediction
			  pplsSource->ApplyNewerActions(penPlayerEntity->m_iLastActionTime);
			  }
			*/
			// if it's no a local player, read data and apply dead reckoning
			//0202/*	
		}
		/*
		else
		{
		static bFirst=TRUE;
		if(bFirst){
		penPlayerEntity->Read_net_brief(&nmMessage,ses_emEntityMessage.em_tmMessageTime);
		bFirst=FALSE;
		CPrintF(TRANS("Read_net_brief!\n"));
		}

		  }
		*/


		break;
	}
	/*
	// read base placement
	case EMT_BASEPLACEMENT:
	{
	ses_emEntityMessage.ReadBasePosition(_vBasePosition);
	_bBasePositionSet = TRUE;

	  // report to console
	  if (net_bReportClientTraffic) {
	  CPrintF("BASEPLACEMENT:           Position: %f, %f, %f\n",_vBasePosition(1),_vBasePosition(2),_vBasePosition(3));
	  }

		break;
						}*/

						// ska animation event
	case EMT_SKA_ANIM:
	{
		CEntity* penEntity;
		UBYTE ubSkaCode;
		SLONG slDataSize = ESKA_MAX_DATA_SIZE;
		static UBYTE aubSkaData[ESKA_MAX_DATA_SIZE];
		UBYTE* pubData = aubSkaData;

		ses_ulMsgId++;
		// get the entity id
		ses_emEntityMessage.ReadSka(ulEntityID, ubSkaCode, aubSkaData, slDataSize);
		// the pointer to the entity
		if (!_pNetwork->ga_World.EntityExists(ulEntityID, penEntity)) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				//CPrintF(TRANS("Warning: SKA event received for non existing entity, EntityID: 0x%X\n"),ulEntityID);            
			}
			break;
		}
		//penEntity = _pNetwork->ga_World.EntityFromID(ulEntityID);
		// if it fails in the release version, don't crash ;)
		if (penEntity == NULL) break;
		if (penEntity->en_RenderType != CEntity::RT_SKAMODEL && penEntity->en_RenderType != CEntity::RT_SKAEDITORMODEL) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Warning: SKA event received for non SKA entity, EntityID: 0x%X\n"), ulEntityID);
			}
			break;
		}

		switch (ubSkaCode)
		{
		case EM_SKA_ADD:
		{
			INDEX iAnimID, iLocalAnimID, iGroupID, iLocalGroupID, iModelInstanceID, iLocalModelInstanceID;
			ULONG ulFlags;
			FLOAT fStrength, fSpeedMul;
			extern CStaticStackArray<INDEX> _aiNetSkaIDConversion;

			//				ska_StringToID("Windwalker");

			iAnimID = *(INDEX*)pubData; pubData += sizeof(iAnimID);
			ulFlags = *(ULONG*)pubData; pubData += sizeof(ulFlags);
			fStrength = *(FLOAT*)pubData; pubData += sizeof(fStrength);
			iGroupID = *(INDEX*)pubData; pubData += sizeof(iGroupID);
			iModelInstanceID = *(INDEX*)pubData; pubData += sizeof(iModelInstanceID);
			fSpeedMul = *(FLOAT*)pubData;

			iLocalAnimID = _aiNetSkaIDConversion[iAnimID];
			iLocalGroupID = _aiNetSkaIDConversion[iGroupID];
			if (iModelInstanceID == ESKA_MASTER_MODEL_INSTANCE) {
				iLocalModelInstanceID = ESKA_MASTER_MODEL_INSTANCE;
			}
			else {
				iLocalModelInstanceID = _aiNetSkaIDConversion[iModelInstanceID];
			}

			penEntity->AddAnimation(iLocalAnimID, ulFlags, fStrength, iLocalGroupID, iLocalModelInstanceID, fSpeedMul);

			break;
		}
		case EM_SKA_REM:
		{
			INDEX iAnimID, iLocalAnimID, iModelInstanceID, iLocalModelInstanceID;

			iAnimID = *(INDEX*)pubData; pubData += sizeof(iAnimID);
			iModelInstanceID = *(INDEX*)pubData; pubData += sizeof(iModelInstanceID);
			iLocalAnimID = _aiNetSkaIDConversion[iAnimID];
			if (iModelInstanceID == ESKA_MASTER_MODEL_INSTANCE) {
				iLocalModelInstanceID = ESKA_MASTER_MODEL_INSTANCE;
			}
			else {
				iLocalModelInstanceID = _aiNetSkaIDConversion[iModelInstanceID];
			}

			penEntity->RemAnimation(iLocalAnimID, iLocalModelInstanceID);

			break;
		}
		case EM_SKA_REMID:
		{
			INDEX iGroupID, iModelInstanceID, iLocalModelInstanceID;

			iGroupID = *(INDEX*)pubData; pubData += sizeof(iGroupID);
			iModelInstanceID = *(INDEX*)pubData; pubData += sizeof(iModelInstanceID);

			if (iModelInstanceID == ESKA_MASTER_MODEL_INSTANCE) {
				iLocalModelInstanceID = ESKA_MASTER_MODEL_INSTANCE;
			}
			else {
				iLocalModelInstanceID = _aiNetSkaIDConversion[iModelInstanceID];
			}

			penEntity->RemAnimsWithID(iGroupID, iLocalModelInstanceID);

			break;
		}
		case EM_SKA_NEWCLONED:
		{
			INDEX iModelInstanceID, iLocalModelInstanceID;
			FLOAT fFadeTime;

			fFadeTime = *(FLOAT*)pubData; pubData += sizeof(fFadeTime);
			iModelInstanceID = *(INDEX*)pubData; pubData += sizeof(iModelInstanceID);
			if (iModelInstanceID == ESKA_MASTER_MODEL_INSTANCE) {
				iLocalModelInstanceID = ESKA_MASTER_MODEL_INSTANCE;
			}
			else {
				iLocalModelInstanceID = _aiNetSkaIDConversion[iModelInstanceID];
			}

			penEntity->NewClonedState(fFadeTime, iLocalModelInstanceID);

			break;
		}
		case EM_SKA_NEWCLEAR:
		{
			INDEX iModelInstanceID, iLocalModelInstanceID;
			FLOAT fFadeTime;

			fFadeTime = *(FLOAT*)pubData; pubData += sizeof(fFadeTime);
			iModelInstanceID = *(INDEX*)pubData; pubData += sizeof(iModelInstanceID);
			if (iModelInstanceID == ESKA_MASTER_MODEL_INSTANCE) {
				iLocalModelInstanceID = ESKA_MASTER_MODEL_INSTANCE;
			}
			else {
				iLocalModelInstanceID = _aiNetSkaIDConversion[iModelInstanceID];
			}

			penEntity->NewClearState(fFadeTime, iLocalModelInstanceID);

			break;
		}
		case EM_SKA_STRETCH:
		{
			INDEX iModelInstanceID, iLocalModelInstanceID;
			FLOAT3D vStretch;

			vStretch(1) = *(FLOAT*)pubData; pubData += sizeof(FLOAT);
			vStretch(2) = *(FLOAT*)pubData; pubData += sizeof(FLOAT);
			vStretch(3) = *(FLOAT*)pubData; pubData += sizeof(FLOAT);
			iModelInstanceID = *(INDEX*)pubData; pubData += sizeof(iModelInstanceID);
			if (iModelInstanceID == ESKA_MASTER_MODEL_INSTANCE) {
				iLocalModelInstanceID = ESKA_MASTER_MODEL_INSTANCE;
			}
			else {
				iLocalModelInstanceID = _aiNetSkaIDConversion[iModelInstanceID];
			}

			penEntity->StretchModel(vStretch, iLocalModelInstanceID);

			break;
		}
		case EM_SKA_STRETCHSINGLE:
		{
			INDEX iModelInstanceID, iLocalModelInstanceID;
			FLOAT3D vStretch;

			vStretch(1) = *(FLOAT*)pubData; pubData += sizeof(FLOAT);
			vStretch(2) = *(FLOAT*)pubData; pubData += sizeof(FLOAT);
			vStretch(3) = *(FLOAT*)pubData; pubData += sizeof(FLOAT);
			iModelInstanceID = *(INDEX*)pubData; pubData += sizeof(iModelInstanceID);
			if (iModelInstanceID == ESKA_MASTER_MODEL_INSTANCE) {
				iLocalModelInstanceID = ESKA_MASTER_MODEL_INSTANCE;
			}
			else {
				iLocalModelInstanceID = _aiNetSkaIDConversion[iModelInstanceID];
			}

			penEntity->StretchSingleModel(vStretch, iLocalModelInstanceID);

			break;
		}
		default:
		{
			ASSERT(FALSE);
		}
		}
		break;
	}
	// pause/unpause game
	case EMT_PAUSE:
	{
		CTString strPauser;
		BOOL bPauseBefore = ses_bPause;

		ses_ulMsgId++;
		// read the new pause state
		ses_emEntityMessage.ReadPause(ses_bPause, strPauser);

		// report to console
		if (net_bReportClientTraffic) {
			CPrintF("PAUSE.\n");
		}

		// report who paused
		if (ses_bPause != bPauseBefore) {
			if (ses_bPause) {
				CPrintF(TRANS("Paused by '%s'\n"), strPauser);
			}
			else {
				CPrintF(TRANS("Unpaused by '%s'\n"), strPauser);
			}
		}

		// must keep wanting current state
		ses_bWantPause = ses_bPause;

		break;
	}///*
	case EMT_REMPLAYER:
	{
		INDEX iPlayer;

		ses_ulMsgId++;
		// read the new pause state
		ses_emEntityMessage.ReadRemovePlayer(iPlayer);

		// report to console
		//if (net_bReportClientTraffic) {
		CPrintF("REMPLAYER:     %s   index: %ld\n", (const char*)_pNetwork->ga_srvServer.srv_apltPlayers[iPlayer].plt_pcCharacter.pc_strName, iPlayer);
		//}

		CPlayerTarget& plt = _pNetwork->ga_srvServer.srv_apltPlayers[iPlayer];
		if (plt.plt_penPlayerEntity == NULL) {
			if (plt.IsActive()) {
				_pNetwork->ga_srvServer.srv_apltPlayers[iPlayer].Deactivate();
			}
			return SUCCESS_OK;
		}

		// inform entity of disconnnection
		CPrintF(TRANS("%s left\n"), _pNetwork->ga_srvServer.srv_apltPlayers[iPlayer].plt_penPlayerEntity->GetPlayerName());
		_pNetwork->ga_srvServer.srv_apltPlayers[iPlayer].plt_penPlayerEntity->Disconnect();
		// deactivate the player
		_pNetwork->ga_srvServer.srv_apltPlayers[iPlayer].Deactivate();
		// handle all the sent events
		ses_bAllowRandom = TRUE;
		CEntity::HandleSentEvents();
		ses_bAllowRandom = FALSE;

		break;
	}
	//0205	
	/*
	case EMT_PLAYER_MOVE:{


		CPlayerTarget &plt = _pNetwork->ga_srvServer.srv_apltPlayers[iPlayer];

		  plt->plt_penPlayerEntity->ClearMovingTemp();
		  plt->plt_penPlayerEntity->PreMoving();
		  plt->plt_penPlayerEntity->DoMoving();
		  plt->plt_penPlayerEntity->PostMoving();
		  plt->plt_penPlayerEntity->ClearMovingTemp();
		  CEntity::HandleSentEvents();

			plt->ApplyActionPacket(paAction);
			plt->plt_penPlayerEntity->SetActionApplied();

			  break;
			  }
	*/
	////////////////////////////////						

	case EMT_CHANGECHARACTER:
	{
		CPlayerCharacter pcCharacter;
		CEntity* penEntity;

		ses_ulMsgId++;

		// extract neccessary data from the message
		ses_emEntityMessage.ReadcharacterChange(ulEntityID, pcCharacter);

		// get the pointer to the entity
		if (!_pNetwork->ga_World.EntityExists(ulEntityID, penEntity)) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Warning: Change character received for non existing entity, EntityID: 0x%X\n"), ulEntityID);
			}
			break;
		}
		CPlayerEntity* penPlayerEntity = (CPlayerEntity*)penEntity;

		// change the character
		penPlayerEntity->CharacterChanged(pcCharacter);

		// report to console
		if (net_bReportClientTraffic) {
			CPrintF("%lu: CHARACTERCHANGE:     EntityID: 0x%X\n", ulEntityID);
		}

		break;
	}

	// sound animation event
	case EMT_SOUND:
	{
		CEntity* penEntity;
		UBYTE ubSoundCode;
		SLONG slDataSize = ESOUND_MAX_DATA_SIZE;
		static UBYTE aubSoundData[ESOUND_MAX_DATA_SIZE];
		UBYTE* pubData = aubSoundData;
		ULONG ulComponentOffset;
		CSoundObject* psoSoundObject;

		ses_ulMsgId++;
		// get the entity id
		ses_emEntityMessage.ReadSound(ulEntityID, ubSoundCode, aubSoundData, slDataSize);
		// the pointer to the entity
		if (!_pNetwork->ga_World.EntityExists(ulEntityID, penEntity)) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				//CPrintF(TRANS("Warning: Sound event received for non existing entity, EntityID: 0x%X\n"),ulEntityID);            
			}
			break;
		}



		switch (ubSoundCode)
		{
		case EM_SOUND_PLAY:
		{
			SLONG idSoundComponent;
			SLONG slPlayType;
			UBYTE ubThis;
			ULONG ulOwnerID;
			CEntity* penSoOwner = penEntity;

			ubThis = *(UBYTE*)pubData; pubData += sizeof(ubThis);
			if (!ubThis) {
				ulOwnerID = *(ULONG*)pubData; pubData += sizeof(ulOwnerID);
				if (!_pNetwork->ga_World.EntityExists(ulOwnerID, penSoOwner)) {
					extern INDEX net_bReportMiscErrors;
					if (net_bReportMiscErrors) {
						CPrintF(TRANS("Warning: Sound event received for non existing entity, OwnerID: 0x%X\n"), ulOwnerID);
					}
					break;
				}
			}
			if (penEntity->IsPlayer() && _pNetwork->IsPlayerLocal(penEntity)) {
				break;
			}
			ulComponentOffset = *(ULONG*)pubData;  pubData += sizeof(ulComponentOffset);
			idSoundComponent = *(SLONG*)pubData;   pubData += sizeof(idSoundComponent);
			slPlayType = *(SLONG*)pubData; pubData += sizeof(slPlayType);
			psoSoundObject = (CSoundObject*)(((UBYTE*)penSoOwner) + ulComponentOffset);
			penEntity->PlaySound(*psoSoundObject, idSoundComponent, slPlayType);
			// report to console
			if (net_bReportClientTraffic) {
				CPrintF("%lu: SOUND_PLAY:     EntityID: 0x%X\n", ulEntityID);
			}
			break;
		}
		case EM_SOUND_STOP:
		{
			ulComponentOffset = *(ULONG*)pubData;  pubData += sizeof(ulComponentOffset);
			psoSoundObject = (CSoundObject*)(((UBYTE*)penEntity) + ulComponentOffset);
			psoSoundObject->Stop();
			// report to console
			if (net_bReportClientTraffic) {
				CPrintF("%lu: EM_SOUND_Stop:     EntityID: 0x%X\n", ulEntityID);
			}
			break;
		}
		case EM_SOUND_SETVOLUME:
		{
			ulComponentOffset = *(ULONG*)pubData;    pubData += sizeof(ulComponentOffset);
			FLOAT fVolume = ((FLOAT)(*(UBYTE*)pubData)) / 127.0f;  pubData += sizeof(UBYTE);
			psoSoundObject = (CSoundObject*)(((UBYTE*)penEntity) + ulComponentOffset);
			psoSoundObject->SetVolume(fVolume);
			// report to console
			if (net_bReportClientTraffic) {
				CPrintF("%lu: EM_SOUND_SETVOLUME:     EntityID: 0x%X\n", ulEntityID);
			}
			break;
		}
		case EM_SOUND_SETPITCH:
		{
			ulComponentOffset = *(ULONG*)pubData;  pubData += sizeof(ulComponentOffset);
			FLOAT fPitch = ((FLOAT)(*(UBYTE*)pubData)) / 63.0f;  pubData += sizeof(UBYTE);
			psoSoundObject = (CSoundObject*)(((UBYTE*)penEntity) + ulComponentOffset);
			psoSoundObject->SetPitch(fPitch);
			// report to console
			if (net_bReportClientTraffic) {
				CPrintF("%lu: EM_SOUND_SETPITCH:     EntityID: 0x%X\n", ulEntityID);
			}
			break;
		}
		case EM_SOUND_SETRANGE:
		{
			ulComponentOffset = *(ULONG*)pubData;   pubData += sizeof(ulComponentOffset);
			FLOAT fHotSpot = ((FLOAT)(*(UWORD*)pubData)) / 5.0f;  pubData += sizeof(UWORD);
			FLOAT fFallOff = ((FLOAT)(*(UWORD*)pubData)) / 5.0f;  pubData += sizeof(UWORD);
			psoSoundObject = (CSoundObject*)(((UBYTE*)penEntity) + ulComponentOffset);
			psoSoundObject->SetRange(fHotSpot, fFallOff);
			// report to console
			if (net_bReportClientTraffic) {
				CPrintF("%lu: EM_SOUND_SETRANGE:     EntityID: 0x%X\n", ulEntityID);
			}
			break;
		}
		case EM_SOUND_FADE:
		{
			ulComponentOffset = *(ULONG*)pubData;    pubData += sizeof(ulComponentOffset);
			FLOAT fVolume = ((FLOAT)(*(UBYTE*)pubData)) / 127.0f;  pubData += sizeof(UBYTE);
			TIME tmPeriod = *((TIME*)pubData);  pubData += sizeof(TIME);
			psoSoundObject = (CSoundObject*)(((UBYTE*)penEntity) + ulComponentOffset);
			psoSoundObject->Fade(fVolume, tmPeriod);
			// report to console
			if (net_bReportClientTraffic) {
				CPrintF("%lu: EM_SOUND_FADE:     EntityID: 0x%X, period: %7.4f, volume: %7.4f\n", ses_ulMsgId, ulEntityID, tmPeriod, fVolume);
			}
			break;
		}

		default:
		{
			ASSERT(FALSE);
		}
		}

		break;
	}
	// add a new string to ska string table & net coversion table
	case EMT_ADDSKASTRING:
	{
		CTString strString;
		INDEX iServerIndex;

		ses_ulMsgId++;
		// read server ska ID and ska string to be added
		ses_emEntityMessage.ReadAddSkaString(iServerIndex, strString);

		// add it to the local table
		INDEX iLocalIndex = ska_GetIDFromStringTable(strString);

		ASSERT(_aiNetSkaIDConversion.Count() == iServerIndex);

		// report to console
		if (net_bReportClientTraffic) {
			CPrintF("EMT_ADDSKASTRING:  String  '%s' added to ska table, Local ID is:  %ld, Server ID is: %ld\n", (const char*)strString, iLocalIndex, iServerIndex);
		}

		// expand the conversion array, and make a new entry
		INDEX& iNewIndex = _aiNetSkaIDConversion.Push();
		iNewIndex = iLocalIndex;

		break;
	}
	case EMT_SETPLACEMENT_NOTIFY:
	{
		extern INDEX net_bReportMiscErrors;
		if (net_bReportMiscErrors) {
			CPrintF(TRANS("Warning: server received EMT_SETPLACEMENT_NOTIFY\n"));
		}
		break;
	}
	// update for player data
	case EMT_PLAYERACTION:
	{
		CPlayerEntity* penPlayerEntity;
		CPlayerAction paAction;
		CEntity* penEntity;

		ASSERT(_pNetwork->IsPlayingDemo());

		ses_ulMsgId++;
		// get the player entity id
		ses_emEntityMessage.ReadPlayerAction(ulEntityID, paAction);
		if (!_pNetwork->ga_World.EntityExists(ulEntityID, penEntity)) {
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Warning: player action for non existing player!\n"));
			}
			break;
		}
		ASSERT(penEntity->IsPlayer());
		if (!penEntity->IsPlayer())
		{
			extern INDEX net_bReportMiscErrors;
			if (net_bReportMiscErrors) {
				CPrintF(TRANS("Warning: player action received with non-player entity id !\n"));
			}
			break;
		}

		// the pointer to the player entity
		penPlayerEntity = (CPlayerEntity*)penEntity;

		// report to the console
		if (net_bReportClientTraffic) {
			CPrintF("PLAYERACTION:            EntityID: 0x%X \n", ulEntityID);
		}

		// apply this action
		penPlayerEntity->ApplyAction(paAction, 0);

		// run all player updates
		penPlayerEntity->ClearMovingTemp();
		penPlayerEntity->PreMoving();
		penPlayerEntity->DoMoving();
		penPlayerEntity->PostMoving();
		penPlayerEntity->ClearMovingTemp();

		if (penPlayerEntity->en_penParent != NULL && penPlayerEntity->en_penParent->GetPhysicsFlags() & EPF_MOVABLE)
		{
			penPlayerEntity->en_plLastPlacement.pl_PositionVector = penPlayerEntity->en_plPlacement.pl_PositionVector -
				((CMovableEntity*)(penPlayerEntity->en_penParent))->en_vCurrentTranslationAbsolute * _pTimer->TickQuantum;
		}

		break;
	}
	//    default: {
	//        ASSERT(FALSE);
	//        break;
	//			 }
	}
	return TRUE;
};


// receive new tick data from the server
void CSessionState::ReceiveTick(TIME tmTickTime, UBYTE* pubData, SLONG slSize)
{

	ASSERT(pubData != NULL);
	ASSERT(slSize >= 0);
	float fRandom;

	//	extern INDEX net_bReportClientTraffic;

		// emulate bad network conditions
	fRandom = rand() / (float)RAND_MAX;
	// if tick data is newer than the last data received, and it shouldn't be dropped
	if (ses_tmLastTickTime < tmTickTime && fRandom >= cli_fTickDropRate) {
		// report to console
		if (net_bReportClientTraffic) {
			//0203      CPrintF(TRANS("Client reading tick, time: %5.2f\n"),tmTickTime);
		}
		// put the data into the input buffer
		ses_embReceiveBuffer.WriteTick(tmTickTime, pubData, slSize);
		// send tick acknowledge to server
		if (!_pNetwork->IsPlayingDemo()) {
			SendAcknowledge(tmTickTime);
		}
		// if tick data is older than last received, just send the acknowledge
	}
	else if (fRandom >= cli_fTickDropRate) {
		if (!_pNetwork->IsPlayingDemo()) {
			SendAcknowledge(tmTickTime);
		}
	}

};


// acknowledge that tick data for a certian tick time has been received
void CSessionState::SendAcknowledge(float fTickTime)
{
	//	extern INDEX net_bReportClientTraffic;

		// report to console
	if (net_bReportClientTraffic) {
		//0203    CPrintF(TRANS("Send acknowledge: %5.2f\n"), fTickTime);
	}
};

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *istr - 
//-----------------------------------------------------------------------------
void CSessionState::ReceiveChatMessage(CNetworkMessage* istr)
{
	CTString str;
	CTString strSendName;
	CTString strRecvName;
	BYTE	chChannel = 0; // ä�� �ѹ� (MSG_CHAT_CHANNEL_LEVEL, MSG_CHAT_CHANNEL_TRADE ������ ó��)
	unsigned char chattype;
	SLONG 	 sendindex;
	SLONG	 slGroup = -1;

	(*istr) >> chattype; //0528 kwon
	(*istr) >> sendindex;
	(*istr) >> strSendName;

	if (chattype == MSG_CHAT_CHANNEL_LEVEL || chattype == MSG_CHAT_CHANNEL_TRADE)
	{
		(*istr) >> chChannel; // BYTE (���� ä�� ����)
	}
	else
	{
		(*istr) >> strRecvName; // string (�޴� ��� �̸�?)
	}

	(*istr) >> str;

	// [sora] ������ �׷� ä��
	if (chattype == MSG_CHAT_EXPEDITION)
	{
		(*istr) >> slGroup; // ������ �׷� ����
	}

	// ��Ŀ ���� �޼��� ǥ��.
	if (chattype == MSG_CHAT_RANKER_CONN)
	{
		SBYTE sbJob = atoi(str);
		CTString	strMessage;
		strMessage.PrintF(_S(2358, "%sŬ���� ��Ŀ %s���� �����Ͽ����ϴ�."), CJobInfo::getSingleton()->GetName(sbJob, 0), strSendName);

		_UIAutoHelp->SetGMNotice(strMessage, 0x38FFD7FF);
		return;
	}

	CUIManager* pUIManager = CUIManager::getSingleton();

	// Date : 2005-05-25(���� 11:41:19), By Lee Ki-hwan
	if (chattype == MSG_CHAT_MESSENGER)
	{
		/***
		if( !pUIManager->GetMessenger()->IsUseLevel() ) return;
		pUIManager->GetMessenger()->RevTalk( sendindex, strSendName, strRecvName, str );
		return;
		***/
	}
	SLONG	ItemTotal, isItem;
	ULONG	uniIndex, index, plus, used, used2, nowDurability, maxDurability, starPos, endPos;
	ULONG   flag, flagMain;
	SBYTE	Wearing, sbOptionCount, sbOptionType;
	LONG	lOptionLevel;
	if (slGroup == -1 && !(chattype == MSG_CHAT_CHANNEL_LEVEL || chattype == MSG_CHAT_CHANNEL_TRADE || chattype == MSG_CHAT_WHISPER))
		(*istr) >> isItem;
	(*istr) >> isItem;
	if (isItem == 1)
	{
		if (_UICharacterChatFilter.Filtering(strSendName.str_String) == TRUE)
			return;
		(*istr) >> ItemTotal;
		if (ItemTotal <= 0 || ItemTotal > 5)
			return;
		pUIManager->GetChattingUI()->ItemChatCountFromServer = 0;
		for (int i = 0; i < ItemTotal; i++)
		{
			(*istr) >> uniIndex;
			(*istr) >> index;
			(*istr) >> Wearing;
			(*istr) >> plus;
			(*istr) >> flagMain;
			(*istr) >> flag;
			(*istr) >> used;
			(*istr) >> used2;
			(*istr) >> nowDurability;
			(*istr) >> maxDurability;
			(*istr) >> starPos;
			(*istr) >> endPos;
			(*istr) >> sbOptionCount;
			CItemData* pItemData = _pNetwork->GetItemData(index);
			if (!pItemData) continue;
			CItems* pItem = NULL;
			pItem = new CItems;
			pItem->ItemData = pItemData;
			pItem->SetData(index, uniIndex, -1, -1, plus, flag, -1, used, used2, Wearing, 1);
			pItem->SetDurability(nowDurability, maxDurability);
			if (pItemData->GetFlag() & ITEM_FLAG_RARE)
			{
				if (sbOptionCount == 0)
				{
					pItem->SetRareIndex(0);
				}
				else
				{
					(*istr) >> sbOptionType;
					(*istr) >> lOptionLevel;
					LONG iRareIndex = lOptionLevel;
					pItem->SetRareIndex(iRareIndex);
					(*istr) >> sbOptionType;
					(*istr) >> lOptionLevel;
					WORD iRareOption = lOptionLevel;
					WORD wCBit = 1;
					SBYTE sbOption = -1;
					for (int iBit = 0; iBit < 10; ++iBit)
					{
						if (iRareOption & wCBit)
						{
							CItemRareOption* pItemOption = CItemRareOption::getData(iRareIndex);
							if (pItemOption == NULL)
								continue;
							if (pItemOption->GetIndex() < 0)
								continue;
							int OptionType = pItemOption->rareOption[iBit].OptionIdx;
							int OptionLevel = pItemOption->rareOption[iBit].OptionLevel;
							pItem->SetOptionData(++sbOption, OptionType, OptionLevel, ORIGIN_VAR_DEFAULT);
						}
						wCBit <<= 1;
					}
				}
			}
			else
			{
				LONG lOriginOptionVar = ORIGIN_VAR_DEFAULT;
				for (SBYTE sbOption = 0; sbOption < sbOptionCount; sbOption++)
				{
					(*istr) >> sbOptionType;
					(*istr) >> lOptionLevel;
					if (pItemData->GetFlag() & ITEM_FLAG_ORIGIN)
					{
						(*istr) >> lOriginOptionVar;
					}
					pItem->SetOptionData(sbOption, sbOptionType, lOptionLevel, lOriginOptionVar);
				}
			}
			if (pItemData->GetFlag() & ITEM_FLAG_ORIGIN)
			{
				SBYTE sbBelong, sbSkillcont;
				LONG lSkillIndex;
				SBYTE sbSkillLevel;
				(*istr) >> sbBelong;
				(*istr) >> sbSkillcont;
				pItem->SetItemBelong(sbBelong);
				for (SBYTE sbSkillpos = 0; sbSkillpos < sbSkillcont; sbSkillpos++)
				{
					(*istr) >> lSkillIndex;
					(*istr) >> sbSkillLevel;
					pItem->SetItemSkill(sbSkillpos, lSkillIndex, sbSkillLevel);
				}
			}
			ULONG	plus2;
			(*istr) >> plus2;
			pItem->SetItemPlus2(plus2);
			if (pItemData->GetFlag() & ITEM_FLAG_SOCKET)
			{
				SBYTE	sbSocketCreateCount = 0;
				SBYTE	sbSocketCount = 0;
				LONG	lSocketJewelIndex = 0;
				LONG	lSocketInfo;
				int	i;
				for (i = 0; i < JEWEL_MAX_COUNT; i++)
				{
					(*istr) >> lSocketInfo;
					if (lSocketInfo >= 0)
					{
						sbSocketCreateCount++;
						pItem->SetSocketOption(i, lSocketInfo);
					}
				}
				pItem->SetSocketCount(sbSocketCreateCount);
			}
			ItemChat itemChat;
			itemChat.item = pItem;
			itemChat.StartPos = starPos;
			itemChat.EndPos = endPos;
			itemChat.CountShow = 0;
			itemChat.typeChat = -1;
			pUIManager->GetChattingUI()->ItemsChat.push_back(itemChat);
			pUIManager->GetChattingUI()->ItemChatCountFromServer++;
		}
	}

	pUIManager->GetChattingUI()->AddChatMessage(chattype, sendindex, strSendName, str, chChannel, slGroup);
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *istr - 
//-----------------------------------------------------------------------------
void CSessionState::ReceiveLoginMessage(CNetworkMessage* istr)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if ((*istr).GetType() == MSG_LOGINSERV_PLAYER)
	{
		_pSound->Mute();
		ReceiveServerListMessage(&(*istr));
		//_pNetwork->m_bSendMessage = FALSE;

#ifdef RESTRICT_SOUND
		extern BOOL _bNTKernel;
		//if( _bNTKernel )
		_pSound->UpdateSounds();
#endif		
	}
	else if ((*istr).GetType() == MSG_EXTEND)
	{
		LONG	ubType;
		(*istr) >> ubType;

		//if( ubType == MSG_EX_SECURE_CARD)
		{
			UBYTE cSecurityCode[4];

			(*istr) >> cSecurityCode[0];
			(*istr) >> cSecurityCode[1];
			(*istr) >> cSecurityCode[2];
			(*istr) >> cSecurityCode[3];

			//pUIManager->GetLogin()->SecurityCardSet(cSecurityCode);
		}

		_pNetwork->m_bSendMessage = FALSE;
	}
	else
	{
		unsigned char dbtype;
		(*istr) >> dbtype;

		// FIXME : bFail�� �Ź� üũ�ϴ°� ���� ���� ����...
		static BOOL bFail = FALSE;

		if ((*istr).GetType() == MSG_FAIL)
		{
			//wooss 050824
			// ----------->

			if (dbtype == MSG_FAIL_NOTLEVEL_FORDELETE)
			{
				_pGameState->DisplayErrorMessage(dbtype, UI_NONE, MSGCMD_NULL);
				// WSS_TIMEOUT_BUGFIX 070607 ------->><<
				_pNetwork->m_bSendMessage = FALSE;
				return;
			}
			// <----------
			else if (dbtype == MSG_FAIL_WRONG_IDENTIFICATION)			// �ֹι�ȣ Ʋ��
			{
				pUIManager->CloseMessageBox(MSGCMD_NULL);
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(42, "���� �߻�"), UMBS_OK,
					UI_NONE, MSGCMD_NULL);
				MsgBoxInfo.AddString(_S(2359, "�ֹε�� ��ȣ�� ��ġ���� �ʾ� ĳ���͸� ������ �� �����ϴ�."));

				pUIManager->CreateMessageBox(MsgBoxInfo);
				pUIManager->GetCharacterSelect()->Lock(FALSE);
				// WSS_TIMEOUT_BUGFIX 070607 ------->><<
				_pNetwork->m_bSendMessage = FALSE;
				return;
			}
			else if (dbtype == MSG_FAIL_SCARD_NOT_MATCHING)	//����ī�� ���� ��ȣ Ʋ��
			{
				pUIManager->CloseMessageBox(MSGCMD_NULL);
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(3667, "���� ī��"), UMBS_OK,
					UI_NONE, MSGCMD_NULL);
				MsgBoxInfo.AddString(_S(3669, "���� ī�� ���� ����"));

				pUIManager->CreateMessageBox(MsgBoxInfo);
				pUIManager->GetLogin()->Lock(FALSE);
				_pNetwork->m_bSendMessage = FALSE;

				//pUIManager->GetLogin()->SecurityCardSet(NULL);
				return;
			}
			else if (dbtype == MSG_FAIL_LOGINSERV_BLOCK_USER)
			{	// �н����� 3�� Ʋ��
				pUIManager->CloseMessageBox(MSGCMD_NULL);
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(42, "���� �߻�"), UMBS_YESNO, UI_NONE, MSGCMD_LOGINSERV_BLOCK_USER);
				MsgBoxInfo.AddString(_S(4116, "��й�ȣ 3ȸ ������ 30�а� ������ �� �����ϴ�. ������ ���Ͻø� ������Ʈ �α����� ���� ������ ������ �޴����� ���Ӻ��� ���� ��ư�� �����ּ���."));
				pUIManager->CreateMessageBox(MsgBoxInfo);
				pUIManager->GetLogin()->Lock(FALSE);
				_pNetwork->m_bSendMessage = FALSE;
				return;
			}
			else if (dbtype == MSG_FAIL_CANNOT_CONNECT_SHUTDOWN_TIME)
			{
				pUIManager->CloseMessageBox(MSGCMD_NULL);
				CUIMsgBox_Info	MsgBoxInfo;
				CTString strMessage;
				//strMessage.PrintF( _s( "%s���� �˴ٿ��� ���� ��� �������� Ȯ�εǾ� ���� ������ �Ұ��� �մϴ�.(00:00~06:00) ���ǻ����� �����������ͷ� ���� �ֽʽÿ�. Ȯ���� ������ ������ ���� �˴ϴ�." ), pUIManager->GetLogin()->GetUserId() );

				MsgBoxInfo.SetMsgBoxInfo(_S(42, "���� �߻�"), UMBS_YESNO, UI_NONE, MSGCMD_SHUTDOWN_TIME);
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
				return;
			}
			else if (dbtype == MSG_FAIL_DB_CANNOT_DEL_CHAR)	// [2012/07/05 : Sora]  ĳ���� ���� Ȯ��
			{
				pUIManager->CloseMessageBox(MSGCMD_NULL);
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(42, "���� �߻�"), UMBS_YESNO, UI_NONE, MSGCMD_NULL);
				MsgBoxInfo.AddString(_S(5704, "�߰� ĳ���� ���� ���� �Ⱓ ����� ĳ���͸� ������ �� �����ϴ�."));
				pUIManager->CreateMessageBox(MsgBoxInfo);
				pUIManager->GetCharacterSelect()->Lock(FALSE);
				return;
			}
			_pGameState->DisplayErrorMessage(dbtype, UI_NONE, MSGCMD_LOGIN_ERROR);

			// NOTE : ĳ���� ���� ���нÿ��� ���� ȭ������ �Ѿ�� �ȵǱ� ������ �÷��� üũ��.
			// NOTE : ĳ���� ���� ���нÿ� ���� MSG_FAIL�� ���� MSG_DB_CHAR_EXIST�� �´�...
			if (STAGEMGR()->GetCurStage() == eSTAGE_CREATECHAR)
			{
				bFail = TRUE;
			}
			_pNetwork->m_bSendMessage = FALSE;
			return;
		}
		else if ((*istr).GetType() == MSG_DB)
		{
			_pSound->Mute();
			StageMgr* pStageMgr = StageMgr::getSingleton();

			static BOOL bSlotInfo = FALSE;
			if (dbtype == MSG_DB_SUCCESS)
			{
				if (!bSlotInfo)
				{
					_pGameState->ClearCharacterSlot();
					bSlotInfo = TRUE;
				}
				bFail = FALSE;
			}
			else if (dbtype == MSG_DB_CHAR_EXIST)
			{
				if (!bSlotInfo)
				{
					_pGameState->ClearCharacterSlot();
					bSlotInfo = TRUE;
				}

				_pGameState->ReceiveCharSlot((*istr));		// ĳ���� ���� ��
			}
			// check creatable night shadow. [11/13/2009 rumist]
			else if (dbtype == MSG_DB_NSCREATE)
			{
				_pGameState->SetCreatableNightShadow(TRUE);
			}
			else if (dbtype == MSG_DB_CHAR_SLOT_TIME)	// [2012/07/05 : Sora]  ĳ���� ���� Ȯ��
			{
				ULONG charSlotTime;
				(*istr) >> charSlotTime;

				if (GameDataManager* pGameData = GameDataManager::getSingleton())
				{
					if (CCharacterSelect* pCharSel = pGameData->GetCharSelData())
						pCharSel->SetExpansionTime(charSlotTime);

				}
			}
			else if (dbtype == MSG_DB_CHAR_END)
			{
				bSlotInfo = FALSE;

				//wooss 050820
				ULONG slotTime;
				(*istr) >> slotTime;	// ���� ���� �ʴ� ������. 
				(*istr) >> slotTime;    // ..

				_pNetwork->m_bSendMessage = FALSE;


				pUIManager->GetCharacterSelect()->Lock(FALSE);

				if (_pNetwork->bMoveCharacterSelectUI == TRUE)
				{
					pStageMgr->SetNextStage(eSTAGE_GAMEEND);
					return;
				}
				// EDIT : BS : 070413 : �ű� ��Ŷ ��ȣȭ

#ifdef CRYPT_NET_MSG
#ifndef CRYPT_NET_MSG_MANUAL
				ULONG ulSeed;
				(*istr) >> ulSeed;
				CNM_MakeKeyFromSeed(&_pNetwork->cnmKeyServer, (unsigned int)ulSeed);
#endif // #ifndef CRYPT_NET_MSG_MANUAL
#endif // ifdef CRYPT_NET_MSG
				//#define AUTO_LOGIN
				if (pStageMgr->GetCurStage() == eSTAGE_CREATECHAR)
				{
					if (bFail)
					{
						bFail = FALSE;

#ifdef RESTRICT_SOUND
						extern BOOL _bNTKernel;
						//if( _bNTKernel )
						_pSound->UpdateSounds();
#endif	// RESTRICT_SOUND
						return;
					}
				}
				if (pStageMgr->GetCurStage() == eSTAGE_SELCHAR)
				{
					CmdPostUpdateCharacter* pCmd = new CmdPostUpdateCharacter;
					pCmd->setData(pUIManager->GetCharacterSelect());
					pUIManager->GetCharacterSelect()->SetPostCommand(pCmd);
				}
				else
				{
					pStageMgr->EndCharData();
				}
			}
			else if (dbtype == MSG_DB_OK)
			{
				bFail = FALSE;
				_pNetwork->m_bSendMessage = FALSE;
				// Game Start
				ULONG zone;
				(*istr) >> zone;
				g_slZone = zone;//0616 kwon	

				extern ENGINE_API BOOL _bLoginProcess;
				_bLoginProcess = FALSE;
				_SetPlayStartTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();

				pStageMgr->SetNextStage(eSTAGE_ZONELOADING);

				// �α��� �� ����.
				pUIManager->GetCharacterSelect()->DeleteModel();
			}

			// EDIT : BS
			else if (dbtype == MSG_DB_OTHER_SERVER)
			{
				ULONG zone;
				CTString ip;
				ULONG port;

				(*istr) >> zone;
				(*istr) >> ip;
				(*istr) >> port;

				MoveOtherServer(zone, ip, port);
			}
			// --- EDIT : BS

#ifdef RESTRICT_SOUND
			extern BOOL _bNTKernel;
			//if( _bNTKernel )
			_pSound->UpdateSounds();
#endif // RESTRICT_SOUND
		}
		else if ((*istr).GetType() == MSG_MENU)
		{
			if (dbtype == MSG_RETURN_TO_SELECT_CHANNEL)
			{
				UIMGR()->GetCharacterSelect()->ChangeServer();
			}
		}
		else
		{
			CPrintF("Undefined data received!! msgType=%u \n", (*istr).GetType());
#ifdef RESTRICT_SOUND
			extern BOOL _bNTKernel;
			//if( _bNTKernel )
			_pSound->UpdateSounds();
#endif // RESTRICT_SOUND
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: ���� ����� �����ɴϴ�.
// Input  : *istr - 
//-----------------------------------------------------------------------------
void CSessionState::ReceiveServerListMessage(CNetworkMessage* istr)
{
	LONG lRecentGroup;
	LONG lRecentServer;
	LONG lSubServerCount;
	LONG lGroupCount;
	LONG lSeqGroupNumber;
	LONG lGroupNumber;
	UBYTE ubServerType = 0;

	(*istr) >> lRecentGroup;		// �ֱ� ������ ���� ��
	(*istr) >> lRecentServer;		// �ֱ� ������ ���� ��ȣ
	(*istr) >> lGroupCount;			// ���� ����� ����.
	(*istr) >> lSeqGroupNumber;		// ���� ����� ����.
	(*istr) >> lGroupNumber;		// ���� ����� ����.
	(*istr) >> lSubServerCount;		// ���� ����� ����.

	// --- wooss-060426---��õ�����̺�Ʈ-------------------->>
	(*istr) >> ubServerType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	// -----------------------------------------------------<<
	// �ɳ��� �̺�Ʈ ���� ����Ʈ �ʱ�ȭ
	pUIManager->GetFlowerTree()->ClearList();

	GameDataManager* pGameDataManager = GameDataManager::getSingleton();
	CServerSelect* pServerData = NULL;

	if (pGameDataManager != NULL)
	{
		pServerData = pGameDataManager->GetServerData();
	}

	for (int i = 0; i < lSubServerCount; ++i)
	{
		LONG		lSubNum;		// Sub ��ȣ
		LONG		lPlayerNum;		// �÷��̾� ��
		CTString	strAddress;		// IP Address
		LONG		lPortNum;

		(*istr) >> lSubNum;		// Sub ��ȣ 
		(*istr) >> lPlayerNum;	// �÷��̾� ��
		(*istr) >> strAddress;	// IP Address
		//	strAddress = "lastchaos.lndrs.nl"; // lastchaos.lndrs.nl
		(*istr) >> lPortNum;		// Port Num

		lPlayerNum -= ADDSERVERVALUE;

		if (pServerData != NULL)
		{
			pServerData->AddServerList(lGroupNumber, lSubNum, lPlayerNum, strAddress, lPortNum, ubServerType);
			pServerData->SetRecentServer(lRecentGroup, lRecentServer);
		}
	}

	SetRecentServer(lRecentGroup, lRecentServer);

	if (lSeqGroupNumber == lGroupCount)
	{
		STAGEMGR()->SetNextStage(eSTAGE_SELSERVER);
		_pNetwork->m_bSendMessage = FALSE;
		_cmiComm.Disconnect();
	}
}

//������ ���� ��	//(5th Closed beta)(0.2)
//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *istr - 
//-----------------------------------------------------------------------------
void CSessionState::ReceiveNpcRegenMessage(CNetworkMessage* istr)
{
	INDEX iIndex;
	SBYTE sbYLayer;//1013
	INDEX iMobType;
	INDEX iEntityID;
	CPlacement3D plPlacement = CPlacement3D(FLOAT3D(0.0f, 0.0f, 0.0f), ANGLE3D(0.0f, 0.0f, 0.0f));
	CEntity* penEntity = NULL;

	(*istr) >> iIndex;								// Index
	(*istr) >> iMobType;							// DB Index
	(*istr) >> plPlacement.pl_PositionVector(1);	// Pos X
	(*istr) >> plPlacement.pl_PositionVector(3);	// Pos Z
	(*istr) >> plPlacement.pl_PositionVector(2);	// Pos H
	(*istr) >> plPlacement.pl_OrientationAngle(1);	// Angle
	(*istr) >> sbYLayer;							// Y Layer
	(*istr) >> iEntityID;							// Entity ID

	//������ ���� ����	//(5th Closed beta)(0.2)
	CMobData* MD = CMobData::getData(iMobType);
	if (MD->GetMobIndex() == -1)
	{
		OutputDebugString("Cannot find Mob Data!!!\n");
		ASSERTALWAYS("Cannot find Mob Data!!!\n");
		return;
	}

	CMobTarget* pMT = new CMobTarget;

	penEntity = _pNetwork->ga_World.EntityFromID(iEntityID);
	penEntity->SetNetworkID(iIndex);

	BOOL bNpc = FALSE;
	if (penEntity->IsFirstExtraFlagOn(ENF_EX1_NPC))
	{
		bNpc = TRUE;
	}

	const char* szMobName = CMobData::getData(iMobType)->GetName();
	CTString strMobName = szMobName;
	pMT->SetData(iIndex, iMobType, strMobName, MD->GetLevel(), penEntity, bNpc, sbYLayer);//0826
	pMT->SetSyndicateData(MD->GetSyndicateType(), MD->GetSyndicateGrade());

	if (penEntity != NULL)
	{
		// FIXME : ���ʹ� Spawner�� �ߺ��Ǵ� �κ�.
		penEntity->SetSkaModel(MD->GetMobSmcFileName());
		CMobData::SetMobDataToNPC(penEntity, MD, szMobName);
		// �̱۸���϶� ������ ��ƼƼ�� ������ ������.
		if (_pNetwork->m_bSingleMode &&
			!penEntity->IsFirstExtraFlagOn(ENF_EX1_NPC))
		{
			_pNetwork->wo_dwEnemyCount++;
			if (_pNetwork->m_ubGMLevel > 1)
			{
				CTString strMessage;
				strMessage.PrintF("=====spawned enemy : %d=====\n", _pNetwork->wo_dwEnemyCount);
				_pNetwork->ClientSystemMessage(strMessage);
			}
		}

		// �����ɶ� �ִϸ��̼��� �ʿ��� ���ʹ̵�...
		const int iWanderingZombie = 35;		// ��Ȳ�ϴ� ����
		const int iZombie = 51;		// ����
		const int iDamd = 142;		// ����(���縵 �³�???)

		// FIXME : �ӽ÷� �ϵ� �ڵ��� �κ�.
		// FIXME : ���� ���� ����.
		if (iMobType == iWanderingZombie || iMobType == iZombie || iMobType == iDamd)		// ���� & ����
		{
			CEntityProperty& epPropertyStart = *(penEntity->PropertyForTypeAndID(CEntityProperty::EPT_INDEX, 99));	// Walk Animation
			ENTITYPROPERTY(&*penEntity, epPropertyStart.ep_slOffset, INDEX) = ska_GetIDFromStringTable("m_zm_up01");
		}
		pMT->m_nIdxClient = penEntity->en_ulID;
		penEntity->Initialize();
		penEntity->en_pMobTarget = pMT;

		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetMobData(penEntity, MD->GetHealth(), MD->GetHealth(), MD->GetLevel(), FALSE, -1);
		penEntity->FallDownToFloor();
		CPrintF("---Mob Created! S Index : %d, C Index : %d\n", iIndex, pMT->m_nIdxClient);
	}

	ACTORMGR()->AddObject(pMT);

	// NOTE : 11�� ������ ��쿡��...
	if (g_slZone == 11)
	{
		// NOTE : �������ġ �ϰ�쿡�� �������̽��� ����� ����.
		if (iMobType != 220)
			UIMGR()->GetSingleBattle()->openUI();
	}
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *istr - 
//-----------------------------------------------------------------------------

void CSessionState::ReceiveMoveMessage(CNetworkMessage* istr)
{
	CEntity* penPlEntity;
	CPlayerEntity* penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
	penPlayerEntity = (CPlayerEntity*)penPlEntity;

	ResponseClient::moveMsg* pPack = reinterpret_cast<ResponseClient::moveMsg*>(istr->GetBuffer());

	switch (pPack->charType)
	{
	case MSG_CHAR_PC:
		penPlayerEntity->Read_net_Character(MSG_MOVE, 0, &(*istr));
		break;
	case MSG_CHAR_NPC:
		penPlayerEntity->Read_net_Mob(MSG_MOVE, &(*istr));
		break;
	case MSG_CHAR_PET:
		penPlayerEntity->Read_net_Pet(MSG_MOVE, &(*istr));
		break;
	case MSG_CHAR_ELEMENTAL:
		penPlayerEntity->Read_net_Summon(MSG_MOVE, &(*istr));
		break;
	case MSG_CHAR_WILDPET:
		penPlayerEntity->Read_net_WildPet(MSG_MOVE, &(*istr));
		break;
	}
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *istr - 
//-----------------------------------------------------------------------------
// �������� �̵��� ������ ���� �� GO_ZONE
// �̵��� ������ ���� �� GO_TO
// FiXME : �Ʒ� �Լ� ���� �ʿ���.
// FIXME : Restart_Internal()�κа� �ߺ��Ǵ� �κ��� �ʹ� ����.  �ʱ�ȭ�ϴ� �κи� ���� ������.
void CSessionState::ReceiveGoToMessage(CNetworkMessage* istr)
{
	CEntity* penPlEntity;
	CPlayerEntity* penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
	penPlayerEntity = (CPlayerEntity*)penPlEntity;

	//0917
	INFO()->TargetClear();

	CUIManager* pUIManager = CUIManager::getSingleton();
	ResponseClient::goMsg* pPack = reinterpret_cast<ResponseClient::goMsg*>(istr->GetBuffer());

	if (pPack->zoneIndex == g_slZone)	//���� world�� �̵�
	{
		ACTORMGR()->RemoveAll();
		penPlayerEntity->Read_net_Character(MSG_GOTO, 0, &(*istr));

		UIMGR()->SetCSFlagOff(CSF_TELEPORT);
	}
	else	//�ٸ� world(zone)�� �̵�, �����ʿ���� Ŭ���̾�Ʈ ���� ó��.
	{
		_pNetwork->SetDelivery(false);
		g_slZone = pPack->zoneIndex;//0921
		STAGEMGR()->SetNextStage(eSTAGE_ZONELOADING);
	}
}

// [KH_070316] ���� �����̾� �޸� ����
void CSessionState::ReceiveMemPosMessage(CNetworkMessage* istr)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(istr->GetBuffer());
	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (pBase->subType)
	{
	case MSG_MEMPOS_LIST:
	{
		if (g_iCountry != RUSSIA)
			proc_mempos_list(istr);
		else
			proc_mempos_list_rus(istr);
	}
	break;
	case MSG_MEMPOS_WRITE:
	{
		if (g_iCountry != RUSSIA)
		{
			ResponseClient::memposWrite* pPack = reinterpret_cast<ResponseClient::memposWrite*>(istr->GetBuffer());

			if (pBase->type == MSG_MEMPOS)
			{
				pUIManager->GetTeleport()->SetTeleportInfo(pPack->data.index, pPack->data.zone, pPack->data.x, pPack->data.z, CTString(pPack->data.comment));
				pUIManager->GetTeleport()->UpdateListItem(pPack->data.index);
				pUIManager->GetTeleport()->ListItemDown();
			}
		}
		else
		{
			ResponseClient::memposWriteRus* pPack = reinterpret_cast<ResponseClient::memposWriteRus*>(istr->GetBuffer());

			if (pBase->type == MSG_MEMPOS)
			{
				pUIManager->GetTeleport()->SetTeleportInfo(pPack->data.index, pPack->data.zone, pPack->data.x, pPack->data.z, CTString(pPack->data.comment));
				pUIManager->GetTeleport()->UpdateListItem(pPack->data.index);
				pUIManager->GetTeleport()->ListItemDown();
			}
		}
	}
	break;
	}
}

void CSessionState::proc_mempos_list(CNetworkMessage* istr)
{
	CUIManager* pUIManager = UIMGR();

	ResponseClient::memposList* pPack = reinterpret_cast<ResponseClient::memposList*>(istr->GetBuffer());

	if (pPack->type == MSG_MEMPOS)
		pUIManager->GetTeleport()->ClearTeleportList();

	pUIManager->GetTeleport()->SetUseTime(pPack->memposTime);

	if (pPack->listCount <= 0)
		return;

	ResponseClient::memposElement* pData = new ResponseClient::memposElement[pPack->listCount];
	memcpy(pData, &pPack->list[0], sizeof(ResponseClient::memposElement) * pPack->listCount);

	for (int i = 0; i < pPack->listCount; ++i)
	{
		if (pPack->type == MSG_MEMPOS && pData[i].index != 255)
			pUIManager->GetTeleport()->SetTeleportInfo(pData[i].index, pData[i].zone, pData[i].x, pData[i].z, CTString(pData[i].comment));
	}

	SAFE_ARRAY_DELETE(pData);
}

void CSessionState::proc_mempos_list_rus(CNetworkMessage* istr)
{
	CUIManager* pUIManager = UIMGR();

	ResponseClient::memposListRus* pPack = reinterpret_cast<ResponseClient::memposListRus*>(istr->GetBuffer());

	if (pPack->type == MSG_MEMPOS)
		pUIManager->GetTeleport()->ClearTeleportList();

	pUIManager->GetTeleport()->SetUseTime(pPack->memposTime);

	if (pPack->listCount <= 0)
		return;

	ResponseClient::memposElementRus* pData = new ResponseClient::memposElementRus[pPack->listCount];
	memcpy(pData, &pPack->list[0], sizeof(ResponseClient::memposElementRus) * pPack->listCount);

	for (int i = 0; i < pPack->listCount; ++i)
	{
		if (pPack->type == MSG_MEMPOS && pData[i].index != 255)
			pUIManager->GetTeleport()->SetTeleportInfo(pData[i].index, pData[i].zone, pData[i].x, pData[i].z, CTString(pData[i].comment));
	}

	SAFE_ARRAY_DELETE(pData);
}


void CSessionState::ReceiveGmMessage(CNetworkMessage* istr)
{
	UBYTE ubGmSubType;
	(*istr) >> ubGmSubType;
	if (ubGmSubType == MSG_GM_WHOAMI)
	{
		(*istr) >> _pNetwork->m_ubGMLevel;
		CPrintF("I'm a GM, level %d.", _pNetwork->m_ubGMLevel);
	}
}
void CSessionState::ReceiveInventoryMessage(CNetworkMessage* istr)
{
	/*
		SBYTE	bArrange;	//���Ľ� 1
		SBYTE	tabId;
		SBYTE	rowId;
		ULONG	uniIndex;
		ULONG	index;
		SBYTE	Wearing;
		ULONG	plus,plus2=0;
		ULONG	flag;
		ULONG	used;
		ULONG	used2;
		SQUAD	count;
		SBYTE	sbOptionCount;
		SBYTE	sbOptionType;
		LONG	lOptionLevel;
		LONG	lComUniIndex;

		CPrintF("Recieve Inven Msg.\n");
		CEntity			*penPlEntity;
		CPlayerEntity	*penPlayerEntity;
		penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
		penPlayerEntity = static_cast<CPlayerEntity *>(penPlEntity);

		(*istr) >> bArrange;
		(*istr) >> tabId;
		(*istr) >> rowId;

		CUIManager* pUIManager = CUIManager::getSingleton();

		//CPrintF(TRANS("MSG_INVENTORY : (TAB)%d (ROW)%d \n"), tabId,rowId);
		for( int i = 0;i < 5; i++ )
		{
			(*istr) >> uniIndex;

			if( uniIndex == -1 )
			{
				_pNetwork->MySlotItem[tabId][rowId][i].Init();
				continue;
			}

			(*istr) >> index;
			(*istr) >> Wearing;
			(*istr) >> plus;
			(*istr) >> flag;
			(*istr) >> lComUniIndex;
			(*istr) >> used;

			(*istr) >> used2;

			(*istr) >> count;
			(*istr) >> sbOptionCount;

			//CPrintF(TRANS("MSG_INVENTORY(%d): (uniIndex)%d (index)%d (wear)%d (plus)%d (flag)%d (count)%ld \n"), i+1,uniIndex,index,Wearing,plus,flag,count);
			// eons 2006.11.1
			CItemData* pItemData	= &_pNetwork->GetItemData(index);

			_pNetwork->MySlotItem[tabId][rowId][i].Item_Wearing = Wearing;
			_pNetwork->MySlotItem[tabId][rowId][i].ItemData		= pItemData;
			_pNetwork->MySlotItem[tabId][rowId][i].SetData( index, uniIndex, tabId, rowId, i,
				plus, flag, lComUniIndex, used, used2, Wearing, count );

			// ���� ������ ���....
			if( pItemData->GetType() == CItemData::ITEM_ACCESSORY &&
				pItemData->GetSubType() == CItemData::ACCESSORY_PET &&
				Wearing != -1)
			{
				const INDEX iPetIndex = _pNetwork->MySlotItem[tabId][rowId][i].Item_Plus;
				CNetworkLibrary::sPetInfo	TempPet;
				TempPet.lIndex				= iPetIndex;
				INFO()->_PetTargetInfo.lIndex		= iPetIndex;
				std::vector<CNetworkLibrary::sPetInfo>::iterator iter =
					std::find_if(_pNetwork->m_vectorPetList.begin(), _pNetwork->m_vectorPetList.end(), CNetworkLibrary::FindPet(TempPet) );
				if( iter != _pNetwork->m_vectorPetList.end() )
				{
					INFO()->_PetTargetInfo.iLevel		= (*iter).lLevel;
					INFO()->_PetTargetInfo.fHealth		= (*iter).lHP;
					INFO()->_PetTargetInfo.fMaxHealth	= (*iter).lMaxHP;
					INFO()->_PetTargetInfo.fMaxHungry	= (*iter).lMaxHungry;
					INFO()->_PetTargetInfo.fHungry		= (*iter).lHungry;
					INFO()->_PetTargetInfo.lAbility		= (*iter).lAbility;
					INFO()->_PetTargetInfo.bIsActive		= TRUE;
					INFO()->_PetTargetInfo.strNameCard	= (*iter).strNameCard;

					INDEX iPetType;
					INDEX iPetAge;
					_pNetwork->CheckPetType( (*iter).sbPetTypeGrade, iPetType, iPetAge );

					INFO()->_PetTargetInfo.iType			= iPetType;
					INFO()->_PetTargetInfo.iAge			= iPetAge;
				}
			}

			_pNetwork->MySlotItem[tabId][rowId][i].InitOptionData();

			//���� �������϶�...
			if( pItemData->GetFlag() & ITEM_FLAG_RARE )
			{
				//�ɼ� ������ 0�̸� �̰��� ���������
				if( sbOptionCount ==0)
					_pNetwork->MySlotItem[tabId][rowId][i].SetRareIndex(0);
				//������ ����������̸�...
				else
				{
					pUIManager->SetRareOption(istr, _pNetwork->MySlotItem[tabId][rowId][i]);
				}
			}
			//���� �������� �ƴϸ�.....
			else
			{
				LONG lOriginOptionVar = ORIGIN_VAR_DEFAULT;
				for( SBYTE sbOption = 0; sbOption < sbOptionCount; sbOption++ )
				{
					(*istr) >> sbOptionType;
					(*istr) >> lOptionLevel;
	#ifdef REFORM_SYSTEM
					if ( pItemData->GetFlag() & ITEM_FLAG_ORIGIN )
					{
						(*istr) >> lOriginOptionVar;
					}
	#endif

					_pNetwork->MySlotItem[tabId][rowId][i].SetOptionData( sbOption, sbOptionType, lOptionLevel, lOriginOptionVar );
				}
			}

			if ( pItemData->GetFlag() & ITEM_FLAG_ORIGIN)
			{
				SBYTE sbBelong, sbSkillcont;
				LONG lSkillIndex;
				SBYTE sbSkillLevel;

				(*istr) >> sbBelong;
				(*istr) >> sbSkillcont;

				_pNetwork->MySlotItem[tabId][rowId][i].SetItemBelong(sbBelong);

				for (SBYTE sbSkillpos = 0; sbSkillpos < sbSkillcont; sbSkillpos++)
				{
					(*istr) >> lSkillIndex;
					(*istr) >> sbSkillLevel;

					_pNetwork->MySlotItem[tabId][rowId][i].SetItemSkill(sbSkillpos, lSkillIndex, sbSkillLevel);
				}

			}

			(*istr) >> plus2;
			_pNetwork->MySlotItem[tabId][rowId][i].SetItemPlus2(plus2);

	#if defined SOCKET_SYSTEM
			_pNetwork->MySlotItem[tabId][rowId][i].InitSocketInfo();
			// receive data about socket type. [6/23/2010 rumist]
			if( pItemData->GetFlag() & ITEM_FLAG_SOCKET )
			{
				SBYTE	sbSocketCreateCount = 0;
				SBYTE	sbSocketCount = 0;
				LONG	lSocketJewelIndex = 0;

	#ifdef SOCKET_SYSTEM_S2 // �κ��丮 �޽��� ���� �κ� [4/3/2013 Ranma]
				LONG	lSocketInfo[JEWEL_MAX_COUNT] = {-1,};
				int	j;

				for (j = 0; j < JEWEL_MAX_COUNT; j++)
				{
					(*istr) >> lSocketInfo[j];
					if (lSocketInfo[j] >= 0)
						sbSocketCreateCount++;
				}

				_pNetwork->MySlotItem[tabId][rowId][i].SetSocketCount( sbSocketCreateCount );

				for ( j = 0; j < JEWEL_MAX_COUNT; j++)
				{
					if (lSocketInfo[j] >= 0)
						_pNetwork->MySlotItem[tabId][rowId][i].SetSocketOption( j, lSocketInfo[j] );
				}
	#else

				(*istr) >> sbSocketCreateCount;
				_pNetwork->MySlotItem[tabId][rowId][i].SetSocketCount( sbSocketCreateCount );

				(*istr) >> sbSocketCount;
				for( SBYTE si = 0; si < sbSocketCreateCount; ++si )
				{
					(*istr) >> lSocketJewelIndex;
					_pNetwork->MySlotItem[tabId][rowId][i].SetSocketOption( si, lSocketJewelIndex );
				}
	#endif
			}
	#endif

			pUIManager->GetInventory()->InitInventory( tabId, rowId, i, uniIndex, index, Wearing );

			if( CLacarette::IsCoinItem( index) )
			{
				pUIManager->GetLacarette()->SetCoinCount( index, count );
			}

			// BUGFIX : ITS(#1265) ���ϵ��� ����Ʈ �� ���̵��� ���� ����Ʈ ǥ�� ���� [6/15/2011 rumist]
			// ����Ʈ�� �������� ��(ž�½ÿ��� ���ϵ尡 ��)�� ���� �� �ֵ��� ���� ���� � ������ �Ǵ��Ͽ�
			// ���� �ν��Ͻ��� Ȯ����.
			CModelInstance *pMI			= NULL;
			// wildpet or pet ž���Ͻ� ���� child��. [6/15/2011 rumist]
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
			else
			{
				pMI	= penPlayerEntity->GetModelInstance();
			}

			//INDEX PlayerType = _pNetwork->ga_srvServer.srv_apltPlayers[0].plt_penPlayerEntity->en_pcCharacter.pc_iPlayerType;//Ÿ��ź:0,����Ʈ:1,healer:2 ������:3
			if(Wearing != -1 && _pNetwork->MyCharacterInfo.sbEvocationType == -1)
			{
				int WearPos = pItemData->GetWearingPosition();
				INDEX iCurWearIndex = -1;
				if ( !(pItemData->GetFlag()&ITEM_FLAG_COSTUME2))
				{
					INDEX iCosWearIndex = _pNetwork->MyCharacterInfo.CostumeWearing[WearPos].idbIndex;
					if (WearPos == WEAR_BACKWING)
					{
						iCosWearIndex = _pNetwork->MyCharacterInfo.CostumeWearing[WEAR_COSTUME_BACKWING].idbIndex;
					}
					if (iCosWearIndex < 0)
					{
						if (!(pItemData->GetWearingPosition() == WEAR_HELMET && (CTString)pItemData->GetItemSmcFileName() == MODEL_TREASURE))
						{
							penPlayerEntity->DeleteCurrentArmor(Wearing);//1005 ������ ������ ���׼���
							penPlayerEntity->DeleteDefaultArmor(Wearing);
						}

						if(!(pItemData->GetWearingPosition() == WEAR_HELMET && (CTString)pItemData->GetItemSmcFileName() == MODEL_TREASURE))
						{
							_pGameState->WearingArmor( pMI, *pItemData );
						}
						iCurWearIndex = index;
					}
					else
					{
						iCurWearIndex = iCosWearIndex;
					}
					// Date : 2005-04-07(���� 3:39:57), By Lee Ki-hwan
					_pNetwork->MyCharacterInfo.itemEffect.Change(_pNetwork->MyCharacterInfo.job
						, &_pNetwork->GetItemData(iCurWearIndex)
						, Wearing
						, plus
						, &pMI->m_tmSkaTagManager
						, 1, _pNetwork->GetItemData(iCurWearIndex).GetSubType() );
				}
			}

			_pNetwork->MyCharacterInfo.itemEffect.Refresh(&pMI->m_tmSkaTagManager, 1);
			_pNetwork->MyCharacterInfo.statusEffect.Refresh(&pMI->m_tmSkaTagManager, CStatusEffect::R_NONE);
		}


		if(bArrange & ITEM_ARRANGE_END)
		{
			for(int row=rowId+1;row<TOTAL_ROW;++row)
			{
				for(int col=0;col<TOTAL_COL;++col)
				{
					_pNetwork->MySlotItem[tabId][(row * INVEN_SLOT_COL) + col].Init();
				}
			}
		}
	*/
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *istr - 
//-----------------------------------------------------------------------------
// �������� �̵��� ������ ���� �� GO_ZONE
// �̵��� ������ ���� �� GO_TO
// FIXME : �Ʒ� �Լ� ������ �ʿ���.
void CSessionState::ReceiveGoZoneMessage(CNetworkMessage* istr)
{
	ResponseClient::moveGoZone* pRecv = reinterpret_cast<ResponseClient::moveGoZone*>(istr->GetBuffer());

	CTString	ip = pRecv->ip;

	MoveOtherServer(pRecv->zone, ip, pRecv->port);

	CPrintF(TRANS("MSG_GO_ZONE zone:%d extra:%d ip:%s port:%d \n"), pRecv->zone, pRecv->extra, ip, pRecv->port);
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *istr - 
//-----------------------------------------------------------------------------
void CSessionState::ReceiveItemMessage(CNetworkMessage* istr)
{
	OBFUSCATE();

	SBYTE	type;
	SBYTE	wear_type;						// �Դ� ��ġ 
	ULONG	item_uniindex;
	ULONG	item_index;
	ULONG	plus, flag;
	LONG	used, used2;
	SQUAD	count;
	FLOAT	x, h, z, r;
	SBYTE	ylayer;
	SBYTE	cha_type;
	ULONG	cha_index;
	SBYTE	tab, row, col;
	SQUAD	delta;
	int itemGrade = 0;		// item rarity grade for loot filter

	//wooss 050818i
	int commandCode = -1;

	//wooss 050818
	CTString strTitle;
	CTString strMessage1, strMessage2;
	CUIMsgBox_Info	MsgBoxInfo;

	CEntity* penPlEntity;
	CPlayerEntity* penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity(0);		// ĳ���� �ڱ� �ڽ�
	penPlayerEntity = static_cast<CPlayerEntity*>(penPlEntity);

	(*istr) >> type;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (type)
	{
	case MSG_ITEM_DISAPPEAR: //0607 kwon
	{
		(*istr) >> item_uniindex;

		ACTORMGR()->RemoveObject(eOBJ_ITEM, item_uniindex);
	}
	break;

	case MSG_ITEM_APPEAR: //0607 kwon
	{
		(*istr) >> item_uniindex;
		(*istr) >> item_index;
		(*istr) >> count;
		(*istr) >> x;
		(*istr) >> z;
		(*istr) >> h;
		(*istr) >> r;
		(*istr) >> ylayer;
		(*istr) >> itemGrade;

		CItemData* pItemData = _pNetwork->GetItemData(item_index);
		const char* szItemName = _pNetwork->GetItemName(item_index);

		CItemTarget* pTarget = new CItemTarget;

		CEntity* penEntity;
		CPlacement3D plPlacement;
		plPlacement.pl_PositionVector(1) = x;
		plPlacement.pl_PositionVector(2) = h + 1.0f;
		plPlacement.pl_PositionVector(3) = z;
		plPlacement.pl_OrientationAngle = ANGLE3D(0.0f, 0.0f, 0.0f);

		penEntity = _pNetwork->ga_World.CreateEntity_t(plPlacement, CLASS_ITEM, -1, TRUE);
		pTarget->SetData(item_uniindex, szItemName, penEntity, ylayer, count, FLOAT3D(x, h, z), item_index);	//0�� dummy
		pTarget->m_nType = item_index;
		pTarget->m_itemGrade = itemGrade;

		if (penEntity != NULL)
		{
			pTarget->m_nIdxClient = penEntity->en_ulID;
			penEntity->en_strItemName = szItemName;
			SetDropItemModel(penEntity, pItemData, pTarget);
			penEntity->SetNetworkID(item_uniindex);
		}

		ACTORMGR()->AddObject(pTarget);
	}
	break;

	case MSG_ITEM_DROP:
	{
		(*istr) >> item_uniindex;
		(*istr) >> item_index;
		(*istr) >> count;
		(*istr) >> x;
		(*istr) >> z;
		(*istr) >> h;
		(*istr) >> r;
		(*istr) >> ylayer;
		(*istr) >> cha_type;
		(*istr) >> cha_index;
		(*istr) >> itemGrade;

		//������ ���� ����	//(5th Closed beta)(0.2)
		CItemData* pItemData = _pNetwork->GetItemData(item_index);
		const char* szItemName = _pNetwork->GetItemName(item_index);

		CItemTarget* pTarget = new CItemTarget;

		pTarget->SetData(item_uniindex, szItemName, NULL, ylayer, count, FLOAT3D(x, h, z), item_index);//0826
		pTarget->m_nType = item_index;
		pTarget->m_itemGrade = itemGrade;

		if (cha_type == MSG_CHAR_NPC)
		{
			BYTE bLive = 0;

			(*istr) >> bLive; // NPC�� ��� �ִ°�? 1(LIVE), 0(DEATH)

			// edit by cpp2angel (044.12.20) : �ڵ� ����
			if (cha_index == _UIAutoHelp->GetKillMonIndex())
			{
				_UIAutoHelp->SetInfo(AU_ITEM_DROP);
			}
			// ... End Edit 

			bool bFind = false;

			if (bLive < ISNPCLIVE)
			{
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_ITEM, cha_index);
				if (pObject != NULL)
				{
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->AddDeathItem(
						pObject->GetEntity(), FLOAT3D(x, h + 1, z), pTarget, pItemData);
					pObject->m_nType = item_index;

					bFind = true;
				}
			}

			// FIXME : ������ ǥ���ϴ� �κ� �߿��� �ߺ��Ǵ� �κ��� �ʹ� ����.
			if (bFind == false || bLive == ISNPCLIVE)
			{
				char* szEffectName = NULL;
				CEntity* penEntity;
				CPlacement3D plPlacement;

				plPlacement.pl_PositionVector(1) = x;
				plPlacement.pl_PositionVector(2) = h + 1.0f;
				plPlacement.pl_PositionVector(3) = z;
				plPlacement.pl_OrientationAngle = ANGLE3D(0.0f, 0.0f, 0.0f);

				penEntity = _pNetwork->ga_World.CreateEntity_t(plPlacement, CLASS_ITEM, -1, TRUE);
				penEntity->SetNetworkID(item_uniindex);

				if (penEntity != NULL)
				{
					pTarget->m_nIdxClient = penEntity->en_ulID;
					pTarget->m_pEntity = penEntity;
					penEntity->en_strItemName = szItemName;
					SetDropItemModel(penEntity, pItemData, pTarget);
				}

				ACTORMGR()->AddObject(pTarget);
			}
		}
		else	//MSG_CHA_PC
		{
			if (cha_index == _pNetwork->MyCharacterInfo.index)
			{

				CTString	strSysMessage;
				CTString	strCount = pUIManager->IntegerToCommaString(count);

				if (pItemData->GetType() == CItemData::ITEM_ETC &&
					pItemData->GetSubType() == CItemData::ITEM_ETC_MONEY)	// 0829 ��ӻ���
				{
					penPlayerEntity->PlayItemSound(FALSE, TRUE);
					strSysMessage.PrintF(_S(301, "%s ������ ���Ƚ��ϴ�."), strCount);	// ���� ����
					_pNetwork->ClientSystemMessage(strSysMessage);
				}
				else
				{
					penPlayerEntity->PlayItemSound(FALSE, FALSE);
					strSysMessage.PrintF(_S(302, "%s %s���� ���Ƚ��ϴ�."), szItemName, strCount);
					_pNetwork->ClientSystemMessage(strSysMessage);
				}
			}

			CEntity* penEntity;
			CPlacement3D plPlacement;
			plPlacement.pl_PositionVector(1) = x;
			plPlacement.pl_PositionVector(2) = h + 1.0f;
			plPlacement.pl_PositionVector(3) = z;
			plPlacement.pl_OrientationAngle = ANGLE3D(0.0f, 0.0f, 0.0f);
			penEntity = _pNetwork->ga_World.CreateEntity_t(plPlacement, CLASS_ITEM, -1, TRUE);
			penEntity->SetNetworkID(item_uniindex);

			if (penEntity != NULL)
			{
				pTarget->m_nIdxClient = penEntity->en_ulID;
				pTarget->m_pEntity = penEntity;
				penEntity->en_strItemName = szItemName;

				SetDropItemModel(penEntity, pItemData, pTarget);
			}

			ACTORMGR()->AddObject(pTarget);
		}

		// [091216: selo] ��ų ���� UI ����
		if (pUIManager->DoesUIExist(UI_SSKILLLEARN))
		{
			pUIManager->GetSSkillLearn()->updateList();
		}
	}
	break;

	case MSG_ITEM_UPDATE:
	{
		LONG	lComUniIndex;
		SBYTE	sbOptionCount;
		SBYTE	sbOptionType;
		LONG	lOptionLevel;

		(*istr) >> tab;
		(*istr) >> row;
		(*istr) >> col;
		(*istr) >> item_uniindex;
		(*istr) >> plus;
		(*istr) >> flag;
		(*istr) >> lComUniIndex; // �ռ��� ������ �ε���(when upgrade item)
		(*istr) >> used;
		(*istr) >> used2;
		(*istr) >> count;
		(*istr) >> delta;
		(*istr) >> sbOptionCount;

		CItems* pItems = &_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col];
		pItems->Item_Plus = plus;
		pItems->Item_Flag = flag;
		pItems->ComItem_index = lComUniIndex;
		pItems->Item_Used = used;
		pItems->Item_Used2 = used2;
		pItems->Item_Sum = count;

		_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].InitOptionData();

		if (pItems->ItemData->GetFlag() & ITEM_FLAG_RARE)
		{
			//�ɼ� ������ 0�̸� �̰��� ���������
			if (sbOptionCount == 0)
				_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetRareIndex(0);
			//������ ����������̸�...
			else
				pUIManager->SetRareOption(istr, _pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col]);
		}
		else
		{
			LONG lOriginOptionVar = ORIGIN_VAR_DEFAULT;

			for (SBYTE sbOption = 0; sbOption < sbOptionCount; sbOption++)
			{
				(*istr) >> sbOptionType;
				(*istr) >> lOptionLevel;

				if (pItems->ItemData->GetFlag() & ITEM_FLAG_ORIGIN)
				{
					(*istr) >> lOriginOptionVar;
				}
				_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetOptionData(sbOption, sbOptionType, lOptionLevel, lOriginOptionVar);
			}
		}

		if (pItems->ItemData->GetFlag() & ITEM_FLAG_ORIGIN)
		{
			SBYTE sbBelong, sbSkillcont;
			LONG lSkillIndex;
			SBYTE sbSkillLevel;

			(*istr) >> sbBelong;
			(*istr) >> sbSkillcont;

			_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetItemBelong(sbBelong);

			for (SBYTE sbSkillpos = 0; sbSkillpos < sbSkillcont; sbSkillpos++)
			{
				(*istr) >> lSkillIndex;
				(*istr) >> sbSkillLevel;

				_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetItemSkill(sbSkillpos, lSkillIndex, sbSkillLevel);
			}

		}

		LONG lplus2;
		(*istr) >> lplus2;
		_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetItemPlus2(lplus2);
		_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].InitSocketInfo();
		// data receive about socket type. [6/23/2010 rumist]
		if (pItems->ItemData->GetFlag() & ITEM_FLAG_SOCKET)
		{
			SBYTE	sbSocketCreateCount = 0;
			SBYTE	sbSocketCount = 0;
			LONG	lSocketJewelIndex = 0;
			LONG	lSocketInfo[JEWEL_MAX_COUNT] = { -1, };
			int	i;

			for (i = 0; i < JEWEL_MAX_COUNT; i++)
			{
				(*istr) >> lSocketInfo[i];
				if (lSocketInfo[i] >= 0)
					sbSocketCreateCount++;
			}

			_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetSocketCount(sbSocketCreateCount);

			for (i = 0; i < JEWEL_MAX_COUNT; i++)
			{
				if (lSocketInfo[i] >= 0)
					_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetSocketOption(i, lSocketInfo[i]);
			}
		}

		pUIManager->GetInventory()->InitInventory(tab, (row * INVEN_SLOT_COL) + col, item_uniindex, pItems->Item_Index,
			pItems->Item_Wearing);

		if (delta > 0)
		{
			CTString	strSysMessage;
			CItemData* pItemData = pItems->ItemData;
			const char* szItemName = _pNetwork->GetItemName(pItems->Item_Index);

			CTString strCount;
			strCount.PrintF("%I64d", delta);
			pUIManager->InsertCommaToString(strCount);

			strSysMessage.PrintF(_S(417, "%s %s���� ������ϴ�."), szItemName, strCount);
			_pNetwork->ClientSystemMessage(strSysMessage);

		}

		// edit by cpp2angel (044.12.20) : 
		if (pUIManager->GetProcess()->IsVisible())
		{
			pUIManager->GetProcess()->SelectItem();
		}

		if (pUIManager->GetProduct()->IsVisible())
		{
			pUIManager->GetProduct()->SelectItem();
		}

		// Date : 2005-04-07(���� 3:40:01), By Lee Ki-hwan
		INDEX iCurWearIndex = pItems->Item_Index;
		if (_pNetwork->MyWearCostItem[pItems->Item_Wearing].Item_Index > 0)
		{
			iCurWearIndex = _pNetwork->MyWearCostItem[pItems->Item_Wearing].Item_Index;
		}

		CModelInstance* pMI = NULL;
		if (_pNetwork->MyCharacterInfo.bPetRide || _pNetwork->MyCharacterInfo.bWildPetRide)
		{
			CModelInstance* pMITemp = penPlayerEntity->GetModelInstance();

			INDEX ctmi = pMITemp->mi_cmiChildren.Count();
			if (ctmi > 0)
			{
				pMI = &pMITemp->mi_cmiChildren[0];
			}
			else
			{
				pMI = penPlayerEntity->GetModelInstance();
			}
		}
		else
		{
			pMI = penPlayerEntity->GetModelInstance();
		}
		_pNetwork->MyCharacterInfo.itemEffect.Change(_pNetwork->MyCharacterInfo.job
			, _pNetwork->GetItemData(iCurWearIndex)
			, pItems->Item_Wearing
			, pItems->Item_Plus
			, &pMI->m_tmSkaTagManager
			, 1, _pNetwork->GetItemData(iCurWearIndex)->GetSubType());

		// [sora] 090731 ������ ������ count update
		pUIManager->GetQuickSlot()->UpdateItemCount(item_uniindex, count);

		// [091216: selo] ��ų ���� UI ����
		if (pUIManager->DoesUIExist(UI_SSKILLLEARN))
		{
			pUIManager->GetSSkillLearn()->updateList();
		}
	}
	break;

	case MSG_ITEM_ADD:
	{
		LONG	lComUniIndex;
		SBYTE	sbOptionCount;
		SBYTE	sbOptionType;
		LONG	lOptionLevel;

		(*istr) >> tab;
		(*istr) >> row;
		(*istr) >> col;
		(*istr) >> item_uniindex;
		(*istr) >> item_index;
		(*istr) >> wear_type;
		(*istr) >> plus;
		(*istr) >> flag;
		(*istr) >> lComUniIndex; // �ռ��� ������ �ε���(when upgrade item)
		(*istr) >> used;
		(*istr) >> used2;
		(*istr) >> count;
		(*istr) >> sbOptionCount;

		Notice* pNotice = GAMEDATAMGR()->GetNotice();

		// �巹��ũ�� ���� ����� ���, Notice�� ǥ������.
		if (item_index == 949)
		{
			if (!ItemHelp::HaveItem(item_index) && !ItemHelp::HaveItem(872))
			{
				if (pNotice != NULL)
					pNotice->AddToNoticeList(4001, Notice::NOTICE_EVENT);
			}
		}

		// ���� �Ǹ��� ����� ���, Notice�� ǥ������.
		if (item_index == 948)
		{
			if (!ItemHelp::HaveItem(item_index) && !ItemHelp::HaveItem(871))
			{
				if (pNotice != NULL)
					pNotice->AddToNoticeList(4000, Notice::NOTICE_EVENT);
			}
		}

		// wooss 060810
		// ��ũ �巹��ũ�� ���� ����� ���, Notice�� ǥ������.
		if (item_index == 1706)
		{
			if (!ItemHelp::HaveItem(item_index) && !ItemHelp::HaveItem(1711))
			{
				if (pNotice != NULL)
					pNotice->AddToNoticeList(4003, Notice::NOTICE_EVENT);
			}
		}
		// �Ұ������� �巹��ũ�� ���� ����� ���, Notice�� ǥ������.
		if (item_index == 1709)
		{
			if (!ItemHelp::HaveItem(item_index) && !ItemHelp::HaveItem(1712))
			{
				if (pNotice != NULL)
					pNotice->AddToNoticeList(4005, Notice::NOTICE_EVENT);
			}
		}
		// �Ķ� ���� �Ǹ��� ����� ���, Notice�� ǥ������.
		if (item_index == 1707)
		{
			if (!ItemHelp::HaveItem(item_index) && !ItemHelp::HaveItem(1710))
			{
				if (pNotice != NULL)
					pNotice->AddToNoticeList(4002, Notice::NOTICE_EVENT);
			}
		}
		// �Ұ��������� �Ǹ��� ����� ���, Notice�� ǥ������.
		if (item_index == 1708)
		{
			if (!ItemHelp::HaveItem(item_index) && !ItemHelp::HaveItem(1713))
			{
				if (pNotice != NULL)
					pNotice->AddToNoticeList(4004, Notice::NOTICE_EVENT);
			}
		}

		CItemData* pItemData = _pNetwork->GetItemData(item_index);
		const char* szItemName = _pNetwork->GetItemName(item_index);

		_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].ItemData = pItemData;
		_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetData(item_index, item_uniindex,
			tab, (row * INVEN_SLOT_COL) + col, plus, flag,
			lComUniIndex, used, used2, wear_type, count);

		_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].InitOptionData();

		if (pItemData->GetFlag() & ITEM_FLAG_RARE)
		{
			//�ɼ� ������ 0�̸� �̰��� ���������
			if (sbOptionCount == 0)
				_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetRareIndex(0);
			//������ ����������̸�...
			else
				pUIManager->SetRareOption(istr, _pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col]);
		}
		else
		{
			LONG lOriginOptionVar = ORIGIN_VAR_DEFAULT;

			for (SBYTE sbOption = 0; sbOption < sbOptionCount; sbOption++)
			{
				(*istr) >> sbOptionType;
				(*istr) >> lOptionLevel;

				if (pItemData->GetFlag() & ITEM_FLAG_ORIGIN)
				{
					(*istr) >> lOriginOptionVar;
				}

				_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetOptionData(sbOption, sbOptionType, lOptionLevel, lOriginOptionVar);
			}
		}

		if (pItemData->GetFlag() & ITEM_FLAG_ORIGIN)
		{
			SBYTE sbBelong, sbSkillcont;
			LONG lSkillIndex;
			SBYTE sbSkillLevel;

			(*istr) >> sbBelong;
			(*istr) >> sbSkillcont;

			_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetItemBelong(sbBelong);

			for (SBYTE sbSkillpos = 0; sbSkillpos < sbSkillcont; sbSkillpos++)
			{
				(*istr) >> lSkillIndex;
				(*istr) >> sbSkillLevel;

				_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetItemSkill(sbSkillpos, lSkillIndex, sbSkillLevel);
			}
		}

		LONG lplus2;
		(*istr) >> lplus2;
		_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetItemPlus2(lplus2);

		if (wear_type != -1)
		{
			penPlayerEntity->DeleteDefaultArmor(wear_type);
			//penPlayerEntity->WearingArmor(tab, (row * INVEN_SLOT_COL) + col);
			CModelInstance* pMI = NULL;
			if (_pNetwork->MyCharacterInfo.bPetRide || _pNetwork->MyCharacterInfo.bWildPetRide)
			{
				CModelInstance* pMITemp = penPlayerEntity->GetModelInstance();

				INDEX ctmi = pMITemp->mi_cmiChildren.Count();
				if (ctmi > 0)
				{
					pMI = &pMITemp->mi_cmiChildren[0];
				}
				else
				{
					pMI = penPlayerEntity->GetModelInstance();
				}
			}
			else
			{
				pMI = penPlayerEntity->GetModelInstance();
			}
			_pGameState->WearingArmor(pMI, *pItemData);
		}

		_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].InitSocketInfo();

		if (pItemData->GetFlag() & ITEM_FLAG_SOCKET)
		{
			SBYTE	sbSocketCreateCount = 0;
			SBYTE	sbSocketCount = 0;
			LONG	lSocketJewelIndex = 0;
			LONG	lSocketInfo[JEWEL_MAX_COUNT] = { -1, };
			int	i;

			for (i = 0; i < JEWEL_MAX_COUNT; i++)
			{
				(*istr) >> lSocketInfo[i];
				if (lSocketInfo[i] >= 0)
					sbSocketCreateCount++;
			}

			_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetSocketCount(sbSocketCreateCount);

			for (i = 0; i < JEWEL_MAX_COUNT; i++)
			{
				if (lSocketInfo[i] >= 0)
					_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].SetSocketOption(i, lSocketInfo[i]);
			}
		}

		pUIManager->GetInventory()->InitInventory(tab, (row * INVEN_SLOT_COL) + col, item_uniindex, item_index, wear_type);

		CTString strSysMessage;

		if (count > 0)
		{
			CTString strCount;
			strCount.PrintF("%I64d", count);
			pUIManager->InsertCommaToString(strCount);
			strSysMessage.PrintF(_S(417, "%s %s���� ������ϴ�."), szItemName, strCount);
		}
		else
			strSysMessage.PrintF(_S2(303, szItemName, "%s<��> ������ϴ�."),
				szItemName);

		_pNetwork->ClientSystemMessage(strSysMessage);

		// edit by cpp2angel (044.12.20) : 
		if (pUIManager->GetProcess()->IsVisible())
		{
			pUIManager->GetProcess()->SelectItem();
		}

		if (pUIManager->GetProduct()->IsVisible())
		{
			pUIManager->GetProduct()->SelectItem();
		}

		if (pUIManager->GetChangeWeapon()->GetCashItem()) { //wooss 051011
			CUIMsgBox_Info	MsgBoxInfo;
			if (pItemData->GetType() == CItemData::ITEM_WEAPON)
			{
				MsgBoxInfo.SetMsgBoxInfo(_S(1049, "���� ��ü"), UMBS_OK, UI_NONE, MSGCMD_NULL);
				MsgBoxInfo.AddString(_S(2229, "���Ⱑ ���������� ��ü�Ǿ����ϴ�."));
			}
			else if (pItemData->GetType() == CItemData::ITEM_SHIELD)
			{
				MsgBoxInfo.SetMsgBoxInfo(_S(3536, "�� ��ü"), UMBS_OK, UI_NONE, MSGCMD_NULL);
				MsgBoxInfo.AddString(_S(3537, "���� ���������� ��ü�Ǿ����ϴ�."));
			}
			pUIManager->CreateMessageBox(MsgBoxInfo);
			pUIManager->GetChangeWeapon()->close();
		}

		// [091216: selo] ��ų ���� UI ����
		if (pUIManager->DoesUIExist(UI_SSKILLLEARN))
		{
			pUIManager->GetSSkillLearn()->updateList();
		}
	}
	break;

	case MSG_ITEM_USE:
	{
		updateItemUse(istr);
	}
	break;

	case MSG_ITEM_TAKE:
	{
		penPlayerEntity->Read_net_Character(MSG_ITEM, MSG_ITEM_TAKE, &(*istr));
		/*
		(*istr) >> cha_index;
		(*istr) >> item_uniindex;

		for( ipl = 0; ipl < _pNetwork->ga_srvServer.srv_aitItem.Count(); ipl++ )
		{
		CItemTarget	&it = _pNetwork->ga_srvServer.srv_aitItem[ipl];
		if( it.item_Index == item_uniindex )
		{
		it.Init();
		//������ ���� ����	//(5th Closed beta)(0.2)
		_pNetwork->ga_srvServer.srv_aitItem.SwapAndPop(ipl);
		//������ ���� ��	//(5th Closed beta)(0.2)
		}
		}
		*/
	}
	break;
	case MSG_ITEM_GET:
	{
		penPlayerEntity->Read_net_Character(MSG_ITEM, MSG_ITEM_GET, &(*istr));
	}
	break;

	case MSG_ITEM_DELETE:
	{
		(*istr) >> tab;
		(*istr) >> row;
		(*istr) >> col;

		CItemData* pItemData = _pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].ItemData;

		// ���� ��� ����Ʈ���� �����մϴ�.
		if (pItemData->GetType() == CItemData::ITEM_ACCESSORY &&
			(pItemData->GetSubType() == CItemData::ACCESSORY_PET || pItemData->GetSubType() == CItemData::ACCESSORY_WILDPET))
		{
			const INDEX iPetIndex = _pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].Item_Plus;
			CNetworkLibrary::sPetInfo	TempPet;
			TempPet.lIndex = iPetIndex;
			std::vector<CNetworkLibrary::sPetInfo>::iterator iter =
				std::find_if(_pNetwork->m_vectorPetList.begin(), _pNetwork->m_vectorPetList.end(), CNetworkLibrary::FindPet(TempPet));
			if (iter != _pNetwork->m_vectorPetList.end())
			{
				_pNetwork->m_vectorPetList.erase(iter);
			}
		}

		_pNetwork->MySlotItem[tab][(row * INVEN_SLOT_COL) + col].Init();
		pUIManager->GetInventory()->InitInventory(tab, (row * INVEN_SLOT_COL) + col, -1, -1, -1);

		// [091216: selo] ��ų ���� UI ����
		if (pUIManager->DoesUIExist(UI_SSKILLLEARN))
		{
			pUIManager->GetSSkillLearn()->updateList();
		}
	}
	break;

	case MSG_ITEM_UPGRADE_REP:
	{
		SBYTE	sbResult, sbisRune, sbPlus;
		(*istr) >> sbResult;
		(*istr) >> sbisRune;

		if (sbisRune)
		{
			(*istr) >> sbPlus;
			pUIManager->GetInventory()->UpgradeItem(sbResult, sbPlus);
		}
		else pUIManager->GetInventory()->UpgradeItem(sbResult);
	}
	break;

	case MSG_ITEM_REFINE_REP:
	{
		SBYTE	sbResult;
		(*istr) >> sbResult;
		pUIManager->GetRefine()->RefineRep(sbResult);
	}
	break;
	case MSG_ITEM_TRANSMOGRIFY_REP:
	{
		SBYTE	sbResult;
		(*istr) >> sbResult;
		pUIManager->GetTransmogrifyUI()->TransmogrifyRep(sbResult);
	}
	break;
	case MSG_ITEM_OPEN_BOX_REP:
	{
		SBYTE	sbResult;
		(*istr) >> sbResult;
		pUIManager->GetBoxOpenUI()->BoxOpenRep(sbResult);
	}
	break;
	case MSG_ITEM_SEAL_COMPOSE_REP:
	{
		SBYTE	sbResult;
		LONG	total;
		CTString name;
		(*istr) >> sbResult;
		(*istr) >> total;
		(*istr) >> name;
		pUIManager->GetSealComposeUI()->SealComposeRep(sbResult, total, name);
	}
	break;
	case MSG_ITEM_EXTEND_MENU_REP:
	{
		SBYTE	sbResult;
		(*istr) >> sbResult;
		pUIManager->GetExtendMenuUI()->ExtendMenuRep(sbResult);
	}
	break;
	case MSG_ITEM_PROCESS_REP:
	{
		SBYTE	sbResult;
		(*istr) >> sbResult;

		pUIManager->GetProcess()->ProcessRep(sbResult); // �̱�ȯ ���� ( 12.3 )
	}
	break;

	// �̱�ȯ ���� ( 12.6 ) �߰� 
	case MSG_ITEM_MAKE_REP:
	{
		SBYTE	sbResult;
		(*istr) >> sbResult;

		pUIManager->GetProduct()->ProductRep(sbResult);
	}
	break;
	// �̱�ȯ ���� �� 

	// �̱�ȯ �߰� (12.8)
	case MSG_ITEM_MIX_REP:
	{
		SBYTE	sbResult;
		(*istr) >> sbResult;

		pUIManager->GetMix()->MixRep(sbResult);
	}
	break;
	// �̱�ȯ �߰� ��
	case MSG_ITEM_ARCANE_REP:
	{
		SBYTE	sbResult;
		(*istr) >> sbResult;

		pUIManager->GetCompound()->CompoundRep(sbResult);
	}
	break;



	case MSG_ITEM_OPTION_ADD_REP:
	{
		SBYTE	sbResult;
		(*istr) >> sbResult;
		pUIManager->GetInventory()->OptionAddRep(sbResult);
	}
	break;
	case MSG_ITEM_OPTION_DEL_REP:
	{
		SBYTE	sbResult;
		(*istr) >> sbResult;
		pUIManager->GetInventory()->OptionDelRep(sbResult);
	}
	break;
	case MSG_ITEM_CHANGEWEAPON_REP:
	{
		// ���� ��ȯ ����		: old_itemdbindex(n) new_itemdbindex(n)
		LONG lOldItemIndex;
		LONG lNewItemIndex;
		(*istr) >> lOldItemIndex;
		(*istr) >> lNewItemIndex;

		// ���� ���ڸ� ���.
		if (lOldItemIndex == -1)
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(1328, "������ �����Ͽ� ���⸦ ��ü�� �� �����ϴ�."), SYSMSG_ERROR);
		}
		// �߸��� ��ȯ�� ��û�� ���.
		else if (lNewItemIndex == -1)
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(1329, "���⸦ ��ü�� �� �����ϴ�."), SYSMSG_ERROR);
		}
		pUIManager->GetChangeWeapon()->close();
		pUIManager->GetChangeEquipment()->close();
	}
	break;
	case MSG_ITEM_PROCESS_NPC:
	{
		//processItemDBIndex(n) count(n) errcode(n:s)
		LONG processItemDBIndex;
		LONG count;
		LONG errcode;
		(*istr) >> processItemDBIndex;
		(*istr) >> count;
		(*istr) >> errcode;

		pUIManager->GetProcessNPC()->ProcessNPCRep(processItemDBIndex, count, errcode);
	} break;
	case MSG_ITEM_ADD_BOOSTER:
	{
		LONG flag;
		(*istr) >> flag;
		CTString strTitle;
		CTString strContent;

		int commandCode = -1;
		switch (flag)
		{
		case MSG_ITEM_ADD_BOOSTER_ERROR_OK:		// ����
		{
			strTitle = _S(1825, "���׷��̵� ����");
			strContent = _S(1826, "�ν��� ���׷��̵忡 �����߽��ϴ�.");
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
		} break;
		case MSG_ITEM_ADD_BOOSTER_ERROR_USED:	// ����
		{
			strTitle = _S(1827, "���׷��̵� �Ұ�");
			strContent = _S(1828, "�������� �����մϴ�.");
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
		} break;
		case MSG_ITEM_ADD_BOOSTER_ERROR_ALREADY:	// ī��Ʈ ����
		{
			strTitle = _S(1827, "���׷��̵� �Ұ�");
			strContent = _S(1829, "�̹� �ν��� ���׷��̵尡 �Ǿ� �ִ� �������Դϴ�.");
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
		} break;
		}

		pUIManager->CloseMessageBox(MSGCMD_INVEN_UPGRADE_REP);
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_OK, UI_INVENTORY, commandCode);
		MsgBoxInfo.AddString(strContent);
		pUIManager->CreateMessageBox(MsgBoxInfo);

		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
	} break;
	//wooss 050816
	//item prolong message
	case MSG_ITEM_USE_PROLONG:

		ULONG useTime;
		UBYTE prolong;

		(*istr) >> item_index;
		(*istr) >> useTime;
		(*istr) >> prolong;

		if (item_index == MEMSCROLL_EX_ITEM || item_index == MEMSCROLL_EX_ITEM_7DAYS)
		{
			pUIManager->GetTeleport()->SetUseTime(useTime);

			if (prolong && useTime > 0) {
				//�޸� ��ũ���� �̹� ����ϰ� ������
				//wooss 050816
				strTitle = _S(2088, "��� Ȯ��");
				strMessage1 = _S(2128, "�̹� �޸� ��ũ���� Ȯ��Ǿ� �ִ� ���� �Դϴ�.");
				strMessage2 = _S(2148, "�Ⱓ�� �����Ͻðڽ��ϱ�?");
				MsgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_YESNO, UI_NONE, MSGCMD_PROLONG_MEMSCROLL_EX);
				MsgBoxInfo.AddString(strMessage1);
				MsgBoxInfo.AddString(strMessage2);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
		}
		else if (item_index == WAREHOUSE_EX_ITEM || item_index == WAREHOUSE_EX_ITEM_7DAYS)
		{
			pUIManager->GetWareHouseUI()->SetUseTime(useTime);

			if (prolong && useTime > 0) {
				//Ȯ��â���� �̹� ����ϰ� ������
				//wooss 050816
				strTitle = _S(2088, "��� Ȯ��");
				strMessage1 = _S(2129, "�̹� ���� â���� Ȯ��Ǿ� �ִ� ���� �Դϴ�.");
				strMessage2 = _S(2148, "�Ⱓ�� �����Ͻðڽ��ϱ�?");
				MsgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_YESNO, UI_NONE, MSGCMD_PROLONG_WAREHOUSE_EX);
				MsgBoxInfo.AddString(strMessage1);
				MsgBoxInfo.AddString(strMessage2);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
		}
		break;
	case MSG_ITEM_USE_ERROR:
		updateItemUseError(istr);
		break;
	case MSG_ITEM_LEND_WEAPON:
	{
		ULONG idx;
		ULONG errType;
		(*istr) >> idx;
		(*istr) >> errType;
		LeaseWeaponErrChk(errType);
	}
	break;

	// ���� ������ ���� 
	case MSG_ITEM_MIX_WARITEM:
	{
		LONG nErrorCode;
		(*istr) >> nErrorCode;
		pUIManager->GetGWMix()->MixRep(nErrorCode);
	}
	break;

	case MSG_ITEM_LEVELDOWN:
	{
		LONG nErrorCode;
		(*istr) >> nErrorCode;

		pUIManager->CloseMessageBox(MSGCMD_ITEM_LEVELDOWN_REP);
		CUIMsgBox_Info MsgBoxInfo;

		switch (nErrorCode)
		{
		case MSG_ITEM_LEVELDOWN_ERROR_OK:			// ����
		{
			strTitle = _S(1970, "����");
			strMessage1 = _S(3982, "�������� ���������� ���ҵǾ����ϴ�.");
		}
		break;
		case MSG_ITEM_LEVELDOWN_ERROR_ALREADY: // �̹� ���� �϶�
		{
			strTitle = _S(1971, "����");
			strMessage1 = _S(3983, "�̹� �������� ���Ұ� ����Ǿ� �ֽ��ϴ�.");
		}
		break;
		case MSG_ITEM_LEVELDOWN_ERROR_NOEQUIP: // ��� �ƴ�
		{
			strTitle = _S(1971, "����");
			strMessage1 = _S(3984, "�������� ���Ҹ� ������ �� �ִ� ��� �������� �ƴմϴ�.");
		}
		break;
		case MSG_ITEM_LEVELDOWN_ERROR_SCROLL: // �ֹ��� �ƴ�
		{
			strTitle = _S(1971, "����");
			strMessage1 = _S(3985, "������ �������� ���� �ֹ����� �ƴմϴ�.");
		}
		break;
		}

		MsgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(strMessage1);
		pUIManager->CreateMessageBox(MsgBoxInfo);
		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
	}
	break;

	case MSG_ITEM_CHECK_COMPOSITION:
	{
		SBYTE sbRow, sbCol;

		(*istr) >> sbRow;
		(*istr) >> sbCol;

		pUIManager->GetInventory()->UpgradeCompositedItem((sbRow * INVEN_SLOT_COL) + sbCol);
	}
	break;
	case MSG_ITEM_WEAR_COSTUME_SUIT:

	case MSG_ITEM_WEAR_COSTUME:
	case MSG_ITEM_WEAR_COSTUME_TAKEOFF:
	case MSG_ITEM_WEAR:
	case MSG_ITEM_WEAR_TAKE_OFF:
		ReceiveItemWearError(istr);
		break;
	case MSG_ITEM_WEAR_COSTUME_SUIT_TAKEOFF:
		ReceiveCostSuitTakeOff();
		break;
	case MSG_ITEM_LETSPARTY_USE:
	{
		RecieveUsedPartyItemMessage(istr);
	}
	break;

	case MSG_ITEM_MASTERSTONE_USE:
	{
		RecieveMasterStoneMessage(istr);
	}
	break;
	// [2012/07/05 : Sora]  ĳ���� ���� Ȯ�� ������
	case MSG_ITEM_USE_CHAR_SLOT_EXT:
	{
		BYTE result;
		(*istr) >> result;

		if (result == 1) // ��� ����
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(5706, "ĳ���� ���� ������ ���������� Ȱ��ȭ �Ǿ����ϴ�."));
		}
		else	// ��� ����
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(5312, "�������� ����� �� �����ϴ�."));
		}
	}
	break;
	// [2013/02/13] sykim70 Fortune System
	case MSG_ITEM_COSTUME_SUIT_FORTUNE:
	{
		SLONG ret;
		*istr >> ret;
		if (ret == 0)
		{
			SLONG item_index, skill_index, skill_level;
			*istr >> item_index;
			*istr >> skill_index;
			*istr >> skill_level;
			((CUIFortune*)pUIManager->GetUI(UI_FORTUNE))->SetFortune(item_index, skill_index, skill_level);
		}
		else
		{
			((CUIFortune*)pUIManager->GetUI(UI_FORTUNE))->SetFortune(-1, -1, ret);
		}
	}
	break;

	case MSG_ITEM_EXCHANGE:
	{
		ReceiveItemExchange(istr);
	}
	break;

	case MSG_ITEM_COMPOSE:
	{
		ReceiveItemComposMessage(istr);
	}
	break;
	}
}

void CSessionState::ReceiveAttackMessage(CNetworkMessage* istr)
{
	SBYTE	type;
	(*istr) >> type;

	CEntity* penPlEntity;
	CPlayerEntity* penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
	penPlayerEntity = static_cast<CPlayerEntity*>(penPlEntity);

	if (type == MSG_CHAR_PC)
	{
		penPlayerEntity->Read_net_Character(MSG_ATTACK, 0, &(*istr));
	}
	else if (type == MSG_CHAR_NPC)
	{
		penPlayerEntity->Read_net_Mob(MSG_ATTACK, &(*istr));
	}
	else if (type == MSG_CHAR_PET)
	{
		penPlayerEntity->Read_net_Pet(MSG_ATTACK, &(*istr));
	}
	else if (type == MSG_CHAR_ELEMENTAL)
	{
		penPlayerEntity->Read_net_Summon(MSG_ATTACK, &(*istr));
	}
}

void CSessionState::ReceiveExchangeMessage(CNetworkMessage* istr)
{
	BYTE	ExchType;
	(*istr) >> ExchType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	if (ExchType == MSG_EXCHANGE_REQ)
	{
		BYTE		bExchReqType;
		(*istr) >> bExchReqType;

		switch (bExchReqType)
		{
		case MSG_EXCHANGE_REQ_REQ:
		{
			LONG		lSrcIndex;
			LONG		lDestIndex;
			CTString	strSrcName;
			CTString	strDestName;
			(*istr) >> lSrcIndex;
			(*istr) >> strSrcName;
			(*istr) >> lDestIndex;
			(*istr) >> strDestName;
			pUIManager->GetExchange()->ExchangeReq_Req(lSrcIndex, strSrcName, lDestIndex, strDestName);
		}
		break;
		case MSG_EXCHANGE_REQ_REP:
			pUIManager->GetExchange()->ExchangeReq_Rep();
			break;
		case MSG_EXCHANGE_REQ_REJECT_SRC:
			pUIManager->GetExchange()->ExchangeReq_Rej(TRUE);
			break;
		case MSG_EXCHANGE_REQ_REJECT_DEST:
			pUIManager->GetExchange()->ExchangeReq_Rej(FALSE);
			break;
		case MSG_EXCHANGE_REQ_READY_SRC:
			pUIManager->GetExchange()->ExchangeReq_Ready(TRUE);
			break;
		case MSG_EXCHANGE_REQ_READY_DEST:
			pUIManager->GetExchange()->ExchangeReq_Ready(FALSE);
			break;
		case MSG_EXCHANGE_REQ_READY:
			pUIManager->GetExchange()->ExchangeReq_BothReady();
			break;
		case MSG_EXCHANGE_REQ_FULL_SRC:
			pUIManager->GetExchange()->ExchangeReq_Full(TRUE);
			break;
		case MSG_EXCHANGE_REQ_FULL_DEST:
			pUIManager->GetExchange()->ExchangeReq_Full(FALSE);
			break;
		case MSG_EXCHANGE_REQ_OK_SRC:
			pUIManager->GetExchange()->ExchangeReq_Ok(TRUE);
			break;
		case MSG_EXCHANGE_REQ_OK_DEST:
			pUIManager->GetExchange()->ExchangeReq_Ok(FALSE);
			break;
		case MSG_EXCHANGE_REQ_OK:
			pUIManager->GetExchange()->ExchangeReq_BothOk();
			break;
		case MSG_EXCHANGE_REQ_SRC_PET_ANYMORE:
			pUIManager->GetExchange()->ExchangeReq_Pet_Err(FALSE);
			break;
		case MSG_EXCHANGE_REQ_DEST_PET_ANYMORE:
			pUIManager->GetExchange()->ExchangeReq_Pet_Err(TRUE);
			break;

		}
	}
	else if (ExchType == MSG_EXCHANGE_ITEM)
	{
		BYTE	bExchItemType;
		SLONG	slUniIndex;
		SQUAD	llCount;
		SLONG	slIndex;
		SLONG	slPlus;
		SLONG	slFlag;
		SLONG	slUsed;
		SLONG	slUsed2;
		SBYTE	sbOptionCount;
		SBYTE	sbOptionType;
		LONG	lOptionLevel;
#ifdef DURABILITY
		LONG	nDurabilityNow;
		LONG	nDurabilityMax;
#endif // DURABILITY

		(*istr) >> bExchItemType;

		switch (bExchItemType)
		{
		case MSG_EXCHANGE_ITEM_ADD_SRC:
		{
			(*istr) >> slUniIndex;
			(*istr) >> llCount;
			(*istr) >> slIndex;
			(*istr) >> slPlus;
			(*istr) >> slFlag;
			(*istr) >> slUsed;
			(*istr) >> slUsed2;
#ifdef	DURABILITY
			(*istr) >> nDurabilityNow;
			(*istr) >> nDurabilityMax;
#endif
			(*istr) >> sbOptionCount;

			pUIManager->GetExchange()->ExchangeItem_Add(TRUE, slUniIndex, llCount, slIndex, slPlus, slFlag, slUsed, slUsed2);
#ifdef	DURABILITY
			pUIManager->GetExchange()->SetDurability(TRUE, slUniIndex, nDurabilityNow, nDurabilityMax);
#endif	// DURABILITY

			//���� �������϶�...
			if (_pNetwork->GetItemData(slIndex)->GetFlag() & ITEM_FLAG_RARE)
			{
				if (sbOptionCount > 0)
					pUIManager->GetExchange()->ExchangeItem_SetRareOption(istr, TRUE, slUniIndex);
			}
			//���� �������� �ƴϸ�.....
			else
			{
				LONG lOriginOptionVar = ORIGIN_VAR_DEFAULT;

				for (SBYTE sbOption = 0; sbOption < sbOptionCount; sbOption++)
				{
					(*istr) >> sbOptionType;
					(*istr) >> lOptionLevel;

					if (_pNetwork->GetItemData(slIndex)->GetFlag() & ITEM_FLAG_ORIGIN)
					{
						(*istr) >> lOriginOptionVar;
					}

					pUIManager->GetExchange()->ExchangeItem_SetOptionData(TRUE, slUniIndex, sbOption,
						sbOptionType, lOptionLevel, 0, lOriginOptionVar);
				}
			}

			if (_pNetwork->GetItemData(slIndex)->GetFlag() & ITEM_FLAG_ORIGIN)
			{
				pUIManager->GetExchange()->ExchangeItem_SetSkill(istr, TRUE, slUniIndex);
			}
			else
			{
				LONG lPlue2 = 0;
				(*istr) >> lPlue2;

				// [2010/12/16 : Sora] ������ plus2����
				pUIManager->GetExchange()->ExchangeItem_SetPlus2(TRUE, slUniIndex, lPlue2);
			}

			pUIManager->GetExchange()->ExchangeItem_InitSocket(TRUE, slUniIndex);
			// data receive about socket type. [6/23/2010 rumist]
			if (_pNetwork->GetItemData(slIndex)->GetFlag() & ITEM_FLAG_SOCKET)
			{
				SBYTE	sbSocketCreateCount = 0;
				SBYTE	sbSocketCount = 0;
				LONG	lSocketJewelIndex = 0;
				LONG	lSocketInfo[JEWEL_MAX_COUNT] = { -1, };
				int	i;

				for (i = 0; i < JEWEL_MAX_COUNT; i++)
				{
					(*istr) >> lSocketInfo[i];
					if (lSocketInfo[i] >= 0)
						sbSocketCreateCount++;
				}
				for (i = 0; i < JEWEL_MAX_COUNT; i++)
				{
					pUIManager->GetExchange()->ExchangeItem_SetSocketData(TRUE, slUniIndex, sbSocketCreateCount,
						i, lSocketInfo[i]);
				}
			}
		}
		break;

		case MSG_EXCHANGE_ITEM_ADD_DEST:
		{
			(*istr) >> slUniIndex;
			(*istr) >> llCount;
			(*istr) >> slIndex;
			(*istr) >> slPlus;
			(*istr) >> slFlag;
			(*istr) >> slUsed;
			(*istr) >> slUsed2;
#ifdef	DURABILITY
			(*istr) >> nDurabilityNow;
			(*istr) >> nDurabilityMax;
#endif
			(*istr) >> sbOptionCount;

			pUIManager->GetExchange()->ExchangeItem_Add(FALSE, slUniIndex, llCount, slIndex, slPlus, slFlag, slUsed, slUsed2);
#ifdef	DURABILITY
			pUIManager->GetExchange()->SetDurability(FALSE, slUniIndex, nDurabilityNow, nDurabilityMax);
#endif	// DURABILITY

			//���� �������϶�...
			if (_pNetwork->GetItemData(slIndex)->GetFlag() & ITEM_FLAG_RARE)
			{
				if (sbOptionCount > 0)
					pUIManager->GetExchange()->ExchangeItem_SetRareOption(istr, FALSE, slUniIndex);
			}
			//���� �������� �ƴϸ�.....
			else
			{
				LONG lOriginOptionVar = ORIGIN_VAR_DEFAULT;

				for (SBYTE sbOption = 0; sbOption < sbOptionCount; sbOption++)
				{
					(*istr) >> sbOptionType;
					(*istr) >> lOptionLevel;

					if (_pNetwork->GetItemData(slIndex)->GetFlag() & ITEM_FLAG_ORIGIN)
					{
						(*istr) >> lOriginOptionVar;
					}

					pUIManager->GetExchange()->ExchangeItem_SetOptionData(FALSE, slUniIndex, sbOption,
						sbOptionType, lOptionLevel, 0, lOriginOptionVar);
				}
			}

			if (_pNetwork->GetItemData(slIndex)->GetFlag() & ITEM_FLAG_ORIGIN)
			{
				pUIManager->GetExchange()->ExchangeItem_SetSkill(istr, FALSE, slUniIndex);
			}
			else
			{
				LONG lPlue2 = 0;
				(*istr) >> lPlue2;

				// [2010/12/16 : Sora] ������ plus2����
				pUIManager->GetExchange()->ExchangeItem_SetPlus2(FALSE, slUniIndex, lPlue2);
			}

			pUIManager->GetExchange()->ExchangeItem_InitSocket(FALSE, slUniIndex);
			// data receive about socket type. [6/23/2010 rumist]
			if (_pNetwork->GetItemData(slIndex)->GetFlag() & ITEM_FLAG_SOCKET)
			{
				SBYTE	sbSocketCreateCount = 0;
				SBYTE	sbSocketCount = 0;
				LONG	lSocketJewelIndex = 0;
				LONG	lSocketInfo[JEWEL_MAX_COUNT] = { -1, };
				int	i;

				for (i = 0; i < JEWEL_MAX_COUNT; i++)
				{
					(*istr) >> lSocketInfo[i];
					if (lSocketInfo[i] >= 0)
						sbSocketCreateCount++;
				}

				for (i = 0; i < JEWEL_MAX_COUNT; i++)
				{
					pUIManager->GetExchange()->ExchangeItem_SetSocketData(FALSE, slUniIndex, sbSocketCreateCount,
						i, lSocketInfo[i]);
				}
			}
		}
		break;

		case MSG_EXCHANGE_ITEM_DEL_SRC:
		{
			(*istr) >> slUniIndex;
			pUIManager->GetExchange()->ExchangeItem_Del(TRUE, slUniIndex);
		}
		break;

		case MSG_EXCHANGE_ITEM_DEL_DEST:
		{
			(*istr) >> slUniIndex;
			pUIManager->GetExchange()->ExchangeItem_Del(FALSE, slUniIndex);
		}
		break;

		case MSG_EXCHANGE_ITEM_UPDATE_SRC:
		{
			SQUAD llNas;
			(*istr) >> slUniIndex;
			(*istr) >> llCount;
			(*istr) >> llNas;
			pUIManager->GetExchange()->ExchangeItem_Update(TRUE, slUniIndex, llCount, llNas);
		}
		break;

		case MSG_EXCHANGE_ITEM_UPDATE_DEST:
		{
			SQUAD llNas;
			(*istr) >> slUniIndex;
			(*istr) >> llCount;
			(*istr) >> llNas;
			pUIManager->GetExchange()->ExchangeItem_Update(FALSE, slUniIndex, llCount, llNas);
		}
		break;
		}
	}
}

void CSessionState::ReceivePartyMessage(CNetworkMessage* istr)
{
	SBYTE	sbPartyType;
	(*istr) >> sbPartyType;

	CUIManager* pUIManager = CUIManager::getSingleton();
	Party* pParty = GAMEDATAMGR()->GetPartyInfo();

	if (pParty == NULL)
		return;

	switch (sbPartyType)
	{
	case MSG_PARTY_INVITE:
	{
		SBYTE		sbType;
		SLONG		slSrcIndex;
		CTString	strSrcName;
		SBYTE	sbPartyTypeItem = 0;
		SBYTE	sbPartyTypeSPItem = 0;

		(*istr) >> sbType;
		// [sora] ������ �ý��� �߰��� ��Ƽ Ÿ�� �߰�

		(*istr) >> sbPartyTypeItem;
		(*istr) >> sbPartyTypeSPItem;

		(*istr) >> slSrcIndex;
		(*istr) >> strSrcName;

		pParty->PartyInvite(sbType, slSrcIndex, strSrcName, sbPartyTypeItem, sbPartyTypeSPItem);
	}
	break;

	case MSG_PARTY_REJECT_SRC:
		pParty->PartyReject(TRUE);
		break;

	case MSG_PARTY_REJECT_DEST:
		pParty->PartyReject(FALSE);
		break;

	case MSG_PARTY_ADD:
	{
		SBYTE		sbLeader, sbJob, sbJob2, sbLayer;
		SLONG		slIndex, slZone;
		SLONG		swLevel, swHP, swMaxHP, swMP, swMaxMP;
		FLOAT		fX, fZ;
		CTString	strName;

		(*istr) >> sbLeader >> slIndex >> strName >> sbJob >> sbJob2 >> swLevel;
#ifdef HP_PERCENTAGE //  [3/29/2013 Ranma] MSG_PARTY_ADD HP �޴� �κ�
		FLOAT		fHp_percentage;
		(*istr) >> fHp_percentage;
		swHP = (10 * fHp_percentage);
		swMaxHP = 1000;
#else
		(*istr) >> swHP >> swMaxHP;
#endif
		(*istr) >> swMP >> swMaxMP;
		(*istr) >> fX >> fZ >> sbLayer >> slZone;

		pParty->PartyAddMember(sbLeader, slIndex, strName, sbJob, sbJob2, swLevel,
			swHP, swMaxHP, swMP, swMaxMP, fX, fZ, sbLayer, slZone);

		// [100216: selo] ������ ��Ƽ������ �����Ѵ�.
		pParty->SetIsPartyPlay(TRUE);
	}
	break;

	case MSG_PARTY_QUIT:
	{
		SLONG	slIndex;
		(*istr) >> slIndex;

		pParty->PartyQuit(slIndex);
	}
	break;

	case MSG_PARTY_KICK:
	{
		SLONG	slIndex;
		(*istr) >> slIndex;

		pParty->PartyKick(slIndex);
	}
	break;

	case MSG_PARTY_END:
	{
		// [sora] ��ü �˸� �޽��� �ڽ��� ������ �ݴ´�
		if (pUIManager->DoesMessageBoxExist(MSGCMD_EXPEDITION_ERROR))
			pUIManager->CloseMessageBox(MSGCMD_EXPEDITION_ERROR);

		pParty->PartyEnd();

		if (pUIManager->IsPlayInZone())
		{
			pUIManager->SetCSFlagOn(CSF_TELEPORT);
		}

	}
	break;
	case MSG_PARTY_ENDPARTY_START:	// [sora] ��Ƽ���� ��Ƽ ��ü ��û�� ��Ƽ���鿡�� �˸�
	{
		CUIMsgBox_Info	MsgBoxInfo;
		CTString strMessage;
		int nCommandCode = MSGCMD_EXPEDITION_ERROR;

		strMessage = _S(4658, "20���� ��Ƽ�� ��ü�˴ϴ�.");
		// [sora] �ν���Ʈ �������� ��Ȱ��ġ�� �̵��˸�
		if (pUIManager->IsPlayInZone())
		{
			nCommandCode = MSGCMD_EXPEDITION_GO_STARTPLACE;
			strMessage += _S(4659, "�ν���Ʈ ���� ��Ȱ ��ġ�� �̵��մϴ�.(���� �ð� ���� �������� �̵��մϴ�.)");
		}

		MsgBoxInfo.SetMsgBoxInfo(_S(97, "��Ƽ"), UMBS_OK,
			UI_PARTY, nCommandCode);

		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	break;

	case MSG_PARTY_ASSISTINFO:
		break;
	case MSG_PARTY_CHANGEBOSS: // ��Ƽ �� ���� 
	{
		CTString	strBossName;
		CTString	strManadateChaName;
		SLONG		slManadateIndex;
		SBYTE		sbMandate;	// 0: ��Ƽ�� Ż��, 1:����

		(*istr) >> strBossName;
		(*istr) >> slManadateIndex;
		(*istr) >> strManadateChaName;
		(*istr) >> sbMandate;

		GAMEDATAMGR()->GetPartyInfo()->MandateBoss(strBossName, slManadateIndex, strManadateChaName, sbMandate);

	}
	break;
	case MSG_PARTY_ERROR:
	{
		SBYTE	sbError;
		(*istr) >> sbError;

		pParty->PartyError(sbError);
	}
	break;
	case MSG_PARTY_EMPTY: // �۽��� ���� ����� ��Ƽ �ʱ�ȭ [1/11/2007 Theodoric]
		if (pParty->GetMemberCount())
		{
			pParty->PartyEnd();
		}
		break;
	case MSG_PARTY_CHANGETYPE:
	{
		SBYTE sbPartyType;
		(*istr) >> sbPartyType;
		// [sora] ������ �ý��� �߰��� ��Ƽ Ÿ�� �߰�
		SBYTE sbDivisionType;
		SBYTE sbAllOneSet;	//��ƼŸ�Լ��� or �����׸���� ����

		(*istr) >> sbDivisionType;
		(*istr) >> sbAllOneSet;

		if (sbAllOneSet == MSG_PARTY_SETALLONE_ONE) // �����׸� ����
		{
			pParty->SetDivisionType(sbPartyType, sbDivisionType);
			break;
		}
		else if (sbAllOneSet == MSG_PARTY_SETALLONE_ALL) // ��ƼŸ�� ����
		{
			pParty->SetPartyType(sbPartyType);
		}

		CTString strMessage, strPartyType;

		switch (sbPartyType)
		{
		case PT_PEACEEVER:
			strPartyType = _S(2660, "�յ�й� ��Ƽ");
			break;
		case PT_SURVIVAL:
			strPartyType = _S(2661, "�Լ��켱 ��Ƽ");
			break;
		case PT_ATTACK:
			strPartyType = _S(2662, "������ ��Ƽ");
			break;
		}

		strMessage.PrintF(_S(4197, "��Ƽ ������ %s�� ����Ǿ����ϴ�."), strPartyType);

		pUIManager->GetChattingUI()->AddSysMessage(strMessage);

		//��Ƽ ����â�� ������Ʈ���� �����Ƿ� �ݾ��ش�.
		if (pUIManager->DoesMessageBoxExist(MSGCMD_DIVISION_INFO))
		{
			pUIManager->CloseMessageBox(MSGCMD_DIVISION_INFO);
		}
	}
	break;

	case MSG_PARTY_INZONE_CLEAR_REP:
	{
		CTString strTemp = _S(4660, "�ν���Ʈ ���� �ʱ�ȭ �Ǿ����ϴ�.");

		pUIManager->GetChattingUI()->AddSysMessage(strTemp);
	}
	break;

	case MSG_PARTY_TYPEINFO:
	{
		SBYTE sbPartyType, sbDivisionTypeItem, sbDivisionTypeSPItem;

		(*istr) >> sbPartyType;
		(*istr) >> sbDivisionTypeItem;
		(*istr) >> sbDivisionTypeSPItem;

		pParty->SetPartyType(sbPartyType);
		pParty->SetDivisionType(sbDivisionTypeItem, MSG_DIVITYPE_ITEM, TRUE);
		pParty->SetDivisionType(sbDivisionTypeSPItem, MSG_DIVITYPE_SPECIAL, TRUE);

		// [091119: selo] ������ ��Ƽ������ �����Ѵ�.
		pParty->SetIsPartyPlay(TRUE);
	}
	break;
	}
}

void CSessionState::ReceiveQuickSlotMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;//1013
	SBYTE	sbPage, sbSlotType;
	(*istr) >> ubType;
	(*istr) >> sbPage;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (ubType)
	{
	case MSG_QUICKSLOT_LIST:
	{
		pUIManager->GetQuickSlot()->ClearAllBtns(sbPage);

		//for( int iSlot = 0; iSlot < 10; iSlot++ )
		for (int iSlot = 0; iSlot < QSLOT_BTN_COUNT; iSlot++)
		{
			(*istr) >> sbSlotType;
			if (sbSlotType == QUICKSLOT_TYPE_EMPTY)
			{
				pUIManager->GetQuickSlot()->AddBtn(sbPage, iSlot);
			}
			else if (sbSlotType == QUICKSLOT_TYPE_ITEM)
			{
				SWORD	nTab, nIdx;
				(*istr) >> nTab;
				(*istr) >> nIdx;

				pUIManager->GetQuickSlot()->AddBtn(sbPage, iSlot, sbSlotType, nTab, nIdx);
			}
			else if (sbSlotType == QUICKSLOT_TYPE_ITEM_WEAR)
			{
				SLONG	nType, nIdx;

				(*istr) >> nType;
				(*istr) >> nIdx;

				pUIManager->GetQuickSlot()->AddBtn(sbPage, iSlot, sbSlotType, nType, nIdx);
			}
			else
			{
				SLONG	slIndex; // Date : 2005-03-02,   By Lee Ki-hwan
				(*istr) >> slIndex;

				pUIManager->GetQuickSlot()->AddBtn(sbPage, iSlot, sbSlotType, slIndex);
			}
		}
		// ţ���� ��ư�� ���� �ɶ� ���ϵ嵵 ����� ������ ������ �Ѵ� [12/21/2012 Ranma]

		((CUIChildQuickSlot*)pUIManager->GetUI(UI_QUICKSLOT2))->FirstOpen();
		((CUIChildQuickSlot*)pUIManager->GetUI(UI_QUICKSLOT3))->FirstOpen();
		((CUIChildQuickSlot*)pUIManager->GetUI(UI_QUICKSLOT4))->FirstOpen();
	}
	break;

	case MSG_QUICKSLOT_ADD:
	{
		SBYTE	sbSlotNum;
		(*istr) >> sbSlotNum;
		(*istr) >> sbSlotType;

		if (sbSlotType == QUICKSLOT_TYPE_EMPTY)
		{
			pUIManager->GetQuickSlot()->AddBtn(sbPage, sbSlotNum);
		}
		else if (sbSlotType == QUICKSLOT_TYPE_ITEM)
		{
			SWORD	nTab, nIdx;
			(*istr) >> nTab;
			(*istr) >> nIdx;

			pUIManager->GetQuickSlot()->AddBtn(sbPage, sbSlotNum, sbSlotType, nTab, nIdx);
		}
		else if (sbSlotType == QUICKSLOT_TYPE_ITEM_WEAR)
		{
			SLONG	nType, nIdx;

			(*istr) >> nType;
			(*istr) >> nIdx;

			pUIManager->GetQuickSlot()->AddBtn(sbPage, sbSlotNum, sbSlotType, nType, nIdx);
		}
		else
		{
			SLONG	slIndex;		// Date : 2005-03-02,   By Lee Ki-hwan
			(*istr) >> slIndex;
			if (slIndex >= 0)
			{
				pUIManager->GetQuickSlot()->AddBtn(sbPage, sbSlotNum, sbSlotType, slIndex);
			}
		}
	}
	break;

	case MSG_QUICKSLOT_SWAP:
	{
		SBYTE	sbSlotNum1, sbSlotNum2;
		(*istr) >> sbSlotNum1;
		(*istr) >> sbSlotNum2;

		pUIManager->GetQuickSlot()->SwapBtns(sbPage, sbSlotNum1, sbSlotNum2);
	}
	break;
	}
}

void CSessionState::ReceiveSkillMessage(CNetworkMessage* istr)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(istr->GetBuffer());
	CUIManager* pUIManager = CUIManager::getSingleton();

	CEntity* penPlEntity;
	CPlayerEntity* penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
	penPlayerEntity = static_cast<CPlayerEntity*>(penPlEntity);

	switch (pBase->subType)
	{
	case MSG_SKILL_LIST:
	{
		ResponseClient::skillList* pPack = reinterpret_cast<ResponseClient::skillList*>(istr->GetBuffer());
		ResponseClient::skillList::tag_list* pList = NULL;

		pUIManager->GetCharacterInfo()->ClearSkills();
		MY_INFO()->ClearSkill();

		if (pPack->count > 0)
		{
			pList = pPack->list;
		}

		for (int i = 0; i < pPack->count; i++)
		{
			CSkill& rSelSkill = _pNetwork->GetSkillData(pList[i].index);

			if (rSelSkill.GetType() == CSkill::ST_SEAL)
			{
				if (rSelSkill.Skill_Data.index > 0)
					pUIManager->GetCharacterInfo()->AddSeal(pList[i].index, pList[i].sealExp);
			}
			else if (rSelSkill.GetType() == CSkill::ST_MELEE ||
				rSelSkill.GetType() == CSkill::ST_RANGE ||
				rSelSkill.GetType() == CSkill::ST_MAGIC ||
				rSelSkill.GetType() == CSkill::ST_SUMMON_TOTEM_SKILL)
			{
				if (pList[i].enable <= 0)
					continue;

				if (rSelSkill.Skill_Data.index > 0)
				{
					MY_INFO()->SetSkill(pPack->list[i].index, (int)pPack->list[i].level);
					pUIManager->GetCharacterInfo()->AddSkill(pPack->list[i].index, pPack->list[i].level);
				}

				if (pList[i].index >= 0 && pList[i].index < _pNetwork->ga_World.wo_aSkillData.Count())
				{
					CSkill& SkillData = _pNetwork->GetSkillData(pList[i].index);

					if (pList[i].sendTime <= 0)
					{
						SkillData.ResetStartTime();
						continue;
					}

					SLONG slRemainTime = ((SLONG)time(NULL) - _pNetwork->slServerTimeGap) - pList[i].sendTime;

					if (slRemainTime > 0)
						SkillData.SetStartTime(slRemainTime);
				}
			}
			else
			{
				if (rSelSkill.Skill_Data.index > 0)
				{
					MY_INFO()->SetSkill(pPack->list[i].index, (int)pPack->list[i].level);
					pUIManager->GetCharacterInfo()->AddSkill(pPack->list[i].index, pPack->list[i].level);
				}
			}
		}

		if (pUIManager->GetSkillNew()->IsVisible() == TRUE || pUIManager->GetSkillNew()->GetHide() == FALSE)
			pUIManager->GetSkillNew()->UpdateSkillData();
	}
	break;

	case MSG_SKILL_LEARN:
	{
		ResponseClient::skillLearnMsg* pPack = reinterpret_cast<ResponseClient::skillLearnMsg*>(istr->GetBuffer());

		_pNetwork->MyCharacterInfo.sp = pPack->skillPoint;
		pUIManager->GetSkillNew()->LearnSkillMessage(pPack->skillIndex, pPack->skillLevel_flag, pPack->skillLevel);
	}
	break;

	case MSG_SKILL_READY:
	{
		//��ų ����.		
		penPlayerEntity->Read_net_Character(MSG_SKILL, MSG_SKILL_READY, istr);
	}
	break;

	case MSG_SKILL_FIRE:
	{
		//��ų �ߵ�.
		//2012/11/09 jeil ��ų �ߵ��� ������ �κ� ī���Ͱ� ���⼭ üũ?		
		penPlayerEntity->Read_net_Character(MSG_SKILL, MSG_SKILL_FIRE, istr);
	}
	break;

	case MSG_SKILL_CANCEL:
	{
		penPlayerEntity->Read_net_Character(MSG_SKILL, MSG_SKILL_CANCEL, istr);		//1013	
		//��ų���.
	}
	break;

	case MSG_SKILL_LEARN_ERROR:
	{
		ResponseClient::skillLearnErrorMsg* pPack = reinterpret_cast<ResponseClient::skillLearnErrorMsg*>(istr->GetBuffer());

		pUIManager->GetSkillLearn()->LearnSkillError(pPack->errorCode);
	}
	break;
	case MSG_SKILL_AUTO_USE:
	{
		ResponseClient::skillAutoUseMsg* pPack = reinterpret_cast<ResponseClient::skillAutoUseMsg*>(istr->GetBuffer());

		pUIManager->GetCharacterInfo()->UseSkill(pPack->skillIndex);
	}
	break;
	case MSG_SKILL_LEARN_SEAL:
	{
		ResponseClient::sealSkillLearn* pPack = reinterpret_cast<ResponseClient::sealSkillLearn*>(istr->GetBuffer());

		pUIManager->GetCharacterInfo()->AddSeal(pPack->skillIndex, pPack->exp);

		// Create message box of skill learn
		CTString	strMessage;
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(4490, "��ǥ"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		strMessage.PrintF(_S(4661, "��ǥ�� �����Ͽ����ϴ�"));
		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);

	}break;
	case MSG_SKILL_SOUL:
	{
		ResponseClient::skillSoulCountMsg* pPack = reinterpret_cast<ResponseClient::skillSoulCountMsg*>(istr->GetBuffer());

		_pNetwork->MyCharacterInfo.sbSoulCount = pPack->soulCount; // ��ȥ ����
	}
	break;
	case MSG_SKILL_MIDLEVEL_SUPPORT:
	{
		ResponseClient::skillSupportMsg* pPack = reinterpret_cast<ResponseClient::skillSupportMsg*>(istr->GetBuffer());
		CTString strMessage;

		switch (pPack->flag)
		{
		case 0:
			strMessage = _S(8429, "You don't have the required level to heal");
			break;
			// case 1:
			// 	strMessage = _S(8430, "You are ready to fight again!");
			// 	break;
		}

		pUIManager->CloseMessageBox(UI_NONE);
		if (!strMessage.IsEmpty()) {
			CUIMsgBox_Info MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
	}
	break;

	case MSG_SKILL_ERROR:
	{
		ResponseClient::skillErrorMsg* pPack = reinterpret_cast<ResponseClient::skillErrorMsg*>(istr->GetBuffer());

		if (!(_pNetwork->MyCharacterInfo.eMorphStatus == CNetworkLibrary::MyChaInfo::eMORPH_EVOCATION)
			&& !(_pNetwork->MyCharacterInfo.eMorphStatus == CNetworkLibrary::MyChaInfo::eMORPH_TRANSFORMATION))
		{
			_pNetwork->MyCharacterInfo.eMorphStatus = CNetworkLibrary::MyChaInfo::eMORPH_END;
		}

		switch (pPack->errorCode)
		{
		case MSG_SKILL_ERROR_CANNOT_SPELL:
			pUIManager->GetChattingUI()->AddSysMessage(_S(1438, "��ų ����� �Ұ����� �����Դϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_ALREADY_USE:	// �ٸ� ��ų �����
			pUIManager->GetChattingUI()->AddSysMessage(_S(315, "�ٸ� ��ų�� ������Դϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_NOTFOUND:		// �׷� ��ų �����
			pUIManager->GetChattingUI()->AddSysMessage(_S(316, "�������� �ʴ� ��ų�Դϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_NOTREADY:		// ��ų �غ� ��... ��, ���� ��ų ������		���� ��ų ���� �ð��� �ȵǾ�����
			pUIManager->GetChattingUI()->AddSysMessage(_S(317, "��ų�� �غ����Դϴ�."), SYSMSG_ERROR);
			// NOTE : ��ų �ð��� �ȵƴٱ� ������Ű�鼭 ��ų�� Cancel�ϸ� �ȵ�.
			break;
		case MSG_SKILL_ERROR_INVAL_TARGET:	// Ÿ���� �߸��Ǿ���
			pUIManager->GetChattingUI()->AddSysMessage(_S(318, "Ÿ���� �߸��Ǿ����ϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_INSUFF_MP:		// ������ �� �¾� ��� ����(MP)
			pUIManager->GetChattingUI()->AddSysMessage(_S(320, "MP�� �����մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_INSUFF_HP:		// ������ �� �¾� ��� ����(HP)
			pUIManager->GetChattingUI()->AddSysMessage(_S(319, "HP�� �����մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_INSUFF_ITEM:	// ������ �� �¾� ��� ����(Item)
			pUIManager->GetChattingUI()->AddSysMessage(_S(1330, "�������� �����մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_LONG:	// �־ �ȵ�
			pUIManager->GetChattingUI()->AddSysMessage(_S(322, "�Ÿ��� �־ ����� �� �����ϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_INVAL_STATE_DEATH:		// ���� �Ҹ��� : �׾�� ����
			pUIManager->GetChattingUI()->AddSysMessage(_S(390, "�׾��� ���� ��밡�� �մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_INVAL_STATE_WEAPON:		// ���� �Ҹ��� : ���� ���ø� ����
			pUIManager->GetChattingUI()->AddSysMessage(_S(391, "���⸦ �����ؾ� ��밡�� �մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_INVAL_STATE_SITDOWN:	// ���� �Ҹ��� : �ɾƼ��� ����
			pUIManager->GetChattingUI()->AddSysMessage(_S(392, "�ɾ����� ���� ��밡�� �մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_INVAL_STATE_PEACEZONE:	// ���� �Ҹ��� : �ǽ��� �Ұ���
			pUIManager->GetChattingUI()->AddSysMessage(_S(393, "��ȭ�������� ��� �Ұ����մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_INVAL_STATE_STAND:		// ���� �Ҹ��� : ������ ����
			pUIManager->GetChattingUI()->AddSysMessage(_S(394, "������ ���� ��밡�� �մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_INVAL_STATE_SHIELD:	// ���� �Ҹ��� : ���� ������
			pUIManager->GetChattingUI()->AddSysMessage(_S(1331, "���и� �����ؾ߸� ����մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_INVAL_STATE_MAGIC:		// ���� �Ҹ��� : �ʿ� ���� �����
		{
			CSkill& skill = _pNetwork->GetSkillData(pPack->skillIndex);
			CTString strMessage;
			switch (pPack->skillIndex)
			{
			case 236: // ���̵� ���� 
			case 237: // ���̵� �� 
				strMessage.PrintF(_S(2063, "%s�� ����ϱ� ���ؼ��� [�κ�������Ƽ]��ų�� �ʿ��մϴ�."), skill.GetName());
				break;
			default:
				strMessage = _S(1332, "Ư�� ���� ��ų�� �ʿ��մϴ�.");
				break;
			}
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			//penPlayerEntity->Read_net_Character_SkillError( MSG_SKILL_ERROR_INVAL_STATE_MAGIC );
		}
		break;
		case MSG_SKILL_ERROR_STATPOINT_STR:			// �� ����
			pUIManager->GetChattingUI()->AddSysMessage(_S(1333, "���� �����մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_STATPOINT_DEX:			// ��ø ����
			pUIManager->GetChattingUI()->AddSysMessage(_S(1334, "��ø�� �����մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_STATPOINT_INT:			// ���� ����
			pUIManager->GetChattingUI()->AddSysMessage(_S(1335, "������ �����մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_STATPOINT_CON:			// ü�� ����
			pUIManager->GetChattingUI()->AddSysMessage(_S(1336, "ü���� �����մϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_TARGET_PKLIMITLEVEL: // 15���� ���ϴ� pvp�� �� �� �����ϴ�.
			pUIManager->GetChattingUI()->AddSysMessage(_S(2230, "15���� ������ �ɸ��ʹ� ������ �� �����ϴ�."), SYSMSG_ERROR);
			pUIManager->LostTarget();
			break;
		case MSG_SKILL_ERROR_ELEMENTAL_TIME:			// ��ȯ �Ұ��� : ��ȯ�� ����� 5�е��� ��ȯ �Ұ�
		{
			CTString strMessage;
			int iMin, iSec;
			if (pPack->extraInfo == 0)
			{
				iMin = 0;
				iSec = 1;
			}
			else
			{
				iMin = pPack->extraInfo / 60;
				iSec = pPack->extraInfo % 60;
			}
			strMessage.PrintF(_S(2360, "[%d�� %d��] �Ŀ� ��ȯ���� ��ȯ �����մϴ�."), iMin, iSec);
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		}
		//pUIManager->GetChattingUI()->AddSysMessage( _S(2361, "��ȯ���� ����ϰ� 5�е����� ��ȯ�� �Ұ����մϴ�." ), SYSMSG_ERROR ); 
		//pUIManager->CancelSkill();
		break;
		case MSG_SKILL_ERROR_ELEMENTAL_FIRE:			// ��ȯ �Ұ��� : �������ɰ� �ߺ� �Ұ�
			pUIManager->GetChattingUI()->AddSysMessage(_S(2362, "���� ������ �̹� ��ȯ�Ǿ� �ְų�, ���� ���ɰ� �浹�Ͽ� ��ȯ���� ��ȯ�Ҽ� �����ϴ�."), SYSMSG_ERROR);
			//pUIManager->CancelSkill();
			break;
		case MSG_SKILL_ERROR_ELEMENTAL_WIND:			// ��ȯ �Ұ��� : �ٶ������ɰ� �ߺ� �Ұ�
			pUIManager->GetChattingUI()->AddSysMessage(_S(2363, "�ٶ��� ������ �̹� ��ȯ�Ǿ� �ְų�, �ٶ��� ���ɰ� �浹�Ͽ� ��ȯ���� ��ȯ�Ҽ� �����ϴ�."), SYSMSG_ERROR);
			//pUIManager->CancelSkill();
			break;
		case MSG_SKILL_ERROR_ELEMENTAL_EARTH:		// ��ȯ �Ұ��� : ���������ɰ� �ߺ� �Ұ�
			pUIManager->GetChattingUI()->AddSysMessage(_S(2364, "������ ������ �̹� ��ȯ�Ǿ� �ְų�, ������ ���ɰ� �浹�Ͽ� ��ȯ���� ��ȯ�Ҽ� �����ϴ�."), SYSMSG_ERROR);
			//pUIManager->CancelSkill();
			break;
		case MSG_SKILL_ERROR_ELEMENTAL_WATER:		// ��ȯ �Ұ��� : �������ɰ� �ߺ� �Ұ�
			pUIManager->GetChattingUI()->AddSysMessage(_S(2365, "���� ������ �̹� ��ȯ�Ǿ� �ְų�, ���� ���ɰ� �浹�Ͽ� ��ȯ���� ��ȯ�Ҽ� �����ϴ�."), SYSMSG_ERROR);
			//pUIManager->CancelSkill();
			break;
		case MSG_SKILL_ERROR_EVOCATION_ALREADY:
			pUIManager->GetChattingUI()->AddSysMessage(_S(2366, "�̹� ������ �����Դϴ�."), SYSMSG_ERROR);
			//pUIManager->CancelSkill();
			break;
		case MSG_SKILL_ERROR_EVOCATION_TIME:
		{
			CTString strMessage;
			int iMin, iSec;
			if (pPack->extraInfo == 0)
			{
				iMin = 0;
				iSec = 1;
			}
			else
			{
				iMin = pPack->extraInfo / 60;
				iSec = pPack->extraInfo % 60;
			}
			strMessage.PrintF(_S(2367, "[%d�� %d��] �Ŀ� ���� �����մϴ�."), iMin, iSec);
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			_pNetwork->MyCharacterInfo.eMorphStatus = CNetworkLibrary::MyChaInfo::eMORPH_END;
		}
		break;
		case MSG_SKILL_ERROR_CANNOT_INVISIBLE:
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(3167, "���Ϳ��� Ÿ������ �Ǿ� ���� ��� ��ų�� ����� �� �����ϴ�."), SYSMSG_ERROR);
		}
		break;
		case MSG_SKILL_ERROR_CANNOT_DEATHMOTION_ANOTHER_PC:
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(3168, "�ݰ� 15M�̳� ����� �𸣴� ������ �����Ͽ� ��ų�� ����� �� �����ϴ�."), SYSMSG_ERROR);
		}
		break;
		case MSG_SKILL_ERROR_MISS_ROGUE_SKILL:		// 070725_ttos: ���ϵ� ��� ��ų(index 125) ����
			pUIManager->GetChattingUI()->AddSysMessage(_S(3595, "��ų ��뿡 �����Ͽ����ϴ�."), SYSMSG_ERROR);
			break;

		case MSG_SKILL_ERROR_COMPETITION:
			pUIManager->GetChattingUI()->AddSysMessage(_S(4264, "��Ÿ���� ���� ���Դϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_INVAL_STATE_DARKNESS:
			pUIManager->GetChattingUI()->AddSysMessage(_S(4686, "�絵 ��忡�� ����� �� ���� ��ų�Դϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_WARP_CAN_NOT_GO_THERE:
			pUIManager->GetChattingUI()->AddSysMessage(_S(4714, "�߰��� ���θ����ų� �� �� ���� ���Դϴ�"), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_SOUL_COUNT_ALREADY_FULL:
			pUIManager->GetChattingUI()->AddSysMessage(_S(4715, "��ȥ ���� ������ �ִ��Դϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_CANNOT_TO_PC:
			pUIManager->GetChattingUI()->AddSysMessage(_S(4716, "PC���� ��� �Ұ��� �մϴ�.(PK ���� �Ұ���)"), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_DONT_HAS_SOUL:
			pUIManager->GetChattingUI()->AddSysMessage(_S(4717, "�̹� ��ȥ�� ������ ����̶� ������ �Ұ��� �մϴ�. "), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_INVAL_STATE_PSERSONAL_DUNGEON:
			pUIManager->GetChattingUI()->AddSysMessage(_S(5183, "�̱� �������� ����� �� ���� ��ų�Դϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_DUPLICATE:
			pUIManager->GetChattingUI()->AddSysMessage(_S(556, "�̹� ������� ������ �Դϴ�."), SYSMSG_ERROR);
			break;
		case MSG_SKILL_ERROR_CANNOT_ZONE:
			pUIManager->GetChattingUI()->AddSysMessage(_S(5413, "���� �������� ����� �� �����ϴ�."), SYSMSG_ERROR);
			break;
		}

		// NOTE : ��ų �����ϰ� ����� ���ϸ� ���� �ɸ��� ������...
		pUIManager->CancelSkill(FALSE, TRUE);

		pUIManager->SetCSFlagOff(CSF_SKILLREADY);

	}
	break;

	case MSG_SKILL_RESET_COOLTIME:
	{
		_pNetwork->ResetSkillDelayTime(); //��ų ������ Ÿ�� �ʱ�ȭ
		pUIManager->GetQuickSlot()->ResetQuickSLotSKill(); // �����Կ��� ��ų ����			
	}
	break;
	case MSG_SKILL_TOGGLE:
	{
		ReceiveToggleMessage(istr);
	}
	break;
	case MSG_SKILL_RECOVER_HP:
	{
		ReceiveRecoverHp(istr);
	}
	break;
	}
}

// ���� ���� Ư�� ��ų...(Passive Skill��)
//-----------------------------------------------------------------------------
// Purpose:
// Input  : *istr - 
//-----------------------------------------------------------------------------
void CSessionState::ReceiveSSkillMessage(CNetworkMessage* istr)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(istr->GetBuffer());
	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (pBase->subType)
	{
	case MSG_SSKILL_LIST:
	{
		ResponseClient::sskillList* pPack = reinterpret_cast<ResponseClient::sskillList*>(istr->GetBuffer());
		pUIManager->GetCharacterInfo()->ClearSSkills();
		MY_INFO()->ClearSSkill();

		for (int iSkill = 0; iSkill < pPack->listCount; iSkill++)
		{
			MY_INFO()->SetSkill(pPack->list[iSkill].skillIndex, pPack->list[iSkill].skillLevel, true);
			pUIManager->GetCharacterInfo()->AddSkill(pPack->list[iSkill].skillIndex, pPack->list[iSkill].skillLevel, TRUE);
		}
	}
	break;
	case MSG_SSKILL_LEARN:
	{
		ResponseClient::sskillLearn* pPack = reinterpret_cast<ResponseClient::sskillLearn*>(istr->GetBuffer());

		MY_INFO()->SetSkill(pPack->skillIndex, pPack->skillLevel, true);
		pUIManager->GetSkillLearn()->LearnSkill(pPack->skillIndex, pPack->flag, pPack->skillLevel, TRUE);
		pUIManager->GetCharacterInfo()->SetSSkill();
	}
	break;
	case MSG_SSKILL_LEARN_ERROR:		// ���� �߻�.
	{
		ResponseClient::sskillLearnError* pPack = reinterpret_cast<ResponseClient::sskillLearnError*>(istr->GetBuffer());

		pUIManager->GetSkillLearn()->LearnSSkillError(pPack->errorCode);
	}
	break;
	}
}

void CSessionState::ReceiveStatMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;//1013
	SLONG   swRemainedStat;
	(*istr) >> ubType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	if (ubType == MSG_STATPOINT_REMAIN)
	{
		(*istr) >> swRemainedStat;

		_UIAutoHelp->SetStatpoint(_pNetwork->MyCharacterInfo.StatPoint, swRemainedStat);

		_pNetwork->MyCharacterInfo.StatPoint = swRemainedStat;
		pUIManager->GetCharacterInfo()->NotifyStatPoint();
	}
	else if (ubType == MSG_STATPOINT_USE)
	{
		UBYTE	ubStatType;
		SLONG	slStatChange;
		(*istr) >> ubStatType;
		(*istr) >> slStatChange;
		(*istr) >> swRemainedStat;

		_pNetwork->MyCharacterInfo.StatPoint = swRemainedStat;
		pUIManager->GetCharacterInfo()->UseStatPoint(ubStatType, slStatChange);
	}
	else if (ubType == MSG_STATPOINT_ERROR)
	{
		SBYTE	sbError;
		(*istr) >> sbError;

		pUIManager->GetCharacterInfo()->StatPointError(sbError);
	}
	// ���� �ʱ�ȭ��.
	else if (ubType == MSG_STATPOINT_RESET)
	{
		LONG	lStr;
		LONG	lDex;
		LONG	lInt;
		LONG	lCon;
		int		iTotalStat = 0;

		(*istr) >> lStr;
		(*istr) >> lDex;
		(*istr) >> lInt;
		(*istr) >> lCon;
		iTotalStat += lStr;
		iTotalStat += lDex;
		iTotalStat += lInt;
		iTotalStat += lCon;

		CTString strSysMessage;
		strSysMessage.PrintF(_S(1337, "�� %d ������ �ʱ�ȭ�Ǿ����ϴ�."), iTotalStat);
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_NORMAL);
		pUIManager->GetInitJob()->CloseInitJob();
	}
}

void CSessionState::ReceiveUIMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;

	if (ubType == MSG_UI_PLUS_EFFECT_REP)
	{
		SBYTE	sbItemPlusEffect;
		SLONG	slCharIndex;

		(*istr) >> sbItemPlusEffect;
		(*istr) >> slCharIndex;

		if (slCharIndex == _pNetwork->MyCharacterInfo.index)
		{
			_pNetwork->MyCharacterInfo.sbItemEffectOption = sbItemPlusEffect;
		}
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, slCharIndex);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTarget->SetItemEffectOption(sbItemPlusEffect);
				pTarget->cha_itemEffect.Refresh(&(pTarget->m_pEntity->GetModelInstance()->m_tmSkaTagManager), sbItemPlusEffect);
			}
		}
	}
}

void CSessionState::ReceiveSystemMessage(CNetworkMessage* istr)
{
	SBYTE		sbType;
	SBYTE		sbTab;	// 1013
	CTString	strSysMessage;

	(*istr) >> sbType;

	CEntity* penPlEntity;
	CPlayerEntity* penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity(0);		// ĳ���� �ڱ� �ڽ�
	penPlayerEntity = static_cast<CPlayerEntity*>(penPlEntity);

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (sbType)
	{
	case MSG_SYS_WHISPER_NOTFOUND:	// �Ӹ� ��� ����	:
		pUIManager->GetChattingUI()->AddSysMessage(_S(304, "�ӼӸ� ��븦 ã�� �� �����ϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_TIMEOUT:			// Ÿ�� �ƿ� �߻�	:
		strSysMessage = "MSG_SYS_TIMEOUT";
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		break;

	case MSG_SYS_CANNOT_WEAR:		// ���� ����		:
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(305, "��� ������ �� �����ϴ�."), SYSMSG_ERROR);

		if (CUIManager::getSingleton()->IsCSFlagOn(CSF_ITEMWEARING))
		{
			// ��� ���� �õ� ���� ����
			CUIManager::getSingleton()->SetCSFlagOffElapsed(CSF_ITEMWEARING);
		}
	}
	break;

	case MSG_SYS_FULL_INVENTORY:	// �κ��丮 ���� ��	: tab_index(uc)
		(*istr) >> sbTab;//1013
		pUIManager->GetChattingUI()->AddSysMessage(_S(265, "�κ��丮 ������ �����մϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_CUSTOM:			// Ŀ���� �޽���	: msg(str)
	{
		CTString	strMsg;//1013
		(*istr) >> strMsg;//1013
		strSysMessage = "MSG_SYS_CUSTOM";
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;

	case MSG_SYS_SHORT_MONEY:		// �� ���� ������	:
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(306, "������ �����մϴ�."), SYSMSG_ERROR);

		// ������ �̵��߿� �� �� �ִ� �޼����̴�. (���� ������ ���� �ΰ�)
		pUIManager->SetCSFlagOff(CSF_TELEPORT);
	}
	break;
	
	case MSG_SYS_SHOP_CANCEL:		// ���� �ŷ� ���	:
		pUIManager->GetChattingUI()->AddSysMessage(_S(307, "���� �ŷ��� ����ϼ̽��ϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_EXCHANGE_NOTFOUND:	// ��ȯ ��� ����	:
		pUIManager->GetChattingUI()->AddSysMessage(_S(308, "��ȯ ��븦 ã�� �� �����ϴ�."), SYSMSG_ERROR);

		pUIManager->CloseMessageBox(MSGCMD_EXCH_REQ_SRC);
		if (pUIManager->IsCSFlagOn(CSF_EXCHANGE))
		{
			pUIManager->SetCSFlagOff(CSF_EXCHANGE);
		}
		break;

	case MSG_SYS_EXCHANGE_ALREADY:	// �̹� ��ȯ ��		: 
		pUIManager->GetChattingUI()->AddSysMessage(_S(309, "�̹� ��ȯ���Դϴ�."), SYSMSG_ERROR);
		pUIManager->GetExchange()->ResetExchange();
		pUIManager->CloseMessageBox(MSGCMD_EXCH_REQ_SRC);
		if (pUIManager->IsCSFlagOn(CSF_EXCHANGE))
		{
			pUIManager->SetCSFlagOff(CSF_EXCHANGE);
		}
		break;

		/*
		case MSG_SYS_SKILL_ALREADY_USE:	// �ٸ� ��ų �����
			pUIManager->GetChattingUI()->AddSysMessage( _S( 315, "�ٸ� ��ų�� ������Դϴ�." ), SYSMSG_ERROR );
			penPlayerEntity->Read_net_Character( MSG_SYS_SKILL_ALREADY_USE, NULL );
			break;

		case MSG_SYS_SKILL_NOTFOUND:		// �׷� ��ų �����
			pUIManager->GetChattingUI()->AddSysMessage( _S( 316, "�������� �ʴ� ��ų�Դϴ�." ), SYSMSG_ERROR );
			penPlayerEntity->Read_net_Character( MSG_SYS_SKILL_NOTFOUND, NULL );
			break;

		case MSG_SYS_SKILL_NOTREADY:		// ��ų �غ� ��... ��, ���� ��ų ������ ���� ��ų ���� �ð��� �ȵǾ�����
			pUIManager->GetChattingUI()->AddSysMessage( _S( 317, "��ų�� �غ����Դϴ�." ), SYSMSG_ERROR );
			penPlayerEntity->Read_net_Character( MSG_SYS_SKILL_NOTREADY, NULL );
			break;

		case MSG_SYS_SKILL_INVAL_TARGET:	// Ÿ���� �߸��Ǿ���
			pUIManager->GetChattingUI()->AddSysMessage( _S( 318, "Ÿ���� �߸��Ǿ����ϴ�." ), SYSMSG_ERROR );
			penPlayerEntity->Read_net_Character( MSG_SYS_SKILL_INVAL_TARGET, NULL );
			break;

		case MSG_SYS_SKILL_INSUFF:		// ������ �� �¾� ��� ����(HP, MP, ������ ����)
			{
				SBYTE	sbErrType;
				(*istr) >> sbErrType;

				switch( sbErrType )
				{
				case 0:		// HP
					strSysMessage = _S( 319, "HP�� �����մϴ�." );
					break;
				case 1:		// MP
					strSysMessage = _S( 320, "MP�� �����մϴ�." );
					break;
				case 2:		// Item
					strSysMessage = _S( 321, "���" );
					break;
				}
				pUIManager->GetChattingUI()->AddSysMessage( strSysMessage, SYSMSG_ERROR );
				penPlayerEntity->Read_net_Character( MSG_SYS_SKILL_INSUFF, NULL );
			}
			break;

		case MSG_SYS_SKILL_LONG:			// �־ �ȵ�
			pUIManager->GetChattingUI()->AddSysMessage( _S( 322, "�Ÿ��� �־ ����� �� �����ϴ�." ), SYSMSG_ERROR );
			penPlayerEntity->Read_net_Character( MSG_SYS_SKILL_LONG, NULL );
			break;
*/
	case MSG_SYS_NOT_OWNER_ITEM:		// ������ �켱���� ����
		pUIManager->GetChattingUI()->AddSysMessage(_S(323, "������ ������ �����ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_UPGRADE_NOCONDITION:	// ������ �ȸ¾� ���׷��̵� ���� (�Ϲ����ü� ������ ���� ����)
		pUIManager->GetChattingUI()->AddSysMessage(_S(328, "������ ���� �ʾ� ���׷��̵� �� �� �����ϴ�."), SYSMSG_ERROR);
		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_PET_ITEM_UPGRADE);
		break;

	case MSG_SYS_MAKE_REFINE_KIND:		// ���⳪ ���� �ƴ� �ٸ��� ���ü����� ��ȯ�Ϸ��� ��
		pUIManager->GetChattingUI()->AddSysMessage(_S(329, "����� ���� ���׷��̵� �� �� �ֽ��ϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_MAKE_REFINE_WEARING:	// �԰� �ִ� ���������� ���ü� ��ȯ �Ұ���
		pUIManager->GetChattingUI()->AddSysMessage(_S(330, "����� �������� ���ü����� ��ȯ�� �Ұ����մϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_MAKE_REFINE_PLUS:		// Plus ���� ���õǾ� �ִ� ������ ���ü� ��ȯ �Ұ���
		pUIManager->GetChattingUI()->AddSysMessage(_S(331, "���׷��̵� �� �������� ���ü����� ��ȯ�� �Ұ����մϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_MEMPOS_CANT_WRITE:		// ��� ��� ��ġ ��� �Ұ��� ��
		pUIManager->GetChattingUI()->AddSysMessage(_S(333, "�޸� ��ũ���� ����� �� ���� �����Դϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_LAYERDUNGEON_FULL:		// ���̾� �� ���� ���� ���� �Ұ�
		strSysMessage = _S(1338, "���̾� ���� ���� ���� ���� �� �� �����ϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		break;

	case MSG_SYS_CANT_WARP_STATE:
		pUIManager->GetChattingUI()->AddSysMessage(_S(415, "�̵��� �� ���� �����Դϴ�."), SYSMSG_ERROR);
		pUIManager->GetChattingUI()->AddSysMessage(_S(340, "�̵��� ��ҵǾ����ϴ�."), SYSMSG_ERROR);
		pUIManager->SetCSFlagOff(CSF_TELEPORT);
		break;

	case MSG_SYS_CANT_WARP_OTHER:		// �ٸ� �̵� ��ġ ��������� �̵� ��ġ ��� �Ұ�
		pUIManager->GetChattingUI()->AddSysMessage(_S(334, "�ٸ� �̵� ��ġ�� ������Դϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_MEMPOS_OTHERZONE:		// �ٸ� �����δ� ��� ��� �̵� �Ұ�
	case MSG_SYS_MEMPOS_CASTLE:
		pUIManager->GetChattingUI()->AddSysMessage(_S(335, "�޸� ��ũ�ѷ� �̵��� �� �ִ� ������ �ƴմϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_SINGLEDUNGEON_FULL:	// �̱� ������ �� ������.
		strSysMessage = _S(1339, "�̱� ���� �ο� �ʰ��� ���� �� �� �����ϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		break;
		/*
				case MSG_SYS_SKILL_INVAL_STATE:		// ���� �Ҹ���			: flag(c: 0 - �׾������� ����, 1 - ���� ���ø� ����, 2 - �ɾƼ��� ����, 3 - �ǽ��� �Ұ���, 4 - ������ ����
					{
						SBYTE	sbErrType;
						(*istr) >> sbErrType;

						switch( sbErrType )
						{
							case 0:
								strSysMessage = _S( 390, "�׾��� ���� ��밡�� �մϴ�." );
								break;
							case 1:
								strSysMessage = _S( 391, "���⸦ �����ؾ� ��밡�� �մϴ�." );
								break;
							case 2:
								strSysMessage = _S( 392, "�ɾ����� ���� ��밡�� �մϴ�." );
								break;
							case 3:
								strSysMessage = _S( 393, "��ȭ�������� ��� �Ұ����մϴ�." );
								break;
							case 4:
								strSysMessage = _S( 394, "������ ���� ��밡�� �մϴ�." );
								break;
						}

						pUIManager->GetChattingUI()->AddSysMessage( strSysMessage, SYSMSG_ERROR );
					}
					break;
		*/
	case MSG_SYS_MAKE_REFINE_SHORT:		// ���ü� ���鶧 �� ������
		pUIManager->GetChattingUI()->AddSysMessage(_S(369, "���� ����� �����մϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_PRODUCE_NOTOOL:			// ���굵���� ����
		pUIManager->GetChattingUI()->AddSysMessage(_S(657, "���꿡 �ʿ��� ������ �����ϴ�."), SYSMSG_ERROR);
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->CancelProduct();
		break;
	case MSG_SYS_PRODUCE_WEAR_TOOL:		// ���굵���� �����Ͻÿ�
		pUIManager->GetChattingUI()->AddSysMessage(_S(658, "���� ������ �����Ͻÿ�."), SYSMSG_ERROR);
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->CancelProduct();
		break;
	case MSG_SYS_PRODUCE_MATCH_TOOL:		// �´� ���굵���� �����Ͻÿ�
		pUIManager->GetChattingUI()->AddSysMessage(_S(659, "�������� ���� ���� �����Դϴ�."), SYSMSG_ERROR);
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->CancelProduct();
		break;
	case MSG_SYS_PRODUCE_MAXUSE_TOOL:	// ���굵�� �� ����
		pUIManager->GetChattingUI()->AddSysMessage(_S(660, "���� ������ ���Ƽ� �ı��Ǿ����ϴ�."), SYSMSG_ERROR);
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->CancelProduct();
		break;
	case MSG_SYS_PRODUCE_MAX_ACCEPTABLE:	// ���� ���� �ο� �ʰ�
		pUIManager->GetChattingUI()->AddSysMessage(_S(661, "���� ���� �ο��� �ʰ��߽��ϴ�."), SYSMSG_ERROR);
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->CancelProduct();
		break;
	case MSG_SYS_PRODUCE_NO_SSKILL:			// �ش��ϴ� ���� ��ų�� ����!!
		pUIManager->GetChattingUI()->AddSysMessage(_S(662, "�ش��ϴ� ���� ��ų�� �����ϴ�."), SYSMSG_ERROR);
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->CancelProduct();
		break;
	case MSG_SYS_PROCESS_DOC_NOT_SSKILL:// �������� ���µ� ������ų�� ����
		pUIManager->GetChattingUI()->AddSysMessage(_S(663, "����ǰ�� �����ϱ� ���� ������ų�� �����ϴ�"), SYSMSG_ERROR);
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->CancelProduct();
		break;
	case MSG_SYS_BLOODITEM:
	{
		SLONG	itemindex;
		(*istr) >> itemindex;

		//CItemData &ItemData	= _pNetwork->GetItemData(itemindex);
		//CTString strSysMessage;
		strSysMessage.PrintF(_S(703, "%s�� �����ۿ� ������ �ɼ��� ����� �� �ֽ��ϴ�."), _pNetwork->GetItemName(itemindex));
		_pNetwork->ClientSystemMessage(strSysMessage, SYSMSG_ERROR);

		//pUIManager->GetChattingUI()->AddSysMessage( CTString(_S( 665, "������ �ɼ��� ����Ҽ� �ֽ��ϴ�." )) );		
		break;
	}
	case MSG_SYS_MAKE_REFINE_CANNOT:
		pUIManager->GetChattingUI()->AddSysMessage(_S(666, "�ش� �������� ���ü����� ��ȯ�� �� ���� �������Դϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_PKMODE_LIMITLEVEL:		// PK ������ �Ұ����� ����
		pUIManager->GetChattingUI()->AddSysMessage(_S(806, "15���� ���ϴ� PVP�� �� ���� �����ϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_CANTCHAT_INVISIBLE:		// [2012/02/03 : Sora] ITS 6649 �κ����� ���¿����� �Ϲ� ä�� �Ұ� �޽��� ó�� �߰�
		pUIManager->GetChattingUI()->AddSysMessage(_S(5666, "�Ϲ� ä���� �Ͻ� �� ���� �����Դϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_SHORT_FAME:
		pUIManager->GetChattingUI()->AddSysMessage(_S(1340, "����ġ�� �����մϴ�."), SYSMSG_ERROR);
		break;

	case MSG_SYS_FRIEND_NOTFOUND:
	{
		// ���� Ȱ��ȭ �Ǿ� �ִ� ���� â���� ���� �޼����� ������ 
		pUIManager->GetMessenger()->TalkErrorMessage(_S(2064, "��ȭ��밡 ���������̿��� �޼����� ������ �� �����ϴ�."));
	}
	break;
	//TEMP: �ʰ��� ���ü�
	case MSG_SYS_UPGRADE_CANT_SUPERSTONE:
	{
		strSysMessage = _S(1746, "�� ���� ���ü��� �̹� ����� ����Դϴ�. �ٸ� �����ۿ� ����� �ֽʽÿ�.");
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(1673, "���� �Ұ�!!!"), UMBS_OK, UI_SHOP, MSGCMD_SUPERGOJE_NOTIFY);
		MsgBoxInfo.AddString(strSysMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);

		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_PET_ITEM_UPGRADE);
	} break;
	case MSG_SYS_UPGRADE_CANT_14LEVEL:
	{
		strSysMessage = _S(1747, "�� ���� ���ü��� +14��񿡴� ����� �� �����ϴ�.");
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(1670, "����!!!"), UMBS_OK, UI_SHOP, MSGCMD_SUPERGOJE_NOTIFY);
		MsgBoxInfo.AddString(strSysMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);

		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_PET_ITEM_UPGRADE);
	} break;
	case MSG_SYS_CAN_RECEIVE_SUPERSTONE:
	{
		SLONG fame;
		(*istr) >> fame;
		strSysMessage.PrintF(_S(1749, "�����մϴ�.\n����ġ�� %d�� �Ǿ����ϴ�.\n���� ��ȭ�� �ڿ��� ����\n�� ���� ���ü��� ���޹��� ��\n�ֽ��ϴ�."), fame);
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(1748, "�ȳ�"), UMBS_OK, UI_SHOP, MSGCMD_SUPERGOJE_NOTIFY);
		MsgBoxInfo.AddString(strSysMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);
	} break;
	case MSG_SYS_FAME_NOT_ENOUGH:
	{
		strSysMessage = _S(1750, "����ġ�� �����Ͽ� �� ���� ���ü��� ���� ���� �� �����ϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	} break;
	case MSG_SYS_INVEN_NOT_ENOUGH:
	{
		strSysMessage = _S(1751, "������� �κ��丮�� ������� �����Ͽ� �� ���� ���ü��� ������ �� �����ϴ�. �κ��丮�� ��� �ֽʽÿ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	} break;
	case MSG_SYS_NO_MORE_SUPERSTONE:
	{
		strSysMessage = _S(1752, "�� ���� ���ü��� ��� ���� �޾� ���̻� ���� ���� �� �����ϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	} break;
	case MSG_SYS_APPEAR_NOVICE:
	{
		CTString strName;
		(*istr) >> strName;
		strSysMessage.PrintF(_S(1753, "�ű� ���� %s ���� ���� ���ӿ� �����߽��ϴ�. �İ��� ������ ���� ���� ���� ��Ź�帳�ϴ�."), strName.str_String);
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_NOTIFY);
	} break;
	case MSG_SYS_NOTICE:
	{
		LONG lIndex;
		(*istr) >> lIndex;

		Notice* pNotice = GAMEDATAMGR()->GetNotice();

		if (pNotice != NULL)
			pNotice->AddToNoticeList(2000 + lIndex, Notice::NOTICE_EVENT);

	} break;

	case MSG_SYS_PET_CANT_SUMMON:		// ��ȯ �Ұ��� ����
	{
		strSysMessage = _S(2130, "��ȯ�� �Ұ����� �����Դϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;

	case MSG_SYS_PET_CANT_MOUNT:		// ����Ʈ �Ұ��� ����
	{
		strSysMessage = _S(2065, "����Ʈ�� �Ұ����� �����Դϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		pUIManager->SetCSFlagOff(CSF_PETRIDING);	// [2011/03/21 : Sora] ����Ʈ ���н� Ǯ���� off
	}
	break;
	case MSG_SYS_PRODUCE_NO_MONEY:		// ����� ���� �Ұ�
	{
		strSysMessage = _S(2066, "������ �����Ͽ� ������ �Ұ����մϴ�. ");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_PRODUCE_CANNT_BOOST:	// �ν��ͷδ� ���� ���� �Ұ�
	{
		pUIManager->CancelSkill();
		pUIManager->CloseMessageBox(MSGCMD_BOOST_RANDON_PRODUCT_ERROR);
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->CancelProduct();
		strSysMessage = _S(2067, "�ν��͸� ������ ���δ� ���� ���길 �����մϴ�.");

		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(2068, "����"), UMBS_OK, NULL, MSGCMD_BOOST_RANDON_PRODUCT_ERROR);
		MsgBoxInfo.AddString(strSysMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);

	}
	break;
	case MSG_SYS_CANNOT_DUPLICATION:	// �ν��ͷδ� ���� ���� �Ұ�
	{
		SLONG	nNewItmeIndex;
		SLONG	nCurItemIndex;

		(*istr) >> nNewItmeIndex;
		(*istr) >> nCurItemIndex;

		CTString strNewItmeName;
		CTString strCurItmeName;


		strNewItmeName = _pNetwork->GetItemName(nNewItmeIndex);
		strCurItmeName = _pNetwork->GetItemName(nCurItemIndex);

		if (nNewItmeIndex == nCurItemIndex)
		{
			strSysMessage.PrintF(_S2(2069, strNewItmeName, "%s<��> �ߺ��Ͽ� ����� �� �����ϴ�."), strNewItmeName);
		}
		else
		{
			strSysMessage.PrintF(_S3(2070, strNewItmeName, strCurItmeName, "%s<��> %s<��> �ߺ��Ͽ� ����� �� �����ϴ�."), strNewItmeName, strCurItmeName);
		}
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_UPGRADE_CANT_6LEVEL_LUCKY:	// ����� ���¼� ���� ���� wooss 051010
	{
		strSysMessage = _S(2151, "����� ���ü��� ����� �� �����ϴ�.");
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(1673, "���� �Ұ�!!!"), UMBS_OK, UI_SHOP, MSGCMD_SUPERGOJE_NOTIFY);
		MsgBoxInfo.AddString(strSysMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);

		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_PET_ITEM_UPGRADE);
	}
	break;

	case MSG_SYS_TARGET_PKLIMITLEVEL:
	{
		pUIManager->LostTarget();

		strSysMessage = _S(2231, "15���� ������ �ɸ��ʹ� ������ �� �����ϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_NOT_ADULT:
	{
		ULONG remTime;
		(*istr) >> remTime;
		CTString strSysMessage;
		strSysMessage.PrintF(_S(2261, "%d���Ŀ� ������ ����ϴ�. ���� ���� 6�� ���Ŀ� ���Ӱ����մϴ�."), remTime);
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;

	case MSG_SYS_NOTTIME_GOZONE:
	{
		CTString strSysMessage = _S(2279, "�̵� ������ �ð��� �ƴմϴ�."); // wooss 051212 ���� 
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;

	case MSG_SYS_CANNOT_WEAR_DEADPET:
	{
		// MSG_SYS_CANNOT_WEAR_DEADPET,	// 060221 : bs : ����� �� ���� �Ұ� : petindex(n) remainRebirth(n)
		SLONG	remainRebirth;
		SLONG	lPetIndex;
		(*istr) >> lPetIndex;
		(*istr) >> remainRebirth;
		CTString strSysMessage;
		strSysMessage.PrintF(_S(2508, "�� �������� �ð��� %d�ð� %d�� ���ҽ��ϴ�."), remainRebirth / 3600, (remainRebirth % 3600) / 60);
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;

	case MSG_SYS_ITEMCOMPOSITED:			// ������ �ռ� ����
	{
		CTString strSysMessage = _S(2730, "������ �ռ��� �����Ͽ����ϴ�."); // wooss 051212 ���� 
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		pUIManager->GetMixNew()->CloseMixNew();
	}
	break;

	case MSG_SYS_EXPIRE_ITEMCOMPOSITE:		// ������ �ռ� ���� : itemdbindex(n)
	{
		CTString strSysMessage;
		LONG tv_idx;
		(*istr) >> tv_idx;

		strSysMessage.PrintF(_S(3041, "[%s]������ �ռ� ����� ���� �Ǿ����ϴ�."),
			CItemData::getData(tv_idx)->GetName()); // wooss 051212 ���� ")
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		pUIManager->GetMixNew()->CloseMixNew();
	}
	break;
	case MSG_SYS_CANNOT_RESET_MOUNT:	// �� ����Ʈ Ÿ�� ��� �Ұ�
	{
		CTString strSysMessage = _S(2900, "���� ����Ʈ �Ʒ��� ��� �� �� �����ϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_RESET_MOUNT:	// �� ����Ʈ Ÿ�� ���
	{
		CTString strSysMessage = _S(2901, "�ֿϵ����� ���� ��ȯ�� �Ϸ� �Ǿ����ϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);

		pUIManager->CloseMessageBox(MSGCMD_PET_MOUNT_CANCEL_CARD);
	}
	break;
	case MSG_SYS_CANNOT_SEPARATE_ITEM:
	{
		CTString strSysMessage = _S(2934, "�ɷ�ġ�� ���յ� ���� ��� �����۸� ���� ������ �����մϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		pUIManager->GetMixNew()->CloseMixNew();
	}
	break;
	case MSG_SYS_SEPARATE_ITEM:
	{
		LONG tv_idx;
		(*istr) >> tv_idx;
		CTString strSysMessage;
		strSysMessage.PrintF(_S(2935, "���յ� ���[%s] �и��� �����Ͽ����ϴ�."), _pNetwork->GetItemName(tv_idx));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		pUIManager->GetMixNew()->CloseMixNew();
	}
	break;

	case MSG_SYS_RAIDMOB_REGEN:
	{
		LONG tv_idx;
		(*istr) >> tv_idx;

		CTString strNoticeMsg;
		strNoticeMsg.PrintF("[ %s %s ]", CMobData::getData(tv_idx)->GetName(), _S(3158, "���Ͱ� �����Ͽ����ϴ�."));

		_UIAutoHelp->SetGMNotice(strNoticeMsg, 0xFF5014FF);

	}
	break;
	case MSG_SYS_TIMEOUT_LUCKY_ACCESSORY:
	{
		LONG tv_idx;
		(*istr) >> tv_idx;
		CTString strSysMessage;
		strSysMessage.PrintF(_S(3188, "%s�� ���Ⱓ�� ����Ǿ� �������� ������ϴ�."), _pNetwork->GetItemName(tv_idx));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		pUIManager->GetMixNew()->CloseMixNew();
	}
	break;
	case MSG_SYS_CHANGE_LUCKY_BOX:
	{
		/***
		LONG tv_idx;
		(*istr) >> tv_idx;
		CTString strSysMessage;
		strSysMessage.PrintF( _S(3187, "��Ű��ο���ڿ��� %s �������� ���Խ��ϴ�."), _pNetwork->GetItemName(tv_idx));
		pUIManager->GetChattingUI()->AddSysMessage( strSysMessage, SYSMSG_ERROR );
		pUIManager->GetMixNew()->CloseMixNew();
		***/
		LONG iReward, iUsedItem;

		(*istr) >> iReward;
		(*istr) >> iUsedItem;

		CTString strSysMessage;

		if (iReward == 0)
		{
			strSysMessage.PrintF(_s("���̸��� �޴��� ȹ���Ͽ����ϴ�"));
		}
		else
		{
			if (iUsedItem == 0 || iUsedItem == 2037 || iUsedItem == 2597)
				strSysMessage.PrintF(_S(3187, "��Ű��ο���ڿ��� %s �������� ���Խ��ϴ�."), _pNetwork->GetItemName(iReward));
			else
				strSysMessage.PrintF(_S(4198, "%s���� %s �������� ���Խ��ϴ�."), _pNetwork->GetItemName(iUsedItem), _pNetwork->GetItemName(iReward));
		}

		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);

		pUIManager->GetMixNew()->CloseMixNew();
	}
	break;
	case MSG_SYS_CANNOT_HAVE_DUPLICATE:
	{
		CTString strSysMessage = _S(3218, "�ߺ��ؼ� ������ �� ���� ������ �Դϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	// wooss 070307----------------------------------------------------------------->>
	// kw : WSS_WHITEDAY_2007
	case MSG_SYS_MATCHSEX:
	{
		CTString strSysMessage = _S(3256, "������ ���� �ʽ��ϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	// -----------------------------------------------------------------------------<<
	case MSG_SYS_NO_AUTO_ITEM:
	{
		CTString strSysMessage = _S(3666, "�� �̻� ����� ������ �����ϴ�.");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;

	case MSG_SYS_EGEHA_MINLEVEL:
	{
		CTString strSysMessage = _S(2712, "���� ���� ������ �������� ���մϴ�");
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);

	}
	break;
	case MSG_SYS_IRISPOINT_ALARM:
	{
		ULONG iCnt;
		(*istr) >> iCnt;

		strSysMessage.PrintF(_S(4400, "���̸��� �޴��� %d �� ȹ���Ͽ����ϴ�."), iCnt);
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_CHANGE_RAID_BOX:	// [sora] ���̵� ���� ����
	{
		LONG iReward, iUsedItem;
		CTString strSysMessage;

		(*istr) >> iReward;
		(*istr) >> iUsedItem;

		if (iReward >= 0)
		{
			strSysMessage.PrintF(_S(4198, "%s���� %s �������� ���Խ��ϴ�."), _pNetwork->GetItemName(iUsedItem), _pNetwork->GetItemName(iReward));
		}
		else	// iReward == -1�̸� �����
		{
			strSysMessage = _S(4662, "���ھȿ��� �ƹ��͵� ������� �ʾҽ��ϴ�.");
		}

		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_FACTORY_EXP:
	{
		SQUAD lExp;
		(*istr) >> lExp;

		CTString strExp;
		strExp.PrintF("%I64d", lExp);
		pUIManager->InsertCommaToString(strExp);

		strSysMessage.PrintF(_S(4663, "���õ��� %s ����Ͽ����ϴ�."), strExp);
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_NOTIFY);
	}break;
	case MSG_SYS_CANNOT_DESTROY:
	{
		strSysMessage.PrintF(_S(4696, "�ı��� �Ұ����� �������Դϴ�."));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}break;
	case MSG_SYS_TITLE_EXPIRED:
	{
		INDEX iCount, iIndex, iItemIndex;

		(*istr) >> iCount;

		for (int i = 0; i < iCount; ++i)
		{
			(*istr) >> iIndex;
			//  [3/25/2010 kiny8216] ȣĪ �̸��� ������ lod���� �ҷ������� ����
			iItemIndex = TitleStaticData::getData(iIndex)->GetItemIndex();
			strSysMessage.PrintF(_S(4838, "%s ȣĪ�� �Ⱓ�� ���� �Ǿ����ϴ�."), pUIManager->GetNickName()->GetName(iItemIndex));
			pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_NOTIFY);
		}
	}break;
	case MSG_SYS_IRISPOINT_DROPMEDAL:
	{
		strSysMessage.PrintF(_s("1�ð��� ����Ǿ� ���̸��� �޴��� ����˴ϴ�."));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_CANNOT_GOZONE_LEVEL:
	{
		strSysMessage.PrintF(_S(4850, "������ ���� �ʾ� �̵��� �Ұ����մϴ�."));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		pUIManager->SetCSFlagOff(CSF_TELEPORT);
	}break;
	case MSG_SYS_COSTUME2_ITEM_EXPIRED:
	{
		INDEX costume2_index;
		(*istr) >> costume2_index;
		strSysMessage.PrintF(_S(3188, "%s�� ���Ⱓ�� ����Ǿ� �������� ������ϴ�."), _pNetwork->GetItemName(costume2_index));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_TRANSLATE_START:		// �꺯�Ž���
	{
		strSysMessage.PrintF(_S(5210, "��� �� �����մϴ�."));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}break;
	case MSG_SYS_CANT_MOUNT_EVOCATION: // ���� �� ����Ʈ �Ұ���
	{
		strSysMessage.PrintF(_S(2580, "�������϶��� �ֿϵ����� Ż �� �����ϴ�."));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		pUIManager->SetCSFlagOff(CSF_PETRIDING);
	}
	break;
	case MSG_SYS_CANT_MAKE_PET_EVOCATION: // ������ �� Ż�� ����� ����
	{
		strSysMessage.PrintF(_S(5179, "���� �߿��� �̿��� �� �����ϴ�."));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_FULL_INVENTORY_AND_DROP:
	{
		pUIManager->CloseMessageBox(MSGCMD_NULL);

		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(_S(5367, "�κ��丮�� �����Ͽ� �������� �ٴڿ� �������ϴ�. "));
		MsgBoxInfo.AddString(_S(5368, "�κ��丮�� ��� �� ���� �Ͻñ� �ٶ��ϴ�."));
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	break;
	case MSG_SYS_ENTER_RAID_ZONE_REMAIN:
	{
		SLONG remainTime;

		(*istr) >> remainTime;

		strSysMessage.PrintF(_S(5369, "%d�� �� ���̵� ������ �ʱ�ȭ �˴ϴ�."), remainTime);
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_RAID_RESET_COMPLETE:
	{
		strSysMessage.PrintF(_S(5370, "���̵� ���� �ʱ�ȭ�� �Ϸ�Ǿ����ϴ�."));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_NO_ENTER_RAID_ZONE:
	{
		strSysMessage.PrintF(_S(5371, "���̵� ���� �ʱ�ȭ ���Դϴ�."));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_GMCOMMAND_NOTICE:
	{
		UBYTE		ubSubType;
		CTString	strMessage;
		CTString	strGM, strUser;
		(*istr) >> ubSubType
			>> strGM
			>> strUser;
		switch (ubSubType)
		{
		case MSG_GM_COMMAND_NOTICE_KICK:
			strMessage.PrintF(_S(5447, "%s ���� %s ������ ���ӿ��� �߹��Ͽ����ϴ�."), strGM, strUser);
			_UIAutoHelp->SetGMNotice(strMessage);
			break;

		case MSG_GM_COMMAND_NOTICE_SILENCE:
			strMessage.PrintF(_S(5448, "%s ���� %s ������ ä�ñ��� �Ͽ����ϴ�."), strGM, strUser);
			_UIAutoHelp->SetGMNotice(strMessage);
			break;

		default: break;
		}
	}
	break;
	// BUG FIX : LC-MX-20110506-001 [5/18/2011 rumist]
	case MSG_SYS_PET_CANT_MOUNT_ETC:
	{
		pUIManager->SetCSFlagOff(CSF_PETRIDING);
		pUIManager->GetChattingUI()->AddSysMessage(_S(5489, "���� ž���� �� �����ϴ�."), SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_DUP_PREFINE_COMPOSITE:
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(5668, "�÷�Ƽ�� ���ü��� �����ֹ����� �ߺ��Ͽ� ��� �Ͻ� �� �����ϴ�."), SYSMSG_ERROR);
		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_PET_ITEM_UPGRADE);
	}
	break;
	// ��������� NPC��Ż ��ũ�� ������ ���Ⱓ ���� [8/22/2012 Ranma] NEW_NPC_PORTAL_SCROLL_ABS
	case MSG_SYS_NPC_PORTAL_EXPIRED:
	{
		CTString strName, strmassage;
		INDEX nItem_Index;
		strName = _pNetwork->MyCharacterInfo.GetPlayerName();

		(*istr) >> nItem_Index;

		strmassage.PrintF(_S(4213, "%s �� %s �������� �Ⱓ ����� ������ϴ�."), strName, _pNetwork->GetItemName(nItem_Index));
		pUIManager->GetChattingUI()->AddSysMessage(strmassage, SYSMSG_NORMAL);
	}
	break;
	case MSG_SYS_NOT_ENOUGH_MONEY:
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(5902, "���� ������ �ִ� ���� ���� ���� ������ ��ȯ �� �� �����ϴ�."), SYSMSG_ERROR);
	}
	break;
	case MSG_SYS_DO_NOT_ATTACK_IMMOTAL:
		pUIManager->GetChattingUI()->AddSysMessage(
			_S(6080, "����� �鿪 �����Դϴ�. ���� �� �� �����ϴ�."),
			SYSMSG_ERROR);
		break;
	case MSG_SYS_DO_NOT_ATTACK_DO_MOVE:
		pUIManager->GetChattingUI()->AddSysMessage(
			_S(6079, "���� ��忡���� ���� �� ��ų ����� �Ұ����մϴ�. ���� ���� ���� ��ȯ�Ͻ÷��� ĳ���͸� �����̼���."),
			SYSMSG_ERROR);
		break;
	case MSG_SYS_DO_NOT_CHANGE_PK_MODE:
		pUIManager->GetChattingUI()->AddSysMessage(_S(5596, "���� ���������� PVP���� ��Ȱ�� �� �����ϴ�."), SYSMSG_ERROR);
		break;

#ifdef DAILY_LOGIN
	case MSG_SYS_REZA:
	{
		CTString MSG;
		int colortype = 0;
		int chatbox = 0;
		(*istr) >> MSG;
		(*istr) >> colortype;
		(*istr) >> chatbox;


		strSysMessage.PrintF("%s", MSG);
		if (chatbox == 1)
		{
			pUIManager->GetChattingUI()->AddChatMessage(CHATMSG_ADMIN, -1, CTString("Server"), strSysMessage);
		}
		else
		{
			pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, colortype);
		}
	}
	break;
#endif
	case MSG_SYS_DO_NOT_SYSTEM_NOT_EQ_RVRTYPE:
		pUIManager->GetChattingUI()->AddSysMessage(_S(6090, "���� �������� ���� ������ ��� ����� �� ���� ����Դϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_DO_NOT_PARTY_THISZONE:
		pUIManager->GetChattingUI()->AddSysMessage(_S(6112, "���� ������ �����Ͽ� ��Ƽ �� �����뿡�� Ż�� �Ǿ����ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_DO_NOT_USE_DURING_IMMORTAL:
		pUIManager->GetChattingUI()->AddSysMessage(_S(6286, "���� ������ �����Ͽ� ����� �� �����ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_DO_NOT_USE_ITEM_STATE:
		pUIManager->GetChattingUI()->AddSysMessage(_S(5312, "�������� ����� �� �����ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_DO_NOT_GO_ZONE_GMORDER:
		pUIManager->GetChattingUI()->AddSysMessage(_S(384, "�̵��� �� �����ϴ�."), SYSMSG_ERROR);
		pUIManager->SetCSFlagOff(CSF_TELEPORT);
		break;
	case MSG_SYS_DO_NOT_PLAY_PVP:		// PVP�� �� �� ���� �����Դϴ�.
		pUIManager->GetChattingUI()->AddSysMessage(_S(6347, "PVP�� �� �� ���� �����Դϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_DO_NOT_ATTACK_PROTECT_PVP: // PVP��ȣ �����̹Ƿ� ������ �� �����ϴ�.
		pUIManager->GetChattingUI()->AddSysMessage(_S(6349, "PVP��ȣ �����̹Ƿ� ������ �� �����ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_PVP_PROTECT_ITEM_END:	// PVP��ȣ ������ ���Ⱓ�� ����Ǿ� PVP�� ������ ���°� �Ǿ����ϴ�.
		pUIManager->GetChattingUI()->AddSysMessage(_S(6350, "PVP��ȣ ������ ���Ⱓ�� ����Ǿ� PVP�� ������ ���°� �Ǿ����ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_AREADY_USE: //	�̹� ����� �Դϴ�.
		pUIManager->GetChattingUI()->AddSysMessage(_S(556, "�̹� ������� ������ �Դϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_WAR_BUF_NOT_IN_ZONE: // ���� ������ ��� ���� ȿ���� ������ϴ�.
		pUIManager->GetChattingUI()->AddSysMessage(_S(6421, "���� ������ ����� ���� ȿ���� ������ϴ�. �ٽ� ���� �������� �̵� �� ��� ���� ȿ���� ���������� ���� �˴ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_WAR_BUF_END_WAR: // ���� �ð��� ����Ǿ� ���� ȿ���� �����
		pUIManager->GetChattingUI()->AddSysMessage(_S(6420, "���� �ð��� ���� �Ǿ� ���� ȿ���� ������ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_ARTIFACT_DONT_IN_DUNGEON: //���� �������� ������ ���·� ������ ���� �� �� �����ϴ�.
		pUIManager->SetCSFlagOff(CSF_TELEPORT);
		pUIManager->GetItemCompose()->ShowErrorPopup(eCOMPOSE_POPUP_DONT_IN_DUNGEON);
		break;
	case MSG_SYS_ARTIFACT_PVP_GET_ITEM:	// PVP�� �Ұ����� ĳ���ʹ� ���� �������� ȹ�� �� �� �����ϴ�.
		pUIManager->GetItemCompose()->ShowErrorPopup(eCOMPOSE_POPUP_HAVE_NOT_RELIC);
		break;
	case MSG_SYS_ARTIFACT_ITEM_DELETE_EVENT_OFF:
		pUIManager->GetChattingUI()->AddSysMessage(_S(6443, "���� ��ɲ� �̺�Ʈ�� ����Ǿ� ��� ���� �������� ������ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_ARTIFACT_ITEM_DO_NOT_USE_PVPPROTECT:
		pUIManager->GetChattingUI()->AddSysMessage(_S(6447, "���� �������� ������ �ִ� ���¿����� PVP��ȣ���и� ����� �� �����ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_ARTIFACT_USE_PVPPROTECT:
		pUIManager->GetChattingUI()->AddSysMessage(_S(6448, "PVP��ȣ���и� ��� �� �Դϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_SUMMON_TOTEM_NPC: // ���� �������� ��ȯ �Ǿ���.
		pUIManager->GetChattingUI()->AddSysMessage(_S(6426, "������ ��ȯ �Ǿ����ϴ�. ���۰� ���� �Ÿ� �̻� ����ų� HP �� ���� �ð��� 0�� �Ǹ� ������ ������� �˴ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_NOT_CONDITION_ITEM_ALL_USER:
		pUIManager->GetChattingUI()->AddSysMessage(_S(6446, "�������� ȹ���� �� �ִ� ������ �����ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_BELONG_ITEM:
		pUIManager->GetChattingUI()->AddSysMessage(_S(6453, "�������� ĳ���Ϳ� �ͼӵǾ����Ƿ� �̵��� �� �����ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_BOSS_REGEN:
	{
		CTString strError = "";
		CTString name;
		CTString zone;
		INDEX posX;
		INDEX posZ;
		(*istr) >> name;
		(*istr) >> zone;
		(*istr) >> posX;
		(*istr) >> posZ;
		CTString msg;
		strError.PrintF(_S(8417, "The BOSS %s has spawned in %s at position (%d, %d)"), name, zone, posX, posZ);
		pUIManager->GetChattingUI()->AddSysMessage(msg, SYSMSG_RED, DEF_UI_COLOR_ORANGE);
		
	}
	break;
	case MSG_SYS_BOSS_DEAD:
	{
		CTString of;
		CTString df;
		INDEX hour;
		INDEX min;
		INDEX sec;
		(*istr) >> of;
		(*istr) >> df;
		(*istr) >> hour;
		(*istr) >> min;
		(*istr) >> sec;
		CTString msg;
		msg.PrintF(_S(8415, "The player %s killed the boss: %s - Time %d:%d:%d"), of, df, hour, min, sec);
		pUIManager->GetChattingUI()->AddSysMessage(msg, SYSMSG_RED, DEF_UI_COLOR_ORANGE);
	}
	break;
	case MSG_SYS_PLAYER_DEAD:  //pwesty arena dumb shit msg 8414
	{
		CTString of;
		CTString df;
		(*istr) >> of;
		(*istr) >> df;
		CTString msg;
		msg.PrintF(_S(8414, "The player %s killed the enemy %s"), of, df);
		pUIManager->GetChattingUI()->AddSysMessage(msg, SYSMSG_RED, DEF_UI_COLOR_ORANGE);
	}
	break;
	case MSG_SYS_EVENT_SUMMON_NPC_DEAD:
	{
		CTString of;
		int total;
		(*istr) >> of;
		(*istr) >> total;
		CTString msg;
		msg.PrintF(_S(8418, "%s found one, %d left!"), of, total);
		pUIManager->GetChattingUI()->AddSysMessage(msg, SYSMSG_RED, DEF_UI_COLOR_ORANGE);
	}
	break;
	case MSG_SYS_NOT_ENCHANTED_FOREST:
		pUIManager->GetChattingUI()->AddSysMessage(_S(8521, "�������� ĳ���Ϳ� �ͼӵǾ����Ƿ� �̵��� �� �����ϴ�."), SYSMSG_ERROR);
		break;
	case MSG_SYS_FLAG_PICKUP:
	{
		CTString of;
		INDEX posX;
		INDEX posZ;
		(*istr) >> of;
		(*istr) >> posX;
		(*istr) >> posZ;
		CTString msg;
		msg.PrintF(_S(8525, "%s Captured the Lets Play Flag at position , (%d, %d). Kil him now!"), of, posX, posZ);
		pUIManager->GetChattingUI()->AddSysMessage(msg, SYSMSG_RED, DEF_UI_COLOR_ORANGE);
	}
	break;
	case MSG_SYS_FLAG_DEAD:
	{
		CTString df;
		INDEX posX;
		INDEX posZ;
		(*istr) >> df;
		(*istr) >> posX;
		(*istr) >> posZ;
		CTString msg;
		msg.PrintF(_S(8526, "The Lets Play Flag Carrier %s was killed at position (%d, %d). Capture the flag!"), df, posX, posZ);
		pUIManager->GetChattingUI()->AddSysMessage(msg, SYSMSG_RED, DEF_UI_COLOR_ORANGE);
	}
	break;
	case MSG_SYS_FLAG_DC:
	{
		CTString df;
		INDEX posX;
		INDEX posZ;
		(*istr) >> df;
		(*istr) >> posX;
		(*istr) >> posZ;
		CTString msg;
		msg.PrintF(_S(8528, "The Lets Play Flag Carrier %s has logged out at position (%d, %d). Capture the flag!"), df, posX, posZ);
		pUIManager->GetChattingUI()->AddSysMessage(msg, SYSMSG_RED, DEF_UI_COLOR_ORANGE);
	}
	break;


	case MSG_CASH_ZONE_FAG:
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(9425, "������ �����մϴ�."), SYSMSG_ERROR);
		pUIManager->SetCSFlagOff(CSF_TELEPORT);

	}
	break;
	case MSG_SYS_CANNOT_USE_LETSPLAY_RUNE:
		pUIManager->GetChattingUI()->AddSysMessage(_s("shit dont work"), SYSMSG_ERROR);
		break;
	case MSG_SYS_PROMO_KEY_INVALID:
		strSysMessage.PrintF(_s("Promo key is invalid."));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		break;
	case MSG_SYS_PROMO_KEY_EXPIRED:
		strSysMessage.PrintF(_s("Promo key is expired"));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		break;
	case MSG_SYS_PROMO_KEY_ALREADY_USE:
		strSysMessage.PrintF(_s("Promo key is already used"));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
		break;
	case MSG_SYS_PROMO_KEY_ADDED_TO_INVENTORY:
		strSysMessage.PrintF(_s("Promo key has been used. Gift added to inventory"));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_NOTIFY);
		break;
	case MSG_SYS_PROMO_KEY_ADDED_TO_STASH:
		strSysMessage.PrintF(_s("Promo key has been used. Gift added to stash"));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_NOTIFY);
		break;
	case MSG_SYS_DONATION_MAIL_REWARD:
		strSysMessage.PrintF(_s("[Donation reward] You received a gift in the mail"));
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_NOTIFY);
		break;
	default:
	{
		strSysMessage = "Undefined Message..";
		pUIManager->GetChattingUI()->AddSysMessage(strSysMessage, SYSMSG_ERROR);
	}
	break;
	}

}

void CSessionState::ReceiveRebirthMessage(CNetworkMessage* istr)
{
	/*
		SLONG  cha_index
		SWORD  hp,maxHp,mp,maxMp;

		(*istr) >> cha_index;
		(*istr) >> hp;
		(*istr) >> maxHp;
		(*istr) >> mp;
		(*istr) >> maxMp;

		if(cha_index == _pNetwork->MyCharacterInfo.index)
		{
			_pNetwork->MyCharacterInfo.hp = hp;
			_pNetwork->MyCharacterInfo.maxHP = maxHP;
			_pNetwork->MyCharacterInfo.mp = mp;
			_pNetwork->MyCharacterInfo.maxMP = maxMP;
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->Rebirth();
			return;
		}
	*/
	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->Read_net_Character(MSG_PC_REBIRTH, 0, &(*istr));

}


void CSessionState::ReceiveEffectMessage(CNetworkMessage* istr)
{
	//COMMON
	SBYTE	sbType;
	//SKILL
	SLONG	slSkillId;
	SBYTE	sbTargetType;
	SLONG	slTargetId;
	//ETC
	SBYTE	sbEtcType;
	SBYTE	sbChaType;
	SLONG	slChaIndex;

	(*istr) >> sbType;

	switch (sbType)
	{
	case MSG_EFFECT_SKILL:
	{
		(*istr) >> slSkillId;
		(*istr) >> sbTargetType;
		(*istr) >> slTargetId;

		INDEX	iWeapon = 0;
		CEntity* penTarget = NULL;
		if (sbTargetType == MSG_CHAR_PC)
		{
			if (_pNetwork->MyCharacterInfo.index == slTargetId)	//�� ĳ���̸�
			{
				penTarget = CEntity::GetPlayerEntity(0);
				iWeapon = _pNetwork->MyCharacterInfo.bExtension;
			}
			else													//�� ĳ���� �ƴϸ�
			{
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, slTargetId);

				if (pObject != NULL)
				{
					CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

					penTarget = pTarget->GetEntity();
					iWeapon = pTarget->cha_bExtension;
				}
			}

			CSkill& skill = _pNetwork->GetSkillData(slSkillId);
			INDEX iTempAnim = _pNetwork->MyCharacterInfo.bExtension;
			INDEX iSkillAni1 = skill.idPlayer_Anim_Skill[iTempAnim][0];
			INDEX iSkillAni2 = skill.idPlayer_Anim_Skill[iTempAnim][2];

			if (slSkillId == 33	//Hardcording, ��Ƽ����, ��ƼŬ ����Ʈ�� �� �ȳ��� ��� INDEX�� �ǽ��� ��.
				|| (slSkillId == 114 && skill.GetMissileType(0) == 21)//Hardcoding, baal skill 1
				|| slSkillId == 115 //Hardcoding, baal skill 2
				|| slSkillId == 149 //Hardcoding, death knight skill 1
				|| slSkillId == 150 //Hardcoding, death knight skill 2
				|| slSkillId == 169 //Hardcoding, knight telekinesis
				|| slSkillId == 226 //Hardcoding, mage flame storm
				|| skill.GetTargetType() == CSkill::STT_PARTY_ALL // ��Ƽ�� �鿡�� �� ȿ��
				|| skill.GetTargetType() == CSkill::STT_GUILD_ALL // ���� �鿡�� �� ȿ��
				|| (skill.GetFlag() & SF_GUILD && iSkillAni1 == -1 && iSkillAni2 == -1) // �ִϸ��̼��� ���� ��� ��ų
				|| (skill.GetFlag() & SF_SUMMON_NPC)
				)
			{
				PCStartEffectGroup(skill.GetFireEffect3(iWeapon), slTargetId, penTarget);
			}
		}
		// Date : 2005-10-28(���� 1:42:53), By Lee Ki-hwan
		// ���Ͱ� ���Ϳ��� ����Ʈ�� ����Ҷ��� ����ó����
		// Ÿ�� ����Ʈ ó�� ��
		else if (sbTargetType == MSG_CHAR_NPC)
		{
			if (slSkillId == 289 || slSkillId == 290 || _pNetwork->GetSkillData(slSkillId).GetFlag() & SF_GUILD || _pNetwork->GetSkillData(slSkillId).GetFlag() & SF_SUMMON_NPC)
			{
				CPrintF("Target = NPC, Skill ID : %d, TargetID: %d\n", slSkillId, slTargetId);

				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_MOB, slTargetId);

				if (pObject != NULL)
				{
					penTarget = pObject->GetEntity();
					iWeapon = 0;
				}

				CSkill& skill = _pNetwork->GetSkillData(slSkillId);
				PCStartEffectGroup(skill.GetFireEffect3(iWeapon), slTargetId, penTarget);
			}
		}
	} break;
	case MSG_EFFECT_ETC:
	{
		(*istr) >> sbChaType;
		(*istr) >> slChaIndex;
		(*istr) >> sbEtcType;

		CPrintF("ChaType:%d, slChaIndex:%d, sbEtcType:%d\n", sbChaType, slChaIndex, sbEtcType);

		switch (sbEtcType)
		{
		case MSG_EFFECT_ETC_LEVELUP: // ������
		{
			if (sbChaType != MSG_CHAR_PC) break;	//���� ���� �������� ����.

			PCStartEffectGroup("LevelUp", slChaIndex);		//Hardcording

			_UIAutoHelp->SetInfo(AU_LEVEL_UP);
			//	_UIAutoHelp->SetInfo ( AU_LEVEL_UP_QUEST2 );
			_UIAutoHelp->SetInfo(AU_LEVEL_UP_QUEST8);
			_UIAutoHelp->SetInfo(AU_LEVEL_UP_QUEST9);
			_UIAutoHelp->SetInfo(AU_LEVEL_UP_QUEST10);
			_UIAutoHelp->SetInfo(AU_LEVEL_UP_QUEST16);
			_UIAutoHelp->SetInfo(AU_LEVEL_UP_QUEST24);
		}
		break;
		case MSG_EFFECT_ETC_GOZONE: // GO_World
		{
			if (sbChaType != MSG_CHAR_PC) break;	//���� ���� ���̵��� ����.

			PCStartEffectGroup("Teleport End", slChaIndex);		//Hardcording
		}
		break;
		case MSG_EFFECT_ETC_PRODUCE_MINING:
		case MSG_EFFECT_ETC_PRODUCE_GATHERING:
		case MSG_EFFECT_ETC_PRODUCE_CHARGE:
		case MSG_EFFECT_ETC_ITEM_PROCESS:
		case MSG_EFFECT_ETC_ITEM_MAKE:
		{
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->PlayItemEffect(-1, sbEtcType);
		}
		break;
		case MSG_EFFECT_ETC_HP_STEEL: // HP ��ƿ ���� ����Ʈ
		{
			if (sbChaType != MSG_CHAR_PC) break;

			PCStartEffectGroup("HP_STEAL", slChaIndex);
		}
		break;
		case MSG_EFFECT_ETC_MP_STEEL: // MP ��ƿ ���� ����Ʈ
		{
			if (sbChaType != MSG_CHAR_PC) break;

			PCStartEffectGroup("MP_STEAL", slChaIndex);
		}
		break;
		case MSG_EFFECT_ETC_FIRECRACKER: // ���� �������� ������� �� ������ ����Ʈ // [070824: Su-won] ITEM_FIRECRACKER
		{
			if (sbChaType != MSG_CHAR_PC) break;

			PCStartEffectGroup("squid", slChaIndex);
		}
		break;
		case MGS_EFFECT_ETC_COMPETITION:
		{
			if (sbChaType != MSG_CHAR_PC) break;
			PCStartEffectGroup("STATE_UP", slChaIndex);
		}
		break;
		case MSG_EFFECT_ETC_RANDOM_EXP: // ���� ����ġ ���� 
		{
			PCStartEffectGroup("EXP_UP", slChaIndex);
		}
		break;
		case MSG_EFFECT_ETC_RANDOM_SP: // ���� SP ����
		{
			PCStartEffectGroup("SP_UP", slChaIndex);
		}
		break;
		case MSG_EFFECT_ETC_RANDOM_DROP: // ���� ����� ����
		{
			PCStartEffectGroup("DROP_UP", slChaIndex);
		}
		break;
		case MSG_EFFECT_FLAG_KILL_TARGET:
		{
			PCStartEffectGroup("QMARK_CAN_PRIZE", slChaIndex);
		}
		break;
		}
	} break;
	case MSG_EFFECT_PRODUCE:		// ���� ����Ʈ
	{

		SLONG	targetindex;
		SLONG	targethp;
		SBYTE	targettype;
		(*istr) >> sbEtcType;
		(*istr) >> sbChaType;
		(*istr) >> slChaIndex;
		(*istr) >> targettype;
		(*istr) >> targetindex;
		(*istr) >> targethp;

		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetProduct(slChaIndex, sbEtcType);
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ProcessProduce(sbChaType, slChaIndex, targettype, targetindex, targethp);
	}
	// FIXME : ���� ����Ʈ�� �ϴ��� ����������...
	//PCStartEffectGroup("LevelUp", slChaIndex);		//Hardcording
	break;

	case MSG_EFFECT_ITEM:
	{
		SLONG	slItemIndex;
		(*istr) >> sbChaType;
		(*istr) >> slChaIndex;
		(*istr) >> slItemIndex;

		if (sbChaType != MSG_CHAR_PC)
			break;
		if (slItemIndex == -1)
			break;

		CItemData* pItemData = _pNetwork->GetItemData(slItemIndex);

#define INDEX_INVISIBLE_CURE		677
#define INDEX_STONE_CURE			873
#define INDEX_BLIND_CURE			874
#define INDEX_SILENT_CURE			875	
#define INDEX_RECOMMEND_EVENT		1393	

		switch (slItemIndex)
		{
		case INDEX_INVISIBLE_CURE:
			PCStartEffectGroup("InVisibleCure", slChaIndex);
			return;
		case INDEX_STONE_CURE:
		case INDEX_BLIND_CURE:
		case INDEX_SILENT_CURE:
			PCStartEffectGroup("CurePosion", slChaIndex);
			return;
		case INDEX_RECOMMEND_EVENT:
			PCStartEffectGroup("server_event_using", slChaIndex);
			return;
		}

		if (pItemData->GetType() == CItemData::ITEM_POTION)
		{
			/*				if( pItemData->GetSubType() == CItemData::POTION_HP )
							{
								PCStartEffectGroup( "potionHP", slChaIndex );
							}
							else if( pItemData->GetSubType() == CItemData::POTION_MP )
							{
								PCStartEffectGroup( "potionMP", slChaIndex );
							}*/
							/*if (strlen(pItemData->GetArmorEffectName()) > 0)
							{	// ���� �����ۿ� Effect�̸��� ��ϵǾ� �ִٴ� ���ǿ��� ����
								PCStartEffectGroup(pItemData->GetArmorEffectName(), slChaIndex);
							}*/

			if (slChaIndex == _pNetwork->MyCharacterInfo.index)
			{
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->PlayItemEffect(slItemIndex, -1);
			}
		}
	}
	break;
	case MSG_EFFECT_FIRE:
	{
		INDEX nExtra;
		INDEX nCount;
		INDEX index;
		INDEX animID[5];
		FLOAT x, z, h;
		//			SBYTE yLayer;
		CPlacement3D vDesiredPosition;
		CEntity* penEntity = NULL;
		CTString strEffectname;
		int i;

		(*istr) >> nExtra;
		(*istr) >> nCount;

		CPrintF("MSG_EFFECT_FIRE\n");

		for (i = 0; i < nCount; i++)
		{
			(*istr) >> index;
			(*istr) >> x;
			(*istr) >> z;
			(*istr) >> h;
			//		(*istr) >> yLayer;

			vDesiredPosition.pl_PositionVector(1) = x;
			vDesiredPosition.pl_PositionVector(2) = h;
			vDesiredPosition.pl_PositionVector(3) = z;
			vDesiredPosition.pl_OrientationAngle(1) = 0.0f;
			vDesiredPosition.pl_OrientationAngle(2) = 0.0f;
			vDesiredPosition.pl_OrientationAngle(3) = 0.0f;

			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_MOB, index);

			if (pObject != NULL)
			{
				penEntity = pObject->GetEntity();
				if (penEntity != NULL)
					penEntity->Teleport(vDesiredPosition, FALSE);

				CMobData* MD = CMobData::getData(pObject->m_nType);
				CPrintF("NPC index : %d \n", index);

				animID[0] = ska_StringToID(MD->GetAnimWalkName());		// ȭ�� ����Ʈ
				animID[1] = ska_StringToID(MD->GetAnimAttackName());		// ���� ����Ʈ
				animID[2] = ska_StringToID(MD->GetAnimRunName());		// ���� ����Ʈ
				animID[3] = ska_StringToID(MD->GetAnimDefault2Name());	// �ٶ� ����Ʈ
				animID[4] = ska_StringToID(MD->GetAnimAttack2Name());	// ���� ����Ʈ

				if (penEntity != NULL && nExtra > 0 && nExtra < 6)
					penEntity->GetModelInstance()->AddAnimation(animID[nExtra - 1], AN_CLEAR, 1.0f, 0);
			}
		}
	}
	break;
	}
}

void CSessionState::ReceiveEXPMessage(CNetworkMessage* istr)
{
	SQUAD Exp; //1013
	SQUAD Sp;


	(*istr) >> Exp;
	(*istr) >> Sp;


	_pNetwork->MyCharacterInfo.curExp += Exp;
	_pNetwork->MyCharacterInfo.sp += Sp;

	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString strExp, strSp;

	strExp.PrintF("%I64d", Exp);
	strSp.PrintF("%I64d", Sp);

	pUIManager->InsertCommaToString(strExp);
	pUIManager->InsertCommaToString(strSp);

	CTString strSysMessage;
	if (Exp > 0 && Sp > 0)
		strSysMessage.PrintF(_S(337, "%s�� ����ġ�� %s�� SP�� ������ϴ�."), strExp, strSp);
	else if (Exp > 0)
		strSysMessage.PrintF(_S(427, "%s�� ����ġ�� ������ϴ�."), strExp);
	else
		strSysMessage.PrintF(_S(428, "%s�� SP�� ������ϴ�."), strSp);

	pUIManager->GetChattingUI()->AddSysMessage(strSysMessage);
	pUIManager->GetSimplePlayerInfo()->UpdateEXP();
	pUIManager->GetCharacterInfo()->UpdateExpAndSp();
}

void CSessionState::ReceiveHonorMessage(CNetworkMessage* istr)
{
	SQUAD Honor; //1013

	(*istr) >> Honor;

	_pNetwork->MyCharacterInfo.a_honor += Honor;

	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString strExp;

	strExp.PrintF("%I64d", Honor);

	pUIManager->InsertCommaToString(strExp);

	CTString strSysMessage;

	strSysMessage.PrintF(_S(8550, "%s�� ����ġ�� %s�� SP�� ������ϴ�."), strExp);

	pUIManager->GetChattingUI()->AddSysMessage(strSysMessage);
	pUIManager->GetCharacterInfo()->UpdateHonorPoints();
}

void CSessionState::ReceiveActionMessage(CNetworkMessage* istr)
{
	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->Read_net_Character(MSG_ACTION, 0, &(*istr));
}

void CSessionState::ReceiveEnvMessage(CNetworkMessage* istr)//1013
{
	UBYTE subType;
	(*istr) >> subType;

	SLONG year, zone, sellrate, buyrate;
	SBYTE month, day, hour;
	UBYTE weather;

	// -------------------------------------->>
	LONG startWorldTime = 0;
	// --------------------------------------<<

	if (subType == MSG_ENV_TAX_CHANGE)
	{
		(*istr) >> zone
			>> sellrate
			>> buyrate;
	}
	else if (subType == MSG_ENV_WEATHER)
	{
		(*istr) >> weather;
	}
	else if (subType == MSG_ENV_TIME)
	{
		(*istr) >> year;
		(*istr) >> month;
		(*istr) >> day;
		(*istr) >> hour;
		(*istr) >> startWorldTime;

		//		if(_pNetwork->m_ubGMLevel < 2)//GM�̶�� �ð��� �帧�� �����.
		{
			CUIManager::getSingleton()->GetRadar()->SetTime(year, month, day, hour, startWorldTime);

			if (IS_EVENT_ON(A_EVENT_HOLLOWEEN))
			{
				g_fGWTime = 30 * 3600; // �ҷ�������2007�̺�Ʈ������ ��� ���� ���� �Ѵ�.
				g_fGWTimeMul = 0.0f;
			}
			else
			{
				g_fGWTime = hour * 3600;
			}
		}
	}
}

void CSessionState::ReceiveWarpMessage(CNetworkMessage* istr)
{
	UBYTE subtype;

	(*istr) >> subtype;
	static std::map<SLONG, CEffectGroup*> mapEG;

	CUIManager* pUIManager = CUIManager::getSingleton();

	if (subtype == MSG_WARP_START)
	{
		SLONG	char_index;
		(*istr) >> char_index;

		//������ ���� ����	//(5th Closed beta)(0.2)
		CTagManager* pTM = NULL;
		if (_pNetwork->MyCharacterInfo.index == char_index)
		{
			pUIManager->SetCSFlagOn(CSF_TELEPORT);
			pUIManager->GetTeleport()->CloseTeleport();

			pUIManager->GetInventory()->Lock(TRUE, FALSE, LOCK_WARP);

			if (CEntity::GetPlayerEntity(0) != NULL
				&& CEntity::GetPlayerEntity(0)->en_pmiModelInstance != NULL)
			{
				pTM = &CEntity::GetPlayerEntity(0)->en_pmiModelInstance->m_tmSkaTagManager;
			}
		}
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, char_index);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTM = &pTarget->GetEntity()->en_pmiModelInstance->m_tmSkaTagManager;
			}
		}

		CEffectGroup* pEG = StartEffectGroup("Teleport Start"		//Hardcording
			, pTM
			, _pTimer->GetLerpedCurrentTick());
		std::map<SLONG, CEffectGroup*>::value_type tmpVal(char_index, pEG);
		mapEG.insert(tmpVal);
		//������ ���� ��	//(5th Closed beta)(0.2)
	}
	else if (subtype == MSG_WARP_CANCEL)
	{
		SLONG	char_index;
		(*istr) >> char_index;

		if (_pNetwork->MyCharacterInfo.index == char_index)
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(340, "�̵��� ��ҵǾ����ϴ�."));

			if (pUIManager->DoesMessageBoxExist(MSGCMD_WARP_TO_CANCEL)) pUIManager->CloseMessageBox(MSGCMD_WARP_TO_CANCEL); //wooss 050808
			if (pUIManager->DoesMessageBoxExist(MSGCMD_WARP_TAKE_CANCEL)) pUIManager->CloseMessageBox(MSGCMD_WARP_TAKE_CANCEL); //wooss 050808
			// Character state flags
			pUIManager->SetCSFlagOff(CSF_TELEPORT);
			pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_WARP);
		}
		//������ ���� ����	//(5th Closed beta)(0.2)
		std::map<SLONG, CEffectGroup*>::iterator it = mapEG.find(char_index);
		if (it != mapEG.end())
		{
			if ((*it).second != NULL && CEffectGroupManager::Instance().IsValidCreated((*it).second))
				(*it).second->Stop(0);
			mapEG.erase(it);
		}
	}
	else if (subtype == MSG_WARP_END)
	{
		SLONG char_index;
		(*istr) >> char_index;

		std::map<SLONG, CEffectGroup*>::iterator it = mapEG.find(char_index);
		if (it != mapEG.end())
		{
			if ((*it).second != NULL && CEffectGroupManager::Instance().IsValidCreated((*it).second))
				(*it).second->Stop(0);
			mapEG.erase(it);
		}

		if (_pNetwork->MyCharacterInfo.index == char_index)
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(395, "�̵��� �Ϸ�Ǿ����ϴ�."));

			if (pUIManager->DoesMessageBoxExist(MSGCMD_WARP_TO_CANCEL)) pUIManager->CloseMessageBox(MSGCMD_WARP_TO_CANCEL); //wooss 050808
			if (pUIManager->DoesMessageBoxExist(MSGCMD_WARP_TAKE_CANCEL)) pUIManager->CloseMessageBox(MSGCMD_WARP_TAKE_CANCEL); //wooss 050808
			// Character state flags
			pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_WARP);
		}
	}
	else if (subtype == MSG_WARP_TELEPORT)
	{
		// pos(n) x(f:s) z(f:s) h(f:s) r(f:s) ylayer(c:s)
		LONG	lPos;
		float	fPosX;
		float	fPosZ;
		float	fPosH;
		float	fPosR;
		SBYTE	sbYLayer;

		(*istr) >> lPos;
		(*istr) >> fPosX;
		(*istr) >> fPosZ;
		(*istr) >> fPosH;
		(*istr) >> fPosR;
		(*istr) >> sbYLayer;

		CEntity* penPlEntity;
		CPlayerEntity* penPlayerEntity;
		penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
		penPlayerEntity = (CPlayerEntity*)penPlEntity;
		penPlayerEntity->WarpTeleport(fPosX, fPosZ, fPosH, fPosR, sbYLayer);
		UIMGR()->SetCSFlagOff(CSF_TELEPORT);
	}
	//wooss 050808 
	//��������� ��ȯ������ �޼��� ó��

	else if (subtype == MSG_WARP_TO_REQ)
	{
		CTString charName;
		(*istr) >> charName;
		ConfirmMsgProc(MSG_WARP_TO_REQ, NULL, charName);
	}
	else if (subtype == MSG_WARP_TAKE_REQ)
	{
		CTString charName;
		(*istr) >> charName;
		ConfirmMsgProc(MSG_WARP_TAKE_REQ, NULL, charName);
	}

	//����ó�� 
	else if (subtype == MSG_WARP_ERROR)
	{
		UBYTE errType;
		CTString strName;
		(*istr) >> errType;

		pUIManager->CloseMessageBox(MSGCMD_WARP_TO_CANCEL);
		pUIManager->CloseMessageBox(MSGCMD_WARP_TAKE_CANCEL);
		UIMGR()->SetCSFlagOff(CSF_TELEPORT);
		switch (errType)
		{
		case MSG_WARP_ERROR_NOTCHAR:
			ConfirmMsgProc(MSG_WARP_ERROR, MSG_WARP_ERROR_NOTCHAR);
			break;

		case MSG_WARP_ERROR_NOTALLOW:
			(*istr) >> strName;
			ASSERT(strName != "");
			ConfirmMsgProc(MSG_WARP_ERROR, MSG_WARP_ERROR_NOTALLOW, strName);
			break;

		case MSG_WARP_ERROR_NOTALLOWZONE:
			ConfirmMsgProc(MSG_WARP_ERROR, MSG_WARP_ERROR_NOTALLOWZONE);
			break;
		case MSG_WARP_ERROR_CANCEL:
			ConfirmMsgProc(MSG_WARP_ERROR, MSG_WARP_ERROR_CANCEL);
			break;
		}
	}
	else if (subtype == MSG_WARP_PROMPT) // ���� ���� �� ������������ �̵� �� ������ Ȯ��!!
	{
		LONG	lZone;
		LONG	lPos;

		(*istr) >> lZone;
		(*istr) >> lPos;

		_pNetwork->MyCharacterInfo.lWarpZone = lZone;
		_pNetwork->MyCharacterInfo.lWarpPos = lPos;

		pUIManager->CloseMessageBox(MSGCMD_SIEGE_WARFARE_MOVEING_CONFIRM);

		pUIManager->m_nShowMessageBox = MSGCMD_SIEGE_WARFARE_MOVEING_CONFIRM;
		CUIMsgBox_Info	MsgBoxInfo;
		CTString		strMessage;


#ifdef REZARLGL
		if (lZone == E_RLGL)
		{
			MsgBoxInfo.SetMsgBoxTimer(60, FALSE);
			MsgBoxInfo.SetMsgBoxInfo(CTString("Teleport to RLGL Event"), UMBS_YESNO | UMBS_USE_TIMER, UI_NONE, MSGCMD_SIEGE_WARFARE_MOVEING_CONFIRM);
			strMessage.PrintF(CTString("Would you like to attend the event?"));
			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);

		}
		else
		{
			MsgBoxInfo.SetMsgBoxInfo(_S(2071, "�������� �̵�"), UMBS_YESNO, UI_NONE, MSGCMD_SIEGE_WARFARE_MOVEING_CONFIRM);
			strMessage.PrintF(_S(2072, "���� ���� �������� �̵��Ͻðڽ��ϱ�?"));
			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
#else
		MsgBoxInfo.SetMsgBoxInfo(_S(2071, "�������� �̵�"), UMBS_YESNO, UI_NONE, MSGCMD_SIEGE_WARFARE_MOVEING_CONFIRM);
		strMessage.PrintF(_S(2072, "���� ���� �������� �̵��Ͻðڽ��ϱ�?"));
		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);
#endif
	}

	//������ ���� ��	//(5th Closed beta)(0.2)
}

void CSessionState::ReceiveAssistMessage(CNetworkMessage* istr)
{
	//CTString tempMessage;
	//CUIManager* pUIManager = CUIManager::getSingleton();

	SBYTE	sbType;
	(*istr) >> sbType;

	switch (sbType)
	{
	case MSG_ASSIST_ADD:
	{
		SBYTE		sbCharType;
		SLONG		slCharIndex;

		BuffInfo	sBuff;
		sBuff.m_llStartTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();

		(*istr) >> sbCharType >> slCharIndex;
		//(*istr) >> sBuff.m_slItemIndex >> sBuff.m_slSkillIndex >> sBuff.m_sbLevel >> sBuff.m_slRemain;  //����
		//2012/11/12 jeil ��ųȮ�� ���� count�� �߰� 
		(*istr) >> sBuff.m_slItemIndex;
		(*istr) >> sBuff.m_slSkillIndex;
		(*istr) >> sBuff.m_sbLevel;
		(*istr) >> sBuff.m_slRemain;
		(*istr) >> sBuff.m_slRemainCount;

		CItemData* pItemData = _pNetwork->GetItemData(sBuff.m_slItemIndex);
		CEntity* pDestEntity = NULL;
		ObjInfo* pInfo = ObjInfo::getSingleton();

		if (sbCharType == MSG_CHAR_PC)
		{
			if (_pNetwork->MyCharacterInfo.index == slCharIndex)
			{
				// wooss 070305 --------------------------------------------------------------------------------->>
				// kw : WSS_WHITEDAY_2007
				// 6�� ������� ��ų
				// 423 424 425 426 427 428

				CEffectGroup* pEG = NULL;

				CEntity* penEntity = (CPlayerEntity*)CEntity::GetPlayerEntity(0);

				if (sBuff.m_slSkillIndex >= 423 && sBuff.m_slSkillIndex <= 428)
				{
					int i, j;
					for (i = 423, j = 0; i <= 428; i++)
					{
						if ((_pUIBuff->IsBuffBySkill(i)) != NULL) {
							j++;
							break;
						}
					}

					// ó���̸� ����Ʈ�� ������...
					if (j == 0)
					{
						// ���� ����Ʈ - ���� ������ ��������� ����...
						pEG = StartEffectGroup("STATE_LOVE", &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
					}
					else
					{
						pEG = _pUIBuff->GetEGFromSkillIndex(i);
					}
					// ó���� �ƴϸ� ���� CEffectGroup�� �����͸� �Ѱ���...
					// ���� ������ �������� ���� �ϳ��� �������� ����Ʈ�� �����ش�...
					sBuff.m_pEG = pEG;

					// �߰� ����Ʈ
					StartEffectGroup("STATE_LOVEMAGIC", &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
				}
				// ------------------------------------------------------------------------------------------------<<
				else if (pItemData && pItemData->GetType() == CItemData::ITEM_POTION && strlen(pItemData->GetArmorEffectName()) > 0)
				{	// ���� �����ۿ� Effect�̸��� ��ϵǾ� �ִٴ� ���ǿ��� ����
					pEG = StartEffectGroup(pItemData->GetArmorEffectName(), &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
					sBuff.m_pEG = pEG;
				}

				if (sBuff.m_slSkillIndex == 564)	// �׸��� ���� �������� ȿ��
				{
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetFlagOn(ENF_SHOWHIDDEN);
				}

				// Ÿ�ٿ� �پ ���������� �÷��� �Ǵ� ����Ʈ�� �ٿ� �ֱ� ���� �߰�.
				if (strlen(_pNetwork->GetSkillData(sBuff.m_slSkillIndex).GetAfter_AttachEffect()) > 0)
				{
					sBuff.m_pEG = StartEffectGroup(_pNetwork->GetSkillData(sBuff.m_slSkillIndex).GetAfter_AttachEffect(),
						&penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
				}

				_pUIBuff->AddMyBuff(sBuff);

				pDestEntity = CEntity::GetPlayerEntity(0);

				//�̼���� �����϶� ������Ʈ�� ���� �ϵ��ڵ�..�Ѥ�;
				// wooss 070310 ----------------------->><<
				// kw : WSS_WHITEDAY_2007
				// Add lovemagic buff (wind - skill index 423 )
				if (sBuff.m_slItemIndex == 391 || sBuff.m_slItemIndex == 1226 || sBuff.m_slItemIndex == 1227 || sBuff.m_slSkillIndex == 423
					|| sBuff.m_slItemIndex == 2407 || sBuff.m_slItemIndex == 2408 || sBuff.m_slItemIndex == 2609 || sBuff.m_slItemIndex == 2845 //���� ������, �ٶ��� �ӵ� ����
					|| sBuff.m_slItemIndex == 2500
					|| sBuff.m_slItemIndex == 5018 || sBuff.m_slItemIndex == 5019 // ���� 2 ������
					)
				{
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetSpeedUp(TRUE, 0, TRUE);
				}
				CEntity* penPlayer = CEntity::GetPlayerEntity(0);
				if (pInfo->GetTargetEntity(eTARGET) == penPlayer)
					_pUIBuff->AddTargetBuff(sBuff);
			}
			else
			{
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, slCharIndex);

				if (pObject != NULL)
				{
					CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

					// 6�� ������� ��ų
					// 423 424 425 426 427 428

					CEffectGroup* pEG = NULL;
					CEntity* penEntity = _pNetwork->GetEntityByTypeIndex(sbCharType, slCharIndex);

					if (sBuff.m_slSkillIndex >= 423 && sBuff.m_slSkillIndex <= 428)
					{
						int i, j;
						for (i = 423, j = 0; i <= 428; i++)
						{
							if ((pTarget->IsBuffBySkill(i)) != NULL) {
								j++;
								break;
							}
						}

						// ó���̸� ����Ʈ�� ������...
						if (j == 0)
						{
							// ���� ����Ʈ - ���� ������ ��������� ����...
							pEG = StartEffectGroup("STATE_LOVE", &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
						}
						else
						{
							pEG = pTarget->IsBuffBySkill(i);
						}
						// ó���� �ƴϸ� ���� CEffectGroup�� �����͸� �Ѱ���...
						// ���� ������ �������� ���� �ϳ��� �������� ����Ʈ�� �����ش�...
						if (pEG != NULL)
						{
							sBuff.m_pEG = pEG;
						}

						// �߰� ����Ʈ
						StartEffectGroup("STATE_LOVEMAGIC", &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
					}
					// ------------------------------------------------------------------------------------------------<<
					else if (pItemData->GetType() == CItemData::ITEM_POTION && strlen(pItemData->GetArmorEffectName()) > 0)
					{	// ���� �����ۿ� Effect�̸��� ��ϵǾ� �ִٴ� ���ǿ��� ����
						pEG = StartEffectGroup(pItemData->GetArmorEffectName(), &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
						sBuff.m_pEG = pEG;
					}

					if (strlen(_pNetwork->GetSkillData(sBuff.m_slSkillIndex).GetAfter_AttachEffect()) > 0)
					{
						sBuff.m_pEG = StartEffectGroup(_pNetwork->GetSkillData(sBuff.m_slSkillIndex).GetAfter_AttachEffect(),
							&penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
					}

					pTarget->AddBuff(sBuff);
					_pUIBuff->AddPartyBuff(slCharIndex, sBuff);

					pDestEntity = pTarget->GetEntity();

					//�̼���� �����϶� ������Ʈ�� ���� �ϵ��ڵ�..�Ѥ�;
					// wooss 070310 ----------------------->><<
					// kw : WSS_WHITEDAY_2007
					// Add lovemagic buff (wind - skill index 423 )
					if (sBuff.m_slItemIndex == 391 || sBuff.m_slItemIndex == 1226 || sBuff.m_slItemIndex == 1227 || sBuff.m_slSkillIndex == 423
						|| sBuff.m_slItemIndex == 2407 || sBuff.m_slItemIndex == 2408 || sBuff.m_slItemIndex == 2609 || sBuff.m_slItemIndex == 2845	//���� ������, �ٶ��� �ӵ� ����
						|| sBuff.m_slItemIndex == 2500
						|| sBuff.m_slItemIndex == 5018 || sBuff.m_slItemIndex == 5019 // ���� 2 ������
						)
					{
						((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetSpeedUp(FALSE, pTarget->GetCIndex(), TRUE);
					}

					if (pInfo->GetTargetEntity(eTARGET) == pTarget->GetEntity())
						_pUIBuff->AddTargetBuff(sBuff);
				}
			}
		}
		else if (sbCharType == MSG_CHAR_NPC)
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_MOB, slCharIndex);

			if (pObject != NULL)
			{
				CMobTarget* pTarget = static_cast<CMobTarget*>(pObject);

				pDestEntity = pTarget->GetEntity();

				if (pDestEntity == NULL)
					return;

				if (strlen(_pNetwork->GetSkillData(sBuff.m_slSkillIndex).GetAfter_AttachEffect()) > 0)
				{
					CEffectGroup* pEG = StartEffectGroup(_pNetwork->GetSkillData(sBuff.m_slSkillIndex).GetAfter_AttachEffect(),
						&pDestEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());

					sBuff.m_pEG = pEG;
				}

				pTarget->AddBuff(sBuff);
				pTarget->BuffsStartGroupEffect();

				if (pInfo->GetTargetEntity(eTARGET) == pTarget->GetEntity())
					_pUIBuff->AddTargetBuff(sBuff);
			}
		}
		else if (sbCharType == MSG_CHAR_ELEMENTAL)
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_SLAVE, slCharIndex);

			if (pObject != NULL)
			{
				CSlaveTarget* pTarget = static_cast<CSlaveTarget*>(pObject);

				pTarget->AddBuff(sBuff);

				pDestEntity = pTarget->m_pEntity;

				if (pInfo->GetTargetEntity(eTARGET) == pTarget->GetEntity())
					_pUIBuff->AddTargetBuff(sBuff);
			}
		}

		// ������ ������ ��� Ÿ�ٿ� ����Ʈ ����
		if (sBuff.m_slItemIndex == 2382)
		{
			CTString strEffect = _pNetwork->GetSkillData(sBuff.m_slSkillIndex).GetFireEffect1(0);
			StartEffectGroup(strEffect, &pDestEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
		}
	}
	break;

	case MSG_ASSIST_DEL:
	{
		SBYTE	sbCharType;
		SLONG	slCharIndex, slItemIndex, slSkillIndex;

		(*istr) >> sbCharType >> slCharIndex >> slItemIndex >> slSkillIndex;

		CItemData* pItemData = _pNetwork->GetItemData(slItemIndex);
		ObjInfo* pInfo = ObjInfo::getSingleton();

		if (sbCharType == MSG_CHAR_PC)
		{
			if (_pNetwork->MyCharacterInfo.index == slCharIndex)
			{
				// wooss 070305 ----------------------------------->>
				// kw : WSS_WHITEDAY_2007
				// 6�� ������� ��ų
				// 423 424 425 426 427 428
				if (slSkillIndex >= 423 && slSkillIndex <= 428)
				{
					int i, j;
					for (i = 423, j = 0; i <= 428; i++)
					{
						if (_pUIBuff->IsBuffBySkill(i)) j++;
					}

					// ������ ������ ������� ����Ʈ�� ������...
					if (j == 1)
					{
						CEffectGroup* pEG = _pUIBuff->GetEGFromSkillIndex(slSkillIndex);
						if (pEG != NULL)
						{
							DestroyEffectGroup(pEG);
						}
					}
				}
				// -------------------------------------------------<<
				else if (slSkillIndex == 564) // �׸��� ���� ���� ���� ȿ�� ����
				{
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetFlagOff(ENF_SHOWHIDDEN);

					if (pInfo->GetTargetDBIdx(eTARGET) == 504 || pInfo->GetTargetDBIdx(eTARGET) == 505) //�Ȱ��׸��� �巡��,�ͺ��׸��� �巡��
					{
						if (pInfo->GetTargetEntity(eTARGET) != NULL)
							CUIManager::getSingleton()->StopTargetEffect(pInfo->GetTargetServerIdx(eTARGET)); // Ÿ�� ����Ʈ ����

						((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ClearTargetInfo(pInfo->GetTargetEntity(eTARGET));
					}
				}

				_pUIBuff->RemoveMyBuff(slItemIndex, slSkillIndex);


				// wooss 070310 ----------------------->><<
				// kw : WSS_WHITEDAY_2007
				// Add lovemagic buff (wind - skill index 423 )
				if (!_pUIBuff->IsBuff(391) && !_pUIBuff->IsBuff(1226) && !_pUIBuff->IsBuff(1227) && !_pUIBuff->IsBuffBySkill(423) //�̼���� �����϶� ������Ʈ�� ���� �ϵ��ڵ�..�Ѥ�;
					&& !_pUIBuff->IsBuff(2407) && !_pUIBuff->IsBuff(2408) && !_pUIBuff->IsBuff(2609) && !_pUIBuff->IsBuff(2845)		//���� ������, �ٶ��� �ӵ� ����
					&& !_pUIBuff->IsBuff(2500)
					&& !_pUIBuff->IsBuff(5018) && !_pUIBuff->IsBuff(5019) // ���� 2 ������
					)
				{
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetSpeedUp(TRUE, 0, FALSE);
				}

				CEntity* penPlayer = CEntity::GetPlayerEntity(0);
				if (pInfo->GetTargetEntity(eTARGET) == penPlayer)
					_pUIBuff->RemoveTargetBuff(slItemIndex, slSkillIndex);
			}
			else
			{
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, slCharIndex);

				if (pObject != NULL)
				{
					CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

					// wooss 070312 ------------------------------------>>
					// kw : WSS_WHITEDAY_2007
					if (slSkillIndex >= 423 && slSkillIndex <= 428)
					{
						int i, j;
						for (i = 423, j = 0; i <= 428; i++)
						{
							if (pTarget->IsBuffBySkill(i))
								j++;
						}

						// ������ ������ ������� ����Ʈ�� ������...
						if (j == 1)
						{
							CEffectGroup* pEG = pTarget->IsBuffBySkill(slSkillIndex);
							if (pEG != NULL)
							{
								DestroyEffectGroup(pEG);
							}
						}
					}
					// -------------------------------------------------<<

					pTarget->RemoveBuff(slItemIndex, slSkillIndex);
					_pUIBuff->RemovePartyBuff(slCharIndex, slItemIndex, slSkillIndex);


					// wooss 070310 ----------------------->><<
					// kw : WSS_WHITEDAY_2007
					// Add lovemagic buff (wind - skill index 423 )
					//if( !_pUIBuff->IsBuff( 391 ) && !_pUIBuff->IsBuff( 1226 ) && !_pUIBuff->IsBuff( 1227 ) &&!_pUIBuff->IsBuffBySkill(423) )//�̼���� �����϶� ������Ʈ�� ���� �ϵ��ڵ�..�Ѥ�;
					if (!pTarget->IsBuff(391) && !pTarget->IsBuff(1226) && !pTarget->IsBuff(1227) && !pTarget->IsBuffBySkill(423) //�̼���� �����϶� ������Ʈ�� ���� �ϵ��ڵ�..�Ѥ�;
						&& !pTarget->IsBuff(2407) && !pTarget->IsBuff(2408) && !pTarget->IsBuff(2609) && !pTarget->IsBuff(2845)	//���� ������
						&& !pTarget->IsBuff(2500)
						&& !pTarget->IsBuff(5018) && !pTarget->IsBuff(5019) // ���� 2 ������
						)
					{
						((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetSpeedUp(FALSE, pTarget->m_nIdxClient, FALSE);
					}

					if (pInfo->GetTargetEntity(eTARGET) == pTarget->m_pEntity)
						_pUIBuff->RemoveTargetBuff(slItemIndex, slSkillIndex);
				}
			}
		}
		else if (sbCharType == MSG_CHAR_NPC)
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_MOB, slCharIndex);

			if (pObject != NULL)
			{
				CMobTarget* pTarget = static_cast<CMobTarget*>(pObject);
				pTarget->RemoveBuff(slItemIndex, slSkillIndex);
				if (pInfo->GetTargetEntity(eTARGET) == pTarget->m_pEntity)
					_pUIBuff->RemoveTargetBuff(slItemIndex, slSkillIndex);
			}
		}
		else if (sbCharType == MSG_CHAR_ELEMENTAL)
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_SLAVE, slCharIndex);

			if (pObject != NULL)
			{
				CSlaveTarget* pTarget = static_cast<CSlaveTarget*>(pObject);

				pTarget->RemoveBuff(slItemIndex, slSkillIndex);
				if (pInfo->GetTargetEntity(eTARGET) == pTarget->GetEntity())
					_pUIBuff->RemoveTargetBuff(slItemIndex, slSkillIndex);
			}
		}
	}
	break;
	case MSG_ASSIST_MODIFY:	//2012/11/12 jeil �߰� 1119���� ��ųȮ�� ���� �߰�	
	{
		SBYTE		sbCharType;
		SLONG		slCharIndex;

		BuffInfo	sBuff;
		sBuff.m_llStartTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();

		(*istr) >> sbCharType >> slCharIndex;
		//(*istr) >> sBuff.m_slItemIndex >> sBuff.m_slSkillIndex >> sBuff.m_sbLevel >> sBuff.m_slRemain;  //����
		//2012/11/12 jeil ��ųȮ�� ���� count�� �߰� 
		(*istr) >> sBuff.m_slItemIndex >> sBuff.m_slSkillIndex >> sBuff.m_sbLevel >> sBuff.m_slRemain >> sBuff.m_slRemainCount;
		if (sBuff.m_slRemainCount == 0)
		{
			_pUIBuff->RemoveMyBuff(sBuff.m_slItemIndex, sBuff.m_slSkillIndex);
		}
		else
		{
			if (sbCharType == MSG_CHAR_PC)
			{
				if (_pNetwork->MyCharacterInfo.index == slCharIndex)
				{
					_pUIBuff->ChangeMyBuffRemain(sBuff.m_slItemIndex, sBuff.m_slSkillIndex, sBuff.m_llStartTime, sBuff.m_slRemain);
				}
				else
				{
					ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, slCharIndex);

					if (pObject != NULL)
					{
						if (INFO()->GetTargetEntity(eTARGET) == pObject->GetEntity())
							_pUIBuff->ChangeTargetBuffRemain(sBuff.m_slItemIndex, sBuff.m_slSkillIndex, sBuff.m_llStartTime, sBuff.m_slRemain);
					}
				}
			}
		}
	}
	break;
	case MSG_ASSIST_LIST:
	{
		SQUAD	slAssistState;
		SBYTE	sbAssistCount;
		(*istr) >> slAssistState >> sbAssistCount;

		_pUIBuff->ResetMyBuff();

		BuffInfo	sBuff;
		sBuff.m_llStartTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();
		CEntity* penEntity = (CPlayerEntity*)CEntity::GetPlayerEntity(0);
		CEffectGroup* pEG = NULL;

		for (int i = 0; i < sbAssistCount; i++)
		{
			//(*istr) >> sBuff.m_slItemIndex >> sBuff.m_slSkillIndex >> sBuff.m_sbLevel >> sBuff.m_slRemain; //���� 
			//2012/11/12 jeil ��ųȮ�� ���� count�� �߰� 
			(*istr) >> sBuff.m_slItemIndex;
			(*istr) >> sBuff.m_slSkillIndex;
			(*istr) >> sBuff.m_sbLevel;
			(*istr) >> sBuff.m_slRemain;
			(*istr) >> sBuff.m_slRemainCount;

			CItemData* pItemData = _pNetwork->GetItemData(sBuff.m_slItemIndex);
			// wooss 070305 ------------------------------------>>
			// kw : WSS_WHITEDAY_2007
			// 6�� ������� ��ų
			// 423 424 425 426 427 428
			if (sBuff.m_slSkillIndex >= 423 && sBuff.m_slSkillIndex <= 428)
			{
				int i, j;
				for (i = 423, j = 0; i <= 428; i++)
				{
					if (_pUIBuff->IsBuffBySkill(i)) j++;
				}

				// ó���̸� ����Ʈ�� ������...
				if (j == 0)
				{
					pEG = StartEffectGroup("STATE_LOVE", &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
					//		penEntity->GetModelInstance()->pEG = StartEffectGroup( 
					//			"STATE_LOVE", 
					//			&penEntity->en_pmiModelInstance->m_tmSkaTagManager, 
					//			_pTimer->GetLerpedCurrentTick());
				}

				sBuff.m_pEG = pEG;
			}
			// -------------------------------------------------<<
			else if (pItemData && pItemData->GetType() == CItemData::ITEM_POTION && strlen(pItemData->GetArmorEffectName()) > 0)
			{	// ���� �����ۿ� Effect�̸��� ��ϵǾ� �ִٴ� ���ǿ��� ����
				pEG = StartEffectGroup(pItemData->GetArmorEffectName(), &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
				sBuff.m_pEG = pEG;
			}

			if (sBuff.m_slSkillIndex == 564)	// �׸��� ���� �������� ȿ��
			{
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetFlagOn(ENF_SHOWHIDDEN);
			}

			// wooss 070310 ----------------------->><<
			// kw : WSS_WHITEDAY_2007
			// Add lovemagic buff (wind - skill index 423 )
			if (sBuff.m_slItemIndex == 391 || sBuff.m_slItemIndex == 1226 || sBuff.m_slItemIndex == 1227 || sBuff.m_slSkillIndex == 423//�̼���� �����϶� ������Ʈ�� ���� �ϵ��ڵ�..�Ѥ�;
				|| sBuff.m_slItemIndex == 2407 || sBuff.m_slItemIndex == 2408 || sBuff.m_slItemIndex == 2609 || sBuff.m_slItemIndex == 2845	//���� ������, �ٶ��� �ӵ� ����
				|| sBuff.m_slItemIndex == 2500
				|| sBuff.m_slItemIndex == 5018 || sBuff.m_slItemIndex == 5019 // ���� 2 ������
				)
			{
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetSpeedUp(TRUE, 0, TRUE);
			}

			_pUIBuff->AddMyBuff(sBuff);
		}
	}
	break;
	}
}

// ----------------------------------------------------------------------------
// Name : ReceiveQuestMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveQuestMessage(CNetworkMessage* istr)
{
	UBYTE ubType;
	(*istr) >> ubType;

	CUIManager* pUIManager = CUIManager::getSingleton();
	Quest* pQuest = GAMEDATAMGR()->GetQuest();

	if (pQuest == NULL)
		return;

	MSG_QUEST_TYPE msgQuestType = MSG_QUEST_TYPE(ubType);
	switch (msgQuestType)
	{
	case MSG_QUEST_PC_LIST:
	{
		INDEX questCount;
		INDEX questIndex;
		INDEX questCurCount[QUEST_MAX_CONDITION];

		(*istr) >> questCount;			// �������� ����Ʈ ��

		pQuest->ClearQuestList();
		CQuestSystem::Instance().ClearAllDynamicData();
		for (INDEX iQuest = 0; iQuest < questCount; ++iQuest)
		{
			(*istr) >> questIndex;		// ����Ʈ ��ȣ
			// connie [2009/9/7] - tutorial quest
			if (questIndex == 45)
				pUIManager->GetQuestBookList()->OpenTutorialWindow();

			for (int i = 0; i < QUEST_MAX_CONDITION; ++i)
			{
				(*istr) >> questCurCount[i];
			}

			CQuestDynamicData* pQuestDD = CQuestSystem::Instance().GetDynamicDataByQuestIndex(questIndex);
			if (pQuestDD == NULL)
			{
				pQuestDD = CQuestSystem::Instance().Create(questIndex);
				if (pQuestDD != NULL)
				{
					CQuestSystem::Instance().AddCurrentRequest();
					pQuestDD->SetCurrentConditionValueStatus(questCurCount);
					BOOL bInserted = pQuest->AddQuestList(questIndex, pQuestDD->IsQuestComplete());
					ASSERT(bInserted && "Somthing is wrong, client fail add quest to list");
					CQuestSystem::Instance().SetQuestAllow(questIndex, CQuestSystem::QAT_DOING);
				}
				else
				{
					ASSERTALWAYS("MSG_QUEST_LIST : Quest Index is abnormal. Server or Client has wrong quest index.");
				}
			}
		}
		pUIManager->GetQuestBookList()->RefreshQuestListNew();
		pUIManager->GetQuestView()->open();
	}
	break;
	case MSG_QUEST_NPC_LIST:
	{
		//TODO : NewQuestSystem
		INDEX iNpcIndex;
		INDEX iQuestCount;
		INDEX iQuestIndex;
		SBYTE sbQuestFlag;

		(*istr) >> iNpcIndex;
		(*istr) >> iQuestCount;

		pQuest->ClearQuest();

		// Handle NPC 3696 (Cash Exchange) specially
		if (iNpcIndex == 3696)
		{
			pUIManager->GetCashExchange()->OpenUI();
		}
		else
		{
			INDEX iQuestValid = 0;
			for (INDEX iQuest = 0; iQuest < iQuestCount; ++iQuest)
			{
				(*istr) >> iQuestIndex;
				(*istr) >> sbQuestFlag;
				if (sbQuestFlag == QUEST_FLAG_CAN)
				{
					BOOL bInserted = pQuest->AddQuest(iQuestIndex, FALSE);
					ASSERT(bInserted && "Somthing is wrong, client fail add quest to list");
					++iQuestValid;
				}
				else if (sbQuestFlag == QUEST_FLAG_COMPLETE)
				{
					BOOL bInserted = pQuest->AddQuest(iQuestIndex, TRUE);
					ASSERT(bInserted && "Somthing is wrong, client fail add quest to list");
					++iQuestValid;
				}
			}

			pUIManager->GetQuestBookList()->SetTargetIndex(pUIManager->GetQuestAccept()->GetTargetIndex());
			pUIManager->GetQuestAccept()->OpenWindow(iQuestValid > 0 ? TRUE : FALSE);
		}
	}
	break;
	case MSG_QUEST_RANKING_SUMMON_REP:
	{
		SBYTE		sbMultiCount;
		CTString	strName;
		INDEX		iNumOfDeadMonster;
		INDEX		iJob;

		(*istr) >> sbMultiCount;

		pUIManager->GetRankingSummon()->ClearRankingList();

		for (int i = 0; i < sbMultiCount; ++i)
		{
			(*istr) >> strName;
			(*istr) >> iNumOfDeadMonster;
			(*istr) >> iJob;
			pUIManager->GetRankingSummon()->AddToRankingList(strName, iNumOfDeadMonster, iJob);
		}

		if (!pUIManager->GetRankingSummon()->IsVisible())
			pUIManager->GetRankingSummon()->OpenRankingList();
		else
			pUIManager->GetRankingSummon()->RefreshRankingList();
	}
	break;
	case MSG_QUEST_RANKING_REBORN_REP:
	{
		SBYTE		sbMultiCount;
		CTString	strName;
		INDEX		iNumOfReborns;
		INDEX		iJob;

		(*istr) >> sbMultiCount;

		pUIManager->GetRankingReborn()->ClearRankingList();

		for (int i = 0; i < sbMultiCount; ++i)
		{
			(*istr) >> strName;
			(*istr) >> iNumOfReborns;
			(*istr) >> iJob;
			pUIManager->GetRankingReborn()->AddToRankingList(strName, iNumOfReborns, iJob);
		}

		if (!pUIManager->GetRankingReborn()->IsVisible())
			pUIManager->GetRankingReborn()->OpenRankingList();
		else
			pUIManager->GetRankingReborn()->RefreshRankingList();
	}
	break;
	case MSG_QUEST_RANKING_PVP_REP:
	{
		SBYTE		sbMultiCount;
		CTString	strName;
		INDEX		iNumOfKills;
		INDEX		iJob;

		(*istr) >> sbMultiCount;

		pUIManager->GetRankingPvP()->ClearRankingList();

		for (int i = 0; i < sbMultiCount; ++i)
		{
			(*istr) >> strName;
			(*istr) >> iNumOfKills;
			(*istr) >> iJob;
			pUIManager->GetRankingPvP()->AddToRankingList(strName, iNumOfKills, iJob);
		}

		if (!pUIManager->GetRankingPvP()->IsVisible())
			pUIManager->GetRankingPvP()->OpenRankingList();
		else
			pUIManager->GetRankingPvP()->RefreshRankingList();
	}
	break;
	case MSG_QUEST_PD4_RANK_VIEW_REP:		// �̱۴��� ��ŷ �� ����.
	{
		// ��ũ ������	: multicount(c) charname(str) bclear(c) deadmon(n) time(ll)
		SBYTE		sbMultiCount;
		CTString	strName;
		SBYTE		sbSuccess;
		INDEX		iNumOfDeadMonster;
		__int64		llTime;

		(*istr) >> sbMultiCount;

		pUIManager->GetRanking()->ClearRankingList();

		for (int i = 0; i < sbMultiCount; ++i)
		{
			(*istr) >> strName;
			(*istr) >> sbSuccess;
			(*istr) >> iNumOfDeadMonster;
			(*istr) >> llTime;
			pUIManager->GetRanking()->AddToRankingList(strName, sbSuccess, iNumOfDeadMonster, llTime);
		}

		if (!pUIManager->GetRanking()->IsVisible())
			pUIManager->GetRanking()->OpenRankingList();
		else
			pUIManager->GetRanking()->RefreshRankingList();
	}
	break;

	case MSG_QUEST_PD4_RANK_REWARD_RANK_REP:	// �̱۴��� ���� ����.
	{
		// ���� ������	: multicount(c) charname(str) itemindex(n) itemnum(c) breward(c)			
		SBYTE		sbMultiCount;
		CTString	strName;
		INDEX		iItemIndex;
		SBYTE		sbNumOfItem;
		SBYTE		sbReward;

		(*istr) >> sbMultiCount;

		for (int i = 0; i < sbMultiCount; ++i)
		{
			(*istr) >> strName;
			(*istr) >> iItemIndex;
			(*istr) >> sbNumOfItem;
			(*istr) >> sbReward;
			pUIManager->GetRanking()->AddToPrizeList(strName, iItemIndex, sbNumOfItem, sbReward);
		}

		pUIManager->GetRanking()->OpenRankingPrize();
	}
	break;

	case MSG_QUEST_PD4_REWARD:	// ������ ���� ���.
	{
		pUIManager->GetRanking()->ResetRanking();
	}
	break;

	case MSG_QUEST_PD4_ERROR:	// ���� �߻�.
	{
		SBYTE	sbErrType;
		(*istr) >> sbErrType;
		CTString strMessage;

		switch (sbErrType)
		{
		case MSG_QUEST_ERR_REWARD_NOT_RANK:		// ����� ��Ŀ�� �ƴ�.
			strMessage = _S(1754, "������ ���� �� �ִ� ������ �ƴմϴ�.");
			_pNetwork->ClientSystemMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_QUEST_ERR_BREWARD:				// �̹� ���� �޾���.
			strMessage = _S(1755, "�̹� ������ �޾ҽ��ϴ�.");
			_pNetwork->ClientSystemMessage(strMessage, SYSMSG_ERROR);
			break;
		}
		pUIManager->GetRanking()->ResetRanking();
	}
	break;

	case MSG_QUEST_CREATE_LIST://�ڵ� ����Ʈ �κ�
	{
		//TODO : NewQuestSystem
		INDEX iQuestCount;
		INDEX iQuestIndex;

		(*istr) >> iQuestCount;

		Notice* pNotice = GAMEDATAMGR()->GetNotice();

		for (INDEX iQuest = 0; iQuest < iQuestCount; ++iQuest)
		{
			(*istr) >> iQuestIndex;

			if (pNotice != NULL)
				pNotice->AddToNoticeList(iQuestIndex, Notice::NOTICE_QUEST);
		}
		if (iQuestCount > 0)
		{
			CTString strLevelQuest;
			strLevelQuest.PrintF(_S(770, "���� ����Ʈ�� %d�� �޾ҽ��ϴ�."), iQuestCount);
			_pNetwork->ClientSystemMessage(strLevelQuest);
		}
	}
	break;

	case MSG_QUEST_START:
	{
		//TODO : NewQuestSystem
		INDEX questIndex;
		INDEX remainTime = -1;		// [090609: selo] Ÿ�Ӿ��ÿ����� ���� �ð�
		(*istr) >> questIndex;
		(*istr) >> remainTime;
		//Check Point Init
		_pNetwork->SetCheckPointData(0, 0, 0);

		CQuestDynamicData* pQuestDD = CQuestSystem::Instance().Create(questIndex);
		//pUIManager->GetCharacterInfo()->OpenQuestIntro( pQuestDD );

		//TODO : NewQuestSystem
		ASSERT(CQuestSystem::Instance().GetCurrentRequest() != NULL &&
			questIndex == CQuestSystem::Instance().GetCurrentRequest()->GetQuestIndex());
		CQuestSystem::Instance().AddCurrentRequest();

		BOOL bInserted = pQuest->AddQuestList(questIndex, FALSE);
		pQuest->AddSelectedQuest(questIndex);
		ASSERT(bInserted && "Somthing is wrong, client fail add quest to list");

		// [090609: selo] Ÿ�Ӿ����� ���� �ð��� �����Ѵ�.
		pQuest->SetQuestRemainTime(questIndex, remainTime);

		pUIManager->GetQuestBookList()->RefreshQuestListNew();

		if (g_iQuestBookOpen != 0)
		{
			pUIManager->GetQuestBookList()->open();
		}
		else
		{
			CTString	cstrQuestMessage;
			cstrQuestMessage.PrintF(_S(5588, "[%s] ����Ʈ�� �����Ͽ����ϴ�."), CQuestSystem::Instance().GetQuestName(questIndex));
			_pNetwork->ClientSystemMessage(cstrQuestMessage);
		}

		CQuestSystem::Instance().SetQuestAllow(questIndex, CQuestSystem::QAT_DOING);
		INDEX iTargetIndex = pUIManager->GetQuestAccept()->GetTargetIndex();
		ACTORMGR()->RefreshNPCQuestMark(iTargetIndex);

		pUIManager->GetQuestAccept()->close();

		if (pQuestDD->GetQuestType1() == QTYPE_KIND_SAVE)			// �̱۴��� ����Ʈ�� ���(���� ����Ʈ�� ���)
		{
			// �ϴ� �������� �̵� ��Ű������...
			// ������ 0���� �Ǵ���.				
			const int iWorldNum = pQuestDD->GetConditionData(0, 0);						// ���� ��ȣ.
			const int iExtraNum = pQuestDD->GetConditionData(0, 1);						// Extra ��ȣ.
			_pNetwork->GoZone(iWorldNum, iExtraNum, pQuestDD->GetPrizeNPCIndex());
		}
		else if (pQuestDD->GetQuestType1() == QTYPE_KIND_DEFEAT)	// �̱۴��� ����Ʈ�� ���(���� ����Ʈ�� ���)
		{
			// �ϴ� �������� �̵� ��Ű������...
			// ������ 0���� �Ǵ���.
			const int iWorldNum = pQuestDD->GetConditionData(0, 0);						// ���� ��ȣ.
			const int iExtraNum = pQuestDD->GetConditionData(0, 1);						// Extra ��ȣ.
			_pNetwork->GoZone(iWorldNum, iExtraNum, pQuestDD->GetPrizeNPCIndex());
		}
	}
	break;

	case MSG_QUEST_STATUS:
	{
		//TODO : NewQuestSystem
		INDEX questIndex;
		INDEX currentConditionValue[3];

		(*istr) >> questIndex;
		CQuestDynamicData* pData = CQuestSystem::Instance().GetDynamicDataByQuestIndex(questIndex);
		int changeIndex = -1;
		for (int i = 0; i < QUEST_MAX_CONDITION; ++i)
		{
			(*istr) >> currentConditionValue[i];
			if (pData->GetCurrentConditionValueStatus(i) != currentConditionValue[i]
				&& (pData->GetConditionType(i) == QCONDITION_ITEM
					|| pData->GetConditionType(i) == QCONDITION_ITEM_NORMAL
					|| pData->GetConditionType(i) == QCONDITION_NPC
					|| pData->GetConditionType(i) == QCONDITION_AREA
					|| pData->GetConditionType(i) == QCONDITION_ITEMUSE)
				)
				changeIndex = i;
		}

		if (pData != NULL)
		{
			pData->SetCurrentConditionValueStatus(currentConditionValue);
			// [090731: selo] ����Ʈ ���� ������Ʈ ó��
			pUIManager->GetQuestBookList()->UpdateQuestContent(questIndex);
			pUIManager->GetQuestView()->UpdateContent();

			if (changeIndex != -1
				&& (_UIAutoHelp->GetGMNoticeColor() == 0xFFFFFFFF || !_UIAutoHelp->IsShowGMNotice()))
			{
				CTString strCurrentChangedStatus = CQuestSystem::Instance().MakeInfoForCondition(
					questIndex
					, pData->GetConditionType(changeIndex)
					, pData->GetConditionIndex(changeIndex)
					, currentConditionValue[changeIndex]
					, pData->GetConditionNum(changeIndex));
				if (strCurrentChangedStatus.Length() != 0)
					_UIAutoHelp->SetGMNotice(strCurrentChangedStatus, 0xFFFFFFFF);
			}
		}
		else
		{
			ASSERTALWAYS("MSG_QUEST_STATUS : Quest Index is abnormal. Server or Client has wrong quest index.");
		}
	}
	break;

	case MSG_QUEST_COMPLETE:
	{
		INDEX questIndex;
		(*istr) >> questIndex;

		//TODO : NewQuestSystem
		CQuestDynamicData* pData = CQuestSystem::Instance().GetDynamicDataByQuestIndex(questIndex);
		if (pData)
		{
			pData->MakeQuestComplete();
			pQuest->DelQuestList(questIndex, FALSE);
			pQuest->AddQuestList(questIndex, TRUE);
			pUIManager->GetQuestBookList()->RefreshQuestListNew();
			pUIManager->GetQuestBookList()->UpdateQuestContent(questIndex);

			ACTORMGR()->RefreshNPCQuestMark(pData->GetPrizeNPCIndex());
			// �̱۴��� ������ ����Ʈ�� ���.
			if (_pNetwork->m_bSingleMode)
			{
				if (pData->GetQuestType1() == QTYPE_KIND_DEFEAT || pData->GetQuestType1() == QTYPE_KIND_SAVE)
				{
					pUIManager->CloseMessageBox(MSGCMD_QUEST_COMPLETE);
					CTString		strMessage;
					CUIMsgBox_Info	MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(99, "����Ʈ"), UMBS_OK, UI_CHARACTERINFO, MSGCMD_QUEST_COMPLETE);
					strMessage.PrintF(_S(667, "[%s] ����Ʈ�� �Ϸ� �߽��ϴ�."), pData->GetName());
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);

					// ���� ���� �� ��Ƽ�� ���´�. [12/26/2006 Theodoric]
					if (_pNetwork->m_bSingleMode && GAMEDATAMGR()->GetPartyInfo()->GetMemberCount())
					{
						GAMEDATAMGR()->GetPartyInfo()->PartyEnd();
					}
					// ��ŸƮ ������ �̵���Ŵ.
					//_pNetwork->GoZone(0, 0);
				}
			}
#ifdef CLOUD_AUTO_QUEST_DELIVERY
			//Cloud auto quest
			if (pUIManager->GetQuestBookList()->GetSaveAutoQuest() && !pData->IsOptionPrizeExist())//g_iQuestAutoDelivery
				_pNetwork->Send_auto_quest(questIndex);
			//Cloud auto quest
#endif
		}
		else
		{
			ASSERTALWAYS("MSG_QUEST_COMPLETE : Quest Index is abnormal. Server or Client has wrong quest index.");
		}

		pUIManager->GetQuestView()->open();
	}
	break;

	case MSG_QUEST_UNCOMPLETE:
	{
		INDEX questIndex;
		(*istr) >> questIndex;
		//TODO : NewQuestSystem
		CQuestDynamicData* pData = CQuestSystem::Instance().GetDynamicDataByQuestIndex(questIndex);
		if (pData)
		{
			pData->MakeQuestUncomplete();
			BOOL bDeleted = pQuest->DelQuestList(questIndex, TRUE);
			if (!bDeleted)//�����°� ������
			{
				bDeleted = pQuest->DelQuestList(questIndex, FALSE);
				ASSERTALWAYS("Somthing is wrong, client fail delete quest from list");
				if (!bDeleted)
				{
					ASSERTALWAYS("Somthing is wrong, unknown quest index");
				}
			}
			BOOL bInserted = pQuest->AddQuestList(questIndex, FALSE);
			ASSERT(bInserted && "Somthing is wrong, client fail add quest to list");
			pUIManager->GetQuestBookList()->RefreshQuestListNew();
			pUIManager->GetQuestBookList()->UpdateQuestContent(questIndex);

			ACTORMGR()->RefreshNPCQuestMark(pData->GetPrizeNPCIndex());
		}
		else
		{
			ASSERTALWAYS("MSG_QUEST_UNCOMPLETE : Quest Index is abnormal. Server or Client has wrong quest index.");
		}
	} break;

	case MSG_QUEST_GIVEUP:
	{
		//TODO : NewQuestSystem
		INDEX questIndex;
		(*istr) >> questIndex;

		if (CQuestSystem::Instance().GetCurrentRequest() != NULL &&
			questIndex == CQuestSystem::Instance().GetCurrentRequest()->GetQuestIndex())
		{
			CQuestSystem::Instance().DeleteCurrentRequest();
			CQuestSystem::Instance().SetQuestAllow(questIndex, CQuestSystem::QAT_GIVEUP);
			ACTORMGR()->RefreshNPCQuestMark(pUIManager->GetQuestAccept()->GetTargetIndex());
			pUIManager->GetQuestAccept()->close();
		}
		else
		{
			CQuestDynamicData* pData = CQuestSystem::Instance().GetDynamicDataByQuestIndex(questIndex);
			if (pData != NULL)
			{
				if (pUIManager->GetQuestBookComplete()->GetCurrIdx() == questIndex)
					pUIManager->GetQuestBookComplete()->close();
				BOOL bDeleted = pQuest->DelQuestList(questIndex, pData->IsQuestComplete());
				pQuest->RemoveSelectedQuest(questIndex);
				if (!bDeleted)//�����°� ������
				{
					bDeleted = pQuest->DelQuestList(questIndex, !pData->IsQuestComplete());
					ASSERTALWAYS("Somthing is wrong, client fail delete quest from list");
					if (!bDeleted)
					{
						ASSERTALWAYS("Somthing is wrong, unknown quest index");
					}
				}
				CQuestSystem::Instance().SetQuestAllow(questIndex, CQuestSystem::QAT_GIVEUP);

				INDEX startType = pData->GetStartType();
				INDEX startData = pData->GetStartData();
				INDEX prizeNPCIndex = pData->GetPrizeNPCIndex();
				CQuestSystem::Instance().Remove(questIndex);
				if (startType == QSTART_NPC)
					ACTORMGR()->RefreshNPCQuestMark(startData);
				ACTORMGR()->RefreshNPCQuestMark(prizeNPCIndex);

				// ���ֱ��� �����൵�� �����ϰ� ���͵� ���� ����â�� �״�� �ִ� ���� [12/27/2006 Theodoric]
				if (questIndex == 14) // ���ֱ���
				{
					_pNetwork->EndRescueNPC();
				}
			}
			else
			{
				CQuestSystem::Instance().DeleteCurrentRequest();
				CQuestSystem::Instance().SetQuestAllow(questIndex, CQuestSystem::QAT_GIVEUP);
				ACTORMGR()->RefreshNPCQuestMark(pUIManager->GetQuestAccept()->GetTargetIndex());
				pUIManager->GetQuestAccept()->close();
			}
		}
		pUIManager->GetQuestBookList()->RefreshQuestListNew();
		pUIManager->GetQuestBookList()->UpdateQuestContent(-1);
	}
	break;

	case MSG_QUEST_PRIZE:
	{
		//TODO : NewQuestSystem
		INDEX questIndex;
		(*istr) >> questIndex;

		pUIManager->GetQuestBookComplete()->close();

		CQuestDynamicData* pData = CQuestSystem::Instance().GetDynamicDataByQuestIndex(questIndex);
		if (pData)
		{
			if (pData->GetQuestType1() != QTYPE_KIND_TUTORIAL)
			{
				CTString		strMessage;
				strMessage.PrintF("%s", pData->GetName());

				INDEX iPrizeNPCIndex = pData->GetPrizeNPCIndex();
				if (CQuestSystem::Instance().Remove(questIndex))
				{
					BOOL bDeleted = pQuest->DelQuestList(questIndex, TRUE);
					pQuest->RemoveSelectedQuest(questIndex);
					if (!bDeleted)//�����°� ������
					{
						bDeleted = pQuest->DelQuestList(questIndex, FALSE);
						ASSERTALWAYS("Somthing is wrong, client fail delete quest from list");
						if (!bDeleted)
						{
							ASSERTALWAYS("Somthing is wrong, unknown quest index");
						}
					}
				}

				pUIManager->GetQuestBookList()->RefreshQuestListNew();
				pUIManager->GetQuestBookList()->UpdateQuestContent(-1);
				CQuestSystem::Instance().SetQuestAllow(questIndex, CQuestSystem::QAT_ALREADY_DONE);
				ACTORMGR()->RefreshNPCQuestMark(iPrizeNPCIndex);

				INDEX iContactNpc = CQuestSystem::Instance().SearchContactQuestIndex(questIndex);

				if (iContactNpc > 0 && iContactNpc != iPrizeNPCIndex)
				{
					ACTORMGR()->RefreshNPCQuestMark(iContactNpc);
				}
			}
			// FIXME : Ʃ�丮�� ����Ʈ�� Ư���ؼ� �̷��� ó����...
			else
			{
				CTString		strMessage;
				strMessage.PrintF("%s", pData->GetName());

				// Create skill learn message box
				pUIManager->CreateMessageBoxL(strMessage, UI_CHARACTERINFO, MSGLCMD_QUEST_TUTORIAL);

				strMessage.PrintF("%s", pData->GetDesc2());
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_TUTORIAL, TRUE, strMessage);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_TUTORIAL, FALSE, _S(191, "Ȯ��"), 0);
			}
		}
		else
		{
			ASSERTALWAYS("MSG_QUEST_PRIZE : Quest Index is abnormal. Server or Client has wrong quest index.");
		}
	}
	break;

	case MSG_QUEST_ERROR:
	{
		//TODO : NewQuestSystem
		SBYTE	sbErrType;
		(*istr) >> sbErrType;

		if (CQuestSystem::Instance().GetCurrentRequest())
			CQuestSystem::Instance().DeleteCurrentRequest();

		pUIManager->GetQuest()->QuestError(sbErrType);
	}
	break;

	case MSG_QUEST_FAIL:
	{
		//TODO : NewQuestSystem
		INDEX questIndex;
		(*istr) >> questIndex;

		CQuestDynamicData* pData = CQuestSystem::Instance().GetDynamicDataByQuestIndex(questIndex);
		if (pData)
		{
			pUIManager->GetQuest()->SetCurQuest(questIndex);
			INDEX startType = pData->GetStartType();
			INDEX startData = pData->GetStartData();
			INDEX prizeNPCIndex = pData->GetPrizeNPCIndex();
			//CQuestSystem::Instance().SetQuestAllow(questIndex, CQuestSystem::QAT_GIVEUP);
			if (_pNetwork->MyCharacterInfo.hp != 0)
			{
				pUIManager->CloseMessageBox(MSGCMD_QUEST_FAIL);
				CTString		strMessage;
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(99, "����Ʈ"), UMBS_OK, UI_QUEST, MSGCMD_QUEST_FAIL);
				strMessage.PrintF(_S(669, "[%s] ����Ʈ�� �����߽��ϴ�."), pData->GetName());
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
			else
			{
				CTString strQuestFail;// = "����Ʈ�� �����߽��ϴ�.";		
				strQuestFail.PrintF(_S(669, "[%s] ����Ʈ�� �����߽��ϴ�."), pData->GetName());
				_pNetwork->ClientSystemMessage(strQuestFail);
			}

			// �̱۴����� ��쿡�� ��ư�� ���������� ��������.
			if (!_pNetwork->m_bSingleMode)
			{
				BOOL isComplete = pData->IsQuestComplete();
				if (CQuestSystem::Instance().Remove(questIndex))
				{
					BOOL bDeleted = pQuest->DelQuestList(questIndex, isComplete);
					pQuest->RemoveSelectedQuest(questIndex);
					if (!bDeleted)//�����°� ������
					{
						bDeleted = pQuest->DelQuestList(questIndex, !isComplete);
						ASSERTALWAYS("Somthing is wrong, client fail delete quest from list");
						if (!bDeleted)
						{
							ASSERTALWAYS("Somthing is wrong, unknown quest index");
						}
					}
				}
				pUIManager->GetQuestBookList()->RefreshQuestListNew();
				pUIManager->GetQuestBookList()->UpdateQuestContent(-1);

				if (pUIManager->GetQuestBookComplete()->GetCurrIdx() == questIndex)
					pUIManager->GetQuestBookComplete()->close();
				CQuestSystem::Instance().SetQuestAllow(questIndex, CQuestSystem::QAT_ALLOW);

				if (startType == QSTART_NPC)
					ACTORMGR()->RefreshNPCQuestMark(startData);
				ACTORMGR()->RefreshNPCQuestMark(prizeNPCIndex);
			}

			if (questIndex == 14) // ���� ����
			{
				_pNetwork->EndRescueNPC();
			}
		}
	}
	break;

	case MSG_QUEST_DONE_LIST:
	{
		INDEX completeQuestCount;
		(*istr) >> completeQuestCount;
		for (int i = 0; i < completeQuestCount; ++i)
		{
			INDEX completeQuestIndex;
			(*istr) >> completeQuestIndex;
			CQuestSystem::Instance().SetQuestAllow(completeQuestIndex, CQuestSystem::QAT_ALREADY_DONE);
		}
	} break;
	case MSG_QUEST_ABANDON_LIST:
	{
		INDEX giveupQuestCount;
		(*istr) >> giveupQuestCount;
		for (int i = 0; i < giveupQuestCount; ++i)
		{
			INDEX giveupQuestIndex;
			(*istr) >> giveupQuestIndex;
			CQuestSystem::Instance().SetQuestAllow(giveupQuestIndex, CQuestSystem::QAT_GIVEUP);
		}
	} break;
	case MSG_QUEST_FORCE_GIVEUP:
	{
		INDEX questIndex;
		(*istr) >> questIndex;
		CQuestDynamicData* pData = CQuestSystem::Instance().GetDynamicDataByQuestIndex(questIndex);
		if (pData != NULL)
		{
			//Ȯ��â
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(99, "����Ʈ"), UMBS_OK, UI_QUESTBOOK_LIST, MSGCMD_QUEST_NOTIFY);
			CTString strMessage;
			strMessage.PrintF(_S(1756, "%s ����Ʈ�� ���� ���� ������ ���� �����˴ϴ�."), pData->GetName());
			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);

			//�����ؼ� �����ִ� â �ݱ� �� ����Ʈ ���� ����
			if (pUIManager->GetQuestBookComplete()->GetCurrIdx() == questIndex)
				pUIManager->GetQuestBookComplete()->close();
			BOOL bDeleted = pQuest->DelQuestList(questIndex, pData->IsQuestComplete());
			pQuest->RemoveSelectedQuest(questIndex);
			if (!bDeleted)//�����°� ������
			{
				bDeleted = pQuest->DelQuestList(questIndex, !pData->IsQuestComplete());
				ASSERTALWAYS("Somthing is wrong, client fail delete quest from list");
				if (!bDeleted)
				{
					ASSERTALWAYS("Somthing is wrong, unknown quest index");
				}
			}
			CQuestSystem::Instance().SetQuestAllow(questIndex, CQuestSystem::QAT_GIVEUP);

			//npc�� ����Ʈ ��ũ ����
			INDEX startType = pData->GetStartType();
			INDEX startData = pData->GetStartData();
			INDEX prizeNPCIndex = pData->GetPrizeNPCIndex();
			CQuestSystem::Instance().Remove(questIndex);
			if (startType == QSTART_NPC)
				ACTORMGR()->RefreshNPCQuestMark(startData);
			ACTORMGR()->RefreshNPCQuestMark(prizeNPCIndex);
		}
		//����Ʈ ����Ʈ ����
		pUIManager->GetQuestBookList()->RefreshQuestListNew();
		pUIManager->GetQuestBookList()->UpdateQuestContent(-1);
	} break;

	case MSG_QUEST_COLLECT:
	{
		LONG npcIdx, charIdx, itemIdx;
		(*istr) >> npcIdx >> charIdx >> itemIdx;

		// 	>	0 : NPC�� ����ϰ� itemdbindex�� ������
		//	==	0 : NPC�� ����ϰ� ������ ���� ����
		//	<   0 : NPC�� �״�� ������ ���� ����

		if (itemIdx >= 0)
		{
			// npc�� ���� �Ѥ�;;
			CEntity* penEntity = NULL;
			CEntity* penTargetEntity = NULL;

			if (_pNetwork->SearchEntityByNetworkID(npcIdx, MSG_CHAR_NPC, penTargetEntity))
			{
				((CMovableModelEntity*)penTargetEntity)->DeathNow();
			}

			//  ���� ����, Ż���� ���� ����
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->CancelProduct();
			pUIManager->GetSelectResource()->SetKeyMove(true);
		}

	}
	break;
	// [100208: selo] ���� ����Ʈ ����
	case MSG_QUEST_RESTORE_ABANDON:
	{
		INDEX storeCount;
		INDEX questIndex = -1;
		CQuestDynamicData* pData = NULL;
		INDEX startType = -1;
		INDEX startData = -1;
		INDEX prizeNPCIndex = -1;

		(*istr) >> storeCount;
		pQuest->ClearAllRestoreList();

		for (int i = 0; i < storeCount; i++)
		{
			(*istr) >> questIndex;

			CQuestDynamicData QuestDD(CQuestSystem::Instance().GetStaticData(questIndex));

			pQuest->AddRestoreQuestList(questIndex, QuestDD.GetNeedMinLevel());

			startType = QuestDD.GetStartType();
			startData = QuestDD.GetStartData();
			prizeNPCIndex = QuestDD.GetPrizeNPCIndex();

			CQuestSystem::Instance().SetQuestAllow(questIndex, CQuestSystem::QAT_ALLOW);

			if (startType == QSTART_NPC)
				ACTORMGR()->RefreshNPCQuestMark(startData);
			ACTORMGR()->RefreshNPCQuestMark(prizeNPCIndex);
		}

		pQuest->SortRestoreQuest();

		pUIManager->GetQuestRestore()->open();
		pUIManager->GetInitJob()->CloseInitJob();
	}
	break;

	case MSG_QUEST_PBI_USE_REQ:
	{
		//we need to assert if the user  is pressing ok and just sending the result to the server nothing more.
		// if its existing close it otherwise it will open alot of windows

		if (pUIManager->DoesMessageBoxExist(MSGCMD_QUEST_PBI_USE_REP))
			pUIManager->CloseMessageBox(MSGCMD_QUEST_PBI_USE_REP);

		CUIMsgBox_Info	MsgBoxInfo;
		CTString strMessage;
		MsgBoxInfo.SetMsgBoxInfo(_S(8394, "You are not using a Platinum Blessed Iris would you like to use one to obtain x3 Quest EXP? Selecting cancel will turn in quest like normal."), UMBS_OKCANCEL, UI_NONE, MSGCMD_QUEST_PBI_USE_REP);
		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);


	}
	break;

	default:
	{
		//ASSERTALWAYS("Not defined MSG_QUEST_TYPE.");
	}
	break;
	}
}

// ----------------------------------------------------------------------------
// Name : ReceivePkMessage()
// Desc : 
// ----------------------------------------------------------------------------			
void CSessionState::ReceivePkMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;

	switch (ubType)
	{
	case MSG_PK_ITEMSEAL:
	{
		SBYTE sbTab;
		SBYTE sbIdx;
		ULONG ulIndex;
		ULONG ulFlag;
		(*istr) >> sbTab;
		(*istr) >> sbIdx;
		(*istr) >> ulIndex;
		(*istr) >> ulFlag;

		const int iIndex = _pNetwork->MySlotItem[sbTab][sbIdx].Item_Index;
		//CItemData& ID = _pNetwork->GetItemData(iIndex);
		CTString strItemSealed;
		strItemSealed.PrintF(_S2(670, _pNetwork->GetItemName(iIndex), "[%s]<��> ���εǾ����ϴ�."), _pNetwork->GetItemName(iIndex));
		_pNetwork->ClientSystemMessage(strItemSealed);
	}
	break;
	case MSG_PK_RECOVER_ITEMSEAL:	// item ���� ����
	{
		SBYTE sbTab;
		SBYTE sbIdx;
		SLONG slIndex;
		SLONG slFlag;
		(*istr) >> sbTab;
		(*istr) >> sbIdx;
		(*istr) >> slIndex;
		(*istr) >> slFlag;

		const int iIndex = _pNetwork->MySlotItem[sbTab][sbIdx].Item_Index;
		//CItemData& ID = _pNetwork->GetItemData(iIndex);
		CTString strItemSealed;
		strItemSealed.PrintF(_S2(672, _pNetwork->GetItemName(iIndex), "[%s]<��> ������ �����Ǿ����ϴ�."), _pNetwork->GetItemName(iIndex));
		_pNetwork->ClientSystemMessage(strItemSealed);
		//CUIManager::getSingleton()->GetRemission()->InitRemission();
	}
	break;
	case MSG_PK_TARGET_SHOWHP: // WSS_PK_TARGET_HP 070726
	{
		SBYTE	sbON;
		(*istr) >> sbON;
		CUIManager::getSingleton()->GetTargetInfoUI()->ShowPKTargetHP((BOOL)sbON);
	}
	break;
	case MSG_PK_ERROR:
	{
		SBYTE	sbError;
		(*istr) >> sbError;

		//CUIManager::getSingleton()->GetRemission()->RemissionError( sbError );
	}
	break;
	default:
	{
		ASSERTALWAYS("Not defined MSG_QUEST_TYPE.");
	}
	break;
	}
}

// ----------------------------------------------------------------------------
// Name : ReceivePersonalShopMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceivePersonalShopMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;

	_pNetwork->m_iNetworkResponse[MSG_PERSONALSHOP] = 0;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (ubType)
	{
	case MSG_PERSONALSHOP_ERROR:
	{
		SBYTE	sbError;
		(*istr) >> sbError;

		CTString strMessage;
		switch (sbError)
		{
			//case MSG_PERSONALSHOP_ERROR_OK:
			//	strMessage.PrintF(_S( 771, "����" ));		
			//	break;
		case MSG_PERSONALSHOP_ERROR_INSUFF_SKILL:		// ��ų ���
			strMessage.PrintF(_S(772, "�ŷ��� ��û�� ĳ���Ͱ� ��ų�� ��� ���Դϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_INSUFF_WARP:		// ����
			strMessage.PrintF(_S(773, "�ŷ��� ��û�� ĳ���Ͱ� ����(�̵���ġ) ���Դϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_INSUFF_EXCHANGE:	// ��ȯ ��
			strMessage.PrintF(_S(774, "�ŷ��� ��û�� ĳ���Ͱ� ��ȯ ���Դϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_INSUFF_ALREADY:		// ���� ������
			strMessage.PrintF(_S(775, "�ŷ��� ��û�� ĳ���Ͱ� �̹� ���λ��� �ŷ����Դϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_INSUFF_MONEY:		// ������ ���λ������� �ŷ��ϰ��� �Ҷ�
			strMessage.PrintF(_S(776, "������ ���λ������� �ŷ��� �� �����ϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_INSUFF_ETC:			// ������ ���� ���� ����(��ų���/����/��Ŷ������� ���)
			strMessage.PrintF(_S(777, "���λ��� �ŷ��� ��ҵǾ����ϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_DUPLICATION:		// �ߺ� ���
			strMessage.PrintF(_S(778, "�������� �ߺ� ��� �Ǿ����ϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_NOTSELL:			// ��� ĳ���Ͱ� �Ǹ� ������ �ƴ� ��
			strMessage.PrintF(_S(779, "��� ĳ���Ͱ� �Ǹ� ������ �ƴմϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_NOTPACKAGE:			// ��� ĳ���Ͱ� ��Ű�� �ǸŰ� �ƴ� ��
			strMessage.PrintF(_S(780, "��� ĳ���Ͱ� ��Ű�� �Ǹ����� �ƴմϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_NOTFOUND:			// ��� ĳ���Ͱ� ���� ��
			strMessage.PrintF(_S(781, "��� ĳ���Ͱ� �������� �ʽ��ϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_MONEY:				// ������ ����
			strMessage.PrintF(_S(782, "������ �����Ͽ� �ŷ��� �� �� �����ϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_COUNT:			// ��� ���λ������� ��û �Ǹ�/���� ī��Ʈ�� Ŭ��
			strMessage.PrintF(_S(783, "��û�� ������ ������ �ùٸ��� �ʽ��ϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_CANTPREMIUM:	// ������ �������� ��Ű�� ���� ���� �Ұ�
			strMessage.PrintF(_S(784, "�������� �����Ͽ� ��Ű�� ������ ������ �� �����ϴ�."));
			break;
			// Date : 2005-02-01,   By Lee Ki-hwan
		case MSG_PERSONALSHOP_ERROR_BUY_FULLINVENTORY:	// �κ��丮�� ���� ���� ������ ������ �� �����ϴ�.
			strMessage.PrintF(_S(862, "�κ��丮�� ���� ���� ������ ������ �� �����ϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_AREA:
			strMessage.PrintF(_S(785, "���λ����� ������ �� ���� �����Դϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_ANYMORE_PET:
			strMessage.PrintF(_S(2582, "�� ���� ������ �Ѿ ��ҵǾ����ϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_NOSPACE:
			strMessage.PrintF(_S(265, "�κ��丮 ������ �����մϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_CANNOT_USE:
			strMessage.PrintF(_S(5030, "�̿��� �� ���� ���λ����Դϴ�."));
			break;
		case MSG_PERSONALSHOP_ERROR_DELAY:
			strMessage.PrintF(_S(9389, "�̿��� �� ���� ���λ����Դϴ�."));
			break;
		}
		_pNetwork->ClientSystemMessage(strMessage, SYSMSG_ERROR);
		pUIManager->SetCSFlagOff(CSF_PERSONALSHOP);
	}
	break;
	case MSG_PERSONALSHOP_CHANGE:
	{
		LONG	lChaIndex;
		SBYTE	sbShopType;
		(*istr) >> lChaIndex;
		(*istr) >> sbShopType;

		//// ���� ���� ��ȭ			: charindex(n) shoptype(c)
		if (lChaIndex == _pNetwork->MyCharacterInfo.index)
		{
			_pNetwork->MyCharacterInfo.sbShopType = sbShopType;
			if (sbShopType == PST_NOSHOP)
			{
				CTString strSysMessage;
				strSysMessage.PrintF(_S(786, "������ �ݾҽ��ϴ�."));
				_pNetwork->ClientSystemMessage(strSysMessage);

				pUIManager->SetCSFlagOff(CSF_PERSONALSHOP);
				pUIManager->GetPersonalShop()->ChangeShopState(FALSE);
				_pNetwork->MyCharacterInfo.ShopMsg.Reset();
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->StandDown(FALSE);
			}
		}
		// Ÿĳ������ ���� ���� ��ȭ.
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lChaIndex);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTarget->cha_sbShopType = sbShopType;
				if (sbShopType == PST_NOSHOP)
				{
					pTarget->ShopMsg.Reset();
					if (pUIManager->GetPersonalShop()->EndBuyShop(lChaIndex))
					{
						CTString strSysMessage;
						strSysMessage.PrintF(_S(3075, "%s ���� ���λ����� �ݾҽ��ϴ�."), pTarget->m_strName.c_str());
						_pNetwork->ClientSystemMessage(strSysMessage);
					}
				}

				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetShopData(pTarget->GetCIndex(), sbShopType);
			}
		}
	}
	break;
	case MSG_PERSONALSHOP_SELL_LIST:
	{
		LONG	lChaIndex;
		(*istr) >> lChaIndex;
		pUIManager->GetPersonalShop()->ReceivePersonalShopItemList(lChaIndex, &(*istr));
	}
	break;
	case MSG_PERSONALSHOP_BUY:
	{
		pUIManager->GetPersonalShop()->ReceivePersonalShopItemUpdate(&(*istr));
	}
	break;
	case MSG_PERSONALSHOP_SELL_START:
	{
		// charindex(n) shoptype(c) shopname(str)
		LONG lChaIndex;
		SBYTE sbShopType;
		CTString strShopName;

		(*istr) >> lChaIndex;
		(*istr) >> sbShopType;
		(*istr) >> strShopName;

		if (lChaIndex == _pNetwork->MyCharacterInfo.index)
		{
			pUIManager->GetPersonalShop()->ChangeShopState(TRUE);
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->StandDown(TRUE);
			_pNetwork->MyCharacterInfo.sbShopType = sbShopType;
			_pNetwork->MyCharacterInfo.ShopMsg.SetChatMsg(strShopName);

			CTString strSysMessage;
			strSysMessage.PrintF(_S(1037, "[%s] ������ �������ϴ�."), strShopName);
			_pNetwork->ClientSystemMessage(strSysMessage);
			pUIManager->SetCSFlagOn(CSF_PERSONALSHOP);
		}
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lChaIndex);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTarget->cha_sbShopType = sbShopType;
				pTarget->ShopMsg.SetChatMsg(strShopName);

				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetShopData(pTarget->GetCIndex(), sbShopType);
			}
		}
	}
	break;
	}
}
// ----------------------------------------------------------------------------
// Name : ReceivePersonalShopMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveCashPersonShopMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (ubType)
	{
	case MSG_ALTERNATEMERCHANT_ERROR:
	{
		SBYTE	sbError;
		(*istr) >> sbError;

		CTString strMessage;
		switch (sbError)
		{
			//case MSG_PERSONALSHOP_ERROR_OK:
			//	strMessage.PrintF(_S( 771, "����" ));		
			//	break;
		case MSG_ALTERNATEMERCHANT_ERROR_INSUFF_SKILL:		// ��ų ���
			strMessage.PrintF(_S(772, "�ŷ��� ��û�� ĳ���Ͱ� ��ų�� ��� ���Դϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_INSUFF_WARP:		// ����
			strMessage.PrintF(_S(773, "�ŷ��� ��û�� ĳ���Ͱ� ����(�̵���ġ) ���Դϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_INSUFF_EXCHANGE:	// ��ȯ ��
			strMessage.PrintF(_S(774, "�ŷ��� ��û�� ĳ���Ͱ� ��ȯ ���Դϴ�."));
			break;
			//			case MSG_ALTERNATEMERCHANT_ERROR_INSUFF_ALREADY:		// ���� ������
			//				strMessage.PrintF(_S( 775, "�ŷ��� ��û�� ĳ���Ͱ� �̹� ���λ��� �ŷ����Դϴ�." ));		
			//				break;
		case MSG_ALTERNATEMERCHANT_ERROR_INSUFF_MONEY:		// ������ ���λ������� �ŷ��ϰ��� �Ҷ�
			strMessage.PrintF(_S(776, "������ ���λ������� �ŷ��� �� �����ϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_INSUFF_ETC:			// ������ ���� ���� ����(��ų���/����/��Ŷ������� ���)
			strMessage.PrintF(_S(777, "���λ��� �ŷ��� ��ҵǾ����ϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_DUPLICATION:		// �ߺ� ���
			strMessage.PrintF(_S(778, "�������� �ߺ� ��� �Ǿ����ϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_NOTSELL:			// ��� ĳ���Ͱ� �Ǹ� ������ �ƴ� ��
			strMessage.PrintF(_S(779, "��� ĳ���Ͱ� �Ǹ� ������ �ƴմϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_NOTPACKAGE:			// ��� ĳ���Ͱ� ��Ű�� �ǸŰ� �ƴ� ��
			strMessage.PrintF(_S(780, "��� ĳ���Ͱ� ��Ű�� �Ǹ����� �ƴմϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_NOTFOUND:			// ��� ĳ���Ͱ� ���� ��
			strMessage.PrintF(_S(781, "��� ĳ���Ͱ� �������� �ʽ��ϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_MONEY:				// ������ ����
			strMessage.PrintF(_S(782, "������ �����Ͽ� �ŷ��� �� �� �����ϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_COUNT:			// ��� ���λ������� ��û �Ǹ�/���� ī��Ʈ�� Ŭ��
			strMessage.PrintF(_S(783, "��û�� ������ ������ �ùٸ��� �ʽ��ϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_CANTPREMIUM:	// ������ �������� ��Ű�� ���� ���� �Ұ�
			strMessage.PrintF(_S(784, "�������� �����Ͽ� ��Ű�� ������ ������ �� �����ϴ�."));
			break;
			// Date : 2005-02-01,   By Lee Ki-hwan
		case MSG_ALTERNATEMERCHANT_ERROR_BUY_FULLINVENTORY:	// �κ��丮�� ���� ���� ������ ������ �� �����ϴ�.
			strMessage.PrintF(_S(862, "�κ��丮�� ���� ���� ������ ������ �� �����ϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_AREA:
			strMessage.PrintF(_S(785, "���λ����� ������ �� ���� �����Դϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_ANYMORE_PET:
			strMessage.PrintF(_S(2582, "�� ���� ������ �Ѿ ��ҵǾ����ϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_NOSPACE:
			strMessage.PrintF(_S(265, "�κ��丮 ������ �����մϴ�."));
			break;
		case MSG_ALTERNATEMERCHANT_ERROR_NOCOLLECT_ITEM:
			strMessage.PrintF(_s("ȸ�� ���� ���� �������� �����մϴ�."));
			break;
		case  MSG_ALTERNATEMERCHANT_ERROR_TIMEOVER:
			strMessage.PrintF(_s("�Ǹ� ���� �ð��� ���� �Ǿ����ϴ�. �Ǹ����� �������� �Ǹ� ������ȸ ȸ��Բ� ȸ�� �Ͻñ� �ٶ��ϴ�."));
			break;

		}
		_pNetwork->ClientSystemMessage(strMessage, SYSMSG_ERROR);
		pUIManager->SetCSFlagOff(CSF_PERSONALSHOP);
	}
	break;
	case MSG_ALTERNATEMERCHANT_CHANGE:
	{
		LONG	lChaIndex;
		SBYTE	sbShopType;
		(*istr) >> lChaIndex;
		(*istr) >> sbShopType;

		//// ���� ���� ��ȭ			: charindex(n) shoptype(c)
		if (lChaIndex == _pNetwork->MyCharacterInfo.index)
		{
			_pNetwork->MyCharacterInfo.sbShopType = sbShopType;
			if (sbShopType == PST_NOSHOP)
			{
				CTString strSysMessage;
				strSysMessage.PrintF(_S(786, "������ �ݾҽ��ϴ�."));
				_pNetwork->ClientSystemMessage(strSysMessage);

				pUIManager->SetCSFlagOff(CSF_PERSONALSHOP);
				pUIManager->GetPersonalShop()->ChangeShopState(FALSE);
				_pNetwork->MyCharacterInfo.ShopMsg.Reset();
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->StandDown(FALSE);
			}
		}
		// Ÿĳ������ ���� ���� ��ȭ.
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lChaIndex);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTarget->cha_sbShopType = sbShopType;

				if (sbShopType == PST_NOSHOP)
				{
					pTarget->ShopMsg.Reset();
					if (pUIManager->GetPersonalShop()->EndBuyShop(lChaIndex))
					{
						CTString strSysMessage;
						strSysMessage.PrintF(_S(3075, "%s ���� ���λ����� �ݾҽ��ϴ�."), pTarget->m_strName.c_str());
						_pNetwork->ClientSystemMessage(strSysMessage);
					}
				}

				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetShopData(pTarget->GetCIndex(), sbShopType);
			}
		}
	}
	break;
	case MSG_ALTERNATEMERCHANT_SELL_LIST:
	{
		LONG	lChaIndex;
		(*istr) >> lChaIndex;
		pUIManager->GetPersonalShop()->ReceivePersonalShopItemList(lChaIndex, &(*istr));
	}
	break;
	case MSG_ALTERNATEMERCHANT_BUY:
	{
		pUIManager->GetPersonalShop()->ReceivePersonalShopItemUpdate(&(*istr));
	}
	break;
	case MSG_ALTERNATEMERCHANT_SELL_START:
	{
		// charindex(n) shoptype(c) shopname(str)
		LONG lChaIndex;
		SBYTE sbShopType;
		CTString strShopName;

		(*istr) >> lChaIndex;
		(*istr) >> sbShopType;
		(*istr) >> strShopName;

		if (lChaIndex == _pNetwork->MyCharacterInfo.index)
		{
			pUIManager->GetPersonalShop()->ChangeShopState(TRUE);
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->StandDown(TRUE);
			_pNetwork->MyCharacterInfo.sbShopType = sbShopType;
			_pNetwork->MyCharacterInfo.ShopMsg.SetChatMsg(strShopName);

			CTString strSysMessage;
			strSysMessage.PrintF(_S(1037, "[%s] ������ �������ϴ�."), strShopName);
			_pNetwork->ClientSystemMessage(strSysMessage);
			pUIManager->SetCSFlagOn(CSF_PERSONALSHOP);
		}
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lChaIndex);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTarget->cha_sbShopType = sbShopType;
				pTarget->ShopMsg.SetChatMsg(strShopName);

				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetShopData(pTarget->GetCIndex(), sbShopType);
			}
		}
	}
	break;
	}
}

// ----------------------------------------------------------------------------
// Name : SetRecentServer()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::SetRecentServer(int iRecentGroup, int iRecentServer)
{
	m_iRecentGroup = iRecentGroup;
	m_iRecentServer = iRecentServer;
}

// ----------------------------------------------------------------------------
// Name : ReceiveLegitimateMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveLegitimateMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;
	SBYTE	targettype;
	SLONG	targetindex;

	(*istr) >> ubType;
	(*istr) >> targettype;
	(*istr) >> targetindex;

	if (targettype != MSG_CHAR_PC)
	{
		return;
	}

	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetLegit(ubType, targetindex);
}

// ----------------------------------------------------------------------------
// Name : ReceiveWareHouseMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveWareHouseMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (ubType)
	{
	case MSG_STASH_ERROR_CODE:
	{
		SBYTE	sbError;
		(*istr) >> sbError;

		CTString strMessage;
		switch (sbError)
		{
		case MSG_STASH_ERROR_OK:						// ����
			//	strMessage.PrintF( _S( 771, "����" ));		
			return;
			break;
		case MSG_STASH_ERROR_CANNOT_STATE:
			strMessage.PrintF(_S(850, "â�� �̿��� �� �� ���� �����Դϴ�."));
			break;
		case MSG_STASH_ERROR_NOTCOMPLETE:				// ���� â�� ��û�� ������ ���� �ʾ���
			strMessage.PrintF(_S(851, "������ â�� ��û�� ������ ���� �ʾҽ��ϴ�."));
			break;
		case MSG_STASH_ERROR_SEALED:					// â�� ��� ��� ����
			strMessage.PrintF(_S(852, "â���� ��� ��� �����Դϴ�."));
			break;
		case MSG_STASH_ERROR_WRONG_PASSWORD:			// ��ȣ Ʋ��
			strMessage.PrintF(_S(853, "��ȣ�� �ùٸ��� �ʽ��ϴ�."));
			break;
		case MSG_STASH_ERROR_WRONG_PACKET:				// ��Ŷ ���� ����
			strMessage.PrintF(_S(3257, "��û�� �۾��� ���� �Ͽ����ϴ�."));
			break;
		case MSG_STASH_ERROR_MONEY:						// �� ����
			strMessage = _S(306, "������ �����մϴ�.");
			break;
		case MSG_STASH_ERROR_STASH_FULL:				// â�� ���� ��
			strMessage.PrintF(_S(855, "â���� ���� á���ϴ�."));
			break;
		case MSG_STASH_ERROR_INVENTORY_FULL:			// �κ��丮 ���� �ʰ��� ã�� �� ����
			strMessage.PrintF(_S(857, "�κ��丮�� �� ���� ã�� �� �����ϴ�."));
			break;
		case MSG_STASH_ERROR_WRONG_CHAR:				// ��ȣ�� �߸��� ���ڰ� ��
			strMessage.PrintF(_S(809, "��ȣ�� �߸��� ���ڰ� �� �ֽ��ϴ�."));
			break;
		case MSG_STASH_ERROR_CANNOT_SEAL:				// ��ۼ� ����
			strMessage.PrintF(_S(810, "��� �� �����ϴ�."));
			break;
		case MSG_STASH_ERROR_ALREADY_SEAL:				// �̹� ���
			strMessage.PrintF(_S(811, "�̹� ����ֽ��ϴ�."));
			break;
		}

		pUIManager->CloseMessageBox(MSGCMD_WAREHOUSE_ERROR);
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(823, "â��"), UMBS_OK, UI_WARE_HOUSE, MSGCMD_WAREHOUSE_ERROR);
		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);

		pUIManager->GetWareHouseUI()->closeUI();
		pUIManager->GetSecurity()->ResetSecurity();
	}
	break;

	case MSG_STASH_KEEP_REP:
	{
		// �ñ�� ���				: keepcount(n) [itemdbindex(n) count(ll)]:keepcount
		LONG lKeepCount;
		CTString strMessage;
		(*istr) >> lKeepCount;
		for (int i = 0; i < lKeepCount; ++i)
		{
			LONG	lItemDBIndex;
			SQUAD	llCount;
			(*istr) >> lItemDBIndex;
			(*istr) >> llCount;
			//const char* szName = _pNetwork->GetItemData( lItemDBIndex ).GetName();
			const char* szName = _pNetwork->GetItemName(lItemDBIndex);
			CItemData* pItemData = _pNetwork->GetItemData(lItemDBIndex);

			CTString strCount;
			strCount.PrintF("%I64d", llCount);
			pUIManager->InsertCommaToString(strCount);

			if (pItemData->GetType() == CItemData::ITEM_ETC &&
				pItemData->GetSubType() == CItemData::ITEM_ETC_MONEY)
			{
				strMessage.PrintF(_S(1346, "������ %s�� �����Ͽ����ϴ�."), strCount);
			}
			else
			{
				strMessage.PrintF(_S(808, "%s�� %s�� �����Ͽ����ϴ�."), szName, strCount);
			}
			_pNetwork->ClientSystemMessage(strMessage);
		}
		//pUIManager->SetCSFlagOff( CSF_WAREHOUSE );
		pUIManager->GetWareHouseUI()->closeUI();
	}
	break;

	case MSG_STASH_TAKE_REP:
	{
		// ã�� ���				: takecount(n) [itemdbindex(n) count(ll)]:keepcount
		LONG lTakeCount;
		CTString strMessage;
		(*istr) >> lTakeCount;
		for (int i = 0; i < lTakeCount; ++i)
		{
			LONG	lItemDBIndex;
			SQUAD	llCount;
			(*istr) >> lItemDBIndex;
			(*istr) >> llCount;
		}
		pUIManager->GetWareHouseUI()->closeUI();
	}
	break;
#ifdef	STASH_PASSWORD		
	case MSG_STASH_DELETE_PASSWORD:
	{
		ResponseClient::doStashDeletePassword* pPack = reinterpret_cast<ResponseClient::doStashDeletePassword*>(istr->GetBuffer());

		pUIManager->GetSecurity()->ShowMsgBoxDelPW(pPack->result);
	}
	break;
#endif	// STASH_PASSWORD

	case MSG_STASH_CHECK_PASSWORD_REP:		// ��ȣ Ȯ�� ���.
	{
		// ��ȣ�� ����...
		pUIManager->CloseMessageBox(MSGCMD_NEW_PASSWORD);
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(1727, "���� �Է�"), UMBS_OK | UMBS_INPUTPASSWORD, UI_SECURITY, MSGCMD_NEW_PASSWORD);
		CTString	strMessage = _S(1738, "�� ��ȣ�� �Է��Ͽ� �ֽʽÿ�.");
		MsgBoxInfo.AddStringEx(strMessage, 0, 0, 0xF2F2F2FF, TEXT_CENTER);
		strMessage = _S(1729, "8��(���� ��������).");
		MsgBoxInfo.AddStringEx(strMessage, 1, 0, 0xF2F2F2FF, TEXT_CENTER);
		pUIManager->CreateMessageBox(MsgBoxInfo);

		CUIMessageBox* pMsgBox = pUIManager->GetMessageBox(MSGCMD_NEW_PASSWORD);
		ASSERT(pMsgBox != NULL && "Invalid Message Box!!!");
		//pMsgBox->GetInputBox().SetMaxChar(MAX_PASSWORD);
		pMsgBox->GetInputBox().SetMaxChar(8);
	}
	break;

	case MSG_STASH_SETTING_NEWPASSWORD_REP:	// ��ȣ ���� ���.
	{
		pUIManager->GetSecurity()->ResetSecurity();

		// ��ȣ ���� ���.
		SBYTE sbResult;
		(*istr) >> sbResult;
		if (sbResult == 0)
		{
			pUIManager->CloseMessageBox(MSGCMD_SECURITY_NOTIFY);
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(1774, "��ȣ ����"), UMBS_OK, UI_SECURITY, MSGCMD_SECURITY_NOTIFY);
			CTString	strMessage = _S(1775, "��ȣ�� �����Ǿ����ϴ�. â�� ���� ����� Ȱ��ȭ�˴ϴ�.");
			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
		else if (sbResult == 1)
		{
			pUIManager->CloseMessageBox(MSGCMD_SECURITY_NOTIFY);
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(1774, "��ȣ ����"), UMBS_OK, UI_SECURITY, MSGCMD_SECURITY_NOTIFY);
			CTString	strMessage = _S(1776, "�������� ���� ��ȣ�Դϴ�.");
			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
		else if (sbResult == 2)
		{
		}
	}
	break;

	case MSG_STASH_SEAL:
	{
		pUIManager->GetSecurity()->ResetSecurity();
	}
	break;
	}
}

// ----------------------------------------------------------------------------
// Name : ReceiveGuildMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveGuildMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (ubType)
	{
	case MSG_GUILD_ERROR:
	{
		SBYTE	sbError;
		(*istr) >> sbError;

		CTString strMessage;
		bool bSysMsg = false;
		switch (sbError)
		{
			//case MSG_GUILD_ERROR_OK:
			//	strMessage.PrintF( _S( 963, "����" ) );		
			//	break;

			// ��� ��Ʋ ���� ���� ó�� �κ�
			// UIGuildBattle���� �Ѳ����� ó�� �մϴ�.
		case MSG_GUILD_ERROR_BATTLE:
		{
			SBYTE	sbError;
			(*istr) >> sbError;
			pUIManager->GetGuildBattle()->GBErrorProcess(sbError);
		}
		return;
		case MSG_GUILD_ERROR_PACKET:
			ASSERTALWAYS("ȣ��Ǹ� �ȵǴ� �κ�");
			break;
		case MSG_GUILD_ERROR_CHARLEVEL:
			strMessage.PrintF(_S(965, "������ �����մϴ�."));
			break;
		case MSG_GUILD_ERRRO_SKILLPOINT:
			strMessage.PrintF(_S(966, "SP�� �����մϴ�."));
			break;
		case MSG_GUILD_ERROR_MONEY:
			strMessage.PrintF(_S(967, "������ �����մϴ�."));
			break;
		case MSG_GUILD_ERROR_ALREADYBOSS:
			strMessage.PrintF(_S(968, "�ٸ� ����� (��)���̱� ������ ��带 ������ �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_DUPNAME:
			strMessage.PrintF(_S(969, "�̹� �����ϴ� ��� �̸��Դϴ�."));
			break;
		case MSG_GUILD_ERROR_GUILDNAME:
			strMessage.PrintF(_S(970, "��� �̸��� ������ �ֽ��ϴ�."));
			break;
		case MSG_GUILD_ERROR_GAMESERVER:
			strMessage.PrintF(_S(971, "���� ������ ������ ���ؼ� ��带 ������ �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_NOGUILD:
			strMessage.PrintF(_S(972, "��忡 �������� �ʽ��ϴ�."));
			break;
		case MSG_GUILD_ERROR_NOTBOSS:
			strMessage.PrintF(_S(973, "������ �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_MAXLEVEL:
			strMessage.PrintF(_S(974, "�� �̻� ����� ����� ���� �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_CREATE_OK:
			strMessage.PrintF(_S(975, "��尡 ���� �Ǿ����ϴ�."));
			break;
			//return;
		case MSG_GUILD_ERROR_LEVELUP_OK:
			strMessage.PrintF(_S(976, "��尡 �±� �Ǿ����ϴ�."));
			break;
			//return;
		case MSG_GUILD_ERROR_BREAKUP_OK:
			strMessage.PrintF(_S(977, "��尡 �ػ� �Ǿ����ϴ�."));
			break;
			//return;
		case MSG_GUILD_ERROR_TARGET_NOBOSS:
			strMessage.PrintF(_S(978, "����� ������� �ƴϾ ���� ��û�� �� �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_TARGET_BUSY:
			strMessage.PrintF(_S(979, "������� �ٸ� ��û�� ó���ϰ� �ֽ��ϴ�. �ٽ� �õ��Ͻʽÿ�."));
			_pNetwork->GuildApplicantReject(FALSE);
			break;
		case MSG_GUILD_ERROR_SOURCE_BUSY:
			strMessage.PrintF(_S(980, "��� ���� ��û�߿� �ٸ� ��忡 ���� ��û�� �� �� �����ϴ�."));
			_pNetwork->GuildApplicantReject(FALSE);
			break;
		case MSG_GUILD_ERROR_FULLMEMBER:					// ��� ������ �ʰ�
			strMessage.PrintF(_S(981, "��忡 ������ �ʰ� �Ͽ� ������ �� �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_REGIST_OK:					// ���� ���� �Ϸ�
		{
			pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);
			strMessage.PrintF(_S(982, "��忡 ���ԵǾ����ϴ�."));
			break;
		}
		//return;
		case MSG_GUILD_ERROR_OUTBOSS:					// ������� Ż���Ϸ��� ����
			strMessage.PrintF(_S(983, "������� Ż���� �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_OUT_OK:						// Ż�� ����
			pUIManager->GetGuild()->ReceiveCorpsInfo(istr);
			strMessage.PrintF(_S(984, "��� Ż�� �Ϸ�Ǿ����ϴ�."));

			MY_INFO()->_guildmark.remove();
			UIMGR()->SetGuildMark();
			break;
			//return;
		case MSG_GUILD_ERROR_NOTFOUNDMEMBER:				// ����, �Ӹ�, ���ӵ�� ��� ����� ������
			strMessage.PrintF(_S(985, "�ش� ������ ã�� �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_CANTKICKBOSS:				// ������ ���� �Ҵ�
			strMessage.PrintF(_S(986, "���(��)���� ���� ����� �ƴմϴ�."));
			break;
		case MSG_GUILD_ERROR_KICK_OK:					// ���� ����
			pUIManager->GetGuild()->ReceiveCorpsInfo(istr);
			strMessage.PrintF(_S(987, "������ ���� �Ǿ����ϴ�."));
			break;
			//return;
		case MSG_GUILD_ERROR_CHANGE_BOSS_OK:
			strMessage.PrintF(_S(988, "������� ���� �Ǿ����ϴ�."));
			break;
			//return;
		case MSG_GUILD_ERROR_CANTOFFICER:				// ������̳� �ΰ��� �ٽ� �ΰ����� �Ӹ���
			strMessage.PrintF(_S(989, "�ش� ������ ���������� �Ӹ��� �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_APPOINT_OFFICER_OK:		// �ΰ� �Ӹ� ����
			strMessage.PrintF(_S(990, "�������� �Ӹ� �Ǿ����ϴ�."));
			break;
			//return;
		case MSG_GUILD_ERROR_FULLOFFICER:				// �ΰ� ���� ��
			strMessage.PrintF(_S(991, "�� �̻� �������� �Ӹ��� �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_NOTOFFICER:					// �ΰ��� �ƴ϶� ���� �Ұ�
			strMessage.PrintF(_S(992, "�������� �ƴ϶� ������ �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_FIRE_OFFICER_OK:			// ���� ����S
			strMessage.PrintF(_S(993, "������ �����Ͽ����ϴ�."));
			break;
			//return;
		case MSG_GUILD_ERROR_REGDELAY:					// ������ 10���� ������ �ʾ� Ż�� �Ұ�
			strMessage.PrintF(_S(6470, "��忡 �������� 10���� ������ �ʾ� Ż���� �� �����ϴ�. "));
			bSysMsg = true;
			break;
		case MSG_GUILD_ERROR_CANTKICK:
			strMessage.PrintF(_S(995, "�������� �������� ������ �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_CANNOT_REGIST_REQ_BATTLE:	// ����� �߿��� ���Խ�û �Ұ� 
			strMessage.PrintF(_S(1830, "�����Ϸ��� ��尡 ��� �������� ���� ���Խ�û�� �� �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_CANNOT_BREAK_BATTLE:		// ������ - ����� �� ��� ��ü �Ұ�
			strMessage.PrintF(_S(1831, "��� �������� ���� ��带 ��ü�� �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_CANNOT_KICK_BATTLE:		// ������ - ����� �� ���� �Ұ�   
			strMessage.PrintF(_S(1832, "��� �������� ���� ������ ������ �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_CANNOT_OUT_BATTLE:
			strMessage.PrintF(_S(1833, "��� �������� ���� ��带 Ż���� �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_CANNOT_BREAK_WAR:
			strMessage.PrintF(_S(2077, "���� ���� ��� ��ü�� �� �� �����ϴ�."));
			break;
			// WSS_NEW_GUILD_SYSTEM 070704
			// ---------------------------------------------------------------->>
		case MSG_NEW_GUILD_ERRROR_GUILDPOINT:				// ��� �������� ��� ����Ʈ ���� 
			strMessage.PrintF(_S(3884, "��� ����Ʈ�� �����մϴ�."));
			break;

		case MSG_NEW_GUILD_ERROR_SAME_INCLNE:				// ��� ������ ����
			strMessage.PrintF(_S(3885, "��� ������ �����ϴ�."));
			break;
		case MSG_NEW_GUILD_ERROR_CHANG_INCLINE:				// ��� ���� ���� ����
			strMessage.PrintF(_S(3886, "��� ���� ���濡 �����Ͽ����ϴ�."));
			break;
		case MSG_NEW_GUILD_ERROR_INCLINE_OK:				// ��� ���� ���� ����
			strMessage.PrintF(_S(3887, "��� ������ ����Ǿ����ϴ�."));
			break;
		case MSG_NEW_GUILD_ERROR_ADJUST_FAIL:				// ��� �������  ���� ���� ����
			strMessage.PrintF(_S(3888, "��� ���� ���뿡 �����Ͽ����ϴ�."));
			break;
		case MSG_NEW_GUILD_ERROR_ADJUST_OK:
			pUIManager->GetGuild()->AdjustGuildMemberInfo();
			pUIManager->GetGuild()->ReceiveCorpsInfo(istr);
			strMessage.PrintF(_S(3889, "��� ������ ����Ǿ����ϴ�."));
			break;
		case MSG_NEW_GUILD_NOTICE_UPDATE_ERROR_OK:			// ���ο� ��� ���� ������Ʈ ����
			strMessage.PrintF(_S(3890, "��� ���� ������Ʈ�� �Ϸ�Ǿ����ϴ�."));
			break;
		case MSG_NEW_GUILD_NOTICE_UPDATE_ERROR_FAIL:		// ���ο� ��� ���� ������Ʈ ����
			strMessage.PrintF(_S(3891, "��� ���� ������Ʈ�� �����Ͽ����ϴ�."));
			break;
		case MSS_NEW_GUILD_NOTICE_TRANSMISSION_ERROR_OK:
			strMessage.PrintF(_S(3892, "��� ���� �޽����� ���½��ϴ�."));
			break;
		case MSS_NEW_GUILD_NOTICE_TRANSMISSION_ERROR_FAIL:
			strMessage.PrintF(_S(3893, "��� ���� �޽��� ���޿� �����Ͽ����ϴ�."));
			break;
		case MSG_NEW_GUILD_SKILL_ERROR_NOTEXIST:
			strMessage.PrintF(_S(3894, "��� ��ų�� �����ϴ�."));
			break;
		case MSG_NEW_GUILD_NOTICE_ERROR_NOT_MESSAGE:
			strMessage.PrintF(_S(3895, "���� �޽����� �����ϴ�."));
			break;
		case MSG_NEW_GUILD_SKILL_LEARN_ERROR_OK:
			strMessage.PrintF(_S(3896, "��� ��ų�� �����Ͽ����ϴ�."));
			break;
		case MSG_NEW_GUILD_SKILL_LEARN_ERROR_LEVEL:
			strMessage.PrintF(_S(3897, "��� ������ �����մϴ�."));
			break;
		case MSG_NEW_GUILD_SKILL_ALEADY_LEARN:
			strMessage.PrintF(_S(3897, "��� ������ �����մϴ�."));
			break;
		case MSG_NEW_GUILD_STASH_AREADY_USE_NAS:
			strMessage.PrintF(_S(6511, "������� �ý����� ������̾ â������ ����� �� �����ϴ�."));
			break;
		case MSG_NEW_GUILD_POINT_AREADY_USE:
			strMessage.PrintF(_S(6510, "������� �ý����� ������̾ ��� ����Ʈ�� ����� �� �����ϴ�."));
			break;
		case MSG_GUILD_GRADE_EX_ERROR_WARCASTLE:
			strMessage.PrintF(_S(5332, "�����߿��� �� �� ���� �ൿ�Դϴ�."));
			break;
		case MSG_GUILD_GRADE_EX_ERROR_COUNT_OEVER:
			strMessage.PrintF(_S(5333, "������ �� �ִ� �ο� ���� �ʰ��Ͽ����ϴ�."));
			break;
		case MSG_GUILD_ERROR_CANNOT_BOSSCHANGE_FAIL:
			strMessage.PrintF(_S(5360, "���(��)���� ������ �� �����ϴ�."));
			break;
		case MSG_NEW_GUILD_ERROR_SYSTEM:
			strMessage.PrintF(_S(5513, "��� ��ũ ������ ������ �߻��Ͽ����ϴ�."));
			break;
		case MSG_NEW_GUILD_ERROR_OK_MARK_WND:
			pUIManager->GetGuildMark()->OpenGuildMarkEdit();
			return;
			// ==> 1107 ��� �ý��� ���� [trylord 11/12/28]
		case MSG_NEW_GUILD_ERROR_MASTER_KICK_RESERVE:
			strMessage.PrintF(_S(5618, "����� ���� ��� �����Դϴ�."));
			break;
		case MSG_NEW_GUILD_ERROR_MASTER_KICK_LAST_CONNECT:
			strMessage.PrintF(_S(5619, "����� �ֱ� ���� �������� 7���� ���� �ʾ� ������ �� �����ϴ�."));
			break;
		case MSG_NEW_GUILD_ERROR_MASTER_KICK_LAST_CHANGE:
			strMessage.PrintF(_S(5620, "����� �ֱ� ���� ���� 7���� ���� �ʾ� ������ �� �����ϴ�."));
			break;
		case MSG_NEW_GUILD_ERROR_MASTER_KICK_CANCEL_NOT_RESERVE:
			strMessage.PrintF(_S(5621, "���� ��� ���°� �ƴϱ� ������ ����� �� �����ϴ�."));
			break;
		case MSG_NEW_GUILD_ERROR_MASTER_KICK_DATA:
			strMessage.PrintF(_S(5622, "��� ������ ����"));
			break;
			// [2012/05/24 : Sora] ITS 7137 ��� ���� ������ �������� �߰�
		case MSG_NEW_GUILD_ERROR_NOT_EXIST_CHAR:
			strMessage.PrintF(_S(11, "�������� �ʴ� ĳ���� �Դϴ�."));
			break;
		case MSG_NEW_GUILD_ERROR_EXIST_GUILD:
			strMessage.PrintF(_S(866, "�̹� ��忡 ���ԵǾ� �ֽ��ϴ�.\n���� ���ԵǾ� �ִ� ��忡�� Ż���Ͽ� �ֽʽÿ�."));
			break;
		case MSG_GUILD_ERROR_CANNOT_REGIST_REQ_SERVERTRANS:
			break;
		case MSG_GUILD_ERROR_NOT_EXIST_NPC:
			strMessage.PrintF(_S(5913, "���డ���� NPC�� ������ �������� �ʽ��ϴ�."));
			break;
		case MSG_GUILD_ERROR_CANNOT_REGISTER_REQ_ZONE:
			strMessage.PrintF(_S(6090, "���� �������� ���� ������ ��� ����� �� ���� ����Դϴ�."));
			break;
		case MSG_GUILD_ERROR_ITEM:
			strMessage.PrintF(_S(280, "�������� �������� �ʾ� ��ų�� ������ �� �����ϴ�."));
			break;
		case MSG_GUILD_ERROR_CANNOT_BREAK_10DAYS:
			strMessage.PrintF(_S(6471, "��尡 �������� 10���� ������ �ʾ� ��ü�� �� �����ϴ�."));
			bSysMsg = true;
			break;
		case MSG_GUILD_ERROR_CONTRIBUTE_SET_SUCCESS:
			pUIManager->GetGuild()->AdjustMyDonateInfo();
			strMessage.PrintF(_S(3889, "��� ������ ����Ǿ����ϴ�."));
			bSysMsg = true;
			break;
		case MSG_GUILD_ERROR_CONTRIBUTE_SET_ALL_SUCCESS:
			pUIManager->GetGuild()->AdjustDonateMinMaxInfo();
			strMessage.PrintF(_S(3889, "��� ������ ����Ǿ����ϴ�."));
			bSysMsg = true;
			break;
		case MSG_GUILD_ERROR_CONTRIBUTE_SET_FAIL:
		case MSG_GUILD_ERROR_CONTRIBUTE_SET_ALL_FAIL:
			strMessage.PrintF(_S(3888, "��� ���� ���뿡 �����Ͽ����ϴ�."));
			bSysMsg = true;
			break;
		case MSG_GUILD_ERROR_CONTRIBUTE_INVALID_VALUE:
			strMessage.PrintF(_S(6472, "��ġ�� �߸� �Է� �Ͽ����ϴ�. �ּ� ��ġ�� �ִ� ��ġ���� ���� �� ������, �ִ� ��ġ�� �ּ� ��ġ���� ���� �� �����ϴ�."));
			break;
			// <== 1107 ��� �ý��� ���� [trylord 11/12/28]
						// ----------------------------------------------------------------<<
		}
		pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_DESTROY);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_QUIT);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_KICK);						// ��� ����
		pUIManager->CloseMessageBox(MSGCMD_GUILD_ADD_VICE_BOSS);				// �δ��� �Ӹ�
		pUIManager->CloseMessageBox(MSGCMD_GUILD_DEL_VICE_BOSS);				// �δ��� ����
		pUIManager->CloseMessageBox(MSGCMD_GUILD_CHANGE_BOSS);					// ���� ����

		if (bSysMsg == true)
		{
			_pNetwork->ClientSystemMessage(strMessage, SYSMSG_ERROR);
		}
		else
		{
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(865, "���"), UMBS_OK, UI_GUILD, MSGCMD_GUILD_ERROR);
			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);
			//pUIManager->GetGuild()->ResetGuild();
		}
	}
	break;

	case MSG_GUILD_CREATE:		// ��� ����
	{
		CPrintF("��� ����\n");
	}
	break;

	case MSG_GUILD_INFO:		// �� ��� ���� ������
	{
		//MSG_GUILD_INFO,	// �� ��� ���� ������	: guildindex(n) guildname(str) guildlevel(n) mypos(n)
							// ��� ������ guildindex == -1, ���� �׸� ����
		LONG		lGuildIndex;
		(*istr) >> lGuildIndex;

		_pNetwork->MyCharacterInfo.lGuildIndex = lGuildIndex;

		// ��忡 �������� ����.
		if (lGuildIndex == -1)
		{
		}
		else
		{
			CTString	strGuildName, strGuildClassName;
			LONG		lGuildLevel;
			LONG		lMyPos;
			(*istr) >> strGuildName;
			(*istr) >> lGuildLevel;
			(*istr) >> lMyPos;
			(*istr) >> _pNetwork->MyCharacterInfo.sbGuildRank;
			(*istr) >> strGuildClassName;
			// WSS_NEW_GUILD_SYSTEM 070731
			SBYTE		sbGuildSkill444;	// ���� Ȯ�� ��ų
			(*istr) >> sbGuildSkill444;
			pUIManager->GetGuild()->ResetGuildMaxMember((int)sbGuildSkill444);

			_pNetwork->MyCharacterInfo.lGuildLevel = lGuildLevel;
			_pNetwork->MyCharacterInfo.lGuildPosition = lMyPos;
			_pNetwork->MyCharacterInfo.strGuildName = strGuildName;
			_pNetwork->MyCharacterInfo.guildPosName = strGuildClassName;

			// [sora] GUILD_MARK
#ifdef GUILD_MARK
			SBYTE gm_row, gm_col, bg_row, bg_col;

			(*istr) >> gm_row;
			(*istr) >> gm_col;
			(*istr) >> bg_row;
			(*istr) >> bg_col;

			MY_INFO()->_guildmark.setData(gm_row, gm_col, bg_row, bg_col);
			UIMGR()->SetGuildMark();
#endif
#ifdef	UPDATE1107_GUILDSYSTEM	// 1107 ��� �ý��� ���� [trylord 11/12/28]
			LONG	lGuildMStatus = 0;

			(*istr) >> lGuildMStatus;
			_pNetwork->MyCharacterInfo.iGuildMasterKickStatus = (int)lGuildMStatus;

			if (_pNetwork->MyCharacterInfo.iGuildMasterKickStatus == 1)
			{
				pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);

				CTString		strMessage;
				CUIMsgBox_Info	MsgBoxInfo;

				strMessage.PrintF(_S(5631, "[%s] ����� ������� ����� ����� ������ ������ �����Դϴ�."), _pNetwork->MyCharacterInfo.strGuildName);
				MsgBoxInfo.SetMsgBoxInfo(_S(865, "���"), UMBS_OK, UI_GUILD, MSGCMD_GUILD_ERROR);		// Ȯ�θ� �ϸ� �ǹǷ� MSGCMD_GUILD_ERROR ������
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
#endif	// #ifdef	UPDATE1107_GUILDSYSTEM

		}
	}
	break;

	case MSG_GUILD_MEMBERLIST:	// ���� ����Ʈ
	{
		// ��� ����Ʈ			: guildindex(n) count(n) [index(n) name(str) position(n) online(c)]:count
		LONG lGuildIndex;
		LONG lCount;
		(*istr) >> lGuildIndex;
		(*istr) >> lCount;

		if (_pNetwork->MyCharacterInfo.lGuildIndex == lGuildIndex)
		{
			pUIManager->GetGuild()->ResetGuild();
			pUIManager->GetGuild()->ClearMemberList();
		}

		for (int i = 0; i < lCount; ++i)
		{
			LONG		lIndex;
			CTString	strName;
			LONG		lPosition;
			SBYTE		sbOnline;

			(*istr) >> lIndex;
			(*istr) >> strName;
			(*istr) >> lPosition;
			(*istr) >> sbOnline;

			if (_pNetwork->MyCharacterInfo.lGuildIndex == lGuildIndex)
			{
				pUIManager->GetGuild()->AddToMemberList(lIndex, strName, lPosition, sbOnline);
			}
		}
	}
	break;

	case MSG_GUILD_ONLINE:		// ���� �¶��� ����
	{
		LONG		lGuildIndex;
		LONG		lIndex;
		CTString	strName;
		//LONG		lPosition;
		SBYTE		sbOnline;

		(*istr) >> lGuildIndex;
		(*istr) >> lIndex;
		(*istr) >> strName;
		//(*istr) >> lPosition;
		(*istr) >> sbOnline;

		// �츮 ����.
		if (_pNetwork->MyCharacterInfo.lGuildIndex == lGuildIndex)
		{
			if (_pNetwork->MyCharacterInfo.index != lIndex)
			{
				CTString strMessage;
				if (sbOnline == TRUE)
					strMessage.PrintF(_S(996, "[%s] ������ �����ϼ̽��ϴ�."), strName);
				else
					strMessage.PrintF(_S(997, "[%s] ������ �������� �ϼ̽��ϴ�."), strName);
				pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
			}

			pUIManager->GetGuild()->ChangeMemberOnline(lIndex, sbOnline);

			if (_pNetwork->MyCharacterInfo.lGuildLevel < LIMIT_GUILD_LEVEL)
			{
				if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS ||
					_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_VICE_BOSS)
				{
					pUIManager->GetGuild()->RefreshMemberList(TRUE);
				}
				else if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_MEMBER)
				{
					pUIManager->GetGuild()->RefreshApplicantList();
				}
			}
		}
	}
	break;

	case MSG_GUILD_LEVELUP:		// ��� �±�
	{
	}
	break;

	case MSG_GUILD_LEVELINFO:	// ��� ���� ����
	{
		LONG lGuildIndex;
		LONG lGuildLevel;
		(*istr) >> lGuildIndex;
		(*istr) >> lGuildLevel;

		// my Character
		if (_pNetwork->MyCharacterInfo.lGuildIndex == lGuildIndex)
		{
			_pNetwork->MyCharacterInfo.lGuildLevel = lGuildLevel;
		}
		// other Characters
		else
		{
			// �ٸ� ĳ���͵��� ��� ������ �����Ŵ.
			ACTORMGR()->ChangeGuildLevel(lGuildIndex, lGuildLevel);
		}
		pUIManager->GetGuild()->ResetGuild();
	}
	break;

	case MSG_GUILD_BREAKUP:		// ��� ��ü
	{
		//pUIManager->GetGuild()->ResetGuild();
		//pUIManager->GetGuild()->ClearMemberList();
	}
	break;

	case MSG_GUILD_BREAKUP_NOTIFY:
	{
		LONG		lGuildIndex;
		CTString	strGuildName;
		(*istr) >> lGuildIndex;
		(*istr) >> strGuildName;

		ACTORMGR()->ChangeGuildInfo(lGuildIndex, -1, -1, GUILD_MEMBER_NOMEMBER, "");

		if (lGuildIndex == _pNetwork->MyCharacterInfo.lGuildIndex)
		{
			_pNetwork->MyCharacterInfo.lGuildIndex = -1;
			_pNetwork->MyCharacterInfo.lGuildLevel = -1;
			_pNetwork->MyCharacterInfo.lGuildPosition = GUILD_MEMBER_NOMEMBER;
			_pNetwork->MyCharacterInfo.guildPosName = "";	// [2010/12/12 : Sora] ������ �ʱ�ȭ�ؾ� �Ѵ�

			CTString strMessage;
			strMessage.PrintF(_S(998, "[%s] ��尡 ��ü�Ǿ����ϴ�."), strGuildName);
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);

			pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_DESTROY);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_QUIT);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);
			pUIManager->CloseMessageBox(MSGCMD_GUILD_KICK);						// ��� ����
			pUIManager->CloseMessageBox(MSGCMD_GUILD_ADD_VICE_BOSS);				// �δ��� �Ӹ�
			pUIManager->CloseMessageBox(MSGCMD_GUILD_DEL_VICE_BOSS);				// �δ��� ����
			pUIManager->CloseMessageBox(MSGCMD_GUILD_CHANGE_BOSS);				// ���� ����

			CUIGuild* pGuild = pUIManager->GetGuild();

			if (pGuild != NULL)
			{
				pGuild->ResetGuild();
				pGuild->ClearMemberList();
				pGuild->ClearGuildSkill();
			}

			((CUIWebBoard*)pUIManager->GetUI(UI_WEBBOARD))->NotifyGuildChange();

			MY_INFO()->_guildmark.remove();
			UIMGR()->SetGuildMark();
		}
	}
	break;

	case MSG_GUILD_REGIST_REQ:	// ���� ��û�� ��.
	{
		LONG lGuildIndex;
		LONG lBossIndex;
		LONG lRequesterIndex;

		(*istr) >> lGuildIndex;
		(*istr) >> lBossIndex;
		(*istr) >> lRequesterIndex;

		if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS ||
			_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_VICE_BOSS)
			pUIManager->GetGuild()->ApplicantAccept(lRequesterIndex);
	}
	break;

	case MSG_GUILD_REGIST_ALLOW:	// ��� ��û Ȯ��
	{
		pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);
	}
	break;

	case MSG_GUILD_REGIST_CANCEL:	// ��� ��û ���
	{
		//m_bGuildJoinReq;

		pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);
		CTString strMessage;
		strMessage.PrintF(_S(999, "��� ���� ��û�� ��ҵǾ����ϴ�."));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
	}
	break;

	case MSG_GUILD_CHANGE_BOSS:
	{
		// ���� ����			: guildindex(n) current(n) newboss(n)
		LONG lGuildIndex;
		LONG lCharIndex;
		LONG lBossIndex;
		(*istr) >> lGuildIndex;
		(*istr) >> lCharIndex;
		(*istr) >> lBossIndex;

		CTString strNewBossName = "";
		// WSS_NEW_GUILD_SYSTEM 2007/08/07---------------------------------------------->>
		if (_pNetwork->MyCharacterInfo.lGuildLevel >= LIMIT_GUILD_LEVEL)
		{
			if (lCharIndex == _pNetwork->MyCharacterInfo.index)
			{
				_pNetwork->MyCharacterInfo.lGuildIndex = lGuildIndex;		// �ӽ�	����� �ε���
				_pNetwork->MyCharacterInfo.lGuildPosition = GUILD_MEMBER_MEMBER;		// �ӽ� ��忡���� ĳ������ ����				
				pUIManager->GetGuild()->ChangeMemberLevel(lCharIndex, GUILD_MEMBER_MEMBER);
			}

			if (lBossIndex == _pNetwork->MyCharacterInfo.index)
			{
				_pNetwork->MyCharacterInfo.lGuildIndex = lGuildIndex;				// �ӽ�	����� �ε���
				_pNetwork->MyCharacterInfo.lGuildPosition = GUILD_MEMBER_BOSS;		// �ӽ� ��忡���� ĳ������ ����
				pUIManager->GetGuild()->ChangeMemberLevel(lBossIndex, GUILD_MEMBER_BOSS);
				CTString strMessage;
				strMessage.PrintF(_S(1000, "����忡 �Ӹ��Ǿ����ϴ�."));
				pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
				strNewBossName = _pNetwork->MyCharacterInfo.name;
			}
			else
			{
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lBossIndex);

				if (pObject != NULL)
				{
					pUIManager->GetGuild()->ChangeMemberLevel(pObject->GetSIndex(), GUILD_MEMBER_BOSS);
					strNewBossName = pObject->m_strName.c_str();
				}
			}

		}
		else {
			// ------------------------------------------------------------------------------<<
			// ���� ����.
			if (lCharIndex == _pNetwork->MyCharacterInfo.index)
			{
				_pNetwork->MyCharacterInfo.lGuildIndex = lGuildIndex;		// �ӽ�	����� �ε���
				_pNetwork->MyCharacterInfo.lGuildPosition = GUILD_MEMBER_MEMBER;		// �ӽ� ��忡���� ĳ������ ����				
				pUIManager->GetGuild()->ChangeMemberLevel(lCharIndex, GUILD_MEMBER_MEMBER);
				const BOOL bVisible = pUIManager->GetGuild()->IsVisible();
				pUIManager->GetGuild()->ResetGuild();
				if (bVisible)
				{
					pUIManager->GetGuild()->OpenGuildManager(_pNetwork->MyCharacterInfo.lGuildPosition);
				}
			}
			else
			{
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lCharIndex);

				if (pObject != NULL)
				{
					CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

					pTarget->cha_lGuildIndex = lGuildIndex;				// �ӽ�	����� �ε���
					pTarget->cha_lGuildPosition = GUILD_MEMBER_MEMBER;		// �ӽ� ��忡���� ĳ������ ����
				}

				pUIManager->GetGuild()->ChangeMemberLevel(lCharIndex, GUILD_MEMBER_MEMBER);
			}

			if (lBossIndex == _pNetwork->MyCharacterInfo.index)
			{
				_pNetwork->MyCharacterInfo.lGuildIndex = lGuildIndex;				// �ӽ�	����� �ε���
				_pNetwork->MyCharacterInfo.lGuildPosition = GUILD_MEMBER_BOSS;		// �ӽ� ��忡���� ĳ������ ����
				pUIManager->GetGuild()->ChangeMemberLevel(lBossIndex, GUILD_MEMBER_BOSS);
				const BOOL bVisible = pUIManager->GetGuild()->IsVisible();
				pUIManager->GetGuild()->ResetGuild();
				if (bVisible)
				{
					pUIManager->GetGuild()->OpenGuildManager(_pNetwork->MyCharacterInfo.lGuildPosition);
				}

				CTString strMessage;
				strMessage.PrintF(_S(1000, "����忡 �Ӹ��Ǿ����ϴ�."));
				pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
				strNewBossName = _pNetwork->MyCharacterInfo.name;
			}
			else
			{
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lBossIndex);

				if (pObject != NULL)
				{
					CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

					pTarget->cha_lGuildIndex = lGuildIndex;
					pTarget->cha_lGuildPosition = GUILD_MEMBER_BOSS;
					strNewBossName = pTarget->m_strName.c_str();
				}

				pUIManager->GetGuild()->ChangeMemberLevel(lBossIndex, GUILD_MEMBER_BOSS);
			}

			if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS ||
				_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_VICE_BOSS)
			{
				pUIManager->GetGuild()->RefreshMemberList(TRUE);
			}
			else if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_MEMBER)
			{
				pUIManager->GetGuild()->RefreshApplicantList();
			}
		}

		if (!strNewBossName.IsEmpty())
		{
			CUIMsgBox_Info	MsgBoxInfo;
			CTString strTemp;
			MsgBoxInfo.SetMsgBoxInfo(_S(865, "���"), UMBS_OK, UI_NONE, MSGCMD_NULL);
			strTemp.PrintF(_S(5672, "%s �Բ��� ��������� �Ӹ��Ǽ̽��ϴ�."), strNewBossName);
			MsgBoxInfo.AddString(strTemp);
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}

	}
	break;

	case MSG_GUILD_APPOINT_OFFICER:
	{
		// �δ��� �Ӹ�			: guildindex(n) charindex(n)
		LONG lGuildIndex;
		LONG lCharIndex;
		(*istr) >> lGuildIndex;
		(*istr) >> lCharIndex;

		// WSS_NEW_GUILD_SYSTEM 2007/08/07---------------------------------------------->>
		if (_pNetwork->MyCharacterInfo.lGuildLevel >= LIMIT_GUILD_LEVEL)
		{
			if (lCharIndex == _pNetwork->MyCharacterInfo.index)
			{
				_pNetwork->MyCharacterInfo.lGuildIndex = lGuildIndex;		// �ӽ�	����� �ε���
				_pNetwork->MyCharacterInfo.lGuildPosition = GUILD_MEMBER_VICE_BOSS;		// �ӽ� ��忡���� ĳ������ ����				

				CTString strMessage;
				strMessage.PrintF(_S(1001, "�����忡 �Ӹ��Ǿ����ϴ�."));
				pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
			}
			else
			{
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lCharIndex);

				if (pObject != NULL)
				{
					CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

					pTarget->cha_lGuildIndex = lGuildIndex;
					pTarget->cha_lGuildPosition = GUILD_MEMBER_VICE_BOSS;
				}
			}

			pUIManager->GetGuild()->ChangeMemberLevel(lCharIndex, GUILD_MEMBER_VICE_BOSS);
		}
		// ------------------------------------------------------------------------------<<

		if (lCharIndex == _pNetwork->MyCharacterInfo.index)
		{
			_pNetwork->MyCharacterInfo.lGuildIndex = lGuildIndex;		// �ӽ�	����� �ε���
			_pNetwork->MyCharacterInfo.lGuildPosition = GUILD_MEMBER_VICE_BOSS;		// �ӽ� ��忡���� ĳ������ ����				
			pUIManager->GetGuild()->ChangeMemberLevel(lCharIndex, GUILD_MEMBER_VICE_BOSS);
			const BOOL bVisible = pUIManager->GetGuild()->IsVisible();
			pUIManager->GetGuild()->ResetGuild();
			if (bVisible)
			{
				pUIManager->GetGuild()->OpenGuildManager(_pNetwork->MyCharacterInfo.lGuildPosition);
			}

			CTString strMessage;
			strMessage.PrintF(_S(1001, "�����忡 �Ӹ��Ǿ����ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
		}
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lCharIndex);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTarget->cha_lGuildIndex = lGuildIndex;
				pTarget->cha_lGuildPosition = GUILD_MEMBER_VICE_BOSS;
			}

			pUIManager->GetGuild()->ChangeMemberLevel(lCharIndex, GUILD_MEMBER_VICE_BOSS);
		}

		if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS ||
			_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_VICE_BOSS)
		{
			pUIManager->GetGuild()->RefreshMemberList(TRUE);
		}
		else if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_MEMBER)
		{
			pUIManager->GetGuild()->RefreshApplicantList();
		}
	}
	break;

	case MSG_GUILD_FIRE_OFFICER:
	{
		// �δ��� ����			: guildindex(n) charindex(n)
		LONG lGuildIndex;
		LONG lCharIndex;
		(*istr) >> lGuildIndex;
		(*istr) >> lCharIndex;

		// WSS_NEW_GUILD_SYSTEM 2007/08/07---------------------------------------------->>
		if (_pNetwork->MyCharacterInfo.lGuildLevel >= LIMIT_GUILD_LEVEL)
		{
			if (lCharIndex == _pNetwork->MyCharacterInfo.index)
			{
				_pNetwork->MyCharacterInfo.lGuildIndex = lGuildIndex;		// �ӽ�	����� �ε���
				_pNetwork->MyCharacterInfo.lGuildPosition = GUILD_MEMBER_MEMBER;		// �ӽ� ��忡���� ĳ������ ����				
				CTString strMessage;
				strMessage.PrintF(_S(1002, "�����忡�� ���ӵǾ����ϴ�."));
				pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
			}
			else
			{
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lCharIndex);

				if (pObject != NULL)
				{
					CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

					pTarget->cha_lGuildIndex = lGuildIndex;
					pTarget->cha_lGuildPosition = GUILD_MEMBER_MEMBER;
				}
			}

			pUIManager->GetGuild()->ChangeMemberLevel(lCharIndex, GUILD_MEMBER_MEMBER);
		}
		// ------------------------------------------------------------------------------<<

		if (lCharIndex == _pNetwork->MyCharacterInfo.index)
		{
			_pNetwork->MyCharacterInfo.lGuildIndex = lGuildIndex;		// �ӽ�	����� �ε���
			_pNetwork->MyCharacterInfo.lGuildPosition = GUILD_MEMBER_MEMBER;		// �ӽ� ��忡���� ĳ������ ����				
			pUIManager->GetGuild()->ChangeMemberLevel(lCharIndex, GUILD_MEMBER_MEMBER);
			const BOOL bVisible = pUIManager->GetGuild()->IsVisible();
			pUIManager->GetGuild()->ResetGuild();
			if (bVisible)
			{
				pUIManager->GetGuild()->OpenGuildManager(_pNetwork->MyCharacterInfo.lGuildPosition);
			}

			CTString strMessage;
			strMessage.PrintF(_S(1002, "�����忡�� ���ӵǾ����ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
		}
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lCharIndex);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTarget->cha_lGuildIndex = lGuildIndex;
				pTarget->cha_lGuildPosition = GUILD_MEMBER_MEMBER;
			}

			pUIManager->GetGuild()->ChangeMemberLevel(lCharIndex, GUILD_MEMBER_MEMBER);
		}

		if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS ||
			_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_VICE_BOSS)
		{
			pUIManager->GetGuild()->RefreshMemberList(TRUE);
		}
		else if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_MEMBER)
		{
			pUIManager->GetGuild()->RefreshApplicantList();
		}
	}
	break;
	case MSG_GUILD_MEMBER_ADD:		// ��� �߰�
	{
		LONG lGuildIndex;
		LONG lCharIndex;
		CTString strCharName;
		(*istr) >> lGuildIndex;
		(*istr) >> lCharIndex;
		(*istr) >> strCharName;

		// WSS_NEW_GUILD_SYSTEM 2007/08/08	
		// �ǽð� ������ �ȵǹǷ� �޽����� ����� �ش�.
		if (_pNetwork->MyCharacterInfo.lGuildLevel >= LIMIT_GUILD_LEVEL)
		{
			CTString strMessage;
			strMessage.PrintF(_S(1003, "[%s] ������ �����Ͽ����ϴ�."), strCharName);
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
			break;
		}
		// �� ��忡 �߰��Ǵ� ���.
		if (_pNetwork->MyCharacterInfo.lGuildIndex == lGuildIndex)
		{
			pUIManager->GetGuild()->AddToMemberList(lCharIndex, strCharName, GUILD_MEMBER_MEMBER, TRUE);

			if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_MEMBER)
			{
				pUIManager->GetGuild()->RefreshApplicantList();
			}
			else if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS ||
				_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_VICE_BOSS)
			{
				pUIManager->GetGuild()->RefreshMemberList();
			}

			CTString strMessage;
			strMessage.PrintF(_S(1003, "[%s] ������ �����Ͽ����ϴ�."), strCharName);
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
		}
	}
	break;
	case MSG_GUILD_MEMBER_OUT:		// ��� Ż��
	{
		LONG lGuildIndex;
		LONG lCharIndex;
		CTString strCharName;
		(*istr) >> lGuildIndex;
		(*istr) >> lCharIndex;
		(*istr) >> strCharName;

		if (lCharIndex == _pNetwork->MyCharacterInfo.index)
		{
			_pNetwork->MyCharacterInfo.lGuildIndex = -1;		// �ӽ�	����� �ε���
			_pNetwork->MyCharacterInfo.lGuildLevel = -1;		// �ӽ� ����� ����
			_pNetwork->MyCharacterInfo.lGuildPosition = GUILD_MEMBER_NOMEMBER;		// �ӽ� ��忡���� ĳ������ ����
			_pNetwork->MyCharacterInfo.strGuildName = "";

			((CUIWebBoard*)pUIManager->GetUI(UI_WEBBOARD))->NotifyGuildChange();

			pUIManager->GetGuild()->ClearGuildSkill();
		}
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lCharIndex);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTarget->cha_lGuildIndex = -1;
				pTarget->cha_lGuildLevel = -1;
				pTarget->cha_lGuildPosition = GUILD_MEMBER_NOMEMBER;
				pTarget->cha_strGuildName = "";
			}
		}

		if (_pNetwork->MyCharacterInfo.lGuildIndex == lGuildIndex)
		{
			// WSS_NEW_GUILD_SYSTEM 2007/08/08	
		// �ǽð� ������ �ȵǹǷ� �޽����� ����� �ش�.
			if (_pNetwork->MyCharacterInfo.lGuildLevel < LIMIT_GUILD_LEVEL)
			{
				pUIManager->GetGuild()->DelFromMemberList(lCharIndex);

				if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_MEMBER)
				{
					pUIManager->GetGuild()->RefreshApplicantList();
				}
				else if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS ||
					_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_VICE_BOSS)
				{
					pUIManager->GetGuild()->RefreshMemberList();
				}
			}
			CTString strMessage;
			strMessage.PrintF(_S(1004, "[%s] ������ Ż���Ͽ����ϴ�."), strCharName);

			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
		}
	}
	break;
	case MSG_GUILD_MEMBER_KICK:		// ��� ����
	{
		// guildindex(n) bossindex(n) charindex(n) charname(str)

		LONG lGuildIndex;
		LONG lBossIndex;
		LONG lCharIndex;
		CTString strCharName;
		(*istr) >> lGuildIndex;
		(*istr) >> lBossIndex;
		(*istr) >> lCharIndex;
		(*istr) >> strCharName;

		if (lCharIndex == _pNetwork->MyCharacterInfo.index)
		{
			// �ڽ��� ����ȰŶ��...				
			_pNetwork->MyCharacterInfo.lGuildIndex = -1;		// �ӽ�	����� �ε���
			_pNetwork->MyCharacterInfo.lGuildLevel = -1;		// �ӽ� ����� ����
			_pNetwork->MyCharacterInfo.lGuildPosition = GUILD_MEMBER_NOMEMBER;		// �ӽ� ��忡���� ĳ������ ����
			_pNetwork->MyCharacterInfo.strGuildName = "";
			pUIManager->GetGuild()->ResetGuild();
			pUIManager->GetGuild()->ClearMemberList();

			CTString strMessage;
			strMessage.PrintF(_S(1005, "��忡�� ����Ǿ����ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);

			((CUIWebBoard*)pUIManager->GetUI(UI_WEBBOARD))->NotifyGuildChange();

			MY_INFO()->_guildmark.remove();
			UIMGR()->SetGuildMark();
			return;
		}
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lCharIndex);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTarget->cha_lGuildIndex = -1;
				pTarget->cha_lGuildLevel = -1;
				pTarget->cha_lGuildPosition = GUILD_MEMBER_NOMEMBER;
				pTarget->cha_strGuildName = "";
			}
		}

		// ���� ���� �ִ� ��� �������� �ش� ĳ���� ������ ������.
		if (_pNetwork->MyCharacterInfo.lGuildIndex == lGuildIndex)
		{
			// WSS_NEW_GUILD_SYSTEM 2007/08/08	
			// �ǽð� ������ �ȵǹǷ� �޽����� ����� �ش�.
			if (_pNetwork->MyCharacterInfo.lGuildLevel < LIMIT_GUILD_LEVEL)
			{
				pUIManager->GetGuild()->DelFromMemberList(lCharIndex);

				if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_MEMBER)
				{
					pUIManager->GetGuild()->RefreshApplicantList();
				}
				else if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS ||
					_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_VICE_BOSS)
				{
					pUIManager->GetGuild()->RefreshMemberList();
				}
			}
			CTString strMessage;
			strMessage.PrintF(_S(1006, "[%s] ������ �����Ͽ����ϴ�."), strCharName);
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
		}
	}
	break;
	case MSG_GUILD_INFO_CHANGE:		// ��� ���� ����.
	{
		LONG		lCharIndex;
		LONG		lGuildIndex;
		CTString	strGuildName;
		LONG		lCharPos;

		(*istr) >> lCharIndex;
		(*istr) >> lGuildIndex;
		(*istr) >> strGuildName;
		(*istr) >> lCharPos;
		SBYTE		sbGuildRank;
		(*istr) >> sbGuildRank;

		LONG		lOldPos = _pNetwork->MyCharacterInfo.lGuildPosition;

		// [sora] GUILD_MARK
#ifdef GUILD_MARK
		SBYTE gm_row, gm_col, bg_row, bg_col;

		(*istr) >> gm_row;
		(*istr) >> gm_col;
		(*istr) >> bg_row;
		(*istr) >> bg_col;
#endif

		// ��� �󿡼��� �� ��ġ�� ������ ����� ���...
		if (lCharIndex == _pNetwork->MyCharacterInfo.index)
		{
			_pNetwork->MyCharacterInfo.lGuildIndex = lGuildIndex;		// �ӽ�	����� �ε���				
			_pNetwork->MyCharacterInfo.lGuildPosition = lCharPos;		// �ӽ� ��忡���� ĳ������ ����
			_pNetwork->MyCharacterInfo.strGuildName = strGuildName;
			_pNetwork->MyCharacterInfo.sbGuildRank = sbGuildRank;

			// [sora] GUILD_MARK
#ifdef GUILD_MARK
			MY_INFO()->_guildmark.setData(gm_row, gm_col, bg_row, bg_col);
			UIMGR()->SetGuildMark();
#endif
		}
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lCharIndex);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTarget->cha_lGuildIndex = lGuildIndex;		// �ӽ�	����� �ε���
				pTarget->cha_lGuildPosition = lCharPos;			// �ӽ� ��忡���� ĳ������ ����
				pTarget->cha_strGuildName = strGuildName;
				pTarget->cha_sbGuildRank = sbGuildRank;

#ifdef GUILD_MARK
				if (gm_row >= 0)
				{
					if (pTarget->pGuildmark == NULL)
					{
						pTarget->pGuildmark = new CUIGuildMarkIcon;
						pTarget->pGuildmark->Create(NULL, 0, 0, 15, 15);
					}

					pTarget->pGuildmark->CalcUV(gm_row, gm_col, true);
					pTarget->pGuildmark->CalcUV(bg_row, bg_col, false);
				}
#endif
			}
		}

		if (_pNetwork->MyCharacterInfo.lGuildIndex == lGuildIndex)
		{
			pUIManager->GetGuild()->ChangeMemberLevel(lCharIndex, lCharPos);

			// WSS_NEW_GUILD_SYSTEM 2007/08/08	
			// �ǽð� ������ �ȵǹǷ� �޽����� ����� �ش�.
			if (_pNetwork->MyCharacterInfo.lGuildLevel < LIMIT_GUILD_LEVEL)
			{
				// ���¿� ������ ����.
				if (lOldPos == _pNetwork->MyCharacterInfo.lGuildPosition)
				{
					if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_MEMBER)
					{
						pUIManager->GetGuild()->RefreshApplicantList();
					}
					else if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS ||
						_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_VICE_BOSS)
					{
						pUIManager->GetGuild()->RefreshMemberList();
					}
				}
				else
				{
					// ������� ���� Ȥ�� �δ������� ����.
					if (lOldPos == GUILD_MEMBER_MEMBER &&
						(_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS ||
							_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_VICE_BOSS))
					{
						const BOOL bVisible = pUIManager->GetGuild()->IsVisible();
						pUIManager->GetGuild()->ResetGuild();
						if (bVisible)
						{
							pUIManager->GetGuild()->OpenGuildManager(_pNetwork->MyCharacterInfo.lGuildPosition);
						}
					}
					else if ((lOldPos == GUILD_MEMBER_BOSS || lOldPos == GUILD_MEMBER_VICE_BOSS))
					{
						// ���� Ȥ�� �δ��忡�� �Ϲ� �����...
						if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_MEMBER)
						{
							const BOOL bVisible = pUIManager->GetGuild()->IsVisible();
							pUIManager->GetGuild()->ResetGuild();
							if (bVisible)
							{
								pUIManager->GetGuild()->OpenGuildManager(_pNetwork->MyCharacterInfo.lGuildPosition);
							}
						}
					}
				}
			}
		}
	}
	break;
	// Guild Battle 
// ����� ��û ��û ����
	case MSG_GUILD_BATTLE_REQ_REQ:
	{
		LONG		lGuildIndex;
		CTString	strGuildName;
		LONG		lPrize;
		LONG		lTime;

		(*istr) >> lGuildIndex;
		(*istr) >> strGuildName;
		(*istr) >> lPrize;
		(*istr) >> lTime;


		pUIManager->GetGuildBattle()->GBReq(lGuildIndex, strGuildName, lPrize, lTime);
	}
	break;

	// ����� ��û ���� ����
	case MSG_GUILD_BATTLE_REQ_REJECT:
	{
		LONG lRejectCharIndex;
		(*istr) >> lRejectCharIndex;

		pUIManager->GetGuildBattle()->GBReqReject(lRejectCharIndex);

	}
	break;

	// ����� ��û ���	����
	case MSG_GUILD_BATTLE_REQ_ACCEPT:
	{
		LONG		lGuildIndex1;
		CTString	strGuildName1;
		LONG		lGuildIndex2;
		CTString	strGuildName2;
		LONG		lPrize;
		LONG		lZone;
		LONG		lTime;

		(*istr) >> lGuildIndex1;
		(*istr) >> strGuildName1;
		(*istr) >> lGuildIndex2;
		(*istr) >> strGuildName2;
		(*istr) >> lPrize;
		(*istr) >> lZone;
		(*istr) >> lTime;


		pUIManager->GetGuildBattle()->GBReqAccept(lGuildIndex1, strGuildName1, lGuildIndex2, strGuildName2, lPrize, lZone, lTime);
	}
	break;

	// ����� �ߴ� ��û	���� 
	case MSG_GUILD_BATTLE_STOP_REQ:
	{
		LONG		lGuildIndex;
		CTString	strGuildName;

		(*istr) >> lGuildIndex;
		(*istr) >> strGuildName;

		pUIManager->GetGuildBattle()->GBStopReqRev(lGuildIndex, strGuildName);
	}
	break;

	// ����� �ߴ� ���� ���� 
	case MSG_GUILD_BATTLE_STOP_REJECT:
	{
		LONG lRejectCharIndex;
		(*istr) >> lRejectCharIndex;

		pUIManager->GetGuildBattle()->GBStopReqReject(lRejectCharIndex);
	}
	break;

	// ����� �ߴ� ��� ���� 
	case MSG_GUILD_BATTLE_STOP_ACCEPT:
	{
		pUIManager->GetGuildBattle()->GBStopReqAccept();
	}
	break;

	// ����� ���� �˸�
	case MSG_GUILD_BATTLE_START:
	{
		LONG		lGuildIndex1;
		CTString	strGuildName1;
		LONG		lGuildIndex2;
		CTString	strGuildName2;
		LONG		lPrize;
		LONG		lZone;
		LONG		lTime;

		(*istr) >> lGuildIndex1;
		(*istr) >> strGuildName1;
		(*istr) >> lGuildIndex2;
		(*istr) >> strGuildName2;
		(*istr) >> lPrize;
		(*istr) >> lZone;
		(*istr) >> lTime;

		pUIManager->GetGuildBattle()->GBStart(lGuildIndex1, strGuildName1, lGuildIndex2, strGuildName2, lPrize, lZone, lTime);

	}
	break;

	// ����� ��Ȳ			
	case MSG_GUILD_BATTLE_STATUS:
	{
		LONG		lGuildIndex1;
		CTString	strGuildName1;
		LONG		lCount1;
		LONG		lGuildIndex2;
		CTString	strGuildName2;
		LONG		lCount2;
		LONG		lTime;
		LONG		lZone;

		(*istr) >> lGuildIndex1;
		(*istr) >> strGuildName1;
		(*istr) >> lCount1;
		(*istr) >> lGuildIndex2;
		(*istr) >> strGuildName2;
		(*istr) >> lCount2;
		(*istr) >> lTime;
		(*istr) >> lZone;

		pUIManager->GetGuildBattle()->GBStatus(lGuildIndex1, strGuildName1, lCount1,
			lGuildIndex2, strGuildName2, lCount2, lTime, lZone);
	}
	break;

	// ����� ���� 	
	case MSG_GUILD_BATTLE_END:
	{
		LONG		lWinnerGuildIndex;
		LONG		lGuildIndex1;
		CTString	strGuildName1;
		LONG		lGuildIndex2;
		CTString	strGuildName2;
		LONG		lPrize;

		(*istr) >> lWinnerGuildIndex;
		(*istr) >> lGuildIndex1;
		(*istr) >> strGuildName1;
		(*istr) >> lGuildIndex2;
		(*istr) >> strGuildName2;
		(*istr) >> lPrize;

		pUIManager->GetGuildBattle()->GBEnd(lWinnerGuildIndex, lGuildIndex1, strGuildName1, lGuildIndex2, strGuildName2, lPrize);
	}
	break;

	case MSG_GUILD_BATTLE_SCORE_INIT:
	{
		if (pUIManager->GetGuildBattle()->IsInBattle() == TRUE)
			return;
		else
			pUIManager->GetGuildBattle()->Close();
	}
	break;

	// Date : 2005-07-06(���� 2:41:11), By Lee Ki-hwan
	// ������ ���� �޼��� ó�� 
	case MSG_GUILD_WAR_JOIN_ATTACK_GUILD:
	case MSG_GUILD_WAR_JOIN_DEFENSE_GUILD:
	case MSG_GUILD_WAR_JOIN_ATTACK_CHAR:
	case MSG_GUILD_WAR_JOIN_DEFENSE_CHAR:
	{
		LONG		nErrorCode;
		(*istr) >> nErrorCode;
		_pUISWDoc->ErrorProc(nErrorCode, ubType);
	}
	break;
	case MSG_GUILD_WAR_GET_TIME:
	{
		LONG		nErrorCode;
		LONG		nGuildIndex;
		CTString	strGuildName;
		SBYTE		nMonth;
		SBYTE		nDay;
		SBYTE		nHour;
		SBYTE		nMin;

		(*istr) >> nErrorCode;
		(*istr) >> nGuildIndex;
		(*istr) >> strGuildName;
		(*istr) >> nMonth;
		(*istr) >> nDay;
		(*istr) >> nHour;
		(*istr) >> nMin;

		if (nErrorCode != MSG_GUILD_ERROR_OK)	_pUISWDoc->ErrorProc(nErrorCode);
		else
		{
			_pUISWDoc->GetTime(nGuildIndex, strGuildName, nMonth, nDay, nHour, nMin);
		}

	}
	break;
	case MSG_GUILD_WAR_START:
	{
		LONG		nZoneIndex;
		LONG		nRemainSec;

		(*istr) >> nZoneIndex;
		(*istr) >> nRemainSec;

		_pUISWDoc->GuildWarStart(nZoneIndex, nRemainSec);
	}
	break;
	case MSG_GUILD_WAR_NOTICE_START_CASTLE:
	{
		LONG		nZoneIndex;
		LONG		nRemainSec;
		LONG		nGuildIndex1;
		CTString	strGuildName1;
		LONG		nGuildIndex2;
		CTString	strGuildName2;
		LONG		nGuildIndex3;
		CTString	strGuildName3;

		(*istr) >> nZoneIndex;
		(*istr) >> nRemainSec;
		(*istr) >> nGuildIndex1;
		(*istr) >> strGuildName1;
		(*istr) >> nGuildIndex2;
		(*istr) >> strGuildName2;
		(*istr) >> nGuildIndex3;
		(*istr) >> strGuildName3;

		_pUISWDoc->StartCastle(nZoneIndex, nRemainSec, nGuildIndex1, strGuildName1, nGuildIndex2, strGuildName2, nGuildIndex3, strGuildName3);
	}
	break;
	case MSG_GUILD_WAR_POINT:
	{
		LONG		nRemainSec;
		LONG		nGuildIndex1;
		CTString	strGuildName1;
		LONG		nGuildPoint1;
		LONG		nGuildIndex2;
		CTString	strGuildName2;
		LONG		nGuildPoint2;
		LONG		nGuildIndex3;
		CTString	strGuildName3;
		LONG		nGuildPoint3;
		LONG		nMyPoint;
		LONG		nDefensPoint;

		(*istr) >> nRemainSec;
		(*istr) >> nGuildIndex1;
		(*istr) >> strGuildName1;
		(*istr) >> nGuildPoint1;
		(*istr) >> nGuildIndex2;
		(*istr) >> strGuildName2;
		(*istr) >> nGuildPoint2;
		(*istr) >> nGuildIndex3;
		(*istr) >> strGuildName3;
		(*istr) >> nGuildPoint3;
		(*istr) >> nMyPoint;
		(*istr) >> nDefensPoint;

		SGuild Guild1, Guild2, Guild3;

		Guild1.SetGuildInfo(nGuildIndex1, strGuildName1, nGuildPoint1);
		Guild2.SetGuildInfo(nGuildIndex2, strGuildName2, nGuildPoint2);
		Guild3.SetGuildInfo(nGuildIndex3, strGuildName3, nGuildPoint3);

		_pUISWDoc->UpdatePoint(nRemainSec, Guild1, Guild2, Guild3, nMyPoint, nDefensPoint);
	}
	break;
	case MSG_GUILD_WAR_NOTICE_REMAIN_FIELD_TIME:
	{
		LONG		nRemainSec;
		LONG		nZoneIndex;

		(*istr) >> nZoneIndex;
		(*istr) >> nRemainSec;

		_pUISWDoc->RemainFiledTime(nZoneIndex, nRemainSec);
	}
	break;
	case MSG_GUILD_WAR_NOTICE_TIME:
	{
		LONG		nZoneIndex;
		SBYTE		nMonth;
		SBYTE		nDay;
		SBYTE		nHour;
		SBYTE		nMin;

		(*istr) >> nZoneIndex;
		(*istr) >> nMonth;
		(*istr) >> nDay;
		(*istr) >> nHour;
		(*istr) >> nMin;

		_pUISWDoc->TimeConfirm(nZoneIndex, nMonth, nDay, nHour, nMin);
	}
	break;
	case MSG_GUILD_WAR_NOTICE_TIME_REMAIN:
	{
		LONG		nZoneIndex;
		SBYTE		nMin;

		(*istr) >> nZoneIndex;
		(*istr) >> nMin;

		_pUISWDoc->RemainStartTime(nZoneIndex, nMin);
	}
	break;
	case MSG_GUILD_WAR_CASTLE_STATE:
	{
		LONG		nZoneIndex;
		LONG		nState;
		LONG		nGateState;
		LONG		nRemainSec;
		LONG		nGuildIndex1;
		CTString	strGuildName1;
		LONG		nGuildPoint1;
		LONG		nGuildIndex2;
		CTString	strGuildName2;
		LONG		nGuildPoint2;
		LONG		nGuildIndex3;
		CTString	strGuildName3;
		LONG		nGuildPoint3;
		LONG		nMyPoint;
		LONG		nDefensPoint;

		(*istr) >> nZoneIndex;
		(*istr) >> nState;
		(*istr) >> nGateState;
		(*istr) >> nRemainSec;
		// WSS_DRATAN_SIEGEWARFARE 070723 ------------------>><<
		// ���ź ������ ����Ʈ ���� �����͸� ���� �ʴ´�.
		if (nZoneIndex == 7)
		{
			(*istr) >> nGuildIndex1;
			(*istr) >> strGuildName1;
			(*istr) >> nGuildPoint1;
			(*istr) >> nGuildIndex2;
			(*istr) >> strGuildName2;
			(*istr) >> nGuildPoint2;
			(*istr) >> nGuildIndex3;
			(*istr) >> strGuildName3;
			(*istr) >> nGuildPoint3;
			(*istr) >> nMyPoint;
			(*istr) >> nDefensPoint;

			SGuild Guild1, Guild2, Guild3;

			Guild1.SetGuildInfo(nGuildIndex1, strGuildName1, nGuildPoint1);
			Guild2.SetGuildInfo(nGuildIndex2, strGuildName2, nGuildPoint2);
			Guild3.SetGuildInfo(nGuildIndex3, strGuildName3, nGuildPoint3);

			_pUISWDoc->CastleState(nZoneIndex, nState, nGateState, nRemainSec, Guild1, Guild2, Guild3, nMyPoint, nDefensPoint);
		}
		else if (nZoneIndex == 4)
		{
			_pUISWDoc->CastleState(nZoneIndex, nState, nGateState, nRemainSec);
		}


	}
	break;
	case MSG_GUILD_WAR_GATE_STATE:
	{
		LONG lOldGate;
		LONG lNewGate;
		(*istr) >> lOldGate;
		(*istr) >> lNewGate;

		_pUISWDoc->SetGateState(lOldGate, lNewGate);

	}
	break;

	case MSG_GUILD_WAR_ATTACK_SYMBOL:
	{
		LONG lChaIndex;
		(*istr) >> lChaIndex;
	}
	break;

	case MSG_GUILD_WAR_END:
	{
		LONG		nZoneIndex;
		BYTE		nWinDefense;
		LONG		nOwnerGuildIndex;
		CTString	strOwnerGuildName;
		LONG		nOwnerIndex;
		CTString	strOwnerName;
		LONG		nNextMonth;
		LONG		nNextDay;
		LONG		nNextWeek;
		LONG		nNextHour;

		(*istr) >> nZoneIndex;
		(*istr) >> nWinDefense;
		(*istr) >> nOwnerGuildIndex;
		(*istr) >> strOwnerGuildName;
		(*istr) >> nOwnerIndex;
		(*istr) >> strOwnerName;
		(*istr) >> nNextMonth;
		(*istr) >> nNextDay;
		(*istr) >> nNextHour;
		(*istr) >> nNextWeek;

		_pUISWDoc->EndWar(nZoneIndex, nWinDefense, nOwnerGuildIndex, strOwnerGuildName, nOwnerIndex, strOwnerName, nNextMonth, nNextDay, nNextWeek, nNextHour);
	}
	break;
	case MSG_GUILD_WAR_SET_TIME_REP:
	{
		LONG		nErrorCode;
		SBYTE		nMonth;
		SBYTE		nDay;
		SBYTE		nHour;
		SBYTE		nMin;

		(*istr) >> nErrorCode;
		(*istr) >> nMonth;
		(*istr) >> nDay;
		(*istr) >> nHour;
		(*istr) >> nMin;


		if (nErrorCode != MSG_GUILD_ERROR_OK) _pUISWDoc->ErrorProc(nErrorCode);
		else
		{
			_pUISWDoc->SetTimeRep(nMonth, nDay, nHour, nMin);
		}

	}
	break;
	case MSG_GUILD_WAR_INVALID_COMMAND:
	{
		BYTE		nReqMsgType;
		(*istr) >> nReqMsgType;

		_pUISWDoc->InvalidCommand(nReqMsgType);
	}
	break;

	// Date : 2005-09-06(���� 11:03:59), By Lee Ki-hwan 
	case MSG_GUILD_STASH_HISTORY_REP:
	{
		LONG	nErrorCode;

		LONG		lMonth, lDay;
		LONGLONG	llMoney;

		(*istr) >> nErrorCode;

		if (nErrorCode != MSG_GUILD_STASH_ERROR_OK)
		{
			pUIManager->GetGuildStash()->ErrorProc(nErrorCode, ubType);
			return;
		}

		pUIManager->GetGuildStash()->ResetTakeInfo();
		for (int i = 0; i < 7; i++)
		{
			(*istr) >> lMonth;
			(*istr) >> lDay;
			(*istr) >> llMoney;

			pUIManager->GetGuildStash()->AddTakeInfo(lMonth, lDay, llMoney);
		}
		//pUIManager->GetGuildStash()->OpenView();

	}
	break;

	case MSG_GUILD_STASH_VIEW_REP:
	{

		LONG	nErrorCode;
		LONGLONG	llMoney;

		(*istr) >> nErrorCode;

		if (nErrorCode != MSG_GUILD_STASH_ERROR_OK)
		{
			pUIManager->GetGuildStash()->ErrorProc(nErrorCode, ubType);
			return;
		}

		(*istr) >> llMoney;

		pUIManager->GetGuildStash()->OpenTake(llMoney);
	}
	break;

	case MSG_GUILD_STASH_TAKE_REP:
	{
		LONG	nErrorCode;
		(*istr) >> nErrorCode;

		if (nErrorCode != MSG_GUILD_STASH_ERROR_OK)
		{
			pUIManager->GetGuildStash()->ErrorProc(nErrorCode, ubType);
			return;
		}

		pUIManager->GetGuildStash()->Message(MSGCMD_GUILDSTASH_INFO, _S(2078, "�ݾ��� ���������� ���� �Ǿ����ϴ�. "), UMBS_OK);

	}
	break;

	case MSG_NEW_GUILD_INCLINE_ESTABLISH:
	case MSG_NEW_GUILD_INFO:
	case MSG_NEW_GUILD_MEMBERLIST:
	case MSG_NEW_GUILD_SKILL:
	case MSG_NEW_GUILD_NOTICE:
	case MSG_NEW_GUILD_NOTICE_TRANSMISSION:
	case MSG_NEW_GUILD_MANAGE:
	case MSG_NEW_GUILD_POINT_RANKING:
	case MSG_GUILD_GP_INFO:
	case MSG_GUILD_WAR_SET_TIME_MENU:
	case MSG_GUILD_WAR_GET_TIME_UNI_REP:
	case MSG_NEW_GUILD_MARK_EDIT_FIN:
	case MSG_NEW_GUILD_MARK_EXPIRE:
	case MSG_GUILD_CONTRIBUTE_DATA:
		pUIManager->GetGuild()->ReceiveNewGuildMessage(ubType, istr);
		break;
	case MSG_NEW_GUILD_STASH_LIST:
	case MSG_NEW_GUILD_STASH_KEEP:
	case MSG_NEW_GUILD_STASH_TAKE:
	case MSG_NEW_GUILD_STASH_LOG:
	case MSG_NEW_GUILD_STASH_ERROR:
	case MSG_NEW_GUILD_STASH_LIST_MONEY:	//2013/04/05 jeil ���� ������ ���� 
		pUIManager->GetGuildStash()->ReceiveGuildStashMessage(ubType, istr);
		break;

		// ==> 1107 ��� �ý��� ���� [trylord 11/12/28]
	case MSG_GUILD_MASTER_KICK_REP:
	{	// ��� �߹� ����
		INDEX		idxGuild;
		CTString	strGuildMName;
		CTString	strMessage[3];

		(*istr) >> (INDEX)idxGuild;
		(*istr) >> strGuildMName;

		pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);

		strMessage[0].PrintF(_S(5623, "[%s] ����� ����� [%s]���� ����� ����� ������ ������ �����Դϴ�."), _pNetwork->MyCharacterInfo.strGuildName, strGuildMName);
		strMessage[1].PrintF(" ");
		strMessage[2].PrintF(_S(5624, "���� ���� : �������忡�� ������� ����"));

		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(865, "���"), UMBS_OK, UI_GUILD, MSGCMD_GUILD_ERROR);		// Ȯ�θ� �ϸ� �ǹǷ� MSGCMD_GUILD_ERROR ������
		MsgBoxInfo.AddString(strMessage[0]);
		MsgBoxInfo.AddString(strMessage[1]);
		MsgBoxInfo.AddString(strMessage[2]);
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	break;

	case MSG_GUILD_MASTER_KICK_CANCEL_REP:
	{
		INDEX		idxGuild;
		CTString	strMessage;
		CTString	strSubMessage;

		(*istr) >> (INDEX)idxGuild;

		pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);

		strMessage.PrintF(_S(5625, "[%s] ����� ����� ������ ��ҵǾ����ϴ�."), _pNetwork->MyCharacterInfo.strGuildName);

		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(865, "���"), UMBS_OK, UI_GUILD, MSGCMD_GUILD_ERROR);		// Ȯ�θ� �ϸ� �ǹǷ� MSGCMD_GUILD_ERROR ������
		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	break;

	case MSG_GUILD_MASTER_KICK_STATUS:
	{
		INDEX		idxGuild;
		LONG		lStatus;

		(*istr) >> idxGuild;
		(*istr) >> (LONG)lStatus;

		_pNetwork->MyCharacterInfo.iGuildMasterKickStatus = (int)lStatus;
	}
	break;

	case MSG_GUILD_REMOTE_JOIN_REQ:
	{
		CTString	strMessage;
		CTString	strTarget;
		CTString	strOwner;
		LONG		lType;
		UI_MSGCMD	eMsgCmd;

		(*istr) >> strTarget;
		(*istr) >> strOwner;
		(*istr) >> lType;

		pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);

		pUIManager->GetGuild()->SetRemoteGuildJoinTaget(strOwner);

		if (strcmp(strOwner, _pNetwork->MyCharacterInfo.name) == 0)
		{	// �ڱ� �ڽ��̹Ƿ� ���������� ��û�Ǿ��ٰ� �޼����� ����ش�
			strMessage.PrintF(_S(5629, "���������� ��尡�� ��û�Ͽ����ϴ�."));

			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(865, "���"), UMBS_OK, UI_GUILD, MSGCMD_GUILD_ERROR);
			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
		else
		{

			if (lType == 0)
			{	// ������ ��û ����
				CUIManager::getSingleton()->CloseMessageBox(MSGCMD_GUILDREMOTE_JOIN_TOUSER);

				strMessage.PrintF(_S(5628, "[%s] �Բ��� ��尡�� ��û�� �ϼ̽��ϴ�. �����Ͻðڽ��ϱ�?"), strOwner);
				eMsgCmd = MSGCMD_GUILDREMOTE_JOIN_TOUSER;
			}
			else if (lType == 1)
			{	// �渶�� ��û ����
				CUIManager::getSingleton()->CloseMessageBox(MSGCMD_GUILDREMOTE_JOIN_TOMASTER);

				strMessage.PrintF(_S(5628, "[%s] �Բ��� ��尡�� ��û�� �ϼ̽��ϴ�. �����Ͻðڽ��ϱ�?"), strOwner);
				eMsgCmd = MSGCMD_GUILDREMOTE_JOIN_TOMASTER;
			}

			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(865, "���"), UMBS_OKCANCEL, UI_GUILD, eMsgCmd);
			MsgBoxInfo.AddString(strMessage);
			CUIManager::getSingleton()->CreateMessageBox(MsgBoxInfo);

		}
	}
	break;

	case MSG_GUILD_REMOTE_JOIN_OK:
	{
		CTString	strMessage;
		LONG		lType;

		(*istr) >> lType;

		pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);
		strMessage.PrintF(_S(982, "��忡 ���ԵǾ����ϴ�."));

		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(865, "���"), UMBS_OK, UI_GUILD, MSGCMD_GUILD_ERROR);
		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	break;

	case MSG_GUILD_REMOTE_JOIN_NO:
	{
		CTString	strMessage;
		LONG		lType;

		(*istr) >> lType;

		pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);
		pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);
		strMessage.PrintF(_S(999, "��� ���� ��û�� ��ҵǾ����ϴ�."));

		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(865, "���"), UMBS_OK, UI_GUILD, MSGCMD_GUILD_ERROR);
		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	break;
	// <== 1107 ��� �ý��� ���� [trylord 11/12/28]
	}
}

// ----------------------------------------------------------------------------
// Name : ReceiveTeachMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveTeachMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (ubType)
	{
	case MSG_TEACH_TEACHER_LIST:		// ���� ����Ʈ
	{
		UBYTE ubSubType;
		(*istr) >> ubSubType;

		switch (ubSubType)
		{
		case MSG_TEACH_TEACHER_LIST_UP:		// ���� ���� ��Ͽ� �ø�
		{
			pUIManager->GetHelper()->SetRegistredTeacher(TRUE);

			CTString strMessage;
			strMessage.PrintF(_S(1347, "[%s]���� �İ��� ��Ͽ� �߰��Ǿ����ϴ�."), _pNetwork->MyCharacterInfo.name);
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
		}
		break;
		case MSG_TEACH_TEACHER_LIST_DN:		// ���� ���� ��Ͽ��� ����
		{
			pUIManager->GetHelper()->SetRegistredTeacher(FALSE);

			CTString strMessage;
			strMessage.PrintF(_S(1348, "[%s]���� �İ��� ��Ͽ��� �����Ǿ����ϴ�."), _pNetwork->MyCharacterInfo.name);
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
		}
		break;
		case MSG_TEACH_TEACHER_LIST_SHOW:
		{
			LONG		lCharIndex;
			CTString	strCharName;
			SBYTE		sbCharJob;
			SBYTE		sbCharJob2;

			GAMEDATAMGR()->GetHelperManager()->ClearHelperList();

			for (int i = 0; i < HELPER_MAX_STUDENTS; ++i)
			{
				(*istr) >> lCharIndex;

				if (lCharIndex != -1)
				{
					(*istr) >> strCharName;
					(*istr) >> sbCharJob;
					(*istr) >> sbCharJob2;

					SLONG fame, cntTeachingStudent, cntCompleteStudent, cntFailStudent;
					(*istr) >> fame;
					(*istr) >> cntTeachingStudent;
					(*istr) >> cntCompleteStudent;
					(*istr) >> cntFailStudent;

					GAMEDATAMGR()->GetHelperManager()->AddToHelperList(lCharIndex, strCharName, -1, sbCharJob, sbCharJob2);
					SBYTE iStartPlayTime;
					SBYTE iEndPlayTime;
					(*istr) >> iStartPlayTime;
					(*istr) >> iEndPlayTime;
					GAMEDATAMGR()->GetHelperManager()->AddToTeacherInfoList(lCharIndex, fame, cntTeachingStudent, cntCompleteStudent, cntFailStudent, iStartPlayTime, iEndPlayTime);
				}
			}
			GAMEDATAMGR()->GetHelperManager()->PrepareOpen();
		}
		break;
		}
	}
	break;

	case MSG_TEACH_TEACHER_REQ:		// ���� ��û ����
	{
		UBYTE ubSubType;
		(*istr) >> ubSubType;

		switch (ubSubType)
		{
		case MSG_TEACH_TEACHER_REQ_REQ:
		{
			LONG		lCharIndex;
			CTString	strCharName;

			(*istr) >> lCharIndex;
			(*istr) >> strCharName;
			pUIManager->GetHelper()->TeacherAccept(lCharIndex, strCharName);
		}
		break;
		case MSG_TEACH_TEACHER_REQ_REJECT:
		{
			//UBYTE		ubCharType;
			LONG		lRejectCharIndex;
			CTString	strCharName;

			pUIManager->CloseMessageBox(MSGCMD_HELPER_STUDENT_ACCEPT);
			pUIManager->CloseMessageBox(MSGCMD_HELPER_BEMYTEACHER_REQ);

			//(*istr) >> ubCharType;
			(*istr) >> lRejectCharIndex;
			(*istr) >> strCharName;
			// ���� ��û ����	: char_type(uc) reject_charindex(n) reject_charname(str)

			if (lRejectCharIndex == _pNetwork->MyCharacterInfo.index)	// ���� ����������...
			{
			}
			else		// �ٸ� ����� ����������...
			{
				CTString strMessage;
				strMessage.PrintF(_S(1349, "[%s]���� �����Ͽ����ϴ�."), strCharName);
				pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
			}

			//_pNetwork->MyCharacterInfo.lTeacherIndex = -1;
		}
		break;

		case MSG_TEACH_TEACHER_REQ_ACCEPT:
		{
			LONG		lTeacherIndex;
			CTString	strTeacherName;
			LONG		lStudentIndex;
			CTString	strStudentName;

			pUIManager->CloseMessageBox(MSGCMD_HELPER_BEMYTEACHER_REQ);

			(*istr) >> lTeacherIndex;
			(*istr) >> strTeacherName;
			(*istr) >> lStudentIndex;
			(*istr) >> strStudentName;

			INDEX		iCurTeachCnt;
			INDEX		iCompleteTeachCnt;
			INDEX		iFailTeachCnt;

			(*istr) >> iCurTeachCnt;
			(*istr) >> iCompleteTeachCnt;
			(*istr) >> iFailTeachCnt;
			// ���� ���		: teacher_index(n) teacher_name(str) student_index(n) student_name(str)

			CTString strMessage;
			if (lStudentIndex == _pNetwork->MyCharacterInfo.index)
			{
				// ���� �л��ε�, ������ ������...
				strMessage.PrintF(_S(1350, "[%s]���� [%s]���� �İ����� �Ǿ����ϴ�."), strTeacherName, strStudentName);
				pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
			}
			else
			{
				pUIManager->GetHelper()->SetMyTeachInfo(iCurTeachCnt, iCompleteTeachCnt, iFailTeachCnt);
				strMessage.PrintF(_S(1351, "[%s]���� [%s]���� �߽����� �Ǿ����ϴ�."), strStudentName, strTeacherName);
				pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);
			}
		}
		break;
		case MSG_TEACH_TEACHER_GIVEUP:
		{
			// �л� ���� ��û	: teacher_index(n) teacher_name(str) student_index(n) student_name(str)

			LONG		lTeacherIndex;
			CTString	strTeacherName;
			LONG		lStudentIndex;
			CTString	strStudentName;
			INDEX		iGiveupCount;

			(*istr) >> lTeacherIndex;
			if (lTeacherIndex != -1)
			{
				(*istr) >> strTeacherName;
			}
			(*istr) >> lStudentIndex;
			(*istr) >> strStudentName;
			(*istr) >> iGiveupCount;

			if (lTeacherIndex == _pNetwork->MyCharacterInfo.index)
			{	// ���� ������ ��,
				if (iGiveupCount == -1)
				{
					INDEX iCurTeachCnt, iCompleteTeachCnt, iFailTeachCnt;
					(*istr) >> iCurTeachCnt;
					(*istr) >> iCompleteTeachCnt;
					(*istr) >> iFailTeachCnt;
					pUIManager->GetHelper()->SetMyTeachInfo(iCurTeachCnt, iCompleteTeachCnt, iFailTeachCnt);
				}

				CTString strMessage;
				strMessage.PrintF(_S(5096, "[%s]�԰��� �İ��� ���谡 �����Ǿ����ϴ�."), strStudentName);
				pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);

				GAMEDATAMGR()->GetHelperManager()->DelFromHelperList(lStudentIndex);
				GAMEDATAMGR()->GetHelperManager()->PrepareOpen();
			}
			else if (lStudentIndex == _pNetwork->MyCharacterInfo.index)
			{	// ���� �л��� ��,
				if (iGiveupCount != -1)
				{
					_pNetwork->MyCharacterInfo.iStudentGiveUpCnt = iGiveupCount;
				}
				CTString strMessage;
				strMessage.PrintF(_S(5096, "[%s]�԰��� �İ��� ���谡 �����Ǿ����ϴ�."), _pNetwork->MyCharacterInfo.strTeacherName);
				pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);

				_pNetwork->MyCharacterInfo.lTeacherIndex = -1;
				_pNetwork->MyCharacterInfo.strTeacherName.Clear();
				GAMEDATAMGR()->GetHelperManager()->ClearHelperList();
				pUIManager->GetHelper_GuardianInfo()->CloseUI();
			}
		}
		break;
		}
	}
	break;
	case MSG_TEACH_END:			// ����
	{
		LONG		lTeacherIndex;
		CTString	strTeacherName;
		LONG		lStudentIndex;
		CTString	strStudentName;
		UBYTE		ubEndType;
		SBYTE		sbEvent;
		LONG		lUpFame = 0;
		INDEX		iCurTeachCnt, iCompleteTeachCnt, iFailTeachCnt;

		(*istr) >> lTeacherIndex;
		(*istr) >> strTeacherName;
		(*istr) >> lStudentIndex;
		(*istr) >> strStudentName;
		(*istr) >> ubEndType;
		(*istr) >> sbEvent;
		(*istr) >> lUpFame;
		(*istr) >> iCurTeachCnt;
		(*istr) >> iCompleteTeachCnt;
		(*istr) >> iFailTeachCnt;

		switch (ubEndType)
		{
		case MSG_TEACH_END_FAIL:		// ����
		{
			CTString strMessage;

			// ���� �����̾��� ��...
			if (lTeacherIndex == _pNetwork->MyCharacterInfo.index)
			{
				GAMEDATAMGR()->GetHelperManager()->DelFromHelperList(lTeacherIndex);
				GAMEDATAMGR()->GetHelperManager()->PrepareOpen();
				pUIManager->GetHelper()->SetMyTeachInfo(iCurTeachCnt, iCompleteTeachCnt, iFailTeachCnt);
			}
			// ���� �л��̾��� ��...
			else
			{
				GAMEDATAMGR()->GetHelperManager()->DelFromHelperList(lTeacherIndex);
				GAMEDATAMGR()->GetHelperManager()->PrepareOpen();
				_pNetwork->MyCharacterInfo.lTeacherIndex = -1;
				_pNetwork->MyCharacterInfo.strTeacherName.Clear();
			}

			strMessage.PrintF(_S(5102, "[%s]���� 10�ϵ��� �������� �ʾ� �İ��� ���谡 ���� ����Ǿ����ϴ�."), strStudentName);
			pUIManager->GetChattingUI()->AddSysMessage(strMessage);
		}
		break;

		case MSG_TEACH_END_SUCCESS:		// ����
		{
			CTString strMessage;

			pUIManager->CloseMessageBox(MSGCMD_HELPER_NOTIFY);

			CUIMsgBox_Info	MsgBoxInfo;

			// [KH_070417] �����ǳ� �̺�Ʈ ���� �߰�
			if (IS_EVENT_ON(TEVENT_TEACHER_2007))
				MsgBoxInfo.SetMsgBoxInfo(_S(3344, "������ ���� �̺�Ʈ"), UMBS_OK, UI_NONE, MSGCMD_NULL);
			else
				MsgBoxInfo.SetMsgBoxInfo(_S(1355, "�߽��� �缺 ����"), UMBS_OK, UI_HELPER, MSGCMD_HELPER_NOTIFY);

			// ���� �����̾��� ��...
			if (lTeacherIndex == _pNetwork->MyCharacterInfo.index)
			{
				int iPlusFame = 0;
				// FIXME : �̷��� ���� ���� ������ üũ�ϴ°� ���� �ȵ�...						
				extern UINT g_uiEngineVersion;
				if (g_uiEngineVersion >= 10000)
					iPlusFame = 20;
				else
					iPlusFame = 10;

				if (sbEvent == 1)
				{
#ifndef TEACHER_PRIZE_EVENT_2PAN4PAN		// �İ��� ���� ���� �̺�Ʈ�� �ƴѰ��.
					strMessage.PrintF(_S(1356, "[%s]���� ������ %d�� �Ǿ� �İ��� ���谡 ���� �Ǿ����ϴ�."), strStudentName, LIMIT_GUARDIAN_APP_LEVEL);

					if (lUpFame > 0)
					{
						CTString strAddString;
						strAddString.PrintF(_S(5046, "����ġ�� +%d����Ͽ����ϴ�."), lUpFame);

						strMessage += strAddString;
					}
#else
					iPlusFame = 20;
					// [KH_070417] �����ǳ� �̺�Ʈ ���� �߰� (Ȥ�� ���� ����)
					if (IS_EVENT_ON(TEVENT_TEACHER_2007))
						MsgBoxInfo.AddString(_S(3346, "�����մϴ�. �߽��� �缺�� ���������� �̷�� �� ��� ī���̼��� ȹ�� �Ͽ����ϴ�."));
					else
					{

						strMessage.PrintF(_S(1356, "[%s]���� ������ %d�� �Ǿ� �İ��� ���谡 ���� �Ǿ����ϴ�."), strStudentName, LIMIT_GUARDIAN_APP_LEVEL);

						if (lUpFame > 0)
						{
							CTString strAddString;
							strAddString.PrintF(_S(5046, "����ġ�� +%d����Ͽ����ϴ�."), lUpFame);

							strMessage += strAddString;
						}
					}
#endif							
				}
				else
				{
					// [KH_070417] �����ǳ� �̺�Ʈ ���� �߰�
					if (IS_EVENT_ON(TEVENT_TEACHER_2007))
						MsgBoxInfo.AddString(_S(3346, "�����մϴ�. �߽��� �缺�� ���������� �̷�� �� ��� ī���̼��� ȹ�� �Ͽ����ϴ�."));
					else
					{
						strMessage.PrintF(_S(1356, "[%s]���� ������ %d�� �Ǿ� �İ��� ���谡 ���� �Ǿ����ϴ�."), strStudentName, LIMIT_GUARDIAN_APP_LEVEL);

						if (lUpFame > 0)
						{
							CTString strAddString;
							strAddString.PrintF(_S(5046, "����ġ�� +%d����Ͽ����ϴ�."), lUpFame);

							strMessage += strAddString;
						}
					}
				}
				pUIManager->GetHelper()->SetMyTeachInfo(iCurTeachCnt, iCompleteTeachCnt, iFailTeachCnt);
				GAMEDATAMGR()->GetHelperManager()->DelFromHelperList(lStudentIndex);
				GAMEDATAMGR()->GetHelperManager()->PrepareOpen();
			}
			// ���� �л��̾��� ��...
			else
			{
#ifndef TEACHER_PRIZE_EVENT_2PAN4PAN		// �İ��� ���� ���� �̺�Ʈ�� �ƴѰ��.
				if (sbEvent == 1)
				{
					// NOTE : �̺�Ʈ�϶�...
					strMessage.PrintF(_S(2079, "�İ��� �ý����� ���Ͽ� ���������� �����Ͽ����Ƿ� �̺�Ʈ���� ���޵˴ϴ�."));
				}
				else
				{
					strMessage.PrintF(_S(1357, "������ %d�� �Ǿ� [%s]�԰��� �İ��� ���谡 ���� �Ǿ����ϴ�."), LIMIT_GUARDIAN_APP_LEVEL, strTeacherName);
				}
#else
				// [KH_070417] �����ǳ� �̺�Ʈ ���� �߰�
				if (IS_EVENT_ON(TEVENT_TEACHER_2007))
					MsgBoxInfo.AddString(_S(3347, "�����մϴ�. ���� 20�� �޼��Ͽ� �����ǳ� �̺�Ʈ ��� ����� �̺�Ʈ���� ȹ�� �Ͽ����ϴ�."));
				else
					strMessage.PrintF(_S(1357, "������ %d�� �Ǿ� [%s]�԰��� �İ��� ���谡 ���� �Ǿ����ϴ�."), LIMIT_GUARDIAN_APP_LEVEL, strTeacherName);
#endif

				GAMEDATAMGR()->GetHelperManager()->ClearHelperList();
				pUIManager->GetHelper_GuardianInfo()->CloseUI();
				pUIManager->GetHelper()->SetMyTeachInfo(0, 0, 0);

				_pNetwork->MyCharacterInfo.lTeacherIndex = -1;
				_pNetwork->MyCharacterInfo.strTeacherName.Clear();
			}

			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
		break;
		}
	}
	break;
	case MSG_TEACH_INFO:		// ���� ����
	{
		// �ڽ��� �������� �л������� ����...
		SBYTE		sbRegistered;
		SBYTE		sbCharType;
		LONG		lTeacherIndex;
		LONG		lTeacherLevel;
		CTString	strTeacherName;
		SBYTE		sbTeacherJob;
		SBYTE		sbTeacherJob2;

		(*istr) >> sbRegistered;
		(*istr) >> sbCharType;

		// �İ������� ��ϵǾ� �ִ� ���.				
		pUIManager->GetHelper()->SetRegistredTeacher(sbRegistered);

		// ���� ������ ������ ��ü ������ �ޱ� ������ ������ �ʱ�ȭ�Ͽ� �����Ѵ�. [10/31/2011 ldy1978220]
		GAMEDATAMGR()->GetHelperManager()->ClearHelperList();

		// �ڽ��� �л��� ���, �̹� �İ��� ����.
		if (sbCharType == MSG_TEACH_STUDENT_TYPE)
		{
			INDEX iGiveUpCount;
			(*istr) >> iGiveUpCount;
			_pNetwork->MyCharacterInfo.iStudentGiveUpCnt = iGiveUpCount;

			(*istr) >> lTeacherIndex;
			(*istr) >> lTeacherLevel;
			(*istr) >> strTeacherName;
			(*istr) >> sbTeacherJob;
			(*istr) >> sbTeacherJob2;

			_pNetwork->MyCharacterInfo.lTeacherIndex = lTeacherIndex;
			_pNetwork->MyCharacterInfo.strTeacherName = strTeacherName;

			SLONG fame, cntTeachingStudent, cntCompleteStudent, cntFailStudent;
			(*istr) >> fame;
			(*istr) >> cntTeachingStudent;
			(*istr) >> cntCompleteStudent;
			(*istr) >> cntFailStudent;

			GAMEDATAMGR()->GetHelperManager()->AddToHelperList(lTeacherIndex, strTeacherName, lTeacherLevel, sbTeacherJob, sbTeacherJob2);
			GAMEDATAMGR()->GetHelperManager()->AddToTeacherInfoList(lTeacherIndex, fame, cntTeachingStudent, cntCompleteStudent, cntFailStudent);
			GAMEDATAMGR()->GetHelperManager()->PrepareOpen();

		}
		// �ڽ��� ������ ���.
		else if (sbCharType == MSG_TEACH_TEACHER_TYPE)
		{
			// �л��� ����� ������.
			//pUIManager->GetHelper()->ClearHelperList();
			int nLoopCnt = 8;
			INDEX iCurTeachCnt, iCompleteTeachCnt, iFailTeachCnt;

			(*istr) >> iCurTeachCnt;
			(*istr) >> iCompleteTeachCnt;
			(*istr) >> iFailTeachCnt;
			pUIManager->GetHelper()->SetMyTeachInfo(iCurTeachCnt, iCompleteTeachCnt, iFailTeachCnt);
			nLoopCnt = 10;

			for (int i = 0; i < nLoopCnt; ++i)
			{
				LONG		lStudentIndex;
				LONG		lStudentLevel;
				CTString	strStudentName;
				SBYTE		sbStudentJob;
				SBYTE		sbStudentJob2;

				(*istr) >> lStudentIndex;

				if (lStudentIndex != -1)
				{
					(*istr) >> lStudentLevel;
					(*istr) >> strStudentName;
					(*istr) >> sbStudentJob;
					(*istr) >> sbStudentJob2;
					GAMEDATAMGR()->GetHelperManager()->AddToHelperList(lStudentIndex, strStudentName, lStudentLevel, sbStudentJob, sbStudentJob2);
					CTString strFirstDate, strFinalDate;

					GAMEDATAMGR()->GetHelperManager()->AddToStudentInfoList(lStudentIndex, strFirstDate.str_String, strFinalDate.str_String);
				}
			}
			GAMEDATAMGR()->GetHelperManager()->PrepareOpen();
		}
	}
	break;
	case MSG_TEACH_STUDENT_LEVELUP:		// �л� ������
	{
		// FIXME : ������ ����Ǵ°� ���� �Ǿ�� ��.
		LONG		lStudentIndex;
		LONG		lStudentLevel;
		CTString	strStudentName;
		SBYTE		sbStudentJob;
		SBYTE		sbStudentJob2;

		(*istr) >> lStudentIndex;
		(*istr) >> lStudentLevel;
		(*istr) >> strStudentName;
		(*istr) >> sbStudentJob;
		(*istr) >> sbStudentJob2;

		GAMEDATAMGR()->GetHelperManager()->ChangeHelperLevel(lStudentIndex, lStudentLevel);

		// ���� �ش� �л��ΰ��...
		if (lStudentIndex == _pNetwork->MyCharacterInfo.index)
		{
			// String Index : 5084, 5085, 5086, 5087, 5088, 5089, 5090, 5091, 5092, 5093
			if (lStudentLevel % 5 == 0)
			{
				int nIndex = lStudentLevel / 5 + 5083;
				CTString strMessage;
				strMessage.PrintF(_S(nIndex, ""), _pNetwork->MyCharacterInfo.name, lStudentLevel);
				_UIAutoHelp->SetGMNotice(strMessage, 0x38FFD7FF);
			}
			GAMEDATAMGR()->GetHelperManager()->ChangeHelperLevel(lStudentIndex, lStudentLevel);
		}

		GAMEDATAMGR()->GetHelperManager()->PrepareOpen();
	}
	break;
	case MSG_TEACH_ERR:			// ����
	{
		UBYTE ubErrorType;
		CTString strMessage;

		pUIManager->CloseMessageBox(MSGCMD_HELPER_NOTIFY);
		pUIManager->CloseMessageBox(MSGCMD_HELPER_BEMYTEACHER);
		pUIManager->CloseMessageBox(MSGCMD_HELPER_BEMYTEACHER_REQ);

		(*istr) >> ubErrorType;

		switch (ubErrorType)
		{
		case MSG_TEACH_ERR_SYSTEM:					// ������ �ȵǴ� ����
			ASSERTALWAYS("Invalid Error Message!!!");
			break;
		case MSG_TEACH_ERR_TEACHER_LEVEL:			// ���� ���ɷ����� �ƴ�
			strMessage.PrintF(_S(1358, "�İ������� ��� ������ ������ �ƴմϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_TEACH_ERR_TEACHER_LIST_ALREADY:	// �̹� ���� ����Ʈ�� ����
			strMessage.PrintF(_S(1359, "�̹� �İ��� ����Ʈ�� ��ϵǾ� �ֽ��ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_TEACH_ERR_TEACHER_LIST_NOT:		// ���� ����Ʈ�� ���� ����
			strMessage.PrintF(_S(1360, "�İ��� ����Ʈ�� ��� �Ǿ� ���� �ʽ��ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_TEACH_ERR_TEACHER_REQ_ALREADY:		// �̹� ��û��
			strMessage.PrintF(_S(1361, "�̹� ��û���Դϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_TEACH_ERR_STUDENT_LEVEL:			// �л� ���ɷ����� �ƴ�
			strMessage.PrintF(_S(1362, "�߽����� ������ ������ �ƴմϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_TEACH_ERR_HAVE_TEACHER:			// �̹� ������ ����
			strMessage.PrintF(_S(1363, "�̹� �İ����� �ֽ��ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_TEACH_ERR_TEACHER_NOT_CONNECT:		// ������ �������� �ƴ�
			strMessage.PrintF(_S(1364, "�İ����� �������� �ƴմϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_TEACH_ERR_STUDENT_NOT_CONNECT:		// �л��� �������� �ƴ�
			strMessage.PrintF(_S(1365, "�߽����� �������� �ƴմϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_TEACH_ERR_TEACHER_FULL:			// ���ڰ� �� �� ����
			strMessage.PrintF(_S(1366, "�� �̻� �߽����� ���� �� �����ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_TEACH_ERR_NOE_REQ:					// ��û�� �� ����
			strMessage.PrintF(_S(1367, "��û�� ���� �����ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_TEACH_ERR_NOMORE_STUDENT:			// ���̻� �л� �� �� ����
			strMessage.PrintF(_S(1368, "�� �̻� �߽����� �� �� �����ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_TEACH_ERR_FAME:
			strMessage.PrintF(_S(1340, "����ġ�� �����մϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		default:
			ASSERTALWAYS("Invalid Error Message!!!");
			break;
		}
	}
	break;
	case MSG_TEACH_RENEWER_TEACH_GIFT:
	{
		UBYTE ubErrorType;
		CTString strMessage;

		(*istr) >> ubErrorType;
		switch (ubErrorType)
		{
		case MSG_TEACH_GIFT_ERROR:
		{
			strMessage.PrintF(_S(1722, "������ ������ �� �ִ� ������ �ƴմϴ�"));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		}
		break;
		case MSG_TEACH_GIFT_SUC:
		{

		}
		break;
		case MSG_TEACH_GIFT_NOMORE:
		{
			strMessage.PrintF(_S(4676, "��� ������ �޾ҽ��ϴ�. ���̻� ������� �������� �����ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		}
		break;
		}
	}
	break;
	case MSG_TEACH_LOGIN:
	{
		SBYTE iTeachType;
		INDEX iCharIndex;
		CTString strName, strMessage;

		(*istr) >> iTeachType;
		(*istr) >> iCharIndex;
		(*istr) >> strName;
		if (iTeachType == MSG_TEACH_STUDENT_TYPE)
		{	// �л��� ���,
			strMessage.PrintF(_S(5095, "�߽��� [%s]���� ���ӿ� �����ϼ̽��ϴ�."), strName);
		}
		else
		{
			strMessage.PrintF(_S(5094, "�İ��� [%s]���� ���ӿ� �����ϼ̽��ϴ�."), strName);
		}
		pUIManager->GetChattingUI()->AddSysMessage(strMessage);
	}
	break;
	}
}

void CSessionState::ReceiveRebornMessage(CNetworkMessage* istr)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(istr->GetBuffer());

	CUIManager* pUIManager = CUIManager::getSingleton();

	CTString strMessage;

	switch (pBase->subType)
	{
	case MSG_REBORN_ERROR_NOCONDITION_LEVEL:
		strMessage.PrintF(_S(8335, "Sorry, you must be hight level to start a new reborn"));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		break;
	case MSG_REBORN_ERROR_NOCONDITION_MAX_REBORN:
		strMessage.PrintF(_S(8336, "Sorry, you already achieved the max reborn: %d"), 5);
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		break;
	case MSG_REBORN_ERROR_NOCONDITION_WEARING_ITEM:
		strMessage.PrintF(_S(8341, "You must remove all wearing items to proceed"));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		break;
	case MSG_REBORN_REP:
	{
		ResponseClient::reborn* pPack = reinterpret_cast<ResponseClient::reborn*>(istr->GetBuffer());
		if (pPack->nIndex == _pNetwork->MyCharacterInfo.index)
		{
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(8339, "Reborn system"), UMBS_OK, UI_NONE, MSGCMD_NULL);
			strMessage.PrintF(_S(8334, "Congratulations! You are starting a new reborn. Your current reborn is %d"), pPack->currentReborn);
			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
		break;
	}
	}
}
// ----------------------------------------------------------------------------
// Name : ReceiveChangeJobMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveChangeJobMessage(CNetworkMessage* istr)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(istr->GetBuffer());

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (pBase->subType)
	{
	case MSG_CHANGEJOB_REP:			// ���� �˸�		: charindex(n) job(c) job2(c)
	{
		ResponseClient::changeJob* pPack = reinterpret_cast<ResponseClient::changeJob*>(istr->GetBuffer());

		// ��
		if (pPack->nIndex == _pNetwork->MyCharacterInfo.index)
		{
			_pNetwork->MyCharacterInfo.job = pPack->job1;
			_pNetwork->MyCharacterInfo.job2 = pPack->job2;

			CTString strMessage;
			strMessage.PrintF(_S(1369, "[%s]�� ���� �Ǿ����ϴ�."), CJobInfo::getSingleton()->GetName(pPack->job1, pPack->job2));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);

			// ����� ����Ʈ �϶���...
			if (pPack->job1 == SORCERER &&
				pPack->job2 == 2)
			{
				pUIManager->GetQuickSlot()->RemoveSummonSkill();
			}

			pUIManager->GetSkillNew()->InitArrayData();

			if (pUIManager->GetSkillNew()->IsVisible() == TRUE || pUIManager->GetSkillNew()->GetHide() == FALSE)
				pUIManager->GetSkillNew()->UpdateSkillData(true);
		}
		// Ÿ ĳ����
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pPack->nIndex);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTarget->m_nType = pPack->job1;
				pTarget->cha_iJob2 = pPack->job2;
			}
		}
	}
	break;
	case MSG_CHANGEJOB_RESET_REP:	// ���� ���� �˸�	: charindex(n) job(c)
	{
		ResponseClient::changeJobReset* pPack = reinterpret_cast<ResponseClient::changeJobReset*>(istr->GetBuffer());

		// ��
		if (pPack->charIndex == _pNetwork->MyCharacterInfo.index)
		{
			CTString strMessage;
			strMessage.PrintF(_S(1370, "[%s] ������ ���� �Ǿ����ϴ�."), CJobInfo::getSingleton()->GetName(_pNetwork->MyCharacterInfo.job, _pNetwork->MyCharacterInfo.job2));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_NORMAL);

			// ����� ����Ʈ �϶���...
			if (_pNetwork->MyCharacterInfo.job == SORCERER &&
				_pNetwork->MyCharacterInfo.job2 == 1)
			{
				pUIManager->GetQuickSlot()->RemoveElementalSkill();
			}

			_pNetwork->MyCharacterInfo.job = pPack->job;
			_pNetwork->MyCharacterInfo.job2 = 0;

			pUIManager->GetInitJob()->CloseInitJob();

			pUIManager->GetSkillNew()->InitArrayData();

			if (pUIManager->GetSkillNew()->IsVisible() == TRUE || pUIManager->GetSkillNew()->GetHide() == FALSE)
				pUIManager->GetSkillNew()->UpdateSkillData(true);
		}
		// Ÿ ĳ����.
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pPack->charIndex);

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

				pTarget->m_nType = pPack->job;
				pTarget->cha_iJob2 = 0;
			}
		}
	}
	break;
	case MSG_CHANGEJOB_ERROR:			// ����
	{
		ResponseClient::changeJobError* pPack = reinterpret_cast<ResponseClient::changeJobError*>(istr->GetBuffer());
		CTString strMessage;

		switch (pPack->errorCode)
		{
		case MSG_CHANGEJOB_ERROR_OK:
			break;
		case MSG_CHANGEJOB_ERROR_WRONGMSG:
			strMessage.PrintF(_S(1371, "�߸� �� �޼����Դϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_CHANGEJOB_ERROR_ALREADY:
			strMessage.PrintF(_S(1372, "�̹� �����߽��ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_CHANGEJOB_ERROR_NOCONDITION_LEVEL:
			strMessage.PrintF(_S(1373, "������ �����Ͽ� ������ �� �����ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_CHANGEJOB_ERROR_NOCONDITION_SKILL:
			strMessage.PrintF(_S(1374, "��ų�� ��� ������ �� �����ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_CHANGEJOB_ERROR_NOCONDITION_SKILLLEVEL:
			strMessage.PrintF(_S(1375, "��ų ������ �����Ͽ� ������ �� �����ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_CHANGEJOB_ERROR_NOMONEY:
			strMessage.PrintF(_S(1376, "���� �����Ͽ� ������ �� �����ϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		case MSG_CHANGEJOB_ERROR_NOITEM:
			strMessage.PrintF(_S(2908, "There is no item to be exchanged"));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			break;
		default:
			ASSERTALWAYS("Invalid Error Message!!!");
			break;
		}
	}
	break;
	}
}

//------------------------------------------------------------------------------
// CSessionState::ReceiveMessengerMessage
// Explain:  �޽��� ���� �޼��� ó��
// Date : 2005-05-21,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CSessionState::ReceiveMessengerMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (ubType)
	{
		// ģ�� ����Ʈ�� �޴´�.
	case MSG_FRIEND_MEMBERLIST:
	{
		LONG		nCount;
		LONG		lCharIndex;
		LONG		lGroupIndex;
		CTString	strReqCharName;
		LONG		lJob;
		LONG		lCondition;

		(*istr) >> nCount;
		int i;
		for (i = 0; i < nCount; i++)
		{
			(*istr) >> lCharIndex;
			(*istr) >> strReqCharName;
			(*istr) >> lJob;
			(*istr) >> lCondition;
			(*istr) >> lGroupIndex;

			pUIManager->GetMessenger()->AddFriendList(lCharIndex, lGroupIndex, strReqCharName, (eJob)lJob, (eCondition)lCondition, false);
		}
	}
	break;
	default:
		break;
	}
}

void CSessionState::ReceiveMessengerExMessage(CNetworkMessage* istr)
{
	UBYTE	exType;
	(*istr) >> exType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (exType)
	{
	case MSG_EX_MESSENGER_GROUP_LIST:
	{
		LONG		nCount;
		LONG		nGroupIndex;
		CTString	strGroupName;

		(*istr) >> nCount;
		for (int i = 0; i < nCount; ++i)
		{
			(*istr) >> nGroupIndex;
			(*istr) >> strGroupName;
			pUIManager->GetMessenger()->AddGroup(nGroupIndex, strGroupName);
		}

		pUIManager->GetMessenger()->SetDefaultGroupName(_S(2986, "��Ʈī����ģ��"));

	}
	break;

	case MSG_EX_MESSENGER_GROUP_ADD:
	{
		LONG		nGroupIndex;
		CTString	strName;

		(*istr) >> nGroupIndex;
		(*istr) >> strName;
		pUIManager->GetMessenger()->AddGroup(nGroupIndex, strName);

	}
	break;

	case MSG_EX_MESSENGER_GROUP_DEL:
	{
		//LONG		nGroupIndex;  

		//(*istr) >> nGroupIndex;
	}
	break;

	case MSG_EX_MESSENGER_GROUP_CHANGE:
	{
		LONG		nGroupIndex;
		CTString	strName;

		(*istr) >> nGroupIndex;
		(*istr) >> strName;

		pUIManager->GetMessenger()->RenameGroup(nGroupIndex, strName);
	}
	break;

	case MSG_EX_MESSENGER_INVITE:
	{
		LONG		lMakeCharIndex;
		LONG		lChatIndex;
		CTString	strName;

		(*istr) >> lMakeCharIndex;
		(*istr) >> lChatIndex;
		(*istr) >> strName;

		pUIManager->GetMessenger()->SetChat(lMakeCharIndex, lChatIndex, strName);
	}
	break;

	case MSG_EX_MESSENGER_OUT:
	{
		LONG		lMakeCharIndex;
		LONG		lChatIndex;
		CTString	strName;

		(*istr) >> lMakeCharIndex;
		(*istr) >> lChatIndex;
		(*istr) >> strName;

		pUIManager->GetMessenger()->DeleteChatMember(lMakeCharIndex, lChatIndex, strName);
	}
	break;

	case MSG_EX_MESSENGER_CHAT:
	{
		LONG		lMakeCharIndex;
		LONG		lChatIndex;
		LONG		lColIndex;
		CTString	strName;
		CTString	strChat;

		(*istr) >> lMakeCharIndex;
		(*istr) >> lChatIndex;
		(*istr) >> lColIndex;
		(*istr) >> strName;
		(*istr) >> strChat;

		pUIManager->GetMessenger()->RevTalk(lMakeCharIndex, lChatIndex, strName, strChat, lColIndex);
	}


	case MSG_EX_MESSENGER_CHARLIST:
	{
		LONG		lMakeCharIndex;
		LONG		lChatIndex;
		LONG		lCount;
		CTString	strCharName;

		(*istr) >> lMakeCharIndex;
		(*istr) >> lChatIndex;
		(*istr) >> lCount;

		for (int i = 0; i < lCount; ++i)
		{
			(*istr) >> strCharName;
			pUIManager->GetMessenger()->AddChatMember(lMakeCharIndex, lChatIndex, strCharName);
		}
	}
	break;

	case MSG_EX_MESSENGER_BLOCK:
	{
		BYTE		cError;
		LONG		lCharIndex;
		CTString	strCharName;

		(*istr) >> cError;
		(*istr) >> lCharIndex;
		(*istr) >> strCharName;

		pUIManager->GetMessenger()->Block(cError, lCharIndex, strCharName);
	}
	break;

	case MSG_EX_MESSENGER_RELEASE_BLOCK:
	{
		BYTE		cError;
		LONG		lCharIndex;
		CTString	strCharName;

		(*istr) >> cError;
		(*istr) >> lCharIndex;
		(*istr) >> strCharName;

		pUIManager->GetMessenger()->UnBlock(cError, lCharIndex, strCharName);
	}
	break;


	case MSG_EX_MESSENGER_BLOCK_LIST:
	{
		LONG		lCount;
		LONG		lCharIndex;
		CTString	strCharName;

		(*istr) >> lCount;


		for (int i = 0; i < lCount; ++i)
		{
			(*istr) >> lCharIndex;
			(*istr) >> strCharName;
			pUIManager->GetMessenger()->AddFriendList(lCharIndex, -1, strCharName, (eJob)0, (eCondition)0, true);
		}
	}
	break;

	case MSG_EX_MESSENGER_ONE_VS_ONE: // ������ �ε����� Ŭ���̾�Ʈ�� ���� 1:1 ä��
	{
		LONG		lsIndex;
		CTString	strName;
		LONG		lrIndex;
		LONG		lColIndex;
		CTString	strChat;

		(*istr) >> lsIndex;
		(*istr) >> strName;
		(*istr) >> lrIndex;
		(*istr) >> lColIndex;
		(*istr) >> strChat;

		pUIManager->GetMessenger()->RevOneVsOneTalk(lsIndex, lrIndex, strName, strChat, lColIndex);

	}
	break;

	case MSG_EX_MESSENGER_ONE_OFF_LINE:	// 1:1��ȭ���� ��밡 ������ �� ���� ���
	{
		LONG		lsIndex;
		LONG		lrIndex;

		(*istr) >> lsIndex;
		(*istr) >> lrIndex;

		// �ٽõ��ƿ��� ���� �޼����̱� ������ sender�� resiver�� �ٲ��
		pUIManager->GetMessenger()->RevOneVsOneTalk(lrIndex, lsIndex, CTString(""),
			_S(2064, "��ȭ��밡 ���������̿��� �޼����� ������ �� �����ϴ�."), 7 /*RED*/);

	}
	break;
	}
}

// ----------------------------------------------------------------------------
// Name : ReceiveFailMessage()
// Desc : 
// ----------------------------------------------------------------------------
void CSessionState::ReceiveFailMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;

	CTString		strTitle, strMessage;
	CUIMsgBox_Info	MsgBoxInfo;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (ubType)
	{

	case MSG_FAIL_WRONG_CHAR:
		pUIManager->CloseMessageBox(MSG_FAIL_WRONG_CHAR);
		strTitle = _S(191, "Ȯ��");
		strMessage = _S(883, "��� �̸��� �߸��� ���ڰ� ���ԵǾ� �ֽ��ϴ�.");
		MsgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);

		break;
	}

}

// EDIT : BS
void CSessionState::MoveOtherServer(ULONG zone, CTString ip, ULONG port)
{
	extern BOOL _bLoginProcess;
	_bLoginProcess = TRUE;
	//extern BOOL _bUseSocket;
	//_bUseSocket = TRUE;

	// ������ ������ �����ٰ�, �ٽ� ������.
	_cmiComm.Reconnect(ip, port);

	// EDIT : BS : 070413 : �ű� ��Ŷ ��ȣȭ
	// EDIT : BS : ��Ŷ ��ȣȭ : ��ȣȭ Ű �ʱ�ȭ
#ifdef CRYPT_NET_MSG
	CNM_InitKeyValue(&_pNetwork->cnmKey);
#ifndef CRYPT_NET_MSG_MANUAL
	CNM_InitKeyValue(&_pNetwork->cnmKeyServer);
#endif // #ifndef CRYPT_NET_MSG_MANUAL
#else
	_pNetwork->cnmKey = CNM_INIT_KEY;
#endif // #ifdef CRYPT_NET_MSG

	// �α��� ������ ���� ��, ���ο� ������ ������ �õ��մϴ�.
	CNetworkMessage nmLoginNew((UBYTE)MSG_LOGIN);			// �α��� �޽��� ������.	
	ULONG version;
	version = 700;
	nmLoginNew << version;
	nmLoginNew << (unsigned char)MSG_LOGIN_RE;		// ���� �̵�

	CTString _strUserID;
	CTString _strUserPW;

	_strUserID = _pNetwork->m_strUserID;
	_strUserPW = _pNetwork->m_strUserPW;
	nmLoginNew << _strUserID;
	nmLoginNew << _strUserPW;

#ifdef CRYPT_NET_MSG
	// EDIT : BS : 070413 : �ű� ��Ŷ ��ȣȭ
	// new Version serialization 060710
	// national code 
	INDEX tv_idx;
	switch (g_iCountry)
	{
	case KOREA:
		tv_idx = 0;
		break;
	case THAILAND:
		tv_idx = 4;
		break;
	}

	nmLoginNew << (UBYTE)tv_idx;

#ifndef CRYPT_NET_MSG_MANUAL
	ULONG ulSeed = (ULONG)CNM_MakeSeedForClient(_strUserID, _strUserPW, GetTickCount());
	nmLoginNew << ulSeed;
#endif // #ifndef CRYPT_NET_MSG_MANUAL
#endif // #ifdef CRYPT_NET_MSG

	_pNetwork->SendToServerNew(nmLoginNew, TRUE);
	_cmiComm.Server_Update();

	// EDIT : BS : 070413 : �ű� ��Ŷ ��ȣȭ
#ifdef CRYPT_NET_MSG
#ifndef CRYPT_NET_MSG_MANUAL
	CNM_MakeKeyFromSeed(&_pNetwork->cnmKey, (unsigned int)ulSeed);
#endif // #ifndef CRYPT_NET_MSG_MANUAL
#endif // #ifdef CRYPT_NET_MSG

	unsigned int StartTime = (unsigned int(_pTimer->GetLerpedCurrentTick() * 1000)); //timeGetTime(); 
	//	StartTime = (unsigned int(_pTimer->GetLerpedCurrentTick()*1000)); //timeGetTime(); 

	CUIManager* pUIManager = CUIManager::getSingleton();

	for (;;)
	{
		_cmiComm.Server_Update();
		CNetworkMessage nmMessage;
		if (_pNetwork->ReceiveFromServerNew(nmMessage))
		{
			if (nmMessage.GetType() == MSG_DB)
			{
				unsigned char dbtype;
				nmMessage >> dbtype;

				if (dbtype == MSG_DB_CHAR_END)
				{
#ifdef CRYPT_NET_MSG
					// EDIT : BS : 070413 : �ű� ��Ŷ ��ȣȭ
					//wooss 050820
					ULONG slotTime;
					nmMessage >> slotTime;
					nmMessage >> slotTime;

#ifndef CRYPT_NET_MSG_MANUAL
					ULONG ulSeed;
					nmMessage >> ulSeed;
					CNM_MakeKeyFromSeed(&_pNetwork->cnmKeyServer, (unsigned int)ulSeed);
#endif // #ifndef CRYPT_NET_MSG_MANUAL
#endif // #ifdef CRYPT_NET_MSG
					break;
				}
			}
		}

		// FIXME : GO_ZONE�� ��� ��Ʈ��ũ ���õ� �κ��� ���� �Լ����� ó���ϱ� ������,
		// FIXME : ���� ���� ó���� �� �ȿ��� �ϴµ�...
		// FIXME : �����ؾ� ��.
		if ((unsigned int(_pTimer->GetLerpedCurrentTick() * 1000)) - StartTime > 10000)
		{
			// FIXME : �ߺ��Ǵ� �ڵ尡 ����.
			pUIManager->CloseMessageBox(MSGCMD_DISCONNECT);
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_OK, UI_NONE, MSGCMD_DISCONNECT);
			MsgBoxInfo.AddString(_S(300, "�������� ������ ���������ϴ�."));
			pUIManager->CreateMessageBox(MsgBoxInfo);
			//cci_bInitUpdateMasterBuffer = FALSE;
			_pNetwork->m_bSendMessage = FALSE;
			_cmiComm.Disconnect();
			break;
		}
	}

	CNetworkMessage nmChaStart((UBYTE)MSG_MENU);
	nmChaStart << (unsigned char)MSG_MENU_START;
	nmChaStart << _pNetwork->MyCharacterInfo.index;
	_pNetwork->SendToServerNew(nmChaStart, TRUE);

	StartTime = (unsigned int(_pTimer->GetLerpedCurrentTick() * 1000)); //timeGetTime(); 

	for (;;)
	{
		_cmiComm.Server_Update();
		CNetworkMessage nmMessage;
		if (_pNetwork->ReceiveFromServerNew(nmMessage))
		{
			if (nmMessage.GetType() == MSG_DB)
			{
				unsigned char dbtype;
				nmMessage >> dbtype;

				if (dbtype == MSG_DB_OK)
				{
					ULONG zone;
					nmMessage >> zone;
					g_slZone = zone;
				}

				_bLoginProcess = FALSE;
				_SetPlayStartTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();

				CEntity* penPlEntity;
				CPlayerEntity* penPlayerEntity;
				penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
				penPlayerEntity = static_cast<CPlayerEntity*>(penPlEntity);

				g_slZone = zone;//0921

				if (CZoneInfo::getSingleton()->GetZoneType(zone) == ZONE_SDUNGEON)
				{
					CPrintF("===Start Single Mode===\n");
					_pNetwork->m_bSingleMode = TRUE;
					_pNetwork->wo_dwEnemyCount = 0;
					_pNetwork->wo_dwKilledEnemyCount = 0;
					penPlayerEntity->SingleModeOn();
				}
				else
				{
					CPrintF("===End Single Mode===\n");
					_pNetwork->m_bSingleMode = FALSE;
					penPlayerEntity->FieldModeOn();
					pUIManager->GetSingleBattle()->closeUI();
				}
				///////////
				_pNetwork->m_ubGMLevel = 0;

				_pNetwork->TogglePause();
				_pNetwork->ChangeLevel(CZoneInfo::getSingleton()->GetZoneWldFile(zone), FALSE, 0);

				_pNetwork->DeleteAllMob();
				_pNetwork->MyCharacterInfo.EntranceType = CURRENT_ENTER_NORMAL; // �ʱ�ȭ

				EPreLevelChange ePreChange;
				ePreChange.iUserData = _pNetwork->ga_iNextLevelUserData;
				SendLevelChangeNotification(ePreChange);
				CEntity::HandleSentEvents();
				_pNetwork->ChangeLevel_internal();
				EPostLevelChange ePostChange;
				ePostChange.iUserData = _pNetwork->ga_iNextLevelUserData;
				SendLevelChangeNotification(ePostChange);
				CEntity::HandleSentEvents();
				_lphCurrent = LCP_NOCHANGE;
				CNetworkMessage nmStartGame((UBYTE)MSG_START_GAME);
				_pNetwork->SendToServerNew(nmStartGame, TRUE);
				_cmiComm.Server_Update();

				//_bUseSocket = FALSE;
				//////////
				break;
			}
			// FIXME : GO_ZONE�� ��� ��Ʈ��ũ ���õ� �κ��� ���� �Լ����� ó���ϱ� ������,
			// FIXME : ���� ���� ó���� �� �ȿ��� �ϴµ�...
			// FIXME : �����ؾ� ��.
			else if (nmMessage.GetType() == MSG_FAIL)
			{
				// FIXME : �ߺ��Ǵ� �ڵ尡 ����.
				pUIManager->CloseMessageBox(MSGCMD_DISCONNECT);
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_OK, UI_NONE, MSGCMD_DISCONNECT);
				MsgBoxInfo.AddString(_S(300, "�������� ������ ���������ϴ�."));
				pUIManager->CreateMessageBox(MsgBoxInfo);
				//cci_bInitUpdateMasterBuffer = FALSE;
				_pNetwork->m_bSendMessage = FALSE;
				_cmiComm.Disconnect();
				break;
			}
		}

		// FIXME : GO_ZONE�� ��� ��Ʈ��ũ ���õ� �κ��� ���� �Լ����� ó���ϱ� ������,
		// FIXME : ���� ���� ó���� �� �ȿ��� �ϴµ�...
		// FIXME : �����ؾ� ��.
		if ((unsigned int(_pTimer->GetLerpedCurrentTick() * 1000)) - StartTime > 10000)
		{
			// FIXME : �ߺ��Ǵ� �ڵ尡 ����.
			pUIManager->CloseMessageBox(MSGCMD_DISCONNECT);
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_OK, UI_NONE, MSGCMD_DISCONNECT);
			MsgBoxInfo.AddString(_S(300, "�������� ������ ���������ϴ�."));
			pUIManager->CreateMessageBox(MsgBoxInfo);
			//cci_bInitUpdateMasterBuffer = FALSE;
			_pNetwork->m_bSendMessage = FALSE;
			_cmiComm.Disconnect();
			break;
		}
	}
}
// --- EDIT : BS

// ----------------------------------------------------------------------------
// Name : ReceiveExHairChange()
// Desc : ��Ÿ ���� ����( ��� ���� �޼��� ó�� )
// ----------------------------------------------------------------------------
void CSessionState::ReceiveExHairChange(CNetworkMessage* istr)
{
	ULONG ulCharIndex;
	UBYTE ubHairStyle;

	(*istr) >> ulCharIndex >> ubHairStyle;

	CEntity* penEntity = NULL;
	CEntity* penPlEntity = NULL;
	CModelInstance* pMI = NULL;
	CPlayerEntity* penPlayerEntity = NULL;
	penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
	penPlayerEntity = (CPlayerEntity*)penPlEntity; // SetCharacterHairChange() ȣ���� ���� ���

	if (ulCharIndex == _pNetwork->MyCharacterInfo.index) // �ڱ� ĳ����
	{
		_pNetwork->MyCharacterInfo.hairStyle = ubHairStyle;
		penPlayerEntity->SetCharacterHairChange(ulCharIndex, ubHairStyle, TRUE);
	}
	else // Ÿ ĳ����
	{
		penPlayerEntity->SetCharacterHairChange(ulCharIndex, ubHairStyle, FALSE);
	}
}
// ----------------------------------------------------------------------------
// Name : ReceiveExPlayerStateChange()
// Desc : ���� ������ ����( Ư�� ������ ����� ����Ʈ ���� )
// ----------------------------------------------------------------------------
void CSessionState::ReceiveExPlayerStateChange(CNetworkMessage* istr)
{
	ULONG ulCharIndex;
	ULONG ulPlayerState;

	(*istr) >> ulCharIndex >> ulPlayerState;

	CEntity* penEntity = NULL;
	CEntity* penPlEntity = NULL;
	CModelInstance* pMI = NULL;
	BOOL bAdd = FALSE;
	CPlayerEntity* penPlayerEntity = NULL;
	penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
	penPlayerEntity = (CPlayerEntity*)penPlEntity; // PlAddAccessoryEffect() ȣ���� ���� ���

	if (ulPlayerState & PLAYER_STATE_SUPPORTER) bAdd = TRUE;

	if (ulCharIndex == _pNetwork->MyCharacterInfo.index)
	{
		// �ڱ� ĳ����
		_pNetwork->MyCharacterInfo.ulPlayerState = ulPlayerState;

		if (bAdd)
		{ // ����
			penPlayerEntity->PlAddAccessoryEffect(penPlEntity, NULL);
		}
		else
		{ // ����
			_pNetwork->MyCharacterInfo.itemEffect.DelAccessoryEffect();
		}
	}
	else
	{
		// Ÿ ĳ����
		ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, ulCharIndex);

		if (pObject != NULL)
		{
			CCharacterTarget* pTarget = static_cast<CCharacterTarget*>(pObject);

			penEntity = pTarget->GetEntity();

			if (penEntity == NULL)
				return;

			penPlayerEntity->SetCharacterState(penEntity, ulPlayerState);

			if (bAdd)
			{ // ����
				pTarget->cha_state = ulPlayerState;
				penPlayerEntity->PlAddAccessoryEffect(penEntity, pTarget);
			}
			else
			{ // ����
				pTarget->cha_state = ulPlayerState;
				pTarget->cha_itemEffect.DelAccessoryEffect();
			}
		}
	}
}

// WSS_NPROTECT 070402 ------------------------------->>
#ifndef NO_GAMEGUARD
void CSessionState::ReceiveExnProtect(CNetworkMessage* istr)
{
	//	extern ENGINE_API CNPGameLib npgl;
	GG_AUTH_DATA m_AuthData;
	(*istr) >> m_AuthData.dwIndex
		>> m_AuthData.dwValue1
		>> m_AuthData.dwValue2
		>> m_AuthData.dwValue3;

	// Debug...
//	CPrintF("Recv Index : %x\n", m_AuthData.dwIndex);
//	CPrintF("Recv Value1 : %x\n", m_AuthData.dwValue1);
//	CPrintF("Recv Value2 : %x\n", m_AuthData.dwValue2);
//	CPrintF("Recv Value3 : %x\n", m_AuthData.dwValue3);

//	CPrintF("[ ---->> GameGuard Auth2...Start <<---- ] - %lu\n",timeGetTime());
	//npgl.Auth2(&m_AuthData);
//	CPrintF("[ ---->> GameGuard Auth2...End   <<---- ] - %lu\n",timeGetTime());
	if (g_pGameGuardRecvAuth)
	{
		g_pGameGuardRecvAuth(m_AuthData);
	}
}
#endif
// ---------------------------------------------------<<
// [KH_070413] �����ǳ� �̺�Ʈ ���� �߰�
void CSessionState::ReceiveEventMaster(CNetworkMessage* istr)
{
	INDEX iValue;
	(*istr) >> iValue;

	CUIMsgBox_Info MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo(_S(3344, "������ ���� �̺�Ʈ"), UMBS_OK, UI_NONE, MSGCMD_NULL);

	if (iValue < 10)
		MsgBoxInfo.AddString(_S(3348, "����� ���迡 ���� ���� �ǵ��� 25���� �Ϲ����ü� 10���� �帮�ڽ��ϴ�."));
	else
	{
		CTString strMsg;
		strMsg.PrintF(_S(3349, "�߽����� �� �缺�Ͽ� ����ġ�� +%d�� �Ǿ����ϴ�. �����ε� ���� �߽��� �缺�� �����ֽñ� �ٶ��ϴ�."), iValue);
		MsgBoxInfo.AddString(strMsg);
	}

	CUIManager::getSingleton()->CreateMessageBox(MsgBoxInfo);
}

// [070613: Su-won] �� ���� ������ ��� ��� �޽��� ó��
void CSessionState::ReceiveExPetNameChange(CNetworkMessage* istr)
{
	UBYTE lResult;
	(*istr) >> lResult;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (lResult)
	{
	case MSG_EX_PET_CHANGE_NAME_ERROR_OK:	// �̸� ���� ����:
	{
		ULONG lPetIndex;
		CTString strPetName;
		ULONG lOwnerIndex = 0;

		(*istr) >> lPetIndex;
		(*istr) >> strPetName;

		//�� ���� ������Ʈ
		CNetworkLibrary::sPetInfo	TempPet;
		TempPet.lIndex = lPetIndex;
		std::vector<CNetworkLibrary::sPetInfo>::iterator iter =
			std::find_if(_pNetwork->m_vectorPetList.begin(), _pNetwork->m_vectorPetList.end(), CNetworkLibrary::FindPet(TempPet));

		if (iter != _pNetwork->m_vectorPetList.end())
		{
			(*iter).strNameCard = strPetName;
		}

		ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_PET, lPetIndex);

		if (pObject != NULL)
		{
			CPetTarget* pTarget = static_cast<CPetTarget*>(pObject);

			pTarget->pet_strNameCard = strPetName;
			lOwnerIndex = pTarget->pet_OwnerIndex;
		}

		_pNetwork->UpdatePetTargetInfo(lPetIndex);

		if (lOwnerIndex == _pNetwork->MyCharacterInfo.index)
		{
			CUIMsgBox_Info	MsgBoxInfo;
			pUIManager->CloseMessageBox(MSGCMD_NULL);
			MsgBoxInfo.SetMsgBoxInfo(CTString(_pNetwork->GetItemName(PET_NAMECARD_ITEM)), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(_S(3531, "���� ������ ����Ǿ����ϴ�."));
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
	}
	break;
	case MSG_EX_PET_CHANGE_NAME_ERROR_FAIL:	// Pet �̸� ���� ����
		break;
	case MSG_EX_PET_CHANGE_NAME_ERROR_ITEM:	// �������� ����
		break;
	case MSG_EX_PET_CHANGE_NAME_ERROR_NOPET: // Pet ���� ����
		break;
	case MSG_EX_PET_CHANGE_NAME_ERROR_DUPLICATE:	// Pet �̸� �ߺ�
	{
		CUIMsgBox_Info	MsgBoxInfo;
		pUIManager->CloseMessageBox(MSGCMD_NULL);
		MsgBoxInfo.SetMsgBoxInfo(CTString(_pNetwork->GetItemName(PET_NAMECARD_ITEM)), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(_S(3532, "�Է��� �̸��� �����ϴ� �̸��Դϴ�. �ٽ� �Է��� �ּ���."));
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	break;
	}
}

// [070820: Su-won] PET_TEX_CHANGE
void CSessionState::ReceiveExPetColorChange(CNetworkMessage* istr)
{
	ULONG lPetIndex;			// �� �ε���
	SBYTE sbPetColor;			// �� ����
	ULONG lOwnerIndex;			// �� ���� �ε���
	UBYTE sbTypeGrade;			// �� Ÿ��

	(*istr) >> lPetIndex;
	(*istr) >> sbPetColor;
	(*istr) >> lOwnerIndex;
	(*istr) >> sbTypeGrade;

	// [090827: selo] ���� �����ϰ� ���� �ʴٸ� �����Ѵ�.
	//if( INFO()->_PetTargetInfo.iAge < 0 )
	//	return;

	INDEX iPetType = -1;
	INDEX iPetAge = -1;
	_pNetwork->CheckPetType(sbTypeGrade, iPetType, iPetAge);
	const BOOL bPetRide = PetInfo().IsRide(iPetType, iPetAge);

	// ������ �ؽ��� ����
	CTString strTexFile = PetInfo().GetColoredTexFileName(iPetType, iPetAge, sbPetColor);

	CEntity* penEntity = NULL;

	//����Ʈ �����̸�...
	if (bPetRide)
	{
		//�� ���̸�...
		if (lOwnerIndex == _pNetwork->MyCharacterInfo.index)
		{
			penEntity = CEntity::GetPlayerEntity(0);
		}
		// �� ���� �ƴϸ�...
		else
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, lOwnerIndex);

			if (pObject != NULL)
			{
				penEntity = pObject->GetEntity();
			}
		}
	}
	//����Ʈ ���°� �ƴϸ�...
	else
	{
		ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_PET, lPetIndex);

		if (pObject != NULL)
		{
			penEntity = pObject->GetEntity();
		}
	}

	if (penEntity == NULL)
		return;

	// �� ���� �ؽ��ĸ� �ٲ���...
	penEntity->GetModelInstance()->mi_aMeshInst[0].mi_tiTextures[0].ti_toTexture.SetData_t(strTexFile);


	// ����Ʈ �ѷ���...
	{
		CTString strEffect;
		//���̸�...
		if (iPetType % 6 < 3)
			strEffect = CTString("pet_dye");
		//���̸�...
		else
			strEffect = CTString("pet_dye_1");

		if (bPetRide)
			PCStartEffectGroup(strEffect, lOwnerIndex);
		else
			PetStartEffectGroup(strEffect, lPetIndex);
	}


	// �� ���� ������ ����Ǿ��� ���� �޽���â �����...
	if (lOwnerIndex == _pNetwork->MyCharacterInfo.index)
	{
		CUIManager* pUIManager = CUIManager::getSingleton();

		CUIMsgBox_Info	MsgBoxInfo;
		pUIManager->CloseMessageBox(MSGCMD_NULL);
		//		MsgBoxInfo.SetMsgBoxInfo( CTString(_pNetwork->GetItemName(PET_NAMECARD_ITEM)), UMBS_OK, UI_NONE, MSGCMD_NULL );
		MsgBoxInfo.SetMsgBoxInfo(_S(1970, "����"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(_S(3665, "�� ���󺯰��� ���������� �̷�������ϴ�."));
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
}

//////////////////////////////////////////////////////////////////////////
// [sora]  ������ ����
//////////////////////////////////////////////////////////////////////////
void CSessionState::ReceiveExpeditionMessage(CNetworkMessage* istr)
{
	// �Ұ� : �޽��� ó��
	SLONG	slType;
	(*istr) >> slType;

	CUIManager* pUIManager = CUIManager::getSingleton();
	Party* pParty = GAMEDATAMGR()->GetPartyInfo();

	if (pParty == NULL)
		return;

	switch (slType)
	{
	case MSG_CREATE_REP: // ������ ��ȯ
	{
		pParty->RecvChangeExpedition(istr);
	}
	break;
	case MSG_INVITE_REP: // �ʴ�
	{
		pParty->RecvExpeditionInvite(istr);
	}
	break;
	case MSG_REJECT_DEST:
	{
		pParty->ExpeditionReject(FALSE);
	}
	break;
	case MSG_REJECT_SRC:
	{
		pParty->ExpeditionReject(TRUE);
	}
	break;

	case MSG_ENDEXPED_START: // ���������� ������ ��ü��û�� ����鿡�� �˸�
	{

		CUIMsgBox_Info	MsgBoxInfo;
		CTString strMessage;
		int nCommandCode = MSGCMD_EXPEDITION_ERROR;

		strMessage = _S(4664, "20���� �����밡 ��ü�˴ϴ�.");

		// [sora] �ν���Ʈ �������� ��Ȱ��ġ�� �̵��˸�
		if (pUIManager->IsPlayInZone())
		{
			strMessage += _S(4659, "�ν���Ʈ ���� ��Ȱ ��ġ�� �̵��մϴ�.(���� �ð� ���� �������� �̵��մϴ�.)");
			nCommandCode = MSGCMD_EXPEDITION_GO_STARTPLACE;
		}

		MsgBoxInfo.SetMsgBoxInfo(_S(4493, "������"), UMBS_OK | UMBS_USE_TIMER,
			UI_PARTY, nCommandCode);

		MsgBoxInfo.AddString(strMessage);
		MsgBoxInfo.SetMsgBoxTimer(20, FALSE);
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	break;

	case MSG_ENDEXPED_REP:
	{
		// ������ ��ü �˸� �޽��� �ڽ��� ������ �ݴ´�
		if (pUIManager->DoesMessageBoxExist(MSGCMD_EXPEDITION_ERROR))
			pUIManager->CloseMessageBox(MSGCMD_EXPEDITION_ERROR);

		pUIManager->GetChattingUI()->AddSysMessage(_S(4665, "�����밡 ��ü�Ǿ����ϴ�."));
		pParty->ExpeditionEnd();
	}
	break;

	case MSG_EXPED_ADD:
	{
		// ������� �߰�
		SLONG nGroupNum, nPos, slIndex, nPosition, iLevel, iHP, iMaxHP, iMP, iMaxMP, slZone;
		SBYTE sbJob, sbJob2, sbLayer;
		FLOAT fX, fZ;
		CTString strName;

		(*istr) >> slIndex;
		(*istr) >> strName;
		(*istr) >> nGroupNum;
		(*istr) >> nPosition;
		(*istr) >> nPos;
		(*istr) >> sbJob;
		(*istr) >> sbJob2;
		(*istr) >> iLevel;
#ifdef HP_PERCENTAGE //MSG_EXPED_ADD Rep  [3/29/2013 Ranma]
		FLOAT fHp_percentage;
		(*istr) >> fHp_percentage;
		iHP = fHp_percentage * 10;
		iMaxHP = 1000;
#else
		(*istr) >> iHP;
		(*istr) >> iMaxHP;
#endif
		(*istr) >> iMP;
		(*istr) >> iMaxMP;
		(*istr) >> fX;
		(*istr) >> fZ;
		(*istr) >> sbLayer;
		(*istr) >> slZone;

		pParty->AddExpeditionMember(nGroupNum, nPos, nPosition, slIndex, strName, sbJob, sbJob2,
			iLevel, iHP, iMaxHP, iMP, iMaxMP, fX, fZ, sbLayer, slZone);

		// [100216: selo] ������ ��Ƽ������ �����Ѵ�.
		pParty->SetIsPartyPlay(TRUE);

	}
	break;

	case MSG_QUIT_REP:
	{
		SLONG slIndex, nType;
		(*istr) >> slIndex;
		(*istr) >> nType;

		pParty->ExpeditionQuit(nType, slIndex);
	}
	break;
	case MSG_KICK_REP:
	{
		SLONG slIndex;
		(*istr) >> slIndex;

		pParty->ExpeditionKick(slIndex);
	}
	break;
	case MSG_CHANGEBOSS_REP:
	{
		SLONG slIndexSrc, slIndexDesc, slChangeMode;
		(*istr) >> slIndexSrc;
		(*istr) >> slIndexDesc;
		(*istr) >> slChangeMode;

		pParty->ChangeExpeditionLeader(slIndexSrc, slIndexDesc, slChangeMode);
	}
	break;
	case MSG_CHANGETYPE_REP:
	{
		SBYTE sbType, sbDivisionType;
		(*istr) >> sbType;
		(*istr) >> sbDivisionType;

		pParty->SetDivisionType(sbDivisionType, sbType);
	}
	break;
	case MSG_SETMBOSS_REP:
	{
		SLONG slIndex;
		(*istr) >> slIndex;

		pParty->SetExpeditionPosition(slIndex, MSG_EXPED_MEMBERTYPE_MBOSS);
	}
	break;
	case MSG_RESETMBOSS_REP:
	{
		SLONG slIndex;
		(*istr) >> slIndex;

		pParty->SetExpeditionPosition(slIndex, MSG_EXPED_MEMBERTYPE_NORMAL);
	}
	break;
	case MSG_MOVEGROUP_REP:
	{
		SLONG slGroupSrc, slIndex, slGroupDesc, slPos;
		(*istr) >> slGroupSrc;
		(*istr) >> slIndex;
		(*istr) >> slGroupDesc;
		(*istr) >> slPos;

		pParty->ChangeGroup(slIndex, slGroupDesc, slPos);
	}
	break;
	case MSG_SET_LABEL_REP:
	{
		// Ÿ�� ����
		SLONG slType, slMode, slLabel, slIndex;
		(*istr) >> slType;
		(*istr) >> slMode;
		(*istr) >> slLabel;
		(*istr) >> slIndex;

		pParty->SetTargetLabel(slType, slMode, slLabel, slIndex);
	}
	break;
	case MSG_VIEWDETAIL_INVEN:
	case MSG_VIEWDETAIL_PET:
	case MSG_VIEWDETAIL_APET:
	{
		// ���캸�� ���� ����
		pParty->RecvViewDetail(slType, istr);
	}
	break;
#ifdef CLOUD_EXPEDITION_REWORK
	case MSG_PARTYDUNGEON_SEND:
	{
		pParty->RecvDungeonDetail(slType, istr);
	}
	break;
#endif
	case MSG_EXPED_ERROR:
	{
		pParty->RecvExpeditionError(istr);
	}
	break;

	case MSG_EXPED_TYPEINFO:
	{
		// Ÿ�� ����
		SBYTE sbDivisionTypeEXP, sbDivisionTypeITEM, sbDivisionTypeSPITEM;

		(*istr) >> sbDivisionTypeEXP;
		(*istr) >> sbDivisionTypeITEM;
		(*istr) >> sbDivisionTypeSPITEM;

		pParty->SetDivisionType(sbDivisionTypeEXP, sbDivisionTypeITEM, sbDivisionTypeSPITEM);

		// [091119: selo] ������ ��Ƽ������ �����Ѵ�.
		pParty->SetIsPartyPlay(TRUE);
	}
	break;

	case MSG_GET_QUESTITEM_SUCCESS_REP:	// ������ ����Ʈ ������ �˻� ����
	{
		CUIMsgBox_Info	MsgBoxInfo;

		MsgBoxInfo.SetMsgBoxInfo(_S(4493, "������"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(_S(4778, "������ ������ ���������� �̷�������ϴ�."));
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	break;

	case MSG_GET_QUESTITEM_FAILED_REP: // ������ ����Ʈ ������ �˻� ����
	{
		CUIMsgBox_Info	MsgBoxInfo;

		MsgBoxInfo.SetMsgBoxInfo(_S(4493, "������"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(_S(4777, "������ ������ �����Ͽ����ϴ�."));
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	break;
	case MSG_EXPED_ADD_SYSMSG:
	{
		CTString strMessage;
		CTString strName;
		(*istr) >> strName;

		strMessage.PrintF(_S(5498, "%s�� �����뿡 �շ��Ͽ����ϴ�."), strName);
		pUIManager->GetChattingUI()->AddSysMessage(strMessage);
	}
	break;
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
	case MSG_PARTYDUNGEON_RECALL_RECV://Cloud Expedition_Party_Dungeon
	{

		pParty->RecvPartyDungeonRecall(slType, istr);
	}
	break;
#endif
	}
}
//////////////////////////////////////////////////////////////////////////



 //Craft system
void CSessionState::ReceiveCraftMessage(CNetworkMessage* istr)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(istr->GetBuffer());

	SLONG	slType;
	if (pBase->subType != 0)
	{
		slType = pBase->subType;
	}
	else
		(*istr) >> slType;

	CUIManager* pUIManager = CUIManager::getSingleton();
	CUIMsgBox_Info	MsgBoxInfo;
	pUIManager->CloseMessageBox(MSGCMD_NULL);
	switch (slType)
	{
	case MSG_CRAFT_ERROR:
		MsgBoxInfo.SetMsgBoxInfo(_S(577, "Failure"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(_S(8248, "Unknown error! Item not created."));
		break;
	case MSG_CRAFT_NOT_ITEM:
		MsgBoxInfo.SetMsgBoxInfo(_S(577, "Failure"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(_S(8249, "Item to create does not exist!"));
		break;
	case MSG_CRAFT_NOT_MONEY:
		MsgBoxInfo.SetMsgBoxInfo(_S(577, "Failure"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(_S(266, "You don't have enough gold."));
		break;
	case MSG_CRAFT_NOT_ENOUGHT_ITEM:
		MsgBoxInfo.SetMsgBoxInfo(_S(577, "Failure"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(_S(8250, "Not enough materials to craft an item!"));
		break;
	case MSG_CRAFT_ITEM:
		MsgBoxInfo.SetMsgBoxInfo(_S(1970, "Success"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(_S(8247, "You have successfully created an item!"));
		pUIManager->GetCraft()->ReSelectList();
		break;
	}
	pUIManager->CreateMessageBox(MsgBoxInfo);
}

void CSessionState::ReceiveFactoryMessage(CNetworkMessage* istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (ubType)
	{
	case MSG_FACTORY_ITEM_MAKE_REP:
	case MSG_FACTORY_ERROR:
	{
		pUIManager->CloseMessageBox(MSGCMD_NULL);

		UBYTE	ubErrorType;
		CTString strMessage;
		CUIMsgBox_Info	MsgBoxInfo;

		(*istr) >> ubErrorType;

		switch (ubErrorType)
		{
		case MSG_FACTORY_ERROR_MAKE_OK:
		{
			pUIManager->GetProduct2()->SetItemMaking(TRUE);
			return;
		}break;
		case MSG_FACTORY_ERROR_SYSTEM:
		{
			strMessage.PrintF(_S(1688, "������ ���� �ʽ��ϴ�."));
		}break;
		case MSG_FACTORY_ERROR_ALREADY_REG:
		{
			strMessage.PrintF(_S(2701, "�̹� ����Ʈ�� ��ϵ� �����Դϴ�"));
		}break;
		case MSG_FACTORY_ERROR_SKILL:
		{
			strMessage.PrintF(_S(578, "���ۿ� �ʿ��� ���� ��ų�� �����ϴ�."));
		}break;
		case MSG_FACTORY_ERROR_NAS:
		{
			strMessage.PrintF(_S(306, "������ �����մϴ�."));
		}break;
		case MSG_FACTORY_ERROR_EXP:
		{
			strMessage.PrintF(_S(4667, "���õ��� �����մϴ�."));
		}break;
		case MSG_FACTORY_ERROR_ITEM:
		{
			strMessage.PrintF(_S(1799, "��ᰡ �����մϴ�. Ȯ���ϰ� �ٽ� �õ��Ͽ� �ֽʽÿ�."));
		}break;
		case MSG_FACTORY_ERROR_INVEN:
		{
			strMessage.PrintF(_S(265, "�κ��丮 ������ �����մϴ�."));
		}break;
		}

		MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);

	}break;
	case MSG_FACTORY_LEARN:
	{
		SLONG nfactoryIndex;
		CTString strTem;

		(*istr) >> nfactoryIndex;

		CMakeItemData temMakeItem = _pNetwork->GetMakeItemData(nfactoryIndex);
		strTem.PrintF(_S(4668, "%s ���� ����� �����Ͽ����ϴ�."), temMakeItem.GetName());
		_pNetwork->ClientSystemMessage(strTem, SYSMSG_NOTIFY);
		pUIManager->GetProductNPC()->CloseProductNPC();

	}break;
	case MSG_FACTORY_ITEM_LIST:
	{
		UBYTE UItype;
		SLONG nfactoryIndex, temSealtype, ncount;

		(*istr) >> (UBYTE)UItype;		// 0: NPC���� ��û 1: ����⿡�� ��û
		(*istr) >> temSealtype;
		(*istr) >> ncount;

		pUIManager->GetProduct2()->SetSealType(temSealtype);

		pUIManager->GetProduct2()->ListReset();

		for (int i = 0; i < ncount; i++)
		{
			(*istr) >> nfactoryIndex;

			MY_INFO()->add_makeitem(nfactoryIndex);
		}

		// 0: NPC���� ��û 1: ����⿡�� ��û
		if (UItype)
		{
			pUIManager->GetProduct2()->OpenProduct2(temSealtype);
		}
		else
		{
			pUIManager->GetProductNPC()->OpenProductList(temSealtype);
		}


	}break;
	// 	case MSG_FACTORY_ITEM_MAKE_REP:
	// 		{
	// 			ULONG lindex;
	// 			UBYTE ubResult;
	// 
	// 			(*istr) >> lindex;
	// 			(*istr) >> ubResult;
	// 
	// 			if (ubResult)
	// 			{
	// 				pUIManager->GetProduct2()->CloseProduct2();
	// 				pUIManager->GetProduct2()->SendMakeItem(MSG_FACTORY_ITEM_MAKE,lindex);
	// 			}
	// 			
	// 
	//		}break;
	case MSG_FACTORY_ITEM_MAKE:
	{
		SLONG nItemIndex, nSealIndex;
		SQUAD lSealExp;

		CTString strMessage;
		CUIMsgBox_Info	MsgBoxInfo;

		(*istr) >> nItemIndex;
		(*istr) >> nSealIndex;
		(*istr) >> lSealExp;

		pUIManager->CloseMessageBox(MSGCMD_NULL);	// �̹� ���� �ִٸ� �ݴ´�.

		CMakeItemData& Itemdata = _pNetwork->GetMakeItemData(nItemIndex);
		strMessage.PrintF("%s ", Itemdata.GetName());
		strMessage += _S(580, "���ۿ� ���� �Ͽ����ϴ�.");

		MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);

		pUIManager->GetCharacterInfo()->UpdateSealExp(nSealIndex, lSealExp);

	}break;

	}

}

// connie [2009/9/8] - NPC ã��
void CSessionState::ReceiveNPCPortalMessage(CNetworkMessage* istr)
{
	SLONG	slType;

	(*istr) >> slType;
	// [eons]
	// �޼��� Ÿ���� �Һи� �ϴ�.
	// ��ɻ� ����Ʈ�� ��û�ϰ�, ������ ����ϰ� �Ǿ� �����Ƿ�, ��û�� ������ �Ϸ� ���� ���������� �޼����� �޴� ������ �δ� ���� ����.
	// ���� Ŭ���̾�Ʈ�� MSG_NPC_PORTAL_LIST�� ���������� ������� �ʴ´�. ��û�� ������ ����� �ٷ� �� �� ����.
	// ���� ReceiveNPCData() ���ο��� ���� �Լ��� �۵��ϰ� �Ͽ���.
	// Error�ÿ��� â�� ����� �ʴ´�.

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (slType)
	{
	case MSG_NPC_PORTAL_LIST:
	{
		pUIManager->GetNpcScroll()->ReceiveNPCData(istr);
	}
	break;
	case MSG_NPC_PORTAL_LOCATION:
	{
		pUIManager->GetNpcScroll()->ReceiveMobLocation(istr);
	}
	break;
	case MSG_NPC_PORTAL_ERROR:
	{
		SLONG slErrorType;

		(*istr) >> slErrorType;
		// OpenNPCScrollInfo���� ErrorType�״�� ����Ѵ�. [eons]
		pUIManager->GetNpcScroll()->OpenNPCScrollInfo(slErrorType);
	}
	break;
	}

}

void CSessionState::RecievePromotionEventMessage(CNetworkMessage* istr)
{
	UBYTE ubType;
	(*istr) >> ubType;

	CUIMsgBox_Info	MsgBoxInfo;
	CTString strMessage;
	MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

	switch (ubType)
	{
	case MSG_EVENT_PROMOTION2_REP_ERROR_FAIL:
	{	// ���� ( ������ ���� �߱� �ý����� ����� �� �����ϴ�. )
		strMessage = _S(5106, "������ ���� �߱� �ý����� ����� �� �����ϴ�.");
	}
	break;
	case MSG_EVENT_PROMOTION2_REP_ERROR_SUC:
	{	// ���� ��� ���� (�ٷ� ��ǰ ���� )
		strMessage = _S(2224, "�̺�Ʈ ��ǰ�� ���޵Ǿ����ϴ�.");
	}
	break;
	case MSG_EVENT_PROMOTION2_REP_ERROR_KEY:
	{	// ����� �� ���� ���� (�̹� ����� ����, 
		strMessage = _S(2405, "��û�� ���� ��ȣ�� �������� �ʽ��ϴ�.");
	}
	break;
	case MSG_EVENT_PROMOTION2_REP_ERROR_USED:
	{	// �̹� ����� ����
		strMessage = _S(2406, "�̹� ���޹��� ���� ��ȣ �Դϴ�.");
	}
	break;
	case MSG_EVENT_PROMOTION2_REP_ERROR_USER:
	{	// ������ ����� �� ���� ������ ���
		strMessage = _S(1722, "������ ������ �� �ִ� ������ �ƴմϴ�");
	}
	break;
	case MSG_EVENT_PROMOTION2_REP_ERROR_DATE:
	{	// ��� �Ⱓ�� ������
		strMessage = _S(5107, "��� �Ⱓ�� ����� �����Դϴ�.");
	}
	break;
	}

	if (strMessage.Length() > 0)
	{
		MsgBoxInfo.AddString(strMessage);
		CUIManager::getSingleton()->CreateMessageBox(MsgBoxInfo);
	}
}

#ifdef KALYDO
void CSessionState::DelayLoadingFromKalydo()
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CEntity* penPlEntity;
	CPlayerEntity* penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity(0); //ĳ���� �ڱ� �ڽ�
	penPlayerEntity = static_cast<CPlayerEntity*>(penPlEntity);

	_pNetwork->m_ubGMLevel = 0;
	_pNetwork->TogglePause();
	_pNetwork->ChangeLevel(CZoneInfo::getSingleton()->GetZoneWldFile(g_slZone), FALSE, 0);

	// [090826: selo] �ý��� �޽��� ���� ������
	pUIManager->GetChattingUI()->End_SaveSysMessage(1);

	// Date : 2006-04-26(���� 11:48:00), By eons
	if (penPlayerEntity->IsPolymophing())	// ���� ���̶��
	{
		penPlayerEntity->ReturnChange(TRUE);
		const int iStopChangeItem = 521;
	}

	pUIManager->GetSummonFirst()->ResetSummon();
	pUIManager->GetSummonSecond()->ResetSummon();

	pUIManager->GetPersonalShop()->ResetShop();
	pUIManager->SetCSFlagOff(CSF_PERSONALSHOP);
	pUIManager->SetCSFlagOff(CSF_MOONSTONE);
	pUIManager->SetCSFlagOff(CSF_MOUNT_HUNGRY);
	pUIManager->GetGuild()->ResetGuild();
	pUIManager->GetGuild()->ClearMemberList();
	_pNetwork->LeavePet(static_cast<CPlayerEntity*>(CEntity::GetPlayerEntity(0)));
	INFO()->GetMyPetInfo()->Init();	// [091119: selo] �� ���� �ʱ�ȭ
	// FIXED : wild pet mount bug [12/12/2010 rumist]
	// �ʱ�ȭ ���з� �Žð� ������ �� ����.
	static_cast<CPlayerEntity*>(CEntity::GetPlayerEntity(0))->LeavingWildPet(static_cast<CPlayerEntity*>(CEntity::GetPlayerEntity(0)));
	MY_APET_INFO()->Init();
	// royal rumble init [5/11/2011 rumist]
	pUIManager->GetRadar()->ResetRoyalRumbleStat();
	pUIManager->GetRoyalRumbleIcon()->ShowRoyalRumbleIcon(FALSE);
	// ITS#3867 : ä�� �� �̵��� �ִϸ��̼� ����. [2/13/2012 rumist]
	static_cast<CPlayerEntity*>(CEntity::GetPlayerEntity(0))->CancelProduct();

	// [091119: selo] ��Ƽ���� �ʱ�ȭ
	pParty->Init();
	pParty->InitExpedition();

	//		Bug Fix 060530 wooss
	//		_pNetwork->ClearPetList();
	//		INFO()->_PetTargetInfo.Init();
	INFO()->m_MySlaveInfo[0].Init();
	INFO()->m_MySlaveInfo[1].Init();

	pUIManager->GetHelper()->CloseUI();
	pUIManager->GetHelper()->ClearHelperList();

	penPlayerEntity->ClearMultiTargets();

	_pNetwork->DeleteAllMob();
	_pNetwork->MyCharacterInfo.EntranceType = CURRENT_ENTER_NORMAL; // �ʱ�ȭ

	EPreLevelChange ePreChange;
	ePreChange.iUserData = _pNetwork->ga_iNextLevelUserData;
	SendLevelChangeNotification(ePreChange);
	CEntity::HandleSentEvents();
	_pNetwork->ChangeLevel_internal();
	EPostLevelChange ePostChange;
	ePostChange.iUserData = _pNetwork->ga_iNextLevelUserData;
	SendLevelChangeNotification(ePostChange);
	CEntity::HandleSentEvents();
	_lphCurrent = LCP_NOCHANGE;
	CNetworkMessage nmStartGame(MSG_START_GAME);
	_pNetwork->SendToServerNew(nmStartGame, TRUE);
	_cmiComm.Server_Update();
	//������ ���� ���� �̱۴��� ���丮	10.07
		// TargetNPC�� ��κ� �̸� �����Ǿ��� ��ƼƼ����.
	for (std::vector<CEntity*>::iterator iter = _pNetwork->ga_World.m_vectorPreCreateNPC.begin(); iter != _pNetwork->ga_World.m_vectorPreCreateNPC.end(); ++iter)
	{
		(*iter)->Reinitialize();
	}
	_pNetwork->ga_World.m_vectorPreCreateNPC.clear();
	_cmiComm.Server_Update();

	/*
	if(_pNetwork && _pNetwork->m_bSingleMode && _pNetwork->ga_World.wo_iNumOfNPC)
	{
		CEntity* penPlayer = CEntity::GetPlayerEntity(0);
		_pNetwork->ga_World.m_vectorTargetNPC.push_back(penPlayer);
	}
	*/
}


#endif
void CSessionState::ReceiveMoneyMessage(CNetworkMessage* istr)
{
	OBFUSCATE();

	SBYTE	type;	//���� Ÿ��
	SQUAD	count;	//�ѷ�
	SQUAD	delta;	//��ȭ��

	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString	strSysMessage;

	(*istr) >> type;
	switch (type)
	{
	case MSG_MONEY_COUNT:
	{
		(*istr) >> count;
		(*istr) >> delta;

		if (count < 0)	//������ ���� ���� ������ 
		{
			ASSERT(FALSE);
			break;
		}

		bool bChange = false;
		if (_pNetwork->MyCharacterInfo.money != count)
		{
			// ������ ��ȭ �Ǿ��ٸ�
			bChange = true;
		}

		_pNetwork->MyCharacterInfo.money = count;

		if (delta > 0)	//���� ����
		{
			CTString strCount;
			strCount.PrintF("%I64d", delta);
			pUIManager->InsertCommaToString(strCount);

			strSysMessage.PrintF(_S(416, "%s ������ ������ϴ�."), strCount); // ���� ����
			_pNetwork->ClientSystemMessage(strSysMessage);
		}
		else if (delta == 0)	//���� ��ȭ ����
		{

		}
		else	//���� ���� 
		{

		}

		if (bChange == true)
			GameDataManager::getSingleton()->GetAuction()->updateNas();
	}
	break;
	default:
		ASSERT(FALSE);
		break;

	}
}

void CSessionState::ReceiveExpressMessage(CNetworkMessage* istr)
{
	GameDataManager* pGameDataManager = GameDataManager::getSingleton();

	pGameDataManager->GetExpressData()->RecvExpressMessage(&(*istr));
}
void CSessionState::ReceiveMailBoxMessage(CNetworkMessage* istr)
{
	GameDataManager* pGameDataManager = GameDataManager::getSingleton();
	pGameDataManager->GetMailBoxManager()->ReceiveMessage(istr);
}

void CSessionState::ReceiveCalendarMessage(CNetworkMessage* istr)
{
	GameDataManager* pGameDataManager = GameDataManager::getSingleton();

	pGameDataManager->GetCalendarData()->RecvCalendarMessage(&(*istr));
}

void CSessionState::ReceiveTimerItemMessage(CNetworkMessage* istr)
{
	_pUIBuff->RecvTimerItemBuff(&(*istr));
}

#ifdef HP_PERCENTAGE
void CSessionState::ReceiveDamageRealStatMessage(CNetworkMessage* istr)
{
	SBYTE	type;	//���� Ÿ��
	LONG	index;
	LONG	curHp;
	LONG	MaxHp;
	LONG	curMp;
	LONG	MaxMp;

	CUIManager* pUIManager = CUIManager::getSingleton();

	(*istr) >> type;
	(*istr) >> index;
	(*istr) >> curHp;
	(*istr) >> MaxHp;
	(*istr) >> curMp;
	(*istr) >> MaxMp;

	switch (type)
	{
	case MSG_CHAR_PC:
	{
		_pNetwork->MyCharacterInfo.hp = curHp;
		_pNetwork->MyCharacterInfo.maxHP = MaxHp;
		_pNetwork->MyCharacterInfo.mp = curMp;
		_pNetwork->MyCharacterInfo.maxMP = MaxMp;
	}
	break;

	case MSG_CHAR_PET:
	case MSG_CHAR_WILDPET:
	{
		CNetworkLibrary::sPetInfo	TempPet;
		TempPet.lIndex = index;

		std::vector<CNetworkLibrary::sPetInfo>::iterator iter =
			std::find_if(_pNetwork->m_vectorPetList.begin(), _pNetwork->m_vectorPetList.end(), CNetworkLibrary::FindPet(TempPet));

		if (iter != _pNetwork->m_vectorPetList.end())
		{
			(*iter).lHP = curHp;
			(*iter).lMaxHP = MaxHp;

			_pNetwork->UpdatePetTargetInfo(index);
		}
	}
	break;

	case MSG_CHAR_ELEMENTAL:
	{
		ObjectBase* pObject = ACTORMGR()->GetObject(index);

		if (pObject != NULL && pObject->m_eType == eOBJ_SLAVE)
		{
			if (st.m_pEntity)
			{
				((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetElementalData(pObject->GetEntity(), curHp, MaxHp);
			}
		}
	}
	break;
	default:
		break;
	}

}

#endif // HP_PERCENTAGE

void CSessionState::DeleteObject(SBYTE type, ULONG index)
{
	ACTORMGR()->RemoveObject((eOBJ_TYPE)type, index);
}

void CSessionState::ReceivePetStashMessage(CNetworkMessage* istr)
{
	GameDataManager* pGameDataManager = GameDataManager::getSingleton();
	pGameDataManager->GetStashData()->RecvPetStashMessage(&(*istr));
}

void CSessionState::ReceiveRVRMessage(CNetworkMessage* istr)
{
	GameDataManager* pGameDataManager = GameDataManager::getSingleton();
	pGameDataManager->GetSyndicate()->RecvSyndicateMsg(&(*istr));
}

void CSessionState::ReceiveDurabilityMessage(CNetworkMessage* istr)
{
	CDurability* pData = GameDataManager::getSingleton()->GetDurability();

	if (pData != NULL)
		pData->RecvDurabilityMsg(&(*istr));
}

void CSessionState::ReceiveToggleMessage(CNetworkMessage* istr)
{
	ResponseClient::ToggleMsg* pRecv = reinterpret_cast<ResponseClient::ToggleMsg*>(istr->GetBuffer());

	// ��ų.
	if (pRecv->toggle_type == 0)
	{
		CSkill* pSkill = &_pNetwork->GetSkillData(pRecv->index);

		if (pSkill != NULL)
		{
			pSkill->SetToggle(pRecv->toggle);
			UIMGR()->GetSkillNew()->SetToggle(pRecv->index);
		}
	}
	else //if(pRecv->toggle_type == 1) ������
	{
		CUIIcon* pIcon = UIMGR()->GetInventory()->GetItemIcon(pRecv->index);
		CItems* pItems;

		if (pIcon != NULL)
		{
			pItems = pIcon->getItems();

			if (pItems != NULL)
				pItems->SetToggle(pRecv->toggle);

			pIcon->SetToggle(pRecv->toggle);
		}

		if (pRecv->toggle == true)
		{
			if (pItems != NULL)
			{
				CItemData* pItemData = pItems->ItemData;

				if (pItemData != NULL)
				{
					// ���� �������� ��쿡�� ���� ���
					if (pItemData->GetType() == CItemData::ITEM_ONCEUSE &&
						pItemData->GetSubType() == CItemData::ITEM_SUB_HOLY_WATER)
					{
						CEntity* penPlEntity;
						CPlayerEntity* penPlayerEntity;

						penPlEntity = CEntity::GetPlayerEntity(0);
						penPlayerEntity = (CPlayerEntity*)penPlEntity;

						penPlayerEntity->PlayHolyWaterSound();
					}
				}
			}
		}
	}

	UIMGR()->GetQuickSlot()->SetToggle(pRecv->toggle_type, pRecv->index, pRecv->toggle);
}

void CSessionState::ReceiveItemCollectionMessage(CNetworkMessage* istr)
{
	CItemCollection* pData = GameDataManager::getSingleton()->GetItemCollection();

	if (pData != NULL)
		pData->RecvItemCollectionMsg(&(*istr));
}

void CSessionState::ReceivePremiumCharMessage(CNetworkMessage* istr)
{
#ifdef PREMIUM_CHAR
	CPremiumChar* pData = GameDataManager::getSingleton()->GetPremiumChar();

	if (pData != NULL)
		pData->RecvPremiumCharMsg(&(*istr));
#endif	//	PREMIUM_CHAR
}

void CSessionState::ReceiveItemComposMessage(CNetworkMessage* istr)
{
	CItemCompose* pData = GAMEDATAMGR()->GetItemCompose();

	if (pData != NULL)
		pData->RecvItemComposeMsg(istr);
}

void CSessionState::ReceiveRecoverHp(CNetworkMessage* istr)
{
	ResponseClient::RecoverMsg* pRecv = reinterpret_cast<ResponseClient::RecoverMsg*>(istr->GetBuffer());

	CEntity* penTargetEntity = NULL;

	extern INDEX g_iHideRecoverHP;

	if (g_iHideRecoverHP == FALSE)
		return;

	if (_pNetwork->SearchEntityByNetworkID(pRecv->index_char, MSG_CHAR_PC, penTargetEntity))
	{
		UIMGR()->AddDamageData(pRecv->recover_hp, 0, penTargetEntity->en_ulID, FALSE, TRUE);
		UIMGR()->ShowDamage(penTargetEntity->en_ulID);
	}
}

#ifdef BATTLE_PASS_SYSTEM
void CSessionState::ReceiveBattlePassMessage(CNetworkMessage* istr)
{
	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(istr->GetBuffer());

	CUIManager* pUIManager = CUIManager::getSingleton();

	CTString strMessage;

	switch (pBase->subType)
	{
	case MSG_BATTLE_PASS_ERROR_LIMIT:
		strMessage.PrintF(_S(8514, "Sorry, you already achieved the max battle pass"));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		if (pUIManager->GetBattlePassUI()->IsVisible())
			pUIManager->GetBattlePassUI()->RefreshUI();
		break;
	case MSG_BATTLE_PASS_ERROR_EXP_NEEDED:
		strMessage.PrintF(_S(8515, "Sorry, you don't have the required exp for next battle pass"));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		if (pUIManager->GetBattlePassUI()->IsVisible())
			pUIManager->GetBattlePassUI()->RefreshUI();
		break;
	case MSG_BATTLE_PASS_ERROR_NOT_EXIST_NPC:
		strMessage.PrintF(_S(8516, "This npc doesn't exist"));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		if (pUIManager->GetBattlePassUI()->IsVisible())
			pUIManager->GetBattlePassUI()->RefreshUI();
		break;
	case MSG_BATTLE_PASS_ERROR_NOCONDITION_LEVEL:
		strMessage.PrintF(_S(8517, "You don't have the required level for next battle pass"));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		if (pUIManager->GetBattlePassUI()->IsVisible())
			pUIManager->GetBattlePassUI()->RefreshUI();
		break;
	case MSG_BATTLE_PASS_ERROR_EMPTY_SLOT:
		strMessage.PrintF(_S(8518, "You need more empty slot in your inventory"));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		if (pUIManager->GetBattlePassUI()->IsVisible())
			pUIManager->GetBattlePassUI()->RefreshUI();
		break;
	case MSG_BATTLE_PASS_INFO_REP:
	{
		ResponseClient::battlePassInfo* pPack = reinterpret_cast<ResponseClient::battlePassInfo*>(istr->GetBuffer());
		uint8_t* bytePointer = reinterpret_cast<uint8_t*>(pPack);
		bytePointer += 2;

		// Adjust pPack using bytePointer
		pPack = reinterpret_cast<ResponseClient::battlePassInfo*>(bytePointer);


		pUIManager->GetBattlePassUI()->ClearItems();
		pUIManager->GetBattlePassUI()->UpdateInfo(pPack->premium, pPack->points, pPack->progress, pPack->level, pPack->season);
		for (int i = 0; i < pPack->total; i++)
		{
			BattlePassItem bPassItem;
			//bPassItem.type = pPack->list[i].type;
			bPassItem.level = pPack->list[i].level;
			bPassItem.name = pPack->list[i].name;
			bPassItem.points = pPack->list[i].points;

			BattlePassRewardItem reward;
			reward.itemIdx = pPack->list[i].item_index;
			reward.itemCount = pPack->list[i].item_count;

			bPassItem.reward = reward;

			pUIManager->GetBattlePassUI()->AddItemFree(bPassItem);

			BattlePassRewardItem rewardPremium;
			rewardPremium.itemIdx = pPack->list[i].premium_item_index;
			rewardPremium.itemCount = pPack->list[i].premium_item_count;
			bPassItem.reward = rewardPremium;

			pUIManager->GetBattlePassUI()->AddItemPremium(bPassItem);

			/*if (bPassItem.type == 0)
				pUIManager->GetBattlePassUI()->AddItemFree(bPassItem);
			else if (bPassItem.type == 1)
				pUIManager->GetBattlePassUI()->AddItemPremium(bPassItem);*/
		}

		pUIManager->GetBattlePassUI()->SetHasNext(pPack->next);

		if (pUIManager->GetBattlePassUI()->IsVisible())
			pUIManager->GetBattlePassUI()->RefreshUI();
		else
			pUIManager->GetBattlePassUI()->OpenUI();
	}
	break;
	case MSG_BATTLE_PASS_REP:
	{
		ResponseClient::battlePassInfo* pPack = reinterpret_cast<ResponseClient::battlePassInfo*>(istr->GetBuffer());
		uint8_t* bytePointer = reinterpret_cast<uint8_t*>(pPack);
		bytePointer += 2;
		pPack = reinterpret_cast<ResponseClient::battlePassInfo*>(bytePointer);

		if (pPack->nIndex == _pNetwork->MyCharacterInfo.index)
		{
			CUIMsgBox_Info	MsgBoxInfo;
			strMessage.PrintF(_S(9389, "Battle Pass"));
			MsgBoxInfo.SetMsgBoxInfo(strMessage, UMBS_OK, UI_NONE, MSGCMD_NULL);
			strMessage.PrintF(_S(9430, "Congratulations! You achieved a new battle pass level! %d"), pPack->level);
			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);

			// Refresh battle pass UI if open
			if (pUIManager->GetBattlePassUI()->IsVisible())
			{
				_pNetwork->SendBattlePassInfoReq(-1, pUIManager->GetBattlePassUI()->GetCurrentPage());
			}
		}
	}
	break;
	default:
		break;
	}

}
#endif

#ifdef PRESTIGE_SYSTEM
void CSessionState::ReceivePrestigeMessage(CNetworkMessage* istr)
{

	pTypeBase* pBase = reinterpret_cast<pTypeBase*>(istr->GetBuffer());

	CUIManager* pUIManager = CUIManager::getSingleton();

	CTString strMessage;

	switch (pBase->subType)
	{
	case MSG_PRESTIGE_ERROR_LIMIT:
		strMessage.PrintF(_S(8558, "Sorry, you already achieved the max Prestige"));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		break;
	case MSG_PRESTIGE_ERROR_EXP_NEEDED:
		strMessage.PrintF(_S(8559, "Sorry, you don't have the required exp for next Prestige"));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		break;
	case MSG_PRESTIGE_ERROR_NOT_EXIST_NPC:
		strMessage.PrintF(_S(8705, "This npc doesn't exist"));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		break;
	case MSG_PRESTIGE_ERROR_NOCONDITION_LEVEL:
		strMessage.PrintF(_S(8560, "You don't have the required level for next Prestige"));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		break;
	case MSG_PRESTIGE_ERROR_EMPTY_SLOT:
		strMessage.PrintF(_S(8707, "You need more empty slot in your inventory"));
		pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
		break;
	case MSG_PRESTIGE_INFO_REP:
	{
		ResponseClient::prestigeInfo* pPack = reinterpret_cast<ResponseClient::prestigeInfo*>(istr->GetBuffer());
		pUIManager->GetPrestigeUI()->ClearItems();
		pUIManager->GetPrestigeUI()->UpdateInfo(pPack->premium, pPack->points, pPack->progress, pPack->level, pPack->season);
		for (int i = 0; i < pPack->total; i++)
		{
			PrestigeItem bPsItem;
			bPsItem.level = pPack->list[i].level;
			bPsItem.name = pPack->list[i].name;
			bPsItem.points = pPack->list[i].points;

			PrestigeRewardItem reward;
			reward.itemIdx = pPack->list[i].item_index;
			reward.itemCount = pPack->list[i].item_count;
			bPsItem.reward = reward;

			pUIManager->GetPrestigeUI()->AddItemFree(bPsItem);

			PrestigeRewardItem rewardPremium;
			rewardPremium.itemIdx = pPack->list[i].premium_item_index;
			rewardPremium.itemCount = pPack->list[i].premium_item_count;
			bPsItem.reward = rewardPremium;

			pUIManager->GetPrestigeUI()->AddItemPremium(bPsItem);
		}

		pUIManager->GetPrestigeUI()->SetHasNext(pPack->next);

		if (pUIManager->GetPrestigeUI()->IsVisible())
			pUIManager->GetPrestigeUI()->RefreshUI();
		else
			pUIManager->GetPrestigeUI()->OpenUI();
	}
	break;
	case MSG_PRESTIGE_REP:
	{
		ResponseClient::prestigeInfo* pPack = reinterpret_cast<ResponseClient::prestigeInfo*>(istr->GetBuffer());
		if (pPack->nIndex == _pNetwork->MyCharacterInfo.index)
		{
			CUIMsgBox_Info	MsgBoxInfo;
			strMessage.PrintF(_S(8554, "Prestige"));
			MsgBoxInfo.SetMsgBoxInfo(strMessage, UMBS_OK, UI_NONE, MSGCMD_NULL);
			strMessage.PrintF(_S(8561, "Congratulations! You achieved a new Prestige level! %d"), pPack->level);
			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
	}
	break;
	default:
		break;
	}
}
#endif