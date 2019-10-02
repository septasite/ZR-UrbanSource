// RanManagerUserBank.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerUserBank.h"
#include "RanManagerUserTab.h"

#include "COdbc.h"
#include "CCfg.h"
#include "s_NetGlobal.h"
#include "china_md5.h"
#include "Calendar.h"
#include "EtcFunction.h"
#include "LogScript.h"
#include "RanManagerComments.h"
#include ".\ranmanageruserbank.h"
// CRanManagerUserBank dialog

IMPLEMENT_DYNAMIC(CRanManagerUserBank, CPropertyPage)
CRanManagerUserBank::CRanManagerUserBank(LOGFONT logfont)
	: CPropertyPage(CRanManagerUserBank::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerUserBank::~CRanManagerUserBank()
{
}

void CRanManagerUserBank::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHOP, m_list_Shop );
	DDX_Control(pDX, IDC_LIST_BANK, m_list_Bank );
	DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE, m_cSearchType );
}


BEGIN_MESSAGE_MAP(CRanManagerUserBank, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_SHOP, OnBnClickedButtonSearchShop)
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCH_TYPE, OnCbnSelchangeComboSearchType)
	ON_BN_CLICKED(IDC_BUTTON_USERBANK_CLOSE, OnBnClickedButtonUserbankClose)
	ON_BN_CLICKED(IDC_BUTTON_INSERT2, OnBnClickedButtonInsert2)
END_MESSAGE_MAP()


// CRanManagerUserBank message handlers
BOOL CRanManagerUserBank::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_Shop.SetExtendedStyle ( m_list_Shop.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |LVS_EX_CHECKBOXES);
		m_list_Shop.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 6;	
		char* szColumnName1[nColumnCount] = { "#","Item#", "Main" , "Sub", "ItemName", ""};
		int nColumnWidthPercent[nColumnCount] = { 12, 12,12,12,47,5 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_Shop.InsertColumn (i, &lvColumn );
		}
	}
	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_Bank.SetExtendedStyle ( m_list_Bank.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |LVS_EX_CHECKBOXES);
		m_list_Bank.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 6;	
		char* szColumnName1[nColumnCount] = { "#","Key","Item#", "ItemName" , "PurchaseDate",""};
		int nColumnWidthPercent[nColumnCount] = { 12,15,12,36,20,5 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_Bank.InsertColumn (i, &lvColumn );
		}
	}

	for ( int i = 0; i < SEARCHSHOP_SIZE; ++i )
	{
		m_cSearchType.InsertString( i, RMComments::m_SearchShopType[i].c_str() );
	}
	m_cSearchType.SetCurSel( 0 );

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerUserBank::SetUser(int nUser)
{
	LoadShop(0,0,"none");
	LoadBank(nUser);
}

void CRanManagerUserBank::LoadShop(int nType,int nVal,CString strSearch)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectShop(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
	{
		return;
	}

	TCHAR szTemp[256] = {0};
		_snprintf( szTemp, 256, "SELECT ProductNum,ItemMain,ItemSub,ItemName FROM %s.dbo.ShopItemMap WITH (NOLOCK)"
		,CToolCfg::GetInstance()->szShopDb  );
	
	sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("UserBank.txt","%s--%s",strTIME.c_str(),szTemp);
	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nProductNum = 0, cbProductNum = SQL_NTS; 
	SQLINTEGER nItemMain = 0, cbItemMain = SQL_NTS; 
	SQLINTEGER nItemSub = 0, cbItemSub  = SQL_NTS; 
	SQLCHAR    szItemName[100] = {0}; SQLINTEGER cbItemName = SQL_NTS;


	int nNum = 0;
	char szTempChar[256];
	m_list_Shop.DeleteAllItems();
	m_ShopVec.clear();
	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nProductNum, 0, &cbProductNum );
			::SQLGetData(hStmt, 2, SQL_C_LONG, &nItemMain, 0, &cbItemMain );
			::SQLGetData(hStmt, 3, SQL_C_LONG, &nItemSub, 0, &cbItemSub );
			::SQLGetData(hStmt, 4, SQL_C_CHAR, szItemName, 100, &cbItemName);

			bool bFound = false;
			switch (nType)
			{
			case SEARCHSHOP_NONE:	bFound = true;	break;
			case SEARCHSHOP_NUM:
				{
					if (nVal == (int)nProductNum ) bFound = true;
				}break;
			case SEARCHSHOP_MID:
				{
					if (nVal == (int)nItemMain ) bFound = true;
				}break;
			case SEARCHSHOP_SID:
				{
					if (nVal == (int)nItemSub ) bFound = true;
				}break;
			case SEARCHSHOP_NAME:
				{
					std::string strItemName = (const TCHAR*)szItemName;
					unsigned found = strItemName.find(strSearch);
					if (found!=std::string::npos)	bFound = true;
				}break;
			};

			if (bFound)
			{
				sprintf( szTempChar, "%d", nNum );
				m_list_Shop.InsertItem( nNum, szTempChar );

				sprintf( szTempChar, "%d", nProductNum );
				m_list_Shop.SetItemText(nNum,1,szTempChar);
				sprintf( szTempChar, "%d", nItemMain );
				m_list_Shop.SetItemText(nNum,2,szTempChar);
				sprintf( szTempChar, "%d", nItemSub );
				m_list_Shop.SetItemText(nNum,3,szTempChar);
				sprintf( szTempChar, "%s", szItemName );
				m_list_Shop.SetItemText(nNum,4,szTempChar);

				nNum++;
			}

			ITEMBANKINFO*	NewInfo = new ITEMBANKINFO;
			NewInfo->nProductNum = nProductNum;
			NewInfo->strItemName = (const TCHAR*)szItemName;
			m_ShopVec.push_back(NewInfo);
			
			}
		else	break;
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	

}

void CRanManagerUserBank::LoadBank(int nUser)
{
	TCHAR szUserName[CHR_ID_LENGTH+1];
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
		
		sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);
		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("UserBank.txt","%s--%s",strTIME.c_str(),szTemp);
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
				StringCchCopy( szUserName, CHR_ID_LENGTH+1, (const TCHAR*)szCharId );
				SetWin_Num_int ( this, IDC_EDIT_NUM,nUser);
				SetWin_Text ( this, IDC_EDIT_ID,szUserName );
			}
			else	break;
			Sleep( 0 );
		}
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	

	}
	{
		SQLRETURN	sReturn = 0; // SQL return value (short)	
		SQLHSTMT	hStmt; // Handle of statement (void*)

		sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectShop(), &hStmt);
		if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)
		{
			return;
		}

		TCHAR szTemp[256] = {0};
			_snprintf( szTemp, 256, "SELECT Purkey,ProductNum,PurDate FROM %s.dbo.ShopPurchase WITH (NOLOCK) WHERE UserUID='%s'"
			,CToolCfg::GetInstance()->szShopDb,szUserName  );
		
		sReturn = ::SQLExecDirect(hStmt, (SQLCHAR*) szTemp, SQL_NTS);
		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("UserBank.txt","%s--%s",strTIME.c_str(),szTemp);
		if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
		{
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			return;
		}

		SQLINTEGER nPurKey = 0, cbPurKey  = SQL_NTS;
		SQLINTEGER nProductNum = 0, cbProductNum = SQL_NTS; 
		TIMESTAMP_STRUCT sPurDate;	SQLINTEGER cbPurDate   = SQL_NTS;

		int nNum = 0;
		char szTempChar[256];
		m_list_Bank.DeleteAllItems();
		while (true)
		{
			sReturn = ::SQLFetch(hStmt);
			if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;
			if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
			{
				::SQLGetData(hStmt, 1, SQL_C_LONG, &nPurKey, 0, &cbPurKey );
				::SQLGetData(hStmt, 2, SQL_C_LONG, &nProductNum, 0, &cbProductNum );
				::SQLGetData(hStmt, 3, SQL_C_TYPE_TIMESTAMP,	&sPurDate,	0,	&cbPurDate);//

				sprintf( szTempChar, "%d", nNum );
				m_list_Bank.InsertItem( nNum, szTempChar );

				sprintf( szTempChar, "%d", nPurKey );
				m_list_Bank.SetItemText(nNum,1,szTempChar);

				sprintf( szTempChar, "%d", nProductNum );
				m_list_Bank.SetItemText(nNum,2,szTempChar);

				sprintf( szTempChar, "%s", GetShopName(nProductNum).GetString() );
				m_list_Bank.SetItemText(nNum,3,szTempChar);

				sprintf( szTempChar, "%d/%d/%d %d:%d:%d", 
					sPurDate.day,
					sPurDate.month,
					sPurDate.year
					,sPurDate.hour,
					sPurDate.minute,
					sPurDate.second );
				m_list_Bank.SetItemText(nNum,4,szTempChar);

				nNum++;	}
			else	break;
			Sleep( 0 );
		}
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
	}
}

CString CRanManagerUserBank::GetShopName(int nItemNum )
{
	CString strTemp;
	ITEMBANK_LIST_ITER iter = m_ShopVec.begin();
	ITEMBANK_LIST_ITER iter_end = m_ShopVec.end();
	for( ; iter != iter_end; ++iter )
	{
		ITEMBANKINFO* pInfo = *iter;
		if (pInfo->nProductNum == nItemNum)
		{
			strTemp.Format("%s",pInfo->strItemName.c_str() );
			return strTemp;
		}
	}
	strTemp.Format("%s","NotFound" );
	return strTemp;
}
void CRanManagerUserBank::OnBnClickedButtonInsert()
{
	int nItemNum;
	int nItem = 0; 
    for(nItem =0 ; nItem <  m_list_Shop.GetItemCount(); nItem++)
    {
        BOOL bChecked = m_list_Shop.GetCheck(nItem);
        if( bChecked)
        {
			nItemNum = atoi ( m_list_Shop.GetItemText(nItem, 1).GetString() );
			InsertItemToBank(nItemNum);
        }
    }
}

void CRanManagerUserBank::OnBnClickedButtonDelete()
{
	if ( MessageBox("Are you sure you want to Delete the Selected Items?\nThis is Permanent Delete!","Question",MB_YESNO) == IDYES )
	{
		int nKey;
		int nItem = 0; 
		for(nItem =0 ; nItem <  m_list_Bank.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_Bank.GetCheck(nItem);
			if( bChecked)
			{
				nKey = atoi ( m_list_Bank.GetItemText(nItem, 1).GetString() );
				DeleteItemFromBank(nKey );
			}
		}
	}
}

void CRanManagerUserBank::OnBnClickedButtonClear()
{
	if ( MessageBox("Are you sure you want to Clear the ItemBank for this User?\nThis is Permanent Delete!","Question",MB_YESNO) == IDYES )
	{

		SQLRETURN	sReturn = 0; // SQL return value (short)	
		SQLHSTMT	hStmt; // Handle of statement (void*)

		sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectShop(), &hStmt);
		if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

		TCHAR szTemp[1024] = {0};
		
		_snprintf( szTemp, 1024, 
			"Delete From %s.dbo.ShopPurchase "
			" Where UserUID ='%s'"
		,CToolCfg::GetInstance()->szShopDb
		,(const TCHAR*)GetWin_Text( this, IDC_EDIT_ID ).GetString()
		);

		sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("UserBank.txt","%s--%s",strTIME.c_str(),szTemp);

		if (sReturn == SQL_ERROR )	
		{
			MessageBox("Error! Cant Delete Items in ItemBank","Ran Manager",MB_OK);
			::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
		}

		LoadBank(GetWin_Num_int ( this, IDC_EDIT_NUM ));
	}
}

void CRanManagerUserBank::InsertItemToBank(int nItemNum )
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectShop(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

	TCHAR szTemp[1024] = {0};
	
	_snprintf( szTemp, 1024, 
		"Insert Into %s.dbo.ShopPurchase "
		"(UserUID,ProductNum,PurPrice,PurDate)"
		" Values ('%s',%d,%d,%s)"
	,CToolCfg::GetInstance()->szShopDb
	,(const TCHAR*)GetWin_Text( this, IDC_EDIT_ID ).GetString()
	,nItemNum
	,10211
	,"getdate()"
	);

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("UserBank.txt","%s--%s",strTIME.c_str(),szTemp);

	if (sReturn == SQL_ERROR )	
	{
		MessageBox("Error! Inserting Item to ItemBank","Ran Manager",MB_OK);
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
	}

	LoadBank(GetWin_Num_int ( this, IDC_EDIT_NUM ));
}

void CRanManagerUserBank::DeleteItemFromBank(int nKey )
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectShop(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

	TCHAR szTemp[1024] = {0};
	
	_snprintf( szTemp, 1024, 
		"Delete From %s.dbo.ShopPurchase "
		" Where Purkey = %d AND UserUID ='%s'"
	,CToolCfg::GetInstance()->szShopDb
	,nKey
	,(const TCHAR*)GetWin_Text( this, IDC_EDIT_ID ).GetString()
	);

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("UserBank.txt","%s--%s",strTIME.c_str(),szTemp);

	if (sReturn == SQL_ERROR )	
	{
		MessageBox("Error! Cant Delete This Item In ItemBank","Ran Manager",MB_OK);
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}

	LoadBank(GetWin_Num_int ( this, IDC_EDIT_NUM ));
}
void CRanManagerUserBank::OnBnClickedButtonSearchShop()
{
	int nSelect = m_cSearchType.GetCurSel();
	int nVal = GetWin_Num_int(this,IDC_EDIT_SEARCH_SHOP);
	CString strTemp =  GetWin_Text(this,IDC_EDIT_SEARCH_SHOP).GetString();
	LoadShop(nSelect,nVal,strTemp);
}

void CRanManagerUserBank::OnCbnSelchangeComboSearchType()
{
	int nSelect = m_cSearchType.GetCurSel();
	if (nSelect == SEARCHSHOP_NONE )	SetWin_Enable(this,IDC_EDIT_SEARCH_SHOP,false);
	else	SetWin_Enable(this,IDC_EDIT_SEARCH_SHOP,true);
}

void CRanManagerUserBank::OnBnClickedButtonUserbankClose()
{
	m_pToolTab->ActivePage(USERPAGE_MAIN,0);
}

void CRanManagerUserBank::OnBnClickedButtonInsert2()
{
	// TODO: add new Dialog 
}
