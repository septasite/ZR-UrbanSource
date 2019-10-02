// XEffMark.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffMark.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffMark dialog

IMPLEMENT_DYNAMIC(CEffMark, CPropertyPage)
CEffMark::CEffMark(LOGFONT logfont)
	: CPropertyPage(CEffMark::IDD)
	,m_pFont( NULL )
	,EffMarkEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffMarkEdit = new DxEffCharMark;
}

CEffMark::~CEffMark()
{
}

void CEffMark::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffMark, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffMark message handlers
BOOL CEffMark::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffMark::SetEffMark ( DxEffCharMark*	EffMarkX)
{ 
	EffMarkEdit = EffMarkX; 
	Update();
}

void CEffMark::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffMarkReturn( EffMarkEdit );
	}
}

void CEffMark::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffMark::Update()
{
	EFFCHAR_PROPERTY_MARK EffEdit = *((EFFCHAR_PROPERTY_MARK*)EffMarkEdit->GetProperty() );
	SetWin_Num_int ( this, IDC_EDIT_MFLAG,  EffEdit.m_dwFlag );
	SetWin_Num_int ( this, IDC_EDIT_MBLEND,  EffEdit.m_nBlend );
	SetWin_Num_int ( this, IDC_EDIT_MTNUM,  EffEdit.m_nTexNum );
	SetWin_Num_float ( this, IDC_EDIT_DIF1_1,  EffEdit.m_cDiffuse1.r );
	SetWin_Num_float ( this, IDC_EDIT_DIF1_2,  EffEdit.m_cDiffuse1.g );
	SetWin_Num_float ( this, IDC_EDIT_DIF1_3,  EffEdit.m_cDiffuse1.b );
	SetWin_Num_float ( this, IDC_EDIT_DIF1_4,  EffEdit.m_cDiffuse1.a );
	SetWin_Num_float ( this, IDC_EDIT_DIF2_1,  EffEdit.m_cDiffuse2.r );
	SetWin_Num_float ( this, IDC_EDIT_DIF2_2,  EffEdit.m_cDiffuse2.g );
	SetWin_Num_float ( this, IDC_EDIT_DIF2_3,  EffEdit.m_cDiffuse2.b );
	SetWin_Num_float ( this, IDC_EDIT_DIF2_4,  EffEdit.m_cDiffuse2.a );
	SetWin_Num_float ( this, IDC_EDIT_TEX1_1,  EffEdit.m_vTex01.x );
	SetWin_Num_float ( this, IDC_EDIT_TEX1_2,  EffEdit.m_vTex01.y );
	SetWin_Num_float ( this, IDC_EDIT_TEX2_1,  EffEdit.m_vTex02.x );
	SetWin_Num_float ( this, IDC_EDIT_TEX2_2,  EffEdit.m_vTex02.y );
	SetWin_Num_float ( this, IDC_EDIT_UV1_1,  EffEdit.m_vTexUV01.x );
	SetWin_Num_float ( this, IDC_EDIT_UV1_2,  EffEdit.m_vTexUV01.y );
	SetWin_Num_float ( this, IDC_EDIT_UV2_1,  EffEdit.m_vTexUV02.x );
	SetWin_Num_float ( this, IDC_EDIT_UV2_2,  EffEdit.m_vTexUV02.y );
	SetWin_Text ( this, IDC_EDIT_TEXTURE1,  EffEdit.m_szTex1 );
	SetWin_Text ( this, IDC_EDIT_TEXTURE2,  EffEdit.m_szTex2 );

	return TRUE;
}

BOOL CEffMark::Save()
{
	EFFCHAR_PROPERTY_MARK* EffEdit = new EFFCHAR_PROPERTY_MARK;

	EffEdit->m_dwFlag = GetWin_Num_int ( this, IDC_EDIT_MFLAG );
	EffEdit->m_nBlend = GetWin_Num_int ( this, IDC_EDIT_MBLEND );
	EffEdit->m_nTexNum = GetWin_Num_int ( this, IDC_EDIT_MTNUM );
	EffEdit->m_cDiffuse1.r = GetWin_Num_float ( this,IDC_EDIT_DIF1_1 );
	EffEdit->m_cDiffuse1.g = GetWin_Num_float ( this,IDC_EDIT_DIF1_2 );
	EffEdit->m_cDiffuse1.b = GetWin_Num_float ( this,IDC_EDIT_DIF1_3 );
	EffEdit->m_cDiffuse1.a = GetWin_Num_float ( this,IDC_EDIT_DIF1_4 );
	EffEdit->m_cDiffuse2.r = GetWin_Num_float ( this,IDC_EDIT_DIF2_1 );
	EffEdit->m_cDiffuse2.g = GetWin_Num_float ( this,IDC_EDIT_DIF2_2 );
	EffEdit->m_cDiffuse2.b = GetWin_Num_float ( this,IDC_EDIT_DIF2_3 );
	EffEdit->m_cDiffuse2.a = GetWin_Num_float ( this,IDC_EDIT_DIF2_4 );
	EffEdit->m_vTex01.x = GetWin_Num_float ( this,IDC_EDIT_TEX1_1 );
	EffEdit->m_vTex01.y = GetWin_Num_float ( this,IDC_EDIT_TEX1_2 );
	EffEdit->m_vTex02.x = GetWin_Num_float ( this,IDC_EDIT_TEX2_1 );
	EffEdit->m_vTex02.y = GetWin_Num_float ( this,IDC_EDIT_TEX2_2 );
	EffEdit->m_vTexUV01.x = GetWin_Num_float ( this,IDC_EDIT_UV1_1 );
	EffEdit->m_vTexUV01.y = GetWin_Num_float ( this,IDC_EDIT_UV1_2 );
	EffEdit->m_vTexUV02.x = GetWin_Num_float ( this,IDC_EDIT_UV2_1 );
	EffEdit->m_vTexUV02.y = GetWin_Num_float ( this,IDC_EDIT_UV2_2 );
	StringCchCopy( EffEdit->m_szTex1, MAX_PATH, GetWin_Text( this, IDC_EDIT_TEXTURE1 ).GetString() );
	StringCchCopy( EffEdit->m_szTex2, MAX_PATH, GetWin_Text( this, IDC_EDIT_TEXTURE2 ).GetString() );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffMarkEdit->SetProperty(EffEditProp);

	return TRUE;
}
