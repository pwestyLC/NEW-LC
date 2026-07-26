#include "stdh.h"

// ������� ����. [12/1/2009 rumist]
// [6/17/2009 rumist] include definition stat. 
#include <Engine/LocalDefine.h>
#include <Engine/Network/MessageDefine.h>
#include <Engine/Interface/UISpriteAni.h>
#include <Engine/Interface/UIImage.h>
#include <Engine/Interface/UITextureManager.h>
#include <Engine/Interface/UIPetInfo.h>
#include <Engine/Help/Util_Help.h>
#include <Engine/Interface/UIImageFont.h>
#include <Engine/Help/ItemHelp.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Interface/UIGuild.h>
#include <Engine/Contents/Base/UICharacterInfoNew.h>
#include <Engine/Interface/UIMonsterCombo.h>
#include <Engine/Contents/Base/UIPartyNew.h>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Interface/UIWildPetInfo.h>
#include <Engine/Interface/UIMonsterMercenary.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/Base/Syndicate.h>
#include <Engine/Interface/UIChatting.h>

// [sora] hpǥ�� �ؽ��� ��ġ
// [2012/08/27 : Sora] EX�α� �߰�
const int siExpeditionStartUV[TOTAL_JOB][2] = {
												{335,166},
												{335,182},
												{335,198},
												{335,214},
												{335,230},
												{335,246},
												{335,262},
#ifdef CHAR_EX_ROGUE
												{335,230},
#endif
#ifdef CHAR_EX_MAGE
												{355,214}	//2013/01/08 jeil EX������ �߰� 
#endif
												};
// ----------------------------------------------------------------------------
// Name : CUIButtonEx()
// Desc : Constructor
// ----------------------------------------------------------------------------
CUIButtonEx::CUIButtonEx()
	: m_bWearTab(false)
#ifdef DURABILITY
	, m_imgDurabilityZero(NULL)
	, m_bDuraZero(false)
#endif	//	DURABILITY
	, m_paniToggle(NULL)
{
	m_nTab = -1;
	m_InvenIndex = -1;
	m_nServerIdx = -1;

	InitBtn();
	m_bSkillDelay = FALSE;
	m_pExpeditionTexture = NULL;
	m_ptdAddTexture = NULL;
	m_iColor = 0xFFFFFFFF;

	// �Ӽ� �ý��� [1/22/2013 Ranma]
	m_ptdAttrTexture = NULL;
	m_ptdSocketTexture = NULL;
	m_ptdJewelGradeTexture = NULL;
	m_pImageFont = NULL;

	m_bToggleState = false;
	m_nDurNow = 0;
	m_nDurMax = 0;
}

// ----------------------------------------------------------------------------
// Name : ~CUIButtonEx()
// Desc : Destructor
// ----------------------------------------------------------------------------
CUIButtonEx::~CUIButtonEx()
{
	Destroy();
}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight,
							SBYTE nWhichUI, UIBtnExType betType, SBYTE nTab, LONG inven_idx )
{
	CUIWindow::Create(pParentWnd, nX, nY, nWidth, nHeight);

	m_nWhichUI = nWhichUI;
	m_betType = betType;
	m_nTab = nTab;
	m_InvenIndex = inven_idx;

	// Identification of button
	static UWORD	uwBtnID = 0;
	m_uwBtnID = uwBtnID++;
	m_bSkillDelay = FALSE;

	m_ptdAddTexture = CreateTexture( CTString( "Data\\Interface\\CommonBtn.tex" ) );
	m_pExpeditionTexture =  CreateTexture( CTString( "Data\\Interface\\Expedition.tex" ) );

	FLOAT	fTexWidth = m_ptdAddTexture->GetPixWidth();
	FLOAT	fTexHeight = m_ptdAddTexture->GetPixHeight();

	//m_rtPopupInfo.SetUV(0,137,141,227,fTexWidth,fTexHeight);
	m_bxPopupInfo.SetBoxUV(m_ptdAddTexture,20,WRect(0,137,141,227));
	m_rtPopupName.SetUV(0,229,85,251,fTexWidth,fTexHeight);

	// �Ӽ� �ý��� ������ UV [1/17/2013 Ranma]
	m_ptdAttrTexture = CreateTexture( CTString( "Data\\Interface\\NewCharacterInfo.tex" ) );
	
	fTexWidth = m_ptdAttrTexture->GetPixWidth();
	fTexHeight = m_ptdAttrTexture->GetPixHeight();

	
	// ��
	m_rtAttributeIconAtt[eICON_ATTR_NONE].SetUV(266, 717, 304, 755, fTexWidth, fTexHeight );
	m_rtAttributeIconDef[eICON_ATTR_NONE].SetUV(307, 717, 345, 755, fTexWidth, fTexHeight );
	// ��
	m_rtAttributeIconAtt[eICON_ATTR_FIRE].SetUV(266, 757, 304, 795, fTexWidth, fTexHeight );
	m_rtAttributeIconDef[eICON_ATTR_FIRE].SetUV(307, 757, 345, 795, fTexWidth, fTexHeight );
	// ��
	m_rtAttributeIconAtt[eICON_ATTR_WATER].SetUV(266, 798, 304, 836, fTexWidth, fTexHeight );
	m_rtAttributeIconDef[eICON_ATTR_WATER].SetUV(307, 798, 345, 836, fTexWidth, fTexHeight );
	// ����
	m_rtAttributeIconAtt[eICON_ATTR_EARTH].SetUV(266, 880, 304, 918, fTexWidth, fTexHeight );
	m_rtAttributeIconDef[eICON_ATTR_EARTH].SetUV(307, 880, 345, 918, fTexWidth, fTexHeight );
	// �ٶ�
	m_rtAttributeIconAtt[eICON_ATTR_WIND].SetUV(266, 839, 304, 877, fTexWidth, fTexHeight );
	m_rtAttributeIconDef[eICON_ATTR_WIND].SetUV(307, 839, 345, 877, fTexWidth, fTexHeight );
	// ��
	m_rtAttributeIconAtt[eICON_ATTR_DARK].SetUV(266, 962, 304, 1000, fTexWidth, fTexHeight );
	m_rtAttributeIconDef[eICON_ATTR_DARK].SetUV(307, 962, 345, 1000, fTexWidth, fTexHeight );
	// ��
	m_rtAttributeIconAtt[eICON_ATTR_LIGHT].SetUV(266, 921, 304, 959, fTexWidth, fTexHeight );
	m_rtAttributeIconDef[eICON_ATTR_LIGHT].SetUV(307, 921, 345, 959, fTexWidth, fTexHeight );

	// �Ӽ� �ý��� [1/22/2013 Ranma]
	m_nAtt = 0;
	m_nDef = 0;
	m_bAttribute = FALSE;

	m_ptdSocketTexture = CreateTexture( CTString( "Data\\Interface\\SocketSystemEx.tex" ) );
	
	fTexWidth = m_ptdSocketTexture->GetPixWidth();
	fTexHeight = m_ptdSocketTexture->GetPixHeight();

	// ī���� ���� ���������
	m_rtSocketIcon[SOCKET_CHAOS_NONE].SetUV(196, 123, 214, 139, fTexWidth, fTexHeight );
	// ī���� ���� ���� �Ǿ��� ���
	m_rtSocketIcon[SOCKET_CHAOS_EQUIP].SetUV(175, 123, 193, 139, fTexWidth, fTexHeight );
	// �Ϲ� ���� ��� ���� ���
	m_rtSocketIcon[SOCKET_GENERAL_NONE].SetUV(196, 144, 214, 160, fTexWidth, fTexHeight );
	// �Ϲ� ���� ���� �Ǿ� ���� ���
	m_rtSocketIcon[SOCKET_GENERAL_EQUIP].SetUV(175, 144, 193, 160, fTexWidth, fTexHeight );

	m_bSocketCreatedItem = FALSE;

	int i;
	for(i = 0; i < MAX_SOCKET_OPTION; i++)
	{
		m_nSocketInfoShowLine[i] = 0;
	}

	m_ptdJewelGradeTexture = CreateTexture( CTString("Data\\Interface\\Jewel_Compos.tex") );

	fTexWidth = m_ptdJewelGradeTexture->GetPixWidth();
	fTexHeight = m_ptdJewelGradeTexture->GetPixHeight();

	int nX1 = 194; // Jewel_Compos.tex �� ��� ǥ�� �̹����� 3�ٷ� ��� �����Ǿ� �ִ�
	int nX2 = 215; // X�� 3������ ���ٸ��� �����ϴ� Y���� ���Ͽ� �����Ѵ�
	int nX3 = 236; // ������ 9��°���� ��ư������ ������ �� �������µ� if���� �װͶ����� ����Ͽ���.
	int nY1 = JEWEL_GRADE_START_Y;
	int nYgapTab;
	for (i = 0, nYgapTab = 0; i < JEWEL_GRADE_MAX; i+=3, nYgapTab++)
	{		
		if (nYgapTab >= 8)
			nY1 = JEWEL_GRADE_START_Y + (JEWEL_GRADE_GROW_Y * nYgapTab) + 34;
		else
			nY1 = JEWEL_GRADE_START_Y + (JEWEL_GRADE_GROW_Y * nYgapTab);
		
		m_rtGradeIcon[i].SetUV(nX1, nY1, nX1 + JEWEL_GRADE_BTN_SIZE, nY1 + JEWEL_GRADE_BTN_SIZE, fTexWidth, fTexHeight);
		m_rtGradeIcon[i + 1].SetUV(nX2, nY1, nX2 + JEWEL_GRADE_BTN_SIZE, nY1 + JEWEL_GRADE_BTN_SIZE, fTexWidth, fTexHeight);
		m_rtGradeIcon[i + 2].SetUV(nX3, nY1, nX3 + JEWEL_GRADE_BTN_SIZE, nY1 + JEWEL_GRADE_BTN_SIZE, fTexWidth, fTexHeight);
	}

	m_pImageFont = new CUIImageFont;
	UIRectUV uv;
	uv.U0 = 1;
	uv.V0 = 478;
	uv.U1 = uv.U0 + 97;
	uv.V1 = uv.V0 + 10;
	m_pImageFont->setTexString("NewInventory.tex");
	m_pImageFont->setOrigString("0123456789");
	m_pImageFont->setFontSizeGap(7, 10, 3);
	m_pImageFont->setSourceImage(uv);
	m_pImageFont->setOutputGap(-3);

#ifdef DURABILITY
	m_imgDurabilityZero = new CUIImage;

	m_imgDurabilityZero->setTexString("NewInventory.tex");
	m_imgDurabilityZero->InitPos(0, 0, BTN_SIZE, BTN_SIZE);
	UIRectUV DurUv;
	DurUv.SetUV(196, 441, 196+34, 441+34);
	m_imgDurabilityZero->SetUV(DurUv);
#endif	//	DURABILITY

	// Toggle Ani Set
	m_paniToggle = new CUISpriteAni;
	m_paniToggle->setTexString("toggleskill.tex");
	
	int nToggleSize = 64;
	
	m_paniToggle->InitPos(0, 0, nToggleSize, nToggleSize);
	m_paniToggle->SetRenderIdx(0);
	UIRectUV toggleUv;
	int j;
	for (i = 0; i < 2; i++)
	{
		int y = nToggleSize * i;

		for (j = 0; j < 4; j++)
		{
			int x = nToggleSize * j;
			toggleUv.SetUV(x, y, x + nToggleSize, y + nToggleSize);
			m_paniToggle->PushUV(toggleUv);
		}		
	}	
}

// ----------------------------------------------------------------------------
// Name : InitBtn()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::InitBtn()
{
	int		i;
	m_nIndex = -1;
	m_nUniIndex = -1;
	
	m_nCashIndex = -1;
	m_nCashType = -1;
	m_nCashName = "";
	m_nCashDesc = "";
	m_nCashListCount = -1;
	m_nCashTypeIndex = -1;
		
	m_nWearType = -1;
	m_ulPlus = 0;
	m_ulFlag = 0;
	m_llCount = 0;
	m_llPrice = 0;
	m_llTime = 0;

	for( i = 0; i < MAX_OPTION_INC_ORIGIN; ++i )
	{
		m_sbOptionType[i] = -1;
		m_lOptionLevel[i] = 0;
		m_lOriginOptionVar[i] = ORIGIN_VAR_DEFAULT;
	}

	m_nTextureID = -1;
	m_betType = UBET_ITEM;
	m_bEmpty = TRUE;
	m_bsState = UBES_IDLE;
	m_bSpecial	= FALSE;		// Dongmin
	m_ulUsed = 0;
	m_bSkillDelay = FALSE;
	m_bLButtonDown = FALSE;

	m_bShow = FALSE;

	m_uwRareIndex =0;
	for( i = 0; i < MAX_ITEMINFO_LINE; ++i )
	{
		m_strButtonInfo[i].Clear();
		m_strSetItemInfo[i].Clear();
	}
	
	m_eCharType = CHAR_NAME_NONE;
	m_strCharName = "";
	m_bSetItem = FALSE;
	m_bWidthExtend = FALSE;
	Item_Belong = -1;

	for( i = 0; i < MAX_ITEM_SKILL; ++i )
	{
		Item_SkillIndex[i] = -1;
		Item_SkillLevel[i] = -1;
	}

	Item_SocketCount = 0;

	for( i = 0; i < MAX_SOCKET_OPTION; ++i )
	{
		Item_SocketJewelIndex[i] = -1;
	}
	// [sora] ������ ��ư ó��
	m_sbJob = -1; 
	m_slPosition = -1;
	m_slBarWidth = 0;
	m_bOnline = FALSE;
	m_lState_plus = 0;
	m_slLevel = 0;
	
	m_iSuitIndex = -1;
	m_iColor = 0xFFFFFFFF;

	// �Ӽ� �ý��� [1/22/2013 Ranma]
	m_nAtt = 0;
	m_nDef = 0;

	m_bAttribute = FALSE;

	// Fortune Info
	m_bHasFortuneInfo = FALSE;
	m_bSocketCreatedItem = FALSE;

	for(i = 0; i < MAX_SOCKET_OPTION; i++)
	{
		m_nSocketInfoShowLine[i] = 0;
	}
	m_bShowStack		= true;

	m_bWearTab = false;
	// ������

	m_nDurNow = 0;
	m_nDurMax = 0;
	// toggle ani state
	m_bToggleState = false;
}	

void CUIButtonEx::Destroy()
{
	CUIWindow::Destroy();

	STOCK_RELEASE(m_ptdAddTexture);
	STOCK_RELEASE(m_pExpeditionTexture);
	STOCK_RELEASE(m_ptdAttrTexture);
	STOCK_RELEASE(m_ptdSocketTexture);
	STOCK_RELEASE(m_ptdJewelGradeTexture);
	SAFE_DELETE(m_pImageFont);
#ifdef DURABILITY
	SAFE_DELETE(m_imgDurabilityZero);
#endif	//	DURABILITY
	SAFE_DELETE(m_paniToggle);
}

// ----------------------------------------------------------------------------
// Name : Copy()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::Copy( CUIButtonEx &btnSrc )
{
	// Item button
	if( btnSrc.GetBtnType() == UBET_ITEM )
		CopyItemInfo( btnSrc );
	// Skill button
	else if( btnSrc.GetBtnType() == UBET_SKILL )
		CopySkillInfo( btnSrc );
	// Action button
	else if( btnSrc.GetBtnType() == UBET_ACTION )
		CopyActionInfo( btnSrc );
	else if( btnSrc.GetBtnType() == UBET_COMBO)
		CopyComboInfo( btnSrc );
	else if(btnSrc.GetBtnType() == UBET_EXPEDITION)	// [sora] ������ ��ư ó��
		CopyExpeditionInfo( btnSrc );
	else
		InitBtn();
}

// ----------------------------------------------------------------------------
// Name : Swap()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::Swap( CUIButtonEx &btnSrc )
{
	// Item button
	if( btnSrc.GetBtnType() == UBET_ITEM )
		SwapItemInfo( btnSrc );
}

void CUIButtonEx::SetBaseInfo( UIBtnExType type, SBYTE cTexID, int texRow, int texCol )
{
	m_nTextureID = cTexID;
	m_bEmpty = FALSE;

	{
		int nUVSX = BTN_SIZE;
		int nUVSY = BTN_SIZE;

		nUVSX *= texCol;
		nUVSY *= texRow;

		FLOAT	fTexWidth = _pUIBtnTexMgr->GetTexWidth( type, cTexID );
		FLOAT	fTexHeight = _pUIBtnTexMgr->GetTexHeight( type, cTexID );

		SetUV( nUVSX, nUVSY, nUVSX + BTN_SIZE, nUVSY + BTN_SIZE, fTexWidth, fTexHeight );
	}
}
// ----------------------------------------------------------------------------
// Name : SetItemInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::SetItemInfo( SBYTE nTab, LONG inven_idx, int nIndex, int nUniIndex, SBYTE nWearingType, 
							  int nCashIndex , int nCashType , CTString nName, CTString nDesc, int nListCount ,int nTypeIndex)
{
	int			nOldIndex = m_nIndex;
	UIBtnExType	betOldType = m_betType;

	// Set item information
	m_nIndex	= nIndex;
	m_nUniIndex = nUniIndex;

	m_nCashIndex = nCashIndex;
	m_nCashType = nCashType;
	m_nCashName = nName;
	m_nCashDesc = nDesc;
	m_nCashListCount = nListCount;
	m_nCashTypeIndex = nTypeIndex;

	m_nWearType = nWearingType;
	m_nTab		= nTab;
	m_InvenIndex = inven_idx;
	m_bEmpty	= FALSE;
	m_betType	= UBET_ITEM;

	// Texture data is already set
	if( nOldIndex == nIndex && betOldType == UBET_ITEM && m_nCashIndex == -1)
		return;
	
	int nUVSX = BTN_SIZE;
	int nUVSY = BTN_SIZE;

	if(m_nCashIndex > 0){
		if( nTab !=-1 && inven_idx != -1 ){
			m_nTextureID = nTab;
// 			nUVSX *= (inven_idx);
// 			nUVSY *= (inven_idx);
		} else {
			int tv_index = _pNetwork->GetCashShopData().GetCashShopData(m_nCashIndex)->m_vItemDataArray[0].m_itemIndex;
			// Set texture data
			CItemData*	pItemData = _pNetwork->GetItemData( tv_index );
			m_nTextureID = pItemData->GetIconTexID();
			int	nTexRow = pItemData->GetIconTexRow();
			int	nTexCol = pItemData->GetIconTexCol();
			nUVSX *= nTexCol;
			nUVSY *= nTexRow;
		}
			
	}
	else {
		int nTexRow, nTexCol;
		
		if ( nIndex == NAS_INDEX )
		{
			m_nTextureID	= NAS_TEX_ID;
			nTexRow			= NAS_TEX_ROW;
			nTexCol			= NAS_TEX_COL;
		}
		else
		{
		// Set texture data
			CItemData*	pItemData = _pNetwork->GetItemData( nIndex );
			m_nTextureID = pItemData->GetIconTexID();
			nTexRow = pItemData->GetIconTexRow();
			nTexCol = pItemData->GetIconTexCol();

			if(!(pItemData->GetFlag()&ITEM_FLAG_QUEST) && pItemData->GetSetItemIndex() > 0)
			{
				m_bSetItem = TRUE;
			}
			else
			{
				m_bSetItem = FALSE;
			}
		}
		nUVSX *= nTexCol;
		nUVSY *= nTexRow;
	}

	FLOAT	fTexWidth = _pUIBtnTexMgr->GetTexWidth( UBET_ITEM, m_nTextureID );
	FLOAT	fTexHeight = _pUIBtnTexMgr->GetTexHeight( UBET_ITEM, m_nTextureID );
	m_rtUV.SetUV( nUVSX, nUVSY, nUVSX + BTN_SIZE, nUVSY + BTN_SIZE, fTexWidth, fTexHeight );

	m_bSkillDelay = CUIManager::getSingleton()->GetInventory()->GetSkillDelay( nIndex );

	m_bAttribute = FALSE;
}

// ----------------------------------------------------------------------------
// Name : CopyItemInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::CopyItemInfo( CUIButtonEx &btnSrc )
{
	int		i;
	m_nIndex = btnSrc.GetItemIndex();
	m_nUniIndex = btnSrc.GetItemUniIndex();
	
	m_nCashIndex = btnSrc.GetCashIndex();
	m_nCashType = btnSrc.GetCashType();
	m_nCashName = btnSrc.GetCashName();
	m_nCashDesc = btnSrc.GetCashDesc();
	m_nCashListCount = btnSrc.GetCashListCount();
	m_nCashTypeIndex = btnSrc.GetCashTypeIndex();

	m_nWearType = btnSrc.GetItemWearType();
	m_llCount = btnSrc.GetItemCount();
	m_llPrice = btnSrc.GetItemPrice();
	m_ulFlag = btnSrc.GetItemFlag();
	SetItemPlus(btnSrc.GetItemPlus());	// for m_bHasFortuneInfo
	m_ulUsed = btnSrc.GetItemUsed();
	m_nTab = btnSrc.GetItemTab();
	m_InvenIndex = btnSrc.GetInvenIndex();

	m_uwBtnID = btnSrc.GetBtnID();
	m_nTextureID = btnSrc.GetTextureID();
	m_nWhichUI = btnSrc.GetWhichUI();
	m_betType = btnSrc.GetBtnType();
	m_bEmpty = btnSrc.IsEmpty();	
	m_rtUV = btnSrc.GetUV();
	m_bSkillDelay = btnSrc.GetSkillDelay();
	
	m_dwWndState = btnSrc.GetWndState();

	m_uwRareIndex =btnSrc.GetItemRareIndex();
	//for���� ������..(20090206.. Gee~~~)
	for( i = 0; i < MAX_OPTION_INC_ORIGIN; ++i )
	{
		m_sbOptionType[i] = btnSrc.GetItemOptionType(i);
		m_lOptionLevel[i] = btnSrc.GetItemOptionLevel(i);
		m_lOriginOptionVar[i] = btnSrc.GetItemOriginOptionVar(i);
	}

	m_eCharType = btnSrc.GetCharType();
	m_strCharName = btnSrc.GetCharName();
	m_bSetItem = btnSrc.GetSetItemChack();
	Item_Belong = btnSrc.GetItemBelong();

	for( i = 0; i < MAX_ITEM_SKILL; i++)
	{
		Item_SkillIndex[i] = btnSrc.GetItemSkillIndex(i);
		Item_SkillLevel[i] = btnSrc.GetItemSkillLevel(i);
	}

	Item_SocketCount = btnSrc.GetItemSocketCount();

	for( i = 0; i < MAX_SOCKET_OPTION; ++i)
	{
		this->SetItemSocket( i, btnSrc.GetItemSocketJewelIndex(i) );
	}
	m_lState_plus = btnSrc.GetItemPlus2();
	m_ulUsed2 = btnSrc.GetItemUsed2();
	m_iSuitIndex = btnSrc.GetSuitIndex();
	m_iColor = btnSrc.GetItemColor();
	m_bShowStack = btnSrc.GetStack();
	m_bWearTab = btnSrc.IsWearTab();

	m_nDurNow = btnSrc.GetItemDurNow();
	m_nDurMax = btnSrc.GetItemDurMax();

	m_bAttribute = FALSE;
	m_bToggleState = btnSrc.IsToggleState();
}

// ----------------------------------------------------------------------------
// Name : SwapItemInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::SwapItemInfo( CUIButtonEx &btnSrc )
{
	int	nTab0 = m_nTab;
	int	inven_idx0 = m_InvenIndex;

	int	nTab1 = btnSrc.GetItemTab();
	int	inven_idx1 = btnSrc.GetInvenIndex();

	CUIButtonEx	btnTemp;
	btnTemp.CopyItemInfo( *this );
	CopyItemInfo( btnSrc );
	btnSrc.CopyItemInfo( btnTemp );

	SetItemLocation( nTab0, inven_idx0 );
	btnSrc.SetItemLocation( nTab1, inven_idx1 );
}

// ----------------------------------------------------------------------------
// Name : SetSkillInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::SetSkillInfo( int nIndex, SBYTE sbSkillLevel, BOOL bSpecial )
{
	int			nOldIndex = m_nIndex;
	UIBtnExType	betOldType = m_betType;

	// Set skill information
	m_nIndex = nIndex;
	m_nSkillLevel = sbSkillLevel;
	m_bEmpty = FALSE;
	m_betType = UBET_SKILL;
	m_bSpecial	= bSpecial;			// Dongmin

	// Texture data is already set

	if( nOldIndex == nIndex && betOldType == UBET_SKILL )
		return;

	FLOAT	fTexWidth;
	FLOAT	fTexHeight;
	int		nTexRow = -1;
	int		nTexCol = -1;

	if(!bSpecial)
	{
		// Set texture data
		CSkill	&rSkillData = _pNetwork->GetSkillData( nIndex );
		if (GetSkillBlend() == true)
			m_nTextureID = rSkillData.GetIconTexID() + 3;
		else
			m_nTextureID = rSkillData.GetIconTexID();

		fTexWidth = _pUIBtnTexMgr->GetTexWidth( UBET_SKILL, m_nTextureID );
		fTexHeight = _pUIBtnTexMgr->GetTexHeight( UBET_SKILL, m_nTextureID );
		
		nTexRow = rSkillData.GetIconTexRow();
		nTexCol = rSkillData.GetIconTexCol();

		int nSkillLevelIndex = 0;
		// �Ӽ� �ý��� [1/22/2013 Ranma]
		if (m_nSkillLevel > 0)
			nSkillLevelIndex = m_nSkillLevel - 1;
	
		// �Ӽ� �ý��� [1/22/2013 Ranma]
		m_nAtt = int(rSkillData.GetAttrAtt(nSkillLevelIndex));
		m_nDef = int(rSkillData.GetAttrDef(nSkillLevelIndex));

		if (m_nDef > 0 || m_nAtt > 0)
			m_bAttribute = TRUE;
		else
			m_bAttribute = FALSE;

		DOUBLE dStartTime;
		DOUBLE dCoolTime;
		DOUBLE dReUseTime = GetReuseTime();
		dStartTime = _pNetwork->GetSkillData( m_nIndex ).Skill_Data.Skill_StartTime;
		dCoolTime = GetCoolTime(dReUseTime, dStartTime);

		if (dCoolTime > 0.0f)
			m_bSkillDelay = TRUE;
		else
			m_bSkillDelay = FALSE;

		m_bToggleState = rSkillData.GetToggle();
	}
	// Special Skill
	else
	{
		CSpecialSkill* pSSkillData = CSpecialSkill::getData( nIndex );

		if (pSSkillData == NULL)
			return;

		m_nTextureID = pSSkillData->GetIconTexID();
		fTexWidth = _pUIBtnTexMgr->GetTexWidth( UBET_SKILL, m_nTextureID );
		fTexHeight = _pUIBtnTexMgr->GetTexHeight( UBET_SKILL, m_nTextureID );
		
		nTexRow = pSSkillData->GetIconTexRow();
		nTexCol = pSSkillData->GetIconTexCol();
	}
	
	int	nUVSX = BTN_SIZE * nTexCol;
	int	nUVSY = BTN_SIZE * nTexRow;
	m_rtUV.SetUV( nUVSX, nUVSY, nUVSX + BTN_SIZE, nUVSY + BTN_SIZE, fTexWidth, fTexHeight );

	CUIManager* pUIManager = CUIManager::getSingleton();
}

// ----------------------------------------------------------------------------
// Name : CopySkillInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::CopySkillInfo( CUIButtonEx &btnSrc )
{
	m_nIndex = btnSrc.GetSkillIndex();
	m_nSkillLevel = btnSrc.GetSkillLevel();
	m_bSpecial	= btnSrc.GetSkillSpecial();

	m_uwBtnID = btnSrc.GetBtnID();
	m_nTextureID = btnSrc.GetTextureID();
	m_nWhichUI = btnSrc.GetWhichUI();
	m_betType = btnSrc.GetBtnType();
	m_bEmpty = btnSrc.IsEmpty();	
	m_rtUV = btnSrc.GetUV();
	m_bSkillDelay = btnSrc.GetSkillDelay();
	
	m_dwWndState = btnSrc.GetWndState();

	// �Ӽ� �ý��� [1/22/2013 Ranma]
	m_nAtt = btnSrc.GetAttrAtt();
	m_nDef = btnSrc.GetAttrDef();

	if (m_nDef > 0 || m_nAtt > 0)
		m_bAttribute = TRUE;
	else
		m_bAttribute = FALSE;
	

	m_bToggleState = btnSrc.IsToggleState();
}

// ----------------------------------------------------------------------------
//  Name 	: SetSkillAffinityInfo()
//  Desc 	: 
// ----------------------------------------------------------------------------
void CUIButtonEx::SetSkillAffinityInfo( int _nIndex )
{
	int			nOldIndex = m_nIndex;
	UIBtnExType	betOldType = m_betType;

	// Set action information
	m_nIndex = _nIndex;
	m_bEmpty = FALSE;
	m_betType = UBET_SKILL;

	// Texture data is already set
	if( nOldIndex == _nIndex && betOldType == UBET_SKILL )
		return;

	// Set texture data
	CAffinityData* pData = _pNetwork->GetAffinityData();
	
	m_nTextureID = pData->GetAffinityDataByIndex( _nIndex )->nIconTextureID;
	FLOAT	fTexWidth = _pUIBtnTexMgr->GetTexWidth( UBET_SKILL, m_nTextureID );
	FLOAT	fTexHeight = _pUIBtnTexMgr->GetTexHeight( UBET_SKILL, m_nTextureID );

	int	nUVSX = BTN_SIZE * pData->GetAffinityDataByIndex( _nIndex )->nIconTextureCol;
	int	nUVSY = BTN_SIZE * pData->GetAffinityDataByIndex( _nIndex )->nIconTextureRow;
	m_rtUV.SetUV( nUVSX, nUVSY, nUVSX + BTN_SIZE, nUVSY + BTN_SIZE, fTexWidth, fTexHeight );
}

// ----------------------------------------------------------------------------
// Name : SetActionInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::SetActionInfo( int nIndex )
{
	int			nOldIndex = m_nIndex;
	UIBtnExType	betOldType = m_betType;

	// Set action information
	m_nIndex = nIndex;
	m_bEmpty = FALSE;
	m_betType = UBET_ACTION;

	// Texture data is already set
	if( nOldIndex == nIndex && betOldType == UBET_ACTION )
		return;

	// Set texture data
	CAction* pActionData = CAction::getData(nIndex);

	if (pActionData == NULL)
		return;

	m_nTextureID = pActionData->GetTexID();
	FLOAT	fTexWidth = _pUIBtnTexMgr->GetTexWidth( UBET_ACTION, m_nTextureID );
	FLOAT	fTexHeight = _pUIBtnTexMgr->GetTexHeight( UBET_ACTION, m_nTextureID );

	int	nUVSX = BTN_SIZE * pActionData->GetTexCol();
	int	nUVSY = BTN_SIZE * pActionData->GetTexRow();
	m_rtUV.SetUV( nUVSX, nUVSY, nUVSX + BTN_SIZE, nUVSY + BTN_SIZE, fTexWidth, fTexHeight );

	m_bAttribute = FALSE;
}

// ----------------------------------------------------------------------------
// Name : CopyActionInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::CopyActionInfo( CUIButtonEx &btnSrc )
{
	m_nIndex = btnSrc.GetActionIndex();

	m_uwBtnID = btnSrc.GetBtnID();
	m_nTextureID = btnSrc.GetTextureID();
	m_nWhichUI = btnSrc.GetWhichUI();
	m_betType = btnSrc.GetBtnType();
	m_bEmpty = btnSrc.IsEmpty();	
	m_rtUV = btnSrc.GetUV();
	
	m_dwWndState = btnSrc.GetWndState();
	m_bAttribute = FALSE;
}

// ----------------------------------------------------------------------------
// Name : SetExpeditionInfo()
// Desc : [sora]
// ----------------------------------------------------------------------------
void CUIButtonEx::SetExpeditionInfo(SBYTE sbJob, SLONG slPosition, CTString strText , SLONG slBarWidth, SLONG slLevel)
{
	m_bEmpty = FALSE;
	m_sbJob = sbJob;
	m_slPosition = slPosition;
	m_slLevel = slLevel;
	m_bOnline = TRUE;
	m_betType = UBET_EXPEDITION;

	m_strCharName = strText;

	FLOAT	fTexWidth = m_pExpeditionTexture->GetPixWidth();
	FLOAT	fTexHeight = m_pExpeditionTexture->GetPixHeight();

	m_rtUV.SetUV(341, 373, 489, 388, fTexWidth,fTexHeight);

	int nU = siExpeditionStartUV[sbJob][0];
	int nV = siExpeditionStartUV[sbJob][1];
	m_rtHPUV.SetUV(nU, nV, nU + 11, nV + 8, fTexWidth,fTexHeight);
	
	m_rtPositionUV[0].SetUV(405, 166, 418, 179, fTexWidth, fTexHeight);
	m_rtPositionUV[1].SetUV(388, 166, 401, 179, fTexWidth, fTexHeight);
	
	m_slBarWidth = slBarWidth;
	
	m_bAttribute = FALSE;
}

// ----------------------------------------------------------------------------
// Name : CopyExpeditionInfo()
// Desc : [sora]
// ----------------------------------------------------------------------------
void CUIButtonEx::CopyExpeditionInfo(CUIButtonEx &btnSrc)
{
	m_uwBtnID = btnSrc.GetBtnID();
	m_nWhichUI = btnSrc.GetWhichUI();
	m_betType = btnSrc.GetBtnType();
	m_bEmpty = btnSrc.IsEmpty();	
	m_rtUV = btnSrc.GetUV();

	m_eCharType = btnSrc.GetCharType();
	m_strCharName = btnSrc.GetCharName();
	m_sbJob = btnSrc.GetCharJob(); 
	m_slPosition = btnSrc.GetCharPosition();	
	m_rtHPUV = btnSrc.GetHPUV();

	m_slLevel = btnSrc.GetCharLevel();
		
	m_dwWndState = btnSrc.GetWndState();

	m_slBarWidth = btnSrc.GetBarWidth();

	m_bOnline = btnSrc.GetOnline();
	m_bAttribute = FALSE;
}

// ----------------------------------------------------------------------------
// Name : SetQuestInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::SetQuestInfo( int nIndex, SBYTE sbType, SBYTE sbQuestFlag )
{
	int			nOldIndex = m_nIndex;
	UIBtnExType	betOldType = m_betType;

	// Set quest information
	m_nIndex = nIndex;
	m_nQuestType = sbType;
	m_sbQuestFlag = sbQuestFlag;
	m_bEmpty = FALSE;
	m_betType = UBET_QUEST;

	// Texture data is already set
	if( nOldIndex == nIndex && betOldType == UBET_QUEST )
		return;

	// Set texture data
	m_nTextureID = 0;
	FLOAT	fTexWidth = _pUIBtnTexMgr->GetTexWidth( UBET_QUEST, m_nTextureID );
	FLOAT	fTexHeight = _pUIBtnTexMgr->GetTexHeight( UBET_QUEST, m_nTextureID );

	int	nTexRow = ( nIndex - 1 ) / 4;
	int	nTexCol = ( nIndex - 1 ) % 4;

	if( nIndex == 1000 ) // ���� ���������� ����ϴ� Quest��ư : ���� �ϵ�...
	{
		nTexRow = 0;
		nTexCol = 4;
	}
	// �� ���� ����Ʈ...
	else if( nIndex == 4000 || nIndex == 4003 || nIndex == 4005)
	{
		nTexRow = 1;
		nTexCol = 1;
	}
	// �� ���� ����Ʈ...
	else if( nIndex == 4001 || nIndex == 4004 || nIndex == 4006)
	{
		nTexRow = 1;
		nTexCol = 1;
	}
	// �̺�Ʈ ��ư�� �̹���.
	else if( nIndex >= EVENT_START_INDEX )
	{
		nTexRow = 1;
		nTexCol = 4;
	}

	int	nUVSX = BTN_SIZE * nTexCol;
	int	nUVSY = BTN_SIZE * nTexRow;
	m_rtUV.SetUV( nUVSX, nUVSY, nUVSX + BTN_SIZE, nUVSY + BTN_SIZE, fTexWidth, fTexHeight );

	m_bAttribute = FALSE;
}

// ----------------------------------------------------------------------------
// Name : SetEventInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::SetEventInfo( int nIndex )
{
	int			nOldIndex = m_nIndex;
	UIBtnExType	betOldType = m_betType;

	// Set event information
	m_nIndex = nIndex;
	m_bEmpty = FALSE;
	m_betType = UBET_EVENT;

	// Texture data is already set
	if( nOldIndex == nIndex && betOldType == UBET_EVENT )
		return;

	// Set texture data
	m_nTextureID = 0;
	FLOAT	fTexWidth = _pUIBtnTexMgr->GetTexWidth( UBET_EVENT, m_nTextureID );
	FLOAT	fTexHeight = _pUIBtnTexMgr->GetTexHeight( UBET_EVENT, m_nTextureID );

	int	nTexRow = ( nIndex - 1 ) / 4;
	int	nTexCol = ( nIndex - 1 ) % 4;
	int	nUVSX = BTN_SIZE * nTexCol;
	int	nUVSY = BTN_SIZE * nTexRow;
	m_rtUV.SetUV( nUVSX, nUVSY, nUVSX + BTN_SIZE, nUVSY + BTN_SIZE, fTexWidth, fTexHeight );

	m_bAttribute = FALSE;
}

// ----------------------------------------------------------------------------
// Name : SetRemissionInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::SetRemissionInfo( SBYTE iRemissionType, SWORD nTab, SWORD inven_idx, int nIndex, int nUniIndex, SBYTE nWearingType )
{
	//int			nOldIndex = m_nIndex;
	UIBtnExType	betOldType = m_betType;
	SBYTE		sbOldType = m_sbRemissionType;
	
	// Set remission information
	m_nIndex	= nIndex;
	m_nUniIndex = nUniIndex;
	m_nWearType = nWearingType;
	m_nTab		= nTab;
	m_InvenIndex = inven_idx;
	m_bEmpty	= FALSE;
	m_betType	= UBET_REMISSION;
	m_sbRemissionType = iRemissionType;
	
	// Texture data is already set
	if( sbOldType == iRemissionType && betOldType == UBET_REMISSION )
		return;
	
	// Set texture data
	m_nTextureID = 0;
	FLOAT	fTexWidth = _pUIBtnTexMgr->GetTexWidth( UBET_REMISSION, m_nTextureID );
	FLOAT	fTexHeight = _pUIBtnTexMgr->GetTexHeight( UBET_REMISSION, m_nTextureID );
	
	int	nTexRow = ( iRemissionType - 1 ) / 4;
	int	nTexCol = ( iRemissionType - 1 ) % 4;
	int	nUVSX = BTN_SIZE * nTexCol;
	int	nUVSY = BTN_SIZE * nTexRow;
	m_rtUV.SetUV( nUVSX, nUVSY, nUVSX + BTN_SIZE, nUVSY + BTN_SIZE, fTexWidth, fTexHeight );

	m_bAttribute = FALSE;
}

// ----------------------------------------------------------------------------
// Name : SetComboInfo()
// Desc : �̼� ���̽� ��ư �̹���
// ----------------------------------------------------------------------------
void CUIButtonEx::SetComboInfo( SBYTE nTab , SBYTE nRow , SBYTE nCol )
{
	int nUVSX = COMBO_BTN_SIZE-2;
	int nUVSY = COMBO_BTN_SIZE-2;

	m_nTextureID = nTab;
	int	nTexRow = nRow;
	int	nTexCol = nCol;
	m_bEmpty	= FALSE;
	m_betType	= UBET_COMBO;

	nUVSX *= nTexCol;
	nUVSY *= nTexRow;

	FLOAT	fTexWidth = _pUIBtnTexMgr->GetTexWidth( UBET_COMBO, m_nTextureID );
	FLOAT	fTexHeight = _pUIBtnTexMgr->GetTexHeight( UBET_COMBO, m_nTextureID );
	m_rtUV.SetUV( nUVSX, nUVSY, nUVSX + COMBO_BTN_SIZE-2, nUVSY + COMBO_BTN_SIZE-2, fTexWidth, fTexHeight );

	m_bAttribute = FALSE;
}

void CUIButtonEx::CopyComboInfo(CUIButtonEx &btnSrc)
{
	m_nIndex = btnSrc.GetItemIndex();
		
	m_nTab = btnSrc.GetItemTab();
	m_InvenIndex = btnSrc.GetInvenIndex();

	m_uwBtnID = btnSrc.GetBtnID();
	m_nTextureID = btnSrc.GetTextureID();
	m_nWhichUI = btnSrc.GetWhichUI();
	m_betType = btnSrc.GetBtnType();
	m_bEmpty = btnSrc.IsEmpty();	
	m_rtUV = btnSrc.GetUV();
		
	m_dwWndState = btnSrc.GetWndState();
	m_bAttribute = FALSE;
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::Render()
{
	// Get position
	int	nX, nY;
	GetAbsPos( nX, nY );

	CUIManager* pUIManager = CUIManager::getSingleton();
	CDrawPort* pDrawPort = pUIManager->GetDrawPort();

	if( m_betType == UBET_ITEM  && m_nCashIndex == -1)
	{
		if( !HasReuseTimeItem() )
		{
			RenderDefaultButton();
			RenderStack(nX, nY, pDrawPort);
			RenderDurZero(nX, nY, pDrawPort);
			RenderToggleAni(nX, nY, pDrawPort);
			return;
		}
	}
	else if(m_betType == UBET_EXPEDITION) // [sora] ������ ��ư ó��
	{
		pDrawPort->InitTextureData(m_pExpeditionTexture);

		pDrawPort->AddTexture(nX, nY, nX + m_nWidth, nY + m_nHeight, m_rtUV.U0, m_rtUV.V0,
								   m_rtUV.U1, m_rtUV.V1, 0xFFFFFFFF);

		COLOR strColor = 0xFFFFFFFF;
		int nWidth = m_slBarWidth;
		if(!m_bOnline) // ���������� ���
		{
			strColor = 0x777777FF;
			nWidth = 1;
		}

		pDrawPort->AddTexture(nX + 15, nY + 3, nX + nWidth + 15, nY + 11, m_rtHPUV.U0, m_rtHPUV.V0,
										   m_rtHPUV.U1, m_rtHPUV.V1, strColor);

		if(m_slPosition >= 0 && m_slPosition < MSG_EXPED_MEMBERTYPE_NORMAL)
		{
			// ��å ǥ��
			pDrawPort->AddTexture(nX + 1, nY + 1, nX + 14, nY + 14, m_rtPositionUV[m_slPosition].U0, m_rtPositionUV[m_slPosition].V0,
											   m_rtPositionUV[m_slPosition].U1, m_rtPositionUV[m_slPosition].V1, 0xFFFFFFFF);
		}

		pDrawPort->FlushRenderingQueue();

		if(m_strCharName != "")
		{
			CTString strTemp;
			if(m_bOnline)
			{
				strTemp.PrintF("(%d)", m_slLevel);
				strColor = pUIManager->GetParty()->GetJobStringColor(m_sbJob);
			}
			else
			{
				strTemp.PrintF("(off)");
				strColor = 0x777777FF;
			}

			pDrawPort->PutTextExCX(m_strCharName + strTemp, nX+(m_nWidth/2), nY + 1, strColor);

			pDrawPort->EndTextEx();
		}

		return;
	}
// 	else if( m_betType == UBET_GUILD_MARK )	// [sora] GUILD_MARK
// 	{
// 		pUIManager->GetGuildMark()->RenderGuildMark( nX, nY, BTN_SIZE, m_guildMark );
// 		return;
// 	}

	// If button is skill and is delay state
	if( m_bSkillDelay && ( !m_bSpecial || m_betType == UBET_ITEM ) )
	{
		DOUBLE dStartTime;
		DOUBLE dCoolTime;
		DOUBLE dReUseTime = GetReuseTime();

		if(m_betType == UBET_SKILL)
		{
			dStartTime = _pNetwork->GetSkillData( m_nIndex ).Skill_Data.Skill_StartTime;
		}
		else if( m_betType == UBET_ITEM )
		{
			dStartTime =  _pNetwork->GetItemData( m_nIndex )->StartTime;
		}

		dCoolTime = GetCoolTime(dReUseTime, dStartTime);

		if(  dCoolTime < 0.5 )
		{
			float fDelta;
			
			fDelta = dCoolTime * 10;

			if( fDelta < 0 || fDelta > 5 ) 
			{
				fDelta = 0;
			}
			// Add render regions
			pDrawPort->AddBtnTexture( m_nTextureID, nX - fDelta, nY - fDelta, nX + m_nWidth + fDelta *2, nY + m_nHeight + fDelta * 2,
													m_rtUV.U0, m_rtUV.V0, m_rtUV.U1, m_rtUV.V1,
													0xFFFFFFFF );
			// Render all button elements
			pDrawPort->FlushBtnRenderingQueue( m_betType, PBT_BLEND );

			// Add render regions
			pDrawPort->AddBtnTexture( m_nTextureID, nX - fDelta, nY - fDelta, nX + m_nWidth + fDelta *2, nY + m_nHeight + fDelta * 2,
													m_rtUV.U0, m_rtUV.V0, m_rtUV.U1, m_rtUV.V1,
													0x808080FF );

			// Render all button elements
			pDrawPort->FlushBtnRenderingQueue( m_betType, PBT_ADD );

			// �Ӽ� �ý��� ��ư���� ���׸İ� �Ӽ� �׸��� [1/22/2013 Ranma]
			if (m_bAttribute)
			{
				pDrawPort->InitTextureData( m_ptdAttrTexture );
				
				// ���� �Ӽ� ������
				if (m_nAtt > 0)
				{
					pDrawPort->AddTexture(nX + 16, nY + 16, nX + 32, nY + 32,
						m_rtAttributeIconAtt[m_nAtt].U0, m_rtAttributeIconAtt[m_nAtt].V0,
						m_rtAttributeIconAtt[m_nAtt].U1, m_rtAttributeIconAtt[m_nAtt].V1, 0xFFFFFFFF);
				}
				// ��� �Ӽ� ������
				if (m_nDef > 0)
				{
					pDrawPort->AddTexture(nX + 16, nY + 16, nX + 32, nY + 32,
						m_rtAttributeIconDef[m_nDef].U0, m_rtAttributeIconDef[m_nDef].V0,
						m_rtAttributeIconDef[m_nDef].U1, m_rtAttributeIconDef[m_nDef].V1, 0xFFFFFFFF);
				}
				
				pDrawPort->FlushRenderingQueue();
			}
			// Reset
			if( dCoolTime == 0.0f )
				m_bSkillDelay = FALSE;
		}
		else
		{
			// Add render regions
			// [091009 sora] ��Ÿ������ ��ư �÷� ����
			pDrawPort->AddBtnTexture( m_nTextureID, nX, nY, nX + m_nWidth, nY + m_nHeight,
													m_rtUV.U0, m_rtUV.V0, m_rtUV.U1, m_rtUV.V1,
													0x404040FF );
			// Render all button elements
			pDrawPort->FlushBtnRenderingQueue( m_betType, PBT_BLEND );

			// Delay animation
			FLOAT	fDelayRatio = dCoolTime / dReUseTime;
			FLOAT	fSizeOffset = FLOAT(BTN_SIZE / 2) * fDelayRatio;
			FLOAT	fUOffset = ( m_rtUV.U1 - m_rtUV.U0 ) * 0.5f * fDelayRatio;
			FLOAT	fVOffset = ( m_rtUV.V1 - m_rtUV.V0 ) * 0.5f * fDelayRatio;
			FLOAT	fX0 = FLOAT(nX) + fSizeOffset;
			FLOAT	fY0 = FLOAT(nY) + fSizeOffset;
			FLOAT	fX1 = FLOAT(nX + m_nWidth) - fSizeOffset;
			FLOAT	fY1 = FLOAT(nY + m_nHeight) - fSizeOffset;

			// Add render regions
			pDrawPort->AddBtnTexture( m_nTextureID, fX0, fY0, fX1, fY1,
													m_rtUV.U0 + fUOffset, m_rtUV.V0 + fVOffset,
													m_rtUV.U1 - fUOffset, m_rtUV.V1 - fVOffset,
													0xDFCFCFFF );
			// Render all button elements
			pDrawPort->FlushBtnRenderingQueue( m_betType, PBT_ADD );

			// �Ӽ� �ý��� ��ư���� ���׸İ� �Ӽ� �׸��� [1/22/2013 Ranma]
			if (m_bAttribute)
			{
				pDrawPort->InitTextureData( m_ptdAttrTexture );
				
				// ���� �Ӽ� ������
				if (m_nAtt > 0)
				{
					pDrawPort->AddTexture(nX + 16, nY + 16, nX + 32, nY + 32,
						m_rtAttributeIconAtt[m_nAtt].U0, m_rtAttributeIconAtt[m_nAtt].V0,
						m_rtAttributeIconAtt[m_nAtt].U1, m_rtAttributeIconAtt[m_nAtt].V1, 0xFFFFFFFF);
				}
				// ��� �Ӽ� ������
				if (m_nDef > 0)
				{
					pDrawPort->AddTexture(nX + 16, nY + 16, nX + 32, nY + 32,
						m_rtAttributeIconDef[m_nDef].U0, m_rtAttributeIconDef[m_nDef].V0,
						m_rtAttributeIconDef[m_nDef].U1, m_rtAttributeIconDef[m_nDef].V1, 0xFFFFFFFF);
				}
				
				pDrawPort->FlushRenderingQueue();
			}
		
		}

		RenderStack(nX, nY, pDrawPort);
		RenderDurZero(nX, nY, pDrawPort);
		RenderToggleAni(nX, nY, pDrawPort);
	}
	else
	{
		RenderDefaultButton();
		RenderStack(nX, nY, pDrawPort);
		RenderDurZero(nX, nY, pDrawPort);
		RenderToggleAni(nX, nY, pDrawPort);
		return;
	}
}

//------------------------------------------------------------------------------
// CUIButtonEx::RenderDefaultButton
// Explain:  
// Date : 2005-10-11,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUIButtonEx::RenderDefaultButton()
{
	int	nX, nY;
	GetAbsPos( nX, nY );	

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Add render regions
	pDrawPort->AddBtnTexture( m_nTextureID,
											nX, nY, nX + m_nWidth, nY + m_nHeight,//old
											m_rtUV.U0, m_rtUV.V0, m_rtUV.U1, m_rtUV.V1,//old
											m_iColor );

	// Render all button elements
	pDrawPort->FlushBtnRenderingQueue( m_betType, PBT_BLEND );
	
	if( m_bsState == UBES_CLICK )
	{
	
		
		// Add render regions
		pDrawPort->AddBtnTexture( m_nTextureID,
												nX+1, nY+1, nX + m_nWidth-1, nY + m_nHeight-1,//old
												m_rtUV.U0, m_rtUV.V0, m_rtUV.U1, m_rtUV.V1,//old
												0x969696FF );

		// Render all button elements
		pDrawPort->FlushBtnRenderingQueue( m_betType, PBT_ADD );
	}

	

	if (m_nIndex >= 0)
	{
		CItemData*	pItemData = _pNetwork->GetItemData( m_nIndex );

		if (pItemData != NULL)
		{
			// �÷��� ��ġ ǥ��
			// [2010/10/20 : Sora] ���� �뺴 ī������
			if(m_ulPlus > 0 && 
				( (pItemData->GetType() == CItemData::ITEM_ETC && pItemData->GetSubType() != CItemData::ITEM_ETC_MONSTER_MERCENARY_CARD && pItemData->GetSubType() != 10)
				|| (pItemData->GetType() == CItemData::ITEM_ONCEUSE && pItemData->GetSubType() != CItemData::ITEM_ETC_EVENT &&
				pItemData->GetSubType() != CItemData::ITEM_SUB_BOX && pItemData->GetSubType() != CItemData::ITEM_SUB_ETC) ) )
			{ // ������ ī��� ���� ���� �߰�, ��ȸ�� ���� ����
				pDrawPort->FlushBtnRenderingQueue( m_betType, PBT_BLEND );

				CTString tv_plus;
				tv_plus.PrintF("+%d", m_ulPlus);

				pDrawPort->PutTextEx( 
					tv_plus, 
					nX+17,
					nY+17, 
					0xFF0000FF );

				// Flush all render text queue
				pDrawPort->EndTextEx();
			}
			if ( pItemData->GetType() == CItemData::ITEM_ETC && pItemData->GetSubType() == CItemData::ITEM_ETC_JEWEL || pItemData->GetSubType() == CItemData::ITEM_ETC_CHAOSJEWEL)
			{
				pDrawPort->InitTextureData(m_ptdJewelGradeTexture);

				int nGrade = pItemData->GetNum0() - 1; 

				pDrawPort->AddTexture(nX, nY, nX + JEWEL_GRADE_ICON_SIZE, nY + JEWEL_GRADE_ICON_SIZE,
					m_rtGradeIcon[nGrade].U0, m_rtGradeIcon[nGrade].V0,
					m_rtGradeIcon[nGrade].U1, m_rtGradeIcon[nGrade].V1, 0xFFFFFFFF);

				pDrawPort->FlushRenderingQueue();
			}
		}		
	}
	// �Ӽ� �ý��� ��ư���� ���׸İ� �Ӽ� �׸��� [1/22/2013 Ranma]
	if (m_bAttribute)
	{
		pDrawPort->InitTextureData( m_ptdAttrTexture );
		
		// ���� �Ӽ� ������
		if (m_nAtt > 0)
		{
			pDrawPort->AddTexture(nX + 16, nY + 16, nX + 32, nY + 32,
				m_rtAttributeIconAtt[m_nAtt].U0, m_rtAttributeIconAtt[m_nAtt].V0,
				m_rtAttributeIconAtt[m_nAtt].U1, m_rtAttributeIconAtt[m_nAtt].V1, 0xFFFFFFFF);
		}
		// ��� �Ӽ� ������
		if (m_nDef > 0)
		{
			pDrawPort->AddTexture(nX + 16, nY + 16, nX + 32, nY + 32,
				m_rtAttributeIconDef[m_nDef].U0, m_rtAttributeIconDef[m_nDef].V0,
				m_rtAttributeIconDef[m_nDef].U1, m_rtAttributeIconDef[m_nDef].V1, 0xFFFFFFFF);
		}
		
		pDrawPort->FlushRenderingQueue();
	}
}

// ----------------------------------------------------------------------------
// Name : RenderHighlight()
// Desc :
// ----------------------------------------------------------------------------
void CUIButtonEx::RenderHighlight( const COLOR colHighlight, const ULONG ulPBT/* = PBT_ADD*/ )
{
	// Get position
	int	nX, nY;
	GetAbsPos( nX, nY );

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Add render regions
	pDrawPort->AddBtnTexture( m_nTextureID, nX, nY, nX + m_nWidth, nY + m_nHeight,
											m_rtUV.U0, m_rtUV.V0, m_rtUV.U1, m_rtUV.V1,
											colHighlight );

	// Render all button elements
	pDrawPort->FlushBtnRenderingQueue( m_betType, ulPBT );
}

// ----------------------------------------------------------------------------
// Name : MouseMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT CUIButtonEx::MouseMessage( MSG *pMsg )
{
	m_bShow = FALSE;

	// If button is disabled
	if( !IsEnabled() || IsEmpty() )
		return WMSG_FAIL;

	// Mouse point
	int	nX = LOWORD( pMsg->lParam );
	int	nY = HIWORD( pMsg->lParam );

	// Mouse message
	switch( pMsg->message )
	{
	case WM_MOUSEMOVE:
		{
			if( IsInside( nX, nY ) )
			{
				if( !( pMsg->wParam & MK_LBUTTON ) )
					m_bLButtonDown = FALSE;

				if( m_bLButtonDown )
					m_bsState = UBES_CLICK;
				else
					m_bsState = UBES_IDLE;

				m_bShow = TRUE;

				return WMSG_SUCCESS;
			}
			
			m_bsState = UBES_IDLE;
		}
		break;

	case WM_LBUTTONDOWN:
		{
			if( IsInside( nX, nY ) )
			{
				m_bsState = UBES_CLICK;
				m_bLButtonDown = TRUE;
				return WMSG_SUCCESS;
			}
		}
		break;

	case WM_LBUTTONUP:
		{
			m_bLButtonDown = FALSE;

			if( IsInside( nX, nY ) )
			{
				if( m_bsState == UBES_CLICK )
				{
					m_bsState = UBES_IDLE;
					if( !m_bSkillDelay )
						return WMSG_COMMAND;
				}
				else
				{
					m_bsState = UBES_IDLE;
					return WMSG_SUCCESS;
				}
			}
		}
		break;

	case WM_LBUTTONDBLCLK:
		{
			if( IsInside( nX, nY ) && !m_bSkillDelay )
			{
				m_bsState = UBES_IDLE;

				if (m_bToggleState == true && m_betType == UBET_ITEM)
				{
					if (m_nWhichUI == UI_QUICKSLOT || (m_nWhichUI >= UI_INVENTORY && m_nWhichUI <= UI_QUICKSLOT4))
					{
						return WMSG_COMMAND;
					}
					else
					{
						UIMGR()->GetChatting()->AddSysMessage(_S(7035, "Ȱ��ȭ �� �������� �ű� �� �����ϴ�."));
						return WMSG_FAIL;
					}
				}

				return WMSG_COMMAND;
			}
		}
		break;
	}

	return WMSG_FAIL;
}

extern INDEX g_iCountry;

void CUIButtonEx::AddInfoString( CTString &strInfo, COLOR colInfo, BOOL bSetIteminfo )
{
	if( m_nCurInfoLines >= MAX_ITEMINFO_LINE ||
		(bSetIteminfo && m_nCurSetItemInfoLines >= MAX_ITEMINFO_LINE))
		return;

	// Get length of string
	INDEX	nLength = strInfo.Length();
	if( nLength <= 0 )
		return;

	// wooss 051002
#if defined(G_THAI)
	{
		int		iPos;
		// Get length of string
		INDEX	nThaiLen = FindThaiLen(strInfo);
		INDEX	nChatMax= (DEF_MAXSTRINGCHAR-1)*(_pUIFontTexMgr->GetFontWidth()+_pUIFontTexMgr->GetFontSpacing());
		if( nLength == 0 )
			return;
		// If length of string is less than max char
		if( nThaiLen <= nChatMax )
		{
			if (bSetIteminfo)
			{
				m_strSetItemInfo[m_nCurSetItemInfoLines] = strInfo;
				m_colSetItemInfo[m_nCurSetItemInfoLines++] = colInfo;
			}else
			{
				m_strButtonInfo[m_nCurInfoLines] = strInfo;
				m_colButtonInfo[m_nCurInfoLines++] = colInfo;
			}
		}
		// Need multi-line
		else
		{
			// Check splitting position for 2 byte characters
			int		nSplitPos = DEF_MAXSTRINGCHAR;
			BOOL	b2ByteChar = FALSE;
			for( iPos = 0; iPos < nLength; iPos++ )
			{
				if(nChatMax < FindThaiLen(strInfo,0,iPos))
					break;
			}
			nSplitPos = iPos;

			// Split string
			CTString	strTemp;
			if (bSetIteminfo)
			{
				strInfo.Split( nSplitPos, m_strSetItemInfo[m_nCurSetItemInfoLines], strTemp );
				m_colSetItemInfo[m_nCurSetItemInfoLines++] = colInfo;
			}
			else 
			{
				strInfo.Split( nSplitPos, m_strButtonInfo[m_nCurInfoLines], strTemp );
				m_colButtonInfo[m_nCurInfoLines++] = colInfo;
			}
			

			// Trim space
			if( strTemp[0] == ' ' )
			{
				int	nTempLength = strTemp.Length();
				for( iPos = 1; iPos < nTempLength; iPos++ )
				{
					if( strTemp[iPos] != ' ' )
						break;
				}

				strTemp.TrimLeft( strTemp.Length() - iPos );
			}

			AddInfoString( strTemp, colInfo , bSetIteminfo);

		}
		
	} 
#else
	{
		#if defined(G_RUSSIA)
			{
				INDEX iStrSub = strInfo.FindSubstr("\n");
				if(iStrSub != -1)
				{
					CTString	strTemp, strTemp2;
					strTemp = strInfo;
					strTemp.str_String[iStrSub] = ' ';


					strTemp.Split( iStrSub+1, strTemp, strTemp2 );

					AddInfoString( strTemp, colInfo, bSetIteminfo );
					AddInfoString( strTemp2, colInfo, bSetIteminfo );
					return;
				}
			}
		#endif//#if defined(RUSSIA)

		// If length of string is less than max char
#if defined(G_RUSSIA)
		if( CUIManager::getSingleton()->GetDrawPort()->GetTextWidth( strInfo ) <= 200)
#else
		if( nLength <= DEF_MAXSTRINGCHAR )
#endif
		{
			if (bSetIteminfo)
			{
				m_strSetItemInfo[m_nCurSetItemInfoLines] = strInfo;
				m_colSetItemInfo[m_nCurSetItemInfoLines++] = colInfo;
			}
			else
			{
				m_strButtonInfo[m_nCurInfoLines] = strInfo;
				m_colButtonInfo[m_nCurInfoLines++] = colInfo;
#if defined(G_RUSSIA)
			m_bWidthExtend	= TRUE;
#endif
			}
		}
#if	defined(G_BRAZIL)
		else if( nLength <= DEF_MAXSTRINGCHAREXTEND 
				&& bSetIteminfo == FALSE )
		{
			m_strButtonInfo[m_nCurInfoLines] = strInfo;
			m_colButtonInfo[m_nCurInfoLines++] = colInfo;
			m_bWidthExtend	= TRUE;
		}
#endif
		// Need multi-line
		else
		{
			// Check splitting position for 2 byte characters
			int		nSplitPos = DEF_MAXSTRINGCHAR;
#if	defined(G_BRAZIL) | defined(G_RUSSIA) 
			if(bSetIteminfo == FALSE)
			{
				nSplitPos		= DEF_MAXSTRINGCHAREXTEND;
				m_bWidthExtend	= TRUE;
			}
#endif
#if defined(G_RUSSIA)
			nSplitPos = CUIManager::getSingleton()->GetDrawPort()->CheckShowCharLength( strInfo.str_String, 200 );

			for( int iPos=nSplitPos; iPos >=0; --iPos )
			{
				if( strInfo[iPos] == ' ' )
				{
					nSplitPos = iPos;
					break;
				}
			}
#else
			BOOL	b2ByteChar = FALSE;
			for( int iPos = 0; iPos < nSplitPos; iPos++ )
			{
				if( strInfo[iPos] & 0x80 )
					b2ByteChar = !b2ByteChar;
				else
					b2ByteChar = FALSE;
			}

			if( b2ByteChar )
				nSplitPos--;
#endif
			// Split string
			CTString	strTemp;
			if (bSetIteminfo)
			{
				strInfo.Split( nSplitPos, m_strSetItemInfo[m_nCurSetItemInfoLines], strTemp );
				m_colSetItemInfo[m_nCurSetItemInfoLines++] = colInfo;
			}
			else 
			{
				strInfo.Split( nSplitPos, m_strButtonInfo[m_nCurInfoLines], strTemp );
				m_colButtonInfo[m_nCurInfoLines++] = colInfo;
			}

			// Trim space
			if( strTemp[0] == ' ' )
			{
				int	nTempLength = strTemp.Length();
				int iPos;
				for( iPos = 1; iPos < nTempLength; iPos++ )
				{
					if( strTemp[iPos] != ' ' )
						break;
				}

				strTemp.TrimLeft( strTemp.Length() - iPos );
			}

			AddInfoString( strTemp, colInfo, bSetIteminfo);
		}
	}
#endif //#if defined(G_THAI)
}

CTString CUIButtonEx::GetOptionAciveSkillInfo(CItemData& rItem)
{
	CTString strTemp;
	LONG		lSkillIndex;
	LONG		lSkillProb;
	
	lSkillIndex = rItem.GetSocketOptionIndex();
	lSkillProb = rItem.GetSocketOptionLevel(); // ���� ��� �ߵ� Ȯ���� ��
	CSkill &SkillItem = _pNetwork->GetSkillData( lSkillIndex );

	strTemp.PrintF( "%s : %s %.2f%%", rItem.GetName(), SkillItem.GetName(), lSkillProb / 100.0f );
	return strTemp;
}

CTString CUIButtonEx::GetJewelOptionSkillInfo(CItemData& rItem)
{
	CTString strTemp;
	LONG		lSkillIndex;
	LONG		lSkillProb;
	
	lSkillIndex = rItem.GetSocketOptionIndex();
	lSkillProb = rItem.GetSocketOptionLevel(); // ���� ��� �ߵ� Ȯ���� ��
	CSkill &SkillItem = _pNetwork->GetSkillData( lSkillIndex );
	
	strTemp.PrintF( "%s : %.2f%%",  SkillItem.GetName(), lSkillProb / 100.0f );
	return strTemp;
}

CTString CUIButtonEx::GetJewelOptionInfo(CItemData& rItem)
{
	CTString strTemp;
	SBYTE		sbOptionType;
	LONG		lOptionLevel;
	
	sbOptionType = rItem.GetSocketOptionIndex();
	lOptionLevel = rItem.GetSocketOptionLevel();
	COptionData* podItem = COptionData::getData( sbOptionType );

	if (podItem == NULL)
		return CTString("");

	if (UtilHelp* pHelp = UtilHelp::getSingleton())
	{
		switch( pHelp->GetPaciveOptionType(sbOptionType) )
		{
		case STRING_TYPE_INTEGER:
			strTemp.PrintF( "%s : %d", podItem->GetName(), podItem->GetValue( lOptionLevel - 1 ) );
			break;
		case STRING_TYPE_NEGATIVE:
			strTemp.PrintF( "%s : -%d", podItem->GetName(), podItem->GetValue( lOptionLevel - 1 ) );
			break;
		case STRING_TYPE_PERCENT:
			strTemp.PrintF( "%s : %d%%", podItem->GetName(), podItem->GetValue( lOptionLevel - 1 ) );
			break;
		case STRING_TYPE_FLOAT_POINT_ONE:
			strTemp.PrintF("%s : %.1f", podItem->GetName(), podItem->GetValue(lOptionLevel - 1) / 10.0f);
			break;
		case STRING_TYPE_FLOAT_POINT_TWO:
			strTemp.PrintF("%s : %.2f", podItem->GetName(), podItem->GetValue(lOptionLevel - 1) / 100.0f);
			break;
		}
	}
	
	return strTemp;
}

CTString CUIButtonEx::GetOptionPaciveInfo(CItemData& rItem)
{
	CTString strTemp;
	SBYTE		sbOptionType;
	LONG		lOptionLevel;

	sbOptionType = rItem.GetSocketOptionIndex();
	lOptionLevel = rItem.GetSocketOptionLevel();
	COptionData* podItem = COptionData::getData( sbOptionType );

	if (podItem == NULL)
		return CTString("");

	if (UtilHelp* pHelp = UtilHelp::getSingleton())
	{
		switch( pHelp->GetPaciveOptionType(sbOptionType) )
		{
		case STRING_TYPE_INTEGER:
			strTemp.PrintF( "%s : %s %d", rItem.GetName(), podItem->GetName(), podItem->GetValue( lOptionLevel - 1 ) );
			break;
		case STRING_TYPE_NEGATIVE:
			strTemp.PrintF( "%s : %s -%d", rItem.GetName(), podItem->GetName(), podItem->GetValue( lOptionLevel - 1 ) );
			break;
		case STRING_TYPE_PERCENT:
			strTemp.PrintF( "%s : %s %d%%", rItem.GetName(), podItem->GetName(), podItem->GetValue( lOptionLevel - 1 ) );
			break;
		case STRING_TYPE_FLOAT_POINT_ONE:
			strTemp.PrintF("%s : %s %.1f", rItem.GetName(), podItem->GetName(), podItem->GetValue(lOptionLevel - 1) / 10.0f);
			break;
		case STRING_TYPE_FLOAT_POINT_TWO:
			strTemp.PrintF("%s : %s %.2f", rItem.GetName(), podItem->GetName(), podItem->GetValue(lOptionLevel - 1) / 100.0f);
			break;
		}
	}
	return strTemp;
}

tm* gt_tv_t = NULL; // �Ⱓ ǥ�ÿ� ���� ������ ����
void CUIButtonEx::GetButtonInfo(/*CTString *strInfo, COLOR *colInfo,*/ int &nInfoWidth, int &nInfoHeight)
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString	strTemp;
	m_nCurInfoLines = 0;

	for(int i = 0; i < MAX_SOCKET_OPTION; i++)
	{
		m_nSocketInfoShowLine[i] = 0;
	}

	if (m_nIndex < 0)
	{
		nInfoWidth = 27 - _pUIFontTexMgr->GetFontSpacing() + DEF_MAXSTRINGCHAR *
				( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() );
		nInfoHeight = 19 - _pUIFontTexMgr->GetLineSpacing() + _pUIFontTexMgr->GetLineHeight();

#ifdef	_DEBUG
		AddInfoString( CTString("none") );
#endif	// _DEBUG
		return;
	}

	switch(m_betType)
	{
	case UBET_ITEM:
		{
			CItemData* pItemData = _pNetwork->GetItemData(m_nIndex);
			CItemRareOption* pItemRareOption = NULL;
			int iRareGrade = -1;
			BOOL bRareItem = FALSE;
			int nItemleveldown = 0;
			BOOL bTransmogrify = m_ulFlag & FLAG_ITEM_TRANSMOGRIFY;

			if(  pItemData->IsFlag(ITEM_FLAG_RARE) && !bTransmogrify)
			{			
				bRareItem = TRUE;
				INDEX iRare = m_uwRareIndex;
				
				pItemRareOption = CItemRareOption::getData(iRare);

				if (pItemRareOption != NULL)
					iRareGrade = pItemRareOption->GetGrade();
				else
					iRareGrade = 0;
			}
			else
			{
				bRareItem = FALSE;
				iRareGrade =-1;
			}

			if (_pNetwork->m_ubGMLevel > 1)
			{
				CTString strIndex;
				strIndex.PrintF("Index [%d]", m_nIndex);
				AddInfoString(strIndex);
			}

			const CTString strItemName =_pNetwork->GetItemName( pItemData->GetItemIndex() );

			CTString szItemName =strItemName;
			if( bRareItem )
			{
				if (pItemRareOption != NULL)
				{
					CTString strPrefix = pItemRareOption->GetPrefix();
					if( strPrefix.Length() >0)
						szItemName.PrintF("%s %s", strPrefix, strItemName);
				}
			}

			COLOR colNas = 0xF2F2F2FF;

			// Get item name
			if( pItemData->GetFlag() & ITEM_FLAG_COUNT )
			{
				CTString	strCount;
				SQUAD		llCountSum = 0;
				strCount.PrintF( "%I64d", m_llCount );

				pUIManager->InsertCommaToString( strCount );
				strTemp.PrintF( "%s(%s)", szItemName, strCount );

				colNas = pUIManager->GetNasColor( m_llCount );		

				AddInfoString( strTemp, colNas );
			}
			else
			{
				if( ( ( pItemData->GetType() == CItemData::ITEM_WEAPON && !pItemData->IsProductionItem() )||
					pItemData->GetType() == CItemData::ITEM_SHIELD ) )
				{
					if(m_ulFlag&(PLATINUM_MAX_PLUS) || m_ulFlag&(FLAG_ITEM_COMPOSITION) || 
						pItemData->IsFlag(ITEM_FLAG_COMPOSITE) || pItemData->IsFlag(ITEM_FLAG_CASH))
					{
						strTemp.PrintF( "%s",szItemName);

						if(m_ulPlus > 0)
						{
							// �� �߿�, �ѹ��ǻ��� ��ȭ ��ġ ǥ�� ����
							if ( (pItemData->GetType() == CItemData::ITEM_SHIELD &&
								  pItemData->GetSubType() == CItemData::ITEM_SHIELD_ONE_SUIT) == false )
							{
								int plat_plus,diff;
								FLAG_ITEM_PLATINUM_GET(m_ulFlag,plat_plus);
								diff = m_ulPlus - plat_plus;
																
								CTString strMsg;
								if(diff > 0)
								{
									strMsg.PrintF("+%d",diff) ;
									strTemp +=strMsg;
								}
								if(plat_plus > 0)
								{
									strMsg.PrintF("[+%d]",plat_plus) ;
									strTemp +=strMsg;
								}
							}							
						}

						if (pItemData->IsFlag(ITEM_FLAG_ORIGIN) && !bTransmogrify)
						{
							colNas = 0xCC66FFFF;
						}

						AddInfoString( strTemp, iRareGrade >= 0 ? RareItem_Name_Color[iRareGrade] : colNas);

						CTString strTime1, strTime2;

						if (pItemData->IsFlag(ITEM_FLAG_COMPOSITE))
						{
							//strTime1 = _S(3219, "�ǻ󸸷� : %d��%d��%d��%d��");
						}

						if(m_ulFlag&(FLAG_ITEM_COMPOSITION))
						{
							strTemp.PrintF( _S( 2706, "�ɷ�ġ ���� ȿ��"));
							AddInfoString( strTemp, 0xFFAA44FF );

							strTime2 = CTString("");

						//	strTime2 = _S(3220, "���ո��� : %d��%d��%d��%d��"); // �Ⱓ�� �����ֹ��� ������ ���� �ߴ�[10/11/2011 ldy1978220]

						}
						else if(m_ulFlag&(PLATINUM_MAX_PLUS))
						{
								strTemp.PrintF( _S( 2675, "�÷�Ƽ�� ���� ȿ��"));
								AddInfoString( strTemp, 0xFFAA44FF );

								//strTime1 = _S(2525,"���� : %d��%d��%d��%d��");
								//strTime2 = CTString("");
						}
						else if(pItemData->IsFlag(ITEM_FLAG_CASH))
						{
							//strTime1 = _S(2525,"���� : %d��%d��%d��%d��");
							//strTime2 = CTString("");
						}

						if (m_ulUsed > 0)
						{
							gt_tv_t = localtime((time_t*)&m_ulUsed);
							strTemp.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),gt_tv_t->tm_year + 1900
								,gt_tv_t->tm_mon + 1,gt_tv_t->tm_mday,gt_tv_t->tm_hour, gt_tv_t->tm_min);
								
							AddInfoString( strTemp, 0xFFAA44FF );
						}

						// ITEM_FLAG_ABS �÷��װ� �ִ� �������� Item_Used2�� �����ð��� �ִ�.(�Ⱓ�� �ƴ� �ð�(��))
						// ����� Item_Used������ ǥ���Ѵ�.

						// �Ⱓ�� �����ֹ��� ������ ���� �ߴ�[10/11/2011 ldy1978220]
					}
					else if(m_ulFlag&(FLAG_ITEM_LENT) && !bTransmogrify)
					{
						CTString tv_str=_S(3046,"�뿩");
						tv_str+= CTString(" ")+szItemName;
						if(m_ulPlus > 0)
						{
							strTemp.PrintF( "%s +%d", tv_str, m_ulPlus );
							AddInfoString( strTemp, colNas );
						}
						else 
						{
							strTemp.PrintF( "%s",tv_str);
							AddInfoString( strTemp );
						}
						if(m_ulUsed > 0)
						{
							gt_tv_t = localtime((time_t*)&m_ulUsed);
							strTemp.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),gt_tv_t->tm_year + 1900
								,gt_tv_t->tm_mon + 1,gt_tv_t->tm_mday,gt_tv_t->tm_hour, gt_tv_t->tm_min);
				
							AddInfoString( strTemp, 0xFFAA44FF );
						}
					}
					else if ( !(m_ulFlag & (FLAG_ITEM_LEVELDOWN)) && !bTransmogrify)
					{
						if(m_ulPlus > 0)
						{
							strTemp.PrintF( "%s +%d", szItemName, m_ulPlus );
						//	AddInfoString( strTemp, colNas );
						}
						else
						{
							strTemp.PrintF( "%s",szItemName);
						//	AddInfoString( strTemp );
						}

						if (pItemData->IsFlag(ITEM_FLAG_ORIGIN))
						{
							colNas = 0xCC66FFFF;
						}

						AddInfoString( strTemp, iRareGrade >= 0 ? RareItem_Name_Color[iRareGrade] : colNas);
					}
				}
				else if( pItemData->GetType() == CItemData::ITEM_ACCESSORY)
				{
					if( pItemData->GetSubType() ==CItemData::ACCESSORY_PET)
					{
						const INDEX iPetIndex = m_ulPlus;
						SBYTE sbPetTypeGrade =pUIManager->GetPetInfo()->GetPetTypeGrade( iPetIndex );

						if( sbPetTypeGrade >0 )
						{
							INDEX iPetType;
							INDEX iPetAge;
							_pNetwork->CheckPetType( sbPetTypeGrade, iPetType, iPetAge );
							szItemName +=CTString(" - ")+PetInfo().GetName(iPetType, iPetAge);
						}
					}

					if (pItemData->IsFlag(ITEM_FLAG_ORIGIN))
					{
						colNas = 0xCC66FFFF;
					}

				//	AddInfoString( szItemName, colNas );
					AddInfoString( szItemName, iRareGrade >= 0 ? RareItem_Name_Color[iRareGrade] : colNas);
				}
				else
				{
					if (pItemData->GetType() == CItemData::ITEM_ETC && pItemData->GetSubType() == CItemData::ITEM_ETC_SYNDICATEJEWEL )
					{
						if(m_ulUsed > 0)
						{
							gt_tv_t = localtime((time_t*)&m_ulUsed);
							strTemp.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),gt_tv_t->tm_year + 1900
								,gt_tv_t->tm_mon + 1,gt_tv_t->tm_mday,gt_tv_t->tm_hour, gt_tv_t->tm_min);

							AddInfoString( strTemp, 0xFFAA44FF );
						}
					}
					
					if (bTransmogrify) {

					} else if( m_ulFlag&( FLAG_ITEM_BOOSTER_ADDED ) )
					{
						strTemp.PrintF(_S( 1929, "�ν�Ʈ %s" ), szItemName);	
					}
					else if( m_ulFlag&( FLAG_ITEM_SILVERBOOSTER_ADDED ) )
					{
						strTemp.PrintF(_S( 2429, "�ǹ� �ν�Ʈ %s" ), szItemName);	
					}
					else if( m_ulFlag&( FLAG_ITEM_GOLDBOOSTER_ADDED ) )
					{
						strTemp.PrintF(_S( 2430,"��� �ν�Ʈ %s" ), szItemName);	
					}
					else if( m_ulFlag&( FLAG_ITEM_PLATINUMBOOSTER_ADDED ) )
					{
						strTemp.PrintF(_S( 2639, "�÷�Ƽ�� �ν�Ʈ %s" ), szItemName);	
					}
					else
					{
						strTemp.PrintF("%s", szItemName);
					}
					
					AddInfoString( strTemp, colNas );
				}
			}
			
			// �Ⱓ�� �Ǽ��縮�� ���� �������� ��� ���� ���� ǥ��
			if(pItemData->GetType() == CItemData::ITEM_ACCESSORY
				|| pItemData->GetItemIndex()==2407 || pItemData->GetItemIndex()==2408 || pItemData->GetItemIndex()==2609
				|| pItemData->GetItemIndex() == 2500 || pItemData->GetItemIndex() == 2609
				|| pItemData->GetItemIndex() == 5018 || pItemData->GetItemIndex() == 5019
				|| pItemData->GetItemIndex() == 6941 ) //���� ���� 
			{
				if(m_ulUsed > 0)
				{
		#if defined(G_JAPAN)
					{
						gt_tv_t = localtime((time_t*)&m_ulUsed);
						strTemp.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),gt_tv_t->tm_year + 1900
							,gt_tv_t->tm_mon + 1,gt_tv_t->tm_mday,gt_tv_t->tm_hour, gt_tv_t->tm_min);
						
					}
		#else
					{
						gt_tv_t = localtime((time_t*)&m_ulUsed);
						strTemp.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),gt_tv_t->tm_year + 1900
							,gt_tv_t->tm_mon + 1,gt_tv_t->tm_mday,gt_tv_t->tm_hour, gt_tv_t->tm_min);
						//IN_VALIDTM(gt_tv_t)
					}
		#endif						
					AddInfoString( strTemp, 0xFFAA44FF );
				}
			}
			
			// Price - except money
			if( m_nWhichUI == UI_PERSONALSHOP && (pItemData->GetType() != CItemData::ITEM_ETC ||
				pItemData->GetSubType() != CItemData::ITEM_ETC_MONEY ) && m_llPrice > 0)
			{
				CTString	strMoney;
				
				strMoney.PrintF( "%I64d", m_llPrice );
				pUIManager->InsertCommaToString( strMoney );
				strTemp.PrintF( _S( 255, "���� : %I64d" ), strMoney );
				
				AddInfoString( strTemp, pUIManager->GetNasColor( m_llPrice ) );
			}

			switch( pItemData->GetType() )
			{
			case CItemData::ITEM_WEAPON:		// Weapon item
				{
					if(pItemData->IsFlag(ITEM_FLAG_ORIGIN) && !bTransmogrify)
					{
						if(Item_Belong != -1)
						{
							if (m_ulFlag&FLAG_ITEM_BELONG)
							{
								strTemp.PrintF(_S(4482, "���� ������"));
							}else 
							{
								strTemp.PrintF(_S(4483, "����� �ͼ�"));
							}
							AddInfoString(strTemp, 0xFFFFFFFF);
						}
					}

					//�ʰ��� ���ü� ����
					//TEMP : �ʰ��� ���ü� ����
					//�뿩 ������ �߰�...
					if(m_ulFlag&(FLAG_ITEM_LENT) && !bTransmogrify)
					{
						CTString strLeaseItem(_S(3047,"���ü� ���Ұ�" ));
						AddInfoString( strLeaseItem, 0xFF4040FF);

					}
					else if( pItemData->IsFlag( ITEM_FLAG_UPGRADE ) && !bTransmogrify) // �� �׷��̵� ���� ������ 
					{
						if (pItemData->GetLevel() >= RUNE_ITEM_LEVEL)
						{
							if( !( m_ulFlag&FLAG_ITEM_SUPER_RUNE_USED ) )
							{
								CTString strCanUseSuperRune(_S(5726, "�� ���� �� ��� ����" ));
								AddInfoString(strCanUseSuperRune, 0xFFFF40FF );
							}
#ifdef OPAL_MINUS_11132021
							if( !( m_ulFlag&FLAG_ITEM_OPAL_MINUS_USED ) )
							{
								CTString strCanUseSuperRune(_S(5726, "�� ���� �� ��� ����" ));
								AddInfoString(strCanUseSuperRune, 0xFFFF40FF );
							}
#endif
							strTemp.PrintF(_S(4484, "������ ���׷��̵� ����"));
							AddInfoString(strTemp, 0xFFFF40FF );
						}else
						{
							// �ʰ��� ����� �� ���� ���� ǥ��
							BOOL bCanUseSuperGOJE = !(m_ulFlag&FLAG_ITEM_SUPER_STONE_USED );
							CTString strCanUseSuperGOJE(_S( 1658, "�� ���� ���ü� ��� ����" ));
						
							if( bCanUseSuperGOJE )
								AddInfoString(strCanUseSuperGOJE, 0xFFFF40FF );
						}
					}
					CTString strReform;
					// ���� ���� ������Ʈ�� �߰� ������
					if (pItemData->IsFlag(ITEM_FLAG_ORIGIN) && !bTransmogrify)
					{
						if (pItemData->GetFlag() & ITEM_FLAG_NOT_REFORM)
						{
							strReform = _S(5774, "���� �Ұ�");
						}
						else
						{
							strReform = _S(5773, "��� ���� ����");
						}
						AddInfoString( strReform, 0xFFFF40FF );
					}
					// ���� ���� ������Ʈ�� �߰� ����
					if (pItemData->IsFlag(ITEM_FLAG_RARE) && !bTransmogrify)
					{
						if (pItemData->GetFlag() & ITEM_FLAG_NOT_REFORM)
						{
							strReform = _S(5774, "���� �Ұ�");
						}
						else
						{
							strReform = _S(5772, "�߱� ���� ����");
						}	
						AddInfoString( strReform, 0xFFFF40FF );
					}
				
					// Class
					CUIManager::GetClassOfItem( pItemData, strTemp );
					AddInfoString( strTemp, 0xFFFFFFFF );

					//������ ������� ������� ǥ��
					int	nItemLevel = pItemData->GetLevel();

					int nWearLevelReduction = GetWearLevelReduction();
					nItemleveldown = GetJewelLevelReduction();
					if( nWearLevelReduction >0 || nItemleveldown > 0 )
						strTemp.PrintF( _S( 160, "����: %d" ) +" (-%d)", nItemLevel, nWearLevelReduction+nItemleveldown );
					else
						strTemp.PrintF( _S( 160, "����: %d" ), nItemLevel );
					
					if (nItemleveldown > 0)
						AddInfoString(strTemp, 0xFFFF40FF);
					else 
						AddInfoString( strTemp,	0xFFFFFFFF );

					// ���� Ÿ���� �ִ� �������� ���.
					if (pItemData->GetSyndicateType() > 0)
					{
						GameDataManager* pGameData = GameDataManager::getSingleton();
						if (pGameData != NULL)
						{
							CSyndicate* pSyndicate = pGameData->GetSyndicate();

							if (pSyndicate != NULL)
							{
								strTemp.PrintF(_S(6169, "����:%s"), pSyndicate->GetSyndicateName(pItemData->GetSyndicateType()));
								AddInfoString( strTemp,	0xFFFFFFFF );
								strTemp.PrintF(_S(6170, "����:%s �̻�"), pSyndicate->GetGradeName(pItemData->GetSyndicateType(), pItemData->GetSyndicateGrade()));
								AddInfoString( strTemp,	0xFFFFFFFF );
							}
						}
					}

					int	nPlusValue;
					int nRarePhysicalAttack = 0;
					int nRareMagicAttack = 0;

					if (pItemRareOption)
					{
						nRarePhysicalAttack = pItemRareOption->GetPhysicalAttack();
						nRareMagicAttack = pItemRareOption->GetMagicAttack();
					}

					int nBasePhysicalAttack = pItemData->GetPhysicalAttack() + nRarePhysicalAttack;
					int nBaseMagicAttack = pItemData->GetMagicAttack() + nRareMagicAttack;
					if( m_ulPlus > 0 )
					{
						// Physical attack
						if( pItemData->GetPhysicalAttack() > 0 )
						{
#ifdef UPDATE_1106_ITEM_UPGRADE
							nPlusValue = CItems::ItemUpgradeFuckingFunction( pItemData->GetPhysicalAttack(), m_ulPlus, pItemData->GetLevel() >= 146 ? TRUE : FALSE);
#else
							nPlusValue = CItems::CalculatePlusDamage( pItemData->GetPhysicalAttack(), m_ulPlus, pItemData->GetLevel() >= 146 ? TRUE : FALSE);
#endif
							if( nPlusValue > 0 )
								strTemp.PrintF( _S( 355, "���ݷ� : %d + %d" ), nBasePhysicalAttack+m_lState_plus, nPlusValue );
							else
								strTemp.PrintF( _S( 161, "���ݷ� : %d" ), nBasePhysicalAttack+m_lState_plus);
																
							AddInfoString( strTemp, 0xFFFFFFFF );	//������� ǥ��

							if( m_ulPlus >= 15 && pItemData->GetLevel() < 146)
							{
								strTemp.PrintF(_S( 1891, "���� ���ݷ� + 75"));
								AddInfoString( strTemp, 0xFFFFFFFF );	//������� ǥ��
							}
						}

						// Magic attack
						if( pItemData->GetMagicAttack() > 0 )
						{
#ifdef UPDATE_1106_ITEM_UPGRADE
							nPlusValue = CItems::ItemUpgradeFuckingFunction( pItemData->GetMagicAttack(), m_ulPlus ,pItemData->GetLevel() >= 146 ? TRUE : FALSE);
#else
							nPlusValue = CItems::CalculatePlusDamage( pItemData->GetMagicAttack(), m_ulPlus ,pItemData->GetLevel() >= 146 ? TRUE : FALSE);
#endif
							if( nPlusValue > 0 )
								strTemp.PrintF( _S( 356, "���� ���ݷ� : %d + %d" ), nBaseMagicAttack+m_lState_plus, nPlusValue );
							else
								strTemp.PrintF( _S( 162, "���� ���ݷ� : %d" ), nBaseMagicAttack+m_lState_plus);

							AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��

							if( m_ulPlus >= 15 && pItemData->GetLevel() < 146 )
							{
								strTemp.PrintF(_S(1892,"���� ���ݷ� + 50"));
								AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��
							}
						}

						// �� ���� �������� ��� �߰���ġ ǥ��
						if ( pItemData->GetLevel() >= RUNE_ITEM_LEVEL )
						{
							int nRuneBonus = CItems::CalculateRuneItemBonus(pItemData->GetType(), m_ulPlus);
							if(nRuneBonus > 0)
							{
								strTemp.PrintF(_S(4810, "�߰� ���ݷ� %d���"), nRuneBonus);
								AddInfoString( strTemp, 0xFF6A00FF );
							}
							if (m_pItem->Item_Flag & FLAG_ITEM_ENCHANTED_USED)
							{
								strTemp.PrintF("Echantments:");
								AddInfoString(strTemp, 0xFF6A00FF);
								strTemp.PrintF("- Increased Gold 3%");
								AddInfoString(strTemp, 0xFF6A00FF);
								strTemp.PrintF("- PVP Damage Absorb 1.5%");
								AddInfoString(strTemp, 0xFF6A00FF);
								strTemp.PrintF("- Weapon Attack 3%");
								AddInfoString(strTemp, 0xFF6A00FF);
							}
							else if !(m_pItem->Item_Flag & FLAG_ITEM_ENCHANTED_USED)
							{
								strTemp.PrintF("Echantments:");
								AddInfoString(strTemp, 0xFF6A00FF);
								strTemp.PrintF("- None");
								AddInfoString(strTemp, 0xFF6A00FF);
								strTemp.PrintF("- None");
								AddInfoString(strTemp, 0xFF6A00FF);
								strTemp.PrintF("- None");
								AddInfoString(strTemp, 0xFF6A00FF);
							}
						}
					}
					else
					{
						// Physical attack
						if( pItemData->GetPhysicalAttack() > 0 )
						{
							strTemp.PrintF( _S( 161, "���ݷ� : %d" ), nBasePhysicalAttack+m_lState_plus);						
							AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��
						}

						// Magic attack
						if( pItemData->GetMagicAttack() > 0 )
						{
							strTemp.PrintF( _S( 162, "���� ���ݷ� : %d" ), nBaseMagicAttack+m_lState_plus );
							AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��
						}
					}

					// Penalty
					int	nPenalty = 0;
					int	nDiffLevel = (nItemLevel - nItemleveldown) - _pNetwork->MyCharacterInfo.level;
					if( nDiffLevel > 12 )
						nPenalty = 90;
					else if( nDiffLevel > 8 )
						nPenalty = 70;
					else if( nDiffLevel > 4 )
						nPenalty = 50;
					if( nPenalty > 0 && !bRareItem)
					{
						strTemp.PrintF( _S( 1029, "�г�Ƽ : ���ݷ� %d%% ����" ), nPenalty );		
						AddInfoString( strTemp, 0xE53535FF );
					}
#ifdef DURABILITY
					if (pItemData->IsFlag( ITEM_FLAG_DURABILITY) && !bTransmogrify)
					{
						int nDur = m_nDurNow / 10;
						COLOR strColor = 0xFFC000FF;

						strTemp.PrintF(_S(6191,"������: %d/%d"), nDur, m_nDurMax / 10);

						if (nDur <= 0)
							strColor = 0xFF0000FF;

						AddInfoString( strTemp, strColor );
					}
#endif	//	DURABILITY
				
					if(pItemData->GetSubType() == CItemData::ITEM_WEAPON_MINING 
						|| pItemData->GetSubType() == CItemData::ITEM_WEAPON_CHARGE
						|| pItemData->GetSubType() == CItemData::ITEM_WEAPON_GATHERING)
					{
						strTemp.PrintF(  _S( 510, "������ : %ld" ), m_ulUsed);		
						AddInfoString( strTemp, 0xDEC05BFF );
					}
				}
				break;

			case CItemData::ITEM_SHIELD:		// Shield item
				{
					//�ʰ��� ���ü� ���ü� ����
					//TEMP : �ʰ��� ���ü� ����
					if(pItemData->IsFlag(ITEM_FLAG_ORIGIN) && !bTransmogrify)
					{
						if(Item_Belong != -1)
						{
							if (m_ulFlag&FLAG_ITEM_BELONG)
							{
								strTemp.PrintF(_S(4482, "���� ������"));
							}else 
							{
								strTemp.PrintF(_S(4483, "����� �ͼ�"));
							}
							AddInfoString(strTemp, 0xFFFFFFFF);
						}
						
					}
					
					// $ ITEM_FLAG_ORIGIN ������� ���׷��̵� ���� ���� ǥ��
					if( pItemData->IsFlag( ITEM_FLAG_UPGRADE ) && !bTransmogrify) // �� �׷��̵� ���� ������ 
					{
						if (pItemData->GetLevel() >= 146)
						{
							if(!( m_ulFlag&FLAG_ITEM_SUPER_RUNE_USED ))
							{
								CTString strCanUseSuperRune(_S( 5726, "�� ���� �� ��� ����" ));
								AddInfoString(strCanUseSuperRune, 0xFFFF40FF );
							}
#ifdef OPAL_MINUS_11132021
							if(!( m_ulFlag&FLAG_ITEM_OPAL_MINUS_USED ))
							{
								CTString strCanUseSuperRune(_S( 8522, "�� ���� �� ��� ����" ));
								AddInfoString(strCanUseSuperRune, 0xFFFF40FF );
							}
#endif
							strTemp.PrintF(_S(4484, "������ ���׷��̵� ����"));
							AddInfoString(strTemp, 0xFFFF40FF );

						}else
						{
							// �ʰ��� ����� �� ���� ���� ǥ��
							BOOL bCanUseSuperGOJE = !(m_ulFlag&FLAG_ITEM_SUPER_STONE_USED );
							CTString strCanUseSuperGOJE(_S( 1658, "�� ���� ���ü� ��� ����" ));
						
							if( bCanUseSuperGOJE )
								AddInfoString(strCanUseSuperGOJE, 0xFFFF40FF );
						}
					}
					// ������ �� ������Ʈ���߰�

					CTString strReform;
					// �� ���� ������Ʈ�� �߰� ������
					if (pItemData->IsFlag(ITEM_FLAG_ORIGIN) && !bTransmogrify)
					{
						if (pItemData->GetFlag() & ITEM_FLAG_NOT_REFORM)
						{
							strReform = _S(5774, "���� �Ұ�");
						}
						else
						{
							strReform = _S(5773, "��� ���� ����");
						}
						AddInfoString( strReform, 0xFFFF40FF );

					}
					// �� ���� ������Ʈ�� �߰� ����
					if (pItemData->IsFlag(ITEM_FLAG_RARE) && !bTransmogrify)
					{
						if (pItemData->GetFlag() & ITEM_FLAG_NOT_REFORM)
						{
							strReform = _S(5774, "���� �Ұ�");
						}
						else
						{
							strReform = _S(5772, "�߱� ���� ����");
						}
						AddInfoString( strReform, 0xFFFF40FF );
					}
					
					

					// Class
					CUIManager::GetClassOfItem( pItemData, strTemp );				
					AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��

					int	nItemLevel = pItemData->GetLevel();

					int nWearLevelReduction = GetWearLevelReduction();
					nItemleveldown = GetJewelLevelReduction();

					if( nWearLevelReduction >0 || nItemleveldown > 0 )
						strTemp.PrintF( _S( 160, "����: %d" ) +" (-%d)", nItemLevel, nWearLevelReduction+nItemleveldown );
					else
						strTemp.PrintF( _S( 160, "����: %d" ), nItemLevel );

					if (nItemleveldown > 0) 
						 AddInfoString(strTemp, 0xFFFF40FF);
					else 
						 AddInfoString( strTemp,	0xFFFFFFFF );

					// ���� Ÿ���� �ִ� �������� ���.
					if (pItemData->GetSyndicateType() > 0)
					{
						GameDataManager* pGameData = GameDataManager::getSingleton();
						if (pGameData != NULL)
						{
							CSyndicate* pSyndicate = pGameData->GetSyndicate();

							if (pSyndicate != NULL)
							{
								strTemp.PrintF(_S(6169, "����:%s"), pSyndicate->GetSyndicateName(pItemData->GetSyndicateType()));
								AddInfoString( strTemp,	0xFFFFFFFF );
								strTemp.PrintF(_S(6170, "����:%s �̻�"), pSyndicate->GetGradeName(pItemData->GetSyndicateType(), pItemData->GetSyndicateGrade()));
								AddInfoString( strTemp,	0xFFFFFFFF );
							}
						}
					}

					int	nPlusValue;
					int nRarePhysicalDefence = 0;
					int nRareMagicDefence = 0;

					if (pItemRareOption)
					{
						nRarePhysicalDefence = pItemRareOption->GetPhysicalDefence();
						nRareMagicDefence = pItemRareOption->GetMagicDefence();
					}

					int nBasePhysicalDefence = pItemData->GetPhysicalDefence() + nRarePhysicalDefence;
					int nBaseMagicDefence = pItemData->GetMagicDefence() + nRareMagicDefence;
					if( m_ulPlus > 0 )
					{
						// Physical defense
						if( pItemData->GetPhysicalDefence() > 0 )
						{
#ifdef UPDATE_1106_ITEM_UPGRADE
							nPlusValue = CItems::ItemUpgradeFuckingFunction( pItemData->GetPhysicalDefence(), m_ulPlus, pItemData->GetLevel() >= 146 ? TRUE : FALSE );
#else
							nPlusValue = CItems::CalculatePlusDamage( pItemData->GetPhysicalDefence(), m_ulPlus, pItemData->GetLevel() >= 146 ? TRUE : FALSE );
#endif
							if( nPlusValue > 0 )
								strTemp.PrintF( _S( 357, "���� : %d + %d" ), nBasePhysicalDefence+m_lState_plus, nPlusValue );
							else
								strTemp.PrintF( _S( 163, "���� : %d" ), nBasePhysicalDefence+m_lState_plus );
																
							AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��

							if( m_ulPlus >= 15 && pItemData->GetLevel() < 146)
							{
								strTemp.PrintF(_S( 1893, "���� ���� + 100" ));										
								AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��

								strTemp.PrintF(_S( 1894, "���� ���� + 50" ));		
								AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��
							}
						}

						// Magic defense
						if( pItemData->GetMagicDefence() > 0 )
						{
#ifdef UPDATE_1106_ITEM_UPGRADE
							nPlusValue = CItems::ItemUpgradeFuckingFunction( pItemData->GetMagicDefence(), m_ulPlus, pItemData->GetLevel() >= 146 ? TRUE : FALSE );
#else
							nPlusValue = CItems::CalculatePlusDamage( pItemData->GetMagicDefence(), m_ulPlus, pItemData->GetLevel() >= 146 ? TRUE : FALSE );
#endif
							if( nPlusValue > 0 )
								strTemp.PrintF( _S( 358, "���� ���� : %d + %d" ), nBaseMagicDefence+m_lState_plus, nPlusValue );
							else
								strTemp.PrintF( _S( 164, "���� ���� : %d" ), nBaseMagicDefence+m_lState_plus );
														
							AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��

							if( m_ulPlus >= 15 && pItemData->GetLevel() < 146)
							{
								strTemp.PrintF(_S( 1893, "���� ���� + 100" ));		
								AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��

								strTemp.PrintF(_S( 1894, "���� ���� + 50" ));		
								AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��
							}
						}

						// �� ���� �������� ��� �߰���ġ ǥ��
						if ( pItemData->GetLevel() >= RUNE_ITEM_LEVEL )
						{
							int nRuneBonus = CItems::CalculateRuneItemBonus(pItemData->GetType(), m_ulPlus);
							if(nRuneBonus > 0)
							{
								strTemp.PrintF(_S(4811, "�߰� ���� %d���"), nRuneBonus);
								AddInfoString( strTemp, 0xFF6A00FF );
							}
							if (m_pItem->Item_Flag & FLAG_ITEM_ENCHANTED_USED)
							{
								strTemp.PrintF("Echantments:");
								AddInfoString(strTemp, 0xFF6A00FF);
								strTemp.PrintF("- Increased Gold 3%");
								AddInfoString(strTemp, 0xFF6A00FF);
								strTemp.PrintF("- PVP Damage Absorb 1.5%");
								AddInfoString(strTemp, 0xFF6A00FF);
								strTemp.PrintF("- Weapon Attack 3%");
								AddInfoString(strTemp, 0xFF6A00FF);
							}
							else if !(m_pItem->Item_Flag & FLAG_ITEM_ENCHANTED_USED)
							{
								strTemp.PrintF("Echantments:");
								AddInfoString(strTemp, 0xFF6A00FF);
								strTemp.PrintF("- None");
								AddInfoString(strTemp, 0xFF6A00FF);
								strTemp.PrintF("- None");
								AddInfoString(strTemp, 0xFF6A00FF);
								strTemp.PrintF("- None");
								AddInfoString(strTemp, 0xFF6A00FF);
							}
#ifdef G_USA	// [2012/06/11 : Sora]  ITS 9235 �� HP��� �ɼ� ǥ��
							if( ( m_ulPlus >= 10 ) && ( pItemData->GetSubType() != CItemData::ITEM_SHIELD_SHIELD ) )
							{
								strTemp.PrintF(_S(5700, "�߰� HP ���� %d"), ( m_ulPlus - 9 ) * 100 );
								AddInfoString( strTemp, 0xFFFFFFFF );
							}
#endif
						}

					}
					else
					{
						// Physical defense
						if( pItemData->GetPhysicalDefence() > 0 )
						{
							strTemp.PrintF( _S( 163, "���� : %d" ), nBasePhysicalDefence+m_lState_plus );
							AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��
						}

						// Magic defense
						if( pItemData->GetMagicDefence() > 0 )
						{
							strTemp.PrintF( _S( 164, "���� ���� : %d" ), nBaseMagicDefence+m_lState_plus );
							AddInfoString( strTemp, 0xFFFFFFFF );		//������� ǥ��
						}
					}

					// Penalty
					int	nPenalty = 0;
					int	nDiffLevel = (nItemLevel - nItemleveldown) - _pNetwork->MyCharacterInfo.level;
					if( nDiffLevel > 15 )
						nPenalty = 90;
					else if( nDiffLevel > 10 )
						nPenalty = 70;
					else if( nDiffLevel > 5 )
						nPenalty = 50;
					if( nPenalty > 0 && !bRareItem)
					{
						strTemp.PrintF( _S( 1030, "�г�Ƽ : ���� %d%% ����" ), nPenalty );		
						AddInfoString( strTemp, 0xE53535FF );
					}
#ifdef DURABILITY
					if (pItemData->IsFlag( ITEM_FLAG_DURABILITY) && !bTransmogrify)
					{
						int nDur = m_nDurNow / 10;
						COLOR strColor = 0xFFC000FF;

						strTemp.PrintF(_S(6191,"������: %d/%d"), nDur, m_nDurMax / 10);

						if (nDur <= 0)
							strColor = 0xFF0000FF;

						AddInfoString( strTemp, strColor );
					}
#endif	//	DURABILITY

					if (pItemData->GetSubType() == CItemData::ITEM_SHIELD_BACKWING)
					{ // ����Ʈ ������ ���� ����ӵ� ǥ��
						strTemp.PrintF(_S(4485, "����ӵ� : %.1f"), (pItemData->GetNum2() / 10.0f));
						AddInfoString( strTemp, 0xFFFFFFFF );
					}
				}
				break;

			case CItemData::ITEM_ACCESSORY:		// Accessory
				{
#ifdef DURABILITY
					if (pItemData->IsFlag( ITEM_FLAG_DURABILITY))
					{
						int nDur = m_nDurNow / 10;
						COLOR strColor = 0xFFC000FF;

						strTemp.PrintF(_S(6191,"������: %d/%d"), nDur, m_nDurMax / 10);

						if (nDur <= 0)
							strColor = 0xFF0000FF;

						AddInfoString( strTemp, strColor );
					}
#endif	//	DURABILITY

					if( pItemData->GetSubType() == CItemData::ACCESSORY_PET ) // ���� ��� 
					{
						// ������ ���� �о� �帰 �� ��ȯ ������ ã�Ƽ� ���
						SPetExchangeInfoString pPetExchangeInfo;
						// ������ ���� �е帰 �� ������ �ִ��� Ȯ�� �ִٸ� ������ ������ ����.
						if( pUIManager->GetPetInfo()->GetPetExchangeInfo( m_ulPlus, pPetExchangeInfo ) )
						{
							if( pPetExchangeInfo.strNameCard.Length() >0)
								AddInfoString( pPetExchangeInfo.strNameCard, 0xF2F2F2FF );
							AddInfoString( pPetExchangeInfo.strLevel, 0xDEC05BFF );		
							AddInfoString( pPetExchangeInfo.strHP, 0xDEC05BFF );		
							AddInfoString( pPetExchangeInfo.strlExp, 0xDEC05BFF );		
							AddInfoString( pPetExchangeInfo.strHungry, 0xDEC05BFF );		
							AddInfoString( pPetExchangeInfo.strSympathy, 0xDEC05BFF );		
							AddInfoString( pPetExchangeInfo.strAbility, 0xDEC05BFF );		
	#ifdef PET_SEAL_TIME
							AddInfoString( pPetExchangeInfo.strRemainTime, 0xDEC05BFF );
	#endif
						}
						
					}
					else if(pItemData->GetSubType() == CItemData::ACCESSORY_WILDPET)
					{
						sPetItem_Info pWildPetInfo;
						CWildPetData *m_Petdata = CWildPetData::getData(pItemData->GetPetType());

						if(pUIManager->GetWildPetInfo()->GetWildPetInfo(m_ulPlus,pWildPetInfo))
						{

							strTemp.PrintF(_S(4215, "�̸�: %s"),pWildPetInfo.pet_name);
							AddInfoString(strTemp,  0xF2F2F2FF );

							strTemp.PrintF(_S(4216, "�� ����: %d"),pWildPetInfo.pet_level);
							AddInfoString(strTemp, 0xDEC05BFF);
							if (m_Petdata->nFlag & WILDPET_FLAG_EXP)
							{
								INDEX temCooltime = pWildPetInfo.pet_cooltime - (unsigned int)_pTimer->GetLerpedCurrentTick();
								
								if(temCooltime > 0)
								{
									strTemp.PrintF(_S(5644, "��Ÿ��"));									
									
									int iSec = temCooltime % 60;
									temCooltime /= 60;
									
									int iMin = temCooltime % 60;
									int iHour = temCooltime /= 60;
									CTString temtime;
									temtime.PrintF(": ");
									strTemp += temtime;
									if (iHour > 0)
									{
										temtime.PrintF(_S(2512,"%d�ð�"),iHour);
										strTemp += temtime;
									}
									if (iMin > 0)
									{
										temtime.PrintF(_S(2513, "%d��"),iMin);
										strTemp += temtime;
									}
									if (iSec > 0)
									{
										temtime.PrintF(_S(2514,"%d��"),iSec);
										strTemp += temtime;
										
									}
									
								}else
								{
									strTemp.PrintF(_S(5639, "���� ����ġ: %I64d"),pWildPetInfo.pet_accexp);
								}
								AddInfoString(strTemp, 0xfd9d28FF);
							}else							
							{
								strTemp.PrintF(_S(4217, "��: %d"),pWildPetInfo.pet_str);
								AddInfoString(strTemp, 0xDEC05BFF);
								strTemp.PrintF(_S(4218, "��ø: %d"),pWildPetInfo.pet_dex);
								AddInfoString(strTemp, 0xDEC05BFF);
								strTemp.PrintF(_S(4219, "����: %d"),pWildPetInfo.pet_int);
								AddInfoString(strTemp, 0xDEC05BFF);
								strTemp.PrintF(_S(4220, "ü��: %d"),pWildPetInfo.pet_con);
								AddInfoString(strTemp, 0xDEC05BFF);
							}							
						}
					}
					else
					{
						if(pItemData->IsFlag(ITEM_FLAG_ORIGIN))
						{
							if(Item_Belong != -1)
							{
								if (m_ulFlag&FLAG_ITEM_BELONG)
								{
									strTemp.PrintF(_S(4482, "���� ������"));
								}else 
								{
									strTemp.PrintF(_S(4483, "����� �ͼ�"));
								}
								AddInfoString(strTemp, 0xFFFFFFFF);
							}
							
						}
						CTString strReform;
						// �Ǽ����� ���� ������Ʈ�� �߰� ������
						if (pItemData->IsFlag(ITEM_FLAG_ORIGIN))
						{
							if (pItemData->GetFlag() & ITEM_FLAG_NOT_REFORM)
							{
								strReform = _S(5774, "���� �Ұ�");
							}
							else
							{
								strReform = _S(5773, "��� ���� ����");
							}
							AddInfoString( strReform, 0xFFFF40FF );							
						}
						// �Ǽ����� ���� ������Ʈ�� �߰� ����
						if (pItemData->IsFlag(ITEM_FLAG_RARE))
						{
							if (pItemData->GetFlag() & ITEM_FLAG_NOT_REFORM)
							{
								strReform = _S(5774, "���� �Ұ�");
							}
							else
							{
								strReform = _S(5772, "�߱� ���� ����");
							}
							AddInfoString( strReform, 0xFFFF40FF );
						}

						// ���� Ÿ���� �ִ� �������� ���.
						if (pItemData->GetSyndicateType() > 0)
						{
							GameDataManager* pGameData = GameDataManager::getSingleton();
							if (pGameData != NULL)
							{
								CSyndicate* pSyndicate = pGameData->GetSyndicate();

								if (pSyndicate != NULL)
								{
									strTemp.PrintF(_S(6169, "����:%s"), pSyndicate->GetSyndicateName(pItemData->GetSyndicateType()));
									AddInfoString( strTemp,	0xFFFFFFFF );
									strTemp.PrintF(_S(6170, "����:%s �̻�"), pSyndicate->GetGradeName(pItemData->GetSyndicateType(), pItemData->GetSyndicateGrade()));
									AddInfoString( strTemp,	0xFFFFFFFF );
								}
							}
						}
					}
				
				}
				break;
				
				// ��ȸ��
			case CItemData::ITEM_ONCEUSE:
				{
					// ���� Ÿ���� �ִ� �������� ���.
					if (pItemData->GetSyndicateType() > 0)
					{
						GameDataManager* pGameData = GameDataManager::getSingleton();
						if (pGameData != NULL)
						{
							CSyndicate* pSyndicate = pGameData->GetSyndicate();

							if (pSyndicate != NULL)
							{
								strTemp.PrintF(_S(6169, "����:%s"), pSyndicate->GetSyndicateName(pItemData->GetSyndicateType()));
								AddInfoString( strTemp,	0xFFFFFFFF );
								strTemp.PrintF(_S(6170, "����:%s �̻�"), pSyndicate->GetGradeName(pItemData->GetSyndicateType(), pItemData->GetSyndicateGrade()));
								AddInfoString( strTemp,	0xFFFFFFFF );
							}
						}
					}

					// ����Ʈ ���� ǥ��.
					if ( pItemData->GetSubType() == CItemData::ITEM_SUB_QUEST_SCROLL )
					{	
						const int iQuestIndex = pItemData->GetNum0();

						if( iQuestIndex != -1 )
						{
							// ����Ʈ �̸� ���
							strTemp.PrintF( "%s", CQuestSystem::Instance().GetQuestName( iQuestIndex ) );
							AddInfoString( strTemp, 0xDEC05BFF );
							
							const int iMinLevel = CQuestSystem::Instance().GetQuestMinLevel( iQuestIndex );
							const int iMaxLevel = CQuestSystem::Instance().GetQuestMaxLevel( iQuestIndex );

							// ���� ���� ���.
							strTemp.PrintF( _S( 1660, "���� ���� : %d ~ %d" ), iMinLevel, iMaxLevel );		
							AddInfoString( strTemp, 0xDEC05BFF );
						}
					}
					
					if ( pItemData->GetSubType() == CItemData::ITEM_SUB_WARP || pItemData->GetSubType() == CItemData::ITEM_SUB_CASH_ITEM)
					{
						if(m_ulUsed > 0)
						{
							gt_tv_t = localtime((time_t*)&m_ulUsed);
							strTemp.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),gt_tv_t->tm_year + 1900
								,gt_tv_t->tm_mon + 1,gt_tv_t->tm_mday,gt_tv_t->tm_hour, gt_tv_t->tm_min);
							AddInfoString( strTemp, 0xDEC05BFF );
							//IN_VALIDTM(gt_tv_t)
						}
					}

				}
				break;

			case CItemData::ITEM_POTION:	// Date : 2005-01-07,   By Lee Ki-hwan
				{
					// ���� Ÿ���� �ִ� �������� ���.
					if (pItemData->GetSyndicateType() > 0)
					{
						GameDataManager* pGameData = GameDataManager::getSingleton();
						if (pGameData != NULL)
						{
							CSyndicate* pSyndicate = pGameData->GetSyndicate();

							if (pSyndicate != NULL)
							{
								strTemp.PrintF(_S(6169, "����:%s"), pSyndicate->GetSyndicateName(pItemData->GetSyndicateType()));
								AddInfoString( strTemp,	0xFFFFFFFF );
								strTemp.PrintF(_S(6170, "����:%s �̻�"), pSyndicate->GetGradeName(pItemData->GetSyndicateType(), pItemData->GetSyndicateGrade()));
								AddInfoString( strTemp,	0xFFFFFFFF );
							}
						}
					}

					// Date : 2005-01-14,   By Lee Ki-hwan
					if( pItemData->GetSubType() == CItemData::POTION_POTAL_SCROLL )
					{	
						if( pItemData->IsFlag(ITEM_FLAG_CASH) )
						{
							CTString strTime1, strTime2;
							strTime1 = _S(2525,"���� : %d��%d��%d��%d��");
							strTime2 = CTString("");
							
							gt_tv_t = localtime((time_t*)&m_ulUsed);				
							strTemp.PrintF(strTime1,gt_tv_t->tm_year + 1900, gt_tv_t->tm_mon + 1, gt_tv_t->tm_mday, gt_tv_t->tm_hour);
							
							AddInfoString( strTemp, 0xFFAA44FF );
						}
					}
					
					if ( pItemData->GetSubType() == CItemData::POTION_UP )
					{
						if( m_ulFlag > 0 )
						{
							// Level
							strTemp.PrintF( _S( 160, "����: %d" ), m_ulFlag );
							AddInfoString( strTemp, 0xD28060FF );

							// ��� Ÿ��
							int nSkillType = pItemData->GetSkillType();
							CSkill	&rSkill = _pNetwork->GetSkillData( nSkillType );
							int Power = rSkill.GetPower( m_ulFlag - 1);


							if(  pItemData->GetNum1() == CItemData::POTION_UP_PHYSICAL ) // ����
							{
								if(  pItemData->GetNum2() == CItemData::POTION_UP_ATTACK ) // ����
								{
									strTemp.PrintF ( _S( 790, "���� ���ݷ� +%d ���" ), Power );
									AddInfoString( strTemp, 0xDEC05BFF );
								}
								else if( pItemData->GetNum2() == CItemData::POTION_UP_DEFENSE ) // ���
								{
									strTemp.PrintF ( _S( 791, "���� ���� +%d ���" ),  Power );
									AddInfoString( strTemp, 0xDEC05BFF );
								}

							}
							else if( pItemData->GetNum1() == CItemData::POTION_UP_MAGIC ) // ����
							{
								if(  pItemData->GetNum2() == CItemData::POTION_UP_ATTACK ) // ����
								{
									strTemp.PrintF ( _S( 792, "���� ���ݷ� +%d ���" ),  Power );
									AddInfoString( strTemp, 0xDEC05BFF );
								}
								else if( pItemData->GetNum2() == CItemData::POTION_UP_DEFENSE ) // ���
								{
									strTemp.PrintF ( _S( 793, "���� ���� +%d ���" ),  Power );
									AddInfoString( strTemp, 0xDEC05BFF );
								}
							
							}
						}
							
					}
				}
			case CItemData::ITEM_BULLET:		// Bullet item
				{
				}
				break;

			case CItemData::ITEM_ETC:			// Etc item
				{
					// ���� Ÿ���� �ִ� �������� ���.
					if (pItemData->GetSyndicateType() > 0)
					{
						GameDataManager* pGameData = GameDataManager::getSingleton();
						if (pGameData != NULL)
						{
							CSyndicate* pSyndicate = pGameData->GetSyndicate();

							if (pSyndicate != NULL)
							{
								strTemp.PrintF(_S(6169, "����:%s"), pSyndicate->GetSyndicateName(pItemData->GetSyndicateType()));
								AddInfoString( strTemp,	0xFFFFFFFF );
								strTemp.PrintF(_S(6170, "����:%s �̻�"), pSyndicate->GetGradeName(pItemData->GetSyndicateType(), pItemData->GetSyndicateGrade()));
								AddInfoString( strTemp,	0xFFFFFFFF );
							}
						}
					}

					switch( pItemData->GetSubType() )
					{
					case CItemData::ITEM_ETC_REFINE:
						{
							// FIXME : ���� ǥ�ð� �ȵȴٱ� �ؼ�...
							// �������� ǥ�ð� �Ǿ��ִٸ�, ǥ�ø� �����ش�.
							/*if( m_ulFlag&( FLAG_ITEM_OPTION_ENABLE ) )
							{
								m_ulFlag ^= FLAG_ITEM_OPTION_ENABLE;
							}*/

							// Level
							if( m_ulFlag > 0 )
							{
								strTemp.PrintF( _S( 160, "����: %d" ), m_ulFlag );
								AddInfoString( strTemp, 0xD28060FF );
							}
						}
						break;
						// ������ ������ & ��ȭ��.
					case CItemData::ITEM_ETC_OPTION:
						{

						}
						break;
					case CItemData::ITEM_ETC_EVENT:
						{// Date : 2006-06-02(���� 2:27:41), By eons
							if( m_nIndex == 1483 )
							{// ������ ī��
								ULONG ulTemp = m_ulPlus;

								int nScoreA = static_cast<int>( ( ulTemp & 0xFFFF0000 ) >> 16 );
								int nScoreB = static_cast<int>( ulTemp & 0x0000FFFF );
								
								strTemp.PrintF( "%s (%d) VS (%d) %s", pUIManager->GetQuest()->GetStrTeamA(), nScoreA,
									nScoreB, pUIManager->GetQuest()->GetStrTeamB() );

								AddInfoString( strTemp, 0xFFAA44FF );
							}
						}
						break;
					case CItemData::ITEM_PET_AI:
						{
							if(m_ulUsed > 0)
							{
				#if defined(G_JAPAN)
								{
									gt_tv_t = localtime((time_t*)&m_ulUsed);
									strTemp.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),gt_tv_t->tm_year + 1900
										,gt_tv_t->tm_mon + 1,gt_tv_t->tm_mday,gt_tv_t->tm_hour, gt_tv_t->tm_min);
									AddInfoString( strTemp, 0xDEC05BFF );
								}
				#else
								{
									gt_tv_t = localtime((time_t*)&m_ulUsed);
									strTemp.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),gt_tv_t->tm_year + 1900
										,gt_tv_t->tm_mon + 1,gt_tv_t->tm_mday,gt_tv_t->tm_hour, gt_tv_t->tm_min);
									AddInfoString( strTemp, 0xDEC05BFF );
									//IN_VALIDTM(gt_tv_t)
								}
				#endif
							}

						}break;
					}
				}
				break;
			}
			

			// [090807 sora] Ʈ���� �������� ��� �����ð� ǥ��
			if(pItemData->GetFlag() & ITEM_FLAG_TRIGGER)
			{
				if(m_ulUsed > 0)
				{
#if defined(JAPAN)
					{
						gt_tv_t = localtime((time_t*)&m_ulUsed);
						strTemp.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),gt_tv_t->tm_year + 1900
							,gt_tv_t->tm_mon + 1,gt_tv_t->tm_mday,gt_tv_t->tm_hour, gt_tv_t->tm_min);
						AddInfoString( strTemp, 0xDEC05BFF );
					}
#else
					{
						gt_tv_t = localtime((time_t*)&m_ulUsed);
						strTemp.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),gt_tv_t->tm_year + 1900
							,gt_tv_t->tm_mon + 1,gt_tv_t->tm_mday,gt_tv_t->tm_hour, gt_tv_t->tm_min);
						AddInfoString( strTemp, 0xDEC05BFF );
						//IN_VALIDTM(gt_tv_t)
					}
#endif
				}
			}

			const int iFame = pItemData->GetFame();
			if( iFame > 0 )
			{
				strTemp.PrintF( _S( 1096, "���� %d �ʿ�" ), iFame );		
				AddInfoString( strTemp, 0xDEC05BFF );
			}

			if( bRareItem )
			{
				if( m_uwRareIndex ==0 )
					AddInfoString( _S(3165, "<�̰��� �ɼ�>"), 0xFF4040FF );
			}

			// only weapon & shield.
			if( pItemData->IsFlag( ITEM_FLAG_SOCKET) && !bTransmogrify)
			{
				LONG		lJewelIndex;
				SBYTE		count = 0;
				CTString	info;

#ifdef ENABLE_SOCKET_INFO
				if( !(m_ulFlag & FLAG_ITEM_SOCKET) )
				{
					if (Item_SocketCount <= 0)
					{
						info.PrintF( "%s", _S( 4993, "���� ���� ����" ) );
						AddInfoString( info, 0x00FF00FF );
					}
				}
#endif
				// ������ �����Ҷ���.
				if( Item_SocketCount > 0 )
				{
					for( SBYTE sbCount = 0; sbCount < MAX_SOCKET_OPTION; ++sbCount )
					{
						if( Item_SocketJewelIndex[sbCount] > 0 )
						{
							++count;
							//break;
						}
					}

					info.PrintF( "%s ( %d / %d )", _S( 4994, "���� ����" ), count, Item_SocketCount );
					AddInfoString( info, 0xFFFFFFFF );

					CTString strSocketSpace = CTString("    ");
					m_bSocketCreatedItem = TRUE;

					for( SBYTE sbOption = 0; sbOption < MAX_SOCKET_OPTION; ++sbOption )
					{
						lJewelIndex	 = Item_SocketJewelIndex[sbOption];

						if (lJewelIndex < 0)
							continue;

						if( lJewelIndex == 0 )
						{
							if(sbOption == 0)
							{
								strTemp.PrintF( "%s : %s", _S( 5901, "ī���� ����Ȧ" ), _S( 4996, "�������")  );
								strTemp = strSocketSpace + strTemp;
								m_nSocketInfoShowLine[sbOption] = m_nCurInfoLines;
								AddInfoString( strTemp, 0xFFFFFFFF );									
								continue;
							}

							strTemp.PrintF( "%s : %s", _S( 4995, "����Ȧ" ), _S( 4996, "�������")  );
							strTemp = strSocketSpace + strTemp;
							m_nSocketInfoShowLine[sbOption] = m_nCurInfoLines;
							AddInfoString( strTemp, 0xFFFFFFFF );
							continue;
						}

						CItemData* pItemdata = _pNetwork->GetItemData( lJewelIndex );
						int nJewelOptionType = pItemdata->GetPetAISet1();

						if (UtilHelp* pHelp = UtilHelp::getSingleton())
						{
							switch( pHelp->GetOptionType(nJewelOptionType) )
							{
							case OPTION_TYPE_PACIVE:
								strTemp = GetOptionPaciveInfo(*pItemdata);
								break;

							case OPTION_TYPE_ACTIVE:
								strTemp = GetOptionAciveSkillInfo(*pItemdata);
								break;

							default:
								strTemp.PrintF("find Option type fail");
								break;
							}
						}
						// socket system color change. [6/1/2010 rumist]
						strTemp = strSocketSpace + strTemp;
						m_nSocketInfoShowLine[sbOption] = m_nCurInfoLines;
						if (sbOption == 0)
							AddInfoString( strTemp, 0xFFFF50FF );
						else
							AddInfoString( strTemp, 0xFF610CFF );
					}	// end for
				}
			}
			// Options
			switch( pItemData->GetType() )
			{
			case CItemData::ITEM_WEAPON:
			case CItemData::ITEM_SHIELD:
			case CItemData::ITEM_ACCESSORY:
			case CItemData::ITEM_ETC:
				{
					if( pItemData->GetType() == CItemData::ITEM_ETC && pItemData->GetSubType() != CItemData::ITEM_ETC_JEWEL && pItemData->GetSubType() != CItemData::ITEM_ETC_SKILL &&
						pItemData->GetSubType() != CItemData::ITEM_ETC_MONSTER_MERCENARY_CARD && pItemData->GetSubType() != CItemData::ITEM_ETC_CHAOSJEWEL )
					{	// ������ ��쿡�� ������ ������ ��µǾ�� ��. // [2010/10/20 : Sora] ���� �뺴 ī���߰�
						break;
					}
					// ���� ���� ���� ���� �߰� �κ�
					if (pItemData->GetType() == CItemData::ITEM_ETC && (pItemData->GetSubType() == CItemData::ITEM_ETC_JEWEL || pItemData->GetSubType() == CItemData::ITEM_ETC_CHAOSJEWEL) 
						&& pItemData->GetPetAISet0() > 0)
					{
						CTString strCompositePos = CTString("");
						CTString strCompositeTemp = CTString("");
						bool	bComma = false;

						if (pItemData->GetPetAISet0() == 255)
						{
							strCompositePos.PrintF(_S( 506, "��ü" ));
						}
						else
						{
							if (pItemData->GetPetAISet0() & JEWEL_COMPOSITE_POSITION_WEAPON)
							{
								strCompositePos.PrintF(_S( 4775, "����" ));
								bComma = true;
							}

							if (pItemData->GetPetAISet0() & JEWEL_COMPOSITE_POSITION_HELMET)
							{
								if (bComma)
								{
									strCompositeTemp.PrintF(_S( 2544, "����" ));
									strCompositePos = strCompositePos + CTString(", ") + strCompositeTemp;
								}
								else
								{
									strCompositePos.PrintF(_S( 2544, "����" ));
									bComma = true;
								}
							}

							if (pItemData->GetPetAISet0() & JEWEL_COMPOSITE_POSITION_ARMOR)
							{
								if (bComma)
								{
									strCompositeTemp.PrintF(_S( 4273, "����" ));
									strCompositePos = strCompositePos + CTString(", ") + strCompositeTemp;
								}
								else
								{									
									strCompositePos.PrintF(_S( 4273, "����" ));
									bComma = true;
								}
							}

							if (pItemData->GetPetAISet0() & JEWEL_COMPOSITE_POSITION_PANTS)
							{
								if (bComma)
								{
									strCompositeTemp.PrintF(_S( 4274, "����" ));
									strCompositePos = strCompositePos + CTString(", ") + strCompositeTemp;
								}
								else
								{			
									strCompositePos.PrintF(_S( 4274, "����" ));
									bComma = true;
								}
							}

							if (pItemData->GetPetAISet0() & JEWEL_COMPOSITE_POSITION_GLOVES)
							{
								if (bComma)
								{
									strCompositeTemp.PrintF(_S( 4275, "�尩" ));
									strCompositePos = strCompositePos + CTString(", ") + strCompositeTemp;
								}
								else
								{			
									strCompositePos.PrintF(_S( 4275, "�尩" ));
									bComma = true;
								}
							}

							if (pItemData->GetPetAISet0() & JEWEL_COMPOSITE_POSITION_SHOES)
							{
								if (bComma)
								{
									strCompositeTemp.PrintF(_S( 4276, "�Ź�" ));
									strCompositePos = strCompositePos + CTString(", ") + strCompositeTemp;
								}
								else
								{			
									strCompositePos.PrintF(_S( 4276, "�Ź�" ));
									bComma = true;
								}
							}

							if (pItemData->GetPetAISet0() & JEWEL_COMPOSITE_POSITION_SHIELD)
							{
								if (bComma)
								{
									strCompositeTemp.PrintF(_S( 4277, "����" ));
									strCompositePos = strCompositePos + CTString(", ") + strCompositeTemp;
								}
								else
								{			
									strCompositePos.PrintF(_S( 4277, "����" ));
									bComma = true;
								}
							}

							if (pItemData->GetPetAISet0() & JEWEL_COMPOSITE_POSITION_BACKWING)
							{
								if (bComma)
								{
									strCompositeTemp.PrintF(_S( 5916, "��" ));
									strCompositePos = strCompositePos + CTString(", ") + strCompositeTemp;
								}
								else
								{			
									strCompositePos.PrintF(_S( 5916, "��" ));
								}
							}
						}

						strTemp.PrintF( _S( 5915, "���� ���� ���� : %s"), strCompositePos );
						AddInfoString( strTemp, 0x94B7C6FF );
					}

					SBYTE	sbOptionType;
					LONG	lOptionLevel;
					LONG	lOriginOptionVar;

					if( pItemData->GetType() == CItemData::ITEM_ETC && 
							(pItemData->GetSubType() == CItemData::ITEM_ETC_JEWEL || 
							 pItemData->GetSubType() == CItemData::ITEM_ETC_CHAOSJEWEL) )
					{
						int nJewelOptionType = pItemData->GetPetAISet1();

						if (UtilHelp* pHelp = UtilHelp::getSingleton())
						{
							switch( pHelp->GetOptionType(nJewelOptionType) )
							{
							case OPTION_TYPE_PACIVE:
								strTemp = GetJewelOptionInfo(*pItemData);
								break;
								
							case OPTION_TYPE_ACTIVE:
								strTemp = GetJewelOptionSkillInfo(*pItemData);
								break;
								
							default:
								strTemp.PrintF("find Option type fail");
								break;
							}
						}
						AddInfoString( strTemp, 0x94B7C6FF );
					}
					else
					{
						for( SBYTE sbOption = 0; sbOption < MAX_OPTION_INC_ORIGIN; ++sbOption )
						{
							sbOptionType = m_sbOptionType[sbOption];
							lOptionLevel = m_lOptionLevel[sbOption];
							lOriginOptionVar = m_lOriginOptionVar[sbOption];
							
							if( sbOptionType == -1 || lOptionLevel == 0 )
								continue;
							
							COptionData* podItem = COptionData::getData( sbOptionType );

							if (podItem == NULL)
								continue;

							if (UtilHelp* pHelp = UtilHelp::getSingleton())
							{
								switch( pHelp->GetPaciveOptionType(sbOptionType) )
								{
								case STRING_TYPE_INTEGER:
									strTemp.PrintF( "%s : %d", podItem->GetName(), (podItem->GetValue( lOptionLevel - 1 ) * lOriginOptionVar) / 100 );
									break;
								case STRING_TYPE_NEGATIVE:
									strTemp.PrintF( "%s : -%d", podItem->GetName(), podItem->GetValue( lOptionLevel - 1 ) );
									break;
								case STRING_TYPE_PERCENT:
									strTemp.PrintF( "%s : %d%%", podItem->GetName(), (podItem->GetValue( lOptionLevel - 1 ) * lOriginOptionVar) / 100 );
									break;
								case STRING_TYPE_FLOAT_POINT_ONE:
									strTemp.PrintF( "%s : %.1f", podItem->GetName(), ((podItem->GetValue( lOptionLevel - 1 ) * lOriginOptionVar) / 100) / 10.0f );
									break;
								case STRING_TYPE_FLOAT_POINT_TWO:
									strTemp.PrintF( "%s : %.2f", podItem->GetName(), ((podItem->GetValue( lOptionLevel - 1 ) * lOriginOptionVar) / 100) / 100.0f  );
									break;
								case STRING_TYPE_TRANS:
									if (podItem->GetValue(lOptionLevel - 1) == 0)
									{
										strTemp.PrintF("%s", _S(5305, "���� ����"));
										
									}else if (podItem->GetValue(lOptionLevel - 1) == 100)
									{
										strTemp.PrintF("%s", _S(5306, "���� ���� ����"));
									}else
									{
										strTemp.PrintF( "%s : %d", podItem->GetName(), podItem->GetValue( lOptionLevel - 1 ));
									}
									break;
								}
							}
							AddInfoString( strTemp, 0x94B7C6FF );
						}
					}
					if( m_ulFlag&( FLAG_ITEM_OPTION_ENABLE ) )
					{
						AddInfoString( _S( 511, "������ �ɼ� ����" ), 0xE53535FF );		
					}
					if( m_ulFlag&( FLAG_ITEM_SEALED ) )
					{
						AddInfoString(  _S( 512, "���ε� ������" ), 0xE53535FF );		
					}

					if (pItemData->IsFlag(ITEM_FLAG_ORIGIN))
					{
						for (SBYTE i = 0; i < MAX_ITEM_SKILL; i++)
						{
							if (Item_SkillIndex[i] != -1)
							{
								CSkill &rSetItemSkill = _pNetwork->GetSkillData(Item_SkillIndex[i]);
								strTemp.PrintF(_S(4486, "��ų ȿ�� : %s"),rSetItemSkill.GetDescription());
								AddInfoString(strTemp, 0xCC66FFFF);
							}
							
						}
					}

					// [2010/10/20 : Sora] ���� �뺴 ī��
					if( pItemData->GetSubType() == CItemData::ITEM_ETC_MONSTER_MERCENARY_CARD )
					{
						if(m_ulUsed > 0)
						{
				#if defined(G_JAPAN)
							{
								gt_tv_t = localtime((time_t*)&m_ulUsed);
								strTemp.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),gt_tv_t->tm_year + 1900
									,gt_tv_t->tm_mon + 1,gt_tv_t->tm_mday,gt_tv_t->tm_hour, gt_tv_t->tm_min);
								AddInfoString( strTemp, 0xFFAA44FF );
							}
				#else
							{
								gt_tv_t = localtime((time_t*)&m_ulUsed);
								strTemp.PrintF(  _S( 6070,"���� : %d��%d��%d��%d��%d��"),gt_tv_t->tm_year + 1900
									,gt_tv_t->tm_mon + 1,gt_tv_t->tm_mday,gt_tv_t->tm_hour, gt_tv_t->tm_min);
								AddInfoString( strTemp, 0xDEC05BFF );
								//IN_VALIDTM(gt_tv_t)
							}
				#endif
						}

						if( m_ulUsed2 > 0 )
						{
							strTemp.PrintF(_s("[%s]%s"), pUIManager->GetMonsterMercenary()->GetMonsterGrade(m_ulUsed2),
											CMobData::getData(m_ulPlus)->GetName());
							AddInfoString( strTemp, 0x94B7C6FF );

							int attackPlus = (int)( ( m_lState_plus & 0x0000FF00 ) >> 8 );
							int defencePlus = (int)( m_lState_plus & 0x000000FF );

							if( attackPlus > 0 )
							{
								strTemp.PrintF(_S( 5147, "����,���� ���ݷ� + %d"), attackPlus );
								AddInfoString( strTemp, 0x94B7C6FF );
							}
							if( defencePlus > 0 )
							{
								strTemp.PrintF(_S( 5148, "���� + %d"), defencePlus );
								AddInfoString( strTemp, 0x94B7C6FF );
							}
						}
					}
				}
				break;
			}

			DOUBLE dReuseTime = GetReuseTime();

			if( HasReuseTimeItem() && dReuseTime > 0 )
			{
				DOUBLE coolTime = GetCoolTime( GetReuseTime(), pItemData->StartTime );
				int	min = 0, second = 0;

				if (coolTime > 60)
				{
					min = static_cast<int>(coolTime / 60);
					second = static_cast<int>(coolTime) % 60;
					strTemp.PrintF(_S(4736, "��Ÿ�� : %d�� %d��"), min, second);
				}
				else if ( coolTime >= 3)
				{
					second = static_cast<int>(coolTime);
					strTemp.PrintF(_S(4737, "��Ÿ�� : %d��"), second);
				}
				else if ( coolTime >= 0.0f )
				{
					strTemp.PrintF(_S(6256, "��Ÿ�� : %.1f��"), coolTime);
				}

				if (coolTime > 0.0f)
				{
					AddInfoString( strTemp, 0xFF0000FF );
				}
			}
			// Description
			const char	*pDesc = _pNetwork->GetItemDesc( pItemData->GetItemIndex() );
			if( pDesc[0] != NULL )
			{
				strTemp.PrintF( "%s", pDesc );
				AddInfoString( strTemp, 0x9E9684FF );
			}

		}break;
	case UBET_SKILL:
		{
			if (_pNetwork->m_ubGMLevel > 1)
			{
				CTString strIndex;
				strIndex.PrintF("Index [%d]", m_nIndex);
				AddInfoString(strIndex);
			}

			if(!m_bSpecial)
			{	
				CSkill	&rSelSkill = _pNetwork->GetSkillData( m_nIndex );
				// Get skill name
#if defined(G_RUSSIA)
					strTemp.PrintF( "%s %s %d", rSelSkill.GetName(), _S( 4414, "LV" ), m_nSkillLevel );
#else
					strTemp.PrintF( "%s Lv %d", rSelSkill.GetName(), m_nSkillLevel );
#endif
				AddInfoString( strTemp );

				// Get skill type etc...
				//m_nSkillLevel--;
				switch( rSelSkill.GetType() )
				{
				case CSkill::ST_MELEE:
				case CSkill::ST_RANGE:
				case CSkill::ST_MAGIC:
				case CSkill::ST_SUMMON_TOTEM_SKILL:
					{
						if( rSelSkill.GetFlag() & SF_SINGLEMODE )
							AddInfoString( _S( 499, "�۽��δ��� ���� ��ų" ), 0xCACACAFF );		
						else if ( rSelSkill.GetFlag() & SF_GUILD )
							AddInfoString( _S( 3874, "��� ��ų" ), 0xCACACAFF );	
						else
							AddInfoString( _S( 63, "��Ƽ�� ��ų" ), 0xCACACAFF );

						int	nNeedMP = rSelSkill.GetNeedMP( m_nSkillLevel-1 );
						int	nNeedHP = rSelSkill.GetNeedHP( m_nSkillLevel-1 );
						if( nNeedHP == 0 )
						{
							if( nNeedMP != 0 )
							{
								// �꽺ų�� ��� ���� ���� �ʴ´�.
								if (rSelSkill.GetJob() != WILDPET_JOB && pUIManager->GetNeedMPReductionRate() > 0)
								{
									int nNeedMPReduction = (nNeedMP*pUIManager->GetNeedMPReductionRate())/100;
									strTemp.PrintF( _S( 64, "�Ҹ� MP : %d" )+" (-%d)", nNeedMP, nNeedMPReduction );
								}
								else
									strTemp.PrintF( _S( 64, "�Ҹ� MP : %d" ), nNeedMP );
								AddInfoString( strTemp, 0x94B7C6FF );
							}
						}
						else
						{
							if( nNeedMP == 0 )
							{
								strTemp.PrintF( _S( 500, "�Ҹ� HP : %d" ), nNeedHP );		
								AddInfoString( strTemp, 0x94B7C6FF );
							}
							else
							{
								if (rSelSkill.GetJob() != WILDPET_JOB && pUIManager->GetNeedMPReductionRate() > 0)
								{
									int nNeedMPReduction = (nNeedMP*pUIManager->GetNeedMPReductionRate())/100;
									strTemp.PrintF( _S( 64, "�Ҹ� MP : %d" )+" (-%d)", nNeedMP, nNeedMPReduction );
								}
								else
									strTemp.PrintF( _S( 64, "�Ҹ� MP : %d" ), nNeedMP );
								AddInfoString( strTemp, 0x94B7C6FF );
								strTemp.PrintF( _S( 500, "�Ҹ� HP : %d" ), nNeedHP );		
								AddInfoString( strTemp, 0x94B7C6FF );
							}
						}

						//�Ҹ� ������ ǥ�� �߰�
						{
							int		nNeed[2], nCnt[2];
							nNeed[0] = rSelSkill.GetNeedItemIndex1(m_nSkillLevel-1);
							nNeed[1] = rSelSkill.GetNeedItemIndex2(m_nSkillLevel-1);
							nCnt[0] = rSelSkill.GetNeedItemCount1(m_nSkillLevel-1);
							nCnt[1] = rSelSkill.GetNeedItemCount2(m_nSkillLevel-1);					
							bool bRet[2];
							SWORD swTab, swIdx;
							COLOR col = 0xFF0000FF;

							for (int i = 0; i < 2; ++i)
							{
								bRet[i] = ItemHelp::HaveItem( nNeed[i], &swTab, &swIdx, nCnt[i] );

								if (bRet[i] == true)
									col = 0x94B7C6FF;
							}

							if (nNeed[0] > 0 || nNeed[1] > 0)
							{
								strTemp.PrintF(_S(4405,"�Ҹ� ������"));
								AddInfoString(strTemp, col);

								for (int i = 0; i < 2; ++i)
								{
									if (nNeed[i] > 0)
									{
										const char	*pItemName = _pNetwork->GetItemName( nNeed[i] );
										strTemp.PrintF("- %s(%d)", pItemName, nCnt[i]);
										AddInfoString(strTemp, col);
									}
								}
							}
						}

						//�Ҹ� ������ ǥ�� �߰�
// 						if (rSelSkill.GetNeedItemIndex1(m_nSkillLevel-1) > 0 || rSelSkill.GetNeedItemIndex2(m_nSkillLevel-1) > 0)
// 						{
// 							AddInfoString(_S(4405,"�Ҹ� ������"), 0x94B7C6FF);
// 							if (rSelSkill.GetNeedItemIndex1(m_nSkillLevel-1) > 0)
// 							{
// 								const char	*pItemName = _pNetwork->GetItemName( rSelSkill.GetNeedItemIndex1(m_nSkillLevel-1) );
// 								strTemp.PrintF("- %s(%d)", pItemName, rSelSkill.GetNeedItemCount1(m_nSkillLevel-1));
// 								AddInfoString(strTemp, 0x94B7C6FF);
// 							}
// 							
// 							if (rSelSkill.GetNeedItemIndex2(m_nSkillLevel-1) > 0)
// 							{
// 								const char	*pItemName = _pNetwork->GetItemName( rSelSkill.GetNeedItemIndex2(m_nSkillLevel-1) );
// 								strTemp.PrintF("- %s(%d)", pItemName, rSelSkill.GetNeedItemCount2(m_nSkillLevel-1));
// 								AddInfoString(strTemp, 0x94B7C6FF);
// 							}
// 						}
						if ( rSelSkill.GetNeedGP( m_nSkillLevel-1 ) > 0 )
						{
							strTemp.PrintF( _S( 5032, "�Ҹ� GP : %d" ), rSelSkill.GetNeedGP( m_nSkillLevel-1 ) );	
							AddInfoString( strTemp, 0x94B7C6FF );
						}
						if( rSelSkill.GetPower( m_nSkillLevel-1 ) > 0 )
						{
							strTemp.PrintF( _S( 65, "���� : %d" ), rSelSkill.GetPower( m_nSkillLevel-1 ) );
							AddInfoString( strTemp, 0x94B7C6FF );
						}
						// [2012/03/09 : Sora] ��ų ��ȿ�Ÿ��� 0�ϰ�� ǥ������ �ʵ��� ó��(ITS 7673)
						if( rSelSkill.GetFireRange() > 0.0f )
						{
							strTemp.PrintF( _S( 66, "��ȿ �Ÿ� : %.1f" ), rSelSkill.GetFireRange() );
							AddInfoString( strTemp, 0x94B7C6FF );
						}

						// [091009 sora] ���� ��Ÿ�� ǥ��
						DOUBLE reUseTime = GetReuseTime();

						if( reUseTime  > 0.0f )
						{
							if (reUseTime >= 3)
								strTemp.PrintF( _S( 4173, "���� �ð� : %d�� " ), (int)reUseTime );
							else
								strTemp.PrintF( _S( 6257, "���� �ð� : %.1f�� " ), reUseTime );

							AddInfoString( strTemp, 0x94B7C6FF );

							DOUBLE coolTime =	GetCoolTime(reUseTime, rSelSkill.Skill_Data.Skill_StartTime );
							int	min = 0, second = 0;

							if (coolTime > 60)
							{
								min = static_cast<int>(coolTime / 60);
								second = static_cast<int>(coolTime) % 60;
								strTemp.PrintF(_S(4736, "��Ÿ�� : %d�� %d��"), min, second);
							}
							else if ( coolTime >= 3)
							{
								second = static_cast<int>(coolTime);
								strTemp.PrintF(_S(4737, "��Ÿ�� : %d��"), second);
							}
							else if ( coolTime >= 0.0f )
							{
								strTemp.PrintF(_S(6256, "��Ÿ�� : %.1f��"), coolTime);
							}

							if (coolTime > 0.0f)
							{
								AddInfoString( strTemp, 0xFF0000FF );
							}
						}
					}
					break;

				case CSkill::ST_PASSIVE:
				case CSkill::ST_PET_SKILL_PASSIVE:
					AddInfoString( _S( 67, "�нú� ��ų" ), 0xCACACAFF );
					break;
				}

				const char	*pDesc = rSelSkill.GetDescription();
				if( pDesc != NULL )
				{
					strTemp.PrintF( "%s", pDesc );
					AddInfoString( strTemp, 0x9E9684FF );
				}

				// �Ӽ� �ý��� ��ų ���� �Ӽ� ��Ʈ�� ��� [1/21/2013 Ranma]
				CTString strAtt;
				int nAtt = 0, nAttLv = 0;

				// ���� �Ӽ� [1/21/2013 Ranma]
				nAtt = int(rSelSkill.GetAttrAtt(m_nSkillLevel - 1));

				// �Ӽ� �ý��� ��ų ���� �Ӽ� ��Ʈ�� ��� [1/21/2013 Ranma]
				if (nAtt > 0)
				{
					switch(nAtt)
					{
					case 1:
						strAtt = _S( 5846, "��");
					break;

					case 2:
						strAtt = _S( 5847, "��");
					break;

					case 3:
						strAtt = _S( 5849, "����");
					break;

					case 4:
						strAtt = _S( 5848, "�ٶ�");
					break;

					case 5:
						strAtt = _S( 5850, "����");
					break;

					case 6:
						strAtt = _S( 5851, "��");
					break;

					default:
					break;
					}
					#ifdef ENABLE_ELEMENTAL_ICON_INFO
					nAttLv = int(rSelSkill.GetAttrAttLv(m_nSkillLevel - 1));
					strTemp.PrintF( _S(5845, "�Ӽ� ���� : [%s]�Ӽ� [%d]�ܰ�"), strAtt, nAttLv);
					AddInfoString(strTemp, 0xFF0000FF);
					#endif
				}

				// ��� �Ӽ� [1/21/2013 Ranma]
				nAtt = int(rSelSkill.GetAttrDef(m_nSkillLevel - 1));
				
				// �Ӽ� �ý��� ��ų ���� �Ӽ� ��Ʈ�� ��� [1/21/2013 Ranma]
				if (nAtt > 0)
				{
					switch(nAtt)
					{
					case 1:
						strAtt = _S( 5846, "��");
						break;
						
					case 2:
						strAtt = _S( 5847, "��");
						break;
						
					case 3:
						strAtt = _S( 5849, "����");
						break;
						
					case 4:
						strAtt = _S( 5848, "�ٶ�");
						break;
						
					case 5:
						strAtt = _S( 5850, "����");
						break;
						
					case 6:
						strAtt = _S( 5851, "��");
						break;
						
					default:
						break;
					}
					#ifdef ENABLE_ELEMENTAL_ICON_INFO
					nAttLv = int(rSelSkill.GetAttrDefLv(m_nSkillLevel - 1));
					strTemp.PrintF( _S(5845, "�Ӽ� ���� : [%s]�Ӽ� [%d]�ܰ�"), strAtt, nAttLv);
					AddInfoString(strTemp, 0x0000EEFF);
					#endif
				}

			}
			// Special Skill
			else
			{
				CSpecialSkill*	pSelSSKill = CSpecialSkill::getData( m_nIndex );

				if (pSelSSKill == NULL)
					return;
				// Get skill name
#if defined(G_RUSSIA)
					strTemp.PrintF( "%s %s %d", pSelSSKill->GetName(), _S( 4414, "LV" ), m_nSkillLevel );
#else
					strTemp.PrintF( "%s Lv %d", pSelSSKill->GetName(), m_nSkillLevel );
#endif
				AddInfoString( strTemp );

				AddInfoString( _S( 67, "�нú� ��ų" ), 0xCACACAFF );
				const char	*pDesc = pSelSSKill->GetDescription();
				if( pDesc != NULL )
				{
					strTemp.PrintF( "%s", pDesc );
					AddInfoString( strTemp, 0x9E9684FF );
				}
			}

		}break;
		case UBET_ACTION:
		{
			CAction* pSelAction = CAction::getData(m_nIndex);

			if (pSelAction == NULL)
				return;
			
			AddInfoString(pSelAction->GetName());
			
			if (pSelAction->GetDesc().IsEmpty() == FALSE)
			{
				AddInfoString( pSelAction->GetDesc(), 0x9E9684FF );
			}

		}break;
	}

	if(m_eCharType > CHAR_NAME_NONE)
	{
		switch(m_eCharType)
		{
			case CHAR_NAME_BUYER:
				strTemp.PrintF(_S(4380, "������ : %s"), m_strCharName);
				break;
			case CHAR_NAME_SELLER:
				strTemp.PrintF(_S(4381, "�Ǹ��� : %s"), m_strCharName);
				break;
			case CHAR_NAME_OWNER:
				strTemp.PrintF(_S(4382, "������ : %s"), m_strCharName);
				break;
		}	
		AddInfoString( strTemp, 0xE53535FF );
	}
//	strInfo = m_strButtonInfo;
//	colInfo	= m_colButtonInfo;
#if	defined(G_BRAZIL)
	int	iMaxStringChar	= DEF_MAXSTRINGCHAR;
	if(m_bWidthExtend == TRUE)
		iMaxStringChar	= DEF_MAXSTRINGCHAREXTEND;
	nInfoWidth = 27 - _pUIFontTexMgr->GetFontSpacing() + iMaxStringChar *
					( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() );
#elif defined(G_RUSSIA) 
	int	iMaxStringChar	= DEF_MAXSTRINGCHAR;

	if(m_bWidthExtend == TRUE)
		nInfoWidth = 242;
	else
		nInfoWidth = 151;

#else
	nInfoWidth = 27 - _pUIFontTexMgr->GetFontSpacing() + DEF_MAXSTRINGCHAR *
					( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() );
#endif
	nInfoHeight = 19 - _pUIFontTexMgr->GetLineSpacing() + (m_nCurInfoLines+1) * _pUIFontTexMgr->GetLineHeight();

	
}

int CUIButtonEx::GetWearLevelReduction()
{
	for( SBYTE sbOption = 0; sbOption < MAX_OPTION_INC_ORIGIN; ++sbOption )
	{
		int sbOptionType = (int)m_sbOptionType[sbOption];
		LONG lOptionLevel = m_lOptionLevel[sbOption];
		if( sbOptionType == -1 || lOptionLevel == 0 )
			break;

		//�������ѷ��� �ٿ� �ɼ�
		if( sbOptionType == OPTION_DOWN_LIMITLEVEL)
		{
			COptionData* odItem = COptionData::getData( sbOptionType );

			if (odItem == NULL)
				return 0;

			return odItem->GetValue( lOptionLevel - 1 );
		}
	}
	
	return 0;
}

int CUIButtonEx::GetJewelLevelReduction()
{
	SBYTE		sbOptionType;
	LONG		lOptionLevel;
	if (Item_SocketJewelIndex[JEWEL_POS_CHAOS_SOCKET] > 0)
	{
		CItemData* pLevelItemdata = _pNetwork->GetItemData( Item_SocketJewelIndex[JEWEL_POS_CHAOS_SOCKET] );
		sbOptionType = pLevelItemdata->GetSocketOptionIndex();
		lOptionLevel = pLevelItemdata->GetSocketOptionLevel();
		
		if ( sbOptionType == OPTION_DOWN_LIMITLEVEL )
		{
			COptionData* odItem = COptionData::getData( sbOptionType );

			if (odItem == NULL)
				return 0;

			return odItem->GetValue( lOptionLevel - 1 );
		}
	}	
	return 0;
}

void CUIButtonEx::RenderInfoPopup()
{
	if(!m_bShow || m_betType == UBET_EXPEDITION) 
		return;

	CUIManager* pUIManager = CUIManager::getSingleton();
	CDrawPort* pDrawPort = pUIManager->GetDrawPort();

	// Get position
	int	nInfoX,nInfoY;
	int nInfoWidth, nInfoHeight;

	if (m_ptdAddTexture == NULL)
		return;

	pDrawPort->InitTextureData( m_ptdAddTexture );

	int		i;
	// Get position
	int	nX, nY;
	GetAbsPos( nX, nY );

	GetButtonInfo(nInfoWidth,nInfoHeight);

	if (m_bSetItem)
	{
		int temWidth,temHeight;
		GetSetItemInfo(temWidth, temHeight);
		
		if (nInfoHeight < temHeight)
		{
			nInfoHeight = temHeight;			
		}
		nInfoWidth += temWidth;
	}

	if (m_bHasFortuneInfo)
		nInfoHeight = max(nInfoHeight, m_nFortuneInfoHeight);
	
	nInfoX = (nX+16)-nInfoWidth/2;
	nInfoY = nY - nInfoHeight;

	if( nInfoX < pUIManager->GetMinI() )
	{
		nInfoX = pUIManager->GetMinI();
	}
	else if (nInfoX + (m_bHasFortuneInfo ? nInfoWidth+m_nFortuneInfoWidth : nInfoWidth) > pUIManager->GetMaxI())
	{
		nInfoX = pUIManager->GetMaxI() - (m_bHasFortuneInfo ? nInfoWidth+m_nFortuneInfoWidth : nInfoWidth);
	}

	if (nInfoY < pUIManager->GetMinJ())
	{
		nInfoY = nY + BTN_SIZE;
	}

	if(m_strButtonInfo[0] == "") 
		return;

	m_bxPopupInfo.SetBoxPos(WRect(nInfoX-nX, nInfoY-nY, nInfoX-nX+nInfoWidth, nInfoY-nY+nInfoHeight ));
	m_bxPopupInfo.Render(nX,nY);
	for( i = 0; i < m_nCurInfoLines; i++ )
	{
		pDrawPort->PutTextEx(m_strButtonInfo[i],nInfoX+20,nInfoY+6+(i*14),m_colButtonInfo[i]);

	}
	
	if (m_bSetItem)
	{
		for( i = 0; i < m_nCurSetItemInfoLines; i++ )
		{
#if	defined(G_BRAZIL) | defined(G_RUSSIA)
			if(m_bWidthExtend == TRUE)
				pDrawPort->PutTextEx(m_strSetItemInfo[i],nInfoX+260,nInfoY+6+(i*14),m_colSetItemInfo[i]);
			else
				pDrawPort->PutTextEx(m_strSetItemInfo[i],nInfoX+200,nInfoY+6+(i*14),m_colSetItemInfo[i]);
#else
			pDrawPort->PutTextEx(m_strSetItemInfo[i],nInfoX+200,nInfoY+6+(i*14),m_colSetItemInfo[i]);
#endif
		}
	}

	if (m_bHasFortuneInfo)
	{
		m_bxPopupInfo.SetBoxPos(WRect(nInfoX+nInfoWidth-nX, nInfoY-nY,
									  nInfoX+nInfoWidth-nX+m_nFortuneInfoWidth, nInfoY-nY+nInfoHeight));
		m_bxPopupInfo.Render(nX, nY);

		int x = nInfoX+nInfoWidth;
		int y = nInfoY+6;

		// title -> "���� ����"
		pDrawPort->PutTextExCX(m_strFortuneInfoTitle, x+m_nFortuneInfoWidth/2, y, 0x00FF00FF);

		// skill name(color:0xBBC200FF)
		pDrawPort->PutTextEx(m_strFortuneSkillName, x+BTN_SIZE+24, y+27, 0xBBC200FF);
		pDrawPort->PutTextEx(m_strFortuneSkillName, x+BTN_SIZE+24+1, y+27, 0xBBC200FF);

		// skill desc(color:0xBBBDBAFF)
		y += BTN_SIZE+24;
		for( i = 0; i < m_vecFortuneSkillDesc.size(); i++ )
			pDrawPort->PutTextEx(m_vecFortuneSkillDesc[i], x+16, y+i*14, 0xBBBDBAFF);
		y += m_vecFortuneSkillDesc.size() * 14;

		// comment(color:0xBD6F3EFF) -> "����: %s"
		for( i = 0; i < m_vecFortuneSkillComment.size(); i++ )
			pDrawPort->PutTextEx(m_vecFortuneSkillComment[i], x+16, y+14*i, 0xBD6F3EFF);
	}


	// Render all elements
	pDrawPort->FlushRenderingQueue();

	if (m_bHasFortuneInfo)
	{
		// fortune skill icon
		int nX0 = nInfoX + nInfoWidth + 16;
		int nX1 = nX0 + BTN_SIZE;
		int nY0 = nInfoY + 24;
		int nY1 = nY0 + BTN_SIZE;

		CTextureData* ptdTexture = _pUIBtnTexMgr->GetTex(UBET_SKILL, m_nFortuneSkillIconTexID);
		pDrawPort->InitTextureData(ptdTexture);
		pDrawPort->AddTexture(nX0, nY0, nX1, nY1,
			m_rtFotuneSkillIconUV.U0, m_rtFotuneSkillIconUV.V0,
			m_rtFotuneSkillIconUV.U1, m_rtFotuneSkillIconUV.V1,
			0xFFFFFFFF);
		pDrawPort->FlushRenderingQueue();
	}

	// Flush all render text queue
	pDrawPort->EndTextEx();
	// ������ ���� �Ǿ��ٸ� üũ
	if( Item_SocketCount > 0 )
	{
		int lJewelIndex = -1;
		int nX0 = nInfoX + 20;
		int nX1 = nX0 + 18;
		int nY0 = nInfoY + 4;
		int nY1 = nY0 + 16;

		pDrawPort->InitTextureData(m_ptdSocketTexture);
		// ���������� ����
		for( SBYTE sbOption = 0; sbOption < MAX_SOCKET_OPTION; ++sbOption )
		{
			lJewelIndex	 = Item_SocketJewelIndex[sbOption];

			if (lJewelIndex < 0)
				continue;

			if( lJewelIndex == 0 )
			{
				if(sbOption == 0)
				{
					pDrawPort->AddTexture(nX0, nY0 + (14 * m_nSocketInfoShowLine[sbOption]), nX1, nY1 + (14 * m_nSocketInfoShowLine[sbOption]),
						m_rtSocketIcon[SOCKET_CHAOS_NONE].U0, m_rtSocketIcon[SOCKET_CHAOS_NONE].V0,
						m_rtSocketIcon[SOCKET_CHAOS_NONE].U1, m_rtSocketIcon[SOCKET_CHAOS_NONE].V1,
					0xFFFFFFFF);
					continue;
				}
				else
				{
					pDrawPort->AddTexture(nX0, nY0 + (14 * m_nSocketInfoShowLine[sbOption]), nX1, nY1 + (14 * m_nSocketInfoShowLine[sbOption]),
						m_rtSocketIcon[SOCKET_GENERAL_NONE].U0, m_rtSocketIcon[SOCKET_GENERAL_NONE].V0,
						m_rtSocketIcon[SOCKET_GENERAL_NONE].U1, m_rtSocketIcon[SOCKET_GENERAL_NONE].V1,
					0xFFFFFFFF);
					continue;
				}
			}
			else if( lJewelIndex > 0)
			{
				if(sbOption == 0)
				{
					pDrawPort->AddTexture(nX0, nY0 + (14 * m_nSocketInfoShowLine[sbOption]), nX1, nY1 + (14 * m_nSocketInfoShowLine[sbOption]),
						m_rtSocketIcon[SOCKET_CHAOS_EQUIP].U0, m_rtSocketIcon[SOCKET_CHAOS_EQUIP].V0,
						m_rtSocketIcon[SOCKET_CHAOS_EQUIP].U1, m_rtSocketIcon[SOCKET_CHAOS_EQUIP].V1,
						0xFFFFFFFF);
					continue;
				}
				else
				{
					pDrawPort->AddTexture(nX0, nY0 + (14 * m_nSocketInfoShowLine[sbOption]), nX1, nY1 + (14 * m_nSocketInfoShowLine[sbOption]),
						m_rtSocketIcon[SOCKET_GENERAL_EQUIP].U0, m_rtSocketIcon[SOCKET_GENERAL_EQUIP].V0,
						m_rtSocketIcon[SOCKET_GENERAL_EQUIP].U1, m_rtSocketIcon[SOCKET_GENERAL_EQUIP].V1,
						0xFFFFFFFF);
					continue;
				}
			}
		}

		pDrawPort->FlushRenderingQueue();
	}

	m_bWidthExtend		= FALSE;
}

void CUIButtonEx::RenderFixInfoPopup(bool bUpDown/*true ����, false �Ʒ���*/)
{
	if(!m_bShow || m_betType == UBET_EXPEDITION) 
		return;
	
	CUIManager* pUIManager = CUIManager::getSingleton();
	CDrawPort* pDrawPort = pUIManager->GetDrawPort();
	
	// Get position
	int	nInfoX,nInfoY;
	int nInfoWidth, nInfoHeight;
	pDrawPort->InitTextureData( m_ptdAddTexture );
	
	// Get position
	int	nX, nY;
	GetAbsPos( nX, nY );
	
	GetButtonInfo(nInfoWidth,nInfoHeight);
	
	if (m_bSetItem)
	{
		int temWidth,temHeight;
		GetSetItemInfo(temWidth, temHeight);
		
		if (nInfoHeight < temHeight)
		{
			nInfoHeight = temHeight;			
		}
		nInfoWidth += temWidth;
	}
	
	nInfoX = (nX+16)-nInfoWidth/2;
	nInfoY = nY - nInfoHeight;
	
	if (!bUpDown)
	{
		nInfoY = nY + BTN_SIZE;
	}
	
	if(m_strButtonInfo[0] == "") 
		return;
	
	m_bxPopupInfo.SetBoxPos(WRect(nInfoX-nX, nInfoY-nY, nInfoX-nX+nInfoWidth, nInfoY-nY+nInfoHeight ));
	m_bxPopupInfo.Render(nX,nY);
	for (int i = 0; i < m_nCurInfoLines; i++)
	{
		pDrawPort->PutTextEx(m_strButtonInfo[i],nInfoX+20,nInfoY+6+(i*14),m_colButtonInfo[i]);
		
	}
	
	if (m_bSetItem)
	{
		for (int i = 0; i < m_nCurSetItemInfoLines; i++)
		{
#if	defined(G_BRAZIL) | defined(G_RUSSIA) 
			if(m_bWidthExtend == TRUE)
				pDrawPort->PutTextEx(m_strSetItemInfo[i],nInfoX+260,nInfoY+6+(i*14),m_colSetItemInfo[i]);
			else
				pDrawPort->PutTextEx(m_strSetItemInfo[i],nInfoX+200,nInfoY+6+(i*14),m_colSetItemInfo[i]);
#else
			pDrawPort->PutTextEx(m_strSetItemInfo[i],nInfoX+200,nInfoY+6+(i*14),m_colSetItemInfo[i]);
#endif
		}
	}
	
	
	//	}
	
	// Render all elements
	pDrawPort->FlushRenderingQueue();
	
	// Flush all render text queue
	pDrawPort->EndTextEx();

	// ������ ���� �Ǿ��ٸ� üũ
	if( Item_SocketCount > 0 )
	{
		int lJewelIndex = -1;
		int nX0 = nInfoX + 20;
		int nX1 = nX0 + 18;
		int nY0 = nInfoY + 4;
		int nY1 = nY0 + 16;
		
		pDrawPort->InitTextureData(m_ptdSocketTexture);
		// ���������� ����
		for( SBYTE sbOption = 0; sbOption < MAX_SOCKET_OPTION; ++sbOption )
		{
			lJewelIndex	 = Item_SocketJewelIndex[sbOption];
			
			if (lJewelIndex < 0)
				continue;
			
			if( lJewelIndex == 0 )
			{
				if(sbOption == 0)
				{
					pDrawPort->AddTexture(nX0, nY0 + (14 * m_nSocketInfoShowLine[sbOption]), nX1, nY1 + (14 * m_nSocketInfoShowLine[sbOption]),
						m_rtSocketIcon[SOCKET_CHAOS_NONE].U0, m_rtSocketIcon[SOCKET_CHAOS_NONE].V0,
						m_rtSocketIcon[SOCKET_CHAOS_NONE].U1, m_rtSocketIcon[SOCKET_CHAOS_NONE].V1,
						0xFFFFFFFF);
					continue;
				}
				else
				{
					pDrawPort->AddTexture(nX0, nY0 + (14 * m_nSocketInfoShowLine[sbOption]), nX1, nY1 + (14 * m_nSocketInfoShowLine[sbOption]),
						m_rtSocketIcon[SOCKET_GENERAL_NONE].U0, m_rtSocketIcon[SOCKET_GENERAL_NONE].V0,
						m_rtSocketIcon[SOCKET_GENERAL_NONE].U1, m_rtSocketIcon[SOCKET_GENERAL_NONE].V1,
						0xFFFFFFFF);
					continue;
				}
			}
			else if( lJewelIndex > 0)
			{
				if(sbOption == 0)
				{
					pDrawPort->AddTexture(nX0, nY0 + (14 * m_nSocketInfoShowLine[sbOption]), nX1, nY1 + (14 * m_nSocketInfoShowLine[sbOption]),
						m_rtSocketIcon[SOCKET_CHAOS_EQUIP].U0, m_rtSocketIcon[SOCKET_CHAOS_EQUIP].V0,
						m_rtSocketIcon[SOCKET_CHAOS_EQUIP].U1, m_rtSocketIcon[SOCKET_CHAOS_EQUIP].V1,
						0xFFFFFFFF);
					continue;
				}
				else
				{
					pDrawPort->AddTexture(nX0, nY0 + (14 * m_nSocketInfoShowLine[sbOption]), nX1, nY1 + (14 * m_nSocketInfoShowLine[sbOption]),
						m_rtSocketIcon[SOCKET_GENERAL_EQUIP].U0, m_rtSocketIcon[SOCKET_GENERAL_EQUIP].V0,
						m_rtSocketIcon[SOCKET_GENERAL_EQUIP].U1, m_rtSocketIcon[SOCKET_GENERAL_EQUIP].V1,
						0xFFFFFFFF);
					continue;
				}
			}
		}
		
		pDrawPort->FlushRenderingQueue();
	}
	
	m_bWidthExtend		= FALSE;
}

void CUIButtonEx::SetCharName(eUIBtnCharNameType eCharType, CTString strCharName)
{
	// [sora] �����뿡���� ���
	m_eCharType = eCharType;
	
	if(strCharName.Length() == 0)
	{
		m_strCharName = _S( 3865, "����" );
	}
	else
	{
		m_strCharName = strCharName;
	}
}

void CUIButtonEx::GetSetItemInfo(int &nInfoWidth, int &nInfoHeight)
{
	if (m_betType != UBET_ITEM)
	{
		return;
	}

	CTString	strTemp;
	m_nCurSetItemInfoLines = 0;
	
	CItemData* pItemData = _pNetwork->GetItemData(m_nIndex);
	CSetItemData* pSetItemData = CSetItemData::getData(pItemData->GetSetItemIndex());

	if (pSetItemData == NULL)
		return;

	strTemp.PrintF("%s",pSetItemData->GetName());

	AddInfoString(strTemp, 0x20A51CFF, TRUE);

	int nWearTotal = 0;
	int nWearingCont = 0;
	for (int wearpos = 0; wearpos < WEAR_TOTAL; wearpos++)
	{
		LONG nApplyitem = pSetItemData->GetApplyItemIndex(wearpos);
		LONG nCosApplyitem = 0;
		LONG nCosApplyitemIndex = 0;

		if ( nApplyitem != -1 )
		{
			COLOR ntemColor = 0xB3B3B3FF;
			nWearTotal++;

			if (_pNetwork->MyWearItem[wearpos].IsEmptyItem() == FALSE)
			{
				// 2�� ���̰� �̽� ���� [2/27/2013 Ranma]
				CItemData* pTempItem = _pNetwork->GetItemData(_pNetwork->MyWearItem[wearpos].ItemData->GetItemIndex());

				if (pTempItem->IsFlag(ITEM_FLAG_COMPOSITE) || _pNetwork->MyWearItem[wearpos]->IsFlag(FLAG_ITEM_TRANSMOGRIFY))
				{
					nCosApplyitem = _pNetwork->MyWearItem[wearpos].GetComItem_index();
					
					for (int idx = 0; idx < ITEM_COUNT_IN_INVENTORY_NORMAL; ++idx)
					{
						if (nCosApplyitemIndex)
							break;
						if (nCosApplyitem <= 0)
							break;

						if (nCosApplyitem == _pNetwork->MySlotItem[ITEM_TAB_NORMAL][idx].Item_UniIndex)
						{
							nCosApplyitemIndex = _pNetwork->MySlotItem[ITEM_TAB_NORMAL][idx].Item_Index;
							break;
						}						
					}

					if (nCosApplyitemIndex == nApplyitem)
					{
						ntemColor = 0xFFFFFFFF;
						nWearingCont++;
					}
						
				}
				else
				{
					if (nApplyitem == _pNetwork->MyWearItem[wearpos].ItemData->GetItemIndex())
					{
						ntemColor = 0xFFFFFFFF;
						nWearingCont++;
					}
				}
			}
			
			strTemp.PrintF("%s",_pNetwork->GetItemName(nApplyitem));
			AddInfoString(strTemp, ntemColor, TRUE);
		}
	}

	strTemp.PrintF(_S(4487, "��Ʈ ���� ����(%d / %d)"), nWearingCont, nWearTotal );
	AddInfoString(strTemp,0x20A51CFF,TRUE);
	
	for (int Optioncont = 0; Optioncont < pSetItemData->GetMaxOption(); Optioncont++)
	{
		COLOR ntemColor = 0xB3B3B3FF;
		
		if (pSetItemData->GetOption(Optioncont).nSetType == CSetItemData::SET_ITEM_TYPE_OPTION)
		{
			COptionData* temOP = COptionData::getData(pSetItemData->GetOption(Optioncont).nSetOptionIndex);

			if (temOP != NULL)
				strTemp.PrintF( _S(4488, "(%d)��Ʈ �ɼ� ȿ�� [%s : %d]"), pSetItemData->GetOption(Optioncont).nSetCount, temOP->GetName(), temOP->GetValue( pSetItemData->GetOption(Optioncont).nOptionLevel - 1 ) );

		}else	// ��ų
		{
			CSkill& temSkill = _pNetwork->GetSkillData(pSetItemData->GetOption(Optioncont).nSetOptionIndex);
			strTemp.PrintF( _S(4489, "(%d)��Ʈ ��ų ȿ�� : %s"), pSetItemData->GetOption(Optioncont).nSetCount, temSkill.GetDescription() );
		}

		if (nWearingCont >= pSetItemData->GetOption(Optioncont).nSetCount)
		{
			ntemColor = 0x20A51CFF;
		}

		AddInfoString(strTemp, ntemColor, TRUE);
		
	}

	nInfoWidth = 27 - _pUIFontTexMgr->GetFontSpacing() + DEF_MAXSTRINGCHAR *
					( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() );
	nInfoHeight = 19 - _pUIFontTexMgr->GetLineSpacing() + (m_nCurSetItemInfoLines+1) * _pUIFontTexMgr->GetLineHeight();
#if defined(G_RUSSIA)
	if(m_bWidthExtend == TRUE)
		nInfoWidth = 242;
#endif
}


// ----------------------------------------------------------------------------
// Name : GetCoolTime()
// Desc : ���� ��Ÿ���� ����ؼ� ��ȯ�Ѵ�
// ----------------------------------------------------------------------------
DOUBLE CUIButtonEx::GetCoolTime(DOUBLE reUseTime, DOUBLE startTime)
{
	DOUBLE coolTime = reUseTime - (_pTimer->GetHighPrecisionTimer().GetSeconds() - startTime);

	if (coolTime > reUseTime) // ����ڵ� ���� �ð����� �� ū ���� ���� ���ϵ��� �Ѵ�.
		return reUseTime;
	
	if (coolTime <= 0.00f)
		return 0.00f;	// ���� �ð��� 0���� ������ ��Ÿ�� ����
	else
		return coolTime;
}

// ----------------------------------------------------------------------------
// Name : GetReuseTime()
// Desc : ���� �ð��� ����ؼ� ��ȯ�Ѵ�
// ----------------------------------------------------------------------------
DOUBLE CUIButtonEx::GetReuseTime()
{	
	if(m_betType == UBET_ITEM)
	{
		CItemData*	pItemData = _pNetwork->GetItemData( m_nIndex );

		if(pItemData->GetNum0())
		{
			return DOUBLE( _pNetwork->GetSkillData( pItemData->GetNum0() ).GetReUseTime() )/ 10.0;
		}
	}
	else if(m_betType == UBET_SKILL)
	{
		CSkill	&rSelSkill = _pNetwork->GetSkillData( m_nIndex );

		int nCoolTimeReductionRate = 0;
		DOUBLE dCoolTime = 0.0f;
		DOUBLE dReuseTime = 0.0f;
		int nReuseTime = 0;


		if (rSelSkill.GetJob() != PET_JOB && rSelSkill.GetJob() != WILDPET_JOB && !(rSelSkill.GetFlag()&SF_GUILD) )
		{ 
			// ��ų ��Ÿ�� �ɼ��� ĳ���Ϳ��Ը� �ٴ´�.
			if( !( rSelSkill.Skill_Data.appState & SCT_NOCOOLTIME ) )
			{
				nCoolTimeReductionRate = CUIManager::getSingleton()->GetCoolTimeReductionRate();
				dCoolTime = ( 150.00f / (150.00f + nCoolTimeReductionRate ) * 100.00f / (100.00f + nCoolTimeReductionRate) );
			}
		}

		if(rSelSkill.GetReUseTime())
		{
			dReuseTime = DOUBLE( rSelSkill.GetReUseTime() + _pNetwork->MyCharacterInfo.magicspeed ) / 10.00f *  (nCoolTimeReductionRate ? dCoolTime : 1);

			return dReuseTime;
		}
	}
	return 0.0f;
}

// ----------------------------------------------------------------------------
// Name : HasReuseTimeItem()
// Desc : ������ �� ��Ÿ���� �ִ� �������� Ȯ���Ѵ�(����� ����, ����, Ÿ������ �����۸� TRUE)
// ----------------------------------------------------------------------------
BOOL CUIButtonEx::HasReuseTimeItem()
{
	if (m_nIndex == -1)
		return FALSE;

	if( m_nIndex == 2407 || m_nIndex == 2408 || m_nIndex == 2609 || m_nIndex == 5018 ||
		m_nIndex == 5019 || m_nIndex == 2500 || m_nIndex == 2609)
	{
		return TRUE;
	}

	CItemData*	pItemData = _pNetwork->GetItemData( m_nIndex );		
	if( ( pItemData->GetType() == CItemData::ITEM_POTION ) ||
		( ( pItemData->GetType() == CItemData::ITEM_ONCEUSE && pItemData->GetSubType() == CItemData::ITEM_SUB_TARGET ) ) ||
		( pItemData->GetType() == CItemData::ITEM_ETC && pItemData->GetSubType() == CItemData::ITEM_ETC_MONSTER_MERCENARY_CARD ) )  
	{	// [2010/10/20 : Sora] ���� �뺴 ī���߰�
		return TRUE;
	}

	return FALSE;
}

void CUIButtonEx::SetItemPlus(ULONG ulPlus)
{
	m_ulPlus = ulPlus;
	m_bHasFortuneInfo = FALSE;
	if (m_ulPlus)
	{
		CItemData* pItemData = _pNetwork->GetItemData(m_nIndex);

		if (pItemData == NULL)
			return;
		
		if (pItemData->GetType() == CItemData::ITEM_SHIELD &&
			pItemData->GetSubType() == CItemData::ITEM_SHIELD_ONE_SUIT &&
			pItemData->GetFortuneIndex() > 0)
		{
			m_bHasFortuneInfo = TRUE;

			m_nFortuneSkillIndex = m_ulPlus >> 16;
			m_nFortuneSkillLevel = m_ulPlus & 0x0000FFFF;
			m_vecFortuneSkillDesc.clear();
			m_vecFortuneSkillComment.clear();
			
			// title -> "���� ����"
			m_strFortuneInfoTitle = _S(5893, "���� ����");
			
			// skill name(color:0xBBC200FF)
			CSkill &rSkillData = _pNetwork->GetSkillData(m_nFortuneSkillIndex);
			m_strFortuneSkillName = rSkillData.GetName();

			CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();
			m_nFortuneInfoWidth = pDrawPort->GetTextWidth2(m_strFortuneSkillName)+BTN_SIZE+48;
			if (m_nFortuneInfoWidth < 184)
				m_nFortuneInfoWidth = 184;

			int width = m_nFortuneInfoWidth - 34;
			extern void StringSplit(std::vector<CTString>& vecOutput, CTString strInput, ULONG ulColumnWidth);
			
			// skill desc(color:0xBBBDBAFF)
			CTString strText = rSkillData.GetDescription();
			StringSplit(m_vecFortuneSkillDesc, strText, width);

			// comment(color:0xBD6F3EFF) -> "����: %s"
			CItemData* pItemData = _pNetwork->GetItemData(m_nIndex);
			
			CFortuneData::_map::iterator	iter = CFortuneData::_mapdata.begin();
			CFortuneData::_map::iterator	eiter = CFortuneData::_mapdata.end();

			for (;iter != eiter; ++iter)
			{
				stFortune* info = (*iter).second;

				if (info == NULL)
					continue;

				if (info->skill_index == m_nFortuneSkillIndex &&
					info->skill_level == m_nFortuneSkillLevel)
				{
					strText.PrintF(_S(5894, "����: %s"), _S(info->string_index, "����"));
					StringSplit(m_vecFortuneSkillComment, strText, width);
					break;
				}
			}			
			
			// fortune skill icon
			m_nFortuneSkillIconTexID = rSkillData.GetIconTexID();
			CTextureData* ptdTexture = _pUIBtnTexMgr->GetTex(UBET_SKILL, m_nFortuneSkillIconTexID);
			FLOAT fTexWidth = ptdTexture->GetPixWidth();
			FLOAT fTexHeight = ptdTexture->GetPixHeight();
			int	nUVSX = BTN_SIZE * rSkillData.GetIconTexCol();
			int	nUVSY = BTN_SIZE * rSkillData.GetIconTexRow();
			m_rtFotuneSkillIconUV.SetUV(nUVSX, nUVSY, nUVSX + BTN_SIZE, nUVSY + BTN_SIZE, fTexWidth, fTexHeight);

			m_nFortuneInfoHeight = 12;
			m_nFortuneInfoHeight += BTN_SIZE+24;
			m_nFortuneInfoHeight += m_vecFortuneSkillDesc.size() * 14;
			m_nFortuneInfoHeight += m_vecFortuneSkillComment.size() * 14;
		}
	}
}

void CUIButtonEx::RenderStack(int nX, int nY, CDrawPort* pDrawPort)
{
	CItemData* pItemData = _pNetwork->GetItemData(m_nIndex);
	if( pItemData != NULL && m_betType == UBET_ITEM && (pItemData->GetFlag() & ITEM_FLAG_COUNT) )
	{
		if( m_bShowStack )
		{
			CTString	strCount;
			if( m_llCount > pItemData->GetStack() ) // [4/15/2013 ����] stack ó��
			{
				m_pImageFont->Hide(TRUE);
				strCount.PrintF( "..." );

				pDrawPort->PutTextEx(strCount, nX, nY + 18, 0xFFF300FF);
				pDrawPort->EndTextEx();
			}
			else
			{
				if( m_llCount > 1 )
				{
					m_pImageFont->Hide(FALSE);
					m_pImageFont->SetPos(nX+2, nY + 21);
					strCount.PrintF( "%I64d", m_llCount );
					m_pImageFont->setString( strCount.str_String );
					m_pImageFont->OnRender(pDrawPort);
				}
			}
		}
	}
}

void CUIButtonEx::RenderDurZero( int nX, int nY, CDrawPort* pDraw )
{
#ifdef DURABILITY
	if (m_bDuraZero == true)
	{
		m_imgDurabilityZero->SetPos( nX, nY);
		m_imgDurabilityZero->OnRender(pDraw);
	}
#endif	//	DURABILITY
}
void CUIButtonEx::RenderToggleAni( int nX, int nY, CDrawPort* pDrawPort )
{
	if( m_bToggleState == true )
	{
		m_paniToggle->SetPos( nX - 16, nY - 16); // size 64 button 32  (size - button) / 2
		m_paniToggle->UpdateAni();
		m_paniToggle->OnRender(pDrawPort);
	}
}

void CUIButtonEx::SetSkillBlend( bool bBlend, int idx )
{
	m_bSkillBlend = bBlend; 

	CSkill	&rSkillData = _pNetwork->GetSkillData( idx );

	if (GetSkillBlend() == true)
		m_nTextureID = rSkillData.GetIconTexID() + 3;
	else
		m_nTextureID = rSkillData.GetIconTexID();
}

void CUIButtonEx::UpdateCoolTime()
{
	if( m_bSkillDelay && ( !m_bSpecial || m_betType == UBET_ITEM ) )
	{
		DOUBLE dStartTime;
		DOUBLE dCoolTime;
		DOUBLE dReUseTime = GetReuseTime();

		if(m_betType == UBET_SKILL)
		{
			dStartTime = _pNetwork->GetSkillData( m_nIndex ).Skill_Data.Skill_StartTime;
		}
		else if( m_betType == UBET_ITEM )
		{
			dStartTime =  _pNetwork->GetItemData( m_nIndex )->StartTime;
		}

		dCoolTime = GetCoolTime(dReUseTime, dStartTime);

		if(  dCoolTime < 0.5 )
		{
			float fDelta;

			fDelta = dCoolTime * 10;

			if( fDelta < 0 || fDelta > 5 ) 
			{
				fDelta = 0;
			}
			if( dCoolTime == 0.0f )
				m_bSkillDelay = FALSE;
		}
	}
}

void CUIButtonEx::CopyItems( CItems* pItem )
{
	// SetItemInfo�� �ش����� ����
	SetItemFlag( pItem->Item_Flag );
	SetItemPlus( pItem->Item_Plus );
	SetItemUsed( pItem->Item_Used );
	SetItemUsed2( pItem->Item_Used2 );
	SetItemRareIndex( pItem->Item_RareIndex );

	SetItemCount(pItem->Item_Sum);
	SetItemBelong(pItem->Item_Belong);
	SetItemPlus2(pItem->Item_State_Plus);

	CItemData*	pItemData = _pNetwork->GetItemData( pItem->Item_Index );
	SetItemPrice(pItemData->GetPrice());

	for (int OpCount = 0; OpCount < MAX_OPTION_INC_ORIGIN; OpCount++)
	{
		SetItemOptionData(OpCount,
			pItem->GetOptionType(OpCount),
			pItem->GetOptionLevel(OpCount),
			pItem->GetOriginOptionVar(OpCount));
	}

	for (int nSkillcont = 0; nSkillcont < MAX_ITEM_SKILL; nSkillcont++)
	{
		SetItemSkill(nSkillcont, 
			pItem->GetSetItemSkillIndex(nSkillcont),
			pItem->GetSetItemSkillLevel(nSkillcont));

	}

	InitItemSocketInfo();
	SetItemSocketCount( pItem->GetSocketCount() );

#ifdef	DURABILITY
	int now, max;
	pItem->GetDurability(now, max);
	SetItemDurNow(now);
	SetItemDurMax(max);
#endif	//	DURABILITY
	for (int nSocketCount = 0; nSocketCount < MAX_SOCKET_OPTION; ++nSocketCount)
	{
		SetItemSocket(nSocketCount, 
			pItem->GetSocketJewelIndex(nSocketCount) );
	}
}

void CUIButtonEx::SetItemDurNow( int nowDur )
{
	m_nDurNow = nowDur;
#ifdef DURABILITY
	CItemData* pItemData = _pNetwork->GetItemData(m_nIndex);

	if ( !pItemData->IsFlag( ITEM_FLAG_DURABILITY))
	{
		m_bDuraZero = false;
		return;
	}

	if (nowDur / 10 <= 0)
		m_bDuraZero = true;
	else
		m_bDuraZero = false;
#endif	//	DURABILITY	
}
