// RanViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RanViewer.h"
#include "RanViewDlg.h"
#include "RanViewTab.h"
#include "EtcFunction.h"
#include "ToolComment.h"
#include "../../EngineLib/Meshs/DxAniKeys.h"
#include ".\ranviewdlg.h"
#include "RanView.h"

// CRanViewDlg dialog

IMPLEMENT_DYNAMIC(CRanViewDlg, CPropertyPage)
CRanViewDlg::CRanViewDlg(LOGFONT logfont)
	: CPropertyPage(CRanViewDlg::IDD)
	,m_pFont( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanViewDlg::~CRanViewDlg()
{
}

void CRanViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_R, Slider_R );
	DDX_Control(pDX, IDC_SLIDER_G, Slider_G );
	DDX_Control(pDX, IDC_SLIDER_B, Slider_B );
}


BEGIN_MESSAGE_MAP(CRanViewDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_ANIMATE, OnBnClickedButtonAnimate)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnBnClickedButtonSet)
	ON_CBN_SELCHANGE(IDC_COMBO_EDITTYPE, OnCbnSelchangeComboEdittype)
	ON_BN_CLICKED(IDC_BUTTON_SET2, OnBnClickedButtonSet2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_R, OnNMCustomdrawSliderR)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_G, OnNMCustomdrawSliderG)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_B, OnNMCustomdrawSliderB)
END_MESSAGE_MAP()


// CRanViewDlg message handlers
BOOL CRanViewDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	SetWin_Combo_Init ( this, IDC_COMBO_ANTYPE, ToolComment::m_AniType, AN_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_ANIM, ToolComment::m_AniMain, AN_TYPE_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_ANIS, ToolComment::m_AniSub, AN_SUB_00_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_EDITTYPE, ToolComment::m_EditType, EDIT_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_MODETYPE, ToolComment::m_ModeType, MODE_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_STANCE, ToolComment::m_StanceType, STANCE_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_ABLTYPE, ToolComment::m_ABLType, PIECE_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_ADRATE, ToolComment::m_AdjustRate, RSIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_COLOR, ToolComment::m_ColorType, COLOR_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_ITEMLEVEL, ToolComment::m_LevelType, LEVEL_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_ITEMEFFECT, ToolComment::m_LevelEff, LEVEL_EFF );
	SetWin_Combo_Init ( this, IDC_COMBO_EFF_SEX, ToolComment::m_LevelEffSex, LEVEL_EFFSEX );
	SetWin_Enable(this,IDC_COMBO_MODETYPE,false);
	SetWin_Enable(this,IDC_COMBO_STANCE,false);
	SetWin_Enable(this,IDC_COMBO_ABLTYPE,false);
	SetWin_Enable(this,IDC_COMBO_ADRATE,false);

	Slider_R.SetRange(0, 31, TRUE);
	Slider_G.SetRange(0, 31, TRUE);
	Slider_B.SetRange(0, 31, TRUE);
	Slider_R.SetPos(0);
	Slider_G.SetPos(0);
	Slider_B.SetPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CRanViewDlg::OnBnClickedButtonAnimate()
{
	CRanView::GetView()->SetAnim(
		GetWin_Combo_Sel ( this, IDC_COMBO_ANTYPE ),
		(EMANI_MAINTYPE)GetWin_Combo_Sel ( this, IDC_COMBO_ANIM ),
		(EMANI_SUBTYPE)GetWin_Combo_Sel ( this, IDC_COMBO_ANIS ),
		(bool) GetWin_Check ( this, IDC_CHECK_STANCE ) );
}

void CRanViewDlg::OnBnClickedButtonSet()
{
	int nType = GetWin_Combo_Sel ( this, IDC_COMBO_EDITTYPE );
	switch (nType)
	{
	case 0:
		{
			MessageBox("Please Select Edit Type","Error",MB_OK);
		}break;
	case 1:
		{
			CRanView::GetView()->SetType( nType );
			CRanView::GetView()->SetMode( GetWin_Combo_Sel ( this, IDC_COMBO_MODETYPE ) );
			CRanView::GetView()->SetStance( GetWin_Combo_Sel ( this, IDC_COMBO_STANCE ) );
			CRanView::GetView()->SetPieceType( GetWin_Combo_Sel ( this, IDC_COMBO_ABLTYPE ) );
			CRanView::GetView()->SetDevider( GetWin_Combo_Sel ( this, IDC_COMBO_ADRATE ) );
		}break;
	case 2:
		{
			CRanView::GetView()->SetType( nType );
			CRanView::GetView()->SetMode( GetWin_Combo_Sel ( this, IDC_COMBO_MODETYPE )  );
			CRanView::GetView()->SetStance( GetWin_Combo_Sel ( this, IDC_COMBO_STANCE ) );
			CRanView::GetView()->SetDevider( GetWin_Combo_Sel ( this, IDC_COMBO_ADRATE ) );
		}break;
	};
}

void CRanViewDlg::OnCbnSelchangeComboEdittype()
{
	int nType = GetWin_Combo_Sel ( this, IDC_COMBO_EDITTYPE );
	switch (nType)
	{
	case 0:
		{
			SetWin_Enable(this,IDC_COMBO_MODETYPE,false);
			SetWin_Enable(this,IDC_COMBO_STANCE,false);
			SetWin_Enable(this,IDC_COMBO_ABLTYPE,false);
			SetWin_Enable(this,IDC_COMBO_ADRATE,false);
		}break;
	case 1:
		{
			SetWin_Enable(this,IDC_COMBO_MODETYPE,true);
			SetWin_Enable(this,IDC_COMBO_STANCE,true);
			SetWin_Enable(this,IDC_COMBO_ABLTYPE,true);
			SetWin_Enable(this,IDC_COMBO_ADRATE,true);
		}break;
	case 2:
		{
			SetWin_Enable(this,IDC_COMBO_MODETYPE,true);
			SetWin_Enable(this,IDC_COMBO_STANCE,true);
			SetWin_Enable(this,IDC_COMBO_ADRATE,true);
			SetWin_Enable(this,IDC_COMBO_ABLTYPE,false);
		}break;
	};
}

void CRanViewDlg::OnBnClickedButtonSet2()
{
	CRanView::GetView()->SetGrind( GetWin_Combo_Sel ( this, IDC_COMBO_ITEMLEVEL ) );
}

void CRanViewDlg::OnNMCustomdrawSliderR(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetColor();
	*pResult = 0;
}

void CRanViewDlg::OnNMCustomdrawSliderG(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetColor();
	*pResult = 0;
}

void CRanViewDlg::OnNMCustomdrawSliderB(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	SetColor();
	*pResult = 0;
}

void CRanViewDlg::SetColor()
{
	int nRed = Slider_R.GetPos();
	int nGreen = Slider_G.GetPos();
	int nBlue = Slider_B.GetPos();
	WORD wTemp = nRed << 10	| nGreen << 5 | nBlue;

	SetWin_Num_int(this,IDC_EDIT_R,nRed );
	SetWin_Num_int(this,IDC_EDIT_G,nGreen );
	SetWin_Num_int(this,IDC_EDIT_B,nBlue );
	SetWin_Num_int(this,IDC_EDIT_COLOR,wTemp );
	CRanView::GetView()->SetColor( GetWin_Combo_Sel ( this, IDC_COMBO_COLOR ),wTemp );
}

