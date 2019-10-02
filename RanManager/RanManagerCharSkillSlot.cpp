// RanManagerCharSkillSlot.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerCharSkillSlot.h"
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
#include ".\ranmanagercharskillslot.h"
// CRanManagerCharSkillSlot dialog

IMPLEMENT_DYNAMIC(CRanManagerCharSkillSlot, CPropertyPage)
CRanManagerCharSkillSlot::CRanManagerCharSkillSlot(LOGFONT logfont)
	: CPropertyPage(CRanManagerCharSkillSlot::IDD)
	,m_pFont(NULL)
	,m_wSKILLQUICK_ACT(0)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);

	for ( int i=0; i<EMSKILLQUICK_SIZE; ++i )	m_sSKILLQUICK[i] = NATIVEID_NULL();
	nActiveSlot=0;
}

CRanManagerCharSkillSlot::~CRanManagerCharSkillSlot()
{
}

void CRanManagerCharSkillSlot::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SKILL_ACTIVE, m_cActiveSkill );
}


BEGIN_MESSAGE_MAP(CRanManagerCharSkillSlot, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SKILLSLOT_SAVE, OnBnClickedButtonSkillslotSave)
	ON_BN_CLICKED(IDC_BUTTON_SKILLSLOTCANCEL, OnBnClickedButtonSkillslotcancel)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_1_0, OnBnClickedButtonSkill10)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_1_1, OnBnClickedButtonSkill11)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_1_2, OnBnClickedButtonSkill12)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_1_3, OnBnClickedButtonSkill13)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_1_4, OnBnClickedButtonSkill14)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_1_5, OnBnClickedButtonSkill15)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_1_6, OnBnClickedButtonSkill16)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_1_7, OnBnClickedButtonSkill17)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_1_8, OnBnClickedButtonSkill18)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_1_9, OnBnClickedButtonSkill19)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_2_0, OnBnClickedButtonSkill20)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_2_1, OnBnClickedButtonSkill21)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_2_2, OnBnClickedButtonSkill22)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_2_3, OnBnClickedButtonSkill23)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_2_4, OnBnClickedButtonSkill24)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_2_5, OnBnClickedButtonSkill25)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_2_6, OnBnClickedButtonSkill26)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_2_7, OnBnClickedButtonSkill27)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_2_8, OnBnClickedButtonSkill28)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_2_9, OnBnClickedButtonSkill29)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_3_0, OnBnClickedButtonSkill30)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_3_1, OnBnClickedButtonSkill31)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_3_2, OnBnClickedButtonSkill32)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_3_3, OnBnClickedButtonSkill33)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_3_4, OnBnClickedButtonSkill34)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_3_5, OnBnClickedButtonSkill35)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_3_6, OnBnClickedButtonSkill36)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_3_7, OnBnClickedButtonSkill37)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_3_8, OnBnClickedButtonSkill38)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_3_9, OnBnClickedButtonSkill39)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_4_0, OnBnClickedButtonSkill40)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_4_1, OnBnClickedButtonSkill41)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_4_2, OnBnClickedButtonSkill42)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_4_3, OnBnClickedButtonSkill43)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_4_4, OnBnClickedButtonSkill44)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_4_5, OnBnClickedButtonSkill45)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_4_6, OnBnClickedButtonSkill46)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_4_7, OnBnClickedButtonSkill47)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_4_8, OnBnClickedButtonSkill48)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_4_9, OnBnClickedButtonSkill49)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_SAVE, OnBnClickedButtonSkillSave)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_DELETE, OnBnClickedButtonSkillDelete)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_CHANGE, OnBnClickedButtonSkillChange)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_SLOT_ALL, OnBnClickedButtonDeleteSlotAll)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_SLOT_F1, OnBnClickedButtonDeleteSlotF1)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_SLOT_F2, OnBnClickedButtonDeleteSlotF2)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_SLOT_F3, OnBnClickedButtonDeleteSlotF3)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_SLOT_F4, OnBnClickedButtonDeleteSlotF4)
END_MESSAGE_MAP()


// CRanManagerCharSkillSlot message handlers
BOOL CRanManagerCharSkillSlot::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	SetWin_Enable(this,IDC_BUTTON_SKILL_CHANGE,FALSE);
	SetWin_Enable(this,IDC_BUTTON_SKILL_SAVE,FALSE);
	SetWin_Enable(this,IDC_BUTTON_SKILL_DELETE,FALSE);

	for ( int i = 0; i < SKILL_SLOT_SIZE; ++i )
	{
		m_cActiveSkill.InsertString( i, RMComments::m_SkillSlots[i].c_str() );
	}
	m_cActiveSkill.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerCharSkillSlot::SetChar(int nChar)
{
	ReadChar (nChar);
	ReadSkillSlot (nChar);
}

void CRanManagerCharSkillSlot::ReadChar (int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT ChaNum,ChaName FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChar );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharSkillSlot.txt","%s--%s",strTIME.c_str(),szTemp);

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

void CRanManagerCharSkillSlot::ReadSkillSlot (int nChar)
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
	_snprintf( szTemp, 128, "SELECT ChaSkillSlot FROM  %s.dbo.ChaInfo WITH (NOLOCK) WHERE ChaNum=%u"
		,CToolCfg::GetInstance()->szGameDb,nChar );
	
	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*)szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharSkillSlot.txt","%s--%s",strTIME.c_str(),szTemp);

	if ( sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO )
	{
		MessageBox("Error Reading Skill Slot Binary","Error",MB_OK);
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
	switch ( dwVersion )
	{
	case 0x0100:
		{
			ByteStream >> dwSize;
			ByteStream >> dwNum;

			SNATIVEID sSKILL_ID;
			for ( DWORD i=0; i<dwNum; i++ )
			{
				if ( i>=EMSKILLQUICK_SIZE )		break;

				GASSERT ( dwSize==sizeof(SNATIVEID) );
				ByteStream.ReadBuffer ( (LPBYTE)&sSKILL_ID, sizeof(SNATIVEID) );

				m_sSKILLQUICK[i] = sSKILL_ID;
			}
		}
		break;

	case 0x0101:
		{
			ByteStream >> dwSize;
			ByteStream >> dwNum;

			SNATIVEID sSKILL_ID;
			for ( DWORD i=0; i<dwNum; i++ )
			{
				if ( i>=EMSKILLQUICK_SIZE )		break;

				GASSERT ( dwSize==sizeof(SNATIVEID) );
				ByteStream.ReadBuffer ( (LPBYTE)&sSKILL_ID, sizeof(SNATIVEID) );

				m_sSKILLQUICK[i] = sSKILL_ID;
			}

			ByteStream >> m_wSKILLQUICK_ACT;
		}
		break;
	case 0x0102: //add f4
		{
			ByteStream >> dwSize;
			ByteStream >> dwNum;

			SNATIVEID sSKILL_ID;
			for ( DWORD i=0; i<dwNum; i++ )
			{
				if ( i>=EMSKILLQUICK_SIZE )		break;

				GASSERT ( dwSize==sizeof(SNATIVEID) );
				ByteStream.ReadBuffer ( (LPBYTE)&sSKILL_ID, sizeof(SNATIVEID) );

				m_sSKILLQUICK[i] = sSKILL_ID;
			}

			ByteStream >> m_wSKILLQUICK_ACT;
		}
		break;
	};
	ShowSkillSlot();
}

void CRanManagerCharSkillSlot::ShowSkillSlot()
{
	int nNum = 0;
	TCHAR szTemp[128] = {0};
	for (int i = 0; i < EMSKILLQUICK_SIZE; i++ )
	{
		 SNATIVEID	sID = m_sSKILLQUICK[i];
		 if ( sID.wMainID !=65535 && sID.wSubID !=65535 )	_snprintf( szTemp, 128, "%d_%d",sID.wMainID,sID.wSubID);
		 else	_snprintf( szTemp, 128, "%s","Empty");

		switch (nNum)
		{
		case	0:	SetWin_Text ( this, IDC_BUTTON_SKILL_1_0,(const TCHAR*)szTemp );
		case	1:	SetWin_Text ( this, IDC_BUTTON_SKILL_1_1,(const TCHAR*)szTemp );
		case	2:	SetWin_Text ( this, IDC_BUTTON_SKILL_1_2,(const TCHAR*)szTemp );
		case	3:	SetWin_Text ( this, IDC_BUTTON_SKILL_1_3,(const TCHAR*)szTemp );
		case	4:	SetWin_Text ( this, IDC_BUTTON_SKILL_1_4,(const TCHAR*)szTemp );
		case	5:	SetWin_Text ( this, IDC_BUTTON_SKILL_1_5,(const TCHAR*)szTemp );
		case	6:	SetWin_Text ( this, IDC_BUTTON_SKILL_1_6,(const TCHAR*)szTemp );
		case	7:	SetWin_Text ( this, IDC_BUTTON_SKILL_1_7,(const TCHAR*)szTemp );
		case	8:	SetWin_Text ( this, IDC_BUTTON_SKILL_1_8,(const TCHAR*)szTemp );
		case	9:	SetWin_Text ( this, IDC_BUTTON_SKILL_1_9,(const TCHAR*)szTemp );

		case	10:	SetWin_Text ( this, IDC_BUTTON_SKILL_2_0,(const TCHAR*)szTemp );
		case	11:	SetWin_Text ( this, IDC_BUTTON_SKILL_2_1,(const TCHAR*)szTemp );
		case	12:	SetWin_Text ( this, IDC_BUTTON_SKILL_2_2,(const TCHAR*)szTemp );
		case	13:	SetWin_Text ( this, IDC_BUTTON_SKILL_2_3,(const TCHAR*)szTemp );
		case	14:	SetWin_Text ( this, IDC_BUTTON_SKILL_2_4,(const TCHAR*)szTemp );
		case	15:	SetWin_Text ( this, IDC_BUTTON_SKILL_2_5,(const TCHAR*)szTemp );
		case	16:	SetWin_Text ( this, IDC_BUTTON_SKILL_2_6,(const TCHAR*)szTemp );
		case	17:	SetWin_Text ( this, IDC_BUTTON_SKILL_2_7,(const TCHAR*)szTemp );
		case	18:	SetWin_Text ( this, IDC_BUTTON_SKILL_2_8,(const TCHAR*)szTemp );
		case	19:	SetWin_Text ( this, IDC_BUTTON_SKILL_2_9,(const TCHAR*)szTemp );

		case	20:	SetWin_Text ( this, IDC_BUTTON_SKILL_3_0,(const TCHAR*)szTemp );
		case	21:	SetWin_Text ( this, IDC_BUTTON_SKILL_3_1,(const TCHAR*)szTemp );
		case	22:	SetWin_Text ( this, IDC_BUTTON_SKILL_3_2,(const TCHAR*)szTemp );
		case	23:	SetWin_Text ( this, IDC_BUTTON_SKILL_3_3,(const TCHAR*)szTemp );
		case	24:	SetWin_Text ( this, IDC_BUTTON_SKILL_3_4,(const TCHAR*)szTemp );
		case	25:	SetWin_Text ( this, IDC_BUTTON_SKILL_3_5,(const TCHAR*)szTemp );
		case	26:	SetWin_Text ( this, IDC_BUTTON_SKILL_3_6,(const TCHAR*)szTemp );
		case	27:	SetWin_Text ( this, IDC_BUTTON_SKILL_3_7,(const TCHAR*)szTemp );
		case	28:	SetWin_Text ( this, IDC_BUTTON_SKILL_3_8,(const TCHAR*)szTemp );
		case	29:	SetWin_Text ( this, IDC_BUTTON_SKILL_3_9,(const TCHAR*)szTemp );

		case	30:	SetWin_Text ( this, IDC_BUTTON_SKILL_4_0,(const TCHAR*)szTemp );
		case	31:	SetWin_Text ( this, IDC_BUTTON_SKILL_4_1,(const TCHAR*)szTemp );
		case	32:	SetWin_Text ( this, IDC_BUTTON_SKILL_4_2,(const TCHAR*)szTemp );
		case	33:	SetWin_Text ( this, IDC_BUTTON_SKILL_4_3,(const TCHAR*)szTemp );
		case	34:	SetWin_Text ( this, IDC_BUTTON_SKILL_4_4,(const TCHAR*)szTemp );
		case	35:	SetWin_Text ( this, IDC_BUTTON_SKILL_4_5,(const TCHAR*)szTemp );
		case	36:	SetWin_Text ( this, IDC_BUTTON_SKILL_4_6,(const TCHAR*)szTemp );
		case	37:	SetWin_Text ( this, IDC_BUTTON_SKILL_4_7,(const TCHAR*)szTemp );
		case	38:	SetWin_Text ( this, IDC_BUTTON_SKILL_4_8,(const TCHAR*)szTemp );
		case	39:	SetWin_Text ( this, IDC_BUTTON_SKILL_4_9,(const TCHAR*)szTemp );

		};
		nNum++;
	}
	m_cActiveSkill.SetCurSel(m_wSKILLQUICK_ACT);
}

void CRanManagerCharSkillSlot::OnBnClickedButtonSkillslotSave()
{
	m_wSKILLQUICK_ACT = (WORD)m_cActiveSkill.GetCurSel();

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
	ByteStream << EMSKILLQUICK_VERSION;
	ByteStream << (DWORD)sizeof(SNATIVEID);
	DWORD dwSize2 = (DWORD) EMSKILLQUICK_SIZE;
	ByteStream << dwSize2;
	ByteStream.WriteBuffer ( (LPBYTE)m_sSKILLQUICK, (DWORD)sizeof(SNATIVEID)*dwSize2 );
	ByteStream << m_wSKILLQUICK_ACT;
	ByteStream.GetBuffer(pBuffer, dwSize);

	//write image
	if (pBuffer != NULL)
	{
		TCHAR szTemp[128] = {0};
		_snprintf( szTemp, 128, "UPDATE ChaInfo SET ChaSkillSlot=? WHERE (ChaNum=%u)", (DWORD)nChaNum );

		std::string strTIME = CDebugSet::GetCurTime ();
		LOGSCRIPT::LogToFile("CharSkillSlot.txt","%s--%s",strTIME.c_str(),szTemp);

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
			MessageBox("Error Saving CharSkillSlots Binary!","error",MB_OK);
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
	MessageBox("Done Saving CharSkillSlots!","Info",MB_OK);

	pBuffer = NULL;
	ShowSkillSlot();
}

void CRanManagerCharSkillSlot::OnBnClickedButtonSkillslotcancel()
{
	m_pToolTab->ActivePage(CHARPAGE_MAIN,0);
}

void CRanManagerCharSkillSlot::OnBnClickedButtonSkill10(){	SetSlotState(this,IDC_BUTTON_SKILL_1_0);	LoadSlot(0);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill11(){	SetSlotState(this,IDC_BUTTON_SKILL_1_1);	LoadSlot(1);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill12(){	SetSlotState(this,IDC_BUTTON_SKILL_1_2);	LoadSlot(2);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill13(){	SetSlotState(this,IDC_BUTTON_SKILL_1_3);	LoadSlot(3);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill14(){	SetSlotState(this,IDC_BUTTON_SKILL_1_4);	LoadSlot(4);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill15(){	SetSlotState(this,IDC_BUTTON_SKILL_1_5);	LoadSlot(5);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill16(){	SetSlotState(this,IDC_BUTTON_SKILL_1_6);	LoadSlot(6);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill17(){	SetSlotState(this,IDC_BUTTON_SKILL_1_7);	LoadSlot(7);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill18(){	SetSlotState(this,IDC_BUTTON_SKILL_1_8);	LoadSlot(8);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill19(){	SetSlotState(this,IDC_BUTTON_SKILL_1_9);	LoadSlot(9);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill20(){	SetSlotState(this,IDC_BUTTON_SKILL_2_0);	LoadSlot(10);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill21(){	SetSlotState(this,IDC_BUTTON_SKILL_2_1);	LoadSlot(11);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill22(){	SetSlotState(this,IDC_BUTTON_SKILL_2_2);	LoadSlot(12);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill23(){	SetSlotState(this,IDC_BUTTON_SKILL_2_3);	LoadSlot(13);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill24(){	SetSlotState(this,IDC_BUTTON_SKILL_2_4);	LoadSlot(14);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill25(){	SetSlotState(this,IDC_BUTTON_SKILL_2_5);	LoadSlot(15);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill26(){	SetSlotState(this,IDC_BUTTON_SKILL_2_6);	LoadSlot(16);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill27(){	SetSlotState(this,IDC_BUTTON_SKILL_2_7);	LoadSlot(17);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill28(){	SetSlotState(this,IDC_BUTTON_SKILL_2_8);	LoadSlot(18);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill29(){	SetSlotState(this,IDC_BUTTON_SKILL_2_9);	LoadSlot(19);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill30(){	SetSlotState(this,IDC_BUTTON_SKILL_3_0);	LoadSlot(20);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill31(){	SetSlotState(this,IDC_BUTTON_SKILL_3_1);	LoadSlot(21);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill32(){	SetSlotState(this,IDC_BUTTON_SKILL_3_2);	LoadSlot(22);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill33(){	SetSlotState(this,IDC_BUTTON_SKILL_3_3);	LoadSlot(23);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill34(){	SetSlotState(this,IDC_BUTTON_SKILL_3_4);	LoadSlot(24);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill35(){	SetSlotState(this,IDC_BUTTON_SKILL_3_5);	LoadSlot(25);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill36(){	SetSlotState(this,IDC_BUTTON_SKILL_3_6);	LoadSlot(26);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill37(){	SetSlotState(this,IDC_BUTTON_SKILL_3_7);	LoadSlot(27);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill38(){	SetSlotState(this,IDC_BUTTON_SKILL_3_8);	LoadSlot(28);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill39(){	SetSlotState(this,IDC_BUTTON_SKILL_3_9);	LoadSlot(29);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill40(){	SetSlotState(this,IDC_BUTTON_SKILL_4_0);	LoadSlot(30);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill41(){	SetSlotState(this,IDC_BUTTON_SKILL_4_1);	LoadSlot(31);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill42(){	SetSlotState(this,IDC_BUTTON_SKILL_4_2);	LoadSlot(32);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill43(){	SetSlotState(this,IDC_BUTTON_SKILL_4_3);	LoadSlot(33);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill44(){	SetSlotState(this,IDC_BUTTON_SKILL_4_4);	LoadSlot(34);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill45(){	SetSlotState(this,IDC_BUTTON_SKILL_4_5);	LoadSlot(35);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill46(){	SetSlotState(this,IDC_BUTTON_SKILL_4_6);	LoadSlot(36);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill47(){	SetSlotState(this,IDC_BUTTON_SKILL_4_7);	LoadSlot(37);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill48(){	SetSlotState(this,IDC_BUTTON_SKILL_4_8);	LoadSlot(38);	}
void CRanManagerCharSkillSlot::OnBnClickedButtonSkill49(){	SetSlotState(this,IDC_BUTTON_SKILL_4_9);	LoadSlot(39);	}

void CRanManagerCharSkillSlot::SetSlotState ( CDialog *pDlg,int nID )
{
	ResetSlotState (this);
	CButton *pBtn;
	switch (nID)
	{
	case IDC_BUTTON_SKILL_1_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_1_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_1_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_1_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_1_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_1_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_1_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_1_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_1_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_1_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_9 );	pBtn->SetState(TRUE);	break;

	case IDC_BUTTON_SKILL_2_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_2_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_2_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_2_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_2_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_2_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_2_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_2_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_2_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_2_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_9 );	pBtn->SetState(TRUE);	break;

	case IDC_BUTTON_SKILL_3_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_3_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_3_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_3_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_3_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_3_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_3_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_3_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_3_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_3_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_9 );	pBtn->SetState(TRUE);	break;

	case IDC_BUTTON_SKILL_4_0:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_0 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_4_1:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_1 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_4_2:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_2 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_4_3:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_3 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_4_4:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_4 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_4_5:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_5 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_4_6:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_6 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_4_7:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_7 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_4_8:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_8 );	pBtn->SetState(TRUE);	break;
	case IDC_BUTTON_SKILL_4_9:	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_9 );	pBtn->SetState(TRUE);	break;
	};
}

void CRanManagerCharSkillSlot::ResetSlotState ( CDialog *pDlg )
{
	CButton *pBtn;
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_1_9 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_2_9 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_3_9 );	pBtn->SetState(FALSE);

	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_0 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_1 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_2 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_3 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_4 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_5 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_6 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_7 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_8 );	pBtn->SetState(FALSE);
	pBtn =  (CButton*)pDlg->GetDlgItem ( IDC_BUTTON_SKILL_4_9 );	pBtn->SetState(FALSE);
}

void CRanManagerCharSkillSlot::LoadSlot(int nSlot)
{
	SNATIVEID sID = m_sSKILLQUICK[nSlot];
	SetWin_Num_int(this,IDC_EDIT_S_MID,sID.wMainID );
	SetWin_Num_int(this,IDC_EDIT_S_SID,sID.wSubID );

	PGLSKILL	pSkill = GLSkillMan::GetInstance().GetData(sID);
	if(pSkill)
	{
		SetWin_Text(this,IDC_EDIT_S_NAME,pSkill->GetName());
	}
	else
	{
		SetWin_Text(this,IDC_EDIT_S_NAME,"Unknown Skill");
	}
	nActiveSlot = nSlot;

	SetWin_Text(this,IDC_EDIT_S_ACTIVE,RMComments::m_SkillSlots[nSlot].c_str() );
	SetWin_Enable(this,IDC_BUTTON_SKILL_CHANGE,TRUE);
	SetWin_Enable(this,IDC_BUTTON_SKILL_SAVE,TRUE);
	SetWin_Enable(this,IDC_BUTTON_SKILL_DELETE,TRUE);
}

void CRanManagerCharSkillSlot::OnBnClickedButtonSkillSave()
{
	SNATIVEID sID;
	sID.wMainID = GetWin_Num_int(this,IDC_EDIT_S_MID);
	sID.wSubID = GetWin_Num_int(this,IDC_EDIT_S_SID);
	m_sSKILLQUICK[nActiveSlot] = sID;
	ShowSkillSlot();
}

void CRanManagerCharSkillSlot::OnBnClickedButtonSkillDelete()
{
	SetWin_Num_int(this,IDC_EDIT_S_MID,65535 );
	SetWin_Num_int(this,IDC_EDIT_S_SID,65535 );
	SetWin_Text(this,IDC_EDIT_S_NAME,"Unknown Skill");

	m_sSKILLQUICK[nActiveSlot] = NATIVEID_NULL();
	ShowSkillSlot();
}

void CRanManagerCharSkillSlot::OnBnClickedButtonSkillChange()
{
	CSkillSearch sSkillSearch;
	if ( IDOK == sSkillSearch.DoModal () )
	{
		SNATIVEID sID = sSkillSearch.sSelectedSkill;
		SetWin_Num_int(this,IDC_EDIT_S_MID,sID.wMainID );
		SetWin_Num_int(this,IDC_EDIT_S_SID,sID.wSubID );

		PGLSKILL	pSkill = GLSkillMan::GetInstance().GetData(sID);
		if(pSkill)
		{
			SetWin_Text(this,IDC_EDIT_S_NAME,pSkill->GetName());
		}
		else
		{
			SetWin_Text(this,IDC_EDIT_S_NAME,"Unknown Skill");
		}
	}
}

void CRanManagerCharSkillSlot::OnBnClickedButtonDeleteSlotAll()
{
	for ( int i=0; i<EMSKILLQUICK_SIZE; ++i )	m_sSKILLQUICK[i] = NATIVEID_NULL();
	ShowSkillSlot();
}

void CRanManagerCharSkillSlot::OnBnClickedButtonDeleteSlotF1()
{
	for ( int i=0; i<10; ++i )	m_sSKILLQUICK[i] = NATIVEID_NULL();
	ShowSkillSlot();
}

void CRanManagerCharSkillSlot::OnBnClickedButtonDeleteSlotF2()
{
	for ( int i=10; i<20; ++i )	m_sSKILLQUICK[i] = NATIVEID_NULL();
	ShowSkillSlot();
}

void CRanManagerCharSkillSlot::OnBnClickedButtonDeleteSlotF3()
{
	for ( int i=20; i<30; ++i )	m_sSKILLQUICK[i] = NATIVEID_NULL();
	ShowSkillSlot();
}

void CRanManagerCharSkillSlot::OnBnClickedButtonDeleteSlotF4()
{
	for ( int i=30; i<40; ++i )	m_sSKILLQUICK[i] = NATIVEID_NULL();
	ShowSkillSlot();
}

