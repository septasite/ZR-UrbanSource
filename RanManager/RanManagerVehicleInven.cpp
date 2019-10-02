// RanManagerVehicleInven.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerVehicleInven.h"
#include "RanManagerVehicleTab.h"
#include "RanManagerComments.h"

#include "EtcFunction.h"
#include "COdbc.h"
#include "CCfg.h"
#include "LogScript.h"
#include "CharSearch.h"
#include "s_NetGlobal.h"
#include "ItemSearch.h"
#include "../NetServerLib/s_DbBase.h"
#include "../EngineLib/Common/ByteStream.h"
#include ".\ranmanagervehicleinven.h"


// CRanManagerVehicleInven dialog

IMPLEMENT_DYNAMIC(CRanManagerVehicleInven, CPropertyPage)
CRanManagerVehicleInven::CRanManagerVehicleInven(LOGFONT logfont)
	: CPropertyPage(CRanManagerVehicleInven::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerVehicleInven::~CRanManagerVehicleInven()
{
}

void CRanManagerVehicleInven::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GENTYPE, m_cGenType );
	DDX_Control(pDX, IDC_COMBO_OPTION1, m_cRandomOp1 );
	DDX_Control(pDX, IDC_COMBO_OPTION2, m_cRandomOp2 );
	DDX_Control(pDX, IDC_COMBO_OPTION3, m_cRandomOp3 );
	DDX_Control(pDX, IDC_COMBO_OPTION4, m_cRandomOp4 );
}


BEGIN_MESSAGE_MAP(CRanManagerVehicleInven, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_VP_1, OnBnClickedButtonVp1)
	ON_BN_CLICKED(IDC_BUTTON_VP_2, OnBnClickedButtonVp2)
	ON_BN_CLICKED(IDC_BUTTON_VP_3, OnBnClickedButtonVp3)
	ON_BN_CLICKED(IDC_BUTTON_VP_4, OnBnClickedButtonVp4)
	ON_BN_CLICKED(IDC_BUTTON_VP_5, OnBnClickedButtonVp5)
	ON_BN_CLICKED(IDC_BUTTON_VP_6, OnBnClickedButtonVp6)
	ON_BN_CLICKED(IDC_BUTTON_VP_7, OnBnClickedButtonVp7)
	ON_BN_CLICKED(IDC_BUTTON_ITEMSEARCH_M, OnBnClickedButtonItemsearchM)
	ON_BN_CLICKED(IDC_BUTTON_ITEMSEARCH_COS, OnBnClickedButtonItemsearchCos)
	ON_BN_CLICKED(IDC_BUTTON_RESET_COS_EXPIRE, OnBnClickedButtonResetCosExpire)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_DELETE, OnBnClickedBtnEditItemDelete)
	ON_BN_CLICKED(IDC_BTN_EDIT_ITEM_UPDATE, OnBnClickedBtnEditItemUpdate)
	ON_BN_CLICKED(IDC_BTN_EDIT_SAVE, OnBnClickedBtnEditSave)
	ON_BN_CLICKED(IDC_BTN_EDIT_CANCEL, OnBnClickedBtnEditCancel)
END_MESSAGE_MAP()


// CRanManagerVehicleInven message handlers
BOOL CRanManagerVehicleInven::OnInitDialog()
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

void	CRanManagerVehicleInven::SetVehicle(int nVehicleNum)
{
	GetVehicle(nVehicleNum);
	GetVehicleInven(nVehicleNum);
}

void	CRanManagerVehicleInven::GetVehicle(int nVehicleNum)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT VehicleNum,VehicleName FROM %s.dbo.VehicleInfo WHERE VehicleNum=%d",CToolCfg::GetInstance()->szGameDb,nVehicleNum );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("VehicleInven.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	return;

	SQLINTEGER nVehicleNum1 = 0, cbVehicleNum=SQL_NTS;
	SQLCHAR    szVehicleName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbVehicleName = SQL_NTS; 
	
	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{		
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nVehicleNum1,       0, &cbVehicleNum);
            ::SQLGetData(hStmt, 2, SQL_C_CHAR, szVehicleName   ,  CHR_ID_LENGTH+1, &cbVehicleName); 
            
			SetWin_Num_int(this,IDC_EDIT_V_NUM,nVehicleNum1);
			SetWin_Text(this,IDC_EDIT_V_NAME,(const char*) szVehicleName);
		}
		else
		{
			break;
		}
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

void	CRanManagerVehicleInven::GetVehicleInven(int nVehicleNum)
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
	_snprintf( szTemp, 128, "SELECT VehiclePutOnItems FROM  %s.dbo.VehicleInfo WITH (NOLOCK) WHERE VehicleNum=%u"
		,CToolCfg::GetInstance()->szGameDb,nVehicleNum );
	
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("VehicleInven.txt","%s--%s",strTIME.c_str(),szTemp);

	if ( sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO )
	{
		MessageBox("Error Reading VehiclePutOn Binary","Error",MB_OK);
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

	SETPUTONITEMS_BYBUF( m_PutOnItems, ByteStream );
	ShowPutOn ();
}

void CRanManagerVehicleInven::ShowPutOn ()
{
	int nNum = 0;
	for ( int i = 0; i < ACCE_TYPE_SIZE; i++ )
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
		case 0:		SetWin_Text(this,IDC_BUTTON_VP_1,szTemp);
		case 1:		SetWin_Text(this,IDC_BUTTON_VP_2,szTemp);
		case 2:		SetWin_Text(this,IDC_BUTTON_VP_3,szTemp);
		case 3:		SetWin_Text(this,IDC_BUTTON_VP_4,szTemp);
		case 4:		SetWin_Text(this,IDC_BUTTON_VP_5,szTemp);
		case 5:		SetWin_Text(this,IDC_BUTTON_VP_6,szTemp);
		case 6:		SetWin_Text(this,IDC_BUTTON_VP_7,szTemp);
		};
	}
}


void CRanManagerVehicleInven::OnBnClickedButtonVp1(){	ShowItem(0);	SetPutOnItemState ( this,IDC_BUTTON_VP_1 );	}
void CRanManagerVehicleInven::OnBnClickedButtonVp2(){	ShowItem(1);	SetPutOnItemState ( this,IDC_BUTTON_VP_2 );	}
void CRanManagerVehicleInven::OnBnClickedButtonVp3(){	ShowItem(2);	SetPutOnItemState ( this,IDC_BUTTON_VP_3 );	}
void CRanManagerVehicleInven::OnBnClickedButtonVp4(){	ShowItem(3);	SetPutOnItemState ( this,IDC_BUTTON_VP_4 );	}
void CRanManagerVehicleInven::OnBnClickedButtonVp5(){	ShowItem(4);	SetPutOnItemState ( this,IDC_BUTTON_VP_5 );	}
void CRanManagerVehicleInven::OnBnClickedButtonVp6(){	ShowItem(5);	SetPutOnItemState ( this,IDC_BUTTON_VP_6 );	}
void CRanManagerVehicleInven::OnBnClickedButtonVp7(){	ShowItem(6);	SetPutOnItemState ( this,IDC_BUTTON_VP_7 );	}


void CRanManagerVehicleInven::SetPutOnItemState ( CDialog *pDlg,int nID )
{
	ResetPutOnItemState (this);
	CButton *pBtn;
	switch (nID)
	{
	case IDC_BUTTON_VP_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_VP_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_VP_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_VP_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_VP_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_VP_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_VP_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_7 );	pBtn->SetState(TRUE);	break;
	};
}

void CRanManagerVehicleInven::ResetPutOnItemState ( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_VP_7 );	pBtn->SetState(FALSE);
}

void CRanManagerVehicleInven::ShowItem(int nSlot)
{
	SetWin_Num_int(this,IDC_EDIT_SLOT_NUM,nSlot);
	//SetWin_Text(this,IDC_EDIT_SLOT_NAME,COMMENT::ITEM_VEHICLE_SLOT[nSlot].c_str() );

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
void CRanManagerVehicleInven::OnBnClickedButtonItemsearchM()
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

void CRanManagerVehicleInven::OnBnClickedButtonItemsearchCos()
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

void CRanManagerVehicleInven::OnBnClickedButtonResetCosExpire()
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

void CRanManagerVehicleInven::OnBnClickedBtnEditItemDelete()
{
	if ( MessageBox ( "Do You Want to Delete this Item?, Continue?", "Question", MB_YESNO ) == IDYES )
	{
		int nSlot = GetWin_Num_int(this,IDC_EDIT_SLOT_NUM );
		SITEMCUSTOM		pDummy;
		m_PutOnItems[nSlot] = pDummy;
		ShowPutOn ();
		ShowItem(nSlot);
	}
}

void CRanManagerVehicleInven::OnBnClickedBtnEditItemUpdate()
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
		ShowItem(nSlot);
	}
}

void CRanManagerVehicleInven::OnBnClickedBtnEditSave()
{
	CByteStream ByteStream;
	LPBYTE pBuffer = NULL;
	DWORD dwSize = 0;
	TCHAR szTemp[128] = {0};
	int nVehicleNum = GetWin_Num_int(this,IDC_EDIT_V_NUM);

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
	DWORD dwSize2 = (DWORD) ACCE_TYPE_SIZE;
	ByteStream << dwSize2;
	ByteStream.WriteBuffer ( (LPBYTE)&m_PutOnItems[0], (DWORD)sizeof(SITEMCUSTOM)*dwSize2 );
	ByteStream.GetBuffer(pBuffer, dwSize);

	if (pBuffer != NULL)
	{
		TCHAR szTemp[128] = {0};
		_snprintf( szTemp, 128, "UPDATE VehicleInfo SET VehiclePutOnItems=? WHERE (VehicleNum=%u)", (DWORD)nVehicleNum );

		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("VehicleInven.txt","%s--%s",strTIME.c_str(),szTemp);

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
			MessageBox("Error Saving VehiclePutOnItems Binary!","error",MB_OK);
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
	MessageBox("Done Saving VehiclePutOnItems!","Info",MB_OK);

	pBuffer = NULL;
	ShowPutOn();
}

void CRanManagerVehicleInven::OnBnClickedBtnEditCancel()
{
	m_pToolTab->ActivePage(VEHICLEPAGE_MAIN,0);
}
