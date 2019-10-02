// CHFEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CHFEditor.h"
#include "CHFEditorDlg.h"
#include ".\chfeditordlg.h"

#include "StringUtils.h"
#include "EtcFunction.h"
#include "DxSkinAniMan.h"

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


// CCHFEditorDlg dialog



CCHFEditorDlg::CCHFEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCHFEditorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCHFEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_Ani);
}

BEGIN_MESSAGE_MAP(CCHFEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_LOAD_CHF, OnBnClickedButtonLoadChf)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_CHF, OnBnClickedButtonSaveChf)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_ADD, OnBnClickedButtonAnilistAdd)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_DELETE, OnBnClickedButtonAnilistDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_EDIT, OnBnClickedButtonAnilistEdit)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_OK, OnBnClickedButtonAnilistOk)
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
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_SEARCH, OnBnClickedButtonAnilistSearch)
END_MESSAGE_MAP()


// CCHFEditorDlg message handlers

BOOL CCHFEditorDlg::OnInitDialog()
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

	CAboutDlg dlg;
	int nRet;
	nRet = (int) dlg.DoModal();

	if (nRet == IDOK)
	{
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCHFEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCHFEditorDlg::OnPaint() 
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
HCURSOR CCHFEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCHFEditorDlg::OnBnClickedButtonLoadChf()
{
	// TODO: Add your control notification handler code here
	CString szFilter = "CHF File (*.chf)|*.chf|";

	CFileDialog dlg(TRUE,".chf",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CCHFEditorDlg*)this);

	dlg.m_ofn.lpstrInitialDir = DxSkinCharDataContainer::GetInstance().GetPath();

	if ( dlg.DoModal() == IDOK )
	{
		BOOL bOK = m_pChfCode.LoadFile ( dlg.GetFileName().GetString() );
		if ( bOK )
		{
			SetWindowText ( dlg.GetFileName().GetString() );
			UpdateData();
		}
	}
}

void CCHFEditorDlg::OnBnClickedButtonSaveChf()
{
	// TODO: Add your control notification handler code here
	if ( SaveData () )
	{
		CString szFilter = "CHF File (*.chf)|*.chf|";
		CFileDialog dlg(FALSE,".chf",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CCHFEditorDlg*)this);

		dlg.m_ofn.lpstrInitialDir = DxSkinCharDataContainer::GetInstance().GetPath();
		if ( dlg.DoModal() == IDOK )
		{
			BOOL bOK = m_pChfCode.SaveFile ( dlg.GetFileName().GetString() );
			if ( bOK )
			{
				SetWindowText ( dlg.GetFileName() );
				MessageBox ( "Save Success" );
			}
		}
	}
}

BOOL CCHFEditorDlg::UpdateData()
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

	InitAniList();

	return TRUE;
}

BOOL CCHFEditorDlg::SaveData()
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

	return TRUE;
}

void CCHFEditorDlg::InitAniList()
{
	m_list_Ani.DeleteAllItems();

	int iAniSize = (int)m_pChfCode.m_vecANIFILE.size();
	char szTempChar[256];

	for ( int i = 0; i < iAniSize; i++ )
	{
		//std::string m_strAni = m_pAbfCode.m_vecANIFILE[i];

		sprintf( szTempChar, "%d", i );
		m_list_Ani.InsertItem( i, szTempChar );
		//sprintf( szTempChar, "%s", m_pAbfCode.m_strANINAME.c_str() );
		sprintf( szTempChar, "%s", m_pChfCode.m_vecANIFILE[i].c_str() );
		m_list_Ani.SetItemText( i, 1, szTempChar );
	}

	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_EDIT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_HIDE );
}

void CCHFEditorDlg::OnBnClickedButtonAnilistAdd()
{
	// TODO: Add your control notification handler code here
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CCHFEditorDlg::OnBnClickedButtonAnilistDelete()
{
	// TODO: Add your control notification handler code here
	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	m_pChfCode.m_vecANIFILE.erase ( m_pChfCode.m_vecANIFILE.begin()+nSelect );

	InitAniList();
}

void CCHFEditorDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_EDIT, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );

	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, m_pChfCode.m_vecANIFILE[nSelect].c_str() );
}

void CCHFEditorDlg::OnBnClickedButtonAnilistEdit()
{
	// TODO: Add your control notification handler code here
	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	m_pChfCode.m_vecANIFILE.erase ( m_pChfCode.m_vecANIFILE.begin()+nSelect );
	m_pChfCode.m_strANINAME = m_pChfCode.m_vecANIFILE[nSelect].c_str();

	m_pChfCode.m_strANINAME = GetWin_Text ( this, IDC_EDIT_ANILIST_NAME );

	m_pChfCode.m_vecANIFILE.push_back ( m_pChfCode.m_strANINAME.c_str() );

	InitAniList();
}

void CCHFEditorDlg::OnBnClickedButtonAnilistOk()
{
	// TODO: Add your control notification handler code here
	m_pChfCode.m_strANINAME = GetWin_Text ( this, IDC_EDIT_ANILIST_NAME );

	m_pChfCode.m_vecANIFILE.push_back ( m_pChfCode.m_strANINAME.c_str() );

	InitAniList();
}

void CCHFEditorDlg::LoadCpsfile ( int nID )
{
	CString szFilter = "CPS File (*.cps)|*.cps|";
	
	//	Note : 파일 오픈 다이알로그를 만듬.
	CFileDialog dlg(TRUE,".cps",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CCHFEditorDlg*)this);

	dlg.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		SetWin_Text ( this, nID, dlg.GetFileName().GetString() );
	}
}

void CCHFEditorDlg::OnBnClickedButtonHead()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_HEAD );
}

void CCHFEditorDlg::OnBnClickedButtonBody()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_BODY );
}

void CCHFEditorDlg::OnBnClickedButtonPant()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_PANT );
}

void CCHFEditorDlg::OnBnClickedButtonGlove()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_GLOVE );
}

void CCHFEditorDlg::OnBnClickedButtonRhand()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_RHAND );
}

void CCHFEditorDlg::OnBnClickedButtonLhand()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_LHAND );
}

void CCHFEditorDlg::OnBnClickedButtonFoot()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_FOOT );
}

void CCHFEditorDlg::OnBnClickedButtonHair()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_HAIR );
}

void CCHFEditorDlg::OnBnClickedButtonAcc()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_ACC );
}

void CCHFEditorDlg::OnBnClickedButtonVehicle()
{
	// TODO: Add your control notification handler code here
	LoadCpsfile ( IDC_EDIT_VEHICLE );
}

void CCHFEditorDlg::OnBnClickedButtonAnilistSearch()
{
	// TODO: Add your control notification handler code here
	CString szFilter = "Animation File (*.bin)|*.bin|";
	
	//	Note : 파일 오픈 다이알로그를 만듬.
	CFileDialog dlg(TRUE,".bin",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CCHFEditorDlg*)this);

	dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
	if ( dlg.DoModal() == IDOK )
	{
		std::string strAniName = dlg.GetFileName().GetString();
		CString strBinName;

		STRUTIL::ChangeExt ( strAniName.c_str(), ".bin", strBinName, ".x" );
		SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, strBinName.GetString() );
	}
}
