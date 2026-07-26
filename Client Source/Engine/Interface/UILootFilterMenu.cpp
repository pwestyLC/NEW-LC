#include "stdh.h"

#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIWindowDeclare.h>
#include "UILootFilterMenu.h"
#include "UILootFilter.h"

CUILootFilterMenu::CUILootFilterMenu()
{
	setInherit(false);

	m_pCheckBtnNormal = NULL;
	m_pCheckBtnBlue = NULL;
	m_pCheckBtnGreen = NULL;
	m_pCheckBtnYellow = NULL;
	m_pCheckBtnWhiteBonus = NULL;
	m_pCheckBtnWhite = NULL;
	m_pBtnToggleAll = NULL;
	m_pBtnClose = NULL;
}

CUILootFilterMenu::~CUILootFilterMenu()
{
}

void CUILootFilterMenu::initialize()
{
	// Find all checkboxes from XML by their IDs
	CTString strTmp;

	// Find normal items checkbox (grade -1)
	strTmp.PrintF("cb_normal");
	m_pCheckBtnNormal = (CUICheckButton*)findUI(strTmp.str_String);

	// Find grade checkboxes (5 rare grades 0-4)
	strTmp.PrintF("cb_blue");
	m_pCheckBtnBlue = (CUICheckButton*)findUI(strTmp.str_String);

	strTmp.PrintF("cb_green");
	m_pCheckBtnGreen = (CUICheckButton*)findUI(strTmp.str_String);

	strTmp.PrintF("cb_yellow");
	m_pCheckBtnYellow = (CUICheckButton*)findUI(strTmp.str_String);

	strTmp.PrintF("cb_white_bonus");
	m_pCheckBtnWhiteBonus = (CUICheckButton*)findUI(strTmp.str_String);

	strTmp.PrintF("cb_white");
	m_pCheckBtnWhite = (CUICheckButton*)findUI(strTmp.str_String);

	// Find buttons
	strTmp.PrintF("btn_toggle_all");
	m_pBtnToggleAll = (CUIButton*)findUI(strTmp.str_String);

	strTmp.PrintF("btn_close");
	m_pBtnClose = (CUIButton*)findUI(strTmp.str_String);

	// Sync checkboxes to current filter state
	UpdateCheckboxesFromFilter();
}

void CUILootFilterMenu::UpdateCheckboxesFromFilter()
{
	// Map the 6 grades to checkboxes (grade -1 + grades 0-4):
	// Grade -1 (Normal/White) = m_pCheckBtnNormal
	// Grade 0 (Blue) = m_pCheckBtnBlue
	// Grade 1 (Green) = m_pCheckBtnGreen
	// Grade 2 (Yellow) = m_pCheckBtnYellow
	// Grade 3 (White Bonus) = m_pCheckBtnWhiteBonus
	// Grade 4 (White) = m_pCheckBtnWhite

	if (m_pCheckBtnNormal)
		m_pCheckBtnNormal->SetCheck(g_LootFilter.IsGradeVisible(-1) ? TRUE : FALSE);
	if (m_pCheckBtnBlue)
		m_pCheckBtnBlue->SetCheck(g_LootFilter.IsGradeVisible(0) ? TRUE : FALSE);
	if (m_pCheckBtnGreen)
		m_pCheckBtnGreen->SetCheck(g_LootFilter.IsGradeVisible(1) ? TRUE : FALSE);
	if (m_pCheckBtnYellow)
		m_pCheckBtnYellow->SetCheck(g_LootFilter.IsGradeVisible(2) ? TRUE : FALSE);
	if (m_pCheckBtnWhiteBonus)
		m_pCheckBtnWhiteBonus->SetCheck(g_LootFilter.IsGradeVisible(3) ? TRUE : FALSE);
	if (m_pCheckBtnWhite)
		m_pCheckBtnWhite->SetCheck(g_LootFilter.IsGradeVisible(4) ? TRUE : FALSE);
}

void CUILootFilterMenu::ToggleVisible()
{
	// Simply toggle the visibility state
	if (GetHide())
	{
		// Currently hidden, show it
		Hide(FALSE);
		UIMGR()->RearrangeOrder(UI_LOOT_FILTER_MENU, TRUE);
		UpdateCheckboxesFromFilter();
	}
	else
	{
		// Currently visible, hide it
		Hide(TRUE);
		UIMGR()->RearrangeOrder(UI_LOOT_FILTER_MENU, FALSE);
	}
}

WMSG_RESULT CUILootFilterMenu::MouseMessage( MSG *pMsg )
{
	// Get mouse position
	int nX = LOWORD( pMsg->lParam );
	int nY = HIWORD( pMsg->lParam );

	// Handle mouse button down
	if( pMsg->message == WM_LBUTTONDOWN )
	{
		// Check each checkbox for the 6 grades (including normal items)
		if (m_pCheckBtnNormal && m_pCheckBtnNormal->IsInside(nX, nY))
		{
			BOOL bChecked = m_pCheckBtnNormal->IsChecked();
			g_LootFilter.SetGradeVisible(-1, !bChecked);
			m_pCheckBtnNormal->SetCheck(!bChecked);
			return WMSG_SUCCESS;
		}
		if (m_pCheckBtnBlue && m_pCheckBtnBlue->IsInside(nX, nY))
		{
			BOOL bChecked = m_pCheckBtnBlue->IsChecked();
			g_LootFilter.SetGradeVisible(0, !bChecked);
			m_pCheckBtnBlue->SetCheck(!bChecked);
			return WMSG_SUCCESS;
		}
		if (m_pCheckBtnGreen && m_pCheckBtnGreen->IsInside(nX, nY))
		{
			BOOL bChecked = m_pCheckBtnGreen->IsChecked();
			g_LootFilter.SetGradeVisible(1, !bChecked);
			m_pCheckBtnGreen->SetCheck(!bChecked);
			return WMSG_SUCCESS;
		}
		if (m_pCheckBtnYellow && m_pCheckBtnYellow->IsInside(nX, nY))
		{
			BOOL bChecked = m_pCheckBtnYellow->IsChecked();
			g_LootFilter.SetGradeVisible(2, !bChecked);
			m_pCheckBtnYellow->SetCheck(!bChecked);
			return WMSG_SUCCESS;
		}
		if (m_pCheckBtnWhiteBonus && m_pCheckBtnWhiteBonus->IsInside(nX, nY))
		{
			BOOL bChecked = m_pCheckBtnWhiteBonus->IsChecked();
			g_LootFilter.SetGradeVisible(3, !bChecked);
			m_pCheckBtnWhiteBonus->SetCheck(!bChecked);
			return WMSG_SUCCESS;
		}
		if (m_pCheckBtnWhite && m_pCheckBtnWhite->IsInside(nX, nY))
		{
			BOOL bChecked = m_pCheckBtnWhite->IsChecked();
			g_LootFilter.SetGradeVisible(4, !bChecked);
			m_pCheckBtnWhite->SetCheck(!bChecked);
			return WMSG_SUCCESS;
		}

		// Handle buttons
		if (m_pBtnToggleAll && m_pBtnToggleAll->IsInside(nX, nY))
		{
			g_LootFilter.ToggleAllGrades();
			UpdateCheckboxesFromFilter();
			return WMSG_SUCCESS;
		}
		if (m_pBtnClose && m_pBtnClose->IsInside(nX, nY))
		{
			ToggleVisible();
			return WMSG_SUCCESS;
		}
	}

	return WMSG_FAIL;
}
