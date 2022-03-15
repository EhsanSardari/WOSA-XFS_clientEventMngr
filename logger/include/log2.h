#pragma once

#ifndef LOG_H
#define LOG_H

#include "..\..\common\include\common.h"
#include "..\include\settime.h"

static const unsigned int gLogLevel = 1;


class CLogger 
{
public:
	CLogger() = delete;
	CLogger(const CLogger&) = delete;
	CLogger(CLogger&&) = delete;
	CLogger& operator = (const CLogger&) = delete;
	CLogger& operator = (CLogger&&) = delete;
	~CLogger();

	void SetLogLevel(int nlogLevel);
	void WriteLog(int nlogLevel,const wchar_t* log, ...);
	enum LogLevel { Trace, Debug, Info, Warn, Error, Fatal };

private:
	static int nLogLevel;
};


#endif // LOG_H

