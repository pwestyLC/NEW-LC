// ----------------------------------------------------------------------------
//  File : CTransmogrifyUI.h
//  Desc : Created by yjpark
// ----------------------------------------------------------------------------

#ifndef	TRANSMOGRIFY_UI_H_
#define	TRANSMOGRIFY_UI_H_
#ifdef	PRAGMA_ONCE
	#pragma once
#endif

#include <Engine/Interface/UIWindow.h>

class CUIButton;
class CUIIcon;
class CUIText;

// ----------------------------------------------------------------------------
// Name : CTransmogrifyUI
// Desc :
// ----------------------------------------------------------------------------
class CTransmogrifyUI : public CUIWindow
{
protected:
	// Controls
	CUIButton*			m_btnClose;								// Close button
	CUIButton*			m_btnOK;								// OK button
	CUIButton*			m_btnCancel;							// Cancel button
	CUIIcon*			m_pIconSlotItem;						// Slot item button
	CUIText*			m_tNas;
	UIRect				m_rcInsertItem;							// Region of inserting item
	UIRect				m_rcItemSlot;
	CUIText*			m_tTitle;
	BOOL				m_bWaitRefineResult;					// If UI wait result from server or not

	// Strings
	CTString			m_strRefineMoney;						// String of refine money
	SQUAD				m_llRefineMoney;						// Refine money

protected:

	// Command functions
	void	SetTransmogrifyItem();

	// Network message functions ( send )
	void	SendTransmogrifyReq();

public:
	CTransmogrifyUI();
	~CTransmogrifyUI();
	
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
	void	TransmogrifyRep( SBYTE sbResult );
};


#endif	// CTransmogrifyUI

