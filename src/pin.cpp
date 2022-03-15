#include "pch.h"
#include "..\include\pin.h"

CPin::CPin() {

}

CPin::~CPin() {
	delete lpWFSVersion;
	delete lpSrvcVersion;
	delete lpSPIVersion;
}

void CPin::GetVersion() {
	lpWFSVersion->wVersion = 0x0003;
	lpWFSVersion->wLowVersion = 0x0101;
	lpWFSVersion->wHighVersion = 0x9903;
}

void CPin::GetSrvcVersion() {
	lpSrvcVersion->wVersion = 0x0003;
	lpSrvcVersion->wLowVersion = 0x0003;
	lpSrvcVersion->wHighVersion = 0x0003;
}

void CPin::GetSPIVersion() {
	lpSPIVersion->wVersion = 0x0003;
	lpSPIVersion->wLowVersion = 0x0003;
	lpSPIVersion->wHighVersion = 0x0003;
}


void CPin::SethService(HSERVICE hservice) {
	m_hService = hservice;
}

HSERVICE CPin::GethService() {
	return m_hService;
}

bool CPin::OpenModule() {
	HRESULT hResult;
	WFSRESULT* lpResult = new WFSRESULT;

	hResult = WFSStartUp(dwPinVersionRequired, lpWFSVersion);
	if (!hResult) {
		Log("Startup PIN Successful");
	}
	else {
		Log("Startup PIN: ", hResult);
	}

	hResult = WFSOpen("PIN", WFS_DEFAULT_HAPP, "XFSTest3.0", 0, WFS_INDEFINITE_WAIT, lpWFSVersion->wVersion, lpSrvcVersion, lpSPIVersion, &(lpResult->hService));
	SethService(lpResult->hService);

	if (hResult == 0) {
		WFSFreeResult(lpResult);
		Log("Open PIN Successful");
		AfxMessageBox(_T("Open PIN Successful"));
		return true;
	}
	else {
		WFSFreeResult(lpResult);
		Log("Open PIN: ", hResult);
		AfxMessageBox(hResult, MB_YESNO);
		return false;
	}

}

void CPin::Register() {
	HRESULT hResult;
	LPWSTR lpClassName = L"CEventWindow";

	//::GetWindowTextW(HWND_MESSAGE, className, 255);

	if (m_hwnd = FindWindowExW(HWND_MESSAGE, NULL, lpClassName, NULL)) {
		Log("FindWindowHWND for PIN: ", m_hwnd);
	}
	else {
		Log("HWND for PIN is NULL");
	}

	hResult = WFSRegister(GethService(), SYSTEM_EVENTS | USER_EVENTS | EXECUTE_EVENTS | SERVICE_EVENTS, m_hwnd);
	if (hResult == 0) {
		AfxMessageBox(_T("Register PIN Successful"));
		Log("Register PIN Successful");
	}
	else {
		AfxMessageBox(hResult, MB_YESNO);
		Log("Register PTR: ", hResult);
	}
}

void CPin::GetInfo(DWORD dwCategory) {
	HRESULT hresult;
	WFSRESULT* lpResult = new WFSRESULT;

	hresult = WFSGetInfo(GethService(), dwCategory, NULL, WFS_INDEFINITE_WAIT, &lpResult);
	if (hresult == 0) {
		AfxMessageBox(_T("GetInfo PTR Successful"));
		Log("GetInfo PTR Successful");
	}
	else {
		AfxMessageBox(hresult, MB_YESNO);
		Log("GetInfo PTR: ", hresult);
	}

	switch (dwCategory) {
	case (WFS_INF_PIN_STATUS):
		ShowStatus(lpResult);
		break;
	case(WFS_INF_PIN_CAPABILITIES):

		break;
	case(WFS_INF_PIN_KEY_DETAIL):

		break;
	case(WFS_INF_PIN_FUNCKEY_DETAIL):

		break;
	case(WFS_INF_PIN_HSM_TDATA):

		break;
	case(WFS_INF_PIN_KEY_DETAIL_EX):

		break;
		}
	WFSFreeResult(lpResult);
}

void CPin::Execute(DWORD dwCommand) {

}

void CPin::Close(HSERVICE hService) {
	HRESULT hresult;
	hresult = WFSClose(hService);
	if (hresult == 0) {
		Log("Close Successful");
	}
	else {
		Log("Close: ", hresult);
	}
}



void CPin::ShowStatus(WFSRESULT* lpResult) {
	LPWFSPINSTATUS lpWFSPinStatus = (LPWFSPINSTATUS)(lpResult->lpBuffer);
	switch (lpWFSPinStatus->fwDevice) {
	case(WFS_PIN_DEVONLINE):
		Log("fwDevice: WFS_PIN_DEVONLINE");
		break;
	case(WFS_PIN_DEVOFFLINE):
		Log("fwDevice: WFS_PIN_DEVOFFLINE");
		break;
	case(WFS_PIN_DEVPOWEROFF):
		Log("fwDevice: WFS_PIN_DEVPOWEROFF");
		break;
	case(WFS_PIN_DEVNODEVICE):
		Log("fwDevice: WFS_PIN_DEVNODEVICE");
		break;
	case(WFS_PIN_DEVHWERROR):
		Log("fwDevice: WFS_PIN_DEVHWERROR");
		break;
	case(WFS_PIN_DEVUSERERROR):
		Log("fwDevice: WFS_PIN_DEVUSERERROR");
		break;
	case(WFS_PIN_DEVBUSY):
		Log("fwDevice: WFS_PIN_DEVBUSY");
		break;
	}
}

