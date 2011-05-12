// ViewPublicKey.cpp : implementation file
//

#include "stdafx.h"
#include "WriteTool.h"
#include "ViewPublicKey.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewPublicKey dialog


CViewPublicKey::CViewPublicKey(CWnd* pParent /*=NULL*/)
	: CDialog(CViewPublicKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewPublicKey)
	m_PublicKey1 = _T("");
	m_PublicKey2 = _T("");
	m_PublicKey3 = _T("");
	m_PublicKey4 = _T("");
	m_PublicKey5 = _T("");
	m_PublicKey6 = _T("");
	m_PublicKey7 = _T("");
	m_PublicKey8 = _T("");
	m_PublicKey9 = _T("");
	m_PublicKey10 = _T("");
	m_PublicKey11 = _T("");
	m_PublicKey12 = _T("");
	m_PublicKey13 = _T("");
	m_PublicKey14 = _T("");
	m_PublicKey15 = _T("");
	m_PublicKey16 = _T("");
	m_PublicKey17 = _T("");
	m_PublicKey18 = _T("");
	m_PublicKey19 = _T("");
	m_PublicKey20 = _T("");
	m_PublicKey21 = _T("");
	m_PublicKey22 = _T("");
	m_PublicKey23 = _T("");
	m_PublicKey24 = _T("");
	m_PublicKey25 = _T("");
	m_PublicKey26 = _T("");
	m_PublicKey27 = _T("");
	m_PublicKey28 = _T("");
	m_PublicKey29 = _T("");
	m_PublicKey30 = _T("");
	m_PublicKey31 = _T("");
	m_PublicKey32 = _T("");
	m_PublicKey33 = _T("");
	m_PublicKey34 = _T("");
	m_PublicKey35 = _T("");
	m_PublicKey36 = _T("");
	m_PublicKey37 = _T("");
	m_PublicKey38 = _T("");
	m_PublicKey39 = _T("");
	m_PublicKey40 = _T("");
	m_PublicKey41 = _T("");
	m_PublicKey42 = _T("");
	m_PublicKey43 = _T("");
	m_PublicKey44 = _T("");
	m_PublicKey45 = _T("");
	m_PublicKey46 = _T("");
	m_PublicKey47 = _T("");
	m_PublicKey48 = _T("");
	m_PublicKey49 = _T("");
	m_PublicKey50 = _T("");
	m_PublicKey51 = _T("");
	m_PublicKey52 = _T("");
	m_PublicKey53 = _T("");
	m_PublicKey54 = _T("");
	m_PublicKey55 = _T("");
	m_PublicKey56 = _T("");
	m_PublicKey57 = _T("");
	m_PublicKey58 = _T("");
	m_PublicKey59 = _T("");
	m_PublicKey60 = _T("");
	m_PublicKey61 = _T("");
	m_PublicKey62 = _T("");
	m_PublicKey63 = _T("");
	m_PublicKey64 = _T("");
	m_PublicKey65 = _T("");
	m_PublicKey66 = _T("");
	m_PublicKey67 = _T("");
	m_PublicKey68 = _T("");
	m_PublicKey69 = _T("");
	m_PublicKey70 = _T("");
	m_PublicKey71 = _T("");
	m_PublicKey72 = _T("");
	m_PublicKey73 = _T("");
	m_PublicKey74 = _T("");
	m_PublicKey75 = _T("");
	m_PublicKey76 = _T("");
	m_PublicKey77 = _T("");
	m_PublicKey78 = _T("");
	m_PublicKey79 = _T("");
	m_PublicKey80 = _T("");
	//}}AFX_DATA_INIT
}


void CViewPublicKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewPublicKey)
	DDX_Text(pDX, IDC_PUBLIC_KEY_1, m_PublicKey1);
	DDV_MaxChars(pDX, m_PublicKey1, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_2, m_PublicKey2);
	DDV_MaxChars(pDX, m_PublicKey2, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_3, m_PublicKey3);
	DDV_MaxChars(pDX, m_PublicKey3, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_4, m_PublicKey4);
	DDV_MaxChars(pDX, m_PublicKey4, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_5, m_PublicKey5);
	DDV_MaxChars(pDX, m_PublicKey5, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_6, m_PublicKey6);
	DDV_MaxChars(pDX, m_PublicKey6, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_7, m_PublicKey7);
	DDV_MaxChars(pDX, m_PublicKey7, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_8, m_PublicKey8);
	DDV_MaxChars(pDX, m_PublicKey8, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_9, m_PublicKey9);
	DDV_MaxChars(pDX, m_PublicKey9, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_10, m_PublicKey10);
	DDV_MaxChars(pDX, m_PublicKey10, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_11, m_PublicKey11);
	DDV_MaxChars(pDX, m_PublicKey11, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_12, m_PublicKey12);
	DDV_MaxChars(pDX, m_PublicKey12, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_13, m_PublicKey13);
	DDV_MaxChars(pDX, m_PublicKey13, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_14, m_PublicKey14);
	DDV_MaxChars(pDX, m_PublicKey14, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_15, m_PublicKey15);
	DDV_MaxChars(pDX, m_PublicKey15, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_16, m_PublicKey16);
	DDV_MaxChars(pDX, m_PublicKey16, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_17, m_PublicKey17);
	DDV_MaxChars(pDX, m_PublicKey17, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_18, m_PublicKey18);
	DDV_MaxChars(pDX, m_PublicKey18, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_19, m_PublicKey19);
	DDV_MaxChars(pDX, m_PublicKey19, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_20, m_PublicKey20);
	DDV_MaxChars(pDX, m_PublicKey20, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_21, m_PublicKey21);
	DDV_MaxChars(pDX, m_PublicKey21, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_22, m_PublicKey22);
	DDV_MaxChars(pDX, m_PublicKey22, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_23, m_PublicKey23);
	DDV_MaxChars(pDX, m_PublicKey23, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_24, m_PublicKey24);
	DDV_MaxChars(pDX, m_PublicKey24, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_25, m_PublicKey25);
	DDV_MaxChars(pDX, m_PublicKey25, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_26, m_PublicKey26);
	DDV_MaxChars(pDX, m_PublicKey26, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_27, m_PublicKey27);
	DDV_MaxChars(pDX, m_PublicKey27, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_28, m_PublicKey28);
	DDV_MaxChars(pDX, m_PublicKey28, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_29, m_PublicKey29);
	DDV_MaxChars(pDX, m_PublicKey29, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_30, m_PublicKey30);
	DDV_MaxChars(pDX, m_PublicKey30, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_31, m_PublicKey31);
	DDV_MaxChars(pDX, m_PublicKey31, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_32, m_PublicKey32);
	DDV_MaxChars(pDX, m_PublicKey32, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_33, m_PublicKey33);
	DDV_MaxChars(pDX, m_PublicKey33, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_34, m_PublicKey34);
	DDV_MaxChars(pDX, m_PublicKey34, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_35, m_PublicKey35);
	DDV_MaxChars(pDX, m_PublicKey35, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_36, m_PublicKey36);
	DDV_MaxChars(pDX, m_PublicKey36, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_37, m_PublicKey37);
	DDV_MaxChars(pDX, m_PublicKey37, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_38, m_PublicKey38);
	DDV_MaxChars(pDX, m_PublicKey38, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_39, m_PublicKey39);
	DDV_MaxChars(pDX, m_PublicKey39, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_40, m_PublicKey40);
	DDV_MaxChars(pDX, m_PublicKey40, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_41, m_PublicKey41);
	DDV_MaxChars(pDX, m_PublicKey41, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_42, m_PublicKey42);
	DDV_MaxChars(pDX, m_PublicKey42, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_43, m_PublicKey43);
	DDV_MaxChars(pDX, m_PublicKey43, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_44, m_PublicKey44);
	DDV_MaxChars(pDX, m_PublicKey44, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_45, m_PublicKey45);
	DDV_MaxChars(pDX, m_PublicKey45, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_46, m_PublicKey46);
	DDV_MaxChars(pDX, m_PublicKey46, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_47, m_PublicKey47);
	DDV_MaxChars(pDX, m_PublicKey47, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_48, m_PublicKey48);
	DDV_MaxChars(pDX, m_PublicKey48, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_49, m_PublicKey49);
	DDV_MaxChars(pDX, m_PublicKey49, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_50, m_PublicKey50);
	DDV_MaxChars(pDX, m_PublicKey50, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_51, m_PublicKey51);
	DDV_MaxChars(pDX, m_PublicKey51, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_52, m_PublicKey52);
	DDV_MaxChars(pDX, m_PublicKey52, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_53, m_PublicKey53);
	DDV_MaxChars(pDX, m_PublicKey53, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_54, m_PublicKey54);
	DDV_MaxChars(pDX, m_PublicKey54, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_55, m_PublicKey55);
	DDV_MaxChars(pDX, m_PublicKey55, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_56, m_PublicKey56);
	DDV_MaxChars(pDX, m_PublicKey56, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_57, m_PublicKey57);
	DDV_MaxChars(pDX, m_PublicKey57, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_58, m_PublicKey58);
	DDV_MaxChars(pDX, m_PublicKey58, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_59, m_PublicKey59);
	DDV_MaxChars(pDX, m_PublicKey59, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_60, m_PublicKey60);
	DDV_MaxChars(pDX, m_PublicKey60, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_61, m_PublicKey61);
	DDV_MaxChars(pDX, m_PublicKey61, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_62, m_PublicKey62);
	DDV_MaxChars(pDX, m_PublicKey62, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_63, m_PublicKey63);
	DDV_MaxChars(pDX, m_PublicKey63, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_64, m_PublicKey64);
	DDV_MaxChars(pDX, m_PublicKey64, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_65, m_PublicKey65);
	DDV_MaxChars(pDX, m_PublicKey65, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_66, m_PublicKey66);
	DDV_MaxChars(pDX, m_PublicKey66, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_67, m_PublicKey67);
	DDV_MaxChars(pDX, m_PublicKey67, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_68, m_PublicKey68);
	DDV_MaxChars(pDX, m_PublicKey68, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_69, m_PublicKey69);
	DDV_MaxChars(pDX, m_PublicKey69, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_70, m_PublicKey70);
	DDV_MaxChars(pDX, m_PublicKey70, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_71, m_PublicKey71);
	DDV_MaxChars(pDX, m_PublicKey71, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_72, m_PublicKey72);
	DDV_MaxChars(pDX, m_PublicKey72, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_73, m_PublicKey73);
	DDV_MaxChars(pDX, m_PublicKey73, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_74, m_PublicKey74);
	DDV_MaxChars(pDX, m_PublicKey74, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_75, m_PublicKey75);
	DDV_MaxChars(pDX, m_PublicKey75, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_76, m_PublicKey76);
	DDV_MaxChars(pDX, m_PublicKey76, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_77, m_PublicKey77);
	DDV_MaxChars(pDX, m_PublicKey77, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_78, m_PublicKey78);
	DDV_MaxChars(pDX, m_PublicKey78, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_79, m_PublicKey79);
	DDV_MaxChars(pDX, m_PublicKey79, 2);
	DDX_Text(pDX, IDC_PUBLIC_KEY_80, m_PublicKey80);
	DDV_MaxChars(pDX, m_PublicKey80, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewPublicKey, CDialog)
	//{{AFX_MSG_MAP(CViewPublicKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewPublicKey message handlers

void CViewPublicKey::OnOK() 
{
	// TODO: Add extra validation here
	OTP_PublicKey tmpPublicKey={0};

	UpdateData(TRUE);

	ChangeDataFromHexString(m_PublicKey1,&tmpPublicKey.bytePublicKey[0]);
	ChangeDataFromHexString(m_PublicKey2,&tmpPublicKey.bytePublicKey[1]);
	ChangeDataFromHexString(m_PublicKey3,&tmpPublicKey.bytePublicKey[2]);
	ChangeDataFromHexString(m_PublicKey4,&tmpPublicKey.bytePublicKey[3]);
	ChangeDataFromHexString(m_PublicKey5,&tmpPublicKey.bytePublicKey[4]);
	ChangeDataFromHexString(m_PublicKey6,&tmpPublicKey.bytePublicKey[5]);
	ChangeDataFromHexString(m_PublicKey7,&tmpPublicKey.bytePublicKey[6]);
	ChangeDataFromHexString(m_PublicKey8,&tmpPublicKey.bytePublicKey[7]);
	ChangeDataFromHexString(m_PublicKey9,&tmpPublicKey.bytePublicKey[8]);
	ChangeDataFromHexString(m_PublicKey10,&tmpPublicKey.bytePublicKey[9]);
	ChangeDataFromHexString(m_PublicKey11,&tmpPublicKey.bytePublicKey[10]);
	ChangeDataFromHexString(m_PublicKey12,&tmpPublicKey.bytePublicKey[11]);
	ChangeDataFromHexString(m_PublicKey13,&tmpPublicKey.bytePublicKey[12]);
	ChangeDataFromHexString(m_PublicKey14,&tmpPublicKey.bytePublicKey[13]);
	ChangeDataFromHexString(m_PublicKey15,&tmpPublicKey.bytePublicKey[14]);
	ChangeDataFromHexString(m_PublicKey16,&tmpPublicKey.bytePublicKey[15]);
	ChangeDataFromHexString(m_PublicKey17,&tmpPublicKey.bytePublicKey[16]);
	ChangeDataFromHexString(m_PublicKey18,&tmpPublicKey.bytePublicKey[17]);
	ChangeDataFromHexString(m_PublicKey19,&tmpPublicKey.bytePublicKey[18]);
	ChangeDataFromHexString(m_PublicKey20,&tmpPublicKey.bytePublicKey[19]);
	ChangeDataFromHexString(m_PublicKey21,&tmpPublicKey.bytePublicKey[20]);
	ChangeDataFromHexString(m_PublicKey22,&tmpPublicKey.bytePublicKey[21]);
	ChangeDataFromHexString(m_PublicKey23,&tmpPublicKey.bytePublicKey[22]);
	ChangeDataFromHexString(m_PublicKey24,&tmpPublicKey.bytePublicKey[23]);
	ChangeDataFromHexString(m_PublicKey25,&tmpPublicKey.bytePublicKey[24]);
	ChangeDataFromHexString(m_PublicKey26,&tmpPublicKey.bytePublicKey[25]);
	ChangeDataFromHexString(m_PublicKey27,&tmpPublicKey.bytePublicKey[26]);
	ChangeDataFromHexString(m_PublicKey28,&tmpPublicKey.bytePublicKey[27]);
	ChangeDataFromHexString(m_PublicKey29,&tmpPublicKey.bytePublicKey[28]);
	ChangeDataFromHexString(m_PublicKey30,&tmpPublicKey.bytePublicKey[29]);
	ChangeDataFromHexString(m_PublicKey31,&tmpPublicKey.bytePublicKey[30]);
	ChangeDataFromHexString(m_PublicKey32,&tmpPublicKey.bytePublicKey[31]);
	ChangeDataFromHexString(m_PublicKey33,&tmpPublicKey.bytePublicKey[32]);
	ChangeDataFromHexString(m_PublicKey34,&tmpPublicKey.bytePublicKey[33]);
	ChangeDataFromHexString(m_PublicKey35,&tmpPublicKey.bytePublicKey[34]);
	ChangeDataFromHexString(m_PublicKey36,&tmpPublicKey.bytePublicKey[35]);
	ChangeDataFromHexString(m_PublicKey37,&tmpPublicKey.bytePublicKey[36]);
	ChangeDataFromHexString(m_PublicKey38,&tmpPublicKey.bytePublicKey[37]);
	ChangeDataFromHexString(m_PublicKey39,&tmpPublicKey.bytePublicKey[38]);
	ChangeDataFromHexString(m_PublicKey40,&tmpPublicKey.bytePublicKey[39]);
	ChangeDataFromHexString(m_PublicKey41,&tmpPublicKey.bytePublicKey[40]);
	ChangeDataFromHexString(m_PublicKey42,&tmpPublicKey.bytePublicKey[41]);
	ChangeDataFromHexString(m_PublicKey43,&tmpPublicKey.bytePublicKey[42]);
	ChangeDataFromHexString(m_PublicKey44,&tmpPublicKey.bytePublicKey[43]);
	ChangeDataFromHexString(m_PublicKey45,&tmpPublicKey.bytePublicKey[44]);
	ChangeDataFromHexString(m_PublicKey46,&tmpPublicKey.bytePublicKey[45]);
	ChangeDataFromHexString(m_PublicKey47,&tmpPublicKey.bytePublicKey[46]);
	ChangeDataFromHexString(m_PublicKey48,&tmpPublicKey.bytePublicKey[47]);
	ChangeDataFromHexString(m_PublicKey49,&tmpPublicKey.bytePublicKey[48]);
	ChangeDataFromHexString(m_PublicKey50,&tmpPublicKey.bytePublicKey[49]);
	ChangeDataFromHexString(m_PublicKey51,&tmpPublicKey.bytePublicKey[50]);
	ChangeDataFromHexString(m_PublicKey52,&tmpPublicKey.bytePublicKey[51]);
	ChangeDataFromHexString(m_PublicKey53,&tmpPublicKey.bytePublicKey[52]);
	ChangeDataFromHexString(m_PublicKey54,&tmpPublicKey.bytePublicKey[53]);
	ChangeDataFromHexString(m_PublicKey55,&tmpPublicKey.bytePublicKey[54]);
	ChangeDataFromHexString(m_PublicKey56,&tmpPublicKey.bytePublicKey[55]);
	ChangeDataFromHexString(m_PublicKey57,&tmpPublicKey.bytePublicKey[56]);
	ChangeDataFromHexString(m_PublicKey58,&tmpPublicKey.bytePublicKey[57]);
	ChangeDataFromHexString(m_PublicKey59,&tmpPublicKey.bytePublicKey[58]);
	ChangeDataFromHexString(m_PublicKey60,&tmpPublicKey.bytePublicKey[59]);
	ChangeDataFromHexString(m_PublicKey61,&tmpPublicKey.bytePublicKey[60]);
	ChangeDataFromHexString(m_PublicKey62,&tmpPublicKey.bytePublicKey[61]);
	ChangeDataFromHexString(m_PublicKey63,&tmpPublicKey.bytePublicKey[62]);
	ChangeDataFromHexString(m_PublicKey64,&tmpPublicKey.bytePublicKey[63]);
	ChangeDataFromHexString(m_PublicKey65,&tmpPublicKey.bytePublicKey[64]);
	ChangeDataFromHexString(m_PublicKey66,&tmpPublicKey.bytePublicKey[65]);
	ChangeDataFromHexString(m_PublicKey67,&tmpPublicKey.bytePublicKey[66]);
	ChangeDataFromHexString(m_PublicKey68,&tmpPublicKey.bytePublicKey[67]);
	ChangeDataFromHexString(m_PublicKey69,&tmpPublicKey.bytePublicKey[68]);
	ChangeDataFromHexString(m_PublicKey70,&tmpPublicKey.bytePublicKey[69]);
	ChangeDataFromHexString(m_PublicKey71,&tmpPublicKey.bytePublicKey[70]);
	ChangeDataFromHexString(m_PublicKey72,&tmpPublicKey.bytePublicKey[71]);
	ChangeDataFromHexString(m_PublicKey73,&tmpPublicKey.bytePublicKey[72]);
	ChangeDataFromHexString(m_PublicKey74,&tmpPublicKey.bytePublicKey[73]);
	ChangeDataFromHexString(m_PublicKey75,&tmpPublicKey.bytePublicKey[74]);
	ChangeDataFromHexString(m_PublicKey76,&tmpPublicKey.bytePublicKey[75]);
	ChangeDataFromHexString(m_PublicKey77,&tmpPublicKey.bytePublicKey[76]);
	ChangeDataFromHexString(m_PublicKey78,&tmpPublicKey.bytePublicKey[77]);
	ChangeDataFromHexString(m_PublicKey79,&tmpPublicKey.bytePublicKey[78]);
	ChangeDataFromHexString(m_PublicKey80,&tmpPublicKey.bytePublicKey[79]);

	memcpy(gPublicKey.bytePublicKey,tmpPublicKey.bytePublicKey,sizeof(gPublicKey.bytePublicKey));
	CDialog::OnOK();
}

void CViewPublicKey::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CViewPublicKey::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_PublicKey1.Format("%02x",gPublicKey.bytePublicKey[0]);
	m_PublicKey2.Format("%02x",gPublicKey.bytePublicKey[1]);
	m_PublicKey3.Format("%02x",gPublicKey.bytePublicKey[2]);
	m_PublicKey4.Format("%02x",gPublicKey.bytePublicKey[3]);
	m_PublicKey5.Format("%02x",gPublicKey.bytePublicKey[4]);
	m_PublicKey6.Format("%02x",gPublicKey.bytePublicKey[5]);
	m_PublicKey7.Format("%02x",gPublicKey.bytePublicKey[6]);
	m_PublicKey8.Format("%02x",gPublicKey.bytePublicKey[7]);
	m_PublicKey9.Format("%02x",gPublicKey.bytePublicKey[8]);
	m_PublicKey10.Format("%02x",gPublicKey.bytePublicKey[9]);
	m_PublicKey11.Format("%02x",gPublicKey.bytePublicKey[10]);
	m_PublicKey12.Format("%02x",gPublicKey.bytePublicKey[11]);
	m_PublicKey13.Format("%02x",gPublicKey.bytePublicKey[12]);
	m_PublicKey14.Format("%02x",gPublicKey.bytePublicKey[13]);
	m_PublicKey15.Format("%02x",gPublicKey.bytePublicKey[14]);
	m_PublicKey16.Format("%02x",gPublicKey.bytePublicKey[15]);
	m_PublicKey17.Format("%02x",gPublicKey.bytePublicKey[16]);
	m_PublicKey18.Format("%02x",gPublicKey.bytePublicKey[17]);
	m_PublicKey19.Format("%02x",gPublicKey.bytePublicKey[18]);
	m_PublicKey20.Format("%02x",gPublicKey.bytePublicKey[19]);
	m_PublicKey21.Format("%02x",gPublicKey.bytePublicKey[20]);
	m_PublicKey22.Format("%02x",gPublicKey.bytePublicKey[21]);
	m_PublicKey23.Format("%02x",gPublicKey.bytePublicKey[22]);
	m_PublicKey24.Format("%02x",gPublicKey.bytePublicKey[23]);
	m_PublicKey25.Format("%02x",gPublicKey.bytePublicKey[24]);
	m_PublicKey26.Format("%02x",gPublicKey.bytePublicKey[25]);
	m_PublicKey27.Format("%02x",gPublicKey.bytePublicKey[26]);
	m_PublicKey28.Format("%02x",gPublicKey.bytePublicKey[27]);
	m_PublicKey29.Format("%02x",gPublicKey.bytePublicKey[28]);
	m_PublicKey30.Format("%02x",gPublicKey.bytePublicKey[29]);
	m_PublicKey31.Format("%02x",gPublicKey.bytePublicKey[30]);
	m_PublicKey32.Format("%02x",gPublicKey.bytePublicKey[31]);
	m_PublicKey33.Format("%02x",gPublicKey.bytePublicKey[32]);
	m_PublicKey34.Format("%02x",gPublicKey.bytePublicKey[33]);
	m_PublicKey35.Format("%02x",gPublicKey.bytePublicKey[34]);
	m_PublicKey36.Format("%02x",gPublicKey.bytePublicKey[35]);
	m_PublicKey37.Format("%02x",gPublicKey.bytePublicKey[36]);
	m_PublicKey38.Format("%02x",gPublicKey.bytePublicKey[37]);
	m_PublicKey39.Format("%02x",gPublicKey.bytePublicKey[38]);
	m_PublicKey40.Format("%02x",gPublicKey.bytePublicKey[39]);
	m_PublicKey41.Format("%02x",gPublicKey.bytePublicKey[40]);
	m_PublicKey42.Format("%02x",gPublicKey.bytePublicKey[41]);
	m_PublicKey43.Format("%02x",gPublicKey.bytePublicKey[42]);
	m_PublicKey44.Format("%02x",gPublicKey.bytePublicKey[43]);
	m_PublicKey45.Format("%02x",gPublicKey.bytePublicKey[44]);
	m_PublicKey46.Format("%02x",gPublicKey.bytePublicKey[45]);
	m_PublicKey47.Format("%02x",gPublicKey.bytePublicKey[46]);
	m_PublicKey48.Format("%02x",gPublicKey.bytePublicKey[47]);
	m_PublicKey49.Format("%02x",gPublicKey.bytePublicKey[48]);
	m_PublicKey50.Format("%02x",gPublicKey.bytePublicKey[49]);
	m_PublicKey51.Format("%02x",gPublicKey.bytePublicKey[50]);
	m_PublicKey52.Format("%02x",gPublicKey.bytePublicKey[51]);
	m_PublicKey53.Format("%02x",gPublicKey.bytePublicKey[52]);
	m_PublicKey54.Format("%02x",gPublicKey.bytePublicKey[53]);
	m_PublicKey55.Format("%02x",gPublicKey.bytePublicKey[54]);
	m_PublicKey56.Format("%02x",gPublicKey.bytePublicKey[55]);
	m_PublicKey57.Format("%02x",gPublicKey.bytePublicKey[56]);
	m_PublicKey58.Format("%02x",gPublicKey.bytePublicKey[57]);
	m_PublicKey59.Format("%02x",gPublicKey.bytePublicKey[58]);
	m_PublicKey60.Format("%02x",gPublicKey.bytePublicKey[59]);
	m_PublicKey61.Format("%02x",gPublicKey.bytePublicKey[60]);
	m_PublicKey62.Format("%02x",gPublicKey.bytePublicKey[61]);
	m_PublicKey63.Format("%02x",gPublicKey.bytePublicKey[62]);
	m_PublicKey64.Format("%02x",gPublicKey.bytePublicKey[63]);
	m_PublicKey65.Format("%02x",gPublicKey.bytePublicKey[64]);
	m_PublicKey66.Format("%02x",gPublicKey.bytePublicKey[65]);
	m_PublicKey67.Format("%02x",gPublicKey.bytePublicKey[66]);
	m_PublicKey68.Format("%02x",gPublicKey.bytePublicKey[67]);
	m_PublicKey69.Format("%02x",gPublicKey.bytePublicKey[68]);
	m_PublicKey70.Format("%02x",gPublicKey.bytePublicKey[69]);
	m_PublicKey71.Format("%02x",gPublicKey.bytePublicKey[70]);
	m_PublicKey72.Format("%02x",gPublicKey.bytePublicKey[71]);
	m_PublicKey73.Format("%02x",gPublicKey.bytePublicKey[72]);
	m_PublicKey74.Format("%02x",gPublicKey.bytePublicKey[73]);
	m_PublicKey75.Format("%02x",gPublicKey.bytePublicKey[74]);
	m_PublicKey76.Format("%02x",gPublicKey.bytePublicKey[75]);
	m_PublicKey77.Format("%02x",gPublicKey.bytePublicKey[76]);
	m_PublicKey78.Format("%02x",gPublicKey.bytePublicKey[77]);
	m_PublicKey79.Format("%02x",gPublicKey.bytePublicKey[78]);
	m_PublicKey80.Format("%02x",gPublicKey.bytePublicKey[79]);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
