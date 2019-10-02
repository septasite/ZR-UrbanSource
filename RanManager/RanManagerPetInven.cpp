// RanManagerPetInven.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerPetInven.h"
#include "RanManagerPetTab.h"
#include "RanManagerComments.h"

#include "EtcFunction.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "CharSearch.h"
#include "s_NetGlobal.h"


// CRanManagerPetInven dialog

IMPLEMENT_DYNAMIC(CRanManagerPetInven, CPropertyPage)
CRanManagerPetInven::CRanManagerPetInven(LOGFONT logfont)
	: CPropertyPage(CRanManagerPetInven::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerPetInven::~CRanManagerPetInven()
{
}

void CRanManagerPetInven::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRanManagerPetInven, CPropertyPage)
END_MESSAGE_MAP()


// CRanManagerPetInven message handlers
BOOL CRanManagerPetInven::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void	CRanManagerPetInven::SetPet(int nPetNum)
{
}