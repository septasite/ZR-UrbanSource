// ZEffSingle.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "ZEffSingle.h"
#include "ZEffTab.h"
#include ".\zeffsingle.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// AEffSingle dialog

IMPLEMENT_DYNAMIC(AEffSingle, CPropertyPage)
AEffSingle::AEffSingle(LOGFONT logfont)
	: CPropertyPage(AEffSingle::IDD)
	,m_pFont( NULL )
	,EffSingleEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffSingleEdit = new DxEffAniData_Single;
}

AEffSingle::~AEffSingle()
{
}

void AEffSingle::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AEffSingle, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// AEffSingle message handlers
BOOL AEffSingle::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void AEffSingle::SetEffSingle( DxEffAniData_Single*	EffSingleX )
{ 
	EffSingleEdit = EffSingleX ; 
	Update();
}

BOOL AEffSingle::Update()
{
	SetWin_Check ( this, IDC_CHECK_FLAG1, EffSingleEdit->m_dwFlags&USEDRAWPOINT );
	SetWin_Check ( this, IDC_CHECK_FLAG2, EffSingleEdit->m_dwFlags&USEDRAWRANGE );
	SetWin_Check ( this, IDC_CHECK_FLAG3, EffSingleEdit->m_dwFlags&USEDRAWDIRECT );
	SetWin_Check ( this, IDC_CHECK_FLAG4, EffSingleEdit->m_dwFlags&USEDRAWMATRIX );
	SetWin_Check ( this, IDC_CHECK_FLAG5, EffSingleEdit->m_dwFlags&USETIMEDAY );
	SetWin_Check ( this, IDC_CHECK_FLAG6, EffSingleEdit->m_dwFlags&USETIMENIGHT );
	SetWin_Check ( this, IDC_CHECK_FLAG7, EffSingleEdit->m_dwFlags&USESKYFINE );
	SetWin_Check ( this, IDC_CHECK_FLAG8, EffSingleEdit->m_dwFlags&USESKYRAIN );
	SetWin_Check ( this, IDC_CHECK_FLAG9, EffSingleEdit->m_dwFlags&USESKYSNOW );
	SetWin_Check ( this, IDC_CHECK_FLAG10, EffSingleEdit->m_dwFlags&USESKYLEAVES );
	SetWin_Check ( this, IDC_CHECK_FLAG11, EffSingleEdit->m_dwFlags&USECHARMOVE );

	SetWin_Num_int ( this, IDC_EDIT_FRAME,  EffSingleEdit->m_dwFrame );
	SetWin_Num_float ( this, IDC_EDIT_FACT,  EffSingleEdit->m_fFact );
	SetWin_Num_float ( this, IDC_EDIT_SCALE,  EffSingleEdit->m_fScale );

	/*SetWin_Num_float_f ( this, IDC_EDIT_MAT1,  EffSingleEdit->m_matBase._11 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT2,  EffSingleEdit->m_matBase._12 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT3,  EffSingleEdit->m_matBase._13 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT4,  EffSingleEdit->m_matBase._14 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT5,  EffSingleEdit->m_matBase._21 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT6,  EffSingleEdit->m_matBase._22 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT7,  EffSingleEdit->m_matBase._23 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT8,  EffSingleEdit->m_matBase._24 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT9,  EffSingleEdit->m_matBase._31 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT10,  EffSingleEdit->m_matBase._32 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT11,  EffSingleEdit->m_matBase._33 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT12,  EffSingleEdit->m_matBase._34 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT13,  EffSingleEdit->m_matBase._41 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT14,  EffSingleEdit->m_matBase._42 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT15,  EffSingleEdit->m_matBase._43 );
	SetWin_Num_float_f ( this, IDC_EDIT_MAT16,  EffSingleEdit->m_matBase._44 );*/

	SetWin_Text ( this, IDC_EDIT_EFF, EffSingleEdit->m_szEff );
	SetWin_Text ( this, IDC_EDIT_BIP1, EffSingleEdit->m_szBipFirst );
	SetWin_Text ( this, IDC_EDIT_BIP2, EffSingleEdit->m_szBipSecond );

	return TRUE;
}

BOOL AEffSingle::Save()
{
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FLAG1 ), EffSingleEdit->m_dwFlags,USEDRAWPOINT );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FLAG2 ), EffSingleEdit->m_dwFlags,USEDRAWRANGE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FLAG3 ), EffSingleEdit->m_dwFlags,USEDRAWDIRECT );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FLAG4 ), EffSingleEdit->m_dwFlags,USEDRAWMATRIX );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FLAG5 ), EffSingleEdit->m_dwFlags,USETIMEDAY);
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FLAG6 ), EffSingleEdit->m_dwFlags,USETIMENIGHT );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FLAG7 ), EffSingleEdit->m_dwFlags,USESKYFINE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FLAG8 ), EffSingleEdit->m_dwFlags,USESKYRAIN );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FLAG9 ), EffSingleEdit->m_dwFlags,USESKYSNOW  );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FLAG10 ), EffSingleEdit->m_dwFlags,USESKYLEAVES );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FLAG11 ), EffSingleEdit->m_dwFlags,USECHARMOVE );

	EffSingleEdit->m_dwFrame = GetWin_Num_int ( this, IDC_EDIT_FRAME );
	EffSingleEdit->m_fFact = GetWin_Num_float ( this, IDC_EDIT_FACT );
	EffSingleEdit->m_fScale = GetWin_Num_float ( this, IDC_EDIT_SCALE );

	EffSingleEdit->m_matBase._11 = GetWin_Num_float ( this, IDC_EDIT_MAT1 );
	EffSingleEdit->m_matBase._12 = GetWin_Num_float ( this, IDC_EDIT_MAT2 );
	EffSingleEdit->m_matBase._13 = GetWin_Num_float ( this, IDC_EDIT_MAT3 );
	EffSingleEdit->m_matBase._14 = GetWin_Num_float ( this, IDC_EDIT_MAT4 );
	EffSingleEdit->m_matBase._21 = GetWin_Num_float ( this, IDC_EDIT_MAT5 );
	EffSingleEdit->m_matBase._22 = GetWin_Num_float ( this, IDC_EDIT_MAT6 );
	EffSingleEdit->m_matBase._23 = GetWin_Num_float ( this, IDC_EDIT_MAT7 );
	EffSingleEdit->m_matBase._24 = GetWin_Num_float ( this, IDC_EDIT_MAT8 );
	EffSingleEdit->m_matBase._31 = GetWin_Num_float ( this, IDC_EDIT_MAT9 );
	EffSingleEdit->m_matBase._32 = GetWin_Num_float ( this, IDC_EDIT_MAT10 );
	EffSingleEdit->m_matBase._33 = GetWin_Num_float ( this, IDC_EDIT_MAT11 );
	EffSingleEdit->m_matBase._34 = GetWin_Num_float ( this, IDC_EDIT_MAT12 );
	EffSingleEdit->m_matBase._41 = GetWin_Num_float ( this, IDC_EDIT_MAT13 );
	EffSingleEdit->m_matBase._42 = GetWin_Num_float ( this, IDC_EDIT_MAT14 );
	EffSingleEdit->m_matBase._43 = GetWin_Num_float ( this, IDC_EDIT_MAT15 );
	EffSingleEdit->m_matBase._44 = GetWin_Num_float ( this, IDC_EDIT_MAT16 );
	
	StringCchCopy( EffSingleEdit->m_szEff, STRING_NUM_128, GetWin_Text( this, IDC_EDIT_EFF ).GetString() );
	StringCchCopy( EffSingleEdit->m_szBipFirst, STRING_NUM_128, GetWin_Text( this, IDC_EDIT_BIP1 ).GetString() );
	StringCchCopy( EffSingleEdit->m_szBipSecond, STRING_NUM_128, GetWin_Text( this, IDC_EDIT_BIP2 ).GetString() );

	return TRUE;
}
void AEffSingle::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffSingleReturn( EffSingleEdit );
	}
}

void AEffSingle::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}
