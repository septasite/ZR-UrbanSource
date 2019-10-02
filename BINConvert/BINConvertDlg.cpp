// BINConvertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BINConvert.h"
#include "BINConvertDlg.h"

#include "StringUtils.h"
#include "EtcFunction.h"

#include ".\binconvertdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBINConvertDlg dialog



CBINConvertDlg::CBINConvertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBINConvertDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBINConvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBINConvertDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_LOAD_BIN, OnBnClickedLoadBin)
	ON_BN_CLICKED(IDC_SAVE_BIN, OnBnClickedSaveBin)
	ON_BN_CLICKED(IDC_LOAD_CFG, OnBnClickedLoadCfg)
	ON_BN_CLICKED(IDC_SAVE_CFG, OnBnClickedSaveCfg)
END_MESSAGE_MAP()


// CBINConvertDlg message handlers

BOOL CBINConvertDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBINConvertDlg::OnPaint() 
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
HCURSOR CBINConvertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBINConvertDlg::OnBnClickedLoadBin()
{
	CString szFilterInput = "BIN|*.bin|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath ();
	if ( dlgInput.DoModal() != IDOK ) return;

	CleanUp();

	BOOL bOK = BinFile.LoadFile ( dlgInput.GetFileName() );

	if ( bOK )
	{
		DWORD	dwNum		= BinFile.m_listAnimation.size();
		DWORD	dwNumUP		= BinFile.m_listAniUPBODY.size();

		CString strNum;
		CString strNumUp;
		strNum.Format ("%d",dwNum);
		strNumUp.Format ("%d",dwNumUP);

		SetWin_Text ( this, IDC_EDIT_UP, strNumUp.GetString() );
		SetWin_Text ( this, IDC_EDIT_DOWN, strNum.GetString() );

		SetWin_Text ( this, IDC_EDIT_LOAD_BIN, dlgInput.GetFileName().GetString() );
		SetWin_Text ( this, IDC_EDIT_SAVE_BIN, "" );
	}
}

void CBINConvertDlg::OnBnClickedSaveBin()
{
	CString szFilter = "BIN File (*.bin)|*.bin|";
	CFileDialog dlg(FALSE,".bin",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
	(CBINConvertDlg*)this);
	dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath ();

	if ( dlg.DoModal() == IDOK )
	{
		BOOL bOK = BinFile.SaveFile ( dlg.GetFileName() );
		if ( bOK )
		{
			SetWin_Text ( this, IDC_EDIT_SAVE_BIN, dlg.GetFileName().GetString() );
			MessageBox ( "Save Done :P" );
		}
	}
}

void CBINConvertDlg::OnBnClickedLoadCfg()
{
	CString szFilterInput = "CFG|*.cfg|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath ();
	if ( dlgInput.DoModal() != IDOK ) return;

	CleanUp();

	BOOL bOK = CfgFile.LoadFile ( dlgInput.GetFileName(),NULL );

	if ( bOK )
	{
		SetWin_Text ( this, IDC_EDIT_LOAD_CFG, dlgInput.GetFileName().GetString() );
		SetWin_Text ( this, IDC_EDIT_SAVE_CFG, "" );
	}
}


void CBINConvertDlg::OnBnClickedSaveCfg()
{
	CString szFilter = "CFG File (*.cfg)|*.cfg|";
	CFileDialog dlg(FALSE,".bin",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
	(CBINConvertDlg*)this);
	dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath ();

	if ( dlg.DoModal() == IDOK )
	{
		BOOL bOK = CfgFile.SaveFile ( dlg.GetFileName() );
		if ( bOK )
		{
			SetWin_Text ( this, IDC_EDIT_SAVE_CFG, dlg.GetFileName().GetString() );
		}
	}
}

void CBINConvertDlg::CleanUp()
{
}