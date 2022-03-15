#include "pch.h"
#include "..\include\idc.h"

CIdc::CIdc() {

}

CIdc::~CIdc() {
	delete lpWFSVersion;
	delete lpSrvcVersion;
	delete lpSPIVersion;
}

void CIdc::GetVersion() {
	lpWFSVersion->wVersion = 0x0003;
	lpWFSVersion->wLowVersion = 0x0101;
	lpWFSVersion->wHighVersion = 0x9903;
}

void CIdc::GetSrvcVersion() {
	lpSrvcVersion->wVersion = 0x0003;
	lpSrvcVersion->wLowVersion = 0x0003;
	lpSrvcVersion->wHighVersion = 0x0003;
}

void CIdc::GetSPIVersion() {
	lpSPIVersion->wVersion = 0x0003;
	lpSPIVersion->wLowVersion = 0x0003;
	lpSPIVersion->wHighVersion = 0x0003;
}


void CIdc::SethService(HSERVICE hservice) {
	m_hService = hservice;
}

HSERVICE CIdc::GethService() {
	return m_hService;
}

bool CIdc::OpenModule() {
	HRESULT hResult;
	WFSRESULT* lpResult = new WFSRESULT;

	hResult = WFSStartUp(dwIdcVersionRequired, lpWFSVersion);
	if (!hResult) {
		Log("Startup IDC Successful");
	}
	else {
		Log("Startup: ", hResult);
	}

	hResult = WFSOpen("IDC", WFS_DEFAULT_HAPP, "XFSTest3.0", 0, WFS_INDEFINITE_WAIT, lpWFSVersion->wVersion, lpSrvcVersion, lpSPIVersion, &(lpResult->hService));
	SethService(lpResult->hService);

	if (hResult == 0) {
		WFSFreeResult(lpResult);
		Log("Open IDC Successful");
		AfxMessageBox(_T("Open IDC Successful"));
		return true;
	}
	else {
		WFSFreeResult(lpResult);
		Log("Open IDC: ", hResult);
		AfxMessageBox(hResult, MB_YESNO);
		return false;
	}

}

void CIdc::Register() {
	HRESULT hResult;
	LPWSTR lpClassName = L"CEventWindow";

	//::GetWindowTextW(HWND_MESSAGE, className, 255);

	if (m_hwnd = FindWindowExW(HWND_MESSAGE, NULL, lpClassName, NULL)) {
		Log("FindWindowHWND for IDC: ", m_hwnd);
	}
	else {
		Log("HWND for IDC is NULL");
	}

	hResult = WFSRegister(GethService(), SYSTEM_EVENTS | USER_EVENTS | EXECUTE_EVENTS | SERVICE_EVENTS, m_hwnd);
	if (hResult == 0) {
		AfxMessageBox(_T("Register IDC Successful"));
		Log("Register IDC Successful");
	}
	else {
		AfxMessageBox(hResult, MB_YESNO);
		Log("Register: ", hResult);
	}
}

void CIdc::GetInfo(DWORD dwCategory) {
	HRESULT hresult;
	WFSRESULT* lpResult = new WFSRESULT;

	hresult = WFSGetInfo(GethService(), dwCategory, NULL, WFS_INDEFINITE_WAIT, &lpResult);
	if (hresult == 0) {
		AfxMessageBox(_T("GetInfo IDC Successful"));
		Log("GetInfo IDC Successful");
	}
	else {
		AfxMessageBox(hresult, MB_YESNO);
		Log("GetInfo IDC: ", hresult);
	}

	switch (dwCategory) {
	case (WFS_INF_IDC_STATUS):
		ShowStatus(lpResult);
		break;
	case(WFS_INF_IDC_CAPABILITIES):
	
		break;
	case(WFS_INF_IDC_FORM_LIST):

		break;
	case(WFS_INF_IDC_QUERY_FORM):

		break;
	}
	WFSFreeResult(lpResult);
}

void CIdc::Execute(DWORD dwCommand) {

}

void CIdc::Close(HSERVICE hService) {
	HRESULT hresult;
	hresult = WFSClose(hService);
	if (hresult == 0) {
		Log("Close IDC Successful");
	}
	else {
		Log("CloseIDC : ", hresult);
	}
}


void CIdc::ShowStatus(WFSRESULT* lpResult) {
	LPWFSIDCSTATUS lpWFSIDCStatus = (LPWFSIDCSTATUS)(lpResult->lpBuffer);
	switch (lpWFSIDCStatus->fwDevice) {
	case(WFS_IDC_DEVONLINE):
		Log("fwDevice: WFS_PTR_DEVONLINE");
		break;
	case(WFS_IDC_DEVOFFLINE):
		Log("fwDevice: WFS_PTR_DEVOFFLINE");
		break;
	case(WFS_IDC_DEVPOWEROFF):
		Log("fwDevice: WFS_PTR_DEVPOWEROFF");
		break;
	case(WFS_IDC_DEVNODEVICE):
		Log("fwDevice: WFS_PTR_DEVNODEVICE");
		break;
	case(WFS_IDC_DEVHWERROR):
		Log("fwDevice: WFS_PTR_DEVHWERROR");
		break;
	case(WFS_IDC_DEVUSERERROR):
		Log("fwDevice: WFS_PTR_DEVUSERERROR");
		break;
	case(WFS_IDC_DEVBUSY):
		Log("fwDevice: WFS_PTR_DEVBUSY");
		break;
	}
}

