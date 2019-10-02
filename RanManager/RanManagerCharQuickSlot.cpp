// RanManagerCharQuickSlot.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerCharQuickSlot.h"
#include ".\ranmanagercharquickslot.h"

#include "RanManagerCharTab.h"
#include "COdbc.h"
#include "CCfg.h"
#include "s_NetGlobal.h"
#include "Calendar.h"
#include "LogScript.h"
#include "ItemSearch.h"
#include "SkillSearch.h"
#include "EtcFunction.h"
#include "RanManagerComments.h"
#include "../NetServerLib/s_DbBase.h"
#include "../EngineLib/Common/ByteStream.h"
#include "GLDefine.h"


// CRanManagerCharQuickSlot dialog

IMPLEMENT_DYNAMIC(CRanManagerCharQuickSlot, CPropertyPage)
CRanManagerCharQuickSlot::CRanManagerCharQuickSlot(LOGFONT logfont)
	: CPropertyPage(CRanManagerCharQuickSlot::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	nSelectedSlot = 65535;
}

CRanManagerCharQuickSlot::~CRanManagerCharQuickSlot()
{
}

void CRanManagerCharQuickSlot::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ACT, m_cActType );
}


BEGIN_MESSAGE_MAP(CRanManagerCharQuickSlot, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_QUICKSLOT_SAVE, OnBnClickedButtonQuickslotSave)
	ON_BN_CLICKED(IDC_BUTTON_QUICKSLOT_CANCEL, OnBnClickedButtonQuickslotCancel)
	ON_BN_CLICKED(IDC_BUTTON_QUICK_0, OnBnClickedButtonQuick0)
	ON_BN_CLICKED(IDC_BUTTON_QUICK_1, OnBnClickedButtonQuick1)
	ON_BN_CLICKED(IDC_BUTTON_QUICK_2, OnBnClickedButtonQuick2)
	ON_BN_CLICKED(IDC_BUTTON_QUICK_3, OnBnClickedButtonQuick3)
	ON_BN_CLICKED(IDC_BUTTON_QUICK_4, OnBnClickedButtonQuick4)
	ON_BN_CLICKED(IDC_BUTTON_QUICK_5, OnBnClickedButtonQuick5)
	ON_BN_CLICKED(IDC_BUTTON_Q_CHANGE, OnBnClickedButtonQChange)
	ON_BN_CLICKED(IDC_BUTTON_Q_DELETE, OnBnClickedButtonQDelete)
	ON_BN_CLICKED(IDC_BUTTON_Q_SAVE, OnBnClickedButtonQSave)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL_Q, OnBnClickedButtonDeleteAllQ)
END_MESSAGE_MAP()


// CRanManagerCharQuickSlot message handlers
BOOL CRanManagerCharQuickSlot::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	for ( int i = 0; i < SLOTACT_SIZE; ++i )
	{
		m_cActType.InsertString( i, RMComments::m_SlotAct[i].c_str() );
	}
	m_cActType.SetCurSel(0);

	SetWin_Enable(this,IDC_BUTTON_Q_CHANGE,FALSE);
	SetWin_Enable(this,IDC_BUTTON_Q_SAVE,FALSE);
	SetWin_Enable(this,IDC_BUTTON_Q_DELETE,FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerCharQuickSlot::LoadChar (int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT ChaNum,ChaName FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChar );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharQuickSlot.txt","%s--%s",strTIME.c_str(),szTemp);

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

void CRanManagerCharQuickSlot::SetChar(int nChar)
{
	LoadChar (nChar);
	LoadQuickSlot(nChar);
}

void CRanManagerCharQuickSlot::LoadQuickSlot(int nChar)
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
	_snprintf( szTemp, 128, "SELECT ChaActionSlot FROM  %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaNum=%u"
		,CToolCfg::GetInstance()->szGameDb,nChar );
	
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharQuickSlot.txt","%s--%s",strTIME.c_str(),szTemp);

	if ( sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO )
	{
		MessageBox("Error Reading Action Slot Binary","Error",MB_OK);
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

	DWORD dwVersion, dwSize, dwNum;

	ByteStream >> dwVersion;
	ByteStream >> dwSize;
	ByteStream >> dwNum;

	GASSERT ( (dwSize==sizeof(SACTION_SLOT)) && (SACTION_SLOT::VERSION==dwVersion) );

	SACTION_SLOT sACTION_SLOT;
	for ( DWORD i=0; i<dwNum; i++ )
	{
		if ( i>=EMACTIONQUICK_SIZE )		break;

		ByteStream.ReadBuffer ( (LPBYTE)&sACTION_SLOT, sizeof(SACTION_SLOT) );

		m_sACTIONQUICK[i] = sACTION_SLOT;
	}

	ShowQuickSlot();
}

void CRanManagerCharQuickSlot::ShowQuickSlot()
{
	int nNum = 0;
	TCHAR szTemp[128] = {0};
	for (int i = 0; i < EMACTIONQUICK_SIZE; i++ )
	{
		 SNATIVEID	sID = m_sACTIONQUICK[i].sNID;
		 if ( sID.wMainID !=65535 && sID.wSubID !=65535 )	_snprintf( szTemp, 128, "%d_%d",sID.wMainID,sID.wSubID);
		 else	_snprintf( szTemp, 128, "%s","Empty");

		switch (nNum)
		{
		case	0:	SetWin_Text ( this, IDC_BUTTON_QUICK_0,(const TCHAR*)szTemp );
		case	1:	SetWin_Text ( this, IDC_BUTTON_QUICK_1,(const TCHAR*)szTemp );
		case	2:	SetWin_Text ( this, IDC_BUTTON_QUICK_2,(const TCHAR*)szTemp );
		case	3:	SetWin_Text ( this, IDC_BUTTON_QUICK_3,(const TCHAR*)szTemp );
		case	4:	SetWin_Text ( this, IDC_BUTTON_QUICK_4,(const TCHAR*)szTemp );
		case	5:	SetWin_Text ( this, IDC_BUTTON_QUICK_5,(const TCHAR*)szTemp );
		};
		nNum++;
	}
}

void CRanManagerCharQuickSlot::OnBnClickedButtonQuickslotSave()
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
	ByteStream << SACTION_SLOT::VERSION;
	ByteStream << (DWORD)sizeof(SACTION_SLOT);
	DWORD dwSize2 = (DWORD) EMACTIONQUICK_SIZE;
	ByteStream << dwSize2;
	ByteStream.WriteBuffer ( (LPBYTE)m_sACTIONQUICK, (DWORD)sizeof(SACTION_SLOT)*dwSize2 );
	ByteStream.GetBuffer(pBuffer, dwSize);

	//write image
	if (pBuffer != NULL)
	{
		TCHAR szTemp[128] = {0};
		_snprintf( szTemp, 128, "UPDATE ChaInfo SET ChaActionSlot=? WHERE (ChaNum=%u)", (DWORD)nChaNum );

		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("CharQuickSlot.txt","%s--%s",strTIME.c_str(),szTemp);

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
			MessageBox("Error Saving CharQuickSlots Binary!","error",MB_OK);
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
	MessageBox("Done Saving CharQuickSlots!","Info",MB_OK);

	pBuffer = NULL;
	ShowQuickSlot();
}

void CRanManagerCharQuickSlot::OnBnClickedButtonQuickslotCancel()
{
	m_pToolTab->ActivePage(CHARPAGE_MAIN,0);
}

void CRanManagerCharQuickSlot::OnBnClickedButtonQuick0(){	SetSlotState (this,IDC_BUTTON_QUICK_0 );	LoadSlot(0);	}
void CRanManagerCharQuickSlot::OnBnClickedButtonQuick1(){	SetSlotState (this,IDC_BUTTON_QUICK_1 );	LoadSlot(1);	}
void CRanManagerCharQuickSlot::OnBnClickedButtonQuick2(){	SetSlotState (this,IDC_BUTTON_QUICK_2 );	LoadSlot(2);	}
void CRanManagerCharQuickSlot::OnBnClickedButtonQuick3(){	SetSlotState (this,IDC_BUTTON_QUICK_3 );	LoadSlot(3);	}
void CRanManagerCharQuickSlot::OnBnClickedButtonQuick4(){	SetSlotState (this,IDC_BUTTON_QUICK_4 );	LoadSlot(4);	}
void CRanManagerCharQuickSlot::OnBnClickedButtonQuick5(){	SetSlotState (this,IDC_BUTTON_QUICK_5 );	LoadSlot(5);	}

void CRanManagerCharQuickSlot::SetSlotState ( CDialog *pDlg,int nID )
{
	ResetSlotState (this);
	CButton *pBtn;
	switch (nID)
	{
	case IDC_BUTTON_QUICK_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_QUICK_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_QUICK_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_QUICK_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_QUICK_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_QUICK_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_QUICK_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_QUICK_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_QUICK_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_QUICK_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_QUICK_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_QUICK_5 );	pBtn->SetState(TRUE);	break;
	};
}

void CRanManagerCharQuickSlot::ResetSlotState ( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_QUICK_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_QUICK_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_QUICK_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_QUICK_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_QUICK_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_QUICK_5 );	pBtn->SetState(FALSE);
}

void CRanManagerCharQuickSlot::LoadSlot(int nSlot)
{
	SetWin_Text(this,IDC_EDIT_ACTIVESLOT,RMComments::m_QuickSlots[nSlot].c_str() );

	SNATIVEID	sID = m_sACTIONQUICK[nSlot].sNID;
	SetWin_Num_int(this,IDC_EDIT_S_MID,sID.wMainID );
	SetWin_Num_int(this,IDC_EDIT_S_SID,sID.wSubID );
	SITEM* pItem = GLItemMan::GetInstance().GetItem(sID);
	if (pItem)
	{
		SetWin_Text(this,IDC_EDIT_S_NAME,pItem->GetName() );
	}
	else
	{
		SetWin_Text(this,IDC_EDIT_S_NAME,"Unknown Item" );
	}
	m_cActType.SetCurSel(m_sACTIONQUICK[nSlot].wACT);
	nSelectedSlot = nSlot;

	SetWin_Enable(this,IDC_BUTTON_Q_CHANGE,TRUE);
	SetWin_Enable(this,IDC_BUTTON_Q_SAVE,TRUE);
	SetWin_Enable(this,IDC_BUTTON_Q_DELETE,TRUE);
}

void CRanManagerCharQuickSlot::OnBnClickedButtonQChange()
{
	CItemSearch sItemSearch;
	sItemSearch.SetMultiple(false);
	if ( IDOK == sItemSearch.DoModal () )
	{
		SITEM*	pItemCheck = GLItemMan::GetInstance().GetItem(sItemSearch.sSelectedItem);
		if ( pItemCheck )
		{
			SetWin_Num_int ( this, IDC_EDIT_S_MID,sItemSearch.sSelectedItem.wMainID);
			SetWin_Num_int ( this, IDC_EDIT_S_SID,sItemSearch.sSelectedItem.wSubID);
			SetWin_Text( this,IDC_EDIT_S_NAME,pItemCheck->GetName() );
		}
	}
}

void CRanManagerCharQuickSlot::OnBnClickedButtonQDelete()
{
	m_sACTIONQUICK[nSelectedSlot].RESET();
	LoadSlot(nSelectedSlot);
	ShowQuickSlot();
}

void CRanManagerCharQuickSlot::OnBnClickedButtonQSave()
{
	SNATIVEID	sID;
	sID.wMainID = GetWin_Num_int(this,IDC_EDIT_S_MID );
	sID.wSubID = GetWin_Num_int(this,IDC_EDIT_S_SID );
	m_sACTIONQUICK[nSelectedSlot].sNID = sID;
	m_sACTIONQUICK[nSelectedSlot].wACT = m_cActType.GetCurSel();
	LoadSlot(nSelectedSlot);
	ShowQuickSlot();
}

void CRanManagerCharQuickSlot::OnBnClickedButtonDeleteAllQ()
{
	for (int i = 0; i < EMACTIONQUICK_SIZE; i++ )
	{
		m_sACTIONQUICK[i].RESET();
	}
	LoadSlot(nSelectedSlot);
	ShowQuickSlot();
}
