#if !defined(AFX_COPYRIHT_H__5E763191_5628_4C9A_A760_F9D99078083D__INCLUDED_)
#define AFX_COPYRIHT_H__5E763191_5628_4C9A_A760_F9D99078083D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CopyRiht.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCopyRight dialog

class CCopyRight : public CDialog
{
// Construction
public:
	CCopyRight(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCopyRight)
	enum { IDD = IDD_COPYRIGHT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCopyRight)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCopyRight)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYRIHT_H__5E763191_5628_4C9A_A760_F9D99078083D__INCLUDED_)
