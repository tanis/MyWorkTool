// SERVER.cpp : implementation file
//

#include "stdafx.h"
#include "WriteTool.h"
#include "ServerSetting.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSetting dialog


CServerSetting::CServerSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CServerSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerSetting)
	m_ProjectName = _T("");
	//}}AFX_DATA_INIT
}


void CServerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerSetting)
	DDX_Control(pDX, IDC_SERVER_IPADDRESS, m_IPAddressCtrl);
	DDX_Text(pDX, IDC_PROJECT_NAME, m_ProjectName);
	DDV_MaxChars(pDX, m_ProjectName, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServerSetting, CDialog)
	//{{AFX_MSG_MAP(CServerSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerSetting message handlers

void CServerSetting::OnOK() 
{
	// TODO: Add extra validation here
	BYTE nField0,nField1,nField2,nField3;

	UpdateData(TRUE);
	//Save Project Name
	sprintf(gProjectName,"%s",m_ProjectName.GetBuffer(0));
	m_IPAddressCtrl.GetAddress(nField0,nField1,nField2,nField3);
	sprintf(gIPAddress,"%d.%d.%d.%d",nField0,nField1,nField2,nField3);

	CDialog::OnOK();
}

BOOL CServerSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	BYTE nField0,nField1,nField2,nField3;

	//Save Project Name
	m_ProjectName.Format("%s",gProjectName);
	//Save IP Address
	sscanf(gIPAddress,"%d.%d.%d.%d",&nField0,&nField1,&nField2,&nField3);
	m_IPAddressCtrl.SetAddress(nField0,nField1,nField2,nField3);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
