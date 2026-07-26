#ifndef	_UIREPORT_H_
#define	_UIREPORT_H_
#ifdef	PRAGMA_ONCE
#pragma once
#endif

#include <Engine/Interface/UIWindow.h>

class CUIEditBox;
class CUIText;
class CUIImage;
class CUIButton;
class CUIComboBox;
class CUIBase;


#define MAX_REASON 9
class CUIReport : public CUIWindow
{
public:
	CUIReport();
	~CUIReport();

	void initialize();
	void Open();
	void Close();
	void Send();

	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg); 
	WMSG_RESULT OnKeyMessage(MSG* pMsg);

	BOOL IsEditBoxFocused();

	char* m_strNick;
	char* m_strDesc;
	int   m_selReason;

private:
	CUIImage* m_bg;

	CUIButton* m_send; // Отправка
	CUIButton* m_close;

	CUIText* m_nicktext;
	CUIText* m_desctext;

	CUIEditBox* m_nick;
	CUIEditBox* m_desc;

	CUIComboBox* m_reason;


	bool		m_bDrag;
	int			m_nOriX, m_nOriY;
};

class CUIReportClose : public Command
{
public:
	CUIReportClose() : _pUI(NULL) {}
	void SetData(CUIReport* rep) { _pUI = rep; }

	void execute()
	{
		if (_pUI != NULL)
			_pUI->Close();
	}
private:
	CUIReport* _pUI;
};

class CUIReportSend : public Command
{
public:
	CUIReportSend() : _pUI(NULL) {}
	void SetData(CUIReport* rep) { _pUI = rep; }

	void execute()
	{
		if (_pUI != NULL)
			_pUI->Send();
	}
private:
	CUIReport* _pUI;
};
#endif