// WriteToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WriteTool.h"
#include "WriteToolDlg.h"
#include "ServerSetting.h"
#include "OTPPancel.h"
#include "FlashPancel.h"
#include "NVPancel.h"
#include "Global.h"
#include "CopyRiht.h"
#include "DllParam.h"

#include "setParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWriteToolDlg dialog

CWriteToolDlg* gWriteToolDlg=NULL;
CSetParam gSetParam;

void RefreshMainDlgMsgBox(char* pInformation)
{
	if(gWriteToolDlg != NULL)
	{
		gWriteToolDlg->RefreshInformation(pInformation);
	}
}
void AddInfotoMainDlgMsgBox(char* pInformation)
{
	if(gWriteToolDlg != NULL)
	{
		gWriteToolDlg->AddInformation(pInformation);
	}
}

void EnableComboBox(BOOL bEnable)
{
	if(gWriteToolDlg != NULL)
	{
		gWriteToolDlg->m_ComboBox.EnableWindow(bEnable);
	}
}

void MinimizeMainDialog()
{
	if(gWriteToolDlg != NULL)
	{
		gWriteToolDlg->PostMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
	}
}

void NotifyMainDlgOnWrite()
{
	
	if(gWriteToolDlg != NULL)
	{
		CWnd* pWnd = gWriteToolDlg->GetDlgItem(IDC_WRITE);
		gWriteToolDlg->SendMessage(WM_COMMAND,MAKEWPARAM(IDC_WRITE,BN_CLICKED),(LPARAM)pWnd->m_hWnd);
	}
	
}

CWriteToolDlg::CWriteToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWriteToolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWriteToolDlg)
	m_HandsetStatus = _T("");
	m_InfoDisplay = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_WRITETOOL);
}

void CWriteToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWriteToolDlg)
	DDX_Control(pDX, IDC_COMBO, m_ComboBox);
	DDX_Control(pDX, IDC_WRITETOOL_TAB, m_WriteToolTabCtrl);
	DDX_Text(pDX, IDC_HANDSET_STATUS, m_HandsetStatus);
	DDX_Text(pDX, IDC_DISPLAY_INFO, m_InfoDisplay);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWriteToolDlg, CDialog)
	//{{AFX_MSG_MAP(CWriteToolDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_SETTINGS, OnFileSettings)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_BN_CLICKED(IDC_READ, OnRead)
	ON_BN_CLICKED(IDC_WRITE, OnWrite)
	ON_NOTIFY(TCN_SELCHANGE, IDC_WRITETOOL_TAB, OnSelchangeWritetoolTab)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO, OnSelchangeCombo)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWriteToolDlg message handlers

BOOL CWriteToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Dialog[0] = new COTPPancel();
#ifndef FRV_RELEASE
	m_Dialog[1] = new CFlashPancel();
	m_Dialog[2] = new CNVPancel();
#else
	m_Dialog[1] = NULL;
	m_Dialog[2] = NULL;
#endif

	m_WriteToolTabCtrl.AddPage("IMEI WRITE",m_Dialog[0],IDD_OTP_PANCEL);
#ifndef FRV_RELEASE
	m_WriteToolTabCtrl.AddPage("Flash Options",m_Dialog[1],IDD_FLASH_PANCEL);
	m_WriteToolTabCtrl.AddPage("NV Options",m_Dialog[2],IDD_NV_PANCEL);
#endif
	m_WriteToolTabCtrl.Show();
	m_WriteToolTabCtrl.SetCurSel(0);
	m_ComboBox.ShowWindow(FALSE);

	(COTPPancel*)m_Dialog[0]->SetFocus();
	
	InitData();

	gWriteToolDlg = this;
	return FALSE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWriteToolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWriteToolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWriteToolDlg::InitData()
{
	char FullName[MAX_PATH+1] = {0};

	//Load Library
	m_hLibraryListComPort = LoadLibrary("ListComPort.dll");
	if(m_hLibraryListComPort==NULL)
	{
		m_GetValidComPortProc = NULL;
		MessageBox("Load ListComPort.dll failed!",NULL,MB_ICONERROR);
	}
	else
	{
		//zhangjj 070703 add for devicelist.dat
		TInitDeviceItem* InitDeviceItemProc = (TInitDeviceItem*)GetProcAddress(m_hLibraryListComPort, InitDeviceItemName);
		if (InitDeviceItemProc == NULL)
		{
			MessageBox("GetProc failed!",NULL,MB_ICONERROR);
		}
		
#ifndef FRV_RELEASE
		// read device item list file
		UINT32 ItemBufLen;
		char* pItemBuf = (char*)ReadDLFile("DeviceList.dat", &ItemBufLen);
#else
		UINT32 ItemBufLen = 57;
		char* pItemBuf = "SYSTEM\\CurrentControlSet\\Enum\\USB\\VID_05C6&PID_5747&MI_00";
#endif
		if (InitDeviceItemProc(pItemBuf, ItemBufLen) == FALSE)
		{
			MessageBox("Init device list failed!", NULL,MB_ICONERROR);
		}

		//zhangjj end

		m_GetValidComPortProc = (TDLGetValidComPortProc*)GetProcAddress(m_hLibraryListComPort,DLGetValidComPortName);
		if(m_GetValidComPortProc == NULL)
		{
			MessageBox("Load Process \"GetValidComPort\" failed!",NULL,MB_ICONERROR);
		}
	}
	//Read the data from cfg

	strcpy(gProjectName,"UnknownName");
	strcpy(gIPAddress,"255.255.255.1");

#ifdef FRV_RELEASE


	char MIN_IMEI[CFGFILE_IMEI_STRLEN+1]="35355103001401";
	char MAX_IMEI[CFGFILE_IMEI_STRLEN+1]="35355103099999";
	char MIN_BTADDR[CFGFILE_BT_ADDR_STRLEN+1] = "";
	if (gSetParam.isOK())
		gSetParam.getCfgParam(MIN_IMEI, CFGFILE_IMEI_STRLEN,  MIN_BTADDR, CFGFILE_BT_ADDR_STRLEN);

	strcpy(CfgMinIMEI,MIN_IMEI);
	strcpy(CfgMaxIMEI,MAX_IMEI);

	gbCheckIMEI = TRUE;
	gbCheckBTAddr = FALSE;

	strcpy(CfgMinBtAddress, MIN_BTADDR);

	//init track file
	CString info = "";
	char timebuf[128] = {0};
	char datebuf[128] = {0};

	_strtime( timebuf );
	_strdate( datebuf );

	info += "********";
	info += datebuf;
	info += " ";
	info += timebuf;
	info += "********\n";

	if (!AddToTrackFile(info)) 
	{
		MessageBox("创建TRACK文件失败!", NULL,MB_ICONERROR);
		DestroyWindow();
	}

#endif

	
	m_PageSel = 0;
	gComPortInfo.ComID = 0;
	gComPortInfo.bIsOpen = FALSE;
	gComPortInfo.bIsConnect = FALSE;
	gComPortInfo.ComNum = -1;
	for(int i=0; i<MAX_COM_NUM; i++)
	{
		gComPortInfo.ComIDList[i] = 0;
	}
	//Set timer to detect the com
	m_DetectComTimer = SetTimer(1010, 200, NULL);
	InitHotKey();
}

BOOL CWriteToolDlg::GetConfigFileName(char* pFileName)
{
	UINT nLen = 0;
	int i;

	GetModuleFileName(NULL,pFileName,MAX_PATH);
	nLen = strlen(pFileName);
	if(nLen == 0)
	{
		return FALSE;
	}

	for(i=nLen-1; i>=0; i--)
	{
		if(pFileName[i] == '\\')
		{
			pFileName[i+1] = 0;
			strcat(pFileName,WRITE_TOOL_CONFIG_FILE);
			return TRUE;
		}
	}
	return FALSE;
}

//zhangjj 070703 add for devicelist.dat
byte* CWriteToolDlg::ReadDLFile(const char* pFileName, size_t* FileLen)
{
	// open file
	FILE   *fp = NULL;
	size_t  len = 0;
	byte   *pdata = NULL;
	
	if ( (fp = fopen(pFileName, "rb")) == NULL)
	{
		printf("open %s failed!\n", pFileName);
		return NULL;
	}
	
	// get file length
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	pdata = (byte*)malloc(len+1); // +1 for text file end sign
	fseek(fp, 0, SEEK_SET);
	
	// read file
	if (fread(pdata, len, 1, fp) != 1)
	{
		printf("read %s failed!\n", pFileName);
		return NULL;
	}
	
	fclose(fp);
	
	*FileLen = len;
	pdata[len] = 0; //add text file end sign
	
	return pdata;
}
//zhangjj end

void CWriteToolDlg::ReleaseData()
{
	KillTimer(m_DetectComTimer);
	CloseComPort();
	FreeLibrary (m_hLibraryListComPort);
	//FreeLibrary (ghLibraryDllParam);
	gWriteToolDlg = NULL;
}

void CWriteToolDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == m_DetectComTimer)
	{
		int nComNum = 0;
		int ComPortID[MAX_COM_NUM] = {0};

		if(m_GetValidComPortProc != NULL)
		{
			nComNum = m_GetValidComPortProc(ComPortID,MAX_COM_NUM);
		}
		else
		{
			m_HandsetStatus.Format("Proggram error!");
			UpdateData(FALSE);
			return;
		}

		if(gComPortInfo.ComNum != nComNum)
		{
			gComPortInfo.ComNum = nComNum;
			for(int i=0; i<MAX_COM_NUM; i++)
			{
				gComPortInfo.ComIDList[i] = ComPortID[i];
			}

			if(gComPortInfo.ComNum == 1)
			{
				gComPortInfo.ComID = ComPortID[0];
				gComPortInfo.bIsConnect = TRUE;
				m_HandsetStatus.Format("Gozone phone(COM%d) connected!",gComPortInfo.ComID);
#ifdef FRV_RELEASE
				((COTPPancel*)m_Dialog[0])->m_CIMEI.SetFocus();
#endif
				m_ComboBox.ShowWindow(FALSE);
				UpdateData(FALSE);
			}
			else
			{
				if(gComPortInfo.ComNum <= 0)
				{
					gComPortInfo.bIsConnect = FALSE;
					m_HandsetStatus.Format("No phone connected!");
					m_ComboBox.ShowWindow(FALSE);
				}
				else
				{
					gComPortInfo.bIsConnect = TRUE;
					m_ComboBox.ShowWindow(TRUE);
					m_ComboBox.ResetContent();
					for(i=0; i<gComPortInfo.ComNum; i++)
					{
						CString tmpString;
						tmpString.Format("COM%d",gComPortInfo.ComIDList[i]);
						m_ComboBox.InsertString(i,tmpString.GetBuffer(0));
					}
					gComPortInfo.ComID = gComPortInfo.ComIDList[0];
					m_ComboBox.SetCurSel(0);
					m_HandsetStatus.Format("%d phones connected,use COM%d!",gComPortInfo.ComNum,gComPortInfo.ComID);
				}
				UpdateData(FALSE);
			}
		}
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CWriteToolDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ReleaseData();
	
	return CDialog::DestroyWindow();
}

void CWriteToolDlg::OnFileSettings() 
{
	// TODO: Add your command handler code here
	CServerSetting dlg;
	if(dlg.DoModal() == IDOK)
	{
		char FullName[MAX_PATH+1] = {0};

		//Save the data to cfg file
		if(GetConfigFileName(FullName) == TRUE)
		{
			WritePrivateProfileString("ServerParam","ProjectName",gProjectName,FullName);
			WritePrivateProfileString("ServerParam","IPAddr",gIPAddress,FullName);
		}

		//Set to Server
		if(gComPortInfo.bIsOpen == TRUE)
		{
			if(SetServerParam() == TRUE)
			{
				RefreshMainDlgMsgBox("Set the param of sign server success!");
			}
			else
			{
				RefreshMainDlgMsgBox("Set the param of sign server failed!");
			}
		}
	}
}

void CWriteToolDlg::OnHelpAbout() 
{
	// TODO: Add your command handler code here
	CCopyRight dlg;
	dlg.DoModal();
}

void CWriteToolDlg::OnFileExit() 
{
	// TODO: Add your command handler code here
	CDialog::OnCancel();
}

//Read IMEI
BOOL CWriteToolDlg::ReadIMEI(OTP_IMEI* pIMEI)
{
	return Read_OTP_IMEI(gComPortInfo.ComID,pIMEI);
}
//Write IMEI
BOOL CWriteToolDlg::WriteIMEI(OTP_IMEI IMEI)
{
	SetIMEICheckBit(IMEI.szIMEI);
	return Write_OTP_IMEI(gComPortInfo.ComID,&IMEI);
}

//给IMEI号增加校验位,写入到第15位上
//See TS 0216.720
void CWriteToolDlg::SetIMEICheckBit(char * pIMEI)
{
	char tmpIMEI[16] = {0};
	unsigned int sum=0;
	int i,j;

	for(i=13;i>=1;i=i-2)
	{
		j = (pIMEI[i]-0x30)*2;
		sum = sum + j/10 + j%10 + (pIMEI[i-1]-0x30);
	}
	if((10 - (sum%10)) == 10)
	{
		pIMEI[14] = '0';
	}
	else
	{
		pIMEI[14] = (10 - (sum%10)) + '0';
	}
}

void CWriteToolDlg::ClearIMEICheckBit(char * pIMEI)
{
	pIMEI[14] = '\0';
}

//Read BT Address
BOOL CWriteToolDlg::ReadBTAddress(OTP_BlueToothAddr* pBTAddr)
{
	return Read_OTP_BlueToothAddr(gComPortInfo.ComID,pBTAddr);
}
//Write BT Address
BOOL CWriteToolDlg::WriteBTAddress(OTP_BlueToothAddr BTAddr)
{
	return Write_OTP_BlueToothAddr(gComPortInfo.ComID,&BTAddr);
}


//read ESN
BOOL CWriteToolDlg::ReadESN(OTP_ESN* pESN)
{
	return Read_OTP_ESN(gComPortInfo.ComID,pESN);
}

//write ESN
BOOL CWriteToolDlg::WriteESN(OTP_ESN ESN)
{
	return Write_OTP_ESN(gComPortInfo.ComID,&ESN);
}

//Read Hash
BOOL CWriteToolDlg::ReadHash(OTP_Hash* pHash)
{
	return Read_OTP_HASH(gComPortInfo.ComID,pHash);
}
//Write DCK
BOOL CWriteToolDlg::WriteDCK(BYTE* pDCK)
{
	UINT nOutLenth=0;
	OTP_Hash OTPHash={0};

	//Transform DCK into Hash
	UINT tmplen = strlen((char*)pDCK);
	HashDck(pDCK, tmplen, OTPHash.byteHash, &nOutLenth);
	if(nOutLenth != GOZONE_DCKHASH_LEN)
	{
		MessageBox("Transform DCK into Hash failed!",NULL,MB_ICONWARNING);
		return FALSE;
	}
	return Write_OTP_HASH(gComPortInfo.ComID,&OTPHash);
}

//Read Public Key
BOOL CWriteToolDlg::ReadPublicKey(OTP_PublicKey* pPublicKey)
{
	return Read_OTP_PublicKey(gComPortInfo.ComID,pPublicKey);
}
//Write Public Key
BOOL CWriteToolDlg::WritePublicKey(OTP_PublicKey PublicKey)
{
	return Write_OTP_PublicKey(gComPortInfo.ComID,&PublicKey);
}

//Plmn List
BOOL CWriteToolDlg::ReadPlmnList(OTP_Plmn *pPlmnList)
{
	return Read_OTP_PLMN(gComPortInfo.ComID,pPlmnList);
}
BOOL CWriteToolDlg::WritePlmnList(OTP_Plmn PlmnList)
{
	return Write_OTP_PLMN(gComPortInfo.ComID,&PlmnList);
}

//Read SimLock Info
BOOL CWriteToolDlg::ReadSimLockInfo(OTP_SIMLockInfo *pSimLockInfo)
{
	return Read_OTP_SIMLockInfo(gComPortInfo.ComID,pSimLockInfo);
}
//Write SimLock Info
BOOL CWriteToolDlg::WriteSimLockInfo(OTP_SIMLockInfo SimLockInfo)
{
	return Write_OTP_SIMLockInfo(gComPortInfo.ComID,&SimLockInfo);
}

//Read Hdet OFF
BOOL CWriteToolDlg::GetHdetOffMark(char *pHdetOff)
{
	return Get_HDET_OFF(gComPortInfo.ComID,pHdetOff);
}
//Read Hdet SPN
BOOL CWriteToolDlg::GetHdetSPNMark(char *pHdetSpn)
{
	return Get_HDET_OFF(gComPortInfo.ComID,pHdetSpn);
}

void CWriteToolDlg::OnRead() 
{
	// TODO: Add your control notification handler code here
	CString InfoString="";
	CString tmpString="";
	ReadWriteComReq();

	RefreshMainDlgMsgBox("*****************************************************");
	if(m_PageSel == 0)	// OTP Pancel
	{
		if(gbCheckIMEI == TRUE)
		{
			InfoString += CString("\r\nRead IMEI:");
			if(ReadIMEI(&gIMEI) == TRUE)
			{
				tmpString.Format("\r\n  IMEI = %s",gIMEI.szIMEI);
				ClearIMEICheckBit(gIMEI.szIMEI);
			}
			else
			{
				tmpString = CString("Failed!");
			}
			InfoString += tmpString;
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		if(gbCheckBTAddr == TRUE)
		{
			InfoString += CString("\r\nRead BT Address:");
			if(ReadBTAddress(&gBTAddress) == TRUE)
			{
				tmpString.Format("\r\n  BT Address = %s",gBTAddress.szBlueToothAddr);
			}
			else
			{
				tmpString = CString("Failed!");
			}
			InfoString += tmpString;
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		if(gbCheckESN == TRUE)
		{
			InfoString += CString("\r\nRead ESN:");
			if(ReadESN(&gESN) == TRUE)
			{
				tmpString.Format("\r\n  ESN = %s",gESN.szESN);
				//ReadESNCheckSum(&gESN);
			}
			else
			{
				tmpString = CString("Failed!");
			}
			InfoString += tmpString;
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		if(gbCheckMEID == TRUE)
		{
			InfoString += CString("\r\nRead MEID:");
			if(ReadMEID(&gMEID) == TRUE)
			{
				ClearMEIDCheckBit(gMEID.szMEID);
				tmpString.Format("\r\n  MEID = %s",gMEID.szMEID);
			}
			else
			{
				tmpString = CString("Failed!");
			}
			InfoString += tmpString;
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		if(gbCheckDCK == TRUE)
		{
			OTP_Hash tmpHash;

			InfoString += CString("\r\nRead Hash of DCK:");
			if(ReadHash(&tmpHash) == TRUE)
			{
				for(UINT i=0; i<GOZONE_DCKHASH_LEN; i++)
				{
					if(i%10 == 0)
					{
						InfoString += CString("\r\n  ");
					}
					tmpString.Format("%02x ",tmpHash.byteHash[i]);
					InfoString += tmpString;
				}
			}
			else
			{
				InfoString += CString("Failed!");
			}
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		if(gbCheckPublicKey == TRUE)
		{
			OTP_PublicKey tmpPublicKey;

			InfoString += CString("\r\nRead Public key:");
			if(ReadPublicKey(&tmpPublicKey) == TRUE)
			{
				for(UINT i=0; i<GOZONE_PUBLICKEY_LEN; i++)
				{
					if(i%10 == 0)
					{
						InfoString += CString("\r\n  ");
					}
					tmpString.Format("%02x ",tmpPublicKey.bytePublicKey[i]);
					InfoString += tmpString;
				}
			}
			else
			{
				InfoString += CString("Failed!");
			}
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		((COTPPancel*)m_Dialog[m_PageSel])->RefreshPancel();
	}
	else if(m_PageSel == 1)	//Flash Pancel
	{
		if(gbCheckSimLockInfo == TRUE)
		{
			InfoString += CString("\r\nRead SimLock Info:");
			if(ReadSimLockInfo(&gSimLockInfo) == TRUE)
			{
				tmpString.Format("\r\n%d,%d,%d,%d,%d,%d",
								gSimLockInfo.byteLockStatus,
								gSimLockInfo.byteSequenceAttemptsLeft,
								gSimLockInfo.byteIntervalAttemptsLeft,
								gSimLockInfo.byteHoursLeft,
								gSimLockInfo.byteMinutesLeft,
								gSimLockInfo.byteSecondsLeft);
			}
			else
			{
				tmpString = CString("Failed!");
			}
			InfoString += tmpString;
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		if(gbCheckPlmnList == TRUE)
		{
			OTP_Plmn tmpPlmnList;

			InfoString += CString("\r\nRead Plmn List:");
			if(ReadPlmnList(&tmpPlmnList) == TRUE)
			{
				InfoString += CString("\r\n  List PLMN");
				for(UINT i=0; i<20; i++)
				{
					tmpString.Format("    %02x %02x %02x,",
									tmpPlmnList.bytePlmn[i][0],
									tmpPlmnList.bytePlmn[i][1],
									tmpPlmnList.bytePlmn[i][2]);
					if(i%4 == 0)
					{
						InfoString += CString("\r\n");
					}
					InfoString += tmpString;
				}
				tmpString.Format("\r\n  Country Code = %02x,%02x",
						tmpPlmnList.CountryCode[0],tmpPlmnList.CountryCode[1]);
				InfoString += tmpString;
			}
			else
			{
				InfoString += CString("Failed!");
			}
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		((CFlashPancel*)m_Dialog[m_PageSel])->RefreshPancel();
	}
	else if(m_PageSel == 2)	//NV Pancel
	{
		if(gbCheckBaseAdjust == TRUE)
		{
			InfoString += CString("\r\nRead the value of BaseAdjust:");
			if(GetHdetOffMark(&gBaseAdjust) == TRUE)
			{
				tmpString.Format("\r\n  BaseAdjust = 0x%02x",gBaseAdjust);
				InfoString += tmpString;
			}
			else
			{
				InfoString += CString("Failed!");
			}
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		if(gbCheckGeneralAdjust == TRUE)
		{
			InfoString += CString("\r\nRead the value of GeneralAdjust:");
			if(GetHdetSPNMark(&gGeneralAdjust) == TRUE)
			{
				tmpString.Format("\r\n  GeneralAdjust = 0x%02x",gGeneralAdjust);
				InfoString += tmpString;
			}
			else
			{
				InfoString += CString("Failed!");
			}
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		((CNVPancel*)m_Dialog[m_PageSel])->RefreshPancel();
	}
	else
	{
		RefreshMainDlgMsgBox("");
		InfoString += CString("\r\nNot support this function!");
	}
	AddInfotoMainDlgMsgBox(InfoString.GetBuffer(0));
	CloseComPort();
}

void CWriteToolDlg::OnWrite() 
{
	// TODO: Add your control notification handler code here
	CString InfoString="";
	CString tmpString="";
	BOOL bStatus = TRUE;
	UINT offsetToBaseMEID = 0;
	UINT offsetToBaseIMEI = 0;
	
	ReadWriteComReq();

	RefreshMainDlgMsgBox("*****************************************************");
	if(m_PageSel == 0)	// OTP Pancel
	{
		// TODO: if not read from cfg ini, generate BT
		if(gbCheckIMEI == TRUE)
		{
			InfoString += CString("\r\n录入IMEI:");
			tmpString.Format("%s", gIMEI.szIMEI);
			InfoString += tmpString;
			if(!IsIMEIString(gIMEI.szIMEI) || !IsGozoneIMEI(gIMEI.szIMEI, &offsetToBaseIMEI))
			{
				InfoString += CString("\r\nIMEI无效，请检查!");
				bStatus = FALSE;
				MessageBox("IMEI无效!",NULL,MB_ICONERROR);
			}
			else
			{
			}

			if (bStatus == TRUE)
			{
				if(WriteIMEI(gIMEI) == TRUE)
				{
					InfoString += CString(" 成功!");
					tmpString += "\t";
					AddToTrackFile(tmpString);
				}
				else
				{
					InfoString += CString(" 失败!");
					bStatus = FALSE;
					MessageBox("录入IMEI失败!",NULL,MB_ICONERROR);
				}
			}

			InfoString += CString("\r\n\r\n*****************************************************");
		}

		if ((gbCheckMEID == TRUE) && (bStatus == TRUE))
		{
			InfoString += CString("\r\n录入MEID:");
			tmpString.Format("%s",gMEID.szMEID);
			InfoString += tmpString;
			
			if (!IsMEIDString(gMEID.szMEID) || !IsGozoneMEID(gMEID.szMEID, &offsetToBaseMEID))
			{
				InfoString += CString("\r\nMEID无效，请检查!");
				bStatus = FALSE;
				MessageBox("MEID无效!",NULL,MB_ICONERROR);
			}			
			else
			{
				//允许客户反复快速多次写
				//if ((!IsStrInTrackFile(tmpString)))
				//{
				//	InfoString += CString("\r\nMEID已经使用过，请检查!");
				//	bStatus = FALSE;
				//	MessageBox("MEID已经使用过!",NULL,MB_ICONERROR);
				//}
			}

			if (bStatus == TRUE)
			{
				if(WriteMEID(gMEID) == TRUE)
				{
					InfoString += CString(" 成功!");
					tmpString += "\t";
					AddToTrackFile(tmpString);
				}
				else
				{
					InfoString += CString(" 失败!");
					bStatus = FALSE;
					MessageBox("录入MEID失败!",NULL,MB_ICONERROR);
				}
			}
			InfoString += CString("\r\n\r\n*****************************************************");
		}

		if ((gbCheckBTAddr == TRUE) && (bStatus == TRUE))
		{
			if (!gSetParam.isOK())
			{
				char tmpBT[20];
				strcpy(tmpBT, "0012");
				strncat(tmpBT, gIMEI.szIMEI+6, 8);
				tmpBT[4+GOZONE_IMEI_SIZE*2] = '\0';
				strncpy(gBTAddress.szBlueToothAddr, tmpBT, GOZONE_BT_ADDRESS_SIZE*2);
				gBTAddress.szBlueToothAddr[GOZONE_BT_ADDRESS_SIZE*2] = '\0';
			}

			InfoString += CString("\r\n录入蓝牙地址:");
			if (gSetParam.isOK() && (!IsGozoneBtAddr(offsetToBaseIMEI,gBTAddress.szBlueToothAddr) ||
				!IsBTAddrString(gBTAddress.szBlueToothAddr)))
			{
				InfoString += CString("\r\n蓝牙地址无效，请检查!");
				bStatus = FALSE;
				MessageBox("蓝牙地址无效!",NULL,MB_ICONERROR);
			}
			else
			{
				tmpString.Format("%s",gBTAddress.szBlueToothAddr);
				InfoString += tmpString;
				
				if(WriteBTAddress(gBTAddress) == TRUE)
				{
					InfoString += CString(" 成功!");
					tmpString += CString("\n");
					AddToTrackFile(tmpString);
				}
				else
				{
					InfoString += CString(" 失败!");
					bStatus = FALSE;
					MessageBox("录入蓝牙地址失败!",NULL,MB_ICONERROR);
				}
			}
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		if ((gbCheckESN == TRUE) && (bStatus == TRUE))
		{
			InfoString += CString("\r\n录入ESN:");
			tmpString.Format("%s",gESN.szESN);
			InfoString += tmpString;
			
			if (!IsESNString(gESN.szESN) || !IsGozoneEsn(gESN.szESN, NULL))
			{
				InfoString += CString("\r\nESN无效，请检查!");
				bStatus = FALSE;
				MessageBox("ESN无效!",NULL,MB_ICONERROR);
			}

			if (bStatus == TRUE)
			{
				if(WriteESN(gESN) == TRUE)
				{
					InfoString += CString(" 成功!");
					tmpString += "\t";
					AddToTrackFile(tmpString);
				}
				else
				{
					InfoString += CString(" 失败!");
					bStatus = FALSE;
					MessageBox("录入ESN失败!",NULL,MB_ICONERROR);
				}
			}
			InfoString += CString("\r\n\r\n*****************************************************");
		}
#ifndef FRV_RELEASE		
		if(gbCheckESN == TRUE)
		{
			InfoString += CString("\r\nWrite ESN:");
			if(IsESNString(gESN.szESN) == FALSE)
			{
				InfoString += CString("\r\nESN is invalid,Please check it!");
			}
			else
			{
				if(gbCheckAutoIncESN == TRUE)
				{
					ESNInc(gESN.szESN);
				}
				if(WriteESN(gESN) == TRUE)
				{
					InfoString += CString("Success!");
				}
				else
				{
					InfoString += CString("Failed!");
				}
			}
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		if(gbCheckDCK == TRUE)
		{
			OTP_IMEI tmpIMEI={0};

			InfoString += CString("\r\nWrite DCK:");
			if(ReadIMEI(&tmpIMEI) == FALSE)	//IMEI如果为空则不让写DCK
			{
				InfoString += CString("\r\nIMEI of UE is NULL,please write IMEI first!");
			}
			else
			{
				if((strlen(gDCK) != MAX_DCK_LENGTH) || (gbCheckAutoGenDCK == TRUE))
				{
					GenDCKValue(gDCK);
				}
				if(WriteDCK((BYTE*)gDCK) == TRUE)
				{
					char FullName[MAX_PATH+1] = {0};

					InfoString += CString("Success!");

					InfoString += CString("\r\nAdd DCK&IMEI to the ini file:");
					if((GetConfigFileName(FullName) == TRUE)
						&&(WritePrivateProfileString(tmpIMEI.szIMEI,"IMEI",tmpIMEI.szIMEI,FullName) == TRUE)
						&&(WritePrivateProfileString(tmpIMEI.szIMEI,"DCK ",gDCK,FullName) == TRUE))
					{
						InfoString += CString("Success!");
					}
					else
					{
						InfoString += CString("Failed!");
					}
				}
				else
				{
					InfoString += CString("Failed!");
				}
			}
			InfoString += CString("\r\n\r\n*****************************************************");
			((COTPPancel*)m_Dialog[m_PageSel])->RefreshPancel();
		}
		if(gbCheckPublicKey == TRUE)
		{
			InfoString += CString("\r\nWrite Public key:");
			if(WritePublicKey(gPublicKey) == TRUE)
			{
				InfoString += CString("Success!");
			}
			else
			{
				InfoString += CString("Failed!");
			}
			InfoString += CString("\r\n\r\n*****************************************************");
		}
#endif		
		((COTPPancel*)m_Dialog[m_PageSel])->RefreshPancel();
	}
#ifndef FRV_RELEASE
	else if(m_PageSel == 1)	//Flash Pancel
	{
		if(gbCheckSimLockInfo == TRUE)
		{
			InfoString += CString("\r\nWrite SimLock Info:");
			if(WriteSimLockInfo(gSimLockInfo) == TRUE)
			{
				InfoString += CString("Success!");
			}
			else
			{
				InfoString += CString("Failed!");
			}
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		if(gbCheckPlmnList == TRUE)
		{
			InfoString += CString("\r\nWrite Plmn List:");
			if(WritePlmnList(gPlmnList) == TRUE)
			{
				InfoString += CString("Success!");
			}
			else
			{
				InfoString += CString("Failed!");
			}
			InfoString += CString("\r\n\r\n*****************************************************");
		}
		((CFlashPancel*)m_Dialog[m_PageSel])->RefreshPancel();
	}
	else if(m_PageSel == 2)	//NV Pancel
	{
		RefreshMainDlgMsgBox("");
		InfoString.Format("\r\nNot support this function!");
		((CNVPancel*)m_Dialog[m_PageSel])->RefreshPancel();
	}
#endif
	else
	{
		RefreshMainDlgMsgBox("");
		InfoString += CString("\r\nNot support this function!");
		MessageBox("Not support this function!",NULL,MB_ICONERROR);
	}

	AddInfotoMainDlgMsgBox(InfoString.GetBuffer(0));
	CloseComPort();
}

void CWriteToolDlg::OnSelchangeWritetoolTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_PageSel = m_WriteToolTabCtrl.GetCurSel();
	m_WriteToolTabCtrl.SetCurSel(m_PageSel);

	*pResult = 0;
}

void CWriteToolDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnCancel();
}

void CWriteToolDlg::OnCancel()
{
	MinimizeMainDialog();
}

void CWriteToolDlg::OnOK()
{
}

void CWriteToolDlg::RefreshInformation(char* pInformation)
{
	m_InfoDisplay.Format("%s",pInformation);
	UpdateData(FALSE);
}

void CWriteToolDlg::AddInformation(char* pInformation)
{
	m_InfoDisplay += CString(pInformation);
	UpdateData(FALSE);
}

//如有必要可定义系统的热键
void CWriteToolDlg::InitHotKey()
{
//@**#---2007-03-21 13:57:22 (刘志锋)---#**@
//	::RegisterHotKey(GetSafeHwnd(),1001,MOD_SHIFT,VK_DELETE);
//	::RegisterHotKey(GetSafeHwnd(),1002,MOD_CONTROL,'S');
}

LRESULT CWriteToolDlg::OnHotKey(WPARAM wParam,LPARAM lParam)
{
//@**#---2007-03-21 13:57:35 (刘志锋)---#**@
//	switch((int)wParam)
//	{
//		case 1001:
//			RefreshMainDlgMsgBox("");
//			break;
//		default:
//			break;
//	}
	
	return TRUE;
}

void CWriteToolDlg::OnSelchangeCombo() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ComboBox.GetCurSel();

	if(nIndex < gComPortInfo.ComNum)
	{
		gComPortInfo.ComID = gComPortInfo.ComIDList[nIndex];
		m_HandsetStatus.Format("%d phones connected,use COM%d!",gComPortInfo.ComNum,gComPortInfo.ComID);
		UpdateData(FALSE);
	}
}

BOOL CWriteToolDlg::ReadMEID(OTP_MEID* pMEID)
{
	return Read_OTP_MEID(gComPortInfo.ComID,pMEID);
}

BOOL CWriteToolDlg::WriteMEID(OTP_MEID MEID)
{
	SetMEIDCheckBit(MEID.szMEID);
	return Write_OTP_MEID(gComPortInfo.ComID, &MEID);
}

void CWriteToolDlg::ClearMEIDCheckBit(char *pMEID)
{
	pMEID[14] = 0;
}

void CWriteToolDlg::SetMEIDCheckBit(char *pMEID)
{

}
