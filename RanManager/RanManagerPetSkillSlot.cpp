// RanManagerPetSkillSlot.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerPetSkillSlot.h"
#include "RanManagerPetTab.h"
#include "RanManagerComments.h"

#include "EtcFunction.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "CharSearch.h"
#include "s_NetGlobal.h"


// CRanManagerPetSkillSlot dialog

IMPLEMENT_DYNAMIC(CRanManagerPetSkillSlot, CPropertyPage)
CRanManagerPetSkillSlot::CRanManagerPetSkillSlot(LOGFONT logfont)
	: CPropertyPage(CRanManagerPetSkillSlot::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerPetSkillSlot::~CRanManagerPetSkillSlot()
{
}

void CRanManagerPetSkillSlot::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRanManagerPetSkillSlot, CPropertyPage)
END_MESSAGE_MAP()


// CRanManagerPetSkillSlot message handlers
BOOL CRanManagerPetSkillSlot::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void	CRanManagerPetSkillSlot::SetPet(int nPetNum)
{
}