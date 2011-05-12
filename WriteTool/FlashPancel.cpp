// FlashPancel.cpp : implementation file
//

#include "stdafx.h"
#include "WriteTool.h"
#include "FlashPancel.h"
#include "Global.h"
#include "ViewPlmnList.h"
#include "DllParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CFlashPancel dialog

CFlashPancel::CFlashPancel(CWnd* pParent /*=NULL*/)
	: CDialog(CFlashPancel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlashPancel)
	m_HourLefts = _T("");
	m_InterAttempts = _T("");
	m_LockStatus = _T("");
	m_MinuteLefts = _T("");
	m_PlmnListFileName = _T("");
	m_SecondLefts = _T("");
	m_SeqAttempts = _T("");
	m_CheckPlmnList = FALSE;
	m_CheckSimLockInfo = FALSE;
	//}}AFX_DATA_INIT
}


void CFlashPancel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlashPancel)
	DDX_Text(pDX, IDC_EDIT_HOUR_LEFTS, m_HourLefts);
	DDV_MaxChars(pDX, m_HourLefts, 2);
	DDX_Text(pDX, IDC_EDIT_INTER_ATTEMPTS, m_InterAttempts);
	DDV_MaxChars(pDX, m_InterAttempts, 3);
	DDX_Text(pDX, IDC_EDIT_LOCKSTATUS, m_LockStatus);
	DDV_MaxChars(pDX, m_LockStatus, 1);
	DDX_Text(pDX, IDC_EDIT_MINUTE_LEFTS, m_MinuteLefts);
	DDV_MaxChars(pDX, m_MinuteLefts, 2);
	DDX_Text(pDX, IDC_EDIT_PLMNLIST, m_PlmnListFileName);
	DDX_Text(pDX, IDC_EDIT_SECOND_LEFTS, m_SecondLefts);
	DDV_MaxChars(pDX, m_SecondLefts, 2);
	DDX_Text(pDX, IDC_EDIT_SEQ_ATTEMPTS, m_SeqAttempts);
	DDV_MaxChars(pDX, m_SeqAttempts, 3);
	DDX_Check(pDX, IDC_CHECK_PLMNLIST, m_CheckPlmnList);
	DDX_Check(pDX, IDC_CHECK_SIMLOCK_INFO, m_CheckSimLockInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFlashPancel, CDialog)
	//{{AFX_MSG_MAP(CFlashPancel)
	ON_EN_CHANGE(IDC_EDIT_LOCKSTATUS, OnChangeEditLockstatus)
	ON_EN_CHANGE(IDC_EDIT_SEQ_ATTEMPTS, OnChangeEditSeqAttempts)
	ON_EN_CHANGE(IDC_EDIT_INTER_ATTEMPTS, OnChangeEditInterAttempts)
	ON_EN_CHANGE(IDC_EDIT_HOUR_LEFTS, OnChangeEditHourLefts)
	ON_EN_CHANGE(IDC_EDIT_MINUTE_LEFTS, OnChangeEditMinuteLefts)
	ON_EN_CHANGE(IDC_EDIT_SECOND_LEFTS, OnChangeEditSecondLefts)
	ON_BN_CLICKED(IDC_SEARCH_PLMNLIST, OnSearchPlmnlist)
	ON_BN_CLICKED(IDC_VIEW_PLMNLIST, OnViewPlmnlist)
	ON_BN_CLICKED(IDC_CHECK_SIMLOCK_INFO, OnCheckSimlockInfo)
	ON_BN_CLICKED(IDC_CHECK_PLMNLIST, OnCheckPlmnlist)
	ON_BN_CLICKED(IDC_TURNON_SIMLOCK, OnTurnonSimlock)
	ON_BN_CLICKED(IDC_TURNOFF_SIMLOCK, OnTurnoffSimlock)
	ON_BN_CLICKED(IDC_TURNON_TEST_MENU, OnTurnonTestMenu)
	ON_BN_CLICKED(IDC_TURNOFF_TEST_MENU, OnTurnoffTestMenu)
	ON_BN_CLICKED(IDC_QUERY_VERSION, OnQueryVersion)
#if 0//[zhangjj, 070612,del for auto sign]
	ON_BN_CLICKED(IDC_SIGN_FLASH_DATA, OnSignFlashData)
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlashPancel message handlers

void CFlashPancel::OnChangeEditLockstatus() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	BYTE value;

	UpdateData(TRUE);
	value = (byte)atof(m_LockStatus);
	if(value > 2)
	{
		value = 2;
		m_LockStatus.Format("%d",value);
		UpdateData(FALSE);
	}
	gSimLockInfo.byteLockStatus = value;
}

void CFlashPancel::OnChangeEditSeqAttempts() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	BYTE value;

	UpdateData(TRUE);
	value = (byte)atof(m_SeqAttempts);
	m_SeqAttempts.Format("%d",value);
	UpdateData(FALSE);
	gSimLockInfo.byteSequenceAttemptsLeft = value;
}

void CFlashPancel::OnChangeEditInterAttempts() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	BYTE value;

	UpdateData(TRUE);
	value = (byte)atof(m_InterAttempts);
	m_InterAttempts.Format("%d",value);
	UpdateData(FALSE);
	gSimLockInfo.byteIntervalAttemptsLeft = value;
}

void CFlashPancel::OnChangeEditHourLefts() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	BYTE value;

	UpdateData(TRUE);
	value = (byte)atof(m_HourLefts);
	m_HourLefts.Format("%d",value);
	UpdateData(FALSE);
	gSimLockInfo.byteHoursLeft = value;
}

void CFlashPancel::OnChangeEditMinuteLefts() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	BYTE value;

	UpdateData(TRUE);
	value = (byte)atof(m_MinuteLefts);
	if(value >= 60)
	{
		value = 0;
		m_MinuteLefts.Format("%d",value);
		UpdateData(FALSE);
	}
	gSimLockInfo.byteMinutesLeft = value;
}

void CFlashPancel::OnChangeEditSecondLefts() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	BYTE value;

	UpdateData(TRUE);
	value = (byte)atof(m_SecondLefts);
	if(value >= 60)
	{
		value = 0;
		m_SecondLefts.Format("%d",value);
		UpdateData(FALSE);
	}
	gSimLockInfo.byteSecondsLeft = value;
}

void CFlashPancel::OnSearchPlmnlist() 
{
	// TODO: Add your control notification handler code here
	TCHAR szFilter[] = _T("PlmnList Files(*.inf)|*.inf||");
	CFileDialog filedlg(TRUE, _T("PlmnList Files"), NULL, 
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						szFilter,this);
	char WorkPath[MAX_PATH+1] = {0};

	//保存当前的工作路径
	GetCurrentDirectory(MAX_PATH,WorkPath);

	if(filedlg.DoModal() == IDOK)
	{
		CFile file;
		CFileException fError;

		m_PlmnListFileName = filedlg.GetPathName();

		file.Open(m_PlmnListFileName.GetBuffer(0),CFile::modeRead,&fError);
		if(fError.m_cause != CFileException::none)	//file error
		{
			HLOCAL hlocal = NULL;
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,NULL,fError.m_lOsError,0,(LPTSTR)&hlocal,0,NULL);
			CString errorout = (LPTSTR)LocalLock(hlocal);
			AfxMessageBox(errorout,MB_OK|MB_ICONERROR);
			m_PlmnListFileName = "";
		}
		else
		{
			file.Read(gPlmnList.bytePlmn,sizeof(gPlmnList.bytePlmn));
			file.Read(gPlmnList.CountryCode,sizeof(gPlmnList.CountryCode));
			file.Close();
		}
		UpdateData(FALSE);
	}
	//还原当前的工作路径
	SetCurrentDirectory(WorkPath);
}

void CFlashPancel::OnViewPlmnlist() 
{
	// TODO: Add your control notification handler code here
	CViewPlmnList dlg;
	if(dlg.DoModal() == IDOK)
	{
		//Save PlmnList to file
		CFile file;
		CFileException fError;

		if(m_PlmnListFileName.IsEmpty() == TRUE)
		{
			return;
		}

		file.Open(m_PlmnListFileName.GetBuffer(0),CFile::modeWrite,&fError);
		if(fError.m_cause != CFileException::none)	//file error
		{
			HLOCAL hlocal = NULL;
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,NULL,fError.m_lOsError,0,(LPTSTR)&hlocal,0,NULL);
			CString errorout = (LPTSTR)LocalLock(hlocal);
			AfxMessageBox(errorout,MB_OK|MB_ICONERROR);
			return;
		}
		file.Write(gPlmnList.bytePlmn,sizeof(gPlmnList.bytePlmn));
		file.Write(gPlmnList.CountryCode,sizeof(gPlmnList.CountryCode));
		file.Close();
	}
}

void CFlashPancel::OnCheckSimlockInfo() 
{
	// TODO: Add your control notification handler code here
	m_CheckSimLockInfo = !m_CheckSimLockInfo;
	gbCheckSimLockInfo = m_CheckSimLockInfo;
}

void CFlashPancel::OnCheckPlmnlist() 
{
	// TODO: Add your control notification handler code here
	m_CheckPlmnList = !m_CheckPlmnList;
	gbCheckPlmnList = m_CheckPlmnList;
}

void CFlashPancel::OnTurnonSimlock() 
{
	// TODO: Add your control notification handler code here
	OTP_SimLockSwitch OTPSimLockSwitch={0};

	ReadWriteComReq();
	RefreshMainDlgMsgBox("Turnon Simlock:");

	if(TurnOnSimLockSwitch(gComPortInfo.ComID, &OTPSimLockSwitch) == TRUE)
	{
		AddInfotoMainDlgMsgBox("Success!");
	}
	else
	{
		AddInfotoMainDlgMsgBox("Failed!");
	}
	CloseComPort();
}

void CFlashPancel::OnTurnoffSimlock() 
{
	// TODO: Add your control notification handler code here
	OTP_SimLockSwitch OTPSimLockSwitch={0};

	ReadWriteComReq();
	RefreshMainDlgMsgBox("Turnoff Simlock:");

	if(TurnOffSimLockSwitch(gComPortInfo.ComID, &OTPSimLockSwitch) == TRUE)
	{
		AddInfotoMainDlgMsgBox("Success!");
	}
	else
	{
		AddInfotoMainDlgMsgBox("Failed!");
	}
	CloseComPort();
}

void CFlashPancel::OnTurnonTestMenu() 
{
	// TODO: Add your control notification handler code here
	OTP_EngineeringSwitch OTPEngineeringSwitch;

	ReadWriteComReq();
	RefreshMainDlgMsgBox("Turnon Engineer Switch:");

	if(TurnOnEngineeringSwitch(gComPortInfo.ComID, &OTPEngineeringSwitch) == TRUE)
	{
		AddInfotoMainDlgMsgBox("Success!");
	}
	else
	{
		AddInfotoMainDlgMsgBox("Failed!");
	}
	CloseComPort();
}

void CFlashPancel::OnTurnoffTestMenu() 
{
	// TODO: Add your control notification handler code here
	OTP_EngineeringSwitch OTPEngineeringSwitch;

	ReadWriteComReq();
	RefreshMainDlgMsgBox("Turnoff Engineer Switch:");

	if(TurnOffEngineeringSwitch(gComPortInfo.ComID, &OTPEngineeringSwitch) == TRUE)
	{
		AddInfotoMainDlgMsgBox("Success!");
	}
	else
	{
		AddInfotoMainDlgMsgBox("Failed!");
	}
	CloseComPort();
}

void CFlashPancel::OnQueryVersion() 
{
	// TODO: Add your control notification handler code here
	OTP_Version Version={0};

	ReadWriteComReq();
	RefreshMainDlgMsgBox("Query Version:");

	if(Read_OTP_Version(gComPortInfo.ComID, &Version) == TRUE)
	{
		AddInfotoMainDlgMsgBox(Version.szVersion);
	}
	else
	{
		AddInfotoMainDlgMsgBox("Read Version from UE failed!");
	}
	CloseComPort();
}
#if 0 //[zhangjj, 070612,del for auto sign]
void CFlashPancel::OnSignFlashData() 
{
	// TODO: Add your control notification handler code here
	PSignNVParam SignNVProc = NULL;

	ReadWriteComReq();
	RefreshMainDlgMsgBox("Sign NV Param:");

	SignNVProc = (PSignNVParam)GetProcAddress(ghLibraryDllParam, PROC_SIGN_NVPARAM);

	CheckProcReturnVoid(SignNVProc,"SignNVProc");

	if(SignNVProc(gComPortInfo.ComID) == TRUE)
	{
		AddInfotoMainDlgMsgBox("Success!");
	}
	else
	{
		AddInfotoMainDlgMsgBox("Failed!");
		AddInfotoMainDlgMsgBox("\r\nPlease restart the hanset and try again!");
	}
	CloseComPort();
}
#endif
BOOL CFlashPancel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	RefreshPancel();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFlashPancel::RefreshPancel()
{
	m_LockStatus.Format("%d",gSimLockInfo.byteLockStatus);
	m_SeqAttempts.Format("%d",gSimLockInfo.byteSequenceAttemptsLeft);
	m_InterAttempts.Format("%d",gSimLockInfo.byteIntervalAttemptsLeft);
	m_HourLefts.Format("%d",gSimLockInfo.byteHoursLeft);
	m_MinuteLefts.Format("%d",gSimLockInfo.byteMinutesLeft);
	m_SecondLefts.Format("%d",gSimLockInfo.byteSecondsLeft);
	UpdateData(FALSE);
}

void CFlashPancel::OnCancel()
{
	MinimizeMainDialog();
}

void CFlashPancel::OnOK()
{
}