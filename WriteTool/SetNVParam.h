/*
File: SetNVParam.h
Desc: 

Author: zjj
Date  : 2007.3.14
Notes : CSetNVParam类的定义

   $Source: D:/cvsrepo/DllParam/SetNVParam.h,v $

$Log: SetNVParam.h,v $
Revision 1.1.1.8  2008/03/04 09:46:51  zhangjj
增加陈燕绿修改的NV备份恢复命令

Revision 1.1.1.7  2007/11/16 06:31:55  zhangjj
增加ESN读写接口，兼容联通规范。

Revision 1.1.1.6  2007/10/11 07:46:33  zhangjj
增加测试是否能连接服务器签名

Revision 1.1.1.5  2007/10/11 01:35:25  zhangjj

补充提交没有放在debug分支的错误

Revision 1.2  2007/10/11 01:23:02  zhangjj
OTP锁定前强制网络数据签名,避免锁OTP后由于签名数据为0造成的锁卡

Revision 1.1.1.4  2007/06/13 02:34:48  zhangjj
保留写public key接口,关闭该功能由手机端保证.
锁网--开关simlock和写plmn时自动去服务器签名,
不用手动签名---和手机、writetool同步

Revision 1.1.1.3  2007/04/26 06:12:05  zhangjj
删除pc端写public key的功能

Revision 1.1.1.2  2007/03/27 01:39:52  zhangjj
读取随机数来签名

Revision 1.1.1.1  2007/03/14 07:26:48  zhangjj
导入初始版本


*/

#if !defined(AFX_SETNVPARAM_H__87125966_4158_4903_98F3_E82A5BBF88EA__INCLUDED_)
#define AFX_SETNVPARAM_H__87125966_4158_4903_98F3_E82A5BBF88EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ItemTable.h"
#include "SerialPort.h"
#include "DllParam.h"

#define BYTE_DATA_LEN               128
#define BUFFER_SIZE                 512
#define SORTSINDEXBEGIN_NV          0
#define SORTSINDEXEND_NV            52

#define GOZONE_OTP_EXTERN_ITEM	0x7fff
typedef enum
{
#if 1
	GOZONE_VERSION,				/* 软件版本号的查询 */
	GOZONE_NV_BACKUP,				/* NV的备份 */
	GOZONE_NV_RESTORE,			/* NV的恢复*/
	GOZONE_IMEI_READ,				/* IMEI号的读取 */
	GOZONE_IMEI_WRITE,			/* IMEI号的写入 */
	GOZONE_BTADD_READ,			/* 蓝牙地址的读取 */
	GOZONE_BTADD_WRITE,			/* 蓝牙地址的写入*/
	GOZONE_DCK_READ,				/* DCK数据的读取 */
	GOZONE_DCK_WRITE,				/* DCK数据的写入 */
	GOZONE_PLMN_READ,				/* PLMN数据的读取 */
	GOZONE_PLMN_WRITE,			/* PLMN数据的写入 */
	GOZONE_NCK_READ,				/* simlock info 的读取*/
	GOZONE_NCK_WRITE,				/* simlock info 的写入 */
	GOZONE_NV_IMPORT,				/* NV的导入 */
	GOZONE_NV_EXPORT,				/* NV的导出 */
	GOZONE_OTP_LOCK,				/* 锁定OTP数据 */
	GOZONE_USIM_SWITCH,			/* 修改Usim Switch 的状态 */
	GOZONE_ENGINEERING_SWITCH, 	/* 修改Engineering Switch 的状态 */
	GOZONE_BLUETOOTH_CHECKOUT,	/* 修改Bluetooth Checkout 的状态 */
	GOZONE_NV_CHECKOUT,			/* 修改NV Checkout 的状态 */
	GOZONE_PUBLICKEY_READ,		/* Public key 的读取 */
	GOZONE_PUBLICKEY_WRITE,		/* Public key 的写入 */
	GOZONE_ORIUNDERWRITEDATA,		/* 读取需要签名的原始数据 */
	GOZONE_UNDERWRITEDATA_READ,	/* Underwrite data 的读取*/
	GOZONE_UNDERWRITEDATA_WRITE,	/* Underwrite data 的写入*/
	GOZONE_WRITINGREQUEST,		/* 向手机端发送写请求, 允许之后才能将数据写入Flash */
	GOZONE_ERASUREOTP,
	#if 0
	GOZONE_ERASURE_OTP,			/* 擦除OTP数据 */
	#endif
	GOZONE_PHONEID_READ,			/* 签名数据的安全码的读取 */
	GOZONE_PHONEID_WRITE,			/* 签名数据的安全码的写入 */
	GOZONE_IMEI2_READ,				/* IMEI2号的读取 */
	GOZONE_IMEI2_WRITE,				/* IMEI2号的写入 */
	#if 1
	GOZONE_ESN_READ, 				/* ESN号的读取 zhangjj 071108 */
	GOZONE_ESN_WRITE,				/* ESN号的写入 zhangjj 071108 */
	GOZONE_MEID_READ,				/* MEID的读取 */
	GOZONE_MEID_WRITE,				/* MEID的写入 */
	#endif
#else
	GOZONE_VERSION,					/* 软件版本号的查询 */
	GOZONE_NV_BACKUP,				/* NV的备份 */
	GOZONE_NV_RESTORE,				/* NV的恢复*/
	GOZONE_IMEI_READ,				/* IMEI号的读取 */
	GOZONE_IMEI_WRITE,				/* IMEI号的写入 */
	GOZONE_BTADD_READ,				/* 蓝牙地址的读取 */
	GOZONE_BTADD_WRITE,				/* 蓝牙地址的写入*/
	GOZONE_DCK_READ,				/* DCK数据的读取 */
	GOZONE_DCK_WRITE,				/* DCK数据的写入 */
	GOZONE_PLMN_READ,				/* PLMN数据的读取 */
	GOZONE_PLMN_WRITE,				/* PLMN数据的写入 */
	GOZONE_NCK_READ,				/* simlock info 的读取*/
	GOZONE_NCK_WRITE,				/* simlock info 的写入 */
	GOZONE_NV_IMPORT,				/* NV的导入 */
	GOZONE_NV_EXPORT,				/* NV的导出 */
	GOZONE_OTP_LOCK,				/* 锁定OTP数据 */
	GOZONE_USIM_SWITCH,				/* 修改Usim Switch 的状态 */
	GOZONE_ENGINEERING_SWITCH,		/* 修改Engineering Switch 的状态 */
	GOZONE_BLUETOOTH_CHECKOUT,		/* 修改Bluetooth Checkout 的状态 */
	GOZONE_NV_CHECKOUT,				/* 修改NV Checkout 的状态 */
	GOZONE_PUBLICKEY_READ,			/* Public key 的读取 */
	GOZONE_PUBLICKEY_WRITE,			/* Public key 的写入 */
	GOZONE_ORIUNDERWRITEDATA,		/* 读取需要签名的原始数据 */
	GOZONE_UNDERWRITEDATA_READ,		/* Underwrite data 的读取*/
	GOZONE_UNDERWRITEDATA_WRITE,	/* Underwrite data 的写入*/
	GOZONE_WRITINGREQUEST,			/* 写Flash前的签名数据请求 */
	GOZONE_ERASUREOTP,				/* 擦除OTP数据 */
	GOZONE_PHONEID_READ,			/* 读取随机值签名zhangjj 070322 */
	GOZONE_PHONEID_WRITE,			/* 写随机值,预留 */
	GOZONE_ESN_READ, 				/* ESN号的读取 zhangjj 071108 */
	GOZONE_ESN_WRITE,				/* ESN号的写入 zhangjj 071108 */
	GOZONE_MEID_READ,				/* MEID的读取 */
	GOZONE_MEID_WRITE,				/* MEID的写入 */
	GOZONE_IMEI2_READ,				/* IMEI2号的读取 */
	GOZONE_IMEI2_WRITE,				/* IMEI2号的写入 */
#endif
}ENUM_Gozone_NVOptionType;

/*===========================================================================
	枚举类型：tatCOMMAND
    概要:
        读写每项NV前的命令的上限和下限

    成员：
    1) COMMAND_LOWER_LIMIT
    说明：标识读取NV命令的下限
    2) COMMAND_UPPER_LIMIT
    说明：标识读取NV命令的下上限

    创建日期：2005/11/03
    创建人:	 WangQingXiang
    修改纪录：
===========================================================================*/
typedef enum tatCOMMAND
{
    COMMAND_LOWER_LIMIT = 0x00,
    COMMAND_UPPER_LIMIT = 0x51
}COMMAND;

/*===========================================================================
    结构体：tagNVWriteInput
    概要:
        接收后发送前的每项NV项数结构

    成员：
        1) bIsValid
        说明：标识此结构体中的数据是否有效(能否作为输入或输出)
        2) bIsErrorCommad
        说明：标识返回的是命令错误
        3) uResponseCommad
        说明：标识返回的命令
        4) uStatus
        说明：标识返回的是状态, 如果命令正确，返回的状态不一定正确
        5) nBits
        说明：标识数据的位数
        6) nIsSystem
        说明：标识数据的类型(decimal, hex, byte) 
        7) InputData
        说明：标识数据存放的空间
            a) low
            说明：存放数据的低32位
            b) high
            说明：存放数据的高32位
            c) szText
            说明：存放数据是文本数据(ANSI Fixed String)

    创建日期：2005/11/03
    创建人:	 WangQingXiang
    修改纪录：
===========================================================================*/
typedef struct tagNVWriteInput 
{
    BOOL            bIsValid;
    BOOL            bIsErrorCommand;
    unsigned short  uResponseCommand;
    unsigned short  uStatus;
    int             nBits;
    int             nIsSystem;     // 0: Dec  1: Hex   2: Byte
    struct 
    {
        ULONG       low;
        ULONG       hight;
        char        szText[BYTE_DATA_LEN];
    } InputData;
}NVWriteInput;

class CSetNVParam  
{
public:
	CSetNVParam();
	virtual ~CSetNVParam();
    /*
     *	初始化串口
     */
    BOOL InitSerialPort(int nSerialPort);
    /*
     *	关闭串口
     */
    BOOL CloseSerialPort();

	int SPCRequest(char *pszSPC);
    /*
     *	发一条命令到手机请求读取该命令的数据
     */
    BOOL ReadItem (int nCommand, int nIndex, int *nResCmd, int *nStatus);
    /*
     *	发一条命令到手机请求向手机写入数据
     */
    BOOL WriteItem(int nCommand, int nIndex, int *nResCmd, int *nStatus);

    /*
     *	从某一个Input结构体中取出某一个项的数据
     */
    BOOL GetItemData(int nCommand, int nIndex, int nItemInfoCounts, char *pszText);
    /*
     *	向某一个Input结构体中设置某一个项的数据
     */
    BOOL SetItemData(int nCommand, int nIndex, int nItemInfoCounts, char *pszText);

    /*
     *	从手机中读取OTP的imei
     */
	BOOL Read_Data_By_OTP(int nSubCmd, CommonInfo *pCommonInfo, char *pszData);
	BOOL Write_Data_By_OTP(int nSubCmd, CommonInfo *pCommonInfo, char *pszData);

    BOOL Read_OTP_Version(OTP_Version *pOTPVersion);
	BOOL Write_OTP_Version(OTP_Version *pOTPVersion);

    BOOL Read_OTP_IMEI(OTP_IMEI *pOTPImei);
	BOOL Write_OTP_IMEI(OTP_IMEI *pOTPImei);

    BOOL Read_OTP_IMEI2(OTP_IMEI2 *pOTPImei);
	BOOL Write_OTP_IMEI2(OTP_IMEI2 *pOTPImei);

    BOOL Read_OTP_BlueToothAddr(OTP_BlueToothAddr *pOTPBluetoothaddr);
	BOOL Write_OTP_BlueToothAddr(OTP_BlueToothAddr *pOTPBluetoothaddr);

    BOOL Read_OTP_HASH(OTP_Hash *pOTPHash);
	BOOL Write_OTP_HASH(OTP_Hash *pOTPHash);

	BOOL Read_OTP_PLMN(OTP_Plmn *pOTPPlmn);
	BOOL Write_OTP_PLMN(OTP_Plmn *pOTPPlmn);

	BOOL Read_OTP_FLAG(OTP_ReadWrite *pOTPReadwrite);
	BOOL Write_OTP_FLAG(OTP_ReadWrite *pOTPReadwrite);

	BOOL Read_OTP_SIMLockInfo(OTP_SIMLockInfo *pOTPSimlockinfo);
	BOOL Write_OTP_SIMLockInfo(OTP_SIMLockInfo *pOTPSimlockinfo);

	BOOL Read_OTP_PublicKey(OTP_PublicKey *pOTPPublickey);
	BOOL Write_OTP_PublicKey(OTP_PublicKey *pOTPPublickey);

	BOOL TurnOnSimLockSwitch(OTP_SimLockSwitch *pOTPSimLockSwitch);
	BOOL TurnOffSimLockSwitch(OTP_SimLockSwitch *pOTPSimLockSwitch);

	BOOL TurnOnEngineeringSwitch(OTP_EngineeringSwitch *pOTPEnginswitch);
	BOOL TurnOffEngineeringSwitch(OTP_EngineeringSwitch *pOTPEnginswitch);

	BOOL Read_NVItmesPack(int nSubCmd, NVItemsPack *pNVItemsPack);
	BOOL Write_NVItmesPack(int nSubCmd, NVItemsPack *pNVItemsPack);

	INT  ExportAllNVItemsFromPhone(byte DataBuf[], UINT *pActualBufLenth);
	INT  ImportAllNVItemsIntoPhone(byte DataBuf[], UINT ActualDataSize);

	BOOL SetServerParam(char* IPAddr,char* ProjectName);

	BOOL Get_HDET_OFF(char *pHdetOff);
	BOOL Get_HDET_SPN(char *pHdetSpn);

	BOOL ErasureOTP();

	BOOL Read_Random_Data(TRandom *pRandomData);

	BOOL Test_Sign_Client();

	BOOL Read_OTP_ESN(OTP_ESN *pOTPEsn);
	BOOL Write_OTP_ESN(OTP_ESN *pOTPEsn);

	BOOL CmdNVBackup(OTP_NVBackupRestore *pOTPNVBackupRestore);
	BOOL CmdNVRestore(OTP_NVBackupRestore *pOTPNVBackupRestore);
	
	BOOL Write_OTP_MEID(OTP_MEID *pOTPMeid);
	BOOL Read_OTP_MEID(OTP_MEID *pOTPMeid);

private:
	BOOL SignNVParam(UINT nSerialPort, BOOL forceSign);
	BOOL WriteFlashQuest(char* pData, UINT Length);
    // 清除保存nCommand命令的数据缓冲区
    BOOL ClearInputField(int nCommand, int nIndex);

    // 结构体中的数据是否有效
    BOOL IsValid(int nCommand, int nIndex);

    /*
     *	读串口完成后把读取到的数据写入到input存储缓冲区备份供以后使用
     */
    BOOL SetInputField(
                            int     nCommand, 
                            int     nIndex, 
                            int     nResCmd, 
                            int     nStatus, 
                            char    *pszData
                      );
    /*
     *	写串口开始前先读取备份在input存储缓冲区的数据供写串口时使用
     */
    BOOL GetInputField(
                            int     nCommand, 
                            int     nIndex, 
                            char    *pszData, 
                            int     *nDataLen
                      );
    
    /*
     *	写一条命令到手机
     */
    BOOL UploadToPhone(
                            int     nCommand, 
                            int     nIndex, 
                            int     *nResCmd, 
                            int     *nStatus, 
                            char    *pszData, 
                            int     nDataLen
                      );
    /*
     *	读一条命令从手机
     */
    BOOL DownloadFromPhone(
                            int     nCommand, 
                            int     nIndex   = 0, 
                            int     *nResCmd = NULL, 
                            int     *nStatus = NULL, 
                            char    *pszData = NULL
                          );
    /*
      *每一种型号的高通平台手机，用于写入参数的NV ID　可能不同
　*/
private:
    /*
     *	串口对象
     */
    CSerialPort m_SerialPort;
    NVWriteInput m_NVFieldInput[NUM_ITEMS][FIELD_NUM_ITEMS];
    char *m_pNVField[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS];
	//签名函数
	//THmacSha1 *m_pHMacProc;
	HINSTANCE m_hLibrary;
	char m_ProjectName[GOZONE_PRJECT_NAME_SIZE];
	char m_IPAddress[GOZONE_IP_ADDRESS_SIZE];
};

#endif // !defined(AFX_SETNVPARAM_H__87125966_4158_4903_98F3_E82A5BBF88EA__INCLUDED_)
