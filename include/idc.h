//FILE:idc.h

#pragma once

#ifndef IDC_H
#define IDC_H

#include "..\common\include\common.h"
#include "..\include\modules.h"


static const DWORD dwIdcVersionRequired = 0x0101FF03;

class CIdc:public CModule
{
public:
	CIdc();
	CIdc(const CIdc&) = delete;
	CIdc(CIdc&&) = delete;
	CIdc& operator = (const CIdc&) = delete;
	CIdc& operator = (CIdc&&) = delete;
	virtual ~CIdc();

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
#endif  //IDC_H

