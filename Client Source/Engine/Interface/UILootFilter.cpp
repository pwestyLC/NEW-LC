#include "stdh.h"
#include "UILootFilter.h"
#include <Engine/Base/Console.h>

// Global filter variables
INDEX g_iLootFilterEnabled = 1;                // Enabled
unsigned char g_nGradeVisibilityMask = 0x3F;  // All grades visible by default (0x3F = bits 0-5 set: -1, 0, 1, 2, 3, 4)

UILootFilter g_LootFilter;

UILootFilter::UILootFilter()
{
	// Initialize with all 6 grades visible (including normal items)
	g_iLootFilterEnabled = 1;
	// 0x3F = 0b00111111 = all 6 grades (-1, 0-4) visible
}

UILootFilter::~UILootFilter()
{
}

void UILootFilter::Toggle()
{
	g_iLootFilterEnabled = !g_iLootFilterEnabled;
	PrintStatus();
}

void UILootFilter::SetEnabled(bool bEnabled)
{
	g_iLootFilterEnabled = bEnabled ? 1 : 0;
	PrintStatus();
}

void UILootFilter::PrintStatus()
{
	CTString strStatus;

	if (!IsEnabled())
	{
		strStatus.PrintF("Loot Filter: DISABLED - All items visible");
	}
	else
	{
		// Show which grades are visible
		CTString gradesList = "";
		if (g_nGradeVisibilityMask & GRADE_BLUE) gradesList += "Blue ";
		if (g_nGradeVisibilityMask & GRADE_GREEN) gradesList += "Green ";
		if (g_nGradeVisibilityMask & GRADE_YELLOW) gradesList += "Yellow ";
		if (g_nGradeVisibilityMask & GRADE_WHITE_BONUS) gradesList += "White-Bonus ";
		if (g_nGradeVisibilityMask & GRADE_WHITE) gradesList += "White ";

		strStatus.PrintF("Loot Filter: ENABLED - Visible: %s", gradesList);
	}

	// Print to console/chat
	CPrintF("%s\n", strStatus);
}

bool UILootFilter::IsGradeVisible(int itemGrade) const
{
	// Support the 5 rare grades (0-4) from RareOptionEditor + normal items (grade -1)
	// Grade mapping: 
	//   -1 = Normal (White) - can be filtered
	//    0 = Blue
	//    1 = Green
	//    2 = Yellow
	//    3 = White Bonus (Cyan)
	//    4 = White

	// Grades -1 to 4 are filtered by visibility mask
	// -1 uses bit 5 of the mask for normal items
	if (itemGrade >= -1 && itemGrade <= 4)
	{
		// Normal items (-1) use bit 5, rare grades (0-4) use bits 0-4
		int bitIndex = (itemGrade == -1) ? 5 : itemGrade;
		return (g_nGradeVisibilityMask & (1 << bitIndex)) != 0;
	}

	return false;  // Unknown grades are hidden
}

void UILootFilter::SetGradeVisible(int itemGrade, bool bVisible)
{
	// Support the 6 grades (including normal items at -1)
	if (itemGrade < -1 || itemGrade > 4)
		return;  // Invalid grade

	unsigned char bitMask;

	// Normal items (-1) use bit 5, rare grades (0-4) use bits 0-4
	if (itemGrade == -1)
		bitMask = (1 << 5);
	else
		bitMask = (1 << itemGrade);

	if (bVisible)
		g_nGradeVisibilityMask |= bitMask;
	else
		g_nGradeVisibilityMask &= ~bitMask;
}

void UILootFilter::ToggleAllGrades()
{
	// If all 6 are on, turn all off. Otherwise turn all on.
	bool bAllOn = (g_nGradeVisibilityMask == 0x3F);  // 0x3F = all 6 grades visible

	if (bAllOn)
		g_nGradeVisibilityMask = 0x00;  // Turn all off
	else
		g_nGradeVisibilityMask = 0x3F;  // Turn all on (all 6 grades visible)
}

void UILootFilter::CheckHotkeys()
{
	// Hotkey checking disabled - filter is always on for now
}
