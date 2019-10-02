#include "stdafx.h"
#include "./GLChar.h"
#include "./GLCharData.h"
#include "./GLGaeaServer.h"
#include "./GLSchoolFreePK.h"
#include "GLClubDeathMatch.h"
//crashfix
//#include "GLGaeaClient.h"
#include "GLSchoolWars.h"
#include "GLRoyalRumble.h"
#include "GLTowerWars/GLTowerWars.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BOX_R	(4)

GLChar::GLChar () :
	m_wTARNUM(0),

	m_dwANISUBSELECT(0),

	m_dwActState(NULL),
	m_Action(GLAT_IDLE),

	m_fIdleTime(0.0f),
	m_fMBR_TIMER(0.0f),
	m_fSTATE_TIMER(0.0f),
	m_fPERIOD_TIMER(0.0f),
	m_fQUEST_TIMER(60.0f),
	m_fITEM_TIMER(0.0f),
	m_fSAVEDB_TIMER(0.0f),
	m_fattTIMER(0.0f),
	m_fMoveDelay(0.0f),
	m_fBRIGHT_TIMER(0.0f),

	m_sAssault(CROW_PC,GAEAID_NULL),
	m_lnLastSendExp(0),

	m_lnLastSendVNExp(0),

	m_dwViewFrame(0),
	m_fAge(0.0f),
	m_fGenAge(0.0f),
	m_nDECEXP(0),
	m_vPos(0,0,0),
	
	m_dwClientID(0),
	m_dwGaeaID(0),
	m_dwPartyID(PARTY_NULL),

	m_dwCeID(0),

	m_wHealingNum(0),

	m_pLandMan(NULL),
	
	m_pGaeaNode(NULL),
	m_pLandNode(NULL),

	m_pQuadNode(NULL),
	m_pCellNode(NULL),

	m_SKILLMTYPE(AN_SKILL),
	m_SKILLSTYPE(AN_SUB_00),

	m_bUsedStorageCard(false),

	m_bNon_Rebirth(false),

	m_fSkillDelay(0.0f),

	m_dwPetGUID(UINT_MAX),
	m_dwPetID(0),

	m_dwSummonGUID(UINT_MAX),
	m_dwSummonID(0),

	m_bEntryFailed(FALSE),


	m_bProtectPutOnItem(false),
	m_bGetPetFromDB(false),
	m_bGetVehicleFromDB ( false ),
	m_fVehicleTimer( 0.0f ),
    bCheckMixMaterial( FALSE ),
	m_ItemRemodelPosX(EM_INVENSIZE_X),
	m_ItemRemodelPosY(EM_INVENSIZE_Y),
	m_ItemGarbagePosX(EM_INVENSIZE_X),
	m_ItemGarbagePosY(EM_INVENSIZE_Y),

	m_ChinaGainType(255),
	m_dwVietnamGainType(GAINTYPE_MAX),

	m_bEventStart(FALSE),
	m_bEventApply(FALSE),
	m_hCheckStrDLL( NULL ),
	m_pCheckString( NULL ),

	m_pGLGaeaServer( NULL ),
	m_bItemShopOpen ( false ),
	m_bDefenseSkill ( false ),
	m_bUseRebuildCard( false )
{


	m_sSaveMapID = NATIVEID_NULL();
	m_ARoundSlot.SetChar ( this );


	m_China15Time = CTime::GetCurrentTime();
	DWORD nMaxClient = GLGaeaServer::GetInstance().GetMaxClient();

	GASSERT(nMaxClient);
	m_arrayFieldPC = new PSFIELDCROW[nMaxClient];

	memset ( m_arrayFieldPC, 0, sizeof(PSFIELDCROW)*nMaxClient );
	memset ( m_arrayFieldCROW, 0, sizeof(PSFIELDCROW)*MAXCROW );
	memset ( m_arrayFieldMATERIAL, 0, sizeof(PSFIELDCROW)*MAXCROW );
	memset ( m_arrayFieldITEM, 0, sizeof(PSFIELDCROW)*MAXITEM );
	memset ( m_arrayFieldMONEY, 0, sizeof(PSFIELDCROW)*MAXMONEY );

	//for( int i=0;i<3;i++)		m_wHeadCount[i]=0;

	m_setLandEffectNum.clear();


	// PET
	m_arrayFieldPET = new PSFIELDCROW[nMaxClient];
	memset ( m_arrayFieldPET, 0, sizeof(PSFIELDCROW)*nMaxClient );

	m_arrayFieldSummon = new PSFIELDCROW[nMaxClient];
	memset ( m_arrayFieldSummon, 0, sizeof(PSFIELDCROW)*nMaxClient );

	MGOddEvenInit();

/*#ifdef TH_PARAM
	HMODULE m_hCheckStrDLL = LoadLibrary("ThaiCheck.dll");

	if ( m_hCheckStrDLL )
	{
		m_pCheckString = ( BOOL (_stdcall*)(CString)) GetProcAddress(m_hCheckStrDLL, "IsCompleteThaiChar");
	}
#endif */
}

GLChar::~GLChar ()
{
	delete[] m_arrayFieldPC;

	// PET
	delete[] m_arrayFieldPET;


	// Summon
	delete[] m_arrayFieldSummon;

//#ifdef TH_PARAM
	if( m_hCheckStrDLL ) FreeLibrary( m_hCheckStrDLL );
//#endif
}

DWORD GLChar::GetBonusExp () const
{
	return GLCONST_CHAR::GETEXP_PC(m_wLevel);
}

void GLChar::RESET_DATA ()
{
	int i = 0;

	GLCHARLOGIC::RESET_DATA();

	m_actorMove.ResetMovedData();
	m_actorMove.Stop();
	m_actorMove.Release();

	m_vDir = D3DXVECTOR3(1,0,0);

	m_TargetID = STARGETID(CROW_PC,GAEAID_NULL);
	m_sNPCID   = STARGETID(CROW_PC,GAEAID_NULL);
	m_wTARNUM = 0;

	for ( i=0; i<EMTARGET_NET; ++i )
		m_sTARIDS[i] = STARID(CROW_PC,GAEAID_NULL);

	m_dwANISUBSELECT = 0;

	m_Action = GLAT_IDLE;
	m_dwActState = NULL;
	m_fIdleTime = 0.0f;
	m_fMBR_TIMER = 0.0f;
	m_fSTATE_TIMER = 0.0f;
	m_fPERIOD_TIMER = 0.0f;
	m_fQUEST_TIMER = 60.0f;	// √≥¿Ω «—?Eπ´¡∂∞« Ω««‡µ«∞‘ «œ?E¿ß«œø©

	m_fattTIMER = 0.0f;
	m_fBRIGHT_TIMER = 0.0f;

	m_fMoveDelay = 0.0f;
	m_sAssault = STARGETID(CROW_PC,GAEAID_NULL);

	m_ARoundSlot.Reset();

	m_cDamageLog.clear();

	m_dwThaiCCafeClass	= 0;
	// ∏ª∑π¿ÃΩ√æ∆ PC?E¿Ã∫•∆Æ
	m_nMyCCafeClass		= 0;

	m_bVietnamLevelUp = false;

	m_ChinaGainType    = 255;

	m_bTracingUser     = FALSE;

	m_dwVietnamGainType = GAINTYPE_MAX;

	m_bEventStart	   = FALSE;

	m_bEventApply	   = FALSE;

	m_sChinaTime.Init();
	m_sEventTime.Init();
	m_sVietnamSystem.Init();

	

	m_fAge = 0.0f;
	m_fGenAge = 0.0f;
	m_vPos = D3DXVECTOR3(0,0,0);

	m_dwClientID = 0;
	m_dwGaeaID = GAEAID_NULL;
	m_dwPartyID = PARTY_NULL;

	m_sMapID    = SNATIVEID(false);
	m_sOldMapID = SNATIVEID(false);
	m_dwCeID = 0;
	
	m_pLandMan = NULL;

	m_pGaeaNode = NULL;
	m_pLandNode = NULL;

	m_pQuadNode = NULL;
	m_pCellNode = NULL;

	m_sTrade.Reset();
	m_sPMarket.DoMarketClose();
	m_sCONFTING.RESET();

	m_sHITARRAY.clear();
	m_SKILLMTYPE = AN_SKILL;
	m_SKILLSTYPE = AN_SUB_00;

	m_bUsedStorageCard = false;

	m_bNon_Rebirth     = false;

	m_bGetPetFromDB    = false;

	m_dwPetGUID = UINT_MAX;
	m_dwPetID	= 0;

	m_dwSummonGUID = UINT_MAX;
	m_dwSummonID   = 0;

	m_bEntryFailed = FALSE;

	m_setLandEffectNum.clear();

	m_bProtectPutOnItem = false;

	m_China15Time = CTime::GetCurrentTime();

	MGOddEvenInit();

	m_sVehicle.RESET();
	m_bGetVehicleFromDB = false;
	m_fVehicleTimer = 0.0f;

	m_bItemShopOpen = false;
	m_bDefenseSkill = false;

	DWORD nMaxClient = GLGaeaServer::GetInstance().GetMaxClient();


	memset ( m_arrayFieldPC, 0, sizeof(PSFIELDCROW)*nMaxClient );
	memset ( m_arrayFieldCROW, 0, sizeof(PSFIELDCROW)*MAXCROW );
	memset ( m_arrayFieldMATERIAL, 0, sizeof(PSFIELDCROW)*MAXCROW );
	memset ( m_arrayFieldITEM, 0, sizeof(PSFIELDCROW)*MAXITEM );
	memset ( m_arrayFieldMONEY, 0, sizeof(PSFIELDCROW)*MAXMONEY );

	memset ( m_arrayFieldPET, 0, sizeof(PSFIELDCROW)*nMaxClient );
	memset ( m_arrayFieldSummon, 0, sizeof(PSFIELDCROW)*nMaxClient );
}

HRESULT GLChar::CreateChar( GLLandMan* pLandMan, D3DXVECTOR3 &vPos, PCHARDATA2 pCharData, LPDIRECT3DDEVICEQ pd3dDevice, BOOL bNEW )
{
	HRESULT hr;
	//*/*/*/*
	m_vPos = vPos;

	

	m_dwThaiCCafeClass = pCharData->m_dwThaiCCafeClass;
	// ∏ª∑π¿ÃΩ√æ∆ PC?E¿Ã∫•∆Æ
	m_nMyCCafeClass = pCharData->m_nMyCCafeClass;

	m_sChinaTime	   = pCharData->m_sChinaTime;
	m_sEventTime	   = pCharData->m_sEventTime;
	m_sVietnamSystem   = pCharData->m_sVietnamSystem;

	m_bTracingUser	   = pCharData->m_bTracingUser;

//	m_sEventState	   = m_pGLGaeaServer->m_sEventState;

	m_bEventStart = FALSE;
	m_bEventApply = FALSE;
	if( m_pGLGaeaServer->m_sEventState.bEventStart == TRUE )
	{
		// ¿Ã∫•∆Æ∞° ªı∑Œ Ω√¿€ µ 
		CTime	  crtTime     = CTime::GetCurrentTime();
		CTimeSpan crtGameSpan;
		CTime	  loginTime			 = m_sEventTime.loginTime;
		crtGameSpan					 = ( crtTime - loginTime );
		m_sEventTime.currentGameTime = crtGameSpan.GetTimeSpan();

		if( crtGameSpan.GetTotalSeconds() >= m_pGLGaeaServer->m_sEventState.EventPlayTime )
		{
			m_bEventStart = TRUE;
		}

		if( !(m_pGLGaeaServer->m_sEventState.MinEventLevel > pCharData->m_wLevel || 
			  m_pGLGaeaServer->m_sEventState.MaxEventLevel < pCharData->m_wLevel ) )
		{
			m_bEventApply = TRUE;
		}
	}


	hr = SetData ( pCharData, bNEW );
	if ( FAILED(hr) )	return E_FAIL;

	m_bEntryFailed = FALSE;
	// ¡÷ºÆµπ∑¡
	// ¡¯¿‘¡∂∞« ∞À?E
	if ( m_dwUserLvl < USER_GM3 )
	{
		if( pLandMan->GetMapID() != NATIVEID_NULL() )
		{
			const SLEVEL_REQUIRE* pLEVEL_REQUIRE = GLGaeaServer::GetInstance().GetLevelRequire(pLandMan->GetMapID().dwID);
			EMREQFAIL emReqFail(EMREQUIRE_COMPLETE);
			if( pLEVEL_REQUIRE ) 
			{
				emReqFail = pLEVEL_REQUIRE->ISCOMPLETE ( this );
			}else{
				TEXTCONSOLEMSG_WRITE( "[ERROR]Level Data Load failed! charID[%s] mapID[%d][%d] EMFail[%d]", m_szName, pLandMan->GetMapID().wMainID, pLandMan->GetMapID().wSubID, emReqFail );
			}
			if ( emReqFail != EMREQUIRE_COMPLETE )
			{
				TEXTCONSOLEMSG_WRITE( "[INFO]Entry failed! charID[%s] mapID[%d][%d] EMFail[%d]", m_szName, pLandMan->GetMapID().wMainID, pLandMan->GetMapID().wSubID, emReqFail );
				m_bEntryFailed = TRUE;
			}
		}else{
			TEXTCONSOLEMSG_WRITE( "[ERROR]Land ID is NATIVEID NULL! charID[%s]", m_szName );
		}
	}


	m_setLandEffectNum.clear();
	


	hr = SetNavi ( pLandMan->GetNavi(), m_vPos );
	if ( FAILED(hr) )	return E_FAIL;

	m_lnLastSendExp = m_sExperience.lnNow;

	m_lnLastSendVNExp = m_lVNGainSysExp;

	m_bServerStorage = TRUE;	

	DWORD Num1 = m_cInventory.GetNumItems();
	DWORD Num2 = m_cVietnamInventory.GetNumItems ();

	m_fMoveDelay = 0.0f;
	CTime cTIME_CUR = CTime::GetCurrentTime();

	//	Note : √¢∞˙‹« ¿Ø»øº∫ ∞À?E
	//
	for ( WORD i=0; i<EMSTORAGE_CHANNEL_SPAN_SIZE; ++i )
	{
		CTime cSTORAGE(m_tSTORAGE[i]);

		bool bVALID(true);
		if ( m_tSTORAGE[i]==0 || cSTORAGE<cTIME_CUR )	bVALID = false;
		
		m_bSTORAGE[i] = bVALID;
	}

	//	Note : «¡∏ÆπÃ?Eø©∫Œ ∞À?E
	//
	bool bPREMIUM(true);
	CTime tPREMIUM(m_tPREMIUM);
	if ( m_tPREMIUM==0 || tPREMIUM<cTIME_CUR )	bPREMIUM = false;
	m_bPREMIUM = bPREMIUM;

	m_cInventory.SetAddLine ( GetOnINVENLINE(), true );
	// ∫£∆Æ≥≤ ¿Œ∫•≈‰∏Æ¥¬ ºº∑Œ∞° 10ƒ≠¿Ãπ«∑Œ 6ƒ≠¿ª ?E√ﬂ∞°«—¥Ÿ.
#if defined(VN_PARAM) //vietnamtest%%%
	m_cVietnamInventory.SetAddLine ( 6, true );
#endif


	//DoQuestCheckLeaveMap();


	SetSTATE(EM_ACT_WAITING);

	


	return S_OK;
}

HRESULT GLChar::SetNavi ( NavigationMesh* pNavi, D3DXVECTOR3 &vPos )
{
	m_vPos = vPos;
	if ( m_actorMove.PathIsActive() )		m_actorMove.Stop();

	m_actorMove.Create ( pNavi, vPos, -1 );
	m_actorMove.SetMaxSpeed ( GLCONST_CHAR::cCONSTCLASS[m_CHARINDEX].fWALKVELO );

	return S_OK;
}

HRESULT GLChar::SetData ( PCHARDATA2 pCharData, BOOL bNEW )
{
	SCHARDATA2::Assign ( *pCharData );
	
	if ( !GLCHARLOGIC::INIT_DATA(bNEW,TRUE) )	return E_FAIL;

	return S_OK;
}

HRESULT GLChar::SavePosition ()
{
	//	Note : ¡◊¿∫ªÛ≈¬¿œ ∂ß¥¬ «ˆ¡¶ ∆˜¡ˆº«¿ª ¿˙¿Â«œ?Eæ ¥¬¥Ÿ.
	//
	if ( IsDie() )
	{
		m_sSaveMapID = NATIVEID_NULL();
	}
	//	Note : «ˆ¡¶ ¿ßƒ° ¿˙?E
	//
	else
	{
		m_sSaveMapID = m_sMapID;
		m_vSavePos = m_vPos;
	}

	return S_OK;
}

//	Note : ¡˜?E¿ßƒ°∏¶ ¿˙?E
//
HRESULT GLChar::SaveLastCall ()
{
	if ( !m_pLandMan )	return S_FALSE;

	//	Note : ∏∏æ‡ º±µµ ≈¨∑¥¿¸øÎ ∏„¿œ ∞ÊøÏ ¡˜¿¸ ¿ßƒ°∏¶ ¿˙¿Â«œ¡ˆ æ ¿Ω.
	if ( !m_pLandMan->m_bGuidBattleMap && !m_pLandMan->m_bClubDeathMatchMap && !m_pLandMan->m_bSchoolWarsMap && !m_pLandMan->m_bRoyalRumbleMap && !m_pLandMan->m_bTowerWarsMap )
	{
		m_sLastCallMapID = m_sMapID;
		m_vLastCallPos = m_vPos;

		GLMSG::SNETPC_UPDATE_LASTCALL NetMsg;
		NetMsg.sLastCallMapID = m_sLastCallMapID;
		NetMsg.vLastCallPos = m_vLastCallPos;
		m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsg );
	}

	return S_OK;
}

HRESULT GLChar::LoadStorageFromDB ()
{
	if ( m_bServerStorage )	return S_OK;

	GLDBMan* pDBMan = m_pGLGaeaServer->GetDBMan();
	if ( pDBMan )	pDBMan->ReadUserInven ( &GetCharData2() );
	m_bServerStorage = TRUE;

	return S_OK;
}

HRESULT GLChar::SetPosition ( D3DXVECTOR3 &vPos )
{
	m_actorMove.SetPosition ( vPos, -1 );
	if ( m_actorMove.PathIsActive() )		m_actorMove.Stop();

	m_vPos = m_actorMove.Position();

	return S_OK;
}

BOOL GLChar::IsValidBody () const
{
	if ( IsSTATE(EM_ACT_DIE) )			return FALSE;
	if ( IsSTATE(EM_ACT_WAITING) )		return FALSE;
	if ( IsSTATE(EM_REQ_LOGOUT) )		return FALSE;

	return ( m_Action < GLAT_FALLING );
}

BOOL GLChar::IsDie () const
{
	if ( !IsSTATE(EM_ACT_WAITING) )
	{
		if ( m_Action==GLAT_DIE )		return TRUE;
		if ( IsSTATE(EM_ACT_DIE) )		return TRUE;
	}

	return FALSE;
}

BOOL GLChar::IsVisibleDetect ( const BOOL bRECVISIBLE )
{
	if ( IsSTATE(EM_REQ_VISIBLENONE) || IsSTATE(EM_REQ_VISIBLEOFF) )	return FALSE;

	if ( m_bINVISIBLE && !bRECVISIBLE )									return FALSE;

	return TRUE;
}

BOOL GLChar::IsVaildTradeData ()
{
	//	±›æ◊ ¿Ø»øº∫ ∞À?E
	if ( m_lnMoney < m_sTrade.GetMoney() )		return FALSE;

	GLInventory &sTradeBox = m_sTrade.GetTradeBox();
	GLInventory::CELL_MAP* pItemList = sTradeBox.GetItemList();

	GLInventory::CELL_MAP_ITER iter = pItemList->begin();
	GLInventory::CELL_MAP_ITER iter_end = pItemList->end();
	for ( ; iter!=iter_end; ++iter )
	{
		SINVENITEM* pTradeItem = (*iter).second;
		SINVENITEM* pInvenItem = m_cInventory.GetItem ( pTradeItem->wBackX, pTradeItem->wBackY );
		if ( !pInvenItem )														return FALSE;

		if ( memcmp ( &pTradeItem->sItemCustom, &pInvenItem->sItemCustom, sizeof(SITEMCUSTOM) ) )	return FALSE;
	}

	return TRUE;
}

BOOL GLChar::IsVaildTradeInvenSpace ( GLInventory &sTradeBoxTar )
{
	GLInventory sInvenTemp;
	sInvenTemp.SetAddLine ( m_cInventory.GETAddLine(), true );
	sInvenTemp.Assign ( m_cInventory );

	//	Note : ¿⁄Ω≈¿« ±≥»Ø ∏Ò∑œø° ø√∂Û∞£ æ∆¿Ã≈€¿ª ¿Œ?E°º?¡¶ø‹.
	//
	GLInventory &sTradeBoxMy = m_sTrade.GetTradeBox();
	GLInventory::CELL_MAP* pItemListMy = sTradeBoxMy.GetItemList();

	GLInventory::CELL_MAP_ITER iter = pItemListMy->begin();
	GLInventory::CELL_MAP_ITER iter_end = pItemListMy->end();
	for ( ; iter!=iter_end; ++iter )
	{
		SINVENITEM* pTradeItem = (*iter).second;

		BOOL bOk = sInvenTemp.DeleteItem ( pTradeItem->wBackX, pTradeItem->wBackY );
		if ( !bOk )		return FALSE;
	}

	//	Note : ªÛ?EÊ¿?±≥»Ø π∞«∞¿Ã µÈ?E∞•?E¿÷¥¬?E∞À?E
	//
	GLInventory::CELL_MAP* pItemListTar = sTradeBoxTar.GetItemList();

	iter = pItemListTar->begin();
	iter_end = pItemListTar->end();
	for ( ; iter!=iter_end; ++iter )
	{
		SINVENITEM* pTradeItem = (*iter).second;

		SITEM *pItem = GLItemMan::GetInstance().GetItem ( pTradeItem->sItemCustom.sNativeID );
		if ( !pItem )	return FALSE;

		WORD wPosX = 0, wPosY = 0;
		BOOL bOk = sInvenTemp.FindInsrtable ( pItem->sBasicOp.wInvenSizeX, pItem->sBasicOp.wInvenSizeY, wPosX, wPosY );
		if ( !bOk )		return FALSE;

		bOk = sInvenTemp.InsertItem ( pTradeItem->sItemCustom, wPosX, wPosY );
		if ( !bOk )		return FALSE;
	}
	
	return TRUE;
}

BOOL GLChar::DoTrade ( GLTrade &sTrade, DWORD dwFromCharID )
{
	//	Note : ¡Ÿ ±›æ◊.
	//
	LONGLONG lnMoneyOut = m_sTrade.GetMoney();
	if ( m_lnMoney < lnMoneyOut ) return FALSE;
	CheckMoneyUpdate( m_lnMoney, lnMoneyOut, FALSE, "Do Trade Out Money." );
	m_lnMoney -= lnMoneyOut;	

	//	Note : πﬁ¿ª ±›æ◊.
	//
	LONGLONG lnMoneyIn = sTrade.GetMoney();
	CheckMoneyUpdate( m_lnMoney, lnMoneyIn, TRUE, "Do Trade In Money." );
	m_lnMoney += lnMoneyIn;

	m_bMoneyUpdate = TRUE;

	//	Note : ±›æ◊ ∑Œ±◊.
	//
	LONGLONG lnMoneyDx = (lnMoneyIn-lnMoneyOut);
	if ( lnMoneyDx!=0 )
	{
		GLITEMLMT::GetInstance().ReqMoneyExc ( ID_CHAR, dwFromCharID, ID_CHAR, m_dwCharID, lnMoneyDx, EMITEM_ROUTE_CHAR );
		GLITEMLMT::GetInstance().ReqMoneyExc ( ID_CHAR, m_dwCharID, ID_CHAR, 0, m_lnMoney, EMITEM_ROUTE_CHAR );
	}

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
	if ( m_bTracingUser )
	{
		NET_LOG_UPDATE_TRACINGCHAR TracingMsg;
		TracingMsg.nUserNum  = GetUserID();
		StringCchCopy( TracingMsg.szAccount, USR_ID_LENGTH+1, m_szUID );

		CString strTemp;
		PGLCHAR pFromChar = m_pGLGaeaServer->GetCharID( dwFromCharID );
		if ( pFromChar != NULL )
		{
			strTemp.Format( "Do Trade! From, [%s][%s], Target[%s][%s], RecvMoney:[%I64d], SendMoney:[%I64d], HaveMoney:[%I64d], Target HaveMoney:[%I64d]",
					 m_szUID, m_szName, pFromChar->m_szUID, pFromChar->m_szName, lnMoneyIn, lnMoneyOut, m_lnMoney, pFromChar->m_lnMoney );
		}else{
			strTemp.Format( "Do Trade! From, [%s][%s], Target Not Found, RecvMoney:[%I64d], SendMoney:[%I64d], HaveMoney:[%I64d]",
					 m_szUID, m_szName, lnMoneyIn, lnMoneyOut, m_lnMoney );
		}

		StringCchCopy( TracingMsg.szLogMsg, TRACING_LOG_SIZE, strTemp.GetString() );

		m_pGLGaeaServer->SENDTOAGENT( m_dwClientID, &TracingMsg );
	}
#endif

	//	Note : ±›æ◊ ∫Ø»≠ ≈¨∂Û¿Ãæ∆Æø° æÀ∏≤.
	//
	GLMSG::SNETPC_UPDATE_MONEY NetMsgMoney;
	NetMsgMoney.lnMoney = m_lnMoney;
	//add money 2
	NetMsgMoney.lnVoteP = m_lnVoteP;
	//add money 3
	NetMsgMoney.lnPremP = m_lnPremP;
	//add contributionpoints by CNDev
	NetMsgMoney.lnContribP = m_lnContribP;
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgMoney );


	//	Note : ¿⁄Ω≈¿« ±≥»Ø ∏Ò∑œø° ø√∂Û∞£ æ∆¿Ã≈€¿ª ¿Œ?E°º?¡¶ø‹.
	//
	GLInventory &sTradeBoxMy = m_sTrade.GetTradeBox();
	GLInventory::CELL_MAP* pItemListMy = sTradeBoxMy.GetItemList();
	
	SINVENITEM* pTradeItem = NULL;
	BOOL bOk = FALSE;
	GLMSG::SNETPC_INVEN_DELETE NetMsgDelete;
	GLInventory::CELL_MAP_ITER iter = pItemListMy->begin();
	GLInventory::CELL_MAP_ITER iter_end = pItemListMy->end();
	for ( ; iter!=iter_end; ++iter )
	{
		pTradeItem = (*iter).second;

		bOk = m_cInventory.DeleteItem ( pTradeItem->wBackX, pTradeItem->wBackY );
		if ( !bOk )
		{
			return FALSE;
		}
		else
		{
			//	Note : æ∆¿Ã≈€ ∫Ø»≠∏¶ ≈¨∂Û¿Ãæ∆Æø° æÀ∏≤.
			//			
			NetMsgDelete.wPosX = pTradeItem->wBackX;
			NetMsgDelete.wPosY = pTradeItem->wBackY;
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgDelete );
		}
	}

	//	Note : ªÛ?EÊ¿?¡÷¥¬ π∞«∞¿ª ¿Œ?E?≥÷¿Ω.
	//
	GLInventory::CELL_MAP* pItemListTar = sTrade.GetTradeBox().GetItemList();

	pTradeItem = NULL;
	SITEM* pItem = NULL;
	WORD wPosX = 0, wPosY = 0;

	SINVENITEM* pInvenItem = NULL;
	GLMSG::SNETPC_INVEN_INSERT NetMsgInert;

	iter = pItemListTar->begin();
	iter_end = pItemListTar->end();	
	for ( ; iter!=iter_end; ++iter )
	{
		pTradeItem = (*iter).second;
		pItem = GLItemMan::GetInstance().GetItem ( pTradeItem->sItemCustom.sNativeID );
		if ( !pItem )	return FALSE;

		wPosX = 0;
		wPosY = 0;
		bOk = m_cInventory.FindInsrtable ( pItem->sBasicOp.wInvenSizeX, pItem->sBasicOp.wInvenSizeY, wPosX, wPosY );
		if ( !bOk )		return FALSE;

		bOk = m_cInventory.InsertItem ( pTradeItem->sItemCustom, wPosX, wPosY );
		if ( !bOk )		return FALSE;


/*
		// »πµÊ«— æ∆¿Ã≈€¿Ã ∆÷ƒ´?E&& ª˝º∫µ» ∆÷¿Ã∂Û?Eº“¿Ø±«¿ª ¿Ã?E—¥?
		// ∆÷æ∆¿Ãµ∞° 0 ¿Ã æ∆¥œ?E∆÷ƒ´µÂ¿Ã∏Èº≠ DBø° ∆÷¿Ã ª˝º∫µ» ∞Õ¿Ã¥Ÿ.
		if ( pItem->sBasicOp.emItemType == ITEM_PET_CARD && pTradeItem->sItemCustom.dwPetID != 0 )
		{
			CExchangePet* pDbAction = new CExchangePet ( m_dwCharID, pTradeItem->sItemCustom.dwPetID );
			GLDBMan* pDBMan = m_pGLGaeaServer->GetDBMan ();
			if ( pDBMan ) pDBMan->AddJob ( pDbAction );
		}
*/

		pInvenItem = m_cInventory.GetItem ( wPosX, wPosY );

		//	Note :æ∆¿Ã≈€¿« º“¿Ø ¿Ã?E∞Ê∑Œ ±‚∑œ.
		//
		GLITEMLMT::GetInstance().ReqItemRoute ( pInvenItem->sItemCustom, ID_CHAR, dwFromCharID, ID_CHAR, m_dwCharID, EMITEM_ROUTE_CHAR, pInvenItem->sItemCustom.wTurnNum );

		//	Note : æ∆¿Ã≈€ ∫Ø»≠∏¶ ≈¨∂Û¿Ãæ∆Æø° æÀ∏≤.
		//		
		NetMsgInert.Data = *pInvenItem;
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgInert );
	}

	return TRUE;
}

// *****************************************************
// Desc: Ω√∞£¡¶«— æ∆¿Ã≈€ æ˜µ•¿Ã∆Æ
// *****************************************************
void GLChar::RESET_TIMELMT_ITEM ()
{
	std::vector<GLInventory::CELL_KEY>	vecDELETE;

	const CTime cTIME_CUR = CTime::GetCurrentTime();

	SINVENITEM* pInvenItem = NULL;
	SITEM* pITEM = NULL;
	GLMSG::SNET_INVEN_DEL_ITEM_TIMELMT NetMsgInvenDelTimeLmt;
	GLMSG::SNET_INVEN_ITEM_UPDATE NetItemUpdate;

	// ∆÷ æ∆¿Ã≈€ ΩΩ∑‘
	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( pMyPet && pMyPet->IsValid () ) pMyPet->UpdateTimeLmtItem ( this );

	// ≈ª∞Õ æ∆¿Ã≈€ ΩΩ∑‘ 
	if ( m_sVehicle.IsActiveValue() ) m_sVehicle.UpdateTimeLmtItem( this );

//	GLGaeaServer & glGaeaServer = m_pGLGaeaServer;
	GLITEMLMT & glItemmt = GLITEMLMT::GetInstance();
	GLItemMan & glItemMan = GLItemMan::GetInstance();
	
	// ¿Œ∫•≈‰∏Æ æ∆¿Ã≈€
	GLInventory::CELL_MAP* pMapItem = m_cInventory.GetItemList();
	GLInventory::CELL_MAP_CITER iter = pMapItem->begin();
	GLInventory::CELL_MAP_CITER iter_end = pMapItem->end();
	for ( ; iter!=iter_end; ++iter )
	{
		pInvenItem = (*iter).second;
		pITEM = glItemMan.GetItem ( pInvenItem->sItemCustom.sNativeID );
		if ( !pITEM )	continue;

		bool bDELETE(false);

		// Ω√«—∫Œ æ∆¿Ã≈€
		if ( pITEM->IsTIMELMT() )
		{
			CTimeSpan cSPAN(pITEM->sDrugOp.tTIME_LMT);
			CTime cTIME_LMT(pInvenItem->sItemCustom.tBORNTIME);
			cTIME_LMT += cSPAN;

			if ( cTIME_CUR > cTIME_LMT )
			{
				vecDELETE.push_back ( (*iter).first );
				bDELETE = true;

				if ( pITEM->sBasicOp.emItemType == ITEM_VEHICLE && pInvenItem->sItemCustom.dwVehicleID != 0 )
				{
					// æ«ººªÁ∏Æ∏¶ √º≈©»ƒ ∆÷¿ª DBø°º≠ ªË¡¶«ÿ¡ÿ¥Ÿ.
					GLVEHICLE* pNewVehicle = new GLVEHICLE();
					CGetVehicle* pGetVehicle = new CGetVehicle ( pNewVehicle, 
													 pInvenItem->sItemCustom.dwVehicleID, 
													 m_dwClientID, 
													 m_dwCharID, 
													 true );
					GLDBMan* pDBMan = m_pGLGaeaServer->GetDBMan ();
					if ( pDBMan ) pDBMan->AddJob ( pGetVehicle );				

				}

				// ∆÷ƒ´µÂ¿œ ∞Ê?E
				if ( pITEM->sBasicOp.emItemType == ITEM_PET_CARD && pInvenItem->sItemCustom.dwPetID != 0 )
				{
					// »∞µø¡ﬂ¿Ã?EªÁ∂Û¡ˆ∞‘ «ÿ¡ÿ¥Ÿ.
					if ( pMyPet && pInvenItem->sItemCustom.dwPetID == pMyPet->m_dwPetID ) 
					{
						m_pGLGaeaServer->ReserveDropOutPet ( SDROPOUTPETINFO(pMyPet->m_dwGUID,true,false) );

						// ∆÷¿« æ«ººªÁ∏Æ∏¶ ∞ÀªÁ«—¥Ÿ.
						pMyPet->UpdateTimeLmtItem ( this );

						// ≥÷æ˚›Ÿ≤® ≥÷æ˚›ÿ¥Ÿ.
						for ( WORD i = 0; i < ACCETYPESIZE; ++i )
						{
							CItemDrop cDropItem;
							cDropItem.sItemCustom = pMyPet->m_PutOnItems[i];
							if ( IsInsertToInven ( &cDropItem ) ) InsertToInven ( &cDropItem );
							else
							{
								if ( m_pLandMan )
								{
									m_pLandMan->DropItem ( m_vPos, 
														   &(cDropItem.sItemCustom), 
														   EMGROUP_ONE, 
														   m_dwGaeaID );
								}
							}
						}

						CDeletePet* pDeletePet = new CDeletePet ( m_dwCharID, pInvenItem->sItemCustom.dwPetID );
						GLDBMan* pDBMan = m_pGLGaeaServer->GetDBMan ();
						if ( pDBMan ) pDBMan->AddJob ( pDeletePet );
						
						// ∆÷¿Ã ªË¡¶µ«?E∫Œ»∞¡§∫∏∏¶ ≈¨∂Û¿Ãæ∆Æø° æÀ∑¡¡‹.
						CGetRestorePetList *pGetRestorePetList = new CGetRestorePetList ( m_dwCharID, m_dwClientID );
						if ( pDBMan ) pDBMan->AddJob ( pGetRestorePetList );
					}
					else
					{
						// æ«ººªÁ∏Æ∏¶ √º≈©»ƒ ∆÷¿ª DBø°º≠ ªË¡¶«ÿ¡ÿ¥Ÿ.
						GLPET* pNewPet = new GLPET ();
						CGetPet* pGetPet = new CGetPet ( pNewPet, 
														 pInvenItem->sItemCustom.dwPetID, 
														 m_dwClientID, 
														 m_dwCharID,
														 pInvenItem->wPosX,
														 pInvenItem->wPosY,
														 true );
						GLDBMan* pDBMan = m_pGLGaeaServer->GetDBMan ();
						if ( pDBMan ) pDBMan->AddJob ( pGetPet );
					}
				}
			}
		}

		// ƒ⁄Ω∫∆¨
		if ( !bDELETE && pInvenItem->sItemCustom.nidDISGUISE!=SNATIVEID(false) )
		{
			if ( pInvenItem->sItemCustom.tDISGUISE != 0 )
			{
				CTime cTIME_LMT(pInvenItem->sItemCustom.tDISGUISE);
				if ( cTIME_LMT.GetYear()!=1970 )
				{
					if ( cTIME_CUR > cTIME_LMT )
					{
						//	Ω√∞£ ¡¶«—¿∏∑Œ æ∆¿Ã≈€ ªË¡¶ æÀ∏≤.						
						NetMsgInvenDelTimeLmt.nidITEM = pInvenItem->sItemCustom.nidDISGUISE;
						m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgInvenDelTimeLmt);

						//	Note : ƒ⁄Ω∫?E¡§∫∏ ∏Æº¬.
						pInvenItem->sItemCustom.tDISGUISE = 0;
						pInvenItem->sItemCustom.nidDISGUISE = SNATIVEID(false);

						//	Note : ≈¨∂Û¿Ãæ∆Æø° æÀ∏≤.						
						NetItemUpdate.wPosX = pInvenItem->wPosX;
						NetItemUpdate.wPosY = pInvenItem->wPosY;
						NetItemUpdate.sItemCustom = pInvenItem->sItemCustom;
						m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetItemUpdate);

						//	Note : ∑Œ±◊ ¿˙?E
						glItemmt.ReqItemConversion ( pInvenItem->sItemCustom, ID_CHAR, m_dwCharID );
					}
				}
			}
		}
	}

	if ( !vecDELETE.empty() )
	{
		for ( DWORD i=0; i<vecDELETE.size(); ++i )
		{
			const GLInventory::CELL_KEY &cKEY = vecDELETE[i];
			SINVENITEM sINVENITEM = *m_cInventory.GetItem(cKEY.first,cKEY.second);

			SNATIVEID nidITEM = sINVENITEM.sItemCustom.sNativeID;

			//	Ω√∞£ ¡¶«—¿∏∑Œ æ∆¿Ã≈€ ªË¡¶ ∑Œ±◊ ≥≤?E
			glItemmt.ReqItemRoute ( sINVENITEM.sItemCustom, ID_CHAR, m_dwCharID, ID_CHAR, 0, EMITEM_ROUTE_DELETE, sINVENITEM.sItemCustom.wTurnNum );

			//	Note : æ∆¿Ã≈€ ªË¡¶.
			//
			m_cInventory.DeleteItem ( cKEY.first, cKEY.second );

			//	[¿⁄Ω≈ø°∞‘] «ÿ?Eæ∆¿Ã≈∆¿ª ¿Œ?E°º?ªË¡¶.
			GLMSG::SNETPC_INVEN_DELETE NetMsgInvenDel;
			NetMsgInvenDel.wPosX = cKEY.first;
			NetMsgInvenDel.wPosY = cKEY.second;
			m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgInvenDel);

			//	Ω√∞£ ¡¶«—¿∏∑Œ æ∆¿Ã≈€ ªË¡¶ æÀ∏≤.
			GLMSG::SNET_INVEN_DEL_ITEM_TIMELMT NetMsgInvenDelTimeLmt;
			NetMsgInvenDelTimeLmt.nidITEM = nidITEM;
			m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgInvenDelTimeLmt);

			//	Note : ƒ⁄Ω∫?E∫π±∏.
			if ( sINVENITEM.sItemCustom.nidDISGUISE!=SNATIVEID(false) )
			{
				SITEM *pONE = glItemMan.GetItem ( sINVENITEM.sItemCustom.nidDISGUISE );
				if ( !pONE )		continue;

				//	¿Œ∫• ¿ßƒ°.
				WORD wInsertPosX = cKEY.first, wInsertPosY = cKEY.second;

				SITEMCUSTOM sITEM_NEW;
				sITEM_NEW.sNativeID = sINVENITEM.sItemCustom.nidDISGUISE;
				CTime cTIME = CTime::GetCurrentTime();
				if ( sINVENITEM.sItemCustom.tDISGUISE!=0 && pONE->sDrugOp.tTIME_LMT!= 0 )
				{
					cTIME = CTime(sINVENITEM.sItemCustom.tDISGUISE);

					CTimeSpan tLMT(pONE->sDrugOp.tTIME_LMT);
					cTIME -= tLMT;
				}

				//	Note : æ∆¿Ã≈€ ª˝º∫.
				//
				sITEM_NEW.tBORNTIME = cTIME.GetTime();
				sITEM_NEW.wTurnNum = 1;
				sITEM_NEW.cGenType = EMGEN_BILLING;
				sITEM_NEW.cChnID = (BYTE)m_pGLGaeaServer->GetServerChannel();
				sITEM_NEW.cFieldID = (BYTE)m_pGLGaeaServer->GetFieldSvrID();
				sITEM_NEW.lnGenNum = glItemmt.RegItemGen ( sITEM_NEW.sNativeID, (EMITEMGEN)sITEM_NEW.cGenType );

				//	Note : ¿Œ∫•ø° µÈæ˚Ã• ∞¯∞£ ∞À?E
				BOOL bOk = m_cInventory.IsInsertable ( pONE->sBasicOp.wInvenSizeX, pONE->sBasicOp.wInvenSizeY, wInsertPosX, wInsertPosY );
				if ( !bOk )		continue;

				//	Note : ¿Œ∫•ø° ≥÷¿Ω.
				m_cInventory.InsertItem ( sITEM_NEW, wInsertPosX, wInsertPosY );
				SINVENITEM *pINSERT_ITEM = m_cInventory.GetItem ( wInsertPosX, wInsertPosY );

				GLMSG::SNETPC_INVEN_INSERT NetItemInsert;
				NetItemInsert.Data = *pINSERT_ITEM;
				m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetItemInsert);

				//	Note : ∫–∏Æµ» ƒ⁄Ω∫?E∑Œ±◊.
				glItemmt.ReqItemRoute ( pINSERT_ITEM->sItemCustom, ID_CHAR, 0, ID_CHAR, m_dwCharID, EMITEM_ROUTE_CHAR, pINSERT_ITEM->sItemCustom.wTurnNum );
			}
		}
	}

	// æ∆¿Ã≈€ ΩΩ∑‘ ¡§∫∏ ∞ªΩ≈
	for ( int i=0; i<SLOT_TSIZE; ++i )
	{
		EMSLOT emSLOT = (EMSLOT) i;
		if( m_PutOnItems[emSLOT].sNativeID==NATIVEID_NULL() ) continue;

		SITEMCUSTOM sCUSTOM = m_PutOnItems[emSLOT];

		SITEM *pITEM = glItemMan.GetItem ( sCUSTOM.sNativeID );
		if ( !pITEM )								continue;

		bool bDELETE(false);

		if ( pITEM->IsTIMELMT() )
		{
			CTimeSpan cSPAN(pITEM->sDrugOp.tTIME_LMT);
			CTime cTIME_LMT(sCUSTOM.tBORNTIME);
			cTIME_LMT += cSPAN;

			if ( cTIME_CUR > cTIME_LMT )
			{
				//	Ω√∞£ ¡¶«—¿∏∑Œ æ∆¿Ã≈€ ªË¡¶ ∑Œ±◊ ≥≤?E
				glItemmt.ReqItemRoute ( sCUSTOM, ID_CHAR, m_dwCharID, ID_CHAR, 0, EMITEM_ROUTE_DELETE, sCUSTOM.wTurnNum );

				//	Ω√∞£ ¡¶«—¿∏∑Œ æ∆¿Ã≈€ ªË¡¶ æÀ∏≤.
				GLMSG::SNET_INVEN_DEL_ITEM_TIMELMT NetMsgInvenDelTimeLmt;
				NetMsgInvenDelTimeLmt.nidITEM = sCUSTOM.sNativeID;
				m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgInvenDelTimeLmt);

				if ( pITEM->sBasicOp.emItemType == ITEM_VEHICLE && sCUSTOM.dwVehicleID != 0 )
				{
					m_pGLGaeaServer->SaveVehicle( m_dwClientID, m_dwGaeaID, false );

                	// æ«ººªÁ∏Æ∏¶ √º≈©»ƒ ∆÷¿ª DBø°º≠ ªË¡¶«ÿ¡ÿ¥Ÿ.
					GLVEHICLE* pNewVehicle = new GLVEHICLE();
					CGetVehicle* pGetVehicle = new CGetVehicle ( pNewVehicle, 
													 sCUSTOM.dwVehicleID, 
													 m_dwClientID, 
													 m_dwCharID, 
													 true );

					GLDBMan* pDBMan = m_pGLGaeaServer->GetDBMan ();
					if ( pDBMan ) pDBMan->AddJob ( pGetVehicle );
				}

				//	æ∆¿Ã≈€ ¡¶∞≈.
				RELEASE_SLOT_ITEM ( emSLOT );

				//	[¿⁄Ω≈ø°∞‘]  æ∆¿Ã≈∆ ¡¶∞≈.
				GLMSG::SNETPC_PUTON_RELEASE NetMsg_Release(emSLOT);
				m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg_Release);

				//	Note : ¡÷∫Ø ªÁ∂˜µÈø°∞‘ æ∆¿Ã≈∆ ¡¶∞≈.
				GLMSG::SNETPC_PUTON_RELEASE_BRD NetMsgReleaseBrd;
				NetMsgReleaseBrd.dwGaeaID = m_dwGaeaID;
				NetMsgReleaseBrd.emSlot = emSLOT;
				SendMsgViewAround ( reinterpret_cast<NET_MSG_GENERIC*>(&NetMsgReleaseBrd) );

				bDELETE = true;

				//	Note : ƒ⁄Ω∫?E∫π±∏.
				if ( sCUSTOM.nidDISGUISE!=SNATIVEID(false) )
				{
					SITEM *pONE = glItemMan.GetItem ( sCUSTOM.nidDISGUISE );
					if ( !pONE )		continue;

					SITEMCUSTOM sITEM_NEW;
					sITEM_NEW.sNativeID = sCUSTOM.nidDISGUISE;
					CTime cTIME = CTime::GetCurrentTime();
					if ( sCUSTOM.tDISGUISE!=0 && pONE->sDrugOp.tTIME_LMT!= 0 )
					{
						cTIME = CTime(sCUSTOM.tDISGUISE);

						CTimeSpan tLMT(pONE->sDrugOp.tTIME_LMT);
						cTIME -= tLMT;
					}

					//	Note : æ∆¿Ã≈€ ª˝º∫.
					//
					sITEM_NEW.tBORNTIME = cTIME.GetTime();
					sITEM_NEW.wTurnNum = 1;
					sITEM_NEW.cGenType = EMGEN_BILLING;
					sITEM_NEW.cChnID = (BYTE)m_pGLGaeaServer->GetServerChannel();
					sITEM_NEW.cFieldID = (BYTE)m_pGLGaeaServer->GetFieldSvrID();
					sITEM_NEW.lnGenNum = glItemmt.RegItemGen ( sITEM_NEW.sNativeID, (EMITEMGEN)sITEM_NEW.cGenType );

					//	Note : ∫π?E¬¯?E
					SLOT_ITEM ( sITEM_NEW, emSLOT );

					//	Note : ¿⁄Ω≈ø°∞‘ ¬¯?E∆¿Ã≈?∫Ø?E
					GLMSG::SNETPC_PUTON_UPDATE NetMsgUpdate;
					NetMsgUpdate.emSlot = emSLOT;
					NetMsgUpdate.sItemCustom = sITEM_NEW;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgUpdate);

					//	Note : ¡÷∫Ø ªÁ∂˜µÈø°∞‘ ¬¯?E∆¿Ã≈?∫Ø?E
					GLMSG::SNETPC_PUTON_UPDATE_BRD NetMsgUpdateBrd;
					NetMsgUpdateBrd.dwGaeaID = m_dwGaeaID;
					NetMsgUpdateBrd.emSlot = emSLOT;
					NetMsgUpdateBrd.sItemClient.Assign ( sITEM_NEW );
					SendMsgViewAround ( reinterpret_cast<NET_MSG_GENERIC*>(&NetMsgUpdateBrd) );

					//	Note : ∫–∏Æµ» ƒ⁄Ω∫?E∑Œ±◊.
					glItemmt.ReqItemRoute ( sITEM_NEW, ID_CHAR, 0, ID_CHAR, m_dwCharID, EMITEM_ROUTE_CHAR, sITEM_NEW.wTurnNum );
				}
			}
		}
		
		if ( !bDELETE && VALID_SLOT_ITEM(emSLOT) && sCUSTOM.nidDISGUISE!=SNATIVEID(false) )
		{
			if ( sCUSTOM.tDISGUISE != 0 )
			{
				CTime cTIME_LMT(sCUSTOM.tDISGUISE);
				if ( cTIME_LMT.GetYear()!=1970 )
				{
					if ( cTIME_CUR > cTIME_LMT )
					{
						//	Ω√∞£ ¡¶«—¿∏∑Œ æ∆¿Ã≈€ ªË¡¶ æÀ∏≤.
						GLMSG::SNET_INVEN_DEL_ITEM_TIMELMT NetMsgInvenDelTimeLmt;
						NetMsgInvenDelTimeLmt.nidITEM = sCUSTOM.nidDISGUISE;
						m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgInvenDelTimeLmt);

						//	Note : ƒ⁄Ω∫?E¡§∫∏ ∏Æº¬.
						sCUSTOM.tDISGUISE = 0;
						sCUSTOM.nidDISGUISE = SNATIVEID(false);
						SLOT_ITEM ( sCUSTOM, emSLOT );			//	Ω«¡¶∑Œ ¿˚?E

						//	Note : ¿⁄Ω≈ø°∞‘ ¬¯?E∆¿Ã≈?∫Ø?E
						GLMSG::SNETPC_PUTON_UPDATE NetMsgUpdate;
						NetMsgUpdate.emSlot = emSLOT;
						NetMsgUpdate.sItemCustom = sCUSTOM;
						m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgUpdate);

						//	Note : ¡÷∫Ø ªÁ∂˜µÈø°∞‘ ¬¯?E∆¿Ã≈?∫Ø?E
						GLMSG::SNETPC_PUTON_UPDATE_BRD NetMsgUpdateBrd;
						NetMsgUpdateBrd.dwGaeaID = m_dwGaeaID;
						NetMsgUpdateBrd.emSlot = emSLOT;
						NetMsgUpdateBrd.sItemClient.Assign ( sCUSTOM );
						SendMsgViewAround ( reinterpret_cast<NET_MSG_GENERIC*>(&NetMsgUpdateBrd) );
					}
				}
			}
		}
	}

	//	Note : ¿Œ∫•≈‰∏Æ √ﬂ∞°∂Û¿Œ ¿Ø»øº∫ ∞À?E
	//
	GLMSG::SNETPC_STORAGE_STATE NetMsgStorageState;
	for ( WORD i=0; i<EMSTORAGE_CHANNEL_SPAN_SIZE; ++i )
	{
		bool bVALID(true);
		CTime cSTORAGE(m_tSTORAGE[i]);

		if ( m_tSTORAGE[i]==0 )		bVALID = false;
		if ( cSTORAGE<cTIME_CUR )
		{
			bVALID = false;
		}

		m_bSTORAGE[i] = bVALID;
		NetMsgStorageState.bVALID[i] = bVALID;
	}
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgStorageState);

	bool bPREMIUM(true);
	CTime cPREMIUM(m_tPREMIUM);
	if ( m_tPREMIUM==0 )			bPREMIUM = false;
	if ( cPREMIUM<cTIME_CUR )
	{
		bPREMIUM = false;
	}

	m_bPREMIUM = bPREMIUM;

	GLMSG::SNETPC_PREMIUM_STATE NetMsgPremium;
	NetMsgPremium.bPREMIUM = bPREMIUM;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgPremium);

	//	Note : «ˆ?E»∞º∫»≠µ» ¿Œ∫• ∂Û¿Œ º≥¡§.
	//
	m_cInventory.SetAddLine ( GetOnINVENLINE(), true );

	// √¢?Eæ∆¿Ã≈€ ¿Ø»øº∫ ∞ªΩ≈
	for ( WORD idx = 0; idx < EMSTORAGE_CHANNEL; ++idx )
	{
		GLInventory::CELL_MAP* pMapItem = m_cStorage[idx].GetItemList();
		GLInventory::CELL_MAP_CITER iter = pMapItem->begin();
		GLInventory::CELL_MAP_CITER iter_end = pMapItem->end();

		vecDELETE.clear();

		for ( ; iter!=iter_end; ++iter )
		{
			SINVENITEM *pInvenItem = (*iter).second;

			SITEM *pITEM = glItemMan.GetItem ( pInvenItem->sItemCustom.sNativeID );
			if ( !pITEM )								continue;

			bool bDELETE(false);

			// Ω√«—∫Œ æ∆¿Ã≈€
			if ( pITEM->IsTIMELMT() )
			{
				CTimeSpan cSPAN(pITEM->sDrugOp.tTIME_LMT);
				CTime cTIME_LMT(pInvenItem->sItemCustom.tBORNTIME);
				cTIME_LMT += cSPAN;

				if ( cTIME_CUR > cTIME_LMT )
				{
					vecDELETE.push_back ( (*iter).first );
					bDELETE = true;

					// ∆÷ƒ´µÂ¿œ ∞Ê?E
					if ( pITEM->sBasicOp.emItemType == ITEM_PET_CARD && pInvenItem->sItemCustom.dwPetID != 0 )
					{
						// æ«ººªÁ∏Æ∏¶ √º≈©»ƒ ∆÷¿ª DBø°º≠ ªË¡¶«ÿ¡ÿ¥Ÿ.
						GLPET* pNewPet = new GLPET ();
						CGetPet* pGetPet = new CGetPet ( pNewPet, 
														 pInvenItem->sItemCustom.dwPetID, 
														 m_dwClientID, 
														 m_dwCharID,
														 pInvenItem->wPosX,
														 pInvenItem->wPosY,
														 true );
						GLDBMan* pDBMan = m_pGLGaeaServer->GetDBMan ();
						if ( pDBMan ) pDBMan->AddJob ( pGetPet );
					}

					// ≈ª∞Õ¿œ ∞Ê?E
					if ( pITEM->sBasicOp.emItemType == ITEM_VEHICLE && pInvenItem->sItemCustom.dwVehicleID != 0 )
					{
						// æ«ººªÁ∏Æ∏¶ √º≈©»ƒ ≈ª∞Õ¿ª DBø°º≠ ªË¡¶«ÿ¡ÿ¥Ÿ.
						GLVEHICLE* pNewVehicle = new GLVEHICLE();
						CGetVehicle* pGetVehicle = new CGetVehicle ( pNewVehicle, 
													 pInvenItem->sItemCustom.dwVehicleID, 
													 m_dwClientID,
													 m_dwCharID, 
													 true );
						GLDBMan* pDBMan = m_pGLGaeaServer->GetDBMan ();
						if ( pDBMan ) pDBMan->AddJob ( pGetVehicle );		
					}
				}
			}
			
			// ƒ⁄Ω∫∆¨
			if ( !bDELETE && pInvenItem->sItemCustom.nidDISGUISE!=SNATIVEID(false) )
			{
				if ( pInvenItem->sItemCustom.tDISGUISE != 0 )
				{
					CTime cTIME_LMT(pInvenItem->sItemCustom.tDISGUISE);
					if ( cTIME_LMT.GetYear()!=1970 )
					{
						if ( cTIME_CUR > cTIME_LMT )
						{
							//	Ω√∞£ ¡¶«—¿∏∑Œ æ∆¿Ã≈€ ªË¡¶ æÀ∏≤.
							GLMSG::SNET_INVEN_DEL_ITEM_TIMELMT NetMsgInvenDelTimeLmt;
							NetMsgInvenDelTimeLmt.nidITEM = pInvenItem->sItemCustom.nidDISGUISE;
							m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgInvenDelTimeLmt);

							//	Note : ƒ⁄Ω∫?E¡§∫∏ ∏Æº¬.
							pInvenItem->sItemCustom.tDISGUISE = 0;
							pInvenItem->sItemCustom.nidDISGUISE = SNATIVEID(false);

							//	Note : ≈¨∂Û¿Ãæ∆Æø° æÀ∏≤.
							GLMSG::SNETPC_STORAGE_ITEM_UPDATE NetItemUpdate;
							NetItemUpdate.dwChannel = idx;
							NetItemUpdate.wPosX = pInvenItem->wPosX;
							NetItemUpdate.wPosY = pInvenItem->wPosY;
							NetItemUpdate.sItemCustom = pInvenItem->sItemCustom;
							m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetItemUpdate);

							//	Note : ∑Œ±◊ ¿˙?E
							glItemmt.ReqItemConversion ( pInvenItem->sItemCustom, ID_CHAR, m_dwCharID );
						}
					}
				}
			}
		}

		if ( !vecDELETE.empty() )
		{
			for ( DWORD i=0; i<vecDELETE.size(); ++i )
			{
				const GLInventory::CELL_KEY &cKEY = vecDELETE[i];
				SINVENITEM sINVENITEM = *m_cStorage[idx].GetItem(cKEY.first,cKEY.second);

				SNATIVEID nidITEM = sINVENITEM.sItemCustom.sNativeID;

				//	Ω√∞£ ¡¶«—¿∏∑Œ æ∆¿Ã≈€ ªË¡¶ ∑Œ±◊ ≥≤?E
				glItemmt.ReqItemRoute ( sINVENITEM.sItemCustom, ID_CHAR, m_dwCharID, ID_CHAR, 0, EMITEM_ROUTE_DELETE, sINVENITEM.sItemCustom.wTurnNum );

				//	Note : æ∆¿Ã≈€ ªË¡¶.
				//
				m_cStorage[idx].DeleteItem ( cKEY.first, cKEY.second );

				//	[¿⁄Ω≈ø°∞‘] «ÿ?Eæ∆¿Ã≈∆¿ª ¿Œ?E°º?ªË¡¶.
				GLMSG::SNETPC_STORAGE_DELETE NetMsgStorageDel;
				NetMsgStorageDel.dwChannel = idx;
				NetMsgStorageDel.wPosX = cKEY.first;
				NetMsgStorageDel.wPosY = cKEY.second;
				m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgStorageDel);

				//	Ω√∞£ ¡¶«—¿∏∑Œ æ∆¿Ã≈€ ªË¡¶ æÀ∏≤.
				GLMSG::SNET_INVEN_DEL_ITEM_TIMELMT NetMsgInvenDelTimeLmt;
				NetMsgInvenDelTimeLmt.nidITEM = nidITEM;
				m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgInvenDelTimeLmt);

				//	Note : ƒ⁄Ω∫?E∫π±∏.
				if ( sINVENITEM.sItemCustom.nidDISGUISE!=SNATIVEID(false) )
				{
					SITEM *pONE = glItemMan.GetItem ( sINVENITEM.sItemCustom.nidDISGUISE );
					if ( !pONE )		continue;

					//	¿Œ∫• ¿ßƒ°.
					WORD wInsertPosX = cKEY.first, wInsertPosY = cKEY.second;

					SITEMCUSTOM sITEM_NEW;
					sITEM_NEW.sNativeID = sINVENITEM.sItemCustom.nidDISGUISE;
					CTime cTIME = CTime::GetCurrentTime();
					if ( sINVENITEM.sItemCustom.tDISGUISE!=0 && pONE->sDrugOp.tTIME_LMT!= 0 )
					{
						cTIME = CTime(sINVENITEM.sItemCustom.tDISGUISE);

						CTimeSpan tLMT(pONE->sDrugOp.tTIME_LMT);
						cTIME -= tLMT;
					}

					//	Note : æ∆¿Ã≈€ ª˝º∫.
					//
					sITEM_NEW.tBORNTIME = cTIME.GetTime();
					sITEM_NEW.wTurnNum = 1;
					sITEM_NEW.cGenType = EMGEN_BILLING;
					sITEM_NEW.cChnID = (BYTE)m_pGLGaeaServer->GetServerChannel();
					sITEM_NEW.cFieldID = (BYTE)m_pGLGaeaServer->GetFieldSvrID();
					sITEM_NEW.lnGenNum = glItemmt.RegItemGen ( sITEM_NEW.sNativeID, (EMITEMGEN)sITEM_NEW.cGenType );

					//	Note : ¿Œ∫•ø° µÈæ˚Ã• ∞¯∞£ ∞À?E
					BOOL bOk = m_cStorage[idx].IsInsertable ( pONE->sBasicOp.wInvenSizeX, pONE->sBasicOp.wInvenSizeY, wInsertPosX, wInsertPosY );
					if ( !bOk )		continue;

					//	Note : ¿Œ∫•ø° ≥÷¿Ω.
					m_cStorage[idx].InsertItem ( sITEM_NEW, wInsertPosX, wInsertPosY );
					SINVENITEM *pINSERT_ITEM = m_cStorage[idx].GetItem ( wInsertPosX, wInsertPosY );

					GLMSG::SNETPC_STORAGE_INSERT NetItemInsert;
					NetItemInsert.dwChannel = idx;
					NetItemInsert.Data = *pINSERT_ITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetItemInsert);

					//	Note : ∫–∏Æµ» ƒ⁄Ω∫?E∑Œ±◊.
					glItemmt.ReqItemRoute ( pINSERT_ITEM->sItemCustom, ID_CHAR, 0, ID_CHAR, m_dwCharID, EMITEM_ROUTE_CHAR, pINSERT_ITEM->sItemCustom.wTurnNum );
				}
			}
		}
	}
}




// *****************************************************
// Desc: æ∆¿Ã≈€ ¡∂∞« √º≈© ( Ω√∞£¡¶«—?E∞∞¿Ã ¿€µø ) 
// *****************************************************
void GLChar::RESET_CHECK_ITEM ()
{

	// æ∆¿Ã≈€ ΩΩ∑‘ ¬¯?E¡∂∞«¿ª √º≈©«—¥Ÿ.
	for ( int i=0; i<SLOT_HOLD; ++i )
	{
		EMSLOT emSLOT = (EMSLOT) i;
		
		if ( m_PutOnItems[emSLOT].sNativeID == NATIVEID_NULL() ) continue;

		SITEMCUSTOM sCUSTOM = m_PutOnItems[emSLOT];

		SITEM *pITEM = GLItemMan::GetInstance().GetItem ( sCUSTOM.sNativeID );
		if ( !pITEM )	continue;

		bool bRelease(false);

		// ∫Òƒ⁄Ω∫∆¨
		if ( sCUSTOM.nidDISGUISE == NATIVEID_NULL() )
		{
			if ( !SIMPLE_CHECK_ITEM( sCUSTOM.sNativeID ) )	bRelease = true;
		}
		// ƒ⁄Ω∫∆¨
		else 
		{
			if ( !SIMPLE_CHECK_ITEM ( sCUSTOM.sNativeID, sCUSTOM.nidDISGUISE ) ) bRelease = true;
		}

		if ( bRelease ) 
		{
			EMSLOT emRHand = GetCurRHand();
			EMSLOT emLHand = GetCurLHand();

			if ( emSLOT == emRHand ) 
			{
				SITEM *pITEM_LEFT=NULL, *pITEM_RIGHT=NULL;
				if ( VALID_SLOT_ITEM(emLHand) )	pITEM_LEFT = GLItemMan::GetInstance().GetItem(GET_SLOT_ITEM(emLHand).sNativeID);
				if ( VALID_SLOT_ITEM(emRHand) )	pITEM_RIGHT = GLItemMan::GetInstance().GetItem(GET_SLOT_ITEM(emRHand).sNativeID);

				if ( (pITEM_RIGHT->sSuitOp.emAttack==ITEMATT_BOW) ||(pITEM_RIGHT->sSuitOp.emAttack==ITEMATT_SCYTHE)|| (pITEM_RIGHT->sSuitOp.emAttack==ITEMATT_SPEAR) || (pITEM_RIGHT->sSuitOp.emAttack==ITEMATT_DUAL_GUN || pITEM_RIGHT->sSuitOp.emAttack==ITEMATT_RAIL_GUN || pITEM_RIGHT->sSuitOp.emAttack==ITEMATT_PORTAL_GUN) )
				{
					if ( pITEM_LEFT )	//	»≠?E ∫Œ?Eª©≥ªæﬂ «‘.
					{
						SITEMCUSTOM sITEM_LHAND = GET_SLOT_ITEM(emLHand);

						CItemDrop cDropItem;
						cDropItem.sItemCustom = m_PutOnItems[emLHand];

						if ( IsInsertToInvenEx ( &cDropItem ) )
						{
							InsertToInvenEx( &cDropItem );
						}
						else
						{
							if ( m_pLandMan )
							{
								m_pLandMan->DropItem ( m_vPos, 
														&(cDropItem.sItemCustom), 
														EMGROUP_ONE, 
														m_dwGaeaID );
							}
						}

						//	øﬁ¬  ΩΩ∑‘ ¡ˆøˆ¡‹.
						RELEASE_SLOT_ITEM(emLHand);

						//	[¿⁄Ω≈ø°∞‘] SLOTø° ¿÷æ˙?Eæ∆¿Ã≈∆ ¡¶∞≈.
						GLMSG::SNETPC_PUTON_RELEASE NetMsg_PutOn_Release(emLHand);
						m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg_PutOn_Release);				
					}

				}
			}
			
			// ≈ª∞Õ ΩΩ∑‘¿œ∞Ê?EΩΩ∑‘¿« æ∆¿Ã≈€ ¡§∏Æ
			if ( emSLOT == SLOT_VEHICLE &&  m_sVehicle.IsActiveValue() )
			{
				for ( int i = 0; i < ACCE_TYPE_SIZE; ++i )
				{
					if ( m_sVehicle.m_PutOnItems[i].sNativeID == NATIVEID_NULL() ) continue;
					
					// ¿Œ∫• ª¿‘
					CItemDrop cDropItem;
					cDropItem.sItemCustom = m_sVehicle.m_PutOnItems[i];
					
					if ( IsInsertToInvenEx ( &cDropItem ) )
					{
						InsertToInvenEx ( &cDropItem );
					}
					else
					{
						if ( m_pLandMan )
						{
							m_pLandMan->DropItem ( m_vPos, 
													&(cDropItem.sItemCustom), 
													EMGROUP_ONE, 
													m_dwGaeaID );
						}
					}

					m_sVehicle.m_PutOnItems[i].sNativeID = NATIVEID_NULL();
					
					// ≈ª∞Õ ∏±∏Æ?E
					//	[¿⁄Ω≈ø°∞‘] «ÿ?Eæ∆¿Ã≈∆¿ª ¿Œ?E°º?ªË¡¶.
					GLMSG::SNET_VEHICLE_ACCESSORY_DELETE NetMsg;
					NetMsg.dwVehicleNum	= m_sVehicle.m_dwGUID;
					NetMsg.accetype = (VEHICLE_ACCESSORYTYPE)i;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);

					// ¡÷∫Øø° æÀ∏≤.
					GLMSG::SNET_VEHICLE_ACCESSORY_DELETE_BRD NetMsgBrd;
					NetMsgBrd.dwGaeaID = m_dwGaeaID;
					NetMsgBrd.dwVehicleNum = m_sVehicle.m_dwGUID;
					NetMsgBrd.accetype = (VEHICLE_ACCESSORYTYPE)i;
					SendMsgViewAround ( reinterpret_cast<NET_MSG_GENERIC*>(&NetMsgBrd) );				
				}

				m_pGLGaeaServer->SaveVehicle( m_dwClientID, m_dwGaeaID, false );
			}
			// ≈ª∞Õ ¡§∫∏∞° »∞º∫»≠ µ«?Eæ æ“¿ª∞Ê?E°¥?¡¶∞≈ «œ?Eæ ¥¬¥Ÿ.
			else if ( emSLOT == SLOT_VEHICLE &&  !m_sVehicle.IsActiveValue() )
			{
				continue;
			}

			//	[¿⁄Ω≈ø°∞‘] SLOTø° ¿÷æ˙?Eæ∆¿Ã≈∆ ¡¶∞≈.
			GLMSG::SNETPC_PUTON_RELEASE NetMsg_PutOn_Release(emSLOT);
			m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg_PutOn_Release);

			//	[∏µŒø°∞‘] ¿⁄Ω≈¿« ¬¯?E∫π¿Â¿Ã πŸ≤Ò¿ª æÀ∏≤.
			GLMSG::SNETPC_PUTON_RELEASE_BRD NetMsg_PutOn_Release_Brd;
			NetMsg_PutOn_Release_Brd.dwGaeaID = m_dwGaeaID;
			NetMsg_PutOn_Release_Brd.emSlot = emSLOT;
			SendMsgViewAround ( reinterpret_cast<NET_MSG_GENERIC*>(&NetMsg_PutOn_Release_Brd) );	


			// ¿Œ∫•ø° ª¿‘
			CItemDrop cDropItem;
			cDropItem.sItemCustom = m_PutOnItems[i];

			if ( IsInsertToInvenEx ( &cDropItem ) )
			{
				InsertToInvenEx ( &cDropItem );
			}
			else
			{
				if ( m_pLandMan )
				{
					m_pLandMan->DropItem ( m_vPos, 
											&(cDropItem.sItemCustom), 
											EMGROUP_ONE, 
											m_dwGaeaID );
				}
			}

			RELEASE_SLOT_ITEM ( emSLOT );			
		}
	}

	// ≈ª∞Õ æ«ººº≠∏Æ ¡∂∞« √º≈©
	if ( m_sVehicle.IsActiveValue() )
	{
		for ( int i = 0; i < ACCE_TYPE_SIZE; ++i )
		{
			if ( m_sVehicle.m_PutOnItems[i].sNativeID == NATIVEID_NULL() ) continue;
			
            if ( !SIMPLE_CHECK_ITEM( m_sVehicle.m_PutOnItems[i].sNativeID ) )
			{
				
				// ¿Œ∫• ª¿‘
				CItemDrop cDropItem;
				cDropItem.sItemCustom = m_sVehicle.m_PutOnItems[i];
				
				if ( IsInsertToInvenEx ( &cDropItem ) )
				{
					InsertToInvenEx ( &cDropItem );
				}
				else
				{
					if ( m_pLandMan )
					{
						m_pLandMan->DropItem ( m_vPos, 
												&(cDropItem.sItemCustom), 
												EMGROUP_ONE, 
												m_dwGaeaID );
					}
				}

				m_sVehicle.m_PutOnItems[i].sNativeID = NATIVEID_NULL();
				
				// ≈ª∞Õ ∏±∏Æ?E
				//	[¿⁄Ω≈ø°∞‘] «ÿ?Eæ∆¿Ã≈∆¿ª ¿Œ?E°º?ªË¡¶.
				GLMSG::SNET_VEHICLE_ACCESSORY_DELETE NetMsg;
				NetMsg.dwVehicleNum	= m_sVehicle.m_dwGUID;
				NetMsg.accetype = (VEHICLE_ACCESSORYTYPE)i;
				m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);

				// ¡÷∫Øø° æÀ∏≤.
				GLMSG::SNET_VEHICLE_ACCESSORY_DELETE_BRD NetMsgBrd;
				NetMsgBrd.dwGaeaID = m_dwGaeaID;
				NetMsgBrd.dwVehicleNum = m_sVehicle.m_dwGUID;
				NetMsgBrd.accetype = (VEHICLE_ACCESSORYTYPE)i;
				SendMsgViewAround ( reinterpret_cast<NET_MSG_GENERIC*>(&NetMsgBrd) );				
			}
		}
	}
}

void GLChar::TurnAction ( EMACTIONTYPE toAction )
{
	//	Note : ¿Ã?Eæ◊º« ?E?
	//

	switch ( m_Action )
	{
	case GLAT_IDLE:
		break;

	case GLAT_ATTACK:
		m_fIdleTime = 0.0f;
		break;

	case GLAT_SKILL:
		m_fIdleTime = 0.0f;
		break;
	case GLAT_GATHERING:
		break;

	default:
		break;
	};

	//CONSOLEMSG_WRITE( "TurnAction [%d]", toAction );

	//	Note : æ◊º« √ ±‚»≠.
	//
	m_fIdleTime = 0.0f;
	m_Action = toAction;
	GLMSG::SNETPC_SKILLHOLD_RS_BRD NetMsgSkillBrd;


    switch ( m_Action )
	{
	case GLAT_IDLE:
		break;

	case GLAT_MOVE:
		m_wHealingNum = 0;
		break;

	case GLAT_ATTACK:
		m_fattTIMER = 0.0f;

		for ( int i=0; i<SKILLFACT_SIZE; ++i)
		{
			if( m_sSKILLFACT[i].sNATIVEID == NATIVEID_NULL() )	continue;
			if( m_sSKILLFACT[i].GetSpec( EMSPECA_INVISIBLE ) )
			{
				DISABLESKEFF( i );
				NetMsgSkillBrd.bRESET[i] = true;
				break;
			}
		}

		NetMsgSkillBrd.dwID = m_dwGaeaID;
		NetMsgSkillBrd.emCrow = CROW_PC;
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgSkillBrd );
		break;

	case GLAT_SKILL:
		m_fattTIMER = 0.0f;

		for ( int i=0; i<SKILLFACT_SIZE; ++i)
		{
			if( m_sSKILLFACT[i].sNATIVEID == NATIVEID_NULL() )	continue;
			if( m_sSKILLFACT[i].GetSpec( EMSPECA_INVISIBLE ) )
			{
				DISABLESKEFF( i );
				NetMsgSkillBrd.bRESET[i] = true;
				break;
			}
		}

		NetMsgSkillBrd.dwID = m_dwGaeaID;
		NetMsgSkillBrd.emCrow = CROW_PC;
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgSkillBrd );
		break;

	case GLAT_SHOCK:
		break;

	case GLAT_PUSHPULL:
		break;

	case GLAT_FALLING:
		TurnAction ( GLAT_DIE );
		break;

	case GLAT_DIE:
		break;
	
	case GLAT_GATHERING:
		break;

	default:
		break;
	};
}

void GLChar::AddPlayHostile ( DWORD dwCHARID, BOOL bBAD, BOOL bClubBattle )
{
	bool bBRIGHTEVENT   = m_pGLGaeaServer->IsBRIGHTEVENT();
	bool bSCHOOL_FREEPK = GLSchoolFreePK::GetInstance().IsON();
	bool bGuidBattleMap = m_pLandMan->m_bGuidBattleMap;
	bool bClubDeathMatch = m_pLandMan->m_bClubDeathMatchMap;
	bool bSchoolWars = m_pLandMan->m_bSchoolWarsMap;
	bool bRoyalRumble = m_pLandMan->m_bRoyalRumbleMap;
	//
	//juver battle royale
	bool bRedZone = m_pLandMan->IsRedZone();
	bool bTowerWars = m_pLandMan->m_bTowerWarsMap;

	PGLCHAR pCHAR = m_pGLGaeaServer->GetCharID ( dwCHARID );
	if ( !pCHAR )		return;

	if ( pCHAR->IsSTATE( EM_ACT_DIE ) ) return;
	if ( IsSTATE( EM_ACT_DIE ) ) return;
	
	//juver battle royal
	if ( GetSchool() == pCHAR->GetSchool() )
	{
		if ( bRedZone )
		{
			bSCHOOL_FREEPK = true;
		}
		if ( bRoyalRumble )
		{
			bSCHOOL_FREEPK = true;
		}
		else
		{
			bSCHOOL_FREEPK = false;
		}
	}

	// DESC : ¿Ø¿˙∞° ∏π¿∫ ¥Î∏∏ø°º≠¥¬ «–ø¯∞£ ¿⁄¿ØPK¿œ ∞ÊøÏ ¿˚¥Î¿⁄∞° ±‚«œ±ﬁºˆ¿˚¿∏∑Œ ¥√æÓ≥™∏Á
	//			∫“æ»«— º∫¥…¿ª ∞°¡¯ HASH_MAP¿ª ªÁøÎ«œ¥¬ «ˆ µ•¿Ã≈∏ ±∏¡∂∑Œº≠¥¬ ªÁøÎ«œ±‚ ∫“∞°¥…«œ¥Ÿ.			            
	if ( !(bBRIGHTEVENT||bSCHOOL_FREEPK||bGuidBattleMap||bClubDeathMatch||bSchoolWars||bRoyalRumble||bTowerWars ) )
	{
		//	Note : ¿˚?E«‡¿ß¿⁄ µ˚”œ. ( pk )
		ADD_PLAYHOSTILE ( dwCHARID, bBAD );
	}
	// «–ø¯∞£ ¿⁄¿Ø««ƒ…¿Ã ¡¯«‡¡ﬂ¿Ã?EªÛ?E?∞∞¿∫ «–±≥¿œ∞Ê?E¿˚?E‡¿??EÛ¿⁄∑?±∏∫–«œø© ?EÆ«?
	if ( GLSchoolFreePK::GetInstance().IsON() && !bSCHOOL_FREEPK )
	{
		ADD_PLAYHOSTILE ( dwCHARID, bBAD );
	}

	// «–ø¯∞£ ¿⁄¿Ø««ƒ…¿Ã ¡¯«‡¡ﬂ ªÛ?E?∑æ¿Ã 20∫∏¥Ÿ ≥∑¿ª∂ß ¿˚?E‡¿??EÛ¿⁄∑?±∏∫–«œø© ?EÆ«?
	if ( bSCHOOL_FREEPK )
	{
		if ( pCHAR->GetLevel() < GLCONST_CHAR::nPK_LIMIT_LEVEL || GetLevel() < GLCONST_CHAR::nPK_LIMIT_LEVEL )
		{
			ADD_PLAYHOSTILE ( dwCHARID, bBAD );
		}
	}

	//	Note : ¿˚?E?µ˚”œ æÀ∏≤.
	GLMSG::SNETPC_PLAYERKILLING_ADD NetMsgAdd;
	NetMsgAdd.dwCharID = dwCHARID;
	NetMsgAdd.wSchoolID = pCHAR->m_wSchool;
	NetMsgAdd.bBAD = bBAD;
	NetMsgAdd.bClubBattle = bClubBattle;
	NetMsgAdd.fTime = 0.0f;

	StringCchCopy ( NetMsgAdd.szName, CHAR_SZNAME, pCHAR->m_szName );

	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgAdd);
}

// *****************************************************
// Desc: ?E√¡ﬂ¿??EÛ¿Œ¡ÅECheck
// *****************************************************
bool GLChar::IsConflictTarget ( GLACTOR* pTARGET )
{
	//GASSERT(pTARGET&&"GLChar::IsConflictTarget()");
	if ( !pTARGET )				return false;

	EMCROW emCROW = pTARGET->GetCrow();
	if ( emCROW!=CROW_PC )		return false;

	SCONFTING* pCONFTING = pTARGET->GETCONFTING();
	if ( !pCONFTING )			return false;

	if ( m_sCONFTING.IsFIGHTING() && pCONFTING->IsFIGHTING() )
	{
		if ( m_sCONFTING.emTYPE!=pCONFTING->emTYPE )	return false;

		switch ( pCONFTING->emTYPE )
		{
		case EMCONFT_ONE:
			return ( m_dwGaeaID==pCONFTING->dwTAR_ID );

		case EMCONFT_PARTY:
			return ( m_dwPartyID==pCONFTING->dwTAR_ID );

		case EMCONFT_GUILD:
			return ( m_dwGuild==pCONFTING->dwTAR_ID );
		};
	}

	return false;
}

// *****************************************************
// Desc: æ◊º«¿ª ?E??E¿÷¥¬ ?EÛ¿Œ¡ÅEcheck
// *****************************************************
bool GLChar::IsReActionable ( GLACTOR* pTARGET, bool benermy )
{
	GASSERT(pTARGET&&"GLChar::IsReActionable()");
	if ( !pTARGET )					return false;
	if ( !m_pLandMan )				return false;

	// º∫«‚¿Ã∫•∆Æ ¡ﬂ¿Œ?E
	bool bBRIGHTEVENT = m_pGLGaeaServer->IsBRIGHTEVENT();

	EMCROW emCROW = pTARGET->GetCrow();
	bool bPKZone = m_pLandMan->IsPKZone();
	bool bGuidBattleMap = m_pLandMan->m_bGuidBattleMap;
	bool bClubDeathMatch = m_pLandMan->m_bClubDeathMatchMap;
	bool bSchoolWars = m_pLandMan->m_bSchoolWarsMap;
	bool bRoyalRumble = m_pLandMan->m_bRoyalRumbleMap;
	bool bSCHOOL_FREEPK = GLSchoolFreePK::GetInstance().IsON();
	bool bClubBattleZone = m_pLandMan->IsClubBattleZone();

	bool bTowerWars = m_pLandMan->m_bTowerWarsMap;

	//
	//juver battle royale
	bool bRedZone = m_pLandMan->IsRedZone();

	PGLCROW pCrow = m_pLandMan->GetCrow ( pTARGET->GetCtrlID() );
	
	//if ( GetSchool() == pTARGET->GetSchool() )	bSCHOOL_FREEPK = false;
	if ( GetSchool() == pTARGET->GetSchool() )
	{
		if ( bRedZone )
		{
			bSCHOOL_FREEPK = true;
		}
		if ( bRoyalRumble )
		{
			bSCHOOL_FREEPK = true;
		}
		else
		{
			bSCHOOL_FREEPK = false;
		}
	}

	bool bREACTION(true);

	// ªÛ?E?¿˚¿Œ ∞Ê?E
	if ( benermy )
	{
		switch ( emCROW )
		{
		case CROW_PC:
			// Absolute Non-PK State Check.
			if ( GLCONST_CHAR::bPKLESS ) return false;

			// Desc : ¿˝?Eæ»?E?Ω√∞£ (10√ )
			if ( !pTARGET->IsSafeTime() && !IsSafeTime() && !pTARGET->IsSafeZone() && !IsSafeZone() )
			{
				// ∞∞¿∫ ∆ƒ∆º¿« ∏‚πˆ¿Œ?E
				GLPartyFieldMan& sPartyFieldMan = m_pGLGaeaServer->GetPartyMan();
				GLPARTY_FIELD* sMyParty = sPartyFieldMan.GetParty ( m_dwPartyID );
				if ( sMyParty )
				{
					if ( sMyParty->ISMEMBER ( pTARGET->GetCtrlID() ) )
					{
						return false;
					}
				}

				// º≠∑Œ ?E√¡ﬂ¿Œ¡ÅE
				bREACTION = IsConflictTarget ( pTARGET );
				if ( !bREACTION )
				{
					SCONFTING* pCONFTING = pTARGET->GETCONFTING();
					if ( m_sCONFTING.IsCONFRONTING() || pCONFTING->IsCONFRONTING() )
					{
						return false;
					}
				}
				else
				{
					return true;
				}

				// ¿˚?EÅEË¿Œ¡ÅE√º≈©
				DWORD dwCHARID = pTARGET->GetCharID();
				bREACTION = IS_PLAYHOSTILE ( dwCHARID );
				if ( bREACTION ) return true;
	
				// 20 Lev ¿ÃªÛ¿œ∂ß
				if ( pTARGET->GetLevel() >= GLCONST_CHAR::nPK_LIMIT_LEVEL && GLCONST_CHAR::bPK_MODE && bPKZone)
				{
					// PK ∞°¥…«— ±∏ø™ ( «–±≥∞£ Free PK )
					if ( bSCHOOL_FREEPK )											return true;
					
					// º∫?E¿Ã∫•∆Æ ¡ﬂ¿Ã?E
					if ( bBRIGHTEVENT && ( m_dwPartyID != pTARGET->GetPartyID() ) )	return true;
											
					// ±◊≥… ∞≠¡¶∞¯∞›
					bREACTION = true;		
				}

				PGLCHAR pChar = m_pGLGaeaServer->GetChar( pTARGET->GetCtrlID() );
				GLClubMan &cClubMan = m_pGLGaeaServer->GetClubMan();
				GLCLUB *pMyClub = cClubMan.GetClub ( m_dwGuild );
				GLCLUB *pTarClub = NULL;
				if ( pChar ) pTarClub = cClubMan.GetClub ( pChar->m_dwGuild );

				// º±µµ?E°º?∞∞¿∫ µø∏Õ ≈¨∑¥¿Ã?E∞¯∞› ∫“∞°¥…
				if ( GLCONST_CHAR::bPK_MODE )
				{
					if ( bGuidBattleMap )
					{
						bREACTION = true;

						if ( pMyClub && pTarClub )
						{
							BOOL bAlliance = pMyClub->IsAllianceGuild ( pTarClub->m_dwID );
							if ( bAlliance )	bREACTION = false;
						} // end of if
					}
					else if ( bClubDeathMatch )
					{
						if ( m_dwGuild == pChar->m_dwGuild ) bREACTION = false;
						else bREACTION = true;
					}
					else if ( bSchoolWars || bTowerWars )
					{
						if ( m_wSchool == pChar->m_wSchool ) bREACTION = false;
						else bREACTION = true;
					}

					else if ( bRoyalRumble )
					{
						bREACTION = true;
					}

					if ( bPKZone && bClubBattleZone )
					{
						if ( pMyClub && pTarClub )
						{
							if ( pMyClub->IsBattle( pTarClub->m_dwID ) ) return true;
							if ( pMyClub->IsBattleAlliance( pTarClub->m_dwAlliance ) ) return true;
						}
					}
				}

			} // end of if
			else
				bREACTION = false;
			break;
		
		case CROW_SUMMON:
		case CROW_MOB:	
			if ( pCrow ) //add mobschoolreq
			{
				if ( !(pCrow->m_pCrowData->m_sAction.dwMobReqSchool & index2school(m_wSchool) ) ) 
				{
					bREACTION = false;
				}
				else if ( m_sCONFTING.IsCONFRONTING() )	bREACTION = false;
				else if ( IsSafeZone() ) 	bREACTION = false;
				else 
				{
					bREACTION = true;
	
					if ( m_pLandMan && m_pLandMan->m_bTowerWarsMap )
					{
						PGLCROW pCrow = m_pLandMan->GetCrow ( pTARGET->GetCtrlID() );
						if ( pCrow->m_emOWNER == m_wSchool )
							bREACTION = false;
					}
				}
			}
			else
			{
				if ( m_sCONFTING.IsCONFRONTING() )	bREACTION = false;
				else if ( IsSafeZone() ) 	bREACTION = false;
				else 
				{
					bREACTION = true;
	
					if ( m_pLandMan && m_pLandMan->m_bTowerWarsMap )
					{
						PGLCROW pCrow = m_pLandMan->GetCrow ( pTARGET->GetCtrlID() );
						if ( pCrow->m_emOWNER == m_wSchool )
							bREACTION = false;
					}
				}
			}
			break;

		case CROW_NPC:
			bREACTION = false;
			break;

		case CROW_MATERIAL:
			bREACTION = false;
			break;

		//case CROW_PET:	break;	// PetData

		default:
			bREACTION = false;
			break;
		};
	}
	// ªÛ?E?¿˚¿Ã æ∆¥— ∞Ê?E
	else
	{
		switch ( emCROW )
		{
		case CROW_PC:
			{
				//	pc ø°∞‘ ∫Ò∞¯∞› ∏∂π˝ ∞∞¿∫ ∞Õ¿∫ ?E√¿⁄∞?æ∆¥“ ∂ß∏∏ ∞°¥….
				bREACTION = !IsConflictTarget ( pTARGET );

				//	ªÛ?EÊ¿??E√¡ﬂ¿?∂ß¥¬ ¿⁄±‚∞° ?E√¡ﬂ¿Ã∞ÅE∞∞¿∫ ∆˙‹œ∂ß ∞°¥….
				SCONFTING* pTAR_CONFT = pTARGET->GETCONFTING();
				if ( pTAR_CONFT->IsCONFRONTING() )
				{
					bREACTION = m_sCONFTING.IsSAMENESS(pTAR_CONFT->emTYPE,pTAR_CONFT->dwTAR_ID);
				}

				bool bHOSTILE = IS_PLAYHOSTILE ( pTARGET->GetCharID() );
				if ( bHOSTILE )	bREACTION = false;
			}
			break;
		
		case CROW_SUMMON:
		case CROW_MOB:
			bREACTION = false;
			break;

		case CROW_NPC:
			bREACTION = m_sCONFTING.IsCONFRONTING() ? false : true;
			break;

		case CROW_MATERIAL:
			bREACTION = true;
			break;

		//case CROW_PET:	break;	// PetData

		default:
			bREACTION = false;
			break;
		};
	}

	return bREACTION;
}


inline DWORD GLChar::ToDamage ( const STARGETID &sTargetID, const int nDAMAGE, const BOOL bShock )
{
	GLACTOR* pACTOR_TAR = m_pGLGaeaServer->GetTarget ( m_pLandMan, sTargetID );
	if ( !pACTOR_TAR )	return 0;

	//	Note : PCø°∞‘ damage∏¶ ¡÷∑¡?E?E√¿⁄ø©æ?∞°¥….
	//		?E?¡æ?E¡˜»ƒ damage ¿Ø¿‘ ¬˜¥‹¿ª ¿ß«ÿº≠.
	//
	if ( !IsReActionable(pACTOR_TAR) )	return 0;

	return pACTOR_TAR->ReceiveDamage ( GETCROW(), m_dwGaeaID, nDAMAGE, bShock );
}

void GLChar::PreStrikeProc ( BOOL bSkill, BOOL bLowSP )
{
	SANIATTACK sAniAttack;
	STARGETID sTargetID;

	BOOL bCheckHit = FALSE;

	if ( !bSkill )
	{
		EMSLOT emRHand = GetCurRHand();
		EMSLOT emLHand = GetCurLHand();

		EMANI_SUBTYPE emANISUBTYPE = CHECK_ATTACK_ANISUB ( m_pITEMS[emRHand], m_pITEMS[emLHand] );

		GLCONST_CHARCLASS &ConstCharClass = GLCONST_CHAR::cCONSTCLASS[m_CHARINDEX];
		VECANIATTACK &vecAniAttack = ConstCharClass.m_ANIMATION[AN_ATTACK][emANISUBTYPE];
		if ( vecAniAttack.empty() )	return; // FALSE;

		//	Note : ∆Ø¡§ ∞¯∞› ø°¥œ∏ﬁ¿Ãº« º≥¡§ º±≈√.
		//
		sAniAttack = vecAniAttack[0];

		sTargetID = m_TargetID;
		bCheckHit = TRUE;
	}
	else
	{
		//	Note : Ω∫≈≥ ¡§∫∏ ∞°¡Æø».
		//
		PGLSKILL pSkill = NULL;
		pSkill = GLSkillMan::GetInstance().GetData ( m_idACTIVESKILL.wMainID, m_idACTIVESKILL.wSubID );

		GLCONST_CHARCLASS &ConstCharClass = GLCONST_CHAR::cCONSTCLASS[m_CHARINDEX];
		VECANIATTACK &vecAniAttack = ConstCharClass.m_ANIMATION[pSkill->m_sEXT_DATA.emANIMTYPE][pSkill->m_sEXT_DATA.emANISTYPE];
		if ( vecAniAttack.empty() )	return; // FALSE;

		//	Note : ∆Ø¡§ ∞¯∞› ø°¥œ∏ﬁ¿Ãº« º≥¡§ º±≈√.
		//
		sAniAttack = vecAniAttack[0];

		if ( pSkill->m_sBASIC.emAPPLY != SKILL::EMAPPLY_MAGIC )
		{
			//	Note : Ω∫≈≥ ≈∏∞Ÿ¿ª «œ≥™∏∏ ¿Ø»ø«œ∞‘ »Æ¿Œ¿ª «œ?E¿÷¿Ω.
			//	NEED : ¥Ÿ¡ﬂ ≈∏∞Ÿ¿œ ∞Ê?E¥ŸΩ√ »Æ¿Œ«ÿæﬂ«‘.
			sTargetID = STARGETID(static_cast<EMCROW>(m_sTARIDS[0].wCrow),static_cast<DWORD>(m_sTARIDS[0].wID));
			bCheckHit = TRUE;
		}
		else
		{
			sTargetID.dwID = EMTARGET_NULL;
		}
	}

	//	≈• √ ±‚»≠
	m_sHITARRAY.clear ();

	for ( int i = 0; i < sAniAttack.m_wDivCount; i++ )
	{
		bool bhit = true;
		if ( bCheckHit && (sTargetID.dwID!=EMTARGET_NULL) )
		{
			if ( !CHECKHIT(sTargetID,m_pLandMan,bLowSP) )		bhit = false;
		}

		m_sHITARRAY.push_back ( SSTRIKE(sAniAttack.m_wDivFrame[i],bhit,cast_bool(bLowSP)) );
	}
}

void GLChar::AvoidProc ( const SNATIVEID skill_id, const BOOL bLowSP )
{
	//CONSOLEMSG_WRITE( "AvoidProc Start [%u]", skill_id.dwID );

	if ( skill_id==NATIVEID_NULL() )
	{
		if ( !bLowSP )
		{
			WORD wDisSP = m_wSUM_DisSP + GLCONST_CHAR::wBASIC_DIS_SP;
			m_sSP.DECREASE ( wDisSP );
		}

		GLACTOR *pACTOR = m_pGLGaeaServer->GetTarget ( m_pLandMan, m_TargetID );
		if ( pACTOR )	pACTOR->ReceiveDamage ( CROW_PC, m_dwGaeaID, 0, FALSE);
	}
	else
	{
		//	Note : SP∞° ∫Œ¡∑«œ?Eæ ¿ª∂ßø°¥¬ SP º“∏Ω√≈¥.
		//
		if ( !bLowSP )
		{
			//	Note : ƒ≥∏Ø≈Õ∞° πË?EΩ∫≈≥ ¡§∫∏ ∞°¡Æø».
			SKILL_MAP_ITER learniter = m_ExpSkills.find ( skill_id.dwID );
			if( learniter==m_ExpSkills.end() )								return;	// πË?EΩ∫≈≥¿Ã æ∆¥“ ∞Ê?E
			SCHARSKILL &sSkill = (*learniter).second;

			//	Ω∫≈≥ ¡§∫∏ ∞°¡Æø».
			PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
			if ( !pSkill )													return;
			SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[sSkill.wLevel];

			WORD wDisSP = m_wSUM_DisSP + sSKILL_DATA.wUSE_SP;
			m_sSP.DECREASE ( wDisSP );
		}

		for ( WORD i=0; i<m_wTARNUM; ++i )
		{
			STARGETID sTargetID ( (EMCROW)m_sTARIDS[i].wCrow, (WORD)m_sTARIDS[i].wID );

			GLACTOR *pACTOR = m_pGLGaeaServer->GetTarget ( m_pLandMan, sTargetID );
			if ( pACTOR )	pACTOR->ReceiveDamage ( CROW_PC, m_dwGaeaID, 0, FALSE);
		}
	}

	//	Note : ¿⁄Ω≈ø°∞‘.
	GLMSG::SNETPC_ATTACK_AVOID NetMsg;
	NetMsg.emTarCrow	= m_TargetID.emCrow;
	NetMsg.dwTarID		= m_TargetID.dwID;

	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsg );

	//	Note : ¡÷∫Ø ≈¨∂Û¿Ãæ∆ÆµÈø°∞‘ ∏ﬁºº?E?E?
	//
	GLMSG::SNETPC_ATTACK_AVOID_BRD NetMsgBrd;
	NetMsgBrd.dwGaeaID	= m_dwGaeaID;
	NetMsgBrd.emTarCrow	= m_TargetID.emCrow;
	NetMsgBrd.dwTarID	= m_TargetID.dwID;

	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
}

void GLChar::DamageProc ( int nDAMAGE, const DWORD dwDamageFlag, const BOOL bLowSP )
{
	//	Note : µ•πÃ?E?EÅE
	//				( sp ∫Œ¡∑Ω√ µ•πÃ?E∞®?E )
	float	fDAMAGE_RATE(1.0f);
	if ( bLowSP )						fDAMAGE_RATE *= (1-GLCONST_CHAR::fLOWSP_DAMAGE);

	nDAMAGE = int(nDAMAGE*fDAMAGE_RATE);
	if ( nDAMAGE < 1 )	nDAMAGE = 1;

	// ?E?¡æ∑·»ƒ π´¿˚≈∏¿”¿Ã?E∞¯∞› π´Ω√
	PGLCHAR pCHAR = m_pGLGaeaServer->GetChar ( m_TargetID.dwID );
	if ( pCHAR )
	{
		if ( pCHAR->m_sCONFTING.IsPOWERFULTIME () )
			return;
	}

	//	Note : SP º“?E
	//
	if ( !bLowSP )
	{
		WORD wDisSP = m_wSUM_DisSP + GLCONST_CHAR::wBASIC_DIS_SP;
		m_sSP.DECREASE ( wDisSP );

		GLMSG::SNETPC_UPDATE_SP NetMsg;
		NetMsg.wNowSP = m_sSP.dwNow;
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
	}

	if ( m_TargetID.emCrow==CROW_PC )
	{
		nDAMAGE = int(nDAMAGE*GLCONST_CHAR::fPK_POINT_DEC_PHY);
		if ( nDAMAGE==0 )	nDAMAGE = 1;
	}

	//	Note : ?EÛ¿⁄ø°∞??EÃ¡ˆ∞?¿˚?E
	//
	bool bShock = ( dwDamageFlag & DAMAGE_TYPE_SHOCK );
	ToDamage ( m_TargetID, nDAMAGE, bShock );

	//	Note : ¿⁄Ω≈ø°∞‘.
	GLMSG::SNETPC_ATTACK_DAMAGE NetMsg;
	NetMsg.emTarCrow		= m_TargetID.emCrow;
	NetMsg.dwTarID			= m_TargetID.dwID;
	NetMsg.nDamage			= nDAMAGE;
	NetMsg.dwDamageFlag		= dwDamageFlag;
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsg );

	//	Note : ¡÷∫Ø ≈¨∂Û¿Ãæ∆ÆµÈø°∞‘ ∏ﬁºº?E?E?
	//
	GLMSG::SNETPC_ATTACK_DAMAGE_BRD NetMsgBrd;
	NetMsgBrd.dwGaeaID		= m_dwGaeaID;
	NetMsgBrd.emTarCrow		= m_TargetID.emCrow;
	NetMsgBrd.dwTarID		= m_TargetID.dwID;
	NetMsgBrd.nDamage		= nDAMAGE;
	NetMsgBrd.dwDamageFlag	= dwDamageFlag;
	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );

	GLACTOR* pACTOR = m_pGLGaeaServer->GetTarget ( m_pLandMan, m_TargetID );
	if ( !pACTOR )	return;

	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();

	//	Note : ªÛ≈¬ ¿Ã?E¿Øπﬂ.
	//
	SITEM* pRHandItem = GET_SLOT_ITEMDATA(emRHand);
	SITEM* pLHandItem = GET_SLOT_ITEMDATA(emLHand);

	if ( pRHandItem && pRHandItem->sSuitOp.sBLOW.emTYPE!=EMBLOW_NONE )
	{
		ITEM::SSATE_BLOW &sBlow = pRHandItem->sSuitOp.sBLOW;

		//	Note : πﬂª˝ »Æ¿≤ ∞Ë?E
		//
		short nBLOWRESIST = pACTOR->GETRESIST().GetElement ( STATE_TO_ELEMENT(sBlow.emTYPE) );
		if ( nBLOWRESIST>99 )	nBLOWRESIST = 99;

//		float fPOWER = GLOGICEX::WEATHER_BLOW_POW ( sBlow.emTYPE, GLPeriod::GetInstance().GetWeather(), m_pLandMan->IsWeatherActive() );
		DWORD dwWeather = GLPeriod::GetInstance().GetMapWeather( m_pLandMan->GetMapID().wMainID, m_pLandMan->GetMapID().wSubID );
		float fPOWER = GLOGICEX::WEATHER_BLOW_POW ( sBlow.emTYPE, dwWeather, m_pLandMan->IsWeatherActive() );

		BOOL bBLOW = FALSE;
		if ( !(pACTOR->GETHOLDBLOW()&STATE_TO_DISORDER(sBlow.emTYPE)) )
			bBLOW = GLOGICEX::CHECKSTATEBLOW ( sBlow.fRATE*fPOWER, GETLEVEL(), pACTOR->GetLevel(), nBLOWRESIST );

		if ( bBLOW )
		{
			//	Note : ªÛ≈¬¿Ã?Eπﬂª˝.
			//	
			SSTATEBLOW sSTATEBLOW;
			float fLIFE = sBlow.fLIFE * fPOWER;
			fLIFE = ( fLIFE - (fLIFE*nBLOWRESIST/100.0f*GLCONST_CHAR::fRESIST_G ) );

			sSTATEBLOW.emBLOW = sBlow.emTYPE;
			sSTATEBLOW.fAGE = fLIFE;
			sSTATEBLOW.fSTATE_VAR1 = sBlow.fVAR1;
			sSTATEBLOW.fSTATE_VAR2 = sBlow.fVAR2;

			pACTOR->STATEBLOW ( sSTATEBLOW );

			//	Note : ªÛ≈¬¿Ã?Eπﬂª˝ Msg.
			//
			GLMSG::SNETPC_STATEBLOW_BRD NetMsgState;
			NetMsgState.emCrow = m_TargetID.emCrow;
			NetMsgState.dwID = m_TargetID.dwID;
			NetMsgState.emBLOW = sBlow.emTYPE;
			NetMsgState.fAGE = fLIFE;
			NetMsgState.fSTATE_VAR1 = sBlow.fVAR1;
			NetMsgState.fSTATE_VAR2 = sBlow.fVAR2;

			//	Note : 'Ω∫≈≥?EÅE¿« ¡÷∫Ø ≈¨∂Û¿Ãæ∆ÆµÈø°∞‘ ∏ﬁºº?E?E?
			//
			pACTOR->SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsgState );

			//	Note : Ω∫≈≥ ?EÛø°∞?∏ﬁºº?E?E?
			if ( m_TargetID.emCrow==CROW_PC )	m_pGLGaeaServer->SENDTOCLIENT ( pACTOR->GETCLIENTID (), &NetMsgState );
		}
	}
	else if ( pLHandItem && pLHandItem->sSuitOp.sBLOW.emTYPE!=EMBLOW_NONE )
	{
		ITEM::SSATE_BLOW &sBlow = pLHandItem->sSuitOp.sBLOW;

		//	Note : πﬂª˝ »Æ¿≤ ∞Ë?E
		//
		short nBLOWRESIST = pACTOR->GETRESIST().GetElement ( STATE_TO_ELEMENT(sBlow.emTYPE) );
		if ( nBLOWRESIST>99 )	nBLOWRESIST = 99;

//		float fPOWER = GLOGICEX::WEATHER_BLOW_POW ( sBlow.emTYPE, GLPeriod::GetInstance().GetWeather(), m_pLandMan->IsWeatherActive() );
		DWORD dwWeather = GLPeriod::GetInstance().GetMapWeather( m_pLandMan->GetMapID().wMainID, m_pLandMan->GetMapID().wSubID );
		float fPOWER = GLOGICEX::WEATHER_BLOW_POW ( sBlow.emTYPE, dwWeather, m_pLandMan->IsWeatherActive() );

		BOOL bBLOW = FALSE;
		if ( !(pACTOR->GETHOLDBLOW()&STATE_TO_DISORDER(sBlow.emTYPE)) )
			bBLOW = GLOGICEX::CHECKSTATEBLOW ( sBlow.fRATE*fPOWER, GETLEVEL(), pACTOR->GetLevel(), nBLOWRESIST );

		if ( bBLOW )
		{
			//	Note : ªÛ≈¬¿Ã?Eπﬂª˝.
			//	 
			SSTATEBLOW sSTATEBLOW;
			float fLIFE = sBlow.fLIFE * fPOWER;
			fLIFE = ( fLIFE - (fLIFE*nBLOWRESIST/100.0f*GLCONST_CHAR::fRESIST_G ) );

			sSTATEBLOW.emBLOW = sBlow.emTYPE;
			sSTATEBLOW.fAGE = fLIFE;
			sSTATEBLOW.fSTATE_VAR1 = sBlow.fVAR1;
			sSTATEBLOW.fSTATE_VAR2 = sBlow.fVAR2;

			pACTOR->STATEBLOW ( sSTATEBLOW );

			//	Note : ªÛ≈¬¿Ã?Eπﬂª˝ Msg.
			//
			GLMSG::SNETPC_STATEBLOW_BRD NetMsgState;
			NetMsgState.emCrow = m_TargetID.emCrow;
			NetMsgState.dwID = m_TargetID.dwID;
			NetMsgState.emBLOW = sBlow.emTYPE;
			NetMsgState.fAGE = fLIFE;
			NetMsgState.fSTATE_VAR1 = sBlow.fVAR1;
			NetMsgState.fSTATE_VAR2 = sBlow.fVAR2;

			//	Note : 'Ω∫≈≥?EÅE¿« ¡÷∫Ø ≈¨∂Û¿Ãæ∆ÆµÈø°∞‘ ∏ﬁºº?E?E?
			//
			pACTOR->SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsgState );

			//	Note : Ω∫≈≥ ?EÛø°∞?∏ﬁºº?E?E?
			if ( m_TargetID.emCrow==CROW_PC )	m_pGLGaeaServer->SENDTOCLIENT ( pACTOR->GETCLIENTID (), &NetMsgState );
		}
	}

	// ∞≠«— ≈∏∞›
	if ( dwDamageFlag & DAMAGE_TYPE_CRUSHING_BLOW ) 
	{
		STARGETID dwActorID = STARGETID(CROW_PC,m_dwGaeaID);
		m_pLandMan->PushPullAct( dwActorID, m_TargetID, GLCONST_CHAR::fCRUSH_BLOW_RANGE, 0.0f, false, false, false, false ); //add pushpull //modify //add dash //add teleport
	}
}

void GLChar::DamageReflectionProc ( int nDAMAGE, STARGETID sACTOR )
{
	if ( sACTOR.emCrow==CROW_PC )
	{
		nDAMAGE = int(nDAMAGE*GLCONST_CHAR::fPK_POINT_DEC_PHY);
		if ( nDAMAGE==0 )	nDAMAGE = 1;
	}

	ToDamage ( sACTOR, nDAMAGE, FALSE );

	//	Note : ¿⁄Ω≈ø°∞‘.
	GLMSG::SNETPC_ATTACK_DAMAGE NetMsg;
	NetMsg.emTarCrow		= sACTOR.emCrow;
	NetMsg.dwTarID			= sACTOR.dwID;
	NetMsg.nDamage			= nDAMAGE;
	NetMsg.dwDamageFlag		= DAMAGE_TYPE_NONE;
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsg );

	//	Note : ¡÷∫Ø ≈¨∂Û¿Ãæ∆ÆµÈø°∞‘ ∏ﬁºº?E?E?
	//
	GLMSG::SNETPC_ATTACK_DAMAGE_BRD NetMsgBrd;
	NetMsgBrd.dwGaeaID		= m_dwGaeaID;
	NetMsgBrd.emTarCrow		= sACTOR.emCrow;
	NetMsgBrd.dwTarID		= sACTOR.dwID;
	NetMsgBrd.nDamage		= nDAMAGE;
	NetMsgBrd.dwDamageFlag	= DAMAGE_TYPE_NONE;
	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
}

void GLChar::DefenseSkill( SNATIVEID sNativeID, WORD wLevel, STARGETID sACTOR )
{
	if ( sNativeID == NATIVEID_NULL() ) return;

	GLMSG::SNETPC_DEFENSE_SKILL_ACTIVE NetMsg;
	NetMsg.emTarCrow = sACTOR.emCrow;
	NetMsg.dwTarID = sACTOR.dwID;
	NetMsg.sNativeID = sNativeID;
	NetMsg.wLevel = wLevel;
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsg );

	m_bDefenseSkill	= true;

    return;
}

BOOL GLChar::AttackProcess ( float fElapsedTime )
{
	m_fattTIMER += fElapsedTime*GLCHARLOGIC::GETATTVELO();
	m_fattTIMER += GLCHARLOGIC::GETATT_ITEM();

	GLCONST_CHARCLASS &ConstCharClass = GLCONST_CHAR::cCONSTCLASS[m_CHARINDEX];

	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();

	EMANI_SUBTYPE emANISUBTYPE = CHECK_ATTACK_ANISUB ( m_pITEMS[emRHand], m_pITEMS[emLHand] );
	VECANIATTACK &vecAniAttack = ConstCharClass.m_ANIMATION[AN_ATTACK][emANISUBTYPE];
	if ( vecAniAttack.empty() )	return FALSE;

	//	Note : ∞¯∞› ∏º« ¡æ∑˘∞° ∫Ø∞Êµ» ∞Õ¿∏∑Œ ∫∏¿”. ∞¯∞› ?E? ( ¿Â?E¬˚≈π. )
	//
	if ( vecAniAttack.size() <= m_dwANISUBSELECT )
	{
		TurnAction ( GLAT_IDLE );

		//GLMSG::SNET_ACTION_BRD NetMsgBrd;
		//NetMsgBrd.emCrow = CROW_PC;
		//NetMsgBrd.dwID = m_dwGaeaID;
		//NetMsgBrd.emAction = GLAT_IDLE;
		//m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBrd );

		//SendMsgViewAround ( (NET_MSG_GENERIC *) &NetMsgBrd );

		return FALSE;
	}

	if ( !ISLONGRANGE_ARMS() )
	{
		GLACTOR *pTARGET = m_pGLGaeaServer->GetTarget ( m_pLandMan, m_TargetID );
		if ( !pTARGET )
		{
			TurnAction ( GLAT_IDLE );

			//	Note : ¿⁄Ω≈ø°∞‘.
			GLMSG::SNETPC_ATTACK_DAMAGE NetMsg;
			NetMsg.emTarCrow		= m_TargetID.emCrow;
			NetMsg.dwTarID			= m_TargetID.dwID;
			NetMsg.nDamage			= 0;
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsg );
			SendMsgViewAround ( (NET_MSG_GENERIC *) &NetMsg );

			////	Note : ∏º« ∫Ø?E
			//GLMSG::SNET_ACTION_BRD NetMsgBrd;
			//NetMsgBrd.emCrow = CROW_PC;
			//NetMsgBrd.dwID = m_dwGaeaID;
			//NetMsgBrd.emAction = GLAT_IDLE;
			//m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBrd );

			////	Note : ∏º« ∫Ø?E(∏µŒø°∞‘).
			//SendMsgViewAround ( (NET_MSG_GENERIC *) &NetMsgBrd );

			return FALSE;
		}

		D3DXVECTOR3 vDist = m_vPos - pTARGET->GetPosition();
		float fTarLength = D3DXVec3Length(&vDist);

		WORD wAttackRange = pTARGET->GetBodyRadius() + GETBODYRADIUS() + GETATTACKRANGE() + 2;
		if ( wAttackRange*GLCONST_CHAR::fREACT_VALID_SCALE < (WORD)(fTarLength) )
		{
			TurnAction ( GLAT_IDLE );

			//	Note : ¿⁄Ω≈ø°∞‘.
			GLMSG::SNETPC_ATTACK_DAMAGE NetMsg;
			NetMsg.emTarCrow		= m_TargetID.emCrow;
			NetMsg.dwTarID			= m_TargetID.dwID;
			NetMsg.nDamage			= 0;
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsg );
			SendMsgViewAround ( (NET_MSG_GENERIC *) &NetMsg );

			////	Note : ∏º« ∫Ø?E
			//GLMSG::SNET_ACTION_BRD NetMsgBrd;
			//NetMsgBrd.emCrow = CROW_PC;
			//NetMsgBrd.dwID = m_dwGaeaID;
			//NetMsgBrd.emAction = GLAT_IDLE;
			//m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBrd );

			////	Note : ∏º« ∫Ø?E(∏µŒø°∞‘).
			//SendMsgViewAround ( (NET_MSG_GENERIC *) &NetMsgBrd );

			return FALSE;
		}
	}


	//	Note : ∆Ø¡§ ∞¯∞› ø°¥œ∏ﬁ¿Ãº« º≥¡§ º±≈√.
	//
	const SANIATTACK &sAniAttack = vecAniAttack[m_dwANISUBSELECT];

	DWORD dwThisKey = sAniAttack.m_dwSTime + DWORD(m_fattTIMER*UNITANIKEY_PERSEC);
	
	if ( !m_sHITARRAY.empty() )
	{
		SSTRIKE sStrike = *m_sHITARRAY.begin();

		if ( dwThisKey >= sStrike.wDivKey )
		{
			if ( sStrike.bHit )
			{
				int nDamage = 0;
				DWORD dwDamageFlag = DAMAGE_TYPE_NONE;
				dwDamageFlag = CALCDAMAGE ( nDamage, m_dwGaeaID, m_TargetID, m_pLandMan );

				DamageProc ( nDamage, dwDamageFlag, sStrike.bLowSP );
			}
			else
			{
				AvoidProc ( NATIVEID_NULL(), sStrike.bLowSP );
			}

			//	≈• µ•¿Ã≈∏∞° √≥∏Æµ» ∞Ê?EªË¡¶«—¥Ÿ.
			m_sHITARRAY.pop_front ();
		}	
	}

	//	¿ÃªÛ¡ıªÛø° ¿««ÿ µ•¿Ã≈∏∞° ?EÅE√≥∏Æµ«?Eæ ¿∫∞Ê?E
	//	∏∂¡ˆ∏∑ø° «—≤®π¯ø° √≥∏Æ«œ?E FALSE∏¶ ∏Æ≈œ«—¥Ÿ.
	if ( dwThisKey >= sAniAttack.m_dwETime )
	{
		if ( !m_sHITARRAY.empty() )
		{
			while ( !m_sHITARRAY.empty() )
			{
				SSTRIKE sStrike = *m_sHITARRAY.begin();
				
				if ( sStrike.bHit )
				{
					int nDamage = 0;
					DWORD dwDamageFlag = DAMAGE_TYPE_NONE;
					dwDamageFlag = CALCDAMAGE ( nDamage, m_dwGaeaID, m_TargetID, m_pLandMan );
					DamageProc ( nDamage, dwDamageFlag, sStrike.bLowSP );
				}
				else
				{
					AvoidProc ( NATIVEID_NULL(), sStrike.bLowSP );
				}

				//	≈• µ•¿Ã≈∏∞° √≥∏Æµ» ∞Ê?EªË¡¶«—¥Ÿ.
				m_sHITARRAY.pop_front ();
			}
		}

		return FALSE;
	}

	//	Note : æ∆?E∞¯∞›¿Ã ¡æ?Eµ«?Eæ æ“¿∏≥™ hit¥¬ øœ∑·µÃ?Eø°¥œ≈∞∞° ¿œ¡§ ºˆ∑Æ ¿Ã«œ¿œ ∞Ê?E
	//		∞¯∞›¿Ã ¡æ∑·µ»∞…∑Œ ∞£¡÷. ( ≈¨∂Û¿Ãæ∆ÆøÕ º≠πˆ∞£ø° µÙ∑π¿Ã ∞®æ». )
	if ( m_sHITARRAY.empty() )
	{
		//DWORD dwDISKEY = sAniAttack.m_dwETime - dwThisKey;
		//if ( dwDISKEY <= 5 )		return FALSE;

		return FALSE;
	}

	return TRUE;
}

// *****************************************************
// Desc: ∫Œ»∞Ω∫≈≥ Ω√µø
// *****************************************************
DWORD GLChar::DoRevive2Skill ( SNATIVEID skill_id, WORD wSKILL_LVL, unsigned descriptor )
{
	if ( IsValidBody() )					return 0;
	if ( SKILL::MAX_LEVEL <= wSKILL_LVL )	return 0;
	if ( !IsSTATE(EM_ACT_DIE) )				return 0;

	//	Ω∫≈≥ ¡§∫∏ ∞°¡Æø».
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id );
	const SKILL::SSPEC &sSPEC = pSkill->m_sAPPLY.spec[descriptor].sSPEC[wSKILL_LVL];
	
    //	Note : ∫Œ»∞ map?E∫Œ»∞ gate ¡ˆ¡§, ¿ßƒ°¥¬ ¿«πÃ æ¯¥¬ ∞™.
	BOOL bOk = m_pGLGaeaServer->RequestReBirth ( m_dwGaeaID, m_pLandMan->GetMapID(), UINT_MAX, m_vPos );
	if ( !bOk )
	{
		DEBUGMSG_WRITE ( "ƒ≥∏Ø≈Õ ∫Œ»∞ Ω√µµ¡ﬂø° ø¿∑˘∞° πﬂª˝! m_pGLGaeaServer->RequestReBirth ()" );
		return 0;
	}

	//	∫Œ»∞ øœ?E√º≈©.
	ReSetSTATE(EM_ACT_DIE);

	//	∫Œ»∞Ω√ √§∑¬ »∏∫π.
	m_fGenAge = 0.0f;
	GLCHARLOGIC::INIT_RECOVER(int(sSPEC.fVAR1));
	TurnAction ( GLAT_IDLE );

	//	Note : ∫Œ»∞Ω√ ∞Ê«Ëƒ° ∞®º“.
	ReBirthDecExp ();

	// PET
	// ∏ ¿ÃµøΩ√ Pet π◊ Vehicle ªË¡¶
	m_pGLGaeaServer->ReserveDropOutPet ( SDROPOUTPETINFO(m_dwPetGUID,true,true) );
	m_pGLGaeaServer->ReserveDropOutSummon ( SDROPOUTSUMMONINFO(m_dwSummonGUID,true) );
	m_pGLGaeaServer->SaveVehicle( m_dwClientID, m_dwGaeaID, true );

	//	∫Œ»∞ »Æ¿Œ ∏ﬁΩ√?E
	GLMSG::SNETPC_REQ_REBIRTH_FB NetMsg;
	NetMsg.sMapID = m_pLandMan->GetMapID();
	NetMsg.vPos = GetPosition();
	NetMsg.wNowHP = m_sHP.dwNow;
	NetMsg.wNowMP = m_sMP.dwNow;
	NetMsg.wNowSP = m_sSP.dwNow;
	NetMsg.wNowCP = m_sCP.dwNow; //add cp

	m_pGLGaeaServer->SENDTOAGENT(m_dwClientID,&NetMsg);
	return m_sHP.dwNow;
}

// *****************************************************
// Desc: Ω∫≈≥ øµ«‚¿ª ƒ…∏Ø≈Õø° ¿˚?E√≈≤¥?
// *****************************************************
void GLChar::SkillProc ( SNATIVEID skill_id, BOOL bLowSP )
{
	//CONSOLEMSG_WRITE( "SkillProc Start [%u]", skill_id.dwID );

	//	Note : ƒ≥∏Ø≈Õ∞° πË?EΩ∫≈≥ ¡§∫∏ ∞°¡Æø».
	//
	SCHARSKILL sSkill;
	WORD wSKILL_LVL = 0;

	if ( IsDefenseSkill() )
	{
		if ( skill_id != m_sDefenseSkill.m_dwSkillID ) return;
		sSkill.sNativeID = skill_id;
		sSkill.wLevel = m_sDefenseSkill.m_wLevel;
		wSKILL_LVL = m_sDefenseSkill.m_wLevel;;

	}
	else
	{
		SKILL_MAP_ITER learniter = m_ExpSkills.find ( skill_id.dwID );
		if ( learniter==m_ExpSkills.end() )	return;
		sSkill = (*learniter).second;
		wSKILL_LVL = sSkill.wLevel;
	}

	//	Note : ø°¥œ∏ﬁ¿Ãº« ¡§∫∏.
	GLCONST_CHARCLASS &ConstCharClass = GLCONST_CHAR::cCONSTCLASS[m_CHARINDEX];
	VECANIATTACK &vecAniAttack = ConstCharClass.m_ANIMATION[m_SKILLMTYPE][m_SKILLSTYPE];
	if ( vecAniAttack.empty() )	return;

	//	Note : ∆Ø¡§ ∞¯∞› ø°¥œ∏ﬁ¿Ãº« º≥¡§ º±≈√. (ºˆ¡§?E
	//
	const SANIATTACK &sAniAttack = vecAniAttack[0];

	//	Ω∫≈≥ ¡§∫∏ ∞°¡Æø».
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id );
	SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[wSKILL_LVL];

	//	Note : SP∞° ∫Œ¡∑«œ?Eæ ¿ª∂ßø°¥¬ SP º“∏Ω√≈¥.
	//
	if ( !bLowSP )
	{
		WORD wDisSP = m_wSUM_DisSP + sSKILL_DATA.wUSE_SP;
		m_sSP.DECREASE ( wDisSP );
	}

	int nEXP_NUM = 0;
	int nALL_LVL = 0;
	int nALL_VARHP = 0, nALL_FULLHP = 0;
	int nALL_VARMP = 0, nALL_FULLMP = 0;
	int nALL_VARSP = 0, nALL_FULLSP = 0;

	WORD wMAX_TAR = 0;
	if ( pSkill->m_sBASIC.emIMPACT_TAR == TAR_SELF_TOSPEC )			wMAX_TAR = sSKILL_DATA.wPIERCENUM + GETSUM_PIERCE() + 1;
	else if ( pSkill->m_sBASIC.emIMPACT_REALM == REALM_FANWIZE )	wMAX_TAR = sSKILL_DATA.wTARNUM * ( sSKILL_DATA.wPIERCENUM + GETSUM_PIERCE() + 1 );
	else															wMAX_TAR = sSKILL_DATA.wTARNUM;

	if ( m_wTARNUM > wMAX_TAR )		m_wTARNUM = wMAX_TAR;

	//	Note : Ω∫≈≥¿Ã ¿˚?E«¥?≈∏∞Ÿ ∞À?E
	//
	bool bTowerWars = false;
	if ( m_pLandMan->m_bTowerWarsMap )
	{
		GLTowerWars* pSW = GLTowerWarsFieldMan::GetInstance().Find( m_pLandMan->m_dwTowerWarsMapID );
		if( pSW && pSW->IsBattle() ) bTowerWars = true;
	}
	STARGETID sTARID;
	for ( WORD i=0; i<m_wTARNUM; ++i )
	{
		const STARID &_sTARID = m_sTARIDS[i];

		sTARID.emCrow = _sTARID.GETCROW();
		sTARID.dwID = _sTARID.GETID();
		GLACTOR* pACTOR = m_pGLGaeaServer->GetTarget ( m_pLandMan, sTARID );
		if ( !pACTOR )									continue;

		bool bCrushBlowOne = false;

		for ( WORD j=0; j<sSKILL_DATA.wAPPLYNUM; ++j )
		{
			if ( pACTOR->GetNowHP()==0 )				continue;

			//	Note : π∞∏Æ µ•πÃ?Eπﬂª˝.
			//
			DWORD dwDamageFlag = DAMAGE_TYPE_NONE;

			int nVAR_HP(0), nVAR_MP(0), nVAR_SP(0);

			//	¿˙«◊ƒ°.
			short nRESIST = pACTOR->GETRESIST().GetElement(pSkill->m_sAPPLY.emELEMENT);
			if ( nRESIST>99 )	nRESIST = 99;

			//	SKILL ±‚∫ª ¿˚?E
			//
			switch ( pSkill->m_sAPPLY.emBASIC_TYPE )
			{
			case SKILL::EMFOR_HP:
				//	?EÛø°∞?«««ÿ∏¶ ¡÷¥¬ Ω∫≈≥.
				if ( sSKILL_DATA.fBASIC_VAR < 0.0f )
				{
//					bCRITICAL = CALCDAMAGE ( nVAR_HP, bShock, sTARID, m_pLandMan, pSkill, wSKILL_LVL, GLPeriod::GetInstance().GetWeather(), sAniAttack.m_wDivCount );
					DWORD dwWeather = GLPeriod::GetInstance().GetMapWeather( m_pLandMan->GetMapID().wMainID, m_pLandMan->GetMapID().wSubID );
					dwDamageFlag = CALCDAMAGE ( nVAR_HP, m_dwGaeaID, sTARID, m_pLandMan, pSkill, wSKILL_LVL, dwWeather, sAniAttack.m_wDivCount );
					nVAR_HP = - nVAR_HP;
					DWORD dwDmg;
					switch ( pSkill->m_sBASIC.emAPPLY )
					{
					case SKILL::EMAPPLY_PHY_SHORT:
					case SKILL::EMAPPLY_PHY_LONG:
						dwDmg = DWORD(nVAR_HP*GLCONST_CHAR::fPK_POINT_DEC_PHY);
						break;
					case SKILL::EMAPPLY_MAGIC:
						dwDmg = DWORD(nVAR_HP*GLCONST_CHAR::fPK_POINT_DEC_MAGIC);
						break;
					};

					STARGETID sTargetID(CROW_PC,m_dwGaeaID);
					PGLCHAR pChar = m_pGLGaeaServer->GetChar ( sTargetID.dwID );
					if( bTowerWars )
					{
						GLTowerWars* pSW = GLTowerWarsFieldMan::GetInstance().Find( m_pLandMan->m_dwTowerWarsMapID );
						if( pSW && pChar )
						{
							pSW->AddSWPDamageScore( pChar->m_dwGaeaID, -dwDmg );

							/*GLMSG::SNET_TOWERWARS_CTFPOINT_UPDATE NetMsg;
							NetMsg.bDamagePoint = true;
							NetMsg.bHealPoint = false;
							NetMsg.bResuPoint = false;
							NetMsg.bKillPoint = false;		
							NetMsg.dwDamage = -dwDmg;
							NetMsg.dwHeal = 0;
							m_pGLGaeaServer->SENDTOPLAYERCLIENT_ONMAP ( pChar->m_pLandMan->GetMapID().dwID,pChar->m_dwCharID, &NetMsg);*/
						}
					}
				}
				//	?EÛ¿?»∏∫πΩ√ƒ— ¡÷¥¬ Ω∫≈≥.
				else
				{
					int nDX = pACTOR->GetMaxHP() - pACTOR->GetNowHP();
					nVAR_HP += (int) min(nDX,sSKILL_DATA.fBASIC_VAR);
					STARGETID sTargetID(CROW_PC,m_dwGaeaID);
					PGLCHAR pChar = m_pGLGaeaServer->GetChar ( sTargetID.dwID );
					if( bTowerWars )
					{
						GLTowerWars* pSW = GLTowerWarsFieldMan::GetInstance().Find( m_pLandMan->m_dwTowerWarsMapID );
						if( pSW && pChar )
						{
							pSW->AddSWPHealScore( pChar->m_dwGaeaID,m_dwGaeaID, nVAR_HP );

							/*GLMSG::SNET_TOWERWARS_CTFPOINT_UPDATE NetMsg;
							NetMsg.bDamagePoint = false;
							NetMsg.bHealPoint = true;
							NetMsg.bResuPoint = false;
							NetMsg.bKillPoint = false;		
							NetMsg.dwDamage = 0;
							NetMsg.dwHeal = nVAR_HP;
							m_pGLGaeaServer->SENDTOPLAYERCLIENT_ONMAP ( pChar->m_pLandMan->GetMapID().dwID,pChar->m_dwCharID, &NetMsg);*/
						}
					}
				}
				break;

			case SKILL::EMFOR_MP:
				//	?EÛø°∞?«««ÿ∏¶ ¡÷¥¬ Ω∫≈≥.
				if ( sSKILL_DATA.fBASIC_VAR < 0.0f )
				{
					int nVAR = int(-sSKILL_DATA.fBASIC_VAR);
					nVAR_MP -= (int) ( nVAR - (nVAR*nRESIST/100.0f*GLCONST_CHAR::fRESIST_G ) );
				}
				//	?EÛ¿?»∏∫πΩ√ƒ— ¡÷¥¬ Ω∫≈≥.
				else
				{
					int nDX = pACTOR->GetMaxMP() - pACTOR->GetNowMP();
					nVAR_MP += (int) min(nDX,sSKILL_DATA.fBASIC_VAR);
				}
				break;

			case SKILL::EMFOR_SP:
				//	?EÛø°∞?«««ÿ∏¶ ¡÷¥¬ Ω∫≈≥.
				if ( sSKILL_DATA.fBASIC_VAR < 0.0f )
				{
					int nVAR = int(-sSKILL_DATA.fBASIC_VAR);
					nVAR_SP -= (int) ( nVAR - (nVAR*nRESIST/100.0f*GLCONST_CHAR::fRESIST_G ) );
				}
				//	?EÛ¿?»∏∫πΩ√ƒ— ¡÷¥¬ Ω∫≈≥.
				else
				{
					int nDX = pACTOR->GetMaxSP() - pACTOR->GetNowSP();
					nVAR_SP += (int) min(nDX,sSKILL_DATA.fBASIC_VAR);
				}
				break;
			};

			if ( dwDamageFlag & DAMAGE_TYPE_CRUSHING_BLOW ) bCrushBlowOne = true;

			//	Note : SP ∫Œ¡∑Ω√ø°¥¬ ∫Ø»≠ ∞™¿ª π›¿∏∑Œ ¡∂¡§.
			//
			if ( bLowSP )
			{
				nVAR_HP /= 2;
				nVAR_MP /= 2;
				nVAR_SP /= 2;
			}

			//	Note : Ω∫≈≥ ∆Ø?E±‚¥….
			//
			int nGATHER_HP(0), nGATHER_MP(0), nGATHER_SP(0);
			for( unsigned s=0;s<SKILL::SAPPLY::MAX_DESCRIPTOR;++s)
			{
				const SKILL::SSPEC_DESCRIPTOR &desc = pSkill->m_sAPPLY.spec[s];
				if( pSkill->m_sAPPLY.GetSpec( desc.emSPEC ) != &desc )	continue;
				const SKILL::SSPEC &sSPEC = desc.sSPEC[wSKILL_LVL];
				switch ( desc.emSPEC )
				{
				case EMSPECA_HP_GATHER:
					nGATHER_HP = int ( abs(nVAR_HP) * sSPEC.fVAR1 );
					break;

				case EMSPECA_MP_GATHER:
					nGATHER_MP = int ( abs(nVAR_MP) * sSPEC.fVAR1 );
					break;

				case EMSPECA_SP_GATHER:
					nGATHER_SP = int ( abs(nVAR_SP) * sSPEC.fVAR1 );
					break;
				};
			}

			//	Note : ¿⁄?E¿⁄Ω≈ø°∞‘ æ¥ Ω∫≈≥¿∫ ¡¶ø‹«œ?EEXP ¿⁄∑·∏¶ ºˆ¡˝.
			//
			if ( sTARID!=STARGETID(CROW_PC,m_dwGaeaID) )
			{
				++nEXP_NUM;
				nALL_LVL += pACTOR->GetLevel ();

				nALL_VARHP += nVAR_HP;
				nALL_VARMP += nVAR_MP;
				nALL_VARSP += nVAR_SP;

				nALL_FULLHP += pACTOR->GetMaxHP();
				nALL_FULLMP += pACTOR->GetMaxMP();
				nALL_FULLSP += pACTOR->GetMaxSP();
			}

			//	Note : Ω∫≈≥ ±‚∫ª øµ?E
			//
			SSKILLACT sSKILLACT;
			sSKILLACT.sID = STARGETID(CROW_PC,m_dwGaeaID);
			sSKILLACT.sID_TAR = STARGETID(_sTARID.GETCROW(),_sTARID.GETID());
			sSKILLACT.fDELAY = pSkill->m_sEXT_DATA.fDELAY4DAMAGE;
			sSKILLACT.emAPPLY = pSkill->m_sBASIC.emAPPLY;
			sSKILLACT.dwDamageFlag = dwDamageFlag;			

			//	Note : √º∑¬ ∫Ø»≠ ¿˙?E
			//
			sSKILLACT.nVAR_HP = nVAR_HP;
			sSKILLACT.nVAR_MP = nVAR_MP;
			sSKILLACT.nVAR_SP = nVAR_SP;

			//	Note : √º∑¬ »˙?E¿˙?E
			//
			sSKILLACT.nGATHER_HP = nGATHER_HP;
			sSKILLACT.nGATHER_MP = nGATHER_MP;
			sSKILLACT.nGATHER_SP = nGATHER_SP;

			if ( sSKILLACT.VALID() )
			{
				m_pLandMan->RegSkillAct ( sSKILLACT );
			}
		}

		//	Note : Ω∫≈≥ ∫∏¡∂ øµ?E
		//
		SSKILLACTEX sSKILLACTEX;
		sSKILLACTEX.sID = STARGETID(CROW_PC,m_dwGaeaID);
		sSKILLACTEX.sID_TAR = STARGETID(_sTARID.GETCROW(),_sTARID.GETID());
		sSKILLACTEX.fDELAY = pSkill->m_sEXT_DATA.fDELAY4DAMAGE;

		sSKILLACTEX.idSKILL = skill_id;
		sSKILLACTEX.wSKILL_LVL = wSKILL_LVL;

		//  ∞≠«— ≈∏∞› »Æ?E
		if ( bCrushBlowOne )
		{
			sSKILLACTEX.bCrushBlow = bCrushBlowOne;
			sSKILLACTEX.fPUSH_PULL = GLCONST_CHAR::fCRUSH_BLOW_RANGE;
		}

		//	Note : ªÛ≈¬ ¿Ã?E¿Øπﬂ.
		//
		ITEM::SSATE_BLOW sBLOW;
		sBLOW.emTYPE = EMBLOW_NONE;

		if ( pSkill->m_sAPPLY.emELEMENT==EMELEMENT_ARM )
		{
			SITEM *pITEM = GET_ELMT_ITEM ();
			if ( pITEM )	sBLOW = pITEM->sSuitOp.sBLOW;
		}
		else
		{
			const SKILL::SSTATE_BLOW &sSKILL_BLOW = pSkill->m_sAPPLY.sSTATE_BLOW[wSKILL_LVL];

			sBLOW.emTYPE = pSkill->m_sAPPLY.emSTATE_BLOW;
			sBLOW.fRATE = sSKILL_BLOW.fRATE;
			sBLOW.fLIFE = pSkill->m_sAPPLY.sDATA_LVL[wSKILL_LVL].fLIFE;
			sBLOW.fVAR1 = sSKILL_BLOW.fVAR1;
			sBLOW.fVAR2 = sSKILL_BLOW.fVAR2;
		}
        
		if ( sBLOW.emTYPE!=EMBLOW_NONE )
		{
			//	Note : πﬂª˝ »Æ¿≤ ∞Ë?E
			//
			short nBLOWRESIST = pACTOR->GETRESIST().GetElement ( STATE_TO_ELEMENT(sBLOW.emTYPE) );
			if ( nBLOWRESIST>99 )	nBLOWRESIST = 99;

//			float fPOWER = GLOGICEX::WEATHER_BLOW_POW ( sBLOW.emTYPE, GLPeriod::GetInstance().GetWeather(), m_pLandMan->IsWeatherActive() );
			DWORD dwWeather = GLPeriod::GetInstance().GetMapWeather( m_pLandMan->GetMapID().wMainID, m_pLandMan->GetMapID().wSubID );
			float fPOWER = GLOGICEX::WEATHER_BLOW_POW ( sBLOW.emTYPE, dwWeather, m_pLandMan->IsWeatherActive() );

			BOOL bBLOW(FALSE);
			if ( !(pACTOR->GETHOLDBLOW()&STATE_TO_DISORDER(sBLOW.emTYPE)) )
			{
				bBLOW = GLOGICEX::CHECKSTATEBLOW ( sBLOW.fRATE * fPOWER, GETLEVEL(), pACTOR->GetLevel(), nBLOWRESIST );
			}

			if ( bBLOW )
			{
				//	Note : ªÛ≈¬¿Ã?Eπﬂª˝.
				//	
				SSTATEBLOW sSTATEBLOW;
				float fLIFE = sBLOW.fLIFE * fPOWER;
				fLIFE = ( fLIFE - (fLIFE*nBLOWRESIST/100.0f*GLCONST_CHAR::fRESIST_G ) );

				sSTATEBLOW.emBLOW = sBLOW.emTYPE;
				sSTATEBLOW.fAGE = fLIFE;
				sSTATEBLOW.fSTATE_VAR1 = sBLOW.fVAR1;
				sSTATEBLOW.fSTATE_VAR2 = sBLOW.fVAR2;

				//	Note : ªÛ≈¬ ¿Ã?Eπﬂª˝ ¿˙?E
				//
				sSKILLACTEX.sSTATEBLOW = sSTATEBLOW;
			}
		}

		//	Note : Ω∫≈≥ ∆Ø?E±‚¥….
		//
		for( unsigned s=0;s<SKILL::SAPPLY::MAX_DESCRIPTOR;++s)
		{
			const SKILL::SSPEC_DESCRIPTOR &desc = pSkill->m_sAPPLY.spec[s];
			if( pSkill->m_sAPPLY.GetSpec( desc.emSPEC) != &desc )	continue;
			const SKILL::SSPEC &sSPEC = desc.sSPEC[wSKILL_LVL];
			switch ( desc.emSPEC )
			{
			case EMSPECA_PUSHPULL:
				if ( !pACTOR->IsValidBody() )				break;
				if ( RANDOM_POS > sSPEC.fVAR2 )		break;	//	Note : πﬂª˝»Æ¿≤ ¿˚?E
				if ( bCrushBlowOne )	break;
				sSKILLACTEX.fPUSH_PULL = sSPEC.fVAR1;
				break;

			case EMSPECA_PUSH: 	//add pushpull
				if ( !pACTOR->IsValidBody() )				break;
				sSKILLACTEX.fPUSH_PULL = sSPEC.fVAR1;
				sSKILLACTEX.fPUSH_PULL_B = sSPEC.fVAR2;
				sSKILLACTEX.bPush = true;
				break;

			case EMSPECA_PULL: 	//add pushpull
				if ( !pACTOR->IsValidBody() )				break;
				sSKILLACTEX.fPUSH_PULL = sSPEC.fVAR1;
				sSKILLACTEX.fPUSH_PULL_B = sSPEC.fVAR2;
				sSKILLACTEX.bPull = true;
				break;
			
			case EMSPECA_ONWARD: 	//add dash - SeiferXIII 6/30/13
			case EMSPECA_SHIFTPOS:
				if ( !pACTOR->IsValidBody() )				break;
				sSKILLACTEX.sID_TAR = STARGETID(m_sTARIDS[0].GETCROW(),m_sTARIDS[0].GETID());
				sSKILLACTEX.fPUSH_PULL = 1.0f;
				sSKILLACTEX.fPUSH_PULL_B = sSPEC.fVAR2;
				sSKILLACTEX.bDash = true;
				break;

			case EMSPECA_TELEPORT: 	//add teleport -   2-8-2014
				if ( !pACTOR->IsValidBody() )				break;
				sSKILLACTEX.bTeleport = true;
				break;

				/*
			case EMSPECA_CRUSHING_BLOW:
				if ( !bCrushBlowOne )	break;
				sSKILLACTEX.fPUSH_PULL = sSKILL_SPEC.fVAR1;
				break;
				*/

			case EMSPECA_HP_DIV:
			case EMSPECA_MP_DIV:
			case EMSPECA_SP_DIV:
				break;

			case EMSPECA_RECBLOW:
				//	Note : ªÛ≈¬ ¿Ã?Eƒ°?E
				//
				sSKILLACTEX.dwCUREFLAG |= sSPEC.dwFLAG;
				break;

			case EMSPECA_BUFF_REMOVE:
				sSKILLACTEX.dwRemoveFlag = EMSPECA_BUFF_REMOVE;
				break;
				/*
			case EMSPECA_DEBUFF_REMOVE:
				sSKILLACTEX.dwRemoveFlag = EMSPECA_DEBUFF_REMOVE;
				break;
				*/

			case EMSPECA_REBIRTH:
				if ( sTARID.emCrow==CROW_PC )
				{
					PGLCHAR pPC = m_pGLGaeaServer->GetChar(sTARID.dwID);
					if ( pPC )
					{
						if ( bTowerWars )//add anti-resu if not same school in tyranny map by AnFire16
						{
							if ( pPC->m_wSchool != m_wSchool ) break;
						}
						DWORD wRECOVE = pPC->DoRevive2Skill(skill_id,wSKILL_LVL,s);
						if ( 0<wRECOVE)
						{
							++nEXP_NUM;
							nALL_LVL += pPC->GetLevel ();
							nALL_VARHP += wRECOVE;
							nALL_FULLHP += pPC->GetMaxHP();
							STARGETID sTargetID(CROW_PC,m_dwGaeaID);
							PGLCHAR pChar = m_pGLGaeaServer->GetChar ( sTargetID.dwID );
							if( bTowerWars )
							{
								GLTowerWars* pSW = GLTowerWarsFieldMan::GetInstance().Find( m_pLandMan->m_dwTowerWarsMapID );
								if( pSW && pChar )
								{
									pSW->AddSWPResuScore( pChar->m_dwGaeaID,m_dwGaeaID );

									/*GLMSG::SNET_TOWERWARS_CTFPOINT_UPDATE NetMsg;
									NetMsg.bDamagePoint = false;
									NetMsg.bHealPoint = false;
									NetMsg.bResuPoint = true;
									NetMsg.bKillPoint = false;		
									NetMsg.dwDamage = 0;
									NetMsg.dwHeal = 0;
									m_pGLGaeaServer->SENDTOPLAYERCLIENT_ONMAP ( pChar->m_pLandMan->GetMapID().dwID,pChar->m_dwCharID, &NetMsg);*/
								}
							}
						}
					}
				}
				break;
			};
		}

		switch (pSkill->m_sAPPLY.emBASIC_TYPE)
		{
		case SKILL::EMFOR_CURE:
			//	Note : ªÛ≈¬ ¿Ã?Eƒ°?E
			//
			sSKILLACTEX.dwCUREFLAG |= pSkill->m_sAPPLY.dwCUREFLAG;
			break;
		};

		if ( sSKILLACTEX.VALID() )
		{
			m_pLandMan->RegSkillActEx ( sSKILLACTEX );
			nALL_VARHP;
		}

		//	Note : »∏∫πø° ±‚ø©«ﬂ¿ª ∂ß∏∏ ∞Ê«Ëƒ° πﬂª˝.	( ∞¯∞›Ω√¥¬ ¡¶ø‹ )
		//
		int nSUM_EXP = 0;
		bool bRECOVE = (nALL_VARHP>=0&&nALL_VARMP>=0&&nALL_VARSP&&0) && (nALL_VARHP+nALL_VARMP+nALL_VARSP)>0;

		if ( bRECOVE )
		{
			//	Ω«¡¶ ∫Ø»≠∑Æ¿Ã ¿÷¿ª ∂ß∏∏ ∞Ê«Ëƒ°∏¶ ?EÅE
			if ( nALL_VARHP>0 )
				nSUM_EXP += GLOGICEX::GLATTACKEXP(GETLEVEL(),nALL_LVL,nALL_VARHP,nALL_FULLHP,pACTOR->GetBonusExp());

			if ( nALL_VARMP>0 )
				nSUM_EXP += GLOGICEX::GLATTACKEXP(GETLEVEL(),nALL_LVL,nALL_VARMP,nALL_FULLMP,pACTOR->GetBonusExp());

			if ( nALL_VARSP>0 )
				nSUM_EXP += GLOGICEX::GLATTACKEXP(GETLEVEL(),nALL_LVL,nALL_VARSP,nALL_FULLSP,pACTOR->GetBonusExp());

			nSUM_EXP += int (nSUM_EXP*GLCONST_CHAR::fREC_EXP_RATE);
		}

		//	Note : ∞Ê«Ëƒ° »πµÊ∑Æ ¿˚?E
		//
		if ( nSUM_EXP )
		{
			// æ∆¿Ã≈€ ø°µ∆Æø°º≠ ¿‘∑¬«— ∞Ê«Ëƒ° πË¿≤ ¿˚?E(¡ÿ?E
			nSUM_EXP = int( (float)nSUM_EXP * GetExpMultipleRateFromSlotItem() );

			m_sExperience.lnNow += nSUM_EXP;
			m_sExperience.LIMIT();
		}
	}


	//	Note : Ω∫≈≥ ªÁ?E?µ˚∏• º“∏∑Æ FB MSG.
	//
	GLMSG::SNETPC_SKILLCONSUME_FB NetMsgFB;
	EMSLOT emLHand = GetCurLHand();
	SITEM* pItem = GET_SLOT_ITEMDATA(emLHand);
	if ( pItem && (pItem->sDrugOp.bInstance) )		NetMsgFB.wTurnNum = m_PutOnItems[emLHand].wTurnNum;
	NetMsgFB.wNowHP = m_sHP.dwNow;
	NetMsgFB.wNowMP = m_sMP.dwNow;
	NetMsgFB.wNowSP = m_sSP.dwNow;

	NetMsgFB.wNowCP = m_sCP.dwNow; //add cp

	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgFB );

	//	Note : º“∏º∫ æ∆¿Ã≈∆ ¿Ø»øº∫ ∞ÀªÁ»ƒ, ªÁ∂Û¡˙∂ß ∏ﬁΩ√?Eπﬂª˝.
	//
	CheckInstanceItem ();
}


// *****************************************************
// Desc: Ω√µø¡ﬂ¿Œ Ω∫≈≥?E?¡§∫∏ ∞ªΩ≈
// *****************************************************
BOOL GLChar::SkillProcess ( float fElapsedTime )
{
	//CONSOLEMSG_WRITE( "SkillProcess Start [%u]", m_idACTIVESKILL.dwID );

	//	Note : ƒ≥∏Ø≈Õ∞° πË?EΩ∫≈≥ ¡§∫∏ ∞°¡Æø».
	//
	WORD wSKILL_LVL;
	SCHARSKILL sSkill;

	if ( IsDefenseSkill() )
	{
		if ( m_idACTIVESKILL != m_sDefenseSkill.m_dwSkillID ) return FALSE;
		sSkill.sNativeID = m_idACTIVESKILL;
		sSkill.wLevel = m_sDefenseSkill.m_wLevel;
		wSKILL_LVL = sSkill.wLevel;
	}
	else
	{
        SKILL_MAP_ITER learniter = m_ExpSkills.find ( m_idACTIVESKILL.dwID );
		if ( learniter==m_ExpSkills.end() )		return FALSE;
		sSkill = (*learniter).second;
		wSKILL_LVL = sSkill.wLevel;
	}

	//	Ω∫≈≥ ¡§∫∏ ∞°¡Æø».
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( m_idACTIVESKILL );

	//	¿⁄Ω≈¿« µø√ºπ›?E+ Ω∫≈≥≈∏∞Ÿøµø™ + Ω∫≈≥¿˚?Eµø?+ 20(ø©¿Ø∞™)
	float fSkillRange = (float) ( GETBODYRADIUS() + GETSKILLRANGE_TAR(*pSkill) +
		GETSKILLRANGE_APPLY(*pSkill,wSKILL_LVL) + 20 );

	// ?E?¡æ∑·»ƒ π´¿˚≈∏¿”¿Ã?E∞¯∞› π´Ω√
	if ( m_sCONFTING.IsPOWERFULTIME () ) return FALSE;

	//	Note : Ω∫≈≥¿Ã ¿˚?E«¥?≈∏∞Ÿ ∞À?E
	//
	DWORD dwVALIDNUM(0); // ¿Ø»ø ≈∏∞Ÿ
	STARGETID sTARID;
	for ( WORD i=0; i<m_wTARNUM; ++i )
	{
		sTARID.emCrow = m_sTARIDS[i].GETCROW();
		sTARID.dwID = m_sTARIDS[i].GETID();
		GLACTOR* pACTOR = m_pGLGaeaServer->GetTarget ( m_pLandMan, sTARID );
		if ( !pACTOR )					continue;

		// ?E?¡æ∑·»ƒ π´¿˚≈∏¿”¿Ã?E∞¯∞› π´Ω√
		PGLCHAR pChar = m_pGLGaeaServer->GetChar ( sTARID.dwID );
		if ( pChar )
		{
			if ( pChar->m_sCONFTING.IsPOWERFULTIME () )
				continue;
		}

		// ≈∏∞Ÿπ›?E+ Ω∫≈≥ ¿Ø»øπ›?E
		float fReActionRange = (float) ( pACTOR->GetBodyRadius() + fSkillRange );

		// Ω∫≈≥ πﬂµø¿⁄øÕ ≈∏∞Ÿ∞˙¿« ∞≈∏Æ
		D3DXVECTOR3 vDist = m_vPos - pACTOR->GetPosition();  
		float fDist = D3DXVec3Length(&vDist);

		if ( fReActionRange*GLCONST_CHAR::fREACT_VALID_SCALE < fDist )
		{
			m_sTARIDS[i].wID = USHRT_MAX;
		}
		else
		{
			dwVALIDNUM++;
		}
	}

	// Ω∫≈≥ ¿Ø»øπ›?E≥ªø° ≈∏∞Ÿ¿Ã æ¯¿ª ∞Ê?E
	if ( dwVALIDNUM==0 )
	{
		TurnAction ( GLAT_IDLE );

		//	Note : ¿⁄Ω≈ø°∞‘.
		GLMSG::SNETPC_ATTACK_DAMAGE NetMsg;
		NetMsg.emTarCrow		= m_TargetID.emCrow;
		NetMsg.dwTarID			= m_TargetID.dwID;
		NetMsg.nDamage			= 0;
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsg );
	}

	m_fattTIMER += fElapsedTime*GLCHARLOGIC::GETATTVELO();
	m_fattTIMER += GLCHARLOGIC::GETATT_ITEM();

	GLCONST_CHARCLASS &ConstCharClass = GLCONST_CHAR::cCONSTCLASS[m_CHARINDEX];
	VECANIATTACK &vecAniAttack = ConstCharClass.m_ANIMATION[m_SKILLMTYPE][m_SKILLSTYPE];
	if ( vecAniAttack.empty() )	return FALSE;

	//	Note : ∆Ø¡§ ∞¯∞› ø°¥œ∏ﬁ¿Ãº« º≥¡§ º±≈√. (ºˆ¡§?E
	//
	const SANIATTACK &sAniAttack = vecAniAttack[0];

	//
	//
	int nTotalKeys = int(sAniAttack.m_dwETime) - int(sAniAttack.m_dwSTime);
	DWORD dwThisKey = sAniAttack.m_dwSTime + DWORD(m_fattTIMER*UNITANIKEY_PERSEC);
	
	if ( !m_sHITARRAY.empty() )
	{
		SSTRIKE sStrike = *m_sHITARRAY.begin();

		if ( dwThisKey >= sStrike.wDivKey )
		{
			if ( sStrike.bHit )
			{
				//CONSOLEMSG_WRITE( "SkillProcess m_sHITARRAY1 SkillProc[%u]", m_idACTIVESKILL.dwID );
				SkillProc ( m_idACTIVESKILL, sStrike.bLowSP );
				//TurnAction ( GLAT_IDLE );
			}
			else
			{
				//CONSOLEMSG_WRITE( "SkillProcess m_sHITARRAY1 AvoidProc[%u]", m_idACTIVESKILL.dwID );
				AvoidProc ( m_idACTIVESKILL, sStrike.bLowSP );
				//TurnAction ( GLAT_IDLE );
			}

			//	≈• µ•¿Ã≈∏∞° √≥∏Æµ» ∞Ê?EªË¡¶«—¥Ÿ.
			m_sHITARRAY.pop_front ();
		}	
	}

	//	¿ÃªÛ¡ıªÛø° ¿««ÿ µ•¿Ã≈∏∞° ?EÅE√≥∏Æµ«?Eæ ¿∫∞Ê?E
	//	∏∂¡ˆ∏∑ø° «—≤®π¯ø° √≥∏Æ«œ?E FALSE∏¶ ∏Æ≈œ«—¥Ÿ.
	//
	if ( dwThisKey >= sAniAttack.m_dwETime )
	{
		if ( !m_sHITARRAY.empty() )
		{
			while ( !m_sHITARRAY.empty() )
			{
				SSTRIKE sStrike = *m_sHITARRAY.begin();

				if ( sStrike.bHit )		
				{
					//CONSOLEMSG_WRITE( "SkillProcess m_sHITARRAY2 SkillProc[%u]", m_idACTIVESKILL.dwID );
					SkillProc ( m_idACTIVESKILL, sStrike.bLowSP );
					//TurnAction ( GLAT_IDLE );
				}
				else
				{
					//CONSOLEMSG_WRITE( "SkillProcess m_sHITARRAY2 AvoidProc[%u]", m_idACTIVESKILL.dwID );
					AvoidProc ( m_idACTIVESKILL, sStrike.bLowSP );
					//TurnAction ( GLAT_IDLE );
				}

				//	≈• µ•¿Ã≈∏∞° √≥∏Æµ» ∞Ê?EªË¡¶«—¥Ÿ.
				m_sHITARRAY.pop_front ();
			}
		}

		if ( !sAniAttack.IsLOOP() )	return FALSE;

		//	Note : Ω∫≈≥ π›∫π.
		//
		EMSKILLCHECK emCHECK = GLCHARLOGIC::CHECHSKILL ( m_idACTIVESKILL, 1, IsDefenseSkill() );
		if ( emCHECK != EMSKILL_OK && emCHECK != EMSKILL_NOTSP )
		{
			//	Note : Ω∫≈≥ ±∏µø Ω«∆– FB ∏ﬁΩ√?E
			GLMSG::SNETPC_REQ_SKILL_FB NetMsgFB;
			NetMsgFB.emSKILL_FB = emCHECK;
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgFB );
			return FALSE;
		}

		//	Note : SKILL ±∏µø.
		//
		SETACTIVESKILL ( m_idACTIVESKILL );

		BOOL bLowSP =  (emCHECK==EMSKILL_NOTSP) ? TRUE : FALSE;
		PreStrikeProc ( TRUE, bLowSP );

		//	Note : Ω∫≈≥ ªÁ?E?º“∏∞™?Eº“∏Ω√≈¥.
		//
		GLCHARLOGIC::ACCOUNTSKILL ( m_idACTIVESKILL, 1, true );

		m_fattTIMER = 0.0f;
	}

	return TRUE;
}

inline HRESULT GLChar::UpdateClientState ( float fElapsedTime )
{
	//	Note : ¡ı∞°ºˆƒ°∏¶ ≈¨∂Û¿Ãæ∆Æ∞° øπ√¯¿ª «œ∞‘ µ«?E ∏ﬁºº?Eπﬂª˝¿ª æ»«ÿµµ µ»¥Ÿ.
	//		¥‹ æ‡∞£¿« ø¿¬˜∞° πﬂª˝«“ º“¡ˆ∞° ¿÷¿Ω.
	//
	m_fSTATE_TIMER += fElapsedTime;
	if ( m_fSTATE_TIMER>1.6f )
	{
		m_fSTATE_TIMER = 0.0f;

		//	Note : ¿⁄Ω≈, ?E√¿⁄ø°∞?hp,mp ∞™ ∞ªΩ≈.
		//
		//	∆ƒ∆ºø¯ø°∞‘¥¬ hp,mp ∞ªΩ≈«œ?Eæ ¥¬¥Ÿ.
		MsgSendUpdateState ( false );
	}

	m_fMBR_TIMER += fElapsedTime;

	if ( m_fMBR_TIMER > 1.6f )
	{
		m_fMBR_TIMER = 0.0f;

		GLPartyFieldMan& sPartyFieldMan = m_pGLGaeaServer->GetPartyMan();
		if ( sPartyFieldMan.GetParty ( m_dwPartyID ) )
		{
			GLMSG::SNET_PARTY_MBR_POS NetMsg;
			NetMsg.dwGaeaID = m_dwGaeaID;
			NetMsg.vPos = m_actorMove.Position();
			NetMsg.sHP = m_sHP;
			NetMsg.sMP = m_sMP;

			sPartyFieldMan.SendMsgToMember ( m_dwPartyID, (NET_MSG_GENERIC*) &NetMsg );
		}
	}

	return S_OK;
}

VOID GLChar::UpdateLandEffect()
{
	std::set<int> setOldLandEffectNum = m_setLandEffectNum;
	std::set<int>::iterator iter_EffNum;
	m_setLandEffectNum.clear();

	SLEVEL_ETC_FUNC *pLevelEtcFunc = m_pLandMan->GetLevelEtcFunc();
	if( !pLevelEtcFunc ) return;
	if( !pLevelEtcFunc->m_bUseFunction[EMETCFUNC_LANDEFFECT] ) return;

	int i;
	for( i = 0; i <(int) pLevelEtcFunc->m_vecLandEffect.size(); i++ )
	{
		SLANDEFFECT landEffect = pLevelEtcFunc->m_vecLandEffect[i];
		if( m_vPos.x > landEffect.vMinPos.x &&
			m_vPos.z > landEffect.vMinPos.y &&
			m_vPos.x < landEffect.vMaxPos.x &&
			m_vPos.z < landEffect.vMaxPos.y )
		{
			m_setLandEffectNum.insert(i);
		}
	}

	BOOL bUpdateLandEff = FALSE;
	if( setOldLandEffectNum.size() != m_setLandEffectNum.size() )
	{
		bUpdateLandEff = TRUE;
	}else{
		iter_EffNum = m_setLandEffectNum.begin();
		for( ; iter_EffNum != m_setLandEffectNum.end(); ++iter_EffNum )
		{
			if( setOldLandEffectNum.find( *iter_EffNum ) == setOldLandEffectNum.end() )
			{
				bUpdateLandEff = TRUE; 
				break;
			}
		}
	}

	if( bUpdateLandEff )
	{
		DISABLEALLLANDEFF();

		GLMSG::SNETPC_LANDEFFECT NetMsg;
		int iNum = 0;
		iter_EffNum = m_setLandEffectNum.begin();
		for( ; iter_EffNum != m_setLandEffectNum.end(); ++iter_EffNum )
		{

			SLANDEFFECT landEffect = pLevelEtcFunc->FindLandEffect(*iter_EffNum);
			if( !landEffect.IsUse() ) continue;
			ADDLANDEFF( landEffect, iNum );
			NetMsg.sLandEffect[iNum] = landEffect;
			iNum++;
		}

		NetMsg.dwGaeaID		= m_dwGaeaID;	
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsg );
		SendMsgViewAround( (NET_MSG_GENERIC*) &NetMsg ); 	

		
	}


	// ∏?Eπˆ«¡∏¶ ?E“«ÿæﬂ«?∞Ê?E?√≥∏Æ
	for( int i = 0; i < EMLANDEFFECT_MULTI; i++ )
	{
		SLANDEFFECT landEffect = m_sLandEffect[i];
		if( !landEffect.IsUse() ) continue;
		if( landEffect.emLandEffectType == EMLANDEFFECT_CANCEL_ALLBUFF )
		{
			DisableSkillFact();
			break;
		}
	}


}

BOOL GLChar::ShockProcess ( float fElapsedTime )
{
	GLCONST_CHARCLASS &ConstCharClass = GLCONST_CHAR::cCONSTCLASS[m_CHARINDEX];
	VECANIATTACK &vecShock = ConstCharClass.m_ANIMATION[AN_SHOCK][AN_SUB_NONE];
	if ( vecShock.empty() )	return FALSE;

	m_fIdleTime += fElapsedTime * ( GETMOVEVELO() + GETMOVE_ITEM() );
			
	SANIATTACK &sAniShock = vecShock[0];

	int wTotalKeys = int(sAniShock.m_dwETime) - int(sAniShock.m_dwSTime);
	int wThisKey = int(m_fIdleTime*UNITANIKEY_PERSEC);
	
	if ( wThisKey >= wTotalKeys )	return FALSE;

	return TRUE;
}

float GLChar::GetMoveVelo ()
{
	float fDefaultVelo = IsSTATE(EM_ACT_RUN) ? GLCONST_CHAR::cCONSTCLASS[m_CHARINDEX].fRUNVELO : GLCONST_CHAR::cCONSTCLASS[m_CHARINDEX].fWALKVELO;
	float fMoveVelo = fDefaultVelo * ( GLCHARLOGIC::GETMOVEVELO() + GLCHARLOGIC::GETMOVE_ITEM() ) ;
	return fMoveVelo;
}

void GLChar::ResetConfront ( EMCONFRONT_END emEND )
{
	//	Note : √º∑¬ »Ø?E
	//
	DoConftStateRestore();

	//	Note : ?E?¡æ∑·∏¶ (¿⁄Ω≈) ø°¿Ã?EÆø?æÀ∏≤.
	GLMSG::SNETPC_CONFRONT_END2_AGT NetMsgMyAgt;
	NetMsgMyAgt.emEND = emEND;
	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgMyAgt );

	//	Note : (¿⁄Ω≈) ≈¨∂Û¿Ãæ∆Æø°.
	GLMSG::SNETPC_CONFRONT_END2_CLT NetMsgMyClt;
	NetMsgMyClt.emEND = emEND;
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgMyClt );

	//	∆ƒ∆ºø° ¿÷¥¬ '?E? ?E°¡§∫∏∏?∏Æº¬.
	GLMSG::SNETPC_CONFRONT_END2_CLT_MBR NetMsgTarMbr;

	switch ( m_sCONFTING.emTYPE )
	{
	case EMCONFT_PARTY:
		{
			GLPARTY_FIELD *pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
			if ( pParty )
			{
				NetMsgTarMbr.dwID = m_dwGaeaID;

				//	?E?∏ÆΩ∫∆Æø°º≠ ¡¶∞≈.
				pParty->MBR_CONFRONT_LEAVE(m_dwGaeaID);

				//	∆ƒ∆ºø¯ø°∞‘ ?E√ø°º??E?≥™∞®¿ª æÀ∏≤.
				m_pGLGaeaServer->SENDTOPARTYCLIENT ( m_dwPartyID, &NetMsgTarMbr );

				//	?E?ªÛ?EÅE∆ƒ∆ºø¯ø°∞‘.
				GLPARTY_FIELD *pPartyConft = m_pGLGaeaServer->GetParty ( pParty->m_dwconftPARTYID );
				if ( pPartyConft )
				{
					//	∆ƒ∆ºø¯ø°∞‘ ?E√ø°º??E?≥™∞®¿ª æÀ∏≤.
					m_pGLGaeaServer->SENDTOPARTYCLIENT ( pPartyConft->m_dwPARTYID, &NetMsgTarMbr );
				}
			}
		}
		break;

	case EMCONFT_GUILD:
		{
			GLClubMan &cClubMan = m_pGLGaeaServer->GetClubMan();
			GLCLUB *pCLUB = cClubMan.GetClub ( m_dwGuild );
			if ( pCLUB )
			{
				NetMsgTarMbr.dwID = m_dwCharID;

				//	Note : ¿⁄Ω≈¿« ≈¨∑¥ ¡§∫∏ø°º≠ ?E√¬ÅE?∏‚πˆø°º≠ ¡¶∞≈.
				pCLUB->DELCONFT_MEMBER ( m_dwCharID );

				//	Note : ¿⁄Ω≈¿« ≈¨∑¥ø¯ø°∞‘.
				m_pGLGaeaServer->SENDTOCLUBCLIENT ( m_dwGuild, &NetMsgTarMbr );

				//	Note : ªÛ?EÅE≈¨∑¥ø¯ø°∞‘.
				GLCLUB *pTAR_CLUB = cClubMan.GetClub ( m_sCONFTING.dwTAR_ID );
				if ( pTAR_CLUB )
				{
					m_pGLGaeaServer->SENDTOCLUBCLIENT ( m_sCONFTING.dwTAR_ID, &NetMsgTarMbr );
				}
			}
		}
		break;
	};

	//	Note : ¡÷∫Ø ¿Ø¥÷µÈø° ?E√¡æ∑ÅE?E?
	//
	GLMSG::SNETPC_CONFRONT_END2_CLT_BRD NetMsgTarBrd;
	NetMsgTarBrd.dwGaeaID = m_dwGaeaID;
	NetMsgTarBrd.emEND = emEND;
	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgTarBrd );

	m_sCONFTING.RESET ();
	m_sCONFTING.SETPOWERFULTIME ( 10.0f );
}

void GLChar::VietnamGainCalculate()
{

	if ( IsSTATE(EM_ACT_WAITING) )		return; 
	if ( m_dwVietnamGainType == GAINTYPE_EMPTY )		return;
	// ¡ﬂ±π ¥©?EΩ√∞£ ∫∞ ºˆ¿Õ ∫Ø?E
	CTimeSpan gameTime( 0, (int)m_sVietnamSystem.gameTime / 60, (int)m_sVietnamSystem.gameTime % 60, 0 );
	CTime	  crtTime     = CTime::GetCurrentTime();
	CTimeSpan crtGameSpan, crtGame15Span;
	CTime	  loginTime   = m_sVietnamSystem.loginTime;
	crtGameSpan			  = gameTime + ( crtTime - loginTime );

//	GLGaeaServer & glGaeaServer = m_pGLGaeaServer;


	LONGLONG totalHours	  = crtGameSpan.GetTotalHours();


	// 5Ω√∞£ ¿ÃªÛ¿Ã?E∞Ë?Eœ¡ÅEæ ?E≥—æ˚Ã£¥Ÿ.
	// ºˆ¿Õ µ˚Õﬁ¿Ã πŸ≤˚?E∏ﬁΩ√¡ˆ∏¶ ∫∏≥ø
	if( totalHours >= 5 && m_dwVietnamGainType != GAINTYPE_EMPTY )
	{
		m_dwVietnamGainType = GAINTYPE_EMPTY;	

		GLMSG::SNETPC_VIETNAM_GAINTYPE NetMsg;
		NetMsg.dwGainType = (BYTE)GAINTYPE_EMPTY;
		m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsg );
		// ºˆ¿Õ 50%
	}else if( totalHours >= 3 && m_dwVietnamGainType != GAINTYPE_HALF )
	{	
		m_dwVietnamGainType = GAINTYPE_HALF;	

		GLMSG::SNETPC_VIETNAM_GAINTYPE NetMsg;
		NetMsg.dwGainType = (BYTE)GAINTYPE_HALF;
		m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsg );
	}
	m_sVietnamSystem.currentGameTime = totalHours;
}

void GLChar::ChinaGainCalculate()
{
	if ( IsSTATE(EM_ACT_WAITING) )		return; 
	// 18ºº ¿ÃªÛ¿Ã?E∏Æ≈œ«—¥Ÿ.
	if( m_sChinaTime.userAge == 1 ) return;

//	GLGaeaServer & glGaeaServer = m_pGLGaeaServer;

	// ¡ﬂ±π ¥©?EΩ√∞£ ∫∞ ºˆ¿Õ ∫Ø?E
	CTimeSpan gameTime( 0, (int)m_sChinaTime.gameTime / 60, (int)m_sChinaTime.gameTime % 60, 0 );
	CTime	  crtTime     = CTime::GetCurrentTime();
	CTimeSpan crtGameSpan, crtGame15Span;
	CTime	  loginTime   = m_sChinaTime.loginTime;
	crtGameSpan			  = gameTime + ( crtTime - loginTime );

	// ºˆ¿Õ 0%
	//if( m_ChinaGainType == 2 )
	//{
	//	crtGame15Span = crtTime - m_China15Time;
	//	// 15∫–¿Ã ¡ˆ≥™?E∏ﬁΩ√¡ˆ∏¶ ∫∏≥ø
	//	if( crtGame15Span.GetTotalMinutes() > 15 )
	//	{
	//		m_China15Time	= CTime::GetCurrentTime();

	//		GLMSG::SNETPC_CHINA_GAINTYPE NetMsg;
	//		NetMsg.dwGainType = 3;
	//		m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsg );
	//	}
	//}else
	if( m_ChinaGainType != 2 )
	{
		LONGLONG totalHours	  = crtGameSpan.GetTotalHours();
//		LONGLONG totalMinutes = crtGameSpan.GetTotalMinutes();
//		LONGLONG totalSecond  = crtGameSpan.GetTotalSeconds();

		// ºˆ¿Õ µ˚Õﬁ¿Ã πŸ≤˚?E∏ﬁΩ√¡ˆ∏¶ ∫∏≥ø
		if( totalHours >= 5 && m_ChinaGainType != GAINTYPE_EMPTY )
			//if( totalSecond >= 60 && m_ChinaGainType != 2 )
		{
			m_China15Time	= CTime::GetCurrentTime();
			m_ChinaGainType = GAINTYPE_EMPTY;	

			GLMSG::SNETPC_CHINA_GAINTYPE NetMsg;
			NetMsg.dwGainType = GAINTYPE_EMPTY;
			m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsg );
			// ºˆ¿Õ 50%
		}else if( totalHours >= 3 && m_ChinaGainType != GAINTYPE_HALF  )
			//}else if( totalSecond >= 50 && m_ChinaGainType != 2 )
		{	
			m_ChinaGainType = GAINTYPE_HALF;

			GLMSG::SNETPC_CHINA_GAINTYPE NetMsg;
			NetMsg.dwGainType = GAINTYPE_HALF;
			m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsg );
		}else if( totalHours >= 1 && m_ChinaGainType == 255 )
			//}else if( totalSecond >= 40 && m_ChinaGainType != 2 )
		{
			m_ChinaGainType = 0;

			GLMSG::SNETPC_CHINA_GAINTYPE NetMsg;
			NetMsg.dwGainType = 4;
			m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsg );
		}
	}
	m_sChinaTime.currentGameTime = crtGameSpan.GetTotalMinutes();
}

void GLChar::EventCalculate()
{
	if ( IsSTATE(EM_ACT_WAITING) )		return; 

	SEventState sEventState = m_pGLGaeaServer->m_sEventState;

	if( sEventState.bEventStart == FALSE ) return;

	// ¿Ã∫•∆Æ ¿˚?E∑π∫ß¿Ã æ∆¥œ?E∏Æ≈œ
	if( m_bEventApply == FALSE ) return;

	CTime	  crtTime     = CTime::GetCurrentTime();
	CTimeSpan crtGameSpan;
	CTime	  loginTime			 = m_sEventTime.loginTime;
	crtGameSpan					 = ( crtTime - loginTime );
	m_sEventTime.currentGameTime = crtGameSpan.GetTimeSpan();

	// ¿Ã∫•∆Æ∞° ªı∑Œ Ω√¿€ µ 
	if( m_bEventStart == FALSE )
	{
		// ≈◊Ω∫∆Æ Ω√ø£ Second∑Œ «—¥Ÿ.
		if( crtGameSpan.GetTotalSeconds() >= sEventState.EventPlayTime )
		{
			m_bEventStart = TRUE;

			//	Note : ¿⁄Ω≈¿« ≈¨∂Û¿Ãæ∆Æø°.
			GLMSG::SNET_GM_LIMIT_EVENT_APPLY_START NetMsg;
			NetMsg.loginTime = m_sEventTime.loginTime;
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*)&NetMsg );

		}
	}

	if( m_bEventStart == TRUE )
	{
		if( crtGameSpan.GetTotalSeconds() >= sEventState.EventPlayTime + sEventState.EventBusterTime )
		{
			m_bEventStart = FALSE;
			m_sEventTime.loginTime = crtTime.GetTime();

			// ªı∑Œ ∞ªΩ≈µ» ¿Ã∫•∆Æ Ω√∞£
			GLMSG::SNET_GM_LIMIT_EVENT_RESTART NetMsg;
			NetMsg.restartTime = crtTime.GetTime();

			m_pGLGaeaServer->SENDTOAGENT(m_dwClientID,&NetMsg);

			//	Note : ¿⁄Ω≈¿« ≈¨∂Û¿Ãæ∆Æø°.
			GLMSG::SNET_GM_LIMIT_EVENT_APPLY_END NetMsg2;
			NetMsg2.loginTime = m_sEventTime.loginTime;
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*)&NetMsg2 );
		}
	}




}

HRESULT GLChar::FrameMove ( float fTime, float fElapsedTime )
{
	GASSERT(m_pLandMan);

//	GLGaeaServer & glGaeaServer = m_pGLGaeaServer;

#if defined(VN_PARAM) //vietnamtest%%%
	// ∫£∆Æ≥≤ ≈Ω¥– πÊ?E∞Ë?E
	VietnamGainCalculate();
#endif

#ifdef CH_PARAM_USEGAIN
	// ¡ﬂ±π ≈Ω¥– πÊ?E∞Ë?E
	ChinaGainCalculate();
#else
	// ∏ÆπÃ∆Æ ¿Ã∫•∆Æ ∞Ë?E
	EventCalculate();
#endif

	if ( !IsSTATE(EM_ACT_WAITING) && m_bEntryFailed )
	{
		//  ¡¯¿‘¡∂∞«¿Ã ∏¬¡ˆæ æ∆ ¥Ÿ∏• ∞˜¿∏∑Œ ¿Ãµø «ÿæﬂ«œ¥¬ ∞Ê?E∏ﬁΩ√¡ˆ∏¶ ∫∏≥Ω¥Ÿ.
		GLMSG::SNETENTRY_FAILED NetMsg;
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );

		m_bEntryFailed = FALSE;
	}

	

	// ≈ª∞Õ πË≈Õ∏Æ √º≈©
	UpdateVehicle( fElapsedTime );


	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	

	m_fAge += fElapsedTime;
	m_fGenAge += fElapsedTime;

	m_fSkillDelay += fElapsedTime;

	//	∆Æ∑π¿Ã?EªÛ≈¬ ∞ªΩ≈.
	if ( m_sTrade.Valid() )
	{
		m_sTrade.FrameMove ( fTime, fElapsedTime );

		PGLCHAR pChar = m_pGLGaeaServer->GetChar ( m_sTrade.GetTarget() );
		if ( !pChar )
		{
			GLMSG::SNET_TRADE_CANCEL_TAR NetMsg;
			NetMsg.emCancel = EMTRADE_CANCEL_NORMAL;

			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );

			m_sTrade.Reset ();
		}
	}

	//	DBø° ¡§∫∏ ¿˙¿Â«“ Ω√∞£¿Ã µ«æ˙¥¬?E∞ÀªÁ»ƒø° ¿˙?Eºˆ?E
	//
	m_fSAVEDB_TIMER += fElapsedTime;
	if ( m_fSAVEDB_TIMER > 1800.0f )
	{
		m_fSAVEDB_TIMER = 0.0f;
		m_pGLGaeaServer->SaveCharDB ( m_dwGaeaID );
	}

	if ( m_sCONFTING.IsCONFRONTING() )
	{
		//	Note : ?E?¿Ø»øº∫ ∞À?E
		//
		bool bvalid(false);
		PGLCHAR pTAR_ONE(NULL);
		switch ( m_sCONFTING.emTYPE )
		{
		case EMCONFT_ONE:
			{
				pTAR_ONE = m_pGLGaeaServer->GetChar ( m_sCONFTING.dwTAR_ID );
				if ( pTAR_ONE )		bvalid = true;
			}
			break;

		case EMCONFT_PARTY:
			{
				bool bpartyA(false), bpartyB(false);
				if ( PARTY_NULL!=m_dwPartyID && m_pGLGaeaServer->GetParty(m_dwPartyID) )						bpartyA = true;
				if ( PARTY_NULL!=m_sCONFTING.dwTAR_ID && m_pGLGaeaServer->GetParty(m_sCONFTING.dwTAR_ID) )	bpartyB = true;

				if ( bpartyA && bpartyB )	bvalid = true;
			}
			break;

		case EMCONFT_GUILD:
			{
				GLClubMan &sClubMan = m_pGLGaeaServer->GetClubMan();

				bool bclubA(false), bclubB(false);
				if ( CLUB_NULL!=m_dwGuild && sClubMan.GetClub(m_dwGuild) )							bclubA = true;
				if ( CLUB_NULL!=m_sCONFTING.dwTAR_ID && sClubMan.GetClub(m_sCONFTING.dwTAR_ID) )	bclubB = true;

				if ( bclubA && bclubB )	bvalid = true;
			}
			break;
		};
		

		if ( !bvalid )
		{
			ResetConfront ( EMCONFRONT_END_FAIL );
		}
		else
		{
			bool bFIGHT = m_sCONFTING.UPDATE(fElapsedTime);
			if ( bFIGHT )
			{
				//	Note : ?E?FIGHT æÀ∏≤.
				//
				GLMSG::SNETPC_CONFRONT_FIGHT2_CLT NetMsg;
				m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
			}

			switch ( m_sCONFTING.emTYPE )
			{
			case EMCONFT_ONE:
				{
					if ( m_sCONFTING.sOption.bBOUND )
					{
						D3DXVECTOR3 vDistance = m_vPos - m_sCONFTING.vPosition;
						float fDistance = D3DXVec3Length ( &vDistance );

						if ( GLCONST_CHAR::fCONFRONT_ONE_DIST < fDistance )
						{
							ReceiveLivingPoint ( GLCONST_CHAR::nCONFRONT_LOSS_LP );

							ResetConfront ( EMCONFRONT_END_DISLOSS );
							pTAR_ONE->ResetConfront ( EMCONFRONT_END_DISWIN );
						}
					}

					//	?E√¿?'¡∂∞«'ø° ¿««ÿº≠ ?E“µÃ¿?∞Ê?E
					if ( !m_sCONFTING.IsCONFRONTING() )		break;

					//	Note : º≠∑Œ ∞∞¿∫ ∆ƒ∆º¿Œ?E∞À?E
					//
					if ( GetPartyID()!=PARTY_NULL && pTAR_ONE->GetPartyID()==GetPartyID() )
					{
						ResetConfront ( EMCONFRONT_END_PARTY );
					}
				}
				break;

			case EMCONFT_PARTY:
				{
					if ( m_sCONFTING.sOption.bBOUND )
					{
						D3DXVECTOR3 vDistance = m_vPos - m_sCONFTING.vPosition;
						float fDistance = D3DXVec3Length ( &vDistance );

						if ( GLCONST_CHAR::fCONFRONT_PY_DIST < fDistance )
						{
							ReceiveLivingPoint ( GLCONST_CHAR::nCONFRONT_LOSS_LP );

							ResetConfront ( EMCONFRONT_END_DISLOSS );
						}
					}
				}
				break;

			case EMCONFT_GUILD:
				{
					if ( m_sCONFTING.sOption.bBOUND )
					{
						D3DXVECTOR3 vDistance = m_vPos - m_sCONFTING.vPosition;
						float fDistance = D3DXVec3Length ( &vDistance );

						if ( GLCONST_CHAR::fCONFRONT_CLB_DIST < fDistance )
						{
							ReceiveLivingPoint ( GLCONST_CHAR::nCONFRONT_CLB_LOSS_LP );

							ResetConfront ( EMCONFRONT_END_DISLOSS );
						}
					}
				}
				break;
			};
		}
	}
	// ?E√¡æ∑·»?µÙ∑π¿Ã Ω√∞£ ∞ªΩ≈
	else if ( m_sCONFTING.IsPOWERFULTIME () )
	{
		m_sCONFTING.UPDATEPWRFULTIME ( fElapsedTime );
	}

	//	Note : ¿˚?E«‡¿ß¿⁄¿« ≈∏¿Ã∏” ∞ªΩ≈ π◊ ?E?
	{
		GLMSG::SNETPC_PLAYERKILLING_DEL NetMsgDel;		
		SPLAYHOSTILE* pHOSTILE = NULL;
		for ( MAPPLAYHOSTILE_ITER pos = m_mapPlayHostile.begin() ; pos!=m_mapPlayHostile.end() ; )
		{
			pHOSTILE = pos->second;
			if( !pHOSTILE )
			{
				//	Note : ¿˚?E?ªË¡¶ æÀ∏≤.				
				NetMsgDel.dwCharID = pos->first;
				m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgDel );

				CDebugSet::ToLogFile( "GLChar::FrameMove, pos->second = NULL" );
				m_mapPlayHostile.erase( pos++ );
				continue;
			}

			pHOSTILE->fTIME -= fElapsedTime;
			if ( pHOSTILE->fTIME < 0 )
			{
				//	Note : ¿˚?E?ªË¡¶ æÀ∏≤.				
				NetMsgDel.dwCharID = pos->first;
				m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgDel );

				SAFE_DELETE( pHOSTILE );
				m_mapPlayHostile.erase( pos++ );
				continue;
			}
			++pos;
		}

		if ( IsValidBody() && m_nBright < 0 )
		{
			m_fBRIGHT_TIMER += fElapsedTime;
			if ( m_fBRIGHT_TIMER >= GLCONST_CHAR::fPK_POINT_DEC_RATE )
			{
				m_fBRIGHT_TIMER = 0.0f;

				//	Note : º”º∫ºˆƒ° ∫Ø»≠.
				m_nBright += 1;

				GLMSG::SNETPC_UPDATE_BRIGHT NetMsg;
				NetMsg.nBright = m_nBright;
				m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);

				GLMSG::SNETPC_UPDATE_BRIGHT_BRD NetMsgBrd;
				NetMsgBrd.dwGaeaID = m_dwGaeaID;
				NetMsgBrd.nBright = m_nBright;
				SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
			}
		}
	}

	//	Ω√∞£ ∞ªΩ≈.
	//
	m_fPERIOD_TIMER += fElapsedTime;
	if ( m_fPERIOD_TIMER > 360.0f )
	{
		m_fPERIOD_TIMER = 0.0f;
		MsgSendPeriod ();
	}

	m_fITEM_TIMER += fElapsedTime;
	if ( m_fITEM_TIMER > 1800.0f )
	{
		m_fITEM_TIMER = 0.0f;
		RESET_TIMELMT_ITEM ();
		RESET_CHECK_ITEM ();
	}

	m_fMoveDelay += fElapsedTime;

	if ( m_sQITEMFACT.IsACTIVE() )
	{
		bool bOK = UPDATE_QITEMFACT(fElapsedTime);
		if ( !bOK )
		{
			GLMSG::SNETPC_QITEMFACT_END_BRD	NetMsgBrd;
			NetMsgBrd.dwGaeaID = m_dwGaeaID;

			//	Note : ¡æ∑·µ«æ˙¿ª ∞Ê?E¿⁄Ω≈ø°∞‘ æÀ∏≤.
			m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgBrd );

			//	Note : ¡æ∑·µ«æ˙¿ª ∞Ê?E¡÷∫Ø ªÁ∂˜ø°∞‘ æÀ∏≤.
			SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
		}

		float fQBoxTime = CHECK_QBOXTIME( fElapsedTime ) ;
		if ( fQBoxTime >= 1.0f )
		{
			GLMSG::SNETPC_QITEMFACT_TIMEUPDATE_BRD	NetMsgTUBrd;

			NetMsgTUBrd.dwGaeaID = m_dwGaeaID;
			NetMsgTUBrd.fQBoxTime =  fQBoxTime ;
			m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgTUBrd );
			SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgTUBrd );
		}
	}

	if ( m_lnLastSendExp != m_sExperience.lnNow )
	{
		m_lnLastSendExp = m_sExperience.lnNow;

		//	Note : ∞Ê«Ëƒ° ∫Ø»≠ ≈¨∂Û¿Ãæ∆Æø° æÀ∑¡¡‹.
		//
		GLMSG::SNETPC_UPDATE_EXP NetMsgExp;
		NetMsgExp.lnNowExp = m_sExperience.lnNow;
		m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgExp );

		if ( m_sExperience.ISOVER() )
		{
			//	Note : ∑¶?Eºˆ?E ( ∑Œƒ√ ∏ﬁΩ√?Eπﬂª˝. )
			//
			GLMSG::SNETPC_REQ_LEVELUP NetMsg;
			MsgReqLevelUp ( (NET_MSG_GENERIC*) &NetMsg );

			m_lnLastSendExp = m_sExperience.lnNow;


		}else{
			m_bVietnamLevelUp = FALSE; 
		}
	}

	if ( m_lnLastSendVNExp != m_lVNGainSysExp )
	{
		m_lnLastSendVNExp = m_lVNGainSysExp;

		//	Note : ∞Ê«Ëƒ° ∫Ø»≠ ≈¨∂Û¿Ãæ∆Æø° æÀ∑¡¡‹.
		//
		GLMSG::SNETPC_VIETNAM_GAIN_EXP NetMsgExp;
		NetMsgExp.gainExp = m_lVNGainSysExp;
		m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgExp );

	}

#if defined(_RELEASED) || defined(TW_PARAM) || defined(HK_PARAM)
	if( m_lnTempMoney != m_lnMoney )
	{
		if( m_bMoneyUpdate )
		{
			m_bMoneyUpdate = FALSE;
		}else{
			// «ÿ≈∑¿∏∑Œ ∑Œ±◊∏¶ ≥≤?E
			HACKINGLOG_WRITE( "Different Update Money!!, Account[%s], ID[%s], Money %I64d, TempMoney %I64d, Money Gap %I64d", 
								m_szUID, m_szName, m_lnMoney, m_lnTempMoney, m_lnMoney - m_lnTempMoney );	
		}
		m_lnTempMoney = m_lnMoney;
	}else{
		m_bMoneyUpdate = FALSE;
	}

	if( m_lnTempStorageMoney != m_lnStorageMoney )
	{
		if( m_bStorageMoneyUpdate )
		{
			m_bStorageMoneyUpdate = FALSE;
		}else{
			// «ÿ≈∑¿∏∑Œ ∑Œ±◊∏¶ ≥≤?E
			HACKINGLOG_WRITE( "Different Update Storage Money!!, Account[%s], ID[%s], Storage Money %I64d, TempStorage Money %I64d, Storage Money Gap %I64d", 
							   m_szUID, m_szName, m_lnStorageMoney, m_lnTempStorageMoney, m_lnStorageMoney - m_lnTempStorageMoney );	
		}
		m_lnTempStorageMoney = m_lnStorageMoney;
	}else{
		m_bStorageMoneyUpdate = FALSE;
	}
#endif

	//	Note : ∞¯∞› ∏Ò«•¿« ¿Ø»øº∫ ∞À?E
	//		(¡÷¿«) ≈∏∞π¡§∫∏ ªÁ?EÅEπ›µÂΩ√ »£√‚«œø© ¿Ø»øº∫ ∞À?E« ?E
	//
	if ( m_TargetID.dwID != EMTARGET_NULL )
	{
		if ( !m_pGLGaeaServer->ValidCheckTarget(m_pLandMan,m_TargetID) )
			m_TargetID.dwID = EMTARGET_NULL;
	}
	
	if ( m_TargetID.dwID == EMTARGET_NULL && IsACTION(GLAT_ATTACK) )	TurnAction ( GLAT_IDLE );

	if ( IsValidBody () )
	{
		DoQuestCheckLimitTime ( fTime, fElapsedTime );

		if ( m_sHP.dwNow>0 )
		{
			float fCONFT_POINT_RATE(1.0f);
			if ( m_sCONFTING.IsCONFRONTING() )		fCONFT_POINT_RATE = m_sCONFTING.sOption.fHP_RATE;
			
			if( m_pLandMan->m_bTowerWarsMap )
			{				
				GLCHARLOGIC::SetLandBonusMSpeed( 0.6f );

				if( m_wHeadCount[0] != m_pLandMan->GetPcCount(0) || m_wHeadCount[1] != m_pLandMan->GetPcCount(1) || m_wHeadCount[2] != m_pLandMan->GetPcCount(2) )
				{
					for ( int i=0;i<SW_SCHOOL_MAX;++i)
						m_wHeadCount[i] = m_pLandMan->GetPcCount(i);

					GLMSG::SNETPC_UPDATE_HP_MULTIPLIER NetMsg;
					for ( int i=0;i<SW_SCHOOL_MAX;++i)
					{
						NetMsg.fMultiplier[i] = m_pLandMan->m_fHpMultiplier[i];
					}

					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID , &NetMsg );
				}
				fCONFT_POINT_RATE += m_pLandMan->m_fHpMultiplier[m_wSchool];				
			}
			else
			{
				m_wHeadCount[0] = 0;
				m_wHeadCount[1] = 0;
				m_wHeadCount[2] = 0;

				GLCHARLOGIC::SetLandBonusMSpeed( 0.0f );	
			}


			// ¡ˆ?E¿ÃªÛ»ø?Eæ˜µ•¿Ã∆Æ
			UpdateLandEffect();

			
			//	Note : ±‚√  LOGIC ¡§∫∏∏¶ æ˜?EÃ∆?
			//
			GLCHARLOGIC::UPDATE_DATA ( fTime, fElapsedTime, FALSE, fCONFT_POINT_RATE );

			UpdateClientState ( fElapsedTime );

			m_ARoundSlot.Update ( m_pLandMan );

			DoQuestReachZone();
		}
		else
		{
			//	Note : æ≤∑Ø¡˙∂ß ∫∏?Eπﬂª˝. ( ∞Ê«Ëƒ° + æ∆¿Ã≈€ + ±›æ◊ )
			DoFalling ();

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
			if ( m_bTracingUser )
			{
				NET_LOG_UPDATE_TRACINGCHAR TracingMsg;
				TracingMsg.nUserNum  = GetUserID();
				StringCchCopy( TracingMsg.szAccount, USR_ID_LENGTH+1, m_szUID );

				CString strTemp;
				strTemp.Format( "Dead!!, [%s][%s], Money:[%I64d]", m_szUID, m_szName, m_lnMoney );
				StringCchCopy( TracingMsg.szLogMsg, TRACING_LOG_SIZE, strTemp.GetString() );

				m_pGLGaeaServer->SENDTOAGENT( m_dwClientID, &TracingMsg );
			}
#endif
		}
	}

	// ∏ ¿« ¿ßƒ°∞° πŸ≤º¿ª∂ß ƒ˘Ω∫∆Æ Ω«∆– ø©∫Œ∏¶ ∆«¥‹«—¥Ÿ.
	if( m_sMapID != m_sOldMapID )
	{
		DoQuestCheckLeaveMap();

		m_sOldMapID = m_sMapID;
	}

	switch ( m_Action )
	{
	case GLAT_IDLE:
		m_fIdleTime += fElapsedTime;
		break;

	case GLAT_TALK:
		break;

	case GLAT_MOVE:
		{
			//	Note : ƒ…∏Ø¿« ¿Ãµø æ˜µ•¿Ã∆Æ.
			//
			m_actorMove.SetMaxSpeed ( GetMoveVelo () );
			m_actorMove.Update ( fElapsedTime );
			if ( !m_actorMove.PathIsActive() )
			{
				m_actorMove.Stop ();
				TurnAction ( GLAT_IDLE );
			}

			//	Note : ƒ…∏Ø¿« «ˆ¡¶ ¿ßƒ° æ˜µ•¿Ã∆Æ.
			//
			m_vPos = m_actorMove.Position();

			//	Note : ƒ…∏Ø¿« «ˆ¡¶ πÊ?Eæ˜µ•¿Ã∆Æ.
			//
			D3DXVECTOR3 vMovement = m_actorMove.NextPosition();
			if ( vMovement.x != FLT_MAX && vMovement.y != FLT_MAX && vMovement.z != FLT_MAX )
			{
				D3DXVECTOR3 vDirection = vMovement - m_vPos;
				if ( !DxIsMinVector(vDirection,0.2f) )
				{
					D3DXVec3Normalize ( &vDirection, &vDirection );
					m_vDir = vDirection;
				}
			}
		}
		break;

	case GLAT_ATTACK:
		{
			if ( !AttackProcess ( fElapsedTime ) )
			{
				TurnAction ( GLAT_IDLE );
			}

			GLACTOR* pACTOR = m_pGLGaeaServer->GetTarget ( m_pLandMan, m_TargetID );
			if ( pACTOR )
			{
				D3DXVECTOR3 vDirection = pACTOR->GetPosition() - m_vPos;
				D3DXVec3Normalize ( &vDirection, &vDirection );
				m_vDir = vDirection;
			}
		}
		break;

	case GLAT_SKILL:
		{
			if( !SkillProcess ( fElapsedTime ) )		
				TurnAction ( GLAT_IDLE );
		}
		break;

	case GLAT_SHOCK:
		{
			if( !ShockProcess ( fElapsedTime ) )		TurnAction ( GLAT_IDLE );
		}
		break;

	case GLAT_PUSHPULL:
		{
			m_actorMove.Update ( fElapsedTime );
			if ( !m_actorMove.PathIsActive() )
			{
				m_actorMove.Stop ();
				TurnAction ( GLAT_IDLE );
			}

			//	Note : Mob¿« «ˆ¡¶ ¿ßƒ° æ˜µ•¿Ã∆Æ.
			//
			m_vPos = m_actorMove.Position();
		}
		break;

	case GLAT_FALLING:
		break;

	case GLAT_DIE:
		break;
	case GLAT_GATHERING:
		break;
	};

	//	Note : Mob¿« «ˆ¡¶ ¿ßƒ° æ˜µ•¿Ã∆Æ.
	//
	m_vPos = m_actorMove.Position();


	
	if( m_bEventStart && m_bEventApply) //add btg attack
	{
		SEventState sEventState = GLGaeaServer::GetInstance().m_sEventState;
		if( sEventState.bEventStart ) 
		{
			SetBtgAddAttack( true , sEventState.fAttackGainRate );
		}
	}
	else
	{
		SetBtgAddAttack( false , 0);
	}

	

	return S_OK;
}

void GLChar::STATEBLOW ( const SSTATEBLOW &sStateBlow )
{
	int nIndex = 0;

	if ( sStateBlow.emBLOW <= EMBLOW_SINGLE )	nIndex = 0;
	else										nIndex = sStateBlow.emBLOW-EMBLOW_SINGLE;

	m_sSTATEBLOWS[nIndex] = sStateBlow;

	//	ªÛ≈¬¿Ã?E( ±‚¿˝ ) ¿ª πﬁ¿ª∂ß «ˆ¡¶ «‡¿ß ¡ﬂ¥‹.
	if ( sStateBlow.emBLOW == EMBLOW_STUN )
	{
		//	Note : æ≤∑Ø?E?≈¨∂Û¿Ãæ∆Æ µÈø°∞‘ æÀ∏≤.
		GLMSG::SNET_ACTION_BRD NetMsgBrd;
		NetMsgBrd.emCrow	= CROW_PC;
		NetMsgBrd.dwID		= m_dwGaeaID;
		NetMsgBrd.emAction	= GLAT_IDLE;

		//	Note : ¡÷∫Ø¿« Char ø°∞‘.
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );

		//	Note : ¿⁄Ω≈¿« ≈¨∂Û¿Ãæ∆Æø°.
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgBrd );

		TurnAction ( GLAT_IDLE );
	}
}

void GLChar::CURE_STATEBLOW ( DWORD dwCUREFLAG )
{
	BOOL bChanged = FALSE;

	for ( int i=0; i<EMBLOW_MULTI; ++i )
	{
		if ( m_sSTATEBLOWS[i].emBLOW==EMBLOW_NONE )		continue;

		bChanged = TRUE;
		if ( STATE_TO_DISORDER(m_sSTATEBLOWS[i].emBLOW)&dwCUREFLAG )
		{
			m_sSTATEBLOWS[i].emBLOW = EMBLOW_NONE;
		}
	}

	if ( !bChanged )	return;

	//	Note : ªÛ≈¬ ¿Ã?E∫Ø»≠ MsgFB.
	//
	GLMSG::SNETPC_CURESTATEBLOW_BRD NetMsgBRD;
	NetMsgBRD.dwID = m_dwGaeaID;
	NetMsgBRD.emCrow = CROW_PC;
	NetMsgBRD.dwCUREFLAG = dwCUREFLAG;

	//	Note : ¡÷∫Ø ≈¨∂Û¿Ãæ∆ÆµÈø°∞‘ ∏ﬁºº?E?E?
	//
	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBRD );

	//	Note : ?EÛø°∞?∏ﬁºº?E?E?
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBRD );
}

void GLChar::BUFF_REMOVE( DWORD dwBuffFlag, const SNATIVEID skill_id )
{
	GLMSG::SNETPC_SKILLHOLD_RS_BRD NetMsgSkillBrd;

	if ( dwBuffFlag == 0 ) return;
	PGLSKILL pSkillTarget = GLSkillMan::GetInstance().GetData ( skill_id );
	if ( !pSkillTarget ) return;

	for ( int i=0; i<SKILLFACT_SIZE; ++i )
	{
		if ( m_sSKILLFACT[i].sNATIVEID == NATIVEID_NULL() ) continue;
	
        PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( m_sSKILLFACT[i].sNATIVEID );
		if ( !pSkill ) continue;

		if ( dwBuffFlag == EMSPECA_BUFF_REMOVE && pSkillTarget->m_sBASIC.emIMPACT_SIDE == SIDE_ENERMY )
		{
			if ( IsImmune() )	break;
			if ( pSkill->m_sBASIC.emIMPACT_SIDE == SIDE_ENERMY )	continue;
		}
		else if ( dwBuffFlag == EMSPECA_BUFF_REMOVE && ( pSkillTarget->m_sBASIC.emIMPACT_SIDE == SIDE_OUR || pSkillTarget->m_sBASIC.emIMPACT_SIDE == SIDE_ANYBODY ) )
		{
			if ( pSkill->m_sBASIC.emIMPACT_SIDE == SIDE_OUR )	continue;
		}
		else if ( dwBuffFlag == EMSPECA_IMMUNE )
		{
			if( pSkillTarget->m_sBASIC.emIMPACT_SIDE == SIDE_ENERMY )
			{
				if ( !m_sSKILLFACT[i].GetSpec( EMSPECA_IMMUNE ) )
				continue;
			}
			else if( pSkillTarget->m_sBASIC.emIMPACT_SIDE == SIDE_OUR )
				continue;
		}
		
		DISABLESKEFF( i );

		NetMsgSkillBrd.bRESET[i] = true;
	}
	
	NetMsgSkillBrd.dwID = m_dwGaeaID;
	NetMsgSkillBrd.emCrow = CROW_PC;

	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgSkillBrd );
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgSkillBrd );
}


void GLChar::VAR_BODY_POINT ( const EMCROW emACrow, const DWORD dwAID, const BOOL bPartySkill, int nvar_hp, int nvar_mp, int nvar_sp )
{
	if ( m_sHP.dwNow == 0 )	return;

	DWORD wDxHP = m_sHP.VARIATION ( nvar_hp );
	m_sMP.VARIATION ( nvar_mp );
	m_sSP.VARIATION ( nvar_sp );

	m_sAssault.emCrow = emACrow;
	m_sAssault.dwID = dwAID;

	if ( emACrow == CROW_PC && nvar_hp<0 )
	{
		PGLCHAR pChar = m_pGLGaeaServer->GetChar ( dwAID );
		if ( pChar )
		{
			AddDamageLog ( m_cDamageLog, dwAID, pChar->m_dwUserID, wDxHP );
		}
	}

	// º“»Øºˆ∞° ∂ß∑»¿ª ∞Ê?Eº“»Ø?E¡÷¿Œ¿Ã ∂ß∏∞∞…∑Œ µ˚”œ
	if ( emACrow == CROW_SUMMON && nvar_hp<0 )
	{
		PGLSUMMONFIELD pSummon = GLGaeaServer::GetInstance().GetSummon ( dwAID );
		if( pSummon )
		{
			AddDamageLog ( m_cDamageLog, dwAID, pSummon->m_pOwner->m_dwUserID, wDxHP );
		}
	}

	//	[∆ƒ∆ºø¯µÈø°∞‘]
	if ( m_dwPartyID!=PARTY_NULL )
	{
		GLMSG::SNET_PARTY_MBR_POINT NetMsg;
		NetMsg.dwGaeaID = m_dwGaeaID;
		NetMsg.sHP = m_sHP;
		NetMsg.sMP = m_sMP;
		m_pGLGaeaServer->SENDTOPARTYCLIENT ( m_dwPartyID, (NET_MSG_GENERIC*) &NetMsg );
	}

	if ( nvar_hp<0 && IsACTION(GLAT_GATHERING) )
	{
		GLMSG::SNET_ACTION_BRD NetMsgBrd;
		NetMsgBrd.emCrow	= CROW_PC;
		NetMsgBrd.dwID		= m_dwGaeaID;
		NetMsgBrd.emAction	= GLAT_IDLE;

		//	Note : ¡÷∫Ø¿« Char ø°∞‘.
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );

		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgBrd );		
		TurnAction ( GLAT_IDLE );
	}
}

DWORD GLChar::SELECT_SKILLSLOT ( SNATIVEID skill_id )
{
	SKILLREALFACT_SIZE;
	DWORD dwSELECT = UINT_MAX;

	//	Note : Ω∫≈≥¿Ã µÈæ˚Ã• ±‚∫ª ΩΩ∑‘ º±≈√.
	//
	for ( DWORD i=0; i<SKILLREALFACT_SIZE; ++i )
	{
		if ( m_sSKILLFACT[i].sNATIVEID==skill_id )
		{
			return dwSELECT = i;
		}
	}

	float fAGE = FLT_MAX;
	for ( DWORD i=0; i<SKILLREALFACT_SIZE; ++i )
	{
		if ( m_sSKILLFACT[i].sNATIVEID==SNATIVEID(false) )
		{
			return dwSELECT = i;
		}

		if ( m_sSKILLFACT[i].fAGE < fAGE )
		{
			fAGE = m_sSKILLFACT[i].fAGE;
			dwSELECT = i;
		}
	}

	return dwSELECT;
}

BOOL GLChar::RECEIVE_SKILLFACT ( const SNATIVEID skill_id, const WORD wlevel, DWORD &dwSELECT )
{
	dwSELECT = SKILLFACT_SIZE;

	//	Ω∫≈≥ ¡§∫∏ ∞°¡Æø».
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )				return FALSE;
	SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[wlevel];

	BOOL bHOLD = FALSE;
	SSKILLFACT sSKILLEF;
	switch ( pSkill->m_sAPPLY.emBASIC_TYPE )
	{
	case SKILL::EMFOR_VARHP:
	case SKILL::EMFOR_VARMP:
	case SKILL::EMFOR_VARSP:
	case SKILL::EMFOR_DEFENSE:
	case SKILL::EMFOR_HITRATE:
	case SKILL::EMFOR_AVOIDRATE:
	case SKILL::EMFOR_VARAP:
	case SKILL::EMFOR_VARDAMAGE:
	case SKILL::EMFOR_VARDEFENSE:
	case SKILL::EMFOR_PA:
	case SKILL::EMFOR_SA:
	case SKILL::EMFOR_MA:
	case SKILL::EMFOR_RESIST:
	case SKILL::EMFOR_CP_RATE: //add cp
	case SKILL::EMFOR_CP_GAIN: //add cp
		bHOLD = TRUE;
		sSKILLEF.emTYPE = pSkill->m_sAPPLY.emBASIC_TYPE;
		sSKILLEF.fMVAR = sSKILL_DATA.fBASIC_VAR;
		break;
	};


	for( unsigned s=0;s<SKILL::SAPPLY::MAX_DESCRIPTOR;++s)
	{
		const SKILL::SIMPACT_DESCRIPTOR &desc = pSkill->m_sAPPLY.sadon[s];
		if( desc.emADDON != EMIMPACTA_NONE )
		{
			bHOLD = TRUE;
			sSKILLEF.adon[ s ].Assign( desc, wlevel );
		}
	}
	
	for( unsigned s=0;s<SKILL::SAPPLY::MAX_DESCRIPTOR;++s)
	{
		const SKILL::SSPEC_DESCRIPTOR &desc = pSkill->m_sAPPLY.spec[s];
		switch ( desc.emSPEC )
		{
		case EMSPECA_REFDAMAGE:
		case EMSPECA_NONBLOW:
		case EMSPECA_IMMUNE:		//add new spec
		case EMSPECA_PIERCE:
		case EMSPECA_TARRANGE:
		case EMSPECA_ATTACKRANGE:	//add new spec
		case EMSPECA_MOVEVELO:
		case EMSPECA_ATTACKVELO:
		case EMSPECA_SKILLDELAY:
		case EMSPECA_DURATION:		//add new spec
		case EMSPECA_PSY_DAMAGE_REDUCE:
		case EMSPECA_MAGIC_DAMAGE_REDUCE:
		case EMSPECA_PSY_DAMAGE_REFLECTION:
		case EMSPECA_MAGIC_DAMAGE_REFLECTION:
		case EMSPECA_DAMAGEABSORB:
		case EMSPECA_DEFENSE_SKILL_ACTIVE:
		case EMSPECA_INVISIBLE: //add invi-anti
		case EMSPECA_RECVISIBLE: //add invi-anti
		case EMSPECA_NOPOTION: //add antipot
		case EMSPECA_NOSKILL: //add antiskill
		case EMSPECA_CONTINUEDAMAGE:
		//case EMSPECA_BLOW_DMG: //add blowdmgskill
		//case EMSPECA_CRIT_RATE: //add critrateskill
		//case EMSPECA_CRIT_DMG: //add critdmgskill
		case EMSPECA_BLOW_RATE: //add blowrateskill
		case EMSPECA_STUN:
			bHOLD = TRUE;
			sSKILLEF.spec[ s ].Assign( desc, wlevel );
			break;
		};
	}
	
	//	Note : ¡ˆº”?EΩ∫≈≥¿œ ∞Ê?E√÷?EΩΩ∑‘¿ª √£æ∆º≠ Ω∫≈≥ »ø∞˙∏¶ ≥÷æ˚›‹.
	//
	if ( bHOLD )
	{
		sSKILLEF.sNATIVEID	= skill_id;
		sSKILLEF.wLEVEL		= wlevel;
		sSKILLEF.fAGE		= sSKILL_DATA.fLIFE;

		dwSELECT = SELECT_SKILLSLOT ( skill_id );
		m_sSKILLFACT[dwSELECT] = sSKILLEF;
	}

	return TRUE;
}

BOOL GLChar::RECEIVE_DRUGFACT ( EMITEM_DRUG emDRUG, WORD wCURE, BOOL bRATIO )
{
	//SKILL::EMTYPES emTYPE[3] = { SKILL::EMFOR_VARHP, SKILL::EMFOR_VARMP, SKILL::EMFOR_VARSP };
	//SNATIVEID nidNO[3] = { SNATIVEID(35,USHRT_MAX), SNATIVEID(35,USHRT_MAX), SNATIVEID(35,USHRT_MAX) };

	//if ( bRATIO )
	//{
	//	wCURE = m_sHP.wMax * wCURE / 100;
	//}

	//switch ( emDRUG )
	//{
	//case ITEM_DRUG_HP:
	//	nidNO[0].wSubID = 0;
	//	break;

	//case ITEM_DRUG_MP:
	//	nidNO[1].wSubID = 1;
	//	break;

	//case ITEM_DRUG_SP:
	//	nidNO[2].wSubID = 2;
	//	break;

	//case ITEM_DRUG_HP_MP:
	//	nidNO[0].wSubID = 0;
	//	nidNO[1].wSubID = 1;
	//	break;

	//case ITEM_DRUG_MP_SP:
	//	nidNO[1].wSubID = 1;
	//	nidNO[2].wSubID = 2;
	//	break;

	//case ITEM_DRUG_HP_MP_SP:
	//	nidNO[0].wSubID = 0;
	//	nidNO[1].wSubID = 1;
	//	nidNO[2].wSubID = 2;
	//	break;
	//};

	//for ( int i=0; i<3; ++i )
	//{
	//	const SNATIVEID &skill = nidNO[i];

	//	if ( skill.wSubID == USHRT_MAX )		continue;

	//	SSKILLFACT sSKILLEF;
	//	sSKILLEF.emTYPE = emTYPE[i];
	//	
	//	//	Ω∫≈≥ ¡§∫∏ ∞°¡Æø».
	//	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill );
	//	if ( !pSkill )				return FALSE;
	//	SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[0];

	//	float fRATE = wCURE/float(m_sHP.wMax);
	//	if ( fRATE>1.0f )	fRATE = 1.0f;

	//	float fLIFE = sSKILL_DATA.fLIFE;
	//	if ( fLIFE==0.0f )	fLIFE = 0.01f;

	//	sSKILLEF.sNATIVEID	= skill;
	//	sSKILLEF.wLEVEL		= 0;
	//	sSKILLEF.fAGE		= fLIFE;
	//	sSKILLEF.fMVAR		= fRATE/fLIFE;

	//	WORD wSELECT = SKILLREALFACT_SIZE + i;
	//	m_sSKILLFACT[wSELECT] = sSKILLEF;

	//	GLMSG::SNETPC_REQ_SKILLHOLDEX_BRD NetMsgBRD;
	//	NetMsgBRD.emCrow = GetCrow();
	//	NetMsgBRD.dwID = GetCtrlID();
	//	NetMsgBRD.wSLOT = wSELECT;
	//	NetMsgBRD.sSKILLEF = sSKILLEF;

	//	//	Note : 'Ω∫≈≥?EÅE¿« ¡÷∫Ø ≈¨∂Û¿Ãæ∆ÆµÈø°∞‘ ∏ﬁºº?E?E?
	//	//
	//	SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsgBRD );

	//	//	Note : Ω∫≈≥ ?EÛø°∞?∏ﬁºº?E?E?
	//	m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID(), &NetMsgBRD );
	//}

	return TRUE;
}

void GLChar::ReBirthDecExp ()
{
	if ( m_nDECEXP==0 )		return;

	m_lnReExp = GetReExp();

	if ( (m_sExperience.lnNow-m_nDECEXP) < 0 )	m_sExperience.lnNow = 0;
	else	m_sExperience.lnNow -= m_nDECEXP;

	//	Note : ∞Ê«Ëƒ° ∫Ø»≠ ≈¨∂Û¿Ãæ∆Æø° æÀ∑¡¡‹.
	//
	GLMSG::SNETPC_UPDATE_EXP NetMsgExp;
	NetMsgExp.lnNowExp = m_sExperience.lnNow;
	m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgExp );
}

LONGLONG GLChar::GetReExp ()
{
	LONGLONG nDecExp = 0;
	LONGLONG nReExp = 0;

	nDecExp = m_nDECEXP;

	if ( nDecExp > m_sExperience.lnNow ) nDecExp = m_sExperience.lnNow;
	if ( nDecExp <= 0 )	return 0;


	float fRExpRecovery = GLOGICEX::GLDIE_RECOVERYEXP( m_wLevel );
	nReExp = (LONGLONG)(nDecExp * fRExpRecovery);

	if ( nReExp < 0  ) nReExp = 0;	
	if ( nDecExp < nReExp ) nReExp = nDecExp;

	return nReExp;

}
LONGLONG GLChar::GetReExpMoney ( LONGLONG nReExp )
{
	LONGLONG nDecMoney = 0;

	if ( nReExp <= 0 ) return 0;

	float fRMoney = GLOGICEX::GLDIE_EXPMONEY( m_wLevel );
	nDecMoney = (LONGLONG)(nReExp * fRMoney);

	return nDecMoney;
}

void GLChar::DROP_PUTONITEM ( DWORD _dwNUM, float _fRATE )
{
//	GLGaeaServer & glGaeaServer = m_pGLGaeaServer;
	GLITEMLMT & glItemmt = GLITEMLMT::GetInstance();

	for ( DWORD i=0; i<_dwNUM; ++i )
	{
		if ( RANDOM_GEN(_fRATE) )
		{
			DWORD dwSLOT_NUM(0);

			DWORD dwSLOT_LIST[SLOT_NSIZE_S_2];
			for ( int j=0; j<SLOT_NSIZE_S_2; ++j )
			{
				EMSLOT emSLOT = EMSLOT(j);

				if ( VALID_SLOT_ITEM(emSLOT) && !GET_SLOT_ITEM(emSLOT).IsGM_GENITEM() )
				{
					// when you miss this part everything will be fuck up! -Eduj
					if ( !GET_SLOT_ITEM(emSLOT).IsNonDrop_Ex() )
					{
					SITEM* pITEM = GET_SLOT_ITEMDATA(emSLOT);
					
					//	∞≈∑°ø…º«
					if ( pITEM && pITEM->sBasicOp.IsTHROW() )
						dwSLOT_LIST[dwSLOT_NUM++] = j;
					}
				}
			}

			if ( dwSLOT_NUM==0 )					break;

			DWORD dwSLOT = (DWORD) ( rand()%dwSLOT_NUM );
			
			if ( dwSLOT >= SLOT_NSIZE_S_2 )				break;

			dwSLOT = dwSLOT_LIST[dwSLOT];
			if ( !VALID_SLOT_ITEM(EMSLOT(dwSLOT)) )	break;

			// ∫∏µÂ¥¬ µÂ∂¯µ«?Eæ ¥¬¥Ÿ.
			if ( dwSLOT == SLOT_VEHICLE )			break;

			SITEMCUSTOM sITEM_CUSTOM = m_PutOnItems[dwSLOT];
			
			D3DXVECTOR3 vGenPos = D3DXVECTOR3(m_vPos) + D3DXVECTOR3(RANDOM_NUM*4.0f,0.0f,RANDOM_NUM*4.0f);
			BOOL bCollision;
			D3DXVECTOR3 vCollision;
			bCollision = m_pLandMan->IsCollisionNavi
			(
				D3DXVECTOR3(vGenPos)+D3DXVECTOR3(0,+5,0),
				D3DXVECTOR3(vGenPos)+D3DXVECTOR3(0,-5,0),
				vCollision
			);

			if ( bCollision )
			{
				//	Note :æ∆¿Ã≈€¿« º“¿Ø ¿Ã?E∞Ê∑Œ ±‚∑œ.
				//
				glItemmt.ReqItemRoute ( sITEM_CUSTOM, ID_CHAR, m_dwCharID, ID_CHAR, 0, EMITEM_ROUTE_GROUND, sITEM_CUSTOM.wTurnNum );


				PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
				if ( pMyPet && pMyPet->IsValid () ) 
				{
					//dmk14 | 11-21-16 | dual pet skill
					for( unsigned s=0; s<PETSLOT_SIZE;++s) {
					int nPetMID = pMyPet->m_sActiveSkillID[s].wMainID;
					int nPetSID = pMyPet->m_sActiveSkillID[s].wSubID;
						// Note : «ˆ¿Á ∆Í Ω∫≈≥ »Æ¿Œ ∑Œ±◊ 
					glItemmt.ReqAction ( m_dwCharID,		// ¥ÁªÁ¿⁄.
										EMLOGACT_PET_SKILL, // «‡¿ß.
										ID_CHAR, 0,  0,				
										nPetMID,			// Pet Skill MID
										nPetSID, 			// Pet Skill SID
										0 );		
					}
				}


				//	æ∆¿Ã≈€ ¡¶∞≈.
				GLCHARLOGIC::RELEASE_SLOT_ITEM ( (EMSLOT) dwSLOT );

				//	[¿⁄Ω≈ø°∞‘] SLOTø° ¿÷æ˙?Eæ∆¿Ã≈∆ ¡¶∞≈.
				GLMSG::SNETPC_PUTON_RELEASE NetMsg_PutOn_Release((EMSLOT)dwSLOT);
				m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg_PutOn_Release);

				//	æ∆¿Ã≈€ πﬂª˝.
				m_pLandMan->DropItem ( vGenPos, &sITEM_CUSTOM );
			}
		}
	}
}

void GLChar::GenerateReward ( bool bCONFT /*=false*/, bool bCONFT_SCHOOL /*=false*/ )
{
	//	Note : ∞Ê«Ëƒ° º’?E√≥∏Æ.
	//
	bool bBRIGHTEVENT = m_pGLGaeaServer->IsBRIGHTEVENT();

	m_nDECEXP = 0;
	// ?EÀ¿?¿Ã∞≈≥™ ∏˜«—≈◊ ¡◊æ˙¿ª∞Ê?E
	if ( ISOFFENDER() || m_sAssault.emCrow!=CROW_PC )
	{
		m_nDECEXP = __int64 ( GLOGICEX::GLDIE_DECEXP(GETLEVEL()) * 0.01f * GET_LEVELUP_EXP() );
		
		if ( bCONFT )
		{
			//m_nDECEXP /= 10;	//	?E√Ω?∞Ê«Ëƒ° º’ªÛ¿∫ π›∞®Ω√≈≤¥Ÿ.
			m_nDECEXP = 0;		//	?E√Ω?∞Ê«Ëƒ° º’ªÛ¿∫ æ¯¿Ω.
		}
		else
		{
			m_nDECEXP = __int64 ( m_nDECEXP * GET_PK_DECEXP_RATE()/100.0f );
		}
	}

	//	Note : ∞Ê«Ëƒ° πﬂª˝.
	//
	if ( m_nDECEXP > 0 )
	{
		//STARGETID mytarid(GETCROW(),m_dwGaeaID);

		//if ( m_sAssault.emCrow == CROW_PC && m_sAssault.dwID!=GAEAID_NULL )
		//{
		//	PGLCHAR pChar = m_pGLGaeaServer->GetChar ( m_sAssault.dwID );
		//	if ( pChar )
		//	{
		//		pChar->ReceiveKillExp ( mytarid, bCONFT_SCHOOL );
		//	}
		//}

		//if ( !m_cDamageLog.empty() )
		//{
		//	DAMAGELOG_ITER iter = m_cDamageLog.begin ();
		//	DAMAGELOG_ITER iter_end = m_cDamageLog.end ();
		//	for ( ; iter!=iter_end; ++iter )
		//	{
		//		SDAMAGELOG &sDamageLog = (*iter).second;

		//		PGLCHAR pChar = m_pGLGaeaServer->GetChar ( sDamageLog.dwGaeaID );
		//		if ( !pChar )	continue;
		//		if ( sDamageLog.dwUserID != pChar->m_dwUserID )		continue;

		//		pChar->ReceiveAttackExp ( mytarid, sDamageLog.dwDamage, FALSE, bCONFT_SCHOOL );
		//	}
		//}
	}

	m_cDamageLog.clear ();

	// º∫?E¿Ã∫•∆Æ ¡ﬂø°¥¬ ∞Ê«Ëƒ° ∞®º“«œ?Eæ ?Eæ∆¿Ã≈€µµ µÂ∂¯µ«?Eæ ¿Ω
	if ( bBRIGHTEVENT ) 
	{
		m_nDECEXP = 0; 
		return;
	}

	// ≈¨∑¥ πË∆≤¡ﬂ¿Ã?E∞Ê«Ëƒ° º’Ω« π◊ æ∆¿Ã≈€ µÂ?Eæ¯¿Ω
	if ( m_sAssault.emCrow==CROW_PC && m_pLandMan->IsClubBattleZone() )
	{
		GLClubMan &cClubMan = GLGaeaServer::GetInstance().GetClubMan();
		GLCLUB *pCLUB = cClubMan.GetClub ( m_dwGuild );
		if ( pCLUB )
		{
			GLChar* pChar = GLGaeaServer::GetInstance().GetChar( m_sAssault.dwID );
			if ( pChar )
			{
				if ( pCLUB->IsBattle( pChar->m_dwGuild ) )
				{
					m_nDECEXP = 0;
					return;
				}
				
				GLCLUB *pCLUB_Tar = cClubMan.GetClub ( pChar->m_dwGuild );
				if ( pCLUB_Tar && pCLUB->IsBattleAlliance( pCLUB_Tar->m_dwAlliance ) )
				{
					m_nDECEXP = 0;
					return;
				}
			}
		}
	}

	// ∞Ê«Ëƒ° NonDrop ∏ ¿œ∞Ê?E
	if ( !m_pLandMan->IsDecreaseExpMap () ) m_nDECEXP = 0;

	//	Note : ?E√¿?æ∆¥œ?EµÂ∑”∏ ¿œ ∞Ê?Eæ∆¿Ã≈€ µÂ∑”. && m_bProtectPutOnItem(∆÷¿« æ∆¿Ã≈€ ∫∏»£Ω∫≈≥)
	//
	if ( m_pLandMan && m_pLandMan->IsItemDrop() && !bCONFT && !m_bProtectPutOnItem )
	{
		//	?EÀ¿⁄¿?∞Ê?E
		if ( ISOFFENDER() )
		{
			DWORD dwDROP_NUM = GET_PK_ITEMDROP_NUM();
			float fDROP_RATE = GET_PK_ITEMDROP_RATE();
			DROP_PUTONITEM ( dwDROP_NUM, fDROP_RATE );
		}
		//	¿œπ›¿˚¿∏∑Œ ¡◊¿ª∞Ê?E
		else if ( GLCONST_CHAR::fNONPK_ITEM_DROP!=0 )
		{
			DROP_PUTONITEM ( 1, GLCONST_CHAR::fNONPK_ITEM_DROP );
		}
	}
}

void GLChar::DelPlayHostile ()
{
//	GLGaeaServer & glGaeaServer = m_pGLGaeaServer;

	GLMSG::SNETPC_PLAYERKILLING_DEL NetMsgDel;
	PGLCHAR pCHAR = NULL;
	for ( MAPPLAYHOSTILE_ITER pos = m_mapPlayHostile.begin(); pos != m_mapPlayHostile.end(); ++pos )
	{
		//	Note : ¿˚?E?ªË¡¶ æÀ∏≤.		
		NetMsgDel.dwCharID = pos->first;
		m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgDel );

		pCHAR = m_pGLGaeaServer->GetCharID ( pos->first );
		if( pCHAR )
			pCHAR->DelPlayHostile ( m_dwCharID );

		if( !pos->second )
			CDebugSet::ToLogFile( "GLChar::DelPlayHostile, pos->second = NULL" );
	}

	DEL_PLAYHOSTILE_ALL();
}

void GLChar::DelPlayHostile ( DWORD dwCharID )
{
	bool bDEL = DEL_PLAYHOSTILE ( dwCharID );
	if ( bDEL )
	{
		//	Note : ¿˚?E?ªË¡¶ æÀ∏≤.
		GLMSG::SNETPC_PLAYERKILLING_DEL NetMsgDel;
		NetMsgDel.dwCharID = dwCharID;
		m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgDel );
	}
}

//	∆Ø¡§ ≈¨∑¥¿« ¿˚?E⁄∏?∏µŒ ¡ˆø˚–Ÿ.
void GLChar::DelPlayHostileClub( DWORD dwClubID )
{
	PGLCHAR pCHAR = NULL;

	GLMSG::SNETPC_PLAYERKILLING_DEL NetMsgDel;
	
	MAPPLAYHOSTILE_ITER pos = m_mapPlayHostile.begin();
	MAPPLAYHOSTILE_ITER pos_end = m_mapPlayHostile.end();
	MAPPLAYHOSTILE_ITER del;

	GLClubMan &sClubMan = m_pGLGaeaServer->GetClubMan();
	GLCLUB *pClub = sClubMan.GetClub(m_dwGuild);
	if ( !pClub )	return;
	
	for ( ; pos != pos_end;  )
	{
		del = pos++;
		//	Note : ¿˚?E?ªË¡¶ æÀ∏≤.	
		pCHAR = m_pGLGaeaServer->GetCharID ( del->first );
		if ( !pCHAR ) continue;

		GLCLUB *pClub_S = sClubMan.GetClub(pCHAR->m_dwGuild);
		if ( !pClub_S )	return;

		if ( pClub->IsBattle( pCHAR->m_dwGuild ) || pClub->IsBattleAlliance( pClub_S->m_dwAlliance ) )
		{
			NetMsgDel.dwCharID = del->first;
			m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgDel );
			
			pCHAR->DelPlayHostile ( m_dwCharID );
		}

		m_mapPlayHostile.erase( del );
	}
}


void GLChar::DoFalling ()
{
//	GLGaeaServer & glGaeaServer = m_pGLGaeaServer;

	if ( m_sCONFTING.IsCONFRONTING() )
	{
		switch ( m_sCONFTING.emTYPE )
		{
		case EMCONFT_ONE:
			{
				STARGETID sCONFTID(CROW_PC,m_sCONFTING.dwTAR_ID);

				//	Note : ?E√µµ¡??E√¿⁄∞?æ∆¥— ƒ≥∏Ø≈Õ≥™ ∏˜ø°∞‘ ¡◊¿ª ∞Ê?E
				//
				if( m_sAssault != sCONFTID )
				{
					//	Note : ªÛ?EÅE?E√¿?ID πÈ?E Reset Ω√ø° π´»ø»≠µ«?E∂ßπÆø° πÃ∏Æ πÈ?E
					//
					const DWORD dwTAR_ID = m_sCONFTING.dwTAR_ID;

					//	Note : (¿⁄Ω≈) ?E?¡æ?E
					//
					ResetConfront(EMCONFRONT_END_FAIL);

					//	Note : ?E?ªÛ?EÅE√£¿Ω.
					//
					PGLCHAR pCONFT = m_pGLGaeaServer->GetChar(dwTAR_ID);
					if ( pCONFT )
					{
						//	Note : ?E?ªÛ?EÊ¿?øµ«‚¿ª ¡ÿ ∞Ê«Ëƒ° ∑Œ±◊ ¡¶∞≈Ω√≈¥.
						//
						DAMAGELOG_ITER iter;
						iter = m_cDamageLog.find ( pCONFT->m_dwUserID );
						if ( iter!=m_cDamageLog.end() )		m_cDamageLog.erase ( iter );

						//	Note : (ªÛ?EÅE ?E?¡æ?E
						//
						pCONFT->ResetConfront ( EMCONFRONT_END_FAIL );
					}

					goto _DIE_ACTION;
				}

				//	Note : æ≤∑Ø¡˙∂ß ∫∏?Eπﬂª˝. ( ∞Ê«Ëƒ° + æ∆¿Ã≈€ + ±›æ◊ ?E?E)
				//
				GenerateReward ( true, m_sCONFTING.sOption.bSCHOOL );

				//	Note : ªÛ?EÅE?E√¿?ID πÈ?E Reset Ω√ø° π´»ø»≠µ«?E∂ßπÆø° πÃ∏Æ πÈ?E
				//
				const DWORD dwTAR_ID = m_sCONFTING.dwTAR_ID;
				const SCONFT_OPTION sOption = m_sCONFTING.sOption;

				//	Note : (¿⁄Ω≈) ?E?¡æ?E
				//
				ResetConfront(EMCONFRONT_END_LOSS);

				//	Note : ?E?ªÛ?EÅE√£¿Ω.
				//
				PGLCHAR pCONFT = m_pGLGaeaServer->GetChar(dwTAR_ID);
				if ( pCONFT==NULL )			return;

				//	Note : (ªÛ?EÅE ?E?¡æ?E
				//
				EMCONFRONT_END emCONFT_END = (pCONFT->GETHP()>0) ? EMCONFRONT_END_WIN : EMCONFRONT_END_LOSS;
				pCONFT->ResetConfront ( emCONFT_END );

				//	Note : ¿⁄Ω≈ ª˝»∞¡°?E∫Ø»≠.
				//
				if ( GLCONST_CHAR::nCONFRONT_LOSS_LP!=0 && GLCONST_CHAR::nCONFRONT_WIN_LP!=0 )
				{
					float fLIFE_P(0);

					fLIFE_P = GLCONST_CHAR::nCONFRONT_LOSS_LP - (GETLEVEL()-pCONFT->GETLEVEL())/2.0f
						+ (sOption.fHP_RATE-sOption.fTAR_HP_RATE);
					LIMIT ( fLIFE_P, 0.0f, -20.0f );

					ReceiveLivingPoint ( (int)fLIFE_P );

					//	Note : ªÛ?EÅEª˝»∞¡°?E∫Ø»≠.
					//
					fLIFE_P = GLCONST_CHAR::nCONFRONT_WIN_LP + (GETLEVEL()-pCONFT->GETLEVEL())/2.0f
						+ (sOption.fHP_RATE-sOption.fTAR_HP_RATE);
					LIMIT ( fLIFE_P, 20.0f, 0.0f );

					pCONFT->ReceiveLivingPoint ( (int)fLIFE_P );
				}
			}
			break;

		case EMCONFT_PARTY:
			{
				bool breward(false);
				if ( m_sAssault.emCrow==CROW_PC )
				{
					GLPARTY_FIELD *pConftParty = m_pGLGaeaServer->GetParty(m_sCONFTING.dwTAR_ID);
					if ( pConftParty )
					{
						const GLPARTY_FNET *pPARTY = pConftParty->GETMEMBER(m_sAssault.dwID);
						if ( pPARTY )	breward = pPARTY->m_bConfront;
					}
				}

				if ( !breward )
				{
					m_cDamageLog.clear();

					//	Note : (¿⁄Ω≈) ?E?¡æ?E
					//
					ResetConfront(EMCONFRONT_END_NOTWIN);

					goto _DIE_ACTION;
				}

				//	Note : æ≤∑Ø¡˙∂ß ∫∏?Eπﬂª˝. ( ∞Ê«Ëƒ° + æ∆¿Ã≈€ + ±›æ◊ ?E?E)
				//
				GenerateReward ( true, m_sCONFTING.sOption.bSCHOOL );

				//	Note : (¿⁄Ω≈) ?E?¡æ?E
				//
				ResetConfront(EMCONFRONT_END_NOTWIN);
			}
			break;

		case EMCONFT_GUILD:
			{
				bool breward(false);
				if ( m_sAssault.emCrow==CROW_PC )
				{
					GLClubMan &sClubMan = m_pGLGaeaServer->GetClubMan();
					PGLCHAR pCHAR = m_pGLGaeaServer->GetChar(m_sAssault.dwID);

					GLCLUB *pConftClub = sClubMan.GetClub(m_sCONFTING.dwTAR_ID);
					if ( pConftClub && pCHAR )
					{
						breward = pConftClub->ISCONFT_MEMBER ( pCHAR->m_dwCharID );
					}
				}

				if ( !breward )
				{
					m_cDamageLog.clear();

					//	Note : (¿⁄Ω≈) ?E?¡æ?E
					//
					ResetConfront(EMCONFRONT_END_NOTWIN);

					goto _DIE_ACTION;
				}

				//	Note : æ≤∑Ø¡˙∂ß ∫∏?Eπﬂª˝. ( ∞Ê«Ëƒ° + æ∆¿Ã≈€ + ±›æ◊ ?E?E)
				//
				GenerateReward ( true );

				//	Note : (¿⁄Ω≈) ?E?¡æ?E
				//
				ResetConfront(EMCONFRONT_END_NOTWIN);
			}
			break;
		}

		//	Memo :	?E√¡ﬂ¿Ã∂Û∏ÅEæ∆∑°ƒ⁄µÂ¥¬ Ω««‡«œ?Eæ ¥¬¥Ÿ.
		return;
	}

	if ( m_sQITEMFACT.IsACTIVE() )
	{
		m_sQITEMFACT.RESET();

		GLMSG::SNETPC_QITEMFACT_END_BRD	NetMsgBrd;
		NetMsgBrd.dwGaeaID = m_dwGaeaID;

		//	Note : ¡æ∑·µ«æ˙¿ª ∞Ê?E¿⁄Ω≈ø°∞‘ æÀ∏≤.
		m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgBrd );

		//	Note : ¡æ∑·µ«æ˙¿ª ∞Ê?E¡÷∫Ø ªÁ∂˜ø°∞‘ æÀ∏≤.
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );

		GLMSG::SNETPC_QITEMFACT_TIMEUPDATE_BRD	NetMsgTUBrd; //add qbox
		NetMsgTUBrd.dwGaeaID = m_dwGaeaID;
		NetMsgTUBrd.fQBoxTime = 0;
		m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgTUBrd );
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgTUBrd );
	}

_DIE_ACTION:

	//	Note : player ∞° ¡◊ø¥¿ª ∞Ê?E
	DWORD dwKILL_ID(0);
	if ( m_sAssault.emCrow==CROW_PC )
	{
		PGLCHAR pCHAR = m_pGLGaeaServer->GetChar(m_sAssault.dwID);
		if ( pCHAR )
		{
			dwKILL_ID = pCHAR->m_dwCharID;
			int nBRIGHT(0), nLIFE(0);

			bool bClubBattle = false;
			bool bAllianceBattle = false;
			GLClubMan &cClubMan = m_pGLGaeaServer->GetClubMan();
			GLCLUB *pMyClub = cClubMan.GetClub ( m_dwGuild );
			GLCLUB *pTarClub = cClubMan.GetClub ( pCHAR->m_dwGuild );
			
			if ( pMyClub && pTarClub )
			{
				bClubBattle =  pMyClub->IsBattle( pCHAR->m_dwGuild );
				bAllianceBattle = pMyClub->IsBattleAlliance ( pTarClub->m_dwAlliance );
			}

			bool bClubDeathMatch = false;

			if ( m_pLandMan->m_bClubDeathMatchMap )
			{
				GLClubDeathMatch* pCDM = GLClubDeathMatchFieldMan::GetInstance().Find( m_pLandMan->m_dwClubMapID );
				if( pCDM && pCDM->IsBattle() ) bClubDeathMatch = true;
			}

			bool bSchoolWars = false;

			if ( m_pLandMan->m_bSchoolWarsMap )
			{
				GLSchoolWars* pSW = GLSchoolWarsFieldMan::GetInstance().Find( m_pLandMan->m_dwSchoolWarMapID );
				if( pSW && pSW->IsBattle() ) bSchoolWars = true;
			}

			bool bRoyalRumble = false;

			if ( m_pLandMan->m_bRoyalRumbleMap )
			{
				GLRoyalRumble* pRR = GLRoyalRumbleFieldMan::GetInstance().Find( m_pLandMan->m_dwRoyalRumbleMapID );
				if( pRR && pRR->IsBattle() ) bRoyalRumble = true;
			}

			bool bTowerWars = false;

			if ( m_pLandMan->m_bTowerWarsMap )
			{
				GLTowerWars* pSW = GLTowerWarsFieldMan::GetInstance().Find( m_pLandMan->m_dwTowerWarsMapID );
				if( pSW && pSW->IsBattle() ) bTowerWars = true;
			}

			// ≈¨∑¥πË∆≤Ω√ ¡◊æ˙¿ª ∞ÊøÏ √≥∏Æ
			if ( ( bClubBattle || bAllianceBattle ) && m_pLandMan->IsClubBattleZone() )
			{
				ClubBattleSetPoint( m_dwGuild, pCHAR->m_dwGuild, bAllianceBattle );

				DWORD dwClubID_P, dwClubID_S;
				if ( bAllianceBattle ) 
				{
					dwClubID_P = pMyClub->m_dwAlliance;
					dwClubID_S = pTarClub->m_dwAlliance;
				}
				else
				{
					dwClubID_P = m_dwGuild;
					dwClubID_S = pCHAR->m_dwGuild;
				}

				GLMSG::SNET_CLUB_BATTLE_POINT_UPDATE NetMsg;

				NetMsg.dwBattleClubID = dwClubID_S;
				NetMsg.bKillPoint = false;
				
				m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );

				NetMsg.dwBattleClubID = dwClubID_P;
				NetMsg.bKillPoint = true;
													
				m_pGLGaeaServer->SENDTOCLIENT ( pCHAR->m_dwClientID, &NetMsg );
			
			}
			//	CDM ªÛ»≤
			else if ( bClubDeathMatch )
			{
				GLClubDeathMatch* pCDM = GLClubDeathMatchFieldMan::GetInstance().Find( m_pLandMan->m_dwClubMapID );	
				if ( pCDM )
				{
					pCDM->AddCDMScore( pCHAR->m_dwGuild, m_dwGuild );

					//	POINT UPDATE ≥™?E ªÛ?EÅE
					GLMSG::SNET_CLUB_DEATHMATCH_POINT_UPDATE NetMsg;
					NetMsg.bKillPoint = false;					
					m_pGLGaeaServer->SENDTOCLUBCLIENT_ONMAP ( m_pLandMan->GetMapID().dwID, m_dwGuild, &NetMsg );

					NetMsg.bKillPoint = true;														
					m_pGLGaeaServer->SENDTOCLUBCLIENT_ONMAP ( pCHAR->m_pLandMan->GetMapID().dwID, pCHAR->m_dwGuild, &NetMsg );
	
				}

			}
			else if ( bSchoolWars )
			{
				GLSchoolWars* pSW = GLSchoolWarsFieldMan::GetInstance().Find( m_pLandMan->m_dwSchoolWarMapID );	
				if ( pSW )
				{
					pSW->AddSWScore( pCHAR->m_wSchool, m_wSchool );
					pSW->AddSWPScore( pCHAR->m_dwCharID, pCHAR->m_dwGaeaID, m_dwCharID, m_dwGaeaID );

					//GLSchoolWarsFieldMan::GetInstance().UpdateSWRanking( pSW->m_dwID );
					//GLSchoolWarsFieldMan::GetInstance().UpdateSWPRanking( pSW->m_dwID );

					GLMSG::SNET_SCHOOL_WARS_POINT_UPDATE NetMsg;
					NetMsg.bKillPoint = false;					
					m_pGLGaeaServer->SENDTOSCHOOLCLIENT_ONMAP ( m_pLandMan->GetMapID().dwID, m_wSchool, &NetMsg );
					NetMsg.bKillPoint = true;														
					m_pGLGaeaServer->SENDTOSCHOOLCLIENT_ONMAP ( pCHAR->m_pLandMan->GetMapID().dwID, pCHAR->m_wSchool, &NetMsg );
	
					GLMSG::SNET_SCHOOL_WARS_PPOINT_UPDATE NetPlayerMsg;
					NetPlayerMsg.bKillPoint = false;					
					m_pGLGaeaServer->SENDTOCLIENT_ONMAP ( m_pLandMan->GetMapID().dwID, &NetPlayerMsg );
					NetPlayerMsg.bKillPoint = true;														
					m_pGLGaeaServer->SENDTOCLIENT_ONMAP ( pCHAR->m_pLandMan->GetMapID().dwID, &NetPlayerMsg );
				}
			}

			else if ( bRoyalRumble )
			{
				GLRoyalRumble* pRR = GLRoyalRumbleFieldMan::GetInstance().Find( m_pLandMan->m_dwRoyalRumbleMapID );	
				if ( pRR )
				{
					pRR->AddRRPScore( pCHAR->m_dwCharID, pCHAR->m_dwGaeaID, m_dwCharID, m_dwGaeaID );

					GLMSG::SNET_ROYAL_RUMBLE_PPOINT_UPDATE NetPlayerMsg;
					NetPlayerMsg.bKillPoint = false;					
					m_pGLGaeaServer->SENDTOCLIENT_ONMAP ( m_pLandMan->GetMapID().dwID, &NetPlayerMsg );
					NetPlayerMsg.bKillPoint = true;														
					m_pGLGaeaServer->SENDTOCLIENT_ONMAP ( pCHAR->m_pLandMan->GetMapID().dwID, &NetPlayerMsg );
				}
			}
			else if ( bTowerWars )
			{
				GLTowerWars* pSW = GLTowerWarsFieldMan::GetInstance().Find( m_pLandMan->m_dwTowerWarsMapID );	
				if ( pSW && pCHAR )
				{		
					pSW->AddSWPScore( pCHAR->m_dwCharID, pCHAR->m_dwGaeaID, m_dwCharID, m_dwGaeaID );

					/*GLMSG::SNET_TOWERWARS_CTFPOINT_UPDATE NetPlayerMsg;
					NetPlayerMsg.bDamagePoint = false;
					NetPlayerMsg.bHealPoint = false;
					NetPlayerMsg.bResuPoint = false;
					NetPlayerMsg.bKillPoint = false;		
					NetPlayerMsg.dwDamage = 0;
					NetPlayerMsg.dwHeal = 0;			
					m_pGLGaeaServer->SENDTOPLAYERCLIENT_ONMAP ( m_pLandMan->GetMapID().dwID, m_dwCharID, &NetPlayerMsg );
					NetPlayerMsg.bKillPoint = true;														
					m_pGLGaeaServer->SENDTOPLAYERCLIENT_ONMAP ( pCHAR->m_pLandMan->GetMapID().dwID, pCHAR->m_dwCharID, &NetPlayerMsg );*/
				}
			}

			//	Note : º≠∑Œ ¿˚?E«‡¿ß¿⁄¿œ ∞Ê?E
			else if ( !IS_HOSTILE_ACTOR(pCHAR->m_dwCharID) && pCHAR->IS_HOSTILE_ACTOR(m_dwCharID) )
			{
				//	Note : ?EÀ¿?µ˚Õﬁ¿Œ ∞Ê?EªÛ?EÊø°∞?ª˝»∞¡°?E¡‹.
				//

				if ( ISOFFENDER() )
				{
					DWORD dwMY_PK_LEVEL = GET_PK_LEVEL();
					if ( dwMY_PK_LEVEL != UINT_MAX && dwMY_PK_LEVEL>0 )
					{
						//	Note : ª˝»∞¡°?E∫Ø»≠.
						nLIFE = 7-(GLCONST_CHAR::EMPK_STATE_LEVEL-dwMY_PK_LEVEL);
						pCHAR->ReceiveLivingPoint ( nLIFE );
					}
				}
				//	¿⁄Ω≈¿« µ˚Õﬁ¿Ã ¿œπ›«–ª˝¿œ ∞Ê?E ªÛ?EÅEº”º∫, ª˝¡° ¡∂¿˝.
				else
				{
					bool bGuidBattleMap = m_pLandMan->m_bGuidBattleMap;
					bool bFreePKMap = m_pLandMan->IsFreePK();
					bool bSCHOOL_FREEPK = GLSchoolFreePK::GetInstance().IsON();
					bool bBRIGHTEVENT = m_pGLGaeaServer->IsBRIGHTEVENT(); // º∫«‚ ¿Ã∫•∆ÆøÎ	

					//
					//juver battle royale
					bool bRedZone = m_pLandMan->IsRedZone();
					
					//if ( GetSchool() == pCHAR->GetSchool() )	bSCHOOL_FREEPK = false;
					if ( GetSchool() == pCHAR->GetSchool() )
					{
						if ( bRedZone )
						{	
							bSCHOOL_FREEPK = true;
						}
						else
						{
							bSCHOOL_FREEPK = false;
						}
					}

					if ( !(bGuidBattleMap||bSCHOOL_FREEPK||bFreePKMap) && !bBRIGHTEVENT )
					{
						nBRIGHT = GLCONST_CHAR::nPK_KILL_BRIGHT_POINT;
						nLIFE = GLCONST_CHAR::nPK_KILL_LIVING_POINT;

						//	Note : º”º∫ºˆƒ° ∫Ø»≠.
						pCHAR->m_nBright += nBRIGHT;

						GLMSG::SNETPC_UPDATE_BRIGHT NetMsg;
						NetMsg.nBright = pCHAR->m_nBright;
						m_pGLGaeaServer->SENDTOCLIENT(pCHAR->m_dwClientID,&NetMsg);

						GLMSG::SNETPC_UPDATE_BRIGHT_BRD NetMsgBrd;
						NetMsgBrd.dwGaeaID = pCHAR->m_dwGaeaID;
						NetMsgBrd.nBright = pCHAR->m_nBright;
						pCHAR->SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );

						//	Note : ª˝»∞¡°?E∫Ø»≠.
						pCHAR->m_nLiving += nLIFE;

						GLMSG::SNETPC_UPDATE_LP NetMsgLp;
						NetMsgLp.nLP = pCHAR->m_nLiving;
						m_pGLGaeaServer->SENDTOCLIENT(pCHAR->m_dwClientID,&NetMsgLp);
					}
				}
			}

			//	Note : ¡◊ø¥¿ª ∞Ê?E∑Œ±◊ ±‚∑œ.
			GLITEMLMT::GetInstance().ReqAction
			(
				dwKILL_ID,					//	¥ÁªÁ¿⁄.
				EMLOGACT_KILL,				//	«‡¿ß.
				ID_CHAR, m_dwCharID,		//	ªÛ?EÅE
				0,							//	exp
				nBRIGHT,					//	bright
				nLIFE,						//	life
				0							//	money
			);
			//add cp
			//pCHAR->ReceivePkWinPoint(1,m_szName);

			//crashfix
			//SNATIVEID mapID = GLGaeaClient::GetInstance().GetActiveMapID();

			//if( mapID.wMainID == 254 || mapID.wMainID == 211 || mapID.wMainID == 23 || mapID.wMainID == 16 )
			//{
				if (!( m_wLevel  < 250 ))
				{
					WORD pCHARpk = pCHAR->GetLevel();
					if (!( pCHARpk  < 250 ) )
					{
						pCHAR->ReceivePkWinPoint(1,m_szName);
						ReceivePkLossPoint(1,pCHAR->m_szName,m_szName,pCHAR->m_dwGaeaID);

					}
				}
			//}

			//if (!( m_wLevel < 175 ))
			//{
			//	WORD pCHARpk = pCHAR->GetLevel();
			//	if (!( pCHARpk < 175 ))
			//	{
			//		ReceivePkLossPoint(1,pCHAR->m_szName);
			//	}
			//}

			//ReceivePkLossPoint(1,pCHAR->m_szName);
			pCHAR->ReceiveCP( m_wLevel,1 );

			
			//
		}
	}

	//	Note : ¿˚?E«‡¿ß¿⁄ ªË¡¶.
	DelPlayHostile();

	//	Note : æ≤∑Ø¡˙∂ß ∫∏?Eπﬂª˝. ( ∞Ê«Ëƒ° + æ∆¿Ã≈€ + ±›æ◊ )
	GenerateReward ();

	// Ω√∞£¡¶ ±Õ»•¡÷ ¬¯?E?π´¡∂≤´ ∞Ê«Ëƒ°∏¶ 0¿∏∑Œ ∏∏µÁ¥Ÿ.
	if ( m_nDECEXP > 0 )
	{
		bool bItemRebirth = ISREVIVE() ? true : false;
		if ( bItemRebirth )
		{
			// º“∏º∫ ±Õ»•¡÷¿Ã?E¿⁄µø ±Õ»•¡÷ ªÁ?E
			SITEM* pITEM = GET_SLOT_ITEMDATA(SLOT_NECK);
			if ( !pITEM->ISINSTANCE() ) m_nDECEXP = 0;
		}
	}


	m_cDamageLog.clear();

	////	Note : ¡◊¿ª∂ß ∑Œ±◊ ±‚∑œ.
	// ∫Œ»∞«œ?Eπˆ∆∞¿Ã ≥™ø¿?Eæ æ∆ ∑Œ±◊∏¶ ∏¯≥≤±‚¥¬ ∞Ê?E?¿÷æ˚ÿ≠ ¡◊¿∏?Eπ´¡∂∞« ≥≤±‰¥Ÿ.
	{
		EMIDTYPE emKILL = ID_MOB;
		if ( m_sAssault.emCrow==CROW_PC )	emKILL = ID_CHAR;

		GLITEMLMT::GetInstance().ReqAction
		(
			m_dwCharID,					//	¥ÁªÁ¿⁄.
			EMLOGACT_DIE,				//	«‡¿ß.
			emKILL, dwKILL_ID,			//	ªÛ?EÅE
			m_nDECEXP,					// exp
			0,							// bright
			0,							// life
			0							// money
		);
	}

	//	Note : ƒ˘Ω∫∆Æ ¡¯?E∏Ò∑œ¡ﬂ ¡◊¿ªΩ√ Ω«∆– ø…º« ∞ÀªÁ»ƒ √≥∏Æ.
	DoQuestCheckLimitDie ();

	//	æ≤∑Ø?Eº≥¡§.
	SetSTATE(EM_ACT_DIE);

	//	Note : æ≤∑Ø?E?≈¨∂Û¿Ãæ∆ÆµÈø°∞‘ æÀ∏≤.
	GLMSG::SNET_ACTION_BRD NetMsgBrd;
	NetMsgBrd.emCrow	= CROW_PC;
	NetMsgBrd.dwID		= m_dwGaeaID;
	NetMsgBrd.emAction	= GLAT_FALLING;

	//	Note : ¡÷∫Ø¿« Char ø°∞‘.
	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );

	//	Note : ¿⁄Ω≈¿« ≈¨∂Û¿Ãæ∆Æø°.
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (NET_MSG_GENERIC*) &NetMsgBrd );

	//	«‡¿ß ∫Ø»≠.
	TurnAction ( GLAT_FALLING );

	// πË∆≤∑Œ?E¿Ã∫•∆Æ¿œ∂ß æ≤∑Ø¡ˆ?E≈ı∏˙‘µÂ∑Œ ?EØ«—¥?
	if ( GLCONST_CHAR::bBATTLEROYAL )
	{
		SetSTATE(EM_REQ_VISIBLEOFF);

		//	Note : (ø°¿Ã¡Ø∆Æº≠?E ∏ﬁºº?Eπﬂª˝.
		//
		GLMSG::SNETPC_ACTSTATE NetMsgFld;
		NetMsgFld.dwActState = m_dwActState;
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgFld );
	}

	// ∆÷ Sad æ◊º«
	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( pMyPet && pMyPet->IsValid () )
	{
		pMyPet->ReSetAllSTATE ();
		pMyPet->SetSTATE ( EM_PETACT_SAD );
		
		// ≈¨∂Û¿Ãæ∆Æø° æÀ∏≤
		GLMSG::SNETPET_SAD PetNetMsg;
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &PetNetMsg );

		GLMSG::SNETPET_SAD_BRD PetNetMsgBrd;
		PetNetMsgBrd.dwGUID   = pMyPet->m_dwGUID;
		PetNetMsgBrd.dwOwner  = m_dwGaeaID;

		SendMsgViewAround ( (NET_MSG_GENERIC*) &PetNetMsgBrd );
	}

	// ¡◊æ˙¿ª ∞Ê?Eº“»Øºˆ∏¶ «ÿ¡¶
	PGLSUMMONFIELD pMySummon = m_pGLGaeaServer->GetSummon( m_dwSummonGUID );
	if ( pMySummon && pMySummon->IsValid() )
	{
		m_pGLGaeaServer->DropOutSummon ( m_dwSummonGUID, true );
	}
		
}

HRESULT GLChar::TourchQItem ( DWORD dwGlobID )
{
	PITEMDROP pItemDrop = m_pLandMan->GetItem ( dwGlobID );
	if ( !pItemDrop )	return S_FALSE;

//	GLGaeaServer & glGaeaServer = m_pGLGaeaServer;
	GLItemMan & glItemMan = GLItemMan::GetInstance();
	
	const SITEM *pItemData = glItemMan.GetItem(pItemDrop->sItemCustom.sNativeID);
	if ( !pItemData )	return S_FALSE;

	if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) )	return S_FALSE;

	if ( pItemData->sBasicOp.emItemType!=ITEM_QITEM )		return S_FALSE;

	const ITEM::SQUESTIONITEM &sQUESTIONITEM = pItemData->sQuestionItem;

	//	Note : ?æ∆¿Ã≈€¿« øµ?E ∆ƒ∆º¿œ ∞Ê?Eøµ«‚¿Ã ∆ƒ∆ºø¯ø°∞‘ πÃƒ£¥Ÿ.
	//
	switch ( sQUESTIONITEM.emType )
	{
	case QUESTION_SPEED_UP:
	case QUESTION_CRAZY:
	case QUESTION_ATTACK_UP:
	case QUESTION_EXP_UP:
	case QUESTION_LUCKY:
	case QUESTION_SPEED_UP_M:
	case QUESTION_MADNESS:
	case QUESTION_ATTACK_UP_M:
		{
			SNATIVEID sNativeID;

			// º≠∫ÒΩ∫ «¡∑ŒπŸ¿Ã¥ı∞° «ÿø‹¿Œ ∞Ê?E
			if ( m_pGLGaeaServer->m_nServiceProvider != SP_KOREA )
			{
                if ( sQUESTIONITEM.emType == QUESTION_SPEED_UP_M ||
				     sQUESTIONITEM.emType == QUESTION_MADNESS    ||
				     sQUESTIONITEM.emType == QUESTION_ATTACK_UP_M )
				{
                    sNativeID = pItemData->sBasicOp.sNativeID;
				}
				else
				{
                    sNativeID = glItemMan.GetRandomQItemID ( pItemDrop->sItemCustom.sNativeID );
				}
			}
			else
			{
				sNativeID = glItemMan.GetRandomQItemID ( pItemDrop->sItemCustom.sNativeID );
			}
				
			GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);

			// ªı∑”∞‘ √ﬂ∞°«— ?æ∆¿Ã≈€¿œ ∞Ê?E¡æ?EÅE∞∞¿∫ πÊπ˝¿∏∑Œ √≥∏Æ
			if ( sNativeID == NATIVEID_NULL() )
			{
				if ( pParty )
				{
					GLPARTY_FIELD::MEMBER_ITER pos = pParty->m_cMEMBER.begin();
					GLPARTY_FIELD::MEMBER_ITER end = pParty->m_cMEMBER.end();
					for ( ; pos!=end; ++pos )
					{
						PGLCHAR pCHAR = m_pGLGaeaServer->GetChar ( (*pos).first );
						if ( !pCHAR )	continue;
						if ( pCHAR->m_sMapID!=m_sMapID )	continue;

						D3DXVECTOR3 vDist = pCHAR->m_vPos - m_vPos;
						float fDist = D3DXVec3Length ( &vDist );
						if ( MAX_VIEWRANGE < fDist )		continue;

						pCHAR->RecieveQItemFact ( pItemDrop->sItemCustom.sNativeID );
					}
				}
				else
				{
					RecieveQItemFact ( pItemDrop->sItemCustom.sNativeID );
				}	
			}
			else
			{
				const SITEM *pItem = glItemMan.GetItem( sNativeID );
				if ( !pItem ) return S_FALSE;

				if ( pParty )
				{
					GLPARTY_FIELD::MEMBER_ITER pos = pParty->m_cMEMBER.begin();
					GLPARTY_FIELD::MEMBER_ITER end = pParty->m_cMEMBER.end();
					for ( ; pos!=end; ++pos )
					{
						PGLCHAR pCHAR = m_pGLGaeaServer->GetChar ( (*pos).first );
						if ( !pCHAR )	continue;
						if ( pCHAR->m_sMapID!=m_sMapID )	continue;

						D3DXVECTOR3 vDist = pCHAR->m_vPos - m_vPos;
						float fDist = D3DXVec3Length ( &vDist );
						if ( MAX_VIEWRANGE < fDist )		continue;

						pCHAR->RecieveQItemFact ( sNativeID );
					}
				}
				else
				{
					RecieveQItemFact ( sNativeID );
				}
			}
		}
		break;

	case QUESTION_EXP_GET:
		{
			SQITEM_FACT sFACT;
			sFACT.emType = sQUESTIONITEM.emType;

			GLMSG::SNETPC_QITEMFACT_BRD NetMsgBrd;
			NetMsgBrd.dwGaeaID = m_dwGaeaID;
			NetMsgBrd.sFACT = sFACT;

			GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
			if ( pParty )
			{
				GLPARTY_FIELD::MEMBER_ITER pos = pParty->m_cMEMBER.begin();
				GLPARTY_FIELD::MEMBER_ITER end = pParty->m_cMEMBER.end();
				for ( ; pos!=end; ++pos )
				{
					PGLCHAR pCHAR = m_pGLGaeaServer->GetChar ( (*pos).first );
					if ( !pCHAR )						continue;
					if ( pCHAR->m_sMapID!=m_sMapID )	continue;

					D3DXVECTOR3 vDist = pCHAR->m_vPos - m_vPos;
					float fDist = D3DXVec3Length ( &vDist );
					if ( MAX_VIEWRANGE < fDist )		continue;

					int nRecExp = int ( pCHAR->m_sExperience.lnMax * sQUESTIONITEM.fExp/100.0f );
					pCHAR->ReceiveExp ( nRecExp, false );
					m_pGLGaeaServer->SENDTOCLIENT(pCHAR->m_dwClientID,&NetMsgBrd);
				}
			}
			else
			{
				int nRecExp = int ( m_sExperience.lnMax * sQUESTIONITEM.fExp/100.0f );
				ReceiveExp ( nRecExp, false );
				m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgBrd);
			}
		}
		break;

	case QUESTION_BOMB:
		{
			SQITEM_FACT sFACT;
			sFACT.emType = sQUESTIONITEM.emType;

			GLMSG::SNETPC_QITEMFACT_BRD NetMsgBrd;
			NetMsgBrd.dwGaeaID = m_dwGaeaID;
			NetMsgBrd.sFACT = sFACT;

			GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
			if ( pParty )
			{
				GLPARTY_FIELD::MEMBER_ITER pos = pParty->m_cMEMBER.begin();
				GLPARTY_FIELD::MEMBER_ITER end = pParty->m_cMEMBER.end();
				for ( ; pos!=end; ++pos )
				{
					PGLCHAR pCHAR = m_pGLGaeaServer->GetChar ( (*pos).first );
					if ( !pCHAR )	continue;
					if ( pCHAR->m_sMapID!=m_sMapID )	continue;

					D3DXVECTOR3 vDist = pCHAR->m_vPos - m_vPos;
					float fDist = D3DXVec3Length ( &vDist );
					if ( MAX_VIEWRANGE < fDist )		continue;

					pCHAR->ReceiveDamage ( CROW_ITEM, 0, sQUESTIONITEM.wParam1, FALSE );
					m_pGLGaeaServer->SENDTOCLIENT(pCHAR->m_dwClientID,&NetMsgBrd);
				}
			}
			else
			{
				ReceiveDamage ( CROW_ITEM, 0, sQUESTIONITEM.wParam1, FALSE );
				m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgBrd);
			}
		}
		break;

	case QUESTION_MOBGEN:
		{
			SQITEM_FACT sFACT;
			sFACT.emType = sQUESTIONITEM.emType;

			GLMSG::SNETPC_QITEMFACT_BRD NetMsgBrd;
			NetMsgBrd.dwGaeaID = m_dwGaeaID;
			NetMsgBrd.sFACT = sFACT;

			GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
			if ( pParty )
			{
				GLPARTY_FIELD::MEMBER_ITER pos = pParty->m_cMEMBER.begin();
				GLPARTY_FIELD::MEMBER_ITER end = pParty->m_cMEMBER.end();
				for ( ; pos!=end; ++pos )
				{
					PGLCHAR pCHAR = m_pGLGaeaServer->GetChar ( (*pos).first );
					if ( !pCHAR )	continue;
					if ( pCHAR->m_sMapID!=m_sMapID )	continue;

					D3DXVECTOR3 vDist = pCHAR->m_vPos - m_vPos;
					float fDist = D3DXVec3Length ( &vDist );
					if ( MAX_VIEWRANGE < fDist )		continue;

					m_pGLGaeaServer->SENDTOCLIENT(pCHAR->m_dwClientID,&NetMsgBrd);
				}
			}
			else
			{
				m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgBrd);
			}

			m_pLandMan->DropCrow ( SNATIVEID(sQUESTIONITEM.wParam1,sQUESTIONITEM.wParam2), pItemDrop->vPos.x, pItemDrop->vPos.z );
		}
		break;

	case QUESTION_HEAL:
		{
			SQITEM_FACT sFACT;
			sFACT.emType = sQUESTIONITEM.emType;

			GLMSG::SNETPC_QITEMFACT_BRD NetMsgBrd;
			NetMsgBrd.dwGaeaID = m_dwGaeaID;
			NetMsgBrd.sFACT = sFACT;

			GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
			if ( pParty )
			{
				GLPARTY_FIELD::MEMBER_ITER pos = pParty->m_cMEMBER.begin();
				GLPARTY_FIELD::MEMBER_ITER end = pParty->m_cMEMBER.end();
				for ( ; pos!=end; ++pos )
				{
					PGLCHAR pCHAR = m_pGLGaeaServer->GetChar ( (*pos).first );
					if ( !pCHAR )	continue;
					if ( pCHAR->m_sMapID!=m_sMapID )	continue;

					D3DXVECTOR3 vDist = pCHAR->m_vPos - m_vPos;
					float fDist = D3DXVec3Length ( &vDist );
					if ( MAX_VIEWRANGE < fDist )		continue;

					m_pGLGaeaServer->SENDTOCLIENT(pCHAR->m_dwClientID,&NetMsgBrd);

					pCHAR->VAR_BODY_POINT ( CROW_PC, m_dwGaeaID, FALSE, USHRT_MAX, USHRT_MAX, USHRT_MAX );
				}
			}
			else
			{
				VAR_BODY_POINT ( CROW_PC, m_dwGaeaID, FALSE, USHRT_MAX, USHRT_MAX, USHRT_MAX );
				m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgBrd);
			}
		}
		break;
	};

	//	Note : æ∆¿Ã≈∆ Landø°º≠ ªË¡¶.
	m_pLandMan->DropOutItem ( pItemDrop->dwGlobID );

	return S_OK;
}

// æ∆¿Ã≈€¿« ∞Ê«Ëƒ° πË¿≤ ±∏«œ?E..æ∆¿Ã≈€ø° ∫Ÿ¿∫ ∞Ê«Ëƒ° πË¿≤¿ª ∏µŒ ¥ı«—¥Ÿ.
float GLChar::GetExpMultipleRateFromSlotItem()
{
	float fExpMultipleRateMax = 1.0f;

	GLItemMan & glItemMan = GLItemMan::GetInstance();

	for( int i=0; i<SLOT_TSIZE; ++i )
	{
		const SITEMCUSTOM &sItemCustoms = m_PutOnItems[i];

		if( sItemCustoms.sNativeID == SNATIVEID( false ) )
			continue;

		SITEM* pItem = glItemMan.GetItem( sItemCustoms.sNativeID );
		if( !pItem )
			continue;

		float fExpMultipleRate = pItem->GetExpMultiple();
		if(  1.0f < fExpMultipleRate )
			fExpMultipleRateMax += fExpMultipleRate - 1.0f;
	}

	return fExpMultipleRateMax < 1.0f ? 1.0f : fExpMultipleRateMax;
}

void GLChar::SENDBOXITEMSHOPINFO ()
{
	GLMSG::SNET_GET_ITEMSHOP_FROMDB_FB NetMsgFB;

	NetMsgFB.emFB = EMREQ_CHARGEDITEM_FROMDB_FB_OK;

	//	æ∆¿Ã≈€ òﬁø°º≠ ±∏¿‘«— π∞«∞ ∏Ò∑œ ≈¨∂Û¿Ãæ∆Æø° ¿¸º€

//	GLGaeaServer & glGaeaServer = m_pGLGaeaServer;
	

	ITEMMAPSHOP::reverse_iterator pos = m_mapItemShop.rbegin();
	ITEMMAPSHOP::reverse_iterator end = m_mapItemShop.rend();

	for ( ; pos!=end; ++pos )
	{
		ITEMSHOP &sItemShop = (*pos).second;
		StringCchCopy ( NetMsgFB.szPurKey, PURKEY_LENGTH+1, sItemShop.strItemNum.GetString() );
		NetMsgFB.nidITEM = SNATIVEID(sItemShop.sID.wMainID,sItemShop.sID.wSubID);
		NetMsgFB.wPrice = sItemShop.wItemPrice;
		NetMsgFB.wStock = sItemShop.wItemStock;
		NetMsgFB.wCtg	= sItemShop.wItemCtg;
		NetMsgFB.wCurrency = sItemShop.wItemCurrency;
		m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgFB );
	}
	NetMsgFB.emFB = EMREQ_CHARGEDITEM_FROMDB_FB_END;
	m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgFB );
	return;
}

void GLChar::SENDBOXITEMINFO ()
{
	GLMSG::SNET_GET_CHARGEDITEM_FROMDB_FB NetMsgFB;

	NetMsgFB.emFB = EMREQ_CHARGEDITEM_FROMDB_FB_OK;

	//	æ∆¿Ã≈€ òﬁø°º≠ ±∏¿‘«— π∞«∞ ∏Ò∑œ ≈¨∂Û¿Ãæ∆Æø° ?E?

//	GLGaeaServer & glGaeaServer = m_pGLGaeaServer;

	MAPSHOP::reverse_iterator pos = m_mapCharged.rbegin();
	MAPSHOP::reverse_iterator end = m_mapCharged.rend();

	for ( ; pos!=end; ++pos )
	{
		SHOPPURCHASE &sPURCHASE = (*pos).second;

		StringCchCopy ( NetMsgFB.szPurKey, PURKEY_LENGTH+1, sPURCHASE.strPurKey.GetString() );
		NetMsgFB.nidITEM = SNATIVEID(sPURCHASE.wItemMain,sPURCHASE.wItemSub);
		m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgFB );
	}

	NetMsgFB.emFB = EMREQ_CHARGEDITEM_FROMDB_FB_END;
	m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgFB );
	return;
}

HRESULT GLChar::MGOddEvenOK( GLMSG::SNETPC_MGAME_ODDEVEN* pNetMsg )
{
	GLMSG::SNETPC_MGAME_ODDEVEN_FB NetMsgFB;

	// º“¿Ø ±›æ◊ √º≈©
	if( pNetMsg->uiBattingMoney > m_lnMoney )
	{
		NetMsgFB.emResult = EMMGAME_ODDEVEN_FB_MONEY_FAIL;
		m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgFB );

		return S_FALSE;
	}

	// √÷?EπË∆√ ∞°¥… ±›æ◊ √º≈©
	if( pNetMsg->uiBattingMoney > MINIGAME_ODDEVEN::uiMaxBattingMoney )
	{
		NetMsgFB.emResult = EMMGAME_ODDEVEN_FB_MAXBATTING;
		m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgFB );

		return S_FALSE;
	}

	MGOddEvenInit();

	m_ui64BattingMoney = pNetMsg->uiBattingMoney;

	// πË∆√ øœ?E∞‘¿” Ω√¿€
	NetMsgFB.emResult = EMMGAME_ODDEVEN_FB_OK;
	m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgFB );

	return S_OK;
}

HRESULT GLChar::MGOddEvenCANCEL( GLMSG::SNETPC_MGAME_ODDEVEN* pNetMsg )
{
	GLMSG::SNETPC_MGAME_ODDEVEN_FB NetMsgFB;
	NetMsgFB.emResult = EMMGAME_ODDEVEN_FB_FAIL;
	m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgFB );

	return S_OK;
}

HRESULT GLChar::MGOddEvenSelect( GLMSG::SNETPC_MGAME_ODDEVEN* pNetMsg )
{
	m_nOddEven = pNetMsg->emCase;

	return S_OK;
}

HRESULT GLChar::MGOddEvenAGAIN( GLMSG::SNETPC_MGAME_ODDEVEN* pNetMsg )
{
	GLMSG::SNETPC_MGAME_ODDEVEN_FB NetMsgFB;

	if( pNetMsg->uiBattingMoney > m_lnMoney ) // º“¿Ø ±›æ◊ √º≈©
	{
		NetMsgFB.emResult = EMMGAME_ODDEVEN_FB_FAIL;
	}
	else
	{
		NetMsgFB.emResult = EMMGAME_ODDEVEN_FB_AGAIN_OK;
		NetMsgFB.wRound = m_wMGOddEvenCurRnd+1;

		m_ui64BattingMoney = m_ui64DividendMoney;
	}

	m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgFB );

	return S_OK;
}

HRESULT GLChar::MGOddEvenShuffle( GLMSG::SNETPC_MGAME_ODDEVEN* pNetMsg )
{
	std::vector<int> vecShuffleBuffer;
	vecShuffleBuffer.reserve( 100 );

	{ // »∞?E?µ˚∏• ∑£¥˝ πËø≠ ª˝º∫
		int nSuccessCnt = (int)(MINIGAME_ODDEVEN::fSuccessRate[m_wMGOddEvenCurRnd]*100.0); // º∫?E»Æ?E
		int i = 0;

		for( ; i<nSuccessCnt; ++i )
			vecShuffleBuffer.push_back( m_nOddEven );

		for( ; i<100; ++i)
			vecShuffleBuffer.push_back( EMMGAME_ODDEVEN_ODD - m_nOddEven );

		std::random_shuffle( vecShuffleBuffer.begin(), vecShuffleBuffer.end() );
	}

	srand ( (UINT)time( NULL ) );

	int nDiceNumber = rand() % 100;						// 0~99±˚?Eº˝¿⁄∏¶ ∑£¥˝«œ∞‘ º±≈√«—¥Ÿ.
	int nHabbyNumber = vecShuffleBuffer[nDiceNumber];	// πËø≠ø°º≠ º±≈√

	GLITEMLMT::GetInstance().ReqMoneyExc(	ID_CHAR, m_dwCharID, 
											ID_CHAR, 0, 
											m_ui64BattingMoney, EMITEM_ROUTE_ODDEVEN );

	GLMSG::SNETPC_MGAME_ODDEVEN_FB NetMsgFB;

	if( nHabbyNumber == m_nOddEven ) // ∏¬¥Ÿ?EπË¥Á±› ¡ˆ±ﬁ
	{
		// πË¥Á±› ∞Ë?E
		m_ui64DividendMoney = (LONGLONG)(m_ui64BattingMoney * MINIGAME_ODDEVEN::fReturnRate[m_wMGOddEvenCurRnd]);

		NetMsgFB.emResult = EMMGAME_ODDEVEN_FB_WIN;
		NetMsgFB.ui64DividendMoney = m_ui64DividendMoney;
		NetMsgFB.ui64ActualMoney = m_ui64DividendMoney - m_ui64BattingMoney; // Ω«ºˆ∑… ±›æ◊ = πË¥Á±› - πË∆√±›
		
		CheckMoneyUpdate( m_lnMoney, NetMsgFB.ui64ActualMoney, TRUE, "Odd Event Shuffle." );
		m_bMoneyUpdate = TRUE;

		m_lnMoney += NetMsgFB.ui64ActualMoney;		
		m_wMGOddEvenCurRnd++;

		GLITEMLMT::GetInstance().ReqMoneyExc(	ID_CHAR, m_dwCharID, 
												ID_CHAR, m_wMGOddEvenCurRnd, 
												NetMsgFB.ui64ActualMoney, EMITEM_ROUTE_ODDEVEN );
	}
	else
	{
		NetMsgFB.emResult = EMMGAME_ODDEVEN_FB_LOSE;
		NetMsgFB.ui64DividendMoney = m_ui64BattingMoney;

		CheckMoneyUpdate( m_lnMoney, NetMsgFB.ui64ActualMoney, FALSE, "Odd Event Shuffle." );
		m_bMoneyUpdate = TRUE;

		m_lnMoney -= m_ui64BattingMoney;
		

		GLITEMLMT::GetInstance().ReqMoneyExc(	ID_CHAR, m_dwCharID, 
												ID_MOB, m_wMGOddEvenCurRnd, 
												m_ui64BattingMoney, EMITEM_ROUTE_ODDEVEN );
	}

	GLITEMLMT::GetInstance().ReqMoneyExc(	ID_CHAR, m_dwCharID, 
											ID_CHAR, 0, 
											m_lnMoney, EMITEM_ROUTE_ODDEVEN );

	if( nHabbyNumber )	NetMsgFB.emCase = EMMGAME_ODDEVEN_ODD;
	else				NetMsgFB.emCase = EMMGAME_ODDEVEN_EVEN;

	m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgFB );

	return S_OK;
}

HRESULT GLChar::MGOddEvenFinish( GLMSG::SNETPC_MGAME_ODDEVEN* pNetMsg )
{
	GLMSG::SNETPC_MGAME_ODDEVEN_FB NetMsgFB;

	// π›∫π »∏ºˆ∏¶ √º≈©
	if( m_wMGOddEvenCurRnd >= MINIGAME_ODDEVEN::MAX_ROUND )
	{
		NetMsgFB.emResult = EMMGAME_ODDEVEN_FB_MAXROUND;
	}
	else
	{
		NetMsgFB.emResult = EMMGAME_ODDEVEN_FB_FINISH_OK;
		NetMsgFB.wRound = m_wMGOddEvenCurRnd;
		NetMsgFB.ui64DividendMoney = m_ui64DividendMoney;
	}

	m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgFB );

	return S_OK;
}

HRESULT GLChar::UpdateVehicle( float fElapsedTime )
{
	if ( !m_bVehicle || !m_sVehicle.IsActiveValue() ) return S_OK;
	m_fVehicleTimer += fElapsedTime;
	// ∆÷¿« ∆˜∏∏µµ ∞ªΩ≈
	if ( m_fVehicleTimer > 3600.0f/GLPeriod::REALTIME_TO_VBR )
	{
		m_fVehicleTimer = 0;
		m_sVehicle.m_nFull -= GLCONST_VEHICLE::nFullDecrVehicle[m_sVehicle.m_emTYPE];
		if ( m_sVehicle.m_nFull < 0 ) m_sVehicle.m_nFull = 0;

		// ≈¨∂Û¿Ãæ∆Æ ∆˜∏∏µµ ∞ªΩ≈
		GLMSG::SNET_VEHICLE_UPDATE_CLIENT_BATTERY NetMsg;
		NetMsg.nFull = m_sVehicle.m_nFull;

		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );

		if ( m_sVehicle.IsNotEnoughFull() )	ActiveVehicle( false, false );
	}
	
	return S_OK;
}

BOOL GLChar::CheckMoneyUpdate( const LONGLONG lnCurrentMoney, const LONGLONG lnUpdateMoney, const bool bPlus, const char* msg )
{
	if( lnUpdateMoney < 100000000 && lnUpdateMoney >= 0 )
	{
		return FALSE;
	}

	char szTempChar[256] = {0,};
	string str;
	sprintf( szTempChar, "[%s][%s] %s", m_szUID, m_szName, msg );
	str = szTempChar;
	
	if( lnUpdateMoney < 0 )
	{
		str += " Not Correct Update Money Value!!";
	}

	if( bPlus )	sprintf( szTempChar, " Current Money %I64d Update Money %I64d Plus!!", lnCurrentMoney, lnUpdateMoney );
	else		sprintf( szTempChar, " Current Money %I64d Update Money %I64d Minus!!", lnCurrentMoney, lnUpdateMoney );
	str += szTempChar;

	BILLIONUPDATE_WRITE( str.c_str() );

	return TRUE;
}

void GLChar::ClubBattleSetPoint( DWORD dwClub_P, DWORD dwClub_S, bool bAlliancBattle )
{

	GLClubMan& cClubMan = GLGaeaServer::GetInstance().GetClubMan();
	GLCLUB* pClub_P = cClubMan.GetClub( dwClub_P );
	GLCLUB* pClub_S = cClubMan.GetClub( dwClub_S );

	if ( !pClub_P || !pClub_S ) return;

	if ( bAlliancBattle ) 
	{
		GLCLUB* pClub_M = cClubMan.GetClub( pClub_P->m_dwAlliance );
		if ( !pClub_M ) return;

		CLUB_ALLIANCE_ITER pos = pClub_M->m_setAlliance.begin();
		CLUB_ALLIANCE_ITER end = pClub_M->m_setAlliance.end();
		for ( ; pos!=end; ++pos )
		{
			const GLCLUBALLIANCE &sALLIANCE = *pos;

			GLCLUB *pCLUB = cClubMan.GetClub ( sALLIANCE.m_dwID );
			if ( !pCLUB ) continue;
			
			GLCLUBBATTLE* pClubBattle = pCLUB->GetClubBattle( pClub_S->m_dwAlliance );
			if ( !pClubBattle ) continue;

			pClubBattle->m_wDeathPointTemp++;
			pClubBattle->m_bKillUpdate = true;
		}

		pClub_M = cClubMan.GetClub( pClub_S->m_dwAlliance );
		if ( !pClub_M ) return;

		pos = pClub_M->m_setAlliance.begin();
		end = pClub_M->m_setAlliance.end();
		for ( ; pos!=end; ++pos )
		{
			const GLCLUBALLIANCE &sALLIANCE = *pos;

			GLCLUB *pCLUB = cClubMan.GetClub ( sALLIANCE.m_dwID );
			if ( !pCLUB ) continue;
			
			GLCLUBBATTLE* pClubBattle = pCLUB->GetClubBattle( pClub_P->m_dwAlliance );
			if ( !pClubBattle ) continue;

			pClubBattle->m_wKillPointTemp++;
			pClubBattle->m_bKillUpdate = true;
		}
	}
	else
	{
		GLCLUBBATTLE* pClubBattle = pClub_P->GetClubBattle( dwClub_S );
		if ( !pClubBattle ) return;

		pClubBattle->m_wDeathPointTemp++;
		pClubBattle->m_bKillUpdate = true;
		
		pClubBattle = pClub_S->GetClubBattle( dwClub_P );
		if ( !pClubBattle ) return;
				
		pClubBattle->m_wKillPointTemp++;
		pClubBattle->m_bKillUpdate = true;
	}
	
	return;
}

ITEM_COOLTIME*	GLChar::GetCoolTime( DWORD dwCoolID, EMCOOL_TYPE emCoolType )
{
	if ( emCoolType == EMCOOL_ITEMID )
	{
		COOLTIME_MAP_ITER pos = m_mapCoolTimeID.find(dwCoolID);
		if ( pos==m_mapCoolTimeID.end() )		return NULL;
		
		return &(*pos).second;
	}
	else if ( emCoolType == EMCOOL_ITEMTYPE )
	{
		COOLTIME_MAP_ITER pos = m_mapCoolTimeType.find(dwCoolID);
		if ( pos==m_mapCoolTimeType.end() )		return NULL;
		
		return &(*pos).second;
	}
	else	
		return NULL;
}

bool GLChar::IsCoolTime( SNATIVEID sNativeID )
{
	__time64_t tCurTime = CTime::GetCurrentTime().GetTime();
	__time64_t tCoolTime = GetMaxCoolTime( sNativeID );

	if ( tCurTime < tCoolTime ) return true;

	return false;
}

bool GLChar::CheckCoolTime( SNATIVEID sNativeID )
{
	if ( IsCoolTime ( sNativeID ) )
	{
		GLMSG::SNET_ITEM_COOLTIME_ERROR NetMsg;
		NetMsg.sNativeID = sNativeID;

		GLGaeaServer::GetInstance().SENDTOCLIENT(m_dwClientID,&NetMsg);
		return true;

	}
	return false;
}

__time64_t	GLChar::GetMaxCoolTime ( SNATIVEID sNativeID )
{
	//	æ∆¿Ã≈€ ¡§∫∏ ∞°¡Æø».
	SITEM* pItem = GLItemMan::GetInstance().GetItem ( sNativeID );
	if ( !pItem )			return 0;

	ITEM_COOLTIME* pCoolTimeType = GetCoolTime( (DWORD) pItem->sBasicOp.emItemType, EMCOOL_ITEMTYPE );
	ITEM_COOLTIME* pCoolTimeID = GetCoolTime( pItem->sBasicOp.sNativeID.dwID, EMCOOL_ITEMID );

	__time64_t tCoolType = 0;
	__time64_t tCoolID = 0;

	if ( pCoolTimeType )	tCoolType = pCoolTimeType->tCoolTime;
	if ( pCoolTimeID )		tCoolID = pCoolTimeID->tCoolTime;

	return (tCoolType > tCoolID) ? tCoolType : tCoolID;
}


bool GLChar::SetCoolTime( SNATIVEID sNativeID , EMCOOL_TYPE emCoolType )
{
	//	æ∆¿Ã≈€ ¡§∫∏ ∞°¡Æø».
	SITEM* pItem = GLItemMan::GetInstance().GetItem ( sNativeID );
	if ( !pItem )			return false;

	if ( !pItem->sBasicOp.IsCoolTime() ) return false;

	// ƒ≈∏¿” º¬∆√
	__time64_t  tCurTime = CTime::GetCurrentTime().GetTime();
	__time64_t  tCoolTime = tCurTime + pItem->sBasicOp.dwCoolTime;

	ITEM_COOLTIME* pCoolTime = GetCoolTime( sNativeID.dwID, emCoolType );
	if ( pCoolTime && tCoolTime < pCoolTime->tCoolTime ) return false;

	ITEM_COOLTIME sCoolTime;
	sCoolTime.dwID = pItem->sBasicOp.sNativeID.dwID;
	sCoolTime.tUseTime = tCurTime;
	sCoolTime.tCoolTime = tCoolTime;	

	if ( emCoolType == EMCOOL_ITEMID )
	{
		sCoolTime.dwCoolID = pItem->sBasicOp.sNativeID.dwID;
		m_mapCoolTimeID[sCoolTime.dwCoolID] = sCoolTime;
	}
	else if( emCoolType == EMCOOL_ITEMTYPE )
	{
		sCoolTime.dwCoolID = (DWORD)pItem->sBasicOp.emItemType;
		m_mapCoolTimeType[sCoolTime.dwCoolID] = sCoolTime;
	}

	GLMSG::SNETPC_ITEM_COOLTIME_UPDATE NetMsg;			
	NetMsg.dwID = sCoolTime.dwID;
	NetMsg.dwCoolID = sCoolTime.dwCoolID;
	NetMsg.tCoolTime = sCoolTime.tCoolTime;
	NetMsg.tUseTime = sCoolTime.tUseTime;
	NetMsg.emCoolType = emCoolType;

	GLGaeaServer::GetInstance().SENDTOCLIENT(m_dwClientID,&NetMsg);

	return true;
}

bool GLChar::UpdateNpcCommission( LONGLONG lnCommission )
{
	if ( lnCommission < 0 ) return false;
	
	CheckMoneyUpdate( m_lnStorageMoney, lnCommission, TRUE, "Add Npc Commission");
	m_lnStorageMoney += lnCommission;
	m_bStorageMoneyUpdate = TRUE;
			
	GLITEMLMT::GetInstance().ReqMoneyExc ( ID_CHAR, m_dwCharID, ID_USER, m_dwUserID, lnCommission, EMITEM_ROUTE_NPCCOME );

	GLMSG::SNETPC_REQ_STORAGE_UPDATE_MONEY NetMsgStorage;
	NetMsgStorage.lnMoney = m_lnStorageMoney;
	GLGaeaServer::GetInstance().SENDTOCLIENT( m_dwClientID,&NetMsgStorage);

	return true;
}
