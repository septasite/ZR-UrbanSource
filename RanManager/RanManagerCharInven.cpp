// RanManagerCharInven.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerCharInven.h"
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
#include ".\ranmanagercharinven.h"

// CRanManagerCharInven dialog

IMPLEMENT_DYNAMIC(CRanManagerCharInven, CPropertyPage)
CRanManagerCharInven::CRanManagerCharInven(LOGFONT logfont)
	: CPropertyPage(CRanManagerCharInven::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	nActiveItem_X = 65535;
	nActiveItem_Y = 65535;
}

CRanManagerCharInven::~CRanManagerCharInven()
{
}

void CRanManagerCharInven::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GENTYPE, m_cGenType );
	DDX_Control(pDX, IDC_COMBO_OPTION1, m_cRandomOp1 );
	DDX_Control(pDX, IDC_COMBO_OPTION2, m_cRandomOp2 );
	DDX_Control(pDX, IDC_COMBO_OPTION3, m_cRandomOp3 );
	DDX_Control(pDX, IDC_COMBO_OPTION4, m_cRandomOp4 );
}


BEGIN_MESSAGE_MAP(CRanManagerCharInven, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_0, OnBnClickedButtonInven00)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_1, OnBnClickedButtonInven01)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_2, OnBnClickedButtonInven02)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_3, OnBnClickedButtonInven03)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_4, OnBnClickedButtonInven04)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_5, OnBnClickedButtonInven05)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_6, OnBnClickedButtonInven06)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_7, OnBnClickedButtonInven07)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_8, OnBnClickedButtonInven08)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_9, OnBnClickedButtonInven09)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_10, OnBnClickedButtonInven010)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_11, OnBnClickedButtonInven011)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_12, OnBnClickedButtonInven012)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_13, OnBnClickedButtonInven013)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_14, OnBnClickedButtonInven014)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_15, OnBnClickedButtonInven015)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_16, OnBnClickedButtonInven016)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_17, OnBnClickedButtonInven017)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_18, OnBnClickedButtonInven018)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_19, OnBnClickedButtonInven019)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_20, OnBnClickedButtonInven020)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_21, OnBnClickedButtonInven021)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_22, OnBnClickedButtonInven022)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_23, OnBnClickedButtonInven023)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_24, OnBnClickedButtonInven024)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_25, OnBnClickedButtonInven025)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_26, OnBnClickedButtonInven026)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_27, OnBnClickedButtonInven027)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_28, OnBnClickedButtonInven028)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_0_29, OnBnClickedButtonInven029)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_0, OnBnClickedButtonInven10)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_1, OnBnClickedButtonInven11)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_2, OnBnClickedButtonInven12)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_3, OnBnClickedButtonInven13)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_4, OnBnClickedButtonInven14)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_5, OnBnClickedButtonInven15)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_6, OnBnClickedButtonInven16)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_7, OnBnClickedButtonInven17)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_8, OnBnClickedButtonInven18)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_9, OnBnClickedButtonInven19)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_10, OnBnClickedButtonInven110)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_11, OnBnClickedButtonInven111)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_12, OnBnClickedButtonInven112)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_13, OnBnClickedButtonInven113)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_14, OnBnClickedButtonInven114)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_15, OnBnClickedButtonInven115)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_16, OnBnClickedButtonInven116)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_17, OnBnClickedButtonInven117)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_18, OnBnClickedButtonInven118)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_19, OnBnClickedButtonInven119)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_20, OnBnClickedButtonInven120)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_21, OnBnClickedButtonInven121)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_22, OnBnClickedButtonInven122)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_23, OnBnClickedButtonInven123)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_24, OnBnClickedButtonInven124)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_25, OnBnClickedButtonInven125)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_26, OnBnClickedButtonInven126)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_27, OnBnClickedButtonInven127)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_28, OnBnClickedButtonInven128)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_1_29, OnBnClickedButtonInven129)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_0, OnBnClickedButtonInven20)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_1, OnBnClickedButtonInven21)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_2, OnBnClickedButtonInven22)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_3, OnBnClickedButtonInven23)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_4, OnBnClickedButtonInven24)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_5, OnBnClickedButtonInven25)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_6, OnBnClickedButtonInven26)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_7, OnBnClickedButtonInven27)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_8, OnBnClickedButtonInven28)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_9, OnBnClickedButtonInven29)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_10, OnBnClickedButtonInven210)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_11, OnBnClickedButtonInven211)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_12, OnBnClickedButtonInven212)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_13, OnBnClickedButtonInven213)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_14, OnBnClickedButtonInven214)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_15, OnBnClickedButtonInven215)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_16, OnBnClickedButtonInven216)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_17, OnBnClickedButtonInven217)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_18, OnBnClickedButtonInven218)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_19, OnBnClickedButtonInven219)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_20, OnBnClickedButtonInven220)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_21, OnBnClickedButtonInven221)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_22, OnBnClickedButtonInven222)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_23, OnBnClickedButtonInven223)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_24, OnBnClickedButtonInven224)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_25, OnBnClickedButtonInven225)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_26, OnBnClickedButtonInven226)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_27, OnBnClickedButtonInven227)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_28, OnBnClickedButtonInven228)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_2_29, OnBnClickedButtonInven229)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_0, OnBnClickedButtonInven30)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_1, OnBnClickedButtonInven31)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_2, OnBnClickedButtonInven32)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_3, OnBnClickedButtonInven33)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_4, OnBnClickedButtonInven34)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_5, OnBnClickedButtonInven35)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_6, OnBnClickedButtonInven36)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_7, OnBnClickedButtonInven37)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_8, OnBnClickedButtonInven38)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_9, OnBnClickedButtonInven39)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_10, OnBnClickedButtonInven310)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_11, OnBnClickedButtonInven311)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_12, OnBnClickedButtonInven312)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_13, OnBnClickedButtonInven313)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_14, OnBnClickedButtonInven314)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_15, OnBnClickedButtonInven315)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_16, OnBnClickedButtonInven316)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_17, OnBnClickedButtonInven317)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_18, OnBnClickedButtonInven318)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_19, OnBnClickedButtonInven319)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_20, OnBnClickedButtonInven320)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_21, OnBnClickedButtonInven321)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_22, OnBnClickedButtonInven322)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_23, OnBnClickedButtonInven323)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_24, OnBnClickedButtonInven324)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_25, OnBnClickedButtonInven325)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_26, OnBnClickedButtonInven326)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_27, OnBnClickedButtonInven327)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_28, OnBnClickedButtonInven328)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_3_29, OnBnClickedButtonInven329)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_0, OnBnClickedButtonInven40)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_1, OnBnClickedButtonInven41)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_2, OnBnClickedButtonInven42)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_3, OnBnClickedButtonInven43)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_4, OnBnClickedButtonInven44)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_5, OnBnClickedButtonInven45)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_6, OnBnClickedButtonInven46)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_7, OnBnClickedButtonInven47)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_8, OnBnClickedButtonInven48)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_9, OnBnClickedButtonInven49)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_10, OnBnClickedButtonInven410)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_11, OnBnClickedButtonInven411)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_12, OnBnClickedButtonInven412)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_13, OnBnClickedButtonInven413)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_14, OnBnClickedButtonInven414)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_15, OnBnClickedButtonInven415)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_16, OnBnClickedButtonInven416)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_17, OnBnClickedButtonInven417)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_18, OnBnClickedButtonInven418)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_19, OnBnClickedButtonInven419)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_20, OnBnClickedButtonInven420)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_21, OnBnClickedButtonInven421)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_22, OnBnClickedButtonInven422)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_23, OnBnClickedButtonInven423)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_24, OnBnClickedButtonInven424)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_25, OnBnClickedButtonInven425)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_26, OnBnClickedButtonInven426)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_27, OnBnClickedButtonInven427)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_28, OnBnClickedButtonInven428)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_4_29, OnBnClickedButtonInven429)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_0, OnBnClickedButtonInven50)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_1, OnBnClickedButtonInven51)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_2, OnBnClickedButtonInven52)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_3, OnBnClickedButtonInven53)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_4, OnBnClickedButtonInven54)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_5, OnBnClickedButtonInven55)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_6, OnBnClickedButtonInven56)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_7, OnBnClickedButtonInven57)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_8, OnBnClickedButtonInven58)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_9, OnBnClickedButtonInven59)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_10, OnBnClickedButtonInven510)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_11, OnBnClickedButtonInven511)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_12, OnBnClickedButtonInven512)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_13, OnBnClickedButtonInven513)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_14, OnBnClickedButtonInven514)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_15, OnBnClickedButtonInven515)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_16, OnBnClickedButtonInven516)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_17, OnBnClickedButtonInven517)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_18, OnBnClickedButtonInven518)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_19, OnBnClickedButtonInven519)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_20, OnBnClickedButtonInven520)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_21, OnBnClickedButtonInven521)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_22, OnBnClickedButtonInven522)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_23, OnBnClickedButtonInven523)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_24, OnBnClickedButtonInven524)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_25, OnBnClickedButtonInven525)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_26, OnBnClickedButtonInven526)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_27, OnBnClickedButtonInven527)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_28, OnBnClickedButtonInven528)
	ON_BN_CLICKED(IDC_BUTTON_INVEN_5_29, OnBnClickedButtonInven529)
	ON_BN_CLICKED(IDC_BUTTON_ITEMSEARCH_M, OnBnClickedButtonItemsearchM)
	ON_BN_CLICKED(IDC_BUTTON_ITEMSEARCH_COS, OnBnClickedButtonItemsearchCos)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_DELETE, OnBnClickedBtnEditItemDelete)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_UPDATE, OnBnClickedBtnEditItemUpdate)
	ON_BN_CLICKED(IDC_BUTTON_RESET_COS_EXPIRE, OnBnClickedButtonResetCosExpire)
	ON_CBN_SELCHANGE(IDC_COMBO_GENTYPE, OnCbnSelchangeComboGentype)
	ON_BN_CLICKED(IDC_BUTTON_INVENCANCEL, OnBnClickedButtonInvencancel)
	ON_BN_CLICKED(IDC_BUTTON_INVENSAVE, OnBnClickedButtonInvensave)
	ON_BN_CLICKED(IDC_BUTTON_INVENWIPE, OnBnClickedButtonInvenwipe)
	ON_BN_CLICKED(IDC_BUTTON_P1, OnBnClickedButtonP1)
	ON_BN_CLICKED(IDC_BUTTON_P2, OnBnClickedButtonP2)
	ON_BN_CLICKED(IDC_BUTTON_P3, OnBnClickedButtonP3)
END_MESSAGE_MAP()


// CRanManagerCharInven message handlers
BOOL CRanManagerCharInven::OnInitDialog()
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

void CRanManagerCharInven::SetChar(int nChar)
{
	ReadChar (nChar);
	ReadInven (nChar);
}

void CRanManagerCharInven::ReadChar (int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT ChaNum,ChaName FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChar );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharInven.txt","%s--%s",strTIME.c_str(),szTemp);

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

void CRanManagerCharInven::ReadInven (int nChar)
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
	_snprintf( szTemp, 128, "SELECT ChaInven FROM  %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaNum=%u"
		,CToolCfg::GetInstance()->szGameDb,nChar );
	
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharInven.txt","%s--%s",strTIME.c_str(),szTemp);

	if ( sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO )
	{
		MessageBox("Error Reading Inven Items Binary","Error",MB_OK);
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

	GLInventory cInven;
	BOOL bOk = cInven.SETITEM_BYBUFFER ( ByteStream );
	if ( !bOk )			
	{
		MessageBox("Error Inventory Buffer","Error",MB_OK);
		return;
	}

	m_cInventory.DeleteItemAll();//clear all before adding new data
	m_cInventory.SetAddLine ( 6, true );
	WORD wSIZEX = cInven.GetSizeX();
	WORD wSIZEY = cInven.GetSizeY();
	if ( wSIZEX==EM_INVENSIZE_X && wSIZEY==EM_INVENSIZE_Y )
	{
		m_cInventory.Assign ( cInven );
	}
	else
	{
		m_cInventory.CleanUp ();

		m_cInventory.SetState ( EM_INVENSIZE_X, EM_INVENSIZE_Y );

		GLInventory::CELL_MAP* pmapITEM = cInven.GetItemList();
		GLInventory::CELL_MAP_CITER pos = pmapITEM->begin();
		GLInventory::CELL_MAP_CITER end = pmapITEM->end();
		for ( ; pos!=end; ++pos )
		{
			m_cInventory.InsertItem ( (*pos).second->sItemCustom );
		}
	}

	ShowInven ();
	SetInvenPageState ( this,IDC_BUTTON_P1 );
}

void CRanManagerCharInven::ShowInven ()
{
	SetWin_Num_int(this,IDC_EDIT_TOTAL,m_cInventory.CountItemTotal() );
	int nNum = 0;
	TCHAR szTemp[128] = {0};
	for (int X = 0; X < EM_INVENSIZE_X; X++ )
	{
		for (int Y = 0; Y < EM_INVENSIZE_Y; Y++ )
		{
			SINVENITEM* sItem = m_cInventory.FindPosItem(X,Y);
			if (sItem)	_snprintf( szTemp, 128, "%d_%d",sItem->sItemCustom.sNativeID.wMainID,sItem->sItemCustom.sNativeID.wSubID );
			else	_snprintf( szTemp, 128, "%s","Empty" );

			switch (nNum)
			{
				case	0:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_0,(const TCHAR*)szTemp );
				case	1:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_1,(const TCHAR*)szTemp );
				case	2:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_2,(const TCHAR*)szTemp );
				case	3:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_3,(const TCHAR*)szTemp );
				case	4:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_4,(const TCHAR*)szTemp );
				case	5:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_5,(const TCHAR*)szTemp );
				case	6:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_6,(const TCHAR*)szTemp );
				case	7:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_7,(const TCHAR*)szTemp );
				case	8:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_8,(const TCHAR*)szTemp );
				case	9:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_9,(const TCHAR*)szTemp );

				case	10:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_10,(const TCHAR*)szTemp );
				case	11:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_11,(const TCHAR*)szTemp );
				case	12:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_12,(const TCHAR*)szTemp );
				case	13:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_13,(const TCHAR*)szTemp );
				case	14:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_14,(const TCHAR*)szTemp );
				case	15:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_15,(const TCHAR*)szTemp );
				case	16:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_16,(const TCHAR*)szTemp );
				case	17:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_17,(const TCHAR*)szTemp );
				case	18:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_18,(const TCHAR*)szTemp );
				case	19:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_19,(const TCHAR*)szTemp );

				case	20:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_20,(const TCHAR*)szTemp );
				case	21:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_21,(const TCHAR*)szTemp );
				case	22:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_22,(const TCHAR*)szTemp );
				case	23:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_23,(const TCHAR*)szTemp );
				case	24:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_24,(const TCHAR*)szTemp );
				case	25:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_25,(const TCHAR*)szTemp );
				case	26:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_26,(const TCHAR*)szTemp );
				case	27:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_27,(const TCHAR*)szTemp );
				case	28:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_28,(const TCHAR*)szTemp );
				case	29:	SetWin_Text ( this, IDC_BUTTON_INVEN_0_29,(const TCHAR*)szTemp );

				case	30:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_0,(const TCHAR*)szTemp );
				case	31:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_1,(const TCHAR*)szTemp );
				case	32:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_2,(const TCHAR*)szTemp );
				case	33:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_3,(const TCHAR*)szTemp );
				case	34:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_4,(const TCHAR*)szTemp );
				case	35:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_5,(const TCHAR*)szTemp );
				case	36:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_6,(const TCHAR*)szTemp );
				case	37:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_7,(const TCHAR*)szTemp );
				case	38:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_8,(const TCHAR*)szTemp );
				case	39:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_9,(const TCHAR*)szTemp );

				case	40:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_10,(const TCHAR*)szTemp );
				case	41:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_11,(const TCHAR*)szTemp );
				case	42:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_12,(const TCHAR*)szTemp );
				case	43:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_13,(const TCHAR*)szTemp );
				case	44:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_14,(const TCHAR*)szTemp );
				case	45:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_15,(const TCHAR*)szTemp );
				case	46:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_16,(const TCHAR*)szTemp );
				case	47:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_17,(const TCHAR*)szTemp );
				case	48:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_18,(const TCHAR*)szTemp );
				case	49:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_19,(const TCHAR*)szTemp );

				case	50:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_20,(const TCHAR*)szTemp );
				case	51:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_21,(const TCHAR*)szTemp );
				case	52:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_22,(const TCHAR*)szTemp );
				case	53:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_23,(const TCHAR*)szTemp );
				case	54:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_24,(const TCHAR*)szTemp );
				case	55:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_25,(const TCHAR*)szTemp );
				case	56:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_26,(const TCHAR*)szTemp );
				case	57:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_27,(const TCHAR*)szTemp );
				case	58:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_28,(const TCHAR*)szTemp );
				case	59:	SetWin_Text ( this, IDC_BUTTON_INVEN_1_29,(const TCHAR*)szTemp );

				case	60:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_0,(const TCHAR*)szTemp );
				case	61:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_1,(const TCHAR*)szTemp );
				case	62:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_2,(const TCHAR*)szTemp );
				case	63:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_3,(const TCHAR*)szTemp );
				case	64:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_4,(const TCHAR*)szTemp );
				case	65:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_5,(const TCHAR*)szTemp );
				case	66:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_6,(const TCHAR*)szTemp );
				case	67:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_7,(const TCHAR*)szTemp );
				case	68:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_8,(const TCHAR*)szTemp );
				case	69:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_9,(const TCHAR*)szTemp );

				case	70:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_10,(const TCHAR*)szTemp );
				case	71:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_11,(const TCHAR*)szTemp );
				case	72:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_12,(const TCHAR*)szTemp );
				case	73:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_13,(const TCHAR*)szTemp );
				case	74:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_14,(const TCHAR*)szTemp );
				case	75:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_15,(const TCHAR*)szTemp );
				case	76:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_16,(const TCHAR*)szTemp );
				case	77:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_17,(const TCHAR*)szTemp );
				case	78:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_18,(const TCHAR*)szTemp );
				case	79:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_19,(const TCHAR*)szTemp );

				case	80:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_20,(const TCHAR*)szTemp );
				case	81:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_21,(const TCHAR*)szTemp );
				case	82:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_22,(const TCHAR*)szTemp );
				case	83:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_23,(const TCHAR*)szTemp );
				case	84:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_24,(const TCHAR*)szTemp );
				case	85:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_25,(const TCHAR*)szTemp );
				case	86:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_26,(const TCHAR*)szTemp );
				case	87:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_27,(const TCHAR*)szTemp );
				case	88:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_28,(const TCHAR*)szTemp );
				case	89:	SetWin_Text ( this, IDC_BUTTON_INVEN_2_29,(const TCHAR*)szTemp );

				case	90:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_0,(const TCHAR*)szTemp );
				case	91:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_1,(const TCHAR*)szTemp );
				case	92:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_2,(const TCHAR*)szTemp );
				case	93:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_3,(const TCHAR*)szTemp );
				case	94:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_4,(const TCHAR*)szTemp );
				case	95:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_5,(const TCHAR*)szTemp );
				case	96:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_6,(const TCHAR*)szTemp );
				case	97:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_7,(const TCHAR*)szTemp );
				case	98:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_8,(const TCHAR*)szTemp );
				case	99:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_9,(const TCHAR*)szTemp );

				case	100:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_10,(const TCHAR*)szTemp );
				case	101:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_11,(const TCHAR*)szTemp );
				case	102:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_12,(const TCHAR*)szTemp );
				case	103:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_13,(const TCHAR*)szTemp );
				case	104:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_14,(const TCHAR*)szTemp );
				case	105:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_15,(const TCHAR*)szTemp );
				case	106:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_16,(const TCHAR*)szTemp );
				case	107:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_17,(const TCHAR*)szTemp );
				case	108:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_18,(const TCHAR*)szTemp );
				case	109:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_19,(const TCHAR*)szTemp );

				case	110:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_20,(const TCHAR*)szTemp );
				case	111:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_21,(const TCHAR*)szTemp );
				case	112:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_22,(const TCHAR*)szTemp );
				case	113:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_23,(const TCHAR*)szTemp );
				case	114:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_24,(const TCHAR*)szTemp );
				case	115:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_25,(const TCHAR*)szTemp );
				case	116:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_26,(const TCHAR*)szTemp );
				case	117:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_27,(const TCHAR*)szTemp );
				case	118:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_28,(const TCHAR*)szTemp );
				case	119:	SetWin_Text ( this, IDC_BUTTON_INVEN_3_29,(const TCHAR*)szTemp );

				case	120:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_0,(const TCHAR*)szTemp );
				case	121:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_1,(const TCHAR*)szTemp );
				case	122:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_2,(const TCHAR*)szTemp );
				case	123:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_3,(const TCHAR*)szTemp );
				case	124:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_4,(const TCHAR*)szTemp );
				case	125:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_5,(const TCHAR*)szTemp );
				case	126:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_6,(const TCHAR*)szTemp );
				case	127:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_7,(const TCHAR*)szTemp );
				case	128:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_8,(const TCHAR*)szTemp );
				case	129:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_9,(const TCHAR*)szTemp );

				case	130:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_10,(const TCHAR*)szTemp );
				case	131:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_11,(const TCHAR*)szTemp );
				case	132:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_12,(const TCHAR*)szTemp );
				case	133:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_13,(const TCHAR*)szTemp );
				case	134:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_14,(const TCHAR*)szTemp );
				case	135:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_15,(const TCHAR*)szTemp );
				case	136:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_16,(const TCHAR*)szTemp );
				case	137:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_17,(const TCHAR*)szTemp );
				case	138:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_18,(const TCHAR*)szTemp );
				case	139:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_19,(const TCHAR*)szTemp );

				case	140:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_20,(const TCHAR*)szTemp );
				case	141:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_21,(const TCHAR*)szTemp );
				case	142:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_22,(const TCHAR*)szTemp );
				case	143:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_23,(const TCHAR*)szTemp );
				case	144:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_24,(const TCHAR*)szTemp );
				case	145:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_25,(const TCHAR*)szTemp );
				case	146:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_26,(const TCHAR*)szTemp );
				case	147:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_27,(const TCHAR*)szTemp );
				case	148:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_28,(const TCHAR*)szTemp );
				case	149:	SetWin_Text ( this, IDC_BUTTON_INVEN_4_29,(const TCHAR*)szTemp );

				case	150:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_0,(const TCHAR*)szTemp );
				case	151:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_1,(const TCHAR*)szTemp );
				case	152:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_2,(const TCHAR*)szTemp );
				case	153:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_3,(const TCHAR*)szTemp );
				case	154:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_4,(const TCHAR*)szTemp );
				case	155:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_5,(const TCHAR*)szTemp );
				case	156:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_6,(const TCHAR*)szTemp );
				case	157:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_7,(const TCHAR*)szTemp );
				case	158:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_8,(const TCHAR*)szTemp );
				case	159:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_9,(const TCHAR*)szTemp );

				case	160:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_10,(const TCHAR*)szTemp );
				case	161:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_11,(const TCHAR*)szTemp );
				case	162:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_12,(const TCHAR*)szTemp );
				case	163:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_13,(const TCHAR*)szTemp );
				case	164:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_14,(const TCHAR*)szTemp );
				case	165:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_15,(const TCHAR*)szTemp );
				case	166:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_16,(const TCHAR*)szTemp );
				case	167:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_17,(const TCHAR*)szTemp );
				case	168:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_18,(const TCHAR*)szTemp );
				case	169:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_19,(const TCHAR*)szTemp );

				case	170:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_20,(const TCHAR*)szTemp );
				case	171:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_21,(const TCHAR*)szTemp );
				case	172:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_22,(const TCHAR*)szTemp );
				case	173:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_23,(const TCHAR*)szTemp );
				case	174:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_24,(const TCHAR*)szTemp );
				case	175:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_25,(const TCHAR*)szTemp );
				case	176:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_26,(const TCHAR*)szTemp );
				case	177:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_27,(const TCHAR*)szTemp );
				case	178:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_28,(const TCHAR*)szTemp );
				case	179:	SetWin_Text ( this, IDC_BUTTON_INVEN_5_29,(const TCHAR*)szTemp );
			};
			nNum++;
		}
	}
}

void CRanManagerCharInven::OnBnClickedButtonInven00()	{	ViewItem(0,0);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_0 );	}
void CRanManagerCharInven::OnBnClickedButtonInven01()	{	ViewItem(0,1);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_1 );	}
void CRanManagerCharInven::OnBnClickedButtonInven02()	{	ViewItem(0,2);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_2 );	}
void CRanManagerCharInven::OnBnClickedButtonInven03()	{	ViewItem(0,3);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_3 );	}
void CRanManagerCharInven::OnBnClickedButtonInven04()	{	ViewItem(0,4);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_4 );	}
void CRanManagerCharInven::OnBnClickedButtonInven05()	{	ViewItem(0,5);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_5 );	}
void CRanManagerCharInven::OnBnClickedButtonInven06()	{	ViewItem(0,6);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_6 );	}
void CRanManagerCharInven::OnBnClickedButtonInven07()	{	ViewItem(0,7);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_7 );	}
void CRanManagerCharInven::OnBnClickedButtonInven08()	{	ViewItem(0,8);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_8 );	}
void CRanManagerCharInven::OnBnClickedButtonInven09()	{	ViewItem(0,9);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_9 );	}
void CRanManagerCharInven::OnBnClickedButtonInven010()	{	ViewItem(0,10);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_10 );	}
void CRanManagerCharInven::OnBnClickedButtonInven011()	{	ViewItem(0,11);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_11 );	}
void CRanManagerCharInven::OnBnClickedButtonInven012()	{	ViewItem(0,12);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_12 );	}
void CRanManagerCharInven::OnBnClickedButtonInven013()	{	ViewItem(0,13);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_13 );	}
void CRanManagerCharInven::OnBnClickedButtonInven014()	{	ViewItem(0,14);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_14 );	}
void CRanManagerCharInven::OnBnClickedButtonInven015()	{	ViewItem(0,15);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_15 );	}
void CRanManagerCharInven::OnBnClickedButtonInven016()	{	ViewItem(0,16);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_16 );	}
void CRanManagerCharInven::OnBnClickedButtonInven017()	{	ViewItem(0,17);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_17 );	}
void CRanManagerCharInven::OnBnClickedButtonInven018()	{	ViewItem(0,18);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_18 );	}
void CRanManagerCharInven::OnBnClickedButtonInven019()	{	ViewItem(0,19);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_19 );	}
void CRanManagerCharInven::OnBnClickedButtonInven020()	{	ViewItem(0,10);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_20 );	}
void CRanManagerCharInven::OnBnClickedButtonInven021()	{	ViewItem(0,21);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_21 );	}
void CRanManagerCharInven::OnBnClickedButtonInven022()	{	ViewItem(0,22);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_22 );	}
void CRanManagerCharInven::OnBnClickedButtonInven023()	{	ViewItem(0,23);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_23 );	}
void CRanManagerCharInven::OnBnClickedButtonInven024()	{	ViewItem(0,24);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_24 );	}
void CRanManagerCharInven::OnBnClickedButtonInven025()	{	ViewItem(0,25);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_25 );	}
void CRanManagerCharInven::OnBnClickedButtonInven026()	{	ViewItem(0,26);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_26 );	}
void CRanManagerCharInven::OnBnClickedButtonInven027()	{	ViewItem(0,27);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_27 );	}
void CRanManagerCharInven::OnBnClickedButtonInven028()	{	ViewItem(0,28);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_28 );	}
void CRanManagerCharInven::OnBnClickedButtonInven029()	{	ViewItem(0,29);	SetInvenItemState ( this,IDC_BUTTON_INVEN_0_29 );	}

void CRanManagerCharInven::OnBnClickedButtonInven10()	{	ViewItem(1,0);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_0 );	}
void CRanManagerCharInven::OnBnClickedButtonInven11()	{	ViewItem(1,1);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_1 );	}
void CRanManagerCharInven::OnBnClickedButtonInven12()	{	ViewItem(1,2);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_2 );	}
void CRanManagerCharInven::OnBnClickedButtonInven13()	{	ViewItem(1,3);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_3 );	}
void CRanManagerCharInven::OnBnClickedButtonInven14()	{	ViewItem(1,4);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_4 );	}
void CRanManagerCharInven::OnBnClickedButtonInven15()	{	ViewItem(1,5);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_5 );	}
void CRanManagerCharInven::OnBnClickedButtonInven16()	{	ViewItem(1,6);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_6 );	}
void CRanManagerCharInven::OnBnClickedButtonInven17()	{	ViewItem(1,7);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_7 );	}
void CRanManagerCharInven::OnBnClickedButtonInven18()	{	ViewItem(1,8);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_8 );	}
void CRanManagerCharInven::OnBnClickedButtonInven19()	{	ViewItem(1,9);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_9 );	}
void CRanManagerCharInven::OnBnClickedButtonInven110()	{	ViewItem(1,10);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_10 );	}
void CRanManagerCharInven::OnBnClickedButtonInven111()	{	ViewItem(1,11);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_11 );	}
void CRanManagerCharInven::OnBnClickedButtonInven112()	{	ViewItem(1,12);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_12 );	}
void CRanManagerCharInven::OnBnClickedButtonInven113()	{	ViewItem(1,13);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_13 );	}
void CRanManagerCharInven::OnBnClickedButtonInven114()	{	ViewItem(1,14);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_14 );	}
void CRanManagerCharInven::OnBnClickedButtonInven115()	{	ViewItem(1,15);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_15 );	}
void CRanManagerCharInven::OnBnClickedButtonInven116()	{	ViewItem(1,16);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_16 );	}
void CRanManagerCharInven::OnBnClickedButtonInven117()	{	ViewItem(1,17);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_17 );	}
void CRanManagerCharInven::OnBnClickedButtonInven118()	{	ViewItem(1,18);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_18 );	}
void CRanManagerCharInven::OnBnClickedButtonInven119()	{	ViewItem(1,19);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_19 );	}
void CRanManagerCharInven::OnBnClickedButtonInven120()	{	ViewItem(1,20);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_20 );	}
void CRanManagerCharInven::OnBnClickedButtonInven121()	{	ViewItem(1,21);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_21 );	}
void CRanManagerCharInven::OnBnClickedButtonInven122()	{	ViewItem(1,22);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_22 );	}
void CRanManagerCharInven::OnBnClickedButtonInven123()	{	ViewItem(1,23);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_23 );	}
void CRanManagerCharInven::OnBnClickedButtonInven124()	{	ViewItem(1,24);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_24 );	}
void CRanManagerCharInven::OnBnClickedButtonInven125()	{	ViewItem(1,25);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_25 );	}
void CRanManagerCharInven::OnBnClickedButtonInven126()	{	ViewItem(1,26);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_26 );	}
void CRanManagerCharInven::OnBnClickedButtonInven127()	{	ViewItem(1,27);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_27 );	}
void CRanManagerCharInven::OnBnClickedButtonInven128()	{	ViewItem(1,28);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_28 );	}
void CRanManagerCharInven::OnBnClickedButtonInven129()	{	ViewItem(1,29);	SetInvenItemState ( this,IDC_BUTTON_INVEN_1_29 );	}

void CRanManagerCharInven::OnBnClickedButtonInven20()	{	ViewItem(2,0);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_0 );	}
void CRanManagerCharInven::OnBnClickedButtonInven21()	{	ViewItem(2,1);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_1 );	}
void CRanManagerCharInven::OnBnClickedButtonInven22()	{	ViewItem(2,2);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_2 );	}
void CRanManagerCharInven::OnBnClickedButtonInven23()	{	ViewItem(2,3);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_3 );	}
void CRanManagerCharInven::OnBnClickedButtonInven24()	{	ViewItem(2,4);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_4 );	}
void CRanManagerCharInven::OnBnClickedButtonInven25()	{	ViewItem(2,5);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_5 );	}
void CRanManagerCharInven::OnBnClickedButtonInven26()	{	ViewItem(2,6);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_6 );	}
void CRanManagerCharInven::OnBnClickedButtonInven27()	{	ViewItem(2,7);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_7 );	}
void CRanManagerCharInven::OnBnClickedButtonInven28()	{	ViewItem(2,8);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_8 );	}
void CRanManagerCharInven::OnBnClickedButtonInven29()	{	ViewItem(2,9);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_9 );	}
void CRanManagerCharInven::OnBnClickedButtonInven210()	{	ViewItem(2,10);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_10 );	}
void CRanManagerCharInven::OnBnClickedButtonInven211()	{	ViewItem(2,11);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_11 );	}
void CRanManagerCharInven::OnBnClickedButtonInven212()	{	ViewItem(2,12);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_12 );	}
void CRanManagerCharInven::OnBnClickedButtonInven213()	{	ViewItem(2,13);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_13 );	}
void CRanManagerCharInven::OnBnClickedButtonInven214()	{	ViewItem(2,14);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_14 );	}
void CRanManagerCharInven::OnBnClickedButtonInven215()	{	ViewItem(2,15);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_15 );	}
void CRanManagerCharInven::OnBnClickedButtonInven216()	{	ViewItem(2,16);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_16 );	}
void CRanManagerCharInven::OnBnClickedButtonInven217()	{	ViewItem(2,17);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_17 );	}
void CRanManagerCharInven::OnBnClickedButtonInven218()	{	ViewItem(2,18);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_18 );	}
void CRanManagerCharInven::OnBnClickedButtonInven219()	{	ViewItem(2,19);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_19 );	}
void CRanManagerCharInven::OnBnClickedButtonInven220()	{	ViewItem(2,20);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_20 );	}
void CRanManagerCharInven::OnBnClickedButtonInven221()	{	ViewItem(2,21);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_21 );	}
void CRanManagerCharInven::OnBnClickedButtonInven222()	{	ViewItem(2,22);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_22 );	}
void CRanManagerCharInven::OnBnClickedButtonInven223()	{	ViewItem(2,23);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_23 );	}
void CRanManagerCharInven::OnBnClickedButtonInven224()	{	ViewItem(2,24);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_24 );	}
void CRanManagerCharInven::OnBnClickedButtonInven225()	{	ViewItem(2,25);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_25 );	}
void CRanManagerCharInven::OnBnClickedButtonInven226()	{	ViewItem(2,26);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_26 );	}
void CRanManagerCharInven::OnBnClickedButtonInven227()	{	ViewItem(2,27);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_27 );	}
void CRanManagerCharInven::OnBnClickedButtonInven228()	{	ViewItem(2,28);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_28 );	}
void CRanManagerCharInven::OnBnClickedButtonInven229()	{	ViewItem(2,29);	SetInvenItemState ( this,IDC_BUTTON_INVEN_2_29 );	}

void CRanManagerCharInven::OnBnClickedButtonInven30()	{	ViewItem(3,0);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_0 );	}
void CRanManagerCharInven::OnBnClickedButtonInven31()	{	ViewItem(3,1);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_1 );	}
void CRanManagerCharInven::OnBnClickedButtonInven32()	{	ViewItem(3,2);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_2 );	}
void CRanManagerCharInven::OnBnClickedButtonInven33()	{	ViewItem(3,3);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_3 );	}
void CRanManagerCharInven::OnBnClickedButtonInven34()	{	ViewItem(3,4);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_4 );	}
void CRanManagerCharInven::OnBnClickedButtonInven35()	{	ViewItem(3,5);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_5 );	}
void CRanManagerCharInven::OnBnClickedButtonInven36()	{	ViewItem(3,6);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_6 );	}
void CRanManagerCharInven::OnBnClickedButtonInven37()	{	ViewItem(3,7);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_7 );	}
void CRanManagerCharInven::OnBnClickedButtonInven38()	{	ViewItem(3,8);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_8 );	}
void CRanManagerCharInven::OnBnClickedButtonInven39()	{	ViewItem(3,9);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_9 );	}
void CRanManagerCharInven::OnBnClickedButtonInven310()	{	ViewItem(3,10);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_10 );	}
void CRanManagerCharInven::OnBnClickedButtonInven311()	{	ViewItem(3,11);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_11 );	}
void CRanManagerCharInven::OnBnClickedButtonInven312()	{	ViewItem(3,12);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_12 );	}
void CRanManagerCharInven::OnBnClickedButtonInven313()	{	ViewItem(3,13);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_13 );	}
void CRanManagerCharInven::OnBnClickedButtonInven314()	{	ViewItem(3,14);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_14 );	}
void CRanManagerCharInven::OnBnClickedButtonInven315()	{	ViewItem(3,15);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_15 );	}
void CRanManagerCharInven::OnBnClickedButtonInven316()	{	ViewItem(3,16);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_16 );	}
void CRanManagerCharInven::OnBnClickedButtonInven317()	{	ViewItem(3,17);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_17 );	}
void CRanManagerCharInven::OnBnClickedButtonInven318()	{	ViewItem(3,18);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_18 );	}
void CRanManagerCharInven::OnBnClickedButtonInven319()	{	ViewItem(3,19);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_19 );	}
void CRanManagerCharInven::OnBnClickedButtonInven320()	{	ViewItem(3,20);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_20 );	}
void CRanManagerCharInven::OnBnClickedButtonInven321()	{	ViewItem(3,21);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_21 );	}
void CRanManagerCharInven::OnBnClickedButtonInven322()	{	ViewItem(3,22);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_22 );	}
void CRanManagerCharInven::OnBnClickedButtonInven323()	{	ViewItem(3,23);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_23 );	}
void CRanManagerCharInven::OnBnClickedButtonInven324()	{	ViewItem(3,24);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_24 );	}
void CRanManagerCharInven::OnBnClickedButtonInven325()	{	ViewItem(3,25);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_25 );	}
void CRanManagerCharInven::OnBnClickedButtonInven326()	{	ViewItem(3,26);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_26 );	}
void CRanManagerCharInven::OnBnClickedButtonInven327()	{	ViewItem(3,27);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_27 );	}
void CRanManagerCharInven::OnBnClickedButtonInven328()	{	ViewItem(3,28);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_28 );	}
void CRanManagerCharInven::OnBnClickedButtonInven329()	{	ViewItem(3,29);	SetInvenItemState ( this,IDC_BUTTON_INVEN_3_29 );	}

void CRanManagerCharInven::OnBnClickedButtonInven40()	{	ViewItem(4,0);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_0 );	}
void CRanManagerCharInven::OnBnClickedButtonInven41()	{	ViewItem(4,1);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_1 );	}
void CRanManagerCharInven::OnBnClickedButtonInven42()	{	ViewItem(4,2);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_2 );	}
void CRanManagerCharInven::OnBnClickedButtonInven43()	{	ViewItem(4,3);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_3 );	}
void CRanManagerCharInven::OnBnClickedButtonInven44()	{	ViewItem(4,4);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_4 );	}
void CRanManagerCharInven::OnBnClickedButtonInven45()	{	ViewItem(4,5);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_5 );	}
void CRanManagerCharInven::OnBnClickedButtonInven46()	{	ViewItem(4,6);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_6 );	}
void CRanManagerCharInven::OnBnClickedButtonInven47()	{	ViewItem(4,7);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_7 );	}
void CRanManagerCharInven::OnBnClickedButtonInven48()	{	ViewItem(4,8);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_8 );	}
void CRanManagerCharInven::OnBnClickedButtonInven49()	{	ViewItem(4,9);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_9 );	}
void CRanManagerCharInven::OnBnClickedButtonInven410()	{	ViewItem(4,10);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_10 );	}
void CRanManagerCharInven::OnBnClickedButtonInven411()	{	ViewItem(4,11);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_11 );	}
void CRanManagerCharInven::OnBnClickedButtonInven412()	{	ViewItem(4,12);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_12 );	}
void CRanManagerCharInven::OnBnClickedButtonInven413()	{	ViewItem(4,13);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_13 );	}
void CRanManagerCharInven::OnBnClickedButtonInven414()	{	ViewItem(4,14);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_14 );	}
void CRanManagerCharInven::OnBnClickedButtonInven415()	{	ViewItem(4,15);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_15 );	}
void CRanManagerCharInven::OnBnClickedButtonInven416()	{	ViewItem(4,16);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_16 );	}
void CRanManagerCharInven::OnBnClickedButtonInven417()	{	ViewItem(4,17);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_17 );	}
void CRanManagerCharInven::OnBnClickedButtonInven418()	{	ViewItem(4,18);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_18 );	}
void CRanManagerCharInven::OnBnClickedButtonInven419()	{	ViewItem(4,19);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_19 );	}
void CRanManagerCharInven::OnBnClickedButtonInven420()	{	ViewItem(4,20);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_20 );	}
void CRanManagerCharInven::OnBnClickedButtonInven421()	{	ViewItem(4,21);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_21 );	}
void CRanManagerCharInven::OnBnClickedButtonInven422()	{	ViewItem(4,22);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_22 );	}
void CRanManagerCharInven::OnBnClickedButtonInven423()	{	ViewItem(4,23);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_23 );	}
void CRanManagerCharInven::OnBnClickedButtonInven424()	{	ViewItem(4,24);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_24 );	}
void CRanManagerCharInven::OnBnClickedButtonInven425()	{	ViewItem(4,25);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_25 );	}
void CRanManagerCharInven::OnBnClickedButtonInven426()	{	ViewItem(4,26);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_26 );	}
void CRanManagerCharInven::OnBnClickedButtonInven427()	{	ViewItem(4,27);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_27 );	}
void CRanManagerCharInven::OnBnClickedButtonInven428()	{	ViewItem(4,28);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_28 );	}
void CRanManagerCharInven::OnBnClickedButtonInven429()	{	ViewItem(4,29);	SetInvenItemState ( this,IDC_BUTTON_INVEN_4_29 );	}

void CRanManagerCharInven::OnBnClickedButtonInven50()	{	ViewItem(5,0);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_0 );	}
void CRanManagerCharInven::OnBnClickedButtonInven51()	{	ViewItem(5,1);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_1 );	}
void CRanManagerCharInven::OnBnClickedButtonInven52()	{	ViewItem(5,2);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_2 );	}
void CRanManagerCharInven::OnBnClickedButtonInven53()	{	ViewItem(5,3);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_3 );	}
void CRanManagerCharInven::OnBnClickedButtonInven54()	{	ViewItem(5,4);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_4 );	}
void CRanManagerCharInven::OnBnClickedButtonInven55()	{	ViewItem(5,5);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_5 );	}
void CRanManagerCharInven::OnBnClickedButtonInven56()	{	ViewItem(5,6);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_6 );	}
void CRanManagerCharInven::OnBnClickedButtonInven57()	{	ViewItem(5,7);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_7 );	}
void CRanManagerCharInven::OnBnClickedButtonInven58()	{	ViewItem(5,8);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_8 );	}
void CRanManagerCharInven::OnBnClickedButtonInven59()	{	ViewItem(5,9);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_9 );	}
void CRanManagerCharInven::OnBnClickedButtonInven510()	{	ViewItem(5,10);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_10 );	}
void CRanManagerCharInven::OnBnClickedButtonInven511()	{	ViewItem(5,11);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_11 );	}
void CRanManagerCharInven::OnBnClickedButtonInven512()	{	ViewItem(5,12);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_12 );	}
void CRanManagerCharInven::OnBnClickedButtonInven513()	{	ViewItem(5,13);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_13 );	}
void CRanManagerCharInven::OnBnClickedButtonInven514()	{	ViewItem(5,14);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_14 );	}
void CRanManagerCharInven::OnBnClickedButtonInven515()	{	ViewItem(5,15);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_15 );	}
void CRanManagerCharInven::OnBnClickedButtonInven516()	{	ViewItem(5,16);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_16 );	}
void CRanManagerCharInven::OnBnClickedButtonInven517()	{	ViewItem(5,17);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_17 );	}
void CRanManagerCharInven::OnBnClickedButtonInven518()	{	ViewItem(5,18);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_18 );	}
void CRanManagerCharInven::OnBnClickedButtonInven519()	{	ViewItem(5,19);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_19 );	}
void CRanManagerCharInven::OnBnClickedButtonInven520()	{	ViewItem(5,20);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_20 );	}
void CRanManagerCharInven::OnBnClickedButtonInven521()	{	ViewItem(5,21);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_21 );	}
void CRanManagerCharInven::OnBnClickedButtonInven522()	{	ViewItem(5,22);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_22 );	}
void CRanManagerCharInven::OnBnClickedButtonInven523()	{	ViewItem(5,23);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_23 );	}
void CRanManagerCharInven::OnBnClickedButtonInven524()	{	ViewItem(5,24);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_24 );	}
void CRanManagerCharInven::OnBnClickedButtonInven525()	{	ViewItem(5,25);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_25 );	}
void CRanManagerCharInven::OnBnClickedButtonInven526()	{	ViewItem(5,26);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_26 );	}
void CRanManagerCharInven::OnBnClickedButtonInven527()	{	ViewItem(5,27);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_27 );	}
void CRanManagerCharInven::OnBnClickedButtonInven528()	{	ViewItem(5,28);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_28 );	}
void CRanManagerCharInven::OnBnClickedButtonInven529()	{	ViewItem(5,29);	SetInvenItemState ( this,IDC_BUTTON_INVEN_5_29 );	}

void CRanManagerCharInven::SetInvenItemState ( CDialog *pDlg,int nID )
{
	ResetInvenItemState (this);
	CButton *pBtn;
	switch (nID)
	{
	case IDC_BUTTON_INVEN_0_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_9 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_10:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_10 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_11:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_11 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_12:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_12 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_13:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_13 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_14:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_14 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_15:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_15 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_16:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_16 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_17:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_17 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_18:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_18 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_19:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_19 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_20:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_20 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_21:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_21 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_22:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_22 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_23:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_23 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_24:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_24 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_25:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_25 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_26:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_26 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_27:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_27 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_28:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_28 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_0_29:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_29 );	pBtn->SetState(TRUE);	break;

	case IDC_BUTTON_INVEN_1_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_9 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_10:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_10 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_11:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_11 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_12:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_12 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_13:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_13 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_14:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_14 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_15:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_15 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_16:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_16 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_17:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_17 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_18:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_18 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_19:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_19 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_20:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_20 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_21:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_21 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_22:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_22 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_23:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_23 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_24:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_24 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_25:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_25 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_26:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_26 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_27:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_27 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_28:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_28 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_1_29:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_29 );	pBtn->SetState(TRUE);	break;

	case IDC_BUTTON_INVEN_2_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_9 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_10:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_10 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_11:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_11 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_12:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_12 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_13:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_13 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_14:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_14 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_15:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_15 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_16:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_16 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_17:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_17 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_18:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_18 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_19:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_19 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_20:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_20 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_21:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_21 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_22:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_22 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_23:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_23 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_24:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_24 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_25:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_25 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_26:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_26 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_27:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_27 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_28:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_28 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_2_29:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_29 );	pBtn->SetState(TRUE);	break;

	case IDC_BUTTON_INVEN_3_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_9 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_10:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_10 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_11:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_11 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_12:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_12 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_13:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_13 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_14:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_14 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_15:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_15 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_16:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_16 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_17:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_17 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_18:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_18 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_19:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_19 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_20:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_20 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_21:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_21 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_22:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_22 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_23:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_23 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_24:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_24 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_25:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_25 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_26:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_26 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_27:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_27 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_28:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_28 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_3_29:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_29 );	pBtn->SetState(TRUE);	break;

	case IDC_BUTTON_INVEN_4_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_9 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_10:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_10 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_11:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_11 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_12:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_12 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_13:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_13 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_14:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_14 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_15:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_15 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_16:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_16 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_17:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_17 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_18:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_18 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_19:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_19 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_20:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_20 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_21:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_21 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_22:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_22 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_23:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_23 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_24:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_24 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_25:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_25 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_26:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_26 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_27:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_27 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_28:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_28 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_4_29:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_29 );	pBtn->SetState(TRUE);	break;

	case IDC_BUTTON_INVEN_5_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_9 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_10:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_10 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_11:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_11 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_12:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_12 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_13:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_13 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_14:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_14 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_15:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_15 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_16:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_16 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_17:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_17 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_18:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_18 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_19:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_19 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_20:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_20 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_21:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_21 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_22:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_22 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_23:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_23 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_24:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_24 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_25:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_25 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_26:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_26 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_27:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_27 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_28:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_28 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_INVEN_5_29:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_29 );	pBtn->SetState(TRUE);	break;
	};
}

void CRanManagerCharInven::ResetInvenItemState ( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_9 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_10 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_11 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_12 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_13 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_14 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_15 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_16 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_17 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_18 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_19 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_20 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_21 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_22 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_23 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_24 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_25 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_26 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_27 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_28 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_29 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_9 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_10 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_11 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_12 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_13 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_14 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_15 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_16 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_17 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_18 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_19 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_20 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_21 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_22 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_23 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_24 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_25 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_26 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_27 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_28 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_29 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_9 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_10 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_11 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_12 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_13 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_14 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_15 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_16 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_17 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_18 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_19 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_20 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_21 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_22 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_23 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_24 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_25 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_26 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_27 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_28 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_29 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_9 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_10 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_11 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_12 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_13 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_14 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_15 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_16 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_17 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_18 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_19 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_20 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_21 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_22 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_23 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_24 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_25 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_26 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_27 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_28 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_29 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_9 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_10 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_11 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_12 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_13 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_14 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_15 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_16 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_17 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_18 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_19 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_20 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_21 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_22 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_23 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_24 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_25 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_26 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_27 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_28 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_29 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_9 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_10 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_11 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_12 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_13 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_14 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_15 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_16 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_17 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_18 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_19 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_20 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_21 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_22 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_23 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_24 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_25 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_26 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_27 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_28 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_29 );	pBtn->SetState(FALSE);

}

void CRanManagerCharInven::ViewItem(WORD X,WORD Y)
{
	nActiveItem_X = X;
	nActiveItem_Y = Y;

	SetWin_Enable(this,IDC_BTN_EDIT_ITEM_UPDATE,true);

	SINVENITEM* sItem = m_cInventory.FindPosItem(X,Y);
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
		SetWin_Enable(this,IDC_BTN_EDIT_ITEM_DELETE,false);

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
		//SetWin_Num_int ( this, IDC_EDIT_OWNER_ID,0);
		//SetWin_Num_int ( this, IDC_EDIT_ITEMCOLOR,32767);
	}
}

void CRanManagerCharInven::OnBnClickedButtonItemsearchM()
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

void CRanManagerCharInven::OnBnClickedButtonItemsearchCos()
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

void CRanManagerCharInven::OnBnClickedBtnEditItemDelete()
{
	if ( MessageBox ( "Do You Want to Delete this Item?, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		int X = GetWin_Num_int(this,IDC_EDIT_POS_X);
		int Y = GetWin_Num_int(this,IDC_EDIT_POS_Y);
		m_cInventory.DeleteItem(X,Y);
		ShowInven ();
		ViewItem(X,Y);
	}
}

void CRanManagerCharInven::OnBnClickedBtnEditItemUpdate()
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

		m_cInventory.DeleteItem(nActiveItem_X,nActiveItem_Y);
		if (m_cInventory.InsertItem(pItemUpdate,nActiveItem_X,nActiveItem_Y) )	MessageBox("Done Updating Item","Info",MB_OK);
		else	MessageBox("Error! Updating Item","Info",MB_OK);	

		ShowInven ();
		ViewItem(nActiveItem_X,nActiveItem_Y);
	}
}

void CRanManagerCharInven::OnBnClickedButtonResetCosExpire()
{
	if ( MessageBox ( "This Will Remove the costume, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		SetWin_Num_int ( this, IDC_EDIT_MID_COS,65535);
		SetWin_Num_int ( this, IDC_EDIT_SID_COS,65535);

		SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_1, 0 );
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_2, 0 );
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_3, 0 );
		SetWin_Text ( this, IDC_EDIT_NAME_COS,"Unknown Item");
	}
}

void CRanManagerCharInven::OnCbnSelchangeComboGentype()
{
}

void CRanManagerCharInven::OnBnClickedButtonInvencancel()
{
	m_pToolTab->ActivePage(CHARPAGE_MAIN,0);
}

void CRanManagerCharInven::OnBnClickedButtonInvensave()
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
	m_cInventory.GETITEM_BYBUFFER ( ByteStream );
	ByteStream.GetBuffer(pBuffer, dwSize);

	//write image
	if (pBuffer != NULL)
	{
		TCHAR szTemp[128] = {0};
		_snprintf( szTemp, 128, "UPDATE ChaInfo SET ChaInven=? WHERE (ChaNum=%u)", (DWORD)nChaNum );

		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("CharInven.txt","%s--%s",strTIME.c_str(),szTemp);

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
			MessageBox("Error Saving CharInven Binary!","error",MB_OK);
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
	MessageBox("Done Saving CharInven!","Info",MB_OK);

	pBuffer = NULL;
	ShowInven ();
}

void CRanManagerCharInven::OnBnClickedButtonInvenwipe()
{
	if ( MessageBox ( "This Will Remove All The Character Items In The Inventory!, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		m_cInventory.DeleteItemAll();
		ShowInven ();
		ViewItem(65535,65535);
	}
}

void CRanManagerCharInven::SetInvenPageState ( CDialog *pDlg,int nID )
{
	ResetInvenPageState (this);
	CButton *pBtn;
	switch (nID)
	{
	case IDC_BUTTON_P1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P3 );	pBtn->SetState(TRUE);	break;
	};
}

void CRanManagerCharInven::ResetInvenPageState ( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P3 );	pBtn->SetState(FALSE);
}

void CRanManagerCharInven::OnBnClickedButtonP1()
{
	SetInvenPageState ( this,IDC_BUTTON_P1 );
	SetWin_Num_int ( this, IDC_EDIT_PAGE, 1 );
	ShowPage1( this );
}

void CRanManagerCharInven::OnBnClickedButtonP2()
{
	SetInvenPageState ( this,IDC_BUTTON_P2 );
	SetWin_Num_int ( this, IDC_EDIT_PAGE, 2 );
	ShowPage2( this );
}

void CRanManagerCharInven::OnBnClickedButtonP3()
{
	SetInvenPageState ( this,IDC_BUTTON_P3 );
	SetWin_Num_int ( this, IDC_EDIT_PAGE, 3 );
	ShowPage3( this );
}
void CRanManagerCharInven::ShowPage1( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_0 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_1 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_2 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_3 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_4 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_5 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_6 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_7 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_8 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_9 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_10 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_11 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_12 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_13 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_14 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_15 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_16 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_17 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_18 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_19 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_20 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_21 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_22 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_23 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_24 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_25 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_26 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_27 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_28 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_29 );	pBtn->ShowWindow(SW_HIDE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_0 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_1 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_2 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_3 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_4 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_5 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_6 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_7 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_8 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_9 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_10 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_11 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_12 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_13 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_14 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_15 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_16 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_17 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_18 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_19 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_20 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_21 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_22 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_23 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_24 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_25 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_26 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_27 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_28 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_29 );	pBtn->ShowWindow(SW_HIDE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_0 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_1 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_2 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_3 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_4 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_5 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_6 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_7 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_8 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_9 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_10 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_11 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_12 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_13 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_14 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_15 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_16 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_17 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_18 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_19 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_20 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_21 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_22 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_23 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_24 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_25 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_26 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_27 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_28 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_29 );	pBtn->ShowWindow(SW_HIDE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_0 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_1 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_2 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_3 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_4 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_5 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_6 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_7 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_8 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_9 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_10 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_11 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_12 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_13 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_14 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_15 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_16 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_17 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_18 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_19 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_20 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_21 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_22 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_23 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_24 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_25 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_26 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_27 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_28 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_29 );	pBtn->ShowWindow(SW_HIDE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_0 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_1 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_2 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_3 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_4 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_5 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_6 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_7 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_8 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_9 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_10 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_11 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_12 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_13 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_14 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_15 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_16 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_17 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_18 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_19 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_20 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_21 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_22 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_23 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_24 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_25 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_26 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_27 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_28 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_29 );	pBtn->ShowWindow(SW_HIDE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_0 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_1 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_2 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_3 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_4 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_5 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_6 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_7 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_8 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_9 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_10 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_11 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_12 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_13 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_14 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_15 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_16 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_17 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_18 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_19 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_20 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_21 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_22 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_23 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_24 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_25 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_26 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_27 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_28 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_29 );	pBtn->ShowWindow(SW_HIDE);
}
void CRanManagerCharInven::ShowPage2( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_0 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_1 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_2 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_3 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_4 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_5 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_6 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_7 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_8 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_9 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_10 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_11 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_12 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_13 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_14 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_15 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_16 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_17 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_18 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_19 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_20 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_21 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_22 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_23 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_24 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_25 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_26 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_27 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_28 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_29 );	pBtn->ShowWindow(SW_HIDE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_0 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_1 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_2 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_3 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_4 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_5 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_6 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_7 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_8 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_9 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_10 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_11 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_12 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_13 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_14 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_15 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_16 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_17 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_18 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_19 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_20 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_21 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_22 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_23 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_24 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_25 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_26 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_27 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_28 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_29 );	pBtn->ShowWindow(SW_HIDE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_0 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_1 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_2 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_3 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_4 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_5 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_6 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_7 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_8 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_9 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_10 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_11 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_12 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_13 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_14 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_15 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_16 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_17 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_18 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_19 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_20 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_21 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_22 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_23 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_24 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_25 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_26 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_27 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_28 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_29 );	pBtn->ShowWindow(SW_HIDE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_0 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_1 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_2 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_3 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_4 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_5 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_6 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_7 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_8 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_9 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_10 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_11 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_12 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_13 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_14 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_15 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_16 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_17 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_18 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_19 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_20 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_21 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_22 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_23 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_24 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_25 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_26 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_27 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_28 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_29 );	pBtn->ShowWindow(SW_HIDE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_0 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_1 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_2 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_3 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_4 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_5 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_6 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_7 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_8 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_9 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_10 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_11 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_12 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_13 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_14 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_15 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_16 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_17 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_18 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_19 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_20 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_21 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_22 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_23 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_24 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_25 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_26 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_27 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_28 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_29 );	pBtn->ShowWindow(SW_HIDE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_0 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_1 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_2 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_3 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_4 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_5 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_6 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_7 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_8 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_9 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_10 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_11 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_12 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_13 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_14 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_15 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_16 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_17 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_18 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_19 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_20 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_21 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_22 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_23 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_24 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_25 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_26 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_27 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_28 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_29 );	pBtn->ShowWindow(SW_HIDE);
}
void CRanManagerCharInven::ShowPage3( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_0 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_1 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_2 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_3 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_4 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_5 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_6 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_7 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_8 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_9 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_10 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_11 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_12 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_13 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_14 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_15 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_16 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_17 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_18 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_19 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_20 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_21 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_22 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_23 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_24 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_25 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_26 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_27 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_28 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_0_29 );	pBtn->ShowWindow(SW_SHOW);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_0 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_1 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_2 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_3 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_4 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_5 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_6 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_7 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_8 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_9 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_10 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_11 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_12 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_13 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_14 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_15 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_16 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_17 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_18 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_19 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_20 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_21 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_22 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_23 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_24 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_25 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_26 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_27 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_28 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_1_29 );	pBtn->ShowWindow(SW_SHOW);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_0 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_1 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_2 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_3 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_4 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_5 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_6 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_7 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_8 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_9 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_10 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_11 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_12 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_13 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_14 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_15 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_16 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_17 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_18 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_19 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_20 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_21 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_22 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_23 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_24 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_25 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_26 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_27 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_28 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_2_29 );	pBtn->ShowWindow(SW_SHOW);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_0 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_1 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_2 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_3 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_4 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_5 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_6 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_7 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_8 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_9 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_10 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_11 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_12 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_13 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_14 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_15 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_16 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_17 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_18 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_19 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_20 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_21 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_22 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_23 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_24 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_25 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_26 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_27 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_28 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_3_29 );	pBtn->ShowWindow(SW_SHOW);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_0 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_1 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_2 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_3 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_4 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_5 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_6 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_7 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_8 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_9 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_10 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_11 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_12 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_13 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_14 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_15 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_16 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_17 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_18 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_19 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_20 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_21 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_22 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_23 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_24 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_25 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_26 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_27 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_28 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_4_29 );	pBtn->ShowWindow(SW_SHOW);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_0 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_1 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_2 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_3 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_4 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_5 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_6 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_7 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_8 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_9 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_10 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_11 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_12 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_13 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_14 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_15 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_16 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_17 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_18 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_19 );	pBtn->ShowWindow(SW_HIDE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_20 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_21 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_22 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_23 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_24 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_25 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_26 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_27 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_28 );	pBtn->ShowWindow(SW_SHOW);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_INVEN_5_29 );	pBtn->ShowWindow(SW_SHOW);
}
