// DlgBasic.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgBasic.h"
#include "ToolTab.h"
#include ".\dlgbasic.h"

#include "RanEditLevelView.h"
#include "EtcFunction.h"

// CDlgBasic dialog

IMPLEMENT_DYNAMIC(CDlgBasic, CPropertyPage)
CDlgBasic::CDlgBasic(LOGFONT logfont)
	: CPropertyPage(CDlgBasic::IDD)
	, m_pFont( NULL )
	, pGLLand( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CDlgBasic::~CDlgBasic()
{
}

void CDlgBasic::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBasic, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_BACK, OnBnClickedButtonBasicBack)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_SAVE, OnBnClickedButtonBasicSave)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_WLDOPEN, OnBnClickedButtonBasicWldopen)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_BUILDQUAD, OnBnClickedButtonBasicBuildquad)
	ON_CBN_SELCHANGE(IDC_COMBO_BASIC_QUAD, OnCbnSelchangeComboBasicQuad)
END_MESSAGE_MAP()


// CDlgBasic message handlers
BOOL CDlgBasic::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	std::string strDevision[10] = 
	{
		"QUAD_DIV_01",
		"QUAD_DIV_02",
		"QUAD_DIV_03",
		"QUAD_DIV_04",
		"QUAD_DIV_05",
		"QUAD_DIV_06",
		"QUAD_DIV_07",
		"QUAD_DIV_08",
		"QUAD_DIV_09",
		"QUAD_DIV_10",
	};

	SetWin_Combo_Init( this, IDC_COMBO_BASIC_QUAD, strDevision, 10 );

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgBasic::SetData( GLLandMan*	pLand )
{
	if ( pLand )
	{
		pGLLand = pLand;
		ShowData();
	}
}

void CDlgBasic::ShowData()
{
	if ( !pGLLand )	return;

	SetWin_Text( this, IDC_EDIT_BASIC_WLDNAME, pGLLand->GetWldFileName() );
	SetWin_Text( this, IDC_EDIT_BASIC_FILENAME, pGLLand->GetFileName() );

	int nIndex = 0;
	EMDIVISION emDevision  = pGLLand->GetLandTreeDiv();
	switch ( emDevision )
	{
	case QUAD_DIV_01:	nIndex = 0;	break;
	case QUAD_DIV_02:	nIndex = 1;	break;
	case QUAD_DIV_03:	nIndex = 2;	break;
	case QUAD_DIV_04:	nIndex = 3;	break;
	case QUAD_DIV_05:	nIndex = 4;	break;
	case QUAD_DIV_06:	nIndex = 5;	break;
	case QUAD_DIV_07:	nIndex = 6;	break;
	case QUAD_DIV_08:	nIndex = 7;	break;
	case QUAD_DIV_09:	nIndex = 8;	break;
	case QUAD_DIV_10:	nIndex = 9;	break;
	};

	SetWin_Combo_Sel( this, IDC_COMBO_BASIC_QUAD, nIndex );
	SetWin_Num_int( this, IDC_EDIT_BASIC_DEVISION, int (emDevision) );
}

void CDlgBasic::OnBnClickedButtonBasicBack()
{
	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_MAIN );
}

void CDlgBasic::OnBnClickedButtonBasicSave()
{
	int nSelect = GetWin_Num_int( this, IDC_EDIT_BASIC_DEVISION );
	pGLLand->SetFileName( GetWin_Text( this, IDC_EDIT_BASIC_FILENAME ) );
	pGLLand->SetLandTreeDiv( EMDIVISION(nSelect) );

	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_MAIN );
}

void CDlgBasic::OnBnClickedButtonBasicWldopen()
{
	if ( !pGLLand )	return;

	CString szFilter = "WLD|*.wld|";
	CFileDialog dlg ( TRUE,".WLD",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );
	dlg.m_ofn.lpstrInitialDir = DxLandMan::GetPath();
	if ( dlg.DoModal() == IDOK )	
	{
		BOOL bOK = pGLLand->LoadWldFile ( dlg.GetFileName(), pGLLand->GetFileVer()<=GLLevelFile::VERSION_BEFORE_GATE );
		if ( !bOK )
		{
			MessageBox( "Error Wld Load" );
		}

		CRanEditLevelView::GetView()->LoadWLD( dlg.GetFileName().GetString() );

		ShowData();
	}
}

void CDlgBasic::OnBnClickedButtonBasicBuildquad()
{
	if ( !pGLLand )	return;
	
	int nSelect = GetWin_Num_int( this, IDC_EDIT_BASIC_DEVISION );
	pGLLand->SetLandTreeDiv( EMDIVISION(nSelect) );
	pGLLand->SetMap();
}

void CDlgBasic::OnCbnSelchangeComboBasicQuad()
{
	int nSelect = GetWin_Combo_Sel( this, IDC_COMBO_BASIC_QUAD );

	EMDIVISION emDevision;
	switch ( nSelect )
	{
	case 0:	emDevision = QUAD_DIV_01;	break;
	case 1:	emDevision = QUAD_DIV_02;	break;
	case 2:	emDevision = QUAD_DIV_03;	break;
	case 3:	emDevision = QUAD_DIV_04;	break;
	case 4:	emDevision = QUAD_DIV_05;	break;
	case 5:	emDevision = QUAD_DIV_06;	break;
	case 6:	emDevision = QUAD_DIV_07;	break;
	case 7:	emDevision = QUAD_DIV_08;	break;
	case 8:	emDevision = QUAD_DIV_09;	break;
	case 9:	emDevision = QUAD_DIV_10;	break;
	};

	SetWin_Num_int( this, IDC_EDIT_BASIC_DEVISION, (int) emDevision );
}
