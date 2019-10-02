// XEffDust.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffDust.h"
#include ".\xeffdust.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffDust dialog

IMPLEMENT_DYNAMIC(CEffDust, CPropertyPage)
CEffDust::CEffDust(LOGFONT logfont)
	: CPropertyPage(CEffDust::IDD)
	,m_pFont( NULL )
	,EffDustEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffDustEdit = new DxEffCharDust;
}

CEffDust::~CEffDust()
{
}

void CEffDust::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffDust, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffDust message handlers
BOOL CEffDust::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffDust::SetEffDust ( DxEffCharDust*	EffDustX)
{ 
	EffDustEdit = EffDustX; 
	Update();
}

void CEffDust::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffDustReturn( EffDustEdit );
	}
}

void CEffDust::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffDust::Update()
{
	EFFCHAR_PROPERTY_DUST EffEdit = *((EFFCHAR_PROPERTY_DUST*)EffDustEdit->GetProperty() );

	SetWin_Num_int ( this, IDC_EDIT_FLAG,  EffEdit.m_dwFlag );
	SetWin_Text ( this, IDC_EDIT_TEX, EffEdit.m_szTexture );
	return TRUE;
}

BOOL CEffDust::Save()
{
	EFFCHAR_PROPERTY_DUST* EffEdit = new EFFCHAR_PROPERTY_DUST;

	EffEdit->m_dwFlag = GetWin_Num_int ( this, IDC_EDIT_FLAG );
	StringCchCopy( EffEdit->m_szTexture, MAX_PATH, GetWin_Text( this, IDC_EDIT_TEX ).GetString() );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffDustEdit->SetProperty(EffEditProp);

	return TRUE;
}
