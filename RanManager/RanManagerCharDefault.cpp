// RanManagerCharDefault.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerCharDefault.h"


// CRanManagerCharDefault dialog

IMPLEMENT_DYNAMIC(CRanManagerCharDefault, CPropertyPage)
CRanManagerCharDefault::CRanManagerCharDefault(LOGFONT logfont)
	: CPropertyPage(CRanManagerCharDefault::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerCharDefault::~CRanManagerCharDefault()
{
}

void CRanManagerCharDefault::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRanManagerCharDefault, CPropertyPage)
END_MESSAGE_MAP()


// CRanManagerCharDefault message handlers
BOOL CRanManagerCharDefault::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control	
}
