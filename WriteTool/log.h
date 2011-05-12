#ifndef _LOGFILE_HEADER
#define _LOGFILE_HEADER

class CLogFile{
public:
	void SetLogDirectory(const char *dir);
	CLogFile();
	~CLogFile();
	int Write(const char *buf, int len);
protected:
	void CreateFileName();
	int IsTheSameDay();
protected:
	CTime m_lastTime;
	CTime m_curTime;
	CString m_fileName;
	FILE *m_fp;
	char m_logDir[64];
};
extern CLogFile gLog;

#endif