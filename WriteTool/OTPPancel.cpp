// OTPPancel.cpp : implementation file
//

#include "stdafx.h"
#include "WriteTool.h"
#include "OTPPancel.h"
#include "Global.h"
#include "ViewPublicKey.h"
#include "DllParam.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COTPPancel dialog

COTPPancel::COTPPancel(CWnd* pParent /*=NULL*/)
	: CDialog(COTPPancel::IDD, pParent)
{
	//{{AFX_DATA_INIT(COTPPancel)
	m_BTAddress = _T("");
	m_IMEI = _T("");
	m_PublicKeyFileName = _T("");
	m_DCK = _T("");
	m_CheckBTAddr = FALSE;
	m_CheckDCK = FALSE;
	m_CheckIMEI = FALSE;
	m_CheckPublicKey = FALSE;
	m_CheckAutoGen = FALSE;
	m_CheckAutoIncBTAddr = FALSE;
	m_CheckAutoIncIMEI = FALSE;
	m_ESN = _T("");
	m_CheckESN = FALSE;
	m_CheckAutoIncESN = FALSE;
	m_MEID = _T("");
	m_CheckAutoIncMEID = FALSE;
	m_CheckMEID = FALSE;
	//}}AFX_DATA_INIT
}


void COTPPancel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COTPPancel)
	DDX_Control(pDX, IDC_EDIT_ESN, m_CESN);
	DDX_Control(pDX, IDC_EDIT_MEID, m_CMEID);
	DDX_Text(pDX, IDC_EDIT_BT_ADDRESS, m_BTAddress);
	DDV_MaxChars(pDX, m_BTAddress, 12);
	DDX_Text(pDX, IDC_EDIT_IMEI, m_IMEI);
	DDV_MaxChars(pDX, m_IMEI, 14);
	DDX_Text(pDX, IDC_EDIT_PUBLIC_KEY, m_PublicKeyFileName);
	DDX_Text(pDX, IDC_EDIT_DCK, m_DCK);
	DDV_MaxChars(pDX, m_DCK, 16);
	DDX_Check(pDX, IDC_CHECK_BT_ADDR, m_CheckBTAddr);
	DDX_Check(pDX, IDC_CHECK_DCK, m_CheckDCK);
	DDX_Check(pDX, IDC_CHECK_IMEI, m_CheckIMEI);
	DDX_Check(pDX, IDC_CHECK_PUBLIC_KEY, m_CheckPublicKey);
	DDX_Check(pDX, IDC_CHECK_AUTO_GEN, m_CheckAutoGen);
	DDX_Check(pDX, IDC_CHECK_AUTO_INC_BT_ADDR, m_CheckAutoIncBTAddr);
	DDX_Check(pDX, IDC_CHECK_AUTO_INC_IMEI, m_CheckAutoIncIMEI);
	DDX_Text(pDX, IDC_EDIT_ESN, m_ESN);
	DDV_MaxChars(pDX, m_ESN, 8);
	DDX_Check(pDX, IDC_CHECK_ESN, m_CheckESN);
	DDX_Check(pDX, IDC_CHECK_AUTO_INC_ESN, m_CheckAutoIncESN);
	DDX_Text(pDX, IDC_EDIT_MEID, m_MEID);
	DDV_MaxChars(pDX, m_MEID, 14);
	DDX_Check(pDX, IDC_CHECK_AUTO_INC_MEID, m_CheckAutoIncMEID);
	DDX_Check(pDX, IDC_CHECK_MEID, m_CheckMEID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COTPPancel, CDialog)
	//{{AFX_MSG_MAP(COTPPancel)
	ON_EN_CHANGE(IDC_EDIT_IMEI, OnChangeEditImei)
	ON_EN_CHANGE(IDC_EDIT_BT_ADDRESS, OnChangeEditBtAddress)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_IMEI, OnDeltaposSpinImei)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BT_ADDR, OnDeltaposSpinBtAddr)
	ON_BN_CLICKED(IDC_MAKE_DCK, OnMakeDck)
	ON_BN_CLICKED(IDC_SEARCH_PUBLIC_KEY, OnSearchPublicKey)
	ON_BN_CLICKED(IDC_VIEW_PUBLIC_KEY, OnViewPublicKey)
	ON_BN_CLICKED(IDC_CHECK_IMEI, OnCheckImei)
	ON_BN_CLICKED(IDC_CHECK_BT_ADDR, OnCheckBtAddr)
	ON_BN_CLICKED(IDC_CHECK_DCK, OnCheckDck)
	ON_BN_CLICKED(IDC_CHECK_PUBLIC_KEY, OnCheckPublicKey)
	ON_BN_CLICKED(IDC_LOCK_OTP, OnLockOtp)
	ON_BN_CLICKED(IDC_ERASURE_OTP, OnErasureOtp)
	ON_BN_CLICKED(IDC_CHECK_AUTO_GEN, OnCheckAutoGen)
	ON_BN_CLICKED(IDC_CHECK_AUTO_INC_IMEI, OnCheckAutoIncImei)
	ON_BN_CLICKED(IDC_CHECK_AUTO_INC_BT_ADDR, OnCheckAutoIncBtAddr)
	ON_EN_CHANGE(IDC_EDIT_ESN, OnChangeEditEsn)
	ON_BN_CLICKED(IDC_CHECK_AUTO_INC_ESN, OnCheckAutoIncEsn)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ESN, OnDeltaposSpinEsn)
	ON_BN_CLICKED(IDC_CHECK_ESN, OnCheckEsn)
	ON_BN_CLICKED(IDC_CHECK_AUTO_INC_MEID, OnCheckAutoIncMeid)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MEID, OnDeltaposSpinMeid)
	ON_EN_CHANGE(IDC_EDIT_MEID, OnChangeEditMeid)
	ON_BN_CLICKED(IDC_CHECK_MEID, OnCheckMeid)
	ON_BN_CLICKED(IDC_ENTER_MEID, OnEnterMeid)
	ON_WM_KILLFOCUS()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ENTER_ESN, OnEnterEsn)
	//}}AFX_MSG_MAP
	ON_MESSAGE(DM_GETDEFID, OnGetDefID)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COTPPancel message handlers

void COTPPancel::OnChangeEditImei() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	strcpy(gIMEI.szIMEI,m_IMEI.GetBuffer(0));
}

void COTPPancel::OnChangeEditBtAddress() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	strcpy(gBTAddress.szBlueToothAddr,m_BTAddress.GetBuffer(0));
}

void COTPPancel::OnDeltaposSpinImei(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if(!m_IMEI.IsEmpty())
	{
		if(pNMUpDown->iDelta == -1)
		{
			IMEIInc(m_IMEI.GetBuffer(0));
		}
		else
		{
			IMEIDec(m_IMEI.GetBuffer(0));
		}
		UpdateData(FALSE);
		strcpy(gIMEI.szIMEI,m_IMEI.GetBuffer(0));
	}
	*pResult = 0;
}

void COTPPancel::OnDeltaposSpinBtAddr(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if(!m_BTAddress.IsEmpty())
	{
		if(pNMUpDown->iDelta == -1)
		{
			BTAddressInc(m_BTAddress.GetBuffer(0));
		}
		else
		{
			BTAddressDec(m_BTAddress.GetBuffer(0));
		}
		UpdateData(FALSE);
		strcpy(gBTAddress.szBlueToothAddr,m_BTAddress.GetBuffer(0));
	}
	*pResult = 0;
}

void COTPPancel::OnMakeDck() 
{
	// TODO: Add your control notification handler code here
	GenDCKValue(gDCK);
	m_DCK.Format("%s",gDCK);
	UpdateData(FALSE);
}

void COTPPancel::OnSearchPublicKey() 
{
	// TODO: Add your control notification handler code here
	TCHAR szFilter[] = _T("PublicKey Files(*.key)|*.key||");
	CFileDialog filedlg(TRUE, _T("PublicKey Files"), NULL, 
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						szFilter,this);
	char WorkPath[MAX_PATH+1] = {0};

	//保存当前的工作路径
	GetCurrentDirectory(MAX_PATH,WorkPath);
	if(filedlg.DoModal() == IDOK)
	{
		CFile file;
		CFileException fError;

		m_PublicKeyFileName = filedlg.GetPathName();

		file.Open(m_PublicKeyFileName.GetBuffer(0),CFile::modeRead,&fError);
		if(fError.m_cause != CFileException::none)	//file error
		{
			HLOCAL hlocal = NULL;
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,NULL,fError.m_lOsError,0,(LPTSTR)&hlocal,0,NULL);
			CString errorout = (LPTSTR)LocalLock(hlocal);
			AfxMessageBox(errorout,MB_OK|MB_ICONERROR);
			m_PublicKeyFileName = "";
		}
		else
		{
			file.Read(gPublicKey.bytePublicKey,GOZONE_PUBLICKEY_LEN);
			file.Close();
		}
		UpdateData(FALSE);
	}
	//还原当前的工作路径
	SetCurrentDirectory(WorkPath);
}

void COTPPancel::OnViewPublicKey() 
{
	// TODO: Add your control notification handler code here
	CViewPublicKey dlg;
	if(dlg.DoModal() == IDOK)
	{
		//Save PublicKey to file
		CFile file;
		CFileException fError;

		if(m_PublicKeyFileName.IsEmpty() == TRUE)
		{
			return;
		}

		file.Open(m_PublicKeyFileName.GetBuffer(0),CFile::modeWrite,&fError);
		if(fError.m_cause != CFileException::none)	//file error
		{
			HLOCAL hlocal = NULL;
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,NULL,fError.m_lOsError,0,(LPTSTR)&hlocal,0,NULL);
			CString errorout = (LPTSTR)LocalLock(hlocal);
			AfxMessageBox(errorout,MB_OK|MB_ICONERROR);
			return;
		}
		file.Write(gPublicKey.bytePublicKey,GOZONE_PUBLICKEY_LEN);
		file.Close();
	}
}

void COTPPancel::OnCheckImei() 
{
	// TODO: Add your control notification handler code here
	m_CheckIMEI = !m_CheckIMEI;
	gbCheckIMEI = m_CheckIMEI;
}

void COTPPancel::OnCheckBtAddr() 
{
	// TODO: Add your control notification handler code here
	m_CheckBTAddr = !m_CheckBTAddr;
	gbCheckBTAddr = m_CheckBTAddr;
}

void COTPPancel::OnCheckDck() 
{
	// TODO: Add your control notification handler code here
	m_CheckDCK = !m_CheckDCK;
	gbCheckDCK = m_CheckDCK;
}

void COTPPancel::OnCheckPublicKey() 
{
	// TODO: Add your control notification handler code here
	m_CheckPublicKey = !m_CheckPublicKey;
	gbCheckPublicKey = m_CheckPublicKey;
}

void COTPPancel::OnLockOtp() 
{
	// TODO: Add your control notification handler code here
	OTP_ReadWrite OTPReadWrite = {0};
	
	ReadWriteComReq();
	RefreshMainDlgMsgBox("Lock OTP:");

	if(MessageBox("Will Lock OTP, confirm ?",NULL,MB_YESNO|MB_ICONWARNING) == IDYES)
	{
		if(Write_OTP_FLAG(gComPortInfo.ComID,&OTPReadWrite) == TRUE)
		{
			AddInfotoMainDlgMsgBox("Success!");
		}
		else
		{
			AddInfotoMainDlgMsgBox("Failed!");
		}
	}
	else
	{
		AddInfotoMainDlgMsgBox("Cancel!");
	}
	CloseComPort();
}

void COTPPancel::OnErasureOtp() 
{
	// TODO: Add your control notification handler code here

	ReadWriteComReq();
	RefreshMainDlgMsgBox("Erasure OTP:");
	if(MessageBox("Will Erasure OTP, confirm ?",NULL,MB_YESNO|MB_ICONWARNING) == IDYES)
	{
		if(ErasureOTP(gComPortInfo.ComID) == TRUE)
		{
			AddInfotoMainDlgMsgBox("Success!");
		}
		else
		{
			AddInfotoMainDlgMsgBox("Failed!");
		}
	}
	else
	{
		AddInfotoMainDlgMsgBox("Cancel!");
	}
	CloseComPort();
}

BOOL COTPPancel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	RefreshPancel();
	m_DelayEnterTimer = SetTimer(1012, 3000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COTPPancel::RefreshPancel()
{
	m_IMEI = CString(gIMEI.szIMEI);
	m_BTAddress = CString(gBTAddress.szBlueToothAddr);
	m_DCK = CString(gDCK);
	m_ESN = CString(gESN.szESN);
	m_MEID = CString(gMEID.szMEID);
	m_CMEID.SetFocus();
#ifndef FRV_RELEASE
	UpdateData(FALSE);
#endif
}

void COTPPancel::OnCheckAutoGen() 
{
	// TODO: Add your control notification handler code here
	m_CheckAutoGen = !m_CheckAutoGen;
	gbCheckAutoGenDCK = m_CheckAutoGen;
}

void COTPPancel::OnCheckAutoIncImei() 
{
	// TODO: Add your control notification handler code here
	m_CheckAutoIncIMEI = !m_CheckAutoIncIMEI;
	gbCheckAutoIncIMEI = m_CheckAutoIncIMEI;
}

void COTPPancel::OnCheckAutoIncBtAddr() 
{
	// TODO: Add your control notification handler code here
	m_CheckAutoIncBTAddr = !m_CheckAutoIncBTAddr;
	gbCheckAutoIncBTAddr = m_CheckAutoIncBTAddr;
}

void COTPPancel::OnCancel()
{
	MinimizeMainDialog();
}

void COTPPancel::OnOK()
{
}

void COTPPancel::OnChangeEditEsn() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	strcpy(gESN.szESN,m_ESN.GetBuffer(0));
}

void COTPPancel::OnCheckAutoIncEsn() 
{
	// TODO: Add your control notification handler code here
	m_CheckAutoIncESN = !m_CheckAutoIncESN;
	gbCheckAutoIncESN = m_CheckAutoIncESN;
}

void COTPPancel::OnDeltaposSpinEsn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if(!m_ESN.IsEmpty())
	{
		if(pNMUpDown->iDelta == -1)
		{
			ESNInc(m_ESN.GetBuffer(0));
		}
		else
		{
			ESNDec(m_ESN.GetBuffer(0));
		}
		UpdateData(FALSE);
		strcpy(gESN.szESN,m_ESN.GetBuffer(0));
	}
	*pResult = 0;
}

void COTPPancel::OnCheckEsn() 
{
	// TODO: Add your control notification handler code here
	m_CheckESN = !m_CheckESN;
	gbCheckESN = m_CheckESN;
}

void COTPPancel::OnCheckAutoIncMeid() 
{
	// TODO: Add your control notification handler code here
	m_CheckAutoIncMEID = !m_CheckAutoIncMEID;
	gbCheckAutoIncMEID = m_CheckAutoIncMEID;
}

void COTPPancel::OnDeltaposSpinMeid(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(!m_MEID.IsEmpty())
	{
		if(pNMUpDown->iDelta == -1)
		{
			MEIDInc(m_MEID.GetBuffer(0));
		}
		else
		{
			MEIDDec(m_MEID.GetBuffer(0));
		}
		UpdateData(FALSE);
		strcpy(gMEID.szMEID,m_MEID.GetBuffer(0));
	}
	*pResult = 0;
}

void COTPPancel::OnChangeEditMeid() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	strcpy(gMEID.szMEID,m_MEID.GetBuffer(0));
	if (m_MEID.GetLength()==1)
	{
		RefreshMainDlgMsgBox("");	// clear main dialog msg box
	}
}

void COTPPancel::OnCheckMeid() 
{
	// TODO: Add your control notification handler code here
	m_CheckMEID = !m_CheckMEID;
	gbCheckMEID = m_CheckMEID;
}



static char lastMEID[GOZONE_MEID_SIZE*2+1] = "";
static byte allowEnter = TRUE;

void COTPPancel::OnEnterMeid() 
{
	// TODO: Add your control notification handler code here
	RefreshMainDlgMsgBox("");	// clear main dialog msg box
	UpdateData(TRUE);
	if(m_MEID.GetLength()==14 && allowEnter==TRUE)
	{
		//允许客户反复快速多次写
		//if (0 == strcmp(lastMEID,(LPCTSTR)m_MEID))
		//{
		//	m_MEID.Empty();
		//	UpdateData(FALSE);
		//	RefreshMainDlgMsgBox("MEID和上一台重号！");
		//	MessageBox("MEID和上一台重号！",NULL,MB_ICONERROR);
		//}
		//else
		//{
			KillTimer(m_DelayEnterTimer);
			
			strcpy(lastMEID,(LPCTSTR)m_MEID);
			strcpy(gMEID.szMEID,(LPCTSTR)m_MEID);
			NotifyMainDlgOnWrite();
			
			m_MEID.Empty();
			UpdateData(FALSE);
			
			//allowEnter = FALSE;	//允许客户反复快速多次写
			m_DelayEnterTimer = SetTimer(1011, 3000, NULL);
		//}
	}
	else
	{
		m_MEID.Empty();
		UpdateData(FALSE);
		if (allowEnter == FALSE)
		{
			RefreshMainDlgMsgBox("系统忙，请重试！");
		}
		else
		{
			RefreshMainDlgMsgBox("请检查MEID是否为14位！");
		}
	}
}

void COTPPancel::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	
	if (nIDEvent == m_DelayEnterTimer)
		allowEnter = TRUE;
	
	CDialog::OnTimer(nIDEvent);
}

void COTPPancel::OnKillFocus(CWnd *pNewWnd)
{
	CDialog::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	//m_CMEID.SetFocus();
	m_CESN.SetFocus();
}

void COTPPancel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CFont FontTitle;
	FontTitle.CreateFont(50,
		25,
		0, 0, FW_REGULAR, FALSE, FALSE,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FF_DONTCARE, NULL);
	
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(&FontTitle);
	
	
	RECT Rect;
	Rect.left = 180;
	Rect.right = 800;
	Rect.bottom = 400;
	Rect.top = 50;
	dc.DrawText("GoZone", &Rect, 0);
}

// 
LRESULT COTPPancel::OnGetDefID(WPARAM wp, LPARAM lp)
{
	//return MAKELONG(IDC_ENTER_MEID,DC_HASDEFID);
	return MAKELONG(IDC_ENTER_ESN,DC_HASDEFID);
}

static char lastESN[GOZONE_ESN_SIZE*2+1] = "";

void COTPPancel::OnEnterEsn() 
{
	// TODO: Add your control notification handler code here
	RefreshMainDlgMsgBox("");	// clear main dialog msg box
	UpdateData(TRUE);
	if(m_ESN.GetLength()==8 && allowEnter==TRUE)
	{
		//允许客户反复快速多次写
		//if (0 == strcmp(lastMEID,(LPCTSTR)m_MEID))
		//{
		//	m_MEID.Empty();
		//	UpdateData(FALSE);
		//	RefreshMainDlgMsgBox("MEID和上一台重号！");
		//	MessageBox("MEID和上一台重号！",NULL,MB_ICONERROR);
		//}
		//else
		//{
			KillTimer(m_DelayEnterTimer);
			
			strcpy(lastESN,(LPCTSTR)m_ESN);
			strcpy(gESN.szESN,(LPCTSTR)m_ESN);
			NotifyMainDlgOnWrite();
			
			m_ESN.Empty();
			UpdateData(FALSE);
			
			//allowEnter = FALSE;	//允许客户反复快速多次写
			m_DelayEnterTimer = SetTimer(1012, 3000, NULL);
		//}
	}
	else
	{
		m_ESN.Empty();
		UpdateData(FALSE);
		if (allowEnter == FALSE)
		{
			RefreshMainDlgMsgBox("系统忙，请重试！");
		}
		else
		{
			RefreshMainDlgMsgBox("请检查ESN是否为8位！");
		}
	}
}
