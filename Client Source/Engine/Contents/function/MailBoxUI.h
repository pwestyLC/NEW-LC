#pragma once

#include "Interface/UITrackPopup.h" // cant use global include lel

class CUITab;
class CUIText;
class CUIList;
class CUImage;
class CUIButton;
class MailBoxManager;

class CUIMailBox : public CUIWindow
{
public:
	CUIMailBox();
	~CUIMailBox();

	void	initialize();
	void	ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);
	void	AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);
	void	MsgBoxCommand(int nCommandCode, BOOL bOK, CTString& strInput);

	void	OpenUI();
	void	CloseUI();

	void	UpdateUI();
	void	OnPostRender(CDrawPort* pDraw);

	void	DeleteMail();
	void	DeleteAllMails();

	void	RequestDeleteMail();
	void	RequestDeleteAllMails();

	void	RefreshLetters();
	void	WriteLetter();
	void	OpenLetter();
	void	BlockUser();

	void	MarkAsReaded(int page, int pos);
	void	MarkAsCollected(int page, int pos);

	void	SelectLastMail();

public:
	enum Lists
	{
		Received,
		Sent,
		SystemMail,
		MaxList
	};

	enum Buttons
	{
		Close,
		DeleteAll,
		Write,
		Open,
		Delete,
		Refresh,
		MaxBtn
	};

	enum PopupButtons
	{
		PopupBlock = 1,
		PopupDelete
	};

protected:
	WMSG_RESULT OnRButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnLButtonDBLClick(UINT16 x, UINT16 y);
	WMSG_RESULT OnKeyMessage(MSG* pMsg);

private:
	void PrepareOpening();
	void PrepareClosing();
	void ClearListsItems();
	void OpenPopupMenu(UINT16 x, UINT16 y);

private:
	bool isMove;
	int nX,
		nY;
	CUIBase*	m_moveArea;
	CUITab*		m_tab;
	CUIList*	m_lists[Lists::MaxList];
	CUIButton*	m_buttons[Buttons::MaxBtn];
	MailBoxManager* m_pManager;
	CUITrackPopup	m_popupMenu;
};
