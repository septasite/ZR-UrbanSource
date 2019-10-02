// XEffAmbient.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffAmbient.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include "DummyData.h"
#include ".\xeffambient.h"


// CEffAmbient dialog

IMPLEMENT_DYNAMIC(CEffAmbient, CPropertyPage)
CEffAmbient::CEffAmbient(LOGFONT logfont)
	: CPropertyPage(CEffAmbient::IDD)
	,m_pFont( NULL )
	,EffAmbientEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffAmbientEdit =  new DxEffCharAmbient;
}

CEffAmbient::~CEffAmbient()
{
}

void CEffAmbient::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffAmbient, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_COLOP, OnCbnSelchangeComboColop)
END_MESSAGE_MAP()


// CEffAmbient message handlers
BOOL CEffAmbient::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	SetWin_Combo_Init ( this, IDC_COMBO_COLOP, DUMMYDATA::m_DColorOp, XD3DTOP_SIZE );

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffAmbient::SetEffAmbient ( DxEffCharAmbient*	EffAmbientX)
{ 
	EffAmbientEdit = EffAmbientX; 
	Update();
}

void CEffAmbient::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffAmbientReturn( EffAmbientEdit );
	}
}

void CEffAmbient::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffAmbient::Update()
{
	EFFCHAR_PROPERTY_AMBIENT EffEdit = *((EFFCHAR_PROPERTY_AMBIENT*)EffAmbientEdit->GetProperty() );
	SetWin_Check ( this, IDC_CHECK_AMFLAG1, EffEdit.m_dwFlage&USEALL );
	SetWin_Check ( this, IDC_CHECK_AMFLAG2, EffEdit.m_dwFlage&USETEXCOLOR );
	SetWin_Num_int ( this, IDC_EDIT_COLOR,  EffEdit.m_dwColorOP );
	SetWin_Num_float ( this, IDC_EDIT_FTIME,  EffEdit.m_fFullTime);
	SetWin_Num_float ( this, IDC_EDIT_SCRCOLOR,  EffEdit.m_fSrcColor );
	SetWin_Num_float ( this, IDC_EDIT_AMCOLOR1,  EffEdit.m_cColor.r );
	SetWin_Num_float ( this, IDC_EDIT_AMCOLOR2,  EffEdit.m_cColor.g );
	SetWin_Num_float ( this, IDC_EDIT_AMCOLOR3,  EffEdit.m_cColor.b );
	SetWin_Num_float ( this, IDC_EDIT_AMCOLOR4,  EffEdit.m_cColor.a );
	SetWin_Combo_Sel ( this, IDC_COMBO_COLOP, (int)EffEdit.m_dwColorOP );
	return TRUE;
}

BOOL CEffAmbient::Save()
{
	EFFCHAR_PROPERTY_AMBIENT* EffEdit = new EFFCHAR_PROPERTY_AMBIENT;
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AMFLAG1 ), EffEdit->m_dwFlage,USEALL );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AMFLAG2 ), EffEdit->m_dwFlage,USETEXCOLOR );
	EffEdit->m_dwColorOP = GetWin_Num_int ( this, IDC_EDIT_COLOR );
	EffEdit->m_fFullTime = GetWin_Num_float ( this, IDC_EDIT_FTIME );
	EffEdit->m_fSrcColor = GetWin_Num_float ( this, IDC_EDIT_SCRCOLOR );
	EffEdit->m_cColor.r = GetWin_Num_float ( this, IDC_EDIT_AMCOLOR1 );
	EffEdit->m_cColor.g = GetWin_Num_float ( this, IDC_EDIT_AMCOLOR2 );
	EffEdit->m_cColor.b = GetWin_Num_float ( this, IDC_EDIT_AMCOLOR3 );
	EffEdit->m_cColor.a = GetWin_Num_float ( this, IDC_EDIT_AMCOLOR4 );
	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffAmbientEdit->SetProperty(EffEditProp);
	return TRUE;
}


void CEffAmbient::OnCbnSelchangeComboColop()
{
	SetWin_Num_int ( this, IDC_EDIT_COLOR,  (DCOLOROP) GetWin_Combo_Sel ( this, IDC_COMBO_COLOP ) );
}
