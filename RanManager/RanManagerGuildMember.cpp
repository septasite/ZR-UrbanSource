// RanManagerGuildMember.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerGuildMember.h"
#include ".\ranmanagerguildmember.h"
#include "RanManagerGuildTab.h"
#include "RanManagerComments.h"

#include "EtcFunction.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "CharSearch.h"
#include "s_NetGlobal.h"

// CRanManagerGuildMember dialog

IMPLEMENT_DYNAMIC(CRanManagerGuildMember, CPropertyPage)
CRanManagerGuildMember::CRanManagerGuildMember(LOGFONT logfont)
	: CPropertyPage(CRanManagerGuildMember::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerGuildMember::~CRanManagerGuildMember()
{
}

void CRanManagerGuildMember::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_GUILD_MEMBER, m_list_Char );
	DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE, m_cSearchType );
}


BEGIN_MESSAGE_MAP(CRanManagerGuildMember, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_MEMBER_CANCEL, OnBnClickedBtnMemberCancel)
	ON_BN_CLICKED(IDC_BUTTON_MEMBER_REMOVEALL, OnBnClickedButtonMemberRemoveall)
	ON_BN_CLICKED(IDC_BUTTON_MEMBER_REMOVE, OnBnClickedButtonMemberRemove)
	ON_BN_CLICKED(IDC_BUTTON_MEMBER_EDIT, OnBnClickedButtonMemberEdit)
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCH_TYPE, OnCbnSelchangeComboSearchType)
	ON_BN_CLICKED(IDC_BUTTON_GUILDSEARCH, OnBnClickedButtonGuildsearch)
	ON_BN_CLICKED(IDC_BUTTON_MEMBER_ADD, OnBnClickedButtonMemberAdd)
	ON_BN_CLICKED(IDC_BUTTON_CHA_SAVE, OnBnClickedButtonChaSave)
	ON_BN_CLICKED(IDC_BUTTON_CHA_CANCEL, OnBnClickedButtonChaCancel)
END_MESSAGE_MAP()


// CRanManagerGuildMember message handlers
BOOL CRanManagerGuildMember::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	m_list_Char.SetExtendedStyle ( m_list_Char.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);

	m_list_Char.GetClientRect ( &rectCtrl );
	lnWidth = rectCtrl.right - rectCtrl.left;

	const int nColumnCount = 7;	
	char* szColumnName1[nColumnCount] = { "Num","ChaNum","UserNum","ChaName","GuildPos","Online","Deleted"};
	int nColumnWidthPercent[nColumnCount] = { 10,10,10,40,10,10,10};

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

	SetWin_Enable(this,IDC_BUTTON_CHA_SAVE,FALSE);
	SetWin_Enable(this,IDC_BUTTON_CHA_CANCEL,FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerGuildMember::SetGuild(int nGuildNum)
{
	GetGuild(nGuildNum);
	GetMembers(nGuildNum);
}

void CRanManagerGuildMember::GetGuild(int nGuildNum)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

	TCHAR szTemp[1024] = {0};
	
	_snprintf( szTemp, 1024, 
		"SELECT GuNum,GuName FROM %s.dbo.GuildInfo WITH (NOLOCK) WHERE GuNum =%d "
	,CToolCfg::GetInstance()->szGameDb,nGuildNum);

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildMember.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nGuNum = 0,							cbGuNum = SQL_NTS; 
	SQLCHAR    szGuName[CHR_ID_LENGTH+1] = {0};		SQLINTEGER cbGuName = SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	return;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			::SQLGetData(hStmt, 1, SQL_C_LONG,		&nGuNum,			0,		&cbGuNum );
			::SQLGetData(hStmt, 2, SQL_C_CHAR,		szGuName,			CHR_ID_LENGTH,  &cbGuName);
		}
		else	break;
		Sleep( 0 );
	}

	SetWin_Num_int ( this, IDC_EDIT_NUM,nGuNum);
	SetWin_Text ( this, IDC_EDIT_ID, (const TCHAR*)szGuName );

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerGuildMember::GetMembers(int nGuildNum)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	TCHAR szTemp[256] = {0};
	_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE GuNum=%d"
	"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nGuildNum);

	sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildMember.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nChaNum = 0, cbChaNum = SQL_NTS; 
	SQLINTEGER nUserNum = 0, cbUserNum = SQL_NTS; 
	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbCharId = SQL_NTS;
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
			::SQLGetData(hStmt, 4, SQL_C_LONG, &nGuPosition, 0, &cbGuPosition );
			::SQLGetData(hStmt, 5, SQL_C_LONG, &nChaOnline, 0, &cbChaOnline );	
			::SQLGetData(hStmt, 6, SQL_C_LONG, &nChaDeleted, 0, &cbChaDeleted );	
			
			sprintf( szTempChar, "%d", nNum );
			m_list_Char.InsertItem( nNum, szTempChar );

			sprintf( szTempChar, "%d", nChaNum );
			m_list_Char.SetItemText(nNum,1,szTempChar);

			sprintf( szTempChar, "%d", nUserNum );
			m_list_Char.SetItemText(nNum,2,szTempChar);

			sprintf( szTempChar, "%s", szChaName );
			m_list_Char.SetItemText(nNum,3,szTempChar);

			sprintf( szTempChar, "%d", nGuPosition );
			m_list_Char.SetItemText(nNum,4,szTempChar);
			
			CString strTemp;
			if (nChaOnline >0 )	strTemp.Format("Online",nChaOnline);
			else strTemp.Format("Offline",nChaOnline);
			m_list_Char.SetItemText(nNum,5,strTemp.GetString());

			if (nChaDeleted >0 )	strTemp.Format("Deleted",nChaDeleted);
			else strTemp.Format("Active",nChaDeleted);
			m_list_Char.SetItemText(nNum,6,strTemp.GetString());

			nNum++;	}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerGuildMember::OnBnClickedBtnMemberCancel()
{
	m_pToolTab->ActivePage(GUILDPAGE_MAIN,0);
}

void CRanManagerGuildMember::OnBnClickedButtonMemberRemoveall()
{
	if ( MessageBox ( "Do You Want To Remove All Guild Members?", "Question", MB_YESNO ) == IDYES )
	{
		int nItem = 0; 
		int nOk = 0;
		int nError = 0;
		for(nItem =0 ; nItem <  m_list_Char.GetItemCount(); nItem++)
		{
			int nSelect = atoi ( m_list_Char.GetItemText(nItem,1).GetString() );
			if ( RemoveMember(nSelect) )	nOk++;
			else nError++;
		}

		GetMembers( GetWin_Num_int(this,IDC_EDIT_NUM) );

		CString strTemp;
		strTemp.Format("Remove Sucess:%d---Remove Error:%d",nOk,nError);
		MessageBox(strTemp,"Info",MB_OK);
	}
}

void CRanManagerGuildMember::OnBnClickedButtonMemberRemove()
{
	if ( MessageBox ( "Do You Want To Remove Selected Guild Members?", "Question", MB_YESNO ) == IDYES )
	{
		int nItem = 0; 
		int nOk = 0;
		int nError = 0;
		for(nItem =0 ; nItem <  m_list_Char.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_Char.GetCheck(nItem);
			if( bChecked)
			{
				int nSelect = atoi ( m_list_Char.GetItemText(nItem,1).GetString() );
				if ( RemoveMember(nSelect) )	nOk++;
				else nError++;
			}
		}

		GetMembers( GetWin_Num_int(this,IDC_EDIT_NUM) );

		CString strTemp;
		strTemp.Format("Remove Sucess:%d---Remove Error:%d",nOk,nError);
		MessageBox(strTemp,"Info",MB_OK);
	}
}

void CRanManagerGuildMember::OnBnClickedButtonMemberEdit()
{
	int nSelect = m_list_Char.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;
	int nSelectedChar =  atoi ( m_list_Char.GetItemText(nSelect,1).GetString() );


	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	TCHAR szTemp[256] = {0};
	_snprintf( szTemp, 256, "SELECT ChaNum,ChaName,GuPosition,ChaGuName FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaNum=%d"
	"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nSelectedChar);

	sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildMember.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nChaNum = 0, cbChaNum = SQL_NTS; 
	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbCharId = SQL_NTS;
	SQLINTEGER nGuPosition = 0, cbGuPosition = SQL_NTS; 
	SQLCHAR    szChaGuName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaGuName = SQL_NTS;


	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nChaNum, 0, &cbChaNum );		
			::SQLGetData(hStmt, 2, SQL_C_CHAR, szChaName, CHR_ID_LENGTH, &cbCharId );
			::SQLGetData(hStmt, 3, SQL_C_LONG, &nGuPosition, 0, &cbGuPosition );
			::SQLGetData(hStmt, 4, SQL_C_CHAR, szChaGuName, CHR_ID_LENGTH, &cbChaGuName );
		}
		else	break;
		Sleep( 0 );
	}

	SetWin_Num_int(this,IDC_EDIT_CHA_NUM,nChaNum);
	SetWin_Text(this,IDC_EDIT_CHA_NAME,(const TCHAR*)szChaName );

	DWORD	dwFlags = nGuPosition;
	SetWin_Check ( this, IDC_CHECK_G_INVITE, dwFlags&EMCLUB_SUBMATER_JOIN );
	SetWin_Check ( this, IDC_CHECK_G_KICK, dwFlags&EMCLUB_SUBMATER_KICK );
	SetWin_Check ( this, IDC_CHECK_G_NOTICE, dwFlags&EMCLUB_SUBMATER_NOTICE );
	SetWin_Check ( this, IDC_CHECK_G_VERIFY, dwFlags&EMCLUB_SUBMATER_CD );
	SetWin_Check ( this, IDC_CHECK_G_BADGE, dwFlags&EMCLUB_SUBMATER_MARK );
	SetWin_Check ( this, IDC_CHECK_G_CDM, dwFlags&EMCLUB_SUBMATER_CDM );

	SetWin_Text(this,IDC_EDIT_CHA_AMMEND,(const TCHAR*)szChaGuName );

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	

	SetWin_Enable(this,IDC_BUTTON_CHA_SAVE,TRUE);
	SetWin_Enable(this,IDC_BUTTON_CHA_CANCEL,TRUE);
}

void CRanManagerGuildMember::OnCbnSelchangeComboSearchType()
{
	int nSelect = m_cSearchType.GetCurSel();
	if (nSelect == SEARCH_CHAALL || nSelect == SEARCH_CHAONLINE || nSelect == SEARCH_CHADELETED ) SetWin_Enable(this,IDC_EDIT_SEARCH,false);
	else	 SetWin_Enable(this,IDC_EDIT_SEARCH,true);
}

void CRanManagerGuildMember::OnBnClickedButtonGuildsearch()
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	int nGuildNum = GetWin_Num_int(this,IDC_EDIT_NUM);
	int nType = m_cSearchType.GetCurSel();
	TCHAR szTemp[256] = {0};
	std::string strSign = "%";
	switch (nType)
	{
	case SEARCH_CHAALL :
		{
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE GuNum=%d "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nGuildNum);
		}break;
	case SEARCH_CHANUM :
		{
			int nFind =  GetWin_Num_int(this,IDC_EDIT_SEARCH);
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE GuNum=%d AND ChaNum LIKE '%s%d%s' "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nGuildNum,strSign.c_str(),nFind,strSign.c_str() );
		}break;
	case SEARCH_CHAUSERNUM :
		{
			int nFind =  GetWin_Num_int(this,IDC_EDIT_SEARCH);
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE GuNum=%d AND UserNum LIKE '%s%d%s' "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nGuildNum ,strSign.c_str(),nFind,strSign.c_str());
		}break;
	case SEARCH_CHANAME :
		{
			std::string strUserSearch  = GetWin_Text ( this, IDC_EDIT_SEARCH ); 
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE GuNum=%d AND ChaName LIKE '%s%s%s' "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nGuildNum,strSign.c_str(),strUserSearch.c_str(),strSign.c_str() );
		}break;
	case SEARCH_CHAONLINE :
		{
			int nFind =  GetWin_Num_int(this,IDC_EDIT_SEARCH);
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE GuNum=%d AND ChaOnline > 0  "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nGuildNum ,nFind);
		}break;
	case SEARCH_CHADELETED :
		{
			int nFind =  GetWin_Num_int(this,IDC_EDIT_SEARCH);
			_snprintf( szTemp, 256, "SELECT ChaNum,UserNum,ChaName,GuPosition,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE GuNum=%d AND ChaDeleted >= 1  "
			"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nGuildNum,nFind );
		}break;
	};
	

	sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildMember.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nChaNum = 0, cbChaNum = SQL_NTS; 
	SQLINTEGER nUserNum = 0, cbUserNum = SQL_NTS; 
	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbCharId = SQL_NTS;
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
			::SQLGetData(hStmt, 4, SQL_C_LONG, &nGuPosition, 0, &cbGuPosition );
			::SQLGetData(hStmt, 5, SQL_C_LONG, &nChaOnline, 0, &cbChaOnline );	
			::SQLGetData(hStmt, 6, SQL_C_LONG, &nChaDeleted, 0, &cbChaDeleted );	
			
			sprintf( szTempChar, "%d", nNum );
			m_list_Char.InsertItem( nNum, szTempChar );

			sprintf( szTempChar, "%d", nChaNum );
			m_list_Char.SetItemText(nNum,1,szTempChar);

			sprintf( szTempChar, "%d", nUserNum );
			m_list_Char.SetItemText(nNum,2,szTempChar);

			sprintf( szTempChar, "%s", szChaName );
			m_list_Char.SetItemText(nNum,3,szTempChar);

			sprintf( szTempChar, "%d", (int)nGuPosition );
			m_list_Char.SetItemText(nNum,4,szTempChar);
			
			CString strTemp;
			if (nChaOnline >0 )	strTemp.Format("Online(%d)",(int)nChaOnline);
			else strTemp.Format("Offline(%d)",(int)nChaOnline);
			m_list_Char.SetItemText(nNum,5,strTemp.GetString());

			if (nChaDeleted >0 )	strTemp.Format("Deleted(%d)",(int)nChaDeleted);
			else strTemp.Format("Active(%d)",(int)nChaDeleted);
			m_list_Char.SetItemText(nNum,6,strTemp.GetString());

			nNum++;	}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

BOOL CRanManagerGuildMember::RemoveMember(int nChaNum)
{
	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "UPDATE %s.dbo.ChaInfo SET GuNum=%d, GuPosition=%u"
				" WHERE ChaNum=%u", 
	CToolCfg::GetInstance()->szGameDb,
	0, 
	0, 
	nChaNum
	);
		
	SQLRETURN	sReturn = 0; 	
	SQLHSTMT	hStmt; 

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return FALSE;

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildMember.txt","%s--%s",strTIME.c_str(),szTemp);

	if (sReturn == SQL_ERROR )	return FALSE;
	if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)	return TRUE;

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	return FALSE;
}

BOOL CRanManagerGuildMember::HaveGuild(int nChaNum)
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

	_snprintf( szTemp, 256, "SELECT ChaNum,GuNum FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaNum =%d "
	"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nChaNum );

	sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("Char.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return FALSE;
	}

	SQLINTEGER nChaNum1 = 0, cbChaNum = SQL_NTS; 
	SQLINTEGER nGuNum = 0, cbGuNum = SQL_NTS; 

	int nNum = 0;
	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nChaNum1, 0, &cbChaNum );
			::SQLGetData(hStmt, 2, SQL_C_LONG, &nGuNum, 0, &cbGuNum );

			if (nGuNum > 0 ) return TRUE;
			nNum++;	}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	

	return FALSE;
}

void CRanManagerGuildMember::OnBnClickedButtonMemberAdd()
{
	CCharSearch sCharSearch;
	sCharSearch.SetMultiple(true);
	if ( IDOK == sCharSearch.DoModal () )
	{
		int nOK = 0;
		int nError = 0;
		CCharSearch::VEC_CHAR_SEARCH_RESULT_ITER iter = sCharSearch.m_VecSearchResult.begin();
		CCharSearch::VEC_CHAR_SEARCH_RESULT_ITER iter_end = sCharSearch.m_VecSearchResult.end();
		for ( ; iter!=iter_end; ++iter )
		{
			int nNum = (*iter);

			if ( HaveGuild(nNum) ){	nError++;	}
			else{
				if ( JoinGuild(nNum) ){	nOK++;}
				else{	nError++;	}	}
		}

		CString strTemp;
		strTemp.Format("Join Guild Sucess:%d---Join Guild Error:%d",nOK,nError);
		MessageBox(strTemp,"Info",MB_OK);

		GetMembers( GetWin_Num_int(this,IDC_EDIT_NUM) );
	}
}

BOOL CRanManagerGuildMember::JoinGuild(int nChaNum)
{
	TCHAR szTemp[1024] = {0};
	int nGuildNum = GetWin_Num_int(this,IDC_EDIT_NUM);
	_snprintf( szTemp, 1024, "UPDATE %s.dbo.ChaInfo SET GuNum=%d, GuPosition=%u"
				" WHERE ChaNum=%u", 
	CToolCfg::GetInstance()->szGameDb,
	nGuildNum, 
	0, 
	nChaNum
	);
		
	SQLRETURN	sReturn = 0; 	
	SQLHSTMT	hStmt; 

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return FALSE;

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildMember.txt","%s--%s",strTIME.c_str(),szTemp);

	if (sReturn == SQL_ERROR )	return FALSE;
	if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)	return TRUE;

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	return FALSE;
}

void CRanManagerGuildMember::OnBnClickedButtonChaSave()
{
	TCHAR szTemp[1024] = {0};

	DWORD	dwFlags;
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_G_INVITE ),dwFlags, EMCLUB_SUBMATER_JOIN );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_G_KICK ),dwFlags, EMCLUB_SUBMATER_KICK );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_G_NOTICE ),dwFlags, EMCLUB_SUBMATER_NOTICE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_G_VERIFY ),dwFlags, EMCLUB_SUBMATER_CD );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_G_BADGE ),dwFlags, EMCLUB_SUBMATER_MARK );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_G_CDM ),dwFlags, EMCLUB_SUBMATER_CDM );

	int nChaNum = GetWin_Num_int(this,IDC_EDIT_CHA_NUM);
	_snprintf( szTemp, 1024, "UPDATE %s.dbo.ChaInfo SET GuPosition=%d, ChaGuName='%s' "
				"WHERE ChaNum=%u", 
	CToolCfg::GetInstance()->szGameDb,
	(int)dwFlags, 
	GetWin_Text(this,IDC_EDIT_CHA_AMMEND),
	nChaNum
	);
		
	SQLRETURN	sReturn = 0; 	
	SQLHSTMT	hStmt; 

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildMember.txt","%s--%s",strTIME.c_str(),szTemp);

	if (sReturn == SQL_ERROR )
	{
		MessageBox("Save Error!","Info",MB_OK);
		return;
	}
	if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)	
	{
		MessageBox("Save Complete!","Info",MB_OK);
	}

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	SetWin_Enable(this,IDC_BUTTON_CHA_SAVE,FALSE);
	SetWin_Enable(this,IDC_BUTTON_CHA_CANCEL,FALSE);
}

void CRanManagerGuildMember::OnBnClickedButtonChaCancel()
{
	SetWin_Num_int(this,IDC_EDIT_CHA_NUM,0);
	SetWin_Text(this,IDC_EDIT_CHA_NAME,"NULL" );

	SetWin_Check ( this, IDC_CHECK_G_INVITE, FALSE );
	SetWin_Check ( this, IDC_CHECK_G_KICK, FALSE );
	SetWin_Check ( this, IDC_CHECK_G_NOTICE, FALSE );
	SetWin_Check ( this, IDC_CHECK_G_VERIFY, FALSE );
	SetWin_Check ( this, IDC_CHECK_G_BADGE, FALSE );
	SetWin_Check ( this, IDC_CHECK_G_CDM, FALSE );

	SetWin_Text(this,IDC_EDIT_CHA_AMMEND,"NULL" );
	
	SetWin_Enable(this,IDC_BUTTON_CHA_SAVE,FALSE);
	SetWin_Enable(this,IDC_BUTTON_CHA_CANCEL,FALSE);
}
