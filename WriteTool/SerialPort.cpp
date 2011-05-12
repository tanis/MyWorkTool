/*
File: SerialPort.cpp
Desc: 

Author: zjj
Date  : 2007.3.14
Notes : 串口操作

   $Source: D:/cvsrepo/DllParam/SerialPort.cpp,v $

$Log: SerialPort.cpp,v $
Revision 1.1.1.1  2007/03/14 07:26:48  zhangjj
导入初始版本


*/

#include "stdafx.h"
#include "SerialPort.h"

#include "log.h"

unsigned short crc_16_ccitt_calc(const char *buf_ptr, unsigned short len);

const int XmitBufSize = 4096;
const int RcvBufSize = 4096;

/* CRC table for 16 bit CRC, with generator polynomial 0x8408,
 * calculated 8 bits at a time, LSB first.  This table is used
 * from a macro in sio.c.
 */
static const word crc_16_l_table[ CRC_TAB_SIZE ] = {
  0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
  0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
  0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
  0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
  0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
  0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
  0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
  0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
  0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
  0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
  0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
  0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
  0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
  0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
  0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
  0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
  0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
  0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
  0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
  0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
  0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
  0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
  0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
  0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
  0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
  0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
  0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
  0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
  0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
  0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
  0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
  0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};

CSerialPort::CSerialPort()
{
	m_ov.Offset = 0;
	m_ov.OffsetHigh = 0;
	m_ov.hEvent = NULL;

	m_hComm = NULL;
	m_nPort = 0;
}

CSerialPort::~CSerialPort()
{
    Close();
}

/*
 * CRC checkout
 */
unsigned short crc_16_ccitt_calc(const char *buf_ptr, unsigned short len)
{
  unsigned short data, crc_16;
  for (crc_16 = CRC_16_L_SEED ; len >= 8; len -= 8, buf_ptr++) {
    crc_16 = crc_16_l_table[ (crc_16 ^ *buf_ptr) & 0x00ff ] ^ (crc_16 >> 8);
  }
  if (len != 0) {
    data = ((unsigned short) (*buf_ptr)) << (16-8);
    while (len-- != 0) {
      if ( ((crc_16 ^ data) & 0x01) != 0 ){
        crc_16 >>= 1;
        crc_16 ^= CRC_16_L_POLYNOMIAL;
      } else {
        crc_16 >>= 1;
      }
      data >>= 1;
    }
  }
  return( ~crc_16 );
}

/*
 * process every byte to judge whether string is end.
 */
BOOL CSerialPort::ProcessByte(char **RPtr, char Byte, PT_PROTOCOLSTATE *Protocol)
{
	if (Protocol->ESCFound)
	{
		*(*RPtr)++ = ( Byte ^ CHAR_ESCAPE_XOR);
		Protocol->ESCFound = FALSE;
	}
	else if (Byte == CHAR_ESCAPE_FLAG)
	{
	  Protocol->ESCFound = TRUE;
	}
	else if (Byte != CHAR_ENDING_FLAG)
	{
		*(*RPtr)++ = Byte;
	}
	else
	{
		*(*RPtr)++ = CHAR_ENDING_FLAG;
		return TRUE;		// packet End FLAG
	}
	return FALSE;			// packet isn't End
}
BOOL CSerialPort::DLProcessByte(char **RPtr, char Byte, PT_PROTOCOLSTATE *Protocol)
{
   	if ( Protocol->HDRFound )
   	{
   		if ( Protocol->ESCFound )
   		{
      		*(*RPtr)++ = ( Byte ^ CHAR_ESCAPE_XOR );
      		Protocol->ESCFound = FALSE;
   		}
   		else if ( Byte == CHAR_ESCAPE_FLAG )
   		{
      		Protocol->ESCFound = TRUE;
   		}
   		else if ( Byte != CHAR_ENDING_FLAG )
      		*(*RPtr)++ = Byte;
   		else
   		{
      		*(*RPtr)++ = CHAR_ENDING_FLAG;
      		return TRUE;  // End of a packet
   		}
   	}
   	else if ( Byte == CHAR_ENDING_FLAG ) 
   		Protocol->HDRFound = TRUE;
   
   return FALSE;    // Not yet at the end of a packet
}

/*
 * Set baud
 */
BOOL CSerialPort::SetSerialPort( int nBaud, 
                                 int nParity, 
                                 int nStopbits, 
                                 int nDatabits, 
                                 int nTimeout) 
{
	DCB				dcb;
	COMMPROP 		cp;
	COMMCONFIG 		cc;
	COMMTIMEOUTS 	to;
	unsigned long	lrc;

    m_lTimeout = nTimeout;
	if (!PurgeComm(m_hComm,	PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR))
		return OPTISER_FAILURE;

	dcb.DCBlength = sizeof(DCB);

	if (!GetCommState(m_hComm, &dcb))
		return OPTISER_FAILURE;

	// Get Comm Properties
	cp.wPacketLength = sizeof(COMMPROP);
	GetCommProperties(m_hComm, &cp);

	// Select Comm Baudrate w/ n,8,1
	lrc = sizeof(COMMCONFIG);
	GetCommConfig(m_hComm, &cc, &lrc);
	dcb = cc.dcb;
	dcb.DCBlength = sizeof(DCB);

	// Set baudrate
	dcb.BaudRate 	= nBaud;
	dcb.Parity 		= nParity;
	dcb.ByteSize 	= nDatabits;
	dcb.StopBits 	= nStopbits;


	dcb.fOutxCtsFlow 		= FALSE;
	dcb.fOutxDsrFlow 		= FALSE;
	dcb.fDtrControl 		= DTR_CONTROL_DISABLE;
	dcb.fRtsControl 		= RTS_CONTROL_DISABLE;
	dcb.fDsrSensitivity 	= FALSE;
	dcb.fTXContinueOnXoff 	= FALSE;
	dcb.fOutX 				= FALSE;
	dcb.fInX 				= FALSE;

	if (!SetCommState(m_hComm, &dcb)) 
	{
		return OPTISER_FAILURE;
	}

	if (!GetCommTimeouts(m_hComm, &to)) 
	{
		return OPTISER_FAILURE;
	}
	else 
	{
		to.ReadIntervalTimeout = nTimeout;
		to.ReadTotalTimeoutMultiplier = nTimeout;
		to.ReadTotalTimeoutConstant = nTimeout;
		to.WriteTotalTimeoutMultiplier = nTimeout;
		to.WriteTotalTimeoutConstant = nTimeout;
	}
	if (!SetCommTimeouts(m_hComm, &to)) 
	{
		return OPTISER_FAILURE;
	}
	
	TRACE("baud=%d parity=%d data=%d stop=%d\n", nBaud, nParity, nDatabits, nStopbits);

	return OPTISER_SUCCESS;
}

/*
 * initialize port
 */
BOOL CSerialPort::InitSerialPort(UINT uPort, 
                                 int nBaud, 
                                 int nParity, 
                                 int nStopbits, 
                                 int nDatabits, 
                                 int nTimeout)
{
    if (uPort <= 0)
        return OPTISER_FAILURE;

    Close();

	char  sComPort[20]="";
	DCB				dcb;
	COMMPROP 		cp;
	COMMCONFIG 		cc;
	COMMTIMEOUTS 	to;
	unsigned long	lrc;
	
	m_nPort = uPort;
	m_lTimeout = nTimeout;
    
    sprintf(sComPort, "\\\\.\\COM%d", uPort); 
	//sprintf(&(sComPort[3]), "%d", uPort); 

	m_hComm = CreateFile(sComPort, 
                        GENERIC_READ | GENERIC_WRITE, 
                        0, 
                        NULL, 
		                OPEN_EXISTING, 
                        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, //change to 0;
                        NULL);

	if (m_hComm == INVALID_HANDLE_VALUE) 
    {
        DWORD d = GetLastError();
        if (d == ERROR_FILE_NOT_FOUND) 
        {
            TRACE("serialport error!\n"); 
        }
      	return OPTISER_FAILURE;
    }

	m_ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (!SetCommMask(m_hComm, EV_RXCHAR))
		return OPTISER_FAILURE;
		
	if (!SetupComm(m_hComm, RcvBufSize, XmitBufSize ))
		return OPTISER_FAILURE;
		
	if (!PurgeComm(m_hComm,	PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR))
		return OPTISER_FAILURE;

	dcb.DCBlength = sizeof(DCB);

	if (!GetCommState(m_hComm, &dcb))
		return OPTISER_FAILURE;

	// Get Comm Properties
	cp.wPacketLength = sizeof(COMMPROP);
	GetCommProperties(m_hComm, &cp);

	// Select Comm Baudrate w/ n,8,1
	lrc = sizeof(COMMCONFIG);
	GetCommConfig(m_hComm, &cc, &lrc);
	dcb = cc.dcb;
	dcb.DCBlength = sizeof(DCB);

	// Set baudrate
	dcb.BaudRate 	= nBaud;
	dcb.Parity 		= nParity;
	dcb.ByteSize 	= nDatabits;
	dcb.StopBits 	= nStopbits;


	dcb.fOutxCtsFlow 		= FALSE;
	dcb.fOutxDsrFlow 		= FALSE;
	dcb.fDtrControl 		= DTR_CONTROL_DISABLE;
	dcb.fRtsControl 		= RTS_CONTROL_DISABLE;
	dcb.fDsrSensitivity 	= FALSE;
	dcb.fTXContinueOnXoff 	= FALSE;
	dcb.fOutX 				= FALSE;
	dcb.fInX 				= FALSE;

	if (!SetCommState(m_hComm, &dcb)) 
	{
		return OPTISER_FAILURE;
	}

	if (!GetCommTimeouts(m_hComm, &to)) 
	{
		return OPTISER_FAILURE;
	}
	else 
	{
		to.ReadIntervalTimeout = nTimeout;
		to.ReadTotalTimeoutMultiplier = nTimeout;
		to.ReadTotalTimeoutConstant = nTimeout;
		to.WriteTotalTimeoutMultiplier = nTimeout;
		to.WriteTotalTimeoutConstant = nTimeout;
	}
	if (!SetCommTimeouts(m_hComm, &to)) 
	{
		return OPTISER_FAILURE;
	}
	
	TRACE("baud=%d parity=%d data=%d stop=%d\n", nBaud, nParity, nDatabits, nStopbits);

	return OPTISER_SUCCESS;
}

/*
 * close com port
 */
BOOL CSerialPort::Close()
{
    if (NULL == m_hComm || INVALID_HANDLE_VALUE == m_hComm) 
        return OPTISER_FAILURE;

	PurgeComm(m_hComm, PURGE_RXCLEAR|PURGE_TXCLEAR); 
	SetCommMask(m_hComm, 0 );  // Forces the WaitCommEvent to return
   			
	CloseHandle(m_hComm);
	m_hComm = NULL;

    if (m_ov.hEvent != NULL) 
    {
        CloseHandle(m_ov.hEvent);
        m_ov.hEvent = NULL;
    }

	return OPTISER_SUCCESS;
}

/*
 * send data to com
 */
BOOL CSerialPort::SerialPortSendData(char *pBuff, long lSize, long *pCount)
{
    if (NULL == m_hComm || INVALID_HANDLE_VALUE == m_hComm) 
        return OPTISER_FAILURE;
    
    DWORD BytesSent = 0;
    
    COMSTAT cs;
    
    //if (!WriteFile(m_hComm, pBuff, lSize, (LPDWORD) (pCount), &m_osWrite))
    PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
    if (!WriteFile(m_hComm,							        // Handle to COMM Port
        pBuff,							        // Pointer to message buffer in calling finction
        lSize,							        // Length of message to send
        &BytesSent,						        // Where to store the number of bytes sent
        &m_ov))						            // Overlapped structure
    {
        if (GetLastError() != ERROR_IO_PENDING) { 
            
            // WriteFile failed, but it isn't delayed. Report error and abort.
            ClearCommError(m_hComm, &BytesSent, &cs);
            
            TRACE("SerialPortSendData: Write failed on COM%d\n", m_nPort);
            return OPTISER_FAILURE;
        }
        else {
            // Write is pending.
            if (!GetOverlappedResult(m_hComm, &m_ov, &BytesSent, TRUE))
                // Write operation occur error.
                return OPTISER_FAILURE;
        }	
    } 
    
    *pCount = BytesSent;
    
    return OPTISER_SUCCESS;
}

/*
 * reveive data from com
 */
BOOL CSerialPort::SerialPortReceiveData(char *pBuff, long lSize, long *pCount)
{
    // Device removed, return immediately
    if (NULL == m_hComm || INVALID_HANDLE_VALUE == m_hComm) 
        return OPTISER_FAILURE;
    
    BOOL bResult = OPTISER_FAILURE;
    
    COMSTAT cs;
    unsigned long lHasRead = 0, dwError = 0;
    
    if (!ReadFile(m_hComm, pBuff, lSize, &lHasRead, &m_ov))
    {
        if (GetLastError() != ERROR_IO_PENDING) { 
            // ReadFile failed, but it isn't delayed. Report error and abort.
            ClearCommError(m_hComm, &lHasRead, &cs);
            
            TRACE("SerialPortReceiveData: Read failed on COM%d\n", m_nPort);
            return OPTISER_FAILURE;
        }
        else {
            // Read is pending.
            if (!GetOverlappedResult(m_hComm, &m_ov, &lHasRead, TRUE))
            {
                // Read operation occur error.
                TRACE("Pending error\n");
                return OPTISER_FAILURE;
            }
        }	
    } 
    else if (lHasRead != (unsigned long)lSize) 
        return OPTISER_FAILURE;
    
    *pCount = lHasRead;	
    bResult = OPTISER_SUCCESS;
    
    return bResult;
}

/*
 * get time of out
 */
BOOL CSerialPort::SerialPortGetTimeout(long *pTimeout )
   /* Access function. Returns the timeout for a particular device. */
{
	*pTimeout = m_lTimeout;

	return OPTISER_SUCCESS;
}

/*
 * clear com buffer
 */
BOOL CSerialPort::Clear()
{
	if (!PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR)) 
    {
        TRACE("PurgeComm Error!\n"); 
    }

	if (FlushFileBuffers(m_hComm) == 0)
	  return OPTISER_FAILURE;

	return OPTISER_SUCCESS;
}

/*
 * pack is complete
 */
BOOL CSerialPort::GetResult( char * pResultBuffer, char * pRPtr, char * pResultString )
{
	long i = 0;
	long length = pRPtr - pResultBuffer;
	unsigned short crc = 0;
   
	if (length < 3)
		return OPTISER_FAILURE;
	
	length -= 1;			// remove 1 byte ENDING_FLAG
	
	crc = crc_16_ccitt_calc(pResultBuffer, length * 8);
	
	if (crc != CRC_16_L_OK)
		return OPTISER_FAILURE;	
	
	length -= 2;		    // remove 2 bytes CRC
	
	pResultString[0] = (char)(length & 0x00ff);
	pResultString[1] = (char)((length >> 8) & 0x00ff);
	
	for (i = 0; i < length; i++)
		pResultString[i+2] = pResultBuffer[i];
	
	//for (int j = 0; j < 128; j++)
	//	TRACE("%0x ", (unsigned char)pResultString[j]);
	//TRACE("\n");

    return OPTISER_SUCCESS;
}
BOOL CSerialPort::DLGetResult(char * ResultBuffer, char * RPtr, char * ResultString)
{
    long i;
    long length = RPtr - ResultBuffer;
    unsigned short crc;

    if (length < 3)
	    return OPTISER_FAILURE;
	    
    length -= 1;			// remove 1 byte ENDING_FLAG

    crc = crc_16_ccitt_calc(ResultBuffer, length * 8);

    if (crc != CRC_16_L_OK)
	    return OPTISER_FAILURE;	

    length -= 2;		    // remove 2 bytes CRC

    ResultString[0] = (char)( length & 0x00ff );
    ResultString[1] = (char)(( length >>8 )& 0x00ff );

    for(i=0; i < length; i++)
	    ResultString[i+2] = ResultBuffer[i];	

    return OPTISER_SUCCESS;
}

/*
 * format pack
 */
void CSerialPort::FormatCommand(const char *pCommandString, char * pCommandBuffer, long *pLength)
{
	char *pCPtr = pCommandBuffer;
	unsigned int i = 0, len = 0, k = 0;
	char Ch = 0;
	unsigned short uCrc = 0;
   
	k = pCommandString[1];
	len = (k & 0xff);
	len <<= 8;
	k = pCommandString[0];
	len |= (k & 0xff);

	uCrc = crc_16_ccitt_calc( &(pCommandString[2]), len * 8);
   
   //*CPtr++ = THMS_CT_STRING_TAG; // First byte in message
	for (i = 0; i < len + 2; i++)  // 2 bytes for CRC
	{
		if(i - len == 0 )
			Ch = (char)((uCrc & 0x00ff));
		else if (i - len == 1)
			Ch = (char)((uCrc >> 8) & 0x00ff);
		else
			Ch = pCommandString[i+2];
    
		if (Ch == CHAR_ENDING_FLAG || Ch == CHAR_ESCAPE_FLAG)
		{
			*pCPtr++ = CHAR_ESCAPE_FLAG;
			*pCPtr++ = (Ch ^ CHAR_ESCAPE_XOR);
		}
		else
			*pCPtr++ = Ch;
	}
   
	*pCPtr++ = CHAR_ENDING_FLAG;

	*pLength = pCPtr - pCommandBuffer;
	return;
}

/*
 * Download
 */
void CSerialPort::DLFormatCommand(const char *CommandString, char *CommandBuffer, long *Length)
{
   char *CPtr = CommandBuffer;
   unsigned int i, len, k;
   char Ch;
   unsigned short crc;
   
	k = CommandString[1];
	len = ( k & 0xff );
	len <<= 8;
	k = CommandString[0];
	len |= ( k & 0xff );
	
	crc = crc_16_ccitt_calc(&(CommandString[2]), len * 8);
   
   *CPtr++ = CHAR_ENDING_FLAG; // First byte in message
   
   for ( i = 0; i < len+2; i++ )  // 2 bytes for CRC
   {
      if( i-len==0 )
      		Ch = (char)((crc & 0x00ff));
      else if( i-len==1 )
      		Ch = (char)( ( crc >> 8 ) & 0x00ff );
      else
      		Ch = CommandString[ i+2 ];
      		
      if ( Ch == CHAR_ENDING_FLAG || Ch == CHAR_ESCAPE_FLAG )
      {
         *CPtr++ = CHAR_ESCAPE_FLAG;
         *CPtr++ = ( Ch ^ CHAR_ESCAPE_XOR );
      }
      else
      	*CPtr++ = Ch;
   }
   
   *CPtr++ = CHAR_ENDING_FLAG;

   *Length = CPtr - CommandBuffer;
   return;
}

/*
 * send a command && receive a result
 */
BOOL CSerialPort::CommandResponse(char * pCommandString, char *pResultString)
{
    if (NULL == m_hComm || INVALID_HANDLE_VALUE == m_hComm) 
    {
        return OPTISER_FAILURE;
    }

	char szCommandBuffer[512] = "";
	long Length = 0, lCount = 0;

	Clear();
   
	int i = 0;
	FormatCommand(pCommandString, szCommandBuffer, &Length);
	if (SerialPortSendData(szCommandBuffer, Length, &lCount) == OPTISER_FAILURE) 
	{
		i++;
		TRACE("第%d错误\n", i);
   		if (SerialPortSendData(szCommandBuffer, Length, &lCount) == OPTISER_FAILURE) 
		{
			i++;
			TRACE("第%d错误\n", i);
			if (SerialPortSendData(szCommandBuffer, Length, &lCount) == OPTISER_FAILURE) 
			{
				i++;
				TRACE("第%d错误\n", i);
   				return OPTISER_FAILURE;
			}
		}
	}

	if (GetResponse(pResultString, 0L) == OPTISER_SUCCESS) 
		return OPTISER_SUCCESS;
	else
		return OPTISER_FAILURE;
}

BOOL CSerialPort::DLCommandResponse(const char * CommandString, char *ResultString)
{
   char CommandBuffer[8192] = "";
   long Length, Count;

   DLFormatCommand(CommandString, CommandBuffer, &Length);
   if (SerialPortSendData(CommandBuffer, Length, &Count ) == OPTISER_FAILURE )
   		if (SerialPortSendData(CommandBuffer, Length, &Count ) == OPTISER_FAILURE )
   			if (SerialPortSendData(CommandBuffer, Length, &Count ) == OPTISER_FAILURE )
   				return OPTISER_FAILURE;
   				
      if ( DLGetResponse(ResultString, 0L) == OPTISER_SUCCESS )
      		return OPTISER_SUCCESS;
   		else
      		return OPTISER_FAILURE;
}

/*
 * call GetResult, to get "pResultString"
 */
BOOL CSerialPort::GetResponse(char *pResultString, long lTimeout)
{
	long lCount = 0, lMSecsExpired = 0L;
	BOOL bResultFound = FALSE;

	char szResultBuffer[BUF_LEN] = "";
	char *pRPtr = szResultBuffer;

	PT_PROTOCOLSTATE Protocol = { FALSE, FALSE };
	char Buf[2] = "";

	clock_t StartTime = clock();
	clock_t CurrTime;

	if (lTimeout == 0)
		SerialPortGetTimeout(&lTimeout);

	while (!(bResultFound || (lMSecsExpired > lTimeout)))
	{
        // Device removed, return immediately
        if (NULL == m_hComm || INVALID_HANDLE_VALUE == m_hComm) 
            return OPTISER_FAILURE;
        
		if (SerialPortReceiveData(Buf, 1, &lCount) >= OPTISER_SUCCESS)
		{
			if (lCount == 1)
			{
				if (ProcessByte( &pRPtr, Buf[0], &Protocol))
				{
					// packet is complete
					if (GetResult(szResultBuffer, pRPtr, pResultString))
					{
						bResultFound = TRUE;
					}
					else
					{
						pRPtr = szResultBuffer;
						Protocol.HDRFound = FALSE;
						Protocol.ESCFound = FALSE;
					}
				}
			}
			else 
				break;  // exit because unable to get a single char from ser port
		}

        CurrTime = clock();
        lMSecsExpired = CurrTime - StartTime;
	}

	if (bResultFound)
		return OPTISER_SUCCESS;
	else
		return OPTISER_FAILURE;
}
BOOL CSerialPort::DLGetResponse(char *ResultString, long lTimeout)
{
    long Count = 0, MSecsExpired = 0;
    BOOL ResultFound = FALSE;

    char ResultBuffer[1024] = "";
    char *RPtr = ResultBuffer;

    PT_PROTOCOLSTATE Protocol = { FALSE, FALSE };
    char Buf[2] = "";

    clock_t StartTime = clock();
    clock_t CurrTime;

	if (lTimeout == 0)
		SerialPortGetTimeout(&lTimeout);
   
    while (!(ResultFound || (MSecsExpired > lTimeout)))
    {
        // Device removed, return immediately
        if (NULL == m_hComm || INVALID_HANDLE_VALUE == m_hComm) 
            return OPTISER_FAILURE;

        if (SerialPortReceiveData(Buf, 1, &Count) >= OPTISER_SUCCESS)
        {
            if (Count == 1 )
            {
                if (DLProcessByte(&RPtr, Buf[0], &Protocol))
                {
                    // A packet is complete
                    if (DLGetResult(ResultBuffer, RPtr, ResultString))
                    {
                        ResultFound = TRUE;
                    }
                    else
                    {
                        RPtr = ResultBuffer; // Start again and reset the Protocol
                        Protocol.HDRFound = FALSE;
                        Protocol.ESCFound = FALSE;
                    }
                }
            }
            else
                break;  // exit because unable to get a single char from ser port
        }

        CurrTime = clock();
        MSecsExpired = CurrTime - StartTime;
    }

    return (ResultFound ? OPTISER_SUCCESS : OPTISER_FAILURE);
}

//===================================================================================================//
/*
 * read NV ability
 */
BOOL CSerialPort::Read_NV_ITEM_DATA(unsigned short uItemIndex, char szItemData[NV_ITEMDATA_LEN], char *uResponseCommand, unsigned short *pStatus) 
{
    if (NULL == m_hComm || INVALID_HANDLE_VALUE == m_hComm) 
    {
        TRACE("\nmyMessageBox: Read_NV_ITEM_DATA\n");
        return OPTISER_FAILURE;
    }

    unsigned short uStatus = 0;
    char szCommand[512] = "", szResponse[512] = "";
    szCommand[0] = (char)133; 
    szCommand[1] = (char)0;
    szCommand[2] = 0x26;
    szCommand[3] = uItemIndex & 0xff; 
    szCommand[4] = (uItemIndex >> 8) & 0xff;
    szCommand[5] = szItemData[0];

    if (CommandResponse(szCommand, szResponse) == OPTISER_FAILURE)
    {
        if (CommandResponse(szCommand, szResponse) == OPTISER_FAILURE)
        {
            if (CommandResponse(szCommand, szResponse) == OPTISER_FAILURE)
            {
   	            return OPTISER_FAILURE;
            }
        }
    }

    if (NULL != uResponseCommand) 
    {
        *uResponseCommand = szResponse[2];
    }

    #ifdef DEBUG_GO
        CString strLink;
    #endif

    if (szResponse[2] != szCommand[2] 
        || szResponse[0] != szCommand[0] 
        || szResponse[1] != szCommand[1] 
        || szResponse[3] != szCommand[3] 
        || szResponse[4] != szCommand[4]) 
    {
        #ifdef DEBUG_GO
            strLink.Format("%.4d: ", (unsigned char)szResponse[5] * (0xff + 1) + (unsigned char)szResponse[4]);
            gLog.Write(strLink, strLink.GetLength());
            strLink = "";

            strLink.Format("No DIAG Response Received(Error command: %.2x) - Bad SPC Mode Response\n", szResponse[2]);
            gLog.Write(strLink, strLink.GetLength());
            strLink = "";
        #endif

        return OPTISER_SUCCESS;
    }

    if (NULL != pStatus) 
    {
        uStatus &= 0;
        uStatus |= szResponse[134] & 0xff;
        uStatus <<= 8;
        uStatus |= szResponse[133] & 0xff;
        uStatus &= 0xffff;
        *pStatus = uStatus;
    }

    unsigned int uResponseLen = (unsigned char)szResponse[1] * (0xff + 1) + (unsigned char)szResponse[0] - 5;
    memcpy(szItemData, &(szResponse[5]), uResponseLen);

    return OPTISER_SUCCESS;
}

BOOL CSerialPort::Write_NV_ITEM_DATA(unsigned short uItemIndex, char szItemData[NV_ITEMDATA_LEN], DWORD uNV_ITEM_DATA_Len, char *chResponseCommand, unsigned short *pStatus) 
{
    if (NULL == m_hComm || INVALID_HANDLE_VALUE == m_hComm) 
    {
        return OPTISER_FAILURE;
    }

    unsigned short uStatus = 0;
    char szCommand[512] = "", szResponse[512] = "";

    szCommand[0] = (char)133;
    szCommand[1] = 0;
    szCommand[2] = 0x27;
    szCommand[3] = (uItemIndex & 0xff);
    szCommand[4] = ((uItemIndex >> 8) & 0xff);

    for (DWORD i = 0; i < uNV_ITEM_DATA_Len; i++)
    {
        szCommand[5+i] = szItemData[i];
    }

    if (CommandResponse(szCommand, szResponse) == OPTISER_FAILURE) 
    {
        if (CommandResponse(szCommand, szResponse) == OPTISER_FAILURE) 
        {
            if (CommandResponse(szCommand, szResponse) == OPTISER_FAILURE) 
            {
   	            return OPTISER_FAILURE;
            }
        }
    }

    if (NULL != chResponseCommand) 
    {
        *chResponseCommand = szResponse[2];
    }
    if (szResponse[2] != szCommand[2]
        || szResponse[0] != szCommand[0]
        || szResponse[1] != szCommand[1]
        || szResponse[3] != szCommand[3]
        || szResponse[4] != szCommand[4])
    {
        return OPTISER_FAILURE;
    }

    if (NULL != pStatus) 
    {
        uStatus &= 0;
        uStatus |= szResponse[134] & 0xff;
        uStatus <<= 8;
        uStatus |= szResponse[133] & 0xff;
        uStatus &= 0xffff;
        *pStatus = uStatus;
    }

    return OPTISER_SUCCESS;
}
