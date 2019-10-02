// TabCredits.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "TabCredits.h"
#include "ToolTab.h"

// CTabCredits dialog

IMPLEMENT_DYNAMIC(CTabCredits, CPropertyPage)
CTabCredits::CTabCredits(LOGFONT logfont)
	: CPropertyPage(CTabCredits::IDD)
	,m_pFont( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CTabCredits::~CTabCredits()
{
}

void CTabCredits::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CREDITS, m_TextScroller );
}


BEGIN_MESSAGE_MAP(CTabCredits, CPropertyPage)
END_MESSAGE_MAP()


// CTabCredits message handlers
BOOL CTabCredits::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_pToolTab->ChangeDialogFont( this, m_pFont, CDF_TOPLEFT );
	
	m_bDlgInit = TRUE;

	CStringArray str;
	m_TextScroller.SetFontName("Tahoma");
	m_TextScroller.SetFontBold(TRUE);
	m_TextScroller.SetFontItalic(FALSE);
	m_TextScroller.SetFontSize(18);
	m_TextScroller.SetBkColor(RGB(255,255,255));
	m_TextScroller.SetTextColor(RGB(0,0,0));
	m_TextScroller.SetBorder(FALSE);

	str.Add(_T("This program can edit ABF,CHF,VCF,CPS,APS,VPS,ABL,CFG files"));
	str.Add(_T("This program can downgrade CFG,BIN and EGP files"));
	str.Add(_T("This program can create MMP files"));
	str.Add(_T("RCC(files inside rcc)  and texture(MTF) Encrypter/Decrypter Included"));
	str.Add(_T("The program functionality is tested and proven to work ingame"));
	str.Add(_T("The program promise to bring user friendly editing and fully functional controls"));
	str.Add(_T("For Any Bugs and errors Please PM me i990x@yahoo.com"));
	str.Add(_T("Your Hard Working Friend/Developer/Coder    -JDev"));

	m_TextScroller.AddLine(str);
	str.RemoveAll();	

	return TRUE;  // return TRUE unless you set the focus to a control
}
