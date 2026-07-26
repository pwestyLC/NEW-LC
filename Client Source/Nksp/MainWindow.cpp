/*
 *  Serious Sam
 *  Copyright (c) 1998, CroTeam. All rights reserved.
 *
 */

#include "StdH.h"
#include "MainWindow.h"
#include "resource.h"
#include "CmdLine.h"
#include "Engine/GameState.h"
#include <Engine/Network/Web.h>
#ifdef REZABOT
#include <Engine/ReZaBot.h>
#endif
 //#include "Social/TLastChaosApplication.h"
#include <Engine/Interface/UIManager.h>
#include <Engine/Interface/UIOption.h>
#ifdef KALYDO
#include <Nksp/Social/TLastChaosApplication.h>
#include <Engine/Kalydo/PackageManager.h>

extern ENGINE_API HWND	g_KalydoWindowHandle;
#endif

extern PIX		_pixDesktopWidth;
extern PIX		_pixDesktopHeight;

extern ENGINE_API INDEX	sam_bBorderlessActive;
extern ENGINE_API BOOL	_bWindowChanging;    // ignores window messages while this is set	// yjpark
extern ENGINE_API HWND	_hwndMain;
extern ENGINE_API HWND	_hDlgWeb;
extern ENGINE_API cWeb  g_web;
// kalydo 
extern HWND g_parenthWnd;
extern ENGINE_API INDEX sam_bFullScreenActive;
static char achWindowTitle[256]; // current window title

static HBITMAP _hbmSplash = NULL;
static BITMAP  _bmSplash;


// for window reposition function
static PIX _pixLastSizeI, _pixLastSizeJ;

BOOL _bIMEProc = false; // ÀÌ±âÈ¯ ¼öÁ¤ 11.12

//	±è¿µÈ¯:
bool	_bWinSize = false;

static void QuitGame(void)
{
	_pGameState->Running()		= FALSE;
	_pGameState->QuitScreen()	= FALSE;
}

// window procedure active while window changes are occuring
long FAR PASCAL WindowProc_WindowChanging( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
	switch( message ) {
	case WM_POWERBROADCAST:
		{
//			delete _pTimer;
//			_pTimer = new CTimer;
			if ( wParam == PBT_APMQUERYSUSPEND )
				return BROADCAST_QUERY_DENY;
			else if ( wParam == PBT_APMBATTERYLOW )
			{
				MessageBox(NULL,"Battery power is low.","Warning!",MB_OK);
			}
			return true;
		} break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);

		return 0;
	} break;
	case WM_ERASEBKGND: {

		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		RECT rect;
		GetClientRect(hWnd, &rect);
		FillRect(ps.hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
		//¾ÈÅÂÈÆ ¼öÁ¤ ½ÃÀÛ	//(DevPartner Bug Fix)(2005-01-10)
				//HDC hdcMem = CreateCompatibleDC(ps.hdc); 
		//¾ÈÅÂÈÆ ¼öÁ¤ ³¡	//(DevPartner Bug Fix)(2005-01-10)
				//SelectObject(hdcMem, _hbmSplash); 
				//BitBlt(ps.hdc, 0, 0, _bmSplash.bmWidth, _bmSplash.bmHeight, hdcMem, 0, 0, SRCCOPY); 
		//		StretchBlt(ps.hdc, 0, 0, rect.right, rect.bottom,
		//		hdcMem, 0,0, _bmSplash.bmWidth, _bmSplash.bmHeight, SRCCOPY); 

		EndPaint(hWnd, &ps); 

		return 1; 
	} break;
	case WM_CLOSE:
		return 0;
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// window procedure active normally
long FAR PASCAL WindowProc_Normal( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
	switch( message ) {
#if 1
	// forget erase bacground messages
	//if (Msg==WM_ERASEBKGND) return TRUE;
	case WM_ERASEBKGND:
		return TRUE;
#endif
	case WM_POWERBROADCAST:
		{
//			delete _pTimer;
//			_pTimer = new CTimer;
			if ( wParam == PBT_APMQUERYSUSPEND )
				return BROADCAST_QUERY_DENY;
			else if ( wParam == PBT_APMBATTERYLOW )
			{
				MessageBox(NULL,"Battery power is low","Warning!",MB_OK);
			}
			return true;
		} break;
	// system commands
	case WM_SYSCOMMAND: 
		{
			switch( wParam & ~0x0F) 
			{
            #ifdef REZABOT
		case SC_CLOSE:
		{
			SE_Get_UIManagerPtr()->GetReZaBotUI()->EndBOT();
			Sleep(100);//3000
		}
		break;
#endif
				// window resizing messages
				case SC_MINIMIZE:
				case SC_RESTORE:
				case SC_MAXIMIZE:
				  if (g_web.IsWebHandle())
				  {
					  HWND tmpDlg = g_web.GetWebHandle();
					  if (g_web.CloseWebPage(tmpDlg) == TRUE)
					  {
						ShowWindow(tmpDlg, SW_HIDE);
					  }
					  UpdateWindow(tmpDlg);
				  }
					// do not allow automatic resizing
					break;
					// prevent screen saver and monitor power down
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					break;
			}
		} break;
	// when close box is clicked
	case WM_CLOSE:
		// relay to application
        #ifdef REZABOT
		SE_Get_UIManagerPtr()->GetReZaBotUI()->EndBOT();
		Sleep(100);//2000
#endif
		QuitGame();
		break;
	case WM_MOVE:
		{
			if (g_web.GetWebHandle())
			{
				g_web.UpdatePos();
				SetFocus(g_web.GetWebHandle());
			}
		}
		break;

	// some standard focus loose/gain messages
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_CANCELMODE:
	case WM_SETFOCUS:
	case WM_KILLFOCUS:
	case WM_ACTIVATEAPP:
	//case WM_SETCURSOR:
	case WM_MOUSEMOVE:
	case WM_INPUTLANGCHANGE:
	case WM_INPUTLANGCHANGEREQUEST:
		break;
	case WM_EXITSIZEMOVE:
	{
		//	±è¿µÈ¯ : À©µµ¿ì Ã¢ Å©±â º¯°æÀÌ ¹ß»ýÇÑ °æ¿ì
		if ((sam_bFullScreenActive != 1) && (_bWinSize))
		{
			//	À©µµ¿ì ¸ðµå¿¡¼­ Å©±â º¯°æÀÌ ¹ß»ýÇÑ °æ¿ì¿¡¸¸,
			_bWinSize = false;


			RECT	t_Rect;
			GetClientRect(_hwndMain, &t_Rect);
			long t_Width = t_Rect.right - t_Rect.left;
			long t_Height = t_Rect.bottom - t_Rect.top;

			sam_iScreenSizeI = t_Width;
			sam_iScreenSizeJ = t_Height;

			SE_Get_UIManagerPtr()->SetTitleName(sam_bFullScreenActive, sam_iScreenSizeI, sam_iScreenSizeJ);
			//ResetMainWindowNormal(false);
			//Set_Window_Size();
			_pvpViewPortMain->Resize();
			SE_Get_UIManagerPtr()->SetWidth(t_Width);
			SE_Get_UIManagerPtr()->SetHeight(t_Height);

			SE_Get_UIManagerPtr()->UPDATESHIT();



			// create canvas
			ASSERT(_pdpNormalMain == NULL);
			_pGfx->CreateWindowCanvas(_hwndMain, &_pvpViewPortMain, &_pdpNormalMain);

			// erase context of both buffers (for the sake of wide-screen)
			_pdpMain = _pdpNormalMain;
			if (_pdpMain != NULL && _pdpMain->Lock()) {
				_pdpMain->Fill(C_BLACK | CT_OPAQUE);
				_pdpMain->Unlock();
				_pvpViewPortMain->SwapBuffers();
			}

			//SE_Get_UIManagerPtr()->SetUIGameState();
			//SE_Get_UtilHelpPtr()
			SE_Get_UIManagerPtr()->GetOption()->InitInterface();



		}
		break;
		}
	case WM_SIZE:
		{
			//	±è¿µÈ¯ : À©µµ¿ì Ã¢ Å©±â º¯°æÀÌ ¹ß»ýÇÑ °æ¿ì º¯¼ö ¼³Á¤.
			_bWinSize = true;
#ifdef KALYDO
			sam_bFullScreenActive = 0;
#endif
			break;
		}
	case WM_GETMINMAXINFO:
		{
			(reinterpret_cast<MINMAXINFO*>(lParam))->ptMaxTrackSize.x = 2200;
			(reinterpret_cast<MINMAXINFO*>(lParam))->ptMaxTrackSize.y = 1500;
		}
		break;
#ifdef KALYDO
	case WM_KRFREQUEST:
		{
			//(dynamic_cast<TLastChaosApplication*>(application))->requestZoneKRF( KPackManager::GetInstance()->GetZoneNo() );
			(dynamic_cast<TLastChaosApplication*>(application))->requestZoneKRF( static_cast<unsigned int>(wParam) );
		}
		break;
#endif
	}

	// if we get to here, we pass the message to default procedure
	return _bIMEProc?0:DefWindowProc(hWnd, message, wParam, lParam);  // ÀÌ±âÈ¯ ¼öÁ¤ 11.12
}


BOOL CALLBACK WebDialogProcPtr(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg >= WM_MOUSEFIRST && uMsg <= WM_MOUSELAST)
		return TRUE;

	switch(uMsg)
	{
	case WM_PARENTNOTIFY:
		{
			WORD loMessage = LOWORD(wParam);

			if (loMessage == WM_DESTROY)
			{
				if (g_web.IsWebHandle())
				{
					ShowWindow(hDlg, SW_HIDE);
					UpdateWindow(hDlg);
				}
			}
		}
		break;
	case WM_SHOWWINDOW:
		{
			if (g_web.IsWebHandle())
			{
				g_web.CloseWebPage(hDlg);
			}
			else
			{
				g_web.OpenWebPage(hDlg);
			}
		}
		break;
	case WM_DESTROY:
		{
			g_web.CloseWebPage(hDlg);
		}
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

// main window procedure
long FAR PASCAL WindowProc( HWND hWnd, UINT message, 
			    WPARAM wParam, LPARAM lParam )
{
	/*if (message == WM_SETCURSOR) {
		message = message; 
		return 1;
	}*/
	if(_bWindowChanging) {
		return WindowProc_WindowChanging(hWnd, message, wParam, lParam);
	} else {
		return WindowProc_Normal(hWnd, message, wParam, lParam);
	}
}


// init/end main window management
void MainWindow_Init(void)
{
	// register the window class
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hInstanceMain;
	wc.hIcon = LoadIcon( _hInstanceMain, (LPCTSTR)IDR_ICON_BLUE );
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = APPLICATION_NAME;
	wc.lpszClassName = APPLICATION_NAME;
	wc.hIconSm = NULL;
	RegisterClassEx(&wc);

	// load bitmaps
	_hbmSplash = LoadBitmap(_hInstanceMain, (char*)IDB_SPLASH);
	ASSERT(_hbmSplash!=NULL);
	GetObject(_hbmSplash, sizeof(BITMAP), (LPSTR) &_bmSplash); 
	// here was loading and setting of no-windows-mouse-cursor

#ifdef KALYDO
	KalydoUserData();
	g_KalydoWindowHandle = application->getKalydoWindow();
#endif
}


void MainWindow_End(void)
{
	DeleteObject(_hbmSplash);
}


// close the main application window
void CloseMainWindow(bool p_Exit)
{
	if (_hDlgWeb!=NULL)
	{
		g_web.CloseWebPage(_hDlgWeb);
		DestroyWindow(_hDlgWeb);
		g_web.SetWebHandle(NULL);
	}

	// if window exists
	//	±è¿µÈ¯ : ÁøÂ¥ Á¾·áÀÎ°æ¿ì¸¸.
	if(p_Exit)
	{
		if( _hwndMain!=NULL) {
			// destroy it
			DestroyWindow(_hwndMain);
			_hwndMain = NULL;
		}
	}
}

void ResetMainWindowNormal(bool p_Center)
{
	// screen change bug in fullscreen. [9/27/2011 rumist]
	// ±è¿µÈ¯ ÀÌ°Å Á¦°Å. ±ô¹Ú°Å¸²
	// ShowWindow( _hwndMain, SW_HIDE);

	if (sam_bFullScreenActive)
	{
		HDC hDC = GetDC(GetDesktopWindow());
		int iDesktopBitsPixel = GetDeviceCaps(hDC, BITSPIXEL);
		int iDesktopWidth = GetDeviceCaps(hDC, HORZRES);
		int iDesktopHeight = GetDeviceCaps(hDC, VERTRES);
		ReleaseDC(GetDesktopWindow(), hDC);

		DEVMODE dm;
		memset(&dm, 0, sizeof(dm));
		dm.dmSize = sizeof(dm);
		dm.dmPelsWidth = _pixLastSizeI;
		dm.dmPelsHeight = _pixLastSizeJ;
		dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
		ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
	}

#ifdef PLATFORM_WIN32
	int iFullscreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
	int iFullscreenHeight = ::GetSystemMetrics(SM_CYSCREEN);

	ShowWindow(_hwndMain, SW_HIDE);

	PIX pixWidth = 0;
	PIX pixHeight = 0;

	if (sam_bBorderlessActive)
	{
		pixWidth = _pixLastSizeI;
		pixHeight = _pixLastSizeJ;
	}
	else
	{
		// add edges and title bar to window size so client area would have size that we requested
		RECT rWindow, rClient;
		GetClientRect(_hwndMain, &rClient);
		GetWindowRect(_hwndMain, &rWindow);

		pixWidth = _pixLastSizeI + (rWindow.right - rWindow.left) - (rClient.right - rClient.left);
		pixHeight = _pixLastSizeJ + (rWindow.bottom - rWindow.top) - (rClient.bottom - rClient.top);
	}

	const PIX pixPosX = (iFullscreenWidth - pixWidth) / 2;
	const PIX pixPosY = (iFullscreenHeight - pixHeight) / 2;

	if (sam_bBorderlessActive)
	{
		LONG lStyle = GetWindowLong(_hwndMain, GWL_STYLE);
		lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
		SetWindowLong(_hwndMain, GWL_STYLE, lStyle);
		LONG lExStyle = GetWindowLong(_hwndMain, GWL_EXSTYLE);
		lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
		SetWindowLong(_hwndMain, GWL_EXSTYLE, lExStyle);
	}

	// set new window size and show it
	SetWindowPos(_hwndMain, NULL, pixPosX, pixPosY, pixWidth, pixHeight, SWP_NOZORDER);
	ShowWindow(_hwndMain, SW_SHOW);
#endif
}

void ResetMainWindowNormal_old(bool p_Center)
{
	// ±è¿µÈ¯ ÀÌ°Å Á¦°Å. ±ô¹Ú°Å¸²
	// ShowWindow( _hwndMain, SW_HIDE);

	if (sam_bFullScreenActive)
	{
		HDC hDC = GetDC( GetDesktopWindow() );
		int iDesktopBitsPixel = GetDeviceCaps( hDC, BITSPIXEL );
		int iDesktopWidth = GetDeviceCaps( hDC, HORZRES );
		int iDesktopHeight = GetDeviceCaps( hDC, VERTRES );
		ReleaseDC( GetDesktopWindow(), hDC );

		DEVMODE dm;
		memset( &dm, 0, sizeof( dm ) );
		dm.dmSize = sizeof( dm );
		dm.dmPelsWidth  = _pixLastSizeI;
		dm.dmPelsHeight = _pixLastSizeJ;
		dm.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
		ChangeDisplaySettings( &dm, CDS_FULLSCREEN );
	}

	int pixPosX,pixPosY;
	PIX pixWidth, pixHeight;

	if( sam_bFullScreenActive )
	{
		pixPosX = 0;
		pixPosY = 0;

		pixWidth  = _pixLastSizeI;
		pixHeight = _pixLastSizeJ;
	}
	else
	{
		// add edges and title bar to window size so client area would have size that we requested
		RECT rWindow, rClient;
		GetClientRect( _hwndMain, &rClient);
		GetWindowRect( _hwndMain, &rWindow);
		pixWidth  = _pixLastSizeI + (rWindow.right-rWindow.left) - (rClient.right-rClient.left);
		pixHeight = _pixLastSizeJ + (rWindow.bottom-rWindow.top) - (rClient.bottom-rClient.top);
		
		if (cmd_iWindowLeft > 0) {    
			pixPosX = cmd_iWindowLeft>(::GetSystemMetrics(SM_CXSCREEN))?(::GetSystemMetrics(SM_CXSCREEN)):cmd_iWindowLeft;
			cmd_iWindowLeft = -1;
		} else {
			pixPosX   = (::GetSystemMetrics(SM_CXSCREEN) - pixWidth ) /2;
		}
		if (cmd_iWindowTop > 0) {
			pixPosY = cmd_iWindowTop>(::GetSystemMetrics(SM_CYSCREEN))?(::GetSystemMetrics(SM_CYSCREEN)):cmd_iWindowTop;
			cmd_iWindowTop = -1;
		} else {
			pixPosY   = (::GetSystemMetrics(SM_CYSCREEN) - pixHeight ) /2;
		}
	}

	SetWindowPos( _hwndMain, NULL, pixPosX,pixPosY, pixWidth,pixHeight, SWP_NOZORDER);
	ShowWindow(   _hwndMain, SW_SHOW);
}


// open the main application window for windowed mode
void OpenMainWindowNormal( PIX pixSizeI, PIX pixSizeJ,bool p_Center)
{
	
	//	±è¿µÈ¯ : À©µµ ´Ù½Ã»ý¼º ¾ÈÇÔ
	if(_hwndMain == NULL)
	{
		ASSERT(_hwndMain==NULL);

		if (sam_bFullScreenActive)
		{
			// create a window, invisible initially
			_hwndMain = CreateWindowEx(
			  WS_EX_TOPMOST | WS_EX_APPWINDOW,
			  APPLICATION_NAME,
			  "",   // title
			  WS_POPUP,//WS_OVERLAPPED|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,
			  10,10,
			  100,100,  // window size
			  NULL,
			  NULL,
			  _hInstanceMain,
			  NULL);
		}
		else
		{
			// create a window, invisible initially
			_hwndMain = CreateWindowEx(
			  WS_EX_APPWINDOW,
			  APPLICATION_NAME,
			  "",   // title
			  // ±è¿µÈ¯
			  WS_OVERLAPPED|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,
			  //WS_OVERLAPPEDWINDOW,//WS_OVERLAPPED|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,
			  10,10,
			  100,100,  // window size
			  g_parenthWnd,
			  NULL,
			  _hInstanceMain,
			  NULL);
		}

		// didn't make it?
		if( _hwndMain==NULL) FatalError(TRANS("Cannot open main window!"));
	}
	else
	{
		//	±è¿µÈ¯ : ±âÁ¸ À©µµÀÇ »óÅÂ°ª º¯°æ
		if (sam_bFullScreenActive)
		{
			//	Ç®¸ðµå
			SetWindowLong(_hwndMain,GWL_EXSTYLE,WS_EX_TOPMOST | WS_EX_APPWINDOW);
			SetWindowLong(_hwndMain,GWL_STYLE,WS_POPUP);
		}
		else
		{
			//	Ã¢¸ðµå
			SetWindowLong(_hwndMain,GWL_EXSTYLE,WS_EX_APPWINDOW);
			SetWindowLong(_hwndMain,GWL_STYLE, (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ));
			//SetWindowLong(_hwndMain,GWL_STYLE,WS_OVERLAPPEDWINDOW);
		}
	}

	_hDlgWeb = CreateDialog(_hInstanceMain, MAKEINTRESOURCE(IDD_WEBPAGE), _hwndMain, (DLGPROC)WebDialogProcPtr);

	if( _hDlgWeb==NULL) FatalError(TRANS("Cannot open Web Dialog!"));

	g_web.SetWebDlgID(IDD_WEBPAGE);
	g_web.SetWebDlgCallBack(WebDialogProcPtr);

	SE_UpdateWindowHandle( _hwndMain, _hDlgWeb);

	_pixLastSizeI = pixSizeI;
	_pixLastSizeJ = pixSizeJ;
	ResetMainWindowNormal(p_Center);
}


// open the main application window for fullscreen mode
void OpenMainWindowFullScreen( PIX pixSizeI, PIX pixSizeJ)
{
	//	±è¿µÈ¯ : À©µµ ´Ù½Ã»ý¼º ¾ÈÇÔ
	if(_hwndMain == NULL)
	{
		ASSERT( _hwndMain==NULL);
		// create a window, invisible initially
		_hwndMain = CreateWindowEx(
			WS_EX_TOPMOST | WS_EX_APPWINDOW,
			APPLICATION_NAME,
			"",   // title
			WS_POPUP,
			0,0,
			pixSizeI, pixSizeJ,  // window size
			g_parenthWnd,
			NULL,
			_hInstanceMain,
			NULL);
		// didn't make it?
		if( _hwndMain==NULL) FatalError(TRANS("Cannot open main window!"));
	}
	else
	{
		//	±è¿µÈ¯ : ±âÁ¸ À©µµÀÇ »óÅÂ°ª º¯°æ : Ç® È­¸é.
		SetWindowLong(_hwndMain,GWL_EXSTYLE,WS_EX_TOPMOST | WS_EX_APPWINDOW);
		SetWindowLong(_hwndMain,GWL_STYLE,WS_POPUP);
	}

	_hDlgWeb = CreateDialog(_hInstanceMain, MAKEINTRESOURCE(IDD_WEBPAGE), _hwndMain, (DLGPROC)WebDialogProcPtr);

	if( _hDlgWeb==NULL) FatalError(TRANS("Cannot open Web Dialog!"));

	g_web.SetWebDlgID(IDD_WEBPAGE);
	g_web.SetWebDlgCallBack(WebDialogProcPtr);

	SE_UpdateWindowHandle( _hwndMain, _hDlgWeb);
	
	ShowWindow(    _hwndMain, SW_SHOWNORMAL);
}


// open the main application window invisible
void OpenMainWindowInvisible(void)
{
	//	±è¿µÈ¯ : ÃÊ±â »ý¼º ºÎºÐ.
	if(_hwndMain == NULL)
	{
		ASSERT(_hwndMain==NULL);
		// create a window, invisible initially
		_hwndMain = CreateWindowEx(
		  WS_EX_APPWINDOW,
		  APPLICATION_NAME,
		  // uniqueÇÑ Å¸ÀÌÆ² ³×ÀÓÀÌ ÀÖ¾î¾ßÁö¸¸ Àâ´Â´Ù. [3/28/2012 rumist]
		  "CLICK GAMING",   // title
		  (WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME | WS_SIZEBOX),
		  //WS_OVERLAPPEDWINDOW,//	WS_POPUP,
		  0,0,
		  10, 10,  // window size
		  NULL,
		  NULL,
		  _hInstanceMain,
		  NULL);
		// didn't make it?
		if( _hwndMain==NULL) FatalError(TRANS("Cannot open main window!"));
	}

	_hDlgWeb = CreateDialog(_hInstanceMain, MAKEINTRESOURCE(IDD_WEBPAGE), _hwndMain, (DLGPROC)WebDialogProcPtr);

	if( _hDlgWeb==NULL) FatalError(TRANS("Cannot open Web Dialog!"));

	g_web.SetWebDlgID(IDD_WEBPAGE);
	g_web.SetWebDlgCallBack(WebDialogProcPtr);

	SE_UpdateWindowHandle( _hwndMain, _hDlgWeb);

	//	±è¿µÈ¯ : Å¸ÀÌÆ²ÀÌ¸§ º¯°æ ÇÏÁö¸»ÀÚ ¹ø¿ªÀÌ½´¸¸ ¹ß»ý. 
	/*
#if defined
	sprintf( achWindowTitle, TRANS("Çàãðóçêà?") );
#else
	sprintf( achWindowTitle, TRANS("Loading...") );
#endif
	SetWindowText( _hwndMain, achWindowTitle);
	*/
}
