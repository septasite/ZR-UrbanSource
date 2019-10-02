// RanManagerCharPutOn.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerCharPutOn.h"
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
#include ".\ranmanagercharputon.h"
// CRanManagerCharPutOn dialog

IMPLEMENT_DYNAMIC(CRanManagerCharPutOn, CPropertyPage)
CRanManagerCharPutOn::CRanManagerCharPutOn(LOGFONT logfont)
	: CPropertyPage(CRanManagerCharPutOn::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	nSlotSelected = 65535;
}

CRanManagerCharPutOn::~CRanManagerCharPutOn()
{
}

void CRanManagerCharPutOn::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GENTYPE, m_cGenType );
	DDX_Control(pDX, IDC_COMBO_OPTION1, m_cRandomOp1 );
	DDX_Control(pDX, IDC_COMBO_OPTION2, m_cRandomOp2 );
	DDX_Control(pDX, IDC_COMBO_OPTION3, m_cRandomOp3 );
	DDX_Control(pDX, IDC_COMBO_OPTION4, m_cRandomOp4 );
}


BEGIN_MESSAGE_MAP(CRanManagerCharPutOn, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_P_0, OnBnClickedButtonP0)
	ON_BN_CLICKED(IDC_BUTTON_P_1, OnBnClickedButtonP1)
	ON_BN_CLICKED(IDC_BUTTON_P_2, OnBnClickedButtonP2)
	ON_BN_CLICKED(IDC_BUTTON_P_3, OnBnClickedButtonP3)
	ON_BN_CLICKED(IDC_BUTTON_P_4, OnBnClickedButtonP4)
	ON_BN_CLICKED(IDC_BUTTON_P_5, OnBnClickedButtonP5)
	ON_BN_CLICKED(IDC_BUTTON_P_6, OnBnClickedButtonP6)
	ON_BN_CLICKED(IDC_BUTTON_P_7, OnBnClickedButtonP7)
	ON_BN_CLICKED(IDC_BUTTON_P_8, OnBnClickedButtonP8)
	ON_BN_CLICKED(IDC_BUTTON_P_9, OnBnClickedButtonP9)
	ON_BN_CLICKED(IDC_BUTTON_P_10, OnBnClickedButtonP10)
	ON_BN_CLICKED(IDC_BUTTON_P_11, OnBnClickedButtonP11)
	ON_BN_CLICKED(IDC_BUTTON_P_12, OnBnClickedButtonP12)
	ON_BN_CLICKED(IDC_BUTTON_P_13, OnBnClickedButtonP13)
	ON_BN_CLICKED(IDC_BUTTON_P_14, OnBnClickedButtonP14)
	ON_BN_CLICKED(IDC_BUTTON_P_15, OnBnClickedButtonP15)
	ON_BN_CLICKED(IDC_BUTTON_P_16, OnBnClickedButtonP16)
	ON_BN_CLICKED(IDC_BUTTON_P_17, OnBnClickedButtonP17)
	ON_BN_CLICKED(IDC_BUTTON_P_18, OnBnClickedButtonP18)
	ON_BN_CLICKED(IDC_BUTTON_ITEMSEARCH_M, OnBnClickedButtonItemsearchM)
	ON_BN_CLICKED(IDC_BUTTON_ITEMSEARCH_COS, OnBnClickedButtonItemsearchCos)
	ON_BN_CLICKED(IDC_BUTTON_RESET_COS_EXPIRE, OnBnClickedButtonResetCosExpire)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_DELETE, OnBnClickedBtnEditItemDelete)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_UPDATE, OnBnClickedBtnEditItemUpdate)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_DELETE_ALL, OnBnClickedBtnEditItemDeleteAll)
	ON_BN_CLICKED(IDC_BUTTON_PUTON_SAVE, OnBnClickedButtonPutonSave)
	ON_BN_CLICKED(IDC_BUTTON_PUTON_CANCEL, OnBnClickedButtonPutonCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_GENTYPE, OnCbnSelchangeComboGentype)
END_MESSAGE_MAP()


// CRanManagerCharPutOn message handlers
BOOL CRanManagerCharPutOn::OnInitDialog()
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

void CRanManagerCharPutOn::SetChar(int nChar)
{
	ReadChar (nChar);
	ReadPutOn (nChar);
}

void CRanManagerCharPutOn::ReadChar (int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT ChaNum,ChaName FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChar );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharPutOn.txt","%s--%s",strTIME.c_str(),szTemp);

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

void CRanManagerCharPutOn::ReadPutOn (int nChar)
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
	_snprintf( szTemp, 128, "SELECT ChaPutOnItems FROM  %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaNum=%u"
		,CToolCfg::GetInstance()->szGameDb,nChar );
	
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharPutOn.txt","%s--%s",strTIME.c_str(),szTemp);

	if ( sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO )
	{
		MessageBox("Error Reading Puton Items Binary","Error",MB_OK);
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

	SETPUTONITEMS_BYBUF(m_PutOnItems,ByteStream);
	ShowPutOn ();
}

void CRanManagerCharPutOn::ShowPutOn ()
{
	int nNum = 0;
	for ( int i = 0; i < SLOT_NSIZE_S_2; i++ )
	{
		char szTemp[128] = {0};
		SNATIVEID sID = SNATIVEID( m_PutOnItems[i].sNativeID );
		if( sID != NATIVEID_NULL() )
		{
			_snprintf( szTemp, 128, "%d_%d",sID.wMainID,sID.wSubID );
			nNum++;
		}
		else
		{
			_snprintf( szTemp, 128, "%s","Empty" );
		}

		switch (i)
		{
		case 0:		SetWin_Text(this,IDC_BUTTON_P_0,szTemp);
		case 1:		SetWin_Text(this,IDC_BUTTON_P_1,szTemp);
		case 2:		SetWin_Text(this,IDC_BUTTON_P_2,szTemp);
		case 3:		SetWin_Text(this,IDC_BUTTON_P_3,szTemp);
		case 4:		SetWin_Text(this,IDC_BUTTON_P_4,szTemp);
		case 5:		SetWin_Text(this,IDC_BUTTON_P_5,szTemp);
		case 6:		SetWin_Text(this,IDC_BUTTON_P_6,szTemp);
		case 7:		SetWin_Text(this,IDC_BUTTON_P_7,szTemp);
		case 8:		SetWin_Text(this,IDC_BUTTON_P_8,szTemp);
		case 9:		SetWin_Text(this,IDC_BUTTON_P_9,szTemp);
		case 10:	SetWin_Text(this,IDC_BUTTON_P_10,szTemp);
		case 11:	SetWin_Text(this,IDC_BUTTON_P_11,szTemp);
		case 12:	SetWin_Text(this,IDC_BUTTON_P_12,szTemp);
		case 13:	SetWin_Text(this,IDC_BUTTON_P_13,szTemp);
		case 14:	SetWin_Text(this,IDC_BUTTON_P_14,szTemp);
		case 15:	SetWin_Text(this,IDC_BUTTON_P_15,szTemp);
		case 16:	SetWin_Text(this,IDC_BUTTON_P_16,szTemp);
		case 17:	SetWin_Text(this,IDC_BUTTON_P_17,szTemp);
		case 18:	SetWin_Text(this,IDC_BUTTON_P_18,szTemp);
		};
	}

	SetWin_Num_int(this,IDC_EDIT_TOTAL,nNum);
}
void CRanManagerCharPutOn::OnBnClickedButtonP0()	{	SelectSlot(0);	SetPutOnItemState ( this,IDC_BUTTON_P_0 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP1()	{	SelectSlot(1);	SetPutOnItemState ( this,IDC_BUTTON_P_1 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP2()	{	SelectSlot(2);	SetPutOnItemState ( this,IDC_BUTTON_P_2 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP3()	{	SelectSlot(3);	SetPutOnItemState ( this,IDC_BUTTON_P_3 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP4()	{	SelectSlot(4);	SetPutOnItemState ( this,IDC_BUTTON_P_4 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP5()	{	SelectSlot(5);	SetPutOnItemState ( this,IDC_BUTTON_P_5 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP6()	{	SelectSlot(6);	SetPutOnItemState ( this,IDC_BUTTON_P_6 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP7()	{	SelectSlot(7);	SetPutOnItemState ( this,IDC_BUTTON_P_7 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP8()	{	SelectSlot(8);	SetPutOnItemState ( this,IDC_BUTTON_P_8 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP9()	{	SelectSlot(9);	SetPutOnItemState ( this,IDC_BUTTON_P_9 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP10()	{	SelectSlot(10);	SetPutOnItemState ( this,IDC_BUTTON_P_10 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP11()	{	SelectSlot(11);	SetPutOnItemState ( this,IDC_BUTTON_P_11 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP12()	{	SelectSlot(12);	SetPutOnItemState ( this,IDC_BUTTON_P_12 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP13()	{	SelectSlot(13);	SetPutOnItemState ( this,IDC_BUTTON_P_13 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP14()	{	SelectSlot(14);	SetPutOnItemState ( this,IDC_BUTTON_P_14 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP15()	{	SelectSlot(15);	SetPutOnItemState ( this,IDC_BUTTON_P_15 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP16()	{	SelectSlot(16);	SetPutOnItemState ( this,IDC_BUTTON_P_16 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP17()	{	SelectSlot(17);	SetPutOnItemState ( this,IDC_BUTTON_P_17 );	}
void CRanManagerCharPutOn::OnBnClickedButtonP18()	{	SelectSlot(18); SetPutOnItemState ( this,IDC_BUTTON_P_18 );	}

void CRanManagerCharPutOn::SetPutOnItemState ( CDialog *pDlg,int nID )
{
	ResetPutOnItemState (this);
	CButton *pBtn;
	switch (nID)
	{
	case IDC_BUTTON_P_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_9 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_10:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_10 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_11:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_11 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_12:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_12 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_13:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_13 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_14:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_14 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_15:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_15 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_16:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_16 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_17:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_17 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_P_18:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_18 );	pBtn->SetState(TRUE);	break;
	};
}

void CRanManagerCharPutOn::ResetPutOnItemState ( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_9 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_10 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_11 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_12 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_13 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_14 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_15 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_16 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_17 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_P_18 );	pBtn->SetState(FALSE);
}

void CRanManagerCharPutOn::SelectSlot(int nSlot)
{
	SetWin_Num_int(this,IDC_EDIT_SLOT_NUM,nSlot);
	//SetWin_Text(this,IDC_EDIT_SLOT_NAME,COMMENT::ITEM_PUTON_SLOT[nSlot].c_str() );

	SetWin_Enable(this,IDC_BTN_EDIT_ITEM_UPDATE,true);

	SNATIVEID sID = SNATIVEID( m_PutOnItems[nSlot].sNativeID );
	if( sID != NATIVEID_NULL() )
	{
		SetWin_Enable(this,IDC_BTN_EDIT_ITEM_DELETE,true);
	}
	else
	{
		SetWin_Enable(this,IDC_BTN_EDIT_ITEM_DELETE,false);
	}

	SITEM* pItem = GLItemMan::GetInstance().GetItem(m_PutOnItems[nSlot].sNativeID);
	if (pItem )
	{
		SetWin_Num_int ( this, IDC_EDIT_MID,m_PutOnItems[nSlot].sNativeID.wMainID);
		SetWin_Num_int ( this, IDC_EDIT_SID,m_PutOnItems[nSlot].sNativeID.wSubID);
		SetWin_Text ( this, IDC_EDIT_NAME,pItem->GetName());
	}
	else
	{
		SetWin_Num_int ( this, IDC_EDIT_MID,m_PutOnItems[nSlot].sNativeID.wMainID);
		SetWin_Num_int ( this, IDC_EDIT_SID,m_PutOnItems[nSlot].sNativeID.wSubID);
		SetWin_Text ( this, IDC_EDIT_NAME,"Unknown Item");
	}

	SetWin_Num_int ( this, IDC_EDIT_MID_COS,m_PutOnItems[nSlot].nidDISGUISE.wMainID);
	SetWin_Num_int ( this, IDC_EDIT_SID_COS,m_PutOnItems[nSlot].nidDISGUISE.wSubID);

	CTimeSpan cSPAN(m_PutOnItems[nSlot].tDISGUISE);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_1, (int)cSPAN.GetDays() );
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_2, (int)cSPAN.GetHours() );
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_COS_3, (int)cSPAN.GetMinutes() );

	SITEM* pCosItem = GLItemMan::GetInstance().GetItem(m_PutOnItems[nSlot].nidDISGUISE);
	if (pCosItem)	SetWin_Text ( this, IDC_EDIT_NAME_COS,pCosItem->GetName());
	else	SetWin_Text ( this, IDC_EDIT_NAME_COS,"Unknown Item");

	SetWin_Num_int ( this, IDC_EDIT_TURN_NUM,m_PutOnItems[nSlot].wTurnNum );
	m_cGenType.SetCurSel((int)m_PutOnItems[nSlot].cGenType);

	TCHAR Gen[100];
	_snprintf( Gen, 100, "%I64d",m_PutOnItems[nSlot].lnGenNum );
	SetWin_Text ( this, IDC_EDIT_GEN_NUM,Gen);

	SetWin_Num_int ( this, IDC_EDIT_CHID,m_PutOnItems[nSlot].cChnID );
	SetWin_Num_int ( this, IDC_EDIT_FLDID,m_PutOnItems[nSlot].cFieldID );

	SetWin_Num_int ( this, IDC_EDIT_DAMAGE,m_PutOnItems[nSlot].cDAMAGE);
	SetWin_Num_int ( this, IDC_EDIT_DEFENSE,m_PutOnItems[nSlot].cDEFENSE);

	SetWin_Num_int ( this, IDC_EDIT_FIRE,m_PutOnItems[nSlot].cRESIST_FIRE);
	SetWin_Num_int ( this, IDC_EDIT_ICE,m_PutOnItems[nSlot].cRESIST_ICE);
	SetWin_Num_int ( this, IDC_EDIT_ELE,m_PutOnItems[nSlot].cRESIST_ELEC);
	SetWin_Num_int ( this, IDC_EDIT_POI,m_PutOnItems[nSlot].cRESIST_POISON);
	SetWin_Num_int ( this, IDC_EDIT_SPI,m_PutOnItems[nSlot].cRESIST_SPIRIT);

	m_cRandomOp1.SetCurSel((int)m_PutOnItems[nSlot].cOptTYPE1);
	m_cRandomOp2.SetCurSel((int)m_PutOnItems[nSlot].cOptTYPE2);
	m_cRandomOp3.SetCurSel((int)m_PutOnItems[nSlot].cOptTYPE3);
	m_cRandomOp4.SetCurSel((int)m_PutOnItems[nSlot].cOptTYPE4);

	SetWin_Num_int ( this, IDC_EDIT_OPTION_VAL1,(int)m_PutOnItems[nSlot].nOptVALUE1);
	SetWin_Num_int ( this, IDC_EDIT_OPTION_VAL2,(int)m_PutOnItems[nSlot].nOptVALUE2);
	SetWin_Num_int ( this, IDC_EDIT_OPTION_VAL3,(int)m_PutOnItems[nSlot].nOptVALUE3);
	SetWin_Num_int ( this, IDC_EDIT_OPTION_VAL4,(int)m_PutOnItems[nSlot].nOptVALUE4);

	SetWin_Num_int ( this, IDC_EDIT_PET_ID,(int)m_PutOnItems[nSlot].dwPetID);
	SetWin_Num_int ( this, IDC_EDIT_VEHICLE_ID,(int)m_PutOnItems[nSlot].dwVehicleID);
	//SetWin_Num_int ( this, IDC_EDIT_OWNER_ID,(int)m_PutOnItems[nSlot].dwOwnerID);
	//SetWin_Num_int ( this, IDC_EDIT_ITEMCOLOR,(int)m_PutOnItems[nSlot].wColor);
}
void CRanManagerCharPutOn::OnBnClickedButtonItemsearchM()
{
	//TODO:
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

void CRanManagerCharPutOn::OnBnClickedButtonItemsearchCos()
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

void CRanManagerCharPutOn::OnBnClickedButtonResetCosExpire()
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

void CRanManagerCharPutOn::OnBnClickedBtnEditItemDelete()
{
	if ( MessageBox ( "Do You Want to Delete this Item?, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		int nSlot = GetWin_Num_int(this,IDC_EDIT_SLOT_NUM );
		SITEMCUSTOM		pDummy;
		m_PutOnItems[nSlot] = pDummy;
		ShowPutOn ();
		SelectSlot(nSlot);
	}
}

void CRanManagerCharPutOn::OnBnClickedBtnEditItemUpdate()
{
	if ( MessageBox ( "Update Changes to This Item?", "Question", MB_YESNO ) == IDYES )
	{
		int nSlot = GetWin_Num_int(this,IDC_EDIT_SLOT_NUM);

		m_PutOnItems[nSlot].sNativeID.wMainID = GetWin_Num_int(this,IDC_EDIT_MID);
		m_PutOnItems[nSlot].sNativeID.wSubID = GetWin_Num_int(this,IDC_EDIT_SID);
		m_PutOnItems[nSlot].nidDISGUISE.wMainID = GetWin_Num_int(this,IDC_EDIT_MID_COS);
		m_PutOnItems[nSlot].nidDISGUISE.wSubID = GetWin_Num_int(this,IDC_EDIT_SID_COS);
		CTime cTIME_CUR;
		m_PutOnItems[nSlot].tBORNTIME = cTIME_CUR.GetTime();
		CTimeSpan cSPAN(
			GetWin_Num_int(this,IDC_EDIT_LOCKER_COS_1),
			GetWin_Num_int(this,IDC_EDIT_LOCKER_COS_2),
			GetWin_Num_int(this,IDC_EDIT_LOCKER_COS_3),
			0);
		m_PutOnItems[nSlot].tDISGUISE = cSPAN.GetTimeSpan();
		m_PutOnItems[nSlot].lnGenNum = _strtoi64(GetWin_Text(this,IDC_EDIT_GEN_NUM ),NULL,10);
		m_PutOnItems[nSlot].wTurnNum = (WORD)GetWin_Num_int(this,IDC_EDIT_TURN_NUM);
		m_PutOnItems[nSlot].cGenType = (BYTE)m_cGenType.GetCurSel();
		if ( m_PutOnItems[nSlot].cGenType == EMGEN_GMEDIT || m_PutOnItems[nSlot].cGenType == EMGEN_GMEDIT2 )	SetWin_Num_int(this, IDC_EDIT_FLDID ,255 );
		m_PutOnItems[nSlot].cChnID = (BYTE)GetWin_Num_int(this,IDC_EDIT_CHID);
		m_PutOnItems[nSlot].cFieldID = (BYTE)GetWin_Num_int(this,IDC_EDIT_FLDID);
		m_PutOnItems[nSlot].cDAMAGE = (BYTE)GetWin_Num_int(this,IDC_EDIT_DAMAGE);
		m_PutOnItems[nSlot].cDEFENSE = (BYTE)GetWin_Num_int(this,IDC_EDIT_DEFENSE);
		m_PutOnItems[nSlot].cRESIST_FIRE = (BYTE)GetWin_Num_int(this,IDC_EDIT_FIRE);
		m_PutOnItems[nSlot].cRESIST_ICE = (BYTE)GetWin_Num_int(this,IDC_EDIT_ICE);
		m_PutOnItems[nSlot].cRESIST_ELEC = (BYTE)GetWin_Num_int(this,IDC_EDIT_ELE);
		m_PutOnItems[nSlot].cRESIST_POISON = (BYTE)GetWin_Num_int(this,IDC_EDIT_POI);
		m_PutOnItems[nSlot].cRESIST_SPIRIT = (BYTE)GetWin_Num_int(this,IDC_EDIT_SPI);
		m_PutOnItems[nSlot].cOptTYPE1 = (BYTE)m_cRandomOp1.GetCurSel();
		m_PutOnItems[nSlot].cOptTYPE2 = (BYTE)m_cRandomOp2.GetCurSel();
		m_PutOnItems[nSlot].cOptTYPE3 = (BYTE)m_cRandomOp3.GetCurSel();
		m_PutOnItems[nSlot].cOptTYPE4 = (BYTE)m_cRandomOp4.GetCurSel();
		m_PutOnItems[nSlot].nOptVALUE1 = (short)GetWin_Num_int(this,IDC_EDIT_OPTION_VAL1);
		m_PutOnItems[nSlot].nOptVALUE2 = (short)GetWin_Num_int(this,IDC_EDIT_OPTION_VAL2);
		m_PutOnItems[nSlot].nOptVALUE3 = (short)GetWin_Num_int(this,IDC_EDIT_OPTION_VAL3);
		m_PutOnItems[nSlot].nOptVALUE4 = (short)GetWin_Num_int(this,IDC_EDIT_OPTION_VAL4);
		m_PutOnItems[nSlot].dwPetID = GetWin_Num_int(this,IDC_EDIT_PET_ID);
		m_PutOnItems[nSlot].dwVehicleID = GetWin_Num_int(this,IDC_EDIT_VEHICLE_ID);
		//m_PutOnItems[nSlot].dwOwnerID = GetWin_Num_int(this,IDC_EDIT_OWNER_ID);
		//m_PutOnItems[nSlot].wColor = GetWin_Num_int(this,IDC_EDIT_ITEMCOLOR);
		ShowPutOn ();
		SelectSlot(nSlot);
	}
}

void CRanManagerCharPutOn::OnBnClickedBtnEditItemDeleteAll()
{
	if ( MessageBox ( "Do You Want To Delete All Items?, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		for ( int i = 0; i < SLOT_NSIZE_S_2; i++ )
		{
			SITEMCUSTOM		pDummy;
			m_PutOnItems[i] = pDummy;
			ShowPutOn ();
			SelectSlot(i);
		}
	}
}

void CRanManagerCharPutOn::OnBnClickedButtonPutonSave()
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
	ByteStream << SITEMCUSTOM::VERSION;
	ByteStream << (DWORD)sizeof(SITEMCUSTOM);
	DWORD dwSize2 = (DWORD) SLOT_TSIZE;
	ByteStream << dwSize2;
	ByteStream.WriteBuffer ( (LPBYTE)&m_PutOnItems[0], (DWORD)sizeof(SITEMCUSTOM)*dwSize2 );
	ByteStream.GetBuffer(pBuffer, dwSize);
	if (pBuffer != NULL)
	{
		TCHAR szTemp[128] = {0};
		_snprintf( szTemp, 128, "UPDATE ChaInfo SET ChaPutOnItems=? WHERE (ChaNum=%u)", (DWORD)nChaNum );

		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("CharPutOn.txt","%s--%s",strTIME.c_str(),szTemp);

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
			MessageBox("Error Saving CharPutOnItems Binary!","error",MB_OK);
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
	MessageBox("Done Saving CharPutOnItems!","Info",MB_OK);

	pBuffer = NULL;
	ShowPutOn();
}

void CRanManagerCharPutOn::OnBnClickedButtonPutonCancel()
{
	m_pToolTab->ActivePage(CHARPAGE_MAIN,0);
}

void CRanManagerCharPutOn::OnCbnSelchangeComboGentype()
{
}
