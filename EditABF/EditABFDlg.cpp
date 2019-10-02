// EditABFDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EditABF.h"
#include "EditABFDlg.h"

#include "StringUtils.h"
#include "EtcFunction.h"
#include "DxSkinAniMan.h"
#include ".\editabfdlg.h"

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


// CEditABFDlg dialog



CEditABFDlg::CEditABFDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditABFDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEditABFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ANI, m_list_Ani);
	DDX_Control(pDX, IDC_LIST_BONE, m_list_Bone);
}

BEGIN_MESSAGE_MAP(CEditABFDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_ADD, OnBnClickedButtonAnilistAdd)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_DELETE, OnBnClickedButtonAnilistDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ANI, OnNMDblclkListAni)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_EDIT, OnBnClickedButtonAnilistEdit)

	ON_BN_CLICKED(IDC_BUTTON_BONELIST_ADD, OnBnClickedButtonBonelistAdd)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_DEL, OnBnClickedButtonBonelistDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BONE, OnNMDblclkListBone)
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
	ON_BN_CLICKED(IDC_BUTTON_ABF_LOAD, OnBnClickedButtonAbfLoad)
	ON_BN_CLICKED(IDC_BUTTON_ABF_SAVE, OnBnClickedButtonAbfSave)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_OK, OnBnClickedButtonAnilistOk)
END_MESSAGE_MAP()


// CEditABFDlg message handlers

BOOL CEditABFDlg::OnInitDialog()
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

void CEditABFDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEditABFDlg::OnPaint() 
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
HCURSOR CEditABFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEditABFDlg::OnBnClickedButtonAbfLoad()
{
	// TODO: Add your control notification handler code here
	CString szFilterInput = "ABF|*.abf|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	BOOL bOK = m_pAbfCode.LoadFile( dlgInput.GetFileName() );

	if ( bOK )
	{
		SetWindowText( dlgInput.GetFileName().GetString() );
		UpdateData();
	}
}

void CEditABFDlg::OnBnClickedButtonAbfSave()
{
	// TODO: Add your control notification handler code here
	if ( SaveData () )
	{
		CString szFilter = "ABF File (*.abf)|*.abf|";
		CFileDialog dlg(FALSE,".abf",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CEditABFDlg*)this);

		dlg.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath();
		if ( dlg.DoModal() == IDOK )
		{
			BOOL bOK = m_pAbfCode.SaveFile ( dlg.GetFileName() );
			if ( bOK )
			{
				//SetWindowText ( dlg.GetFileName() );
				MessageBox ( "Save Success" );
			}
		}
	}
}

BOOL CEditABFDlg::UpdateData()
{
	SetWin_Text ( this, IDC_EDIT_BONE_FILE, m_pAbfCode.m_strSkeleton.c_str() );
	SetWin_Num_float ( this, IDC_EDIT_SCALE, m_pAbfCode.m_fScale );
	SetWin_Num_float ( this, IDC_EDIT_HEIGHT, m_pAbfCode.m_fHeight );
	SetWin_Num_float ( this, IDC_EDIT_RADIUS, m_pAbfCode.m_fRadius );

	SetWin_Num_float ( this, IDC_EDIT_MIN_X, m_pAbfCode.m_vMin.x );
	SetWin_Num_float ( this, IDC_EDIT_MIN_Y, m_pAbfCode.m_vMin.y );
	SetWin_Num_float ( this, IDC_EDIT_MIN_Z, m_pAbfCode.m_vMin.z );

	SetWin_Num_float ( this, IDC_EDIT_MAX_X, m_pAbfCode.m_vMax.x );
	SetWin_Num_float ( this, IDC_EDIT_MAX_Y, m_pAbfCode.m_vMax.y );
	SetWin_Num_float ( this, IDC_EDIT_MAX_Z, m_pAbfCode.m_vMax.z );

	SetWin_Text ( this, IDC_EDIT_HEAD, m_pAbfCode.m_strPIECE[0].c_str() );
	SetWin_Text ( this, IDC_EDIT_BODY, m_pAbfCode.m_strPIECE[1].c_str() );
	SetWin_Text ( this, IDC_EDIT_PANT, m_pAbfCode.m_strPIECE[2].c_str() );
	SetWin_Text ( this, IDC_EDIT_GLOVE, m_pAbfCode.m_strPIECE[3].c_str() );
	SetWin_Text ( this, IDC_EDIT_RHAND, m_pAbfCode.m_strPIECE[4].c_str() );
	SetWin_Text ( this, IDC_EDIT_LHAND, m_pAbfCode.m_strPIECE[5].c_str() );
	SetWin_Text ( this, IDC_EDIT_FOOT, m_pAbfCode.m_strPIECE[6].c_str() );
	SetWin_Text ( this, IDC_EDIT_HAIR, m_pAbfCode.m_strPIECE[7].c_str() );
	SetWin_Text ( this, IDC_EDIT_ACC, m_pAbfCode.m_strPIECE[8].c_str() );
	SetWin_Text ( this, IDC_EDIT_VEHICLE, m_pAbfCode.m_strPIECE[9].c_str() );
	SetWin_Text ( this, IDC_EDIT_WING, m_pAbfCode.m_strPIECE[10].c_str() );

	InitAniList();
	InitBoneList();

	return TRUE;
}

BOOL CEditABFDlg::SaveData()
{
	m_pAbfCode.m_strSkeleton = GetWin_Text ( this, IDC_EDIT_BONE_FILE ).GetString();
	m_pAbfCode.m_fScale = GetWin_Num_float ( this, IDC_EDIT_SCALE );
	m_pAbfCode.m_fHeight = GetWin_Num_float ( this, IDC_EDIT_HEIGHT );
	m_pAbfCode.m_fRadius = GetWin_Num_float ( this, IDC_EDIT_RADIUS );

	m_pAbfCode.m_vMin.x = GetWin_Num_float ( this, IDC_EDIT_MIN_X );
	m_pAbfCode.m_vMin.y = GetWin_Num_float ( this, IDC_EDIT_MIN_Y );
	m_pAbfCode.m_vMin.z = GetWin_Num_float ( this, IDC_EDIT_MIN_Z );

	m_pAbfCode.m_vMax.x = GetWin_Num_float ( this, IDC_EDIT_MAX_X );
	m_pAbfCode.m_vMax.y = GetWin_Num_float ( this, IDC_EDIT_MAX_Y );
	m_pAbfCode.m_vMax.z = GetWin_Num_float ( this, IDC_EDIT_MAX_Z );

	m_pAbfCode.m_strPIECE[0] = GetWin_Text ( this, IDC_EDIT_HEAD ).GetString();
	m_pAbfCode.m_strPIECE[1] = GetWin_Text ( this, IDC_EDIT_BODY ).GetString();
	m_pAbfCode.m_strPIECE[2] = GetWin_Text ( this, IDC_EDIT_PANT ).GetString();
	m_pAbfCode.m_strPIECE[3] = GetWin_Text ( this, IDC_EDIT_GLOVE ).GetString();
	m_pAbfCode.m_strPIECE[4] = GetWin_Text ( this, IDC_EDIT_RHAND ).GetString();
	m_pAbfCode.m_strPIECE[5] = GetWin_Text ( this, IDC_EDIT_LHAND ).GetString();
	m_pAbfCode.m_strPIECE[6] = GetWin_Text ( this, IDC_EDIT_FOOT ).GetString();
	m_pAbfCode.m_strPIECE[7] = GetWin_Text ( this, IDC_EDIT_HAIR ).GetString();
	m_pAbfCode.m_strPIECE[8] = GetWin_Text ( this, IDC_EDIT_ACC ).GetString();
	m_pAbfCode.m_strPIECE[9] = GetWin_Text ( this, IDC_EDIT_VEHICLE ).GetString();
	m_pAbfCode.m_strPIECE[10] = GetWin_Text ( this, IDC_EDIT_WING ).GetString();

	return TRUE;
}

void CEditABFDlg::InitAniList()
{
	m_list_Ani.DeleteAllItems();

	int iAniSize = (int)m_pAbfCode.m_vecANIFILE.size();
	char szTempChar[256];

	for ( int i = 0; i < iAniSize; i++ )
	{
		sprintf( szTempChar, "%d", i );
		m_list_Ani.InsertItem( i, szTempChar );
		sprintf( szTempChar, "%s", m_pAbfCode.m_vecANIFILE[i].c_str() );
		m_list_Ani.SetItemText( i, 1, szTempChar );
	}

	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_HIDE );
}

void CEditABFDlg::OnBnClickedButtonAnilistAdd()
{ 
	bADD = true;
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CEditABFDlg::OnBnClickedButtonAnilistDelete()
{
	// TODO: Add your control notification handler code here
	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	m_pAbfCode.m_vecANIFILE.erase ( m_pAbfCode.m_vecANIFILE.begin()+nSelect );

	InitAniList();
}

void CEditABFDlg::OnNMDblclkListAni(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, m_pAbfCode.m_vecANIFILE[nSelect].c_str() );
	bADD = false;
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CEditABFDlg::OnBnClickedButtonAnilistEdit()
{
	// TODO: Add your control notification handler code here
	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, m_pAbfCode.m_vecANIFILE[nSelect].c_str());
	bADD = false;
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CEditABFDlg::OnBnClickedButtonAnilistSearch()
{
	// TODO: Add your control notification handler code here
	CString szFilter = "Animation File (*.bin)|*.bin|";
	
	//	Note : 파일 오픈 다이알로그를 만듬.
	CFileDialog dlg(TRUE,".bin",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CEditABFDlg*)this);

	dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
	if ( dlg.DoModal() == IDOK )
	{
		std::string strAniName = dlg.GetFileName().GetString();
		//CString strBinName;

		//STRUTIL::ChangeExt ( strAniName.c_str(), ".bin", strBinName, ".x" );
		SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, strAniName.c_str() );
	}
}

void CEditABFDlg::OnBnClickedButtonAnilistOk()
{
	if ( !bADD )
	{
		int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if( nSelect == -1 ) return;

		m_pAbfCode.m_vecANIFILE.erase ( m_pAbfCode.m_vecANIFILE.begin()+nSelect );	
	}

	CString strBinName = "";
	CString strFileName = "";
	strFileName = GetWin_Text ( this, IDC_EDIT_ANILIST_NAME ).GetString();
	int nIndex = strFileName.ReverseFind ( '.' );
	strBinName = strFileName.Left(nIndex) + ".x";
	m_pAbfCode.m_vecANIFILE.push_back ( strBinName.GetString() );

	InitAniList();
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_HIDE );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_HIDE );
}


void CEditABFDlg::InitBoneList()
{
	m_list_Bone.DeleteAllItems();

	int iBoneSize = (int)m_pAbfCode.m_dwBONE;
	char szTempChar[256];

	for ( int i = 0; i < iBoneSize; i++ )
	{
		//BONELIST s_BoneList = m_pAbfCode.m_vecBoneList[i];

		sprintf( szTempChar, "%d", i );
		m_list_Bone.InsertItem( i, szTempChar );
		sprintf( szTempChar, "%.2f%%", m_pAbfCode.m_fBONE1[i] );
		m_list_Bone.SetItemText( i, 1, szTempChar );
		sprintf( szTempChar, "%.2f%%", m_pAbfCode.m_fBONE2[i] );
		m_list_Bone.SetItemText( i, 2, szTempChar );
		sprintf( szTempChar, "%.2f%%", m_pAbfCode.m_fBONE3[i] );
		m_list_Bone.SetItemText( i, 3, szTempChar );
		sprintf( szTempChar, "%s", m_pAbfCode.m_strBONE[i].c_str() );
		m_list_Bone.SetItemText( i, 4, szTempChar );
	}

	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_EDIT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_HIDE );
}

void CEditABFDlg::OnBnClickedButtonBonelistAdd()
{
	// TODO: Add your control notification handler code here
	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_SHOW );
}

void CEditABFDlg::OnBnClickedButtonBonelistDel()
{
	// TODO: Add your control notification handler code here
	/*int nSelect = m_list_Bone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;*/
	DWORD dwSize(m_pAbfCode.m_dwBONE);

	m_pAbfCode.m_dwBONE = dwSize - 1;

	InitBoneList();
}

void CEditABFDlg::OnNMDblclkListBone(NMHDR *pNMHDR, LRESULT *pResult)
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

	SetWin_Num_float ( this, IDC_EDIT_BONE1, m_pAbfCode.m_fBONE1[nSelect] );
	SetWin_Num_float ( this, IDC_EDIT_BONE2, m_pAbfCode.m_fBONE2[nSelect] );
	SetWin_Num_float ( this, IDC_EDIT_BONE3, m_pAbfCode.m_fBONE3[nSelect] );
	SetWin_Text ( this, IDC_EDIT_BONE_NAME, m_pAbfCode.m_strBONE[nSelect].c_str() );
}

void CEditABFDlg::OnBnClickedButtonBonelistEdit()
{
	// TODO: Add your control notification handler code here
	int nSelect = m_list_Bone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	m_pAbfCode.m_fBONE1[nSelect] = GetWin_Num_float ( this, IDC_EDIT_BONE1 );
	m_pAbfCode.m_fBONE2[nSelect] = GetWin_Num_float ( this, IDC_EDIT_BONE2 );
	m_pAbfCode.m_fBONE3[nSelect] = GetWin_Num_float ( this, IDC_EDIT_BONE3 );
	m_pAbfCode.m_strBONE[nSelect] = GetWin_Text ( this, IDC_EDIT_BONE_NAME ).GetString();

	InitBoneList();
}

void CEditABFDlg::OnBnClickedButtonBonelistOk()
{
	// TODO: Add your control notification handler code here
	DWORD dwSize(m_pAbfCode.m_dwBONE);

	m_pAbfCode.m_dwBONE = dwSize + 1;
	m_pAbfCode.m_fBONE1[dwSize] = GetWin_Num_float ( this, IDC_EDIT_BONE1 );
	m_pAbfCode.m_fBONE2[dwSize] = GetWin_Num_float ( this, IDC_EDIT_BONE2 );
	m_pAbfCode.m_fBONE3[dwSize] = GetWin_Num_float ( this, IDC_EDIT_BONE3 );
	m_pAbfCode.m_strBONE[dwSize] = GetWin_Text ( this, IDC_EDIT_BONE_NAME ).GetString();

	InitBoneList();
}

void CEditABFDlg::LoadCpsfile ( int nID )
{
	CString szFilter = "Wearing File (*.cps; *.aps; *.vps)|*.cps; *.aps; *.vps|";
	
	//	Note : 파일 오픈 다이알로그를 만듬.
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CEditABFDlg*)this);

	dlg.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		SetWin_Text ( this, nID, dlg.GetFileName().GetString() );
	}
}

void CEditABFDlg::OnBnClickedButtonHead()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_HEAD );
}

void CEditABFDlg::OnBnClickedButtonBody()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_BODY );
}

void CEditABFDlg::OnBnClickedButtonPant()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_PANT );
}

void CEditABFDlg::OnBnClickedButtonGlove()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_GLOVE );
}

void CEditABFDlg::OnBnClickedButtonRhand()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_RHAND );
}

void CEditABFDlg::OnBnClickedButtonLhand()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_LHAND );
}

void CEditABFDlg::OnBnClickedButtonFoot()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_FOOT );
}

void CEditABFDlg::OnBnClickedButtonHair()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_HAIR );
}

void CEditABFDlg::OnBnClickedButtonAcc()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_ACC );
}

void CEditABFDlg::OnBnClickedButtonVehicle()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_VEHICLE );
}

void CEditABFDlg::OnBnClickedButtonWing()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_WING );
}

