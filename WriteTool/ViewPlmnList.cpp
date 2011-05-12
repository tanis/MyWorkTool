// ViewPlmnList.cpp : implementation file
//

#include "stdafx.h"
#include "WriteTool.h"
#include "ViewPlmnList.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewPlmnList dialog


CViewPlmnList::CViewPlmnList(CWnd* pParent /*=NULL*/)
	: CDialog(CViewPlmnList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewPlmnList)
	m_CountryCode1 = _T("");
	m_CountryCode2 = _T("");
	m_Plmn1_1 = _T("");
	m_Plmn1_2 = _T("");
	m_Plmn1_3 = _T("");
	m_Plmn10_1 = _T("");
	m_Plmn10_2 = _T("");
	m_Plmn10_3 = _T("");
	m_Plmn11_1 = _T("");
	m_Plmn11_2 = _T("");
	m_Plmn11_3 = _T("");
	m_Plmn12_1 = _T("");
	m_Plmn12_2 = _T("");
	m_Plmn12_3 = _T("");
	m_Plmn13_1 = _T("");
	m_Plmn13_2 = _T("");
	m_Plmn13_3 = _T("");
	m_Plmn14_1 = _T("");
	m_Plmn14_2 = _T("");
	m_Plmn14_3 = _T("");
	m_Plmn15_1 = _T("");
	m_Plmn15_2 = _T("");
	m_Plmn15_3 = _T("");
	m_Plmn16_1 = _T("");
	m_Plmn16_2 = _T("");
	m_Plmn16_3 = _T("");
	m_Plmn17_1 = _T("");
	m_Plmn17_2 = _T("");
	m_Plmn17_3 = _T("");
	m_Plmn18_1 = _T("");
	m_Plmn18_2 = _T("");
	m_Plmn18_3 = _T("");
	m_Plmn19_1 = _T("");
	m_Plmn19_2 = _T("");
	m_Plmn19_3 = _T("");
	m_Plmn2_1 = _T("");
	m_Plmn2_2 = _T("");
	m_Plmn2_3 = _T("");
	m_Plmn20_1 = _T("");
	m_Plmn20_2 = _T("");
	m_Plmn20_3 = _T("");
	m_Plmn3_1 = _T("");
	m_Plmn3_2 = _T("");
	m_Plmn3_3 = _T("");
	m_Plmn4_1 = _T("");
	m_Plmn4_2 = _T("");
	m_Plmn4_3 = _T("");
	m_Plmn5_1 = _T("");
	m_Plmn5_2 = _T("");
	m_Plmn5_3 = _T("");
	m_Plmn6_1 = _T("");
	m_Plmn6_2 = _T("");
	m_Plmn6_3 = _T("");
	m_Plmn7_1 = _T("");
	m_Plmn7_2 = _T("");
	m_Plmn7_3 = _T("");
	m_Plmn8_1 = _T("");
	m_Plmn8_2 = _T("");
	m_Plmn8_3 = _T("");
	m_Plmn9_1 = _T("");
	m_Plmn9_2 = _T("");
	m_Plmn9_3 = _T("");
	//}}AFX_DATA_INIT
}


void CViewPlmnList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewPlmnList)
	DDX_Text(pDX, IDC_COUNTRY_CODE1, m_CountryCode1);
	DDV_MaxChars(pDX, m_CountryCode1, 2);
	DDX_Text(pDX, IDC_COUNTRY_CODE2, m_CountryCode2);
	DDV_MaxChars(pDX, m_CountryCode2, 2);
	DDX_Text(pDX, IDC_PLMN1_1, m_Plmn1_1);
	DDV_MaxChars(pDX, m_Plmn1_1, 2);
	DDX_Text(pDX, IDC_PLMN1_2, m_Plmn1_2);
	DDV_MaxChars(pDX, m_Plmn1_2, 2);
	DDX_Text(pDX, IDC_PLMN1_3, m_Plmn1_3);
	DDV_MaxChars(pDX, m_Plmn1_3, 2);
	DDX_Text(pDX, IDC_PLMN10_1, m_Plmn10_1);
	DDV_MaxChars(pDX, m_Plmn10_1, 2);
	DDX_Text(pDX, IDC_PLMN10_2, m_Plmn10_2);
	DDV_MaxChars(pDX, m_Plmn10_2, 2);
	DDX_Text(pDX, IDC_PLMN10_3, m_Plmn10_3);
	DDV_MaxChars(pDX, m_Plmn10_3, 2);
	DDX_Text(pDX, IDC_PLMN11_1, m_Plmn11_1);
	DDV_MaxChars(pDX, m_Plmn11_1, 2);
	DDX_Text(pDX, IDC_PLMN11_2, m_Plmn11_2);
	DDV_MaxChars(pDX, m_Plmn11_2, 2);
	DDX_Text(pDX, IDC_PLMN11_3, m_Plmn11_3);
	DDV_MaxChars(pDX, m_Plmn11_3, 2);
	DDX_Text(pDX, IDC_PLMN12_1, m_Plmn12_1);
	DDV_MaxChars(pDX, m_Plmn12_1, 2);
	DDX_Text(pDX, IDC_PLMN12_2, m_Plmn12_2);
	DDV_MaxChars(pDX, m_Plmn12_2, 2);
	DDX_Text(pDX, IDC_PLMN12_3, m_Plmn12_3);
	DDV_MaxChars(pDX, m_Plmn12_3, 2);
	DDX_Text(pDX, IDC_PLMN13_1, m_Plmn13_1);
	DDV_MaxChars(pDX, m_Plmn13_1, 2);
	DDX_Text(pDX, IDC_PLMN13_2, m_Plmn13_2);
	DDV_MaxChars(pDX, m_Plmn13_2, 2);
	DDX_Text(pDX, IDC_PLMN13_3, m_Plmn13_3);
	DDV_MaxChars(pDX, m_Plmn13_3, 2);
	DDX_Text(pDX, IDC_PLMN14_1, m_Plmn14_1);
	DDV_MaxChars(pDX, m_Plmn14_1, 2);
	DDX_Text(pDX, IDC_PLMN14_2, m_Plmn14_2);
	DDV_MaxChars(pDX, m_Plmn14_2, 2);
	DDX_Text(pDX, IDC_PLMN14_3, m_Plmn14_3);
	DDV_MaxChars(pDX, m_Plmn14_3, 2);
	DDX_Text(pDX, IDC_PLMN15_1, m_Plmn15_1);
	DDV_MaxChars(pDX, m_Plmn15_1, 2);
	DDX_Text(pDX, IDC_PLMN15_2, m_Plmn15_2);
	DDV_MaxChars(pDX, m_Plmn15_2, 2);
	DDX_Text(pDX, IDC_PLMN15_3, m_Plmn15_3);
	DDV_MaxChars(pDX, m_Plmn15_3, 2);
	DDX_Text(pDX, IDC_PLMN16_1, m_Plmn16_1);
	DDV_MaxChars(pDX, m_Plmn16_1, 2);
	DDX_Text(pDX, IDC_PLMN16_2, m_Plmn16_2);
	DDV_MaxChars(pDX, m_Plmn16_2, 2);
	DDX_Text(pDX, IDC_PLMN16_3, m_Plmn16_3);
	DDV_MaxChars(pDX, m_Plmn16_3, 2);
	DDX_Text(pDX, IDC_PLMN17_1, m_Plmn17_1);
	DDV_MaxChars(pDX, m_Plmn17_1, 2);
	DDX_Text(pDX, IDC_PLMN17_2, m_Plmn17_2);
	DDV_MaxChars(pDX, m_Plmn17_2, 2);
	DDX_Text(pDX, IDC_PLMN17_3, m_Plmn17_3);
	DDV_MaxChars(pDX, m_Plmn17_3, 2);
	DDX_Text(pDX, IDC_PLMN18_1, m_Plmn18_1);
	DDV_MaxChars(pDX, m_Plmn18_1, 2);
	DDX_Text(pDX, IDC_PLMN18_2, m_Plmn18_2);
	DDV_MaxChars(pDX, m_Plmn18_2, 2);
	DDX_Text(pDX, IDC_PLMN18_3, m_Plmn18_3);
	DDV_MaxChars(pDX, m_Plmn18_3, 2);
	DDX_Text(pDX, IDC_PLMN19_1, m_Plmn19_1);
	DDV_MaxChars(pDX, m_Plmn19_1, 2);
	DDX_Text(pDX, IDC_PLMN19_2, m_Plmn19_2);
	DDV_MaxChars(pDX, m_Plmn19_2, 2);
	DDX_Text(pDX, IDC_PLMN19_3, m_Plmn19_3);
	DDV_MaxChars(pDX, m_Plmn19_3, 2);
	DDX_Text(pDX, IDC_PLMN2_1, m_Plmn2_1);
	DDV_MaxChars(pDX, m_Plmn2_1, 2);
	DDX_Text(pDX, IDC_PLMN2_2, m_Plmn2_2);
	DDV_MaxChars(pDX, m_Plmn2_2, 2);
	DDX_Text(pDX, IDC_PLMN2_3, m_Plmn2_3);
	DDV_MaxChars(pDX, m_Plmn2_3, 2);
	DDX_Text(pDX, IDC_PLMN20_1, m_Plmn20_1);
	DDV_MaxChars(pDX, m_Plmn20_1, 2);
	DDX_Text(pDX, IDC_PLMN20_2, m_Plmn20_2);
	DDV_MaxChars(pDX, m_Plmn20_2, 2);
	DDX_Text(pDX, IDC_PLMN20_3, m_Plmn20_3);
	DDV_MaxChars(pDX, m_Plmn20_3, 2);
	DDX_Text(pDX, IDC_PLMN3_1, m_Plmn3_1);
	DDV_MaxChars(pDX, m_Plmn3_1, 2);
	DDX_Text(pDX, IDC_PLMN3_2, m_Plmn3_2);
	DDV_MaxChars(pDX, m_Plmn3_2, 2);
	DDX_Text(pDX, IDC_PLMN3_3, m_Plmn3_3);
	DDV_MaxChars(pDX, m_Plmn3_3, 2);
	DDX_Text(pDX, IDC_PLMN4_1, m_Plmn4_1);
	DDV_MaxChars(pDX, m_Plmn4_1, 2);
	DDX_Text(pDX, IDC_PLMN4_2, m_Plmn4_2);
	DDV_MaxChars(pDX, m_Plmn4_2, 2);
	DDX_Text(pDX, IDC_PLMN4_3, m_Plmn4_3);
	DDV_MaxChars(pDX, m_Plmn4_3, 2);
	DDX_Text(pDX, IDC_PLMN5_1, m_Plmn5_1);
	DDV_MaxChars(pDX, m_Plmn5_1, 2);
	DDX_Text(pDX, IDC_PLMN5_2, m_Plmn5_2);
	DDV_MaxChars(pDX, m_Plmn5_2, 2);
	DDX_Text(pDX, IDC_PLMN5_3, m_Plmn5_3);
	DDV_MaxChars(pDX, m_Plmn5_3, 2);
	DDX_Text(pDX, IDC_PLMN6_1, m_Plmn6_1);
	DDV_MaxChars(pDX, m_Plmn6_1, 2);
	DDX_Text(pDX, IDC_PLMN6_2, m_Plmn6_2);
	DDV_MaxChars(pDX, m_Plmn6_2, 2);
	DDX_Text(pDX, IDC_PLMN6_3, m_Plmn6_3);
	DDV_MaxChars(pDX, m_Plmn6_3, 2);
	DDX_Text(pDX, IDC_PLMN7_1, m_Plmn7_1);
	DDV_MaxChars(pDX, m_Plmn7_1, 2);
	DDX_Text(pDX, IDC_PLMN7_2, m_Plmn7_2);
	DDV_MaxChars(pDX, m_Plmn7_2, 2);
	DDX_Text(pDX, IDC_PLMN7_3, m_Plmn7_3);
	DDV_MaxChars(pDX, m_Plmn7_3, 2);
	DDX_Text(pDX, IDC_PLMN8_1, m_Plmn8_1);
	DDV_MaxChars(pDX, m_Plmn8_1, 2);
	DDX_Text(pDX, IDC_PLMN8_2, m_Plmn8_2);
	DDV_MaxChars(pDX, m_Plmn8_2, 2);
	DDX_Text(pDX, IDC_PLMN8_3, m_Plmn8_3);
	DDV_MaxChars(pDX, m_Plmn8_3, 2);
	DDX_Text(pDX, IDC_PLMN9_1, m_Plmn9_1);
	DDV_MaxChars(pDX, m_Plmn9_1, 2);
	DDX_Text(pDX, IDC_PLMN9_2, m_Plmn9_2);
	DDV_MaxChars(pDX, m_Plmn9_2, 2);
	DDX_Text(pDX, IDC_PLMN9_3, m_Plmn9_3);
	DDV_MaxChars(pDX, m_Plmn9_3, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewPlmnList, CDialog)
	//{{AFX_MSG_MAP(CViewPlmnList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewPlmnList message handlers

void CViewPlmnList::OnOK() 
{
	// TODO: Add extra validation here
	OTP_Plmn tmpPlmnList={0};

	UpdateData(TRUE);
	
	//Country Code
	ChangeDataFromHexString(m_CountryCode1,&tmpPlmnList.CountryCode[0]);
	ChangeDataFromHexString(m_CountryCode2,&tmpPlmnList.CountryCode[1]);
	//PLMN 01
	ChangeDataFromHexString(m_Plmn1_1,&tmpPlmnList.bytePlmn[0][0]);
	ChangeDataFromHexString(m_Plmn1_2,&tmpPlmnList.bytePlmn[0][1]);
	ChangeDataFromHexString(m_Plmn1_3,&tmpPlmnList.bytePlmn[0][2]);
	//PLMN 02
	ChangeDataFromHexString(m_Plmn2_1,&tmpPlmnList.bytePlmn[1][0]);
	ChangeDataFromHexString(m_Plmn2_2,&tmpPlmnList.bytePlmn[1][1]);
	ChangeDataFromHexString(m_Plmn2_3,&tmpPlmnList.bytePlmn[1][2]);
	//PLMN 03
	ChangeDataFromHexString(m_Plmn3_1,&tmpPlmnList.bytePlmn[2][0]);
	ChangeDataFromHexString(m_Plmn3_2,&tmpPlmnList.bytePlmn[2][1]);
	ChangeDataFromHexString(m_Plmn3_3,&tmpPlmnList.bytePlmn[2][2]);
	//PLMN 04
	ChangeDataFromHexString(m_Plmn4_1,&tmpPlmnList.bytePlmn[3][0]);
	ChangeDataFromHexString(m_Plmn4_2,&tmpPlmnList.bytePlmn[3][1]);
	ChangeDataFromHexString(m_Plmn4_3,&tmpPlmnList.bytePlmn[3][2]);
	//PLMN 05
	ChangeDataFromHexString(m_Plmn5_1,&tmpPlmnList.bytePlmn[4][0]);
	ChangeDataFromHexString(m_Plmn5_2,&tmpPlmnList.bytePlmn[4][1]);
	ChangeDataFromHexString(m_Plmn5_3,&tmpPlmnList.bytePlmn[4][2]);
	//PLMN 06
	ChangeDataFromHexString(m_Plmn6_1,&tmpPlmnList.bytePlmn[5][0]);
	ChangeDataFromHexString(m_Plmn6_2,&tmpPlmnList.bytePlmn[5][1]);
	ChangeDataFromHexString(m_Plmn6_3,&tmpPlmnList.bytePlmn[5][2]);
	//PLMN 07
	ChangeDataFromHexString(m_Plmn7_1,&tmpPlmnList.bytePlmn[6][0]);
	ChangeDataFromHexString(m_Plmn7_2,&tmpPlmnList.bytePlmn[6][1]);
	ChangeDataFromHexString(m_Plmn7_3,&tmpPlmnList.bytePlmn[6][2]);
	//PLMN 08
	ChangeDataFromHexString(m_Plmn8_1,&tmpPlmnList.bytePlmn[7][0]);
	ChangeDataFromHexString(m_Plmn8_2,&tmpPlmnList.bytePlmn[7][1]);
	ChangeDataFromHexString(m_Plmn8_3,&tmpPlmnList.bytePlmn[7][2]);
	//PLMN 09
	ChangeDataFromHexString(m_Plmn9_1,&tmpPlmnList.bytePlmn[8][0]);
	ChangeDataFromHexString(m_Plmn9_2,&tmpPlmnList.bytePlmn[8][1]);
	ChangeDataFromHexString(m_Plmn9_3,&tmpPlmnList.bytePlmn[8][2]);
	//PLMN 10
	ChangeDataFromHexString(m_Plmn10_1,&tmpPlmnList.bytePlmn[9][0]);
	ChangeDataFromHexString(m_Plmn10_2,&tmpPlmnList.bytePlmn[9][1]);
	ChangeDataFromHexString(m_Plmn10_3,&tmpPlmnList.bytePlmn[9][2]);
	//PLMN 11
	ChangeDataFromHexString(m_Plmn11_1,&tmpPlmnList.bytePlmn[10][0]);
	ChangeDataFromHexString(m_Plmn11_2,&tmpPlmnList.bytePlmn[10][1]);
	ChangeDataFromHexString(m_Plmn11_3,&tmpPlmnList.bytePlmn[10][2]);
	//PLMN 12
	ChangeDataFromHexString(m_Plmn12_1,&tmpPlmnList.bytePlmn[11][0]);
	ChangeDataFromHexString(m_Plmn12_2,&tmpPlmnList.bytePlmn[11][1]);
	ChangeDataFromHexString(m_Plmn12_3,&tmpPlmnList.bytePlmn[11][2]);
	//PLMN 13
	ChangeDataFromHexString(m_Plmn13_1,&tmpPlmnList.bytePlmn[12][0]);
	ChangeDataFromHexString(m_Plmn13_2,&tmpPlmnList.bytePlmn[12][1]);
	ChangeDataFromHexString(m_Plmn13_3,&tmpPlmnList.bytePlmn[12][2]);
	//PLMN 14
	ChangeDataFromHexString(m_Plmn14_1,&tmpPlmnList.bytePlmn[13][0]);
	ChangeDataFromHexString(m_Plmn14_2,&tmpPlmnList.bytePlmn[13][1]);
	ChangeDataFromHexString(m_Plmn14_3,&tmpPlmnList.bytePlmn[13][2]);
	//PLMN 15
	ChangeDataFromHexString(m_Plmn15_1,&tmpPlmnList.bytePlmn[14][0]);
	ChangeDataFromHexString(m_Plmn15_2,&tmpPlmnList.bytePlmn[14][1]);
	ChangeDataFromHexString(m_Plmn15_3,&tmpPlmnList.bytePlmn[14][2]);
	//PLMN 16
	ChangeDataFromHexString(m_Plmn16_1,&tmpPlmnList.bytePlmn[15][0]);
	ChangeDataFromHexString(m_Plmn16_2,&tmpPlmnList.bytePlmn[15][1]);
	ChangeDataFromHexString(m_Plmn16_3,&tmpPlmnList.bytePlmn[15][2]);
	//PLMN 17
	ChangeDataFromHexString(m_Plmn17_1,&tmpPlmnList.bytePlmn[16][0]);
	ChangeDataFromHexString(m_Plmn17_2,&tmpPlmnList.bytePlmn[16][1]);
	ChangeDataFromHexString(m_Plmn17_3,&tmpPlmnList.bytePlmn[16][2]);
	//PLMN 18
	ChangeDataFromHexString(m_Plmn18_1,&tmpPlmnList.bytePlmn[17][0]);
	ChangeDataFromHexString(m_Plmn18_2,&tmpPlmnList.bytePlmn[17][1]);
	ChangeDataFromHexString(m_Plmn18_3,&tmpPlmnList.bytePlmn[17][2]);
	//PLMN 19
	ChangeDataFromHexString(m_Plmn19_1,&tmpPlmnList.bytePlmn[18][0]);
	ChangeDataFromHexString(m_Plmn19_2,&tmpPlmnList.bytePlmn[18][1]);
	ChangeDataFromHexString(m_Plmn19_3,&tmpPlmnList.bytePlmn[18][2]);
	//PLMN 20
	ChangeDataFromHexString(m_Plmn20_1,&tmpPlmnList.bytePlmn[19][0]);
	ChangeDataFromHexString(m_Plmn20_2,&tmpPlmnList.bytePlmn[19][1]);
	ChangeDataFromHexString(m_Plmn20_3,&tmpPlmnList.bytePlmn[19][2]);

	//Save PlmnList&CountryCode to the global variable
	memcpy(gPlmnList.bytePlmn,tmpPlmnList.bytePlmn,sizeof(gPlmnList.bytePlmn));
	memcpy(gPlmnList.CountryCode,tmpPlmnList.CountryCode,sizeof(gPlmnList.CountryCode));

	CDialog::OnOK();
}

void CViewPlmnList::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CViewPlmnList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_CountryCode1.Format("%02x",gPlmnList.CountryCode[0]);
	m_CountryCode2.Format("%02x",gPlmnList.CountryCode[1]);

	//PLMN 01
	m_Plmn1_1.Format("%02x",gPlmnList.bytePlmn[0][0]);
	m_Plmn1_2.Format("%02x",gPlmnList.bytePlmn[0][1]);
	m_Plmn1_3.Format("%02x",gPlmnList.bytePlmn[0][2]);
	//PLMN 02
	m_Plmn2_1.Format("%02x",gPlmnList.bytePlmn[1][0]);
	m_Plmn2_2.Format("%02x",gPlmnList.bytePlmn[1][1]);
	m_Plmn2_3.Format("%02x",gPlmnList.bytePlmn[1][2]);
	//PLMN 03
	m_Plmn3_1.Format("%02x",gPlmnList.bytePlmn[2][0]);
	m_Plmn3_2.Format("%02x",gPlmnList.bytePlmn[2][1]);
	m_Plmn3_3.Format("%02x",gPlmnList.bytePlmn[2][2]);
	//PLMN 04
	m_Plmn4_1.Format("%02x",gPlmnList.bytePlmn[3][0]);
	m_Plmn4_2.Format("%02x",gPlmnList.bytePlmn[3][1]);
	m_Plmn4_3.Format("%02x",gPlmnList.bytePlmn[3][2]);
	//PLMN 05
	m_Plmn5_1.Format("%02x",gPlmnList.bytePlmn[4][0]);
	m_Plmn5_2.Format("%02x",gPlmnList.bytePlmn[4][1]);
	m_Plmn5_3.Format("%02x",gPlmnList.bytePlmn[4][2]);
	//PLMN 06
	m_Plmn6_1.Format("%02x",gPlmnList.bytePlmn[5][0]);
	m_Plmn6_2.Format("%02x",gPlmnList.bytePlmn[5][1]);
	m_Plmn6_3.Format("%02x",gPlmnList.bytePlmn[5][2]);
	//PLMN 07
	m_Plmn7_1.Format("%02x",gPlmnList.bytePlmn[6][0]);
	m_Plmn7_2.Format("%02x",gPlmnList.bytePlmn[6][1]);
	m_Plmn7_3.Format("%02x",gPlmnList.bytePlmn[6][2]);
	//PLMN 08
	m_Plmn8_1.Format("%02x",gPlmnList.bytePlmn[7][0]);
	m_Plmn8_2.Format("%02x",gPlmnList.bytePlmn[7][1]);
	m_Plmn8_3.Format("%02x",gPlmnList.bytePlmn[7][2]);
	//PLMN 09
	m_Plmn9_1.Format("%02x",gPlmnList.bytePlmn[8][0]);
	m_Plmn9_2.Format("%02x",gPlmnList.bytePlmn[8][1]);
	m_Plmn9_3.Format("%02x",gPlmnList.bytePlmn[8][2]);
	//PLMN 10
	m_Plmn10_1.Format("%02x",gPlmnList.bytePlmn[9][0]);
	m_Plmn10_2.Format("%02x",gPlmnList.bytePlmn[9][1]);
	m_Plmn10_3.Format("%02x",gPlmnList.bytePlmn[9][2]);
	//PLMN 11
	m_Plmn11_1.Format("%02x",gPlmnList.bytePlmn[10][0]);
	m_Plmn11_2.Format("%02x",gPlmnList.bytePlmn[10][1]);
	m_Plmn11_3.Format("%02x",gPlmnList.bytePlmn[10][2]);
	//PLMN 12
	m_Plmn12_1.Format("%02x",gPlmnList.bytePlmn[11][0]);
	m_Plmn12_2.Format("%02x",gPlmnList.bytePlmn[11][1]);
	m_Plmn12_3.Format("%02x",gPlmnList.bytePlmn[11][2]);
	//PLMN 13
	m_Plmn13_1.Format("%02x",gPlmnList.bytePlmn[12][0]);
	m_Plmn13_2.Format("%02x",gPlmnList.bytePlmn[12][1]);
	m_Plmn13_3.Format("%02x",gPlmnList.bytePlmn[12][2]);
	//PLMN 14
	m_Plmn14_1.Format("%02x",gPlmnList.bytePlmn[13][0]);
	m_Plmn14_2.Format("%02x",gPlmnList.bytePlmn[13][1]);
	m_Plmn14_3.Format("%02x",gPlmnList.bytePlmn[13][2]);
	//PLMN 15
	m_Plmn15_1.Format("%02x",gPlmnList.bytePlmn[14][0]);
	m_Plmn15_2.Format("%02x",gPlmnList.bytePlmn[14][1]);
	m_Plmn15_3.Format("%02x",gPlmnList.bytePlmn[14][2]);
	//PLMN 16
	m_Plmn16_1.Format("%02x",gPlmnList.bytePlmn[15][0]);
	m_Plmn16_2.Format("%02x",gPlmnList.bytePlmn[15][1]);
	m_Plmn16_3.Format("%02x",gPlmnList.bytePlmn[15][2]);
	//PLMN 17
	m_Plmn17_1.Format("%02x",gPlmnList.bytePlmn[16][0]);
	m_Plmn17_2.Format("%02x",gPlmnList.bytePlmn[16][1]);
	m_Plmn17_3.Format("%02x",gPlmnList.bytePlmn[16][2]);
	//PLMN 18
	m_Plmn18_1.Format("%02x",gPlmnList.bytePlmn[17][0]);
	m_Plmn18_2.Format("%02x",gPlmnList.bytePlmn[17][1]);
	m_Plmn18_3.Format("%02x",gPlmnList.bytePlmn[17][2]);
	//PLMN 19
	m_Plmn19_1.Format("%02x",gPlmnList.bytePlmn[18][0]);
	m_Plmn19_2.Format("%02x",gPlmnList.bytePlmn[18][1]);
	m_Plmn19_3.Format("%02x",gPlmnList.bytePlmn[18][2]);
	//PLMN 20
	m_Plmn20_1.Format("%02x",gPlmnList.bytePlmn[19][0]);
	m_Plmn20_2.Format("%02x",gPlmnList.bytePlmn[19][1]);
	m_Plmn20_3.Format("%02x",gPlmnList.bytePlmn[19][2]);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
