// WriteToolDlg.h : header file
//
#if !defined(AFX_WRITETOOLDLG_H__E9659DD5_BA3B_4EA3_BECC_F6C1E9DCB105__INCLUDED_)
#define AFX_WRITETOOLDLG_H__E9659DD5_BA3B_4EA3_BECC_F6C1E9DCB105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DLTypedef.h"
#include "DllParam.h"
#include "TabSheet.h"

/////////////////////////////////////////////////////////////////////////////
// CWriteToolDlg dialog

class CWriteToolDlg : public CDialog
{
// Construction
public:
	CWriteToolDlg(CWnd* pParent = NULL);	// standard constructor
	void RefreshInformation(char* pInformation);
	void AddInformation(char* pInformation);

// Dialog Data
	//{{AFX_DATA(CWriteToolDlg)
	enum { IDD = IDD_WRITETOOL_DIALOG };
	CComboBox	m_ComboBox;
	CTabSheet	m_WriteToolTabCtrl;
	CString	m_HandsetStatus;
	CString	m_InfoDisplay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWriteToolDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	HINSTANCE m_hLibraryListComPort;
	TDLGetValidComPortProc* m_GetValidComPortProc;

	UINT m_DetectComTimer;
	CDialog *m_Dialog[3];
	UINT m_PageSel;

	void InitData();
	void ReleaseData();
	//IMEI
	void SetIMEICheckBit(char * pIMEI);
	void ClearIMEICheckBit(char * pIMEI);
	BOOL ReadIMEI(OTP_IMEI* pIMEI);
	BOOL WriteIMEI(OTP_IMEI IMEI);
	BOOL WriteIMEI2(OTP_IMEI2 IMEI);
	//BT Address
	BOOL ReadBTAddress(OTP_BlueToothAddr* pBTAddr);
	BOOL WriteBTAddress(OTP_BlueToothAddr BTAddr);
	//ESN
	//BOOL ReadESNCheckSum(OTP_ESN* pESN);
	BOOL ReadESN(OTP_ESN* pESN);
	BOOL WriteESN(OTP_ESN ESN);
	//MEID
	void SetMEIDCheckBit(char* pMEID);
	void ClearMEIDCheckBit(char* pMEID);
	BOOL ReadMEID(OTP_MEID* pMEID);
	BOOL WriteMEID(OTP_MEID MEID);
	//Hash&DCK
	BOOL ReadHash(OTP_Hash* pHash);
	BOOL WriteDCK(BYTE* pDCK);
	//Public Key
	BOOL ReadPublicKey(OTP_PublicKey* pPublicKey);
	BOOL WritePublicKey(OTP_PublicKey PublicKey);
	//Plmn List
	BOOL ReadPlmnList(OTP_Plmn *pPlmnList);
	BOOL WritePlmnList(OTP_Plmn PlmnList);
	//SimLock Info
	BOOL ReadSimLockInfo(OTP_SIMLockInfo *pSimLockInfo);
	BOOL WriteSimLockInfo(OTP_SIMLockInfo SimLockInfo);
	//Read Hdet OFF
	BOOL GetHdetOffMark(char *pHdetOff);
	//Read Hdet SPN
	BOOL GetHdetSPNMark(char *pHdetSpn);

	//UI
	void ActivateTabDialogs();
	//Cfg file
	BOOL GetConfigFileName(char* pFileName);
	byte* ReadDLFile(const char* pFileName, size_t* FileLen); //zhangjj 070703 add for devicelist.dat

	void InitHotKey();
	afx_msg LRESULT OnHotKey(WPARAM wParam,LPARAM lParam);
	// Generated message map functions
	//{{AFX_MSG(CWriteToolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFileSettings();
	afx_msg void OnHelpAbout();
	afx_msg void OnFileExit();
	afx_msg void OnRead();
	afx_msg void OnWrite();
	afx_msg void OnSelchangeWritetoolTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	afx_msg void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITETOOLDLG_H__E9659DD5_BA3B_4EA3_BECC_F6C1E9DCB105__INCLUDED_)



