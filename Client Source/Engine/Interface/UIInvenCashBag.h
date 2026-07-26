#ifndef __UI_INVEN_CASH_BAG_H__
#define __UI_INVEN_CASH_BAG_H__

#define INVEN_CASH_BAG_W    204
#ifdef EXPANSION_INVENTORY
#define INVEN_CASH_BAG_NEW_H    394
#endif
#define INVEN_CASH_BAG_H    286

#include "UIChildInvenSlot.h"

class CUIInvenCashBag : public CUIChildInvenSlot
{
public :
	CUIInvenCashBag(int _bag_index);

	void Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight );
	void Render();
	void SetInventoryAllItem(btnAllItems* pAllItem, int nTab);
	void SetCashBagExpireTime(int time);
	bool IsInvenCashBagLock()	{ return m_bLock;	}	// ĳ�� �κ��丮�� Ȱ��ȭ �Ǹ� false.

	WMSG_RESULT		MouseMessage( MSG *pMsg );
	void InvenCashBagLockOn()	{ m_bLock = true; }
	void SetPremiumBenefit(bool bUse);
protected:
	void _openUI(const BOOL bType);
	void _closeUI();
	void RenderExpireTime(CDrawPort* pDrawPort);
private:
	enum eLOCK_STATE
	{
		eLOCK_ON,
		eLOCK_OFF,
		eLOCK_MAX
	};
	UIRectUV	m_uvLockArea[eLOCK_MAX];	// ĳ�� �κ��丮 ��� ���� ǥ�� �̹���.
	UIRect		m_rcLockArea;	// ĳ�� �κ��丮 ��� ���� �̹��� ������.
	bool		m_bLock;

	CTString	m_strTime;
	
	int			m_nCashBagType;
	bool		m_bPremiumChar;
};

#endif // __UI_INVEN_CASH_BAG_H__
