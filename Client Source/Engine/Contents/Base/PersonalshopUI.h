// ----------------------------------------------------------------------------
//  File : UIPersonalShop.h
//  Desc : Created by dongmin
// ----------------------------------------------------------------------------

#ifndef	UIPERSONALSHOP_H_
#define	UIPERSONALSHOP_H_
#ifdef	PRAGMA_ONCE
#pragma once
#endif

#include <Engine/Interface/UIEditBox.h>

class CItems;
class CItemData;
class CUIEditBox;
class CUIArray;

// SHOP CONF
#define PS_MAX_SHOPNAME		100				// ���� �̸� �ִ� ���� 100 ����Ʈ
#define PS_MSGCMD_CASH_AMOUNT	1000			// NEW: Cash amount listing message code
#define PS_MSGCMD_CASH_PRICE	1001			// NEW: Cash price per unit message code
#define PS_MAX_NORMAL_ITEM	10				// �Ϲ� ������ �ŷ� �ִ� ��
#define PS_MAX_PACKAGE_ITEM	5				// ��Ű�� �Ǹ� �ŷ� �ִ� ��

// PERSONAL SHOP TYPE
#define PST_NOSHOP			0
#define PST_SELL			(1 << 0)		// �Ǹ�
#define PST_BUY				(1 << 1)		// ����
#define PST_PREMIUM			(1 << 2)		// �����̾�
#define PST_PACKAGE			(1 << 3)		// ��Ű��

// Define item slot
// #define PERSONAL_SHOP_WIDTH					216
// #define PERSONAL_SHOP_HEIGHT				151
// #define PERSONAL_TRADE_HEIGHT				77		// 98

// Column & Row
#define PERSONAL_SHOP_SLOT_COL				5
#define PERSONAL_SHOP_SLOT_ROW				4
#define PERSONAL_SHOP_SLOT_ROW_TOTAL		20
#define	PERSONAL_SHOP_SLOT_MAX				(ITEM_COUNT_IN_INVENTORY_NORMAL + ITEM_COUNT_IN_INVENTORY_CASH_1 + ITEM_COUNT_IN_INVENTORY_CASH_2 + ITEM_COUNT_IN_INVENTORY_CASH_3 + ITEM_COUNT_IN_INVENTORY_CASH_4 + ITEM_COUNT_IN_INVENTORY_CASH_5 + ITEM_COUNT_IN_INVENTORY_CASH_6)
#define PERSONAL_TRADE_SLOT_COL				5
#define	PERSONAL_TRADE_SLOT_TOTAL			20
#define PERSONAL_PACKAGE_SLOT_COL			5
#define PS_CASH_ITEM_ID						999999		// Virtual item ID for cash listings

// ----------------------------------------------------------------------------
// Name : CUIPersonalShop
// Desc :
// ----------------------------------------------------------------------------
class CUIPersonalshopNew : public CUIWindow
{
public:
	enum eSlotType
	{
		SLOT_PACKAGE	= 0,
		SLOT_TRADE		= 1,
		SLOT_SHOP		= 2,
	};

	enum eCMD_TYPE
	{
		CMD_NONE = -1,
		CMD_DBLCLICK = 0,
		CMD_LBUTTONUP,

	};

	CUIPersonalshopNew();
	~CUIPersonalshopNew();

	// Create
	//void	Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight );
	void initialize();
	void	OpenPersonalShop( bool bSellShop );			// ���� ���� ���� ( TRUE -> �Ǹ�, FALSE -> ���� )
	ENGINE_API void	TradePersonalShop( INDEX iChaIndex, FLOAT fX, FLOAT fZ, bool bBuy );				// ���� �������� ������ ���&�ȱ�

	// Adjust position
	void	ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void	AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );

	// Clear
	void	ClearItems();
	void	RefreshPlayerItem();
	void	RefreshUserItem();
	ENGINE_API void	ResetShop(bool bOpen=FALSE);

	bool	IsBuyShop() const { return m_bBuyShop; }
	void	ChangeShopState(bool bShopStart);
	bool	EndBuyShop(int nChaID);
	//void	ToggleVisible();

	// Command functions
	void	MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput );

	// Set focus
	void	SetFocus( bool bVisible );

	// Edit box focus
//	bool	IsEditBoxFocused() { return m_ebPackagePrice.IsFocused() || m_ebShopName.IsFocused(); }
	void	KillFocusEditBox()
	{
//		m_ebPackagePrice.SetFocus( FALSE );
//		m_ebShopName.SetFocus( FALSE );
	}

	// Network Message 
	void	SendPersonalShopStart();
	void	SendPersonalShopStop();
	void	SendPersonalShopBuy();
	void	SendPersonalOpenShop(int iChaIndex);
	void	ReceivePersonalShopItemList(int iChaIndex, CNetworkMessage *istr);
	void	ReceivePersonalShopItemUpdate(CNetworkMessage *istr);

	// �ǸŴ��� ����
	bool	GetCashPersonShop() {return m_bCashPersonShop;}
	void	SetCashPersonShop(bool bPersonShop) { m_bCashPersonShop = bPersonShop;}
	void	SendCashPersonOpenShop(int iChaIndex);
	void	SendCashPersonShopBuy();

	void	AddItemCallback();
	void	DelItemCallback();

	BOOL	IsEditBoxFocused();
	
	void	proc_command(eCMD_TYPE eCmd, eSlotType eSlot);

	void	start_shop();
	
	void	cancel();
	void	buy();

	void	check_premium();
	void	check_offline_mode();		// NEW: Offline mode toggle callback
	void	package_ok();
	void	package_cancel();

protected:
	// Internal functions
	void	RenderShopItems();

	void	TradeToShop( SQUAD llCount, int iSlot );				// Trade -> Shop
	void	ShopToTrade( SQUAD llCount, SQUAD llPrice, int iSlot);	// Shop -> Trade
	void	PackageToShop( bool bAdd );

	void	FindShopSlot( int& nIdx, int iIndex, ULONG ulFlag);
	void	FindShopSlot( int& nIdx, int iVirtualIdx );
	void	FindEmptySlot( int& nIdx );

	__int64	CalculateTotalPrice(int& iCount);
	__int64	CalculateItemPrice(int iShopID, const CItemData &ID, int iNumOfItem, bool bSell);		
	void	PrepareBuyShop();
	void	PrepareSellShop();	

	// NEW: Cash item helpers
	bool	CreateCashItem(SQUAD llAmount, SQUAD llPrice);
	bool	IsCashItem(int iItemIndex) const;
	bool	ValidateCashListing(SQUAD llAmount, SQUAD llPrice);
	SQUAD	GetPlayerCashBalance() const;			// NEW: Retrieve player's current premium cash balance

	// Command functions
	void	AddShopItem( int nIdx, int nUniIndex, SQUAD llCount, int nWhichSlot );
	void	AskQuantity();
	void	DelShopItem( int nTab, int nIdx, int nUniIndex, SQUAD llCount, int nTradeItemID, int nPackageItemID, int nWhichSlot );
	void	BuyItems();	

	void	ClearPackageSlot();

	WMSG_RESULT	LButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);

	void	proc_dblclick(eSlotType type);
	void	proc_lbutton_up(eSlotType type);

private:
	void	clearContainer();
	void	CloseMsg();

	typedef		std::vector< CItems* >		vec_Items;
	typedef		vec_Items::iterator			vec_Items_iter;	

	bool				m_bBuyShop;				// �Ǹ� �����ΰ�? ���� â�ΰ�?
	bool				m_bShopStart;			// �Ǹ� �����ߴ°�?
	BOOL				m_bPremium;				// �����̾� ���� ���.
	SQUAD				m_llPackagePrice;
	bool				m_bPackageBuy;

	int					m_nSelectedChaID;	// Character ID

	__int64				m_nTotalPrice;	
	int					m_nNumOfItem;

	UINT16				ox, oy;

	CTString			m_strShopName;

	vec_Items			m_vectorSellItemList;					// �Ǹ� ��ǰ�� ���.(��Ʈ��ũ���� �޾ƿͼ�...)
	vec_Items			m_vectorSellPackageList;				// �Ǹ� ��Ű�� ��ǰ�� ���.(��Ʈ��ũ���� �޾ƿͼ�...)

	bool				m_bCashPersonShop;						// �ǸŴ��� ����
	bool				m_bCashPersonShop_open;					// �Ǹ� ���� ���� �ŷ���

	bool				m_bTitleClick;

	CUIArray*			m_pArrTrade;
	CUIArray*			m_pArrPackage;
	CUIArray*			m_pArrShop;

	// Items	
	CUIIcon*			m_pIconsTradeItem[PERSONAL_TRADE_SLOT_TOTAL];			// Player Slot items
	CUIIcon*			m_pIconsShopItem[PERSONAL_SHOP_SLOT_MAX];				// Shop Slot items
	CUIIcon*			m_pIconsPackageItem[PERSONAL_PACKAGE_SLOT_COL];			// Package Slot items

	CItems*				m_pTempItems;

	CUICheckButton*		m_pChkPremium;
	CUICheckButton*		m_pChkOfflineMode;		// NEW: Offline mode toggle
	BOOL				m_bOfflineMode;			// NEW: Offline mode flag
	CUIEditBox*			m_pEditPackagePrice;
	CUIButton*			m_pBtnPackOk;
	CUIButton*			m_pBtnPackCancel;

	CUIEditBox*			m_pEditName;

	
	CUIButton*			m_pBtnCancel;
	CUIButton*			m_pBtnBuy;

	CUIButton*			m_pBtnStart;		// �Ǹ� ���� / ����

	CUIText*			m_pTxtNas;
	CUIText*			m_pTxtTotal;
	CUIText*			m_pTxtPackagePrice;
	CUIText*			m_pTxtTitle;

	CUIBase*			m_pGroupSell;
	CUIBase*			m_pGroupBuy;

	CUIImage*			m_pImgUnmove;
	CUIImage*			m_pImgSelect;
};

#endif // UIPERSONALSHOP_H_

