// CryptionRCCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CryptionRCC.h"
#include "CryptionRCCDlg.h"
#include ".\cryptionrccdlg.h"

#include "strsafe.h"

//#include "..\_NeoProtect\globalNeo.h"

#include "..\EngineLib\Crypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCryptionRCCDlg dialog



CCryptionRCCDlg::CCryptionRCCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCryptionRCCDlg::IDD, pParent)
	, m_cInput(_T(""))
	, m_cOutput(_T(""))
	, m_cEditInfo(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCryptionRCCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_cInput);
	DDX_Text(pDX, IDC_EDIT2, m_cOutput);
	DDX_Control(pDX, IDC_COMBO1, m_cCombobox);
	DDX_Control(pDX, IDC_MODCRYPTION, m_cModCryption);
	DDX_Text(pDX, IDC_EDIT_STATIC, m_cEditInfo);
	DDX_Control(pDX, IDC_EDIT_STATIC, m_cEdit);
}

BEGIN_MESSAGE_MAP(CCryptionRCCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedButton6)
	ON_EN_CHANGE(IDC_EDIT_STATIC, OnEnChangeEditStatic)
END_MESSAGE_MAP()


// CCryptionRCCDlg message handlers

BOOL CCryptionRCCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_cModCryption.InsertString( 0, "RCC" );
	m_cModCryption.SetCurSel( 0 );
	m_cCombobox.InsertString( 0, "File Mode" );
	m_cCombobox.InsertString( 1, "Folder Mode" );
	m_cCombobox.SetCurSel( 0 );
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCryptionRCCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCryptionRCCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCryptionRCCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCryptionRCCDlg::OnBnClickedButton1()
{
	int Select = m_cCombobox.GetCurSel();
	switch( Select )
	{
	case 0:
		{
			CString szFilterInput = "ALL FILE TYPE|*.*|";
			CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
			dlgInput.m_ofn.lpstrInitialDir = m_cInput;
			if ( dlgInput.DoModal() != IDOK ) return;
			CString strFileName = dlgInput.GetFileName();
			m_cInput = dlgInput.GetPathName();
			SetDlgItemText( IDC_EDIT1, dlgInput.GetPathName() );
			UpdateData(true);
		}break;
	case 1:
		{
			BROWSEINFO biInput;
			ZeroMemory(&biInput, sizeof(BROWSEINFO));
			biInput.hwndOwner = m_hWnd; // 현재 핸들
			biInput.lpszTitle = "Select Input Forder"; // 폴더선택창 열었을때 보여지는 문구
			biInput.pidlRoot = NULL;
			biInput.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_NONEWFOLDERBUTTON | BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;

			LPITEMIDLIST pidlFolderInput = SHBrowseForFolder(&biInput);
			
			if (pidlFolderInput == NULL) return;

			TCHAR szPathInput[_MAX_PATH] = {0};
			SHGetPathFromIDList(pidlFolderInput, szPathInput);
			m_cInput = szPathInput;
			SetDlgItemText( IDC_EDIT1, szPathInput );
			UpdateData(true);
		}break;
	}
}

void CCryptionRCCDlg::OnBnClickedButton2()
{
	int Select = m_cCombobox.GetCurSel();
	switch( Select )
	{
	case 0:
		{
			CString szFilterInput = "ALL FILE TYPE|*.*|";
			CFileDialog dlgInput(false,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
			dlgInput.m_ofn.lpstrInitialDir = m_cOutput;
			if ( dlgInput.DoModal() != IDOK ) return;
			CString strFileName = dlgInput.GetFileName();
			m_cOutput = dlgInput.GetPathName();
			SetDlgItemText( IDC_EDIT2, dlgInput.GetPathName() );
			UpdateData(true);
		}break;
	case 1:
		{
			BROWSEINFO biOutput;
			ZeroMemory(&biOutput, sizeof(BROWSEINFO));
			biOutput.hwndOwner = m_hWnd; // 현재 핸들
			biOutput.lpszTitle = "Select Ouput Forder"; // 폴더선택창 열었을때 보여지는 문구
			biOutput.pidlRoot = NULL;
			biOutput.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_NONEWFOLDERBUTTON | BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;

			LPITEMIDLIST pidlFolderOutput = SHBrowseForFolder(&biOutput);
			
			if (pidlFolderOutput == NULL) return;

			TCHAR szPathOutput[_MAX_PATH] = {0};
			SHGetPathFromIDList(pidlFolderOutput, szPathOutput);
			
			SetDlgItemText( IDC_EDIT2, szPathOutput );
			m_cOutput = szPathOutput;
			UpdateData(true);
		}break;
	}
}

void CCryptionRCCDlg::OnBnClickedButton3()
{
	int Select = m_cCombobox.GetCurSel();
	switch( Select )
	{
	case FileCryption:
		{
			if ( m_cInput == "" || m_cOutput == "" )
				break;
			FileEncryption();
		}break;
	case FolderCryption:
		{
			if ( m_cInput == "" || m_cOutput == "" )
				break;
			FolderEncryption( m_cInput , m_cOutput );
		}break;
	}
}

void CCryptionRCCDlg::OnBnClickedButton4()
{
	int Select = m_cCombobox.GetCurSel();
	switch( Select )
	{
	case FileCryption:
		{
			if ( m_cInput == "" || m_cOutput == "" )
				break;
			FileDecryption();
		}break;
	case FolderCryption:
		{
			if ( m_cInput == "" || m_cOutput == "" )
				break;
			FolderDecryption( m_cInput , m_cOutput );
		}break;
	}
}

void CCryptionRCCDlg::OnBnClickedButton5()
{
	const char * cInput = m_cInput;
	const char * cOutput = m_cOutput;
	SetDlgItemText( IDC_EDIT1, cOutput );
	SetDlgItemText( IDC_EDIT2, cInput );
	UpdateData(true);
}

void CCryptionRCCDlg::OnCbnSelchangeCombo1()
{
	clearslot();
}

void CCryptionRCCDlg::clearslot()
{
	SetDlgItemText( IDC_EDIT1, "" );
	SetDlgItemText( IDC_EDIT2, "" );
	UpdateData(true);
}

BOOL CCryptionRCCDlg::FolderEncryption( const CString& strInput, const CString& strOutput )
{
	CString strFind = strInput;
	strFind += "\\*";

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
		strOutFile += strFile;//.Left( strFile.ReverseFind('.'));

		int Select = m_cModCryption.GetCurSel();
		if ( Select == NormalCryption ){
			if ( strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".rcc") || strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".exe") )
			{
				continue;
			}
		}else{
			if ( strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".rcc") || strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".exe") )
			{
				continue;
			}
		}
		if ( strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".lnk")
			|| strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".url")
			|| strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".exe")
			|| strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".dll")
			|| strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".rcc")
			|| strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".zip")
			|| strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".7z") )
		{
			continue;
		}

		if ( !FileEncryption( strInFile, strOutFile ) )
		{
			CString strResult;
			strResult.Format( "FileEncryption::File(%s)TO(%s) Fall", finder.GetFileName(), finder.GetFileName() );
			AddEditString( strResult );
			continue;
		}
		CString strResult;
		strResult.Format( "FileEncryption::File(%s)TO(%s) Success", finder.GetFileName(), finder.GetFileName() );
		AddEditString( strResult );
		nCntSuccess++;
	}
	CString sReport;
	sReport.Format( "Success File : %d File All : %d",nCntSuccess ,nCntFile );
	AddEditString( sReport );
	return TRUE;
}

BOOL CCryptionRCCDlg::FolderDecryption( const CString& strInput, const CString& strOutput )
{
	CString strFind = strInput;
	strFind += "\\*";

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
		strOutFile += strFile;//.Left( strFile.ReverseFind('.'));;

		int Select = m_cModCryption.GetCurSel();
		if ( Select == NormalCryption ){
			if ( strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".rcc") || strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".exe") || strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".lnk") )
			{
				continue;
			}
		}else{
			if ( strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".rcc") || strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".exe") || strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".lnk") )
			{
				continue;
			}
		}
		if ( strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".lnk")
			|| strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".url")
			|| strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".exe")
			|| strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".dll")
			|| strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".rcc")
			|| strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".zip")
			|| strFile.Right( strFile.GetLength() - strFile.ReverseFind('.') ) == _T(".7z") )
		{
			continue;
		}
		
		if ( !FileDecryption( strInFile, strOutFile ) )
		{
			CString strResult;
			strResult.Format( "FileDecryption::File(%s)TO(%s) Fall", finder.GetFileName(), finder.GetFileName() );
			AddEditString( strResult );
			continue;
		}
		CString strResult;
		strResult.Format( "FileDecryption::File(%s)TO(%s) Success", finder.GetFileName(), finder.GetFileName() );
		AddEditString( strResult );
		nCntSuccess++;
	}
	CString sReport;
	sReport.Format( "Success File : %d File All : %d",nCntSuccess ,nCntFile );
	AddEditString( sReport );
	return TRUE;
}

BOOL CCryptionRCCDlg::FileEncryption(CString fileinput , CString fileoutput)
{
	FILE * pFileInput = fopen( fileinput , "rb" );
	if ( !pFileInput ) return FALSE;
	fseek ( pFileInput, 0, SEEK_END );
	int nSize = ftell ( pFileInput );
	fseek ( pFileInput, 0, SEEK_SET );	
	BYTE* pBuffer = new BYTE[nSize];
	fread( pBuffer, sizeof(BYTE), nSize, pFileInput );
	fclose(pFileInput);
	//const char* ccInput = (LPCTSTR)fileinput;
	char * cInput = (char *)(LPCTSTR)fileinput;
	char * cOutput = (char *)(LPCTSTR)fileoutput;
	int Select = m_cModCryption.GetCurSel();
	switch(Select)
	{
		case NormalCryption:
			CCrypt::Encryption( pBuffer, nSize );
		break;
		default:
			MessageBox(_T("This Mode Disable"),_T("CryptionRCC"),MB_OK);
		break;
	}
	
	{
		FILE * pFileOutput = fopen( fileoutput , "wb" );
		if ( !pFileOutput ) return FALSE;
		fwrite( pBuffer , sizeof(BYTE), nSize , pFileOutput );
		fclose(pFileOutput);
	}
	return TRUE;
}
BOOL CCryptionRCCDlg::FileDecryption(CString fileinput , CString fileoutput)
{
	FILE * pFileInput = fopen( fileinput , "rb" );
	if ( !pFileInput ) return FALSE;
	fseek ( pFileInput, 0, SEEK_END );
	int nSize = ftell ( pFileInput );
	fseek ( pFileInput, 0, SEEK_SET );	
	BYTE* pBuffer = new BYTE[nSize];
	fread( pBuffer, sizeof(BYTE), nSize, pFileInput );
	fclose(pFileInput);
	char * cInput = (char *)(LPCTSTR)fileinput;
	char * cOutput = (char *)(LPCTSTR)fileoutput;
	int Select = m_cModCryption.GetCurSel();
	switch(Select)
	{
		case NormalCryption:
			CCrypt::Decryption( pBuffer, nSize );
		break;
		default:
			MessageBox(_T("This Mode Disable"),_T("CryptionRCC"),MB_OK);
		break;
	}
	
	{
		FILE * pFileOutput = fopen( fileoutput , "wb" );
		if ( !pFileOutput ) return FALSE;
		fwrite( pBuffer , sizeof(BYTE), nSize , pFileOutput );
		fclose(pFileOutput);
	}
	return TRUE;
}

BOOL CCryptionRCCDlg::FileEncryption()
{
	if ( FileEncryption( m_cInput , m_cOutput ) )
	{
		CString strResult;
		strResult.Format( "FileEncryption::File(%s)TO(%s) Success", m_cInput, m_cOutput );
		AddEditString( strResult );
	}else{
		CString strResult;
		strResult.Format( "FileEncryption::File(%s)TO(%s) Fall", m_cInput, m_cOutput );
		AddEditString( strResult );
	}
	return TRUE;
}
BOOL CCryptionRCCDlg::FileDecryption()
{
	if ( FileDecryption( m_cInput , m_cOutput ) )
	{
		CString strResult;
		strResult.Format( "FileDecryption::File(%s)TO(%s) Success", m_cInput, m_cOutput );
		AddEditString( strResult );
	}else{
		CString strResult;
		strResult.Format( "FileDecryption::File(%s)TO(%s) Fall", m_cInput, m_cOutput );
		AddEditString( strResult );
	}
	return TRUE;
}
void CCryptionRCCDlg::OnBnClickedButton6()
{
	SetDlgItemText( IDC_EDIT2, m_cInput );
	UpdateData(true);
}
void CCryptionRCCDlg::AddEditString( const char* szInfo )
{
    int len = m_cEdit.GetWindowTextLength();

	if ( m_cEdit.GetWindowTextLength() >= m_cEdit.GetLimitText() )
	{
		m_cEdit.SetSel( 0 , m_cEdit.GetWindowTextLength() );
	}else{
		m_cEdit.SetSel( len, len );
	}
	m_cEdit.ReplaceSel( szInfo );	

	len = m_cEdit.GetWindowTextLength();
	m_cEdit.SetSel( len, len );
	m_cEdit.ReplaceSel( "\r\n" );

	return;
}

void CCryptionRCCDlg::OnEnChangeEditStatic()
{
	/*
	if ( m_cEdit.GetWindowTextLength() >= m_cEdit.GetLimitText() )
	{
		m_cEdit.SetSel( 0 , m_cEdit.GetWindowTextLength() );
		m_cEdit.Req
	}
	*/
}
