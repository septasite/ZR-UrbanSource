// XEffNormalMap.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffNormalMap.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffNormalMap dialog

IMPLEMENT_DYNAMIC(CEffNormalMap, CPropertyPage)
CEffNormalMap::CEffNormalMap(LOGFONT logfont)
	: CPropertyPage(CEffNormalMap::IDD)
	,m_pFont( NULL )
	,EffNormalEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffNormalEdit = new DxEffCharNormal;
}

CEffNormalMap::~CEffNormalMap()
{
}

void CEffNormalMap::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffNormalMap, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffNormalMap message handlers
BOOL CEffNormalMap::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffNormalMap::SetEffNormal ( DxEffCharNormal*	EffNormalX )
{ 
	EffNormalEdit = EffNormalX; 
	Update();
}

void CEffNormalMap::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffNormalReturn( EffNormalEdit );
	}
}

void CEffNormalMap::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffNormalMap::Update()
{
	EFFCHAR_PROPERTY_NORMAL EffEdit = *((EFFCHAR_PROPERTY_NORMAL*)EffNormalEdit->GetProperty() );
	SetWin_Num_int ( this, IDC_EDIT_NFLAG,  EffEdit.m_dwFlags );

	return TRUE;
}

BOOL CEffNormalMap::Save()
{
	EFFCHAR_PROPERTY_NORMAL* EffEdit = new EFFCHAR_PROPERTY_NORMAL;
	EffEdit->m_dwFlags = GetWin_Num_int ( this, IDC_EDIT_NFLAG );	

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffNormalEdit->SetProperty(EffEditProp);

	return TRUE;
}