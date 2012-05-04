/*
File: SetNVParam.h
Desc: 

Author: zjj
Date  : 2007.3.14
Notes : CSetNVParam��Ķ���

   $Source: D:/cvsrepo/DllParam/SetNVParam.h,v $

$Log: SetNVParam.h,v $
Revision 1.1.1.8  2008/03/04 09:46:51  zhangjj
���ӳ������޸ĵ�NV���ݻָ�����

Revision 1.1.1.7  2007/11/16 06:31:55  zhangjj
����ESN��д�ӿڣ�������ͨ�淶��

Revision 1.1.1.6  2007/10/11 07:46:33  zhangjj
���Ӳ����Ƿ������ӷ�����ǩ��

Revision 1.1.1.5  2007/10/11 01:35:25  zhangjj

�����ύû�з���debug��֧�Ĵ���

Revision 1.2  2007/10/11 01:23:02  zhangjj
OTP����ǰǿ����������ǩ��,������OTP������ǩ������Ϊ0��ɵ�����

Revision 1.1.1.4  2007/06/13 02:34:48  zhangjj
����дpublic key�ӿ�,�رոù������ֻ��˱�֤.
����--����simlock��дplmnʱ�Զ�ȥ������ǩ��,
�����ֶ�ǩ��---���ֻ���writetoolͬ��

Revision 1.1.1.3  2007/04/26 06:12:05  zhangjj
ɾ��pc��дpublic key�Ĺ���

Revision 1.1.1.2  2007/03/27 01:39:52  zhangjj
��ȡ�������ǩ��

Revision 1.1.1.1  2007/03/14 07:26:48  zhangjj
�����ʼ�汾


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
	GOZONE_VERSION,				/* ����汾�ŵĲ�ѯ */
	GOZONE_NV_BACKUP,				/* NV�ı��� */
	GOZONE_NV_RESTORE,			/* NV�Ļָ�*/
	GOZONE_IMEI_READ,				/* IMEI�ŵĶ�ȡ */
	GOZONE_IMEI_WRITE,			/* IMEI�ŵ�д�� */
	GOZONE_BTADD_READ,			/* ������ַ�Ķ�ȡ */
	GOZONE_BTADD_WRITE,			/* ������ַ��д��*/
	GOZONE_DCK_READ,				/* DCK���ݵĶ�ȡ */
	GOZONE_DCK_WRITE,				/* DCK���ݵ�д�� */
	GOZONE_PLMN_READ,				/* PLMN���ݵĶ�ȡ */
	GOZONE_PLMN_WRITE,			/* PLMN���ݵ�д�� */
	GOZONE_NCK_READ,				/* simlock info �Ķ�ȡ*/
	GOZONE_NCK_WRITE,				/* simlock info ��д�� */
	GOZONE_NV_IMPORT,				/* NV�ĵ��� */
	GOZONE_NV_EXPORT,				/* NV�ĵ��� */
	GOZONE_OTP_LOCK,				/* ����OTP���� */
	GOZONE_USIM_SWITCH,			/* �޸�Usim Switch ��״̬ */
	GOZONE_ENGINEERING_SWITCH, 	/* �޸�Engineering Switch ��״̬ */
	GOZONE_BLUETOOTH_CHECKOUT,	/* �޸�Bluetooth Checkout ��״̬ */
	GOZONE_NV_CHECKOUT,			/* �޸�NV Checkout ��״̬ */
	GOZONE_PUBLICKEY_READ,		/* Public key �Ķ�ȡ */
	GOZONE_PUBLICKEY_WRITE,		/* Public key ��д�� */
	GOZONE_ORIUNDERWRITEDATA,		/* ��ȡ��Ҫǩ����ԭʼ���� */
	GOZONE_UNDERWRITEDATA_READ,	/* Underwrite data �Ķ�ȡ*/
	GOZONE_UNDERWRITEDATA_WRITE,	/* Underwrite data ��д��*/
	GOZONE_WRITINGREQUEST,		/* ���ֻ��˷���д����, ����֮����ܽ�����д��Flash */
	GOZONE_ERASUREOTP,
	#if 0
	GOZONE_ERASURE_OTP,			/* ����OTP���� */
	#endif
	GOZONE_PHONEID_READ,			/* ǩ�����ݵİ�ȫ��Ķ�ȡ */
	GOZONE_PHONEID_WRITE,			/* ǩ�����ݵİ�ȫ���д�� */
	GOZONE_IMEI2_READ,				/* IMEI2�ŵĶ�ȡ */
	GOZONE_IMEI2_WRITE,				/* IMEI2�ŵ�д�� */
	#if 1
	GOZONE_ESN_READ, 				/* ESN�ŵĶ�ȡ zhangjj 071108 */
	GOZONE_ESN_WRITE,				/* ESN�ŵ�д�� zhangjj 071108 */
	GOZONE_MEID_READ,				/* MEID�Ķ�ȡ */
	GOZONE_MEID_WRITE,				/* MEID��д�� */
	#endif
#else
	GOZONE_VERSION,					/* ����汾�ŵĲ�ѯ */
	GOZONE_NV_BACKUP,				/* NV�ı��� */
	GOZONE_NV_RESTORE,				/* NV�Ļָ�*/
	GOZONE_IMEI_READ,				/* IMEI�ŵĶ�ȡ */
	GOZONE_IMEI_WRITE,				/* IMEI�ŵ�д�� */
	GOZONE_BTADD_READ,				/* ������ַ�Ķ�ȡ */
	GOZONE_BTADD_WRITE,				/* ������ַ��д��*/
	GOZONE_DCK_READ,				/* DCK���ݵĶ�ȡ */
	GOZONE_DCK_WRITE,				/* DCK���ݵ�д�� */
	GOZONE_PLMN_READ,				/* PLMN���ݵĶ�ȡ */
	GOZONE_PLMN_WRITE,				/* PLMN���ݵ�д�� */
	GOZONE_NCK_READ,				/* simlock info �Ķ�ȡ*/
	GOZONE_NCK_WRITE,				/* simlock info ��д�� */
	GOZONE_NV_IMPORT,				/* NV�ĵ��� */
	GOZONE_NV_EXPORT,				/* NV�ĵ��� */
	GOZONE_OTP_LOCK,				/* ����OTP���� */
	GOZONE_USIM_SWITCH,				/* �޸�Usim Switch ��״̬ */
	GOZONE_ENGINEERING_SWITCH,		/* �޸�Engineering Switch ��״̬ */
	GOZONE_BLUETOOTH_CHECKOUT,		/* �޸�Bluetooth Checkout ��״̬ */
	GOZONE_NV_CHECKOUT,				/* �޸�NV Checkout ��״̬ */
	GOZONE_PUBLICKEY_READ,			/* Public key �Ķ�ȡ */
	GOZONE_PUBLICKEY_WRITE,			/* Public key ��д�� */
	GOZONE_ORIUNDERWRITEDATA,		/* ��ȡ��Ҫǩ����ԭʼ���� */
	GOZONE_UNDERWRITEDATA_READ,		/* Underwrite data �Ķ�ȡ*/
	GOZONE_UNDERWRITEDATA_WRITE,	/* Underwrite data ��д��*/
	GOZONE_WRITINGREQUEST,			/* дFlashǰ��ǩ���������� */
	GOZONE_ERASUREOTP,				/* ����OTP���� */
	GOZONE_PHONEID_READ,			/* ��ȡ���ֵǩ��zhangjj 070322 */
	GOZONE_PHONEID_WRITE,			/* д���ֵ,Ԥ�� */
	GOZONE_ESN_READ, 				/* ESN�ŵĶ�ȡ zhangjj 071108 */
	GOZONE_ESN_WRITE,				/* ESN�ŵ�д�� zhangjj 071108 */
	GOZONE_MEID_READ,				/* MEID�Ķ�ȡ */
	GOZONE_MEID_WRITE,				/* MEID��д�� */
	GOZONE_IMEI2_READ,				/* IMEI2�ŵĶ�ȡ */
	GOZONE_IMEI2_WRITE,				/* IMEI2�ŵ�д�� */
#endif
}ENUM_Gozone_NVOptionType;

/*===========================================================================
	ö�����ͣ�tatCOMMAND
    ��Ҫ:
        ��дÿ��NVǰ����������޺�����

    ��Ա��
    1) COMMAND_LOWER_LIMIT
    ˵������ʶ��ȡNV���������
    2) COMMAND_UPPER_LIMIT
    ˵������ʶ��ȡNV�����������

    �������ڣ�2005/11/03
    ������:	 WangQingXiang
    �޸ļ�¼��
===========================================================================*/
typedef enum tatCOMMAND
{
    COMMAND_LOWER_LIMIT = 0x00,
    COMMAND_UPPER_LIMIT = 0x51
}COMMAND;

/*===========================================================================
    �ṹ�壺tagNVWriteInput
    ��Ҫ:
        ���պ���ǰ��ÿ��NV�����ṹ

    ��Ա��
        1) bIsValid
        ˵������ʶ�˽ṹ���е������Ƿ���Ч(�ܷ���Ϊ��������)
        2) bIsErrorCommad
        ˵������ʶ���ص����������
        3) uResponseCommad
        ˵������ʶ���ص�����
        4) uStatus
        ˵������ʶ���ص���״̬, ���������ȷ�����ص�״̬��һ����ȷ
        5) nBits
        ˵������ʶ���ݵ�λ��
        6) nIsSystem
        ˵������ʶ���ݵ�����(decimal, hex, byte) 
        7) InputData
        ˵������ʶ���ݴ�ŵĿռ�
            a) low
            ˵����������ݵĵ�32λ
            b) high
            ˵����������ݵĸ�32λ
            c) szText
            ˵��������������ı�����(ANSI Fixed String)

    �������ڣ�2005/11/03
    ������:	 WangQingXiang
    �޸ļ�¼��
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
     *	��ʼ������
     */
    BOOL InitSerialPort(int nSerialPort);
    /*
     *	�رմ���
     */
    BOOL CloseSerialPort();

	int SPCRequest(char *pszSPC);
    /*
     *	��һ������ֻ������ȡ�����������
     */
    BOOL ReadItem (int nCommand, int nIndex, int *nResCmd, int *nStatus);
    /*
     *	��һ������ֻ��������ֻ�д������
     */
    BOOL WriteItem(int nCommand, int nIndex, int *nResCmd, int *nStatus);

    /*
     *	��ĳһ��Input�ṹ����ȡ��ĳһ���������
     */
    BOOL GetItemData(int nCommand, int nIndex, int nItemInfoCounts, char *pszText);
    /*
     *	��ĳһ��Input�ṹ��������ĳһ���������
     */
    BOOL SetItemData(int nCommand, int nIndex, int nItemInfoCounts, char *pszText);

    /*
     *	���ֻ��ж�ȡOTP��imei
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
    // �������nCommand��������ݻ�����
    BOOL ClearInputField(int nCommand, int nIndex);

    // �ṹ���е������Ƿ���Ч
    BOOL IsValid(int nCommand, int nIndex);

    /*
     *	��������ɺ�Ѷ�ȡ��������д�뵽input�洢���������ݹ��Ժ�ʹ��
     */
    BOOL SetInputField(
                            int     nCommand, 
                            int     nIndex, 
                            int     nResCmd, 
                            int     nStatus, 
                            char    *pszData
                      );
    /*
     *	д���ڿ�ʼǰ�ȶ�ȡ������input�洢�����������ݹ�д����ʱʹ��
     */
    BOOL GetInputField(
                            int     nCommand, 
                            int     nIndex, 
                            char    *pszData, 
                            int     *nDataLen
                      );
    
    /*
     *	дһ������ֻ�
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
     *	��һ��������ֻ�
     */
    BOOL DownloadFromPhone(
                            int     nCommand, 
                            int     nIndex   = 0, 
                            int     *nResCmd = NULL, 
                            int     *nStatus = NULL, 
                            char    *pszData = NULL
                          );
    /*
      *ÿһ���ͺŵĸ�ͨƽ̨�ֻ�������д�������NV ID�����ܲ�ͬ
��*/
private:
    /*
     *	���ڶ���
     */
    CSerialPort m_SerialPort;
    NVWriteInput m_NVFieldInput[NUM_ITEMS][FIELD_NUM_ITEMS];
    char *m_pNVField[FIELD_NUM_ITEMS][FIELD_NUM_COLUMNS];
	//ǩ������
	//THmacSha1 *m_pHMacProc;
	HINSTANCE m_hLibrary;
	char m_ProjectName[GOZONE_PRJECT_NAME_SIZE];
	char m_IPAddress[GOZONE_IP_ADDRESS_SIZE];
};

#endif // !defined(AFX_SETNVPARAM_H__87125966_4158_4903_98F3_E82A5BBF88EA__INCLUDED_)
