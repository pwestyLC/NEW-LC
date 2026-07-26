#include "StdH.h"
#include "UIReport.h"
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIButton.h>
#include <Engine/Interface/UIEditBox.h>
#include <Engine/Interface/UITextBox.h>
#include <Engine/Interface/UIText.h>
#include <Engine/Interface/UIImage.h>


CUIReport::CUIReport() 
	:m_nicktext(NULL)
	,m_desctext(NULL)
	,m_nick(NULL)
	,m_desc(NULL)
	,m_send(NULL)
	,m_close(NULL)
    ,m_reason(NULL)

{

}


CUIReport::~CUIReport()
{
	Destroy();
}

void CUIReport::initialize()
{
	
	CTString strAll[MAX_REASON] = { _S(9394, ""), _S(9395, ""), _S(9396, ""), _S(9397, ""), _S(9398, ""), _S(9399, ""), _S(9400, ""), _S(9401, ""), _S(9402, "") };

	m_bg = (CUIImage*)findUI("bg");

	m_nicktext = (CUIText*)findUI("nick");
	m_desctext = (CUIText*)findUI("desc");

	m_nick = (CUIEditBox*)findUI("nick_text");

	m_desc = (CUIEditBox*)findUI("desc_text");

	m_reason = (CUIComboBox*)findUI("combo");
	for (int i = 0; i < MAX_REASON; ++i)
		m_reason->AddString(strAll[i]);
	
	
	m_send = (CUIButton*)findUI("send");
	if (m_send != NULL)
	{
		CUIReportSend* pSend = new CUIReportSend;
		pSend->SetData(this);
		m_send->SetCommand(pSend);
	}

	m_close = (CUIButton*)findUI("close");
	if (m_close != NULL)
	{
		CUIReportClose* pClose = new CUIReportClose;
		pClose->SetData(this);
		m_close->SetCommand(pClose);
	}

	
	
}

	void CUIReport::Open()
	{
		//CUIManager* pUIMgr = CUIManager::getSingleton();
		
		Hide(FALSE);
		SetVisible(TRUE);
		UIMGR()->RearrangeOrder(UI_REPORT, TRUE);
	}

	void CUIReport::Close()
	{		
		m_nick->ResetString();
		m_desc->ResetString();
		m_reason->SetCurSel(0);

		Hide(TRUE);
		SetVisible(FALSE);
		UIMGR()->RearrangeOrder(UI_REPORT, FALSE);
	}

	WMSG_RESULT CUIReport::OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg)
	{
		WMSG_RESULT	wmsgResult;

		if ((wmsgResult = m_send->MouseMessage(pMsg)) != WMSG_FAIL)
		{
			if (wmsgResult == WMSG_COMMAND)
				Send();
		}

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


		CUIManager::getSingleton()->SetMouseCursorInsideUIs();

		return WMSG_FAIL;
	}

	WMSG_RESULT CUIReport::OnLButtonUp(UINT16 x, UINT16 y)
	{
         m_bDrag = false;
		 

		 if (IsInside(x, y) == FALSE)
			 return WMSG_FAIL;


		CUIManager::getSingleton()->ResetHoldBtn();
		return CUIBase::OnLButtonUp(x, y);
	}

	WMSG_RESULT CUIReport::OnLButtonDown(UINT16 x, UINT16 y)
	{
		if (IsInside(x, y) == FALSE)
			return WMSG_FAIL;

		if (m_bg && m_bg->IsInside(x, y))
		{
			m_bDrag = true;
			m_nOriX = x;
			m_nOriY = y;
		}

		CUIManager::getSingleton()->RearrangeOrder(UI_REPORT, TRUE);

		return CUIBase::OnLButtonDown(x, y);
	}

	BOOL CUIReport::IsEditBoxFocused()
	{
		if (m_nick || m_desc)
		{
			return m_nick->IsFocused() || m_desc->IsFocused();
		}

		return FALSE;
	}

	WMSG_RESULT CUIReport::OnKeyMessage(MSG* pMsg)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			if (m_nick != NULL &&
				(m_nick->GetString() != NULL || m_nick->GetString() != "")
				&& m_desc != NULL
				&& (m_desc->GetString() != NULL || m_desc->GetString() != ""))
			{
                  if (m_send != NULL)
					{
						if (m_send->IsEnabled() == FALSE)
							return WMSG_FAIL;

						Send();
						return WMSG_SUCCESS;
					}
				
			}
		}
		else if (pMsg->wParam == 0x27)
		{
			Close();
		}

		return WMSG_FAIL;
	} 

	void CUIReport::Send()
	{

		CTString text,desc;
		text = m_nick->GetString();
		desc = m_desc->GetString();
		if (text.Length() <= 3 || text.Length() >= 17)
		{
			CUIManager* pUIMgr = CUIManager::getSingleton();
			CUIMsgBox_Info MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(8160, ""), UMBS_OK, UI_NONE, MSGCMD_REPORT_ERROR);
            MsgBoxInfo.AddString(_S(8161, ""));

			if (pUIMgr)
			pUIMgr->CreateMessageBox(MsgBoxInfo);
			return;
		}
		else if (desc.Length() <= 6 || desc.Length() >= 351)
		{
			CUIManager* pUIMgr = CUIManager::getSingleton();
			CUIMsgBox_Info MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(8160, ""), UMBS_OK, UI_NONE, MSGCMD_REPORT_ERROR);
			MsgBoxInfo.AddString(_S(8162, ""));

			if (pUIMgr)
				pUIMgr->CreateMessageBox(MsgBoxInfo);
			return;
		}

		if ((m_nick != NULL && m_nick->GetString() != "") && (m_desc != NULL && m_desc->GetString() != "") && m_reason->GetCurSel() > -1 && m_reason->GetCurSel() <= 8) {
			m_strNick = m_nick->GetString();
			m_strDesc = m_desc->GetString();
			m_selReason = m_reason->GetCurSel();

			if (m_strNick != "" && m_strDesc != "" && m_selReason >= 0)
			{
				_pNetwork->SendReport(m_strNick, m_strDesc, m_selReason);
			}
		}
	}