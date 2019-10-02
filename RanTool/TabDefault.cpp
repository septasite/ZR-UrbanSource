// TabDefault.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "TabDefault.h"
#include "ToolTab.h"

// CTabDefault dialog

IMPLEMENT_DYNAMIC(CTabDefault, CPropertyPage)
CTabDefault::CTabDefault(LOGFONT logfont)
	: CPropertyPage(CTabDefault::IDD)
	,m_pFont( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CTabDefault::~CTabDefault()
{
}

void CTabDefault::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HISTORY, m_cEditHistory );
}


BEGIN_MESSAGE_MAP(CTabDefault, CPropertyPage)
END_MESSAGE_MAP()


// CTabDefault message handlers
BOOL CTabDefault::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_pToolTab->ChangeDialogFont( this, m_pFont, CDF_TOPLEFT );
	
	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTabDefault::AddEditString( const char* szInfo )
{
    int len = m_cEditHistory.GetWindowTextLength();

	if ( m_cEditHistory.GetWindowTextLength() >= m_cEditHistory.GetLimitText() )
	{
		m_cEditHistory.SetSel( 0 , m_cEditHistory.GetWindowTextLength() );
	}else{
		m_cEditHistory.SetSel( len, len );
	}
	m_cEditHistory.ReplaceSel( szInfo );	

	len = m_cEditHistory.GetWindowTextLength();
	m_cEditHistory.SetSel( len, len );
	m_cEditHistory.ReplaceSel( "\r\n" );

	return;
}