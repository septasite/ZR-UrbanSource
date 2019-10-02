// XEffBonePos.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffBonePos.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffBonePos dialog

IMPLEMENT_DYNAMIC(CEffBonePos, CPropertyPage)
CEffBonePos::CEffBonePos(LOGFONT logfont)
	: CPropertyPage(CEffBonePos::IDD)
	,m_pFont( NULL )
	,EffBonePosEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffBonePosEdit = new  DxEffCharBonePosEff;
}

CEffBonePos::~CEffBonePos()
{
}

void CEffBonePos::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffBonePos, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffBonePos message handlers
BOOL CEffBonePos::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffBonePos::SetEffBonePos ( DxEffCharBonePosEff*	EffBonePosX)
{ 
	EffBonePosEdit = EffBonePosX; 
	Update();
}

void CEffBonePos::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffBonePosReturn( EffBonePosEdit );
	}
}

void CEffBonePos::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffBonePos::Update()
{
	EFFCHAR_PROPERTY_BONEPOSEFF EffEdit = *((EFFCHAR_PROPERTY_BONEPOSEFF*)EffBonePosEdit->GetProperty() );

	SetWin_Check ( this, IDC_CHECK_BPFLAG1, EffEdit.m_dwFlag&USE_REMAIN );
	SetWin_Check ( this, IDC_CHECK_BPFLAG2, EffEdit.m_dwFlag&USE_BONEOFFSETPOS );
	SetWin_Check ( this, IDC_CHECK_BPFLAG3, EffEdit.m_dwFlag&USE_RANDOMRANGE );
	SetWin_Check ( this, IDC_CHECK_BPFLAG4, EffEdit.m_dwFlag&USE_SEQUENCE );
	SetWin_Check ( this, IDC_CHECK_BPFLAG5, EffEdit.m_dwFlag&USE_ROTATE );
	SetWin_Check ( this, IDC_CHECK_BPFLAG6, EffEdit.m_dwFlag&USE_PLAY );
	SetWin_Check ( this, IDC_CHECK_BPFLAG7, EffEdit.m_dwFlag&USE_POS1 );
	SetWin_Num_int ( this, IDC_EDIT_PPEC,  EffEdit.m_dwParticlePec );

	D3DCOLOR color = EffEdit.m_dwColor;
	DWORD a = color >> 24;
	DWORD r = (color >> 16) & 0xFF;
	DWORD g = (color >> 8 ) & 0xFF;
	DWORD b = color & 0xFF;
	SetWin_Num_int ( this, IDC_EDIT_DCOL1,  a );
	SetWin_Num_int ( this, IDC_EDIT_DCOL2,  r );
	SetWin_Num_int ( this, IDC_EDIT_DCOL3,  g );
	SetWin_Num_int ( this, IDC_EDIT_DCOL4,  b );

	SetWin_Num_float ( this, IDC_EDIT_VLIFE1,  EffEdit.m_vLife.x );
	SetWin_Num_float ( this, IDC_EDIT_VLIFE2,  EffEdit.m_vLife.y );
	SetWin_Num_float ( this, IDC_EDIT_VROT1,  EffEdit.m_vRotate.x );
	SetWin_Num_float ( this, IDC_EDIT_VROT2,  EffEdit.m_vRotate.y );
	SetWin_Num_float ( this, IDC_EDIT_VSIZE1_1,  EffEdit.m_vSize.x );
	SetWin_Num_float ( this, IDC_EDIT_VSIZE1_2,  EffEdit.m_vSize.y );
	SetWin_Num_float ( this, IDC_EDIT_VSIZE1_3,  EffEdit.m_vSize.z );
	SetWin_Num_float ( this, IDC_EDIT_VVEL1,  EffEdit.m_vVelocity.x );
	SetWin_Num_float ( this, IDC_EDIT_VVEL2,  EffEdit.m_vVelocity.y );
	SetWin_Num_float ( this, IDC_EDIT_VVEL3,  EffEdit.m_vVelocity.z );
	SetWin_Num_float ( this, IDC_EDIT_VLOC1,  EffEdit.m_vLocalPos.x );
	SetWin_Num_float ( this, IDC_EDIT_VLOC2,  EffEdit.m_vLocalPos.y );
	SetWin_Num_float ( this, IDC_EDIT_VLOC3,  EffEdit.m_vLocalPos.z );
	SetWin_Num_int ( this, IDC_EDIT_SCOL,  EffEdit.m_dwSequenceCol );
	SetWin_Num_int ( this, IDC_EDIT_SROW,  EffEdit.m_dwSequenceRow );
	SetWin_Num_float ( this, IDC_EDIT_CLE,  EffEdit.m_fCreateLength );
	SetWin_Text ( this, IDC_EDIT_TXBONE,  EffEdit.m_szBoneName );
	SetWin_Text ( this, IDC_EDIT_TXTEXT,  EffEdit.m_szTexture );

	return TRUE;
}

BOOL CEffBonePos::Save()
{
	EFFCHAR_PROPERTY_BONEPOSEFF* EffEdit = new EFFCHAR_PROPERTY_BONEPOSEFF;

	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG1 ), EffEdit->m_dwFlag,USE_REMAIN );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG2 ), EffEdit->m_dwFlag,USE_BONEOFFSETPOS );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG3 ), EffEdit->m_dwFlag,USE_RANDOMRANGE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG4 ), EffEdit->m_dwFlag,USE_SEQUENCE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG5 ), EffEdit->m_dwFlag,USE_ROTATE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG6 ), EffEdit->m_dwFlag,USE_PLAY );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG7 ), EffEdit->m_dwFlag,USE_POS1 );
	EffEdit->m_dwParticlePec = GetWin_Num_int ( this, IDC_EDIT_PPEC );	

	BYTE a,r,g,b;
	a = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DCOL1 );
	r = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DCOL2 );
	g = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DCOL3 );
	b = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DCOL4 );
	EffEdit->m_dwColor = D3DCOLOR_ARGB(a,r,g,b);

	EffEdit->m_vLife.x = GetWin_Num_float ( this, IDC_EDIT_VLIFE1 );	
	EffEdit->m_vLife.y = GetWin_Num_float ( this, IDC_EDIT_VLIFE2 );
	EffEdit->m_vRotate.x = GetWin_Num_float ( this, IDC_EDIT_VROT1 );
	EffEdit->m_vRotate.y = GetWin_Num_float ( this, IDC_EDIT_VROT2 );
	EffEdit->m_vSize.x = GetWin_Num_float ( this, IDC_EDIT_VSIZE1_1 );
	EffEdit->m_vSize.y = GetWin_Num_float ( this, IDC_EDIT_VSIZE1_2 );
	EffEdit->m_vSize.z = GetWin_Num_float ( this, IDC_EDIT_VSIZE1_3 );
	EffEdit->m_vVelocity.x = GetWin_Num_float ( this, IDC_EDIT_VVEL1 );
	EffEdit->m_vVelocity.y = GetWin_Num_float ( this, IDC_EDIT_VVEL2 );
	EffEdit->m_vVelocity.z = GetWin_Num_float ( this, IDC_EDIT_VVEL3 );
	EffEdit->m_vLocalPos.x = GetWin_Num_float ( this, IDC_EDIT_VLOC1 );
	EffEdit->m_vLocalPos.y = GetWin_Num_float ( this, IDC_EDIT_VLOC2 );
	EffEdit->m_vLocalPos.z = GetWin_Num_float ( this, IDC_EDIT_VLOC3 );
	EffEdit->m_dwSequenceCol = GetWin_Num_int ( this, IDC_EDIT_SCOL );	
	EffEdit->m_dwSequenceRow = GetWin_Num_int ( this, IDC_EDIT_SROW );	
	EffEdit->m_fCreateLength = GetWin_Num_float ( this, IDC_EDIT_CLE );
	StringCchCopy( EffEdit->m_szBoneName, BONEPOSEFF_TEXNAME_SIZE, GetWin_Text( this, IDC_EDIT_TXBONE ).GetString() );
	StringCchCopy( EffEdit->m_szTexture, BONEPOSEFF_TEXNAME_SIZE, GetWin_Text( this, IDC_EDIT_TXTEXT ).GetString() );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffBonePosEdit->SetProperty(EffEditProp);

	return TRUE;
}
