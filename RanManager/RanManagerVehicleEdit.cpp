// RanManagerVehicleEdit.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerVehicleEdit.h"
#include "RanManagerVehicleTab.h"
#include "RanManagerComments.h"

#include "EtcFunction.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "GLItem.h"
#include "GLItemMan.h"
#include "CharSearch.h"
#include "GLVehicle.h"
#include "Calendar.h"
#include "ItemSearch.h"
#include "s_NetGlobal.h"
#include ".\ranmanagervehicleedit.h"

// CRanManagerVehicleEdit dialog

IMPLEMENT_DYNAMIC(CRanManagerVehicleEdit, CPropertyPage)
CRanManagerVehicleEdit::CRanManagerVehicleEdit(LOGFONT logfont)
	: CPropertyPage(CRanManagerVehicleEdit::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerVehicleEdit::~CRanManagerVehicleEdit()
{
}

void CRanManagerVehicleEdit::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_V_FULL, Slider_Battery );
	DDX_Control(pDX, IDC_COMBO_V_TYPE, m_cType );
	DDX_Control(pDX, IDC_COMBO_V_STATUS, m_cStatus );
}


BEGIN_MESSAGE_MAP(CRanManagerVehicleEdit, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_CHG_OWNER, OnBnClickedButtonChgOwner)
	ON_BN_CLICKED(IDC_BUTTON_CHG_ITEM, OnBnClickedButtonChgItem)
	ON_BN_CLICKED(IDC_BUTTON_V1_SET, OnBnClickedButtonV1Set)
	ON_BN_CLICKED(IDC_BUTTON_V2_SET, OnBnClickedButtonV2Set)
	ON_BN_CLICKED(IDC_BUTTON_V1_RESET, OnBnClickedButtonV1Reset)
	ON_BN_CLICKED(IDC_BUTTON_V2_RESET, OnBnClickedButtonV2Reset)
	ON_BN_CLICKED(IDC_BTN_EDIT_SAVE, OnBnClickedBtnEditSave)
	ON_BN_CLICKED(IDC_BTN_EDIT_CANCEL, OnBnClickedBtnEditCancel)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_V_FULL, OnNMCustomdrawSliderVFull)
END_MESSAGE_MAP()


// CRanManagerVehicleEdit message handlers
BOOL CRanManagerVehicleEdit::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	for ( int i = 0; i < VEHICLE_TYPE_SIZE; ++i )
	{
		m_cType.InsertString( i, COMMENT::VEHICLE_TYPE[i].c_str() );
	}

	for ( int i = 0; i < CHARSTATUS_SIZE; ++i )
	{
		m_cStatus.InsertString( i, RMComments::m_CharStatus[i].c_str() );
	}

	Slider_Battery.SetRange(0, 1000, TRUE);
	m_cType.SetCurSel(0);
	m_cStatus.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void	CRanManagerVehicleEdit::SetVehicle(int nVehicleNum)
{
	GetVehicle(nVehicleNum);
}

void	CRanManagerVehicleEdit::GetVehicle(int nVehicleNum)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

	TCHAR szTemp[1024] = {0};
	
	_snprintf( szTemp, 1024, 
		"SELECT VehicleNum,VehicleName,VehicleChaNum,VehicleType,VehicleCardMID,VehicleCardSID,VehicleBattery,VehicleDeleted,VehicleCreateDate,VehicleDeletedDate"
		" FROM %s.dbo.VehicleInfo WITH (NOLOCK) WHERE VehicleNum =%d "
	,CToolCfg::GetInstance()->szGameDb,nVehicleNum);

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("VehicleEdit.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nVehicleNum1 = 0,							cbVehicleNum = SQL_NTS; 
	SQLCHAR    szVehicleName[CHR_ID_LENGTH+1] = {0};		SQLINTEGER cbVehicleName = SQL_NTS;
	SQLINTEGER nVehicleChaNum = 0,							cbVehicleChaNum = SQL_NTS;
	SQLINTEGER nVehicleType = 0,							cbVehicleType = SQL_NTS;
	SQLINTEGER nVehicleCardMID = 0,							cbVehicleCardMID = SQL_NTS;
	SQLINTEGER nVehicleCardSID = 0,							cbVehicleCardSID = SQL_NTS;
	SQLINTEGER nVehicleBattery = 0,							cbVehicleBattery = SQL_NTS;
	SQLINTEGER nVehicleDeleted = 0,							cbVehicleDeleted = SQL_NTS;
	TIMESTAMP_STRUCT sVehicleCreateDate;					SQLINTEGER cbVehicleCreateDate= SQL_NTS;
	TIMESTAMP_STRUCT sVehicleDeletedDate;					SQLINTEGER cbVehicleDeletedDate= SQL_NTS;
	//SQLINTEGER nVehicleColor = 0,							cbVehicleColor = SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	return;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			::SQLGetData(hStmt, 1, SQL_C_LONG,		&nVehicleNum1,			0,		&cbVehicleNum );
			::SQLGetData(hStmt, 2, SQL_C_CHAR,		szVehicleName,			CHR_ID_LENGTH,  &cbVehicleName);
			::SQLGetData(hStmt, 3, SQL_C_LONG,		&nVehicleChaNum,			0,		&cbVehicleChaNum );
			::SQLGetData(hStmt, 4, SQL_C_LONG,		&nVehicleType,			0,		&cbVehicleType );
			::SQLGetData(hStmt, 5, SQL_C_LONG,		&nVehicleCardMID,			0,		&cbVehicleCardMID );
			::SQLGetData(hStmt, 6, SQL_C_LONG,		&nVehicleCardSID,			0,		&cbVehicleCardSID );
			::SQLGetData(hStmt, 7, SQL_C_LONG,		&nVehicleBattery,			0,		&cbVehicleBattery );
			::SQLGetData(hStmt, 8, SQL_C_LONG,		&nVehicleDeleted,			0,		&cbVehicleDeleted );
			::SQLGetData(hStmt, 9, SQL_C_TYPE_TIMESTAMP,	&sVehicleCreateDate,		0,		&cbVehicleCreateDate);
			::SQLGetData(hStmt, 10, SQL_C_TYPE_TIMESTAMP,	&sVehicleDeletedDate,		0,		&cbVehicleDeletedDate);
			//::SQLGetData(hStmt, 11, SQL_C_LONG,		&nVehicleColor,			0,		&cbVehicleColor );
		}
		else	break;
		Sleep( 0 );
	}

	SetWin_Num_int ( this, IDC_EDIT_V_NUM,nVehicleNum1);
	SetWin_Text ( this, IDC_EDIT_V_NAME_1, (const TCHAR*)szVehicleName );
	GetOwner(nVehicleChaNum);

	Slider_Battery.SetPos(nVehicleBattery);
	SetWin_Num_int ( this, IDC_EDIT_V_BATTERY,nVehicleBattery);

	m_cType.SetCurSel(nVehicleType);
	m_cStatus.SetCurSel(nVehicleDeleted);

	SetWin_Num_int ( this, IDC_EDIT_V_MID,nVehicleCardMID);
	SetWin_Num_int ( this, IDC_EDIT_V_SID,nVehicleCardSID);

	SITEM* pItem = GLItemMan::GetInstance().GetItem((WORD)nVehicleCardMID,(WORD)nVehicleCardSID);
	if ( pItem ) SetWin_Text ( this, IDC_EDIT_V_ITEMNAME,pItem->GetName() );

	SetWin_Num_int ( this, IDC_EDIT_DATEV_1_1,sVehicleCreateDate.day);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_1_2,sVehicleCreateDate.month);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_1_3,sVehicleCreateDate.year);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_1_4,sVehicleCreateDate.hour);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_1_5,sVehicleCreateDate.minute);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_1_6,sVehicleCreateDate.second);

	SetWin_Num_int ( this, IDC_EDIT_DATEV_2_1,sVehicleDeletedDate.day);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_2_2,sVehicleDeletedDate.month);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_2_3,sVehicleDeletedDate.year);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_2_4,sVehicleDeletedDate.hour);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_2_5,sVehicleDeletedDate.minute);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_2_6,sVehicleDeletedDate.second);

	//SetWin_Num_int ( this, IDC_EDIT_V_COLOR,nVehicleColor);
}

void CRanManagerVehicleEdit::GetOwner(int nChaNum)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT ChaNum,ChaName "
						"FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChaNum );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("VehicleEdit.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nChaNum1 = 0,							cbChaNum = SQL_NTS; 
	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaName = SQL_NTS; 

	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{	
			::SQLGetData(hStmt, 1, SQL_C_LONG,		&nChaNum1,			0,		&cbChaNum );
			::SQLGetData(hStmt, 2, SQL_C_CHAR, szChaName   ,  CHR_ID_LENGTH+1, &cbChaName); 
			SetWin_Num_int ( this, IDC_EDIT_V_CHANUM,nChaNum1);
			SetWin_Text(this,IDC_EDIT_V_CHANAME,(const char*) szChaName );
			break;
		}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerVehicleEdit::OnBnClickedButtonChgOwner()
{
	CCharSearch sCharSearch;
	sCharSearch.SetMultiple(false);
	if ( IDOK == sCharSearch.DoModal () )
	{
		GetOwner(sCharSearch.nSelectedChar);
	}
}

void CRanManagerVehicleEdit::OnBnClickedButtonChgItem()
{
	CItemSearch sItemSearch;
	sItemSearch.SetMultiple(false);
	sItemSearch.SetFilter(SEARCH_FILTER_VEHICLE);
	if ( IDOK == sItemSearch.DoModal () )
	{
		SITEM*	pItemCheck = GLItemMan::GetInstance().GetItem(sItemSearch.sSelectedItem);
		if ( pItemCheck )
		{
			SetWin_Num_int ( this, IDC_EDIT_V_MID,sItemSearch.sSelectedItem.wMainID);
			SetWin_Num_int ( this, IDC_EDIT_V_SID,sItemSearch.sSelectedItem.wSubID);
			SetWin_Text( this,IDC_EDIT_V_ITEMNAME,pItemCheck->GetName() );
			SetWin_Text( this,IDC_EDIT_V_NAME_1,pItemCheck->GetName() );
		}
	}
}

void CRanManagerVehicleEdit::OnBnClickedButtonV1Set()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay = GetWin_Num_int ( this, IDC_EDIT_DATEV_1_1 );
	sNewTime.wMonth = GetWin_Num_int ( this,IDC_EDIT_DATEV_1_2 );
	sNewTime.wYear = GetWin_Num_int ( this, IDC_EDIT_DATEV_1_3 );
	sNewTime.wHour = GetWin_Num_int ( this, IDC_EDIT_DATEV_1_4 );
	sNewTime.wMinute = GetWin_Num_int ( this, IDC_EDIT_DATEV_1_5 );
	sNewTime.wSecond = GetWin_Num_int ( this, IDC_EDIT_DATEV_1_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_DATEV_1_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_DATEV_1_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_DATEV_1_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_DATEV_1_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_DATEV_1_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_DATEV_1_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerVehicleEdit::OnBnClickedButtonV2Set()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay = GetWin_Num_int ( this, IDC_EDIT_DATEV_2_1 );
	sNewTime.wMonth = GetWin_Num_int ( this,IDC_EDIT_DATEV_2_2 );
	sNewTime.wYear = GetWin_Num_int ( this, IDC_EDIT_DATEV_2_3 );
	sNewTime.wHour = GetWin_Num_int ( this, IDC_EDIT_DATEV_2_4 );
	sNewTime.wMinute = GetWin_Num_int ( this, IDC_EDIT_DATEV_2_5 );
	sNewTime.wSecond = GetWin_Num_int ( this, IDC_EDIT_DATEV_2_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_DATEV_2_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_DATEV_2_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_DATEV_2_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_DATEV_2_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_DATEV_2_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_DATEV_2_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerVehicleEdit::OnBnClickedButtonV1Reset()
{
	SetWin_Num_int ( this, IDC_EDIT_DATEV_1_1,1);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_1_2,2);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_1_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_1_4,1);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_1_5,1);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_1_6,1);
}

void CRanManagerVehicleEdit::OnBnClickedButtonV2Reset()
{
	SetWin_Num_int ( this, IDC_EDIT_DATEV_2_1,1);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_2_2,2);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_2_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_2_4,1);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_2_5,1);
	SetWin_Num_int ( this, IDC_EDIT_DATEV_2_6,1);
}

void CRanManagerVehicleEdit::OnBnClickedBtnEditSave()
{
	//"SELECT VehicleNum,VehicleName,VehicleChaNum,VehicleType,VehicleCardMID,VehicleCardSID,VehicleBattery,VehicleDeleted,VehicleCreateDate,VehicleDeletedDate"
	CString strVehicleCreateDate;
	strVehicleCreateDate.Format("%d/%d/%d %d:%d:%d"
		,GetWin_Num_int ( this, IDC_EDIT_DATEV_1_2 )
		,GetWin_Num_int ( this, IDC_EDIT_DATEV_1_1 )
		,GetWin_Num_int ( this, IDC_EDIT_DATEV_1_3 )
		,GetWin_Num_int ( this, IDC_EDIT_DATEV_1_4 )
		,GetWin_Num_int ( this, IDC_EDIT_DATEV_1_5 )
		,GetWin_Num_int ( this, IDC_EDIT_DATEV_1_6 )
		);

	CString strVehicleDeletedDate;
	strVehicleDeletedDate.Format("%d/%d/%d %d:%d:%d"
		,GetWin_Num_int ( this, IDC_EDIT_DATEV_2_2 )
		,GetWin_Num_int ( this, IDC_EDIT_DATEV_2_1 )
		,GetWin_Num_int ( this, IDC_EDIT_DATEV_2_3 )
		,GetWin_Num_int ( this, IDC_EDIT_DATEV_2_4 )
		,GetWin_Num_int ( this, IDC_EDIT_DATEV_2_5 )
		,GetWin_Num_int ( this, IDC_EDIT_DATEV_2_6 )
		);


	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "UPDATE %s.dbo.VehicleInfo SET VehicleName='%s' ,VehicleChaNum=%u, VehicleType=%u, "
				"VehicleCardMID=%u, VehicleCardSID=%u, VehicleBattery=%u, VehicleDeleted=%d, VehicleCreateDate='%s',VehicleDeletedDate='%s' "
				"WHERE VehicleNum=%u", 
	CToolCfg::GetInstance()->szGameDb, 
	(const TCHAR*)GetWin_Text( this, IDC_EDIT_V_NAME_1 ).GetString(),
	GetWin_Num_int(this,IDC_EDIT_V_CHANUM),
	m_cType.GetCurSel(),
	GetWin_Num_int(this,IDC_EDIT_V_MID),
	GetWin_Num_int(this,IDC_EDIT_V_SID),
	GetWin_Num_int(this,IDC_EDIT_V_BATTERY),
	m_cStatus.GetCurSel(),
	strVehicleCreateDate.GetString(),
	strVehicleDeletedDate.GetString(),
	GetWin_Num_int(this,IDC_EDIT_V_COLOR),
	GetWin_Num_int(this,IDC_EDIT_V_NUM)
	);
		
	SQLRETURN	sReturn = 0; 	
	SQLHSTMT	hStmt; 

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("VehicleEdit.txt","%s--%s",strTIME.c_str(),szTemp);

	if (sReturn == SQL_ERROR )	MessageBox("Error! Saving Vehicle Data :-(","Ran Manager",MB_OK);
	if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)	MessageBox("Success! Saving Vehicle Data :-)","Ran Manager",MB_OK);

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	

	GetVehicle(GetWin_Num_int(this,IDC_EDIT_V_NUM));
}

void CRanManagerVehicleEdit::OnBnClickedBtnEditCancel()
{
	m_pToolTab->ActivePage(VEHICLEPAGE_MAIN,0);
}

void CRanManagerVehicleEdit::OnNMCustomdrawSliderVFull(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nBattery = Slider_Battery.GetPos();
	SetWin_Num_int ( this, IDC_EDIT_V_BATTERY,nBattery);
}
