// TabCFG.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "TabCFG.h"
#include "ToolTab.h"
#include "DummyData.h"
#include "../../EngineLib/Meshs/DxSkinAniMan.h"
#include "../../EngineLib/Meshs/SAnimation.h"
#include "../../EngineSoundLib/DxSound/DxSoundMan.h"
#include "../DxEffect/EffAni/DxEffAni.h"
#include "../DxEffect/EffAni/DxEffAniSingle.h"
#include "DxAniBoneScale.h"
#include "EtcFunction.h"

#include "ZEffTab.h"

#include ".\tabcfg.h"

// CTabCFG dialog

IMPLEMENT_DYNAMIC(CTabCFG, CPropertyPage)
CTabCFG::CTabCFG(LOGFONT logfont)
	: CPropertyPage(CTabCFG::IDD)
	,m_pFont( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	strFileName ="";
}

CTabCFG::~CTabCFG()
{
}

void CTabCFG::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SCALE, m_list_scale );
	DDX_Control(pDX, IDC_LIST_SCDATA, m_list_data );
}


BEGIN_MESSAGE_MAP(CTabCFG, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BTN_SC_ADD, OnBnClickedBtnScAdd)
	ON_BN_CLICKED(IDC_BTN_SC_EDIT, OnBnClickedBtnScEdit)
	ON_BN_CLICKED(IDC_BTN_SC_DEL, OnBnClickedBtnScDel)
	ON_BN_CLICKED(IDC_BTN_SC_CLEAR, OnBnClickedBtnScClear)
	ON_BN_CLICKED(IDC_BTN_SC_OK, OnBnClickedBtnScOk)
	ON_BN_CLICKED(IDC_BTN_SC_CAN, OnBnClickedBtnScCan)
	ON_BN_CLICKED(IDC_BTN_SCM_ADD, OnBnClickedBtnScmAdd)
	ON_BN_CLICKED(IDC_BTN_SCM_EDIT, OnBnClickedBtnScmEdit)
	ON_BN_CLICKED(IDC_BTN_SCM_DEL, OnBnClickedBtnScmDel)
	ON_BN_CLICKED(IDC_BTN_SCM_CLEAR, OnBnClickedBtnScmClear)
	ON_BN_CLICKED(IDC_BTN_SCM_OK, OnBnClickedBtnScmOk)
	ON_BN_CLICKED(IDC_BTN_SCM_CAN, OnBnClickedBtnScmCan)
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnBnClickedButtonNew)
END_MESSAGE_MAP()


// CTabCFG message handlers
BOOL CTabCFG::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	if (!m_bActive)
	{
		SetWin_Combo_Init ( this, IDC_COMBO_ANIMAIN, DUMMYDATA::m_AniMain, AN_TYPE_SIZE );
		SetWin_Combo_Init ( this, IDC_COMBO_ANISUB, DUMMYDATA::m_AniSub, AN_SUB_00_SIZE );

		SetWin_Combo_Init ( this, IDC_COMBO_PIECE0, DUMMYDATA::m_CharType, PIECE_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_PIECE1, DUMMYDATA::m_CharType, PIECE_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_PIECE2, DUMMYDATA::m_CharType, PIECE_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_PIECE3, DUMMYDATA::m_CharType, PIECE_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_PIECE4, DUMMYDATA::m_CharType, PIECE_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_PIECE5, DUMMYDATA::m_CharType, PIECE_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_PIECE6, DUMMYDATA::m_CharType, PIECE_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_PIECE7, DUMMYDATA::m_CharType, PIECE_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_PIECE8, DUMMYDATA::m_CharType, PIECE_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_PIECE9, DUMMYDATA::m_CharType, PIECE_SIZE);

		SetWin_Combo_Init ( this, IDC_COMBO_EFF0, DUMMYDATA::m_StrikeEff, EMSF_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_EFF1, DUMMYDATA::m_StrikeEff, EMSF_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_EFF2, DUMMYDATA::m_StrikeEff, EMSF_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_EFF3, DUMMYDATA::m_StrikeEff, EMSF_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_EFF4, DUMMYDATA::m_StrikeEff, EMSF_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_EFF5, DUMMYDATA::m_StrikeEff, EMSF_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_EFF6, DUMMYDATA::m_StrikeEff, EMSF_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_EFF7, DUMMYDATA::m_StrikeEff, EMSF_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_EFF8, DUMMYDATA::m_StrikeEff, EMSF_SIZE);
		SetWin_Combo_Init ( this, IDC_COMBO_EFF9, DUMMYDATA::m_StrikeEff, EMSF_SIZE);

		SetWin_ShowWindow ( this, IDC_BUTTON_SAVE, SW_HIDE );

		CRect SheetRect;
		CWnd *pWnd;
		pWnd = GetDlgItem ( IDC_STATIC_ANIEFF );
		pWnd->GetWindowRect ( SheetRect );
		ScreenToClient ( &SheetRect );

		LOGFONT logfont = {0};

		CFont* pFont = GetFont();
		if ( pFont ) pFont->GetLogFont( &logfont );

		m_pEffTab = new AEffTab ( SheetRect, logfont, this );
		m_pEffTab->Create( this, WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0 );
		m_pEffTab->ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTabCFG::OnBnClickedButtonLoad()
{
	CString szFilterInput = "CFG|*.cfg|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	Reset();
	BOOL bOK = m_AniInfo.LoadFileTool( dlgInput.GetFileName());

	if ( bOK )
	{
		SetWin_Text ( this, IDC_EDIT_FILENAME2, dlgInput.GetFileName() );
		strFileName = dlgInput.GetFileName();
		UpdateData();
		m_bActive = TRUE;
		SetWin_ShowWindow ( this, IDC_BUTTON_SAVE, SW_SHOW );
		m_pToolTab->AddHistoryOpen( "CFG Editor",dlgInput.GetFileName().GetString() );
	}
	else
	{
		MessageBox ( "Failure to Load :(" );
		m_pToolTab->AddHistoryOpenFail( "CFG Editor",dlgInput.GetFileName().GetString() );
	}
}

void CTabCFG::OnBnClickedButtonSave()
{
	if ( SaveData () )
	{
		CString szFilter = "CFG File (*.cfg)|*.cfg|";
		CFileDialog dlg(FALSE,".cfg",strFileName.GetString(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CTabCFG*)this);

		dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
		if ( dlg.DoModal() == IDOK )
		{
			BOOL bOK = m_AniInfo.SaveFile ( dlg.GetFileName() );
			if ( bOK )
			{
				SetWin_Text ( this, IDC_EDIT_FILENAME2, dlg.GetFileName() );
				MessageBox ( "Save Done :P" );
				m_pToolTab->AddHistorySave( "CFG Editor",dlg.GetFileName().GetString() );
			}
			else
			{
				MessageBox ( "Failure to Save :(" );
				m_pToolTab->AddHistorySaveFail( "CFG Editor",dlg.GetFileName().GetString() );
			}
		}
	}
}

void CTabCFG::OnBnClickedButtonNew()
{
	Reset();
	SetWin_ShowWindow ( this, IDC_BUTTON_SAVE, SW_SHOW );
	SetWin_Text ( this, IDC_EDIT_FILENAME2, "" );
	m_bActive = TRUE;
}

void CTabCFG::UpdateData()
{
	SetWin_Text ( this, IDC_EDIT_NAME, m_AniInfo.m_szName );
	SetWin_Text ( this, IDC_EDIT_SKELNAME, m_AniInfo.m_szSkeletion );
	//SetWin_Num_int ( this, IDC_EDIT_DWFLAG, m_AniInfo.m_dwFlag);

	SetWin_Check ( this, IDC_CHECK_AFLAG1, m_AniInfo.m_dwFlag&ACF_NEWINFO );
	SetWin_Check ( this, IDC_CHECK_AFLAG2, m_AniInfo.m_dwFlag&ACF_LOOP );
	SetWin_Check ( this, IDC_CHECK_AFLAG3, m_AniInfo.m_dwFlag&ACF_UPBODY );
	SetWin_Check ( this, IDC_CHECK_AFLAG4, m_AniInfo.m_dwFlag&ACF_DOWNBODY );

	SetWin_Num_int ( this, IDC_EDIT_DWSTIME, m_AniInfo.m_dwSTime);
	SetWin_Num_int ( this, IDC_EDIT_DWETIME, m_AniInfo.m_dwETime);
	SetWin_Num_int ( this, IDC_EDIT_DWETIMEORIG, m_AniInfo.m_dwETimeOrig);
	SetWin_Num_int ( this, IDC_EDIT_DWUNITTIME, m_AniInfo.m_UNITTIME);
	SetWin_Combo_Sel ( this, IDC_COMBO_ANIMAIN, (int)m_AniInfo.m_MainType );
	SetWin_Num_int ( this, IDC_EDIT_ANIM, m_AniInfo.m_MainType);
	SetWin_Combo_Sel ( this, IDC_COMBO_ANISUB, (int)m_AniInfo.m_SubType );
	SetWin_Num_int ( this, IDC_EDIT_ANIS, m_AniInfo.m_SubType);
	SetWin_Num_int ( this, IDC_EDIT_DIVCOUNT, m_AniInfo.m_wDivCount);

	SetWin_Num_int ( this, IDC_EDIT_DIV0, m_AniInfo.m_wDivFrame[0]);
	SetWin_Num_int ( this, IDC_EDIT_DIV1, m_AniInfo.m_wDivFrame[1]);
	SetWin_Num_int ( this, IDC_EDIT_DIV2, m_AniInfo.m_wDivFrame[2]);
	SetWin_Num_int ( this, IDC_EDIT_DIV3, m_AniInfo.m_wDivFrame[3]);
	SetWin_Num_int ( this, IDC_EDIT_DIV4, m_AniInfo.m_wDivFrame[4]);
	SetWin_Num_int ( this, IDC_EDIT_DIV5, m_AniInfo.m_wDivFrame[5]);
	SetWin_Num_int ( this, IDC_EDIT_DIV6, m_AniInfo.m_wDivFrame[6]);
	SetWin_Num_int ( this, IDC_EDIT_DIV7, m_AniInfo.m_wDivFrame[7]);
	SetWin_Num_int ( this, IDC_EDIT_DIV8, m_AniInfo.m_wDivFrame[8]);

	SetWin_Num_int ( this, IDC_EDIT_STRIKECOUNT, m_AniInfo.m_wStrikeCount);
	SetWin_Combo_Sel ( this, IDC_COMBO_PIECE0, (int)m_AniInfo.m_sStrikeEff[0].m_emPiece);
	SetWin_Combo_Sel ( this, IDC_COMBO_PIECE1, (int)m_AniInfo.m_sStrikeEff[1].m_emPiece);
	SetWin_Combo_Sel ( this, IDC_COMBO_PIECE2, (int)m_AniInfo.m_sStrikeEff[2].m_emPiece);
	SetWin_Combo_Sel ( this, IDC_COMBO_PIECE3, (int)m_AniInfo.m_sStrikeEff[3].m_emPiece);
	SetWin_Combo_Sel ( this, IDC_COMBO_PIECE4, (int)m_AniInfo.m_sStrikeEff[4].m_emPiece);
	SetWin_Combo_Sel ( this, IDC_COMBO_PIECE5, (int)m_AniInfo.m_sStrikeEff[5].m_emPiece);
	SetWin_Combo_Sel ( this, IDC_COMBO_PIECE6, (int)m_AniInfo.m_sStrikeEff[6].m_emPiece);
	SetWin_Combo_Sel ( this, IDC_COMBO_PIECE7, (int)m_AniInfo.m_sStrikeEff[7].m_emPiece);
	SetWin_Combo_Sel ( this, IDC_COMBO_PIECE8, (int)m_AniInfo.m_sStrikeEff[8].m_emPiece);
	SetWin_Combo_Sel ( this, IDC_COMBO_PIECE9, (int)m_AniInfo.m_sStrikeEff[9].m_emPiece);

	SetWin_Combo_Sel ( this, IDC_COMBO_EFF0, (int)m_AniInfo.m_sStrikeEff[0].m_emEffect);
	SetWin_Combo_Sel ( this, IDC_COMBO_EFF1, (int)m_AniInfo.m_sStrikeEff[1].m_emEffect);
	SetWin_Combo_Sel ( this, IDC_COMBO_EFF2, (int)m_AniInfo.m_sStrikeEff[2].m_emEffect);
	SetWin_Combo_Sel ( this, IDC_COMBO_EFF3, (int)m_AniInfo.m_sStrikeEff[3].m_emEffect);
	SetWin_Combo_Sel ( this, IDC_COMBO_EFF4, (int)m_AniInfo.m_sStrikeEff[4].m_emEffect);
	SetWin_Combo_Sel ( this, IDC_COMBO_EFF5, (int)m_AniInfo.m_sStrikeEff[5].m_emEffect);
	SetWin_Combo_Sel ( this, IDC_COMBO_EFF6, (int)m_AniInfo.m_sStrikeEff[6].m_emEffect);
	SetWin_Combo_Sel ( this, IDC_COMBO_EFF7, (int)m_AniInfo.m_sStrikeEff[7].m_emEffect);
	SetWin_Combo_Sel ( this, IDC_COMBO_EFF8, (int)m_AniInfo.m_sStrikeEff[8].m_emEffect);
	SetWin_Combo_Sel ( this, IDC_COMBO_EFF9, (int)m_AniInfo.m_sStrikeEff[9].m_emEffect);

	SetWin_Num_int ( this, IDC_EDIT_SFRAME0,m_AniInfo.m_sStrikeEff[0].m_dwFrame );
	SetWin_Num_int ( this, IDC_EDIT_SFRAME1,m_AniInfo.m_sStrikeEff[1].m_dwFrame );
	SetWin_Num_int ( this, IDC_EDIT_SFRAME2,m_AniInfo.m_sStrikeEff[2].m_dwFrame );
	SetWin_Num_int ( this, IDC_EDIT_SFRAME3,m_AniInfo.m_sStrikeEff[3].m_dwFrame );
	SetWin_Num_int ( this, IDC_EDIT_SFRAME4,m_AniInfo.m_sStrikeEff[4].m_dwFrame );
	SetWin_Num_int ( this, IDC_EDIT_SFRAME5,m_AniInfo.m_sStrikeEff[5].m_dwFrame );
	SetWin_Num_int ( this, IDC_EDIT_SFRAME6,m_AniInfo.m_sStrikeEff[6].m_dwFrame );
	SetWin_Num_int ( this, IDC_EDIT_SFRAME7,m_AniInfo.m_sStrikeEff[7].m_dwFrame );
	SetWin_Num_int ( this, IDC_EDIT_SFRAME8,m_AniInfo.m_sStrikeEff[8].m_dwFrame );
	SetWin_Num_int ( this, IDC_EDIT_SFRAME9,m_AniInfo.m_sStrikeEff[9].m_dwFrame );

	SetWin_Num_int ( this, IDC_EDIT_FRAMECOUNT, m_AniInfo.m_ChaSoundData.m_PlayFrameCount);
	SetWin_Text ( this, IDC_EDIT_SOUND0, m_AniInfo.m_ChaSoundData.m_szFileName[0]);
	SetWin_Text ( this, IDC_EDIT_SOUND1, m_AniInfo.m_ChaSoundData.m_szFileName[1]);
	SetWin_Text ( this, IDC_EDIT_SOUND2, m_AniInfo.m_ChaSoundData.m_szFileName[2]);
	SetWin_Text ( this, IDC_EDIT_SOUND3, m_AniInfo.m_ChaSoundData.m_szFileName[3]);
	SetWin_Text ( this, IDC_EDIT_SOUND4, m_AniInfo.m_ChaSoundData.m_szFileName[4]);
	SetWin_Text ( this, IDC_EDIT_SOUND5, m_AniInfo.m_ChaSoundData.m_szFileName[5]);
	SetWin_Text ( this, IDC_EDIT_SOUND6, m_AniInfo.m_ChaSoundData.m_szFileName[6]);
	SetWin_Text ( this, IDC_EDIT_SOUND7, m_AniInfo.m_ChaSoundData.m_szFileName[7]);
	SetWin_Text ( this, IDC_EDIT_SOUND8, m_AniInfo.m_ChaSoundData.m_szFileName[8]);
	SetWin_Text ( this, IDC_EDIT_SOUND9, m_AniInfo.m_ChaSoundData.m_szFileName[9]);

	SetWin_Check ( this, IDC_CHECK_LOOP0, (BOOL) m_AniInfo.m_ChaSoundData.m_bLoop[0] );
	SetWin_Check ( this, IDC_CHECK_LOOP1, (BOOL) m_AniInfo.m_ChaSoundData.m_bLoop[1] );
	SetWin_Check ( this, IDC_CHECK_LOOP2, (BOOL) m_AniInfo.m_ChaSoundData.m_bLoop[2] );
	SetWin_Check ( this, IDC_CHECK_LOOP3, (BOOL) m_AniInfo.m_ChaSoundData.m_bLoop[3] );
	SetWin_Check ( this, IDC_CHECK_LOOP4, (BOOL) m_AniInfo.m_ChaSoundData.m_bLoop[4] );
	SetWin_Check ( this, IDC_CHECK_LOOP5, (BOOL) m_AniInfo.m_ChaSoundData.m_bLoop[5] );
	SetWin_Check ( this, IDC_CHECK_LOOP6, (BOOL) m_AniInfo.m_ChaSoundData.m_bLoop[6] );
	SetWin_Check ( this, IDC_CHECK_LOOP7, (BOOL) m_AniInfo.m_ChaSoundData.m_bLoop[7] );
	SetWin_Check ( this, IDC_CHECK_LOOP8, (BOOL) m_AniInfo.m_ChaSoundData.m_bLoop[8] );
	SetWin_Check ( this, IDC_CHECK_LOOP9, (BOOL) m_AniInfo.m_ChaSoundData.m_bLoop[9] );

	SetWin_Num_int ( this, IDC_EDIT_PFRAME0, m_AniInfo.m_ChaSoundData.m_PlayFrame[0]);
	SetWin_Num_int ( this, IDC_EDIT_PFRAME1, m_AniInfo.m_ChaSoundData.m_PlayFrame[1]);
	SetWin_Num_int ( this, IDC_EDIT_PFRAME2, m_AniInfo.m_ChaSoundData.m_PlayFrame[2]);
	SetWin_Num_int ( this, IDC_EDIT_PFRAME3, m_AniInfo.m_ChaSoundData.m_PlayFrame[3]);
	SetWin_Num_int ( this, IDC_EDIT_PFRAME4, m_AniInfo.m_ChaSoundData.m_PlayFrame[4]);
	SetWin_Num_int ( this, IDC_EDIT_PFRAME5, m_AniInfo.m_ChaSoundData.m_PlayFrame[5]);
	SetWin_Num_int ( this, IDC_EDIT_PFRAME6, m_AniInfo.m_ChaSoundData.m_PlayFrame[6]);
	SetWin_Num_int ( this, IDC_EDIT_PFRAME7, m_AniInfo.m_ChaSoundData.m_PlayFrame[7]);
	SetWin_Num_int ( this, IDC_EDIT_PFRAME8, m_AniInfo.m_ChaSoundData.m_PlayFrame[8]);
	SetWin_Num_int ( this, IDC_EDIT_PFRAME9, m_AniInfo.m_ChaSoundData.m_PlayFrame[9]);
	SetWin_Num_int ( this, IDC_EDIT_PFRAME10, m_AniInfo.m_ChaSoundData.m_PlayFrame[10]);

	m_pEffTab->ActiveEffList( m_AniInfo.m_listEffAni );

	UpdateListScale();
}

BOOL CTabCFG::SaveData()
{
	StringCchCopy( m_AniInfo.m_szName, ACF_SZNAME, GetWin_Text( this, IDC_EDIT_NAME ).GetString() );
	StringCchCopy( m_AniInfo.m_szSkeletion, ACF_SZNAME, GetWin_Text( this, IDC_EDIT_SKELNAME).GetString() );

	//m_AniInfo.m_dwFlag = GetWin_Num_int ( this, IDC_EDIT_DWFLAG );

	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG1 ), m_AniInfo.m_dwFlag,ACF_NEWINFO );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG2 ), m_AniInfo.m_dwFlag,ACF_LOOP );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG3 ), m_AniInfo.m_dwFlag,ACF_UPBODY );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_AFLAG4 ), m_AniInfo.m_dwFlag,ACF_DOWNBODY );

	m_AniInfo.m_dwSTime = GetWin_Num_int ( this, IDC_EDIT_DWSTIME );
	m_AniInfo.m_dwETime = GetWin_Num_int ( this, IDC_EDIT_DWETIME );
	m_AniInfo.m_dwETimeOrig = GetWin_Num_int ( this, IDC_EDIT_DWETIMEORIG );
	m_AniInfo.m_UNITTIME = GetWin_Num_int ( this, IDC_EDIT_DWUNITTIME );
	m_AniInfo.m_MainType = (EMANI_MAINTYPE) GetWin_Combo_Sel ( this, IDC_COMBO_ANIMAIN );
	m_AniInfo.m_SubType = (EMANI_SUBTYPE) GetWin_Combo_Sel ( this, IDC_COMBO_ANISUB );
	m_AniInfo.m_wDivCount = GetWin_Num_int ( this, IDC_EDIT_DIVCOUNT );
	m_AniInfo.m_wDivFrame[0] = GetWin_Num_int ( this, IDC_EDIT_DIV0 );
	m_AniInfo.m_wDivFrame[1] = GetWin_Num_int ( this, IDC_EDIT_DIV1 );
	m_AniInfo.m_wDivFrame[2] = GetWin_Num_int ( this, IDC_EDIT_DIV2 );
	m_AniInfo.m_wDivFrame[3] = GetWin_Num_int ( this, IDC_EDIT_DIV3 );
	m_AniInfo.m_wDivFrame[4] = GetWin_Num_int ( this, IDC_EDIT_DIV4 );
	m_AniInfo.m_wDivFrame[5] = GetWin_Num_int ( this, IDC_EDIT_DIV5 );
	m_AniInfo.m_wDivFrame[6] = GetWin_Num_int ( this, IDC_EDIT_DIV6 );
	m_AniInfo.m_wDivFrame[7] = GetWin_Num_int ( this, IDC_EDIT_DIV7 );
	m_AniInfo.m_wDivFrame[8] = GetWin_Num_int ( this, IDC_EDIT_DIV8 );
	m_AniInfo.m_wStrikeCount = GetWin_Num_int ( this, IDC_EDIT_STRIKECOUNT );

	m_AniInfo.m_sStrikeEff[0].m_emPiece = (EMPIECECHAR) GetWin_Combo_Sel ( this, IDC_COMBO_PIECE0 );
	m_AniInfo.m_sStrikeEff[1].m_emPiece = (EMPIECECHAR) GetWin_Combo_Sel ( this, IDC_COMBO_PIECE1 );
	m_AniInfo.m_sStrikeEff[2].m_emPiece = (EMPIECECHAR) GetWin_Combo_Sel ( this, IDC_COMBO_PIECE2 );
	m_AniInfo.m_sStrikeEff[3].m_emPiece = (EMPIECECHAR) GetWin_Combo_Sel ( this, IDC_COMBO_PIECE3 );
	m_AniInfo.m_sStrikeEff[4].m_emPiece = (EMPIECECHAR) GetWin_Combo_Sel ( this, IDC_COMBO_PIECE4 );
	m_AniInfo.m_sStrikeEff[5].m_emPiece = (EMPIECECHAR) GetWin_Combo_Sel ( this, IDC_COMBO_PIECE5 );
	m_AniInfo.m_sStrikeEff[6].m_emPiece = (EMPIECECHAR) GetWin_Combo_Sel ( this, IDC_COMBO_PIECE6 );
	m_AniInfo.m_sStrikeEff[7].m_emPiece = (EMPIECECHAR) GetWin_Combo_Sel ( this, IDC_COMBO_PIECE7 );
	m_AniInfo.m_sStrikeEff[8].m_emPiece = (EMPIECECHAR) GetWin_Combo_Sel ( this, IDC_COMBO_PIECE8 );
	m_AniInfo.m_sStrikeEff[9].m_emPiece = (EMPIECECHAR) GetWin_Combo_Sel ( this, IDC_COMBO_PIECE9 );
	
	m_AniInfo.m_sStrikeEff[0].m_emEffect = (EMSTRIKE_EFF) GetWin_Combo_Sel ( this, IDC_COMBO_EFF0 );
	m_AniInfo.m_sStrikeEff[1].m_emEffect = (EMSTRIKE_EFF) GetWin_Combo_Sel ( this, IDC_COMBO_EFF1 );
	m_AniInfo.m_sStrikeEff[2].m_emEffect = (EMSTRIKE_EFF) GetWin_Combo_Sel ( this, IDC_COMBO_EFF2 );
	m_AniInfo.m_sStrikeEff[3].m_emEffect = (EMSTRIKE_EFF) GetWin_Combo_Sel ( this, IDC_COMBO_EFF3 );
	m_AniInfo.m_sStrikeEff[4].m_emEffect = (EMSTRIKE_EFF) GetWin_Combo_Sel ( this, IDC_COMBO_EFF4 );
	m_AniInfo.m_sStrikeEff[5].m_emEffect = (EMSTRIKE_EFF) GetWin_Combo_Sel ( this, IDC_COMBO_EFF5 );
	m_AniInfo.m_sStrikeEff[6].m_emEffect = (EMSTRIKE_EFF) GetWin_Combo_Sel ( this, IDC_COMBO_EFF6 );
	m_AniInfo.m_sStrikeEff[7].m_emEffect = (EMSTRIKE_EFF) GetWin_Combo_Sel ( this, IDC_COMBO_EFF7 );
	m_AniInfo.m_sStrikeEff[8].m_emEffect = (EMSTRIKE_EFF) GetWin_Combo_Sel ( this, IDC_COMBO_EFF8 );
	m_AniInfo.m_sStrikeEff[9].m_emEffect = (EMSTRIKE_EFF) GetWin_Combo_Sel ( this, IDC_COMBO_EFF9 );

	m_AniInfo.m_sStrikeEff[0].m_dwFrame = GetWin_Num_int ( this, IDC_EDIT_SFRAME0 ); 
	m_AniInfo.m_sStrikeEff[1].m_dwFrame = GetWin_Num_int ( this, IDC_EDIT_SFRAME1 ); 
	m_AniInfo.m_sStrikeEff[2].m_dwFrame = GetWin_Num_int ( this, IDC_EDIT_SFRAME2 ); 
	m_AniInfo.m_sStrikeEff[3].m_dwFrame = GetWin_Num_int ( this, IDC_EDIT_SFRAME3 ); 
	m_AniInfo.m_sStrikeEff[4].m_dwFrame = GetWin_Num_int ( this, IDC_EDIT_SFRAME4 ); 
	m_AniInfo.m_sStrikeEff[5].m_dwFrame = GetWin_Num_int ( this, IDC_EDIT_SFRAME5 ); 
	m_AniInfo.m_sStrikeEff[6].m_dwFrame = GetWin_Num_int ( this, IDC_EDIT_SFRAME6 ); 
	m_AniInfo.m_sStrikeEff[7].m_dwFrame = GetWin_Num_int ( this, IDC_EDIT_SFRAME7 ); 
	m_AniInfo.m_sStrikeEff[8].m_dwFrame = GetWin_Num_int ( this, IDC_EDIT_SFRAME8 ); 
	m_AniInfo.m_sStrikeEff[9].m_dwFrame = GetWin_Num_int ( this, IDC_EDIT_SFRAME9 ); 


	m_AniInfo.m_ChaSoundData.m_PlayFrameCount = GetWin_Num_int ( this, IDC_EDIT_FRAMECOUNT );

	StringCchCopy( m_AniInfo.m_ChaSoundData.m_szFileName[0]	, 32, GetWin_Text( this, IDC_EDIT_SOUND0 ).GetString() );
	StringCchCopy( m_AniInfo.m_ChaSoundData.m_szFileName[1]	, 32, GetWin_Text( this, IDC_EDIT_SOUND1 ).GetString() );
	StringCchCopy( m_AniInfo.m_ChaSoundData.m_szFileName[2]	, 32, GetWin_Text( this, IDC_EDIT_SOUND2 ).GetString() );
	StringCchCopy( m_AniInfo.m_ChaSoundData.m_szFileName[3]	, 32, GetWin_Text( this, IDC_EDIT_SOUND3 ).GetString() );
	StringCchCopy( m_AniInfo.m_ChaSoundData.m_szFileName[4]	, 32, GetWin_Text( this, IDC_EDIT_SOUND4 ).GetString() );
	StringCchCopy( m_AniInfo.m_ChaSoundData.m_szFileName[5]	, 32, GetWin_Text( this, IDC_EDIT_SOUND5 ).GetString() );
	StringCchCopy( m_AniInfo.m_ChaSoundData.m_szFileName[6]	, 32, GetWin_Text( this, IDC_EDIT_SOUND6 ).GetString() );
	StringCchCopy( m_AniInfo.m_ChaSoundData.m_szFileName[7]	, 32, GetWin_Text( this, IDC_EDIT_SOUND7 ).GetString() );
	StringCchCopy( m_AniInfo.m_ChaSoundData.m_szFileName[8]	, 32, GetWin_Text( this, IDC_EDIT_SOUND8 ).GetString() );
	StringCchCopy( m_AniInfo.m_ChaSoundData.m_szFileName[9]	, 32, GetWin_Text( this, IDC_EDIT_SOUND9 ).GetString() );


	m_AniInfo.m_ChaSoundData.m_bLoop[0] = GetWin_Check ( this, IDC_CHECK_LOOP0 );
	m_AniInfo.m_ChaSoundData.m_bLoop[1] = GetWin_Check ( this, IDC_CHECK_LOOP1 );
	m_AniInfo.m_ChaSoundData.m_bLoop[2] = GetWin_Check ( this, IDC_CHECK_LOOP2 );
	m_AniInfo.m_ChaSoundData.m_bLoop[3] = GetWin_Check ( this, IDC_CHECK_LOOP3 );
	m_AniInfo.m_ChaSoundData.m_bLoop[4] = GetWin_Check ( this, IDC_CHECK_LOOP4 );
	m_AniInfo.m_ChaSoundData.m_bLoop[5] = GetWin_Check ( this, IDC_CHECK_LOOP5 );
	m_AniInfo.m_ChaSoundData.m_bLoop[6] = GetWin_Check ( this, IDC_CHECK_LOOP6 );
	m_AniInfo.m_ChaSoundData.m_bLoop[7] = GetWin_Check ( this, IDC_CHECK_LOOP7 );
	m_AniInfo.m_ChaSoundData.m_bLoop[8] = GetWin_Check ( this, IDC_CHECK_LOOP8 );
	m_AniInfo.m_ChaSoundData.m_bLoop[9] = GetWin_Check ( this, IDC_CHECK_LOOP9 );

	m_AniInfo.m_ChaSoundData.m_PlayFrame[0] = GetWin_Num_int ( this, IDC_EDIT_PFRAME0 );
	m_AniInfo.m_ChaSoundData.m_PlayFrame[1] = GetWin_Num_int ( this, IDC_EDIT_PFRAME1 );
	m_AniInfo.m_ChaSoundData.m_PlayFrame[2] = GetWin_Num_int ( this, IDC_EDIT_PFRAME2 );
	m_AniInfo.m_ChaSoundData.m_PlayFrame[3] = GetWin_Num_int ( this, IDC_EDIT_PFRAME3 );
	m_AniInfo.m_ChaSoundData.m_PlayFrame[4] = GetWin_Num_int ( this, IDC_EDIT_PFRAME4 );
	m_AniInfo.m_ChaSoundData.m_PlayFrame[5] = GetWin_Num_int ( this, IDC_EDIT_PFRAME5 );
	m_AniInfo.m_ChaSoundData.m_PlayFrame[6] = GetWin_Num_int ( this, IDC_EDIT_PFRAME6 );
	m_AniInfo.m_ChaSoundData.m_PlayFrame[7] = GetWin_Num_int ( this, IDC_EDIT_PFRAME7 );
	m_AniInfo.m_ChaSoundData.m_PlayFrame[8] = GetWin_Num_int ( this, IDC_EDIT_PFRAME8 );
	m_AniInfo.m_ChaSoundData.m_PlayFrame[9] = GetWin_Num_int ( this, IDC_EDIT_PFRAME9 );
	m_AniInfo.m_ChaSoundData.m_PlayFrame[10] = GetWin_Num_int ( this, IDC_EDIT_PFRAME10 );

	m_AniInfo.m_listEffAni = m_pEffTab->GetListEffect();

	return TRUE;
}

void CTabCFG::UpdateListScale()
{
	m_list_scale.ResetContent();

	CString strTemp;
	int nCount(0);
	DxAniScale::MAP_ANISCALEMAIN_ITER iter = m_AniInfo.m_pAniScale->m_mapAniScaleMain.begin();
	for( ; iter!=m_AniInfo.m_pAniScale->m_mapAniScaleMain.end(); ++iter, ++nCount )
	{
		strTemp.Format ("%d--Name:%s"
		,nCount
		,(*iter).first.c_str()
		);
		m_list_scale.InsertString(nCount, strTemp);
	}

	SetWin_ShowWindow ( this, IDC_EDIT_SCNAME, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_LIST_SCDATA, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_BTN_SC_OK, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_BTN_SC_CAN, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_BTN_SCM_ADD, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_BTN_SCM_EDIT, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_BTN_SCM_DEL, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_BTN_SCM_CLEAR, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_EDIT_SCM_KEY, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_EDIT_SCM_SCALE, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_BTN_SCM_OK, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_BTN_SCM_CAN, SW_HIDE);
}

void CTabCFG::OnBnClickedBtnScAdd()
{
	SetWin_ShowWindow ( this, IDC_EDIT_SCNAME, SW_SHOW);
	SetWin_ShowWindow ( this, IDC_LIST_SCDATA, SW_SHOW);
	SetWin_ShowWindow ( this, IDC_BTN_SC_OK, SW_SHOW);
	SetWin_ShowWindow ( this, IDC_BTN_SC_CAN, SW_SHOW);
	SetWin_ShowWindow ( this, IDC_BTN_SCM_ADD, SW_SHOW);
	SetWin_ShowWindow ( this, IDC_BTN_SCM_EDIT, SW_SHOW);
	SetWin_ShowWindow ( this, IDC_BTN_SCM_DEL, SW_SHOW);
	SetWin_ShowWindow ( this, IDC_BTN_SCM_CLEAR, SW_SHOW);

	bAddScale = true;
	pNewScale = new DxAniScaleMAIN;
	SetWin_Text ( this, IDC_EDIT_SCNAME ,"" );
	UpdateListData( pNewScale );
}

void CTabCFG::OnBnClickedBtnScEdit()
{
	int nIndex = m_list_scale.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		SetWin_ShowWindow ( this, IDC_EDIT_SCNAME, SW_SHOW);
		SetWin_ShowWindow ( this, IDC_LIST_SCDATA, SW_SHOW);
		SetWin_ShowWindow ( this, IDC_BTN_SC_OK, SW_SHOW);
		SetWin_ShowWindow ( this, IDC_BTN_SC_CAN, SW_SHOW);
		SetWin_ShowWindow ( this, IDC_BTN_SCM_ADD, SW_SHOW);
		SetWin_ShowWindow ( this, IDC_BTN_SCM_EDIT, SW_SHOW);
		SetWin_ShowWindow ( this, IDC_BTN_SCM_DEL, SW_SHOW);
		SetWin_ShowWindow ( this, IDC_BTN_SCM_CLEAR, SW_SHOW);

		int nCount(0);
		DxAniScale::MAP_ANISCALEMAIN_ITER iter = m_AniInfo.m_pAniScale->m_mapAniScaleMain.begin();
		for( ; iter!=m_AniInfo.m_pAniScale->m_mapAniScaleMain.end(); ++iter, ++nCount )
		{
			if ( nCount == nIndex )
			{
				SetWin_Text ( this, IDC_EDIT_SCNAME ,"" );
				SetWin_Text ( this, IDC_EDIT_SCNAME ,(*iter).first.c_str() );
				pNewScale = new DxAniScaleMAIN;
				pNewScale = (*iter).second;
				bAddScale = false;
				UpdateListData( pNewScale );
				nLastEditScale = nIndex;
			}
		}	
	}
}

void CTabCFG::OnBnClickedBtnScDel()
{
	int nIndex = m_list_scale.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		if ( MessageBox ( "Are you sure you want to Delete?", "Question", MB_YESNO ) == IDYES )
		{
			m_AniInfo.m_pAniScale->DeleteAniScale(nIndex);
			UpdateListScale();
		}
	}
}

void CTabCFG::OnBnClickedBtnScClear()
{
	if ( MessageBox ( "Are you sure you want to Delete All?", "Question", MB_YESNO ) == IDYES )
	{
		m_AniInfo.m_pAniScale->m_mapAniScaleMain.clear();
		UpdateListScale();
	}
}


void CTabCFG::OnBnClickedBtnScOk()
{
	if (!bAddScale)		m_AniInfo.m_pAniScale->DeleteAniScale(nLastEditScale);
	CString strTemScaleName = GetWin_Text( this, IDC_EDIT_SCNAME ).GetString();
	DxAniScale::MAP_ANISCALEMAIN_ITER iter = m_AniInfo.m_pAniScale->m_mapAniScaleMain.find( strTemScaleName.GetString() );

	if( iter != m_AniInfo.m_pAniScale->m_mapAniScaleMain.end() )	
	{
		MessageBox("Name Already Exist!","Error",MB_OK);
	}
	else
	{
		m_AniInfo.m_pAniScale->m_mapAniScaleMain.insert( std::make_pair( strTemScaleName.GetString(), pNewScale ) );
		UpdateListScale();
	}
	
}

void CTabCFG::OnBnClickedBtnScCan()
{
	UpdateListScale();
}

void CTabCFG::UpdateListData(DxAniScaleMAIN*	pData)
{
	m_list_data.ResetContent();
	CString strTemp;
	int nCount(0);
	DxAniScaleMAIN::MAP_ANISCALEDATA_ITER iter = pData->m_mapAniScaleData.begin();
	for( ; iter!=pData->m_mapAniScaleData.end(); ++iter, ++nCount )
	{
		strTemp.Format ("[Index:%d---Scale:%f"
		,(*iter).first
		,(*iter).second
		);
		m_list_data.InsertString(nCount, strTemp);
	}
	SetWin_ShowWindow ( this, IDC_EDIT_SCM_KEY, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_EDIT_SCM_SCALE, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_BTN_SCM_OK, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_BTN_SCM_CAN, SW_HIDE);
}

void CTabCFG::OnBnClickedBtnScmAdd()
{
	SetWin_ShowWindow ( this, IDC_EDIT_SCM_KEY, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_SCM_SCALE, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BTN_SCM_OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BTN_SCM_CAN, SW_SHOW );
	bAddData = true;
	SetWin_Num_int ( this, IDC_EDIT_SCM_KEY, 0 );
	SetWin_Num_float ( this, IDC_EDIT_SCM_SCALE, 0 );

	SetWin_ShowWindow ( this, IDC_BTN_SC_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BTN_SC_CAN, SW_HIDE );
}

void CTabCFG::OnBnClickedBtnScmEdit()
{
	int nIndex = m_list_data.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		SetWin_ShowWindow ( this, IDC_EDIT_SCM_KEY, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_SCM_SCALE, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_BTN_SCM_OK, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_BTN_SCM_CAN, SW_SHOW );
		bAddData = false;

		int nCount(0);
		DxAniScaleMAIN::MAP_ANISCALEDATA_ITER iter = pNewScale->m_mapAniScaleData.begin();
		for( ; iter!=pNewScale->m_mapAniScaleData.end(); ++iter, ++nCount )
		{
			if( nIndex==nCount )
			{
				SetWin_Num_int ( this, IDC_EDIT_SCM_KEY, (*iter).first);
				SetWin_Num_float ( this, IDC_EDIT_SCM_SCALE, (*iter).second );
				nLastEditData = nIndex;
			}
		}

		SetWin_ShowWindow ( this, IDC_BTN_SC_OK, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_BTN_SC_CAN, SW_HIDE );
	}
}

void CTabCFG::OnBnClickedBtnScmDel()
{
	int nIndex = m_list_data.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		if ( MessageBox ( "Are you sure you want to Delete?", "Question", MB_YESNO ) == IDYES )
		{
			pNewScale->DeleteData(nIndex);
			UpdateListData(pNewScale);
		}
	}
}

void CTabCFG::OnBnClickedBtnScmClear()
{
	if ( MessageBox ( "Are you sure you want to Delete ALL?", "Question", MB_YESNO ) == IDYES )
	{
		pNewScale->m_mapAniScaleData.clear();
		UpdateListData(pNewScale);
	}
}

void CTabCFG::OnBnClickedBtnScmOk()
{
	if (!bAddData)	pNewScale->DeleteData( nLastEditData );
	pNewScale->InsertData( GetWin_Num_int(this,IDC_EDIT_SCM_KEY ),GetWin_Num_float(this,IDC_EDIT_SCM_SCALE ) );
	UpdateListData(pNewScale);

	SetWin_ShowWindow ( this, IDC_BTN_SC_OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BTN_SC_CAN, SW_SHOW );
}

void CTabCFG::OnBnClickedBtnScmCan()
{
	UpdateListData(pNewScale);

	SetWin_ShowWindow ( this, IDC_BTN_SC_OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BTN_SC_CAN, SW_SHOW );
}

void CTabCFG::Reset()
{
	SetWin_Text ( this, IDC_EDIT_FILENAME2, "" );
	m_AniInfo.CleanUp();
	StringCchCopy( m_AniInfo.m_szName	, ACF_SZNAME, "" );
	StringCchCopy( m_AniInfo.m_szSkeletion	, ACF_SZNAME, "" );
		
	m_AniInfo.m_dwFlag = 0;
	m_AniInfo.m_dwSTime = 0;
	m_AniInfo.m_dwETime = 0;
	m_AniInfo.m_dwETimeOrig = 0;
	m_AniInfo.m_UNITTIME = 0;
	m_AniInfo.m_MainType = (EMANI_MAINTYPE) 0;
	m_AniInfo.m_SubType = (EMANI_SUBTYPE) 0;
	m_AniInfo.m_wDivCount = 0;

	for ( DWORD i=0; i<9; ++i )
	{
		m_AniInfo.m_wDivFrame[i] = 0;
	}

	m_AniInfo.m_wStrikeCount = 0;

	for ( DWORD i=0; i<10; ++i )
	{
		m_AniInfo.m_sStrikeEff[i].m_emPiece = (EMPIECECHAR) 0;
		m_AniInfo.m_sStrikeEff[i].m_emEffect = (EMSTRIKE_EFF) 0;
		m_AniInfo.m_sStrikeEff[i].m_dwFrame = 0;
	}

	m_AniInfo.m_ChaSoundData.m_PlayFrameCount = 0;

	for ( DWORD i=0; i<10; ++i )
	{
		StringCchCopy( m_AniInfo.m_ChaSoundData.m_szFileName[i]	, 32, "" );
		m_AniInfo.m_ChaSoundData.m_bLoop[i] = FALSE ;
	}

	for ( DWORD i=0; i<11; ++i )
	{
		m_AniInfo.m_ChaSoundData.m_PlayFrame[i] = 0;
	}

	SetWin_ShowWindow ( this, IDC_BUTTON_SAVE, SW_HIDE );
	m_bActive = FALSE;
	UpdateData();
}









