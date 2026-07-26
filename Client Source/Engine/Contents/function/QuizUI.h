#ifndef __QUIZ_UI_H__
#define __QUIZ_UI_H__

#include <Engine/Interface/UIWindow.h>


class CUIBase;
class CUIButton;
class CUIComboBox;

class CQuizUI : public CUIWindow
{
public:
	CQuizUI();
	~CQuizUI();

	void initialize();

public:
	void	ToggleWindow();

	void	Save();

protected:
	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);

	// Auto-functions
	int				preIgni;
	int				prePickUp;

private:
	enum
	{
		eCOMBO_AUTOPICKUP,
		eCOMBO_AUTOIGNI,
		eCOMBO_MAX
	};

	void open();
	void close();

	CUIComboBox* m_pComboOption[eCOMBO_MAX];
	CUIButton* m_btn_save;
	CUIButton* m_btn_close;

	bool			m_bDrag;
	int				m_nOriX, m_nOriY;
	CUIBase* m_pDragArea;
};

#endif
#endif