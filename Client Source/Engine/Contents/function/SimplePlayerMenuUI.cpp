#include "StdH.h"

#include <Engine/Interface/UIInternalClasses.h>
#include "SimplePlayerMenuUI.h"

#include <Engine/Contents/function/PremiumChar.h>
#include <Engine/Interface/UISiegeWarfareNew.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/Base/Party.h>
#include <Engine/Contents/Base/UIPartyNew.h>
#include <Engine/Contents/Base/UICharacterInfoNew.h>
#include <Engine/Contents/Base/UIMsgBoxMgr.h>

enum eCommandSetting
{
	TYPE_PERSONAL = 0,			// �Ϲ�
	TYPE_PARTYLEADER,			// ��Ƽ��
	TYPE_PARTYMEMBER,			// ��Ƽ���
	TYPE_EXPEDITIONLEADER,		// ��������
	TYPE_EXPEDITIONSUBLEADER,	// �����δ���
	TYPE_EXPEDITIONMEMBER,		// �������
};

enum eCmdPersonal
{
	eCMD_PERSONAL_CLASS_NAME = 0,			// Ŭ���� �̸�
	eCMD_PERSONAL_PVP,						// ����/ ������
	eCMD_PERSONAL_AUTO_MATCHING_PARTY,		// ��Ƽ �����Ī
	eCMD_PERSONAL_RAID_INFO,				// ���̵��� ����
	eCMD_PERSONAL_GO_JUNO,
	eCMD_PERSONAL_CANCEL					// ���	
};

enum eCmdPartyLeader
{
	eCMD_PARTY_LEADER_CLASS_NAME = 0,		// Ŭ���� �̸�
	eCMD_PARTY_LEADER_END,					// ��Ƽ ��ü
	eCMD_PARTY_LEADER_QUIT,					// ��Ƽ Ż��
	eCMD_PARTY_LEADER_TYPE_CHANGE,			// ��Ƽ ���� ����
	eCMD_PARTY_LEADER_TYPE_ITEM,			// ��Ƽ �Ϲ� ������ �й�
	eCMD_PARTY_LEADER_TYPE_SPECIAL_ITEM,	// ��Ƽ ����� ������ �й�
	eCMD_PARTY_LEADER_MEMBER,				// ��Ƽ �ɹ�
	eCMD_PARTY_LEADER_AUTO_MATCHING,		// ��Ƽ ���� ��Ī
	eCMD_PARTY_LEADER_CHANGE_EXPEDITION,	// ������� ��ȯ
	eCMD_PARTY_LEADER_INFO,					// ��Ƽ ����
	eCMD_PARTY_LEADER_GO_JUNO,
	eCMD_PARTY_LEADER_CANCEL				// ���
};

enum eCmdPartyMember
{
	eCMD_PARTY_MEMBER_CLASS_NAME = 0,		// Ŭ���� �̸�
	eCMD_PARTY_MEMBER_MEMBER,				// ��Ƽ �ɹ�
	eCMD_PARTY_MEMBER_QUIT,					// ��Ƽ Ż��
	eCMD_PARTY_MEMBER_INFO,					// ��Ƽ ����
	eCMD_PARTY_MEMBER_GO_JUNO,
	eCMD_PARTY_MEMBER_CANCEL				// ���
};

enum eCmdExpeditionLeader
{
	eCMD_EX_LEADER_CLASS_NAME = 0,		// Ŭ���� �̸�
	eCMD_EX_LEADER_TYPE_EXP,			// ������ ����ġ �й�
	eCMD_EX_LEADER_TYPE_ITEM,			// ������ �Ϲ� ������ �й�
	eCMD_EX_LEADER_TYPE_SPECIAL_ITEM,	// ������ ����� ������ �й�
	eCMD_EX_LEADER_MEMBER,				// ������ �ɹ�
	eCMD_EX_LEADER_MANAGER,				// ������ ����
	eCMD_EX_LEADER_END,					// ������ ��ü
	eCMD_EX_LEADER_QUIT,				// ������ Ż��
	eCMD_EX_LEADER_INFO,				// ������ ����
	eCMD_EX_LEADER_COLLECT_ITEM,		// ������ ������ ����
	eCMD_EX_LEADER_GO_JUNO,
	eCMD_EX_LEADER_CANCEL				// ���
};

enum eCmdExpeditionSubLeader
{
	eCMD_EX_SUB_CLASS_NAME = 0,		// Ŭ���� �̸�
	eCMD_EX_SUB_MEMBER ,			// ������ �ɹ�
	eCMD_EX_SUB_MANAGER,			// ������ ����
	eCMD_EX_SUB_QUIT,				// ������ Ż��
	eCMD_EX_SUB_INFO,				// ������ ����
	eCMD_EX_SUB_GO_JUNO,
	eCMD_EX_SUB_CANCEL				// ���
};

enum eCmdExpeditionMember
{
	eCMD_EX_MEMBER_CLASS_NAME = 0,		// Ŭ���� �̸�
	eCMD_EX_MEMBER_MEMBER,				// ������ �ɹ�
	eCMD_EX_MEMBER_QUIT,				// ������ Ż��
	eCMD_EX_MEMBER_INFO,				// ������ ����
	eCMD_EX_MEMBER_GO_JUNO,
	eCMD_EX_MEMBER_CANCEL				// ���
};

// ���� Ŀ�ǵ�.
enum eCmdExp
{
	eCMD_EXP_TYPE_EQUAL = 0,		// �յ� �й�
	eCMD_EXP_TYPE_BATTLE			// ������
};

enum eCmdItem
{
	eCMD_ITEM_TYPE_RANDOM = 0,		// ����
	eCMD_ITEM_TYPE_FIRSTGET			// �Լ��켱
};

enum eCmdSpecialItem
{
	eCMD_SITEM_TYPE_FIRST_GET = 0,	// �Լ��켱
	eCMD_SITEM_TYPE_OPEN_BOX		// ���ڿ���
};

enum eCmdParty
{
	eCMD_PARTY_TYPE_NORMAL = 0,		// �Ϲ�
	eCMD_PARTY_TYPE_BATTLE			// ������
};

class CmdPartyMainMenu : public Command
{
public:
	CmdPartyMainMenu()	: m_pWnd(NULL), m_nCmd(-1)	{}

	void SetData(CSimplePlayerMenuUI* pWnd, int nCmd)	{ m_pWnd = pWnd; m_nCmd = nCmd;	}
	void execute()
	{
		if (m_pWnd != NULL)
			m_pWnd->SetCommand(m_nCmd);
	}

private:
	CSimplePlayerMenuUI* m_pWnd;
	int m_nCmd;
};

class CmdPartySubMenu : public Command
{
public:
	CmdPartySubMenu()	: m_pWnd(NULL), m_nMainCmd(-1), m_nSubCmd(-1)	{}

	void SetData(CSimplePlayerMenuUI* pWnd, int nMainCmd, int nSubCmd)	{ m_pWnd = pWnd; m_nMainCmd = nMainCmd;	m_nSubCmd = nSubCmd;	}
	void execute()
	{
		if (m_pWnd != NULL)
			m_pWnd->SetSubCommand(m_nMainCmd, m_nSubCmd);
	}

private:
	CSimplePlayerMenuUI* m_pWnd;
	int m_nMainCmd;
	int m_nSubCmd;
};

class CmdExpeditionQuit : public Command
{
public:
	void execute()
	{
		GAMEDATAMGR()->GetPartyInfo()->SendExpeditionQuit();
	}
};

class CmdExpeditionEnd : public Command
{
public:
	void execute()
	{
		GAMEDATAMGR()->GetPartyInfo()->SendExpeditionEnd();
	}
};

class CmdExpeditionItemCollect : public Command
{
public:
	void execute()
	{
		_pNetwork->ExpeditionCollectQuestItemReq(_pNetwork->MyCharacterInfo.index);
	}
};

CSimplePlayerMenuUI::CSimplePlayerMenuUI()
	: m_pMainBack(NULL)
	, m_pSubBack(NULL)
	, m_pListMainMenu(NULL)
	, m_pListSubMenu(NULL)
	, m_nMsgBoxID(-1)
{

	for (int i = 0; i < eLIST_OVER_MAX; ++i)
		m_pImgMouseOver[i] = NULL;

	setInherit(false);
}

CSimplePlayerMenuUI::~CSimplePlayerMenuUI()
{
	m_pMainBack = NULL;
	m_pSubBack = NULL;
	m_pListMainMenu = NULL;
	m_pListSubMenu = NULL;

	for (int i = 0; i < eLIST_OVER_MAX; ++i)
		m_pImgMouseOver[i] = NULL;
}

void CSimplePlayerMenuUI::initialize()
{
	m_pListMainMenu = (CUIList*)findUI("list_main_menu");
	m_pListSubMenu = (CUIList*)findUI("list_sub_menu");
	m_pMainBack = (CUIImageSplit*)findUI("img_main_back");
	m_pSubBack = (CUIImageSplit*)findUI("img_sub_back");

	if (m_pSubBack != NULL)
		m_pSubBack->Hide(TRUE);

	UIRectUV uv;
	uv.SetUV(188, 48, 203, 60);

	for (int i = 0; i < eLIST_OVER_MAX; ++i)
	{
		m_pImgMouseOver[i] = new CUIImage;
		m_pImgMouseOver[i]->setTexString("MessageBox.tex");
		
		m_pImgMouseOver[i]->SetUV(uv);
		m_pImgMouseOver[i]->SetSize(15, 15);
		addChild(m_pImgMouseOver[i]);
	}
}

void CSimplePlayerMenuUI::SetMainMenu()
{
	if (m_pListMainMenu == NULL || m_pMainBack == NULL)
		return;

	Hide(FALSE);
	UIMGR()->RearrangeOrder(UI_SIMPLE_PLAYER_MENU, TRUE);

	m_pListMainMenu->DeleteAllListItem();
	m_pListMainMenu->SetHeight(500);

	m_pListStringMenu.clear();

	switch(IsMenuType())
	{
	case TYPE_PERSONAL:
		{
			m_pListStringMenu.push_back(4592);
			m_pListStringMenu.push_back(4593);
			m_pListStringMenu.push_back(4720);
		}
		break;
	case TYPE_PARTYLEADER:
		{
			m_pListStringMenu.push_back(4594);
			m_pListStringMenu.push_back(4595);
			m_pListStringMenu.push_back(4596);
			m_pListStringMenu.push_back(4597);
			m_pListStringMenu.push_back(4598);
			m_pListStringMenu.push_back(4599);
			m_pListStringMenu.push_back(4600);
			m_pListStringMenu.push_back(4601);
			m_pListStringMenu.push_back(4602);
		}
		break;
	case TYPE_PARTYMEMBER:
		{
			m_pListStringMenu.push_back(4599);
			m_pListStringMenu.push_back(4595);
			m_pListStringMenu.push_back(4602);
		}
		break;
	case TYPE_EXPEDITIONLEADER:
		{
			m_pListStringMenu.push_back(4702);
			m_pListStringMenu.push_back(4703);
			m_pListStringMenu.push_back(4704);
			m_pListStringMenu.push_back(4705);
			m_pListStringMenu.push_back(4706);
			m_pListStringMenu.push_back(4707);
			m_pListStringMenu.push_back(4708);
			m_pListStringMenu.push_back(4709);
			m_pListStringMenu.push_back(4710);
		}
		break;
	case TYPE_EXPEDITIONSUBLEADER:
		{
			m_pListStringMenu.push_back(4606);
			m_pListStringMenu.push_back(4607);
			m_pListStringMenu.push_back(4609);
			m_pListStringMenu.push_back(4610);
		}
		break;
	case TYPE_EXPEDITIONMEMBER:
		{
			m_pListStringMenu.push_back(4606);
			m_pListStringMenu.push_back(4609);
			m_pListStringMenu.push_back(4610);
		}
		break;
	}

#ifdef PREMIUM_CHAR
	CPremiumChar* pChar = GAMEDATAMGR()->GetPremiumChar();
	if (pChar->getType() == PREMIUM_CHAR_TYPE_FIRST)
		m_pListStringMenu.push_back(8416);
#endif

	m_pListStringMenu.push_back(139);

	SetMainMenuList(IsMenuType());

	m_pListMainMenu->UpdateList();

	int nHeight = m_pListMainMenu->GetItemTotalHeight();

	m_pListMainMenu->SetHeight(nHeight);
	m_pMainBack->SetHeight(nHeight + 13);
	m_pMainBack->UpdateSplit();

	SetSize(m_pMainBack->GetWidth(), m_pMainBack->GetHeight());
}

void CSimplePlayerMenuUI::SetMainMenuList( int nCmd )
{
	CUIListItem* pItemTmp = m_pListMainMenu->GetListItemTemplate();
	CUIListItem* pItem = NULL;
	CUIText* pText = NULL;

	int nMaxWidth = 0;

	CDrawPort* pDrawPort = UIMGR()->GetDrawPort();

	int nCount = m_pListStringMenu.size() + 1;
	int		i;

	for (i = 0; i < nCount; ++i)
	{
		if (m_pListMainMenu->getChildCount() <= nCount)
			m_pListMainMenu->AddListItem(pItemTmp->Clone());

		pItem = (CUIListItem*)m_pListMainMenu->getChildAt(i);

		if (pItem == NULL)
			continue;

		CmdPartyMainMenu* pCmd = new CmdPartyMainMenu;
		pCmd->SetData(this, i);

		if (IsSubList(i) == true)
			pItem->SetCommandEnter(pCmd);
		else
			pItem->SetCommandUp(pCmd);

		pText = (CUIText*)pItem->findUI("text_menu_name");

		if (pText == NULL)
			continue;

		if (i == 0)
		{
			pText->SetText(_pNetwork->MyCharacterInfo.name);
			pText->setFontColor(C_YELLOW | 0xff);
		}
		else
		{
			pText->SetText(_S(m_pListStringMenu[i - 1], "�޴� �̸�"));
		}

		if (pDrawPort != NULL)
		{
			int nCurWidth = pDrawPort->GetTextWidth2(pText->getText());

			if (nMaxWidth < nCurWidth)
				nMaxWidth = nCurWidth;
		}
	}

	for (i = 0; i < nCount; ++i)
	{
		pItem = (CUIListItem*)m_pListMainMenu->getChildAt(i);

		if (pItem != NULL)
			pItem->SetWidth(nMaxWidth);
	}

	// 14�� ��
	m_pMainBack->SetWidth(nMaxWidth + 14);
	m_pListMainMenu->SetWidth(nMaxWidth);

	if (m_pImgMouseOver[eMAIN_LIST_OVER] != NULL)
	{
		m_pImgMouseOver[eMAIN_LIST_OVER]->SetWidth(nMaxWidth);
		m_pImgMouseOver[eMAIN_LIST_OVER]->Hide(TRUE);
	}
}

void CSimplePlayerMenuUI::SetSubMenuList( int nCmd, int nCount, int* nStrIndex, SBYTE sbSel )
{
	if (m_pListSubMenu == NULL || m_pSubBack == NULL)
		return;

	m_pListSubMenu->DeleteAllListItem();

	m_pListSubMenu->Hide(FALSE);
	m_pSubBack->Hide(FALSE);

	m_pListSubMenu->SetHeight(500);

	CUIListItem* pItemTmp = m_pListSubMenu->GetListItemTemplate();
	CUIListItem* pItem = NULL;
	CUIText* pText = NULL;

	int nMaxWidth = 0;

	CDrawPort* pDrawPort = UIMGR()->GetDrawPort();
	int		i;

	for (i = 0; i < nCount; ++i)
	{
		if (m_pListSubMenu->getChildCount() <= nCount)
			m_pListSubMenu->AddListItem(pItemTmp->Clone());

		pItem = (CUIListItem*)m_pListSubMenu->getChildAt(i);

		if (pItem == NULL)
			continue;

		CmdPartySubMenu* pCmd = new CmdPartySubMenu;
		pCmd->SetData(this, nCmd, i);
		pItem->SetCommandUp(pCmd);

		pText = (CUIText*)pItem->findUI("text_menu_name");

		if (pText == NULL)
			continue;

		pText->SetText(_S(nStrIndex[i], "�޴� �̸�"));

		if (sbSel == i)
			pText->setFontColor(DEF_UI_COLOR_YELLOW);
		else
			pText->setFontColor(0xC2BAC5FF);

		if (pDrawPort != NULL)
		{
			int nCurWidth = pDrawPort->GetTextWidth2(pText->getText());

			if (nMaxWidth < nCurWidth)
				nMaxWidth = nCurWidth;
		}
	}

	for (i = 0; i < nCount; ++i)
	{
		pItem = (CUIListItem*)m_pListSubMenu->getChildAt(i);
		
		if (pItem != NULL)
			pItem->SetWidth(nMaxWidth);
	}

	m_pListSubMenu->UpdateList();

	int nHeight = m_pListSubMenu->GetItemTotalHeight();

	m_pListSubMenu->SetSize(nMaxWidth, nHeight);

	m_pSubBack->SetPosX(m_pMainBack->GetWidth());
	m_pSubBack->SetSize(nMaxWidth + 14, nHeight + 13);
	m_pSubBack->UpdateSplit();

	SetSize(m_pMainBack->GetWidth() + m_pSubBack->GetWidth(), m_nHeight);

	pItem = (CUIListItem*)m_pListMainMenu->GetListItem(nCmd);

	if (pItem != NULL)
	{
		m_pSubBack->SetPosY(pItem->GetAbsPosY() - this->GetPosY() - 7);
	}

	if (m_pImgMouseOver[eSUB_LIST_OVER] != NULL)
	{
		m_pImgMouseOver[eSUB_LIST_OVER]->SetWidth(nMaxWidth);
		m_pImgMouseOver[eSUB_LIST_OVER]->Hide(TRUE);
	}
}

int CSimplePlayerMenuUI::IsMenuType()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if(pUIManager->IsCSFlagOn(CSF_PARTY))
	{
		if(GAMEDATAMGR()->GetPartyInfo()->AmILeader())
			return TYPE_PARTYLEADER;
		else
			return TYPE_PARTYMEMBER;
	}
	else if(pUIManager->IsCSFlagOn(CSF_EXPEDITION))
	{
		switch(GAMEDATAMGR()->GetPartyInfo()->GetExpeditionMyPosition())
		{
		case MSG_EXPED_MEMBERTYPE_BOSS:
			return TYPE_EXPEDITIONLEADER;

		case MSG_EXPED_MEMBERTYPE_MBOSS:
			return TYPE_EXPEDITIONSUBLEADER;

		case MSG_EXPED_MEMBERTYPE_NORMAL:
			return TYPE_EXPEDITIONMEMBER;

		}
	}

	return TYPE_PERSONAL;
}

void CSimplePlayerMenuUI::SetCommand( int nCommand )
{
	switch(IsMenuType())
	{
	case TYPE_PERSONAL:
			CmdPersonal(nCommand);
		break;
	case TYPE_PARTYLEADER:
			CmdPartyLeader(nCommand);
		break;
	case TYPE_PARTYMEMBER:
			CmdPartyMember(nCommand);
		break;
	case TYPE_EXPEDITIONLEADER:
			CmdExpeditionLeader(nCommand);
		break;
	case TYPE_EXPEDITIONSUBLEADER:
			CmdExpeditionSubLeader(nCommand);
		break;
	case TYPE_EXPEDITIONMEMBER:
			CmdExpeditionMember(nCommand);
		break;
	}
}

void CSimplePlayerMenuUI::CmdPersonal( int nCmd )
{
	switch((eCmdPersonal)nCmd)
	{
	case eCMD_PERSONAL_CLASS_NAME:
		return;
	case eCMD_PERSONAL_PVP:
		UIMGR()->GetCharacterInfo()->UseAction(23);
		break;
	case eCMD_PERSONAL_AUTO_MATCHING_PARTY:
		UIMGR()->GetCharacterInfo()->UseAction(41);
		break;
	case eCMD_PERSONAL_RAID_INFO:
		_pNetwork->SendRaidInfoReq();
		break;
	case eCMD_PERSONAL_GO_JUNO:
		GoJuno();
		break;
	case eCMD_PERSONAL_CANCEL:
		break;
	}

	ClearAll();
}

void CSimplePlayerMenuUI::CmdPartyLeader( int nCmd )
{
	switch((eCmdPartyLeader)nCmd)
	{
	case eCMD_PARTY_LEADER_CLASS_NAME:
		// Ŭ���� �̸� Ŭ��
		return;
	case eCMD_PARTY_LEADER_END:
		GAMEDATAMGR()->GetPartyInfo()->SendPartyEnd();
		break;
	case eCMD_PARTY_LEADER_QUIT:
		UIMGR()->GetCharacterInfo()->UseAction(9);
		break;
	case eCMD_PARTY_LEADER_TYPE_CHANGE:
		{
			// �Ϲ�, ������
			int nStrIndex[2] = {3354, 2665};
			int nType = GAMEDATAMGR()->GetPartyInfo()->GetPartyType() == PT_PEACEEVER ? 0 : 1 ;
			SetSubMenuList(eCMD_PARTY_LEADER_TYPE_CHANGE, 2, nStrIndex, nType);
			return;
		}
		break;
	case eCMD_PARTY_LEADER_TYPE_ITEM:
		{
			// ����ȹ��, �Լ��켱
			int nStrIndex[2] = {4517, 4518};
			int nType = GAMEDATAMGR()->GetPartyInfo()->GetDivisionType(MSG_DIVITYPE_ITEM) == MSG_EXPED_TYPE_RANDOM ? 0 : 1 ;
			SetSubMenuList(eCMD_PARTY_LEADER_TYPE_ITEM, 2, nStrIndex, nType);
			return;
		}
		break;
	case eCMD_PARTY_LEADER_TYPE_SPECIAL_ITEM:
		{
			// �Լ��켱, ���ڿ���
			int nStrIndex[2] = {4518, 4520};
			int nType = GAMEDATAMGR()->GetPartyInfo()->GetDivisionType(MSG_DIVITYPE_SPECIAL) == MSG_EXPED_TYPE_FIRSTGET ? 0 : 1 ;
			SetSubMenuList(eCMD_PARTY_LEADER_TYPE_SPECIAL_ITEM, 2, nStrIndex, nType);
			return;
		}
		break;
	case eCMD_PARTY_LEADER_MEMBER:
		UIMGR()->GetCharacterInfo()->UseAction(33);
		break;
	case eCMD_PARTY_LEADER_AUTO_MATCHING:
		UIMGR()->GetCharacterInfo()->UseAction(41);
		break;
	case eCMD_PARTY_LEADER_CHANGE_EXPEDITION:
		GAMEDATAMGR()->GetPartyInfo()->SendChangeExpedition();
		break;
	case eCMD_PARTY_LEADER_INFO:
		UIMGR()->GetParty()->OpenDivisionInfoWindow();
		break;
	case eCMD_PARTY_LEADER_GO_JUNO:
		GoJuno();
		break;
	case eCMD_PARTY_LEADER_CANCEL:
		break;
	}

	ClearAll();
}

void CSimplePlayerMenuUI::CmdPartyMember( int nCmd )
{
	switch((eCmdPartyMember)nCmd)
	{
	case eCMD_PARTY_MEMBER_CLASS_NAME:
		// Ŭ���� �̸� Ŭ��
		return;
	case eCMD_PARTY_MEMBER_MEMBER:
		UIMGR()->GetCharacterInfo()->UseAction(33);
		break;
	case eCMD_PARTY_MEMBER_QUIT:
		UIMGR()->GetCharacterInfo()->UseAction(9);
		break;
	case eCMD_PARTY_MEMBER_INFO:
		UIMGR()->GetParty()->OpenDivisionInfoWindow();
		break;
	case eCMD_PARTY_MEMBER_GO_JUNO:
		GoJuno();
		break;
	case eCMD_PARTY_MEMBER_CANCEL:
		break;
	}

	ClearAll();
}

void CSimplePlayerMenuUI::GoJuno()
{
	if (std::count(m_pListStringMenu.begin(), m_pListStringMenu.end(), 8416)) {
		if (_pNetwork->MyCharacterInfo.pk_mode == CHA_PVP_STATE_PK || 
			_pNetwork->MyCharacterInfo.pk_mode == CHA_PVP_STATE_RELEASE ||
			g_slZone == ZONE_START)  //pwesty juno fix
			return;

		_pNetwork->GoZone(0, 0);
	}
}



void CSimplePlayerMenuUI::CmdExpeditionLeader( int nCmd )
{
	switch((eCmdExpeditionLeader)nCmd)
	{
	case eCMD_EX_LEADER_CLASS_NAME:
		return;
	case eCMD_EX_LEADER_TYPE_EXP:
		{
			// �յ�й�, ������
			int nStrIndex[2] = {4525, 4519};
			int nStrCount = 2;

//#ifndef DISABLE_PARTY_TYPE_BATTLE
			extern INDEX g_iCountry;

			if (IsGamigo(g_iCountry) == FALSE)
				nStrCount = 1;
//#endif //DISABLE_PARTY_TYPE_BATTLE

			int nType = GAMEDATAMGR()->GetPartyInfo()->GetDivisionType(MSG_DIVITYPE_EXP) == MSG_EXPED_TYPE_RANDOM ? 0 : 1 ;
			SetSubMenuList(eCMD_EX_LEADER_TYPE_EXP, nStrCount, nStrIndex, nType);
			return;
		}
		break;
	case eCMD_EX_LEADER_TYPE_ITEM:
		{
			// ����ȹ��, �Լ��켱
			int nStrIndex[2] = {4517, 4518};
			int nType = GAMEDATAMGR()->GetPartyInfo()->GetDivisionType(MSG_DIVITYPE_ITEM) == MSG_EXPED_TYPE_RANDOM ? 0 : 1 ;
			SetSubMenuList(eCMD_EX_LEADER_TYPE_ITEM, 2, nStrIndex, nType);
			return;
		}
		break;
	case eCMD_EX_LEADER_TYPE_SPECIAL_ITEM:
		{
			// �Լ��켱, ���ڿ���
			int nStrIndex[2] = {4518, 4520};
			int nType = GAMEDATAMGR()->GetPartyInfo()->GetDivisionType(MSG_DIVITYPE_SPECIAL) == MSG_EXPED_TYPE_FIRSTGET ? 0 : 1 ;
			SetSubMenuList(eCMD_EX_LEADER_TYPE_SPECIAL_ITEM, 2, nStrIndex, nType);
			return;
		}
		break;
	case eCMD_EX_LEADER_MEMBER:
		UIMGR()->GetParty()->OpenExpeditionMemberWindow();
		break;
	case eCMD_EX_LEADER_MANAGER:
		UIMGR()->GetParty()->OpenExpeditionManageWindow();
		break;
	case eCMD_EX_LEADER_END:
		{
			if (m_nMsgBoxID >= 0)
				MSGBOXMGR()->Close(m_nMsgBoxID);

			CmdExpeditionEnd* pCmd = new CmdExpeditionEnd;

			m_nMsgBoxID = MSGBOXMGR()->CreateMsgBox(_S(4493, "������"),
				_S(4611, "�����븦 ��ü�Ͻðڽ��ϱ�?"),
				eMSG_YESNO, true, pCmd, NULL);
		}
		break;
	case eCMD_EX_LEADER_QUIT:
		{
			if (m_nMsgBoxID >= 0)
				MSGBOXMGR()->Close(m_nMsgBoxID);

			CmdExpeditionQuit* pCmd = new CmdExpeditionQuit;

			m_nMsgBoxID = MSGBOXMGR()->CreateMsgBox(_S(4493, "������"),
				_S(4612, "�����븦 Ż���Ͻðڽ��ϱ�?"),
				eMSG_YESNO, true, pCmd, NULL);
		}
		break;
	case eCMD_EX_LEADER_INFO:
		UIMGR()->GetParty()->OpenDivisionInfoWindow();
		break;
	case eCMD_EX_LEADER_COLLECT_ITEM:
		{
			if (m_nMsgBoxID >= 0)
				MSGBOXMGR()->Close(m_nMsgBoxID);

			CmdExpeditionItemCollect* pCmd = new CmdExpeditionItemCollect;

			m_nMsgBoxID = MSGBOXMGR()->CreateMsgBox(_S(4493, "������"),
				_S(4711, "������ ����Ʈ �������� �����Ͻðڽ��ϱ�?"),
				eMSG_YESNO, true, pCmd, NULL);
		}
		break;
	case eCMD_EX_LEADER_GO_JUNO:
		GoJuno();
		break;
	case eCMD_EX_LEADER_CANCEL:
		break;
	}

	ClearAll();
}

void CSimplePlayerMenuUI::CmdExpeditionSubLeader( int nCmd )
{
	switch((eCmdExpeditionSubLeader)nCmd)
	{
	case eCMD_EX_SUB_CLASS_NAME:
		return;
	case eCMD_EX_SUB_MEMBER:
		UIMGR()->GetParty()->OpenExpeditionMemberWindow();
		break;
	case eCMD_EX_SUB_MANAGER:
		UIMGR()->GetParty()->OpenExpeditionManageWindow();
		break;
	case eCMD_EX_SUB_QUIT:
		{
			if (m_nMsgBoxID >= 0)
				MSGBOXMGR()->Close(m_nMsgBoxID);

			CmdExpeditionQuit* pCmd = new CmdExpeditionQuit;

			m_nMsgBoxID = MSGBOXMGR()->CreateMsgBox(_S(4493, "������"),
				_S(4612, "�����븦 Ż���Ͻðڽ��ϱ�?"),
				eMSG_YESNO, true, pCmd, NULL);
		}
		break;
	case eCMD_EX_SUB_INFO:
		UIMGR()->GetParty()->OpenDivisionInfoWindow();
		break;
	case eCMD_EX_SUB_CANCEL:
		break;
	case eCMD_EX_SUB_GO_JUNO:
		GoJuno();
		break;
	}

	ClearAll();
}

void CSimplePlayerMenuUI::CmdExpeditionMember( int nCmd )
{
	switch((eCmdExpeditionMember)nCmd)
	{
	case eCMD_EX_MEMBER_CLASS_NAME:
		// Ŭ���� �̸� Ŭ��
		return;
	case eCMD_EX_MEMBER_MEMBER:
		UIMGR()->GetParty()->OpenExpeditionMemberWindow();
		break;
	case eCMD_EX_MEMBER_QUIT:
		{
			if (m_nMsgBoxID >= 0)
				MSGBOXMGR()->Close(m_nMsgBoxID);

			CmdExpeditionQuit* pCmd = new CmdExpeditionQuit;

			m_nMsgBoxID = MSGBOXMGR()->CreateMsgBox(_S(4493, "������"),
				_S(4612, "�����븦 Ż���Ͻðڽ��ϱ�?"),
				eMSG_YESNO, true, pCmd, NULL);
		}
		break;
	case eCMD_EX_MEMBER_INFO:
		UIMGR()->GetParty()->OpenDivisionInfoWindow();
		break;
	case eCMD_EX_MEMBER_CANCEL:
		Hide(TRUE);
		UIMGR()->RearrangeOrder(UI_SIMPLE_PLAYER_MENU, FALSE);
		break;
	case eCMD_EX_MEMBER_GO_JUNO:
		GoJuno();
		break;
	}

	ClearAll();
}

bool CSimplePlayerMenuUI::IsSubList( int nCmd )
{
	switch(IsMenuType())
	{
	case TYPE_PERSONAL:
		break;
	case TYPE_PARTYLEADER:
		{
			switch(nCmd)
			{
			case eCMD_PARTY_LEADER_TYPE_CHANGE:
				return true;
				break;
			case eCMD_PARTY_LEADER_TYPE_ITEM:
				return true;
				break;
			case eCMD_PARTY_LEADER_TYPE_SPECIAL_ITEM:
				return true;
				break;
			}
		}
		break;
	case TYPE_PARTYMEMBER:
		break;
	case TYPE_EXPEDITIONLEADER:
		{
			switch(nCmd)
			{
			case eCMD_EX_LEADER_TYPE_EXP:
				return true;
				break;
			case eCMD_EX_LEADER_TYPE_ITEM:
				return true;
				break;
			case eCMD_EX_LEADER_TYPE_SPECIAL_ITEM:
				return true;
				break;
			}
		}
		break;
	case TYPE_EXPEDITIONSUBLEADER:
		break;
	case TYPE_EXPEDITIONMEMBER:
		break;
	}

	return false;
}

void CSimplePlayerMenuUI::SetSubCommand( int nMainCmd, int nSubCmd )
{
	Party* pParty = GAMEDATAMGR()->GetPartyInfo();

	switch(IsMenuType())
	{
	case TYPE_PERSONAL:
		break;
	case TYPE_PARTYLEADER:
		{
			switch(nMainCmd)
			{
			case eCMD_PARTY_LEADER_TYPE_CHANGE:
				{
					switch(nSubCmd)
					{
					case eCMD_PARTY_TYPE_NORMAL:
						pParty->SendDivisionType(MSG_DIVITYPE_EXP, MSG_EXPED_TYPE_RANDOM);
						break;
					case eCMD_PARTY_TYPE_BATTLE:
						pParty->SendDivisionType(MSG_DIVITYPE_EXP, MSG_EXPED_TYPE_BATTLE);
						break;
					}
					break;
				}
			case eCMD_PARTY_LEADER_TYPE_ITEM:
				{
					switch(nSubCmd)
					{
					case eCMD_ITEM_TYPE_RANDOM:
						pParty->SendDivisionType(MSG_DIVITYPE_ITEM, MSG_EXPED_TYPE_RANDOM);
						break;
					case eCMD_ITEM_TYPE_FIRSTGET:
						pParty->SendDivisionType(MSG_DIVITYPE_ITEM, MSG_EXPED_TYPE_FIRSTGET);
						break;
					}
					break;
				}
				break;
			case eCMD_PARTY_LEADER_TYPE_SPECIAL_ITEM:
				{
					switch(nSubCmd)
					{
					case eCMD_SITEM_TYPE_FIRST_GET:
						pParty->SendDivisionType(MSG_DIVITYPE_SPECIAL, MSG_EXPED_TYPE_FIRSTGET);
						break;
					case eCMD_SITEM_TYPE_OPEN_BOX:
						pParty->SendDivisionType(MSG_DIVITYPE_SPECIAL, MSG_EXPED_TYPE_OPENBOX);
						break;
					}
					break;
				}
				break;
			}
		}
		break;
	case TYPE_PARTYMEMBER:
		break;
	case TYPE_EXPEDITIONLEADER:
		{
			switch(nMainCmd)
			{
			case eCMD_EX_LEADER_TYPE_EXP:
				{
					switch(nSubCmd)
					{
					case eCMD_EXP_TYPE_EQUAL:
						pParty->SendDivisionType(MSG_DIVITYPE_EXP, MSG_EXPED_TYPE_RANDOM);
						break;
					case eCMD_EXP_TYPE_BATTLE:
						pParty->SendDivisionType(MSG_DIVITYPE_EXP, MSG_EXPED_TYPE_BATTLE);
						break;
					}
					break;
				}
				break;
			case eCMD_EX_LEADER_TYPE_ITEM:
				{
					switch(nSubCmd)
					{
					case eCMD_ITEM_TYPE_RANDOM:
						pParty->SendDivisionType(MSG_DIVITYPE_ITEM, MSG_EXPED_TYPE_RANDOM);
						break;
					case eCMD_ITEM_TYPE_FIRSTGET:
						pParty->SendDivisionType(MSG_DIVITYPE_ITEM, MSG_EXPED_TYPE_FIRSTGET);
						break;
					}
					break;
				}
				break;
			case eCMD_EX_LEADER_TYPE_SPECIAL_ITEM:
				{
					switch(nSubCmd)
					{
					case eCMD_SITEM_TYPE_FIRST_GET:
						pParty->SendDivisionType(MSG_DIVITYPE_SPECIAL, MSG_EXPED_TYPE_FIRSTGET);
						break;
					case eCMD_SITEM_TYPE_OPEN_BOX:
						pParty->SendDivisionType(MSG_DIVITYPE_SPECIAL, MSG_EXPED_TYPE_OPENBOX);
						break;
					}
					break;
				}
				break;
			}
		}
		break;
	case TYPE_EXPEDITIONSUBLEADER:
		break;
	case TYPE_EXPEDITIONMEMBER:
		break;
	}

	ClearAll();
}

void CSimplePlayerMenuUI::ClearAll()
{
	ClearSubMenu();

	Hide(TRUE);
	UIMGR()->RearrangeOrder(UI_SIMPLE_PLAYER_MENU, FALSE);
	m_pImgMouseOver[eMAIN_LIST_OVER]->Hide(TRUE);
}

void CSimplePlayerMenuUI::ClearSubMenu()
{
	if (m_pSubBack == NULL)
		return;

	m_pSubBack->Hide(TRUE);
	m_pImgMouseOver[eSUB_LIST_OVER]->Hide(TRUE);
}

WMSG_RESULT CSimplePlayerMenuUI::OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg )
{
	if (m_bHide == TRUE)
		return WMSG_FAIL;

	if (m_pListMainMenu != NULL && m_pListSubMenu != NULL)
	{
		if (IsSubList(m_pListMainMenu->getMouseOverItem()) == false)
		{
			ClearSubMenu();
		}

		if (IsInside(x, y) == TRUE)
		{
			if (m_pMainBack->GetHide() == FALSE && m_pListMainMenu->IsInside(x, y) == TRUE)
				SetMouseOver(m_pListMainMenu, m_pImgMouseOver[eMAIN_LIST_OVER]);
	
			if (m_pSubBack->GetHide() == FALSE && m_pListSubMenu->IsInside(x, y) == TRUE)
				SetMouseOver(m_pListSubMenu, m_pImgMouseOver[eSUB_LIST_OVER]);
		}
	}

	return WMSG_FAIL;
}

void CSimplePlayerMenuUI::SetMouseOver( CUIList* pList, CUIImage* pImage )
{
	if (pList == NULL || pImage == NULL)
		return;

	CUIListItem* pItem = (CUIListItem*)pList->GetListItem(pList->getMouseOverItem());

	if (pItem != NULL)
	{
		int nPosX = 0;
		int nPosY = 0;
		pItem->GetAbsPos(nPosX, nPosY);

		pImage->SetPos(nPosX - m_nPosX, nPosY - m_nPosY);
		pImage->Hide(FALSE);
	}
}
