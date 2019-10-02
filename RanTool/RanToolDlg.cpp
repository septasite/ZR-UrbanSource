// RanToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "RanToolDlg.h"
#include ".\rantooldlg.h"
#include "ToolTab.h"
#include "EtcFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRanToolDlg dialog



CRanToolDlg::CRanToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRanToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRanToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TOOL, m_cToolType);
}

BEGIN_MESSAGE_MAP(CRanToolDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnBnClickedButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnBnClickedButtonAbout)
END_MESSAGE_MAP()


// CRanToolDlg message handlers

BOOL CRanToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CString strAppPath;
	TCHAR szPath[MAX_PATH] = {0};
	GetModuleFileName(::AfxGetInstanceHandle(), szPath, MAX_PATH);
	strAppPath = szPath;

	if ( !strAppPath.IsEmpty() )
	{
		DWORD dwFind = strAppPath.ReverseFind ( '\\' );
		if ( dwFind != -1 )
		{
			m_strAppPath = strAppPath.Left ( dwFind );
			
			if ( !m_strAppPath.IsEmpty() )
			if ( m_strAppPath.GetAt(0) == '"' )
				m_strAppPath = m_strAppPath.Right ( m_strAppPath.GetLength() - 1 );

			strcpy ( m_szAppPath, m_strAppPath.GetString() );
		}
	}

	CRect SheetRect;
	CWnd *pWnd;
	pWnd = GetDlgItem ( IDC_STATIC_TOOL );
	pWnd->GetWindowRect ( SheetRect );
	ScreenToClient ( &SheetRect );

	LOGFONT logfont = {0};

	CFont* pFont = GetFont();
	if ( pFont ) pFont->GetLogFont( &logfont );

	m_pToolTab = new CToolTab ( SheetRect, logfont, this );
	m_pToolTab->Create( this, WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0 );
	m_pToolTab->ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	
	//m_pSheetTab->SetActivePage ( ITEMSUITTREEPAGE );

	CString strType[TYPE_SIZE] = 
	{
		"Default",
		"CHF Editor",
		"ABF Editor",
		"VCF Editor",
		"CPS/APS/VPS Editor",
		"ABL Editor",
		"CFG Editor",
		"File Converter",
		"MMP Creator",
		"File Cryption",
	};

	for ( int i = 0; i < TYPE_SIZE; ++i )
	{
		m_cToolType.InsertString( i, strType[i].GetString() );
	}

	m_cToolType.SetCurSel( 0 );
	bSave = false;

	m_pToolTab->AddHistory("Welcome to RanTool");
	m_pToolTab->AddHistory("Please Select Tool Type");

	MEMORYSTATUS MemStat;
	MemStat.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&MemStat);
	CString strRam = "";
	strRam.Format("Machine Memory:%d",MemStat.dwTotalPhys / 1024L);
	m_pToolTab->AddHistory( strRam );
	GetIPAdd();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRanToolDlg::OnPaint() 
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
HCURSOR CRanToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRanToolDlg::OnBnClickedButtonRun()
{
	CString strType[TYPE_SIZE] = 
	{
		"Default",
		"CHF Editor",
		"ABF Editor",
		"VCF Editor",
		"CPS/APS/VPS Editor",
		"ABL Editor",
		"CFG Editor",
		"File Converter",
		"MMP Creator",
		"File Cryption",
	};

	int Select = m_cToolType.GetCurSel();
	SetWin_Text ( this, IDC_EDIT_TOOL, strType[Select].GetString() );
	bSave = (bool)GetWin_Check ( this, IDC_CHECK_SAVE );
	m_pToolTab->ActivateTab( Select , bSave);	
}

void CRanToolDlg::OnBnClickedButtonAbout()
{
	SetWin_Text ( this, IDC_EDIT_TOOL, "Credits" );
	m_pToolTab->ActivateTab( 30 , true);
}

void CRanToolDlg::GetIPAdd()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	char Name[255];
	PHOSTENT HostInfo;
	wVersionRequested = MAKEWORD( 1, 1 );
	char *IPAdd;
	CString strTemp;
	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
	{
		if( gethostname ( Name, sizeof(Name)) == 0)
		{
			if((HostInfo = gethostbyname(Name)) != NULL)
			{
				int nCount = 0;
				while(HostInfo->h_addr_list[nCount])
				{
					IPAdd = inet_ntoa(*(struct in_addr *)HostInfo->h_addr_list[nCount]);
 
					++nCount;

					strTemp.Format("Your Ip is:%s",IPAdd);
					m_pToolTab->AddHistory( strTemp.GetString() );
				}
			}
			strTemp.Format("Logging your IP...." );
			m_pToolTab->AddHistory( strTemp.GetString() );
		}
	}
}
