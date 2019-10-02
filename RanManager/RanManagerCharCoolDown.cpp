// RanManagerCharCoolDown.cpp : implementation file
// todo: Will add *Add cooldown and edit cooldown function
// i will skip this function for now i dont know if its usefull
//
//
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerCharCoolDown.h"
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
#include ".\ranmanagercharcooldown.h"

// CRanManagerCharCoolDown dialog

IMPLEMENT_DYNAMIC(CRanManagerCharCoolDown, CPropertyPage)
CRanManagerCharCoolDown::CRanManagerCharCoolDown(LOGFONT logfont)
	: CPropertyPage(CRanManagerCharCoolDown::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerCharCoolDown::~CRanManagerCharCoolDown()
{
}

void CRanManagerCharCoolDown::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_COOLDOWN_ID, m_list_CD_ID );
	DDX_Control(pDX, IDC_LIST_COOLDOWN_TYPE, m_list_CD_TYPE );
}


BEGIN_MESSAGE_MAP(CRanManagerCharCoolDown, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_ID_DELETE, OnBnClickedButtonIdDelete)
	ON_BN_CLICKED(IDC_BUTTON_ID_DELETEALL, OnBnClickedButtonIdDeleteall)
	ON_BN_CLICKED(IDC_BUTTON_TYPE_DELETE, OnBnClickedButtonTypeDelete)
	ON_BN_CLICKED(IDC_BUTTON_TYPE_DELETEALL, OnBnClickedButtonTypeDeleteall)
	ON_BN_CLICKED(IDC_BUTTON_COOLDOWN_SVE, OnBnClickedButtonCooldownSve)
	ON_BN_CLICKED(IDC_BUTTON_COOLDOWN_CANCEL, OnBnClickedButtonCooldownCancel)
END_MESSAGE_MAP()


// CRanManagerCharCoolDown message handlers
BOOL CRanManagerCharCoolDown::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_CD_ID.SetExtendedStyle (m_list_CD_ID.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |LVS_EX_CHECKBOXES);
		m_list_CD_ID.GetClientRect ( &rectCtrl );
		m_list_CD_TYPE.SetExtendedStyle (m_list_CD_TYPE.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |LVS_EX_CHECKBOXES);
		m_list_CD_TYPE.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 6;	
		char* szColumnName1[nColumnCount] = { "#","ID", "MID" , "SID","ItemName", ""};
		int nColumnWidthPercent[nColumnCount] = { 15,25,10,10,35,5 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_CD_ID.InsertColumn (i, &lvColumn );
			m_list_CD_TYPE.InsertColumn (i, &lvColumn );
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerCharCoolDown::SetChar(int nChar)
{
	LoadChar(nChar);
	LoadCoolDown(nChar);
}

void CRanManagerCharCoolDown::LoadChar(int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT ChaNum,ChaName FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChar );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharCoolDown.txt","%s--%s",strTIME.c_str(),szTemp);

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

void CRanManagerCharCoolDown::LoadCoolDown(int nChar)
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
	_snprintf( szTemp, 128, "SELECT ChaCoolTime FROM  %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaNum=%u"
		,CToolCfg::GetInstance()->szGameDb,nChar );
	
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharCoolDown.txt","%s--%s",strTIME.c_str(),szTemp);

	if ( sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO )
	{
		MessageBox("Error Reading CoolDown Binary","Error",MB_OK);
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

	m_mapCoolTimeType.clear();
	m_mapCoolTimeID.clear();
	
	DWORD dwVersion, dwSize, dwNum;

	ByteStream >> dwVersion;
	ByteStream >> dwSize;
	ByteStream >> dwNum;

	GASSERT ( (dwSize==sizeof(ITEM_COOLTIME)) && (ITEM_COOLTIME::VERSION==dwVersion) );

	ITEM_COOLTIME sCoolTime;
	
	for ( DWORD i=0; i<dwNum; i++ )
	{
		ByteStream.ReadBuffer ( (LPBYTE)&sCoolTime, sizeof(ITEM_COOLTIME) );
		m_mapCoolTimeID[sCoolTime.dwCoolID] = sCoolTime;		
	}

	ByteStream >> dwNum;

	for ( DWORD i=0; i<dwNum; i++ )
	{
		ByteStream.ReadBuffer ( (LPBYTE)&sCoolTime, sizeof(ITEM_COOLTIME) );
		m_mapCoolTimeType[sCoolTime.dwCoolID] = sCoolTime;
	}


	ShowCoolDownID();
	ShowCoolDownType();
}

void CRanManagerCharCoolDown::ShowCoolDownID()
{
	int nNum = 0;
	char szTempChar[1024];
	m_list_CD_ID.DeleteAllItems();

	COOLTIME_MAP_ITER iter = m_mapCoolTimeID.begin();
	COOLTIME_MAP_ITER iter_end = m_mapCoolTimeID.end();
	for ( ; iter!=iter_end; ++iter )
	{
		ITEM_COOLTIME pCD = (*iter).second;
		SNATIVEID sID = pCD.dwID;
		sprintf( szTempChar, "%d", nNum );
		m_list_CD_ID.InsertItem( nNum, szTempChar );

		sprintf( szTempChar, "%d", pCD.dwCoolID );
		m_list_CD_ID.SetItemText(nNum,1,szTempChar);

		sprintf( szTempChar, "%d", sID.wMainID );
		m_list_CD_ID.SetItemText(nNum,2,szTempChar);

		sprintf( szTempChar, "%d", sID.wSubID );
		m_list_CD_ID.SetItemText(nNum,3,szTempChar);

		SITEM* pItem = GLItemMan::GetInstance().GetItem(sID);
		if (pItem)
		{
			sprintf( szTempChar, "%s", pItem->GetName() );
			m_list_CD_ID.SetItemText(nNum,4,szTempChar);
		}
		else
		{
			sprintf( szTempChar, "%s", "Unknown Item" );
			m_list_CD_ID.SetItemText(nNum,4,szTempChar);
		}

		nNum++;
	}
}

void CRanManagerCharCoolDown::ShowCoolDownType()
{
	int nNum = 0;
	char szTempChar[1024];
	m_list_CD_TYPE.DeleteAllItems();

	COOLTIME_MAP_ITER iter = m_mapCoolTimeType.begin();
	COOLTIME_MAP_ITER iter_end = m_mapCoolTimeType.end();
	for ( ; iter!=iter_end; ++iter )
	{
		ITEM_COOLTIME pCD = (*iter).second;
		SNATIVEID sID = pCD.dwID;
		sprintf( szTempChar, "%d", nNum );
		m_list_CD_TYPE.InsertItem( nNum, szTempChar );

		sprintf( szTempChar, "%d", pCD.dwCoolID );
		m_list_CD_TYPE.SetItemText(nNum,1,szTempChar);

		sprintf( szTempChar, "%d", sID.wMainID );
		m_list_CD_TYPE.SetItemText(nNum,2,szTempChar);

		sprintf( szTempChar, "%d", sID.wSubID );
		m_list_CD_TYPE.SetItemText(nNum,3,szTempChar);

		SITEM* pItem = GLItemMan::GetInstance().GetItem(sID);
		if (pItem)
		{
			sprintf( szTempChar, "%s", pItem->GetName() );
			m_list_CD_TYPE.SetItemText(nNum,4,szTempChar);
		}
		else
		{
			sprintf( szTempChar, "%s", "Unknown Item" );
			m_list_CD_TYPE.SetItemText(nNum,4,szTempChar);
		}

		nNum++;
	}
}


void CRanManagerCharCoolDown::OnBnClickedButtonIdDelete()
{
	if ( MessageBox ( "This Will Remove All The Selected Character CoolDown By ID!, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		int nItem = 0; 
		for(nItem =0 ; nItem <  m_list_CD_ID.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_CD_ID.GetCheck(nItem);
			if( bChecked)
			{
				int nID = atoi ( m_list_CD_ID.GetItemText(nItem, 1).GetString() );

				COOLTIME_MAP_ITER pos = m_mapCoolTimeID.find(nID);
				if ( pos==m_mapCoolTimeID.end() )		continue;
			
				m_mapCoolTimeID.erase(pos);
			}
		}
		ShowCoolDownID();
	}	
}

void CRanManagerCharCoolDown::OnBnClickedButtonIdDeleteall()
{
	if ( MessageBox ( "This Will Remove All The Character CoolDown By ID!, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		m_mapCoolTimeID.clear();
		ShowCoolDownID();
	}
}

void CRanManagerCharCoolDown::OnBnClickedButtonTypeDelete()
{
	if ( MessageBox ( "This Will Remove All The Selected Character CoolDown By Type!, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		int nItem = 0; 
		for(nItem =0 ; nItem <  m_list_CD_TYPE.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_CD_TYPE.GetCheck(nItem);
			if( bChecked)
			{
				int nID = atoi ( m_list_CD_TYPE.GetItemText(nItem, 1).GetString() );

				COOLTIME_MAP_ITER pos = m_mapCoolTimeType.find(nID);
				if ( pos==m_mapCoolTimeType.end() )		continue;
			
				m_mapCoolTimeType.erase(pos);
			}
		}
		ShowCoolDownType();
	}	
}

void CRanManagerCharCoolDown::OnBnClickedButtonTypeDeleteall()
{
	if ( MessageBox ( "This Will Remove All The Character CoolDown By Type!, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		m_mapCoolTimeType.clear();
		ShowCoolDownType();
	}
}

void CRanManagerCharCoolDown::OnBnClickedButtonCooldownSve()
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
	ByteStream << ITEM_COOLTIME::VERSION;
	ByteStream << (DWORD)sizeof(ITEM_COOLTIME);
	DWORD dwSize2 = (DWORD) m_mapCoolTimeID.size();
	ByteStream << dwSize2;
	const ITEM_COOLTIME* pCoolTime;
	COOLTIME_MAP_CITER	pos = m_mapCoolTimeID.begin();
	COOLTIME_MAP_CITER	end = m_mapCoolTimeID.end();
	for ( ; pos != end; ++pos )
	{
		pCoolTime = &pos->second;
		ByteStream.WriteBuffer ( (LPBYTE)pCoolTime, sizeof(ITEM_COOLTIME) );
	}
	dwSize2 = (DWORD) m_mapCoolTimeType.size();
	ByteStream << dwSize2;
	pos = m_mapCoolTimeType.begin();
	end = m_mapCoolTimeType.end();
	for ( ; pos != end; ++pos )
	{
		pCoolTime = &pos->second;
		ByteStream.WriteBuffer ( (LPBYTE)pCoolTime, sizeof(ITEM_COOLTIME) );
	}

	ByteStream.GetBuffer(pBuffer, dwSize);

	//write image
	if (pBuffer != NULL)
	{
		TCHAR szTemp[128] = {0};
		_snprintf( szTemp, 128, "UPDATE ChaInfo SET ChaCoolTime=? WHERE (ChaNum=%u)", (DWORD)nChaNum );

		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("CharCoolDown.txt","%s--%s",strTIME.c_str(),szTemp);

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
			MessageBox("Error Saving CoolDown Binary!","error",MB_OK);
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
	MessageBox("Done Saving CoolDown!","Info",MB_OK);

	pBuffer = NULL;

	ShowCoolDownID();
	ShowCoolDownType();
}

void CRanManagerCharCoolDown::OnBnClickedButtonCooldownCancel()
{
	m_pToolTab->ActivePage(CHARPAGE_MAIN,0);
}

//will use this function to add
//pending

	//ITEM_COOLTIME sCoolTime;
	//sCoolTime.dwID = pItem->sBasicOp.sNativeID.dwID;
	//sCoolTime.tUseTime = tCurTime;
	//sCoolTime.tCoolTime = tCoolTime;	

	//if ( emCoolType == EMCOOL_ITEMID )
	//{
	//	sCoolTime.dwCoolID = pItem->sBasicOp.sNativeID.dwID;
	//	m_mapCoolTimeID[sCoolTime.dwCoolID] = sCoolTime;
	//}
	//else if( emCoolType == EMCOOL_ITEMTYPE )
	//{
	//	sCoolTime.dwCoolID = (DWORD)pItem->sBasicOp.emItemType;
	//	m_mapCoolTimeType[sCoolTime.dwCoolID] = sCoolTime;
	//}
