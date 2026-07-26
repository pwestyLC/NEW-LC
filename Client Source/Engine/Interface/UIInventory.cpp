#include "stdh.h"

#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Interface/UIInventory.h>

#include <Engine/Contents/Base/InvenData.h>

#include <Engine/PetInfo.h>
#include <Engine/Interface/UIPetInfo.h>
#include <Engine/Contents/function/TeleportUI.h>
#include <Engine/Contents/function/InventoryOptions.h>
#include <Engine/Interface/UIQuickSlot.h>
#include <Engine/Contents/function/TatooUI.h>
#include <Engine/Interface/UIChildInvenSlot.h>
#include <Engine/Interface/UIFortune.h>
#include <Engine/Help/ItemHelp.h>
#include <Engine/Contents/Base/UIMysteriousBead.h>
#include <Engine/Interface/UIInvenCashBag.h>
#include <Engine/Interface/UIInvenCashBagBox.h>
#include <Engine/Contents/Base/UISkillNew.h>
#include <Common/Packet/ptype_old_do_item.h>
#include <Engine/Interface/UIRadar.h>
#include <Engine/Contents/function/WildPetInfoUI.h>
#include <Engine/Contents/function/BingoBoxUI.h>
#include <Engine/Interface/UIMix.h>
#include <Engine/Interface/UIReformSystem.h>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Contents/function/UIPortalNew.h>
#include <Engine/Contents/function/CompoundUI.h>
#include <Engine/Contents/function/InsectCollectUI.h>
#include <Engine/Contents/function/WareHouseUI.h>
#include <Engine/Contents/function/GuildWarMixUI.h>
#include <Engine/Interface/UINpcScroll.h>
#include <Engine/Contents/Base/UIChangeWeaponNew.h>
#include <Engine/Interface/UIMinigame.h>
#include <Engine/Interface/UIGuild.h>
#include <Engine/Contents/Base/UIPartyNew.h>
#include <Engine/Contents/Base/Party.h>
#include <Engine/Interface/UICharServerMove.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/function/gps.h>
#include <Engine/Contents/Base/UIMsgBoxNumeric_only.h>
#include <Engine/Info/MyInfo.h>
#include <Engine/Contents/function/attendance.h>
#include <Engine/Contents/function/PremiumChar.h>
#include <Engine/Contents/Base/ChattingUI.h>
#include <Engine/Contents/Base/UIMsgBoxMgr.h>
#include <Engine/Contents/function/TreasureMapUI.h>


extern INDEX g_iXPosInInventory;
extern INDEX g_iYPosInInventory;

tm* g_tv_t = NULL; // �Ⱓ ǥ�ÿ� ���� ������ ����

enum EInvenTex
{
	EInvenBg = 0,
	EInvenNormalSelect,
	EInvenWearSelect,
	EInvenMixing,
	EInvenSealed,
	EInvenLeaseMark,
	EInvenInfoUL,			//////////////////////////////////////////////////////////////////////////
	EInvenInfoUM,			//////////////////////////////////////////////////////////////////////////
	EInvenInfoUR,			//////////////////////////////////////////////////////////////////////////
	EInvenInfoML,			//////////////////////////////////////////////////////////////////////////
	EInvenInfoMM,			//////////////////������ ���� ǥ��////////////////////////////////////////
	EInvenInfoMR,			//////////////////////////////////////////////////////////////////////////
	EInvenInfoBL,			//////////////////////////////////////////////////////////////////////////
	EInvenInfoBM,			//////////////////////////////////////////////////////////////////////////
	EInvenInfoBR,			//////////////////////////////////////////////////////////////////////////
	EInvenSimpleInfoL,
	EInvenSimpleInfoM,
	EInvenSimpleInfoR,
	EInvenTotal,
};

CTextureData* ptdCommonTexture = NULL;

#define DEF_TOOLTIP_XGAP 12
#define DEF_TOOLTIP_YGAP 5

class CmdInvenDivideItem : public Command
{
public:
	CmdInvenDivideItem() : m_pWnd(NULL) {}
	void setData(CUIInventory* pWnd) { m_pWnd = pWnd; }
	void execute()
	{
		if (m_pWnd != NULL)
			m_pWnd->DivideItemCallback();
	}
private:
	CUIInventory* m_pWnd;
};

class CmdItemUseTotem : public Command
{
public:
	CmdItemUseTotem() : m_nTab(-1), m_nInvenIdx(-1) {}
	void setData(int nTab, int nInvenIdx)
	{
		m_nTab = nTab;
		m_nInvenIdx = nInvenIdx;
	}
	void execute()
	{
		_pNetwork->UseSlotItem(m_nTab, m_nInvenIdx);
	}

private:
	int m_nTab;
	int m_nInvenIdx;
};
// ----------------------------------------------------------------------------
// Name : CUIInventory()
// Desc : Constructor
// ----------------------------------------------------------------------------
CUIInventory::CUIInventory()
{
	m_bLockInven = FALSE;
	m_eLockInvenProcess = LOCK_NONE;
	m_nSelWearItemID = -1;

	int i;

	for (i = 0; i < INVEN_TAB_TOTAL; ++i)
	{
		m_nSelSlotItemID[i] = -1;
	}

	m_bShowItemInfo = FALSE;
	m_bDetailItemInfo = FALSE;
	m_nCurInfoLines = 0;
	m_strMyMoney = CTString("0");
	m_strNumItems = CTString("100/100");
	m_bShowToolTip = FALSE;
	m_bShowWearSlotToolTip = FALSE;
	m_strToolTip = CTString("");
	m_strWearSlotToolTip = CTString("");
	m_InvenIndex = 0; // wooss 050926

	m_iRareGrade = -1;
	m_NewInvenSurface.Clear();
	m_NewItemEffectSurface.Clear();
	m_InvenCurrentTab = INVEN_TAB_NORMAL0;

	m_slCompositeUniIdx = -1;
	m_sbCompositeRow = -1;
	m_sbCompositeCol = -1;
	m_slCompositePlus = -1;

	m_iInventoryType = INVEN_TAB_GENERNAL;
	m_ptdCostumeTexture = NULL;

	m_ptdWearBackTexture = NULL;

	// UI���� [10/10/2012 Ranma]
	for (i = 0; i < INVENSLOT_MAX; i++)
	{
		m_bSlot[i] = FALSE;
		m_pInvenSlot[i] = NULL;
	}

	m_nUseTab = 0;
	m_nEffectTime = 0;

	int		t;
	for (t = 0; t < INVENTORY_TAB_MAX; ++t)
	{
		for (i = 0; i < ITEM_COUNT_IN_INVENTORY_NORMAL; ++i)
		{
			m_abtnItems[t][i] = NULL;
		}
	}

	ClearNewItemEffect();
	ClearNewBagEffect();

	m_pIconCurSelectItem = NULL;
	m_pImgSelect = NULL;
	m_bLockSelect = false;
}

// ----------------------------------------------------------------------------
// Name : ~CUIInventory()
// Desc : Destructor
// ----------------------------------------------------------------------------
CUIInventory::~CUIInventory()
{
	Destroy();

	STOCK_RELEASE(ptdCommonTexture);
	STOCK_RELEASE(m_ptdCostumeTexture);
	STOCK_RELEASE(m_ptdWearBackTexture);

	int		t, i;
	for (t = 0; t < INVENTORY_TAB_MAX; ++t)
	{
		for (i = 0; i < ITEM_COUNT_IN_INVENTORY_NORMAL; ++i)
		{
			SAFE_DELETE(m_abtnItems[t][i]);
		}
	}

	for (i = 0; i < WEAR_TOTAL; ++i)
		SAFE_DELETE(m_pIconsWearing[i]);

	for (i = 0; i < WEAR_COSTUME_TOTAL; ++i)
		SAFE_DELETE(m_pIconsCostumeWearing[i]);

	SAFE_DELETE(m_pImgSelect);
}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::Create(CUIWindow* pParentWnd, int nX, int nY, int nWidth, int nHeight)
{
	CUIWindow::Create(pParentWnd, nX, nY, nWidth, nHeight);

	// Ÿ��Ʋ�� ����
	m_rcTitle.SetRect(15, 0, nWidth - 30, 32);

	m_rcWearing.SetRect( 35, 45, 240, 183 );// newslot - alanssoares
	m_rcItemTypeTab[0].SetRect( 11, 214, 32, 361 );
	m_rcItemTypeTab[1].SetRect( 223, 214, 244, 361 );
	m_rcItemSlot.SetRect( 33, 214, 222, 400 );

	// Create inventory texture
	m_ptdBaseTexture = CreateTexture(CTString("Data\\Interface\\NewInventory.tex"));
	FLOAT	fTexWidth = m_ptdBaseTexture->GetPixWidth();
	FLOAT	fTexHeight = m_ptdBaseTexture->GetPixHeight();

	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 255, 407), UIRectUV(0, 0, 255, 407, fTexWidth, fTexHeight)); // ���
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(3, 441, 36, 474, fTexWidth, fTexHeight)); // �κ� ������ ���� �����̹���
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(41, 441, 74, 474, fTexWidth, fTexHeight)); // �κ� ��� ���� �����̹���
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(79, 441, 112, 474, fTexWidth, fTexHeight)); // �κ� ���� ���� ��ư �̹���
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(117, 441, 150, 474, fTexWidth, fTexHeight)); // �κ� ���� ���� ��ư �̹���
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(173, 421, 184, 432, fTexWidth, fTexHeight)); // �κ� �뿩 ��ũ �̹���

	m_NewItemEffectSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(157, 441, 191, 475, fTexWidth, fTexHeight)); // ���� ������ ������ ������ �����̹���


	// ������
	m_btnTrashcan.Create(this, _s(" "), 236, 193, 15, 19);
	m_btnTrashcan.SetNewType(TRUE);
	m_btnTrashcan.SetRTSurface(UBS_IDLE, UIRect(0, 0, 15, 19), UIRectUV(3, 413, 17, 431, fTexWidth, fTexHeight));
	m_btnTrashcan.SetRTSurface(UBS_CLICK, UIRect(0, 0, 15, 19), UIRectUV(21, 413, 35, 431, fTexWidth, fTexHeight));
	m_btnTrashcan.CopyRTSurface(UBS_IDLE, UBS_ON);
	m_btnTrashcan.CopyRTSurface(UBS_IDLE, UBS_DISABLE);

	// ���â ��� ����
	m_ptdWearBackTexture = CreateTexture(CTString("Data\\Interface\\NewInventory.tex"));
	fTexWidth = m_ptdWearBackTexture->GetPixWidth();
	fTexHeight = m_ptdWearBackTexture->GetPixHeight();

	// newslot - alanssoares
	m_WearInvenSurface.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(257, 0, 503, 155, fTexWidth, fTexHeight));
	m_WearInvenSurface.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(504, 0, 750, 155, fTexWidth, fTexHeight));
	m_WearInvenSurface.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(751, 0, 997, 155, fTexWidth, fTexHeight));
	m_WearInvenSurface.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(257, 156, 503, 311, fTexWidth, fTexHeight));
	m_WearInvenSurface.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(504, 156, 750, 311, fTexWidth, fTexHeight));
	m_WearInvenSurface.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(751, 156, 997, 311, fTexWidth, fTexHeight));
	m_WearInvenSurface.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(257, 312, 503, 467, fTexWidth, fTexHeight));
#ifdef CHAR_EX_ROGUE
	m_WearInvenSurface.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(504, 156, 750, 311, fTexWidth, fTexHeight));
#endif
#ifdef CHAR_EX_MAGE
	m_WearInvenSurface.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(257, 156, 503, 311, fTexWidth, fTexHeight));
#endif

	ptdCommonTexture = CreateTexture(CTString("Data\\Interface\\CommonBtn.tex"));
	fTexWidth = ptdCommonTexture->GetPixWidth();
	fTexHeight = ptdCommonTexture->GetPixHeight();

	m_NewItemEffectSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(466, 23, 479, 36, fTexWidth, fTexHeight)); // ���� ������ �������� ����ִ� ������ ������ �����̹���
	m_NewItemEffectSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(199, 83, 213, 97, fTexWidth, fTexHeight)); // ���� ������ �������� ����ִ� ������ ������ �����̹���(�ɽ��κ�)

	m_btnTab[INVEN_TAB_NORMAL0].Create(this, _s(" "), 11, 214, 22, 34);
	m_btnTab[INVEN_TAB_NORMAL1].Create(this, _s(" "), 11, 252, 22, 34);
	m_btnTab[INVEN_TAB_NORMAL2].Create(this, _s(" "), 11, 290, 22, 34);
	m_btnTab[INVEN_TAB_NORMAL3].Create(this, _s(" "), 11, 328, 22, 34);
	m_btnTab[INVEN_TAB_NORMAL4].Create(this, _s(" "), 11, 336, 22, 34); // ���� ��� ����

	UIRect top = UIRect(0, 0, 22, 11);	// 11
	UIRect middle = UIRect(0, 11, 22, 23); // 12
	UIRect bottom = UIRect(0, 23, 22, 34);	// 11

	int i;
	for (i = 0; i <= INVEN_TAB_NORMAL4; ++i)
	{
		m_btnTab[i].SetNewType(TRUE);
		m_btnTab[i].SetRTSurface(UBS_IDLE, top, UIRectUV(86, 0, 107, 10, fTexWidth, fTexHeight));
		m_btnTab[i].SetRTSurface(UBS_IDLE, middle, UIRectUV(86, 11, 107, 22, fTexWidth, fTexHeight));
		m_btnTab[i].SetRTSurface(UBS_IDLE, bottom, UIRectUV(86, 90, 107, 100, fTexWidth, fTexHeight));
		m_btnTab[i].SetRTSurface(UBS_IDLE, UIRect(7, 11, 20, 24), UIRectUV(154, 91, 167, 104, fTexWidth, fTexHeight)); // ������
		m_btnTab[i].SetRTSurface(UBS_CLICK, top, UIRectUV(59, 0, 80, 10, fTexWidth, fTexHeight));
		m_btnTab[i].SetRTSurface(UBS_CLICK, middle, UIRectUV(59, 11, 80, 22, fTexWidth, fTexHeight));
		m_btnTab[i].SetRTSurface(UBS_CLICK, bottom, UIRectUV(59, 90, 80, 100, fTexWidth, fTexHeight));
		m_btnTab[i].SetRTSurface(UBS_CLICK, UIRect(7, 11, 20, 24), UIRectUV(139, 91, 152, 104, fTexWidth, fTexHeight)); // ������
		m_btnTab[i].CopyRTSurface(UBS_CLICK, UBS_ON);
		m_btnTab[i].CopyRTSurface(UBS_IDLE, UBS_DISABLE);
	}
	//Dethunter12 Adjust 223.214.22.34
	m_btnTab[INVEN_TAB_CASH1].Create(this, _s(" "), 223, 214, 22, 26);
	m_btnTab[INVEN_TAB_CASH2].Create(this, _s(" "), 223, 239, 22, 26);
	m_btnTab[INVEN_TAB_CASH3].Create(this, _s(" "), 223, 264, 22, 26);
	m_btnTab[INVEN_TAB_CASH4].Create(this, _s(" "), 223, 289, 22, 26);
	m_btnTab[INVEN_TAB_CASH5].Create(this, _s(" "), 223, 314, 22, 26);
	m_btnTab[INVEN_TAB_CASH6].Create(this, _s(" "), 223, 339, 22, 26);

	for (i = INVEN_TAB_CASH1; i <= INVEN_TAB_CASH6; ++i) // 4 ->6 dethunter12
	{
		m_btnTab[i].SetNewType(TRUE);
		m_btnTab[i].SetRTSurface(UBS_IDLE, top, UIRectUV(86, 0, 107, 10, fTexWidth, fTexHeight));
		m_btnTab[i].SetRTSurface(UBS_IDLE, middle, UIRectUV(86, 11, 107, 22, fTexWidth, fTexHeight));
		m_btnTab[i].SetRTSurface(UBS_IDLE, bottom, UIRectUV(86, 90, 107, 100, fTexWidth, fTexHeight));
		m_btnTab[i].SetRTSurface(UBS_IDLE, UIRect(7, 11, 20, 24), UIRectUV(154, 91, 167, 104, fTexWidth, fTexHeight)); // ������
		m_btnTab[i].SetRTSurface(UBS_CLICK, top, UIRectUV(59, 0, 80, 10, fTexWidth, fTexHeight));
		m_btnTab[i].SetRTSurface(UBS_CLICK, middle, UIRectUV(59, 11, 80, 22, fTexWidth, fTexHeight));
		m_btnTab[i].SetRTSurface(UBS_CLICK, bottom, UIRectUV(59, 90, 80, 100, fTexWidth, fTexHeight));
		m_btnTab[i].SetRTSurface(UBS_CLICK, UIRect(7, 11, 20, 24), UIRectUV(139, 91, 152, 104, fTexWidth, fTexHeight)); // ������
		m_btnTab[i].CopyRTSurface(UBS_CLICK, UBS_ON);
		m_btnTab[i].CopyRTSurface(UBS_IDLE, UBS_DISABLE);
	}

	// Copy --> click => on, idle => disable
	m_btnTab[INVEN_TAB_CASH1].CopyRTSurface(UBS_CLICK, UBS_ON);
	m_btnTab[INVEN_TAB_CASH1].CopyRTSurface(UBS_IDLE, UBS_DISABLE);

	m_btnTab[INVEN_TAB_CASH2].CopyRTSurface(UBS_CLICK, UBS_ON);
	m_btnTab[INVEN_TAB_CASH2].CopyRTSurface(UBS_IDLE, UBS_DISABLE);

	m_btnTab[INVEN_TAB_CASH3].CopyRTSurface(UBS_CLICK, UBS_ON);
	m_btnTab[INVEN_TAB_CASH3].CopyRTSurface(UBS_IDLE, UBS_DISABLE);

	m_btnTab[INVEN_TAB_CASH4].CopyRTSurface(UBS_CLICK, UBS_ON);
	m_btnTab[INVEN_TAB_CASH4].CopyRTSurface(UBS_IDLE, UBS_DISABLE);
	//dethunte12 add
	m_btnTab[INVEN_TAB_CASH5].CopyRTSurface(UBS_CLICK, UBS_ON);
	m_btnTab[INVEN_TAB_CASH6].CopyRTSurface(UBS_IDLE, UBS_DISABLE);


	m_btnClose.Create(this, CTString(""), 232, 4, 16, 16);
	m_btnClose.SetUV(UBS_IDLE, 211, 33, 226, 48, fTexWidth, fTexHeight);
	m_btnClose.SetUV(UBS_CLICK, 229, 33, 244, 48, fTexWidth, fTexHeight);
	m_btnClose.CopyUV(UBS_IDLE, UBS_ON);
	m_btnClose.CopyUV(UBS_IDLE, UBS_DISABLE);

	// Detail Info
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(0, 137, 19, 156, fTexWidth, fTexHeight));	// 20 * 20
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(20, 137, 120, 156, fTexWidth, fTexHeight));	// 101 * 20
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(121, 137, 140, 156, fTexWidth, fTexHeight));	// 20 * 20

	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(0, 157, 19, 206, fTexWidth, fTexHeight));	// 20 * 50
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(20, 157, 120, 206, fTexWidth, fTexHeight)); // 101 * 50
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(121, 157, 140, 206, fTexWidth, fTexHeight)); // 20 * 50

	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(0, 207, 19, 226, fTexWidth, fTexHeight));	// 20 * 20
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(20, 207, 120, 226, fTexWidth, fTexHeight)); // 101 * 20
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(121, 207, 140, 226, fTexWidth, fTexHeight));	// 20 * 20

	// Simple Info 
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(0, 229, 11, 250, fTexWidth, fTexHeight));	// 12 * 22
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(16, 229, 56, 250, fTexWidth, fTexHeight)); // ?? * 22
	m_NewInvenSurface.AddRectSurface(UIRect(0, 0, 0, 0), UIRectUV(73, 229, 84, 250, fTexWidth, fTexHeight));	// 12 * 22

	for (i = 0; i < WEAR_TOTAL; ++i)
		m_pIconsWearing[i] = new CUIIcon;

	m_pIconsWearing[WEAR_HELMET]->Create( this, 112, 46, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_JACKET]->Create( this, 112, 81, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_WEAPON]->Create( this, 77, 134, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );  
	m_pIconsWearing[WEAR_PANTS]->Create( this, 112, 116, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_SHIELD]->Create( this, 147, 99, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_GLOVES]->Create( this, 77, 99, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_BOOTS]->Create( this, 112, 151, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );

	m_pIconsWearing[WEAR_ACCESSORY1]->Create( this, 36, 46, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_ACCESSORY2]->Create( this, 36, 81, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_ACCESSORY3]->Create( this, 36, 116, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_ACCESSORY4]->Create( this, 188, 46, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );

	// newslot - alanssoares
	m_pIconsWearing[WEAR_ACCESSORY_ANYWHERE]->Create( this, 77, 56, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_ACCESSORY_SPECIAL1]->Create( this, 219, 110, BTN_SIZE_SMALL, BTN_SIZE_SMALL, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_ACCESSORY_SPECIAL2]->Create( this, 194, 85, BTN_SIZE_SMALL, BTN_SIZE_SMALL, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_ACCESSORY_SPECIAL3]->Create( this, 219, 85, BTN_SIZE_SMALL, BTN_SIZE_SMALL, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_ACCESSORY_SPECIAL4]->Create( this, 194, 110, BTN_SIZE_SMALL, BTN_SIZE_SMALL, UI_INVENTORY, UBET_ITEM );
	m_pIconsWearing[WEAR_ACCESSORY_SPECIAL5]->Create( this, 166, 146, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM );

	m_pIconsWearing[WEAR_BACKWING]->Create(this, 147, 64, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM);

	// ���� ��ũ���� ����������, ������ ��ư�� ��ġ�� �̸� �����Ͽ� �д�.
	// �� �Ǵ� ������ ��ư�� 5 * 5�� ��ġ�� �̷�� ����.
	const int tmpX = 40;
	const int tmpY = 220;
	const int slotX = START_ITEMBTN_X;
	const int slotY = START_ITEMBTN_Y;
	const int btngap = 4;
	int iX = tmpX, iY = tmpY;
	int nXslot = slotX;
	int nYslot = slotY;

	// UI���� �κ��丮 [10/17/2012 Ranma]
	for (i = 0; i < INVENSLOT_MAX; i++)
	{
		m_pInvenSlot[i] = CUIManager::getSingleton()->GetUI(UI_INVEN_SLOT1 + i);

		if (i < INVENSLOT_CASH1)
			((CUIChildInvenSlot*)m_pInvenSlot[i])->SetInventoryAllItem(&m_abtnItems);
		else if (i <= INVENSLOT_CASH6) //4-6
		{
			if (CUIInvenCashBag* pCashBag = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[i]))
				pCashBag->SetInventoryAllItem(&m_abtnItems, i - (INVENSLOT_CASH1 - 1));
		}
	}

	CUIWindow* pParant;

	//for (i = 0; i < ITEM_COUNT_IN_INVENTORY_NORMAL; ++i)
	for (i = 0; i < ITEM_COUNT_IN_INVENTORY_NORMAL; ++i)
	{
		if (i < INVEN_ONE_BAG)
			pParant = this;
		else if (i < (INVEN_ONE_BAG * 2))
			pParant = m_pInvenSlot[INVENSLOT_NUM1];
		else if (i < (INVEN_ONE_BAG * 3))
			pParant = m_pInvenSlot[INVENSLOT_NUM2];
		else
			pParant = m_pInvenSlot[INVENSLOT_NUM3];

		iX = tmpX + ((BTN_SIZE + btngap) * (i % INVEN_SLOT_COL));
		iY = tmpY + ((BTN_SIZE + btngap) * ((i / INVEN_SLOT_COL) % INVEN_SLOT_COL));

		nXslot = slotX + ((BTN_SIZE + btngap) * (i % INVEN_SLOT_COL));
		nYslot = slotY + ((BTN_SIZE + btngap) * ((i / INVEN_SLOT_COL) % INVEN_SLOT_COL));

		{
			m_abtnItems[0][i] = new CUIIcon;
			m_abtnItems[0][i]->Hide(TRUE);
			m_abtnItems[0][i]->initialize();
			m_abtnItems[0][i]->SetWhichUI(UI_INVENTORY);

			if (i < INVEN_ONE_BAG)
			{
				m_abtnItems[0][i]->InitPos(iX, iY, BTN_SIZE, BTN_SIZE);
				m_abtnItems[0][i]->setParent(pParant);
			}
			else
			{
				m_abtnItems[0][i]->InitPos(nXslot, nYslot, BTN_SIZE, BTN_SIZE);
				m_abtnItems[0][i]->setParent(pParant);
			}
		}
	}

	m_rcInventoryTab[INVEN_TAB_GENERNAL].SetRect(5, 15, 5 + INVENTORY_TYPE_TAP_WIDTH, 15 + INVENTORY_TYPE_TAP_HEIGHT);
	m_rcInventoryTab[INVEN_TAB_COSTUME].SetRect(m_rcInventoryTab[INVEN_TAB_GENERNAL].Right, 15, 5 + INVENTORY_TYPE_TAP_WIDTH * 2, 15 + INVENTORY_TYPE_TAP_HEIGHT);
	//	m_rcCostumeTab.SetUV( 145, 138, 240, 172, fTexWidth, fTexHeight );

	m_btnInvenTab[INVEN_TAB_GENERNAL].Create(this, _s(" "), m_rcInventoryTab[INVEN_TAB_GENERNAL].Left, m_rcInventoryTab[INVEN_TAB_GENERNAL].Top, INVENTORY_TYPE_TAP_WIDTH, INVENTORY_TYPE_TAP_HEIGHT);
	m_btnInvenTab[INVEN_TAB_COSTUME].Create(this, _s(" "), m_rcInventoryTab[INVEN_TAB_COSTUME].Left, m_rcInventoryTab[INVEN_TAB_COSTUME].Top, INVENTORY_TYPE_TAP_WIDTH, INVENTORY_TYPE_TAP_HEIGHT);
	m_btnInvenTab[INVEN_TAB_GENERNAL].SetNewType(TRUE);
	m_btnInvenTab[INVEN_TAB_COSTUME].SetNewType(TRUE);
	top = UIRect(0, 0, 11, INVENTORY_TYPE_TAP_HEIGHT);		// 11	
	middle = UIRect(11, 0, 23, INVENTORY_TYPE_TAP_HEIGHT);	// 12
	bottom = UIRect(23, 0, 34, INVENTORY_TYPE_TAP_HEIGHT);	// 11
	m_btnInvenTab[INVEN_TAB_GENERNAL].SetRTSurface(UBS_IDLE, top, UIRectUV(104, 106, 119, 127, fTexWidth, fTexHeight));
	m_btnInvenTab[INVEN_TAB_GENERNAL].SetRTSurface(UBS_IDLE, middle, UIRectUV(120, 106, 132, 127, fTexWidth, fTexHeight));
	m_btnInvenTab[INVEN_TAB_GENERNAL].SetRTSurface(UBS_IDLE, bottom, UIRectUV(189, 106, 204, 127, fTexWidth, fTexHeight));
	m_btnInvenTab[INVEN_TAB_GENERNAL].SetRTSurface(UBS_CLICK, top, UIRectUV(0, 106, 15, 127, fTexWidth, fTexHeight));
	m_btnInvenTab[INVEN_TAB_GENERNAL].SetRTSurface(UBS_CLICK, middle, UIRectUV(16, 106, 31, 127, fTexWidth, fTexHeight));
	m_btnInvenTab[INVEN_TAB_GENERNAL].SetRTSurface(UBS_CLICK, bottom, UIRectUV(85, 106, 100, 127, fTexWidth, fTexHeight));
	m_btnInvenTab[INVEN_TAB_COSTUME].GetRectSurface(UBS_IDLE) = m_btnInvenTab[INVEN_TAB_GENERNAL].GetRectSurface(UBS_IDLE);
	m_btnInvenTab[INVEN_TAB_COSTUME].GetRectSurface(UBS_CLICK) = m_btnInvenTab[INVEN_TAB_GENERNAL].GetRectSurface(UBS_CLICK);
	// ��ư�̹������� ������ �̹��� 
	m_btnInvenTab[INVEN_TAB_GENERNAL].SetRTSurface(UBS_IDLE, UIRect(10, 5, 23, 18), UIRectUV(498, 23, 512, 37, fTexWidth, fTexHeight));
	m_btnInvenTab[INVEN_TAB_GENERNAL].SetRTSurface(UBS_CLICK, UIRect(10, 5, 23, 18), UIRectUV(482, 23, 496, 37, fTexWidth, fTexHeight));
	m_btnInvenTab[INVEN_TAB_COSTUME].SetRTSurface(UBS_IDLE, UIRect(10, 5, 23, 18), UIRectUV(498, 39, 512, 53, fTexWidth, fTexHeight));
	m_btnInvenTab[INVEN_TAB_COSTUME].SetRTSurface(UBS_CLICK, UIRect(10, 5, 23, 18), UIRectUV(482, 39, 496, 53, fTexWidth, fTexHeight));
	// Copy --> click => on, idle => disable
	m_btnInvenTab[INVEN_TAB_GENERNAL].CopyRTSurface(UBS_CLICK, UBS_ON);
	m_btnInvenTab[INVEN_TAB_GENERNAL].CopyRTSurface(UBS_IDLE, UBS_DISABLE);
	m_btnInvenTab[INVEN_TAB_COSTUME].CopyRTSurface(UBS_CLICK, UBS_ON);
	m_btnInvenTab[INVEN_TAB_COSTUME].CopyRTSurface(UBS_IDLE, UBS_DISABLE);

	for (i = 0; i < WEAR_COSTUME_TOTAL; ++i)
		m_pIconsCostumeWearing[i] = new CUIIcon;

	m_pIconsCostumeWearing[WEAR_COSTUME_HELMET]->Create(this, 112, 46, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM);
	m_pIconsCostumeWearing[WEAR_COSTUME_JACKET]->Create(this, 112, 81, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM);
	m_pIconsCostumeWearing[WEAR_COSTUME_WEAPON]->Create(this, 77, 134, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM);
	m_pIconsCostumeWearing[WEAR_COSTUME_PANTS]->Create(this, 112, 116, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM);
	m_pIconsCostumeWearing[WEAR_COSTUME_SHIELD]->Create(this, 147, 99, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM);
	m_pIconsCostumeWearing[WEAR_COSTUME_GLOVES]->Create(this, 77, 99, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM);
	m_pIconsCostumeWearing[WEAR_COSTUME_BOOTS]->Create(this, 112, 151, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM);
	m_pIconsCostumeWearing[WEAR_COSTUME_BACKWING]->Create(this, 147, 64, BTN_SIZE, BTN_SIZE, UI_INVENTORY, UBET_ITEM);


	m_btnArrange.Create(this, _s(" "), 11, 381, 20, 20);
	m_btnArrange.SetNewType(TRUE);
	m_btnArrange.SetRTSurface(UBS_IDLE, UIRect(0, 0, 20, 20), UIRectUV(471, 0, 491, 20, fTexWidth, fTexHeight));
	m_btnArrange.SetRTSurface(UBS_CLICK, UIRect(0, 0, 20, 20), UIRectUV(492, 0, 512, 20, fTexWidth, fTexHeight));
	m_btnArrange.CopyRTSurface(UBS_IDLE, UBS_ON);
	m_btnArrange.CopyRTSurface(UBS_IDLE, UBS_DISABLE);
#ifdef ENABLE_INVISIBLE_HELMET
	m_btnOptions.Create(this, _s(" "), 226, 380, 18, 19);
	m_btnOptions.SetNewType(TRUE);
	m_btnOptions.SetRTSurface(UBS_IDLE, UIRect(0, 0, 18, 19), UIRectUV(488, 71, 506, 90, fTexWidth, fTexHeight));
	m_btnOptions.SetRTSurface(UBS_CLICK, UIRect(0, 0, 18, 19), UIRectUV(466, 71, 484, 90, fTexWidth, fTexHeight));
	m_btnOptions.CopyRTSurface(UBS_IDLE, UBS_ON);
	m_btnOptions.CopyRTSurface(UBS_IDLE, UBS_DISABLE);
#endif
	m_ptdCostumeTexture = CreateTexture(CTString("Data\\Interface\\CostumeInventory.tex"));

	fTexWidth = m_ptdCostumeTexture->GetWidth();
	fTexHeight = m_ptdCostumeTexture->GetHeight();
	m_kRSCostumeBackground.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(257, 0, 503, 155, fTexWidth, fTexHeight));
	m_kRSCostumeBackground.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(504, 0, 750, 155, fTexWidth, fTexHeight));
	m_kRSCostumeBackground.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(751, 0, 997, 155, fTexWidth, fTexHeight));
	m_kRSCostumeBackground.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(257, 156, 503, 311, fTexWidth, fTexHeight));
	m_kRSCostumeBackground.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(504, 156, 750, 311, fTexWidth, fTexHeight));
	m_kRSCostumeBackground.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(751, 156, 997, 311, fTexWidth, fTexHeight));
	m_kRSCostumeBackground.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(257, 312, 503, 467, fTexWidth, fTexHeight));
#ifdef CHAR_EX_ROGUE
	m_kRSCostumeBackground.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(504, 156, 750, 311, fTexWidth, fTexHeight));
#endif
#ifdef CHAR_EX_MAGE
	m_kRSCostumeBackground.AddRectSurface(UIRect(5, 37, 251, 192), UIRectUV(257, 156, 503, 311, fTexWidth, fTexHeight));
#endif

	// [2011/01/18 : Sora] �⼮ �̺�Ʈ
	m_EventPopUp.Create(this, 0, 0, 116, 68);

	m_pImgSelect = UISUPPORT()->clone_Image(eIMG_TYPE_SELECT);
	m_pImgSelect->setParent(this);
	m_pImgSelect->Hide(TRUE);

	m_pEventActiveUI = new CEventActiveUI();
	UIMGR()->LoadXML("EventListRST.xml", m_pEventActiveUI);
	this->addChild(m_pEventActiveUI);

	int nXEvent = GetPosX() + GetWidth();
	int nYEvent = GetPosY();

	m_pEventActiveUI->SetPos(nXEvent, nYEvent);

	SetWidth(GetWidth() + m_pEventActiveUI->GetWidth());
	updatePosition(true);
}

// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	SetPos((pixMaxI + pixMinI) / 2, (pixMaxJ + pixMinJ - GetHeight()) / 2);

	m_EventPopUp.InitPosition();
}

void CUIInventory::ResetSavePosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	ResetPosition(pixMinI, pixMinJ, pixMaxI, pixMaxJ);
	g_iXPosInInventory = GetPosX();
	g_iYPosInInventory = GetPosY();
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	if (m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ)
		ResetPosition(pixMinI, pixMinJ, pixMaxI, pixMaxJ);
}

// ----------------------------------------------------------------------------
// Name : ShowLockErrorMessage()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::ShowLockErrorMessage()
{
	CTString	strError;
	switch (m_eLockInvenProcess)
	{
	case LOCK_UPGRADE_ITEM:
		strError = _S(837, "������ ���׷��̵尡 �������Դϴ�.");
		break;
	case LOCK_BLOOD_OPTION:
		strError = _S(838, "������ �ɼ� �۾��� �������Դϴ�.");
		break;
	case LOCK_REFINE:
		strError = _S(839, "������ �������Դϴ�.");
		break;
	case LOCK_COMPOUND:
		strError = _S(840, "���� ���ڸ� �ռ����Դϴ�.");
		break;
	case LOCK_MIX:
		strError = _S(841, "��Ȱ�� ���ڸ� �������Դϴ�.");
		break;
	case LOCK_MIXNEW:
		strError = _S(6450, "���� �ֹ����� �и� �ֹ����� ��� ���Դϴ�.");
		break;
	case LOCK_MASTERSTONE:
		strError = _S(6449, "�����ͽ��� ���׷��̵� ���Դϴ�.");
		break;
	case LOCK_GW_MIX:
		strError = _S(1928, "���� �������� �������Դϴ�.");
		break;
	case LOCK_PROCESS:
		strError = _S(842, "���� �۾��� �������Դϴ�.");
		break;
	case LOCK_PRODUCT:
	case LOCK_PRODUCT_ITEM:
		strError = _S(843, "���� �۾��� �������Դϴ�.");
		break;
	case LOCK_REMISSION:
		strError = _S(844, "���˺� �۾��� �������Դϴ�.");
		break;
	case LOCK_EXCHANGE:
		strError = _S(845, "��ȯ�� �������Դϴ�.");
		break;
	case LOCK_SHOP:
		strError = _S(846, "������ �̿����Դϴ�.");
		break;
	case LOCK_PERSONAL_SHOP:
		strError = _S(847, "���� ������ �̿����Դϴ�.");
		break;
	case LOCK_WAREHOUSE:
		strError = _S(848, "â���� �̿����Դϴ�.");
		break;
	case LOCK_CHANGEWEAPON:
		strError = _S(1186, "���� ��ü ���Դϴ�.");
		break;
	case LOCK_QUEST:
		strError = _S(1669, "����Ʈ ������ �а� �ִ� ���Դϴ�.");
		break;
	case LOCK_MYSTERIOUSBEAD:
		strError = _S(6107, "�ź��� ������ ������ ��� ���Դϴ�.");
		break;
	case LOCK_AUCTION:
		strError = _S(6108, "�ŷ����� �ý����� ��� ���Դϴ�.");
		break;
	case LOCK_PET_STASH:
		//strError = 
		break;
#ifdef DURABILITY
	case LOCK_DURABILITY:
		strError = _S(6273, "������ �ý����� ��� ���Դϴ�.");
		break;
#endif	//	DURABILITY
	case LOCK_TRANSMOGRIFY:
		strError = _S(8355, "Transmogrify is in progress");
		break;
	case LOCK_EXTEND_MENU:
		strError = _S(8356, "Extend Menu is in progress");
		break;

#ifdef BATTLE_PASS_SYSTEM
	case LOCK_BATTLE_PASS:
		strError = "Battle Pass is in progress";
		break;
#endif
#ifdef PRESTIGE_SYSTEM
	case LOCK_PRESTIGE:
		strError = _S(8555, "Prestige is in progress");
		//strError = "Prestige is in progress";
		break;
#endif
	default:
		strError = _S(6272, "�ٸ� �ý����� �̿����Դϴ�.");
		break;;
	}

	if (strError.IsEmpty() == FALSE)
	{
		CUIManager::getSingleton()->GetChattingUI()->AddSysMessage(strError, SYSMSG_ERROR);
	}
}

// ----------------------------------------------------------------------------
// Name : RenderItems()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::RenderItems()
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CDrawPort* pDrawPort = pUIManager->GetDrawPort();

	// Wearing items
	if (m_iInventoryType == INVEN_TAB_COSTUME)
	{
		for (int iWear = 0; iWear < WEAR_COSTUME_TOTAL; ++iWear)
		{
			if (!m_pIconsCostumeWearing[iWear]->IsEmpty())
				m_pIconsCostumeWearing[iWear]->Render(pDrawPort);
		}
	}
	else
	{
		for (int iWear = 0; iWear < WEAR_TOTAL; iWear++)
		{
			if (!m_pIconsWearing[iWear]->IsEmpty())
				m_pIconsWearing[iWear]->Render(pDrawPort);
		}
	}

	//	int		tv_posX, tv_posY;
	int		nTab;
	int		i, inven_idx;

	nTab = ((m_InvenCurrentTab - INVEN_TAB_NORMAL4) > 0) ? (m_InvenCurrentTab - INVEN_TAB_NORMAL4) : 0;

	for (i = 0; i < INVEN_ONE_BAG; ++i)
	{
		if (nTab > 0)
			inven_idx = i;
		else
			inven_idx = i + (m_InvenCurrentTab * INVEN_ONE_BAG);

		if (IsPlayNewItemEffect(i) == TRUE)
		{
			CInvenData* pInven = CInvenData::getSingleton();

			if (pInven)
			{
				if (pInven->IsNewItemEffectRender() == TRUE &&
					IsCheckNewItemEffectPlayCount(i) == TRUE)
				{
					m_abtnItems[nTab][inven_idx]->setImageHide(eIMG_TYPE_NEW, FALSE);
				}
				else
				{
					m_abtnItems[nTab][inven_idx]->setImageHide(eIMG_TYPE_NEW, TRUE);
				}
			}
		}

		m_abtnItems[nTab][inven_idx]->Render(pDrawPort);
	}

	if (m_pImgSelect != NULL)
		m_pImgSelect->Render(pDrawPort);
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::Render()
{
	// Set inventory texture
	int row;//, col;

	CUIManager* pUIManager = CUIManager::getSingleton();
	CDrawPort* pDrawPort = pUIManager->GetDrawPort();

	m_pEventActiveUI->Render();

	//������ ������Ʈ
	UpdateNewItemEffect();

	m_NewInvenSurface.SetPos(m_nPosX, m_nPosY);
	m_NewItemEffectSurface.SetPos(m_nPosX, m_nPosY);

	if (m_iInventoryType == INVEN_TAB_GENERNAL)
		pDrawPort->InitTextureData(m_ptdBaseTexture);
	else
		pDrawPort->InitTextureData(m_ptdCostumeTexture);

	// ��׶���
	m_NewInvenSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF, EInvenBg);

	// ������ ��ư
	m_btnTrashcan.Render();

	pDrawPort->FlushRenderingQueue();

	if (IsCostumeInventory() == FALSE)
	{
		if (m_ptdWearBackTexture != NULL)
		{
			pDrawPort->InitTextureData(m_ptdWearBackTexture);
			m_WearInvenSurface.SetPos(m_nPosX, m_nPosY);
			m_WearInvenSurface.RenderRectSurface(pDrawPort, DEF_UI_COLOR_WHITE, _pNetwork->MyCharacterInfo.job);
			pDrawPort->FlushRenderingQueue();
		}
	}
	else
	{
		if (m_ptdCostumeTexture != NULL)
		{
			pDrawPort->InitTextureData(m_ptdCostumeTexture);
			m_kRSCostumeBackground.SetPos(m_nPosX, m_nPosY);
			m_kRSCostumeBackground.RenderRectSurface(pDrawPort, DEF_UI_COLOR_WHITE, _pNetwork->MyCharacterInfo.job);
			pDrawPort->FlushRenderingQueue();
		}
	}

	pDrawPort->InitTextureData(ptdCommonTexture);

	m_btnArrange.Render();
#ifdef ENABLE_INVISIBLE_HELMET
	m_btnOptions.Render();
#endif
	//////////////////////////////////////////////////////////////////////////////
		// UI���� [10/11/2012 Ranma]
	m_btnTab[INVEN_TAB_NORMAL0].SetBtnState(UBS_ON);	// �⺻ �κ� ���� ���� �׻� Ȱ��ȭ.

	if (m_InvenCurrentTab > INVEN_TAB_NORMAL0)			// ������ ���� ������ Ȱ��ȭ.
		m_btnTab[m_InvenCurrentTab].SetBtnState(UBS_ON);

	// UI���� [10/10/2012 Ranma]
	for (int id = 0; id < INVENSLOT_MAX; id++)
	{
		if (id < INVENSLOT_CASH1)	// ��.................................. enum���� �ʹ� ������.
		{
			if (m_btnTab[INVEN_TAB_NORMAL1 + id].GetBtnState() != UBS_CLICK)
				m_btnTab[INVEN_TAB_NORMAL1 + id].SetBtnState(m_bSlot[id] ? UBS_ON : UBS_IDLE);
		}
		else if (id <= INVENSLOT_CASH6) //4-6
		{
			if (m_btnTab[INVEN_TAB_NORMAL2 + id].GetBtnState() != UBS_CLICK)
				m_btnTab[INVEN_TAB_NORMAL2 + id].SetBtnState(m_bSlot[id] ? UBS_ON : UBS_IDLE);
		}

		if (id < INVENSLOT_CASH1)
			((CUIChildInvenSlot*)m_pInvenSlot[id])->ToggleVisible(m_bSlot[id]);
		else if (id <= INVENSLOT_CASH6) //4-6
		{
			if (CUIInvenCashBag* pCashBag = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[id]))
				pCashBag->ToggleVisible(m_bSlot[id]);
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	if (m_btnInvenTab[m_iInventoryType].GetBtnState() != UBS_ON)
		m_btnInvenTab[m_iInventoryType].SetBtnState(UBS_ON);

	for (row = 0; row < INVEN_TAB_TOTAL; ++row)
	{
		// UI ���� [10/11/2012 Ranma]
		if (row == INVEN_TAB_NORMAL4)
			continue;

		m_btnTab[row].Render();
	}

	CInvenData* pInven = CInvenData::getSingleton();

	for (int i = 0; i < INVENSLOT_MAX; i++)
	{
		// ���� ���� �������� ������ ����Ʈ
		if (IsPlayNewBagEffect((eInvenSlot)i) == TRUE && pInven)
		{
			int nInvenTab = 0;

			if (pInven->IsNewItemEffectRender() == TRUE &&
				IsCheckNewBagEffectPlayCount((eInvenSlot)i) == TRUE)
			{
				if (i >= INVENSLOT_NUM1 && i <= INVENSLOT_NUM3) // �⺻������ ���� (+1)
				{
					nInvenTab = i + 1;

					m_NewItemEffectSurface.m_RectSurfaceArray[NEW_EFFECT_BAG].m_RT = UIRect(m_btnTab[nInvenTab].GetPosX() + 7, m_btnTab[nInvenTab].GetPosY() + 11,
						m_btnTab[nInvenTab].GetPosX() + 20, m_btnTab[nInvenTab].GetPosY() + 24);
					m_NewItemEffectSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF, NEW_EFFECT_BAG);
				}
				else if (i > INVENSLOT_NUM3 && i < INVENSLOT_MAX) // 4�������� ������� �����Ƿ� (+1)
				{
					nInvenTab = i + 2;//dethunter12 test

					m_NewItemEffectSurface.m_RectSurfaceArray[NEW_EFFECT_BAG_CASH].m_RT = UIRect(m_btnTab[nInvenTab].GetPosX() + 7, m_btnTab[nInvenTab].GetPosY() + 11,
						m_btnTab[nInvenTab].GetPosX() + 20, m_btnTab[nInvenTab].GetPosY() + 24);
					m_NewItemEffectSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF, NEW_EFFECT_BAG_CASH);
				}
			}
		}
	}

	m_btnInvenTab[INVEN_TAB_GENERNAL].Render();
	m_btnInvenTab[INVEN_TAB_COSTUME].Render();

	m_btnClose.Render();
	pDrawPort->FlushRenderingQueue();
	// Text in inventory
	CTString strInven;
	int nTitlePosX;
	if (!IsCostumeInventory())
	{
		strInven = _S(166, "�κ��丮");
	}
	else
	{
		strInven = _S(4784, "�� �� Ƭ");
	}
	nTitlePosX = (INVENTORY_WIDTH - strInven.Length()) / 2;
	pDrawPort->PutTextExCX(strInven, m_nPosX + nTitlePosX, m_nPosY + 17, 0xFFFFFFFF);

	m_strMyMoney.PrintF("%I64d", _pNetwork->MyCharacterInfo.money);
	CUIManager::getSingleton()->InsertCommaToString(m_strMyMoney);
	// Money
	COLOR colNas = pUIManager->GetNasColor(_pNetwork->MyCharacterInfo.money);
	pDrawPort->PutTextExRX(m_strMyMoney, m_nPosX + 229, m_nPosY + 196, colNas);

	int nInvenSlotMax = ITEM_COUNT_IN_INVENTORY_NORMAL;
	COLOR colInvenSlotMax = 0xFFFFFFFF;
	{
		int i;
		for (i = INVENSLOT_CASH1; i < INVENSLOT_MAX; i++)	// ĳ�� �κ��丮 �߰��� ���� �κ��丮 ���� ���� ǥ�� ������Ʈ.
		{
			if (CUIInvenCashBag* pCashBag = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[i]))
			{
				if (!pCashBag->IsInvenCashBagLock())
				{
					nInvenSlotMax += INVEN_ONE_BAG;
					colInvenSlotMax = 0x00FF00FF;
				}
			}
		}
	}
	m_strNumItems.PrintF("%d/%d", GetMySlotItemsCount(), nInvenSlotMax);
	pDrawPort->PutTextExCX(m_strNumItems, m_nPosX + 28, m_nPosY + 196, colInvenSlotMax);

	// Flush all render text queue
	pDrawPort->EndTextEx();

	// Items
	RenderItems();

	// Tool tip
	if (m_bShowToolTip)
	{
		// Set texture
		pDrawPort->InitTextureData(ptdCommonTexture);
		int tmpX1, tmpY1, tmpX2, tmpY2;
		int i;
		tmpX1 = m_rcToolTip.Left - m_nPosX;
		tmpY1 = m_rcToolTip.Top - m_nPosY;
		tmpX2 = m_rcToolTip.Right - m_nPosX;
		tmpY2 = m_rcToolTip.Bottom - m_nPosY;

		m_NewInvenSurface.m_RectSurfaceArray[EInvenSimpleInfoL].m_RT = UIRect(tmpX1, tmpY1, tmpX1 + DEF_TOOLTIP_XGAP, tmpY2);
		m_NewInvenSurface.m_RectSurfaceArray[EInvenSimpleInfoM].m_RT = UIRect(tmpX1 + DEF_TOOLTIP_XGAP, tmpY1, tmpX2 - DEF_TOOLTIP_XGAP, tmpY2);
		m_NewInvenSurface.m_RectSurfaceArray[EInvenSimpleInfoR].m_RT = UIRect(tmpX2 - DEF_TOOLTIP_XGAP, tmpY1, tmpX2, tmpY2);

		for (i = EInvenSimpleInfoL; i < EInvenTotal; ++i)
		{
			m_NewInvenSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF, i);
		}

		// Render all elements
		pDrawPort->FlushRenderingQueue();

		// Text in tool tip
		pDrawPort->PutTextEx(m_strToolTip, m_rcToolTip.Left + DEF_TOOLTIP_XGAP, m_rcToolTip.Top + DEF_TOOLTIP_YGAP);

		// Flush all render text queue
		pDrawPort->EndTextEx();
	}

	// ��� ������ ���̵� ����
	if (m_bShowWearSlotToolTip)
	{
		// Set texture
		pDrawPort->InitTextureData(ptdCommonTexture);
		int tmpX1, tmpY1, tmpX2, tmpY2;
		int i;
		tmpX1 = m_rcWearSlotToolTip.Left - m_nPosX;
		tmpY1 = m_rcWearSlotToolTip.Top - m_nPosY;
		tmpX2 = m_rcWearSlotToolTip.Right - m_nPosX;
		tmpY2 = m_rcWearSlotToolTip.Bottom - m_nPosY;

		m_NewInvenSurface.m_RectSurfaceArray[EInvenSimpleInfoL].m_RT = UIRect(tmpX1, tmpY1, tmpX1 + DEF_TOOLTIP_XGAP, tmpY2);
		m_NewInvenSurface.m_RectSurfaceArray[EInvenSimpleInfoM].m_RT = UIRect(tmpX1 + DEF_TOOLTIP_XGAP, tmpY1, tmpX2 - DEF_TOOLTIP_XGAP, tmpY2);
		m_NewInvenSurface.m_RectSurfaceArray[EInvenSimpleInfoR].m_RT = UIRect(tmpX2 - DEF_TOOLTIP_XGAP, tmpY1, tmpX2, tmpY2);

		for (i = EInvenSimpleInfoL; i < EInvenTotal; ++i)
		{
			m_NewInvenSurface.RenderRectSurface(pDrawPort, 0xFFFFFFFF, i);
		}

		// Render all elements
		pDrawPort->FlushRenderingQueue();

		// Text in tool tip
		pDrawPort->PutTextEx(m_strWearSlotToolTip, m_rcWearSlotToolTip.Left + DEF_TOOLTIP_XGAP, m_rcWearSlotToolTip.Top + DEF_TOOLTIP_YGAP);

		// Flush all render text queue
		pDrawPort->EndTextEx();
	}

	if (!m_EventPopUp.IsEmpty())
		m_EventPopUp.Render();
}

// ----------------------------------------------------------------------------
// Name : ShowToolTip()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::ShowToolTip(BOOL bShow, int nToolTipID)
{
	static int	nOldToolTipID = -1;

	if (!bShow)
	{
		nOldToolTipID = -1;
		m_bShowToolTip = FALSE;
		return;
	}

	m_bShowToolTip = TRUE;

	if (nOldToolTipID != nToolTipID)
	{
		int	nInfoX, nInfoY, nX, nY;

		nOldToolTipID = nToolTipID;
		switch (nToolTipID)
		{
			//case ITEM_TAB_NORMAL:
		case INVEN_TAB_NORMAL0:
			m_strToolTip = _S(5779, "1������");
			break;
		case INVEN_TAB_NORMAL1:
			m_strToolTip = _S(5780, "2������");
			break;
		case INVEN_TAB_NORMAL2:
			m_strToolTip = _S(5781, "3������");
			break;
		case INVEN_TAB_NORMAL3:
			m_strToolTip = _S(5782, "4������");
			break;
		case INVEN_TAB_NORMAL4:
			break;
		case INVEN_TAB_CASH1:
		{
			m_strToolTip.PrintF(_S(6060, "%d�� ���̸��� ����"), 1);
		}
		break;
		case INVEN_TAB_CASH2:
		{
			m_strToolTip.PrintF(_S(6060, "%d�� ���̸��� ����"), 2);
		}
		break;
		case INVEN_TAB_CASH3:
		{
			m_strToolTip.PrintF(_S(6060, "%d�� ���̸��� ����"), 3);
		}
		break;
		case INVEN_TAB_CASH4:
		{
			m_strToolTip.PrintF(_S(6060, "%d�� ���̸��� ����"), 4);
		}
		break;
		case INVEN_TAB_CASH5:
		{
			m_strToolTip.PrintF(_S(6060, "%d�� ���̸��� ����"), 5);
		}
		break;
		case INVEN_TAB_CASH6:
		{
			m_strToolTip.PrintF(_S(6060, "%d�� ���̸��� ����"), 6);
		}
		break;
		}

		int	nInfoWidth = _pUIFontTexMgr->GetFontSpacing() + m_strToolTip.Length() * (_pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing());
		int	nInfoHeight = (DEF_TOOLTIP_YGAP * 2) + _pUIFontTexMgr->GetFontHeight();

		m_btnTab[nToolTipID].GetPos(nX, nY);
		nInfoX = m_nPosX + nX + m_btnTab[nToolTipID].GetWidth() + 2;
		nInfoY = m_nPosY + nY + (m_btnTab[nToolTipID].GetHeight() - _pUIFontTexMgr->GetLineHeight()) / 2;

		if (nInfoX + nInfoWidth > CUIManager::getSingleton()->GetMaxI())
			nInfoX = CUIManager::getSingleton()->GetMaxI() - nInfoWidth;

		m_rcToolTip.Left = nInfoX;
		m_rcToolTip.Top = nInfoY;
		m_rcToolTip.Right = m_rcToolTip.Left + nInfoWidth + (DEF_TOOLTIP_XGAP * 2);
		m_rcToolTip.Bottom = m_rcToolTip.Top + nInfoHeight;
	}
}

void CUIInventory::ShowWearTabToolTip(BOOL bShow, int nToolTipID /*= -1 */)
{
	if (!bShow)
	{
		m_bShowToolTip = FALSE;
		return;
	}

	m_bShowToolTip = TRUE;

	int	nInfoX, nInfoY, nX, nY;

	switch (nToolTipID)
	{
		//case ITEM_TAB_NORMAL:
	case INVEN_TAB_GENERNAL:
		m_strToolTip = _S(6044, "�Ϲ� ����");
		break;
	case INVEN_TAB_COSTUME:
		m_strToolTip = _S(6045, "�ڽ�Ƭ ����");
		break;
	default:
		m_bShowToolTip = FALSE;
		return;
	}

	int	nInfoWidth = _pUIFontTexMgr->GetFontSpacing() + m_strToolTip.Length() * (_pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing());
	int	nInfoHeight = (DEF_TOOLTIP_YGAP * 2) + _pUIFontTexMgr->GetFontHeight();

	m_btnInvenTab[nToolTipID].GetPos(nX, nY);
	nInfoX = m_nPosX + nX + m_btnInvenTab[nToolTipID].GetWidth() + 2;
	nInfoY = m_nPosY + nY + (m_btnInvenTab[nToolTipID].GetHeight() - _pUIFontTexMgr->GetLineHeight()) / 2;

	if (nInfoX + nInfoWidth > CUIManager::getSingleton()->GetMaxI())
		nInfoX = CUIManager::getSingleton()->GetMaxI() - nInfoWidth;

	m_rcToolTip.Left = nInfoX;
	m_rcToolTip.Top = nInfoY;
	m_rcToolTip.Right = m_rcToolTip.Left + nInfoWidth + (DEF_TOOLTIP_XGAP * 2);
	m_rcToolTip.Bottom = m_rcToolTip.Top + nInfoHeight;
}

void CUIInventory::ShowWearGuideToolTip(BOOL bShow, eWEAR_TYPE eType, int WearPos)
{
	if (!bShow)
	{
		m_bShowWearSlotToolTip = FALSE;
		return;
	}

	if (WearPos < 0)
		return;

	CUIIcon** btnWear;

	switch (eType)
	{
	case WEAR_TYPE_NONE:
		btnWear = m_pIconsWearing;
		break;
	case WEAR_TYPE_COSTUME:
	{
		/*if ( WearPos == WEAR_COSTUME_WEAPON || //RomeoST
			WearPos == WEAR_COSTUME_SHIELD ||
			WearPos == WEAR_COSTUME_BACKWING)
		{
			m_bShowWearSlotToolTip = FALSE;
			return;
		}*/

		btnWear = m_pIconsCostumeWearing;
	}
	break;
	default:
		return;
	}

	m_bShowWearSlotToolTip = TRUE;

	UtilHelp* pHelp = UtilHelp::getSingleton();

	if (pHelp == NULL)
		return;

	m_strWearSlotToolTip = pHelp->GetWearPosName(WearPos, eType);

	int	nInfoX, nInfoY, nX, nY;
	int	nInfoWidth = _pUIFontTexMgr->GetFontSpacing() + m_strWearSlotToolTip.Length() * (_pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing());
	int	nInfoHeight = (DEF_TOOLTIP_YGAP * 2) + _pUIFontTexMgr->GetFontHeight();

	btnWear[WearPos]->GetPos(nX, nY);
	nInfoX = m_nPosX + nX + btnWear[WearPos]->GetWidth() + 2;
	nInfoY = m_nPosY + nY + (btnWear[WearPos]->GetHeight() - _pUIFontTexMgr->GetLineHeight()) / 2;

	if (nInfoX + nInfoWidth > CUIManager::getSingleton()->GetMaxI())
		nInfoX = CUIManager::getSingleton()->GetMaxI() - nInfoWidth;

	m_rcWearSlotToolTip.Left = nInfoX;
	m_rcWearSlotToolTip.Top = nInfoY;
	m_rcWearSlotToolTip.Right = m_rcWearSlotToolTip.Left + nInfoWidth + (DEF_TOOLTIP_XGAP * 2);
	m_rcWearSlotToolTip.Bottom = m_rcWearSlotToolTip.Top + nInfoHeight;
}

// ----------------------------------------------------------------------------
// Name : GetLocationOfNormalItem()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::GetLocationOfNormalItem(int nUniIndex, SWORD& nTab, SWORD& inven_idx)
{
	int		t, i, slot;

	for (t = 0; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
	{
		slot = GetCurTabSlotCount(t);

		for (i = 0; i < slot; ++i)
		{
			if (m_abtnItems[t][i]->getItems() == NULL)
				continue;

			if (m_abtnItems[t][i]->getItems()->Item_UniIndex == nUniIndex)
			{
				nTab = t;
				inven_idx = i;
				return;
			}
		}
	}

	nTab = -1;
	inven_idx = -1;
}

// ----------------------------------------------------------------------------
// Name : GetLocationOfNormalItem()
// Desc :
// ----------------------------------------------------------------------------
SQUAD CUIInventory::GetItemCount(int iItemIndex, bool bCompositionItem)
{
	__int64 sum = 0;
	int		t, i, slot;

	for (t = 0; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
	{
		slot = GetCurTabSlotCount(t);
		for (i = 0; i < slot; ++i)
		{
			if (_pNetwork->MySlotItem[t][i].Item_Index == iItemIndex)
			{
				if (bCompositionItem == false)
				{
					// �������� ��� ����
					if (_pNetwork->MySlotItem[t][i].Item_Flag & FLAG_ITEM_COMPOSITION)
						continue;
				}
				sum += _pNetwork->MySlotItem[t][i].Item_Sum;
			}
		}
	}

	return sum;
}

// ----------------------------------------------------------------------------
// Name : GetItemAll()
// Desc :
// ----------------------------------------------------------------------------
SQUAD CUIInventory::GetItemAll()
{
	SQUAD tv_num = 0;
	for (int i = 0; i < ITEM_COUNT_IN_INVENTORY_NORMAL; ++i)
	{
		if (_pNetwork->MySlotItem[0][i].IsEmptyItem() == FALSE)
		{
			tv_num++;
		}
	}

	return tv_num;
}

// ----------------------------------------------------------------------------
// Name : GetItemSlotInfo()
// Desc :
// ----------------------------------------------------------------------------
BOOL CUIInventory::GetItemSlotInfo(int iItemIndex, int& nTab, int& inven_idx)
{
	int		t, i, slot;

	for (t = 0; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
	{
		slot = GetCurTabSlotCount(t);

		for (i = 0; i < slot; ++i)
		{
			if (iItemIndex == _pNetwork->MySlotItem[t][i].Item_Index)
			{
				nTab = t;
				inven_idx = i;
				return TRUE;
			}
		}
	}

	return FALSE;
}

WMSG_RESULT CUIInventory::OnKeyMessage(MSG* pMsg)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->IsFocusAllEditBox();

	if (!pUIManager->IsFocusAllEditBox())
	{
		if (this->GetCurSelectItem() != NULL && this->GetCurSelectItem()->IsEmpty() == false) //dethunter12 Mod (no empty and non existent item ID)
		{
			if (pMsg->wParam == VK_DELETE)
			{
				ShowItemDestroyMessage();
				return WMSG_SUCCESS;
			}
		}
	}


	return CUIWindow::OnKeyMessage(pMsg);
}

// ----------------------------------------------------------------------------
// Name : MouseMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT CUIInventory::MouseMessage(MSG* pMsg)
{
	WMSG_RESULT	wmsgResult;

	// Title bar
	static BOOL bTitleBarClick = FALSE;

	// Item clicked
	static BOOL	bLButtonDownInItem = FALSE;

	// Mouse point
	static int	nOldX, nOldY;
	int	nX = LOWORD(pMsg->lParam);
	int	nY = HIWORD(pMsg->lParam);

	CUIIcon** btnWear = m_pIconsWearing;
	int iWearTotal = WEAR_TOTAL;

	if (m_iInventoryType == INVEN_TAB_COSTUME)
	{
		btnWear = m_pIconsCostumeWearing;
		iWearTotal = WEAR_COSTUME_TOTAL;
	}

	if (m_pEventActiveUI->IsVisible() && m_pEventActiveUI->IsInside(nX, nY))
	{
		m_pEventActiveUI->MouseMessage(pMsg);
	}
	else if (IsInside(nX, nY))
	{
		int xx = nX;
		int yy = nY;
		ConvertToWindow(xx, yy);
		if ((m_pEventActiveUI->IsVisible() && xx > (GetWidth() - m_pEventActiveUI->GetWidth()) && yy > m_pEventActiveUI->GetHeight()) ||
			(!m_pEventActiveUI->IsVisible() && xx > (GetWidth() - m_pEventActiveUI->GetWidth())))
		{
			return WMSG_FAIL;
		}
	}

	switch (pMsg->message)
	{
	case WM_MOUSEMOVE:
	{
		CUIManager* pUIManager = CUIManager::getSingleton();

		if (IsInside(nX, nY))
		{
			pUIManager->SetMouseCursorInsideUIs();
			CUITooltipMgr::getSingleton()->clearTooltip();
		}

		int	ndX = nX - nOldX;
		int	ndY = nY - nOldY;
		int nTab = ((m_InvenCurrentTab - INVEN_TAB_NORMAL4) > 0) ? (m_InvenCurrentTab - INVEN_TAB_NORMAL4) : 0;
		// Hold item button
		if (pUIManager->GetDragIcon() == NULL && bLButtonDownInItem &&
			(pMsg->wParam & MK_LBUTTON) && (ndX != 0 || ndY != 0))
		{
			if (!m_bLockInven)
			{
				// Wearing items
				if (m_nSelWearItemID >= 0)
				{
					// Close message box of inventory
					pUIManager->CloseMessageBox(MSGCMD_DROPITEM);
					if (m_iInventoryType == INVEN_TAB_GENERNAL)
					{
						pUIManager->SetHoldBtn(m_pIconsWearing[m_nSelWearItemID]);
					}
					else
					{
						pUIManager->SetHoldBtn(m_pIconsCostumeWearing[m_nSelWearItemID]);
					}

				}
				// Slot items
				else if (m_nSelSlotItemID[m_InvenCurrentTab] >= 0)
				{
					// Close message box of inventory
					pUIManager->CloseMessageBox(MSGCMD_DROPITEM);

					int	nSel = m_nSelSlotItemID[m_InvenCurrentTab];

					if (nTab == 0) {
						nSel += (m_InvenCurrentTab * INVEN_SLOT_ROW);
					}

					// 						pUIManager->SetHoldBtn( *m_abtnItems[nTab][nSel]->GetButton() );
					// 						int	nOffset = BTN_SIZE / 2;
					// 						pUIManager->GetHoldBtn().SetPos( nX - nOffset, nY - nOffset );
					pUIManager->SetHoldBtn(m_abtnItems[nTab][nSel]);

					if (pUIManager->DoesUIExist(UI_REFORM_SYSTEM))
					{
						// ���� �����̰� ���� �� ������ �̵��� �߻��� ��� �˻� �ϱ� ���� ���� �ش�. [9/6/2012 Ranma]
						pUIManager->GetReformSystem()->SendReformItemBtnInitUniIndex(_pNetwork->MySlotItem[nTab][nSel].Item_UniIndex);
					}
				}
			}

			bLButtonDownInItem = FALSE;
		}

		int i, nWhichTab = -1;
		for (i = 0; i < INVEN_TAB_TOTAL; ++i)
		{
			if (i == INVEN_TAB_NORMAL4) // ���� ��� ����
				continue;

			if (m_btnTab[i].MouseMessage(pMsg) != WMSG_FAIL)
			{
				nWhichTab = i;
			}
		}

		if (nWhichTab >= 0)
		{
			ShowToolTip(TRUE, nWhichTab);
			ShowWearGuideToolTip(FALSE);
			return WMSG_SUCCESS;
		}

		// Move inventory
		if (bTitleBarClick && (pMsg->wParam & MK_LBUTTON))
		{
			nOldX = nX;	nOldY = nY;

			Move(ndX, ndY);

			pUIManager->GetInventoryOptions()->Move(ndX, ndY);
			m_EventPopUp.Move(ndX, ndY);

			return WMSG_SUCCESS;
		}
		// Close button
		else if (m_btnClose.MouseMessage(pMsg) != WMSG_FAIL)
			return WMSG_SUCCESS;
		else if (m_btnTrashcan.MouseMessage(pMsg) != WMSG_FAIL)
			return WMSG_SUCCESS;
		else if (m_btnArrange.MouseMessage(pMsg) != WMSG_FAIL)
		{
			ShowArrangeToolTip(TRUE);
			return WMSG_SUCCESS;
		}
#ifdef ENABLE_INVISIBLE_HELMET
		else if (m_btnOptions.MouseMessage(pMsg) != WMSG_FAIL)
			return WMSG_SUCCESS;
#endif
		// Wearing items
		else if (m_btnInvenTab[INVEN_TAB_GENERNAL].MouseMessage(pMsg) != WMSG_FAIL)
		{
			ShowWearTabToolTip(TRUE, INVEN_TAB_GENERNAL);
			ShowWearGuideToolTip(FALSE);
			return WMSG_SUCCESS;
		}
		else if (m_btnInvenTab[INVEN_TAB_COSTUME].MouseMessage(pMsg) != WMSG_FAIL)
		{
			ShowWearTabToolTip(TRUE, INVEN_TAB_COSTUME);
			ShowWearGuideToolTip(FALSE);
			return WMSG_SUCCESS;
		}
		else
		{
			BOOL bShow = FALSE;
			int nToolTipPos = -1;

			for (int iWear = 0; iWear < iWearTotal; iWear++)
			{
				btnWear[iWear]->MouseMessage(pMsg);

				if (btnWear[iWear]->IsInside(nX, nY) && btnWear[iWear]->IsEmpty())
				{
					bShow = TRUE;
					nToolTipPos = iWear;
				}
			}

			ShowWearGuideToolTip(bShow, (eWEAR_TYPE)m_iInventoryType, nToolTipPos);

			for (int i = 0; i < INVEN_ONE_BAG; ++i)
			{
				m_abtnItems[nTab][i]->MouseMessage(pMsg);
			}

			ShowToolTip(FALSE);
		}

		if (IsInside(nX, nY))
			return WMSG_SUCCESS;
	}
	break;

	case WM_LBUTTONDOWN:
	{
		if (IsInside(nX, nY))
		{
			nOldX = nX;		nOldY = nY;

			// Close button
			if (m_btnClose.MouseMessage(pMsg) != WMSG_FAIL)
			{
				// Nothing
			}
			else if (m_btnTrashcan.MouseMessage(pMsg) != WMSG_FAIL)
			{

			}
			else if (m_btnArrange.MouseMessage(pMsg) != WMSG_FAIL)
			{
				// ���� ��ư ó��
			}
			else if (m_btnOptions.MouseMessage(pMsg) != WMSG_FAIL)
			{
			}
			// Wearing items
			else if (IsInsideRect(nX, nY, m_rcWearing))
			{
				m_nSelWearItemID = -1;
				m_nSelSlotItemID[m_InvenCurrentTab] = -1;

				CUIManager* pUIManager = CUIManager::getSingleton();

				for (int iWear = 0; iWear < iWearTotal; iWear++)
				{
					if (btnWear[iWear]->MouseMessage(pMsg) != WMSG_FAIL)
					{
						// Update selected item
						m_nSelWearItemID = iWear;

						SetCurSelectItem(btnWear[iWear]);
						UpdateSelectItem();

						bLButtonDownInItem = TRUE;

						pUIManager->RearrangeOrder(UI_INVENTORY, TRUE);
						return WMSG_SUCCESS;
					}
				}
			}
			// Slot items
			else if (IsInsideRect(nX, nY, m_rcItemSlot))
			{
				int nTab = ((m_InvenCurrentTab - INVEN_TAB_NORMAL4) > 0) ? (m_InvenCurrentTab - INVEN_TAB_NORMAL4) : 0;
				int	i;

				m_nSelWearItemID = -1;

				m_nSelSlotItemID[m_InvenCurrentTab] = -1;

				CUIManager* pUIManager = CUIManager::getSingleton();

				for (i = 0; i < INVEN_ONE_BAG; ++i)
				{
					if (m_bLockSelect == true)
						return WMSG_SUCCESS;

					// Update selected item
					if (m_abtnItems[nTab][i]->IsInside(nX, nY))
					{
						m_nSelSlotItemID[m_InvenCurrentTab] = i;
						SetCurSelectItem(m_abtnItems[nTab][i]);
						if (pMsg->wParam & MK_CONTROL)
						{
							CItems* pItems = m_abtnItems[nTab][i]->getItems();
							if (pItems && pItems->ItemData)
								CUIManager::getSingleton()->GetChattingUI()->GluingMessage(pItems);
						}
						UpdateSelectItem();
					}

					if (m_abtnItems[nTab][i]->MouseMessage(pMsg) != WMSG_FAIL)
					{
						bLButtonDownInItem = TRUE;

						if (pUIManager->GetInsectCollect()->GetHide() == FALSE)
						{// ���� ä�� ���ڴ� ������ �ݴ´�.
							pUIManager->RearrangeOrder(UI_INSECTCOLLECT, FALSE);
							pUIManager->GetInsectCollect()->Hide(TRUE);
						}

						pUIManager->RearrangeOrder(UI_INVENTORY, TRUE);
						return WMSG_SUCCESS;
					}
				}
			}
			else if (IsInsideRect(nX, nY, m_rcItemTypeTab[0]) || IsInsideRect(nX, nY, m_rcItemTypeTab[1]))
			{
				for (int i = 0; i < INVEN_TAB_TOTAL; ++i)
					m_btnTab[i].MouseMessage(pMsg);
			}
			else if (m_btnInvenTab[INVEN_TAB_GENERNAL].MouseMessage(pMsg) != WMSG_FAIL)
			{
				if (m_iInventoryType != INVEN_TAB_GENERNAL)
				{
					m_iInventoryType = INVEN_TAB_GENERNAL;
					m_nSelWearItemID = -1;
				}
			}
			else if (m_btnInvenTab[INVEN_TAB_COSTUME].MouseMessage(pMsg) != WMSG_FAIL)
			{
				if (m_iInventoryType != INVEN_TAB_COSTUME)
				{
					m_iInventoryType = INVEN_TAB_COSTUME;
					m_nSelWearItemID = -1;
				}
			}
			else if (IsInsideRect(nX, nY, m_rcTitle))
			{
				// Title bar
				bTitleBarClick = TRUE;
			}

			CUIManager::getSingleton()->RearrangeOrder(UI_INVENTORY, TRUE);
			return WMSG_SUCCESS;
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		bLButtonDownInItem = FALSE;
		CTString	strMessage;

		CUIManager* pUIManager = CUIManager::getSingleton();

		// If holding button doesn't exist
		if (pUIManager->GetDragIcon() == NULL)
		{
			// Title bar
			bTitleBarClick = FALSE;

			// If inventory isn't focused
			if (!IsFocused())
				return WMSG_FAIL;

			// Close button
			if ((wmsgResult = m_btnClose.MouseMessage(pMsg)) != WMSG_FAIL)
			{
				if (wmsgResult == WMSG_COMMAND)
				{
					ToggleVisible();
				}

				return WMSG_SUCCESS;
			}
			else if ((wmsgResult = m_btnTrashcan.MouseMessage(pMsg)) != WMSG_FAIL)
			{
				if (wmsgResult == WMSG_COMMAND &&
					m_InvenCurrentTab >= 0 && m_InvenCurrentTab <= INVEN_TAB_CASH6) // 4->6
				{
					if (m_pIconCurSelectItem != NULL && m_pIconCurSelectItem->IsEmpty() == false)
						ShowItemDestroyMessage();
				}

				return WMSG_SUCCESS;
			}
			else if ((wmsgResult = m_btnArrange.MouseMessage(pMsg)) != WMSG_FAIL)
			{
				if (wmsgResult == WMSG_COMMAND)
				{
					if (m_bLockArrange == TRUE)
					{
						ShowLockErrorMessage();
						return WMSG_SUCCESS;
					}

					if (pUIManager->DoesMessageBoxExist(MSGCMD_INVENTORY_ARRANGE))
						pUIManager->CloseMessageBox(MSGCMD_INVENTORY_ARRANGE);

					CTString strTitle;
					CTString strMessage1;
					CUIMsgBox_Info	MsgBoxInfo;

					strTitle = _S(191, "Ȯ��");
					strMessage1 = _S(6053, "�κ��丮�� ���� �Ͻðڽ��ϱ�?");
					MsgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_YESNO, UI_INVENTORY, MSGCMD_INVENTORY_ARRANGE);
					MsgBoxInfo.AddString(strMessage1);
					pUIManager->CreateMessageBox(MsgBoxInfo);

					Lock(TRUE, TRUE, LOCK_INVEN_ARRANGE);
				}
			}
#ifdef ENABLE_INVISIBLE_HELMET
			else if ((wmsgResult = m_btnOptions.MouseMessage(pMsg)) != WMSG_FAIL)
			{
				if (wmsgResult == WMSG_COMMAND)
				{
					BOOL isVisible = pUIManager->GetInventoryOptions()->IsVisible();
					if (isVisible)
					{
						pUIManager->GetInventoryOptions()->CloseUI();
					}
					else
					{
						nX = m_nPosX + m_nWidth + 2;
						nY = m_nPosY + m_nHeight - pUIManager->GetInventoryOptions()->GetHeight();
						pUIManager->GetInventoryOptions()->SetPos(nX, nY);
						pUIManager->GetInventoryOptions()->OpenUI();
					}
				}
			}
#endif
			// Item type tab
			else if (IsInsideRect(nX, nY, m_rcItemTypeTab[0]) || IsInsideRect(nX, nY, m_rcItemTypeTab[1]))
			{
				int i;

				for (i = 1; i < INVEN_TAB_TOTAL; ++i)
				{
					if (i == INVEN_TAB_NORMAL4)
						continue;

					if (m_btnTab[i].MouseMessage(pMsg) != WMSG_FAIL)
					{
						// UI���� [10/10/2012 Ranma]
						// Nothing
						int nIdx = 0;

						if (i >= INVEN_TAB_NORMAL1 && i < INVEN_TAB_NORMAL4)	// �⺻ �κ��丮 ������ ����.
							nIdx = eInvenSlot(i - 1);
						else if (i >= INVEN_TAB_CASH1 && i <= INVEN_TAB_CASH6) //4-6
							nIdx = eInvenSlot(i - 2);

						m_bSlot[nIdx] = !m_bSlot[nIdx];

						if (m_bSlot[nIdx] == TRUE)
							SetNewItemBagEffect(FALSE, (eInvenSlot)nIdx);

						//else if(i==INVEN_TAB_NORMAL2)
						//	m_bSlot[INVENSLOT_NUM2] = !m_bSlot[INVENSLOT_NUM2];	
						//else if(i==INVEN_TAB_NORMAL3)
						//	m_bSlot[INVENSLOT_NUM3] = !m_bSlot[INVENSLOT_NUM3];

						return WMSG_SUCCESS;
					}
				}
			}
			else if (m_btnInvenTab[INVEN_TAB_GENERNAL].MouseMessage(pMsg) != WMSG_FAIL)
			{
				m_btnInvenTab[INVEN_TAB_COSTUME].SetBtnState(UBS_IDLE);
				return WMSG_SUCCESS;
			}
			else if (m_btnInvenTab[INVEN_TAB_COSTUME].MouseMessage(pMsg) != WMSG_FAIL)
			{
				// Nothing
				return WMSG_SUCCESS;
			}
			// Wearing item
			else if (IsInsideRect(nX, nY, m_rcWearing))
			{
				for (int iWear = 0; iWear < iWearTotal; iWear++)
				{
					if (btnWear[iWear]->MouseMessage(pMsg) != WMSG_FAIL)
					{
						// Nothing
						return WMSG_SUCCESS;
					}
				}
			}
			// Slot items
			else if (IsInsideRect(nX, nY, m_rcItemSlot))
			{
				int	i;
				int nTab = ((m_InvenCurrentTab - INVEN_TAB_NORMAL4) > 0) ? (m_InvenCurrentTab - INVEN_TAB_NORMAL4) : 0;

				for (i = 0; i < INVEN_ONE_BAG; ++i)
					m_abtnItems[nTab][i]->MouseMessage(pMsg);

				return WMSG_SUCCESS;
			}
		}
		// If holding button exists
		else
		{
			if (IsInside(nX, nY))
			{
				CUIIcon* pDrag = pUIManager->GetDragIcon();

				if (pDrag == NULL)
					return WMSG_FAIL;

				CItems* pItems = pDrag->getItems();

				if (pItems == NULL)
					return WMSG_FAIL;

				// If holding button is item and comes from inventory
				if (pDrag->getBtnType() == UBET_ITEM &&
					pDrag->GetWhichUI() == UI_INVENTORY)
				{
					// Wearing items
					if (IsInsideRect(nX, nY, m_rcWearing))
					{
						// If this item is not equal to wearing item
						if (m_nSelWearItemID < 0 ||
							btnWear[m_nSelWearItemID]->getItems()->Item_UniIndex != pItems->Item_UniIndex)
						{
							int	nTab = pItems->Item_Tab;
							int nInvenIdx = pItems->InvenIndex;
							int	nIndex = pItems->Item_Index;
							int	nUniIndex = pItems->Item_UniIndex;

							CItemData* pItemData = pItems->ItemData;

							// Reset holding button
							pUIManager->ResetHoldBtn();

							// If holding item is refining stone
							int		iWear;
							if (pItemData->GetType() == CItemData::ITEM_ETC &&
								pItemData->GetSubType() == CItemData::ITEM_ETC_REFINE)
							{
								// �ڽ�Ƭ ���� ��ȭ���� �ʴ´�.
								if (m_iInventoryType == INVEN_TAB_COSTUME)
								{
									pUIManager->GetChattingUI()->AddSysMessage(_S(170, "���׷��̵� ���� �������� �ƴմϴ�."), SYSMSG_ERROR);
									return WMSG_SUCCESS;
								}

								for (iWear = 0; iWear < iWearTotal; iWear++)
								{
									if (!btnWear[iWear]->IsEmpty() &&
										btnWear[iWear]->IsInside(nX, nY))
										break;
								}

								// If holding item is not inside weapon or shield
								if (iWear == iWearTotal)
									return WMSG_SUCCESS;
								// Upgrade item
								UpgradeItem(iWear, btnWear[iWear]->getItems()->Item_UniIndex, nTab, nInvenIdx);
							}
							// ������ ������ & ��ȭ��.
							else if ((pItemData->GetType() == CItemData::ITEM_ETC &&
								pItemData->GetSubType() == CItemData::ITEM_ETC_OPTION)
								|| nIndex == 2361)	//�ǿ� ���� ����
							{
								for (iWear = 0; iWear < iWearTotal; iWear++)
								{
									if (!btnWear[iWear]->IsEmpty() &&
										btnWear[iWear]->IsInside(nX, nY))
									{
										break;
									}
								}

								// If holding item is not inside weapon or shield
								if (iWear == iWearTotal)
									return WMSG_SUCCESS;

								// Upgrade item
								SLONG	slLevel = pItems->Item_Flag;

								if (pItemData->GetOptionType() == CItemData::ITEM_OPTION_BLOOD
									|| nIndex == 2361)	//�ǿ� ���� ����
								{
									OptionAddItem(iWear, nIndex, nTab, nInvenIdx, pItems->Item_UniIndex);
								}
								else if (pItemData->GetOptionType() == CItemData::ITEM_OPTION_CLEAR)
								{
									OptionDelItem(iWear, nIndex, nTab, nInvenIdx, pItems->Item_UniIndex);
								}
							}
							else
							{
								// From item slot to wearing part ( only wearing items !!! )
								if (pItemData->GetWearingPosition() >= 0)
								{
									if (pItemData->GetSubType() == CItemData::ITEM_SHIELD_ONE_SUIT)
									{
										if (_pNetwork->MyCharacterInfo.bOneSuit == TRUE && _pNetwork->MyCharacterInfo.iOneSuitUniIndex == nUniIndex)
											break;
										else
											SendUseSlotItem(nTab, nInvenIdx);
									}
									else
									{
										// Check wearing
										for (iWear = 0; iWear < iWearTotal; iWear++)
										{
											if (btnWear[iWear]->getItems() != NULL &&
												btnWear[iWear]->getItems()->Item_UniIndex == nUniIndex)
												break;
										}

										// Not wearing now
										if (iWear == iWearTotal)
										{
											SendUseSlotItem(nTab, nInvenIdx);
										}
									}

									return WMSG_SUCCESS;
								}
							}
						}
					}
					// Slot items
					else if (IsInsideRect(nX, nY, m_rcItemSlot))
					{
						int	i;
						int nTab = ((m_InvenCurrentTab - INVEN_TAB_NORMAL4) > 0) ? (m_InvenCurrentTab - INVEN_TAB_NORMAL4) : 0;

						for (i = 0; i < INVEN_ONE_BAG; ++i)
						{
							if (m_abtnItems[nTab][i]->IsInside(nX, nY))
							{
								int nVIdx = pItems->Item_UniIndex;

								// �ѹ��ǻ��� ��� �ϳ��� �巡�� �ϸ�, vidx �� ����.
								if (nVIdx == -1 || nVIdx != _pNetwork->MySlotItem[nTab][i].Item_UniIndex)
								{
									// �巡������ �������� wear tab���� �����ߴٸ�
									if (pDrag->IsWearTab() == true)
									{
										if (m_iInventoryType == INVEN_TAB_COSTUME)
										{
											int nVirIdx = pItems->Item_UniIndex;
											CItemData* pItemData = _pNetwork->GetItemData(pDrag->getIndex());


											SBYTE subType = MSG_ITEM_WEAR_COSTUME_TAKEOFF;

											if (pItemData == NULL)
												return WMSG_SUCCESS;

											if (_pNetwork->MyCharacterInfo.bOneSuit == TRUE)
											{
												subType = MSG_ITEM_WEAR_COSTUME_SUIT_TAKEOFF;
											}

											if (m_bLockArrange == FALSE)
											{
												_pNetwork->SendItemWearingMSG(subType, pItems->Item_Wearing,
													nTab, i, 0, nVirIdx);
											}

										}
										else
										{
											if (m_bLockArrange == FALSE)
											{
												_pNetwork->SendItemWearingMSG(MSG_ITEM_WEAR_TAKE_OFF,
													pItems->Item_Wearing, nTab, i, 0);
											}
										}
									}
									else
									{
										// �巡������ �������� ĳ���κ��丮�� �ִ� �������̶��,
										// nTab�� i�� �Ϲ� �κ��丮�� �ִ� �������̸�, ���� �Ϸ��� �������� ���� ���������� �ƴ��� �˻� �ϱ� ���� ��ƾ.
										int nRetMovable = IsCashInvenMoveItem(pItems->Item_Tab, pItems->InvenIndex, nTab, i);

										if (nRetMovable > eERR_NONE)
										{
											ErrMessage(nRetMovable);
											pUIManager->ResetHoldBtn();
											return WMSG_SUCCESS;
										}

										if (pMsg->wParam & MK_SHIFT)
										{
											if (m_bLockArrange == FALSE)
											{
												if (IsDivideItem(pItems->Item_Tab, pItems->InvenIndex, nTab, i) == true)
												{
													ShowDivideMsgBox(0, i);
												}
											}
										}
										else
										{
											SendSwapSlotItems(pItems->Item_Tab, pItems->InvenIndex, nTab, i);
										}
									}
								}

								// Reset holding button
								pUIManager->ResetHoldBtn();

								return WMSG_SUCCESS;
							}
						}
					} // If - Slot items
					else if (IsInsideRect(nX, nY, m_rcItemTypeTab[0]))
					{
						int i;
						int tmpIndex;

						if (pItems->Item_Wearing < 0 && pItems->Item_Tab == ITEM_TAB_NORMAL)
						{
							for (i = 0; i < INVEN_TAB_NORMAL4; ++i)
							{
								if (m_btnTab[i].IsInside(nX, nY))
								{
									if (FindEmptyabtnItem(i, tmpIndex))
									{
										// UI���� �κ��丮 �߰����� [10/17/2012 Ranma]
										int tmpTab;
										tmpTab = tmpIndex / INVEN_ONE_BAG;
										if (tmpTab > 0)
										{
											if (!m_pInvenSlot[tmpTab - 1]->IsVisible())
												m_bSlot[tmpTab - 1] = TRUE;
										}

										SendSwapSlotItems(0, pItems->InvenIndex, 0, tmpIndex);
									}
									else
									{
										pUIManager->GetChattingUI()->AddSysMessage(_S(5783, "������ ������ �������� �̵���ų�� �����ϴ�."), SYSMSG_ERROR);
									}
									pUIManager->ResetHoldBtn();
									break;
								}
							}
						}
					}
					else if (m_btnTrashcan.IsInside(nX, nY))
					{
						ShowItemDestroyMessage();
						pUIManager->ResetHoldBtn();
					}
				}
				else if (pDrag->getBtnType() == UBET_ITEM &&
					pDrag->GetWhichUI() == UI_WARE_HOUSE)
				{
					// Slot items
					if (IsInsideRect(nX, nY, m_rcItemSlot))
					{
						pUIManager->GetWareHouseUI()->DelWareHouseItemToInventory();
					} // If - Slot items
				}
				else if (pDrag->getBtnType() == UBET_ITEM &&
					pDrag->GetWhichUI() == UI_WILDPET_INFO)
				{
					// Slot items
					if (IsInsideRect(nX, nY, m_rcItemSlot))
					{
						_pNetwork->SendUseWildPetItem(pItems->Item_Wearing, -1, -1, pItems->Item_Index);
					} // If - Slot items

				}
				// Reset holding button
				pUIManager->ResetHoldBtn();

				return WMSG_SUCCESS;
			} // If - IsInside
		} // If - If holding button doesn't exist
	}
	break;

	case WM_LBUTTONDBLCLK:
	{
		if (IsInside(nX, nY))
		{
			// Wearing item(Wearing�κ� ���� Ŭ����...)
			if (!m_bLockInven && IsInsideRect(nX, nY, m_rcWearing))
			{
				CUIManager* pUIManager = CUIManager::getSingleton();

				m_nSelWearItemID = -1;

				for (int iWear = 0; iWear < iWearTotal; iWear++)
				{
					if (btnWear[iWear]->MouseMessage(pMsg) == WMSG_COMMAND)
					{
						// Close message box of inventory
						pUIManager->CloseMessageBox(MSGCMD_DROPITEM);

						if (m_iInventoryType == INVEN_TAB_COSTUME)
						{
							if (btnWear[iWear]->getItems() == NULL)
								continue;

							int nVirIdx = btnWear[iWear]->getItems()->Item_UniIndex;
							CItemData* pItemData = btnWear[iWear]->getItems()->ItemData;
							SBYTE subType = MSG_ITEM_WEAR_COSTUME_TAKEOFF;

							if (pItemData == NULL)
								continue;

							if (_pNetwork->MyCharacterInfo.bOneSuit == TRUE)
							{
								subType = MSG_ITEM_WEAR_COSTUME_SUIT_TAKEOFF;
							}

							if (m_bLockArrange == FALSE)
							{
								_pNetwork->SendItemWearingMSG(subType, iWear, -1, -1, 0, nVirIdx);
							}
						}
						else
						{
							if (m_bLockArrange == FALSE)
							{
								_pNetwork->SendItemWearingMSG(MSG_ITEM_WEAR_TAKE_OFF, iWear, -1, -1, 0);
							}
						}

						return WMSG_SUCCESS;
					}
				}
			}
			// Slot items(������ �κ� ���� Ŭ����...)
			else if (!m_bLockInven && IsInsideRect(nX, nY, m_rcItemSlot))
			{
				m_nSelSlotItemID[m_InvenCurrentTab] = -1;

				int	i, tmpTab;
				tmpTab = ((m_InvenCurrentTab - INVEN_TAB_NORMAL4) > 0) ? (m_InvenCurrentTab - INVEN_TAB_NORMAL4) : 0;

				CUIManager* pUIManager = CUIManager::getSingleton();

				for (i = 0; i < INVEN_ONE_BAG; ++i)
				{
					if (m_abtnItems[tmpTab][i]->MouseMessage(pMsg) == WMSG_COMMAND)
					{
						// Close message box of inventory
						pUIManager->CloseMessageBox(MSGCMD_DROPITEM);

						// [090609: selo] : �������� Flag�� ����ƮFlag�� ��� �Ѵٸ�
						//					��ġ�� ����� ���� ��� ���� �ȿ� ���� ���� ������ 
						//					������ �޽����� ������ �ʴ´�.								
						if (IsRestritionItem(tmpTab, i))
						{
							// [090707: selo] : ������ �޽����� ������ ���� ��� ������ ��� ���� �޽��� �ڽ��� ���
							CTString strTitle;
							CTString strMessage1;
							CUIMsgBox_Info	MsgBoxInfo;

							strTitle = _S(191, "Ȯ��");
							strMessage1 = _S(4428, "���⼭�� ��� �� �� �����ϴ�");
							MsgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_OK, UI_NONE, MSGCMD_NULL);
							MsgBoxInfo.AddString(strMessage1);
							pUIManager->CreateMessageBox(MsgBoxInfo);

							return WMSG_SUCCESS;
						}


						// �̱�ȯ ���� (12.9) ����â�� Ȱ��ȭ �Ǿ� ���� ���� ����â���� �������� ���� 
						if (pUIManager->GetMix()->IsEnabled() && pUIManager->GetMix()->IsVisible())
						{
							pUIManager->SetHoldBtn(m_abtnItems[tmpTab][i]);
							pUIManager->GetMix()->SetMixItem();
						}
						else if (pUIManager->GetCompound()->IsEnabled() && pUIManager->GetCompound()->IsVisible())
						{
							pUIManager->SetHoldBtn(m_abtnItems[tmpTab][i]);
							pUIManager->GetCompound()->SetCompoundItem();
						}
						else if (pUIManager->GetGWMix()->IsEnabled() && pUIManager->GetGWMix()->IsVisible())
						{
							pUIManager->SetHoldBtn(m_abtnItems[tmpTab][i]);
							pUIManager->GetGWMix()->SetMixItem();
						}
						else
						{
							// [2012/04/20 : Sora]  �κ��丮 lock ���¿����� ����Ŭ����
							// SetUseItemSlotInfo�Լ��� �����Ͽ� ���� ���� �����۰�
							// ���̰� �߻�, �ش� ���� ����(ITS 8280)
							if (m_bLockArrange == FALSE)
							{
								SetUseItemSlotInfo(tmpTab, i);
								// ������ �κ��� ���� ���� Ŭ����...
								SendUseSlotItem(tmpTab, i);
							}
							else
							{
								ShowLockErrorMessage();
							}
						}

						return WMSG_SUCCESS;
					}
				}
			}
			return WMSG_SUCCESS;
		}
	}
	break;
	}



	return WMSG_FAIL;
}

// ----------------------------------------------------------------------------
// Name : ToggleVisible()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::ToggleVisible()
{
	int i;
	CInvenData* pInven = CInvenData::getSingleton();

	if (IsVisible())
	{
		g_iXPosInInventory = GetPosX();
		g_iYPosInInventory = GetPosY();

		ClearNewItemEffect();

		if (pInven != NULL)
			pInven->ResetRenderCount();

		for (i = 0; i < INVENTORY_TAB_MAX; ++i)
		{
			for (int j = 0; j < ITEM_COUNT_IN_INVENTORY_NORMAL; ++j)
			{
				if (m_abtnItems[i][j] == NULL)
					continue;

				m_abtnItems[i][j]->CloseProc();
			}
		}

		for (i = 0; i < WEAR_TOTAL; ++i)
			m_pIconsWearing[i]->CloseProc();

		for (i = 0; i < WEAR_COSTUME_TOTAL; ++i)
			m_pIconsCostumeWearing[i]->CloseProc();
#ifdef ENABLE_INVISIBLE_HELMET
		UIMGR()->GetInventoryOptions()->CloseUI();
#endif
	}
	else
	{
		SetPos(g_iXPosInInventory, g_iYPosInInventory);
		m_EventPopUp.InitPosition();

		for (i = 0; i < INVEN_ONE_BAG; i++)
		{
			SetStartEffectItem(i);
		}

		// �ƹ��͵� �������� �ʾҴٸ� ����Ʈ �̹��� �Ⱥ��̰� ó��.
		if (m_nSelSlotItemID < 0)
			UpdateSelectItem();
	}

	BOOL	bVisible = !IsVisible();
	CUIManager::getSingleton()->RearrangeOrder(UI_INVENTORY, bVisible);

	for (i = 0; i < INVENSLOT_MAX; i++)
	{
		if (m_bSlot[i])
		{
			if (i < INVENSLOT_CASH1)
				((CUIChildInvenSlot*)m_pInvenSlot[i])->ToggleVisible(bVisible);
			else if (i <= INVENSLOT_CASH6) //4-6
				dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[i])->ToggleVisible(bVisible);

			SetNewItemBagEffect(FALSE, (eInvenSlot)i);
		}
		else
		{
			SetStartEffectBag((eInvenSlot)i);
		}
	}
}


// ========================================================================= //
//                             Command functions                             //
// ========================================================================= //
static SBYTE	sbTempWearPos;
static SWORD	nTempTab1, nTempTab2;
static SLONG	nTempIndex1, nTempIndex2;
static SLONG	slTempPlus, slTempLevel;

// ----------------------------------------------------------------------------
// Name : UpgradeItem()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::UpgradeItem(SLONG nTargetPos, SLONG nTargetVirIndex, SWORD nRefineTab, SWORD nRefineIndex)
{
	// If inventory is already locked
	if (IsLocked() ||
		IsLockedArrange())
	{
		ShowLockErrorMessage();
		return;
	}

	CUIManager* pUIManager = CUIManager::getSingleton();

	// FIXME : ��ų����߿� ������ ������ ����ϸ�, ������ �ȿͼ� �κ��丮 ���� ��Ǯ����...
	if (((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsSkilling())
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(863, "��ų ����߿��� �������� ���׷��̵� �� �� �����ϴ�."), SYSMSG_ERROR);
		return;
	}

	if (pUIManager->IsCSFlagOn(CSF_TELEPORT))
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(925, "���� �̵��߿��� �������� ���׷��̵� �� �� �����ϴ�."), SYSMSG_ERROR);
		return;
	}

	CItems* pItems = &_pNetwork->MyWearItem[nTargetPos];
	CItemData* pItemData = pItems->ItemData;

	CItems* refineItems = &_pNetwork->MySlotItem[nRefineTab][nRefineIndex];
	CItemData* refineItemData = refineItems->ItemData;
	SLONG		slIndex = refineItems->Item_Index;
	SLONG		nUniIndex = refineItems->Item_UniIndex;
	SLONG		slRefineLevel = refineItems->Item_Flag;

	// If this item can not upgrade
	if (((refineItemData->GetNum0() != CItemData::REFINE_BOOSTER) &&
		!(pItemData->GetFlag() & ITEM_FLAG_UPGRADE) && !pItems->IsFlag(FLAG_ITEM_COMPOSITION)) ||
		pItems->IsFlag(FLAG_ITEM_LENT) || (pItemData->GetFlag() & ITEM_FLAG_COSTUME2)) // �뿩 �������� ���׷��̵� �ȵ�
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(170, "���׷��̵� ���� �������� �ƴմϴ�."), SYSMSG_ERROR);
		return;
	}

	SLONG	slWearPlus = pItems->Item_Plus;

	LONG lTmpComIndex = pItems->ComItem_index;

	if (pItems->IsFlag(FLAG_ITEM_COMPOSITION) && lTmpComIndex > 0)
	{
		BOOL bFind = FALSE;

		int t, i, slot;

		for (t = 0; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
		{
			slot = GetCurTabSlotCount(t);

			for (i = 0; i < slot; i++)
			{
				if (lTmpComIndex == _pNetwork->MySlotItem[t][i].Item_UniIndex)
				{
					pItems = &_pNetwork->MySlotItem[t][i];
					pItemData = pItems->ItemData;
					bFind = TRUE;
					break;
				}
			}

			if (bFind == TRUE)
				break;
		}

		if (!bFind) // ������ �ռ����� ��ũ�� �������� ã�� ���ߴ�.
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(170, "���׷��̵� ���� �������� �ƴմϴ�."), SYSMSG_ERROR);
			return;
		}
	}

	SLONG	slWearLevel = pItemData->GetLevel();

	// Check level
	if (slRefineLevel > 0 && slRefineLevel < slWearLevel)		// Normal refining stone
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(171, "������ ������ ���� �ʽ��ϴ�."), SYSMSG_ERROR);
		return;
	}

	const char* szItemName = _pNetwork->GetItemName(pItemData->GetItemIndex());

	CUIMsgBox_Info	MsgBoxInfo;
	CTString	strMessage, strTitle;
	DWORD style;
	int commandCode;
	BOOL bLock = TRUE;
	BOOL bProtected = FALSE;

	switch (refineItemData->GetNum0())
	{
	case CItemData::REFINE_BOOSTER://786: case 1283: case 1284: case  PLATINUM_BOOSTER_ITEM: // Boost items
	{
		if (!(pItems->ItemData->GetType() == CItemData::ITEM_WEAPON
			&& (pItems->ItemData->GetSubType() == CItemData::ITEM_WEAPON_MINING
				|| pItems->ItemData->GetSubType() == CItemData::ITEM_WEAPON_GATHERING
				|| pItems->ItemData->GetSubType() == CItemData::ITEM_WEAPON_CHARGE)
			))
		{
			strTitle.PrintF(_S(1673, "���� �Ұ�!!!"));
			strMessage.PrintF(_S(1783, "�ν��ʹ� ���굵������ ����� �� �ֽ��ϴ�."));
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
		else if (pItems->IsFlag(FLAG_ITEM_PLATINUMBOOSTER_ADDED) == 0 && slIndex == PLATINUM_BOOSTER_ITEM)
		{
			strTitle.PrintF(_S(1670, "����!!!"));
			strMessage.PrintF(_S(2640, "���� ������ �÷�Ƽ�� �ν��͸� �����Ͻðڽ��ϱ�?"));
			style = UMBS_YESNO;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REQ;
			bLock = TRUE;
			m_iItemServerIndex = nUniIndex;
		}
		else if (pItems->IsFlag(FLAG_ITEM_BOOSTER_ADDED) == 0 && slIndex == 786)
		{
			strTitle.PrintF(_S(1670, "����!!!"));
			strMessage.PrintF(_S(1784, "���� �ν��͸� ����Ͻðڽ��ϱ�?"));
			style = UMBS_YESNO;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REQ;
			bLock = TRUE;
			m_iItemServerIndex = nUniIndex;
		}
		else if (pItems->IsFlag(FLAG_ITEM_SILVERBOOSTER_ADDED) == 0 && slIndex == 1283)
		{
			strTitle.PrintF(_S(1670, "����!!!"));
			strMessage.PrintF(_S(2431, "���� ������ �ǹ� �ν��͸� �����Ͻðڽ��ϱ�?"));
			style = UMBS_YESNO;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REQ;
			bLock = TRUE;
			m_iItemServerIndex = nUniIndex;
		}
		else if (pItems->IsFlag(FLAG_ITEM_GOLDBOOSTER_ADDED) == 0 && slIndex == 1284)
		{
			strTitle.PrintF(_S(1670, "����!!!"));
			strMessage.PrintF(_S(2432, "���� ������ ��� �ν��͸� �����Ͻðڽ��ϱ�?"));
			style = UMBS_YESNO;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REQ;
			bLock = TRUE;
			m_iItemServerIndex = nUniIndex;
		}
		else
		{
			strTitle.PrintF(_S(1673, "���� �Ұ�!!!"));
			strMessage.PrintF(_S(1785, "�̹� �ν��͸� ����� ����Դϴ�.\n�ٸ� �����ۿ� ����Ͽ� �ֽʽÿ�."));
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
	}
	break;
	case CItemData::REFINE_SUPER_SPECIAL://779: // �ʰ������ü� ������
	{
		if (slWearPlus >= 14)
		{
			strTitle.PrintF(_S(1670, "����!!!"));
			strMessage.PrintF(_S(1671, "�� ���� ���ü��� +14�̻��� ��񿡴�\n����� �� �����ϴ�."));
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
		else if (pItems->IsFlag(FLAG_ITEM_BOOSTER_ADDED) == 0)
		{
			strTitle.PrintF(_S(1670, "����!!!"));
			strMessage.PrintF(_S(1672, "�� ���� ���ü��� �ϳ��� ���\n�ѹ��� ����� �� �ֽ��ϴ�.\n���� ����Ͻðڽ��ϱ�?"));
			style = UMBS_YESNO;
			commandCode = MSGCMD_INVEN_UPGRADE_REQ;
			bLock = TRUE;
		}
		else
		{
			strTitle.PrintF(_S(1673, "���� �Ұ�!!!"));
			strMessage.PrintF(_S(1674, "�� ���� ���ü��� �̹�\n����� ����Դϴ�.\n�ٸ� �����ۿ� ����� �ֽʽÿ�."));
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
	}
	break;
	case CItemData::REFINE_PLATINUM://1419: // �÷�Ƽ�� ���ü�
	{
		strTitle.PrintF(_S(191, "Ȯ��"));

		if (refineItemData->getindex() == 11109 && pItems->IsFlag(PLATINUM_MAX_PLUS)) {
			strMessage.PrintF(_S(8322, "Platinum Refining Stone will be removed. Do you want to use this item?"));
			style = UMBS_OKCANCEL;
			commandCode = MSGCMD_INVEN_UPGRADE_REQ;
			bLock = TRUE;
		}
		else if (refineItemData->getindex() == 11109) {
			strMessage.PrintF(_S(8323, "You cannot use this item. There is not Platinum Stone in this item."));
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
		else if (pItems->IsFlag(PLATINUM_MAX_PLUS)) {
			strMessage.PrintF(_S(2641, "�̹� �÷�Ƽ�� ���ü��� ������Դϴ�. �� �̻� ����� �� �����ϴ�."));
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
		else if (refineItemData->GetNum1() == 0 && slWearPlus > ITEM_MEX_LEVEL) {		// NUM 1 �� 0�ΰ�� ���� ���ü� ���
			strMessage.PrintF("%s%s", _S(2642, "�� �̻� ���׷��̵� �� �� �����ϴ�."),
				_S(5436, "������ ������ ����ؼ� ��� ���׷��̵带 �ϸ� ���� ��ġ �̻����� �ִ� +30���� ���׷��̵尡 �����մϴ�."));

			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
		else if (refineItemData->GetNum1() != 0 && slWearPlus >= refineItemData->GetNum1())		// �÷�Ƽ�� ������ ����
		{
			strMessage.PrintF(_S(2642, "�� �̻� ���׷��̵� �� �� �����ϴ�."));
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
		else
		{
			//16->17
			strMessage.PrintF(_S(2643, "�÷�Ƽ�� ���ü��� ���� ���׷��̵�� �ִ� +26�� ȿ���� ���ϴ�. ����Ͻðڽ��ϱ�?"));
			style = UMBS_OKCANCEL;
			commandCode = MSGCMD_INVEN_UPGRADE_REQ;
			bLock = TRUE;
		}
	}
	break;
	case 2051: // ������ ���� ���� ���� �ֹ���(�۾� ������ �κ�)
	{
		strTitle.PrintF(_S(191, "Ȯ��"));
		strMessage.PrintF(_S(3979, "[���������] '%s'�� ������ �������� ���Ҹ� ����Ͻðڽ��ϱ�?"), szItemName);
		style = UMBS_OKCANCEL;
		commandCode = MSGCMD_ITEM_LEVELDOWN_REQ;
		bLock = FALSE;
	}
	break;
	case CItemData::REFINE_CHAOS://2844: // ī���� ���ü�
	{
		if (slWearPlus > 11)
		{
			strTitle.PrintF(_S(1670, "����!!!"));
			strMessage.PrintF(_S(4134, "ī���� ���ü��� +12�̻��� ��񿡴� ����� �� �����ϴ�."));
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
		else
		{
			CTString strItemname;
			if (slWearPlus > 0)
				strItemname.PrintF("[%s +%d]", szItemName, slWearPlus);
			else
				strItemname.PrintF("[%s]", szItemName);

			strTitle.PrintF(_S(175, "������ ���׷��̵�"));
			strMessage.PrintF(_S(4135, "%s<��> ī���� ���ü��� ����Ͽ� ���׷��̵� �Ͻðڽ��ϱ�?"), strItemname);
			style = UMBS_OKCANCEL;
			commandCode = MSGCMD_INVEN_UPGRADE_REQ;
		}
	}
	break;
	case CItemData::REFINE_PURITY_RUNE: // ��ȭ�� ��
	case CItemData::REFINE_DEVIL_RUNE: // �Ǹ��� ��
	{
		if (pItemData->GetLevel() < RUNE_ITEM_LEVEL)
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(171, "������ ������ ���� �ʽ��ϴ�."), SYSMSG_ERROR);
			return;
		}

		if (slWearPlus >= ITEM_MAX_UPGRADE_RUNE)
		{
			strMessage.PrintF("%s%s", _S(2642, "���̻� ���׷��̵� �� �� �����ϴ�."),
				_S(5436, "������ ������ ����ؼ� ��� ���׷��̵带 �ϸ� ���� ��ġ �̻����� �ִ� +30���� ���׷��̵尡 �����մϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			return;
		}

		bLock = TRUE;
		strTitle.PrintF(_S(175, "������ ���׷��̵�"));
		style = UMBS_OKCANCEL;
		commandCode = MSGCMD_INVEN_UPGRADE_REQ;

		if (slWearPlus == 0)
		{
			strMessage.PrintF(_S2(4459, szItemName, "[%s]<��> ���׷��̵� �Ͻðڽ��ϱ�?"), szItemName);
		}
		else if (slWearPlus > 0 && slWearPlus <= 4)
		{
			strMessage.PrintF(_S2(4460, szItemName, "[%s +%d]<��> ���׷��̵� �Ͻðڽ��ϱ�?"), szItemName, slWearPlus);
		}
		else if (slWearPlus >= 5)
		{
			bProtected = TRUE;
			style |= UMBS_BUTTONEX;
			commandCode = MSGCMD_INVEN_UPGRADE_PROTECT_REQ;
			strMessage.PrintF(_S2(172, szItemName, "[%s +%d]<��> ���׷��̵� �Ͻðڽ��ϱ�? �����ϸ� �������� �ı��� �� �ֽ��ϴ�."), szItemName, slWearPlus);

			if (slWearPlus <= 14) // 14
			{
				if (pItemData->GetType() == CItemData::ITEM_WEAPON)
				{
					strMessage += _S(4496, "(������ �߰��� ���ݷ� 45�����)");
				}
				else if (pItemData->GetType() == CItemData::ITEM_SHIELD)
				{
					strMessage += _S(4497, "(������ �߰��� ���� 25�����)");
				}
			}
		}
	}
	break;
	case CItemData::REFINE_CHAOS_RUNE:
	{
		if (pItemData->GetLevel() < RUNE_ITEM_LEVEL)
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(171, "������ ������ ���� �ʽ��ϴ�."), SYSMSG_ERROR);
			return;
		}

		else if (slWearPlus > 11)
		{
			strTitle.PrintF(_S(1670, "����!!!"));
			strMessage.PrintF(_S(5724, "ī���� ���� +12�̻��� ��񿡴� ����� �� �����ϴ�."));
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
		else
		{
			CTString strItemname;
			if (slWearPlus > 0)
				strItemname.PrintF("[%s +%d]", szItemName, slWearPlus);
			else
				strItemname.PrintF("[%s]", szItemName);

			strTitle.PrintF(_S(175, "������ ���׷��̵�"));
			strMessage.PrintF(_S(5725, "%s�� ī���� ���� ����Ͽ� ���׷��̵� �Ͻðڽ��ϱ�?"), strItemname);
			style = UMBS_OKCANCEL;
			commandCode = MSGCMD_INVEN_UPGRADE_REQ;
		}
	}
	break;
	case CItemData::REFINE_SUPER_RUNE:		// �� ���� ��
	{
		if (pItemData->GetLevel() < RUNE_ITEM_LEVEL)
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(171, "������ ������ ���� �ʽ��ϴ�."), SYSMSG_ERROR);
			return;
		}
		else if (pItems->IsFlag(FLAG_ITEM_SUPER_RUNE_USED) == 0)
		{
			strTitle.PrintF(_S(1670, "����!!!"));
			strMessage.PrintF(_S(5728, "�� ���� ���� �ϳ��� ��� �ѹ��� ����� �� �ֽ��ϴ�. \n���� ����Ͻðڽ��ϱ�?"));
			style = UMBS_OKCANCEL;
			commandCode = MSGCMD_INVEN_UPGRADE_REQ;
			bLock = TRUE;
		}
		else
		{
			strTitle.PrintF(_S(1673, "���� �Ұ�!!!"));
			strMessage.PrintF(_S(5727, "�� ���� ���� �̹� ����� ����Դϴ�. �ٸ� �����ۿ� ����� �ֽʽÿ�. "));
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
	}
	break;

	case CItemData::REFINE_OPAL_RUNE:		// �� ���� ��
	{
		if (pItemData->GetLevel() < RUNE_ITEM_LEVEL)
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(171, "������ ������ ���� �ʽ��ϴ�."), SYSMSG_ERROR);
			return;
		}
#ifdef OPAL_MINUS_11132021
		else if (pItems->IsFlag(FLAG_ITEM_OPAL_MINUS_USED) == 0)
		{
			strTitle.PrintF(_S(1670, "����!!!"));
			strMessage.PrintF(_S(8530, "�� ���� ���� �ϳ��� ��� �ѹ��� ����� �� �ֽ��ϴ�. \n���� ����Ͻðڽ��ϱ�?"));
			style = UMBS_OKCANCEL;
			commandCode = MSGCMD_INVEN_UPGRADE_REQ;
			bLock = TRUE;
		}
#endif
		else
		{
			strTitle.PrintF(_S(1673, "���� �Ұ�!!!"));
			strMessage.PrintF(_S(5727, "�� ���� ���� �̹� ����� ����Դϴ�. �ٸ� �����ۿ� ����� �ֽʽÿ�. "));
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
	}
	break;
	case CItemData::REFINE_LETSPLAY_RUNE:
	{
		if (slWearPlus >= 20)
		{
			strMessage.PrintF("%s%s", _S(2642, "´õÀÌ»ó ¾÷±×·¹ÀÌµå ÇÒ ¼ö ¾ø½À´Ï´Ù."),
				_S(5436, "¸¶½ºÅÍ ½ºÅæÀ» »ç¿ëÇØ¼­ Àåºñ¸¦ ¾÷±×·¹ÀÌµå¸¦ ÇÏ¸é Á¦ÇÑ ¼öÄ¡ ÀÌ»óÀ¸·Î ÃÖ´ë +30±îÁö ¾÷±×·¹ÀÌµå°¡ °¡´ÉÇÕ´Ï´Ù."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			return;
		}

		bLock = TRUE;
		strTitle.PrintF(_S(175, "¾ÆÀÌÅÛ ¾÷±×·¹ÀÌµå"));
		style = UMBS_OKCANCEL;
		commandCode = MSGCMD_INVEN_UPGRADE_REQ;
		strMessage.PrintF(_S2(174, szItemName, "[%s]<¸¦> ¾÷±×·¹ÀÌµå ÇÏ½Ã°Ú½À´Ï±î? ½ÇÆÐÇÏ¸é ´É·ÂÄ¡°¡ »ó½ÂÇÏÁö ¾Ê½À´Ï´Ù."), szItemName);
	}
	break;
	case CItemData::REFINE_ENCHANT_RUNE:			// Val Add New Enchant Rune
	{
		if (pItemData->GetLevel() < RUNE_ITEM_LEVEL)
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(171, "������ ������ ���� �ʽ��ϴ�."), SYSMSG_ERROR);
			return;
		}

		else if (pItems->IsFlag(FLAG_ITEM_ENCHANTED_USED) == 0)
		{
			strTitle.PrintF(_S(1670, "����!!!"));
			strMessage.PrintF("Enchantment can only be used once per gear. Are you sure to use it?");
			style = UMBS_OKCANCEL;
			commandCode = MSGCMD_INVEN_UPGRADE_REQ;
			bLock = TRUE;
		}
		else
		{
			strTitle.PrintF(_S(1673, "���� �Ұ�!!!"));
			strMessage.PrintF("This equipment has already be enchanted or cannot be enchanted!");
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
	}
	break;
	case CItemData::REFINE_LUCKY_RUNE:			// ����� ��
	{
		if (pItemData->GetLevel() < RUNE_ITEM_LEVEL)
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(171, "������ ������ ���� �ʽ��ϴ�."), SYSMSG_ERROR);
			return;
		}

		if (slWearPlus > 5)
		{
			strTitle.PrintF(_S(1670, "����!!!"));
			strMessage.PrintF(_S(5729, "����� ���� +6�̻��� ��񿡴� ����� �� �����ϴ�."));
			style = UMBS_OK;
			commandCode = MSGCMD_BOOSTER_UPGRADE_REP;
			bLock = FALSE;
		}
		else
		{
			CTString strItemname;
			if (slWearPlus > 0)
				strItemname.PrintF("[%s +%d]", szItemName, slWearPlus);
			else
				strItemname.PrintF("[%s]", szItemName);

			strTitle.PrintF(_S(175, "������ ���׷��̵�"));
			strMessage.PrintF(_S(5730, "%s�� ����� ���� ����Ͽ� ���׷��̵� �Ͻðڽ��ϱ�? "), strItemname);
			style = UMBS_OKCANCEL;
			commandCode = MSGCMD_INVEN_UPGRADE_REQ;
		}
	}
	break;
	case CItemData::REFINE_GENERAL: // �Ϲ� ���ü�
	case CItemData::REFINE_SPECIAL: // ���� ���ü�
	case CItemData::REFINE_LUCKY: // ����� ���� ���ü�
	{
		if (slWearPlus >= ITEM_MEX_LEVEL)
		{
			strMessage.PrintF("%s%s", _S(2642, "���̻� ���׷��̵� �� �� �����ϴ�."),
				_S(5436, "������ ������ ����ؼ� ��� ���׷��̵带 �ϸ� ���� ��ġ �̻����� �ִ� +30���� ���׷��̵尡 �����մϴ�."));
			pUIManager->GetChattingUI()->AddSysMessage(strMessage, SYSMSG_ERROR);
			return;
		}

		bLock = TRUE;
		strTitle.PrintF(_S(175, "������ ���׷��̵�"));
		style = UMBS_OKCANCEL;
		commandCode = MSGCMD_INVEN_UPGRADE_REQ;

		// +3 ~
		if (slWearPlus > 2)
		{
			bProtected = TRUE;
			style |= UMBS_BUTTONEX;
			commandCode = MSGCMD_INVEN_UPGRADE_PROTECT_REQ;
			strMessage.PrintF(_S2(172, szItemName, "[%s +%d]<��> ���׷��̵� �Ͻðڽ��ϱ�? �����ϸ� �������� �ı��� �� �ֽ��ϴ�."), szItemName, slWearPlus);
		}
		// 0 ~ +2
		else if (slWearPlus > 0)
		{
			strMessage.PrintF(_S2(173, szItemName, "[%s +%d]<��> ���׷��̵� �Ͻðڽ��ϱ�? �����ϸ� �ɷ�ġ�� ������� �ʽ��ϴ�."), szItemName, slWearPlus);
		}
		// 0
		else
		{
			strMessage.PrintF(_S2(174, szItemName, "[%s]<��> ���׷��̵� �Ͻðڽ��ϱ�? �����ϸ� �ɷ�ġ�� ������� �ʽ��ϴ�."), szItemName);
		}
	}
	break;
	default:
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(170, "���׷��̵� ���� �������� �ƴմϴ�."), SYSMSG_ERROR);
		return;
	}
	}

	pUIManager->CloseMessageBox(MSGCMD_INVEN_UPGRADE_REQ);
	pUIManager->CloseMessageBox(MSGCMD_INVEN_UPGRADE_PROTECT_REQ);
	pUIManager->CloseMessageBox(MSGCMD_BOOSTER_UPGRADE_REP);

	// Create message box
	m_InLockItemInfo[IN_LOCK_REFINE].TartetWearPos = nTargetPos;
	m_InLockItemInfo[IN_LOCK_REFINE].TartetVirIdx = nTargetVirIndex;
	m_InLockItemInfo[IN_LOCK_REFINE].TargetItem_Plus = slWearPlus;
	m_InLockItemInfo[IN_LOCK_REFINE].UseInvenTab = nRefineTab;
	m_InLockItemInfo[IN_LOCK_REFINE].UseInvenIdx = nRefineIndex;
	m_InLockItemInfo[IN_LOCK_REFINE].UseItem_Level = slRefineLevel;

	MsgBoxInfo.SetMsgBoxInfo(strTitle, style, UI_INVENTORY, commandCode);
	MsgBoxInfo.AddString(strMessage);

	if (bProtected)
		MsgBoxInfo.SetBtnType(UBET_ITEM, -1, -1);

	if (pUIManager->CreateMessageBox(MsgBoxInfo))
	{
		if (bProtected)
			pUIManager->GetMessageBox(commandCode)->GetBtnOK().SetEnable(TRUE);

		// Lock inventory
		if (bLock)
			Lock(TRUE, bProtected, LOCK_UPGRADE_ITEM);
	}
}

// ----------------------------------------------------------------------------
// Name : OptionAddItem()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::OptionAddItem(SBYTE sbWearPos, SLONG slIndex, SWORD nTab, SWORD inven_idx, SLONG VirIdx)
{
	// If inventory is already locked
	if (IsLocked())
	{
		ShowLockErrorMessage();
		return;
	}

	CUIManager* pUIManager = CUIManager::getSingleton();

	// ���� ������ ��밡��
	// �Ǽ������� ����
	if (sbWearPos == WEAR_ACCESSORY1 || sbWearPos == WEAR_ACCESSORY2 ||
		sbWearPos == WEAR_ACCESSORY3 || sbWearPos == WEAR_PET)
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(170, "���׷��̵� ���� �������� �ƴմϴ�."), SYSMSG_ERROR);
		return;
	}

	CItems* pItems = &_pNetwork->MyWearItem[sbWearPos];

	if (pItems == NULL)
		return;

	// ���յ� �����ۿ� ��� �Ұ�
	if (pItems->IsFlag(FLAG_ITEM_COMPOSITION))
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(170, "���׷��̵� ���� �������� �ƴմϴ�."), SYSMSG_ERROR);
		return;
	}

	CItemData* pItemData = pItems->ItemData;

	if (pItemData == NULL)
		return;

	// ��� ������ �������� ��� ���Ұ�
	if ((pItemData->GetFlag() & ITEM_FLAG_ORIGIN) || (pItemData->GetFlag() & ITEM_FLAG_RARE))
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(170, "���׷��̵� ���� �������� �ƴմϴ�."), SYSMSG_ERROR);
		return;
	}

	// �ڽ�Ƭ �����ۿ� ��� �Ұ�
	if (pItemData->GetFlag() & ITEM_FLAG_COSTUME2)
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(170, "���׷��̵� ���� �������� �ƴմϴ�."), SYSMSG_ERROR);
		return;
	}

	// FIXME : ��ų����߿� ������ ������ ����ϸ�, ������ �ȿͼ� �κ��丮 ���� ��Ǯ����...
	if (((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsSkilling())
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(794, "��ų ����߿��� �ɼ��� ���� �� �����ϴ�."), SYSMSG_ERROR);
		return;
	}

	if (pUIManager->IsCSFlagOn(CSF_TELEPORT))
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(926, "���� �̵��߿��� �ɼ��� ���� �� �����ϴ�."), SYSMSG_ERROR);
		return;
	}

	SLONG	slWearLevel = pItemData->GetLevel();

	// Create message box
	pUIManager->CloseMessageBox(MSGCMD_INVEN_OPTION_ADD_REP);

	SLONG	slWearPlus = pItems->Item_Plus;
	m_InLockItemInfo[IN_LOCK_OPTION_ADD].TargetWear_Pos = sbWearPos;
	m_InLockItemInfo[IN_LOCK_OPTION_ADD].TartetVirIdx = pItems->Item_UniIndex;
	m_InLockItemInfo[IN_LOCK_OPTION_ADD].TargetItem_Plus = slWearPlus;
	m_InLockItemInfo[IN_LOCK_OPTION_ADD].UseInvenTab = nTab;
	m_InLockItemInfo[IN_LOCK_OPTION_ADD].UseInvenIdx = inven_idx;
	m_InLockItemInfo[IN_LOCK_OPTION_ADD].UseVirIdx = VirIdx;

	CTString	strMessage;

	const char* szItemName = _pNetwork->GetItemName(pItemData->GetItemIndex());
	// +1 ~
	if (slWearPlus > 0)
	{
		if (slIndex == 2361) //'�ǿ� ���� ����' �������� ��
			strMessage.PrintF(_S(3533, "[���������]�ǿ� ���� ������ ����� [%s +%d]�� �ɼ��� ���̽ðڽ��ϱ�?"), szItemName, slWearPlus);
		else
			strMessage.PrintF(_S(513, "[%s +%d]�� �ɼ��� ���̽ðڽ��ϱ�?"), szItemName, slWearPlus);
	}
	// 0
	else
	{
		if (slIndex == 2361) //'�ǿ� ���� ����' �������� ��
			strMessage.PrintF(_S(3534, "[���������]�ǿ� ���� ������ ����� [%s]�� �ɼ��� ���̽ðڽ��ϱ�?"), szItemName, slWearPlus);
		else
			strMessage.PrintF(_S(514, "[%s]�� �ɼ��� ���̽ðڽ��ϱ�?"), szItemName);
	}

	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo(_S(515, "������ �ɼ�"), UMBS_OKCANCEL,
		UI_INVENTORY, MSGCMD_INVEN_OPTION_ADD_REQ);
	MsgBoxInfo.AddString(strMessage);
	if (pUIManager->CreateMessageBox(MsgBoxInfo))
	{
		// Lock inventory
		Lock(TRUE, FALSE, LOCK_BLOOD_OPTION);
	}
}

// ----------------------------------------------------------------------------
// Name : OptionAddItem()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::OptionDelItem(SBYTE sbWearPos, SLONG slIndex, SWORD nTab, SWORD inven_idx, SLONG VirIdx)
{
	// If inventory is already locked
	if (IsLocked())
	{
		ShowLockErrorMessage();
		return;
	}

	CItems* pItems = &_pNetwork->MyWearItem[sbWearPos];
	CItemData* pItemData = pItems->ItemData;

	CUIManager* pUIManager = CUIManager::getSingleton();

	// FIXME : ��ų����߿� ������ ������ ����ϸ�, ������ �ȿͼ� �κ��丮 ���� ��Ǯ����...
	if (((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsSkilling())
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(795, "��ų ����߿��� �ɼ��� ������ �� �����ϴ�."), SYSMSG_ERROR);
		return;
	}

	if (pUIManager->IsCSFlagOn(CSF_TELEPORT))
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(927, "���� �̵��߿��� �ɼ��� ������ �� �����ϴ�."), SYSMSG_ERROR);
		return;
	}

	SLONG	slWearLevel = pItemData->GetLevel();

	// Create message box
	pUIManager->CloseMessageBox(MSGCMD_INVEN_OPTION_DEL_REP);

	SLONG	slWearPlus = pItems->Item_Plus;
	m_InLockItemInfo[IN_LOCK_OPTION_DEL].TargetWear_Pos = sbWearPos;
	m_InLockItemInfo[IN_LOCK_OPTION_DEL].TartetVirIdx = pItems->Item_UniIndex;
	m_InLockItemInfo[IN_LOCK_OPTION_DEL].TargetItem_Plus = slWearPlus;
	m_InLockItemInfo[IN_LOCK_OPTION_DEL].UseInvenTab = nTab;
	m_InLockItemInfo[IN_LOCK_OPTION_DEL].UseInvenIdx = inven_idx;
	m_InLockItemInfo[IN_LOCK_OPTION_DEL].UseVirIdx = VirIdx;

	CTString	strMessage;

	const char* szItemName = _pNetwork->GetItemName(pItemData->GetItemIndex());
	// +1 ~
	if (slWearPlus > 0)
	{
		strMessage.PrintF(_S(516, "[%s +%d]�� �ɼ��� �����Ͻðڽ��ϱ�?"), szItemName, slWearPlus);
	}
	// 0
	else
	{
		strMessage.PrintF(_S(517, "[%s]�� �ɼ��� �����Ͻðڽ��ϱ�?"), szItemName);
	}

	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo(_S(515, "������ �ɼ�"), UMBS_OKCANCEL,
		UI_INVENTORY, MSGCMD_INVEN_OPTION_DEL_REQ);
	MsgBoxInfo.AddString(strMessage);
	if (pUIManager->CreateMessageBox(MsgBoxInfo))
	{
		// Lock inventory
		Lock(TRUE, FALSE, LOCK_BLOOD_OPTION);
	}
}

// ----------------------------------------------------------------------------
// Name : MsgBoxCommand()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::MsgBoxCommand(int nCommandCode, BOOL bOK, CTString& strInput)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	switch (nCommandCode)
	{
	case MSGCMD_BOOSTER_UPGRADE_REQ:
		if (bOK)
		{
			if (((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsSkilling())
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(863, "��ų ����߿��� �������� ���׷��̵� �� �� �����ϴ�."), SYSMSG_ERROR);
				Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
			}
			else if (pUIManager->IsCSFlagOn(CSF_TELEPORT))
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(925, "���� �̵��߿��� �������� ���׷��̵� �� �� �����ϴ�."), SYSMSG_ERROR);
				Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
			}
			else
				_pNetwork->SendBoosterUpgrade(m_iItemServerIndex);
		}
		else
			Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
		break;

	case MSGCMD_INVEN_UPGRADE_REQ:
		if (bOK)
		{
			if (((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsSkilling())
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(863, "��ų ����߿��� �������� ���׷��̵� �� �� �����ϴ�."), SYSMSG_ERROR);
				Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
			}
			else if (pUIManager->IsCSFlagOn(CSF_TELEPORT))
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(925, "���� �̵��߿��� �������� ���׷��̵� �� �� �����ϴ�."), SYSMSG_ERROR);
				Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
			}
			else
				SendUpgradeItem();
		}
		else
			Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
		break;

	case MSGCMD_INVEN_OPTION_ADD_REQ:
		if (bOK)
		{
			if (((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsSkilling())
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(794, "��ų ����߿��� �ɼ��� ���� �� �����ϴ�."), SYSMSG_ERROR);
				Lock(FALSE, FALSE, LOCK_BLOOD_OPTION);
			}
			else if (pUIManager->IsCSFlagOn(CSF_TELEPORT))
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(926, "���� �̵��߿��� �ɼ��� ���� �� �����ϴ�."), SYSMSG_ERROR);
				Lock(FALSE, FALSE, LOCK_BLOOD_OPTION);
			}
			else
				SendOptionAddItem();
		}
		else
			Lock(FALSE, FALSE, LOCK_BLOOD_OPTION);
		break;

	case MSGCMD_INVEN_OPTION_DEL_REQ:
		if (bOK)
		{
			if (((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsSkilling())
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(795, "��ų ����߿��� �ɼ��� ������ �� �����ϴ�."), SYSMSG_ERROR);
				Lock(FALSE, FALSE, LOCK_BLOOD_OPTION);
			}
			else if (pUIManager->IsCSFlagOn(CSF_TELEPORT))
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(927, "���� �̵��߿��� �ɼ��� ������ �� �����ϴ�."), SYSMSG_ERROR);
				Lock(FALSE, FALSE, LOCK_BLOOD_OPTION);
			}
			else
				SendOptionDelItem();
		}
		else
			Lock(FALSE, FALSE, LOCK_BLOOD_OPTION);
		break;


		// wooss 070305 --------------------------------------------------->>
		// kw : WSS_WHITEDAY_2007
	case MSGCMD_WHITEDAY_BLUELETTER:
		if (bOK)
		{
			// TODO : Send blue,pink letter message
			COLOR colMsg(0x5EB9FFFF);
			CTString tStr = pUIManager->GetMessageBox(nCommandCode)->GetInputBox().GetString();
			_pNetwork->SendWhiteday2007Letter(BLUE_LETTER_ITEM, colMsg, tStr);

		}
		break;
	case MSGCMD_WHITEDAY_PINKLETTER:
		if (bOK)
		{
			// TODO : Send blue,pink letter message
			COLOR colMsg(0xFF96C2FF);
			CTString tStr = pUIManager->GetMessageBox(nCommandCode)->GetInputBox().GetString();
			_pNetwork->SendWhiteday2007Letter(PINK_LETTER_ITEM, colMsg, tStr);

		}
		break;


		//------------------------------------------------------------------<<
	case MSGCMD_ITEM_LEVELDOWN_REQ:
		if (bOK)
		{
			if (((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsSkilling())
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(3980, "��ų ����߿��� ������ �������� ���Ҹ� �� �� �����ϴ�."), SYSMSG_ERROR);
				Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
			}
			else if (pUIManager->IsCSFlagOn(CSF_TELEPORT))
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(3981, "���� �̵��߿��� ������ �������� ���Ҹ� �� �� �����ϴ�."), SYSMSG_ERROR);
				Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
			}
			else
				SendItemLvDown();
		}
		else
			Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
		break;

		// [070820: Su-won] REFINE_PROTECT
	case MSGCMD_INVEN_UPGRADE_PROTECT_REQ:
	{
		if (bOK)
		{
			if (((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsSkilling())
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(863, "��ų ����߿��� �������� ���׷��̵� �� �� �����ϴ�."), SYSMSG_ERROR);
				Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
			}
			else if (pUIManager->IsCSFlagOn(CSF_TELEPORT))
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(925, "���� �̵��߿��� �������� ���׷��̵� �� �� �����ϴ�."), SYSMSG_ERROR);
				Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
			}
			else
			{
				CUIIcon* pIcon = pUIManager->GetMessageBox(MSGCMD_INVEN_UPGRADE_PROTECT_REQ)->GetBtnEx();

				if (pIcon != NULL)
				{
					int iItemIndex = pIcon->getIndex();
					SendUpgradeItem(iItemIndex);
				}
				else
					SendUpgradeItem();
			}
		}
		else
			Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);

		break;
	}
	// [071122: Su-won] NEW_MOONSTONE
	case MSGCMD_MOONSTONE_MIX:
	{
		if (bOK)
		{
			pUIManager->GetMessageBox(MSGCMD_MOONSTONE_MIX)->GetColorBox().Start(0, 2);
		}
		else
			pUIManager->CloseMessageBox(MSGCMD_MOONSTONE_MIX);
	}
	break;
	case MSGCMD_PETTRANSFORM_RU:
	{
		if (bOK)
		{
			int nUniIndex;
			int tv_tab, tv_idx;

			pUIManager->GetMessageBox(MSGCMD_PETTRANSFORM_RU)->GetBtnUseItemInfo(tv_tab, tv_idx, nUniIndex);
			CItems& ItemsBtn = _pNetwork->MySlotItem[tv_tab][tv_idx];

			_pNetwork->SendItemUse(ItemsBtn.Item_Tab, ItemsBtn.InvenIndex, ItemsBtn.Item_UniIndex, 0);
		}

		pUIManager->CloseMessageBox(MSGCMD_PETTRANSFORM_RU);
	}
	break;

	case MSGCMD_EXPRESS_REMOTE_ITEMUSE:
	{
		if (bOK)
		{
			int nUniIndex;
			int tv_tab, tv_idx;

			pUIManager->GetMessageBox(MSGCMD_EXPRESS_REMOTE_ITEMUSE)->GetBtnUseItemInfo(tv_tab, tv_idx, nUniIndex);
			CItems& ItemsBtn = _pNetwork->MySlotItem[tv_tab][tv_idx];

			_pNetwork->SendItemUse(ItemsBtn.Item_Tab, ItemsBtn.InvenIndex, ItemsBtn.Item_UniIndex, 0);
		}

		pUIManager->CloseMessageBox(MSGCMD_EXPRESS_REMOTE_ITEMUSE);
	}
	break;

	case MSGCMD_PET_STASH_USEITEM:
	{
		if (bOK)
		{
			int nUniIndex;
			int tv_tab, tv_idx;

			pUIManager->GetMessageBox(MSGCMD_PET_STASH_USEITEM)->GetBtnUseItemInfo(tv_tab, tv_idx, nUniIndex);
			CItems& ItemsBtn = _pNetwork->MySlotItem[tv_tab][tv_idx];

			_pNetwork->SendItemUse(ItemsBtn.Item_Tab, ItemsBtn.InvenIndex, ItemsBtn.Item_UniIndex, 0);
		}

		pUIManager->CloseMessageBox(MSGCMD_PET_STASH_USEITEM);
	}
	break;

	case MSGCMD_PRESSCORPS:
	{
		int tv_tab, tv_idx;
		pUIManager->GetInventory()->GetUseItemSlotInfo(tv_tab, tv_idx);
		CItems& Items = _pNetwork->MySlotItem[tv_tab][tv_idx];
		_pNetwork->SendPresscorpsMessage(Items.Item_UniIndex, strInput);

		pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_PRESSCORPS);
	}
	break;
	case MSGCMD_ITEMDELETE:
	{
		if (bOK)
		{
			if (m_pIconCurSelectItem != NULL)
			{
				CItems* pItems = m_pIconCurSelectItem->getItems();

				if (pItems != NULL)
				{
					if (pItems->IsEmptyItem() == TRUE)
						return;

					_pNetwork->SendItemDelete(pItems->Item_Tab, pItems->InvenIndex,
						pItems->Item_UniIndex, pItems->Item_Sum);
				}
			}

			m_pIconCurSelectItem = NULL;
		}
		m_bLockSelect = false;

		Lock(FALSE, FALSE, LOCK_INVEN_ITEM_DEL);
		pUIManager->CloseMessageBox(MSGCMD_ITEMDELETE);
	}
	break;
	// [2010/10/20 : Sora] ���� �뺴 ī��
	case MSGCMD_MONSTER_MERCENARY_CARD_USE:
	case MSGCMD_MONSTER_MERCENARY_CARD_HOLDER_USE:
	{
		if (bOK)
		{
			int tv_tab, tv_idx;
			GetUseItemSlotInfo(tv_tab, tv_idx);
			_pNetwork->UseSlotItem(tv_tab, tv_idx);
		}
	}
	break;
	// [2012/07/05 : Sora]  ĳ���� ���� Ȯ�� ������
	case MSGCMD_CHAR_SLOT_EXTEND:
	{
		if (bOK)
		{
			int tv_tab, tv_idx;
			GetUseItemSlotInfo(tv_tab, tv_idx);
			_pNetwork->UseSlotItem(tv_tab, tv_idx);
		}
	}
	break;

	case MSGCMD_INVEN_DIVIDE:
	{
	}
	break;

	case MSGCMD_INVENTORY_ARRANGE:
	{
		if (bOK)
		{
			SendSortInventory();
		}

		Lock(FALSE, FALSE, LOCK_INVEN_ARRANGE);
	}
	break;

	case MSGCMD_ATTENDANCE_ITEM_USE:
	{
		if (bOK)
		{
			int nUniIndex;
			int tv_tab, tv_idx;

			pUIManager->GetMessageBox(MSGCMD_ATTENDANCE_ITEM_USE)->GetBtnUseItemInfo(tv_tab, tv_idx, nUniIndex);
			CItems& ItemsBtn = _pNetwork->MySlotItem[tv_tab][tv_idx];

			_pNetwork->SendItemUse(ItemsBtn.Item_Tab, ItemsBtn.InvenIndex, ItemsBtn.Item_UniIndex, 0);
		}

		pUIManager->CloseMessageBox(MSGCMD_ATTENDANCE_ITEM_USE);
	}
	break;

#ifdef PREMIUM_CHAR
	case MSGCMD_PREMIUM_CHAR_ITEM_USE:
	{
		if (bOK)
		{
			int nUniIndex;
			int tv_tab, tv_idx;

			pUIManager->GetMessageBox(MSGCMD_PREMIUM_CHAR_ITEM_USE)->GetBtnUseItemInfo(tv_tab, tv_idx, nUniIndex);
			CItems& ItemsBtn = _pNetwork->MySlotItem[tv_tab][tv_idx];

			_pNetwork->SendPremiumCharItemUse(ItemsBtn.Item_Tab, ItemsBtn.InvenIndex, ItemsBtn.Item_UniIndex);
		}

		pUIManager->CloseMessageBox(MSGCMD_PREMIUM_CHAR_ITEM_USE);
	}
	break;
#endif	//	PREMIUM_CHAR
	}
}

// ========================================================================= //
//                           Send message functions                          //
// ========================================================================= //

// ----------------------------------------------------------------------------
// Name : SendArrangeItems()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::SendArrangeItem()
{
	// If inventory is locked
	if (IsLocked())
		return;

	// If arrange button is locked
	if (m_bLockArrange)
		return;

	// If current tab is not normal item
//	if( m_nCurItemTab != ITEM_TAB_NORMAL )
//		return;

	CUIManager* pUIManager = CUIManager::getSingleton();

	if (pUIManager->GetInsectCollect()->IsVisible())
	{// ���� ä�� ���ڴ� ������ �ݴ´�.
		pUIManager->RearrangeOrder(UI_INSECTCOLLECT, FALSE);
	}

	// Initialize selected items
//	m_nSelWearItemID = -1;
//	m_nSelSlotItemID[m_nCurItemTab] = -1;

//	_pNetwork->ArrangeItem( m_nCurItemTab );
}

// ----------------------------------------------------------------------------
// Name : SendUseSlotItem()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::SendUseSlotItem(int nTab, int inven_idx, SBYTE sbWearType)
{
	// If arrange button is locked
	if (m_bLockArrange)
		return;

	CUIManager* pUIManager = CUIManager::getSingleton();

	if (pUIManager->IsCSFlagOn(CSF_TELEPORT))
		return;

	SQUAD llTerm = _pTimer->GetHighPrecisionTimer().GetMilliseconds() - _pNetwork->MySlotItem[nTab][inven_idx].GetUseItemStartTime();

	if (llTerm > 500)
	{
		_pNetwork->MySlotItem[nTab][inven_idx].SetUseItemStartTime(_pTimer->GetHighPrecisionTimer().GetMilliseconds());
	}
	else
	{
		return;
	}// 0.5�� ���̿� ���� ��ư�� �����ٸ� return;

// 	if (m_abtnItems[nTab][inven_idx].GetSkillDelay())
// 	{
// 		return;
//	}

	CEntity* penPlEntity;
	CPlayerEntity* penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity(0);
	penPlayerEntity = static_cast<CPlayerEntity*>(penPlEntity);
	if (penPlayerEntity->IsSkilling())
		return;

	if (penPlayerEntity->IsSocialActing())
	{
		if (_pNetwork->MySlotItem[nTab][inven_idx].Item_Wearing == WEAR_WEAPON)
			return;
	}

	CItems* pItems = &_pNetwork->MySlotItem[nTab][inven_idx];
	CItemData* pItemData = pItems->ItemData;

	if (pItemData == NULL)
		return;

	ObjInfo* pInfo = ObjInfo::getSingleton();
	CPetTargetInfom* pPetInfo = pInfo->GetMyPetInfo();

	// ������ ��Ÿ�� �˻�
	DOUBLE dStartTime = 0;
	DOUBLE dCoolTime;
	DOUBLE dReUseTime = 0.0;

	dStartTime = pItems->ItemData->StartTime;
	dReUseTime = MY_INFO()->GetReuseItem(pItems->Item_Index);
	dCoolTime = ItemHelp::GetCoolTime(dReUseTime, dStartTime);

	if (dCoolTime > 0.0)
		return;

	if (pItemData->CanUse(_pNetwork->MyCharacterInfo.job) == FALSE &&
		pItemData->CanUse(WILDPET_JOB) == FALSE)
	{
		CTString str;
		str.PrintF(_S(6085, "%s�� ��� �� �� ���� ������ �Դϴ�."), UtilHelp::getSingleton()->GetClassName((eJob)_pNetwork->MyCharacterInfo.job));
		pUIManager->GetChattingUI()->AddSysMessage(str, SYSMSG_ERROR);

		return;
	}

	if (_pNetwork->m_bSingleMode == TRUE && pItemData->GetFlag() & ITEM_FLAG_NOTSINGLE)
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(6206, "�۽��� ���������� ����� �� �����ϴ�."), SYSMSG_ERROR);
		return;
	}

	// 	if (_pNetwork->IsRvrZone() && pItemData->GetType() & ITEM_FLAG_NONRVR)
	// 	{
	// 		pUIManager->GetChattingUI()->AddSysMessage( _S( 4742, "�� �������� ���� �������� ��� �� �� �����ϴ�."  ), SYSMSG_ERROR );	
	// 		return;
	// 	}

		// [2013/02/13] sykim70 Fortune System
	if (pItemData->GetType() == CItemData::ITEM_SHIELD &&
		pItemData->GetSubType() == CItemData::ITEM_SHIELD_ONE_SUIT &&
		pItemData->GetFortuneIndex() > 0 &&
		pItems->Item_Plus == 0)
	{
		((CUIFortune*)CUIManager::getSingleton()->GetUI(UI_FORTUNE))->OpenFortune(nTab, inven_idx);
		return;
	}

	const int iFame = pItemData->GetFame();		// ����ġ�� ���� �ִ� ������.
	if (iFame > 0 && iFame > _pNetwork->MyCharacterInfo.fame)
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(1187, "����ġ�� �����Ͽ� �������� ����� �� �����ϴ�."), SYSMSG_ERROR);
		return;
	}

	if ((penPlayerEntity->IsTransforming() || penPlayerEntity->IsPolymophing() || penPlayerEntity->IsSocialActing()) &&
		(pItemData->GetType() == CItemData::ITEM_WEAPON || pItemData->GetType() == CItemData::ITEM_SHIELD))//���Ż����ε� ����,������ �����Ϸ��� �Ѵٸ�,
	{
		return;
	}

	// ������ ���� ������ job �÷��װ� Total_job ��ġ�� �Ǿ�����
	if ((pItemData->GetType() == CItemData::ITEM_WEAPON || pItemData->GetType() == CItemData::ITEM_SHIELD) && pItemData->CanUse(WILDPET_JOB))
	{
		_pNetwork->SendUseWildPetItem(pItemData->GetWearingPosition(), nTab, inven_idx, pItemData->GetItemIndex());
		return;
	}

	if (pItemData->IsFlag(ITEM_FLAG_RARE))
	{
		int nNeedLevel = pItemData->GetLevel();

		int nJewelReduction = pItems->GetJewelLevelReduction();
		int nWearReduction = pItems->GetWearLevelReduction();

		// �����̾� ĳ������ ���.

		switch (GAMEDATAMGR()->GetPremiumChar()->getType())
		{
		case PREMIUM_CHAR_TYPE_FIRST:
		{
			int nLvDown = nJewelReduction + nWearReduction;

			if (nLvDown < DEF_PC1_LEVEL_DOWN)
				nNeedLevel -= DEF_PC1_LEVEL_DOWN;
			else
				nNeedLevel -= nLvDown;
		}
		break;

		default:
			nNeedLevel -= (nJewelReduction + nWearReduction);
			break;
		}

		if (_pNetwork->MyCharacterInfo.level < nNeedLevel)
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(3183, "������ �����Ͽ� �������� ������ �� �����ϴ�."), SYSMSG_ERROR);
			return;
		}
	}

	if (pItemData->IsFlag(ITEM_FLAG_CASTLLAN))
	{
		//���� ��Ʈ�� ����(0),����(1) ����
		//���� ��Ʈ�� ������ �ε���
		int nLordPos = HIWORD(pItemData->GetNum3());
		int nLordZone = LOWORD(pItemData->GetNum3());

		if (_pNetwork->MyCharacterInfo.ubGuildNameColor == 0)
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(3743, "���� ��尡 �ƴմϴ�."), SYSMSG_ERROR);
			return;

		}
		else
		{

			if (_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS)
			{

				if (nLordPos != 0)
				{
					pUIManager->GetChattingUI()->AddSysMessage(_S(5114, "���ָ� ������ ������ �������Դϴ�."), SYSMSG_ERROR);
					return;
				}

			}
			else
			{
				if (nLordPos != 1)
				{
					pUIManager->GetChattingUI()->AddSysMessage(_S(2179, "���� ������ ���� �ʽ��ϴ�."), SYSMSG_ERROR);
					return;
				}
			}

			if (!(_pNetwork->MyCharacterInfo.ubGuildNameColor == 2 && nLordZone == 4) &&
				!(_pNetwork->MyCharacterInfo.ubGuildNameColor == 1 && nLordZone == 7))
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(2179, "���� ������ ���� �ʽ��ϴ�."), SYSMSG_ERROR);
				return;
			}
		}
	}

#ifdef PREMIUM_CHAR
	if (pItemData->getindex() == PREMIUM_CHAR_ITEM_INDEX)
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_PREMIUM_CHAR_ITEM_USE))
			pUIManager->CloseMessageBox(MSGCMD_PREMIUM_CHAR_ITEM_USE);

		CTString strMessage, strTitle;
		CUIMsgBox_Info msgBoxInfo;
		strTitle.PrintF(_S(191, "Ȯ��"));

		if (GAMEDATAMGR()->GetPremiumChar()->getType() != PREMIUM_CHAR_TYPE_NONE)
		{
			msgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_OK, UI_NONE, MSGCMD_PREMIUM_CHAR_ITEM_USE);
			strMessage.PrintF(_S(6322, "�����̾� ������ �̹� ����Ǿ� �־� ��� �� �� �����ϴ�."));
			msgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(msgBoxInfo);
			return;
		}

		msgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_OKCANCEL, UI_INVENTORY, MSGCMD_PREMIUM_CHAR_ITEM_USE);
		strMessage.PrintF(_S(6321, "�����̾� ������ ����� ĳ���Ϳ� ���Ͽ� 30�ϵ��ȸ� �����Ǹ�, ������ ĳ�� ������ ��ɰ� �ߺ��ǰų� ��� �Ⱓ�� ������� �ʽ��ϴ�. �����̾� ĳ���� ��Ű���� ����Ͽ� �����̾� ������ �����ðڽ��ϱ�?"));
		msgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(msgBoxInfo);
		pUIManager->GetMessageBox(MSGCMD_PREMIUM_CHAR_ITEM_USE)->SetInvenUseItemInfo(nTab, inven_idx);
		return;
	}
#endif	//	PREMIUM_CHAR

	// Date : 2006-06-28(���� 4:40:57), By eons
	// �̺�Ʈ ������ ��� üũ( ���� ä�� ���� )
	if (pItemData->GetItemIndex() == 1577 || pItemData->GetItemIndex() == 1578)
	{
		pUIManager->GetInsectCollect()->OpenUI(nTab, inven_idx);
		return;
	}

	if (pItemData->GetItemIndex() == 2047 || pItemData->GetItemIndex() == 2633) // ���� �������� , ���� �Ҹ�����
	{
		pUIManager->GetBingoBox()->OpenBingoBox(nTab, inven_idx);
		return;
	}

	if (pUIManager->GetPortal()->IsWarpItem(pItemData->GetItemIndex()))
	{ // ���̵� �ֹ���
		pUIManager->GetPortal()->SetUseItem(TRUE);
		pUIManager->GetPortal()->SetUniItemIndex(pItems->Item_UniIndex);
		pUIManager->GetPortal()->AddToZoneList(pItemData->GetNum0(), 0);
		pUIManager->GetPortal()->SetNpcIdx(pItemData->GetNum2());
		pUIManager->GetPortal()->OpenPortal(_pNetwork->MyCharacterInfo.x, _pNetwork->MyCharacterInfo.z);
		return;
	}

	if (pItemData->GetItemIndex() == 2882)
	{


		if (pUIManager->DoesMessageBoxExist(MSGCMD_PRESSCORPS)) return;

		CTString strSysMessage;
		CUIMsgBox_Info	MsgBoxInfo;

		MsgBoxInfo.SetMsgBoxInfo(_S(4143, "��ī ���ڴ� Ȯ����"), UMBS_USER_12 | UMBS_INPUT_MASK | UMBS_ALIGN_RIGHT, UI_INVENTORY, MSGCMD_PRESSCORPS, 300);
		MsgBoxInfo.SetUserBtnName(_S(191, "Ȯ��"), _S(139, "���"));
		MsgBoxInfo.SetInputBox(2, 2, 80, 235);

		strSysMessage.PrintF(_S(4144, "��ġ�� �� ������ �Է��ϼ���."));
		MsgBoxInfo.AddString(strSysMessage, 0xF3F3F3FF, TEXT_CENTER);

		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetInventory()->Lock(TRUE, TRUE, LOCK_PRESSCORPS);

		return;
	}

	// connie [2009/9/9] - NPC ã��
	// [2010/07/21 : Sora] ������ �ε��� -> �÷��׷� ����, pItemData->GetNum0() ���� ���ѹ��̹Ƿ� �ش簪���� ��üũ
	if (pItemData->GetType() == CItemData::ITEM_POTION && pItemData->GetSubType() == CItemData::POTION_POTAL_SCROLL)
	{
		if (_pNetwork->MyCharacterInfo.zoneNo == pItemData->GetNum0())
		{
			pUIManager->GetNpcScroll()->OpenNPCScroll();
		}
		else
		{
			pUIManager->GetNpcScroll()->OpenNPCScrollInfo(MSG_NPC_PORTAL_ERROR_LIST);
		}
		return;
	}

	// �뺴 ī���� ����
	if (pItemData->IsMercenaryCardHolder())
	{
		pUIManager->CloseMessageBox(MSGCMD_MONSTER_MERCENARY_CARD_HOLDER_USE);

		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(CTString(pItemData->GetName()), UMBS_OKCANCEL, UI_INVENTORY, MSGCMD_MONSTER_MERCENARY_CARD_HOLDER_USE);
		MsgBoxInfo.AddString(_S(5149, "ī�� �� ��� �� ���� �ϰ� �뺴ī�尡 �����Ǹ� ī�� ���� �Ҹ��ϰ� �˴ϴ�. ī�� ���� ��� �Ͻðڽ��ϱ�?"));
		pUIManager->CreateMessageBox(MsgBoxInfo);
		return;
	}

	//�뺴 ī�� ����
	if (pItemData->GetType() == CItemData::ITEM_ETC &&
		pItemData->GetSubType() == CItemData::ITEM_ETC_MONSTER_MERCENARY_CARD &&
		pItems->Item_Used < 1 && (!_pNetwork->MySlotItem[nTab][inven_idx].GetSkillDelay()))
	{
		pUIManager->CloseMessageBox(MSGCMD_MONSTER_MERCENARY_CARD_USE);

		CUIMsgBox_Info	MsgBoxInfo;
		CTString strTemp;

		MsgBoxInfo.SetMsgBoxInfo(CTString(pItemData->GetName()), UMBS_OKCANCEL, UI_INVENTORY, MSGCMD_MONSTER_MERCENARY_CARD_USE);

		strTemp.PrintF(_S(5150, "ī�带 ����ϰ� �Ǹ� �ŷ��� �� �� ������ %s�� ���Ӻ��ϰ� �˴ϴ�. ��� �Ͻðڽ��ϱ�?"), _pNetwork->MyCharacterInfo.name);
		MsgBoxInfo.AddString(strTemp);
		pUIManager->CreateMessageBox(MsgBoxInfo);
		return;
	}

	if (pItemData->GetItemIndex() == 6941)
	{
		INDEX nZone;
		float fposX, fposY;

		nZone = pItems->Item_Used2;
		fposX = pItems->Item_Plus;
		fposY = pItems->GetItemPlus2();

		pUIManager->GetTreasureMapUI()->OpenMap(nZone, fposX, fposY);
		return;
	}

#ifdef	IMPROV1107_NOTICESYSTEM
	if (pItemData->GetItemIndex() == 7736)		// �˸����� Ȯ����
	{
		pUIManager->GetChattingUI()->PopupUserNotice();

		return;
	}
#endif	// #ifdef	IMPROV1107_NOTICESYSTEM


	// wooss 050806
	// ���� ������ ��� üũ 
	int tv_index = pItemData->GetItemIndex();
	CUIMsgBox_Info	MsgBoxInfo;
	CTString		strMessage[MAX_MSGSTRING];
	switch (tv_index)
	{
	case MEMSCROLL_EX_ITEM:
	case MEMSCROLL_EX_ITEM_7DAYS:

		if ((pUIManager->GetTeleport()->GetUseTime()) > 0) {
			//			//�޸� ��ũ���� �̹� ����ϰ� ������
			//			//wooss 050816
			//			strMessage[0]	=	"��� Ȯ��";
			//			strMessage[1]	=	"�̹� �޸� ��ũ���� Ȯ��Ǿ� �ִ� ���� �Դϴ�.";
			//			strMessage[2]   =   "�Ⱓ�� �����Ͻðڽ��ϱ�?";	
			//			MsgBoxInfo.SetMsgBoxInfo(strMessage[0],UMBS_YESNO,UI_NONE,MSGCMD_PROLONG_MEMSCROLL_EX);
			//			MsgBoxInfo.AddString(strMessage[1]);
			//			MsgBoxInfo.AddString(strMessage[2]);
			//			pUIManager->CreateMessageBox(MsgBoxInfo);
			//			MSG_ITME_PROLONG���� ó���ϱ�� ��
		}
		else {
			// �޸� ��ũ���� ����ϰ� ���� ���� ��

			//wooss 050816
			strMessage[0] = _S(2088, "��� Ȯ��");
			strMessage[1] = _S(2089, "�޸� ��ũ���� Ȯ���Ͻðڽ��ϱ�?");
			MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_CONFIRM_MEMSCROLL_EX);
			MsgBoxInfo.AddString(strMessage[1]);

			if (pUIManager->CreateMessageBox(MsgBoxInfo))
				pUIManager->GetMessageBox(MSGCMD_CONFIRM_MEMSCROLL_EX)->SetInvenUseItemInfo(nTab, inven_idx);
			return;
		}
		break;

	case WAREHOUSE_EX_ITEM:
	case WAREHOUSE_EX_ITEM_7DAYS:
		//			if((pUIManager->GetWareHouseUI()->GetUseTime())<=0)
	{
		//wooss 050816
		strMessage[0] = _S(2088, "��� Ȯ��");
		strMessage[1] = _S(2090, "â���� Ȯ���Ͻðڽ��ϱ�?");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_CONFIRM_WAREHOUSE_EX);
		MsgBoxInfo.AddString(strMessage[1]);

		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetMessageBox(MSGCMD_CONFIRM_WAREHOUSE_EX)->SetInvenUseItemInfo(nTab, inven_idx);
		return;
	}
	break;
	case CHANGE_MY_NAME_ITEM:
	case CHANGE_MY_NAME_ITEM_UE:
		strMessage[0] = _S(2088, "��� Ȯ��");
		strMessage[1].PrintF(_S(2091, "����ī�带 ����Ͻðڽ��ϱ�?"), "");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_CONFIRM_CHANGE_MY_NAME);
		MsgBoxInfo.AddString(strMessage[1]);
		pUIManager->CreateMessageBox(MsgBoxInfo);
		return;
	case CHANGE_MY_NAME_ITEM_CUSTOM:
		strMessage[0] = _S(2088, "��� Ȯ��");
		strMessage[1].PrintF(_S(2091, "����ī�带 ����Ͻðڽ��ϱ�?"), "[Premium]");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_CONFIRM_CHANGE_MY_NAME_CUSTOM);
		MsgBoxInfo.AddString(strMessage[1]);
		pUIManager->CreateMessageBox(MsgBoxInfo);
		return;
	case CHANGE_GUILD_NAME_ITEM:
		strMessage[0] = _S(2088, "��� Ȯ��");
		strMessage[1].PrintF(_S(2092, "����ī�带 ����Ͻðڽ��ϱ�?"), "");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_CONFIRM_CHANGE_GUILD_NAME);
		MsgBoxInfo.AddString(strMessage[1]);
		pUIManager->CreateMessageBox(MsgBoxInfo);
		return;
	case CHANGE_GUILD_NAME_CUSTOM_ITEM:
		strMessage[0] = _S(2088, "��� Ȯ��");
		strMessage[1].PrintF(_S(2092, "����ī�带 ����Ͻðڽ��ϱ�?"), "[Premium]");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_CONFIRM_CHANGE_GUILD_NAME_CUSTOM);
		MsgBoxInfo.AddString(strMessage[1]);
		pUIManager->CreateMessageBox(MsgBoxInfo);
		return;
	case RECOVER_HEXP_ITEM:
	case RECOVER_HEXP_ITEM_LUCKY:
	{
		pUIManager->CloseMessageBox(MSGCMD_NULL);

		if (_pUIBuff->IsBuff(RECOVER_HEXP_ITEM) || _pUIBuff->IsBuff(RECOVER_HEXP_ITEM_LUCKY))
		{
			strMessage[0] = _S(2093, "�̹� ����ġ ���� �ֹ����� ������Դϴ�.");
			MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_OK,
				UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(strMessage[0]);
			pUIManager->CreateMessageBox(MsgBoxInfo);
			return;
		}
		// wooss 050926
		if (_pUIBuff->IsBuff(RECOVER_AEXP_ITEM) || _pUIBuff->IsBuff(RECOVER_AEXP_ITEM_LUCKY))
		{

			strMessage[0] = _S(2095, "�̹� ���õ� ���� �ֹ����� ������Դϴ�.");
			MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_OK,
				UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(strMessage[0]);
			pUIManager->CreateMessageBox(MsgBoxInfo);
			return;
		}
		if (_pUIBuff->IsBuff(REBIRTH_ITEM)) {
			strMessage[0] = _S(2094, "�̹� ��Ȱ �ֹ����� ������Դϴ�.");
			MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_OK,
				UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(strMessage[0]);
			pUIManager->CreateMessageBox(MsgBoxInfo);
			return;
		}
	}

	break;

	case RECOVER_AEXP_ITEM:
	case RECOVER_AEXP_ITEM_LUCKY:
	{
		pUIManager->CloseMessageBox(MSGCMD_NULL);

		if (_pUIBuff->IsBuff(RECOVER_AEXP_ITEM) || _pUIBuff->IsBuff(RECOVER_AEXP_ITEM_LUCKY))
		{

			strMessage[0] = _S(2095, "�̹� ���õ� ���� �ֹ����� ������Դϴ�.");
			MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_OK,
				UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(strMessage[0]);
			pUIManager->CreateMessageBox(MsgBoxInfo);
			return;
		}
		// wooss 050926
		if (_pUIBuff->IsBuff(RECOVER_HEXP_ITEM) || _pUIBuff->IsBuff(RECOVER_HEXP_ITEM_LUCKY))
		{
			strMessage[0] = _S(2093, "�̹� ����ġ ���� �ֹ����� ������Դϴ�.");
			MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_OK,
				UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(strMessage[0]);
			pUIManager->CreateMessageBox(MsgBoxInfo);
			return;
		}
		if (_pUIBuff->IsBuff(REBIRTH_ITEM)) {

			strMessage[0] = _S(2094, "�̹� ��Ȱ �ֹ����� ������Դϴ�.");
			MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_OK,
				UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(strMessage[0]);
			pUIManager->CreateMessageBox(MsgBoxInfo);
			return;

		}
	}

	break;

	case REBIRTH_ITEM:
	case REBIRTH_ITEM_NEWBIE:
	{
		pUIManager->CloseMessageBox(MSGCMD_NULL);

		if (_pUIBuff->IsBuff(RECOVER_HEXP_ITEM) || _pUIBuff->IsBuff(RECOVER_HEXP_ITEM_LUCKY))
		{
			strMessage[0] = _S(2093, "�̹� ����ġ ���� �ֹ����� ������Դϴ�.");
			strMessage[1] = _S(2096, "��Ȱ �ֹ����� ����Ͻ� ��� ���� �ֹ����� ȿ���� ������ϴ�.");
			strMessage[2] = _S(2097, "����Ͻðڽ��ϱ�?");
			MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_YESNO,
				UI_NONE, MSGCMD_CHECK_ITEM_HEXP);
			MsgBoxInfo.AddString(strMessage[0]);
			MsgBoxInfo.AddString(strMessage[1]);
			MsgBoxInfo.AddString(strMessage[2]);
			if (pUIManager->CreateMessageBox(MsgBoxInfo))
				pUIManager->GetMessageBox(MSGCMD_CHECK_ITEM_HEXP)->SetInvenUseItemInfo(nTab, inven_idx);
			return;
		}

		if (_pUIBuff->IsBuff(RECOVER_AEXP_ITEM) || _pUIBuff->IsBuff(RECOVER_AEXP_ITEM_LUCKY))
		{
			strMessage[0] = _S(2095, "�̹� ���õ� �ֹ����� ������Դϴ�.");
			strMessage[1] = _S(2096, "��Ȱ �ֹ����� ����Ͻ� ��� ���� �ֹ����� ȿ���� ������ϴ�.");
			strMessage[2] = _S(2097, "����Ͻðڽ��ϱ�?");
			MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_YESNO,
				UI_NONE, MSGCMD_CHECK_ITEM_AEXP);
			MsgBoxInfo.AddString(strMessage[0]);
			MsgBoxInfo.AddString(strMessage[1]);
			MsgBoxInfo.AddString(strMessage[2]);
			if (pUIManager->CreateMessageBox(MsgBoxInfo))
				pUIManager->GetMessageBox(MSGCMD_CHECK_ITEM_AEXP)->SetInvenUseItemInfo(nTab, inven_idx);
			return;

		}

		if (_pUIBuff->IsBuff(REBIRTH_ITEM) || _pUIBuff->IsBuff(REBIRTH_ITEM_NEWBIE))
		{
			strMessage[0] = _S(2094, "�̹� ��Ȱ �ֹ����� ������Դϴ�");
			MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_OK,
				UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(strMessage[0]);
			pUIManager->CreateMessageBox(MsgBoxInfo);
			return;
		}

	}

	break;

	case REBIRTH_ITEM_PHOENIX:
	{
		if (_pUIBuff->IsBuff(REBIRTH_ITEM_PHOENIX))
		{
			strMessage[0] = _S(4258, "�̹� �Ǵн��� ��Ȱ�� ������Դϴ�.");
			MsgBoxInfo.SetMsgBoxInfo(_S(299, "�ý���"), UMBS_OK,
				UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(strMessage[0]);
			pUIManager->CreateMessageBox(MsgBoxInfo);
			return;
		}
	}
	break;

	case WARP_ITEM:
		// Date : 2006-05-30(���� 11:39:42), By eons
		if (!((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsIdle())
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(2739, "�ٸ� �ൿ �߿��� �����̵� �������� ����� �� �����ϴ�."));
			return;
		}
		if (pUIManager->IsPlayInZone()) // [sora] �������ο����� ��� �Ұ�
		{
			_pNetwork->ClientSystemMessage(_S(4504, "�ν���Ʈ�� ���ο����� ����� �� �����ϴ�."), SYSMSG_ERROR);
			return;
		}

		//wooss 050808
		strMessage[0] = _S(2098, "�����̵� ������");
		strMessage[1] = _S(2099, "���� �̵��� �� ��ġ�� �ִ� ĳ������ �̸��� �Է��� �ּ���");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_INPUTBOX | UMBS_YESNO, UI_NONE, MSGCMD_USE_WARP_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);
		pUIManager->CreateMessageBox(MsgBoxInfo); // UIManager���� MSGCMD_USE_WARP_ITEM�� Ȯ���ϰ� ó��

		return;

	case PC_SUMMON_ITEM:
		// Date : 2006-05-30(���� 11:39:42), By eons
		if (!((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsIdle())
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(2740, "�ٸ� �ൿ �߿��� ��ȯ �������� ����� �� �����ϴ�."));
			return;
		}
		if (pUIManager->IsPlayInZone()) // [sora] �������ο����� ��� �Ұ�
		{
			_pNetwork->ClientSystemMessage(_S(4504, "�ν���Ʈ�� ���ο����� ����� �� �����ϴ�."), SYSMSG_ERROR);
			return;
		}

		//wooss 050817
		strMessage[0] = _S(2100, "��ȯ ������");
		strMessage[1] = _S(2101, "��ȯ�� ĳ������ �̸��� �Է��� �ּ���");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_INPUTBOX | UMBS_YESNO, UI_NONE, MSGCMD_USE_PC_SUMMON_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);

		// UIManager���� MSGCMD_USE_PC_SUMMON_ITEM�� Ȯ���ϰ� ó��
		pUIManager->CreateMessageBox(MsgBoxInfo);
		return;

	case BAAL_SUMMON_ITEM:
		//wooss 050818
		if (pUIManager->DoesMessageBoxExist(BAAL_SUMMON_ITEM)) return;
		strMessage[0] = _S(2100, "��ȯ ������");
		strMessage[1] = _S(2102, "���� ���� ��ȯ���� ");
		strMessage[2] = _S(2097, "����Ͻðڽ��ϱ�?");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_USE_BOSS_SUMMON_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);
		MsgBoxInfo.AddString(strMessage[2]);
		if (pUIManager->CreateMessageBox(MsgBoxInfo)) // UIManager���� MSGCMD_USE_BOSS_SUMMON_ITEM�� Ȯ���ϰ� ó��
			pUIManager->GetMessageBox(MSGCMD_USE_BOSS_SUMMON_ITEM)->SetInvenUseItemInfo(nTab, inven_idx);
		return;

	case DEATHNIGHT_SUMMON_ITEM:
		//wooss 050818
		if (pUIManager->DoesMessageBoxExist(DEATHNIGHT_SUMMON_ITEM)) return;
		strMessage[0] = _S(2100, "��ȯ ������");
		strMessage[1] = _S(2102, "���� ���� ��ȯ���� ");
		strMessage[2] = _S(2097, "����Ͻðڽ��ϱ�?");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_USE_BOSS_SUMMON_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);
		MsgBoxInfo.AddString(strMessage[2]);

		if (pUIManager->CreateMessageBox(MsgBoxInfo)) // UIManager���� MSGCMD_USE_BOSS_SUMMON_ITEM�� Ȯ���ϰ� ó��
			pUIManager->GetMessageBox(MSGCMD_USE_BOSS_SUMMON_ITEM)->SetInvenUseItemInfo(nTab, inven_idx);
		return;

	case INIT_STATUS_ITEM:
		//wooss 050818
		strMessage[0] = _S(2103, "�������ͽ� �ʱ�ȭ ī��");
		strMessage[1] = _S(2104, "ī�带 ����ϸ� �Ϻ�  �ʿ��� �������ͽ��� �ִ� ��ų�� ������� ���� �� �ֽ��ϴ�");

		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_USE_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);

		if (pUIManager->CreateMessageBox(MsgBoxInfo)) // UIManager���� MSGCMD_USE_BOSS_SUMMON_ITEM�� Ȯ���ϰ� ó��
			pUIManager->GetMessageBox(MSGCMD_USE_ITEM)->SetInvenUseItemInfo(nTab, inven_idx);
		return;
	case INIT_COMBAT_SKILL_ITEM:
		strMessage[0] = _S(2105, "������ų �ʱ�ȭ ī��");
		strMessage[1] = _S(2106, "ī�带 ����ϸ� ���� ����� �Բ�, �Ϲ�, ��ȭ ��ų ��尡 �ʱ�ȭ�Ǹ� ��ų�� ���µ� ���� ���õ��� ��� ȯ�� �˴ϴ�");

		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_USE_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);

		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetMessageBox(MSGCMD_USE_ITEM)->SetInvenUseItemInfo(nTab, inven_idx);
		return;
	case INIT_SPECIAL_SKILL_ITEM:
		strMessage[0] = _S(2107, "Ư����ų �ʱ�ȭ ī��");
		strMessage[1] = _S(2108, "Ư����ų �ʱ�ȭ ī�带 ����ϸ� ����, ����, ���� ��ų ��ΰ� �ʱ�ȭ�Ǹ� ��ų�� ���µ� ���� ���õ��� ��� ȯ�� �˴ϴ�");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_USE_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);
		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetMessageBox(MSGCMD_USE_ITEM)->SetInvenUseItemInfo(nTab, inven_idx);
		return;
	case INIT_SKILL_ITEM:
		strMessage[0] = _pNetwork->GetItemName(tv_index);
		strMessage[1] = _S(2106, "ī�带 ����ϸ� ���� ����� �Բ�, �Ϲ�, ��ȭ ��ų ��尡 �ʱ�ȭ�Ǹ� ��ų�� ���µ� ���� ���õ��� ��� ȯ�� �˴ϴ�");

		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_USE_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);
		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetMessageBox(MSGCMD_USE_ITEM)->SetInvenUseItemInfo(nTab, inven_idx);
		return;
	case INIT_ALL_ITEM:
		strMessage[0] = _S(2109, "�ɷ�ġ �ʱ�ȭ ī��");
		strMessage[1] = _S(2110, "ĳ������ �������ͽ�, �Ϲ�, ��ȭ, Ư�� ��ų, �ʱ�ȭ, ���� ���Ⱑ �Ǹ� ��ų�� ���µ� ���� ���õ��� ��� ȯ�� �˴ϴ�");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_USE_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);

		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetMessageBox(MSGCMD_USE_ITEM)->SetInvenUseItemInfo(nTab, inven_idx);
		return;
		// wooss 051011	
		// [070613: Su-won] ���� ��ȯ ī��
	case EXCHANGE_WEAPON_ITEM:
		if (pUIManager->GetChangeWeapon()->GetCashItem()) return;
		else {
			SetUseItemSlotInfo(nTab, inven_idx);
			pUIManager->GetChangeWeapon()->SetCashItem(TRUE);
			pUIManager->GetChangeWeapon()->open(CHANGEWEAPON_WEAPON);
			pUIManager->GetChangeWeapon()->MsgBoxLCommand(MSGLCMD_CHANGEWEAPON_REQ, 0);
		}
		return;

		// [070613: Su-won] �� ��ȯ ī��
	case EXCHANGE_ARMOR_ITEM:
		if (pUIManager->GetChangeWeapon()->GetCashItem()) return;
		else {
			SetUseItemSlotInfo(nTab, inven_idx);
			pUIManager->GetChangeWeapon()->SetCashItem(TRUE);
			pUIManager->GetChangeWeapon()->open(CHANGEWEAPON_SHIELD);
			pUIManager->GetChangeWeapon()->MsgBoxLCommand(MSGLCMD_CHANGEWEAPON_REQ, 3);
		}
		return;

	case PARTY_RECALL_ITEM1:
	case PARTY_RECALL_ITEM2:
	case PARTY_RECALL_ITEM3:
	case PARTY_RECALL_ITEM4:
	case PARTY_RECALL_ITEM5:
	case PARTY_RECALL_ITEM6:
	case PARTY_RECALL_IRIS:
	case PARTY_RECALL_ASKA:

	{// ��Ƽ ���� Ȯ�� 
		if (pUIManager->DoesMessageBoxExist(MSGCMD_CONFIRM_PARTY_RECALL_ITEM)) return;
		if (GAMEDATAMGR()->GetPartyInfo()->GetMemberCount() == 0)
		{
			_pNetwork->ClientSystemMessage(_S(3408, "��ȯ�� ��Ƽ������ �����ϴ�."), SYSMSG_ERROR);
			return;
		}
		/*				if(pUIManager->IsPlayInZone()) // [sora] �������ο����� ��� �Ұ�
						{
							_pNetwork->ClientSystemMessage(_S(4504, "�ν���Ʈ�� ���ο����� ����� �� �����ϴ�."), SYSMSG_ERROR);
							return;
						}*/

		strMessage[1] = _S(2515, "��Ƽ������ ��ȯ �Ͻðڽ��ϱ�?");
		strMessage[2].PrintF(_S(3286, "[���������] %s�� �����Ͻðڽ��ϱ�?"), pItemData->GetName());

		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_CONFIRM_PARTY_RECALL_ITEM);

		if (pItems->Item_Used < 0) { MsgBoxInfo.AddString(strMessage[2]); }
		else { MsgBoxInfo.AddString(strMessage[1]); }

		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetMessageBox(MSGCMD_CONFIRM_PARTY_RECALL_ITEM)->SetInvenUseItemInfo(nTab, inven_idx);
	}
	return;

	case PLATINUM_UPGRADESTONE_ITEM1:		//		1418	
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_CONFIRM_UPGRADESTONE_ITEM)) return;
		strMessage[1] = _S(2707, "�÷�Ƽ�� ���ü��� �����Ͻðڽ��ϱ�?");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_CONFIRM_UPGRADESTONE_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);
		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetMessageBox(MSGCMD_CONFIRM_UPGRADESTONE_ITEM)->SetInvenUseItemInfo(nTab, inven_idx);

	}
	return;

	case COMPOSITE_ITEM1:					//		1421
	case COMPOSITE_ITEM_EVENT1:
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_CONFIRM_MIXNEWREQ_ITEM)) return;
		strMessage[1] = _S(2714, "���� �ֹ����� �����Ͻðڽ��ϱ�?");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_CONFIRM_MIXNEWREQ_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);

		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetMessageBox(MSGCMD_CONFIRM_MIXNEWREQ_ITEM)->SetInvenUseItemInfo(nTab, inven_idx);
	}
	return;

	case COMPOSITE_ITEM2:					//		1421
	case COMPOSITE_ITEM_EVENT2:
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_CONFIRM_MIXNEW_ITEM)) return;
		strMessage[1] = _S(2734, "�����ֹ����� ���� �ɷ�ġ ������ �ִ� +26���� ȿ���� ���ϴ�. ����Ͻðڽ��ϱ�?");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_CONFIRM_MIXNEW_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	return;

	case PET_MOUNT_CANCEL_CARD:
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_PET_MOUNT_CANCEL_CARD)) return;

		strMessage[0] = _S(2896, "�� ����Ʈ �Ʒ� ���");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO | UMBS_BUTTONEX, UI_NONE, MSGCMD_PET_MOUNT_CANCEL_CARD);
		strMessage[1] = _S(2897, "Ż ��(����Ʈ) �Ʒ��� ����� �ֿϵ����� �÷� �ּ���.\n��, �ֿ� ������ ��ų�� �ʱ�ȭ�� ���¿��� �մϴ�.");
		MsgBoxInfo.SetBtnType(UBET_ITEM, CItemData::ITEM_ACCESSORY, CItemData::ACCESSORY_PET);
		MsgBoxInfo.AddString(strMessage[1]);
		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetInventory()->SetUseItemSlotInfo(nTab, inven_idx);
	}
	return;
	case UNCOMPOSITE_ITEM:					//		1540
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_CONFIRM_UNMIX_ITEM)) return;
		strMessage[1] = _S(2928, "���� �и� �ֹ����� ����Ͻðڽ��ϱ�?");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_CONFIRM_UNMIX_ITEM);
		MsgBoxInfo.AddString(strMessage[1]);
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	return;
	case PACKING_PAPER_ITEM:
	case SMALL_CORD_ITEM:
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_USE_PACKING_PAPER) ||
			pUIManager->DoesMessageBoxExist(MSGCMD_USE_SMALL_CORD))
			return;

		if (tv_index == SMALL_CORD_ITEM)
		{
			strMessage[0] = _S(3993, "���ָӴ� ���");
			strMessage[1] = _S(3994, "���ָӴϸ� �ø� �� Ȯ�ι�ư�� Ŭ���ϼ���");

			MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO | UMBS_BUTTONEX, UI_NONE, MSGCMD_USE_SMALL_CORD);
			MsgBoxInfo.SetBtnType(UBET_ITEM, CItemData::ITEM_ETC, CItemData::ITEM_ETC_EVENT);
			MsgBoxInfo.AddString(strMessage[1]);
			if (pUIManager->CreateMessageBox(MsgBoxInfo))
				pUIManager->GetMessageBox(MSGCMD_USE_SMALL_CORD)->SetInvenUseItemInfo(nTab, inven_idx);
		}
		else
		{
			strMessage[0] = _S(3199, "����������");
			strMessage[1] = _S(3200, "���ڷ��� �ø� �� Ȯ�ι�ư�� Ŭ���ϼ���");

			MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO | UMBS_BUTTONEX, UI_NONE, MSGCMD_USE_PACKING_PAPER);
			MsgBoxInfo.SetBtnType(UBET_ITEM, CItemData::ITEM_ETC, CItemData::ITEM_ETC_EVENT);
			MsgBoxInfo.AddString(strMessage[1]);
			if (pUIManager->CreateMessageBox(MsgBoxInfo))
				pUIManager->GetMessageBox(MSGCMD_USE_PACKING_PAPER)->SetInvenUseItemInfo(nTab, inven_idx);
		}
	}
	return;

	// wooss 070305 --------------------------------------------------------------------------------->>
	// kw : WSS_WHITEDAY_2007
	case BLUE_LETTER_ITEM:					//		2135
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_WHITEDAY_BLUELETTER)) return;
		strMessage[0] = _S(3224, "�ϴû� ������");
		strMessage[1] = _S(3225, "�޽��� ������ �Է��ϼ���.(50��)");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_OKCANCEL | UMBS_INPUTBOX, UI_INVENTORY, MSGCMD_WHITEDAY_BLUELETTER);
		MsgBoxInfo.AddString(strMessage[1]); // BLUE
		MsgBoxInfo.SetInputBox(3, 3, 50, 150);
		MsgBoxInfo.m_nMaxRow = 5;
		pUIManager->CreateMessageBox(MsgBoxInfo);
		//		pUIManager->GetMessageBox(MSGCMD_WHITEDAY_BLUELETTER)->GetInputBox().SetMaxChar(256);

	}
	return;
	case PINK_LETTER_ITEM:					//		2136
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_WHITEDAY_PINKLETTER)) return;
		strMessage[0] = _S(3226, "��ȫ�� ������");
		strMessage[1] = _S(3225, "�޽��� ������ �Է��ϼ���.(50��)");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_OKCANCEL | UMBS_INPUTBOX, UI_INVENTORY, MSGCMD_WHITEDAY_PINKLETTER);
		MsgBoxInfo.AddString(strMessage[1]); // PINK
		MsgBoxInfo.SetInputBox(3, 3, 50, 150);
		MsgBoxInfo.m_nMaxRow = 5;
		pUIManager->CreateMessageBox(MsgBoxInfo);
		//	pUIManager->GetMessageBox(MSGCMD_WHITEDAY_BLUELETTER)->GetInputBox().SetMaxChar(256);
	}
	return;
	// -----------------------------------------------------------------------------------------------<<
// [KH_070326] �ް� �̺�Ʈ ����
	case EASTER_EGGS:
	{
		strMessage[0] = _S(2088, "��� Ȯ��");
		strMessage[1] = _S(3267, "������ ��Ȱ�� �ް��� ���� �Ͻðڽ��ϱ�?");
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_CONFIRM_EASTER_EGGS);
		MsgBoxInfo.AddString(strMessage[1]);
		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetMessageBox(MSGCMD_CONFIRM_EASTER_EGGS)->SetInvenUseItemInfo(nTab, inven_idx);
	}
	return;
	// [070613: Su-won] �� ���� ������
	case PET_NAMECARD_ITEM:
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_PET_NAMECARD_USE))
			return;
		strMessage[1] = _S(3527, "[���������] ���� ������ ����Ͻðڽ��ϱ�?");
		MsgBoxInfo.SetMsgBoxInfo(CTString(_pNetwork->GetItemName(PET_NAMECARD_ITEM)), UMBS_YESNO, UI_NONE, MSGCMD_PET_NAMECARD_USE);
		MsgBoxInfo.AddString(strMessage[1]);
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
	return;

	// [070824: Su-won] PET_COLOR_CHANGE
	case PET_COLOR_RED:
	case PET_COLOR_ORNAGE:
	case PET_COLOR_YELLOW:
	case PET_COLOR_GREEN:
	case PET_COLOR_BLUE:
	case PET_COLOR_INDIGO:
	case PET_COLOR_VIOLET:
	case PET_COLOR_WHITE:
	case PET_COLOR_BLACK:
	case PET_COLOR_PHOENIX:
	case PET_COLOR_BLACK_HEART:
	case PET_COLOR_WHITE_HEART:
	case PET_COLOR_YELLOW_HEART:
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_PET_COLORCHANGE_USE))
			pUIManager->CloseMessageBox(MSGCMD_PET_COLORCHANGE_USE);
		//					return;

		if (pPetInfo->bIsActive == FALSE)
		{
			_pNetwork->ClientSystemMessage(_S(2189, "�ֿϵ����� ���Կ� �����Ͽ��߸� �մϴ�."), SYSMSG_ERROR);
			return;
		}

		if (pPetInfo->TransformIndex > 0) // ���� �����ϰ� ���� ���
		{
			_pNetwork->ClientSystemMessage(_S(3968, "�������� �꿡�Դ� ����� �� �����ϴ�."));
			return;
		}

		strMessage[1].PrintF(_S(3661, "%s�� ����Ͽ� ���� ���������� �����̽ðڽ��ϱ�?"), _pNetwork->GetItemName(tv_index));
		MsgBoxInfo.SetMsgBoxInfo(CTString(_pNetwork->GetItemName(tv_index)), UMBS_YESNO, UI_NONE, MSGCMD_PET_COLORCHANGE_USE);
		MsgBoxInfo.AddString(strMessage[1]);
		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetMessageBox(MSGCMD_PET_COLORCHANGE_USE)->SetInvenUseItemInfo(nTab, inven_idx);
	}
	return;

	// [090710: selo] �� ���� �ý���
	case PET_TATOO_HORSE:
	case PET_TATOO_DRAGON:
	{
		if (pPetInfo->bIsActive == FALSE)
		{
			_pNetwork->ClientSystemMessage(_S(2189, "�ֿϵ����� ���Կ� �����Ͽ��߸� �մϴ�."), SYSMSG_ERROR);
			return;
		}

		if (pPetInfo->TransformIndex > 0) // ���� �����ϰ� ���� ���
		{
			_pNetwork->ClientSystemMessage(_S(3968, "�������� �꿡�Դ� ����� �� �����ϴ�."));
			return;
		}

		pUIManager->GetTatoo()->OpenTatoo();
	}
	return;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// [071122: Su-won] NEW_MOONSTONE
	case MOONSTONE_POOR_MIX_BOX:
	case MOONSTONE_USEFUL_MIX_BOX:
	case MOONSTONE_SOLID_MIX_BOX:
	case MOONSTONE_STRONG_MIX_BOX:
	case MOONSTONE_TRUSTY_MIX_BOX:
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_MOONSTONE_MIX))
			pUIManager->CloseMessageBox(MSGCMD_MOONSTONE_MIX);

		int nTab, nIndex;
		pUIManager->GetInventory()->GetUseItemSlotInfo(nTab, nIndex);

		int iMoonStoneBox = _pNetwork->MySlotItem[nTab][nIndex].Item_Index;

		strMessage[0] = _pNetwork->GetItemName(iMoonStoneBox);
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_OKCANCEL | UMBS_BUTTONEX | UMBS_INPUTBOX, UI_INVENTORY, MSGCMD_MOONSTONE_MIX);
		MsgBoxInfo.SetBtnType(UBET_ITEM, CItemData::ITEM_ACCESSORY, CItemData::ACCESSORY_PET);
		MsgBoxInfo.AddString(_S(3900, "������ �������� �÷� �ּ���."));

		MsgBoxInfo.SetInputBox(2, 0, 0, MsgBoxInfo.m_nWidth - MSGBOX_MESSAGE_OFFSETX * 2);

		MsgBoxInfo.m_nMaxRow += 4;
		MsgBoxInfo.AddString(_s("X 3") + _s("        "), 0xF2F2F2Ff, TEXT_RIGHT);
		MsgBoxInfo.m_nMaxRow -= 4;

		MsgBoxInfo.m_nColorBoxCount = 1;

		if (pUIManager->CreateMessageBox(MsgBoxInfo))
		{
			pUIManager->GetMessageBox(MSGCMD_MOONSTONE_MIX)->SetInvenUseItemInfo(nTab, nIndex);

			pUIManager->GetMessageBox(MSGCMD_MOONSTONE_MIX)->GetInputBox().SetFocus(FALSE);
			pUIManager->GetMessageBox(MSGCMD_MOONSTONE_MIX)->GetInputBox().SetInValidEditBox(TRUE);

			int iPosX, iPosY;
			int iWidth, iHeight;

			iPosX = MsgBoxInfo.m_nInputPosX + 2;
			iPosY = MsgBoxInfo.m_nInputPosY + 2;

			iWidth = (MsgBoxInfo.m_nInputWidth - 4);
			iHeight = 9;

			WRect rcBox;

			rcBox.SetRect(iPosX, iPosY, iPosX + iWidth, iPosY + iHeight);

			pUIManager->GetMessageBox(MSGCMD_MOONSTONE_MIX)->SetColorBox(0, 6, rcBox);
		}
	}
	break;
	// [071122: Su-won] NEW_MOONSTONE
	////////////////////////////////////////////////////////////////////////////////////////////////////
	case PET_TRANSFORM_RU: // �� �絹�� ���� ������
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_PETTRANSFORM_RU))
			pUIManager->CloseMessageBox(MSGCMD_PETTRANSFORM_RU);

		if (pPetInfo->bIsActive == FALSE)
		{
			_pNetwork->ClientSystemMessage(_S(2189, "�ֿϵ����� ���Կ� �����Ͽ��߸� �մϴ�."), SYSMSG_ERROR);
			return;
		}

		strMessage[0] = _pNetwork->GetItemName(PET_TRANSFORM_RU);
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_INVENTORY, MSGCMD_PETTRANSFORM_RU);
		MsgBoxInfo.AddString(_S(3967, "�������� ���� �̺�Ʈ �Ⱓ ���ȸ� �絹���� ���Ž�Ű�ڽ��ϱ�?"));
		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetMessageBox(MSGCMD_PETTRANSFORM_RU)->SetInvenUseItemInfo(nTab, inven_idx);
		return;
	}
	break;
	case PET_STAT_INIT_CARD:
	{
		if (pUIManager->DoesMessageBoxExist(MSGCMD_PET_STAT_INIT_CARD_USE)) return;

		int nTab, nIndex;
		pUIManager->GetInventory()->GetUseItemSlotInfo(nTab, nIndex);

		strMessage[0] = _pNetwork->GetItemName(PET_STAT_INIT_CARD);
		MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_PET_STAT_INIT_CARD_USE);
		strMessage[1] = _S(5321, "[P2]���� �������ͽ��� ���� ����Ʈ�� ��� ȯ�� �˴ϴ�.");
		MsgBoxInfo.SetBtnType(UBET_ITEM, CItemData::ITEM_ACCESSORY, CItemData::ACCESSORY_PET);
		MsgBoxInfo.AddString(strMessage[1]);
		if (pUIManager->CreateMessageBox(MsgBoxInfo))
			pUIManager->GetMessageBox(MSGCMD_PET_STAT_INIT_CARD_USE)->SetInvenUseItemInfo(nTab, nIndex);
		return;
	}
	break;
	}

	// ��ȸ��-��Ÿ��ȸ�� �����۵�...
	if (pItemData->GetType() == CItemData::ITEM_ONCEUSE)
	{
		// �����ֹ��� ���� �������� �� ������� �ʵ���. [trylord ; 15/09/11]
		if (pItemData->GetSubType() == CItemData::ITEM_SUB_CHANGE_DOC)
		{
			if (_pNetwork->MyCharacterInfo.eMorphStatus != CNetworkLibrary::MyChaInfo::eMORPH_END)
				return;
		}
		else if (pItemData->GetSubType() == CItemData::ITEM_SUB_JUMPING_POTION)
		{
			if (pUIManager->DoesMessageBoxExist(MSGCMD_JUMPIMGPOTION))
				return;

			MsgBoxInfo.SetMsgBoxInfo(CTString(pItemData->GetName()), UMBS_YESNO, UI_NONE, MSGCMD_JUMPIMGPOTION);
			strMessage[0].PrintF(_S(5687, "ĳ������ ������ %d ������ �ǰ�, ���� �Ͻ� ��ų �� ������ ��� �ʱ�ȭ �Ǹ�, ���� ���� ���·� ���ư��� �˴ϴ�."), pItemData->GetJumpingLevel());
			strMessage[1].PrintF(_S(5688, "(��, ���õ� �� ������ �߰� ���� �ص帳�ϴ�.)Jump Potion�� ��� �Ͻðڽ��ϱ�?"));
			MsgBoxInfo.AddString(strMessage[0]);
			MsgBoxInfo.AddString(strMessage[1]);
			if (pUIManager->CreateMessageBox(MsgBoxInfo))
				pUIManager->GetMessageBox(MSGCMD_JUMPIMGPOTION)->SetInvenUseItemInfo(nTab, inven_idx);
			return;
		}
		else if (pItemData->GetSubType() == CItemData::ITEM_SUB_ETC)
		{
			int tv_index = pItemData->GetItemIndex();
			switch (tv_index)
			{
			case RARE_IDENTITY_ITEM1:
			case RARE_IDENTITY_ITEM2:
			case RARE_IDENTITY_ITEM_NEWBIE:
			case RARE_IDENTITY_ITEM3:
			{
				if (pUIManager->DoesMessageBoxExist(MSGCMD_RARE_IDENTIFY)) return;

				strMessage[0] = _S(3160, "�ɼ� ���� ������");
				MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO | UMBS_BUTTONEX, UI_NONE, MSGCMD_RARE_IDENTIFY);
				strMessage[1] = _S(3161, "��� �پ� �ִ� �̰��� �ɼ��� �������ִ� �������Դϴ�. ��, �ɼ��� �̰����� ��� ������ �� �ֽ��ϴ�.");
				MsgBoxInfo.SetBtnType(UBET_ITEM, CItemData::ITEM_ACCESSORY, CItemData::ACCESSORY_PET);
				MsgBoxInfo.AddString(strMessage[1]);
				if (pUIManager->CreateMessageBox(MsgBoxInfo))
					pUIManager->GetMessageBox(MSGCMD_RARE_IDENTIFY)->SetInvenUseItemInfo(nTab, inven_idx);
			}
			return;
			case GOLD_DISH:
			case SILVER_DISH:
			{
				if (pUIManager->DoesMessageBoxExist(MSGCMD_SONGKRAN_REWARD))
					return;

				strMessage[0] = _S(1721, "���� �ޱ�");
				strMessage[1].PrintF(_S(3284, "[��ũ�� �̺�Ʈ] %s�� �����Ͻðڽ��ϱ�?"), _pNetwork->GetItemName(tv_index));
				MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO, UI_NONE, MSGCMD_SONGKRAN_REWARD);
				MsgBoxInfo.AddString(strMessage[1]);

				if (pUIManager->CreateMessageBox(MsgBoxInfo))
					pUIManager->GetMessageBox(MSGCMD_SONGKRAN_REWARD)->SetInvenUseItemInfo(nTab, inven_idx);
			}
			return;
			// socket system [5/18/2010 rumist]
			case SOCKET_ITEM_CHANCE_CARD:
			{
				if (pUIManager->DoesMessageBoxExist(MSGCMD_SOCKETSYSTEM_CHANCECARD)) return;

				int nTab, nIndex;
				pUIManager->GetInventory()->GetUseItemSlotInfo(nTab, nIndex);
				strMessage[0] = _S(4997, "���� �ʱ�ȭ");
				strMessage[1] = _S(4988, "����� ���� ������ �ʱ�ȭ�ϰ� ���� ���� ������ �� �� �ִ� ���·� �ǵ����ϴ�. �ʱ�ȭ �� ��� ���յǾ� �ִ� ��� ���� �� ���� ������ ������ϴ�.");
				MsgBoxInfo.SetMsgBoxInfo(strMessage[0], UMBS_YESNO | UMBS_BUTTONEX, UI_NONE, MSGCMD_SOCKETSYSTEM_CHANCECARD);

				MsgBoxInfo.SetBtnType(UBET_ITEM, CItemData::ITEM_ACCESSORY, CItemData::ACCESSORY_PET);
				MsgBoxInfo.AddString(strMessage[1]);
				if (pUIManager->CreateMessageBox(MsgBoxInfo))
					pUIManager->GetMessageBox(MSGCMD_SOCKETSYSTEM_CHANCECARD)->SetInvenUseItemInfo(nTab, nIndex);
			}
			return;

			case MYSTERIOUS_BEAD:
			{
				pUIManager->GetMysteryousBead()->OpenUI();
			}
			return;

			case SEALED_SOUL:
			{
				MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_YESNO, UI_NONE, MSGCMD_USE_SEALED_SOUL);
				MsgBoxInfo.AddString(_S(6086, "���� �� ��ȥ�� ���� �Ͻðڽ��ϱ�?"));

				if (pUIManager->CreateMessageBox(MsgBoxInfo))
					pUIManager->GetMessageBox(MSGCMD_USE_SEALED_SOUL)->SetInvenUseItemInfo(nTab, inven_idx);
				return;
			}
			break;

			case EXP_PET_COOLTIME_REMOVE:
			{
				MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_YESNO, UI_NONE, MSGCMD_EXP_PET_COOLTIME_REMOVE);
				MsgBoxInfo.AddString(_S(6287, "���� ���� ����ġ ���� ��Ÿ���� �����Ͻðڽ��ϱ�?"));

				if (pUIManager->CreateMessageBox(MsgBoxInfo))
					pUIManager->GetMessageBox(MSGCMD_EXP_PET_COOLTIME_REMOVE)->SetInvenUseItemInfo(nTab, inven_idx);
				return;
			}
			break;
			}
		}
		else if (pItemData->GetSubType() == CItemData::ITEM_SUB_CHAR_SLOT_EXTEND) // [2012/07/05 : Sora]  ĳ���� ���� Ȯ�� ������
		{
			if (pUIManager->DoesMessageBoxExist(MSGCMD_CHAR_SLOT_EXTEND))
				return;

			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_YESNO, UI_INVENTORY, MSGCMD_CHAR_SLOT_EXTEND);
			MsgBoxInfo.AddString(_S(5701, "�߰� ĳ���� ���� ������ Ȱ��ȭ �Ͻðڽ��ϱ�?"));
			pUIManager->CreateMessageBox(MsgBoxInfo);
			return;
		}
		else if (pItemData->GetSubType() == CItemData::ITEM_SUB_EXPRESS_REMOTE)
		{
			if (pUIManager->DoesMessageBoxExist(MSGCMD_EXPRESS_REMOTE_ITEMUSE))
			{
				pUIManager->CloseMessageBox(MSGCMD_EXPRESS_REMOTE_ITEMUSE);
			}
			CTString strMessage, strTitle;
			CUIMsgBox_Info msgBoxInfo;
			strTitle.PrintF(_S(191, "Ȯ��"));
			msgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_OKCANCEL, UI_INVENTORY, MSGCMD_EXPRESS_REMOTE_ITEMUSE);
			strMessage.PrintF(_S(6024, "LCE ���� �̿���� ��� �Ͻðڽ��ϱ�?"));
			msgBoxInfo.AddString(strMessage);
			if (pUIManager)
			{
				pUIManager->CreateMessageBox(msgBoxInfo);
				pUIManager->GetMessageBox(MSGCMD_EXPRESS_REMOTE_ITEMUSE)->SetInvenUseItemInfo(nTab, inven_idx);
			}
			return;
		}
		else if (pItemData->GetSubType() == CItemData::ITEM_SUB_PET_STASH_USE_ITEM)
		{
			if (pUIManager->DoesMessageBoxExist(MSGCMD_PET_STASH_USEITEM))
			{
				pUIManager->CloseMessageBox(MSGCMD_PET_STASH_USEITEM);
			}
			CTString strMessage, strTitle;
			CUIMsgBox_Info msgBoxInfo;
			strTitle.PrintF(_S(191, "Ȯ��"));
			msgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_OKCANCEL, UI_INVENTORY, MSGCMD_PET_STASH_USEITEM);
			strMessage.PrintF(_S(5951, "�� â�� �̿���� ��� �Ͻðڽ��ϱ�?"));
			msgBoxInfo.AddString(strMessage);
			if (pUIManager)
			{
				pUIManager->CreateMessageBox(msgBoxInfo);
				pUIManager->GetMessageBox(MSGCMD_PET_STASH_USEITEM)->SetInvenUseItemInfo(nTab, inven_idx);
			}
			return;
		}
		else if (pItemData->GetSubType() == CItemData::ITEM_SUB_INVEN_CASH_BAG_KEY)
		{
			int t = INVENTORY_TAB_CASH_1;
			if (pItemData->GetItemIndex() - INVEN_CASH_KEY2 == 0)
				t = INVENTORY_TAB_CASH_2;
			else if (pItemData->GetItemIndex() - INVEN_CASH_KEY3 == 0)
				t = INVENTORY_TAB_CASH_3;
			else if (pItemData->GetItemIndex() - INVEN_CASH_KEY4 == 0)
				t = INVENTORY_TAB_CASH_4;
			//dethunter12 add
			else if (pItemData->GetItemIndex() - INVEN_CASH_KEY5 == 0)
				t = INVENTORY_TAB_CASH_5;
			else if (pItemData->GetItemIndex() - INVEN_CASH_KEY6 == 0)
				t = INVENTORY_TAB_CASH_6;

			if (IsCashInvenMoveItem(t) == eERR_NOT_OPEN_CASH_BAG)
				pUIManager->GetInvenCashBagBox()->OpenUI(t);
			return;
		}
		else if ((pItemData->GetItemIndex() >= 2740 && pItemData->GetItemIndex() <= 2744) || pItemData->GetItemIndex() == 2740)
		{
			if (IsInventoryFull() == TRUE)
			{
				pUIManager->GetChattingUI()->AddSysMessage(_S(2850, "�κ��丮�� ���� á���ϴ�."));
				return;
			}
		}
		else if (pItemData->GetSubType() == CItemData::ITEM_SUB_GPS)
		{
			if (pItemData->getindex() == 10954)
			{
				_pNetwork->UseSlotItem(nTab, inven_idx, sbWearType);
				return;
			}
			bool bGPS = false;

			if (pItemData->GetNum0() == 1759)
				bGPS = true;

			// ��ġ�����̶��
			GAMEDATAMGR()->GetGPS()->open(bGPS);
			SetUseItemSlotInfo(nTab, inven_idx);
			return;
		}
		else if (pItemData->getindex() == 10421)
		{
			if (pUIManager->DoesMessageBoxExist(MSGCMD_ATTENDANCE_ITEM_USE))
			{
				pUIManager->CloseMessageBox(MSGCMD_ATTENDANCE_ITEM_USE);
			}

			CTString strMessage, strTitle;
			CUIMsgBox_Info msgBoxInfo;
			strTitle.PrintF(_S(191, "Ȯ��"));

			msgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_OKCANCEL, UI_INVENTORY, MSGCMD_ATTENDANCE_ITEM_USE);
			strMessage.PrintF(_S(5019, "���� [%d]��° ���� �⼮���Դϴ�."), GAMEDATAMGR()->GetAttendance()->GetAccDate());
			msgBoxInfo.AddString(strMessage);
			strMessage.PrintF(_S(6313, "�⼮ ���� ������ ����� �Ⱓ ������ ���ӿ� �������� �ʾƵ� ���� �⼮ �� ���� �״�� �����˴ϴ�. %s �� ��� �Ͻðڽ��ϱ�? "), pItemData->GetName());
			msgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(msgBoxInfo);
			pUIManager->GetMessageBox(MSGCMD_ATTENDANCE_ITEM_USE)->SetInvenUseItemInfo(nTab, inven_idx);
			return;
		}
	}

	if (pItemData->GetType() == CItemData::ITEM_POTION && pItemData->GetSubType() == CItemData::POTION_TOTEM)
	{
		if (_pNetwork->MyCharacterInfo.useTotem == true)
		{
			CTString strMsg = _S(6424, "�̹� ��ȯ �Ǿ� �ִ� ������ �����մϴ�. �ٽ� ��ȯ �Ͻðڽ��ϱ�?");

			CmdItemUseTotem* pCmd = new CmdItemUseTotem;
			pCmd->setData(nTab, inven_idx);
			MSGBOXMGR()->CreateMsgBox(_S(191, "Ȯ��"), strMsg.str_String, eMSG_YESNO, true, pCmd);
			return;
		}
	}
	_pNetwork->UseSlotItem(nTab, inven_idx, sbWearType);
}

// ----------------------------------------------------------------------------
// Name : SendSwapSlotItems()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::SendSwapSlotItems(int nTab0, int inven_idx0, int nTab1, int inven_idx1)
{
	// If arrange button is locked
	if (m_bLockArrange)
		return;
	_pNetwork->SwapItem(nTab0, inven_idx0, nTab1, inven_idx1);
}
// ----------------------------------------------------------------------------
// Name : SendUpgradeItem()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::SendUpgradeItem(INDEX iProtect)
{
	// ���ú�ȣ���� ������� ��...
	if (iProtect >= 0)
	{
		// ��ȣ���ü��� �κ� ��ġ
		SWORD	nTab, nIdx;

		if (ItemHelp::HaveItem(iProtect, &nTab, &nIdx, 1) == true)
		{
			_pNetwork->UpgradeItem(m_InLockItemInfo[IN_LOCK_REFINE].TartetWearPos, m_InLockItemInfo[IN_LOCK_REFINE].TartetVirIdx,
				m_InLockItemInfo[IN_LOCK_REFINE].TargetItem_Plus,
				m_InLockItemInfo[IN_LOCK_REFINE].UseInvenTab, m_InLockItemInfo[IN_LOCK_REFINE].UseInvenIdx,
				m_InLockItemInfo[IN_LOCK_REFINE].UseItem_Level, iProtect, nTab, nIdx);
			return;
		}
	}
	// ���ú�ȣ���� ������� ���� ��...
	else
	{
		_pNetwork->UpgradeItem(m_InLockItemInfo[IN_LOCK_REFINE].TartetWearPos, m_InLockItemInfo[IN_LOCK_REFINE].TartetVirIdx,
			m_InLockItemInfo[IN_LOCK_REFINE].TargetItem_Plus,
			m_InLockItemInfo[IN_LOCK_REFINE].UseInvenTab, m_InLockItemInfo[IN_LOCK_REFINE].UseInvenIdx,
			m_InLockItemInfo[IN_LOCK_REFINE].UseItem_Level);
	}
}

// ----------------------------------------------------------------------------
// Name : SendItemLvDown()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::SendItemLvDown()
{
	_pNetwork->ItemLevelDown(nTempIndex1, nTempIndex2);
}

// ----------------------------------------------------------------------------
// Name : SendOptionItem()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::SendOptionAddItem()
{
	_pNetwork->OptionAddItem(m_InLockItemInfo[IN_LOCK_OPTION_ADD].TargetWear_Pos,
		m_InLockItemInfo[IN_LOCK_OPTION_ADD].TartetVirIdx,
		m_InLockItemInfo[IN_LOCK_OPTION_ADD].UseInvenTab,
		m_InLockItemInfo[IN_LOCK_OPTION_ADD].UseInvenIdx,
		m_InLockItemInfo[IN_LOCK_OPTION_ADD].UseVirIdx);
}

// ----------------------------------------------------------------------------
// Name : SendOptionDelItem()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::SendOptionDelItem()
{
	_pNetwork->OptionDelItem(m_InLockItemInfo[IN_LOCK_OPTION_DEL].TargetWear_Pos,
		m_InLockItemInfo[IN_LOCK_OPTION_DEL].TartetVirIdx,
		m_InLockItemInfo[IN_LOCK_OPTION_DEL].UseInvenTab,
		m_InLockItemInfo[IN_LOCK_OPTION_DEL].UseInvenIdx,
		m_InLockItemInfo[IN_LOCK_OPTION_DEL].UseVirIdx);
}

// ========================================================================= //
//                         Receive message functions                         // 
// ========================================================================= //

// ----------------------------------------------------------------------------
// Name : InitInventory()
// Desc : For initializing inventory ( start game, arrange item ) and
//        deleting item
// ----------------------------------------------------------------------------
void CUIInventory::InitInventory(int nTab, int inven_idx, int nUniIndex, int nIndex, int nWearingType)
{
	// Empty slot
	if (nUniIndex == -1)
	{
		m_abtnItems[nTab][inven_idx]->Hide(TRUE);

		int tmpTab;

		if (nTab > 0)
		{
			tmpTab = nTab + INVENSLOT_CASH1;	// nTab == 0 : �Ϲ� �κ��丮( ���ϵ� ���� )
		}										// nTab == 1 : ĳ���κ� 1, nTab == 2 : ĳ���κ� 2
		else
		{
			tmpTab = inven_idx / INVEN_ONE_BAG;
		}

		if (tmpTab > 0 && nTab == 0)
		{
			if (((CUIChildInvenSlot*)m_pInvenSlot[tmpTab - 1])->GetSelSlotItemID() == inven_idx)
				((CUIChildInvenSlot*)m_pInvenSlot[tmpTab - 1])->SetSelSlotItemID(-1);
		}
		else if (tmpTab > 0 && nTab > 0)
		{
			if (CUIInvenCashBag* pCash = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[tmpTab - 1]))
			{
				if (pCash->GetSelSlotItemID() == inven_idx)
					pCash->SetSelSlotItemID(-1);
			}
		}
		else
		{
			if (m_nSelSlotItemID[tmpTab] == inven_idx)
				m_nSelSlotItemID[tmpTab] = -1;
		}

		return;
	}

	CItems& rItem = _pNetwork->MySlotItem[nTab][inven_idx];

	m_abtnItems[nTab][inven_idx]->Hide(FALSE);
	m_abtnItems[nTab][inven_idx]->setData(&rItem);

	// �׸��� ���� ������ �ִٸ�
	if (_pUIBuff->IsSkillBuff(564) == FALSE)
	{
		int iItemIndex = m_pIconsWearing[WEAR_HELMET]->getIndex();
		if ((((iItemIndex >= 4927 && iItemIndex <= 4932) || iItemIndex == 6228) && IS_EVENT_ON(A_EVENT_HOLLOWEEN))// ȣ��Ż �Ⱓ���� �߰��Ǿ���.
			|| (iItemIndex >= 7253 && iItemIndex <= 7259)) // [ldy1978220 2011/5/31] ���̰� 10�ֳ� �̺�Ʈ ���� �߰� ������
		{ // ȣ��Ż�� hidden �Ӽ��� npc�� �� �� �ִ�.
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetFlagOn(ENF_SHOWHIDDEN);
		}
		else
		{
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetFlagOff(ENF_SHOWHIDDEN);
		}
	}



	if (nIndex == 1577 || nIndex == 1578)
	{// ���� �ڽ� ����
		CUIManager* pUIManager = CUIManager::getSingleton();

		if (pUIManager->GetInsectCollect()->IsVisible())
			pUIManager->GetInsectCollect()->UpDateItem();
	}

	if (ItemHelp::HasReuseTimeItem(_pNetwork->MySlotItem[nTab][inven_idx]) == TRUE)
	{
		DOUBLE coolTime = ItemHelp::GetCoolTime(MY_INFO()->GetReuseItem(m_abtnItems[nTab][inven_idx]->getIndex()),
			_pNetwork->GetItemData(nIndex)->StartTime);
		if (coolTime > 0)
		{
			_pNetwork->MySlotItem[nTab][inven_idx].SetSkillDelay(TRUE);
		}
	}
}

void CUIInventory::InitWearBtn(int nIndex, int nUniIndex, int nWearingType)
{
	int iWearToal = WEAR_TOTAL;
	CUIIcon** btnWear = m_pIconsWearing;

	if (nUniIndex < 0)
	{
		btnWear[nWearingType]->clearIconData();
		return;
	}

	CItemData* pItemData = _pNetwork->GetItemData(nIndex);

	if (pItemData == NULL)
		return;

	// Wear
	//modified by sam [SAM] 11/02/09 �ѹ��ǻ� �����۵� �ڽ�Ƭ�÷��׸� �����ؼ� �����κ� ���� �� ��ư�� ����� �Ǽ� ���ϱ� ����
	if (nWearingType > -1)
	{
		btnWear[nWearingType]->setData(&_pNetwork->MyWearItem[nWearingType]);
		btnWear[nWearingType]->setWearTab(true);
	}
	else
	{
		// Unwear
		for (int iWear = 0; iWear < iWearToal; iWear++)
		{
			if (btnWear[iWear]->getItems()->Item_UniIndex == nUniIndex)
			{
				btnWear[iWear]->clearIconData();
				if (m_nSelWearItemID == iWear)
					m_nSelWearItemID = -1;

				break;
			}
		}
	}

	// �׸��� ���� ������ �ִٸ�
	if (_pUIBuff->IsSkillBuff(564) == FALSE)
	{
		int iItemIndex = m_pIconsWearing[WEAR_HELMET]->getIndex();
		if ((((iItemIndex >= 4927 && iItemIndex <= 4932) || iItemIndex == 6228) && IS_EVENT_ON(A_EVENT_HOLLOWEEN))// ȣ��Ż �Ⱓ���� �߰��Ǿ���.
			|| (iItemIndex >= 7253 && iItemIndex <= 7259)) // [ldy1978220 2011/5/31] ���̰� 10�ֳ� �̺�Ʈ ���� �߰� ������
		{ // ȣ��Ż�� hidden �Ӽ��� npc�� �� �� �ִ�.
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetFlagOn(ENF_SHOWHIDDEN);
		}
		else
		{
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetFlagOff(ENF_SHOWHIDDEN);
		}
	}
}

// ----------------------------------------------------------------------------
// Name : UpgradeItem()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::UpgradeItem(SBYTE sbResult)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// Create message box
	pUIManager->CloseMessageBox(MSGCMD_INVEN_UPGRADE_REP);

	CTString	strMessage;
	switch (sbResult)
	{
	case 0:
		strMessage = _S(176, "���׷��̵带 �����Ͽ����ϴ�. +1 ����Ͽ����ϴ�.");
		break;

	case 1:
		strMessage = _S(177, "���׷��̵带 �����Ͽ����ϴ�. -1 �ϰ��Ͽ����ϴ�.");
		break;

	case 2:
		strMessage = _S(178, "���׷��̵带 �����Ͽ����ϴ�. �����ۿ� ��ȭ�� �����ϴ�.");
		break;

	case 3:
		strMessage = _S(179, "���׷��̵带 �����Ͽ����ϴ�. �������� �ı��Ǿ����ϴ�.");
		break;
	case 4:
		strMessage = _S(2644, "�÷�Ƽ�� ���� ȿ���� ����Ǿ����ϴ�.");
		break;

		// [070824: Su-won] REFINE_PROTECT
	case 5:
		strMessage = _S(3662, "���׷��̵忡 �����Ͽ� �������� +10�� �Ǿ����ϴ�.");
		break;

	case 6://This is the custom message for ITEM_UPGRADE_RUNE_ENCHANTMENT from the server
		strMessage = ("Your item has been successfully enchanted!");
		break;
	}

	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo(_S(175, "������ ���׷��̵�"), UMBS_OK,
		UI_INVENTORY, MSGCMD_INVEN_UPGRADE_REP);
	MsgBoxInfo.AddString(strMessage);
	pUIManager->CreateMessageBox(MsgBoxInfo);

	// Unlock inventory
	Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
}
//��þƮ �ý��� Ȯ��
void CUIInventory::UpgradeItem(SBYTE sbResult, SBYTE sbplus)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// Create message box
	pUIManager->CloseMessageBox(MSGCMD_INVEN_UPGRADE_REP);

	CTString	strMessage;
	switch (sbResult)
	{
	case 0:
		strMessage.PrintF(_S(4505, "���׷��̵带 �����Ͽ����ϴ�. +%d ����Ͽ����ϴ�."), sbplus);
		break;

	case 1:
		strMessage.PrintF(_S(4506, "���׷��̵带 �����Ͽ����ϴ�. -1 �ϰ��Ͽ����ϴ�."));
		break;

	case 2:
		strMessage = _S(178, "���׷��̵带 �����Ͽ����ϴ�. �����ۿ� ��ȭ�� �����ϴ�.");
		break;

	case 3:
		strMessage = _S(179, "���׷��̵带 �����Ͽ����ϴ�. �������� �ı��Ǿ����ϴ�.");
		break;
	case 4:
		strMessage = _S(2644, "�÷�Ƽ�� ���� ȿ���� ����Ǿ����ϴ�.");
		break;

		// [070824: Su-won] REFINE_PROTECT
	case 5:
		strMessage.PrintF(_S(6454, "���׷��̵忡 �����Ͽ� �������� +%d�� �Ǿ����ϴ�."), sbplus);
		break;
	}

	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo(_S(175, "������ ���׷��̵�"), UMBS_OK,
		UI_INVENTORY, MSGCMD_INVEN_UPGRADE_REP);
	MsgBoxInfo.AddString(strMessage);
	pUIManager->CreateMessageBox(MsgBoxInfo);

	// Unlock inventory
	Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
}
// ----------------------------------------------------------------------------
// Name : OptionAddRep()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::OptionAddRep(SBYTE sbResult)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// Create message box
	pUIManager->CloseMessageBox(MSGCMD_INVEN_OPTION_ADD_REP);

	CTString	strMessage;
	switch (sbResult)
	{
	case MSG_OPTION_ADD_ERROR_SYSTEM:		// �־�� �ȵǴ� ����
		strMessage = _S(518, "�ɼ� ���̱⿡ ���� �Ͽ����ϴ�.");
		break;
	case MSG_OPTION_ADD_ERROR_WEAR:			// ������ �����۾����
		strMessage = _S(519, "������ �������̾�� �մϴ�.");
		break;
	case MSG_OPTION_ADD_ERROR_KIND:			// ���⳪ ���� �����ϴ�
		strMessage = _S(520, "���⳪ ���� �����մϴ�.");
		break;
	case MSG_OPTION_ADD_ERROR_ENABLE:		// �ɼ��� ���� �� �ִ� �������� �ƴϴ�
		strMessage = _S(521, "�ɼ��� ���� �� �ִ� �������� �ƴմϴ�.");
		break;
	case MSG_OPTION_ADD_ERROR_MAX:			// �ִ� �ɼ� �� �ʰ�
		strMessage = _S(522, "�ִ� �ɼ� ���� �ʰ� �Ͽ����ϴ�.");
		break;
	case MSG_OPTION_ADD_SUCCESS:				// �ɼ� ���̱� ����
		strMessage = _S(523, "�ɼ� ���̱⿡ �����Ͽ����ϴ�.");
		break;
	case MSG_OPTION_BLOOD_SWEAT_FRUIT_ADD_SUCCESS:
		strMessage = _S(3535, "[���������]�ǿ� ���� ������ ����Ͽ� ������ �ɼ� ���̱⿡ �����Ͽ����ϴ�.");
		break;

	}

	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo(_S(515, "������ �ɼ�"), UMBS_OK,
		UI_INVENTORY, MSGCMD_INVEN_OPTION_ADD_REP);
	MsgBoxInfo.AddString(strMessage);
	pUIManager->CreateMessageBox(MsgBoxInfo);

	// Unlock inventory
	Lock(FALSE, FALSE, LOCK_BLOOD_OPTION);
}

// ----------------------------------------------------------------------------
// Name : OptionDelRep()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::OptionDelRep(SBYTE sbResult)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// Create message box
	pUIManager->CloseMessageBox(MSGCMD_INVEN_OPTION_DEL_REP);

	CTString	strMessage;
	switch (sbResult)
	{
	case MSG_OPTION_DEL_ERROR_SYSTEM:		// �־�� �ȵǴ� ����
		strMessage = _S(524, "�ɼ� ����⿡ ���� �Ͽ����ϴ�.");
		break;
	case MSG_OPTION_DEL_ERROR_WEAR:			// ������ �����۾����
		strMessage = _S(525, "������ �������̾�� �մϴ�.");
		break;
	case MSG_OPTION_DEL_ERROR_KIND:			// ���⳪ ���� �����ϴ�
		strMessage = _S(520, "���⳪ ���� �����մϴ�.");
		break;
	case MSG_OPTION_DEL_ERROR_NUM:			// �ɼ�3�� �̻� �־�� ����� �ִ�
		strMessage = _S(526, "�ɼ��� 3�� �̻� �־�� �ɼ��� ���� �� �ֽ��ϴ�.");
		break;
	case MSG_OPTION_DEL_SUCCESS:				// �ɼ� ����� ����
		strMessage = _S(527, "�ɼ� ����� �����Ͽ����ϴ�.");
		break;
	}

	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo(_S(175, "������ ���׷��̵�"), UMBS_OK,
		UI_INVENTORY, MSGCMD_INVEN_OPTION_DEL_REP);
	MsgBoxInfo.AddString(strMessage);
	pUIManager->CreateMessageBox(MsgBoxInfo);

	// Unlock inventory
	Lock(FALSE, FALSE, LOCK_BLOOD_OPTION);
}

// ----------------------------------------------------------------------------
// Name : ClearAllItems()
// Desc :
// ----------------------------------------------------------------------------
void CUIInventory::ClearAllItems(SBYTE sbTab)
{
	if (sbTab == ITEM_TAB_NORMAL)
	{
		// Initialize wearing items
		for (int iWear = 0; iWear < WEAR_TOTAL; iWear++)
		{
			m_pIconsWearing[iWear]->clearIconData();

			if (iWear < WEAR_COSTUME_TOTAL)
			{
				m_pIconsCostumeWearing[iWear]->clearIconData();
			}
		}
	}

	// Initialize slot items
	int		i;
	for (i = 0; i < ITEM_COUNT_IN_INVENTORY_NORMAL; ++i)
	{
		SAFE_DELETE(m_abtnItems[sbTab][i]);
	}
}

// ----------------------------------------------------------------------------
// Name : GetUseItemInfo() wooss 050806
// Desc : ���� ����Ϸ��� �������� ������ ��´�
// ----------------------------------------------------------------------------

void CUIInventory::GetUseItemSlotInfo(int& nTab, int& inven_idx)
{
	nTab = m_nUseTab;
	inven_idx = m_InvenIndex;
}
void CUIInventory::SetUseItemSlotInfo(int nTab, int inven_idx)
{
	// 	m_InvenCurrentTab = static_cast<InventoryTab>((nTab>0) ? (nTab+INVEN_TAB_NORMAL4) : (nRow/INVEN_SLOT_ROW));
	// 	
	// 	if (m_InvenCurrentTab > 0 && m_InvenCurrentTab < 4)
	// 	{
	// 		m_InvenCurrentTab = static_cast<InventoryTab>(0);
	// 	}
	m_nUseTab = nTab;
	m_InvenIndex = inven_idx;
}


//------------------------------------------------------------------------------
// CUIInventory::StartSkillDelay
// Explain:  
// Date : 2005-10-11,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
BOOL CUIInventory::StartSkillDelay(int nIndex)
{
	int nTab = ((m_InvenCurrentTab - INVEN_TAB_NORMAL4) > 0) ? (m_InvenCurrentTab - INVEN_TAB_NORMAL4) : 0;

	CItems& tv_rItems = _pNetwork->MySlotItem[nTab][m_InvenIndex];
	// [2010/10/20 : Sora] �����ڵ忡�� ���� �������� ���������� ��� ��Ÿ����
	// �Ѱ������� ���ư����� �Ǿ��־ ����
	BOOL	bResult = FALSE;
	int		t, i, slot;

	for (t = 0; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
	{
		slot = GetCurTabSlotCount(t);

		for (i = 0; i < slot; ++i)
		{
			if (m_abtnItems[t][i]->getBtnType() == UBET_ITEM)
			{
				int nItemIndex = m_abtnItems[t][i]->getIndex();

				if (nItemIndex == -1)
					continue;

				CItems& rItems = _pNetwork->MySlotItem[t][i];

				if (ItemHelp::HasReuseTimeItem(rItems) == TRUE &&
					rItems.ItemData->GetNum0() == nIndex)
				{
					if (rItems.GetSkillDelay())
					{
						continue;
					}
					else
					{
						rItems.SetSkillDelay(TRUE);
						bResult = TRUE;
					}
				}

			}
		}
	}

	return bResult;
}

BOOL CUIInventory::GetSkillDelay(int nIndex)
{
	int		t, i, slot;

	for (t = 0; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
	{
		slot = GetCurTabSlotCount(t);

		for (i = 0; i < slot; ++i)
		{
			if (m_abtnItems[t][i]->getBtnType() == UBET_ITEM)
			{
				int nItemIndex = m_abtnItems[t][i]->getIndex();

				if (nItemIndex == nIndex)
				{
					if (_pNetwork->MySlotItem[t][i].GetSkillDelay())
						return TRUE;
					else
						return FALSE;
				}
			}
		}
	}

	return FALSE;
}


//------------------------------------------------------------------------------
// CUIInventory::GetItemIndex
// Explain: �κ��丮���� �������� Index�� ������ ���� �Լ� 
// Date : 2005-11-02,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
LONG CUIInventory::GetItemIndex(int nTab, int inven_idx)
{
	return _pNetwork->MySlotItem[nTab][inven_idx].Item_Index;
}
LONG CUIInventory::GetItemUniIndex(int nTab, int inven_idx)
{
	return _pNetwork->MySlotItem[nTab][inven_idx].Item_UniIndex;
}

// [070824: Su-won] REFINE_PROTECT
SLONG CUIInventory::GetUpgradeItemPlus()
{
	// ���� ��ȣ������ ��� �ϴ� �Լ�.
	// ��ȣ�� ������ ����Ҷ��� �÷�Ƽ�� ��ȭ ��ġ�� �����ؼ� �����.

	int nWearPos = m_InLockItemInfo[IN_LOCK_REFINE].TartetWearPos;

	if (nWearPos < 0 || nWearPos >= WEAR_TOTAL)
		return 0;

	CItems rItem = _pNetwork->MyWearItem[nWearPos];

	int nPlatinum_Ent, nPlus;
	FLAG_ITEM_PLATINUM_GET(rItem.Item_Flag, nPlatinum_Ent);

	// �ǻ� ���� �������� ��� ��þƮ ���� ����������..
	// �� ��Ȳ���� DB�� ����� ��þƮ���� �� �����⿣ ������ �ֱ⿡ Ŭ���̾�Ʈ���� ����� ����ϱ�� ����.
	if (rItem.IsFlag(FLAG_ITEM_COMPOSITION) && rItem.ComItem_index > 0)
	{
		nPlus = nPlatinum_Ent;
	}
	else
	{
		nPlus = rItem.Item_Plus - nPlatinum_Ent;
	}

	return nPlus;
}

INDEX CUIInventory::GetMySlotItemsCount(void)
{
	INDEX Cnt = 0;

	int t, i, slot;

	for (t = 0; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
	{
		slot = GetCurTabSlotCount(t);

		for (i = 0; i < slot; i++)
		{
			if (!_pNetwork->MySlotItem[t][i].IsEmptyItem())
			{
				++Cnt;
			}
		}
	}

	return Cnt;
}

void CUIInventory::ShowItemDestroyMessage()
{
	if (m_pIconCurSelectItem == NULL)
		return;

	CUIManager* pUIManager = CUIManager::getSingleton();

	if (pUIManager->DoesMessageBoxExist(MSGCMD_ITEMDELETE))
	{
		return;
	}

	if (m_bLockArrange == TRUE)
	{
		ShowLockErrorMessage();
		return;
	}

	INDEX nItemIndex = m_pIconCurSelectItem->getIndex();
	CItemData* pItemData = _pNetwork->GetItemData(nItemIndex);
	if (pItemData != NULL &&
		pItemData->GetType() == CItemData::ITEM_ACCESSORY &&
		(pItemData->GetSubType() == CItemData::ACCESSORY_PET /*|| pItemData->GetSubType() == CItemData::ACCESSORY_WILDPET*/))
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(3048, "���� �� ���� �������Դϴ�."), SYSMSG_ERROR);
		return;
	}

	if (m_pIconCurSelectItem->IsWearTab() == true)
	{
		pUIManager->GetChattingUI()->AddSysMessage(_S(3048, "���� �� ���� �������Դϴ�."), SYSMSG_ERROR);
		return;
	}

	if (pItemData != NULL)
	{
		if (pItemData->GetFlag() & ITEM_FLAG_NOT_DELETE ||
			(pItemData->GetType() == CItemData::ITEM_ETC && pItemData->GetSubType() == CItemData::ITEM_ETC_QUEST) ||
			(pItemData->GetFlag() & ITEM_FLAG_QUEST))
		{
			pUIManager->GetChattingUI()->AddSysMessage(_S(4696, "�ı��� �Ұ����� �������Դϴ�."), SYSMSG_ERROR);
			return;
		}
	}

	// [090810: selo] Ʈ���� �������� �ı� �� �� ����.
	if (pItemData->GetType() == CItemData::ITEM_ETC &&
		(pItemData->GetFlag() & ITEM_FLAG_TRIGGER))
	{
		CUIMsgBox_Info MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(_S(4696, "�ı��� �Ұ����� �������Դϴ�."));
		pUIManager->CreateMessageBox(MsgBoxInfo);
		return;
	}

	CUIMsgBox_Info MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo(_S(4202, "������ �ı�(������)"), UMBS_OKCANCEL, UI_INVENTORY, MSGCMD_ITEMDELETE);
	MsgBoxInfo.AddString(_S(4203, "�������� �����뿡 ������ �ı��Ǿ� �ٽ� ������ �� �����ϴ�. �׷��� �ı� �Ͻðڽ��ϱ�?"));
	pUIManager->CreateMessageBox(MsgBoxInfo);
	m_bLockSelect = true;

	Lock(TRUE, TRUE, LOCK_INVEN_ITEM_DEL);
}

// �Ϲ� ���� �� 0 ~ 3 ��
BOOL CUIInventory::FindEmptyabtnItem(int nTab, int& inven_idx)
{
	int i, tmpIdx;

	for (i = 0; i < INVEN_ONE_BAG; ++i)
	{
		tmpIdx = i + (nTab * INVEN_ONE_BAG);

		if (_pNetwork->MySlotItem[0][tmpIdx].IsEmptyItem() == TRUE)
		{
			inven_idx = tmpIdx;
			return TRUE;
		}
	}

	return FALSE;
}

// ===================================================================
//  [6/8/2009 selo]
// Name : IsRestritionItem()
// Desc : ����Ʈ ������ ������� üũ
//		  �ش� ��ġ�� �������� ����Ʈ�� ���� ������� �� ���������� Ȯ��
// ===================================================================
BOOL CUIInventory::IsRestritionItem(int nTab, int inven_idx)
{
	CItems* pItems = &_pNetwork->MySlotItem[nTab][inven_idx];
	CItemData* pItemData = pItems->ItemData;

	if (pItemData != NULL && pItemData->GetFlag() & ITEM_FLAG_QUEST)
	{
		int	nZoneNo = pItemData->GetRestrictionZoneNo();

		if (nZoneNo == _pNetwork->MyCharacterInfo.zoneNo)
		{
			FLOAT3D		restrictionPos;
			FLOAT		fRadius = (FLOAT)pItemData->GetRestrictionRadius();
			if (0 == fRadius)
				fRadius = 20.0f;

			restrictionPos(1) = (FLOAT)pItemData->GetRestrictionPosX();
			restrictionPos(2) = (FLOAT)pItemData->GetRestrictionPosY();
			restrictionPos(3) = (FLOAT)pItemData->GetRestrictionPosZ();

			FLOAT	fDiffX = _pNetwork->MyCharacterInfo.x - restrictionPos(1);
			FLOAT	fDiffZ = _pNetwork->MyCharacterInfo.z - restrictionPos(3);
			if (fDiffX * fDiffX + fDiffZ * fDiffZ > fRadius)
				return TRUE;
		}
		else
			return TRUE;
	}

	return FALSE;
}

// ----------------------------------------------------------------------------
// Name : UpgradeItem()
// Desc : [091028 sora] ���� �������� ��쿡 ��ġ���� �޾Ƽ� ���׷��̵� ���� 
//		  (sbTempRow2, sbTempCol2���� ����� ��)
// ----------------------------------------------------------------------------
void CUIInventory::UpgradeCompositedItem(int inven_idx)
{
	if (inven_idx >= 0)
	{
		UpgradeItem(inven_idx, nTempIndex2);
	}
	else
	{
		_pNetwork->ClientSystemMessage(_S(170, "���׷��̵� ���� �������� �ƴմϴ�."), SYSMSG_ERROR);
	}

	if (IsLocked())
	{
		Lock(FALSE, FALSE, LOCK_UPGRADE_ITEM);
	}
}

// ----------------------------------------------------------------------------
// Name : InitCostumeInventory()
// Desc : 
// ----------------------------------------------------------------------------
void CUIInventory::InitCostumeInventory(INDEX iUni_index, INDEX iDB_index, SBYTE sbWear_type)
{

	int iWearToal = WEAR_COSTUME_TOTAL;

	if (_pNetwork->MyCharacterInfo.bOneSuit == TRUE)
	{
		if (sbWear_type < 0)
		{
			// �ѹ��ǻ� ����
			if (_pNetwork->MyCharacterInfo.bOneSuit)
			{
				for (int iWear = 0; iWear < iWearToal; iWear++)
				{
					//_pNetwork->ga_astOneSuitOption[iWear].InitOneSuitOpt();
					m_pIconsCostumeWearing[iWear]->clearIconData();
				}
			}
			return;
		}
		else
		{
			if (_pNetwork->MyCharacterInfo.iOneSuitUniIndex == iUni_index)
			{
				//�ѹ��ǻ� ���� �� 			
				for (int k = 0; k < WEAR_COSTUME_TOTAL; ++k)
				{
					InitOneSuitItemInfo(-1, -1, _pNetwork->MyWearCostItem[k].Item_Index, _pNetwork->MyWearCostItem[k].Item_UniIndex, k);

				}
				return;
			}
		}
	}

	// �Ϲ� �ڽ�Ƭ��� ���� (�����ε��� -1�� ���� �ϰ� ������ wearPos �����ֱ�)
	if (iUni_index < 0)
	{
		m_pIconsCostumeWearing[sbWear_type]->clearIconData();
		return;
	}

	// ����ó��
	CItemData* pItemData = _pNetwork->GetItemData(iDB_index);

	if (pItemData == NULL)
		return;

	// �Ϲ� �ڽ�Ƭ �Ա� (����, �������ε���, ������ġ ��� ����)
	if (sbWear_type > -1)
	{
		m_pIconsCostumeWearing[sbWear_type]->setData(&_pNetwork->MyWearCostItem[sbWear_type]);
		m_pIconsCostumeWearing[sbWear_type]->setWearTab(true);
	}
}

__int64 CUIInventory::GetItemCountByUniIdx(int nUniqueIndex)
{
	int		t, i, slot;

	for (t = 0; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
	{
		slot = GetCurTabSlotCount(t);

		for (i = 0; i < slot; ++i)
		{
			if (_pNetwork->MySlotItem[t][i].Item_UniIndex == nUniqueIndex)
			{
				return _pNetwork->MySlotItem[t][i].Item_Sum;
			}
		}
	}

	return 0;
}
CUIIcon* CUIInventory::GetItemIcon(int nUniqueIndex)
{
	int nTab = 0, nIndex = 0;
	int		t, i, slot;

	for (t = 0; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
	{
		slot = GetCurTabSlotCount(t);

		for (i = 0; i < slot; ++i)
		{
			if (_pNetwork->MySlotItem[t][i].Item_UniIndex == nUniqueIndex)
			{
				nTab = t;
				nIndex = i;

				// end
				t = INVENTORY_TAB_CASH_6 + 1;
				break;
			}
		}
	}

	return m_abtnItems[nTab][nIndex];
}

CItems* CUIInventory::GetItems(int nUniqueIndex)
{
	int nTab = 0, nIndex = 0;
	int		t, i, slot;

	for (t = 0; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
	{
		slot = GetCurTabSlotCount(t);

		for (i = 0; i < slot; ++i)
		{
			if (_pNetwork->MySlotItem[t][i].Item_UniIndex == nUniqueIndex)
			{
				return &_pNetwork->MySlotItem[t][i];
			}
		}
	}

	return NULL;
}

// ----------------------------------------------------------------------------
// Name : GetItemVisble()
// [5/9/2013 ranma] Desc : �κ��丮�� �����ϴ��� �˻�.
// ----------------------------------------------------------------------------
BOOL CUIInventory::GetItemVisble(int nUniqueIndex)
{
	int		t, i, slot;

	for (t = 0; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
	{
		slot = GetCurTabSlotCount(t);

		for (i = 0; i < slot; ++i)
		{
			if (_pNetwork->MySlotItem[t][i].Item_UniIndex == nUniqueIndex)
				return TRUE;
		}
	}

	return FALSE;
}
// ----------------------------------------------------------------------------
// Name : IsInventoryFull()
// [5/9/2013 ranma] Desc : �κ��丮�� ���� á���� �˻�.
// ----------------------------------------------------------------------------
BOOL CUIInventory::IsInventoryFull()
{
	int t, i, slot;
	for (t = INVENTORY_TAB_NORMAL; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
	{
		if (t >= INVENTORY_TAB_CASH_1)
		{
			if (CUIInvenCashBag* pCash = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[t + INVENSLOT_NUM3]))
			{
				if (pCash->IsInvenCashBagLock() == true)
					continue;
			}
		}

		slot = GetCurTabSlotCount(t);

		for (i = 0; i < slot; ++i)
		{
			if (_pNetwork->MySlotItem[t][i].IsEmptyItem() == TRUE)
				return FALSE;
		}
	}

	return TRUE;
}

// ----------------------------------------------------------------------------
// Name : SetInventoryType()
// Desc : [kiny8216]�κ��丮 �� Ÿ�� ����
// ----------------------------------------------------------------------------
void CUIInventory::SetInventoryType(int iType)
{
	if (IsVisible() && m_iInventoryType != iType)
	{
		m_iInventoryType = iType;
		m_btnInvenTab[iType].SetBtnState(UBS_ON);
		m_btnInvenTab[1 - iType].SetBtnState(UBS_IDLE);
	}
}

// added by sam 11/02/01 [SAM]
// ----------------------------------------------------------------------------
// Name : InitOneSuitItemInfo()
// Desc : �ѹ� �ǻ� ���Ե� �� �ǻ��� ������ ����
//		iDB_index �� �������� �������� ���ؽ� 
//		uni_index�� �ѹ� �������� ���̵� 
// ----------------------------------------------------------------------------
void CUIInventory::InitOneSuitItemInfo(int nTab, int inven_idx, INDEX iDB_index, INDEX iUni_index, INDEX sbWear_type)
{
	//���� �� 
	if (iDB_index > -1)
	{
		CItemData* pTempData = _pNetwork->GetItemData(iDB_index);

		if (sbWear_type == pTempData->GetWearingPosition() /* || ( pTempData->GetWearingPosition() == WEAR_BACKWING  &&  sbWear_type == WEAR_COSTUME_BACKWING)*/)
		{
			m_pIconsCostumeWearing[sbWear_type]->setData(&_pNetwork->MyWearCostItem[sbWear_type]);
			m_pIconsCostumeWearing[sbWear_type]->setWearTab(true);
		}
	}
	else
	{
		m_pIconsCostumeWearing[sbWear_type]->clearIconData();
	}
}

void CUIInventory::FocusLeave()
{

}

void CUIInventory::SetCurSelectItem(CUIIcon* abtn)
{
	m_pIconCurSelectItem = abtn;
}

void CUIInventory::UpdateSelectItem()
{
	if (m_nSelSlotItemID[0] >= 0)
	{
		int		x, y;
		m_abtnItems[0][m_nSelSlotItemID[0]]->GetPos(x, y);
		m_pImgSelect->SetPos(x, y);
		m_pImgSelect->Hide(FALSE);
	}
	else
	{
		m_pImgSelect->Hide(TRUE);
	}
}

void CUIInventory::ShowDivideMsgBox(SWORD nTab, SWORD nInvenIdx)
{
	CUIIcon* pDrag = UIMGR()->GetDragIcon();

	if (pDrag == NULL)
		return;

	CItems* pItems = pDrag->getItems();

	if (pItems == NULL)
		return;

	CUIMsgBox_Info	MsgBoxInfo;
	CTString strMessage;
	strMessage.PrintF(_S(5796, "�и��� ������ ������ �Է����ּ���."));

	CItemData* pItemData = pItems->ItemData;

	CmdInvenDivideItem* pCmd = new CmdInvenDivideItem;
	pCmd->setData(this);
	UIMGR()->GetMsgBoxNumOnly()->SetInfo(pCmd, _S(166, "�κ��丮"), strMessage, 1, pItems->Item_Sum);

	m_InLockItemInfo[IN_LOCK_DIVIDE].UseInvenTab = pItems->Item_Tab;
	m_InLockItemInfo[IN_LOCK_DIVIDE].UseInvenIdx = pItems->InvenIndex;
	m_InLockItemInfo[IN_LOCK_DIVIDE].TargetTab = nTab;
	m_InLockItemInfo[IN_LOCK_DIVIDE].TargetInvenIdx = nInvenIdx;
}

bool CUIInventory::IsDivideItem(SWORD nTabS, SWORD nIdxS, SWORD nTabT, SWORD nIdxT)
{
	// �ҽ��� �и��� �����ؾ� �Ѵ�.
	if ((_pNetwork->MySlotItem[nTabS][nIdxS].ItemData->GetFlag() & ITEM_FLAG_COUNT) == false)
		return false;

	if (_pNetwork->MySlotItem[nTabS][nIdxS].Item_Sum <= 1)
		return false;

	if (_pNetwork->MySlotItem[nTabT][nIdxT].IsEmptyItem() == FALSE)
		return false;

	return true;
}

void CUIInventory::SetCashBagExpireTime(int type)
{
	if (type == TIMERITEM_TYPE_CASH_INVENTORY_1)
	{
		if (CUIInvenCashBag* pCash = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[INVENSLOT_CASH1]))
			pCash->SetCashBagExpireTime(type);
	}
	else if (type == TIMERITEM_TYPE_CASH_INVENTORY_2)
	{
		if (CUIInvenCashBag* pCash = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[INVENSLOT_CASH2]))
			pCash->SetCashBagExpireTime(type);
	}
	else if (type == TIMERITEM_TYPE_CASH_INVENTORY_3)
	{
		if (CUIInvenCashBag* pCash = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[INVENSLOT_CASH3]))
			pCash->SetCashBagExpireTime(type);
	}
	else if (type == TIMERITEM_TYPE_CASH_INVENTORY_4)
	{
		if (CUIInvenCashBag* pCash = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[INVENSLOT_CASH4]))
			pCash->SetCashBagExpireTime(type);
	}
	else if (type == TIMERITEM_TYPE_CASH_INVENTORY_5)
	{
		if (CUIInvenCashBag* pCash = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[INVENSLOT_CASH5]))
			pCash->SetCashBagExpireTime(type);
	}
	else if (type == TIMERITEM_TYPE_CASH_INVENTORY_6)
	{
		if (CUIInvenCashBag* pCash = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[INVENSLOT_CASH6]))
			pCash->SetCashBagExpireTime(type);
	}
}

int CUIInventory::IsCashInvenMoveItem(int inven_tab, int inven_idx /* = -1 */, int target_tab /* = -1 */, int target_idx /* = -1 */)
{
	int nCashInven = -1;

	if (target_tab + INVENSLOT_NUM3 >= INVENSLOT_CASH1 && INVENSLOT_CASH6 >= target_tab + INVENSLOT_NUM3) //4-6
	{
		nCashInven = target_tab + INVENSLOT_NUM3;

		if (nCashInven > INVENSLOT_NUM3)	// ĳ�� �κ�.
		{
			if (CUIInvenCashBag* pCash = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[nCashInven]))
			{
				if (pCash->IsInvenCashBagLock() == true)
				{
					return eERR_NOT_OPEN_CASH_BAG;
				}
			}
		}
	}

	if (inven_tab + INVENSLOT_NUM3 >= INVENSLOT_CASH1 && INVENSLOT_CASH6 >= target_tab + INVENSLOT_NUM3) //4-6
	{
		CItems* pItem = &_pNetwork->MySlotItem[target_tab][target_idx];
		CItemData* pItemData = pItem->ItemData;

		nCashInven = inven_tab + INVENSLOT_NUM3;

		if (pItemData != NULL)
		{
			if (CUIInvenCashBag* pCash = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[nCashInven]))
			{
				if (pCash->IsInvenCashBagLock() == true)
				{
					return eERR_NOT_OPEN_CASH_BAG;
				}
			}
		}

	}

	return eERR_NONE;
}

void CUIInventory::ErrMessage(int errCode)
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString strMessage;
	CUIMsgBox_Info	MsgBoxInfo;

	MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

	switch (errCode)
	{
	case eERR_NOT_OPEN_CASH_BAG:
	{
		strMessage.PrintF(_S(6062, "���̸��� ������ ����־� �������� ���� �� �����ϴ�. ���踦 ����Ͽ� �ֽñ� �ٶ��ϴ�."));
	}
	break;
	case eERR_FLAG_COMPOSITION:
		strMessage.PrintF(_S(6078, "���̸��� ���濡 ���� �� ���� �������Դϴ�."));
		// �������� ������ �̵� �Ұ�
		break;
	}

	if (strMessage.IsEmpty() == FALSE)
	{
		MsgBoxInfo.AddString(strMessage);
		pUIManager->CreateMessageBox(MsgBoxInfo);
	}
}

void CUIInventory::CashInvenLockOn()
{
	int t;
	for (t = INVENSLOT_CASH1; t < INVENSLOT_MAX; t++)
	{
		if (CUIInvenCashBag* pCash = dynamic_cast<CUIInvenCashBag*>(m_pInvenSlot[t]))
		{
			pCash->InvenCashBagLockOn();
		}
	}
}

int	CUIInventory::GetCurTabSlotCount(int tab)
{
	if (tab == INVENTORY_TAB_NORMAL)			return ITEM_COUNT_IN_INVENTORY_NORMAL;
	else if (tab == INVENTORY_TAB_CASH_1)		return ITEM_COUNT_IN_INVENTORY_CASH_1;
	else if (tab == INVENTORY_TAB_CASH_2)		return ITEM_COUNT_IN_INVENTORY_CASH_2;
	else if (tab == INVENTORY_TAB_CASH_3)		return ITEM_COUNT_IN_INVENTORY_CASH_3;
	else if (tab == INVENTORY_TAB_CASH_4)		return ITEM_COUNT_IN_INVENTORY_CASH_4;
	else if (tab == INVENTORY_TAB_CASH_5)		return ITEM_COUNT_IN_INVENTORY_CASH_5;
	else return ITEM_COUNT_IN_INVENTORY_CASH_6;
}

void CUIInventory::SendSortInventory()
{
	CNetworkMessage nmMessage;
	RequestClient::doItemInventorySort* packet = reinterpret_cast<RequestClient::doItemInventorySort*>(nmMessage.nm_pubMessage);
	packet->type = MSG_ITEM;
	packet->subType = MSG_ITEM_SORT_INVENTORY;
	nmMessage.setSize(sizeof(*packet));
	_pNetwork->SendToServerNew(nmMessage);
}

void CUIInventory::ClearNewItemEffect()
{
	for (int i = 0; i < INVEN_ONE_BAG; i++)
	{
		m_bNewItem[i] = FALSE;
		m_bStartEffectItem[i] = FALSE;
		m_nPlayCount[i] = 0;

		if (m_abtnItems[0][i] != NULL)
			m_abtnItems[0][i]->setImage(eIMG_TYPE_NEW, false);
	}
}

void CUIInventory::ClearNewBagEffect()
{
	for (int i = 0; i < INVENSLOT_MAX; i++)
	{
		m_bNewItemBag[i] = FALSE;
		m_bStartEffectBag[i] = FALSE;
		m_nBagPlayCount[i] = 0;
	}
}

BOOL CUIInventory::IsPlayNewItemEffect(int InvenIdx)
{
	if (InvenIdx < 0 || InvenIdx >= INVEN_ONE_BAG)
		return FALSE;

	return m_bNewItem[InvenIdx];
}

void CUIInventory::SetNewItemEffect(BOOL bShowEffect, int InvenIdx)
{
	if (InvenIdx < 0 || InvenIdx >= INVEN_ONE_BAG)
		return;

	m_bNewItem[InvenIdx] = bShowEffect;
	m_bStartEffectItem[InvenIdx] = FALSE;
	m_nPlayCount[InvenIdx] = 0;

	if (IsVisible() != FALSE)
		SetStartEffectItem(InvenIdx);


}

BOOL CUIInventory::IsCheckNewItemEffectPlayCount(int InvenIdx)
{
	CInvenData* pInvenData = CInvenData::getSingleton();

	if (pInvenData == NULL)
		return FALSE;

	if (InvenIdx < 0 || InvenIdx >= INVEN_ONE_BAG)
		return FALSE;

	int nEffectCount = pInvenData->GetPlayCount();

	if (nEffectCount == -1)
		return TRUE;

	if (m_bStartEffectItem[InvenIdx] == FALSE)
		return FALSE;

	int nCount = pInvenData->GetRenderCount() - m_nPlayCount[InvenIdx];

	if (nCount > nEffectCount)
	{
		SetNewItemEffect(FALSE, InvenIdx);
		return FALSE;
	}

	return TRUE;
}

BOOL CUIInventory::IsPlayNewBagEffect(eInvenSlot eBagPos)
{
	if (eBagPos < INVENSLOT_NUM1 || eBagPos >= INVENSLOT_MAX)
		return FALSE;

	return m_bNewItemBag[eBagPos];
}

void CUIInventory::SetNewItemBagEffect(BOOL bShowEffect, eInvenSlot eBagPos)
{
	if (eBagPos < INVENSLOT_NUM1 || eBagPos >= INVENSLOT_MAX)
		return;

	if (m_bSlot[eBagPos] == TRUE)
	{
		m_bNewItemBag[eBagPos] = FALSE;
		m_nBagPlayCount[eBagPos] = 0;
		return;
	}

	m_bNewItemBag[eBagPos] = bShowEffect;
	m_bStartEffectBag[eBagPos] = FALSE;
	m_nBagPlayCount[eBagPos] = 0;

	if (IsVisible() != FALSE)
		SetStartEffectBag(eBagPos);
}

BOOL CUIInventory::IsCheckNewBagEffectPlayCount(eInvenSlot eBagPos)
{
	CInvenData* pInvenData = CInvenData::getSingleton();

	if (pInvenData == NULL)
		return FALSE;

	if (eBagPos < INVENSLOT_NUM1 || eBagPos >= INVENSLOT_MAX)
		return FALSE;

	int nEffectCount = pInvenData->GetPlayCount();

	if (nEffectCount == -1)
		return TRUE;

	if (m_bStartEffectBag[eBagPos] == FALSE)
		return FALSE;

	int nCount = pInvenData->GetRenderCount() - m_nBagPlayCount[eBagPos];

	if (nCount > nEffectCount)
	{
		SetNewItemBagEffect(FALSE, eBagPos);
		return FALSE;
	}

	return TRUE;
}

void CUIInventory::SetStartEffectItem(int InvenIdx)
{
	if (InvenIdx < 0 || InvenIdx >= INVEN_ONE_BAG)
		return;

	if (m_bNewItem[InvenIdx] == FALSE)
		return;

	CInvenData* pInvenData = CInvenData::getSingleton();

	if (pInvenData == NULL)
		return;

	m_bStartEffectItem[InvenIdx] = TRUE;
	m_nPlayCount[InvenIdx] = pInvenData->GetRenderCount();
}

void CUIInventory::SetStartEffectBag(eInvenSlot eBagPos)
{
	if (eBagPos < INVENSLOT_NUM1 || eBagPos >= INVENSLOT_MAX)
		return;

	if (m_bNewItemBag[eBagPos] == FALSE)
		return;

	CInvenData* pInvenData = CInvenData::getSingleton();

	if (pInvenData == NULL)
		return;

	m_bStartEffectBag[eBagPos] = TRUE;
	m_nBagPlayCount[eBagPos] = pInvenData->GetRenderCount();
}

void CUIInventory::UpdateNewItemEffect()
{
	CInvenData* pInvenData = CInvenData::getSingleton();

	if (pInvenData == NULL)
		return;

	DWORD m_nTime = timeGetTime();

	if (m_nTime >= m_nEffectTime)
	{
		m_nEffectTime = m_nTime + pInvenData->GetEffectSpeed();

		BOOL bShow = !pInvenData->IsNewItemEffectRender();
		pInvenData->SetShowEffectFlag(bShow);

		if (bShow == TRUE)
			pInvenData->AddRenderTickCount();
	}
}

void CUIInventory::ShowArrangeToolTip(BOOL bShow)
{
	if (!bShow)
	{
		m_bShowToolTip = FALSE;
		return;
	}

	m_bShowToolTip = TRUE;

	int	nInfoX, nInfoY, nX, nY;

	m_strToolTip = _S(7001, "�κ��丮 ����");

	int	nInfoWidth = _pUIFontTexMgr->GetFontSpacing() + m_strToolTip.Length() * (_pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing());
	int	nInfoHeight = (DEF_TOOLTIP_YGAP * 2) + _pUIFontTexMgr->GetFontHeight();

	m_btnArrange.GetPos(nX, nY);
	nInfoX = m_nPosX + nX + m_btnArrange.GetWidth() + 2;
	nInfoY = m_nPosY + nY + (m_btnArrange.GetHeight() - _pUIFontTexMgr->GetLineHeight()) / 2;

	if (nInfoX + nInfoWidth > CUIManager::getSingleton()->GetMaxI())
		nInfoX = CUIManager::getSingleton()->GetMaxI() - nInfoWidth;

	m_rcToolTip.Left = nInfoX;
	m_rcToolTip.Top = nInfoY;
	m_rcToolTip.Right = m_rcToolTip.Left + nInfoWidth + (DEF_TOOLTIP_XGAP * 2);
	m_rcToolTip.Bottom = m_rcToolTip.Top + nInfoHeight;
}

void CUIInventory::DivideItemCallback()
{
	CItems* pItem = &_pNetwork->MySlotItem[m_InLockItemInfo[IN_LOCK_DIVIDE].UseInvenTab][m_InLockItemInfo[IN_LOCK_DIVIDE].UseInvenIdx];
	int nCount = UIMGR()->GetMsgBoxNumOnly()->GetData();

	if (pItem != NULL)
	{
		if (pItem->Item_Sum < nCount || nCount <= 0)
		{
			// ������ ���� ����!!
			return;
		}
	}

	_pNetwork->DivideItem(m_InLockItemInfo[IN_LOCK_DIVIDE].UseInvenTab,
		m_InLockItemInfo[IN_LOCK_DIVIDE].UseInvenIdx,
		m_InLockItemInfo[IN_LOCK_DIVIDE].TargetTab,
		m_InLockItemInfo[IN_LOCK_DIVIDE].TargetInvenIdx,
		nCount);
}

void CUIInventory::SetIconNewItem(int nTab, int idx, bool bOn)
{
	m_abtnItems[nTab][idx]->setImage(eIMG_TYPE_NEW, bOn);
}

void CUIInventory::OnUpdate(float fDeltaTime, ULONG ElapsedTime)
{
	int		t, i;
	for (t = 0; t < INVENTORY_TAB_MAX; ++t)
	{
		for (i = 0; i < ITEM_COUNT_IN_INVENTORY_NORMAL; ++i)
		{
			if (m_abtnItems[t][i] != NULL)
				m_abtnItems[t][i]->Update(fDeltaTime, ElapsedTime);
		}
	}

	for (i = 0; i < WEAR_TOTAL; ++i)
	{
		if (m_pIconsWearing[i] != NULL)
			m_pIconsWearing[i]->Update(fDeltaTime, ElapsedTime);
	}
}

bool CUIInventory::IsNotCompositionItem(int nItemDBIdx)
{
	CItemData* pItemData = CItemData::getData(nItemDBIdx);

	if (pItemData == NULL)
		return false;

	if (!(pItemData->GetFlag() & ITEM_FLAG_COMPOSITE) &&
		!(pItemData->GetFlag() & FLAG_ITEM_TRANSMOGRIFY))
		return true;

	int		t, i, slot;
	for (t = 0; t <= INVENTORY_TAB_CASH_6; ++t) //4-6
	{
		slot = GetCurTabSlotCount(t);

		for (i = 0; i < slot; ++i)
		{
			if (_pNetwork->MySlotItem[t][i].Item_Index == nItemDBIdx)
			{
				if (_pNetwork->MySlotItem[t][i].Item_Flag & FLAG_ITEM_COMPOSITION)
					continue;

				return true;
			}
		}
	}
	return false;
}

bool CUIInventory::IsWearingItem(int nDBIndex)
{
	for (int i = 0; i < WEAR_TOTAL; ++i)
	{
		if (m_pIconsWearing[i]->IsEmpty() == true)
			continue;

		if (m_pIconsWearing[i]->getIndex() == nDBIndex)
			return true;
	}

	return false;
}


