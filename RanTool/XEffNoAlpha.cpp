// XEffNoAlpha.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffNoAlpha.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffNoAlpha dialog

IMPLEMENT_DYNAMIC(CEffNoAlpha, CPropertyPage)
CEffNoAlpha::CEffNoAlpha(LOGFONT logfont)
	: CPropertyPage(CEffNoAlpha::IDD)
	,m_pFont( NULL )
	,EffNoAlphaEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffNoAlphaEdit =  new DxEffCharNoAlpha;
}

CEffNoAlpha::~CEffNoAlpha()
{
}

void CEffNoAlpha::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffNoAlpha, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffNoAlpha message handlers
BOOL CEffNoAlpha::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffNoAlpha::SetEffNoAlpha ( DxEffCharNoAlpha*	EffNoAlphaX)
{ 
	EffNoAlphaEdit = EffNoAlphaX; 
	Update();
}

void CEffNoAlpha::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffNoAlphaReturn( EffNoAlphaEdit );
	}
}

void CEffNoAlpha::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffNoAlpha::Update()
{
	EFFCHAR_PROPERTY_NOALPHA EffEdit = *((EFFCHAR_PROPERTY_NOALPHA*)EffNoAlphaEdit->GetProperty() );
	SetWin_Num_int(this,IDC_EDIT_FLAG,EffEdit.m_dwFlag );
	return TRUE;
}

BOOL CEffNoAlpha::Save()
{
	EFFCHAR_PROPERTY_NOALPHA* EffEdit = new EFFCHAR_PROPERTY_NOALPHA;
	EffEdit->m_dwFlag = GetWin_Num_int (this,IDC_EDIT_FLAG);
	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffNoAlphaEdit->SetProperty(EffEditProp);

	return TRUE;
}
