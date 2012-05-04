#include "stdafx.h"
#include "DllParam.h"
#include "SetNVParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define INDEX_PORT	128
CSetNVParam SetNVParam[INDEX_PORT];
UINT uIndexPort[INDEX_PORT] = { 0 };


static int SetQueue(UINT nSerialPort);
static int GetQueue(UINT nSerialPort);

static int SetQueue(UINT nSerialPort)
{
	if (0 == nSerialPort)
		return -1;

	for (int i = 0; i < INDEX_PORT; i++)
	{
		if (uIndexPort[i] == 0)				// 数组的空白位置
		{
			uIndexPort[i] = nSerialPort;
			return i;
		}

		if (uIndexPort[i] == nSerialPort)	// 相同的串口号
		return i;
	}
	return -1;								// 超过最大限制
}

static int GetQueue(UINT nSerialPort)
{
	if (nSerialPort == 0 )
		return -1;

	for (int i = 0; i < INDEX_PORT; i++)
	{
		if (uIndexPort[i] == nSerialPort)	// 是否存在该串口
		return i;
	}
	return -1;
}

/*
 *	serial port
 */
BOOL InitSerialPort(UINT nSerialPort) 
{
    int nIndex = SetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].InitSerialPort(nSerialPort))
        return FALSE;

    return TRUE;
}
BOOL CloseSerialPort(UINT nSerialPort) 
{
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].CloseSerialPort())
        return FALSE;

    return TRUE;
}

INT  SPCRequest(UINT nSerialPort, char *pszSPC)
{
	int nIndex = GetQueue(nSerialPort);
	if (-1 == nIndex)
		return FALSE;

	int nResult = SetNVParam[nIndex].SPCRequest(pszSPC);

	return nResult;
}

/*
 *	针对OTP的
 */
// opt_version
BOOL Read_OTP_Version(UINT nSerialPort, OTP_Version *pOTPVersion)
{
	if(pOTPVersion == NULL)
	{
		return FALSE;
	}

    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].Read_OTP_Version(pOTPVersion))
        return FALSE;

    return TRUE;
}
BOOL Write_OTP_Version(UINT nSerialPort, OTP_Version *pOTPVersion)
{
	if(pOTPVersion == NULL)
	{
		return FALSE;
	}

    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].Write_OTP_Version(pOTPVersion))
        return FALSE;
    
    return TRUE;
}

// opt_imei
BOOL Read_OTP_IMEI(UINT nSerialPort, OTP_IMEI *pOTPImei)
{
	if(pOTPImei == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Read_OTP_IMEI(pOTPImei))
        return FALSE;
	
    return TRUE;
}
BOOL Write_OTP_IMEI(UINT nSerialPort, OTP_IMEI *pOTPImei)
{
	if(pOTPImei == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Write_OTP_IMEI(pOTPImei))
        return FALSE;
    
    return TRUE;
}

BOOL Write_OTP_IMEI2(UINT nSerialPort, OTP_IMEI2 *pOTPImei)
{
	if(pOTPImei == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Write_OTP_IMEI2(pOTPImei))
        return FALSE;
    
    return TRUE;
}


// opt_bluetoothaddr
BOOL Read_OTP_BlueToothAddr(UINT nSerialPort, OTP_BlueToothAddr *pOTPBluetoothaddr)
{
	if(pOTPBluetoothaddr == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Read_OTP_BlueToothAddr(pOTPBluetoothaddr))
        return FALSE;
	
    return TRUE;
}
BOOL Write_OTP_BlueToothAddr(UINT nSerialPort, OTP_BlueToothAddr *pOTPBluetoothaddr)
{
	if(pOTPBluetoothaddr == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Write_OTP_BlueToothAddr(pOTPBluetoothaddr))
        return FALSE;
    
    return TRUE;
}

// opt_hash
BOOL Read_OTP_HASH(UINT nSerialPort, OTP_Hash *pOTPHash)
{
	if(pOTPHash == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Read_OTP_HASH(pOTPHash))
        return FALSE;
	
    return TRUE;
}
BOOL Write_OTP_HASH(UINT nSerialPort, OTP_Hash *pOTPHash)
{
	if(pOTPHash == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Write_OTP_HASH(pOTPHash))
        return FALSE;
    
    return TRUE;
}

// opt_plmn
BOOL Read_OTP_PLMN(UINT nSerialPort, OTP_Plmn *pOTPPlmn)
{
	if(pOTPPlmn == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Read_OTP_PLMN(pOTPPlmn))
        return FALSE;
	
    return TRUE;
}
BOOL Write_OTP_PLMN(UINT nSerialPort, OTP_Plmn *pOTPPlmn)
{
	if(pOTPPlmn == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Write_OTP_PLMN(pOTPPlmn))
        return FALSE;
    
    return TRUE;
}

// opt_hash
BOOL Read_OTP_FLAG(UINT nSerialPort, OTP_ReadWrite *pOTPReadwrite)
{
	if(pOTPReadwrite == NULL)
	{
		return FALSE;
	}
	int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].Read_OTP_FLAG(pOTPReadwrite))
        return FALSE;

    return TRUE;
}
BOOL Write_OTP_FLAG(UINT nSerialPort, OTP_ReadWrite *pOTPReadwrite)
{
	if(pOTPReadwrite == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].Write_OTP_FLAG(pOTPReadwrite))
        return FALSE;

    return TRUE;
}

BOOL Read_OTP_SIMLockInfo(UINT nSerialPort, OTP_SIMLockInfo *pOTPSimlockinfo)
{
	if(pOTPSimlockinfo == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].Read_OTP_SIMLockInfo(pOTPSimlockinfo))
        return FALSE;

    return TRUE;
}
BOOL Write_OTP_SIMLockInfo(UINT nSerialPort, OTP_SIMLockInfo *pOTPSimlockinfo)
{
	if(pOTPSimlockinfo == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].Write_OTP_SIMLockInfo(pOTPSimlockinfo))
        return FALSE;

    return TRUE;
}
BOOL Read_OTP_PublicKey(UINT nSerialPort, OTP_PublicKey *pOTPPublickey)
{
	if(pOTPPublickey == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].Read_OTP_PublicKey(pOTPPublickey))
        return FALSE;

    return TRUE;
}

BOOL Write_OTP_PublicKey(UINT nSerialPort, OTP_PublicKey *pOTPPublickey)
{
	if(pOTPPublickey == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].Write_OTP_PublicKey(pOTPPublickey))
        return FALSE;

    return TRUE;
}

BOOL TurnOnSimLockSwitch(UINT nSerialPort, OTP_SimLockSwitch *pOTPSimLockSwitch)
{
	if(pOTPSimLockSwitch == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].TurnOnSimLockSwitch(pOTPSimLockSwitch))
        return FALSE;

    return TRUE;
}
BOOL TurnOffSimLockSwitch(UINT nSerialPort, OTP_SimLockSwitch *pOTPSimLockSwitch)
{
	if(pOTPSimLockSwitch == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].TurnOffSimLockSwitch(pOTPSimLockSwitch))
        return FALSE;

    return TRUE;
}
BOOL TurnOnEngineeringSwitch(UINT nSerialPort, OTP_EngineeringSwitch *pOTPEnginswitch)
{
	if(pOTPEnginswitch == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].TurnOnEngineeringSwitch(pOTPEnginswitch))
        return FALSE;

    return TRUE;
}
BOOL TurnOffEngineeringSwitch(UINT nSerialPort, OTP_EngineeringSwitch *pOTPEnginswitch)
{
	if(pOTPEnginswitch == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].TurnOffEngineeringSwitch(pOTPEnginswitch))
        return FALSE;

    return TRUE;
}
BOOL Read_NVItmesPack(UINT nSerialPort, NVItemsPack *pNVItemsPack)
{
	if(pNVItemsPack == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].Read_NVItmesPack(GOZONE_NV_EXPORT,pNVItemsPack))
        return FALSE;

    return TRUE;
}
BOOL Write_NVItmesPack(UINT nSerialPort, NVItemsPack *pNVItemsPack)
{
	if(pNVItemsPack == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;

    if (!SetNVParam[nIndex].Write_NVItmesPack(GOZONE_NV_IMPORT,pNVItemsPack))
        return FALSE;

    return TRUE;
}
INT ExportAllNVItemsFromPhone(UINT nSerialPort, byte DataBuf[], UINT *pActualBufLenth)
{
	if(pActualBufLenth == NULL)
	{
		return -1;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return -1;

    return SetNVParam[nIndex].ExportAllNVItemsFromPhone(DataBuf, pActualBufLenth);
}

INT ImportAllNVItemsIntoPhone(UINT nSerialPort, byte DataBuf[], UINT ActualDataSize)
{
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return OPTISER_FAILURE;

    return SetNVParam[nIndex].ImportAllNVItemsIntoPhone(DataBuf, ActualDataSize);
}

#if 0 //[zhangjj, 070612,del for auto sign]
BOOL SignNVParam(UINT nSerialPort)
{
	int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return OPTISER_FAILURE;

	return SetNVParam[nIndex].SignNVParam(nSerialPort);
}
#endif
BOOL SetServerParam(UINT nSerialPort,char szIPAddr[],char szProjectName[])
{
	int nIndex = GetQueue(nSerialPort);
	if (-1 == nIndex)
		return OPTISER_FAILURE;

	return SetNVParam[nIndex].SetServerParam(szIPAddr, szProjectName);
}

BOOL Get_HDET_OFF(UINT nSerialPort, char *pHdetOff)
{
	if(pHdetOff == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return OPTISER_FAILURE;

    return SetNVParam[nIndex].Get_HDET_OFF(pHdetOff);
}
 
BOOL Get_HDET_SPN(UINT nSerialPort, char *pHdetSpn)
{
	if(pHdetSpn == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return OPTISER_FAILURE;

    return SetNVParam[nIndex].Get_HDET_SPN(pHdetSpn);
}

BOOL ErasureOTP(UINT nSerialPort)
{
	int nIndex = GetQueue(nSerialPort);
	if (-1 == nIndex)
		return OPTISER_FAILURE;
	
	return SetNVParam[nIndex].ErasureOTP();
}

// 从hashdck.dll中再封装HashDck函数
BOOL CheckHashValue(byte byteHash[], UINT nHashLenth, byte byteDataStr[], UINT nDataStrLenth)
{
#if 0	// zhangjj del hashdck.dll
	byte byteCaculatedHashValue[32] = {0};
	UINT nCaculatedHashLenth = 0;

	HINSTANCE hInst = LoadLibrary("hashdck.dll");
	if (NULL == hInst)
		return OPTISER_FAILURE;
	
	TProcHashDck HashDck;
	HashDck = (TProcHashDck)GetProcAddress(hInst, PROC_HASH_DCK); 
	if (NULL == HashDck)
	{
		FreeLibrary(hInst);					
		hInst = NULL;						
		return OPTISER_FAILURE;
	}
	
	if (!HashDck(byteDataStr, nDataStrLenth, byteCaculatedHashValue, &nCaculatedHashLenth))
		return OPTISER_FAILURE;

	if (nCaculatedHashLenth == 0)
		return OPTISER_FAILURE;

	if (nHashLenth != nCaculatedHashLenth)
		return OPTISER_FAILURE;

	for (UINT i = 0; i < nCaculatedHashLenth; i++)
	{
		if (byteHash[i] != byteCaculatedHashValue[i])
			return OPTISER_FAILURE;
	}

	return OPTISER_SUCCESS;
#else
	return OPTISER_FAILURE;
#endif
 }

BOOL GenDCK(char szDCK[], UINT nLenth)
{
	UINT i;
	int random;
	
	time_t nSeed1;
	
	//START=======Generate nSeed0=======
	static time_t nSeed0 = 0;
	
	if (nSeed0 == 0)
	{
		for (i = 0; i < 3; i++)
		{
			nSeed0 = time(NULL);
			if (nSeed0 != -1)
				break;
		}

		if (i >= 3)
			return FALSE;
	}
	else
	{
		srand ((unsigned)nSeed0);
		nSeed0 = (time_t)rand();
	}
	//END========Generate nSeed0=========

	//START======Generate nSeed1=========
	for (i = 0; i < 3; i++)
	{
		nSeed1 = time(NULL);
		if (nSeed1 != -1)
			break;
	}
	if (i >= 3)
		return FALSE;
	//END=======Generate nSeed1==========

	srand((UINT)( (UINT)nSeed0+(UINT)nSeed1 ));
	for (i = 0; i < nLenth; i++)
	{
		random = rand();
		random %= 10;
		szDCK[i] = (unsigned)random + '0';
	}

	return TRUE;
}

BOOL HashDck(UCHAR *inData, UINT inLen, UCHAR *outData, UINT *poutLen)
{
#if 0	// zhangjj del hashdck.dll
	HINSTANCE hInst = LoadLibrary("hashdck.dll");
	if (NULL == hInst)
		return FALSE;

    PHashDck HashDck;
    HashDck = (PHashDck)GetProcAddress(hInst, "HashDck"); 
	if (NULL == HashDck)
	{
		FreeLibrary(hInst);
		return FALSE;
	}

    if (!HashDck(inData, inLen, outData, poutLen))
	{
		FreeLibrary(hInst);
		return FALSE;
    }

	if (0 == *poutLen)
	{
		FreeLibrary(hInst);
		return FALSE;
	}

	FreeLibrary(hInst);
	return TRUE;
#else
	return FALSE;
#endif
}

BOOL Read_Random_Data(UINT nSerialPort, TRandom *pRandomData)
{
	if(pRandomData == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Read_Random_Data(pRandomData))
        return FALSE;
	
    return TRUE;
}

BOOL Test_Sign_Client(UINT nSerialPort)
{
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    return SetNVParam[nIndex].Test_Sign_Client();
}

// opt_esn
BOOL Read_OTP_ESN(UINT nSerialPort, OTP_ESN *pOTPEsn)
{
	if(pOTPEsn == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Read_OTP_ESN(pOTPEsn))
        return FALSE;
	
    return TRUE;
}
BOOL Write_OTP_ESN(UINT nSerialPort, OTP_ESN *pOTPEsn)
{
	if(pOTPEsn == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Write_OTP_ESN(pOTPEsn))
        return FALSE;
    
    return TRUE;
}


BOOL CmdNVBackup(UINT nSerialPort, OTP_NVBackupRestore *pOTPNVBackupRestore)
{
	if(pOTPNVBackupRestore == NULL)
	{
		return FALSE;
	}
	
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].CmdNVBackup(pOTPNVBackupRestore))
        return FALSE;
	
    return TRUE;
}

BOOL CmdNVRestore(UINT nSerialPort, OTP_NVBackupRestore *pOTPNVBackupRestore)
{
	if(pOTPNVBackupRestore == NULL)
	{
		return FALSE;
	}

    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].CmdNVRestore(pOTPNVBackupRestore))
        return FALSE;
	
    return TRUE;
}


BOOL Read_OTP_MEID(UINT nSerialPort, OTP_MEID *pOTPMeid)
{
	if(pOTPMeid == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Read_OTP_MEID(pOTPMeid))
        return FALSE;
	
    return TRUE;
}
BOOL Write_OTP_MEID(UINT nSerialPort, OTP_MEID *pOTPMeid)
{
	if(pOTPMeid == NULL)
	{
		return FALSE;
	}
    int nIndex = GetQueue(nSerialPort);
    if (-1 == nIndex)
        return FALSE;
	
    if (!SetNVParam[nIndex].Write_OTP_MEID(pOTPMeid))
        return FALSE;
    
    return TRUE;
}

