#include "pch.h"
#include "..\include\printer.h"

CPrinter::CPrinter() {

}

CPrinter::~CPrinter() {
	delete lpWFSVersion;
	delete lpSrvcVersion;
	delete lpSPIVersion;
}

void CPrinter::GetVersion() {
	lpWFSVersion->wVersion = 0x0003;
	lpWFSVersion->wLowVersion = 0x0101;
	lpWFSVersion->wHighVersion = 0x9903;
}

void CPrinter::GetSrvcVersion() {
	lpSrvcVersion->wVersion = 0x0003;
	lpSrvcVersion->wLowVersion = 0x0003;
	lpSrvcVersion->wHighVersion = 0x0003;
}

void CPrinter::GetSPIVersion() {
	lpSPIVersion->wVersion = 0x0003;
	lpSPIVersion->wLowVersion = 0x0003;
	lpSPIVersion->wHighVersion = 0x0003;
}


void CPrinter::SethService(HSERVICE hservice) {
	m_hService = hservice;
}

HSERVICE CPrinter::GethService() {
	return m_hService;
}

bool CPrinter::OpenModule() {
	HRESULT hResult;
	WFSRESULT* lpResult = new WFSRESULT;

	hResult = WFSStartUp(dwPtrVersionRequired, lpWFSVersion);
	if (!hResult) {
		Log("Startup PTR Successful");
	}
	else {
		Log("Startup PTR: ", hResult);
	}

	hResult = WFSOpen("RPTR", WFS_DEFAULT_HAPP, "XFSTest3.0", 0, WFS_INDEFINITE_WAIT, lpWFSVersion->wVersion, lpSrvcVersion, lpSPIVersion, &(lpResult->hService));
	SethService(lpResult->hService);

	if (hResult == 0) {
		WFSFreeResult(lpResult);
		Log("Open PTR Successful");
		AfxMessageBox(_T("Open PTR Successful"));
		return true;
	}
	else {
		WFSFreeResult(lpResult);
		Log("Open PTR: ", hResult);
		AfxMessageBox(hResult, MB_YESNO);
		return false;
	}

}

void CPrinter::Register() {
	HRESULT hResult;
	LPWSTR lpClassName = L"CEventWindow";

	//::GetWindowTextW(HWND_MESSAGE, className, 255);

	if (m_hwnd = FindWindowExW(HWND_MESSAGE, NULL, lpClassName, NULL)) {
		Log("FindWindowHWND for PTR: ", m_hwnd);
	}
	else {
		Log("HWND for PTR is NULL");
	}

	hResult = WFSRegister(GethService(), SYSTEM_EVENTS | USER_EVENTS | EXECUTE_EVENTS | SERVICE_EVENTS, m_hwnd);
	if (hResult == 0) {
		AfxMessageBox(_T("Register PTR Successful"));
		Log("Register PTR Successful");
	}
	else {
		AfxMessageBox(hResult, MB_YESNO);
		Log("Register PTR: ", hResult);
	}
}

void CPrinter::GetInfo(DWORD dwCategory) {
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
	case (WFS_INF_PTR_STATUS):
		ShowStatus(lpResult);
		break;
	case(WFS_INF_PTR_CAPABILITIES):
	
		break;
	case(WFS_INF_PTR_FORM_LIST):

		break;
	case(WFS_INF_PTR_MEDIA_LIST):

		break;
	case(WFS_INF_PTR_QUERY_FORM):

		break;
	case(WFS_INF_PTR_QUERY_MEDIA):

		break;
	case(WFS_INF_PTR_QUERY_FIELD):

		break;
	}
	WFSFreeResult(lpResult);
}

void CPrinter::Execute(DWORD dwCommand) {

}

void CPrinter::Close(HSERVICE hService) {
	HRESULT hresult;
	hresult = WFSClose(hService);
	if (hresult == 0) {
		Log("Close Successful");
	}
	else {
		Log("Close: ", hresult);
	}
}



void CPrinter::ShowStatus(WFSRESULT* lpResult) {
	LPWFSPTRSTATUS lpWFSPTRStatus = (LPWFSPTRSTATUS)(lpResult->lpBuffer);
	switch (lpWFSPTRStatus->fwDevice) {
	case(WFS_PTR_DEVONLINE):
		Log("fwDevice: WFS_PTR_DEVONLINE");
		break;
	case(WFS_PTR_DEVOFFLINE):
		Log("fwDevice: WFS_PTR_DEVOFFLINE");
		break;
	case(WFS_PTR_DEVPOWEROFF):
		Log("fwDevice: WFS_PTR_DEVPOWEROFF");
		break;
	case(WFS_PTR_DEVNODEVICE):
		Log("fwDevice: WFS_PTR_DEVNODEVICE");
		break;
	case(WFS_PTR_DEVHWERROR):
		Log("fwDevice: WFS_PTR_DEVHWERROR");
		break;
	case(WFS_PTR_DEVUSERERROR):
		Log("fwDevice: WFS_PTR_DEVUSERERROR");
		break;
	case(WFS_PTR_DEVBUSY):
		Log("fwDevice: WFS_PTR_DEVBUSY");
		break;
	}

	switch (lpWFSPTRStatus->fwPaper[WFS_PTR_SUPPLYUPPER]) {
	case(WFS_PTR_PAPERFULL):
		Log("WFS_PTR_SUPPLYUPPER: WFS_PTR_PAPERFULL");
		break;
	case(WFS_PTR_PAPERLOW):
		Log("WFS_PTR_SUPPLYUPPER: WFS_PTR_PAPERLOW");
		break;
	case(WFS_PTR_PAPEROUT):
		Log("WFS_PTR_SUPPLYUPPER: WFS_PTR_PAPEROUT");
		break;
	case(WFS_PTR_PAPERNOTSUPP):
		Log("WFS_PTR_SUPPLYUPPER: WFS_PTR_PAPERNOTSUPP");
		break;
	case(WFS_PTR_PAPERUNKNOWN):
		Log("WFS_PTR_SUPPLYUPPER: WFS_PTR_PAPERUNKNOWN");
		break;
	}

}

