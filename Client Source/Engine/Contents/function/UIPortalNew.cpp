#include "stdh.h"

#include <Engine/Interface/UIInternalClasses.h>
#include <vector>
#include <Engine/Contents/function/UIPortalNew.h>
#include <Engine/World/World.h>
#include <algorithm>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Contents/Base/UIQuestBookNew.h>
#include <Engine/Help/Util_Help.h>
#include <Engine/Info/ServerInfo.h>
//--------------------------------------------------------------
// ´Ý±â
class CmdPortalClose : public Command
{
public:
	CmdPortalClose() : pUI_(NULL) {}
	void setData(CUIPortal* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->Close();
	}
private:
	CUIPortal* pUI_;
};

//--------------------------------------------------------------
// ÀÌµ¿
class CmdPortalOk : public Command
{
public:
	CmdPortalOk() : pUI_(NULL) {}
	void setData(CUIPortal* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->PressOk();
	}
private:
	CUIPortal* pUI_;
};

//--------------------------------------------------------------
// List Mouse Event
class CmdPortalMouseEvent : public Command
{
public:
	CmdPortalMouseEvent() : pUI_(NULL), pItem_(NULL), col_(0xffffffff) {}
	void setData(CUIPortal* pUI, CUIListItem* pItem, COLOR col)	
	{ 
		pUI_ = pUI;
		pItem_ = pItem;
		col_ = col;
	}
	void execute() {
		if (pUI_)
			pUI_->SetListItemColor(pItem_, col_);
	}
private:
	CUIPortal*	 pUI_;
	CUIListItem* pItem_;
	COLOR		 col_;
};

// [KH_07044] 3Â÷ µµ¿ò¸» °ü·Ã Ãß°¡
extern INDEX g_iShowHelp1Icon;

CUIPortal::CUIPortal()
	: m_pmoveArea(NULL)
	, m_pList(NULL)
	, m_bDrag(false)
	, m_nOriX(0), m_nOriY(0)
{
	m_npcIdx =-1;
	m_UniItemIdx = -1;
	m_bUseItem = FALSE;
	m_fNpcX = 0.0f;
	m_fNpcZ = 0.0f;

	for (int i = 0; i < eBTN_MAX; ++i)
	{
		m_pBtn[i] = NULL;
	}

	setInherit(false);
}

void CUIPortal::initialize()
{
	m_pmoveArea = (CUIImage*)findUI("move_area");

	CTString strId[eBTN_MAX] = { "btn_close", "btn_move", "btn_cancel" };

	for (int i = 0; i < eBTN_MAX; ++i)
	{
		m_pBtn[i] = (CUIButton*)findUI(strId[i]);
	}

	if (m_pBtn[eBTN_CLOSE] != NULL)
	{
		CmdPortalClose* pCmd = new CmdPortalClose;
		pCmd->setData(this);
		m_pBtn[eBTN_CLOSE]->SetCommandUp(pCmd);
	}

	if (m_pBtn[eBTN_CANCEL] != NULL)
	{
		CmdPortalClose* pCmd = new CmdPortalClose;
		pCmd->setData(this);
		m_pBtn[eBTN_CANCEL]->SetCommandUp(pCmd);
	}

	if (m_pBtn[eBTN_MOVE] != NULL)
	{
		CmdPortalOk* pCmd = new CmdPortalOk;
		pCmd->setData(this);
		m_pBtn[eBTN_MOVE]->SetCommandUp(pCmd);
	}
	m_pList = (CUIList*)findUI("list_menu");
}

void CUIPortal::OnRender( CDrawPort* pDraw )
{
	// Check distance
	FLOAT	fDiffX = _pNetwork->MyCharacterInfo.x - m_fNpcX;
	FLOAT	fDiffZ = _pNetwork->MyCharacterInfo.z - m_fNpcZ;
	if( fDiffX * fDiffX + fDiffZ * fDiffZ > UI_VALID_SQRDIST )
		Close();
}

void CUIPortal::updateUI()
{
	if (m_pList == NULL)
		return;

	m_pList->DeleteAllListItem();

	int nMax = m_vectorListInfo.size();

	if (nMax <= 0)
		return;

	CUIListItem* pTemp = m_pList->GetListItemTemplate();

	if (pTemp == NULL)
		return;

	CUIListItem* pItem = NULL;
	CUIText*	 pText = NULL;
	CTString	 strTemp;
	CDrawPort*  pDrawPort = CUIManager::getSingleton()->GetDrawPort();
		
	for( int i = 0; i < nMax; i++ )
	{
		m_pList->AddListItem(pTemp->Clone());

		pItem = (CUIListItem*)m_pList->GetListItem(i);

		if (pItem == NULL)
			return;

		{
			CmdPortalMouseEvent* pCmd = new CmdPortalMouseEvent;
			pCmd->setData(this, pItem, 0xF8E1B5FF);
			pItem->SetCommandEnter(pCmd);
		}

		{
			CmdPortalMouseEvent* pCmd = new CmdPortalMouseEvent;
			pCmd->setData(this, pItem, 0xC0C0C0FF);
			pItem->SetCommandLeave(pCmd);
		}

		pText = (CUIText*)pItem->findUI("txt_zone");

		if (pText != NULL)
		{
			strTemp.PrintF("%s", CZoneInfo::getSingleton()->GetZoneName( m_vectorListInfo[i].zone ) );

			ULONG nStringWidth = pDrawPort->GetTextWidth2(strTemp);
			if (nStringWidth > pText->GetWidth())
			{
				pText->setTooltip(strTemp);
				strTemp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTemp, pText->GetWidth(), CTString("..."));
			}			
			pText->SetText(strTemp);
		}

		pText = (CUIText*)pItem->findUI("txt_pos");

		if (pText != NULL)
		{
			strTemp.PrintF("%s", CZoneInfo::getSingleton()->GetExtraName( m_vectorListInfo[i].zone, m_vectorListInfo[i].extra ) );

			ULONG nStringWidth = pDrawPort->GetTextWidth2(strTemp);
			if (nStringWidth > pText->GetWidth())
			{
				pText->setTooltip(strTemp);
				strTemp = UtilHelp::getSingleton()->GetCalcStringEllipsis(strTemp, pText->GetWidth(), CTString("..."));
			}			
			pText->SetText(strTemp);
		}
	}

	m_pList->UpdateList();
}

void CUIPortal::PressOk()
{
	if (m_pList == NULL)
		return;

	int nSel = m_pList->getCurSel();

    if( nSel > -1 )
    {
        if (m_bUseItem)
        {
            _pNetwork->SendUseGoDungeon(m_UniItemIdx);
        }
        else
        {
            //¸»·¹ÀÌ½Ã¾Æ
            //¿¡°ÔÇÏ ´øÀü ÀÌ¿ÜÀÇ Áö¿ª¿¡¼­ ¿¡°ÔÇÏ·Î ÀÌµ¿ÇÒ ¶§ ¸Þ¼¼ÁöÃ¢ »ý¼º		FRANCE_SPAIN_CLOSEBETA_NA_20081124
#if		!defined(G_THAI)
            if (m_vectorListInfo[nSel].zone == 15 && _pNetwork->MyCharacterInfo.zoneNo != 17
            && _pNetwork->MyCharacterInfo.zoneNo != 31)
            {
                CUIMsgBox_Info	MsgBoxInfo;
				const LONGLONG llMoveFee = 500000;
                CTString strTitle	= _S(221, 	"ÀÌµ¿");
				CTString strMessage, strFee;

				strFee.PrintF("%I64d", llMoveFee);
				UIMGR()->InsertCommaToString(strFee);

                strMessage.PrintF(_S(9362, "¿¡°ÔÇÏ Áö¿ªÀ¸·Î ÀÌµ¿ÇÏ±â À§ÇØ %s ³ª½º°¡ ¼ÒºñµË´Ï´Ù. ÀÌµ¿ÇÏ½Ã°Ú½À´Ï±î?"), strFee);
                MsgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_YESNO, UI_NONE, MSGCMD_GOTO_EGEHA);
                MsgBoxInfo.AddString(strMessage);
                UIMGR()->CreateMessageBox(MsgBoxInfo);
				return;
            }

#endif

#ifdef FUNZONE
			if (m_vectorListInfo[nSel].zone == 47 )
			{
				CUIMsgBox_Info	MsgBoxInfo;
				const LONGLONG llMoveFee = 1000000000;
				CTString strTitle = _S(221, "ÀÌµ¿");
				CTString strMessage, strFee;

				strFee.PrintF("%I64d", llMoveFee);
				UIMGR()->InsertCommaToString(strFee);

				strMessage.PrintF(_S(9387, "¿¡°ÔÇÏ Áö¿ªÀ¸·Î ÀÌµ¿ÇÏ±â À§ÇØ %s ³ª½º°¡ ¼ÒºñµË´Ï´Ù. ÀÌµ¿ÇÏ½Ã°Ú½À´Ï±î?"), strFee);
				MsgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_YESNO, UI_NONE, MSGCMD_GOTO_FZ);
				MsgBoxInfo.AddString(strMessage);
				UIMGR()->CreateMessageBox(MsgBoxInfo);
				return;
			}

#endif
            _pNetwork->GoZone( m_vectorListInfo[nSel].zone, m_vectorListInfo[nSel].extra ,m_npcIdx);
        }

        Close();
    }
}

void CUIPortal::SetListItemColor( CUIListItem* pItem, COLOR col )
{
	if (pItem == NULL)
		return;
	
	int nMax = pItem->getChildCount();
	CUIText* pTex = NULL;

	for (int i = 0; i < nMax; i++)
	{
		pTex = (CUIText*)pItem->getChildAt(i);

		if ( pTex != NULL)
		{
			pTex->setFontColor(col);
		}
	}
}

void CUIPortal::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

void CUIPortal::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

void CUIPortal::OpenPortal( FLOAT fX, FLOAT fZ )
{
	if (IsVisible()) return;

	CUIManager* pUIManager = CUIManager::getSingleton();
	CDrawPort* pDrawPort = pUIManager->GetDrawPort();

	int	nX = ( pDrawPort->dp_MinI + pDrawPort->dp_MaxI ) / 2 - m_nWidth / 2;
	int	nY = ( pDrawPort->dp_MinJ + pDrawPort->dp_MaxJ ) / 2 - m_nHeight / 2;

	SetPos( nX, nY );

	// Set position of target npc
	m_fNpcX = fX;
	m_fNpcZ = fZ;

	updateUI();

	SetVisible(TRUE);
	Hide(FALSE);
	
	pUIManager->RearrangeOrder( UI_PORTAL, TRUE );
}

void CUIPortal::ResetZoneList()
{
	m_vectorListInfo.clear();
	m_npcIdx = -1;

	if (m_pList != NULL)
	{
		m_pList->setCurSel(-1);
	}
}

void CUIPortal::AddToZoneList(int nZone, int nExtra)
{
	m_vectorListInfo.push_back(sZoneExtraIndex(nZone, nExtra));
	std::sort(m_vectorListInfo.begin(), m_vectorListInfo.end());
}

void CUIPortal::Close()
{
	SetVisible(FALSE);
	Hide(TRUE);

	ResetZoneList();
	m_bUseItem = FALSE;

	CUITooltipMgr::getSingleton()->setData(NULL);
	CUIManager::getSingleton()->RearrangeOrder( UI_PORTAL, FALSE );
}

WMSG_RESULT CUIPortal::OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg )
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

WMSG_RESULT CUIPortal::OnLButtonDown( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
	{
		Close();
		return WMSG_FAIL;
	}

 	if( m_pmoveArea && m_pmoveArea->IsInside(x, y))
 	{
 		m_bDrag = true;
 		m_nOriX = x;
 		m_nOriY = y;
 	}

	CUIManager::getSingleton()->RearrangeOrder( UI_PORTAL, TRUE );

	return WMSG_FAIL;
}

WMSG_RESULT CUIPortal::OnLButtonUp( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	CUIManager::getSingleton()->ResetHoldBtn();
	return WMSG_FAIL;
}

// ----------------------------------------------------------------------------
// Name : Close()
// Desc :
// ----------------------------------------------------------------------------
int CUIPortal::GetZoneListCount()
{
	return m_vectorListInfo.size();
}

void CUIPortal::GotoCurSelZone()
{
	if (m_pList == NULL)
		return;

	int	nSel = m_pList->getCurSel();

	if (nSel < 0)
		return;

	_pNetwork->GoZone( m_vectorListInfo[nSel].zone, m_vectorListInfo[nSel].extra ,m_npcIdx);
	Close();
}

///////////////////////////////////////////////////////////////////////////
// [071115: Su-won] DRATAN_SIEGE_DUNGEON
void CUIPortal::MsgBoxLCommand( int nCommandCode, int nResult )
{
	CTString tv_str; 
	
	switch( nCommandCode )
	{
	case MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ:
		{
			// [090527: selo] È®ÀåÆÑ Äù½ºÆ® ÀÌ¾ß±â ÇÑ´Ù Ã³¸® ¼öÁ¤À» À§ÇÑ ·çÆ¾
			int iQuestIndex = -1;
			if( ciQuestClassifier < nResult )	
			{
				iQuestIndex = nResult;
				nResult = ciQuestClassifier;
			}

			switch( nResult )
			{
			case DRATAN_SIEGE_DUNGEON_ENTER:
				{
					_pNetwork->SendDratanSiegeDungeonMSG(MSG_DUNGEON_ENTER, MSG_DUNGEON_ENTER_FEE);
				}
				break;
			case DRATAN_SIEGE_DUNGEON_STATE:
				{
					_pNetwork->SendDratanSiegeDungeonMSG(MSG_DUNGEON_INFO);
				}
				break;
			case DRATAN_SIEGE_DUNGEON_CONTROL_LORD:
				{
					_pNetwork->SendDratanSiegeDungeonMSG(MSG_MANAGEMENT, MSG_MANAGEMENT_MANAGER_CONFIRM);
				}
				break;
			case DRATAN_SIEGE_DUNGEON_CONTROL_NOMAL:
				{
					_pNetwork->SendDratanSiegeDungeonMSG(MSG_MANAGEMENT, MSG_MANAGEMENT_MANAGER_CONFIRM_NORMAL);
				}
				break;
			case ciQuestClassifier:
				{
					// ¼±ÅÃÇÑ Äù½ºÆ®¿¡ ´ëÇØ ¼ö¶ô ¶Ç´Â º¸»ó Ã¢À» ¿¬´Ù.
					CUIQuestBook::SelectQuestFromMessageBox( iQuestIndex );
				}
				break;
			}
		}
		break;
	case MSGLCMD_DRATAN_SIEGE_DUNGEON_CONTROL:
		{
			switch(nResult)
			{
			case DRATAN_SIEGE_DUNGEON_CONTROL_ENVIRONMENT:
				{
					_pNetwork->SendDratanSiegeDungeonMSG(MSG_MANAGEMENT, MSG_MANAGEMENT_MANAGER_ENV_INFO);
				}
				break;
			case DRATAN_SIEGE_DUNGEON_CONTROL_MONSTER:
				{
					_pNetwork->SendDratanSiegeDungeonMSG(MSG_MANAGEMENT, MSG_MANAGEMENT_MANAGER_MONSTER_INFO);
				}
				break;
			case DRATAN_SIEGE_DUNGEON_CONTROL_ADMISSION_FEE:
				{
					_pNetwork->SendDratanSiegeDungeonMSG(MSG_MANAGEMENT, MSG_MANAGEMENT_MANAGER_TAX_INFO);
				}
				break;
			case DRATAN_SIEGE_DUNGEON_CONTROL_HUNTING_FEE:
				{
					_pNetwork->SendDratanSiegeDungeonMSG(MSG_MANAGEMENT, MSG_MANAGEMENT_MANAGER_HUNTER_TAX_INFO);
				}
				break;
			case DRATAN_SIEGE_DUNGEON_CHANGE_LORDMODE:
				{
					_pNetwork->SendDratanSiegeDungeonMSG(MSG_MANAGEMENT, MSG_NAMAGEMENT_CHANGE_OWNER_MODE);
				}
				break;
			}
			break;
		}
	}
}

void CUIPortal::OpenDratanDungeonMsgBox()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (pUIManager->DoesMessageBoxLExist(MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ))
		return;

	pUIManager->CreateMessageBoxL( _S(3901, "µå¶óÅº Ä«¿À½º °ø¼º ´øÀü °ü¸®ÀÎ"),UI_PORTAL, MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ);
	pUIManager->AddMessageBoxLString(MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ,TRUE, _S(3902, "¾î¼­¿À¼¼¿ä. Àü Ä«¿À½º¼ºÀÇ ´øÀü °ü¸®ÀÎÀÔ´Ï´Ù."),-1,0xa3a1a3ff);
	pUIManager->AddMessageBoxLString(MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ,TRUE, _S(3903, "ÀÌ°÷ ´øÀüÀº Å©¸®½ºÅ»ÀÇ ÈûÀÌ Ãæ¸¸ÇÑ °÷À¸·Î ±× Èû¿¡ ÀÌ²ø·Á °í´ë¿¡¼­ºÎÅÍ ¹ÌÁöÀÇ °­·ÂÇÑ ¸ó½ºÅÍµéÀÌ ²÷ÀÓ¾øÀÌ »ý°Ü³ª°í ÀÖ½À´Ï´Ù."),-1,0xa3a1a3ff);
	pUIManager->AddMessageBoxLString(MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ,TRUE, _S(3904, "Èï¹Ì·Î¿î º¸¹°ÀÌ ÀÖ´Ù°íµµ ÇÏÁö¸¸ ¾î¶°ÇÑ ÀÏÀÌ ÀÏ¾î³¯Áö Àå´ãÇÒ ¼ö ¾øÀ¸¹Ç·Î ÀÚ½ÅÀÌ ¾ø´Ù¸é Á¢±ÙÇÏÁö ¾Ê´Â °ÍÀÌ ÁÁ½À´Ï´Ù."),-1,0xa3a1a3ff);
	pUIManager->AddMessageBoxLString(MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ,TRUE, _S(3905, "ÀÚ, ¾î¶»°Ô ÇÏ½Ã°Ú½À´Ï±î?"),-1,0xa3a1a3ff);

	CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ);

	pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ, FALSE, _S(3906, "´øÀü ÀÔÀåÇÏ±â" ), DRATAN_SIEGE_DUNGEON_ENTER);
	pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ, FALSE, _S(3907, "´øÀü »óÅÂÈ®ÀÎ" ), DRATAN_SIEGE_DUNGEON_STATE);
	pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ, FALSE, _S(3908, "´øÀü ¼ºÁÖ °ü¸®" ), DRATAN_SIEGE_DUNGEON_CONTROL_LORD);
	pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ, FALSE, _S(7059, "´øÀü ÀÏ¹Ý °ü¸®" ), DRATAN_SIEGE_DUNGEON_CONTROL_NOMAL);
	pUIManager->AddMessageBoxLString( MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ, FALSE, _S( 1220, "Ãë¼ÒÇÑ´Ù." ) );		

	return;
}

void CUIPortal::MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	eSelectionCommand eType;

	switch(SERVER_INFO()->GetDG_Mode())
	{
	case eDUNGEON_MODE_NOMAL:
		eType = DRATAN_SIEGE_DUNGEON_CONTROL_NOMAL; 
		break;
	case eDUNGEON_MODE_LORD:
		eType = DRATAN_SIEGE_DUNGEON_CONTROL_LORD;
		break;
	}

	switch( nCommandCode )
	{
	case MSGCMD_SIEGE_DUNGEON_ENTER:
		{
			if( bOK )
			{
				_pNetwork->SendDratanSiegeDungeonMSG(MSG_DUNGEON_ENTER, MSG_DUNGEON_GO);
			}
		}
		break;
	case MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL:
		{
			if( bOK )
			{
				if( pUIManager->DoesMessageBoxExist(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CHANGE) )
					pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CHANGE);

				CUIMsgBox_Info MsgBoxInfo;
				CTString strMessage;
				int nRate =pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL)->GetSpinButton().GetDataToNumber();
				
				strMessage.PrintF( _S( 191, "È®ÀÎ" ) );
				MsgBoxInfo.SetMsgBoxInfo(strMessage,UMBS_YESNO,UI_PORTAL,MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CHANGE);
				strMessage.PrintF( _S(3909, "ÇöÀç »óÅÂ¿¡¼­ %d%%¸¸Å­ ´õ ÄèÀûÇÏ°Ô ÇÏ½Ã°Ú½À´Ï±î?" ), nRate );
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
			else
			{
				pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL);
				pUIManager->GetPortal()->MsgBoxLCommand(MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ, eType);
			}
		}
		break;
	case MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL:
		{
			if( bOK )
			{
				if( pUIManager->DoesMessageBoxExist(MSGCMD_SIEGE_DUNGEON_MONSTER_CHANGE) )
					pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_MONSTER_CHANGE);

				CUIMsgBox_Info MsgBoxInfo;
				CTString strMessage;
				int nRate =pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL)->GetSpinButton().GetDataToNumber();
				
				strMessage.PrintF( _S( 191, "È®ÀÎ" ) );
				MsgBoxInfo.SetMsgBoxInfo(strMessage,UMBS_YESNO,UI_PORTAL,MSGCMD_SIEGE_DUNGEON_MONSTER_CHANGE);
				strMessage.PrintF( _S(3910, "ÇöÀç »óÅÂ¿¡¼­ %d%%¸¸Å­ ´õ ¿Â¼øÇÏ°Ô ÇÏ½Ã°Ú½À´Ï±î?" ), nRate );
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
			else
			{
				pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL);
				pUIManager->GetPortal()->MsgBoxLCommand(MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ, eType);
			}
		}
		break;
	case MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CONTROL:
		{
			if( bOK )
			{
				if( pUIManager->DoesMessageBoxExist(MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CHANGE) )
					pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CHANGE);

				CUIMsgBox_Info MsgBoxInfo;
				CTString strMessage;
				int nFee =pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CONTROL)->GetSpinButton().GetDataToNumber();
				
				strMessage.PrintF( _S( 191, "È®ÀÎ" ) );
				MsgBoxInfo.SetMsgBoxInfo(strMessage,UMBS_YESNO,UI_PORTAL,MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CHANGE);
				strMessage.PrintF( _S(3911, "ÀÔÀå·á¸¦ %d%%·Î ¼³Á¤ÇÏ½Ã°Ú½À´Ï±î?" ), nFee );
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
			else
			{
				pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CONTROL);
				pUIManager->GetPortal()->MsgBoxLCommand(MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ, DRATAN_SIEGE_DUNGEON_CONTROL_LORD);
			}
		}
		break;
	case MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CONTROL:
		{
			if( bOK )
			{
				if( pUIManager->DoesMessageBoxExist(MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CHANGE) )
					pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CHANGE);

				CUIMsgBox_Info MsgBoxInfo;
				CTString strMessage;
				int nFee =pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CONTROL)->GetSpinButton().GetDataToNumber();
				
				strMessage.PrintF( _S( 191, "È®ÀÎ" ) );
				MsgBoxInfo.SetMsgBoxInfo(strMessage,UMBS_YESNO,UI_PORTAL,MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CHANGE);
				strMessage.PrintF( _S(3912, "¼ö·Æ¼¼À²À» %d%%·Î ¼³Á¤ÇÏ½Ã°Ú½À´Ï±î?" ), nFee );
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
			else
			{
				pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CONTROL);
				pUIManager->GetPortal()->MsgBoxLCommand(MSGLCMD_DRATAN_SIEGE_DUNGEON_REQ, DRATAN_SIEGE_DUNGEON_CONTROL_LORD);
			}
		}
		break;
		
	case MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CHANGE:
		{
			if( bOK )
			{
				int nRate =pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL)->GetSpinButton().GetDataToNumber();
				pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL);

				_pNetwork->SendDratanSiegeDungeonMSG(MSG_MANAGEMENT, MSG_MANAGEMENT_MANAGER_ENV_CHANGE, nRate);
			}
		}
		break;
	case MSGCMD_SIEGE_DUNGEON_MONSTER_CHANGE:
		{
			if( bOK )
			{
				int nRate =pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL)->GetSpinButton().GetDataToNumber();
				pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL);

				_pNetwork->SendDratanSiegeDungeonMSG(MSG_MANAGEMENT, MSG_MANAGEMENT_MANAGER_MONSTER_CHANGE, nRate);
			}
		}
		break;
	case MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CHANGE:
		{
			if( bOK )
			{
				int nFee =pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CONTROL)->GetSpinButton().GetDataToNumber();
				pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CONTROL);

				_pNetwork->SendDratanSiegeDungeonMSG(MSG_MANAGEMENT, MSG_MANAGEMENT_MANAGER_TAX_CHANGE, nFee);
			}
		}
		break;
	case MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CHANGE:
		{
			if( bOK )
			{
				int nFee =pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CONTROL)->GetSpinButton().GetDataToNumber();
				pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CONTROL);

				_pNetwork->SendDratanSiegeDungeonMSG(MSG_MANAGEMENT, MSG_MANAGEMENT_MANAGER_HUNTER_TAX_CHANGE, nFee);
			}
		}
		break;
	}
}

void CUIPortal::Create_SiegeDungeon_State_MsgBox(int nEnvRate, int nMonRate)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( pUIManager->DoesMessageBoxExist(MSGCMD_SIEGE_DUNGEON_STATE) )
		pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_STATE);

	CTString strMessage;
	CUIMsgBox_Info	MsgBoxInfo;

	MsgBoxInfo.SetMsgBoxInfo( _S(3907, "´øÀü »óÅÂÈ®ÀÎ" ), UMBS_OK | UMBS_INPUTBOX | UMBS_SECOND_INPUTBOX , UI_PORTAL, MSGCMD_SIEGE_DUNGEON_STATE, 400 );
	
	MsgBoxInfo.AddString( _S(3913, "¢º ´øÀü ³»ºÎ È¯°æ") );
	MsgBoxInfo.m_nMaxRow +=1;
	MsgBoxInfo.AddString( _S(3914, "¿À¿°µÊ") );
	--MsgBoxInfo.m_nMaxRow;

	strMessage.PrintF(_s("%d%%"), nEnvRate);
	MsgBoxInfo.AddString( strMessage, 0xF2F2F2FF, TEXT_CENTER );
	--MsgBoxInfo.m_nMaxRow;
	MsgBoxInfo.AddString( _S(3915, "ÄèÀûÇÔ"), 0xF2F2F2FF, TEXT_RIGHT );
	MsgBoxInfo.m_nMaxRow +=2;
	MsgBoxInfo.AddString( _S(3916, "(ÄèÀûÇÒ¼ö·Ï Ä³¸¯ÅÍÀÇ °ø°Ý·Â&¹æ¾î·ÂÀÌ »ó½ÂµË´Ï´Ù.)") );
	MsgBoxInfo.m_nMaxRow +=2;

	MsgBoxInfo.AddString( _S(3917, "¢º ¸ó½ºÅÍÀÇ ÈäÆøÇÔ") );
	MsgBoxInfo.m_nMaxRow +=1;
	MsgBoxInfo.AddString( _S(3918, "¸Å¿ì ÈäÆøÇÔ") );
	--MsgBoxInfo.m_nMaxRow;

	strMessage.PrintF(_s("%d%%"), nMonRate);
	MsgBoxInfo.AddString( strMessage, 0xF2F2F2FF, TEXT_CENTER );
	--MsgBoxInfo.m_nMaxRow;
	MsgBoxInfo.AddString( _S(3919, "¿Â¼øÇÔ"), 0xF2F2F2FF, TEXT_RIGHT );
	MsgBoxInfo.m_nMaxRow +=2;
	MsgBoxInfo.AddString( _S(3920, "(¿Â¼øÇÒ¼ö·Ï ¸ó½ºÅÍÀÇ °ø°Ý·Â&¹æ¾î·ÂÀÌ ÇÏ¶ôÇÕ´Ï´Ù.)") );
	MsgBoxInfo.m_nMaxRow +=1;

	MsgBoxInfo.SetInputBox( 3, 0, 0, 370 );
	MsgBoxInfo.SetSEInputBox( 11, 0, 0, 370 );
	MsgBoxInfo.m_nInputPosY += _pUIFontTexMgr->GetLineHeight() *0.5f;
	MsgBoxInfo.m_nSEInputPosY += _pUIFontTexMgr->GetLineHeight() *0.5f;

	MsgBoxInfo.m_nColorBoxCount =2;

	pUIManager->CreateMessageBox( MsgBoxInfo );

	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_STATE)->GetInputBox().SetFocus(FALSE);
	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_STATE)->GetInputBox().SetInValidEditBox(TRUE);
	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_STATE)->GetSEInputBox().SetFocus(FALSE);
	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_STATE)->GetSEInputBox().SetInValidEditBox(TRUE);


	float fEnvRate =nEnvRate/100.0f;
	float fMonRate =nMonRate/100.0f;

	int iPosX[2], iPosY[2];
	int iWidth[2], iHeight;

	iPosX[0] =MsgBoxInfo.m_nInputPosX+2;
	iPosX[1] =MsgBoxInfo.m_nSEInputPosX+2;

	iPosY[0] =MsgBoxInfo.m_nInputPosY +2;
	iPosY[1] =MsgBoxInfo.m_nSEInputPosY +2;

	iWidth[0] =(MsgBoxInfo.m_nInputWidth-4)*fEnvRate;
	iWidth[1] =(MsgBoxInfo.m_nSEInputWidth-4)*fMonRate;

	iHeight =9;

	WRect rcBox_Environment;
	WRect rcBox_Monster;

	rcBox_Environment.SetRect( iPosX[0], iPosY[0], iPosX[0]+iWidth[0], iPosY[0]+iHeight);
	rcBox_Monster.SetRect( iPosX[1], iPosY[1], iPosX[1]+iWidth[1], iPosY[1]+iHeight);

	UBYTE ubEnvCol =5;
	UBYTE ubMonCol =7;

	if( nEnvRate <=10 )
		ubEnvCol =6;

	if( nMonRate <=10 )
		ubMonCol =6;

	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_STATE)->SetColorBox(0, ubEnvCol, rcBox_Environment);
	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_STATE)->SetColorBox(1, ubMonCol, rcBox_Monster);
}

void CUIPortal::Create_SiegeDungeon_EnvCtr_MsgBox(int nCurRate)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( pUIManager->DoesMessageBoxExist(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL) )
		pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL);

	CTString strMessage;
	CUIMsgBox_Info	MsgBoxInfo;

	MsgBoxInfo.SetMsgBoxInfo( _S(3921, "´øÀü ³»ºÎ È¯°æ Á¦¾î" ), UMBS_OKCANCEL | UMBS_SPINBUTTON , UI_PORTAL, MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL, 400 );
	
	MsgBoxInfo.AddString( _S(3922, "Å©¸®½ºÅ»ÀÇ ±â¿îÀ» ²ø¾î¿Í ´øÀüÀÇ ³»ºÎ È¯°æÀ» ÄèÀûÇÏ°Ô ¸¸µé ¼ö ÀÖ½À´Ï´Ù. ´øÀüÀÇ È¯°æÀÌ ÄèÀûÇØÁö¸é Ä³¸¯ÅÍÀÇ °ø°Ý·Â°ú ¹æ¾î·ÂÀÌ »ó½ÂµË´Ï´Ù.") );
	MsgBoxInfo.AddString( _S(3923, "´Ü, ÄèÀûÇÔÀ» »ó½Â ½ÃÅ°±â À§ÇØ¼­´Â ³ª½º°¡ ÇÊ¿äÇÏ¸ç, ÄèÀûÇÔÀº 1½Ã°£(ÇöÀç ½Ã°£)¿¡ 10%¾¿ ÇÏ¶ôµË´Ï´Ù.") );
	++MsgBoxInfo.m_nMaxRow;
	MsgBoxInfo.AddString( _S(3924, "¾î´À Á¤µµ³ª ÄèÀûÇÏ°Ô ¸¸µå½Ã°Ú½À´Ï±î?") );
	MsgBoxInfo.m_nMaxRow +=2;

	LONGLONG llNeedNas = SERVER_INFO()->GetDG_EnvNas() * 10;
	
	CTString strNas;
	strNas.PrintF("%I64d", llNeedNas);
	pUIManager->InsertCommaToString(strNas);

	strMessage.PrintF( _s("%s: %s %s%s"), _S(1058, "ÇÊ¿ä³ª½º"), strNas, _S(1762, "³ª½º"), _s("   ") );
	MsgBoxInfo.AddString( strMessage, 0xF2F2F2FF, TEXT_RIGHT );

	
	MsgBoxInfo.m_nColorBoxCount =4;

	MsgBoxInfo.SetSpinButton(MsgBoxInfo.m_nMaxRow-2, 1, -1, _S(3925, "ÄèÀûÇÔ »ó½Â%") + _s("   "));

	pUIManager->CreateMessageBox( MsgBoxInfo );

	int iPosX[4], iPosY[4];
	int iWidth[4], iHeight[4];

	iPosX[0] =MsgBoxInfo.m_nSpinButtonPosX -6;
	iPosY[0] =MsgBoxInfo.m_nSpinButtonPosY -3;
	iWidth[0] =0;
	iHeight[0] = 32;

	iPosX[1] =iPosX[0];
	iPosY[1] =iPosY[0];
	iWidth[1] =MsgBoxInfo.m_nWidth -iPosX[0]*2;
	iHeight[1] = 0;

	iPosX[2] =MsgBoxInfo.m_nWidth -iPosX[0];
	iPosY[2] =iPosY[0];
	iWidth[2] =0;
	iHeight[2] = 34;

	iPosX[3] =iPosX[0];
	iPosY[3] =iPosY[0] +32;
	iWidth[3] =iWidth[1];
	iHeight[3] = 0;


	WRect rcBox[4];

	rcBox[0].SetRect( iPosX[0], iPosY[0], iPosX[0]+iWidth[0], iPosY[0]+iHeight[0]);
	rcBox[1].SetRect( iPosX[1], iPosY[1], iPosX[1]+iWidth[1], iPosY[1]+iHeight[1]);
	rcBox[2].SetRect( iPosX[2], iPosY[2], iPosX[2]+iWidth[2], iPosY[2]+iHeight[2]);
	rcBox[3].SetRect( iPosX[3], iPosY[3], iPosX[3]+iWidth[3], iPosY[3]+iHeight[3]);

	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL)->SetColorBox(0, 0, rcBox[0]);
	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL)->SetColorBox(1, 0, rcBox[1]);
	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL)->SetColorBox(2, 0, rcBox[2]);
	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL)->SetColorBox(3, 0, rcBox[3]);
	
	for(int i=1; i<=10; ++i)
	{
		if( (i*10 +nCurRate) >100 )
			break;
		
		CTString strData;
		strData.PrintF("%d", i*10);
		pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_ENVIRONMENT_CONTROL)->GetSpinButton().AddData(strData);
	}
}

void CUIPortal::Create_SiegeDungeon_MonCtr_MsgBox(int nCurRate)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( pUIManager->DoesMessageBoxExist(MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL) )
		pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL);

	CTString strMessage;
	CUIMsgBox_Info	MsgBoxInfo;

	MsgBoxInfo.SetMsgBoxInfo( _S(3926, "´øÀü ³»ºÎ ¸ó½ºÅÍ Á¦¾î" ), UMBS_OKCANCEL | UMBS_SPINBUTTON , UI_PORTAL, MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL, 400 );
	
	MsgBoxInfo.AddString( _S(3927, "Å©¸®½ºÅ»ÀÇ ±â¿îÀ¸·Î ´øÀü¿¡ ÀÖ´Â ¸ó½ºÅÍµéÀ» ¿Â¼øÇÏ°Ô ¸¸µé ¼ö ÀÖ½À´Ï´Ù. ´øÀüÀÇ ¸ó½ºÅÍ°¡ ¿Â¼øÇØÁö¸é ¸ó½ºÅÍÀÇ °ø°Ý·Â°ú ¹æ¾î·Â, ÃÖ´ë HP°¡ ÇÏ¶ôÇÕ´Ï´Ù.") );
	MsgBoxInfo.AddString( _S(3928, "´Ü, ¸ó½ºÅÍÀÇ ¿Â¼øÇÔÀ» »ó½Â ½ÃÅ°±â À§ÇØ¼­´Â ³ª½º°¡ ÇÊ¿äÇÏ¸ç, ¿Â¼øÇÔÀº 1½Ã°£(ÇöÀç½Ã°£)¿¡ 10%¾¿ ÇÏ¶ôµË´Ï´Ù.") );
	++MsgBoxInfo.m_nMaxRow;
	MsgBoxInfo.AddString( _S(3929, "¾î´À Á¤µµ³ª ¿Â¼øÇÏ°Ô ¸¸µå½Ã°Ú½À´Ï±î?") );
	MsgBoxInfo.m_nMaxRow +=2;

	LONGLONG llNeedNas = SERVER_INFO()->GetDG_MonsterNas() * 10;
	CTString strNas;
	strNas.PrintF("%I64d", llNeedNas);
	pUIManager->InsertCommaToString(strNas);
		
	strMessage.PrintF( _s("%s: %s %s%s"), _S(1058, "ÇÊ¿ä³ª½º"), strNas, _S(1762, "³ª½º"), _s("   ") );
	MsgBoxInfo.AddString( strMessage, 0xF2F2F2FF, TEXT_RIGHT );
	
	MsgBoxInfo.m_nColorBoxCount =4;

	MsgBoxInfo.SetSpinButton(MsgBoxInfo.m_nMaxRow-2, 1, -1, _S(3930, "¿Â¼øÇÔ »ó½Â%") + _s("   "));

	pUIManager->CreateMessageBox( MsgBoxInfo );

	int iPosX[4], iPosY[4];
	int iWidth[4], iHeight[4];

	iPosX[0] =MsgBoxInfo.m_nSpinButtonPosX -6;
	iPosY[0] =MsgBoxInfo.m_nSpinButtonPosY -3;
	iWidth[0] =0;
	iHeight[0] = 32;

	iPosX[1] =iPosX[0];
	iPosY[1] =iPosY[0];
	iWidth[1] =MsgBoxInfo.m_nWidth -iPosX[0]*2;
	iHeight[1] = 0;

	iPosX[2] =MsgBoxInfo.m_nWidth -iPosX[0];
	iPosY[2] =iPosY[0];
	iWidth[2] =0;
	iHeight[2] = 34;

	iPosX[3] =iPosX[0];
	iPosY[3] =iPosY[0] +32;
	iWidth[3] =iWidth[1];
	iHeight[3] = 0;


	WRect rcBox[4];

	rcBox[0].SetRect( iPosX[0], iPosY[0], iPosX[0]+iWidth[0], iPosY[0]+iHeight[0]);
	rcBox[1].SetRect( iPosX[1], iPosY[1], iPosX[1]+iWidth[1], iPosY[1]+iHeight[1]);
	rcBox[2].SetRect( iPosX[2], iPosY[2], iPosX[2]+iWidth[2], iPosY[2]+iHeight[2]);
	rcBox[3].SetRect( iPosX[3], iPosY[3], iPosX[3]+iWidth[3], iPosY[3]+iHeight[3]);

	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL)->SetColorBox(0, 0, rcBox[0]);
	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL)->SetColorBox(1, 0, rcBox[1]);
	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL)->SetColorBox(2, 0, rcBox[2]);
	pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL)->SetColorBox(3, 0, rcBox[3]);
	
	for(int i=1; i<=10; ++i)
	{
		if( (i*10 +nCurRate) >100 )
			break;

		CTString strData;
		strData.PrintF("%d", i*10);
		pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_MONSTER_CONTROL)->GetSpinButton().AddData(strData);
	}
}

void CUIPortal::Create_SiegeDungeon_AdmissionCtr_MsgBox(int nCurFree)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( pUIManager->DoesMessageBoxExist(MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CONTROL) )
		pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CONTROL);

	CTString strMessage;
	CUIMsgBox_Info	MsgBoxInfo;

	MsgBoxInfo.SetMsgBoxInfo( _S(3931, "´øÀü ÀÔÀå·á Á¶Á¤" ), UMBS_OKCANCEL | UMBS_SPINBUTTON , UI_PORTAL, MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CONTROL, 300 );
	
	MsgBoxInfo.AddString( _S(3932, "´øÀüÀÇ ÀÔÀå·á ¼¼À²À» ¼³Á¤ÇØÁÖ¼¼¿ä.") );

	CTString strMsg;
	strMsg.PrintF(_S(3933, "ÇöÀç ÀÔÀå·á ¼¼À²Àº %d%%ÀÔ´Ï´Ù."), nCurFree);
	MsgBoxInfo.AddString(strMsg);
	++MsgBoxInfo.m_nMaxRow;

	MsgBoxInfo.SetSpinButton(MsgBoxInfo.m_nMaxRow, 1, -1, _S(3934, "ÀÔÀå·á ¼¼À²%") + _s("   "));

	pUIManager->CreateMessageBox( MsgBoxInfo );

	for(int i=0; i<17; ++i)
	{
		CTString strData;
		strData.PrintF("%d", 70+i*5);
		pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_ADMISSION_FEE_CONTROL)->GetSpinButton().AddData(strData);
	}

}

void CUIPortal::Create_SiegeDungeon_HuntingCtr_MsgBox(int nCurFree)
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( pUIManager->DoesMessageBoxExist(MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CONTROL) )
		pUIManager->CloseMessageBox(MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CONTROL);

	CTString strMessage;
	CUIMsgBox_Info	MsgBoxInfo;

	MsgBoxInfo.SetMsgBoxInfo( _S(3935, "´øÀü ¼ö·Æ¼¼À² Á¶Á¤" ), UMBS_OKCANCEL | UMBS_SPINBUTTON , UI_PORTAL, MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CONTROL, 300 );
	
	MsgBoxInfo.AddString( _S(3936, "´øÀü ³»ÀÇ ¸ó½ºÅÍ°¡ µå·ÓÇÏ´Â ³ª½º Áß ¼ö·Æ¼¼À²¸¸Å­ÀÇ ³ª½º°¡ ¼ºÁÖ±æµåÀÇ ¼¼±ÝÀ¸·Î Áö±ÞµË´Ï´Ù.") );
	MsgBoxInfo.AddString( _S(3937, "´øÀüÀÇ ¼ö·Æ¼¼À²À» ¼³Á¤ÇØÁÖ¼¼¿ä.") );
	CTString strMsg;
	strMsg.PrintF(_S(3938, "ÇöÀç ¼ö·Æ¼¼À²Àº %d%%ÀÔ´Ï´Ù."), nCurFree);
	MsgBoxInfo.AddString(strMsg);
	++MsgBoxInfo.m_nMaxRow;

	MsgBoxInfo.SetSpinButton(MsgBoxInfo.m_nMaxRow, 1, -1, _S(3939, "¼ö·Æ¼¼À²%") + _s("   "));

	pUIManager->CreateMessageBox( MsgBoxInfo );

	for(int i=0; i<5; ++i)
	{
		CTString strData;
		strData.PrintF("%d", i*5);
		pUIManager->GetMessageBox(MSGCMD_SIEGE_DUNGEON_HUNTING_FEE_CONTROL)->GetSpinButton().AddData(strData);
	}
}
// [071115: Su-won] DRATAN_SIEGE_DUNGEON
///////////////////////////////////////////////////////////////////////////

BOOL CUIPortal::IsWarpItem(int nItemIndex)
{
	switch (nItemIndex)
	{
	case 2860: // º§ÇÇ½ºÆ® ½ÅÀü ÀÌµ¿ ÁÖ¹®¼­
	case 2861: // ÇÁ·ÎÅ°¿Â ½ÅÀü ÀÌµ¿ ÁÖ¹®¼­
	case 2862: // ¸Á°¢ÀÇ ½ÅÀü ÀÌµ¿ ÁÖ¹®¼­
	case 2863: // ¸¶¸£°¡µÒ ÁöÇÏ°¨¿Á ÀÌµ¿ ÁÖ¹®¼­
	case 2864: // ·ç½ºÆ® Æ®·ë ÀÌµ¿ ÁÖ¹®¼­
		return TRUE;
	}

	return FALSE;
}



