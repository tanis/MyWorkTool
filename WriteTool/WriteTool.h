// WriteTool.h : main header file for the WRITETOOL application
//

#if !defined(AFX_WRITETOOL_H__19EDFAD6_9325_44BF_B65F_DE680DFFD20C__INCLUDED_)
#define AFX_WRITETOOL_H__19EDFAD6_9325_44BF_B65F_DE680DFFD20C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWriteToolApp:
// See WriteTool.cpp for the implementation of this class
//

class CWriteToolApp : public CWinApp
{
public:
	CWriteToolApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWriteToolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWriteToolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITETOOL_H__19EDFAD6_9325_44BF_B65F_DE680DFFD20C__INCLUDED_)
