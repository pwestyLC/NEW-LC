#include "stdh.h"
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UISiegeWarfare.h>
#include <Engine/Interface/UISiegeWarfareDoc.h>
#include <Engine/Interface/UIAutoHelp.h>
#include <Engine/Interface/UISiegeWarfareNew.h>
#include <Engine/Interface/UIGuild.h>
#include <Engine/Contents/Base/UIQuestComplete.h>

extern INDEX g_iCountry;

// Position and Size
#define DEF_SIGEWARFARE_START_Y		238

#define SIGEWARFARE_WIDTH			311		// ������ ũ��
#define SIGEWARFARE_HEIGHT			275

// Battle�� ���� ǥ�� 
#define BATTLE_WIDTH				118		
#define BATTLE_HEIGHT				155
#define UNIT_TEXT_OFFSETX			8		// ��� �̸�
#define UNIT_TEXT_OFFSETY			6
#define UNIT_POINT_OFFSETX			114		// ��� ����Ʈ
#define UNIT_POINT_OFFSETY			22
#define UNIT_HEIGHT					44		// ��ü �ϳ� �ϳ�		
#define UNIT_TIME_HEIGHT			21

#define INFO_OFFSETY				160		// Selection Battle�� �ΰ� ����â 
#define INFO_WIDTH					118
#define INFO_HEIGHT					93

#define LEFT_TIME_X					29		// �����ð�
#define LEFT_TIME_Y					2

#define TIME_NUMBER_WIDTH			12		// �ð� ǥ���ϴ� ��ȣ
#define TIME_NUMBER_HEIGHT			17

#define COLON_WIDTH					4		// :
#define COLON_INDEX					10	

#define NUMBER_WIDTH				16		// Point ǥ���ϴ� ��ȣ
#define NUMBER_HEIGHT				19

// �ð� ����
#define TITLE_SX					25		// Ÿ��Ʋ ��
#define TITLE_SY					5
#define TITLE_HEIGHT				25
											// ���
#define BACK_MIDDLE_DESC			150		// �߰� ���� â
#define BACK_MIDDLE_SELECT			57		// �Ʒ� ���� â
#define BACK_BOTTOM_HEIGHT			7		// �Ʒ��� â�� ����

#define CHECKBOX_SIZE				11		// üũ �ڽ�
#define OPTION_TEXT_X1				23		
#define OPTION_TEXT_X2				143
#define OPTION_TEXT_Y				52

#define START_BOTTOM_BUTTON_Y		242		// �Ʒ� Ȯ�� ��ư

// Color
// �ð� ���� �� ��� 
#define SW_COLOR_TITLE				0xE18600FF	// Ÿ��Ʋ
#define SW_COLOR_DESC				0xA3A1A3FF	// ����
#define SW_COLOR_TEXT				0xF2F2F2FF	// �� �߿��� ��

#define SW_COLOR_GUILD_NAME			0xE18600FF	// ��� �̸� 
#define SW_COLOR_GUILD_POINT		0xd7d0a8ff	// �������Ʈ
#define SW_COLOR_DEFENSE_POINT		0xa9a6d9ff  // ����������Ʈ

// Selection
#define SEL_SW_REQ					0		// ������û  
#define	SEL_MERCEAR_REQ				1		// �뺴��û
#define SEL_SET_SW_TIME				2		// �����ð� ����
#define SEL_SW_INFO					3		// ���� ���� Ȯ��
#define SEL_SW_CANCEL				4		// ����ϱ�
#define SEL_COSTUME_REQ				5		// ���� �ڽ�Ƭ ��û
#define SEL_GUILD_COSTUME_REQ		6		// ���� ��� �ڽ�Ƭ ��û
#define SEL_GUILD_TITLE_REQ			7		// ���� ��� ȣĪ ��û

#define SEL_DEF_MERCEAR_GUILD_REQ	0		// �뺴 ��� ��û
#define	SEL_DEF_MERCEAR_REQ			1		// ������ �뺴 ��û
#define SEL_ATT_MERCEAR_REQ			2		// ������ �뺴 ��û
#define SEL_MERCEAR_CANCEL			3		// ����ϱ�

// Notice
#define	NOTICE_DELAY				8000			
#define	NOTICE_FADEOUT				7000
#define	NOTICE_FADETIME				( NOTICE_DELAY - NOTICE_FADEOUT )

#define SIEGEWARFAREINFO_PER_PAGE	5

//------------------------------------------------------------------------------
// CUISiegeWarfare::CUISiegeWarfare
// Explain:  
// Date : 2005-06-20,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
CUISiegeWarfare::CUISiegeWarfare()
{
	Clear();	
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::~CUISiegeWarfare
// Explain:  
// Date : 2005-07-01,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
CUISiegeWarfare::~CUISiegeWarfare()
{
	if( _pUISWDoc!= NULL ) 
	{
		delete _pUISWDoc;
		_pUISWDoc = NULL;
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::ResetPosition
// Explain:  ��� ����
// Date : 2005-06-20,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	int nTempState = _pUISWDoc->GetUIState();

	// OpenSetSWTime - ��� ����
	// OpenBattle - ���� �ÿ��� ������ ���� 

	if (nTempState == SWS_BATTLE || nTempState == SWS_SELECT_BATTLE)
	{
		CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();
		SetPos(	pDrawPort->dp_MaxI - GetWidth() - 10, DEF_SIGEWARFARE_START_Y );
	}else
	{
		SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
	}
	
}


//------------------------------------------------------------------------------
// CUISiegeWarfare::ResetPos
// Explain: ���������� �������� ��ġ ���� 
// OpenSetSWTime - ��� ����
// OpenBattle - ���� �ÿ��� ������ ���� 
// Date : 2005-07-01,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::ResetPos( BOOL bCenter )
{
	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	if( bCenter ) // ��� ���� 
	{
		ResetPosition( pDrawPort->dp_MinI, pDrawPort->dp_MinJ, pDrawPort->dp_MaxI, pDrawPort->dp_MaxJ );	
	}
	else // ������ ���� 
	{
		SetPos(	pDrawPort->dp_MaxI - GetWidth() - 10, DEF_SIGEWARFARE_START_Y );
	}
}
	
//------------------------------------------------------------------------------
// CUISiegeWarfare::AdjustPosition
// Explain:  
// Date : 2005-06-20,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::Clear
// Explain:  
// Date : 2005-06-20,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::Clear()
{
	//_pUISWDoc->SetUIState( SWS_NONE );

	m_tmNoticeTime	= 0;	
	m_bShowNotice	= FALSE;
	
	m_strNoticeMessage.Clear();
	m_strNoticeMessage2.Clear();
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::Create
// Explain:  
// Date : 2005-06-20,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight )
{
	_pUISWDoc = new CUISiegeWarfareDoc();
	_pUISWDoc->SetUIState( SWS_NONE );

	m_strTitle = _S(2417,"����");	// ����

	CUIWindow::Create(pParentWnd, nX, nY, SIGEWARFARE_WIDTH, SIGEWARFARE_HEIGHT);

	// Set Rect
	m_rcTitle.SetRect( 0, 0, 512, 22 );
		
	m_ptdBaseTexture = CreateTexture( CTString( "Data\\Interface\\MessageBox.tex" ) );
	FLOAT	fTexWidth = m_ptdBaseTexture->GetPixWidth();
	FLOAT	fTexHeight = m_ptdBaseTexture->GetPixHeight();

	// Set Background RectUV
	m_rt3BackT.SetUV3( 0, 0, 40, 26, 40, 0, 176, 26, 176, 0, 216, 26, fTexWidth, fTexHeight );
	m_rt3BackSM.SetUV3( 0, 27, 40, 30, 40, 27, 176, 30, 176, 27, 216, 30, fTexWidth, fTexHeight );
	m_rt3BackNM.SetUV3( 0, 31, 40, 34, 40, 31, 176, 34, 176, 31, 216, 34, fTexWidth, fTexHeight );
	m_rt3BackM.SetUV3( 0, 35, 40, 37, 40, 35, 176, 37, 176, 35, 216, 37, fTexWidth, fTexHeight );
	m_rt3BackL.SetUV3( 0, 38, 40, 45, 40, 38, 176, 45, 176, 38, 216, 45, fTexWidth, fTexHeight );

	// Button Create
	m_btnOK.Create( this, _S( 191, "Ȯ��" ), 90, START_BOTTOM_BUTTON_Y, 63, 21 );
	m_btnOK.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnOK.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnOK.CopyUV( UBS_IDLE, UBS_ON );
	m_btnOK.CopyUV( UBS_IDLE, UBS_DISABLE );

	m_btnCancel.Create( this, _S( 139, "���" ), 162, START_BOTTOM_BUTTON_Y, 63, 21 );
	m_btnCancel.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnCancel.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnCancel.CopyUV( UBS_IDLE, UBS_ON );
	m_btnCancel.CopyUV( UBS_IDLE, UBS_DISABLE );

	m_btnClose.Create( this, CTString( "" ), 279, 4, 14, 14 );
	m_btnClose.SetUV( UBS_IDLE, 219, 0, 233, 14, fTexWidth, fTexHeight );
	m_btnClose.SetUV( UBS_CLICK, 234, 0, 248, 14, fTexWidth, fTexHeight );
	m_btnClose.CopyUV( UBS_IDLE, UBS_ON );
	m_btnClose.CopyUV( UBS_IDLE, UBS_DISABLE );

	// CheckButton Create
	int nStrWidth;
	nStrWidth = ( _S( 1980, "�����" ).Length() + 3 ) * ( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() );	
	
	m_cbtnSaturday.Create( this, OPTION_TEXT_X1 + nStrWidth, OPTION_TEXT_Y, 11, 11,
							_S( 1980, "�����" ), TRUE, nStrWidth, nStrWidth );		
	
	m_cbtnSaturday.SetUV( UCBS_NONE, 12, 161, 23, 172, fTexWidth, fTexHeight );
	m_cbtnSaturday.SetUV( UCBS_CHECK, 0, 161, 11, 172, fTexWidth, fTexHeight );
	m_cbtnSaturday.CopyUV( UCBS_NONE, UCBS_CHECK_DISABLE );
	m_cbtnSaturday.CopyUV( UCBS_NONE, UCBS_NONE_DISABLE );
	m_cbtnSaturday.SetTextColor( UCBS_CHECK, 0xF2F2F2FF );
	m_cbtnSaturday.SetTextColor( UCBS_NONE, 0xF2F2F2FF );
	m_cbtnSaturday.SetCheck( FALSE );

	nStrWidth = ( _S( 1981, "�Ͽ���" ).Length() + 3 ) * ( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() );	

	m_cbtnSunday.Create( this, OPTION_TEXT_X2 + nStrWidth, OPTION_TEXT_Y, 11, 11,
							_S( 1981, "�Ͽ���" ), TRUE, nStrWidth, nStrWidth );		
	
	m_cbtnSunday.SetUV( UCBS_NONE, 12, 161, 23, 172, fTexWidth, fTexHeight );
	m_cbtnSunday.SetUV( UCBS_CHECK, 0, 161, 11, 172, fTexWidth, fTexHeight );
	m_cbtnSunday.CopyUV( UCBS_NONE, UCBS_CHECK_DISABLE );
	m_cbtnSunday.CopyUV( UCBS_NONE, UCBS_NONE_DISABLE );
	m_cbtnSunday.SetTextColor( UCBS_CHECK, 0xF2F2F2FF );
	m_cbtnSunday.SetTextColor( UCBS_NONE, 0xF2F2F2FF );
	m_cbtnSunday.SetCheck( FALSE );

	// List box of guild description
	m_lbDesc.Create( this, 8, 142, 290, BACK_MIDDLE_SELECT + 40, _pUIFontTexMgr->GetLineHeight(), 13, 3, 1, FALSE );

	int black = 74; // black �� 0���� ������ ȸ�� ������ Edit �ڽ� ����
	CTString strSiegeTime;
	int btnSize = 60;

	if (g_iCountry == USA)
	{
		strSiegeTime = CTString("Set Time");
		btnSize = 94;
	}
	else
	{
		strSiegeTime = CTString("PM");
	}

	m_sbtnSWTime.Create( this, 24, 96, btnSize, 14, strSiegeTime, 37 );
	m_sbtnSWTime.SetDataBackUV3( 131+black, 46, 135+black, 59, 136+black, 46, 140+black, 59, 
							141 + black, 46, 145 + black, 59, fTexWidth, fTexHeight );
	
	m_sbtnSWTime.SetUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_sbtnSWTime.SetUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_sbtnSWTime.CopyUpUV( UBS_IDLE, UBS_ON );
	m_sbtnSWTime.CopyUpUV( UBS_IDLE, UBS_DISABLE );
	
	m_sbtnSWTime.SetDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_sbtnSWTime.SetDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_sbtnSWTime.CopyDownUV( UBS_IDLE, UBS_ON );
	m_sbtnSWTime.CopyDownUV( UBS_IDLE, UBS_DISABLE );
	m_sbtnSWTime.CreateButtons( 9, 7 );
	m_sbtnSWTime.SetWheelRect( -19, -75, 19, 165 );

	// [2010/11/01 : Sora] ���� ����
	m_sbtnSWZone.Create( this, 134, 96, 105, 14, CTString(""), 95 );
	m_sbtnSWZone.SetDataBackUV3( 131+black, 46, 135+black, 59, 136+black, 46, 140+black, 59, 
							141 + black, 46, 145 + black, 59, fTexWidth, fTexHeight );
	
	m_sbtnSWZone.SetUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_sbtnSWZone.SetUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_sbtnSWZone.CopyUpUV( UBS_IDLE, UBS_ON );
	m_sbtnSWZone.CopyUpUV( UBS_IDLE, UBS_DISABLE );
	
	m_sbtnSWZone.SetDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_sbtnSWZone.SetDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_sbtnSWZone.CopyDownUV( UBS_IDLE, UBS_ON );
	m_sbtnSWZone.CopyDownUV( UBS_IDLE, UBS_DISABLE );
	m_sbtnSWZone.CreateButtons( 9, 7 );
	m_sbtnSWTime.SetWheelRect( -19, -75, 19, 165 );

	// Number
	int nOffsetX = 256;
	int nOffsetY = 157;

	int i;
	for( i = 0 ; i < 10; i++ )
	{
		m_rtNumber[i].SetUV( nOffsetX + i * NUMBER_WIDTH, nOffsetY, 
							nOffsetX + i * NUMBER_WIDTH + NUMBER_WIDTH, nOffsetY + NUMBER_HEIGHT, 
							fTexWidth, fTexHeight );
	}

	m_rtNumber[i].SetUV( nOffsetX + i * NUMBER_WIDTH+4, nOffsetY, 
							nOffsetX + i * NUMBER_WIDTH + NUMBER_WIDTH-4, nOffsetY + NUMBER_HEIGHT, 
							fTexWidth, fTexHeight );

	m_rtBattleBack.SetUV( 256, 0, 374, 155, fTexWidth, fTexHeight );

	m_rtSelectBattleBack.SetUV( 375, 0, 493, 93, fTexWidth, fTexHeight );

	// Notice
	//m_rcNotice1.SetRect( 0, 100, 0, 119 );
	//m_rcNotice2.SetRect ( 0, 120, 0, 139 );
	m_rcNotice1.SetRect( 0, 75, 0, 94 );
	m_rcNotice2.SetRect ( 0, 95, 0, 114 );

	m_rtNoticeL.SetUV( 375, 95, 407, 114, fTexWidth, fTexHeight );
	m_rtNoticeC.SetUV( 426, 117, 440, 136, fTexWidth, fTexHeight );
	m_rtNoticeR.SetUV( 409, 95, 441, 114, fTexWidth, fTexHeight );

}

//------------------------------------------------------------------------------
// CUISiegeWarfare::MsgBoxLCommand
// Explain:  
// Date : 2005-06-21,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::MsgBoxLCommand( int nCommandCode, int nResult )
{
	switch( nCommandCode )
	{
	case MSGLCMD_SIEGE_WARFARE:
		{
			switch( nResult ) 
			{
			case SEL_SW_REQ:		// ���� ��û
				OpenSWReq();
				break;
			case SEL_MERCEAR_REQ:	// �뺴 ��û 
				OpenMercearReq();
				break;
			case SEL_SET_SW_TIME:	// �����ð� ���� 
				_pNetwork->SendGuildWarTimeMenu();
				break;
			case SEL_SW_INFO:		// �������� Ȯ��
				_pNetwork->SendGuildWarTimeReq();
				break;
			case SEL_SW_CANCEL:		// ����ϱ�
				CloseSiegeWarfare();
				break;
			case SEL_COSTUME_REQ:
				OpenCostumeReq();
				break;
			// ���� ��� �ڽ�Ƭ [1/21/2011 ldy1978220]
			case SEL_GUILD_COSTUME_REQ:
				{
					_pNetwork->LordGuildCostumeReq();
				}				
				break;
			case SEL_GUILD_TITLE_REQ:
				{
					_pNetwork->LordGuildTitleReq();
				}				
				break;
			}
		}
		break;
	case MSGLCMD_MERCEAR_REQ:
		{
			switch( nResult )
			{
			case SEL_DEF_MERCEAR_GUILD_REQ:	// ������ �뺴 ��� ��û 
				{
					_pNetwork->DefenseGuildReq();
				}
				break;
			case SEL_DEF_MERCEAR_REQ:		// ������ �뺴����
				{
					//_pNetwork->AttackCharReq();
					_pNetwork->AttackGuildReq();
				}
				break;
			case SEL_ATT_MERCEAR_REQ:		// ������ �뺴 ���� 
				{
					//_pNetwork->AttackGuildReq();
					_pNetwork->AttackCharReq();
				}
				break;
			case SEL_MERCEAR_CANCEL:		// ����ϱ�
				{
					OpenSiegeWarfare();
				}
				break;
			}
		}
		break;
	case MSGLCMD_LORD_COSTUME_REQ:
		{
			if ( nResult == 0 )
			{
				// ������ ���� �ڽ�Ƭ ������ ��û
				_pNetwork->LordCostumeReq();
			}
		}
		break;
	}

}

//------------------------------------------------------------------------------
// CUISiegeWarfare::MsgBoxCommand
// Explain:  
// Date : 2005-06-21,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput )
{
	switch( nCommandCode )
	{
	case MSGCMD_SIEGE_WARFARE_INFO:
		//OpenSiegeWarfare();
		break;
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::CloseSiegeWarfare
// Explain:  
// Date : 2005-06-20,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::CloseSiegeWarfare()
{
	Clear();
	_pUISWDoc->Clear();
	CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE, FALSE );
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::RenderLeftTime
// Explain:  
// Date : 2005-06-28,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::RenderLeftTime()
{
	__int64	llCurTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds(); // ���� �ð� ���
	__int64	llCurDelay = llCurTime - _pUISWDoc->m_tmLeftTime;

	int lLeftTime = _pUISWDoc->m_lLeftTime - (llCurDelay/1000);

	if ( lLeftTime < 0 ) lLeftTime = 0;

	int iSec = lLeftTime % 60;
	lLeftTime /= 60;

	int iMin = lLeftTime % 60;
	int iTime = lLeftTime /= 60;

	int nX = m_nPosX + LEFT_TIME_X;
	int nY = m_nPosY + LEFT_TIME_Y;

	int t10;
	// �ð� ���
	
	t10 = iTime / 10;
	iTime %= 10;

	DrawNumber( nX, nY, t10, TIME_NUMBER_WIDTH, TIME_NUMBER_HEIGHT );			nX += TIME_NUMBER_WIDTH;
	DrawNumber( nX, nY, iTime, TIME_NUMBER_WIDTH, TIME_NUMBER_HEIGHT );			nX += TIME_NUMBER_WIDTH;

	DrawNumber( nX, nY, COLON_INDEX, COLON_WIDTH, TIME_NUMBER_HEIGHT );			nX += COLON_WIDTH;

	// �� ��� 
	t10 = iMin / 10;
	iMin %= 10;

	DrawNumber( nX, nY, t10, TIME_NUMBER_WIDTH, TIME_NUMBER_HEIGHT );			nX += TIME_NUMBER_WIDTH;
	DrawNumber( nX, nY, iMin, TIME_NUMBER_WIDTH, TIME_NUMBER_HEIGHT );			nX += TIME_NUMBER_WIDTH;

	DrawNumber( nX, nY, COLON_INDEX, COLON_WIDTH, TIME_NUMBER_HEIGHT );			nX += COLON_WIDTH;

	// �� ��� 
	t10 = iSec / 10;
	iSec %= 10;

	DrawNumber ( nX, nY, t10, TIME_NUMBER_WIDTH, TIME_NUMBER_HEIGHT );			nX += TIME_NUMBER_WIDTH;
	DrawNumber ( nX, nY, iSec, TIME_NUMBER_WIDTH, TIME_NUMBER_HEIGHT );	
}

void CUISiegeWarfare::RenderNotice()
{
	if ( m_bShowNotice == FALSE )
		return;

	__int64	llCurTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();
	__int64	llCurDelay = llCurTime - m_tmNoticeTime;
	if( llCurDelay < CHATMSG_NOTICE_DELAY )
	{
		COLOR	colBackground = 0xFFFFFFFF;
		COLOR	colText = 0x00fffbff;
		if( llCurDelay > NOTICE_FADEOUT )
		{
			FLOAT	fFadeRatio = (FLOAT)( NOTICE_DELAY - llCurDelay ) / (FLOAT)NOTICE_FADETIME;
			COLOR	colBlend = 0xFF * fFadeRatio;
			
			colBackground &= 0xFFFFFF00;
			colBackground |= colBlend;
			colText &= 0xFFFFFF00;
			colText |= colBlend;
		}

		CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

		pDrawPort->InitTextureData( m_ptdBaseTexture );
		
		// Add render regions
		// Background
		pDrawPort->AddTexture( m_rcNotice1.Left - 32, m_rcNotice1.Top,
												m_rcNotice1.Left, m_rcNotice1.Bottom,
												m_rtNoticeL.U0, m_rtNoticeL.V0, m_rtNoticeL.U1, m_rtNoticeL.V1,
												colBackground );
		
		pDrawPort->AddTexture( m_rcNotice1.Left, m_rcNotice1.Top,
												m_rcNotice1.Right, m_rcNotice1.Bottom,
												m_rtNoticeC.U0, m_rtNoticeC.V0, m_rtNoticeC.U1, m_rtNoticeC.V1,
												colBackground );
		
		pDrawPort->AddTexture( m_rcNotice1.Right, m_rcNotice1.Top,
												m_rcNotice1.Right + 32, m_rcNotice1.Bottom,
												m_rtNoticeR.U0, m_rtNoticeR.V0, m_rtNoticeR.U1, m_rtNoticeR.V1,
												colBackground );
		
		if( m_bBottomNotice )
		{
			
			// bottom
			pDrawPort->AddTexture( m_rcNotice2.Left - 32, m_rcNotice2.Top,
				m_rcNotice2.Left, m_rcNotice2.Bottom,
				m_rtNoticeL.U0, m_rtNoticeL.V0, m_rtNoticeL.U1, m_rtNoticeL.V1,
				colBackground );
			
			pDrawPort->AddTexture( m_rcNotice2.Left, m_rcNotice2.Top,
				m_rcNotice2.Right, m_rcNotice2.Bottom,
				m_rtNoticeC.U0, m_rtNoticeC.V0, m_rtNoticeC.U1, m_rtNoticeC.V1,
				colBackground );
			
			pDrawPort->AddTexture( m_rcNotice2.Right, m_rcNotice2.Top,
				m_rcNotice2.Right + 32, m_rcNotice2.Bottom,
				m_rtNoticeR.U0, m_rtNoticeR.V0, m_rtNoticeR.U1, m_rtNoticeR.V1,
				colBackground );
		}
		
		// Render all elements
		pDrawPort->FlushRenderingQueue();
		
		
		pDrawPort->PutTextEx( m_strNoticeMessage, m_rcNotice1.Left, m_rcNotice1.Top + 4, colText );
		if( m_bBottomNotice )
			pDrawPort->PutTextEx( m_strNoticeMessage2, m_rcNotice2.Left, m_rcNotice2.Top + 4, colText );
		
		// Flush all render text queue
		pDrawPort->EndTextEx();
	}
	else
	{
		m_bShowNotice = FALSE;
		if( _pUISWDoc->IsUIState( SWS_END ) ) 
		{
			_pUISWDoc->StopEffect( -1, TRUE );
			_pUISWDoc->StopGuildMasterEffect( -1, TRUE );
			
			CloseSiegeWarfare();
		}
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::Render
// Explain:  
// Date : 2005-06-20,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::Render()
{
	_pUISWDoc->RunDalyTime();
	
	if( _pUISWDoc->IsUIState( SWS_SET_SW_TIME ) ) // �ð� ���� ������ 
	{
		RenderSetSWTime();
	}
	else if( _pUISWDoc->IsBattle() || _pUISWDoc->IsSelectBattle() )
	{
		RenderBattle();
	}
	else if( _pUISWDoc->IsUIState( SWS_END ) ) 
	{	
		

	}
	
	RenderNotice();
}
 
//------------------------------------------------------------------------------
// CUISiegeWarfare::OpenSlelectBattle
// Explain:  
// Date : 2005-06-28,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::OpenSelectBattle()
{
	SetSize( BATTLE_WIDTH, BATTLE_HEIGHT + INFO_HEIGHT + 4 );
	ResetPos( FALSE );
	_pUISWDoc->SetUIState( SWS_SELECT_BATTLE );
	CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE, TRUE );
	
	_pUISWDoc->m_tmLeftTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds ();

}

//------------------------------------------------------------------------------
// CUISiegeWarfare::OpenBattle
// Explain:  
// Date : 2005-06-28,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::OpenBattle()
{
	SetSize( BATTLE_WIDTH, BATTLE_HEIGHT );
	ResetPos( FALSE );

	_pUISWDoc->SetUIState( SWS_BATTLE );
	CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE, TRUE );
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::OpenSiegeWarfare
// Explain:  
// Date : 2005-06-20,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::OpenSiegeWarfare()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if(pUIManager->DoesMessageBoxLExist( MSGLCMD_SIEGE_WARFARE ) )
		return;	
	
	CTString strMessage;		// ���� ��...
	CTString strNecessity[4];	// �ʿ� ����
	CTString strSelection[5];	// ���� ��Ʈ�� 
	CTString strName;
	int i;
	INDEX npcIndex = pUIManager->GetQuestBookComplete()->GetTargetIndex();

	// Create guild message box
	pUIManager->CreateMessageBoxL( m_strTitle, UI_SIEGE_WARFARE, MSGLCMD_SIEGE_WARFARE );					
	
	// [2010/11/01 : Sora] ���� ����
	strName = _S( 1982, "����NPC" );
	if( npcIndex == 1155 )
	{
		strName = CMobData::getData( npcIndex )->GetName();

		strMessage = _S( 5163, "�ٹ��� �̻� ��!!\n�� ������ �ִ� ��� �������� �� �ð� ������ ������ ������ �ֽʽÿ�.\n�ٷ� �������� �ϰڽ��ϴ�." );	
	}
	else
	{
		strMessage = _S( 1983, "�̰��� ���� ���̽Ű���?\n���� ���ֿ� ������ ��û�ϱ� ���ؼ� ���� �� �ƴϰ���?\n���ֶ�� ���� �׷��� ���ԵǴ� ���� �ƴմϴ�. ����� �Ʊ��ٸ� �׸� ���� ������." );	
		
		strNecessity[0] = _S( 1984, "�ʿ� ��巹�� : 5Lv" );	
		strNecessity[1] = _S( 1985, "�ʿ� ������ : ������ ��ǥ" );	
		strNecessity[2] = _S( 1986, "�ʿ� ���� : 20��" );	
		strNecessity[3] = _S( 1987, "�ʿ� ���� : 10�� ����" );	
	}

	pUIManager->AddMessageBoxLString( MSGLCMD_SIEGE_WARFARE, TRUE, strName, -1, SW_COLOR_TITLE );	

	// Description
	pUIManager->AddMessageBoxLString( MSGLCMD_SIEGE_WARFARE, TRUE, strMessage, -1, SW_COLOR_DESC );
	pUIManager->AddMessageBoxLString( MSGLCMD_SIEGE_WARFARE, TRUE, CTString(" "), -1, SW_COLOR_TEXT );
	
	// WSS_DRATAN_SEIGEWARFARE 2007/09/11	
	// �޶�ũ�� �ʿ� ������ ������ �Ѵ�.
	if( npcIndex == 219 ) // ��������
	{
		for( i = 0; i < 4; i++ )
		{
			pUIManager->AddMessageBoxLString( MSGLCMD_SIEGE_WARFARE, TRUE, strNecessity[i], -1, SW_COLOR_TEXT );
		}
	}	

	strSelection[0] = _S( 1988, "���� ��û." );	
	// WSS_DRATAN_SEIGEWARFARE 2007/09/11
	// ���ź�� ��� �뺴->����
	if( npcIndex == 387 )
	{
		strSelection[1] = _S( 1998, "������ �뺴��� ����." );	
	}
	else
	{
		strSelection[1] = _S( 1989, "�뺴 ��û." );	
	}
	
	strSelection[2] = _S( 1990, "�����ð� ����." );	
	strSelection[3] = _S( 1991, "�������� Ȯ��." );	
	strSelection[4] = _S( 880, "����ϱ�." );	

	CTString strLordCostume = _S( 5115, "���� �ڽ�Ƭ" );

	if ( !pUIManager->GetSiegeWarfareNew()->GetWarState() && !_pUISWDoc->IsWar() )
	{
		if ( (npcIndex == 219 || npcIndex == 387) && _pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS && _pNetwork->MyCharacterInfo.ubGuildNameColor != 0 )
		{	// ���ź ���� ����̰� �渶�̸�,
			pUIManager->AddMessageBoxLString( MSGLCMD_SIEGE_WARFARE, FALSE, strLordCostume, SEL_COSTUME_REQ );
		}

		// ���� ��常 Ŭ���̾�Ʈ���� üũ�� [1/21/2011 ldy1978220]
		if ( npcIndex == 1155 && _pNetwork->MyCharacterInfo.lGuildPosition != GUILD_MEMBER_BOSS && _pNetwork->MyCharacterInfo.ubGuildNameColor != 0 )
		{	// ���ź ���� ����̰� �渶�̸�,
			pUIManager->AddMessageBoxLString( MSGLCMD_SIEGE_WARFARE, FALSE, _S(2169,"���� ��� �ǻ�ޱ�"), SEL_GUILD_COSTUME_REQ );
			pUIManager->AddMessageBoxLString( MSGLCMD_SIEGE_WARFARE, FALSE, _S(2175,"���� ��� ȣĪ�ޱ�"), SEL_GUILD_TITLE_REQ );
		}
	}

	for( i = 0; i< 5; i++ )
	{
		if( npcIndex == 1155 )
		{
			if( i < 2 )
				continue;
		}
		pUIManager->AddMessageBoxLString( MSGLCMD_SIEGE_WARFARE, FALSE, strSelection[i], i );
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::OpenSWReq
// Explain:  ���� ��û
// Date : 2005-06-21,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::OpenSWReq() 
{	
	_pUISWDoc->SetUIState( SWS_SW_REQ );
	_pNetwork->AttackReq();
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::OpenMercearReq
// Explain:  �뺴��û
// Date : 2005-06-21,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::OpenMercearReq()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// WSS_DRATAN_SEIGEWARFARE 2007/09/11 ----------------------------->>
	// ���ź�� ��� ���� ��� ��û
	if( pUIManager->GetQuestBookComplete()->GetTargetIndex() == 387 )
	{
		_pNetwork->DefenseGuildReq();
		return;
	}	
	// ----------------------------------------------------------------<<

	static int nTotalSelection = 4;
	_pUISWDoc->SetUIState( SWS_MERCEAR_REQ );

	if(pUIManager->DoesMessageBoxLExist( MSGLCMD_MERCEAR_REQ ) )
		return;	
	
	CTString strMessage;		// ���� ��...
	CTString strNecessity[4];	// �ʿ� ����
	CTString strSelection[4];	// ���� ��Ʈ�� 
	int i;

	// Create guild message box
	pUIManager->CreateMessageBoxL( m_strTitle, UI_SIEGE_WARFARE, MSGLCMD_MERCEAR_REQ );					

	pUIManager->AddMessageBoxLString( MSGLCMD_MERCEAR_REQ, TRUE, _S( 1992, "�뺴��û NPC" ), -1, SW_COLOR_TITLE );		

	strMessage =_S( 1993,  "�뺴���� �̹� ������ �����ϰ� �����Ű���?\n������ ������ ���Դϴ�. ���� ������ �ϰ� �����ôٸ� �������� �ʰ����� ..." );	
	
	strNecessity[0] = _S( 1994, "�뺴 ����" );	
	strNecessity[1] = _S( 1995, "�ʿ� ���� : 15Lv �̻�" );	
	strNecessity[2] = _S( 1996, "�뺴 ��� ����" );	
	strNecessity[3] = _S( 1997, "�ʿ� ���� : 4Lv �̻�" );	
	//0xE18600FF
	// Description
	pUIManager->AddMessageBoxLString( MSGLCMD_MERCEAR_REQ, TRUE, strMessage, -1, SW_COLOR_DESC );
	pUIManager->AddMessageBoxLString( MSGLCMD_MERCEAR_REQ, TRUE, CTString(" "), -1, SW_COLOR_DESC );

	for( i = 0; i < 4; i++ )
	{
		COLOR Color = SW_COLOR_TITLE;
		if( i & 1 ) Color = SW_COLOR_TEXT; //�ӽ�
		pUIManager->AddMessageBoxLString( MSGLCMD_MERCEAR_REQ, TRUE, strNecessity[i], -1, Color );
	}

	strSelection[0] = _S( 1998, "������ �뺴��� ����." );	
	strSelection[1] = _S( 1999, "������ �뺴 ����." );	
	strSelection[2] = _S( 2000, "������ �뺴 ����." );	
	strSelection[3] =_S( 880,  "����ϱ�." );	

	for( i = 0; i< 4; i++ )
	{
		pUIManager->AddMessageBoxLString( MSGLCMD_MERCEAR_REQ, FALSE, strSelection[i], i );
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::
// Explain:  ���� Ȯ��
// Date : 2005-06-21,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::OpenSWInfo()
{
	_pUISWDoc->SetUIState( SWS_SW_INFO  );

	CUIManager* pUIManager = CUIManager::getSingleton();

	if( pUIManager->DoesMessageBoxExist( MSGCMD_SIEGE_WARFARE_INFO ) )
		return;

	CTString strMessage;
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( m_strTitle, UMBS_OK, UI_SIEGE_WARFARE, MSGCMD_SIEGE_WARFARE_INFO );
	

	MsgBoxInfo.AddString( _S( 2001, "�������" ), SW_COLOR_TITLE, TEXT_CENTER );	// ���� ���	

	if( _pUISWDoc->m_gdDefGuild.m_nGuildIndex <= 0 )
	{
		strMessage.PrintF(_S( 2002,  "���� ��尡 �������� �ʽ��ϴ�." ) );	
	}
	else
	{
		strMessage.PrintF(_S( 2146,  "%s ���" ), _pUISWDoc->m_gdDefGuild.m_strGuildName ); 
	}
	
	MsgBoxInfo.AddString( strMessage, SW_COLOR_TEXT, TEXT_CENTER ); // XXXXXXXXX����̸�
	
	MsgBoxInfo.AddString( CTString(" ") ); // XXXXXXXXX����̸�
	
	MsgBoxInfo.AddString( _S( 2003, "���� �ð�" ), SW_COLOR_TITLE, TEXT_CENTER ); // ���� �ð�	
	
	strMessage.PrintF(_S( 2004,  "%d�� %d�� %d" ), _pUISWDoc->m_nMonth, _pUISWDoc->m_nDay, _pUISWDoc->m_nHour );	
	MsgBoxInfo.AddString( strMessage, SW_COLOR_TEXT, TEXT_CENTER ); // XXXXXXXXX��¥ 
	MsgBoxInfo.AddString( CTString( " " ) );

	pUIManager->CreateMessageBox( MsgBoxInfo );

}

//------------------------------------------------------------------------------
// CUISiegeWarfare::
// Explain:  �ð� ���� 
// Date : 2005-06-21,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::OpenSetSWTime()
{
	SetSize( SIGEWARFARE_WIDTH, SIGEWARFARE_HEIGHT );
	ResetPos();

	_pUISWDoc->SetUIState( SWS_SET_SW_TIME );
	SetDayOfWeek( SATURDAY );

	m_lbDesc.ResetAllStrings();

	CTString strTemp, strAmPm;
	int hour;
	m_lbDesc.AddString( 0, _S( 5164, "����� ���� �ð�" ), SW_COLOR_TITLE );	
	
	m_sbtnSWZone.ResetAllDatas();

	CUIManager* pUIManager = CUIManager::getSingleton();

	for( int i=0; i<m_vecSWInfo.size(); ++i )
	{
		strTemp.PrintF(_s("%s(%s)"), CZoneInfo::getSingleton()->GetZoneName( m_vecSWInfo[i].zone ), _pUISWDoc->GetCastleName( m_vecSWInfo[i].zone ) );
		m_sbtnSWZone.AddData( strTemp );

		hour = m_vecSWInfo[i].zone == 4 ? m_vecSWInfo[i].hour - 12 + 2 : m_vecSWInfo[i].hour - 12 + 1;
		if( hour >= 12 )
		{
			if( hour > 12 )
			{
				hour -= 12;
			}
			strAmPm = "AM";
		}
		else
		{
			strAmPm = "PM";
		}

		//added by sam 10/12/20 ���� ��¥ �۾��� �ȳ����ų� ����
		//-------------------------------------------------------->		
		int iStringIndex = pUIManager->GetWeekToStringIndex( m_vecSWInfo[i].wday  );
		CTString ctDay;
		if ( -1 != iStringIndex)
		{
			ctDay = _S(iStringIndex,"����");
			strTemp.PrintF( _s("[%s] %s : PM%d:00 ~ %s%d:00"), CZoneInfo::getSingleton()->GetZoneName( m_vecSWInfo[i].zone ), 							
						ctDay, m_vecSWInfo[i].hour - 12, 
						 strAmPm, hour);	// ���ź 2�ð� �޶�ũ 1�ð�
		}
		else
		{
			strTemp.PrintF( _s("[%s] %s : PM%d:00 ~ %s%d:00"), CZoneInfo::getSingleton()->GetZoneName( m_vecSWInfo[i].zone ), 
						pUIManager->GetWeekToString( m_vecSWInfo[i].wday ), m_vecSWInfo[i].hour - 12, 							
						 strAmPm, hour);	// ���ź 2�ð� �޶�ũ 1�ð�
		}
		/*
		strTemp.PrintF( _s("[%s] %s : PM%d:00 ~ %s%d:00"), ZoneInfo().GetZoneName( m_vecSWInfo[i].zone ), 
					pUIManager->GetWeekToString( m_vecSWInfo[i].wday ), m_vecSWInfo[i].hour - 12, 							
					 strAmPm, hour);	// ���ź 2�ð� �޶�ũ 1�ð�
		/**/
		
		//<------------------------------------------------------------------
		m_lbDesc.AddString( 0, strTemp, SW_COLOR_TEXT );
	}

	m_lbDesc.AddString( 0, _S( 2005, "�������� �ð�" ), SW_COLOR_TITLE );	
	m_lbDesc.AddString( 0, _S( 2006, "����� : PM 06:00 ~ PM 11:00" ), SW_COLOR_TEXT );	
	m_lbDesc.AddString( 0, _S( 2007 , "�Ͽ��� : PM 01:00 ~ PM 11:00" ), SW_COLOR_TEXT );	

	CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE, TRUE );
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::RenderSetSWTime
// Explain:  
// Date : 2005-06-21,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::RenderSetSWTime()
{
	int	nX, nY;
	GetAbsPos( nX, nY );

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();
	
	pDrawPort->InitTextureData( m_ptdBaseTexture );

#define UNIT_SIZE_DEFAULT					40

	// Background 
	RenderRectUV3( UNIT_SIZE_DEFAULT, nX, nY, m_nWidth, TITLE_HEIGHT, m_rt3BackT ); 

	nY += TITLE_HEIGHT;
	RenderRectUV3( UNIT_SIZE_DEFAULT, nX, nY, m_nWidth, BACK_MIDDLE_DESC, m_rt3BackSM ); 
	nY += BACK_MIDDLE_DESC;
	RenderRectUV3( UNIT_SIZE_DEFAULT, nX, nY, m_nWidth, 3, m_rt3BackM ); 
	nY += 3;
	RenderRectUV3( UNIT_SIZE_DEFAULT, nX, nY, m_nWidth, BACK_MIDDLE_SELECT, m_rt3BackNM ); 
	nY += BACK_MIDDLE_SELECT;

	RenderRectUV3( UNIT_SIZE_DEFAULT, nX, nY, m_nWidth, 37 - BACK_BOTTOM_HEIGHT, m_rt3BackM ); 
	nY += 37 - BACK_BOTTOM_HEIGHT;
	RenderRectUV3( UNIT_SIZE_DEFAULT, nX, nY, m_nWidth, BACK_BOTTOM_HEIGHT, m_rt3BackL ); 

	// ������ ���� 
	m_cbtnSaturday.Render();
	m_cbtnSunday.Render();

	// ���� �ð� ���� 
	// SpinButton render
	m_sbtnSWTime.Render();

	m_sbtnSWZone.Render();

	// Description ListBox : ���� ���� �ð�
	m_lbDesc.Render();
	
	// Button
	m_btnOK.Render();
	m_btnCancel.Render();
	m_btnClose.Render();


	pDrawPort->FlushRenderingQueue();

	// Title
	pDrawPort->PutTextEx( m_strTitle, m_nPosX + TITLE_SX,
										m_nPosY + TITLE_SY );
	
	// ������
	pDrawPort->PutTextEx( _S(2008 , "������" ), m_nPosX + 18, m_nPosY + 35, SW_COLOR_TITLE );	

	// �����ð�
	pDrawPort->PutTextEx( _S( 2009, "�����ð�" ), m_nPosX + 18, m_nPosY + 81, SW_COLOR_TITLE );
	
	CTString cstrTiem = _S( 2009, "�����ð�");
	int nGap = _pUIFontTexMgr->GetFontWidth() * cstrTiem.Length();
	if ( nGap > 80 )
		pDrawPort->PutTextEx( _S( 5165, "����" ), m_nPosX + nGap + 18 + 5, m_nPosY + 81, SW_COLOR_TITLE );
	else 
		pDrawPort->PutTextEx( _S( 5165, "����" ), m_nPosX + 98, m_nPosY + 81, SW_COLOR_TITLE );

	// Flush all render text queue
	pDrawPort->EndTextEx();
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::RenderPoint
// Explain:  
// Date : 2005-06-28,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::RenderPoint( int nX, int nY, int nPoint )
{
	// ��µ� ��ġ �������� ������ ����
	int i = 1;
	int nRenderNumber;

	while( nPoint / i > 0  )
	{
		nX -= NUMBER_WIDTH;		
		i *= 10;
	}

	if ( i != 1 ) 
	{
		i /= 10;
	}
	else 
	{
		nX -= NUMBER_WIDTH;	
	}
	
	while( i )
	{		
		nRenderNumber = nPoint / i;
		nPoint %= i;

		DrawNumber( nX, nY, nRenderNumber );

		printf ( "%d", nRenderNumber );
		nX += NUMBER_WIDTH;	
		i /= 10;
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::RenderBattle
// Explain:  
// Date : 2005-06-21,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::RenderBattle()
{
	int	nX, nY;
	GetAbsPos( nX, nY );

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	pDrawPort->InitTextureData( m_ptdBaseTexture );

	pDrawPort->AddTexture( m_nPosX, m_nPosY, m_nPosX + BATTLE_WIDTH, m_nPosY + BATTLE_HEIGHT,
										m_rtBattleBack.U0, m_rtBattleBack.V0, m_rtBattleBack.U1, m_rtBattleBack.V1,
										0xFFFFFFFF );

	if( _pUISWDoc->IsSelectBattle() )
	{
		int nOffsetX, nOffsetY;
		nOffsetX = m_nPosX;
		nOffsetY = m_nPosY + INFO_OFFSETY;
	
		pDrawPort->AddTexture( nOffsetX, nOffsetY, nOffsetX + INFO_WIDTH, nOffsetY + INFO_HEIGHT,
										m_rtSelectBattleBack.U0, m_rtSelectBattleBack.V0, m_rtSelectBattleBack.U1, m_rtSelectBattleBack.V1,
										0xFFFFFFFF );
	
		pDrawPort->PutTextEx( _S( 2010, "�������Ʈ" ), nOffsetX + UNIT_TEXT_OFFSETX,	
											nOffsetY + ( UNIT_HEIGHT * 0 ) 
													+ UNIT_TEXT_OFFSETY, SW_COLOR_DEFENSE_POINT );	
		// Render Number
		RenderPoint(	nOffsetX + UNIT_POINT_OFFSETX, 
						nOffsetY + ( UNIT_HEIGHT * 0 + UNIT_POINT_OFFSETY ),
						_pUISWDoc->m_nGuildPoint );

		pDrawPort->PutTextEx( _S( 2011, "����������Ʈ" ), nOffsetX + UNIT_TEXT_OFFSETX,	
											nOffsetY + ( UNIT_HEIGHT * 1 ) 
													+ UNIT_TEXT_OFFSETY, SW_COLOR_DEFENSE_POINT );	
		// Render Number
		RenderPoint(	nOffsetX + UNIT_POINT_OFFSETX, 
						nOffsetY + ( UNIT_HEIGHT * 1 + UNIT_POINT_OFFSETY ),
						_pUISWDoc->m_gdDefGuild.m_nPoint );

		
		pDrawPort->FlushRenderingQueue();
	}
	
	RenderLeftTime();

	for( int i = 0; i < 3; i++)
	{
		
		pDrawPort->PutTextEx( _pUISWDoc->m_gdGuild[i].m_strGuildName, m_nPosX + UNIT_TEXT_OFFSETX,
											m_nPosY + UNIT_TIME_HEIGHT + ( UNIT_HEIGHT * i ) 
													+ UNIT_TEXT_OFFSETY, SW_COLOR_GUILD_NAME );	
		// Render Number
		RenderPoint(	m_nPosX + UNIT_POINT_OFFSETX, 
						m_nPosY + UNIT_TIME_HEIGHT + ( UNIT_HEIGHT * i + UNIT_POINT_OFFSETY ),
						_pUISWDoc->m_gdGuild[i].m_nPoint );
	}

	pDrawPort->FlushRenderingQueue();
	
	// Flush all render text queue
	pDrawPort->EndTextEx();
}


//------------------------------------------------------------------------------
// CUISiegeWarfare::DrawNumber
// Explain:  
// Date : 2005-06-28,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::DrawNumber( int nX, int nY, int nNumber, int nWidth, int nHeight )
{
	UIRectUV rtNumber = m_rtNumber[nNumber];

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	pDrawPort->AddTexture( nX, nY, nX + nWidth, nY + nHeight,
							rtNumber.U0, rtNumber.V0, rtNumber.U1, rtNumber.V1,
							0xFFFFFFFF );

}

//------------------------------------------------------------------------------
// CUIMessenger::RenderRectUV3
// Explain:  
// Date : 2005-05-23,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::RenderRectUV3( int nUnitSize, int nX, int nY, int nWidth, int nHeight, UIRectUV3 rtRectUV3 )
{
	int nX2 = nX + nWidth;
	int nY2 = nY + nHeight;

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	pDrawPort->AddTexture( nX, nY, nX + nUnitSize, nY2,
										rtRectUV3.rtL.U0, rtRectUV3.rtL.V0, rtRectUV3.rtL.U1, rtRectUV3.rtL.V1,
										0xFFFFFFFF );
	pDrawPort->AddTexture( nX + nUnitSize, nY, nX2 - nUnitSize, nY2,
										rtRectUV3.rtM.U0, rtRectUV3.rtM.V0, rtRectUV3.rtM.U1, rtRectUV3.rtM.V1,
										0xFFFFFFFF );
	pDrawPort->AddTexture( nX2 - nUnitSize, nY, nX2, nY2,
										rtRectUV3.rtR.U0, rtRectUV3.rtR.V0, rtRectUV3.rtR.U1, rtRectUV3.rtR.V1,
										0xFFFFFFFF );
}


//------------------------------------------------------------------------------
// CUISiegeWarfare::CloseAllMsgBox
// Explain:  
// Date : 2005-06-21,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::CloseAllMsgBox()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->CloseMessageBox(MSGCMD_SIEGE_WARFARE_ERROR);
	pUIManager->CloseMessageBox(MSGCMD_SIEGE_WARFARE_INFO);
}

//------------------------------------------------------------------------------
// CUIGuildBattle::GBErrorMessage
// Explain:  
// Date : 2005-03-19(���� 12:28:10) Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::ErrorMessage( CTString strErrorMessage )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->CloseMessageBox(MSGCMD_SIEGE_WARFARE_ERROR);

	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( m_strTitle, UMBS_OK, UI_SIEGE_WARFARE, MSGCMD_SIEGE_WARFARE_ERROR );
	MsgBoxInfo.AddString( strErrorMessage );	
	pUIManager->CreateMessageBox( MsgBoxInfo );		
}


//------------------------------------------------------------------------------
// CUIGuildBattle::GBMessage
// Explain:  
// Date : 2005-03-21(���� 4:46:32) Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::Message( int nCommandCode, CTString strMessage, DWORD dwStyle )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( pUIManager->DoesMessageBoxExist( nCommandCode ) )
		return;

	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( m_strTitle, dwStyle, UI_SIEGE_WARFARE, nCommandCode );
	
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::SetDayOfWeek
// Explain:  
// Date : 2005-06-21,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::SetDayOfWeek( int nDayOfWeek )
{
	int nTimePrev, nTimeNext;

	if( nDayOfWeek == SATURDAY )
	{
		m_cbtnSaturday.SetCheck( TRUE );
		m_cbtnSunday.SetCheck( FALSE );

		m_sbtnSWTime.ResetAllDatas();

		nTimePrev = 6; nTimeNext = 11;
		nTimePrev = 5;

	
		if (g_iCountry == USA)
		{
			nTimePrev = 10;
			nTimeNext = 23;
		}

		for( int i = nTimePrev; i <= nTimeNext; i++ ) //!�ð� ����
		{
			CTString strTime;
			strTime.PrintF( "%d", i );
			m_sbtnSWTime.AddData( strTime );
		}

	}
	else if( nDayOfWeek == SUNDAY )
	{
		m_cbtnSaturday.SetCheck( FALSE );
		m_cbtnSunday.SetCheck( TRUE );

		m_sbtnSWTime.ResetAllDatas();

		nTimePrev = 1; nTimeNext = 11;

		if (g_iCountry == USA)
		{
			nTimePrev = 11;
			nTimeNext = 20;
		}

		for( int i = nTimePrev; i <= nTimeNext; i++ )//!�ð�
		{
			CTString strTime;
			strTime.PrintF( "%d", i );
			m_sbtnSWTime.AddData( strTime );
		}
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::MouseMessage
// Explain:  
// Date : 2005-06-28,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
WMSG_RESULT CUISiegeWarfare::MouseMessage( MSG *pMsg )
{
	WMSG_RESULT	wmsgResult;
	// Title bar
	static BOOL	bTitleBarClick = FALSE;

	// Item clicked
	static BOOL	bLButtonDownInItem = FALSE;

	// Mouse point
	static int	nOldX, nOldY;
	int	nX = LOWORD( pMsg->lParam );
	int	nY = HIWORD( pMsg->lParam );
	
	// Mouse message
	switch( pMsg->message )
	{
	case WM_MOUSEMOVE:
		{
			//if( IsInside( nX, nY ) )

			int	ndX = nX - nOldX;
			int	ndY = nY - nOldY;

			// Move shop
			if( bTitleBarClick && ( pMsg->wParam & MK_LBUTTON ) )
			{
				nOldX = nX;	nOldY = nY;
				Move( ndX, ndY );
				if( IsInside( nX, nY ) )
					CUIManager::getSingleton()->SetMouseCursorInsideUIs();
			
				return WMSG_SUCCESS;
			}

			// ��� ��û ������ 
			if( _pUISWDoc->IsSetSWTime() ) // �ð� ���� ������ 
			{
				if( IsInside( nX, nY ) )
					CUIManager::getSingleton()->SetMouseCursorInsideUIs();
				if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;
				else if( m_btnCancel.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;
				else if( m_btnClose.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;
				else if( m_sbtnSWTime.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;
				else if( m_sbtnSWZone.MouseMessage( pMsg ) != WMSG_FAIL )
					return WMSG_SUCCESS;
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			if( _pUISWDoc->IsSetSWTime() ) // �ð� ���� ������ 
			{
				if( IsInside( nX, nY ) )
				{
					nOldX = nX;		nOldY = nY;
				
					// Title bar
					if( IsInsideRect( nX, nY, m_rcTitle ) )
					{
						bTitleBarClick = TRUE;
					}

					// OK Button
					if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
					{
						return WMSG_SUCCESS;
					}
					else if( m_btnCancel.MouseMessage( pMsg ) != WMSG_FAIL )
					{
						return WMSG_SUCCESS;
					}
					else if( m_btnClose.MouseMessage( pMsg ) != WMSG_FAIL )
					{
						return WMSG_SUCCESS;
					}
					else if( m_cbtnSaturday.MouseMessage( pMsg ) != WMSG_FAIL )
					{
						SetDayOfWeek( SATURDAY );
						return WMSG_SUCCESS;
					}
					else if( m_cbtnSunday.MouseMessage( pMsg ) != WMSG_FAIL )
					{
						SetDayOfWeek( SUNDAY );
						return WMSG_SUCCESS;
					}
					else if( m_sbtnSWTime.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					else if( m_sbtnSWZone.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					
					CUIManager::getSingleton()->RearrangeOrder( UI_GUILD_BATTLE, TRUE );
					return WMSG_SUCCESS;
				}
			}
		}
		break;

	case WM_LBUTTONUP:
		{
			bTitleBarClick = FALSE;
		
			if( _pUISWDoc->IsSetSWTime() ) // �ð� ���� ������ 
			{				
				if( IsInside( nX, nY ) )
				{
					// OK Button
					if( ( wmsgResult = m_btnOK.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							int nDay = -1;
							int nHour = 0;

							// ��¥���
							if( m_cbtnSaturday.IsChecked() )		nDay = SATURDAY;
							else if ( m_cbtnSunday.IsChecked() )	nDay = SUNDAY;
							// �ð� ���
							
							if (g_iCountry == USA)
								nHour = m_sbtnSWTime.GetDataToNumber();
							else
								nHour = m_sbtnSWTime.GetDataToNumber() + 12;
			
							int zone = m_vecSWInfo[m_sbtnSWZone.GetSelectPos()].zone;
							_pNetwork->SetTimeReq( nDay, nHour, zone);

						}
						return WMSG_SUCCESS;
					}
					else if( ( wmsgResult = m_btnCancel.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							CloseSiegeWarfare();
							OpenSiegeWarfare();
						}
						return WMSG_SUCCESS;
					}
					else if( ( wmsgResult = m_btnClose.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							CloseSiegeWarfare();
							OpenSiegeWarfare();
						}
						return WMSG_SUCCESS;
					}
					else if( m_sbtnSWTime.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					else if( m_sbtnSWZone.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;

					return WMSG_SUCCESS;
				}
			}
		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			if( _pUISWDoc->IsSetSWTime() ) // �ð� ���� ������ 
			{
				if( IsInside( nX, nY ) )
				{ // ��ư Ŭ���� �ߵ��� �ʴ� ������ ���� Ŭ���� ó������ �ʴ´�.
//					if( m_sbtnSWTime.MouseMessage( pMsg ) != WMSG_FAIL )
//							return WMSG_SUCCESS;

					return WMSG_SUCCESS;
				}
			}
		}
		break;

	case WM_MOUSEWHEEL:
		{
			if( _pUISWDoc->IsSetSWTime() ) // �ð� ���� ������ 
			{
				if( IsInside( nX, nY ) )
				{
					if( m_sbtnSWTime.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					if( m_sbtnSWZone.MouseMessage( pMsg ) != WMSG_FAIL )
						return WMSG_SUCCESS;
					
					return WMSG_SUCCESS;		
				}
			}
		}
		break;
	}

	return WMSG_FAIL;
}


//------------------------------------------------------------------------------
// CUIGuildBattle::SetNotice
// Explain:  
// Date : 2005-03-21(���� 9:53:57) Lee Ki-hwan
//------------------------------------------------------------------------------
void CUISiegeWarfare::SetNotice( CTString strNoticeMessage, CTString strNoticeMessage2 )
{
	CloseAllMsgBox();

	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->RearrangeOrder( UI_SIEGE_WARFARE, TRUE );

	// [2012/06/04 : Sora] ITS 8986 ���������� �������� �������� �̵� �� ĳ���� �̵��Ұ� ���� �߻� ����
	// ���� �޽��� ����ϸ鼭 �ش� UI�� Ȱ��ȭ �����־��� �Ѵ�. ���� �޽��� ��� ��� ����
#ifdef	IMPROV1107_NOTICESYSTEM
	_UIAutoHelp->SetGMNotice( strNoticeMessage );
	
	if( strNoticeMessage2.Length() > 0 )
	{
		_UIAutoHelp->SetGMNotice( strNoticeMessage2 );
	}
#else
	m_bShowNotice = TRUE;
	m_bBottomNotice = TRUE;

	pUIManager->GetChattingUI()->AddSysMessage( strNoticeMessage, SYSMSG_NORMAL );	

	if( strNoticeMessage2.Length() <= 1 )
	{
		m_bBottomNotice = FALSE;
	}
	else
	{
		pUIManager->GetChattingUI()->AddSysMessage( strNoticeMessage2, SYSMSG_NORMAL );	
	}

	int nWidth = 0;
	CDrawPort* pDrawPort = pUIManager->GetDrawPort();
	int nCX = pDrawPort->dp_MinI + ( pDrawPort->dp_MaxI - pDrawPort->dp_MinI ) / 2;

	m_strNoticeMessage = strNoticeMessage;
	m_strNoticeMessage2 = strNoticeMessage2;

	// ���ʿ� ��� �� ����
	nWidth = ( m_strNoticeMessage.Length() ) * 
			 ( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() ) - 1;
		
	m_rcNotice1.Left = nCX - nWidth / 2;
	m_rcNotice1.Right = m_rcNotice1.Left + nWidth;


	// �Ʒ��ʿ� ��µ� ����
	nWidth = ( strNoticeMessage2.Length() ) *
			 ( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() ) - 1;
		
	m_rcNotice2.Left = nCX - nWidth / 2;
	m_rcNotice2.Right = m_rcNotice2.Left + nWidth;

	// �ð� ����
	m_tmNoticeTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds ();
#endif
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::OpenCostumeReq
// Explain: ���� �ڽ�Ƭ ���� ��û
// Date : 2010-09-15
//------------------------------------------------------------------------------
void CUISiegeWarfare::OpenCostumeReq()
{
	CTString strTitle = _S( 5115, "���� �ڽ�Ƭ" );
	CTString strMessage;

	CUIManager* pUIManager = CUIManager::getSingleton();

	pUIManager->CreateMessageBoxL( strTitle, UI_SIEGE_WARFARE, MSGLCMD_LORD_COSTUME_REQ );
	
	pUIManager->AddMessageBoxLString( MSGLCMD_LORD_COSTUME_REQ, TRUE, _S( 1748, "�ȳ�" ) );		
	
	strMessage =_S( 5116, "�ȳ��ϼ���. ���ִ�. ������ �÷ð� ���� �ӿ� ���� ������ �������� �¸��Ͽ� ���ְ� �ǽ� ���� ���� �帳�ϴ�. ���� �� ������ �԰� ���� �������� ���� �˸��ñ� �ٶ��ϴ�." );	
	pUIManager->AddMessageBoxLString( MSGLCMD_LORD_COSTUME_REQ, TRUE, strMessage, -1, SW_COLOR_DESC );
	pUIManager->AddMessageBoxLString( MSGLCMD_LORD_COSTUME_REQ, TRUE, CTString(" "), -1, SW_COLOR_DESC );
	
	strMessage = _S( 1839, "������ ����" );
	pUIManager->AddMessageBoxLString( MSGLCMD_LORD_COSTUME_REQ, FALSE, strMessage, 0 );
}

//------------------------------------------------------------------------------
// CUISiegeWarfare::SetSiegeWarfareTimeInfo
// Explain: ���� �ð� ���� ����
// Date : 2010-11-01
//------------------------------------------------------------------------------
void CUISiegeWarfare::SetSiegeWarfareTimeInfo( stSiegeWarfareTimeInfo swInfo )
{
	m_vecSWInfo.push_back( swInfo );
}

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::CUISiegeWarfareInfo
// Explain: 
// Date : 2010-11-01
//------------------------------------------------------------------------------
CUISiegeWarfareInfo::CUISiegeWarfareInfo()
{

}

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::~CUISiegeWarfareInfo
// Explain: 
// Date : 2010-11-01
//------------------------------------------------------------------------------
CUISiegeWarfareInfo::~CUISiegeWarfareInfo()
{

}

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::Create
// Explain: 
// Date : 2010-11-01
//------------------------------------------------------------------------------
void CUISiegeWarfareInfo::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight )
{
	CUIWindow::Create(pParentWnd, nX, nY, nWidth, nHeight);

	m_ptdBaseTexture = CreateTexture( CTString( "Data\\Interface\\new_Interface.tex" ) );
	FLOAT	fTexWidth = m_ptdBaseTexture->GetPixWidth();
	FLOAT	fTexHeight = m_ptdBaseTexture->GetPixHeight();

	m_bxBackground[0].SetBoxUV(m_ptdBaseTexture, 120, 36, WRect(0,98,272,253));
	m_bxBackground[0].SetBoxPos(WRect(0,0,nWidth,nHeight));

	m_bxBackground[1].SetBoxUV(m_ptdBaseTexture, 20, WRect(0,304,221,346));
	m_bxBackground[1].SetBoxPos(WRect(20, 80, 380, 175));

	m_bxBackground[2].SetBoxUV(m_ptdBaseTexture, 20, WRect(0,304,221,346));
	m_bxBackground[2].SetBoxPos(WRect(20, 200, 380, 295));

	m_bxBackground[3].SetBoxUV(m_ptdBaseTexture, 3, WRect(339,464,368,466));
	m_bxBackground[3].SetBoxPos(WRect(20, 50, 380, 53));

	m_btnOK.Create(this, CTString(_S(191, "Ȯ��")), 150, 310, 100, 20);
	m_btnOK.SetUV(UBS_IDLE,282,244,351,265, fTexWidth, fTexHeight );
	m_btnOK.SetUV(UBS_CLICK, 364,244,433,265, fTexWidth, fTexHeight);
	m_btnOK.CopyUV(UBS_IDLE, UBS_ON);
	m_btnOK.CopyUV(UBS_IDLE, UBS_DISABLE);

	m_rsMyGuildName.Create(this, 28, 248, 85, 25 );
	m_rsMyGuildName.SetAlign( ALIGN_CENTER );

	m_rsMyGuildBossName.Create(this, 113, 248, 85, 25 );
	m_rsMyGuildBossName.SetAlign( ALIGN_CENTER );

	m_rcTitle.SetRect(0, 0, nWidth, 30);
}

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::Render
// Explain: 
// Date : 2010-11-01
//------------------------------------------------------------------------------
void CUISiegeWarfareInfo::Render()
{
	CTString strTemp;

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	pDrawPort->InitTextureData( m_ptdBaseTexture );

	for(int i =0; i < 4; i++)
	{
		m_bxBackground[i].Render(m_nPosX,m_nPosY);
	}

	m_btnOK.Render();

	pDrawPort->FlushRenderingQueue();

	pDrawPort->PutTextExCX(_S( 5166, "���� ���� ����"), m_nPosX+200, m_nPosY+18);

	pDrawPort->PutTextEx(_S( 5167, "���� ����"), m_nPosX + 25, m_nPosY + 60);
	pDrawPort->PutTextEx(_S( 5168, "���� ����"), m_nPosX + 25, m_nPosY + 180);
	

	pDrawPort->PutTextExCX( _S( 2001, "�������"), m_nPosX + 100, m_nPosY + 85 );
	pDrawPort->PutTextExCX( _S( 5165, "����"), m_nPosX + 230, m_nPosY + 85 );
	pDrawPort->PutTextExCX( _S( 1718, "�ð�"), m_nPosX + 330, m_nPosY + 85 );

	if( m_vecDefGuildInfo.size() == 0 )
	{
		pDrawPort->PutTextExCX( _S( 2002,  "���� ��尡 �������� �ʽ��ϴ�." ), m_nPosX + 200, m_nPosY + 124);
	}
	else
	{
		for( int i=0; i<m_vecDefGuildInfo.size(); ++i )
		{
			pDrawPort->PutTextExCX( m_vecDefGuildInfo[i].guildName, m_nPosX + 100, m_nPosY + 110+(i*28));
			pDrawPort->PutTextExCX( CZoneInfo::getSingleton()->GetZoneName( m_vecDefGuildInfo[i].zone ), m_nPosX + 230, m_nPosY + 110+(i*28));

			strTemp.PrintF(_S( 2004,  "%d�� %d�� %d" ), m_vecDefGuildInfo[i].month, m_vecDefGuildInfo[i].day, m_vecDefGuildInfo[i].hour );
			pDrawPort->PutTextExCX( strTemp, m_nPosX + 330, m_nPosY + 110+(i*28));
		}
	}

	pDrawPort->PutTextExCX( _S( 3451, "��� ��"), m_nPosX + 70, m_nPosY + 205 );
	pDrawPort->PutTextExCX( _S( 4344, "��� ������"), m_nPosX + 155, m_nPosY + 205 );
	pDrawPort->PutTextExCX( _S( 5169, "���� ����"), m_nPosX + 255, m_nPosY + 205 );
	pDrawPort->PutTextExCX( _S( 5165, "����"), m_nPosX + 335, m_nPosY + 205 );

	if( m_MySiegeWarfareInfo.vecZone.size() > 0 )
	{
		m_rsMyGuildName.Render();
		m_rsMyGuildBossName.Render();

		for( int j=0; j<m_MySiegeWarfareInfo.vecZone.size(); ++j )
		{	
			pDrawPort->PutTextExCX( GetJoinStatusString( m_MySiegeWarfareInfo.vecJoinFlag[j] ), m_nPosX + 255, m_nPosY + 248 + (j*14) );
			pDrawPort->PutTextExCX( CZoneInfo::getSingleton()->GetZoneName( m_MySiegeWarfareInfo.vecZone[j] ), m_nPosX + 335, m_nPosY + 248 + (j*14) );	
		} 
	}
	else
	{
		pDrawPort->PutTextExCX( _S( 5170, "���� ���� ������ �������� �ʽ��ϴ�." ), m_nPosX + 200, m_nPosY + 248);
	}

	pDrawPort->EndTextEx();
}

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::ResetPosition
// Explain: 
// Date : 2010-11-01
//------------------------------------------------------------------------------
void CUISiegeWarfareInfo::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::AdjustPosition
// Explain: 
// Date : 2010-11-01
//------------------------------------------------------------------------------
void CUISiegeWarfareInfo::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::MouseMessage
// Explain: 
// Date : 2010-11-01
//------------------------------------------------------------------------------
WMSG_RESULT CUISiegeWarfareInfo::MouseMessage( MSG *pMsg )
{
	WMSG_RESULT	wmsgResult;
	
	// Title bar
	static BOOL	bTitleBarClick = FALSE;

	// Mouse point
	static int	nOldX, nOldY;
	int	nX = LOWORD( pMsg->lParam );
	int	nY = HIWORD( pMsg->lParam );

	switch( pMsg->message )
	{
		case WM_MOUSEMOVE:
			{
				if( IsInside( nX, nY ) )
					CUIManager::getSingleton()->SetMouseCursorInsideUIs();
				
				int	ndX = nX - nOldX;
				int	ndY = nY - nOldY;

				if( bTitleBarClick && ( pMsg->wParam & MK_LBUTTON ) )
				{
					nOldX = nX;	nOldY = nY;
					
					Move( ndX, ndY );
					
					return WMSG_SUCCESS;
				}

				m_btnOK.MouseMessage( pMsg );
			}
			break;

		case WM_LBUTTONDOWN:
			{
				if( IsInside( nX, nY ) )
				{
					nOldX = nX;		nOldY = nY;
					if( IsInsideRect( nX, nY, m_rcTitle ) )
					{
						bTitleBarClick = TRUE;
					}

					if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
					{
					}

					CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_INFO, TRUE );
					return WMSG_SUCCESS;
				}

			}
			break;

		case WM_LBUTTONUP:
			{
				CUIManager* pUIManager = CUIManager::getSingleton();
				bTitleBarClick = FALSE;

				if (pUIManager->GetDragIcon() == NULL)
				{
					if( !IsFocused() )
						return WMSG_FAIL;

					if( ( wmsgResult = m_btnOK.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							ToggleSiegeWarfareInfo( FALSE );
						}

						return WMSG_SUCCESS;
					}
				}
				else
				{
					pUIManager->ResetHoldBtn();
				}

			}
			break;
	}

	return WMSG_FAIL;
}

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::InitSiegeWarfareInfo
// Explain: 
// Date : 2010-11-01
//------------------------------------------------------------------------------
void CUISiegeWarfareInfo::InitSiegeWarfareInfo()
{
	m_MySiegeWarfareInfo.Init();
	m_vecDefGuildInfo.clear();

	m_rsMyGuildName.ClearString();
	m_rsMyGuildBossName.ClearString();
}

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::SetSiegeWarfareDefGuildInfo
// Explain: ������� ���� ����
// Date : 2010-11-01
//------------------------------------------------------------------------------
void CUISiegeWarfareInfo::SetSiegeWarfareDefGuildInfo( stSiegeWarfareDefGuildInfo defGuildInfo )
{
	BOOL exist = FALSE;
	for (int i = 0; i < m_vecDefGuildInfo.size(); i++) {
		if (m_vecDefGuildInfo[i].guildName == defGuildInfo.guildName) {
			exist = TRUE;
		}
	}
	
	if (!exist) {
		m_vecDefGuildInfo.push_back(defGuildInfo);
	}
} 

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::SetMySiegeWarfareGuildInfo
// Explain: �� ������� ����
// Date : 2010-11-01
//------------------------------------------------------------------------------
void CUISiegeWarfareInfo::SetMySiegeWarfareGuildInfo( CTString guildName, CTString guildBossName )
{

	if (guildName.Length() > 12) 
		guildName = std::string(guildName.str_String).substr(0, 12).c_str();
	
	if (guildBossName.Length() > 12) 
		guildBossName = std::string(guildBossName.str_String).substr(0, 12).c_str();

	m_MySiegeWarfareInfo.guildName = guildName;
	m_MySiegeWarfareInfo.guildBossName = guildBossName;

	m_rsMyGuildName.AddString( guildName );
	m_rsMyGuildBossName.AddString( guildBossName );
}

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::SetMySiegeWarfareJoinInfo
// Explain: �� �������� ����
// Date : 2010-11-01
//------------------------------------------------------------------------------
void CUISiegeWarfareInfo::SetMySiegeWarfareJoinInfo( char zone, char joinFlag )
{
	m_MySiegeWarfareInfo.vecZone.push_back( zone );
	m_MySiegeWarfareInfo.vecJoinFlag.push_back( joinFlag );
}

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::ToggleSiegeWarfareInfo
// Explain: ��������â �����ݱ�
// Date : 2010-11-01
//------------------------------------------------------------------------------
void CUISiegeWarfareInfo::ToggleSiegeWarfareInfo( BOOL bShown )
{
	if( !bShown )
	{
		InitSiegeWarfareInfo();
	}

	CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_INFO, bShown );
}

//------------------------------------------------------------------------------
// CUISiegeWarfareInfo::GetJoinStatusString
// Explain: �������� ���� ��Ʈ��
// Date : 2010-11-01
//------------------------------------------------------------------------------
CTString CUISiegeWarfareInfo::GetJoinStatusString( char joinFlag )
{
	switch( joinFlag )
	{
		case WCJF_NONE:
			return "";
		case WCJF_OWNER:
			return _S( 5171, "���ֱ��");
		case WCJF_DEFENSE_GUILD:
			return _S( 2001, "�������" );
		case WCJF_DEFENSE_CHAR:
			return _S( 5172, "�������뺴");
		case WCJF_ATTACK_GUILD:
			return _S( 5173, "�������");
		case WCJF_ATTACK_CHAR:
			return _S( 5174, "�������뺴");
	}
	
	return "";
}

