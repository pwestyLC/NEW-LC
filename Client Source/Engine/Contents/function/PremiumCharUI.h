#ifndef __PREMIUM_CHAR_UI_H__
#define __PREMIUM_CHAR_UI_H__

class CUIImage;
class CUIText;
class CUIList;
class CUIScrollBar;
class CUIButton;

class CPremiumCharDesign;

enum ePASSIVE_TYPE
{
	ePASSIVE_EXP_SP_UP = 0, // exp, sp 10% ����
	ePASSIVE_LEVEL_DOWN, // 180�� ���� ��� ��� -3 ���� ���� ����
	ePASSIVE_AUCTION_NO_FEE, // �ŷ����� ������ ����
	ePASSIVE_CASH_INVEN1_USE, // ĳ�� �κ� 1�� ���� ��밡��
	ePASSIVE_EXPRESS_REMOTE_USE, // �ͽ������� �ý��� ���� ��밡��
	ePASSIVE_CHANGE_FACE_PREE_USE, // ���� ���� ������ ���� ��� ����
	ePASSIVE_DURABILITY_REMOTE_USE, // ������ ���� ���� ��� ����
	ePASSIVE_DONT_LOOSE_BUFF_DEAD,
	ePASSIVE_AUTO_PICK_EVENT,
	ePASSIVE_INCREASE_HP
};

class CPremiumCharUI : public CUIWindow
{
public:
	CPremiumCharUI();
	~CPremiumCharUI();

	void OpenUI();
	void CloseUI();

	void initialize();
	void updateUI();
	void updatePassive();
	void updateActive();
	void updateAc_PetRevival();
	void updateAc_Jump();

	void updateExpireTime();

	void PetRemoteRevival();
	void OpenMessenger();

	BOOL	CloseWindowByEsc()	{ CloseUI(); return TRUE; }

	WMSG_RESULT OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg );
	WMSG_RESULT OnLButtonUp( UINT16 x, UINT16 y );
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
private:

	CUIListItem* getPassiveItem(ePASSIVE_TYPE eItem);
	CTString getPassiveItemString(ePASSIVE_TYPE eItem);
	
	bool		m_bDrag;
	int			m_nOriX, m_nOriY;

	CUIImage*	m_pMoveArea;

	enum
	{
		eBTN_CLOSE = 0,
		eBTN_PET_REMOTE,
		eBTN_JUMP,
		eBTN_CANCEL,
		eBTN_MAX
	};

	enum
	{
		eLIST_PASSIVE = 0,
		eLIST_PET_REMOTE,
		eLIST_JUMP,
		eLIST_MAX
	};

	CPremiumCharDesign* m_pDesign;

	CUIButton*	m_pBtn[eBTN_MAX];
	CUIList*	m_pList[eLIST_MAX];

	CUIText*	m_pstrExpire;

	CUIScrollBar* m_plistScroll;
};	
#endif // __PREMIUM_CHAR_UI_H__