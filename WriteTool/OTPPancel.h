#if !defined(AFX_OTPPANCEL_H__1F363B85_3D71_4FED_8ED2_0E4D314DB394__INCLUDED_)
#define AFX_OTPPANCEL_H__1F363B85_3D71_4FED_8ED2_0E4D314DB394__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OTPPancel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COTPPancel dialog

class COTPPancel : public CDialog
{
// Construction
public:
	COTPPancel(CWnd* pParent = NULL);   // standard constructor
	void RefreshPancel();
// Dialog Data
	//{{AFX_DATA(COTPPancel)
	enum { IDD = IDD_OTP_PANCEL };
	CEdit	m_CIMEI;
	CEdit	m_CESN;
	CEdit	m_CMEID;
	CString	m_BTAddress;
	CString	m_IMEI;
	CString	m_PublicKeyFileName;
	CString	m_DCK;
	BOOL	m_CheckBTAddr;
	BOOL	m_CheckDCK;
	BOOL	m_CheckIMEI;
	BOOL	m_CheckPublicKey;
	BOOL	m_CheckAutoGen;
	BOOL	m_CheckAutoIncBTAddr;
	BOOL	m_CheckAutoIncIMEI;
	CString	m_ESN;
	BOOL	m_CheckESN;
	BOOL	m_CheckAutoIncESN;
	CString	m_MEID;
	BOOL	m_CheckAutoIncMEID;
	BOOL	m_CheckMEID;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COTPPancel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	LRESULT OnGetDefID(WPARAM wp, LPARAM lp);
	void OnPaint();
	void OnKillFocus(CWnd* pNewWnd);
	void OnTimer(UINT nIDEvent);
	UINT m_DelayEnterTimer;
	// Generated message map functions
	//{{AFX_MSG(COTPPancel)
	afx_msg void OnChangeEditImei();
	afx_msg void OnChangeEditBtAddress();
	afx_msg void OnDeltaposSpinImei(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinBtAddr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMakeDck();
	afx_msg void OnSearchPublicKey();
	afx_msg void OnViewPublicKey();
	afx_msg void OnCheckImei();
	afx_msg void OnCheckBtAddr();
	afx_msg void OnCheckDck();
	afx_msg void OnCheckPublicKey();
	afx_msg void OnLockOtp();
	afx_msg void OnErasureOtp();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckAutoGen();
	afx_msg void OnCheckAutoIncImei();
	afx_msg void OnCheckAutoIncBtAddr();
	afx_msg void OnCancel();
	virtual void OnOK();
	afx_msg void OnChangeEditEsn();
	afx_msg void OnCheckAutoIncEsn();
	afx_msg void OnDeltaposSpinEsn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckEsn();
	afx_msg void OnCheckAutoIncMeid();
	afx_msg void OnDeltaposSpinMeid(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditMeid();
	afx_msg void OnCheckMeid();
	afx_msg void OnEnterMeid();
	afx_msg void OnEnterEsn();
	afx_msg void OnEnterImei();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTPPANCEL_H__1F363B85_3D71_4FED_8ED2_0E4D314DB394__INCLUDED_)
