// RanManagerGuildLocker.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerGuildLocker.h"
#include ".\ranmanagerguildlocker.h"
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
#include "../NetServerLib/s_DbBase.h"
#include "../EngineLib/Common/ByteStream.h"

// CRanManagerGuildLocker dialog

IMPLEMENT_DYNAMIC(CRanManagerGuildLocker, CPropertyPage)
CRanManagerGuildLocker::CRanManagerGuildLocker(LOGFONT logfont)
	: CPropertyPage(CRanManagerGuildLocker::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	
	nActivePage = 0;
	for ( int i=0; i<LOCKER_SIZE; ++i )	m_cStorage[i].SetState ( STORAGE_INVEN_X, STORAGE_INVEN_Y );
	nActiveItem_X = 65535;
	nActiveItem_Y = 65535;
}

CRanManagerGuildLocker::~CRanManagerGuildLocker()
{
}

void CRanManagerGuildLocker::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GENTYPE, m_cGenType );
	DDX_Control(pDX, IDC_COMBO_OPTION1, m_cRandomOp1 );
	DDX_Control(pDX, IDC_COMBO_OPTION2, m_cRandomOp2 );
	DDX_Control(pDX, IDC_COMBO_OPTION3, m_cRandomOp3 );
	DDX_Control(pDX, IDC_COMBO_OPTION4, m_cRandomOp4 );
}


BEGIN_MESSAGE_MAP(CRanManagerGuildLocker, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_EDIT_CANCEL_LOCKER, OnBnClickedBtnEditCancelLocker)
	ON_BN_CLICKED(IDC_BTN_EDIT_SAVE_LOCKER, OnBnClickedBtnEditSaveLocker)
	ON_BN_CLICKED(IDC_BUTTON_P1, OnBnClickedButtonP1)
	ON_BN_CLICKED(IDC_BUTTON_P2, OnBnClickedButtonP2)
	ON_BN_CLICKED(IDC_BUTTON_P3, OnBnClickedButtonP3)
	ON_BN_CLICKED(IDC_BUTTON_P4, OnBnClickedButtonP4)
	ON_BN_CLICKED(IDC_BUTTON_P5, OnBnClickedButtonP5)
	ON_BN_CLICKED(IDC_BUTTON_0_0, OnBnClickedButton00)
	ON_BN_CLICKED(IDC_BUTTON_0_1, OnBnClickedButton01)
	ON_BN_CLICKED(IDC_BUTTON_0_2, OnBnClickedButton02)
	ON_BN_CLICKED(IDC_BUTTON_0_3, OnBnClickedButton03)
	ON_BN_CLICKED(IDC_BUTTON_1_0, OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON_1_1, OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON_1_2, OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON_1_3, OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON_2_0, OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON_2_1, OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON_2_2, OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON_2_3, OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON_3_0, OnBnClickedButton30)
	ON_BN_CLICKED(IDC_BUTTON_3_1, OnBnClickedButton31)
	ON_BN_CLICKED(IDC_BUTTON_3_2, OnBnClickedButton32)
	ON_BN_CLICKED(IDC_BUTTON_3_3, OnBnClickedButton33)
	ON_BN_CLICKED(IDC_BUTTON_4_0, OnBnClickedButton40)
	ON_BN_CLICKED(IDC_BUTTON_4_1, OnBnClickedButton41)
	ON_BN_CLICKED(IDC_BUTTON_4_2, OnBnClickedButton42)
	ON_BN_CLICKED(IDC_BUTTON_4_3, OnBnClickedButton43)
	ON_BN_CLICKED(IDC_BUTTON_5_0, OnBnClickedButton50)
	ON_BN_CLICKED(IDC_BUTTON_5_1, OnBnClickedButton51)
	ON_BN_CLICKED(IDC_BUTTON_5_2, OnBnClickedButton52)
	ON_BN_CLICKED(IDC_BUTTON_5_3, OnBnClickedButton53)
	ON_BN_CLICKED(IDC_BUTTON_ITEMSEARCH_M, OnBnClickedButtonItemsearchM)
	ON_BN_CLICKED(IDC_BUTTON_ITEMSEARCH_COS, OnBnClickedButtonItemsearchCos)
	ON_BN_CLICKED(IDC_BUTTON_RESET_COS_EXPIRE, OnBnClickedButtonResetCosExpire)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_DELETE, OnBnClickedBtnEditItemDelete)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_UPDATE, OnBnClickedBtnEditItemUpdate)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_CLEAR, OnBnClickedBtnEditItemClear)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_CLEARALL, OnBnClickedBtnEditItemClearall)
END_MESSAGE_MAP()


// CRanManagerGuildLocker message handlers
BOOL CRanManagerGuildLocker::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	for ( int i = 0; i < GEN_SIZE; ++i )
	{
		m_cGenType.InsertString( i, RMComments::m_GenType[i].c_str() );
	}
	m_cGenType.SetCurSel( 0 );

	for ( int i = 0; i < EMR_OPT_SIZE; ++i )
	{
		m_cRandomOp1.InsertString( i, COMMENT::ITEM_RANDOM_OPT[i].c_str() );
		m_cRandomOp2.InsertString( i, COMMENT::ITEM_RANDOM_OPT[i].c_str() );
		m_cRandomOp3.InsertString( i, COMMENT::ITEM_RANDOM_OPT[i].c_str() );
		m_cRandomOp4.InsertString( i, COMMENT::ITEM_RANDOM_OPT[i].c_str() );
	}

	m_cRandomOp1.SetCurSel( 0 );
	m_cRandomOp2.SetCurSel( 0 );
	m_cRandomOp3.SetCurSel( 0 );
	m_cRandomOp4.SetCurSel( 0 );

	SetWin_Enable(this,IDC_BTN_EDIT_ITEM_DELETE,false);
	SetWin_Enable(this,IDC_BTN_EDIT_ITEM_UPDATE,false);

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerGuildLocker::SetGuild(int nGuildNum)
{
	GetGuild(nGuildNum);
	GetGuildMoney(nGuildNum);
	LoadLocker(nGuildNum);
}

void CRanManagerGuildLocker::GetGuild(int nGuildNum)
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
	LOGSCRIPT::LogToFile("GuildLocker.txt","%s--%s",strTIME.c_str(),szTemp);

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

void CRanManagerGuildLocker::GetGuildMoney(int nGuildNum)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

	TCHAR szTemp[1024] = {0};
	
	_snprintf( szTemp, 1024, 
		"SELECT GuMoney,GuIncomeMoney FROM %s.dbo.GuildInfo WITH (NOLOCK) WHERE GuNum =%d "
	,CToolCfg::GetInstance()->szGameDb,nGuildNum);


	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildLocker.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	LONGLONG   llGuildMoney = 0;
    SQLINTEGER cbGuildMoney = SQL_NTS;
	LONGLONG   llGuildIncomeMoney = 0;
    SQLINTEGER cbGuildIncomeMoney = SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	return;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			::SQLGetData(hStmt, 1, SQL_C_SBIGINT,        &llGuildMoney,   0, &cbGuildMoney);
			::SQLGetData(hStmt, 2, SQL_C_SBIGINT,        &llGuildIncomeMoney,   0, &cbGuildIncomeMoney);
		}
		else	break;
		Sleep( 0 );
	}

	CString strMoney;
	strMoney.Format("%I64d",llGuildMoney);
	SetWin_Text ( this, IDC_EDIT_GUMONEY,strMoney);

	strMoney.Format("%I64d",llGuildIncomeMoney);
	SetWin_Text ( this, IDC_EDIT_GUINCOMEMONEY,strMoney);

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerGuildLocker::LoadLocker(int nGuildNum)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)
	CByteStream ByteStream;
	ByteStream.ClearBuffer();

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "SELECT GuStorage FROM  %s.dbo.GuildInfo WITH (NOLOCK) WHERE GuNum=%u"
		,CToolCfg::GetInstance()->szGameDb
		,nGuildNum );
	
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildLocker.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	BYTE pBuffer[DB_IMAGE_BUF_SIZE] = {0};
	SQLINTEGER  lSize=0, lTotalSize=0;

	while ((sReturn = ::SQLFetch(hStmt)) != SQL_NO_DATA) 
	{			
		while (1) 
		{
			::ZeroMemory(pBuffer, DB_IMAGE_BUF_SIZE);
			lSize = 0;
			sReturn = ::SQLGetData(hStmt, 1, SQL_C_BINARY, pBuffer, DB_IMAGE_BUF_SIZE, &lSize);
			if (lSize > 0)
			{
				if (lSize > DB_IMAGE_BUF_SIZE) lSize = DB_IMAGE_BUF_SIZE;
				lTotalSize += lSize;
				ByteStream.WriteBuffer((LPBYTE) pBuffer, lSize);
			}
			if (sReturn == SQL_NO_DATA || lSize == 0)
				break;
			Sleep( 0 );
		}
		if ( lTotalSize < DB_IMAGE_MIN_SIZE )		
			ByteStream.ClearBuffer ();
		Sleep( 0 );
	}

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	if ( ByteStream.IsEmpty() )
	{
		return;
	}

	DWORD dwChannel = 0;
	ByteStream >> dwChannel;
	if ( dwChannel > LOCKER_SIZE )	dwChannel = LOCKER_SIZE;
	
	for ( DWORD i=0; i<dwChannel; ++i )//clear all before adding new data
	{
		m_cStorage[i].DeleteItemAll();
	}

	for ( DWORD i=0; i<dwChannel; ++i )
	{
		BOOL bOk = m_cStorage[i].SETITEM_BYBUFFER ( ByteStream );
		if ( !bOk )		
		{
			return;
		}
	}
	InitLockerInven();
	SetLockerPageState ( this,IDC_BUTTON_P1 );
}

void CRanManagerGuildLocker::InitLockerInven()
{	
	nActiveItem_X = 65535;
	nActiveItem_Y = 65535;

	SetWin_Num_int ( this, IDC_EDIT_PAGE,nActivePage+1 );
	SetWin_Num_int ( this, IDC_EDIT_TOTAL,m_cStorage[nActivePage].CountItemTotal() );

	int nNum = 0;
	TCHAR szTemp[128] = {0};
	for (int X = 0; X < STORAGE_INVEN_X; X++ )
	{
		for (int Y = 0; Y < STORAGE_INVEN_Y; Y++ )
		{
			SINVENITEM* sItem = m_cStorage[nActivePage].FindPosItem(X,Y);
			if (sItem)	_snprintf( szTemp, 128, "%d_%d",sItem->sItemCustom.sNativeID.wMainID,sItem->sItemCustom.sNativeID.wSubID );
			else	_snprintf( szTemp, 128, "%s","Empty" );

			switch (nNum)
			{
				case	0:	SetWin_Text ( this, IDC_BUTTON_0_0,(const TCHAR*)szTemp );
				case	1:	SetWin_Text ( this, IDC_BUTTON_0_1,(const TCHAR*)szTemp );
				case	2:	SetWin_Text ( this, IDC_BUTTON_0_2,(const TCHAR*)szTemp );
				case	3:	SetWin_Text ( this, IDC_BUTTON_0_3,(const TCHAR*)szTemp );
				case	4:	SetWin_Text ( this, IDC_BUTTON_1_0,(const TCHAR*)szTemp );
				case	5:	SetWin_Text ( this, IDC_BUTTON_1_1,(const TCHAR*)szTemp );
				case	6:	SetWin_Text ( this, IDC_BUTTON_1_2,(const TCHAR*)szTemp );
				case	7:	SetWin_Text ( this, IDC_BUTTON_1_3,(const TCHAR*)szTemp );
				case	8:	SetWin_Text ( this, IDC_BUTTON_2_0,(const TCHAR*)szTemp );
				case	9:	SetWin_Text ( this, IDC_BUTTON_2_1,(const TCHAR*)szTemp );
				case	10:	SetWin_Text ( this, IDC_BUTTON_2_2,(const TCHAR*)szTemp );
				case	11:	SetWin_Text ( this, IDC_BUTTON_2_3,(const TCHAR*)szTemp );
				case	12:	SetWin_Text ( this, IDC_BUTTON_3_0,(const TCHAR*)szTemp );
				case	13:	SetWin_Text ( this, IDC_BUTTON_3_1,(const TCHAR*)szTemp );
				case	14:	SetWin_Text ( this, IDC_BUTTON_3_2,(const TCHAR*)szTemp );
				case	15:	SetWin_Text ( this, IDC_BUTTON_3_3,(const TCHAR*)szTemp );
				case	16:	SetWin_Text ( this, IDC_BUTTON_4_0,(const TCHAR*)szTemp );
				case	17:	SetWin_Text ( this, IDC_BUTTON_4_1,(const TCHAR*)szTemp );
				case	18:	SetWin_Text ( this, IDC_BUTTON_4_2,(const TCHAR*)szTemp );
				case	19:	SetWin_Text ( this, IDC_BUTTON_4_3,(const TCHAR*)szTemp );
				case	20:	SetWin_Text ( this, IDC_BUTTON_5_0,(const TCHAR*)szTemp );
				case	21:	SetWin_Text ( this, IDC_BUTTON_5_1,(const TCHAR*)szTemp );
				case	22:	SetWin_Text ( this, IDC_BUTTON_5_2,(const TCHAR*)szTemp );
				case	23:	SetWin_Text ( this, IDC_BUTTON_5_3,(const TCHAR*)szTemp );
			};
			nNum++;
		}
	}
}

void CRanManagerGuildLocker::OnBnClickedBtnEditCancelLocker()
{
	m_pToolTab->ActivePage(GUILDPAGE_MAIN,0);
}

void CRanManagerGuildLocker::OnBnClickedBtnEditSaveLocker()
{
	CByteStream ByteStream;
	LPBYTE pBuffer = NULL;
	DWORD dwSize = 0;
	TCHAR szTemp[128] = {0};
	CString strTemp;

	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	
	{
		MessageBox("Error Connecting to Game DB!","error",MB_OK);
		return;
	}

	//save money
	LONGLONG	llGuMoney = _strtoi64 ( GetWin_Text(this,IDC_EDIT_GUMONEY),NULL,10 );
	LONGLONG	llGuIncomeMoney = _strtoi64 ( GetWin_Text(this,IDC_EDIT_GUINCOMEMONEY),NULL,10 );
	_snprintf( szTemp, 128, "Update %s.dbo.GuildInfo Set GuMoney=%I64d,GuIncomeMoney=%I64d WHERE GuNum=%u",
		CToolCfg::GetInstance()->szGameDb,llGuMoney,llGuIncomeMoney, GetWin_Num_int(this,IDC_EDIT_NUM) );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("GuildLocker.txt","%s--%s",strTIME.c_str(),szTemp);

	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)		
	{
		MessageBox("Error Saving Guild Money!","error",MB_OK);
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	//save locker inven 
	//fucking hard to code!
	ByteStream.ClearBuffer ();
	ByteStream << DWORD(LOCKER_SIZE);
	for ( DWORD i=0; i<LOCKER_SIZE; ++i )	m_cStorage[i].GETITEM_BYBUFFER_FORSTORAGE ( ByteStream );
	ByteStream.GetBuffer(pBuffer, dwSize);
	if (pBuffer != NULL)
	{
		_snprintf( szTemp, 128, "UPDATE %s.dbo.GuildInfo SET GuStorage = ? WHERE (GuNum=%u)", CToolCfg::GetInstance()->szGameDb,GetWin_Num_int(this,IDC_EDIT_NUM) );
		LOGSCRIPT::LogToFile("GuildLocker.txt","%s--%s",strTIME.c_str(),szTemp);

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
			MessageBox("Error Saving Guild Locker Binary!","error",MB_OK);
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
	MessageBox("Done Saving Guild Locker Data!","Info",MB_OK);

	pBuffer = NULL;
	InitLockerInven();
}

void CRanManagerGuildLocker::OnBnClickedButton00(){	ViewLockerItem(0,0);	SetLockerItemState ( this,IDC_BUTTON_0_0 );	}
void CRanManagerGuildLocker::OnBnClickedButton01(){	ViewLockerItem(0,1);	SetLockerItemState ( this,IDC_BUTTON_0_1 );	}
void CRanManagerGuildLocker::OnBnClickedButton02(){	ViewLockerItem(0,2);	SetLockerItemState ( this,IDC_BUTTON_0_2 );	}
void CRanManagerGuildLocker::OnBnClickedButton03(){	ViewLockerItem(0,3);	SetLockerItemState ( this,IDC_BUTTON_0_3 );	}
void CRanManagerGuildLocker::OnBnClickedButton10(){	ViewLockerItem(1,0);	SetLockerItemState ( this,IDC_BUTTON_1_0 );	}
void CRanManagerGuildLocker::OnBnClickedButton11(){	ViewLockerItem(1,1);	SetLockerItemState ( this,IDC_BUTTON_1_1 );	}
void CRanManagerGuildLocker::OnBnClickedButton12(){	ViewLockerItem(1,2);	SetLockerItemState ( this,IDC_BUTTON_1_2 );	}
void CRanManagerGuildLocker::OnBnClickedButton13(){	ViewLockerItem(1,3);	SetLockerItemState ( this,IDC_BUTTON_1_3 );	}
void CRanManagerGuildLocker::OnBnClickedButton20(){	ViewLockerItem(2,0);	SetLockerItemState ( this,IDC_BUTTON_2_0 );	}
void CRanManagerGuildLocker::OnBnClickedButton21(){	ViewLockerItem(2,1);	SetLockerItemState ( this,IDC_BUTTON_2_1 );	}
void CRanManagerGuildLocker::OnBnClickedButton22(){	ViewLockerItem(2,2);	SetLockerItemState ( this,IDC_BUTTON_2_2 );	}
void CRanManagerGuildLocker::OnBnClickedButton23(){	ViewLockerItem(2,3);	SetLockerItemState ( this,IDC_BUTTON_2_3 );	}
void CRanManagerGuildLocker::OnBnClickedButton30(){	ViewLockerItem(3,0);	SetLockerItemState ( this,IDC_BUTTON_3_0 );	}
void CRanManagerGuildLocker::OnBnClickedButton31(){	ViewLockerItem(3,1);	SetLockerItemState ( this,IDC_BUTTON_3_1 );	}
void CRanManagerGuildLocker::OnBnClickedButton32(){	ViewLockerItem(3,2);	SetLockerItemState ( this,IDC_BUTTON_3_2 );	}
void CRanManagerGuildLocker::OnBnClickedButton33(){	ViewLockerItem(3,3);	SetLockerItemState ( this,IDC_BUTTON_3_3 );	}
void CRanManagerGuildLocker::OnBnClickedButton40(){	ViewLockerItem(4,0);	SetLockerItemState ( this,IDC_BUTTON_4_0 );	}
void CRanManagerGuildLocker::OnBnClickedButton41(){	ViewLockerItem(4,1);	SetLockerItemState ( this,IDC_BUTTON_4_1 );	}
void CRanManagerGuildLocker::OnBnClickedButton42(){	ViewLockerItem(4,2);	SetLockerItemState ( this,IDC_BUTTON_4_2 );	}
void CRanManagerGuildLocker::OnBnClickedButton43(){	ViewLockerItem(4,3);	SetLockerItemState ( this,IDC_BUTTON_4_3 );	}
void CRanManagerGuildLocker::OnBnClickedButton50(){	ViewLockerItem(5,0);	SetLockerItemState ( this,IDC_BUTTON_5_0 );	}
void CRanManagerGuildLocker::OnBnClickedButton51(){	ViewLockerItem(5,1);	SetLockerItemState ( this,IDC_BUTTON_5_1 );	}
void CRanManagerGuildLocker::OnBnClickedButton52(){	ViewLockerItem(5,2);	SetLockerItemState ( this,IDC_BUTTON_5_2 );	}
void CRanManagerGuildLocker::OnBnClickedButton53(){	ViewLockerItem(5,3);	SetLockerItemState ( this,IDC_BUTTON_5_3 );	}
void CRanManagerGuildLocker::OnBnClickedButtonP1(){	nActivePage = 0;	SetLockerPageState ( this,IDC_BUTTON_P1 ); InitLockerInven();	ResetLockerItem( 65535,65535 );	}
void CRanManagerGuildLocker::OnBnClickedButtonP2(){	nActivePage = 1;	SetLockerPageState ( this,IDC_BUTTON_P2 ); InitLockerInven();	ResetLockerItem( 65535,65535 );	}
void CRanManagerGuildLocker::OnBnClickedButtonP3(){	nActivePage = 2;	SetLockerPageState ( this,IDC_BUTTON_P3 ); InitLockerInven();	ResetLockerItem( 65535,65535 );	}
void CRanManagerGuildLocker::OnBnClickedButtonP4(){	nActivePage = 3;	SetLockerPageState ( this,IDC_BUTTON_P4 ); InitLockerInven();	ResetLockerItem( 65535,65535 );	}
void CRanManagerGuildLocker::OnBnClickedButtonP5(){	nActivePage = 4;	SetLockerPageState ( this,IDC_BUTTON_P5 ); InitLockerInven();	ResetLockerItem( 65535,65535 );	}

void CRanManagerGuildLocker::SetLockerItemState ( CDialog *pDlg,int nID )
{
	ResetLockerItemState (this);
	CButton *pBtn;
	switch (nID)
	{
	case IDC_BUTTON_0_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_0_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_0_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_0_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_3 );	pBtn->SetState(TRUE);	break;
	};
}

void CRanManagerGuildLocker::ResetLockerItemState ( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_3 );	pBtn->SetState(FALSE);

}

void CRanManagerGuildLocker::SetLockerPageState ( CDialog *pDlg,int nID )
{
	ResetLockerItemState (this);
	ResetLockerPageState (this);
	CButton *pBtn;
	switch (nID)
	{
	case IDC_BUTTON_P1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P5 );	pBtn->SetState(TRUE);	break;
	};
}

void CRanManagerGuildLocker::ResetLockerPageState ( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P5 );	pBtn->SetState(FALSE);
}

void CRanManagerGuildLocker::ViewLockerItem(WORD X,WORD Y)
{
	nActiveItem_X = X;
	nActiveItem_Y = Y;

	SINVENITEM* sItem = m_cStorage[nActivePage].FindPosItem(X,Y);
	if (sItem) 
	{
		SetWin_Enable(this,IDC_BTN_EDIT_ITEM_DELETE,true);
		
		SetWin_Num_int ( this, IDC_EDIT_POS_X,sItem->wPosX);
		SetWin_Num_int ( this, IDC_EDIT_POS_Y,sItem->wPosY);

		SITEM* pItem = GLItemMan::GetInstance().GetItem(sItem->sItemCustom.sNativeID);
		if (pItem ) 
		{
			SetWin_Num_int ( this, IDC_EDIT_MID,pItem->sBasicOp.sNativeID.wMainID);
			SetWin_Num_int ( this, IDC_EDIT_SID,pItem->sBasicOp.sNativeID.wSubID);
			SetWin_Text ( this, IDC_EDIT_NAME,pItem->GetName());
		}
		else
		{
			SetWin_Num_int ( this, IDC_EDIT_MID,sItem->sItemCustom.sNativeID.wMainID);
			SetWin_Num_int ( this, IDC_EDIT_SID,sItem->sItemCustom.sNativeID.wSubID);
			SetWin_Text ( this, IDC_EDIT_NAME,"Unknown Item");
		}

		SetWin_Num_int ( this, IDC_EDIT_MID_COS,sItem->sItemCustom.nidDISGUISE.wMainID);
		SetWin_Num_int ( this, IDC_EDIT_SID_COS,sItem->sItemCustom.nidDISGUISE.wSubID);

		CTimeSpan cSPAN(sItem->sItemCustom.tDISGUISE);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_1, (int)cSPAN.GetDays() );
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_2, (int)cSPAN.GetHours() );
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_3, (int)cSPAN.GetMinutes() );

		SITEM* pCosItem = GLItemMan::GetInstance().GetItem(sItem->sItemCustom.nidDISGUISE);
		if (pCosItem)	SetWin_Text ( this, IDC_EDIT_NAME_COS,pCosItem->GetName());
		else	SetWin_Text ( this, IDC_EDIT_NAME_COS,"Unknown Item");

		SetWin_Num_int ( this, IDC_EDIT_TURN_NUM,sItem->sItemCustom.wTurnNum );
		//SetWin_Combo_Sel ( this, IDC_COMBO_GENTYPE, (int)sItem->sItemCustom.cGenType );
		m_cGenType.SetCurSel((int)sItem->sItemCustom.cGenType);

		TCHAR Gen[100];
		_snprintf( Gen, 100, "%I64d",sItem->sItemCustom.lnGenNum );
		SetWin_Text ( this, IDC_EDIT_GEN_NUM,Gen);

		SetWin_Num_int ( this, IDC_EDIT_CHID,sItem->sItemCustom.cChnID );
		SetWin_Num_int ( this, IDC_EDIT_FLDID,sItem->sItemCustom.cFieldID );

		SetWin_Num_int ( this, IDC_EDIT_DAMAGE,sItem->sItemCustom.cDAMAGE);
		SetWin_Num_int ( this, IDC_EDIT_DEFENSE,sItem->sItemCustom.cDEFENSE);

		SetWin_Num_int ( this, IDC_EDIT_FIRE,sItem->sItemCustom.cRESIST_FIRE);
		SetWin_Num_int ( this, IDC_EDIT_ICE,sItem->sItemCustom.cRESIST_ICE);
		SetWin_Num_int ( this, IDC_EDIT_ELE,sItem->sItemCustom.cRESIST_ELEC);
		SetWin_Num_int ( this, IDC_EDIT_POI,sItem->sItemCustom.cRESIST_POISON);
		SetWin_Num_int ( this, IDC_EDIT_SPI,sItem->sItemCustom.cRESIST_SPIRIT);

		m_cRandomOp1.SetCurSel((int)sItem->sItemCustom.cOptTYPE1);
		m_cRandomOp2.SetCurSel((int)sItem->sItemCustom.cOptTYPE2);
		m_cRandomOp3.SetCurSel((int)sItem->sItemCustom.cOptTYPE3);
		m_cRandomOp4.SetCurSel((int)sItem->sItemCustom.cOptTYPE4);

		SetWin_Num_int ( this, IDC_EDIT_OPTION_VAL1,(int)sItem->sItemCustom.nOptVALUE1);
		SetWin_Num_int ( this, IDC_EDIT_OPTION_VAL2,(int)sItem->sItemCustom.nOptVALUE2);
		SetWin_Num_int ( this, IDC_EDIT_OPTION_VAL3,(int)sItem->sItemCustom.nOptVALUE3);
		SetWin_Num_int ( this, IDC_EDIT_OPTION_VAL4,(int)sItem->sItemCustom.nOptVALUE4);

		SetWin_Num_int ( this, IDC_EDIT_PET_ID,(int)sItem->sItemCustom.dwPetID);
		SetWin_Num_int ( this, IDC_EDIT_VEHICLE_ID,(int)sItem->sItemCustom.dwVehicleID);
		//SetWin_Num_int ( this, IDC_EDIT_OWNER_ID,(int)sItem->sItemCustom.dwOwnerID);
		//SetWin_Num_int ( this, IDC_EDIT_ITEMCOLOR,(int)sItem->sItemCustom.wColor);
	}
	else
	{
		ResetLockerItem( X,Y );
	}

	SetWin_Enable(this,IDC_BTN_EDIT_ITEM_UPDATE,true);
}

void CRanManagerGuildLocker::ResetLockerItem( WORD X,WORD Y )
{
	if ( X == 65535 || Y == 65535 )	SetWin_Enable(this,IDC_BTN_EDIT_ITEM_UPDATE,false);
	else	SetWin_Enable(this,IDC_BTN_EDIT_ITEM_UPDATE,true);

	SetWin_Enable(this,IDC_BTN_EDIT_ITEM_DELETE,false);
	SetWin_Enable(this,IDC_BTN_EDIT_ITEM_UPDATE,false);

	SetWin_Num_int ( this, IDC_EDIT_POS_X,X);
	SetWin_Num_int ( this, IDC_EDIT_POS_Y,Y);
	SetWin_Num_int ( this, IDC_EDIT_MID,65535);
	SetWin_Num_int ( this, IDC_EDIT_SID,65535);
	SetWin_Text ( this, IDC_EDIT_NAME,"NULL");

	SetWin_Num_int ( this, IDC_EDIT_MID_COS,65535);
	SetWin_Num_int ( this, IDC_EDIT_SID_COS,65535);

	SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_1, 0 );
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_2, 0 );
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_3, 0 );

	SetWin_Text ( this, IDC_EDIT_NAME_COS,"NULL");

	SetWin_Num_int ( this, IDC_EDIT_TURN_NUM,0 );
	m_cGenType.SetCurSel(0);

	SetWin_Text ( this, IDC_EDIT_GEN_NUM,"0");

	SetWin_Num_int ( this, IDC_EDIT_CHID,0 );
	SetWin_Num_int ( this, IDC_EDIT_FLDID,0 );

	SetWin_Num_int ( this, IDC_EDIT_DAMAGE,0);
	SetWin_Num_int ( this, IDC_EDIT_DEFENSE,0);

	SetWin_Num_int ( this, IDC_EDIT_FIRE,0);
	SetWin_Num_int ( this, IDC_EDIT_ICE,0);
	SetWin_Num_int ( this, IDC_EDIT_ELE,0);
	SetWin_Num_int ( this, IDC_EDIT_POI,0);
	SetWin_Num_int ( this, IDC_EDIT_SPI,0);

	m_cRandomOp1.SetCurSel(0);
	m_cRandomOp2.SetCurSel(0);
	m_cRandomOp3.SetCurSel(0);
	m_cRandomOp4.SetCurSel(0);

	SetWin_Num_int ( this, IDC_EDIT_OPTION_VAL1,0);
	SetWin_Num_int ( this, IDC_EDIT_OPTION_VAL2,0);
	SetWin_Num_int ( this, IDC_EDIT_OPTION_VAL3,0);
	SetWin_Num_int ( this, IDC_EDIT_OPTION_VAL4,0);

	SetWin_Num_int ( this, IDC_EDIT_PET_ID,0);
	SetWin_Num_int ( this, IDC_EDIT_VEHICLE_ID,0);
	SetWin_Num_int ( this, IDC_EDIT_OWNER_ID,0);
	SetWin_Num_int ( this, IDC_EDIT_ITEMCOLOR,32767);
}

void CRanManagerGuildLocker::OnBnClickedButtonItemsearchM()
{
	CItemSearch sItemSearch;
	sItemSearch.SetMultiple(false);
	if ( IDOK == sItemSearch.DoModal () )
	{
		SITEM*	pItemCheck = GLItemMan::GetInstance().GetItem(sItemSearch.sSelectedItem);
		if ( pItemCheck )
		{
			SetWin_Num_int ( this, IDC_EDIT_MID,sItemSearch.sSelectedItem.wMainID);
			SetWin_Num_int ( this, IDC_EDIT_SID,sItemSearch.sSelectedItem.wSubID);
			SetWin_Text( this,IDC_EDIT_NAME,pItemCheck->GetName() );
		}
	}
}

void CRanManagerGuildLocker::OnBnClickedButtonItemsearchCos()
{
	CItemSearch sItemSearch;
	sItemSearch.SetMultiple(false);
	if ( IDOK == sItemSearch.DoModal () )
	{
		SITEM*	pItemCheck = GLItemMan::GetInstance().GetItem(sItemSearch.sSelectedItem);
		if ( pItemCheck )
		{
			SetWin_Num_int ( this, IDC_EDIT_MID_COS,sItemSearch.sSelectedItem.wMainID);
			SetWin_Num_int ( this, IDC_EDIT_SID_COS,sItemSearch.sSelectedItem.wSubID);
			SetWin_Text( this,IDC_EDIT_NAME_COS,pItemCheck->GetName() );
		}
	}
}

void CRanManagerGuildLocker::OnBnClickedButtonResetCosExpire()
{
	if ( MessageBox ( "This Will Remove the costume, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		SetWin_Num_int ( this, IDC_EDIT_MID_COS,65535);
		SetWin_Num_int ( this, IDC_EDIT_SID_COS,65535);

		SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_1, 0 );
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_2, 0 );
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_3, 0 );
		SetWin_Text ( this, IDC_EDIT_NAME_COS,"NULL");
	}
}

void CRanManagerGuildLocker::OnBnClickedBtnEditItemDelete()
{
	if ( MessageBox ( "Do You Want To Delete Item?", "Question", MB_YESNO ) == IDYES )
	{
		int X = GetWin_Num_int(this,IDC_EDIT_POS_X);
		int Y = GetWin_Num_int(this,IDC_EDIT_POS_Y);
		m_cStorage[nActivePage].DeleteItem(X,Y);
		InitLockerInven();
		ResetLockerItem( X,Y );
	}
}

void CRanManagerGuildLocker::OnBnClickedBtnEditItemUpdate()
{
	if ( MessageBox ( "Update Changes to This Item?", "Question", MB_YESNO ) == IDYES )
	{
		SITEM*  sItemCheck = GLItemMan::GetInstance().GetItem(GetWin_Num_int(this,IDC_EDIT_MID),GetWin_Num_int(this,IDC_EDIT_SID));
		if (!sItemCheck)
		{
			MessageBox("Invalid Item ID! Recheck Item MID and SID","Item Error",MB_OK);
			return;
		}

		SITEMCUSTOM	pItemUpdate;
		pItemUpdate.sNativeID = sItemCheck->sBasicOp.sNativeID;
		SNATIVEID sCosID;
		sCosID.wMainID = GetWin_Num_int(this,IDC_EDIT_MID_COS);
		sCosID.wSubID = GetWin_Num_int(this,IDC_EDIT_SID_COS);
		pItemUpdate.nidDISGUISE = sCosID;
		CTime cTIME_CUR;
		pItemUpdate.tBORNTIME = cTIME_CUR.GetTime();

		CTimeSpan cSPAN(
			GetWin_Num_int(this,IDC_EDIT_LOCKER_COS_1),
			GetWin_Num_int(this,IDC_EDIT_LOCKER_COS_2),
			GetWin_Num_int(this,IDC_EDIT_LOCKER_COS_3),
			0);
		pItemUpdate.tDISGUISE = cSPAN.GetTimeSpan();
		pItemUpdate.lnGenNum = _strtoi64(GetWin_Text(this,IDC_EDIT_GEN_NUM ),NULL,10);
		pItemUpdate.wTurnNum = (WORD)GetWin_Num_int(this,IDC_EDIT_TURN_NUM);
		pItemUpdate.cGenType = (BYTE)m_cGenType.GetCurSel();
		if ( pItemUpdate.cGenType == EMGEN_GMEDIT || pItemUpdate.cGenType == EMGEN_GMEDIT2)	SetWin_Num_int(this, IDC_EDIT_FLDID ,255 );
		pItemUpdate.cChnID = (BYTE)GetWin_Num_int(this,IDC_EDIT_CHID);
		pItemUpdate.cFieldID = (BYTE)GetWin_Num_int(this,IDC_EDIT_FLDID);
		pItemUpdate.cDAMAGE = (BYTE)GetWin_Num_int(this,IDC_EDIT_DAMAGE);
		pItemUpdate.cDEFENSE = (BYTE)GetWin_Num_int(this,IDC_EDIT_DEFENSE);
		pItemUpdate.cRESIST_FIRE = (BYTE)GetWin_Num_int(this,IDC_EDIT_FIRE);
		pItemUpdate.cRESIST_ICE = (BYTE)GetWin_Num_int(this,IDC_EDIT_ICE);
		pItemUpdate.cRESIST_ELEC = (BYTE)GetWin_Num_int(this,IDC_EDIT_ELE);
		pItemUpdate.cRESIST_POISON = (BYTE)GetWin_Num_int(this,IDC_EDIT_POI);
		pItemUpdate.cRESIST_SPIRIT = (BYTE)GetWin_Num_int(this,IDC_EDIT_SPI);
		pItemUpdate.cOptTYPE1 = (BYTE)m_cRandomOp1.GetCurSel();
		pItemUpdate.cOptTYPE2 = (BYTE)m_cRandomOp2.GetCurSel();
		pItemUpdate.cOptTYPE3 = (BYTE)m_cRandomOp3.GetCurSel();
		pItemUpdate.cOptTYPE4 = (BYTE)m_cRandomOp4.GetCurSel();
		pItemUpdate.nOptVALUE1 = (short)GetWin_Num_int(this,IDC_EDIT_OPTION_VAL1);
		pItemUpdate.nOptVALUE2 = (short)GetWin_Num_int(this,IDC_EDIT_OPTION_VAL2);
		pItemUpdate.nOptVALUE3 = (short)GetWin_Num_int(this,IDC_EDIT_OPTION_VAL3);
		pItemUpdate.nOptVALUE4 = (short)GetWin_Num_int(this,IDC_EDIT_OPTION_VAL4);
		pItemUpdate.dwPetID = GetWin_Num_int(this,IDC_EDIT_PET_ID);
		pItemUpdate.dwVehicleID = GetWin_Num_int(this,IDC_EDIT_VEHICLE_ID);
		//pItemUpdate.dwOwnerID = GetWin_Num_int(this,IDC_EDIT_OWNER_ID);
		//pItemUpdate.wColor = GetWin_Num_int(this,IDC_EDIT_ITEMCOLOR);


		m_cStorage[nActivePage].DeleteItem(nActiveItem_X,nActiveItem_Y);
		if (m_cStorage[nActivePage].InsertItem(pItemUpdate,nActiveItem_X,nActiveItem_Y) )	MessageBox("Done Updating Item","Info",MB_OK);
		else	MessageBox("Error! Updating Item","Info",MB_OK);	

		int nOldX = nActiveItem_X;
		int nOldY = nActiveItem_Y;
		InitLockerInven();
		ViewLockerItem(nOldX,nOldY);
	}
}

void CRanManagerGuildLocker::OnBnClickedBtnEditItemClear()
{
	if ( MessageBox ( "Do You Want To Delete All Item In This Page?", "Question", MB_YESNO ) == IDYES )
	{
		m_cStorage[nActivePage].DeleteItemAll();
		InitLockerInven();
		ResetLockerItem( 65535,65535 );
	}
}

void CRanManagerGuildLocker::OnBnClickedBtnEditItemClearall()
{
	if ( MessageBox ( "Do You Want To Delete All Item In All Page?", "Question", MB_YESNO ) == IDYES )
	{
		for (int i =0; i<LOCKER_SIZE ; i++ )
		{
			m_cStorage[i].DeleteItemAll();
		}
		InitLockerInven();
		ResetLockerItem( 65535,65535 );	
	}
}
