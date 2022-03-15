#ifndef CSETTIME_H
#define CSETTIME_H
#include "..\..\common\include\common.h"
#include <time.h>
#include <iomanip>

class CSetTime
{
    int  m_iyear;
    int  m_imonth;
    int  m_iday;
    int  m_ihour;
    int  m_imin;
    int  m_isec;

    static tm *m_ti;
	tm newtime;

    void setYear();
    void setMonth();
    void setDay();
    void setHour();
    void setMin();
    void setSec();
    void set_ti();

public:
    CSetTime();
    void CSettime();
    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMin();
    int getSec();
};


#endif // CSETTIME_H
