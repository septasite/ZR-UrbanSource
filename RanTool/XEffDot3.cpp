// XEffDot3.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffDot3.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include "DummyData.h"
#include ".\xeffdot3.h"


// CEffDot3 dialog

IMPLEMENT_DYNAMIC(CEffDot3, CPropertyPage)
CEffDot3::CEffDot3(LOGFONT logfont)
	: CPropertyPage(CEffDot3::IDD)
	,m_pFont( NULL )
	,EffDot3Edit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffDot3Edit =  new DxEffCharDot3;
}

CEffDot3::~CEffDot3()
{
}

void CEffDot3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffDot3, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_COLOP, OnCbnSelchangeComboColop)
END_MESSAGE_MAP()


// CEffDot3 message handlers
BOOL CEffDot3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	SetWin_Combo_Init ( this, IDC_COMBO_D3OP1, DUMMYDATA::m_CRDT_Type, DCRDT_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_D3OP2, DUMMYDATA::m_CRDT_Type, DCRDT_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_D3OP3, DUMMYDATA::m_CRDT_Type, DCRDT_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_COLOP, DUMMYDATA::m_DColorOp, XD3DTOP_SIZE );

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffDot3::SetEffDot3 ( DxEffCharDot3*	EffDot3X)
{ 
	EffDot3Edit = EffDot3X; 
	Update();
}

void CEffDot3::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffDot3Return( EffDot3Edit );
	}
}

void CEffDot3::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffDot3::Update()
{
	EFFCHAR_PROPERTY_DOT3 EffEdit = *((EFFCHAR_PROPERTY_DOT3*)EffDot3Edit->GetProperty() );

	SetWin_Check ( this, IDC_CHECK_D3FLAG1, EffEdit.m_dwFlag&ISTEXTURE1 );
	SetWin_Check ( this, IDC_CHECK_D3FLAG2, EffEdit.m_dwFlag&ISTEXTURE2 );
	SetWin_Check ( this, IDC_CHECK_D3FLAG3, EffEdit.m_dwFlag&ISTEXTURE3 );
	SetWin_Check ( this, IDC_CHECK_D3FLAG4, EffEdit.m_dwFlag&USETEXTURE1 );
	SetWin_Check ( this, IDC_CHECK_D3FLAG5, EffEdit.m_dwFlag&USETEXTURE2 );
	SetWin_Check ( this, IDC_CHECK_D3FLAG6, EffEdit.m_dwFlag&USETEXTURE3 );
	SetWin_Num_int ( this, IDC_EDIT_COLOROP,  EffEdit.m_dwColorOP );
	SetWin_Combo_Sel ( this, IDC_COMBO_D3OP1, EffEdit.m_dwDetail_1 );
	SetWin_Combo_Sel ( this, IDC_COMBO_D3OP2, EffEdit.m_dwDetail_2 );
	SetWin_Combo_Sel ( this, IDC_COMBO_D3OP3, EffEdit.m_dwDetail_3 );
	SetWin_Text ( this, IDC_EDIT_TEXTURE,  EffEdit.m_szTexture );
	SetWin_Text ( this, IDC_EDIT_SRCTEX1,  EffEdit.m_szSrcTex_1 );
	SetWin_Text ( this, IDC_EDIT_SRCTEX2,  EffEdit.m_szSrcTex_2 );
	SetWin_Text ( this, IDC_EDIT_SRCTEX3,  EffEdit.m_szSrcTex_3 );
	SetWin_Text ( this, IDC_EDIT_D3TEX1,  EffEdit.m_szTexture_1 );
	SetWin_Text ( this, IDC_EDIT_D3TEX2,  EffEdit.m_szTexture_2 );
	SetWin_Text ( this, IDC_EDIT_D3TEX3,  EffEdit.m_szTexture_3 );
	SetWin_Text ( this, IDC_EDIT_DOTEX1,  EffEdit.m_szDot3Tex_1 );
	SetWin_Text ( this, IDC_EDIT_DOTEX2,  EffEdit.m_szDot3Tex_2 );
	SetWin_Text ( this, IDC_EDIT_DOTEX3,  EffEdit.m_szDot3Tex_3 );
	SetWin_Combo_Sel ( this, IDC_COMBO_COLOP, (int)EffEdit.m_dwColorOP );
	return TRUE;
}

BOOL CEffDot3::Save()
{
	EFFCHAR_PROPERTY_DOT3* EffEdit = new EFFCHAR_PROPERTY_DOT3;
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_D3FLAG1 ), EffEdit->m_dwFlag,ISTEXTURE1 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_D3FLAG2 ), EffEdit->m_dwFlag,ISTEXTURE2 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_D3FLAG3 ), EffEdit->m_dwFlag,ISTEXTURE3 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_D3FLAG4 ), EffEdit->m_dwFlag,USETEXTURE1 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_D3FLAG5 ), EffEdit->m_dwFlag,USETEXTURE2 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_D3FLAG6 ), EffEdit->m_dwFlag,USETEXTURE3 );
	EffEdit->m_dwColorOP = GetWin_Num_int ( this, IDC_EDIT_COLOROP );
	EffEdit->m_dwDetail_1 = (CRDT_TYPE) GetWin_Combo_Sel ( this, IDC_COMBO_D3OP1 );
	EffEdit->m_dwDetail_2 = (CRDT_TYPE) GetWin_Combo_Sel ( this, IDC_COMBO_D3OP2 );
	EffEdit->m_dwDetail_3 = (CRDT_TYPE) GetWin_Combo_Sel ( this, IDC_COMBO_D3OP3 );
	StringCchCopy( EffEdit->m_szTexture, MAX_PATH, GetWin_Text( this, IDC_EDIT_TEXTURE ).GetString() );
	StringCchCopy( EffEdit->m_szSrcTex_1, MAX_PATH, GetWin_Text( this, IDC_EDIT_SRCTEX1 ).GetString() );
	StringCchCopy( EffEdit->m_szSrcTex_2, MAX_PATH, GetWin_Text( this, IDC_EDIT_SRCTEX2 ).GetString() );
	StringCchCopy( EffEdit->m_szSrcTex_3, MAX_PATH, GetWin_Text( this, IDC_EDIT_SRCTEX3 ).GetString() );
	StringCchCopy( EffEdit->m_szTexture_1, MAX_PATH, GetWin_Text( this, IDC_EDIT_D3TEX1 ).GetString() );
	StringCchCopy( EffEdit->m_szTexture_2, MAX_PATH, GetWin_Text( this, IDC_EDIT_D3TEX2 ).GetString() );
	StringCchCopy( EffEdit->m_szTexture_3, MAX_PATH, GetWin_Text( this, IDC_EDIT_D3TEX3 ).GetString() );
	StringCchCopy( EffEdit->m_szDot3Tex_1, MAX_PATH, GetWin_Text( this, IDC_EDIT_DOTEX1 ).GetString() );
	StringCchCopy( EffEdit->m_szDot3Tex_2, MAX_PATH, GetWin_Text( this, IDC_EDIT_DOTEX2 ).GetString() );
	StringCchCopy( EffEdit->m_szDot3Tex_3, MAX_PATH, GetWin_Text( this, IDC_EDIT_DOTEX3 ).GetString() );
	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffDot3Edit->SetProperty(EffEditProp);
	return TRUE;
}

void CEffDot3::OnCbnSelchangeComboColop()
{
	SetWin_Num_int ( this, IDC_EDIT_COLOROP,  (DCOLOROP) GetWin_Combo_Sel ( this, IDC_COMBO_COLOP ) );
}
