
/*--------------------------------------------------------

Desc:   APST Download Error Codes

Author:  wuchunpeng
Date:   2006.7.13
Notes:  

$Log: ErrorCode.h,v $
Revision 1.1.1.2  2007/06/12 02:11:06  zhangjj
初始版本

Revision 1.1.1.2  2006/07/17 03:31:40  wucp
增加了ImgFile无效的错误码

Revision 1.1.1.1  2006/07/13 01:57:24  wucp
导入初始模块


--------------------------------------------------------*/

#ifndef _ERROR_CODE_H_
#define _ERROR_CODE_H_

typedef enum
{
	E_OK = 0,
	E_FAILED,
	E_PARAM_INVALID,		// if the parameters are NULL or length == 0;
// port error
	E_PORT_OPEN,
	E_PORT_SEND,
	E_PORT_SEND_TIMEOUT,
	E_PORT_RECEIVE,
	E_PORT_RECEIVE_TIMEOUT,
	E_PORT_CLOSE,

// packet error
	E_PACKET_RECEIVE_TOO_LARGE,
	E_PACKET_RECEIVE_TOO_SHORT,
	E_PACKET_RECEIVE_CRC,

	E_PACKET_SEND,

// prg download command error
	E_ACK_PACKET,  // can not receive a ack packte, (ACK or NAK)
	E_ACK_FAILED,  // receive a NAK cmd

// data download command error
	E_DATA_RSP,
	E_DATA_CRC,

// Image error
	E_IMAGE_FAILED,

	E_END
} TResult;

#endif //_ERROR_CODE_H_
