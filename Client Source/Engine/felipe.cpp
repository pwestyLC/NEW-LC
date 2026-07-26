#include "StdH.h"
#include "Util.h"
#include "resource.h"
#include "Splash.h"
//#include "Engine.h"

void MsgBox(char* message, ...) // OK
{
	char buff[256];

	memset(buff, 0, sizeof(buff));

	va_list arg;
	va_start(arg, message);
	vsprintf_s(buff, message, arg);
	va_end(arg);

	MessageBox(0, buff, "Error", MB_OK | MB_ICONERROR);
}


DWORD WINAPI SplashThread(CSplash* lpSplash) // OK
{
	lpSplash->ShowSplash();

	//	SetEvent(lpSplash->m_SplashEvent);

	MSG msg;

	while (GetMessage(&msg, 0, 0, 0) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return 0;
}


void SplashScreen(CSplash* ClassInst, int SplashType, bool TextSwitch, char DisplayText[255], int CloseTime)
{
	//	gLog.Output(LOG_DEBUG, GetEncryptedString(42), SplashType, TextSwitch, DisplayText);

	int ResId;

	COLORREF TextColor;

	//	//SplashAlert.CloseSplash();
		//SplashError.CloseSplash();

	switch (SplashType)
	{
	case 0:
		ResId = IDB_BITMAP1;
		TextColor = RGB(118, 164, 156);
		break;
	case 1:
		ResId = IDB_BITMAP2;
		TextColor = RGB(150, 104, 17);
		break;
	case 2:
		ResId = IDB_BITMAP2;
		TextColor = RGB(185, 43, 43);
		break;
	}

	if (TextSwitch)
		//		ClassInst->Start(ResId, hins, RGB(128, 128, 128), 1, DisplayText, TextColor);
		//	else
				//ClassInst->Start(ResId, hins, RGB(128, 128, 128));

			//ClassInst->m_SplashEvent = CreateEvent(0, 0, 0, 0);

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SplashThread, ClassInst, 0, 0);

	//WaitForSingleObject(ClassInst->m_SplashEvent, INFINITE);

	//CloseHandle(ClassInst->m_SplashEvent);

	if (CloseTime > 0)
	{
		Sleep(CloseTime);

		if (SplashType != 0)
		{
			ClassInst->CloseSplash();
			//Sleep(1000);
			//SafeExitProcess();
		}
	}
}