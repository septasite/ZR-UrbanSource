// RanManagerPetDefault.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerPetDefault.h"
#include "RanManagerPetTab.h"
#include "RanManagerComments.h"

#include "EtcFunction.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "CharSearch.h"
#include "s_NetGlobal.h"

// CRanManagerPetDefault dialog

IMPLEMENT_DYNAMIC(CRanManagerPetDefault, CPropertyPage)
CRanManagerPetDefault::CRanManagerPetDefault(LOGFONT logfont)
	: CPropertyPage(CRanManagerPetDefault::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerPetDefault::~CRanManagerPetDefault()
{
}

void CRanManagerPetDefault::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRanManagerPetDefault, CPropertyPage)
END_MESSAGE_MAP()


// CRanManagerPetDefault message handlers
BOOL CRanManagerPetDefault::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void	CRanManagerPetDefault::SetPet(int nPetNum)
{
}