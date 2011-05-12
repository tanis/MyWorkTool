#if !defined(AFX_NVPANCEL_H__CB7197BF_6FCE_4C0C_8969_955D71411ED3__INCLUDED_)
#define AFX_NVPANCEL_H__CB7197BF_6FCE_4C0C_8969_955D71411ED3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NVPancel.h : header file
//
#include "Global.h"

/////////////////////////////////////////////////////////////////////////////
// CNVPancel dialog

class CNVPancel : public CDialog
{
// Construction
public:
	CNVPancel(CWnd* pParent = NULL);   // standard constructor

	void RefreshPancel();
// Dialog Data
	//{{AFX_DATA(CNVPancel)
	enum { IDD = IDD_NV_PANCEL };
	CString	m_ExportPathName;
	CString	m_ImportPathName;
	CString	m_BaseAdjust;
	CString	m_GeneralAdjust;
	BOOL	m_CheckBaseAdjust;
	BOOL	m_CheckGeneralAdjust;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNVPancel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL SelectFolderDlg(CString* lpstrFolder);
	BOOL ReadIMEI(OTP_IMEI* pIMEI);
	BOOL ExportAllNVsFromPhone(byte *pDataBuf, UINT *pActualBufLenth);
	BOOL ImportAllNVsIntoPhone(byte *pDataBuf, UINT ActualBufLenth);
	// Generated message map functions
	//{{AFX_MSG(CNVPancel)
	afx_msg void OnSelectExportDirectory();
	afx_msg void OnSelectImportDirectory();
	afx_msg void OnExportNv();
	afx_msg void OnImportNv();
	afx_msg void OnCheckBaseAdjust();
	afx_msg void OnCheckGeneralAdjust();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NVPANCEL_H__CB7197BF_6FCE_4C0C_8969_955D71411ED3__INCLUDED_)
