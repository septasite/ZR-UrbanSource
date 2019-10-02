// RanViewDlg.cpp : implementation file
//
#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerDlg.h"
#include "RanManagerTab.h"
#include "RanManagerMain.h"
#include "EtcFunction.h"


// CRanManagerMain dialog
IMPLEMENT_DYNAMIC(CRanManagerMain, CPropertyPage)
CRanManagerMain::CRanManagerMain(LOGFONT logfont)
	: CPropertyPage(CRanManagerMain::IDD)
	,m_pFont( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerMain::~CRanManagerMain()
{
}

void CRanManagerMain::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STATUS, m_cEditLog );
	DDX_Control(pDX, IDC_EDIT_INFO, m_cEditInfo );
}

BEGIN_MESSAGE_MAP(CRanManagerMain, CPropertyPage)
END_MESSAGE_MAP()

// CRanManagerMain message handlers
BOOL CRanManagerMain::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;
	CStringArray str;
	str.Add(_T("This program Use Client Data as Reference to read Database Information like Item ID, Skill ID , Quest Id and Map ID. Please use the correct client that matches with the character data in your database"));
	str.Add(_T("This program connects to database using ODBC driver please setup your ODBC properly for this to work"));
	str.Add(_T("This program read database binary data using the same method of server files since this program is built using the RanOnline source code"));
	str.Add(_T("This Program read information directly inside the rcc(if you cant see the item and skill information make sure the glogic.rcc is updated!)"));
	str.Add(_T("Maximum Gold,Premium Point,Vote Point,Exp,ReExp and locker gold value is 99,999,999,999,999 or -99,999,999,999,999 if the value exceeds this limitations character wont save! This is a Compiler limitation"));
	str.Add(_T("For Any Bugs and errors Please PM me i990x@yahoo.com"));
	str.Add(_T("Your Hard Working Friend/Developer/Coder    -JDev"));

	for(int ii =0 ;ii<str.GetSize();ii++)
	{
		AddInfo( str.GetAt(ii));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CRanManagerMain::AddLog( const char* szInfo )
{
    int len = m_cEditLog.GetWindowTextLength();

	if ( m_cEditLog.GetWindowTextLength() >= m_cEditLog.GetLimitText() )
	{
		m_cEditLog.SetSel( 0 , m_cEditLog.GetWindowTextLength() );
	}else{
		m_cEditLog.SetSel( len, len );
	}
	m_cEditLog.ReplaceSel( szInfo );	

	len = m_cEditLog.GetWindowTextLength();
	m_cEditLog.SetSel( len, len );
	m_cEditLog.ReplaceSel( "\r\n" );

	return;
}

void CRanManagerMain::AddInfo( const char* szInfo )
{
    int len = m_cEditInfo.GetWindowTextLength();

	if ( m_cEditInfo.GetWindowTextLength() >= m_cEditInfo.GetLimitText() )
	{
		m_cEditInfo.SetSel( 0 , m_cEditInfo.GetWindowTextLength() );
	}else{
		m_cEditInfo.SetSel( len, len );
	}
	m_cEditInfo.ReplaceSel( szInfo );	

	len = m_cEditInfo.GetWindowTextLength();
	m_cEditInfo.SetSel( len, len );
	m_cEditInfo.ReplaceSel( "\r\n" );

	return;
}


