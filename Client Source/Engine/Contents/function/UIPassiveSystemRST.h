#ifndef __PASSIVE_SYSTEM_RST_UI_H__
#define __PASSIVE_SYSTEM_RST_UI_H__

#define SKILL_SLOT_COUNT 3

struct stPassiveSystem;
class CUIList;
class CUIText;
class CUIButton;
class CUIBase;

class CUIPassiveSystemRST : public CUIWindow
{
public:
	CUIPassiveSystemRST();
	~CUIPassiveSystemRST();

	void initialize();

	void openUI();
	void closeUI();

	void ReceiveMsg(CNetworkMessage* istr);

	void ToogleVisible();

	void ClearIcon();

	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);

private:
	bool m_bDrag;
	int m_nOldX{};
	int m_nOldY{};

	int m_oldSelectedElement;
	int m_selectedPassiveId;

	int m_selectedIcon;

	std::vector<int> m_passiveActiveList;
	std::map<int,int> m_passiveActiveSlotList;

	void Use();

	void UpdateList();
	void UpdateSlots();
	void AddItemToList(CTString str, COLOR col, int elementId, stPassiveSystem& passiveId, bool disable = true);
	CUIBase* GetListItemById(int idx) const;
	int GetListIdPassiveId(int passiveId) const;
	void ChangeListMouseColor(int idxElement, bool isEnter);
	void ChangeListMouseClick(int idxElement, int passiveId, bool isBlock = false);

	void ResetSelectedItems();

	void IconSelectByPassiveId(int passiveId);
	void IconSelectBySlot(int slot);

	int GetPassiveActiveSlotByPassiveId(int passiveId);
	int GetPassiveActiveIdBySlot(int slot) const;

	enum eBTN_PLAYER
	{
		eBTN_USE = 0,
		eBTN_CLOSE,
		eBTN_END
	};

	enum eSLOT
	{
		eSLOT_1 = 1,
		eSLOT_2,
		eSLOT_3
	};

	CUIButton*	m_pBtn[eBTN_END]{};
	CUIList*	m_list;
	CUIText*	m_txt_name{};
	CUIText*	m_txt_description{};
	CUIText*	m_txt_option{};
	CUIText*	m_txt_option_info{};
	CUIIcon*	m_pSlotIco[SKILL_SLOT_COUNT]{};
	CUIBase*	m_pDrag{};
};

#endif // __CRAFT_UI_H__