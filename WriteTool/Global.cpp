#include "stdafx.h"
#include "Global.h"
#include "DllParam.h"

//Param of Sign Server
char gProjectName[GOZONE_PRJECT_NAME_SIZE]	= "";
char gIPAddress[GOZONE_IP_ADDRESS_SIZE]		= "";

//Param of Handset
OTP_IMEI			gIMEI = {0};
OTP_BlueToothAddr	gBTAddress = {0};
OTP_PublicKey		gPublicKey = {0};
OTP_Plmn			gPlmnList = {0};
OTP_SIMLockInfo		gSimLockInfo = {0};
OTP_ESN				gESN = {0};
OTP_MEID			gMEID = {0};
char gDCK[MAX_DCK_LENGTH+1] = {0};
char gBaseAdjust = 0;
char gGeneralAdjust = 0;

//Read&Write control
HINSTANCE ghLibraryDllParam	= NULL;
TComPortInfo gComPortInfo	= {0};
BOOL gbCheckIMEI			= FALSE;
BOOL gbCheckBTAddr			= FALSE;
BOOL gbCheckDCK				= FALSE;
BOOL gbCheckPublicKey		= FALSE;
BOOL gbCheckSimLockInfo		= FALSE;
BOOL gbCheckPlmnList		= FALSE;
BOOL gbCheckESN				= FALSE;
BOOL gbCheckMEID			= FALSE;
BOOL gbCheckAutoGenDCK		= FALSE;
BOOL gbCheckAutoIncIMEI		= FALSE;
BOOL gbCheckAutoIncBTAddr	= FALSE;
BOOL gbCheckAutoIncESN		= FALSE;
BOOL gbCheckAutoIncMEID		= FALSE;
BOOL gbCheckBaseAdjust		= FALSE;
BOOL gbCheckGeneralAdjust	= FALSE;

//Param of Cfg File
char CfgMinBtAddress[CFGFILE_BT_ADDR_STRLEN+1] = {0};
char CfgMaxBtAddress[CFGFILE_BT_ADDR_STRLEN+1] = {0};
char CfgMinMEID[CFGFILE_MEID_STRLEN+1] = {0};
char CfgMaxMEID[CFGFILE_MEID_STRLEN+1] = {0};
char CfgMinESN[CFGFILE_ESN_STRLEN+1] = {0};
char CfgMaxESN[CFGFILE_ESN_STRLEN+1] = {0};

char CfgWriteMEID[CFGFILE_WRITE_FLAG+1] = {0};
char CfgWriteBTAddr[CFGFILE_WRITE_FLAG+1] = {0};
char CfgWriteESN[CFGFILE_WRITE_FLAG+1] = {0};


BOOL IsIMEIString(char* string)
{
	UINT nLen = strlen(string);

	if(nLen != 14)
	{
		return FALSE;
	}
	for(UINT i=0; i<nLen; i++)
	{
		if(!(string[i]>='0' && string[i]<='9'))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL IsBTAddrString(const char* string)
{
	UINT nLen = strlen(string);

	if(nLen != GOZONE_BT_ADDRESS_SIZE*2)
	{
		return FALSE;
	}
	for(UINT i=0; i<nLen; i++)
	{
		if(!((string[i]>='0' && string[i]<='9')
			||(string[i]>='a' && string[i]<='f')
			||(string[i]>='A' && string[i]<='F')))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL IsESNString(const char* string)
{
	UINT nLen = strlen(string);
	
	if(nLen != GOZONE_ESN_SIZE*2)
	{
		return FALSE;
	}
	for(UINT i=0; i<nLen; i++)
	{
		if(!((string[i]>='0' && string[i]<='9')
			||(string[i]>='a' && string[i]<='f')
			||(string[i]>='A' && string[i]<='F')))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL IsMEIDString(const char* string)
{
	UINT nLen = strlen(string);
	
	if(nLen != 14)
	{
		return FALSE;
	}
	for(UINT i=0; i<nLen; i++)
	{
		if(!((string[i]>='0' && string[i]<='9')
			||(string[i]>='a' && string[i]<='f')
			||(string[i]>='A' && string[i]<='F')))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL GenDCKValue(char* pDCK)
{
	return GenDCK(pDCK,MAX_DCK_LENGTH);
}

BOOL GetValueFromHexString(CString HexString, byte* pValue)
{
	char *pBuffer = NULL;
	UINT i,nLen = 0;
	UINT tmpValue=0;

	if(HexString.IsEmpty() || pValue == NULL)
	{
		return FALSE;
	}
	nLen = HexString.GetLength();
	if(nLen > 2)
	{
		return FALSE;
	}

	pBuffer = HexString.GetBuffer(0);
	for(i=0; i<nLen; i++)
	{
		if(!((pBuffer[i]>='0' && pBuffer[i]<='9')
			||(pBuffer[i]>='a' && pBuffer[i]<='f')
			||(pBuffer[i]>='A' && pBuffer[i]<='F')))
		{
			return FALSE;
		}
	}
	sscanf(pBuffer,"%x",&tmpValue);
	*pValue = tmpValue;
	return TRUE;
}

BOOL IMEIInc(char* pIMEI)
{
	UINT nIMEILast6D = 0;
	if(IsIMEIString(pIMEI) == FALSE)
	{
		return FALSE;
	}

	nIMEILast6D = strtoul(pIMEI+8, NULL, 10);
	if(nIMEILast6D != 999999)
	{
		nIMEILast6D ++;
		sprintf(pIMEI+8,"%06u",nIMEILast6D);
	}
	return TRUE;
}

BOOL IMEIDec(char* pIMEI)
{
	UINT nIMEILast6D = 0;
	if(IsIMEIString(pIMEI) == FALSE)
	{
		return FALSE;
	}

	nIMEILast6D = strtoul(pIMEI+8, NULL, 10);
	if(nIMEILast6D != 0)
	{
		nIMEILast6D --;
		sprintf(pIMEI+8,"%06u",nIMEILast6D);
	}
	return TRUE;
}

BOOL BTAddressInc(char* pBTAddress)
{
	UINT nBTAddrLast6D = 0;
	if(IsBTAddrString(pBTAddress) == FALSE)
	{
		return FALSE;
	}

	nBTAddrLast6D = strtoul(pBTAddress+6, NULL, 16);
	if(nBTAddrLast6D != 0xFFFFFF)
	{
		nBTAddrLast6D ++;
		sprintf(pBTAddress+6,"%06x",nBTAddrLast6D);
	}
	return TRUE;
}

BOOL BTAddressDec(char* pBTAddress)
{
	UINT nBTAddrLast6D = 0;
	if(IsBTAddrString(pBTAddress) == FALSE)
	{
		return FALSE;
	}

	nBTAddrLast6D = strtoul(pBTAddress+6, NULL, 16);
	if(nBTAddrLast6D != 0)
	{
		nBTAddrLast6D --;
		sprintf(pBTAddress+6,"%06x",nBTAddrLast6D);
	}
	return TRUE;
}


BOOL ESNInc(char* pESN)
{
	UINT nESNLast6D = 0;
	if(IsESNString(pESN) == FALSE)
	{
		return FALSE;
	}
	
	nESNLast6D = strtoul(pESN+3, NULL, 16);
	if(nESNLast6D != 0xFFFFFF)
	{
		nESNLast6D ++;
		sprintf(pESN+3,"%05x",nESNLast6D);
	}
	return TRUE;
}

BOOL ESNDec(char* pESN)
{
	UINT nESNLast6D = 0;
	if(IsESNString(pESN) == FALSE)
	{
		return FALSE;
	}
	
	nESNLast6D = strtoul(pESN+3, NULL, 16);
	if(nESNLast6D != 0)
	{
		nESNLast6D --;
		sprintf(pESN+3,"%05x",nESNLast6D);
	}
	return TRUE;
}


BOOL MEIDInc(char* pMEID)
{
	UINT nMEIDLast6D = 0;
	if(IsMEIDString(pMEID) == FALSE)
	{
		return FALSE;
	}
	
	nMEIDLast6D = strtoul(pMEID+8, NULL, 16);
	if(nMEIDLast6D != 0xFFFFFF)
	{
		nMEIDLast6D ++;
		sprintf(pMEID+8,"%06x",nMEIDLast6D);
	}
	return TRUE;
}

BOOL MEIDDec(char* pMEID)
{
	UINT nMEIDLast6D = 0;
	if(IsMEIDString(pMEID) == FALSE)
	{
		return FALSE;
	}
	
	nMEIDLast6D = strtoul(pMEID+8, NULL, 16);
	if(nMEIDLast6D != 0)
	{
		nMEIDLast6D --;
		sprintf(pMEID+8,"%06x",nMEIDLast6D);
	}
	return TRUE;
}

BOOL SetupComPort()
{
	if(gComPortInfo.bIsOpen == TRUE)
	{
		return TRUE;
	}

	if(gComPortInfo.bIsConnect == FALSE)
	{
		return FALSE;
	}

	if(InitSerialPort(gComPortInfo.ComID) == FALSE)
	{
		return FALSE;
	}
	gComPortInfo.bIsOpen = TRUE;
	EnableComboBox(FALSE);

	return TRUE;
}

BOOL CloseComPort()
{
	if(gComPortInfo.bIsOpen == FALSE)
	{
		return TRUE;
	}
	
	if(CloseSerialPort(gComPortInfo.ComID) == FALSE)
	{
		return FALSE;
	}
	gComPortInfo.bIsOpen = FALSE;
	EnableComboBox(TRUE);

	return TRUE;
}

//Set Param of Server
BOOL SetServerParam()
{
	return SetServerParam(gComPortInfo.ComID, gIPAddress, gProjectName);
}

BOOL IsGozoneMEID(char* string,UINT* pOffsetToBaseMEID)
{
	/*
	__int64 GozoneMEID = 0;
	__int64 MinMEID = 0;
	__int64 MaxMEID = 0;

	sscanf(CfgMinMEID,"%I64x",&MinMEID);
	sscanf(CfgMaxMEID,"%I64x",&MaxMEID);
	sscanf(string,"%I64x",&GozoneMEID);

	if (GozoneMEID<MinMEID || GozoneMEID>MaxMEID)
		return FALSE;

#if 0	//[zhangjj,maybe enable in crv,100707]
	if ((GozoneMEID-MinMEID) >= (800*1024))	// 限制产能800K
		return FALSE;
#endif
	
	if (pOffsetToBaseMEID==NULL)
		return FALSE;
	
	*pOffsetToBaseMEID = (UINT)(GozoneMEID-MinMEID);
	*/
	return TRUE;
}


BOOL IsGozoneBtAddr(UINT OffsetToBaseBTAddr, char* string)
{
	/*
	__int64 GozoneBTAddr = 0;
	__int64 MinBtAddr = 0;
	__int64 MaxBtAddr = 0;
	
	sscanf(CfgMinBtAddress,"%I64x",&MinBtAddr);
	sscanf(CfgMaxBtAddress,"%I64x",&MaxBtAddr);
	
	GozoneBTAddr = MinBtAddr+OffsetToBaseBTAddr;
	
	if (string==NULL || GozoneBTAddr<MinBtAddr || GozoneBTAddr>MaxBtAddr)
		return FALSE;
	
	sprintf(string,"%.12I64x",GozoneBTAddr);
	*/
	return TRUE;
}


BOOL IsGozoneEsn(char* string,UINT* pOffsetToBaseEsn)
{
	/*
	__int64 GozoneESN = 0;
	__int64 MinESN = 0;
	__int64 MaxESN = 0;

	sscanf(CfgMinESN,"%I64x",&MinESN);
	sscanf(CfgMaxESN,"%I64x",&MaxESN);
	sscanf(string,"%I64x",&GozoneESN);

	if (GozoneESN<MinESN || GozoneESN>MaxESN)
		return FALSE;

#if 0	//[zhangjj,maybe enable in crv,100707]
	if ((GozoneMEID-MinMEID) >= (800*1024))	// 限制产能800K
		return FALSE;
#endif

#if 0	//[zhangjj,ESN暂时没用此offset,101014]
	if (pOffsetToBaseMEID==NULL)
		return FALSE;

	*pOffsetToBaseMEID = (UINT)(GozoneMEID-MinMEID);
#endif
*/
	return TRUE;
}

BOOL AddToTrackFile(CString Info)
{
	char FullName[MAX_PATH+1] = {0};
	FILE *stream = NULL;
	
	// 修改文件名为日期格式,若存在该文件就追加,若没有就创建
	char realFileName[128] = {0};
	char dbuffer[9] = {0};
	_strdate( dbuffer ); // "12/19/08"
#if 0	
	
	strcpy(realFileName, "20");
	memcpy(&realFileName[2], &dbuffer[6], 2);	// year "08" or "09"
	memcpy(&realFileName[4], &dbuffer[0], 2);	// month "12"
	memcpy(&realFileName[6], &dbuffer[3], 2);	// month "12"
	
	strcat(realFileName, "_");
	strcat(realFileName,WRITE_TOOL_TRACK_FILE);
	
	if(GetFileFullName(FullName,realFileName))
#else
		if(GetFileFullName(FullName,WRITE_TOOL_TRACK_FILE))
#endif
		{
			if ((stream = fopen(FullName,"r+")) == NULL)
			{
				if ((stream = fopen(FullName,"a+")) == NULL)
				{
					return FALSE;
				}
			}
			
			fseek(stream, 0, SEEK_END);
			fprintf(stream, "%s", Info);
			fclose(stream);
		}
		
		return TRUE;
}

BOOL IsStrInTrackFile(CString Str)
{
	char FullName[MAX_PATH+1] = {0};
	FILE *stream = NULL;
	char *pList = NULL;
	UINT fileLen = 0;

	if(GetFileFullName(FullName,WRITE_TOOL_TRACK_FILE))
	{
		if ((stream = fopen(FullName,"r")) == NULL)
		{
			return FALSE;
		}
		
		fseek(stream, 0, SEEK_END);
		fileLen = ftell(stream);
		pList = (char*)malloc(fileLen+1);

		fseek(stream,0,SEEK_SET);
		fread(pList,sizeof(char),fileLen,stream);

		if (strstr(pList,Str))
		{
			free(pList);
			fclose(stream);
			return FALSE;
		}

		free(pList);
		fclose(stream);
	}

	return TRUE;
}

BOOL GetFileFullName(char *pFileFullName, char *FileName)
{
	UINT nLen = 0;
	int i;
	
	GetModuleFileName(NULL,pFileFullName,MAX_PATH);
	nLen = strlen(pFileFullName);
	if(nLen == 0)
	{
		return FALSE;
	}
	
	for(i=nLen-1; i>=0; i--)
	{
		if(pFileFullName[i] == '\\')
		{
			pFileFullName[i+1] = 0;
			strcat(pFileFullName,FileName);
			return TRUE;
		}
	}
	return FALSE;
	
}
