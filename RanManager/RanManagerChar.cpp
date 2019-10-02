// RanManagerChar.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerChar.h"
#include "RanManagerDlg.h"
#include "RanManagerTab.h"
#include "EtcFunction.h"
#include "RanManagerComments.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "s_NetGlobal.h"
#include "RanManagerCharTab.h"
#include ".\ranmanagerchar.h"


// CRanManagerChar dialog

IMPLEMENT_DYNAMIC(CRanManagerChar, CPropertyPage)
CRanManagerChar::CRanManagerChar(LOGFONT logfont)
	: CPropertyPage(CRanManagerChar::IDD)
	,m_pFont( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	nChaNum = 0;
	strChar = "";
}

CRanManagerChar::~CRanManagerChar()
{
}

void CRanManagerChar::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHAR, m_list_Char );
	DDX_Control(pDX, IDC_COMBO_CHARSEARCHTYPE, m_cSearchType );
	DDX_Control(pDX, IDC_COMBO_CHARTYPE, m_cCharPage );
}


BEGIN_MESSAGE_MAP(CRanManagerChar, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_CHARSEARCHTYPE, OnCbnSelchangeComboCharsearchtype)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CHAR, OnNMDblclkListChar)
	ON_BN_CLICKED(IDC_BUTTON_CHAR_SELECT, OnBnClickedButtonCharSelect)
END_MESSAGE_MAP()


// CRanManagerChar message handlers
BOOL CRanManagerChar::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	CRect SheetRect;
	CWnd *pWnd;
	pWnd = GetDlgItem ( IDC_STATIC_CHAR );
	pWnd->GetWindowRect ( SheetRect );
	ScreenToClient ( &SheetRect );
	LOGFONT logfont = {0};
	CFont* pFont = GetFont();
	if ( pFont ) pFont->GetLogFont( &logfont );
	m_pCharTab = new CRanManagerCharTab ( SheetRect, logfont, this );
	m_pCharTab->Create( this, WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0 );
	m_pCharTab->ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	m_pCharTab->SetActivePage ( CHARPAGE_MAIN );

	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	m_list_Char.SetExtendedStyle ( m_list_Char.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_list_Char.GetClientRect ( &rectCtrl );
	lnWidth = rectCtrl.right - rectCtrl.left;

	const int nColumnCount = 7;	
	char* szColumnName1[nColumnCount] = { "Num","ChaNum", "UserNum" , "ChaName", "Online", "Deleted"};
	int nColumnWidthPercent[nColumnCount] = { 14,14,14,27,14,17 };

	for ( int i = 0; i < nColumnCount; i++ )
	{		
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.pszText = szColumnName1[i];
		lvColumn.iSubItem = i;
		lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
		m_list_Char.InsertColumn (i, &lvColumn );
	}

	for ( int i = 0; i < SEARCH_CHASIZE; ++i )
	{
		m_cSearchType.InsertString( i, RMComments::m_SearchChaType[i].c_str() );
	}
	m_cSearchType.SetCurSel( 0 );

	OnCbnSelchangeComboCharsearchtype();

	for ( int i = 0; i < CHARPAGE_SIZE; ++i )
	{
		m_cCharPage.InsertString( i, RMComments::m_PageChar[i].c_str() );
	}
	m_cCharPage.SetCurSel( 0 );

	SetWin_ShowWindow( this ,IDC_COMBO_CHARTYPE, FALSE );
	SetWin_ShowWindow( this ,IDC_BUTTON_CHAR_SELECT, FALSE );
	SetWin_ShowWindow( this ,IDC_EDIT_CHARTYPE, FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CRanManagerChar::OnBnClickedButtonSearch()
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	int nType = m_cSearchType.GetCurSel();
	TCHAR szTemp[256] = {0};
	std::string strSign = "%";
	switch (nType)
	{
	case SEARCH_CHAALL :
		{
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb);
		}break;
	case SEARCH_CHANUM :
		{
			int nFind =  GetWin_Num_int(this,IDC_EDIT_SEARCH);
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaNum LIKE '%s%d%s' "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),nFind,strSign.c_str() );
		}break;
	case SEARCH_CHAUSERNUM :
		{
			int nFind =  GetWin_Num_int(this,IDC_EDIT_SEARCH);
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE UserNum LIKE '%s%d%s' "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),nFind,strSign.c_str() );
		}break;
	case SEARCH_CHANAME :
		{
			std::string strUserSearch  = GetWin_Text ( this, IDC_EDIT_SEARCH ); 
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaName LIKE '%s%s%s' "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),strUserSearch.c_str(),strSign.c_str() );
		}break;
	case SEARCH_CHAONLINE :
		{
			int nFind =  GetWin_Num_int(this,IDC_EDIT_SEARCH);
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaOnline > 0 "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nFind );
		}break;
	case SEARCH_CHADELETED :
		{
			int nFind =  GetWin_Num_int(this,IDC_EDIT_SEARCH);
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaDeleted >= 1 "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nFind );
		}break;
	};
	

	sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("Char.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nChaNum = 0, cbChaNum = SQL_NTS; 
	SQLINTEGER nUserNum = 0, cbUserNum = SQL_NTS; 
	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbCharId = SQL_NTS;
	SQLINTEGER nCharOnline = 0, cbCharOnline = SQL_NTS; 
	SQLINTEGER nChaDeleted = 0, cbChaDeleted = SQL_NTS; 

	int nNum = 0;
	char szTempChar[256];
	m_list_Char.DeleteAllItems();
	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nChaNum, 0, &cbChaNum );	
			::SQLGetData(hStmt, 2, SQL_C_LONG, &nUserNum, 0, &cbUserNum );	
			::SQLGetData(hStmt, 3, SQL_C_CHAR, szChaName, CHR_ID_LENGTH, &cbCharId );
			::SQLGetData(hStmt, 4, SQL_C_LONG, &nCharOnline, 0, &cbCharOnline );	
			::SQLGetData(hStmt, 5, SQL_C_LONG, &nChaDeleted, 0, &cbChaDeleted );	
			
			sprintf( szTempChar, "%d", nNum );
			m_list_Char.InsertItem( nNum, szTempChar );

			sprintf( szTempChar, "%d", nChaNum );
			m_list_Char.SetItemText(nNum,1,szTempChar);

			sprintf( szTempChar, "%d", nUserNum );
			m_list_Char.SetItemText(nNum,2,szTempChar);

			sprintf( szTempChar, "%s", szChaName );
			m_list_Char.SetItemText(nNum,3,szTempChar);
			
			CString strTemp;
			if (nCharOnline >0 )	strTemp.Format("Online",nCharOnline);
			else strTemp.Format("Offline",nCharOnline);
			m_list_Char.SetItemText(nNum,4,strTemp.GetString());

			if (nChaDeleted >0 )	strTemp.Format("Deleted(%d)",nChaDeleted);
			else strTemp.Format("Active(%d)",nChaDeleted);
			m_list_Char.SetItemText(nNum,5,strTemp.GetString());

			nNum++;	}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerChar::OnCbnSelchangeComboCharsearchtype()
{
	int nSelect = m_cSearchType.GetCurSel();
	if (nSelect == SEARCH_CHAALL || nSelect == SEARCH_CHAONLINE || nSelect == SEARCH_CHADELETED ) SetWin_Enable(this,IDC_EDIT_SEARCH,false);
	else	 SetWin_Enable(this,IDC_EDIT_SEARCH,true);
}

void CRanManagerChar::OnNMDblclkListChar(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nSelect = m_list_Char.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;
	nChaNum = atoi ( m_list_Char.GetItemText(nSelect,1).GetString() );
	strChar = m_list_Char.GetItemText(nSelect,3).GetString();

	BOOL bOnline = CheckOnline(nChaNum);
	if (bOnline)
	{
		MessageBox("Warning Character is Online! Character May Not Save!","Warning",MB_OK);
	}
	SetWin_ShowWindow( this ,IDC_COMBO_CHARTYPE, TRUE );
	SetWin_ShowWindow( this ,IDC_BUTTON_CHAR_SELECT, TRUE );
	SetWin_ShowWindow( this ,IDC_EDIT_CHARTYPE, TRUE );

	SetWin_Num_int ( this, IDC_EDIT_SELECTED_NUM,nChaNum );
	SetWin_Text ( this, IDC_EDIT_SELECTED_NAME, strChar.GetString() );

	m_pCharTab->ActivePage(CHARPAGE_EDIT,nChaNum);
	m_cCharPage.SetCurSel(CHARPAGE_EDIT);
	SetWin_Text(this,IDC_EDIT_CHARTYPE,RMComments::m_PageChar[CHARPAGE_EDIT].c_str() );
}

void CRanManagerChar::OnBnClickedButtonCharSelect()
{
	int nSelect = m_cCharPage.GetCurSel();

	SetWin_Text(this,IDC_EDIT_CHARTYPE,RMComments::m_PageChar[nSelect].c_str() );

	switch (nSelect)
	{
	case CHARPAGE_MAIN:	m_pCharTab->ActivePage ( CHARPAGE_MAIN ,nChaNum );	break;
	case CHARPAGE_EDIT:	m_pCharTab->ActivePage ( CHARPAGE_EDIT ,nChaNum );	break;
	case CHARPAGE_PUTON:	m_pCharTab->ActivePage ( CHARPAGE_PUTON ,nChaNum );	break;
	case CHARPAGE_INVEN:	m_pCharTab->ActivePage ( CHARPAGE_INVEN ,nChaNum );	break;
	case CHARPAGE_SKILL:	m_pCharTab->ActivePage ( CHARPAGE_SKILL ,nChaNum );	break;
	case CHARPAGE_QUEST:	m_pCharTab->ActivePage ( CHARPAGE_QUEST ,nChaNum );	break;
	case CHARPAGE_VEHICLE:	m_pCharTab->ActivePage ( CHARPAGE_VEHICLE ,nChaNum );	break;
	case CHARPAGE_PET:	m_pCharTab->ActivePage ( CHARPAGE_PET ,nChaNum );	break;
	case CHARPAGE_SKILLSLOT:	m_pCharTab->ActivePage ( CHARPAGE_SKILLSLOT ,nChaNum );	break;
	case CHARPAGE_QUICKSLOT:	m_pCharTab->ActivePage ( CHARPAGE_QUICKSLOT ,nChaNum );	break;
	case CHARPAGE_COOLDOWN:	m_pCharTab->ActivePage ( CHARPAGE_COOLDOWN ,nChaNum );	break;
	};
}

BOOL CRanManagerChar::CheckOnline(int nCheck)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return FALSE;
	}

	int nType = m_cSearchType.GetCurSel();
	TCHAR szTemp[256] = {0};

	_snprintf( szTemp, 256, "SELECT ChaNum,ChaOnline FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaNum =%d "
	"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nCheck );

	sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("Char.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return FALSE;
	}

	SQLINTEGER nChaNum = 0, cbChaNum = SQL_NTS; 
	SQLINTEGER nChaOnline = 0, cbChaOnline = SQL_NTS; 

	int nNum = 0;
	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nChaNum, 0, &cbChaNum );
			::SQLGetData(hStmt, 2, SQL_C_LONG, &nChaOnline, 0, &cbChaOnline );

			if (nChaOnline == 1 ) return TRUE;
			nNum++;	}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	

	return FALSE;
}
