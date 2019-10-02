// XEffSpecular.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffSpecular.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffSpecular dialog

IMPLEMENT_DYNAMIC(CEffSpecular, CPropertyPage)
CEffSpecular::CEffSpecular(LOGFONT logfont)
	: CPropertyPage(CEffSpecular::IDD)
	,m_pFont( NULL )
	,EffSpecularEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffSpecularEdit =  new DxEffCharSpecular;
}

CEffSpecular::~CEffSpecular()
{
}

void CEffSpecular::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffSpecular, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffSpecular message handlers
BOOL CEffSpecular::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffSpecular::SetEffSpecular ( DxEffCharSpecular*	EffSpecularX)
{ 
	EffSpecularEdit = EffSpecularX; 
	Update();
}

void CEffSpecular::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffSpecularReturn( EffSpecularEdit );
	}
}

void CEffSpecular::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffSpecular::Update()
{
	EFFCHAR_PROPERTY_SPECULAR EffEdit = *((EFFCHAR_PROPERTY_SPECULAR*)EffSpecularEdit->GetProperty() );

	SetWin_Check ( this, IDC_CHECK_AFLAG1, EffEdit.m_dwFlag&ISTEXTURE1 );
	SetWin_Check ( this, IDC_CHECK_AFLAG2, EffEdit.m_dwFlag&ISTEXTURE2 );
	SetWin_Check ( this, IDC_CHECK_AFLAG3, EffEdit.m_dwFlag&ISTEXTURE3 );
	SetWin_Check ( this, IDC_CHECK_AFLAG4, EffEdit.m_dwFlag&ISTEXTURE4 );
	SetWin_Check ( this, IDC_CHECK_AFLAG5, EffEdit.m_dwFlag&USETEXTURE1 );
	SetWin_Check ( this, IDC_CHECK_AFLAG6, EffEdit.m_dwFlag&USETEXTURE2 );
	SetWin_Check ( this, IDC_CHECK_AFLAG7, EffEdit.m_dwFlag&USETEXTURE3 );
	SetWin_Check ( this, IDC_CHECK_AFLAG8, EffEdit.m_dwFlag&USETEXTURE4 );
	SetWin_Text ( this, IDC_EDIT_TEX1,  EffEdit.m_szSrcTex_1 );
	SetWin_Text ( this, IDC_EDIT_TEX2,  EffEdit.m_szSrcTex_2 );
	SetWin_Text ( this, IDC_EDIT_TEX3,  EffEdit.m_szSrcTex_3 );
	SetWin_Text ( this, IDC_EDIT_TEX4,  EffEdit.m_szSrcTex_4 );

	return TRUE;
}

BOOL CEffSpecular::Save()
{
	EFFCHAR_PROPERTY_SPECULAR* EffEdit = new EFFCHAR_PROPERTY_SPECULAR;

	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG1 ), EffEdit->m_dwFlag,ISTEXTURE1 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG2 ), EffEdit->m_dwFlag,ISTEXTURE2 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG3 ), EffEdit->m_dwFlag,ISTEXTURE3 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG4 ), EffEdit->m_dwFlag,ISTEXTURE4 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG5 ), EffEdit->m_dwFlag,USETEXTURE1 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG6 ), EffEdit->m_dwFlag,USETEXTURE2 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG7 ), EffEdit->m_dwFlag,USETEXTURE3 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG8 ), EffEdit->m_dwFlag,USETEXTURE4 );
	StringCchCopy( EffEdit->m_szSrcTex_1, MAX_PATH, GetWin_Text( this, IDC_EDIT_TEX1 ).GetString() );
	StringCchCopy( EffEdit->m_szSrcTex_2, MAX_PATH, GetWin_Text( this, IDC_EDIT_TEX2 ).GetString() );
	StringCchCopy( EffEdit->m_szSrcTex_3, MAX_PATH, GetWin_Text( this, IDC_EDIT_TEX3 ).GetString() );
	StringCchCopy( EffEdit->m_szSrcTex_4, MAX_PATH, GetWin_Text( this, IDC_EDIT_TEX4 ).GetString() );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffSpecularEdit->SetProperty(EffEditProp);

	return TRUE;
}