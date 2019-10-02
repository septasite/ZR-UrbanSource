// RanManagerVehicle.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerVehicle.h"

#include "RanManagerVehicleTab.h"
#include "RanManagerDlg.h"
#include "RanManagerTab.h"
#include "EtcFunction.h"
#include "RanManagerComments.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "s_NetGlobal.h"
#include ".\ranmanagervehicle.h"


// CRanManagerVehicle dialog

IMPLEMENT_DYNAMIC(CRanManagerVehicle, CPropertyPage)
CRanManagerVehicle::CRanManagerVehicle(LOGFONT logfont)
	: CPropertyPage(CRanManagerVehicle::IDD)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	nVehicleNum = 0;
	strVehicle = "";
}

CRanManagerVehicle::~CRanManagerVehicle()
{
}

void CRanManagerVehicle::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VEHICLE, m_list_Vehicle );
	DDX_Control(pDX, IDC_COMBO_VEHICLESEARCHTYPE, m_cSearchType );
	DDX_Control(pDX, IDC_COMBO_VEHICLETYPE, m_cVehiclePage );
}


BEGIN_MESSAGE_MAP(CRanManagerVehicle, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_VEHICLESEARCHTYPE, OnCbnSelchangeComboVehiclesearchtype)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VEHICLE, OnNMDblclkListVehicle)
	ON_BN_CLICKED(IDC_BUTTON_VEHICLE_SELECT, OnBnClickedButtonVehicleSelect)
END_MESSAGE_MAP()


// CRanManagerVehicle message handlers
BOOL CRanManagerVehicle::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	CRect SheetRect;
	CWnd *pWnd;
	pWnd = GetDlgItem ( IDC_STATIC_VEHICLE );
	pWnd->GetWindowRect ( SheetRect );
	ScreenToClient ( &SheetRect );
	LOGFONT logfont = {0};
	CFont* pFont = GetFont();
	if ( pFont ) pFont->GetLogFont( &logfont );
	m_pVehicleTab = new CRanManagerVehicleTab ( SheetRect, logfont, this );
	m_pVehicleTab->Create( this, WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0 );
	m_pVehicleTab->ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	m_pVehicleTab->SetActivePage ( VEHICLEPAGE_MAIN );

	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	m_list_Vehicle.SetExtendedStyle ( m_list_Vehicle.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_list_Vehicle.GetClientRect ( &rectCtrl );
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
		m_list_Vehicle.InsertColumn (i, &lvColumn );
	}

	for ( int i = 0; i < SEARCH_VEHICLESIZE; ++i )
	{
		m_cSearchType.InsertString( i, RMComments::m_SearchVehicleType[i].c_str() );
	}
	
	m_cSearchType.SetCurSel( 0 );

	OnCbnSelchangeComboVehiclesearchtype();

	for ( int i = 0; i < VEHICLEPAGE_SIZE; ++i )
	{
		m_cVehiclePage.InsertString( i, RMComments::m_PageVehicle[i].c_str() );
	}
	m_cVehiclePage.SetCurSel( 0 );

	SetWin_ShowWindow( this ,IDC_COMBO_VEHICLETYPE, FALSE );
	SetWin_ShowWindow( this ,IDC_BUTTON_VEHICLE_SELECT, FALSE );
	SetWin_ShowWindow( this ,IDC_EDIT_VEHICLETYPE, FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CRanManagerVehicle::OnBnClickedButtonSearch()
{
	int nSelect = m_cSearchType.GetCurSel();
	int nFind = GetWin_Num_int(this,IDC_EDIT_SEARCH);
	std::string strSearch = GetWin_Text(this,IDC_EDIT_SEARCH);
	TCHAR szTemp[256] = {0};
	std::string strSign = "%";
	switch (nSelect)
	{
	case SEARCH_VEHICLEALL:
		{
			_snprintf( szTemp, 256, "SELECT VehicleNum,VehicleName,VehicleChaNum,VehicleType,VehicleDeleted FROM %s.dbo.VehicleInfo WITH (NOLOCK) "
			"ORDER BY VehicleNum",CToolCfg::GetInstance()->szGameDb);
		}break;
	case SEARCH_VEHICLENUM:
		{
			_snprintf( szTemp, 256, "SELECT VehicleNum,VehicleName,VehicleChaNum,VehicleType,VehicleDeleted FROM %s.dbo.VehicleInfo WITH (NOLOCK) WHERE VehicleNum LIKE '%s%d%s' "
			"ORDER BY VehicleNum",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),nFind,strSign.c_str() );
		}break;
	case SEARCH_VEHICLEOWNERNAME:
		{
			GetSearchNum( strSearch.c_str() );
		}break;
	case SEARCH_VEHICLEOWNERNUM:
		{
			_snprintf( szTemp, 256, "SELECT VehicleNum,VehicleName,VehicleChaNum,VehicleType,VehicleDeleted FROM %s.dbo.VehicleInfo WITH (NOLOCK) WHERE VehicleChaNum LIKE '%s%d%s' "
			"ORDER BY VehicleNum",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),nFind,strSign.c_str() );
		}break;
	case SEARCH_VEHICLEDELETED:
		{
			_snprintf( szTemp, 256, "SELECT VehicleNum,VehicleName,VehicleChaNum,VehicleType,VehicleDeleted FROM %s.dbo.VehicleInfo WITH (NOLOCK) WHERE VehicleDeleted=1 "
			"ORDER BY VehicleNum",CToolCfg::GetInstance()->szGameDb );
		}break;
	};


	switch (nSelect)
	{
	case SEARCH_VEHICLEALL:
	case SEARCH_VEHICLENUM:
	case SEARCH_VEHICLEOWNERNUM:
	case SEARCH_VEHICLEDELETED:
		{
			SQLRETURN	sReturn = 0; // SQL return value (short)	
			SQLHSTMT	hStmt; // Handle of statement (void*)

			sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
			if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
			{
				return;
			}

			std::string strTIME = CDebugSet::GetCurTime ();
			LOGSCRIPT::LogToFile("Vehicle.txt","%s--%s",strTIME.c_str(),szTemp);

			sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);

			if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
			{
				::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				return;
			}

			SQLINTEGER nVehicleNum = 0, cbVehicleNum = SQL_NTS; 
			SQLCHAR    szVehicleName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbVehicleName = SQL_NTS;
			SQLINTEGER nVehicleChaNum = 0, cbVehicleChaNum = SQL_NTS; 
			SQLINTEGER nVehicleType = 0, cbVehicleType = SQL_NTS; 
			SQLINTEGER nVehicleDeleted = 0, cbVehicleDeleted = SQL_NTS; 

			int nNum = 0;
			char szTempChar[256];
			m_list_Vehicle.DeleteAllItems();
			while (true)
			{
				sReturn = ::SQLFetch(hStmt);
				if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
				if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
				{
					::SQLGetData(hStmt, 1, SQL_C_LONG, &nVehicleNum, 0, &cbVehicleNum );
					::SQLGetData(hStmt, 2, SQL_C_CHAR, szVehicleName, CHR_ID_LENGTH, &cbVehicleName);
					::SQLGetData(hStmt, 3, SQL_C_LONG, &nVehicleChaNum, 0, &cbVehicleChaNum );
					::SQLGetData(hStmt, 4, SQL_C_LONG, &nVehicleType, 0, &cbVehicleType );
					::SQLGetData(hStmt, 5, SQL_C_LONG, &nVehicleDeleted, 0, &cbVehicleDeleted );
			
					sprintf( szTempChar, "%d", nNum );
					m_list_Vehicle.InsertItem( nNum, szTempChar );

					sprintf( szTempChar, "%d", nVehicleNum );
					m_list_Vehicle.SetItemText(nNum,1,szTempChar);

					sprintf( szTempChar, "%s", szVehicleName );
					m_list_Vehicle.SetItemText(nNum,2,szTempChar);

					sprintf( szTempChar, "%d", nVehicleChaNum );
					m_list_Vehicle.SetItemText(nNum,3,szTempChar);

					sprintf( szTempChar, "%s", COMMENT::VEHICLE_TYPE[nVehicleType].c_str() );
					m_list_Vehicle.SetItemText(nNum,5,szTempChar);

					if (nVehicleDeleted == 1 ) sprintf( szTempChar, "%s(%d)","Deleted",nVehicleDeleted );
					else	sprintf( szTempChar, "%s(%d)","Active",nVehicleDeleted );
					m_list_Vehicle.SetItemText(nNum,6,szTempChar);

					nNum++;	}
				else	break;
				Sleep( 0 );
			}
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			GetOWnerNames();
		}break;

	case SEARCH_VEHICLEOWNERNAME:
		{
			VEC_SEARCH_NUM_ITER iter = m_VecSearchNum.begin();
			VEC_SEARCH_NUM_ITER iter_end = m_VecSearchNum.end();

			m_list_Vehicle.DeleteAllItems();
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

				_snprintf( szTemp, 256, "SELECT VehicleNum,VehicleName,VehicleChaNum,VehicleType,VehicleDeleted FROM %s.dbo.VehicleInfo WITH (NOLOCK) WHERE VehicleChaNum =%d"
				"ORDER BY VehicleNum",CToolCfg::GetInstance()->szGameDb,int (*iter) );

				std::string strTIME = CDebugSet::GetCurTime ();
				LOGSCRIPT::LogToFile("Vehicle.txt","%s--%s",strTIME.c_str(),szTemp);

				sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);

				if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
				{
					::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
					return;
				}

				SQLINTEGER nVehicleNum = 0, cbVehicleNum = SQL_NTS; 
				SQLCHAR    szVehicleName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbVehicleName = SQL_NTS;
				SQLINTEGER nVehicleChaNum = 0, cbVehicleChaNum = SQL_NTS; 
				SQLINTEGER nVehicleType = 0, cbVehicleType = SQL_NTS; 
				SQLINTEGER nVehicleDeleted = 0, cbVehicleDeleted = SQL_NTS; 

				while (true)
				{
					sReturn = ::SQLFetch(hStmt);
					if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
					if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
					{
						::SQLGetData(hStmt, 1, SQL_C_LONG, &nVehicleNum, 0, &cbVehicleNum );
						::SQLGetData(hStmt, 2, SQL_C_CHAR, szVehicleName, CHR_ID_LENGTH, &cbVehicleName);
						::SQLGetData(hStmt, 3, SQL_C_LONG, &nVehicleChaNum, 0, &cbVehicleChaNum );
						::SQLGetData(hStmt, 4, SQL_C_LONG, &nVehicleType, 0, &cbVehicleType );
						::SQLGetData(hStmt, 5, SQL_C_LONG, &nVehicleDeleted, 0, &cbVehicleDeleted );
			
						sprintf( szTempChar, "%d", nNum );
						m_list_Vehicle.InsertItem( nNum, szTempChar );

						sprintf( szTempChar, "%d", nVehicleNum );
						m_list_Vehicle.SetItemText(nNum,1,szTempChar);

						sprintf( szTempChar, "%s", szVehicleName );
						m_list_Vehicle.SetItemText(nNum,2,szTempChar);

						sprintf( szTempChar, "%d", nVehicleChaNum );
						m_list_Vehicle.SetItemText(nNum,3,szTempChar);

						sprintf( szTempChar, "%s", COMMENT::VEHICLE_TYPE[nVehicleType].c_str() );
						m_list_Vehicle.SetItemText(nNum,5,szTempChar);

						if (nVehicleDeleted == 1 ) sprintf( szTempChar, "%s(%d)","Deleted",nVehicleDeleted );
						else	sprintf( szTempChar, "%s(%d)","Active",nVehicleDeleted );
						m_list_Vehicle.SetItemText(nNum,6,szTempChar);

						nNum++;	}
					else	break;
					Sleep( 0 );
				}
				::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			}
			
			GetOWnerNames();
		}break;
	};
}

void CRanManagerVehicle::OnCbnSelchangeComboVehiclesearchtype()
{
	int nSelect = m_cSearchType.GetCurSel();
	if ( nSelect == SEARCH_VEHICLEALL || nSelect == SEARCH_VEHICLEDELETED ) SetWin_Enable(this,IDC_EDIT_SEARCH,false);
	else	 SetWin_Enable(this,IDC_EDIT_SEARCH,true);
}

void CRanManagerVehicle::OnNMDblclkListVehicle(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nSelect = m_list_Vehicle.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;
	nVehicleNum = atoi ( m_list_Vehicle.GetItemText(nSelect,1).GetString() );
	strVehicle = m_list_Vehicle.GetItemText(nSelect,2).GetString();

	SetWin_ShowWindow( this ,IDC_COMBO_VEHICLETYPE, TRUE );
	SetWin_ShowWindow( this ,IDC_BUTTON_VEHICLE_SELECT, TRUE );
	SetWin_ShowWindow( this ,IDC_EDIT_VEHICLETYPE, TRUE );

	SetWin_Num_int ( this, IDC_EDIT_SELECTED_NUM,nVehicleNum );
	SetWin_Text ( this, IDC_EDIT_SELECTED_NAME, strVehicle.GetString() );

	m_pVehicleTab->ActivePage(VEHICLEPAGE_EDIT,nVehicleNum);
	m_cVehiclePage.SetCurSel(VEHICLEPAGE_EDIT);
	SetWin_Text(this,IDC_EDIT_VEHICLETYPE,RMComments::m_PageVehicle[VEHICLEPAGE_EDIT].c_str() );
}

void CRanManagerVehicle::GetOWnerNames()
{
	int nItem = 0; 
	for(nItem =0 ; nItem < m_list_Vehicle.GetItemCount(); nItem++)
	{
		SQLRETURN	sReturn = 0; // SQL return value (short)	
		SQLHSTMT	hStmt; // Handle of statement (void*)

		int nChaNum =  atoi ( m_list_Vehicle.GetItemText(nItem, 3).GetString() );

		sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
		if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	continue;

		TCHAR szTemp[1024] = {0};
		_snprintf( szTemp, 256, "SELECT ChaName FROM %s.dbo.ChaInfo WHERE ChaNum = %d "
		"ORDER BY ChaNum",CToolCfg::GetInstance()->szGameDb,nChaNum);
		
		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("Vehicle.txt","%s--%s",strTIME.c_str(),szTemp);

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
		m_list_Vehicle.SetItemText(nItem,4,szTempChar);
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}		
}

void CRanManagerVehicle::GetSearchNum(std::string strSearch)
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
	LOGSCRIPT::LogToFile("Vehicle.txt","%s--%s",strTIME.c_str(),szTemp);

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
void CRanManagerVehicle::OnBnClickedButtonVehicleSelect()
{
	int nSelect = m_cVehiclePage.GetCurSel();
	SetWin_Text(this,IDC_EDIT_VEHICLETYPE,RMComments::m_PageVehicle[nSelect].c_str() );
	switch (nSelect)
	{
	case VEHICLEPAGE_MAIN:	m_pVehicleTab->ActivePage ( VEHICLEPAGE_MAIN ,nVehicleNum );	break;
	case VEHICLEPAGE_EDIT:	m_pVehicleTab->ActivePage ( VEHICLEPAGE_EDIT ,nVehicleNum );	break;
	case VEHICLEPAGE_INVEN:	m_pVehicleTab->ActivePage ( VEHICLEPAGE_INVEN ,nVehicleNum );	break;
	};
}
