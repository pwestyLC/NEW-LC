#ifndef __UI_LOOT_FILTER_H__
#define __UI_LOOT_FILTER_H__

#include <Engine/Interface/UIInternalClasses.h>

// Global filter state - can be toggled in-game
extern INDEX g_iLootFilterEnabled;     // 0 = disabled, 1 = enabled
extern unsigned char g_nGradeVisibilityMask;  // Bitmask for the 5 rare grades (0-4)

// Grade visibility bitmask values (matching RareOptionEditor grades from Util_Help.cpp GetRareItemColor)
// Only these 5 grades are supported: 0=Blue, 1=Green, 2=Yellow, 3=White Bonus, 4=White
#define GRADE_BLUE              (1 << 0)  // Grade 0 - Blue (0x1C54CCFF)
#define GRADE_GREEN             (1 << 1)  // Grade 1 - Green (0x20A51CFF)
#define GRADE_YELLOW            (1 << 2)  // Grade 2 - Yellow (0xE5E230FF)
#define GRADE_WHITE_BONUS       (1 << 3)  // Grade 3 - White Bonus (0xB2FDB7FF)
#define GRADE_WHITE             (1 << 4)  // Grade 4 - White (0x01FDEEFF)

class UILootFilter
{
public:
	UILootFilter();
	~UILootFilter();

	void Toggle();
	void SetEnabled(bool bEnabled);
	void CheckHotkeys();  // Check for Q key to toggle filter

	bool IsEnabled() const { return g_iLootFilterEnabled != 0; }

	// Per-grade visibility checks
	bool IsGradeVisible(int itemGrade) const;
	void SetGradeVisible(int itemGrade, bool bVisible);
	void ToggleAllGrades();

	// Display help text showing current filter status
	void PrintStatus();
};

extern UILootFilter g_LootFilter;

#endif
