// RanManagerUserNew.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerUserNew.h"
#include "RanManagerUserTab.h"

#include "COdbc.h"
#include "CCfg.h"
#include "s_NetGlobal.h"
#include "china_md5.h"
#include "Calendar.h"
#include "EtcFunction.h"
#include "LogScript.h"
#include "RanManagerComments.h"
#include ".\ranmanagerusernew.h"

// CRanManagerUserNew dialog

IMPLEMENT_DYNAMIC(CRanManagerUserNew, CPropertyPage)
CRanManagerUserNew::CRanManagerUserNew(LOGFONT logfont)
	: CPropertyPage(CRanManagerUserNew::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerUserNew::~CRanManagerUserNew()
{
}

void CRanManagerUserNew::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_USERTYPE_N, m_cUserType );
}


BEGIN_MESSAGE_MAP(CRanManagerUserNew, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_MD5_1, OnBnClickedButtonMd51)
	ON_BN_CLICKED(IDC_BUTTON_MD5_2, OnBnClickedButtonMd52)
	ON_BN_CLICKED(IDC_BUTTON_CREATEUSER, OnBnClickedButtonCreateuser)
	ON_BN_CLICKED(IDC_BUTTON_CREATECANCEL, OnBnClickedButtonCreatecancel)
END_MESSAGE_MAP()


// CRanManagerUserNew message handlers
BOOL CRanManagerUserNew::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	for ( int i = 0; i < USER_TYPE_SIZE; ++i )
	{
		m_cUserType.InsertString( i, RMComments::m_UserType[i].c_str() );
	}
	m_cUserType.SetCurSel( 0 );

	SetWin_Text ( this, IDC_EDIT_USERID_N, "PlaceUserNameHere" );
	SetWin_Text ( this, IDC_EDIT_USERPASS_N, "PlacePasswordHere" );
	SetWin_Text ( this, IDC_EDIT_USERPASS2_N, "Place2ndPasswordHere" );
	SetWin_Text ( this, IDC_EDIT_USEREMAIL_N, "PlaceEmailHere" );
	SetWin_Num_int ( this, IDC_EDIT_USERP_N,0);
	SetWin_Num_int ( this, IDC_EDIT_CHAREMAIN_N,4);
	SetWin_Num_int ( this, IDC_EDIT_SVRNUM_N,0);
	SetWin_Num_int ( this, IDC_EDIT_SGNUM_N,0);

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerUserNew::OnBnClickedButtonMd51()
{
	if ( MessageBox("Are you sure you want to convert UserPass to MD5?","Question",MB_YESNO) == IDYES )
	ConvertMD5( GetWin_Text( this, IDC_EDIT_USERPASS_N ).GetString(),1);
}

void CRanManagerUserNew::OnBnClickedButtonMd52()
{
	if ( MessageBox("Are you sure you want to convert UserPass2 to MD5?","Question",MB_YESNO) == IDYES )
	ConvertMD5( GetWin_Text( this, IDC_EDIT_USERPASS2_N ).GetString(),2);
}

void CRanManagerUserNew::ConvertMD5(const TCHAR* szText,int nType)
{
	CHINA_MD5::MD5 md5; 
	size_t nLength = 0;
	StringCchLength( szText, USR_PASS_LENGTH, &nLength );
	md5.update( reinterpret_cast<const unsigned char*> (szText), nLength );	
	std::string strOut = md5.asString();

	TCHAR	szTemp[25];
	StringCchCopy( szTemp, USR_PASS_LENGTH, strOut.c_str() );
	m_Tea.encrypt( szTemp, USR_PASS_LENGTH );

	switch (nType)
	{
		case 1:	SetWin_Text ( this, IDC_EDIT_USERPASS_N, szTemp );	break;
		case 2:	SetWin_Text ( this, IDC_EDIT_USERPASS2_N, szTemp );	break;
	};
}

void CRanManagerUserNew::OnBnClickedButtonCreateuser()
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectUser(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;

	TCHAR szTemp[1024] = {0};
	
	int nUserTypeTemp,nUserType;
	nUserTypeTemp = m_cUserType.GetCurSel();
	switch (nUserTypeTemp)
	{
	case 0:	nUserType = 1; break;
	case 1:	nUserType = 10; break;
	case 2:	nUserType = 30; break;
	};
	
	_snprintf( szTemp, 1024, 
		"Insert Into %s.dbo.UserInfo "
		"(UserName,UserID,UserPass,UserPass2,UserType,UserAvailable,CreateDate,SGNum,SvrNum,"
		"ChaRemain,ChaTestRemain,UserEmail,UserPoint )"
		" Values ('%s','%s','%s','%s',%d,%d,%s,%d,%d,%d,%d,'%s',%d )"
	,CToolCfg::GetInstance()->szUserDb
	,(const TCHAR*)GetWin_Text( this, IDC_EDIT_USERID_N ).GetString()
	,(const TCHAR*)GetWin_Text( this, IDC_EDIT_USERID_N ).GetString()
	,(const TCHAR*)GetWin_Text( this, IDC_EDIT_USERPASS_N ).GetString()
	,(const TCHAR*)GetWin_Text( this, IDC_EDIT_USERPASS2_N ).GetString()
	,nUserType
	,1
	,"getdate()"
	,GetWin_Num_int ( this, IDC_EDIT_SGNUM_N )
	,GetWin_Num_int ( this, IDC_EDIT_SVRNUM_N )
	,GetWin_Num_int ( this, IDC_EDIT_CHAREMAIN_N )
	,GetWin_Num_int ( this, IDC_EDIT_CHAREMAIN_N )
	,(const TCHAR*)GetWin_Text( this, IDC_EDIT_USEREMAIL_N ).GetString()
	,GetWin_Num_int ( this, IDC_EDIT_USERP_N )
	);

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp, SQL_NTS);
	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("UserNew.txt","%s--%s",strTIME.c_str(),szTemp);
	if (sReturn == SQL_ERROR )	MessageBox("Error! Inserting User Data","Ran Manager",MB_OK);
	if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)	MessageBox("Success! Inserting User Data","Ran Manager",MB_OK);

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerUserNew::OnBnClickedButtonCreatecancel()
{
	m_pToolTab->ActivePage(USERPAGE_MAIN,0);
}
