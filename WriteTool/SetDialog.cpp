// SetDialog.cpp : implementation file
//

#include "stdafx.h"
#include "writetool.h"
#include "SetDialog.h"
#include "SetParam.h"

extern CSetParam gSetParam;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetDialog dialog


SetDialog::SetDialog(CWnd* pParent /*=NULL*/)
	: CDialog(SetDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetDialog)
	m_bt_addr = _T("");
	m_hwid = _T("");
	//}}AFX_DATA_INIT
}


void SetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetDialog)
	DDX_Text(pDX, IDC_BT_ADDR_EDIT, m_bt_addr);
	DDX_Text(pDX, IDC_HWID_EDIT, m_hwid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetDialog, CDialog)
	//{{AFX_MSG_MAP(SetDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetDialog message handlers

void SetDialog::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if (gSetParam.setCfgParam(m_hwid, m_bt_addr))
		CDialog::OnOK();
	else
	{
		MessageBox("输入的数值不合法!", NULL,MB_ICONERROR);
	}
}
