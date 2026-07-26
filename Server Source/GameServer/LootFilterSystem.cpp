#include "stdhdrs.h"
#include "LootFilterSystem.h"

CLootFilter::CLootFilter()
	: m_bEnabled(false)
	, m_rarityThreshold(0)  // Default: show all
{
}

CLootFilter::~CLootFilter()
{
}

bool CLootFilter::IsGradeVisible(int grade) const
{
	if (!m_bEnabled)
		return true;  // Show all if filter is disabled

	int rarity = GetGradeRarity(grade);
	return rarity >= m_rarityThreshold;
}

int CLootFilter::GetGradeRarity(int grade)
{
	switch (grade)
	{
	case eITEM_GRADE_NORMAL:
		return eGRADE_RARITY_COMMON;
	case eITEM_GRADE_RARE_BASIC:
		return eGRADE_RARITY_UNCOMMON;
	case eITEM_GRADE_RARE_MAGIC:
		return eGRADE_RARITY_RARE;
	case eITEM_GRADE_RARE_RARE:
		return eGRADE_RARITY_EPIC;
	case eITEM_GRADE_RARE_UNIQUE:
		return eGRADE_RARITY_LEGENDARY;
	case eITEM_GRADE_RARE_HERO:
		return eGRADE_RARITY_MYTHIC;
	case eITEM_GRADE_ORIGIN:
		return eGRADE_RARITY_SPECIAL;
	case eITEM_GRADE_RARE_NOTOPEN:
		return eGRADE_RARITY_COMMON;  // Treat as common
	default:
		return eGRADE_RARITY_COMMON;
	}
}

const char* CLootFilter::GetGradeName(int grade)
{
	switch (grade)
	{
	case eITEM_GRADE_NORMAL:
		return "White - Basic";
	case eITEM_GRADE_RARE_BASIC:
		return "Yellow - Okay (y3-y4)";
	case eITEM_GRADE_RARE_MAGIC:
		return "Blue (b1-b6)";
	case eITEM_GRADE_RARE_RARE:
		return "Green (g5 BEST)";
	case eITEM_GRADE_RARE_UNIQUE:
		return "Purple - Sets";
	case eITEM_GRADE_RARE_HERO:
		return "AMAZING - Tier";
	case eITEM_GRADE_ORIGIN:
		return "Origin - Gold";
	case eITEM_GRADE_RARE_NOTOPEN:
		return "Boxes";
	default:
		return "Unknown";
	}
}

void CLootFilter::GetGradeColor(int grade, unsigned char& r, unsigned char& g, unsigned char& b)
{
	// Custom rarity color scheme with special highlighting for best items
	// White:  Basic gear
	// Yellow: Okay items (y3-y4)
	// Green:  g4=okay, g5=BEST
	// Blue:   b1-b4=good, b5=AWESOME, b6=AMAZING
	// Purple: Static sets

	switch (grade)
	{
	case eITEM_GRADE_NORMAL:
		// White - Basic gear
		r = 192; g = 192; b = 192;
		break;
	case eITEM_GRADE_RARE_BASIC:
		// Yellow - Okay items (y3-y4 at best)
		r = 255; g = 215; b = 0;
		break;
	case eITEM_GRADE_RARE_MAGIC:
		// Blue - b1-b6 (b5 = AWESOME, b6 = AMAZING)
		// Using bright cyan for excellence
		r = 0; g = 255; b = 255;
		break;
	case eITEM_GRADE_RARE_RARE:
		// Green - g5 is the BEST, g4 is okay
		// Using bright lime for excellence
		r = 0; g = 255; b = 0;
		break;
	case eITEM_GRADE_RARE_UNIQUE:
		// Purple - Static sets
		r = 200; g = 100; b = 255;
		break;
	case eITEM_GRADE_RARE_HERO:
		// AMAZING ITEMS - Use brightest red/orange for maximum visibility
		// This could be for b6 or other legendary tier
		r = 255; g = 69; b = 0;  // Orange-red for AMAZING tier
		break;
	case eITEM_GRADE_ORIGIN:
		// Special tier - Gold for prestige
		r = 255; g = 215; b = 0;
		break;
	case eITEM_GRADE_RARE_NOTOPEN:
		// Not open boxes - Light cyan
		r = 100; g = 200; b = 200;
		break;
	default:
		// Unknown - White
		r = 255; g = 255; b = 255;
		break;
	}
}

//
