#include "stdh.h"

// ��� ����. [12/2/2009 rumist]
#include <vector>
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Interface/UISelectWord.h>
#include <Engine/Interface/UIShop.h>
#include <Engine/LocalDefine.h>
#include <Engine/Interface/UISiegeWarfareDoc.h>
#include <Engine/Contents/Base/UINoticeNew.h>
#include <Engine/Help/ItemHelp.h>
#include <Common/Packet/ptype_old_do_event.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Interface/UISkillLearn.h>
#include <Engine/Interface/UIHelp.h>
#include <Engine/Interface/UIMinigame.h>
#include <Engine/Interface/UISiegeWarfareNew.h>
#include <Engine/Contents/Base/UIAuctionNew.h>
#include <Engine/Interface/UIFlowerTree.h>
#include <Engine/Interface/UIProduct.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/Base/Syndicate.h>
#include <Engine/Object/ActorMgr.h>
#include <Engine/Contents/Base/UITrade.h>
#include <Engine/Contents/Base/Quest.h>
#include <Engine/Contents/Base/UIQuestBookNew.h>
#include <Engine/Contents/Base/UIQuestAccept.h>
#include <Engine/Contents/Base/UIQuestComplete.h>
#include <Engine/Contents/function/CashExchangeUI.h>
#include <Engine/Info/MyInfo.h>

#ifdef BATTLE_PASS_SYSTEM
#include <Engine/Interface/UIBattlePass.h>
#endif
#ifdef PRESTIGE_SYSTEM
#include <Engine/Interface/UIPrestige.h>
#endif

extern INDEX g_iCountry;
extern INDEX g_iTempFlag;

// [KH_07044] 3�� ���� ���� �߰�
extern INDEX g_iShowHelp1Icon;

ENGINE_API extern CUISiegeWarfareDoc* _pUISWDoc;

///////////////////////////////////////////////////////////////////////////////////////
//
// g_iTempflag :	< 0x0000**** - ZONE FLAG >				
//	(ps.dta)				
//					0x00000001 - ����ī����				0x00000002 - ������ �� on/off
//					
//					< 0x****0000 - EVENT FLAG >
//
//					0x00010000 - WEAPONCHANGE_EVENT		0x00020000 - TREASURE_BOX_EVENT
//					0x00040000 - QUEST_HARVEST_MOON_DAY -> Replace Open Event(temporary) 
//					0x00080000 - Christmas Event	
//					0x00100000 - Newyear Event
//					0x00200000 - Coupon Event (JAPAN)
//					0x00400000 - Connect Event (JAPAN)	
//					0x80000000 - EVENT on/off
//
///////////////////////////////////////////////////////////////////////////////////////

//#define WEAPONCHANGE_EVENT		// ���� ��ȯ �̺�Ʈ
#define TREASURE_BOX_EVENT			// �������� �̺�Ʈ
//#define QUEST_HARVEST_MOON_DAY		// �߼� �̺�Ʈ 
//#define RENUAL_EVENT			// 2P4P Renual Event  10/6 Update
//#define PLATINUM_EVENT
//#define WORLDCUP_ITEM
//#define WORLDCUP_GOLDENBALL
#define XMAS_EVENT_2006				// 2006 X-MAS Event [12/11/2006 Theodoric]

// �������̺�Ʈ
#define WORLDCUP_MAX_GROUP 4

// �ұ� �к� �̺�Ʈ
//#define BUDDHISM_EVENT

//#define EVENT_REQUITALM //[ttos_2009_4_13]:���� ���� �����̺�Ʈ

#define DEF_REGISTER_MERCHANT_NEED_SP	2000
#define DEF_REGISTER_MERCHANT_NEED_NAS	100000000

int	iSelCountry =-1;
int iSelGroup =-1;
int iGroup[WORLDCUP_MAX_GROUP+1] ={ 0, 5, 14, 23, 32 };


enum eWeaponChangeSelection
{
	EVENT_CHANGEWEAPON,
};

enum eGateOfDimensionSelection
{
	GOD_ENTER,						// ������ �� ����
	GOD_RANKING,					// ������ �� ���� Ȯ��
	GOD_PRIZE,						// ����
};

enum eClothesExchangeSelection
{
	COAT_PANTS,
	GLOVE_FOOTWEAR,
	HELMET,
};

enum ePlatiumExchangeSelection
{
	PLATINUM_STONE_EXCHANGE1,
	PLATINUM_STONE_EXCHANGE2,
	PLATINUM_STONE_EXCHANGE3
};

enum eWorldCupExchangeSelection
{
	WORLDCUP_EVENT1_EXCHANGE,
	WORLDCUP_EVENT1_RECEIVE,
	WORLDCUP_EVENT1_EXCHANGE100,
	WORLDCUP_EVENT1_EXCHANGE75,
	WORLDCUP_EVENT1_EXCHANGE50,
	WORLDCUP_EVENT1_EXCHANGE25,
	WORLDCUP_EVENT1_REWARD1,
	WORLDCUP_EVENT1_REWARD2,
	WORLDCUP_EVENT1_REWARD3,
	WORLDCUP_EVENT1_REWARD4,
};

// Date : 2005-03-07,   By Lee Ki-hwan
static int	_iMaxMsgStringChar = 0;

// WSS_GUILDMASTER 070416 ------------------------------------->>
BOOL CheckGuildMasterEvent()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;	
	pUIManager->DoesMessageBoxExist(MSGCMD_NULL);
	
	if( pUIManager->GetInventory()->GetItemCount(2331) <= 0 ) // 2331 ���� ī���̼�
	{
		MsgBoxInfo.SetMsgBoxInfo( _S( 100, "�̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_NULL);		
		strMessage.PrintF( _S(2236,"�̺�Ʈ �������� �������� �ʽ��ϴ�.") );
		MsgBoxInfo.AddString( strMessage );
		pUIManager->CreateMessageBox( MsgBoxInfo );
		return FALSE;
	}
	
	return TRUE;
}
// ------------------------------------------------------------<<


// ----------------------------------------------------------------------------
// Name : CUIQuest()
// Desc : Constructor
// ----------------------------------------------------------------------------
CUIQuest::CUIQuest()
{
	m_iNpcIndex			= -1;
	m_iNpcVirIdx		= -1;
	m_iCurQuestIndex	= -1;

	for(int i=0 ; i< WORLDCUP_MAX_COUNTRY ;i++)
		m_strCountry[i] = _S(i+2858,"2006 ������ ���� ���ⱹ");
/*
	"�����","����","��Ż����","����","�Ƹ���Ƽ��",
	"������","�״�����","������","��������","ü��",
	"������","�߽���","��ũ���̳�","ũ�ξ�Ƽ��","�̱�",
	"������","��Ʈ��ξƸ�","�������-���׳ױ׷�","������","�Ķ����",
	"���ѹα�","ȣ��","�Ϻ�","����","Ƣ����",
	"���⵵��","���","�Ӱ��","�̶�","����ƶ���",
	"�ڽ�Ÿ��ī","Ʈ���ϴٵ� ��ٰ�",
	*/
	
	// ($E_WC2010) [100517: selo] ���� ������ ����Ʈ �����
	InitNationFlag();	
}

// ----------------------------------------------------------------------------
// Name : ~CUIQuest()
// Desc : Destructor
// ----------------------------------------------------------------------------
CUIQuest::~CUIQuest()
{
}

// -----------------------------------------------------------------------------
//  [5/17/2010 selo0530] ($E_WC2010)
//	Name : InitNationFlag
//	Desc : ���� ������ ����Ʈ �����
// -----------------------------------------------------------------------------
void CUIQuest::InitNationFlag()
{
	m_mapNationFlag.insert(std::make_pair(1485, 0));	// �����
	m_mapNationFlag.insert(std::make_pair(1486, 0));	// ����
	m_mapNationFlag.insert(std::make_pair(1487, 0));	// ��Ż����
	m_mapNationFlag.insert(std::make_pair(1488, 0));	// ����	
	m_mapNationFlag.insert(std::make_pair(1489, 0));	// �Ƹ���Ƽ��
	m_mapNationFlag.insert(std::make_pair(1490, 0));	// ������
	m_mapNationFlag.insert(std::make_pair(1491, 0));	// �״�����
	m_mapNationFlag.insert(std::make_pair(1492, 0));	// ������
	m_mapNationFlag.insert(std::make_pair(1493, 0));	// ��������
	m_mapNationFlag.insert(std::make_pair(1494, 0));	// ü��
	m_mapNationFlag.insert(std::make_pair(1495, 0));	// ������
	m_mapNationFlag.insert(std::make_pair(1496, 0));	// �߽���
	m_mapNationFlag.insert(std::make_pair(1497, 0));	// ��ũ���̳�
	m_mapNationFlag.insert(std::make_pair(1498, 0));	// ũ�ξ�Ƽ��
	m_mapNationFlag.insert(std::make_pair(1499, 0));	// �̱�
	m_mapNationFlag.insert(std::make_pair(1500, 0));	// ������
	m_mapNationFlag.insert(std::make_pair(1501, 0));	// ��Ʈ��ξƸ�	
	m_mapNationFlag.insert(std::make_pair(1502, 0));	// ������Ƹ��׳ױ׷�
	m_mapNationFlag.insert(std::make_pair(1503, 0));	// ������
	m_mapNationFlag.insert(std::make_pair(1504, 0));	// �Ķ����
	m_mapNationFlag.insert(std::make_pair(1505, 0));	// ���ѹα�
	m_mapNationFlag.insert(std::make_pair(1506, 0));	// ȣ��
	m_mapNationFlag.insert(std::make_pair(1507, 0));	// �Ϻ�
	m_mapNationFlag.insert(std::make_pair(1508, 0));	// ����
	m_mapNationFlag.insert(std::make_pair(1509, 0));	// Ƣ����
	m_mapNationFlag.insert(std::make_pair(1510, 0));	// ���⵵��
	m_mapNationFlag.insert(std::make_pair(1511, 0));	// ���
	m_mapNationFlag.insert(std::make_pair(1512, 0));	// �Ӱ��
	m_mapNationFlag.insert(std::make_pair(1513, 0));	// �̶�
	m_mapNationFlag.insert(std::make_pair(1514, 0));	// ����ƶ���
	m_mapNationFlag.insert(std::make_pair(1515, 0));	// �ڽ�Ÿ��ī
	m_mapNationFlag.insert(std::make_pair(1516, 0));	// Ʈ���ϴٵ���ٰ�
	m_mapNationFlag.insert(std::make_pair(5331, 0));	// ��������ī��ȭ��
	m_mapNationFlag.insert(std::make_pair(5332, 0));	// ������
	m_mapNationFlag.insert(std::make_pair(5333, 0));	// ����������
	m_mapNationFlag.insert(std::make_pair(5334, 0));	// �׸���
	m_mapNationFlag.insert(std::make_pair(5335, 0));	// ���κ��Ͼ�
	m_mapNationFlag.insert(std::make_pair(5336, 0));	// �������
	m_mapNationFlag.insert(std::make_pair(5337, 0));	// ����ũ
	m_mapNationFlag.insert(std::make_pair(5338, 0));	// ī�޷�
	m_mapNationFlag.insert(std::make_pair(5339, 0));	// ��������
	m_mapNationFlag.insert(std::make_pair(5340, 0));	// ���ι�Ű��
	m_mapNationFlag.insert(std::make_pair(5341, 0));	// ����
	m_mapNationFlag.insert(std::make_pair(5342, 0));	// �µζ�
	m_mapNationFlag.insert(std::make_pair(5343, 0));	// ĥ��
	m_mapNationFlag.insert(std::make_pair(5344, 0));	// ������
}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
void CUIQuest::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight )
{
	int diff = SKILLLEARN_HEIGHT - QUEST_HEIGHT;

	CUIWindow::Create(pParentWnd, nX, nY, nWidth, nHeight);
	
	_iMaxMsgStringChar = QUESTINFO_CHAR_WIDTH / ( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() );

	m_strTeamA = CTString( " " );
	m_strTeamB = CTString( " " );
	m_bGoldenBallEntry = FALSE;
	m_bGoldenBallRequital = FALSE;
	m_bStartGoldenBall = FALSE;

	// [2011/02/09 : Sora]	����Ʈ������ �ٽ� �ޱ�
	m_restoreQuestIndex = -1;
	m_restoreQuestItemIndex = -1;
}

static BOOL g_bHasQuest = FALSE;
static BOOL g_bHasEvent = FALSE;
// ----------------------------------------------------------------------------
// Name : OpenQuest()
// Desc : 
// ----------------------------------------------------------------------------
void CUIQuest::OpenQuest( int iMobIndex, int iMobVirIdx, BOOL bHasQuest, FLOAT fX, FLOAT fZ )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// If this is already exist
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_QUEST_REQ ) || IsVisible() ) 		return;
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_RENUAL_EVENT ) || IsVisible() )		return;
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_HARVEST_MOON_DAY1 ) || IsVisible() )	return;
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_HARVEST_MOON_DAY2 ) || IsVisible() )	return;
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_EVENT ) || IsVisible() )				return;
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_GATE_OF_DIMENSION ) || IsVisible() )	return;
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_CHANGEWEAPON_EVENT_REQ ) || IsVisible() )	return;
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_TREASUREBOX_EVENT ) || IsVisible() )	return;
	if (pUIManager->DoesMessageBoxLExist(MSGLCMD_EVENT_MINIGAME) || IsVisible()) return;
	
	if( pUIManager->GetSelectWord()->IsVisible() ) return;

	// Set position of target npc
	m_fNpcX = fX;
	m_fNpcZ = fZ;

	CMobData* MD = CMobData::getData(iMobIndex);

	// Cash Exchange NPC (early check to bypass default quest dialog)
	if( iMobIndex == 3696 )
	{
		pUIManager->GetCashExchange()->OpenUI();
		return;
	}

	// NOTE : ���� �������� ���.
	if( iMobIndex == 71 )
	{
		// ����Ʈ ���� Ȯ��.
		if(GAMEDATAMGR()->GetQuest()->GetCompleteQuestCount())
		{
			int nQuestIdx = GAMEDATAMGR()->GetQuest()->GetCompleteQuestIndex(0);
			pUIManager->GetQuestBookComplete()->open(nQuestIdx);
			pUIManager->GetQuestBookComplete()->SetTargetIndex( pUIManager->GetQuestBookList()->GetTargetIndex() );
			pUIManager->GetQuestBookList()->SetTargetIndex(-1);
			pUIManager->GetQuestAccept()->SetTargetIndex(-1);

			// [090528: selo] ���� ��ư�� ����ϱ� ���� NPC �ε����� �ѹ��� �����ϴ� ���
			pUIManager->GetQuestBookComplete()->SetPrevNpcIdx(71);
			pUIManager->GetQuestBookComplete()->SetPrevNpcUIType(UI_QUEST);
		}
		else
		{
			// [KH_07044] 3�� ���� ���� �߰�
			if(g_iShowHelp1Icon)
			{
				pUIManager->GetHelp3()->ClearHelpString();
				pUIManager->GetHelp3()->AddHelpString(_S(3294, "�۽��� ������ ȥ�ڼ��� ���� �������� �� �������� ������ �ӹ��� �����ϴ� ���� �����Դϴ�. �����ϰ��� �ϴ� �ӹ��� ����� �����ϸ� �ӹ��� ����� ���� & ���������� Ȯ���� �� ������ ������ Ŭ���ϸ� �ڵ����� �ش� �۽��� �������� �̵��˴ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3295, "�� �۽��� ������ ���� ���ؼ��� ���������� ������� �ʿ��� �� �ֽ��ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3296, "�� �۽��� ���������� ��� �Ϲݰ����� ������������ ����Ǹ� �۽��� ���� ���� ��ų�� ����� �� �ֽ��ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3297, "�� �ӹ��� �ϼ� �ϸ� �ڵ����� ������ ��ȯ�Ǹ�, ���� �����Ϳ��� ������ ���� �� �ֽ��ϴ�."));
				pUIManager->GetHelp3()->OpenHelp(this);
			}
			// Create quest message box
			pUIManager->CreateMessageBoxL( _S( 99,"����Ʈ" ), UI_QUEST, MSGLCMD_QUEST_REQ );		
			
			CTString	strNpcName = CMobData::getData(iMobIndex)->GetName();
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, TRUE, strNpcName, -1, 0xE18600FF );
			
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, TRUE, _S( 581, "������ � ������ �����Ű���?" ), -1, 0xA3A1A3FF );			

// 			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1683, "�߷� ����" ), QUEST_KILL_BOSS );			
// 			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1684, "���� ����" ), QUEST_SAVE_PRINCESS );		
// 			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1685, "����ī ����" ), QUEST_AZAKA_RAVINE );	
//			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1686, "������ ��" ), QUEST_GATE_OF_DIMENSION );
			CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_QUEST_REQ);
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1686, "������ �� ����" ), QUEST_GATE_OF_DIMENSION );
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1874, "����Ѵ�."  ) );
		}
	}
 	else if(iMobIndex == 336 )  	// 2006 X-Mas event Snowman [12/11/2006 Theodoric]
 	{
 		pUIManager->CreateMessageBoxL(_S(100,"�̺�Ʈ"),UI_QUEST,MSGLCMD_QUEST_REQ);
		CTString strNpcName = CMobData::getData(iMobIndex)->GetName();
 		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  strNpcName,-1,0xE18600FF);
 		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3175,"�޸� ũ��������!! ��� ����� ��ȭ��!!"),-1,0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3176,"��ȭ�� ��ȣ�ϴ� ������ ���� �Ϸ� ���� ã�� ���̽��ϱ�?"),-1,0xa3a1a3ff);
 		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3177,"���� ���� �帱 �� �ִ� ���̶��, ũ�������� �������� �����̵� ���� �帮�ڽ��ϴ�."),-1,0xa3a1a3ff);
 		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  CTString(" "));		
 		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3169, "ũ����Ʈ���� �̺�Ʈ" ), EVENT_XMAS_2006 );	
 		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1874, "����Ѵ�."  ) );	
 	}
	// WSS_MINIGAME 070420 -------------------------------------------------------------->>
	else if(iMobIndex == 340 )  	// 2006 X-Mas event Snowman [12/11/2006 Theodoric]
 	{
		// [100518: selo] ���������� ���̸� �޽��� �ڽ��� ���� �ʴ´�.
		if( pUIManager->GetMinigame()->IsVisible() == FALSE )
		{
			pUIManager->CreateMessageBoxL(_S(100,"�̺�Ʈ"),UI_QUEST,MSGLCMD_QUEST_REQ);
			CTString strNpcName = CMobData::getData(iMobIndex)->GetName();
			if (IS_EVENT_ON(TEVENT_GOMDOLI))
			{
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  strNpcName,-1,0xE18600FF);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3420, "�ȳ��ϼ���. ���� ��ξ�! ������ '��Ÿ�Ͻ���'�� ����� ���Դϴ�."),-1,0xa3a1a3ff);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3421, "���� ��ô� ���δ��� �����ϱ�� ������ ���̸��� ������� �ټ� �հ����� ��� ������ �ҳ�ó�� ������."),-1,0xa3a1a3ff); 		
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3422, "���� �츮 ���δ��� �����ϴ� �Ϳ��� ��̸� ���� ������ ������ ������ ����ôٰ� �׸� ū ������ ���ܹ��Ƚ��ϴ�."),-1,0xa3a1a3ff);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3423, "���δԲ����� '���� �������� ����� �������� �������� �渶���� ����� �ϼ��� ���� ���� ���� ���� ���� �� ����. "),-1,0xa3a1a3ff);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3424, "���̸��� ����� ���Ե鲲 ������ ���� ã�ƴ޶�� ��Ź�Ϸ�����' ��� ������ �����ϼ̽��ϴ�. "),-1,0xa3a1a3ff);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3425, "�׷��� ���� ���δ��� ������ ���� ã���ֽ� ������ ������ ���̸��� ��� ��� ������ ���м����ϰ� �ֽ��ϴ�."),-1,0xa3a1a3ff);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3426, "�������� ��� ã���� �Ϳ��� ��̵鿡�� ������ �� �� �����ٵ��������ֽðڽ��ϱ�?"),-1,0xa3a1a3ff);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3427, "�̺�Ʈ �����ϱ�" ), EVENT_MINIGAME );	
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1874, "����Ѵ�."  ) );
			}
			else if (IS_EVENT_ON(TEVENT_XMAS_2007))
			{
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  strNpcName, -1, 0xE18600FF);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3420, "�ȳ��ϼ���. ���� ��ξ�! ������ '��Ÿ�Ͻ���'�� ����� ���Դϴ�."), -1, 0xa3a1a3ff);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3421, "���� ��ô� ���δ��� �����ϱ�� ������ ���̸��� ������� �ټ� �հ����� ��� ������ �ҳ�ó�� ������."), -1, 0xa3a1a3ff); 		
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(5801, "���� �츮 ���δ��� �����ϴ� �Ϳ��� ��̸� ���� ��ŸŬ�ν� ������ ����ôٰ� �׸� ū ������ ���ܹ��Ƚ��ϴ�."), -1, 0xa3a1a3ff);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(5802, "���δԲ����� '���� �������� ����� �������� �������� �渶���� ����� �ϼ��� ��ŸŬ�ν��� ������ ���� ���� ���� ���� �� ����."), -1, 0xa3a1a3ff);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(5803, "���̸��� ����� ���Ե鲲 ������ ��Ÿ������ ã�ƴ޶�� ��Ź�Ϸ�����' ��� ������ �����ϼ̽��ϴ�."), -1, 0xa3a1a3ff);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(5804, "�׷��� ���� ���δ��� ��ŸŬ�ν� ������ ã���ֽ� ������ ������ ���̸��� ��� ��� ������ ���м����ϰ� �ֽ��ϴ�."), -1, 0xa3a1a3ff);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S(3426, "���� ������ ��� ã���� �Ϳ��� ���̵鿡�� ������ �� �� �����ٵ�.. �����ֽðڽ��ϱ�?"), -1, 0xa3a1a3ff);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3427, "�̺�Ʈ �����ϱ�"), EVENT_MINIGAME);
				pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1874, "����Ѵ�."));
			}
		}
 	}
	// -----------------------------------------------------------------------------------<<
	else if (iMobIndex == 341) // eons �ɳ��� �̺�Ʈ(������)
	{
		pUIManager->CreateMessageBoxL(_S(100, "�̺�Ʈ"), UI_QUEST, MSGLCMD_QUEST_REQ);
		CTString strNpcName = CMobData::getData(iMobIndex)->GetName();

		/**********************************************************************************************/
		// 2008��
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, strNpcName, -1, 0xE18600FF);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(3489, "���� �ɳ����� �����ϴ� �������Դϴ�. "), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4110, "���� �����Ͽ� ���ڰ� �ǿ� ����? �̰��� �� �۳⿡ ���� �����ֽ� ��������. �׷��� ���ε���."), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4111, "�� �ɳ����� �����ϴµ� ��� ���� ���µ� ������ ��� �� ������ �ּ���. �׷� ���� ���� ������ �帱����."), -1, 0xa3a1a3ff);

		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(4112, "��� �ǳ��ش�."), EVENT_SAKURA_2008);
		// 2008��
		/*********************************************************************************************/

		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1874, "����Ѵ�."));
	}
	else if (iMobIndex == 342)
	{
		// empty : �ɳ����� ��� ���� ������
	}
	else if (iMobIndex == 484 || iMobIndex == 1304) // ũ�������� Ʈ�� (2007)
	{
		pUIManager->CreateMessageBoxL(_S(100, "�̺�Ʈ"), UI_QUEST, MSGLCMD_QUEST_REQ);
		CTString strNpcName = CMobData::getData(iMobIndex)->GetName();

		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, strNpcName, -1, 0xE18600FF);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(3947, "�ܿ��� �Ǹ� �ٵ� ��ٰ��� ������ ���� ���� ������ �ҽ��� ����� �������� �ʽ��ϴ�."), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(3948, "�Ͼ� ���� ������ �ҿ��� ���� �̷���� �� ���� �ʳ���?"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(3949, "���ش� ������ ��ο��� �ູ�ϰ� ������ ũ�������� �Ǳ� �ٶ��ϴ�."), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(3950, "Merry Christmas"), -1, 0xa3a1a3ff);

		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3951, "ũ�������� Ʈ�� ����ϱ�"), EVENT_XMAS2007_DECO);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3952, "ũ�������� �ູ�ޱ�"), EVENT_XMAS2007_BLESSEDNESS);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1268, "����ϱ�"));
	}
	else if (iMobIndex == 455)
	{
		pUIManager->CreateMessageBoxL(_S(100,"�̺�Ʈ"), UI_QUEST, MSGLCMD_QUEST_REQ);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, (CTString)MD->GetName(), -1, 0xE18600FF);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,
			_S(3775, "���� ���� �ڵ��� ����!! ������ �츮���� ����!! ����ְ� ����� ������ ������ ������� �ְڴ�!!"),-1, 0xa3a1a3ff);
		
		if (IS_EVENT_ON(A_EVENT_HOLLOWEEN))
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3776, "�Ǹ����� �Ӹ��� ���޹ޱ�"), EVENT_HALLOWEEN2007_DEVILHAIR);
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3777, "�����ٱ��Ͽ� �����ޱ�"), EVENT_HALLOWEEN2007_CANDYBASKET);
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3778, "ȣ�ڸӸ� Ż ��ȯ�ޱ�"), EVENT_HALLOWEEN2007_PUMKINHEAD);
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(5108, "�ҷ��� ��ũ�� ���� �ޱ�"), EVENT_HALLOWEEN2007_WITCHHAT);
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3780, "ȣ�ڱ�ȯ �ޱ�"), EVENT_HALLOWEEN2007_PUMKIN);
		}
		
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1874, "����Ѵ�."));
	}
	else  if(iMobIndex == 254 )
	{	// ��� �̺�Ʈ NPC ����....wooss 051031
		// Create Event Message Box
		pUIManager->CreateMessageBoxL(_S(100,"�̺�Ʈ"),UI_QUEST,MSGLCMD_QUEST_REQ);
		CTString strNpcName = CMobData::getData(iMobIndex)->GetName();
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,TRUE, strNpcName,-1,0xE18600FF);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,TRUE, _S(2204,"���� �Ϸ� ���� ã�� ���̳���?"),-1,0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,TRUE, _S(2205,"���� ���� �帱 �� �ִ� ���� �ִٸ� ���� �帮�ڽ��ϴ�."),-1,0xa3a1a3ff);
		
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_QUEST_REQ);
		
		//WSS_GUILD_MASTER 070411 ----------------------->>
		if( IS_EVENT_ON(TEVENT_PARENTS_2007)||IS_EVENT_ON(TEVENT_CHILDREN_2007)||IS_EVENT_ON(TEVENT_TEACHER_2007) )
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3395, "������ �� �̺�Ʈ" ), EVENT_MAY );	 		
		}
		// ----------------------------------------------<<
		if( IS_EVENT_ON(TEVENT_OX_QUIZ) )
		{
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(2616, "O.X �̺�Ʈ �� ����" ), EVENT_OX_GOZONE );
		}
#ifdef NETCAFE_CAMPAIGN
		if( _pNetwork->MyCharacterInfo.lLocation == BILL_LOCATION_PCBANG )
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,FALSE,_S(2744, "NetCafe ķ����" ),EVENT_NETCAFE_BOX);			
		}
#endif

		// ---------- WORLDCUP EVENT wooss 060530 ------------------------------------------------>>
#ifdef WORLDCUP_ITEM
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 2795, "��±��� ���߱� �̺�Ʈ" ), WIN_SELECT );
#endif
		// ---------- WORLDCUP EVENT wooss 060530 ------------------------------------------------<<

		if( IS_EVENT_ON(TEVENT_RAIN) )	//070621 ttos: �Ϻ��� ����� �̺�Ʈ , �±��� ��Ӵϳ� �̺�Ʈ ����
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,FALSE,_S(2753, "����� �̺�Ʈ" ),EVENT_RAINYDAY);			
		}

#ifdef WORLDCUP_GOLDENBALL
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 2796, "��� �� �̺�Ʈ" ), EVENT_GOLDENBALL );
#endif		

		if( IS_EVENT_ON(TEVENT_BUDDHIST) )
		{
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 2918, "�ұ� �к� ���� �̺�Ʈ ����" ), EVENT_BUDDHISM );
		}

		if (IS_EVENT_ON(TEVENT_CHUSEOK_2006))
		{
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1860, "�߼����� �̺�Ʈ" ), QUEST_HARVEST_MOON_DAY_EVENT2 );
		}

		if (IS_EVENT_ON(TEVENT_LUNARNEWYEAR_2008))
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _s("2008 ���� �̺�Ʈ"), EVENT_LOVE_LOVE);		
		}

		if (IS_EVENT_ON(A_EVENT_VALENTINE_DAY))
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3203, "���귯�� �̺�Ʈ"), EVENT_LOVE_LOVE);
		}

		if (IS_EVENT_ON(TEVENT_LOI_KRATHONG_TLD))	// [11/10/18 trylord] �±� ũ���� �̺�Ʈ
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(5600, "ũ�������� ��ȯ �ޱ�"), EVENT_LOI_KRATHONG);
		}

		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(5017, "�⼮ ��Ȳ ����"), ATTENDANT_DATE_REQ);
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1220, "����Ѵ�." ) );			
	}
	else if (iMobIndex ==1662 )
	{
		pUIManager->CreateMessageBoxL(CTString(MD->GetName()), UI_QUEST, MSGLCMD_QUEST_REQ);

		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, TRUE, _S(8509, "Hello, Warriors of Iris, you will need a buff token in order to recieve buffs from me. You can trade 4 buff fragments for 1 buff token by talking to me as well." ), -1, 0xa3a1a3ff );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8508, "Recieve Buffs" ), BUFF_REQ );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8507, "Trade Buff Fragments" ), BUFF_FRAG_REQ );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(139, "Cancel" ));
	}
	//ranking NPC (reborn master) dethunter12
	else if (iMobIndex == 1729) 
	{
		pUIManager->CreateMessageBoxL(CTString(MD->GetName()), UI_QUEST, MSGLCMD_QUEST_REQ);

		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, TRUE, _S(8337, "Hello! Welcome to reborn system!" ), -1, 0xa3a1a3ff );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8338, "Start a new reborn" ), MSGLCMD_REBORN_REQ );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8342, "Check your reborn" ), MSGLCMD_REBORN_CHECK_REQ );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8370, "Ranking reborn" ), MSGLCMD_REBORN_RANKING_REQ );
		//pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8371, "Ranking summon" ), MSGLCMD_RANKING_SUMMON_REQ );
		//pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8372, "Ranking pvp" ), MSGLCMD_RANKING_PVP_REQ );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(139, "Cancel" ));
	}
	//Class Change NPC Dethunter12
	else if (iMobIndex == 1730) 
	{
		pUIManager->CreateMessageBoxL(CTString(MD->GetName()), UI_QUEST, MSGLCMD_QUEST_REQ);

		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, TRUE, _S(8330, "Change class description" ), -1, 0xa3a1a3ff );

		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8323, "Transform to Healer" ), MSGLCMD_EXCHANGE_HEALER );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8324, "Transform to Knight" ), MSGLCMD_EXCHANGE_KNIGHT );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8325, "Transform to Mage" ), MSGLCMD_EXCHANGE_MAGE );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8326, "Transform to NightShadow" ), MSGLCMD_EXCHANGE_NIGHTSHADOW );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8327, "Transform to Rogue" ), MSGLCMD_EXCHANGE_ROGUE );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8328, "Transform to Sorcerer" ), MSGLCMD_EXCHANGE_SORCERER );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(8329, "Transform to Titan" ), MSGLCMD_EXCHANGE_TITAN );
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(9356, "Transform to Ex-Rogue"), MSGLCMD_EXCHANGE_EXROGUE);
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(9357, "Transform to ArchMage" ), MSGLCMD_EXCHANGE_ARCHMAGE);

		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(139, "Cancel" ));
	}

	else if (iMobIndex == 1832)  //pwesty
	{
		pUIManager->CreateMessageBoxL(CTString(MD->GetName()), UI_QUEST, MSGLCMD_QUEST_REQ);

		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(9385, "Exchange Wings"), -1, 0xa3a1a3ff);

		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, CTString(_pNetwork->GetItemName(20630)), 0);	//����� �������ü�
		//pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(9384, "Exchange Wings to Healer"), MSGLCMD_EXCHANGE_HEALER);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(9386, "Exchange Wings to Knight"), MSGLCMD_EXCHANGE_KNIGHT);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(9387, "Exchange Wings to Mage"), MSGLCMD_EXCHANGE_MAGE);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(9388, "Exchange Wings to NightShadow"), MSGLCMD_EXCHANGE_NIGHTSHADOW);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(9389, "Exchange Wings to Rogue"), MSGLCMD_EXCHANGE_ROGUE);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(9390, "Exchange Wings to Sorcerer"), MSGLCMD_EXCHANGE_SORCERER);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(9391, "Exchange Wings to Titan"), MSGLCMD_EXCHANGE_TITAN);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(9392, "Exchange Wings to Ex-Rogue"), MSGLCMD_EXCHANGE_EXROGUE);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(9393, "Exchange Wings to ArchMage"), MSGLCMD_EXCHANGE_ARCHMAGE);

		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(139, "Cancel"));
	}
	//Dethunter12 trader shop id
	else if (MD->IsMultiExchange()) {
		pUIManager->CreateMessageBoxL(_S(100, "�̺�Ʈ"), UI_QUEST, MSGLCMD_QUEST_REQ);
		CTString strNpcName = CMobData::getData(iMobIndex)->GetName();
		
		if (IS_EVENT_ON(TEVENT_SONGKRAN))
		{
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, TRUE, _S( 7032, "�±��� ���� ��ũ���� �����Ͽ� ������ ��ȯ �̺�Ʈ�� ���� �˴ϴ�..." ), -1, 0xA3A1A3FF );
		}
		
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_QUEST_REQ);
		
		if(IS_EVENT_ON(TEVENT_SONGKRAN))
		{
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 3275, "��ũ�� ���� �̺�Ʈ" ), EVENT_SONGKRAN );
		}

		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1874, "����Ѵ�."));
	}
	else if (iMobIndex == 408) // �̺�Ʈ ������
	{
		pUIManager->CreateMessageBoxL(_S(100, "�̺�Ʈ"), UI_QUEST, MSGLCMD_QUEST_REQ);
		CTString strNpcName = CMobData::getData(iMobIndex)->GetName();

		// if (IS_EVENT_ON(TEVENT_SONGKRAN))
		// {
		// 	pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, TRUE, _S( 7023, "�±��� ���� ��ũ���� �����Ͽ� ������ ��ȯ �̺�Ʈ�� ���� �˴ϴ�..." ), -1, 0xA3A1A3FF );
		// }
		// else
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, strNpcName, -1, 0xE18600FF);
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(3613, "�ȳ��ϼ���. ���� �糪�ý� ���� �����ܿ��� �İߵ� �̺�Ʈ �������Դϴ�."), -1, 0xa3a1a3ff);
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(3614, "�糪�ý��� ������ ������ ������� ������ �ΰ����� �پ �γ��� ��ü�� ���� õ�ε��� ��� �־��ٰ��� �������� â���ſ� ���� ������� ������ ��������̿���."), -1, 0xa3a1a3ff);
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(3615, "Ư���� ��ġ�� �����Ǿ� ���� ������ ���� �ֱ�� ���̸����� �����̳� �������� ���ʿ��� �������� Ȯ���� �� �ִ� ��ġ���� �����ϱ⵵ �մϴ�."), -1, 0xa3a1a3ff);
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, CTString(" "));
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(3616, "�׷���, �̹��� �����Ϸ� ���� ã�ƿ��̳���?"), -1, 0xa3a1a3ff);
		}

		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_QUEST_REQ);
		
		// if(IS_EVENT_ON(TEVENT_SONGKRAN))
		// {
		// 	pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 3275, "��ũ�� ���� �̺�Ʈ" ), EVENT_SONGKRAN );
		// }

		// [100416: selo] ���þƴ� �η����� �̺�Ʈ �����Ѵ�.
		if (g_iCountry != RUSSIA)
		{
			if(MD->IsEvent())
			{
				g_bHasEvent = TRUE;
				pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 100, "�̺�Ʈ" ), QUEST_EVENT );				
			}
		}

		if (IS_EVENT_ON(TEVENT_BJMONO_2007))
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _s("SK BJ MONO ����� �ޱ�"), EVENT_BJMONO_2007_REQ);
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _s("SK BJ MONO ����� ��ȯ"), EVENT_BJMONO_2007_CHANGE_REQ);
		}
		if (IS_EVENT_ON(TEVENT_TG2007_1000DAYS))
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3828, "��Ʈī���� 1000�� ������ �ޱ�"), EVENT_TG2007_1000DAYS_CAP);
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3829, "������ ���׷��̵�"), EVENT_TG2007_1000DAYS_CAP_UPGRADE);
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(3830, "���� �ޱ� �̺�Ʈ"), EVENT_TG2007_1000DAYS_FIRECRACKER);
		}

		if (IS_EVENT_ON(TEVENT_TG2007_SCREENSHOT)) // WSS_TG2007 2007/09/14
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _s("�����ޱ� �̺�Ʈ"), EVENT_TG2007_SCREENSHOT);			
		}

		if (IS_EVENT_ON(TEVENT_CHAOSBALL)) // WSS_TG2007 2007/09/14
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(4118, "���̸��� ���� �̺�Ʈ [ī���� ���� �����!]"), EVENT_CHAOSBALL);			
		}

		if (IS_EVENT_ON(TEVENT_ADD_UP_AFRON_2009))
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(4773, "�������� ���ǰ �ޱ�"), EVENT_ADD_UP_NEW_AFRON);
		}

		// ($E_WC2010) [100514: selo] 2010 ���ư� ������ �޴�
		if (IS_EVENT_ON(TEVNET_WORLDCUP_2010_TOTO))
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(4900, "��±� �����ϱ� �̺�Ʈ �ȳ�"), EVENT_WOLRDCUP_2010_EVENT2);
		}
		if (IS_EVENT_ON(TEVNET_WORLDCUP_2010_TOTO_STATUS))
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(4900, "��±� �����ϱ� �̺�Ʈ �ȳ�"), EVENT_WOLRDCUP_2010_EVENT2_STATUS);
		}
		if (IS_EVENT_ON(TEVNET_WORLDCUP_2010_TOTO_GIFT))
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(4900, "��±� �����ϱ� �̺�Ʈ �ȳ�"), EVENT_WOLRDCUP_2010_EVENT2_GIFT);
		}
		if (IS_EVENT_ON(TEVNET_WORLDCUP_2010_ATTENDANCE))
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(4901, "���� �̺�Ʈ �ȳ�"), EVENT_WOLRDCUP_2010_EVENT3);
		}
		if (IS_EVENT_ON(TEVENT_PROMOTION2))
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(2404, "���� �̺�Ʈ"), EVENT_PROMOTION2);
		}

		// [2011/01/18 : Sora] �⼮ �̺�Ʈ
		if( pUIManager->GetNotice()->IsAttendanceEventOn() )
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(5345, "���� �⼮�̺�Ʈ ����ޱ�"), EVENT_ATTENDANCE_2011); 

		// [2/17/2011 kiny8216] �޸� ���� ���� �̺�Ʈ
		if ( IS_EVENT_ON(TEVENT_COMEBACK) )
		{
			if(!(g_iCountry == GERMANY && _pNetwork->m_iServerGroup == 8))
			{
				pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 5353, "�޸����� ���� �����ޱ�" ), EVENT_COMEBACK );
			}
		}
		// [2/17/2011 kiny8216] ���� �̺�Ʈ
		if ( IS_EVENT_ON(TEVENT_BIRTHDAY) )
		{
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 5354, "���� ���� �ޱ�" ), EVENT_BIRTHDAY_GIFT );
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 5355, "���� Ȯ���ϱ�" ), EVENT_BIRTHDAY_INFO );
		}

		// [2011/11/14 : Sora] �±� ���� ź���� �̺�Ʈ
		if( IS_EVENT_ON( TEVENT_TLD_KING_BIRTHDAY ) )
		{
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 5602, "����ź���� �������� ��ȯ�ޱ�" ), EVENT_KB_EXCHAGE_HEART );
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 5603, "����ź���� �̺�Ʈ�ǻ� ��ȯ�ޱ�" ), EVENT_KB_EXCHAGE_FLAG );
		}

		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(5522, "[����]���� ���� ��ȯ�ϱ�" ), EVENT_TREASURE_MAP );
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1874, "����Ѵ�."));
	}
	else if( iMobIndex == 834 ) // �Ǵн� Ŭ�� ������
	{
		pUIManager->CreateMessageBoxL(_S(100, "�̺�Ʈ"), UI_QUEST, MSGLCMD_QUEST_REQ);
		CTString strNpcName = CMobData::getData(iMobIndex)->GetName();

		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, strNpcName, -1, 0xE18600FF);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4225, "�������. �Ǵн� Ŭ���� ���� ���� ȯ���մϴ�"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _s(" "));
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4226, "���̸��� ������� ������ �����ϰ� ���� ������ �׾� 100���� �̻��� �Ǿ��ٸ� ���ο� ĳ���͸� �����Ͽ� �Ǵн��� �� �� �ֽ��ϴ�."), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4227, "�Ǵн��� �Ǹ� �Ʒ��� ���� ������ ���� ������ Ŭ�����麸�� �� �� ���� ������ �� �� �ְ� �˴ϴ�."), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _s(" "));
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4228, "�Ǵн� ��������"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4229, "1. 100���� �̻��� ĳ���͸� ������ ������ ���Ӱ� ������ �ű� ĳ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4249, "2. �Ǵн� Ŭ�� ���Ա��� ������ ĳ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _s(" "));
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4230, "�Ǵн� ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4231, "1. �Ǵн��� ���"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4250, "ĳ���� ������ 35�� ���(�⺻ ��������Ʈ ����)"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4251, "���õ�, �Ǵн� ���ʽ� ��������Ʈ 30�� �߰� ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4232, "2. �Ǵн��� �ູ"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4252, "����&���� ���ݷ�/���� ����5%���(100���� �������� ����)"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4253, "3. �Ǵн��� ��Ȱ"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4254, "��� �� ���ڸ����� ��Ȱ�� ������ ������ ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4233, "4. �Ǵн��� ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4255, "�Ǵн� ���� ����(�Ⱓ ������, �ڽ�Ƭ ������ �����ֹ��� ��밡��) ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4256, "�Ǵн� ���� ��� ��Ʈ ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4257, "�� ���� 1�� �Ǵн��� ������ [�Ǵн��� ����] ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _s(" "));
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_QUEST_REQ);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(4234, "�Ǵн��� ����Ѵ�."), EVENT_PHOENIX_REQ);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1268, "����ϱ�"));
	}
	else if( iMobIndex == 899 || iMobIndex == 900 || iMobIndex == 1048) //��Ŵ��� npc
	{
		pUIManager->GetAuction()->OpenAuction(iMobIndex, m_fNpcX, m_fNpcZ);
	}
	else if (iMobIndex == 2050) // demi god pwesty
	{
		pUIManager->CreateMessageBoxL(_S(100, "�̺�Ʈ"), UI_QUEST, MSGLCMD_QUEST_REQ);
		CTString strNpcName = CMobData::getData(iMobIndex)->GetName();

		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, strNpcName, -1, 0xE18600FF);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(9410, "�������. �Ǵн� Ŭ���� ���� ���� ȯ���մϴ�"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _s(" "));
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(9411, "���̸��� ������� ������ �����ϰ� ���� ������ �׾� 100���� �̻��� �Ǿ��ٸ� ���ο� ĳ���͸� �����Ͽ� �Ǵн��� �� �� �ֽ��ϴ�."), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(9412, "�Ǵн��� �Ǹ� �Ʒ��� ���� ������ ���� ������ Ŭ�����麸�� �� �� ���� ������ �� �� �ְ� �˴ϴ�."), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _s(" "));
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(9413, "�Ǵн� ��������"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(9414, "1. 100���� �̻��� ĳ���͸� ������ ������ ���Ӱ� ������ �ű� ĳ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(9415, "2. �Ǵн� Ŭ�� ���Ա��� ������ ĳ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _s(" "));
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(9416, "�Ǵн� ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(9417, "1. �Ǵн��� ���"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(9418, "ĳ���� ������ 35�� ���(�⺻ ��������Ʈ ����)"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(9419, "���õ�, �Ǵн� ���ʽ� ��������Ʈ 30�� �߰� ����"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _s(" "));
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_QUEST_REQ);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(9420, "�Ǵн��� ����Ѵ�."), EVENT_DEMIGOD_REQ);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1268, "����ϱ�"));
	} // demi god pwesty
// [070807: Su-won] EVENT_ADULT_OPEN
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// WSS_DRATAN_SIEGEWARFARE 070730 ----------------------------------------------->>
	else if( iMobIndex == 351)	// ���ź ���� ������ Ÿ��
	{	
		// Create Event Message Box
		pUIManager->CreateMessageBoxL(_S( 3671,"������ Ÿ�� ���� �޴�"),UI_QUEST,MSGLCMD_QUEST_REQ);
		CTString strNpcName = CMobData::getData(iMobIndex)->GetName();
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,TRUE, strNpcName,-1,0xE18600FF);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,TRUE, _S( 3672,"�ȳ��ϼ���. ���ִ�"),-1,0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,TRUE, _S( 3673,"�̰������� ���� ��ȣ�ϱ� ���� ���� Ÿ���� ��ġ�ϰ� ��ȭ, �����ϰų� ������ ��ȭ�� �� �ֽ��ϴ�."),-1,0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,TRUE, _S( 3674,"�ʿ��� ����� �����Ͻñ� �ٶ��ϴ�."),-1,0xa3a1a3ff);
		
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_QUEST_REQ);
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 3675, "Ÿ�� �����ϱ�" ), SIEGEWARFARE_MASTERTOWER1 );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 3676, "Ÿ�� ��ȭ�ϱ�" ), SIEGEWARFARE_MASTERTOWER2 );			
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 3677, "���� ��ȭ�ϱ�" ), SIEGEWARFARE_MASTERTOWER3 );			
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 3678, "������ Ÿ�� �����ϱ�" ), SIEGEWARFARE_MASTERTOWER4 );			
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1220, "����Ѵ�." ) );		
	}
	//----------------------------------------------
	//071129 ttos: �Ǹ� ���� NPC ȸ��
	else if(iMobIndex == 470)
	{
		// Create Event Message Box
		pUIManager->CreateMessageBoxL(_s( "������ �Ǹ� ������ȸ ȸ��"),UI_QUEST,MSGLCMD_QUEST_REQ);
//		CTString strNpcName = _pNetwork->GetMobName(iMobIndex);
//		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,TRUE, strNpcName,-1,0xE18600FF);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,TRUE, _s( "�ȳ��ϼ���. ���� ������ �Ǹ� ������ȸ ȸ���Դϴ�."),-1,0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,TRUE, _s( "���� ������ �Ǹ� ������ȸ������ �������� ������ �������� �����ϰ� �Ǹ� ������ �ϰ� �ֽ��ϴ�."),-1,0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ,TRUE, _s( "���� �ϰ� ��ǰ�� �ðܸ� �ֽø� �����ϰ� �ǸŸ� �ص帮�ڽ��ϴ�."),-1,0xa3a1a3ff);
		
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_QUEST_REQ);
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _s( "������ �Ǹ� ���� ����" ), CASH_PERSONSHOP_CLOSE );
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _s( "������ ��ǰ ȸ��" ), CASH_PERSONSHOP_ITEM );			
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _s( "������ ���� ȸ��" ), CASH_PERSONSHOP_NAS );			
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1220, "����Ѵ�." ) );		
	}
	// ------------------------------------------------------------------------------<<
	else if( iMobIndex == 893 ) //[ttos_2009_3_18]: �ϳ����� �� SK��ε��� ������ �̺�Ʈ
	{
		pUIManager->CreateMessageBoxL(_S(4449, "�ʺ� ������"), UI_QUEST, MSGLCMD_QUEST_REQ);
		CTString strNpcName = CMobData::getData(iMobIndex)->GetName();

		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, strNpcName, -1, 0xE18600FF);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4450, "���̸������������ ���� ��ȭ�� ���� ������ ���Ű��� ȯ���մϴ�!"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(8431, "���� ���� ���ܿ��� �İߵ� �ʺ�������� �̰��� ó�� ���� �����е鿡��"), -1, 0xa3a1a3ff);

		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_QUEST_REQ);
	
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(4455, "�ʺ� ���� ���� �ޱ�"), EVENT_HANAPOS_SK_EVENT, 0x33ccffff);
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1748, "NPC �ȳ�" ), NPC_HELP);
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1220, "����Ѵ�." ) );	
	}
	else if (iMobIndex == 1107) // �� ������ ������
	{
		pUIManager->CreateMessageBoxL(CTString(MD->GetName()), UI_QUEST, MSGLCMD_QUEST_REQ);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4948, "������ �ʴ� �̲����� ���� �̰����� �߱��� ���� �����ڿ�!"), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4949, "���� �� ���� ����� ���� �������� ��ģ ��ſ��� ���� ������ �����ϱ� ���� ���� �ð� ����� ��ٸ��� �־����."), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4950, "�� ������ ������ ����, ���� ���ݷ°� ������ 20% ��µȴ�ϴ�."), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4951, "�� ������ �����ϸ� ������ ������� �Ǹ�, 90���������� ������ Ǯ���� �ٽ� ������ ���� �� ������ ���� ã�� ������."), -1, 0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(4952, "����� ���� ���࿡ ���� �ູ�� �Բ� �ϱ�!"), -1, 0xa3a1a3ff);
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_QUEST_REQ);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(4953, "�������� ���� ���� �ޱ�"), MIDLEVEL_SUPPORT_REQ);
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1748, "NPC �ȳ�" ), NPC_HELP);
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1220, "����Ѵ�." ) );
	}
 	else if(iMobIndex == 1136 )	// [2010/08/25 : Sora] ADD_SUBJOB ������ ����
 	{
		if(_pNetwork->IsMySubJob(SUBJOB_MERCHANT))
		{
			CUIMsgBox_Info MsgInfo;
			MsgInfo.SetMsgBoxInfo( _S( 1748, "�ȳ�" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
			MsgInfo.AddString( _S( 5052, "�̹� �������� ��ϵǾ� �ֽ��ϴ�.") );
			pUIManager->CreateMessageBox( MsgInfo );	
			return;
		}

 		pUIManager->CreateMessageBoxL(CTString(MD->GetName()), UI_QUEST,MSGLCMD_QUEST_REQ);
		CTString strNpcName = CMobData::getData(iMobIndex)->GetName();
 		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  strNpcName,-1,0xE18600FF);
 		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S( 5053, "���� ���� ������ ���� ���� �ʰڳ�?"),-1,0xa3a1a3ff);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S( 5054, "��, ������ �ο� ������ �ս��� ���� �� �ִ� �ŷ����� ���� �̶��!"),-1,0xa3a1a3ff);
 		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  _S( 5055, "������ ������ �ǰ� �ʹٸ� ���� ã�ƿ��Գ�"),-1,0xa3a1a3ff);
 		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  CTString(" "));
 		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S( 5056, "�������� ���"), REGISTER_MERCHANT );
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S( 1748, "NPC �ȳ�" ), NPC_HELP);
 		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1874, "����Ѵ�."  ) );	
 	}
	else if (iMobIndex == 1137)
	{
		pUIManager->CreateMessageBoxL(CTString(MD->GetName()), UI_QUEST, MSGLCMD_QUEST_REQ);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S( 581, "������ � ������ �����Ű���?" ), -1, 0xA3A1A3FF );
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S( 5362, "��ĭ ��� Normal"), DUNGEON_DIFFICULTY_NORMAL);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S( 5363, "��ĭ ��� Hard"), DUNGEON_DIFFICULTY_HARD);
		pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1220, "����Ѵ�."));
	}
	else if (iMobIndex == 1734) //Val add new raid teleporter NPC
	{
	pUIManager->CreateMessageBoxL(CTString(MD->GetName()), UI_QUEST, MSGLCMD_QUEST_REQ);
	pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S(8543, "������ � ������ �����Ű���?"), -1, 0xA3A1A3FF);
	pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(8542, "��ĭ ��� Normal"), DUNGEON_DIFFICULTY_NORMAL_NEW);
	pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, FALSE, _S(1220, "����Ѵ�."));
	}

	else if (iMobIndex == 1574 || iMobIndex == 1575)
	{	// 1574 : ī�̷轺 ���� ������, 1575 ���� ���� ������.
		if( pUIManager->DoesMessageBoxExist( MSGLCMD_SYNDICATE_JEWEL_GIVE ) ) 
			pUIManager->CloseMessageBox(MSGLCMD_SYNDICATE_JEWEL_GIVE);

		GameDataManager* pGameData = GameDataManager::getSingleton();

		if (pGameData == NULL)
			return;

		CSyndicate* pSyndicateData = pGameData->GetSyndicate();

		if (pSyndicateData == NULL)
			return;

		CTString strSyndicateName = pSyndicateData->GetSyndicateName(_pNetwork->MyCharacterInfo.iSyndicateType);
		CTString strTmp;

		strTmp.PrintF(_S(6113, "â���� ������ �߰��ϼ̳���? [%s] ���븦 ���� ����� �ֽø� �����ϰ� ����ϰڽ��ϴ�."), strSyndicateName);

		pUIManager->CreateMessageBoxL(_S(6114, "â���� ���� ���"), UI_QUEST, MSGLCMD_SYNDICATE_JEWEL_GIVE);
		pUIManager->AddMessageBoxLString(MSGLCMD_SYNDICATE_JEWEL_GIVE, TRUE, strTmp, -1, 0xA3A1A3FF );
		pUIManager->AddMessageBoxLString(MSGLCMD_SYNDICATE_JEWEL_GIVE, FALSE, _S(6114, "â���� ���� ���"), SYNDICATE_JEWEL_GIVE);
		pUIManager->AddMessageBoxLString(MSGLCMD_SYNDICATE_JEWEL_GIVE, FALSE, _S(139, "���."));
	}
	else if (iMobIndex == 1543 || iMobIndex == 1544)
	{
		if( pUIManager->DoesMessageBoxExist( MSGLCMD_SYNDICATE_SECESSION_REQ ) ) 
			pUIManager->CloseMessageBox(MSGLCMD_SYNDICATE_SECESSION_REQ);

		pUIManager->CreateMessageBoxL(CTString(MD->GetName()), UI_QUEST, MSGLCMD_SYNDICATE_SECESSION_REQ);
		pUIManager->AddMessageBoxLString(MSGLCMD_SYNDICATE_SECESSION_REQ, TRUE, _S( 6122, "�ȳ��ϼ���! ���� �繫�Ҹ� ã���ּż� �����մϴ�. ������Ե��� ��û ������ ������ ��Ȯ�ϰ� ó���Ͽ��帮�ڽ��ϴ�. � ������ ���͵帱���?" ), -1, 0xA3A1A3FF );
		pUIManager->AddMessageBoxLString(MSGLCMD_SYNDICATE_SECESSION_REQ, FALSE, _S( 6123, "���� Ż�� ��û"), SYNDICATE_SECESSION);
		pUIManager->AddMessageBoxLString(MSGLCMD_SYNDICATE_SECESSION_REQ, FALSE, _S(139, "���"));
	}
	else 
	{
		// Create quest message box
		pUIManager->CreateMessageBoxL( _S( 99,"����Ʈ" ), UI_QUEST, MSGLCMD_QUEST_REQ );		
		
		CTString	strNpcName = CMobData::getData(iMobIndex)->GetName();
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, TRUE, strNpcName, -1, 0xE18600FF );
		
		if (iMobIndex == 1131) //[4/15/2011 ldy1978220] Juno Reform add NPC ������ Ʈ��Ʈ
		{
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S( 5382, "�츮 Ʈ��Ʈ ������ �Ÿ��� ������ �ӿ� �ΰ����� ��ȣ�ϴ� �ӹ��� �ް� �־���..." ), -1, 0xA3A1A3FF );
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S( 5383, "�嵥 ����������� ����� �� ���� �ϳ��� ���ϱ� �����ϸ鼭 �ΰ���� �Ÿ��� �����ϱ� �����ߴٳ�..." ), -1, 0xA3A1A3FF );
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S( 5384, "���� �����н��� �ູ�� ���� ������ ���п� �������� �ʾ�����..." ), -1, 0xA3A1A3FF );
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE,  CTString(" "));
			pUIManager->AddMessageBoxLString(MSGLCMD_QUEST_REQ, TRUE, _S( 5385, "�ڳ� ���� �������� �ʰڳ�?" ), -1, 0xA3A1A3FF );

		}
		else
		{
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, TRUE, _S( 581, "������ � ������ �����Ű���?" ), -1, 0xA3A1A3FF );
		}	
		// 2009. 05. 27 ������
		// �̾߱��Ѵ� ���� ó��
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_QUEST_REQ);	
		
		if(MD->IsEvent())
		{
			g_bHasEvent = TRUE;
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 100, "�̺�Ʈ" ), QUEST_EVENT );				
		}

		if( iMobIndex == 139 )		// �η��� NPC �ϰ��...
		{
#ifdef WEAPONCHANGE_EVENT
			pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1203, "���ⱳü �̺�Ʈ" ), QUEST_CHANGEWEAPON );			
#endif				
			if(IS_EVENT_ON(TEVENT_SAKURA))
			{
				pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 2536, "�����ǻ� ��ȯ" ), EVENT_CLOTHES_EXCHANGE );
			}

			if(IS_EVENT_ON(A_EVENT_COLLECT_BUG))
			{
				pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 2946, "���� ����ä�� �̺�Ʈ" ), EVENT_COLLECTBUGS );
			}
		}

		// [100208: selo] ������ ��ų�� ���
		if( iMobIndex == 276 )
		{
			// 1. #248 ����Ʈ�� �Ϸ��� �����̰�
			// 2. #4659 �������� ������ ���� ������
			// �׸��� ���� ���� ������ �ٽ� �ޱ�			
			if( CQuestSystem::QAT_DOING == CQuestSystem::Instance().GetQuestAllow(249) &&
				pUIManager->GetInventory() &&  
				pUIManager->GetInventory()->GetItemCount(4659) == 0 )
			{
				m_restoreQuestIndex = -1;
				m_restoreQuestItemIndex = -1;

				pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S(4818, "[�׸��� ���� ����] ������ �ٽ� �ޱ�"), QUEST_RESTORE_ITEM );
			}
		}

		// [2011/02/09 : Sora] ����� ����Ʈ ������ �ٽ� �ޱ�
		if( iMobIndex == 1049 )
		{
			if( CQuestSystem::QAT_ALREADY_DONE == CQuestSystem::Instance().GetQuestAllow(262) )
			{
				CTString strMessage;

				m_restoreQuestIndex = 262;
				m_restoreQuestItemIndex = 4696;

				strMessage.PrintF(_S(5358, "[%s] �ٽ� �ޱ�" ), _pNetwork->GetItemName( m_restoreQuestItemIndex ) );
				pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, strMessage, QUEST_RESTORE_ITEM );
			}
		}

		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1748, "NPC �ȳ�" ), NPC_HELP);
		pUIManager->AddMessageBoxLString( MSGLCMD_QUEST_REQ, FALSE, _S( 1220, "����Ѵ�." ) );			
	}
	
	m_iNpcIndex		= iMobIndex;
	m_iNpcVirIdx	= iMobVirIdx;
	g_bHasQuest		= bHasQuest;
}

// ----------------------------------------------------------------------------
// Name : MsgBoxLCommand()
// Desc :
// ----------------------------------------------------------------------------
void CUIQuest::MsgBoxLCommand( int nCommandCode, int nResult )
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString tv_str;

	switch( nCommandCode )
	{
	case MSGLCMD_RENUAL_EVENT:
		{
			if( nResult == QUEST_RENUAL_EVENT_OK )
			{
				pUIManager->GetSelectWord()->OpenSelectWord();						
				//!! ������ Ȯ�� �޼��� ������ 
			}
		}
		break;
	case MSGLCMD_HARVEST_MOON_DAY1:
		{
			pUIManager->CloseMessageBox( MSGCMD_HARVEST_MOON_DAY_EVENT_UPGRADE1 );
			pUIManager->CloseMessageBox( MSGCMD_HARVEST_MOON_DAY_EVENT_UPGRADE2 );
			pUIManager->CloseMessageBox( MSGCND_MOON_DAY_EVENT_GIVE_ITEM );
				
			CTString strMessage;
			CUIMsgBox_Info	MsgBoxInfo;
				
			//strMessage = _S( 1859, "�۹��� ���׷��̵� �Ͻðڽ��ϱ�?" );	
			if( nResult == QUEST_HARVEST_MOON_DAY_EVENT_UPGRADE1 )
			{
				strMessage = _S(3131, "������ ����ðڽ��ϱ�?" );
				MsgBoxInfo.SetMsgBoxInfo( _S( 1860,  "�߼����� �̺�Ʈ" ) , UMBS_OKCANCEL,
				UI_QUEST, MSGCMD_HARVEST_MOON_DAY_EVENT_UPGRADE1 );
			}
			else if( nResult == QUEST_HARVEST_MOON_DAY_EVENT_UPGRADE2 )
			{
				strMessage = _S(3132, "���� ������ ����ðڽ��ϱ�?" );
				MsgBoxInfo.SetMsgBoxInfo( _S( 1860,  "�߼����� �̺�Ʈ" ) , UMBS_OKCANCEL,
					UI_QUEST, MSGCMD_HARVEST_MOON_DAY_EVENT_UPGRADE2 );
			}
			else
			{
				break;
			}
						
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;
	case MSGLCMD_HARVEST_MOON_DAY2:
		{
			if( nResult == MSGCND_MOON_DAY_EVENT_GIVE_ITEM )
			{
				pUIManager->CloseMessageBox( MSGCMD_HARVEST_MOON_DAY_EVENT_UPGRADE1 );
				pUIManager->CloseMessageBox( MSGCMD_HARVEST_MOON_DAY_EVENT_UPGRADE2 );
				pUIManager->CloseMessageBox( MSGCND_MOON_DAY_EVENT_GIVE_ITEM );
				CTString strMessage;
				CUIMsgBox_Info	MsgBoxInfo;
				
				strMessage = _S( 1861, "�߼� �̺�Ʈ ����ǰ�� ���� �����ðڽ��ϱ�?" ); 
				MsgBoxInfo.SetMsgBoxInfo( _S( 1860,  "�߼����� �̺�Ʈ" ) , UMBS_OKCANCEL,
					UI_QUEST, MSGCND_MOON_DAY_EVENT_GIVE_ITEM );
				
				
				MsgBoxInfo.AddString( strMessage );
				pUIManager->CreateMessageBox( MsgBoxInfo );

			//	_pNetwork->SendChuseokExchange();
			}

		}
		break;
	case MSGLCMD_EVENT :
		{
			if( nResult == QUEST_RENUAL_EVENT )
			{
				CTString strMessage;
				pUIManager->CloseMessageBoxL( MSGLCMD_RENUAL_EVENT );

				strMessage = _S(2209, "���� ���߱� �̺�Ʈ" );	 
				pUIManager->CreateMessageBoxL( strMessage, UI_QUEST, MSGLCMD_RENUAL_EVENT );				
				pUIManager->AddMessageBoxLString( MSGLCMD_RENUAL_EVENT, TRUE, strMessage, -1,0xE18600FF );				

				strMessage = _S(2210, "�����Ͻ� �������� �κ��丮�� ���� �Ͻ�ä�� ������ ���� Ÿ��Ʋ�� �����Ͻø� �ϼ��� ������ ���� ������ ���޵˴ϴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_RENUAL_EVENT, TRUE, strMessage, -1, 0xA3A1A3FF );				
				strMessage = " ";
				pUIManager->AddMessageBoxLString( MSGLCMD_RENUAL_EVENT, TRUE, strMessage, -1, 0xA3A1A3FF );				
				strMessage = _S(2211, "�� �̹� �ѹ� ���޹��� ��ǰ�� ���ؼ��� �ٽ� ������ �ȵǹǷ� �����Ͻñ� �ٶ��ϴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_RENUAL_EVENT, TRUE, strMessage, -1, 0xA3A1A3FF );				
				strMessage = " ";
				pUIManager->AddMessageBoxLString( MSGLCMD_RENUAL_EVENT, TRUE, strMessage, -1, 0xA3A1A3FF );				
				
				pUIManager->AddMessageBoxLString( MSGLCMD_RENUAL_EVENT, FALSE, _S(2212, "���� Ÿ��Ʋ ����."  ), QUEST_RENUAL_EVENT_OK );		
				pUIManager->AddMessageBoxLString( MSGLCMD_RENUAL_EVENT, FALSE, _S( 1874, "����Ѵ�."  ) );			

			}
			else if( nResult == QUEST_TREASURE_BOX )
			{
				// ������ �޼��� ������.
				_pNetwork->SendEventTreasureList();
			}
			else if (nResult == EVENT_OPENBETAITEMGIFT)
			{
				_pNetwork->SendUsaOpenBetaGift();
			}
			else if( nResult == QUEST_HARVEST_MOON_DAY_EVENT1 )
			{
				CTString strMessage;
				pUIManager->CloseMessageBoxL( MSGLCMD_HARVEST_MOON_DAY1 );

				strMessage = _S( 1860, "�߼����� �̺�Ʈ" );	 
				pUIManager->CreateMessageBoxL( strMessage, UI_QUEST, MSGLCMD_HARVEST_MOON_DAY1 );				
				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, TRUE, strMessage, -1,0xE18600FF );				

				strMessage = _S(3122, "������ ���� �߼��� �¾Ƽ� ���մ� ������ ����� ���ðھ��?" );
				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, TRUE, strMessage, -1, 0xA3A1A3FF );				
				strMessage = _S(3123, "�ٸ� ���� ������ �� ������ �������� �Ұ���, ��, ������ ������ �ּ���." );
				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, TRUE, strMessage, -1, 0xA3A1A3FF );				
				strMessage = _S(3124, "������ �̺�Ʈ �Ⱓ ���� ���͸� ����ϸ� ���� �� ������ ���� 1���� �� 3���� ��ƿ��ø�" );
				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S(3125, "�̵��ӵ��� ���ݼӵ��� ���Ǵ� Ư���� ������ 1�� ����� �帮�ڽ��ϴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, TRUE, strMessage, -1, 0xA3A1A3FF );				
				strMessage = _S(3126, "�׸��� ���� 10���� ��ƿ��� ������������ ���� �� �ִµ�," );
				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S(3127, "���������� ���� ���� �����ϴ� �������� ������ �ָ� ����ǰ�� ���� �� �ֽ��ϴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = " ";
				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, TRUE, strMessage, -1, 0xA3A1A3FF );	
				strMessage = _S(3128, "��, ������ ����ٰ� �����ϸ� ����� ��ᰡ ��� �������, ���������� ����ٰ� �����ϸ� ���� 2���� ���� �˴ϴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = " ";
				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, TRUE, strMessage, -1, 0xA3A1A3FF );

				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, FALSE, _S(3129, "������ �����."  ), QUEST_HARVEST_MOON_DAY_EVENT_UPGRADE1 );
				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, FALSE, _S(3130, "���������� �����."  ), QUEST_HARVEST_MOON_DAY_EVENT_UPGRADE2 );
				pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY1, FALSE, _S( 1874, "����Ѵ�."  ) );			
			}
			else if(nResult ==  EVENT_COUPON )
			{
				if(pUIManager->DoesMessageBoxExist( MSGCMD_EVENT_COUPON_SENDNUM )) break;
				if(pUIManager->DoesMessageBoxExist( MSGCMD_NULL)) break;
				
				int tv_all = (INVEN_SLOT_ROW_TOTAL*INVEN_SLOT_COL);
				if ( pUIManager->GetInventory()->GetItemAll() > tv_all-5) {
					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(169,"�̺�Ʈ"),UMBS_OK,UI_NONE,MSGCMD_NULL);
					MsgBoxInfo.AddString(_S(116,"�κ��丮 ������ �����Ͽ� ������ ���� �� �����ϴ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);

				}
				else{
					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(169,"�̺�Ʈ"),UMBS_YESNO|UMBS_INPUTBOX,UI_QUEST,MSGCMD_EVENT_COUPON_SENDNUM);
					MsgBoxInfo.AddString(_S(2402,"�ش� ���� ��ȣ�� �Է��ϸ� ���ο� �ǻ��� ���� �� �ֽ��ϴ�."));
					MsgBoxInfo.AddString(_S(2403,"���� ��ȣ�� �Է��� �ֽʽÿ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
			}
			else if( nResult == EVENT_CONNECT )
			{
				_pNetwork->SendConnectItemReq();								
			}
			else if(nResult ==  EVENT_PROMOPACK )
			{
				CTString strMessage;
				pUIManager->CloseMessageBoxL( MSGLCMD_EVENT_PROMOPACK );

				strMessage = _S(3145, "���θ� ��Ű�� ��ǰ �̺�Ʈ" );	
				pUIManager->CreateMessageBoxL( strMessage, UI_QUEST, MSGLCMD_EVENT_PROMOPACK );				
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_PROMOPACK, TRUE, strMessage, -1,0xE18600FF );				

				strMessage = _S(3146, "���θ� ��Ű�� ��ǰ�� ������ ������ ��Ű���� ���� ���� key�� �Է��ϸ� ���Ӿ������� ����ǰ���� ���� �� �ִ� �̺�Ʈ�Դϴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_PROMOPACK, TRUE, strMessage, -1, 0xA3A1A3FF );				
				strMessage = " ";
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_PROMOPACK, TRUE, strMessage, -1, 0xA3A1A3FF );				
				
				strMessage = _S(3147, "���θ� ��Ű�� �̺�Ʈ ����ǰ" );
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_PROMOPACK, TRUE, strMessage, -1, 0xA3A1A3FF );	

				strMessage = _S(3148, "1. ���� HP, MP Ȯ������ 5����" );
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_PROMOPACK, TRUE, strMessage, -1, 0xA3A1A3FF );	
				strMessage = _S(3149, "2. A~E ��� �ɷ�ġ�� ���� �Ǽ��縮 ������ �� �Ѱ�" );
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_PROMOPACK, TRUE, strMessage, -1, 0xA3A1A3FF );	

				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_PROMOPACK, FALSE, _S( 3150, "���� Key �Է�"  ), EVENT_PROMO_KEY_ENTER );
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_PROMOPACK, FALSE, _S( 1874, "����Ѵ�."  ) );
			}
			// wooss 070305 
			// kw : WSS_WHITEDAY_2007 ------------------------------------------------------------------------------------->>
			else if( nResult == EVENT_WHITEDAY_2007 )
			{
				CTString strMessage;
				pUIManager->CloseMessageBoxL( MSGLCMD_WHITEDAY_2007 );

				strMessage = _S( 3238, "ȭ��Ʈ���� �̺�Ʈ" );	 
				pUIManager->CreateMessageBoxL( strMessage, UI_QUEST, MSGLCMD_WHITEDAY_2007 );				
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1,0xE18600FF );				

				strMessage = _S( 3239, "������ �ְ� ������ ����� ������ ������ ȭ��Ʈ���̸� �¾Ƽ� ���͵��� ������ �شٰ� �մϴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );				
				strMessage = _S( 3240, "�ÿ��� �ϴû� ������ ������ ��ȫ�� ������ �԰� ������ ������ �ֽðھ��?" );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );				
				strMessage = _S( 3241, "�ϴû� ���� 5���� ��ȫ�� 5���� ������ �ֽø� ������ ǥ�÷� ������� �ֹ� �� 1������ �������� �����ؼ� �ɾ�帮��," );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S( 3242, "���� 20���� ������ �ֽø� ���� ���� �´� �������� �帮�ڽ��ϴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );				
				strMessage = _S( 3243, "������� �ֹ��� �Ͻ������� ĳ������ �ɷ��� �����ִ� �ֹ��̸�, �������� ������ü�� ���������� ����� �޽����� ���� �� �ִ� �������Դϴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S( 3244, "�� ������� �ֹ� ����" );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S( 3245, "�ٶ��� ������� - �ֹ��� �ɸ� �������� 10�а� �̵��ӵ��� ���ȴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S( 3246, "���� ������� - �ֹ��� �ɸ� �������� 30�а� ���� 20 �����ȴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S( 3247, "��ø�� ������� - �ֹ��� �ɸ� �������� 30�а� ��ø�� 20 �����ȴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S( 3248, "������ ������� - �ֹ��� �ɸ� �������� 30�а� ������ 20 �����ȴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S( 3249, "ü���� ������� - �ֹ��� �ɸ� �������� 30�а� ü���� 50 �����ȴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S( 3250, "�η����� ������� - �ֹ��� �ɸ� �������� 30�а� ���� ���ݽ� ���� Ȯ���� ���� ĳ���� �������� 10�迡 �ش��ϴ� �������� ������." );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S( 3251, "�� �̺�Ʈ �Ⱓ : 2007�� 3�� 13�� ~ 3�� 27��" );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S( 3252, "�� �̺�Ʈ �Ⱓ ������ �����ִ� ���� �� �������� ��� ������ϴ�." );				
			
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, FALSE, _S( 3253, "������� �ֹ��� �޴´�."  ), EVENT_REWARD_1 );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, FALSE, _S( 3254, "�ϴû� �������� ��ȯ�Ѵ�."  ), EVENT_REWARD_2 );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, FALSE, _S( 3255, "��ȫ�� �������� ��ȯ�Ѵ�."  ), EVENT_REWARD_3 );
				pUIManager->AddMessageBoxLString( MSGLCMD_WHITEDAY_2007, FALSE, _S( 1874, "����Ѵ�."  ) );	
				
			}
			// --------------------------------------------------------------------------------------------------------------<<
			
			// [070705: Su-won] EVENT_SUMMER_2007
			else if( nResult == EVENT_SUMMER_2007 )
			{
				CTString strMessage;
				pUIManager->CloseMessageBoxL( MSGLCMD_SUMMER_2007 );

				strMessage = _S(3561, "�������� �̺�Ʈ" );	 
				pUIManager->CreateMessageBoxL( strMessage, UI_QUEST, MSGLCMD_SUMMER_2007 );				
				pUIManager->AddMessageBoxLString( MSGLCMD_SUMMER_2007, TRUE, strMessage, -1,0xE18600FF );				

				strMessage = _S(3566, "�������е��� ģ����� �������⸦�ߴ� ������ ���ø��� � ������ ���ư����� ���� ����?" );
				pUIManager->AddMessageBoxLString( MSGLCMD_SUMMER_2007, TRUE, strMessage, -1, 0xA3A1A3FF );				
				strMessage = _S(3567, "�����̸� ������ ���ø� ����ִ� ���� ���⸦ ������ �帮�ڽ��ϴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_SUMMER_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage.PrintF("�� %s", _S(3565, "�� �̺�Ʈ �Ⱓ : 2007�� 7�� 10��(ȭ) ~ 8�� 24��(ȭ)") );
				pUIManager->AddMessageBoxLString( MSGLCMD_SUMMER_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
				strMessage = _S(3568, "�� �����̴� ���� ���� �� �Һ�Ǹ�, �̺�Ʈ�Ⱓ ���� �� �Ѵ� �� ��밡���մϴ�." );
				pUIManager->AddMessageBoxLString( MSGLCMD_SUMMER_2007, TRUE, strMessage, -1, 0xA3A1A3FF );
			
				pUIManager->AddMessageBoxLString( MSGLCMD_SUMMER_2007, FALSE, _S(3569, "��������"  ), EVENT_REWARD_1 );
				pUIManager->AddMessageBoxLString( MSGLCMD_SUMMER_2007, FALSE, _S(3570, "����������"  ), EVENT_REWARD_2 );
				pUIManager->AddMessageBoxLString( MSGLCMD_SUMMER_2007, FALSE, _S( 1874, "����Ѵ�."  ) );	
				
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// [070807: Su-won] EVENT_ADULT_OPEN
			else if( nResult == EVENT_ADULT_MAGICCARD)
			{
				if( pUIManager->DoesMessageBoxLExist( MSGLCMD_EVENT_ADULT_MAGICCARD ) ) break;
				
				CTString strMessage;

				pUIManager->CreateMessageBoxL(_S(100,"�̺�Ʈ"), UI_QUEST, MSGLCMD_EVENT_ADULT_MAGICCARD);				

				strMessage = _S(3619, "���� �Ƴ��� �߿��� ���̵��� �� �ϳ��� ����ī�忡�� 2���� �׸� �ٶ��� ������ ���а� ��������.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_MAGICCARD, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3620, "�� ī�忡�� ������ �ɷ��־ �߸� �ǵ帮�� ������ ���� ���������� �𸣴µ�... ū���̳׿�!");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_MAGICCARD, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3621, "Ȥ�ö� �����̽� Aī��� ��Ʈ Aī�带 �߰��Ͻø� �� ������ ������ �ּ���! ������ ǥ�÷� ������� �����ֹ��� �ɾ� �帱����.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_MAGICCARD, TRUE, strMessage, -1, 0xA3A1A3FF);
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_MAGICCARD, TRUE,  CTString(" "));


				strMessage = _S(3244, "�� ������� �ֹ� ����");
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_ADULT_MAGICCARD, TRUE, strMessage, -1, 0xE18600FF );
				strMessage = _S(3245, "�ٶ��� �������-�ֹ��� �ɸ� �������� 10�а� �̵��ӵ��� ���ȴ�.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_MAGICCARD, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3246, "���� �������-�ֹ��� �ɸ� �������� 30�а� ���� 20 �����ȴ�.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_MAGICCARD, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3247, "��ø�� �������-�ֹ��� �ɸ� �������� 30�а� ��ø�� 20�����ȴ�.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_MAGICCARD, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3248, "������ �������-�ֹ��� �ɸ� �������� 30�а� ������ 20�����ȴ�.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_MAGICCARD, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3249, "ü���� �������-�ֹ��� �ɸ� �������� 30�а� ü���� 50�����ȴ�.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_MAGICCARD, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3250, "�η����� �������-�ֹ��� �ɸ� �������� 30�а� ���� ���ݽ� ���� Ȯ���� ���� ĳ���� �������� 10�迡 �ش��ϴ� �������� ������.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_MAGICCARD, TRUE, strMessage, -1, 0xA3A1A3FF);
				
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_MAGICCARD, FALSE, _S(3622, "����ī�� ���� �ޱ�"), 0);
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_MAGICCARD, FALSE, _S(1874,"����Ѵ�."));

			}
			else if( nResult == EVENT_ADULT_CHANGEJOB)
			{
				if( pUIManager->DoesMessageBoxLExist( MSGLCMD_EVENT_ADULT_CHANGEJOB ) ) break;

				CTString strMessage;

				pUIManager->CreateMessageBoxL(_S(100,"�̺�Ʈ"), UI_QUEST, MSGLCMD_EVENT_ADULT_CHANGEJOB);				

				strMessage = _S(3623, "�����̶�� ���� �׵��� ���� ������ �����̴ٴ� ���ű⵵ ������ �������� ���迡�� �� ����� ���� ������ �ȴٴ� ���̱⵵ ������.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_CHANGEJOB, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3624, "�׷� �ǹ̷� ������ �Ͻ� �е鲲 ���� ���� ����� Ư���� �����ؿ� �糪�ý� �ְ��� �ּ��簡 ���� ������ ������ Ư���� �帮�ڽ��ϴ�.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_CHANGEJOB, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3625, "���� �����ϱ� ���� �̰� �ѹ� ���ָ� ������ ������ �ؼ� ���� ������ ���� �����ϰ� �����ϱ� �� ���� ���� �ſ���.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_CHANGEJOB, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3626, "��! ��ǰ�� ������ ���� ���� ������� ���� �帮�� �����ϼ���.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_CHANGEJOB, TRUE, strMessage, -1, 0xA3A1A3FF);

				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_CHANGEJOB, FALSE, _S(3627, "���� ���� ��ǰ �ޱ�"), 0);
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_CHANGEJOB, FALSE, _S(1874,"����Ѵ�."));
			}
			else if( nResult == EVENT_ADULT_ALCHEMIST)
			{
				if( pUIManager->DoesMessageBoxLExist( MSGLCMD_EVENT_ADULT_ALCHEMIST ) ) break;

				CTString strMessage;

				pUIManager->CreateMessageBoxL(_S(100,"�̺�Ʈ"), UI_QUEST, MSGLCMD_EVENT_ADULT_ALCHEMIST);				

				strMessage = _S(3628, "���� Ź���� �����̽ÿ�. ��� ���� �׵��� ������ ��￩�� ������ ����� ����� ���ݼ��� ������ �´µ�...");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_ALCHEMIST, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3629, "�ٷ� �� ��� ������ �ٷ� ���ܰ��� �� ���� �������ִ� Ư���� ���������.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_ALCHEMIST, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3630, "������ �ߵǸ� ���õ� �� ��� ���� ���� ������ �̰� ���� ������� �ʼ�?");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_ALCHEMIST, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3631, "�ʹ� ����� ���Ƽ� ������� ����� ��� �������ִ� �̺�Ʈ�� �غ����ϴµ�, ������ ���ڼ�?");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_ALCHEMIST, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3632, "�̺�Ʈ �Ⱓ���� ���� ���� ��Ḹ ������ ���� �Ǵ� �δ� ���� �� ���ٿ�, ����.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_ALCHEMIST, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3633, "����, ������ �õ��ϱ� ���� �̰� �˾Ƶνÿ�. ��~�� ���� ���ڸ� ���� ���ݼ��� ���а� �Ǳ⵵ �ϴµ� �����ϸ� ��� ������ ���� ������ ��� ����� ���� ���� �ְ�,");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_ALCHEMIST, TRUE, strMessage, -1, 0xA3A1A3FF);
				strMessage = _S(3634, "40���� �̻��� ���� ���� �� ���ٴ� �͵� ����ϸ� ���ڼ�.");
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_ALCHEMIST, TRUE, strMessage, -1, 0xA3A1A3FF);
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_ALCHEMIST, TRUE,  CTString(" "));
				
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_ALCHEMIST, FALSE, _S(3427, "�̺�Ʈ �����ϱ�"), 0);
				pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_ADULT_ALCHEMIST, FALSE, _S(1874,"����Ѵ�."));

			}			
			else if( nResult == EVENT_SHOOT )
			{
				pUIManager->CloseMessageBox( MSGCMD_EVENT_SHOOT );

				CTString strMessage;
				// Create message box of remission
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo( _S(3658, "��ħ���� ���!" ), UMBS_OKCANCEL, UI_QUEST, MSGCMD_EVENT_SHOOT );
				strMessage.PrintF( _S(3659, "��ħ���� ���! �̺�Ʈ�� �����Ͻðڽ��ϱ�?" ) );
				MsgBoxInfo.AddString( strMessage );
				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
			// [070807: Su-won] EVENT_ADULT_OPEN
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if( nResult == EVENT_TG2007_FRUITFULL ) // WSS_TG2007 2007/09/14 ǳ�� �̺�Ʈ
			{
				pUIManager->CreateMessageBoxL(_S(100,"�̺�Ʈ"),UI_QUEST,MSGLCMD_TG2007_FRUITFULL);
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, TRUE, _S( 3761,"ǳ���̺�Ʈ"),0x6BD2FFFF);
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, TRUE, _S( 3766,"�ܰ躰�� ��Ʈī���� ������ ���� �ܰ�� ���׷��̵带 �Ͻ÷��� ���ɾ������� �ʿ��մϴ�.") );
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, TRUE, _S( 3767,"�����ܰ���� ���׷��̵�� ���� Ȯ���� ���׷��̵� �Ǹ� ������ ���� �ֽ��ϴ�.") );
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, TRUE, _S( 3768,"���׷��̵�� ��Ʈī���� ������ ����ǰ�� ��ȯ�ϰų� ���� �ܰ�� ���׷��̵� �� �� �ֽ��ϴ�.") );
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, TRUE, _S( 3769,"����ǰ�� �� �ܰ躰�� �ٸ� Ȯ���� ȹ���� �� �ֽ��ϴ�.") );
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, TRUE, _S( 1866,"����ǰ"),0xA3A1A3FF );
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, TRUE, _S( 3770,"������"),0xA3A1A3FF );
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, TRUE, _S( 3771,"��� ������ 3��"),0xA3A1A3FF );
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, TRUE, _S( 3772,"����â�� 7�� Ȯ��ī��"),0xA3A1A3FF );
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, TRUE, _S( 3773,"������ ����"),0xA3A1A3FF );
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, TRUE, _S( 3774,"�ǰ��� ����"),0xA3A1A3FF );
 				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, FALSE, _S( 1872,"�۹��� ���׷��̵� �Ѵ�." ), EVENT_REWARD_1 );
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, FALSE, _S( 1873,"����ǰ�� ���޹޴´�." ), EVENT_REWARD_2 );
				pUIManager->AddMessageBoxLString(MSGLCMD_TG2007_FRUITFULL, FALSE, _S( 1874,"����Ѵ�."));				
			}
			else if( nResult == EVENT_RED_TREASUREBOX )
			{
				int iTreasureBoxLevel =0;
				if( pUIManager->GetInventory()->GetItemCount(2660) )	//5Lv ������ ��������
				{
					iTreasureBoxLevel =5;

					if( _pNetwork->MyCharacterInfo.level < 5 )
					{
						_pNetwork->ClientSystemMessage( _S( 1757, "������ �����Ͽ� ���� ���ڸ� ���� �����ϴ�." ), SYSMSG_ERROR );
						return;
					}
				}
				else if( pUIManager->GetInventory()->GetItemCount(2661) )	//12Lv ������ ��������
				{
					iTreasureBoxLevel =12;

					if( _pNetwork->MyCharacterInfo.level < 12 )
					{
						_pNetwork->ClientSystemMessage( _S( 1757, "������ �����Ͽ� ���� ���ڸ� ���� �����ϴ�." ), SYSMSG_ERROR );
						return;
					}
				}
				else if( pUIManager->GetInventory()->GetItemCount(2662) )	//16Lv ������ ��������
				{
					iTreasureBoxLevel =16;

					if( _pNetwork->MyCharacterInfo.level < 16 )
					{
						_pNetwork->ClientSystemMessage( _S( 1757, "������ �����Ͽ� ���� ���ڸ� ���� �����ϴ�." ), SYSMSG_ERROR );
						return;
					}
				}
				else
				{
					_pNetwork->ClientSystemMessage( _S( 1758, "���� ���ڰ� �����ϴ�." ), SYSMSG_ERROR );
					return;
				}

				CTString strMessage, strCount;

				pUIManager->CloseMessageBoxL( MSGLCMD_RED_TREASUREBOX_EVENT );
					
				pUIManager->CreateMessageBoxL( _S(100,"�̺�Ʈ"), UI_QUEST, MSGLCMD_RED_TREASUREBOX_EVENT );			
				
				pUIManager->AddMessageBoxLString( MSGLCMD_RED_TREASUREBOX_EVENT, TRUE, _S(4010, "������ �������� �̺�Ʈ" ), -1, 0xE18600FF );	
				strMessage.PrintF( _S(4018, "%d Lv ������ �������ڸ� ���� �Ʒ� �������� ���޵˴ϴ�.  %d Lv ������ �������ڸ� ����ðڽ��ϱ�?" ), iTreasureBoxLevel, iTreasureBoxLevel );	
				pUIManager->AddMessageBoxLString( MSGLCMD_RED_TREASUREBOX_EVENT, TRUE, strMessage, -1, 0xA3A1A3FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_RED_TREASUREBOX_EVENT, TRUE, CTString("  "), -1, 0xA3A1A3FF );
				strMessage.PrintF( _S(4019, "%d Lv ������ �������� ���� ǰ��"), iTreasureBoxLevel);	
				pUIManager->AddMessageBoxLString( MSGLCMD_RED_TREASUREBOX_EVENT, TRUE, strMessage, -1, 0xE18600FF );			

				strCount = pUIManager->IntegerToCommaString(5);
				strMessage.PrintF( _S( 61, "%s %s��" ), _pNetwork->GetItemName(2658), strCount);
				pUIManager->AddMessageBoxLString( MSGLCMD_RED_TREASUREBOX_EVENT, TRUE, strMessage, -1, 0xA3A1A3FF );

				strCount = pUIManager->IntegerToCommaString(5);
				strMessage.PrintF( _S( 61, "%s %s��" ), _pNetwork->GetItemName(2659), strCount);
				pUIManager->AddMessageBoxLString( MSGLCMD_RED_TREASUREBOX_EVENT, TRUE, strMessage, -1, 0xA3A1A3FF );
				
				if( iTreasureBoxLevel == 12 )
				{
					strCount = pUIManager->IntegerToCommaString(10);
					strMessage.PrintF( _S( 61, "%s %s��" ), _pNetwork->GetItemName(2860), strCount);
					pUIManager->AddMessageBoxLString( MSGLCMD_RED_TREASUREBOX_EVENT, TRUE, strMessage, -1, 0xA3A1A3FF );
				}
				
				pUIManager->AddMessageBoxLString( MSGLCMD_RED_TREASUREBOX_EVENT, FALSE, _S(4020, "������ �������ڸ� ����." ), 1 );
				pUIManager->AddMessageBoxLString( MSGLCMD_RED_TREASUREBOX_EVENT, FALSE, _S( 1220, "����Ѵ�." ) );	
			}
			else if (nResult == EVENT_REQUITAL_1)
			{
				_pNetwork->SendEventRequital(0);	
			}
			else if (nResult == EVENT_REQUITAL_2)
			{
				_pNetwork->SendEventRequital(1);
			}
		}
		break;
	case MSGLCMD_QUEST_REQ:
		{
			// 2009. 05. 27 ������
			// Ȯ���ѿ��� �̾߱� �Ѵ� �׸��� ������ NPC�� �����ϴ� ��� ����Ʈ �߿�
			// ������ ������ ����Ʈ�� �����ϰ� �Ѵ�.
			if( ciQuestClassifier < nResult )
			{
				// ������ ����Ʈ�� ���� ���� �Ǵ� ���� â�� ����.
				CUIQuestBook::SelectQuestFromMessageBox( nResult );
			}
			else
			{
				switch(nResult)
				{
				case MSGLCMD_REBORN_REQ:
					{
						CUIMsgBox_Info MsgBox;
						MsgBox.SetMsgBoxInfo( _S( 8339, ""), UMBS_OKCANCEL, UI_QUEST, MSGLCMD_REBORN_REQ );
						MsgBox.AddString( _S( 8340, ""), 0xa3a1a3ff );
						pUIManager->CreateMessageBox( MsgBox );
					}
					break;
				case MSGLCMD_REBORN_CHECK_REQ:
					{
						CUIMsgBox_Info MsgBox;
						CTString strMessage;
						MsgBox.SetMsgBoxInfo( _S( 8339, "Reborn system" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
						strMessage.PrintF(_S(8343, "Your current reborn is: %d"), _pNetwork->MyCharacterInfo.reborn);
						MsgBox.AddString(strMessage);
						pUIManager->CreateMessageBox( MsgBox );	
					}
					break;
				case MSGLCMD_REBORN_RANKING_REQ:
					{
						_pNetwork->RankingRebornReq();
					}
					break;
				case MSGLCMD_RANKING_SUMMON_REQ:
					{
						_pNetwork->RankingSummonReq();
					}
					break;
				case MSGLCMD_RANKING_PVP_REQ:
					{
						_pNetwork->RankingPvPReq();
					}
					break;
				case MSGLCMD_EXCHANGE_HEALER:
					{
						CUIMsgBox_Info MsgBox;
						MsgBox.SetMsgBoxInfo( _S( 8331, ""), UMBS_OKCANCEL, UI_QUEST, MSGLCMD_EXCHANGE_HEALER );
						MsgBox.AddString( _S( 8323, ""), 0xa3a1a3ff );
						pUIManager->CreateMessageBox( MsgBox );
					}
					break;
				case MSGLCMD_EXCHANGE_KNIGHT:
					{
						CUIMsgBox_Info MsgBox;
						MsgBox.SetMsgBoxInfo( _S( 8331, ""), UMBS_OKCANCEL, UI_QUEST, MSGLCMD_EXCHANGE_KNIGHT );
						MsgBox.AddString( _S( 8324, ""), 0xa3a1a3ff );
						pUIManager->CreateMessageBox( MsgBox );
					}
					break;
				case MSGLCMD_EXCHANGE_MAGE:
					{
						CUIMsgBox_Info MsgBox;
						MsgBox.SetMsgBoxInfo( _S( 8331, ""), UMBS_OKCANCEL, UI_QUEST, MSGLCMD_EXCHANGE_MAGE );
						MsgBox.AddString( _S( 8325, ""), 0xa3a1a3ff );
						//MsgBox.AddString( _S( 8535, ""), 0xa3a1a3ff );
						pUIManager->CreateMessageBox( MsgBox );
					}
					break;
				case MSGLCMD_EXCHANGE_NIGHTSHADOW:
					{
						CUIMsgBox_Info MsgBox;
						MsgBox.SetMsgBoxInfo( _S( 8331, ""), UMBS_OKCANCEL, UI_QUEST, MSGLCMD_EXCHANGE_NIGHTSHADOW );
						MsgBox.AddString( _S( 8326, ""), 0xa3a1a3ff );
						pUIManager->CreateMessageBox( MsgBox );
					}
					break;
				case MSGLCMD_EXCHANGE_ROGUE:
					{
						CUIMsgBox_Info MsgBox;
						MsgBox.SetMsgBoxInfo( _S( 8331, ""), UMBS_OKCANCEL, UI_QUEST, MSGLCMD_EXCHANGE_ROGUE );
						MsgBox.AddString( _S( 8327, ""), 0xa3a1a3ff );
						pUIManager->CreateMessageBox( MsgBox );
					}
					break;
				case MSGLCMD_EXCHANGE_SORCERER:
					{
						CUIMsgBox_Info MsgBox;
						MsgBox.SetMsgBoxInfo( _S( 8331, ""), UMBS_OKCANCEL, UI_QUEST, MSGLCMD_EXCHANGE_SORCERER );
						MsgBox.AddString( _S( 8328, ""), 0xa3a1a3ff );
						pUIManager->CreateMessageBox( MsgBox );
					}
					break;
				case MSGLCMD_EXCHANGE_TITAN:
					{
						CUIMsgBox_Info MsgBox;
						MsgBox.SetMsgBoxInfo( _S( 8331, ""), UMBS_OKCANCEL, UI_QUEST, MSGLCMD_EXCHANGE_TITAN );
						MsgBox.AddString( _S( 8329, ""), 0xa3a1a3ff );
						pUIManager->CreateMessageBox( MsgBox );
					}
					break;
				case MSGLCMD_EXCHANGE_EXROGUE:
				{
					CUIMsgBox_Info MsgBox;
					MsgBox.SetMsgBoxInfo(_S(8331, ""), UMBS_OKCANCEL, UI_QUEST, MSGLCMD_EXCHANGE_EXROGUE);
					MsgBox.AddString(_S(9356, ""), 0xa3a1a3ff);
					pUIManager->CreateMessageBox(MsgBox);
				}
				break;
				case MSGLCMD_EXCHANGE_ARCHMAGE:
				{
					CUIMsgBox_Info MsgBox;
					MsgBox.SetMsgBoxInfo(_S(8331, ""), UMBS_OKCANCEL, UI_QUEST, MSGLCMD_EXCHANGE_ARCHMAGE);
					MsgBox.AddString(_S(9357, ""), 0xa3a1a3ff);
					pUIManager->CreateMessageBox(MsgBox);
				}
				break;
				case QUEST_TALK: // Quest (Ȯ���ѹ��� ���Ŀ� ������� �ʴ´�.
					{
						CUIQuestBook::TalkWithNPC();
					}
					break;
				case QUEST_EVENT:
					{
						if (g_bHasEvent)
						{
							CTString strMessage;
							pUIManager->CloseMessageBoxL( MSGLCMD_EVENT );
							
							strMessage = _S( 1875, "�̺�Ʈ ����â" );
							pUIManager->CreateMessageBoxL( strMessage, UI_QUEST, MSGLCMD_EVENT );				
							pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, TRUE, strMessage, -1,0xE18600FF );				
							pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, TRUE, _S( 1876, "������ �̺�Ʈ�� �����Ͽ� �ֽʽÿ�." ), -1, 0xA3A1A3FF );	

							// kw : WSS_WHITEDAY_2007 , WSS_EVENT_LOD 
							if( IS_EVENT_ON(TEVENT_TREASUREBOX)  )
								pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, FALSE, _S( 1877, "�������� �̺�Ʈ." ), QUEST_TREASURE_BOX );	
							if( IS_EVENT_ON(TEVENT_RED_TREASUREBOX)  )
								pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, FALSE, _S(4010, "������ �������� �̺�Ʈ" ), EVENT_RED_TREASUREBOX );
							if (IS_EVENT_ON(TEVENT_CHUSEOK_2006))
								pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, FALSE, _S( 1860, "�߼����� �̺�Ʈ." ), QUEST_HARVEST_MOON_DAY_EVENT1 );	

							#ifdef RENUAL_EVENT			// 2P4P Renual Event  10/6 Update
									pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, FALSE, _S(2213, "���ǻ��� ���� �̺�Ʈ." ), QUEST_RENUAL_EVENT );	
							#endif

							if(g_iTempFlag&0x00200000)
								pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, FALSE, _S(2404, "���� �̺�Ʈ" ), EVENT_COUPON );
							if(g_iTempFlag&0x00400000)
								pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, FALSE, _S(2509, "���� �̺�Ʈ ��ǰ �ޱ�" ), EVENT_CONNECT );

							if (IsGamigo(g_iCountry) == TRUE || g_iCountry == USA)
							{
								if ( g_iCountry != FRANCE && g_iCountry != ITALY)
								{
									pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, FALSE, _S(3145, "���θ� ��Ű����ǰ �̺�Ʈ" ), EVENT_PROMOPACK );
								}
							}

							// wooss 070305 
							// kw : WSS_WHITEDAY_2007 , WSS_EVENT_LOD --------------------------------------------------------------------->>
							if( IS_EVENT_ON(A_EVENT_WHITE_DAY)  )
								pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, FALSE, _S(3238, "ȭ��Ʈ���� �̺�Ʈ" ), EVENT_WHITEDAY_2007 );
							// ------------------------------------------------------------------------------------------------------------<<
							// [070705: Su-won] EVENT_SUMMER_2007
							if( IS_EVENT_ON(TEVENT_SUMMER_2007)  )
								pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, FALSE, _S(3561, "���� ���� �̺�Ʈ" ), EVENT_SUMMER_2007 );

							if (IS_EVENT_ON(TEVENT_SUMMER_2008))
							{
								pUIManager->AddMessageBoxLString(MSGLCMD_EVENT, FALSE, _S(3617, "[����ī�带 ã�ƶ�!] �̺�Ʈ ����"), EVENT_ADULT_MAGICCARD);
							}

							if( IS_EVENT_ON(TEVENT_ADULT_OPEN) )
							{
								pUIManager->AddMessageBoxLString(MSGLCMD_EVENT, FALSE, _S(3658, "��ħ���� ���!"), EVENT_SHOOT);
								pUIManager->AddMessageBoxLString(MSGLCMD_EVENT, FALSE, _S(3617, "[����ī�带 ã�ƶ�!] �̺�Ʈ ����"), EVENT_ADULT_MAGICCARD);
							}

							// WSS_TG2007 2007/09/17 ǳ�� �̺�Ʈ
							if( IS_EVENT_ON(TEVENT_TG2007_FRUITFULL)  )
								pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, FALSE, _S( 3761, "ǳ�� �̺�Ʈ" ), EVENT_TG2007_FRUITFULL );

			#ifdef EVENT_REQUITALM //[ttos_2009_4_13]:���� ���� �����̺�Ʈ				
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT, FALSE, _s("���� ���� ���� ����ǰ �ޱ�"), EVENT_REQUITAL_1); 
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT, FALSE, _s("�⼮ üũ ����ǰ �ޱ�"), EVENT_REQUITAL_2); 
			#endif
							if (IS_EVENT_ON(TEVENT_ADD_UP_AFRON_2009))
							{
								pUIManager->AddMessageBoxLString(MSGLCMD_EVENT, FALSE, _s("�⼮ üũ ����ǰ �ޱ�"), EVENT_REQUITAL_2); 
							}

							pUIManager->AddMessageBoxLString( MSGLCMD_EVENT, FALSE, _S( 1874, "����Ѵ�." ) );		
						}
					}
					break;
				case QUEST_CHANGEWEAPON:
					{
						pUIManager->CloseMessageBoxL( MSGLCMD_CHANGEWEAPON_EVENT_REQ );
						pUIManager->CreateMessageBoxL( _S( 1204, "���ⱳü �̺�Ʈ" ), UI_QUEST, MSGLCMD_CHANGEWEAPON_EVENT_REQ );				
						pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_EVENT_REQ, TRUE, _S( 1205, "�̺�Ʈ�� ���� ��ü�� �� ��� ����ϴ� ������ ���ð��̳�, ������ �ɼ��� �״�� ��ü ���⿡ �Ű����ϴ�." ), -1, 0xA3A1A3FF );				
						pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_EVENT_REQ, TRUE, CTString("  "), -1, 0xA3A1A3FF );				
						pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_EVENT_REQ, TRUE, _S( 1206, "��ü�Ǵ� ����� �ش� Ŭ������ ����ϴ� ������ ��ݵ� ���⸸ �����մϴ�." ), -1, 0xA3A1A3FF );				
						pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_EVENT_REQ, TRUE, _S( 1207, "(Ex > Ÿ��ź : ��� <-> �����θ� ��ü)" ), -1, 0xA3A1A3FF );				
						pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_EVENT_REQ, TRUE, CTString("  "), -1, 0xA3A1A3FF );				
						pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_EVENT_REQ, TRUE, _S( 1208, "��ü ���� ȸ���� �̺�Ʈ �Ⱓ�� ���ؼ� ���� ���� �� �� �ֽ��ϴ�." ), -1, 0xA3A1A3FF );				
						pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_EVENT_REQ, TRUE, CTString("  "), -1, 0xA3A1A3FF );				
						pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_EVENT_REQ, TRUE, _S( 1209, "�α׿� ������ ��� �ɼ��� ��ü�Ǵ� ���⿡ �����ϰ� ����Ǵ� Ȩ�������� �����Ͻñ� �ٶ��ϴ�." ), -1, 0xA3A1A3FF );				
						pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_EVENT_REQ, FALSE, _S( 1210, "���⸦ ��ü�Ѵ�." ), EVENT_CHANGEWEAPON );		
						pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEWEAPON_EVENT_REQ, FALSE, _S( 1220, "����Ѵ�." ) );					
					}
					break;
				case QUEST_KILL_BOSS:					// �߷� ����.
					{
						// FIXME : �̱� ���� ���� �κ�...
						// FIXME : �˴� �ϵ� �ڵ�~~~!!!
						// FIXME : �ڵ� �ߺ��� ����....
						// FIXME : Hardcoding �ε���
						const int iQuestIndex = 13;
						if( CQuestSystem::Instance().CanIDoQuest( iQuestIndex ) )
						{
							if( CQuestSystem::Instance().GetDynamicDataByQuestIndex( iQuestIndex ) == NULL )
							{										
								pUIManager->GetQuestAccept()->open( iQuestIndex );
							}
							else
							{
								CTString strSysMessage;
								strSysMessage.PrintF( _S( 1687, "�̹� �������� ����Ʈ�Դϴ�."  ) );		
								_pNetwork->ClientSystemMessage( strSysMessage, SYSMSG_ERROR );
							}
						}
						else
						{
							CTString strSysMessage;
							strSysMessage.PrintF( _S( 1688, "������ ���� �ʽ��ϴ�."  ) );		
							_pNetwork->ClientSystemMessage( strSysMessage, SYSMSG_ERROR );
						}
					}
					break;
				case QUEST_SAVE_PRINCESS:						// ���� ����
					{
						// FIXME : Hardcoding �ε���
						const int iQuestIndex = 14;
						if( CQuestSystem::Instance().CanIDoQuest( iQuestIndex ) )
						{
							if( CQuestSystem::Instance().GetDynamicDataByQuestIndex( iQuestIndex ) == NULL )
							{										
								pUIManager->GetQuestAccept()->open( iQuestIndex );
							}
							else
							{
								CTString strSysMessage;
								strSysMessage.PrintF( _S( 1687, "�̹� �������� ����Ʈ�Դϴ�."  ) );		
								_pNetwork->ClientSystemMessage( strSysMessage, SYSMSG_ERROR );
							}
						}
						else
						{
							CTString strSysMessage;
							strSysMessage.PrintF( _S( 1688, "������ ���� �ʽ��ϴ�."  ) );		
							_pNetwork->ClientSystemMessage( strSysMessage, SYSMSG_ERROR );
						}
					}
					break;
				case QUEST_AZAKA_RAVINE:						// ����ī ����
					{
						// FIXME : Hardcoding �ε���
						const int iQuestIndex = 104;
						if( CQuestSystem::Instance().CanIDoQuest( iQuestIndex ) )
						{
							if( CQuestSystem::Instance().GetDynamicDataByQuestIndex( iQuestIndex ) == NULL )
							{										
								pUIManager->GetQuestAccept()->open( iQuestIndex );
							}
							else
							{
								CTString strSysMessage;
								strSysMessage.PrintF( _S( 1687, "�̹� �������� ����Ʈ�Դϴ�."  ) );		
								_pNetwork->ClientSystemMessage( strSysMessage, SYSMSG_ERROR );
							}
						}
						else
						{
							CTString strSysMessage;
							strSysMessage.PrintF( _S( 1688, "������ ���� �ʽ��ϴ�."  ) );		
							_pNetwork->ClientSystemMessage( strSysMessage, SYSMSG_ERROR );
						}
					}
					break;
				case QUEST_GATE_OF_DIMENSION:				// ������ ��
					{
						pUIManager->CloseMessageBoxL( MSGLCMD_GATE_OF_DIMENSION );
						pUIManager->CreateMessageBoxL( _S( 1686, "������ ��" ), UI_QUEST, MSGLCMD_GATE_OF_DIMENSION );				
						pUIManager->AddMessageBoxLString( MSGLCMD_GATE_OF_DIMENSION, TRUE, _S( 1689, "������ � ������ �����Ű���?" ), -1, 0xA3A1A3FF );		
						pUIManager->AddMessageBoxLString( MSGLCMD_GATE_OF_DIMENSION, TRUE, _S( 1690, "������ ���� ���� ���͵��� ������ ���� ���� ���̸��� ������� �Ѿ���� ������ ������ ���Դϴ�." ), -1, 0xA3A1A3FF );	
						pUIManager->AddMessageBoxLString( MSGLCMD_GATE_OF_DIMENSION, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGLCMD_GATE_OF_DIMENSION, TRUE, _S( 1691, "������ ������ ���� ���ø� ���� �ٽ��ѹ� ã�� �ּ��� ����� ���̸��� ����� �⿩�ϴ� ������ Ȯ���Ͻ� �� ���� �̴ϴ�." ), -1, 0xA3A1A3FF );	
						pUIManager->AddMessageBoxLString( MSGLCMD_GATE_OF_DIMENSION, TRUE, _S( 1692, "���� �� �⿩���� ���� �������ְ� ������ ���� ������ �� ���� �̴ϴ�." ), -1, 0xA3A1A3FF );		
						pUIManager->AddMessageBoxLString( MSGLCMD_GATE_OF_DIMENSION, FALSE, _S( 1694, "������ �� ����Ȯ��" ), GOD_RANKING );		
						pUIManager->AddMessageBoxLString( MSGLCMD_GATE_OF_DIMENSION, FALSE, _S( 1695, "����"), GOD_PRIZE );		
					}
					break;
				case QUEST_EXCHANGE_MONEY:
					{
						pUIManager->CloseMessageBoxL( MSGLCMD_EVENT_2PAN4PAN_ONE );
						pUIManager->CreateMessageBoxL( _S( 1875, "�̺�Ʈ ����â" ), UI_QUEST, MSGLCMD_EVENT_2PAN4PAN_ONE );	
						pUIManager->AddMessageBoxLString( 
							MSGLCMD_EVENT_2PAN4PAN_ONE, 
							TRUE,
							_S(2214,"2pan4pan �°� ī��� 2pan4pan ��Ŀ ī��� �������� ����Ʈ�� 2pan4pan�� �°�, ��Ŀ ���ӿ��� ����� �� �ִ� ���� �ӴϷ� ��ȯ�� �� �ֽ��ϴ�." ),
							-1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_ONE, TRUE, CTString("\n\n") , -1,0xA3A1A3FF );		
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_ONE, TRUE, _S(2215, "2pan4pan �°�ī�� :          : �°��Ӵ�" ), -1, 0xFFA41CFF );		
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_ONE, TRUE, _S(2216, "2pan4pan ��Ŀī�� :          : ��Ŀ�Ӵ�" ), -1, 0xFFA41CFF );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_ONE, FALSE, _S(2217,"2pan4pan �°�ī�� ��ȯ"),EXCH_FIVE);
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_ONE, FALSE, _S(2218,"2pan4pan ��Ŀī�� ��ȯ"),EXCH_FOUR);
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_ONE, FALSE,_S( 1220, "����Ѵ�." ));
					}
					break;
				case  QUEST_OPEN_TREASURE:
					{
						_pNetwork->SendEvent24(0,MSG_EVENT_2PAN4PAN_BOX_CHECK);
					}
					break;
				case QUEST_CHARACTER_CARD:
					{
						_pNetwork->SendEvent24(0,MSG_EVENT_2PAN4PAN_GOODS_CHECK);
					}
					break;
				case EVENT_NEWYEAR1:
					{
						if(pUIManager->DoesMessageBoxLExist( MSGLCMD_EVENT_NEWYEAR1 )) break;
						pUIManager->CreateMessageBoxL(_S (1875,"�̺�Ʈ ����â"), UI_QUEST,MSGLCMD_EVENT_NEWYEAR1);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR1, TRUE,	_S(2286,"2005 ũ�������� �̺�Ʈ"),-1,0xA3A1A3FF);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR1, TRUE, 
							_S(2288,"�ް� ��� �������� �����Ͽ� ������ ������ �� �ֽ��ϴ�.\n���� ��ǰ�� Ȩ�������� �����ϼ���."));
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR1, TRUE,	_S(2305,"�ް� ��� �̺�Ʈ ���� ����"),-1,0xA3A1A3FF);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR1, TRUE,	
							_S(2289,"��(4��) + ���(1��)\n��(8��) + ���(2��)\n��(16��) + ���(4��)\n��(24��) + ���(6��)\
							\n��(40��) + ���(10��)\n��(56��) + ���(14��)\n��(80��) + ���(20��)"));
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR1, FALSE, _S(2290,"�ް� ��� ����ǰ�� ���� �޴´�."),EVENT_NEWYEAR1_REWARD);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR1, FALSE, _S(1220,"����Ѵ�."));
					}
					break;
				case EVENT_NEWYEAR2:
					{
						if(pUIManager->DoesMessageBoxLExist( MSGLCMD_EVENT_NEWYEAR2 )) break;
						pUIManager->CreateMessageBoxL(_S (1875,"�̺�Ʈ ����â"), UI_QUEST,MSGLCMD_EVENT_NEWYEAR2);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR2, TRUE,	_S(2287,"2006 �ų� �γ��� ���� �̺�Ʈ"),-1,0xA3A1A3FF);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR2, TRUE, 
							_S(2291,"�̺�Ʈ �Ⱓ���� �������� �ڽ��� ĳ���� ��� �ð��� ���� ����ǰ�� ���� ������ �� �ֽ��ϴ�.\n����ǰ�� �̺�Ʈ �Ⱓ�� ���� �������� ���޵˴ϴ�."));
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR2, TRUE,	_S(2292,"�γ��� ���� �̺�Ʈ ����ǰ"),-1,0xA3A1A3FF);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR2, TRUE,	
							_S(2293,"10�ð�          100,000 Nas\n20�ð�          200,000 Nas\n30�ð�      ���� ���ü� 1��"));
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR2, FALSE, _S(2294,"���ӽð� Ȯ��"),EVENT_NEWYEAR2_TIMECHECK);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR2, FALSE, _S(2295,"�γ��� ���� ����ǰ�� ���� �޴´�."),EVENT_NEWYEAR2_REWARD);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_NEWYEAR2, FALSE, _S(1220,"����Ѵ�."));
					}
					break;
				case EVENT_FIND_FRIEND:
					{
						if(pUIManager->DoesMessageBoxLExist( MSGLCMD_EVENT_FIND_FRIEND )) break;
						pUIManager->CreateMessageBoxL(_S (1875,"�̺�Ʈ ����â"), UI_QUEST,MSGLCMD_EVENT_FIND_FRIEND);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_FIND_FRIEND, TRUE,	_S( 2433, "ģ�� ã�� �̺�Ʈ"),-1,0xA3A1A3FF);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_FIND_FRIEND, TRUE, 	_S( 2480, "���� ���� ģ���� ����ϼ���."));
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_FIND_FRIEND, TRUE, 
							_S( 2481, "ģ���� �ٽ� ���ƿ� ������ �ϸ� ģ���� 60�ð����� ����߿� 2���� ����ġ�� ��� �ǰ� ģ���� �����ð� ������ �ϸ� ģ���� �Բ� ������ ���� �� �ִ� �̺�Ʈ �Դϴ�."));
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_FIND_FRIEND, TRUE,	_S( 2482, "ģ�� ã�� �̺�Ʈ ����ǰ"),-1,0xA3A1A3FF);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_FIND_FRIEND, TRUE,	
							_S( 2483,"ģ���� �ٽ� ���ƿ� 30�ð� �̻� ����� �ϰ� �Ǹ� �޸� ĳ���� ���� ���ü� 2���� ģ���� ����� ĳ������ �������ü� 1���� ���޵˴ϴ�."));
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_FIND_FRIEND, FALSE, _S( 2484, "ģ�� ���"),EVENT_FF_REG);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_FIND_FRIEND, FALSE, _S( 2485, "�޸�ĳ�� ��ɽð� Ȯ��"),EVENT_FF_TIMECHECK);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_FIND_FRIEND, FALSE, _S( 2486, "���󰡴� Ȯ�� �� ����"),EVENT_FF_REWARD);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_FIND_FRIEND, FALSE, _S(1220,"����Ѵ�."));
					}
					break;
				case EVENT_CLOTHES_EXCHANGE:		// 060322 eons
					{
						if( pUIManager->DoesMessageBoxLExist( MSGLCMD_CLOTHES_EXCHANGE ) ) break;
						pUIManager->CreateMessageBoxL( _S( 2537, "�����ǻ� ��ȯ �̺�Ʈ" ), UI_QUEST, MSGLCMD_CLOTHES_EXCHANGE );
						pUIManager->AddMessageBoxLString( MSGLCMD_CLOTHES_EXCHANGE, TRUE,
							_S( 2538, "�����ǻ����� ��ȯ�ϱ� ���ؼ��� ���� ���츮�� �ʿ��մϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_CLOTHES_EXCHANGE, TRUE,
							_S( 2539, "����, ���� : ���� ���츮 18��" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGLCMD_CLOTHES_EXCHANGE, TRUE,
							_S( 2540, "�尩, �Ź� : ���� ���츮 12��" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGLCMD_CLOTHES_EXCHANGE, TRUE,
							_S( 2541, "���� : ���� ���츮 7��" ), -1, 0xA3A1A3FF );

						pUIManager->AddMessageBoxLString( MSGLCMD_CLOTHES_EXCHANGE, FALSE, _S( 2542, "����, ����" ), COAT_PANTS );
						pUIManager->AddMessageBoxLString( MSGLCMD_CLOTHES_EXCHANGE, FALSE, _S( 2543, "�尩, �Ź�" ), GLOVE_FOOTWEAR );
						pUIManager->AddMessageBoxLString( MSGLCMD_CLOTHES_EXCHANGE, FALSE, _S( 2544, "����" ), HELMET );
						pUIManager->AddMessageBoxLString( MSGLCMD_CLOTHES_EXCHANGE, FALSE, _S( 1220, "����Ѵ�." ) );
					}
					break;
				case EVENT_OX_GOZONE:				// O.X �̺�Ʈ
					{
						CTString strSysMessage;
						CUIMsgBox_Info	MsgBoxInfo;

						MsgBoxInfo.SetMsgBoxInfo( _S( 169, "�̺�Ʈ" ), UMBS_USER_12, UI_QUEST, MSGLCMD_EVENT_OXQUIZ, MSGBOX_WIDTH + 20 );
						MsgBoxInfo.SetUserBtnName( _S( 191, "Ȯ��" ), _S( 139, "���" ) );

						strSysMessage.PrintF( _S(2617, "O.X �̺�Ʈ ������ �����Ͻðڽ��ϱ�?" ) );
						MsgBoxInfo.AddString( strSysMessage);

						pUIManager->CreateMessageBox( MsgBoxInfo );
					}
					break;
#ifdef NETCAFE_CAMPAIGN
				case EVENT_NETCAFE_BOX:
					{// Date : 2006-04-27(���� 3:01:37), By eons
						_pNetwork->SendNetCafeOpenBox();
					}
					break;
#endif
				case WIN_SELECT:				// ��±� �˾� ���߱�
					{
						if( pUIManager->DoesMessageBoxLExist( MSGCMD_WORLDCUP_EVENT1 ) ) break;
						pUIManager->CreateMessageBoxL(  _S( 169, "�̺�Ʈ" ), UI_QUEST, MSGCMD_WORLDCUP_EVENT1 );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, TRUE,
							_S( 2797, "1. ��±��� ���߱� �̺�Ʈ" ) , -1 , 0xFFE591FF );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, TRUE,
							_S( 2798, "������� ��� �౸��ȸ ���� ���� 32���� �� ����� ����Ǵ� ������ ����� ��ȯ�ϸ� ��ȸ�� ���� ���� ����� ���� ���� ���� �� �ֽ��ϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, TRUE,
							_S( 2799, "�� ��� Ȯ���� ���� �ʿ��� ������� ������ �ٸ��ϴ�." ), -1 , 0xFFE591FF );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, TRUE,
							_S( 2800, "�� ���ⱳȯ�Ⱓ : 6��9�� ~ 6�� 30��" ), -1 , 0xFFE591FF );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, TRUE, CTString (""));
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, TRUE,
							_S( 2801, "[����ǰ]" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, TRUE,
							_S( 2802, "1�� : �������ü� 3��" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, TRUE,
							_S( 2803, "2�� : �������ü� 1��" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, TRUE,
							_S( 2804, "3�� : 300,000����" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, TRUE,
							_S( 2805, "�׿� : ������ 5��" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, FALSE, _S( 2806, "������� ����� ��ȯ�Ѵ�." ), WORLDCUP_EVENT1_EXCHANGE );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, FALSE, _S( 2807, "����ǰ�� ���� �޴´�" ), WORLDCUP_EVENT1_RECEIVE );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1, FALSE, _S( 1220, "����Ѵ�." ) );
					}
					break;
				case EVENT_GOLDENBALL:
					{
						if( pUIManager->DoesMessageBoxLExist( MSGCMD_WORLDCUP_GOLDENBALL ) ) break;
						
						if( !m_bStartGoldenBall && !m_bGoldenBallRequital )
						{
							_pNetwork->ClientSystemMessage( _S( 945, "������ �̺�Ʈ �Ⱓ�� �ƴմϴ�." ), SYSMSG_ERROR );
							return;
						}

						CTString strMessageA, strMessageB, strMessageC;
						strMessageA.PrintF( _S( 2808, "���� ��纼 �̺�Ʈ�� %s VS %s �� �౸ ��� �Դϴ�." ), m_strTeamA, m_strTeamB );
						strMessageB.PrintF( _S( 2809, "%s VS %s ��� �� ����" ), m_strTeamA, m_strTeamB );
						strMessageC.PrintF( _S( 2810, "%s VS %s ��� �� ����" ), m_strTeamA, m_strTeamB );

						pUIManager->CreateMessageBoxL( _S( 169, "�̺�Ʈ" ), UI_QUEST, MSGCMD_WORLDCUP_GOLDENBALL );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_GOLDENBALL, TRUE, strMessageA );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_GOLDENBALL, TRUE,
							_S( 2811, "�ڽ��� ������ ����� ��� ����� ���� ��� ��ǰ�� �����մϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_GOLDENBALL, TRUE, CTString( " " ) );
						
						if( m_bGoldenBallRequital ) // ��纼 �������̶��
						{// ������� ǥ��
							strMessageA.PrintF( _S( 2791, "%s VS %s �౸����� ����� %d : %d �Դϴ�." ),
								pUIManager->GetQuest()->GetStrTeamA(), pUIManager->GetQuest()->GetStrTeamB(),
								pUIManager->GetQuest()->GetScoreTeamA(), pUIManager->GetQuest()->GetScoreTeamB() );

							pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_GOLDENBALL, TRUE, strMessageA, 0x6BD2FFFF );
						}

						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_GOLDENBALL, FALSE, strMessageB, MSGCMD_WORLDCUP_GOLDENBALL_ENTRY );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_GOLDENBALL, FALSE, strMessageC, MSGCMD_WORLDCUP_GOLDENBALL_REQUITAL );
						pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_GOLDENBALL, FALSE, _S( 1220, "����Ѵ�." ) );
					}
					break;
				case EVENT_MOTHERDAY:
				case EVENT_RAINYDAY:
					{
						if( pUIManager->DoesMessageBoxLExist( MSGLCMD_MOTHERDAY ) ) break;
						pUIManager->CreateMessageBoxL( _S(2753, "��Ӵϳ� �̺�Ʈ" ), UI_QUEST, MSGLCMD_MOTHERDAY );
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, TRUE,
							_S(2754, "��Ӵϳ��� �¾� �𽺹β� �̺�Ʈ�� ����ǰ� �ֽ��ϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, TRUE,
							_S(2755, "�������� �����Ͻ� �𽺹β��̳� �𽺹β� ���ġ�� ���� ���ø� ���������ǰ�� �� 1�� ǰ�� ����Ȯ���� �帳�ϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, TRUE,
							_S(2756, "�𽺹β� 10���� ���� ���ø� �̺�Ʈ ������ ������ �� �ֽ��ϴ�. " ));
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, TRUE,
							_S(2757, "�𽺹β� ���ġ 1���� �𽺹β� 5���� ������, ��ȯ�ÿ��� �𽺹β� ���ġ�� �켱������ ��ȯ�ǰ� �� ���п� ���Ͽ� �𽺹β��� ��ȯ�˴ϴ�." ));

						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, TRUE,	_S(2758,  "���� ������" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, TRUE,	_S( 2759,"���� 5��" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, TRUE,	_S(  2760,"Ǫ����,�ɸ� ��Ʈ" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, TRUE,	_S(  2761,"������,�ɸ� ��Ʈ" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, TRUE,	_S(  2762,"���� ȸ���� 5��" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, TRUE,	_S(  2763,"����� ��ũ�� 1��" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, TRUE,	_S(  2764,"����� ��ũ�� 1��" ), -1, 0xA3A1A3FF );
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, TRUE,	_S(  2765,"���� ���ü� 1��" ), -1, 0xA3A1A3FF );
						
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, FALSE, _S( 2766,"����ǰ���� ��ȯ�Ѵ�." ), 1 );
						pUIManager->AddMessageBoxLString( MSGLCMD_MOTHERDAY, FALSE, _S( 1220, "����Ѵ�." ) );
					}
					break;
				case EVENT_BUDDHISM:
					{
						if( pUIManager->DoesMessageBoxLExist( MSGLCMD_BUDDHISM_EVENT ) ) break;
						pUIManager->CreateMessageBoxL( _S( 2913, "�ұ� �к� ���� �̺�Ʈ" ), UI_QUEST, MSGLCMD_BUDDHISM_EVENT );

						/********************************************/
						// 2007��
						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, TRUE,
							_S(3590, "���� ������ �𷡰� �� ������ ��ƿ��� �������� �帳�ϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, TRUE,
							_S(3591, "4���� ������ �𷡺����� ���� 10���� ��ƿ��� ����� �������ü���, ���� 7���� ��ƿ��� �������ü���, ���� 5���� ��ƿ��� ��������, ���� 3���� ��ƿ��� ����� ��������, ���� 2���� ��ƿ��� ���ʸ� �帮��," ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, TRUE,
							_S(3592, "������ Ȳ�� ���� 2������ ��ƿ��� ������ ������, ����� ������ ���� 2���� ��ƿ��� �뼭�� ������ �帳�ϴ�." ) );

						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, TRUE,
							_S( 2923, "�������� ��� ���ϴ°�?" ) );
						/*********************************************/
						
						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, TRUE, CTString(" ") );

						/*************************************/
						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, FALSE, CTString(_pNetwork->GetItemName(974)), 0);	//����� �������ü�
						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, FALSE, CTString(_pNetwork->GetItemName(85)), 1);		//�������ü�
						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, FALSE, CTString(_pNetwork->GetItemName(1576)), 2);	//������
						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, FALSE, CTString(_pNetwork->GetItemName(884)), 3);	//����� ������
						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, FALSE, CTString(_pNetwork->GetItemName(1575)), 4);	//����
						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, FALSE, CTString(_pNetwork->GetItemName(675)), 5);	//������ ����
						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, FALSE, CTString(_pNetwork->GetItemName(676)), 6);	//�뼭�� ����
						/*************************************/
						pUIManager->AddMessageBoxLString( MSGLCMD_BUDDHISM_EVENT, FALSE, _S( 1220, "����Ѵ�." ) );
					}
					break;
				case EVENT_COLLECTBUGS:
					{
						if( pUIManager->DoesMessageBoxLExist( MSGLCMD_COLLECT_INSECT_EVENT ) ) break;
						
						pUIManager->CreateMessageBoxL( _S( 169, "�̺�Ʈ" ), UI_QUEST, MSGLCMD_COLLECT_INSECT_EVENT );
						pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_INSECT_EVENT, TRUE, 
							_S( 2947, "�������� ������ ����ä���� �ߴ� ������ ���ø��� ������� ���ư����� ���� ����?" ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_INSECT_EVENT, TRUE,
							_S( 2948, "����ä�����ڸ� �����Ͻø� ���ͷκ��� ���� ������ ä���� �� �ֽ��ϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_INSECT_EVENT, TRUE,
							_S( 2949, "���������� �� 10������ ���� 1~10 ����Ʈ�� ������ �ְ�, ä�����ڿ��� 16������ ������ ������ �� ������ �� ä������ ������ ����������." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_INSECT_EVENT, TRUE,
							_S( 2950, "ä�������� �� ����Ʈ �հ迡 ���� ����ǰ�� �帳�ϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_INSECT_EVENT, TRUE, CTString(" ") );
						pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_INSECT_EVENT, TRUE,
							_S( 2951, "�� �̺�Ʈ �Ⱓ: 2012�� 7�� 21�� ~ 8�� 29��" ), -1, 0x6BD2FFFF );
						pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_INSECT_EVENT, TRUE,
							_S( 2952, "�� ä�����ڴ� ���� �� �������, �̺�Ʈ �Ⱓ ���� �� ������ �����Ͽ� ����ؼ� �̺�Ʈ�� ������ �� �ֽ��ϴ�." ), -1, 0x6BD2FFFF );
						pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_INSECT_EVENT, TRUE, CTString(" ") );

						pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_INSECT_EVENT, FALSE, _S( 2953, "���� ä������ ����(100 Nas)" ), 0 );
						pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_INSECT_EVENT, FALSE,_S( 2954, "���� ä������ ����" ), 1 );
						pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_INSECT_EVENT, FALSE, _S( 1220, "����Ѵ�." ) );
					}
					break;
				case QUEST_HARVEST_MOON_DAY_EVENT2:
					{
						CTString strMessage;
						pUIManager->CloseMessageBoxL( MSGLCMD_HARVEST_MOON_DAY2 );

						strMessage = _S( 1860, "�߼����� �̺�Ʈ" );	 
						pUIManager->CreateMessageBoxL( strMessage, UI_QUEST, MSGLCMD_HARVEST_MOON_DAY2 );				
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, TRUE, strMessage, -1,0xE18600FF );				

						strMessage = _S(3133, "�߼����� ���� ������ ���� �� ����. �� �߿����� ���� Ư�� ���������� ���� �����Ѵ�ϴ�." );
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, TRUE, strMessage, -1, 0xA3A1A3FF );				
						strMessage = _S(3134, "�߼��̺�Ʈ �Ⱓ ���� �η��ο��� �Ұ���� ��, ������ ��Ƽ� �������� ������ ������ִµ���" );
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, TRUE, strMessage, -1, 0xA3A1A3FF );				
						strMessage = _S(3135, "���� 10���� ������ ���ִ� ���������� ����� �ش�ϴ�." );
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, TRUE, strMessage, -1, 0xA3A1A3FF );
						strMessage = _S(3136, "Ȥ�� ���������� �����ôٸ� ������ �ֽ��� �����Ƿ���? �Ʒ��� ����ǰ �� 1���� �帮�ڽ��ϴ�." );
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, TRUE, strMessage, -1, 0xA3A1A3FF );				
						strMessage = " ";
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, TRUE, strMessage, -1, 0xA3A1A3FF );	

						strMessage = _S( 1866, "����ǰ" );
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, TRUE, strMessage, -1,0xE18600FF );	

						strMessage = _S( 1867, "10,000 Nas" );
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, TRUE, strMessage, -1, 0xA3A1A3FF );	
						strMessage = _S( 1868, "50,000 Nas" );
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, TRUE, strMessage, -1, 0xA3A1A3FF );	
						strMessage = _S( 1869, "200,000 Nas" );
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, TRUE, strMessage, -1, 0xA3A1A3FF );	
						strMessage = _S( 1870, "500,000 Nas" );
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, TRUE, strMessage, -1, 0xA3A1A3FF );	
						strMessage = _S( 1871, "�������ü� 2��" );
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, TRUE, strMessage, -1, 0xA3A1A3FF );	

						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, FALSE, _S(3137, "���������� ����ǰ���� ��ȯ�Ѵ�."  ), MSGCND_MOON_DAY_EVENT_GIVE_ITEM );																														
						pUIManager->AddMessageBoxLString( MSGLCMD_HARVEST_MOON_DAY2, FALSE, _S( 1874, "����Ѵ�."  ) );			
					}
					break;
				case EVENT_XMAS_2006:// 2006 X-Mas Event [12/12/2006 Theodoric]
					{
						pUIManager->CloseMessageBox(MSGLCMD_EVENT_XMAS_2006_CHANGE);
						CUIMsgBox_Info	MsgBoxInfo;
						CTString strTitle;
						CMobData* MD = CMobData::getData(336); // �����
						strTitle.PrintF("%s", MD->GetName());
						
						MsgBoxInfo.SetMsgBoxInfo( strTitle, UMBS_USER_12|UMBS_BUTTONEX , UI_NONE, MSGLCMD_EVENT_XMAS_2006_CHANGE );
						MsgBoxInfo.SetUserBtnName( _S(127, "��ȯ" ), _S( 139, "���" ) );
						MsgBoxInfo.SetBtnType( UBET_ITEM, CItemData::ITEM_POTION, CItemData::POTION_ETC );

						CTString strSysMessage = _S(3178, "��ȣ! ���־� ���̴� ����ũ��!!") ;
						MsgBoxInfo.AddString( strSysMessage );
						strSysMessage = _S(3179, "�� ����ũ�� ���� ���� �ʰڳ�?");
						MsgBoxInfo.AddString( strSysMessage );
						strSysMessage = _S(3180, "����ũ 3���� ������ �������� �ϳ��� �ֵ�������.");
						MsgBoxInfo.AddString( strSysMessage );				

						pUIManager->CreateMessageBox( MsgBoxInfo );
					}
					break;
				case EVENT_LOVE_LOVE:
					{
						pUIManager->CloseMessageBox(MSGLCMD_EVENT_LOVE_LOVE);
						
						CTString strMessage, strMessageA, strMessageB, strMessageC, strMessageD;

						if (IS_EVENT_ON(TEVENT_LUNARNEWYEAR_2008))
						{
							strMessage = _S(3996, "2008 ���� ���ָӴ� �̺�Ʈ");
							strMessageA = _S(4004, "2008�� ���� �� ���� �����ð� �Ҹ� �̷�ñ� �ٶ��ϴ�.");
							strMessageB = _S(4005, "������ ��� �Ҹ����ڿ� ����ִ� ���ָӴϰ� ����������� ���� �̷�� �ִٸ� �Ҹ����ڸ� ��ȯ �� �� �ֽ��ϴ�.");
							strMessageC = _S(4006, "�Ҹ����� ��ȯ");
							strMessageD = _S(4007, "���ָӴ��� ���� ���� ������ �Ǿ��� �� ���� ��ǰ�� ���޵Ǵ� Ȯ���� �޶����ϴ�.");
						}
						else
						{
							strMessage = _S(3203, "���귯�� �̺�Ʈ");
							strMessageA = _S(3214, "���ڻ��ڿ� ��� �ִ� ���ڷ��� ���� ������ ���� �̷�� �ִٸ� ���ڻ��ڸ� ��ȯ�� �� �ֽ��ϴ�.");
							strMessageB = _S(3215, "īī�� 30, īī�� 60, īī�� 90 3������ ���ڷ��� ���� ������ �Ǿ��� �� ���� ��ǰ�� ���޵Ǵ� Ȯ���� �޶����ϴ�.");
							strMessageC = _S(3216, "���ڻ��� ��ȯ");
						}

						pUIManager->CreateMessageBoxL(strMessage, UI_QUEST, MSGLCMD_EVENT_LOVE_LOVE);				
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_LOVE_LOVE, TRUE, strMessage, -1,0xE18600FF);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_LOVE_LOVE, TRUE, strMessageA, -1, 0xA3A1A3FF);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_LOVE_LOVE, TRUE, strMessageB, -1, 0xA3A1A3FF);

						if (IS_EVENT_ON(TEVENT_LUNARNEWYEAR_2008))
						{
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_LOVE_LOVE, TRUE, strMessageD, -1, 0xA3A1A3FF);
						}

						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_LOVE_LOVE, FALSE, strMessageC, 0);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_LOVE_LOVE, FALSE, _S(1874,"����Ѵ�."));
					}
					break;
				case NPC_HELP:
					{
						pUIManager->RearrangeOrder( UI_NPCHELP, TRUE );
					}
					break;
				case EVENT_MAY:
					{
						pUIManager->CreateMessageBoxL(_S(100,"�̺�Ʈ"),UI_QUEST,MSGLCMD_EVENT_MAY);
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MAY, TRUE, _S(3396, "�ݰ����ϴ�. 5�� ������ ���� �����Ͽ� ��Ʈ ī�������� ��ſ� ������ �� �ǽö�� ���ӳ� 4���� �̺�Ʈ�� �غ��߽��ϴ�.") );
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MAY, TRUE, _S(3397, "��̰� �ູ�� 5�� ������ �� ��������.") );
 						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MAY, TRUE,  CTString(" "));
						if(IS_EVENT_ON(TEVENT_CHILDREN_2007))
 						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MAY, FALSE, _S(3370, "�� ���� Ż������" ), EVENT_MAY_CHILDREN );	
						if(IS_EVENT_ON(TEVENT_PARENTS_2007))
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MAY, FALSE, _S(3362, "ī���̼��� ��ƶ�~" ), EVENT_MAY_PARENTS );	
						if(IS_EVENT_ON(TEVENT_TEACHER_2007))
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MAY, FALSE, _S(3379, "������ ����" ), EVENT_MAY_MASTER );	
						pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MAY, FALSE, _S(1874,"����Ѵ�."));
					}
					break;
				case EVENT_MINIGAME:
					{
						if (IS_EVENT_ON(TEVENT_GOMDOLI))
						{
							// WSS_MINIGAME 070420 -------------------------------->>
							pUIManager->CloseMessageBoxL( MSGLCMD_EVENT_MINIGAME );
							pUIManager->CreateMessageBoxL(_S(100,"�̺�Ʈ"),UI_QUEST,MSGLCMD_EVENT_MINIGAME);
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE, _S(3428, "������ ���� ������ ���� ������") );
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE, _S(3429, "���͸� ����ϸ� ���� Ȯ���� [������ ������ ����]�� ���� �� �ֽ��ϴ�.") );
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE, _S(3430, "������ ����� 1������ 9������ ��ȩ ���� �������� �Ǿ������� ������ ��� ��� ������ �������ø� ���� ���� ����, ����, �� ������ ���� �� �־��.") );
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE, _S(3431, "����, ����, �� ���ӿ��� ������ �¸��ϼ��� �� ���� ���� �ܰ迡 �������� �׳� ������ ��ǰ�� �ް� �׸����� ������ �� �ִµ�, �����ؼ� ���� �̱���� ���� ��ǰ�� ���� �� �ִ�ϴ�.") );
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE, CTString(" ") );
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE, _S(3432, "����ǰ �Ұ�") );
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE, _S(3433, "�ذ��������� ���ӿ� �����Ͻ� �� ù ȸ�� �й��Ͻ� ���(0��) �� �ѹ��� 'ü��� ������Ʈ'�� �帮��, ù 1�� �ÿ��� 'ü��� ���⹫��' 1���� �帳�ϴ�.") );
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE, _S(3434, "���������� 0�� ��ǰ: ���� �� HP ȸ�� ���� 1��") );
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE,  _S(3435, "���������� 1�� ��ǰ: ���� �� MP ȸ�� ���� 5��"));
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE,  _S(3436, "���������� 2�� ��ǰ: ���� �� HP ȸ�� ���� 5��"));
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE,  _S(3437, "���������� 3�� ��ǰ: ���� �� ��� ȸ�� ���� 5��"));
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE,  _S(3438, "���������� 4�� ��ǰ: �����ֹ��� 1��"));
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE,  _S(3439, "���������� 5�� ��ǰ: �����ֹ��� 2��"));
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE,  _S(3440, "���������� 6�� ��ǰ: �������ü� 1��"));
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE,  _S(3441, "���������� 7�� ��ǰ: �������ü� 2��"));
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE,  _S(3442, "���������� 8�� ��ǰ: �������ü� 3��"));
 							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE,  CTString(" "));		
 							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, FALSE, _S(3443, "���������� �����ϱ�" ), EVENT_REWARD_1 );	
					//		���� �ּ�....
					//		��Ȳ�� �� ���̰� ó��
					//		pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, FALSE, _S(3444, "������ ���� ���� ã�� ��Ȳ����" ), EVENT_REWARD_2 );	
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, FALSE, _S(1874,"����Ѵ�."));
						}
						else if (IS_EVENT_ON(TEVENT_XMAS_2007))
						{
							pUIManager->CloseMessageBoxL(MSGLCMD_EVENT_MINIGAME);
							pUIManager->CreateMessageBoxL(_S(100, "�̺�Ʈ"), UI_QUEST, MSGLCMD_EVENT_MINIGAME);
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE, _S(5805, "��ŸŬ�ν� ���� ���� ������!!"));
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE, _S(5806, "���͸� ����ϸ� ���� Ȯ���� [��ŸŬ�ν��� ����]�� ���� �� �ֽ��ϴ�."));
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE, _S(5807, "��ŸŬ�ν��� ������ 1������ 9������ ��ȩ ���� �������� �Ǿ������� ��� ��� ������ �������ø� ���� ���� ����, ����, �� ������ ���� �� �־��."));
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE, _S(3431, "����, ����, �� ���ӿ��� ������ �¸��ϼ��� �� ���� ���� �ܰ迡 �������� �׳� ������ ��ǰ�� �ް� �׸����� ������ �� �ִµ�, �����ؼ� ���� �̱���� ���� ��ǰ�� ���� �� �ִ�ϴ�."));
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, TRUE,  CTString(" "));
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, FALSE, _S(3443, "���������� �����ϱ�"), EVENT_REWARD_1);
							pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_MINIGAME, FALSE, _S(1874, "����Ѵ�."));
						}
					}
					break;
				case EVENT_FLOWERS_SUPPORT:
					{
						pUIManager->GetFlowerTree()->OpenFlowerTree();
					}
					break;
				case EVENT_SUPPORT_EXCHANGE:
					{
						if (!pUIManager->DoesMessageBoxExist(MSGCMD_FLOWERTREE_TICKET) )
							_pNetwork->SendFlowerTreeReq((UBYTE)MSG_EVENT_FLOWERTREE_2007_MY_POINT);
					}
					break;
				case SIEGEWARFARE_MASTERTOWER1:			// Ÿ�� �����ϱ�
					{
						pUIManager->GetSiegeWarfareNew()->SendRequestTowerSet();
						//_pUISWDoc->SetUIState(SWS_APPLY_TOWER);
						//pUIManager->GetSiegeWarfareNew()->OpenCheckTower();
					}
					break;
				case SIEGEWARFARE_MASTERTOWER2:			// Ÿ�� ��ȭ�ϱ�
					{
						pUIManager->CreateMessageBoxL(_S(100,"�̺�Ʈ"),UI_QUEST,MSGLCMD_SIEGE_WARFARE_UPGRADE);
						pUIManager->AddMessageBoxLString(MSGLCMD_SIEGE_WARFARE_UPGRADE, TRUE, _S( 3679,"������Ų ��ȣŸ���� ���׷��̵� �� �� �ֽ��ϴ�.") );
						pUIManager->AddMessageBoxLString(MSGLCMD_SIEGE_WARFARE_UPGRADE, TRUE, _S( 3680,"����� ���� ������� ���� ��ȣ�ϴ� ��ȣŸ���� ��ȭ��Ű�� ������ Ÿ�� ��ɿ� ���� Ź���� ȿ���� ���� �� ���� �̴ϴ�.") );				
						pUIManager->AddMessageBoxLString(MSGLCMD_SIEGE_WARFARE_UPGRADE, TRUE, _S( 3681,"��ȭ�ϰ��� �ϴ� ��ȣ Ÿ���� ������ �ּ���.") );
 						pUIManager->AddMessageBoxLString(MSGLCMD_SIEGE_WARFARE_UPGRADE, FALSE, _S( 3682,"������ Ÿ�� ��ȭ" ), EVENT_REWARD_1 );	
						pUIManager->AddMessageBoxLString(MSGLCMD_SIEGE_WARFARE_UPGRADE, FALSE, _S( 3683,"������ Ÿ�� ��ȭ" ), EVENT_REWARD_2 );	
						pUIManager->AddMessageBoxLString(MSGLCMD_SIEGE_WARFARE_UPGRADE, FALSE, _S(1874,"����Ѵ�."));
					}
					break;
				case SIEGEWARFARE_MASTERTOWER3:			// ���� ��ȭ�ϱ�
					{
						pUIManager->GetSiegeWarfareNew()->SetUpgradeType( SWUT_GATE );						
						pUIManager->GetSiegeWarfareNew()->SendTowerStateRequest(SWUT_GATE);	
					}
					break;
				case SIEGEWARFARE_MASTERTOWER4:			// ������ Ÿ�� �����ϱ�
					{
						pUIManager->GetSiegeWarfareNew()->SetRepairTowerIndex(m_iNpcIndex);
						pUIManager->GetSiegeWarfareNew()->SendTowerRepairStateRequest(m_iNpcIndex);
					}
					break;
				case EVENT_BJMONO_2007_REQ:
					{
						_pNetwork->SendBJMono2007Req(MSG_EVENT_BJMONO_2007_TICKET_REQ); // ����� ��û
					}
					break;
				case EVENT_BJMONO_2007_CHANGE_REQ:
					{
						pUIManager->CloseMessageBox(MSGCMD_BJMONO_2007_CHANGE_REQ);

						CMobData* MD = CMobData::getData(408); // �̺�Ʈ ���� ���
						CTString strMessage, strName;
						CUIMsgBox_Info MsgBoxInfo;
						strName = MD->GetName();

						MsgBoxInfo.SetMsgBoxInfo(strName, UMBS_OKCANCEL|UMBS_INPUTBOX, UI_QUEST, MSGCMD_BJMONO_2007_CHANGE_REQ);
						strMessage.PrintF(_s("�� ���� ������� ��ȯ �Ͻðڽ��ϱ�?"));
						MsgBoxInfo.AddString(strMessage);
						pUIManager->CreateMessageBox(MsgBoxInfo);
					}
					break;
				case EVENT_TG2007_SCREENSHOT:  // WSS_TG2007 2007/09/14 ��ũ���� �̺�Ʈ
					{
						_pNetwork->SendTG2007ScreenshotReq();
					}
					break;
				case EVENT_TG2007_1000DAYS_CAP:
					{
						// TODO :: ��Ʈī���� 1000�� ������ �ޱ�
						_pNetwork->SendLC1000DayTakeHatReq();
					}
					break;
				case EVENT_TG2007_1000DAYS_CAP_UPGRADE:
					{	// TODO :: ������ ���巹�̵�
						CUIMsgBox_Info MsgBoxInfo;
						CTString strMessage;

						MsgBoxInfo.SetMsgBoxInfo(_S(3829, "������ ���׷��̵�"), UMBS_YESNO | UMBS_BUTTONEX, UI_QUEST, MSGCMD_TG2007_1000DAYS_CAP_UPGRADE);
						MsgBoxInfo.SetBtnType(UBET_ITEM, CItemData::ITEM_SHIELD, CItemData::ITEM_SHIELD_HEAD);
						strMessage.PrintF(_S(3832, "���׷��̵� �� �����ڸ� �÷��� �ֽʽÿ�"));
						MsgBoxInfo.AddString(strMessage);
						pUIManager->CreateMessageBox(MsgBoxInfo);
					}
					break;
				case EVENT_TG2007_1000DAYS_FIRECRACKER:
					{	//  TODO :: ���� �ޱ� �̺�Ʈ
						_pNetwork->SendTakeFireCracker();
					}
					break;
				case EVENT_HALLOWEEN2007_DEVILHAIR:
					{	// TODO :: �ҷ����̺�Ʈ2007, �Ǹ����� �Ӹ��� ���� ��û
						_pNetwork->SendHalloween2007Req(MSG_EVENT_TAKE_DEVILHEAIR);
					}
					break;
				case EVENT_HALLOWEEN2007_CANDYBASKET:
					{	// TODO :: �ҷ��� �̺�Ʈ2007, �����ޱ� ��û
						_pNetwork->SendHalloween2007Req(MSG_EVENT_CHANGE_CANDYBASKET);
					}
					break;
				case EVENT_HALLOWEEN2007_PUMKINHEAD:
					{	// TODO :: �ҷ��� �̺�Ʈ2007, ȣ�ڸӸ� Ż ��ȯ�ޱ�
						_pNetwork->SendHalloween2007Req(MSG_EVENT_CHANGE_PUMKINHEAD);
					}
					break;
				case EVENT_HALLOWEEN2007_WITCHHAT:
					{	// TODO :: �ҷ��� �̺�Ʈ2007, ������� ��ȯ ��û
						_pNetwork->SendHalloween2007Req(MSG_EVENT_CHANGE_WITCHHAT);
					}
					break;
				case EVENT_HALLOWEEN2007_PUMKIN:
					{	// TODO :: �ҷ��� �̺�Ʈ2007, ȣ�� ��ȯ ��û
						_pNetwork->SendHalloween2007Req(MSG_EVENT_CHANGE_PUMKIN);
					}
					break;
				case EVENT_XMAS2007_DECO:	// ũ�������� ��� 
					{
						CUIMsgBox_Info MsgBoxInfo;
						CTString strMessage;

						MsgBoxInfo.SetMsgBoxInfo(_S(169, "�̺�Ʈ"), UMBS_YESNO, UI_QUEST, MSGCMD_EVENT_XMAS_2007_DECO);
						MsgBoxInfo.AddString(_S(3953, "ũ�������� Ʈ���� ����ϸ� ������ ũ�������� Ʈ�� ����� ��� ������ϴ�"));
						pUIManager->CreateMessageBox(MsgBoxInfo);
					}
					break;
				case EVENT_XMAS2007_BLESSEDNESS:
					{	// ũ�������� �ູ ��û
						_pNetwork->SendXMAS2007DecoReq(MSG_EVENT_XMASTREE_GET_BLESS);
					}
					break;
				case CASH_PERSONSHOP_CLOSE:	//071129 ttos : �Ǹ� ������ȸ ȸ��
					{	// TODO :: �Ǹ� ���� ����
						_pNetwork->SendCashPersonShop(MSG_ALTERNATEMERCHANT_END);
					}
					break;
				case CASH_PERSONSHOP_ITEM:
					{	// TODO :: ������ ������ ȸ��
						_pNetwork->SendCashPersonShop(MSG_ALTERNATEMERCHANT_PRODUCT_RECOVERY);
					}
					break;
				case CASH_PERSONSHOP_NAS:
					{	// TODO :: ������ ���� ȸ��
						_pNetwork->SendCashPersonShop( MSG_ALTERNATEMERCHANT_PRODUCT_NAS);
					}
					break;
				case EVENT_SAKURA_2008: //2008�� ���� ���� �̺�Ʈ ���� ��ȯ ��û
					{
						if (pUIManager->DoesMessageBoxExist(MSGCMD_EVENT_SAKURA_2008))
							pUIManager->CloseMessageBox(MSGCMD_EVENT_SAKURA_2008);

						CUIMsgBox_Info MsgBoxInfo;
						MsgBoxInfo.SetMsgBoxInfo(_S(169, "�̺�Ʈ"), UMBS_YESNO, UI_QUEST, MSGCMD_EVENT_SAKURA_2008);
						MsgBoxInfo.AddString(_S(4113, "������ �ִ� ���� ��� ������ϴ�. ��� �ǳ��ְڽ��ϱ�?"));
						pUIManager->CreateMessageBox(MsgBoxInfo);
					}
					break;
				case EVENT_CHAOSBALL:	// [080422: Su-won] EVENT_CHAOSBALL
					{
						if( pUIManager->DoesMessageBoxLExist( MSGLCMD_CHAOSBALL_EVENT ) ) 
							break;

						pUIManager->CreateMessageBoxL( _S(100, "�̺�Ʈ"), UI_QUEST, MSGLCMD_CHAOSBALL_EVENT );
						pUIManager->AddMessageBoxLString( MSGLCMD_CHAOSBALL_EVENT, TRUE, 
							_S(4128, "ī���� ���� ������ ���������� ������ �ź��� ���Դϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_CHAOSBALL_EVENT, TRUE,	
							_S(4129, "���̸��� ��������� ���� �� �� �ִ� ������ �ƴ�����, ���� ���� �糪�ý������� ������ �����̳� ����� ��Ƴ��� ���ڷ� �̿��ϰ� �Ѵ�ϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_CHAOSBALL_EVENT, TRUE,
							_S(4130, "������ �Ϸ��̴� ���� �ܴ��� ǥ�鶧���� �������� ������ �ϱ� �������� �ȿ� ���� ����ִ���, � ���� ����ִ��� ���� �� �� ������ ������ ������ ���ܵα⿡�� �ȼ�����������." ));
						pUIManager->AddMessageBoxLString( MSGLCMD_CHAOSBALL_EVENT, TRUE,
							_S(4131, "�ֱٿ� ���̸��� �������� �Ǹ��ϴ� ��� ���ǿ� ����ִٰ� �ϴµ�, ī���� ���� ������ ��Ŵٸ� ������ ������ �ּ���. ������ �����ؼ� �ȿ� ����ִ� ������ ���� �帮�ڽ��ϴ�." ));

						pUIManager->AddMessageBoxLString( MSGLCMD_CHAOSBALL_EVENT, FALSE, _S(4132, "ī���� �� ���������ϱ�" ), 1 );
						pUIManager->AddMessageBoxLString( MSGLCMD_CHAOSBALL_EVENT, FALSE, _S(1220, "����Ѵ�." ) );
					}
					break;
				case EVENT_REQUITAL_1:	// [090811: selo] 2009�� 7�� ����
					{
						_pNetwork->SendEventRequital(0);
					}
					break;
				case EVENT_PHOENIX_REQ:	//�Ǵн� �̺�Ʈ
					{
						_pNetwork->SendPhoenixCharacterCondition();
					}
					break;
				

				case EVENT_HANAPOS_SK_EVENT:
					{
                    BOOL bOK = TRUE;

						if( bOK )
						_pNetwork->SendHanaposEvent(m_iNpcVirIdx);
					}
					break;
				case MIDLEVEL_SUPPORT_REQ: // �������� ������ ���� ��û
					{
						_pNetwork->SendSupportSkill((UBYTE)MSG_SKILL_MIDLEVEL_SUPPORT);
					}
					break;
				case EVENT_ADD_UP_NEW_AFRON:	// ���� ���� �̺�Ʈ(������ + ������)
					{
						_pNetwork->SendEventMsg(static_cast<UBYTE>(MSG_EVENT_NEW_AFRON_2009));
					}
					break;				
				case QUEST_RESTORE_ITEM:		// [100208: selo] ����Ʈ ������ �ٽ� �ޱ�
					{
						pUIManager->CloseMessageBox(MSGCMD_QUEST_RESTORE_ITEM);

						CUIMsgBox_Info MsgBoxInfo;
						MsgBoxInfo.SetMsgBoxInfo(_S( 99, "����Ʈ" ), UMBS_YESNO, UI_QUEST, MSGCMD_QUEST_RESTORE_ITEM );						
						if( m_restoreQuestItemIndex != -1 )
						{
							CTString strMessage;
							strMessage.PrintF(_S( 5359, "[%s] �������� �����ðڽ��ϱ�?" ), _pNetwork->GetItemName( m_restoreQuestItemIndex ) );
							MsgBoxInfo.AddString( strMessage );
						}
						else
						{
							MsgBoxInfo.AddString(_S(4819, "[�׸��� ���� ����] �������� �����ðڽ��ϱ�?"));
						}
						pUIManager->CreateMessageBox(MsgBoxInfo);
					}
					break;

					// ($E_WC2010) [100514: selo] 2010 ���ư� ������ �̺�Ʈ2 ��� ���� �����ϱ�
				case EVENT_WOLRDCUP_2010_EVENT2:
				case EVENT_WOLRDCUP_2010_EVENT2_STATUS:
				case EVENT_WOLRDCUP_2010_EVENT2_GIFT:
					{
						if( pUIManager->DoesMessageBoxLExist(MSGLCMD_EVENT_WORLDCUP_EVENT2))
							pUIManager->CloseMessageBoxL(MSGLCMD_EVENT_WORLDCUP_EVENT2);
						
						pUIManager->CreateMessageBoxL( _S(4900, "��±� �����ϱ� �̺�Ʈ �ȳ�"), UI_QUEST, MSGLCMD_EVENT_WORLDCUP_EVENT2 );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT2, TRUE, 
							_S(4902, "�ݰ�����. ��±� �����ϱ� �̺�Ʈ�� �����Ͻ÷���, �� ������ ���� �������� �ʿ��ؿ�" ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT2, TRUE, 
							_S(4903, "���� �������� '���� ���� ����'���� ȹ���� �� �ִ�ϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT2, TRUE, 
							_S(4904, "���� ����� ����� ����Ǵ� ������ ���⸦ ������ ���ø� ������ �� �־��. ����� ���ÿ� ���� �������� �������, �ٽ� �ǵ��� ������ �� �����ϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT2, TRUE, 
							_S(4905, "��, ���� �Ⱓ ���ȿ��� �������� ���� �����մϴ�. �ٽ� ����Ϸ��� ���� �������� �߰��� �ʿ�������." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT2, TRUE, 
							_S(4906, "�̺�Ʈ ��÷ ������ �������� ����� �Ŀ� ���޵˴ϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT2, TRUE, 
							_S(4907, "��... � ���� ����� �����Ͻðھ��?" ) );

						if( nResult == EVENT_WOLRDCUP_2010_EVENT2 )
						{						
							pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT2, FALSE, _S(4908, "��� ���� ����" ), EVENT_WORLDCUP_2010_EVENT2_SEL1);							
							pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT2, FALSE, _S(4911, "�� ���� ��Ȳ" ), EVENT_WORLDCUP_2010_EVENT2_SEL2);
						}
						else if( nResult == EVENT_WOLRDCUP_2010_EVENT2_STATUS )
						{
							pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT2, FALSE, _S(4911, "�� ���� ��Ȳ" ), EVENT_WORLDCUP_2010_EVENT2_SEL2);
						}
						else if( nResult == EVENT_WOLRDCUP_2010_EVENT2_GIFT )
						{	
							pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT2, FALSE, _S(4911, "�� ���� ��Ȳ" ), EVENT_WORLDCUP_2010_EVENT2_SEL2);
							pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT2, FALSE, _S(4912, "��÷ ���� �ޱ�" ), EVENT_WORLDCUP_2010_EVENT2_SEL3);
						}
					}
					break;
					// ($E_WC2010) [100514: selo] 2010 ���ư� ������ �̺�Ʈ3 ���� ���� �����ϱ�
				case EVENT_WOLRDCUP_2010_EVENT3:
					{
						if( pUIManager->DoesMessageBoxLExist(MSGLCMD_EVENT_WORLDCUP_EVENT3))
							pUIManager->CloseMessageBoxL(MSGLCMD_EVENT_WORLDCUP_EVENT3);
						
						pUIManager->CreateMessageBoxL( _S(4901, "���� �̺�Ʈ �ȳ�"), UI_QUEST, MSGLCMD_EVENT_WORLDCUP_EVENT3 );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT3, TRUE, 
							_S(4932, "���� ī�带 ������ ���̱���. ����ī�� �ޱ� ��ư�� �����ø� ��ü ���� �帳�ϴ�." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT3, TRUE, 
							_S(4933, "�ƾ�... ������ �ٶ�� �帮�� �� �ƴϴϱ� ���� ������. ��, �Ϸ翡 1�常 �帱 �� �־��." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT3, TRUE, 
							_S(4934, "���� �Ϸ翡 �� �� ������ ����ī�带 ���� ���� ���� ���� ������ ������ �� ���� �ſ���." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT3, TRUE, 
							_S(4935, "����, ���ϴ� ������ �ִٸ� �߰��� �ٲٽ� ���� �־��." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT3, TRUE, 
							_S(4936, "�ŵ������ϰ�, �ϴ� ����ī�� ���� �ް� �����ұ��?" ) );	
						
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT3, FALSE, _S(4937, "����ī�� �ޱ�" ), EVENT_WORLDCUP_2010_EVENT3_SEL1);
						pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_WORLDCUP_EVENT3, FALSE, _S(1721, "���� �ޱ�"), EVENT_WORLDCUP_2010_EVENT3_SEL2);
					}
					break;
				case ATTENDANT_DATE_REQ:
					{
						// ������ �����⼮�ϼ� ��û
						_pNetwork->SendAttendanceReq( 0 );
					}
					break;
				case DUNGEON_DIFFICULTY_NORMAL:
					{
						_pNetwork->RaidInzoneJoinReq(36, 0);
					}
					break;
				case DUNGEON_DIFFICULTY_HARD:
					{
						_pNetwork->RaidInzoneJoinReq(36, 1);
					}
					break;
				case EVENT_TEMP: // �ܹ߼� �̺�Ʈ (100907 ���� ��ĭ���)
					{
						if (!pUIManager->DoesMessageBoxExist(MSGCMD_SOULOFSCALP_CONFIRM))
						{
							CUIMsgBox_Info MsgBox;
							MsgBox.SetMsgBoxInfo(_S(127, "��ȯ"), UMBS_OKCANCEL, UI_QUEST, MSGCMD_SOULOFSCALP_CONFIRM);
							MsgBox.AddString(_s("��ȥ�� ¡ǥ�� ��ȯ �Ͻðڽ��ϱ�? (���� ������ ���� �ڵ����� ������ ���޵˴ϴ�.)"));
							pUIManager->CreateMessageBox(MsgBox);
						}
					}
					break;
				case REGISTER_MERCHANT:	// [2010/08/25 : Sora] ADD_SUBJOB
					{
						if( pUIManager->DoesMessageBoxLExist( MSGLCMD_REGISTER_MERCHANT ) ) 
							break;

						CTString strSp, strNas, strTemp;
						strSp = pUIManager->IntegerToCommaString(DEF_REGISTER_MERCHANT_NEED_SP);
						strNas = pUIManager->IntegerToCommaString(DEF_REGISTER_MERCHANT_NEED_NAS);

						pUIManager->CreateMessageBoxL( _S(5057, "��� ����"), UI_QUEST, MSGLCMD_REGISTER_MERCHANT );
						pUIManager->AddMessageBoxLString( MSGLCMD_REGISTER_MERCHANT, TRUE, pUIManager->GetSubJobName(SUBJOB_MERCHANT), -1, 0xE18600FF);
						pUIManager->AddMessageBoxLString( MSGLCMD_REGISTER_MERCHANT, TRUE,	_S(5058, "������ ��� ���� ����� �ϴ� �ڿ�, ������ �Ǿ� ��� �ְ��� ���ڰ� �Ǿ� ���� �ʰڳ�?") );
						pUIManager->AddMessageBoxLString( MSGLCMD_REGISTER_MERCHANT, TRUE, _S(5059, "(��� ����ؼ� �ҹ����� �ȵȴٳ�!)" ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_REGISTER_MERCHANT, TRUE, _S(5060, "�ʿ� ���� : 50Lv~55Lv" ), -1, 0xE18600FF);
						strTemp.PrintF(_S(5061, "�ʿ� SP : %s" ), strSp);
						pUIManager->AddMessageBoxLString( MSGLCMD_REGISTER_MERCHANT, TRUE, strTemp, -1, 0xE18600FF);
						pUIManager->AddMessageBoxLString( MSGLCMD_REGISTER_MERCHANT, TRUE, _S(5062, "����ġ : 5" ), -1, 0xE18600FF);
						strTemp.PrintF(_S(5063, "���� : %s" ), strNas);
						pUIManager->AddMessageBoxLString( MSGLCMD_REGISTER_MERCHANT, TRUE, strTemp, -1, 0xE18600FF);
						strTemp.PrintF( _S( 5056, "�������� ���"), pUIManager->GetSubJobName(SUBJOB_MERCHANT) );
						pUIManager->AddMessageBoxLString( MSGLCMD_REGISTER_MERCHANT, FALSE, strTemp, 1 );
						pUIManager->AddMessageBoxLString( MSGLCMD_REGISTER_MERCHANT, FALSE, _S(1220, "����Ѵ�." ) );
					}
					break;
				case EVENT_PROMOTION2:
					{
						CUIMsgBox_Info MsgBoxInfo;

						MsgBoxInfo.m_nInputMaxChar = 24;
						MsgBoxInfo.m_nInputWidth = 130;
						MsgBoxInfo.m_nInputPosX = 44;
						MsgBoxInfo.m_nInputPosY = 48;

						MsgBoxInfo.SetMsgBoxInfo(_S(3150, "����Key �Է�"),UMBS_OKCANCEL|UMBS_INPUTBOX,UI_QUEST,MSGCMD_PROMOTION2_REQ);
						pUIManager->CreateMessageBox(MsgBoxInfo);
					}
					break;
					
				case EVENT_ATTENDANCE_2011:	// [2011/01/18 : Sora] �⼮ �̺�Ʈ
					{
						_pNetwork->SendAttendanceRewardReq();
					}
					break;
				case EVENT_COMEBACK:
					{
						CUIMsgBox_Info MsgBox;
						MsgBox.SetMsgBoxInfo( _S( 100, "�̺�Ʈ"), UMBS_OKCANCEL, UI_QUEST, MSGCMD_COMEBACK_CONFIRM );
						MsgBox.AddString( _S( 586, "�̺�Ʈ ������ ��û�Ͻðڽ��ϱ�?") );
						pUIManager->CreateMessageBox( MsgBox );
					}
					break;
				case EVENT_BIRTHDAY_GIFT:
					{
						CUIMsgBox_Info MsgBox;
						MsgBox.SetMsgBoxInfo( _S( 100, "�̺�Ʈ"), UMBS_OKCANCEL, UI_QUEST, MSGCMD_BIRTHDAY_CONFIRM );
						MsgBox.AddString( _S( 586, "�̺�Ʈ ������ ��û�Ͻðڽ��ϱ�?") );
						pUIManager->CreateMessageBox( MsgBox );
					}
					break;
				case EVENT_BIRTHDAY_INFO:
					{
						_pNetwork->SendBirthdayMessage( EVENT_BIRTHDAY_INFO );
					}
					break;
				case EVENT_TREASURE_MAP:
					{
						CNetworkMessage nmEvent( MSG_EXTEND );
						nmEvent << (ULONG)MSG_EX_TREASURE_MAP_SYSTEM_KEY_EXCHANGE;

						_pNetwork->SendToServerNew( nmEvent );
						
					}break;

				case EVENT_LOI_KRATHONG:
					{
						_pNetwork->SendEventKrathongReq();
					}
					break;

				case EVENT_KB_EXCHAGE_HEART:	// [2011/11/14 : Sora] �±� ���� ź���� �̺�Ʈ ��Ʈ�� ���� ��ȯ
					{
						CUIMsgBox_Info MsgBox;
						MsgBox.SetMsgBoxInfo( _S( 100, "�̺�Ʈ"), UMBS_OKCANCEL, UI_QUEST, MSGCMD_KB_EXCHAGE_HEART );
						MsgBox.AddString( _S( 5604, "��ȯ�� �ް� �Ǹ� ������ ��Ʈ�� ��� ������� �˴ϴ�. ��ȯ �����ðڽ��ϱ�?") );
						pUIManager->CreateMessageBox( MsgBox );
					}
					break;
				case EVENT_KB_EXCHAGE_FLAG:	// [2011/11/14 : Sora] �±� ���� ź���� �̺�Ʈ �÷��׷� �ǻ� ��ȯ
					{
						CUIMsgBox_Info MsgBox;
						MsgBox.SetMsgBoxInfo( _S( 100, "�̺�Ʈ"), UMBS_OKCANCEL, UI_QUEST, MSGCMD_KB_EXCHAGE_FLAG );
						MsgBox.AddString( _S( 5605, "�����ǻ����� ��ȯ�� �ް� �Ǹ� Father Flag �������� ������� �˴ϴ�. ���� �Ͻðڽ��ϱ�?") );
						pUIManager->CreateMessageBox( MsgBox );
					}
					break;
				case EVENT_SONGKRAN:
					{
						UIMGR()->GetTrade()->OpenUI(m_iNpcIndex);
					}
					break;
#ifdef DEMIGOD
				case EVENT_DEMIGOD_REQ:	//�Ǵн� �̺�Ʈ
				{
					_pNetwork->SendDemiGodCharacterCondition();
				}
				break;
#endif
				case BUFF_FRAG_REQ:
				{
					_pNetwork->SendBuffNPCReq(MSG_BUFF_FRAG_2021_REQ);
				}
				break;
				case BUFF_REQ:
				{
					_pNetwork->SendBuffNPCReq(MSG_BUFF_2021_REQ);
				}
				break;

			#ifdef BATTLE_PASS_SYSTEM
				case BATTLE_PASS:
				{
					_pNetwork->SendBattlePassInfoReq(m_iNpcVirIdx);
				}
				break;
			#endif
#ifdef PRESTIGE_SYSTEM
				case PRESTIGE:
				{
					_pNetwork->SendPrestigeInfoReq(m_iNpcVirIdx);
				}
				break;
#endif
				case DUNGEON_DIFFICULTY_NORMAL_NEW:
				{
					_pNetwork->RaidInzoneJoinReq(45, 0);
				}
				break;
				}
			}
		}
		break;
	case MSGLCMD_GATE_OF_DIMENSION:
		{
			if( nResult == GOD_ENTER )				// ������ �� ����
			{
				// FIXME : Hardcoding �ε���
				const int iQuestIndex = 105;
				if( CQuestSystem::Instance().CanIDoQuest( iQuestIndex ) )
				{
					if( CQuestSystem::Instance().GetDynamicDataByQuestIndex( iQuestIndex ) == NULL )
					{										
						pUIManager->GetQuestAccept()->open( iQuestIndex );
					}
					else
					{
						CTString strSysMessage;
						strSysMessage.PrintF( _S( 1687, "�̹� �������� ����Ʈ�Դϴ�."  ) );		
						_pNetwork->ClientSystemMessage( strSysMessage, SYSMSG_ERROR );
					}
				}
				else
				{
					CTString strSysMessage;
					strSysMessage.PrintF( _S( 1688, "������ ���� �ʽ��ϴ�."  ) );		
					_pNetwork->ClientSystemMessage( strSysMessage, SYSMSG_ERROR );
				}
			}
			else if( nResult == GOD_RANKING )		// ������ �� ����Ȯ��
			{
				_pNetwork->Ranking_RequestList( _pNetwork->MyCharacterInfo.job );
			}
			else if( nResult == GOD_PRIZE )			// ����.
			{
				_pNetwork->Ranking_RequestPrizeList();
			}
		}
		break;

	case MSGLCMD_CHANGEWEAPON_EVENT_REQ:
		{
			if( nResult == EVENT_CHANGEWEAPON )
			{
				pUIManager->CloseMessageBox( MSGCMD_WEAPONCHANGE_EVENT );
				CTString strMessage;
				// Create message box of remission
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo( _S( 1204, "���� ��ü �̺�Ʈ" ), UMBS_OKCANCEL,	
					UI_QUEST, MSGCMD_WEAPONCHANGE_EVENT );
				strMessage.PrintF( _S( 1213, "���⸦ ��ü�Ͻðڽ��ϱ�?" ) );				
				MsgBoxInfo.AddString( strMessage );
				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
			else
			{
			}
		}
		break;
		
	case MSGLCMD_TREASUREBOX_EVENT:
		{
			if( nResult == 1 )
			{
				_pNetwork->SendEventOpenTreasure();
			}
		}
		break;

	case MSGLCMD_EVENT_2PAN4PAN_ONE:
		{
			if(nResult == EXCH_FIVE){
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo( _S( 100, "�̺�Ʈ" ), UMBS_YESNO, UI_QUEST, MSGCMD_ASK_ONE_FIVE );
				MsgBoxInfo.AddString( _S(2219, "2pan4pan �°�ī�带 �°��ӴϷ� ��ȯ�Ͻðڽ��ϱ�?"));
				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
			else if(nResult == EXCH_FOUR){
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo( _S( 100, "�̺�Ʈ" ), UMBS_YESNO, UI_QUEST, MSGCMD_ASK_ONE_FOUR );			
				MsgBoxInfo.AddString( _S(2220, "2pan4pan ��Ŀī�带 ��Ŀ�ӴϷ� ��ȯ�Ͻðڽ��ϱ�?"));
				pUIManager->CreateMessageBox( MsgBoxInfo );
			}

		}
		break;
	case MSGLCMD_EVENT_2PAN4PAN_TWO:
		{
			if(nResult == OPEN_TREA ){
				_pNetwork->SendEvent24(0,MSG_EVENT_2PAN4PAN_BOX_REQ);

			}			
		}
		break;
		
	case MSGLCMD_EVENT_NEWYEAR1:
		{
			if(nResult == EVENT_NEWYEAR1_REWARD){
				CUIMsgBox_Info MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(169,"�̺�Ʈ"),UMBS_YESNO,UI_QUEST,MSGCMD_ASK_NEWYEAR1);
				MsgBoxInfo.AddString(_S(2296,"����ǰ�� ���� �����ðڽ��ϱ�?"));
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
		}
		break;
	case MSGLCMD_EVENT_NEWYEAR2:
		{
			if(nResult == EVENT_NEWYEAR2_TIMECHECK){
				_pNetwork->SendEventNewyear(EVENT_NEWYEAR2_TIMECHECK);				
				
			}
			else if(nResult == EVENT_NEWYEAR2_REWARD){
				CUIMsgBox_Info MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(169,"�̺�Ʈ"),UMBS_YESNO,UI_QUEST,MSGCMD_ASK_NEWYEAR2);
				MsgBoxInfo.AddString(_S(2296,"����ǰ�� ���� �����ðڽ��ϱ�?"));
				pUIManager->CreateMessageBox(MsgBoxInfo);

			}
		}
		break;

	case MSGLCMD_EVENT_FIND_FRIEND :
		{
			if( nResult == EVENT_FF_REG){
				CUIMsgBox_Info MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S( 2433, "ģ�� ã�� �̺�Ʈ"),UMBS_OKCANCEL|UMBS_INPUTBOX,UI_QUEST,MSGCMD_INPUT_FRIEND);
				MsgBoxInfo.AddString(_S( 2487, "ã�⸦ ���ϴ� ģ���� ĳ������ �Է� �ϼ���."));
				pUIManager->CreateMessageBox(MsgBoxInfo);

			} else if (nResult == EVENT_FF_TIMECHECK){
				// TODO : get TIME 
				_pNetwork->SendFindFriend(MSG_EVENT_SEARCHFRIEND_TIME_CHECK);
				
			} else if (nResult == EVENT_FF_REWARD){
				// TODO : send message to make friend list
				_pNetwork->SendFindFriend(MSG_EVENT_SEARCHFRIEND_LIST_GOODS);
			}

		}
		break;
	case MSGLCMD_CLOTHES_EXCHANGE:	// �Ϻ� ���� �ǻ� ��ȯ �̺�Ʈ eons
		{
			_pNetwork->SendClothesExchange( nResult );
		}
		break;

	case MSGCMD_WORLDCUP_EVENT1 :
		{
			switch(nResult)
			{
				case WORLDCUP_EVENT1_EXCHANGE:
				{
					if( pUIManager->DoesMessageBoxLExist( MSGCMD_WORLDCUP_EVENT1_EXCHANGE ) ) break;
					pUIManager->CreateMessageBoxL(  _S( 169, "�̺�Ʈ" ), UI_QUEST, MSGCMD_WORLDCUP_EVENT1_EXCHANGE );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_EXCHANGE, TRUE,
						_S( 2813, "������ �� ���� ��ȯ�� �ʿ��� ����� ����" ) );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_EXCHANGE, TRUE,
						_S( 2814, "�� 100�� - �����,����,��Ż����,����,�Ƹ���Ƽ��" ) );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_EXCHANGE, TRUE,
						_S( 2815, "�� 75�� - ������, �״�����, ������, ��������, ü��, ������, �߽���, ��ũ���̳�, ũ�ξ�Ƽ��" ) );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_EXCHANGE, TRUE,
						_S( 2816, "�� 50�� - �̱�, ������, ��Ʈ��ξƸ�, �������-���׳ױ׷�, ������, �Ķ����,�ѱ�, ȣ��, �Ϻ�" ) );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_EXCHANGE, TRUE,
						_S( 2817, "�� 25�� - ����, Ƣ����, ���⵵��, ���, �Ӱ��, �̶�, ����ƶ���, �ڽ�Ÿ��ī, Ʈ���ϴٵ� ��ٰ�" ) );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_EXCHANGE, FALSE, _S( 2818, "����� 100�� ��ȯ" ), WORLDCUP_EVENT1_EXCHANGE100 );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_EXCHANGE, FALSE, _S( 2819, "����� 75�� ��ȯ" ), WORLDCUP_EVENT1_EXCHANGE75 );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_EXCHANGE, FALSE, _S( 2820, "����� 50�� ��ȯ" ), WORLDCUP_EVENT1_EXCHANGE50 );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_EXCHANGE, FALSE, _S( 2821, "����� 30�� ��ȯ" ), WORLDCUP_EVENT1_EXCHANGE25 );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_EXCHANGE, FALSE, _S( 1220, "����Ѵ�." ) );
				}
				break;
				
				case WORLDCUP_EVENT1_RECEIVE:
				{
					if( pUIManager->DoesMessageBoxLExist( MSGCMD_WORLDCUP_EVENT1_RECEIVE ) ) break;
					pUIManager->CreateMessageBoxL(  _S( 169, "�̺�Ʈ" ), UI_QUEST, MSGCMD_WORLDCUP_EVENT1_RECEIVE );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_RECEIVE, TRUE,
						_S( 2822, "�౸ ��ȸ ��� " ) );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_RECEIVE, TRUE,
						_S( 2823, "1�� ����" ) );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_RECEIVE, TRUE,
						_S( 2824, "2�� ����" ) );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_RECEIVE, TRUE,
						_S( 2825, "3�� ����" ) );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_RECEIVE, FALSE, _S( 2826, "1�� ����" ), WORLDCUP_EVENT1_REWARD1 );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_RECEIVE, FALSE, _S( 2827, "2�� ����" ), WORLDCUP_EVENT1_REWARD2 );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_RECEIVE, FALSE, _S( 2828, "3�� ����" ), WORLDCUP_EVENT1_REWARD3 );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_RECEIVE, FALSE, _S( 2829, "�׿� ���� ����" ), WORLDCUP_EVENT1_REWARD4 );
					pUIManager->AddMessageBoxLString( MSGCMD_WORLDCUP_EVENT1_RECEIVE, FALSE, _S( 1220, "����Ѵ�." ) );
				}
				break;
			}
		}
		break;

	
	case MSGCMD_WORLDCUP_EVENT1_EXCHANGE :
		{
			nResult-=WORLDCUP_EVENT1_EXCHANGE100;

			if(nResult >= 0 && nResult < WORLDCUP_MAX_GROUP )
			{

				CUIMsgBox_Info MsgBoxInfo;
				CTString strMessage;
				strMessage.PrintF(_S( 2830, "������� ��ȯ�� �������� ������ �ּ���."));
				
				MsgBoxInfo.SetMsgBoxInfo(_S(191,"Ȯ��"),UMBS_YESNO | UMBS_COMBOBOX ,UI_QUEST,MSGCMD_WORLDCUP_EVENT1_NUM);
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);

				iSelGroup = nResult;
				pUIManager->GetMessageBox(MSGCMD_WORLDCUP_EVENT1_NUM)->GetComboBox().ResetStrings();
				for(int i=iGroup[iSelGroup] ; i<iGroup[iSelGroup+1]; i++  )
				{
					pUIManager->GetMessageBox(MSGCMD_WORLDCUP_EVENT1_NUM)->GetComboBox().AddString(m_strCountry[i]);
				}
			}
							
		}
		break;
	case MSGCMD_WORLDCUP_EVENT1_RECEIVE :
		{
			nResult-=WORLDCUP_EVENT1_REWARD1;

			if(nResult >= 0 && nResult < WORLDCUP_MAX_GROUP )
			{
				_pNetwork->SendWorldCupEvent(MSGCMD_WORLDCUP_EVENT1_RECEIVE,nResult+1);
			}
								
		}
		break;

	case MSGCMD_WORLDCUP_GOLDENBALL:
		{
			switch( nResult )
			{
			case MSGCMD_WORLDCUP_GOLDENBALL_ENTRY:
				{
					if( pUIManager->DoesMessageBoxExist( MSGCMD_GOLDENBALL_EVENT ) )
						return;

					if( !m_bGoldenBallEntry )
					{
						_pNetwork->ClientSystemMessage( _S( 2831, "���� ���� ���� �ð��� �ƴմϴ�." ), SYSMSG_ERROR );
						return;
					}
					
					CTString strMessageA, strMessageB;
					strMessageA.PrintF( _S( 2832, "%s VS %s ���\n\n�¸������� ������ �����Ͽ� �Է��� �ּ���\n\n" ), m_strTeamA, m_strTeamB );
					strMessageB.PrintF( _S( 2833, "%-5s����     %-5s����" ), m_strTeamA, m_strTeamB );

					strMessageA += strMessageB;

					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo( _S( 2834, "��� �� �̺�Ʈ" ), UMBS_OKCANCEL | UMBS_INPUTBOX | UMBS_SECOND_INPUTBOX,
																UI_NONE, MSGCMD_GOLDENBALL_EVENT );

					MsgBoxInfo.AddString( strMessageA, 0xF2F2F2FF, TEXT_CENTER );
					MsgBoxInfo.SetMaxRow( 8 );

					MsgBoxInfo.SetInputBox( 7, 6, 2, 30 );
					MsgBoxInfo.SetSEInputBox( 7, 12, 2, 30, 54 );

					pUIManager->CreateMessageBox( MsgBoxInfo );
				}
				break;
			case MSGCMD_WORLDCUP_GOLDENBALL_REQUITAL:
				{
					_pNetwork->SendWorldCupGoldenBallEvent( MSG_EVENT_GOLDENBALL_GIFT, 0, 0 );
				}
				break;
			}
		}		
		break;
	case MSGLCMD_RAINYDAY:	// �Ϻ� ����� �̺�Ʈ
	case MSGLCMD_MOTHERDAY: // �±� ��Ӵϳ� �̺�Ʈ
		{
			if( nResult == 1)
			{
				_pNetwork->SendRainyDayExchange();
			}
		}
		break;
	case MSGLCMD_BUDDHISM_EVENT:
		{
			if( nResult >= 0 && nResult <= 6 )
			{ _pNetwork->SendBuddhismEvent( (BYTE)nResult ); }
		}
		break;
	case MSGLCMD_COLLECT_INSECT_EVENT:
		{
			switch( nResult )
			{
			case 0:
				{// ����
					pUIManager->CloseMessageBox( MSGCMD_COLLECTBOX_BUY_REQ );

					CTString strMessage;
					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo( _S( 191, "Ȯ��" ), UMBS_YESNO, UI_QUEST, MSGCMD_COLLECTBOX_BUY_REQ );
					strMessage.PrintF( _S( 2955, "���� �̺�Ʈ�� ���� ä�������� ������ 100���� �Դϴ�. �����Ͻðڽ��ϱ�?" ) );
					MsgBoxInfo.AddString( strMessage );
					pUIManager->CreateMessageBox( MsgBoxInfo );
				}
				break;
			case 1:
				{// ����
					if( pUIManager->DoesMessageBoxLExist( MSGLCMD_COLLECT_BOX_GIFT ) ) break;
					pUIManager->CreateMessageBoxL( _S( 2954, "���� ä������ ����" ), UI_QUEST, MSGLCMD_COLLECT_BOX_GIFT );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2956, "���� ä�����ڸ� ��� ä�� ���̳���?" ) );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE,
						_S( 2957, "ä������ �ȿ� �ִ� ������ ����Ʈ �հ迡 ���� �Ʒ��� ����ǰ�� ��ȯ�� �帮�ڽ��ϴ�." ) );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE,
						_S( 2958, "�̺�Ʈ�Ⱓ ������ ���� �� �ٽ� ���� ä�����ڸ� �����Ͽ� �̺�Ʈ�� ��� �� �� �ֽ��ϴ�." ) );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, CTString(" ") );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 1866, "����ǰ" ), -1, 0x6BD2FFFF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2959, "1~25 ����Ʈ: 500����" ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2960, "26~40 ����Ʈ: �޸� ��ũ�� 3��" ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2961, "41~55 ����Ʈ: ���� ���� ȸ���� 5��" ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2962, "56~70 ����Ʈ: ���� ü�� ȸ���� 5��" ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2963, "71~85 ����Ʈ: ������ 2��" ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2964, "86~100 ����Ʈ: ������ 5��" ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2965, "101~115 ����Ʈ: ������ ���� 2��" ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2966, "116~120 ����Ʈ: ������ �ڵ� 2��" ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2967, "121~125 ����Ʈ: ������ ���� 2��" ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2968, "126~130 ����Ʈ: ���� ���ü� 1��" ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2969, "131~159 ����Ʈ: ���� ���ü� 2��" ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, TRUE, _S( 2970, "160 ����Ʈ �̻�: ���� ���ü� 3��" ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, FALSE, _S( 2971, "���� ä������ ���� �ޱ�" ), 0 );
					pUIManager->AddMessageBoxLString( MSGLCMD_COLLECT_BOX_GIFT, FALSE, _S( 1220, "����Ѵ�." ) );
				}
				break;
			}
		}
		break;
	case MSGLCMD_COLLECT_BOX_GIFT:
		{
			if( nResult == 0 )
			{
				_pNetwork->SendGiftCollectBox();
			}
		}
		break;
	case MSGLCMD_EVENT_PROMOPACK:
		{
			if( nResult == EVENT_PROMO_KEY_ENTER )
			{
				CUIMsgBox_Info MsgBoxInfo;
				int tmpInputMaxChar = 12;

				MsgBoxInfo.m_nInputMaxChar = tmpInputMaxChar;
				MsgBoxInfo.m_nInputWidth = 78;
				MsgBoxInfo.m_nInputPosX = 70;
				MsgBoxInfo.m_nInputPosY = 48;

				if (IsGamigo(g_iCountry) == TRUE)
				{
					if ( g_iCountry != FRANCE )
					{
						MsgBoxInfo.m_nInputMaxChar = 20;
						MsgBoxInfo.m_nInputWidth = 130;
						MsgBoxInfo.m_nInputPosX = 44;
					}
				}

				MsgBoxInfo.SetMsgBoxInfo(_S(3150, "Serial Key Enter"),UMBS_OKCANCEL|UMBS_INPUTBOX,UI_QUEST,MSGCMD_EVENT_COUPON_SENDNUM);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
		}
		break;
	case MSGLCMD_EVENT_LOVE_LOVE:
		{
			if (nResult == 0 )
			{
				if (pUIManager->DoesMessageBoxExist(MSGCMD_OK_EXCHANGE_CHOCOBOX) ||
					pUIManager->DoesMessageBoxExist(MSGCMD_OK_EXCHANGE_LUCKYBOX))
					return;

				CUIMsgBox_Info MsgBoxInfo;
				CTString strMessage, strTitle;
				int nCommand;

				if (IS_EVENT_ON(TEVENT_LUNARNEWYEAR_2008))
				{
					strMessage = _S(4008, "�Ҹ����ڸ� �ø� �� Ȯ�ι�ư�� Ŭ���ϼ���");
					strTitle = _S(4006, "�Ҹ����� ��ȯ");
					nCommand = MSGCMD_OK_EXCHANGE_LUCKYBOX;
				}
				else
				{
					strMessage = _S(3217, "���ڻ��ڸ� �ø� �� Ȯ�ι�ư�� Ŭ���ϼ���");
					strTitle = _S(3216, "���ڻ��� ��ȯ");
					nCommand = MSGCMD_OK_EXCHANGE_CHOCOBOX;
				}

				MsgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_YESNO | UMBS_BUTTONEX, UI_QUEST, nCommand);
				MsgBoxInfo.SetBtnType(UBET_ITEM, CItemData::ITEM_ONCEUSE, CItemData::ITEM_SUB_BOX);
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
		}
		break;
	
		// wooss 070305	------------------------------>>
		// kw : WSS_WHITEDAY_2007
	case  MSGLCMD_WHITEDAY_2007:
		{
			CTString tstr;
			switch(nResult)
			{
				case EVENT_REWARD_1:
					// TODO : ������� �ֹ��� �޴´�.
				case EVENT_REWARD_2:
					// TODO : �ϴû� �������� ��ȯ
				case EVENT_REWARD_3:
					// TODO : ��ȫ�� �������� ��ȯ
					_pNetwork->SendWhiteday2007((UBYTE)(nResult - EVENT_REWARD_1));
					break;

			}

		} // MSGLCMD_WHITEDAY_2007
		break;	
		// ---------------------------------------------<<
	case MSGLCMD_EVENT_MAY:
		{
			switch(nResult)
			{
				case EVENT_MAY_PARENTS:
					{
						// TODO : ����̳� �̺�Ʈ 
						// WSS_GUILDMASTER 070411 -------------------------------------------------------------->>						
						if( pUIManager->DoesMessageBoxLExist( MSGLCMD_GUILDMASTER ) ) break;
						pUIManager->CreateMessageBoxL(  _S( 169, "�̺�Ʈ" ), UI_QUEST, MSGLCMD_GUILDMASTER );
						pUIManager->AddMessageBoxLString( MSGLCMD_GUILDMASTER, TRUE,CTString(""));
						pUIManager->AddMessageBoxLString( MSGLCMD_GUILDMASTER, TRUE,_S(3445, "����̳� �̺�Ʈ�� ����̳��� �����Ͽ� ���� ī���̼��� �������� ��帶���Ϳ��� ������ �ϴ� �̺�Ʈ�Դϴ�."));
						pUIManager->AddMessageBoxLString( MSGLCMD_GUILDMASTER, TRUE,_S(3446, "��� �����ʹ� ���� ī���̼��� ������ �ް� �̸� ��� ����Ʈ�� ����Ͽ� ���� ���� ������ ���� ��带 �̴� �̺�Ʈ �Դϴ�."));
						pUIManager->AddMessageBoxLString( MSGLCMD_GUILDMASTER, TRUE,CTString(""));
						pUIManager->AddMessageBoxLString( MSGLCMD_GUILDMASTER, FALSE,_S(3447, "��� ����Ʈ"), EVENT_REWARD_1 );
						pUIManager->AddMessageBoxLString( MSGLCMD_GUILDMASTER, FALSE,_S(3448, "��ȯ��"), EVENT_REWARD_2 );
						pUIManager->AddMessageBoxLString( MSGLCMD_GUILDMASTER, FALSE, _S( 1220, "����Ѵ�." ) );
						// ---------------------------------------------------------------------------------------<<
					
					}
					break;
				case EVENT_MAY_MASTER:
					{
						// TODO : �����ǳ� �̺�Ʈ
// [KH_070413] �����ǳ� �̺�Ʈ ���� �߰�
						if(!ItemHelp::HaveItem(MEDAL_OF_TEACHER) &&
							!ItemHelp::HaveItem(MEDAL_OF_DISCIPLE))
						{
							CUIMsgBox_Info MsgBoxInfo;
							MsgBoxInfo.SetMsgBoxInfo(_S(3344, "������ ���� �̺�Ʈ"), UMBS_OK, UI_NONE,MSGCMD_NULL);
							MsgBoxInfo.AddString(_S(3345, "������ ���� �̺�Ʈ�� �����Ͽ� ������. �׷� ���� ���� ���� �ſ���."));
							pUIManager->CreateMessageBox(MsgBoxInfo);
						}
						else
							_pNetwork->SendEventMaster();
					}
					break;
			}
		}			
		break;
		// --------------------------------------------<<

	// WSS_GUILDMASTER 070411 -------------------------------------------------------------->>
	case MSGLCMD_GUILDMASTER:
		{
			switch(nResult)
			{
				case EVENT_REWARD_1:
					{
						pUIManager->CloseMessageBox(MSGCMD_GUILDMASTER_1);
						CUIMsgBox_Info	MsgBoxInfo;
						CTString strTitle =_S(169, "�̺�Ʈ");
						MsgBoxInfo.SetMsgBoxInfo( strTitle, UMBS_LISTBOX|UMBS_USER_12 | UMBS_ALIGN_CENTER , UI_QUEST, MSGCMD_GUILDMASTER_1 );
						MsgBoxInfo.SetUserBtnName( _S(2489, "���" ), _S(3449, "����") );
						MsgBoxInfo.SetListBoxPlacement(5,25,330,100,5,3);
						pUIManager->CreateMessageBox( MsgBoxInfo );
						CUIListBox* tBox = &pUIManager->GetMessageBox(MSGCMD_GUILDMASTER_1)->GetListBox();
						tBox->ResetAllStrings();
						tBox->AddString( 0, _S(1714, "����"),0xF2F2F2FF, FALSE );
						tBox->AddString( 1, _S(3450, "����Ʈ"),0xF2F2F2FF, FALSE );
						tBox->AddString( 2, _S(3451, "����"),0xF2F2F2FF, FALSE );						
						
						// Adjust column position of list box
						int tSpc = _pUIFontTexMgr->GetFontWidth();
						tBox->SetColumnPosX( 0, 5*tSpc, TEXT_CENTER );
						tBox->SetColumnPosX( 1, 25*tSpc, TEXT_RIGHT );
						tBox->SetColumnPosX( 2, 45*tSpc, TEXT_CENTER );						

						// ��� ����Ʈ ��û...
						_pNetwork->SendRequestParentsday( MSG_EVENT_PARENTSDAY_2007_ACCUMULATEPOINT_RANKING_LIST);
					}
					break;					
				case EVENT_REWARD_2:
					{						
						if( pUIManager->DoesMessageBoxLExist( MSGLCMD_GUILDMASTER_2 ) ) break;
						pUIManager->CreateMessageBoxL(  _S( 169, "�̺�Ʈ" ), UI_QUEST, MSGLCMD_GUILDMASTER_2 );
						pUIManager->AddMessageBoxLString( MSGLCMD_GUILDMASTER_2, TRUE,	CTString(" "));
						pUIManager->AddMessageBoxLString( MSGLCMD_GUILDMASTER_2, TRUE,	_S(3466, "��� ����Ʈ 100����Ʈ�� ��ȯ�� 1���� ���� �� �ֽ��ϴ�. ���� ���� ��ȯ���� ����Ͽ� ��ǰ�� �޾� ������� �̺�Ʈ�� ��� ������." ) );
						pUIManager->AddMessageBoxLString( MSGLCMD_GUILDMASTER_2, FALSE, _S(3467, "��ȯ�� �ޱ�" ), EVENT_REWARD_1 );
						pUIManager->AddMessageBoxLString( MSGLCMD_GUILDMASTER_2, FALSE, _S(3468, "��ȯ�� ����ϱ�" ), EVENT_REWARD_2 );
						pUIManager->AddMessageBoxLString( MSGLCMD_GUILDMASTER_2, FALSE, _S(1220, "����Ѵ�." ) );
						
					}
					break;			
			}
		}			
		break;
	case MSGLCMD_GUILDMASTER_2:
		{
			// TODO : ��ȯ��
			switch(nResult)
			{
				case EVENT_REWARD_1:
					{
						// ��ȯ�� �ޱ�
						pUIManager->CloseMessageBox(MSGCMD_GUILDMASTER_2_1);
						CUIMsgBox_Info	MsgBoxInfo;
						CTString strMessage =_S(169, "�̺�Ʈ");
						MsgBoxInfo.SetMsgBoxInfo( strMessage, UMBS_OKCANCEL, UI_QUEST, MSGCMD_GUILDMASTER_2_1 );
						strMessage = _S(3452, "������ ��ȯ���� �����ðڽ��ϱ�?");
						MsgBoxInfo.AddString(strMessage);
						pUIManager->CreateMessageBox( MsgBoxInfo );
					}
					break;					
				case EVENT_REWARD_2:
					{	
						// ��ȯ�� ����ϱ�
						_pNetwork->SendRequestParentsday( MSG_EVENT_PARENTSDAY_2007_EXCHANGE_ITEM);
						
					}
					break;			
			}

		}
		break; 
	// --------------------------------------------------------------------------------------<<

	// WSS_EVENT_MINIGAME 070420 ------------------------------------------------------------>>
	case MSGLCMD_EVENT_MINIGAME:
		{
			switch(nResult)
			{
				case EVENT_REWARD_1:
					{
						// TODO : ���������� �����ϱ�
						if (IS_EVENT_ON(TEVENT_GOMDOLI))
						{
							// Send MSG_EVENT_GOMDORI_2007_CHECKITEM 	
							_pNetwork->SendMinigameDefaultMessage(MSG_EVENT_GOMDORI_2007, MSG_EVENT_GOMDORI_2007_CHECKITEM);
						}
						else if (IS_EVENT_ON(TEVENT_XMAS_2007))
						{
							_pNetwork->SendMinigameDefaultMessage(MSG_EVENT_XMAS_2007, MSG_EVENT_XMAS_PUZZLE_CHECKITEM_REQ);
						}
					}
					break;					
				case EVENT_REWARD_2:
					{
						// TODO : ������ ���� ���� ã�� ��Ȳ����
						if (IS_EVENT_ON(TEVENT_GOMDOLI))
							_pNetwork->SendMinigameDefaultMessage(MSG_EVENT_GOMDORI_2007, MSG_EVENT_GOMDORI_2007_VIEW_STATUS);					
					}
					break;				
			}
		}			
		break;

	case MSGLCMD_SIEGE_WARFARE_UPGRADE:
		{
			switch(nResult)
			{
				case EVENT_REWARD_1:  // ������ ��ȭ
					{
						pUIManager->GetSiegeWarfareNew()->SetUpgradeType( SWUT_ATTACK );						
						pUIManager->GetSiegeWarfareNew()->SendTowerStateRequest(SWUT_ATTACK);				
						
					}
					break;					
				case EVENT_REWARD_2:  // ������ ��ȭ
					{
						pUIManager->GetSiegeWarfareNew()->SetUpgradeType( SWUT_GUARD );						
						pUIManager->GetSiegeWarfareNew()->SendTowerStateRequest(SWUT_GUARD);
										
					}
					break;				
			}
		}			
		break;
	// -----------------------------------------------------------------------------------------<<
		
	// [070705: Su-won] EVENT_SUMMER_2007
	case MSGLCMD_SUMMER_2007:
		{
			switch(nResult)
			{
				case EVENT_REWARD_1:
					{
						//���� ����
						pUIManager->CloseMessageBox(MSGCMD_SUMMER2007_PAPERFOLDING);
						CUIMsgBox_Info	MsgBoxInfo;
						CTString strMessage =_S(3569, "��������");
						MsgBoxInfo.SetMsgBoxInfo( strMessage, UMBS_OKCANCEL | UMBS_BUTTONEX, UI_QUEST, MSGCMD_SUMMER2007_PAPERFOLDING );
						MsgBoxInfo.SetBtnType( UBET_ITEM, CItemData::ITEM_ETC, CItemData::ITEM_ETC_MATERIAL, 3 );
						strMessage = _S(3571, "�������⸦ �� �����̸� �÷� ��������.");
						MsgBoxInfo.AddString(strMessage);
						strMessage = _S(3572, "�������⿡�� 100������ �ʿ��մϴ�.");
						MsgBoxInfo.AddString(strMessage);
						pUIManager->CreateMessageBox( MsgBoxInfo );
					}
					break;					
				case EVENT_REWARD_2:
					{
						//������ ����
						pUIManager->CloseMessageBox(MSGCMD_SUMMER2007_PAPERBLENDING);
						CUIMsgBox_Info	MsgBoxInfo;
						CTString strMessage =_S(3570, "������ ����");
						MsgBoxInfo.SetMsgBoxInfo( strMessage, UMBS_OKCANCEL | UMBS_BUTTONEX, UI_QUEST, MSGCMD_SUMMER2007_PAPERBLENDING );
						MsgBoxInfo.SetBtnType( UBET_ITEM, CItemData::ITEM_ETC, CItemData::ITEM_ETC_MATERIAL);
						strMessage = _S(3573, "������ �����̸� �÷� ��������.");
						MsgBoxInfo.AddString(strMessage);
						strMessage = _S(3574, "������ ������ 5���� �����Ͽ� ���� ������ 1���� ������ �� �ֽ��ϴ�.");
						MsgBoxInfo.AddString(strMessage);
						strMessage = _S(3575, "��! ������ ���� ������ �����ϼ���.");
						MsgBoxInfo.AddString(strMessage);
						pUIManager->CreateMessageBox( MsgBoxInfo );
					}
					break;				
			}
		}			
		break;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// [070807: Su-won] EVENT_ADULT_OPEN
	case MSGLCMD_EVENT_ADULT_MAGICCARD:
		{
			if( nResult ==0)
			{
				_pNetwork->SendAdultOpenEventReq(0);
			}
		}
		break;
	case MSGLCMD_EVENT_ADULT_CHANGEJOB:
		{
			if( nResult ==0)
			{
				_pNetwork->SendAdultOpenEventReq(1);
			}
		}
		break;
	case MSGLCMD_EVENT_ADULT_ALCHEMIST:
		{
			if( nResult ==0 )
			{
				pUIManager->CloseMessageBox(MSGCMD_ADULTEVENT_ALCHEMIST);

				CUIMsgBox_Info	MsgBoxInfo;
				CTString strMessage =_S(3635, "������� ���ݼ� �̺�Ʈ");
				MsgBoxInfo.SetMsgBoxInfo( strMessage, UMBS_OKCANCEL | UMBS_BUTTONEX, UI_QUEST, MSGCMD_ADULTEVENT_ALCHEMIST );
				MsgBoxInfo.SetBtnType(UBET_ITEM, -1, -1);

				strMessage = _S(3636, "������ ��� �÷��ּ���.");
				MsgBoxInfo.AddString(strMessage);
				MsgBoxInfo.AddString(CTString(" "));

				strMessage = _S(2462, "�ʿ� ���");
				MsgBoxInfo.AddString(strMessage, 0xE18600FF);
				MsgBoxInfo.AddString(CTString(" "));
				MsgBoxInfo.AddString(CTString(" "));

				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
		}
		break;
		// [070807: Su-won] EVENT_ADULT_OPEN
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case MSGLCMD_TG2007_FRUITFULL: // WSS_TG2007 2007/09/14
		{
			switch(nResult)
			{
				case EVENT_REWARD_1:  // ���� �ܰ�� ���׷��̵� �Ѵ�.
					{
						// TODO ::  ���׷��̵� ��û
						_pNetwork->SendTG2007RichYearReq(MSG_EVENT_RICHYEAR_UPGRADE);
					}
					break;					
				case EVENT_REWARD_2:  // ����ǰ�� ���� �޴´�.
					{
						// TODO ::  ����ǰ ���� ��û	
						_pNetwork->SendTG2007RichYearReq(MSG_EVENT_RICHYEAR_EXCHANGE);
					
					}
					break;				
			}
		}			
		break;

		// ������ ���� ���� ����
	case MSGLCMD_RED_TREASUREBOX_EVENT:
		{
			if( nResult == 1 )
			{
				CNetworkMessage nmEvent( MSG_EVENT );
				nmEvent << (UBYTE)MSG_EVENT_TREASUREBOX_RED;
				nmEvent << (UBYTE)MSG_EVENT_TREASUREBOX_RED_OPEN_REQ;
				nmEvent << _pNetwork->MyCharacterInfo.index;
				_pNetwork->SendToServerNew( nmEvent );
			}
		}
		break;

	// [080422: Su-won] EVENT_CHAOSBALL
	case MSGLCMD_CHAOSBALL_EVENT:
		{
			if( nResult == 1)
			{
				if (pUIManager->DoesMessageBoxExist(MSGCMD_EVENT_CHAOSBALL))
					pUIManager->CloseMessageBox(MSGCMD_EVENT_CHAOSBALL);

				CUIMsgBox_Info	MsgBoxInfo;
				CTString strMessage =_S(4132, "ī���� �� ���������ϱ�");
				MsgBoxInfo.SetMsgBoxInfo( strMessage, UMBS_OKCANCEL | UMBS_BUTTONEX, UI_QUEST, MSGCMD_EVENT_CHAOSBALL );
				MsgBoxInfo.SetBtnType( UBET_ITEM, CItemData::ITEM_ETC, CItemData::ITEM_ETC_MATERIAL, 1 );
				strMessage = _S(4133, "ī���� ���� �ø� �� Ȯ�� ��ư�� Ŭ���ϼ���.");
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
		}
		break;

	// ($E_WC2010) [100514: selo] 2010 ���ư� ������ �̺�Ʈ2 ��� ���� �����ϱ�
	case MSGLCMD_EVENT_WORLDCUP_EVENT2:
		{
			if( nResult == EVENT_WORLDCUP_2010_EVENT2_SEL1 )		// ��� ���� ����
			{
				_pNetwork->SendWorldCup2010_Event(MSG_EVENT_WORLDCUP2010_TOTO_STATUS_REQ, EVENT_WORLDCUP_2010_EVENT2_SEL1);
			}			
			else if( nResult == EVENT_WORLDCUP_2010_EVENT2_SEL2 )	// �� ���� ��Ȳ
			{
				_pNetwork->SendWorldCup2010_Event(MSG_EVENT_WORLDCUP2010_TOTO_STATUS_REQ, EVENT_WORLDCUP_2010_EVENT2_SEL2);
			}
			else if( nResult == EVENT_WORLDCUP_2010_EVENT2_SEL3 )	// ��÷ ���� �ޱ�
			{
				_pNetwork->SendWorldCup2010_Event(MSG_EVENT_WORLDCUP2010_TOTO_GIFT_REQ);
			}
		}
		break;
	// ($E_WC2010) [100514: selo] 2010 ���ư� ������ �̺�Ʈ3 ���� ���� �����ϱ�
	case MSGLCMD_EVENT_WORLDCUP_EVENT3:
		{
			if( nResult == EVENT_WORLDCUP_2010_EVENT3_SEL1 )
			{
				_pNetwork->SendWorldCup2010_Event(MSG_EVENT_WORLDCUP2010_KOREA_REQ);
			}
		}
		break;
	case MSGLCMD_ATTENDANCE_SYSTEM:
		{	// �⼮ �ý��� ���� ��û (100��, 200��, 365�� ���� �⼮�� ��� ���� ����)
			if ( nResult == 0)
			{
				_pNetwork->SendAttendanceReq( 1 );
			}
		}
		break;
	case MSGLCMD_REGISTER_MERCHANT:	// [2010/08/25 : Sora] ADD_SUBJOB
		{
			if( nResult == 1)
			{
				if (pUIManager->DoesMessageBoxExist(MSGCMD_REGISTER_MERCHANT))
					pUIManager->CloseMessageBox(MSGCMD_REGISTER_MERCHANT);

				CUIMsgBox_Info	MsgBoxInfo;
				CTString strMessage =_S( 2489,"���");
				MsgBoxInfo.SetMsgBoxInfo( strMessage, UMBS_OKCANCEL, UI_QUEST, MSGCMD_REGISTER_MERCHANT );
				strMessage = _S( 5064, "�������� ��� �Ͻðڽ��ϱ�?");
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
		}
		break;
	case MSGLCMD_SYNDICATE_JEWEL_GIVE:
		{
			if (nResult < 0)
				break;

			if( pUIManager->DoesMessageBoxExist( MSGLCMD_SYNDICATE_JEWEL_GIVE ) ) 
				return;

			CUIMsgBox_Info MsgBoxInfo;
			CTString strMessage;

			strMessage.PrintF(_S(6114, "â���� ���� ���" ));
			MsgBoxInfo.SetMsgBoxInfo( strMessage, UMBS_YESNO | UMBS_BUTTONEX, UI_QUEST, MSGCMD_SYNDICATE_PUTON_JEWEL_REQ );
			strMessage.PrintF(_S(6115,  "�Ʒ��� ���Կ� ����� â���� ������ �÷������� �� ��� ��ư�� �����ּ���." ));
			MsgBoxInfo.SetBtnType( UBET_ITEM, CItemData::ITEM_ETC, CItemData::ITEM_ETC_SYNDICATEJEWEL );	// ������ Ÿ�� ���� �ؾ���.
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );		
		}
		break;
	case MSGLCMD_SYNDICATE_SECESSION_REQ:
		{
			if (nResult < 0)
				break;

			if( pUIManager->DoesMessageBoxExist( MSGCMD_SYNDICATE_SECESSION_REQ ) ) 
				return;

			GameDataManager* pGameData = GameDataManager::getSingleton();

			if (pGameData == NULL)
				break;

			CSyndicate* pSyndicateData = pGameData->GetSyndicate();

			if (pSyndicateData == NULL)
				break;

			CTString strSyndicateName = pSyndicateData->GetSyndicateName(_pNetwork->MyCharacterInfo.iSyndicateType);

			CUIMsgBox_Info	MsgBoxInfo;
			CTString strMessage =_S( 6123,"���� Ż�� ��û");
			MsgBoxInfo.SetMsgBoxInfo( strMessage, UMBS_YESNO | UMBS_BUTTONEX, UI_QUEST, MSGCMD_SYNDICATE_SECESSION_REQ );
			
			strMessage.PrintF(_S( 6124,
				"���뿡�� Ż�� �ÿ��� �� ���� �����Ǿ��� �⿩���� ��� �ʱ�ȭ�Ǹ� �Ʒ��� ���� ������� ���� �ϼž� �մϴ�."));
			MsgBoxInfo.AddString( strMessage );

			CTString strTemp;
			strTemp.PrintF("%I64d", pSyndicateData->GetSecssionNas());
			pUIManager->InsertCommaToString(strTemp);
			strMessage.PrintF(_S( 6125, "�����:%s ����"), strTemp);
			MsgBoxInfo.AddString( strMessage );

			strMessage.PrintF(_S( 6285,
				"��, ���� Ż�� ���Ƽ��å ���� ����Ͻø� �⿩�� �϶��� ����� ���� Ż�� �����մϴ�."),
				pSyndicateData->GetSecssionNas());
			MsgBoxInfo.AddString( strMessage );

			MsgBoxInfo.SetBtnType( UBET_ITEM, CItemData::ITEM_ETC, CItemData::ITEM_ETC_MATERIAL );

			strMessage.PrintF(_S( 6126, "[%s] ���븦 ������ Ż�� �Ͻðڽ��ϱ�?"), strSyndicateName);
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
			pUIManager->GetMessageBox(MSGCMD_SYNDICATE_SECESSION_REQ)->GetBtnOK().SetEnable(TRUE);

		}
		break;
	}
}

// ----------------------------------------------------------------------------
//  [5/17/2010 selo0530] ($E_WC2010)
//
//	Name : CreateMessageBox_WorldCup2010_Event2
//	Desc : 2010 ���ư� ������ ��� ���� ���߱� �޽��� �ڽ�
//	Info : nType ���� ���
// ----------------------------------------------------------------------------
void CUIQuest::CreateMessageBox_WorldCup2010_Event2( INDEX nType )
{	
	CTString strTitle;
	CTString strDesc;
	int nCommand = -1;
	int nBtnCnt = 1;

	switch( nType )
	{
	case EVENT_WORLDCUP_2010_EVENT2_SEL1:
		{
			strTitle = _S(4908, "��� ���� ����");
			strDesc = _S(4913, "����� �����ϴ� ������ ���� �������� ����� �ּ���. ���� �������� ��ϰ� ���ÿ� ���� �ǿ���, �����ϰ� ������ �ּ���.");
			nCommand = MSGCMD_EVENT_WORLDCUP_EVENT2_REQ;			
		}
		break;	
	default:	// �ش� ���� ������ �׳� �����Ͽ� �޽��� �ڽ��� ������ �ʴ´�.
		return;
	}	


	CUIMsgBox_Info	MsgBoxInfo;	
	MsgBoxInfo.SetMsgBoxInfo( strTitle, UMBS_OKCANCEL | UMBS_BUTTONEX, UI_QUEST, nCommand );
	MsgBoxInfo.SetBtnType(UBET_ITEM, CItemData::ITEM_ETC, CItemData::ITEM_ETC_EVENT, nBtnCnt);
	MsgBoxInfo.AddString(strDesc);
	MsgBoxInfo.AddString(CTString(" "));
	
	CUIManager::getSingleton()->CreateMessageBox( MsgBoxInfo );
}

// ----------------------------------------------------------------------------
// Name : CloseQuest()
// Desc :
// ----------------------------------------------------------------------------
void CUIQuest::CloseQuest()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// Close message box of remission
	pUIManager->CloseMessageBox( MSGCMD_QUEST_NOTIFY );
	pUIManager->CloseMessageBox( MSGCMD_QUEST_NEWQUEST );
		
	pUIManager->CloseMessageBoxL( MSGLCMD_QUEST_REQ); 
	pUIManager->CloseMessageBoxL( MSGLCMD_EVENT_2PAN4PAN_ONE); 
	pUIManager->CloseMessageBoxL( MSGLCMD_EVENT_2PAN4PAN_TWO); 

	pUIManager->CloseMessageBox( MSGCMD_ASK_ONE_FIVE );   
	pUIManager->CloseMessageBox( MSGCMD_ASK_ONE_FOUR );
	pUIManager->CloseMessageBox( MSGCMD_ASK_TWO_OPEN );   

	pUIManager->CloseMessageBox( MSGLCMD_EVENT_NEWYEAR1);
	pUIManager->CloseMessageBox( MSGLCMD_EVENT_NEWYEAR2);

	pUIManager->RearrangeOrder( UI_QUEST, FALSE );
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CUIQuest::Render()
{
	// Check distance
	FLOAT	fDiffX = _pNetwork->MyCharacterInfo.x - m_fNpcX;
	FLOAT	fDiffZ = _pNetwork->MyCharacterInfo.z - m_fNpcZ;
	if( fDiffX * fDiffX + fDiffZ * fDiffZ > UI_VALID_SQRDIST )
		CloseQuest();
}

// ----------------------------------------------------------------------------
// Name : MsgBoxCommand()
// Desc :
// ----------------------------------------------------------------------------
void CUIQuest::MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// WSS_GUILDMASTER 070416
	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;	

	CMobData* MD = CMobData::getData(m_iNpcIndex);
	LONGLONG lNpcVIndex = 0;
	CEntity* pEntity = NULL;

	pEntity = INFO()->GetTargetEntity(eTARGET);
	
	if (pEntity != NULL)
		lNpcVIndex = pEntity->GetNetworkID();	// npc virtual index

	switch( nCommandCode )
	{
	case MSGLCMD_REMOVE_SELECTED_BUFF:
		if( bOK ) {
			_pNetwork->SendRemoveBuffReq(_pUIBuff->GetBuffSelectedItem(), _pUIBuff->GetBuffSelectedSkill());
		}
		break;
	case MSGLCMD_REBORN_REQ:
		if( bOK ) {
			_pNetwork->SendRebornReq(lNpcVIndex);
		}
		break;
	case MSGLCMD_EXCHANGE_HEALER:
		if( bOK ) {
			_pNetwork->SendClassChange(HEALER, lNpcVIndex);
		}
		break;
	case MSGLCMD_EXCHANGE_KNIGHT:
		if( bOK ) {
			_pNetwork->SendClassChange(KNIGHT, lNpcVIndex);
		}
		break;
	case MSGLCMD_EXCHANGE_MAGE:
		if( bOK ) {
			_pNetwork->SendClassChange(MAGE, lNpcVIndex);
		}
		break;
	case MSGLCMD_EXCHANGE_NIGHTSHADOW:
		if( bOK ) {
			_pNetwork->SendClassChange(NIGHTSHADOW, lNpcVIndex);
		}
		break;
	case MSGLCMD_EXCHANGE_ROGUE:
		if( bOK ) {
			_pNetwork->SendClassChange(ROGUE, lNpcVIndex);
		}
		break;
	case MSGLCMD_EXCHANGE_SORCERER:
		if( bOK ) {
			_pNetwork->SendClassChange(SORCERER, lNpcVIndex);
		}
		break;
	case MSGLCMD_EXCHANGE_TITAN:
		if( bOK ) {
			_pNetwork->SendClassChange(TITAN, lNpcVIndex);
		}
		break;
#ifdef CHAR_EX_ROGUE
	case MSGLCMD_EXCHANGE_EXROGUE:
		if (bOK) {
			_pNetwork->SendClassChange(EX_ROGUE, lNpcVIndex);
		}
		break;
#endif
#ifdef CHAR_EX_MAGE
	case MSGLCMD_EXCHANGE_ARCHMAGE:
		if (bOK) {
			_pNetwork->SendClassChange(EX_MAGE, lNpcVIndex);
		}
		break;
#endif
	case MSGCMD_HARVEST_MOON_DAY_EVENT_UPGRADE1:
		{
			//2006 �߼� �̺�Ʈ: ������ ����
			if( bOK )
			{
				_pNetwork->Send2006ChuseokRicecakeMake();
			}
			else
			{
				// ����â���� ���ư�
				MsgBoxLCommand( MSGLCMD_EVENT, QUEST_HARVEST_MOON_DAY_EVENT1 ); 
			}
		}
		break;
	case MSGCMD_HARVEST_MOON_DAY_EVENT_UPGRADE2:
		{
			//2006 �߼� �̺�Ʈ: ���������� ����
			if( bOK )
			{
				_pNetwork->Send2006ChuseokRainbowMake();
			}
			else
			{
				// ����â���� ���ư�
				MsgBoxLCommand( MSGLCMD_EVENT, QUEST_HARVEST_MOON_DAY_EVENT1 ); 
			}
		}
		break;
	case MSGCND_MOON_DAY_EVENT_GIVE_ITEM:
		{
			//2006 �߼� �̺�Ʈ: ���������� ����ǰ�� ��ȯ��
			if( bOK )
			{
				_pNetwork->Send2006ChuseokExchange();
			}
			else
			{
				// ����â���� ���ư�
				MsgBoxLCommand( MSGLCMD_EVENT, QUEST_HARVEST_MOON_DAY_EVENT2 );
			}

		}
		break;
	case MSGCMD_QUEST_FAIL:
		{
			CQuestDynamicData	*pQuestDD = CQuestSystem::Instance().GetDynamicDataByQuestIndex( m_iCurQuestIndex );
			if(pQuestDD && _pNetwork->m_bSingleMode)
			{
				INDEX startType = pQuestDD->GetStartType();
				INDEX startData = pQuestDD->GetStartData();
				INDEX prizeNPCIndex = pQuestDD->GetPrizeNPCIndex();
				if( pQuestDD->GetQuestType1() == QTYPE_KIND_SAVE || pQuestDD->GetQuestType1() == QTYPE_KIND_TUTORIAL || pQuestDD->GetQuestType1() == QTYPE_KIND_DEFEAT )			// �̱۴��� ����Ʈ�� ���(���� ����Ʈ�� ���)
				{
					INDEX questIndex = m_iCurQuestIndex;
					BOOL isComplete = pQuestDD->IsQuestComplete();
					if( CQuestSystem::Instance().Remove( questIndex ) )
					{
						BOOL bDeleted = GAMEDATAMGR()->GetQuest()->DelQuestList(questIndex, isComplete);
						if(!bDeleted)//�����°� ������
						{
							bDeleted = GAMEDATAMGR()->GetQuest()->DelQuestList(questIndex, !isComplete);
							ASSERTALWAYS("Somthing is wrong, client fail delete quest from list");
							if(!bDeleted)
							{
								ASSERTALWAYS("Somthing is wrong, unknown quest index");
							}
						}
					}
					pUIManager->GetQuestBookList()->RefreshQuestListNew();
					
					if(pUIManager->GetQuestBookComplete()->GetCurrIdx() == questIndex)
						pUIManager->GetQuestBookComplete()->close();
					CQuestSystem::Instance().SetQuestAllow(questIndex, CQuestSystem::QAT_ALLOW);
					
					if(startType == QSTART_NPC)
						ACTORMGR()->RefreshNPCQuestMark(startData);
					ACTORMGR()->RefreshNPCQuestMark(prizeNPCIndex);

					// FIXME : �ϵ� �ڵ��� �κ�.
					// Hardcoding
					_pNetwork->GoZone(0, 0);
				}			
			}			
		}
		break;
	case MSGCMD_QUEST_NOTIFY:
		break;
	case MSGCMD_QUEST_NEWQUEST:
		{
			CQuestDynamicData	*pQuestDD = CQuestSystem::Instance().GetDynamicDataByQuestIndex( m_iCurQuestIndex );
			if(pQuestDD)
			{
				if( pQuestDD->GetQuestType1() == QTYPE_KIND_SAVE || pQuestDD->GetQuestType1() == QTYPE_KIND_TUTORIAL || pQuestDD->GetQuestType1() == QTYPE_KIND_DEFEAT )			// �̱۴��� ����Ʈ�� ���(���� ����Ʈ�� ���)
				{
					// �ϴ� �������� �̵� ��Ű������...
					// ������ 0���� �Ǵ���.				
					const int iWorldNum = pQuestDD->GetConditionData(0, 0);						// ���� ��ȣ.
					const int iExtraNum = pQuestDD->GetConditionData(0, 1);						// Extra ��ȣ.
					//---- woos 060515 ------------------------------------->>
					FLOAT3D tv_pos = (m_fNpcX,0,m_fNpcZ);
					_pNetwork->GoZone(iWorldNum, iExtraNum,m_iNpcIndex);
					//------------------------------------------------------<<
					
				}				
			}
			m_iCurQuestIndex = -1;
		}
		break;

	case MSGCMD_WEAPONCHANGE_EVENT:		// ���� ��ü �̺�Ʈ.
		if(bOK)
		{
			_pNetwork->SendChangeWeaponEvent();
		}
		break;

	case MSGCMD_ASK_ONE_FIVE:
		if(bOK){
		pUIManager->CloseMessageBox(MSGCMD_ASK_ONE_FIVE);
		_pNetwork->SendEvent24(1,MSG_EVENT_2PAN4PAN_MONEY_REQ);
		}
		break;
	case MSGCMD_ASK_ONE_FOUR:
		if(bOK){
		pUIManager->CloseMessageBox(MSGCMD_ASK_ONE_FOUR);
		_pNetwork->SendEvent24(2,MSG_EVENT_2PAN4PAN_MONEY_REQ);
		}
		break;
	case MSGCMD_ASK_TWO_OPEN:
		if(bOK){
		pUIManager->CloseMessageBox(MSGCMD_ASK_TWO_OPEN);
		_pNetwork->SendEvent24(0,MSG_EVENT_2PAN4PAN_GOODS_REQ);
		}
		break;
	case MSGCMD_ASK_NEWYEAR1:
		if(bOK)
		{			
			_pNetwork->SendEventNewyear(EVENT_NEWYEAR1_REWARD);
		}
		break;
	case MSGCMD_ASK_NEWYEAR2:
		if(bOK)
		{
			_pNetwork->SendEventNewyear(EVENT_NEWYEAR2_REWARD);
		}
		break;
	case MSGCMD_INPUT_FRIEND :
		if(bOK)
		{
			_pNetwork->SendFindFriend(MSG_EVENT_SEARCHFRIEND_ADD_CHECK,&strInput);

		}
		break;
	case MSGCMD_EVENT_COUPON_SENDNUM :
		if(bOK){
			_pNetwork->SendCouponItemReq(strInput);			
		}
		break;
	case MSGLCMD_EVENT_OXQUIZ:
		if(bOK)
		{
			_pNetwork->GoZone( 14, 0 ,254);
		}
		break;
	
	case MSGCMD_WORLDCUP_EVENT1_NUM:
		if(bOK)
		{				
			iSelCountry = iGroup[iSelGroup] + pUIManager->GetMessageBox(MSGCMD_WORLDCUP_EVENT1_NUM)->GetComboBox().GetCurSel();
			_pNetwork->SendWorldCupEvent( MSGCMD_WORLDCUP_EVENT1_EXCHANGE, iSelCountry );
		}
		break;
	case MSGCMD_COLLECTBOX_BUY_REQ:
		if(bOK)
		{
			_pNetwork->SendBuyCollectBox();
		}
		break;
	case MSGCMD_OK_EXCHANGE_CHOCOBOX:
	case MSGCMD_OK_EXCHANGE_LUCKYBOX:
		if (bOK)
		{
			CUIIcon* pIcon = pUIManager->GetMessageBox(nCommandCode)->GetBtnEx();

			if (pIcon != NULL)
			{
				_pNetwork->SendReqGiftChocoBox(pIcon->getIndex());
			}
		}
		break;
	case MSGCMD_GUILDMASTER_1:
		if(bOK) // ���
		{
			if(CheckGuildMasterEvent())
			{
				pUIManager->DoesMessageBoxExist(MSGCMD_GUILDMASTER_1_1);
				MsgBoxInfo.SetMsgBoxInfo( _S( 100, "�̺�Ʈ" ), UMBS_OKCANCEL, UI_QUEST, MSGCMD_GUILDMASTER_1_1);
				strMessage.PrintF( _S(3469, "�����Ͻ� ���� ī���̼��� ������� �� ������ŭ ��� ����Ʈ�� �ö� ���ϴ�. �����Ͻðڽ��ϱ�?" ));
				MsgBoxInfo.AddString( strMessage );
				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
			
		}
		else	// ����	
		{
			_pNetwork->SendRequestParentsday( MSG_EVENT_PARENTSDAY_2007_ACCUMULATEPOINT_RANKING_LIST);
		}
		break;	
	case MSGCMD_GUILDMASTER_1_1:
		if(bOK)	// ��� �޽���
		{			
			_pNetwork->SendParentsdayAddPoint(_pNetwork->MyCharacterInfo.index);
		}		
		break;

	case MSGCMD_GUILDMASTER_2_1:
		if(bOK)
		{
			// ��ȯ�� �ޱ�
			_pNetwork->SendRequestParentsday( MSG_EVENT_PARENTSDAY_2007_EXCHANGE_TICKET);
		}
		break;

		///////////////////////////////////////////////////////////////////////////////////
		// [070705 :Su-won] EVENT_SUMMER_2007
	case MSGCMD_SUMMER2007_PAPERFOLDING:
		if(bOK)
		{
			CUIMessageBox* pMsgBox =pUIManager->GetMessageBox(MSGCMD_SUMMER2007_PAPERFOLDING);
			
			int nItemIndex0 = pMsgBox->GetBtnEx(0)->getIndex();
			int nItemIndex1 = pMsgBox->GetBtnEx(1)->getIndex();
			int nItemIndex2 = pMsgBox->GetBtnEx(2)->getIndex();

			_pNetwork->SendPaperFoldingReq( nItemIndex0, nItemIndex1, nItemIndex2);
		}
		else
			MsgBoxLCommand( MSGLCMD_EVENT, EVENT_SUMMER_2007 ); 

		break;
	case MSGCMD_SUMMER2007_PAPERBLENDING:
		if(bOK)
		{
			int nItemIndex =pUIManager->GetMessageBox(MSGCMD_SUMMER2007_PAPERBLENDING)->GetBtnEx(0)->getIndex();
			
			_pNetwork->SendPaperBlendingReq( nItemIndex );
		}
		else
			MsgBoxLCommand( MSGLCMD_EVENT, EVENT_SUMMER_2007 ); 
		break;
		// [070705 :Su-won] EVENT_SUMMER_2007
		///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////
	// [070807: Su-won] EVENT_ADULT_OPEN
		//���μ��� ���� �̺�Ʈ: ���ݼ� �̺�Ʈ
	case MSGCMD_ADULTEVENT_ALCHEMIST:
		{
			if(bOK)
			{			
				CUIIcon* pIcon = pUIManager->GetMessageBox(MSGCMD_ADULTEVENT_ALCHEMIST)->GetBtnEx();

				if (pIcon != NULL)
				{
					CItems* pItems = pIcon->getItems();

					if (pItems != NULL)
					{
						_pNetwork->SendAdultOpenEventReq(2, pItems->Item_Tab, pItems->InvenIndex);
					}
				}
			}
		}
		break;
		//'��ħ���� ���!' �̺�Ʈ
	case MSGCMD_EVENT_SHOOT:
		{
			if(bOK)
			{
				CNetworkMessage nmMessage(MSG_EVENT);
				nmMessage << (UBYTE)MSG_EVENT_GIFT_2007;

				_pNetwork->SendToServerNew(nmMessage);
			}
		}
		break;
	// [070807: Su-won] EVENT_ADULT_OPEN
	///////////////////////////////////////////////////////
	case MSGCMD_BJMONO_2007_CHANGE_REQ:
		{
			if (bOK)
			{
				if (!(strInput.IsInteger()))
				{
					_pNetwork->ClientSystemMessage(_s("���ڸ� �Է��� �ֽñ� �ٶ��ϴ�."));
					return;
				}

				const char* TempNum = strInput;
				int Num = atoi(TempNum);

				if (Num < 1 || Num > 6)
				{
					_pNetwork->ClientSystemMessage(_s("1~6���� ����Ǹ� ��ȯ ���� �մϴ�."));
					return;
				}

				_pNetwork->SendBJMono2007Req(MSG_EVENT_BJMONO_2007_CHANGE_TICKET_REQ, Num);

				if ( pUIManager->DoesMessageBoxExist(MSGCMD_BJMONO_2007_CHANGE_REQ) )
					pUIManager->CloseMessageBox(MSGCMD_BJMONO_2007_CHANGE_REQ);
				
			}
		}
		break;
	case MSGCMD_TG2007_1000DAYS_CAP_UPGRADE:
		{
			if (bOK)
			{
				CUIIcon* pIcon = pUIManager->GetMessageBox(MSGCMD_TG2007_1000DAYS_CAP_UPGRADE)->GetBtnEx();

				if (pIcon != NULL)
				{
					CItems* pItems = pIcon->getItems();

					if (pItems != NULL)
					{
						_pNetwork->SendLC1000DayHatUpgradeReq((SWORD)pItems->InvenIndex, (LONG)pItems->Item_Index);
					}
				}
			}
		}
		break;
	case MSGCMD_EVENT_XMAS_2007_DECO:
		{
			if (bOK)
			{   // ũ���� ���� ���
				_pNetwork->SendXMAS2007DecoReq(MSG_EVENT_XMASTREE_ADD_POINT);
			}
		}
		break;
	case MSGCMD_EVENT_SAKURA_2008:
		{
			if(bOK)
			{
				if( pUIManager->GetInventory()->GetItemCount(2345) <=0 )
				{
					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

					MsgBoxInfo.AddString(_S(4114, "��� ������ ���� �ʽ��ϴ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);

					return;
				}

				CNetworkMessage nmMessage(MSG_EVENT);

				nmMessage << (UBYTE)MSG_EVENT_SAKURA_2008;
				nmMessage << (UBYTE)MSG_EVENT_SAKURAEVENT_2008;

				_pNetwork->SendToServerNew(nmMessage);
			}
		}
		break;
	// [080422: Su-won] EVENT_CHAOSBALL
	case MSGCMD_EVENT_CHAOSBALL:
		{
			if(bOK)
			{
				CUIIcon* pIcon = pUIManager->GetMessageBox(MSGCMD_EVENT_CHAOSBALL)->GetBtnEx();

				if (pIcon != NULL)
				{
					CItems* pItems = pIcon->getItems();

					if (pItems != NULL)
					{
						int tv_tab, tv_idx;

						tv_tab = pItems->Item_Tab;
						tv_idx = pItems->InvenIndex;
						int iUniIndex = pItems->Item_UniIndex;

						int nCheckIdx = _pNetwork->MySlotItem[tv_tab][tv_idx].Item_UniIndex;

						if (iUniIndex != pItems->Item_UniIndex)
						{
							pUIManager->GetMessageBox(MSGCMD_EVENT_CHAOSBALL)->GetBtnEx(0)->clearIconData();
							break;
						}

						CNetworkMessage nmMessage;
						RequestClient::doChaosBall* packet = reinterpret_cast<RequestClient::doChaosBall*>(nmMessage.nm_pubMessage);
						packet->type = MSG_EXTEND;
						packet->subType = htonl(MSG_EX_CHAOSBALL);
						packet->thirdType = 0;
						packet->tab = tv_tab;
						packet->invenIndex = tv_idx;
						nmMessage.setSize( sizeof(*packet) );

						_pNetwork->SendToServerNew(nmMessage);
					}
				}
			}
		}
		break;

		// [100208: selo] ����Ʈ ������ �ٽ� �ޱ�
	case MSGCMD_QUEST_RESTORE_ITEM:
		{
			if(bOK)
			{
				if( m_restoreQuestIndex != -1 )
				{
					_pNetwork->SendRestoreQuestItem( m_restoreQuestIndex );
				}
				else
				{
					_pNetwork->SendTakeAgainQuestItem();
				}
			}
		}
		break;
		// [100208: selo] ����Ʈ ������ �ٽ� �ޱ� ���
	case MSGCMD_QUEST_RESTORE_ITEM_RESULT:
		break;

		// ($E_WC2010) [100518: selo] ��� ���� ������ �ϱ�
	case MSGCMD_EVENT_WORLDCUP_EVENT2_REREQ:
		{
			if(bOK)
			{
				CreateMessageBox_WorldCup2010_Event2(EVENT_WORLDCUP_2010_EVENT2_SEL1);
			}
		}
		break;

		// ($E_WC2010) [100518: selo] ��� ���� ���� �ϱ�
	case MSGCMD_EVENT_WORLDCUP_EVENT2_REQ:
		{
			if(bOK)
			{
				CUIIcon* pIcon = pUIManager->GetMessageBox(MSGCMD_EVENT_WORLDCUP_EVENT2_REQ)->GetBtnEx();

				if (pIcon != NULL)
				{
					INDEX nItemIndex = pIcon->getIndex();
					_pNetwork->SendWorldCup2010_Event(MSG_EVENT_WORLDCUP2010_TOTO_REQ, nItemIndex);
				}
			}
		}
		break;
	case MSGCMD_REGISTER_MERCHANT:	// [2010/08/25 : Sora] ADD_SUBJOB
		{
			if(bOK)
			{
				_pNetwork->SendSubJobRegister( SUBJOB_MERCHANT );
			}
		}
		break;
	case MSGCMD_PROMOTION2_REQ :
		if(bOK){
			_pNetwork->SendPromotionEventReq(strInput);			
		}
		break;
	case MSGCMD_SOULOFSCALP_CONFIRM:
		{
			if (bOK)
			{
				_pNetwork->SendEventMsg(MSG_EVENT_AKAN_TEMPLE);
			}
		}
		break;
	case MSGCMD_COMEBACK_CONFIRM:
		{
			if (bOK)
			{
				_pNetwork->SendComebackMessage();
			}
		}
		break;
	case MSGCMD_BIRTHDAY_CONFIRM:
		{
			if (bOK)
			{
				_pNetwork->SendBirthdayMessage( EVENT_BIRTHDAY_GIFT );
			}
		}
		break;
	case MSGCMD_KB_EXCHAGE_HEART:	// [2011/11/14 : Sora] �±� ���� ź���� �̺�Ʈ
		{
			if (bOK)
			{
				_pNetwork->SendKBRewardReq( 0 );
			}
		}
		break;
	case MSGCMD_KB_EXCHAGE_FLAG:	// [2011/11/14 : Sora] �±� ���� ź���� �̺�Ʈ
		{
			if (bOK)
			{
				_pNetwork->SendKBRewardReq( 1 );
			}
		}
		break;
	case MSGCMD_SYNDICATE_PUTON_JEWEL_REQ:
		{
			if (pEntity == NULL ||
				pEntity->IsEnemy() == FALSE)
			{
				UIMGR()->GetChattingUI()->AddSysMessage(_S(6312, "NPC�� ��ȭ���� �ƴմϴ�."), SYSMSG_ERROR);			
				return;
			}

			if (bOK)
			{	// ���� ���� ��� �޽���.
				GameDataManager* pGameData = GameDataManager::getSingleton();

				if (pGameData == NULL)
					break;

				CSyndicate* pSyndicateData = pGameData->GetSyndicate();

				if (pSyndicateData == NULL)
					break;

				CUIIcon* pIcon = pUIManager->GetMessageBox(MSGCMD_SYNDICATE_PUTON_JEWEL_REQ)->GetBtnEx();

				if (pIcon != NULL)
				{
					CItems* pItems = pIcon->getItems();

					if (pItems != NULL)
					{
						INDEX nItemUniIndex = pItems->Item_UniIndex;

						pSyndicateData->SendGiveJewel(lNpcVIndex, nItemUniIndex);
					}
				}
			}
		}
		break;
	case MSGCMD_SYNDICATE_SECESSION_REQ:
		{
			if (pEntity == NULL ||
				pEntity->IsEnemy() == FALSE)
			{
				UIMGR()->GetChattingUI()->AddSysMessage(_S(6312, "NPC�� ��ȭ���� �ƴմϴ�."), SYSMSG_ERROR);			
				return;
			}

			if (bOK)
			{
				GameDataManager* pGameData = GameDataManager::getSingleton();

				if (pGameData == NULL)
					break;

				CSyndicate* pSyndicateData = pGameData->GetSyndicate();

				if (pSyndicateData == NULL)
					break;

				int nTab = -1;
				int nInvenIndex = -1;

				CUIIcon* pIcon = pUIManager->GetMessageBox(MSGCMD_SYNDICATE_SECESSION_REQ)->GetBtnEx();

				if (pIcon != NULL)
				{
					CItems* pItems = pIcon->getItems();

					if (pItems != NULL)
					{
						nTab = pItems->Item_Tab;
						nInvenIndex = pItems->InvenIndex;
					}
				}

				pSyndicateData->SendSecession(lNpcVIndex, nTab, nInvenIndex);
			}
		}
		break;
	}
}

// ----------------------------------------------------------------------------
// Name : QuestError()
// Desc :
// ----------------------------------------------------------------------------
void CUIQuest::QuestError( UBYTE ubError )
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString	strMessage;
	
	switch(ubError)
	{
	case MSG_QUEST_ERR_START_ONCE:		// ����Ʈ ���۽� ���� : �̹� ������ 1ȸ�� ����Ʈ
		strMessage = _S( 590, "�ش� ����Ʈ�� �̹� ������ ����Ʈ�Դϴ�." );		
		break;
	case MSG_QUEST_ERR_START_ALREADY:	// ����Ʈ ���۽� ���� : �̹� ��������
		strMessage = _S( 591, "�̹� �������� ����Ʈ�Դϴ�." );		
		break;
	case MSG_QUEST_ERR_START_LEVEL:		// ����Ʈ ���۽� ���� : ���� ���� �ȸ���
		strMessage = _S( 592, "���� ������ ���� �ʾƼ� ����Ʈ�� ������ �� �����ϴ�." );		
		break;
	case MSG_QUEST_ERR_START_JOB:		// ����Ʈ ���۽� ���� : ���� ���� �ȸ���
		strMessage = _S( 593, "���� ������ ���� �ʾƼ� ����Ʈ�� ������ �� �����ϴ�." );		
		break;
	case MSG_QUEST_ERR_START_ITEM:		// ����Ʈ ���۽� ���� : ������ ���� �ȸ���
		strMessage = _S( 594, "������ ������ ���� �ʾƼ� ����Ʈ�� ������ �� �����ϴ�." );		
		break;
	case MSG_QUEST_ERR_START_MAX:		// ����Ʈ ���۽� ���� : �ִ� ���� ���� �� �ʰ�
		strMessage = _S( 595, "���� ������ ����Ʈ Ƚ���� �ʰ��߽��ϴ�." );		
		break;
	case MSG_QUEST_ERR_START_FULL:		// ����Ʈ ���۽� ���� : �̱۴����� ��� �̱۴��� ����
		strMessage = _S( 596, "�̱۴����� ȥ���Ͽ� ����Ʈ�� ������ �� �����ϴ�" );		
		break;
	case MSG_QUEST_ERR_DELIVERY_FULL:	// ���� ����Ʈ �� : �κ��丮�� ������ ������ ����Ʈ ����
		strMessage = _S( 597, "�κ��丮�� �� ���� ����Ʈ�� ������ �� �����ϴ�." );		
		break;
	case MSG_QUEST_ERR_PRIZE_FULL:		// ���� ������ �κ� �� ���� ���� ����
		strMessage = _S( 598, "�κ��丮�� �� ���� ������ ���� �� �����ϴ�." );		
		break;
	case MSG_QUEST_ERR_PRZIE_ITEM:		// ���� ������ ������ ������ ����
		strMessage = _S( 599, "������ ������ ���� �ʾ� ������ ���� �� �����ϴ�." );		
		break;
	case MSG_QUEST_ERR_PET_NOT_HAVE_ONEMORE:
		{
			strMessage = _S(2221,"���� �� �̻� ������ �� �����ϴ�.");
			pUIManager->GetQuestBookComplete()->close();
		}
		break;
	case MSG_QUEST_ERR_NOT_EXIST_ABANDON_QUEST:		// [100208: selo] ���� ����Ʈ ���� ����
		strMessage = _S(4816,"���� ������ �´� ������ ����Ʈ�� �������� �ʽ��ϴ�. �ٽ� Ȯ�� �� �õ��Ͻñ� �ٶ��ϴ�.");
		break;
	case MSG_QUEST_ERR_DONT_HAVE_NAS:				// [100208: selo] ���� ����Ʈ ���� ����
		strMessage = _S(4817,"������ �����ؼ� ���� ����Ʈ�� ������ �� �����ϴ�.");
		break;
	case MSG_QUEST_ERR_DONT_HAVE_SPACE:				// ALEX QUEST SPACE
		strMessage = _S(10071, "�κ��丮�� �� ���� ������ ���� �� �����ϴ�." );
		break;
	case MSG_QUEST_ERR_CHECK_DONE_ING:
		{
			pUIManager->SetCSFlagOff(CSF_TELEPORT);
			strMessage = _S(6311, "����Ʈ �Ϸᰡ �ƴϰų� �������� �ƴմϴ�.");
		}
		break;
	}

	// Close message box of remission
	pUIManager->CloseMessageBox( MSGCMD_QUEST_NOTIFY );
	pUIManager->CloseMessageBox( MSGCMD_QUEST_NEWQUEST );
		
	// Create message box of remission
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 99, "����Ʈ" ), UMBS_OK,			
								UI_QUEST, MSGCMD_QUEST_NOTIFY );
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );
}
