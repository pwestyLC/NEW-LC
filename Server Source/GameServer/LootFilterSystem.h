#ifndef __LOOT_FILTER_SYSTEM_H__
#define __LOOT_FILTER_SYSTEM_H__

#include "../ShareLib/Config.h"

// Simple Loot Filter - toggles visibility of low-rarity items
class CLootFilter
{
public:
	CLootFilter();
	~CLootFilter();

	// Filter enabled/disabled
	bool IsEnabled() const { return m_bEnabled; }
	void SetEnabled(bool enabled) { m_bEnabled = enabled; }
	void Toggle() { m_bEnabled = !m_bEnabled; }

	// Check if item grade should be shown (when filter is enabled)
	bool IsGradeVisible(int grade) const;

	// Get grade rarity level
	static int GetGradeRarity(int grade);

	// Get grade name for display
	static const char* GetGradeName(int grade);

	// Get grade color (RGB) for display
	static void GetGradeColor(int grade, unsigned char& r, unsigned char& g, unsigned char& b);

	// Rarity threshold when filter is enabled (0=show all, 1+=hide commons, etc)
	int GetRarityThreshold() const { return m_rarityThreshold; }
	void SetRarityThreshold(int threshold) { m_rarityThreshold = threshold; }

private:
	bool m_bEnabled;			// Is filter enabled?
	int m_rarityThreshold;		// Minimum rarity level to show when filter is on (0=all, 1=uncommon+, etc)
};

// Rarity levels for filtering
enum eGRADE_RARITY
{
	eGRADE_RARITY_COMMON = 0,		// Common - always shown
	eGRADE_RARITY_UNCOMMON,		// Uncommon
	eGRADE_RARITY_RARE,			// Rare
	eGRADE_RARITY_EPIC,			// Epic
	eGRADE_RARITY_LEGENDARY,		// Legendary
	eGRADE_RARITY_MYTHIC,			// Mythic
	eGRADE_RARITY_SPECIAL,			// Special/Origin

	eGRADE_RARITY_MAX
};

#endif // __LOOT_FILTER_SYSTEM_H__
//
