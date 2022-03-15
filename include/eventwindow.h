#pragma once
#ifndef EVENTWINDOW_H
#define EVENTWINDOW_H

#include "common.h"
#include <thread>
#include "log.h"
#include "..\include\printer.h"
#include "..\include\idc.h"
#include "..\include\siu.h"

class CEventWindow :/*public CWinThread,*/public WNDCLASSA {
private:
	HWND m_hwnd;
	HANDLE m_hStopEvent{ NULL };

public:
	CEventWindow();
	CEventWindow(const CEventWindow&);
	CEventWindow(CEventWindow&&) = delete;
	CEventWindow& operator = (const CEventWindow&) = delete;
	CEventWindow& operator = (CEventWindow&&) = delete;
	~CEventWindow();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void EventHandle();
	
	void SetHwnd(HWND hwnd1);
	HWND GetHwnd();

	static UINT __cdecl CreateWindowThreadProc(LPVOID pParam);
	int StartThread();

	CWinThread* pThread = new CWinThread;
	CPrinter* pCPrinter = new CPrinter;
	CIdc* pCIdc = new CIdc;
	CSiu* pCSiu = new CSiu;

	static void ExecuteEventHandle(LPARAM lParam);
	static void ServiceEventHandle(LPARAM lParam);
	static void UserEventHandle(LPARAM lParam);
	static void SystemEventHandle(LPARAM lParam);
	static void ModuleSpecifier(LPARAM lParam);
	static void ShowDevStatus(LPWFSRESULT lpWFSResult);

	/*typedef */enum ModuleNo:int{Printer = 1, IDC, CDM, TTU = 7, SIU , CAM = 10, CIM = 13};
};

#endif
