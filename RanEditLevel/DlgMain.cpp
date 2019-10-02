// DlgMain.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgMain.h"
#include "ToolTab.h"
#include ".\dlgmain.h"

#include "EtcFunction.h"

// CDlgMain dialog

IMPLEMENT_DYNAMIC(CDlgMain, CPropertyPage)
CDlgMain::CDlgMain(LOGFONT logfont)
	: CPropertyPage(CDlgMain::IDD)
	, m_pFont( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CDlgMain::~CDlgMain()
{
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMain, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_PAGESEL, OnBnClickedButtonPagesel)
END_MESSAGE_MAP()


// CDlgMain message handlers
BOOL CDlgMain::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	std::string strPages[DLG_SIZE-DLG_NOTLIST] = 
	{
		"PageMain",
		"PageBasic",
		"PageCondition",
		"PageEtcFunction",
		"PageCrowList",
		"PageGateList",
		"PageEffList",
		"PageLandMarkList",
	};
	SetWin_Combo_Init( this, IDC_COMBO_PAGES, strPages, DLG_SIZE-DLG_NOTLIST );
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgMain::OnBnClickedButtonPagesel()
{
	int nSel = GetWin_Combo_Sel( this, IDC_COMBO_PAGES );
	if ( nSel < 0 || nSel >= DLG_SIZE )	return;
	m_pToolTab->ActiveDlgPage( nSel );
}
