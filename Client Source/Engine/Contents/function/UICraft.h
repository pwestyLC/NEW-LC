#ifndef __CRAFT_UI_H__
#define __CRAFT_UI_H__

class CUIList;
class CUIImage;
class CUIText;
class CUIButton;
class CUIBase;
class CUITree;
class CUITreeItem;

class CUICraft : public CUIWindow
{
public:
	CUICraft();
	~CUICraft();

	void initialize();

	void openUI();
	void closeUI();

	void ToogleVisible();

	void ClearIcon();

	void UpdateCraftList();

	void ReSelectList() { if(m_nOldSubType != -1 && m_nOldIdxElement != -1) ChangeListMouseClick(m_nOldSubType, m_nOldIdxElement, m_selectedCrafIdx,true); }

	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);

	WMSG_RESULT	OnKeyMessage(MSG* pMsg);
	WMSG_RESULT OnCharMessage(MSG* pMsg);
	WMSG_RESULT	OnIMEMessage(MSG* pMsg);

	BOOL IsEditBoxFocused();

private:
	bool m_bDrag;
	int m_nOldX;
	int m_nOldY;

	int m_nOldSubType;
	int m_nOldIdxElement;

	int m_selectedCrafIdx;
	int m_findNeedCraftIdx;
	int m_findCrafIdx; // предмет который может быть скравчен, для поиска его рецепта

	void CreateItem();
	void ChangeCountItem(char pl, bool isButton);

	bool FindCheckName(const char* itemName);
	bool FindCheckListName(const char* itemName);

	CUITree* GetTreeItem(int subType, int idxElement);

	void ChangeListMouseColor(int subType, int idxElement, bool isEnter);
	void ChangeListMouseClick(int subType, int idxElement, int idxCraft, bool isReselect = false);

	void OverrideCheckBox(int subType);
	bool CheckFilter(CItemData* itemDate, stCraft& craft);
	void CleatFilter();

	void InitOption(CItems* item, CItemData* itemDate);
	void InitCombo();

	enum eBTN_PLAYER
	{
		eBTN_CREATE = 0,
		eBTN_CLOSE,
		eBTN_PLUS,
		eBTN_MINUS,
		eBTN_FIND,
		eBTN_CLEAR,
		eBTN_END
	};

	enum eCMB_TYPE
	{
		eCMB_TYPE,
		eCMB_RANK,
		eCMB_CLASS,
		eCMB_END
	};

	enum eEDIT
	{
		eEDIT_FIND,
		eEDIT_COUNT,
		eEDIT_LVL_FROM,
		eEDIT_LVL_TO,
		eEDIT_END
	};

	CUITree*	m_pTree;
	CUITree*	m_pTreeDesign;
	CUIText*	m_pTextPrice;
	CUIText*	m_pTextCount;
	CUIButton*	m_pBtn[eBTN_END];
	CUIText*	m_pTextCountItem[MAX_CRAFT_ITEM_NEED];
	CUIIcon*	m_pIco[MAX_CRAFT_ITEM_NEED];
	CUIIcon*	m_IcoResult;
	CUIBase*	m_pDrag;
	CUIComboBox* m_pComboBox[eCMB_END];
	CUIEditBox*	m_pEdit[eEDIT_END];
};

#endif // __CRAFT_UI_H__