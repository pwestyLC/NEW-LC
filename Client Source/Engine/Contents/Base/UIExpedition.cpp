#include "stdh.h"

// 헤더정리. [12/2/2009 rumist]
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Contents/Base/UIExpedition.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Contents/Base/UIPartyNew.h>
#include <Engine/Object/ActorMgr.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/Base/Party.h>
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
#include <Engine/Help/Util_Help.h>
#include <Engine/Interface/UIInventory.h>
#endif
//-----------------------------------
class CmdManageClose : public Command
{
public:
	CmdManageClose() : pUI_(NULL) {}
	void setData(CUIExpManage* pUI)
	{ 
		pUI_ = pUI;
	}
	void execute()	{
		if (pUI_)	{
			pUI_->closeUI();
		}
	}
private:
	CUIExpManage*	pUI_;
};

//-----------------------------------
class CmdManageAdd : public Command
{
public:
	CmdManageAdd() : pUI_(NULL) {}
	void setData(CUIExpManage* pUI)
	{ 
		pUI_ = pUI;
	}
	void execute()	{
		if (pUI_)	{
			pUI_->PressAddBtn();
		}
	}
private:
	CUIExpManage*	pUI_;
};

//-----------------------------------
class CmdManageMenu : public Command
{
public:
	CmdManageMenu() : pUI_(NULL), nGroup_(0), nPos_(0) {}
	void setData(CUIExpManage* pUI, int nGroup, int nPos)
	{ 
		pUI_ = pUI;
		nGroup_ = nGroup;
		nPos_ = nPos;
	}
	void execute()	{
		if (pUI_)	{
			pUI_->ShowManageMenu(nGroup_, nPos_);
		}
	}
private:
	CUIExpManage*	pUI_;
	int nGroup_;
	int nPos_;
};

//-----------------------------------
class CmdDragBase : public Command
{
public:
	CmdDragBase() : pUI_(NULL), _pBase(NULL), nGroup_(0), nPos_(0) {}
	void setData(CUIExpManage* pUI, CUIBase* pBase, int nGroup, int nPos)	
	{
		pUI_ = pUI;
		_pBase = pBase;
		nGroup_ = nGroup;
		nPos_ = nPos;
	}
	void execute()
	{
		if (pUI_ != NULL)
		{
			if (pUI_->GetBtnMove() == false)
				return;

			pUI_->SetSelectBtnGroup(nGroup_);
			pUI_->SetSelectBtnPos(nPos_);

			if (_pBase != NULL)
				UIMGR()->SetHoldBtn(_pBase);
		}
	}
private:
	CUIExpManage* pUI_;
	CUIBase*	_pBase;
	int nGroup_;
	int nPos_;
};

// ----------------------------------
class CmdViewClose : public Command
{
public:
	CmdViewClose() : pUI_(NULL) {}
	void setData(CUIViewDetail* pUI)
	{ 
		pUI_ = pUI;
	}
	void execute()	{
		if (pUI_)	{
			pUI_->closeUI();
		}
	}
private:
	CUIViewDetail*	pUI_;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
class CmdEPDungeonClose : public Command//Cloud Expedition_Party_Dungeon
{
public:
	CmdEPDungeonClose() : pUI_(NULL) {}
	void setData(CUIExpeditionPartyDungeon* pUI)
	{
		pUI_ = pUI;
	}
	void execute() {
		if (pUI_) {
			pUI_->CloseUI();
		}
	}
private:
	CUIExpeditionPartyDungeon* pUI_;
};

class CmdSelectDungeon : public Command
{
public:
	CmdSelectDungeon() : pUI_(NULL), m_nSelectIndex(-1) {};
	void setData(CUIExpeditionPartyDungeon* pUI, int nSelectIndex) { pUI_ = pUI; m_nSelectIndex = nSelectIndex; }
	void execute()
	{
		if (pUI_)
		{
			pUI_->UpdateAmenddungeon(m_nSelectIndex);
			pUI_->UpdateInfoRank(m_nSelectIndex);
		}
	}

private:
	CUIExpeditionPartyDungeon* pUI_;
	int m_nSelectIndex;
};

class CmdEPDungeonJoin : public Command//Cloud Expedition_Party_Dungeon
{
public:
	CmdEPDungeonJoin() : pUI_(NULL), m_nSelectIndex(-1), m_ndifficulty(-1), m_nZone(-1) {};
	void setData(CUIExpeditionPartyDungeon* pUI, int nSelectIndex, int ndifficulty, int nZone) { pUI_ = pUI; m_nSelectIndex = nSelectIndex; m_ndifficulty = ndifficulty;	m_nZone = nZone; }
	void execute()
	{
		if (pUI_)
		{
			_pNetwork->ExpeditionTeamJoinReq(m_nSelectIndex, m_ndifficulty, m_nZone);
		}
	}

private:
	CUIExpeditionPartyDungeon* pUI_;
	int m_nSelectIndex;
	int m_ndifficulty;
	int m_nZone;
};

class CmdEPDungeonRecall : public Command//Cloud Expedition_Party_Dungeon
{
public:
	CmdEPDungeonRecall() : pUI_(NULL), m_nSelectIndex(-1) {};
	void setData(CUIExpeditionPartyDungeon* pUI, int nSelectIndex) { pUI_ = pUI; m_nSelectIndex = nSelectIndex; }
	void execute()
	{
		if (pUI_)
		{
			_pNetwork->ExpeditionTeamRecallReq(m_nSelectIndex);
		}
	}

private:
	CUIExpeditionPartyDungeon* pUI_;
	int m_nSelectIndex;
};

class CmdEPDungeonReward : public Command//Cloud Expedition_Party_Dungeon
{
public:
	CmdEPDungeonReward() : pUI_(NULL), m_nSelectIndex(-1), m_nZone(-1) {};
	void setData(CUIExpeditionPartyDungeon* pUI, int nSelectIndex, int nZone) { pUI_ = pUI; m_nSelectIndex = nSelectIndex; m_nZone = nZone; }
	void execute()
	{
		if (pUI_)
		{
			_pNetwork->ExpeditionTeamRewardReq(m_nSelectIndex, m_nZone);
			_pNetwork->MyCharacterInfo.cloud_partydgdata[m_nSelectIndex] = 0;
			pUI_->UpdateInfoRank(m_nSelectIndex);

		}
	}

private:
	CUIExpeditionPartyDungeon* pUI_;
	int m_nSelectIndex;
	int m_nZone;
};
#endif

CUIExpManage::CUIExpManage()
	: m_slDestIndex(-1)
	, m_slSeletedBtnGroup(-1)
	, m_slSeletedBtnPos(-1)
	, m_bCanUseBtn(true)
	, m_ptdMessageBoxTexture(NULL)
	, m_pMoveArea(NULL)
	, m_pstrTitle(NULL)
	, m_bDrag(false)
	, m_nOriX(0), m_nOriY(0)
	, m_nMouseX(0), m_nMouseY(0)
{
	m_strDestName = "";

	int i;
	for (i = 0; i < eGROUP_MAX; ++i)
	{
		m_pStrText[i] = NULL;
	}

	for (i = 0; i < eBTN_MAX; ++i)
	{
		m_pBtn[i] = NULL;
		m_pList[i] = NULL;
	}

	setInherit(false);
}

CUIExpManage::~CUIExpManage()
{
	Destroy();

	STOCK_RELEASE(m_ptdMessageBoxTexture);
}

BOOL CUIExpManage::SetCommand(SLONG slPosition, BOOL bIsMyGroup /* = FALSE */, BOOL bIsExpeditionLeader /* = FALSE */)
{
	BOOL	bRet	= FALSE;
	m_tpList.ResetAllStrings();

	switch(slPosition)
	{
	case MSG_EXPED_MEMBERTYPE_BOSS: //원정대장
		m_tpList.AddMenuList(_S(4578, "지휘관 위임"), 0xc2bac5FF, MANAGE_CONNAMD_CHANGE_LEADER);
		m_tpList.AddMenuList(_S(4579, "부대장 임명"), 0xc2bac5FF, MANAGE_CONNAMD_SET_SUBLEADER);
		m_tpList.AddMenuList(_S(4580, "부대장 임명 해제"), 0xc2bac5FF, MANAGE_CONNAMD_RESET_SUBLEADER);
		m_tpList.AddMenuList(_S(4581, "원정대 추방"), 0xc2bac5FF, MANAGE_CONNAMD_KICK_MEMBER);
		m_tpList.AddMenuList(_S(4582, "살펴보기"), 0xc2bac5FF, MANAGE_CONNAMD_VIEW_MEMBER);
		bRet		= TRUE;
		break;

	case MSG_EXPED_MEMBERTYPE_MBOSS: //원정부대장
		{
			if(!bIsExpeditionLeader) // 원정대 부대장은 원정대장을 살펴볼 수 없다
			{
				m_tpList.AddMenuList(_S(4582, "살펴보기"), 0xc2bac5FF, MANAGE_CONNAMD_VIEW_MEMBER);

				if(bIsMyGroup)	// 원정대 부대장은 자기 그룹만 추방 가능
				{
					m_tpList.AddMenuList(_S(4583, "원정대 추방"), 0xc2bac5FF, MANAGE_CONNAMD_KICK_MEMBER);
				}

				bRet		= TRUE;
			}
		}
		break;

	default:
		break;
	}

	return bRet;
}

void CUIExpManage::RunCommand(INDEX iCommand)
{
	CUIMsgBox_Info	MsgBoxInfo;
	CTString strMessage;

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch(iCommand)
	{
	case MANAGE_CONNAMD_CHANGE_LEADER:
		{
			//기존 메시지박스가 있으면 닫아준다
			if(pUIManager->DoesMessageBoxExist(MSGCMD_EXPEDITION_SET_BOSS))
				pUIManager->CloseMessageBox(MSGCMD_EXPEDITION_SET_BOSS);

			MsgBoxInfo.SetMsgBoxInfo( _S(4493, "원정대" ), UMBS_YESNO, UI_PARTY, MSGCMD_EXPEDITION_SET_BOSS );

			strMessage.PrintF( _S(4584, "%s님께 원정대장을 위임하시겠습니까?" ), m_strDestName );

			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;
	case MANAGE_CONNAMD_SET_SUBLEADER:
		{
			//기존 메시지박스가 있으면 닫아준다
			if(pUIManager->DoesMessageBoxExist(MSGCMD_EXPEDITION_SET_MBOSS))
				pUIManager->CloseMessageBox(MSGCMD_EXPEDITION_SET_MBOSS);

			MsgBoxInfo.SetMsgBoxInfo( _S(4493, "원정대" ), UMBS_YESNO, UI_PARTY, MSGCMD_EXPEDITION_SET_MBOSS );

			strMessage.PrintF( _S(4585, "%s님을 부대장으로 임명하시겠습니까?" ), m_strDestName );

			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;
	case MANAGE_CONNAMD_RESET_SUBLEADER:
		{
			//기존 메시지박스가 있으면 닫아준다
			if(pUIManager->DoesMessageBoxExist(MSGCMD_EXPEDITION_RESET_MBOSS))
				pUIManager->CloseMessageBox(MSGCMD_EXPEDITION_RESET_MBOSS);

			MsgBoxInfo.SetMsgBoxInfo( _S(4493, "원정대" ), UMBS_YESNO, UI_PARTY, MSGCMD_EXPEDITION_RESET_MBOSS );

			strMessage.PrintF( _S(4586, "%s님을 부대장에서 해임하시겠습니까?" ), m_strDestName );

			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;
	case MANAGE_CONNAMD_KICK_MEMBER:
		{
			//기존 메시지박스가 있으면 닫아준다
			if(pUIManager->DoesMessageBoxExist(MSGCMD_EXPEDITION_KICK))
				pUIManager->CloseMessageBox(MSGCMD_EXPEDITION_KICK);

			MsgBoxInfo.SetMsgBoxInfo( _S(4493, "원정대" ), UMBS_YESNO, UI_PARTY, MSGCMD_EXPEDITION_KICK );

			strMessage.PrintF( _S(4587, "%s님을 추방하시겠습니까?" ), m_strDestName );

			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;
	case MANAGE_CONNAMD_VIEW_MEMBER:
		{
			GAMEDATAMGR()->GetPartyInfo()->SendExpeditionViewDetail(m_slDestIndex, m_strDestName);
		}
		break;
	default:
		break;
	}
}

void CUIExpManage::ClearExpManage()
{
	m_slDestIndex = -1;
	m_slSeletedBtnGroup = -1;
	m_slSeletedBtnPos = -1;
	m_strDestName = "";
	m_bCanUseBtn = true;

	m_tpList.Hide();
}

void CUIExpManage::OnPostRender(CDrawPort* pDraw)
{
	if (IsVisible() == FALSE)
		return;

	pDraw->InitTextureData(m_ptdMessageBoxTexture);
	m_tpList.Render();
	pDraw->FlushRenderingQueue();
	pDraw->EndTextEx();
}

void CUIExpManage::initialize()
{
	m_ptdMessageBoxTexture = CreateTexture( CTString( "Data\\Interface\\MessageBox.tex" ) );
	float fTexWidth = m_ptdMessageBoxTexture->GetPixWidth();
	float fTexHeight = m_ptdMessageBoxTexture->GetPixHeight();

	m_tpList.m_rtBackUL.SetUV( 164, 45, 171, 63, fTexWidth, fTexHeight );
	m_tpList.m_rtBackUM.SetUV( 174, 45, 176, 63, fTexWidth, fTexHeight );
	m_tpList.m_rtBackUR.SetUV( 179, 45, 186, 63, fTexWidth, fTexHeight );
	m_tpList.m_rtBackML.SetUV( 164, 55, 171, 58, fTexWidth, fTexHeight );
	m_tpList.m_rtBackMM.SetUV( 174, 55, 176, 58, fTexWidth, fTexHeight );
	m_tpList.m_rtBackMR.SetUV( 179, 55, 186, 58, fTexWidth, fTexHeight );
	m_tpList.m_rtBackLL.SetUV( 164, 60, 171, 68, fTexWidth, fTexHeight );
	m_tpList.m_rtBackLM.SetUV( 174, 60, 176, 68, fTexWidth, fTexHeight );
	m_tpList.m_rtBackLR.SetUV( 179, 60, 186, 68, fTexWidth, fTexHeight );

	m_tpList.Create( NULL, 0,  0, 100, 200, _pUIFontTexMgr->GetLineHeight(), 6, 3, 1, TRUE, TRUE );
	m_tpList.SetScrollBar( FALSE );
	m_tpList.SetSelBar( 100, _pUIFontTexMgr->GetLineHeight()+2, 187, 46, 204, 61, fTexWidth, fTexHeight );
	m_tpList.SetOverColor( 0xF8E1B5FF );
	m_tpList.SetSelectColor( 0xF8E1B5FF );
	m_tpList.Hide();

	m_pMoveArea = (CUIImage*)findUI("move_area");

	int i;
	CTString strListID[eGROUP_MAX] = { "list_group1", "list_group2", "list_group3", "list_group4"};
	CTString strGroupTitleID[eGROUP_MAX] = { "str_group1", "str_group2", "str_group3", "str_group4"};
	CTString strTemp = "";

	for (i = 0; i < eGROUP_MAX; i++)
	{
		m_pList[i] = (CUIList*)findUI(strListID[i]);
		m_pStrText[i] = (CUIText*)findUI(strGroupTitleID[i]);

		if (m_pStrText[i] != NULL)
		{
			strTemp.PrintF(_S(4494, "그룹%d"), i + 1);
			m_pStrText[i]->SetText(strTemp);
		}
	}

	CTString strBtnID[eBTN_MAX] = { "btn_close", "btn_add", "btn_cancel" };
	for (i = 0; i < eBTN_MAX; ++i)
	{
		m_pBtn[i] = (CUIButton*)findUI(strBtnID[i]);
	}

	if (m_pBtn[eBTN_CLOSE] != NULL)
	{
		CmdManageClose* pCmd = new CmdManageClose;
		pCmd->setData(this);
		m_pBtn[eBTN_CLOSE]->SetCommandUp(pCmd);
	}

	if (m_pBtn[eBTN_ADD] != NULL)
	{
		CmdManageAdd* pCmd = new CmdManageAdd;
		pCmd->setData(this);
		m_pBtn[eBTN_ADD]->SetCommandUp(pCmd);
	}

	if (m_pBtn[eBTN_CANCEL] != NULL)
	{
		CmdManageClose* pCmd = new CmdManageClose;
		pCmd->setData(this);
		m_pBtn[eBTN_CANCEL]->SetCommandUp(pCmd);
	}
}

void CUIExpManage::UpdateUI()
{
	if (IsVisible() == FALSE)
		return;

	Party* pParty = GAMEDATAMGR()->GetPartyInfo();

	if (pParty == NULL)
		return;

	int i, j;

	for (i = 0; i < eGROUP_MAX; ++i)
	{
		if (m_pList[i] == NULL)
			return;
	}

	CUIListItem*	pItem = NULL;
	CUIImageArray*	pImageArr = NULL;
	CUIText*		pText = NULL;
	CUIImage*		pImg = NULL;

	for (i = 0; i < EXPEDITION_GROUP_MAX; ++i)
	{
		for (j = 0; j < EXPEDITION_MEMBER_PER_GROUP; ++j)
		{
			bool bEmpty = pParty->IsExpedetionDataExist(i, j);

			pItem = (CUIListItem*)m_pList[i]->GetListItem(j);

			if (pItem == NULL)
				continue;

			if (bEmpty == true)
			{
				pItem->Hide(FALSE);
				
				// 직책 아이콘
				pImageArr = (CUIImageArray*)pItem->findUI("ia_pos");

				if (pImageArr != NULL)
				{
					SBYTE sbPos = pParty->GetExpeditionMemberPosition(i, j);

					if (sbPos >= MSG_EXPED_MEMBERTYPE_NORMAL)
					{
						pImageArr->Hide(TRUE);
					}
					else if (sbPos >= 0)
					{
						pImageArr->Hide(FALSE);
						pImageArr->SetRenderIdx(sbPos);
					}					
				}

				BOOL bOnline = pParty->GetExpeditionMemberOnline(i, j);
				SBYTE Job = pParty->GetExpeditionMemberJob(i, j);
				int nWidth = 0;
				// 직업 HP 바
				pImageArr = (CUIImageArray*)pItem->findUI("ia_job");
				pImg = (CUIImage*)pItem->findUI("img_hpRect");

				if (pImageArr != NULL)
				{
					if (pImg != NULL)
					{
						nWidth = calcHpBar(i, j, pImg->GetWidth());
					}

					pImageArr->SetRenderIdx(Job);
					pImageArr->SetImageWidth(Job, nWidth);					
				}
				
				// 파티원 이름
				pText = (CUIText*)pItem->findUI("str_name");

				if (pText != NULL)
				{
					COLOR color = UIMGR()->GetParty()->GetJobStringColor(Job);
					CTString strTemp;
					strTemp.PrintF("(%d)", pParty->GetExpeditionMemberLevel(i, j));

					if (bOnline == FALSE)
					{
						 color = 0x777777FF;
						 strTemp.PrintF("(off)");
					}

					pText->SetText(pParty->GetExpeditionMemberName(i, j) + strTemp);
					pText->setFontColor(color);
				}
				
				{
					CmdManageMenu* pCmd = new CmdManageMenu;
					pCmd->setData(this, i, j);
					pItem->SetCommandR(pCmd);
				}

				{
					CmdDragBase* pCmd = new CmdDragBase;
					pCmd->setData(this, (CUIBase*)pItem, i, j);
					pItem->SetCommandDrag(pCmd);
				}				
			}
			else
			{
				pItem->Hide(TRUE);
			}
		}
	}

}

void CUIExpManage::openUI()
{
	SetVisible(TRUE);
	Hide(FALSE);

	UpdateUI();

	UIMGR()->RearrangeOrder(UI_EXPEDITION, TRUE);
}

void CUIExpManage::closeUI()
{
	SetVisible(FALSE);
	Hide(TRUE);

	UIMGR()->RearrangeOrder(UI_EXPEDITION, FALSE);
}

WMSG_RESULT CUIExpManage::OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_nMouseX = x;
	m_nMouseY = y;

	if( m_bDrag && ( pMsg->wParam & MK_LBUTTON ) )
	{
		int ndX = x - m_nOriX;
		int ndY = y - m_nOriY;

		m_nOriX = x;
		m_nOriY = y;

		Move( ndX, ndY );
		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	CUIManager::getSingleton()->SetMouseCursorInsideUIs();

	return WMSG_FAIL;
}

WMSG_RESULT CUIExpManage::OnLButtonDown( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if( m_pMoveArea && m_pMoveArea->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}

	CUIManager::getSingleton()->RearrangeOrder( UI_EXPEDITION, TRUE );

	return WMSG_FAIL;
}

WMSG_RESULT CUIExpManage::OnLButtonUp( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;


	if (UIMGR()->GetDragBase() != NULL)
	{
		Party* pParty = GAMEDATAMGR()->GetPartyInfo();
		int i, j;

		if (pParty == NULL)
			return WMSG_FAIL;
		
		CUIListItem* pItem = NULL;

		for (i = 0; i < EXPEDITION_GROUP_MAX; ++i)
		{
			for (j = 0; j < EXPEDITION_MEMBER_PER_GROUP; ++j)
			{
				if (m_pList[i] != NULL)
					pItem = (CUIListItem*)m_pList[i]->GetListItem(j);

				if (pItem == NULL)
					continue;

				if (pItem->IsInside(x, y) == TRUE)
				{
					if (pParty->IsExpedetionDataExist(i, j) == true)
					{
						CTString strTemp;

						if (pParty->GetExpeditionMemberOnline(i, j) == FALSE)
							strTemp.PrintF(_S(4590, "오프라인 멤버는 그룹을 이동할 수 없습니다."));
						else
							strTemp.PrintF(_S(4589, "이미 %s가 지정되어 있습니다."), pParty->GetExpeditionMemberName(i, j));

						UIMGR()->GetChattingUI()->AddSysMessage(strTemp);
					}
					else
					{
						SetBtnMove(false);
						pParty->SendChangeGroup(m_slSeletedBtnGroup, m_slSeletedBtnPos, i, j);
					}

					CUIManager::getSingleton()->ResetHoldBtn();
					return WMSG_SUCCESS;
				}
			}
		}
	}	

	CUIManager::getSingleton()->ResetHoldBtn();
	return WMSG_FAIL;
}

WMSG_RESULT CUIExpManage::MouseMessage( MSG *pMsg )
{
	int	nX = LOWORD( pMsg->lParam );
	int	nY = HIWORD( pMsg->lParam );

	switch( pMsg->message )
	{
	case WM_MOUSEMOVE:
		{
			if( IsInside( nX, nY ) )
				CUIManager::getSingleton()->SetMouseCursorInsideUIs();

			if(m_tpList.MouseMessage(pMsg) != WMSG_FAIL)
			{
				return WMSG_SUCCESS;
			}
		}
		break;

	case WM_LBUTTONDOWN:
		{
			if(m_tpList.MouseMessage(pMsg) != WMSG_FAIL)
			{
				INDEX iIndex = m_tpList.GetCurSel();
				RunCommand(m_tpList.GetCommandNum(iIndex));
				m_tpList.Hide();

				return WMSG_SUCCESS;
			}
			else
			{
				m_tpList.Hide();
			}
		}
		break;
	}	

	return CUIBase::MouseMessage(pMsg);
}

void CUIExpManage::PressAddBtn()
{
	CUIMsgBox_Info MsgBoxInfo;
	CTString strTemp;
	MsgBoxInfo.SetMsgBoxInfo( _S(4577, "대원추가"), UMBS_OKCANCEL | UMBS_INPUTBOX, UI_PARTY, MSGCMD_EXPEDITION_INVITE_BY_NAME);	
	MsgBoxInfo.AddString( _S(4588, "추가할 캐릭터의 이름을 입력해 주세요.") );

	UIMGR()->CreateMessageBox( MsgBoxInfo );
}

int CUIExpManage::calcHpBar( int nGroup, int nPos, int nWidth )
{
	Party* pParty = GAMEDATAMGR()->GetPartyInfo();

	if (pParty == NULL)
		return 0;

	if (m_pList[nGroup] == NULL)
		return 0;

	if (pParty->IsExpedetionDataExist(nGroup, nPos) == false)
		return 0;

	if (pParty->GetExpeditionMemberOnline(nGroup, nPos) == FALSE)
		return 0;

	FLOAT fRatio = 0.0f;
	fRatio = (FLOAT)pParty->GetExpeditionMemberHp(nGroup, nPos) / (FLOAT)pParty->GetExpeditionMemberMaxHp(nGroup, nPos);

	if (fRatio > 1.0f)
		fRatio = 1.0f;
	else if (fRatio < 0.0f)
		fRatio = 0.0f;

	int nCurValue = 0;
	nCurValue = nWidth * fRatio;

	return nCurValue;
}

void CUIExpManage::ShowManageMenu( int nGroup, int nPos )
{
	Party* pParty = GAMEDATAMGR()->GetPartyInfo();

	if (pParty == NULL)
		return;

	if(pParty->IsExpedetionDataExist(nGroup, nPos) == true)
	{
		m_tpList.SetPos(m_nMouseX, m_nMouseY);

		// 내정보 획득
		int slMyPosition = pParty->GetExpeditionMyPosition();
		int slMyGroup, slMyPos;
		pParty->SearchExpeditionMember(_pNetwork->MyCharacterInfo.index ,slMyGroup, slMyPos);

		//  상대 정보 획득
		BOOL bIsMyGroup = ( nGroup == slMyGroup );
		BOOL bIsExpeditionLeader = ( MSG_EXPED_MEMBERTYPE_BOSS == pParty->GetExpeditionMemberPosition(nGroup, nPos));
		m_strDestName = pParty->GetExpeditionMemberName(nGroup, nPos);
		m_slDestIndex = pParty->GetExpeditionMemberIndex(nGroup, nPos);

		if(SetCommand(slMyPosition, bIsMyGroup, bIsExpeditionLeader))
			m_tpList.Show();
		else
			m_tpList.Hide();
	}
	else
	{
		m_tpList.Hide();
	}
}

void CUIExpManage::UpdateMemberInfo( int nGroup, int nPos )
{
	if (IsVisible() == FALSE)
		return;

	Party* pParty = GAMEDATAMGR()->GetPartyInfo();

	if (pParty == NULL)
		return;

	if (m_pList[nGroup] == NULL)
		return;

	CUIListItem*	pItem = NULL;
	CUIImageArray*	pImageArr = NULL;
	CUIImage*		pImg = NULL;
	
	bool bEmpty = pParty->IsExpedetionDataExist(nGroup, nPos);
	pItem = (CUIListItem*)m_pList[nGroup]->GetListItem(nPos);

	if (pItem == NULL)
		return;
		
	if (bEmpty == true)
	{
		BOOL bOnline = pParty->GetExpeditionMemberOnline(nGroup, nPos);
	    SBYTE Job = pParty->GetExpeditionMemberJob(nGroup, nPos);
	    int nWidth = 0;
	    // 직업 HP 바
	    pImageArr = (CUIImageArray*)pItem->findUI("ia_job");
	    pImg = (CUIImage*)pItem->findUI("img_hpRect");

	    if (pImageArr != NULL)
	    {
	        if (pImg != NULL)
	        {
	            nWidth = calcHpBar(nGroup, nPos, pImg->GetWidth());
	        }

	        pImageArr->SetRenderIdx(Job);
	        pImageArr->SetImageWidth(Job, nWidth);
	    }
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CUIViewDetail::CUIViewDetail()
	: m_pIaBack(NULL)
	, m_pbtnClose(NULL)
	, m_pstrName(NULL)
	, m_pMoveArea(NULL)
{
	for (int i = 0; i < WEAR_TOTAL; i++)
	{
		m_pIcon[i] = NULL;
	}

	setInherit(false);
}

void CUIViewDetail::ClearViewDetail()
{
	m_sPetInfo.lIndex			= -1;
	m_sPetInfo.sbPetTypeGrade	= -1;
	m_sPetInfo.lLevel			= -1;
	m_sPetInfo.llExp			= -1;
	m_sPetInfo.llNeedExp		= -1;
	m_sPetInfo.lHP				= -1;
	m_sPetInfo.lMaxHP			= 0;
	m_sPetInfo.lAbility		= 0;
	m_sPetInfo.lHungry			= -1;
	m_sPetInfo.lMaxHungry		= -1;
	m_sPetInfo.lSympathy		= -1;
	m_sPetInfo.lMaxSympathy	= -1;
	m_sPetInfo.lRemainRebirth	= 0;
	m_sPetInfo.strNameCard		= CTString("");

	m_sWildPetInfo.pet_index = -1;
	m_sWildPetInfo.pet_name = CTString("");
	m_sWildPetInfo.pet_level = -1;
	m_sWildPetInfo.pet_str = -1;
	m_sWildPetInfo.pet_con = -1;
	m_sWildPetInfo.pet_dex = -1;
	m_sWildPetInfo.pet_int = -1;

	for (int i = 0; i < WEAR_TOTAL; ++i)
	{
		if (m_pIcon[i] != NULL)
			m_pIcon[i]->clearIconData();
	}
}

void CUIViewDetail::initialize()
{
	m_pIaBack = (CUIImageArray*)findUI("ia_back");
	m_pstrName = (CUIText*)findUI("str_name");
	m_pMoveArea = (CUIImage*)findUI("move_area");
	m_pbtnClose = (CUIButton*)findUI("btn_close");

	if (m_pbtnClose != NULL)
	{
		CmdViewClose* pCmd = new CmdViewClose;
		pCmd->setData(this);
		m_pbtnClose->SetCommandUp(pCmd);
	}

	CTString strIconId;
	for (int i = 0; i < WEAR_TOTAL; ++i)
	{
		strIconId.PrintF("icon_wear%d", i);
		m_pIcon[i] = (CUIIcon*)findUI(strIconId);

		if (m_pIcon[i] != NULL)
			m_pIcon[i]->clearIconData();
	}
}

void CUIViewDetail::openUI()
{
	SetVisible(TRUE);
	Hide(FALSE);

	UIMGR()->RearrangeOrder(UI_EXPEDITION_VIEW, TRUE);
}

void CUIViewDetail::closeUI()
{
	SetVisible(FALSE);
	Hide(TRUE);

	ClearViewDetail();
	UIMGR()->RearrangeOrder(UI_EXPEDITION_VIEW, FALSE);
}

WMSG_RESULT CUIViewDetail::OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg )
{
	if (m_bHide)
		return WMSG_FAIL;

	if( m_bDrag && ( pMsg->wParam & MK_LBUTTON ) )
	{
		int ndX = x - m_nOriX;
		int ndY = y - m_nOriY;

		m_nOriX = x;
		m_nOriY = y;

		Move( ndX, ndY );
		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	CUIManager::getSingleton()->SetMouseCursorInsideUIs();
	return WMSG_FAIL;
}

WMSG_RESULT CUIViewDetail::OnLButtonDown( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if( m_pMoveArea && m_pMoveArea->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}

	CUIManager::getSingleton()->RearrangeOrder( UI_EXPEDITION_VIEW, TRUE );
	return WMSG_FAIL;
}

WMSG_RESULT CUIViewDetail::OnLButtonUp( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	CUIManager::getSingleton()->ResetHoldBtn();
	return WMSG_FAIL;
}

void CUIViewDetail::SetViewItem( int nWearPos, CItems* pItem )
{
	if (nWearPos < 0 || nWearPos >= WEAR_TOTAL)
		return;

	if (m_pIcon[nWearPos] == NULL)
		return;

	m_pIcon[nWearPos]->Hide(FALSE);
	m_pIcon[nWearPos]->SetWhichUI(UI_EXPEDITION_VIEW);
	m_pIcon[nWearPos]->setData(pItem, false);
}

void CUIViewDetail::SetCharInfo( CTString strCharInfo, SBYTE sbJob )
{
	if (m_pstrName != NULL)
		m_pstrName->SetText(strCharInfo);


	if (sbJob < 0 || sbJob >= TOTAL_JOB)
		return;

	if (m_pIaBack != NULL)
		m_pIaBack->SetRenderIdx(sbJob);
}
//ken //new2022
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
CUIExpeditionPartyDungeon::CUIExpeditionPartyDungeon()
//: m_pIaBack(NULL)
	: m_pbtnClose(NULL)
	, m_pbtnJoin(NULL)
	, m_pbtnCallMembers(NULL)
	, m_pbtnReward(NULL)
	, m_pstrName(NULL)
	, m_pstrTitle(NULL)
	, m_pstrEnter(NULL)
	, m_pstrReward(NULL)
	, m_pMoveArea(NULL)
	, BaseInfoDungeon(NULL)
	, m_pArrayRewardDG(NULL)
	, BaseArrayReward(NULL)
	, BaseInfoRank(NULL)
	, m_pstrEnterLv(NULL)
	, m_pstrEnterItem(NULL)
	, m_pstrEnterMembers(NULL)
	, m_pstrEnterMode(NULL)
	, m_pstrEnteriLv(NULL)
	, m_pstrEnterTimer(NULL)
	, m_pDominateProgress(NULL)
	, m_StrProgress(NULL)
	, m_difficulty(NULL)
	, m_nLastCurSel(-1)
	, m_plistScroll(NULL)
{
	setInherit(false);

	for (int i = 0; i < eLIST_DGEND; ++i)
	{
		m_pList[i] = NULL;
	}
}

CUIExpeditionPartyDungeon::~CUIExpeditionPartyDungeon()
{
	m_pbtnClose = NULL;
	m_pbtnJoin = NULL;
	m_pbtnCallMembers = NULL;
	m_pbtnReward = NULL;
	m_pstrName = NULL;
	m_pstrTitle = NULL;
	m_pstrEnter = NULL;
	m_pstrReward = NULL;
	m_pMoveArea = NULL;
	BaseInfoDungeon = NULL;
	m_pArrayRewardDG = NULL;
	BaseArrayReward = NULL;
	BaseInfoRank = NULL;
	m_pstrEnterLv = NULL;
	m_pstrEnterItem = NULL;
	m_pstrEnterMembers = NULL;
	m_pstrEnterMode = NULL;
	m_pstrEnteriLv = NULL;
	m_pstrEnterTimer = NULL;
	m_pDominateProgress = NULL;
	m_StrProgress = NULL;
	m_difficulty = NULL;
	m_nLastCurSel = -1;
	m_plistScroll = NULL;

#ifdef CLOUD_EXPEDITION_REWORK
	m_nCount = 0;
	memset(m_nzone, 0, sizeof(m_nzone));
	memset(m_ndifficulty, 0, sizeof(m_ndifficulty));
	memset(m_nlevel, 0, sizeof(m_nlevel));
	memset(m_ncp, 0, sizeof(m_ncp));
	memset(m_nneeditem, 0, sizeof(m_nneeditem));
	memset(m_nneedcount, 0, sizeof(m_nneedcount));
	memset(m_npartymember, 0, sizeof(m_npartymember));
	memset(m_ntime, 0, sizeof(m_ntime));
	memset(m_nrewardindex, 0, sizeof(m_nrewardindex));
	memset(m_nrewardindex1, 0, sizeof(m_nrewardindex1));
	memset(m_nrewardindex2, 0, sizeof(m_nrewardindex2));
	memset(m_nrewardindex3, 0, sizeof(m_nrewardindex3));
	memset(m_nrewardindex4, 0, sizeof(m_nrewardindex4));
	memset(m_ntitle, 0, sizeof(m_ntitle));
	memset(m_nbox, 0, sizeof(m_nbox));
#endif

	for (int i = 0; i < eLIST_DGEND; ++i)
	{
		m_pList[i] = NULL;
	}
}

void CUIExpeditionPartyDungeon::ClearDungeonInfo()
{
#ifdef CLOUD_EXPEDITION_REWORK
	m_nCount = 0;
	memset(m_nzone, 0, sizeof(m_nzone));
	memset(m_ndifficulty, 0, sizeof(m_ndifficulty));
	memset(m_nlevel, 0, sizeof(m_nlevel));
	memset(m_ncp, 0, sizeof(m_ncp));
	memset(m_nneeditem, 0, sizeof(m_nneeditem));
	memset(m_nneedcount, 0, sizeof(m_nneedcount));
	memset(m_npartymember, 0, sizeof(m_npartymember));
	memset(m_ntime, 0, sizeof(m_ntime));
	memset(m_nrewardindex, 0, sizeof(m_nrewardindex));
	memset(m_nrewardindex1, 0, sizeof(m_nrewardindex1));
	memset(m_nrewardindex2, 0, sizeof(m_nrewardindex2));
	memset(m_nrewardindex3, 0, sizeof(m_nrewardindex3));
	memset(m_nrewardindex4, 0, sizeof(m_nrewardindex4));
	memset(m_ntitle, 0, sizeof(m_ntitle));
	memset(m_nbox, 0, sizeof(m_nbox));
#endif
}

void CUIExpeditionPartyDungeon::initialize()
{
	CTString difficultyAll[3] = { _S(PARTY_DIFICULTY_STRING_NORMAL, ""), _S(PARTY_DIFICULTY_STRING_HARD, ""), _S(PARTY_DIFICULTY_STRING_HELL, ""), };
	//COLOR strColor;

	m_difficulty = (CUIComboBox*)findUI("Difficulty");
	for (int i = 0; i < 3; ++i)
	{
		m_difficulty->AddString(difficultyAll[i]);
	}

	m_pstrName = (CUIText*)findUI("text_name");
	m_pstrTitle = (CUIText*)findUI("text_title");
	m_pMoveArea = findUI("base_drag");
	m_pbtnClose = (CUIButton*)findUI("btn_close");

	CTString strString = CTString("");

	strString = _S(PARTY_DG_INTERFACE_TITLE, "Expeditions�");
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (m_pstrTitle != NULL)
		m_pstrTitle->SetText(strString);

	if (m_pbtnClose != NULL)
	{
		CmdEPDungeonClose* pCmd = new CmdEPDungeonClose;
		pCmd->setData(this);
		m_pbtnClose->SetCommandUp(pCmd);
	}

	m_pList[eLIST_AMEND_DUNGEON] = (CUIList*)findUI("list_dungeon_back");
	//m_pList[eLIST_AMEND_DGCONDITION] = (CUIList*)findUI("list_dungeon");
	m_plistScroll = (CUIScrollBar*)findUI("scroll_amend");
	BaseInfoDungeon = findUI("base_info_dungeon");
	BaseInfoRank = findUI("base_info_rank");

	if (BaseInfoRank != NULL)
	{
		m_pstrEnter = (CUIText*)BaseInfoRank->findUI("text_enter");
		m_pstrReward = (CUIText*)BaseInfoRank->findUI("text_reward");
		m_pDominateProgress = (CUIProgressBar*)BaseInfoRank->findUI("pb_progress");
		if (m_pDominateProgress != NULL) {
			m_pDominateProgress->SetProgressRange(0, 100);
			m_pDominateProgress->StartProgress();
		}
		m_StrProgress = (CUIText*)BaseInfoRank->findUI("text_progress");
		m_pbtnReward = (CUIButton*)BaseInfoRank->findUI("btn_reward");
	}
}

void CUIExpeditionPartyDungeon::OpenUI()
{
	SetVisible(TRUE);
	Hide(FALSE);

	//ClearDungeonInfo();
	//_pNetwork->ExpeditionDungeonDetailReq(0);

	if (m_plistScroll)
		m_plistScroll->SetScrollPos(0);

	if (m_difficulty)
		m_difficulty->SetCurSel(0);
	UpdateDungeonInfo();
	UIMGR()->RearrangeOrder(UI_EXPEDITION_PARTY_DUNGEON, TRUE);
}

void CUIExpeditionPartyDungeon::CloseUI()
{
	SetVisible(FALSE);
	Hide(TRUE);
	if (m_difficulty)
		m_difficulty->SetCurSel(0);
	ClearDungeonInfo();
	UIMGR()->RearrangeOrder(UI_EXPEDITION_PARTY_DUNGEON, FALSE);
}

WMSG_RESULT CUIExpeditionPartyDungeon::OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg)
{
	if (m_bHide)
		return WMSG_FAIL;

	if (m_bDrag && (pMsg->wParam & MK_LBUTTON))
	{
		int ndX = x - m_nOriX;
		int ndY = y - m_nOriY;

		m_nOriX = x;
		m_nOriY = y;

		Move(ndX, ndY);
		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	UIMGR()->SetMouseCursorInsideUIs();

	return CUIBase::OnMouseMove(x, y, pMsg);
}

WMSG_RESULT CUIExpeditionPartyDungeon::OnLButtonDown(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if (m_pMoveArea && m_pMoveArea->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}

	CUIManager::getSingleton()->RearrangeOrder(UI_EXPEDITION_PARTY_DUNGEON, TRUE);
	return WMSG_FAIL;
}

WMSG_RESULT CUIExpeditionPartyDungeon::OnLButtonUp(UINT16 x, UINT16 y)
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	CUIManager::getSingleton()->ResetHoldBtn();

	if (m_difficulty && m_difficulty->IsInside(x, y))
	{
		if (m_nLastCurSel != m_difficulty->GetCurSel())
		{
			m_nLastCurSel = m_difficulty->GetCurSel();
#ifdef CLOUD_EXPEDITION_REWORK
			ClearDungeonInfo();
			_pNetwork->ExpeditionDungeonDetailReq(m_difficulty->GetCurSel());
#else
			UpdateDungeonInfo();
#endif
		}
	}
	return WMSG_FAIL;
}

void CUIExpeditionPartyDungeon::SetViewItemRewards(int nWearPos, CItems* pItem)
{
	if (nWearPos < 0 || nWearPos >= WEAR_TOTAL)
		return;

}

void CUIExpeditionPartyDungeon::SetDungeonInfo(CTString strCharInfo, SBYTE sbJob)
{
	if (m_pstrName != NULL)
		m_pstrName->SetText(strCharInfo);

}

#ifdef CLOUD_EXPEDITION_REWORK
void CUIExpeditionPartyDungeon::SetDetailInfo(int amend, SLONG nCount, SLONG zone, SLONG difficulty, SLONG level, SLONG cp, SLONG needitem, SLONG needcount, SLONG partymember, int time, SLONG rewardindex, SLONG rewardindex1, SLONG rewardindex2, SLONG rewardindex3, SLONG rewardindex4, SLONG title, SLONG box)
{
	if (amend < 0 || amend >= 50)
		return;

	m_nCount = nCount; m_nzone[amend] = zone; m_ndifficulty[amend] = difficulty;  m_nlevel[amend] = level;  m_ncp[amend] = cp; m_nneeditem[amend] = needitem; m_nneedcount[amend] = needcount; m_npartymember[amend] = partymember; m_ntime[amend] = time; m_nrewardindex[amend] = rewardindex;  m_nrewardindex1[amend] = rewardindex1;  m_nrewardindex2[amend] = rewardindex2;  m_nrewardindex3[amend] = rewardindex3;  m_nrewardindex4[amend] = rewardindex4;  m_ntitle[amend] = title; m_nbox[amend] = box;
	/*CUIManager* pUIManager = CUIManager::getSingleton();
	CTString debug;
	debug.PrintF("WARNING count %d %d",m_nneeditem[amend],m_nrewardindex[amend]);//speedhack count %d %f
	pUIManager->GetChattingUI()->AddSysMessage(debug , SYSMSG_BOSSSPAWN);*/
}
#endif

void CUIExpeditionPartyDungeon::UpdateDungeonInfo()
{

	if (m_pList[eLIST_AMEND_DUNGEON] == NULL)
		return;

	m_pList[eLIST_AMEND_DUNGEON]->DeleteAllListItem();

	if (m_plistScroll)
		m_plistScroll->SetScrollPos(0);

	int i = 0, j = 0, max = m_nCount;//MAX_DG_COUNT;

	if (max < 0)
		return;

	int nItemCnt = m_pList[eLIST_AMEND_DUNGEON]->getListItemCount();

	CUIListItem* pItem = m_pList[eLIST_AMEND_DUNGEON]->GetListItemTemplate();
	CUIListItem* pItemTmp = NULL;

	CUIBase* pItemreward = NULL;
	CUIIcon* pIcon = NULL;
	CUIText* pText = NULL;

	for (i = 0; i < max; ++i)//max
	{
		if (nItemCnt <= i)
			m_pList[eLIST_AMEND_DUNGEON]->AddListItem(pItem->Clone());

		pItemTmp = (CUIListItem*)m_pList[eLIST_AMEND_DUNGEON]->GetListItem(i);

		if (pItemTmp == NULL)
			continue;

		CmdSelectDungeon* pCmd = new CmdSelectDungeon;
		pCmd->setData(this, i);
		pItemTmp->SetCommand(pCmd);
       {

			if (pText = (CUIText*)pItemTmp->findUI("text_name"))
		{
				int zoneidx;
				zoneidx = m_nzone[i];

              CTString strTmp = CZoneInfo::getSingleton()->GetZoneName(zoneidx);

               strTmp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTmp, pText->GetWidth(), CTString("..."));

             pText->SetText(strTmp);
			}

			BaseArrayReward = pItemTmp->findUI("base_reward_group");
			m_pArrayRewardDG = (CUIArray*)pItemTmp->findUI("array_reward");

			if (BaseArrayReward == NULL)
             continue;

			if (m_pArrayRewardDG == NULL)
             continue;

			BaseArrayReward->Hide(TRUE);

			if (BaseArrayReward != NULL && m_pArrayRewardDG != NULL)
			{
				BaseArrayReward->Hide(FALSE);

				int nArrayItemCnt = m_pArrayRewardDG->GetArrayChildCount();
				CUIBase* pItemTmp = m_pArrayRewardDG->GetArrayItemTemplate();

				int nTmpCnt = 5;

				if (nTmpCnt <= 0)
                 continue;

				for (j = 0; j < nTmpCnt; ++j)
				{
					if (j >= nArrayItemCnt)
						m_pArrayRewardDG->AddArrayItem((CUIArrayItem*)pItemTmp->Clone());


					pItemreward = m_pArrayRewardDG->GetArrayItem(j);
					pIcon = (CUIIcon*)pItemreward->findUI("icon_reward");

					pItemreward->Hide(FALSE);

					if (pIcon == NULL)
						continue;

					int nRewardIdx[] = { m_nrewardindex[i], m_nrewardindex1[i], m_nrewardindex2[i], m_nrewardindex3[i], m_nrewardindex4[i] };

					pIcon->setData(UBET_ITEM, nRewardIdx[j]);
				}

				nArrayItemCnt = m_pArrayRewardDG->GetArrayChildCount();

				for (j = nTmpCnt; j < nArrayItemCnt; ++j)
				{
					pItemreward = m_pArrayRewardDG->GetArrayItem(j);

                  if (pItemreward == NULL)
						continue;

                  pItemreward->Hide(TRUE);
				}
			}
		}
	}

	m_pList[eLIST_AMEND_DUNGEON]->setCurSel(-1);
	m_pList[eLIST_AMEND_DUNGEON]->UpdateList();
	m_pList[eLIST_AMEND_DUNGEON]->UpdateScroll(max);

	UpdateAmenddungeon(0);
	UpdateInfoRank(0);
	if (m_difficulty)
		m_nLastCurSel = m_difficulty->GetCurSel();
}
void CUIExpeditionPartyDungeon::UpdateAmenddungeon(int nAmendIndex)
{
	if (BaseInfoDungeon == NULL)
		return;

	BaseInfoDungeon->Hide(TRUE);

	if (nAmendIndex < 0 || nAmendIndex >= m_nCount)
		return;

	BaseInfoDungeon->Hide(FALSE);
	CTString strTmp;
	COLOR strColor;
	CTString difficultyAll[3] = { _S(PARTY_DIFICULTY_STRING_NORMAL, ""), _S(PARTY_DIFICULTY_STRING_HARD, ""), _S(PARTY_DIFICULTY_STRING_HELL, ""), };

	m_pbtnJoin = (CUIButton*)BaseInfoDungeon->findUI("btn_join");
	m_pbtnCallMembers = (CUIButton*)BaseInfoDungeon->findUI("btn_callmembers");

	int i = nAmendIndex;
	{
			int difficultyLevel = m_nlevel[i];
			int difficultyiLevel = m_ncp[i];
			//const char* difficultyTime[3] = {PARTY_DG0_AVERAGE_TIME_NORMAL,PARTY_DG0_AVERAGE_TIME_HARD,PARTY_DG0_AVERAGE_TIME_HELL};

			if (CUITextBox* pText = (CUITextBox*)BaseInfoDungeon->findUI("text_info"))
			{
				CTString strString = _S(PARTY_DG0_INFO_STRING, "Velpist historia�");
				pText->SetText(strString);
			}

			if (m_pstrEnterLv = (CUIText*)BaseInfoDungeon->findUI("str_info_level"))
			{

				strTmp.PrintF("%d", m_nlevel[i]);//_pNetwork->MyCharacterInfo.str


				if (_pNetwork->MyCharacterInfo.level < difficultyLevel)
					strColor = DEF_UI_COLOR_RED;//Vermelho
				else
					strColor = 0x00FF21FF;//VERDE 

				strTmp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTmp, m_pstrEnterLv->GetWidth(), CTString("..."));

				m_pstrEnterLv->SetText(strTmp);
				m_pstrEnterLv->setFontColor(strColor);
			}

			if (m_pstrEnterItem = (CUIText*)BaseInfoDungeon->findUI("str_info_item"))
			{
				if (IS_EVENT_ON(707))
					strTmp.PrintF("Free");
				else
				{
					if (m_nneeditem[i] == -1)
						strTmp.PrintF("Free");
					else
						strTmp.PrintF("%s(%d)", _pNetwork->GetItemName(m_nneeditem[i]), m_nneedcount[i]);
				}

				CUIInventory* pInven = UIMGR()->GetInventory();

				int nInvenItemCnt = pInven->GetItemCount(m_nneeditem[i]);

				if (IS_EVENT_ON(707))
				{
					strColor = 0x00FF21FF;//VERDE 
				}
				else
				{
					if (nInvenItemCnt <= 0 || nInvenItemCnt < m_nneedcount[i])
						strColor = DEF_UI_COLOR_RED;//Vermelho
					else
						strColor = 0x00FF21FF;//VERDE 
				}

				strTmp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTmp, m_pstrEnterItem->GetWidth(), CTString("..."));

				m_pstrEnterItem->SetText(strTmp);
				m_pstrEnterItem->setFontColor(strColor);
			}

			if (m_pstrEnterMembers = (CUIText*)BaseInfoDungeon->findUI("str_info_members"))
			{
#ifdef CLOUD_EXPEDITION_SOLO_DUNGEONS
				strTmp.PrintF("%d/%d", 1, 1);
#else
				strTmp.PrintF("%d/%d", GAMEDATAMGR()->GetPartyInfo()->GetMemberCount(), m_npartymember[i]);//_pNetwork->MyCharacterInfo.str
#endif

#ifndef CLOUD_EXPEDITION_SOLO_DUNGEONS
				if (GAMEDATAMGR()->GetPartyInfo()->GetMemberCount() < m_npartymember[i])
					strColor = DEF_UI_COLOR_RED;//Vermelho
				else
#endif
					strColor = 0x00FF21FF;//VERDE 

				strTmp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTmp, m_pstrEnterMembers->GetWidth(), CTString("..."));

				m_pstrEnterMembers->SetText(strTmp);
				m_pstrEnterMembers->setFontColor(strColor);
			}

			if (m_pstrEnterMode = (CUIText*)BaseInfoDungeon->findUI("str_info_mode"))
			{
				int nCurSel = m_difficulty ? m_difficulty->GetCurSel() : 0;
				strTmp.PrintF(difficultyAll[nCurSel]);
				if (nCurSel == 0)
					strColor = DEF_UI_COLOR_WHITE;//Branco
				else if (nCurSel == 1)
					strColor = 0xCC66FFFF;//roxo
				else if (nCurSel == 2)
					strColor = 0xFF6A00FF;//laranja
				strTmp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTmp, m_pstrEnterMode->GetWidth(), CTString("..."));

				m_pstrEnterMode->SetText(strTmp);
				m_pstrEnterMode->setFontColor(strColor);
			}

			if (m_pstrEnteriLv = (CUIText*)BaseInfoDungeon->findUI("str_info_ilevel"))
			{
				if (difficultyiLevel == -1)
					difficultyiLevel = 0;

				strTmp.PrintF("%d", difficultyiLevel);

				/*if (_pNetwork->MyCharacterInfo.iItemLevel < difficultyiLevel)
					strColor = DEF_UI_COLOR_RED;//Vermelho
				else*/
					strColor = 0x00FF21FF;//VERDE 

				strTmp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTmp, m_pstrEnteriLv->GetWidth(), CTString("..."));

				m_pstrEnteriLv->SetText(strTmp);
				m_pstrEnteriLv->setFontColor(strColor);
			}

			if (m_pstrEnterTimer = (CUIText*)BaseInfoDungeon->findUI("str_info_time"))
			{
				int nTime = static_cast<int>(m_ntime[i]);
					int nSec = nTime % 60;
					nTime /= 60;

					int nMin = nTime % 60;
					int nHour = nTime / 60;

				strTmp.PrintF(_s("%02d:%02d:%02d"), nHour, nMin, nSec);
				//strTmp.PrintF( difficultyTime[m_difficulty->GetCurSel()]);
				strColor = 0x3fb9f2FF;//azul
				strTmp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTmp, m_pstrEnterTimer->GetWidth(), CTString("..."));

				m_pstrEnterTimer->SetText(strTmp);
				m_pstrEnterTimer->setFontColor(strColor);
			}

			if (m_pbtnCallMembers != NULL)
			{

				if (_pNetwork->MyCharacterInfo.zoneNo != m_nzone[i])
					m_pbtnCallMembers->SetEnable(FALSE);
				else
				{
					if (GAMEDATAMGR()->GetPartyInfo()->AmILeader())
					{
						m_pbtnCallMembers->SetEnable(TRUE);
						CmdEPDungeonRecall* pCmd = new CmdEPDungeonRecall;
#ifdef CLOUD_EXPEDITION_REWORK
						pCmd->setData(this, m_nzone[i]);
#else
						pCmd->setData(this, nAmendIndex);
#endif
						m_pbtnCallMembers->SetCommandUp(pCmd);
					}
					else
						m_pbtnCallMembers->SetEnable(FALSE);
				}
			}

							if (m_pbtnJoin != NULL)
							{
								CUIInventory* pInven = UIMGR()->GetInventory();

								int nInvenItemCnt = pInven->GetItemCount(m_nneeditem[i]);

								if (IS_EVENT_ON(707))
									nInvenItemCnt = 1;
								if (m_nneeditem[i] == -1)
									nInvenItemCnt = 1;

								int nCurDifficulty = m_difficulty ? m_difficulty->GetCurSel() : 0;

								if (_pNetwork->MyCharacterInfo.level < difficultyLevel// || _pNetwork->MyCharacterInfo.iItemLevel < difficultyiLevel
					#ifndef CLOUD_EXPEDITION_SOLO_DUNGEONS	
									|| GAMEDATAMGR()->GetPartyInfo()->GetMemberCount() < m_npartymember[i]
					#endif
									|| nInvenItemCnt <= 0 || nInvenItemCnt < m_nneedcount[i] || _pNetwork->MyCharacterInfo.zoneNo == m_nzone[i])
									m_pbtnJoin->SetEnable(FALSE);
								else
								{
					#ifndef CLOUD_EXPEDITION_SOLO_DUNGEONS					
									if (GAMEDATAMGR()->GetPartyInfo()->AmILeader())
									{
										m_pbtnJoin->SetEnable(TRUE);
										CmdEPDungeonJoin* pCmd = new CmdEPDungeonJoin;
										pCmd->setData(this, nAmendIndex, nCurDifficulty, m_nzone[i]);
										m_pbtnJoin->SetCommandUp(pCmd);
									}
									else
										m_pbtnJoin->SetEnable(FALSE);
					#else
									{
										m_pbtnJoin->SetEnable(TRUE);
										CmdEPDungeonJoin* pCmd = new CmdEPDungeonJoin;
										pCmd->setData(this, nAmendIndex, nCurDifficulty, m_nzone[i]);
										m_pbtnJoin->SetCommandUp(pCmd);
									}
					#endif
								}
							}
						}
						UpdateInfoRank(nAmendIndex);
					}
void CUIExpeditionPartyDungeon::UpdateInfoRank(int nAmendIndex)
{
	if (BaseInfoRank == NULL)
		return;

	BaseInfoRank->Hide(TRUE);

	if (nAmendIndex < 0 || nAmendIndex >= m_nCount)
		return;

	BaseInfoRank->Hide(FALSE);
	CUIIcon* pIcon = NULL;

	CTString strString = CTString("");

	if (m_pstrName == NULL)
		return;
	if (m_pstrEnter == NULL)
		return;
	if (m_pstrReward == NULL)
		return;
	if (m_pDominateProgress == NULL)
		return;

	int i = nAmendIndex;
	int zoneidx = m_nzone[i];

	CTString strzonename = CZoneInfo::getSingleton()->GetZoneName(zoneidx);

	if (m_pstrTitle != NULL)
		strzonename = UtilHelp::getSingleton()->GetCalcStringEllipsis(strzonename, m_pstrTitle->GetWidth(), CTString("..."));

	CUIText* mm_pstrName = (CUIText*)BaseInfoRank->findUI("text_name");
	if (mm_pstrName != NULL)
		mm_pstrName->SetText(strzonename);

	strString = _S(PARTY_DG_PROGRESS_STRING, "Expeditions�");

	if (m_pstrEnter != NULL)
		m_pstrEnter->SetText(strString);

	if (pIcon = (CUIIcon*)BaseInfoRank->findUI("icon_reward0"))
	{
		if (_pNetwork->MyCharacterInfo.cloud_partydgtitle[i] == 0)
			pIcon->setData(UBET_ITEM, m_ntitle[i]);
		else
			pIcon->setData(UBET_ITEM, m_nbox[i]);
	}

	if (m_pstrReward != NULL)
	{
		CTString strTmp;

		if (_pNetwork->MyCharacterInfo.cloud_partydgtitle[i] == 0)
			strTmp = _pNetwork->GetItemName(m_ntitle[i]);
		else
			strTmp = _pNetwork->GetItemName(m_nbox[i]);

		strTmp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTmp, m_pstrReward->GetWidth(), CTString("..."));

		m_pstrReward->SetText(strTmp);
	}

	{
		SQUAD sqExp = _pNetwork->MyCharacterInfo.cloud_partydgdata[i];
		SQUAD sqMaxExp;

		if (_pNetwork->MyCharacterInfo.cloud_partydgtitle[i] == 0)
			sqMaxExp = PARTY_DG_COMPLETE_TIMES_TITLE;
		else
			sqMaxExp = PARTY_DG_COMPLETE_TIMES_BOX;

		if (sqExp < 0)
			sqExp = 0;
		float mpercent = ((float)sqExp / (float)sqMaxExp) * 100.f;
		m_pDominateProgress->SetProgressPos(static_cast<int>(mpercent));
		m_pDominateProgress->SetShowText(0);

		CTString strTemp;

		if (sqExp >= sqMaxExp)
			strTemp.PrintF("Max");
		else
			strTemp.PrintF("%.2f%%", mpercent);

		if (m_StrProgress != NULL)
			m_StrProgress->SetText(strTemp);

		if (m_pbtnReward != NULL)
		{
			if (sqExp < sqMaxExp)
				m_pbtnReward->SetEnable(FALSE);
			else
			{
				m_pbtnReward->SetEnable(TRUE);
				CmdEPDungeonReward* pCmd = new CmdEPDungeonReward;
				pCmd->setData(this, nAmendIndex, zoneidx);
				m_pbtnReward->SetCommandUp(pCmd);
			}
		}
	}
}
#endif
