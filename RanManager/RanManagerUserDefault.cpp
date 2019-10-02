// RanManagerUserDefault.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerUserDefault.h"


// CRanManagerUserDefault dialog

IMPLEMENT_DYNAMIC(CRanManagerUserDefault, CPropertyPage)
CRanManagerUserDefault::CRanManagerUserDefault(LOGFONT logfont)
	: CPropertyPage(CRanManagerUserDefault::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerUserDefault::~CRanManagerUserDefault()
{
}

void CRanManagerUserDefault::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRanManagerUserDefault, CPropertyPage)
END_MESSAGE_MAP()


// CRanManagerUserDefault message handlers
BOOL CRanManagerUserDefault::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control	
}
