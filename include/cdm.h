#pragma once

#ifndef CDM_H
#define CDM_H

#include "..\common\include\common.h"
#include "..\include\modules.h"


static const DWORD dwCdmVersionRequired = 0x0101FF03;

class CCdm:public CModule{
public:
	CCdm();
	CCdm(const CCdm&) = delete;
	CCdm(CCdm&&) = delete;
	CCdm& operator = (const CCdm&) = delete;
	CCdm& operator = (CCdm&&) = delete;
	virtual ~CCdm();

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


private:
	HWND m_hwnd;
};
#endif

