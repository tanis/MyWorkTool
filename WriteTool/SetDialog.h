#if !defined(AFX_SETDIALOG_H__02337301_0F4D_4D24_8669_5C02C64A652C__INCLUDED_)
#define AFX_SETDIALOG_H__02337301_0F4D_4D24_8669_5C02C64A652C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetDialog dialog

class SetDialog : public CDialog
{
// Construction
public:
	SetDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SetDialog)
	enum { IDD = IDD_SET_DIALOG };
	CString	m_bt_addr;
	CString	m_hwid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SetDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETDIALOG_H__02337301_0F4D_4D24_8669_5C02C64A652C__INCLUDED_)
