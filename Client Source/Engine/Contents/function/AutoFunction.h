#ifndef __AUTOFUNC_UI_H__
#define __AUTOFUNC_UI_H__

#include <Engine/Interface/UIWindow.h>
#include <Interface/UICheckButton.h>
//test
class CUIBase;
class CUIButton;
class CUIComboBox;

class CAutoFuncUI : public CUIWindow
{
public:
	CAutoFuncUI();
	~CAutoFuncUI();
	
	void initialize();

public:
	void	ToggleWindow();
	void	ResAutoSettingData(CNetworkMessage* istr);

	void	Save();

protected:
	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);

	// Auto-functions
	int				prePickUp;
	int				preIgni;
	int				preSell;
	

private:
	enum
	{
		eCOMBO_AUTOPICKUP,
		eCOMBO_AUTOIGNI,
		eCOMBO_AUTOSELL,
		eCOMBO_MAX
	};

	void open();
	void close();

	CUIComboBox*	m_pComboOption[eCOMBO_MAX];
	CUIButton*		m_btn_save;
	CUIButton*		m_btn_close;
	bool			m_bDrag;
	int				m_nOriX, m_nOriY;
	CUIBase*		m_pDragArea;
};

#endif // __AUTOFUNC_UI_H__