// TabCNV.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "TabCNV.h"
#include "ToolTab.h"
#include ".\tabcnv.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include "HexData.h"

// CTabCNV dialog

IMPLEMENT_DYNAMIC(CTabCNV, CPropertyPage)
CTabCNV::CTabCNV(LOGFONT logfont)
	: CPropertyPage(CTabCNV::IDD)
	,m_pFont( NULL )
	,m_strInput(_T(""))
	,m_strOutput(_T(""))
	,m_strResult(_T(""))
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CTabCNV::~CTabCNV()
{
}

void CTabCNV::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_HEXTYPE, m_cHexType );
	DDX_Control(pDX, IDC_COMBO_CNVTYPE, m_cType );
	DDX_Control(pDX, IDC_COMBO_CNVMODE, m_cMode );
	DDX_Control(pDX, IDC_EDIT_CNVLOG, m_cEditResult );
	DDX_Control(pDX, IDC_EDIT_CNVLOGERR, m_cEditErr );
}


BEGIN_MESSAGE_MAP(CTabCNV, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_HEXCNV, OnBnClickedButtonHexcnv)
	ON_BN_CLICKED(IDC_BUTTON_IN, OnBnClickedButtonIn)
	ON_BN_CLICKED(IDC_BUTTON_OUT, OnBnClickedButtonOut)
	ON_BN_CLICKED(IDC_BUTTON_CONVERT, OnBnClickedButtonConvert)
	ON_CBN_SELCHANGE(IDC_COMBO_CNVMODE, OnCbnSelchangeComboCnvmode)
	ON_CBN_SELCHANGE(IDC_COMBO_CNVTYPE, OnCbnSelchangeComboCnvtype)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, OnBnClickedButtonEqual)
END_MESSAGE_MAP()


// CTabCNV message handlers
BOOL CTabCNV::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	if (!m_bActive)
	{
		SetWin_ShowWindow ( this, IDC_BUTTON_OUT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_BUTTON_CONVERT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_BUTTON_EQUAL, SW_HIDE );

		CString strHexType[HEXCNV_SIZE] = 
		{
			"HEX > DEC (RanSetFile)",
			"DEC > HEX (RanSetFile)",
			"HEX > DEC (Normal)",
			"DEC > HEX (Normal)",
		};

		CString strType[CNVTYPE_SIZE] = 
		{
			"EGP Convert",
			"BIN Convert",
			"CFG Convert",
			"CPS Convert",
			"CPS Ran2 Convert",
			"CHF Convert",
			"ABF Convert",
		};

		CString strMode[CNVMODE_SIZE] = 
		{
			"File",
			"Folder",
		};

		for ( int i = 0; i < CNVTYPE_SIZE; ++i )
		{
			m_cType.InsertString( i, strType[i].GetString() );
		}

		for ( int i = 0; i < CNVMODE_SIZE; ++i )
		{
			m_cMode.InsertString( i, strMode[i].GetString() );
		}

		for ( int i = 0; i < HEXCNV_SIZE; ++i )
		{
			m_cHexType.InsertString( i, strHexType[i].GetString() );
		}

		m_cHexType.SetCurSel( 0 );
		m_cType.SetCurSel( 0 );
		m_cMode.SetCurSel( 0 );
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTabCNV::OnBnClickedButtonHexcnv()
{
	CString strVal1 = GetWin_Text(this,IDC_EDIT_D1).GetString();
	CString strVal2 = "";
	HEXTYPE hextype = ( HEXTYPE ) m_cHexType.GetCurSel();

	switch ( hextype )
	{
	case HEX2DEC_RAN:
		{
			strVal2.Format ("%s",HexData::Hex2DecRan( strVal1.GetString() ).GetString() );
		}break;
	case DEC2HEX_RAN:
		{
			strVal2.Format ("%s",HexData::Dec2HexRan( strVal1.GetString() ).GetString() );
		}break;
	case HEX2DEC_NOR:
		{
			strVal2.Format ("%s",HexData::Hex2DecNor( strVal1.GetString() ).GetString() );
		}break;
	case DEC2HEX_NOR:
		{
			strVal2.Format ("%s",HexData::Dec2HexNor( strVal1.GetString() ).GetString() );
		}break;
	};

	SetWin_Text(this,IDC_EDIT_D2,strVal2.GetString());
}

void CTabCNV::OnBnClickedButtonIn()
{
	int nMode = m_cMode.GetCurSel();
	int nType = m_cType.GetCurSel();
	CString strLog;
	switch (nMode)
	{
	case CNV_FILE: // file mode
		{
			switch (nType)
			{
			case CNV_EGP: //egp convert
				{
					CString szFilterInput = "EGP|*.egp|";
					CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = DxEffSinglePropGMan::GetInstance().GetPath();
					if ( dlgInput.DoModal() != IDOK ) return;
				
					HRESULT hr = pPropGroup.LoadFile ( dlgInput.GetFileName(),NULL );
					if ( SUCCEEDED(hr) )
					{
						SetWin_Text ( this, IDC_EDIT_IN, dlgInput.GetFileName().GetString() );
						SetWin_Text ( this, IDC_EDIT_OUT, "" );
						SetWin_ShowWindow ( this, IDC_BUTTON_OUT, SW_SHOW );
						strLog.Format ("Open EGP Success File: %s",dlgInput.GetFileName().GetString() );
						strFileName = dlgInput.GetFileName().GetString();
						m_bActive = TRUE;
					}
					else
					{
						strLog.Format ("Open EGP Fail File: %s",dlgInput.GetFileName().GetString() );
						AddEditStringErr( strLog );
					}
				}break;

			case CNV_BIN: //bin convert
				{
					CString szFilterInput = "BIN|*.bin|";
					CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath ();
					if ( dlgInput.DoModal() != IDOK ) return;
				
					BOOL bOK = BinFile.LoadFile ( dlgInput.GetFileName() );
					if ( bOK )
					{
						SetWin_Text ( this, IDC_EDIT_IN, dlgInput.GetFileName().GetString() );
						SetWin_Text ( this, IDC_EDIT_OUT, "" );
						SetWin_ShowWindow ( this, IDC_BUTTON_OUT, SW_SHOW );
						strLog.Format ("Open BIN Success File: %s",dlgInput.GetFileName().GetString() );
						strFileName = dlgInput.GetFileName().GetString();
						m_bActive = TRUE;
					}
					else
					{
						strLog.Format ("Open BIN Fail File: %s",dlgInput.GetFileName().GetString() );
						AddEditStringErr( strLog );
					}
				}break;

			case CNV_CFG: //cfg convert
				{
					CString szFilterInput = "CFG|*.cfg|";
					CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath ();
					if ( dlgInput.DoModal() != IDOK ) return;
				
					BOOL bOK = CfgFile.LoadFileTool ( dlgInput.GetFileName(),NULL );
					if ( bOK )
					{
						SetWin_Text ( this, IDC_EDIT_IN, dlgInput.GetFileName().GetString() );
						SetWin_Text ( this, IDC_EDIT_OUT, "" );
						SetWin_ShowWindow ( this, IDC_BUTTON_OUT, SW_SHOW );
						strLog.Format ("Open CFG Success File: %s",dlgInput.GetFileName().GetString() );
						strFileName = dlgInput.GetFileName().GetString();
						m_bActive = TRUE;
					}
					else
					{
						strLog.Format ("Open CFG Fail File: %s",dlgInput.GetFileName().GetString() );
						AddEditStringErr( strLog );
					}
				}break;
			case CNV_CPS: //cps convert
				{
					CString szFilterInput = "Piece (*.cps,*.aps,*.vps)|*.cps;*.aps;*.vps|";
					CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath();
					if ( dlgInput.DoModal() != IDOK ) return;

					Reset();
					HRESULT hr = m_pPiece.LoadPieceTool ( dlgInput.GetFileName(),NULL,TRUE );

					if ( SUCCEEDED(hr) )
					{
						SetWin_Text ( this, IDC_EDIT_IN, dlgInput.GetFileName().GetString() );
						SetWin_Text ( this, IDC_EDIT_OUT, "" );
						SetWin_ShowWindow ( this, IDC_BUTTON_OUT, SW_SHOW );
						strLog.Format ("Open Piece Success File: %s",dlgInput.GetFileName().GetString() );
						strFileName = dlgInput.GetFileName().GetString();
						m_bActive = TRUE;
					}
					else
					{
						strLog.Format ("Open Piece Fail File: %s",dlgInput.GetFileName().GetString() );
						AddEditStringErr( strLog );
					}
				}break;
			case CNV_CPSR2: //cps Ran2 convert
				{
					CString szFilterInput = "Piece (*.cps,*.aps,*.vps)|*.cps;*.aps;*.vps|";
					CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath();
					if ( dlgInput.DoModal() != IDOK ) return;

					Reset();
					HRESULT hr = m_pPiece.LoadPieceToolRan2 ( dlgInput.GetFileName(),NULL,TRUE );

					if ( SUCCEEDED(hr) )
					{
						SetWin_Text ( this, IDC_EDIT_IN, dlgInput.GetFileName().GetString() );
						SetWin_Text ( this, IDC_EDIT_OUT, "" );
						SetWin_ShowWindow ( this, IDC_BUTTON_OUT, SW_SHOW );
						strLog.Format ("Open Piece Ran2 Success File: %s",dlgInput.GetFileName().GetString() );
						strFileName = dlgInput.GetFileName().GetString();
						m_bActive = TRUE;
					}
					else
					{
						strLog.Format ("Open Piece Ran2 Fail File: %s",dlgInput.GetFileName().GetString() );
						AddEditStringErr( strLog );
					}
				}break;
			case CNV_CHF: //CHF
				{
					CString szFilterInput = "CHF|*.chf|";
					CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = DxSkinCharDataContainer::GetInstance().GetPath();
					if ( dlgInput.DoModal() != IDOK ) return;

					BOOL bOK = m_pChfCode.LoadFile ( dlgInput.GetFileName() );
					if ( bOK )
					{
						SetWin_Text ( this, IDC_EDIT_IN, dlgInput.GetFileName().GetString() );
						SetWin_Text ( this, IDC_EDIT_OUT, "" );
						SetWin_ShowWindow ( this, IDC_BUTTON_OUT, SW_SHOW );
						strLog.Format ("Open CHF Success File: %s",dlgInput.GetFileName().GetString() );
						strFileName = dlgInput.GetFileName().GetString();
						m_bActive = TRUE;
					}
					else
					{
						strLog.Format ("Open CHF Fail File: %s",dlgInput.GetFileName().GetString() );
						AddEditStringErr( strLog );
					}
				}break;
			case CNV_ABF: //ABF
				{
					CString szFilterInput = "ABF|*.abf|";
					CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
					if ( dlgInput.DoModal() != IDOK ) return;

					BOOL bOK = m_pAbfCode.LoadFile_PH ( dlgInput.GetFileName() );
					if ( bOK )
					{
						SetWin_Text ( this, IDC_EDIT_IN, dlgInput.GetFileName().GetString() );
						SetWin_Text ( this, IDC_EDIT_OUT, "" );
						SetWin_ShowWindow ( this, IDC_BUTTON_OUT, SW_SHOW );
						strLog.Format ("Open ABF Success File: %s",dlgInput.GetFileName().GetString() );
						strFileName = dlgInput.GetFileName().GetString();
						m_bActive = TRUE;
					}
					else
					{
						strLog.Format ("Open ABF Fail File: %s",dlgInput.GetFileName().GetString() );
						AddEditStringErr( strLog );
					}
				}break;
			};
		}break;
	case CNV_FOLDER:
		{
			BROWSEINFO biInput;
			ZeroMemory(&biInput, sizeof(BROWSEINFO));
			biInput.hwndOwner = m_hWnd;
			biInput.lpszTitle = "Select Input Folder";
			biInput.pidlRoot = NULL;
			biInput.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_NONEWFOLDERBUTTON | BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;

			LPITEMIDLIST pidlFolderInput = SHBrowseForFolder(&biInput);
			
			if (pidlFolderInput == NULL) return;

			TCHAR szPathInput[_MAX_PATH] = {0};
			SHGetPathFromIDList(pidlFolderInput, szPathInput);
			m_strInput = szPathInput;
			SetDlgItemText( IDC_EDIT_IN, szPathInput );
			strLog.Format ("Input Folder: %s",m_strInput.GetString() );
			UpdateData(true);

			SetWin_ShowWindow ( this,IDC_BUTTON_OUT, SW_SHOW );
			SetWin_ShowWindow ( this,IDC_BUTTON_EQUAL, SW_SHOW );
			m_bActive = TRUE;
		}break;
	};

	AddEditString( strLog.GetString() );
}

void CTabCNV::OnBnClickedButtonOut()
{
	int nMode = m_cMode.GetCurSel();
	int nType = m_cType.GetCurSel();
	CString strLog;
	CString strMsg;
	switch (nMode)
	{
	case CNV_FILE: // file mode
		{
			switch (nType)
			{
			case CNV_EGP: //egp convert
				{
					CString szFilter = "EGP (*.egp)|*.egp|";
					CFileDialog dlg(FALSE,".egp",strFileName.GetString(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
					(CTabCNV*)this);
				
					dlg.m_ofn.lpstrInitialDir = DxEffSinglePropGMan::GetInstance().GetPath();
					if ( dlg.DoModal() == IDOK )
					{
						HRESULT hr = pPropGroup.SaveFile( dlg.GetFileName() );
						if ( SUCCEEDED(hr) )
						{
							strLog.Format ("Save EGP Success File: %s",dlg.GetFileName().GetString() );
							strMsg.Format ("%s",dlg.GetFileName().GetString() );
							pPropGroup.CleanUp();
						}
						else
						{
							strLog.Format ("Save EGP Fail File: %s",dlg.GetFileName().GetString() );
							strMsg.Format ("Save File Error: %s",dlg.GetFileName().GetString() );
							AddEditStringErr( strLog );
						}
					}

				}break;

			case CNV_BIN: //bin convert
				{
					CString szFilter = "BIN (*.bin)|*.bin|";
					CFileDialog dlg(FALSE,".bin",strFileName.GetString(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
					(CTabCNV*)this);
					dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath ();
				
					if ( dlg.DoModal() == IDOK )
					{
						BOOL bOK = BinFile.SaveFile ( dlg.GetFileName() );
						if ( bOK )
						{
							strLog.Format ("Save BIN Success File: %s",dlg.GetFileName().GetString() );
							strMsg.Format ("%s",dlg.GetFileName().GetString() );
						}
						else
						{
							strLog.Format ("Save BIN Fail File: %s",dlg.GetFileName().GetString() );
							strMsg.Format ("Save File Error: %s",dlg.GetFileName().GetString() );
							AddEditStringErr( strLog );
						}
					}
				}break;

			case CNV_CFG: //cfg convert
				{
					CString szFilter = "CFG (*.cfg)|*.cfg|";
					CFileDialog dlg(FALSE,".cfg",strFileName.GetString(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
					(CTabCNV*)this);
					dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath ();
				
					if ( dlg.DoModal() == IDOK )
					{
						BOOL bOK = CfgFile.SaveFile ( dlg.GetFileName() );
						if ( bOK )
						{
							strLog.Format ("Save CFG Success File: %s",dlg.GetFileName().GetString() );
							strMsg.Format ("%s",dlg.GetFileName().GetString() );
							CfgFile.CleanUp();
						}
						else
						{
							strLog.Format ("Save CFG Fail File: %s",dlg.GetFileName().GetString() );
							strMsg.Format ("Save File Error: %s",dlg.GetFileName().GetString() );
							AddEditStringErr( strLog );
						}
					}
				}break;
			case CNV_CPS: //cps convert
			case CNV_CPSR2:
				{
					CString szFilter = "Piece (*.cps,*.aps,*.vps)|*.cps;*.aps;*.vps|";
					CFileDialog dlg(FALSE,"",strFileName.GetString(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
					(CTabCPS*)this);

					dlg.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath();
					if ( dlg.DoModal() == IDOK )
					{
						HRESULT hr = m_pPiece.SavePieceTool( dlg.GetFileName() );
						if ( SUCCEEDED(hr) )
						{
							strLog.Format ("Save Piece Success File: %s",dlg.GetFileName().GetString() );
							strMsg.Format ("%s",dlg.GetFileName().GetString() );
							m_pPiece.ClearAll ();
						}
						else
						{
							strLog.Format ("Save Piece Fail File: %s",dlg.GetFileName().GetString() );
							strMsg.Format ("Save File Error: %s",dlg.GetFileName().GetString() );
							AddEditStringErr( strLog );
						}
					}
				}break;
			case CNV_CHF: //chf convert
				{
					CString szFilter = "CHF (*.chf)|*.chf|";
					CFileDialog dlg(FALSE,".chf",strFileName.GetString(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
					(CTabCNV*)this);
					dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath ();
				
					if ( dlg.DoModal() == IDOK )
					{
						BOOL bOK = m_pChfCode.SaveFileOld ( dlg.GetFileName() );
						if ( bOK )
						{
							strLog.Format ("Save CHF Success File: %s",dlg.GetFileName().GetString() );
							strMsg.Format ("%s",dlg.GetFileName().GetString() );
							m_pChfCode.Reset();
						}
						else
						{
							strLog.Format ("Save CHF Fail File: %s",dlg.GetFileName().GetString() );
							strMsg.Format ("Save File Error: %s",dlg.GetFileName().GetString() );
							AddEditStringErr( strLog );
						}
					}
				}break;
			case CNV_ABF: //chf convert
				{
					CString szFilter = "ABF (*.abf)|*.abf|";
					CFileDialog dlg(FALSE,".chf",strFileName.GetString(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
					(CTabCNV*)this);
					dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath ();
				
					if ( dlg.DoModal() == IDOK )
					{
						BOOL bOK = m_pAbfCode.SaveFileOld ( dlg.GetFileName() );
						if ( bOK )
						{
							strLog.Format ("Save ABF Success File: %s",dlg.GetFileName().GetString() );
							strMsg.Format ("%s",dlg.GetFileName().GetString() );
							m_pAbfCode.Reset();
						}
						else
						{
							strLog.Format ("Save ABF Fail File: %s",dlg.GetFileName().GetString() );
							strMsg.Format ("Save File Error: %s",dlg.GetFileName().GetString() );
							AddEditStringErr( strLog );
						}
					}
				}break;
			};
		}break;
	case CNV_FOLDER:
		{
			BROWSEINFO biOutput;
			ZeroMemory(&biOutput, sizeof(BROWSEINFO));
			biOutput.hwndOwner = m_hWnd;
			biOutput.lpszTitle = "Select Ouput Folder"; 
			biOutput.pidlRoot = NULL;
			biOutput.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_NONEWFOLDERBUTTON | BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;

			LPITEMIDLIST pidlFolderOutput = SHBrowseForFolder(&biOutput);
			
			if (pidlFolderOutput == NULL) return;

			TCHAR szPathOutput[_MAX_PATH] = {0};
			SHGetPathFromIDList(pidlFolderOutput, szPathOutput);
			
			SetDlgItemText( IDC_EDIT_OUT, szPathOutput );
			
			SetWin_ShowWindow ( this, IDC_BUTTON_CONVERT, SW_SHOW );
			m_strOutput = szPathOutput;
			strLog.Format ("OutPut Folder: %s",m_strOutput.GetString() );
			UpdateData(true);
		}break;
	};
	AddEditString( strLog.GetString() );
	SetWin_Text ( this, IDC_EDIT_OUT, strMsg.GetString() );
}

void CTabCNV::OnBnClickedButtonEqual()
{
	SetDlgItemText( IDC_EDIT_OUT, m_strInput );
	m_strOutput = m_strInput.GetString();
	UpdateData(true);
	SetWin_ShowWindow ( this, IDC_BUTTON_CONVERT, SW_SHOW );
}

void CTabCNV::OnBnClickedButtonConvert()
{
	int nType = m_cType.GetCurSel();
	CString strLog;

	CString strFind = m_strInput.GetString();
	strFind += "\\*";

	CString strOutFile, strOutPath;
	strOutPath = m_strOutput.GetString();
	strOutPath += "\\";

	CString strInFile, strInPath;
	strInPath = m_strInput.GetString();
	strInPath += "\\";

	CString strFile;
	
	CFileFind finder;	
	BOOL bFind ( TRUE );

	if ( !finder.FindFile( strFind ) )
	{
		bFind = FALSE;
	}

	int nCntFile =0, nCntSuccess = 0;
	CString strTemp;

	while( bFind )
	{
		nCntFile++;
		bFind = finder.FindNextFile();
		strFile = finder.GetFileName();
		strInFile = strInPath;
		strInFile += strFile;
		strOutFile = strOutPath;
		strOutFile += strFile;

		switch (nType)
		{
		case CNV_EGP: //egp convert
			{
				HRESULT hr = pPropGroup.LoadFile ( strInFile ,NULL );
				if ( SUCCEEDED(hr) )
				{
					CString strResult;
					strResult.Format( "EGP Convert Load Success::File(%s)", strInFile );
					AddEditString( strResult );

					HRESULT hr2 = pPropGroup.SaveFile( strOutFile );
					if ( SUCCEEDED(hr2) )
					{
						CString strResult;
						strResult.Format( "EGP Convert Save Success::File(%s)",strOutFile );
						AddEditString( strResult );
						nCntSuccess++;
						pPropGroup.CleanUp();
					}
					else
					{
						CString strResult;
						strResult.Format( "EGP Convert Save Failure::File(%s)",strOutFile );
						AddEditString( strResult );
						AddEditStringErr( strResult );
					}
				}
				else
				{
					CString strResult;
					strResult.Format( "EGP Convert Load Failure::File(%s)", strInFile  );
					AddEditString( strResult );
					AddEditStringErr( strResult );
				}
			}break;

		case CNV_BIN: //bin convert
			{
				BOOL bOK = BinFile.LoadFile ( strInFile );
				if ( bOK )
				{
					CString strResult;
					strResult.Format( "BIN Convert Load Success::File(%s)", strInFile );
					AddEditString( strResult );

					BOOL bOK2 = BinFile.SaveFile ( strOutFile );
					if ( bOK2 )
					{
						CString strResult;
						strResult.Format( "BIN Convert Save Success::File(%s)",strOutFile );
						AddEditString( strResult );
						nCntSuccess++;
					}
					else
					{
						CString strResult;
						strResult.Format( "BIN Convert Save Failure::File(%s)",strOutFile );
						AddEditString( strResult );
						AddEditStringErr( strResult );
					}
				}
				else
				{
					CString strResult;
					strResult.Format( "BIN Convert Load Failure::File(%s)", strInFile  );
					AddEditString( strResult );
					AddEditStringErr( strResult );
				}
			}break;

		case CNV_CFG: //cfg convert
			{
				BOOL bOK = CfgFile.LoadFileTool ( strInFile ,NULL );
				if ( bOK )
				{
					CString strResult;
					strResult.Format( "CFG Convert Load Success::File(%s)", strInFile );
					AddEditString( strResult );

					BOOL bOK2 = CfgFile.SaveFile ( strOutFile );
					if ( bOK2 )
					{
						CString strResult;
						strResult.Format( "CFG Convert Save Success::File(%s)",strOutFile );
						AddEditString( strResult );
						nCntSuccess++;
						CfgFile.CleanUp();
					}
					else
					{
						CString strResult;
						strResult.Format( "CFG Convert Save Failure::File(%s)",strOutFile );
						AddEditString( strResult );
						AddEditStringErr( strResult );
					}
				}
				else
				{
					CString strResult;
					strResult.Format( "CFG Convert Load Failure::File(%s)", strInFile  );
					AddEditString( strResult );
					AddEditStringErr( strResult );
				}	
			}break;
		case CNV_CPS: //cps convert
			{
				HRESULT hr = m_pPiece.LoadPieceTool ( strInFile,NULL,TRUE );
				if ( SUCCEEDED(hr) )
				{
					CString strResult;
					strResult.Format( "CPS Convert Load Success::File(%s)", strInFile );
					AddEditString( strResult );

					HRESULT hr2 = m_pPiece.SavePieceTool( strOutFile );
					if ( SUCCEEDED(hr2) )
					{
						CString strResult;
						strResult.Format( "CPS Convert Save Success::File(%s)",strOutFile );
						AddEditString( strResult );
						nCntSuccess++;
						m_pPiece.ClearAll ();
					}
					else
					{
						CString strResult;
						strResult.Format( "CPS Convert Save Failure::File(%s)",strOutFile );
						AddEditString( strResult );
						AddEditStringErr( strResult );
					}
				}
				else
				{
					CString strResult;
					strResult.Format( "CPS Convert Load Failure::File(%s)", strInFile  );
					AddEditString( strResult );
					AddEditStringErr( strResult );
				}
			}break;
		case CNV_CPSR2: //cps convert
			{
				HRESULT hr = m_pPiece.LoadPieceToolRan2 ( strInFile,NULL,TRUE );
				if ( SUCCEEDED(hr) )
				{
					CString strResult;
					strResult.Format( "CPS Ran2 Convert Load Success::File(%s)", strInFile );
					AddEditString( strResult );

					HRESULT hr2 = m_pPiece.SavePieceTool( strOutFile );
					if ( SUCCEEDED(hr2) )
					{
						CString strResult;
						strResult.Format( "CPS Ran2 Convert Save Success::File(%s)",strOutFile );
						AddEditString( strResult );
						nCntSuccess++;
						m_pPiece.ClearAll ();
					}
					else
					{
						CString strResult;
						strResult.Format( "CPS Ran2 Convert Save Failure::File(%s)",strOutFile );
						AddEditString( strResult );
						AddEditStringErr( strResult );
					}
				}
				else
				{
					CString strResult;
					strResult.Format( "CPS Ran2 Convert Load Failure::File(%s)", strInFile  );
					AddEditString( strResult );
					AddEditStringErr( strResult );
				}
			}break;
		case CNV_CHF: //cfg convert
			{
				BOOL bOK = m_pChfCode.LoadFile ( strInFile );
				if ( bOK )
				{
					CString strResult;
					strResult.Format( "CHF Convert Load Success::File(%s)", strInFile );
					AddEditString( strResult );

					BOOL bOK2 = m_pChfCode.SaveFileOld ( strOutFile );
					if ( bOK2 )
					{
						CString strResult;
						strResult.Format( "CHF Convert Save Success::File(%s)",strOutFile );
						AddEditString( strResult );
						nCntSuccess++;
						m_pChfCode.Reset();
					}
					else
					{
						CString strResult;
						strResult.Format( "CHF Convert Save Failure::File(%s)",strOutFile );
						AddEditString( strResult );
						AddEditStringErr( strResult );
					}
				}
				else
				{
					CString strResult;
					strResult.Format( "CHF Convert Load Failure::File(%s)", strInFile  );
					AddEditString( strResult );
					AddEditStringErr( strResult );
				}	
			}break;
		case CNV_ABF: //abf convert
			{
				BOOL bOK = m_pAbfCode.LoadFile_PH ( strInFile );
				if ( bOK )
				{
					CString strResult;
					strResult.Format( "ABF Convert Load Success::File(%s)", strInFile );
					AddEditString( strResult );

					BOOL bOK2 = m_pAbfCode.SaveFileOld ( strOutFile );
					if ( bOK2 )
					{
						CString strResult;
						strResult.Format( "ABF Convert Save Success::File(%s)",strOutFile );
						AddEditString( strResult );
						nCntSuccess++;
						m_pAbfCode.Reset();
					}
					else
					{
						CString strResult;
						strResult.Format( "ABF Convert Save Failure::File(%s)",strOutFile );
						AddEditString( strResult );
						AddEditStringErr( strResult );
					}
				}
				else
				{
					CString strResult;
					strResult.Format( "ABF Convert Load Failure::File(%s)", strInFile  );
					AddEditString( strResult );
					AddEditStringErr( strResult );
				}	
			}break;
		};
	}
	CString sReport;
	sReport.Format( "Success File : %d File All : %d",nCntSuccess ,nCntFile );
	AddEditString( sReport.GetString() );
}

void CTabCNV::Reset()
{
	m_bActive = FALSE;

	m_cHexType.SetCurSel( 0 );
	m_cType.SetCurSel( 0 );
	m_cMode.SetCurSel( 0 );

	SetWin_ShowWindow ( this, IDC_BUTTON_CONVERT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_OUT, SW_HIDE );
	SetWin_Text(this,IDC_EDIT_IN,"");
	SetWin_Text(this,IDC_EDIT_OUT,"");
	m_strInput = "";
	m_strOutput = "";
}

void CTabCNV::AddEditString( const char* szInfo )
{
    int len = m_cEditResult.GetWindowTextLength();

	if ( m_cEditResult.GetWindowTextLength() >= m_cEditResult.GetLimitText() )
	{
		m_cEditResult.SetSel( 0 , m_cEditResult.GetWindowTextLength() );
	}else{
		m_cEditResult.SetSel( len, len );
	}
	m_cEditResult.ReplaceSel( szInfo );	

	len = m_cEditResult.GetWindowTextLength();
	m_cEditResult.SetSel( len, len );
	m_cEditResult.ReplaceSel( "\r\n" );

	return;
}

void CTabCNV::AddEditStringErr( const char* szInfo )
{
    int len = m_cEditErr.GetWindowTextLength();

	if ( m_cEditErr.GetWindowTextLength() >= m_cEditErr.GetLimitText() )
	{
		m_cEditErr.SetSel( 0 , m_cEditErr.GetWindowTextLength() );
	}else{
		m_cEditErr.SetSel( len, len );
	}
	m_cEditErr.ReplaceSel( szInfo );	

	len = m_cEditErr.GetWindowTextLength();
	m_cEditErr.SetSel( len, len );
	m_cEditErr.ReplaceSel( "\r\n" );

	return;
}

void CTabCNV::OnCbnSelchangeComboCnvmode()
{
	SetWin_ShowWindow ( this, IDC_BUTTON_CONVERT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_OUT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_EQUAL, SW_HIDE );
	SetWin_Text(this,IDC_EDIT_IN,"");
	SetWin_Text(this,IDC_EDIT_OUT,"");
	m_strInput = "";
	m_strOutput = "";
}

void CTabCNV::OnCbnSelchangeComboCnvtype()
{
	SetWin_ShowWindow ( this, IDC_BUTTON_CONVERT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_OUT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_EQUAL, SW_HIDE );
	SetWin_Text(this,IDC_EDIT_IN,"");
	SetWin_Text(this,IDC_EDIT_OUT,"");
	m_strInput = "";
	m_strOutput = "";
}


