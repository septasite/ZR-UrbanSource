// XEffGhosting.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffGhosting.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include "DummyData.h"


// CEffGhosting dialog

IMPLEMENT_DYNAMIC(CEffGhosting, CPropertyPage)
CEffGhosting::CEffGhosting(LOGFONT logfont)
	: CPropertyPage(CEffGhosting::IDD)
	,m_pFont( NULL )
	,EffGhostingEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffGhostingEdit = new DxEffCharGhosting;
}

CEffGhosting::~CEffGhosting()
{
}

void CEffGhosting::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffGhosting, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffGhosting message handlers
BOOL CEffGhosting::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	SetWin_Combo_Init ( this, IDC_COMBO_ANIM_M, DUMMYDATA::m_AniMain, AN_TYPE_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_ANIM_S, DUMMYDATA::m_AniSub, AN_SUB_00_SIZE );

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffGhosting::SetEffGhosting ( DxEffCharGhosting*	EffGhostingX)
{ 
	EffGhostingEdit = EffGhostingX; 
	Update();
}

void CEffGhosting::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffGhostingReturn( EffGhostingEdit );
	}
}

void CEffGhosting::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffGhosting::Update()
{
	EFFCHAR_PROPERTY_GHOSTING EffEdit = *((EFFCHAR_PROPERTY_GHOSTING*)EffGhostingEdit->GetProperty() );

	SetWin_Num_int ( this, IDC_EDIT_GFLAG,  EffEdit.m_dwFlag );
	SetWin_Num_int ( this, IDC_EDIT_GNUM,  EffEdit.m_dwGhostingNum );
	SetWin_Num_int ( this, IDC_EDIT_AMAX,  EffEdit.m_dwAlphaMax );
	SetWin_Num_int ( this, IDC_EDIT_UNIT,  EffEdit.m_dwUnit);
	SetWin_Combo_Sel ( this, IDC_COMBO_ANIM_M, (int)EffEdit.m_AniMType );
	SetWin_Combo_Sel ( this, IDC_COMBO_ANIM_S, (int)EffEdit.m_AniSType );

	D3DCOLOR color = EffEdit.m_dwColor;
	DWORD a = color >> 24;
	DWORD r = (color >> 16) & 0xFF;
	DWORD g = (color >> 8 ) & 0xFF;
	DWORD b = color & 0xFF;

	SetWin_Num_int ( this, IDC_EDIT_GCOL1,  a );
	SetWin_Num_int ( this, IDC_EDIT_GCOL2,  r );
	SetWin_Num_int ( this, IDC_EDIT_GCOL3,  g );
	SetWin_Num_int ( this, IDC_EDIT_GCOL4,  b );

	return TRUE;
}

BOOL CEffGhosting::Save()
{
	EFFCHAR_PROPERTY_GHOSTING* EffEdit = new EFFCHAR_PROPERTY_GHOSTING;

	EffEdit->m_dwFlag = GetWin_Num_int ( this, IDC_EDIT_GFLAG );
	EffEdit->m_dwGhostingNum = GetWin_Num_int ( this, IDC_EDIT_GNUM );
	EffEdit->m_dwAlphaMax = GetWin_Num_int ( this, IDC_EDIT_AMAX );
	EffEdit->m_dwUnit = GetWin_Num_int ( this, IDC_EDIT_UNIT );
	EffEdit->m_AniMType = ( EMANI_MAINTYPE )GetWin_Combo_Sel ( this, IDC_COMBO_ANIM_M );
	EffEdit->m_AniSType = ( EMANI_SUBTYPE )GetWin_Combo_Sel ( this, IDC_COMBO_ANIM_S );

	BYTE a,r,g,b;
	a = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_GCOL1 );
	r = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_GCOL2 );
	g = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_GCOL3 );
	b = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_GCOL4 );
	EffEdit->m_dwColor = D3DCOLOR_ARGB(a,r,g,b);

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffGhostingEdit->SetProperty(EffEditProp);

	return TRUE;
}

