// RanManagerGuildMain.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerGuildMain.h"


// CRanManagerGuildMain dialog

IMPLEMENT_DYNAMIC(CRanManagerGuildMain, CPropertyPage)
CRanManagerGuildMain::CRanManagerGuildMain(LOGFONT logfont)
	: CPropertyPage(CRanManagerGuildMain::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerGuildMain::~CRanManagerGuildMain()
{
}

void CRanManagerGuildMain::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRanManagerGuildMain, CPropertyPage)
END_MESSAGE_MAP()


// CRanManagerGuildMain message handlers
BOOL CRanManagerGuildMain::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerGuildMain::SetGuild(int nGuildNum)
{

}
