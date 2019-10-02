// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "RanEditLevel.h"

#include "MainFrm.h"
#include "RanEditLevelView.h"
#include "ToolTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND_EX(ID_VIEW_EDITTOOLBAR, OnBarCheck)  
	ON_UPDATE_COMMAND_UI(ID_VIEW_EDITTOOLBAR, OnUpdateControlBarMenu)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndDlgBar.Create(this, IDD_DIALOG_MAIN, 
		CBRS_RIGHT | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY, ID_VIEW_EDITTOOLBAR ))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);


	CFont* pFont = new CFont;
	pFont->CreatePointFont( 80, "Tahoma" ); 
	LOGFONT logfont = {0};
	pFont->GetLogFont( &logfont );
	m_pToolTab = new CToolTab ( CRect(0, 0, 560, 980), logfont, &m_wndDlgBar );
	m_pToolTab->Create( &m_wndDlgBar, WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0 );
	m_pToolTab->ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	//m_pToolTab->ActiveDlgPage( DLG_MAIN );

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::ResetToolTab()
{
	m_pToolTab->SetActivePage( DLG_MAIN );
}

void CMainFrame::SelectCrow( std::string strName )
{
	m_pToolTab->SelectCrow( strName.c_str() );
}