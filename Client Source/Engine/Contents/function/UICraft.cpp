#include "StdH.h"

#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIMessenger.h>

#include "UICraft.h"
#include <Engine/Interface/UIInventory.h>
#include "Info/MyInfo.h"
#include "Contents/Base/UIMsgBoxMgr.h"
#include <Engine/Base/bot.h>
#include <Engine/Help/Util_Help.h>
//#include "RankData.h"
#include <Engine/Help/DefineHelp.h>

class CraftComboCommand : public Command
{
public:
	CraftComboCommand() : m_pWnd(NULL) {}
	void setData(CUICraft* pWnd) { m_pWnd = pWnd; }
	void execute()
	{
		if (m_pWnd != NULL)
		{
			m_pWnd->UpdateCraftList();
		}
	}
private:
	CUICraft * m_pWnd;
};

enum eCraft{
	CRAFT_OPEN,
};

CUICraft::CUICraft()
{
	m_bDrag = false;
	m_nOldSubType = -1;
	m_nOldIdxElement = -1;
	m_selectedCrafIdx = -1;
	m_findNeedCraftIdx = -1;
	m_findCrafIdx = -1;

	setInherit(false);
}

CUICraft::~CUICraft()
{

}

void CUICraft::initialize()
{
	CTString strName[eBTN_END] = { "craft", "close","plus","minus", "find", "cancel"};
	CTString strName2[eCMB_END] = { "type", "rank","char" };
	CTString strName3[eEDIT_END] = { "find", "count","levelFrom","levelTo" };

	for (int i = 0; i < eBTN_END; ++i)
		m_pBtn[i] = static_cast<CUIButton*>(findUI("btn_" + strName[i]));
	for (int i = 0; i < eCMB_END; ++i)
		m_pComboBox[i] = static_cast<CUIComboBox*>(findUI("combo_" + strName2[i]));
	for (int i = 0; i < eEDIT_END; ++i)
		m_pEdit[i] = static_cast<CUIEditBox*>(findUI("edit_" + strName3[i]));

	for (int i = 0; i < MAX_CRAFT_ITEM_NEED; ++i)
	{
		CTString str;
		str.PrintF("ico_item%d", (i + 1));
		m_pIco[i] = static_cast<CUIIcon*>(findUI(str));
		m_pIco[i]->clearIconData();
		m_pIco[i]->SetWhichUI(UI_CRAFT);
		str.PrintF("txt_info_item%d", (i + 1));
		m_pTextCountItem[i] = static_cast<CUIText*>(findUI(str));
		m_pTextCountItem[i]->Hide(TRUE);
	}
	m_IcoResult = static_cast<CUIIcon*>(findUI("ico_item"));
	m_IcoResult->clearIconData();
	m_IcoResult->SetWhichUI(UI_CRAFT);
	m_pTextPrice = static_cast<CUIText*>(findUI("txt_info_price"));
	m_pTextCount = static_cast<CUIText*>(findUI("txt_info_count"));
	m_pTree = static_cast<CUITree*>(findUI("tree"));
	m_pTreeDesign = static_cast<CUITree*>(m_pTree->Clone());

	auto scroll = static_cast<CUIScrollBar*>(findUI("scroll_tree"));
	if (scroll != nullptr)
		m_pTree->setScroll(scroll);

	m_pDrag = static_cast<CUIBase*>(findUI("base_drag"));

#ifndef WORLD_EDITOR
	m_pBtn[eBTN_CLOSE]->SetCommandFUp(boost::bind(&CUICraft::closeUI , this));
	m_pBtn[eBTN_CREATE]->SetCommandFUp(boost::bind(&CUICraft::CreateItem, this));
	m_pBtn[eBTN_PLUS]->SetCommandFUp(boost::bind(&CUICraft::ChangeCountItem, this, '+', true));
	m_pBtn[eBTN_MINUS]->SetCommandFUp(boost::bind(&CUICraft::ChangeCountItem, this, '-', true));
	m_pBtn[eBTN_FIND]->SetCommandFUp(boost::bind(&CUICraft::UpdateCraftList, this));
	m_pBtn[eBTN_CLEAR]->SetCommandFUp(boost::bind(&CUICraft::CleatFilter, this));
#endif
	for(auto i = 0; i < eCMB_END; i++)
	{
		auto cmdCombo = new CraftComboCommand();
		cmdCombo->setData(this);
		m_pComboBox[i]->SetCommandUp(cmdCombo);
	}

	//m_bSkipWalk = true;
	m_pEdit[eEDIT_COUNT]->SetOnlyIntegerMode(TRUE);
	m_pEdit[eEDIT_LVL_FROM]->SetOnlyIntegerMode(TRUE);
	m_pEdit[eEDIT_LVL_TO]->SetOnlyIntegerMode(TRUE);
}

void CUICraft::openUI()
{
	CUIManager* pUIMgr = CUIManager::getSingleton();

	if (IsVisible() != FALSE)
		return;

	m_pBtn[eBTN_CREATE]->SetEnable(FALSE);
	m_pTextPrice->SetText(CTString("0"));
	m_pEdit[eEDIT_COUNT]->SetString("1");

	SetVisible(TRUE);
	Hide(FALSE);
	for (auto i = 0; i < eCMB_END; i++)
		m_pComboBox[i]->Hide(FALSE);

	pUIMgr->RearrangeOrder(UI_CRAFT, TRUE);

	InitCombo();
	UpdateCraftList();
}

void CUICraft::closeUI()
{
	SetVisible(FALSE);
	Hide(TRUE);

	ClearIcon();

	m_nOldSubType = -1;
	m_nOldIdxElement = -1;
	m_selectedCrafIdx = -1;
	m_findNeedCraftIdx = -1;
	m_findCrafIdx = -1;

	for(auto i = 0; i < MAX_CRAFT_ITEM_NEED; i++)
		m_pTextCountItem[i]->Hide(TRUE);

	m_pTextPrice->SetText(CTString("0"));
	m_pEdit[eEDIT_FIND]->ClearInputBuffer();
	for(auto i = 0; i < eCMB_END; i++)
		m_pComboBox[i]->Hide(TRUE);

	CUIManager* pUIMgr = CUIManager::getSingleton();
	pUIMgr->RearrangeOrder(UI_CRAFT, FALSE);
}

void CUICraft::ToogleVisible()
{
	if (IsVisible())
		closeUI();
	else
		openUI();
}

void CUICraft::ClearIcon()
{
	for (int i = 0; i < MAX_CRAFT_ITEM_NEED; ++i)
	{
		if (m_pIco[i] != NULL)
		{
			m_pIco[i]->clearIconData();
		}
	}
	if(m_IcoResult != NULL)
	{
		m_IcoResult->clearIconData();
	}
}

void CUICraft::CreateItem()
{
	if (m_selectedCrafIdx == -1)
		return;

	auto craft = CCraft::GetCraftById(m_selectedCrafIdx);

	std::stringstream s(m_pEdit[eEDIT_COUNT]->GetString());
	int count = 1;
	s >> count;

	_pNetwork->SendCraftItem(craft.index, count);
}

void CUICraft::ChangeCountItem(char pl, bool isButton)
{
	if (m_nOldSubType == -1 || m_nOldIdxElement == -1)
		return;

	auto tree = GetTreeItem(m_nOldSubType, m_nOldIdxElement);
	if (tree == nullptr)
		return;
	auto iconList = static_cast<CUIIcon*>(tree->findUI("ico_item"));
	auto craft    = CCraft::GetCraftById(m_selectedCrafIdx);

	std::stringstream s(m_pEdit[eEDIT_COUNT]->GetString());
	int count = 0;
	s >> count;
	CTString txt;
	if (isButton)
	{
		if ((pl == '+' && count == 10000) || (pl == '-' && count == 1))
			return;

		txt.PrintF("%d", pl == '+' ? ++count : --count);
		m_pEdit[eEDIT_COUNT]->SetString(txt.str_String);
	}
	else if(!_pNetwork->GetItemData(craft.itemIdx)->IsFlag(ITEM_FLAG_COUNT))
	{
		count = 1;
		m_pEdit[eEDIT_COUNT]->SetString("1");
	}
	else
	{
		if (count > 10000)
		{
			count = 10000;
			m_pEdit[eEDIT_COUNT]->SetString("10000");
		}
		else if(count <= 0)
		{
			count = 1;
			m_pEdit[eEDIT_COUNT]->SetString("1");
		}
	}

	LONGLONG final_price = craft.price * count;
	txt.PrintF("%lld", pl == '+' ? final_price : final_price);
	UIMGR()->InsertCommaToString(txt);
	m_pTextPrice->SetText(txt);

	// Craft count
	txt.PrintF("x%d", craft.itemCount * count);
	m_pTextCount->SetText(txt);

	// Craft need item
	bool isNeed = false;
	for (auto i = 0; i < MAX_CRAFT_ITEM_NEED; i++)
	{
		if (craft.itemNeed[i] == -1)
			continue;

		int permission = UIMGR()->GetInventory()->GetItemCount(craft.itemNeed[i], false);
		txt.PrintF("%d/%d", permission, craft.countNeed[i] * count);
		m_pTextCountItem[i]->SetText(txt);
		if (permission >= craft.countNeed[i] * count)
		{
			isNeed = true;
			m_pTextCountItem[i]->setFontColor(DEF_UI_COLOR_GREEN);
		}
		else
		{
			isNeed = false;
			m_pTextCountItem[i]->setFontColor(DEF_UI_COLOR_RED);
		}

		m_pTextCountItem[i]->Hide(FALSE);
	}

	if (_pNetwork->MyCharacterInfo.money >= final_price)
		m_pTextPrice->setFontColor(DEF_UI_COLOR_GREEN);
	else
	{
		isNeed = false;
		m_pTextPrice->setFontColor(DEF_UI_COLOR_RED);
	}
	if(isNeed)
		m_pBtn[eBTN_CREATE]->SetEnable(TRUE);
	else
		m_pBtn[eBTN_CREATE]->SetEnable(FALSE);
}

void CUICraft::UpdateCraftList()
{
	if(m_pTree == nullptr)
		return;

	m_pTree->deleteChildAll();
	m_pTree->clearChildList();

	m_pTree->setRoot();

	CUIBase* pGroup = nullptr;
	CUIBase* pChild = nullptr;
	CUIText* pText = nullptr;
	CUIIcon* pIcon = nullptr;

	CTString strName;

	auto tree_group = findUI("tree_group");
	auto tree_child = findUI("tree_child");

	if (tree_group == nullptr || tree_child == nullptr)
		return;

	auto selectedComboIdx = m_pComboBox[eCMB_TYPE]->GetCurSel();

	auto firstCraftIdx = 0;

	// Сбросить поиск по предмету(need)
	if (selectedComboIdx != 1)
	{
		m_findNeedCraftIdx = -1;
		m_findCrafIdx = -1;
	}

	auto groupSubType = CCraft::GetSubTypeByType(m_pComboBox[eCMB_TYPE]->GetVecString().at(selectedComboIdx).str_String);

	for(auto i = 0,ii=0; i < groupSubType.size(); i++)
	{
		// Type init
		auto pGroupTree = static_cast<CUITree*>(m_pTreeDesign->Clone());
		auto subType = groupSubType[i];

		pGroup = tree_group->Clone();

		extern INDEX g_iCountry;
		CTString strLocal = DefHelp::getNationPostfix(g_iCountry, true);

		//if (strLocal == "ru")
		//strName = UtilHelp::getSingleton()->GetCalcStringEllipsis(subType.name, 173, "...");

		//if (strLocal == "us")
			strName = UtilHelp::getSingleton()->GetCalcStringEllipsis(subType.english_name, 173, "...");

		pText = static_cast<CUIText*>(pGroup->findUI("txt_name"));

		pText->SetText(strName);
		pGroup->Hide(FALSE);
		pGroup->SetPos(0, 0);
		bool isAdded = false; // Что бы последовательность элементов при поиске в правильном порядке отображаласт
		// SubType init
		auto subTypeCraft = CCraft::GetCraftBySubType(subType.type, subType.subType);
		for(auto j = 0,jj=0; j < subTypeCraft.size(); j++)
		{
			auto pChildTree = static_cast<CUITree*>(m_pTreeDesign->Clone());
			auto curSub = subTypeCraft[j];

			auto itemDate = CItemData::getData(curSub.itemIdx);

			// Фильтры для поиска
			if(!CheckFilter(itemDate, curSub))
				continue;

			if (!isAdded)
			{
				pGroupTree->addChild(pGroup);
				pGroupTree->InitPos(0, 0, 173, 22);
				isAdded = true;
			}

			pChild = tree_child->Clone();
			pText = static_cast<CUIText*>(pChild->findUI("txt_name"));
			strName = UtilHelp::getSingleton()->GetCalcStringEllipsis(itemDate->GetName(), 145, "...");
			pText->SetText(strName);

			pIcon = static_cast<CUIIcon*>(pChild->findUI("ico_item"));
			pIcon->clearIconData();
			pIcon->setData(UBET_ITEM, itemDate->index);
			InitOption(pIcon->getItems(), itemDate);	// Инициализировать для отображения печати

			pIcon->Hide(TRUE);
			pIcon->SetWhichUI(UI_CRAFT);

			pChild->Hide(FALSE);
			pChild->SetPos(0, 0);
			pChildTree->addChild(pChild);
			pChildTree->InitPos(0, 0, 173, 22);
			pGroupTree->addTree(pChildTree, false);

			// Выбрать первый элемент после прогрузки листа (только в момент пользовательского крафта)
			if(firstCraftIdx == 0)
				firstCraftIdx = curSub.index;
#ifndef WORLD_EDITOR
			pChild->SetCommandFOnEnter(boost::bind(&CUICraft::ChangeListMouseColor, this, ii, jj, true));
			pChild->SetCommandFOnLeave(boost::bind(&CUICraft::ChangeListMouseColor, this, ii, jj, false));
			pChild->SetCommandFUp(boost::bind(&CUICraft::ChangeListMouseClick, this, ii, jj++, curSub.index,false));
#endif // !WORLD_EDITOR
		}
		if (!isAdded)
			continue;
#ifndef WORLD_EDITOR
		pGroupTree->getCheck()->SetCommandF(boost::bind(&CUICraft::OverrideCheckBox, this, ii++));
#endif // !WORLD_EDITOR
		m_pTree->addTree(pGroupTree);
		pGroupTree->updateTree();
	}

	m_nOldSubType = -1;
	m_nOldIdxElement = -1;

	m_pTree->updateTree();
	m_pTree->UpdateScroll();

	if (m_pTree->getChildCount() > 0 && (m_findNeedCraftIdx != -1 || m_findCrafIdx != -1))
	{
		m_pTree->getChildTree(0)->setUncollapse(TRUE);
		OverrideCheckBox(0);
		ChangeListMouseClick(0, 0, firstCraftIdx, true);
	}
}

bool CUICraft::FindCheckName(const char* itemName)
{
	ChatBot m_Bot;

	char str[256] = { 0 }, ListName[256] = { 0 };
	strcpy(str, m_pEdit[eEDIT_FIND]->GetString());

	m_Bot.EditInDownRegister(str);
	m_Bot.DeleteAllSymbol(str);

	int len = strlen(str);

	CTString BufferString = itemName;
	m_Bot.EditInDownRegister(BufferString.str_String);
	m_Bot.DeleteAllSymbol(BufferString.str_String);

	int CountIteration = 0;

	for (int w = 0; w < len; w++)
		for (int k = 0; k < BufferString.Length(); k++)
			if (str[w] == BufferString.str_String[k])
			{
				/*if(FindCheckListName(BufferString))
					continue;*/
				CountIteration++;
				if (len == 1)
					return true;
				for (int t = k + 1; t < BufferString.Length(); t++)
				{
					if (str[w + CountIteration] == BufferString.str_String[t])
					{
						CountIteration++;
						if ((len == CountIteration) || ((w + CountIteration - 1) == len))
							return true;
					}
				}
			}
	return false;
}

bool CUICraft::FindCheckListName(const char* itemName)
{
	return false;
}

CUITree* CUICraft::GetTreeItem(int subType, int idxElement)
{
	int nCount = 0;
	
	nCount = m_pTree->getChildTreeCount();

	if (0 <= nCount && subType >= nCount)
		return nullptr;

	CUITree* pTree2 = m_pTree->getChildTree(subType);

	if (pTree2 == nullptr)
		return nullptr;

	nCount = pTree2->getChildTreeCount();

	if (0 <= nCount && idxElement >= nCount)
		return nullptr;

	CUITree* pFind = pTree2->getChildTree(idxElement);

	if (pFind != nullptr)
		return pFind;
	return nullptr;
}

void CUICraft::ChangeListMouseColor(int subType, int idxElement, bool isEnter)
{
	if (subType == m_nOldSubType && idxElement == m_nOldIdxElement)
		return;

	auto tree = GetTreeItem(subType, idxElement);
	if (tree == nullptr)
		return;

	auto img = static_cast<CUIImage*>(tree->findUI("img_over"));
	if (img == nullptr)
		return;

	if (isEnter)
		img->Hide(FALSE);
	else
		img->Hide(TRUE);
}

void CUICraft::ChangeListMouseClick(int subType, int idxElement, int idxCraft, bool isReselect)
{
	if (subType == m_nOldSubType && idxElement == m_nOldIdxElement && !isReselect)
		return;

	auto tree = GetTreeItem(subType, idxElement);
	if (tree == nullptr)
		return;

	if(auto img = static_cast<CUIImage*>(tree->findUI("img_select")))
		img->Hide(FALSE);
	if (auto img = static_cast<CUIImage*>(tree->findUI("img_over")))
		img->Hide(TRUE);

	auto tree_old = GetTreeItem(m_nOldSubType, m_nOldIdxElement);
	if (tree_old != nullptr)
	{
		if (auto img = static_cast<CUIImage*>(tree_old->findUI("img_select")))
			img->Hide(TRUE);
	}

	m_nOldSubType = subType;
	m_nOldIdxElement = idxElement;

	// Craft result ico
	auto craft = CCraft::GetCraftById(idxCraft);
	m_IcoResult->setData(UBET_ITEM, craft.itemIdx);
	InitOption(m_IcoResult->getItems(), CItemData::getData(craft.itemIdx));

	m_selectedCrafIdx = craft.index;

	// Craft price
	CTString txt;
	txt.PrintF("%d", craft.price);
	UIMGR()->InsertCommaToString(txt);
	m_pTextPrice->SetText(txt);

	// Craft count
	txt.PrintF("x%d", craft.itemCount);
	m_pTextCount->SetText(txt);

	// Config craft flag
	if(!_pNetwork->GetItemData(craft.itemIdx)->IsFlag(ITEM_FLAG_COUNT))
	{
		m_pBtn[eBTN_PLUS]->Hide(TRUE);
		m_pBtn[eBTN_MINUS]->Hide(TRUE);
		m_pEdit[eEDIT_COUNT]->SetString("1");
	}
	else
	{
		m_pBtn[eBTN_PLUS]->Hide(FALSE);
		m_pBtn[eBTN_MINUS]->Hide(FALSE);
	}

	// Craft need item
	bool isNeed = true;
	for(auto i = 0; i < MAX_CRAFT_ITEM_NEED; i++)
	{
		if (craft.itemNeed[i] == -1)
		{
			m_pIco[i]->clearIconData();
			m_pTextCountItem[i]->Hide(TRUE);
			continue;
		}
		m_pIco[i]->setData(UBET_ITEM, craft.itemNeed[i]);

		int permission = UIMGR()->GetInventory()->GetItemCount(craft.itemNeed[i], false);
		txt.PrintF("%d/%d", permission, craft.countNeed[i]);
		m_pTextCountItem[i]->SetText(txt);
		if (permission >= craft.countNeed[i])
		{
			m_pTextCountItem[i]->setFontColor(DEF_UI_COLOR_GREEN);
		}
		else
		{
			isNeed = false;
			m_pTextCountItem[i]->setFontColor(DEF_UI_COLOR_RED);
		}
		m_pTextCountItem[i]->Hide(FALSE);
	}

	if (_pNetwork->MyCharacterInfo.money >= craft.price)
		m_pTextPrice->setFontColor(DEF_UI_COLOR_GREEN);
	else
	{
		isNeed = false;
		m_pTextPrice->setFontColor(DEF_UI_COLOR_RED);
	}
	if (isNeed)
		m_pBtn[eBTN_CREATE]->SetEnable(TRUE);
	else
		m_pBtn[eBTN_CREATE]->SetEnable(FALSE);

	ChangeCountItem('*', false);
}

void CUICraft::OverrideCheckBox(int subType)
{
	auto tree = m_pTree->getChildTree(subType);
	if (tree == nullptr)
		return;

	for(auto i = 0; i < tree->getChildTreeCount(); i++)
	{
		auto treeSub = tree->getChildTree(i);
		auto icon = static_cast<CUIIcon*>(treeSub->findUI("ico_item"));
		if (tree->getCheck()->IsChecked())
			icon->Hide(FALSE);
		else
			icon->Hide(TRUE);
	}
}

bool CUICraft::CheckFilter(CItemData* itemDate, stCraft& craft)
{
	if(m_pComboBox[eCMB_TYPE]->GetCurSel() == 1)
	{
		if (m_findCrafIdx == -1)
		{
			for (auto i = 0; i < MAX_CRAFT_ITEM_NEED; i++)
			{
				if (craft.itemNeed[i] == m_findNeedCraftIdx)
					return true;
			}
		}
		else
		{
			if (craft.itemIdx == m_findCrafIdx)
				return true;
		}
		return false;
	}

	if (CTString(m_pEdit[eEDIT_FIND]->GetString()).Length() > 0 && !FindCheckName(itemDate->GetName()))
		return false;

	if (m_pComboBox[eCMB_CLASS]->GetCurSel() != 0 && (itemDate->GetJob() != (1 << m_pComboBox[eCMB_CLASS]->GetCurSel() - 1)))
	{
		if ((m_pComboBox[eCMB_CLASS]->GetCurSel() - 1 == 4 && itemDate->GetJob() & (1 << m_pComboBox[eCMB_CLASS]->GetCurSel() - 1)) ||
			m_pComboBox[eCMB_CLASS]->GetCurSel() - 1 == 7 && itemDate->GetJob() & (1 << m_pComboBox[eCMB_CLASS]->GetCurSel() - 1) ||
			(m_pComboBox[eCMB_CLASS]->GetCurSel() - 1 == 3 && itemDate->GetJob() & (1 << m_pComboBox[eCMB_CLASS]->GetCurSel() - 1)) ||
			m_pComboBox[eCMB_CLASS]->GetCurSel() - 1 == 8 && itemDate->GetJob() & (1 << m_pComboBox[eCMB_CLASS]->GetCurSel() - 1)) {
			unsigned char bidlocod = 0;
		}
		else
			return false;
	}

	//if (m_pComboBox[eCMB_RANK]->GetCurSel() != 0)
	//{
	//	auto rank = GetRangData();
	//	if (rank != nullptr)
	//	{
	//		auto rank_index = rank->GetRankIndex(itemDate->getindex(), RANK_ITEM);
	//		if (m_pComboBox[eCMB_RANK]->GetCurSel() - 1 != rank_index)
	//			return false;
	//	}
	//}

	if(CTString(m_pEdit[eEDIT_LVL_FROM]->GetString()).Length() > 0  && CTString(m_pEdit[eEDIT_LVL_TO]->GetString()).Length() > 0)
	{
		std::stringstream s(m_pEdit[eEDIT_LVL_FROM]->GetString());
		int from = 0;
		s >> from;

		std::stringstream s2(m_pEdit[eEDIT_LVL_TO]->GetString());
		int to = 0;
		s2 >> to;

		if (itemDate->GetLevel() < from || itemDate->GetLevel() > to)
			return false;
	}
	return true;
}

void CUICraft::CleatFilter()
{
	for (auto i = 0; i < eCMB_END; i++)
		m_pComboBox[i]->SetCurSel(0);

	for (auto i = 0; i < eEDIT_END; i++)
		m_pEdit[i]->ClearInputBuffer();

	UpdateCraftList();
}

void CUICraft::InitOption(CItems * item, CItemData* itemDate)
{
	if (itemDate->GetFlag() & ITEM_FLAG_ORIGIN)
	{
		for (auto opt = 0; opt < MAX_ORIGIN_OPTION; ++opt)
		{
			item->SetOptionData(opt, itemDate->GetOptionOriginType(opt),
				itemDate->GetOptionOriginLevel(opt), 100);
		}

		// ѕЖАМЕЫ ЅєЕі јјЖГ
		for (auto opt = 0; opt < MAX_ITEM_SKILL; ++opt)
		{
			item->SetItemSkill(opt,
				itemDate->GetOptionSkillType(opt), itemDate->GetOptionSkillLevel(opt));
		}
	}
}

void CUICraft::InitCombo()
{
	int countType = CCraft::GetTypeCount();
	if (countType < 0)
		return;

	extern INDEX g_iCountry;
	CTString strLocal = DefHelp::getNationPostfix(g_iCountry, true);

	if (m_pComboBox[eCMB_TYPE]->GetVecString().size() <= 0)
	{
		CTString strName;

		//if (strLocal == "ru")
		//{
		//	m_pComboBox[eCMB_TYPE]->AddString(CTString("Все категории"));
		//	m_pComboBox[eCMB_TYPE]->AddString(CTString("Пользовательский крафт"));
		//}

		//if (strLocal == "us")
		//{
			m_pComboBox[eCMB_TYPE]->AddString(CTString("All categories"));
			m_pComboBox[eCMB_TYPE]->AddString(CTString("Custom craft"));
		//}

		for (auto i = 0; i < countType; i++)
		{
			auto type = CCraft::m_vecCraftType[i];

			//if (strLocal == "ru")
			//strName = UtilHelp::getSingleton()->GetCalcStringEllipsis(type.name, 120, "...");			
			
			//if (strLocal == "us")
			strName = UtilHelp::getSingleton()->GetCalcStringEllipsis(type.english_name, 120, "...");

			m_pComboBox[eCMB_TYPE]->AddString(strName);
		}

		//if (strLocal == "ru")
		//   m_pComboBox[eCMB_CLASS]->AddString(CTString("Все классы"));

		//if (strLocal == "us")
			m_pComboBox[eCMB_CLASS]->AddString(CTString("All classes"));

		for (auto i = 0; i < eJob::TOTAL_JOB - 2; i++)
			m_pComboBox[eCMB_CLASS]->AddString(UtilHelp::getSingleton()->GetClassName((eJob)i));

		//if (strLocal == "ru")
		//m_pComboBox[eCMB_RANK]->AddString(CTString("Все ранги"));	
		
		//if (strLocal == "us")
		m_pComboBox[eCMB_RANK]->AddString(CTString("All ranks"));

		//for (auto i = 0; i < GetRangData()->rank_count; i++) {
		//	    m_pComboBox[eCMB_RANK]->AddString(CTString(GetRangData()->rank[i].name.c_str()));
		}
	}
//}

WMSG_RESULT CUICraft::OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg)
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

WMSG_RESULT CUICraft::OnLButtonDown(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	m_nOldX = x;
	m_nOldY = y;

	CUIManager::getSingleton()->RearrangeOrder(UI_CRAFT, TRUE);

	if (m_pDrag->IsInside(x, y) == TRUE)
	{
		m_bDrag = true;
		return WMSG_SUCCESS;
	}

	return WMSG_FAIL;
}

WMSG_RESULT CUICraft::OnLButtonUp(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	CUIManager* pUIManager = CUIManager::getSingleton();

	if (pUIManager->GetDragIcon() != NULL)
	{
		CUIIcon* pDrag = pUIManager->GetDragIcon();

		CItems* pItems = pDrag->getItems();

		if (pItems == NULL)
			return WMSG_FAIL;

		pUIManager->GetMessenger()->SetDragging(false);

		if (pDrag->getBtnType() == UBET_ITEM)
		{
			if (m_pIco[0]->IsInside(x,y) == TRUE)
			{
				CItemData* pItemData = _pNetwork->GetItemData(pDrag->getIndex());
				auto craft = CCraft::GetFirstCraftItemNeed(pItemData->getindex());
				if (craft.itemIdx != -1)
				{
					m_findNeedCraftIdx = pDrag->getIndex();
					m_pComboBox[eCMB_TYPE]->SetCurSel(1); // Выбрать меню пользовательского крафта
					m_findCrafIdx = -1;

					UpdateCraftList();
				}
				else
				{
					pUIManager->GetChattingUI()->AddSysMessage(_S(666, "Неподходящий предмет."), SYSMSG_ERROR);
					pUIManager->ResetHoldBtn();
					return WMSG_FAIL;
				}
			}
			else if(m_IcoResult->IsInside(x,y) == TRUE)
			{
				auto pItemData = _pNetwork->GetItemData(pDrag->getIndex());
				auto craf = CCraft::GetCraftByItem(pItemData->getindex());
				if(craf.itemIdx != -1)
				{
					m_findCrafIdx = pDrag->getIndex();
					m_pComboBox[eCMB_TYPE]->SetCurSel(1);
					m_findNeedCraftIdx = -1;

					UpdateCraftList();
				}
				else
				{
					pUIManager->GetChattingUI()->AddSysMessage(_S(666, "Неподходящий предмет."), SYSMSG_ERROR);
					pUIManager->ResetHoldBtn();
					return WMSG_FAIL;
				}
			}
		}

		m_pTree->SetScrollPos(0);
		pUIManager->ResetHoldBtn();
		return WMSG_SUCCESS;
	}

	return WMSG_FAIL;
}

WMSG_RESULT CUICraft::OnKeyMessage(MSG * pMsg)
{
	if (m_pEdit == NULL)
		return WMSG_FAIL;

	switch (pMsg->wParam)
	{
		case VK_RETURN:
		{
			if(m_pEdit[eEDIT_FIND]->IsFocused())
				UpdateCraftList();
		}
		case VK_BACK:
		{
			if (m_pEdit[eEDIT_COUNT]->IsFocused() && m_pEdit[eEDIT_COUNT]->OnKeyMessage(pMsg) != WMSG_FAIL)
			{
				ChangeCountItem('*', false);
				return WMSG_SUCCESS;
			}
		}
		break;
	}

	return WMSG_FAIL;
}

WMSG_RESULT CUICraft::OnCharMessage(MSG * pMsg)
{
	if (m_pEdit[eEDIT_COUNT]->IsFocused() && m_pEdit[eEDIT_COUNT]->CharMessage(pMsg) != WMSG_FAIL)
	{
		ChangeCountItem('*', false);
		return WMSG_SUCCESS;
	}
	return WMSG_FAIL;
}

WMSG_RESULT CUICraft::OnIMEMessage(MSG * pMsg)
{
	return WMSG_FAIL;
}

BOOL CUICraft::IsEditBoxFocused()
{
	return m_pEdit[eEDIT_FIND]->IsFocused() || m_pEdit[eEDIT_COUNT]->IsFocused() ||
	  m_pEdit[eEDIT_LVL_FROM]->IsFocused()  || m_pEdit[eEDIT_LVL_TO]->IsFocused();
}
