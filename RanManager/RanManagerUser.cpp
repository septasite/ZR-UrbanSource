// RanViewDlg.cpp : implementation file
//
#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerDlg.h"
#include "RanManagerTab.h"
#include "RanManagerUser.h"
#include "RanManagerChar.h"
#include "RanManagerUserTab.h"
#include "EtcFunction.h"
#include "RanManagerComments.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "s_NetGlobal.h"
#include ".\ranmanageruser.h"


// CRanManagerUser dialog
IMPLEMENT_DYNAMIC(CRanManagerUser, CPropertyPage)
CRanManagerUser::CRanManagerUser(LOGFONT logfont)
	: CPropertyPage(CRanManagerUser::IDD)
	,m_pFont( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	nUserNum = 0;
	strUser = "";
}

CRanManagerUser::~CRanManagerUser()
{
}

void CRanManagerUser::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USER, m_list_User );
	DDX_Control(pDX, IDC_COMBO_SEARCHTYPE, m_cSearchType );
	DDX_Control(pDX, IDC_COMBO_USERTYPE, m_cUserPage );
}

BEGIN_MESSAGE_MAP(CRanManagerUser, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCHTYPE, OnCbnSelchangeComboSearchtype)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_USER, OnNMDblclkListUser)
	ON_BN_CLICKED(IDC_BUTTON_USER_SELECT, OnBnClickedButtonUserSelect)
END_MESSAGE_MAP()

// CRanManagerUser message handlers
BOOL CRanManagerUser::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	CRect SheetRect;
	CWnd *pWnd;
	pWnd = GetDlgItem ( IDC_STATIC_USER );
	pWnd->GetWindowRect ( SheetRect );
	ScreenToClient ( &SheetRect );
	LOGFONT logfont = {0};
	CFont* pFont = GetFont();
	if ( pFont ) pFont->GetLogFont( &logfont );
	m_pUserTab = new CRanManagerUserTab ( SheetRect, logfont, this );
	m_pUserTab->Create( this, WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0 );
	m_pUserTab->ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	m_pUserTab->SetActivePage ( USERPAGE_MAIN );

	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	m_list_User.SetExtendedStyle ( m_list_User.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_list_User.GetClientRect ( &rectCtrl );
	lnWidth = rectCtrl.right - rectCtrl.left;

	const int nColumnCount = 6;	
	char* szColumnName1[nColumnCount] = { "Num","UserNum", "UserName" , "UserType", "UserOnline", ""};
	int nColumnWidthPercent[nColumnCount] = { 15, 15,30,15,15,10 };

	for ( int i = 0; i < nColumnCount; i++ )
	{		
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.pszText = szColumnName1[i];
		lvColumn.iSubItem = i;
		lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
		m_list_User.InsertColumn (i, &lvColumn );
	}

	for ( int i = 0; i < SEARCH_SIZE; ++i )
	{
		m_cSearchType.InsertString( i, RMComments::m_SearchType[i].c_str() );
	}
	m_cSearchType.SetCurSel( 0 );

	for ( int i = 0; i < USERPAGE_SIZE; ++i )
	{
		m_cUserPage.InsertString( i, RMComments::m_PageUser[i].c_str() );
	}
	m_cUserPage.SetCurSel( 0 );

	SetWin_ShowWindow( this ,IDC_COMBO_USERTYPE  , FALSE );
	SetWin_ShowWindow( this ,IDC_BUTTON_USER_SELECT  , FALSE );
	SetWin_ShowWindow( this ,IDC_EDIT_USERTYPE  , FALSE );
	OnCbnSelchangeComboSearchtype();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CRanManagerUser::OnCbnSelchangeComboSearchtype()
{
	int nType = m_cSearchType.GetCurSel();
	switch (nType)
	{
	case SEARCH_NUM:
	case SEARCH_ID:
		{
			SetWin_Enable( this ,IDC_EDIT_SEARCH  , TRUE );
		}break;
	default:SetWin_Enable( this ,IDC_EDIT_SEARCH  , FALSE );
	};
}

void CRanManagerUser::OnBnClickedButtonSearch()
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectUser(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	int nType = m_cSearchType.GetCurSel();
	TCHAR szTemp[256] = {0};
	std::string strSign = "%";
	switch (nType)
	{
	case SEARCH_ALL :
		{
			_snprintf( szTemp, 256, "SELECT UserNum,UserID,UserType,UserLoginState FROM %s.dbo.UserInfo WITH (NOLOCK) "
			"ORDER BY UserNum",CToolCfg::GetInstance()->szUserDb);
		}break;
	case SEARCH_NUM :
		{
			int nUserNumFind = GetWin_Num_int ( this, IDC_EDIT_SEARCH ); 
			_snprintf( szTemp, 256, "SELECT UserNum,UserID,UserType,UserLoginState FROM %s.dbo.UserInfo WITH (NOLOCK) WHERE UserNum LIKE '%s%d%s' "
			"ORDER BY UserNum",CToolCfg::GetInstance()->szUserDb,strSign.c_str(),nUserNumFind,strSign.c_str() );
		}break;
	case SEARCH_ID :
		{
			std::string strUserSearch  = GetWin_Text ( this, IDC_EDIT_SEARCH ); 
			_snprintf( szTemp, 256, "SELECT UserNum,UserID,UserType,UserLoginState FROM %s.dbo.UserInfo WITH (NOLOCK) WHERE UserID LIKE '%s%s%s' "
			"ORDER BY UserNum",CToolCfg::GetInstance()->szUserDb,strSign.c_str(),strUserSearch.c_str(),strSign.c_str() );
		}break;
	case SEARCH_GM :
		{
			_snprintf( szTemp, 256, "SELECT UserNum,UserID,UserType,UserLoginState FROM %s.dbo.UserInfo WITH (NOLOCK) WHERE UserType >10 "
			"ORDER BY UserNum",CToolCfg::GetInstance()->szUserDb  );
		}break;
	case SEARCH_STAFF :
		{
			_snprintf( szTemp, 256, "SELECT UserNum,UserID,UserType,UserLoginState FROM %s.dbo.UserInfo WITH (NOLOCK) WHERE UserType =10 "
			"ORDER BY UserNum",CToolCfg::GetInstance()->szUserDb  );
		}break;
	case SEARCH_ONLINE :
		{
			_snprintf( szTemp, 256, "SELECT UserNum,UserID,UserType,UserLoginState FROM %s.dbo.UserInfo WITH (NOLOCK) WHERE UserLoginState = 1 "
			"ORDER BY UserNum",CToolCfg::GetInstance()->szUserDb  );
		}break;
	};
	

	sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("User.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nUserNum = 0, cbUserNum = SQL_NTS; 
	SQLCHAR    szCharId[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbUserId = SQL_NTS;
	SQLINTEGER nUserType = 0, cbUserType = SQL_NTS; 
	SQLINTEGER nUserOnline = 0, cbUserOnline = SQL_NTS; 

	int nNum = 0;
	char szTempChar[256];
	m_list_User.DeleteAllItems();
	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nUserNum, 0, &cbUserNum );	
			::SQLGetData(hStmt, 2, SQL_C_CHAR, szCharId, CHR_ID_LENGTH, &cbUserId);
			::SQLGetData(hStmt, 3, SQL_C_LONG, &nUserType, 0, &cbUserType);	
			::SQLGetData(hStmt, 4, SQL_C_LONG, &nUserOnline, 0, &cbUserOnline);	
			
			sprintf( szTempChar, "%d", nNum );
			m_list_User.InsertItem( nNum, szTempChar );

			sprintf( szTempChar, "%d", nUserNum );
			m_list_User.SetItemText(nNum,1,szTempChar);

			sprintf( szTempChar, "%s", szCharId );
			m_list_User.SetItemText(nNum,2,szTempChar);
			
			CString strTemp;
			if (nUserType < 10 )	strTemp.Format("Normal",nUserType);
			else if (nUserType == 10 )	strTemp.Format("Premium",nUserType);
			else if (nUserType > 10 )	strTemp.Format("Game Master",nUserType);
			m_list_User.SetItemText(nNum,3,strTemp.GetString());

			if (nUserOnline == 0)strTemp.Format("Offline",nUserOnline);
			else if (nUserOnline > 0)strTemp.Format("Online",nUserOnline);
			m_list_User.SetItemText(nNum,4,strTemp.GetString());

			nNum++;	}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerUser::OnNMDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	int nSelect = m_list_User.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;
	nUserNum = atoi ( m_list_User.GetItemText(nSelect,1).GetString() );
	strUser = m_list_User.GetItemText(nSelect,2).GetString();

	SetWin_ShowWindow( this ,IDC_COMBO_USERTYPE  , TRUE );
	SetWin_ShowWindow( this ,IDC_BUTTON_USER_SELECT  , TRUE );
	SetWin_ShowWindow( this ,IDC_EDIT_USERTYPE  , TRUE );

	SetWin_Num_int ( this, IDC_EDIT_SELECTED_NUM,nUserNum );
	SetWin_Text ( this, IDC_EDIT_SELECTED_NAME, strUser.GetString() );

	m_pUserTab->ActivePage(USERPAGE_EDIT,nUserNum);
	m_cUserPage.SetCurSel(USERPAGE_EDIT);
	SetWin_Text(this,IDC_EDIT_USERTYPE,RMComments::m_PageUser[USERPAGE_MAIN].c_str() );
}

void CRanManagerUser::OnBnClickedButtonUserSelect()
{
	int nSelect = m_cUserPage.GetCurSel();

	SetWin_Text(this,IDC_EDIT_USERTYPE,RMComments::m_PageUser[nSelect].c_str() );

	switch (nSelect)
	{
	case USERPAGE_MAIN:	m_pUserTab->ActivePage ( USERPAGE_MAIN ,nUserNum );	break;
	case USERPAGE_NEW:	m_pUserTab->ActivePage ( USERPAGE_NEW ,nUserNum );	break;
	case USERPAGE_EDIT:	m_pUserTab->ActivePage ( USERPAGE_EDIT ,nUserNum );	break;
	case USERPAGE_BANK:	m_pUserTab->ActivePage ( USERPAGE_BANK ,nUserNum );	break;
	case USERPAGE_CHAR:	m_pUserTab->ActivePage ( USERPAGE_CHAR ,nUserNum );	break;
	case USERPAGE_LOCKER:	m_pUserTab->ActivePage ( USERPAGE_LOCKER ,nUserNum );	break;
	};
}
