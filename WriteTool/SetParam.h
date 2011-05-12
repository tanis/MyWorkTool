// SetParam.h: interface for the CSetParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETPARAM_H__349616A3_30D9_4C3E_8AD8_8154DF271564__INCLUDED_)
#define AFX_SETPARAM_H__349616A3_30D9_4C3E_8AD8_8154DF271564__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSetParam  
{
public:
	CSetParam();
	virtual ~CSetParam();

	BOOL isOK(); // if parser is OK
	BOOL getCfgParam(char *hwid, int len_hwid, char *bt, int len_bt);
	BOOL setCfgParam(CString hwid, CString bt);
private:
	BOOL bOKParser;
	CString hwid_min;
	CString bt_min;
};

#endif // !defined(AFX_SETPARAM_H__349616A3_30D9_4C3E_8AD8_8154DF271564__INCLUDED_)
