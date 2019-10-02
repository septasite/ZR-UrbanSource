// ZEffTrace.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "ZEffTrace.h"
#include "ZEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// AEffTrace dialog

IMPLEMENT_DYNAMIC(AEffTrace, CPropertyPage)
AEffTrace::AEffTrace(LOGFONT logfont)
	: CPropertyPage(AEffTrace::IDD)
	,m_pFont( NULL )
	,EffTraceEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffTraceEdit = new DxEffAniData_Trace;
}

AEffTrace::~AEffTrace()
{
}

void AEffTrace::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AEffTrace, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// AEffTrace message handlers
BOOL AEffTrace::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void AEffTrace::SetEffTrace( DxEffAniData_Trace*	EffTraceX )
{ 
	EffTraceEdit = EffTraceX ; 
	Update();
}

BOOL AEffTrace::Update()
{
	SetWin_Num_float ( this, IDC_EDIT_SCALE,  EffTraceEdit->m_fScale );
	SetWin_Text ( this, IDC_EDIT_TEX, EffTraceEdit->m_strTexName.c_str() );

	return TRUE;
}

BOOL AEffTrace::Save()
{
	EffTraceEdit->m_fScale = GetWin_Num_float ( this, IDC_EDIT_SCALE );
	EffTraceEdit->m_strTexName = GetWin_Text ( this, IDC_EDIT_TEX ).GetString();

	return TRUE;
}
void AEffTrace::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffTraceReturn( EffTraceEdit );
	}
}

void AEffTrace::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

