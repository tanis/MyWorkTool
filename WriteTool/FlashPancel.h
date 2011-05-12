#if !defined(AFX_FLASHPANCEL_H__B052CE43_9188_466B_A2F1_B4963D9B8875__INCLUDED_)
#define AFX_FLASHPANCEL_H__B052CE43_9188_466B_A2F1_B4963D9B8875__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlashPancel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlashPancel dialog

class CFlashPancel : public CDialog
{
// Construction
public:
	CFlashPancel(CWnd* pParent = NULL);   // standard constructor

	void RefreshPancel();
// Dialog Data
	//{{AFX_DATA(CFlashPancel)
	enum { IDD = IDD_FLASH_PANCEL };
	CString	m_HourLefts;
	CString	m_InterAttempts;
	CString	m_LockStatus;
	CString	m_MinuteLefts;
	CString	m_PlmnListFileName;
	CString	m_SecondLefts;
	CString	m_SeqAttempts;
	BOOL	m_CheckPlmnList;
	BOOL	m_CheckSimLockInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlashPancel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFlashPancel)
	afx_msg void OnChangeEditLockstatus();
	afx_msg void OnChangeEditSeqAttempts();
	afx_msg void OnChangeEditInterAttempts();
	afx_msg void OnChangeEditHourLefts();
	afx_msg void OnChangeEditMinuteLefts();
	afx_msg void OnChangeEditSecondLefts();
	afx_msg void OnSearchPlmnlist();
	afx_msg void OnViewPlmnlist();
	afx_msg void OnCheckSimlockInfo();
	afx_msg void OnCheckPlmnlist();
	afx_msg void OnTurnonSimlock();
	afx_msg void OnTurnoffSimlock();
	afx_msg void OnTurnonTestMenu();
	afx_msg void OnTurnoffTestMenu();
	afx_msg void OnQueryVersion();
#if 0//[zhangjj, 070612,del for auto sign]
	afx_msg void OnSignFlashData();
#endif
	virtual BOOL OnInitDialog();
	afx_msg void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLASHPANCEL_H__B052CE43_9188_466B_A2F1_B4963D9B8875__INCLUDED_)
