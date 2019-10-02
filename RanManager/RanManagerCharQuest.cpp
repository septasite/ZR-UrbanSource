// RanManagerCharQuest.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerCharQuest.h"
#include "RanManagerCharTab.h"

#include "COdbc.h"
#include "CCfg.h"
#include "s_NetGlobal.h"
#include "Calendar.h"
#include "LogScript.h"
#include "ItemSearch.h"
#include "EtcFunction.h"
#include "RanManagerComments.h"
#include "../NetServerLib/s_DbBase.h"
#include "../EngineLib/Common/ByteStream.h"
#include "GLDefine.h"
#include ".\ranmanagercharquest.h"
// CRanManagerCharQuest dialog

IMPLEMENT_DYNAMIC(CRanManagerCharQuest, CPropertyPage)
CRanManagerCharQuest::CRanManagerCharQuest(LOGFONT logfont)
	: CPropertyPage(CRanManagerCharQuest::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerCharQuest::~CRanManagerCharQuest()
{
}

void CRanManagerCharQuest::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_QUEST_RUN, m_list_Quest_Run );
	DDX_Control(pDX, IDC_LIST_QUEST_DONE, m_list_Quest_Done );
}


BEGIN_MESSAGE_MAP(CRanManagerCharQuest, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_RUN_DELETE, OnBnClickedButtonRunDelete)
	ON_BN_CLICKED(IDC_BUTTON_RUN_DELETE_ALL, OnBnClickedButtonRunDeleteAll)
	ON_BN_CLICKED(IDC_BUTTON_DONE_DELETE, OnBnClickedButtonDoneDelete)
	ON_BN_CLICKED(IDC_BUTTON_DONE_DELETE_ALL, OnBnClickedButtonDoneDeleteAll)
	ON_BN_CLICKED(IDC_BUTTON_QUEST_SAVE, OnBnClickedButtonQuestSave)
	ON_BN_CLICKED(IDC_BUTTON_QUEST_CANCEL, OnBnClickedButtonQuestCancel)
END_MESSAGE_MAP()


// CRanManagerCharQuest message handlers
BOOL CRanManagerCharQuest::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_Quest_Run.SetExtendedStyle (m_list_Quest_Run.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |LVS_EX_CHECKBOXES);
		m_list_Quest_Run.GetClientRect ( &rectCtrl );
		m_list_Quest_Done.SetExtendedStyle (m_list_Quest_Done.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |LVS_EX_CHECKBOXES);
		m_list_Quest_Done.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 5;	
		char* szColumnName1[nColumnCount] = { "#","MID", "SID" , "Quest",""};
		int nColumnWidthPercent[nColumnCount] = { 15,15,15,50,5 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_Quest_Run.InsertColumn (i, &lvColumn );
			m_list_Quest_Done.InsertColumn (i, &lvColumn );
		}
	}


	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerCharQuest::SetChar(int nChar)
{
	LoadChar(nChar);
	LoadQuest(nChar);
}

void CRanManagerCharQuest::LoadChar(int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT ChaNum,ChaName FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChar );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharQuest.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	return;

	SQLINTEGER nCharNum = 0, cbCharNum=SQL_NTS;
	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaName = SQL_NTS; 
	
	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{		
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nCharNum,       0, &cbCharNum);
            ::SQLGetData(hStmt, 2, SQL_C_CHAR, szChaName   ,  CHR_ID_LENGTH+1, &cbChaName); 
            
			SetWin_Num_int(this,IDC_EDIT_CHANUM,nCharNum);
			SetWin_Text(this,IDC_EDIT_CHANAME,(const char*) szChaName);
		}
		else
		{
			break;
		}
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerCharQuest::LoadQuest(int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)
	CByteStream ByteStream;
	
	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "SELECT ChaQuest FROM  %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaNum=%u"
		,CToolCfg::GetInstance()->szGameDb,nChar );
	
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharQuest.txt","%s--%s",strTIME.c_str(),szTemp);

	if ( sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO )
	{
		MessageBox("Error Reading Quests Binary","Error",MB_OK);
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return ;
	}

	SQLCHAR		pBinary[DB_IMAGE_BUF_SIZE] = {0};	// Declare a binary buffer to retrieve 1024 bytes of data at a time.
	SQLINTEGER  lSize=0, lTotalSize=0;	
	ByteStream.ClearBuffer();

	while ( (sReturn = ::SQLFetch(hStmt) ) != SQL_NO_DATA )
	{			
		while (1) 
		{
			::memset( pBinary, 0, DB_IMAGE_BUF_SIZE );
			lSize = 0;
			sReturn = ::SQLGetData(
							hStmt,
							1,
							SQL_C_BINARY,
							pBinary,
							DB_IMAGE_BUF_SIZE,
							&lSize );
			if (lSize > 0)
			{
				if (lSize > DB_IMAGE_BUF_SIZE) lSize = DB_IMAGE_BUF_SIZE;
				lTotalSize += lSize;
				ByteStream.WriteBuffer( (LPBYTE) pBinary, lSize );
			}
			if (sReturn == SQL_NO_DATA || lSize == 0)
				break;
		}

		if ( lTotalSize < DB_IMAGE_MIN_SIZE )		
			ByteStream.ClearBuffer ();
	}

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	if ( ByteStream.IsEmpty() )
	{
		MessageBox("Binary Data Empty!","Error",MB_OK);
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	m_cQuestPlay.DeleteAll();
	m_cQuestPlay.GET_BYBUFFER ( ByteStream );

	ShowQuestsRun();
	ShowQuestsDone();
}

void CRanManagerCharQuest::ShowQuestsRun()
{
	int nNum = 0;
	char szTempChar[1024];
	m_list_Quest_Run.DeleteAllItems();
	GLQuestPlay::MAPQUEST& mapQuest = m_cQuestPlay.GetQuestProc ();
	GLQuestPlay::MAPQUEST_ITER iter = mapQuest.begin();
	GLQuestPlay::MAPQUEST_ITER iter_end = mapQuest.end();
	for ( ; iter!=iter_end; ++iter )
	{
		GLQUESTPROG *pPROG = (*iter).second;
		GLQUEST *pQUEST = GLQuestMan::GetInstance().Find ( pPROG->m_sNID.dwID );
		if ( pQUEST )
		{
			sprintf( szTempChar, "%d", nNum );
			m_list_Quest_Run.InsertItem( nNum, szTempChar );

			sprintf( szTempChar, "%d", pQUEST->m_sNID.wMainID );
			m_list_Quest_Run.SetItemText(nNum,1,szTempChar);

			sprintf( szTempChar, "%d", pQUEST->m_sNID.wSubID );
			m_list_Quest_Run.SetItemText(nNum,2,szTempChar);

			sprintf( szTempChar, "%s", pQUEST->m_strTITLE.c_str() );
			m_list_Quest_Run.SetItemText(nNum,3,szTempChar);
			nNum++;
		}
	}
}

void CRanManagerCharQuest::ShowQuestsDone()
{
	int nNum = 0;
	char szTempChar[1024];
	m_list_Quest_Done.DeleteAllItems();
	GLQuestPlay::MAPQUEST& mapQuest = m_cQuestPlay.GetQuestEnd ();
	GLQuestPlay::MAPQUEST_ITER iter = mapQuest.begin();
	GLQuestPlay::MAPQUEST_ITER iter_end = mapQuest.end();
	for ( ; iter!=iter_end; ++iter )
	{
		GLQUESTPROG *pPROG = (*iter).second;
		GLQUEST *pQUEST = GLQuestMan::GetInstance().Find ( pPROG->m_sNID.dwID );
		if ( pQUEST )
		{
			sprintf( szTempChar, "%d", nNum );
			m_list_Quest_Done.InsertItem( nNum, szTempChar );

			sprintf( szTempChar, "%d", pQUEST->m_sNID.wMainID );
			m_list_Quest_Done.SetItemText(nNum,1,szTempChar);

			sprintf( szTempChar, "%d", pQUEST->m_sNID.wSubID );
			m_list_Quest_Done.SetItemText(nNum,2,szTempChar);

			sprintf( szTempChar, "%s", pQUEST->m_strTITLE.c_str() );
			m_list_Quest_Done.SetItemText(nNum,3,szTempChar);
			nNum++;
		}
	}
}
void CRanManagerCharQuest::OnBnClickedButtonRunDelete()
{
	if ( MessageBox ( "This Will Remove All The Selected Running Quests of the Character!, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		int nItem = 0; 
		for(nItem =0 ; nItem <  m_list_Quest_Run.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_Quest_Run.GetCheck(nItem);
			if( bChecked)
			{
				SNATIVEID	sTempID;
				sTempID.wMainID = atoi ( m_list_Quest_Run.GetItemText(nItem, 1).GetString() );
				sTempID.wSubID = atoi ( m_list_Quest_Run.GetItemText(nItem, 2).GetString() );
				m_cQuestPlay.DeleteProc(sTempID.dwID);
			}
		}
		ShowQuestsRun();
	}
}

void CRanManagerCharQuest::OnBnClickedButtonRunDeleteAll()
{
	if ( MessageBox ( "This Will Remove All The Running Quests of the Character!, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		GLQuestPlay::MAPQUEST& mapQuest = m_cQuestPlay.GetQuestProc ();
		GLQuestPlay::MAPQUEST_ITER iter = mapQuest.begin();
		GLQuestPlay::MAPQUEST_ITER iter_end = mapQuest.end();
		for ( ; iter!=iter_end; ++iter )
		{
			GLQUESTPROG *pPROG = (*iter).second;
			m_cQuestPlay.DeleteProc(pPROG->m_sNID.dwID);
		}
		ShowQuestsRun();
	}
}

void CRanManagerCharQuest::OnBnClickedButtonDoneDelete()
{
	if ( MessageBox ( "This Will Remove All The Selected Finished Quests of the Character!, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		int nItem = 0; 
		for(nItem =0 ; nItem <  m_list_Quest_Done.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_Quest_Done.GetCheck(nItem);
			if( bChecked)
			{
				SNATIVEID	sTempID;
				sTempID.wMainID = atoi ( m_list_Quest_Done.GetItemText(nItem, 1).GetString() );
				sTempID.wSubID = atoi (m_list_Quest_Done.GetItemText(nItem, 2).GetString() );
				m_cQuestPlay.DeleteEnd(sTempID.dwID);
			}
		}
		ShowQuestsDone();
	}
}

void CRanManagerCharQuest::OnBnClickedButtonDoneDeleteAll()
{
	if ( MessageBox ( "This Will Remove All The Finished Quests of the Character!, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		GLQuestPlay::MAPQUEST& mapQuest = m_cQuestPlay.GetQuestEnd ();
		GLQuestPlay::MAPQUEST_ITER iter = mapQuest.begin();
		GLQuestPlay::MAPQUEST_ITER iter_end = mapQuest.end();
		for ( ; iter!=iter_end; ++iter )
		{
			GLQUESTPROG *pPROG = (*iter).second;
			m_cQuestPlay.DeleteEnd(pPROG->m_sNID.dwID);
		}
		ShowQuestsDone();
	}
}

void CRanManagerCharQuest::OnBnClickedButtonQuestSave()
{
	CByteStream ByteStream;
	LPBYTE pBuffer = NULL;
	DWORD dwSize = 0;
	TCHAR szTemp[128] = {0};
	int nChaNum = GetWin_Num_int(this,IDC_EDIT_CHANUM);

	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	
	{
		MessageBox("Error Connecting to Game DB!","error",MB_OK);
		return;
	}
	
	ByteStream.ClearBuffer ();
	m_cQuestPlay.SET_BYBUFFER ( ByteStream );
	ByteStream.GetBuffer(pBuffer, dwSize);

	//write image
	if (pBuffer != NULL)
	{
		TCHAR szTemp[128] = {0};
		_snprintf( szTemp, 128, "UPDATE ChaInfo SET ChaQuest=? WHERE (ChaNum=%u)", (DWORD)nChaNum );

		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("CharQuest.txt","%s--%s",strTIME.c_str(),szTemp);

		sReturn = ::SQLPrepare(hStmt, (SQLCHAR*)szTemp, SQL_NTS);
		if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO) 
		{	
			MessageBox("Error Sql Prepare","error",MB_OK);
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return;
		}

		SQLINTEGER cbBinaryParam = SQL_LEN_DATA_AT_EXEC(0);

		sReturn = ::SQLBindParameter(hStmt, 
								1, 
								SQL_PARAM_INPUT,
								SQL_C_BINARY, 
								SQL_LONGVARBINARY,
								dwSize, 
								0, 
								(SQLPOINTER) 2, 
								0, 
								&cbBinaryParam);
		if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO) 
		{
			MessageBox("Error SQLBind","error",MB_OK);
			return;
		}

		sReturn = ::SQLExecute(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			MessageBox("Error Saving CharSkill Binary!","error",MB_OK);
			return;
		}
	
		SQLPOINTER pToken = NULL;
		while (sReturn == SQL_NEED_DATA) 
		{
			sReturn = ::SQLParamData(hStmt, &pToken);
			if (sReturn == SQL_NEED_DATA) 
			{				
				::SQLPutData(hStmt, pBuffer, (SQLINTEGER) dwSize);
			}
			Sleep( 0 );
		}	
	}

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	MessageBox("Done Saving CharQuests!","Info",MB_OK);

	pBuffer = NULL;
	ShowQuestsRun();
	ShowQuestsDone();
}

void CRanManagerCharQuest::OnBnClickedButtonQuestCancel()
{
	m_pToolTab->ActivePage(CHARPAGE_MAIN,0);
}
