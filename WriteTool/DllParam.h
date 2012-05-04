#ifndef __DLLPARAM_H__
#define __DLLPARAM_H__

#ifdef __cplusplus
extern "C" {
#endif

#define GOZONE_IP_ADDRESS_SIZE		20		//IP地址长度
#define GOZONE_PRJECT_NAME_SIZE		32		//项目名称最大长度
#define GOZONE_VERSION_SIZE			64		//版本长度
#define GOZONE_BT_ADDRESS_SIZE		6		//蓝牙地址长度
#define GOZONE_IMEI_SIZE			9		//IMEI号长度
#define GOZONE_PLMNLIST_LEN			20		//最大支持20组PLMN
#define GOZONE_DCKHASH_LEN			20		//DCK的HASH值长度
#define GOZONE_PUBLICKEY_LEN		80		//PublicKey长度,实际只使用到74个字节
#define NV_PACK_MAX_DATA_SIZE		120
#define GOZONE_RANDOM_LEN			20		//签名用的随机数长度
#define GOZONE_ESN_SIZE				4		//ESN号长度
#define GOZONE_MEID_SIZE			8		//MEID长度

typedef struct tagCommomInfo            // 写的时候这个元素可以不考虑
{
	BOOL	bValid;
	INT		nResCmd;
	INT		nStatus;
}CommonInfo;

typedef struct tagOTP_Version
{
	CommonInfo  structCommonInfo;
	char        szVersion[GOZONE_VERSION_SIZE];
}OTP_Version;

typedef struct tagOTP_IMEI
{
	CommonInfo  structCommonInfo;
	char        szIMEI[GOZONE_IMEI_SIZE*2+1];
}OTP_IMEI;

typedef struct tagOTP_IMEI2
{
	CommonInfo  structCommonInfo;
	char		szIMEI2[GOZONE_IMEI_SIZE*2+1];
}OTP_IMEI2;

typedef struct tagOTP_BlueToothAddress
{
	CommonInfo  structCommonInfo;
	char        szBlueToothAddr[GOZONE_BT_ADDRESS_SIZE*2+1];
}OTP_BlueToothAddr;

typedef struct tagOTP_Hash
{
	CommonInfo  structCommonInfo;
	byte		byteHash[GOZONE_DCKHASH_LEN];
}OTP_Hash;

typedef struct tagOTP_Plmn
{
	CommonInfo  structCommonInfo;
	byte		bytePlmn[GOZONE_PLMNLIST_LEN][3];
	byte		CountryCode[2];
}OTP_Plmn;

typedef struct tagOTP_ReadWrite
{
	CommonInfo  structCommonInfo;
}OTP_ReadWrite;

typedef struct tagOTP_PublicKey
{
	CommonInfo  structCommonInfo;
	byte bytePublicKey[GOZONE_PUBLICKEY_LEN];
}OTP_PublicKey;

typedef struct tagOTP_SIMLockInfo
{
	CommonInfo  structCommonInfo;
	byte byteLockStatus;				/* The status of the key lock.The type is 'TSimLockLockStatus' */
	byte byteSequenceAttemptsLeft;		/* The number of sequence attempts left unlocking the key lock. */
	byte byteIntervalAttemptsLeft; 		/* The number of interval attempts left unlocking the key lock. */
	byte byteHoursLeft;					/* Hours left on running timer. */
	byte byteMinutesLeft;				/* Minutes left on running timer. */
	byte byteSecondsLeft;				/* Seconds left on running timer. */
}OTP_SIMLockInfo;

typedef struct tagOTP_SimLockSwitch
{
	CommonInfo  structCommonInfo;
}OTP_SimLockSwitch;

typedef struct tagOTP_EngineeringSwitch
{
	CommonInfo  structCommonInfo;
}OTP_EngineeringSwitch;

typedef struct tagNVItemsPack
{
	CommonInfo  structCommonInfo;
	UINT	TotalPack;
	UINT	CurrPack;
	byte	len;
	byte	data[NV_PACK_MAX_DATA_SIZE];
}NVItemsPack;

typedef struct tagRandomData
{
	CommonInfo  structCommonInfo;
	byte		byteRandom[GOZONE_RANDOM_LEN];
}TRandom;

typedef struct tagOTP_ESN
{
	CommonInfo  structCommonInfo;
	char        szESN[GOZONE_ESN_SIZE*2+1];
	char        szESNCheckSum[GOZONE_ESN_SIZE*2+1];
}OTP_ESN;

typedef struct tagNVBackupRestore
{
	CommonInfo  structCommonInfo;
}OTP_NVBackupRestore;

typedef struct tagOTP_MEID
{
	CommonInfo  structCommonInfo;
	char        szMEID[GOZONE_MEID_SIZE*2+1];
}OTP_MEID;

typedef struct tagPortInfo PortInfo;

struct tagPortInfo 
{
    UINT nIndexSetNVParamEx;     // 该模块的第几个实例
    UINT nSerialPort;            // 该模块用第几个串口
};

BOOL InitSerialPort(UINT nSerialPort);
BOOL CloseSerialPort(UINT nSerialPort);
INT  SPCRequest(UINT nSerialPort, char *pszSPC);
BOOL Read_OTP_Version(UINT nSerialPort, OTP_Version *pOTPVersion);
BOOL Write_OTP_Version(UINT nSerialPort, OTP_Version *pOTPVersion);
BOOL Read_OTP_IMEI(UINT nSerialPort, OTP_IMEI *pOTPImei);
BOOL Write_OTP_IMEI(UINT nSerialPort, OTP_IMEI *pOTPImei);
BOOL Write_OTP_IMEI2(UINT nSerialPort, OTP_IMEI2 *pOTPImei);

BOOL Read_OTP_BlueToothAddr(UINT nSerialPort, OTP_BlueToothAddr *pOTPBluetoothaddr);
BOOL Write_OTP_BlueToothAddr(UINT nSerialPort, OTP_BlueToothAddr *pOTPBluetoothaddr);
BOOL Read_OTP_HASH(UINT nSerialPort, OTP_Hash *pOTPHash);
BOOL Write_OTP_HASH(UINT nSerialPort, OTP_Hash *pOTPHash);
BOOL Read_OTP_PLMN(UINT nSerialPort, OTP_Plmn *pOTPPlmn);
BOOL Write_OTP_PLMN(UINT nSerialPort, OTP_Plmn *pOTPPlmn);
BOOL Read_OTP_FLAG(UINT nSerialPort, OTP_ReadWrite *pOTPReadwrite);
BOOL Write_OTP_FLAG(UINT nSerialPort, OTP_ReadWrite *pOTPReadwrite);
BOOL Read_OTP_SIMLockInfo(UINT nSerialPort, OTP_SIMLockInfo *pOTPSimlockinfo);
BOOL Write_OTP_SIMLockInfo(UINT nSerialPort, OTP_SIMLockInfo *pOTPSimlockinfo);
BOOL Read_OTP_PublicKey(UINT nSerialPort, OTP_PublicKey *pOTPPublickey);
BOOL Write_OTP_PublicKey(UINT nSerialPort, OTP_PublicKey *pOTPPublickey);
BOOL TurnOnSimLockSwitch(UINT nSerialPort, OTP_SimLockSwitch *pOTPSimLockSwitch);
BOOL TurnOffSimLockSwitch(UINT nSerialPort, OTP_SimLockSwitch *pOTPSimLockSwitch);
BOOL TurnOnEngineeringSwitch(UINT nSerialPort, OTP_EngineeringSwitch *pOTPEnginswitch);
BOOL TurnOffEngineeringSwitch(UINT nSerialPort, OTP_EngineeringSwitch *pOTPEnginswitch);
BOOL Read_NVItmesPack(UINT nSerialPort, NVItemsPack *pNVItemsPack);
BOOL Write_NVItmesPack(UINT nSerialPort, NVItemsPack *pNVItemsPack);
INT ExportAllNVItemsFromPhone(UINT nSerialPort, byte DataBuf[], UINT *pActualBufLenth);
INT ImportAllNVItemsIntoPhone(UINT nSerialPort, byte DataBuf[], UINT ActualDataSize);
BOOL SetServerParam(UINT nSerialPort,char szIPAddr[],char szProjectName[]);
BOOL Get_HDET_OFF(UINT nSerialPort, char *pHdetOff);
BOOL Get_HDET_SPN(UINT nSerialPort, char *pHdetSpn);
BOOL ErasureOTP(UINT nSerialPort);
BOOL CheckHashValue(byte byteHash[], UINT nHashLenth, byte byteDataStr[], UINT nDataStrLenth);
BOOL GenDCK(char szDCK[], UINT nLenth);
BOOL HashDck(UCHAR *inData, UINT inLen, UCHAR *outData, UINT *poutLen);
BOOL Read_Random_Data(UINT nSerialPort, TRandom *pRandomData);
BOOL Test_Sign_Client(UINT nSerialPort);
BOOL Read_OTP_ESN(UINT nSerialPort, OTP_ESN *pOTPEsn);
BOOL Write_OTP_ESN(UINT nSerialPort, OTP_ESN *pOTPEsn);
BOOL CmdNVBackup(UINT nSerialPort, OTP_NVBackupRestore *pOTPNVBackupRestore);
BOOL CmdNVRestore(UINT nSerialPort, OTP_NVBackupRestore *pOTPNVBackupRestore);
BOOL Read_OTP_MEID(UINT nSerialPort, OTP_MEID *pOTPMeid);
BOOL Write_OTP_MEID(UINT nSerialPort, OTP_MEID *pOTPMeid);

#ifdef __cplusplus
}
#endif

#endif // __DLLPARAM_H__
