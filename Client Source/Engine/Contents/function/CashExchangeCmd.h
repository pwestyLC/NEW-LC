#ifndef _CASHEXCHANGE_CMD_H_
#define _CASHEXCHANGE_CMD_H_

class Command;

class CmdCashExchangeClose : public Command
{
public:
	CmdCashExchangeClose() : pUI(NULL) {}
	void setData(CCashExchangeUI* pUI) { pUI = pUI; }
	void execute() {
		if (pUI)
			pUI->CloseUI();
	}
private:
	CCashExchangeUI* pUI;
};

class CmdCashExchangeNumericInput : public Command
{
public:
	CmdCashExchangeNumericInput() : m_pWnd(NULL), m_nCommandCode(0) {}
	void setData(CCashExchangeUI* pWnd, int nCommandCode)
	{
		m_pWnd = pWnd;
		m_nCommandCode = nCommandCode;
	}
	void execute() 
	{
		if (m_pWnd)
		{
			// Get the input value from the numeric message box
			CUIManager* pUIManager = CUIManager::getSingleton();
			if (pUIManager == NULL)
				return;

			CUIMsgBoxNumericOnly* pNumBox = pUIManager->GetMsgBoxNumOnly();
			if (pNumBox == NULL)
				return;

			// Get the numeric value that was entered
			SQUAD llValue = pNumBox->GetData();

			// Convert to string for the callback
			CTString strInput;
			strInput.PrintF("%I64d", llValue);

			// Call the message box handler with the input
			m_pWnd->MsgBoxCommand(m_nCommandCode, TRUE, strInput);
		}
	}
private:
	CCashExchangeUI* m_pWnd;
	int m_nCommandCode;
};

#endif // _CASHEXCHANGE_CMD_H_
