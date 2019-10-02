// XEffArrow.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffArrow.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffArrow dialog

IMPLEMENT_DYNAMIC(CEffArrow, CPropertyPage)
CEffArrow::CEffArrow(LOGFONT logfont)
	: CPropertyPage(CEffArrow::IDD)
	,m_pFont( NULL )
	,EffArrowEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffArrowEdit = new DxEffCharArrow;
}

CEffArrow::~CEffArrow()
{
}

void CEffArrow::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffArrow, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffArrow message handlers
BOOL CEffArrow::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffArrow::SetEffArrow ( DxEffCharArrow*	EffArrowX)
{ 
	EffArrowEdit = EffArrowX; 
	Update();
}

void CEffArrow::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffArrowReturn( EffArrowEdit );
	}
}

void CEffArrow::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffArrow::Update()
{
	EFFCHAR_PROPERTY_ARROW EffEdit = *((EFFCHAR_PROPERTY_ARROW*)EffArrowEdit->GetProperty() );

	SetWin_Check ( this, IDC_CHECK_EFLAG1, EffEdit.m_dwFlag&USEA );
	SetWin_Check ( this, IDC_CHECK_EFLAG2, EffEdit.m_dwFlag&USEB );
	SetWin_Check ( this, IDC_CHECK_EFLAG3, EffEdit.m_dwFlag&USEC );
	SetWin_Check ( this, IDC_CHECK_EFLAG4, EffEdit.m_dwFlag&USED );
	SetWin_Check ( this, IDC_CHECK_EFLAG5, EffEdit.m_dwFlag&USESEC );
	SetWin_Check ( this, IDC_CHECK_EFLAG6, EffEdit.m_dwFlag&USESIZE );
	SetWin_Check ( this, IDC_CHECK_EFLAG7, EffEdit.m_dwFlag&USERANDROTATE );
	SetWin_Check ( this, IDC_CHECK_EFLAG8, EffEdit.m_dwFlag&USEARROW );
	SetWin_Check ( this, IDC_CHECK_EFLAG9, EffEdit.m_dwFlag&USEEFFECT );
	SetWin_Check ( this, IDC_CHECK_BUSE, EffEdit.m_bUse );
	SetWin_Num_int ( this, IDC_EDIT_BLEND,  EffEdit.m_nBlend );
	SetWin_Num_int ( this, IDC_EDIT_SEC,  EffEdit.m_nSec );
	SetWin_Num_float ( this, IDC_EDIT_SETRATE,  EffEdit.m_fSetRate );
	SetWin_Num_float ( this, IDC_EDIT_FULLTIME,  EffEdit.m_fFullTime );
	SetWin_Num_float ( this, IDC_EDIT_ALPHATIME,  EffEdit.m_fAlphaTime );
	SetWin_Num_float ( this, IDC_EDIT_DEPTH,  EffEdit.m_fDepth );
	SetWin_Num_float ( this, IDC_EDIT_SIZE,  EffEdit.m_fSize );
	SetWin_Num_float ( this, IDC_EDIT_VS1,  EffEdit.m_vEffStart.x );
	SetWin_Num_float ( this, IDC_EDIT_VS2,  EffEdit.m_vEffStart.y );
	SetWin_Num_float ( this, IDC_EDIT_VS3,  EffEdit.m_vEffStart.z );
	SetWin_Num_float ( this, IDC_EDIT_VE1,  EffEdit.m_vEffEnd.x );
	SetWin_Num_float ( this, IDC_EDIT_VE2,  EffEdit.m_vEffEnd.y );
	SetWin_Num_float ( this, IDC_EDIT_VE3,  EffEdit.m_vEffEnd.z );

	D3DCOLOR color = EffEdit.m_vColor;
	DWORD a = color >> 24;
	DWORD r = (color >> 16) & 0xFF;
	DWORD g = (color >> 8 ) & 0xFF;
	DWORD b = color & 0xFF;
	SetWin_Num_int ( this, IDC_EDIT_DC1,  a );
	SetWin_Num_int ( this, IDC_EDIT_DC2,  r );
	SetWin_Num_int ( this, IDC_EDIT_DC3,  g );
	SetWin_Num_int ( this, IDC_EDIT_DC4,  b );

	SetWin_Text ( this, IDC_EDIT_MESH,  EffEdit.m_szMeshFile );
	SetWin_Text ( this, IDC_EDIT_FILER,  EffEdit.m_szFileName_R );
	SetWin_Text ( this, IDC_EDIT_FILEC,  EffEdit.m_szFileName_C );

	return TRUE;
}

BOOL CEffArrow::Save()
{
	EFFCHAR_PROPERTY_ARROW* EffEdit = new EFFCHAR_PROPERTY_ARROW;
	
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EFLAG1 ), EffEdit->m_dwFlag,USEA );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EFLAG2 ), EffEdit->m_dwFlag,USEB );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EFLAG3 ), EffEdit->m_dwFlag,USEC );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EFLAG4 ), EffEdit->m_dwFlag,USED );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EFLAG5 ), EffEdit->m_dwFlag,USESEC );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EFLAG6 ), EffEdit->m_dwFlag,USESIZE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EFLAG7 ), EffEdit->m_dwFlag,USERANDROTATE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EFLAG8 ), EffEdit->m_dwFlag,USEARROW );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EFLAG9 ), EffEdit->m_dwFlag,USEEFFECT );
	EffEdit->m_bUse = GetWin_Check ( this, IDC_CHECK_BUSE );
	EffEdit->m_nBlend = GetWin_Num_int ( this, IDC_EDIT_BLEND );
	EffEdit->m_nSec = GetWin_Num_int ( this, IDC_EDIT_SEC );
	EffEdit->m_fSetRate = GetWin_Num_float ( this, IDC_EDIT_SETRATE );
	EffEdit->m_fFullTime = GetWin_Num_float ( this, IDC_EDIT_FULLTIME );
	EffEdit->m_fAlphaTime = GetWin_Num_float ( this, IDC_EDIT_ALPHATIME );
	EffEdit->m_fDepth = GetWin_Num_float ( this, IDC_EDIT_DEPTH );
	EffEdit->m_fSize = GetWin_Num_float ( this, IDC_EDIT_SIZE );
	EffEdit->m_vEffStart.x = GetWin_Num_float ( this, IDC_EDIT_VS1 );
	EffEdit->m_vEffStart.y = GetWin_Num_float ( this, IDC_EDIT_VS2 );
	EffEdit->m_vEffStart.z = GetWin_Num_float ( this, IDC_EDIT_VS3 );
	EffEdit->m_vEffEnd.x = GetWin_Num_float ( this, IDC_EDIT_VE1 );
	EffEdit->m_vEffEnd.y = GetWin_Num_float ( this, IDC_EDIT_VE2 );
	EffEdit->m_vEffEnd.z = GetWin_Num_float ( this, IDC_EDIT_VE3 );

	BYTE a,r,g,b;
	a = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DC1 );
	r = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DC2 );
	g = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DC3 );
	b = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DC4 );
	EffEdit->m_vColor = D3DCOLOR_ARGB(a,r,g,b);

	StringCchCopy( EffEdit->m_szMeshFile, MAX_PATH, GetWin_Text( this, IDC_EDIT_MESH ).GetString() );
	StringCchCopy( EffEdit->m_szFileName_R, MAX_PATH, GetWin_Text( this, IDC_EDIT_FILER ).GetString() );
	StringCchCopy( EffEdit->m_szFileName_C, MAX_PATH, GetWin_Text( this, IDC_EDIT_FILEC ).GetString() );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffArrowEdit->SetProperty(EffEditProp);

	return TRUE;
}
