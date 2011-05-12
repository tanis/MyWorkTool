
#ifndef __COMMON_H__
#define __COMMON_H__

typedef struct tagInt64 Int64;
struct tagInt64
{
    ULONG uLow;
    ULONG uHigh;
};

static int DataType(char *pszData);
static Int64 *Shift(int nSize, char *pszData);
static char *ShiftToChar(int nSize, Int64 *int64);
static char *HexToDecimal(char *szText);
static char *HexToIPAddress(char *szText);
static char *IPAddressToHex(char *szIP);
static void GetIMEIAfterCRC(char *pszIMEI);
static BOOL Testbit(char *pResponse, unsigned short nIndex);
static void output(char *szResponse);

static int DataType(char *pszData)
{
    int nResult = 0;
    if ((pszData[1] == 'x') || (pszData[1] == 'X')) 
        nResult = 1;
    if ((pszData[1] == 'b') || (pszData[1] == 'B')) 
        nResult = 2;
    
    return nResult;
}

static Int64 *ShiftToInt64(int nSize, char *pszData)
{
    static Int64 int64;
    
    UCHAR nValueAfterShift = 0;

    UINT uValueLow = 0;
    UINT uValueHigh = 0;
    
    int i = 0;
    int nCount = nSize / 8;
    if (nSize <= 32)
    {
        for (i = 0; i < nCount; i++)
        {
            nValueAfterShift = (UCHAR)pszData[i];
            uValueLow = (nValueAfterShift << (i * 8)) | uValueLow;
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            nValueAfterShift = (UCHAR)pszData[i];
            uValueLow = (nValueAfterShift << (i * 8)) | uValueLow;
        }
        for (; i < nCount; i++)
        {
            nValueAfterShift = (UCHAR)pszData[i];
            uValueHigh = (nValueAfterShift << (i * 8)) | uValueHigh;
        }
    }
    
    int64.uLow  = uValueLow;
    int64.uHigh = uValueHigh;
    
    return &int64; 
}

static char *ShiftToChar(int nSize, Int64 *int64)
{
    static char szData[128];
    memset(szData, 0, sizeof(szData));

    int nValueAfterShift = 0;

    int i = 0;
    int nCount = nSize / 8;

    if (nSize <= 32)
    {
        for (i = 0; i < nCount; i++)
        {
            nValueAfterShift = (int64->uLow) >> (i * 8);
            szData[i] = (UCHAR)(nValueAfterShift & 0xff);
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            nValueAfterShift = (int64->uLow) >> (i * 8);
            szData[i] = (UCHAR)(nValueAfterShift & 0xff);
        }
        for (; i < nCount; i++)
        {
            nValueAfterShift = (int64->uHigh) >> (i * 8);
            szData[i] = (UCHAR)(nValueAfterShift & 0xff);  
        }
    }

    return szData;
}

static BOOL Testbit(char *pResponse, unsigned short nIndex) 
{
    unsigned int uResponseLen = (unsigned char)pResponse[4] * 0x100 + (unsigned char)pResponse[3];
    
    int nPos = nIndex / 8;
    for (int j = 7; j >= 0; j--) 
    {
        if (nIndex == nPos * 8 + j) 
        {
            unsigned char ch = (unsigned char)pResponse[5 + nPos];
            if (ch & (1 << j))
                return TRUE;
            else
                return FALSE;
        }
    }
    
    return FALSE;
}

/*
 * 	   3 50 96 06 90 29 37 5,9
 *            |||
 *             |
 * 80 a3 50 96 06 90 29 37 59  
 */
static void GetIMEIAfterCRC(char *pszIMEI)
{
    //char szIMEI[] = "35820800123456";
    
    int nLen = 0;
    char szIMEICRC[32] = { 0 };
    for (int i = 0; i < 7; i++)                 // len: 14
    {
        nLen += sprintf(szIMEICRC + nLen, "%c%d", 
            pszIMEI[2 * i], (pszIMEI[2 * i + 1] - '0') * 2);
    }
    
    int nSum = 0;
    for (i = 0; i < nLen; i++)
    {
        nSum += (szIMEICRC[i] - '0');
    }
    int nMode = nSum % 10;
    int nResult = (nMode != 0) ? (10 - nMode) : 0;
    
    sprintf(pszIMEI + strlen(pszIMEI), "%d", nResult);

    char szTempBuffer[MAX_PATH];
    sprintf(szTempBuffer, "80a%s", pszIMEI);
    
    sprintf(pszIMEI, "%s", szTempBuffer);
}

static char *HexToDecimal(char *szText)
{
    static char szData[_MAX_PATH];
    memset(szData, 0, _MAX_PATH);
    ULONG uValue = strtoul(szText + 2, NULL, 16);
    sprintf(szData, "%u", uValue);
    return szData;
}
static char *HexToIPAddress(char *szText)
{
    int nLen = 0;
    int nDigit = 0;
    static char szData[_MAX_PATH];
    memset(szData, 0, _MAX_PATH);
    for (int i = 0; i < 4; i++)
    {
        char sztemp[3];
        memset(sztemp, 0, sizeof(sztemp));
        sprintf(sztemp, "%c%c", szText[i * 2 + 2], szText[i * 2 + 3]); 
        nDigit = strtol(sztemp, NULL, 16);
        if (i != 3)
            nLen += sprintf(szData + nLen, "%d.", nDigit); 
        else
            nLen += sprintf(szData + nLen, "%d", nDigit); 
    }
    
    return szData;
}
static char *IPAddressToHex(char *szIP)
{
    char *p = NULL;
    char szField[4]; BYTE nFild[4];
    
    int nLen = 0;
    static char szHex[16]; 
    memset(szHex, 0, 16);
    
    for (int i = 0; i < 4; i++) 
    {
        p = strrchr(szIP, '.');
        if (p)
        {
            strcpy(szField, p + 1);
            nFild[3 - i] = atoi(szField);
            *p = 0;
        }
        else
        {
            nFild[0] = atoi(szIP);
        }
    }
    for (i = 0; i < 4;  i++)
    {
        nLen += sprintf(szHex + nLen, "%.2x", nFild[i]);
    }
    return szHex;
}

static void output(char *szResponse) 
{
    int nLen = (unsigned char)szResponse[1] * 0x100 + (unsigned char)szResponse[0];
    
    char *pBuf = new char[nLen];
    memcpy(pBuf, szResponse + 2, nLen);
    
    char szTempBuf[3] = "";
    for (int i = 0; i < nLen; i++) {
        sprintf(szTempBuf, "%.2x ", (unsigned char)pBuf[i]);
        //TRACE("%.2d:%.2x ", i, (unsigned char)pBuf[i]);
        TRACE("%.2x ", (unsigned char)pBuf[i]);
    }
    TRACE("\n");
    
    delete [] pBuf;
}

#endif