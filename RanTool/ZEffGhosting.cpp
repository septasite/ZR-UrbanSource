// ZEffGhosting.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "ZEffGhosting.h"
#include "ZEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// AEffGhosting dialog

IMPLEMENT_DYNAMIC(AEffGhosting, CPropertyPage)
AEffGhosting::AEffGhosting(LOGFONT logfont)
	: CPropertyPage(AEffGhosting::IDD)
	,m_pFont( NULL )
	,EffGhostingEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffGhostingEdit = new DxEffAniData_Ghosting;
}

AEffGhosting::~AEffGhosting()
{
}

void AEffGhosting::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AEffGhosting, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// AEffGhosting message handlers
BOOL AEffGhosting::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void AEffGhosting::SetEffGhosting( DxEffAniData_Ghosting*	EffGhostingX )
{ 
	EffGhostingEdit = EffGhostingX ; 
	Update();
}

BOOL AEffGhosting::Update()
{
	SetWin_Num_int ( this, IDC_EDIT_FLAGS,  EffGhostingEdit->m_dwFlags );
	SetWin_Num_int ( this, IDC_EDIT_FRAME1,  EffGhostingEdit->m_dwFrame_1);
	SetWin_Num_int ( this, IDC_EDIT_FRAME2,  EffGhostingEdit->m_dwFrame_2);
	SetWin_Num_int ( this, IDC_EDIT_GNUM,  EffGhostingEdit->m_dwGhostingNum);
	SetWin_Num_int ( this, IDC_EDIT_AMAX,  EffGhostingEdit->m_dwAlphaMax);
	SetWin_Num_int ( this, IDC_EDIT_UNIT,  EffGhostingEdit->m_dwUnit);

	D3DCOLOR color = EffGhostingEdit->m_dwColor;

	DWORD a = color >> 24;
	DWORD r = (color >> 16) & 0xFF;
	DWORD g = (color >> 8 ) & 0xFF;
	DWORD b = color & 0xFF;

	SetWin_Num_int ( this, IDC_EDIT_DCOLOR1,  a );
	SetWin_Num_int ( this, IDC_EDIT_DCOLOR2,  r );
	SetWin_Num_int ( this, IDC_EDIT_DCOLOR3,  g );
	SetWin_Num_int ( this, IDC_EDIT_DCOLOR4,  b );

	return TRUE;
}

BOOL AEffGhosting::Save()
{

	EffGhostingEdit->m_dwFlags = GetWin_Num_int ( this, IDC_EDIT_FLAGS );
	EffGhostingEdit->m_dwFrame_1 = GetWin_Num_int ( this, IDC_EDIT_FRAME1 );
	EffGhostingEdit->m_dwFrame_2 = GetWin_Num_int ( this, IDC_EDIT_FRAME2 );
	EffGhostingEdit->m_dwGhostingNum = GetWin_Num_int ( this, IDC_EDIT_GNUM );
	EffGhostingEdit->m_dwAlphaMax = GetWin_Num_int ( this, IDC_EDIT_AMAX );
	EffGhostingEdit->m_dwUnit = GetWin_Num_int ( this, IDC_EDIT_UNIT );

	BYTE a,r,g,b;
	a = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DCOLOR1 );
	r = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DCOLOR2 );
	g = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DCOLOR3 );
	b = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DCOLOR4 );
	EffGhostingEdit->m_dwColor = D3DCOLOR_ARGB(a,r,g,b);

	return TRUE;
}
void AEffGhosting::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffGhostingReturn( EffGhostingEdit );
	}
}

void AEffGhosting::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}
