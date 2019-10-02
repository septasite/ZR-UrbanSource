// RanManagerPetSkill.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerPetSkill.h"
#include "RanManagerPetTab.h"
#include "RanManagerComments.h"

#include "EtcFunction.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "CharSearch.h"
#include "s_NetGlobal.h"


// CRanManagerPetSkill dialog

IMPLEMENT_DYNAMIC(CRanManagerPetSkill, CPropertyPage)
CRanManagerPetSkill::CRanManagerPetSkill(LOGFONT logfont)
	: CPropertyPage(CRanManagerPetSkill::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerPetSkill::~CRanManagerPetSkill()
{
}

void CRanManagerPetSkill::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRanManagerPetSkill, CPropertyPage)
END_MESSAGE_MAP()


// CRanManagerPetSkill message handlers
BOOL CRanManagerPetSkill::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void	CRanManagerPetSkill::SetPet(int nPetNum)
{
}