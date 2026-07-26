// ----------------------------------------------------------------------------
//  File : UIInventory.h
//  Desc : Created by yjpark
// ----------------------------------------------------------------------------

#ifndef	UIINVENTORY_H_
#define	UIINVENTORY_H_
#ifdef	PRAGMA_ONCE
	#pragma once
#endif

#include <Engine/Interface/UIWindow.h>
#include <Engine/Interface/UIScrollBar.h>
#include <Engine/Interface/UIIcon.h>
#include <Engine/Interface/UIEventPopup.h>
#include <Engine/GlobalDefinition.h>
#include <Engine/Help/Util_Help.h>
#include <Engine/Contents/function/EventActiveUI.h>


typedef CUIIcon*	btnAllItems[INVENTORY_TAB_MAX][ITEM_COUNT_IN_INVENTORY_NORMAL];	// Slot items

// Define item type tab
enum ItemTab
{
	ITEM_TAB_NORMAL	= 0,
	ITEM_TAB_CASH1,
	ITEM_TAB_CASH2,
	ITEM_TAB_CASH3,
	ITEM_TAB_CASH4,
	ITEM_TAB_TOTAL,
};

enum InventoryTab
{
	INVEN_TAB_NORMAL0 = 0,
	INVEN_TAB_NORMAL1,
	INVEN_TAB_NORMAL2,
	INVEN_TAB_NORMAL3,
	INVEN_TAB_NORMAL4,
	INVEN_TAB_CASH1,
	INVEN_TAB_CASH2,
	INVEN_TAB_CASH3,
	INVEN_TAB_CASH4,
	//dethunter12 add
	INVEN_TAB_CASH5,
	INVEN_TAB_CASH6,
	//dethunter12 add
	INVEN_TAB_TOTAL,
};

enum eNewItemTex
{
	NEW_EFFECT_ITEM = 0,
	NEW_EFFECT_BAG,
	NEW_EFFECT_BAG_CASH,
	NEW_EFFECT_TOTAL,
};

#define	ITEM_TAB_HEIGHT				58
#define	ITEM_TAB_WIDTH				21
#define	ITEM_TAB_GAP				3

// Define process requesting to lock inventory
enum InvenLockProcess
{
	LOCK_NONE = 0,
	LOCK_UPGRADE_ITEM,
	LOCK_BLOOD_OPTION,
	LOCK_REFINE,
	LOCK_COMPOUND,
	LOCK_GW_MIX,
	LOCK_MIX,
	LOCK_MIXNEW,
	LOCK_MASTERSTONE,
	LOCK_PROCESS,
	LOCK_PRODUCT,
	LOCK_PRODUCT_ITEM,
	LOCK_REMISSION,
	LOCK_EXCHANGE,
	LOCK_SHOP,
	LOCK_CHANGEWEAPON,
	LOCK_PERSONAL_SHOP,
	LOCK_WAREHOUSE,
	LOCK_QUEST,
	LOCK_WARP,
	LOCK_PRESSCORPS,
	LOCK_SOCKETSYSTEM,
	LOCK_SENDMAIL,
	LOCK_REFORMSYSTEM,
	LOCK_GUILDSTASH,
	LOCK_AFFINITY_DONATION,
	LOCK_MYSTERIOUSBEAD,
	LOCK_AUCTION,
	LOCK_PET_STASH,
	LOCK_MESSAGEBTN,
#ifdef DURABILITY
	LOCK_DURABILITY,
#endif	//	DURABILITY
	LOCK_TRADE,
	LOCK_EXP_PET,
	LOCK_PET_TRAINING,
	LOCK_GPS,
	LOCK_ITEMCOLLECTION,
	LOCK_PET_FREE,
	LOCK_ITEM_COMPOSE,
	LOCK_INVEN_ARRANGE,
	LOCK_INVEN_ITEM_DEL,
	LOCK_MAKE_TITLE,
	LOCK_PET_ITEM_UPGRADE,
	LOCK_TRANSMOGRIFY,
	LOCK_BOX_OPEN,
	LOCK_PRS_REMOVE,
	LOCK_SEAL_COMPOSE,
	LOCK_EXTEND_MENU,
	LOCK_MAILBOX_LETTER,
	#ifdef BATTLE_PASS_SYSTEM
	LOCK_BATTLE_PASS,
	#endif
#ifdef PRESTIGE_SYSTEM
	LOCK_PRESTIGE,
#endif
};

// Define max char and line of item informaion 
#define	MAX_ITEMINFO_CHAR			26

// Define text position
#define	INVEN_TITLE_TEXT_OFFSETX	25
#define	INVEN_TITLE_TEXT_OFFSETY	5
#define	ITEMTAB_TEXT_OFFSETY		147
#define	INVEN_MONEY_TEXT_POSX		211
#define	INVEN_MONEY_TEXT_POSY		182
#define	INVEN_WEIGHT_TEXT_POSX		82
#define	LEASE_INFO_TEXT_OFFSETX		180

// Define size of inventory
#define	INVENTORY_WIDTH				256
#define	INVENTORY_HEIGHT			408
#define	INVENTORY_WEIGHT_WIDTH		62

// define Ineventory Type Tab(General/Costume)
#define INVEN_TAB_GENERNAL			0
#define INVEN_TAB_COSTUME			1

// Inventroy Type Tab Size
#define INVENTORY_TYPE_TAP_WIDTH	34
#define INVENTORY_TYPE_TAP_HEIGHT	22

enum eInvenSlot
{
	INVENSLOT_NUM1 = 0,
	INVENSLOT_NUM2,
	INVENSLOT_NUM3,
	INVENSLOT_CASH1,
	INVENSLOT_CASH2,
	INVENSLOT_CASH3,
	INVENSLOT_CASH4,
	INVENSLOT_CASH5,
	INVENSLOT_CASH6,
	INVENSLOT_MAX,
};

enum eERR_MSG
{
	eERR_NONE = 0,
	eERR_NOT_OPEN_CASH_BAG,
	eERR_FLAG_COMPOSITION,
	eERR_MAX
};

// ----------------------------------------------------------------------------
// Name : CUIInventory
// Desc :
// ----------------------------------------------------------------------------

class CUIInventory : public CUIWindow
{
protected:
	struct INVEN_LOCK_ITEMINFO
	{
		SWORD	TargetTab;
		SWORD	TargetInvenIdx;
		SWORD	UseInvenTab;
		SWORD	UseInvenIdx;
		SBYTE	TargetWear_Pos;
		INDEX	TargetItem_Plus;
		INDEX	UseItem_Level;
		SLONG	TartetWearPos;
		SLONG	TartetVirIdx;
		SLONG	UseVirIdx;
	};

	enum IN_LOCK_ITEMINFO_TYPE
	{
		IN_LOCK_REFINE,
		IN_LOCK_OPTION_ADD,
		IN_LOCK_OPTION_DEL,
		IN_LOCK_DIVIDE,
		IN_LOCK_NONE,
	};

	// Controls
	CUIButton			m_btnClose;								// Close button
	BOOL				m_bLockInven;							// If inventory is locked or not
	BOOL				m_bLockArrange;							// If arrange button is locked or not
	bool				m_bLockSelect;							// ������ ���� ����.
	InvenLockProcess	m_eLockInvenProcess;					// Process requesting to lock inventory
	BOOL				m_bShowToolTip;							// If tool tip is shown or not
	BOOL				m_bShowWearSlotToolTip;
	CTString			m_strToolTip;							// String of tool tip
	CTString			m_strWearSlotToolTip;

	// Items
	InventoryTab		m_InvenCurrentTab;						//
	CUIIcon*			m_pIconsWearing[WEAR_TOTAL];				// Wearing items
	// UI����  [10/10/2012 Ranma]	
	btnAllItems			m_abtnItems;
	BOOL				m_bSlot[INVENSLOT_MAX];
	CUIWindow*			m_pInvenSlot[INVENSLOT_MAX];

	// Items info add	
	int					m_nUseTab;
	int					m_InvenIndex;

	// Item information
	int					m_nSelWearItemID;						// Selected weating item
	int					m_nSelSlotItemID[INVEN_TAB_TOTAL];		// Selected slot item
	BOOL				m_bShowItemInfo;						// If item tool tip is shown or not
	BOOL				m_bDetailItemInfo;						// If item informaion is shown in detail or not
	int					m_nCurInfoLines;						// Count of current item information lines
	UIRect				m_rcItemInfo;							// Item information region
	CTString			m_strMyMoney;							// String of current money
	CTString			m_strWeight;							// String of current weight
	CTString			m_strNumItems;							// String of current items count
	COLOR				m_colWeight;							// Color of weight string
	int					m_iItemServerIndex;						// for booster upgrade

	BOOL				m_bRareItem;
	int					m_iRareGrade;

	SLONG				m_slCompositeUniIdx;					// ���յ� �ǻ� ������ Uniidx
	SLONG				m_slCompositePlus;						// ���յ� �ǻ� ������ Plus
	SBYTE				m_sbCompositeRow;						// ���յ� �ǻ� ������ Row
	SBYTE				m_sbCompositeCol;						// ���յ� �ǻ� ������ Col

	// Region of each part
	UIRect				m_rcTitle;								// Region of title
	UIRect				m_rcWearing;							// Region of wearing
	UIRect				m_rcItemTypeTab[2];						// Region of item type tab
	UIRect				m_rcItemSlot;							// Region of item slot0
	UIRect				m_rcToolTip;							// Region of tool tip
	UIRect				m_rcWearSlotToolTip;

	CUIRectSurface		m_NewInvenSurface;
	CUIRectSurface		m_WearInvenSurface;						// ���â ���
	CUIRectSurface		m_NewItemEffectSurface;					// ���� ���� ������ ������ ����Ʈ�� �̹���
	CTextureData		*m_ptdWearBackTexture;					// ���â �ؽ���

	BOOL				m_bNewItem[INVEN_ONE_BAG];
	BOOL				m_bStartEffectItem[INVEN_ONE_BAG];
	int					m_nPlayCount[INVEN_ONE_BAG];

	BOOL				m_bNewItemBag[INVENSLOT_MAX];
	BOOL				m_bStartEffectBag[INVENSLOT_MAX];
	int					m_nBagPlayCount[INVENSLOT_MAX];

	DWORD				m_nEffectTime;		// ������Ʈ�� ���� Ÿ��
	
	CUIButton			m_btnTab[INVEN_TAB_TOTAL];
	CUIButton			m_btnTrashcan;							// ������ ��ư
	CUIButton			m_btnArrange;							// ���� ��ư
	CUIButton			m_btnOptions;
	
	std::vector<CTString>	m_vecItemName;						// [090701: selo] �������� �̸��� �����Ѵ�(�������� �̸��� ������ �Ѿ�� �� ������ �̰��� ����)

	INVEN_LOCK_ITEMINFO	m_InLockItemInfo[IN_LOCK_NONE];

	CTextureData		*m_ptdCostumeTexture;						// �ڽ�Ƭ2 �κ��丮 ��� �ؽ���
	int					m_iInventoryType;							// ���� ���õ� �κ��丮 �� Ÿ�� (General : 0 / Costume : 1)
	CUIIcon*			m_pIconsCostumeWearing[WEAR_COSTUME_TOTAL];	// �ڽ�Ƭ2 Wearing Item Button
	UIRect				m_rcInventoryTab[2];						// �ڽ�Ƭ2 �� ����
	UIRectUV			m_rcCostumeTab;								// �ڽ�Ƭ2 �� UV ����
	CUIButton			m_btnInvenTab[2];							// �ڽ�Ƭ2 �� ��ư
	CUIRectSurface		m_kRSCostumeBackground;

	// [2011/01/18 : Sora] �⼮ �̺�Ʈ
	CUIEventPopUp	m_EventPopUp;

	CUIIcon*			m_pIconCurSelectItem;
	CUIImage*			m_pImgSelect;

protected:
	// Internal functions
	void	RenderItems();
	void	ShowToolTip( BOOL bShow, int nToolTipID = -1 );
	void	ShowWearGuideToolTip( BOOL bShow, eWEAR_TYPE eType = WEAR_TYPE_NONE, int WearPos = -1 );
	void	ShowWearTabToolTip( BOOL bShow, int nToolTipID = -1 );
	void	ShowArrangeToolTip( BOOL bShow );

	// Command functions
	void	UpgradeItem(SLONG nTargetPos, SLONG nTargetVirIndex, SWORD nRefineTab, SWORD nRefineIndex);

	void	OptionAddItem( SBYTE sbWearPos, SLONG slIndex, SWORD nTab, SWORD inven_idx, SLONG VirIdx );
	void	OptionDelItem( SBYTE sbWearPos, SLONG slIndex, SWORD nTab, SWORD inven_idx, SLONG VirIdx );
public:
	// Network message functions ( send )
	void	SendArrangeItem();
	void	SendSwapSlotItems( int nTab0, int inven_idx0, int nTab1, int inven_idx1 );
	void	SendUpgradeItem( INDEX iProtect =-1);
	void	SendItemLvDown();

	void	SendOptionAddItem();
	void	SendOptionDelItem();

	void	SetCashBagExpireTime( int type );
	int		IsCashInvenMoveItem( int inven_tab, int inven_idx = -1, int target_tab = -1, int target_idx = -1);
	void	ErrMessage(int errCode);
	void	CashInvenLockOn();
public:
	CUIInventory();
	~CUIInventory();

	// Create
	void	Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight );

	// Render
	void	Render();
	void	FocusLeave();

	// Adjust position
	void	ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void	ResetSavePosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void	AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );

	// Get row, col of warehouse item
	void	GetLocationOfNormalItem( int nUniIndex, SWORD& nTab, SWORD& inven_idx );

	//Get item info(tab,indenIdx) of DoubleClicked item
	void	GetUseItemSlotInfo(int &nTab, int &inven_idx);
	void	SetUseItemSlotInfo(int nTab, int inven_idx);
	
	// find
	SQUAD	GetItemCount(int iItemIndex, bool bCompositionItem = true);
	SQUAD	GetItemAll();

	// find function. [9/22/2009 rumist]
	BOOL	GetItemSlotInfo( int iItemIndex, int &nTab, int &inven_idx );
	
	// Lock
	void	Lock( BOOL bLock, BOOL bOnlyArrange, InvenLockProcess eWhichProcess )
	{
		if( !bLock && eWhichProcess != LOCK_NONE && m_eLockInvenProcess != eWhichProcess )
			return;

		m_bLockArrange = bLock;
		if( !bOnlyArrange )
			m_bLockInven = bLock;

		bLock ? m_eLockInvenProcess = eWhichProcess : m_eLockInvenProcess = LOCK_NONE;
	}
	BOOL	IsLocked() const { return m_bLockInven; }
	BOOL	IsLockedArrange() const { return m_bLockArrange; }
	bool	IsLockSelect()	{ return m_bLockSelect;	}
	void	SetLockSelect(bool bLock)	{ m_bLockSelect = bLock;	}
	InvenLockProcess getLocked()		{ return m_eLockInvenProcess; }
	void	ShowLockErrorMessage();

	// Toggle visible
	void	ToggleVisible();

	// Messages
	WMSG_RESULT	OnKeyMessage( MSG *pMsg );
	WMSG_RESULT	MouseMessage( MSG *pMsg );

	// Network message functions ( send )
	void	SendUseSlotItem( int nTab, int inven_idx, SBYTE sbWearType = -1 );

	// Network message functions ( receive )
	void	InitInventory( int nTab, int inven_idx, int nUniIndex, int nIndex, int nWearingType );
	void	InitWearBtn(int nIndex, int nUniIdex, int nWearingType);
	void	UpgradeItem( SBYTE sbResult );
	void	UpgradeItem( SBYTE sbResult, SBYTE sbplus );
	void	ClearAllItems( SBYTE sbTab );
	void	OptionAddRep( SBYTE sbResult );
	void	OptionDelRep( SBYTE sbResult );
	
	// Command functions
	void	MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput );
	BOOL	StartSkillDelay( int nIndex );
	BOOL	GetSkillDelay( int nIndex );
	
	LONG	GetItemIndex( int nTab, int inven_idx );
	LONG	GetItemUniIndex( int nTab, int inven_idx );

	// [070824: Su-won] REFINE_PROTECT
	// ������ �õ��� �������� +��ġ�� ����
	SLONG	GetUpgradeItemPlus();

	INDEX	GetMySlotItemsCount(void);

	void	ShowItemDestroyMessage();
	BOOL	FindEmptyabtnItem(int nTab, int &inven_idx);
	
	// [090608: selo] ����Ʈ ������ ������� üũ
	BOOL	IsRestritionItem(int nTab, int inven_idx);
	
	// [091028 sora] ������ ���׷��̵� �߰�
	void	UpgradeCompositedItem(int inven_idx);

	BOOL	IsCostumeInventory()	//���� ���õ� �κ��丮�� �Ϲ� �κ��丮���� �ڽ�Ƭ �κ��丮���� üũ ( return value : TRUE->�ڽ�Ƭ�κ�, FALSE->�Ϲ��κ�)
	{ 
		return (m_iInventoryType == INVEN_TAB_COSTUME);
	}

	void	SetInventoryType(int iType);	// �κ��丮 �� Ÿ�� ���� (General/Costume)
	void	InitCostumeInventory(INDEX iUni_index, INDEX iDB_index, SBYTE sbWear_type);
	
	CUIIcon*		GetItemIcon(int nUniqueIndex);
	CItems*			GetItems(int nUniqueIndex);

	// �������� �κ��丮 �� ���� �ϴ��� �˻�
	BOOL			GetItemVisble( int nUniqueIndex );
	// �κ��丮�� �� ������ �ִ��� �˻�
	BOOL			IsInventoryFull();

	// [2011/01/18 : Sora] �⼮ �̺�Ʈ
	CUIEventPopUp* GetEventPopUp() { return &m_EventPopUp; }

	// get pet info in wearing m_abtnCostumeWearing
	const bool		IsWearing( const eEquipment _wearPos )			{ return m_pIconsWearing[_wearPos]->IsEmpty(); }
	bool			IsWearingItem(int nDBIndex);	// �������� ����ϰ� �ִ��� �˻�
	CUIIcon*		GetWearingBtn( const eEquipment _wearPos )		{ return m_pIconsWearing[_wearPos];				}
	CUIIcon*		GetWearingBtnforSlot( const int _wearPos )		{ return m_pIconsWearing[_wearPos];				}
	CUIIcon*		GetCostumeWearingBtnforSlot( const int _wearPos )		{ return m_pIconsCostumeWearing[_wearPos];				}
	
	//added by sam 11/02/01 
	void InitOneSuitItemInfo ( int nTab, int inven_idx, INDEX iDB_index, INDEX iUni_index, INDEX sbWear_type );

	void SetTabSlotInfo(BOOL bSlot, int nSlotID) { m_bSlot[nSlotID] = bSlot; }
	
	CUIRectSurface* GetInvenSurface() { return &m_NewInvenSurface; }

	int		GetSelWearItemID() { return m_nSelWearItemID; }	
	void	SetSelWearItemID(int nWearID)	{ m_nSelWearItemID = nWearID; }
	void	SetCurSelectItem(CUIIcon* abtn);
	void	UpdateSelectItem();
	CUIIcon*	GetCurSelectItem() { return m_pIconCurSelectItem; }

	void	ShowDivideMsgBox(SWORD nTab, SWORD nInvenIdx);
	bool	IsDivideItem(SWORD nTabS, SWORD nIdxS, SWORD nTabT, SWORD nIdxT);
	
	// ������ ����Ʈ
	void	UpdateNewItemEffect();

	void	ClearNewItemEffect();
	void	ClearNewBagEffect();

	void	SetNewItemBagEffect(BOOL bShowEffect, eInvenSlot eBagPos);
	void	SetNewItemEffect(BOOL bShowEffect, int InvenIdx);

	void	SetStartEffectItem(int InvenIdx);
	void	SetStartEffectBag(eInvenSlot eBagPos);

	BOOL	IsPlayNewItemEffect(int InvenIdx);
	BOOL	IsCheckNewItemEffectPlayCount(int InvenIdx);
	BOOL	IsPlayNewBagEffect(eInvenSlot eBagPos);
	BOOL	IsCheckNewBagEffectPlayCount(eInvenSlot eBagPos);
	void	DivideItemCallback();
	void	SetIconNewItem(int nTab, int idx, bool bOn);

	__int64 GetItemCountByUniIdx( int nUniqueIndex );
	
	// �ε����� �ش��ϴ� ������ �������� ���յ��� ���� �������� �ִ��� �˻�
	bool	IsNotCompositionItem( int nItemDBIdx);
	CEventActiveUI* m_pEventActiveUI;
private:
	int		GetCurTabSlotCount(int tab);	// ĳ�� �κ� �߰��� ���� normal���� ������ 100��, ĳ�ô� 25���� ���

	// ���� â ��� �׸��� (�������� �ٸ��� ���;� ��)
	void	SendSortInventory();

	void	OnUpdate( float fDeltaTime, ULONG ElapsedTime );
};


#endif	// UIINVENTORY_H_

