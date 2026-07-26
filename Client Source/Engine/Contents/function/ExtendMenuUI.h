// ----------------------------------------------------------------------------
//  File : ExtendMenuUI.H
//  Desc : Created by alan
// ----------------------------------------------------------------------------

#ifndef	EXTEND_MENU_UI_H_
#define	EXTEND_MENU_UI_H_
#ifdef	PRAGMA_ONCE
	#pragma once
#endif

class CUIButton;
class CUIIcon;
class CUIText;

// ----------------------------------------------------------------------------
// Name : CExtendMenuUI
// Desc :
// ----------------------------------------------------------------------------
class CExtendMenuUI : public CUIWindow
{
protected:
	// Controls
	CUIButton*			m_btnClose;								// Close button
	CUIButton*			m_btnOK;								// OK button
	CUIButton*			m_btnCancel;							// Cancel button
	CUIButton*			m_btn1Day;
	CUIButton*			m_btn7Day;
	CUIButton*			m_btn30Day;
	CUIIcon*			m_pIconSlotItem;						// Slot item button
	UIRect				m_rcInsertItem;							// Region of inserting item
	UIRect				m_rcItemSlot;
	CUIText*			m_tTitle;
	BOOL				m_bWaitRefineResult;					// If UI wait result from server or not

protected:

	// Command functions
	void	SetExtendMenuItem();
	
	// Network message functions ( send )
	void	SendExtendMenuReq(int days);

public:
	CExtendMenuUI();
	~CExtendMenuUI();

	// Render
	void	Render();

	void 	openUI();
	void	closeUI();

	void	initialize();

	// Adjust position
	void	ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void	AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );

	// Messages
	WMSG_RESULT	MouseMessage( MSG *pMsg );

	// Network message functions ( receive )
	void	ExtendMenuRep( SBYTE sbResult );
};


#endif	// EXTEND_MENU_UI_H_

