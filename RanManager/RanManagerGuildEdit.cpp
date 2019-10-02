// RanManagerGuildEdit.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerGuildEdit.h"
#include ".\ranmanagerguildedit.h"
#include "RanManagerGuildTab.h"
#include "RanManagerComments.h"

#include "COdbc.h"
#include "CCfg.h"
#include "s_NetGlobal.h"
#include "Calendar.h"
#include "EtcFunction.h"
#include "GLCharDefine.h"
#include "GLogicData.h"
#include "LogScript.h"
#include "GuildSearch.h"
#include "MapSearch.h"
#include "ItemSearch.h"
#include "CharSearch.h"
#include "GLogicData.h"

// CRanManagerGuildEdit dialog

IMPLEMENT_DYNAMIC(CRanManagerGuildEdit, CPropertyPage)
CRanManagerGuildEdit::CRanManagerGuildEdit(LOGFONT logfont)
	: CPropertyPage(CRanManagerGuildEdit::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerGuildEdit::~CRanManagerGuildEdit()
{
}

void CRanManagerGuildEdit::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GURANK, m_cRank );
	DDX_Control(pDX, IDC_COMBO_GUEXPIRE, m_cExpire );
}


BEGIN_MESSAGE_MAP(CRanManagerGuildEdit, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_EDIT_CANCEL, OnBnClickedBtnEditCancel)
	ON_BN_CLICKED(IDC_BUTTON_SET_G1, OnBnClickedButtonSetG1)
	ON_BN_CLICKED(IDC_BUTTON_SET_G2, OnBnClickedButtonSetG2)
	ON_BN_CLICKED(IDC_BUTTON_SET_G3, OnBnClickedButtonSetG3)
	ON_BN_CLICKED(IDC_BUTTON_SET_G4, OnBnClickedButtonSetG4)
	ON_BN_CLICKED(IDC_BUTTON_SET_G5, OnBnClickedButtonSetG5)
	ON_BN_CLICKED(IDC_BUTTON_SET_G6, OnBnClickedButtonSetG6)
	ON_BN_CLICKED(IDC_BUTTON_RESET_G1, OnBnClickedButtonResetG1)
	ON_BN_CLICKED(IDC_BUTTON_RESET_G2, OnBnClickedButtonResetG2)
	ON_BN_CLICKED(IDC_BUTTON_RESET_G3, OnBnClickedButtonResetG3)
	ON_BN_CLICKED(IDC_BUTTON_RESET_G4, OnBnClickedButtonResetG4)
	ON_BN_CLICKED(IDC_BUTTON_RESET_G5, OnBnClickedButtonResetG5)
	ON_BN_CLICKED(IDC_BUTTON_RESET_G6, OnBnClickedButtonResetG6)
	ON_BN_CLICKED(IDC_BUTTON_CHANGEMASTER, OnBnClickedButtonChangemaster)
	ON_BN_CLICKED(IDC_BTN_EDIT_SAVE, OnBnClickedBtnEditSave)
END_MESSAGE_MAP()


// CRanManagerGuildEdit message handlers
BOOL CRanManagerGuildEdit::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	for ( int i = 0; i < CLUBRANK_SIZE; ++i )
	{
		m_cRank.InsertString( i, RMComments::m_ClubRank[i].c_str() );
	}
	m_cRank.SetCurSel(0);

	for ( int i = 0; i < CLUBSATUS_SIZE; ++i )
	{
		m_cExpire.InsertString( i, RMComments::m_ClubStatus[i].c_str() );
	}
	m_cExpire.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerGuildEdit::SetGuild(int nGuildNum)
{
	LoadGuild(nGuildNum);
}

void CRanManagerGuildEdit::LoadGuild(int nGuildNum)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

	TCHAR szTemp[1024] = {0};
	
	_snprintf( szTemp, 1024, 
		"SELECT GuNum,ChaNum,GuDeputy,GuName,GuNotice,GuRank,GuExpire,GuMakeTime,"
		"GuExpireTime,GuAllianceSec,GuAllianceDis,GuAuthorityTime,GuAllianceBattleLose,GuAllianceBattleDraw,"
		"GuAllianceBattleWin,GuBattleLastTime,GuBattleLose,GuBattleDraw,GuBattleWin"
		" FROM %s.dbo.GuildInfo WITH (NOLOCK) WHERE GuNum =%d "
	,CToolCfg::GetInstance()->szGameDb,nGuildNum);

	//GuMoney,GuIncomeMoney,GuMarkVer
	//	SQLCHAR    szGuNotice[EMCLUB_NOTICE_LEN+1]= {0};  SQLINTEGER cbGuNotice = SQL_NTS;

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildEdit.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nGuNum = 0,							cbGuNum = SQL_NTS; 
	SQLINTEGER nChaNum = 0,							cbChaNum = SQL_NTS; 
	SQLINTEGER nGuDeputy = 0,						cbGuDeputy= SQL_NTS; 
	SQLCHAR    szGuName[CHR_ID_LENGTH+1] = {0};		SQLINTEGER cbGuName = SQL_NTS;
	SQLCHAR    szGuNotice[EMCLUB_NOTICE_LEN+1] = {0};		SQLINTEGER cbGuNotice = SQL_NTS;
	SQLINTEGER nGuRank = 0,							cbGuRank= SQL_NTS; 
	SQLINTEGER nGuExpire = 0,						cbGuExpire= SQL_NTS; 
	TIMESTAMP_STRUCT sGuMakeTime;					SQLINTEGER cbGuMakeTime = SQL_NTS;
	TIMESTAMP_STRUCT sGuExpireTime;					SQLINTEGER cbGuExpireTime = SQL_NTS;
	TIMESTAMP_STRUCT sGuAllianceSec;					SQLINTEGER cbGuAllianceSec = SQL_NTS;
	TIMESTAMP_STRUCT sGuAllianceDis;					SQLINTEGER cbGuAllianceDis = SQL_NTS;
	TIMESTAMP_STRUCT sGuAuthorityTime;					SQLINTEGER cbGuAuthorityTime = SQL_NTS;
	SQLINTEGER nGuAllianceBattleLose = 0,						cbGuAllianceBattleLose = SQL_NTS; 
	SQLINTEGER nGuAllianceBattleDraw = 0,						cbGuAllianceBattleDraw = SQL_NTS; 
	SQLINTEGER nGuAllianceBattleWin = 0,						cbGuAllianceBattleWin = SQL_NTS; 
	TIMESTAMP_STRUCT sGuBattleLastTime;					SQLINTEGER cbGuBattleLastTime = SQL_NTS;
	SQLINTEGER nGuBattleLose = 0,						cbGuBattleLose = SQL_NTS; 
	SQLINTEGER nGuBattleDraw = 0,						cbGuBattleDraw = SQL_NTS; 
	SQLINTEGER nGuBattleWin = 0,						cbGuBattleWin = SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	return;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			::SQLGetData(hStmt, 1, SQL_C_LONG,		&nGuNum,			0,		&cbGuNum );
			::SQLGetData(hStmt, 2, SQL_C_LONG,		&nChaNum,			0,		&cbChaNum );
			::SQLGetData(hStmt, 3, SQL_C_LONG,		&nGuDeputy,			0,		&cbGuDeputy);
			::SQLGetData(hStmt, 4, SQL_C_CHAR,		szGuName,			CHR_ID_LENGTH,  &cbGuName);
			::SQLGetData(hStmt, 5, SQL_C_CHAR,		szGuNotice,			EMCLUB_NOTICE_LEN,  &cbGuNotice);
			::SQLGetData(hStmt, 6, SQL_C_LONG,		&nGuRank,			0,		&cbGuRank);
			::SQLGetData(hStmt, 7, SQL_C_LONG,		&nGuExpire,			0,		&cbGuExpire);
			::SQLGetData(hStmt, 8, SQL_C_TYPE_TIMESTAMP,	&sGuMakeTime,		0,		&cbGuMakeTime);
			::SQLGetData(hStmt, 9, SQL_C_TYPE_TIMESTAMP,	&sGuExpireTime,		0,		&cbGuExpireTime);
			::SQLGetData(hStmt, 10, SQL_C_TYPE_TIMESTAMP,	&sGuAllianceSec,		0,		&cbGuAllianceSec);
			::SQLGetData(hStmt, 11, SQL_C_TYPE_TIMESTAMP,	&sGuAllianceDis,		0,		&cbGuAllianceDis);
			::SQLGetData(hStmt, 12, SQL_C_TYPE_TIMESTAMP,	&sGuAuthorityTime,		0,		&cbGuAuthorityTime);
			::SQLGetData(hStmt, 13, SQL_C_LONG,		&nGuAllianceBattleLose,			0,		&cbGuAllianceBattleLose);
			::SQLGetData(hStmt, 14, SQL_C_LONG,		&nGuAllianceBattleDraw,			0,		&cbGuAllianceBattleDraw);
			::SQLGetData(hStmt, 15, SQL_C_LONG,		&nGuAllianceBattleWin,			0,		&cbGuAllianceBattleWin);
			::SQLGetData(hStmt, 16, SQL_C_TYPE_TIMESTAMP,	&sGuBattleLastTime,		0,		&cbGuBattleLastTime);
			::SQLGetData(hStmt, 17, SQL_C_LONG,		&nGuBattleLose,			0,		&cbGuBattleLose);
			::SQLGetData(hStmt, 18, SQL_C_LONG,		&nGuBattleDraw,			0,		&cbGuBattleDraw);
			::SQLGetData(hStmt, 19, SQL_C_LONG,		&nGuBattleWin,			0,		&cbGuBattleWin);
		}
		else	break;
		Sleep( 0 );
	}

	SetWin_Num_int ( this, IDC_EDIT_GUNUM,nGuNum);
	SetWin_Text ( this, IDC_EDIT_GUNAME, (const TCHAR*)szGuName );

	SetWin_Num_int ( this, IDC_EDIT_GUDEPUTY,nGuDeputy);
	SetWin_Text ( this, IDC_EDIT_NOTICE, (const TCHAR*)szGuNotice );

	m_cRank.SetCurSel(nGuRank);
	m_cExpire.SetCurSel(nGuExpire);

	SetWin_Num_int ( this, IDC_EDIT_DATE_G1_1,sGuMakeTime.day);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G1_2,sGuMakeTime.month);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G1_3,sGuMakeTime.year);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G1_4,sGuMakeTime.hour);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G1_5,sGuMakeTime.minute);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G1_6,sGuMakeTime.second);

	SetWin_Num_int ( this, IDC_EDIT_DATE_G2_1,sGuExpireTime.day);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G2_2,sGuExpireTime.month);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G2_3,sGuExpireTime.year);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G2_4,sGuExpireTime.hour);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G2_5,sGuExpireTime.minute);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G2_6,sGuExpireTime.second);

	SetWin_Num_int ( this, IDC_EDIT_DATE_G3_1,sGuAllianceSec.day);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G3_2,sGuAllianceSec.month);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G3_3,sGuAllianceSec.year);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G3_4,sGuAllianceSec.hour);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G3_5,sGuAllianceSec.minute);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G3_6,sGuAllianceSec.second);

	SetWin_Num_int ( this, IDC_EDIT_DATE_G4_1,sGuAllianceDis.day);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G4_2,sGuAllianceDis.month);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G4_3,sGuAllianceDis.year);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G4_4,sGuAllianceDis.hour);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G4_5,sGuAllianceDis.minute);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G4_6,sGuAllianceDis.second);

	SetWin_Num_int ( this, IDC_EDIT_DATE_G5_1,sGuAuthorityTime.day);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G5_2,sGuAuthorityTime.month);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G5_3,sGuAuthorityTime.year);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G5_4,sGuAuthorityTime.hour);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G5_5,sGuAuthorityTime.minute);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G5_6,sGuAuthorityTime.second);

	SetWin_Num_int ( this, IDC_EDIT_DATE_G6_1,sGuBattleLastTime.day);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G6_2,sGuBattleLastTime.month);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G6_3,sGuBattleLastTime.year);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G6_4,sGuBattleLastTime.hour);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G6_5,sGuBattleLastTime.minute);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G6_6,sGuBattleLastTime.second);

	SetWin_Num_int ( this, IDC_EDIT_A_LOSS,nGuAllianceBattleLose);
	SetWin_Num_int ( this, IDC_EDIT_A_DRAW,nGuAllianceBattleDraw);
	SetWin_Num_int ( this, IDC_EDIT_A_WIN,nGuAllianceBattleWin);

	SetWin_Num_int ( this, IDC_EDIT_LOSS,nGuBattleLose);
	SetWin_Num_int ( this, IDC_EDIT_DRAW,nGuBattleDraw);
	SetWin_Num_int ( this, IDC_EDIT_WIN,nGuBattleWin);

	LoadMaster(nChaNum);

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerGuildEdit::LoadMaster(int nMaster )
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT ChaNum,ChaName "
						"FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nMaster );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildEdit.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nChaNum = 0,							cbChaNum = SQL_NTS; 
	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaName = SQL_NTS; 

	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{	
			::SQLGetData(hStmt, 1, SQL_C_LONG,		&nChaNum,			0,		&cbChaNum );
			::SQLGetData(hStmt, 2, SQL_C_CHAR, szChaName   ,  CHR_ID_LENGTH+1, &cbChaName); 
			SetWin_Num_int ( this, IDC_EDIT_CHANUM,nChaNum);
			SetWin_Text(this,IDC_EDIT_CHANAME,(const char*) szChaName );
//
			break;
		}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerGuildEdit::OnBnClickedBtnEditCancel()
{
	m_pToolTab->ActivePage(GUILDPAGE_MAIN,0);
}

void CRanManagerGuildEdit::OnBnClickedButtonSetG1()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay		= GetWin_Num_int ( this, IDC_EDIT_DATE_G1_1 );
	sNewTime.wMonth		= GetWin_Num_int ( this, IDC_EDIT_DATE_G1_2 );
	sNewTime.wYear		= GetWin_Num_int ( this, IDC_EDIT_DATE_G1_3 );
	sNewTime.wHour		= GetWin_Num_int ( this, IDC_EDIT_DATE_G1_4 );
	sNewTime.wMinute	= GetWin_Num_int ( this, IDC_EDIT_DATE_G1_5 );
	sNewTime.wSecond	= GetWin_Num_int ( this, IDC_EDIT_DATE_G1_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_DATE_G1_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G1_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G1_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G1_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G1_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G1_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerGuildEdit::OnBnClickedButtonSetG2()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay		= GetWin_Num_int ( this, IDC_EDIT_DATE_G2_1 );
	sNewTime.wMonth		= GetWin_Num_int ( this, IDC_EDIT_DATE_G2_2 );
	sNewTime.wYear		= GetWin_Num_int ( this, IDC_EDIT_DATE_G2_3 );
	sNewTime.wHour		= GetWin_Num_int ( this, IDC_EDIT_DATE_G2_4 );
	sNewTime.wMinute	= GetWin_Num_int ( this, IDC_EDIT_DATE_G2_5 );
	sNewTime.wSecond	= GetWin_Num_int ( this, IDC_EDIT_DATE_G2_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_DATE_G2_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G2_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G2_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G2_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G2_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G2_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerGuildEdit::OnBnClickedButtonSetG3()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay		= GetWin_Num_int ( this, IDC_EDIT_DATE_G3_1 );
	sNewTime.wMonth		= GetWin_Num_int ( this, IDC_EDIT_DATE_G3_2 );
	sNewTime.wYear		= GetWin_Num_int ( this, IDC_EDIT_DATE_G3_3 );
	sNewTime.wHour		= GetWin_Num_int ( this, IDC_EDIT_DATE_G3_4 );
	sNewTime.wMinute	= GetWin_Num_int ( this, IDC_EDIT_DATE_G3_5 );
	sNewTime.wSecond	= GetWin_Num_int ( this, IDC_EDIT_DATE_G3_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_DATE_G3_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G3_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G3_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G3_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G3_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G3_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerGuildEdit::OnBnClickedButtonSetG4()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay		= GetWin_Num_int ( this, IDC_EDIT_DATE_G4_1 );
	sNewTime.wMonth		= GetWin_Num_int ( this, IDC_EDIT_DATE_G4_2 );
	sNewTime.wYear		= GetWin_Num_int ( this, IDC_EDIT_DATE_G4_3 );
	sNewTime.wHour		= GetWin_Num_int ( this, IDC_EDIT_DATE_G4_4 );
	sNewTime.wMinute	= GetWin_Num_int ( this, IDC_EDIT_DATE_G4_5 );
	sNewTime.wSecond	= GetWin_Num_int ( this, IDC_EDIT_DATE_G4_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_DATE_G4_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G4_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G4_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G4_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G4_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G4_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerGuildEdit::OnBnClickedButtonSetG5()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay		= GetWin_Num_int ( this, IDC_EDIT_DATE_G5_1 );
	sNewTime.wMonth		= GetWin_Num_int ( this, IDC_EDIT_DATE_G5_2 );
	sNewTime.wYear		= GetWin_Num_int ( this, IDC_EDIT_DATE_G5_3 );
	sNewTime.wHour		= GetWin_Num_int ( this, IDC_EDIT_DATE_G5_4 );
	sNewTime.wMinute	= GetWin_Num_int ( this, IDC_EDIT_DATE_G5_5 );
	sNewTime.wSecond	= GetWin_Num_int ( this, IDC_EDIT_DATE_G5_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_DATE_G5_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G5_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G5_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G5_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G5_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G5_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerGuildEdit::OnBnClickedButtonSetG6()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay		= GetWin_Num_int ( this, IDC_EDIT_DATE_G6_1 );
	sNewTime.wMonth		= GetWin_Num_int ( this, IDC_EDIT_DATE_G6_2 );
	sNewTime.wYear		= GetWin_Num_int ( this, IDC_EDIT_DATE_G6_3 );
	sNewTime.wHour		= GetWin_Num_int ( this, IDC_EDIT_DATE_G6_4 );
	sNewTime.wMinute	= GetWin_Num_int ( this, IDC_EDIT_DATE_G6_5 );
	sNewTime.wSecond	= GetWin_Num_int ( this, IDC_EDIT_DATE_G6_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_DATE_G6_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G6_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G6_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G6_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G6_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_DATE_G6_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerGuildEdit::OnBnClickedButtonResetG1()
{
	SetWin_Num_int ( this, IDC_EDIT_DATE_G1_1,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G1_2,2);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G1_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G1_4,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G1_5,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G1_6,1);
}

void CRanManagerGuildEdit::OnBnClickedButtonResetG2()
{
	SetWin_Num_int ( this, IDC_EDIT_DATE_G2_1,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G2_2,2);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G2_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G2_4,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G2_5,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G2_6,1);
}

void CRanManagerGuildEdit::OnBnClickedButtonResetG3()
{
	SetWin_Num_int ( this, IDC_EDIT_DATE_G3_1,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G3_2,2);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G3_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G3_4,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G3_5,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G3_6,1);
}

void CRanManagerGuildEdit::OnBnClickedButtonResetG4()
{
	SetWin_Num_int ( this, IDC_EDIT_DATE_G4_1,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G4_2,2);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G4_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G4_4,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G4_5,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G4_6,1);
}

void CRanManagerGuildEdit::OnBnClickedButtonResetG5()
{
	SetWin_Num_int ( this, IDC_EDIT_DATE_G5_1,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G5_2,2);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G5_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G5_4,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G5_5,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G5_6,1);
}

void CRanManagerGuildEdit::OnBnClickedButtonResetG6()
{
	SetWin_Num_int ( this, IDC_EDIT_DATE_G6_1,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G6_2,2);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G6_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G6_4,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G6_5,1);
	SetWin_Num_int ( this, IDC_EDIT_DATE_G6_6,1);
}

void CRanManagerGuildEdit::OnBnClickedButtonChangemaster()
{
	CCharSearch sCharSearch;
	//sCharSearch.SetMultiple(true);
	if ( IDOK == sCharSearch.DoModal () )
	{
		if ( DropMaster( GetWin_Num_int(this,IDC_EDIT_CHANUM) ) )
		{
			LoadMaster(sCharSearch.nSelectedChar );
		}
	}
}

void CRanManagerGuildEdit::OnBnClickedBtnEditSave()
{
	CString strGuMakeTime;
	strGuMakeTime.Format("%d/%d/%d %d:%d:%d"
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G1_2 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G1_1 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G1_3 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G1_4 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G1_5 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G1_6 )
		);

	CString strGuExpireTime;
	strGuExpireTime.Format("%d/%d/%d %d:%d:%d"
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G2_2 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G2_1 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G2_3 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G2_4 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G2_5 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G2_6 )
		);

	CString strGuAllianceSec;
	strGuAllianceSec.Format("%d/%d/%d %d:%d:%d"
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G3_2 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G3_1 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G3_3 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G3_4 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G3_5 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G3_6 )
		);

	CString strGuAllianceDis;
	strGuAllianceDis.Format("%d/%d/%d %d:%d:%d"
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G4_2 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G4_1 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G4_3 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G4_4 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G4_5 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G4_6 )
		);

	CString strGuAuthorityTime;
	strGuAuthorityTime.Format("%d/%d/%d %d:%d:%d"
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G5_2 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G5_1 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G5_3 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G5_4 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G5_5 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G5_6 )
		);

	CString strGuBattleLastTime;
	strGuBattleLastTime.Format("%d/%d/%d %d:%d:%d"
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G6_2 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G6_1 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G6_3 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G6_4 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G6_5 )
		,GetWin_Num_int ( this, IDC_EDIT_DATE_G6_6 )
		);


	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "UPDATE %s.dbo.GuildInfo SET ChaNum=%d, GuDeputy=%u, GuName='%s', "
				"GuNotice='%s', GuRank=%u, GuExpire=%u, GuMakeTime='%s', GuExpireTime='%s', "
				"GuAllianceSec='%s', GuAllianceDis='%s', GuAuthorityTime='%s', GuAllianceBattleLose=%u, GuAllianceBattleDraw=%u, "
				"GuAllianceBattleWin=%u, GuBattleLastTime='%s', GuBattleLose=%u, GuBattleDraw=%u, GuBattleWin=%u "
				"WHERE GuNum=%u", 
	CToolCfg::GetInstance()->szGameDb,
	GetWin_Num_int(this,IDC_EDIT_CHANUM), 
	GetWin_Num_int(this,IDC_EDIT_GUDEPUTY), 
	(const TCHAR*)GetWin_Text( this, IDC_EDIT_GUNAME ).GetString(),
	(const TCHAR*)GetWin_Text( this, IDC_EDIT_NOTICE ).GetString(),
	m_cRank.GetCurSel(),
	m_cExpire.GetCurSel(),
	strGuMakeTime.GetString(),
	strGuExpireTime.GetString(),
	strGuAllianceSec.GetString(),
	strGuAllianceDis.GetString(),
	strGuAuthorityTime.GetString(),
	GetWin_Num_int(this,IDC_EDIT_A_LOSS),
	GetWin_Num_int(this,IDC_EDIT_A_DRAW),
	GetWin_Num_int(this,IDC_EDIT_A_WIN),
	strGuBattleLastTime.GetString(),
	GetWin_Num_int(this,IDC_EDIT_LOSS),
	GetWin_Num_int(this,IDC_EDIT_DRAW),
	GetWin_Num_int(this,IDC_EDIT_WIN),
	GetWin_Num_int(this,IDC_EDIT_GUNUM)
	);
		
	SQLRETURN	sReturn = 0; 	
	SQLHSTMT	hStmt; 

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildEdit.txt","%s--%s",strTIME.c_str(),szTemp);

	if (sReturn == SQL_ERROR )	MessageBox("Error! Saving Guild Data :-(","Ran Manager",MB_OK);
	if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)	MessageBox("Success! Saving Guild Data :-)","Ran Manager",MB_OK);

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	

	LoadGuild(GetWin_Num_int(this,IDC_EDIT_GUNUM));
}


BOOL CRanManagerGuildEdit::DropMaster(int nMaster)
{
	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "UPDATE %s.dbo.ChaInfo SET GuNum=%d, GuPosition=%u"
				" WHERE ChaNum=%u", 
	CToolCfg::GetInstance()->szGameDb,
	0, 
	0, 
	nMaster
	);
		
	SQLRETURN	sReturn = 0; 	
	SQLHSTMT	hStmt; 

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return FALSE;

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildEdit.txt","%s--%s",strTIME.c_str(),szTemp);

	if (sReturn == SQL_ERROR )	return FALSE;
	if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)	return TRUE;

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	

	return FALSE;
}