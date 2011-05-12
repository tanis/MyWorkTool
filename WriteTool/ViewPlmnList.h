#if !defined(AFX_VIEWPLMNLIST_H__CF2EE495_DCD1_4004_A4FD_E6D7F6C24D0D__INCLUDED_)
#define AFX_VIEWPLMNLIST_H__CF2EE495_DCD1_4004_A4FD_E6D7F6C24D0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewPlmnList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewPlmnList dialog

class CViewPlmnList : public CDialog
{
// Construction
public:
	CViewPlmnList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewPlmnList)
	enum { IDD = IDD_VIEW_PLMNLIST };
	CString	m_CountryCode1;
	CString	m_CountryCode2;
	CString	m_Plmn1_1;
	CString	m_Plmn1_2;
	CString	m_Plmn1_3;
	CString	m_Plmn10_1;
	CString	m_Plmn10_2;
	CString	m_Plmn10_3;
	CString	m_Plmn11_1;
	CString	m_Plmn11_2;
	CString	m_Plmn11_3;
	CString	m_Plmn12_1;
	CString	m_Plmn12_2;
	CString	m_Plmn12_3;
	CString	m_Plmn13_1;
	CString	m_Plmn13_2;
	CString	m_Plmn13_3;
	CString	m_Plmn14_1;
	CString	m_Plmn14_2;
	CString	m_Plmn14_3;
	CString	m_Plmn15_1;
	CString	m_Plmn15_2;
	CString	m_Plmn15_3;
	CString	m_Plmn16_1;
	CString	m_Plmn16_2;
	CString	m_Plmn16_3;
	CString	m_Plmn17_1;
	CString	m_Plmn17_2;
	CString	m_Plmn17_3;
	CString	m_Plmn18_1;
	CString	m_Plmn18_2;
	CString	m_Plmn18_3;
	CString	m_Plmn19_1;
	CString	m_Plmn19_2;
	CString	m_Plmn19_3;
	CString	m_Plmn2_1;
	CString	m_Plmn2_2;
	CString	m_Plmn2_3;
	CString	m_Plmn20_1;
	CString	m_Plmn20_2;
	CString	m_Plmn20_3;
	CString	m_Plmn3_1;
	CString	m_Plmn3_2;
	CString	m_Plmn3_3;
	CString	m_Plmn4_1;
	CString	m_Plmn4_2;
	CString	m_Plmn4_3;
	CString	m_Plmn5_1;
	CString	m_Plmn5_2;
	CString	m_Plmn5_3;
	CString	m_Plmn6_1;
	CString	m_Plmn6_2;
	CString	m_Plmn6_3;
	CString	m_Plmn7_1;
	CString	m_Plmn7_2;
	CString	m_Plmn7_3;
	CString	m_Plmn8_1;
	CString	m_Plmn8_2;
	CString	m_Plmn8_3;
	CString	m_Plmn9_1;
	CString	m_Plmn9_2;
	CString	m_Plmn9_3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewPlmnList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewPlmnList)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWPLMNLIST_H__CF2EE495_DCD1_4004_A4FD_E6D7F6C24D0D__INCLUDED_)
