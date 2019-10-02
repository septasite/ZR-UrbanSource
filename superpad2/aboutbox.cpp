// aboutbox.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.



#include "stdafx.h"
#include "resource.h"
#include "aboutbox.h"
#include <dos.h>
#include <direct.h>
#include "../EngineLib/Common/StringFile.h"
#include "../enginelib/Common/Rijndael.h"
//#include "paddoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutBox dialog

BEGIN_MESSAGE_MAP(CAboutBox, CDialog)
	//{{AFX_MSG_MAP(CAboutBox)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutBox::OnBnClickedButton_SOURCE)
	ON_BN_CLICKED(IDC_BUTTON2, &CAboutBox::OnBnClickedButton_DEST)
	ON_BN_CLICKED(IDOK, &CAboutBox::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, &CAboutBox::OnBnClickedButtonDecrypt)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT, &CAboutBox::OnBnClickedButtonEncrypt)
END_MESSAGE_MAP()

CAboutBox::CAboutBox(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutBox::IDD, pParent)
	, TXTSOURCE(0)
	, TXTDESTINATION(0)
{
	//{{AFX_DATA_INIT(CAboutBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CAboutBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutBox)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAboutBox message handlers

BOOL CAboutBox::OnInitDialog()
{
	CDialog::OnInitDialog();

	// initialize the big icon control
	m_icon.SubclassDlgItem(IDC_BIGICON, this);
	m_icon.SizeToContent();

	// fill available memory
	CString str, strFmt;
	strFmt.LoadString(IDS_PHYSICAL_MEM);

	MEMORYSTATUS MemStat;
	MemStat.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&MemStat);
	wsprintf(str.GetBuffer(80), strFmt, MemStat.dwTotalPhys / 1024L);
	str.ReleaseBuffer();
	SetDlgItemText(IDC_PHYSICAL_MEM, str);

	// fill disk free information
	struct _diskfree_t diskfree;
	if (_getdiskfree(_getdrive(), &diskfree) == 0)
	{
		strFmt.LoadString(IDS_DISK_SPACE);
		wsprintf(str.GetBuffer(80), strFmt,
			(DWORD)diskfree.avail_clusters *
			(DWORD)diskfree.sectors_per_cluster *
			(DWORD)diskfree.bytes_per_sector / (DWORD)1024L);
		str.ReleaseBuffer();
	}
	else
		str.LoadString(IDS_DISK_SPACE_UNAVAIL);
	SetDlgItemText(IDC_DISK_SPACE, str);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// CSplashWnd dialog

BEGIN_MESSAGE_MAP(CSplashWnd, CDialog)
	//{{AFX_MSG_MAP(CSplashWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSplashWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplashWnd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CSplashWnd::Create(CWnd* pParent)
{
	//{{AFX_DATA_INIT(CSplashWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	if (!CDialog::Create(CSplashWnd::IDD, pParent))
	{
		TRACE0("Warning: creation of CSplashWnd dialog failed\n");
		return FALSE;
	}

	return TRUE;
}

BOOL CSplashWnd::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();

	// initialize the big icon control
	m_icon.SubclassDlgItem(IDC_BIGICON, this);
	m_icon.SizeToContent();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// CSplashWnd message handlers

/////////////////////////////////////////////////////////////////////////////
// CBigIcon

BEGIN_MESSAGE_MAP(CBigIcon, CButton)
	//{{AFX_MSG_MAP(CBigIcon)
	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBigIcon message handlers

#define CY_SHADOW   4
#define CX_SHADOW   4

void CBigIcon::SizeToContent()
{
	// get system icon size
	int cxIcon = ::GetSystemMetrics(SM_CXICON);
	int cyIcon = ::GetSystemMetrics(SM_CYICON);

	// a big icon should be twice the size of an icon + shadows
	SetWindowPos(NULL, 0, 0, cxIcon*2 + CX_SHADOW + 4, cyIcon*2 + CY_SHADOW + 4,
		SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
}

void CBigIcon::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	ASSERT(pDC != NULL);

	CRect rect;
	GetClientRect(rect);
	int cxClient = rect.Width();
	int cyClient = rect.Height();

	// load icon
	HICON hicon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	if (hicon == NULL)
		return;

	// draw icon into off-screen bitmap
	int cxIcon = ::GetSystemMetrics(SM_CXICON);
	int cyIcon = ::GetSystemMetrics(SM_CYICON);

	CBitmap bitmap;
	if (!bitmap.CreateCompatibleBitmap(pDC, cxIcon, cyIcon))
		return;
	CDC dcMem;
	if (!dcMem.CreateCompatibleDC(pDC))
		return;
	CBitmap* pBitmapOld = dcMem.SelectObject(&bitmap);
	if (pBitmapOld == NULL)
		return;

	// blt the bits already on the window onto the off-screen bitmap
	dcMem.StretchBlt(0, 0, cxIcon, cyIcon, pDC,
		2, 2, cxClient-CX_SHADOW-4, cyClient-CY_SHADOW-4, SRCCOPY);

	// draw the icon on the background
	dcMem.DrawIcon(0, 0, hicon);

	// draw border around icon
	CPen pen;
	pen.CreateStockObject(BLACK_PEN);
	CPen* pPenOld = pDC->SelectObject(&pen);
	pDC->Rectangle(0, 0, cxClient-CX_SHADOW, cyClient-CY_SHADOW);
	if (pPenOld)
		pDC->SelectObject(pPenOld);

	// draw shadows around icon
	CBrush br;
	br.CreateStockObject(DKGRAY_BRUSH);
	rect.SetRect(cxClient-CX_SHADOW, CY_SHADOW, cxClient, cyClient);
	pDC->FillRect(rect, &br);
	rect.SetRect(CX_SHADOW, cyClient-CY_SHADOW, cxClient, cyClient);
	pDC->FillRect(rect, &br);

	// draw the icon contents
	pDC->StretchBlt(2, 2, cxClient-CX_SHADOW-4, cyClient-CY_SHADOW-4,
		&dcMem, 0, 0, cxIcon, cyIcon, SRCCOPY);
}

BOOL CBigIcon::OnEraseBkgnd(CDC*)
{
	return TRUE;    // we don't do any erasing...
}

/////////////////////////////////////////////////////////////////////////////

void CAboutBox::OnBnClickedButton_SOURCE()
{
		OpenSelectFolder(1);
}
void CAboutBox::OnBnClickedButton_DEST()
{
	OpenSelectFolder(2);
}



void CAboutBox::OpenSelectFolder(int i)
{
	BROWSEINFO biInput;
	ZeroMemory(&biInput, sizeof(BROWSEINFO));
	biInput.hwndOwner = m_hWnd; // 현재 핸들
	biInput.lpszTitle = "Select Input Forder"; // 폴더선택창 열었을때 보여지는 문구
	biInput.pidlRoot = NULL;
	biInput.lpfn = BrowseCallbackProc; // 콜백함수
	//biInput.lParam = (LPARAM)(LPCSTR)m_strAppPath;
	biInput.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_NONEWFOLDERBUTTON | BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;

	LPITEMIDLIST pidlFolderInput = SHBrowseForFolder(&biInput);
	
//	if (pidlFolderInput == NULL) return;

	TCHAR szPathInput[_MAX_PATH] = {0};
	SHGetPathFromIDList(pidlFolderInput, szPathInput);

if (i == 1) 	
	SetDlgItemText( IDC_EDIT1, szPathInput );
else if (i==2) 
	SetDlgItemText( IDC_EDIT2, szPathInput );

}
int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM dwData)
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		SendMessage( hwnd, BFFM_SETSELECTION, (WPARAM)TRUE, (LPARAM) dwData );
		break;
	}
	return 0;
}

void CAboutBox::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CAboutBox::OnBnClickedButtonDecrypt()
{
	CString strInput; 
	CString strOutput;
	
	GetDlgItemText( IDC_EDIT1, strInput );
	GetDlgItemText( IDC_EDIT2, strOutput );

	if ( strInput.IsEmpty() || strOutput.IsEmpty() )	return;
	
//if( strExt != _T(".CHARSET") && strExt != _T(".CHARCLASS") &&
	//	strExt != _T(".CLASSCONST") && strExt != _T(".CROWSALE") &&
	//	strExt != _T(".GENITEM") && strExt != _T(".BIN") )
	RunDecryptFolder(strInput,strOutput,".charset");
	RunDecryptFolder(strInput,strOutput,".classconst");
	RunDecryptFolder(strInput,strOutput,".charclass");
	RunDecryptFolder(strInput,strOutput,".crowsale");
	RunDecryptFolder(strInput,strOutput,".genitem");
	RunDecryptFolder(strInput,strOutput,".bin");
	RunDecryptFolder(strInput,strOutput,".txt");
	RunDecryptFolder(strInput,strOutput,".ini");
	//
	RunDecryptFolder(strInput,strOutput,".als");

	AfxMessageBox( "Decrypt Successful!", MB_OK );
}

void CAboutBox::OnBnClickedButtonEncrypt()
{
	CString strInput; 
	CString strOutput;
	
	GetDlgItemText( IDC_EDIT1, strInput );
	GetDlgItemText( IDC_EDIT2, strOutput );

	if ( strInput.IsEmpty() || strOutput.IsEmpty() )	return;
	

	RunEncryptFolder(strInput,strOutput,".charset");
	RunEncryptFolder(strInput,strOutput,".classconst");
	RunEncryptFolder(strInput,strOutput,".charclass");
	RunEncryptFolder(strInput,strOutput,".crowsale");
	RunEncryptFolder(strInput,strOutput,".genitem");
	RunEncryptFolder(strInput,strOutput,".bin");
	RunEncryptFolder(strInput,strOutput,".txt");
	RunEncryptFolder(strInput,strOutput,".ini");
	//
	RunEncryptFolder(strInput,strOutput,".als");

	AfxMessageBox( "Encrypt Successful!", MB_OK );
	
}

void CAboutBox::AddEditString( const char* szInfo )
{
   /* int len = m_cEdit.GetWindowTextLength();

	m_cEdit.SetSel( len, len );
	m_cEdit.ReplaceSel( szInfo );	

	len = m_cEdit.GetWindowTextLength();
	m_cEdit.SetSel( len, len );
	m_cEdit.ReplaceSel( "\r\n" );*/

	return;
}

BOOL CAboutBox::RunDecryptFolder( const CString& strInput, const CString& strOutput, const CString& strSearchPattern )
{
	AddEditString( "Run Decrypt File in Forder" );
	AddEditString( strInput );

	// DDS FILE 변환
	CString strFind = strInput;
	//strFind += "\\*.charset";
	strFind += "\\*" + strSearchPattern;
	CString strOutFile, strOutPath;
	strOutPath = strOutput;
	strOutPath += "\\";

	CString strInFile, strInPath;
	strInPath = strInput;
	strInPath += "\\";

	CString strFile;
	
	CFileFind finder;	
	BOOL bFind ( TRUE );

	if ( !finder.FindFile( strFind ) )
	{
		bFind = FALSE;
	}

	int nCntFile =0, nCntSuccess = 0;
	CString strTemp;

	while( bFind )
	{
		nCntFile++;
		bFind = finder.FindNextFile();
		strFile = finder.GetFileName();
		strInFile = strInPath;
		strInFile += strFile;
		strOutFile = strOutPath;
		strOutFile += strFile.Left( strFile.ReverseFind('.'));
		strOutFile += strSearchPattern; //".charset";
		
		if ( !RunDecryptFile( strInFile, strOutFile ) )
		{
			strTemp.Format( " Error Decrypt File : %s ", strFile );
			AddEditString( strTemp );
			continue;
		}
		
		strTemp.Format( " Success Decrypt File : %s ", strFile );
		AddEditString( strTemp );

		nCntSuccess++;
	}

	CString strResult;
	strResult.Format( "%d in %d File Encrypt Success", nCntSuccess, nCntFile );
	AddEditString( strResult );

	//AfxMessageBox( strResult, MB_OK );

	return TRUE;
}


BOOL CAboutBox::RunDecryptFile( const CString& strInput, const CString& strOutput )
{

		char ext[_MAX_EXT] = {0};
	_splitpath( strInput, NULL, NULL, NULL, ext );

	CString strExt(ext);
	strExt.MakeUpper();

	//if( strExt != _T(".CHARSET") && strExt != _T(".CHARCLASS") &&
	//	strExt != _T(".CLASSCONST") && strExt != _T(".CROWSALE") &&
	//	strExt != _T(".GENITEM") && strExt != _T(".BIN") )
	//{
	//	if( IDNO == AfxMessageBox( "디코딩 하시겠습니까?", MB_YESNO ) )
	//		return TRUE;
	//}

	CStringFile StrFile;
	if ( !StrFile.Open ( strInput, TRUE ) ) // 스트링파일 클래스 오픈, 디코딩한다.
		return FALSE;

	CString strTemp, strLine;
	while ( StrFile.GetNextLine(strLine) ) // 파일로 부터 한라인씩 읽어온다.
	{
		strLine += "\r\n";
		strTemp += strLine;
	}

	strTemp.SetAt(strTemp.GetLength()-2, NULL); // 마지막 \r\n은 제거한다.


	FILE* fp = fopen ( strOutput, "wb" );
	
	if ( fp )
	{
		
		fprintf ( fp, "%s", strTemp );
		fclose ( fp );
	}


	return TRUE;
}





BOOL CAboutBox::RunEncryptFolder( const CString& strInput, const CString& strOutput, const CString& strSearchPattern )
{
	AddEditString( "Run Decrypt File in Forder" );
	AddEditString( strInput );

	
	CString strFind = strInput;
	strFind += "\\*" + strSearchPattern;
	CString strOutFile, strOutPath;
	strOutPath = strOutput;
	strOutPath += "\\";

	CString strInFile, strInPath;
	strInPath = strInput;
	strInPath += "\\";

	CString strFile;
	
	CFileFind finder;	
	BOOL bFind ( TRUE );

	if ( !finder.FindFile( strFind ) )
	{
		bFind = FALSE;
	}

	int nCntFile =0, nCntSuccess = 0;
	CString strTemp;

	while( bFind )
	{
		nCntFile++;
		bFind = finder.FindNextFile();
		strFile = finder.GetFileName();
		strInFile = strInPath;
		strInFile += strFile;
		strOutFile = strOutPath;
		strOutFile += strFile.Left( strFile.ReverseFind('.'));
		strOutFile += strSearchPattern; //".charset";
		
		if ( !RunEncryptFile( strInFile, strOutFile ) )
		{
			strTemp.Format( " Error Encrypt File : %s ", strFile );
			AddEditString( strTemp );
			continue;
		}
		
		strTemp.Format( " Success Encrypt File : %s ", strFile );
		AddEditString( strTemp );

		nCntSuccess++;
	}

	CString strResult;
	strResult.Format( "%d in %d File Encrypt Success", nCntSuccess, nCntFile );
	AddEditString( strResult );

	return TRUE;
}


BOOL CAboutBox::RunEncryptFile( const CString& strInput, const CString& strOutput )
{

//Read File
			char ext[_MAX_EXT] = {0};
	_splitpath( strInput, NULL, NULL, NULL, ext );

	CString strExt(ext);
	strExt.MakeUpper();


	CStringFile StrFile;
	if ( !StrFile.Open ( strInput, FALSE ) ) 
		return FALSE;

	CString strTempDec, strLine;
	while ( StrFile.GetNextLine(strLine) ) 
	{
		strLine += "\r\n";
		strTempDec += strLine;
	}

	strTempDec.SetAt(strTempDec.GetLength()-2, NULL); 


//Encrypt File


	CRijndael oRijndael;
	oRijndael.Initialize( CRijndael::sm_Version[CRijndael::VERSION-1].c_str(), CRijndael::sm_KeyLength[CRijndael::VERSION-1] );

	int nLen = oRijndael.GetEncryptStringLength( strTempDec );
	char * szBuffer = new char[nLen];

	oRijndael.EncryptEx( strTempDec.GetString(), szBuffer, strTempDec.GetLength() );
	int nVersion = CRijndael::VERSION;

	CFile file;
	file.Open( strOutput, CFile::modeCreate|CFile::modeWrite );	
	file.Write( &nVersion, sizeof(int) );							
	file.Write( szBuffer, nLen );	
	file.Close();

	delete [] szBuffer;

	return TRUE;
}
