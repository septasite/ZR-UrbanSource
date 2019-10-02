// RanManagerCharEdit.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerCharEdit.h"
#include "RanManagerCharTab.h"
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
#include ".\ranmanagercharedit.h"

// CRanManagerCharEdit dialog
GLMapList CRanManagerCharEdit::m_sMapList;

IMPLEMENT_DYNAMIC(CRanManagerCharEdit, CPropertyPage)
CRanManagerCharEdit::CRanManagerCharEdit(LOGFONT logfont)
	: CPropertyPage(CRanManagerCharEdit::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerCharEdit::~CRanManagerCharEdit()
{
}

void CRanManagerCharEdit::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRanManagerCharEdit, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_EMCLASS, OnCbnSelchangeComboEmclass)
	ON_BN_CLICKED(IDC_BUTTON_CHAREDIT_SAVE, OnBnClickedButtonChareditSave)
	ON_BN_CLICKED(IDC_BUTTON_CHAREDIT_CALCEL, OnBnClickedButtonChareditCalcel)
	ON_BN_CLICKED(IDC_BUTTON_CHECKNAME, OnBnClickedButtonCheckname)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEGUILD, OnBnClickedButtonRemoveguild)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFERGUILD, OnBnClickedButtonTransferguild)
	ON_BN_CLICKED(IDC_BUTTON_MAPEDIT_START, OnBnClickedButtonMapeditStart)
	ON_BN_CLICKED(IDC_BUTTON_MAPEDIT_SAVE, OnBnClickedButtonMapeditSave)
	ON_BN_CLICKED(IDC_BUTTON_MAPEDIT_RET, OnBnClickedButtonMapeditRet)
	ON_BN_CLICKED(IDC_BUTTON_SP_CHANGE, OnBnClickedButtonSpChange)
	ON_BN_CLICKED(IDC_BUTTON_SET_C1, OnBnClickedButtonSetC1)
	ON_BN_CLICKED(IDC_BUTTON_SET_C2, OnBnClickedButtonSetC2)
	ON_BN_CLICKED(IDC_BUTTON_SET_C3, OnBnClickedButtonSetC3)
	ON_BN_CLICKED(IDC_BUTTON_RESET_C1, OnBnClickedButtonResetC1)
	ON_BN_CLICKED(IDC_BUTTON_RESET_C2, OnBnClickedButtonResetC2)
	ON_BN_CLICKED(IDC_BUTTON_RESET_C3, OnBnClickedButtonResetC3)
END_MESSAGE_MAP()


// CRanManagerCharEdit message handlers
BOOL CRanManagerCharEdit::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	SetWin_Combo_Init ( this, IDC_COMBO_EMTRIBE, COMMENT::TRIBE, TRIBE_NSIZE );
	SetWin_Combo_Init ( this, IDC_COMBO_EMCLASS, COMMENT::CHARCLASS, GLCI_NUM_NEWEST );
	SetWin_Combo_Init ( this, IDC_COMBO_EMSCHOOL, GLCONST_CHAR::strSCHOOLNAME, GLSCHOOL_NUM );
	SetWin_Combo_Init ( this, IDC_COMBO_CHARSTATUS, RMComments::m_CharStatus, CHARSTATUS_SIZE );

	m_sMapList.LoadMapList ( "mapslist.ini" );
	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerCharEdit::SetChar(int nChar)
{
	LoadChar(nChar);
}

void CRanManagerCharEdit::LoadChar(int nChar)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT UserNum,SGNum,ChaName,ChaTribe,ChaClass,"
							"ChaBright,ChaLevel,ChaDex,ChaIntel,ChaPower,"
							"ChaStrong,ChaSpirit,ChaStrength,ChaStRemain,ChaAttackP,"							
							"ChaDefenseP,ChaFightA,ChaShootA,ChaSkillPoint,ChaHP,"
							"ChaMP,ChaSP,ChaPK,ChaStartMap,ChaStartGate,"
							"ChaPosX,ChaPosY,ChaPosZ,ChaMoney,ChaExp,"
							"ChaSaveMap,ChaSavePosX,ChaSavePosY,ChaSavePosZ,ChaSchool,"
							"ChaHair,ChaFace,ChaLiving,ChaInvenLine,"
							"ChaReturnMap,ChaReturnPosX,ChaReturnPosY,ChaReturnPosZ,GuNum,"
							"ChaGuName,ChaSex,ChaHairColor, ChaReExp, ChaSpMID, ChaSpSID,"
							"ChaReborn, ChaCP, ChaPkWin, ChaPkLoss,"
							"ChaDeleted, GuPosition, ChaCreateDate, ChaDeletedDate, ChaGuSecede "
							"FROM %s.dbo.ChaInfo WHERE ChaNum=%d",CToolCfg::GetInstance()->szGameDb,nChar );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharEdit.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaName = SQL_NTS; 
	SQLCHAR    szChaGuName[CHAR_SZNAME+1] = {0}; SQLINTEGER cbChaGuName = SQL_NTS;
    SQLINTEGER nUserNum = 0, cbUserNum=SQL_NTS;
	SQLINTEGER nChaTribe = 0, cbChaTribe=SQL_NTS;
	SQLINTEGER nChaClass = 0, cbChaClass=SQL_NTS;
	SQLINTEGER nSGNum = 0, cbSGNum=SQL_NTS;
    SQLINTEGER nChaLevel = 0, cbChaLevel=SQL_NTS;
	SQLINTEGER nChaPower = 0, cbChaPower=SQL_NTS; 
	SQLINTEGER nChaStrong = 0, cbChaStrong=SQL_NTS;   
	SQLINTEGER nChaStrength = 0, cbChaStrength=SQL_NTS; 
	SQLINTEGER nChaSpirit = 0, cbChaSpirit=SQL_NTS;
	SQLINTEGER nChaDex = 0, cbChaDex=SQL_NTS;
	SQLINTEGER nChaIntel = 0, cbChaIntel=SQL_NTS;
	SQLINTEGER nChaStRemain = 0, cbChaStRemain=SQL_NTS; 
	SQLINTEGER nChaHP = 0, cbChaHP=SQL_NTS;
	SQLINTEGER nChaMP = 0, cbChaMP=SQL_NTS;
	SQLINTEGER nChaStartMap = 0, cbChaStartMap=SQL_NTS;
	SQLINTEGER nChaStartGate = 0, cbChaStartGate=SQL_NTS;
	SQLFLOAT fChaPosX = 0; SQLINTEGER cbChaPosX=SQL_NTS;
	SQLFLOAT fChaPosY = 0; SQLINTEGER cbChaPosY=SQL_NTS;
	SQLFLOAT fChaPosZ = 0; SQLINTEGER cbChaPosZ=SQL_NTS;
	SQLINTEGER nChaBright = 0, cbChaBright=SQL_NTS;
	SQLINTEGER nChaAttackP = 0, cbChaAttackP=SQL_NTS;
	SQLINTEGER nChaDefenseP = 0, cbChaDefenseP=SQL_NTS;
	SQLINTEGER nChaFightA = 0, cbChaFightA=SQL_NTS;
	SQLINTEGER nChaShootA = 0, cbChaShootA=SQL_NTS;
	SQLINTEGER nChaSP = 0, cbChaSP=SQL_NTS;
	SQLINTEGER nChaPK = 0, cbChaPK=SQL_NTS;
	SQLINTEGER nChaSkillPoint = 0, cbChaSkillPoint=SQL_NTS;
	SQLINTEGER nChaSaveMap = 0, cbChaSaveMap=SQL_NTS;
	SQLFLOAT fChaSavePosX = 0; SQLINTEGER cbChaSavePosX=SQL_NTS;
	SQLFLOAT fChaSavePosY = 0; SQLINTEGER cbChaSavePosY=SQL_NTS;
	SQLFLOAT fChaSavePosZ = 0; SQLINTEGER cbChaSavePosZ=SQL_NTS;
	SQLINTEGER nChaSchool = 0, cbChaSchool = SQL_NTS;
	SQLINTEGER nChaHair = 0, cbChaHair = SQL_NTS;
	SQLINTEGER nChaFace = 0, cbChaFace = SQL_NTS;
	SQLINTEGER nChaLiving = 0, cbChaLiving = SQL_NTS;
	SQLSMALLINT nChaSex = 0; SQLINTEGER cbChaSex = SQL_NTS;
	SQLINTEGER nChaHairColor =0, cbChaHairColor = SQL_NTS;
	LONGLONG   llChaExp = 0, llChaMoney = 0;
	SQLINTEGER cbChaExp=SQL_NTS, cbChaMoney=SQL_NTS; 
    SQLINTEGER nChaInvenLine = 0; SQLINTEGER cbChaInvenLine = SQL_NTS;
    SQLINTEGER nGuNum = 0; SQLINTEGER cbGuNum = SQL_NTS;
    SQLINTEGER nChaReturnMap  = 0; SQLINTEGER cbChaReturnMap  = SQL_NTS;
	SQLFLOAT   fChaReturnPosX = 0; SQLINTEGER cbChaReturnPosX = SQL_NTS;
	SQLFLOAT   fChaReturnPosY = 0; SQLINTEGER cbChaReturnPosY = SQL_NTS;
	SQLFLOAT   fChaReturnPosZ = 0; SQLINTEGER cbChaReturnPosZ = SQL_NTS;
	LONGLONG   llChaReExp = 0;
	SQLINTEGER cbChaReExp=SQL_NTS;
	SQLINTEGER nChaSpMID = 0, cbChaSpMID=SQL_NTS;
	SQLINTEGER nChaSpSID = 0, cbChaSpSID=SQL_NTS;
	SQLINTEGER nChaReborn = 0, cbChaReborn=SQL_NTS;
	SQLINTEGER nChaCP = 0, cbChaCP=SQL_NTS; 
	SQLINTEGER nChaPkWin = 0, cbChaPkWin=SQL_NTS;
	SQLINTEGER nChaPkLoss = 0, cbChaPkLoss=SQL_NTS;
	SQLINTEGER nChaDeleted = 0, cbChaDeleted=SQL_NTS; 
	SQLINTEGER nGuPosition = 0, cbGuPosition=SQL_NTS; 
	TIMESTAMP_STRUCT sChaCreateDate;	SQLINTEGER cbChaCreateDate = SQL_NTS;
	TIMESTAMP_STRUCT sChaDeletedDate;	SQLINTEGER cbChaDeletedDate = SQL_NTS;
	TIMESTAMP_STRUCT sChaGuSecede;		SQLINTEGER cbChaGuSecede = SQL_NTS;
	

	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{		
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nUserNum,       0, &cbUserNum);
			::SQLGetData(hStmt, 2, SQL_C_LONG, &nSGNum,         0, &cbSGNum);
            ::SQLGetData(hStmt, 3, SQL_C_CHAR, szChaName   ,  CHR_ID_LENGTH+1, &cbChaName); 
            ::SQLGetData(hStmt, 4, SQL_C_LONG, &nChaTribe,      0, &cbChaTribe);
            ::SQLGetData(hStmt, 5, SQL_C_LONG, &nChaClass,      0, &cbChaClass);
			::SQLGetData(hStmt, 6, SQL_C_LONG, &nChaBright,     0, &cbChaBright);
            ::SQLGetData(hStmt, 7, SQL_C_LONG, &nChaLevel,      0, &cbChaLevel);
			::SQLGetData(hStmt, 8, SQL_C_LONG, &nChaDex,        0, &cbChaDex);
			::SQLGetData(hStmt, 9, SQL_C_LONG, &nChaIntel,      0, &cbChaIntel);
            ::SQLGetData(hStmt,10, SQL_C_LONG, &nChaPower,      0, &cbChaPower);
            ::SQLGetData(hStmt,11, SQL_C_LONG, &nChaStrong,     0, &cbChaStrong);
			::SQLGetData(hStmt,12, SQL_C_LONG, &nChaSpirit,     0, &cbChaSpirit);
            ::SQLGetData(hStmt,13, SQL_C_LONG, &nChaStrength,   0, &cbChaStrength);
			::SQLGetData(hStmt,14, SQL_C_LONG, &nChaStRemain,   0, &cbChaStRemain);
			::SQLGetData(hStmt,15, SQL_C_LONG, &nChaAttackP,    0, &cbChaAttackP);		         
            ::SQLGetData(hStmt,16, SQL_C_LONG, &nChaDefenseP,   0, &cbChaDefenseP);
			::SQLGetData(hStmt,17, SQL_C_LONG, &nChaFightA,     0, &cbChaFightA);
			::SQLGetData(hStmt,18, SQL_C_LONG, &nChaShootA,     0, &cbChaShootA);
			::SQLGetData(hStmt,19, SQL_C_LONG, &nChaSkillPoint, 0, &cbChaSkillPoint);
			::SQLGetData(hStmt,20, SQL_C_LONG, &nChaHP,			0, &cbChaHP);
			::SQLGetData(hStmt,21, SQL_C_LONG, &nChaMP,			0, &cbChaMP);
			::SQLGetData(hStmt,22, SQL_C_LONG, &nChaSP,			0, &cbChaSP);
			::SQLGetData(hStmt,23, SQL_C_LONG, &nChaPK,			0, &cbChaPK);
			::SQLGetData(hStmt,24, SQL_C_LONG, &nChaStartMap,	0, &cbChaStartMap);
			::SQLGetData(hStmt,25, SQL_C_LONG, &nChaStartGate,  0, &cbChaStartGate);
			::SQLGetData(hStmt,26, SQL_C_DOUBLE, &fChaPosX,		0, &cbChaPosX);
			::SQLGetData(hStmt,27, SQL_C_DOUBLE, &fChaPosY,		0, &cbChaPosY);
			::SQLGetData(hStmt,28, SQL_C_DOUBLE, &fChaPosZ,		0, &cbChaPosZ);			
            ::SQLGetData(hStmt,29, SQL_C_SBIGINT, &llChaMoney,  0, &cbChaMoney);
            ::SQLGetData(hStmt,30, SQL_C_SBIGINT, &llChaExp,    0, &cbChaExp);
			::SQLGetData(hStmt,31, SQL_C_LONG, &nChaSaveMap,    0, &cbChaSaveMap);
			::SQLGetData(hStmt,32, SQL_C_DOUBLE, &fChaSavePosX,   0, &cbChaSavePosX);
			::SQLGetData(hStmt,33, SQL_C_DOUBLE, &fChaSavePosY,   0, &cbChaSavePosY);
			::SQLGetData(hStmt,34, SQL_C_DOUBLE, &fChaSavePosZ,   0, &cbChaSavePosZ);
			::SQLGetData(hStmt,35, SQL_C_LONG, &nChaSchool,		0, &cbChaSchool);
			::SQLGetData(hStmt,36, SQL_C_LONG, &nChaHair,		0, &cbChaHair);
			::SQLGetData(hStmt,37, SQL_C_LONG, &nChaFace,		0, &cbChaFace);
			::SQLGetData(hStmt,38, SQL_C_LONG, &nChaLiving,		0, &cbChaLiving);
            ::SQLGetData(hStmt,39, SQL_C_LONG, &nChaInvenLine, 0, &cbChaInvenLine);
            ::SQLGetData(hStmt,40, SQL_C_LONG,   &nChaReturnMap,  0, &cbChaReturnMap);
			::SQLGetData(hStmt,41, SQL_C_DOUBLE, &fChaReturnPosX, 0, &cbChaReturnPosX);
			::SQLGetData(hStmt,42, SQL_C_DOUBLE, &fChaReturnPosY, 0, &cbChaReturnPosY);
			::SQLGetData(hStmt,43, SQL_C_DOUBLE, &fChaReturnPosZ, 0, &cbChaReturnPosZ);
            ::SQLGetData(hStmt,44, SQL_C_LONG, &nGuNum, 0, &cbGuNum);
            ::SQLGetData(hStmt,45, SQL_C_CHAR, szChaGuName, CHAR_SZNAME, &cbChaGuName); 
			::SQLGetData(hStmt,46, SQL_SMALLINT, &nChaSex,       0, &cbChaSex);
			::SQLGetData(hStmt,47, SQL_C_LONG,   &nChaHairColor, 0, &cbChaHairColor);
			::SQLGetData(hStmt,48, SQL_C_SBIGINT, &llChaReExp, 0, &cbChaReExp);
			::SQLGetData(hStmt,49, SQL_C_LONG, &nChaSpMID, 0, &cbChaSpMID);
			::SQLGetData(hStmt,50, SQL_C_LONG, &nChaSpSID, 0, &cbChaSpSID);	
			::SQLGetData(hStmt,51, SQL_C_LONG, &nChaReborn, 0, &cbChaReborn);
			::SQLGetData(hStmt,52, SQL_C_LONG, &nChaCP,			0, &cbChaCP);	
			::SQLGetData(hStmt,53, SQL_C_LONG, &nChaPkWin, 0, &cbChaPkWin);	
			::SQLGetData(hStmt,54, SQL_C_LONG, &nChaPkLoss, 0, &cbChaPkLoss);
			::SQLGetData(hStmt,57, SQL_C_LONG, &nChaDeleted,			0, &cbChaDeleted );
			::SQLGetData(hStmt,58, SQL_C_LONG, &nGuPosition,			0, &cbGuPosition );
			::SQLGetData(hStmt,59, SQL_C_TYPE_TIMESTAMP,	&sChaCreateDate,		0,		&cbChaCreateDate );
			::SQLGetData(hStmt,60, SQL_C_TYPE_TIMESTAMP,	&sChaDeletedDate,		0,		&cbChaDeletedDate );
			::SQLGetData(hStmt,61, SQL_C_TYPE_TIMESTAMP,	&sChaGuSecede,		0,		&cbChaGuSecede );
			


			SetWin_Num_int(this,IDC_EDIT_CHARID,nChar);
			SetWin_Num_int(this,IDC_EDIT_USERID,nUserNum);
			SetWin_Num_int(this,IDC_EDIT_SGNUM,nSGNum);
			SetWin_Text(this,IDC_EDIT_CHANAME,(const char*) szChaName);
			SetWin_Text(this,IDC_EDIT_CHAGUNAME,(const char*) szChaGuName);
			SetWin_Combo_Sel(this,IDC_COMBO_EMTRIBE,nChaTribe);
			int nClass = CharClassToIndex(EMCHARCLASS(nChaClass));
			SetWin_Combo_Sel(this,IDC_COMBO_EMCLASS,nClass);
			SetWin_Combo_Sel(this,IDC_COMBO_EMSCHOOL,nChaSchool);
			SetWin_Num_int(this,IDC_EDIT_LEVEL,nChaLevel);
			SetWin_Num_int(this,IDC_EDIT_REBORN,nChaReborn);
			SetWin_Num_int(this,IDC_EDIT_POWER,nChaPower);
			SetWin_Num_int(this,IDC_EDIT_STRONG,nChaStrong);
			SetWin_Num_int(this,IDC_EDIT_STRENGTH,nChaStrength);
			SetWin_Num_int(this,IDC_EDIT_SPIRIT,nChaSpirit);
			SetWin_Num_int(this,IDC_EDIT_DEX,nChaDex);
			SetWin_Num_int(this,IDC_EDIT_INTEL,nChaIntel);
			SetWin_Num_int(this,IDC_EDIT_STATSP,nChaStRemain);
			SetWin_Num_int(this,IDC_EDIT_SKILLP,nChaSkillPoint);

			CString strMoney;
			strMoney.Format("%I64d",llChaMoney);
			SetWin_Text ( this, IDC_EDIT_CHAMONEY,strMoney);
			strMoney.Format("%I64d",llChaExp);
			SetWin_Text ( this, IDC_EDIT_CHAEXP,strMoney);
			strMoney.Format("%I64d",llChaReExp);
			SetWin_Text ( this, IDC_EDIT_CHAREEXP,strMoney);

			SetWin_Num_int(this,IDC_EDIT_CHAHP,nChaHP);
			SetWin_Num_int(this,IDC_EDIT_CHAMP,nChaMP);
			SetWin_Num_int(this,IDC_EDIT_CHASP,nChaSP);
			SetWin_Num_int(this,IDC_EDIT_CHACP,nChaCP);

			SetWin_Num_int(this,IDC_EDIT_FACE,nChaFace);
			SetWin_Num_int(this,IDC_EDIT_HAIR,nChaHair);
			SetWin_Num_int(this,IDC_EDIT_HAIRCOLOR,nChaHairColor);

			SetWin_Num_int(this,IDC_EDIT_ATTACK_P,nChaAttackP);
			SetWin_Num_int(this,IDC_EDIT_DEFENSE_P,nChaDefenseP);
			SetWin_Num_int(this,IDC_EDIT_FIGHT_A,nChaFightA);
			SetWin_Num_int(this,IDC_EDIT_SHOOT_A,nChaShootA);

			SetWin_Num_int(this,IDC_EDIT_CHAPK,nChaPK);
			SetWin_Num_int(this,IDC_EDIT_CHAPKWIN,nChaPkWin);
			SetWin_Num_int(this,IDC_EDIT_CHAPKLOSS,nChaPkLoss);

			SetWin_Num_int(this,IDC_EDIT_LP,nChaLiving);
			SetWin_Num_int(this,IDC_EDIT_BP,nChaBright);
			SetWin_Num_int(this,IDC_EDIT_INVENLINE,nChaInvenLine);

			SNATIVEID	sStartMapID = (DWORD) nChaStartMap;
			SetWin_Num_int(this,IDC_EDIT_SM_MID,sStartMapID.wMainID);
			SetWin_Num_int(this,IDC_EDIT_SM_SID,sStartMapID.wSubID);
			SetWin_Num_int(this,IDC_EDIT_SM_GATEID,nChaStartGate);
			SetWin_Num_float(this,IDC_EDIT_SM_POSX,(float) fChaPosX);
			SetWin_Num_float(this,IDC_EDIT_SM_POSY,(float) fChaPosY);
			SetWin_Num_float(this,IDC_EDIT_SM_POSZ,(float) fChaPosZ);
			
			SNATIVEID	sSaveMapID = (DWORD) nChaSaveMap;
			SetWin_Num_int(this,IDC_EDIT_SAVE_MID,sSaveMapID.wMainID);
			SetWin_Num_int(this,IDC_EDIT_SAVE_SID,sSaveMapID.wSubID);
			SetWin_Num_float(this,IDC_EDIT_SAVE_POSX,(float) fChaSavePosX);
			SetWin_Num_float(this,IDC_EDIT_SAVE_POSY,(float) fChaSavePosY);
			SetWin_Num_float(this,IDC_EDIT_SAVE_POSZ,(float) fChaSavePosZ);
			
			SNATIVEID	sRetMapID = (DWORD) nChaReturnMap;
			SetWin_Num_int(this,IDC_EDIT_RET_MID,sRetMapID.wMainID);
			SetWin_Num_int(this,IDC_EDIT_RET_SID,sRetMapID.wSubID);
			SetWin_Num_float(this,IDC_EDIT_RET_POSX,(float) fChaReturnPosX);
			SetWin_Num_float(this,IDC_EDIT_RET_POSY,(float) fChaReturnPosY);
			SetWin_Num_float(this,IDC_EDIT_RET_POSZ,(float) fChaReturnPosZ);
			
			{
				CString strMap;
				SMAPNODE* pNODE(NULL);
				pNODE = m_sMapList.FindMapNode ( sStartMapID );
				if ( pNODE )	strMap = pNODE->strMapName.c_str();
				SetWin_Text(this,IDC_EDIT_SM_MAPNAME,strMap.GetString());
			}
			{
				CString strMap;
				SMAPNODE* pNODE(NULL);
				pNODE = m_sMapList.FindMapNode ( sSaveMapID );
				if ( pNODE )	strMap = pNODE->strMapName.c_str();
				SetWin_Text(this,IDC_EDIT_SAVE_MAPNAME,strMap.GetString());
			}
			{
				CString strMap;
				SMAPNODE* pNODE(NULL);
				pNODE = m_sMapList.FindMapNode ( sRetMapID );
				if ( pNODE )	strMap = pNODE->strMapName.c_str();
				SetWin_Text(this,IDC_EDIT_RET_MAPNAME,strMap.GetString());
			}

			SITEM* pItem = GLItemMan::GetInstance().GetItem((WORD) nChaSpMID,(WORD) nChaSpSID );
			if ( pItem )
			{
				SetWin_Num_int(this,IDC_EDIT_SP_MID,pItem->sBasicOp.sNativeID.wMainID);
				SetWin_Num_int(this,IDC_EDIT_SP_SID,pItem->sBasicOp.sNativeID.wSubID);
				SetWin_Text(this,IDC_EDIT_SP_NAME,pItem->GetName());
			}
			else
			{
				SetWin_Num_int(this,IDC_EDIT_SP_MID,(WORD) nChaSpMID);
				SetWin_Num_int(this,IDC_EDIT_SP_SID,(WORD) nChaSpSID);
				SetWin_Text(this,IDC_EDIT_SP_NAME,"Unknown Item");
			}

			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_1,sChaCreateDate.day);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_2,sChaCreateDate.month);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_3,sChaCreateDate.year);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_4,sChaCreateDate.hour);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_5,sChaCreateDate.minute);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_6,sChaCreateDate.second);

			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_1,sChaDeletedDate.day);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_2,sChaDeletedDate.month);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_3,sChaDeletedDate.year);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_4,sChaDeletedDate.hour);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_5,sChaDeletedDate.minute);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_6,sChaDeletedDate.second);

			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_1,sChaGuSecede.day);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_2,sChaGuSecede.month);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_3,sChaGuSecede.year);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_4,sChaGuSecede.hour);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_5,sChaGuSecede.minute);
			SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_6,sChaGuSecede.second);
				
			SetWin_Combo_Sel(this,IDC_COMBO_CHARSTATUS,nChaDeleted);

			

			/*DWORD	dwFlags = nGuPosition;
			SetWin_Check ( this, IDC_CHECK_G_INVITE, dwFlags&EMCLUB_SUBMATER_JOIN );
			SetWin_Check ( this, IDC_CHECK_G_KICK, dwFlags&EMCLUB_SUBMATER_KICK );
			SetWin_Check ( this, IDC_CHECK_G_NOTICE, dwFlags&EMCLUB_SUBMATER_NOTICE );
			SetWin_Check ( this, IDC_CHECK_G_VERIFY, dwFlags&EMCLUB_SUBMATER_CD );
			SetWin_Check ( this, IDC_CHECK_G_BADGE, dwFlags&EMCLUB_SUBMATER_MARK );
			SetWin_Check ( this, IDC_CHECK_G_CDM, dwFlags&EMCLUB_SUBMATER_CDM );*/

			GetGuild(nGuNum);
			OnCbnSelchangeComboEmclass();
		}
		else
		{
			break;
		}
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}
void CRanManagerCharEdit::OnCbnSelchangeComboEmclass()
{
	int nClass = GetWin_Combo_Sel(this,IDC_COMBO_EMCLASS);
	if ( nClass == GLCI_FIGHTER_M || nClass == GLCI_ARMS_M || nClass == GLCI_EXTREME_M || nClass == GLCI_ARCHER_M ||
		nClass == GLCI_SPIRIT_M || nClass == GLCI_SCIENCE_M || nClass == GLCI_ASSASSIN_M)
	{
		SetWin_Text(this,IDC_EDIT_SEX,"Male");
	}
	else if ( nClass == GLCI_FIGHTER_W || nClass == GLCI_ARMS_W || nClass == GLCI_EXTREME_W || nClass == GLCI_ARCHER_W ||
			nClass == GLCI_SPIRIT_W || nClass == GLCI_SCIENCE_W || nClass == GLCI_ASSASSIN_W )
	{
		SetWin_Text(this,IDC_EDIT_SEX,"Female");
	}
}

void CRanManagerCharEdit::GetGuild (int nGuNum)
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	_snprintf( szTemp, 1024, "SELECT GuNum,GuName "
							"FROM %s.dbo.GuildInfo WHERE GuNum=%d",CToolCfg::GetInstance()->szGameDb,nGuNum );

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharEdit.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLINTEGER nGuildNum = 0, cbGuNum=SQL_NTS;
	SQLCHAR    szGuName[CHAR_SZNAME+1] = {0}; SQLINTEGER cbGuName = SQL_NTS;

	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	break;

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{		
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nGuildNum,       0, &cbGuNum);
            ::SQLGetData(hStmt, 2, SQL_C_CHAR, szGuName   ,  CHR_ID_LENGTH+1, &cbGuName); 
           
			SetWin_Num_int(this,IDC_EDIT_CHAGUILDNUM,nGuildNum);
			SetWin_Text(this,IDC_EDIT_CHAGUILDNAME,(const char*) szGuName);
			break;
		}
		else
		{
			SetWin_Num_int(this,IDC_EDIT_CHAGUILDNUM,nGuNum);
			SetWin_Text(this,IDC_EDIT_CHAGUILDNAME,"None");
			break;
		}
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	

}

void CRanManagerCharEdit::OnBnClickedButtonChareditSave()
{
	char szNick[CHAR_SZNAME] = {0};
	char szName[CHAR_SZNAME] = {0}; 
	StringCchCopy(szName, CHAR_SZNAME, GetWin_Text(this,IDC_EDIT_CHANAME).GetString() );
	StringCchCopy(szNick, CHAR_SZNAME, GetWin_Text(this,IDC_EDIT_CHAGUNAME).GetString() );

	LONGLONG	llMoney = _strtoi64 ( GetWin_Text(this,IDC_EDIT_CHAMONEY),NULL,10 );
	LONGLONG	llExp = _strtoi64 ( GetWin_Text(this,IDC_EDIT_CHAEXP),NULL,10  );
	LONGLONG	llReExp = _strtoi64 ( GetWin_Text(this,IDC_EDIT_CHAREEXP),NULL,10  );
	int	nSchool = GetWin_Combo_Sel(this,IDC_COMBO_EMSCHOOL);
	SNATIVEID	sStartMap;
	sStartMap.wMainID = GetWin_Num_int(this,IDC_EDIT_SM_MID);
	sStartMap.wSubID = GetWin_Num_int(this,IDC_EDIT_SM_SID);
	SNATIVEID	sSaveMap;
	sSaveMap.wMainID = GetWin_Num_int(this,IDC_EDIT_SAVE_MID);
	sSaveMap.wSubID = GetWin_Num_int(this,IDC_EDIT_SAVE_SID);
	SNATIVEID	sCallMap;
	sCallMap.wMainID = GetWin_Num_int(this,IDC_EDIT_RET_MID);
	sCallMap.wSubID = GetWin_Num_int(this,IDC_EDIT_RET_SID);

	EMTRIBE	emTribe = (EMTRIBE)GetWin_Combo_Sel(this,IDC_COMBO_EMTRIBE);
	EMCHARINDEX emIndex = (EMCHARINDEX)GetWin_Combo_Sel(this,IDC_COMBO_EMCLASS);
	EMCHARCLASS	emClass = CharIndexToClass(emIndex);

	int nSex;
	if ( emIndex == GLCI_FIGHTER_M || emIndex == GLCI_ARMS_M || emIndex == GLCI_EXTREME_M || emIndex == GLCI_ARCHER_M ||
		emIndex == GLCI_SPIRIT_M || emIndex == GLCI_SCIENCE_M || emIndex == GLCI_ASSASSIN_M)
	{
		nSex =1;
	}
	else if ( emIndex == GLCI_FIGHTER_W || emIndex == GLCI_ARMS_W || emIndex == GLCI_EXTREME_W || emIndex == GLCI_ARCHER_W ||
			emIndex == GLCI_SPIRIT_W || emIndex == GLCI_SCIENCE_W || emIndex == GLCI_ASSASSIN_W )
	{
		nSex =0;
	}

	/*CString strChaCreateDate;
	strChaCreateDate.Format("%d/%d/%d %d:%d:%d"
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_2 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_1 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_3 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_4 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_5 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_6 )
		);

	CString strChaDeletedDate;
	strChaDeletedDate.Format("%d/%d/%d %d:%d:%d"
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_2 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_1 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_3 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_4 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_5 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_6 )
		);

	CString strChaGuSecede;
	strChaGuSecede.Format("%d/%d/%d %d:%d:%d"
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_2 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_1 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_3 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_4 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_5 )
		,GetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_6 )
		);*/

	/*DWORD	dwFlags;
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_G_INVITE ),dwFlags, EMCLUB_SUBMATER_JOIN );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_G_KICK ),dwFlags, EMCLUB_SUBMATER_KICK );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_G_NOTICE ),dwFlags, EMCLUB_SUBMATER_NOTICE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_G_VERIFY ),dwFlags, EMCLUB_SUBMATER_CD );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_G_BADGE ),dwFlags, EMCLUB_SUBMATER_MARK );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_G_CDM ),dwFlags, EMCLUB_SUBMATER_CDM );*/

	int	nStatus = GetWin_Combo_Sel(this,IDC_COMBO_CHARSTATUS);

	//"ChaDeleted, GuPosition, ChaCreateDate, ChaDeletedDate, ChaGuSecede "

	TCHAR szTemp[2048] = {0};
	_snprintf( szTemp, 2048, "UPDATE %s.dbo.ChaInfo SET ChaBright=%d, ChaLevel=%u, ChaMoney=%I64d, "
				"ChaDex=%u, ChaIntel=%u, ChaSchool=%u, ChaHair=%u, ChaFace=%u, "
				"ChaLiving=%d, ChaStrong=%u, ChaPower=%u, ChaSpirit=%u, ChaStrength=%u, "
				"ChaStRemain=%u, ChaAttackP=%u, ChaDefenseP=%u, ChaFightA=%u, ChaShootA=%u, "
				"ChaExp=%I64d, ChaSkillPoint=%u, ChaHP=%u, ChaMP=%u, ChaSP=%u, ChaPK=%u, "
				"ChaStartMap=%u, ChaStartGate=%u, ChaPosX=%f, ChaPosY=%f, ChaPosZ=%f, "
				"ChaSaveMap=%d, ChaSavePosX=%f, ChaSavePosY=%f, ChaSavePosZ=%f, ChaReturnMap=%d, "
				"ChaReturnPosX=%f, ChaReturnPosY=%f, ChaReturnPosZ=%f, ChaGuName='%s', ChaReExp=%I64d, "
				"ChaSpMID = %u, ChaSpSID = %u, ChaReborn = %u, "
				"ChaCP=%u , ChaPkWin = %u, ChaPkLoss = %u, ChaName='%s' ,ChaTribe=%d, "
				"ChaClass=%d, SGNum=%u, ChaInvenLine=%u, GuNum=%u, ChaSex=%u, ChaHairColor=%u, "
				"ChaDeleted=%d"
				"WHERE ChaNum=%u", 
	CToolCfg::GetInstance()->szGameDb,
	GetWin_Num_int(this,IDC_EDIT_BP), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_LEVEL), 
	llMoney, 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_DEX), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_INTEL), 
	(DWORD)nSchool, 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_HAIR),  
	(DWORD)GetWin_Num_int(this,IDC_EDIT_FACE),  
	GetWin_Num_int(this,IDC_EDIT_LP), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_STRONG), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_POWER), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_SPIRIT), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_STRENGTH), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_STATSP), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_ATTACK_P), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_DEFENSE_P), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_FIGHT_A), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_SHOOT_A), 
	llExp, 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_SKILLP), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_CHAHP), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_CHAMP), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_CHASP), 
	(DWORD)GetWin_Num_int(this,IDC_EDIT_CHAPK),  
	(DWORD)sStartMap.dwID,
	(DWORD)GetWin_Num_int(this,IDC_EDIT_SM_GATEID),  
	GetWin_Num_float(this,IDC_EDIT_SM_POSX),   
	GetWin_Num_float(this,IDC_EDIT_SM_POSY), 
	GetWin_Num_float(this,IDC_EDIT_SM_POSZ), 
	(int)sSaveMap.dwID, 
	GetWin_Num_float(this,IDC_EDIT_SAVE_POSX),
	GetWin_Num_float(this,IDC_EDIT_SAVE_POSY),
	GetWin_Num_float(this,IDC_EDIT_SAVE_POSZ), 
	(int)sCallMap.dwID, 
	GetWin_Num_float(this,IDC_EDIT_RET_POSX),
	GetWin_Num_float(this,IDC_EDIT_RET_POSY), 
	GetWin_Num_float(this,IDC_EDIT_RET_POSZ),
	szNick,
	llReExp,
	(DWORD)GetWin_Num_int(this,IDC_EDIT_SP_MID),
	(DWORD)GetWin_Num_int(this,IDC_EDIT_SP_SID),
	(DWORD)GetWin_Num_int(this,IDC_EDIT_REBORN),
	(DWORD)GetWin_Num_int(this,IDC_EDIT_CHACP),
	(DWORD)GetWin_Num_int(this,IDC_EDIT_CHAPKWIN),
	(DWORD)GetWin_Num_int(this,IDC_EDIT_CHAPKLOSS),
	szName,
	(int)emTribe,
	(int)emClass,
	(DWORD)GetWin_Num_int(this,IDC_EDIT_SGNUM),
	(DWORD)GetWin_Num_int(this,IDC_EDIT_INVENLINE),
	(DWORD)GetWin_Num_int(this,IDC_EDIT_CHAGUILDNUM),
	(DWORD)nSex,
	(DWORD)GetWin_Num_int(this,IDC_EDIT_HAIRCOLOR),
	nStatus,
	 
	//dwFlags,
	//strChaCreateDate.GetString(),
	//strChaDeletedDate.GetString(),
	//strChaGuSecede.GetString(),

	(DWORD)GetWin_Num_int(this,IDC_EDIT_CHARID)
	);
		
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharEdit.txt","%s--%s",strTIME.c_str(),szTemp);

	if (sReturn == SQL_ERROR )	MessageBox("Error! Saving Char Data :-(","Ran Manager",MB_OK);
	else MessageBox("Success! Saving Char Data :-)","Ran Manager",MB_OK);

	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerCharEdit::OnBnClickedButtonChareditCalcel()
{
	m_pToolTab->ActivePage(CHARPAGE_MAIN,0);
}

void CRanManagerCharEdit::OnBnClickedButtonCheckname()
{
	SQLRETURN	sReturn = 0; // SQL return value (short)	
	SQLHSTMT	hStmt; // Handle of statement (void*)

	sReturn = ::SQLAllocHandle(SQL_HANDLE_STMT, COdbc::GetInstance()->ConnectGame(), &hStmt);
	if (sReturn != SQL_SUCCESS && sReturn != SQL_SUCCESS_WITH_INFO)	return;	

	TCHAR szTemp[1024] = {0};
	std::string strSign = "'";
	_snprintf( szTemp, 1024, "SELECT UserNum,ChaName "
							"FROM %s.dbo.ChaInfo WHERE ChaName=%s%s%s",CToolCfg::GetInstance()->szGameDb,strSign.c_str(),GetWin_Text(this,IDC_EDIT_CHANAME).GetString(),strSign.c_str());

	sReturn = ::SQLExecDirect(hStmt,(SQLCHAR*) szTemp,SQL_NTS);

	std::string strTIME = CDebugSet::GetCurTime ();
	LOGSCRIPT::LogToFile("CharEdit.txt","%s--%s",strTIME.c_str(),szTemp);

	if ((sReturn != SQL_SUCCESS) && (sReturn != SQL_SUCCESS_WITH_INFO))	
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		return;
	}

	SQLCHAR    szChaName[CHR_ID_LENGTH+1] = {0}; SQLINTEGER cbChaName = SQL_NTS; 
    SQLINTEGER nUserNum = 0, cbUserNum=SQL_NTS;
	
	while (true)
	{
		sReturn = ::SQLFetch(hStmt);
		if (sReturn == SQL_ERROR || sReturn == SQL_SUCCESS_WITH_INFO)	
		{
			break;
		}

		if (sReturn == SQL_SUCCESS || sReturn == SQL_SUCCESS_WITH_INFO)
		{		
			::SQLGetData(hStmt, 1, SQL_C_LONG, &nUserNum,       0, &cbUserNum);
            ::SQLGetData(hStmt, 2, SQL_C_CHAR, szChaName   ,  CHR_ID_LENGTH+1, &cbChaName); 
            
			CString strTemp;
			strTemp.Format("Character Name: %s Exist",(const char*) szChaName);
			MessageBox(strTemp,"Info",MB_OK);
			break;
		}
		else
		{
			MessageBox("Character Name Dont Exist","Info",MB_OK);
			break;
		}
		Sleep( 0 );
	}
	::SQLFreeHandle(SQL_HANDLE_STMT, hStmt);	
}

void CRanManagerCharEdit::OnBnClickedButtonRemoveguild()
{
	SetWin_Num_int(this,IDC_EDIT_CHAGUILDNUM,0);
	SetWin_Text(this,IDC_EDIT_CHAGUILDNAME,"None");
}

void CRanManagerCharEdit::OnBnClickedButtonTransferguild()
{
	CGuildSearch	sGuildSearch;
	if ( IDOK == sGuildSearch.DoModal() )
	{
		GetGuild (sGuildSearch.nSelectedGuild);
	}
}

void CRanManagerCharEdit::OnBnClickedButtonMapeditStart()
{
	CMapSearch	sMapSearch;
	if ( IDOK == sMapSearch.DoModal() )
	{
		SNATIVEID	sStartMapID;
		sStartMapID.wMainID = sMapSearch.nSelectMID;
		sStartMapID.wSubID = sMapSearch.nSelectSID;
		SetWin_Num_int(this,IDC_EDIT_SM_MID,sStartMapID.wMainID);
		SetWin_Num_int(this,IDC_EDIT_SM_SID,sStartMapID.wSubID);	
		CString strMap;
		SMAPNODE* pNODE(NULL);
		pNODE = m_sMapList.FindMapNode ( sStartMapID );
		if ( pNODE )	strMap = pNODE->strMapName.c_str();
		SetWin_Text(this,IDC_EDIT_SM_MAPNAME,strMap.GetString());
	}
}

void CRanManagerCharEdit::OnBnClickedButtonMapeditSave()
{
	CMapSearch	sMapSearch;
	if ( IDOK == sMapSearch.DoModal() )
	{
		SNATIVEID	sSaveMapID;
		sSaveMapID.wMainID = sMapSearch.nSelectMID;
		sSaveMapID.wSubID = sMapSearch.nSelectSID;
		SetWin_Num_int(this,IDC_EDIT_SAVE_MID,sSaveMapID.wMainID);
		SetWin_Num_int(this,IDC_EDIT_SAVE_SID,sSaveMapID.wSubID);	
		CString strMap;
		SMAPNODE* pNODE(NULL);
		pNODE = m_sMapList.FindMapNode ( sSaveMapID );
		if ( pNODE )	strMap = pNODE->strMapName.c_str();
		SetWin_Text(this,IDC_EDIT_SAVE_MAPNAME,strMap.GetString());
	}
}

void CRanManagerCharEdit::OnBnClickedButtonMapeditRet()
{
	CMapSearch	sMapSearch;
	if ( IDOK == sMapSearch.DoModal() )
	{
		SNATIVEID	sReturnMapID;
		sReturnMapID.wMainID = sMapSearch.nSelectMID;
		sReturnMapID.wSubID = sMapSearch.nSelectSID;
		SetWin_Num_int(this,IDC_EDIT_RET_MID,sReturnMapID.wMainID);
		SetWin_Num_int(this,IDC_EDIT_RET_SID,sReturnMapID.wSubID);	
		CString strMap;
		SMAPNODE* pNODE(NULL);
		pNODE = m_sMapList.FindMapNode ( sReturnMapID );
		if ( pNODE )	strMap = pNODE->strMapName.c_str();
		SetWin_Text(this,IDC_EDIT_RET_MAPNAME,strMap.GetString());
	}
}

void CRanManagerCharEdit::OnBnClickedButtonSpChange()
{
	CItemSearch sItemSearch;
	sItemSearch.SetMultiple(false);
	sItemSearch.SetFilter(SEARCH_FILTER_POTS);
	if ( IDOK == sItemSearch.DoModal () )
	{
		SITEM*	pItemCheck = GLItemMan::GetInstance().GetItem(sItemSearch.sSelectedItem);
		if ( pItemCheck )
		{
			SetWin_Num_int ( this, IDC_EDIT_SP_MID,sItemSearch.sSelectedItem.wMainID);
			SetWin_Num_int ( this, IDC_EDIT_SP_SID,sItemSearch.sSelectedItem.wSubID);
			SetWin_Text( this,IDC_EDIT_SP_NAME,pItemCheck->GetName() );
		}
	}
}

void CRanManagerCharEdit::OnBnClickedButtonSetC1()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay =		GetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_1 );
	sNewTime.wMonth =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_2 );
	sNewTime.wYear =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_3 );
	sNewTime.wHour =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_4 );
	sNewTime.wMinute =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_5 );
	sNewTime.wSecond =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerCharEdit::OnBnClickedButtonSetC2()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay =		GetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_1 );
	sNewTime.wMonth =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_2 );
	sNewTime.wYear =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_3 );
	sNewTime.wHour =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_4 );
	sNewTime.wMinute =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_5 );
	sNewTime.wSecond =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerCharEdit::OnBnClickedButtonSetC3()
{
	CCalendar sCalender;
	SYSTEMTIME sNewTime;
	sNewTime.wDay =		GetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_1 );
	sNewTime.wMonth =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_2 );
	sNewTime.wYear =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_3 );
	sNewTime.wHour =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_4 );
	sNewTime.wMinute =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_5 );
	sNewTime.wSecond =	GetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_6 );
	sCalender.SetTime(sNewTime);

	if ( IDOK == sCalender.DoModal () )
	{
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_1,sCalender.GetTime().wDay);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_2,sCalender.GetTime().wMonth);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_3,sCalender.GetTime().wYear);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_4,sCalender.GetTime().wHour);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_5,sCalender.GetTime().wMinute);
		SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_6,sCalender.GetTime().wSecond);
	}
}

void CRanManagerCharEdit::OnBnClickedButtonResetC1()
{
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_1,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_2,2);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_4,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_5,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C1_6,1);
}

void CRanManagerCharEdit::OnBnClickedButtonResetC2()
{
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_1,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_2,2);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_4,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_5,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C2_6,1);
}

void CRanManagerCharEdit::OnBnClickedButtonResetC3()
{
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_1,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_2,2);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_3,1970);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_4,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_5,1);
	SetWin_Num_int ( this, IDC_EDIT_LOCKER_C3_6,1);
}
