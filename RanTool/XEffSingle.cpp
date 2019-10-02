// XEffSingle.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffSingle.h"
#include "xEffTab.h"
#include ".\xeffsingle.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include "DummyData.h"


// CEffSingle dialog

IMPLEMENT_DYNAMIC(CEffSingle, CPropertyPage)
CEffSingle::CEffSingle(LOGFONT logfont)
	: CPropertyPage(CEffSingle::IDD)
	,m_pFont( NULL )
	,EffSingleEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffSingleEdit = new DxEffCharSingle;
}

CEffSingle::~CEffSingle()
{
}

void CEffSingle::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEffSingle, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CEffSingle message handlers
BOOL CEffSingle::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	SetWin_Combo_Init ( this, IDC_COMBO_WEATHER, DUMMYDATA::m_WeatherType, WESIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_ANIM, DUMMYDATA::m_AnimType, ANSIZE );

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffSingle::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffSingleReturn( EffSingleEdit );
	}
}

void CEffSingle::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

void	CEffSingle::SetEffSingle ( DxEffCharSingle*	EffSingleX)
{ 
	EffSingleEdit = EffSingleX; 
	Update();
}

BOOL	CEffSingle::Update()
{
	EFFCHAR_PROPERTY_SINGLE EffEdit = *((EFFCHAR_PROPERTY_SINGLE*)EffSingleEdit->GetProperty() );
	SetWin_Check ( this, IDC_CHECK_REPEAT, EffEdit.m_dwFlag&USE_REPEAT );
	SetWin_Check ( this, IDC_CHECK_REPEATMOVE, EffEdit.m_dwFlag&USE_REPEATMOVE );
	SetWin_Check ( this, IDC_CHECK_AUTOMOVE, EffEdit.m_dwFlag&USE_AUTOMOVE );
	SetWin_Check ( this, IDC_CHECK_1POINT, EffEdit.m_dwFlag&USE_1POINT );
	SetWin_Check ( this, IDC_CHECK_2POINT, EffEdit.m_dwFlag&USE_2POINT );
	SetWin_Check ( this, IDC_CHECK_MATRIX, EffEdit.m_dwFlag&USE_MATRIX );
	SetWin_Num_int ( this, IDC_EDIT_PLAYSINGLE,  EffEdit.m_dwPlaySlngle );
	SetWin_Combo_Sel ( this, IDC_COMBO_WEATHER, (int)EffEdit.m_nWeather );
	SetWin_Combo_Sel ( this, IDC_COMBO_ANIM, (int)EffEdit.m_nAniMType );
	SetWin_Num_float ( this, IDC_EDIT_COOLTIME, EffEdit.m_fCoolTime );
	SetWin_Num_float ( this, IDC_EDIT_SCALE, EffEdit.m_fScale );
	SetWin_Num_float ( this, IDC_EDIT_DEPTHUP, EffEdit.m_fDepthUp );
	SetWin_Num_float ( this, IDC_EDIT_DEPTHDOWN, EffEdit.m_fDepthDown );
	SetWin_Num_float ( this, IDC_EDIT_REPEATSPEED, EffEdit.m_fRepeatSpeed );
	SetWin_Text ( this, IDC_EDIT_FILENAME, EffEdit.m_szFileName );
	SetWin_Text ( this, IDC_EDIT_TRACE, EffEdit.m_szTrace );
	SetWin_Text ( this, IDC_EDIT_TRACEBACK, EffEdit.m_szTraceBack );

	return TRUE;
}

BOOL	CEffSingle::Save()
{
	EFFCHAR_PROPERTY_SINGLE* EffEdit = new EFFCHAR_PROPERTY_SINGLE;

	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_REPEAT ), EffEdit->m_dwFlag,USE_REPEAT );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_REPEATMOVE ), EffEdit->m_dwFlag,USE_REPEATMOVE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AUTOMOVE ), EffEdit->m_dwFlag,USE_AUTOMOVE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_1POINT ), EffEdit->m_dwFlag,USE_1POINT );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_2POINT ), EffEdit->m_dwFlag,USE_2POINT );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_MATRIX ), EffEdit->m_dwFlag,USE_MATRIX );

	EffEdit->m_dwPlaySlngle = GetWin_Num_int ( this, IDC_EDIT_PLAYSINGLE );
	EffEdit->m_nWeather = ( WEATHER ) GetWin_Combo_Sel ( this, IDC_COMBO_WEATHER );
	EffEdit->m_nAniMType = ( ANIMATION ) GetWin_Combo_Sel ( this, IDC_COMBO_ANIM );
	EffEdit->m_fCoolTime = GetWin_Num_float ( this, IDC_EDIT_COOLTIME );
	EffEdit->m_fScale = GetWin_Num_float ( this, IDC_EDIT_SCALE );
	EffEdit->m_fDepthUp = GetWin_Num_float ( this, IDC_EDIT_DEPTHUP );
	EffEdit->m_fDepthDown = GetWin_Num_float ( this, IDC_EDIT_DEPTHDOWN );
	EffEdit->m_fRepeatSpeed = GetWin_Num_float ( this, IDC_EDIT_REPEATSPEED );

	StringCchCopy( EffEdit->m_szFileName, MAX_PATH, GetWin_Text( this, IDC_EDIT_FILENAME ).GetString() );
	StringCchCopy( EffEdit->m_szTrace, STRACE_NSIZE, GetWin_Text( this, IDC_EDIT_TRACE ).GetString() );
	StringCchCopy( EffEdit->m_szTraceBack, STRACE_NSIZE, GetWin_Text( this, IDC_EDIT_TRACEBACK ).GetString() );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffSingleEdit->SetProperty(EffEditProp);

	return TRUE;
}
