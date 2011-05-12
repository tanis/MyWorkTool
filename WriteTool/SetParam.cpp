// SetParam.cpp: implementation of the CSetParam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "writetool.h"
#include "SetParam.h"
#include <windows.h>
#include "Global.h"
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// if parser is OK
BOOL CSetParam::isOK()
{
	return bOKParser;
}
BOOL  CSetParam::getCfgParam(char *a_hwid, int len_hwid, char *a_bt, int len_bt)
{
	const char *hwid = hwid_min;
	const char *bt = bt_min;
	strncpy(a_hwid, hwid, len_hwid);
	strncpy(a_bt, bt, len_bt);
	return TRUE;
}

CSetParam::CSetParam()
{
	char file_FullName[MAX_PATH+1] = {0};
	CString tmp;
	bOKParser = FALSE;
	if (GetFileFullName(file_FullName, "hwid_cfg.ini"))
	{
		if ( 0< GetPrivateProfileString("Product","IMEI","", hwid_min.GetBuffer(MAX_PATH),MAX_PATH, file_FullName)
			&& 0< GetPrivateProfileString("Product","BT_ADDR","", bt_min.GetBuffer(MAX_PATH),MAX_PATH, file_FullName))
		{
			// check
			const char *hwid = hwid_min;
			const char *bt = bt_min;
			if (IsIMEIString(hwid)
				&& IsBTAddrString(bt))
			{
				bOKParser = TRUE;
			}
		}
	}
}


BOOL CSetParam::setCfgParam(CString a_hwid, CString a_bt)
{
	const char *hwid = a_hwid;
	const char* bt = a_bt;
	if (IsIMEIString(hwid)
		&& IsBTAddrString(bt))
	{
		hwid_min = a_hwid;
		bt_min = a_bt;
		bOKParser = TRUE;
	}
	else
	{
		bOKParser = FALSE;;
	}
	return bOKParser;


}

CSetParam::~CSetParam()
{
}
