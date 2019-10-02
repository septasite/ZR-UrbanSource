// EditCFGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EditCFG.h"
#include "EditCFGDlg.h"
#include "../../EngineLib/Meshs/DxSkinAniMan.h"
#include "../../EngineLib/Meshs/SAnimation.h"
#include "../../EngineSoundLib/DxSound/DxSoundMan.h"
#include "../DxEffect/EffAni/DxEffAni.h"
#include ".\editcfgdlg.h"
#include "EtcFunction.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CEditCFGDlg dialog



CEditCFGDlg::CEditCFGDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditCFGDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEditCFGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEditCFGDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CEditCFGDlg message handlers

BOOL CEditCFGDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	SetWin_Combo_Init ( this, IDC_COMBO_ANIMAIN, DUMMY_TOOL_DATA::m_AniMain, AN_TYPE_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_ANISUB, DUMMY_TOOL_DATA::m_AniSub, AN_SUB_00_SIZE );

	SetWin_Combo_Init ( this, IDC_COMBO_PIECE0, DUMMY_TOOL_DATA::m_PieceNames, PIECE_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_PIECE1, DUMMY_TOOL_DATA::m_PieceNames, PIECE_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_PIECE2, DUMMY_TOOL_DATA::m_PieceNames, PIECE_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_PIECE3, DUMMY_TOOL_DATA::m_PieceNames, PIECE_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_PIECE4, DUMMY_TOOL_DATA::m_PieceNames, PIECE_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_PIECE5, DUMMY_TOOL_DATA::m_PieceNames, PIECE_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_PIECE6, DUMMY_TOOL_DATA::m_PieceNames, PIECE_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_PIECE7, DUMMY_TOOL_DATA::m_PieceNames, PIECE_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_PIECE8, DUMMY_TOOL_DATA::m_PieceNames, PIECE_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_PIECE9, DUMMY_TOOL_DATA::m_PieceNames, PIECE_SIZE);

	SetWin_Combo_Init ( this, IDC_COMBO_EFF0, DUMMY_TOOL_DATA::m_StrikeEff, EMSF_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_EFF1, DUMMY_TOOL_DATA::m_StrikeEff, EMSF_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_EFF2, DUMMY_TOOL_DATA::m_StrikeEff, EMSF_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_EFF3, DUMMY_TOOL_DATA::m_StrikeEff, EMSF_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_EFF4, DUMMY_TOOL_DATA::m_StrikeEff, EMSF_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_EFF5, DUMMY_TOOL_DATA::m_StrikeEff, EMSF_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_EFF6, DUMMY_TOOL_DATA::m_StrikeEff, EMSF_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_EFF7, DUMMY_TOOL_DATA::m_StrikeEff, EMSF_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_EFF8, DUMMY_TOOL_DATA::m_StrikeEff, EMSF_SIZE);
	SetWin_Combo_Init ( this, IDC_COMBO_EFF9, DUMMY_TOOL_DATA::m_StrikeEff, EMSF_SIZE);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEditCFGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEditCFGDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEditCFGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEditCFGDlg::OnBnClickedButtonLoad()
{
	CString szFilterInput = "CFG|*.cfg|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	BOOL bOK = m_AniInfo.LoadFile( dlgInput.GetFileName(),NULL);

	if ( bOK )
	{
		SetWindowText( dlgInput.GetFileName().GetString() );
		UpdateData();
	}
}

void CEditCFGDlg::OnBnClickedButtonSave()
{
	if ( SaveData () )
	{
		CString szFilter = "CFG File (*.cfg)|*.cfg|";
		CFileDialog dlg(FALSE,".cfg",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CEditCFGDlg*)this);

		dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
		if ( dlg.DoModal() == IDOK )
		{
			BOOL bOK = m_AniInfo.SaveFile ( dlg.GetFileName() );
			if ( bOK )
			{
				MessageBox ( "Save Done :P" );
			}
		}
	}
}

void CEditCFGDlg::UpdateData()
{
	SetWin_Text ( this, IDC_EDIT_NAME, m_AniInfo.m_szName );
	SetWin_Text ( this, IDC_EDIT_NAME2, m_AniInfo.m_szBin );
	SetWin_Text ( this, IDC_EDIT_SKELNAME, m_AniInfo.m_szSkeletion );

	SetWin_Num_int ( this, IDC_EDIT_DWFLAG, m_AniInfo.m_dwFlag);
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


}
BOOL CEditCFGDlg::SaveData()
{
	//m_AniInfo.m_szName = LPCTSTR (GetWin_Text( this, IDC_EDIT_NAME ).GetString());
	_tcscpy(m_AniInfo.m_szName, GetWin_Text( this, IDC_EDIT_NAME ).GetString()); 
	_tcscpy(m_AniInfo.m_szBin, GetWin_Text( this, IDC_EDIT_NAME2 ).GetString()); 
	//m_AniInfo.m_szSkeletion = GetWin_Text( this, IDC_EDIT_SKELNAME );
	_tcscpy(m_AniInfo.m_szSkeletion, GetWin_Text( this, IDC_EDIT_SKELNAME).GetString()); 

	m_AniInfo.m_dwFlag = GetWin_Num_int ( this, IDC_EDIT_DWFLAG );
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

	m_AniInfo.m_ChaSoundData.m_PlayFrameCount = GetWin_Num_int ( this, IDC_EDIT_FRAMECOUNT );

	//m_AniInfo.m_ChaSoundData.m_szFileName[0] = GetWin_Text( this, IDC_EDIT_SOUND0 );
	//m_AniInfo.m_ChaSoundData.m_szFileName[1] = GetWin_Text( this, IDC_EDIT_SOUND1 );
	//m_AniInfo.m_ChaSoundData.m_szFileName[2] = GetWin_Text( this, IDC_EDIT_SOUND2 );
	//m_AniInfo.m_ChaSoundData.m_szFileName[3] = GetWin_Text( this, IDC_EDIT_SOUND3 );
	//m_AniInfo.m_ChaSoundData.m_szFileName[4] = GetWin_Text( this, IDC_EDIT_SOUND4 );
	//m_AniInfo.m_ChaSoundData.m_szFileName[5] = GetWin_Text( this, IDC_EDIT_SOUND5 );
	//m_AniInfo.m_ChaSoundData.m_szFileName[6] = GetWin_Text( this, IDC_EDIT_SOUND6 );
	//m_AniInfo.m_ChaSoundData.m_szFileName[7] = GetWin_Text( this, IDC_EDIT_SOUND7 );
	//m_AniInfo.m_ChaSoundData.m_szFileName[8] = GetWin_Text( this, IDC_EDIT_SOUND8 );
	//m_AniInfo.m_ChaSoundData.m_szFileName[9] = GetWin_Text( this, IDC_EDIT_SOUND9 );

	_tcscpy(m_AniInfo.m_ChaSoundData.m_szFileName[0], GetWin_Text( this, IDC_EDIT_SOUND0 ).GetString()); 
	_tcscpy(m_AniInfo.m_ChaSoundData.m_szFileName[1], GetWin_Text( this, IDC_EDIT_SOUND1 ).GetString()); 
	_tcscpy(m_AniInfo.m_ChaSoundData.m_szFileName[2], GetWin_Text( this, IDC_EDIT_SOUND2 ).GetString()); 
	_tcscpy(m_AniInfo.m_ChaSoundData.m_szFileName[3], GetWin_Text( this, IDC_EDIT_SOUND3 ).GetString()); 
	_tcscpy(m_AniInfo.m_ChaSoundData.m_szFileName[4], GetWin_Text( this, IDC_EDIT_SOUND4 ).GetString()); 
	_tcscpy(m_AniInfo.m_ChaSoundData.m_szFileName[5], GetWin_Text( this, IDC_EDIT_SOUND5 ).GetString()); 
	_tcscpy(m_AniInfo.m_ChaSoundData.m_szFileName[6], GetWin_Text( this, IDC_EDIT_SOUND6 ).GetString()); 
	_tcscpy(m_AniInfo.m_ChaSoundData.m_szFileName[7], GetWin_Text( this, IDC_EDIT_SOUND7 ).GetString()); 
	_tcscpy(m_AniInfo.m_ChaSoundData.m_szFileName[8], GetWin_Text( this, IDC_EDIT_SOUND8 ).GetString()); 
	_tcscpy(m_AniInfo.m_ChaSoundData.m_szFileName[9], GetWin_Text( this, IDC_EDIT_SOUND9 ).GetString()); 


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

	return TRUE;
}


namespace DUMMY_TOOL_DATA
{
	std::string	m_PieceNames[PIECE_SIZE] =
	{
	_T("Piece Head"),
	_T("Piece Upbody"),
	_T("Piece LowBody"),
	_T("Piece Glove"),
	_T("Piece R-Hand"),
	_T("Piece L-Hand"),
	_T("Piece Foot"),
	_T("Pisce Hair"),
	_T("Piece Headgear"),
	_T("Piece Vehicle"),
	_T("Piece Wing"),
	_T("Piece Eff-UpBody"),
	_T("Piece Eff-LowBody"),
	_T("Piece Eff-Hand"),
	_T("Piece Eff-Foot"),
	_T("Piece Belt"),
	_T("Piece Accessory"),
	_T("Piece Neck"),
	_T("Piece Wrist"),
	_T("Piece R-Finger"),
	_T("Piece L-Finger"),
	_T("Piece R-Earring"),
	_T("Piece L-Earring"),
	_T("Piece REV01"),
	_T("Piece REV02"),
	_T("Piece REV03"),
	};

	std::string	m_StrikeEff[EMSF_SIZE] =
	{
		_T("EMSF_NULL"),
		_T("EMSF_SELFBODY"),
		_T("EMSF_TARGET"),
	};

	std::string	m_AniMain[AN_TYPE_SIZE] =
	{
		_T("AN_Guard_N------/Bike_Stay---------/ABL_Stay"),
		_T("AN_Placid-------/Bike_Walk---------/ABL_Attack"),
		_T("AN_Walk---------/Bike_Booster"),
		_T("AN_Run----------/Bike_Run"),
		_T("AN_Attack-------/Bike_Down"),
		_T("AN_Shock--------/Bike_Shock"),
		_T("AN_Die----------/Bike_Attack"),
		_T("AN_Create-------/Bike_Skill_A"),
		_T("AN_Talk---------/Bike_Skill_B"),
		_T("AN_Skill--------/Bike_Skill_C"),
		_T("AN_Gesture------/Bike_Skill_D"),
		_T("AN_Shock_Mix----/Bike_Anim001"),
		_T("AN_Guard_L------/Bike_Anim002"),
		_T("AN_Duel_Win-----/Bike_Anim003"),
		_T("AN_Duel_Loss----/Bike_Anim004"),
		_T("AN_Special------/Bike_Anim005"),
		_T("AN_Skill_B------/Bike_Anim_None"),
		_T("AN_Skill_C"),
		_T("AN_Skill_D"),
		_T("AN_Skill_E"),
		_T("AN_Gathering"),
		_T("AN_Bike_A"),
		_T("AN_Bike_B"),
		_T("AN_Bike_C"),
		_T("AN_Bike_EV1"),
		_T("AN_Flight"),
		_T("AN_Skill_F"),
		_T("AN_Skill_G"),
		_T("AN_Skill_H"),
		_T("AN_Ferrari"),
		_T("AN_Ewan1"),
		_T("AN_Ewan2"),
		_T("AN_Ewan3"),
		_T("AN_Rearcar"),
		_T("AN_Ewan4"),
		_T("AN_Ewan5"),
		_T("AN_Ewan6"),
		_T("AN_Ewan7"),
		_T("AN_Ewan8"),
		_T("AN_Ewan9"),
		_T("AN_Ewan10"),
		_T("AN_Ewan11"),
		_T("AN_Ewan12"),
		_T("AN_Ewan13"),
		_T("AN_Ewan14"),
		_T("AN_Ewan15"),
		_T("AN_Ewan16"),
		_T("AN_Ewan17"),
		_T("AN_Ewan18"),
		_T("AN_Ewan19"),
		_T("AN_Ewan20"),
		_T("AN_Ewan21"),
		_T("AN_Ewan22"),
		_T("AN_Ewan23"),
		_T("AN_Ewan24"),
		_T("AN_Ewan25"),
		_T("AN_Ewan26"),
		_T("AN_Ewan27"),
		_T("AN_Ewan28"),
		_T("AN_Ewan29"),
		_T("AN_Ewan30")
	};
	std::string	m_AniSub[AN_SUB_00_SIZE] =
	{
		_T("Sub00----/Sub_None-----------/01_Board"),
		_T("Sub01----/Sub_OneHandSword---/01_Stand"),
		_T("Sub02----/Sub_TwoHandSword---/01_Walk"),
		_T("Sub03----/Sub_BothSword------/01_Run"),
		_T("Sub04----/Sub_Dagger---------/01_Boost"),
		_T("Sub05----/Sub_Spear----------/01_Death"),
		_T("Sub06----/Sub_Bow------------/02_Board"),
		_T("Sub07----/Sub_Throw----------/02_Stand"),
		_T("Sub08----/Sub_Mana-----------/02_Walk"),
		_T("Sub09----/Sub_BigHandSword---/02_Run"),
		_T("Sub10----/Sub_Stick----------/02_Boost"),
		_T("Sub11----/Sub_OneSaber-------/02_Death"),
		_T("Sub12----/Sub_TwoSaber"),
		_T("Sub13----/Sub_BigSaber"),
		_T("Sub14----/Sub_BothSaber"),
		_T("Sub15----/Sub_Guant"),
		_T("Sub16----/Sub_Broom"),
		_T("Sub17----/Sub_HoverBoard"),
		_T("Sub18----/Sub_DualGun"),
		_T("Sub19----/Sub_Gun"),
		_T("Sub20----/Sub_Scythe"),
		_T("Sub21----/Sub_DualSpear"),
		_T("Sub22----/Sub_Shuriken"),
		_T("Sub23"),
		_T("Sub24"),
		_T("Sub25"),
		_T("Sub26"),
		_T("Sub27"),
		_T("Sub28"),
		_T("Sub29"),
		_T("Sub30"),
		_T("Sub31"),
		_T("Sub32"),
		_T("Sub33"),
		_T("Sub34"),
		_T("Sub35"),
		_T("Sub36"),
		_T("Sub37"),
		_T("Sub37"),
		_T("Sub39"),
		_T("Sub40"),
		_T("Sub41"),
		_T("Sub42"),
		_T("Sub43"),
		_T("Sub44"),
		_T("Sub45"),
		_T("Sub46"),
		_T("Sub47"),
		_T("Sub47"),
		_T("Sub49"),
		_T("Sub50"),
		_T("Sub51"),
		_T("Sub52"),
		_T("Sub53"),
		_T("Sub54"),
		_T("Sub55"),
		_T("Sub56"),
		_T("Sub57"),
		_T("Sub57"),
		_T("Sub59"),
		_T("Sub60"),
		_T("Sub61"),
		_T("Sub62"),
		_T("Sub63"),
		_T("Sub64"),
		_T("Sub65"),
		_T("Sub66"),
		_T("Sub67"),
		_T("Sub67"),
		_T("Sub69"),
		_T("Sub70"),
		_T("Sub71"),
		_T("Sub72"),
		_T("Sub73"),
		_T("Sub74"),
		_T("Sub75"),
		_T("Sub76"),
		_T("Sub77"),
		_T("Sub77"),
		_T("Sub79"),
		_T("Sub80"),
		_T("Sub81"),
		_T("Sub82"),
		_T("Sub83"),
		_T("Sub84"),
		_T("Sub85"),
		_T("Sub86"),
		_T("Sub87"),
		_T("Sub87"),
		_T("Sub89"),
		_T("Sub90"),
		_T("Sub91"),
		_T("Sub92"),
		_T("Sub93"),
		_T("Sub94"),
		_T("Sub95"),
		_T("Sub96"),
		_T("Sub97"),
		_T("Sub97"),
		_T("Sub99")
	};
};
