//FILE:siu.cpp
//CDM module functions for openning, register, and ...

#include "pch.h"
#include "..\include\siu.h"

CSiu::CSiu() 
{

}

CSiu::~CSiu() 
{
	delete lpWFSVersion;
	delete lpSrvcVersion;
	delete lpSPIVersion;
}

void CSiu::GetVersion() 
{
	lpWFSVersion->wVersion = 0x0003;
	lpWFSVersion->wLowVersion = 0x0101;
	lpWFSVersion->wHighVersion = 0x9903;
}

void CSiu::GetSrvcVersion() 
{
	lpSrvcVersion->wVersion = 0x0003;
	lpSrvcVersion->wLowVersion = 0x0003;
	lpSrvcVersion->wHighVersion = 0x0003;
}

void CSiu::GetSPIVersion() 
{
	lpSPIVersion->wVersion = 0x0003;
	lpSPIVersion->wLowVersion = 0x0003;
	lpSPIVersion->wHighVersion = 0x0003;
}


void CSiu::SethService(HSERVICE hservice) 
{
	m_hService = hservice;
}

HSERVICE CSiu::GethService() 
{
	return m_hService;
}

bool CSiu::OpenModule() 
{
	HRESULT hResult;
	WFSRESULT* lpResult = new WFSRESULT;

	hResult = WFSStartUp(dwSiuVersionRequired, lpWFSVersion);
	if (!hResult) 
	{
		Log("Startup SIU Successful");
	}
	else {
		Log("Startup SIU: ", hResult);
	}

	hResult = WFSOpen("SIU", WFS_DEFAULT_HAPP, "XFSTest3.0", 0, WFS_INDEFINITE_WAIT, lpWFSVersion->wVersion, lpSrvcVersion, lpSPIVersion, &(lpResult->hService));
	SethService(lpResult->hService);

	if (hResult == 0) 
	{
		WFSFreeResult(lpResult);
		Log("Open SIU Successful");
		AfxMessageBox(_T("Open SIU Successful"));
		return true;
	}
	else {
		WFSFreeResult(lpResult);
		Log("Open SIU: ", hResult);
		AfxMessageBox(hResult, MB_YESNO);
		return false;
	}

}

void CSiu::Register() 
{
	HRESULT hResult;
	LPWSTR lpClassName = L"CEventWindow";

	if (m_hwnd = FindWindowExW(HWND_MESSAGE, NULL, lpClassName, NULL)) 
	{
		Log("FindWindowHWND for SIU: ", m_hwnd);
	}
	else {
		Log("HWND for PTR is NULL");
	}

	hResult = WFSRegister(GethService(), SYSTEM_EVENTS | USER_EVENTS | EXECUTE_EVENTS | SERVICE_EVENTS, m_hwnd);
	if (hResult == 0) 
	{
		AfxMessageBox(_T("Register SIU Successful"));
		Log("Register SIU Successful");
	}
	else {
		AfxMessageBox(hResult, MB_YESNO);
		Log("Register SIU: ", hResult);
	}
}

void CSiu::GetInfo(DWORD dwCategory) 
{
	HRESULT hresult;
	WFSRESULT* lpResult = new WFSRESULT;

	hresult = WFSGetInfo(GethService(), dwCategory, NULL, WFS_INDEFINITE_WAIT, &lpResult);
	if (hresult == 0) 
	{
		AfxMessageBox(_T("GetInfo SIU Successful"));
		Log("GetInfo SIU Successful");
	}
	else {
		AfxMessageBox(hresult, MB_YESNO);
		Log("GetInfo SIU: ", hresult);
	}

	switch (dwCategory) 
	{
	case (WFS_INF_SIU_STATUS):
		ShowStatus(lpResult);
		ShowSensorsStatus(lpResult);
		break;
	case(WFS_INF_SIU_CAPABILITIES):
	
		break;
	}
	WFSFreeResult(lpResult);
}

//This function should be implemented later
void CSiu::Execute(DWORD dwCommand) 
{

}

void CSiu::Close(HSERVICE hService) 
{
	HRESULT hresult;
	hresult = WFSClose(hService);
	if (hresult == 0) {
		Log("Close Successful");
	}
	else {
		Log("Close: ", hresult);
	}
}



void CSiu::ShowStatus(WFSRESULT* lpResult) 
{
	LPWFSSIUSTATUS lpWFSSiuStatus = (LPWFSSIUSTATUS)(lpResult->lpBuffer);
	switch (lpWFSSiuStatus->fwDevice) 
	{
	case(WFS_SIU_DEVONLINE):
		Log("fwDevice: WFS_SIU_DEVONLINE");
		break;
	case(WFS_SIU_DEVOFFLINE):
		Log("fwDevice: WFS_SIU_DEVOFFLINE");
		break;
	case(WFS_SIU_DEVPOWEROFF):
		Log("fwDevice: WFS_SIU_DEVPOWEROFF");
		break;
	case(WFS_SIU_DEVNODEVICE):
		Log("fwDevice: WFS_SIU_DEVNODEVICE");
		break;
	case(WFS_SIU_DEVHWERROR):
		Log("fwDevice: WFS_SIU_DEVHWERROR");
		break;
	case(WFS_SIU_DEVUSERERROR):
		Log("fwDevice: WFS_SIU_DEVUSERERROR");
		break;
	case(WFS_SIU_DEVBUSY):
		Log("fwDevice: WFS_SIU_DEVBUSY");
		break;
	}
}

void CSiu::ShowSensorsStatus(WFSRESULT* lpResult) 
{
	LPWFSSIUSTATUS lpWFSSiuStatus = (LPWFSSIUSTATUS)(lpResult->lpBuffer);

	switch (lpWFSSiuStatus->fwSensors[WFS_SIU_OPERATORSWITCH]) 
	{
	case(WFS_SIU_NOT_AVAILABLE):
		Log("WFS_SIU_OPERATORSWITCH: WFS_SIU_NOT_AVAILABLE");
		break;
	case(WFS_SIU_RUN):
		Log("WFS_SIU_OPERATORSWITCH: WFS_SIU_RUN");
		break;
	case(WFS_SIU_MAINTENANCE):
		Log("WFS_SIU_OPERATORSWITCH: WFS_SIU_MAINTENANCE");
		break;
	case(WFS_SIU_SUPERVISOR):
		Log("WFS_SIU_OPERATORSWITCH: WFS_SIU_SUPERVISOR");
		break;
	}
	switch (lpWFSSiuStatus->fwSensors[WFS_SIU_TAMPER]) 
	{
	case(WFS_SIU_NOT_AVAILABLE):
		Log("WFS_SIU_TAMPER: WFS_SIU_NOT_AVAILABLE");
		break;
	case(WFS_SIU_OFF):
		Log("WFS_SIU_TAMPER: WFS_SIU_OFF");
		break;
	case(WFS_SIU_ON):
		Log("WFS_SIU_TAMPER: WFS_SIU_ON");
		break;
	}

	switch (lpWFSSiuStatus->fwSensors[WFS_SIU_PROXIMITY]) 
	{
	case(WFS_SIU_NOT_AVAILABLE):
		Log("WFS_SIU_PROXIMITY: WFS_SIU_NOT_AVAILABLE");
		break;
	case(WFS_SIU_PRESENT):
		Log("WFS_SIU_PROXIMITY: WFS_SIU_PRESENT");
		break;
	case(WFS_SIU_NOT_PRESENT):
		Log("WFS_SIU_PROXIMITY: WFS_SIU_NOT_PRESENT");
		break;
	}
}

void CSiu::ShowDoorsStatus(WFSRESULT* lpResult) 
{
	LPWFSSIUSTATUS lpWFSSiuStatus = (LPWFSSIUSTATUS)(lpResult->lpBuffer);

	switch (lpWFSSiuStatus->fwDoors[WFS_SIU_CABINET]) 
	{
	case(WFS_SIU_NOT_AVAILABLE):
		Log("WFS_SIU_CABINET: WFS_SIU_NOT_AVAILABLE");
		break;
	case(WFS_SIU_CLOSED):
		Log("WFS_SIU_CABINET: WFS_SIU_CLOSED");
		break;
	case(WFS_SIU_OPEN):
		Log("	WFS_SIU_OPEN");
		break;
	case(WFS_SIU_LOCKED):
		Log("WFS_SIU_CABINET: WFS_SIU_LOCKED");
		break;
	case(WFS_SIU_BOLTED):
		Log("WFS_SIU_CABINET: WFS_SIU_BOLTED");
		break;
	}

	switch (lpWFSSiuStatus->fwDoors[WFS_SIU_SAFE]) 
	{
	case(WFS_SIU_NOT_AVAILABLE):
		Log("WFS_SIU_SAFE: WFS_SIU_NOT_AVAILABLE");
		break;
	case(WFS_SIU_CLOSED):
		Log("WFS_SIU_SAFE: WFS_SIU_CLOSED");
		break;
	case(WFS_SIU_OPEN):
		Log("WFS_SIU_SAFE: WFS_SIU_OPEN");
		break;
	case(WFS_SIU_LOCKED):
		Log("WFS_SIU_SAFE: WFS_SIU_LOCKED");
		break;
	case(WFS_SIU_BOLTED):
		Log("WFS_SIU_SAFE: WFS_SIU_BOLTED");
		break;
	}

	switch (lpWFSSiuStatus->fwDoors[WFS_SIU_VANDALSHIELD]) 
	{
	case(WFS_SIU_NOT_AVAILABLE):
		Log("WFS_SIU_VANDALSHIELD: WFS_SIU_NOT_AVAILABLE");
		break;
	case(WFS_SIU_CLOSED):
		Log("WFS_SIU_VANDALSHIELD: WFS_SIU_CLOSED");
		break;
	case(WFS_SIU_OPEN):
		Log("WFS_SIU_VANDALSHIELD: WFS_SIU_OPEN");
		break;
	case(WFS_SIU_LOCKED):
		Log("WFS_SIU_VANDALSHIELD: WFS_SIU_LOCKED");
	case(WFS_SIU_SERVICE):
		Log("WFS_SIU_VANDALSHIELD: WFS_SIU_SERVICE");
		break;
	case(WFS_SIU_KEYBOARD):
		Log("WFS_SIU_VANDALSHIELD: WFS_SIU_KEYBOARD");
		break;
	case(WFS_SIU_AJAR):
		Log("WFS_SIU_VANDALSHIELD: WFS_SIU_AJAR");
		break;
	case(WFS_SIU_JAMMED):
		Log("WFS_SIU_VANDALSHIELD: WFS_SIU_JAMMED");
		break;
	}
}
