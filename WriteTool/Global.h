#ifndef __WRITETOOL_GLOBAL_H__
#define __WRITETOOL_GLOBAL_H__

#include "DllParam.h"

#define WRITE_TOOL_CONFIG_FILE		"GDWToolFRV.cfg"
#define WRITE_TOOL_TRACK_FILE		"GDWToolFRV.trk"

#define MAX_DCK_LENGTH 16
#define MAX_COM_NUM	100

#ifdef FRV_RELEASE
#define CFGFILE_BT_ADDR_STRLEN	GOZONE_BT_ADDRESS_SIZE*2
#define CFGFILE_MEID_STRLEN		(GOZONE_MEID_SIZE-1)*2
#define CFGFILE_WRITE_FLAG		1
#define CFGFILE_ESN_STRLEN		GOZONE_ESN_SIZE*2
#define CFGFILE_IMEI_STRLEN		GOZONE_IMEI_SIZE*2
#endif

typedef struct tagComInfo
{
	UINT ComID;
	BOOL bIsConnect;
	BOOL bIsOpen;
	int  ComNum;
	int  ComIDList[MAX_COM_NUM];
}TComPortInfo;

//Param of Sign Server
extern char gProjectName[GOZONE_PRJECT_NAME_SIZE];
extern char gIPAddress[GOZONE_IP_ADDRESS_SIZE];

#ifdef FRV_RELEASE
extern char CfgMinBtAddress[CFGFILE_BT_ADDR_STRLEN+1];
extern char CfgMaxBtAddress[CFGFILE_BT_ADDR_STRLEN+1];
extern char CfgMinMEID[CFGFILE_MEID_STRLEN+1];
extern char CfgMaxMEID[CFGFILE_MEID_STRLEN+1];
extern char CfgWriteMEID[CFGFILE_WRITE_FLAG+1];
extern char CfgWriteBTAddr[CFGFILE_WRITE_FLAG+1];
extern char CfgMinESN[CFGFILE_ESN_STRLEN+1];
extern char CfgMaxESN[CFGFILE_ESN_STRLEN+1];
extern char CfgWriteESN[CFGFILE_WRITE_FLAG+1];
extern char CfgMinIMEI[CFGFILE_IMEI_STRLEN+1];
extern char CfgMaxIMEI[CFGFILE_IMEI_STRLEN+1];
extern char CfgWriteIMEI[CFGFILE_WRITE_FLAG+1];
#endif

//Param of Handset
extern OTP_IMEI				gIMEI;
extern OTP_IMEI2				gIMEI2;
extern OTP_BlueToothAddr	gBTAddress;
extern OTP_PublicKey		gPublicKey;
extern OTP_Plmn				gPlmnList;
extern OTP_SIMLockInfo		gSimLockInfo;
extern OTP_ESN				gESN;
extern char					gDCK[MAX_DCK_LENGTH+1];
extern char					gBaseAdjust;
extern char					gGeneralAdjust;
extern OTP_MEID				gMEID;
//Read&Write control
extern HINSTANCE ghLibraryDllParam;
extern TComPortInfo gComPortInfo;
extern BOOL gbCheckIMEI;
extern BOOL gbCheckBTAddr;
extern BOOL gbCheckDCK;
extern BOOL gbCheckPublicKey;
extern BOOL gbCheckSimLockInfo;
extern BOOL gbCheckPlmnList;
extern BOOL gbCheckESN;
extern BOOL gbCheckMEID;
extern BOOL gbCheckAutoGenDCK;
extern BOOL gbCheckAutoIncIMEI;
extern BOOL gbCheckAutoIncBTAddr;
extern BOOL gbCheckAutoIncESN;
extern BOOL gbCheckAutoIncMEID;
extern BOOL gbCheckBaseAdjust;
extern BOOL gbCheckGeneralAdjust;



extern BOOL IsIMEIString(const char* string);		//判断是否IMEI号
extern BOOL IsBTAddrString(const char* string);	//判断是否蓝牙地址
extern BOOL IsESNString(const char* string);		//判断是否ESN号
extern BOOL IsMEIDString(const char* string);		//判断是否MEID号
extern BOOL GenDCKValue(char* pDCK);		//随机生产DCK的明码
extern void RefreshMainDlgMsgBox(char* pInformation);	//重设显示信息(之前的信息将被新的信息替代)
extern void AddInfotoMainDlgMsgBox(char* pInformation);	//添加一条信息(之前的信息不清除)
extern void EnableComboBox(BOOL bEnable);	//使能ComboBox控件
extern void MinimizeMainDialog();	//最小化窗口
extern void NotifyMainDlgOnWrite();	//主窗口调用write
extern BOOL IsGozoneMEID(char* string,UINT* pOffsetToBaseMEID);	//判断输入的MEID是否属于配置文件中指定的范围
// 判断范围，同时，处理自动生成蓝牙地址的offset
extern BOOL IsGozoneIMEI(char* string,UINT* pOffsetToBaseIMEI);

extern BOOL IsGozoneBtAddr(UINT OffsetToBaseBTAddr, char* string);	//判断输入的BTAddr是否属于配置文件中指定的范围
extern BOOL IsGozoneEsn(char* string,UINT* pOffsetToBaseEsn);	//判断输入的ESN是否属于配置文件中指定的范围
extern BOOL IsStrInTrackFile(CString Str);	//判断Str是否存在Track文件中
extern BOOL AddToTrackFile(CString Info);	//增加信息到Track文件中
extern BOOL GetFileFullName(char* pFileFullName, char* FileName);	//获取指定文件的全路径

//For UI
extern BOOL GetValueFromHexString(CString HexString, byte* pValue);
//IMEI&BT&ESN&MEID
extern BOOL IMEIInc(char* pIMEI);
extern BOOL IMEIDec(char* pIMEI);
extern BOOL BTAddressInc(char* pBTAddress);
extern BOOL BTAddressDec(char* pBTAddress);
extern BOOL ESNInc(char* pESN);
extern BOOL ESNDec(char* pESN);
extern BOOL MEIDInc(char* pMEID);
extern BOOL MEIDDec(char* pMEID);
//Com Port
extern BOOL SetupComPort();
extern BOOL CloseComPort();
//Set Param of Server
extern BOOL SetServerParam();


#define ReadWriteComReq() \
{\
	if(SetupComPort() == TRUE)\
	{\
		if(SetServerParam() == FALSE)\
		{\
			RefreshMainDlgMsgBox("Set param of sign server failed!");\
			CloseComPort();\
			return;\
		}\
	}\
	else\
	{\
		if(gComPortInfo.bIsConnect == TRUE)\
		{\
			if(gComPortInfo.ComNum > 1)\
			{\
				RefreshMainDlgMsgBox("Two or more phones is connected,please check!");\
			}\
			else\
			{\
				RefreshMainDlgMsgBox("Gozone phone is using,please check!");\
			}\
		}\
		else\
		{\
			RefreshMainDlgMsgBox("No phone connected!");\
		}\
		return;\
	}\
}


#define ChangeDataFromHexString(HexString,pValue) \
{\
	if(GetValueFromHexString(HexString,pValue) == FALSE)\
	{\
		MessageBox("One of more data is not hex,please check!",NULL,MB_ICONWARNING);\
		return;\
	}\
}


#define CheckProcReturnVoid(ProcAddress,pErrorString) \
{\
	if(ProcAddress == NULL)\
	{\
		CString Buffer = CString("Load process \"");\
		Buffer += CString(pErrorString);\
		Buffer += CString("\" failed!");\
		MessageBox(Buffer.GetBuffer(0), NULL, MB_ICONERROR);\
		AddInfotoMainDlgMsgBox(Buffer.GetBuffer(0));\
		CloseComPort();\
		return;\
	}\
}


#define CheckProcReturnFALSE(ProcAddress,pErrorString) \
{\
	if(ProcAddress == NULL)\
	{\
		CString Buffer = CString("Load process \"");\
		Buffer += CString(pErrorString);\
		Buffer += CString("\" failed!");\
		MessageBox(Buffer.GetBuffer(0), NULL, MB_ICONERROR);\
		return FALSE;\
	}\
}


#endif	//__WRITETOOL_GLOBAL_H__

