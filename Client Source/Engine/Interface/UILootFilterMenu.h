#ifndef __UI_LOOT_FILTER_MENU_H__
#define __UI_LOOT_FILTER_MENU_H__

class CUILootFilterMenu : public CUIWindow
{
public:
	CUILootFilterMenu();
	~CUILootFilterMenu();

	void initialize();
	void ToggleVisible();
	virtual WMSG_RESULT MouseMessage( MSG *pMsg );

private:
	CUICheckButton* m_pCheckBtnNormal;          // Grade -1 - Normal (White)
	CUICheckButton* m_pCheckBtnBlue;         // Grade 0 - Blue
	CUICheckButton* m_pCheckBtnGreen;        // Grade 1 - Green
	CUICheckButton* m_pCheckBtnYellow;       // Grade 2 - Yellow
	CUICheckButton* m_pCheckBtnWhiteBonus;   // Grade 3 - White Bonus
	CUICheckButton* m_pCheckBtnWhite;        // Grade 4 - White
	CUIButton* m_pBtnToggleAll;
	CUIButton* m_pBtnClose;

	void UpdateCheckboxesFromFilter();
};

#endif
