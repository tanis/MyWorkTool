/*--------------------------------------------------------
Desc:   define APST Download types
Author:  wuchunpeng
Date:   2006.7.13
Notes:  

$Log: DLTypedef.h,v $
Revision 1.1.1.3  2007/07/03 07:54:04  zhangjj
增加设备列表配置

Revision 1.1.1.6  2007/04/19 09:12:22  wucp
增加了设备列表配置功能

Revision 1.1.1.5  2007/03/14 01:58:05  wucp
增加下载进度平滑显示以及获得手机信息功能

Revision 1.1.1.4  2007/01/29 02:52:37  wucp
增加了对6245平台的支持

Revision 1.1.1.3  2006/07/21 00:44:23  wucp
增加 IMAGE_INFO_POS 定义

Revision 1.1.1.2  2006/07/17 03:31:10  wucp
支持通用的 PRG，能够识别 ImgFile 的信息块。

Revision 1.1.1.1  2006/07/13 01:57:24  wucp
导入初始模块

Revision 1.1.1.2  2007/06/12 02:11:06  zhangjj
初始版本
--------------------------------------------------------*/
#ifndef _DL_TYPEDEF_H_
#define _DL_TYPEDEF_H_

#include <windows.h>
#include "ErrorCode.h"

#ifndef byte
typedef unsigned char byte;
#endif

typedef int TComId;  // com port id


#define D_PRJ_NAME_SIZE  32  // project name size
// image info position relative to data end.
#define IMAGE_INFO_POS  (64 + 512 + 512)
#define D_WRITE_FLASH_SCALE		20 // 数据在手机中写入Flash所需时间在整个下载过程中的比例.
#define D_WRITE_FLASH_SIZE_AT_TIME		(512*1024) // 每次写入Flash的数据长度 512KB
#define GOZONE_MAGIC1		0x55E3DB66
#define GOZONE_MAGIC2		0xcc55AA73

// for Qualcomm 6250A platform
#define BOOT_IMAGE		0x76ac91c0		
#define AMSS_IMAGE		0xbcff9900
#define EFS_IMAGE		0xe0117789

// for Qualcomm 6245 platform
#define AMSS_IMAGE_6245		0x9e672dad
#define BOOT_IMAGE_6245		0x1444d65f
#define EFS_IMAGE_6245		0xdbf97ca6
#define OEMSBL_IMAGE_6245	0x2f54aa1f

struct tagTCbInfo;

// Call back function prototype
typedef void (TCbProgressProc)(struct tagTCbInfo *pTCbInfo);
//typedef void (TCbInitProc)(TDLDeviceInfo* pDevInfo, struct tagTCbInfo *pTCbInfo);

typedef struct tagTCbInfo
{
	size_t   Size;
	TCbProgressProc* pProgressProc;   // Call back function pointer
	size_t   nTotal;    // Total of data. (byte)
	size_t   nSent;     // Sent data length (byte)
	size_t   nPercent;	//  Account percent
	void*    pUserData; // for user data
} TDLCbInfo;

typedef struct
{
	byte*  pData;
	size_t Len;
} TDLData;

typedef struct
{
	int			Magic1;	   			/* MAGIC1 */
	int			Magic2;	   			/* MAGIC2 */
	int			ImageType;			/*image type*/
	char		ProjectName[D_PRJ_NAME_SIZE]; 	/*project name*/
	int			MajorVersion;	 	/* major version number */
	int			MinorVersion;	 	/* minor version number */
	int			FlashAddr;	     	/* Start address in FLASH*/
	int			Length;	         	/* length of image (exclude image info)*/
	int			Checksum;		   	/* check sum of device info */
} TDLImageInfo;

typedef TDLImageInfo TDLDeviceInfo;


#define DLGetValidComPortName  "GetValidComPort"
typedef int (TDLGetValidComPortProc)(TComId *pComIdBuf, size_t ComIdBufSize);

#define InitDeviceItemName "InitDeviceItem"
typedef BOOL (TInitDeviceItem)(const char* pItemListBuf, int BufLen);

// if pCbInfo == NULL , then not execute call back function
typedef struct
{
	size_t Size;		// must equal sizeof(self)
	TComId ComId;		// com port id
	TDLData Prg;
	TDLData ImgData;
} TDLDataInfo;

#define DLProcName  "APSTDownload"
typedef TResult (TDLProc)(TDLDataInfo* pDLInfo,
							TDLCbInfo* pCbInfo);

#define DLGetDevInfoProcName "APSTGetDeviceInfo"
typedef TResult (TDLGetDeviceInfoProc)(TComId Com,
							TDLDeviceInfo* pDevInfo);

#endif //_DL_TYPEDEF_H_

