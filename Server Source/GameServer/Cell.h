#ifndef __ACELL_H__
#define __ACELL_H__

#include "Character.h"

class CCell
{
public:
	bool Send(CNetMsg::SP& msg, CPC* ch = NULL);
	CCell();
	~CCell();

	CCharacter*		m_listChar;		// ¼¿ ¾ÈÀÇ ÄÉ¸¯ÅÍ ¸®½ºÆ® Çì´õ
	CItem*			m_listItem;		// ¼¿ ¾ÈÀÇ ¾ÆÀÌÅÛ ¸®½ºÆ® Çì´õ
	int				m_nCountNPC;	// npc ¼ö
	int				m_nCountPC;		// PC ¼ö
	int				m_nTotalRegen;	// ÇØ´ç ¼¿¿¡¼­ ¸®Á¨µÇ´Â NPC ¼ö

	void CharToCell(CCharacter* ch);
	void CharToCellForSummonNpc(CCharacter* owner, CCharacter* ch);
	void CharFromCell(CCharacter* ch);
	void ItemToCell(CItem* item);
	void ItemFromCell(CItem* item);
};

#endif
//
