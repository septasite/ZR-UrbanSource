// ZEffFaceOff.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "ZEffFaceOff.h"
#include "ZEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// AEffFaceOff dialog

IMPLEMENT_DYNAMIC(AEffFaceOff, CPropertyPage)
AEffFaceOff::AEffFaceOff(LOGFONT logfont)
	: CPropertyPage(AEffFaceOff::IDD)
	,m_pFont( NULL )
	,EffFaceOffEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffFaceOffEdit = new DxEffAniData_FaceOff;
}

AEffFaceOff::~AEffFaceOff()
{
}

void AEffFaceOff::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AEffFaceOff, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// AEffFaceOff message handlers
BOOL AEffFaceOff::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void AEffFaceOff::SetEffFaceOff( DxEffAniData_FaceOff*	EffFaceOffX )
{ 
	EffFaceOffEdit = EffFaceOffX ; 
	Update();
}

BOOL AEffFaceOff::Update()
{
	SetWin_Text ( this, IDC_EDIT_TEX, EffFaceOffEdit->m_szTexture );

	return TRUE;
}

BOOL AEffFaceOff::Save()
{
	StringCchCopy( EffFaceOffEdit->m_szTexture, 32, GetWin_Text( this, IDC_EDIT_TEX ).GetString() );

	return TRUE;
}
void AEffFaceOff::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffFaceOffReturn( EffFaceOffEdit );
	}
}

void AEffFaceOff::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}
