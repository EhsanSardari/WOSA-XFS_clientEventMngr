#pragma once

#ifndef SIU_H
#define SIU_H

#include "..\common\include\common.h"
#include "..\include\modules.h"


static const DWORD dwSiuVersionRequired = 0x0101FF03;

class CSiu:public CModule{
public:
	CSiu();
	CSiu(const CSiu&) = delete;
	CSiu(CSiu&&) = delete;
	CSiu& operator = (const CSiu&) = delete;
	CSiu& operator = (CSiu&&) = delete;
	virtual ~CSiu();

	bool OpenModule();
	void Register();
	void GetInfo(DWORD dwCategory);
	void Execute(DWORD dwCommand);
	void Close(HSERVICE hService);

	WFSVERSION* lpWFSVersion = new WFSVERSION;
	WFSVERSION* lpSrvcVersion = new WFSVERSION;
	WFSVERSION* lpSPIVersion = new WFSVERSION;

	void GetVersion();
	void GetSrvcVersion();
	void GetSPIVersion();

	HSERVICE m_hService;
	void SethService(HSERVICE hservice);
	HSERVICE GethService();
	void ShowStatus(WFSRESULT* lpResult);
	void ShowSensorsStatus(WFSRESULT* lpResult);
	void ShowDoorsStatus(WFSRESULT* lpResult);

private:
	HWND m_hwnd;
};
#endif

