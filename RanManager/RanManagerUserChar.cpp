// RanManagerUserChar.cpp : implementation file
//
#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerUserChar.h"
#include "RanManagerUserTab.h"

#include "COdbc.h"
#include "CCfg.h"
#include "s_NetGlobal.h"
#include "china_md5.h"
#include "Calendar.h"
#include "LogScript.h"
#include "EtcFunction.h"
#include "RanManagerComments.h"
#include ".\ranmanageruserchar.h"

// CRanManagerUserChar dialog

IMPLEMENT_DYNAMIC(CRanManagerUserChar, CPropertyPage)
CRanManagerUserChar::CRanManagerUserChar(LOGFONT logfont)
	: CPropertyPage(CRanManagerUserChar::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerUserChar::~CRanManagerUserChar()
{
}

void CRanManagerUserChar::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHAR, m_list_Char );
}


BEGIN_MESSAGE_MAP(CRanManagerUserChar, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_CHAR_DELETE, OnBnClickedButtonCharDelete)
	ON_BN_CLICKED(IDC_BUTTON_CHAR_CLEAR, OnBnClickedButtonCharClear)
	ON_BN_CLICKED(IDC_BUTTON_USERCHAR_CANCEL, OnBnClickedButtonUsercharCancel)
END_MESSAGE_MAP()


// CRanManagerUserChar message handlers
BOOL CRanManagerUserChar::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_Char.SetExtendedStyle ( m_list_Char.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |LVS_EX_CHECKBOXES);
		m_list_Char.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 6;	
		char* szColumnName1[nColumnCount] = { "#","ChaNum", "ChaName" , "ChaOnline", "ChaDeleted", ""};
		int nColumnWidthPercent[nColumnCount] = { 15,15,35,15,15,5 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_Char.InsertColumn (i, &lvColumn );
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerUserChar::SetUser(int nUser)
{
	LoadUser(nUser);
	LoadChar(nUser);
}

void CRanManagerUserChar::LoadUser(int nUser)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectUser(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	TCHAR szTemp[256] = {0};
		_snprintf( szTemp, 256, "SELECT UserID FROM %s.dbo.UserInfo WITH (NOLOCK) WHERE UserNum=%d"
		,CToolCfg::GetInstance()->szUserDb,nUser  );
	
	sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("UserChar.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLCHAR    szCharId[CHR_ID_LENGTH+1] = {0};		SQLINTEGER cbUserId = SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			::SQLGetData(hStmt, 1, SQL_C_CHAR, szCharId, CHR_ID_LENGTH+1, &cbUserId);
			SetWin_Num_int ( this, IDC_EDIT_NUM_CHAR,nUser);
			SetWin_Text ( this, IDC_EDIT_ID_CHAR,(const TCHAR*)szCharId );
		}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerUserChar::LoadChar(int nUser)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	TCHAR szTemp[256] = {0};
		_snprintf( szTemp, 256, "SELECT ChaNum,ChaName,ChaOnline,ChaDeleted FROM %s.dbo.ChaInfo WITH (NOLOCK) WHERE UserNum=%d"
		,CToolCfg::GetInstance()->szGameDb,
		nUser  );
		
	sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("UserChar.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nChaNum = 0, cbChaNum  = SQL_NTS; 
	SQLCHAR    szCharName[33] = {0};		SQLINTEGER cbCharName = SQL_NTS;
	SQLINTEGER nChaOnline = 0, cbChaOnline  = SQL_NTS; 
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
			::SQLGetData(hStmt, 2, SQL_C_CHAR, szCharName, 33 ,&cbCharName);
			::SQLGetData(hStmt, 3, SQL_C_LONG, &nChaOnline, 0, &cbChaOnline );
			::SQLGetData(hStmt, 4, SQL_C_LONG, &nChaDeleted, 0, &cbChaDeleted);

			sprintf( szTempChar, "%d", nNum );
			m_list_Char.InsertItem( nNum, szTempChar );

			sprintf( szTempChar, "%d", nChaNum );
			m_list_Char.SetItemText(nNum,1,szTempChar);

			sprintf( szTempChar, "%s", (const TCHAR*)szCharName );
			m_list_Char.SetItemText(nNum,2,szTempChar);

			CString strTemp;
			if (nChaOnline == 0 )	strTemp.Format("Offline",nChaOnline);
			else if (nChaOnline > 0 )	strTemp.Format("Online",nChaOnline);
			m_list_Char.SetItemText(nNum,3,strTemp.GetString());

			if (nChaDeleted == 0 )	strTemp.Format("Not Deleted",nChaDeleted);
			else if (nChaDeleted> 0 )	strTemp.Format("Deleted",nChaDeleted);
			m_list_Char.SetItemText(nNum,4,strTemp.GetString());

			nNum++;

		}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerUserChar::OnBnClickedButtonCharDelete()
{
	if ( MessageBox("Are you sure you want to Delete Selected Characters?\nThis is Permanent Delete!","Question",MB_YESNO) == IDYES )
	{
		int nChaNum;
		int nItem = 0; 
		for(nItem =0 ; nItem <  m_list_Char.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_Char.GetCheck(nItem);
			if( bChecked)
			{
				nChaNum = atoi ( m_list_Char.GetItemText(nItem, 1).GetString() );
				DeleteChar(nChaNum);
			}
		}
	}
}

void CRanManagerUserChar::DeleteChar(int nChaNum)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

	TCHAR szTemp[1024] = {0};
	
	_snprintf( szTemp, 1024, 
		"Delete From %s.dbo.ChaInfo "
		" Where ChaNum = %d AND UserNum =%d"
	,CToolCfg::GetInstance()->szGameDb
	,nChaNum
	,GetWin_Num_int ( this, IDC_EDIT_NUM_CHAR )
	);

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("UserChar.txt","%s--%s",strTIME.c_str(),szTemp);

	if (sReturn == SQL_ERROR )	
	{
		MessageBox("Error! Deleting Character!","Ran Manager",MB_OK);
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

	LoadChar(GetWin_Num_int ( this, IDC_EDIT_NUM_CHAR ));
}

void CRanManagerUserChar::OnBnClickedButtonCharClear()
{
	if ( MessageBox("Are you sure you want to Delete All The Characters of this User?\nThis is Permanent Delete!","Question",MB_YESNO) == IDYES )
	{
		SQLRETURN	sReturn = 0; // SQL return value (short)	
		SQLHSTMT	hStmt; // Handle of statement (void*)

		sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
		if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

		TCHAR szTemp[1024] = {0};
		
		_snprintf( szTemp, 1024, 
			"Delete From %s.dbo.ChaInfo "
			"WHERE UserNum =%d"
		,CToolCfg::GetInstance()->szGameDb
		,GetWin_Num_int ( this, IDC_EDIT_NUM_CHAR )
		);

		sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("UserChar.txt","%s--%s",strTIME.c_str(),szTemp);

		if (sReturn == SQL_ERROR )	
		{
			MessageBox("Error! Deleting Characters!","Ran Manager",MB_OK);
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
		}

		LoadChar(GetWin_Num_int ( this, IDC_EDIT_NUM_CHAR ));
	}
}

void CRanManagerUserChar::OnBnClickedButtonUsercharCancel()
{
	m_pToolTab->ActivePage(USERPAGE_MAIN,0);
}
