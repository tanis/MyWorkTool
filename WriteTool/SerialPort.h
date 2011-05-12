/*
File: SerialPort.h
Desc: 

Author: zjj
Date  : 2007.3.14
Notes : 有关串口操作的一些定义

   $Source: D:/cvsrepo/DllParam/SerialPort.h,v $

$Log: SerialPort.h,v $
Revision 1.1.1.1  2007/03/14 07:26:48  zhangjj
导入初始版本


*/


#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

#define CHAR_ENDING_FLAG		    0x7E
#define CHAR_ESCAPE_FLAG		    0x7D
#define CHAR_ESCAPE_XOR			    0x20

// These are used in the Optimay serial port implementation
#define OPTISER_SUCCESS			    1
#define OPTISER_FAILURE			    0

// These are used in buffer
#define BUF_LEN				        4096
#define NV_ITEMDATA_LEN             128

// These are used in mymessagebox's text
#define ID_STR_FAILTOINITIALIZE     "serial port initialize failure."

/* Status of the NV Read operation
 *The DMSS sets this field on return to indicate the status of the
 *read operation:
 */
#define STATUS_REQUEST_COMPLETED        0       //– Request completed OK
#define STATUS_INTERNAL_DMSS_USE        1       //– Internal DMSS use
#define STATUS_UNRECOGNIZABLE_COMMAND   2       //– Unrecognizable command
#define STATUS_MEMORY_IS_FULL           3       //– NV memory is full (should not get this status in a read response)
#define STATUS_COMMAND_FAILED           4       //– Command failed
#define STATUS_VARIABLE_NOT_ACTIVE      5       //– Variable was not active (never written)
#define STATUS_BAD_PARAM                6       //– Bad parameter in command block (may indicate this item does not exist for this phone or for the specified index for this phone)
#define STATUS_ITEM_READ_ONLY           7       //– Item was read-only (should not get this status in a read response)
#define STATUS_ITEM_NOT_DEFINED         8       //– Item not defined for this target
#define STATUS_MEMORY_EXHAUSTED         9       //– Free memory exhausted
#define STATUS_INTERNAL_USE             10      //– Internal use

// Unsinged 16 bit value type
typedef unsigned short			    word; 

// Boolean variable, are used in find out HDR or ESC char
typedef struct _PT_PROTOCOLSTATE    PT_PROTOCOLSTATE;
struct _PT_PROTOCOLSTATE
{
	BOOL HDRFound;
	BOOL ESCFound;
};


/* Mask for CRC-16 polynomial:
 *
 *      x^16 + x^12 + x^5 + 1
 *
 * This is more commonly referred to as CCITT-16.
 * Note:  the x^16 tap is left off, it's implicit.
 */
#define CRC_16_L_POLYNOMIAL     0x8408

/* Seed value for CRC register.  The all ones seed is part of CCITT-16, as
 * well as allows detection of an entire data stream of zeroes.
 */
#define CRC_16_L_SEED           0xFFFF

/* Seed value for CRC register.  The all ones seed is inverted prior to
 * being used in the step-wise CRC CCITT-16.  This behaves as CRC_16_L_SEED.
 */
#define CRC_16_L_STEP_SEED        ((word) ~((word) CRC_16_L_SEED))

/* Residual CRC value to compare against return value of a CRC_16_L_STEP().
 * Use CRC_16_L_STEP() to calculate a 16 bit CRC, complement the result,
 * and append it to the buffer.  When CRC_16_L_STEP() is applied to the
 * unchanged entire buffer, and complemented, it returns CRC_16_L_OK.
 * Crc_16_l_calc() of the same entire buffer returns CRC_16_L_OK.
 */
#define CRC_16_L_OK					0x0F47   
   
#define CRC_TAB_SIZE    256             /* 2^CRC_TAB_BITS      */

//---------------------------------------------------------------------------//

typedef enum _LOAD_STATUS
{
    LOAD_FAILURE = 0,
    LOAD_SUCCESS = 1
}LOAD_STATUS;

class CSerialPort
{														 
public:
	// contruction and destruction
	CSerialPort();
	virtual		~CSerialPort();

	// provide five functions to user
    /*
     * Set baud
     */
    BOOL SetSerialPort( int nBaud = 115200, 
                        int nParity = 0, 
                        int nStopbits = 1, 
                        int nDatabits = 8, 
                        int nTimeout = 5000);
	/*
	 * initialize com port
	 */
	BOOL InitSerialPort(UINT uPort = 4, 
                        int nBaud = 115200, 
                        int nParity = 0, 
                        int nStopbits = 1, 
                        int nDatabits = 8, 
                        int nTimeout = 5000);
	/*
	 * close com port
	 */
	BOOL Close();
    
    /*
	 * send a command && receive a result
	 */
	BOOL CommandResponse(char * CommandString, char *ResultString);
    BOOL DLCommandResponse(const char * CommandString, char *ResultString);

    /*
     * read and write NV ability
     */
    BOOL Read_NV_ITEM_DATA
        (
            unsigned short uItemIndex, 
            char szITEM_DATA[NV_ITEMDATA_LEN], 
            char *uResponseCommand = NULL, 
            unsigned short *pStatus = NULL
        );
    BOOL Write_NV_ITEM_DATA
        (
            unsigned short uItemIndex, 
            char szItemData[NV_ITEMDATA_LEN], 
            DWORD uNV_ITEM_DATA_Len = NV_ITEMDATA_LEN, 
            char *chResponseCommand = NULL, 
            unsigned short *pStatus = NULL
        );

protected:
//public:
	HANDLE				m_hComm;					// com port handle
	int					m_nPort;					// com port index
	long				m_lTimeout;					// times out seted

	DCB					m_dcb;						// dbc
	COMMTIMEOUTS		m_CommTimeouts;				// commtimeouts struct

    OVERLAPPED          m_ov;                       // overlapped

	//****************************************************//
	/*
	 * send data to com
	 */
	BOOL SerialPortSendData(char *pBuff, long lSize, long *pCount);
	/*
	 * reveive data from com
	 */
	BOOL SerialPortReceiveData(char *pBuff, long lSize, long *pCount );
	/*
	 * get time of out(取的超时时间)
	 */
	BOOL SerialPortGetTimeout(long *pTimeout );

	//****************************************************//
	/*
	 * process every byte to judge whether string is end.
	 */
	BOOL ProcessByte(char **pRPtr, char Byte, PT_PROTOCOLSTATE *Protocol);
    BOOL DLProcessByte(char **RPtr, char Byte, PT_PROTOCOLSTATE *Protocol);

	/*
	 * format pack(格式化Command)
	 */
	void FormatCommand( const char *pCommandString, char * pCommandBuffer, long *pLength);
    void DLFormatCommand(const char *CommandString, char *CommandBuffer, long *Length);

	/*
	 * pack is complete(包完成)
	 */
	BOOL GetResult( char * pResultBuffer, char * pRPtr, char * pResultString);
    BOOL DLGetResult(char * ResultBuffer, char * RPtr, char * ResultString);

	/*
	 * call GetResult, to get "pResultString"(调用GetResult)
	 */
	BOOL GetResponse(char *pResultString, long lTimeout);
    BOOL DLGetResponse(char *ResultString, long lTimeout);

	/*
	 * clear com buffer
	 */
	BOOL Clear();
};

#endif __SERIALPORT_H__


