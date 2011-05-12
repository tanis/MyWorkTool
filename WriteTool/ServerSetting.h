#if !defined(AFX_SERVERSETTING_H__BE888F9A_CF24_4BB1_8638_16CA9EBD4530__INCLUDED_)

#define AFX_SERVERSETTING_H__BE888F9A_CF24_4BB1_8638_16CA9EBD4530__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000

// SERVER.h : header file

//

#include "DllParam.h"



/////////////////////////////////////////////////////////////////////////////

// CServerSetting dialog



class CServerSetting : public CDialog

{

// Construction

public:

	CServerSetting(CWnd* pParent = NULL);   // standard constructor



// Dialog Data

	//{{AFX_DATA(CServerSetting)

	enum { IDD = IDD_SERVER_SETTING };

	CIPAddressCtrl	m_IPAddressCtrl;

	CString	m_ProjectName;

	//}}AFX_DATA





// Overrides

	// ClassWizard generated virtual function overrides

	//{{AFX_VIRTUAL(CServerSetting)

	protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//}}AFX_VIRTUAL



// Implementation

protected:

	// Generated message map functions

	//{{AFX_MSG(CServerSetting)

	virtual void OnOK();

	virtual BOOL OnInitDialog();

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



#endif // !defined(AFX_ServerSetting_H__BE888F9A_CF24_4BB1_8638_16CA9EBD4530__INCLUDED_)

