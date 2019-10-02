// RanManagerPetEdit.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerPetEdit.h"
#include "RanManagerPetTab.h"
#include "RanManagerComments.h"

#include "EtcFunction.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "CharSearch.h"
#include "s_NetGlobal.h"

// CRanManagerPetEdit dialog

IMPLEMENT_DYNAMIC(CRanManagerPetEdit, CPropertyPage)
CRanManagerPetEdit::CRanManagerPetEdit(LOGFONT logfont)
	: CPropertyPage(CRanManagerPetEdit::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerPetEdit::~CRanManagerPetEdit()
{
}

void CRanManagerPetEdit::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRanManagerPetEdit, CPropertyPage)
END_MESSAGE_MAP()


// CRanManagerPetEdit message handlers
BOOL CRanManagerPetEdit::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void	CRanManagerPetEdit::SetPet(int nPetNum)
{
}