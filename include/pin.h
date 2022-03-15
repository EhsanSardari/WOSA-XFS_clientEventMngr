#pragma once

#ifndef PIN_H
#define PIN_H

#include "..\common\include\common.h"
#include "..\include\modules.h"


static const DWORD dwPinVersionRequired = 0x0101FF03;

class CPin:public CModule{
public:
	CPin();
	CPin(const CPin&) = delete;
	CPin(CPin&&) = delete;
	CPin& operator = (const CPin&) = delete;
	CPin& operator = (CPin&&) = delete;
	virtual ~CPin();

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

