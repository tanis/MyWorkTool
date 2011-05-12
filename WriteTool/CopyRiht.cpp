// CopyRiht.cpp : implementation file
//

#include "stdafx.h"
#include "WriteTool.h"
#include "CopyRiht.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCopyRight dialog


CCopyRight::CCopyRight(CWnd* pParent /*=NULL*/)
	: CDialog(CCopyRight::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCopyRight)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCopyRight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopyRight)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCopyRight, CDialog)
	//{{AFX_MSG_MAP(CCopyRight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyRight message handlers

void CCopyRight::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
