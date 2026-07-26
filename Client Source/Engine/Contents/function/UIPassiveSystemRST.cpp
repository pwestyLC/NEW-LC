#include "StdH.h"

#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIMessenger.h>

#include <Engine/Interface/UIInventory.h>
#include "Info/MyInfo.h"
#include "Contents/Base/UIMsgBoxMgr.h"
#include <Engine/Base/bot.h>
#include <Engine/Help/Util_Help.h>
//#include "RankData.h"
#include "UIPassiveSystemRST.h"

#include <Engine/Help/DefineHelp.h>

#include "Entities/PassiveSystem.h"

#ifdef PASSIVE_SYSTEM
CUIPassiveSystemRST::CUIPassiveSystemRST()
{
	m_bDrag = false;
	m_list = nullptr;
	m_oldSelectedElement = -1;
	m_selectedIcon = -1;
	m_selectedPassiveId = -1;

	m_txt_name = nullptr;
	m_txt_description = nullptr;

	setInherit(false);
}

CUIPassiveSystemRST::~CUIPassiveSystemRST()
{
	m_passiveActiveList.clear();
	m_passiveActiveSlotList.clear();
}

void CUIPassiveSystemRST::initialize()
{
	CTString strName[eBTN_END] = { "use", "close" };

	for (int i = 0; i < eBTN_END; ++i)
		m_pBtn[i] = dynamic_cast<CUIButton*>(findUI("btn_" + strName[i]));

	for (int i = 0; i < SKILL_SLOT_COUNT; ++i)
	{
		CTString str;
		str.PrintF("ico_slot%d", (i + 1));
		m_pSlotIco[i] = dynamic_cast<CUIIcon*>(findUI(str));
		m_pSlotIco[i]->clearIconData();
		m_pSlotIco[i]->SetWhichUI(UI_PASSIVE_SYSTEM_RST);
		m_pSlotIco[i]->SetCommandFUp(boost::bind(&CUIPassiveSystemRST::IconSelectBySlot, this, i));

		auto img = dynamic_cast<CUIImage*>(m_pSlotIco[i]->findUI("img_select"));
		img->Hide(TRUE);
	}

	m_txt_name = dynamic_cast<CUIText*>(findUI("txt_skill_name"));
	m_txt_description = dynamic_cast<CUIText*>(findUI("txt_skill_description"));
	m_txt_option = dynamic_cast<CUIText*>(findUI("txt_skill_option"));

	m_list = dynamic_cast<CUIList*>(findUI("list"));
	m_pDrag = findUI("base_drag");

#ifndef WORLD_EDITOR
	m_pBtn[eBTN_CLOSE]->SetCommandFUp(boost::bind(&CUIPassiveSystemRST::closeUI, this));
	m_pBtn[eBTN_USE]->SetCommandFUp(boost::bind(&CUIPassiveSystemRST::Use, this));
#endif
}

void CUIPassiveSystemRST::openUI()
{
	CUIManager* pUIMgr = CUIManager::getSingleton();

	if (IsVisible() != FALSE)
		return;

	_pNetwork->SendPassiveSystemList();
	_pNetwork->SendPassiveSystemSlotList();

	m_txt_name->SetText(CTString(""));
	m_txt_description->SetText(CTString(""));
	m_txt_option->SetText(CTString(""));

	m_oldSelectedElement = -1;
	m_selectedPassiveId = -1;

	SetVisible(TRUE);
	Hide(FALSE);

	pUIMgr->RearrangeOrder(UI_PASSIVE_SYSTEM_RST, TRUE);
}

void CUIPassiveSystemRST::closeUI()
{
	SetVisible(FALSE);
	Hide(TRUE);

	m_passiveActiveList.clear();
	m_passiveActiveSlotList.clear();

	m_oldSelectedElement = -1;

	ClearIcon();

	CUIManager* pUIMgr = CUIManager::getSingleton();
	pUIMgr->RearrangeOrder(UI_PASSIVE_SYSTEM_RST, FALSE);
}

void CUIPassiveSystemRST::ReceiveMsg(CNetworkMessage* istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;

	switch (ubType)
	{
	case MSG_PASSIVE_SYSTEM_LIST:
	{
		m_passiveActiveList.clear();
		int count, index;
		(*istr) >> count;
		for (int i = 0; i < count; i++)
		{
			(*istr) >> index;
			m_passiveActiveList.push_back(index);
		}

	}break;
	case MSG_PASSIVE_SYSTEM_SLOT_LIST:
	{
		m_passiveActiveSlotList.clear();
		for(int i = 0; i < SKILL_SLOT_COUNT; i++)
		{
			m_passiveActiveSlotList.insert(std::make_pair(i, -1));
		}
		int count, index, slot;
		(*istr) >> count;
		for (int i = 0; i < count; i++)
		{
			(*istr) >> index >> slot;
			if (slot >= SKILL_SLOT_COUNT || slot < 0) continue;

			m_passiveActiveSlotList[slot] = index;
		}
		UpdateSlots();
		UpdateList();
		if (m_oldSelectedElement != -1 && m_selectedPassiveId != -1)
		{
			const bool slotFound = GetPassiveActiveSlotByPassiveId(m_selectedPassiveId) != -1 ? true : false;
			m_pBtn[eBTN_USE]->SetText(slotFound ? CTString("Unequip") : CTString("Equip"));
		}
	}break;
	case MSG_PASSIVE_SYSTEM_EQUIP_REP:
	case MSG_PASSIVE_SYSTEM_UNEQUIP_REP:
		_pNetwork->SendPassiveSystemSlotList();
		break;
	case MSG_PASSIVE_SYSTEM_LEARN:
		_pNetwork->SendPassiveSystemList();
		break;
	}
}

void CUIPassiveSystemRST::ToogleVisible()
{
	if (IsVisible())
		closeUI();
	else
		openUI();
}

void CUIPassiveSystemRST::ClearIcon()
{
	for (int i = 0; i < SKILL_SLOT_COUNT; ++i)
	{
		if (m_pSlotIco[i] != nullptr)
		{
			m_pSlotIco[i]->clearIconData();
		}
	}

	if (m_selectedIcon != -1)
	{
		auto img = dynamic_cast<CUIImage*>(m_pSlotIco[m_selectedIcon]->findUI("img_select"));
		img->Hide(TRUE);
	}

	m_selectedIcon = -1;
}


void CUIPassiveSystemRST::Use()
{
	if (m_selectedPassiveId == -1 || m_list == nullptr) return;

	const bool foundInActiveList = std::find(m_passiveActiveList.begin(), m_passiveActiveList.end(), m_selectedPassiveId) != m_passiveActiveList.end();
	const int foundInActiveSlotList = GetPassiveActiveSlotByPassiveId(m_selectedPassiveId);

	if (!foundInActiveList) return;

	if (foundInActiveSlotList >= 0)
		_pNetwork->SendPassiveSystemUnequip(m_selectedPassiveId);
	else
		_pNetwork->SendPassiveSystemEquip(m_selectedPassiveId, m_selectedIcon);
}

void CUIPassiveSystemRST::UpdateList()
{
	if (m_list == nullptr)
	{
		return;
	}

	m_list->DeleteAllListItem();

	auto passiveItems = CPassiveSystem::m_vecPassive;
	for (auto i = 0; i < passiveItems.size(); i++)
	{
		if (std::find(m_passiveActiveList.begin(), m_passiveActiveList.end(), passiveItems[i].index) != m_passiveActiveList.end())
		{
			AddItemToList(CTString(passiveItems[i].name.c_str()), DEF_UI_FONT_COLOR, i, passiveItems[i], false);

		}
		else
		{
			AddItemToList(CTString(passiveItems[i].name.c_str()), DEF_UI_FONT_COLOR, i, passiveItems[i]);
		}
	}

	const int nMaxItem = m_list->getListItemCount();
	m_list->UpdateScroll(nMaxItem);
	m_list->UpdateList();
}

void CUIPassiveSystemRST::UpdateSlots()
{
	ClearIcon();
	auto it = m_passiveActiveSlotList.begin();
	auto end = m_passiveActiveSlotList.end();

	for (; it != end; ++it)
	{
		if (it->second == -1) continue;
		auto passive = CPassiveSystem::GetPassiveById(it->second);
		m_pSlotIco[it->first]->setInfo(UBET_PASSIVE, 0, passive.IcoRow, passive.IcoCol);
	}
}

void CUIPassiveSystemRST::AddItemToList(CTString str, COLOR col, int elementId, stPassiveSystem& passive, bool disable)
{
	CUIListItem* ptemp = m_list->GetListItemTemplate();
	const auto pItem = ptemp->Clone();

	const auto pTxt = dynamic_cast<CUIText*>(pItem->findUI("txt_skill_name"));
	pTxt->SetText(str);

	const auto txt = dynamic_cast<CUIText*>(pItem->findUI("txt_description"));

	if (disable)
	{
		const auto pImg = dynamic_cast<CUIImage*>(pItem->findUI("img_block"));
		pImg->Hide(FALSE);
		txt->SetText(CTString("Not owned"));
	}
	else
	{
		auto slot = GetPassiveActiveSlotByPassiveId(passive.index);
		if(slot != -1)
			txt->SetText(CTString("Equipped"));
		else
			txt->SetText(CTString(""));
	}

	auto img = dynamic_cast<CUIImage*>(pItem->findUI("img_select"));
	if(m_oldSelectedElement == elementId)
		img->Hide(FALSE);
	else
		img->Hide(TRUE);

	auto ico = dynamic_cast<CUIIcon*>(pItem->findUI("ico_skill"));
	ico->setInfo(UBET_PASSIVE, 0, passive.IcoRow, passive.IcoCol);

	pItem->SetCommandFOnEnter(boost::bind(&CUIPassiveSystemRST::ChangeListMouseColor, this, elementId, true));
	pItem->SetCommandFOnLeave(boost::bind(&CUIPassiveSystemRST::ChangeListMouseColor, this, elementId, false));
	pItem->SetCommandFUp(boost::bind(&CUIPassiveSystemRST::ChangeListMouseClick, this, elementId, passive.index, disable));

	std::string passiveIdStr = std::to_string(passive.index);
	pItem->setPID(passiveIdStr.c_str());

	m_list->AddListItem(pItem);
}

CUIBase* CUIPassiveSystemRST::GetListItemById(int idx) const
{
	const int nCount = m_list->GetItemCount();

	if (nCount <= 0)
		return nullptr;

	CUIBase* pFind = m_list->GetListItem(idx);

	if (pFind != nullptr)
		return pFind;

	return nullptr;
}

int CUIPassiveSystemRST::GetListIdPassiveId(int passiveId) const
{
	const int nCount = m_list->GetItemCount();

	if (nCount <= 0)
		return -1;

	std::string passiveIdStr = std::to_string(passiveId);

	for (int i = 0; i < nCount; i++)
	{
		CUIBase* pFind = m_list->GetListItem(i);

		if (pFind == nullptr)
			continue;;

		if (strcmp(pFind->getPID(), passiveIdStr.c_str()) == 0)
		{
			return i;
		}
	}

	return -1;
}

void CUIPassiveSystemRST::ChangeListMouseColor(int idxElement, bool isEnter)
{
	if (idxElement == m_oldSelectedElement)
		return;

	auto item = GetListItemById(idxElement);

	if (item == nullptr)
		return;

	auto pTxt = dynamic_cast<CUIText*>(item->findUI("txt_skill_name"));
	if (isEnter)
		pTxt->setFontColor(DEF_UI_COLOR_YELLOW);
	else
		pTxt->setFontColor(DEF_UI_FONT_COLOR);
}

void CUIPassiveSystemRST::ChangeListMouseClick(int idxElement, int passiveId, bool isBlock)
{
	if (idxElement == m_oldSelectedElement)
		return;

	auto item = GetListItemById(idxElement);

	if (item == nullptr)
		return;

	m_oldSelectedElement = idxElement;

	ResetSelectedItems();

	auto pTxt = dynamic_cast<CUIText*>(item->findUI("txt_skill_name"));
	pTxt->setFontColor(DEF_UI_COLOR_RED);

	auto img = dynamic_cast<CUIImage*>(item->findUI("img_select"));
	img->Hide(FALSE);

	m_selectedPassiveId = passiveId;
	auto passive = CPassiveSystem::GetPassiveById(passiveId);

	m_txt_name->SetText(CTString(passive.name.c_str()));
	m_txt_description->SetText(CTString(passive.description.c_str()));

	auto strOption = UTIL_HELP()->GetOptionPaciveInfo(passive.OptionId, passive.OptionLevel + 1);
	m_txt_option->SetText(strOption);

	const bool slotFound = GetPassiveActiveSlotByPassiveId(passiveId) != -1 ? true : false;

	m_pBtn[eBTN_USE]->SetText(slotFound ? CTString("Unequip") : CTString("Equip"));
	m_pBtn[eBTN_USE]->SetEnable(isBlock ? FALSE : TRUE);

	IconSelectByPassiveId(passiveId);
}

void CUIPassiveSystemRST::ResetSelectedItems()
{
	for (int i = 0; i < m_list->GetItemCount(); i++)
	{
		if (i == m_oldSelectedElement)
			continue;

		auto item = GetListItemById(i);
		if (item == nullptr)
			continue;

		auto pTxt = dynamic_cast<CUIText*>(item->findUI("txt_skill_name"));
		pTxt->setFontColor(DEF_UI_FONT_COLOR);

		auto img = dynamic_cast<CUIImage*>(item->findUI("img_select"));
		img->Hide(TRUE);
	}
}

void CUIPassiveSystemRST::IconSelectByPassiveId(int passiveId)
{
	if (m_selectedIcon != -1)
	{
		int selectedPassiveIco = m_passiveActiveSlotList.find(m_selectedIcon)->second;
		if (passiveId == selectedPassiveIco || selectedPassiveIco == -1) return;

		auto img = m_pSlotIco[m_selectedIcon]->findUI("img_select");
		img->Hide(TRUE);
	}

	auto it = m_passiveActiveSlotList.begin();
	auto end = m_passiveActiveSlotList.end();

	for (; it != end; ++it)
	{
		if(it->second != passiveId) continue;

		auto img = m_pSlotIco[it->first]->findUI("img_select");
		img->Hide(FALSE);
		m_selectedIcon = it->first;

		return;
	}

	m_selectedIcon = -1;
}

void CUIPassiveSystemRST::IconSelectBySlot(int slot)
{
	if (slot == -1 ||
		(m_selectedIcon != -1 && slot == m_selectedIcon) ||
		(slot + 1) > SKILL_SLOT_COUNT)
	{
		return;
	}

	if (m_selectedIcon != -1)
	{
		auto img = dynamic_cast<CUIImage*>(m_pSlotIco[m_selectedIcon]->findUI("img_select"));
		img->Hide(TRUE);
	}

	auto img = dynamic_cast<CUIImage*>(m_pSlotIco[slot]->findUI("img_select"));
	img->Hide(FALSE);

	m_selectedIcon = slot;

	auto passiveId = GetPassiveActiveIdBySlot(slot);
	if (passiveId == -1 || m_selectedPassiveId == passiveId) return;

	auto listItemId = GetListIdPassiveId(passiveId);
	ChangeListMouseClick(listItemId, passiveId);
}

int CUIPassiveSystemRST::GetPassiveActiveSlotByPassiveId(int passiveId)
{
	auto it = m_passiveActiveSlotList.begin();
	auto end = m_passiveActiveSlotList.end();

	for(; it != end; ++it)
	{
		if (it->second == passiveId)
			return it->first;
	}

	return -1;
}

int CUIPassiveSystemRST::GetPassiveActiveIdBySlot(int slot) const
{
	return m_passiveActiveSlotList.find(slot)->second;
}

WMSG_RESULT CUIPassiveSystemRST::OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg)
{
	int ndXx = x - m_nOldX;
	int ndYy = y - m_nOldY;

	if (m_bHide)
		return WMSG_FAIL;

	if (m_bDrag)
	{
		m_nOldX = x; m_nOldY = y;
		Move(ndXx, ndYy);

		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	CUIManager::getSingleton()->SetMouseCursorInsideUIs();

	return WMSG_FAIL;
}

WMSG_RESULT CUIPassiveSystemRST::OnLButtonDown(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	m_nOldX = x;
	m_nOldY = y;

	CUIManager::getSingleton()->RearrangeOrder(UI_PASSIVE_SYSTEM_RST, TRUE);

	if (m_pDrag->IsInside(x, y) == TRUE)
	{
		m_bDrag = true;
		return WMSG_SUCCESS;
	}

	return WMSG_FAIL;
}

WMSG_RESULT CUIPassiveSystemRST::OnLButtonUp(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	return WMSG_FAIL;
}
#endif