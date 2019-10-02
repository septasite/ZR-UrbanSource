// XEffBlur.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffBlur.h"
#include ".\xeffblur.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include "DummyData.h"
#include "DxAniKeys.h"



// CEffBlur dialog

IMPLEMENT_DYNAMIC(CEffBlur, CPropertyPage)
CEffBlur::CEffBlur(LOGFONT logfont)
	: CPropertyPage(CEffBlur::IDD)
	,m_pFont( NULL )
	,EffBlurEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffBlurEdit = new DxEffCharBlur;
}

CEffBlur::~CEffBlur()
{
}

void CEffBlur::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffBlur, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffBlur message handlers
BOOL CEffBlur::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	SetWin_Combo_Init ( this, IDC_COMBO_ANIM_M, DUMMYDATA::m_AniMain, AN_TYPE_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_ANIM_S, DUMMYDATA::m_AniSub, AN_SUB_00_SIZE );

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffBlur::SetEffBlur ( DxEffCharBlur*	EffBlurX)
{ 
	EffBlurEdit = EffBlurX; 
	Update();
}

void CEffBlur::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffBlurReturn( EffBlurEdit );
	}
}

void CEffBlur::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffBlur::Update()
{
	EFFCHAR_PROPERTY_BLUR EffEdit = *((EFFCHAR_PROPERTY_BLUR*)EffBlurEdit->GetProperty() );

	SetWin_Check ( this, IDC_CHECK_NOUSEORIGIN, EffEdit.m_dwFlag&NOUSEORIGIN );
	SetWin_Check ( this, IDC_CHECK_USEREFRACT, EffEdit.m_dwFlag&USEREFRACT );
	SetWin_Check ( this, IDC_CHECK_NOUSEBEZIER, EffEdit.m_dwFlag&NOUSE_BEZIER );
	SetWin_Check ( this, IDC_CHECK_NOUSEMIDDLE, EffEdit.m_dwFlag&NOUSE_MIDDLE );
	SetWin_Check ( this, IDC_CHECK_USEALLACTION, EffEdit.m_dwFlag&USEALLACTION );
	SetWin_Num_int ( this, IDC_EDIT_BLEND,  EffEdit.m_nBlend );
	SetWin_Num_float ( this, IDC_EDIT_FULLLIFE, EffEdit.m_fFullLifeTemp );

	D3DCOLOR color = EffEdit.m_vColorUPTemp;
	D3DCOLOR color2 = EffEdit.m_vColorDOWNTemp;

	DWORD a = color >> 24;
	DWORD r = (color >> 16) & 0xFF;
	DWORD g = (color >> 8 ) & 0xFF;
	DWORD b = color & 0xFF;

	DWORD a2 = color2 >> 24;
	DWORD r2 = (color2 >> 16) & 0xFF;
	DWORD g2 = (color2 >> 8 ) & 0xFF;
	DWORD b2 = color2 & 0xFF;

	SetWin_Num_int ( this, IDC_EDIT_VCOLORUP1,  a );
	SetWin_Num_int ( this, IDC_EDIT_VCOLORUP2,  r );
	SetWin_Num_int ( this, IDC_EDIT_VCOLORUP3,  g );
	SetWin_Num_int ( this, IDC_EDIT_VCOLORUP4,  b );
	SetWin_Num_int ( this, IDC_EDIT_VCOLORDN1,  a2 );
	SetWin_Num_int ( this, IDC_EDIT_VCOLORDN2,  r2 );
	SetWin_Num_int ( this, IDC_EDIT_VCOLORDN3,  g2 );
	SetWin_Num_int ( this, IDC_EDIT_VCOLORDN4,  b2 );
	SetWin_Combo_Sel ( this, IDC_COMBO_ANIM_M, (int)EffEdit.m_SetAniMType );
	SetWin_Combo_Sel ( this, IDC_COMBO_ANIM_S, (int)EffEdit.m_SetAniSType );
	SetWin_Text ( this, IDC_EDIT_TEX, EffEdit.m_szTexture );
	SetWin_Text ( this, IDC_EDIT_TRACEUP, EffEdit.m_szTraceUP );
	SetWin_Text ( this, IDC_EDIT_TRACEDN, EffEdit.m_szTraceDOWN );

	return TRUE;
}

BOOL CEffBlur::Save()
{
	EFFCHAR_PROPERTY_BLUR* EffEdit = new EFFCHAR_PROPERTY_BLUR;

	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NOUSEORIGIN ), EffEdit->m_dwFlag,NOUSEORIGIN );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_USEREFRACT ), EffEdit->m_dwFlag,USEREFRACT );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NOUSEBEZIER ), EffEdit->m_dwFlag,NOUSE_BEZIER );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NOUSEMIDDLE ), EffEdit->m_dwFlag,NOUSE_MIDDLE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_USEALLACTION ), EffEdit->m_dwFlag,USEALLACTION );
	EffEdit->m_nBlend = GetWin_Num_int ( this, IDC_EDIT_BLEND );
	EffEdit->m_fFullLifeTemp = GetWin_Num_float( this,IDC_EDIT_FULLLIFE);

	BYTE a,r,g,b;
	BYTE a2,r2,g2,b2;
	a = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORUP1 );
	r = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORUP2 );
	g = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORUP3 );
	b = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORUP4 );
	EffEdit->m_vColorUPTemp = D3DCOLOR_ARGB(a,r,g,b);
	a2 = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORDN1 );
	r2 = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORDN2 );
	g2 = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORDN3 );
	b2 = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORDN4 );
	EffEdit->m_vColorDOWNTemp = D3DCOLOR_ARGB(a2,r2,g2,b2);

	EffEdit->m_SetAniMType = ( EMANI_MAINTYPE )GetWin_Combo_Sel ( this, IDC_COMBO_ANIM_M );
	EffEdit->m_SetAniSType = ( EMANI_SUBTYPE )GetWin_Combo_Sel ( this, IDC_COMBO_ANIM_S );
	StringCchCopy( EffEdit->m_szTexture, TEXTURE_LENGTH, GetWin_Text( this, IDC_EDIT_TEX ).GetString() );
	StringCchCopy( EffEdit->m_szTraceUP, STRACE_NSIZE, GetWin_Text( this, IDC_EDIT_TRACEUP ).GetString() );
	StringCchCopy( EffEdit->m_szTraceDOWN, STRACE_NSIZE, GetWin_Text( this, IDC_EDIT_TRACEDN ).GetString() );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffBlurEdit->SetProperty(EffEditProp);

	return TRUE;
}