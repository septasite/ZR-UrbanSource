// RanManagerGuild.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerGuild.h"
#include "RanManagerGuildTab.h"
#include "RanManagerDlg.h"
#include "RanManagerTab.h"
#include "EtcFunction.h"
#include "RanManagerComments.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "s_NetGlobal.h"
#include ".\ranmanagerguild.h"


// CRanManagerGuild dialog

IMPLEMENT_DYNAMIC(CRanManagerGuild, CPropertyPage)
CRanManagerGuild::CRanManagerGuild(LOGFONT logfont)
	: CPropertyPage(CRanManagerGuild::IDD)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	nGuildNum = 0;
	strGuild = "";
}

CRanManagerGuild::~CRanManagerGuild()
{
}

void CRanManagerGuild::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_GUILD, m_list_Guild );
	DDX_Control(pDX, IDC_COMBO_CHARSEARCHTYPE, m_cSearchType );
	DDX_Control(pDX, IDC_COMBO_GUILDTYPE, m_cGuildPage );
}


BEGIN_MESSAGE_MAP(CRanManagerGuild, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_CHARSEARCHTYPE, OnCbnSelchangeComboCharsearchtype)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_GUILD, OnNMDblclkListGuild)
	ON_BN_CLICKED(IDC_BUTTON_GUILD_SELECT, OnBnClickedButtonGuildSelect)
END_MESSAGE_MAP()


// CRanManagerGuild message handlers
BOOL CRanManagerGuild::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	CRect SheetRect;
	CWnd *pWnd;
	pWnd = GetDlgItem ( IDC_STATIC_GUILD );
	pWnd->GetWindowRect ( SheetRect );
	ScreenToClient ( &SheetRect );
	LOGFONT logfont = {0};
	CFont* pFont = GetFont();
	if ( pFont ) pFont->GetLogFont( &logfont );
	m_pGuildTab = new CRanManagerGuildTab ( SheetRect, logfont, this );
	m_pGuildTab->Create( this, WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0 );
	m_pGuildTab->ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	m_pGuildTab->SetActivePage ( CHARPAGE_MAIN );

	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	m_list_Guild.SetExtendedStyle ( m_list_Guild.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_list_Guild.GetClientRect ( &rectCtrl );
	lnWidth = rectCtrl.right - rectCtrl.left;

	const int nColumnCount = 6;	
	char* szColumnName1[nColumnCount] = { "Num","GuNum", "GuildName" , "MNum", "Master Name", "Member"};
	int nColumnWidthPercent[nColumnCount] = { 7,14,28,14,23,14 };

	for ( int i = 0; i < nColumnCount; i++ )
	{		
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.pszText = szColumnName1[i];
		lvColumn.iSubItem = i;
		lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
		m_list_Guild.InsertColumn (i, &lvColumn );
	}

	for ( int i = 0; i < SEARCH_GUILDSIZE; ++i )
	{
		m_cSearchType.InsertString( i, RMComments::m_SearchGuildType[i].c_str() );
	}
	
	m_cSearchType.SetCurSel( 0 );

	OnCbnSelchangeComboCharsearchtype();

	for ( int i = 0; i < GUILDPAGE_SIZE; ++i )
	{
		m_cGuildPage.InsertString( i, RMComments::m_PageGuild[i].c_str() );
	}
	m_cGuildPage.SetCurSel( 0 );

	SetWin_ShowWindow( this ,IDC_COMBO_GUILDTYPE, FALSE );
	SetWin_ShowWindow( this ,IDC_BUTTON_GUILD_SELECT, FALSE );
	SetWin_ShowWindow( this ,IDC_EDIT_GUILDTYPE, FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
}
void CRanManagerGuild::OnBnClickedButtonSearch()
{
	int nSelect = m_cSearchType.GetCurSel();
	int nGuildNum = GetWin_Num_int(this,IDC_EDIT_SEARCH);
	std::string strSearch = GetWin_Text(this,IDC_EDIT_SEARCH);
	TCHAR szTemp[256] = {0};
	std::string strSign = "%";
	switch (nSelect)
	{
	case SEARCH_GUILDALL:
		{
			_snprintf( szTemp, 256, "SELECT GuNum,ChaNum,GuName FROM %s.dbo.GuildInfo WITH (NOLOCK) "
			"ORDER BY GuNum",CToolCfg::GetInstance()->szGameDb);
		}break;
	case SEARCH_GUILDNUM:
		{
			_snprintf( szTemp, 256, "SELECT GuNum,ChaNum,GuName FROM %s.dbo.GuildInfo WITH (NOLOCK) WHERE GuNum LIKE '%s%d%s' "
			"ORDER BY GuNum",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),nGuildNum,strSign.c_str());
		}break;
	case SEARCH_GUILDNAME:
		{
			_snprintf( szTemp, 256, "SELECT GuNum,ChaNum,GuName FROM %s.dbo.GuildInfo WITH (NOLOCK) WHERE GuName LIKE '%s%s%s' "
			"ORDER BY GuNum",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),strSearch.c_str(),strSign.c_str());
		}break;
	case SEARCH_MASTERNAME:
		{
			GetGuildMaster( strSearch.c_str() );
		}break;
	};


	switch (nSelect)
	{
	case SEARCH_GUILDALL:
	case SEARCH_GUILDNUM:
	case SEARCH_GUILDNAME:
		{
			SQLRETURN	sReturn = 0; // SQL return value (short)	
			SQLHSTMT	hStmt; // Handle of statement (void*)

			sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
			if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
			{
				return;
			}

			std::string strTIME = CDebugSet::GetCurTime ();
			LOGSCRIPT::LogToFile("Guild.txt","%s--%s",strTIME.c_str(),szTemp);

			sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);

			if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
			{
				::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				return;
			}

			SQLINTEGER nGuNum = 0, cbGuNum = SQL_NTS; 
			SQLINTEGER nChaNum = 0, cbChaNum = SQL_NTS; 
			SQLCHAR    szGuName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbGuName = SQL_NTS;

			int nNum = 0;
			char szTempChar[256];
			m_list_Guild.DeleteAllItems();
			while (true)
			{
				sReturn = ::SQLFetch(hStmt);
				if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
				if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
				{
					::SQLGetData(hStmt, 1, SQL_C_LONG, &nGuNum, 0, &cbGuNum );	
					::SQLGetData(hStmt, 2, SQL_C_LONG, &nChaNum, 0, &cbChaNum );	
					::SQLGetData(hStmt, 3, SQL_C_CHAR, szGuName, CHR_ID_LENGTH, &cbGuName );
				
					sprintf( szTempChar, "%d", nNum );
					m_list_Guild.InsertItem( nNum, szTempChar );
					sprintf( szTempChar, "%d", nGuNum );
					m_list_Guild.SetItemText(nNum,1,szTempChar);
					sprintf( szTempChar, "%s", szGuName );
					m_list_Guild.SetItemText(nNum,2,szTempChar);
					sprintf( szTempChar, "%d", nChaNum );
					m_list_Guild.SetItemText(nNum,3,szTempChar);

					nNum++;	}
				else	break;
				Sleep( 0 );
			}
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

			GetMaster();
			GetMembers();
		}break;

	case SEARCH_MASTERNAME:
		{
			VEC_SEARCH_NUM_ITER iter = m_VecSearchNum.begin();
			VEC_SEARCH_NUM_ITER iter_end = m_VecSearchNum.end();
			m_list_Guild.DeleteAllItems();
			int nNum = 0;
			char szTempChar[256];
			for ( ; iter!=iter_end; ++iter )
			{
				SQLRETURN	sReturn = 0; // SQL return value (short)	
				SQLHSTMT	hStmt; // Handle of statement (void*)

				sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
				if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
				{
					continue;
				}

				_snprintf( szTemp, 256, "SELECT GuNum,ChaNum,GuName FROM %s.dbo.GuildInfo WITH (NOLOCK) WHERE ChaNum = %d "
				"ORDER BY GuNum",CToolCfg::GetInstance()->szGameDb,int (*iter));

				std::string strTIME = CDebugSet::GetCurTime ();
				LOGSCRIPT::LogToFile("GuildSearch.txt","%s--%s",strTIME.c_str(),szTemp);

				sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);

				if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
				{
					::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
					return;
				}

				SQLINTEGER nGuNum = 0, cbGuNum = SQL_NTS; 
				SQLINTEGER nChaNum = 0, cbChaNum = SQL_NTS; 
				SQLCHAR    szGuName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbGuName = SQL_NTS;

				while (true)
				{
					sReturn = ::SQLFetch(hStmt);
					if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
					if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
					{
						::SQLGetData(hStmt, 1, SQL_C_LONG, &nGuNum, 0, &cbGuNum );	
						::SQLGetData(hStmt, 2, SQL_C_LONG, &nChaNum, 0, &cbChaNum );	
						::SQLGetData(hStmt, 3, SQL_C_CHAR, szGuName, CHR_ID_LENGTH, &cbGuName );
					
						sprintf( szTempChar, "%d", nNum );
						m_list_Guild.InsertItem( nNum, szTempChar );
						sprintf( szTempChar, "%d", nGuNum );
						m_list_Guild.SetItemText(nNum,1,szTempChar);
						sprintf( szTempChar, "%s", szGuName );
						m_list_Guild.SetItemText(nNum,2,szTempChar);
						sprintf( szTempChar, "%d", nChaNum );
						m_list_Guild.SetItemText(nNum,3,szTempChar);

						nNum++;	}
					else	break;
					Sleep( 0 );
				}
				::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			}
			GetMaster();
			GetMembers();
		}break;
	};
}

void	CRanManagerGuild::GetGuildMaster( std::string strSearch )
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

	TCHAR szTemp[1024] = {0};
	std::string strSign = "%";
	_snprintf( szTemp, 1024, "SELECT ChaNum "
						"FROM %s.dbo.ChaInfo WHERE ChaName LIKE '%s%s%s' ",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),strSearch.c_str(),strSign.c_str() );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("Guild.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nChaNum = 0, cbChaNum = SQL_NTS; 

	m_VecSearchNum.clear();
	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{		
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nChaNum, 0, &cbChaNum );
			m_VecSearchNum.push_back(nChaNum);
		}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void CRanManagerGuild::GetMaster()
{
	int nItem = 0; 
	for(nItem =0 ; nItem < m_list_Guild.GetItemCount(); nItem++)
	{
		SQLRETURN	sReturn = 0; // SQL return value (short)	
		SQLHSTMT	hStmt; // Handle of statement (void*)

		int nChaNum =  atoi ( m_list_Guild.GetItemText(nItem, 3).GetString() );

		sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
		if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	continue;

		TCHAR szTemp[1024] = {0};
		_snprintf( szTemp, 1024, "SELECT ChaName "
							"FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChaNum );

		sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("Guild.txt","%s--%s",strTIME.c_str(),szTemp);

		if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
		{
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return;
		}

		SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaName = SQL_NTS; 
	
		char szTempChar[256];
		while (true)
		{
			sReturn = ::SQLFetch(hStmt);
			if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
			if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
			{		
				::SQLGetData(hStmt, 1, SQL_C_CHAR, szChaName   ,  CHR_ID_LENGTH+1, &cbChaName); 
				sprintf( szTempChar, "%s",(const char*) szChaName );
				m_list_Guild.SetItemText(nItem,4,szTempChar);
				break;
			}
			else	break;
			Sleep( 0 );
		}
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}		
}

void CRanManagerGuild::GetMembers()
{
	int nItem = 0; 
	for(nItem =0 ; nItem < m_list_Guild.GetItemCount(); nItem++)
	{
		SQLRETURN	sReturn = 0; // SQL return value (short)	
		SQLHSTMT	hStmt; // Handle of statement (void*)

		int nGuNum =  atoi ( m_list_Guild.GetItemText(nItem, 1).GetString() );

		sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
		if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	continue;

		TCHAR szTemp[1024] = {0};
		_snprintf( szTemp, 256, "SELECT ChaNum FROM %s.dbo.ChaInfo WHERE GuNum = %d "
		"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nGuNum);
		
		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("Guild.txt","%s--%s",strTIME.c_str(),szTemp);

		sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

		if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
		{
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return;
		}

		int nNum = 0;
		char szTempChar[256];
		while (true)
		{
			sReturn = ::SQLFetch(hStmt);
			if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
			if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)	nNum++;
			else	break;
			Sleep( 0 );
		}
		sprintf( szTempChar, "%d",nNum);
		m_list_Guild.SetItemText(nItem,5,szTempChar);
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}		
}
void CRanManagerGuild::OnCbnSelchangeComboCharsearchtype()
{
	int nSelect = m_cSearchType.GetCurSel();
	if (nSelect == SEARCH_GUILDALL ) SetWin_Enable(this,IDC_EDIT_SEARCH,false);
	else	 SetWin_Enable(this,IDC_EDIT_SEARCH,true);
}

void CRanManagerGuild::OnNMDblclkListGuild(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nSelect = m_list_Guild.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;
	nGuildNum = atoi ( m_list_Guild.GetItemText(nSelect,1).GetString() );
	strGuild = m_list_Guild.GetItemText(nSelect,2).GetString();

	SetWin_ShowWindow( this ,IDC_COMBO_GUILDTYPE, TRUE );
	SetWin_ShowWindow( this ,IDC_BUTTON_GUILD_SELECT, TRUE );
	SetWin_ShowWindow( this ,IDC_EDIT_GUILDTYPE, TRUE );

	SetWin_Num_int ( this, IDC_EDIT_SELECTED_NUM,nGuildNum );
	SetWin_Text ( this, IDC_EDIT_SELECTED_NAME, strGuild.GetString() );

	m_pGuildTab->ActivePage(GUILDPAGE_EDIT,nGuildNum);
	m_cGuildPage.SetCurSel(GUILDPAGE_EDIT);
	SetWin_Text(this,IDC_EDIT_GUILDTYPE,RMComments::m_PageGuild[GUILDPAGE_EDIT].c_str() );
}

void CRanManagerGuild::OnBnClickedButtonGuildSelect()
{
	int nSelect = m_cGuildPage.GetCurSel();
	SetWin_Text(this,IDC_EDIT_GUILDTYPE,RMComments::m_PageGuild[nSelect].c_str() );
	switch (nSelect)
	{
	case GUILDPAGE_MAIN:	m_pGuildTab->ActivePage ( GUILDPAGE_MAIN ,nGuildNum );	break;
	case GUILDPAGE_EDIT:	m_pGuildTab->ActivePage ( GUILDPAGE_EDIT ,nGuildNum );	break;
	case GUILDPAGE_LOCKER:	m_pGuildTab->ActivePage ( GUILDPAGE_LOCKER ,nGuildNum );	break;
	case GUILDPAGE_MEMBER:	m_pGuildTab->ActivePage ( GUILDPAGE_MEMBER ,nGuildNum );	break;
	case GUILDPAGE_IMAGE:	m_pGuildTab->ActivePage ( GUILDPAGE_IMAGE ,nGuildNum );	break;
	};
}
