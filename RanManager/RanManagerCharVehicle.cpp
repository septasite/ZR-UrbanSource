// RanManagerCharVehicle.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerCharVehicle.h"
#include ".\ranmanagercharvehicle.h"
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


// CRanManagerCharVehicle dialog

IMPLEMENT_DYNAMIC(CRanManagerCharVehicle, CPropertyPage)
CRanManagerCharVehicle::CRanManagerCharVehicle(LOGFONT logfont)
	: CPropertyPage(CRanManagerCharVehicle::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerCharVehicle::~CRanManagerCharVehicle()
{
}

void CRanManagerCharVehicle::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VEHICLE, m_list_Vehicle );
}


BEGIN_MESSAGE_MAP(CRanManagerCharVehicle, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_VEHICLE_CANCEL, OnBnClickedButtonVehicleCancel)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL, OnBnClickedButtonDeleteAll)
END_MESSAGE_MAP()


// CRanManagerCharVehicle message handlers
BOOL CRanManagerCharVehicle::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	m_list_Vehicle.SetExtendedStyle (m_list_Vehicle.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |LVS_EX_CHECKBOXES);
	m_list_Vehicle.GetClientRect ( &rectCtrl );
	lnWidth = rectCtrl.right - rectCtrl.left;

	const int nColumnCount = 9;	
	char* szColumnName1[nColumnCount] = { "#","Number", "MID", "SID" , "Name" , "Type" , "Deleted","Battery",""};
	int nColumnWidthPercent[nColumnCount] = { 9,9,9,9,30,13,9,7,5 };

	for ( int i = 0; i < nColumnCount; i++ )
	{		
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.pszText = szColumnName1[i];
		lvColumn.iSubItem = i;
		lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
		m_list_Vehicle.InsertColumn (i, &lvColumn );
	}

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerCharVehicle::SetChar(int nChar)
{
	LoadChar(nChar);
	LoadVehicle(nChar);
}

void CRanManagerCharVehicle::LoadChar(int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT ChaNum,ChaName FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChar );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharVehicle.txt","%s--%s",strTIME.c_str(),szTemp);

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

void CRanManagerCharVehicle::LoadVehicle(int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT VehicleNum,VehicleCardMID,VehicleCardSID,VehicleName,VehicleType,VehicleDeleted,VehicleBattery "
		"FROM %s.dbo.VehicleInfo WHERE VehicleChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChar );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharVehicle.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	return;

	SQLINTEGER nVehicleNum = 0, cbVehicleNum=SQL_NTS;
	SQLINTEGER nVehicleCardMID = 0, cbVehicleCardMID=SQL_NTS;
	SQLINTEGER nVehicleCardSID = 0, cbVehicleCardSID=SQL_NTS;
	SQLCHAR    szVehicleName[CHR_ID_LENGTH+10] = {0}; SQLINTEGER cbVehicleName = SQL_NTS; 
	SQLINTEGER nVehicleType = 0, cbVehicleType=SQL_NTS;
	SQLINTEGER nVehicleDeleted = 0, cbVehicleDeleted=SQL_NTS;
	SQLINTEGER nVehicleBattery = 0, cbVehicleBattery=SQL_NTS;
	
	int nNum = 0;
	char szTempChar[256];
	m_list_Vehicle.DeleteAllItems();
	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{		
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nVehicleNum,       0, &cbVehicleNum );
			::SQLGetData(hStmt, 2, SQL_C_LONG, &nVehicleCardMID,       0, &cbVehicleCardMID );
			::SQLGetData(hStmt, 3, SQL_C_LONG, &nVehicleCardSID,       0, &cbVehicleCardSID );
			::SQLGetData(hStmt, 4, SQL_C_CHAR, szVehicleName   ,  CHR_ID_LENGTH+10, &cbVehicleName ); 
			::SQLGetData(hStmt, 5, SQL_C_LONG, &nVehicleType,       0, &cbVehicleType );
			::SQLGetData(hStmt, 6, SQL_C_LONG, &nVehicleDeleted,       0, &cbVehicleDeleted );
			::SQLGetData(hStmt, 7, SQL_C_LONG, &nVehicleBattery,       0, &cbVehicleBattery );
           
			sprintf( szTempChar, "%d", nNum );
			m_list_Vehicle.InsertItem( nNum, szTempChar );

			sprintf( szTempChar, "%d", nVehicleNum );
			m_list_Vehicle.SetItemText(nNum,1,szTempChar);

			sprintf( szTempChar, "%d", nVehicleCardMID );
			m_list_Vehicle.SetItemText(nNum,2,szTempChar);

			sprintf( szTempChar, "%d", nVehicleCardSID );
			m_list_Vehicle.SetItemText(nNum,3,szTempChar);

			sprintf( szTempChar, "%s", szVehicleName );
			m_list_Vehicle.SetItemText(nNum,4,szTempChar);

			sprintf( szTempChar, "%s", COMMENT::VEHICLE_TYPE[nVehicleType].c_str() );
			m_list_Vehicle.SetItemText(nNum,5,szTempChar);

			if (nVehicleDeleted == 1)	sprintf( szTempChar, "%s", "Deleted" );
			else		sprintf( szTempChar, "%s", "Usable" );
			m_list_Vehicle.SetItemText(nNum,6,szTempChar);

			sprintf( szTempChar, "%d", nVehicleBattery );
			m_list_Vehicle.SetItemText(nNum,7,szTempChar);

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

void CRanManagerCharVehicle::OnBnClickedButtonVehicleCancel()
{
	m_pToolTab->ActivePage(CHARPAGE_MAIN,0);
}

void CRanManagerCharVehicle::OnBnClickedButtonDelete()
{
	if ( MessageBox("This Will Delete the Selected Vehicles! Continue?\nThis is Permanent Delete!","Question",MB_YESNO) == IDYES )
	{
		int nItem = 0; 
		int nChar = GetWin_Num_int(this,IDC_EDIT_CHANUM);
		for(nItem =0 ; nItem <  m_list_Vehicle.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_Vehicle.GetCheck(nItem);
			if( bChecked)
			{
				SQLRETURN	sReturn = 0; // SQL return value (short)	
				SQLHSTMT	hStmt; // Handle of statement (void*)
				int nVehicleNum = atoi ( m_list_Vehicle.GetItemText(nItem, 1).GetString() );

				sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
				if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	continue;

				TCHAR szTemp[1024] = {0};
				
				_snprintf( szTemp, 1024, 
					"Delete From %s.dbo.VehicleInfo "
					" Where VehicleChaNum =%d AND VehicleNum =%d"
				,CToolCfg::GetInstance()->szGameDb
				,nChar
				,nVehicleNum
				);

				sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
				std::string strTIME = CDebugSet::GetCurTime ();
				LOGSCRIPT::LogToFile("CharVehicle.txt","%s--%s",strTIME.c_str(),szTemp);

				if (sReturn == SQL_ERROR )	
				{
					MessageBox("Error! Cant Delete Vehicles","Ran Manager",MB_OK);
					::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
					continue;
				}
			}
		}
		LoadVehicle(nChar);
	}
}

void CRanManagerCharVehicle::OnBnClickedButtonDeleteAll()
{
	if ( MessageBox("Are you sure you want to Clear All The Saved Vehicles of this Character?\nThis is Permanent Delete!","Question",MB_YESNO) == IDYES )
	{
		SQLRETURN	sReturn = 0; // SQL return value (short)	
		SQLHSTMT	hStmt; // Handle of statement (void*)
		int nChar = GetWin_Num_int(this,IDC_EDIT_CHANUM);

		sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
		if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

		TCHAR szTemp[1024] = {0};
		
		_snprintf( szTemp, 1024, 
			"Delete From %s.dbo.VehicleInfo "
			" Where VehicleChaNum =%d"
		,CToolCfg::GetInstance()->szGameDb
		,nChar
		);

		sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("CharVehicle.txt","%s--%s",strTIME.c_str(),szTemp);

		if (sReturn == SQL_ERROR )	
		{
			MessageBox("Error! Cant Delete Vehicles","Ran Manager",MB_OK);
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
		}
		LoadVehicle(nChar);
	}
}
