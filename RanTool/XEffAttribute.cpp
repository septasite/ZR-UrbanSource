// XEffAttribute.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffAttribute.h"
#include ".\xeffattribute.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffAttribute dialog

IMPLEMENT_DYNAMIC(CEffAttribute, CPropertyPage)
CEffAttribute::CEffAttribute(LOGFONT logfont)
	: CPropertyPage(CEffAttribute::IDD)
	,m_pFont( NULL )
	,EffAttributeEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffAttributeEdit = new DxEffCharAttribute;
}

CEffAttribute::~CEffAttribute()
{
}

void CEffAttribute::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffAttribute, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffAttribute message handlers
BOOL CEffAttribute::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffAttribute::SetEffAttribute ( DxEffCharAttribute*	EffAttributeX)
{ 
	EffAttributeEdit = EffAttributeX; 
	Update();
}

void CEffAttribute::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffAttributeReturn( EffAttributeEdit );
	}
}

void CEffAttribute::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffAttribute::Update()
{
	EFFCHAR_PROPERTY_ATTRIBUTE EffEdit = *((EFFCHAR_PROPERTY_ATTRIBUTE*)EffAttributeEdit->GetProperty() );

	SetWin_Check ( this, IDC_CHECK_BUSE,  EffEdit.m_bUse );
	SetWin_Num_int ( this, IDC_EDIT_FLAG,  EffEdit.m_dwFaces );
	SetWin_Num_int ( this, IDC_EDIT_ATTRI,  EffEdit.m_nAttribute );
	SetWin_Num_int ( this, IDC_EDIT_BLEND,  EffEdit.m_nBlend);
	SetWin_Text ( this, IDC_EDIT_TRACEUP,  EffEdit.m_szTraceUP);
	SetWin_Text ( this, IDC_EDIT_TRACEDN,  EffEdit.m_szTraceDOWN);
	SetWin_Num_float ( this, IDC_EDIT_LENGTH,  EffEdit.m_fLength);
	SetWin_Check ( this, IDC_CHECK_GRAVITY,  EffEdit.m_bGravity );
	SetWin_Num_float ( this, IDC_EDIT_GRAVITY,  EffEdit.m_fGravity);
	SetWin_Check ( this, IDC_CHECK_FLARE,  EffEdit.m_bFlarePos );
	SetWin_Num_float ( this, IDC_EDIT_FLARE,  EffEdit.m_fFlarePos);
	SetWin_Num_float ( this, IDC_EDIT_RAND,  EffEdit.m_fRandLength);
	SetWin_Num_float ( this, IDC_EDIT_BLUR,  EffEdit.m_fBlurRate);
	SetWin_Num_int ( this, IDC_EDIT_DFACES,  EffEdit.m_dwFaces);
	SetWin_Text ( this, IDC_EDIT_TEX,  EffEdit.m_szTexture);

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


	return TRUE;
}

BOOL CEffAttribute::Save()
{
	EFFCHAR_PROPERTY_ATTRIBUTE* EffEdit = new EFFCHAR_PROPERTY_ATTRIBUTE;

	EffEdit->m_bUse = GetWin_Check ( this, IDC_CHECK_BUSE );
	EffEdit->m_dwFlag = GetWin_Num_int ( this, IDC_EDIT_FLAG );
	EffEdit->m_nAttribute = GetWin_Num_int ( this, IDC_EDIT_ATTRI );
	EffEdit->m_nBlend = GetWin_Num_int ( this, IDC_EDIT_BLEND );
	StringCchCopy( EffEdit->m_szTraceUP, STRACE_NSIZE, GetWin_Text( this, IDC_EDIT_TRACEUP ).GetString() );
	StringCchCopy( EffEdit->m_szTraceDOWN, STRACE_NSIZE, GetWin_Text( this, IDC_EDIT_TRACEDN ).GetString() );
	EffEdit->m_fLength = GetWin_Num_float ( this, IDC_EDIT_LENGTH );
	EffEdit->m_bGravity = GetWin_Check ( this, IDC_CHECK_GRAVITY );
	EffEdit->m_fGravity = GetWin_Num_float ( this, IDC_EDIT_GRAVITY );
	EffEdit->m_bFlarePos = GetWin_Check ( this, IDC_CHECK_FLARE );
	EffEdit->m_fFlarePos = GetWin_Num_float ( this, IDC_EDIT_FLARE );
	EffEdit->m_fRandLength = GetWin_Num_float ( this, IDC_EDIT_RAND );
	EffEdit->m_fBlurRate = GetWin_Num_float ( this, IDC_EDIT_BLUR );
	EffEdit->m_dwFaces = GetWin_Num_int ( this, IDC_EDIT_DFACES );
	StringCchCopy( EffEdit->m_szTexture, MAX_PATH, GetWin_Text( this, IDC_EDIT_TEX ).GetString() );

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

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffAttributeEdit->SetProperty(EffEditProp);

	return TRUE;
}
