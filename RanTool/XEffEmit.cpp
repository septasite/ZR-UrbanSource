// XEffEmit.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffEmit.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffEmit dialog

IMPLEMENT_DYNAMIC(CEffEmit, CPropertyPage)
CEffEmit::CEffEmit(LOGFONT logfont)
	: CPropertyPage(CEffEmit::IDD)
	,m_pFont( NULL )
	,EffEmitEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffEmitEdit = new DxEffCharEmit;
}

CEffEmit::~CEffEmit()
{
}

void CEffEmit::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffEmit, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffEmit message handlers
BOOL CEffEmit::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffEmit::SetEffEmit ( DxEffCharEmit*	EffEmitX)
{ 
	EffEmitEdit = EffEmitX; 
	Update();
}

void CEffEmit::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffEmitReturn( EffEmitEdit );
	}
}

void CEffEmit::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffEmit::Update()
{
	EFFCHAR_PROPERTY_EMIT EffEdit = *((EFFCHAR_PROPERTY_EMIT*)EffEmitEdit->GetProperty() );

	SetWin_Text ( this, IDC_EDIT_EMITTEX, EffEdit.m_szTexture);

	return TRUE;
}

BOOL CEffEmit::Save()
{
	EFFCHAR_PROPERTY_EMIT* EffEdit = new EFFCHAR_PROPERTY_EMIT;

	StringCchCopy( EffEdit->m_szTexture, MAX_PATH, GetWin_Text( this, IDC_EDIT_EMITTEX ).GetString() );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffEmitEdit->SetProperty(EffEditProp);

	return TRUE;
}
