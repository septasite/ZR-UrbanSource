// CharSearch.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "CharSearch.h"
#include ".\charsearch.h"

#include "EtcFunction.h"
#include "RanManagerComments.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "s_NetGlobal.h"

// CCharSearch dialog

IMPLEMENT_DYNAMIC(CCharSearch, CDialog)
CCharSearch::CCharSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CCharSearch::IDD, pParent)
{
	nSelectedChar = 0;
	bMultiple = false;
}

CCharSearch::~CCharSearch()
{
}

void CCharSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHAR, m_list_Char );
	DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE, m_cSearchType );
}


BEGIN_MESSAGE_MAP(CCharSearch, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_GUILDSEARCH, OnBnClickedButtonGuildsearch)
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCH_TYPE, OnCbnSelchangeComboSearchType)
END_MESSAGE_MAP()


// CCharSearch message handlers
BOOL CCharSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	if (bMultiple)	m_list_Char.SetExtendedStyle ( m_list_Char.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	else	m_list_Char.SetExtendedStyle ( m_list_Char.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	m_list_Char.GetClientRect ( &rectCtrl );
	lnWidth = rectCtrl.right - rectCtrl.left;

	const int nColumnCount = 9;	
	char* szColumnName1[nColumnCount] = { "Num","ChaNum","UserNum","ChaName","GuildNum","Guild","GuildPos","Online","Deleted"};
	int nColumnWidthPercent[nColumnCount] = { 8,8,8,18,8,18,14,9,9 };

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
	OnCbnSelchangeComboSearchType();
	ReadAllChar();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CCharSearch::ReadAllChar()
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	TCHAR szTemp[256] = {0};
	_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuNum,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) "
	"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb);

	sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharSearch.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nChaNum = 0, cbChaNum = SQL_NTS; 
	SQLINTEGER nUserNum = 0, cbUserNum = SQL_NTS; 
	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbCharId = SQL_NTS;
	SQLINTEGER nGuNum = 0, cbGuNum = SQL_NTS; 
	SQLINTEGER nGuPosition = 0, cbGuPosition = SQL_NTS; 
	SQLINTEGER nChaOnline = 0, cbChaOnline = SQL_NTS; 
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
			::SQLGetData(hStmt, 4, SQL_C_LONG, &nGuNum , 0, &cbGuNum  );
			::SQLGetData(hStmt, 5, SQL_C_LONG, &nGuPosition, 0, &cbGuPosition );
			::SQLGetData(hStmt, 6, SQL_C_LONG, &nChaOnline, 0, &cbChaOnline );	
			::SQLGetData(hStmt, 7, SQL_C_LONG, &nChaDeleted, 0, &cbChaDeleted );	
			
			sprintf( szTempChar, "%d", nNum );
			m_list_Char.InsertItem( nNum, szTempChar );

			sprintf( szTempChar, "%d", nChaNum );
			m_list_Char.SetItemText(nNum,1,szTempChar);

			sprintf( szTempChar, "%d", nUserNum );
			m_list_Char.SetItemText(nNum,2,szTempChar);

			sprintf( szTempChar, "%s", szChaName );
			m_list_Char.SetItemText(nNum,3,szTempChar);

			sprintf( szTempChar, "%d", nGuNum );
			m_list_Char.SetItemText(nNum,4,szTempChar);

			//5 is pending

			sprintf( szTempChar, "%d", nGuPosition );
			m_list_Char.SetItemText(nNum,6,szTempChar);
			
			CString strTemp;
			if (nChaOnline >0 )	strTemp.Format("Online",nChaOnline);
			else strTemp.Format("Offline",nChaOnline);
			m_list_Char.SetItemText(nNum,7,strTemp.GetString());

			if (nChaDeleted >0 )	strTemp.Format("Deleted",nChaDeleted);
			else strTemp.Format("Active",nChaDeleted);
			m_list_Char.SetItemText(nNum,8,strTemp.GetString());

			nNum++;	}
		else	break;
		Sleep( 0 );
	}
	ReadGuilds();
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CCharSearch::ReadGuilds()
{
	int nItem = 0; 
	for(nItem =0 ; nItem < m_list_Char.GetItemCount(); nItem++)
	{
		SQLRETURN	sReturn = 0; // SQL return value (short)	
		SQLHSTMT	hStmt; // Handle of statement (void*)

		int nGuNum =  atoi ( m_list_Char.GetItemText(nItem, 4).GetString() );

		sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
		if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	continue;

		TCHAR szTemp[1024] = {0};
		_snprintf( szTemp, 1024, "SELECT GuName "
							"FROM %s.dbo.GuildInfo WHERE GuNum=%d",CToolCfg::GetInstance()->szGameDb,nGuNum );

		sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("CharSearch.txt","%s--%s",strTIME.c_str(),szTemp);

		if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
		{
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return;
		}

		SQLCHAR    szGuName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbGuName = SQL_NTS; 
	
		char szTempChar[256];
		while (true)
		{
			sReturn = ::SQLFetch(hStmt);
			if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
			if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
			{		
				::SQLGetData(hStmt, 1, SQL_C_CHAR, szGuName   ,  CHR_ID_LENGTH+1, &cbGuName); 
				sprintf( szTempChar, "%s",(const char*) szGuName );
				m_list_Char.SetItemText(nItem,5,szTempChar);
				break;
			}
			else	break;
			Sleep( 0 );
		}
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}		
}

void CCharSearch::OnBnClickedButtonOk()
{
	if (bMultiple)	
	{
		m_VecSearchResult.clear();
		int nItem = 0; 
		for(nItem =0 ; nItem <  m_list_Char.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_Char.GetCheck(nItem);
			if( bChecked)
			{
				int nSelect = atoi ( m_list_Char.GetItemText(nItem,1).GetString() );
				m_VecSearchResult.push_back(nSelect);
			}
		}
	}
	else	
	{
		int nSelect = m_list_Char.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if( nSelect == -1 ) return;
		nSelectedChar =  atoi ( m_list_Char.GetItemText(nSelect,1).GetString() );
	}
	OnOK();
}

void CCharSearch::OnBnClickedButtonCancel()
{
	OnCancel();
}

void CCharSearch::OnBnClickedButtonGuildsearch()
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
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuNum,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb);
		}break;
	case SEARCH_CHANUM :
		{
			int nFind =  GetWin_Num_int(this,IDC_EDIT_SEARCH);
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuNum,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaNum LIKE '%s%d%s' "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),nFind,strSign.c_str() );
		}break;
	case SEARCH_CHAUSERNUM :
		{
			int nFind =  GetWin_Num_int(this,IDC_EDIT_SEARCH);
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuNum,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE UserNum LIKE '%s%d%s' "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),nFind,strSign.c_str() );
		}break;
	case SEARCH_CHANAME :
		{
			std::string strUserSearch  = GetWin_Text ( this, IDC_EDIT_SEARCH ); 
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuNum,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaName LIKE '%s%s%s' "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),strUserSearch.c_str(),strSign.c_str() );
		}break;
	case SEARCH_CHAONLINE :
		{
			int nFind =  GetWin_Num_int(this,IDC_EDIT_SEARCH);
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuNum,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaOnline > 0 "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nFind );
		}break;
	case SEARCH_CHADELETED :
		{
			int nFind =  GetWin_Num_int(this,IDC_EDIT_SEARCH);
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuNum,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaDeleted >= 1 "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nFind );
		}break;
	};
	

	sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharSearch.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nChaNum = 0, cbChaNum = SQL_NTS; 
	SQLINTEGER nUserNum = 0, cbUserNum = SQL_NTS; 
	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbCharId = SQL_NTS;
	SQLINTEGER nGuNum = 0, cbGuNum = SQL_NTS; 
	SQLINTEGER nGuPosition = 0, cbGuPosition = SQL_NTS; 
	SQLINTEGER nChaOnline = 0, cbChaOnline = SQL_NTS; 
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
			::SQLGetData(hStmt, 4, SQL_C_LONG, &nGuNum , 0, &cbGuNum  );
			::SQLGetData(hStmt, 5, SQL_C_LONG, &nGuPosition, 0, &cbGuPosition );
			::SQLGetData(hStmt, 6, SQL_C_LONG, &nChaOnline, 0, &cbChaOnline );	
			::SQLGetData(hStmt, 7, SQL_C_LONG, &nChaDeleted, 0, &cbChaDeleted );	
			
			sprintf( szTempChar, "%d", nNum );
			m_list_Char.InsertItem( nNum, szTempChar );

			sprintf( szTempChar, "%d", nChaNum );
			m_list_Char.SetItemText(nNum,1,szTempChar);

			sprintf( szTempChar, "%d", nUserNum );
			m_list_Char.SetItemText(nNum,2,szTempChar);

			sprintf( szTempChar, "%s", szChaName );
			m_list_Char.SetItemText(nNum,3,szTempChar);

			sprintf( szTempChar, "%d", nGuNum );
			m_list_Char.SetItemText(nNum,4,szTempChar);

			//5 is pending

			sprintf( szTempChar, "%d", nGuPosition );
			m_list_Char.SetItemText(nNum,6,szTempChar);
			
			CString strTemp;
			if (nChaOnline >0 )	strTemp.Format("Online",nChaOnline);
			else strTemp.Format("Offline",nChaOnline);
			m_list_Char.SetItemText(nNum,7,strTemp.GetString());

			if (nChaDeleted >0 )	strTemp.Format("Deleted",nChaDeleted);
			else strTemp.Format("Active",nChaDeleted);
			m_list_Char.SetItemText(nNum,8,strTemp.GetString());

			nNum++;	}
		else	break;
		Sleep( 0 );
	}
	ReadGuilds();
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CCharSearch::OnCbnSelchangeComboSearchType()
{
	int nSelect = m_cSearchType.GetCurSel();
	if (nSelect == SEARCH_CHAALL || nSelect == SEARCH_CHAONLINE || nSelect == SEARCH_CHADELETED ) SetWin_Enable(this,IDC_EDIT_SEARCH,false);
	else	 SetWin_Enable(this,IDC_EDIT_SEARCH,true);
}
