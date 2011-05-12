/*
File: SetNVParam.cpp
Desc: 

Author: zjj
Date  : 2007.3.14
Notes : CSetNVParam类的实现

   $Source: D:/cvsrepo/DllParam/SetNVParam.cpp,v $

$Log: SetNVParam.cpp,v $
Revision 1.1.1.10  2008/03/04 09:46:50  zhangjj
增加陈燕绿修改的NV备份恢复命令

Revision 1.1.1.9  2007/11/16 06:31:55  zhangjj
增加ESN读写接口，兼容联通规范。

Revision 1.1.1.8  2007/10/11 07:46:33  zhangjj
增加测试是否能连接服务器签名

Revision 1.1.1.7  2007/10/11 01:35:25  zhangjj

补充提交没有放在debug分支的错误

Revision 1.2  2007/10/11 01:23:02  zhangjj
OTP锁定前强制网络数据签名,避免锁OTP后由于签名数据为0造成的锁卡

Revision 1.1.1.6  2007/06/13 02:34:48  zhangjj
保留写public key接口,关闭该功能由手机端保证.
锁网--开关simlock和写plmn时自动去服务器签名,
不用手动签名---和手机、writetool同步

Revision 1.1.1.5  2007/06/11 07:05:41  zhangjj
写otp时不需要签名

Revision 1.1.1.4  2007/04/26 06:12:05  zhangjj
删除pc端写public key的功能

Revision 1.1.1.3  2007/03/27 01:39:51  zhangjj
读取随机数来签名

Revision 1.1.1.2  2007/03/20 08:16:46  zhangjj
根据IMEI号来签名

Revision 1.1.1.1  2007/03/14 07:26:48  zhangjj
导入初始版本


*/

#include "stdafx.h"
#include "SetNVParam.h"

#include "common.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSetNVParam::CSetNVParam()
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        memset(m_NVFieldInput[i], 0, sizeof(NVWriteInput) * FIELD_NUM_ITEMS);
    }
    memset(m_pNVField, 0, sizeof(char *)* FIELD_NUM_ITEMS * FIELD_NUM_COLUMNS);
	memset(m_IPAddress, 0, sizeof(m_IPAddress));
	memset(m_ProjectName, 0, sizeof(m_ProjectName));

#if 0	// zhangjj del asc.dll 100317
	//获取签名函数
	m_pHMacProc = NULL;
	m_hLibrary = LoadLibrary("ASC.dll");
	if(m_hLibrary != NULL)
	{
		m_pHMacProc = (THmacSha1*)GetProcAddress(m_hLibrary, PROC_HMAC_SHA1);
	}
#endif
}

CSetNVParam::~CSetNVParam()
{
	FreeLibrary(m_hLibrary);
}

BOOL CSetNVParam::WriteFlashQuest(char* pData, UINT Length)
{
	CommonInfo structCommonInfo;
	TRandom randomData;
	char Signature[127] = { 0 };
	int SigLen = 0;
	
	//获取手机的随机值
	if(Read_Random_Data(&randomData) == FALSE)
	{
		return FALSE;
	}
#if 0	// zhangjj del asc.dll 100317
	if (m_pHMacProc == NULL)
	{
		return FALSE;
	}
	
	m_pHMacProc(m_IPAddress, m_ProjectName,
			(char*)randomData.byteRandom, sizeof(randomData.byteRandom),
			pData, Length,
			Signature, D_SIGNATURE_SIZE, &SigLen);
#if 0 //[zhangjj,070611,del because otp don't need to sign]	
	if(SigLen == 0)
	{
		return FALSE;
	}
#endif
#endif
	//写入签名数据
	if(Write_Data_By_OTP(GOZONE_WRITINGREQUEST,&structCommonInfo,Signature) == FALSE)
	{
		return FALSE;
	}
	
	return TRUE;
}

/*===========================================================================
函数名：ClearInputField
概要:
    清除保存nCommand命令的数据缓冲区
   
原型：
    BOOL ClearInputField(int nCommand, int nIndex)
参数：
    1) [IN]   int nCommand
    说明：命令号
    2) [IN]   int nIndex
    说明：如果该命令是关于双NAM的，那么代表第几个NAM序号
    如果该命令是关于序号的，那么代表第几条序号
返回值
   类型：BOOL
   说明：非零   成功清除
         零     非成功清除
           
创建日期：2005/11/03
创建人:	  WangQingXiang
修改纪录：
============================================================================*/
BOOL CSetNVParam::ClearInputField(int nCommand, int nIndex)
{
    int nIndexCommand = nCommand + nIndex;
    memset(m_NVFieldInput[nIndexCommand], 0, sizeof(NVWriteInput)*FIELD_NUM_ITEMS);
    
    return TRUE;
}

/*===========================================================================
函数名：IsValid
概要:
    判断存储nCommand命令的数据缓冲区中的数据是否有效
   
原型：
    BOOL IsValid(int nCommand, int nIndex)
参数：
    1) [IN]   int nCommand
    说明：命令号
    2) [IN]   int nIndex
    说明：如果该命令是关于双NAM的，那么代表第几个NAM序号
    如果该命令是关于序号的，那么代表第几条序号
返回值
   类型：BOOL
   说明：非零   有效
         零     无效
           
创建日期：2005/11/03
创建人:	  WangQingXiang
修改纪录：
============================================================================*/
BOOL CSetNVParam::IsValid(int nCommand, int nIndex)
{
    int nIndexCommand = nCommand + nIndex;
    if (!m_NVFieldInput[nIndexCommand][0].bIsValid)
        return FALSE;

    if (0 != m_NVFieldInput[nIndexCommand][0].uStatus)
        return FALSE;

    if (0x14 == m_NVFieldInput[nIndexCommand][0].uResponseCommand)
        return FALSE;

    return TRUE;
}

/*===========================================================================
函数名：SetInputField
概要:
    读串口完成后把读取到的数据写入到input存储缓冲区备份供以后使用
   
原型：
BOOL SetInputField( int nCommand, 
                    int nIndex, 
                    int nResCmd, 
                    int  nStatus, 
                    char *pszData)
参数：
    1) [IN]   int nCommand
    说明：命令号
    2) [IN]   int nIndex
    说明：如果该命令是关于双NAM的，那么代表第几个NAM序号
    如果该命令是关于序号的，那么代表第几条序号
    3) [IN]   int  nStatus
    说明：此次读取的数据如果成功，成功后的状态(只有00是数据正确状态，
    状态的详细情况请参见SerialPort.h文件)
    4) [IN]   char *pszData
    说明：读取的数据存储的缓冲区

返回值
   类型：BOOL
   说明：非零   成功存储
         零     未成功存储
           
创建日期：2005/11/03
创建人:	  WangQingXiang
修改纪录：
============================================================================*/
BOOL CSetNVParam::SetInputField(int  nCommand, 
                                int  nIndex, 
                                int  nResCmd, 
                                int  nStatus, 
                                char *pszData)
{
    int nIndexByte = 0;
    int nIndexCommand = nCommand + nIndex;
    
    memset(m_pNVField, 0, 
        sizeof(char *) * FIELD_NUM_ITEMS * FIELD_NUM_COLUMNS);
    memcpy(m_pNVField, _gszFieldItem[nIndexCommand], 
        sizeof(char *) * FIELD_NUM_ITEMS * FIELD_NUM_COLUMNS); 

    m_NVFieldInput[nIndexCommand][0].bIsValid = (nStatus == 0) ? TRUE : FALSE;
    m_NVFieldInput[nIndexCommand][0].uStatus = nStatus;
    m_NVFieldInput[nIndexCommand][0].uResponseCommand = nResCmd;

    // 如果此次读取的数据无效，直接返回，不把读到的数据放入到input缓冲区
    if (!IsValid(nCommand, nIndex))
        return TRUE;
    
    // 由_gszItem[][]中第1列计算出该结构体有多少项
    int nCount = atol(_gszItem[nIndexCommand][1]); 
    for (int i = 0; i < nCount; i++)
    {
        int nNVSize = atoi(m_pNVField[i][3]);
        m_NVFieldInput[nIndexCommand][i].nBits = nNVSize;
        
        char szTempBuffer[20];
        memcpy(szTempBuffer, m_pNVField[i][0], 20);
        int nDataType = DataType(szTempBuffer);
        m_NVFieldInput[nIndexCommand][i].nIsSystem = nDataType;
        if (2 != nDataType)
        {
            Int64 *pInt64 = ShiftToInt64(nNVSize, pszData + nIndexByte);
            m_NVFieldInput[nIndexCommand][i].InputData.low = pInt64->uLow;
            m_NVFieldInput[nIndexCommand][i].InputData.hight = pInt64->uHigh;
        }
        else
        {
            memcpy(m_NVFieldInput[nIndexCommand][i].InputData.szText, 
                &pszData[nIndexByte], nNVSize / 8);
        }
        nIndexByte += (nNVSize / 8);
    }
    
    return TRUE;
}

/*===========================================================================
函数名：GetInputField
概要:
    写串口前把input缓冲区的数据取出准备写入到手机
   
原型：
BOOL GetInputField( int  nCommand, 
                    int  nIndex,  
                    char *pszData, 
                    int  *nDataLen)
参数：
    1) [IN]   int nCommand
    说明：命令号
    2) [IN]   int nIndex
    说明：如果该命令是关于双NAM的，那么代表第几个NAM序号
    如果该命令是关于序号的，那么代表第几条序号
    3) [OUT]   char *pszData
    说明：从input缓冲区取出的的数据存在该缓冲区中
    4) [OUT]   int  *nDataLen
    说明：从input缓冲区取出的的数据长度

返回值
   类型：BOOL
   说明：非零   成功取出
         零     未成功取出
           
创建日期：2005/11/03
创建人:	  WangQingXiang
修改纪录：
============================================================================*/
BOOL CSetNVParam::GetInputField(int     nCommand, 
                                int     nIndex, 
                                char    *pszData, 
                                int     *nDataLen)
{
    int nIndexByte = 0;
    int nIndexCommand = nCommand + nIndex;

    if (0 == m_NVFieldInput[nIndexCommand][0].bIsValid) 
    {
        //TRACE("\nthe item: %s(index: %d) is invalid\n", _gszItem[nIndexCommand][0], nIndex); 
        return FALSE; 
    }
    //TRACE("\nthe item: %s(index: %d) is valid\n", _gszItem[nIndexCommand][0], nIndex);

    memset(m_pNVField, 0, 
        sizeof(char *) * FIELD_NUM_ITEMS * FIELD_NUM_COLUMNS);
    memcpy(m_pNVField, _gszFieldItem[nIndexCommand], 
        sizeof(char *) * FIELD_NUM_ITEMS * FIELD_NUM_COLUMNS);

    // 存储将要发送的缓冲区
    //char szItemData[NV_ITEMDATA_LEN] = ""; 

    // 由_gszItem[][]中第1列计算出该结构体有多少项
    int nCount = atoi(_gszItem[nIndexCommand][1]);
    for (int i = 0; i < nCount; i++)
    {
        int nNVSize = atoi(m_pNVField[i][3]);
        if (2 != m_NVFieldInput[nIndexCommand][i].nIsSystem) 
        {
            Int64 int64;
            int64.uLow = m_NVFieldInput[nIndexCommand][i].InputData.low;
            int64.uHigh = m_NVFieldInput[nIndexCommand][i].InputData.hight;
            memcpy(pszData + nIndexByte, 
                ShiftToChar(nNVSize, &int64), (nNVSize / 8));
        }
        else
        {
            memcpy(pszData + nIndexByte, 
                m_NVFieldInput[nIndexCommand][i].InputData.szText, 
                strlen(m_NVFieldInput[nIndexCommand][i].InputData.szText));
        }
        nIndexByte += (nNVSize / 8);

    }
    *nDataLen = nIndexByte;

    return TRUE;
}

/*===========================================================================
函数名：InitSerialPort
概要:
    初始化串口
   
原型：
    BOOL InitSerialPort(int nPort)
参数：
    1) [IN] int nPort
        说明：端口号
返回值
   类型：BOOL
   说明：非零   成功初始化
         零     非成功初始化
           
创建日期：2005/11/03
创建人:	  WangQingXiang
修改纪录：
============================================================================*/
BOOL CSetNVParam::InitSerialPort(int nSerialPort)
{
    if (!m_SerialPort.InitSerialPort(nSerialPort))
        return FALSE;

    return TRUE;
}

/*===========================================================================
函数名：CloseSerialPort
概要:
    初始化串口
   
原型：
    BOOL CloseSerialPort
参数：
    无参数
返回值
   类型：BOOL
   说明：非零   成功关闭
         零     非成功关闭
           
创建日期：2005/11/03
创建人:	  WangQingXiang
修改纪录：
===========================================================================*/
BOOL CSetNVParam::CloseSerialPort()
{
    if (!m_SerialPort.Close())
        return FALSE;

    return TRUE;
}

int CSetNVParam::SPCRequest(char *pszSPC) 
{
	if (NULL == pszSPC) 
		return FALSE;
	
	BOOL bResult = FALSE;
	int  nResult = 0;
	
	char szCommand[BUFFER_SIZE] = "", szResponse[BUFFER_SIZE] = ""; 
	memset(szCommand, 0, BUFFER_SIZE);
	memset(szResponse, 0, BUFFER_SIZE);
	
	szCommand[0] = 7;
	szCommand[1] = 0;
	szCommand[2] = 0x41;
	for (int i = 3; i < 9; i++) 
	{
		szCommand[i] = pszSPC[i - 3];
	}
	bResult = m_SerialPort.CommandResponse(szCommand, szResponse);
	
	if (bResult) 
	{
		if (1 == szResponse[3]) 
			nResult = 1;
		else
			nResult = 0;
	}
	else
	{
		nResult = -1;
	}
	
	return nResult;
}

/*===========================================================================
函数名：UploadToPhone
概要:
    向手机写NV数据
 
原型：
BOOL UploadToPhone( int     nCommand, 
                    int     nIndex, 
                    int     *nResponseCommand, 
                    int     *nStatus, 
                    char    *pszData)
参数：
    1) [IN]   int nCommand
        说明：命令号
    2) [IN]   int nIndex
        说明：如果该命令是关于双NAM的，那么代表第几个NAM序号
              如果该命令是关于序号的，那么代表第几条序号
    3) [OUT]  int *nResponseCommand
        说明：读写操作如果执行成功，从手机端返回的此次操作的命令
    4) [OUT]  int *nStatus
        说明：读写操作如果执行成功，从手机端返回的此次操作的状态
    5) [OUT]  char *pszData
        说明：由该函数的使用者分配pszData空间，代表从手机返回的数据
返回值
   类型：BOOL
   说明：非零   串口读写操作成功
         零     串口读写操作未成功
           
创建日期：2005/11/03
创建人:	  WangQingXiang
修改纪录：
===========================================================================*/
BOOL CSetNVParam::UploadToPhone( int     nCommand, 
                                 int     nIndex, 
                                 int     *nResCmd, 
                                 int     *nStatus, 
                                 char    *pszData, 
                                 int     nDataLen)
{ 
    if (NULL == pszData)
        return FALSE;

    int nIndexCommand = nCommand + nIndex;
    if (nIndexCommand < COMMAND_LOWER_LIMIT || nIndexCommand > COMMAND_UPPER_LIMIT)
        return FALSE;

    char chResCmd = 0;
    USHORT uStatus = 0;
    if (!m_SerialPort.Write_NV_ITEM_DATA(atoi(_gszItem[nIndexCommand][0]), 
        pszData, nDataLen, &chResCmd, &uStatus))
        return FALSE;
    
    *nResCmd = chResCmd;
    *nStatus = uStatus;

    return TRUE;
}

/*===========================================================================

函数名：DownloadFromPhone
概要:
    从手机读NV数据
   
原型：
    BOOL DownloadFromPhone( int     nCommand, 
                            int     nIndex, 
                            int     *nResponseCommand, 
                            int     *nStatus,
                            char    *pszData) 
参数：
    1) [IN]  int nCommand
        说明：命令号
    2) [IN]  int nIndex
        说明：如果该命令是关于双NAM的，那么代表第几个NAM序号
              如果该命令是关于序号的，那么代表第几条序号
    3) [OUT] int *nResponseCommand
        说明：读写操作如果执行成功，从手机端返回的此次操作的命令
    4) [OUT] int *nStatus
        说明：读写操作如果执行成功，从手机端返回的此次操作的状态
    5) [OUT] char *pszData
        说明：由该函数的使用者分配pszData空间，代表从手机返回的数据
返回值
   类型：BOOL
   说明：非零   串口读写操作成功
         零     串口读写操作未成功
           
创建日期：2005/11/03
创建人:	  WangQingXiang
修改纪录：
	 
===========================================================================*/
BOOL CSetNVParam::DownloadFromPhone(int     nCommand, 
                                    int     nIndex, 
                                    int     *nResCmd, 
                                    int     *nStatus, 
                                    char    *pszData)
{
    if (NULL == pszData)
        return FALSE;
    // 计算出该命令在循环中的序号
    int nIndexCommand = nCommand + nIndex;
    TRACE("%.4d:   ", nIndexCommand); 
    if (nIndexCommand < COMMAND_LOWER_LIMIT || nIndexCommand > COMMAND_UPPER_LIMIT)
        return FALSE;
    
    // 由_gszItem[][]中第2列填充包的第0个字节(第几个NAM或者第几个序号)
    pszData[0] = (char)(atol(_gszItem[nIndexCommand][2]));
    
    char chResCmd = 0;
    USHORT uStatus = 0;
    // 由_gszItem[][]中第0列计算出该命令所属的NV值
    if (!m_SerialPort.Read_NV_ITEM_DATA(atoi(_gszItem[nIndexCommand][0]), 
        pszData, &chResCmd, &uStatus)) 
        return FALSE;

    *nResCmd = chResCmd;
    *nStatus = uStatus;

    return TRUE;
}

/*===========================================================================
函数名：ReadItem
概要:
    从手机读NV命令

原型：
    ReadItem (int nCommand, int nIndex, int *nResCmd, int *nStatus);
参数：
    1) [IN]  int nCommand
        说明：命令号
    2) [IN]  int nIndex
        说明：如果该命令是关于双NAM的，那么代表第几个NAM序号
              如果该命令是关于序号的，那么代表第几条序号
    3) [OUT] int *nResCmd
        说明：读写操作如果执行成功，从手机端返回的此次操作的命令
    4) [OUT] int *nStatus
        说明：读写操作如果执行成功，从手机端返回的此次操作的状态
返回值
   类型：BOOL
   说明：非零   串口读写操作成功
         零     串口读写操作未成功

创建日期：2005/11/03
创建人:	  WangQingXiang
修改纪录：
===========================================================================*/
BOOL CSetNVParam::ReadItem (int nCommand, int nIndex, int *nResCmd, int *nStatus)
{
    char szNV_ITEM_DATA[NV_ITEMDATA_LEN] = "";
  
    if (!ClearInputField(nCommand, nIndex))
        return FALSE;

    if (!DownloadFromPhone(nCommand, nIndex, nResCmd, nStatus, szNV_ITEM_DATA))
        return FALSE;

    if (!SetInputField(nCommand, nIndex, *nResCmd, *nStatus, szNV_ITEM_DATA))
        return FALSE;

    return TRUE;
}

/*===========================================================================
函数名：WriteItem
概要:
    向手机写NV命令
   
原型：
    WriteItem(int nCommand, int nIndex, int *nResCmd, int *nStatus)
参数：
    1) [IN]  int nCommand
        说明：命令号
    2) [IN]  int nIndex
        说明：如果该命令是关于双NAM的，那么代表第几个NAM序号
              如果该命令是关于序号的，那么代表第几条序号
    3) [OUT] int *nResCmd
        说明：读写操作如果执行成功，从手机端返回的此次操作的命令
    4) [OUT] int *nStatus
        说明：读写操作如果执行成功，从手机端返回的此次操作的状态
返回值
   类型：BOOL
   说明：非零   串口读写操作成功
         零     串口读写操作未成功

创建日期：2005/11/03
创建人:	  WangQingXiang
修改纪录：
	 
===========================================================================*/
BOOL CSetNVParam::WriteItem(int nCommand, int nIndex, int *nResCmd, int *nStatus)
{
    int nDataLen = 0;
    char szNV_ITEM_DATA[NV_ITEMDATA_LEN] = "";

    if (!GetInputField(nCommand, nIndex, szNV_ITEM_DATA, &nDataLen))
        return FALSE;

    if (!UploadToPhone(nCommand, nIndex, nResCmd, nStatus, szNV_ITEM_DATA, nDataLen))
        return FALSE;

    if (*nResCmd == 0x14)
    {
        #ifdef _DEBUG
            CString strText;
            strText.Format("the item: %s(index: %d) response command error.\n", _gszItem[nCommand + nIndex][0], nIndex);
            //MYTRACE(strText);
        #endif
        return FALSE;
    }

    if (*nStatus != 0)
    {
        #ifdef _DEBUG
            CString strText;
            strText.Format("the item: %s(index: %d) resoponse status error.\n", _gszItem[nCommand + nIndex][0], nIndex, STATUS_REQUEST_COMPLETED + nStatus);
            //MYTRACE(strText);
        #endif
        return FALSE;
    }

    CString strText;
    strText.Format("the item: %s(index: %d) writed successfully.\n", _gszItem[nCommand + nIndex][0], nIndex);
    //MYTRACE(strText);

    return TRUE;
}

/*===========================================================================
函数名：GetItemData
概要:
    该函数负责从input中取出某个命令中的某一项数据内容

原型：
    GetItemData (int nCommand, int nIndex, int nItemInfoCounts, char *pszText)
参数：
    1) [IN]  int nCommand
        说明：命令号
    2) [IN]  int nIndex
        说明：如果该命令是关于双NAM的，那么代表第几个NAM序号
              如果该命令是关于序号的，那么代表第几条序号
    3) [OUT] int nItemInfoCounts
        说明：当前命令的某一项
    4) [OUT] char *pszText
        说明：当前命令下的某项数据内容
返回值
   类型：BOOL
   说明：非零   成功获取
         零     未成功获取

创建日期：2005/11/03
创建人:	  WangQingXiang
修改纪录：
===========================================================================*/
BOOL CSetNVParam::GetItemData(int nCommand, int nIndex, int nItemInfoCounts, char *pszText)
{
    int nIndexCommand = nCommand + nIndex;
    ASSERT(nItemInfoCounts <= atoi(_gszItem[nIndexCommand][1]));
    
    if (!IsValid(nCommand, nIndex))
        return FALSE;

    if (2 != m_NVFieldInput[nIndexCommand][nItemInfoCounts].nIsSystem) 
    {
        if (m_NVFieldInput[nIndexCommand][nItemInfoCounts].nBits == 8) 
        {
            if (1 == m_NVFieldInput[nIndexCommand][nItemInfoCounts].nIsSystem)
                sprintf(pszText, "0x%.2x", 
                m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low);
            else
                sprintf(pszText,"%d", 
                m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low);
        } 
        else if (m_NVFieldInput[nIndexCommand][nItemInfoCounts].nBits == 16) 
        {
            if (1 == m_NVFieldInput[nIndexCommand][nItemInfoCounts].nIsSystem)
                sprintf(pszText, "0x%.4x", 
                m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low);
            else
                sprintf(pszText, "%d", 
                m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low);;
        }
        else if (m_NVFieldInput[nIndexCommand][nItemInfoCounts].nBits == 24) 
        {
            if (1 == m_NVFieldInput[nIndexCommand][nItemInfoCounts].nIsSystem)
                sprintf(pszText, "0x%.6x", 
                m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low);
            else
                sprintf(pszText, "%d", 
                m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low);;
        }
        else if (m_NVFieldInput[nIndexCommand][nItemInfoCounts].nBits == 32) 
        {
            if (1 == m_NVFieldInput[nIndexCommand][nItemInfoCounts].nIsSystem)
                sprintf(pszText, "0x%.8X", 
                m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low);
            else
                sprintf(pszText, "%d", 
                m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low);
        }
        else if (m_NVFieldInput[nIndexCommand][nItemInfoCounts].nBits == 48) 
        {
            ULONGLONG value = 0;
            if (1 == m_NVFieldInput[nIndexCommand][nItemInfoCounts].nIsSystem) 
            {
                value = (m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.hight << 16)
                    | m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low;
                sprintf(pszText, "0x%.12x", value);
            }
        }
        else if (m_NVFieldInput[nIndexCommand][nItemInfoCounts].nBits == 64) 
        {
            ULONGLONG value = 0;
            if (1 == m_NVFieldInput[nIndexCommand][nItemInfoCounts].nIsSystem) 
            {
                value = (m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.hight << 16)
                    |m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low;
                sprintf(pszText, "0x%.16x", value);
            }
        }
    }
    else
    {
        memcpy(pszText, m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.szText, 
            m_NVFieldInput[nIndexCommand][nItemInfoCounts].nBits / 8);
    }
    
    return TRUE;
}

/*===========================================================================
函数名：SetItemData
概要:
    该函数负责把某个命令中的某一项数据内容存储到该命令中

原型：
    SetItemData (int nCommand, int nIndex, int nItemInfoCounts, char *pszText)
参数：
    1) [IN]  int nCommand
        说明：命令号
    2) [IN]  int nIndex
        说明：如果该命令是关于双NAM的，那么代表第几个NAM序号
              如果该命令是关于序号的，那么代表第几条序号
    3) [OUT] int nItemInfoCounts
        说明：当前命令的某一项
    4) [OUT] char *pszText
        说明：要存储的某项数据内容
返回值
   类型：BOOL
   说明：非零   成功存储
         零     未成功存储

创建日期：2005/11/03
创建人:	  WangQingXiang
修改纪录：
===========================================================================*/
BOOL CSetNVParam::SetItemData(int nCommand, int nIndex, int nItemInfoCounts, char *pszText) 
{
    if (NULL == pszText)
        return FALSE;

    if (nItemInfoCounts >= FIELD_NUM_ITEMS)
        return FALSE;

    int nIndexCommand = nCommand + nIndex;
    ASSERT(nItemInfoCounts <= atoi(_gszItem[nIndexCommand][1]));

    memset(m_pNVField, 0, 
        sizeof(char *) * FIELD_NUM_ITEMS * FIELD_NUM_COLUMNS);
    memcpy(m_pNVField, _gszFieldItem[nIndexCommand], 
        sizeof(char *) * FIELD_NUM_ITEMS * FIELD_NUM_COLUMNS);
    
    if (strcmp(pszText, "") != 0)
    {
        m_NVFieldInput[nIndexCommand][0].bIsValid = 1;
        m_NVFieldInput[nIndexCommand][0].uStatus = 0;
    }
    else 
    {
        m_NVFieldInput[nIndexCommand][0].bIsValid = 0; 
        return FALSE; 
    }
    
    int nNVSize = atoi(m_pNVField[nItemInfoCounts][3]);
    if (m_NVFieldInput[nIndexCommand][nItemInfoCounts].nBits == 0) // for list ctrl(NAI)
    {
        m_NVFieldInput[nIndexCommand][nItemInfoCounts].nBits = nNVSize;
    }

    char tempbuffer[20];
    memcpy(tempbuffer, pszText, 20);
    if ((tempbuffer[1] == 'x') || (tempbuffer[1] == 'X'))
    {
        m_NVFieldInput[nIndexCommand][nItemInfoCounts].nIsSystem = 1;
        if (nNVSize <= 32)
        {
            m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low 
                = strtoul(tempbuffer+2, NULL, 16);
        }
        else
        {
            UCHAR Strlength = strlen(pszText)-2;
            if (Strlength <= 8)
            {
                m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low 
                    = strtoul(tempbuffer+2, NULL, 16);
            }
            else
            {
                char buffer[8];
                memset(buffer, 0, 8);
                memcpy(buffer, tempbuffer + 2, (Strlength - 8));	// hight byte

                m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.hight = 
                    (ULONG)(strtoul(buffer, NULL, 16));
                m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low = 
                    (ULONG)(strtoul(tempbuffer + 2 + (Strlength - 8), NULL, 16));
            }
        }
    }
    else if ((tempbuffer[1] == 'b') || (tempbuffer[1] == 'B')) 
    {
        m_NVFieldInput[nIndexCommand][nItemInfoCounts].nIsSystem = 2;
        memcpy(m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.szText, 
            pszText + 2, nNVSize / 8);
    }
    else
    {
        m_NVFieldInput[nIndexCommand][nItemInfoCounts].nIsSystem = 0;
        m_NVFieldInput[nIndexCommand][nItemInfoCounts].InputData.low 
            = atol(pszText);
    }

    return TRUE;
}

/*
 *	通过OTP向手机中读取参数
 */
BOOL CSetNVParam::Read_Data_By_OTP(int nSubCmd, CommonInfo *pCommonInfo, char *pszData)
{
    char chResCmd = 0;
	word wStatus  = 0;
    BOOL bResult = FALSE;

    char szITEM_DATA[NV_ITEMDATA_LEN] = { 0 };
	szITEM_DATA[0] = char(nSubCmd);			// 为第一个字节填充子命令.

	bResult = m_SerialPort.Read_NV_ITEM_DATA(GOZONE_OTP_EXTERN_ITEM,
											szITEM_DATA,
											&chResCmd,
											&wStatus);

	pCommonInfo->nResCmd = (int)chResCmd;
	pCommonInfo->nStatus = (int)wStatus;
	pCommonInfo->bValid  = bResult;

    bResult = bResult && (wStatus == 0);

	if (bResult && NULL != pszData)
	{
		memcpy (pszData, szITEM_DATA + 1, 127);	// 去掉第一个字节, 因为是子命令.
	}

	return bResult;
}

/*
 *	通过OTP向手机中写入参数
 */
BOOL CSetNVParam::Write_Data_By_OTP(int nSubCmd, CommonInfo *pCommonInfo, char *pszData)
{
    char chRescmd = 0; 
	word wStatus  = 0;
    BOOL bResult = FALSE;

	char szITEM_DATA[NV_ITEMDATA_LEN] = { 0 };
	szITEM_DATA[0] = char(nSubCmd);			// 为第一个字节填充子命令.
	
	if (NULL != pszData)
	{
		memcpy(szITEM_DATA + 1, pszData, 127);
	}

    bResult = m_SerialPort.Write_NV_ITEM_DATA(GOZONE_OTP_EXTERN_ITEM,
											szITEM_DATA,
											NV_ITEMDATA_LEN,
											&chRescmd,
											&wStatus);

	pCommonInfo->nResCmd = (int)chRescmd;
	pCommonInfo->nStatus = (int)wStatus;
	pCommonInfo->bValid	= bResult;

    bResult = bResult && (wStatus == 0);

    return bResult;
}

/*
 *	通过OTP向手机中版本号
 */
BOOL CSetNVParam::Read_OTP_Version(OTP_Version *pOTPVersion)
{
	char szVersion[128] = {0};

	BOOL bResult = Read_Data_By_OTP(GOZONE_VERSION, 
									&pOTPVersion->structCommonInfo,
									szVersion);

	if (bResult)
	{
		memcpy (pOTPVersion->szVersion, szVersion, GOZONE_VERSION_SIZE);
		pOTPVersion->structCommonInfo.bValid = 1;
	}

	return bResult;
}

/*
 *	通过OTP向手机中写入版本号,暂时不支持
 */
BOOL CSetNVParam::Write_OTP_Version(OTP_Version *pOTPVersion)
{
	return FALSE;
}

/*
 *	通过OTP向手机中读取IMEI
 */
BOOL CSetNVParam::Read_OTP_IMEI(OTP_IMEI *pOTPImei)
{
	char szText[128]	= { 0 };
	char szTempText[32]	= { 0 };

	BOOL bResult = Read_Data_By_OTP(GOZONE_IMEI_READ, 
									&pOTPImei->structCommonInfo,
									szText);

	if (bResult)
	{
		for (int i = 0; i < GOZONE_IMEI_SIZE; i++)
		{
			sprintf (szTempText+i*2, "%x%x", szText[i]&0xf, (szText[i]>>4)&0xf);
		}
		strcpy (pOTPImei->szIMEI, szTempText+3);

		pOTPImei->structCommonInfo.bValid = 1;
	}
	return bResult;
}
/*
 *	通过OTP向手机中写入IMEI
 */
BOOL CSetNVParam::Write_OTP_IMEI(OTP_IMEI *pOTPImei)
{
    char szText[32]			= { 0 };
	char szDigitText[32]	= { 0 };
	char szTempText[127+1]	= { 0 };

    sprintf(szText, "80a%s", pOTPImei->szIMEI);

    for (int i=GOZONE_IMEI_SIZE-1; i>=0; i--)
    {
        sprintf(szDigitText, "%c%c", szText[2 * i + 1], szText[2 * i]);
        TRACE("IMEI[%d]: %s\n", i, szDigitText);

		szTempText[i] = (char)strtoul(szDigitText, NULL, 16);
    }

	if(WriteFlashQuest(szTempText,GOZONE_IMEI_SIZE) == FALSE)
	{
		return FALSE;
	}

	BOOL bResult = Write_Data_By_OTP(GOZONE_IMEI_WRITE, 
									&pOTPImei->structCommonInfo,
									szTempText);
	
	return bResult;
}

/*
 *	通过OTP向手机中读取蓝牙
 */
BOOL CSetNVParam::Read_OTP_BlueToothAddr(OTP_BlueToothAddr *pOTPBluetoothaddr)
{
	int i;
	char szText[128] = { 0 };
	byte asc_1,asc_2;
	int Index=0;

	BOOL bResult = Read_Data_By_OTP(GOZONE_BTADD_READ, 
									&pOTPBluetoothaddr->structCommonInfo,
									szText);

	if (bResult)
	{
		for(i=GOZONE_BT_ADDRESS_SIZE-1; i>=0; i--)
		{
			asc_1 = (szText[i]&0xF0)>>4;	//高位
			asc_2 = szText[i]&0x0F;			//低位
			pOTPBluetoothaddr->szBlueToothAddr[Index++] = (asc_1 <= 9) ? (asc_1+'0') :(asc_1-10+'A');
			pOTPBluetoothaddr->szBlueToothAddr[Index++] = (asc_2 <= 9) ? (asc_2+'0') :(asc_2-10+'A');
		}
		pOTPBluetoothaddr->szBlueToothAddr[Index] = 0;

		pOTPBluetoothaddr->structCommonInfo.bValid = 1;
	}

	return bResult;
}
/*
 *	通过OTP向手机中写入蓝牙
 */
BOOL CSetNVParam::Write_OTP_BlueToothAddr(OTP_BlueToothAddr *pOTPBluetoothaddr)
{
	int i;
    char szText[127]	= { 0 };
	char szBTAddr[GOZONE_BT_ADDRESS_SIZE*2+1] = { 0 };

	for(i=0; i<GOZONE_BT_ADDRESS_SIZE*2; i++)
	{
		if(pOTPBluetoothaddr->szBlueToothAddr[i]>='0' && pOTPBluetoothaddr->szBlueToothAddr[i]<= '9')
		{
			szBTAddr[i] = pOTPBluetoothaddr->szBlueToothAddr[i] - '0';
		}
		else if(pOTPBluetoothaddr->szBlueToothAddr[i]>='a' && pOTPBluetoothaddr->szBlueToothAddr[i]<= 'f')
		{
			szBTAddr[i] = pOTPBluetoothaddr->szBlueToothAddr[i] - 'a' + 0x0A;
		}
		else if(pOTPBluetoothaddr->szBlueToothAddr[i]>='A' && pOTPBluetoothaddr->szBlueToothAddr[i]<= 'F')
		{
			szBTAddr[i] = pOTPBluetoothaddr->szBlueToothAddr[i] - 'A' + 0x0A;
		}
		else
		{
			szBTAddr[i] = 0x0F;
		}
	}
	for(i=GOZONE_BT_ADDRESS_SIZE-1; i>=0; i--)
	{
		szText[GOZONE_BT_ADDRESS_SIZE-i-1] = ((szBTAddr[i*2]&0x0F)<<4) + (szBTAddr[i*2 + 1]&0x0F);
	}

	if(WriteFlashQuest(szText,GOZONE_BT_ADDRESS_SIZE) == FALSE)
	{
		return FALSE;
	}

	BOOL bResult = Write_Data_By_OTP(GOZONE_BTADD_WRITE, 
									&pOTPBluetoothaddr->structCommonInfo,
									szText);

	return bResult;
}

/*
 *	通过OTP向手机中读取hash
 */
BOOL CSetNVParam::Read_OTP_HASH(OTP_Hash *pOTPHash)
{
	char szText[127] = { 0 };

	BOOL bResult = Read_Data_By_OTP(GOZONE_DCK_READ, 
									&pOTPHash->structCommonInfo,
									szText);
	
	if (bResult)
	{
		int i = 0;

		for (i = 0; i < GOZONE_DCKHASH_LEN; i++)		// 填充dck
		{
			pOTPHash->byteHash[i] = szText[i];
		}
		pOTPHash->structCommonInfo.bValid = 1;
	}

	return bResult;
}
/*
 *	通过OTP向手机中写入hash
 */
BOOL CSetNVParam::Write_OTP_HASH(OTP_Hash *pOTPHash)
{
	char szText[127] = { 0 };
	int i = 0;

	for (i = 0; i < GOZONE_DCKHASH_LEN; i++)		// 填充dck
	{
		szText[i] = pOTPHash->byteHash[i];
	}
	
	if(WriteFlashQuest(szText,GOZONE_DCKHASH_LEN) == FALSE)
	{
		return FALSE;
	}

	BOOL bResult = Write_Data_By_OTP(GOZONE_DCK_WRITE, 
									&pOTPHash->structCommonInfo,
									szText);

	return bResult;
}

/*
 *	通过OTP向手机中读取Plmn
 */
BOOL CSetNVParam::Read_OTP_PLMN(OTP_Plmn *pOTPPlmn)
{
	char szText[127] = { 0 };

	BOOL bResult = Read_Data_By_OTP(GOZONE_PLMN_READ, 
									&pOTPPlmn->structCommonInfo,
									szText);
	
	if (bResult)
	{
		int i = 0, j = 0;

		for (i = 0; i < GOZONE_PLMNLIST_LEN; i++)		// 填充plmn
		{
			for (j = 0; j < 3; j++)
			{
				pOTPPlmn->bytePlmn[i][j] = szText[i*3+j];
			}
		}
		pOTPPlmn->CountryCode[0] = szText[GOZONE_PLMNLIST_LEN*3];
		pOTPPlmn->CountryCode[1] = szText[GOZONE_PLMNLIST_LEN*3+1];
		pOTPPlmn->structCommonInfo.bValid = 1;
	}

	return bResult;
}
/*
 *	通过OTP向手机中写入Plmn
 */
BOOL CSetNVParam::Write_OTP_PLMN(OTP_Plmn *pOTPPlmn)
{
	char szText[127] = { 0 };
	int i = 0, j = 0;

	for (i = 0; i < GOZONE_PLMNLIST_LEN; i++)		// 填充plmn
	{
		for (j = 0; j < 3; j++)
		{
			szText[i*3+j] = pOTPPlmn->bytePlmn[i][j];
		}
	}
	szText[GOZONE_PLMNLIST_LEN*3] = pOTPPlmn->CountryCode[0];
	szText[GOZONE_PLMNLIST_LEN*3+1] = pOTPPlmn->CountryCode[1];

	if(WriteFlashQuest(szText,GOZONE_PLMNLIST_LEN*3+2) == FALSE)
	{
		return FALSE;
	}

	BOOL bResult = Write_Data_By_OTP(GOZONE_PLMN_WRITE, 
									&pOTPPlmn->structCommonInfo,
									szText);
#if 1 //[zhangjj,070612,add for auto sign]
	if (TRUE == bResult) 
	{
		SignNVParam(0,FALSE);
	}
#endif

	return bResult;
}

/*
 *	通过OTP向手机中读取请求
 */
BOOL CSetNVParam::Read_OTP_FLAG(OTP_ReadWrite *pOTPReadwrite)
{
	BOOL bResult = Read_Data_By_OTP(GOZONE_OTP_LOCK, 
									&pOTPReadwrite->structCommonInfo,
									NULL);

	if (bResult)
	{
		pOTPReadwrite->structCommonInfo.bValid = 1;
	}

	return bResult;
}
/*
 *	通过OTP向手机中写入请求
 */
BOOL CSetNVParam::Write_OTP_FLAG(OTP_ReadWrite *pOTPReadwrite)
{
	OTP_PublicKey otp_PublicKey = {0};

	//be sure the sign not 0
	if (FALSE == SignNVParam(0, TRUE))
	{
		return FALSE;
	}

	//读取Public Key
	if(Read_OTP_PublicKey(&otp_PublicKey) == FALSE)
	{
		return FALSE;
	}

	//用Public Key 来签名
	if(WriteFlashQuest((char*)otp_PublicKey.bytePublicKey,GOZONE_PUBLICKEY_LEN) == FALSE)
	{
		return FALSE;
	}

	return Write_Data_By_OTP(GOZONE_OTP_LOCK, 
							&pOTPReadwrite->structCommonInfo,
							NULL);

}

BOOL CSetNVParam::Read_OTP_SIMLockInfo(OTP_SIMLockInfo *pOTPSimlockinfo)
{
	char szText[127] = {0};

	BOOL bResult = Read_Data_By_OTP(GOZONE_NCK_READ, 
									&pOTPSimlockinfo->structCommonInfo,
									szText);

	if (bResult) 
	{
		pOTPSimlockinfo->byteLockStatus				= szText[0];
		pOTPSimlockinfo->byteSequenceAttemptsLeft	= szText[1];
		pOTPSimlockinfo->byteIntervalAttemptsLeft	= szText[2];
		pOTPSimlockinfo->byteHoursLeft		= szText[3];
		pOTPSimlockinfo->byteMinutesLeft	= szText[4];
		pOTPSimlockinfo->byteSecondsLeft	= szText[5];

		pOTPSimlockinfo->structCommonInfo.bValid = 1;
	}

	return bResult;
}

BOOL CSetNVParam::Write_OTP_SIMLockInfo(OTP_SIMLockInfo *pOTPSimlockinfo)
{
	char szText[127] = { 0 };

	szText[0] = pOTPSimlockinfo->byteLockStatus;
	szText[1] = pOTPSimlockinfo->byteSequenceAttemptsLeft;
	szText[2] = pOTPSimlockinfo->byteIntervalAttemptsLeft;
	szText[3] = pOTPSimlockinfo->byteHoursLeft;
	szText[4] = pOTPSimlockinfo->byteMinutesLeft;
	szText[5] = pOTPSimlockinfo->byteSecondsLeft;

	if(WriteFlashQuest(szText,6) == FALSE)
	{
		return FALSE;
	}

	BOOL bResult = Write_Data_By_OTP(GOZONE_NCK_WRITE, 
									&pOTPSimlockinfo->structCommonInfo,
									szText);

	return bResult;
}
BOOL CSetNVParam::Read_OTP_PublicKey(OTP_PublicKey *pOTPPublickey)
{
	char szText[127] = { 0 };

	BOOL bResult = Read_Data_By_OTP(GOZONE_PUBLICKEY_READ, 
									&pOTPPublickey->structCommonInfo,
									szText);

	if (bResult)
	{
		memcpy (pOTPPublickey->bytePublicKey, szText, GOZONE_PUBLICKEY_LEN); //Get the first 74 byte (other bytes are all 0)

		pOTPPublickey->structCommonInfo.bValid = 1;
	}

	return bResult;
}
/*
 *	通过OTP向手机中写入PublicKey
 */
BOOL CSetNVParam::Write_OTP_PublicKey(OTP_PublicKey *pOTPPublickey)
{
	char szText[127] = { 0 };

	memcpy (szText, pOTPPublickey->bytePublicKey, GOZONE_PUBLICKEY_LEN);

	if(WriteFlashQuest(szText,GOZONE_PUBLICKEY_LEN) == FALSE)
	{
		return FALSE;
	}

	BOOL bResult = Write_Data_By_OTP(GOZONE_PUBLICKEY_WRITE, 
									&pOTPPublickey->structCommonInfo,
									szText);
	
	return bResult;
}

//打开网络锁
BOOL CSetNVParam::TurnOnSimLockSwitch(OTP_SimLockSwitch *pOTPSimLockSwitch)
{
	char szText[128] = { 0 };

	memset (szText, 0, 128);

	szText[0] = 1;//Turn on.

	if(WriteFlashQuest(szText,1) == FALSE)
	{
		return FALSE;
	}
	
	BOOL bResult = Write_Data_By_OTP(GOZONE_USIM_SWITCH, 
									&pOTPSimLockSwitch->structCommonInfo,
									szText);
#if 1 //[zhangjj,070612,add for auto sign]
	if (TRUE == bResult) 
	{
		SignNVParam(0, FALSE);
	}
#endif

	return bResult;
}
//关闭网络锁
BOOL CSetNVParam::TurnOffSimLockSwitch(OTP_SimLockSwitch *pOTPSimLockSwitch)
{
	char szText[128] = { 0 };

	memset (szText, 0, 128);

	szText[0] = 0;//Turn off.

	if(WriteFlashQuest(szText,1) == FALSE)
	{
		return FALSE;
	}
	
	BOOL bResult = Write_Data_By_OTP(GOZONE_USIM_SWITCH, 
									&pOTPSimLockSwitch->structCommonInfo,
									szText);
#if 1 //[zhangjj,070612,add for auto sign]
	if (TRUE == bResult) 
	{
		SignNVParam(0, FALSE);
	}
#endif

	return bResult;
}

//打开测试菜单
BOOL CSetNVParam::TurnOnEngineeringSwitch(OTP_EngineeringSwitch *pOTPEnginswitch)
{
	char szText[128] = { 0 };

	memset (szText, 0, 128);

	szText[0] = 0;//Turn on.
	if(WriteFlashQuest(szText,1) == FALSE)
	{
		return FALSE;
	}

	BOOL bResult = Write_Data_By_OTP(GOZONE_ENGINEERING_SWITCH, 
									&pOTPEnginswitch->structCommonInfo,
									szText);

	return bResult;
}
//关闭测试菜单
BOOL CSetNVParam::TurnOffEngineeringSwitch(OTP_EngineeringSwitch *pOTPEnginswitch)
{
	char szText[127] = { 0 };

	memset (szText, 0, 127);

	szText[0] = 1;//Turn off.
	if(WriteFlashQuest(szText,1) == FALSE)
	{
		return FALSE;
	}

	BOOL bResult = Write_Data_By_OTP(GOZONE_ENGINEERING_SWITCH, 
									&pOTPEnginswitch->structCommonInfo,
									szText);

	return bResult;
}

//数据超过120的,采用分包的形式传送
BOOL CSetNVParam::Read_NVItmesPack(int nSubCmd, NVItemsPack *pNVItemsPack)
{
	char szText[127];

	memset (szText, 0, 127);
	memset (pNVItemsPack->data, 0, NV_PACK_MAX_DATA_SIZE);

	BOOL bResult = Read_Data_By_OTP(nSubCmd, 
									&pNVItemsPack->structCommonInfo,
									szText);

	if (bResult)
	{
		pNVItemsPack->TotalPack &= 0;
		pNVItemsPack->TotalPack |= szText[1] & 0xff;
		pNVItemsPack->TotalPack <<=8;
		pNVItemsPack->TotalPack |= szText[0] & 0xff;
		pNVItemsPack->TotalPack &= 0xffff;

		pNVItemsPack->CurrPack &= 0;
		pNVItemsPack->CurrPack |= szText[3] & 0xff;
		pNVItemsPack->CurrPack <<=8;
		pNVItemsPack->CurrPack |= szText[2] & 0Xff;
		pNVItemsPack->CurrPack &= 0xffff;

		pNVItemsPack->len = (byte)szText[4];

		for (byte i = 0; i < pNVItemsPack->len; i++)
		{
			pNVItemsPack->data[i] = (byte)szText[i+5];
		}
		
		pNVItemsPack->structCommonInfo.bValid = 1;
	}

	return bResult;
}
BOOL CSetNVParam::Write_NVItmesPack(int nSubCmd, NVItemsPack *pNVItemsPack)
{
	char szText[127];

	memset (szText, 0, 127);

	szText[0] = (char)(pNVItemsPack->TotalPack & 0xff);
	szText[1] = (char)(pNVItemsPack->TotalPack >> 8 & 0xff);
	szText[2] = (char)(pNVItemsPack->CurrPack & 0xff);
	szText[3] = (char)(pNVItemsPack->CurrPack >> 8 & 0xff);

	szText[4] = (char)pNVItemsPack->len;

	for (byte i = 0; i < pNVItemsPack->len; i++)
	{
		szText[5+i] = pNVItemsPack->data[i];
	}

	BOOL bResult = Write_Data_By_OTP(nSubCmd, 
									&pNVItemsPack->structCommonInfo,
									szText);

	return bResult;
}

//NV数据的导出
INT CSetNVParam::ExportAllNVItemsFromPhone(byte DataBuf[], UINT *pActualBufLenth)
{
	NVItemsPack nvitemspack;
	UINT nTotal = 100, nCurrent = 1;
	byte  byteCurLen;
	UINT nCurrPosi;
	INT   nResult;
	UINT     nCount;

	nCount = 0;
	nCurrPosi = 0;
	byteCurLen = 0;
	while (nTotal > nCurrent)
	{
		nCount++;

		nResult = Read_NVItmesPack(GOZONE_NV_EXPORT,&nvitemspack);

		if (!nResult)
			return -1; 				//Export fail
		
		if (nvitemspack.len == 0)
			return -1;     			//Export fail
		
		if (nvitemspack.CurrPack > nvitemspack.TotalPack)
			return -1;     			//Export fail
			
		if (nCount != nvitemspack.CurrPack)
			return -2;				//Phone isn't at the correct status.

		for (byte i = 0; i < nvitemspack.len; i++)
		{
			DataBuf[nCurrPosi+i] = nvitemspack.data[i];
		}
		nCurrPosi += nvitemspack.len;

		nTotal   = nvitemspack.TotalPack;
		nCurrent = nvitemspack.CurrPack;
	} 
	
	if (nTotal == nCurrent && nvitemspack.len > 0)
	{
		*pActualBufLenth = nCurrPosi;
		return 0;			 		//Export success and write success.
	}
	else
		return -1;				 	//Export fail
}

//NV数据的导入
INT CSetNVParam::ImportAllNVItemsIntoPhone(byte DataBuf[], UINT ActualDataSize)
{
	NVItemsPack CurrNVItemsPack;
	UINT nCurrPosition, nLeftLenth;
	INT nResult;

	CurrNVItemsPack.TotalPack = (UINT)((ActualDataSize / NV_PACK_MAX_DATA_SIZE) & 0xffff);
	if (ActualDataSize % NV_PACK_MAX_DATA_SIZE != 0) CurrNVItemsPack.TotalPack++;
	
	CurrNVItemsPack.CurrPack = 0;
	
	nLeftLenth = ActualDataSize;
	
	nCurrPosition = 0;

	while (nLeftLenth > 0)
	{
		CurrNVItemsPack.CurrPack++;
		
		CurrNVItemsPack.len = (nLeftLenth >= NV_PACK_MAX_DATA_SIZE? NV_PACK_MAX_DATA_SIZE : nLeftLenth);
		
		for (byte i = 0; i < CurrNVItemsPack.len; i++)
		{
			CurrNVItemsPack.data[i] = DataBuf[nCurrPosition+i];
		}

		nResult = Write_NVItmesPack(GOZONE_NV_IMPORT,&CurrNVItemsPack);
		if (!nResult)
			return -1;					//Import fail

		nLeftLenth -= CurrNVItemsPack.len;
		nCurrPosition += CurrNVItemsPack.len;
	}
	
	return 0;
}

BOOL CSetNVParam::SetServerParam(char* IPAddr,char* ProjectName)
{
	int IPLen = 0;
	int NameLen = 0;
	if(IPAddr==NULL || ProjectName==NULL)
	{
		return FALSE;
	}
	IPLen = strlen(IPAddr);
	NameLen = strlen(ProjectName);
	if(IPLen > GOZONE_IP_ADDRESS_SIZE || NameLen>GOZONE_PRJECT_NAME_SIZE)
	{
		return FALSE;
	}

	memset(m_IPAddress,0,GOZONE_IP_ADDRESS_SIZE);
	memset(m_ProjectName,0,GOZONE_PRJECT_NAME_SIZE);

	memcpy(m_IPAddress,IPAddr,IPLen);
	memcpy(m_ProjectName,ProjectName,NameLen);

	return TRUE;
}

//给手机数据签名 PLMN+SIMLckSwitch
BOOL CSetNVParam::SignNVParam(UINT nSerialPort, BOOL forceSign)
{
#if 0
	CommonInfo structCommonInfo;
	TRandom randomData;
	NVItemsPack nvitemspack;
	UINT nTotal = 100, nCurrent = 1;
	byte byteCurLen=0;
	UINT nCurrPosi=0;
	UINT nCount=0;
	char szParam[D_DATA_MAX_SIZE] = { 0 };

	char Signature[127] = { 0 };
	int SigLen = 0;

	//获取签名的原始数据
	while (nTotal > nCurrent)
	{
		nCount++;

		if((Read_NVItmesPack(GOZONE_ORIUNDERWRITEDATA, &nvitemspack) == FALSE)
			|| (nvitemspack.len == 0)
			|| (nCount != nvitemspack.CurrPack)
			|| (nvitemspack.CurrPack > nvitemspack.TotalPack))
		{
			return FALSE;
		}
		
		for (byte i=0; i<nvitemspack.len; i++)
		{
			//超过最大的签名数据就不再读取
			if(nCurrPosi >= D_DATA_MAX_SIZE)
			{
				return FALSE;
			}
			szParam[nCurrPosi++] = nvitemspack.data[i];
		}

		nTotal   = nvitemspack.TotalPack;
		nCurrent = nvitemspack.CurrPack;
	}

	//获取手机的随机值
	if(Read_Random_Data(&randomData) == FALSE)
	{
		return FALSE;
	}

#if 0	// zhangjj del asc.dll 100317
	if (m_pHMacProc == NULL)
	{
		return FALSE;
	}

	m_pHMacProc(m_IPAddress, m_ProjectName,
			(char*)randomData.byteRandom, sizeof(randomData.byteRandom),
			szParam, nCurrPosi,
			Signature, D_SIGNATURE_SIZE, &SigLen);

	if (SigLen==0 && forceSign==TRUE)
	{
		return FALSE;
	}
#endif

	//写入签名数据
	if(Write_Data_By_OTP(GOZONE_UNDERWRITEDATA_WRITE,&structCommonInfo,Signature) == FALSE)
	{
		return FALSE;
	}
#endif
	return TRUE;
}


#define NV_WCDMA_1900_HDET_OFF	1187
BOOL CSetNVParam::Get_HDET_OFF(char *pHdetOff)
{
    char szITEM_DATA[NV_ITEMDATA_LEN];
    char chResponseCommand = 0; 
    BOOL bResult = FALSE;
	word wStatus;
    
    memset(szITEM_DATA, 0, NV_ITEMDATA_LEN);
    bResult = m_SerialPort.Read_NV_ITEM_DATA(NV_WCDMA_1900_HDET_OFF,
											szITEM_DATA, 
											&chResponseCommand,
											&wStatus);
	*pHdetOff = szITEM_DATA[0];
    
    bResult = bResult && (wStatus == 0);
    
    return bResult;
}

#define NV_WCDMA_1900_HDET_SPN	1188
BOOL CSetNVParam::Get_HDET_SPN(char *pHdetSpn)
{
	char szITEM_DATA[NV_ITEMDATA_LEN];
	char chResponseCommand = 0;
	BOOL bResult = FALSE;
	word wStatus;
    
    memset(szITEM_DATA, 0, NV_ITEMDATA_LEN);
    bResult = m_SerialPort.Read_NV_ITEM_DATA(NV_WCDMA_1900_HDET_SPN,
											szITEM_DATA, 
											&chResponseCommand,
											&wStatus);
	*pHdetSpn = szITEM_DATA[0];
    
    bResult = bResult && (wStatus == 0);
    
    return bResult;
}

BOOL CSetNVParam::ErasureOTP()
{
	CommonInfo structCommonInfo;
	OTP_PublicKey otp_PublicKey = {0};

	//读取Public Key
	if(Read_OTP_PublicKey(&otp_PublicKey) == FALSE)
	{
		return FALSE;
	}

	//用Public Key 来签名
	if(WriteFlashQuest((char*)otp_PublicKey.bytePublicKey,GOZONE_PUBLICKEY_LEN) == FALSE)
	{
		return FALSE;
	}

	return Write_Data_By_OTP(GOZONE_ERASUREOTP, &structCommonInfo,NULL);
}

// 从手机读取随机值
BOOL CSetNVParam::Read_Random_Data(TRandom *pRandomData)
{
	char szText[127] = { 0 };

	BOOL bResult = Read_Data_By_OTP(GOZONE_PHONEID_READ, 
									&pRandomData->structCommonInfo,
									szText);
	
	if (bResult)
	{
		int i = 0;

		for (i = 0; i < GOZONE_DCKHASH_LEN; i++)		// 填充dck
		{
			pRandomData->byteRandom[i] = szText[i];
		}
		pRandomData->structCommonInfo.bValid = 1;
	}

	return bResult;
}


// 测试是否能连接服务器签名
BOOL CSetNVParam::Test_Sign_Client()
{
#if	0	//[zhangjj,del for no use now,100707]
	char Signature[127] = { 0 };
	int SigLen = 0;
	
	char key[] =	{
						0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A,
						0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32,
						0x33, 0x34, 0x35, 0x36
					};
	
	char Data[] =	{
						0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62,
						0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A,
						0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72,
						0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A
					};

	if (m_pHMacProc == NULL)
	{
		return FALSE;
	}
	
	m_pHMacProc(m_IPAddress, m_ProjectName,
		key, sizeof(key),
		Data, sizeof(Data),
		Signature, D_SIGNATURE_SIZE, &SigLen);
	
	if (SigLen==0)
	{
		return FALSE;
	}
#endif
	return TRUE;
}

/*
 *	通过OTP向手机中读取ESN
 */
BOOL CSetNVParam::Read_OTP_ESN(OTP_ESN *pOTPEsn)
{
	int i;
	char szText[128] = { 0 };
	byte asc_1,asc_2;
	int Index=0;

	BOOL bResult = Read_Data_By_OTP(GOZONE_ESN_READ, 
									&pOTPEsn->structCommonInfo,
									szText);

	if (bResult)
	{
		for(i=GOZONE_ESN_SIZE-1; i>=0; i--)
		{
			asc_1 = (szText[i]&0xF0)>>4;	//高位
			asc_2 = szText[i]&0x0F;			//低位
			pOTPEsn->szESN[Index++] = (asc_1 <= 9) ? (asc_1+'0') :(asc_1-10+'A');
			pOTPEsn->szESN[Index++] = (asc_2 <= 9) ? (asc_2+'0') :(asc_2-10+'A');
		}
		pOTPEsn->szESN[Index] = 0;

		pOTPEsn->structCommonInfo.bValid = 1;
	}

	return bResult;
}
/*
 *	通过OTP向手机中写入ESN
 */
BOOL CSetNVParam::Write_OTP_ESN(OTP_ESN *pOTPEsn)
{
	int i;
	char szText[127]	= { 0 };
	char szESN[GOZONE_ESN_SIZE*2+1] = { 0 };

	for(i=0; i<GOZONE_ESN_SIZE*2; i++)
	{
		if(pOTPEsn->szESN[i]>='0' && pOTPEsn->szESN[i]<= '9')
		{
			szESN[i] = pOTPEsn->szESN[i] - '0';
		}
		else if(pOTPEsn->szESN[i]>='a' && pOTPEsn->szESN[i]<= 'f')
		{
			szESN[i] = pOTPEsn->szESN[i] - 'a' + 0x0A;
		}
		else if(pOTPEsn->szESN[i]>='A' && pOTPEsn->szESN[i]<= 'F')
		{
			szESN[i] = pOTPEsn->szESN[i] - 'A' + 0x0A;
		}
		else
		{
			szESN[i] = 0x0F;
		}
	}
	for(i=GOZONE_ESN_SIZE-1; i>=0; i--)
	{
		szText[GOZONE_ESN_SIZE-i-1] = ((szESN[i*2]&0x0F)<<4) + (szESN[i*2 + 1]&0x0F);
	}

	if(WriteFlashQuest(szText,GOZONE_ESN_SIZE) == FALSE)
	{
		return FALSE;
	}

	BOOL bResult = Write_Data_By_OTP(GOZONE_ESN_WRITE, 
									&pOTPEsn->structCommonInfo,
									szText);

	return bResult;
}

/*
 *	向手机发送备份NV命令
 */
BOOL CSetNVParam::CmdNVBackup(OTP_NVBackupRestore *pOTPNVBackupRestore)
{
	return Write_Data_By_OTP(GOZONE_NV_BACKUP, &pOTPNVBackupRestore->structCommonInfo,NULL);
}

/*
 *	向手机发送恢复NV命令
 */
BOOL CSetNVParam::CmdNVRestore(OTP_NVBackupRestore *pOTPNVBackupRestore)
{
	return Write_Data_By_OTP(GOZONE_NV_RESTORE, &pOTPNVBackupRestore->structCommonInfo,NULL);
}


BOOL CSetNVParam::Read_OTP_MEID(OTP_MEID *pOTPMeid)
{
	int i;
	char szText[128] = { 0 };
	byte asc_1,asc_2;
	int Index=0;
	
	BOOL bResult = Read_Data_By_OTP(GOZONE_MEID_READ, &pOTPMeid->structCommonInfo, szText);
	
	if (bResult)
	{
		/* 
		 *	zhangjj : 多一个 -1 因为OTP中MEID存储的16bytes，而实际只用14bytes，不改成14bytes，是为了和高通的处理机制统一
		*/

		for (i=GOZONE_MEID_SIZE-1-1; i>=0; i--)
		{
			asc_1 = (szText[i]&0xF0)>>4;	//高位
			asc_2 = szText[i]&0x0F;			//低位
			pOTPMeid->szMEID[Index++] = (asc_1 <= 9) ? (asc_1+'0') :(asc_1-10+'A');
			pOTPMeid->szMEID[Index++] = (asc_2 <= 9) ? (asc_2+'0') :(asc_2-10+'A');
		}
		pOTPMeid->szMEID[Index] = 0;
		
		pOTPMeid->structCommonInfo.bValid = 1;
	}
	return bResult;
}

BOOL CSetNVParam::Write_OTP_MEID(OTP_MEID *pOTPMeid)
{
	int i;
	char szText[127]	= { 0 };
	char szMEID[GOZONE_MEID_SIZE*2+1] = { 0 };
	
	for(i=0; i<GOZONE_MEID_SIZE*2; i++)
	{
		if(pOTPMeid->szMEID[i]>='0' && pOTPMeid->szMEID[i]<= '9')
		{
			szMEID[i] = pOTPMeid->szMEID[i] - '0';
		}
		else if(pOTPMeid->szMEID[i]>='a' && pOTPMeid->szMEID[i]<= 'f')
		{
			szMEID[i] = pOTPMeid->szMEID[i] - 'a' + 0x0A;
		}
		else if(pOTPMeid->szMEID[i]>='A' && pOTPMeid->szMEID[i]<= 'F')
		{
			szMEID[i] = pOTPMeid->szMEID[i] - 'A' + 0x0A;
		}
		else
		{
			szMEID[i] = 0x0F;
		}
	}
	for(i=GOZONE_MEID_SIZE-1; i>0; i--)
	{
		szText[GOZONE_MEID_SIZE-i-1] = ((szMEID[(i-1)*2]&0x0F)<<4) + (szMEID[(i-1)*2 + 1]&0x0F);
	}
	
	if(WriteFlashQuest(szText,GOZONE_MEID_SIZE) == FALSE)
	{
		return FALSE;
	}
	
	return Write_Data_By_OTP(GOZONE_MEID_WRITE, &pOTPMeid->structCommonInfo, szText);
}

