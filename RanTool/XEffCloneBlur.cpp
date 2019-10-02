// XEffCloneBlur.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffCloneBlur.h"
#include ".\xeffcloneblur.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffCloneBlur dialog

IMPLEMENT_DYNAMIC(CEffCloneBlur, CPropertyPage)
CEffCloneBlur::CEffCloneBlur(LOGFONT logfont)
	: CPropertyPage(CEffCloneBlur::IDD)
	,m_pFont( NULL )
	,EffCloneBlurEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffCloneBlurEdit = new DxEffCharCloneBlur;
}

CEffCloneBlur::~CEffCloneBlur()
{
}

void CEffCloneBlur::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffCloneBlur, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffCloneBlur message handlers

BOOL CEffCloneBlur::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffCloneBlur::SetEffCloneBlur ( DxEffCharCloneBlur*	EffCloneBlurX)
{ 
	EffCloneBlurEdit = EffCloneBlurX; 
	Update();
}

void CEffCloneBlur::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffCloneBlurReturn( EffCloneBlurEdit );
	}
}

void CEffCloneBlur::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}


BOOL CEffCloneBlur::Update()
{
	EFFCHAR_PROPERTY_CLONEBLUR EffEdit = *((EFFCHAR_PROPERTY_CLONEBLUR*)EffCloneBlurEdit->GetProperty() );

	SetWin_Check ( this, IDC_CHECK_USE, EffEdit.m_bUse );
	SetWin_Check ( this, IDC_CHECK_BEZIER, EffEdit.m_bBezier);
	SetWin_Num_int ( this, IDC_EDIT_CBLEND,  EffEdit.m_nBlend );
	SetWin_Text ( this, IDC_EDIT_CTRACEUP, EffEdit.m_szTraceUP );
	SetWin_Text ( this, IDC_EDIT_CTRACEDN, EffEdit.m_szTraceDOWN );
	SetWin_Num_int ( this, IDC_EDIT_FACES,  EffEdit.m_dwFaces );
	SetWin_Num_float ( this, IDC_EDIT_WIDTH, EffEdit.m_fWidth );

	D3DCOLOR color = EffEdit.m_vColorUP;
	D3DCOLOR color2 = EffEdit.m_vColorDOWN;

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
	SetWin_Text ( this, IDC_EDIT_TEX, EffEdit.m_szTexture );
	return TRUE;
}

BOOL CEffCloneBlur::Save()
{
	EFFCHAR_PROPERTY_CLONEBLUR* EffEdit = new EFFCHAR_PROPERTY_CLONEBLUR;

	EffEdit->m_bUse = GetWin_Check ( this, IDC_CHECK_USE );
	EffEdit->m_bBezier= GetWin_Check ( this, IDC_CHECK_BEZIER );
	EffEdit->m_nBlend = GetWin_Num_int ( this, IDC_EDIT_CBLEND );
	StringCchCopy( EffEdit->m_szTraceUP, STRACE_NSIZE, GetWin_Text( this, IDC_EDIT_CTRACEUP ).GetString() );
	StringCchCopy( EffEdit->m_szTraceDOWN, STRACE_NSIZE, GetWin_Text( this, IDC_EDIT_CTRACEDN ).GetString() );
	EffEdit->m_dwFaces = GetWin_Num_int ( this, IDC_EDIT_FACES );
	EffEdit->m_fWidth = GetWin_Num_float( this,IDC_EDIT_WIDTH);

	BYTE a,r,g,b;
	BYTE a2,r2,g2,b2;
	a = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORUP1 );
	r = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORUP2 );
	g = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORUP3 );
	b = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORUP4 );
	EffEdit->m_vColorUP = D3DCOLOR_ARGB(a,r,g,b);
	a2 = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORDN1 );
	r2 = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORDN2 );
	g2 = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORDN3 );
	b2 = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_VCOLORDN4 );
	EffEdit->m_vColorDOWN = D3DCOLOR_ARGB(a2,r2,g2,b2);

	StringCchCopy( EffEdit->m_szTexture, MAX_PATH, GetWin_Text( this, IDC_EDIT_TEX ).GetString() );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffCloneBlurEdit->SetProperty(EffEditProp);

	return TRUE;
}