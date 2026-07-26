// UIReformSystem.cpp: implementation of the CUIReformSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdh.h"
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIReformSystem.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Interface/UIMessenger.h>
#include <Engine/Contents/Base/UIMsgBoxNumeric_only.h>
#include <Engine/Loading.h>
#include <Engine/Info/MyInfo.h>
// ���α׷��� �� �߰� [9/12/2012 Ranma]
static BOOL	m_bProcessing = FALSE;

enum REFORM_MENU
{
	REFORM_HIGH = 1,
	REFORM_LOW,
#ifdef PREMIUM_REFORMER_11072021
	REFORM_MEGA,
#endif
	REFORM_END
};

#define	DEF_TOOLTIP_GAP		10

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

class CmdReformPutOnItem : public Command
{
public:
	CmdReformPutOnItem() : m_pWnd(NULL), m_bOk(false) {}
	void setData(CUIReformSystem* pWnd, bool bOk)	{	m_pWnd = pWnd; m_bOk = bOk;	}
	void execute()
	{
		if (m_pWnd != NULL)
		{
			if (m_bOk == true)
				m_pWnd->MagnifierPutOnCallBack();
			else
				m_pWnd->MagnifierPutOnCancelCallBack();
		}
	}
private:
	CUIReformSystem* m_pWnd;
	bool m_bOk;
};

CUIReformSystem::CUIReformSystem()
	: m_pItemsPrev(NULL)
{

}

CUIReformSystem::~CUIReformSystem()
{
	Destroy();

	STOCK_RELEASE(m_ptdButtonTexture);
	int		i;

	for (i = 0 ; i < eSLOT_MAX; i++)
		SAFE_DELETE(m_pIconsItem[i]);

	for (i = 0; i < 2; ++i)
		SAFE_DELETE(m_pTooltip[i]);

	SAFE_DELETE(m_pItemsPrev);
}

void CUIReformSystem::Create(CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight)
{
	CUIWindow::Create(pParentWnd, nX, nY, nWidth, nHeight);

	m_nOrgWidth = nWidth;
	m_nOrgHeight = nHeight;
	m_nWidth = 172;
	m_nHeight = 248;
	m_nMiddleGap = 30;

	// create texture.
	m_ptdBaseTexture = CreateTexture( CTString( "Data\\Interface\\SocketSystem.tex" ) );
	m_ptdButtonTexture = CreateTexture( CTString( "Data\\Interface\\CommonBtn.tex" ) );
	
	//texture size
	FLOAT	fTexWidth = m_ptdBaseTexture->GetPixWidth();
	FLOAT	fTexHeight = m_ptdBaseTexture->GetPixHeight();

	m_rtTop.SetUV(0,0,172, 37, fTexWidth, fTexHeight);
	m_rtMiddle.SetUV(0,37, 172, 220, fTexWidth, fTexHeight);
	m_rtBottom.SetUV(0, 190, 172, 229, fTexWidth, fTexHeight );
	m_rtItemSlot.SetUV( 412, 172, 412 + BTN_SIZE+ 2, 172 + BTN_SIZE + 2, fTexWidth, fTexHeight );

	//set size of title.
	m_rcTitle.SetRect(0, 0, REFORM_UI_FRAME_WIDTH, REFORM_UI_FRAME_TITLE);

	//set rect size.
	SetUIRect();
	//���� UI texture ������ ����
	m_rtsReform.AddRectSurface( UIRect(0,0,REFORM_UI_INNERFRAME_WIDTH, REFORM_UI_INNERFRAME_HEIGHT),
							    UIRectUV(REFORM_UI_TEX_CREATE_X, REFORM_UI_TEX_CREATE_Y,
										 REFORM_UI_TEX_CREATE_X+REFORM_UI_INNERFRAME_WIDTH,
										 REFORM_UI_TEX_CREATE_Y+REFORM_UI_INNERFRAME_HEIGHT,
										 fTexWidth,fTexHeight) );

	//set button texture.
	fTexWidth = m_ptdButtonTexture->GetPixWidth();
	fTexHeight = m_ptdButtonTexture->GetPixHeight();

	//close button
	m_btnClose.Create(this,CTString(""),148 ,4 ,16 ,16);
	// ��ư ����
	m_btnClose.SetUV(UBS_IDLE,211, 33, 227, 49, fTexWidth, fTexHeight);
	m_btnClose.SetUV(UBS_CLICK,229, 33, 245, 49, fTexWidth, fTexHeight);
	m_btnClose.CopyUV(UBS_IDLE,UBS_ON);
	m_btnClose.CopyUV(UBS_IDLE,UBS_DISABLE);

	//set button pos
	UIRect rcLeft, rcMiddle, rcRight;
	UIRectUV3 rtIdleBtn, rtClickBtn;
	rcLeft.SetRect(0, 0, 14, 21);
	rcMiddle.SetRect(14, 0, 78, 21);
	rcRight.SetRect(78, 0, 92, 21);
	
	rtIdleBtn.SetUV3(113, 0, 127, 22, 127, 0, 168, 22, 168, 0, 183, 22, fTexWidth, fTexHeight );
	rtClickBtn.SetUV3(187, 0, 201, 22, 201, 0, 242, 22, 242, 0, 256, 22, fTexWidth, fTexHeight);
	
	m_btnConfirm.Create( this, _S(5763,"����" ),(REFORM_UI_FRAME_WIDTH/2)-46, m_nHeight - 60, 92, 21 );
	m_btnConfirm.SetRTSurface( UBS_IDLE, rcLeft, rtIdleBtn.rtL );
	m_btnConfirm.SetRTSurface( UBS_IDLE, rcMiddle, rtIdleBtn.rtM );
	m_btnConfirm.SetRTSurface( UBS_IDLE, rcRight, rtIdleBtn.rtR );
	m_btnConfirm.SetRTSurface( UBS_CLICK, rcLeft, rtClickBtn.rtL );
	m_btnConfirm.SetRTSurface( UBS_CLICK, rcMiddle, rtClickBtn.rtM );
	m_btnConfirm.SetRTSurface( UBS_CLICK, rcRight, rtClickBtn.rtR );
	m_btnConfirm.CopyRTSurface( UBS_IDLE, UBS_ON );
	m_btnConfirm.CopyRTSurface( UBS_IDLE, UBS_DISABLE );
	m_btnConfirm.SetNewType(TRUE);

	int		i;

	for (i = 0 ; i < eSLOT_MAX; i++)
	{
		m_pIconsItem[i] = new CUIIcon;
		m_pIconsItem[i]->Create(this, 0, 0, BTN_SIZE, BTN_SIZE, UI_REFORM_SYSTEM, UBET_ITEM);
	}

	m_btnConfirm.SetEnable(FALSE);

	m_nReformType = 4;

	//���α׷��� �� �߰� [9/12/2012 Ranma]
	m_pbBar.Create( this, nX+6, nY+214, 172-6*2, 25);
 	m_pbBar.SetProgressRange( 0, 100 );
 	m_pbBar.SetProgressStep( 1 );
 	m_pbBar.OffsetProgressPos( 0 );
 	m_pbBar.SetAutoComplete( FALSE );

	// 5�ʿ� �ش��ϴ� timegettime() ��ġ.
	m_uEndTime = 1;
	m_pbBar.SetProgressRange( 0, m_uEndTime* 1000 );
	m_bUseTimer = FALSE;

	for (i = 0; i < 2; ++i)
	{
		m_pTooltip[i] = new CUITooltip;
		m_pTooltip[i]->initialize();
		m_pTooltip[i]->setParent(this);
	}
}

void CUIReformSystem::MsgBoxLCommand( int nCommandCode, int nResult )
{
	CUIManager* pUIManager = CUIManager::getSingleton();
//	BOOL bVisible = !(IsVisible());

	if ( nResult >= 0)	// reform UI�� ������ �Ҷ�.
	{
		if (pUIManager->GetInventory()->IsLocked() == TRUE ||
			pUIManager->GetInventory()->IsLockedArrange() == TRUE)
		{
			// �̹� Lock �� â�� ���� ��� ���� ���Ѵ�.
			pUIManager->GetInventory()->ShowLockErrorMessage();
			return;
		}
	}

	switch(nCommandCode)
	{
	case MSGLCMD_REFORM_SYSTEM:
		{
			// cancle
			if (nResult > 0)
			{
				if(nResult == REFORM_HIGH)
				{
					m_nReformType = 1; // ��� ����
				}
				else if(nResult == REFORM_LOW)
				{
					m_nReformType = 0; // �߱� ����
				
				}
			#ifdef PREMIUM_REFORMER_11072021
				else if (nResult == REFORM_MEGA)
				{
					m_nReformType = 2;
				}
			#endif
				///< �κ��丮â ���� ����ֱ�
				if(!pUIManager->GetInventory()->IsVisible())
					pUIManager->GetInventory()->ToggleVisible();
				SetItemButton();
				pUIManager->RearrangeOrder(UI_REFORM_SYSTEM, TRUE);			
				pUIManager->GetInventory()->Lock( TRUE, TRUE, LOCK_REFORMSYSTEM );
				Render();
			}	
		}
		break;
	}
}
void CUIReformSystem::OpenReformSystem(int iMobIndex, FLOAT fX, FLOAT fZ)
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	
	// ������ �޴��� �ٽ� Ŭ�� �ϰų� �̹� UI�� �� �ִ� ���¸� ����
	Close();

	if( pUIManager->DoesMessageBoxLExist(MSGLCMD_REFORM_SYSTEM) )
	{
		return;
	}

	CMobData* MD = CMobData::getData(iMobIndex);
	m_nNPCIndex = iMobIndex;
	m_fNPCPosX = fX;
	m_fNPCPosZ = fZ;

	if (CEntity* pEntity = INFO()->GetTargetEntity(eTARGET))
		m_nNPCVIdx = pEntity->GetNetworkID();

	pUIManager->CreateMessageBoxL(_S(5763,"����"), UI_REFORM_SYSTEM, MSGLCMD_REFORM_SYSTEM);

	CTString strNpcName = CMobData::getData(iMobIndex)->GetName();
	pUIManager->AddMessageBoxLString( MSGLCMD_REFORM_SYSTEM, TRUE, strNpcName, -1, 0xA3A1A3FF);
	pUIManager->AddMessageBoxLString( MSGLCMD_REFORM_SYSTEM, TRUE, _S(5764,"�����ۿ� �پ� �ִ� �ɼ��� ���� �� �� �ֽ��ϴ�."
																		"Ȳ�� ������� 1~100���� ���� �� �ֽ��ϴ�."
																		"�Ϻ� ���� �������� ���� �� �� �����ϴ�."
																		"���� �Ŀ� �ɼ��� �� ������ ���� �ֽ��ϴ�."), -1, 0xA3A1A3FF);
	CTString strMessage;
	strMessage.PrintF(_S(5765,"�߱� ����"));
	pUIManager->AddMessageBoxLString(MSGLCMD_REFORM_SYSTEM, FALSE, strMessage, REFORM_LOW);
	strMessage.PrintF(_S(5766,"��� ����"));
	pUIManager->AddMessageBoxLString(MSGLCMD_REFORM_SYSTEM, FALSE, strMessage, REFORM_HIGH);
#ifdef PREMIUM_REFORMER_11072021
	strMessage.PrintF(_S(8523, "����Ѵ�."));
	pUIManager->AddMessageBoxLString(MSGLCMD_REFORM_SYSTEM, FALSE, strMessage, REFORM_MEGA);
#endif
	strMessage.PrintF(_S(1220,"����Ѵ�."));
	pUIManager->AddMessageBoxLString(MSGLCMD_REFORM_SYSTEM, FALSE, strMessage);

	m_pbBar.SetIdleText( _S( 4962, "�������� �÷��ּ���."), FALSE );
	m_pbBar.SetDoingText( _S( 5776, "������"), TRUE );
	m_pbBar.SetCompleteText( _S( 4970, "��ȭ�Ϸ�"), TRUE );
}
void CUIReformSystem::CommandTimer(pReq req, UINT _second /* = 5  */)
{
	// ���α׷��� �� �߰� [9/12/2012 Ranma]
	m_bProcessing = TRUE;
	this->m_fnReq = req;
	m_uEndTime = _second;
	m_bUseTimer = TRUE;
	m_pbBar.SetProgressPos( 0 );
	m_pbBar.StartProgress();
	m_uStartTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();

	CUIManager* pUIManager = CUIManager::getSingleton();
}

void CUIReformSystem::_calcCmdTimer()
{
	// ���α׷��� �� �߰� [9/12/2012 Ranma]
	if( m_bUseTimer )
	{
		m_btnConfirm.SetEnable(FALSE);

		__int64 tmpTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();
		if( tmpTime - m_uStartTime > ( m_uEndTime * 1000 ) )
		{
			(this->*m_fnReq)();
			m_bUseTimer = FALSE;
		}
		else 
			m_pbBar.OffsetProgressPos( (tmpTime - m_uStartTime) ); 
	}
}

void CUIReformSystem::SendReformReq()
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	LONG lReformerUniIndex;
	LONG lGoldUniIndex;
	LONG lReformItemUniIndex;

	CItems*	pItems0 = m_pIconsItem[eSLOT_REFORMER]->getItems();
	CItems*	pItems1 = m_pIconsItem[eSLOT_MAGNIFIER]->getItems();
	CItems*	pItems2 = m_pIconsItem[eSLOT_ITEM]->getItems();

	if (pItems0 == NULL || pItems1 == NULL || pItems2 == NULL)
		return;
	
	// ������ ���� �ε��� ��� [9/6/2012 Ranma]
	lReformerUniIndex = pUIManager->GetInventory()->GetItemUniIndex(pItems0->Item_Tab, 
		pItems0->InvenIndex);
	
	// Ȳ�� ������ ���� �ε��� ��� [9/6/2012 Ranma]
	lGoldUniIndex = pUIManager->GetInventory()->GetItemUniIndex(pItems1->Item_Tab, 
		pItems1->InvenIndex);
	
	// ������ ������ ���� �ε��� ��� [9/6/2012 Ranma]
	lReformItemUniIndex = pUIManager->GetInventory()->GetItemUniIndex(pItems2->Item_Tab, 
		pItems2->InvenIndex);
	
	// ���� ������ ���� ������ Ȯ�� [9/6/2012 Ranma]
	if (lReformerUniIndex	!= pItems0->Item_UniIndex || 
		lGoldUniIndex		!= pItems1->Item_UniIndex ||
		lReformItemUniIndex != pItems2->Item_UniIndex)
	{
		// ���� �޽����������� ���� �̵����� ���� ��ȭ�� üũ ������ �������� ��츦 ����Ͽ� �ٽ� üũ
		Close();
		return;
	}
	
	// ���� �޽��� ������ [9/5/2012 Ranma]	
	_pNetwork->SendReformItemReq( m_nReformType, 
		pItems0->Item_Tab, pItems0->InvenIndex,
		pItems1->Item_Tab, pItems1->InvenIndex, pItems1->Item_Sum,
		pItems2->Item_Tab, pItems2->InvenIndex, m_nNPCVIdx);
}


void CUIReformSystem::SetUIRect(const int nHeight)
{
	m_nHeightGap = nHeight;
	m_nHeight -= m_nHeightGap;
	m_rcTop.SetRect(0,0,172,37);
	m_rcMiddle.SetRect(0, 37, 172, 220);
	m_rcBottom.SetRect(0, 220 ,172, 248);

	m_rcReformSystemRect.SetRect(	0, 	0,	172, 248 );
}

void CUIReformSystem::Render()
{
	CUIManager* pUiManager = CUIManager::getSingleton();

	// ���� Ȱ��ȭ�� �Ϻ� ��ȣ�ۿ� �ź� [9/25/2012 Ranma]
	pUiManager->InteractionMsgBoxReject();

	// ���α׷����� �߰� [9/12/2012 Ranma]
	_calcCmdTimer();

	m_btnConfirm.SetText( _S(5763, "����") );

	int nX, nY;
	GetAbsPos(nX, nY);

	if(m_fNPCPosX >= 0.0f && m_fNPCPosZ >= 0.0f)
	{
		FLOAT	fDiffX = _pNetwork->MyCharacterInfo.x - m_fNPCPosX;
		FLOAT	fDiffZ = _pNetwork->MyCharacterInfo.z - m_fNPCPosZ;
		if( fDiffX * fDiffX + fDiffZ * fDiffZ > 100.0f )
		{
			Close();
		}
	}

	CDrawPort*	pDrawPort = pUiManager->GetDrawPort();

	pDrawPort->InitTextureData(m_ptdBaseTexture);
	pDrawPort->AddTexture( nX+m_rcTop.Left, nY+m_rcTop.Top, nX+m_rcTop.Right, nY+m_rcTop.Bottom,
		m_rtTop.U0, m_rtTop.V0, m_rtTop.U1, m_rtTop.V1, 0xFFFFFFFF );
	pDrawPort->AddTexture( nX+m_rcMiddle.Left, nY+m_rcMiddle.Top, nX+m_rcMiddle.Right, nY+m_rcMiddle.Bottom,
		m_rtMiddle.U0, m_rtMiddle.V0, m_rtMiddle.U1, m_rtMiddle.V1, 0xFFFFFFFF );
	pDrawPort->AddTexture( nX+m_rcBottom.Left, nY+m_rcBottom.Top, nX+m_rcBottom.Right, nY+m_rcBottom.Bottom,
										m_rtBottom.U0, m_rtBottom.V0, m_rtBottom.U1, m_rtBottom.V1, 0xFFFFFFFF );
	pDrawPort->FlushRenderingQueue();

	// button render
	pDrawPort->InitTextureData(m_ptdButtonTexture);
	m_btnClose.Render();
	m_btnConfirm.Render();
//	m_btnConfirm.RenderHighlight(0x11111111);
	pDrawPort->FlushRenderingQueue();

	CTString strTemp;
	//COLOR	 colStrTemp;
	if(m_nReformType == 1)
	{
		strTemp =  _S(5766,"��� ����");
	}
	else if(m_nReformType == 0)
	{
		strTemp =  _S(5765,"�߱� ����");
	}
	#ifdef PREMIUM_REFORMER_11072021
	else if (m_nReformType == 2)
	{
		strTemp = _S(8523, "");
	}
	#endif
	pDrawPort->PutTextExCX(strTemp, m_nPosX+REFORM_UI_FRAME_WIDTH/2, m_nPosY+18, 0xDED9A0FF);
	pDrawPort->EndTextEx();
	
	pDrawPort->InitTextureData( m_ptdBaseTexture );
	m_rtsReform.SetPos( m_nPosX + REFORM_UI_FRAME_BORDER, m_nPosY + REFORM_UI_FRAME_TITLE + REFORM_UI_FRAME_BORDER );
	m_rtsReform.RenderRectSurface( pDrawPort, 0xFFFFFFFF );
	pDrawPort->FlushRenderingQueue();

	// ������ ��ư ��׶��� ȸ�� ó�� [9/13/2012 Ranma]
	CItemData* pItemDataBotton0 = _pNetwork->GetItemData( 9005 );
	CItemData* pItemDataBotton1 = _pNetwork->GetItemData( 1839 );
	UIRectUV	rectBotton0UV, rectBotton1UV;

	rectBotton0UV.SetUV(pItemDataBotton0->GetIconTexCol() * BTN_SIZE,
		pItemDataBotton0->GetIconTexRow() * BTN_SIZE,
		(pItemDataBotton0->GetIconTexCol()+1) * BTN_SIZE,
		(pItemDataBotton0->GetIconTexRow()+1) * BTN_SIZE,
		_pUIBtnTexMgr->GetTexWidth( UBET_ITEM, pItemDataBotton0->GetIconTexID() ),
		_pUIBtnTexMgr->GetTexHeight( UBET_ITEM, pItemDataBotton0->GetIconTexID() ) );

	rectBotton1UV.SetUV(pItemDataBotton1->GetIconTexCol() * BTN_SIZE,
		pItemDataBotton1->GetIconTexRow() * BTN_SIZE,
		(pItemDataBotton1->GetIconTexCol()+1) * BTN_SIZE,
		(pItemDataBotton1->GetIconTexRow()+1) * BTN_SIZE,
		_pUIBtnTexMgr->GetTexWidth( UBET_ITEM, pItemDataBotton1->GetIconTexID() ),
		_pUIBtnTexMgr->GetTexHeight( UBET_ITEM, pItemDataBotton1->GetIconTexID() ) );

	pDrawPort->AddBtnTexture(	pItemDataBotton0->GetIconTexID(),
		nX + m_pIconsItem[eSLOT_REFORMER]->GetPosX() , nY + m_pIconsItem[eSLOT_REFORMER]->GetPosY(), 
		nX + m_pIconsItem[eSLOT_REFORMER]->GetPosX() + BTN_SIZE , nY + m_pIconsItem[eSLOT_REFORMER]->GetPosY() + BTN_SIZE,
		rectBotton0UV.U0, rectBotton0UV.V0,
		rectBotton0UV.U1, rectBotton0UV.V1, 0x404040FF );
	
	pDrawPort->AddBtnTexture(	pItemDataBotton1->GetIconTexID(),
		nX + m_pIconsItem[eSLOT_MAGNIFIER]->GetPosX() , nY + m_pIconsItem[eSLOT_MAGNIFIER]->GetPosY(), 
		nX + m_pIconsItem[eSLOT_MAGNIFIER]->GetPosX() + BTN_SIZE , nY + m_pIconsItem[eSLOT_MAGNIFIER]->GetPosY() + BTN_SIZE,
		rectBotton1UV.U0, rectBotton1UV.V0,
		rectBotton1UV.U1, rectBotton1UV.V1, 0x404040FF );
	
	pDrawPort->FlushBtnRenderingQueue( UBET_ITEM );
	
	// ���α׷��� �� �߰� [9/12/2012 Ranma]
	m_pbBar.Render();
	pDrawPort->FlushRenderingQueue();


	for(int i = 0; i < eSLOT_MAX; i++)
	{
		if(m_pIconsItem[i]->IsEmpty())
			continue;
		m_pIconsItem[i]->Render(pDrawPort);
	}

	m_pTooltip[0]->Render(pDrawPort);
	m_pTooltip[1]->Render(pDrawPort);
}
void CUIReformSystem::SetItemButton()
{
	for(int i = 0 ; i < eSLOT_MAX; i++)
	{
		m_pIconsItem[i]->clearIconData();
	}

	m_pIconsItem[eSLOT_REFORMER]->SetPos(REFORM_UI_FRAME_BORDER + 22, REFORM_UI_FRAME_TITLE + REFORM_UI_FRAME_BORDER + 6);
	m_pIconsItem[eSLOT_MAGNIFIER]->SetPos(REFORM_UI_FRAME_BORDER + 106, REFORM_UI_FRAME_TITLE + REFORM_UI_FRAME_BORDER + 6);
	m_pIconsItem[eSLOT_ITEM]->SetPos(REFORM_UI_FRAME_BORDER + 64, REFORM_UI_FRAME_TITLE + REFORM_UI_FRAME_BORDER + 77);

	m_pTooltip[0]->Hide(TRUE);
	m_pTooltip[1]->Hide(TRUE);
}
void CUIReformSystem::ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}
void CUIReformSystem::AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}
void CUIReformSystem::Close()
{
	m_bUseTimer = FALSE;
	m_fnReq = NULL;
	m_bProcessing = FALSE; // ���α׷��� �� �߰� [9/12/2012 Ranma]
	m_fNPCPosX = 0.0f;
	m_fNPCPosZ = 0.0f;
	m_bPickTitle = FALSE;
	m_btnConfirm.SetEnable(FALSE);
	m_nReformType = 4;

	// ���α׷����� �߰� [9/12/2012 Ranma]
	m_pbBar.IdleProgress();
	m_pbBar.SetProgressPos( 0 );
	CUIManager* pUIManager = CUIManager::getSingleton();
	pUIManager->RearrangeOrder(UI_REFORM_SYSTEM, FALSE);
	pUIManager->GetInventory()->Lock(FALSE, FALSE, LOCK_REFORMSYSTEM);
	pUIManager->GetMsgBoxNumOnly()->CloseBox();
}
WMSG_RESULT	CUIReformSystem::MouseMessage(MSG *pMsg )
{
	WMSG_RESULT wmsgResult;
	static BOOL bTitleBarClick = FALSE;
	static int nOldX, nOldY;
	int nX = LOWORD(pMsg->lParam);
	int nY = HIWORD(pMsg->lParam);

	switch(pMsg->message)
	{
	case WM_MOUSEMOVE:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();
			if(IsInside(nX,nY))
				pUIManager->SetMouseCursorInsideUIs();

			int ndX = nX - nOldX;
			int ndY = nY - nOldY;

			if(m_bPickTitle && (pMsg->wParam & MK_LBUTTON))
			{
				nOldX = nX; nOldY = nY;
				Move(ndX,ndY);
				return WMSG_SUCCESS;
			}
			else if( m_btnClose.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else if( m_btnConfirm.MouseMessage( pMsg ) != WMSG_FAIL )
				return WMSG_SUCCESS;
			else
			{

				if(IsInsideRect(nX,nY,m_rcReformSystemRect))
				{
					for(int i = 0; i < eSLOT_MAX; i++)
					{
						m_pIconsItem[i]->MouseMessage(pMsg);						
					}					

					return WMSG_SUCCESS;
				}

				
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();
			if(IsInside(nX,nY))
			{
				nOldX = nX;		nOldY = nY;
				
				if( m_btnClose.MouseMessage( pMsg ) != WMSG_FAIL )
				{
				}
				else if( m_btnConfirm.MouseMessage( pMsg ) != WMSG_FAIL )
				{
				}
				else if(IsInsideRect(nX,nY,m_rcTitle))
				{
					m_bPickTitle = TRUE;
				}

				pUIManager->RearrangeOrder(UI_REFORM_SYSTEM,TRUE);
				return WMSG_SUCCESS;
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();
			m_bPickTitle = FALSE;
			
			if (pUIManager->GetDragIcon() == NULL)
			{
				if(!IsFocused())
					return WMSG_FAIL;
				if((wmsgResult = m_btnClose.MouseMessage(pMsg)) != WMSG_FAIL)
				{
					if(wmsgResult == WMSG_COMMAND)
					{
						Close();
					}
					return WMSG_SUCCESS;
				}
				else if((wmsgResult = m_btnConfirm.MouseMessage(pMsg)) != WMSG_FAIL)
				{
					if(wmsgResult == WMSG_COMMAND)
					{
						if(pUIManager->GetMsgBoxNumOnly()->IsOpen() == true)
						{
							// ���� �Է� �ڽ��� ��� ä�� ������ ���� �ϴ� ��츦 ���� [9/5/2012 Ranma]
							return WMSG_SUCCESS;
						}
						// ���α׷����� �߰� [9/12/2012 Ranma]
						m_pbBar.IdleProgress();
						m_pbBar.SetProgressPos( 0 );
						CommandTimer(&CUIReformSystem::SendReformReq);
						setPrevData(m_pIconsItem[eSLOT_ITEM]->getItems());
						return WMSG_SUCCESS;
					}
				}
			}
			else
			{
				if(IsInside(nX,nY))
				{
					CUIIcon* pDrag = pUIManager->GetDragIcon();

					CItems* pItems = pDrag->getItems();

					if (pItems == NULL)
						return WMSG_FAIL;

					pUIManager->GetMessenger()->SetDragging(false);
					if(IsInsideRect(nX,nY,m_rcReformSystemRect))
					{
						if (pDrag->getBtnType() == UBET_ITEM)
						{
							if (m_pIconsItem[eSLOT_REFORMER]->IsInside(nX, nY) == TRUE) // ������ ���� start////
							{
								CItemData* pItemData = _pNetwork->GetItemData(pDrag->getIndex());

								if ( m_nReformType == 0 && pItemData->GetType() == CItemData::ITEM_ETC &&
									pItemData->GetSubType() == CItemData::ITEM_ETC_REFORMER && 
									pItemData->GetNum0() == CItemData::ITEM_ETC_REFORMER_MID_GRADE)
								{
									m_pIconsItem[eSLOT_REFORMER]->copyItem(pDrag);									
								}
								else if ( m_nReformType == 1 && pItemData->GetType() == CItemData::ITEM_ETC &&
									pItemData->GetSubType() == CItemData::ITEM_ETC_REFORMER && 
									pItemData->GetNum0() == CItemData::ITEM_ETC_REFORMER_HIGH_GRADE)
								{
									m_pIconsItem[eSLOT_REFORMER]->copyItem(pDrag);
								}
							#ifdef PREMIUM_REFORMER_11072021
								else if ( m_nReformType == 2 && pItemData->GetType() == CItemData::ITEM_ETC &&
									pItemData->GetSubType() == CItemData::ITEM_ETC_REFORMER && 
									pItemData->GetNum0() == CItemData::ITEM_ETC_MEGA_REFORMER_GRADE)
								{
									m_pIconsItem[eSLOT_REFORMER]->copyItem(pDrag);
								}
							#endif
								else
								{
									// ���� �޽��� 2�� [9/3/2012 Ranma]
									pUIManager->GetChattingUI()->AddSysMessage( _S(5757,"������ ����� �����Ӱ� �ƴմϴ�."), SYSMSG_ERROR );
									m_pIconsItem[eSLOT_REFORMER]->clearIconData();
									pUIManager->ResetHoldBtn();
									return WMSG_FAIL;
								}
								
								if(!m_pIconsItem[eSLOT_MAGNIFIER]->IsEmpty() && !m_pIconsItem[eSLOT_ITEM]->IsEmpty())
										m_btnConfirm.SetEnable(TRUE);
								
							}//// ������ ���� end

							else if (m_pIconsItem[eSLOT_MAGNIFIER]->IsInside(nX,nY)) // Ȳ�� ������ ���� start////
							{
								CItemData* pItemData = pItems->ItemData;
								if(pItemData->GetItemIndex() == RARE_IDENTITY_ITEM2 &&
									pItemData->GetType() == CItemData::ITEM_ONCEUSE && pItemData->GetSubType() == CItemData::ITEM_SUB_ETC)
								{
									CUIMsgBoxNumericOnly* pMsgBoxNumOnly = pUIManager->GetMsgBoxNumOnly();

									if (pMsgBoxNumOnly->IsOpen() == true)
										pMsgBoxNumOnly->CloseBox();

									int nInitCount = pItems->Item_Sum;

									if (pItems->Item_Sum > 100)
										nInitCount = 100;

									CTString strMessage;
									strMessage.PrintF(_S(5756,"1ȸ ���� �� �� ���� Ȳ�� �����⸦ ��� �Ͻðڽ��ϱ�?"));

									CmdReformPutOnItem* pCmdOk = new CmdReformPutOnItem;
									pCmdOk->setData(this, true);

									CmdReformPutOnItem* pCmdCancel = new CmdReformPutOnItem;
									pCmdCancel->setData(this, false);

									pMsgBoxNumOnly->SetInfo(pCmdOk, _S(5763,"����"), strMessage, 1, (int)nInitCount, pCmdCancel);
									pMsgBoxNumOnly->InitData((int)nInitCount);

									{
										m_pIconsItem[eSLOT_MAGNIFIER]->cloneItem(pDrag);
										m_pIconsItem[eSLOT_MAGNIFIER]->setCount(nInitCount);
									}
								} 
								else
								{
									///< ���� �޽���
									// Ȳ�� �����⸸ ���� [9/3/2012 Ranma]
									pUIManager->GetChattingUI()->AddSysMessage( _S(5758,"Ȳ�� �����Ⱑ �ƴմϴ�."), SYSMSG_ERROR );
									pUIManager->ResetHoldBtn();
								}
							}/// Ȳ�� ������ ���� end//////

							else if(m_pIconsItem[eSLOT_ITEM]->IsInside(nX,nY)) // ��� ���� start///
							{
								CTString strMessage;
								CUIMsgBox_Info msgBoxInfo;
								CItemData* pItemData = pItems->ItemData;

								// ���� ������ ����
								if (pDrag->IsWearTab() == true)
								{
									pUIManager->GetChattingUI()->AddSysMessage( _S(4981,"���� ���� ������ �Դϴ�."), SYSMSG_ERROR );
									pUIManager->ResetHoldBtn();
									return WMSG_FAIL;
								}
									// ���� ��� ����. ��, �Ǽ��縮 [9/5/2012 Ranma]

								if(pItemData->GetFlag() & ITEM_FLAG_NOT_REFORM) // ���� ���� ���� üũ [9/11/2012 Ranma]
								{
									///< ���� �޽��� ���� �Ұ��� 4��
									pUIManager->GetChattingUI()->AddSysMessage( _S(5759,"���� ������ �������� �ƴմϴ�."), SYSMSG_ERROR );
									pUIManager->ResetHoldBtn();
									return WMSG_FAIL;
								}
								else
								{
									if( pItemData->GetType() == CItemData::ITEM_WEAPON
										|| pItemData->GetType() == CItemData::ITEM_SHIELD
										|| pItemData->GetType() == CItemData::ITEM_ACCESSORY )
									{
										
										if (m_nReformType == 0)
										{
											if (pItemData->IsFlag(ITEM_FLAG_RARE))
											{
												if (pItems->Item_RareIndex == 0) //�̰��� ��������� ����
												{
													pUIManager->GetChattingUI()->AddSysMessage( _S(5771,"�������� ���� ������ �Դϴ�."), SYSMSG_ERROR );
													m_pIconsItem[eSLOT_ITEM]->clearIconData();
													pUIManager->ResetHoldBtn();
													return WMSG_FAIL;
												}
											}										
											else 
											{
												pUIManager->GetChattingUI()->AddSysMessage( _S(5760,"�߱� �������� �ƴմϴ�."), SYSMSG_ERROR );
												m_pIconsItem[eSLOT_ITEM]->clearIconData();
												pUIManager->ResetHoldBtn();
												return WMSG_FAIL;
											}
										}
										else if (m_nReformType == 1)
										{
											if (pItemData->IsFlag(ITEM_FLAG_ORIGIN))
											{
											}
											else
											{
												pUIManager->GetChattingUI()->AddSysMessage( _S(5761,"���� �������� �ƴմϴ�."), SYSMSG_ERROR );
												m_pIconsItem[eSLOT_ITEM]->clearIconData();
												pUIManager->ResetHoldBtn();
												return WMSG_FAIL;
											}
										}
#ifdef PREMIUM_REFORMER_11072021
										else if (m_nReformType == 2)
										{
											if (pItemData->IsFlag(ITEM_FLAG_ORIGIN))
											{
											}
											else
											{
												pUIManager->GetChattingUI()->AddSysMessage(_S(8524, "���� �������� �ƴմϴ�."), SYSMSG_ERROR);
												m_pIconsItem[eSLOT_ITEM]->clearIconData();
												pUIManager->ResetHoldBtn();
												return WMSG_FAIL;
											}
										}
#endif
									}
									else
									{
										// ���� �� �Ǽ������� ������ �ٸ� ������ ���� [9/12/2012 Ranma]
										pUIManager->GetChattingUI()->AddSysMessage( _S(5759,"���� ������ �������� �ƴմϴ�."), SYSMSG_ERROR );
										pUIManager->ResetHoldBtn();
										return WMSG_FAIL;
									}
									// ������ ��Ͻ�
									m_pIconsItem[eSLOT_ITEM]->copyItem(pDrag);
									setPrevData(m_pIconsItem[eSLOT_ITEM]->getItems());

									if(!m_pIconsItem[eSLOT_MAGNIFIER]->IsEmpty() && !m_pIconsItem[eSLOT_REFORMER]->IsEmpty())
										m_btnConfirm.SetEnable(TRUE);
								}							
							}// ��� ���� end///
						}
					}
				}
				pUIManager->ResetHoldBtn();
				return WMSG_SUCCESS;
			}
		}
	case WM_LBUTTONDBLCLK:
		{
			CUIManager* pUIManager = CUIManager::getSingleton();
			if(IsInside(nX,nY))
			{
				pUIManager->RearrangeOrder(UI_REFORM_SYSTEM,TRUE);
				return WMSG_SUCCESS;
			}
		}
		break;
	case WM_MOUSEWHEEL:
		{
		}
		break;
	}
	return WMSG_FAIL;
}

void CUIReformSystem::MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput )
{
}

void CUIReformSystem::BtnSetItemCheckforPos()
{
	m_pTooltip[1]->Hide(FALSE);
	m_pTooltip[1]->SetItemData(m_pIconsItem[eSLOT_ITEM]->getItems());
	m_pTooltip[1]->SetPosX(GetWidth() + DEF_TOOLTIP_GAP);
}

void CUIReformSystem::SendReformItemBtnInitUniIndex(int uniindex)
{
	for(int i = 0; i < eSLOT_MAX; ++i)
	{
		if (m_pIconsItem[i]->getItems() != NULL && 
			m_pIconsItem[i]->getItems()->Item_UniIndex == uniindex)
		{
			m_pIconsItem[i]->clearIconData();
			m_btnConfirm.SetEnable(FALSE);
		}
	}
}


void CUIReformSystem::RecvReformSystemResult(CNetworkMessage* istr)
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	UCHAR type;
	
	(*istr) >> type;
	
	switch( type )
	{
	case MSG_EX_REFORMER_SYSTEM_NOT_GRADE_REP:
		{
			pUIManager->GetChattingUI()->AddSysMessage( _S(5757,"������ ����� �����Ӱ� �ƴմϴ�."), SYSMSG_ERROR );
		}
		break;
	case MSG_EX_REFORMER_SYSTEM_NOT_GOLD_MAGNIFIER_REP:
		{
			pUIManager->GetChattingUI()->AddSysMessage( _S(5758,"Ȳ�� �����Ⱑ �ƴմϴ�."), SYSMSG_ERROR );
		}
		break;
	case MSG_EX_REFORMER_SYSTEM_NOT_REFORM_ITEM_REP:
		{
			pUIManager->GetChattingUI()->AddSysMessage( _S(5759,"���� ������ �������� �ƴմϴ�."), SYSMSG_ERROR );
			m_pIconsItem[eSLOT_ITEM]->clearIconData();
		}
		break;
	case MSG_EX_REFORMER_SYSTEM_NOT_MID_ITEM_REP:
		{
			pUIManager->GetChattingUI()->AddSysMessage( _S(5760,"�߱� �������� �ƴմϴ�."), SYSMSG_ERROR );
			m_pIconsItem[eSLOT_ITEM]->clearIconData();
		}
		break;
	case MSG_EX_REFORMER_SYSTEM_NOT_HIGH_ITEM_REP:
		{
			pUIManager->GetChattingUI()->AddSysMessage( _S(5761,"���޾������� �ƴմϴ�."), SYSMSG_ERROR );
			m_pIconsItem[eSLOT_ITEM]->clearIconData();
		}
		break;
	case MSG_EX_REFORMER_SYSTEM_EXCEPTION_ERROR_REP:
		{
			//pUIManager->GetChattingUI()->AddSysMessage( _s("������ ����� �����Ӱ� �ƴմϴ�."), SYSMSG_ERROR );
		}
		break;
	case MSG_EX_REFORMER_SYSTEM_REFORM_SUCCESS_REP:
		{
			SWORD nTab, nIndex;
			SLONG itemIndex, itemUniIndex;
			SQUAD itemCount = 0;
			
			(*istr) >> nTab;
			(*istr) >> nIndex;
			
			(*istr) >> itemUniIndex;
			(*istr) >> itemIndex;

			if (IsVisible() == FALSE)
				return;

			// �����۹�ư�� ����
			
			// ���������� ����
			m_pTooltip[1]->SetItemData(m_pIconsItem[eSLOT_ITEM]->getItems());
			
			// ������ ����
			CItems*		pItems = pUIManager->GetInventory()->GetItems(m_pIconsItem[eSLOT_REFORMER]->getItems()->Item_UniIndex);
			
			if (pItems == NULL || pItems->IsEmptyItem())
			{
				m_pIconsItem[eSLOT_REFORMER]->clearIconData();
			}
			else
			{
				m_pIconsItem[eSLOT_REFORMER]->setCount(pItems->Item_Sum);
			}

			pItems = pUIManager->GetInventory()->GetItems(m_pIconsItem[eSLOT_MAGNIFIER]->getItems()->Item_UniIndex);
			
			// Ȳ�� ������ ����
			if (pItems == NULL || pItems->IsEmptyItem())
			{
				m_pIconsItem[eSLOT_MAGNIFIER]->clearIconData();
			}
			else
			{
				itemCount = pItems->Item_Sum;
				
				if (itemCount < m_pIconsItem[eSLOT_MAGNIFIER]->getItems()->Item_Sum)
				{
					m_pIconsItem[eSLOT_MAGNIFIER]->clearIconData();
				}
			}
			// ���α׷����� �߰� [9/12/2012 Ranma]
			CompleteProgress();
			m_bProcessing = FALSE;
			m_pTooltip[1]->Hide(FALSE);

			//�˾�â ��ġ ���� (��Ʈ ������ ���� üũ) 
			BtnSetItemCheckforPos();

			// ���� ��ư Ȱ��ȭ ���� [9/5/2012 Ranma]
			if ( m_pIconsItem[eSLOT_REFORMER]->IsEmpty() || m_pIconsItem[eSLOT_MAGNIFIER]->IsEmpty() || m_pIconsItem[eSLOT_ITEM]->IsEmpty() )
			{
				// ������ư ��Ȱ�� [9/5/2012 Ranma]
				m_btnConfirm.SetEnable(FALSE);
			}
			else
			{
				m_btnConfirm.SetEnable(TRUE);
			}
		}
		break;
	}
	
}

void CUIReformSystem::setPrevData( CItems* pItems )
{
	if (pItems == NULL)
		return;

	SAFE_DELETE(m_pItemsPrev);
	
	m_pItemsPrev = new CItems;
	memcpy(m_pItemsPrev, pItems, sizeof(CItems));
	m_pTooltip[0]->ClearData();//Cloud add Fix Reform bug tooltip
	m_pTooltip[0]->SetItemData(m_pItemsPrev);
	m_pTooltip[0]->SetPosX(-m_pTooltip[0]->GetWidth() - DEF_TOOLTIP_GAP);

	m_pTooltip[0]->Hide(FALSE);
	m_pTooltip[1]->Hide(TRUE);
}

void CUIReformSystem::MagnifierPutOnCallBack()
{
	SQUAD llData = UIMGR()->GetMsgBoxNumOnly()->GetData();

	if(llData && llData <= 100 && llData > 0)
	{
		if (llData <= m_pIconsItem[eSLOT_MAGNIFIER]->getItems()->Item_Sum)
		{
			// ������ �Է��� ���� �޾Ƽ� ǥ��
			m_pIconsItem[eSLOT_MAGNIFIER]->setCount(llData);
		}
	}
	else
	{
		///< ���� ó��
		UIMGR()->GetChattingUI()->AddSysMessage( _S(5762,"Ȳ�� ������ 1ȸ ��� ���� ������ 1~100 �Դϴ�."), SYSMSG_ERROR );
		m_pIconsItem[eSLOT_MAGNIFIER]->clearIconData();
		return;
	}

	// ���࿡ ������ ��ư�� ��� ��ư�� ä���� �ִٸ� ���� ��ư Ȱ��ȭ
	if(!m_pIconsItem[eSLOT_REFORMER]->IsEmpty() && !m_pIconsItem[eSLOT_ITEM]->IsEmpty())
		m_btnConfirm.SetEnable(TRUE);

	if (m_pIconsItem[eSLOT_MAGNIFIER]->IsEmpty())
		m_pIconsItem[eSLOT_MAGNIFIER]->setCount(llData);
}

void CUIReformSystem::MagnifierPutOnCancelCallBack()
{
	if (m_pIconsItem[eSLOT_MAGNIFIER]->IsEmpty() == true)
		return;

	m_pIconsItem[eSLOT_MAGNIFIER]->clearIconData();
	m_btnConfirm.SetEnable(FALSE);
}
