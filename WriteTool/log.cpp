// Log.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "log.h"
#include <stdio.h>
#include <direct.h> // for directory creation
CLogFile::CLogFile()
{
	m_lastTime = m_curTime = 0;
	m_fp = NULL; m_fileName = _T("");
}
CLogFile::~CLogFile()
{
	if(m_fp)
		fclose(m_fp);
}
int CLogFile::Write(const char *buf,int len)
{
	int ret = 0;
	CTime t= CTime::GetCurrentTime();
	CString s,writeString;
	s = t.Format("[%H:%M:%S]");
	if(m_fp == NULL) // the file should be created if it's the first time
	{
		CreateFileName();
		m_fp = fopen(m_fileName,"a");
	}else{
		if(!IsTheSameDay()){
			fclose(m_fp);
			CreateFileName();
			m_fp = fopen(m_fileName,"a");
		}

	}
	if(m_fp){
		writeString.Format("%s",buf);
		ret = fwrite(writeString,sizeof(char),writeString.GetLength(),m_fp);
		fflush(m_fp);
	}
	m_lastTime = CTime::GetCurrentTime();
	return ret;
}
void CLogFile::CreateFileName()
{
	CTime t= CTime::GetCurrentTime();
	CString dir = t.Format("%Y-%m-Log");
	CString wholePath;
	wholePath.Format("%s\\%s",m_logDir,dir);
	CString fileName = t.Format("%Y-%m-%d.log");
	mkdir(m_logDir);
	
	mkdir(wholePath);
	m_fileName.Format("%s\\%s",wholePath,fileName);
}
int CLogFile::IsTheSameDay()
{
	CTime t= CTime::GetCurrentTime();
	return (   t.GetYear() == m_lastTime.GetYear()
			&& t.GetMonth() == m_lastTime.GetMonth()
			&& t.GetDay() == m_lastTime.GetDay() );
}

void CLogFile::SetLogDirectory(const char *dir)
{

	strcpy(m_logDir,dir);

}
CLogFile gLog;

