#include "stdh.h"

// ��� ����. [12/1/2009 rumist]
#include <Engine/Interface/UIInternalClasses.h>
#include <vector>
#include <Engine/Interface/UIChangeWeapon.h>
#include <Engine/Entities/InternalClasses.h>
#include <algorithm>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Interface/UIHelp.h>
#include <Engine/Interface/UIMixNew.h>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Contents/Base/UIQuestBookNew.h>

extern INDEX g_iCountry;

// [KH_07044] 3�� ���� ���� �߰�
extern INDEX g_iShowHelp1Icon;

enum eSelection
{
	CHANGEWEAPON_OK,
	CHANGEWEAPON_TALK,
	CHANGEWEAPON_EVENT,
	CHANGESHIELD_OK,
	CHANGEWEAPON_MASTERSTONE
};

static int	_iMaxMsgStringChar = 0;

#define DESC_LIST_BOX_HEIGHT			(130)
#define CRITERION_LEVEL					(28)
#define WEAPON_LIST_START_X				(21)
#define WEAPON_INFO_START_X				(21)
#define WEAPON_DESC_START_X				(190)
#define WEAPON_LISTBOX_WIDTH			(193)

#define EXCHANGE_LIMIT_LEVEL			(29)

//#define CHANGE_WEAPON_EVENT_2PAN4PAN		// 2��4�� ���� ��ü �̺�Ʈ.
//#define CHANGE_WEAPON_SHIELD_EVENT			// ���� �� ��ü �̺�Ʈ

// NOTE : �������� �ϵ��ڵ� �Ǿ� �ִ� ���� ��ü ���� ������ �ε���.
// ����, �Ѽհ�, ����, ������, ���, ����, ��������, Ȱ, �ܰ�, -1, -1, -1, �̵���, �ϵ�, ���̵�, ���� : ���� : �Ҽ���
const static int matchTable[12][16] = {
	{1,48,530,600,12,558,356,50,528,-1,-1,-1,459,599,-1,-1},
	{5,53,666,628,51,601,357,56,529,-1,-1,-1,610,619,-1,-1},
	{9,55,637,629,52,602,358,57,532,-1,-1,-1,611,620,-1,-1},
	{13,107,638,630,105,603,359,106,533,-1,-1,-1,612,621,-1,-1},
	{17,180,639,631,306,604,360,185,534,-1,-1,-1,613,622,-1,-1},
	{21,322,640,632,307,605,361,341,535,-1,-1,-1,614,623,-1,-1},
	{25,323,641,633,308,606,362,342,536,-1,-1,-1,615,624,-1,-1},
	{29,324,642,634,309,607,363,343,537,-1,-1,-1,616,625,-1,-1},
	{33,325,643,635,310,608,364,344,538,-1,-1,-1,617,626,-1,-1},
	{37,326,644,636,311,609,365,345,539,-1,-1,-1,618,627,-1,-1},
	{41,681,721,719,715,645,720,718,722,-1,-1,-1,716,717,-1,-1},
	{45,800,823,816,793,794,815,808,822,-1,-1,-1,801,809,-1,-1}
};

// ----------------------------------------------------------------------------
// Name : IsChangeableWeapon()
// Desc : �ٲܼ� �ִ� ���������� üũ�մϴ�.
// ----------------------------------------------------------------------------
BOOL CUIChangeWeapon::IsChangeableWeapon( int iWeaponIndex )
{
	if( iWeaponIndex == -1 )
		return FALSE;
	// ������ ����� ���������� �ܾ�ٰ� ���� �ְ�...
	for( int i = 1; i < 12; ++i )
	{
		for( int j = 0; j < 16; ++j )
		{
			if( matchTable[i][j] == iWeaponIndex )
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

// ----------------------------------------------------------------------------
// Name : CUIChangeWeapon()
// Desc : Constructor
// ----------------------------------------------------------------------------
CUIChangeWeapon::CUIChangeWeapon()
	: m_pSelItem(NULL)
{
	m_eChangeWeaponState	= CHANGEWEAPON_REQ;
	m_nStringCount			= 0;
	m_strChangeWeaponMoney	= CTString( "" );
	m_llChangeWeaponMoney	= 0;

	m_strWeaponName			= CTString( "" );
	m_strWeaponLevel		= CTString( "" );
	m_strWeaponClass		= CTString( "" );
	m_strWeaponAttack		= CTString( "" );
	m_strWeaponDefence		= CTString( "" );
	m_strWeaponMagicAttack	= CTString( "" );
	m_strWeight				= CTString( "" );

	m_slLevel				= -1;
	m_bCashItemChk			= FALSE;
}

// ----------------------------------------------------------------------------
// Name : ~CUIChangeWeapon()
// Desc : Destructor
// ----------------------------------------------------------------------------
CUIChangeWeapon::~CUIChangeWeapon()
{
}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight )
{
	CUIWindow::Create(pParentWnd, nX, nY, nWidth, nHeight);

	_iMaxMsgStringChar = 190 / ( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() );

	// Region of each part
	m_rcTitle.SetRect( 0, 0, 216, 22 );
	m_rcItemSlot.SetRect( 97, 0, 131, 0 );
	m_rcInsertItem.SetRect( 3, 0, 213, 0 );

	// Create refine texture
	m_ptdBaseTexture = CreateTexture( CTString( "Data\\Interface\\MessageBox.tex" ) );
	FLOAT	fTexWidth	= m_ptdBaseTexture->GetPixWidth();
	FLOAT	fTexHeight	= m_ptdBaseTexture->GetPixHeight();

	// UV Coordinate of each part
	// Background
	m_rtTop.SetUV( 0, 0, 216, 26, fTexWidth, fTexHeight );
	m_rtMiddle1.SetUV( 0, 31, 216, 33, fTexWidth, fTexHeight );
	m_rtMiddle2.SetUV( 0, 35, 216, 37, fTexWidth, fTexHeight );
	m_rtMiddle3.SetUV( 36, 86, 252, 104, fTexWidth, fTexHeight );
	m_rtBottom.SetUV( 0, 38, 216, 45, fTexWidth, fTexHeight );
	m_rtItemSlot.SetUV( 0, 68, 34, 102, fTexWidth, fTexHeight );

	// Input box
	m_rtInputBoxL.SetUV( 205, 46, 209, 59, fTexWidth, fTexHeight );
	m_rtInputBoxM.SetUV( 211, 46, 213, 59, fTexWidth, fTexHeight );
	m_rtInputBoxR.SetUV( 215, 46, 219, 59, fTexWidth, fTexHeight );

	// Close button
	m_btnClose.Create( this, CTString( "" ), 184, 4, 14, 14 );
	m_btnClose.SetUV( UBS_IDLE, 219, 0, 233, 14, fTexWidth, fTexHeight );
	m_btnClose.SetUV( UBS_CLICK, 234, 0, 248, 14, fTexWidth, fTexHeight );
	m_btnClose.CopyUV( UBS_IDLE, UBS_ON );
	m_btnClose.CopyUV( UBS_IDLE, UBS_DISABLE );

	// OK button
	m_btnOK.Create( this, _S( 191, "Ȯ��" ), 78, 371, 63, 21 );
	m_btnOK.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnOK.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnOK.CopyUV( UBS_IDLE, UBS_ON );
	m_btnOK.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Cancel button
	m_btnCancel.Create( this, _S( 139, "���" ), 146, 371, 63, 21 );
	m_btnCancel.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnCancel.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnCancel.CopyUV( UBS_IDLE, UBS_ON );
	m_btnCancel.CopyUV( UBS_IDLE, UBS_DISABLE );

	// List box of guild description
	m_lbWeaponDesc.Create( this, 8, 263, WEAPON_LISTBOX_WIDTH, 101, _pUIFontTexMgr->GetLineHeight(), 13, 3, 1, FALSE );
	m_lbWeaponDesc.CreateScroll( TRUE, 0, 0, 9, 101, 9, 7, 0, 0, 10 );
	m_lbWeaponDesc.SetSelBar( 190, _pUIFontTexMgr->GetLineHeight(), 187, 46, 204, 61, fTexWidth, fTexHeight );
	// Up button
	m_lbWeaponDesc.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbWeaponDesc.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbWeaponDesc.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbWeaponDesc.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbWeaponDesc.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbWeaponDesc.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbWeaponDesc.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbWeaponDesc.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbWeaponDesc.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbWeaponDesc.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbWeaponDesc.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );

	// List box of guild description
	m_lbWeaponList.Create( this, 8, 158, WEAPON_LISTBOX_WIDTH, 101, _pUIFontTexMgr->GetLineHeight(), 13, 3, 1, TRUE );
	m_lbWeaponList.CreateScroll( TRUE, 0, 0, 9, 101, 9, 7, 0, 0, 10 );
	m_lbWeaponList.SetSelBar( WEAPON_LISTBOX_WIDTH, _pUIFontTexMgr->GetLineHeight(), 187, 46, 204, 61, fTexWidth, fTexHeight );
	m_lbWeaponList.SetOverColor( 0xF8E1B5FF );
	m_lbWeaponList.SetSelectColor( 0xF8E1B5FF );	
	// Up button
	m_lbWeaponList.SetScrollUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_lbWeaponList.SetScrollUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_lbWeaponList.CopyScrollUpUV( UBS_IDLE, UBS_ON );
	m_lbWeaponList.CopyScrollUpUV( UBS_IDLE, UBS_DISABLE );
	// Down button
	m_lbWeaponList.SetScrollDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_lbWeaponList.SetScrollDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_lbWeaponList.CopyScrollDownUV( UBS_IDLE, UBS_ON );
	m_lbWeaponList.CopyScrollDownUV( UBS_IDLE, UBS_DISABLE );
	// Bar button
	m_lbWeaponList.SetScrollBarTopUV( 219, 16, 228, 26, fTexWidth, fTexHeight );
	m_lbWeaponList.SetScrollBarMiddleUV( 219, 27, 228, 29, fTexWidth, fTexHeight );
	m_lbWeaponList.SetScrollBarBottomUV( 219, 30, 228, 40, fTexWidth, fTexHeight );	

	m_rcItemSlot.Top		= 51;
	m_rcItemSlot.Bottom		= m_rcItemSlot.Top + 34;

	m_rcInsertItem.Top		= 33;
	m_rcInsertItem.Bottom	= m_rcItemSlot.Bottom + 33;

	// Slot item button
	m_btnSlotItem.Create( this, m_rcItemSlot.Left + 1, m_rcItemSlot.Top + 1, BTN_SIZE, BTN_SIZE, UI_CHANGEWEAPON, UBET_ITEM );
/*
	AddWeaponInfo( CItemData::ITEM_WEAPON_KNIFE,	_S( 1038, "��絵" ),	TITAN );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_CROSSBOW, _S( 1039, "����" ),		ROGUE );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_STAFF,	_S( 1040, "������" ),	MAGE );			
	AddWeaponInfo( CItemData::ITEM_WEAPON_BIGSWORD, _S( 1041, "���" ),		TITAN );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_AXE,		_S( 1042, "����" ),		TITAN );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_SSTAFF,	_S( 1043, "��������" ), MAGE );			
	AddWeaponInfo( CItemData::ITEM_WEAPON_BOW,		_S( 1044, "Ȱ" ),		HEALER );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_DAGGER,	_S( 1045, "�ܰ�" ),		ROGUE );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_TWOSWORD, _S( 1046, "�̵���" ),	KNIGHT );	
	AddWeaponInfo( CItemData::ITEM_WEAPON_WAND,		_S( 1047, "�����ϵ�" ),		HEALER );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_SCYTHE,	_S( 2306,"���̵�" ),		SORCERER );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_POLEARM,		_S(2307, "����" ),		SORCERER );		

	RefreshWeaponList();
	*/
}

// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

// ----------------------------------------------------------------------------
// Name : OpenChangeWeapon()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::OpenChangeWeapon(int iMobIndex, BOOL bHasQuest, FLOAT fX, FLOAT fZ )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( pUIManager->GetInventory()->IsLocked() == TRUE ||
		pUIManager->GetInventory()->IsLockedArrange() == TRUE)
	{
		pUIManager->GetInventory()->ShowLockErrorMessage();
		return;
	}

	// If this is already exist
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_CHANGEWEAPON_REQ ) || IsVisible() )
		return;

	// ���� ĳ���������� üũ��!!!
	// ���� ĳ���Ͱ� �ƴ϶�� return;
	//pUIManager->GetChatting()->AddSysMessage( _S( 1048, "���� ĳ���͸� ���� ��ü�� �� �� �ֽ��ϴ�." ), SYSMSG_ERROR );		

	pUIManager->CloseMessageBox( MSGCMD_CHANGEWEAPON_REP );
	pUIManager->CloseMessageBox( MSGCMD_CHANGEWEAPON_NOTIFY );

	// Set position of target npc
	m_fNpcX = fX;
	m_fNpcZ = fZ;

	CMobData* MD = CMobData::getData(iMobIndex);

	CTString strMessage;	

#ifdef	MASTERSTONE
	if(iMobIndex == 1261)		// ��æƮ ������ �Ҹ� ; ������ �����
	{
		pUIManager->CreateMessageBoxL( _S(5435, "������ �������� ���׷��̵��ϱ�" ), UI_CHANGEWEAPON, MSGLCMD_CHANGEWEAPON_REQ );		

		CTString	strNpcName = CMobData::getData(iMobIndex)->GetName();
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, strNpcName, -1, 0xE18600FF );

		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(5443,"�Ϲ����� �������� ���׷��̵��ϴ� ���� �Ѱ谡 �ֽ��ϴ�. ���� �� �Ѱ踦 �پ� �Ѵ� ���׷��̵��ϴ� ����� �˰� ������ ���� ���� ���׷��̵� �Ѱ� ��ġ �̻� +26���� ���׷��̵� �� �� �ֽ��ϴ�."), -1, 0xA3A1A3FF );
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(5444,"�� ����� ������ �����Դϴ�. ������ ������ ũ�� ���⸶���� ����� ��� �� ������ ���� 2������ ������ ���� ������ ������ ��޺��� 6�ܰ谡 �����մϴ�."), -1, 0xA3A1A3FF );
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(5445,"(0~16, 0~18, 0~20, 0~22, 0~24, 0~25) ��� �� ������ ������ ��� ���� ��� �����մϴ�. �����ϴ� ���׷��̵�� ���� ���� 100%������ �ڶ��մϴ�."), -1, 0xA3A1A3FF );

		strMessage= _S(5435, "������ �������� ���׷��̵� �ϱ�" );			
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage, CHANGEWEAPON_MASTERSTONE );	

		strMessage.PrintF( _S( 1220, "����Ѵ�." ) );
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage );	

		return;
	}
#endif

	// Create refine message box
	pUIManager->CreateMessageBoxL( _S(2308, "����� �� ��ü" ), UI_CHANGEWEAPON, MSGLCMD_CHANGEWEAPON_REQ );		

	CTString	strNpcName = CMobData::getData(iMobIndex)->GetName();
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, strNpcName, -1, 0xE18600FF );

#ifndef CHANGE_WEAPON_EVENT_2PAN4PAN		// 2��4�� ���� ��ü �̺�Ʈ.
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S( 1050, "���� ����ϰ� �ִ� ���⳪ ���� ������ ���� �ʴ°հ�?" ), -1, 0xA3A1A3FF );		
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S( 1051, "�׷� ���� �ڳ׸� ������ �� �ְڱ���." ), -1, 0xA3A1A3FF );
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2309,"������ �����ؾ��� ������ �ֳ�"), -1, 0xA3A1A3FF );			
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2310,"��ü�Ǵ� ���� ���õ� ��ġ�� ���� ������ �ɼǰ��� �����Ǵϱ� �� ������ ���ð� ��ü�Գ�."), -1, 0xF3BA0CFF );
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2311,"�׷��� �̷��� ���� ���ο� ��� ���� �� �ִ� ���� ��� �ְڳ�..."), -1, 0xA3A1A3FF );
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2312,"�� ���� ��ȯ�ϰԳ�...  ������� �� ������ ����..."), -1, 0xA3A1A3FF );
#else
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2152,"��ŵ� ���� ��ü�� �Ϸ� ���� �� ����?"), -1, 0xA3A1A3FF );			
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2153,"����ϴ� ���⸦ ����� �ٸ� ������ ����� �ٲ� �شٴ� �ҹ��� ��� ������ �������� �������� ������� �����ͼ� ������ ���׿�."), -1, 0xA3A1A3FF );			
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2154,"������ �����ؾ��� ������ �־��!"), -1, 0xA3A1A3FF );			
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2155,"��ü�Ǵ� ����� ���õ� ��ġ�� ���� ������ �ɼǰ��� �����Ǵϱ� �� ������ ���ð� ��ü�ϼ���."), -1, 0xF3BA0CFF );
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2156,"�׷��� �̷��� ���� ���ο� ���⸦ ���� �� �ִ� ���� ��� �ְھ��..."), -1, 0xA3A1A3FF );
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, TRUE, _S(2157,"�� ���� ��ȯ�ϼ���.  ������� �� ������ ������..."), -1, 0xA3A1A3FF );
#endif

	strMessage.PrintF( _S( 1049, "���� ��ü" ) );			
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage, CHANGEWEAPON_OK );	
	
	// wooss add shield item exchange
	strMessage= _S(2313, "�� ��ü" );			
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage, CHANGESHIELD_OK );	

	if( bHasQuest )
	{
		// 2009. 05. 27 ������
		// �̾߱��Ѵ� ���� ó��
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_CHANGEWEAPON_REQ);				
	}
	
	if( MD->IsEvent() )
	{
		strMessage.PrintF( _S( 100, "�̺�Ʈ." ) );			
		pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage, CHANGEWEAPON_EVENT );
	}

	strMessage.PrintF( _S( 1220, "����Ѵ�." ) );
	pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_REQ, FALSE, strMessage );	

}

// ----------------------------------------------------------------------------
// Name : CloseChangeWeapon()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::CloseChangeWeapon()
{
	// Reset slot item
	m_btnSlotItem.InitBtn();

	// Reset ListBox
	m_lbWeaponDesc.ResetAllStrings();
	m_lbWeaponList.ResetAllStrings();

	m_strWeaponName.Clear();
	m_strWeaponLevel.Clear();
	m_strWeaponClass.Clear();
	m_strWeaponAttack.Clear();
	m_strWeaponDefence.Clear();
	m_strWeaponMagicAttack.Clear();
	m_strWeight.Clear();
	m_slLevel				= -1;

	CUIManager* pUIManager = CUIManager::getSingleton();

	// Close refine
	pUIManager->RearrangeOrder( UI_CHANGEWEAPON, FALSE );

	pUIManager->GetInventory()->Lock( FALSE, FALSE, LOCK_CHANGEWEAPON );

	m_strChangeWeaponMoney.Clear();

	//wooss 051011
	if(m_bCashItemChk) m_bCashItemChk = FALSE;
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::Render()
{
	// Check distance
	FLOAT	fDiffX = _pNetwork->MyCharacterInfo.x - m_fNpcX;
	FLOAT	fDiffZ = _pNetwork->MyCharacterInfo.z - m_fNpcZ;
	// cash item check wooss 051011
	if( m_bCashItemChk == FALSE )
	{
		if( fDiffX * fDiffX + fDiffZ * fDiffZ > UI_VALID_SQRDIST )
		{
			CloseChangeWeapon();
		}
	}

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Set refine texture
	pDrawPort->InitTextureData( m_ptdBaseTexture );

	// Add render regions
	int	nX, nY, nX2, nY2;
	
	// Background
	// Top
	nX = m_nPosX + m_nWidth;
	nY = m_nPosY + 26;
	pDrawPort->AddTexture( m_nPosX, m_nPosY, nX, nY,
		m_rtTop.U0, m_rtTop.V0,
		m_rtTop.U1, m_rtTop.V1,
		0xFFFFFFFF );
	
	pDrawPort->AddTexture( m_nPosX, nY, nX, nY + 103,
		m_rtMiddle1.U0, m_rtMiddle1.V0,
		m_rtMiddle1.U1, m_rtMiddle1.V1,
		0xFFFFFFFF );

	nY += 103;
	
	pDrawPort->AddTexture( m_nPosX, nY, nX, nY + 11,
		m_rtMiddle2.U0, m_rtMiddle2.V0,
		m_rtMiddle2.U1, m_rtMiddle2.V1,
		0xFFFFFFFF );

	nY += 11;

	pDrawPort->AddTexture( m_nPosX, nY, nX, nY + 18,
		m_rtMiddle3.U0, m_rtMiddle3.V0,
		m_rtMiddle3.U1, m_rtMiddle3.V1,
		0xFFFFFFFF );

	nY += 18;

	pDrawPort->AddTexture( m_nPosX, nY, nX, nY + 101,
		m_rtMiddle1.U0, m_rtMiddle1.V0,
		m_rtMiddle1.U1, m_rtMiddle1.V1,
		0xFFFFFFFF );

	nY += 101;

	pDrawPort->AddTexture( m_nPosX, nY, nX, nY + 4,
		m_rtMiddle2.U0, m_rtMiddle2.V0,
		m_rtMiddle2.U1, m_rtMiddle2.V1,
		0xFFFFFFFF );
	
	nY += 4;
	
	pDrawPort->AddTexture( m_nPosX, nY, nX, nY + 101,
		m_rtMiddle1.U0, m_rtMiddle1.V0,
		m_rtMiddle1.U1, m_rtMiddle1.V1,
		0xFFFFFFFF );

	nY += 101;

	pDrawPort->AddTexture( m_nPosX, nY, nX, m_nPosY + m_nHeight - 7,
		m_rtMiddle2.U0, m_rtMiddle2.V0,
		m_rtMiddle2.U1, m_rtMiddle2.V1,
		0xFFFFFFFF );
	
	// Bottom
	nY = m_nPosY + m_nHeight - 7;
	pDrawPort->AddTexture( m_nPosX, nY, nX, m_nPosY + m_nHeight,
		m_rtBottom.U0, m_rtBottom.V0,
		m_rtBottom.U1, m_rtBottom.V1,
		0xFFFFFFFF );

	// Slot item region
	pDrawPort->AddTexture( m_nPosX + m_rcItemSlot.Left, m_nPosY + m_rcItemSlot.Top,
										m_nPosX + m_rcItemSlot.Right, m_nPosY + m_rcItemSlot.Bottom,
										m_rtItemSlot.U0, m_rtItemSlot.V0, m_rtItemSlot.U1, m_rtItemSlot.V1,
										0xFFFFFFFF );

	nX	= m_nPosX + 95;
	nX2	= nX + 84;
	nY	= m_nPosY + 102;
	nY2 = nY + 13;

	if(!m_bCashItemChk){
	// Point    �ݾ� �ڽ� wooss 051011
	pDrawPort->AddTexture( nX, nY, nX + 4, nY2,
		m_rtInputBoxL.U0, m_rtInputBoxL.V0, m_rtInputBoxL.U1, m_rtInputBoxL.V1,
		0xFFFFFFFF );
	//Lower middle
		pDrawPort->AddTexture( nX + 4, nY, nX2 - 4, nY2,
			m_rtInputBoxM.U0, m_rtInputBoxM.V0, m_rtInputBoxM.U1, m_rtInputBoxM.V1,
			0xFFFFFFFF );
	// Lower right
	pDrawPort->AddTexture( nX2 - 4, nY, nX2, nY2,
		m_rtInputBoxR.U0, m_rtInputBoxR.V0, m_rtInputBoxR.U1, m_rtInputBoxR.V1,
		0xFFFFFFFF );
	}
	// Close button
	m_btnClose.Render();

	// OK button
	m_btnOK.Render();

	// Cancel button
	m_btnCancel.Render();

	// List Box
	m_lbWeaponDesc.Render();
	m_lbWeaponList.Render();

	// Render all elements
	pDrawPort->FlushRenderingQueue();

	// Item
	if( !m_btnSlotItem.IsEmpty() )
	{
		m_btnSlotItem.Render();
		pDrawPort->FlushBtnRenderingQueue( UBET_ITEM );
	}

	if( m_eChangeWeaponState == CHANGEWEAPON_STAT ){
	
		// Text in refine
		pDrawPort->PutTextEx( _S( 1049, "���� ��ü"  ), m_nPosX + CHANGEWEAPON_TITLE_TEXT_OFFSETX,		
											m_nPosY + CHANGEWEAPON_TITLE_TEXT_OFFSETY, 0xFFFFFFFF );

		pDrawPort->PutTextEx( _S( 1057, "��ü����" ), m_nPosX + 40,		
											m_nPosY + 60, 0xFFFFFFFF );

		// cash item check wooss 051011
		if(!m_bCashItemChk) {
			nY = m_nPosY + 104;
			pDrawPort->PutTextEx( _S( 1058, "�ʿ䳪��" ), m_nPosX + 40,		
										nY, 0xFFFFFFFF );
			// ChangeWeaponing money
#ifdef CHANGE_WEAPON_SHIELD_EVENT	
			pDrawPort->PutTextEx( _S(2315," ��ü �̺�Ʈ"),	m_nPosX + 95, m_nPosY + 102, 0xE1B300FF );	
#else
			pDrawPort->PutTextEx( m_strChangeWeaponMoney,	m_nPosX + 95, m_nPosY + 102, 0xE1B300FF );				
#endif 

		}
		
		nY = m_nPosY + 143;
		pDrawPort->PutTextEx( _S( 1059, "���� ����Ʈ" ), m_nPosX + 12,		
											nY, 0xE18600FF );

		nY = m_nPosY + 269;
		pDrawPort->PutTextEx( _S( 1065, "���� �̸�" ), m_nPosX + WEAPON_INFO_START_X,		
											nY, 0xFFFFFFFF );

		pDrawPort->PutTextExRX( m_strWeaponName, m_nPosX + WEAPON_DESC_START_X,		
											nY, 0xFFd223FF );

		nY += 15;
		pDrawPort->PutTextEx( _S( 1066, "���� ����" ), m_nPosX + WEAPON_INFO_START_X,		
											nY, 0xFFFFFFFF );

		pDrawPort->PutTextExRX( m_strWeaponLevel, m_nPosX + WEAPON_DESC_START_X,		
											nY, 0xFFd223FF );

		nY += 15;
		pDrawPort->PutTextEx( _S( 1067, "��� Ŭ����" ), m_nPosX + WEAPON_INFO_START_X,		
											nY, 0xFFFFFFFF );

		pDrawPort->PutTextExRX( m_strWeaponClass, m_nPosX + WEAPON_DESC_START_X,		
											nY, 0xFFd223FF );

		nY += 15;
		pDrawPort->PutTextEx( _S( 1068, "���ݷ�" ), m_nPosX + WEAPON_INFO_START_X,		
											nY, 0xFFFFFFFF );

		pDrawPort->PutTextExRX( m_strWeaponAttack, m_nPosX + WEAPON_DESC_START_X,		
											nY, 0xFFd223FF );

		nY += 15;
		pDrawPort->PutTextEx( _S( 1069, "���� ���ݷ�" ), m_nPosX + WEAPON_INFO_START_X,		
											nY, 0xFFFFFFFF );

		pDrawPort->PutTextExRX( m_strWeaponMagicAttack, m_nPosX + WEAPON_DESC_START_X,		
											nY, 0xFFd223FF );

		
	}
	else if( m_eChangeWeaponState == CHANGEWEAPON_SHIELD){
		// Text in refine
		pDrawPort->PutTextEx( _S( 2313,"�� ��ü"  ), m_nPosX + CHANGEWEAPON_TITLE_TEXT_OFFSETX,		
											m_nPosY + CHANGEWEAPON_TITLE_TEXT_OFFSETY, 0xFFFFFFFF );

		pDrawPort->PutTextEx( _S( 2314,"��ü ��" ), m_nPosX + 30,		
											m_nPosY + 60, 0xFFFFFFFF );

		// cash item check wooss 051011
		if(!m_bCashItemChk) {
			nY = m_nPosY + 104;
			pDrawPort->PutTextEx( _S( 1058, "�ʿ䳪��" ), m_nPosX + 40,		
										nY, 0xFFFFFFFF );
#ifdef CHANGE_WEAPON_SHIELD_EVENT	
			pDrawPort->PutTextEx( _S(2315," ��ü �̺�Ʈ"), m_nPosX + 95, m_nPosY + 102, 0xE1B300FF );	
#else
			pDrawPort->PutTextEx( m_strChangeWeaponMoney,	m_nPosX + 95, m_nPosY + 102, 0xE1B300FF );				
#endif 
		}
		
		nY = m_nPosY + 143;
		pDrawPort->PutTextEx( _S(2316, "Ŭ���� ����Ʈ" ), m_nPosX + 12,		
											nY, 0xE18600FF );

		nY = m_nPosY + 269;
		pDrawPort->PutTextEx( _S(2317, "�� �̸�" ), m_nPosX + WEAPON_INFO_START_X,		
											nY, 0xFFFFFFFF );

		pDrawPort->PutTextExRX( m_strWeaponName, m_nPosX + WEAPON_DESC_START_X,		
											nY, 0xFFd223FF );

		nY += 15;
		pDrawPort->PutTextEx( _S(2318, "�� ����" ), m_nPosX + WEAPON_INFO_START_X,		
											nY, 0xFFFFFFFF );

		pDrawPort->PutTextExRX( m_strWeaponLevel, m_nPosX + WEAPON_DESC_START_X,		
											nY, 0xFFd223FF );

		nY += 15;
		pDrawPort->PutTextEx( _S( 1067, "��� Ŭ����" ), m_nPosX + WEAPON_INFO_START_X,		
											nY, 0xFFFFFFFF );

		pDrawPort->PutTextExRX( m_strWeaponClass, m_nPosX + WEAPON_DESC_START_X,		
											nY, 0xFFd223FF );

		nY += 15;
		pDrawPort->PutTextEx( _S(87, "����" ), m_nPosX + WEAPON_INFO_START_X,		
											nY, 0xFFFFFFFF );

		pDrawPort->PutTextExRX( m_strWeaponDefence, m_nPosX + WEAPON_DESC_START_X,		
											nY, 0xFFd223FF );

	

	}

	// Flush all render text queue
	pDrawPort->EndTextEx();
}

// ----------------------------------------------------------------------------
// Name : MouseMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT CUIChangeWeapon::MouseMessage( MSG *pMsg )
{
	WMSG_RESULT	wmsgResult;

	// Title bar
	static BOOL bTitleBarClick = FALSE;

	// Mouse point
	static int	nOldX, nOldY;
	int	nX = LOWORD( pMsg->lParam );
	int	nY = HIWORD( pMsg->lParam );

	// Mouse message
	switch( pMsg->message )
	{
	case WM_MOUSEMOVE:
		{
			if( IsInside( nX, nY ) )
				CUIManager::getSingleton()->SetMouseCursorInsideUIs();

			// Move refine
			if( bTitleBarClick && ( pMsg->wParam & MK_LBUTTON ) )
			{
				int	ndX = nX - nOldX;
				int	ndY = nY - nOldY;
				nOldX = nX;	nOldY = nY;

				Move( ndX, ndY );

				return WMSG_SUCCESS;
			}
			// Close button
			else if( m_btnClose.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			// OK button
			else if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			// Cancel button
			else if( m_btnCancel.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			// List box
			else if( m_lbWeaponList.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_lbWeaponDesc.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
		}
		break;

	case WM_LBUTTONDOWN:
		{
			if( IsInside( nX, nY ) )
			{
				nOldX = nX;		nOldY = nY;

				// Close button
				if( m_btnClose.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				// Title bar
				else if( IsInsideRect( nX, nY, m_rcTitle ) )
				{
					bTitleBarClick = TRUE;
				}
				// OK button
				else if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				// Cancel button
				else if( m_btnCancel.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				// List box
				else if( m_lbWeaponList.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					int	iSelWeapon = m_lbWeaponList.GetCurSel();
					if( iSelWeapon != -1 && !m_btnSlotItem.IsEmpty() && m_slLevel > 0 )
					{
						sWeaponInfo &TempMember = m_vectorWeaponInfo[iSelWeapon];

						if( m_eChangeWeaponState == CHANGEWEAPON_STAT )
						{
							m_llChangeWeaponMoney = CalculateNeedNas( m_slLevel );
							m_strChangeWeaponMoney.PrintF( "%I64d", m_llChangeWeaponMoney );
						
							// FIXME : �� �Լ��� ȣ���ϱ� ����, �������� �����ߴ������� Ȯ��.
							// ������ ������ ����ϴ�.
							GetWeaponInfo( TempMember.iJob, m_slLevel, TempMember.iIndex );
						}
						else if( m_eChangeWeaponState == CHANGEWEAPON_SHIELD )
						{
							m_llChangeWeaponMoney = CalculateNeedNasS( m_slLevel );
							m_strChangeWeaponMoney.PrintF( "%I64d", m_llChangeWeaponMoney );
						
							// FIXME : �� �Լ��� ȣ���ϱ� ����, �������� �����ߴ������� Ȯ��.
							// ������ ������ ����ϴ�.
							
							// ����Ʈ�ε��� �������� ��ȯ ǰ���� �ƴϴ�. ���� 6���ǿ� ����Ʈ�ε��찡 �����ֱ� ������ ����ó��.
							if (iSelWeapon >= 6)
								++iSelWeapon;

							if (m_pSelItem->ItemData != NULL)
								GetShieldInfo( iSelWeapon, m_slLevel, m_pSelItem->ItemData->GetSubType());
						}
						
					}
					return WMSG_SUCCESS;
				}
				else if( m_lbWeaponDesc.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;

				CUIManager::getSingleton()->RearrangeOrder( UI_CHANGEWEAPON, TRUE );
				return WMSG_SUCCESS;
			}
		}
		break;

	case WM_LBUTTONUP:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();

			// If holding button doesn't exist
			if( pUIManager->GetHoldBtn().IsEmpty() )
			{
				// Title bar
				bTitleBarClick = FALSE;

				// If refine isn't focused
				if( !IsFocused() )
					return WMSG_FAIL;

				// Close button
				if( ( wmsgResult = m_btnClose.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
						CloseChangeWeapon();

					return WMSG_SUCCESS;
				}
				// OK button
				else if( ( wmsgResult = m_btnOK.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						SendChangeWeaponReq();				
					}

					return WMSG_SUCCESS;
				}
				// Cancel button
				else if( ( wmsgResult = m_btnCancel.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
						CloseChangeWeapon();

					return WMSG_SUCCESS;
				}
				// List box
				else if( ( wmsgResult = m_lbWeaponList.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
					}
					return WMSG_SUCCESS;
				}
				else if( m_lbWeaponDesc.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;
			}
			// If holding button exists
			else
			{
				if( IsInside( nX, nY ) )
				{
					// If holding button is item and comes from inventory
					if( pUIManager->GetHoldBtn().GetBtnType() == UBET_ITEM &&
						pUIManager->GetHoldBtn().GetWhichUI() == UI_INVENTORY )
					{
						if( IsInsideRect( nX, nY, m_rcInsertItem ) )
						{
							// Set refine item
							if(m_eChangeWeaponState == CHANGEWEAPON_STAT)
								SetChangeWeaponItem();
							else if(m_eChangeWeaponState == CHANGEWEAPON_SHIELD)
								SetChangeShieldItem();
						}
					}

					// Reset holding button
					pUIManager->ResetHoldBtn();

					return WMSG_SUCCESS;
				}
			}
		}
		break;

	case WM_LBUTTONDBLCLK:
		{
			if( IsInside( nX, nY ) )
				return WMSG_SUCCESS;
		}
		break;
		
	case WM_MOUSEWHEEL:
		{
			if( IsInside( nX, nY ) )
			{
				// List box
				if( m_lbWeaponList.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;
				else if( m_lbWeaponDesc.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;
			}
		}
		break;
	}

	return WMSG_FAIL;
}

// ========================================================================= //
//                             Command functions                             //
// ========================================================================= //

// ----------------------------------------------------------------------------
// Name : SetChangeShieldItem()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::SetChangeShieldItem()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// If this is wearing item
	if( pUIManager->GetHoldBtn().GetItemWearType() >= 0 )
	{
		pUIManager->GetChatting()->AddSysMessage( _S( 1071, "����� �������� ��ü�� �� �����ϴ�." ), SYSMSG_ERROR );		
		return;
	}

	// If this is not weapon or armor
	int	nTab = pUIManager->GetHoldBtn().GetItemTab();
	int	nIdx = pUIManager->GetHoldBtn().GetInvenIndex();
	// wooss : add shield item exchange
	m_pSelItem = &_pNetwork->MySlotItem[nTab][nIdx];
	CItemData*	pItemData = m_pSelItem->ItemData;
	
	if( pItemData->GetType() != CItemData::ITEM_SHIELD )	{
		pUIManager->GetChatting()->AddSysMessage( _S(2320, "���� ��ü �� �� �ֽ��ϴ�." ), SYSMSG_ERROR );		
		return;
	}

#ifndef CHANGE_WEAPON_EVENT_2PAN4PAN		// 2��4�� ���� ��ü �̺�Ʈ.
	if( pItemData->GetLevel() < 29 || pItemData->GetLevel() >72)
	{
		pUIManager->GetChatting()->AddSysMessage( _S( 1073, "��ü�� �� �ִ� ������ ������ �ƴմϴ�." ), SYSMSG_ERROR );		
		return;
	}
#if defined SOCKET_CHANGEWEAPON_ENABLE
	if( (m_pSelItem->GetSocketCount() > 0) )
	{
		pUIManager->GetChatting()->AddSysMessage( _S(2158,"��ü�� �� ���� �������Դϴ�."), SYSMSG_ERROR );
		return;
	}
#endif
#else

	// ��ȯ ������ ������ ������� Ȯ���մϴ�.
	if( !IsChangeableWeapon( rItems.Item_Index )
#if defined SOCKET_CHANGEWEAPON_ENABLE
		|| (m_pSelItem->GetSocketCount() > 0) 
#endif
		)
	{
		pUIManager->GetChatting()->AddSysMessage( _S(2158,"��ü�� �� ���� �������Դϴ�."), SYSMSG_ERROR );
		return;
	}
#endif

	// If refining money is short
	m_slLevel = pItemData->GetLevel();

	// Insert upgrade slot
	m_btnSlotItem.Copy( pUIManager->GetHoldBtn() );
	
	m_llChangeWeaponMoney = CalculateNeedNasS( m_slLevel );
	m_strChangeWeaponMoney.PrintF( "%I64d", m_llChangeWeaponMoney );

	// Lock inventory
	//pUIManager->GetInventory()->Lock( TRUE, FALSE, LOCK_CHANGEWEAPON );
	int	iSelWeapon = m_lbWeaponList.GetCurSel();
	
	if (iSelWeapon >= 0)
	{
		sWeaponInfo &TempMember = m_vectorWeaponInfo[iSelWeapon];

		// FIXME : �� �Լ��� ȣ���ϱ� ����, �������� �����ߴ������� Ȯ��.
		// ������ ������ ����ϴ�.
		GetShieldInfo( _pNetwork->MyCharacterInfo.job, m_slLevel, m_pSelItem->ItemData->GetSubType());
	}

	// Lock inventory
	pUIManager->GetInventory()->Lock( TRUE, TRUE, LOCK_CHANGEWEAPON );
}

// ----------------------------------------------------------------------------
// Name : SetChangeWeaponItem()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::SetChangeWeaponItem()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// If this is wearing item
	if( pUIManager->GetHoldBtn().GetItemWearType() >= 0 )
	{
		pUIManager->GetChatting()->AddSysMessage( _S( 1071, "����� �������� ��ü�� �� �����ϴ�." ), SYSMSG_ERROR );		
		return;
	}

	// If this is not weapon or armor
	int	nTab = pUIManager->GetHoldBtn().GetItemTab();
	int	nIdx = pUIManager->GetHoldBtn().GetInvenIndex();
	// wooss : add shield item exchange

	m_pSelItem = &_pNetwork->MySlotItem[nTab][nIdx];
	CItemData*	pItemData = m_pSelItem->ItemData;
	if( pItemData->GetType() != CItemData::ITEM_WEAPON )
	{
		pUIManager->GetChatting()->AddSysMessage( _S( 1072, "���⸸ ��ü �� �� �ֽ��ϴ�." ), SYSMSG_ERROR );		
		return;
	}

	// 060810 wooss
	// �߰��� ��ȯ �Ұ� ������
	// 1. �÷�Ƽ�� ���ü� ���� ������ 2. �ռ��� ������
	if(		m_pSelItem->IsFlag(PLATINUM_MAX_PLUS) 
		||	m_pSelItem->IsFlag(FLAG_ITEM_COMPOSITION)
#if defined SOCKET_CHANGEWEAPON_ENABLE
		||	(m_pSelItem->GetSocketCount() > 0) 
#endif
		)

	{
		pUIManager->GetChatting()->AddSysMessage( _S(2158,"��ü�� �� ���� �������Դϴ�."), SYSMSG_ERROR );
		return;
	}

#ifndef CHANGE_WEAPON_EVENT_2PAN4PAN		// 2��4�� ���� ��ü �̺�Ʈ.
	if( pItemData->GetLevel() < 29 || pItemData->GetLevel() >69)
	{
		pUIManager->GetChatting()->AddSysMessage( _S( 1073, "��ü�� �� �ִ� ������ ������ �ƴմϴ�." ), SYSMSG_ERROR );		
		return;
	}
#else

	// ��ȯ ������ ������ ������� Ȯ���մϴ�.
	if( !IsChangeableWeapon( rItems.Item_Index ) )
	{
		pUIManager->GetChatting()->AddSysMessage( _S(2158,"��ü�� �� ���� �������Դϴ�."), SYSMSG_ERROR );
		return;
	}
#endif

	// If refining money is short
	m_slLevel = pItemData->GetLevel();


	// Insert upgrade slot
	m_btnSlotItem.Copy( pUIManager->GetHoldBtn() );

	m_llChangeWeaponMoney = CalculateNeedNas( m_slLevel );
	m_strChangeWeaponMoney.PrintF( "%I64d", m_llChangeWeaponMoney );



	// Lock inventory
	//pUIManager->GetInventory()->Lock( TRUE, FALSE, LOCK_CHANGEWEAPON );
	int	iSelWeapon = m_lbWeaponList.GetCurSel();
	
	if (iSelWeapon >= 0)
	{
		sWeaponInfo &TempMember = m_vectorWeaponInfo[iSelWeapon];

		// FIXME : �� �Լ��� ȣ���ϱ� ����, �������� �����ߴ������� Ȯ��.
		// ������ ������ ����ϴ�.
		GetWeaponInfo( _pNetwork->MyCharacterInfo.job, m_slLevel,  TempMember.iIndex );
	}

	// Lock inventory
	pUIManager->GetInventory()->Lock( TRUE, TRUE, LOCK_CHANGEWEAPON );
}

// ----------------------------------------------------------------------------
// Name : MsgBoxCommand()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput )
{
	switch( nCommandCode )
	{
	case MSGCMD_CHANGEWEAPON_REP:		// ���� ��ü Ȯ��.
		{
			if( bOK )
			{
				int	iSelWeapon = m_lbWeaponList.GetCurSel();
				if( iSelWeapon != -1 )
				{
					SWORD nTab		= m_btnSlotItem.GetItemTab();
					SWORD nIdx		= m_btnSlotItem.GetInvenIndex();
					int iUniIndex	= m_btnSlotItem.GetItemUniIndex();
					// ���������� �޼��� ������.
					sWeaponInfo &TempMember = m_vectorWeaponInfo[iSelWeapon];

					int nCheckIdx = _pNetwork->MySlotItem[nTab][nIdx].Item_UniIndex;

					if (iUniIndex != nCheckIdx)
					{
						m_btnSlotItem.InitBtn();
						break;
					}
					
#ifndef CHANGE_WEAPON_EVENT_2PAN4PAN		// 2��4�� ���� ��ü �̺�Ʈ.
					if(m_bCashItemChk)
						_pNetwork->UseChangeWeaponItem( nTab, nIdx, iUniIndex, TempMember.iIndex );
					else
					{
						if(m_eChangeWeaponState == CHANGEWEAPON_STAT)
							_pNetwork->ChangeWeaponReq( nTab, nIdx, iUniIndex, TempMember.iIndex );
						else if(m_eChangeWeaponState == CHANGEWEAPON_SHIELD)
						{
							// ����Ʈ�ε��� �������� ��ȯ ǰ���� �ƴϴ�. ���� 6���ǿ� ����Ʈ�ε��찡 �����ֱ� ������ ����ó��.
							if (iSelWeapon >= 6)
								++iSelWeapon;

							_pNetwork->ChangeWeaponReq( nTab, nIdx, iUniIndex, iSelWeapon);
						}
					}
							
#else				
			//		if(m_bCashItemChk) _pNetwork->ChangeWeaponReq( sbRow, sbCol, iUniIndex, TempMember.iIndex );  else //wooss 051011
					_pNetwork->ChangeWeaponEventReq( iUniIndex, TempMember.iIndex );
#endif
				}
			}
		}
		break;
	case MSGCMD_CHANGEWEAPON_NOTIFY:
		{
		}
		break;
	}
}

// ----------------------------------------------------------------------------
// Name : MsgBoxCommand()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::MsgBoxLCommand( int nCommandCode, int nResult )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	switch( nCommandCode )
	{
	case MSGLCMD_CHANGEWEAPON_REQ:
		if( nResult == CHANGEWEAPON_OK )
		{
			m_vectorWeaponInfo.clear();		
			AddWeaponInfo( CItemData::ITEM_WEAPON_KNIFE,	_S( 1038, "��絵" ),	KNIGHT ); // [2012/05/18 : Sora]  ITS 9075 TITAN -> KNIGHT	
			AddWeaponInfo( CItemData::ITEM_WEAPON_CROSSBOW, _S( 1039, "����" ),		ROGUE );		
			AddWeaponInfo( CItemData::ITEM_WEAPON_STAFF,	_S( 1040, "������" ),	MAGE );			
			AddWeaponInfo( CItemData::ITEM_WEAPON_BIGSWORD, _S( 1041, "���" ),		TITAN );		
			AddWeaponInfo( CItemData::ITEM_WEAPON_AXE,		_S( 1042, "����" ),		TITAN );		
			AddWeaponInfo( CItemData::ITEM_WEAPON_SSTAFF,	_S( 1043, "��������" ), MAGE );			
			AddWeaponInfo( CItemData::ITEM_WEAPON_BOW,		_S( 1044, "Ȱ" ),		HEALER );		
			AddWeaponInfo( CItemData::ITEM_WEAPON_DAGGER,	_S( 1045, "�ܰ�" ),		ROGUE );		
			AddWeaponInfo( CItemData::ITEM_WEAPON_TWOSWORD, _S( 1046, "�̵���" ),	KNIGHT );		
			AddWeaponInfo( CItemData::ITEM_WEAPON_WAND,		_S( 1047, "�����ϵ�" ),		HEALER );		
			AddWeaponInfo( CItemData::ITEM_WEAPON_SCYTHE,	_S(2306, "���̵�" ),		SORCERER );		
			AddWeaponInfo( CItemData::ITEM_WEAPON_POLEARM,		_S(2307, "����" ),		SORCERER );		

			RefreshWeaponList();

			m_eChangeWeaponState = CHANGEWEAPON_STAT;
			pUIManager->RearrangeOrder( UI_CHANGEWEAPON, TRUE );

			if( !pUIManager->GetInventory()->IsVisible() )
				pUIManager->GetInventory()->ToggleVisible();			
			// [KH_07044] 3�� ���� ���� �߰�
			if(g_iShowHelp1Icon)
			{
				pUIManager->GetHelp3()->ClearHelpString();
				pUIManager->GetHelp3()->AddHelpString(_S(3288, "��ü�ϰ��� �ϴ� ���⳪ ���� ���� ����� �� ĭ�� �÷� ������ ��ü����� ���Ǹ�, ��ü�Ϸ��� ������ �����ϰ� Ȯ���� ������ ����� ���ҵǰ� ���õ� ��ġ �״�� ������ ������ ���� ��ȯ�� �̷�� ���ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3289, "�� ��ü�Ǵ� ���� �� ���� ������ �ɼ��� �Ű����� �ʽ��ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3290, "�� 29���� �̻��� ������ ��ü�� �����մϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3291, "�� ���� ���� ��� ����ɼ� ���(73���� �̻�)�� ��ü�� �� �����ϴ�."));
				pUIManager->GetHelp3()->OpenHelp(this);
			}
		}		
		else if( nResult == CHANGEWEAPON_TALK )				// �̾߱��ϱ�.
		{
			//TODO : NewQuestSystem
			// ����Ʈ â ����
			CUIQuestBook::TalkWithNPC();
			//pUIManager->GetQuest()->OpenQuest( pUIManager->GetCharacterInfo()->GetMobIndex(), m_fNpcX, m_fNpcZ );
		}
		else if( nResult == CHANGEWEAPON_EVENT )			// Event
		{
		}
		else if(nResult == CHANGESHIELD_OK)
		{
			m_vectorWeaponInfo.clear();
					
			AddWeaponInfo( TITAN,	_S( 43, "Ÿ��ź" ),	TITAN );		
			AddWeaponInfo( KNIGHT,  _S( 44, "���" ),		KNIGHT );		
			AddWeaponInfo( HEALER,	_S( 45, "����" ),		HEALER );			
			AddWeaponInfo( MAGE,	_S( 46, "������" ),	MAGE );			
			AddWeaponInfo( ROGUE,	_S( 47, "�α�" ),		ROGUE );		
			AddWeaponInfo( SORCERER, _S( 48,"�Ҽ���" ),	SORCERER );		
#ifdef CHAR_EX_ROGUE
			AddWeaponInfo( EX_ROGUE,	_S( 5732, "EX�α�" ),		EX_ROGUE );		// [2012/08/27 : Sora] EX�α� �߰�
#endif
#ifdef CHAR_EX_MAGE
			AddWeaponInfo( EX_MAGE,	_S( 5820, "��ũ������" ),		EX_MAGE );		// 2013/01/08 jeil EX������ �߰� ���߿� ��Ʈ�� ������ ���� 
#endif
			RefreshWeaponList();
		

			m_eChangeWeaponState = CHANGEWEAPON_SHIELD;
			pUIManager->RearrangeOrder( UI_CHANGEWEAPON, TRUE );

			if( !pUIManager->GetInventory()->IsVisible() )
				pUIManager->GetInventory()->ToggleVisible();
			// [KH_07044] 3�� ���� ���� �߰�
			if(g_iShowHelp1Icon)
			{
				pUIManager->GetHelp3()->ClearHelpString();
				pUIManager->GetHelp3()->AddHelpString(_S(3288, "��ü�ϰ��� �ϴ� ���⳪ ���� ���� ����� �� ĭ�� �÷� ������ ��ü����� ���Ǹ�, ��ü�Ϸ��� ������ �����ϰ� Ȯ���� ������ ����� ���ҵǰ� ���õ� ��ġ �״�� ������ ������ ���� ��ȯ�� �̷�� ���ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3289, "�� ��ü�Ǵ� ���� �� ���� ������ �ɼ��� �Ű����� �ʽ��ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3290, "�� 29���� �̻��� ������ ��ü�� �����մϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3291, "�� ���� ���� ��� ����ɼ� ���(73���� �̻�)�� ��ü�� �� �����ϴ�."));
				pUIManager->GetHelp3()->OpenHelp(this);
			}
		}
		else if(nResult == CHANGEWEAPON_MASTERSTONE)
		{
			pUIManager->GetMixNew()->OpenMixNewMasterStone();
		}
		// [090527: selo] Ȯ���� ����Ʈ ����
		else if( ciQuestClassifier < nResult )	
		{
			// ������ ����Ʈ�� ���� ���� �Ǵ� ���� â�� ����.
			CUIQuestBook::SelectQuestFromMessageBox( nResult );
		}
		else
		{
			pUIManager->RearrangeOrder( UI_CHANGEWEAPON, FALSE );
		}
		break;
	
	}
}

// ----------------------------------------------------------------------------
// Name : CalculateNeedNas()
// Desc :
// ----------------------------------------------------------------------------
SQUAD CUIChangeWeapon::CalculateNeedNas( int iWeaponLevel )
{
#ifdef CHANGE_WEAPON_EVENT_2PAN4PAN		// 2��4�� ���� ��ü �̺�Ʈ.
	return 0;
#else
	ASSERT( iWeaponLevel <= CRITERION_LEVEL && "Invalid Weapon Level" );

	SQUAD llPrice	= 0;
	if( iWeaponLevel <= CRITERION_LEVEL )
		return llPrice;

//	llPrice			= ( iWeaponLevel - CRITERION_LEVEL ) * 5000;
// wooss 051217
//	llPrice = 5000 * (m_selItem.Item_Plus * 2 + 10) * (iWeaponLevel - CRITERION_LEVEL) / 10;
	llPrice = 5000 * (m_btnSlotItem.GetItemPlus() * 2 + 10) * (iWeaponLevel - CRITERION_LEVEL) / 10;
	return llPrice;
#endif
}

// ----------------------------------------------------------------------------
// Name : CalculateNeedNasS()
// Desc : Shield item Price
// ----------------------------------------------------------------------------
SQUAD CUIChangeWeapon::CalculateNeedNasS( int iWeaponLevel )
{
#ifdef CHANGE_WEAPON_EVENT_2PAN4PAN		// 2��4�� ���� ��ü �̺�Ʈ.
	return 0;
#else
	ASSERT( iWeaponLevel <= CRITERION_LEVEL && "Invalid Weapon Level" );

	SQUAD llPrice	= 0;
	if( iWeaponLevel <= CRITERION_LEVEL )
		return llPrice;

//	llPrice			= ( iWeaponLevel - CRITERION_LEVEL ) * 5000;
// wooss 051217
//	llPrice = 3000 * (m_selItem.Item_Plus * 2 + 10) * (iWeaponLevel - CRITERION_LEVEL) / 10;
	llPrice = 3000 * (m_btnSlotItem.GetItemPlus() * 2 + 10) * (iWeaponLevel - CRITERION_LEVEL) / 10;
	return llPrice;
#endif
}
// ----------------------------------------------------------------------------
// Name : SendChangeWeaponReq()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::SendChangeWeaponReq()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( ( (CPlayerEntity*)CEntity::GetPlayerEntity(0) )->IsSkilling() )
	{
		pUIManager->GetChatting()->AddSysMessage( _S( 1074, "��ų ����߿��� �������� ��ü�� �� �����ϴ�." ), SYSMSG_ERROR );	
		return;
	}
	
	if( pUIManager->IsCSFlagOn( CSF_TELEPORT ) )
	{
		pUIManager->GetChatting()->AddSysMessage( _S( 1075, "���� �̵��߿��� �����۸� ��ü�� �� �����ϴ�." ), SYSMSG_ERROR );	
		return;
	}
	
	if( m_btnSlotItem.IsEmpty() )
	{
		pUIManager->GetChatting()->AddSysMessage( _S( 1076, "��ü�� �������� �����ϴ�." ), SYSMSG_ERROR );		
		return;
	}

	const ULONG ulFlag = m_btnSlotItem.GetItemFlag();
	if( ulFlag & FLAG_ITEM_SEALED )
	{
		pUIManager->GetChatting()->AddSysMessage( _S( 1079, "���ε� �������� ��ü�� �� �����ϴ�." ), SYSMSG_ERROR );		
		return;
	}

#ifndef CHANGE_WEAPON_SHIELD_EVENT
	if( m_llChangeWeaponMoney > _pNetwork->MyCharacterInfo.money && !m_bCashItemChk )
	{
		pUIManager->GetChatting()->AddSysMessage( _S( 1080, "��ü ����� �����մϴ�." ), SYSMSG_ERROR );		
		return;
	}
#endif

	if( m_lbWeaponList.GetCurSel() == -1 )
	{
		pUIManager->GetChatting()->AddSysMessage( _S( 2321,"���ο� ����� ���� �������ֽʽÿ�." ), SYSMSG_ERROR );		
		return;
	}

	// wooss 051217 add shield item exchange
	if(m_slLevel < EXCHANGE_LIMIT_LEVEL)
	{
		pUIManager->GetChatting()->AddSysMessage( _S(2322,"29Lv�̻��� ����� ���� ��ü�� �Ͻ� �� �ֽ��ϴ�."));
		return;
	}

	
	pUIManager->CloseMessageBox( MSGCMD_CHANGEWEAPON_REP );
	
	// Create message box of remission
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S(2308, "����� �� ��ü" ), UMBS_OKCANCEL,UI_CHANGEWEAPON, MSGCMD_CHANGEWEAPON_REP );
	MsgBoxInfo.AddString( _S(2323,"��ü ����� ���� ���õ� ����� �Ű������� ������ �ɼ��� �Ű����� �ʽ��ϴ�. ����� ���� ��ü�Ͻðڽ��ϱ�?" ) );
	pUIManager->CreateMessageBox( MsgBoxInfo );
}


// ----------------------------------------------------------------------------
// Name : AddWeaponDescString()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::AddWeaponDescString( CTString &strDesc, COLOR colDesc )
{
	// Get length of string
	INDEX	nLength = strDesc.Length();
	if( nLength == 0 )
		return;

	// wooss 051002
#if defined(G_THAI)
	{
		int		iPos;
		// Get length of string
		INDEX	nThaiLen = FindThaiLen(strDesc);
		INDEX	nChatMax= (_iMaxMsgStringChar-1)*(_pUIFontTexMgr->GetFontWidth()+_pUIFontTexMgr->GetFontSpacing());
		if( nLength == 0 )
			return;
		// If length of string is less than max char
		if( nThaiLen <= nChatMax )
		{
			// Check line character
		for( iPos = 0; iPos < nLength; iPos++ )
		{
			if( strDesc[iPos] == '\n' || strDesc[iPos] == '\r' )
				break;
		}

		// Not exist
		if( iPos == nLength )
		{
			m_lbWeaponDesc.AddString( 0, strDesc, colDesc );
		}
		else
		{
			// Split string
			CTString	strTemp, strTemp2;
			strDesc.Split( iPos, strTemp2, strTemp );
			m_lbWeaponDesc.AddString( 0, strTemp2, colDesc );

			// Trim line character
			if( strTemp[0] == '\r' && strTemp[1] == '\n' )
				strTemp.TrimLeft( strTemp.Length() - 2 );
			else
				strTemp.TrimLeft( strTemp.Length() - 1 );

			AddWeaponDescString( strTemp, colDesc );
		}
		}
		// Need multi-line
		else
		{
			// Check splitting position for 2 byte characters
			int		nSplitPos = _iMaxMsgStringChar;
			BOOL	b2ByteChar = FALSE;
			for( iPos = 0; iPos < nLength; iPos++ )
			{
				if(nChatMax < FindThaiLen(strDesc,0,iPos))
					break;
			}
			nSplitPos = iPos;

			// Check line character
			for( iPos = 0; iPos < nSplitPos; iPos++ )
			{
				if( strDesc[iPos] == '\n' || strDesc[iPos] == '\r' )
					break;
			}

			// Not exist
			if( iPos == nSplitPos )
			{
				// Split string
				CTString	strTemp, strTemp2;
				strDesc.Split( nSplitPos, strTemp2, strTemp );
				m_lbWeaponDesc.AddString( 0, strTemp2, colDesc );

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

				AddWeaponDescString( strTemp, colDesc );
			}
			else
			{
				// Split string
				CTString	strTemp, strTemp2;
				strDesc.Split( iPos, strTemp2, strTemp );
				m_lbWeaponDesc.AddString( 0, strTemp2, colDesc );

				// Trim line character
				if( strTemp[0] == '\r' && strTemp[1] == '\n' )
					strTemp.TrimLeft( strTemp.Length() - 2 );
				else
					strTemp.TrimLeft( strTemp.Length() - 1 );

				AddWeaponDescString( strTemp, colDesc );
			}

		}
		
	}
#else
	{
		// If length of string is less than max char
		if( nLength <= _iMaxMsgStringChar )
		{
			// Check line character
			int iPos;
			for( iPos = 0; iPos < nLength; iPos++ )
			{
				if( strDesc[iPos] == '\n' || strDesc[iPos] == '\r' )
					break;
			}

			// Not exist
			if( iPos == nLength )
			{
				m_lbWeaponDesc.AddString( 0, strDesc, colDesc );
			}
			else
			{
				// Split string
				CTString	strTemp, strTemp2;
				strDesc.Split( iPos, strTemp2, strTemp );
				m_lbWeaponDesc.AddString( 0, strTemp2, colDesc );

				// Trim line character
				if( strTemp[0] == '\r' && strTemp[1] == '\n' )
					strTemp.TrimLeft( strTemp.Length() - 2 );
				else
					strTemp.TrimLeft( strTemp.Length() - 1 );

				AddWeaponDescString( strTemp, colDesc );
			}
		}
		// Need multi-line
		else
		{
			// Check splitting position for 2 byte characters
			int		nSplitPos = _iMaxMsgStringChar;
			BOOL	b2ByteChar = FALSE;
			int iPos;
			for( iPos = 0; iPos < nSplitPos; iPos++ )
			{
				if( strDesc[iPos] & 0x80 )
					b2ByteChar = !b2ByteChar;
				else
					b2ByteChar = FALSE;
			}

			if( b2ByteChar )
				nSplitPos--;

			// Check line character			
			for( iPos = 0; iPos < nSplitPos; iPos++ )
			{
				if( strDesc[iPos] == '\n' || strDesc[iPos] == '\r' )
					break;
			}

			// Not exist
			if( iPos == nSplitPos )
			{
				// Split string
				CTString	strTemp, strTemp2;
				strDesc.Split( nSplitPos, strTemp2, strTemp );
				m_lbWeaponDesc.AddString( 0, strTemp2, colDesc );

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

				AddWeaponDescString( strTemp, colDesc );
			}
			else
			{
				// Split string
				CTString	strTemp, strTemp2;
				strDesc.Split( iPos, strTemp2, strTemp );
				m_lbWeaponDesc.AddString( 0, strTemp2, colDesc );

				// Trim line character
				if( strTemp[0] == '\r' && strTemp[1] == '\n' )
					strTemp.TrimLeft( strTemp.Length() - 2 );
				else
					strTemp.TrimLeft( strTemp.Length() - 1 );

				AddWeaponDescString( strTemp, colDesc );
			}
		}
	}
#endif
}

// ----------------------------------------------------------------------------
// Name : GetWeaponInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::GetWeaponInfo( int iJob, int iWeaponLevel, int iWeaponType )
{
	ASSERT( iWeaponLevel != -1 && "Invalid Weapon Level" );	
	CItemData::_map::iterator	iter = CItemData::_mapdata.begin();
	CItemData::_map::iterator	eiter = CItemData::_mapdata.end();

	for (;iter != eiter; ++iter)
	{
		CItemData* pID = (*iter).second;
		
		if (pID == NULL)
			continue;
		
		if( pID->GetType() != CItemData::ITEM_WEAPON )
			continue;
		
		if( pID->GetSubType() != iWeaponType )
			continue;
		
		if( pID->GetLevel() != iWeaponLevel )
			continue;

		// [2012/05/18 : Sora] ITS 9075 ���ⱳȯ ī�� ���� (������ �� ���ϰ� �ٸ���..�ϴ� ���� -_-;)
		if( !(pID->GetJob()&(1<<iJob)))
			continue;

		if( !(pID->IsFlag(ITEM_FLAG_CHANGE)))
			continue;
		// [2012/05/18 : Sora]  //

#ifdef CHANGE_WEAPON_EVENT_2PAN4PAN		// 2��4�� ���� ��ü �̺�Ʈ.
		if( !IsChangeableWeapon( pID->GetItemIndex() ) )
		{
			continue;
		}
#endif
		
		m_strWeaponName			= pID->GetName();
		m_strWeaponLevel.PrintF( "%d", pID->GetLevel() );
		
		// FIXME : �ϳ��� ���⸦ �ٸ� �� ������ ���� �ֳ�???
		// [2012/05/18 : Sora] ITS 9075 �� ��ó�� �ʿ� ������...����
		/*
		CTString strTemp;
		for(int i = 0; i < TOTAL_JOB; ++i)
		{
			if( pID->CanUse(i) )
			{
				strTemp += JobInfo().GetName(i);
				break;
			}
		}
		
		m_strWeaponClass		= strTemp;
		*/
		m_strWeaponClass		= CJobInfo::getSingleton()->GetName(iJob);
		// [2012/05/18 : Sora]  //
		m_strWeaponAttack.PrintF( "%d", pID->GetPhysicalAttack() );
		m_strWeaponMagicAttack.PrintF( "%d", pID->GetMagicAttack() );
		return;
	}	

	m_strWeaponName.Clear();
	m_strWeaponLevel.Clear();
	m_strWeaponClass.Clear();
	m_strWeaponAttack.Clear();
	m_strWeaponMagicAttack.Clear();
	m_strWeight.Clear();
	m_strChangeWeaponMoney.Clear();
}

// ----------------------------------------------------------------------------
// Name : GetShieldInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::GetShieldInfo( int iJob, int iWeaponLevel ,int iWeaponType)
{
	ASSERT( iWeaponLevel != -1 && "Invalid Weapon Level" );	
	CItemData::_map::iterator	iter = CItemData::_mapdata.begin();
	CItemData::_map::iterator	eiter = CItemData::_mapdata.end();

	for (;iter != eiter; ++iter)
	{
		CItemData* pID = (*iter).second;

		if (pID == NULL)
			continue;

		if( pID->GetType() != CItemData::ITEM_SHIELD )
			continue;

		if( pID->GetSubType() != iWeaponType )
			continue;
				
		if( pID->GetLevel() != iWeaponLevel )
			continue;
		
		if( !(pID->GetJob()&(1<<iJob)))
			continue;

		if( !(pID->IsFlag(ITEM_FLAG_CHANGE)))
			continue;
		

#ifdef CHANGE_WEAPON_EVENT_2PAN4PAN		// 2��4�� ���� ��ü �̺�Ʈ.
		if( !IsChangeableWeapon( pID->GetItemIndex() ) )
		{
			continue;
		}
#endif
		
		m_strWeaponName			= pID->GetName();
		m_strWeaponLevel.PrintF( "%d", pID->GetLevel() );
		m_strWeaponClass		= CJobInfo::getSingleton()->GetName(iJob);
		m_strWeaponDefence.PrintF( "%d", pID->GetPhysicalDefence() );
		return;
	}	

	m_strWeaponName.Clear();
	m_strWeaponLevel.Clear();
	m_strWeaponClass.Clear();
	m_strWeaponDefence.Clear();
	m_strWeight.Clear();
	m_strChangeWeaponMoney.Clear();
}

// ----------------------------------------------------------------------------
// Name : AddWeaponInfo()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::AddWeaponInfo( int iType, const CTString& strName, int iJob )
{
	sWeaponInfo		TempWeapon;
	TempWeapon.strName		= strName;
	TempWeapon.iIndex		= iType;
	TempWeapon.iJob			= iJob;
	m_vectorWeaponInfo.push_back(TempWeapon);
}

// ----------------------------------------------------------------------------
// Name : RefreshWeaponList()
// Desc :
// ----------------------------------------------------------------------------
void CUIChangeWeapon::RefreshWeaponList()
{
	m_lbWeaponList.ResetAllStrings();
	std::sort( m_vectorWeaponInfo.begin(), m_vectorWeaponInfo.end() );

	std::vector<sWeaponInfo>::const_iterator End = m_vectorWeaponInfo.end();	
	for( std::vector<sWeaponInfo>::iterator it = m_vectorWeaponInfo.begin();
		it != End; ++it )
	{
		m_lbWeaponList.AddString( 0, (*it).strName );
	}
	
}

void CUIChangeWeapon::initialize()
{
	_iMaxMsgStringChar = 190 / ( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() );

	// Region of each part
	m_rcTitle.SetRect( 0, 0, 216, 22 );
	m_rcItemSlot.SetRect( 97, 0, 131, 0 );
	m_rcInsertItem.SetRect( 3, 0, 213, 0 );
	
	m_rcItemSlot.Top		= 51;
	m_rcItemSlot.Bottom		= m_rcItemSlot.Top + 34;

	m_rcInsertItem.Top		= 33;
	m_rcInsertItem.Bottom	= m_rcItemSlot.Bottom + 33;

	// Slot item button
	m_btnSlotItem.Create( this, m_rcItemSlot.Left + 1, m_rcItemSlot.Top + 1, BTN_SIZE, BTN_SIZE, UI_CHANGEWEAPON, UBET_ITEM );
/*
	AddWeaponInfo( CItemData::ITEM_WEAPON_KNIFE,	_S( 1038, "��絵" ),	TITAN );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_CROSSBOW, _S( 1039, "����" ),		ROGUE );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_STAFF,	_S( 1040, "������" ),	MAGE );			
	AddWeaponInfo( CItemData::ITEM_WEAPON_BIGSWORD, _S( 1041, "���" ),		TITAN );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_AXE,		_S( 1042, "����" ),		TITAN );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_SSTAFF,	_S( 1043, "��������" ), MAGE );			
	AddWeaponInfo( CItemData::ITEM_WEAPON_BOW,		_S( 1044, "Ȱ" ),		HEALER );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_DAGGER,	_S( 1045, "�ܰ�" ),		ROGUE );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_TWOSWORD, _S( 1046, "�̵���" ),	KNIGHT );	
	AddWeaponInfo( CItemData::ITEM_WEAPON_WAND,		_S( 1047, "�����ϵ�" ),		HEALER );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_SCYTHE,	_S( 2306,"���̵�" ),		SORCERER );		
	AddWeaponInfo( CItemData::ITEM_WEAPON_POLEARM,		_S(2307, "����" ),		SORCERER );		

	RefreshWeaponList();
	*/
}

void CUIChangeWeapon::OnUpdate( float fElapsedTime )
{

}

void CUIChangeWeapon::OnRender( CDrawPort* pDraw )
{
	// Check distance
	FLOAT	fDiffX = _pNetwork->MyCharacterInfo.x - m_fNpcX;
	FLOAT	fDiffZ = _pNetwork->MyCharacterInfo.z - m_fNpcZ;
	// cash item check wooss 051011
	if( m_bCashItemChk == FALSE )
	{
		if( fDiffX * fDiffX + fDiffZ * fDiffZ > UI_VALID_SQRDIST )
		{
			CloseChangeWeapon();
		}
	}

	// Set refine texture
	pDraw->InitTextureData( m_ptdBaseTexture );

	// Add render regions
	int	nX, nY, nX2, nY2;

	nX	= m_nPosX + 95;
	nX2	= nX + 84;
	nY	= m_nPosY + 102;
	nY2 = nY + 13;

	if(!m_bCashItemChk){
		// Point    �ݾ� �ڽ� wooss 051011
		pDraw->AddTexture( nX, nY, nX + 4, nY2,
			m_rtInputBoxL.U0, m_rtInputBoxL.V0, m_rtInputBoxL.U1, m_rtInputBoxL.V1,
			0xFFFFFFFF );
		//Lower middle
		pDraw->AddTexture( nX + 4, nY, nX2 - 4, nY2,
			m_rtInputBoxM.U0, m_rtInputBoxM.V0, m_rtInputBoxM.U1, m_rtInputBoxM.V1,
			0xFFFFFFFF );
		// Lower right
		pDraw->AddTexture( nX2 - 4, nY, nX2, nY2,
			m_rtInputBoxR.U0, m_rtInputBoxR.V0, m_rtInputBoxR.U1, m_rtInputBoxR.V1,
			0xFFFFFFFF );
	}

	// Render all elements
	pDraw->FlushRenderingQueue();

	// Item
	if( !m_btnSlotItem.IsEmpty() )
	{
		m_btnSlotItem.Render();
		pDraw->FlushBtnRenderingQueue( UBET_ITEM );
	}

	if( m_eChangeWeaponState == CHANGEWEAPON_STAT ){

		// Text in refine
		pDraw->PutTextEx( _S( 1049, "���� ��ü"  ), m_nPosX + CHANGEWEAPON_TITLE_TEXT_OFFSETX,		
			m_nPosY + CHANGEWEAPON_TITLE_TEXT_OFFSETY, 0xFFFFFFFF );

		pDraw->PutTextEx( _S( 1057, "��ü����" ), m_nPosX + 40,		
			m_nPosY + 60, 0xFFFFFFFF );

		// cash item check wooss 051011
		if(!m_bCashItemChk) {
			nY = m_nPosY + 104;
			pDraw->PutTextEx( _S( 1058, "�ʿ䳪��" ), m_nPosX + 40,		
				nY, 0xFFFFFFFF );
			// ChangeWeaponing money
#ifdef CHANGE_WEAPON_SHIELD_EVENT	
			pDraw->PutTextEx( _S(2315," ��ü �̺�Ʈ"),	m_nPosX + 95, m_nPosY + 102, 0xE1B300FF );	
#else
			pDraw->PutTextEx( m_strChangeWeaponMoney,	m_nPosX + 95, m_nPosY + 102, 0xE1B300FF );				
#endif 

		}

		nY = m_nPosY + 143;
		pDraw->PutTextEx( _S( 1059, "���� ����Ʈ" ), m_nPosX + 12,		
			nY, 0xE18600FF );

		nY = m_nPosY + 269;
		pDraw->PutTextEx( _S( 1065, "���� �̸�" ), m_nPosX + WEAPON_INFO_START_X,		
			nY, 0xFFFFFFFF );

		pDraw->PutTextExRX( m_strWeaponName, m_nPosX + WEAPON_DESC_START_X,		
			nY, 0xFFd223FF );

		nY += 15;
		pDraw->PutTextEx( _S( 1066, "���� ����" ), m_nPosX + WEAPON_INFO_START_X,		
			nY, 0xFFFFFFFF );

		pDraw->PutTextExRX( m_strWeaponLevel, m_nPosX + WEAPON_DESC_START_X,		
			nY, 0xFFd223FF );

		nY += 15;
		pDraw->PutTextEx( _S( 1067, "��� Ŭ����" ), m_nPosX + WEAPON_INFO_START_X,		
			nY, 0xFFFFFFFF );

		pDraw->PutTextExRX( m_strWeaponClass, m_nPosX + WEAPON_DESC_START_X,		
			nY, 0xFFd223FF );

		nY += 15;
		pDraw->PutTextEx( _S( 1068, "���ݷ�" ), m_nPosX + WEAPON_INFO_START_X,		
			nY, 0xFFFFFFFF );

		pDraw->PutTextExRX( m_strWeaponAttack, m_nPosX + WEAPON_DESC_START_X,		
			nY, 0xFFd223FF );

		nY += 15;
		pDraw->PutTextEx( _S( 1069, "���� ���ݷ�" ), m_nPosX + WEAPON_INFO_START_X,		
			nY, 0xFFFFFFFF );

		pDraw->PutTextExRX( m_strWeaponMagicAttack, m_nPosX + WEAPON_DESC_START_X,		
			nY, 0xFFd223FF );
	}
	else if( m_eChangeWeaponState == CHANGEWEAPON_SHIELD){
		// Text in refine
		pDraw->PutTextEx( _S( 2313,"�� ��ü"  ), m_nPosX + CHANGEWEAPON_TITLE_TEXT_OFFSETX,		
			m_nPosY + CHANGEWEAPON_TITLE_TEXT_OFFSETY, 0xFFFFFFFF );

		pDraw->PutTextEx( _S( 2314,"��ü ��" ), m_nPosX + 30,		
			m_nPosY + 60, 0xFFFFFFFF );

		// cash item check wooss 051011
		if(!m_bCashItemChk) {
			nY = m_nPosY + 104;
			pDraw->PutTextEx( _S( 1058, "�ʿ䳪��" ), m_nPosX + 40,		
				nY, 0xFFFFFFFF );
#ifdef CHANGE_WEAPON_SHIELD_EVENT	
			pDraw->PutTextEx( _S(2315," ��ü �̺�Ʈ"), m_nPosX + 95, m_nPosY + 102, 0xE1B300FF );	
#else
			pDraw->PutTextEx( m_strChangeWeaponMoney,	m_nPosX + 95, m_nPosY + 102, 0xE1B300FF );				
#endif 
		}

		nY = m_nPosY + 143;
		pDraw->PutTextEx( _S(2316, "Ŭ���� ����Ʈ" ), m_nPosX + 12,		
			nY, 0xE18600FF );

		nY = m_nPosY + 269;
		pDraw->PutTextEx( _S(2317, "�� �̸�" ), m_nPosX + WEAPON_INFO_START_X,		
			nY, 0xFFFFFFFF );

		pDraw->PutTextExRX( m_strWeaponName, m_nPosX + WEAPON_DESC_START_X,		
			nY, 0xFFd223FF );

		nY += 15;
		pDraw->PutTextEx( _S(2318, "�� ����" ), m_nPosX + WEAPON_INFO_START_X,		
			nY, 0xFFFFFFFF );

		pDraw->PutTextExRX( m_strWeaponLevel, m_nPosX + WEAPON_DESC_START_X,		
			nY, 0xFFd223FF );

		nY += 15;
		pDraw->PutTextEx( _S( 1067, "��� Ŭ����" ), m_nPosX + WEAPON_INFO_START_X,		
			nY, 0xFFFFFFFF );

		pDraw->PutTextExRX( m_strWeaponClass, m_nPosX + WEAPON_DESC_START_X,		
			nY, 0xFFd223FF );

		nY += 15;
		pDraw->PutTextEx( _S(87, "����" ), m_nPosX + WEAPON_INFO_START_X,		
			nY, 0xFFFFFFFF );

		pDraw->PutTextExRX( m_strWeaponDefence, m_nPosX + WEAPON_DESC_START_X,		
			nY, 0xFFd223FF );
	}

	// Flush all render text queue
	pDraw->EndTextEx();
}

