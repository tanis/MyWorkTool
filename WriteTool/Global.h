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



extern BOOL IsIMEIString(const char* string);		//�ж��Ƿ�IMEI��
extern BOOL IsBTAddrString(const char* string);	//�ж��Ƿ�������ַ
extern BOOL IsESNString(const char* string);		//�ж��Ƿ�ESN��
extern BOOL IsMEIDString(const char* string);		//�ж��Ƿ�MEID��
extern BOOL GenDCKValue(char* pDCK);		//�������DCK������
extern void RefreshMainDlgMsgBox(char* pInformation);	//������ʾ��Ϣ(֮ǰ����Ϣ�����µ���Ϣ���)
extern void AddInfotoMainDlgMsgBox(char* pInformation);	//���һ����Ϣ(֮ǰ����Ϣ�����)
extern void EnableComboBox(BOOL bEnable);	//ʹ��ComboBox�ؼ�
extern void MinimizeMainDialog();	//��С������
extern void NotifyMainDlgOnWrite();	//�����ڵ���write
extern BOOL IsGozoneMEID(char* string,UINT* pOffsetToBaseMEID);	//�ж������MEID�Ƿ����������ļ���ָ���ķ�Χ
// �жϷ�Χ��ͬʱ�������Զ�����������ַ��offset
extern BOOL IsGozoneIMEI(char* string,UINT* pOffsetToBaseIMEI);

extern BOOL IsGozoneBtAddr(UINT OffsetToBaseBTAddr, char* string);	//�ж������BTAddr�Ƿ����������ļ���ָ���ķ�Χ
extern BOOL IsGozoneEsn(char* string,UINT* pOffsetToBaseEsn);	//�ж������ESN�Ƿ����������ļ���ָ���ķ�Χ
extern BOOL IsStrInTrackFile(CString Str);	//�ж�Str�Ƿ����Track�ļ���
extern BOOL AddToTrackFile(CString Info);	//������Ϣ��Track�ļ���
extern BOOL GetFileFullName(char* pFileFullName, char* FileName);	//��ȡָ���ļ���ȫ·��

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

