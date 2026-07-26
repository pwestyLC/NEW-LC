#include "stdh.h"

// ��� ����. [12/1/2009 rumist]
#include <Engine/GameState.h>
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UICreateChar.h>
#include <Engine/Ska/Render.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Sound/SoundLibrary.h>
#include <Engine/Base/KeyNames.h>


// connie [2009/7/21] - login2
#ifdef CHAR_EX_ROGUE	//2012/01/08 jeil EX������ �߰� ���� ���� 

	#ifdef CHAR_EX_MAGE
		#define MAXJOB			(9)
	#else
		#define MAXJOB			(8)
	#endif
	
#else

	#ifdef CHAR_EX_MAGE
		#define MAXJOB			(8)
	#else
		#define MAXJOB			(7)
	#endif
	
#endif

extern INDEX g_iCountry;

FLOAT g_CharacterAngle[MAXJOB];

static int _aiMarkerEntities[TOTAL_JOB] =
{

	43773,		// Titan
	43774,		// Knight
	43775,		// Healer
	43776,		// Mage	
	43777,		// Rogue	
	43778,		// Sorcerer
	43779,		// KnightShadow

#ifdef CHAR_EX_ROGUE
	43835,		// [2012/08/27 : Sora] EX�α� �߰�
#endif
#ifdef CHAR_EX_MAGE
	43841,			// 2012/01/08 jeil EX������ ���� �߰� ������ �ǹ��ϴ��� �߸��� ���߿� �߰� ���� -> ���������� �����Ͱ��� ���� ���� ���� 
#endif
};

static int _aiBasicWearing[TOTAL_JOB][6] =
{
	{			// TITAN
		2,		// ����
		12,		// Į
		3,		// ����
		-1,		// ����
		4,		// �尩
		8,		// ����		
	},
	{			// KNIGHT
		34,		// ����
		48,		// Į
		38,		// ����
		49,		// ����
		39,		// �尩
		41,		// ����
	},
	{			// HEALER
		26,		// ����
		50,		// Ȱ
		28,		// ����
		-1,		// ����
		30,		// �尩
		32,		// ����		
	},
	{			// MAGE
		266,	// ����
		356,	// Į
		18,		// ����
		-1,		// ����
		22,		// �尩
		20,		// ����				
	},
	{			// ROGUE
		524,	// ����
		528,	// Į
		525,	// ����
		-1,		// ����
		527,	// �尩
		526,	// ����
	},
	{			// SORCERER
		1000,	// ����
		976,	// Į
		1010,	// ����
		-1,	// ����
		1020,	// �尩
		1030,	// ����
	},
	{			//KnightShadow
		4487,	//����
		4474,	//Į 
		4500,	//����
		-1,		//����
		4513,	//�尩 
		4526,	//����		
	},
#ifdef CHAR_EX_ROGUE
	{			// EX_ROGUE	// [2012/08/27 : Sora] EX�α� �߰�
		9209,	// ����
		528,	// Į
		9210,	// ����
		-1,		// ����
		9211,	// �尩
		9212,	// ����
	},
#endif
#ifdef CHAR_EX_MAGE	//2013/01/08 jeil EX������ �߰� ������ �ǹ��ϴ��� ���� ���߿� �߰� ���� �ʿ� -> ��ȹ������ �������� �ִ´� ������ ��� �߰�? -> �ɸ��� ����â�� �ɸ��Ͱ� �԰� �ִ� ��� �����ִ� ��  
	{
		9343,	// ����
		356,	// Į
		9344,	// ����
		-1,		// ����
		9345,	// �尩
		9346,	// ����
	},
#endif
};


// Maximum size of character information
static	int	_iMaxCharInfoChar = 0;

#define MIN_NAME_LEN	(4)
#define MAX_NAME_LEN	(16)

// ----------------------------------------------------------------------------
// Name : CUICreateChar()
// Desc : Constructor
// ----------------------------------------------------------------------------
CUICreateChar::CUICreateChar() :
m_iSelectedJob(0),
//m_pCurChar(NULL),
m_fZDelta(0.0f),
m_fRotDelta(0.0f),
m_sbSelectedHair(0),
m_sbSelectedFace(0),
m_iSelectedColor(0),
m_nCurInfoLines(0),
m_bAutoRotate(FALSE),
m_pWorld(NULL),
m_bIsShowMessageInfo(FALSE),
m_ptdMsgTexture(NULL)
{
}

// ----------------------------------------------------------------------------
// Name : ~CUICreateChar()
// Desc : Destructor
// ----------------------------------------------------------------------------
CUICreateChar::~CUICreateChar()
{
	STOCK_RELEASE(m_ptdMsgTexture);
}

// ----------------------------------------------------------------------------
// Name : Create()
// Desc :
// ----------------------------------------------------------------------------
void CUICreateChar::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight )
{
	CUIWindow::Create(pParentWnd, nX, nY, nWidth, nHeight);

	_iMaxCharInfoChar = MAX_CHARINFO_CHAR_WIDTH / ( _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing() );

	// Create creating character texture
	m_ptdBaseTexture = CreateTexture( CTString( "Data\\Interface\\CreateCharacter.tex" ) );
	FLOAT	fTexWidth	= m_ptdBaseTexture->GetPixWidth();
	FLOAT	fTexHeight	= m_ptdBaseTexture->GetPixHeight();

	// UV Coordinate of each part
	m_rtCharInfoTop.SetUV( 0, 0, 255, 386, fTexWidth, fTexHeight );
	m_rtCharInfoBottom.SetUV( 0, 390, 255, 393, fTexWidth, fTexHeight );

	// OK Button(Create character)
	m_btnOK.Create( this, _S( 138, "����" ), 0, 0, 63, 21 );
	m_btnOK.SetUV( UBS_IDLE, 0, 397, 63, 418, fTexWidth, fTexHeight );
	m_btnOK.SetUV( UBS_CLICK, 66, 397, 129, 418, fTexWidth, fTexHeight );
	m_btnOK.CopyUV( UBS_IDLE, UBS_ON ); 
	m_btnOK.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Back Button
	m_btnCancel.Create( this, _S( 139, "���" ), 0, 0, 63, 21 );
	m_btnCancel.SetUV( UBS_IDLE, 0, 397, 63, 418, fTexWidth, fTexHeight );
	m_btnCancel.SetUV( UBS_CLICK, 66, 397, 129, 418, fTexWidth, fTexHeight );
	m_btnCancel.CopyUV( UBS_IDLE, UBS_ON );
	m_btnCancel.CopyUV( UBS_IDLE, UBS_DISABLE );

	// ZoomIn Button
	m_btnZoomIn.Create( this, CTString( "" ), 0, 0, 38, 37 );
	m_btnZoomIn.SetUV( UBS_IDLE, 151, 418, 189, 455, fTexWidth, fTexHeight );
	m_btnZoomIn.SetUV( UBS_CLICK, 151, 418, 189, 455, fTexWidth, fTexHeight );
	m_btnZoomIn.CopyUV( UBS_IDLE, UBS_ON );
	m_btnZoomIn.CopyUV( UBS_IDLE, UBS_DISABLE );

	// ZoomOut Button
	m_btnZoomOut.Create( this, CTString( "" ), 0, 0, 38, 37 );
	m_btnZoomOut.SetUV( UBS_IDLE, 151, 464, 189, 501, fTexWidth, fTexHeight );
	m_btnZoomOut.SetUV( UBS_CLICK, 151, 464, 189, 501, fTexWidth, fTexHeight );
	m_btnZoomOut.CopyUV( UBS_IDLE, UBS_ON );
	m_btnZoomOut.CopyUV( UBS_IDLE, UBS_DISABLE );

	// RotateToLeft Character Button
	m_btnRotateToLeft.Create( this, CTString( "" ), 0, 0, 38, 37 );
	m_btnRotateToLeft.SetUV( UBS_IDLE, 209, 441, 247, 478, fTexWidth, fTexHeight );
	m_btnRotateToLeft.SetUV( UBS_CLICK, 209, 441, 247, 478, fTexWidth, fTexHeight );
	m_btnRotateToLeft.CopyUV( UBS_IDLE, UBS_ON );
	m_btnRotateToLeft.CopyUV( UBS_IDLE, UBS_DISABLE );

	// RotateToRight Button
	m_btnRotateToRight.Create( this, CTString( "" ), 0, 0, 38, 37 );
	m_btnRotateToRight.SetUV( UBS_IDLE, 94, 441, 132, 478, fTexWidth, fTexHeight );
	m_btnRotateToRight.SetUV( UBS_CLICK, 94, 441, 132, 478, fTexWidth, fTexHeight );
	m_btnRotateToRight.CopyUV( UBS_IDLE, UBS_ON );
	m_btnRotateToRight.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Prev Job
	m_btnJobPrev.Create( this, CTString( "" ), 0, 0, 13, 13 );
	m_btnJobPrev.SetUV( UBS_IDLE, 0, 421, 13, 434, fTexWidth, fTexHeight );
	m_btnJobPrev.SetUV( UBS_CLICK, 0, 436, 13, 449, fTexWidth, fTexHeight );
	m_btnJobPrev.CopyUV( UBS_IDLE, UBS_ON );
	m_btnJobPrev.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Next Job
	m_btnJobNext.Create( this, CTString( "" ), 0, 0, 13, 13 );
	m_btnJobNext.SetUV( UBS_IDLE, 16, 421, 29, 434, fTexWidth, fTexHeight );
	m_btnJobNext.SetUV( UBS_CLICK, 16, 436, 29, 449, fTexWidth, fTexHeight );
	m_btnJobNext.CopyUV( UBS_IDLE, UBS_ON );
	m_btnJobNext.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Prev Head
	m_btnFacePrev.Create( this, CTString( "" ), 0, 0, 13, 13 );
	m_btnFacePrev.SetUV( UBS_IDLE, 0, 421, 13, 434, fTexWidth, fTexHeight );
	m_btnFacePrev.SetUV( UBS_CLICK, 0, 436, 13, 449, fTexWidth, fTexHeight );
	m_btnFacePrev.CopyUV( UBS_IDLE, UBS_ON );
	m_btnFacePrev.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Next Head
	m_btnFaceNext.Create( this, CTString( "" ), 0, 0, 13, 13 );
	m_btnFaceNext.SetUV( UBS_IDLE, 16, 421, 29, 434, fTexWidth, fTexHeight );
	m_btnFaceNext.SetUV( UBS_CLICK, 16, 436, 29, 449, fTexWidth, fTexHeight );
	m_btnFaceNext.CopyUV( UBS_IDLE, UBS_ON );
	m_btnFaceNext.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Prev Hair
	m_btnHairPrev.Create( this, CTString( "" ), 0, 0, 13, 13 );
	m_btnHairPrev.SetUV( UBS_IDLE, 0, 421, 13, 434, fTexWidth, fTexHeight );
	m_btnHairPrev.SetUV( UBS_CLICK, 0, 436, 13, 449, fTexWidth, fTexHeight );
	m_btnHairPrev.CopyUV( UBS_IDLE, UBS_ON );
	m_btnHairPrev.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Next Hair
	m_btnHairNext.Create( this, CTString( "" ), 0, 0, 13, 13 );
	m_btnHairNext.SetUV( UBS_IDLE, 16, 421, 29, 434, fTexWidth, fTexHeight );
	m_btnHairNext.SetUV( UBS_CLICK, 16, 436, 29, 449, fTexWidth, fTexHeight );
	m_btnHairNext.CopyUV( UBS_IDLE, UBS_ON );
	m_btnHairNext.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Prev Face
	m_btnHeadPrev.Create( this, CTString( "" ), 0, 0, 13, 13 );
	m_btnHeadPrev.SetUV( UBS_IDLE, 0, 421, 13, 434, fTexWidth, fTexHeight );
	m_btnHeadPrev.SetUV( UBS_CLICK, 0, 436, 13, 449, fTexWidth, fTexHeight );
	m_btnHeadPrev.CopyUV( UBS_IDLE, UBS_ON );
	m_btnHeadPrev.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Next Face
	m_btnHeadNext.Create( this, CTString( "" ), 0, 0, 13, 13 );
	m_btnHeadNext.SetUV( UBS_IDLE, 16, 421, 29, 434, fTexWidth, fTexHeight );
	m_btnHeadNext.SetUV( UBS_CLICK, 16, 436, 29, 449, fTexWidth, fTexHeight );
	m_btnHeadNext.CopyUV( UBS_IDLE, UBS_ON );
	m_btnHeadNext.CopyUV( UBS_IDLE, UBS_DISABLE );

	// Character name edit box
	m_ebCharName.Create( this, 0, 0, 88, 13, MAX_NAME_LEN );
	m_ebCharName.SetReadingWindowUV( 34, 423, 51, 439, fTexWidth, fTexHeight );
	m_ebCharName.SetCandidateUV( 34, 423, 51, 439, fTexWidth, fTexHeight );
	m_ebCharName.SetFocus( TRUE );
	// [2011/11/02 : Sora] Ŀ�� �̵� �Ұ��÷���
	m_ebCharName.SetCursorMove( FALSE );

	// Description of character
	m_astrDescription[0] = _S( 129, " �Ѻ��⿡�� �ټ� ��ġ ū ���ó�� ���� �� ������, �Ѹ�����δ� ����� �� ���� ������ ��û�� ����, ü�°� �Բ� ���� ��Ȳ�� ���� ����� �Ǵܷ±��� ���ϰ� �ִ� Ÿ���� ����." );
	m_astrDescription[1] = _S( 130, "�ڽ��� ���� �⸣�� ��ü�� �ܷ��ϴ� ���� ���� ��ǥ�� ����� ������ ����� �Դٰ��� �Ÿ��� ������ �ְ��� �ܷ���Ҷ� ����� ���Ӿ��� ������ ���� ��ư��� ���� ������." );
	m_astrDescription[2] = _S( 131, " ���� ���� ��ô� �������� ���� �ܼ��� �������� ������ ������ ȥ���� �ô븦 ��ư��� ���ؼ����� �ƴ� �ڽ��� ������ ������ ����� ���� ��Ű�� ���� ��� �ܷ��ϴ� ����." );
	m_astrDescription[3] = _S( 132, "�ڽ��� ������ �ֺ��� ������� ��Ȳ�� ������ ��ȣ�ϸ鼭 �ο�� ������ ����ϱ⿡ ���� ��� �̻󰡴� �پ��� ������� ���ϰ� ������ �̸� Ȱ���Ͽ� ������ �׻� �¸��� �̲���." );
	m_astrDescription[4] = _S( 133, " ������ ���� �̿��Ͽ� �پ��� ȸ��, ġ���� ���õ� ��ȭ�� ������ ����ϴ� ���� Ư���� ���̿��� ������ ���� �� ��ó�� ���� ����� �ڿ��� ġ���ϴ� ������ ������ �ִ�." );
	m_astrDescription[5] = _S( 134, "�������� �������� �ʴ� �׵��� �ַ� Ȱ�� ����Ͽ� ���Ÿ��κ��� ������ �����ϴµ� �ٶ��� ���ɿ��� ������ �ޱ� �������� ���� ���õ� �ü��� ���� �ʴ� �������� ���Ѵ�." );
	m_astrDescription[6] = _S( 449, "������ ��ȣ�� �ް� �ִ� ������� �޸� �ڽ� �������� ��¿� ���� ������ ���Ŀ� ���� ������ �帧�� �����ϰ� �̸� �����Ͽ� �����Ӱ� ����ϴ� �ڵ��� �̵� �������̴�. " );
	m_astrDescription[7] = _S( 450, "�������� ������ �ڶ��ϴ� ���� ������ ��븦 ȥ����Ű�� ���� ������ �� Ư��� ����ϴ� �������� �׿��� �����ϴ� ��븦 ����, �����ϴµ� �� ���� �Ƴ��� �ʰ� ����Ѵ�. " );
	m_astrDescription[8] = _S( 1025, "�������� �������� �ʰ� �ٶ����ٵ� �����Ӱ� ��ư��� ����. ���� ������ �ູ�� �޾� �¾ �̵��� �ſ� ���� ����� �پ �þ߸� ���ϸ� �׿� �Բ� �����й��� �����İ� ������ �����ϴ� ������ Ÿ�����ٰ� ��������." );		
	m_astrDescription[9] = _S( 1026, "���� ����� �þ߸� Ȱ���� �� �ִ� �ܰ˰� ������ �ַ� ����ϴ� �α״� ���� ü���� Ŀ���ϱ� ���� ���� �ϳ��ϳ��� ���� ������ ��� ġ������ �����ų� ���Ÿ����� ���� ���� �Ʊ��� ����Ʈ�ϴ� �Ϳ� �ַ��Ѵ�." );	
	m_astrDescription[10] = _S( 1027, "ġ���� ����ϴ� ���̿��� ������ �޸� ���̿��� �Ҽ����� �ڿ��� ��ó �����ų� �׵��� ������ ���� �ڿ� ���� ������ �������� ���縦 ���ϴ� ������ �ð� �ִ�." );	
	m_astrDescription[11] = _S( 1028, "�ڿ� ���� ������ �������� ���·� ��ȯ���� ����ϴ� �������� �޸� �Ҽ����� 4�� ������ ���� ���� ������ 4�� �Ӽ��� ������ ����Ѵ�." );
	m_astrDescription[12] = _S( 4698, "������ ������ ���� ���ݸ������� ���� ���ظ� ���� �����ϴ� ������ �������̴�. ���� ������ �迭���� ���� ������� ���ϰ� ������, ���� ������ �Բ� ������ ���ָ� ���� �ɾ�����⵵ �Ѵ�.");
	m_astrDescription[13] = _S( 4699, "�������� ����Ʈ������� ���� ��ȥ�� �����ϰ� ������ ��ȥ�� �̿��� ������ ���� ������ ����Ѵ�. ��Ʈī������ ù��° ���� Ŭ������ 90���� �̻� ĳ���͸� ������ ������ ���ؼ� ������ �����ϴ�.");
#ifdef CHAR_EX_ROGUE
	m_astrDescription[14] = _S( 1025, "�������� �������� �ʰ� �ٶ����ٵ� �����Ӱ� ��ư��� ����. ���� ������ �ູ�� �޾� �¾ �̵��� �ſ� ���� ����� �پ �þ߸� ���ϸ� �׿� �Բ� �����й��� �����İ� ������ �����ϴ� ������ Ÿ�����ٰ� ��������." );		// [2012/08/27 : Sora] EX�α� �߰�
	m_astrDescription[15] = _S( 5733, "�α� �߿��� ����� ����� ��Ե� Ư���� �α׵��� ����� ���� �̿��Ͽ� ������ ���ظ� �����ų� �Ʊ��� ��ȣ�� �� ������, �پ��� ������ ��ġ�Ͽ� ���� ������Ű�� ���� ������ ��ģ��." );	// [2012/08/27 : Sora] EX�α� �߰�
#endif
#ifdef CHAR_EX_MAGE
		//2013/01/08 jeil EX������ �߰� ��Ʈ�� ������ �߰� ���� �ʿ� 
	m_astrDescription[16] = _S( 449, "������ ��ȣ�� �ް� �ִ� ������� �޸� �ڽ� �������� ��¿� ���� ������ ���Ŀ� ���� ������ �帧�� �����ϰ� �̸� �����Ͽ� �����Ӱ� ����ϴ� �ڵ��� �̵� �������̴�. " );
	m_astrDescription[17] = _S( 5821, "��ũ�������� �������� �ٸ��� ������ ������ ����ϴ� �鸶�����, �й����� ���������� ������ �����Ѵ�. ���� �⺻���̸鼭�� �������� �Ӽ� ������ �����Ӱ� �ٷ� �� ������ �����ϴ� ��븦 ����, �����ϴµ��� ���� �������� ����." );

#endif

	m_ptdMsgTexture = CreateTexture( CTString( "Data\\Interface\\TopUI.tex" ) );
	m_rcMessageInfo.SetRect( 20, 40, 215, 102 );
	m_bxNoticeMsg.SetBoxUV(m_ptdMsgTexture,7,WRect(239,253,335,269));

	m_msgNCText.SetRenderRect( 20, 45, 187, 62 );
	m_msgNCText.AddString( _S(4794, "����Ʈ������ ĳ���͸� ������ �� �ִ� ������ �����Ͽ����ϴ�. ����Ʈ������ ĳ���͸� �����Ͽ� �����Ͻʽÿ�." ) );
}

// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUICreateChar::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	m_rcCharInfo.SetRect( pixMaxI - CREATECHAR_INFO_WIDTH, pixMinJ, pixMaxI, pixMaxJ );

	int	nX = ( pixMaxI + pixMinI - CREATECHAR_CONTROL_WIDTH ) / 2;
	int	nY = pixMaxJ - CREATECHAR_CONTROL_HEIGHT - 5;
	m_rcCharControl.SetRect( nX, nY, nX + CREATECHAR_CONTROL_WIDTH, nY + CREATECHAR_CONTROL_HEIGHT );

	// OK & cancel button
	m_btnOK.SetPos( pixMaxI - 138, 360 );
	m_btnCancel.SetPos( pixMaxI - 72, 360 );

	// Job button
	m_btnJobPrev.SetPos( pixMaxI - 172, 264 );
	m_btnJobNext.SetPos( pixMaxI - 89, 264 );

	// Head button
	m_btnFacePrev.SetPos( pixMaxI - 172, 283 );
	m_btnFaceNext.SetPos( pixMaxI - 89, 283 );

	// Hair button
	m_btnHairPrev.SetPos( pixMaxI - 172, 303 );
	m_btnHairNext.SetPos( pixMaxI - 89, 303 );

	// Face button
	m_btnHeadPrev.SetPos( pixMaxI - 172, 323 );
	m_btnHeadNext.SetPos( pixMaxI - 89, 323 );

	// Character name edit box
	m_ebCharName.SetPos( pixMaxI - 168, 229 );

	// ZoomIn Button
	m_btnZoomIn.SetPos( m_rcCharControl.Left + 57, m_rcCharControl.Top );

	// ZoomOut Button
	m_btnZoomOut.SetPos( m_rcCharControl.Left + 57, m_rcCharControl.Top + 46 );

	// RotateToLeft Character Button
	m_btnRotateToLeft.SetPos( m_rcCharControl.Left, m_rcCharControl.Top + 23 );

	// RotateToRight Button
	m_btnRotateToRight.SetPos( m_rcCharControl.Left + 115, m_rcCharControl.Top + 23 );
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUICreateChar::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CUICreateChar::Reset()
{	
	Lock(FALSE);
	m_iSelectedJob	= 0;	
	m_fZDelta		= 0.0f;
	m_fRotDelta		= 0.0f;

	m_ebCharName.ResetString();

	// ī�޶� ����, ĳ���� ��ġ ����.	
	for(int i = 0; i < MAXJOB; ++i)
	{
		const int iMarker			= _aiMarkerEntities[i];
		CEntity *penMarker			= m_pWorld->EntityFromID(iMarker);	
		penMarker->SetSkaModel(JobInfo().GetFileName(i));
		g_CharacterAngle[i] = penMarker->GetPlacement().pl_OrientationAngle(1);
		
		CModelInstance* pMI	= penMarker->GetModelInstance();
		if(pMI)
		{		
			INDEX idAttackIdle = ska_GetIDFromStringTable( JobInfo().GetAnimationName( i, ANIM_IDLE ) );
			pMI->AddAnimation(idAttackIdle, AN_LOOPING|AN_NORESTART|AN_CLEAR, 1, 0);
		}
	}
	
#if defined(G_BRAZIL) 
		CharWearing();
#endif
	ChangeSelJob();

	m_bIsShowMessageInfo = _pGameState->IsCreatableNightShadow();
}

// ----------------------------------------------------------------------------
// Name : Render()
// Desc :
// ----------------------------------------------------------------------------
void CUICreateChar::Render()
{	
	extern INDEX	sam_bWideScreen;
	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	// Set create character textire
	pDrawPort->InitTextureData( m_ptdBaseTexture );
	
	// Character information
	// Top
	pDrawPort->AddTexture( m_rcCharInfo.Left, m_rcCharInfo.Top,
										m_rcCharInfo.Right, m_rcCharInfo.Top + CREATECHAR_INFO_HEIGHT,
										m_rtCharInfoTop.U0, m_rtCharInfoTop.V0,
										m_rtCharInfoTop.U1, m_rtCharInfoTop.V1,
										0xFFFFFFFF );
	// Bottom
	pDrawPort->AddTexture( m_rcCharInfo.Left, m_rcCharInfo.Top + CREATECHAR_INFO_HEIGHT,
										m_rcCharInfo.Right, m_rcCharInfo.Bottom,
										m_rtCharInfoBottom.U0, m_rtCharInfoBottom.V0,
										m_rtCharInfoBottom.U1, m_rtCharInfoBottom.V1,
										0xFFFFFFFF );

	// Character name input box
	m_ebCharName.Render();

	// Job button
	m_btnJobPrev.Render();
	m_btnJobNext.Render();

	// Head button
	m_btnFacePrev.Render();
	m_btnFaceNext.Render();

	// Hair button
	m_btnHairPrev.Render();
	m_btnHairNext.Render();

	// Face button
	//m_btnHeadPrev.Render();
	//m_btnHeadNext.Render();

	// OK button
	m_btnOK.Render();

	// Cancel button
	m_btnCancel.Render();

	// Character control
	/*
	// Zoom in button
	m_btnZoomIn.Render();

	// Zoom out button
	m_btnZoomOut.Render();

	// Rotate to left button
	m_btnRotateToLeft.Render();

	// Rotate to right
	m_btnRotateToRight.Render();
	*/

	// Render all elements
	pDrawPort->FlushRenderingQueue();

	// Render character information
	int	nX = m_rcCharInfo.Left + CREATECHAR_DESC_SX;
	int	nY = m_rcCharInfo.Top + CREATECHAR_DESC_SY;
	for( int iInfo = 0; iInfo < m_nCurInfoLines; iInfo++ )
	{
		pDrawPort->PutTextEx( m_strCharInfo[iInfo], nX, nY, m_colCharInfo[iInfo] );
		nY += _pUIFontTexMgr->GetLineHeight();
	}
	
	// Prepare Rendering Text
	nX = m_rcCharInfo.Left;
	nY = m_rcCharInfo.Top;
	pDrawPort->PutTextEx( _S( 140, "ĳ���� ����" ),
										nX + CREATECHAR_TITLE_OFFSETX, nY + CREATECHAR_TITLE_OFFSETY );
	pDrawPort->PutTextExRX( _S( 71, "�̸�" ),
											nX + CREATECHAR_NAME_RX, nY + CREATECHAR_NAME_SY );
	pDrawPort->PutTextExRX( _S( 141, "����" ),
											nX + CREATECHAR_NAME_RX, nY + CREATECHAR_JOB_SY );
	pDrawPort->PutTextExRX( _S( 144, "��" ),		// ��
											nX + CREATECHAR_NAME_RX, nY + CREATECHAR_FACE_SY );
	pDrawPort->PutTextExRX( _S( 143, "���" ),		// ���
											nX + CREATECHAR_NAME_RX, nY + CREATECHAR_HAIR_SY );
	//pDrawPort->PutTextExRX( _S( 142, "�Ӹ�" ),		// �Ӹ�
	//										nX + CREATECHAR_NAME_RX, nY + CREATECHAR_HEAD_SY );

	// Print Job
	pDrawPort->PutTextExCX( JobInfo().GetName(m_iSelectedJob),
											nX + CREATECHAR_JOB_MAIN_CY, nY + CREATECHAR_JOB_SY );
	// Print Face
	CTString strTemp;
	strTemp.PrintF("%d", m_sbSelectedFace + 1);
	pDrawPort->PutTextExCX( strTemp,
											nX + CREATECHAR_JOB_MAIN_CY, nY + CREATECHAR_FACE_SY );

	strTemp.PrintF("%d", m_sbSelectedHair + 1);
	// Print Hair
	pDrawPort->PutTextExCX( strTemp,
											nX + CREATECHAR_JOB_MAIN_CY, nY + CREATECHAR_HAIR_SY );

	// Print Head
	//pDrawPort->PutTextExCX( CTString( "1" ),
	//										nX + CREATECHAR_JOB_MAIN_CY, nY + CREATECHAR_FACE_SY );

	// Flush all render text queue
	pDrawPort->EndTextEx();

	// Reading window
	if( m_ebCharName.DoesShowReadingWindow() )
	{
		// Set texture
		pDrawPort->InitTextureData( m_ptdBaseTexture );

		// Reading window
		m_ebCharName.RenderReadingWindow();

		// Render all elements
		pDrawPort->FlushRenderingQueue();

		// Flush all render text queue
		pDrawPort->EndTextEx();
	}

	// show night shadow message [11/6/2009 rumist]
	if( m_bIsShowMessageInfo )
	{
		pDrawPort->InitTextureData( m_ptdMsgTexture );
		m_bxNoticeMsg.SetBoxPos(m_rcMessageInfo);
		m_bxNoticeMsg.Render();
		
		// Render all elements
		pDrawPort->FlushRenderingQueue();
		
		m_msgNCText.SetRenderPos( m_rcMessageInfo.Left, m_rcMessageInfo.Top );
		m_msgNCText.Render();
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//
//-----------------------------------------------------------------------------
void CUICreateChar::PressOKBtn()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// Get input string
	if( m_ebCharName.GetString() )
	{
		m_strCharName = m_ebCharName.GetString();	
		
		// ���� üũ.		
		for(const char *chr = m_strCharName.str_String; *chr != 0; chr++)
		{
			if( (*chr) == ' ' || (*chr) == '\t' || (*chr) == '\n' || (*chr) == '\r' || 
				(*chr) == '%' || (*chr) == '#' || (*chr) == '&' || (*chr) == '?' || (*chr) == '+' || (*chr) == '=' ||
				(g_iCountry == HONGKONG && !CheckCharacterHK(chr))) // ȫ�� Ư�����ڴ� �Է� �Ұ�ó��
			{
				pUIManager->CloseMessageBox(MSGCMD_CREATE_ERROR);
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo( _S( 145, "ĳ���� ���� ����" ), UMBS_OK,
					UI_CREATE_CHAR, MSGCMD_CREATE_ERROR );
				CTString	strMessage = _S( 146, "ĳ���͸��� ������ �� �� �����ϴ�." );
				MsgBoxInfo.AddString( strMessage );
				pUIManager->CreateMessageBox( MsgBoxInfo );
				
				m_ebCharName.ResetString();
				return;
			}
#if defined(G_RUSSIA)
				// [100510: selo] LC-RU-P20100504-006
				// http://en.wikipedia.org/wiki/Windows-1251 �����Ͽ� ����
				if( !((*chr) >= 48 && (*chr) <= 57 )
					&& !((*chr) >= -64 && (*chr) <= -1)
					&& !((*chr) == -88)
					&& !((*chr) == -72)	)
				{
					pUIManager->CloseMessageBox(MSGCMD_CREATE_ERROR);
					CUIMsgBox_Info	MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo( _S( 145, "ĳ���� ���� ����" ), UMBS_OK,
						UI_CREATE_CHAR, MSGCMD_CREATE_ERROR );
					CTString	strMessage = _S(2980, "���̵�� ������ ���ڸ� ���˴ϴ�." );
					MsgBoxInfo.AddString( strMessage );
					pUIManager->CreateMessageBox( MsgBoxInfo );
					
					m_ebCharName.ResetString();
					return;
				}

#elif !defined(G_HONGKONG) && !defined(G_EUROPE2) && !defined(G_KOR) && !defined(G_JAPAN) && !defined(G_THAI)
			if( !((*chr) >= 48 && (*chr) <=57)  //! 0 ~ 9
				&& !((*chr) >= 65 && (*chr) <=90) // ! A ~ Z 
				&& !((*chr) >= 97 && (*chr) <=122) // ! a ~ z 
				)
			{
				pUIManager->CloseMessageBox(MSGCMD_CREATE_ERROR);
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo( _S( 145, "ĳ���� ���� ����" ), UMBS_OK,
					UI_CREATE_CHAR, MSGCMD_CREATE_ERROR );
				CTString	strMessage = _S(2980, "���̵�� ������ ���ڸ� ���˴ϴ�." );
				MsgBoxInfo.AddString( strMessage );
				pUIManager->CreateMessageBox( MsgBoxInfo );
				
				m_ebCharName.ResetString();
				return;
			}
#endif

		}
	}
//#define RESTRICT_SOUND 	

	_pSound->Mute();
	CreateCharacter();

#ifdef RESTRICT_SOUND
	extern BOOL _bNTKernel;
	//if( _bNTKernel )
		_pSound->UpdateSounds();
	#endif
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *pMsg - 
// Output : WMSG_RESULT
//-----------------------------------------------------------------------------
WMSG_RESULT CUICreateChar::KeyMessage( MSG *pMsg )
{
	// If character creation is not focused
	if( !IsFocused() )
		return WMSG_FAIL;

	if( pMsg->wParam == VK_RETURN )
	{	
		PressOKBtn();
		return WMSG_SUCCESS;
	}
	
	if( m_ebCharName.KeyMessage( pMsg ) != WMSG_FAIL )
	{
		return WMSG_SUCCESS;
	}
	
/*	switch(pMsg->wParam)
	{
	case VK_LEFT:
		{
			CEntity *Character = m_pWorld->EntityFromID(_aiMarkerEntities[m_iSelectedJob]);
			FLOAT tmp = Character->GetPlacement().pl_OrientationAngle(1);
			Character->en_plPlacement.pl_OrientationAngle(1) += 6.0f;
			return WMSG_SUCCESS;
		}
		break;
	case VK_RIGHT:
		{
			CEntity *Character = m_pWorld->EntityFromID(_aiMarkerEntities[m_iSelectedJob]);
			FLOAT tmp = Character->GetPlacement().pl_OrientationAngle(1);
			Character->en_plPlacement.pl_OrientationAngle(1) -= 6.0f;
			return WMSG_SUCCESS;
		}
		break;
	}
*/
	return WMSG_FAIL;
}

void CUICreateChar::SetCharaterAngle(FLOAT f_inL, FLOAT f_inR)
{
	if (CUIManager::getSingleton()->GetUIGameState() == eSTAGE_CREATECHAR)
	{
		CEntity *Character = m_pWorld->EntityFromID(_aiMarkerEntities[m_iSelectedJob]);
		Character->en_plPlacement.pl_OrientationAngle(1) -= f_inL;
		Character->en_plPlacement.pl_OrientationAngle(1) += f_inR;
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *pMsg - 
// Output : WMSG_RESULT
//-----------------------------------------------------------------------------
WMSG_RESULT CUICreateChar::IMEMessage( MSG *pMsg )
{

	// �̱�ȯ ���� ���� (11.20) : IME ��ƾ ����
	return m_ebCharName.IMEMessage( pMsg );
	// �̱�ȯ ���� ��
	
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *pMsg - 
// Output : WMSG_RESULT
//-----------------------------------------------------------------------------
WMSG_RESULT CUICreateChar::CharMessage( MSG *pMsg )
{
	// [2012/06/08 : Sora] ITS 9144 �±� ��û���� ctrl key ��Ȱ��ȭ
#ifdef G_THAI
	extern UBYTE	_abKeysPressed[256];
	if( _abKeysPressed[KID_LCONTROL] || _abKeysPressed[KID_RCONTROL] )
	{
		return WMSG_FAIL;
	}
#endif
	if( m_ebCharName.CharMessage( pMsg ) != WMSG_FAIL )
	{
		return WMSG_SUCCESS;
	}

	return WMSG_FAIL;
}

// ----------------------------------------------------------------------------
// Name : MouseMessage()
// Desc :
// ----------------------------------------------------------------------------
WMSG_RESULT CUICreateChar::MouseMessage( MSG *pMsg )
{
	WMSG_RESULT	wmsgResult;

	// Mouse point
	int	nX = LOWORD( pMsg->lParam );
	int	nY = HIWORD( pMsg->lParam );
	
	// Mouse message
	switch( pMsg->message )
	{
	case WM_MOUSEMOVE:
		{
			if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnCancel.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnJobPrev.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnJobNext.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnFacePrev.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnFaceNext.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnHairPrev.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnHairNext.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnHeadPrev.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnHeadNext.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			/*else if( m_btnZoomIn.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnZoomOut.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnRotateToLeft.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnRotateToRight.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;*/
		}
		break;
	case WM_LBUTTONDOWN:
		{
			if( IsInsideRect( nX, nY, m_rcCharInfo ) )
			{
				if( m_ebCharName.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				else if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				else if( m_btnCancel.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				else if( m_btnJobPrev.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				else if( m_btnJobNext.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				else if( m_btnFacePrev.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				else if( m_btnFaceNext.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				else if( m_btnHairPrev.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				else if( m_btnHairNext.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				else if( m_btnHeadPrev.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}
				else if( m_btnHeadNext.MouseMessage( pMsg ) != WMSG_FAIL )
				{
					// Nothing
				}

				CUIManager::getSingleton()->RearrangeOrder( UI_CREATE_CHAR, TRUE );
				return WMSG_SUCCESS;
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			if( IsInsideRect( nX, nY, m_rcCharInfo ) )
			{
				if( ( wmsgResult = m_btnOK.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						PressOKBtn();
					}
					return WMSG_SUCCESS;
				}
				else if( ( wmsgResult = m_btnCancel.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						CUIManager::getSingleton()->SetUIGameState(eSTAGE_SELCHAR);
						_pGameState->BackToSelChar();
					}
				}			
				else if( ( wmsgResult = m_btnJobPrev.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{	
					if( wmsgResult == WMSG_COMMAND )
					{
						CEntity *penMarker = m_pWorld->EntityFromID(_aiMarkerEntities[m_iSelectedJob]);
						penMarker->en_plPlacement.pl_OrientationAngle(1) = g_CharacterAngle[m_iSelectedJob];
						m_iSelectedJob--;
						//_pSound->Mute();						
						ChangeSelJob();
						//_pSound->UpdateSounds();
						_pGameState->SetCameraByJob(m_iSelectedJob);
					}
				}
				else if( ( wmsgResult = m_btnJobNext.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						CEntity *penMarker = m_pWorld->EntityFromID(_aiMarkerEntities[m_iSelectedJob]);
						penMarker->en_plPlacement.pl_OrientationAngle(1) = g_CharacterAngle[m_iSelectedJob];
						m_iSelectedJob++;
						//_pSound->Mute();
						ChangeSelJob();
						//_pSound->UpdateSounds();
						_pGameState->SetCameraByJob(m_iSelectedJob);
					}
				}
				else if( ( wmsgResult = m_btnFacePrev.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						m_sbSelectedFace--;						

						if(m_sbSelectedFace < 0) 
							m_sbSelectedFace = TOTAL_HEAD - 1;
						m_sbSelectedFace	= m_sbSelectedFace % TOTAL_HEAD;

						const int iMarker			= _aiMarkerEntities[m_iSelectedJob];
						CEntity *penMarker			= m_pWorld->EntityFromID(iMarker);	
						
						CModelInstance* pMI			= penMarker->GetModelInstance();

						((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ChangeFaceMesh(pMI, m_iSelectedJob, m_sbSelectedFace);
					}
				}
				else if( ( wmsgResult = m_btnFaceNext.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						m_sbSelectedFace++;
						
						m_sbSelectedFace	= m_sbSelectedFace % TOTAL_HEAD;

						const int iMarker			= _aiMarkerEntities[m_iSelectedJob];
						CEntity *penMarker			= m_pWorld->EntityFromID(iMarker);							
						CModelInstance* pMI			= penMarker->GetModelInstance();

						((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ChangeFaceMesh(pMI, m_iSelectedJob, m_sbSelectedFace);
					}
				}
				else if( ( wmsgResult = m_btnHairPrev.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						m_sbSelectedHair--;

						if(m_sbSelectedHair < 0) 
							m_sbSelectedHair = TOTAL_HAIR - 1;
						m_sbSelectedHair	= m_sbSelectedHair % TOTAL_HAIR;

						const int iMarker			= _aiMarkerEntities[m_iSelectedJob];
						CEntity *penMarker			= m_pWorld->EntityFromID(iMarker);							
						CModelInstance* pMI			= penMarker->GetModelInstance();
						((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ChangeHairMesh(pMI, m_iSelectedJob, m_sbSelectedHair);
						//((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ChangeHairTexture(pMI, m_iSelectedJob, m_sbSelectedHair);
					}
				}
				else if( ( wmsgResult = m_btnHairNext.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						m_sbSelectedHair++;						
						
						m_sbSelectedHair	= m_sbSelectedHair % TOTAL_HAIR;

						const int iMarker			= _aiMarkerEntities[m_iSelectedJob];
						CEntity *penMarker			= m_pWorld->EntityFromID(iMarker);							
						CModelInstance* pMI			= penMarker->GetModelInstance();
						((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ChangeHairMesh(pMI, m_iSelectedJob, m_sbSelectedHair);
						//((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ChangeHairTexture(pMI, m_iSelectedJob, m_sbSelectedHair);
					}
				}
				else if( ( wmsgResult = m_btnHeadPrev.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
					}
				}
				else if( ( wmsgResult = m_btnHeadNext.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
					}
				}

				return WMSG_SUCCESS;
			}
			else if( IsInsideRect( nX, nY, m_rcCharControl ) )
			{
				if( ( wmsgResult = m_btnZoomIn.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						m_fZDelta += 0.6f;
					}
				}
				else if( ( wmsgResult = m_btnZoomOut.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						m_fZDelta -= 0.6f;
					}
				}
				else if( ( wmsgResult = m_btnRotateToLeft.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						//m_bAutoRotate = !m_bAutoRotate;
						m_fRotDelta -= 10.0f;
					}
				}
				else if( ( wmsgResult = m_btnRotateToRight.MouseMessage( pMsg ) ) != WMSG_FAIL )
				{
					if( wmsgResult == WMSG_COMMAND )
					{
						//m_bAutoRotate = !m_bAutoRotate;
						m_fRotDelta += 10.0f;
					}
				}

				return WMSG_SUCCESS;
			}
		}
		break;
	}

	return WMSG_FAIL;
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : nCommandCode - 
//			bOK - 
//			&strInput - 
//-----------------------------------------------------------------------------
void CUICreateChar::MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput )
{
}

//-----------------------------------------------------------------------------
// Purpose: ��� ���� ĳ������ �⺻ ��� ����
//-----------------------------------------------------------------------------
void CUICreateChar::CharWearing()
{
	for(int i = 0 ; i < MAXJOB; ++i)
	{
		// ī�޶� ����, ĳ���� ��ġ ����.	
		const int iMarker			= _aiMarkerEntities[i];
		CEntity *penMarker			= m_pWorld->EntityFromID(iMarker);	
		
		CModelInstance* pMI	= penMarker->GetModelInstance();
		
		// ������ ĳ���Ϳ� ��� ������ ����� ������� �ϴ� �κ�...
		// ���� ���� ���� ���� �尩 �Ź�
		if(pMI)
		{
			for(int j = 0; j < 6; ++j)
			{
				const SLONG lWear = _aiBasicWearing[i][j];
				if(lWear > 0)
				{
					CItemData* pID = _pNetwork->GetItemData(lWear);
					_pGameState->DeleteDefaultArmor(pMI, pID->GetWearingPosition(), i);
					_pGameState->WearingArmor(pMI, *pID);					
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: Prev �� Next�� ������ ���õ� ĳ���Ͱ� ����� ���.
//-----------------------------------------------------------------------------
void CUICreateChar::ChangeSelJob()
{
//������ ���� ���� Ŭ���� 2�� �۾�	08.18
	// FIXME : ��� ĳ���Ͱ� �� ������ �ּ��� Ǯ��.
	//if(m_iSelectedJob < 0) 
	//	m_iSelectedJob = TOTAL_JOB - 1;
	//m_iSelectedJob	= m_iSelectedJob % TOTAL_JOB;

	// FIXME : Ŭ���� 2���� ����Ʈ�� ������ �����ֱ� ���� �κ�.
	if(m_iSelectedJob < 0) 
		m_iSelectedJob = MAXJOB - 1;

	if(m_iSelectedJob > MAXJOB - 1)
		m_iSelectedJob = 0;
	
	m_sbSelectedHair= 0;
	m_sbSelectedFace= 0;
	m_iSelectedColor= 0;
	
//������ ���� �� Ŭ���� 2�� �۾�		08.18

	m_fRotDelta		= 0.0f;
	m_fZDelta		= 0.0f;
	if(!m_pWorld)			return;
	
	// ī�޶� ����, ĳ���� ��ġ ����.	
	const int iMarker			= _aiMarkerEntities[m_iSelectedJob];
	CEntity *penMarker			= m_pWorld->EntityFromID(iMarker);
	//penMarker->SetSkaModel(_aJobFileName[m_iSelectedJob]);

	CModelInstance* pMI	= penMarker->GetModelInstance();
	if(pMI)
	{
		//pMI->mi_iFaceMesh	= -1;
		//pMI->mi_iFaceTexture= -1;
		//pMI->mi_iHairMesh	= -1;
		//pMI->mi_iHairTexture= -1;

		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ChangeFaceMesh(pMI, m_iSelectedJob, 0);
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->ChangeHairMesh(pMI, m_iSelectedJob, 0);

		pMI->mi_iFaceMesh	= -1;
		pMI->mi_iHairMesh	= -1;

		if(_pNetwork->wo_iNumOfItem > 0)
		{
			// ������ ĳ���Ϳ� ��� ������ ����� ������� �ϴ� �κ�...
			// ���� ���� ���� ���� �尩 �Ź�
			for(int i = 0; i < 6; ++i)
			{
				const SLONG lWear = _aiBasicWearing[m_iSelectedJob][i];
				if(lWear > 0)
				{
					CItemData* pID = _pNetwork->GetItemData(lWear);
					_pGameState->DeleteDefaultArmor(pMI, pID->GetWearingPosition(), m_iSelectedJob);
					_pGameState->WearingArmor(pMI, *pID);					
				}
			}
		}

		//INDEX idWalk		= ska_GetIDFromStringTable(_afnIdleAnim[m_iSelectedJob]);
		//pMI->AddAnimation(idWalk,AN_LOOPING|AN_NORESTART|AN_CLEAR,1,0);
		// ������ ĳ���Ϳ� ���� ������ �����ݴϴ�.
		GetCharInfo();
	}	
}

//-----------------------------------------------------------------------------
// Purpose: ĳ���͸� �����մϴ�.
//-----------------------------------------------------------------------------
void CUICreateChar::CreateCharacter()
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString strMessage;

#if defined(G_MAXICO) || defined(G_BRAZIL) || defined(G_KOR)
	{
	// �̱�ȯ ���� ���� ( 11.29 ) : ĳ���͸� ����  �޼��� ó��
		
		char szBuffer[MAX_STR_LENGTH];
		strcpy ( szBuffer, m_strCharName.str_String );
	
		if( m_strCharName.Length() <= 0 )
		{
			pUIManager->CloseMessageBox(MSGCMD_CREATE_ERROR);
			CUIMsgBox_Info	MsgBoxInfo;
					
			MsgBoxInfo.SetMsgBoxInfo( _S( 145, "ĳ���� ���� ����" ), UMBS_OK,
										UI_CREATE_CHAR, MSGCMD_CREATE_ERROR );
			MsgBoxInfo.AddString( _S( 432, "ĳ���� �̸��� �Է��Ͽ� �ֽʽÿ�.\n(�ѱ� 4~8��, ���� 2~16��)" ) );
	
			pUIManager->CreateMessageBox( MsgBoxInfo );
	
			m_ebCharName.ResetString();
	
			return;
		}
		else if(m_strCharName.Length() < MIN_NAME_LEN )
		{
			pUIManager->CloseMessageBox(MSGCMD_CREATE_ERROR);
			CUIMsgBox_Info	MsgBoxInfo;
					
			MsgBoxInfo.SetMsgBoxInfo( _S( 145, "ĳ���� ���� ����" ), UMBS_OK,
										UI_CREATE_CHAR, MSGCMD_CREATE_ERROR );
			MsgBoxInfo.AddString( _S( 433, "ĳ���� �̸��� �ʹ� ª���ϴ�.\n(�ѱ� 4~8��, ���� 2~16��)" ) );
	
	
			pUIManager->CreateMessageBox( MsgBoxInfo );
	
			m_ebCharName.ResetString();
		
			return;
		}
		else if ( m_strCharName.Length() > MAX_NAME_LEN  )
		{
			pUIManager->CloseMessageBox(MSGCMD_CREATE_ERROR);
			CUIMsgBox_Info	MsgBoxInfo;
					
			MsgBoxInfo.SetMsgBoxInfo( _S( 145, "ĳ���� ���� ����" ), UMBS_OK,
										UI_CREATE_CHAR, MSGCMD_CREATE_ERROR );
			MsgBoxInfo.AddString( _S( 434, "ĳ���� �̸��� �ʹ� ��ϴ�.\n(�ѱ� 4~8��, ���� 2~16��)" ) );
	
	
			pUIManager->CreateMessageBox( MsgBoxInfo );
	
			m_ebCharName.ResetString();
		
			return;
		}
		else if( _UIFilteringCharacter.Filtering ( szBuffer ) == TRUE ) // find ...
		{
			pUIManager->CloseMessageBox(MSGCMD_CREATE_ERROR);
			CUIMsgBox_Info	MsgBoxInfo;
					
			MsgBoxInfo.SetMsgBoxInfo( _S( 145, "ĳ���� ���� ����" ), UMBS_OK,
										UI_CREATE_CHAR, MSGCMD_CREATE_ERROR );
			
			CTString	strMessage = _S( 435, "�߸��� ����[" );	
			strMessage += m_strCharName.str_String;
			strMessage += _S( 436, "]�� ���ԵǾ� �ֽ��ϴ�." );
			
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
	
			m_ebCharName.ResetString();
		
			return;
		}
		
	// �̱�ȯ ���� ��	
	}
#else

		strMessage = m_strCharName;
		if(!pUIManager->checkName(strMessage, eCHECK_TYPE_PLAYER_NAME)) return;

#endif

	if(_pNetwork->m_bSendMessage)
		return;

	_pNetwork->SendCreateCharacter( m_strCharName, m_iSelectedJob, m_sbSelectedHair + 1, m_sbSelectedFace + 1 );
	pUIManager->Lock(TRUE);
}

//-----------------------------------------------------------------------------
// Purpose: ĳ������ ������ ������.
// Input  : &strItemInfo - 
//			colItemInfo - 
//-----------------------------------------------------------------------------
void CUICreateChar::AddCharInfoString( CTString &strCharInfo, COLOR colCharInfo )
{
	if( m_nCurInfoLines >= MAX_CHARINFO_LINE )
		return;

	// Get length of string
	INDEX	nLength = strCharInfo.Length();
	if( nLength == 0 )
		return;

	// wooss 051002
#if defined(G_THAI)
	{
		int		iPos;
		// Get length of string
		INDEX	nThaiLen = FindThaiLen(strCharInfo);
		INDEX	nChatMax= (_iMaxCharInfoChar-1)*(_pUIFontTexMgr->GetFontWidth()+_pUIFontTexMgr->GetFontSpacing());
		if( nLength == 0 )
			return;
		// If length of string is less than max char
		if( nThaiLen <= nChatMax )
		{
			// Check line character
			for( iPos = 0; iPos < nLength; iPos++ )
			{
				if( strCharInfo[iPos] == '\n' || strCharInfo[iPos] == '\r' )
					break;	
			}

			// Not exist
			if( iPos == nLength )
			{
				m_strCharInfo[m_nCurInfoLines] = strCharInfo;
				m_colCharInfo[m_nCurInfoLines++] = colCharInfo;
			}
			else
			{
				// Split string
				CTString	strTemp;
				strCharInfo.Split( iPos, m_strCharInfo[m_nCurInfoLines], strTemp );
				m_colCharInfo[m_nCurInfoLines++] = colCharInfo;

				// Trim line character
				if( strTemp[0] == '\r' && strTemp[1] == '\n' )
					strTemp.TrimLeft( strTemp.Length() - 2 );
				else
					strTemp.TrimLeft( strTemp.Length() - 1 );

				AddCharInfoString( strTemp, colCharInfo );
			}
		}
		// Need multi-line
		else
		{
			// Check splitting position for 2 byte characters
			int		nSplitPos = _iMaxCharInfoChar;
			BOOL	b2ByteChar = FALSE;
			for( iPos = 0; iPos < nLength; iPos++ )
			{
				if(nChatMax < FindThaiLen(strCharInfo,0,iPos))
					break;
			}
			nSplitPos = iPos;

			// Check line character
			for( iPos = 0; iPos < nSplitPos; iPos++ )
			{
				if( strCharInfo[iPos] == '\n' || strCharInfo[iPos] == '\r' )
					break;
			}

			// Not exist
			if( iPos == nSplitPos )
			{
				// Split string
				CTString	strTemp;
				strCharInfo.Split( nSplitPos, m_strCharInfo[m_nCurInfoLines], strTemp );
				m_colCharInfo[m_nCurInfoLines++] = colCharInfo;

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

				AddCharInfoString( strTemp, colCharInfo );
			}
			else
			{
				// Split string
				CTString	strTemp;
				strCharInfo.Split( iPos, m_strCharInfo[m_nCurInfoLines], strTemp );
				m_colCharInfo[m_nCurInfoLines++] = colCharInfo;

				// Trim line character
				if( strTemp[0] == '\r' && strTemp[1] == '\n' )
					strTemp.TrimLeft( strTemp.Length() - 2 );
				else
					strTemp.TrimLeft( strTemp.Length() - 1 );

				AddCharInfoString( strTemp, colCharInfo );
			}

		}
		
	} 
#else
 {
		// If length of string is less than max char
		if( nLength < _iMaxCharInfoChar )
		{
			// Check line character
			int iPos;
			for( iPos = 0; iPos < nLength; iPos++ )
			{
				if( strCharInfo[iPos] == '\n' || strCharInfo[iPos] == '\r' )
					break;	
			}

			// Not exist
			if( iPos == nLength )
			{
				m_strCharInfo[m_nCurInfoLines] = strCharInfo;
				m_colCharInfo[m_nCurInfoLines++] = colCharInfo;
			}
			else
			{
				// Split string
				CTString	strTemp;
				strCharInfo.Split( iPos, m_strCharInfo[m_nCurInfoLines], strTemp );
				m_colCharInfo[m_nCurInfoLines++] = colCharInfo;

				// Trim line character
				if( strTemp[0] == '\r' && strTemp[1] == '\n' )
					strTemp.TrimLeft( strTemp.Length() - 2 );
				else
					strTemp.TrimLeft( strTemp.Length() - 1 );

				AddCharInfoString( strTemp, colCharInfo );
			}
		}
		// Need multi-line
		else
		{
			// Check splitting position for 2 byte characters
			int		nSplitPos = _iMaxCharInfoChar;
			BOOL	b2ByteChar = FALSE;
			int		iPos;
			for( iPos = 0; iPos < nSplitPos; iPos++ )
			{
				if( strCharInfo[iPos] & 0x80 )
					b2ByteChar = !b2ByteChar;
				else
					b2ByteChar = FALSE;
			}

			if( b2ByteChar )
				nSplitPos--;

			// Check line character			
			for( iPos = 0; iPos < nSplitPos; iPos++ )
			{
				if( strCharInfo[iPos] == '\n' || strCharInfo[iPos] == '\r' )
					break;
			}

			// Not exist
			if( iPos == nSplitPos )
			{
				// Split string
				CTString	strTemp;
				strCharInfo.Split( nSplitPos, m_strCharInfo[m_nCurInfoLines], strTemp );
				m_colCharInfo[m_nCurInfoLines++] = colCharInfo;

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

				AddCharInfoString( strTemp, colCharInfo );
			}
			else
			{
				// Split string
				CTString	strTemp;
				strCharInfo.Split( iPos, m_strCharInfo[m_nCurInfoLines], strTemp );
				m_colCharInfo[m_nCurInfoLines++] = colCharInfo;

				// Trim line character
				if( strTemp[0] == '\r' && strTemp[1] == '\n' )
					strTemp.TrimLeft( strTemp.Length() - 2 );
				else
					strTemp.TrimLeft( strTemp.Length() - 1 );

				AddCharInfoString( strTemp, colCharInfo );
			}
		}
	}
#endif
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CUICreateChar::GetCharInfo()
{
	m_nCurInfoLines = 0;

	AddCharInfoString( m_astrDescription[m_iSelectedJob * 2], 0xCCCCCCFF );
	AddCharInfoString( m_astrDescription[m_iSelectedJob * 2 + 1], 0xCCCCCCFF );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CUICreateChar::Lock(BOOL bLock)
{
	m_ebCharName.SetEnable(!bLock);
	m_btnOK.SetEnable(!bLock);
	m_btnJobPrev.SetEnable(!bLock);
	m_btnJobNext.SetEnable(!bLock);
	m_btnFacePrev.SetEnable(!bLock);
	m_btnFaceNext.SetEnable(!bLock);
	m_btnHairPrev.SetEnable(!bLock);
	m_btnHairNext.SetEnable(!bLock);
	m_btnHeadPrev.SetEnable(!bLock);
	m_btnHeadNext.SetEnable(!bLock);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CUICreateChar::SetBackgroundWorld( CWorld *pWorld )
{
	m_pWorld = pWorld;
}

/************************************************************************/
/* Name : BOOL CheckChracterHK                                          */
/************************************************************************/
BOOL CUICreateChar::CheckCharacterHK(const char* chHK)
{
	unsigned char chTemp1 = (*chHK);
	unsigned char chTemp2;
	
	// ȫ�� ���̵� �Է½� ������ ��� 0xF5FA�� ��Ʈ�� �ϼ���. [7/27/2010 rumist]
	// ���� FA�� 250���� �����Ǿ� Ư�����ڷ� �νĵ�.
	// ������ 0xFA�� ���͸� 0xFB�� ����.
	// ȫ�� IME���� �Է� ������ �ɸ��Ƿ� 0xC8�� ������. [9/8/2010 rumist]
	if ( ((chTemp1) >= 0x80 && (chTemp1) <= 0xA0) || (chTemp1) == 0xC7/* || (chTemp1) == 0xC8*/ || ((chTemp1) >= 0xFB && (chTemp1) <= 0xFF) )
	{
		return FALSE;
	}
	else if ( (chTemp1) == 0xF9 )
	{
		chTemp2 = (*(chHK+1));

		if ( (chTemp2) >= 0xDD && (chTemp2) <= 0xFF )
		{
			return FALSE;
		}
	}
	else
	{
		chTemp2 = (*(chHK+1));

		if ( (chTemp2) >= 0x7F && (chTemp2) <= 0xA0 )
		{
			return FALSE;
		}
	}

	if (chTemp1 >= 0x80)
	{
		chHK++;
	}

	return TRUE;
}