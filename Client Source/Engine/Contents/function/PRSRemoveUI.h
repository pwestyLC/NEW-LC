// ----------------------------------------------------------------------------
//  File : CPRSRemoveUI.h
//  Desc : Created by alanssoares
// ----------------------------------------------------------------------------

#ifndef	PRS_REMOVE_UI_H_
#define	PRS_REMOVE_UI_H_
#ifdef	PRAGMA_ONCE
	#pragma once
#endif

#include <Engine/Interface/UIWindow.h>

class CUIButton;
class CUIIcon;
class CUIText;

// ----------------------------------------------------------------------------
// Name : CPRSRemoveUI
// Desc :
// ----------------------------------------------------------------------------
class CPRSRemoveUI : public CUIWindow
{
protected:
	// Controls
	CUIButton*			m_btnClose;								// Close button
	CUIButton*			m_btnOK;								// OK button
	CUIButton*			m_btnCancel;							// Cancel button
	CUIIcon*			m_pIconSlotItem[2];						// Slot item button
	UIRect				m_rcInsertItem[2];						// Region of inserting item
	UIRect				m_rcItemSlot[2];
	CUIText*			m_tTitle;

protected:

	// Network message functions ( send )
	void	SendPRSRemoveReq();

public:
	CPRSRemoveUI();
	~CPRSRemoveUI();
	
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
	void	BoxOpenRep( SBYTE sbResult );
};


#endif	// CPRSRemoveUI

