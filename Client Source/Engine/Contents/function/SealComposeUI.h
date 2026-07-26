// ----------------------------------------------------------------------------
//  File : CSealComposeUI.h
//  Desc : Created by alanssoares
// ----------------------------------------------------------------------------

#ifndef	SEAL_COMPOSE_UI_H_
#define	SEAL_COMPOSE_UI_H_
#ifdef	PRAGMA_ONCE
	#pragma once
#endif

#include <Engine/Interface/UIWindow.h>

class CUIButton;
class CUIIcon;
class CUIText;

// ----------------------------------------------------------------------------
// Name : CSealComposeUI
// Desc :
// ----------------------------------------------------------------------------
class CSealComposeUI : public CUIWindow
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
	void	SendSealsComposeReq();

public:
	CSealComposeUI();
	~CSealComposeUI();
	
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
	void	SealComposeRep( SBYTE sbResult, LONG total, CTString name );
};


#endif	// CSealComposeUI

