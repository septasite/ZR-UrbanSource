// EditABLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EditABL.h"
#include "EditABLDlg.h"
#include ".\editabldlg.h"
#include "DxSkinPieceRootDataDummy.h"
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


// CEditABLDlg dialog



CEditABLDlg::CEditABLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditABLDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEditABLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEditABLDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_LOADABLNEO, OnBnClickedButtonLoadablneo)
	ON_BN_CLICKED(IDC_BUTTON_LOADABL, OnBnClickedButtonLoadabl)
	ON_BN_CLICKED(IDC_BUTTON_SAVEABL, OnBnClickedButtonSaveabl)
END_MESSAGE_MAP()


// CEditABLDlg message handlers

BOOL CEditABLDlg::OnInitDialog()
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
	SetWin_Combo_Init ( this, IDC_COMBO_TYPE, DUMMYABL::m_CharType, PIECE_SIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_SLOT, DUMMYABL::m_SlotType, EMPEACE_WEAPON_SIZE );

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEditABLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEditABLDlg::OnPaint() 
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
HCURSOR CEditABLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEditABLDlg::OnBnClickedButtonLoadablneo()
{
	// TODO: Add your control notification handler code here
	CString szFilterInput = "ABL|*.abl|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	BOOL bOK = ABLDummy.LoadFileNeo ( dlgInput.GetFileName() );

	if ( bOK )
	{
		SetWindowText( dlgInput.GetFileName().GetString() );
		UpdateData ();
	}
	else 
		MessageBox("Can't Load ABL File!!!");
}

void CEditABLDlg::OnBnClickedButtonLoadabl()
{
	CString szFilterInput = "ABL|*.abl|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	BOOL bOK = ABLDummy.LoadFile ( dlgInput.GetFileName() );

	if ( bOK )
	{
		SetWindowText( dlgInput.GetFileName().GetString() );
		if ( ABLDummy.m_vScale_F == D3DXVECTOR3(0,0,0) ) { UpdateData();
		}else{
			UpdateData2();
		}
	}
}

void CEditABLDlg::OnBnClickedButtonSaveabl()
{
	if ( SaveData () )
	{
		CString szFilter = "ABL File (*.abl)|*.abl|";
		CFileDialog dlg(FALSE,".abl",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CEditABLDlg*)this);

		dlg.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath();
		if ( dlg.DoModal() == IDOK )
		{
			BOOL bOK = ABLDummy.SaveFile ( dlg.GetFileName() );
			if ( bOK )
			{
				MessageBox ( "Save Done" );
			}
		}
	}
}

BOOL	CEditABLDlg::UpdateData ()
{
	SetWin_Text ( this, IDC_EDIT_ABFFILE, ABLDummy.m_strAbf.c_str() );
	SetWin_Text ( this, IDC_EDIT_CPSFILE, ABLDummy.m_strCPS.c_str() );
	SetWin_Text ( this, IDC_EDIT_SKEFILE, ABLDummy.m_strSkeleton.c_str() );
	SetWin_Text ( this, IDC_EDIT_BONELINK, ABLDummy.m_strBoneLink.c_str() );
	SetWin_Combo_Sel ( this, IDC_COMBO_TYPE, (int)ABLDummy.m_dwType );
	SetWin_Combo_Sel ( this, IDC_COMBO_SLOT, (int)ABLDummy.m_dwWeaponSlot );
	SetWin_Num_float( this, IDC_EDIT_ROTX, ABLDummy.m_fRotX );
	SetWin_Num_float( this, IDC_EDIT_ROTY, ABLDummy.m_fRotY );
	SetWin_Num_float( this, IDC_EDIT_ROTZ, ABLDummy.m_fRotZ );
	SetWin_Num_float( this, IDC_EDIT_ROOTX, ABLDummy.m_fRootX );
	SetWin_Num_float( this, IDC_EDIT_ROOTY, ABLDummy.m_fRootY );
	SetWin_Num_float( this, IDC_EDIT_ROOTZ, ABLDummy.m_fRootZ );
	SetWin_Num_float( this, IDC_EDIT_ROTXF, ABLDummy.m_fRotX_F );
	SetWin_Num_float( this, IDC_EDIT_ROTYF, ABLDummy.m_fRotY_F );
	SetWin_Num_float( this, IDC_EDIT_ROTZF, ABLDummy.m_fRotZ_F );
	SetWin_Num_float( this, IDC_EDIT_ROOTXF, ABLDummy.m_fRootX_F );
	SetWin_Num_float( this, IDC_EDIT_ROOTYF, ABLDummy.m_fRootY_F );
	SetWin_Num_float( this, IDC_EDIT_ROOTZF, ABLDummy.m_fRootZ_F );
	SetWin_Check ( this, IDC_CHECK_BCPS, ABLDummy.m_bCPS );
	SetWin_Check ( this, IDC_CHECK_BCPS, ABLDummy.m_bCPS );

	return TRUE;
}
BOOL	CEditABLDlg::UpdateData2 ()
{
	SetWin_Text ( this, IDC_EDIT_ABFFILE, ABLDummy.m_strAbf.c_str() );
	SetWin_Text ( this, IDC_EDIT_CPSFILE, ABLDummy.m_strCPS.c_str() );
	SetWin_Text ( this, IDC_EDIT_SKEFILE, ABLDummy.m_strSkeleton.c_str() );
	SetWin_Text ( this, IDC_EDIT_BONELINK, ABLDummy.m_strBoneLink.c_str() );
	SetWin_Combo_Sel ( this, IDC_COMBO_TYPE, (int)ABLDummy.m_dwType );
	SetWin_Combo_Sel ( this, IDC_COMBO_SLOT, (int)ABLDummy.m_dwWeaponSlot );

	SetWin_Num_float( this, IDC_EDIT_ROTX, ABLDummy.m_vRot.x );
	SetWin_Num_float( this, IDC_EDIT_ROTY, ABLDummy.m_vRot.y );
	SetWin_Num_float( this, IDC_EDIT_ROTZ, ABLDummy.m_vRot.z );

	SetWin_Num_float( this, IDC_EDIT_ROOTX, ABLDummy.m_vRoot.x );
	SetWin_Num_float( this, IDC_EDIT_ROOTY, ABLDummy.m_vRoot.y );
	SetWin_Num_float( this, IDC_EDIT_ROOTZ, ABLDummy.m_vRoot.z );
	//SCALE
	SetWin_Num_float( this, IDC_EDIT_SCALEX, ABLDummy.m_vScale.x );
	SetWin_Num_float( this, IDC_EDIT_SCALEY, ABLDummy.m_vScale.y );
	SetWin_Num_float( this, IDC_EDIT_SCALEZ, ABLDummy.m_vScale.z );

	SetWin_Num_float( this, IDC_EDIT_ROTXF, ABLDummy.m_vRot_F.x );
	SetWin_Num_float( this, IDC_EDIT_ROTYF, ABLDummy.m_vRot_F.y );
	SetWin_Num_float( this, IDC_EDIT_ROTZF, ABLDummy.m_vRot_F.z );

	SetWin_Num_float( this, IDC_EDIT_ROOTXF, ABLDummy.m_vRoot_F.x );
	SetWin_Num_float( this, IDC_EDIT_ROOTYF, ABLDummy.m_vRoot_F.y );
	SetWin_Num_float( this, IDC_EDIT_ROOTZF, ABLDummy.m_vRoot_F.z );

	//SCale Mike915
	SetWin_Num_float( this, IDC_EDIT_SCALEXF, ABLDummy.m_vScale_F.x );
	SetWin_Num_float( this, IDC_EDIT_SCALEYF, ABLDummy.m_vScale_F.y );
	SetWin_Num_float( this, IDC_EDIT_SCALEZF, ABLDummy.m_vScale_F.z );
	SetWin_Check ( this, IDC_CHECK_BCPS, ABLDummy.m_bCPS );

	return TRUE;
}
BOOL	CEditABLDlg::SaveData ()
{
	ABLDummy.m_strAbf = GetWin_Text ( this, IDC_EDIT_ABFFILE ).GetString();
	ABLDummy.m_strCPS = GetWin_Text ( this, IDC_EDIT_CPSFILE ).GetString();
	ABLDummy.m_strSkeleton = GetWin_Text ( this, IDC_EDIT_SKEFILE ).GetString();
	ABLDummy.m_strBoneLink = GetWin_Text ( this, IDC_EDIT_BONELINK ).GetString();
	ABLDummy.m_dwType = (EMPIECECHAR) GetWin_Combo_Sel ( this, IDC_COMBO_TYPE );
	ABLDummy.m_dwWeaponSlot = (EMPEACEZONEWEAPON) GetWin_Combo_Sel ( this,  IDC_COMBO_SLOT );

	ABLDummy.m_vRot.x = GetWin_Num_float( this, IDC_EDIT_ROTX );
	ABLDummy.m_vRot.y = GetWin_Num_float( this, IDC_EDIT_ROTY );
	ABLDummy.m_vRot.z = GetWin_Num_float( this, IDC_EDIT_ROTZ );

	ABLDummy.m_vRoot.x = GetWin_Num_float( this, IDC_EDIT_ROOTX );
	ABLDummy.m_vRoot.y = GetWin_Num_float( this, IDC_EDIT_ROOTY );
	ABLDummy.m_vRoot.z = GetWin_Num_float( this, IDC_EDIT_ROOTZ );


	ABLDummy.m_vRot_F.x = GetWin_Num_float( this, IDC_EDIT_ROTXF );
	ABLDummy.m_vRot_F.y = GetWin_Num_float( this, IDC_EDIT_ROTYF );
	ABLDummy.m_vRot_F.z = GetWin_Num_float( this, IDC_EDIT_ROTZF );


	ABLDummy.m_vRoot_F.x = GetWin_Num_float( this, IDC_EDIT_ROOTXF );
	ABLDummy.m_vRoot_F.y = GetWin_Num_float( this, IDC_EDIT_ROOTYF );
	ABLDummy.m_vRoot_F.z = GetWin_Num_float( this, IDC_EDIT_ROOTZF );

	ABLDummy.m_vScale.x = GetWin_Num_float( this, IDC_EDIT_SCALEX );
	ABLDummy.m_vScale.y = GetWin_Num_float( this, IDC_EDIT_SCALEY );
	ABLDummy.m_vScale.z = GetWin_Num_float( this, IDC_EDIT_SCALEZ );


	ABLDummy.m_vScale_F.x = GetWin_Num_float( this, IDC_EDIT_SCALEXF );
	ABLDummy.m_vScale_F.y = GetWin_Num_float( this, IDC_EDIT_SCALEYF );
	ABLDummy.m_vScale_F.z = GetWin_Num_float( this, IDC_EDIT_SCALEZF );

	if ( strcmp( ABLDummy.m_strCPS.c_str() , _T("") ) != 0 )
	{
		ABLDummy.m_bCPS = TRUE;
	}

	return TRUE;
}





