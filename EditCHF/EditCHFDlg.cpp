// EditCHFDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EditCHF.h"
#include "EditCHFDlg.h"

#include "StringUtils.h"
#include "EtcFunction.h"
#include "DxSkinAniMan.h"
#include ".\editchfdlg.h"

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


// CEditCHFDlg dialog



CEditCHFDlg::CEditCHFDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditCHFDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEditCHFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ANI, m_list_Ani);
	DDX_Control(pDX, IDC_LIST_BONE, m_list_Bone);
}

BEGIN_MESSAGE_MAP(CEditCHFDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ANI, OnNMDblclkListAni)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_ADD, OnBnClickedButtonAnilistAdd)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_DELETE, OnBnClickedButtonAnilistDelete)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_EDIT, OnBnClickedButtonAnilistEdit)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_OK, OnBnClickedButtonAnilistOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BONE, OnNMDblclkListBone)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_ADD, OnBnClickedButtonBonelistAdd)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_DEL, OnBnClickedButtonBonelistDel)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_EDIT, OnBnClickedButtonBonelistEdit)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_OK, OnBnClickedButtonBonelistOk)
	ON_BN_CLICKED(IDC_BUTTON_HEAD, OnBnClickedButtonHead)
	ON_BN_CLICKED(IDC_BUTTON_BODY, OnBnClickedButtonBody)
	ON_BN_CLICKED(IDC_BUTTON_PANT, OnBnClickedButtonPant)
	ON_BN_CLICKED(IDC_BUTTON_GLOVE, OnBnClickedButtonGlove)
	ON_BN_CLICKED(IDC_BUTTON_RHAND, OnBnClickedButtonRhand)
	ON_BN_CLICKED(IDC_BUTTON_LHAND, OnBnClickedButtonLhand)
	ON_BN_CLICKED(IDC_BUTTON_FOOT, OnBnClickedButtonFoot)
	ON_BN_CLICKED(IDC_BUTTON_HAIR, OnBnClickedButtonHair)
	ON_BN_CLICKED(IDC_BUTTON_ACC, OnBnClickedButtonAcc)
	ON_BN_CLICKED(IDC_BUTTON_VEHICLE, OnBnClickedButtonVehicle)
	ON_BN_CLICKED(IDC_BUTTON_WING, OnBnClickedButtonWing)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_SEARCH, OnBnClickedButtonAnilistSearch)
	ON_BN_CLICKED(IDC_BUTTON_CHF_LOAD, OnBnClickedButtonChfLoad)
	ON_BN_CLICKED(IDC_BUTTON_CHF_SAVE, OnBnClickedButtonChfSave)
END_MESSAGE_MAP()


// CEditCHFDlg message handlers

BOOL CEditCHFDlg::OnInitDialog()
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
	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	m_list_Ani.SetExtendedStyle ( m_list_Ani.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_list_Ani.GetClientRect ( &rectCtrl );
	lnWidth = rectCtrl.right - rectCtrl.left;

	const int nColumnCount = 2;	
	char* szColumnName1[nColumnCount] = { "No", "Animation Cfg" };
	int nColumnWidthPercent1[nColumnCount] = { 20, 80 };

	for ( int i = 0; i < nColumnCount; i++ )
	{		
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.pszText = szColumnName1[i];
		lvColumn.iSubItem = i;
		lvColumn.cx = ( lnWidth*nColumnWidthPercent1[i] ) / 100;
		m_list_Ani.InsertColumn (i, &lvColumn );
	}

	RECT rectCtrl1;
	LONG lnWidth1;
	LV_COLUMN lvColumn1;

	m_list_Bone.SetExtendedStyle ( m_list_Bone.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_list_Bone.GetClientRect ( &rectCtrl1 );
	lnWidth1 = rectCtrl1.right - rectCtrl1.left;

	const int nColumnCount1 = 5;	
	char* szColumnName2[nColumnCount1] = { "No", "Bone 1", "Bone 2", "Bone 3", "Bone Name" };
	int nColumnWidthPercent2[nColumnCount1] = { 10, 15, 15, 15, 45 };

	for ( int i = 0; i < nColumnCount1; i++ )
	{		
		lvColumn1.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn1.fmt = LVCFMT_LEFT;
		lvColumn1.pszText = szColumnName2[i];
		lvColumn1.iSubItem = i;
		lvColumn1.cx = ( lnWidth*nColumnWidthPercent2[i] ) / 100;
		m_list_Bone.InsertColumn (i, &lvColumn1 );
	}

	bADD = true;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEditCHFDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEditCHFDlg::OnPaint() 
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
HCURSOR CEditCHFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEditCHFDlg::OnBnClickedButtonChfLoad()
{
	CString szFilterInput = "CHF|*.chf|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinCharDataContainer::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	BOOL bOK = m_pChfCode.LoadFile ( dlgInput.GetFileName() );

	if ( bOK )
	{
		SetWindowText( dlgInput.GetFileName().GetString() );
		UpdateData();
	}
}

void CEditCHFDlg::OnBnClickedButtonChfSave()
{
	if ( SaveData () )
	{
		CString szFilter = "CHF File (*.chf)|*.chf|";
		CFileDialog dlg(FALSE,".abf",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CEditCHFDlg*)this);

		dlg.m_ofn.lpstrInitialDir = DxSkinCharDataContainer::GetInstance().GetPath();
		if ( dlg.DoModal() == IDOK )
		{
			BOOL bOK = m_pChfCode.SaveFile ( dlg.GetFileName() );
			if ( bOK )
			{
				SetWindowText ( dlg.GetFileName() );
				MessageBox ( "Save Success" );
			}
		}
	}
}

BOOL CEditCHFDlg::UpdateData()
{
	SetWin_Text ( this, IDC_EDIT_BONE_FILE, m_pChfCode.m_strSkeleton.c_str() );
	SetWin_Num_float ( this, IDC_EDIT_SCALE, m_pChfCode.m_fScale );
	SetWin_Num_float ( this, IDC_EDIT_HEIGHT, m_pChfCode.m_fHeight );
	SetWin_Num_float ( this, IDC_EDIT_RADIUS, m_pChfCode.m_fRadius );

	SetWin_Num_float ( this, IDC_EDIT_MIN_X, m_pChfCode.m_vMin.x );
	SetWin_Num_float ( this, IDC_EDIT_MIN_Y, m_pChfCode.m_vMin.y );
	SetWin_Num_float ( this, IDC_EDIT_MIN_Z, m_pChfCode.m_vMin.z );

	SetWin_Num_float ( this, IDC_EDIT_MAX_X, m_pChfCode.m_vMax.x );
	SetWin_Num_float ( this, IDC_EDIT_MAX_Y, m_pChfCode.m_vMax.y );
	SetWin_Num_float ( this, IDC_EDIT_MAX_Z, m_pChfCode.m_vMax.z );

	SetWin_Text ( this, IDC_EDIT_HEAD, m_pChfCode.m_strPIECE[0].c_str() );
	SetWin_Text ( this, IDC_EDIT_BODY, m_pChfCode.m_strPIECE[1].c_str() );
	SetWin_Text ( this, IDC_EDIT_PANT, m_pChfCode.m_strPIECE[2].c_str() );
	SetWin_Text ( this, IDC_EDIT_GLOVE, m_pChfCode.m_strPIECE[3].c_str() );
	SetWin_Text ( this, IDC_EDIT_RHAND, m_pChfCode.m_strPIECE[4].c_str() );
	SetWin_Text ( this, IDC_EDIT_LHAND, m_pChfCode.m_strPIECE[5].c_str() );
	SetWin_Text ( this, IDC_EDIT_FOOT, m_pChfCode.m_strPIECE[6].c_str() );
	SetWin_Text ( this, IDC_EDIT_HAIR, m_pChfCode.m_strPIECE[7].c_str() );
	SetWin_Text ( this, IDC_EDIT_ACC, m_pChfCode.m_strPIECE[8].c_str() );
	SetWin_Text ( this, IDC_EDIT_VEHICLE, m_pChfCode.m_strPIECE[9].c_str() );
	SetWin_Text ( this, IDC_EDIT_WING, m_pChfCode.m_strPIECE[10].c_str() );
	SetWin_Check ( this, IDC_CHECK_BWO, (BOOL) m_pChfCode.m_bWorldObj );

	InitAniList();
	InitBoneList();

	return TRUE;
}

BOOL CEditCHFDlg::SaveData()
{
	m_pChfCode.m_strSkeleton = GetWin_Text ( this, IDC_EDIT_BONE_FILE ).GetString();
	m_pChfCode.m_fScale = GetWin_Num_float ( this, IDC_EDIT_SCALE );
	m_pChfCode.m_fHeight = GetWin_Num_float ( this, IDC_EDIT_HEIGHT );
	m_pChfCode.m_fRadius = GetWin_Num_float ( this, IDC_EDIT_RADIUS );

	m_pChfCode.m_vMin.x = GetWin_Num_float ( this, IDC_EDIT_MIN_X );
	m_pChfCode.m_vMin.y = GetWin_Num_float ( this, IDC_EDIT_MIN_Y );
	m_pChfCode.m_vMin.z = GetWin_Num_float ( this, IDC_EDIT_MIN_Z );

	m_pChfCode.m_vMax.x = GetWin_Num_float ( this, IDC_EDIT_MAX_X );
	m_pChfCode.m_vMax.y = GetWin_Num_float ( this, IDC_EDIT_MAX_Y );
	m_pChfCode.m_vMax.z = GetWin_Num_float ( this, IDC_EDIT_MAX_Z );

	m_pChfCode.m_strPIECE[0] = GetWin_Text ( this, IDC_EDIT_HEAD ).GetString();
	m_pChfCode.m_strPIECE[1] = GetWin_Text ( this, IDC_EDIT_BODY ).GetString();
	m_pChfCode.m_strPIECE[2] = GetWin_Text ( this, IDC_EDIT_PANT ).GetString();
	m_pChfCode.m_strPIECE[3] = GetWin_Text ( this, IDC_EDIT_GLOVE ).GetString();
	m_pChfCode.m_strPIECE[4] = GetWin_Text ( this, IDC_EDIT_RHAND ).GetString();
	m_pChfCode.m_strPIECE[5] = GetWin_Text ( this, IDC_EDIT_LHAND ).GetString();
	m_pChfCode.m_strPIECE[6] = GetWin_Text ( this, IDC_EDIT_FOOT ).GetString();
	m_pChfCode.m_strPIECE[7] = GetWin_Text ( this, IDC_EDIT_HAIR ).GetString();
	m_pChfCode.m_strPIECE[8] = GetWin_Text ( this, IDC_EDIT_ACC ).GetString();
	m_pChfCode.m_strPIECE[9] = GetWin_Text ( this, IDC_EDIT_VEHICLE ).GetString();
	m_pChfCode.m_strPIECE[10] = GetWin_Text ( this, IDC_EDIT_WING ).GetString();
	m_pChfCode.m_bWorldObj = GetWin_Check ( this, IDC_CHECK_BWO );

	return TRUE;
}

void CEditCHFDlg::InitAniList()
{
	m_list_Ani.DeleteAllItems();

	int iAniSize = (int)m_pChfCode.m_vecANIFILE.size();
	char szTempChar[256];

	for ( int i = 0; i < iAniSize; i++ )
	{
		sprintf( szTempChar, "%d", i );
		m_list_Ani.InsertItem( i, szTempChar );
		sprintf( szTempChar, "%s", m_pChfCode.m_vecANIFILE[i].c_str() );
		m_list_Ani.SetItemText( i, 1, szTempChar );
	}

	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_HIDE );
}

void CEditCHFDlg::OnBnClickedButtonAnilistAdd()
{
	bADD = true;
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CEditCHFDlg::OnBnClickedButtonAnilistDelete()
{
	// TODO: Add your control notification handler code here
	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	m_pChfCode.m_vecANIFILE.erase ( m_pChfCode.m_vecANIFILE.begin()+nSelect );

	InitAniList();
}


void CEditCHFDlg::OnNMDblclkListAni(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, m_pChfCode.m_vecANIFILE[nSelect].c_str() );
	bADD = false;
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CEditCHFDlg::OnBnClickedButtonAnilistEdit()
{
	// TODO: Add your control notification handler code here
	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, m_pChfCode.m_vecANIFILE[nSelect].c_str());
	bADD = false;
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CEditCHFDlg::OnBnClickedButtonAnilistSearch()
{
	// TODO: Add your control notification handler code here
	CString szFilter = "Animation File (*.bin)|*.bin|";
	
	//	Note : 파일 오픈 다이알로그를 만듬.
	CFileDialog dlg(TRUE,".bin",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CEditCHFDlg*)this);

	dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
	if ( dlg.DoModal() == IDOK )
	{
		std::string strAniName = dlg.GetFileName().GetString();
		//CString strCfgName;

		//STRUTIL::ChangeExt ( strAniName.c_str(), ".bin", strCfgName, ".cfg" );
		SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, strAniName.c_str() );
	}
}

void CEditCHFDlg::OnBnClickedButtonAnilistOk()
{
	if ( !bADD )
	{
		int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if( nSelect == -1 ) return;

		m_pChfCode.m_vecANIFILE.erase ( m_pChfCode.m_vecANIFILE.begin()+nSelect );	
	}

	CString strBinName = "";
	CString strFileName = "";
	strFileName = GetWin_Text ( this, IDC_EDIT_ANILIST_NAME ).GetString();
	int nIndex = strFileName.ReverseFind ( '.' );
	strBinName = strFileName.Left(nIndex) + ".x";
	m_pChfCode.m_vecANIFILE.push_back ( strBinName.GetString() );

	InitAniList();
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_HIDE );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_HIDE );
}

void CEditCHFDlg::InitBoneList()
{
	m_list_Bone.DeleteAllItems();

	int iBoneSize = (int)m_pChfCode.m_dwBONE;
	char szTempChar[256];

	for ( int i = 0; i < iBoneSize; i++ )
	{
		//BONELIST s_BoneList = m_pAbfCode.m_vecBoneList[i];

		sprintf( szTempChar, "%d", i );
		m_list_Bone.InsertItem( i, szTempChar );
		sprintf( szTempChar, "%.2f%%", m_pChfCode.m_fBONE1[i] );
		m_list_Bone.SetItemText( i, 1, szTempChar );
		sprintf( szTempChar, "%.2f%%", m_pChfCode.m_fBONE2[i] );
		m_list_Bone.SetItemText( i, 2, szTempChar );
		sprintf( szTempChar, "%.2f%%", m_pChfCode.m_fBONE3[i] );
		m_list_Bone.SetItemText( i, 3, szTempChar );
		sprintf( szTempChar, "%s", m_pChfCode.m_strBONE[i].c_str() );
		m_list_Bone.SetItemText( i, 4, szTempChar );
	}

	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_EDIT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_HIDE );
}

void CEditCHFDlg::OnNMDblclkListBone(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_EDIT, SW_SHOW );

	int nSelect = m_list_Bone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_Num_float ( this, IDC_EDIT_BONE1, m_pChfCode.m_fBONE1[nSelect] );
	SetWin_Num_float ( this, IDC_EDIT_BONE2, m_pChfCode.m_fBONE2[nSelect] );
	SetWin_Num_float ( this, IDC_EDIT_BONE3, m_pChfCode.m_fBONE3[nSelect] );
	SetWin_Text ( this, IDC_EDIT_BONE_NAME, m_pChfCode.m_strBONE[nSelect].c_str() );
}

void CEditCHFDlg::OnBnClickedButtonBonelistAdd()
{
	// TODO: Add your control notification handler code here
	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_SHOW );
}

void CEditCHFDlg::OnBnClickedButtonBonelistDel()
{
	// TODO: Add your control notification handler code here
	DWORD dwSize(m_pChfCode.m_dwBONE);

	m_pChfCode.m_dwBONE = dwSize - 1;

	InitBoneList();
}

void CEditCHFDlg::OnBnClickedButtonBonelistEdit()
{
	// TODO: Add your control notification handler code here
	int nSelect = m_list_Bone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	m_pChfCode.m_fBONE1[nSelect] = GetWin_Num_float ( this, IDC_EDIT_BONE1 );
	m_pChfCode.m_fBONE2[nSelect] = GetWin_Num_float ( this, IDC_EDIT_BONE2 );
	m_pChfCode.m_fBONE3[nSelect] = GetWin_Num_float ( this, IDC_EDIT_BONE3 );
	m_pChfCode.m_strBONE[nSelect] = GetWin_Text ( this, IDC_EDIT_BONE_NAME ).GetString();

	InitBoneList();
}

void CEditCHFDlg::OnBnClickedButtonBonelistOk()
{
	// TODO: Add your control notification handler code here
	DWORD dwSize(m_pChfCode.m_dwBONE);

	m_pChfCode.m_dwBONE = dwSize + 1;
	m_pChfCode.m_fBONE1[dwSize] = GetWin_Num_float ( this, IDC_EDIT_BONE1 );
	m_pChfCode.m_fBONE2[dwSize] = GetWin_Num_float ( this, IDC_EDIT_BONE2 );
	m_pChfCode.m_fBONE3[dwSize] = GetWin_Num_float ( this, IDC_EDIT_BONE3 );
	m_pChfCode.m_strBONE[dwSize] = GetWin_Text ( this, IDC_EDIT_BONE_NAME ).GetString();

	InitBoneList();
}

void CEditCHFDlg::LoadCpsfile ( int nID )
{
	CString szFilter = "Wearing File (*.cps; *.aps; *.vps)|*.cps; *.aps; *.vps|";
	
	//	Note : 파일 오픈 다이알로그를 만듬.
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CEditCHFDlg*)this);

	dlg.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		SetWin_Text ( this, nID, dlg.GetFileName().GetString() );
	}
}

void CEditCHFDlg::OnBnClickedButtonHead()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_HEAD );
}

void CEditCHFDlg::OnBnClickedButtonBody()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_BODY );
}

void CEditCHFDlg::OnBnClickedButtonPant()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_PANT );
}

void CEditCHFDlg::OnBnClickedButtonGlove()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_GLOVE );
}

void CEditCHFDlg::OnBnClickedButtonRhand()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_RHAND );
}

void CEditCHFDlg::OnBnClickedButtonLhand()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_LHAND );
}

void CEditCHFDlg::OnBnClickedButtonFoot()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_FOOT );
}

void CEditCHFDlg::OnBnClickedButtonHair()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_HAIR );
}

void CEditCHFDlg::OnBnClickedButtonAcc()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_ACC );
}

void CEditCHFDlg::OnBnClickedButtonVehicle()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_VEHICLE );
}

void CEditCHFDlg::OnBnClickedButtonWing()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_WING );
}


