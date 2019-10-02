// XEffToon.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffToon.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffToon dialog

IMPLEMENT_DYNAMIC(CEffToon, CPropertyPage)
CEffToon::CEffToon(LOGFONT logfont)
	: CPropertyPage(CEffToon::IDD)
	,m_pFont( NULL )
	,EffToonEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffToonEdit =  new DxEffCharToon;
}

CEffToon::~CEffToon()
{
}

void CEffToon::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffToon, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffToon message handlers
BOOL CEffToon::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffToon::SetEffToon ( DxEffCharToon*	EffToonX)
{ 
	EffToonEdit = EffToonX; 
	Update();
}

void CEffToon::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffToonReturn( EffToonEdit );
	}
}

void CEffToon::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffToon::Update()
{
	EFFCHAR_PROPERTY_TOON EffEdit = *((EFFCHAR_PROPERTY_TOON*)EffToonEdit->GetProperty() );
	SetWin_Check ( this, IDC_CHECK_TFLAG1, EffEdit.m_dwFlag&USE_OBLIQUE );
	SetWin_Num_float ( this, IDC_EDIT_TSIZE,  EffEdit.m_fSize );
	SetWin_Num_float ( this, IDC_EDIT_TSIZEADD,  EffEdit.m_fSizeADD );
	SetWin_Text ( this, IDC_EDIT_TTEX, EffEdit.m_szToonTex );
	SetWin_Text ( this, IDC_EDIT_OTEX, EffEdit.m_szObliqueTex );
	return TRUE;
}

BOOL CEffToon::Save()
{
	EFFCHAR_PROPERTY_TOON* EffEdit = new EFFCHAR_PROPERTY_TOON;
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_TFLAG1 ), EffEdit->m_dwFlag,USE_OBLIQUE );
	EffEdit->m_fSize = GetWin_Num_float ( this, IDC_EDIT_TSIZE );
	EffEdit->m_fSizeADD = GetWin_Num_float ( this, IDC_EDIT_TSIZEADD );
	StringCchCopy( EffEdit->m_szToonTex, MAX_PATH, GetWin_Text( this, IDC_EDIT_TTEX ).GetString() );
	StringCchCopy( EffEdit->m_szObliqueTex, MAX_PATH, GetWin_Text( this, IDC_EDIT_OTEX ).GetString() );
	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffToonEdit->SetProperty(EffEditProp);

	return TRUE;
}
