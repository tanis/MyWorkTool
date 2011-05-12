// NVPancel.cpp : implementation file
//

#include "stdafx.h"
#include "WriteTool.h"
#include "NVPancel.h"
#include "DllParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNVPancel dialog
#define MAX_NV_DATA_LENGTH (NV_PACK_MAX_DATA_SIZE*500)	//定义最大的NV数据包

//	初始化文件夹设定用的回调函数
int CALLBACK _SHBrowseForFolderCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if(uMsg == BFFM_INITIALIZED)
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	
	return	0;
}

CNVPancel::CNVPancel(CWnd* pParent /*=NULL*/)
	: CDialog(CNVPancel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNVPancel)
	m_ExportPathName = _T("");
	m_ImportPathName = _T("");
	m_BaseAdjust = _T("");
	m_GeneralAdjust = _T("");
	m_CheckBaseAdjust = FALSE;
	m_CheckGeneralAdjust = FALSE;
	//}}AFX_DATA_INIT
}


void CNVPancel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNVPancel)
	DDX_Text(pDX, IDC_EDIT_EXPORT_DIRECTORY, m_ExportPathName);
	DDX_Text(pDX, IDC_EDIT_IMPORT_DIRECTORY, m_ImportPathName);
	DDX_Text(pDX, IDC_EDIT_BASE_ADJUST, m_BaseAdjust);
	DDV_MaxChars(pDX, m_BaseAdjust, 2);
	DDX_Text(pDX, IDC_EDIT_GENERAL_ADJUST, m_GeneralAdjust);
	DDV_MaxChars(pDX, m_GeneralAdjust, 2);
	DDX_Check(pDX, IDC_CHECK_BASE_ADJUST, m_CheckBaseAdjust);
	DDX_Check(pDX, IDC_CHECK_GENERAL_ADJUST, m_CheckGeneralAdjust);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNVPancel, CDialog)
	//{{AFX_MSG_MAP(CNVPancel)
	ON_BN_CLICKED(IDC_SELECT_EXPORT_DIRECTORY, OnSelectExportDirectory)
	ON_BN_CLICKED(IDC_SELECT_IMPORT_DIRECTORY, OnSelectImportDirectory)
	ON_BN_CLICKED(IDC_EXPORT_NV, OnExportNv)
	ON_BN_CLICKED(IDC_IMPORT_NV, OnImportNv)
	ON_BN_CLICKED(IDC_CHECK_BASE_ADJUST, OnCheckBaseAdjust)
	ON_BN_CLICKED(IDC_CHECK_GENERAL_ADJUST, OnCheckGeneralAdjust)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNVPancel message handlers

void CNVPancel::OnSelectExportDirectory() 
{
	// TODO: Add your control notification handler code here
	SelectFolderDlg(&m_ExportPathName);
	UpdateData(FALSE);
}

void CNVPancel::OnSelectImportDirectory() 
{
	// TODO: Add your control notification handler code here
	SelectFolderDlg(&m_ImportPathName);
	UpdateData(FALSE);
}

void CNVPancel::OnExportNv() 
{
	// TODO: Add your control notification handler code here
	byte DataBuf[MAX_NV_DATA_LENGTH]={0};
	UINT ActualBufLength = 0;
	CString FullPathName;
	OTP_IMEI tmpIMEI;
	TCHAR szFilter[] = _T("NV backup Files(*.acn)|*.acn||");
	CFileDialog filedlg(TRUE, _T("NV backup Files"), NULL, 
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						szFilter,this);
	char WorkPath[MAX_PATH+1] = {0};

	ReadWriteComReq();
	RefreshMainDlgMsgBox("Export NV From UE:");

	if(m_ExportPathName.IsEmpty())
	{
		AddInfotoMainDlgMsgBox("\r\n  The directory of export path is NULL,please select it first!");
		CloseComPort();
		return;
	}
	//Select a file
	if(ReadIMEI(&tmpIMEI) == TRUE)
	{
		FullPathName.Format("%s\\%s.acn",m_ExportPathName.GetBuffer(0),tmpIMEI.szIMEI);
	}
	else
	{
		BOOL bStatus = FALSE;
		//保存当前的工作路径
		GetCurrentDirectory(MAX_PATH,WorkPath);
		if(filedlg.DoModal() == IDOK)
		{
			FullPathName = filedlg.GetPathName();
			bStatus = TRUE;
		}
		//还原当前的工作路径
		SetCurrentDirectory(WorkPath);
		if(bStatus == FALSE)
		{
			AddInfotoMainDlgMsgBox("\r\n  The operation is cancelled!");
			CloseComPort();
			return;
		}
	}

	if(ExportAllNVsFromPhone(DataBuf,&ActualBufLength) == TRUE)
	{
		CFile file;
		CFileException fError;

		file.Open(FullPathName.GetBuffer(0),CFile::modeWrite|CFile::modeCreate,&fError);
		if(fError.m_cause != CFileException::none)	//file error
		{
			HLOCAL hlocal = NULL;
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,NULL,fError.m_lOsError,0,(LPTSTR)&hlocal,0,NULL);
			CString errorout = (LPTSTR)LocalLock(hlocal);
			AfxMessageBox(errorout,MB_OK|MB_ICONERROR);
			AddInfotoMainDlgMsgBox("\r\n  Cannot write the file!");
		}
		else
		{
			AddInfotoMainDlgMsgBox("Success!");
			AddInfotoMainDlgMsgBox("\r\n  Save the NV to the file:");
			AddInfotoMainDlgMsgBox(FullPathName.GetBuffer(0));
			file.Write(DataBuf,ActualBufLength);
			file.Close();
		}
	}
	CloseComPort();
}

void CNVPancel::OnImportNv() 
{
	// TODO: Add your control notification handler code here
	byte DataBuf[MAX_NV_DATA_LENGTH]={0};
	UINT ActualBufLength = 0;
	CString FullPathName;
	CFile file;
	CFileException fError;
	OTP_IMEI tmpIMEI;
	BOOL bIsExist = FALSE;

	ReadWriteComReq();
	RefreshMainDlgMsgBox("Import NV to UE:");

	if(m_ImportPathName.IsEmpty())
	{
		AddInfotoMainDlgMsgBox("\r\n  The directory of import path is NULL,please select it!");
		CloseComPort();
		return;
	}
	if(ReadIMEI(&tmpIMEI) == TRUE)
	{
		CFileStatus rStatus;

		FullPathName.Format("%s\\%s.acn",m_ImportPathName.GetBuffer(0),tmpIMEI.szIMEI);
		//check if the file is exist
		bIsExist = file.GetStatus(FullPathName.GetBuffer(0),rStatus);
	}
	if(bIsExist == FALSE)
	{
		BOOL bStatus = FALSE;
		TCHAR szFilter[] = _T("NV backup Files(*.acn)|*.acn||");
		CFileDialog filedlg(TRUE, _T("NV backup Files"), NULL, 
							OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
							szFilter,this);
		char WorkPath[MAX_PATH+1] = {0};

		FullPathName = "";
		//保存当前的工作路径
		GetCurrentDirectory(MAX_PATH,WorkPath);
		if(filedlg.DoModal() == IDOK)
		{
			FullPathName = filedlg.GetPathName();
			bStatus = TRUE;
		}
		//还原当前的工作路径
		SetCurrentDirectory(WorkPath);
		if(bStatus == FALSE)
		{
			AddInfotoMainDlgMsgBox("\r\n  The operation is cancelled!");
			CloseComPort();
			return;
		}
	}

	AddInfotoMainDlgMsgBox("\r\n  Read the NV from the file:");
	AddInfotoMainDlgMsgBox(FullPathName.GetBuffer(0));

	file.Open(FullPathName.GetBuffer(0),CFile::modeRead,&fError);
	if(fError.m_cause != CFileException::none)	//file error
	{
		HLOCAL hlocal = NULL;
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,NULL,fError.m_lOsError,0,(LPTSTR)&hlocal,0,NULL);
		CString errorout = (LPTSTR)LocalLock(hlocal);
		AfxMessageBox(errorout,MB_OK|MB_ICONERROR);
	}
	else
	{
		ActualBufLength = file.Read(DataBuf,MAX_NV_DATA_LENGTH);
		if(ImportAllNVsIntoPhone(DataBuf, ActualBufLength) == TRUE)
		{
			AddInfotoMainDlgMsgBox("\r\n  Import NV to the UE success!");
		}
	}
	CloseComPort();
}

void CNVPancel::OnCheckBaseAdjust() 
{
	// TODO: Add your control notification handler code here
	m_CheckBaseAdjust = !m_CheckBaseAdjust;
	gbCheckBaseAdjust = m_CheckBaseAdjust;
}

void CNVPancel::OnCheckGeneralAdjust() 
{
	// TODO: Add your control notification handler code here
	m_CheckGeneralAdjust = !m_CheckGeneralAdjust;
	gbCheckGeneralAdjust = m_CheckGeneralAdjust;
}

void CNVPancel::RefreshPancel()
{
	m_BaseAdjust.Format("%02x",gBaseAdjust);
	m_GeneralAdjust.Format("%02x",gGeneralAdjust);
	UpdateData(FALSE);
}

BOOL CNVPancel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	RefreshPancel();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CNVPancel::SelectFolderDlg(CString* lpstrFolder)
{
	BOOL			ret;
	TCHAR			lpszPath[MAX_PATH];
	LPMALLOC		lpMalloc;
	BROWSEINFO		sInfo;
	LPITEMIDLIST	lpidlRoot;
	LPITEMIDLIST	lpidlBrowse;
	char FullName[MAX_PATH+1] = {0};
	
	if(lpstrFolder == NULL)
		return	FALSE;
	
	if(::SHGetMalloc(&lpMalloc) != NOERROR)
		return	false;

	ret = FALSE;

	GetCurrentDirectory(MAX_PATH,FullName);

	::SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &lpidlRoot);	//取得选定的文件夹名
	
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot		= lpidlRoot;
	sInfo.pszDisplayName= lpszPath;
	sInfo.lpszTitle		= "Select Directory";
	sInfo.ulFlags		= BIF_RETURNONLYFSDIRS;
	sInfo.ulFlags		|= BIF_EDITBOX ;
	sInfo.lpfn			= _SHBrowseForFolderCallbackProc;
	sInfo.lParam		= (LPARAM)FullName;
	
	lpidlBrowse = ::SHBrowseForFolder(&sInfo);			//显示文件夹选择对话框
	
	if(lpidlBrowse != NULL)
	{
		if(::SHGetPathFromIDList(lpidlBrowse,lpszPath))	//取得文件夹名		
		{
			*lpstrFolder = "";
			*lpstrFolder = lpszPath;

			if(*lpstrFolder != "")
			{
				if(lpstrFolder->Right(1) != "\\")
					*lpstrFolder += "\\";				//在末尾时附加"\\"
			}
		}

		ret = TRUE;
	}
	
	if(lpidlBrowse != NULL)
		::CoTaskMemFree(lpidlBrowse);
	if(lpidlRoot != NULL)
		::CoTaskMemFree(lpidlRoot);
	
	lpMalloc->Release();
	return	ret;
}

BOOL CNVPancel::ReadIMEI(OTP_IMEI* pIMEI)
{
	return Read_OTP_IMEI(gComPortInfo.ComID,pIMEI);
}

BOOL CNVPancel::ExportAllNVsFromPhone(byte *pDataBuf, UINT *pActualBufLength)
{
	UINT ValidDataSize = 0;

	//Export data
	if(ExportAllNVItemsFromPhone(gComPortInfo.ComID,pDataBuf,pActualBufLength) != 0)
	{
		AddInfotoMainDlgMsgBox("\r\n  Export the data from UE failed!");
		return FALSE;
	}
	//Check Length
	memcpy(&ValidDataSize, pDataBuf, 4);
	if(ValidDataSize+NV_PACK_MAX_DATA_SIZE != *pActualBufLength)
	{
		AddInfotoMainDlgMsgBox("\r\n  The length of data is mismatch!");
		return FALSE;
	}
	//Check Hash of Data
	if(CheckHashValue(&pDataBuf[4],
					GOZONE_DCKHASH_LEN,
					&pDataBuf[NV_PACK_MAX_DATA_SIZE],
					*pActualBufLength-NV_PACK_MAX_DATA_SIZE) == FALSE)
	{
		AddInfotoMainDlgMsgBox("\r\n  The Hash of data is mismatch!");
		return FALSE;
	}

	return TRUE;
}

BOOL CNVPancel::ImportAllNVsIntoPhone(byte *pDataBuf, UINT ActualBufLength)
{
	UINT ValidDataSize = 0;

	//Check Length
	memcpy(&ValidDataSize, pDataBuf, 4);
	if(ValidDataSize+NV_PACK_MAX_DATA_SIZE != ActualBufLength)
	{
		AddInfotoMainDlgMsgBox("\r\n  The length of data is mismatch!");
		return FALSE;
	}
	//Check Hash of Data
	if(CheckHashValue(&pDataBuf[4],
					GOZONE_DCKHASH_LEN,
					&pDataBuf[NV_PACK_MAX_DATA_SIZE],
					ActualBufLength-NV_PACK_MAX_DATA_SIZE) == FALSE)
	{
		AddInfotoMainDlgMsgBox("\r\n  The Hash of data is mismatch!");
		return FALSE;
	}
	//Import Data
	if(ImportAllNVItemsIntoPhone(gComPortInfo.ComID,pDataBuf,ActualBufLength) != 0)
	{
		AddInfotoMainDlgMsgBox("\r\n  Import the data to the UE failed!");
		return FALSE;
	}

	return TRUE;
}

void CNVPancel::OnCancel()
{
	MinimizeMainDialog();
}

void CNVPancel::OnOK()
{
}