// XEffShock.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffShock.h"
#include ".\xeffshock.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffShock dialog

IMPLEMENT_DYNAMIC(CEffShock, CPropertyPage)
CEffShock::CEffShock(LOGFONT logfont)
	: CPropertyPage(CEffShock::IDD)
	,m_pFont( NULL )
	,EffShockEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffShockEdit =  new DxEffCharShock;
}

CEffShock::~CEffShock()
{
}

void CEffShock::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffShock, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffShock message handlers
BOOL CEffShock::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffShock::SetEffShock ( DxEffCharShock*	EffShockX)
{ 
	EffShockEdit = EffShockX; 
	Update();
}

void CEffShock::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffShockReturn( EffShockEdit );
	}
}

void CEffShock::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffShock::Update()
{
	EFFCHAR_PROPERTY_SHOCK EffEdit = *((EFFCHAR_PROPERTY_SHOCK*)EffShockEdit->GetProperty() );

	SetWin_Num_int ( this, IDC_EDIT_FLAG,  EffEdit.m_dwFlag );
	SetWin_Num_float ( this, IDC_EDIT_FULLTIME,  EffEdit.m_fFullTime );

	SetWin_Num_float ( this, IDC_EDIT_CCOLOR1,  EffEdit.m_cColor.r );
	SetWin_Num_float ( this, IDC_EDIT_CCOLOR2,  EffEdit.m_cColor.g );
	SetWin_Num_float ( this, IDC_EDIT_CCOLOR3,  EffEdit.m_cColor.b );
	SetWin_Num_float ( this, IDC_EDIT_CCOLOR4,  EffEdit.m_cColor.a );

	return TRUE;
}

BOOL CEffShock::Save()
{
	EFFCHAR_PROPERTY_SHOCK* EffEdit = new EFFCHAR_PROPERTY_SHOCK;

	EffEdit->m_dwFlag = GetWin_Num_int ( this, IDC_EDIT_FLAG );
	EffEdit->m_fFullTime = GetWin_Num_float ( this, IDC_EDIT_FULLTIME );
	EffEdit->m_cColor.r = GetWin_Num_float ( this, IDC_EDIT_CCOLOR1 );
	EffEdit->m_cColor.g = GetWin_Num_float ( this, IDC_EDIT_CCOLOR2 );
	EffEdit->m_cColor.b = GetWin_Num_float ( this, IDC_EDIT_CCOLOR3 );
	EffEdit->m_cColor.a = GetWin_Num_float ( this, IDC_EDIT_CCOLOR4 );


	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffShockEdit->SetProperty(EffEditProp);

	return TRUE;
}

