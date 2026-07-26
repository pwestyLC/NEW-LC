#include "stdh.h"

// ��� ����. [12/2/2009 rumist]
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UISignBoard.h>
#include <Engine/Templates/Stock_CFontData.h>		// Font Use ...
#include <Engine/Interface/UISiegeWarfareDoc.h>
#include <Engine/World/World.h>
#include <Engine/Help/DefineHelp.h>

CUISignBoard*	_UISignBoard = NULL;

extern BOOL g_bIsMalEng;
// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
ENGINE_API void ShowSignBoard ( int nIndex )
{
	_UISignBoard->ShowSingBoard ( nIndex );
}


// ----------------------------------------------------------------------------
// Name : CUIRefine()
// Desc : Constructor
// ----------------------------------------------------------------------------
CUISignBoard::CUISignBoard()
{
	m_ptdBaseTexture = NULL;
	Clear ();
	
	
}

// ----------------------------------------------------------------------------
// Name : ~CUIRefine()
// Desc : Destructor
// ----------------------------------------------------------------------------
CUISignBoard::~CUISignBoard()
{
	Clear ();
	STOCK_RELEASE(m_ptdBaseTexture);
}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
void CUISignBoard::Clear ()
{

	m_nTextureIndex = -1;
	m_bStop			= FALSE;		// ���� �����ΰ�?
	m_fShowTime		= 0;
	m_iAlpha		= 0x01;
	m_FadeInOp		= 64;
	m_FadeOutOp		= -16;
	m_bText			= false;
	
	m_strLocalName.Clear ();

	m_bVisible		= false;
}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
void CUISignBoard::Create( int iCountry )
{



}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
void CUISignBoard::ShowSingBoard ( int nIndex, SLONG slZoneIndex )
{
	SLONG	slIndex = g_slZone;

	if ( nIndex < -1 || g_slZone<0 ) 
	{
		return;
	}
	else if ( nIndex != -1 && m_nTextureIndex == nIndex )	// ���� ���� �� ���
	{
		// ���� ǥ�� �ð��� �ٽ� ���� �� �ش�.
		m_fShowTime	= SHOW_TIME;
		return;
	}

	if( slZoneIndex != -1 )
	{
		slIndex = slZoneIndex;
	}

	// ���̸��� ���� �ε����� ���� �̸� ������ �ε��Ѵ�.
	if ( LoadSignBoardTexture ( slIndex, nIndex ) == FALSE )
	{
		return;
	}
	
	// ������ �ʱ�ȭ
	m_bVisible = TRUE;
	m_strLocalName	=_S( 2062,  "������" );		
	m_fShowTime		= SHOW_TIME;
	m_op			= m_FadeInOp;
}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
void CUISignBoard::Render ()
{
	if ( !m_bVisible )	return;
	
	// ȭ�鿡 ���� �ְ� �ִٸ� ������ �ð��� üũ �ؼ� �������� ���� �� �� ���� Ȯ�� �Ѵ�.
	if ( m_bStop )	
	{
		if ( _pTimer->GetHighPrecisionTimer().GetMilliseconds() - m_tmStartTime >= m_fShowTime )
		{
			m_op 	= m_FadeOutOp;
			m_bStop = FALSE;
		}
	}
	else
	{	
		m_iAlpha += m_op;

		if ( m_iAlpha >= 0xff )
		{
			m_iAlpha	= 0xff;
			m_bStop		= TRUE;
			m_tmStartTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds ();
		}
		else if ( m_iAlpha <= 0 )
		{
			// END
			Clear ();
		}
	}

	if( m_ptdBaseTexture == NULL )
	{
		return;
	}

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	int pX = pDrawPort->GetWidth() / 2 - m_fTexWidth / 2;
	int pY = SIGNBOARD_SY;

	pDrawPort->InitTextureData( m_ptdBaseTexture );

	pDrawPort->AddTexture( pX, pY,	pX + m_fTexWidth , pY + m_fTexHeight, 
										m_rtCurrent.U0, m_rtCurrent.V0, 
										m_rtCurrent.U1, m_rtCurrent.V1,
										0xffffff00 | m_iAlpha );

	pDrawPort->FlushRenderingQueue();


}


//------------------------------------------------------------------------------
// CUISignBoard::LoadSignBoardTexture
// Explain: ����ȣ(nZoneIndex)�� ������ȣ(nLocalIndex), ���� �������� 
//          ���ϸ��� �����Ͽ� �׽��� ������ �ε� �Ѵ�.
//
// Date : 2005-01-13,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
BOOL CUISignBoard::LoadSignBoardTexture( int nZoneIndex, int nLocalIndex )
{
	extern INDEX	g_iCountry;
	extern CTString g_language;
	
	CTString strSignBoardName;
	CTString strDir = "Local\\";
	strDir += DefHelp::getNationPostfix(DefHelp::getNationByLang(g_language), true);
	strDir += "\\SignBoard\\";

	// �̹� �׽��İ� �ε� �Ǿ� ������ ����
	if( m_ptdBaseTexture != NULL )
	{
		_pTextureStock->Release( m_ptdBaseTexture );
		m_ptdBaseTexture = NULL;
	}

	// += �� �̸� += ���� ��ȣ  
	strSignBoardName.PrintF ( "sb_%d_%d", nZoneIndex, nLocalIndex );
	
	// �������� (7�� ���� 11�� ����) �� ��쿡�� ���������� �ƴ����� ���� ǥ�ð� �ٸ�
	if( nZoneIndex == 7 && nLocalIndex == 11 )
	{
		if( _pUISWDoc->IsWar() )
			strSignBoardName += "_war";
	}

	strSignBoardName += ".tex";

	//[090914 ���κ��� ������ ������ �ý��� �޽����� ����Ѵ�]
	// �׽��� �ε�
	try
	{
		m_ptdBaseTexture = _pTextureStock->Obtain_t ( strDir + strSignBoardName );
	}
	catch (char* strError)
	{
		if ( _pNetwork->m_ubGMLevel > 0 )
		{	// GM�϶��� ǥ��
			//FatalError(strError);
			CTString strtmpError = strError;
			_pNetwork->ClientSystemMessage(strtmpError, SYSMSG_ERROR);
		}

		return FALSE;
	}

	if ( m_ptdBaseTexture == NULL )
	{
		return FALSE;
	}

	m_fTexWidth		= m_ptdBaseTexture->GetPixWidth();
	m_fTexHeight	= m_ptdBaseTexture->GetPixHeight();
	
	m_rtCurrent.SetUV( 0, 0, m_fTexWidth, m_fTexHeight, m_fTexWidth, m_fTexHeight );

	return TRUE;
}