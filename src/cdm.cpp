#include "pch.h"
#include "..\include\cdm.h"

CCdm::CCdm() {

}

CCdm::~CCdm() {
	delete lpWFSVersion;
	delete lpSrvcVersion;
	delete lpSPIVersion;
}

void CCdm::GetVersion() {
	lpWFSVersion->wVersion = 0x0003;
	lpWFSVersion->wLowVersion = 0x0101;
	lpWFSVersion->wHighVersion = 0x9903;
}

void CCdm::GetSrvcVersion() {
	lpSrvcVersion->wVersion = 0x0003;
	lpSrvcVersion->wLowVersion = 0x0003;
	lpSrvcVersion->wHighVersion = 0x0003;
}

void CCdm::GetSPIVersion() {
	lpSPIVersion->wVersion = 0x0003;
	lpSPIVersion->wLowVersion = 0x0003;
	lpSPIVersion->wHighVersion = 0x0003;
}


void CCdm::SethService(HSERVICE hservice) {
	m_hService = hservice;
}

HSERVICE CCdm::GethService() {
	return m_hService;
}

bool CCdm::OpenModule() {
	HRESULT hResult;
	WFSRESULT* lpResult = new WFSRESULT;

	hResult = WFSStartUp(dwCdmVersionRequired, lpWFSVersion);
	if (!hResult) {
		Log("Startup CDM Successful");
	}
	else {
		Log("Startup CDM: ", hResult);
	}

	hResult = WFSOpen("CDM", WFS_DEFAULT_HAPP, "XFSTest3.0", 0, WFS_INDEFINITE_WAIT, lpWFSVersion->wVersion, lpSrvcVersion, lpSPIVersion, &(lpResult->hService));
	SethService(lpResult->hService);

	if (hResult == 0) {
		WFSFreeResult(lpResult);
		Log("Open CDM Successful");
		AfxMessageBox(_T("Open CDM Successful"));
		return true;
	}
	else {
		WFSFreeResult(lpResult);
		Log("Open CDM: ", hResult);
		AfxMessageBox(hResult, MB_YESNO);
		return false;
	}

}

void CCdm::Register() {
	HRESULT hResult;
	LPWSTR lpClassName = L"CEventWindow";

	//::GetWindowTextW(HWND_MESSAGE, className, 255);

	if (m_hwnd = FindWindowExW(HWND_MESSAGE, NULL, lpClassName, NULL)) {
		Log("FindWindowHWND for CDM: ", m_hwnd);
	}
	else {
		Log("HWND for CDM is NULL");
	}

	hResult = WFSRegister(GethService(), SYSTEM_EVENTS | USER_EVENTS | EXECUTE_EVENTS | SERVICE_EVENTS, m_hwnd);
	if (hResult == 0) {
		AfxMessageBox(_T("Register CDM Successful"));
		Log("Register CDM Successful");
	}
	else {
		AfxMessageBox(hResult, MB_YESNO);
		Log("Register CDM: ", hResult);
	}
}

void CCdm::GetInfo(DWORD dwCategory) {
	HRESULT hresult;
	WFSRESULT* lpResult = new WFSRESULT;

	hresult = WFSGetInfo(GethService(), dwCategory, NULL, WFS_INDEFINITE_WAIT, &lpResult);
	if (hresult == 0) {
		AfxMessageBox(_T("GetInfo CDM Successful"));
		Log("GetInfo CDM Successful");
	}
	else {
		AfxMessageBox(hresult, MB_YESNO);
		Log("GetInfo CDM: ", hresult);
	}

	switch (dwCategory) {
	case (WFS_INF_CDM_STATUS):
		ShowStatus(lpResult);
		break;
	case(WFS_INF_CDM_CAPABILITIES):
	
		break;
	case(WFS_INF_CDM_CASH_UNIT_INFO):

		break;
	case(WFS_INF_CDM_TELLER_INFO):

		break;
	case(WFS_INF_CDM_CURRENCY_EXP):

		break;
	case(WFS_INF_CDM_MIX_TYPES):

		break;
	case(WFS_INF_CDM_MIX_TABLE):

		break;
	case(WFS_INF_CDM_PRESENT_STATUS):

		break;
	}
	WFSFreeResult(lpResult);
}

void CCdm::Execute(DWORD dwCommand) {

}

void CCdm::Close(HSERVICE hService) {
	HRESULT hresult;
	hresult = WFSClose(hService);
	if (hresult == 0) {
		Log("Close Successful");
	}
	else {
		Log("Close: ", hresult);
	}
}



void CCdm::ShowStatus(WFSRESULT* lpResult) {
	LPWFSCDMSTATUS lpWFSCdmStatus = (LPWFSCDMSTATUS)(lpResult->lpBuffer);
	switch (lpWFSCdmStatus->fwDevice) {
	case(WFS_CDM_DEVONLINE):
		Log("fwDevice: WFS_CDM_DEVONLINE");
		break;
	case(WFS_CDM_DEVOFFLINE):
		Log("fwDevice: WFS_CDM_DEVOFFLINE");
		break;
	case(WFS_CDM_DEVPOWEROFF):
		Log("fwDevice: WFS_CDM_DEVPOWEROFF");
		break;
	case(WFS_CDM_DEVNODEVICE):
		Log("fwDevice: WFS_CDM_DEVNODEVICE");
		break;
	case(WFS_CDM_DEVHWERROR):
		Log("fwDevice: WFS_CDM_DEVHWERROR");
		break;
	case(WFS_CDM_DEVUSERERROR):
		Log("fwDevice: WFS_CDM_DEVUSERERROR");
		break;
	case(WFS_CDM_DEVBUSY):
		Log("fwDevice: WFS_CDM_DEVBUSY");
		break;
	}
}

