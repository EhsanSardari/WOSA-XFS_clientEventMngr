#pragma once

#ifndef MODULES_H
#define MODULES_H

#include "..\common\include\common.h"
#include "..\xfsInclude\xfsheaders.h"

class CModule {
public:
	CModule() = default;
	CModule(const CModule&) = delete;
	CModule(CModule&&) = delete;
	CModule& operator = (const CModule&) = delete;
	CModule& operator = (CModule&&) = delete;
	virtual ~CModule() = default;

	virtual bool OpenModule() = 0;
	virtual void Register() = 0;
	virtual void GetInfo(DWORD dwCategory) = 0;
	virtual void Execute(DWORD dwCommand) = 0;
	virtual void Close(HSERVICE hService) = 0;

	virtual void GetVersion() = 0;
	virtual void GetSrvcVersion() = 0;
	virtual void GetSPIVersion() = 0;

	enum ModuleNo :int { Printer = 1, IDC, CDM, TTU = 7, SIU, CAM = 10, CIM = 13 };

};

#endif
