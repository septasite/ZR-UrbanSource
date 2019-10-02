// RanManagerPet.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerPet.h"
#include "RanManagerPetTab.h"
#include "RanManagerDlg.h"
#include "RanManagerTab.h"
#include "EtcFunction.h"
#include "RanManagerComments.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "s_NetGlobal.h"
#include ".\ranmanagerpet.h"

// CRanManagerPet dialog

IMPLEMENT_DYNAMIC(CRanManagerPet, CPropertyPage)
CRanManagerPet::CRanManagerPet(LOGFONT logfont)
	: CPropertyPage(CRanManagerPet::IDD)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	nPetNum = 0;
	strPet = "";
}

CRanManagerPet::~CRanManagerPet()
{
}

void CRanManagerPet::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PET, m_list_Pet );
	DDX_Control(pDX, IDC_COMBO_PETSEARCHTYPE, m_cSearchType );
	DDX_Control(pDX, IDC_COMBO_PETTYPE, m_cPetPage );
}


BEGIN_MESSAGE_MAP(CRanManagerPet, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_PETSEARCHTYPE, OnCbnSelchangeComboPetsearchtype)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_PET_SELECT, OnBnClickedButtonPetSelect)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PET, OnNMDblclkListPet)
END_MESSAGE_MAP()


// CRanManagerPet message handlers
BOOL CRanManagerPet::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	CRect SheetRect;
	CWnd *pWnd;
	pWnd = GetDlgItem ( IDC_STATIC_PET );
	pWnd->GetWindowRect ( SheetRect );
	ScreenToClient ( &SheetRect );
	LOGFONT logfont = {0};
	CFont* pFont = GetFont();
	if ( pFont ) pFont->GetLogFont( &logfont );
	m_pPetTab = new CRanManagerPetTab ( SheetRect, logfont, this );
	m_pPetTab->Create( this, WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0 );
	m_pPetTab->ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	m_pPetTab->SetActivePage ( PETPAGE_MAIN );

	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	m_list_Pet.SetExtendedStyle ( m_list_Pet.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_list_Pet.GetClientRect ( &rectCtrl );
	lnWidth = rectCtrl.right - rectCtrl.left;

	const int nColumnCount = 7;	
	char* szColumnName1[nColumnCount] = { "#","Num", "Name" , "OwnerNum", "OwnerName", "Type", "Deleted"};
	int nColumnWidthPercent[nColumnCount] = { 10,11,22,13,18,14,12 };

	for ( int i = 0; i < nColumnCount; i++ )
	{		
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.pszText = szColumnName1[i];
		lvColumn.iSubItem = i;
		lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
		m_list_Pet.InsertColumn (i, &lvColumn );
	}

	for ( int i = 0; i < SEARCH_VEHICLESIZE; ++i )
	{
		m_cSearchType.InsertString( i, RMComments::m_SearchPetType[i].c_str() );
	}
	
	m_cSearchType.SetCurSel( 0 );

	OnCbnSelchangeComboPetsearchtype();

	for ( int i = 0; i < PETPAGE_SIZE; ++i )
	{
		m_cPetPage.InsertString( i, RMComments::m_PagePet[i].c_str() );
	}
	m_cPetPage.SetCurSel( 0 );

	SetWin_ShowWindow( this ,IDC_COMBO_PETTYPE, FALSE );
	SetWin_ShowWindow( this ,IDC_BUTTON_PET_SELECT, FALSE );
	SetWin_ShowWindow( this ,IDC_EDIT_PETTYPE, FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
}
void CRanManagerPet::OnCbnSelchangeComboPetsearchtype()
{
	int nSelect = m_cSearchType.GetCurSel();
	if ( nSelect == SEARCH_PETALL || nSelect == SEARCH_PETDELETED ) SetWin_Enable(this,IDC_EDIT_SEARCH,false);
	else	 SetWin_Enable(this,IDC_EDIT_SEARCH,true);
}

void CRanManagerPet::OnBnClickedButtonSearch()
{
	int nSelect = m_cSearchType.GetCurSel();
	int nFind = GetWin_Num_int(this,IDC_EDIT_SEARCH);
	std::string strSearch = GetWin_Text(this,IDC_EDIT_SEARCH);
	TCHAR szTemp[256] = {0};
	std::string strSign = "%";
	switch (nSelect)
	{
	case SEARCH_PETALL:
		{
			_snprintf( szTemp, 256, "SELECT PetNum,PetName,PetChaNum,PetType,PetDeleted FROM %s.dbo.PetInfo WITH (NOLOCK) "
			"ORDER BY PetNum",CToolCfg::GetInstance()->szGameDb);
		}break;
	case SEARCH_PETNUM:
		{
			_snprintf( szTemp, 256, "SELECT PetNum,PetName,PetChaNum,PetType,PetDeleted FROM %s.dbo.PetInfo WITH (NOLOCK) WHERE PetNum LIKE '%s%d%s' "
			"ORDER BY PetNum",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),nFind,strSign.c_str() );
		}break;
	case SEARCH_PETOWNERNAME:
		{
			GetSearchNum( strSearch.c_str() );
		}break;
	case SEARCH_PETOWNERNUM:
		{
			_snprintf( szTemp, 256, "SELECT PetNum,PetName,PetChaNum,PetType,PetDeleted FROM %s.dbo.PetInfo WITH (NOLOCK) WHERE PetChaNum LIKE '%s%d%s' "
			"ORDER BY PetNum",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),nFind,strSign.c_str() );
		}break;
	case SEARCH_PETDELETED:
		{
			_snprintf( szTemp, 256, "SELECT PetNum,PetName,PetChaNum,PetType,PetDeleted FROM %s.dbo.PetInfo WITH (NOLOCK) WHERE PetDeleted=1 "
			"ORDER BY PetNum",CToolCfg::GetInstance()->szGameDb );
		}break;
	};


	switch (nSelect)
	{
	case SEARCH_PETALL:
	case SEARCH_PETNUM:
	case SEARCH_PETOWNERNUM:
	case SEARCH_PETDELETED:
		{
			SQLRETURN	sReturn = 0; // SQL return value (short)	
			SQLHSTMT	hStmt; // Handle of statement (void*)

			sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
			if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
			{
				return;
			}

			std::string strTIME = CDebugSet::GetCurTime ();
			LOGSCRIPT::LogToFile("Pet.txt","%s--%s",strTIME.c_str(),szTemp);

			sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);

			if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
			{
				::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				return;
			}

			SQLINTEGER nPetNum = 0, cbPetNum = SQL_NTS; 
			SQLCHAR    szPetName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbPetName = SQL_NTS;
			SQLINTEGER nPetChaNum = 0, cbPetChaNum = SQL_NTS; 
			SQLINTEGER nPetType = 0, cbPetType = SQL_NTS; 
			SQLINTEGER nPetDeleted = 0, cbPetDeleted = SQL_NTS; 

			int nNum = 0;
			char szTempChar[256];
			m_list_Pet.DeleteAllItems();
			while (true)
			{
				sReturn = ::SQLFetch(hStmt);
				if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
				if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
				{
					::SQLGetData(hStmt, 1, SQL_C_LONG, &nPetNum, 0, &cbPetNum );
					::SQLGetData(hStmt, 2, SQL_C_CHAR, szPetName, CHR_ID_LENGTH, &cbPetName);
					::SQLGetData(hStmt, 3, SQL_C_LONG, &nPetChaNum, 0, &cbPetChaNum );
					::SQLGetData(hStmt, 4, SQL_C_LONG, &nPetType, 0, &cbPetType );
					::SQLGetData(hStmt, 5, SQL_C_LONG, &nPetDeleted, 0, &cbPetDeleted );
			
					sprintf( szTempChar, "%d", nNum );
					m_list_Pet.InsertItem( nNum, szTempChar );

					sprintf( szTempChar, "%d", nPetNum );
					m_list_Pet.SetItemText(nNum,1,szTempChar);

					sprintf( szTempChar, "%s", szPetName );
					m_list_Pet.SetItemText(nNum,2,szTempChar);

					sprintf( szTempChar, "%d", nPetChaNum );
					m_list_Pet.SetItemText(nNum,3,szTempChar);

					sprintf( szTempChar, "%s", COMMENT::PET_TYPE[nPetType].c_str() );
					m_list_Pet.SetItemText(nNum,5,szTempChar);

					if (nPetDeleted == 1 ) sprintf( szTempChar, "%s(%d)","Deleted",nPetDeleted );
					else	sprintf( szTempChar, "%s(%d)","Active",nPetDeleted );
					m_list_Pet.SetItemText(nNum,6,szTempChar);

					nNum++;	}
				else	break;
				Sleep( 0 );
			}
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			GetOWnerNames();
		}break;

	case SEARCH_PETOWNERNAME:
		{
			VEC_SEARCH_NUM_ITER iter = m_VecSearchNum.begin();
			VEC_SEARCH_NUM_ITER iter_end = m_VecSearchNum.end();

			m_list_Pet.DeleteAllItems();
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

				_snprintf( szTemp, 256, "SELECT PetNum,PetName,PetChaNum,PetType,PetDeleted FROM %s.dbo.PetInfo WITH (NOLOCK) WHERE PetChaNum =%d "
				"ORDER BY PetNum",CToolCfg::GetInstance()->szGameDb,int (*iter) );

				std::string strTIME = CDebugSet::GetCurTime ();
				LOGSCRIPT::LogToFile("Pet.txt","%s--%s",strTIME.c_str(),szTemp);

				sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);

				if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
				{
					::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
					return;
				}

				SQLINTEGER nPetNum = 0, cbPetNum = SQL_NTS; 
				SQLCHAR    szPetName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbPetName = SQL_NTS;
				SQLINTEGER nPetChaNum = 0, cbPetChaNum = SQL_NTS; 
				SQLINTEGER nPetType = 0, cbPetType = SQL_NTS; 
				SQLINTEGER nPetDeleted = 0, cbPetDeleted = SQL_NTS; 

				while (true)
				{
					sReturn = ::SQLFetch(hStmt);
					if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
					if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
					{
						::SQLGetData(hStmt, 1, SQL_C_LONG, &nPetNum, 0, &cbPetNum );
						::SQLGetData(hStmt, 2, SQL_C_CHAR, szPetName, CHR_ID_LENGTH, &cbPetName);
						::SQLGetData(hStmt, 3, SQL_C_LONG, &nPetChaNum, 0, &cbPetChaNum );
						::SQLGetData(hStmt, 4, SQL_C_LONG, &nPetType, 0, &cbPetType );
						::SQLGetData(hStmt, 5, SQL_C_LONG, &nPetDeleted, 0, &cbPetDeleted );
			
						sprintf( szTempChar, "%d", nNum );
						m_list_Pet.InsertItem( nNum, szTempChar );

						sprintf( szTempChar, "%d", nPetNum );
						m_list_Pet.SetItemText(nNum,1,szTempChar);

						sprintf( szTempChar, "%s", szPetName );
						m_list_Pet.SetItemText(nNum,2,szTempChar);

						sprintf( szTempChar, "%d", nPetChaNum );
						m_list_Pet.SetItemText(nNum,3,szTempChar);

						sprintf( szTempChar, "%s", COMMENT::PET_TYPE[nPetType].c_str() );
						m_list_Pet.SetItemText(nNum,5,szTempChar);

						if (nPetDeleted == 1 ) sprintf( szTempChar, "%s(%d)","Deleted",nPetDeleted );
						else	sprintf( szTempChar, "%s(%d)","Active",nPetDeleted );
						m_list_Pet.SetItemText(nNum,6,szTempChar);

						nNum++;	
					}
					else	break;
					Sleep( 0 );
				}
				::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			}
			GetOWnerNames();
		}break;
	};
}

void CRanManagerPet::GetOWnerNames()
{
	int nItem = 0; 
	for(nItem =0 ; nItem < m_list_Pet.GetItemCount(); nItem++)
	{
		SQLRETURN	sReturn = 0; // SQL return value (short)	
		SQLHSTMT	hStmt; // Handle of statement (void*)

		int nChaNum =  atoi ( m_list_Pet.GetItemText(nItem, 3).GetString() );

		sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
		if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	continue;

		TCHAR szTemp[1024] = {0};
		_snprintf( szTemp, 256, "SELECT ChaName FROM %s.dbo.ChaInfo WHERE ChaNum = %d "
		"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nChaNum);
		
		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("Pet.txt","%s--%s",strTIME.c_str(),szTemp);

		sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

		if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
		{
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return;
		}

		SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaName = SQL_NTS;

		int nNum = 0;
		char szTempChar[256];
		while (true)
		{
			sReturn = ::SQLFetch(hStmt);
			if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
			if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)	
			{
				::SQLGetData(hStmt, 1, SQL_C_CHAR, szChaName, CHR_ID_LENGTH, &cbChaName);
			}
			else	break;
			Sleep( 0 );
		}
		sprintf( szTempChar, "%s",szChaName);
		m_list_Pet.SetItemText(nItem,4,szTempChar);
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}		
}

void CRanManagerPet::GetSearchNum(std::string strSearch)
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
	LOGSCRIPT::LogToFile("Pet.txt","%s--%s",strTIME.c_str(),szTemp);

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

void CRanManagerPet::OnBnClickedButtonPetSelect()
{
	int nSelect = m_cPetPage.GetCurSel();
	SetWin_Text(this,IDC_EDIT_PETTYPE,RMComments::m_PagePet[nSelect].c_str() );
	switch (nSelect)
	{
	case PETPAGE_MAIN:	m_pPetTab->ActivePage ( PETPAGE_MAIN ,nPetNum );	break;
	case PETPAGE_EDIT:	m_pPetTab->ActivePage ( PETPAGE_EDIT ,nPetNum );	break;
	case PETPAGE_INVEN:	m_pPetTab->ActivePage ( PETPAGE_INVEN ,nPetNum );	break;
	case PETPAGE_SKILL:	m_pPetTab->ActivePage ( PETPAGE_SKILL ,nPetNum );	break;
	case PETPAGE_SKILLSLOT:	m_pPetTab->ActivePage ( PETPAGE_SKILLSLOT ,nPetNum );	break;
	};
}

void CRanManagerPet::OnNMDblclkListPet(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nSelect = m_list_Pet.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;
	nPetNum = atoi ( m_list_Pet.GetItemText(nSelect,1).GetString() );
	strPet = m_list_Pet.GetItemText(nSelect,2).GetString();

	SetWin_ShowWindow( this ,IDC_COMBO_PETTYPE, TRUE );
	SetWin_ShowWindow( this ,IDC_BUTTON_PET_SELECT, TRUE );
	SetWin_ShowWindow( this ,IDC_EDIT_PETTYPE, TRUE );

	SetWin_Num_int ( this, IDC_EDIT_SELECTED_NUM,nPetNum );
	SetWin_Text ( this, IDC_EDIT_SELECTED_NAME, strPet.GetString() );

	m_pPetTab->ActivePage(PETPAGE_EDIT,nPetNum);
	m_cPetPage.SetCurSel(PETPAGE_EDIT);
	SetWin_Text(this,IDC_EDIT_PETTYPE,RMComments::m_PagePet[PETPAGE_EDIT].c_str() );
}
