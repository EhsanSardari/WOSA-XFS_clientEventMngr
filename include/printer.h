#pragma once

#ifndef PRINTER_H
#define PRINTER_H

#include "..\common\include\common.h"
#include "..\include\modules.h"


static const DWORD dwPtrVersionRequired = 0x0101FF03;

class CPrinter:public CModule{
public:
	CPrinter();
	CPrinter(const CPrinter&) = delete;
	CPrinter(CPrinter&&) = delete;
	CPrinter& operator = (const CPrinter&) = delete;
	CPrinter& operator = (CPrinter&&) = delete;
	virtual ~CPrinter();

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

