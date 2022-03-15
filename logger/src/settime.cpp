#include "pch.h"
#include "..\include\settime.h"

CSetTime::CSetTime()
{
}

/*!
 * input:none
 * output:none
 * set date and time and log it in test.txt file
 */
tm* CSetTime::m_ti;

void CSetTime::CSettime(){
    set_ti();
    setYear();
    setMonth();
    setDay();
    setHour();
    setMin();
    setSec();

    int iyear  = getYear();
    int imonth = getMonth();
    int iday   = getDay();
    int ihour  = getHour();
    int imin   = getMin();
    int isec   = getSec();

    ofstream out("Log.txt", ios::app);
    if(!out.is_open()){
        cout <<"Can not open test.txt in settime\n";
    }

    out << "[" << iyear << "/" << setw(2) << setfill('0') << imonth << "/" << setw(2) << setfill('0') << iday << "  ";
    out << setw(2) << setfill('0') << ihour << ":" << setw(2) << setfill('0') << imin << ":" << setw(2) << setfill('0') << isec <<"]" <<"  ";

    out.close();
}

void CSetTime::set_ti() {
	time_t now = time(0);
	localtime_s(&newtime, &now);
	m_ti = &newtime;
}

void CSetTime::setYear(){
    m_iyear  = 1900 + m_ti->tm_year;
}

void CSetTime::setMonth(){
     m_imonth = 1 + m_ti->tm_mon;
}

void CSetTime::setDay(){
    m_iday   = m_ti->tm_mday;
}

void CSetTime::setHour(){
    m_ihour  = m_ti->tm_hour;
}

void CSetTime::setMin(){
     m_imin   = m_ti->tm_min;
}

void CSetTime::setSec(){
    m_isec   = m_ti->tm_sec;
}

int CSetTime::getYear(){
    return m_iyear;
}

int CSetTime::getMonth(){
    return m_imonth;
}

int CSetTime::getDay(){
    return m_iday;
}

int CSetTime::getHour(){
    return m_ihour;
}

int CSetTime::getMin(){
    return m_imin;
}

int CSetTime::getSec(){
    return m_isec;
}