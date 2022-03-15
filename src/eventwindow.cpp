//FILE: ewentwindow.cpp
//handling events that modules send.

#include "pch.h"
#include "..\include\eventwindow.h"

//Construction
CEventWindow::CEventWindow() 
{
}

CEventWindow::~CEventWindow() 
{
	delete pThread;
	delete pCPrinter;
	delete pCSiu;
	delete pCIdc;
}

CEventWindow::CEventWindow(const CEventWindow&) 
{
}
//////////////////////////////////////////////////////////////////////////
//eventhandle

void CEventWindow::EventHandle() 
{
	Log("Entered to EventHandle");
	
	const wchar_t CLASS_NAME[] = L"CEventWindow";
	//const wchar_t CLASS_NAME = className;

	WNDCLASSEX wcex;

	wcex.lpfnWndProc = &CEventWindow::WindowProc;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = CLASS_NAME;
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	//wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	//wc.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	//wc.lpszClassName = strWndName.c_str();
	wcex.hIconSm = NULL;
	

	if(!RegisterClassExW(&wcex))
		Log("RegisterClassEx err: ",GetLastError());

	// Create the window.
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		NULL,			                // Window text 
		NULL,                           // Window style
		NULL, NULL, NULL, NULL,         // Size and position
		HWND_MESSAGE,                   // Parent window    
		NULL,                           // Menu
		NULL,                           // Instance handle
		NULL                            // Additional application data
	);
	Log("EventWindow hwnd: ", hwnd);
	if (!hwnd)
	{
		Log("CreateWindow last error: ", GetLastError());
		Log("CreateWindow ExW created and hwnd is: ", hwnd);
	}
	else {
		ShowWindow(hwnd, SW_HIDE);
	}

	MSG msg;
	bool bRet;

	while ((bRet = GetMessage(&msg, hwnd, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
			Log("GetMessage faild");
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg); //<< This line send msg to WindowProc()
		}
	}
	Log("GetMessage loop finished");

}

LRESULT CALLBACK CEventWindow::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WFS_EXECUTE_EVENT:
			ExecuteEventHandle(lParam);
			break;
		case WFS_SERVICE_EVENT:
			ServiceEventHandle(lParam);
			break;
		case WFS_USER_EVENT:
			UserEventHandle(lParam);
			break;
		case WFS_SYSTEM_EVENT:
			SystemEventHandle(lParam);
			break;
		default:    
			Log("WndProc msg: ", msg);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void CEventWindow::SetHwnd(HWND hwnd1) 
{
	m_hwnd = hwnd1;
}

HWND CEventWindow::GetHwnd() 
{
	return m_hwnd;
}

int CEventWindow::StartThread() 
{
	Log("start of thread");
	const wchar_t* className = L"CEventWindow";

	thread EventWindowThread(&CEventWindow::EventHandle, CEventWindow());
	EventWindowThread.detach();
	return 0;
}


void CEventWindow::ExecuteEventHandle(LPARAM lParam) 
{
	Log("WFS_EXECUTE_EVENT");
	ModuleSpecifier(lParam);
}

void CEventWindow::ServiceEventHandle(LPARAM lParam) 
{
	Log("WFS_EXECUTE_EVENT");
	ModuleSpecifier(lParam);
}

void CEventWindow::UserEventHandle(LPARAM lParam) 
{
	Log("WFS_USER_EVENT");
	ModuleSpecifier(lParam);

}

void CEventWindow::ModuleSpecifier(LPARAM lParam) 
{
	ModuleNo n = Printer;
	int nModuleNo = 0;
	LPWFSRESULT lpWFSResult = (LPWFSRESULT)lParam;
	nModuleNo = (lpWFSResult->u.dwEventID / 100);
	switch (nModuleNo) 
	{
	case(Printer):
		Log("Printer: ");
		Log(lpWFSResult->u.dwEventID);
		break;
	case(IDC):
		Log("IDC: ");
		Log(lpWFSResult->u.dwEventID);
		break;
	case(CDM):
		Log("CDM: ");
		Log(lpWFSResult->u.dwEventID);
		break;
	case(TTU):
		Log("TTU: ");
		Log(lpWFSResult->u.dwEventID);
		break;
	case(SIU):
		Log("SIU: ");
		Log(lpWFSResult->u.dwEventID);
		break;
	case(CAM):
		
		break;
	case(CIM):

		break;
	}
}

void CEventWindow::SystemEventHandle(LPARAM lParam) 
{
	Log("WFS_SYSTEM_EVENT");
	ModuleSpecifier(lParam);
	LPWFSRESULT lpWFSResult = (LPWFSRESULT)lParam;
	
	switch (lpWFSResult->u.dwEventID) 
	{
		case(WFS_SYSE_UNDELIVERABLE_MSG):
			Log("	WFS_SYSE_UNDELIVERABLE_MSG");
			break;
		case(WFS_SYSE_HARDWARE_ERROR):
			Log("	WFS_SYSE_HARDWARE_ERROR");
			break;
		case(WFS_SYSE_VERSION_ERROR):
			Log("	WFS_SYSE_VERSION_ERROR");
			break;
		case(WFS_SYSE_DEVICE_STATUS):
			ShowDevStatus(lpWFSResult);
			break;
		case(WFS_SYSE_APP_DISCONNECT):
			Log("	WFS_SYSE_APP_DISCONNECT");
			break;
		case(WFS_SYSE_SOFTWARE_ERROR):
			Log("	WFS_SYSE_SOFTWARE_ERROR");
			break;
		case(WFS_SYSE_USER_ERROR):
			Log("	WFS_SYSE_USER_ERROR");
			break;
		case(WFS_SYSE_LOCK_REQUESTED):
			Log("	WFS_SYSE_LOCK_REQUESTED");
			break;
		case(WFS_SYSE_FRAUD_ATTEMPT):
			Log("	WFS_SYSE_FRAUD_ATTEMPT");
			break;
	}
}

void CEventWindow::ShowDevStatus(LPWFSRESULT lpWFSResult) 
{
	LPWFSDEVSTATUS lpWFSDEVStatus = (LPWFSDEVSTATUS)(lpWFSResult->lpBuffer);
	Log("lpszPhysicalName", lpWFSDEVStatus->lpszPhysicalName);
	
	switch (lpWFSDEVStatus->dwState) 
	{
		case(WFS_STAT_DEVONLINE):
			Log("	WFS_STAT_DEVONLINE");
			break;
		case(WFS_STAT_DEVOFFLINE):
			Log("	WFS_STAT_DEVOFFLINE");
			break;
		case(WFS_STAT_DEVPOWEROFF):
			Log("	WFS_STAT_DEVPOWEROFF");
			break;
		case(WFS_STAT_DEVNODEVICE):
			Log("	WFS_STAT_DEVNODEVICE");
			break;
		case(WFS_STAT_DEVHWERROR):
			Log("	WFS_STAT_DEVHWERROR");
			break;
		case(WFS_STAT_DEVUSERERROR):
			Log("	WFS_STAT_DEVUSERERROR");
			break;
		case(WFS_STAT_DEVBUSY):
			Log("	WFS_STAT_DEVBUSY");
			break;
		case(WFS_STAT_DEVFRAUDATTEMPT):
			Log("	WFS_STAT_DEVFRAUDATTEMPT");
			break;
		case(WFS_STAT_DEVPOTENTIALFRAUD):
			Log("	WFS_STAT_DEVPOTENTIALFRAUD");
			break;
	}
}
