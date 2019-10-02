// RanManagerCharSkill.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerCharSkill.h"
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
#include ".\ranmanagercharskill.h"
// CRanManagerCharSkill dialog

IMPLEMENT_DYNAMIC(CRanManagerCharSkill, CPropertyPage)
CRanManagerCharSkill::CRanManagerCharSkill(LOGFONT logfont)
	: CPropertyPage(CRanManagerCharSkill::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerCharSkill::~CRanManagerCharSkill()
{
}

void CRanManagerCharSkill::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SKILL, m_list_Skill );
	DDX_Control(pDX, IDC_LIST_SKILL_CHAR, m_list_SkillChar );
}


BEGIN_MESSAGE_MAP(CRanManagerCharSkill, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_DELETESKILL, OnBnClickedButtonDeleteskill)
	ON_BN_CLICKED(IDC_BUTTON_DELETESKILLALL, OnBnClickedButtonDeleteskillall)
	ON_BN_CLICKED(IDC_BUTTON_EDITSKILLLEVEL, OnBnClickedButtonEditskilllevel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_SKILL, OnBnClickedButtonSaveSkill)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_SKILL, OnBnClickedButtonCancelSkill)
	ON_BN_CLICKED(IDC_BUTTON_SK_SAVE, OnBnClickedButtonSkSave)
	ON_BN_CLICKED(IDC_BUTTON_INSERT_SKILL, OnBnClickedButtonInsertSkill)
	ON_BN_CLICKED(IDC_BUTTON_ALL_CLASS, OnBnClickedButtonAllClass)
	ON_BN_CLICKED(IDC_BUTTON_COMPATIBLE, OnBnClickedButtonCompatible)
END_MESSAGE_MAP()


// CRanManagerCharSkill message handlers
BOOL CRanManagerCharSkill::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_Skill.SetExtendedStyle ( m_list_Skill.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |LVS_EX_CHECKBOXES);
		m_list_Skill.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 5;	
		char* szColumnName1[nColumnCount] = { "#","MID", "SID" , "SkillName",""};
		int nColumnWidthPercent[nColumnCount] = { 15,15,15,50,5 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_Skill.InsertColumn (i, &lvColumn );
		}
	}

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_SkillChar.SetExtendedStyle ( m_list_SkillChar.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |LVS_EX_CHECKBOXES);
		m_list_SkillChar.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 6;	
		char* szColumnName1[nColumnCount] = { "#","MID", "SID" , "Level" , "SkillName",""};
		int nColumnWidthPercent[nColumnCount] = { 15,13,13,14,40,5 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_SkillChar.InsertColumn (i, &lvColumn );
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerCharSkill::SetChar(int nChar)
{
	LoadChar(nChar);
	LoadSkill(nChar);
}

void CRanManagerCharSkill::LoadGameSkill( EMCHARCLASS emClass ,bool bAll )
{
	int nNum = 0;
	char szTempChar[4096];
	m_list_Skill.DeleteAllItems();
	for ( WORD MID=0; MID<EMSKILLCLASS_NSIZE; ++MID )
	{
		for ( WORD SID=0; SID<GLSkillMan::MAX_CLASSSKILL; ++SID )
		{
			bool bFound = false;
			PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( MID, SID );
			if ( pSkill )
			{
				if (bAll)		
				{
					bFound = true;
				}
				else	
				{
					if ( (pSkill->m_sLEARN.dwCLASS&emClass) )	bFound = true;
				}
				if (bFound)
				{
					sprintf( szTempChar, "%d", nNum );
					m_list_Skill.InsertItem( nNum, szTempChar );

					sprintf( szTempChar, "%d", pSkill->m_sBASIC.sNATIVEID.wMainID );
					m_list_Skill.SetItemText(nNum,1,szTempChar);

					sprintf( szTempChar, "%d", pSkill->m_sBASIC.sNATIVEID.wSubID );
					m_list_Skill.SetItemText(nNum,2,szTempChar);

					sprintf( szTempChar, "%s", pSkill->GetName() );
					m_list_Skill.SetItemText(nNum,3,szTempChar);

					nNum++;
				}
			}
		}
	}

	SetWin_Num_int(this,IDC_EDIT_INSERT_LVL,1);
}

void CRanManagerCharSkill::LoadChar(int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT ChaNum,ChaName,ChaClass FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChar );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharSkill.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	return;

	SQLINTEGER nCharNum = 0, cbCharNum=SQL_NTS;
	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaName = SQL_NTS; 
	SQLINTEGER nCharClass = 0, cbCharClass=SQL_NTS;
	
	int nClass  = 0;
	EMCHARCLASS emClass;
	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{		
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nCharNum,       0, &cbCharNum);
            ::SQLGetData(hStmt, 2, SQL_C_CHAR, szChaName   ,  CHR_ID_LENGTH+1, &cbChaName); 
			::SQLGetData(hStmt, 3, SQL_C_LONG, &nCharClass,       0, &cbCharClass);
            
			SetWin_Num_int(this,IDC_EDIT_CHANUM,nCharNum);
			SetWin_Text(this,IDC_EDIT_CHANAME,(const char*) szChaName);
			emClass = EMCHARCLASS(nCharClass);
			SetWin_Num_int(this,IDC_EDIT_CHACLASS,emClass);
			SetWin_Text(this,IDC_EDIT_CHACLASSNAME, COMMENT::CHARCLASS[ CharClassToIndex(EMCHARCLASS(nCharClass) ) ].c_str() );
		}
		else
		{
			break;
		}
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	LoadGameSkill( emClass ,false);
}

void CRanManagerCharSkill::LoadSkill(int nChar)
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
	_snprintf( szTemp, 128, "SELECT ChaSkills FROM  %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaNum=%u"
		,CToolCfg::GetInstance()->szGameDb,nChar );
	
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharSkill.txt","%s--%s",strTIME.c_str(),szTemp);

	if ( sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO )
	{
		MessageBox("Error Reading Skills Binary","Error",MB_OK);
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

	DWORD dwVersion, dwSize, dwNum;
	ByteStream >> dwVersion;
	ByteStream >> dwSize;
	ByteStream >> dwNum;

	SCHARSKILL sCharSkill;
	m_ExpSkills.clear();
	for ( DWORD i=0; i<dwNum; i++ )
	{
		ByteStream.ReadBuffer ( (LPBYTE)&sCharSkill, sizeof(SCHARSKILL) );
		m_ExpSkills.insert ( std::make_pair(sCharSkill.sNativeID.dwID,sCharSkill) );
	}

	ShowSkills();
}

void CRanManagerCharSkill::ShowSkills()
{
	m_list_SkillChar.DeleteAllItems();

	char szTempChar[1024];
	int nNum = 0;
	SKILL_MAP_ITER iter = m_ExpSkills.begin();
	SKILL_MAP_ITER iter_end = m_ExpSkills.end();
	for ( ; iter!=iter_end; ++iter )
	{
		const SCHARSKILL &sSkill = (*iter).second;

		sprintf( szTempChar, "%d", nNum );
		m_list_SkillChar.InsertItem( nNum, szTempChar );

		sprintf( szTempChar, "%d", sSkill.sNativeID.wMainID );
		m_list_SkillChar.SetItemText(nNum,1,szTempChar);

		sprintf( szTempChar, "%d", sSkill.sNativeID.wSubID );
		m_list_SkillChar.SetItemText(nNum,2,szTempChar);

		sprintf( szTempChar, "%d", sSkill.wLevel );
		m_list_SkillChar.SetItemText(nNum,3,szTempChar);

		PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sSkill.sNativeID );
		if ( pSkill )
		{
			sprintf( szTempChar, "%s", pSkill->GetName() );
			m_list_SkillChar.SetItemText(nNum,4,szTempChar);
		}
		else
		{
			sprintf( szTempChar, "%s", "Unknown Skill" );
		}
		nNum++;
	}
}

void CRanManagerCharSkill::OnBnClickedButtonDeleteskill()
{
	if ( MessageBox ( "This Will Remove The Selected Skills!, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		int nItem = 0; 
		for(nItem =0 ; nItem <  m_list_SkillChar.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_SkillChar.GetCheck(nItem);
			if( bChecked)
			{
				SNATIVEID	wTempID;
				wTempID.wMainID = atoi ( m_list_SkillChar.GetItemText(nItem, 1).GetString() );
				wTempID.wSubID = atoi ( m_list_SkillChar.GetItemText(nItem, 2).GetString() );
				SKILL_MAP_ITER iter_del = m_ExpSkills.find ( wTempID.dwID );
				if ( iter_del!=m_ExpSkills.end() )	m_ExpSkills.erase ( iter_del );
			}
		}
		ShowSkills();
	}
}

void CRanManagerCharSkill::OnBnClickedButtonDeleteskillall()
{
	if ( MessageBox ( "This Will Remove All The Skill of the Selected Character!, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		m_ExpSkills.clear();
		ShowSkills();
	}
}

void CRanManagerCharSkill::OnBnClickedButtonEditskilllevel()
{
	int nSelect = m_list_SkillChar.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;
	int MID = atoi ( m_list_SkillChar.GetItemText(nSelect,1).GetString() );
	int SID = atoi ( m_list_SkillChar.GetItemText(nSelect,2).GetString() );
	int nLEVEL = atoi ( m_list_SkillChar.GetItemText(nSelect,3).GetString() );
	SetWin_Num_int(this,IDC_EDIT_SK_MID,MID);
	SetWin_Num_int(this,IDC_EDIT_SK_SID,SID);
	SetWin_Num_int(this,IDC_EDIT_SK_LVL,nLEVEL);

	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( MID,SID );
	if ( pSkill )	SetWin_Text(this,IDC_EDIT_SK_NAME,pSkill->GetName());
	else	SetWin_Text(this,IDC_EDIT_SK_NAME,"Unknown Skill");
}

void CRanManagerCharSkill::OnBnClickedButtonSaveSkill()
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

	ByteStream << SCHARSKILL::VERSION;
	ByteStream << SCHARSKILL::SIZE;
	DWORD dwSize2 = (DWORD) m_ExpSkills.size();
	ByteStream << dwSize2;

	SKILL_MAP_CITER iter = m_ExpSkills.begin ();
	SKILL_MAP_CITER iter_end = m_ExpSkills.end ();
	for ( ; iter!=iter_end; ++iter )
	{
		const SCHARSKILL &sSkill = (*iter).second;
		ByteStream.WriteBuffer ( &sSkill, (DWORD)sizeof(SCHARSKILL) );
	}

	ByteStream.GetBuffer(pBuffer, dwSize);

	//write image
	if (pBuffer != NULL)
	{
		TCHAR szTemp[128] = {0};
		_snprintf( szTemp, 128, "UPDATE ChaInfo SET ChaSkills=? WHERE (ChaNum=%u)", (DWORD)nChaNum );

		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("CharSkill.txt","%s--%s",strTIME.c_str(),szTemp);

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
	MessageBox("Done Saving CharSkills!","Info",MB_OK);

	pBuffer = NULL;
	ShowSkills();
}

void CRanManagerCharSkill::OnBnClickedButtonCancelSkill()
{
	m_pToolTab->ActivePage(CHARPAGE_MAIN,0);
}

void CRanManagerCharSkill::OnBnClickedButtonSkSave()
{
	int nSkillLevel =  GetWin_Num_int(this,IDC_EDIT_SK_LVL);
	if  (nSkillLevel < 1 || nSkillLevel > 8 )
	{
		MessageBox("Wrong Skill Level 1~8 Only! ReCheck Level Value!","Error",MB_OK);
		return;
	}

	SNATIVEID	wTempID;
	wTempID.wMainID = GetWin_Num_int(this,IDC_EDIT_SK_MID);
	wTempID.wSubID =  GetWin_Num_int(this,IDC_EDIT_SK_SID);
	SKILL_MAP_ITER iter_del = m_ExpSkills.find ( wTempID.dwID );
	if ( iter_del!=m_ExpSkills.end() )	m_ExpSkills.erase ( iter_del );

	SCHARSKILL sCharSkill;
	sCharSkill.sNativeID.wMainID = GetWin_Num_int(this,IDC_EDIT_SK_MID);
	sCharSkill.sNativeID.wSubID = GetWin_Num_int(this,IDC_EDIT_SK_SID);
	sCharSkill.wLevel = nSkillLevel;
	m_ExpSkills.insert ( std::make_pair(sCharSkill.sNativeID.dwID,sCharSkill) );
	ShowSkills();
}

void CRanManagerCharSkill::OnBnClickedButtonInsertSkill()
{
	int nSkillLevel =  GetWin_Num_int(this,IDC_EDIT_INSERT_LVL);
	if  (nSkillLevel < 1 || nSkillLevel > 8 )
	{
		MessageBox("Wrong Skill Level 1~8 Only! ReCheck Level Value!","Error",MB_OK);
		return;
	}

	int nItem = 0; 
	for(nItem =0 ; nItem <  m_list_Skill.GetItemCount(); nItem++)
	{
		BOOL bChecked = m_list_Skill.GetCheck(nItem);
		if( bChecked)
		{
			SNATIVEID	wTempID;
			wTempID.wMainID = atoi ( m_list_Skill.GetItemText(nItem, 1).GetString() );
			wTempID.wSubID = atoi ( m_list_Skill.GetItemText(nItem, 2).GetString() );
			SKILL_MAP_ITER iter_del = m_ExpSkills.find ( wTempID.dwID );
			if ( iter_del!=m_ExpSkills.end() )	m_ExpSkills.erase ( iter_del );

			SCHARSKILL sCharSkill;
			sCharSkill.sNativeID.wMainID = wTempID.wMainID;
			sCharSkill.sNativeID.wSubID = wTempID.wSubID;
			sCharSkill.wLevel = nSkillLevel;
			m_ExpSkills.insert ( std::make_pair(sCharSkill.sNativeID.dwID,sCharSkill) );
		}
	}
		ShowSkills();
}

void CRanManagerCharSkill::OnBnClickedButtonAllClass()
{
	LoadGameSkill( GLCC_NONE ,true);
}

void CRanManagerCharSkill::OnBnClickedButtonCompatible()
{
	int nClass = GetWin_Num_int(this,IDC_EDIT_CHACLASS);
	LoadGameSkill( (EMCHARCLASS)nClass ,false);
}
