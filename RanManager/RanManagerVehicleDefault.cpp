// RanManagerVehicleDefault.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerVehicleDefault.h"
#include "RanManagerVehicleTab.h"
#include "RanManagerComments.h"

#include "EtcFunction.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "CharSearch.h"
#include "s_NetGlobal.h"

// CRanManagerVehicleDefault dialog

IMPLEMENT_DYNAMIC(CRanManagerVehicleDefault, CPropertyPage)
CRanManagerVehicleDefault::CRanManagerVehicleDefault(LOGFONT logfont)
	: CPropertyPage(CRanManagerVehicleDefault::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerVehicleDefault::~CRanManagerVehicleDefault()
{
}

void CRanManagerVehicleDefault::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRanManagerVehicleDefault, CPropertyPage)
END_MESSAGE_MAP()


// CRanManagerVehicleDefault message handlers
BOOL CRanManagerVehicleDefault::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void	CRanManagerVehicleDefault::SetVehicle(int nVehicleNum)
{
}