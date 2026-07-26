// WSS_DRATAN_SIEGEWARFARE 070726 -------------------------------------------//
// ���ź �Ű��� �ý��� 
// ���� �������� �߰��� �κи� �����Ѵ�.
// --------------------------------------------------------------------------//
#include "stdh.h"

// ��� ����. [12/2/2009 rumist]
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UISiegeWarfareNew.h>
#include <Engine/Interface/UISiegeWarfareDoc.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Object/ActorMgr.h>

#define TOWER_COMBOBOX_SIZE (18)
#define CONSENSUSBAR_SIZE	(261)
#define CONSENSUS_TIMEUP	(180)		// ���� �ð�(sec)
#define CONSENSUS_WAIT		(6)
#define TOWER_USE_NAS		(1000000)	// 1�鸸 ����(default)

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::CUISiegeWarfareNew
// Explain:  
//------------------------------------------------------------------------------
CUISiegeWarfareNew::CUISiegeWarfareNew()
{
	m_tmWaitTime = 0;
	m_tmStartTime = 0;	
	m_iConsensusBarSize = 0;
	m_iUpgradeLevel = 0;
	m_iUpgradeLevelOld = 0;
	m_iUpgradeType	= SWUT_ATTACK;
	m_iRepairMoney = 0;
	m_iRepairTowerIndex = 0;	
	m_iNpcIdx = 0;		
	m_iWaitTime = -1;
	m_iWaitTime_const = -1;
	m_tmInitTime = 0;
	m_bOnWar	= FALSE;
	m_bReceivedTime = TRUE;
}

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::~CUISiegeWarfareNew
// Explain:  
//------------------------------------------------------------------------------
CUISiegeWarfareNew::~CUISiegeWarfareNew()
{	
	if( _pUISWDoc!= NULL ) 
	{
		delete _pUISWDoc;
		_pUISWDoc = NULL;
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::Clear
// Explain:  
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::Clear()
{
	for(int i=0;i<DRATAN_TOWER_KIND_MAX;i++)
	{
		for(int j=0;j<DRATAN_TOWER_MAX;j++)
		{
			m_cbtnTowerOn[i][j].SetCheck(FALSE);
		}
	}
	m_tmStartTime = 0;
	m_tmWaitTime = 0;
	m_iConsensusBarSize =0;
	m_iUpgradeLevel = 0;
	m_iUpgradeLevelOld = 0;
	m_iUpgradeType	= SWUT_ATTACK;
	m_iRepairMoney = 0;
	m_iRepairTowerIndex = 0;	
	m_iNpcIdx =0;
	m_iWaitTime = -1;
	m_iWaitTime_const = -1;
	m_tmInitTime = 0;		
}

// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUISiegeWarfareNew::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUISiegeWarfareNew::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::Create
// Explain:  
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight )
{
	// CUISiegeWarfare::Create ���� �����Ǽ� ���´�.
	// �ߺ� ���� (�޸� ����)
// 	_pUISWDoc = new CUISiegeWarfareDoc();
// 	_pUISWDoc->SetUIState( SWS_NONE );	

	CUIWindow::Create(pParentWnd, nX, nY, nWidth, nHeight);
	
	m_ptdBaseTexture = CreateTexture( CTString( "Data\\Interface\\MessageBox.tex" ) );

	FLOAT	fTexWidth = m_ptdBaseTexture->GetPixWidth();
	FLOAT	fTexHeight = m_ptdBaseTexture->GetPixHeight();

	// ����
	// Set Box
	m_bxBackGroundBox.SetBoxUV(m_ptdBaseTexture,30,22,WRect(0,0,216,22));
	m_bxBackGroundBox2.SetBoxUV(m_ptdBaseTexture,20,11,WRect(0,22,216,45));	
	m_bxBox1.SetBoxUV(m_ptdBaseTexture,3,WRect(0,68,34,102));	
	m_bxBox2.SetBoxUV(m_ptdBaseTexture,3,WRect(42,86,245,105));
	
	// Lines
	m_uvLineH.SetUV(237,1,244,1,fTexWidth,fTexHeight);
	m_uvLineV.SetUV(246,3,246,9,fTexWidth,fTexHeight);
		
	// Ÿ�� �����ϱ� -------------------------------------------------------->>
	// ��ư
	// Buttons
	m_btnApply.Create( this, _S( 3688,"�����ϱ�" ), 383, 307, 63, 21 );
	m_btnApply.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnApply.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnApply.CopyUV( UBS_IDLE, UBS_ON );
	m_btnApply.CopyUV( UBS_IDLE, UBS_DISABLE );
		
	m_btnReturn.Create( this, _S(  3689,"���ư���" ), 470, 307, 63, 21 );
	m_btnReturn.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnReturn.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnReturn.CopyUV( UBS_IDLE, UBS_ON );
	m_btnReturn.CopyUV( UBS_IDLE, UBS_DISABLE );

	m_cbtnTowerOn[7][DRATAN_TOWER_MAX];		// ���� ���� ��ư

	int		i, j;
	for( i = 0; i < DRATAN_TOWER_KIND_MAX; i++ )
	{
		for( j = 0; j < DRATAN_TOWER_MAX; j++ )
		{
			m_cbtnTowerOn[i][j].Create( this, 442 + TOWER_COMBOBOX_SIZE * j, 132 +TOWER_COMBOBOX_SIZE * i
										, TOWER_COMBOBOX_SIZE, TOWER_COMBOBOX_SIZE,	CTString("") );	
			m_cbtnTowerOn[i][j].SetUV( UCBS_NONE, 12, 161, 23, 172, fTexWidth, fTexHeight );
			m_cbtnTowerOn[i][j].SetUV( UCBS_CHECK, 0, 161, 11, 172, fTexWidth, fTexHeight );
			m_cbtnTowerOn[i][j].CopyUV( UCBS_NONE, UCBS_CHECK_DISABLE );
			m_cbtnTowerOn[i][j].CopyUV( UCBS_NONE, UCBS_NONE_DISABLE );
			m_cbtnTowerOn[i][j].SetTextColor( UCBS_CHECK, 0xF2F2F2FF );
			m_cbtnTowerOn[i][j].SetTextColor( UCBS_NONE, 0xF2F2F2FF );
			m_cbtnTowerOn[i][j].SetCheck( FALSE );
		}
	}
	// ----------------------------------------------------------------------<<
	
	// Ÿ�� ��ȭ�ϱ� -------------------------------------------------------->>	

	int black = 74; // black �� 0���� ������ ȸ�� ������ Edit �ڽ� ����
	CTString tStr;
	// ��ȭ ���� ��ư	
//	m_sbtnUpgrade.Create( this, 80, 159, 100, 14, _S( 3690,"��ȭ �ܰ�"), 37 );
	m_sbtnUpgrade.Create( this, 80, 159, 150, 15, _S( 3690,"��ȭ �ܰ�"), 37 );
	m_sbtnUpgrade.SetDataBackUV3( 131+black, 46, 135+black, 59, 136+black, 46, 140+black, 59, 
							141 + black, 46, 145 + black, 59, fTexWidth, fTexHeight );
	
	m_sbtnUpgrade.SetUpUV( UBS_IDLE, 230, 16, 239, 23, fTexWidth, fTexHeight );
	m_sbtnUpgrade.SetUpUV( UBS_CLICK, 240, 16, 249, 23, fTexWidth, fTexHeight );
	m_sbtnUpgrade.CopyUpUV( UBS_IDLE, UBS_ON );
	m_sbtnUpgrade.CopyUpUV( UBS_IDLE, UBS_DISABLE );
	
	m_sbtnUpgrade.SetDownUV( UBS_IDLE, 230, 24, 239, 31, fTexWidth, fTexHeight );
	m_sbtnUpgrade.SetDownUV( UBS_CLICK, 240, 24, 249, 31, fTexWidth, fTexHeight );
	m_sbtnUpgrade.CopyDownUV( UBS_IDLE, UBS_ON );
	m_sbtnUpgrade.CopyDownUV( UBS_IDLE, UBS_DISABLE );
	m_sbtnUpgrade.CreateButtons( 9, 7 );
	m_sbtnUpgrade.SetWheelRect( -19, -75, 271, 165 );

	m_sbtnUpgrade.ResetAllDatas();
	for( i = 0; i <= TOWER_UPGRADE_MAX; i++)
	{
		tStr.PrintF("%d",i);
		m_sbtnUpgrade.AddData(tStr);
	}

	// Button Create
	m_btnOK.Create( this, _S( 191, "Ȯ��" ), 146, 249, 63, 21 );
	m_btnOK.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnOK.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnOK.CopyUV( UBS_IDLE, UBS_ON );
	m_btnOK.CopyUV( UBS_IDLE, UBS_DISABLE );

	m_btnCancel.Create( this, _S( 139, "���" ), 237, 249, 63, 21 );
	m_btnCancel.SetUV( UBS_IDLE, 0, 46, 63, 67, fTexWidth, fTexHeight );
	m_btnCancel.SetUV( UBS_CLICK, 66, 46, 129, 67, fTexWidth, fTexHeight );
	m_btnCancel.CopyUV( UBS_IDLE, UBS_ON );
	m_btnCancel.CopyUV( UBS_IDLE, UBS_DISABLE );
	// ----------------------------------------------------------------------<<

	// ���� �ϱ� ------------------------------------------------------------>>
	m_rcPuple.SetRect(26,47,26+m_iConsensusBarSize,66);
	m_bxPurple.SetBoxUV(m_ptdBaseTexture,2,WRect(328,189,336,195));								// ���� ���� �ڽ�
	// ----------------------------------------------------------------------<<	

	// ��Ȱ ��� �ð�
	m_rcWaitTime.SetRect(26,47,56,87);
	
}

// Open UI ------------------------------------------------------>>
// Ÿ�� �����ϱ� ����
void CUISiegeWarfareNew::OpenCheckTower()
{
	extern ENGINE_API CDrawPort	*_pdpMain;
	// Set window Size
	SetSize(550,368);
	m_rcTitle.SetRect(0,0,550,22);
	
	ResetPosition(_pdpMain->dp_MinI,_pdpMain->dp_MinJ,_pdpMain->dp_MaxI,_pdpMain->dp_MaxJ);
	_pUISWDoc->SetUIState(SWS_APPLY_TOWER);
	CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_NEW, TRUE );
}
// Ÿ�� ��ȭ�ϱ� ����
void CUISiegeWarfareNew::OpenUpgradeTower()
{
	extern ENGINE_API CDrawPort	*_pdpMain;
	// Set window Size
	SetSize(421,289);
	m_rcTitle.SetRect(0,0,421,22);
	
	// Reset Button Position
	m_btnOK.SetPos( 146, 249 );
	m_btnCancel.SetPos( 237, 249 );	

	ResetPosition(_pdpMain->dp_MinI,_pdpMain->dp_MinJ,_pdpMain->dp_MaxI,_pdpMain->dp_MaxJ);
	_pUISWDoc->SetUIState(SWS_UPGRADE_TOWER);
	CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_NEW, TRUE );
}
// Ÿ�� ���� �ϱ�
void CUISiegeWarfareNew::OpenRepairTower()
{
	extern ENGINE_API CDrawPort	*_pdpMain;
	// Set window Size
	SetSize(421,145);
	m_rcTitle.SetRect(0,0,421,22);

	// Reset Button Position
	m_btnOK.SetPos( 130, 110 );
	m_btnCancel.SetPos( 240, 110 );

	ResetPosition(_pdpMain->dp_MinI,_pdpMain->dp_MinJ,_pdpMain->dp_MaxI,_pdpMain->dp_MaxJ);
	_pUISWDoc->SetUIState(SWS_REPAIR_TOWER);
	CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_NEW, TRUE );
}
// ũ����Ż ���� ����
void CUISiegeWarfareNew::OpenConsensus()
{
	// Set window Size
	CTString tStr;
	extern ENGINE_API CDrawPort	*_pdpMain;

	SetSize(316,121);
	m_rcTitle.SetRect(0,0,316,22);	

	ResetPosition(_pdpMain->dp_MinI,_pdpMain->dp_MinJ,_pdpMain->dp_MaxI,_pdpMain->dp_MaxJ);
	_pUISWDoc->SetUIState(SWS_CONSENSUS_CRYSTAL);
	CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_NEW, TRUE );

}

void CUISiegeWarfareNew::OpenWaitTime()
{
	extern ENGINE_API CDrawPort	*_pdpMain;

	SetSize(185,121);
	m_rcTitle.SetRect(0,0,185,22);	

	ResetPosition(_pdpMain->dp_MinI,_pdpMain->dp_MinJ,_pdpMain->dp_MaxI,_pdpMain->dp_MaxJ);
	m_bReceivedTime = FALSE;
	_pUISWDoc->SetUIState(SWS_WAIT_REBIRTH);
	CUIManager::getSingleton()->RearrangeOrder(UI_SIEGE_WARFARE_NEW,TRUE);			
}

//----------------------------------------------------------------<<

// ��Ȱ ��� �ð�
void CUISiegeWarfareNew::RenderWaitTime()
{	
	int	nX, nY;
	CTString tStr;
	GetAbsPos( nX, nY );

	CUIManager* pUIManager = CUIManager::getSingleton();
	CDrawPort* pDrawPort = pUIManager->GetDrawPort();

	pDrawPort->InitTextureData( m_ptdBaseTexture );

	// Background
	m_bxBackGroundBox.SetBoxPos(WRect(nX,nY,nX+185,nY+22));
	m_bxBackGroundBox.Render();
	m_bxBackGroundBox2.SetBoxPos(WRect(nX,nY+22,nX+185,nY+121));
	m_bxBackGroundBox2.Render();

	m_bxBox2.SetBoxPos(WRect(nX+23,nY+45,nX+160,nY+69));
	m_bxBox2.Render();

	// Render Vertical Lines
	// Render Text		
	pDrawPort->PutTextEx(_S( 3691,"���� �� ��Ȱ ���ð�"),nX+19,nY+6);
	if( m_iWaitTime > 0 )
	{
		if ( m_iWaitTime >= 60 )
			tStr.PrintF(_S(2513,"%d��"),(m_iWaitTime/60));
		else 
			tStr.PrintF(_S(2514,"%d��"),(m_iWaitTime));
		
		pDrawPort->PutTextExCX(tStr,nX+93,nY+49);

		m_iWaitTime = m_iWaitTime_const - (((unsigned int(_pTimer->GetLerpedCurrentTick()*1000))/*timeGetTime()*/ - m_tmStartTime))/1000;
	}
	else 
	{	
		pDrawPort->PutTextExCX(_S( 3692,"��Ȱ �����...."),nX+93,nY+86);
		if(m_tmStartTime && m_bReceivedTime)
		{
			if( pUIManager->DoesMessageBoxExist(MSGCMD_SIEGEWARFARE_REBIRTH) ) return;

			// ��ŸƮ Ÿ�� ����
			m_tmStartTime = 0;
			m_tmWaitTime = 0;

			// ��Ȱ ���� üũ
			BOOL bComp = FALSE;
			std::map<int,int>::iterator tBegin,tEnd;					
			
			for(tBegin	=	_pNetwork->MyCharacterInfo.mQuarter.begin(), 
				tEnd	=	_pNetwork->MyCharacterInfo.mQuarter.end();
				tBegin	!=	tEnd;tBegin++)
			{
				bComp = (tBegin->second == _pNetwork->MyCharacterInfo.lGuildIndex)?TRUE:FALSE;
				if( bComp ) break;				
			}
			
			// ���� ��Ȱ �޽���
			CUIMsgBox_Info msgInfo;			
			tStr= _S( 3693,"���� ��Ȱ" );
			if( bComp )
			{				
				msgInfo.SetMsgBoxInfo(tStr,UMBS_SELECTBOX,UI_NONE,MSGCMD_SIEGEWARFARE_REBIRTH );
				msgInfo.m_nHeight =200;
				pUIManager->CreateMessageBox(msgInfo);
				pUIManager->GetMessageBox(MSGCMD_SIEGEWARFARE_REBIRTH)->addSelectContext(_S( 3694,"��Ȱ ������ �̵�"));
				pUIManager->GetMessageBox(MSGCMD_SIEGEWARFARE_REBIRTH)->addSelectContext(_S( 3695,"����� ������ �̵�"));
			}			
			else
			{
				msgInfo.SetMsgBoxInfo(tStr,UMBS_OK,UI_SIEGE_WARFARE_NEW ,MSGCMD_SIEGEWARFARE_REBIRTH );				
				msgInfo.AddString(_S( 403, "�׾����ϴ�. ������������ �̵��Ͻðڽ��ϱ�?" ));
				pUIManager->CreateMessageBox(msgInfo);				
			}

			pUIManager->RearrangeOrder(UI_SIEGE_WARFARE_NEW,FALSE);
		}
	}

}

// ���� ���� �ð�
void CUISiegeWarfareNew::RenderConsensus()
{
	int	nX, nY;
	CTString tStr;
	GetAbsPos( nX, nY );
	
	if( CheckConsensus() > 0 ){
		StopConsensus(_pNetwork->MyCharacterInfo.index);
		SendConsensus(MSG_CASTLE_CRISTAL_RESPOND_END);
	}

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	pDrawPort->InitTextureData( m_ptdBaseTexture );

	// Background
	m_bxBackGroundBox.SetBoxPos(WRect(nX,nY,nX+316,nY+22));
	m_bxBackGroundBox.Render();
	m_bxBackGroundBox2.SetBoxPos(WRect(nX,nY+22,nX+316,nY+121));
	m_bxBackGroundBox2.Render();

	m_bxBox2.SetBoxPos(WRect(nX+23,nY+45,nX+289,nY+69));
	m_bxBox2.Render();

	// Render Vertical Lines
	// Render Text
	pDrawPort->PutTextEx(_S( 3696, "���� ���� �ð�"),nX+19,nY+6);
	for(int i=0;i<4;i++)
	{
		pDrawPort->AddTexture(nX+24+i*88,nY+69,nX+25+i*88,nY+72,m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);
		tStr.PrintF(_S(2513,"%d��"),i);
		pDrawPort->PutTextEx(tStr,nX+23+i*83,nY+80);
	}
	m_rcPuple.SetRect(26,47,26+m_iConsensusBarSize,66);
	m_bxPurple.SetBoxPos(m_rcPuple);
	m_bxPurple.Render(nX,nY);

}

// ��ȭ
void CUISiegeWarfareNew::RenderUpgradeTower()
{
	int	nX, nY;
	GetAbsPos( nX, nY );

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	pDrawPort->InitTextureData( m_ptdBaseTexture );

	// Background
	m_bxBackGroundBox.SetBoxPos(WRect(nX,nY,nX+421,nY+22));
	m_bxBackGroundBox.Render();
	m_bxBackGroundBox2.SetBoxPos(WRect(nX,nY+22,nX+421,nY+289));
	m_bxBackGroundBox2.Render();

	m_bxBox2.SetBoxPos(WRect(nX+17,nY+134,nX+403,nY+205));
	m_bxBox2.Render();

	// Render Buttons
	m_btnOK.Render();
	m_btnCancel.Render();
	m_sbtnUpgrade.Render();

	// Render Text	
	int nX2,nY2,nCab;
	CTString tStr,tStr1,tStr2,tStr3;
	nX2 = nX + 23;
	nY2 = nY + 36;
	nCab = _pUIFontTexMgr->GetFontHeight()+5;
	tStr3=_S(3697,"������");
	switch(m_iUpgradeType)
	{
		case SWUT_ATTACK:
			tStr1=_S( 3698, "������ Ÿ�� ��ȭ");
			tStr2=_S(85,"���ݷ�");			
		case SWUT_GUARD:
			{			
				if(m_iUpgradeType == SWUT_GUARD)
				{
					tStr1=_S( 3699,"������ Ÿ�� ��ȭ");
					tStr2=_S( 3700,"ȿ��"); // WSS_DRATAN_SIEGEWARFARE 071002 ��Ʈ�� ��ȣ ����
				}
				pDrawPort->PutTextEx( tStr1, nX+23, nY+6 );
				pDrawPort->PutTextEx( _S( 3701, "�󸶳� ��ȭ �Ͻðڽ��ϱ�?" ), nX2, nY2+=nCab ,COLOR(0xD3BFFFFF));
				tStr.PrintF(_S( 3702, "%d�ܰ�" ),1);
				tStr1.PrintF(_S( 3703, "%s %d% ����" ),tStr2,30);
				tStr = tStr + CTString(" ") + tStr1;
				pDrawPort->PutTextEx( tStr, nX2, nY2+=nCab);
				tStr.PrintF(_S( 3702, "%d�ܰ�" ),2);
				tStr1.PrintF(_S( 3703, "%s %d% ����" ),tStr2,50);
				tStr = tStr + CTString(" ") + tStr1;
				tStr1.PrintF(_S( 3703, "%s %d% ����" ),tStr3,50);
				tStr = tStr +CTString("/") + tStr1; 				
				pDrawPort->PutTextEx( tStr, nX2, nY2+=nCab);
				tStr.PrintF(_S( 3702, "%d�ܰ�" ),3);
				tStr1.PrintF(_S( 3703, "%s %d% ����" ),tStr2,100);
				tStr = tStr + CTString(" ") + tStr1;
				tStr1.PrintF(_S( 3703, "%s %d% ����" ),tStr3,100);
				tStr = tStr +CTString("/") + tStr1; 
				pDrawPort->PutTextEx( tStr, nX2, nY2+=nCab);				
			}
			break;
		case SWUT_GATE:
			{
				tStr1=_S( 3704,"���� ��ȭ");
				
				pDrawPort->PutTextEx( tStr1, nX+23, nY+6 );
				pDrawPort->PutTextEx( _S( 3701,  "�󸶳� ��ȭ �Ͻðڽ��ϱ�?" ), nX2, nY2+=nCab ,COLOR(0xD3BFFFFF));
				tStr.PrintF(_S( 3702, "%d�ܰ�" ),1);
				tStr1.PrintF(_S( 3703, "%s %d% ����" ),tStr3,50);				
				tStr = tStr+CTString(" ")+ tStr1;
				pDrawPort->PutTextEx( tStr, nX2, nY2+=nCab);
				tStr.PrintF(_S( 3702, "%d�ܰ�" ),2);
				tStr1.PrintF(_S( 3703, "%s %d% ����" ),tStr3,100);
				tStr = tStr+CTString(" ")+ tStr1;
				pDrawPort->PutTextEx( tStr, nX2, nY2+=nCab);
				tStr.PrintF(_S( 3702, "%d�ܰ�" ),3);
				tStr1.PrintF(_S( 3703, "%s %d% ����" ),tStr3,200);
				tStr = tStr+CTString(" ")+ tStr1;
				pDrawPort->PutTextEx( tStr, nX2, nY2+=nCab);
			}
			
			break;
	}	
	
	
	pDrawPort->PutTextExRX( _S(1181, "�ʿ� ����" ), nX+301, nY+164 );
	tStr.PrintF(_S(836,"%I64d ����"),GetTowerUpgradePay(m_iUpgradeType,m_iUpgradeLevel));	// TODO :: Ÿ�� ���� ����
	pDrawPort->PutTextExRX( tStr, nX+392, nY+164 );

}

// Ÿ�� �����ϱ� 
void CUISiegeWarfareNew::RenderCheckTower()
{
	int	nX, nY,i,j,iGab;
	GetAbsPos( nX, nY );

	// Move -> OpenCheckTower
	// Set window Size

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	pDrawPort->InitTextureData( m_ptdBaseTexture );

	// Background
	m_bxBackGroundBox.SetBoxPos(WRect(nX,nY,nX+550,nY+22));
	m_bxBackGroundBox.Render();
	m_bxBackGroundBox2.SetBoxPos(WRect(nX,nY+22,nX+550,nY+346));
	m_bxBackGroundBox2.Render();

	m_bxBox2.SetBoxPos(WRect(nX+15,nY+113,nX+532,nY+133));
	m_bxBox2.Render();

	// Horizon Lines
	iGab = 18;
	for(i=0;i<9;i++)
	{
		pDrawPort->AddTexture(nX+80,nY+113+iGab*i,nX+532,nY+114+iGab*i,
		m_uvLineH.U0,m_uvLineH.V0,m_uvLineH.U1,m_uvLineH.V1,0xFFFFFFFF);
	}

	pDrawPort->AddTexture(nX+16,nY+113,nX+80,nY+114,
	m_uvLineH.U0,m_uvLineH.V0,m_uvLineH.U1,m_uvLineH.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+16,nY+131,nX+80,nY+132,
	m_uvLineH.U0,m_uvLineH.V0,m_uvLineH.U1,m_uvLineH.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+16,nY+185,nX+80,nY+186,
	m_uvLineH.U0,m_uvLineH.V0,m_uvLineH.U1,m_uvLineH.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+16,nY+239,nX+80,nY+240,
	m_uvLineH.U0,m_uvLineH.V0,m_uvLineH.U1,m_uvLineH.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+16,nY+257,nX+80,nY+258,
	m_uvLineH.U0,m_uvLineH.V0,m_uvLineH.U1,m_uvLineH.V1,0xFFFFFFFF);

	// Vertical Lines
	pDrawPort->AddTexture(nX+16,nY+113,nX+17,nY+257,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+80,nY+113,nX+81,nY+257,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);
	pDrawPort->AddTexture(nX+198,nY+113,nX+199,nY+257,
	m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);

	for(i=0;i<6;i++)
	{
		pDrawPort->AddTexture(nX+441+iGab*i,nY+113,nX+442+iGab*i,nY+257,
		m_uvLineV.U0,m_uvLineV.V0,m_uvLineV.U1,m_uvLineV.V1,0xFFFFFFFF);
	}	

	// Render Buttons
	m_btnApply.Render();
	m_btnReturn.Render();
	
	// Render Text
	int nX2,nY2,nCab;
	CTString tStr;
	nX2 = nX + 19;
	nY2 = nY + 30;
	nCab = _pUIFontTexMgr->GetFontHeight()+5;
	
	pDrawPort->PutTextEx( _S( 3675, "Ÿ�� �����ϱ�" ), nX+23, nY+6 );	

	pDrawPort->PutTextEx( _S( 3706, "��ȣŸ�� �� ����ϰ��� �ϴ� Ÿ���� ������ �ֽñ� �ٶ��ϴ�." ), nX2, nY2+=nCab ,COLOR(0xD3BFFFFF));	
	pDrawPort->PutTextEx( _S( 3707, "���� ������ Ÿ���� 5������ �����ϸ�, �ѹ� ������ Ÿ���� ������ ����� �� �����ϴ�." ), nX2, nY2+=nCab,COLOR(0xD3BFFFFF));
	pDrawPort->PutTextEx( _S( 3708, "��, ����� Ÿ���� ������ ��ġ�� ������� ��ġ�� Ÿ���� ������ ���� å���˴ϴ�." ), nX2, nY2+=nCab,COLOR(0xD3BFFFFF));

	pDrawPort->PutTextExCX( _S( 3709, "Ÿ��" ), nX+48, nY+117 );	
	pDrawPort->PutTextExCX( _S( 3710, "������" ), nX+48, nY+153 );
	pDrawPort->PutTextExCX( _S( 3711, "������" ), nX+48, nY+206 );
	pDrawPort->PutTextExCX( _S( 3712, "������" ), nX+48, nY+242 );

	pDrawPort->PutTextExCX( _S( 3713, "����" ), nX+138, nY+117 );
	pDrawPort->PutTextExCX( _S( 3714, "�ٰŸ�" ), nX+138, nY+135 );
	pDrawPort->PutTextExCX( _S( 3715, "���Ÿ�" ), nX+138, nY+152 );
	pDrawPort->PutTextExCX( _S( 3716, "����" ), nX+138, nY+171 );
	pDrawPort->PutTextExCX( _S( 3717, "�ӵ��϶�" ), nX+138, nY+188 );
	pDrawPort->PutTextExCX( _S( 3718, "�ɷ�ġ�϶�" ), nX+138, nY+206 );
	pDrawPort->PutTextExCX( _S( 3719, "�� �ߵ�" ), nX+138, nY+225 );
	pDrawPort->PutTextExCX( _S( 3720, "��������" ), nX+138, nY+242 );

	pDrawPort->PutTextExCX( _S( 3721, "����" ), nX+321, nY+117 );
	pDrawPort->PutTextEx( _S( 3722, "�ֺ��� ���� �����Ѵ�." ), nX+206, nY+135 );
	pDrawPort->PutTextEx( _S( 3723, "���� �Ÿ� ���� ���� �����Ѵ�." ), nX+206, nY+152 );
	pDrawPort->PutTextEx( _S( 3724, "�ֺ��� ������ ���� ������ �Ѵ�." ), nX+206, nY+171 );
	pDrawPort->PutTextEx( _S( 3725, "�ֺ� ���� ���� �ӵ��� �̵��ӵ� �϶�" ), nX+206, nY+188 );
	pDrawPort->PutTextEx( _S( 3726, "�ֺ� ���� �ɷ�ġ �϶�" ), nX+206, nY+206 );
	pDrawPort->PutTextEx( _S( 3727, "�ֺ��� ������ ������ �� �ߵ�" ), nX+206, nY+225 );
	pDrawPort->PutTextEx( _S( 3728, "���� ����, ��Ȱ ���ð� ����" ), nX+206, nY+242 );


	pDrawPort->PutTextExRX( _S( 3729, "�� �ʿ䳪��:" ), nX+425, nY+267 );

	CTString strNas;
	strNas.PrintF("%I64d", GetTowerPay());
	UIMGR()->InsertCommaToString(strNas);
	tStr.PrintF(_S( 3730, "%s ����"), strNas);	// TODO :: Ÿ�� ���� ����
	pDrawPort->PutTextExRX( tStr, nX+527, nY+267 );	
	
	for(i=0;i<5;i++)
	{
		tStr.PrintF("%d",i+1);
		pDrawPort->PutTextExCX( tStr, nX+450+iGab*i, nY+117 );
	}

	for( i=0;i<DRATAN_TOWER_KIND_MAX;i++)
	{
		for( j=0;j<DRATAN_TOWER_MAX;j++)
		{
			m_cbtnTowerOn[i][j].Render();	
		}
	}
	
}

// Ÿ�� �����ϱ�
void CUISiegeWarfareNew::RenderRepairTower()
{
	int	nX, nY;
	GetAbsPos( nX, nY );

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	pDrawPort->InitTextureData( m_ptdBaseTexture );

	// Background
	m_bxBackGroundBox.SetBoxPos(WRect(nX,nY,nX+421,nY+22));
	m_bxBackGroundBox.Render();
	m_bxBackGroundBox2.SetBoxPos(WRect(nX,nY+22,nX+421,nY+145));
	m_bxBackGroundBox2.Render();

	// Render Buttons
	m_btnOK.Render();
	m_btnCancel.Render();	

	// Render Text	
	int nX2,nY2,nCab;
	CTString tStr;
	nX2 = nX + 23;
	nY2 = nY + 25;
	nCab = _pUIFontTexMgr->GetFontHeight()+5;	
	
	CTString strNas;
	strNas.PrintF("%I64d", GetRepairMoney());
	UIMGR()->InsertCommaToString(strNas);
	tStr.PrintF(_S(3899, "�������:%s"), strNas);

	pDrawPort->PutTextEx( _S( 3731,"Ÿ�� �����ϱ�"), nX+23, nY+6 );
	pDrawPort->PutTextEx( _S( 3732,"�ı����� �ʰ� �μ��� Ÿ���� �ٷ� ������ �����մϴ�."), nX2, nY2+=nCab);
	pDrawPort->PutTextEx( _S( 3733,"��������� �μ��� ������ ���� å���Ǹ� ������ �����ϴ�."), nX2, nY2+=nCab);
	pDrawPort->PutTextExCX( tStr, nX+GetWidth()/2, nY2+=nCab+10,COLOR(0xD3BFFFFF));

}
//------------------------------------------------------------------------------
// CUISiegeWarfareNew::Render
// Explain:  
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::Render()
{	
//	_pUISWDoc->RunDalyTime();

	switch(_pUISWDoc->GetUIState())
	{
		case SWS_APPLY_TOWER:
			RenderCheckTower();
			break;
		case SWS_UPGRADE_TOWER:
			RenderUpgradeTower();
			break;
		case SWS_REPAIR_TOWER:
			RenderRepairTower();
			break;
		case SWS_CONSENSUS_CRYSTAL:
			RenderConsensus();
			break;
		case SWS_WAIT_REBIRTH :
			RenderWaitTime();
			break;
	}	

	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	pDrawPort->FlushRenderingQueue();
	pDrawPort->EndTextEx();
}
 
//------------------------------------------------------------------------------
// CUISiegeWarfareNew::MouseMessage
// Explain:  
//------------------------------------------------------------------------------
WMSG_RESULT CUISiegeWarfareNew::MouseMessage( MSG *pMsg )
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
			if( IsInside( nX, nY ) )
				CUIManager::getSingleton()->SetMouseCursorInsideUIs();

			int	ndX = nX - nOldX;
			int	ndY = nY - nOldY;

			// Move shop
			if( bTitleBarClick && ( pMsg->wParam & MK_LBUTTON ) )
			{
				nOldX = nX;	nOldY = nY;
				Move( ndX, ndY );			
				return WMSG_SUCCESS;
			}

			m_btnOK.MouseMessage( pMsg );		// Ȯ��
			m_btnCancel.MouseMessage( pMsg );	// ���
			m_btnApply.MouseMessage( pMsg );	// �����ϱ�
			m_btnReturn.MouseMessage( pMsg );	// ���ư���
			m_sbtnUpgrade.MouseMessage(pMsg);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			if( IsInside( nX, nY ) )
				{
					nOldX = nX;		nOldY = nY;
				
					// Title bar
					if( IsInsideRect( nX, nY, m_rcTitle ) )
					{
						bTitleBarClick = TRUE;
					}


					switch(_pUISWDoc->GetUIState())
					{
						case SWS_APPLY_TOWER:
							{
									// Check ComboBox
								if( ( wmsgResult = CheckCBMouseMessage(pMsg)) != WMSG_FAIL )
								{
									return WMSG_SUCCESS;
								}
								else if( m_btnApply.MouseMessage( pMsg ) != WMSG_FAIL )
								{
									return WMSG_SUCCESS;
								}
								else if( m_btnReturn.MouseMessage( pMsg ) != WMSG_FAIL )
								{
									return WMSG_SUCCESS;
								}	
							}
							break;

						case SWS_UPGRADE_TOWER:							
							if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
							{
								return WMSG_SUCCESS;
							}
							else if( m_btnCancel.MouseMessage( pMsg ) != WMSG_FAIL )
							{
								return WMSG_SUCCESS;
							}
							else if( m_sbtnUpgrade.MouseMessage(pMsg) != WMSG_FAIL )
							{								 
								return WMSG_SUCCESS;
							}
							break;
						case SWS_REPAIR_TOWER:
							if( m_btnOK.MouseMessage( pMsg ) != WMSG_FAIL )
							{
								return WMSG_SUCCESS;
							}
							else if( m_btnCancel.MouseMessage( pMsg ) != WMSG_FAIL )
							{
								return WMSG_SUCCESS;
							}
							break;
						
					}					
					CUIManager::getSingleton()->RearrangeOrder( UI_GUILD_BATTLE, TRUE );
					return WMSG_SUCCESS;
				}
			
		}
		break;

	case WM_LBUTTONUP:
		{
			bTitleBarClick = FALSE;

			switch(_pUISWDoc->GetUIState())
			{
				case SWS_APPLY_TOWER:
					
					if( ( wmsgResult = m_btnApply.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							// TODO : �ش� üũ�� ������ ��� ���¸� �����Ѵ�.
							SetTowerSetFromCB();
							SendApplyTowerSet();	
							CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_NEW, FALSE );
						}								
					}
					else if( ( wmsgResult = m_btnReturn.MouseMessage( pMsg ) ) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{	
							//Clear();
							CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_NEW, FALSE );
						}				
					}
					break;
				case SWS_UPGRADE_TOWER:							
					if( (wmsgResult = m_btnOK.MouseMessage( pMsg )) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							SendTowerReinforce(m_iUpgradeType,m_iUpgradeLevel);						
							CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_NEW, FALSE );
						}
						return wmsgResult;
					}
					else if( (wmsgResult = m_btnCancel.MouseMessage( pMsg )) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{	
						//	Clear();
							CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_NEW, FALSE );
						}			
						return wmsgResult;
					}	
					else if( m_sbtnUpgrade.MouseMessage(pMsg) != WMSG_FAIL )
					{
						m_iUpgradeLevel = m_sbtnUpgrade.GetSelectPos();
						if( m_iUpgradeLevelOld >= m_iUpgradeLevel)
						{
								m_sbtnUpgrade.SetSelectPos(m_iUpgradeLevelOld);
								m_iUpgradeLevel = m_iUpgradeLevelOld;
						}
						return WMSG_SUCCESS;
					}
					break;
				case SWS_REPAIR_TOWER:
					if( (wmsgResult= m_btnOK.MouseMessage( pMsg )) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{
							SendTowerRepair(m_iRepairTowerIndex );
							CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_NEW, FALSE );
						}
						return wmsgResult;
					}
					else if((wmsgResult= m_btnCancel.MouseMessage( pMsg )) != WMSG_FAIL )
					{
						if( wmsgResult == WMSG_COMMAND )
						{	
						//	Clear();
							CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_NEW, FALSE );
						}			
						return wmsgResult;
					}
					break;
			}
			return WMSG_SUCCESS;
		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			return WMSG_SUCCESS;			
		}
		break;	

	case WM_MOUSEWHEEL:
		{
			if( IsInside( nX, nY ) )
			{
				if( _pUISWDoc->GetUIState() == SWS_UPGRADE_TOWER )
				{
					if( m_sbtnUpgrade.MouseMessage( pMsg ) != WMSG_FAIL )
					{
						m_iUpgradeLevel = m_sbtnUpgrade.GetSelectPos();
						if( m_iUpgradeLevelOld >= m_iUpgradeLevel)
						{
							m_sbtnUpgrade.SetSelectPos(m_iUpgradeLevelOld);	
							m_iUpgradeLevel = m_iUpgradeLevelOld;
						}
						return WMSG_SUCCESS;	
					}
				}	
			}
		}
		break;
	}

	return WMSG_FAIL;
}

void CUISiegeWarfareNew::WaitConsensus(ULONG charIdx) {
	if (_pNetwork->MyCharacterInfo.index == charIdx && m_tmWaitTime == 0) {
		m_tmWaitTime = (unsigned int(_pTimer->GetLerpedCurrentTick()*1000)); //timeGetTime();
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::StartConsensus()
// Explain:  
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::StartConsensus(ULONG charIdx)
{		
	// �÷��̾��� ���...
	if( _pNetwork->MyCharacterInfo.index == charIdx )
	{
		m_tmStartTime = (unsigned int(_pTimer->GetLerpedCurrentTick()*1000)); //timeGetTime();		
		m_iConsensusBarSize = 0;
		OpenConsensus();		
		StartConsensusAni(charIdx);
	}
	// �ٸ� ĳ������ ���
	else
	{
		StartConsensusAni(charIdx);
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::CompleteConsensus()
// Explain:  
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::CompleteConsensus(ULONG charIdx)
{	
	// �÷��̾��� ���...
	if( //_pNetwork->MyCharacterInfo.index == charIdx ||
		_pNetwork->MyCharacterInfo.bConsensus ) // WSS_DRATAN_SIEGEWARFARE 071008
	{
		//  �� ĳ�� ���� ����
		m_tmStartTime = 0;
		m_iConsensusBarSize = 0;	
		m_tmWaitTime = 0;
		
		if( _pUISWDoc->GetUIState() == SWS_CONSENSUS_CRYSTAL )
		{
			_pUISWDoc->SetUIState( SWS_NONE );
			CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_NEW, FALSE );
		}
		_pNetwork->MyCharacterInfo.bConsensus =FALSE;
		
		// WSS_DRATAN_SIEGEWARFARE 2007/10/18
		// ���� �ʱ�ȭ
		((CPlayerEntity*)CEntity::GetPlayerEntity(0))->PlayerInit(true);

	}

	// ���� ����Ʈ ����
	_pUISWDoc->StopConsensusEffect(charIdx,TRUE); // WSS_DRATAN_SIEGEWARFARE 2007/10/14

}

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::StopConsensus()
// Explain:  
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::StopConsensus(ULONG charIdx)
{	
	// �÷��̾��� ���...
	if( _pNetwork->MyCharacterInfo.index == charIdx )
	{
		m_tmWaitTime = 0;
		m_tmStartTime = 0;
		m_iConsensusBarSize = 0;	
		
		if( _pUISWDoc->GetUIState() == SWS_CONSENSUS_CRYSTAL )
		{
			_pUISWDoc->SetUIState( SWS_NONE );
			CUIManager::getSingleton()->RearrangeOrder( UI_SIEGE_WARFARE_NEW, FALSE );
		}
		_pNetwork->MyCharacterInfo.bConsensus =FALSE;
		_pUISWDoc->StopConsensusEffect(charIdx); // WSS_DRATAN_SIEGEWARFARE 2007/10/14		
	}
	// �ٸ� ĳ������ ���
	else 
	{
		_pUISWDoc->StopConsensusEffect(charIdx); // WSS_DRATAN_SIEGEWARFARE 2007/10/14
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::CheckConsensus()
// Explain: ���� �ð� üũ( <= : ������,  > Ÿ�Ӿ�
//------------------------------------------------------------------------------
int CUISiegeWarfareNew::CheckConsensus()
{	
	DWORD tmNow = (unsigned int(_pTimer->GetLerpedCurrentTick()*1000)); //timeGetTime();
	
	if (m_tmWaitTime > 0) {
		int tmw = (tmNow - m_tmWaitTime) / 1000;
		if (tmw >= CONSENSUS_WAIT) {
			m_tmStartTime += (tmNow - m_tmWaitTime);
			m_tmWaitTime = 0;
		}
	}

	int tSec = (tmNow - m_tmStartTime)/1000;
	if( (tSec-CONSENSUS_TIMEUP) <= 0 ) m_iConsensusBarSize = tSec*260/CONSENSUS_TIMEUP ;
	return tSec-CONSENSUS_TIMEUP;
}

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::StartConsensusAni()
// Explain: 
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::StartConsensusAni(int charIdx)
{	
	// �÷��̾��� ���...
	if( _pNetwork->MyCharacterInfo.index == charIdx )
	{	
		_pNetwork->MyCharacterInfo.bConsensus = TRUE;
		_pUISWDoc->StartConsensusEffect(charIdx,CEntity::GetPlayerEntity(0)); // WSS_DRATAN_SIEGEWARFARE 2007/10/14
	}
	// �ٸ� ĳ������ ���
	else 
	{
		ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, charIdx);

		if (pObject != NULL)
		{
			((CPlayerEntity*)CEntity::GetPlayerEntity(0))->SetConsensus(charIdx);
			_pUISWDoc->StartConsensusEffect(charIdx, pObject->GetEntity());
		}		
	}
}


//------------------------------------------------------------------------------
// CUISiegeWarfareNew::SendSiegewarfareRebirth()
// Explain: 
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::SendSiegewarfareRebirth(int tSubType)
{	
	CNetworkMessage nmRebirth(MSG_PC_REBIRTH);
	nmRebirth << (ULONG)0;
	nmRebirth << (UBYTE)tSubType;
	nmRebirth << (UBYTE)0;
	_pNetwork->SendToServerNew(nmRebirth);	
}


//------------------------------------------------------------------------------
// CUISiegeWarfareNew::SendConsensus()
// Explain: 
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::SendConsensus(UBYTE tSubType)
{	
	CNetworkMessage nmMessage(MSG_EXTEND);
	nmMessage << (ULONG)MSG_EX_CASTLE_WAR;
	nmMessage << (UBYTE)tSubType;
	nmMessage << (ULONG)_pNetwork->MyCharacterInfo.index;
	
	if (tSubType == MSG_CASTLE_CRISTAL_RESPOND_START)
	{
		nmMessage << _pTimer->GetHighPrecisionTimer().GetMilliseconds();
	}

	_pNetwork->SendToServerNew(nmMessage);
}
//------------------------------------------------------------------------------
// CUISiegeWarfareNew::SendRequestTowerSet()
// Explain: 
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::SendRequestTowerSet()
{	
	CNetworkMessage nmMessage(MSG_EXTEND);
	nmMessage << (ULONG)MSG_EX_CASTLE_WAR;
	nmMessage << (UBYTE)MSG_CASTLE_TOWER_CONTRAL_LIST;	
	_pNetwork->SendToServerNew(nmMessage);
}
//------------------------------------------------------------------------------
// CUISiegeWarfareNew::SendApplyTowerSet()
// Explain: 
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::SendApplyTowerSet()
{	
	CNetworkMessage nmMessage(MSG_EXTEND);
	nmMessage << (ULONG)MSG_EX_CASTLE_WAR;
	nmMessage << (UBYTE)MSG_CASTLE_TOWER_CONTRAL;
	
	SetCBFromTowerSet();
	for(int i=0;i<DRATAN_TOWER_KIND_MAX;i++)
	{
		nmMessage << (UBYTE)m_cTowerSet[i];
	}

	_pNetwork->SendToServerNew(nmMessage);
}
//------------------------------------------------------------------------------
// CUISiegeWarfareNew::SendTowerReinforce()
// Explain: 
//------------------------------------------------------------------------------
void  CUISiegeWarfareNew::SendTowerReinforce(int iType,int iLevel)
{
	CNetworkMessage nmMessage(MSG_EXTEND);
	nmMessage << (ULONG)MSG_EX_CASTLE_WAR;
	nmMessage << (UBYTE)MSG_CASTLE_TOWER_REINFORCE;
	nmMessage << (UBYTE)iType << (UBYTE)iLevel;
	_pNetwork->SendToServerNew(nmMessage);
}
//------------------------------------------------------------------------------
// CUISiegeWarfareNew::SendTowerStateRequest()
// Explain: 
//------------------------------------------------------------------------------
void  CUISiegeWarfareNew::SendTowerStateRequest(int tType)
{
	CNetworkMessage nmMessage(MSG_EXTEND);
	nmMessage << (ULONG)MSG_EX_CASTLE_WAR;
	nmMessage << (UBYTE)MSG_CASTLE_TOWER_REINFORCE_LIST;
	nmMessage << (UBYTE)tType;
	_pNetwork->SendToServerNew(nmMessage);
}
//------------------------------------------------------------------------------
// CUISiegeWarfareNew::SendTowerRepair()
// Explain: 
//------------------------------------------------------------------------------
void  CUISiegeWarfareNew::SendTowerRepair(int tIdx)
{
	CNetworkMessage nmMessage(MSG_EXTEND);
	nmMessage << (ULONG)MSG_EX_CASTLE_WAR;
	nmMessage << (UBYTE)MSG_CASTLE_TOWER_REPAIRE;
	nmMessage << (ULONG)tIdx;
	_pNetwork->SendToServerNew(nmMessage);
}

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::SendTowerRepairStateRequest()
// Explain: 
//------------------------------------------------------------------------------
void  CUISiegeWarfareNew::SendTowerRepairStateRequest(int tIdx)
{
	CNetworkMessage nmMessage(MSG_EXTEND);
	nmMessage << (ULONG)MSG_EX_CASTLE_WAR;
	nmMessage << (UBYTE)MSG_CASTLE_TOWER_REPAIRE_LIST;
	nmMessage << (ULONG)tIdx;
	_pNetwork->SendToServerNew(nmMessage);
}


//------------------------------------------------------------------------------
// CUISiegeWarfareNew::SendDratanPortalMessage()
// Explain: 
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::SendDratanPortalMessage( int iMobIndex )
{
	CNetworkMessage nmMessage(MSG_EXTEND);
	nmMessage << (ULONG)MSG_EX_CASTLE_WAR;
	nmMessage << (UBYTE)MSG_CASTLE_TOWER_WARP_LIST;
	nmMessage << (ULONG)iMobIndex;
	_pNetwork->SendToServerNew(nmMessage);
}

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::SendBuyQuarter()
// Explain: 
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::SendBuyQuarter(int iNpcIdx)
{
	CNetworkMessage nmMessage(MSG_EXTEND);
	nmMessage << (ULONG)MSG_EX_CASTLE_WAR;
	nmMessage << (UBYTE)MSG_CASTLE_QUARTERS_INSTALL;
	nmMessage << (ULONG)iNpcIdx;
	_pNetwork->SendToServerNew(nmMessage);
}


//------------------------------------------------------------------------------
// CUISiegeWarfareNew::SetTowerSetFromCB()
// Explain: 
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::SetTowerSetFromCB()
{
	for(int i=0;i<DRATAN_TOWER_KIND_MAX;i++)
	{
		for(int j=0;j<DRATAN_TOWER_MAX;j++)
		{
			if(m_cbtnTowerOn[i][j].IsChecked())
			{
				m_cTowerSet[i] = j+1;
			}
		}
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::SetCBFromTowerSet()
// Explain: 
//------------------------------------------------------------------------------
void CUISiegeWarfareNew::SetCBFromTowerSet()
{
	for(int i=0;i<DRATAN_TOWER_KIND_MAX;i++)
	{
		for(int j=0;j<DRATAN_TOWER_MAX;j++)
		{
			if(m_cTowerSet[i] > j )
				m_cbtnTowerOn[i][j].SetCheck(TRUE);
			else 
				m_cbtnTowerOn[i][j].SetCheck(FALSE);
		}
	}
}

//------------------------------------------------------------------------------
// CUISiegeWarfareNew::CheckCBMouseMessage()
// Explain: 
//------------------------------------------------------------------------------
WMSG_RESULT CUISiegeWarfareNew::CheckCBMouseMessage(MSG *pMsg)
{
	int i=0;
	int j=0;
	for(;i< DRATAN_TOWER_KIND_MAX;i++)
	{
		j = m_cTowerSet[i];
		for( ;j<DRATAN_TOWER_MAX;j++)
		{
			
			if( m_cbtnTowerOn[i][j].MouseMessage(pMsg) != WMSG_FAIL )
			{				
				if ( j>0)
				{
					if( !m_cbtnTowerOn[i][j-1].IsChecked())
					{
						m_cbtnTowerOn[i][j].SetCheck(FALSE);						
					}
				}				
				return WMSG_SUCCESS;
			}
		}

	}
	return WMSG_FAIL;
}

SQUAD CUISiegeWarfareNew::GetTowerPay() 
{
	SQUAD tTotalNas=0;
	for(int i=0 ;i< DRATAN_TOWER_KIND_MAX;i++)
	{
		for( int j=0;j<DRATAN_TOWER_MAX;j++)
		{
			if( m_cbtnTowerOn[i][j].IsChecked())
			{
				tTotalNas += TOWER_USE_NAS*(j+1);
			}
		}
	}
	return 	tTotalNas;
}

SQUAD CUISiegeWarfareNew::GetTowerUpgradePay(int tType,int tLevel) 
{
	SQUAD tTotalNas=0;
	if( tType == SWUT_GATE && tLevel == 1)
		tTotalNas += TOWER_USE_NAS*2;	
	else
		tTotalNas += TOWER_USE_NAS*tLevel;
	
	return 	tTotalNas;
}

void CUISiegeWarfareNew::SetUpgradePos(INDEX tPos)
{
	m_sbtnUpgrade.SetSelectPos( tPos);
}

void CUISiegeWarfareNew::SetRepairMoney(int tIdx ,SQUAD tMoney)
{
	m_iRepairTowerIndex = tIdx;
	m_iRepairMoney = tMoney;	
}

// Rebirth Quarters
void CUISiegeWarfareNew::CreateWaitQuarterBox()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( pUIManager->DoesMessageBoxExist( MSGCMD_SIEGE_WARFARE_BUY_QUARTER )) return;			
	
	CUIMsgBox_Info	MsgBoxInfo;	
	CTString		strMessage;

	// TODO :: ��� �ð��� ǥ���ؾ� �ϹǷ� ���� UI ������ �ҵ�....
	MsgBoxInfo.SetMsgBoxInfo(  _S( 3734, "���� �� ��Ȱ ��� �ð�" ), NULL , UI_SIEGE_WARFARE_NEW, MSGCMD_SIEGE_WARFARE_BUY_QUARTER );	
	strMessage = _S( 3735, "��Ȱ ��� ��..." );
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );	
	
}

void CUISiegeWarfareNew::CreateBuyQuarterBox(int iNpcIdx)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	m_iNpcIdx = 0;

	if( iNpcIdx < 390 || iNpcIdx > 399 )
		return;

	if( pUIManager->DoesMessageBoxExist( MSGCMD_SIEGE_WARFARE_WAIT_QUARTER )) return;

	m_iNpcIdx = iNpcIdx;
		
	int tNas=0;	
	CUIMsgBox_Info	MsgBoxInfo;	
	CTString		strMessage;

	if ( iNpcIdx == 390  ) tNas = TOWER_USE_NAS*3;
	if ( iNpcIdx >= 391 && iNpcIdx <= 394 ) tNas = TOWER_USE_NAS*2;
	if ( iNpcIdx >= 395 && iNpcIdx <= 399 ) tNas = TOWER_USE_NAS;

	MsgBoxInfo.SetMsgBoxInfo(  _S( 3736, "��Ȱ���� ����" ), UMBS_YESNO , UI_SIEGE_WARFARE_NEW, MSGCMD_SIEGE_WARFARE_WAIT_QUARTER );	
	strMessage.PrintF( _S( 3737, "��Ȱ ���� %d"), iNpcIdx - 389 );
	MsgBoxInfo.AddString( strMessage );
	strMessage.PrintF("%d",tNas);
	strMessage.PrintF(_S( 255, "���� : %s"), strMessage);
	MsgBoxInfo.AddString( strMessage );
	strMessage=_S( 3738, "������ ��Ȱ������ �����Ͻðڽ��ϱ�?");
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );

}

	
// ----------------------------------------------------------------------------
// Name : MsgBoxCommand()
// Desc :
// ----------------------------------------------------------------------------
void CUISiegeWarfareNew::MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput )
{
	if(bOK) 
	{
		switch( nCommandCode )
		{		
			case MSGCMD_SIEGE_WARFARE_WAIT_QUARTER:
				SendBuyQuarter(m_iNpcIdx);
				break;

			case MSGCMD_SIEGEWARFARE_REBIRTH:
				// ����� ���� �������� ��Ȱ
				// WSS_DRATAN_SIEGEWARFARE 2007/10/11
				if( _pNetwork->MyCharacterInfo.sbJoinFlagDratan == WCJF_OWNER ||
					_pNetwork->MyCharacterInfo.sbJoinFlagDratan == WCJF_DEFENSE_GUILD )
					SendSiegewarfareRebirth(0);
				else 
					SendSiegewarfareRebirth(1);
				
				break;
		}
	}		
}
