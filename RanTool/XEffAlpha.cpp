// XEffAlpha.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffAlpha.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffAlpha dialog

IMPLEMENT_DYNAMIC(CEffAlpha, CPropertyPage)
CEffAlpha::CEffAlpha(LOGFONT logfont)
	: CPropertyPage(CEffAlpha::IDD)
	,m_pFont( NULL )
	,EffAlphaEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffAlphaEdit = new DxEffCharAlpha;
}

CEffAlpha::~CEffAlpha()
{
}

void CEffAlpha::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffAlpha, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffAlpha message handlers
BOOL CEffAlpha::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffAlpha::SetEffAlpha ( DxEffCharAlpha*	EffAlphaX)
{ 
	EffAlphaEdit = EffAlphaX; 
	Update();
}

void CEffAlpha::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffAlphaReturn( EffAlphaEdit );
	}
}

void CEffAlpha::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffAlpha::Update()
{
	EFFCHAR_PROPERTY_ALPHA EffEdit = *((EFFCHAR_PROPERTY_ALPHA*)EffAlphaEdit->GetProperty() );
	SetWin_Check ( this, IDC_CHECK_AFLAG, EffEdit.m_dwFlags&USETRANSLUCENT );
	SetWin_Num_float ( this, IDC_EDIT_AWTIME, EffEdit.m_fWaitTime );
	SetWin_Num_float ( this, IDC_EDIT_APTIME, EffEdit.m_fPlayTime );
	SetWin_Num_float ( this, IDC_EDIT_AHEIGHT, EffEdit.m_fHeight );
	SetWin_Num_float ( this, IDC_EDIT_AALPHA, EffEdit.m_fAlpha );

	return TRUE;
}

BOOL CEffAlpha::Save()
{
	EFFCHAR_PROPERTY_ALPHA* EffEdit = new EFFCHAR_PROPERTY_ALPHA;
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG ), EffEdit->m_dwFlags,USETRANSLUCENT );
	EffEdit->m_fWaitTime = GetWin_Num_float ( this, IDC_EDIT_AWTIME );
	EffEdit->m_fPlayTime = GetWin_Num_float ( this, IDC_EDIT_APTIME );
	EffEdit->m_fHeight = GetWin_Num_float ( this, IDC_EDIT_AHEIGHT );
	EffEdit->m_fAlpha = GetWin_Num_float ( this, IDC_EDIT_AALPHA );
	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffAlphaEdit->SetProperty(EffEditProp);

	return TRUE;
}

