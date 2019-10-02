// TabABL.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "TabABL.h"
#include "ToolTab.h"
#include "EtcFunction.h"
#include "DummyData.h"
#include ".\tababl.h"

// CTabABL dialog

IMPLEMENT_DYNAMIC(CTabABL, CPropertyPage)
CTabABL::CTabABL(LOGFONT logfont)
	: CPropertyPage(CTabABL::IDD)
	,m_pFont( NULL )
{
	m_bDlgInit = FALSE;
	m_bActive = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	strFileName ="";
}

CTabABL::~CTabABL()
{
}

void CTabABL::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabABL, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_LOADABLNEO, OnBnClickedButtonLoadablneo)
	ON_BN_CLICKED(IDC_BUTTON_LOADABL, OnBnClickedButtonLoadabl)
	ON_BN_CLICKED(IDC_BUTTON_SAVEABL, OnBnClickedButtonSaveabl)
	ON_BN_CLICKED(IDC_BUTTON_NEWABL, OnBnClickedButtonNewabl)
END_MESSAGE_MAP()


// CTabABL message handlers
BOOL CTabABL::OnInitDialog()
{
	CPropertyPage::OnInitDialog();	
	m_bDlgInit = TRUE;

	if (!m_bActive)
	{
		SetWin_Combo_Init ( this, IDC_COMBO_TYPE, DUMMYDATA::m_CharType, PIECE_SIZE );
		SetWin_Combo_Init ( this, IDC_COMBO_SLOT, DUMMYDATA::m_SlotType, EMPEACE_WEAPON_SIZE );
		SetWin_ShowWindow ( this, IDC_BUTTON_SAVEABL, SW_HIDE );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTabABL::OnBnClickedButtonLoadablneo()
{
	CString szFilterInput = "ABL|*.abl|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	Reset();
	BOOL bOK = m_pAblCode.LoadFileNeo ( dlgInput.GetFileName() );

	if ( bOK )
	{
		SetWin_Text ( this, IDC_EDIT_FILENAME, dlgInput.GetFileName() );
		strFileName = dlgInput.GetFileName();
		UpdateData ();
		m_bActive = TRUE;
		SetWin_ShowWindow ( this, IDC_BUTTON_SAVEABL, SW_SHOW );
		m_pToolTab->AddHistoryOpen( "ABL Editor (NEO)",dlgInput.GetFileName().GetString() );
	}
	else
	{
		MessageBox ( "Failure to Load :(" );
		m_pToolTab->AddHistoryOpenFail( "ABL Editor (NEO)",dlgInput.GetFileName().GetString() );
	}
}

void CTabABL::OnBnClickedButtonLoadabl()
{
	CString szFilterInput = "ABL|*.abl|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	Reset();
	BOOL bOK = m_pAblCode.LoadFile ( dlgInput.GetFileName() );

	if ( bOK )
	{
		SetWin_Text ( this, IDC_EDIT_FILENAME, dlgInput.GetFileName() );
		strFileName = dlgInput.GetFileName();
		UpdateData ();
		m_bActive = TRUE;
		SetWin_ShowWindow ( this, IDC_BUTTON_SAVEABL, SW_SHOW );
		m_pToolTab->AddHistoryOpen( "ABL Editor (OFFICIAL)",dlgInput.GetFileName().GetString() );
	}
	else
	{
		MessageBox ( "Failure to Load :(" );
		m_pToolTab->AddHistoryOpenFail( "ABL Editor (OFFICIAL)",dlgInput.GetFileName().GetString() );
	}
}

void CTabABL::OnBnClickedButtonNewabl()
{
	Reset();
	SetWin_ShowWindow ( this, IDC_BUTTON_SAVEABL, SW_SHOW );
	SetWin_Text ( this, IDC_EDIT_FILENAME, "" );
	m_bActive = TRUE;
}

void CTabABL::OnBnClickedButtonSaveabl()
{
	if ( SaveData () )
	{
		CString szFilter = "ABL File (*.abl)|*.abl|";
		CFileDialog dlg(FALSE,".abl",strFileName.GetString(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CTabABL*)this);

		dlg.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath();
		if ( dlg.DoModal() == IDOK )
		{
			BOOL bOK = m_pAblCode.SaveFile ( dlg.GetFileName() );
			if ( bOK )
			{
				SetWin_Text ( this, IDC_EDIT_FILENAME, dlg.GetFileName() );
				MessageBox ( "Save Done :P" );
				m_pToolTab->AddHistorySave( "ABL Editor",dlg.GetFileName().GetString() );
			}
			else
			{
				MessageBox ( "Failure to Save :(" );
				m_pToolTab->AddHistorySaveFail( "ABL Editor",dlg.GetFileName().GetString() );
			}
		}
	}
}

BOOL	CTabABL::UpdateData ()
{
	SetWin_Text ( this, IDC_EDIT_ABFFILE, m_pAblCode.m_strAbf.c_str() );
	SetWin_Text ( this, IDC_EDIT_CPSFILE, m_pAblCode.m_strCPS.c_str() );
	SetWin_Text ( this, IDC_EDIT_SKEFILE, m_pAblCode.m_strSkeleton.c_str() );
	SetWin_Text ( this, IDC_EDIT_BONELINK, m_pAblCode.m_strBoneLink.c_str() );
	SetWin_Combo_Sel ( this, IDC_COMBO_TYPE, (int)m_pAblCode.m_dwType );
	SetWin_Combo_Sel ( this, IDC_COMBO_SLOT, (int)m_pAblCode.m_dwWeaponSlot );
	SetWin_Num_float( this, IDC_EDIT_ROTX, m_pAblCode.m_fRotX );
	SetWin_Num_float( this, IDC_EDIT_ROTY, m_pAblCode.m_fRotY );
	SetWin_Num_float( this, IDC_EDIT_ROTZ, m_pAblCode.m_fRotZ );
	SetWin_Num_float( this, IDC_EDIT_ROOTX, m_pAblCode.m_fRootX );
	SetWin_Num_float( this, IDC_EDIT_ROOTY, m_pAblCode.m_fRootY );
	SetWin_Num_float( this, IDC_EDIT_ROOTZ, m_pAblCode.m_fRootZ );
	SetWin_Num_float( this, IDC_EDIT_ROTXF, m_pAblCode.m_fRotX_F );
	SetWin_Num_float( this, IDC_EDIT_ROTYF, m_pAblCode.m_fRotY_F );
	SetWin_Num_float( this, IDC_EDIT_ROTZF, m_pAblCode.m_fRotZ_F );
	SetWin_Num_float( this, IDC_EDIT_ROOTXF, m_pAblCode.m_fRootX_F );
	SetWin_Num_float( this, IDC_EDIT_ROOTYF, m_pAblCode.m_fRootY_F );
	SetWin_Num_float( this, IDC_EDIT_ROOTZF, m_pAblCode.m_fRootZ_F );
	SetWin_Check ( this, IDC_CHECK_BCPS, m_pAblCode.m_bCPS );

	return TRUE;
}

BOOL	CTabABL::SaveData ()
{
	m_pAblCode.m_strAbf = GetWin_Text ( this, IDC_EDIT_ABFFILE ).GetString();
	m_pAblCode.m_strCPS = GetWin_Text ( this, IDC_EDIT_CPSFILE ).GetString();
	m_pAblCode.m_strSkeleton = GetWin_Text ( this, IDC_EDIT_SKEFILE ).GetString();
	m_pAblCode.m_strBoneLink = GetWin_Text ( this, IDC_EDIT_BONELINK ).GetString();
	m_pAblCode.m_dwType = (EMPIECECHAR) GetWin_Combo_Sel ( this, IDC_COMBO_TYPE );
	m_pAblCode.m_dwWeaponSlot = (EMPEACEZONEWEAPON) GetWin_Combo_Sel ( this,  IDC_COMBO_SLOT );
	m_pAblCode.m_fRotX = GetWin_Num_float( this, IDC_EDIT_ROTX );
	m_pAblCode.m_fRotY = GetWin_Num_float( this, IDC_EDIT_ROTY );
	m_pAblCode.m_fRotZ = GetWin_Num_float( this, IDC_EDIT_ROTZ );
	m_pAblCode.m_fRootX = GetWin_Num_float( this, IDC_EDIT_ROOTX );
	m_pAblCode.m_fRootY = GetWin_Num_float( this, IDC_EDIT_ROOTY );
	m_pAblCode.m_fRootZ = GetWin_Num_float( this, IDC_EDIT_ROOTZ );
	m_pAblCode.m_fRotX_F = GetWin_Num_float( this, IDC_EDIT_ROTXF );
	m_pAblCode.m_fRotY_F = GetWin_Num_float( this, IDC_EDIT_ROTYF );
	m_pAblCode.m_fRotZ_F = GetWin_Num_float( this, IDC_EDIT_ROTZF );
	m_pAblCode.m_fRootX_F = GetWin_Num_float( this, IDC_EDIT_ROOTXF );
	m_pAblCode.m_fRootY_F = GetWin_Num_float( this, IDC_EDIT_ROOTYF );
	m_pAblCode.m_fRootZ_F = GetWin_Num_float( this, IDC_EDIT_ROOTZF );

	if ( strcmp( m_pAblCode.m_strCPS.c_str() , _T("") ) != 0 )
	{
		m_pAblCode.m_bCPS = TRUE;
	}

	return TRUE;
}

void CTabABL::Reset()
{
	SetWin_Text ( this, IDC_EDIT_FILENAME, "" );
	m_pAblCode.Reset();
	SetWin_ShowWindow ( this, IDC_BUTTON_SAVEABL, SW_HIDE );
	m_bActive = FALSE;
	UpdateData();
}

