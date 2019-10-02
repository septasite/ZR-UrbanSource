// TabCRY.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "TabCRY.h"
#include "ToolTab.h"
#include ".\tabcry.h"
#include "..\EngineLib\Crypt.h"
#include "EtcFunction.h"

// CTabCRY dialog

IMPLEMENT_DYNAMIC(CTabCRY, CPropertyPage)
CTabCRY::CTabCRY(LOGFONT logfont)
	: CPropertyPage(CTabCRY::IDD)
	,m_pFont( NULL )
	,m_strInput(_T(""))
	,m_strOutput(_T(""))
	,m_strResult(_T(""))
{
	m_bDlgInit = FALSE;
	m_bActive = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CTabCRY::~CTabCRY()
{
}

void CTabCRY::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OPEN, m_strInput );
	DDX_Text(pDX, IDC_EDIT_SAVE, m_strOutput );
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult );
	DDX_Control(pDX, IDC_TYPE, m_ComboType );
	DDX_Control(pDX, IDC_MODE, m_ComboMode );
	DDX_Control(pDX, IDC_EDIT_RESULT, m_cEditResult );
}


BEGIN_MESSAGE_MAP(CTabCRY, CPropertyPage)
	ON_BN_CLICKED(IDC_OPEN, OnBnClickedOpen)
	ON_BN_CLICKED(IDC_SAVE, OnBnClickedSave)
	ON_BN_CLICKED(IDC_SAMEFILE, OnBnClickedSamefile)
	ON_BN_CLICKED(IDC_REVERSE, OnBnClickedReverse)
	ON_BN_CLICKED(IDC_ENCRYPT, OnBnClickedEncrypt)
	ON_BN_CLICKED(IDC_DECRYPT, OnBnClickedDecrypt)
END_MESSAGE_MAP()


// CTabCRY message handlers
BOOL CTabCRY::OnInitDialog()
{
	if (!m_bActive)
	{
		CPropertyPage::OnInitDialog();
		m_bDlgInit = TRUE;

		m_ComboType.InsertString( 0, "RCC Files" );
		m_ComboType.InsertString( 1, "Texture (.mtf)" );
		m_ComboType.SetCurSel( 0 );

		m_ComboMode.InsertString( 0, "File Mode" );
		m_ComboMode.InsertString( 1, "Folder Mode" );
		m_ComboMode.SetCurSel( 0 );

		SetWin_ShowWindow ( this, IDC_ENCRYPT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_DECRYPT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_SAMEFILE, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_REVERSE, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_SAVE, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_EDIT_SAVE, SW_HIDE );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTabCRY::Reset()
{
	SetDlgItemText( IDC_EDIT_OPEN, "" );
	SetDlgItemText( IDC_EDIT_SAVE, "" );
	SetDlgItemText( IDC_EDIT_RESULT, "" );
	m_strInput = "";
	m_strOutput = "";
	m_strResult = "";

	SetWin_ShowWindow ( this, IDC_ENCRYPT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_DECRYPT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_SAMEFILE, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_REVERSE, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_SAVE, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_SAVE, SW_HIDE );
	m_bActive = FALSE;
}
void CTabCRY::OnBnClickedOpen()
{
	int Select = m_ComboMode.GetCurSel();
	switch( Select )
	{
	case FileCryption:
		{
			int nType = m_ComboType.GetCurSel();
			switch ( nType )
			{
			case RCC_CRYPTION:
				{
					CString szFilterInput = "ALL FILE TYPE|*.*|";
					CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = m_strInput;
					if ( dlgInput.DoModal() != IDOK ) return;
					CString strFileName = dlgInput.GetFileName();
					m_strInput = dlgInput.GetPathName();
					SetDlgItemText( IDC_EDIT_OPEN, dlgInput.GetPathName() );
					UpdateData(true);
					m_bActive = TRUE;
				}break;
			case TEX_CRYPTION:
				{
					CString szFilterInput = "Texture File (*.dds,*.tga,*.mtf)|*.dds;*.tga;*.mtf|";
					CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = m_strInput;
					if ( dlgInput.DoModal() != IDOK ) return;
					CString strFileName = dlgInput.GetFileName();
					m_strInput = dlgInput.GetPathName();
					SetDlgItemText( IDC_EDIT_OPEN, dlgInput.GetPathName() );
					UpdateData(true);
					m_bActive = TRUE;
				}break;
			default:
				{
					CString szFilterInput = "ALL FILE TYPE|*.*|";
					CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = m_strInput;
					if ( dlgInput.DoModal() != IDOK ) return;
					CString strFileName = dlgInput.GetFileName();
					m_strInput = dlgInput.GetPathName();
					SetDlgItemText( IDC_EDIT_OPEN, dlgInput.GetPathName() );
					UpdateData(true);
					m_bActive = TRUE;
				}break;
			}
			
			SetWin_ShowWindow ( this, IDC_SAMEFILE, SW_SHOW );
			SetWin_ShowWindow ( this, IDC_SAVE, SW_SHOW );
			SetWin_ShowWindow ( this, IDC_EDIT_SAVE, SW_SHOW );
		}break;
	case FolderCryption:
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
			SetDlgItemText( IDC_EDIT_OPEN, szPathInput );
			UpdateData(true);

			SetWin_ShowWindow ( this, IDC_SAMEFILE, SW_SHOW );
			SetWin_ShowWindow ( this, IDC_SAVE, SW_SHOW );
			SetWin_ShowWindow ( this, IDC_EDIT_SAVE, SW_SHOW );
			m_bActive = TRUE;

		}break;
	}
}

void CTabCRY::OnBnClickedSave()
{
	int Select = m_ComboMode.GetCurSel();
	switch( Select )
	{
	case FileCryption:
		{
			int nType = m_ComboType.GetCurSel();
			switch ( nType )
			{
				case RCC_CRYPTION:
				{
					CString szFilterInput = "ALL FILE TYPE|*.*|";
					CFileDialog dlgInput(false,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = m_strOutput;
					if ( dlgInput.DoModal() != IDOK ) return;
					CString strFileName = dlgInput.GetFileName();
					m_strOutput = dlgInput.GetPathName();
					SetDlgItemText( IDC_EDIT_SAVE, dlgInput.GetPathName() );
					UpdateData(true);
				}break;
				case TEX_CRYPTION:
				{
					CString szFilterInput = "Texture File (*.dds,*.tga,*.mtf)|*.dds;*.tga;*.mtf|";
					CFileDialog dlgInput(false,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = m_strOutput;
					if ( dlgInput.DoModal() != IDOK ) return;
					CString strFileName = dlgInput.GetFileName();
					m_strOutput = dlgInput.GetPathName();
					SetDlgItemText( IDC_EDIT_SAVE, dlgInput.GetPathName() );
					UpdateData(true);
				}break;
				default:
				{
					CString szFilterInput = "ALL FILE TYPE|*.*|";
					CFileDialog dlgInput(false,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
					dlgInput.m_ofn.lpstrInitialDir = m_strOutput;
					if ( dlgInput.DoModal() != IDOK ) return;
					CString strFileName = dlgInput.GetFileName();
					m_strOutput = dlgInput.GetPathName();
					SetDlgItemText( IDC_EDIT_SAVE, dlgInput.GetPathName() );
					UpdateData(true);
				}break;
			}
			SetWin_ShowWindow ( this, IDC_ENCRYPT, SW_SHOW );
			SetWin_ShowWindow ( this, IDC_DECRYPT, SW_SHOW );
			SetWin_ShowWindow ( this, IDC_REVERSE, SW_SHOW );
		}break;
	case FolderCryption:
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
			
			SetDlgItemText( IDC_EDIT_SAVE, szPathOutput );
			m_strOutput = szPathOutput;
			UpdateData(true);
			SetWin_ShowWindow ( this, IDC_ENCRYPT, SW_SHOW );
			SetWin_ShowWindow ( this, IDC_DECRYPT, SW_SHOW );
			SetWin_ShowWindow ( this, IDC_REVERSE, SW_SHOW );
		}break;
	}
}

void CTabCRY::OnBnClickedSamefile()
{
	SetDlgItemText( IDC_EDIT_SAVE, m_strInput );
	UpdateData(true);
	SetWin_ShowWindow ( this, IDC_ENCRYPT, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_DECRYPT, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_REVERSE, SW_SHOW );
}

void CTabCRY::OnBnClickedReverse()
{
	const char * cInput = m_strInput;
	const char * cOutput = m_strOutput;
	SetDlgItemText( IDC_EDIT_OPEN, cOutput );
	SetDlgItemText( IDC_EDIT_SAVE, cInput );
	UpdateData(true);
}

void CTabCRY::OnBnClickedEncrypt()
{
	int Select = m_ComboMode.GetCurSel();
	switch( Select )
	{
	case FileCryption:
		{
			if ( m_strInput == "" || m_strOutput == "" )
				break;
			FileEncryption();
		}break;
	case FolderCryption:
		{
			if ( m_strInput == "" || m_strOutput == "" )
				break;
			FolderEncryption( m_strInput , m_strOutput );
		}break;
	}
}

void CTabCRY::OnBnClickedDecrypt()
{
	int Select = m_ComboMode.GetCurSel();
	switch( Select )
	{
	case FileCryption:
		{
			if ( m_strInput == "" || m_strOutput == "" )
				break;
			FileDecryption();
		}break;
	case FolderCryption:
		{
			if ( m_strInput == "" || m_strOutput == "" )
				break;
			FolderDecryption( m_strInput , m_strOutput );
		}break;
	}
}

BOOL CTabCRY::FileEncryption()
{
	int Select = m_ComboType.GetCurSel();
	switch(Select)
	{
		case RCC_CRYPTION:
			{
				if ( Encryption( m_strInput , m_strOutput ) )
				{
					CString strResult;
					strResult.Format( "FileEncryption::File(%s)TO(%s) Success", m_strInput, m_strOutput );
					AddEditString( strResult );
				}else{
					CString strResult;
					strResult.Format( "FileEncryption::File(%s)TO(%s) Fall", m_strInput, m_strOutput );
					AddEditString( strResult );
				}
			}
		break;
		case TEX_CRYPTION:
			{
				if ( EncryptTex( m_strInput , m_strOutput ) )
				{
					CString strResult;
					strResult.Format( "TextureEncryption::File(%s)TO(%s) Success", m_strInput, m_strOutput );
					AddEditString( strResult );
				}else{
					CString strResult;
					strResult.Format( "TextureEncryption::File(%s)TO(%s) Fall", m_strInput, m_strOutput );
					AddEditString( strResult );
				}
			}
		break;
		default:
			MessageBox(_T("Select Cryption Type"),_T("Tip"),MB_OK);
		break;
	}
	return TRUE;
}

BOOL CTabCRY::FileDecryption()
{
	int Select = m_ComboType.GetCurSel();
	switch(Select)
	{
		case RCC_CRYPTION:
			{
				if ( Decryption( m_strInput , m_strOutput ) )
				{
					CString strResult;
					strResult.Format( "FileDecryption::File(%s)TO(%s) Success", m_strInput, m_strOutput );
					AddEditString( strResult );
				}else{
					CString strResult;
					strResult.Format( "FileDecryption::File(%s)TO(%s) Failure", m_strInput, m_strOutput );
					AddEditString( strResult );
				}
			}
		break;
		case TEX_CRYPTION:
			{
				if ( DecryptTex( m_strInput , m_strOutput ) )
				{
					CString strResult;
					strResult.Format( "TextureDecryption::File(%s)TO(%s) Success", m_strInput, m_strOutput );
					AddEditString( strResult );
				}else{
					CString strResult;
					strResult.Format( "TextureDecryption::File(%s)TO(%s) Failure", m_strInput, m_strOutput );
					AddEditString( strResult );
				}
			}
		break;
		default:
			MessageBox(_T("Select Cryption Type"),_T("Tip"),MB_OK);
		break;
	}
	return TRUE;
}

BOOL CTabCRY::FolderEncryption( const CString& strInput, const CString& strOutput )
{
	CString strFind = strInput;
	strFind += "\\*";

	CString strOutFile, strOutPath;
	strOutPath = strOutput;
	strOutPath += "\\";

	CString strInFile, strInPath;
	strInPath = strInput;
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

		int nType = m_ComboType.GetCurSel();
		switch ( nType )
		{
			case RCC_CRYPTION:
			{
				strOutFile += strFile;

				if ( !Encryption( strInFile, strOutFile ) )
				{
					CString strResult;
					strResult.Format( "FileEncryption::File(%s)TO(%s) Failure", strInFile, strOutFile );
					AddEditString( strResult );
					continue;
				}
				CString strResult;
				strResult.Format( "FileEncryption::File(%s)TO(%s) Success", strInFile, strOutFile );
				AddEditString( strResult );
				nCntSuccess++;

			}break;
			case TEX_CRYPTION:
			{
				strOutFile += strFile.Left( strFile.ReverseFind('.'));
				strOutFile += ".mtf";

				if ( !EncryptTex( strInFile, strOutFile ) )
				{
					CString strResult;
					strResult.Format( "TextureEncryption::File(%s)TO(%s) Failure", strInFile, strOutFile );
					AddEditString( strResult );
					continue;
				}
				CString strResult;
				strResult.Format( "TextureEncryption::File(%s)TO(%s) Success", strInFile, strOutFile );
				AddEditString( strResult );
				nCntSuccess++;

			}break;
			default:
			{
				MessageBox(_T("Select Cryption Type"),_T("Tip"),MB_OK);
			}break;
		}

	}
	CString sReport;
	sReport.Format( "Success File : %d File All : %d",nCntSuccess ,nCntFile );
	AddEditString( sReport );
	return TRUE;
}

BOOL CTabCRY::FolderDecryption( const CString& strInput, const CString& strOutput )
{
	CString strFind = strInput;
	strFind += "\\*";

	CString strOutFile, strOutPath;
	strOutPath = strOutput;
	strOutPath += "\\";

	CString strInFile, strInPath;
	strInPath = strInput;
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

		int nType = m_ComboType.GetCurSel();
		switch ( nType )
		{
			case RCC_CRYPTION:
			{
				strOutFile += strFile;

				if ( !Decryption( strInFile, strOutFile ) )
				{
					CString strResult;
					strResult.Format( "FileDecryption::File(%s)TO(%s) Failure", strInFile, strOutFile );
					AddEditString( strResult );
					continue;
				}
				CString strResult;
				strResult.Format( "FileDecryption::File(%s)TO(%s) Success", strInFile, strOutFile );
				AddEditString( strResult );
				nCntSuccess++;

			}break;
			case TEX_CRYPTION:
			{
				strOutFile += strFile;

				if ( !DecryptTex( strInFile, strOutFile ) )
				{
					CString strResult;
					strResult.Format( "TextureDecryption::File(%s)TO(%s) Failure", strInFile, strOutFile );
					AddEditString( strResult );
					continue;
				}
				CString strResult;
				strResult.Format( "TextureDecryption::File(%s)TO(%s) Success", strInFile, strOutFile );
				AddEditString( strResult );
				nCntSuccess++;
			}break;
			default:
			{
				MessageBox(_T("Select Cryption Type"),_T("Tip"),MB_OK);
			}break;
		}

		
	}
	CString sReport;
	sReport.Format( "Success File : %d File All : %d",nCntSuccess ,nCntFile );
	AddEditString( sReport );
	return TRUE;
}

BOOL CTabCRY::Encryption(CString fInput , CString fOutput)
{
	FILE * pFileInput = fopen( fInput , "rb" );
	if ( !pFileInput ) return FALSE;
	fseek ( pFileInput, 0, SEEK_END );
	int nSize = ftell ( pFileInput );
	fseek ( pFileInput, 0, SEEK_SET );	
	BYTE* pBuffer = new BYTE[nSize];
	fread( pBuffer, sizeof(BYTE), nSize, pFileInput );
	fclose(pFileInput);
	char * cInput = (char *)(LPCTSTR)fInput;
	char * cOutput = (char *)(LPCTSTR)fOutput;

	CCrypt::Encryption( pBuffer, nSize );
	
	{
		FILE * pFileOutput = fopen( fOutput , "wb" );
		if ( !pFileOutput ) return FALSE;
		fwrite( pBuffer , sizeof(BYTE), nSize , pFileOutput );
		fclose(pFileOutput);
	}
	return TRUE;
}
BOOL CTabCRY::Decryption( CString fInput , CString fOutput )
{
	FILE * pFileInput = fopen( fInput , "rb" );
	if ( !pFileInput ) return FALSE;
	fseek ( pFileInput, 0, SEEK_END );
	int nSize = ftell ( pFileInput );
	fseek ( pFileInput, 0, SEEK_SET );	
	BYTE* pBuffer = new BYTE[nSize];
	fread( pBuffer, sizeof(BYTE), nSize, pFileInput );
	fclose(pFileInput);
	char * cInput = (char *)(LPCTSTR)fInput;
	char * cOutput = (char *)(LPCTSTR)fOutput;

	CCrypt::Decryption( pBuffer, nSize );
	
	{
		FILE * pFileOutput = fopen( fOutput , "wb" );
		if ( !pFileOutput ) return FALSE;
		fwrite( pBuffer , sizeof(BYTE), nSize , pFileOutput );
		fclose(pFileOutput);
	}
	return TRUE;
}


void CTabCRY::AddEditString( const char* szInfo )
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

BOOL CTabCRY::EncryptTex( const CString& strInput, const CString& strOutput )
{
	char g_szFileExt[CCrypt::TEXTURE_TYPE][MAX_PATH] = { ".dds",".tga" };

	FILE* pFileInput = NULL;
	pFileInput = fopen( strInput, "rb" );
	if ( !pFileInput )
	{
		return FALSE;
	}

	fseek ( pFileInput, 0, SEEK_END );
	int nSize = ftell ( pFileInput );

	fseek ( pFileInput, 0, SEEK_SET );	
	
	BYTE* pBuffer = new BYTE[CCrypt::TEX_HEADER_SIZE+nSize];

	int nVersion = CCrypt::TEX_VERSION;
	int nFileType = CCrypt::TEXTURE_DDS;

	CString strFileExt = strInput;

	strFileExt = strFileExt.Right( strFileExt.GetLength() - strFileExt.ReverseFind( '.' ) );
	strFileExt.MakeLower();

	if ( !strcmp( strFileExt, g_szFileExt[CCrypt::TEXTURE_DDS] ) )	nFileType = CCrypt::TEXTURE_DDS;
	else if ( !strcmp( strFileExt, g_szFileExt[CCrypt::TEXTURE_TGA] ) ) nFileType = CCrypt::TEXTURE_TGA;
	
	memcpy( pBuffer, &nVersion, sizeof( int ) );
	memcpy( pBuffer+4 , &nSize, sizeof(int) );
	memcpy( pBuffer+8, &nFileType, sizeof(int) );	
	
	fread( pBuffer+CCrypt::TEX_HEADER_SIZE, sizeof(BYTE), nSize, pFileInput );
	fclose( pFileInput );

	for ( int i = 0; i < nSize; ++i )
	{
		pBuffer[CCrypt::TEX_HEADER_SIZE+i] = pBuffer[CCrypt::TEX_HEADER_SIZE+i] ^ CCrypt::TEX_XOR_DATA;
		pBuffer[CCrypt::TEX_HEADER_SIZE+i] -= CCrypt::TEX_DIFF_DATA;
	}


	CString strOutFile = strOutput;
	strOutFile = strOutFile.Left( strOutFile.ReverseFind( '.' ) );
	strOutFile += ".mtf";

	FILE* pFileOutput = NULL;
	pFileOutput = fopen( strOutFile, "wb" );
	if ( !pFileOutput )
	{
		delete[] pBuffer;
		return FALSE;
	}
	
	fwrite( pBuffer, sizeof(BYTE), nSize+CCrypt::TEX_HEADER_SIZE, pFileOutput );
	fclose( pFileOutput );

	delete[] pBuffer;
	return TRUE;
}

BOOL CTabCRY::DecryptTex( const CString& strInput, const CString& strOutput )
{
	char g_szFileExt[CCrypt::TEXTURE_TYPE][MAX_PATH] = { ".dds",".tga" };

	FILE* pFileInput = NULL;
	pFileInput = fopen( strInput, "rb" );
	if ( !pFileInput )
	{
		return FALSE;
	}
	
	fseek ( pFileInput, 0, SEEK_END );
	int nSize = ftell ( pFileInput );

	fseek ( pFileInput, 0, SEEK_SET );	
	
	int nVersion = 0;
	int nReadSize = 0;
	int nFileType = 0;
	
	fread( &nVersion, sizeof(int), 1, pFileInput );
    fread( &nReadSize, sizeof(int), 1, pFileInput );
	fread( &nFileType, sizeof(int), 1, pFileInput );

	if ( nVersion != CCrypt::TEX_VERSION || nSize != nReadSize + CCrypt::TEX_HEADER_SIZE )
	{
		return FALSE;
	}	
	
	BYTE* pBuffer = new BYTE[nReadSize];

	fread( pBuffer, sizeof(BYTE), nReadSize, pFileInput );
	fclose( pFileInput );	

	for ( int i = 0; i < nReadSize; ++i )
	{
		pBuffer[i] += CCrypt::TEX_DIFF_DATA;
		pBuffer[i] = pBuffer[i] ^ CCrypt::TEX_XOR_DATA;		
	}

	CString strOutFile = strOutput;
	strOutFile = strOutFile.Left( strOutFile.ReverseFind( '.' ) );
	strOutFile += g_szFileExt[nFileType];

	FILE* pFileOutput = NULL;
	pFileOutput = fopen( strOutFile, "wb" );
	if ( !pFileOutput )
	{
		delete[] pBuffer;
		return FALSE;
	}
	
	fwrite( pBuffer, sizeof(BYTE), nReadSize, pFileOutput );
	fclose( pFileOutput );

	delete[] pBuffer;
	return TRUE;
}