// ----------------------------------------------------------------------------
//  File : CBoxOpenUI.h
//  Desc : Created by yjpark
// ----------------------------------------------------------------------------

#ifndef	BOX_OPEN_UI_H_
#define	BOX_OPEN_UI_H_
#ifdef	PRAGMA_ONCE
	#pragma once
#endif

#include <Engine/Interface/UIWindow.h>

class CUIButton;
class CUIIcon;
class CUIText;

// ----------------------------------------------------------------------------
// Name : CBoxOpenUI
// Desc :
// ----------------------------------------------------------------------------
class CBoxOpenUI : public CUIWindow
{
protected:
	// Controls
	CUIButton*			m_btnClose;								// Close button
	CUIButton*			m_btnOK;								// OK button
	CUIButton*			m_btnCancel;							// Cancel button
	CUIIcon*			m_pIconSlotItem;						// Slot item button
	UIRect				m_rcInsertItem;							// Region of inserting item
	UIRect				m_rcItemSlot;
	CUIText*			m_tTitle;
	BOOL				m_bWaitResult;					// If UI wait result from server or not

protected:

	// Network message functions ( send )
	void	SendOpenBoxReq();

public:
	CBoxOpenUI();
	~CBoxOpenUI();
	
	// Render
	void	Render();

	void 	openUI();
	void	closeUI();

	void	initialize();

	void	PutOnCallBack();
	void	PutOnCancelCallBack();

	// Adjust position
	void	ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void	AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );

	// Messages
	WMSG_RESULT	MouseMessage( MSG *pMsg );

	// Network message functions ( receive )
	void	BoxOpenRep( SBYTE sbResult );
};


#endif	// CBoxOpenUI

