// RanManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerDlg.h"
#include "RanManagerTab.h"

#include "GLOGIC.h"
#include "DxResponseMan.h"
#include "RANPARAM.h"
#include "DxServerInstance.h"
#include "SUBPATH.h"
#include "GLItemMan.h"
#include "GLItem.h"
#include "GLSkill.h"

#include "CCfg.h"
#include "COdbc.h"
#include "EtcFunction.h"
#include "../NetServerLib/s_COdbcManager.h"
#include ".\ranmanagerdlg.h"
#include "s_NetGlobal.h"
#include "RanManagerComments.h"
#include "LogScript.h"

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


// CRanManagerDlg dialog
CRanManagerDlg::CRanManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRanManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bSuccess = false;
}

void CRanManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MAINTYPE, m_cMainPage );
}

BEGIN_MESSAGE_MAP(CRanManagerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP

	ON_BN_CLICKED(IDC_BUTTON_MAIN_SELECT, OnBnClickedButtonMainSelect)
END_MESSAGE_MAP()


// CRanManagerDlg message handlers

BOOL CRanManagerDlg::OnInitDialog()
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

	CRect SheetRect;
	CWnd *pWnd;
	pWnd = GetDlgItem ( IDC_STATIC_WINDOW );
	pWnd->GetWindowRect ( SheetRect );
	ScreenToClient ( &SheetRect );
	LOGFONT logfont = {0};
	CFont* pFont = GetFont();
	if ( pFont ) pFont->GetLogFont( &logfont );
	m_pToolTab = new CRanManagerTab ( SheetRect, logfont, this );
	m_pToolTab->Create( this, WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0 );
	m_pToolTab->ModifyStyleEx (0, WS_EX_CONTROLPARENT);

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

	GLOGIC::bGLOGIC_PACKFILE = FALSE;
	GLOGIC::bGLOGIC_ZIPFILE = TRUE;
	GLOGIC::bENGLIB_ZIPFILE = TRUE;

	char szFullPath[MAX_PATH] = {0};
	strcpy ( szFullPath, m_szAppPath );
	strcat ( szFullPath, SUBPATH::GLOGIC_FILE );
	GLOGIC::SetPath ( szFullPath );
	RANPARAM::LOAD ( m_szAppPath );
	DxResponseMan::GetInstance().OneTimeSceneInit ( m_szAppPath, this, RANPARAM::strFontType, RANPARAM::dwLangSet, RANPARAM::strGDIFont );
	GLItemMan::GetInstance().OneTimeSceneInit();
	GLSkillMan::GetInstance().OneTimeSceneInit();
	LOGSCRIPT::InitLog(m_szAppPath);

	GMTOOL::Create ( m_szAppPath ); 

	for ( int i = 0; i < MAINPAGE_SIZE; ++i )
	{
		m_cMainPage.InsertString( i, RMComments::m_PageMain[i].c_str() );
	}
	m_cMainPage.SetCurSel( 0 );

	// TODO: Add extra initialization here
	if (!bSuccess)	ConnectDatabase();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRanManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRanManagerDlg::OnPaint() 
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
HCURSOR CRanManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRanManagerDlg::ConnectDatabase()
{
	if (!CToolCfg::GetInstance()->Load())	PostMessage(WM_CLOSE, 0, 0);

	int nRetCode;
	bSuccess = true;

	nRetCode = COdbc::GetInstance()->OpenGameDB();
    if (nRetCode == DB_ERROR)	
	{	m_pToolTab->SendLog("Game DB Open Fail :(");	bSuccess = false;	}
	else  m_pToolTab->SendLog("Game DB Open Success :)");

	nRetCode = COdbc::GetInstance()->OpenLogDB();
    if (nRetCode == DB_ERROR)	
	{	m_pToolTab->SendLog("Log DB Open Fail :(");		bSuccess = false;	}
	else  m_pToolTab->SendLog("Log DB Open Success :)");

	nRetCode = COdbc::GetInstance()->OpenShopDB();
    if (nRetCode == DB_ERROR)	
	{	m_pToolTab->SendLog("Shop DB Open Fail :(");	bSuccess = false;	}
	else  m_pToolTab->SendLog("Shop DB Open Success :)");

	nRetCode = COdbc::GetInstance()->OpenUserDB();
    if (nRetCode == DB_ERROR)	
	{	m_pToolTab->SendLog("User DB Open Fail :(");	bSuccess = false;	}
	else  m_pToolTab->SendLog("User DB Open Success :)");

	//get total ram
	MEMORYSTATUS MemStat;
	MemStat.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&MemStat);
	CString strRam = "";
	strRam.Format("Machine Memory:%d",MemStat.dwTotalPhys / 1024L);
	m_pToolTab->SendLog( strRam.GetString() );

	//get machine ip
	WORD wVersionRequested;
	WSADATA wsaData;
	char Name[255];
	PHOSTENT HostInfo;
	wVersionRequested = MAKEWORD( 1, 1 );
	char *IPAdd;
	/*CString strIP;
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

					strIP.Format("Your Ip is:%s",IPAdd);
					m_pToolTab->SendLog( strIP.GetString() );
				}
			}
			strIP.Format("Logging your IP...." );
			m_pToolTab->SendLog( strIP.GetString() );
		}
	}*/
}

void CRanManagerDlg::OnBnClickedButtonMainSelect()
{
	int nSelect = m_cMainPage.GetCurSel();
	if ( bSuccess )	
	{
		SetWin_Text(this,IDC_EDIT_MAINTYPE,RMComments::m_PageMain[nSelect].c_str() );
		CString strTitle;
		strTitle.Format("%s--%s","RanManager",RMComments::m_PageMain[nSelect].c_str() );
		SetWindowText( strTitle.GetString() );

		switch (nSelect)
		{
		case MAINPAGE_MAIN:	m_pToolTab->ActivePage ( MAINPAGE_MAIN );	break;
		case MAINPAGE_USER:	m_pToolTab->ActivePage ( MAINPAGE_USER );	break;
		case MAINPAGE_CHAR:	m_pToolTab->ActivePage ( MAINPAGE_CHAR );	break;
		case MAINPAGE_GUILD:	m_pToolTab->ActivePage ( MAINPAGE_GUILD );	break;
		case MAINPAGE_VEHICLE:	m_pToolTab->ActivePage ( MAINPAGE_VEHICLE );	break;
		case MAINPAGE_PET:	m_pToolTab->ActivePage ( MAINPAGE_PET );	break;
		};
	}
}
