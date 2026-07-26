#ifndef		_PERSONALSHOP_CMD_H_
#define		_PERSONALSHOP_CMD_H_

class Command;

class CmdPSClose : public Command
{
public:
	CmdPSClose() : pUI(NULL) {}
	void setData(CUIPersonalshopNew* pShop)		{ pUI = pShop; }
	void execute() {
		if (pUI)
			pUI->OpenPersonalShop(false);
	}

private:
	CUIPersonalshopNew*		pUI;
};

class CmdPersnalShopAddItem : public Command
{
public:
	CmdPersnalShopAddItem() : m_pWnd(NULL)	{}
	void setData(CUIPersonalshopNew* pWnd)	{ m_pWnd = pWnd;	}
	void execute() 
	{
		if (m_pWnd != NULL)
			m_pWnd->AddItemCallback();
	}
private:
	CUIPersonalshopNew* m_pWnd;
};

class CmdPersnalShopDelItem : public Command
{
public:
	CmdPersnalShopDelItem() : m_pWnd(NULL)	{}
	void setData(CUIPersonalshopNew* pWnd)	{ m_pWnd = pWnd;	}
	void execute() 
	{
		if (m_pWnd != NULL)
			m_pWnd->DelItemCallback();
	}
private:
	CUIPersonalshopNew* m_pWnd;
};

class CmdPSProcCmd : public Command
{
public:
	CmdPSProcCmd() : eCmd(CUIPersonalshopNew::CMD_NONE), _ui(NULL), eSlot(CUIPersonalshopNew::SLOT_TRADE) {}
	void setData(CUIPersonalshopNew::eCMD_TYPE cmd, CUIPersonalshopNew* pUI, CUIPersonalshopNew::eSlotType type) {
		eCmd = cmd;	_ui = pUI; eSlot = type; 
	}

	void execute() {
		if (_ui) {
			_ui->proc_command(eCmd, eSlot);
		}
	}

private:
	CUIPersonalshopNew::eCMD_TYPE	eCmd;
	CUIPersonalshopNew*		_ui;
	CUIPersonalshopNew::eSlotType	eSlot;
};

class CmdPSMsgBox : public Command
{
public:
	CmdPSMsgBox() : m_pWnd(NULL), m_nCommandCode(0) {}
	void setData(CUIPersonalshopNew* pWnd, int nCommandCode)
	{
		m_pWnd = pWnd;
		m_nCommandCode = nCommandCode;
	}
	void execute() 
	{
		// Placeholder - cash exchange moved to separate NPC system
	}
private:
	CUIPersonalshopNew* m_pWnd;
	int m_nCommandCode;
};

#endif		// _PERSONALSHOP_CMD_H_