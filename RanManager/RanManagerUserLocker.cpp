// RanManagerUserLocker.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerUserLocker.h"
#include "RanManagerUserTab.h"

#include "COdbc.h"
#include "CCfg.h"
#include "s_NetGlobal.h"
#include "china_md5.h"
#include "Calendar.h"
#include "ItemSearch.h"
#include "EtcFunction.h"
#include "LogScript.h"
#include "RanManagerComments.h"
#include ".\ranmanageruserlocker.h"
#include "../NetServerLib/s_DbBase.h"
#include "../EngineLib/Common/ByteStream.h"


// CRanManagerUserLocker dialog
IMPLEMENT_DYNAMIC(CRanManagerUserLocker, CPropertyPage)
CRanManagerUserLocker::CRanManagerUserLocker(LOGFONT logfont)
	: CPropertyPage(CRanManagerUserLocker::IDD)
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

CRanManagerUserLocker::~CRanManagerUserLocker()
{
}

void CRanManagerUserLocker::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GENTYPE, m_cGenType );
	DDX_Control(pDX, IDC_COMBO_OPTION1, m_cRandomOp1 );
	DDX_Control(pDX, IDC_COMBO_OPTION2, m_cRandomOp2 );
	DDX_Control(pDX, IDC_COMBO_OPTION3, m_cRandomOp3 );
	DDX_Control(pDX, IDC_COMBO_OPTION4, m_cRandomOp4 );
}

BEGIN_MESSAGE_MAP(CRanManagerUserLocker, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SET1, OnBnClickedButtonSet1)
	ON_BN_CLICKED(IDC_BUTTON_SET2, OnBnClickedButtonSet2)
	ON_BN_CLICKED(IDC_BUTTON_SET3, OnBnClickedButtonSet3)
	ON_BN_CLICKED(IDC_BUTTON_RESET1, OnBnClickedButtonReset1)
	ON_BN_CLICKED(IDC_BUTTON_RESET2, OnBnClickedButtonReset2)
	ON_BN_CLICKED(IDC_BUTTON_RESET3, OnBnClickedButtonReset3)
	ON_BN_CLICKED(IDC_BUTTON_0_0, OnBnClickedButton00)
	ON_BN_CLICKED(IDC_BUTTON_0_1, OnBnClickedButton01)
	ON_BN_CLICKED(IDC_BUTTON_0_2, OnBnClickedButton02)
	ON_BN_CLICKED(IDC_BUTTON_0_3, OnBnClickedButton03)
	ON_BN_CLICKED(IDC_BUTTON_0_4, OnBnClickedButton04)
	ON_BN_CLICKED(IDC_BUTTON_0_5, OnBnClickedButton05)
	ON_BN_CLICKED(IDC_BUTTON_0_6, OnBnClickedButton06)
	ON_BN_CLICKED(IDC_BUTTON_0_7, OnBnClickedButton07)
	ON_BN_CLICKED(IDC_BUTTON_0_8, OnBnClickedButton08)
	ON_BN_CLICKED(IDC_BUTTON_0_9, OnBnClickedButton09)
	ON_BN_CLICKED(IDC_BUTTON_1_0, OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON_1_1, OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON_1_2, OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON_1_3, OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON_1_4, OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON_1_5, OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON_1_6, OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON_1_7, OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON_1_8, OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON_1_9, OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON_2_0, OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON_2_1, OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON_2_2, OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON_2_3, OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON_2_4, OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON_2_5, OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON_2_6, OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON_2_7, OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON_2_8, OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON_2_9, OnBnClickedButton29)
	ON_BN_CLICKED(IDC_BUTTON_3_0, OnBnClickedButton30)
	ON_BN_CLICKED(IDC_BUTTON_3_1, OnBnClickedButton31)
	ON_BN_CLICKED(IDC_BUTTON_3_2, OnBnClickedButton32)
	ON_BN_CLICKED(IDC_BUTTON_3_3, OnBnClickedButton33)
	ON_BN_CLICKED(IDC_BUTTON_3_4, OnBnClickedButton34)
	ON_BN_CLICKED(IDC_BUTTON_3_5, OnBnClickedButton35)
	ON_BN_CLICKED(IDC_BUTTON_3_6, OnBnClickedButton36)
	ON_BN_CLICKED(IDC_BUTTON_3_7, OnBnClickedButton37)
	ON_BN_CLICKED(IDC_BUTTON_3_8, OnBnClickedButton38)
	ON_BN_CLICKED(IDC_BUTTON_3_9, OnBnClickedButton39)
	ON_BN_CLICKED(IDC_BUTTON_4_0, OnBnClickedButton40)
	ON_BN_CLICKED(IDC_BUTTON_4_1, OnBnClickedButton41)
	ON_BN_CLICKED(IDC_BUTTON_4_2, OnBnClickedButton42)
	ON_BN_CLICKED(IDC_BUTTON_4_3, OnBnClickedButton43)
	ON_BN_CLICKED(IDC_BUTTON_4_4, OnBnClickedButton44)
	ON_BN_CLICKED(IDC_BUTTON_4_5, OnBnClickedButton45)
	ON_BN_CLICKED(IDC_BUTTON_4_6, OnBnClickedButton46)
	ON_BN_CLICKED(IDC_BUTTON_4_7, OnBnClickedButton47)
	ON_BN_CLICKED(IDC_BUTTON_4_8, OnBnClickedButton48)
	ON_BN_CLICKED(IDC_BUTTON_4_9, OnBnClickedButton49)
	ON_BN_CLICKED(IDC_BUTTON_5_0, OnBnClickedButton50)
	ON_BN_CLICKED(IDC_BUTTON_5_1, OnBnClickedButton51)
	ON_BN_CLICKED(IDC_BUTTON_5_2, OnBnClickedButton52)
	ON_BN_CLICKED(IDC_BUTTON_5_3, OnBnClickedButton53)
	ON_BN_CLICKED(IDC_BUTTON_5_4, OnBnClickedButton54)
	ON_BN_CLICKED(IDC_BUTTON_5_5, OnBnClickedButton55)
	ON_BN_CLICKED(IDC_BUTTON_5_6, OnBnClickedButton56)
	ON_BN_CLICKED(IDC_BUTTON_5_7, OnBnClickedButton57)
	ON_BN_CLICKED(IDC_BUTTON_5_8, OnBnClickedButton58)
	ON_BN_CLICKED(IDC_BUTTON_5_9, OnBnClickedButton59)
	ON_BN_CLICKED(IDC_BUTTON_P1, OnBnClickedButtonP1)
	ON_BN_CLICKED(IDC_BUTTON_P2, OnBnClickedButtonP2)
	ON_BN_CLICKED(IDC_BUTTON_P3, OnBnClickedButtonP3)
	ON_BN_CLICKED(IDC_BUTTON_P4, OnBnClickedButtonP4)
	ON_BN_CLICKED(IDC_BUTTON_P5, OnBnClickedButtonP5)
	ON_BN_CLICKED(IDC_BUTTON_ITEMSEARCH_M, OnBnClickedButtonItemsearchM)
	ON_BN_CLICKED(IDC_BUTTON_ITEMSEARCH_COS, OnBnClickedButtonItemsearchCos)
	ON_CBN_SELCHANGE(IDC_COMBO_GENTYPE, OnCbnSelchangeComboGentype)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_UPDATE, OnBnClickedBtnEditItemUpdate)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_DELETE, OnBnClickedBtnEditItemDelete)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_CLEAR, OnBnClickedBtnEditItemClear)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_CLEARALL, OnBnClickedBtnEditItemClearall)
	ON_BN_CLICKED(IDC_BTN_EDIT_CANCEL_LOCKER, OnBnClickedBtnEditCancelLocker)
	ON_BN_CLICKED(IDC_BUTTON_RESET_COS_EXPIRE, OnBnClickedButtonResetCosExpire)
	ON_BN_CLICKED(IDC_BTN_EDIT_SAVE_LOCKER, OnBnClickedBtnEditSaveLocker)
	ON_BN_CLICKED(IDC_BUTTON_0_4, OnBnClickedButton04)
END_MESSAGE_MAP()


// CRanManagerUserLocker message handlers
BOOL CRanManagerUserLocker::OnInitDialog()
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

void CRanManagerUserLocker::SetUser(int nUser)
{
	LoadUser(nUser);
	LoadLocker(nUser);
	LoadLockerBinary(nUser);
}

void CRanManagerUserLocker::LoadUser(int nUser)
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
	LOGSCRIPT::LogToFile("UserLocker.txt","%s--%s",strTIME.c_str(),szTemp);
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
			SetWin_Num_int ( this, IDC_EDIT_NUM,nUser);
			SetWin_Text ( this, IDC_EDIT_ID,(const TCHAR*)szCharId );
		}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerUserLocker::LoadLocker(int nUser)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	TCHAR szTemp[128] = {0};
	_snprintf( szTemp, 128, "SELECT UserMoney, ChaStorage2, ChaStorage3, ChaStorage4 FROM  %s.dbo.UserInven WITH (NOLOCK) WHERE UserNum=%u"
		,CToolCfg::GetInstance()->szGameDb
		,nUser );
	
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("UserLocker.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	LONGLONG   llUserMoney = 0;
    SQLINTEGER cbUserMoney = SQL_NTS;
    TIMESTAMP_STRUCT sStorageDate2; SQLINTEGER cbStorageDate2 = SQL_NTS;
    TIMESTAMP_STRUCT sStorageDate3; SQLINTEGER cbStorageDate3 = SQL_NTS;
    TIMESTAMP_STRUCT sStorageDate4; SQLINTEGER cbStorageDate4 = SQL_NTS;

	while(true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)
        {
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
		}

 		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{	
            ::SQLGetData(hStmt, 1, SQL_C_SBIGINT,        &llUserMoney,   0, &cbUserMoney);
            ::SQLGetData(hStmt, 2, SQL_C_TYPE_TIMESTAMP, &sStorageDate2, 0, &cbStorageDate2);
            ::SQLGetData(hStmt, 3, SQL_C_TYPE_TIMESTAMP, &sStorageDate3, 0, &cbStorageDate3);
            ::SQLGetData(hStmt, 4, SQL_C_TYPE_TIMESTAMP, &sStorageDate4, 0, &cbStorageDate4);

			CString strMoney;
			strMoney.Format("%I64d",llUserMoney);
			SetWin_Text ( this, IDC_EDIT_USERMONEY,strMoney);

			SetWin_Num_int ( this, IDC_EDIT_LOCKER1_1,sStorageDate2.day);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER1_2,sStorageDate2.month);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER1_3,sStorageDate2.year);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER1_4,sStorageDate2.hour);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER1_5,sStorageDate2.minute);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER1_6,sStorageDate2.second);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER2_1,sStorageDate3.day);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER2_2,sStorageDate3.month);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER2_3,sStorageDate3.year);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER2_4,sStorageDate3.hour);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER2_5,sStorageDate3.minute);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER2_6,sStorageDate3.second);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER3_1,sStorageDate4.day);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER3_2,sStorageDate4.month);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER3_3,sStorageDate4.year);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER3_4,sStorageDate4.hour);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER3_5,sStorageDate4.minute);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER3_6,sStorageDate4.second);
		}
		else
		{
			break;		
		}
		Sleep( 0 );
	}

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerUserLocker::LoadLockerBinary(int nUser)
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
	_snprintf( szTemp, 128, "SELECT UserInven FROM  %s.dbo.UserInven WITH (NOLOCK) WHERE UserNum=%u"
		,CToolCfg::GetInstance()->szGameDb
		,nUser );
	
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("UserLocker.txt","%s--%s",strTIME.c_str(),szTemp);
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

void CRanManagerUserLocker::InitLockerInven()
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
				case	4:	SetWin_Text ( this, IDC_BUTTON_0_4,(const TCHAR*)szTemp );
				case	5:	SetWin_Text ( this, IDC_BUTTON_0_5,(const TCHAR*)szTemp );
				case	6:	SetWin_Text ( this, IDC_BUTTON_0_6,(const TCHAR*)szTemp );
				case	7:	SetWin_Text ( this, IDC_BUTTON_0_7,(const TCHAR*)szTemp );
				case	8:	SetWin_Text ( this, IDC_BUTTON_0_8,(const TCHAR*)szTemp );
				case	9:	SetWin_Text ( this, IDC_BUTTON_0_9,(const TCHAR*)szTemp );

				case	10:	SetWin_Text ( this, IDC_BUTTON_1_0,(const TCHAR*)szTemp );
				case	11:	SetWin_Text ( this, IDC_BUTTON_1_1,(const TCHAR*)szTemp );
				case	12:	SetWin_Text ( this, IDC_BUTTON_1_2,(const TCHAR*)szTemp );
				case	13:	SetWin_Text ( this, IDC_BUTTON_1_3,(const TCHAR*)szTemp );
				case	14:	SetWin_Text ( this, IDC_BUTTON_1_4,(const TCHAR*)szTemp );
				case	15:	SetWin_Text ( this, IDC_BUTTON_1_5,(const TCHAR*)szTemp );
				case	16:	SetWin_Text ( this, IDC_BUTTON_1_6,(const TCHAR*)szTemp );
				case	17:	SetWin_Text ( this, IDC_BUTTON_1_7,(const TCHAR*)szTemp );
				case	18:	SetWin_Text ( this, IDC_BUTTON_1_8,(const TCHAR*)szTemp );
				case	19:	SetWin_Text ( this, IDC_BUTTON_1_9,(const TCHAR*)szTemp );


				case	20:	SetWin_Text ( this, IDC_BUTTON_2_0,(const TCHAR*)szTemp );
				case	21:	SetWin_Text ( this, IDC_BUTTON_2_1,(const TCHAR*)szTemp );
				case	22:	SetWin_Text ( this, IDC_BUTTON_2_2,(const TCHAR*)szTemp );
				case	23:	SetWin_Text ( this, IDC_BUTTON_2_3,(const TCHAR*)szTemp );
				case	24:	SetWin_Text ( this, IDC_BUTTON_2_4,(const TCHAR*)szTemp );
				case	25:	SetWin_Text ( this, IDC_BUTTON_2_5,(const TCHAR*)szTemp );
				case	26:	SetWin_Text ( this, IDC_BUTTON_2_6,(const TCHAR*)szTemp );
				case	27:	SetWin_Text ( this, IDC_BUTTON_2_7,(const TCHAR*)szTemp );
				case	28:	SetWin_Text ( this, IDC_BUTTON_2_8,(const TCHAR*)szTemp );
				case	29:	SetWin_Text ( this, IDC_BUTTON_2_9,(const TCHAR*)szTemp );

				case	30:	SetWin_Text ( this, IDC_BUTTON_3_0,(const TCHAR*)szTemp );
				case	31:	SetWin_Text ( this, IDC_BUTTON_3_1,(const TCHAR*)szTemp );
				case	32:	SetWin_Text ( this, IDC_BUTTON_3_2,(const TCHAR*)szTemp );
				case	33:	SetWin_Text ( this, IDC_BUTTON_3_3,(const TCHAR*)szTemp );
				case	34:	SetWin_Text ( this, IDC_BUTTON_3_4,(const TCHAR*)szTemp );
				case	35:	SetWin_Text ( this, IDC_BUTTON_3_5,(const TCHAR*)szTemp );
				case	36:	SetWin_Text ( this, IDC_BUTTON_3_6,(const TCHAR*)szTemp );
				case	37:	SetWin_Text ( this, IDC_BUTTON_3_7,(const TCHAR*)szTemp );
				case	38:	SetWin_Text ( this, IDC_BUTTON_3_8,(const TCHAR*)szTemp );
				case	39:	SetWin_Text ( this, IDC_BUTTON_3_9,(const TCHAR*)szTemp );

				case	40:	SetWin_Text ( this, IDC_BUTTON_4_0,(const TCHAR*)szTemp );
				case	41:	SetWin_Text ( this, IDC_BUTTON_4_1,(const TCHAR*)szTemp );
				case	42:	SetWin_Text ( this, IDC_BUTTON_4_2,(const TCHAR*)szTemp );
				case	43:	SetWin_Text ( this, IDC_BUTTON_4_3,(const TCHAR*)szTemp );
				case	44:	SetWin_Text ( this, IDC_BUTTON_4_4,(const TCHAR*)szTemp );
				case	45:	SetWin_Text ( this, IDC_BUTTON_4_5,(const TCHAR*)szTemp );
				case	46:	SetWin_Text ( this, IDC_BUTTON_4_6,(const TCHAR*)szTemp );
				case	47:	SetWin_Text ( this, IDC_BUTTON_4_7,(const TCHAR*)szTemp );
				case	48:	SetWin_Text ( this, IDC_BUTTON_4_8,(const TCHAR*)szTemp );
				case	49:	SetWin_Text ( this, IDC_BUTTON_4_9,(const TCHAR*)szTemp );

				case	50:	SetWin_Text ( this, IDC_BUTTON_5_0,(const TCHAR*)szTemp );
				case	51:	SetWin_Text ( this, IDC_BUTTON_5_1,(const TCHAR*)szTemp );
				case	52:	SetWin_Text ( this, IDC_BUTTON_5_2,(const TCHAR*)szTemp );
				case	53:	SetWin_Text ( this, IDC_BUTTON_5_3,(const TCHAR*)szTemp );
				case	54:	SetWin_Text ( this, IDC_BUTTON_5_4,(const TCHAR*)szTemp );
				case	55:	SetWin_Text ( this, IDC_BUTTON_5_5,(const TCHAR*)szTemp );
				case	56:	SetWin_Text ( this, IDC_BUTTON_5_6,(const TCHAR*)szTemp );
				case	57:	SetWin_Text ( this, IDC_BUTTON_5_7,(const TCHAR*)szTemp );
				case	58:	SetWin_Text ( this, IDC_BUTTON_5_8,(const TCHAR*)szTemp );
				case	59:	SetWin_Text ( this, IDC_BUTTON_5_9,(const TCHAR*)szTemp );
			};
			nNum++;
		}
	}
}

void CRanManagerUserLocker::OnBnClickedButtonSet1()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay = GetWin_Num_int ( this, IDC_EDIT_LOCKER1_1 );
	sNewTime.wMonth = GetWin_Num_int ( this, IDC_EDIT_LOCKER1_2 );
	sNewTime.wYear = GetWin_Num_int ( this, IDC_EDIT_LOCKER1_3 );
	sNewTime.wHour = GetWin_Num_int ( this, IDC_EDIT_LOCKER1_4 );
	sNewTime.wMinute = GetWin_Num_int ( this, IDC_EDIT_LOCKER1_5 );
	sNewTime.wSecond = GetWin_Num_int ( this, IDC_EDIT_LOCKER1_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_LOCKER1_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER1_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER1_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER1_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER1_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER1_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerUserLocker::OnBnClickedButtonSet2()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay = GetWin_Num_int ( this, IDC_EDIT_LOCKER2_1 );
	sNewTime.wMonth = GetWin_Num_int ( this, IDC_EDIT_LOCKER2_2 );
	sNewTime.wYear = GetWin_Num_int ( this, IDC_EDIT_LOCKER2_3 );
	sNewTime.wHour = GetWin_Num_int ( this, IDC_EDIT_LOCKER2_4 );
	sNewTime.wMinute = GetWin_Num_int ( this, IDC_EDIT_LOCKER2_5 );
	sNewTime.wSecond = GetWin_Num_int ( this, IDC_EDIT_LOCKER2_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_LOCKER2_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER2_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER2_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER2_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER2_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER2_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerUserLocker::OnBnClickedButtonSet3()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay = GetWin_Num_int ( this, IDC_EDIT_LOCKER3_1 );
	sNewTime.wMonth = GetWin_Num_int ( this, IDC_EDIT_LOCKER3_2 );
	sNewTime.wYear = GetWin_Num_int ( this, IDC_EDIT_LOCKER3_3 );
	sNewTime.wHour = GetWin_Num_int ( this, IDC_EDIT_LOCKER3_4 );
	sNewTime.wMinute = GetWin_Num_int ( this, IDC_EDIT_LOCKER3_5 );
	sNewTime.wSecond = GetWin_Num_int ( this, IDC_EDIT_LOCKER3_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_LOCKER3_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER3_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER3_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER3_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER3_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER3_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerUserLocker::OnBnClickedButtonReset1()
{
	SetWin_Num_int ( this, IDC_EDIT_LOCKER1_1,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER1_2,2);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER1_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER1_4,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER1_5,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER1_6,1);
}

void CRanManagerUserLocker::OnBnClickedButtonReset2()
{
	SetWin_Num_int ( this, IDC_EDIT_LOCKER2_1,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER2_2,2);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER2_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER2_4,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER2_5,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER2_6,1);
}

void CRanManagerUserLocker::OnBnClickedButtonReset3()
{
	SetWin_Num_int ( this, IDC_EDIT_LOCKER3_1,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER3_2,2);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER3_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER3_4,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER3_5,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER3_6,1);
}

void CRanManagerUserLocker::ViewLockerItem(WORD X,WORD Y)
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

void CRanManagerUserLocker::ResetLockerItem( WORD X,WORD Y )
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
	//SetWin_Num_int ( this, IDC_EDIT_ITEMCOLOR,32767);
}

void CRanManagerUserLocker::OnBnClickedButton00(){	ViewLockerItem(0,0);	SetLockerItemState ( this,IDC_BUTTON_0_0 );	}
void CRanManagerUserLocker::OnBnClickedButton01(){	ViewLockerItem(0,1);	SetLockerItemState ( this,IDC_BUTTON_0_1 );	}
void CRanManagerUserLocker::OnBnClickedButton02(){	ViewLockerItem(0,2);	SetLockerItemState ( this,IDC_BUTTON_0_2 );	}
void CRanManagerUserLocker::OnBnClickedButton03(){	ViewLockerItem(0,3);	SetLockerItemState ( this,IDC_BUTTON_0_3 );	}
void CRanManagerUserLocker::OnBnClickedButton04(){	ViewLockerItem(0,4);	SetLockerItemState ( this,IDC_BUTTON_0_4 );	}
void CRanManagerUserLocker::OnBnClickedButton05(){	ViewLockerItem(0,5);	SetLockerItemState ( this,IDC_BUTTON_0_5 );	}
void CRanManagerUserLocker::OnBnClickedButton06(){	ViewLockerItem(0,6);	SetLockerItemState ( this,IDC_BUTTON_0_6 );	}
void CRanManagerUserLocker::OnBnClickedButton07(){	ViewLockerItem(0,7);	SetLockerItemState ( this,IDC_BUTTON_0_7 );	}
void CRanManagerUserLocker::OnBnClickedButton08(){	ViewLockerItem(0,8);	SetLockerItemState ( this,IDC_BUTTON_0_8 );	}
void CRanManagerUserLocker::OnBnClickedButton09(){	ViewLockerItem(0,9);	SetLockerItemState ( this,IDC_BUTTON_0_9 );	}

void CRanManagerUserLocker::OnBnClickedButton10(){	ViewLockerItem(1,0);	SetLockerItemState ( this,IDC_BUTTON_1_0 );	}
void CRanManagerUserLocker::OnBnClickedButton11(){	ViewLockerItem(1,1);	SetLockerItemState ( this,IDC_BUTTON_1_1 );	}
void CRanManagerUserLocker::OnBnClickedButton12(){	ViewLockerItem(1,2);	SetLockerItemState ( this,IDC_BUTTON_1_2 );	}
void CRanManagerUserLocker::OnBnClickedButton13(){	ViewLockerItem(1,3);	SetLockerItemState ( this,IDC_BUTTON_1_3 );	}
void CRanManagerUserLocker::OnBnClickedButton14(){	ViewLockerItem(1,4);	SetLockerItemState ( this,IDC_BUTTON_1_4 );	}
void CRanManagerUserLocker::OnBnClickedButton15(){	ViewLockerItem(1,5);	SetLockerItemState ( this,IDC_BUTTON_1_5 );	}
void CRanManagerUserLocker::OnBnClickedButton16(){	ViewLockerItem(1,6);	SetLockerItemState ( this,IDC_BUTTON_1_6 );	}
void CRanManagerUserLocker::OnBnClickedButton17(){	ViewLockerItem(1,7);	SetLockerItemState ( this,IDC_BUTTON_1_7 );	}
void CRanManagerUserLocker::OnBnClickedButton18(){	ViewLockerItem(1,8);	SetLockerItemState ( this,IDC_BUTTON_1_8 );	}
void CRanManagerUserLocker::OnBnClickedButton19(){	ViewLockerItem(1,9);	SetLockerItemState ( this,IDC_BUTTON_1_9 );	}

void CRanManagerUserLocker::OnBnClickedButton20(){	ViewLockerItem(2,0);	SetLockerItemState ( this,IDC_BUTTON_2_0 );	}
void CRanManagerUserLocker::OnBnClickedButton21(){	ViewLockerItem(2,1);	SetLockerItemState ( this,IDC_BUTTON_2_1 );	}
void CRanManagerUserLocker::OnBnClickedButton22(){	ViewLockerItem(2,2);	SetLockerItemState ( this,IDC_BUTTON_2_2 );	}
void CRanManagerUserLocker::OnBnClickedButton23(){	ViewLockerItem(2,3);	SetLockerItemState ( this,IDC_BUTTON_2_3 );	}
void CRanManagerUserLocker::OnBnClickedButton24(){	ViewLockerItem(2,4);	SetLockerItemState ( this,IDC_BUTTON_2_4 );	}
void CRanManagerUserLocker::OnBnClickedButton25(){	ViewLockerItem(2,5);	SetLockerItemState ( this,IDC_BUTTON_2_5 );	}
void CRanManagerUserLocker::OnBnClickedButton26(){	ViewLockerItem(2,6);	SetLockerItemState ( this,IDC_BUTTON_2_6 );	}
void CRanManagerUserLocker::OnBnClickedButton27(){	ViewLockerItem(2,7);	SetLockerItemState ( this,IDC_BUTTON_2_7 );	}
void CRanManagerUserLocker::OnBnClickedButton28(){	ViewLockerItem(2,8);	SetLockerItemState ( this,IDC_BUTTON_2_8 );	}
void CRanManagerUserLocker::OnBnClickedButton29(){	ViewLockerItem(2,9);	SetLockerItemState ( this,IDC_BUTTON_2_9 );	}

void CRanManagerUserLocker::OnBnClickedButton30(){	ViewLockerItem(3,0);	SetLockerItemState ( this,IDC_BUTTON_3_0 );	}
void CRanManagerUserLocker::OnBnClickedButton31(){	ViewLockerItem(3,1);	SetLockerItemState ( this,IDC_BUTTON_3_1 );	}
void CRanManagerUserLocker::OnBnClickedButton32(){	ViewLockerItem(3,2);	SetLockerItemState ( this,IDC_BUTTON_3_2 );	}
void CRanManagerUserLocker::OnBnClickedButton33(){	ViewLockerItem(3,3);	SetLockerItemState ( this,IDC_BUTTON_3_3 );	}
void CRanManagerUserLocker::OnBnClickedButton34(){	ViewLockerItem(3,4);	SetLockerItemState ( this,IDC_BUTTON_3_4 );	}
void CRanManagerUserLocker::OnBnClickedButton35(){	ViewLockerItem(3,5);	SetLockerItemState ( this,IDC_BUTTON_3_5 );	}
void CRanManagerUserLocker::OnBnClickedButton36(){	ViewLockerItem(3,6);	SetLockerItemState ( this,IDC_BUTTON_3_6 );	}
void CRanManagerUserLocker::OnBnClickedButton37(){	ViewLockerItem(3,7);	SetLockerItemState ( this,IDC_BUTTON_3_7 );	}
void CRanManagerUserLocker::OnBnClickedButton38(){	ViewLockerItem(3,8);	SetLockerItemState ( this,IDC_BUTTON_3_8 );	}
void CRanManagerUserLocker::OnBnClickedButton39(){	ViewLockerItem(3,9);	SetLockerItemState ( this,IDC_BUTTON_3_9 );	}

void CRanManagerUserLocker::OnBnClickedButton40(){	ViewLockerItem(4,0);	SetLockerItemState ( this,IDC_BUTTON_4_0 );	}
void CRanManagerUserLocker::OnBnClickedButton41(){	ViewLockerItem(4,1);	SetLockerItemState ( this,IDC_BUTTON_4_1 );	}
void CRanManagerUserLocker::OnBnClickedButton42(){	ViewLockerItem(4,2);	SetLockerItemState ( this,IDC_BUTTON_4_2 );	}
void CRanManagerUserLocker::OnBnClickedButton43(){	ViewLockerItem(4,3);	SetLockerItemState ( this,IDC_BUTTON_4_3 );	}
void CRanManagerUserLocker::OnBnClickedButton44(){	ViewLockerItem(4,4);	SetLockerItemState ( this,IDC_BUTTON_4_4 );	}
void CRanManagerUserLocker::OnBnClickedButton45(){	ViewLockerItem(4,5);	SetLockerItemState ( this,IDC_BUTTON_4_5 );	}
void CRanManagerUserLocker::OnBnClickedButton46(){	ViewLockerItem(4,6);	SetLockerItemState ( this,IDC_BUTTON_4_6 );	}
void CRanManagerUserLocker::OnBnClickedButton47(){	ViewLockerItem(4,7);	SetLockerItemState ( this,IDC_BUTTON_4_7 );	}
void CRanManagerUserLocker::OnBnClickedButton48(){	ViewLockerItem(4,8);	SetLockerItemState ( this,IDC_BUTTON_4_8 );	}
void CRanManagerUserLocker::OnBnClickedButton49(){	ViewLockerItem(4,9);	SetLockerItemState ( this,IDC_BUTTON_4_9 );	}

void CRanManagerUserLocker::OnBnClickedButton50(){	ViewLockerItem(5,0);	SetLockerItemState ( this,IDC_BUTTON_5_0 );	}
void CRanManagerUserLocker::OnBnClickedButton51(){	ViewLockerItem(5,1);	SetLockerItemState ( this,IDC_BUTTON_5_1 );	}
void CRanManagerUserLocker::OnBnClickedButton52(){	ViewLockerItem(5,2);	SetLockerItemState ( this,IDC_BUTTON_5_2 );	}
void CRanManagerUserLocker::OnBnClickedButton53(){	ViewLockerItem(5,3);	SetLockerItemState ( this,IDC_BUTTON_5_3 );	}
void CRanManagerUserLocker::OnBnClickedButton54(){	ViewLockerItem(5,4);	SetLockerItemState ( this,IDC_BUTTON_5_4 );	}
void CRanManagerUserLocker::OnBnClickedButton55(){	ViewLockerItem(5,5);	SetLockerItemState ( this,IDC_BUTTON_5_5 );	}
void CRanManagerUserLocker::OnBnClickedButton56(){	ViewLockerItem(5,6);	SetLockerItemState ( this,IDC_BUTTON_5_6 );	}
void CRanManagerUserLocker::OnBnClickedButton57(){	ViewLockerItem(5,7);	SetLockerItemState ( this,IDC_BUTTON_5_7 );	}
void CRanManagerUserLocker::OnBnClickedButton58(){	ViewLockerItem(5,8);	SetLockerItemState ( this,IDC_BUTTON_5_8 );	}
void CRanManagerUserLocker::OnBnClickedButton59(){	ViewLockerItem(5,9);	SetLockerItemState ( this,IDC_BUTTON_5_9 );	}

void CRanManagerUserLocker::OnBnClickedButtonP1(){	nActivePage = 0;	SetLockerPageState ( this,IDC_BUTTON_P1 ); InitLockerInven();	ResetLockerItem( 65535,65535 );	}
void CRanManagerUserLocker::OnBnClickedButtonP2(){	nActivePage = 1;	SetLockerPageState ( this,IDC_BUTTON_P2 ); InitLockerInven();	ResetLockerItem( 65535,65535 );	}
void CRanManagerUserLocker::OnBnClickedButtonP3(){	nActivePage = 2;	SetLockerPageState ( this,IDC_BUTTON_P3 ); InitLockerInven();	ResetLockerItem( 65535,65535 );	}
void CRanManagerUserLocker::OnBnClickedButtonP4(){	nActivePage = 3;	SetLockerPageState ( this,IDC_BUTTON_P4 ); InitLockerInven();	ResetLockerItem( 65535,65535 );	}
void CRanManagerUserLocker::OnBnClickedButtonP5(){	nActivePage = 4;	SetLockerPageState ( this,IDC_BUTTON_P5 ); InitLockerInven();	ResetLockerItem( 65535,65535 );	}


void CRanManagerUserLocker::SetLockerItemState ( CDialog *pDlg,int nID )
{
	ResetLockerItemState (this);
	CButton *pBtn;
	switch (nID)
	{
	case IDC_BUTTON_0_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_0_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_0_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_0_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_0_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_0_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_0_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_0_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_0_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_0_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_9 );	pBtn->SetState(TRUE);	break;
	
	case IDC_BUTTON_1_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_1_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_9 );	pBtn->SetState(TRUE);	break;
	
	case IDC_BUTTON_2_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_2_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_9 );	pBtn->SetState(TRUE);	break;
	
	case IDC_BUTTON_3_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_3_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_9 );	pBtn->SetState(TRUE);	break;

	case IDC_BUTTON_4_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_4_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_9 );	pBtn->SetState(TRUE);	break;

	case IDC_BUTTON_5_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_5_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_9 );	pBtn->SetState(TRUE);	break;
	};
}

void CRanManagerUserLocker::ResetLockerItemState ( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_0_9 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_1_9 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_2_9 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_3_9 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_4_9 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_5_9 );	pBtn->SetState(FALSE);

}

void CRanManagerUserLocker::SetLockerPageState ( CDialog *pDlg,int nID )
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

void CRanManagerUserLocker::ResetLockerPageState ( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P5 );	pBtn->SetState(FALSE);
}
void CRanManagerUserLocker::OnBnClickedButtonItemsearchM()
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

void CRanManagerUserLocker::OnBnClickedButtonItemsearchCos()
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

void CRanManagerUserLocker::OnCbnSelchangeComboGentype()
{
}

void CRanManagerUserLocker::OnBnClickedBtnEditItemUpdate()
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

void CRanManagerUserLocker::OnBnClickedBtnEditItemDelete()
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

void CRanManagerUserLocker::OnBnClickedBtnEditItemClear()
{
	if ( MessageBox ( "Do You Want To Delete All Item In This Page?", "Question", MB_YESNO ) == IDYES )
	{
		m_cStorage[nActivePage].DeleteItemAll();
		InitLockerInven();
		ResetLockerItem( 65535,65535 );
	}
}

void CRanManagerUserLocker::OnBnClickedBtnEditItemClearall()
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

void CRanManagerUserLocker::OnBnClickedBtnEditCancelLocker()
{
	m_pToolTab->ActivePage(USERPAGE_MAIN,0);
}

void CRanManagerUserLocker::OnBnClickedButtonResetCosExpire()
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

void CRanManagerUserLocker::OnBnClickedBtnEditSaveLocker()
{

	CByteStream ByteStream;
	LPBYTE pBuffer = NULL;
	DWORD dwSize = 0;
	TCHAR szTemp[128] = {0};
	CString strTemp;
	int nYear,nMonth,nDay,nHour,nMinute,nSecond ;

	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)
	DWORD dwUserNum = GetWin_Num_int(this,IDC_EDIT_NUM);
	LONGLONG llMoney = _strtoi64(GetWin_Text(this,IDC_EDIT_USERMONEY),NULL,10);

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	
	{
		MessageBox("Error Connecting to Game DB!","error",MB_OK);
		return;
	}

	//save locker gold
	_snprintf( szTemp, 128, "{call UpdateUserMoney(%u,%I64d)}", dwUserNum, llMoney );
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("UserLocker.txt","%s--%s",strTIME.c_str(),szTemp);

	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)		
	{
		MessageBox("Error Saving Locker Gold!","error",MB_OK);
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	//save locker time2
	nYear =		GetWin_Num_int(this,IDC_EDIT_LOCKER1_3);
	nMonth =	GetWin_Num_int(this,IDC_EDIT_LOCKER1_2);
	nDay =		GetWin_Num_int(this,IDC_EDIT_LOCKER1_1);
	nHour =		GetWin_Num_int(this,IDC_EDIT_LOCKER1_4);
	nMinute =	GetWin_Num_int(this,IDC_EDIT_LOCKER1_5);
	nSecond =	GetWin_Num_int(this,IDC_EDIT_LOCKER1_6);
	strTemp.Format("%d-%d-%d %d:%d:%d",nYear,nMonth,nDay,nHour,nMinute,nSecond);

	_snprintf( szTemp, 128, "Update %s.dbo.UserInven Set ChaStorage2='%s' WHERE UserNum=%d", CToolCfg::GetInstance()->szGameDb,strTemp.GetString(), dwUserNum );
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);
	LOGSCRIPT::LogToFile("UserLocker.txt","%s--%s",strTIME.c_str(),szTemp);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)		
	{
		MessageBox("Error Saving Locker Date 2","error",MB_OK);
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	

	//save locker time3
	nYear =		GetWin_Num_int(this,IDC_EDIT_LOCKER2_3);
	nMonth =	GetWin_Num_int(this,IDC_EDIT_LOCKER2_2);
	nDay =		GetWin_Num_int(this,IDC_EDIT_LOCKER2_1);
	nHour =		GetWin_Num_int(this,IDC_EDIT_LOCKER2_4);
	nMinute =	GetWin_Num_int(this,IDC_EDIT_LOCKER2_5);
	nSecond =	GetWin_Num_int(this,IDC_EDIT_LOCKER2_6);
	strTemp.Format("%d-%d-%d %d:%d:%d",nYear,nMonth,nDay,nHour,nMinute,nSecond);

	_snprintf( szTemp, 128, "Update %s.dbo.UserInven Set ChaStorage3='%s' WHERE UserNum=%d", CToolCfg::GetInstance()->szGameDb,strTemp.GetString(), dwUserNum );
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);
	LOGSCRIPT::LogToFile("UserLocker.txt","%s--%s",strTIME.c_str(),szTemp);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)		
	{
		MessageBox("Error Saving Locker Date 3","error",MB_OK);
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}


	//save locker time4
	nYear =		GetWin_Num_int(this,IDC_EDIT_LOCKER3_3);
	nMonth =	GetWin_Num_int(this,IDC_EDIT_LOCKER3_2);
	nDay =		GetWin_Num_int(this,IDC_EDIT_LOCKER3_1);
	nHour =		GetWin_Num_int(this,IDC_EDIT_LOCKER3_4);
	nMinute =	GetWin_Num_int(this,IDC_EDIT_LOCKER3_5);
	nSecond =	GetWin_Num_int(this,IDC_EDIT_LOCKER3_6);
	strTemp.Format("%d-%d-%d %d:%d:%d",nYear,nMonth,nDay,nHour,nMinute,nSecond);

	_snprintf( szTemp, 128, "Update %s.dbo.UserInven Set ChaStorage4='%s' WHERE UserNum=%d", CToolCfg::GetInstance()->szGameDb,strTemp.GetString(), dwUserNum );
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);
	LOGSCRIPT::LogToFile("UserLocker.txt","%s--%s",strTIME.c_str(),szTemp);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)		
	{
		MessageBox("Error Saving Locker Date 4","error",MB_OK);
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
		_snprintf( szTemp, 128, "UPDATE %s.dbo.UserInven SET UserInven = ? WHERE (UserNum=%u)", CToolCfg::GetInstance()->szGameDb,dwUserNum );
		LOGSCRIPT::LogToFile("UserLocker.txt","%s--%s",strTIME.c_str(),szTemp);

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
			MessageBox("Error Saving User Locker Binary!","error",MB_OK);
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
	MessageBox("Done Saving Locker Data!","Info",MB_OK);

	pBuffer = NULL;
	InitLockerInven();
}

