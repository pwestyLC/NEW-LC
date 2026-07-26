#include "stdh.h"

// ��� ����. [12/1/2009 rumist]
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Contents/Base/UIChangeWeaponNew.h>
#include <Engine/Contents/Base/UIChangeEquipment.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Interface/UIHelp.h>
#include <Engine/Interface/UIMixNew.h>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Contents/Base/UIQuestBookNew.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/Base/ChangeWeapon.h>

#define DEF_LIST_INFO_COUNT 5

enum eERROR_MSG
{
	eERROR_NOT_TRADE_ITEM = 0,
	eERROR_NOT_TRADE_LEVEL,
	eERROR_NOT_ENOUGH_NAS,
	eERROR_NO_TRADE_ITEM,
	eERROR_NO_SELECT_TRADE_ITEM,
	eERROR_SEALED_ITEM,
	eERROR_ONLY_WEAPON,
	eERROR_ONLY_ARMOR,
	eERROR_WEARING_EQUIPMENT,
	eERROR_USE_SKILL,
	eERROR_USE_TELEPORT
};

//--------------------------------------------------------------
// â �ݱ�
class CmdChangeWeaponClose : public Command
{
public:
	CmdChangeWeaponClose() : pUI_(NULL) {}
	void setData(CUIChangeWeapon* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->close();
	}
private:
	CUIChangeWeapon* pUI_;
};

//--------------------------------------------------------------
// Ȯ�� Ŭ��
class CmdChangeWeaponOk : public Command
{
public:
	CmdChangeWeaponOk() : pUI_(NULL) {}
	void setData(CUIChangeWeapon* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->PressOK();
	}
private:
	CUIChangeWeapon* pUI_;
};

//--------------------------------------------------------------
// ����Ʈ Ŭ��
class CmdChangeWeaponClick : public Command
{
public:
	CmdChangeWeaponClick() : pUI_(NULL) {}
	void setData(CUIChangeWeapon* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->ClickListItem();
	}
private:
	CUIChangeWeapon* pUI_;
};

// [KH_07044] 3�� ���� ���� �߰�
extern INDEX g_iShowHelp1Icon;

enum eSelection
{
	CHANGEWEAPON_OK,
	CHANGEWEAPON_TALK,
	CHANGEWEAPON_EVENT,
	CHANGESHIELD_OK,
	CHANGEWEAPON_MASTERSTONE,
	CHANGEEQUIP_WEAPON_OPEN,
	CHANGEEQUIP_ARMOR_OPEN,
	CHANGEWEAPON_REFORGE_HAMMER,
};

#define CRITERION_LEVEL					(28)
#define EXCHANGE_LIMIT_LEVEL			(29)
#define EXCHANGE_LIMIT_LEVEL_MAX		(72)

CUIChangeWeapon::CUIChangeWeapon()
	: m_piconItem(NULL)
	, m_psbList(NULL)
	, m_bDrag(false)
	, m_nOriX(0), m_nOriY(0)
	, m_llNas(0)
{
	m_eChangeWeaponState	= CHANGEWEAPON_WEAPON;
	m_bCashItemChk			= FALSE;

	int i;	
	for (i = 0; i < eBUTTON_MAX; i++)
	{
		m_pbtn[i] = NULL;
	}

	for (i = 0; i < eTEXT_MAX; i++)
	{
		m_pText[i] = NULL;
	}

	for (i = 0; i < eLIST_MAX; i++)
	{
		m_plist[i] = NULL;
	}

	setInherit(false);
}

void CUIChangeWeapon::OpenChangeWeapon(int iMobIndex, BOOL bHasQuest, FLOAT fX, FLOAT fZ )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( pUIManager->GetInventory()->IsLocked() == TRUE ||
		pUIManager->GetInventory()->IsLockedArrange() == TRUE)
	{
		pUIManager->GetInventory()->ShowLockErrorMessage();
		return;
	}

	// If this is already exist
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_CHANGEWEAPON_REQ ) || IsVisible() )
		return;

	// ���� ĳ���������� üũ��!!!
	pUIManager->CloseMessageBox( MSGCMD_CHANGEWEAPON_REP );
	pUIManager->CloseMessageBox( MSGCMD_CHANGEWEAPON_NOTIFY );

	// Set position of target npc
	m_fNpcX = fX;
	m_fNpcZ = fZ;

	CMobData* MD = CMobData::getData(iMobIndex);

	CTString strMessage;	

	if(iMobIndex == 1261)		// ��æƮ ������ �Ҹ� ; ������ �����
	{
		pUIManager->CreateMessageBoxL( _S(5435, "������ �������� ���׷��̵��ϱ�" ), UI_CHANGEWEAPON, MSGLCMD_CHANGEWEAPON_REQ );		

		CTString	strNpcName = CMobData::getData(iMobIndex)->GetName();
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, strNpcName, -1, 0xE18600FF );

		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(5443,"�Ϲ����� �������� ���׷��̵��ϴ� ���� �Ѱ谡 �ֽ��ϴ�. ���� �� �Ѱ踦 �پ� �Ѵ� ���׷��̵��ϴ� ����� �˰� ������ ���� ���� ���׷��̵� �Ѱ� ��ġ �̻� +26���� ���׷��̵� �� �� �ֽ��ϴ�."), -1, 0xA3A1A3FF );
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(5444,"�� ����� ������ �����Դϴ�. ������ ������ ũ�� ���⸶���� ����� ��� �� ������ ���� 2������ ������ ���� ������ ������ ��޺��� 6�ܰ谡 �����մϴ�."), -1, 0xA3A1A3FF );
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(5445,"(0~16, 0~18, 0~20, 0~22, 0~24, 0~25) ��� �� ������ ������ ��� ���� ��� �����մϴ�. �����ϴ� ���׷��̵�� ���� ���� 100%������ �ڶ��մϴ�."), -1, 0xA3A1A3FF );
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(6451,"��, �����ͽ����� �ѹ��̶� ����� �������� �� ��� �ͼӵǾ� �ٸ� ����� ����� �� ���ٴ����� �ݵ�� �����Ͻñ� �ٶ��ϴ�."), -1, 0xA3A1A3FF );

		strMessage= _S(5435, "������ �������� ���׷��̵� �ϱ�" );			
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage, CHANGEWEAPON_MASTERSTONE );	

		strMessage= _S(8399, "Reforge using Hammer" );
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage, CHANGEWEAPON_REFORGE_HAMMER );	

		strMessage.PrintF( _S( 1220, "����Ѵ�." ) );
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage );	

		return;
	}

	// Create refine message box
	pUIManager->CreateMessageBoxL( _S(2308, "����� �� ��ü" ), UI_CHANGEWEAPON, MSGLCMD_CHANGEWEAPON_REQ );		

	CTString	strNpcName = CMobData::getData(iMobIndex)->GetName();
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, strNpcName, -1, 0xE18600FF );
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S( 1050, "���� ����ϰ� �ִ� ���⳪ ���� ������ ���� �ʴ°հ�?" ), -1, 0xA3A1A3FF );		
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S( 1051, "�׷� ���� �ڳ׸� ������ �� �ְڱ���." ), -1, 0xA3A1A3FF );
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2309,"������ �����ؾ��� ������ �ֳ�"), -1, 0xA3A1A3FF );			
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2310,"��ü�Ǵ� ���� ���õ� ��ġ�� ���� ������ �ɼǰ��� �����Ǵϱ� �� ������ ���ð� ��ü�Գ�."), -1, 0xF3BA0CFF );
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2311,"�׷��� �̷��� ���� ���ο� ��� ���� �� �ִ� ���� ��� �ְڳ�..."), -1, 0xA3A1A3FF );
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2312,"�� ���� ��ȯ�ϰԳ�...  ������� �� ������ ����..."), -1, 0xA3A1A3FF );

	strMessage.PrintF( _S( 1049, "���� ��ü" ) );			
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage, CHANGEWEAPON_OK );	

	// wooss add shield item exchange
	strMessage= _S(2313, "�� ��ü" );			
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage, CHANGESHIELD_OK );

	strMessage= _S(7025, "������ ���� ��ü" );			
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage, CHANGEEQUIP_WEAPON_OPEN );

	strMessage= _S(7026, "������ �� ��ü" );			
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage, CHANGEEQUIP_ARMOR_OPEN );

	if( bHasQuest )
	{
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_CHANGEWEAPON_REQ);				
	}

	if( MD->IsEvent() )
	{
		strMessage.PrintF( _S( 100, "�̺�Ʈ." ) );			
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage, CHANGEWEAPON_EVENT );
	}

	strMessage.PrintF( _S( 1220, "����Ѵ�." ) );
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage );	

}

void CUIChangeWeapon::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

void CUIChangeWeapon::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

void CUIChangeWeapon::PressOK()
{
	SendChangeWeaponReq();
}

void CUIChangeWeapon::ClickListItem()
{
	refreshListInfo();
}

void CUIChangeWeapon::MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput )
{
	switch( nCommandCode )
	{
	case MSGCMD_CHANGEWEAPON_REP:		// ���� ��ü Ȯ��.
		{
			if( bOK )
			{
				ChangeWeapon* pData = GAMEDATAMGR()->GetChangeWeapon();

				if (pData != NULL)
					pData->SendChangeEquipment(m_bCashItemChk);
			}
		}
		break;
	}
}

void CUIChangeWeapon::MsgBoxLCommand( int nCommandCode, int nResult )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	switch( nCommandCode )
	{
	case MSGLCMD_CHANGEWEAPON_REQ:
		if( nResult == CHANGEWEAPON_OK )
		{
			open(CHANGEWEAPON_WEAPON);

			if( !pUIManager->GetInventory()->IsVisible() )
				pUIManager->GetInventory()->ToggleVisible();			
			// [KH_07044] 3�� ���� ���� �߰�
			if(g_iShowHelp1Icon)
			{
				pUIManager->GetHelp3()->ClearHelpString();
				pUIManager->GetHelp3()->AddHelpString(_S(3288, "��ü�ϰ��� �ϴ� ���⳪ ���� ���� ����� �� ĭ�� �÷� ������ ��ü����� ���Ǹ�, ��ü�Ϸ��� ������ �����ϰ� Ȯ���� ������ ����� ���ҵǰ� ���õ� ��ġ �״�� ������ ������ ���� ��ȯ�� �̷�� ���ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3289, "�� ��ü�Ǵ� ���� �� ���� ������ �ɼ��� �Ű����� �ʽ��ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3290, "�� 29���� �̻��� ������ ��ü�� �����մϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3291, "�� ���� ���� ��� ����ɼ� ���(73���� �̻�)�� ��ü�� �� �����ϴ�."));
				pUIManager->GetHelp3()->OpenHelp(this);
			}
		}		
		else if( nResult == CHANGEWEAPON_TALK )				// �̾߱��ϱ�.
		{
			CUIQuestBook::TalkWithNPC();
		}
		else if( nResult == CHANGEWEAPON_EVENT )			// Event
		{
		}
		else if(nResult == CHANGESHIELD_OK)
		{
			open(CHANGEWEAPON_SHIELD);

			if( !pUIManager->GetInventory()->IsVisible() )
				pUIManager->GetInventory()->ToggleVisible();
			// [KH_07044] 3�� ���� ���� �߰�
			if(g_iShowHelp1Icon)
			{
				pUIManager->GetHelp3()->ClearHelpString();
				pUIManager->GetHelp3()->AddHelpString(_S(3288, "��ü�ϰ��� �ϴ� ���⳪ ���� ���� ����� �� ĭ�� �÷� ������ ��ü����� ���Ǹ�, ��ü�Ϸ��� ������ �����ϰ� Ȯ���� ������ ����� ���ҵǰ� ���õ� ��ġ �״�� ������ ������ ���� ��ȯ�� �̷�� ���ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3289, "�� ��ü�Ǵ� ���� �� ���� ������ �ɼ��� �Ű����� �ʽ��ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3290, "�� 29���� �̻��� ������ ��ü�� �����մϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3291, "�� ���� ���� ��� ����ɼ� ���(73���� �̻�)�� ��ü�� �� �����ϴ�."));
				pUIManager->GetHelp3()->OpenHelp(this);
			}
		}
		else if (nResult == CHANGEEQUIP_WEAPON_OPEN)
		{
			if( !pUIManager->GetInventory()->IsVisible() )
				pUIManager->GetInventory()->ToggleVisible();

			pUIManager->GetChangeEquipment()->open(CHANGEEQUIP_WEAPON, m_fNpcX, m_fNpcZ);
		}
		else if (nResult == CHANGEEQUIP_ARMOR_OPEN)
		{
			if( !pUIManager->GetInventory()->IsVisible() )
				pUIManager->GetInventory()->ToggleVisible();

			pUIManager->GetChangeEquipment()->open(CHANGEEQUIP_ARMOR, m_fNpcX, m_fNpcZ);
		}
		else if(nResult == CHANGEWEAPON_MASTERSTONE)
		{
			pUIManager->GetMixNew()->OpenMixNewMasterStone(CHANGEWEAPON_MASTERSTONE);
		}
		else if (nResult == CHANGEWEAPON_REFORGE_HAMMER)
		{
			pUIManager->GetMixNew()->OpenMixNewMasterStone(CHANGEWEAPON_REFORGE_HAMMER);
		}
		// [090527: selo] Ȯ���� ����Ʈ ����
		else if( ciQuestClassifier < nResult )	
		{
			// ������ ����Ʈ�� ���� ���� �Ǵ� ���� â�� ����.
			CUIQuestBook::SelectQuestFromMessageBox( nResult );
		}
		else
		{
			close();
		}
		break;
	
	}
}

SQUAD CUIChangeWeapon::CalculateNeedNas( int iWeaponLevel )
{
	SQUAD llPrice	= 0;
	if( iWeaponLevel <= CRITERION_LEVEL )
		return llPrice;

	int nPlus = 0;
	if (m_piconItem != NULL)
	{
		CItems* pItem = m_piconItem->getItems();

		if (pItem != NULL)
			nPlus = pItem->GetItemPlus();
	}

	llPrice = 5000 * (nPlus * 2 + 10) * (iWeaponLevel - CRITERION_LEVEL) / 10;
	return llPrice;
}

SQUAD CUIChangeWeapon::CalculateNeedNasS( int iWeaponLevel )
{
	SQUAD llPrice	= 0;
	if( iWeaponLevel <= CRITERION_LEVEL )
		return llPrice;

	int nPlus = 0;
	if (m_piconItem != NULL)
	{
		CItems* pItem = m_piconItem->getItems();

		if (pItem != NULL)
			nPlus = pItem->GetItemPlus();
	}

	llPrice = 3000 * (nPlus * 2 + 10) * (iWeaponLevel - CRITERION_LEVEL) / 10;
	return llPrice;
}

void CUIChangeWeapon::SendChangeWeaponReq()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (m_piconItem == NULL)
	{
		ShowSystemMsg(eERROR_NO_TRADE_ITEM);
		return;
	}

	if (m_piconItem->IsEmpty() != false)
	{
		ShowSystemMsg(eERROR_NO_TRADE_ITEM);
		return;
	}

	if( ( (CPlayerEntity*)CEntity::GetPlayerEntity(0) )->IsSkilling() )
	{
		ShowSystemMsg(eERROR_USE_SKILL);
		return;
	}
	
	if( pUIManager->IsCSFlagOn( CSF_TELEPORT ) )
	{
		ShowSystemMsg(eERROR_USE_TELEPORT);
		return;
	}

	if( m_llNas > _pNetwork->MyCharacterInfo.money && !m_bCashItemChk )
	{
		ShowSystemMsg(eERROR_NOT_ENOUGH_NAS);
		return;
	}

	if (m_plist[eLIST_ITEM] == NULL)
	{
		ShowSystemMsg(eERROR_NO_SELECT_TRADE_ITEM);
		return;
	}

	int nSelIdx = m_plist[eLIST_ITEM]->getCurSel();

	if( nSelIdx < 0 )
	{
		ShowSystemMsg(eERROR_NO_SELECT_TRADE_ITEM);
		return;
	}

	ChangeWeapon* pData = GAMEDATAMGR()->GetChangeWeapon();

	if (pData == NULL)
		return;

	pData->SetSelectIdx(getSelectIdx(nSelIdx));
	pUIManager->CloseMessageBox( MSGCMD_CHANGEWEAPON_REP );
	
	// Create message box of remission
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S(2308, "����� �� ��ü" ), UMBS_OKCANCEL,UI_CHANGEWEAPON, MSGCMD_CHANGEWEAPON_REP );
	MsgBoxInfo.AddString( _S(2323,"��ü ����� ���� ���õ� ����� �Ű������� ������ �ɼ��� �Ű����� �ʽ��ϴ�. ����� ���� ��ü�Ͻðڽ��ϱ�?" ) );
	pUIManager->CreateMessageBox( MsgBoxInfo );
}

void CUIChangeWeapon::initialize()
{
	m_piconItem = (CUIIcon*)findUI("icon_item");
	m_psbList = (CUIScrollBar*)findUI("list_scroll");
	CTString strBtn[eBUTTON_MAX] = { "btn_close", "btn_ok", "btn_no" };
	CTString strText[eTEXT_MAX] = { "move_title", "str_title", "str_nas", "str_listType" };
	CTString strList[eLIST_MAX] = { "list_item", "list_itemInfo" };
	int i;	
	for (i = 0; i < eBUTTON_MAX; i++)
	{
		m_pbtn[i] = (CUIButton*)findUI(strBtn[i]);
	}

	for (i = 0; i < eTEXT_MAX; i++)
	{
		m_pText[i] = (CUIText*)findUI(strText[i]);
	}

	for (i = 0; i < eLIST_MAX; i++)
	{
		m_plist[i] = (CUIList*)findUI(strList[i]);
	}

	// command ����
	if (m_pbtn[eBUTTON_CLOSE] != NULL)
	{
		CmdChangeWeaponClose* pCmd = new CmdChangeWeaponClose;
		pCmd->setData(this);
		m_pbtn[eBUTTON_CLOSE]->SetCommandUp(pCmd);
	}

	if (m_pbtn[eBUTTON_NO] != NULL)
	{
		CmdChangeWeaponClose* pCmd = new CmdChangeWeaponClose;
		pCmd->setData(this);
		m_pbtn[eBUTTON_NO]->SetCommandUp(pCmd);
	}

	if (m_pbtn[eBUTTON_OK] != NULL)
	{
		CmdChangeWeaponOk* pCmd = new CmdChangeWeaponOk;
		pCmd->setData(this);
		m_pbtn[eBUTTON_OK]->SetCommandUp(pCmd);
	}
}

void CUIChangeWeapon::open( eChangeWeaponState eType )
{
	m_eChangeWeaponState = eType;
	CUIManager* pUIManager = CUIManager::getSingleton();
	pUIManager->CloseMessageBox( MSGCMD_CHANGEWEAPON_REP );
	SetVisible(TRUE);
	Hide(FALSE);

	ChangeWeapon* pData = GAMEDATAMGR()->GetChangeWeapon();

	if (pData != NULL)
		pData->Clear();
	
	UpdateUI();

	pUIManager->RearrangeOrder( UI_CHANGEWEAPON, TRUE );
	pUIManager->GetInventory()->Lock( TRUE, TRUE, LOCK_CHANGEWEAPON );
}

void CUIChangeWeapon::close()
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CUITooltipMgr::getSingleton()->setData(NULL);
	SetVisible(FALSE);
	Hide(TRUE);
	
	pUIManager->CloseMessageBox( MSGCMD_CHANGEWEAPON_REP );
	pUIManager->RearrangeOrder( UI_CHANGEWEAPON, FALSE );
	pUIManager->GetInventory()->Lock( FALSE, FALSE, LOCK_CHANGEWEAPON );

	if(m_bCashItemChk)
		m_bCashItemChk = FALSE;
}

void CUIChangeWeapon::UpdateUI()
{	
	if (refreshString() == false)
		close();

	if (refreshListItem() == false)
		close();

	refreshListInfo();

	clearIcon();
}

void CUIChangeWeapon::OnUpdate( float fDeltaTime, ULONG ElapsedTime )
{
	if (IsVisible() == FALSE)
		return;

	// Check distance
	FLOAT	fDiffX = _pNetwork->MyCharacterInfo.x - m_fNpcX;
	FLOAT	fDiffZ = _pNetwork->MyCharacterInfo.z - m_fNpcZ;

	if( m_bCashItemChk == FALSE )
	{
		if( fDiffX * fDiffX + fDiffZ * fDiffZ > UI_VALID_SQRDIST )
		{
			close();
		}
	}
}

WMSG_RESULT CUIChangeWeapon::OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg )
{
	if (m_bHide)
		return WMSG_FAIL;

	if( m_bDrag && ( pMsg->wParam & MK_LBUTTON ) )
	{
		int ndX = x - m_nOriX;
		int ndY = y - m_nOriY;

		m_nOriX = x;
		m_nOriY = y;

		Move( ndX, ndY );
		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	CUIManager::getSingleton()->SetMouseCursorInsideUIs();

	return WMSG_FAIL;
}

WMSG_RESULT CUIChangeWeapon::OnLButtonDown( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if( m_pText[eTEXT_MOVE] && m_pText[eTEXT_MOVE]->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}

	CUIManager::getSingleton()->RearrangeOrder( UI_CHANGEWEAPON, TRUE );

	return WMSG_FAIL;
}

WMSG_RESULT CUIChangeWeapon::OnLButtonUp( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	CUIManager* pUIManager = CUIManager::getSingleton();

	if (m_piconItem == NULL)
	{
		CUIManager::getSingleton()->ResetHoldBtn();
		return WMSG_FAIL;
	}
	// ������ �˻�

	CUIIcon* pDrag = pUIManager->GetDragIcon();

	if (m_piconItem->IsInside(x, y) == TRUE && pDrag != NULL)
	{
		bool bError = false;
		// Error check
		if (pDrag->IsWearTab() == true)
		{
			ShowSystemMsg(eERROR_WEARING_EQUIPMENT);
			bError = true;
		}

		CItems*	pItems = pDrag->getItems();

		if (pItems == NULL)
			return WMSG_FAIL;

		CItemData*	pItemData = pItems->ItemData;

		if (pItemData == NULL)
			return WMSG_FAIL;

		if (pItems->Item_Flag & FLAG_ITEM_SEALED || pItems->Item_Flag & FLAG_ITEM_COMPOSITION)
		{
			ShowSystemMsg(eERROR_SEALED_ITEM);
			bError = true;
		}

		if (bError == true)
		{
			CUIManager::getSingleton()->ResetHoldBtn();
			return WMSG_FAIL;
		}

		if (pItemData != NULL)
		{
			switch(m_eChangeWeaponState)
			{
			case CHANGEWEAPON_WEAPON:
				{
					if (pItemData->GetType() != CItemData::ITEM_WEAPON)
					{
						ShowSystemMsg(eERROR_ONLY_WEAPON);
						bError = true;
					}
				}
				break;
			case CHANGEWEAPON_SHIELD:
				{
					if (pItemData->GetType() != CItemData::ITEM_SHIELD)
					{
						ShowSystemMsg(eERROR_ONLY_ARMOR);
						bError = true;
					}
				}
				break;
			}

			if (checkValidItem(pItemData->getindex()) == true && bError == false)
			{
				ChangeWeapon* pData = GAMEDATAMGR()->GetChangeWeapon();
				if (pData != NULL)
				{
					pData->SetInvenTab(pItems->Item_Tab);
					pData->SetInvenIdx(pItems->InvenIndex);
					pData->SetVirtualIndex(pItems->Item_UniIndex);
				}
				m_piconItem->setData(pItems);
				updateNas();
				refreshListInfo();
			}
		}
	}

	CUIManager::getSingleton()->ResetHoldBtn();
	return WMSG_FAIL;
}

bool CUIChangeWeapon::refreshString()
{
	CTString strString[eTEXT_MAX];
	m_llNas = 0;
	strString[eTEXT_NAS].PrintF("%d", m_llNas);

	switch(m_eChangeWeaponState)
	{
	case CHANGEWEAPON_WEAPON:
		{
			strString[eTEXT_TITLE].PrintF( _S(1049, "���� ��ü"));
			strString[eTEXT_LISTNAME].PrintF( _S(1059, "���� ����Ʈ"));
		}
		break;
	case CHANGEWEAPON_SHIELD:
		{
			strString[eTEXT_TITLE].PrintF( _S(2313, "�� ��ü"));
			strString[eTEXT_LISTNAME].PrintF( _S(2316, "Ŭ���� ����Ʈ"));
		}
		break;
	default:
		return false;
	}
	
	for (int i = 1; i < eTEXT_MAX; i++)
	{
		if (m_pText[i] == NULL)
		{
			LOG_DEBUG("CUIChangeWeapon::refreshString() ERROR %d String Null ptr", i);
			return false;
		}

		m_pText[i]->SetText(strString[i]);
	}

	return true;
}

bool CUIChangeWeapon::refreshListItem()
{
	if (m_plist[eLIST_ITEM] == NULL)
		return false;

	m_plist[eLIST_ITEM]->DeleteAllListItem();
	m_plist[eLIST_ITEM]->setCurSel(-1);

	if (m_psbList != NULL)
		m_psbList->SetScrollPos(0);

	int i, nMax = 0;
	CUIListItem* pTempItem = m_plist[eLIST_ITEM]->GetListItemTemplate();
	CUIListItem* pItem = NULL;

	switch(m_eChangeWeaponState)
	{
	case CHANGEWEAPON_WEAPON:
		{
			nMax = DEF_TRADE_WEAPON_MAX - 1; // (�Ѱ��� - ��ȯ���� ��)
		}
		break;
	case CHANGEWEAPON_SHIELD:
		{
			nMax = TOTAL_JOB - 1; // (����Ʈ ������ ����)
		}
		break;
	default:
		return false;
	}

	int nListString[CHANGEWEAPON_MAX][DEF_TRADE_WEAPON_MAX - 1] = { \
	{1038, 1039, 1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047, 2306, 2307}, \
	{43, 44, 45, 46, 47, 48, 5732, 5820, 0, 0, 0, 0}		\
	};

	CTString strTemp;

	for (i = 0; i < nMax; i++)
	{
		m_plist[eLIST_ITEM]->AddListItem(pTempItem->Clone());
		pItem = (CUIListItem*)m_plist[eLIST_ITEM]->GetListItem( i );

		if (pItem == NULL)
			continue;

		CUIText* pText = (CUIText*)pItem->findUI("str_itemType");

		if (pText != NULL)
		{
			strTemp.PrintF(_S( nListString[m_eChangeWeaponState][i], "����Ʈ ��Ʈ��"));
			pText->SetText(strTemp);
		}

		CmdChangeWeaponClick* pCmd = new CmdChangeWeaponClick;
		pCmd->setData(this);
		pItem->SetCommandUp(pCmd);	
	}

	m_plist[eLIST_ITEM]->UpdateList();
	m_plist[eLIST_ITEM]->UpdateScroll(nMax);
	return true;
}

bool CUIChangeWeapon::refreshListInfo()
{
	if (m_plist[eLIST_INFO] == NULL)
		return false;
	// ���� �ʱ�ȭ
	m_plist[eLIST_INFO]->DeleteAllListItem();

	// ���� ���� �˻�
	if (m_piconItem == NULL)
		return false;

	if (m_piconItem->IsEmpty() != false)
		return false;

	if (m_plist[eLIST_ITEM] == NULL)
		return false;

	// ��ȯ�� ������ �ε��� ���
	int nSelectItemIdx = m_piconItem->getIndex();
	int nSelectListIdx = m_plist[eLIST_ITEM]->getCurSel();

	if (nSelectListIdx < 0)
		return false;

	// ���� ����
	int i;
	int nTradeItemIdx = 0;
	CUIListItem* pTempItem = m_plist[eLIST_INFO]->GetListItemTemplate();
	CUIListItem* pItem = NULL;

	// ��Ȱ�� ������ ���� ���
	switch(m_eChangeWeaponState)
	{
	case CHANGEWEAPON_WEAPON:
		{
			nTradeItemIdx = CChangeEquipment::getTradeWeaponIndex(nSelectItemIdx, nSelectListIdx);
		}
		break;
	case CHANGEWEAPON_SHIELD:
		{
			nTradeItemIdx = CChangeEquipment::getTradeArmorIndex(nSelectItemIdx, nSelectListIdx);
		}
		break;
	default:
		return false;
	}

	if (nTradeItemIdx <= 0)
		return false;

	if (GAMEDATAMGR()->GetChangeWeapon() != NULL)
		GAMEDATAMGR()->GetChangeWeapon()->SetTradeItemIndex(nTradeItemIdx);

	// ���� Ÿ��Ʋ ��Ʈ�� �ε���
	int nListString[CHANGEWEAPON_MAX][DEF_LIST_INFO_COUNT] = { \
	{1065, 1066, 1067, 1068, 1069}, \
	{2317, 2318, 1067, 87, 0}		\
	};

	// String XML ID
	CTString strTitleID[DEF_LIST_INFO_COUNT] = {"str_nameTitle", "str_levelTitle", "str_classTitle", \
		"str_point1Title", "str_point2Title" };
	// String XML ID
	CTString strValueID[DEF_LIST_INFO_COUNT] = {"str_name", "str_level", "str_class", "str_point1", "str_point2" };

	CTString strTemp;
	m_plist[eLIST_INFO]->AddListItem(pTempItem->Clone());
	pItem = (CUIListItem*)m_plist[eLIST_INFO]->GetListItem(0);

	if (pItem == NULL)
	{
		m_plist[eLIST_INFO]->DeleteAllListItem();
		return false;
	}

	CUIText* pTextString = NULL;
	CUIText* pTextValue = NULL;

	// Ÿ��Ʋ ����
	for (i = 0; i < DEF_LIST_INFO_COUNT; i++)
	{
		pTextString = (CUIText*)pItem->findUI(strTitleID[i]);

		if (pTextString != NULL)
		{
			strTemp.PrintF(_S( nListString[m_eChangeWeaponState][i], "Ÿ��Ʋ ��Ʈ��"));
			pTextString->SetText(strTemp);
		}
	}

	pTextString = (CUIText*)pItem->findUI(strTitleID[4]);

	if (pTextString != NULL)
	{
		if (m_eChangeWeaponState == CHANGEWEAPON_SHIELD)
			pTextString->Hide(TRUE);
		else
			pTextString->Hide(FALSE);
	}

	// ������ ���� ����
	CTString strValue[DEF_LIST_INFO_COUNT];

	CItemData* pItemData = CItemData::getData(nTradeItemIdx);

	if (pItemData == NULL)
	{
		m_plist[eLIST_INFO]->DeleteAllListItem();
		return false;
	}	
	
	// ������ �̸�
	strValue[0] = pItemData->GetName();
	// ������ ����
	strValue[1].PrintF("%d", pItemData->GetLevel());
	// ������ ��� Ŭ����
	CUIManager::getSingleton()->GetClassOfItem(pItemData, strValue[2]);
	
	int nPoint1 = 0, nPoint2 = 0;
	switch(m_eChangeWeaponState)
	{
	case CHANGEWEAPON_WEAPON:
		{
			nPoint1 = pItemData->GetPhysicalAttack();
			nPoint2 = pItemData->GetMagicAttack();
		}
		break;
	case CHANGEWEAPON_SHIELD:
		{
			nPoint1 = pItemData->GetPhysicalDefence();
		}
		break;
	}
	// ���ݷ�, ����
	strValue[3].PrintF("%d", nPoint1);
	// ���� ���ݷ�, ����
	strValue[4].PrintF("%d", nPoint2);

	for (i = 0; i < DEF_LIST_INFO_COUNT; i++)
	{
		pTextValue = (CUIText*)pItem->findUI(strValueID[i]);

		if (pTextValue != NULL)
		{
			pTextValue->SetText(strValue[i]);
		}
	}

	pTextValue = (CUIText*)pItem->findUI(strValueID[4]);

	if (pTextValue != NULL)
	{
		if (m_eChangeWeaponState == CHANGEWEAPON_SHIELD)
			pTextValue->Hide(TRUE);
		else
			pTextValue->Hide(FALSE);
	}

	m_plist[eLIST_INFO]->UpdateList();
	m_plist[eLIST_INFO]->UpdateScroll(1);
	return true;
}

bool CUIChangeWeapon::checkValidItem( int nItemIdx )
{
	bool bValid = false;

	switch(m_eChangeWeaponState)
	{
	case CHANGEWEAPON_WEAPON:
		bValid = CChangeEquipment::IsValidWeapon(nItemIdx);
		break;
	case CHANGEWEAPON_SHIELD:
		bValid = CChangeEquipment::IsValidArmor(nItemIdx);
		break;
	}
	
	if (bValid == false)
	{
		ShowSystemMsg(eERROR_NOT_TRADE_ITEM);
		return false;
	}
	
	int nlevel = CItemData::getData(nItemIdx)->GetLevel();

	if (nlevel < EXCHANGE_LIMIT_LEVEL || nlevel > EXCHANGE_LIMIT_LEVEL_MAX)
	{
		ShowSystemMsg(eERROR_NOT_TRADE_LEVEL);
		return false;
	}
	
	return true;
}

void CUIChangeWeapon::updateNas()
{
	if (m_pText[eTEXT_NAS] == NULL)
		return;

	CTString strNas;
	m_llNas = 0;

	if (m_piconItem != NULL)
	{
		int nlevel = CItemData::getData(m_piconItem->getIndex())->GetLevel();

		switch(m_eChangeWeaponState)
		{
		case CHANGEWEAPON_WEAPON:
			m_llNas = CalculateNeedNas(nlevel);
			break;
		case CHANGEWEAPON_SHIELD:
			m_llNas = CalculateNeedNasS(nlevel);
			break;
		}
	}
	
	strNas.PrintF("%lli", m_llNas);
	m_pText[eTEXT_NAS]->SetText(strNas);
}

void CUIChangeWeapon::ShowSystemMsg( int errorType )
{
	CTString strMessage;

	switch (errorType)
	{
	case eERROR_NOT_TRADE_ITEM:
		strMessage.PrintF( _S( 2158,"��ü�� �� ���� �������Դϴ�." ) );
		break;
	case eERROR_NOT_TRADE_LEVEL:
		strMessage.PrintF( _S( 1073, "��ü�� �� �ִ� ������ ������ �ƴմϴ�." ) );
		break;
	case eERROR_NOT_ENOUGH_NAS:
		strMessage.PrintF( _S( 1080, "��ü ����� �����մϴ�." ) );
		break;
	case eERROR_NO_TRADE_ITEM:
		strMessage.PrintF( _S( 1076, "��ü�� �������� �����ϴ�." ) );
		break;
	case eERROR_NO_SELECT_TRADE_ITEM:
		strMessage.PrintF( _S( 2321,"���ο� ����� ���� �������ֽʽÿ�." ) );
		break;
	case eERROR_SEALED_ITEM:
		strMessage.PrintF( _S( 1079, "���ε� �������� ��ü�� �� �����ϴ�." ) );
		break;
	case eERROR_ONLY_WEAPON:
		strMessage.PrintF( _S( 1072, "���⸸ ��ü �� �� �ֽ��ϴ�.") );
		break;
	case eERROR_ONLY_ARMOR:
		strMessage.PrintF( _S( 2320, "���� ��ü �� �� �ֽ��ϴ�." ) );
		break;
	case eERROR_WEARING_EQUIPMENT:
		strMessage.PrintF( _S( 1071, "����� �������� ��ü�� �� �����ϴ�." ) );
		break;
	case eERROR_USE_SKILL:
		strMessage.PrintF( _S( 1074, "��ų ����߿��� �������� ��ü�� �� �����ϴ�." ) );
		break;
	case eERROR_USE_TELEPORT:
		strMessage.PrintF( _S( 1075, "���� �̵��߿��� �����۸� ��ü�� �� �����ϴ�." ) );
		break;
	default:
		return;
	}

	_pNetwork->ClientSystemMessage(strMessage, SYSMSG_ERROR);
}

int CUIChangeWeapon::getSelectIdx( int nSelIdx )
{
	int ret = -1;

	switch(m_eChangeWeaponState)
	{
	case CHANGEWEAPON_WEAPON:
		ret = nWeaponSelType[nSelIdx];
		break;
	case CHANGEWEAPON_SHIELD:
		ret = nClassSelType[nSelIdx];
		break;
	}
	return ret;
}

void CUIChangeWeapon::clearIcon()
{
	CTString strToolTip;

	if (m_piconItem != NULL)
	{
		m_piconItem->clearIconData();
		strToolTip.PrintF(_S(7033, "��� ����"));
		m_piconItem->setTooltip(strToolTip);
	}
}
