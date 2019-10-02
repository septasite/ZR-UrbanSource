// RanAddItemShop.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "COdbc.h"
#include "CCfg.h"
#include "s_NetGlobal.h"
#include "Calendar.h"
#include "EtcFunction.h"
#include "RanManagerComments.h"
#include "GLCharDefine.h"
#include "GLogicData.h"
#include "LogScript.h"
#include "GuildSearch.h"
#include "MapSearch.h"
#include "ItemSearch.h"
#include "RanAddItemShop.h"
#include ".\ranadditemshop.h"


// RanAddItemShop dialog
IMPLEMENT_DYNAMIC(RanAddItemShop, CPropertyPage)
RanAddItemShop::RanAddItemShop(LOGFONT logfont)
	: CPropertyPage(RanAddItemShop::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

RanAddItemShop::~RanAddItemShop()
{
}

void RanAddItemShop::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cCtg );
	DDX_Control(pDX, IDC_COMBO2, m_cSec );
}

BOOL RanAddItemShop::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(RanAddItemShop, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_ITEMSEARCH_M, OnBnClickedButtonItemsearchM)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()



void RanAddItemShop::OnBnClickedButtonItemsearchM()
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
void RanAddItemShop::OnBnClickedButton1()
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	
	{
		MessageBox("Error Connecting to Game DB!","error",MB_OK);
		return;
	}

	DWORD sMid = (DWORD)GetWin_Num_int(this,IDC_EDIT_MID);
	DWORD sSid = (DWORD)GetWin_Num_int(this,IDC_EDIT_SID);
	DWORD sPrice = (DWORD)GetWin_Num_int(this,IDC_EDIT1);
	DWORD sStock = (DWORD)GetWin_Num_int(this,IDC_EDIT2);
	DWORD sCtg = (DWORD)m_cCtg.GetCurSel();
	DWORD sSec  = (DWORD)m_cSec.GetCurSel();
	
	

		TCHAR szTemp[256] = {0};
		_snprintf( szTemp, 256, "INSERT INTO RanShop.dbo.ShopItemMap (ItemMain,ItemSub,ItemPrice,Itemstock,ItemCtg,ItemSec) "
			"VALUES ('%d','%d','%d','%d','%d','%d')", sMid , sSid  ,sPrice , sStock , sCtg , sSec );

		sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("ItemShop.txt","%s--%s",strTIME.c_str(),szTemp);
	if (sReturn == SQL_ERROR )	MessageBox("Error! Saving Data :-(","Ran Manager",MB_OK);
	else MessageBox("Success! Saving Data :-)","Ran Manager",MB_OK);

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	

}
