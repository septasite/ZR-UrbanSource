// RanManagerCharPet.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerCharPet.h"
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
#include ".\ranmanagercharpet.h"



// CRanManagerCharPet dialog

IMPLEMENT_DYNAMIC(CRanManagerCharPet, CPropertyPage)
CRanManagerCharPet::CRanManagerCharPet(LOGFONT logfont)
	: CPropertyPage(CRanManagerCharPet::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerCharPet::~CRanManagerCharPet()
{
}

void CRanManagerCharPet::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PET, m_list_Pet );
}


BEGIN_MESSAGE_MAP(CRanManagerCharPet, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_DELETE2, OnBnClickedButtonDelete2)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL2, OnBnClickedButtonDeleteAll2)
	ON_BN_CLICKED(IDC_BUTTON_CHARPET_CANCEL, OnBnClickedButtonCharpetCancel)
END_MESSAGE_MAP()


// CRanManagerCharPet message handlers
BOOL CRanManagerCharPet::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	m_list_Pet.SetExtendedStyle (m_list_Pet.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |LVS_EX_CHECKBOXES);
	m_list_Pet.GetClientRect ( &rectCtrl );
	lnWidth = rectCtrl.right - rectCtrl.left;

	const int nColumnCount = 9;	
	char* szColumnName1[nColumnCount] = { "#","Number", "MID", "SID" , "Name" , "Type" , "Deleted","Food",""};
	int nColumnWidthPercent[nColumnCount] = { 9,9,7,7,28,19,9,7,5 };

	for ( int i = 0; i < nColumnCount; i++ )
	{		
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.pszText = szColumnName1[i];
		lvColumn.iSubItem = i;
		lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
		m_list_Pet.InsertColumn (i, &lvColumn );
	}

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerCharPet::SetChar(int nChar)
{
	LoadChar(nChar);
	LoadPet(nChar);
}

void CRanManagerCharPet::LoadChar(int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT ChaNum,ChaName FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChar );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharPet.txt","%s--%s",strTIME.c_str(),szTemp);

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

void CRanManagerCharPet::LoadPet(int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT PetNum,PetMID,PetSID,PetName,PetType,PetDeleted,PetFull "
		"FROM %s.dbo.PetInfo WHERE PetChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChar );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharPet.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	return;

	SQLINTEGER nPetNum = 0, cbPetNum=SQL_NTS;
	SQLINTEGER nPetMID = 0, cbPetMID=SQL_NTS;
	SQLINTEGER nPetSID = 0, cbPetSID=SQL_NTS;
	SQLCHAR    szPetName[CHR_ID_LENGTH+10] = {0}; SQLINTEGER cbPetName = SQL_NTS; 
	SQLINTEGER nPetType = 0, cbPetType=SQL_NTS;
	SQLINTEGER nPetDeleted = 0, cbPetDeleted=SQL_NTS;
	SQLINTEGER nPetFull = 0, cbPetFull=SQL_NTS;
	
	int nNum = 0;
	char szTempChar[256];
	m_list_Pet.DeleteAllItems();
	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{		
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nPetNum,       0, &cbPetNum );
			::SQLGetData(hStmt, 2, SQL_C_LONG, &nPetMID,       0, &cbPetMID );
			::SQLGetData(hStmt, 3, SQL_C_LONG, &nPetSID,       0, &cbPetSID );
			::SQLGetData(hStmt, 4, SQL_C_CHAR, szPetName   ,  CHR_ID_LENGTH+10, &cbPetName ); 
			::SQLGetData(hStmt, 5, SQL_C_LONG, &nPetType,       0, &cbPetType );
			::SQLGetData(hStmt, 6, SQL_C_LONG, &nPetDeleted,       0, &cbPetDeleted );
			::SQLGetData(hStmt, 7, SQL_C_LONG, &nPetFull,       0, &cbPetFull );
           
			sprintf( szTempChar, "%d", nNum );
			m_list_Pet.InsertItem( nNum, szTempChar );

			sprintf( szTempChar, "%d", nPetNum );
			m_list_Pet.SetItemText(nNum,1,szTempChar);

			sprintf( szTempChar, "%d", nPetMID );
			m_list_Pet.SetItemText(nNum,2,szTempChar);

			sprintf( szTempChar, "%d", nPetSID );
			m_list_Pet.SetItemText(nNum,3,szTempChar);

			sprintf( szTempChar, "%s", szPetName );
			m_list_Pet.SetItemText(nNum,4,szTempChar);

			sprintf( szTempChar, "%s", COMMENT::PET_TYPE[nPetType].c_str() );
			m_list_Pet.SetItemText(nNum,5,szTempChar);

			if (nPetDeleted == 1)	sprintf( szTempChar, "%s", "Deleted" );
			else		sprintf( szTempChar, "%s", "Usable" );
			m_list_Pet.SetItemText(nNum,6,szTempChar);

			sprintf( szTempChar, "%d", nPetFull );
			m_list_Pet.SetItemText(nNum,7,szTempChar);

			nNum++;
		}
		else
		{
			break;
		}
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}
void CRanManagerCharPet::OnBnClickedButtonDelete2()
{
	if ( MessageBox("This Will Delete the Selected Pets! Continue?\nThis is Permanent Delete!","Question",MB_YESNO) == IDYES )
	{
		int nItem = 0; 
		int nChar = GetWin_Num_int(this,IDC_EDIT_CHANUM);
		for(nItem =0 ; nItem <  m_list_Pet.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_Pet.GetCheck(nItem);
			if( bChecked)
			{
				SQLRETURN	sReturn = 0; // SQL return value (short)	
				SQLHSTMT	hStmt; // Handle of statement (void*)
				int nPetNum = atoi ( m_list_Pet.GetItemText(nItem, 1).GetString() );

				sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
				if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	continue;

				TCHAR szTemp[1024] = {0};
				
				_snprintf( szTemp, 1024, 
					"Delete From %s.dbo.PetInfo "
					" Where PetChaNum =%d AND PetNum =%d"
				,CToolCfg::GetInstance()->szGameDb
				,nChar
				,nPetNum
				);

				sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
				std::string strTIME = CDebugSet::GetCurTime ();
				LOGSCRIPT::LogToFile("CharPet.txt","%s--%s",strTIME.c_str(),szTemp);

				if (sReturn == SQL_ERROR )	
				{
					MessageBox("Error! Cant Delete Pets","Ran Manager",MB_OK);
					::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
					continue;
				}
			}
		}
		LoadPet(nChar);
	}
}

void CRanManagerCharPet::OnBnClickedButtonDeleteAll2()
{
	if ( MessageBox("Are you sure you want to Clear All The Saved Pets of this Character?\nThis is Permanent Delete!","Question",MB_YESNO) == IDYES )
	{
		SQLRETURN	sReturn = 0; // SQL return value (short)	
		SQLHSTMT	hStmt; // Handle of statement (void*)
		int nChar = GetWin_Num_int(this,IDC_EDIT_CHANUM);

		sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
		if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

		TCHAR szTemp[1024] = {0};
		
		_snprintf( szTemp, 1024, 
			"Delete From %s.dbo.PetInfo "
			" Where PetChaNum =%d"
		,CToolCfg::GetInstance()->szGameDb
		,nChar
		);

		sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("CharPet.txt","%s--%s",strTIME.c_str(),szTemp);

		if (sReturn == SQL_ERROR )	
		{
			MessageBox("Error! Cant Delete Pets","Ran Manager",MB_OK);
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
		}
		LoadPet(nChar);
	}
}

void CRanManagerCharPet::OnBnClickedButtonCharpetCancel()
{
	m_pToolTab->ActivePage(CHARPAGE_MAIN,0);
}
