#include "stdh.h"

#include <Engine/Graphics/ViewPort.h>

#include <Engine/Graphics/GfxLibrary.h>
#include <Engine/Base/Statistics_internal.h>
#include <Engine/Interface/UIIME.h>
#include <Engine/Graphics/D3D_ResourceLog.h>
extern INDEX ogl_bExclusive;
//	±è¿µÈ¯ Àü¿ª ¼³Á¤ °ª °¡Á®¿À±â
extern BOOL _bClientApp;

// helper for D3D surface
extern CViewPort* _pVp = NULL;

// helper for D3D surface
static HRESULT CreateSwapChain_D3D( CViewPort *pvp, PIX pixSizeI, PIX pixSizeJ)
{
	HRESULT hr;

	// release old if still allocated
	if( pvp->vp9_pSwapChain!=NULL) {
		ASSERT( pvp->vp9_pSurfDepth!=NULL);
		D3DRELEASE( pvp->vp9_pSwapChain, TRUE);
		D3DRELEASE( pvp->vp9_pSurfDepth, TRUE);
	} else ASSERT(pvp->vp9_pSurfDepth==NULL);

	// prepare new parameters
	D3DPRESENT_PARAMETERS d3dPresentParams; // ###
	memset( &d3dPresentParams, 0, sizeof(d3dPresentParams));
	d3dPresentParams.Windowed = TRUE;
	d3dPresentParams.BackBufferWidth  = pixSizeI;
	d3dPresentParams.BackBufferHeight = pixSizeJ;
	d3dPresentParams.BackBufferFormat = _pGfx->gl_d3dColorFormat;
	d3dPresentParams.BackBufferCount  = 1;
	d3dPresentParams.MultiSampleType  = D3DMULTISAMPLE_NONE; // !!!! TODO
	d3dPresentParams.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	d3dPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD; 
	d3dPresentParams.hDeviceWindow = pvp->vp_hWnd;

	// Disable V-Sync
	d3dPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	ASSERT(pvp->vp9_pSwapChain == NULL && pvp->vp9_pSurfDepth == NULL);
	hr = _pGfx->gl_pd3d9Device->CreateAdditionalSwapChain(&d3dPresentParams, &pvp->vp9_pSwapChain);
	D3D_CHECKERROR(hr);
	hr = _pGfx->gl_pd3d9Device->CreateDepthStencilSurface(pixSizeI, pixSizeJ, _pGfx->gl_d3dDepthFormat,
		D3DMULTISAMPLE_NONE, 0, FALSE, &pvp->vp9_pSurfDepth, NULL); // ### DX9

	// done
	ASSERT( pvp->vp9_pSwapChain!=NULL && pvp->vp9_pSurfDepth!=NULL);
	return hr;
}


static void SetAsRenderTarget_D3D(CViewPort *pvp)
{
	HRESULT hr;
	LPDIRECT3DSURFACE9 pColorSurface; // ### DX9

	if (pvp->vp9_pSwapChain != NULL)
	{
		hr = pvp->vp9_pSwapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pColorSurface);
		D3D_CHECKERROR(hr);
		// ### DX9 begin
		//hr = _pGfx->gl_pd3dDevice->SetRenderTarget( pColorSurface, pvp->vp_pSurfDepth);
		//D3D_CHECKERROR(hr);
		hr = _pGfx->gl_pd3d9Device->SetDepthStencilSurface(pvp->vp9_pSurfDepth);
		D3D_CHECKERROR(hr);
		hr = _pGfx->gl_pd3d9Device->SetRenderTarget(0, pColorSurface);
		D3D_CHECKERROR(hr);
		// ### DX9 end
		D3DRELEASE(pColorSurface, TRUE);
	}
}


// helper for OGL

CTempDC::CTempDC(HWND hWnd)
{
	ASSERT(hWnd!=NULL);
	hwnd = hWnd;
	hdc = GetDC(hwnd);
	ASSERT(hdc!=NULL);
}

CTempDC::~CTempDC(void)
{
	ReleaseDC(hwnd, hdc);
}


/*
*   ViewPort functions
*/

CViewPort::CViewPort( PIX pixWidth, PIX pixHeight, HWND hWnd) :
vp_Raster( pixWidth, pixHeight, 0)
{
	vp_hWnd = NULL;
	vp_hWndParent = hWnd;
	vp9_pSwapChain = NULL;
	vp9_pSurfDepth = NULL;
	vp_ctDisplayChanges = 0;
	OpenCanvas();
	vp_Raster.ra_pvpViewPort = this;
}


CViewPort::~CViewPort(void)
{
	D3DRES_LOG_MARKER("CViewPort::~CViewPort BEGIN");
	extern void DrawPort_NoCurrentDrawPort(void);
	DrawPort_NoCurrentDrawPort();
	CloseCanvas();
	// reset current viewport if needed
	if( _pGfx->gl_pvpActive==this) _pGfx->gl_pvpActive = NULL;
	D3DRES_LOG_MARKER("CViewPort::~CViewPort END");
}




#define CViewPortCLASS "ViewPort Window"
static BOOL _bClassRegistered = FALSE;

LRESULT CALLBACK CViewPortCLASS_WindowProc(
	HWND hWnd,      // handle to window
	UINT Msg,       // message identifier
	WPARAM wParam,  // first message parameter
	LPARAM lParam   // second message parameter
										   )
{
	// forget erase bacground messages
	if (Msg==WM_ERASEBKGND) return TRUE;

	// if any mouse message
	if ((Msg>=WM_MOUSEFIRST&&Msg<=WM_MOUSELAST)) {
		// send it to parent
		HWND hWndParent = GetParent(hWnd);
		ASSERT(hWndParent!=NULL);
#if (defined PLATFORM_64BIT)
		return CallWindowProc( (WNDPROC)GetWindowLongPtr(hWndParent, GWLP_WNDPROC),
													 hWndParent, Msg, wParam, lParam);
#else
		return CallWindowProc((WNDPROC)GetWindowLong(hWndParent, GWL_WNDPROC),
			hWndParent, Msg, wParam, lParam);
#endif
	}
	// ÀÌ±âÈ¯ ¼öÁ¤ ½ÃÀÛ (11. 15) : FullScreen¿¡¼­ IMEÃ¢ ¼û±â±â
	return _bIMEProc?0:DefWindowProc(hWnd, Msg, wParam, lParam);
	// ÀÌ±âÈ¯ ¼öÁ¤ ³¡ (11. 15)
}



// open overlaid window for rendering context
void CViewPort::OpenCanvas(void)
{
	// ±è¿µÈ¯ : vp_hWndParent À» vp_hWnd·Î »ç¿ë	
	if(_bClientApp)
	{
		vp_hWnd = vp_hWndParent;	// ¸ÞÀÎ ÇÚµé »ç¿ë.
		// À©µµ¿ì ¿µ¿ª ¹× ÇÃ ½ºÅ©¸° Á¤º¸ ¾ò´Â´Ù.
		// determine window and desktopsize
		RECT rectWindow;
		GetClientRect( vp_hWndParent, &rectWindow);
		const PIX pixWinSizeI = rectWindow.right  - rectWindow.left;
		const PIX pixWinSizeJ = rectWindow.bottom - rectWindow.top;
		CDisplayMode dm;
		_pGfx->GetCurrentDisplayMode(dm);
		ASSERT( (dm.dm_pixSizeI==0 && dm.dm_pixSizeJ==0) || (dm.dm_pixSizeI!=0 && dm.dm_pixSizeJ!=0));
		const BOOL bFullScreen = (dm.dm_pixSizeI==pixWinSizeI && dm.dm_pixSizeJ==pixWinSizeJ);

		// prepare new swap chain for D3D
		if( _pGfx->gl_eCurrentAPI==GAT_D3D && !bFullScreen)
		{
			// WSS_VIDEOMEMORYFAIL 070615 ------------------------------->>
			HRESULT hr;
			if( (hr=CreateSwapChain_D3D( this, pixWinSizeI, pixWinSizeJ)))
			{
			}
			// ----------------------------------------------------------->>
		}

		// resize raster
		Resize();
		ShowWindow( vp_hWnd, SW_SHOW);

		// set as rendering target
		if( _pGfx->gl_eCurrentAPI==GAT_D3D && vp9_pSwapChain!=NULL) 
			SetAsRenderTarget_D3D(this);
	}
	else
	{
		// do nothing if not feasable
		if( vp_hWnd!=NULL || vp_hWndParent==NULL) return;

		// register class
		if( !_bClassRegistered) {
			WNDCLASS wc;
			wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
			wc.lpfnWndProc = CViewPortCLASS_WindowProc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = NULL;
			wc.hIcon = NULL;
			wc.hCursor = LoadCursor( NULL, IDC_ARROW);
			wc.hbrBackground = NULL;
			wc.lpszMenuName = NULL;
			wc.lpszClassName = CViewPortCLASS;
			RegisterClass(&wc);
			_bClassRegistered = TRUE;
		}
		
		// determine window and desktopsize
		RECT rectWindow;
		GetClientRect( vp_hWndParent, &rectWindow);
		const PIX pixWinSizeI = rectWindow.right  - rectWindow.left;
		const PIX pixWinSizeJ = rectWindow.bottom - rectWindow.top;
		CDisplayMode dm;
		_pGfx->GetCurrentDisplayMode(dm);
		ASSERT( (dm.dm_pixSizeI==0 && dm.dm_pixSizeJ==0) || (dm.dm_pixSizeI!=0 && dm.dm_pixSizeJ!=0));
		const BOOL bFullScreen = (dm.dm_pixSizeI==pixWinSizeI && dm.dm_pixSizeJ==pixWinSizeJ);

		// set fullscreen attribs if window size is equal to screen size
		DWORD dwExStyle = NONE;
		DWORD dwStyle   = WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
		if( bFullScreen && ogl_bExclusive) {
			dwExStyle = WS_EX_TOPMOST;
			dwStyle   = WS_POPUP;     
		} 

		// set child window
		vp_hWnd = ::CreateWindowEx(
		  dwExStyle,
		  CViewPortCLASS,
		  "",   // title
			dwStyle,
		  0,0,
		  0,0,  // window size
		  vp_hWndParent,
		  NULL,
#if (defined PLATFORM_64BIT)
		  (HINSTANCE)GetWindowLongPtr(vp_hWndParent, GWLP_HINSTANCE),
#else
		  (HINSTANCE)GetWindowLong(vp_hWndParent, GWL_HINSTANCE),
#endif
		  NULL);
		ASSERT( vp_hWnd!=NULL);
		
		// prepare new swap chain for D3D
		if( _pGfx->gl_eCurrentAPI==GAT_D3D && !bFullScreen)
		{
			// WSS_VIDEOMEMORYFAIL 070615 ------------------------------->>
			HRESULT hr;
			if( (hr=CreateSwapChain_D3D( this, pixWinSizeI, pixWinSizeJ)))
			{
				/*****
				CTString tStr;
				tStr.PrintF("CreateSwapChain_D3D Failed!! - OpenCanvas %x",hr);
				MessageBox(vp_hWndParent,tStr.str_String,"ERROR",MB_OK);
				::DestroyWindow(vp_hWnd);
				return;
				*****/
			}
			// ----------------------------------------------------------->>
		}

		// resize raster
		Resize();
		ShowWindow( vp_hWnd, SW_SHOW);

		// set as rendering target
		if( _pGfx->gl_eCurrentAPI==GAT_D3D && vp9_pSwapChain!=NULL) SetAsRenderTarget_D3D(this);
	}
}


// close overlaid window
void CViewPort::CloseCanvas(void)
{
	D3DRES_LOG("CloseCanvas: vp9_pSwapChain=0x%p vp9_pSurfDepth=0x%p", (void*)vp9_pSwapChain, (void*)vp9_pSurfDepth);
	// release D3D swap chain if allocated
	if( _pGfx->gl_eCurrentAPI==GAT_D3D) 
	{
       LPDIRECT3DSURFACE9 pCurrentBackSurface = NULL;
		LPDIRECT3DSURFACE9 pCurrentDepthSurface = NULL;
		LPDIRECT3DSURFACE9 pViewportBackSurface = NULL;
		_pGfx->gl_pd3d9Device->GetRenderTarget(0, &pCurrentBackSurface);
		_pGfx->gl_pd3d9Device->GetDepthStencilSurface(&pCurrentDepthSurface);

		if( vp9_pSwapChain != NULL ) {
			vp9_pSwapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &pViewportBackSurface);
		}

		if( pCurrentDepthSurface == vp9_pSurfDepth ) {
			_pGfx->gl_pd3d9Device->SetDepthStencilSurface(NULL);
		}

		if( pCurrentBackSurface == pViewportBackSurface ) {
			IDirect3DSurface9* pMainBackSurface = NULL;
			if( SUCCEEDED(_pGfx->gl_pd3d9Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pMainBackSurface)) ) {
				_pGfx->gl_pd3d9Device->SetRenderTarget(0, pMainBackSurface);
				D3DRELEASE(pMainBackSurface, TRUE);
			}
		}

		D3DRES_LOG("  CloseCanvas: D3DRELEASE pViewportBackSurface=0x%p", (void*)pViewportBackSurface);
		D3DRELEASE( pViewportBackSurface, TRUE);
		D3DRES_LOG("  CloseCanvas: D3DRELEASE pCurrentBackSurface=0x%p", (void*)pCurrentBackSurface);
		D3DRELEASE( pCurrentBackSurface, TRUE);
		D3DRES_LOG("  CloseCanvas: D3DRELEASE pCurrentDepthSurface=0x%p", (void*)pCurrentDepthSurface);
		D3DRELEASE( pCurrentDepthSurface, TRUE);
		if( vp9_pSwapChain!=NULL) {
			D3DRES_LOG("  CloseCanvas: D3DRELEASE vp9_pSwapChain=0x%p", (void*)vp9_pSwapChain);
			D3DRELEASE( vp9_pSwapChain, TRUE);
		}
		if( vp9_pSurfDepth!=NULL) {
			D3DRES_LOG("  CloseCanvas: D3DRELEASE vp9_pSurfDepth=0x%p", (void*)vp9_pSurfDepth);
			D3DRELEASE( vp9_pSurfDepth, TRUE);
		}
	} else {
		vp9_pSwapChain = NULL;
		vp9_pSurfDepth = NULL;
	}
	// destroy window
	//	±è¿µÈ¯ : Å¬¶óÀÌ¾ðÆ®¿ëÀÌ ¾Æ´Ñ °æ¿ì¸¸.(Åø¿¡¼­ »ç¿ëÇÏ´Â °æ¿ì)
	if(_bClientApp == FALSE)
	{
		if( vp_hWnd!=NULL && IsWindow(vp_hWnd)) 
		{ 
			BOOL bRes = DestroyWindow(vp_hWnd);
			ASSERT(bRes);
		}
	}
	// mark
	vp_hWnd = NULL;
}


// Change size of this viewport, it's raster and all it's drawports
void CViewPort::Resize(void)
{
	PIX pixNewWidth, pixNewHeight;
	RECT rectWindow;

	//°­µ¿¹Î ¼öÁ¤ ½ÃÀÛ ½Ã½ºÅÛ ¸¶¿ì½º ÀÛ¾÷	09.09
	extern BOOL _bFirst;
	if(!_bFirst)				_bFirst = TRUE;

	extern INDEX d3d_bDeviceChanged;
	if(!d3d_bDeviceChanged)		d3d_bDeviceChanged = TRUE;
	//°­µ¿¹Î ¼öÁ¤ ³¡ ½Ã½ºÅÛ ¸¶¿ì½º ÀÛ¾÷		09.09
	
	// get the size of the window
	GetClientRect( vp_hWndParent, &rectWindow);
	pixNewWidth  = rectWindow.right  - rectWindow.left;
	pixNewHeight = rectWindow.bottom - rectWindow.top;
	//¾ÈÅÂÈÆ ¼öÁ¤ ½ÃÀÛ	//(Easy Use World Editor)(0.1)
	if(pixNewWidth < 1) pixNewWidth = 1;
	if(pixNewHeight < 1) pixNewHeight = 1;
	//¾ÈÅÂÈÆ ¼öÁ¤ ³¡	//(Easy Use World Editor)(0.1)

	// resize child window
	//	±è¿µÈ¯ : Å©±âÁ¶Àý ¾ÈÇÔ.
	if(_bClientApp == FALSE)
	{
		ASSERT( vp_hWnd!=NULL);
		SetWindowPos( vp_hWnd, NULL, 0,0, pixNewWidth, pixNewHeight, SWP_NOZORDER|SWP_NOMOVE);
	}

	// resize the raster
	vp_Raster.Resize( pixNewWidth, pixNewHeight);

	// "resize" D3D surface (if any)
	if( _pGfx->gl_eCurrentAPI==GAT_D3D && vp9_pSwapChain!=NULL)// && vp_pSurfDepth!=NULL) 
	{
		// release old surface
		D3DRELEASE( vp9_pSwapChain, TRUE);
		D3DRELEASE( vp9_pSurfDepth, TRUE);
		// create a new one and set it as current
		// WSS_VIDEOMEMORYFAIL 070615 ------------------------------->>
		HRESULT hr;
		if( (hr=CreateSwapChain_D3D( this, pixNewWidth, pixNewHeight)) )
		{
			/*****
			CTString tStr;
			tStr.PrintF("CreateSwapChain_D3D Failed!! - Resize %x",hr);
			MessageBox(vp_hWndParent,tStr.str_String,"ERROR",MB_OK);			
			return;
			*****/
		}				
		// ----------------------------------------------------------->>
		SetAsRenderTarget_D3D(this);
	}
}


void CViewPort::SwapBuffers( const BOOL bWaitForRetrace/*=FALSE*/)
{
	// skip if child window not present
	if( vp_hWnd==NULL) return;
  if( _pGfx==NULL) return;

#ifdef UI_TOOL
	if (_pGfx->gl_eCurrentAPI==GAT_D3D && _pGfx->gl_pd3d9Device==NULL) {
		return;
	}
#endif
	// ask the gfx lib to swap buffers
 #ifdef UI_TOOL
	__try {
		_pGfx->SwapBuffers( this, bWaitForRetrace);
	}
	__except(EXCEPTION_EXECUTE_HANDLER) {
		return;
	}
	#else
	_pGfx->SwapBuffers( this, bWaitForRetrace);
   #endif
}

