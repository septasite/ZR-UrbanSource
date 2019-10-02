#include "stdafx.h"
#include "Psapi.h"
#pragma comment( lib, "Psapi.lib" )
#include "./GLAgentServer.h"
#include "./GLItemLMT.h"

#include "../DbActionLogic.h"

#include "../RanClientUILib/Interface/GameTextControl.h"
#include "./GLTaxiStation.h"
#include "./GLClubDeathMatch.h"
#include "./GLSchoolWars.h"
#include "./GLSchoolWar.h"
#include "./GLRoyalRumble.h"
#include "GLTowerWars/GLTowerWars.h"

//crashfix
//#include "../../RanClientUILib/Interface/InnerInterface.h"
//#include "../../RanClientUILib/Interface/UITextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//	Note : ÇÊ?E¼­?Eº¯°æ½Ã Å¬¶óÀÌ¾ðÆ® Á¤º¸ º¯?E»çÇ× ¹Ý¿µ.
//		ºÎÈ°½Ã, gate¸¦ ?E?¸Ê ÀÌµ¿½Ã È£ÃâµÊ.
BOOL GLAgentServer::ReActionMoveFieldSvr ( DWORD dwClientID, DWORD dwGaeaID )
{
	//	Note : Å¬¶óÀÌ¾ðÆ®ÀÇ Áö¼Ó ½ºÅ³ ¸®¼Â.
	//
	GLMSG::SNETPC_SKILLHOLD_RS_BRD NetMsgSkillBrd;
	
	NetMsgSkillBrd.dwID = dwGaeaID;
	NetMsgSkillBrd.emCrow = CROW_PC;
	for ( int i=0; i<SKILLFACT_SIZE; ++i )
	{
		NetMsgSkillBrd.bRESET[i] = true;
	}
	SENDTOCLIENT ( dwClientID, &NetMsgSkillBrd );

	GLMSG::SNETPC_CURESTATEBLOW_BRD NetMsgBlowBrd;
	NetMsgBlowBrd.dwID = dwGaeaID;
	NetMsgBlowBrd.dwID = CROW_PC;
	NetMsgBlowBrd.dwCUREFLAG = DIS_ALL;
	SENDTOCLIENT ( dwClientID, &NetMsgBlowBrd );

	GLMSG::SNETPC_QITEMFACT_END_BRD NetMsgQFactEndBrd;
	SENDTOCLIENT ( dwClientID, &NetMsgQFactEndBrd );

	GLMSG::SNETPC_QITEMFACT_TIMEUPDATE_BRD NetMsgQFactTimeUpdateBrd; //add qbox
	NetMsgQFactTimeUpdateBrd.fQBoxTime = 0;
	SENDTOCLIENT ( dwClientID, &NetMsgQFactTimeUpdateBrd );

	return TRUE;
}

// *****************************************************
// Desc: ÇÊµå¼­?EÁ¤º¸¸¦ Ã¼Å©ÈÄ Á¢¼Ó Á¤º¸ ?E?Agent->Field)
// *****************************************************
BOOL GLAgentServer::MsgReqFieldSvrCharChkFb ( NET_MSG_GENERIC* nmg, DWORD _dwClientID, DWORD _dwGaeaID )
{
	GLMSG::SNETPC_FIELDSVR_CHARCHK_FB *pNetMsg = (GLMSG::SNETPC_FIELDSVR_CHARCHK_FB *) nmg;
	PGLCHARAG pChar = GetChar ( pNetMsg->dwGaeaID );
	if ( !pChar )									return FALSE;

	//	Note : Ã¼Å©µÈ È½?ELOG.
	//
	++pChar->m_dwFIELDCK_NUM;
	pChar->m_bFIELD_CK[pNetMsg->nChannel][pNetMsg->dwFIELDID] = true;
	if ( pNetMsg->bExist )		++pChar->m_dwFIELDCK_BEING;

	//	Note : ÇÊ?EÃ¼Å© ¿Ï?E¿©ºÎ ÆÇ´Ü. ¸¸Á· ¾ÈÇÏ?E?EE
	//
	if ( !pChar->IsFieldCheckComplete(&m_bFIELDSVR[0][0]) )		return TRUE;

	if ( pChar->m_dwFIELDCK_BEING > 0 )
	{
        //	ÇÊµå¼­¹ö·Î Á¢¼ÓÀÌ ½ÇÆÐÇÔ
		/*
		DEBUGMSG_WRITE( "Found same character in field server. %d removed exist character. ( name %s )",
			pChar->m_dwFIELDCK_BEING, pChar->m_szName );
		*/
	}

	//	Note : Ä³¸¯ÅÍ »ý¼ºÀ§Ä¡¸¦ ÁöÁ¤.
	//
	SNATIVEID sGenMapID = pChar->m_sStartMapID;
	DWORD dwGenGateID = pChar->m_dwStartGate;
	D3DXVECTOR3 vGenPos = pChar->m_vStartPos;

	//	ÀúÀåµÈ À§Ä¡°¡ ÀÖÀ» °æ?E¼³Á¤ÇÔ.
	if ( pChar->m_sSaveMapID != NATIVEID_NULL() )
	{
		if ( GLAgentServer::GetInstance().GetFieldServer ( sGenMapID ) != FIELDSERVER_MAX )
		{
			sGenMapID = pChar->m_sSaveMapID;
			dwGenGateID = UINT_MAX;
			vGenPos = pChar->m_vSavePos;

			// MapList ¿¡ Restart flag °¡ ¼³Á¤µÇ?EÀÖÀ¸?E
			// °­Á¦ÀûÀ¸·Î ½ÃÀÛÁöÁ¡À¸·Î ÀÌµ¿ÇÏ°Ô µÈ´Ù.
			SMAPNODE* pGenMap = m_sMapList.FindMapNode ( sGenMapID );
			if ( !pGenMap )
			{
				DEBUGMSG_WRITE ( "Can't find MapNode in MapsList." );
			}
			else if ( pGenMap->bRestart )
			{
				sGenMapID   = pChar->m_sStartMapID;
				dwGenGateID = pChar->m_dwStartGate;
				vGenPos		= D3DXVECTOR3(0,0,0);
			}
		}

	}

	// Á÷?E?Á¾·áÇÑ ¸ÊÀÌ ¼±µµ?E¸ÊÀÌ?E¼±µµÅ¬·´ÀÌ ¾Æ´Ò°æ?E½ÃÀÛ¸ÊÀ¸·Î ÁöÁ¤
	GLAGLandMan* pLAND = GetByMapID ( sGenMapID );
	if ( pLAND )
	{
		if ( pLAND->m_bGuidBattleMap )
		{
			GLGuidance* pGUID = GLGuidanceAgentMan::GetInstance().Find ( pLAND->m_dwClubMapID );
			if ( pGUID && pGUID->m_dwGuidanceClub != pChar->m_dwGuild )
			{
				sGenMapID = pChar->m_sStartMapID;
				dwGenGateID = pChar->m_dwStartGate;
			}
		}

		if ( pLAND->m_bClubDeathMatchMap )
		{
			GLClubDeathMatch* pCDM = GLClubDeathMatchAgentMan::GetInstance().Find ( pLAND->m_dwClubMapID );

			if ( pCDM )
			{
				sGenMapID = pCDM->m_dwClubHallMap;
				dwGenGateID = pCDM->m_dwClubHallGate;
			}
		}

		if ( pLAND->m_bSchoolWarsMap )
		{
			GLSchoolWars* pSW = GLSchoolWarsAgentMan::GetInstance().Find ( pLAND->m_dwClubMapID );

			if ( pSW )
			{
				sGenMapID = pSW->m_dwClubHallMap;
				dwGenGateID = pSW->m_dwClubHallGate;
			}
		}

		//royal rumble random respawn fix
		if ( pLAND->m_bRoyalRumbleMap )
		{
			BOOL bFAILED = TRUE;
			GLRoyalRumble* pRR = GLRoyalRumbleAgentMan::GetInstance().Find ( pLAND->m_dwRoyalRumbleMapID );

			if ( pRR )
			{
				srand(time(NULL));
				PDXLANDGATE pRRGATE = pLAND->GetLandGateMan()->FindLandGate( (DWORD)RANDOM_GATE );

				if ( pRRGATE )
				{
					sGenMapID = pRR->m_dwClubMap;
					dwGenGateID = pRRGATE->GetGateID();
					vGenPos = pRRGATE->GetGenPos( DxLandGate::GEN_RENDUM );
					bFAILED = FALSE;
				}
			}

			if ( bFAILED )
			{
				sGenMapID = GLCONST_CHAR::nidSTARTMAP[pChar->m_wSchool];
				dwGenGateID = GLCONST_CHAR::dwSTARTGATE[pChar->m_wSchool];
				vGenPos   = D3DXVECTOR3(0.0f,0.0f,0.0f);
			}
		}

		if ( pLAND->m_bTowerWarsMap )
		{
			BOOL bFAILED = TRUE;
			GLTowerWars* pSW = GLTowerWarsAgentMan::GetInstance().Find ( pLAND->m_dwTowerWarsMapID );
			if ( pSW && pSW->IsEnterMap() )
			{
				PDXLANDGATE pSWGATE = pLAND->GetLandGateMan()->FindLandGate(pSW->GetReviveGate( pChar->m_wSchool ));
			
				if ( pSWGATE )
				{
					sGenMapID = pSW->m_dwClubMap;
					dwGenGateID = pSWGATE->GetGateID();
					vGenPos = pSWGATE->GetGenPos( DxLandGate::GEN_RENDUM );
					bFAILED = FALSE;
				}
			}

			if ( bFAILED )
			{
				sGenMapID = GLCONST_CHAR::nidSTARTMAP[pChar->m_wSchool];
				dwGenGateID = GLCONST_CHAR::dwSTARTGATE[pChar->m_wSchool];
				vGenPos   = D3DXVECTOR3(0.0f,0.0f,0.0f);
			}
		}
	}

	//	Note : ÇÊµå¼­?EÁ¤º¸¸¦ °¡Á®¿Í¼­ ÇÊµå¼­¹ö·Î Á¢¼Ó
	//
	bool bCANNOTFINDMAP(false);
	DWORD dwFieldServer = GLAgentServer::GetInstance().GetFieldServer ( sGenMapID );
	if ( dwFieldServer == FIELDSERVER_MAX )
	{
		bCANNOTFINDMAP = true;

        //	Ä³¸¯ÅÍ°¡ »ý¼ºµÉ ÇÊµå¼­¹ö¸¦ Ã£?E¸øÇÔ. ±×·¯³ª ÁøÀÔÇÒ ?EÀÖµµ·Ï ÃÊ±âÈ­ÇÔ ( Ä³¸¯ÅÍº° ÇÐ±³ÀÇ 0?E°ÔÀÌÆ® )
		DEBUGMSG_WRITE ( "Can't find field server associate with character (MID[%d/%d], CID[%d] name %s)",
			sGenMapID.wMainID, sGenMapID.wSubID, pChar->m_dwClientID, pChar->m_szName );

		// DBAction ÀÛ?E³¡³ª?E¹Ù·Î Á¦°ÅÇÏ?EÅ×½ºÆ® ÇØ?E
		// return FALSE;

		sGenMapID = GLCONST_CHAR::nidSTARTMAP[pChar->m_wSchool];
		dwGenGateID = GLCONST_CHAR::dwSTARTGATE[pChar->m_wSchool];

		GLAGLandMan* pLandMan = GetByMapID ( sGenMapID );
		if ( !pLandMan )
		{
			DEBUGMSG_WRITE ( "Can't find StartMap ID." );
			return FALSE;
		}

		DxLandGateMan* pGateMan = pLandMan->GetLandGateMan ();
		if ( !pGateMan )
		{
			DEBUGMSG_WRITE ( "Can't Find LandGateManager." );
			return FALSE;

		}
		PDXLANDGATE pGate = pGateMan->FindLandGate ( dwGenGateID );
		if ( !pGate )
		{
			DEBUGMSG_WRITE ( "Can't Find LandGate." );
			vGenPos = D3DXVECTOR3(0,0,0);
		}
		else
		{
			vGenPos = pGate->GetGenPos ( DxLandGate::GEN_RENDUM );
		}

		dwFieldServer = GLAgentServer::GetInstance().GetFieldServer ( sGenMapID );
		if ( dwFieldServer == FIELDSERVER_MAX )
		{
			DEBUGMSG_WRITE ( "Can't Find FieldServer associate with character'school." );
			return FALSE;
		}

		pChar->m_sStartMapID = sGenMapID;
		pChar->m_dwStartGate = dwGenGateID;
		pChar->m_vStartPos   = vGenPos;
		pChar->m_sSaveMapID = sGenMapID;
		pChar->m_vSavePos   = vGenPos;

		// ÀÌºÎºÐ¿¡¼­ º¯°æµÈ ½ºÅ¸Æ®ÁöÁ¡(MapID, GateID, À§Ä¡) À» DB¿¡ ÀúÀåÇÔ
		CSaveChaPos* pDBAction = new CSaveChaPos ( pChar->m_dwClientID, 
												   pChar->m_dwCharID,
												   dwFieldServer,
												   pChar->m_sStartMapID.dwID,
												   pChar->m_dwStartGate,
												   pChar->m_vStartPos.x,
												   pChar->m_vStartPos.y,
												   pChar->m_vStartPos.z,
												   pChar->m_sSaveMapID.dwID,
												   pChar->m_vSavePos.x,
												   pChar->m_vSavePos.y,
												   pChar->m_vSavePos.z,
												   pChar->m_sSaveMapID.dwID,
												   pChar->m_vSavePos.x,
												   pChar->m_vSavePos.y,
												   pChar->m_vSavePos.z );

		GLDBMan *pDbMan = GLAgentServer::GetInstance().GetDBMan();
		if ( pDbMan )	pDbMan->AddJob ( pDBAction );        
	}

	// ¸¸?E¸ÊÀ» ?EÃ£¾Ò´Ù?E¸ÊÀ» ÃÊ±âÈ­ ÇÏ?E´Ù¸¥ °÷¿¡¼­ Ä³¸¯ÅÍ Á¶ÀÎÁ¤º¸¸¦ ?EÛÇÑ´?
	if ( bCANNOTFINDMAP ) return true;

	if ( m_pMsgServer->ConnectFieldSvr ( pChar->m_dwClientID, dwFieldServer, pChar->m_dwGaeaID, pChar->m_nChannel ) != NET_OK )
	{
        //	Ä³¸¯ÅÍ°¡ »ý¼ºµÉ ÇÊµå¼­¹ö·Î Á¢¼ÓÀÌ ½ÇÆÐÇÔ
		DEBUGMSG_WRITE ( "Can't connect field. FIELDID : %d, CID[%d] name %s",
			dwFieldServer, pChar->m_dwClientID, pChar->m_szName );
		return FALSE;
	}

	//	Ä³¸¯ÅÍ Á¶ÀÎ Á¤º¸ ?E?
	NET_GAME_JOIN_FIELDSVR NetJoinField;
	NetJoinField.emType				= EMJOINTYPE_FIRST;
	NetJoinField.dwSlotAgentClient	= pChar->m_dwClientID;
	StringCchCopy ( NetJoinField.szUID, DAUM_MAX_UID_LENGTH+1, pChar->m_szUserName );
	NetJoinField.nUserNum			= pChar->m_dwUserID;
	NetJoinField.dwUserLvl			= pChar->m_dwUserLvl;
	NetJoinField.nChaNum			= pChar->m_dwCharID;
	NetJoinField.dwGaeaID			= pChar->m_dwGaeaID;
    NetJoinField.tPREMIUM			= pChar->m_tPREMIUM;
	NetJoinField.tCHATBLOCK			= pChar->m_tCHATBLOCK;

	NetJoinField.sStartMap			= sGenMapID;
	NetJoinField.dwStartGate		= dwGenGateID;
	NetJoinField.vStartPos			= vGenPos;

	NetJoinField.dwActState			= pChar->m_dwActState;
	NetJoinField.bUseArmSub			= pChar->m_bUseArmSub;

	NetJoinField.dwThaiCCafeClass	= pChar->m_dwThaiCCafeClass;
	NetJoinField.nMyCCafeClass		= pChar->m_nMyCCafeClass;				// ¸»·¹ÀÌ½Ã¾Æ PC?EÀÌº¥Æ®

	NetJoinField.sChinaTime			= pChar->m_sChinaTime;
	NetJoinField.sEventTime			= pChar->m_sEventTime;
	NetJoinField.sVietnamGainSystem = pChar->m_sVietnamSystem;

	//** Add EventTime

	SENDTOFIELD ( pChar->m_dwClientID, &NetJoinField );

	//	Note : ÄÉ¸¯ÅÍÀÇ Çö?EÁ¢¼Ó ÇÊµå¼­?E¹× Çö?E¸Ê ID ÁöÁ¤.
	//
	pChar->SetCurrentField ( dwFieldServer, sGenMapID );


	return TRUE;
}

BOOL GLAgentServer::MsgReqGenItemAgt ( NET_MSG_GENERIC* nmg, DWORD dwClientID )
{
	GLMSG::SNET_REQ_GENITEM_AGT *pNetMsg = (GLMSG::SNET_REQ_GENITEM_AGT *) nmg;

	int nCHANNEL = pNetMsg->nCHANNEL;

	const SNATIVEID &sNID = pNetMsg->sNID;
	SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sNID );
	if ( !pITEM )		return FALSE;

	SMAPNODE* pMAPNODE = m_sMapList.FindMapNode ( pNetMsg->sMAPID );
	if ( !pMAPNODE )	return FALSE;

	int nSvrNum = (int) pMAPNODE->dwFieldSID;

	if ( GLITEMLMT::GetInstance().DoCheckItemGen ( sNID ) )
	{
		LONGLONG lnGenCount = GLITEMLMT::GetInstance().RegItemGen ( sNID, pNetMsg->emGENTYPE );

		GLMSG::SNET_REQ_GENITEM_FLD_FB NetMsgFb;
		NetMsgFb.sNID = pNetMsg->sNID;
		NetMsgFb.sMAPID = pNetMsg->sMAPID;
		NetMsgFb.emGENTYPE = pNetMsg->emGENTYPE;
		NetMsgFb.lnGENCOUNT = lnGenCount;
		NetMsgFb.emHoldGroup = pNetMsg->emHoldGroup;
		NetMsgFb.dwHoldGID = pNetMsg->dwHoldGID;
		NetMsgFb.vPos = pNetMsg->vPos;

		SENDTOFIELDSVR ( nCHANNEL, nSvrNum, &NetMsgFb );
	}

	return TRUE;
}

BOOL GLAgentServer::SendToGMMsg( PGLCHARAG pChar, NET_CHAT_FB NetChatFB )
{
	UINT i;
	for( i = 0; i < pChar->m_vecGetWhisperList.size(); i++ )
	{
		PGLCHARAG pSendGMChar = GetChar( pChar->m_vecGetWhisperList[i].dwGaeaID );
		if( pSendGMChar == NULL || 
			pSendGMChar->m_GmWhisperList.dwClientID != pChar->m_dwClientID ||
			pSendGMChar->m_GmWhisperList.dwGaeaID != pChar->m_dwGaeaID ||
			pSendGMChar->m_bViewWhisperMSG == FALSE)
		{
			pChar->m_vecGetWhisperList.erase( pChar->m_vecGetWhisperList.begin() + i );
			i--;
			continue;
		}
		SENDTOCLIENT( pChar->m_vecGetWhisperList[i].dwClientID, &NetChatFB );
	}

	return TRUE;
}


BOOL GLAgentServer::ChatMsgProc ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	NET_CHAT* pNetMsg = (NET_CHAT*) nmg;

	switch ( pNetMsg->emType )
	{
	case CHAT_TYPE_GLOBAL: // ?E®¿E±Û·Î?E¸Þ½Ã?E
		{
			PGLCHARAG pChar = GetChar ( dwGaeaID );
			if ( !pChar )							return FALSE;
			if ( pChar->m_dwUserLvl < USER_GM3 )	return FALSE;

			NET_CHAT_CTRL_FB NetChatFB;
			NetChatFB.emType = CHAT_TYPE_GLOBAL;
			NetChatFB.sITEMLINK = pNetMsg->sITEMLINK;
			StringCchCopy ( NetChatFB.szChatMsg, GLOBAL_CHAT_MSG_SIZE+1, pNetMsg->szChatMsg );

			//add staffchat
			if ( pChar->m_dwUserLvl == USER_GM1 )
			{
				NetChatFB.bStaff =true ;
			}

			//add staffchat
			if ( pChar->m_dwUserLvl == USER_GM0 )
			{
				NetChatFB.bStaff2 =true ;
			}


			AGCHARNODE *pCharNode = m_PCList.m_pHead;
			for ( ; pCharNode; pCharNode=pCharNode->pNext )
			{
				SENDTOCLIENT ( pCharNode->Data->m_dwClientID, &NetChatFB );
			}
		}
		break;

	case CHAT_TYPE_NORMAL: // ÀÏ¹Ý¸Þ½Ã?E
		{
			PGLCHARAG pChar = GetChar ( dwGaeaID );
			if ( !pChar )					return FALSE;
			if ( pChar->IsCHATBLOCK() )
			{
				GLMSG::SNETPC_CHAT_BLOCK NetChatBlock;
				StringCchCopy( NetChatBlock.szName, USR_ID_LENGTH+1, pChar->m_szUserName );
				NetChatBlock.tChatBlock = pChar->m_tCHATBLOCK;

				SENDTOCLIENT ( pChar->m_dwClientID, &NetChatBlock );

				return FALSE;
			}

			//	ÇÊ?E¼­¹ö·Î ?E?
			SENDTOFIELD ( pChar->m_dwClientID, nmg );

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
			if( pChar->m_bTracingUser )
			{
				CDebugSet::ToTracingFile( pChar->m_szUserName, "**Normal Send**, [%s][%s], %s", pChar->m_szUserName, pChar->m_szName, pNetMsg->szChatMsg  );
			}
#endif
		}
		break;

	case CHAT_TYPE_PARTY: // ÆÄÆ¼¸Þ½Ã?E
		{
			PGLCHARAG pChar = GetChar ( dwGaeaID );
			if ( !pChar )							return FALSE;
			if ( pChar->m_dwPartyID==PARTY_NULL )	return FALSE;
			if ( pChar->IsCHATBLOCK() )
			{
				GLMSG::SNETPC_CHAT_BLOCK NetChatBlock;
				StringCchCopy ( NetChatBlock.szName, USR_ID_LENGTH+1, pChar->m_szUserName );
				NetChatBlock.tChatBlock = pChar->m_tCHATBLOCK;

				SENDTOCLIENT ( pChar->m_dwClientID, &NetChatBlock );

				return FALSE;
			}

			NET_CHAT_FB NetChatFB;
			NetChatFB.sITEMLINK = pNetMsg->sITEMLINK;
			NetChatFB.emType = pNetMsg->emType;
			StringCchCopy ( NetChatFB.szName, CHR_ID_LENGTH+1, pChar->m_szName );
			StringCchCopy ( NetChatFB.szChatMsg, CHAT_MSG_SIZE+1, pNetMsg->szChatMsg );

			SENDTOPARTY ( pChar->m_dwGaeaID, pChar->m_dwPartyID, (NET_MSG_GENERIC*) &NetChatFB );

			// ÀÚ½ÅÀÇ ¸Þ½ÃÁö¸¦ º¸³¿
			SendToGMMsg( pChar, NetChatFB );
			//// »ó?EæÀ?¸Þ½ÃÁö¸¦ º¸³¿
			//SendToGMMsg( GetChar(pChar->m_dwGaeaID), NetChatFB );

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print

			GLPARTY* pParty = m_cPartyMan.GetParty(pChar->m_dwPartyID);
			if( pParty && pParty->ISVAILD() )
			{
				GLPARTY::MEMBER_ITER iter = pParty->m_cMEMBER.begin();
				GLPARTY::MEMBER_ITER iter_end = pParty->m_cMEMBER.end();

				PGLCHARAG pMemChar = NULL;
				for ( ; iter!=iter_end; ++iter )
				{
					pMemChar = GLAgentServer::GetInstance().GetChar ( (*iter) );
					if ( pMemChar && pMemChar->m_bTracingUser )
					{
						if( pMemChar->m_dwClientID == pChar->m_dwClientID ) continue;

						CDebugSet::ToTracingFile( pMemChar->m_szUserName, "##Party Recv##, [%s][%s]->[%s][%s], %s", 
												  pChar->m_szUserName, pChar->m_szName, pMemChar->m_szUserName, pMemChar->m_szName, pNetMsg->szChatMsg );
					}
				}
			}
			if( pChar->m_bTracingUser )
			{
				CDebugSet::ToTracingFile( pChar->m_szUserName, "##Party Send##, [%s][%s], %s", 
										  pChar->m_szUserName, pChar->m_szName, pNetMsg->szChatMsg  );
			}
#endif
		}
		break;

	case CHAT_TYPE_PRIVATE: // °³ÀÎ¸Þ½Ã?E
		{
			PGLCHARAG pChar = GetChar ( dwGaeaID );
			if ( !pChar )							return FALSE;
			if ( pChar->IsCHATBLOCK() )
			{
				GLMSG::SNETPC_CHAT_BLOCK NetChatBlock;
				StringCchCopy ( NetChatBlock.szName, USR_ID_LENGTH+1, pChar->m_szUserName );
				NetChatBlock.tChatBlock = pChar->m_tCHATBLOCK;

				SENDTOCLIENT ( pChar->m_dwClientID, &NetChatBlock );

				return FALSE;
			}

			CHAR_MAP_ITER iterChar = m_PCNameMap.find ( std::string(pNetMsg->szName) );
			if ( iterChar==m_PCNameMap.end() )
			{
				//	±Ó¼Ó¸»ÀÇ ?EóÀ?¾øÀ»¶§ FB ¸Þ½Ã?E
				GLMSG::SNETPC_CHAT_PRIVATE_FAIL NetMsgFail;
				StringCchCopy ( NetMsgFail.szName, CHR_ID_LENGTH+1, pNetMsg->szName );

				SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFail );

				return FALSE;
			}

			//	»ó?Eæ¿¡°?ÀÚ?EÀÚ½ÅÀÌ ±Ó¼Ó¸» ºúÓ°µÇ?EÀÖ´Â?E°Ë?E
			PGLCHARAG pCHAR_TAR = (*iterChar).second;
			int dwFR_FLAG = pCHAR_TAR->GetStateFriend ( pChar->m_szName );
			
			if ( (dwFR_FLAG==EMFRIEND_BLOCK) && (pChar->m_dwUserLvl>USER_GM3) )
			{
				dwFR_FLAG = EMFRIEND_OFF;
			}

			if ( dwFR_FLAG==EMFRIEND_BLOCK )
			{
				//	ÇØ?E»ç¶÷¿¡°Ô ºúÓ° µÇ¾úÀ»¶§.
				//	±Ó¼Ó¸»ÀÇ ?EóÀ?¾øÀ»¶§ FB ¸Þ½Ã?E
				GLMSG::SNETPC_CHAT_PRIVATE_FAIL NetMsgFail;
				StringCchCopy ( NetMsgFail.szName, CHR_ID_LENGTH+1, pNetMsg->szName );

				SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFail );
			}
			else
			{
				NET_CHAT_FB NetChatFB;
				NetChatFB.emType = pNetMsg->emType;
				NetChatFB.sITEMLINK = pNetMsg->sITEMLINK;
				StringCchCopy ( NetChatFB.szName,CHR_ID_LENGTH+1,pChar->m_szName );
				StringCchCopy ( NetChatFB.szChatMsg, CHAT_MSG_SIZE+1, pNetMsg->szChatMsg );

				PGLCHARAG pGLChar = (*iterChar).second;
				SENDTOCLIENT ( pGLChar->m_dwClientID, &NetChatFB );

				// ÀÚ½ÅÀÇ ¸Þ½ÃÁö¸¦ º¸³¿
				SendToGMMsg( pChar, NetChatFB );
				// »ó?EæÀ?¸Þ½ÃÁö¸¦ º¸³¿
				SendToGMMsg( pGLChar, NetChatFB );

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
			
				if( pChar->m_bTracingUser )
				{
					CDebugSet::ToTracingFile( pChar->m_szUserName, "@@Private Send@@, [%s][%s]->[%s][%s], %s", 
						pChar->m_szUserName, pChar->m_szName, pGLChar->m_szUserName, pGLChar->m_szName, pNetMsg->szChatMsg );
				}
				if( pGLChar->m_bTracingUser )
				{
					CDebugSet::ToTracingFile( pGLChar->m_szUserName, "@@Private Recv@@, [%s][%s]<-[%s][%s], %s", 
						pGLChar->m_szUserName, pGLChar->m_szName, pChar->m_szUserName, pChar->m_szName, pNetMsg->szChatMsg );

				}
#endif

			}
		}
		break;

	case CHAT_TYPE_GUILD : // ±æµå¸Þ½Ã?E
		{
			PGLCHARAG pChar = GetChar ( dwGaeaID );
			if ( !pChar )							return FALSE;
			if ( pChar->m_dwGuild==CLUB_NULL )		return FALSE;
			if ( pChar->IsCHATBLOCK() )
			{
				GLMSG::SNETPC_CHAT_BLOCK NetChatBlock;
				StringCchCopy ( NetChatBlock.szName, USR_ID_LENGTH+1, pChar->m_szUserName );
				NetChatBlock.tChatBlock = pChar->m_tCHATBLOCK;

				SENDTOCLIENT ( pChar->m_dwClientID, &NetChatBlock );

				return FALSE;
			}

			GLCLUB *pCLUB = m_cClubMan.GetClub ( pChar->m_dwGuild );
			if ( !pCLUB )							return FALSE;

			CLUBMEMBERS_ITER pos = pCLUB->m_mapMembers.begin();
			CLUBMEMBERS_ITER end = pCLUB->m_mapMembers.end();
			for ( ; pos!=end; ++pos )
			{
				PGLCHARAG pMEMBER = GetCharID ( (*pos).first );
				if ( !pMEMBER )		continue;

				NET_CHAT_FB NetChatFB;
				NetChatFB.sITEMLINK = pNetMsg->sITEMLINK;
				NetChatFB.emType = pNetMsg->emType;
				StringCchCopy ( NetChatFB.szName,CHR_ID_LENGTH+1,pChar->m_szName );
				StringCchCopy ( NetChatFB.szChatMsg, CHAT_MSG_SIZE+1, pNetMsg->szChatMsg );

				SENDTOCLIENT ( pMEMBER->m_dwClientID, &NetChatFB );

				// »ó?EæÀ?¸Þ½ÃÁö¸¦ º¸³¿
				SendToGMMsg( pMEMBER, NetChatFB );

				
#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
				if( pMEMBER->m_bTracingUser )
				{
					CDebugSet::ToTracingFile( pMEMBER->m_szUserName, "%%Guild Recv%%, [%s][%s]->[%s][%s], %s", 
						pChar->m_szUserName, pChar->m_szName, pMEMBER->m_szUserName, pMEMBER->m_szName, pNetMsg->szChatMsg );
				}
#endif
			}

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
			if( pChar->m_bTracingUser )
			{
				CDebugSet::ToTracingFile( pChar->m_szUserName, "%%Guild Send%%, [%s][%s], %s", pChar->m_szUserName, pChar->m_szName, pNetMsg->szChatMsg  );
			}
#endif

			NET_CHAT_FB NetChatFB;
			NetChatFB.sITEMLINK = pNetMsg->sITEMLINK;
			NetChatFB.emType = pNetMsg->emType;
			StringCchCopy ( NetChatFB.szName,CHR_ID_LENGTH+1,pChar->m_szName );
			StringCchCopy ( NetChatFB.szChatMsg, CHAT_MSG_SIZE+1, pNetMsg->szChatMsg );

			// ÀÚ½ÅÀÇ ¸Þ½ÃÁö¸¦ º¸³¿
			// SendToGMMsg( pChar, NetChatFB );

		}
		break;

	case CHAT_TYPE_ALLIANCE:
		{
			PGLCHARAG pChar = GetChar ( dwGaeaID );
			if ( !pChar )							return FALSE;
			if ( pChar->m_dwGuild==CLUB_NULL )		return FALSE;
			if ( pChar->IsCHATBLOCK() )
			{
				GLMSG::SNETPC_CHAT_BLOCK NetChatBlock;
				StringCchCopy ( NetChatBlock.szName, USR_ID_LENGTH+1, pChar->m_szUserName );
				NetChatBlock.tChatBlock = pChar->m_tCHATBLOCK;

				SENDTOCLIENT ( pChar->m_dwClientID, &NetChatBlock );

				return FALSE;
			}

			GLCLUB *pCLUB = m_cClubMan.GetClub ( pChar->m_dwGuild );
			if ( !pCLUB )							return FALSE;
			if ( pCLUB->m_dwAlliance==CLUB_NULL )	return FALSE;

			GLCLUB *pCLUB_CHIEF = m_cClubMan.GetClub ( pCLUB->m_dwAlliance );
			if ( !pCLUB_CHIEF )						return FALSE;

			CLUB_ALLIANCE_ITER pos_alliance = pCLUB_CHIEF->m_setAlliance.begin();
			CLUB_ALLIANCE_ITER end_alliance = pCLUB_CHIEF->m_setAlliance.end();
			for ( ; pos_alliance!=end_alliance; ++pos_alliance )
			{
				const GLCLUBALLIANCE &sALLIANCE = (*pos_alliance);
				GLCLUB *pCLUB_INDIAN = m_cClubMan.GetClub ( sALLIANCE.m_dwID );
				if ( !pCLUB_INDIAN )	continue;

				CLUBMEMBERS_ITER pos = pCLUB_INDIAN->m_mapMembers.begin();
				CLUBMEMBERS_ITER end = pCLUB_INDIAN->m_mapMembers.end();
				for ( ; pos!=end; ++pos )
				{
					PGLCHARAG pMEMBER = GetCharID ( (*pos).first );
					if ( !pMEMBER )		continue;

					NET_CHAT_FB NetChatFB;
					NetChatFB.emType = pNetMsg->emType;
					NetChatFB.sITEMLINK = pNetMsg->sITEMLINK;
					StringCchCopy ( NetChatFB.szName,CHR_ID_LENGTH+1,pChar->m_szName );
					StringCchCopy ( NetChatFB.szChatMsg, CHAT_MSG_SIZE+1, pNetMsg->szChatMsg );

					SENDTOCLIENT ( pMEMBER->m_dwClientID, &NetChatFB );

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
					if( pMEMBER->m_bTracingUser )
					{
						CDebugSet::ToTracingFile( pMEMBER->m_szUserName, "**Alliance Recv**, [%s][%s]->[%s][%s], %s", 
							pChar->m_szUserName, pChar->m_szName, pMEMBER->m_szUserName, pMEMBER->m_szName, pNetMsg->szChatMsg );
					}
#endif
				}
			}

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
			if( pChar->m_bTracingUser )
			{
				CDebugSet::ToTracingFile( pChar->m_szUserName, "**Alliance Send**, [%s][%s], %s", pChar->m_szUserName, pChar->m_szName, pNetMsg->szChatMsg  );
			}
#endif
		}
		break;

	case CHAT_TYPE_REGION : //add region chat by AnFire16
		{
			PGLCHARAG pChar = GetChar ( dwGaeaID );
			if ( !pChar )							return FALSE;
			if ( pChar->IsCHATBLOCK() )
			{
				GLMSG::SNETPC_CHAT_BLOCK NetChatBlock;
				StringCchCopy ( NetChatBlock.szName, USR_ID_LENGTH+1, pChar->m_szUserName );
				NetChatBlock.tChatBlock = pChar->m_tCHATBLOCK;

				SENDTOCLIENT ( pChar->m_dwClientID, &NetChatBlock );

				return FALSE;
			}

			AGCHARNODE *pCharNode = m_PCList.m_pHead;
			for ( ; pCharNode; pCharNode=pCharNode->pNext )
			{
				if ( pCharNode->Data->m_wSchool == pChar->m_wSchool )
				{
					NET_CHAT_FB NetChatFB;
					NetChatFB.emType = CHAT_TYPE_REGION;
					NetChatFB.sITEMLINK = pNetMsg->sITEMLINK;
					StringCchCopy ( NetChatFB.szName,CHR_ID_LENGTH+1,pChar->m_szName );
					StringCchCopy ( NetChatFB.szChatMsg, CHAT_MSG_SIZE+1, pNetMsg->szChatMsg );

					SENDTOCLIENT ( pCharNode->Data->m_dwClientID, &NetChatFB );
				}
			}
		}
		break;

	default:
		break;
	}

	return TRUE;
}

BOOL GLAgentServer::MsgReqCreateInstantMap ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{

	

	GLMSG::SNETREQ_CREATE_INSTANT_MAP_REQ *pNetMsg = (GLMSG::SNETREQ_CREATE_INSTANT_MAP_REQ *) nmg;
	GLMSG::SNETREQ_CREATE_INSTANT_MAP_FB NetMsgFB;

	PGLCHARAG pChar = GetChar ( pNetMsg->dwGaeaID );
	if ( !pChar )							return FALSE;

	//	Note : Çö?E¸Ê Á¤º¸.
	//
	GLAGLandMan* pCurLandMan = GetByMapID ( pChar->m_sCurMapID );
	if ( !pCurLandMan )
	{
		CDebugSet::ToLogFile( "EMCHAR_GATEOUT_MAPID %d, %d", pChar->m_dwCharID, pChar->m_sCurMapID );

		NetMsgFB.emFB = EMCHAR_CREATE_INSTANT_MAP_FAIL_MAPID;
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}

	// Çö?E°ÔÀÌÆ®
	DxLandGateMan* pCurGateMan = pCurLandMan->GetLandGateMan ();
	PDXLANDGATE pCurGate = pCurGateMan->FindLandGate ( pNetMsg->dwGateID );
	if ( !pCurGate )
	{
		CDebugSet::ToLogFile( "EMCHAR_GATEOUT_GATEID %d %d %d", pChar->m_dwCharID, 
			pChar->m_sCurMapID, pNetMsg->dwGateID );

		NetMsgFB.emFB = EMCHAR_CREATE_INSTANT_MAP_FAIL_GATEID;
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Note : ¸ñÇ¥ ¸Ê.
	//
	GLAGLandMan* pNextLandMan = GetByMapID ( pCurGate->GetToMapID() );
	if ( !pNextLandMan )
	{
		CDebugSet::ToLogFile( "EMCHAR_GATEOUT_TARMAPID %d %d %d %d", 
			pChar->m_dwCharID, pChar->m_sCurMapID, pCurGate->GetGateID(), pCurGate->GetToMapID() );

		NetMsgFB.emFB = EMCHAR_CREATE_INSTANT_MAP_FAIL_TARMAPID;
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Note : ¸ñÇ¥ °ÔÀÌÆ®.
	//
	DxLandGateMan* pNextGateMan = pNextLandMan->GetLandGateMan ();
	PDXLANDGATE pNextGate = pNextGateMan->FindLandGate ( pCurGate->GetToGateID() );
	if ( !pNextGate )
	{
		CDebugSet::ToLogFile( "EMCHAR_GATEOUT_TARGATEID %d, %d %d %d %d", 
			pChar->m_dwCharID, pChar->m_sCurMapID, pNetMsg->dwGateID, pCurGate->GetToMapID(), 
			pCurGate->GetToGateID() );

		NetMsgFB.emFB = EMCHAR_CREATE_INSTANT_MAP_FAIL_TARMAPID;
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}
	SMAPNODE* pMapNode = m_sMapList.FindMapNode (  pCurGate->GetToMapID() );
	if( !pMapNode->bInstantMap )
	{
		NetMsgFB.emFB = EMCHAR_CREATE_INSTANT_MAP_FAIL_NOT;
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}
	DWORD dwNextFieldSvr = GetFieldServer ( pCurGate->GetToMapID() );
	if( pChar->m_dwCurFieldSvr != dwNextFieldSvr )
	{
		NetMsgFB.emFB = EMCHAR_CREATE_INSTANT_MAP_FAIL;
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}

	/*m_sTestInstantMapCharInfo.dwGaeaID	= pNetMsg->dwGaeaID;
	m_sTestInstantMapCharInfo.sBaseMapID = pCurGate->GetToMapID();

	return TRUE;*/

	GLMSG::SNETREQ_CREATE_INSTANT_MAP_FLD NetMsgFld; 
	SNATIVEID sInstantMapID;

	// ÀÎ½ºÅÏÆ® ´ø?E?»ý¼ºÇÏ±â?E?Á¤¸» »ý¼ºÀ» ÇØ¾ßÇÏ´Â?E¿©ºÎ¸¦ ÇÑ¹ø?EÆÇ´ÜÇÑ´Ù.
	if( pNetMsg->bCreate )
	{
		/*VEC_INSTANT_MAPID_ITER iter = m_vecInstantMapId.begin();
		bool  bEnterInstantMap = FALSE;
		for( ; iter != m_vecInstantMapId.end(); ++iter )
		{
			bEnterInstantMap = FALSE;

			SNATIVEID sNativeID = *iter;
			GLAGLandMan* pLandMan = GetByMapID( sNativeID );
			if( !pLandMan ) continue;

			if( pLandMan->GetMapID().wMainID == pCurGate->GetToMapID().wMainID && !pLandMan->IsInstantMap() ) continue;

			if( pLandMan->IsPartyInstantMap() )
			{
				if( pLandMan->GetInstantMapHostID() == pChar->GetPartyID() )
					bEnterInstantMap = TRUE;
			}else if( pChar->GetPartyID() == PARTY_NULL ){
				if( pLandMan->GetInstantMapHostID() == pChar->m_dwGaeaID )
					bEnterInstantMap = TRUE;
			}		

			if( bEnterInstantMap )
			{
				pNetMsg->bCreate	   = FALSE;
				pNetMsg->sInstantMapID = sNativeID;
				break;
			}
		}*/
	}

	if( pNetMsg->bCreate )
	{
		
		sInstantMapID.wMainID = pCurGate->GetToMapID().wMainID;
		sInstantMapID.wSubID  = m_sInsertInstantMapId.InsertInduMapID();
		if( sInstantMapID.wSubID == SNATIVEID::ID_NULL )
		{
			TEXTCONSOLEMSG_WRITE( "[INFO]Create Failed Instant Map! ID reached Max Size! IDSize %d Map ID [%d][%d]", 
								m_sInsertInstantMapId.useMapSubIDSet.size(), sInstantMapID.wMainID, sInstantMapID.wSubID );

			NetMsgFB.emFB = EMCHAR_CREATE_INSTANT_MAP_FAIL_CREATEMAX;
			SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
			return FALSE;
		}



		DWORD StartTime = ::GetTickCount();

		if( CreateInstantMap( pCurGate->GetToMapID(), sInstantMapID, pNetMsg->dwGaeaID, pChar->GetPartyID() ) == E_FAIL )
		{
			NetMsgFB.emFB = EMCHAR_CREATE_INSTANT_MAP_FAIL;
			SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
			return FALSE;
		}

		GLAGLandMan* pInLandMan = NULL;
		pInLandMan = GetByMapID ( sInstantMapID );
		if ( !pInLandMan )
		{
			NetMsgFB.emFB = EMCHAR_CREATE_INSTANT_MAP_FAIL;
			SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
			return FALSE;
		}

		DWORD ElspTime = ::GetTickCount() - StartTime;

		HANDLE hProcess			= GetCurrentProcess(); 
		PROCESS_MEMORY_COUNTERS pmc;
		if( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc)) )
		{
			TEXTCONSOLEMSG_WRITE( "[INFO]Create Instant Map Time %d msec. MapInfo: ID [%d][%d] Size %dbytes. PartyMap %d HostID %d WorkingMemory %dbytes.", 
				ElspTime, sInstantMapID.wMainID, sInstantMapID.wSubID, sizeof(*pInLandMan),
				pInLandMan->IsPartyInstantMap(), pInLandMan->GetInstantMapHostID(), pmc.WorkingSetSize );
		}


		NetMsgFld.bCreate	  = TRUE;
		NetMsgFld.dwGaeaID	  = pNetMsg->dwGaeaID;
		NetMsgFld.dwGateID	  = pNetMsg->dwGateID;
		NetMsgFld.sInstantMapID = sInstantMapID;
		NetMsgFld.sBaseMapID  = pCurGate->GetToMapID();

	}else{
		GLAGLandMan* pInLandMan = GetByMapID( pNetMsg->sInstantMapID );
		if ( !pInLandMan )
		{
			NetMsgFB.emFB = EMCHAR_CREATE_INSTANT_MAP_FAIL;
			SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
			return FALSE;
		}

		HANDLE hProcess			= GetCurrentProcess(); 
		PROCESS_MEMORY_COUNTERS pmc;
		if( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc)) )
		{
			TEXTCONSOLEMSG_WRITE( "[INFO]Enter Instant Map. MapInfo: ID [%d][%d] Size %dbytes. PartyMap %d HostID %d WorkingMemory %dbytes.", 
									pNetMsg->sInstantMapID.wMainID, pNetMsg->sInstantMapID.wSubID, sizeof(*pInLandMan),
									pInLandMan->IsPartyInstantMap(), pInLandMan->GetInstantMapHostID(), pmc.WorkingSetSize );
		}


		sInstantMapID = pNetMsg->sInstantMapID;

		NetMsgFld.bCreate	  = FALSE;
		NetMsgFld.dwGaeaID	  = pNetMsg->dwGaeaID;
		NetMsgFld.dwGateID	  = pNetMsg->dwGateID;
		NetMsgFld.sInstantMapID = sInstantMapID;
		NetMsgFld.sBaseMapID  = pCurGate->GetToMapID();
	}

	
	// Agent ¼­¹ö¿¡¼­ °®?EÀÖ´Â ÄÉ¸¯ÅÍ ¸ÊÁ¤º¸ º¯?E
	pChar->SetCurrentField ( pChar->m_dwCurFieldSvr, sInstantMapID );

	//	Note : ÇÊ?E¼­?Eº¯?EÇÊ?E¾øÀ½. Çö?EÇÊµå¼­¹ö·Î ÀÎ?E¸Ê »ý¼ºÀ» ¿äÃ»
	SENDTOFIELDSVR ( pChar->m_nChannel, pChar->m_dwCurFieldSvr, &NetMsgFld );

	

	return TRUE;
}

BOOL GLAgentServer::TestCreateInstantMap( float fElpasedTime )
{
	if( m_sTestInstantMapCharInfo.sBaseMapID == NATIVEID_NULL() ) return FALSE;

	m_sTestInstantMapCharInfo.fElapsedTime += fElpasedTime;

	if( m_sTestInstantMapCharInfo.fElapsedTime < 0.5f ) return FALSE;
	m_sTestInstantMapCharInfo.fElapsedTime = 0.0f;


	PGLCHARAG pChar = GetChar ( m_sTestInstantMapCharInfo.dwGaeaID );
	if ( !pChar )
	{
		m_sTestInstantMapCharInfo.dwGaeaID	  = 0;
		m_sTestInstantMapCharInfo.fElapsedTime = 0.0f;
		m_sTestInstantMapCharInfo.sBaseMapID   = NATIVEID_NULL();
		return FALSE;
	}

	SNATIVEID sBaseMapID = m_sTestInstantMapCharInfo.sBaseMapID;

	SNATIVEID sInstantMapID;
	sInstantMapID.wMainID = sBaseMapID.wMainID;
	sInstantMapID.wSubID  = m_sInsertInstantMapId.InsertInduMapID();


	if( sInstantMapID.wSubID == SNATIVEID::ID_NULL )
	{
		TEXTCONSOLEMSG_WRITE( "[INFO]Create Failed Instant Map! ID reached Max Size! IDSize %d Map ID [%d][%d]", 
								m_sInsertInstantMapId.useMapSubIDSet.size(), sInstantMapID.wMainID, sInstantMapID.wSubID );

//		NetMsgFB.emFB = EMCHAR_CREATE_INSTANT_MAP_FAIL_CREATEMAX;
//		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}

	


	DWORD StartTime = ::GetTickCount();

	if( CreateInstantMap( sBaseMapID, sInstantMapID, m_sTestInstantMapCharInfo.dwGaeaID, pChar->GetPartyID() ) == E_FAIL )
	{
//		NetMsgFB.emFB = EMCHAR_CREATE_INSTANT_MAP_FAIL;
//		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}

	GLAGLandMan* pInLandMan = NULL;
	pInLandMan = GetByMapID ( sInstantMapID );
	if ( !pInLandMan )	return FALSE;

	DWORD ElspTime = ::GetTickCount() - StartTime;

	HANDLE hProcess			= GetCurrentProcess(); 
	PROCESS_MEMORY_COUNTERS pmc;
	if( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc)) )
	{
		TEXTCONSOLEMSG_WRITE( "[INFO]Create Instant Map! Mem %d Time %d msec Size %dbytes. IDSize %d Map ID [%d][%d]", 
								pmc.WorkingSetSize, ElspTime, sizeof(*pInLandMan), m_sInsertInstantMapId.useMapSubIDSet.size(), 
								sInstantMapID.wMainID, sInstantMapID.wSubID );
	}

	



	GLMSG::SNETREQ_CREATE_INSTANT_MAP_FLD NetMsgFld; 
//	NetMsgFld.dwGaeaID	  = pNetMsg->dwGaeaID;
//	NetMsgFld.dwGateID	  = pNetMsg->dwGateID;
	NetMsgFld.dwGaeaID	    = m_sTestInstantMapCharInfo.dwGaeaID;	
	NetMsgFld.sInstantMapID = sInstantMapID;
	NetMsgFld.sBaseMapID	= sBaseMapID;



	// Agent ¼­¹ö¿¡¼­ °®?EÀÖ´Â ÄÉ¸¯ÅÍ ¸ÊÁ¤º¸ º¯?E
//	pChar->SetCurrentField ( pChar->m_dwCurFieldSvr, sInstantMapID );

	//	Note : ÇÊ?E¼­?Eº¯?EÇÊ?E¾øÀ½. Çö?EÇÊµå¼­¹ö·Î ÀÎ?E¸Ê »ý¼ºÀ» ¿äÃ»
	SENDTOFIELDSVR ( pChar->m_nChannel, pChar->m_dwCurFieldSvr, &NetMsgFld );

	return TRUE;
}

BOOL GLAgentServer::MsgReqDeleteInstantMap( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETREQ_CREATE_INSTANT_MAP_DEL *pNetMsg = (GLMSG::SNETREQ_CREATE_INSTANT_MAP_DEL *) nmg;

	GLAGLandMan *pLandMan = GetByMapID ( pNetMsg->sInstantMapID );
	if( pLandMan == NULL ) return FALSE;
	if( !pLandMan->IsInstantMap() ) return FALSE;

	m_sInsertInstantMapId.DeleteInstantMapID( pNetMsg->sInstantMapID.wSubID );


	VEC_INSTANT_MAPID_ITER MapID_iter = std::find( m_vecInstantMapId.begin(), m_vecInstantMapId.end(), pNetMsg->sInstantMapID.dwID );
	if( MapID_iter != m_vecInstantMapId.end()  ) m_vecInstantMapId.erase(MapID_iter);

	SAFE_DELETE ( pLandMan );
	m_pLandMan[pNetMsg->sInstantMapID.wMainID][pNetMsg->sInstantMapID.wSubID] = NULL;

	HANDLE hProcess			= GetCurrentProcess(); 
	PROCESS_MEMORY_COUNTERS pmc;		
	if( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc)) )
	{
		TEXTCONSOLEMSG_WRITE( "[INFO]Delete Instant Map!! ServerMem %d Instant Map ID [%d][%d]", pmc.WorkingSetSize, pNetMsg->sInstantMapID.wMainID,  pNetMsg->sInstantMapID.wSubID );
	}	


	return TRUE;
	
}


// *****************************************************
// Desc: ÀÌ?EÔÀÌÆ®·?ÀÌµ¿ ¿äÃ» (Field->Agent)
// *****************************************************
BOOL GLAgentServer::MsgReqGateOut ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETREQ_GATEOUT *pNetMsg = (GLMSG::SNETREQ_GATEOUT *) nmg;
	//if ( dwGaeaID!=GAEAID_NULL )			return FALSE;

	PGLCHARAG pChar = GetChar ( pNetMsg->dwGaeaID );
	if ( !pChar )							return FALSE;

	//	Note : Çö?E¸Ê Á¤º¸.
	//
	GLAGLandMan* pCurLandMan = GetByMapID ( pChar->m_sCurMapID );
	if ( !pCurLandMan )
	{
		CDebugSet::ToLogFile( "EMCHAR_GATEOUT_MAPID %d, %d", pChar->m_dwCharID, pChar->m_sCurMapID );

		GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
		NetMsgFB.emFB = EMCHAR_GATEOUT_MAPID;
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}
	
	// Çö?E°ÔÀÌÆ®
	DxLandGateMan* pCurGateMan = pCurLandMan->GetLandGateMan ();
	PDXLANDGATE pCurGate = pCurGateMan->FindLandGate ( pNetMsg->dwGateID );
	if ( !pCurGate )
	{
		CDebugSet::ToLogFile( "EMCHAR_GATEOUT_GATEID %d %d %d", pChar->m_dwCharID, 
			pChar->m_sCurMapID, pNetMsg->dwGateID );

		GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
		NetMsgFB.emFB = EMCHAR_GATEOUT_GATEID;
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Note : ¸ñÇ¥ ¸Ê.
	//
	GLAGLandMan* pNextLandMan = GetByMapID ( pCurGate->GetToMapID() );
	if ( !pNextLandMan )
	{
		CDebugSet::ToLogFile( "EMCHAR_GATEOUT_TARMAPID %d %d %d %d", 
			pChar->m_dwCharID, pChar->m_sCurMapID, pCurGate->GetGateID(), pCurGate->GetToMapID() );

		GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
		NetMsgFB.emFB = EMCHAR_GATEOUT_TARMAPID;
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}

	// ¸ñÇ¥¸ÊÀÌ ¼±µÎÅ¬·´ ?EõÁ¸ÀÎµ?¼±µµ?E?³¡³µ?E¼±µµÅ¬·´ÀÇ ±æ¿øÀÌ ¾Æ´Ï?E
	if ( pNextLandMan->m_bGuidBattleMap )
	{
		if ( GLCONST_CHAR::bPKLESS ) 
		{
			GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
			NetMsgFB.emFB = EMCHAR_GATEOUT_HOLD;
			SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
			return FALSE;
		}
		m_pConsoleMsg->Write( "Entered CW Map" );

		GLGuidance *pGuid = GLGuidanceAgentMan::GetInstance().Find ( pNextLandMan->m_dwClubMapID );
		if ( pGuid )
		{

			// ¼±µµ?EÀÏ¶§ ±æÆ®¹èÆ² ÁßÀÌ°Å³ª Á¾·á½Ã°£ ¹Ì´ÞÀÌ?EÃâÀÔ±Ý?E
			GLCLUB* pClub = m_cClubMan.GetClub ( pChar->m_dwGuild );
			if ( pClub && pGuid->m_bBattle && ( pClub->GetAllBattleNum() > 0 || !pClub->IsGuidBattle()) )
			{
				GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
				NetMsgFB.emFB = EMCHAR_GATEOUT_CLUBBATTLE;
				SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
				return FALSE;
			}
			m_pConsoleMsg->Write( "Entered CW Map" );

			GLCLUB* pGuidanceClub = m_cClubMan.GetClub ( pGuid->m_dwGuidanceClub );
			if ( !pGuid->m_bBattle && !pGuid->IsGuidClub(pChar->m_dwGuild) )
			{
				if ( pGuidanceClub )
				{
					// ¼±µµÅ¬·´ÀÇ µ¿¸ÍÀÌ ¾Æ´Ï?E
					if ( !pGuidanceClub->IsAllianceGuild ( pChar->m_dwGuild ) )
					{
						GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
						NetMsgFB.emFB = EMCHAR_GATEOUT_HOLD;
						SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
						return FALSE;
					}
				}
			}
			else
			{
				m_pConsoleMsg->Write( "Entered CW Map" );
			}
		}
	}

	// ¸ñÇ¥¸ÊÀÌ ¼±µÎÅ¬·´ ?EõÁ¸ÀÎµ?¼±µµ?E?³¡³µ?E¼±µµÅ¬·´ÀÇ ±æ¿øÀÌ ¾Æ´Ï?E
	if ( pNextLandMan->m_bClubDeathMatchMap )
	{
		if ( GLCONST_CHAR::bPKLESS || pChar->m_nChannel != 0) 
		{
			GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
			NetMsgFB.emFB = EMCHAR_GATEOUT_HOLD;
			SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
			return FALSE;
		}

		GLClubDeathMatch *pCDM = GLClubDeathMatchAgentMan::GetInstance().Find ( pNextLandMan->m_dwClubMapID );
		if ( pCDM )
		{
			GLCLUB* pClub = m_cClubMan.GetClub ( pChar->m_dwGuild );

			if ( !pCDM->IsEnterMap( pChar->m_dwGuild ) || !pClub )
			{
				GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
				NetMsgFB.emFB = EMCHAR_GATEOUT_HOLD;
				SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
				return FALSE;
			}			
			
			if ( pClub )
			{
				// Å¬·´¹èÆ² ÁøÇàÁßÀÏ¶§´Â ¸øµé¾ûÌ£´Ù.
                if ( pClub->GetAllBattleNum() > 0 )
				{
					GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
					NetMsgFB.emFB = EMCHAR_GATEOUT_CLUBBATTLE2;
					SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
					return FALSE;
				}

				if ( !pClub->IsMemberFlgCDM(pChar->m_dwCharID) )
				{
					GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
					NetMsgFB.emFB = EMCHAR_GATEOUT_HOLD;
					SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
					return FALSE;
				}
			}			
		}
	}

	if ( pNextLandMan->m_bSchoolWarsMap )
	{
		if ( GLCONST_CHAR::bPKLESS || pChar->m_nChannel != 0) 
		{
			GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
			NetMsgFB.emFB = EMCHAR_GATEOUT_HOLD;
			SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
			return FALSE;
		}

		GLSchoolWars *pSW = GLSchoolWarsAgentMan::GetInstance().Find ( pNextLandMan->m_dwSchoolWarMapID );
		if ( pSW )
		{
			if ( !pSW->IsEnterMap(pChar->m_dwCharID) )
			{
				GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
				NetMsgFB.emFB = EMCHAR_GATEOUT_HOLD;
				SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
				return FALSE;
			}						
		}
	}

	//we must fucking modify this fucking variable
	//when entering a ctf map player should be assigned to different gate! called fucking home base!
	DWORD dwTOGATEID = pCurGate->GetToGateID();

	//royal rumble random respawn fix
	if ( pNextLandMan->m_bRoyalRumbleMap )
	{
		if ( GLCONST_CHAR::bPKLESS || pChar->m_nChannel != 0) 
		{
			GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
			NetMsgFB.emFB = EMCHAR_GATEOUT_HOLD;
			SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
			return FALSE;
		}

		GLRoyalRumble *pRR = GLRoyalRumbleAgentMan::GetInstance().Find ( pNextLandMan->m_dwRoyalRumbleMapID );
		if ( pRR )
		{
			if ( !pRR->IsEnterMap( pChar->m_dwCharID ) )
			{
				GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
				NetMsgFB.emFB = EMCHAR_GATEOUT_HOLD;
				SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
				return FALSE;
			}
			else
			{
				if ( pNextLandMan->m_bRoyalRumbleMap )
				{
					srand(time(NULL));
					PDXLANDGATE pTESTGATE = pNextLandMan->GetLandGateMan()->FindLandGate ( (DWORD)RANDOM_GATE );

					if ( pTESTGATE )
					{
						dwTOGATEID = pTESTGATE->GetGateID();
					}
				}
			}
		}
	}

	if ( pNextLandMan->m_bTowerWarsMap )
	{
		if ( GLCONST_CHAR::bPKLESS || pChar->m_nChannel != 0) 
		{
			GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
			NetMsgFB.emFB = EMCHAR_GATEOUT_HOLD;
			SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
			return FALSE;
		}

		GLTowerWars *pSW = GLTowerWarsAgentMan::GetInstance().Find ( pNextLandMan->m_dwTowerWarsMapID );
		if ( pSW )
		{
			if ( !pSW->IsEnterMap() )
			{
				GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
				NetMsgFB.emFB = EMCHAR_GATEOUT_HOLD;
				SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
				return FALSE;
			}
			else
			{
				if ( pChar )
				{
					PDXLANDGATE pTESTGATE = pNextLandMan->GetLandGateMan()->FindLandGate ( pSW->GetReviveGate( pChar->m_wSchool ) );						
					if ( pTESTGATE )
					{
						dwTOGATEID = pTESTGATE->GetGateID();
					}
				}
			}
		}
	}

	//	Note : ¸ñÇ¥ °ÔÀÌÆ®.
	//
	DxLandGateMan* pNextGateMan = pNextLandMan->GetLandGateMan ();
	PDXLANDGATE pNextGate = pNextGateMan->FindLandGate ( pCurGate->GetToGateID() );
	if ( !pNextGate )
	{
		CDebugSet::ToLogFile( "EMCHAR_GATEOUT_TARGATEID %d, %d %d %d %d", 
			pChar->m_dwCharID, pChar->m_sCurMapID, pNetMsg->dwGateID, pCurGate->GetToMapID(), 
			pCurGate->GetToGateID() );

		GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
		NetMsgFB.emFB = EMCHAR_GATEOUT_TARGATEID;
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Note : ÇÊ?E¼­¹ö°¡ °°Àº ¸ÊÁ¾?EÀÏ¶§¿¡´Â ÇÊ?E¼­?Eº¯°æÀÌ ÇÊ?E¾øÀ½.
	//
	DWORD dwNextFieldSvr = GetFieldServer ( pCurGate->GetToMapID() );
	if ( dwNextFieldSvr==pChar->m_dwCurFieldSvr )
	{
		// Agent ¼­¹ö¿¡¼­ °®?EÀÖ´Â ÄÉ¸¯ÅÍ ¸ÊÁ¤º¸ º¯?E
		pChar->SetCurrentField ( pChar->m_dwCurFieldSvr, pCurGate->GetToMapID() );

		//	Note : ÇÊ?E¼­?Eº¯?EÇÊ?E¾øÀ½. Çö?EÇÊµå¼­¹ö·Î ¸ÊÀÌµ¿À» ¿äÃ».
		//
		SENDTOFIELDSVR ( pChar->m_nChannel, pChar->m_dwCurFieldSvr, nmg );
	}
	//	Note : ÇÊ?E¼­?Eº¯?EÇÊ?E
	//
	else
	{
		//	Note : ÇÊ?E¼­¹ö°¡ Á¤»óÀÎ?E°Ë?E
		//
		BOOL bSVR_OK = m_pMsgServer->IsSlotOnline ( dwNextFieldSvr );
		if ( !bSVR_OK )
		{
			GLMSG::SNETREQ_GATEOUT_FB NetMsgFB;
			NetMsgFB.emFB = EMCHAR_GATEOUT_FIELDSVR;
			SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgFB );
			return FALSE;
		}

		//	Note : ÇÊ?E¼­?Eº¯°æ½Ã Å¬¶óÀÌ¾ðÆ® Á¤º¸ º¯?E»çÇ× ¹Ý¿µ.
		//
		ReActionMoveFieldSvr ( pChar->m_dwClientID, pChar->m_dwGaeaID );

		//	Çö?EÇÊ?E¼­¹ö¿¡ ÀÚ½ÅÀÌ ¶°³ª°¥ ¿¹Á¤ÀÓÀ» ?E?
		GLMSG::SNETPC_FIELDSVR_OUT NetMsg;
		SENDTOFIELD ( pChar->m_dwClientID, &NetMsg );

		//	ÀÌµ¿ÇÒ ¸Ê ID Àú?E
		pChar->SetNextFieldSvr ( pCurGate->GetToMapID(), pCurGate->GetToGateID(), D3DXVECTOR3(FLT_MAX,FLT_MAX,FLT_MAX), dwNextFieldSvr );


		
	}

	return TRUE;
}

BOOL GLAgentServer::CheckStartMap( DWORD dwGaeaID )
{
	PGLCHARAG pChar = GetChar ( dwGaeaID );
	if ( !pChar )			return FALSE;

	GLAGLandMan *pLandMan=NULL;
	DWORD dwGenGate = 0;
	pLandMan = GetByMapID ( pChar->m_sStartMapID );

	if ( pLandMan && pLandMan->m_bClubDeathMatchMap )
	{
		if ( GLCONST_CHAR::bPKLESS ) return FALSE;

		if ( pChar->m_nChannel != 0 )	return FALSE;

        GLClubDeathMatch *pCDM = GLClubDeathMatchAgentMan::GetInstance().Find ( pLandMan->m_dwClubMapID );
		if ( pCDM && !pCDM->IsEnterMap( pChar->m_dwGuild ) )	return FALSE;

		GLCLUB* pClub = m_cClubMan.GetClub ( pChar->m_dwGuild );
		if ( !pClub )	return FALSE;		

		// Å¬·´¹èÆ² ÁøÇàÁßÀÏ¶§´Â ¸øµé¾ûÌ£´Ù.
		if ( pClub->GetAllBattleNum() > 0 )	return FALSE;
		if ( !pClub->IsMemberFlgCDM(pChar->m_dwCharID) )	return FALSE;
	}

	if ( pLandMan && pLandMan->m_bSchoolWarsMap )
	{
		if ( GLCONST_CHAR::bPKLESS ) return FALSE;

		if ( pChar->m_nChannel != 0 )	return FALSE;

        GLSchoolWars *pSW = GLSchoolWarsAgentMan::GetInstance().Find ( pLandMan->m_dwSchoolWarMapID );
		if ( pSW && !pSW->IsEnterMap(pChar->m_dwCharID) )	return FALSE;
	}

	if ( pLandMan && pLandMan->m_bRoyalRumbleMap )
	{
		if ( GLCONST_CHAR::bPKLESS ) return FALSE;

		if ( pChar->m_nChannel != 0 )	return FALSE;

        GLRoyalRumble *pRR = GLRoyalRumbleAgentMan::GetInstance().Find ( pLandMan->m_dwRoyalRumbleMapID );
		if ( pRR && !pRR->IsEnterMap(pChar->m_dwCharID) )	return FALSE;

		DWORD dwMY_PARTYID = pChar->GetPartyID();

		GLPARTY* pPARTY = m_cPartyMan.GetParty ( dwMY_PARTYID );
		if ( pPARTY ) return false;
	}

	if ( pLandMan && pLandMan->m_bTowerWarsMap )
	{
		if ( GLCONST_CHAR::bPKLESS ) return FALSE;

		if ( pChar->m_nChannel != 0 )	return FALSE;

        GLTowerWars *pSW = GLTowerWarsAgentMan::GetInstance().Find ( pLandMan->m_dwTowerWarsMapID );
		if ( pSW && !pSW->IsEnterMap() )	return FALSE;
	}

	if ( !pLandMan ) 		
	{
		return FALSE;
	}
	else if ( !pLandMan->GetLandGateMan()->FindLandGate(pChar->m_dwStartGate) )
	{
		PDXLANDGATE pLandGate = pLandMan->GetLandGateMan()->GetListLandGate();
		if ( !pLandGate )	return FALSE;	//	Gate°¡ ÇÏ³ªµµ ¾ø´Â °÷¿£ ºÎÈ°ÇÒ ?E¾øÀ½.
	}

	return TRUE;

	if ( !pLandMan ) 		
	{
		return FALSE;
	}
	else if ( !pLandMan->GetLandGateMan()->FindLandGate(pChar->m_dwStartGate) )
	{
		PDXLANDGATE pLandGate = pLandMan->GetLandGateMan()->GetListLandGate();
		if ( !pLandGate )	return FALSE;	//	Gate°¡ ÇÏ³ªµµ ¾ø´Â °÷¿£ ºÎÈ°ÇÒ ¼E¾øÀ½.
	}

	return TRUE;
}

// *****************************************************
// Desc: ºÎÈ°¿äÃ» Ã³¸®
// *****************************************************
BOOL GLAgentServer::MsgReqReBirth ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pChar = GetChar ( dwGaeaID );
	if ( !pChar )			return FALSE;

	//  ºÎÈ° ÁöÁ¡À¸·Î ÁøÀÔ ºÒ°¡½Ã ºÎÈ° ÁöÁ¡À» ÃÊ±âÈ­ÇÑ´Ù.
	GLMSG::SNETPC_REQ_REBIRTH *pNetMsg = (GLMSG::SNETPC_REQ_REBIRTH *) nmg;

	bool bStartMap = false;
	
	//	ºÎÈ°.
	GLAGLandMan *pLandMan=NULL;
	DWORD dwGenGate = 0;

	if ( pNetMsg->bCTFMAP )
	{
		GLAGLandMan * pLandManCTF = GetByMapID ( pNetMsg->sCURMAPID );
		if ( pLandManCTF )
		{
			if ( pLandManCTF->m_bTowerWarsMap )
			{
				GLTowerWars *pTW = GLTowerWarsAgentMan::GetInstance().Find ( pLandManCTF->m_dwTowerWarsMapID );
				if ( pTW && pTW->IsEnterMap() )	
				{
					PDXLANDGATE pTWGATE = pLandManCTF->GetLandGateMan()->FindLandGate(pTW->GetReviveGate( pChar->m_wSchool ));
					if ( pTWGATE )
					{
						pChar->m_sStartMapID = pTW->m_dwClubMap;
						pChar->m_dwStartGate = pTWGATE->GetGateID();
						pChar->m_vStartPos = pTWGATE->GetGenPos( DxLandGate::GEN_RENDUM );
					}
				}
			}

			if ( pLandManCTF->m_bRoyalRumbleMap )
			{
				GLRoyalRumble *pRR = GLRoyalRumbleAgentMan::GetInstance().Find ( pLandManCTF->m_dwRoyalRumbleMapID );
				if ( pRR && pRR->IsEnterMap(pChar->m_dwCharID) )	
				{
					PDXLANDGATE pRRGATE = pLandManCTF->GetLandGateMan()->FindLandGate( (DWORD)RANDOM_GATE );
					if ( pRRGATE )
					{
						pChar->m_sStartMapID = pRR->m_dwClubMap;
						pChar->m_dwStartGate = pRRGATE->GetGateID();
						pChar->m_vStartPos = pRRGATE->GetGenPos( DxLandGate::GEN_RENDUM );
					}
				}
			}
		}
	}

	//	½ÃÀÛÀ§Ä¡°¡ º¯°æµÇ¾ûÚß ÇÏ´Â °æ¿E
	if ( pNetMsg->bRegenEntryFailed || !CheckStartMap( dwGaeaID ) )
	{
		pChar->m_sStartMapID = GLCONST_CHAR::nidSTARTMAP[pChar->m_wSchool];
		pChar->m_dwStartGate = GLCONST_CHAR::dwSTARTGATE[pChar->m_wSchool];
		pChar->m_vStartPos   = D3DXVECTOR3(0.0f,0.0f,0.0f);

		SNATIVEID nidSTARTMAP = pChar->m_sStartMapID;
		DWORD dwSTARTGATE = pChar->m_dwStartGate;

		pLandMan = GetByMapID ( nidSTARTMAP );
		if ( pLandMan )
		{
			DxLandGateMan* pLandGateMan = pLandMan->GetLandGateMan();
			if ( !pLandGateMan->FindLandGate ( dwSTARTGATE ) )
			{
				DEBUGMSG_WRITE ( "(Revive) - Default gate is a failure. school %d", pChar->m_wSchool );
				return FALSE;
			}
			else
			{
				dwGenGate = dwSTARTGATE;
			}
		}
		else
		{
			DEBUGMSG_WRITE(	"GLAgentServer::MsgReqReBirth Default map is a failure. school %d",	pChar->m_wSchool );
			return FALSE;
		}
	}
	else
	{
		pLandMan = GetByMapID ( pChar->m_sStartMapID );
		
		//	¿©?EÀÌ¿ÜÀÇ »óÈ²Àº À§¿¡¼­ ´Ù °É·¯Áø´Ù. 
		if ( pLandMan )
		{
			if ( !pLandMan->GetLandGateMan()->FindLandGate(pChar->m_dwStartGate) ) 
			{
				PDXLANDGATE pLandGate = pLandMan->GetLandGateMan()->GetListLandGate();
				if ( pLandGate )	dwGenGate = pLandGate->GetGateID();		//	Ã¹¹øÂ° Gate ¿¡¼­ »ý?E
				else
				{
					DEBUGMSG_WRITE(	"GLAgentServer::MsgReqReBirth Error Logic No Gate" );
					return FALSE;
				}
			}
			else	dwGenGate = pChar->m_dwStartGate;
		}
		else
		{
			//	ÀÏ¾ûÏ¯?E¾ø´Â »óÈ²
			DEBUGMSG_WRITE(	"GLAgentServer::MsgReqReBirth Error Logic No LandMan" );
			return FALSE;
		}
	}

/*
	if( pNetMsg->bRegenEntryFailed )
	{
		pChar->m_sStartMapID = GLCONST_CHAR::nidSTARTMAP[pChar->m_wSchool];
		pChar->m_dwStartGate = GLCONST_CHAR::dwSTARTGATE[pChar->m_wSchool];
		pChar->m_vStartPos   = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}

	//	ºÎÈ°.
	GLAGLandMan *pLandMan=NULL;
	DWORD dwGenGate = 0;

	//	ºÎÈ°ÇÒ Map?EGate À¯È¿¼º °Ë?E
	if ( pChar->m_sStartMapID!=NATIVEID_NULL() )
	{
		pLandMan = GetByMapID ( pChar->m_sStartMapID );

		if ( pLandMan )
		{
			DxLandGateMan* pLandGateMan = pLandMan->GetLandGateMan();
			if ( pLandGateMan->FindLandGate(pChar->m_dwStartGate)==NULL )
			{
				PDXLANDGATE pLandGate = pLandGateMan->GetListLandGate();
				if ( !pLandGate )	pLandMan = NULL;					//	Gate°¡ ÇÏ³ªµµ ¾ø´Â °÷¿£ ºÎÈ°ÇÒ ?E¾øÀ½.
				else				dwGenGate = pLandGate->GetGateID();	//	Ã¹¹øÂ° Gate ¿¡¼­ »ý?E
			}
			else					dwGenGate = pChar->m_dwStartGate;
		}
	}
	

	if ( !pLandMan )
	{
		SNATIVEID nidSTARTMAP = GLCONST_CHAR::nidSTARTMAP[pChar->m_wSchool];
		DWORD dwSTARTGATE = GLCONST_CHAR::dwSTARTGATE[pChar->m_wSchool];

		pLandMan = GetByMapID ( nidSTARTMAP );
		if ( pLandMan )
		{
			DxLandGateMan* pLandGateMan = pLandMan->GetLandGateMan();
			if ( !pLandGateMan->FindLandGate ( dwSTARTGATE ) )
			{
				DEBUGMSG_WRITE ( "(Revive) - Default gate is a failure. school %d", pChar->m_wSchool );
				return FALSE;
			}
			else
			{
				dwGenGate = dwSTARTGATE;
			}
		}
	}

	if ( !pLandMan )
	{
		DEBUGMSG_WRITE(
			"GLAgentServer::MsgReqReBirth Default map is a failure. school %d",
			pChar->m_wSchool );
		return FALSE;
	}
*/
	SNATIVEID sBirthMapID = pLandMan->GetMapID ();

	DWORD dwNextFieldSvr = GetFieldServer ( sBirthMapID );
	if ( dwNextFieldSvr==pChar->m_dwCurFieldSvr )
	{
		pChar->SetCurrentField ( pChar->m_dwCurFieldSvr, sBirthMapID );

		//	Note : ÇÊ?E¼­?Eº¯°æÀÌ ÇÊ?E¾øÀ»¶§. Çö?EÇÊµå¼­¹ö·Î ºÎÈ°À» ¿äÃ».
		//
		SENDTOFIELD ( dwClientID, nmg );
	}
	else
	{
		//	Note : ÇÊ?E¼­¹öÀÇ º¯°æÀÌ ÇÊ¿äÇÒ °æ?E
		//

		//	Note : ÇÊ?E¼­?Eº¯°æ½Ã Å¬¶óÀÌ¾ðÆ® Á¤º¸ º¯?E»çÇ× ¹Ý¿µ.
		//
		ReActionMoveFieldSvr ( dwClientID, dwGaeaID );


		//	ÇöÁ¦ ÇÊ?E¼­¹ö¿¡ ÀÚ½ÅÀÌ ´Ù¸¥ °÷¿¡¼­ ºÎÈ°ÇÒ ¿¹Á¤ÀÓÀ» ?E?
		GLMSG::SNETPC_REBIRTH_OUT NetMsg;
		SENDTOFIELD ( dwClientID, &NetMsg );

		//	ÀÌµ¿ÇÒ ¸Ê ID Àú?E
		pChar->SetNextFieldSvr ( sBirthMapID, dwGenGate, D3DXVECTOR3(FLT_MAX,FLT_MAX,FLT_MAX), dwNextFieldSvr );
	}

	return TRUE;
}

BOOL GLAgentServer::MsgReqReGenGate ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETPC_REQ_REGEN_GATE_FB *pNetMsg = (GLMSG::SNETPC_REQ_REGEN_GATE_FB *)nmg;

	PGLCHARAG pChar = GetChar ( dwGaeaID );
	if ( !pChar )			return FALSE;

	//	Note : º¯°æµÈ ½ºÅ¸Æ® ?E ½ºÅ¸Æ® °ÔÀÌÆ®ÀÇ Á¤º¸¸¦ Àû?E
	//
	pChar->m_sStartMapID = pNetMsg->sMapID;
	pChar->m_dwStartGate = pNetMsg->dwGateID;

	SENDTOCLIENT ( pChar->m_dwClientID, nmg );

	return TRUE;
}

// *****************************************************
// Desc: ÇÊµå¼­¹ö¿¡ Á¢¼ÓÁ¤º¸ ?E?ÇÊµå¼­¹ö°¡ ¹Ù²ð°æ?E
// *****************************************************
BOOL GLAgentServer::MsgFieldSvrOutFb ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	if( dwGaeaID < 0 || dwGaeaID >= m_dwMaxClient ) 
		return FALSE;

	PGLCHARAG pChar = GetChar ( dwGaeaID );
	if ( !pChar )			return FALSE;

	if ( pChar->m_sNextMapID==SNATIVEID(MAXLANDMID,MAXLANDSID) )	return FALSE;

	//	Note : Çö?EÇÊ?E¼­?E¹× ¸Ê ID ÁöÁ¤.
	pChar->SetCurrentField ( pChar->m_dwNextFieldSvr, pChar->m_sNextMapID );

	//	Note : ¸Ê¿¡ »õ·Î ÁøÀÔÇÏ?EÀ§ÇØ¼­ Field¼­¹ö¿¡ ¸Þ½Ã?E¼Û½Å.
	//
	NET_GAME_JOIN_FIELDSVR NetJoinField;
	NetJoinField.emType = EMJOINTYPE_MOVEMAP;
	
	NetJoinField.dwSlotAgentClient = pChar->m_dwClientID;
	StringCchCopy ( NetJoinField.szUID, DAUM_MAX_UID_LENGTH+1, pChar->m_szUserName );
	NetJoinField.nUserNum = pChar->m_dwUserID;
	NetJoinField.dwUserLvl = pChar->m_dwUserLvl;
	NetJoinField.nChaNum = pChar->m_dwCharID;
	NetJoinField.dwGaeaID = pChar->m_dwGaeaID;
	NetJoinField.tPREMIUM = pChar->m_tPREMIUM;
	NetJoinField.tCHATBLOCK = pChar->m_tCHATBLOCK;

	NetJoinField.sStartMap = pChar->m_sNextMapID;
	NetJoinField.dwStartGate = pChar->m_dwNextGateID;
	NetJoinField.vStartPos = pChar->m_vNextPos;

	NetJoinField.dwActState = pChar->m_dwActState;
	NetJoinField.bUseArmSub	= pChar->m_bUseArmSub;

	NetJoinField.dwThaiCCafeClass	= pChar->m_dwThaiCCafeClass;
	NetJoinField.nMyCCafeClass		= pChar->m_nMyCCafeClass;				// ¸»·¹ÀÌ½Ã¾Æ PC?EÀÌº¥Æ®

	NetJoinField.sChinaTime			= pChar->m_sChinaTime;
	NetJoinField.sEventTime			= pChar->m_sEventTime;
	NetJoinField.sVietnamGainSystem = pChar->m_sVietnamSystem;

	

	//** Add EventTime


	pChar->ResetNextFieldSvr ();

	SENDTOFIELD ( dwClientID, &NetJoinField );

	return TRUE;
}

BOOL GLAgentServer::MsgReBirthOutFb ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pChar = GetChar ( dwGaeaID );
	if ( !pChar )			return FALSE;

	if ( pChar->m_sNextMapID==SNATIVEID(MAXLANDMID,MAXLANDSID) )	return FALSE;

	//	Note : Çö?EÇÊ?E¼­?E¹× ¸Ê ID ÁöÁ¤.
	pChar->SetCurrentField ( pChar->m_dwNextFieldSvr, pChar->m_sNextMapID );

	//	Note : ¸Ê¿¡ »õ·Î ÁøÀÔÇÏ?EÀ§ÇØ¼­ Field¼­¹ö¿¡ ¸Þ½Ã?E¼Û½Å.
	//
	NET_GAME_JOIN_FIELDSVR NetJoinField;
	NetJoinField.emType = EMJOINTYPE_REBIRTH;
	
	NetJoinField.dwSlotAgentClient = pChar->m_dwClientID;
	NetJoinField.nUserNum = pChar->m_dwUserID;
	StringCchCopy ( NetJoinField.szUID, DAUM_MAX_UID_LENGTH+1, pChar->m_szUserName );
	NetJoinField.dwUserLvl = pChar->m_dwUserLvl;
	NetJoinField.nChaNum = pChar->m_dwCharID;
	NetJoinField.dwGaeaID = pChar->m_dwGaeaID;
	NetJoinField.tPREMIUM = pChar->m_tPREMIUM;
	NetJoinField.tCHATBLOCK = pChar->m_tCHATBLOCK;

	NetJoinField.sStartMap = pChar->m_sNextMapID;
	NetJoinField.dwStartGate = pChar->m_dwNextGateID;
	NetJoinField.vStartPos = D3DXVECTOR3(0,0,0);

	NetJoinField.dwActState = pChar->m_dwActState;
	NetJoinField.bUseArmSub	= pChar->m_bUseArmSub;

	NetJoinField.dwThaiCCafeClass	= pChar->m_dwThaiCCafeClass;
	NetJoinField.nMyCCafeClass		= pChar->m_nMyCCafeClass;					// ¸»·¹ÀÌ½Ã¾Æ PC?EÀÌº¥Æ®

	NetJoinField.sChinaTime			= pChar->m_sChinaTime;
	NetJoinField.sEventTime			= pChar->m_sEventTime;
	NetJoinField.sVietnamGainSystem = pChar->m_sVietnamSystem;

	//** Add EventTime

	pChar->ResetNextFieldSvr ();

	SENDTOFIELD ( dwClientID, &NetJoinField );

	return TRUE;
}
// *****************************************************
// Desc: ·¹º§ ¾÷½Ã Çö?E¸Ê¿¡ ¸Ó¹°·¯ ÀÖ?E¾Ê¾Æ¾ß ÇÏ´Â °æ?E
// *****************************************************
BOOL GLAgentServer::MsgLvUpMustLeaveMap( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pChar = GetChar ( dwGaeaID );
	if ( !pChar )			return FALSE;

	GLMSG::SNETPC_REQ_MUST_LEAVE_MAP_AG *pNetMsg = (GLMSG::SNETPC_REQ_MUST_LEAVE_MAP_AG *) nmg;

	//	Note : ¸ñÇ¥ ¸Ê.
	//
	GLAGLandMan* pNextLandMan = GetByMapID ( pNetMsg->sMAPID );
	if ( !pNextLandMan )
	{
		GLMSG::SNETPC_REQ_MUST_LEAVE_MAP_FB NetMsgFB;
		NetMsgFB.emFB = EMREQ_MUST_LEAVE_MAP_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Note : ÀÌµ¿ À§Ä¡ Á¤º¸ À¯È¿¼º °Ë?E
	//
	if ( pNetMsg->dwGATEID==UINT_MAX && pNetMsg->vPOS==D3DXVECTOR3(FLT_MAX,FLT_MAX,FLT_MAX) )
	{
		GLMSG::SNETPC_REQ_MUST_LEAVE_MAP_FB NetMsgFB;
		NetMsgFB.emFB = EMREQ_MUST_LEAVE_MAP_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	// ¸ÊÀÌ ÀÖ´Â?E
	SMAPNODE* pMapNode = m_sMapList.FindMapNode ( pNetMsg->sMAPID );
	if ( !pMapNode )
	{
		GLMSG::SNETPC_REQ_MUST_LEAVE_MAP_FB NetMsgFB;
		NetMsgFB.emFB = EMREQ_MUST_LEAVE_MAP_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	DWORD dwNextFieldSvr = pMapNode->dwFieldSID;

	// ÇÊµå¼­¹ö¸¦ ¿Å°Ü¾ß ÇÒ °æ?E
	{
		//	Note : ÇÊµå¼­¹ö°¡ Á¤»óÀÎ?E°Ë?E
		//
		BOOL bSVR_OK = m_pMsgServer->IsSlotOnline ( dwNextFieldSvr );
		if ( !bSVR_OK )
		{
			GLMSG::SNETPC_REQ_MUST_LEAVE_MAP_FB NetMsgFB;
			NetMsgFB.emFB = EMREQ_MUST_LEAVE_MAP_FB_FAIL;
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
			return FALSE;
		}

		//	Note : ÇÊ?E¼­?Eº¯°æ½Ã Å¬¶óÀÌ¾ðÆ® Á¤º¸ º¯?E»çÇ× ¹Ý¿µ.
		//
		ReActionMoveFieldSvr ( dwClientID, dwGaeaID );

		//	Çö?EÇÊ?E¼­¹ö¿¡ ÀÚ½ÅÀÌ ¶°³ª°¥ ¿¹Á¤ÀÓÀ» ?E?
		GLMSG::SNETPC_FIELDSVR_OUT NetMsg;
		SENDTOFIELD ( pChar->m_dwClientID, &NetMsg );

		//	ÀÌµ¿ÇÒ ¸Ê ID Àú?E
		pChar->SetNextFieldSvr ( pNetMsg->sMAPID, pNetMsg->dwGATEID, pNetMsg->vPOS, dwNextFieldSvr );

	}

	return TRUE;
}


// *****************************************************
// Desc: ¼ÒÈ¯¿äÃ» Ã³¸® (´Ù¸¥ ÇÊµå¼­¹öÀÏ °æ?E
// *****************************************************
BOOL GLAgentServer::MsgReCallAg ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pChar = GetChar ( dwGaeaID );
	if ( !pChar )			return FALSE;

	GLMSG::SNETPC_REQ_RECALL_AG *pNetMsg = (GLMSG::SNETPC_REQ_RECALL_AG *) nmg;

	//	Note : ¸ñÇ¥ ¸Ê.
	//
	GLAGLandMan* pNextLandMan = GetByMapID ( pNetMsg->sMAPID );
	if ( !pNextLandMan )
	{
		GLMSG::SNETPC_REQ_RECALL_FB NetMsgFB;
		NetMsgFB.emFB = EMREQ_RECALL_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Note : ÀÌµ¿ À§Ä¡ Á¤º¸ À¯È¿¼º °Ë?E
	//
	if ( pNetMsg->dwGATEID==UINT_MAX && pNetMsg->vPOS==D3DXVECTOR3(FLT_MAX,FLT_MAX,FLT_MAX) )
	{
		GLMSG::SNETPC_REQ_RECALL_FB NetMsgFB;
		NetMsgFB.emFB = EMREQ_RECALL_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	// ¸ÊÀÌ ÀÖ´Â?E
	SMAPNODE* pMapNode = m_sMapList.FindMapNode ( pNetMsg->sMAPID );
	if ( !pMapNode )
	{
		GLMSG::SNETPC_REQ_RECALL_FB NetMsgFB;
		NetMsgFB.emFB = EMREQ_RECALL_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	DWORD dwNextFieldSvr = pMapNode->dwFieldSID;

	// ÇÊµå¼­¹ö¸¦ ¿Å°Ü¾ß ÇÒ °æ?E
	{
		//	Note : ÇÊµå¼­¹ö°¡ Á¤»óÀÎ?E°Ë?E
		//
		BOOL bSVR_OK = m_pMsgServer->IsSlotOnline ( dwNextFieldSvr );
		if ( !bSVR_OK )
		{
			GLMSG::SNETPC_REQ_RECALL_FB NetMsgFB;
			NetMsgFB.emFB = EMREQ_RECALL_FB_FAIL;
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
			return FALSE;
		}

		//	Note : ÇÊ?E¼­?Eº¯°æ½Ã Å¬¶óÀÌ¾ðÆ® Á¤º¸ º¯?E»çÇ× ¹Ý¿µ.
		//
		ReActionMoveFieldSvr ( dwClientID, dwGaeaID );

		//	Çö?EÇÊ?E¼­¹ö¿¡ ÀÚ½ÅÀÌ ¶°³ª°¥ ¿¹Á¤ÀÓÀ» ?E?
		GLMSG::SNETPC_FIELDSVR_OUT NetMsg;
		SENDTOFIELD ( pChar->m_dwClientID, &NetMsg );

		//	ÀÌµ¿ÇÒ ¸Ê ID Àú?E
		pChar->SetNextFieldSvr ( pNetMsg->sMAPID, pNetMsg->dwGATEID, pNetMsg->vPOS, dwNextFieldSvr );

	}

	return TRUE;
}

BOOL GLAgentServer::MsgTeleportAg ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pChar = GetChar ( dwGaeaID );
	if ( !pChar )			return FALSE;

	GLMSG::SNETPC_REQ_TELEPORT_AG *pNetMsg = (GLMSG::SNETPC_REQ_TELEPORT_AG *) nmg;

	//	Note : ¸ñÇ¥ ¸Ê.
	//
	GLAGLandMan* pNextLandMan = GetByMapID ( pNetMsg->sMAPID );
	if ( !pNextLandMan )
	{
		GLMSG::SNETPC_REQ_TELEPORT_FB NetMsgFB;
		NetMsgFB.emFB = EMREQ_TELEPORT_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Note : ÀÌµ¿ À§Ä¡ Á¤º¸ À¯È¿¼º °Ë?E
	//
	if ( pNetMsg->vPOS==D3DXVECTOR3(FLT_MAX,FLT_MAX,FLT_MAX) )
	{
		GLMSG::SNETPC_REQ_TELEPORT_FB NetMsgFB;
		NetMsgFB.emFB = EMREQ_TELEPORT_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	// ¸ÊÀÌ ÀÖ´Â?E
	SMAPNODE* pMapNode = m_sMapList.FindMapNode ( pNetMsg->sMAPID );
	if ( !pMapNode )
	{
		GLMSG::SNETPC_REQ_TELEPORT_FB NetMsgFB;
		NetMsgFB.emFB = EMREQ_TELEPORT_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	DWORD dwNextFieldSvr = pMapNode->dwFieldSID;

	// ÇÊµå¼­¹ö¸¦ ¿Å°Ü¾ß ÇÒ °æ?E
	{
		//	Note : ÇÊµå¼­¹ö°¡ Á¤»óÀÎ?E°Ë?E
		//
		BOOL bSVR_OK = m_pMsgServer->IsSlotOnline ( dwNextFieldSvr );
		if ( !bSVR_OK )
		{
			GLMSG::SNETPC_REQ_TELEPORT_FB NetMsgFB;
			NetMsgFB.emFB = EMREQ_TELEPORT_FB_FAIL;
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
			return FALSE;
		}

		//	Note : ÇÊ?E¼­?Eº¯°æ½Ã Å¬¶óÀÌ¾ðÆ® Á¤º¸ º¯?E»çÇ× ¹Ý¿µ.
		//
		ReActionMoveFieldSvr ( dwClientID, dwGaeaID );

		//	Çö?EÇÊ?E¼­¹ö¿¡ ÀÚ½ÅÀÌ ¶°³ª°¥ ¿¹Á¤ÀÓÀ» ?E?
		GLMSG::SNETPC_FIELDSVR_OUT NetMsg;
		SENDTOFIELD ( pChar->m_dwClientID, &NetMsg );

		//	ÀÌµ¿ÇÒ ¸Ê ID Àú?E
		pChar->SetNextFieldSvr ( pNetMsg->sMAPID, UINT_MAX, pNetMsg->vPOS, dwNextFieldSvr );

	}

	return TRUE;

}

BOOL GLAgentServer::MsgPartyLure ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_PARTY_LURE* pNetMsg = (GLMSG::SNET_PARTY_LURE*) nmg;
	
	PGLCHARAG pCharMaster = GetChar ( dwGaeaID );
	if ( !pCharMaster )							return FALSE;
	DWORD dwPartyID = pCharMaster->m_dwPartyID;

	PGLCHARAG pCharTar;
	if ( pNetMsg->bName ){	pCharTar = GetChar ( pNetMsg->szNAME );	}
	else	{	pCharTar = GetChar ( pNetMsg->dwGaeaID );}

	if ( !pCharTar )
	{
		GLMSG::SNET_PARTY_LURE_FB NetMsgFB;
		NetMsgFB.dwGaeaID = dwGaeaID;
		NetMsgFB.emAnswer = EMPARTY_LURE_NO_TARGET;

		SENDTOCLIENT ( pCharMaster->m_dwClientID, &NetMsgFB );

		return FALSE;
	}

	if ( !pNetMsg->sOption.VALID_OPT() )
	{
		GLMSG::SNET_PARTY_LURE_FB NetMsgFB;
		NetMsgFB.dwGaeaID = dwGaeaID;
		NetMsgFB.emAnswer = EMPARTY_LURE_OPT;

		SENDTOCLIENT ( pCharMaster->m_dwClientID, &NetMsgFB );

		return FALSE;
	}

	//	Note : ?EóÀ?ÀÌ¹Ì ÆÄÆ¼¿¡ °¡ÀÔµÇ?EÀÖÀ½.
	//
	if ( pCharTar->m_dwPartyID!=PARTY_NULL )
	{
		GLMSG::SNET_PARTY_LURE_FB NetMsgFB;
		NetMsgFB.dwGaeaID = dwGaeaID;
		NetMsgFB.emAnswer = EMPARTY_LURE_OTHER;

		SENDTOCLIENT ( pCharMaster->m_dwClientID, &NetMsgFB );

		return FALSE;
	}

	GLAGLandMan* pLandMan = GetByMapID ( pCharMaster->m_sCurMapID );
	if ( pCharMaster->m_wSchool != pCharTar->m_wSchool && ( pLandMan->m_bTowerWarsMap ) )
	{
		return FALSE;
	}

	//////////////cannot pt in battle royal map
	if ( pLandMan->IsRedZone() )
	{
		GLMSG::SNET_PARTY_LURE_FB NetMsgFB;
		NetMsgFB.dwGaeaID = dwGaeaID;
		NetMsgFB.emAnswer = EMPARTY_LURE_ROYAL_MAP;

		SENDTOCLIENT ( pCharMaster->m_dwClientID, &NetMsgFB );

		return FALSE;
	}

	if ( pLandMan->IsRoyalRumble() )
	{
		GLMSG::SNET_PARTY_LURE_FB NetMsgFB;
		NetMsgFB.dwGaeaID = dwGaeaID;
		NetMsgFB.emAnswer = EMPARTY_LURE_ROYAL_MAP;

		SENDTOCLIENT ( pCharMaster->m_dwClientID, &NetMsgFB );

		return FALSE;
	}

	SNATIVEID sCurMapID = pCharMaster->m_sCurMapID;
	if ( sCurMapID.wMainID==147 )
	{
		GLMSG::SNET_PARTY_LURE_FB NetMsgFB;
		NetMsgFB.dwGaeaID = dwGaeaID;
		NetMsgFB.emAnswer = EMPARTY_LURE_ROYAL_MAP;

		SENDTOCLIENT ( pCharMaster->m_dwClientID, &NetMsgFB );

		return FALSE;
	}
	////////////////////////////

	GLClubMan& cClubMan = GLAgentServer::GetInstance().GetClubMan();

	GLCLUB *pCLUB = cClubMan.GetClub ( pCharTar->m_dwGuild );
	GLCLUB *pCLUB_M = cClubMan.GetClub ( pCharMaster->m_dwGuild );

	if ( pCLUB )
	{
		bool bClubBattle = false;
		// ÆÄÆ¼°¡ ¾øÀ»°æ?E( ÀÚ½Å¸¸ Ã¼Å© ) 				
		if ( dwPartyID==PARTY_NULL )
		{
			if ( pCLUB->IsBattle( pCharMaster->m_dwGuild ) ) bClubBattle = true;
			if ( pCLUB_M && pCLUB->IsBattleAlliance( pCLUB_M->m_dwAlliance ) ) bClubBattle = true;
		}
		//	ÀÖÀ»°æ?E¸ð?E¸â¹ö?EÃ¼Å©
		else
		{		
			GLPARTY* pParty = m_cPartyMan.GetParty ( dwPartyID );
			
			if( pParty && pParty->ISVAILD() )
			{
				GLPARTY::MEMBER_ITER iter = pParty->m_cMEMBER.begin();
				GLPARTY::MEMBER_ITER iter_end = pParty->m_cMEMBER.end();
				PGLCHARAG pMemChar = NULL;

				for ( ; iter!=iter_end; ++iter )
				{
					pMemChar = GLAgentServer::GetInstance().GetChar ( (*iter) );
					if ( !pMemChar ) continue;
			
					if ( pCLUB->IsBattle(pMemChar->m_dwGuild) )
					{
						bClubBattle = true;
						break;
					}
					
					GLCLUB* pClub_Mem = cClubMan.GetClub( pMemChar->m_dwGuild );

					if( pClub_Mem && pCLUB->IsBattleAlliance( pClub_Mem->m_dwAlliance ))
					{
						bClubBattle = true;
						break;
					}
				}
			}
		}	

		if ( bClubBattle ) 
		{
			GLMSG::SNET_PARTY_LURE_FB NetMsgFB;
			NetMsgFB.dwGaeaID = dwGaeaID;
			NetMsgFB.emAnswer = EMPARTY_LURE_CLUBBATTLE;

			SENDTOCLIENT ( pCharMaster->m_dwClientID, &NetMsgFB );

			return FALSE;
		}
	}

	//	Note : ´Ù¸¥ ÇÐ¿ø»ý?EÆÄÆ¼ °á¼º Á¦ÇÑ ¿É¼ÇÀÌ ÀÖÀ» °æ?EÁ¦ÇÑÇÔ.
	if ( !GLCONST_CHAR::bPARTY_2OTHERSCHOOL )
	{
		if ( pCharTar->m_wSchool!=pCharMaster->m_wSchool )
		{
			GLMSG::SNET_PARTY_LURE_FB NetMsgFB;
			NetMsgFB.dwGaeaID = dwGaeaID;
			NetMsgFB.emAnswer = EMPARTY_LURE_OTHERSCHOOL;

			SENDTOCLIENT ( pCharMaster->m_dwClientID, &NetMsgFB );

			return FALSE;
		}
	}

	//	Note : ¾Æ?EÀÚ½ÅÀÇ ÆÄÆ¼°¡ ¸¸µé?EÁö?E¾Ê¾ÒÀ» °æ?E ?Eó¿¡°?ÆÄÆ¼ ?E?¿äÃ».
	//
	if ( dwPartyID==PARTY_NULL )
	{
		pCharMaster->m_sReqPartyOpt = pNetMsg->sOption;

		GLMSG::SNET_PARTY_LURE_TAR NetMsgLureTar;
		NetMsgLureTar.dwMasterID = dwGaeaID;
		NetMsgLureTar.dwPartyID = PARTY_NULL;
		NetMsgLureTar.sOption = pCharMaster->m_sReqPartyOpt;

		SENDTOCLIENT ( pCharTar->m_dwClientID, &NetMsgLureTar );

		return TRUE;
	}

	GLPARTY* pParty = m_cPartyMan.GetParty ( dwPartyID );
	if ( !pParty )								return FALSE;
	if ( !pParty->ISMASTER(dwGaeaID) )			return FALSE;

	if ( pParty->ISFULL() )
	{
		GLMSG::SNET_PARTY_LURE_FB NetMsgFB;
		NetMsgFB.dwGaeaID = dwGaeaID;
		NetMsgFB.emAnswer = EMPARTY_LURE_FULL;

		SENDTOCLIENT ( pCharMaster->m_dwClientID, &NetMsgFB );

		return FALSE;
	}

	//	Note : ?EóÀÚ¸?¸ðÁý ?Eó¿?µûÓÏÇÔ.
	//
	pParty->PREADDMEMBER ( pCharTar->m_dwGaeaID );
    
	//	Note : ?Eó¿¡°?ÆÄÆ¼ ?E?¿äÃ».
	//
	GLMSG::SNET_PARTY_LURE_TAR NetMsgLureTar;
	NetMsgLureTar.dwMasterID = dwGaeaID;
	NetMsgLureTar.dwPartyID = dwPartyID;
	NetMsgLureTar.sOption = pCharMaster->m_sReqPartyOpt;

	SENDTOCLIENT ( pCharTar->m_dwClientID, &NetMsgLureTar );

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
	if( pCharMaster->m_bTracingUser )
	{
		CDebugSet::ToTracingFile( pCharMaster->m_szUserName, "Party Request, [%s][%s], Target Char: [%s][%s]",
								  pCharMaster->m_szUserName, pCharMaster->m_szName, pCharTar->m_szUserName, pCharTar->m_szName );
	}
#endif

	return TRUE;
}

BOOL GLAgentServer::MsgPartyLureTarAns ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_PARTY_LURE_TAR_ANS* pNetMsg = (GLMSG::SNET_PARTY_LURE_TAR_ANS*) nmg;

	PGLCHARAG pCharMaster = GetChar ( pNetMsg->dwMasterID );
	if ( !pCharMaster )											return FALSE;
	
	// ÆÄÆ¼°¡ ÃÖÃÊ·Î ±¸¼ºµÉ¶§
	if ( pNetMsg->dwPartyID == PARTY_NULL && pCharMaster->GetPartyID() == PARTY_NULL )
	{
		PGLCHARAG pCharTar = GetChar ( dwGaeaID );
		if ( !pCharTar )										return FALSE;
		if ( pCharTar->GetPartyID()!=PARTY_NULL )				return FALSE;

		if ( pNetMsg->emAnswer != EMPARTY_LURE_OK )
		{
			if ( pCharMaster->m_sReqPartyOpt!=pNetMsg->sOption )
			{
				GLMSG::SNET_PARTY_LURE_FB NetMsgFB;
				NetMsgFB.dwGaeaID = dwGaeaID;
				NetMsgFB.emAnswer = EMPARTY_LURE_OPT;

				SENDTOCLIENT ( pCharMaster->GetPartyID(), &NetMsgFB );
				return FALSE;
			}

			GLMSG::SNET_PARTY_LURE_FB NetMsgFB;
			NetMsgFB.dwGaeaID = dwGaeaID;
			NetMsgFB.emAnswer = pNetMsg->emAnswer;

			SENDTOCLIENT ( pCharMaster->m_dwClientID, &NetMsgFB );

			return FALSE;
		}

		//	Note : ÆÄÆ¼ »ý¼º.
		//
		GLPARTY* pParty = m_cPartyMan.NewParty ( pNetMsg->dwMasterID );
		if ( !pParty )										return FALSE;

		//	Note : ÆÄÆ¼ ¿É¼Ç ÁöÁ¤.
		//
		pParty->m_sOPTION = pNetMsg->sOption;

		//	Note : ÆÄÆ¼ ±¸¼º¿ø¿¡ Ãß°¡. ( Ã¹¹øÂÅ ±¸¼º?E)
		//
		pCharTar->SetPartyID ( pParty->m_dwPARTYID );
		pParty->ADDMEMBER ( dwGaeaID );

		//	Note : ÆÄÆ¼ »ý¼ºÀ» ÇÊµå¿¡ ¾Ë¸². ( ÇÊ?E¼­¹ö´Â ÆÄÆ¼ Á¤º¸À» ¹ÞÀ¸?E»õ·ÎÀÌ ÆÄÆ¼¸¦ ±¸¼ºÇÑ´Ù. )
		//
		GLMSG::SNET_PARTY_FNEW NetPartyInfo;
		NetPartyInfo.SETINFO ( pParty->m_dwPARTYID, pParty->m_dwMASTER );
		NetPartyInfo.sOption = pParty->m_sOPTION;

		GLPARTY::MEMBER_ITER iter = pParty->m_cMEMBER.begin();
		GLPARTY::MEMBER_ITER iter_end = pParty->m_cMEMBER.end();

		for ( ; iter!=iter_end; ++iter )
		{
			PGLCHARAG pCharMem = GetChar ( (*iter) );
			NetPartyInfo.ADDMEMBER ( GLPARTY_FNET(pCharMem->m_dwGaeaID,pCharMem->m_szName,pCharMem->m_emClass,pCharMem->m_sCurMapID,pCharMem->m_wLevel,pCharMem->m_wSchool) ); //Add Level and School by NjD //Party System
		}

		SENDTOALLCHANNEL ( &NetPartyInfo );

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
		if( pCharTar->m_bTracingUser )
		{
			CDebugSet::ToTracingFile( pCharTar->m_szUserName, "Create Party Answer OK, [%s][%s], Master Char: [%s][%s]",
					 				  pCharTar->m_szUserName, pCharTar->m_szName, pCharMaster->m_szUserName, pCharMaster->m_szName );
		}
#endif

		return TRUE;
	}
	// ÆÄÆ¼¿øÀ» Ãß°¡ÇÒ¶§
	else if ( pNetMsg->dwMasterID == pCharMaster->m_dwGaeaID )
	{
		GLPARTY* pParty = m_cPartyMan.GetParty ( pCharMaster->GetPartyID() );
		if ( !pParty )									return FALSE;
		if ( pParty->ISFULL() )							return FALSE;

		// ÆÄÆ¼°¡ °á¼ºµÇ?E¾ÊÀº »óÈ²¿¡¼­´Â ¿¹ºñ¸â¹öµéÀ» Ãß°¡ ÇÒ?E¾ø´Â
		// °æ?E?¹ß»ýÇÒ ?EÀÖÀ¸¹Ç·Î ¿©±â¼­ ¾Æ·¡ ÄÚµå¸¦ Ã³¸®ÇÏ?E¾Ê´Â´Ù!
		// if ( !pParty->ISPREMEMBER ( dwGaeaID ) )		return FALSE;

		//	Note : ?EóÀÚ¸?¸ðÁý ?Eó¿¡¼?Á¦¿ÜÇÔ.
		//
		pParty->PREDELMEMBER ( dwGaeaID );

		if ( pNetMsg->emAnswer == EMPARTY_LURE_OK )
		{
			PGLCHARAG pCharTar = GetChar ( dwGaeaID );
			if ( !pCharTar )							return FALSE;
			if ( pCharTar->GetPartyID()!=PARTY_NULL )	return FALSE;

			//	Note : ÆÄÆ¼ ±¸¼º¿ø¿¡ Ãß°¡.
			//
			pCharTar->SetPartyID ( pCharMaster->GetPartyID() );
			pParty->ADDMEMBER ( dwGaeaID );

			//	Note : ÇÊ?E¼­¹ö¿¡ ÆÄÆ¼¿øÀÌ Ãß°¡µÊÀ» ¾Ë¸².
			//
			GLMSG::SNET_PARTY_ADD NetPartyAdd;
			NetPartyAdd.dwPartyID = pCharMaster->GetPartyID();
			NetPartyAdd.sPartyInfo = GLPARTY_FNET(pCharTar->m_dwGaeaID,pCharTar->m_szName,pCharTar->m_emClass,pCharTar->m_sCurMapID,pCharTar->m_wLevel,pCharTar->m_wSchool); //Add Level and School by NjD //Party System

			SENDTOALLCHANNEL ( &NetPartyAdd );

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
			if( pCharTar->m_bTracingUser )
			{
				CDebugSet::ToTracingFile( pCharTar->m_szUserName, "Add Party Answer OK, [%s][%s], Master Char: [%s][%s]",
					pCharTar->m_szUserName, pCharTar->m_szName, pCharMaster->m_szUserName, pCharMaster->m_szName );
			}
#endif
		}

		//	Note : ÆÄÆ¼ ¸ðÁý ¿äÃ» ÀÀ´äÀ» master¿¡°Ô ¾Ë¸².
		//
		GLMSG::SNET_PARTY_LURE_FB NetMsgFB;
		NetMsgFB.dwGaeaID = dwGaeaID;
		NetMsgFB.emAnswer = pNetMsg->emAnswer;

		SENDTOCLIENT ( pCharMaster->m_dwClientID, &NetMsgFB );


	}

	

	return TRUE;
}

BOOL GLAgentServer::MsgPartySecede ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_PARTY_SECEDE* pNetMsg = (GLMSG::SNET_PARTY_SECEDE*) nmg;

	GLPARTY* pParty = m_cPartyMan.GetParty ( pNetMsg->dwPartyID );
	if ( !pParty )									return FALSE;
	if ( !pParty->ISMEMBER(pNetMsg->dwGaeaID) )		return FALSE;

	//	Note : ÀÚ½Å ÀÌ¿ÜÀÇ »ç¶÷ÀÌ Å»ÅðµÉ °æ?E?ÆÄÆ¼ÀåÀÇ ±ÇÇÑÀÌ ÀÖ¾ûÚß °¡´É.
	//
	if ( ( pNetMsg->dwGaeaID != dwGaeaID ) && !pParty->ISMASTER(dwGaeaID) )		return FALSE;

	PGLCHARAG pCharTar = GetChar ( pNetMsg->dwGaeaID );
	if ( !pCharTar )						return FALSE;

	//	Note : ÆÄÆ¼¿øÀÌ Å»?EÇÔÀ» ÆÄÆ¼¿øµé¿¡°Ô ¾Ë¸².
	//
	GLMSG::SNET_PARTY_DEL NetMsgDel;
	NetMsgDel.dwPartyID = pNetMsg->dwPartyID;
	NetMsgDel.dwDelMember = pNetMsg->dwGaeaID;

	SENDTOPARTY ( pNetMsg->dwPartyID, (NET_MSG_GENERIC*) &NetMsgDel );

	//	Note : ÆÄÆ¼¿øÀÌ Å»?EÇÔÀ» ÇÊ?E¼­¹ö¿¡ ¾Ë¸².
	//
	SENDTOALLCHANNEL ( &NetMsgDel );

	//	Note : ÆÄÆ¼ Å»?EÃ³¸®.
	//
	pCharTar->ReSetPartyID ();
	pParty->DELMEMBER ( pNetMsg->dwGaeaID );

	return TRUE;
}

BOOL GLAgentServer::MsgPartyAuthority( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_PARTY_AUTHORITY* pNetMsg = ( GLMSG::SNET_PARTY_AUTHORITY* ) nmg;

	GLPARTY* pParty = m_cPartyMan.GetParty ( pNetMsg->dwPartyID );
	if ( !pParty )										return FALSE;
	if ( !pParty->ISMEMBER( pNetMsg->dwGaeaID ) )		return FALSE;

	if ( ( pNetMsg->dwGaeaID != dwGaeaID ) && !pParty->ISMASTER( dwGaeaID ) )		return FALSE;

	PGLCHARAG pCharTar = GetChar ( pNetMsg->dwGaeaID );
	if ( !pCharTar )						return FALSE;

	//	Note : ÆÄÆ¼ÀåÀÌ ¹Ù?E°ÍÀ» ÆÄÆ¼¿øµé¿¡°Ô ¾Ë¸².
	//
	GLMSG::SNET_PARTY_AUTHORITY NetMsgAuth;
	NetMsgAuth.dwPartyID = pNetMsg->dwPartyID;
	NetMsgAuth.dwGaeaID = pNetMsg->dwGaeaID;

	SENDTOPARTY ( pNetMsg->dwPartyID, ( NET_MSG_GENERIC* ) &NetMsgAuth );

	//	Note : ÆÄÆ¼ÀåÀÌ ¹Ù?E°ÍÀ»À» ÇÊ?E¼­¹ö¿¡ ¾Ë¸².
	//
	SENDTOALLCHANNEL ( &NetMsgAuth );

	pParty->CHANGEMASTER( pNetMsg->dwGaeaID );

	return TRUE;
}

BOOL GLAgentServer::MsgPartyDissolve ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_PARTY_DISSOLVE* pNetMsg = (GLMSG::SNET_PARTY_DISSOLVE*) nmg;
	
	GLPARTY* pParty = m_cPartyMan.GetParty ( pNetMsg->dwPartyID );
	if ( !pParty )									return FALSE;
	if ( !pParty->ISMASTER(dwGaeaID) )				return FALSE;
	
	//	Note : ÆÄÆ¼¸¦ ÇØÃ¼ ÇÑ´Ù.
	//
	m_cPartyMan.DelParty ( pNetMsg->dwPartyID );

	return TRUE;
}

BOOL GLAgentServer::MsgReqGateOutFB ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETREQ_GATEOUT_FB *pNetMsg = (GLMSG::SNETREQ_GATEOUT_FB *) nmg;

	//	Note : Å¬¶óÀÌ¾ðÆ®¿¡ ?EÛÇÑ´?
	SENDTOCLIENT ( dwClientID, nmg );

	return TRUE;
}

BOOL GLAgentServer::MsgReqReBirthFB ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETPC_REQ_REBIRTH_FB *pNetMsg = (GLMSG::SNETPC_REQ_REBIRTH_FB *) nmg;

	//	Note : Å¬¶óÀÌ¾ðÆ®¿¡ ?EÛÇÑ´?
	SENDTOCLIENT ( dwClientID, nmg );

	return TRUE;
}

BOOL GLAgentServer::MsgReqCreateInstantMapFB ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETREQ_CREATE_INSTANT_MAP_FB *pNetMsg = (GLMSG::SNETREQ_CREATE_INSTANT_MAP_FB *) nmg;

	//	Note : Å¬¶óÀÌ¾ðÆ®¿¡ ?EÛÇÑ´?
	SENDTOCLIENT ( dwClientID, nmg );

	return TRUE;
}



BOOL GLAgentServer::MsgReqConfront ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETPC_REQ_CONFRONT *pNetMsg = (GLMSG::SNETPC_REQ_CONFRONT *) nmg;

	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )		return FALSE;

	GLAGLandMan* pLandMan = GetByMapID ( pMyChar->m_sCurMapID );
	if ( !pLandMan )
	{
		//	Note : ÀÏ¹Ý ¿À?E
		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emFB = EMCONFRONT_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pLandMan->m_bGuidBattleMap )
	{
		//	Note : ÀÏ¹Ý ¿À?E
		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emFB = EMCONFRONT_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pLandMan->m_bClubDeathMatchMap )
	{
		//	Note : ÀÏ¹Ý ¿À?E
		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emFB = EMCONFRONT_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pLandMan->m_bSchoolWarsMap )
	{
		//	Note : ÀÏ¹Ý ¿À?E
		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emFB = EMCONFRONT_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pLandMan->m_bTowerWarsMap )
	{
		//	Note : ÀÏ¹Ý ¿À·ù.
		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emFB = EMCONFRONT_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	PGLCHARAG pTarChar = GetChar ( pNetMsg->dwID );
	if ( !pTarChar )
	{
		//	Note : ÀÏ¹Ý ¿À?E
		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emFB = EMCONFRONT_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( !pNetMsg->sOption.VALID_OPT() )
	{
		//	Note : ÀÏ¹Ý ¿À?E
		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emFB = EMCONFRONT_OPTION;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pLandMan->IsPeaceZone() )
	{
		//	Note : ÆòÈ­ Áö¿ª¿¡¼­´Â ?E?ºÒ°¡.
		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emFB = EMCONFRONT_PEACE;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pLandMan->IsRedZone() )
	{
		//	Note : ÆòÈ­ Áö¿ª¿¡¼­´Â ´ë·Ã ºÒ°¡.
		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emFB = EMCONFRONT_PEACE;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );

		return FALSE;
	}

	if ( pLandMan->m_bRoyalRumbleMap )
	{
		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emFB = EMCONFRONT_PEACE;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );

		return FALSE;
	}
	

	DWORD dwMY_PARTYID = pMyChar->GetPartyID();
	if ( PARTY_NULL!=dwMY_PARTYID )
	{
		GLPARTY* pPARTY = m_cPartyMan.GetParty ( dwMY_PARTYID );
		if ( pPARTY && pPARTY->ISMEMBER(pTarChar->m_dwGaeaID) )
		{
			//	Note : °°Àº ÆÄÆ¼ ¸â?E³¢¸®´Â ?E?ºÒ°¡.
			GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
			NetMsgFB.emFB = EMCONFRONT_PARTY;
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
		}
	}

	const SCONFTING &sMYCONFTING = pMyChar->GETCONFRONTING();
	if ( sMYCONFTING.IsCONFRONTING() )
	{
		//	Note : (ÀÚ½ÅÀÌ) ÀÌ¹Ì ?E?ÁßÀÔ´Ï´Ù.
		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emFB = EMCONFRONT_ALREADY_ME;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	const SCONFTING &sTARCONFTING = pTarChar->GETCONFRONTING ();
	if ( sTARCONFTING.IsCONFRONTING() )
	{
		//	Note : (»ó?EæÀ? ÀÌ¹Ì ?E?ÁßÀÔ´Ï´Ù.
		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emFB = EMCONFRONT_ALREADY_TAR;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}
	
	switch ( pNetMsg->emTYPE )
	{
	case EMCONFT_ONE:
		{
			//	Note : ?E?Á¤º¸´Â "?E? Á¾·á½Ã ¾çÀÚ ¸ðµÎ ·Î±×¸¦ ³²±â¹Ç·Î GaeaID ÇÏ³ª¸¸ È®ÀÎÇÏ?EÁßº¹ ?E?Ã¼Å©°¡ °¡´É.
			//
			DWORD dwCHARID = pMyChar->m_dwCharID;
			const SCONFT_LOG* pCONFT = pTarChar->GETCONFRONT_LOG ( dwCHARID );
			if ( pCONFT )
			{
				//	Note : ÀÏÁ¤ ½Ã°£¾È¿¡ ÁöÁ¤È½?EÀÌ?E?E?¹æ?E
				if ( pCONFT->dwCOUNT >= GLCONST_CHAR::dwCONFRONT_MAX )
				{
					GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
					NetMsgFB.emFB = EMCONFRONT_MAX;
					NetMsgFB.fTIME = GLCONST_CHAR::fCONFRONT_RESET - pCONFT->fTIMER;	//	?E?°¡´É¿¡ ³²Àº½Ã°£ : <¿¬¼Ó?EÃ¹æÁE¸®¼Â½Ã°£ - °æ°ú½Ã°£.
					SENDTOCLIENT ( dwClientID, &NetMsgFB );
					return FALSE;
				}

				//	Note : Á¾?E?EÃÈ?ÀÏÁ¤½Ã°£ °æ?EÀÌ?E??E?¹æ?E
				if ( pCONFT->fTIMER < GLCONST_CHAR::fCONFRONT_ELAP )
				{
					GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
					NetMsgFB.emFB = EMCONFRONT_ELAP;
					NetMsgFB.fTIME = GLCONST_CHAR::fCONFRONT_ELAP - pCONFT->fTIMER;	//	?E?°¡´É¿¡ ³²Àº½Ã°£ : <¿¬¼Ó?EÃ¹æÁE¸®¼Â½Ã°£ - °æ°ú½Ã°£.
					SENDTOCLIENT ( dwClientID, &NetMsgFB );
					return FALSE;
				}
			}

			//	Note : ?E?¿ÀÃ»ÇÑ Á¤º¸ Àú?E
			//
			pMyChar->m_sREQCONFTING.RESET();
			pMyChar->m_sREQCONFTING.emTYPE = EMCONFT_ONE;
			pMyChar->m_sREQCONFTING.dwTAR_ID = pTarChar->m_dwGaeaID;
			pMyChar->m_sREQCONFTING.sOption = pNetMsg->sOption;

			//	Note : ?E?(»ó?Eæ¿¡°? ¿äÃ».
			//
			GLMSG::SNETPC_REQ_CONFRONT_TAR NetMsgTAR;
			NetMsgTAR.dwID = dwGaeaID;	// ÀÚ½ÅÀÇ ID.
			NetMsgTAR.sOption = pNetMsg->sOption;
			SENDTOCLIENT ( pTarChar->m_dwClientID, &NetMsgTAR );


#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
			if( pMyChar->m_bTracingUser )
			{
				CDebugSet::ToTracingFile( pMyChar->m_szUserName, "Confront1 Request, [%s][%s], Target Char: [%s][%s]",
										  pMyChar->m_szUserName, pMyChar->m_szName, pTarChar->m_szUserName, pTarChar->m_szName );
			}
#endif
		}
		break;

	case EMCONFT_PARTY:
		{
			DWORD dwMyPartyID = pMyChar->GetPartyID();
			DWORD dwTarPartyID = pTarChar->GetPartyID();
		
			if ( dwMyPartyID==GAEAID_NULL )
			{
				//	Note : (ÀÚ½ÅÀÌ) ÆÄÆ¼¸¦ °á¼ºÇÏ?E¾Ê¾Ò½À´Ï´Ù.
				GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
				NetMsgFB.emFB = EMCONFRONT_MENOTPARTY;
				SENDTOCLIENT ( dwClientID, &NetMsgFB );
				return FALSE;
			}

			GLPARTY *pMyParty = m_cPartyMan.GetParty(dwMyPartyID);
			if ( NULL==pMyParty )
			{
				//	Note : (ÀÚ½ÅÀÌ) ÆÄÆ¼¸¦ °á¼ºÇÏ?E¾Ê¾Ò½À´Ï´Ù.
				GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
				NetMsgFB.emFB = EMCONFRONT_MENOTPARTY;
				SENDTOCLIENT ( dwClientID, &NetMsgFB );
				return FALSE;
			}

			if ( FALSE==pMyParty->ISMASTER(pMyChar->m_dwGaeaID) )
			{
				//	Note : (ÀÚ½ÅÀÌ) ÆÄÆ¼ ¸¶½ºÅÍ°¡ ¾Æ´Õ´Ï´Ù.
				GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
				NetMsgFB.emFB = EMCONFRONT_MENOTMASTER;
				SENDTOCLIENT ( dwClientID, &NetMsgFB );
				return FALSE;
			}

			if ( dwTarPartyID==GAEAID_NULL )
			{
				//	Note : (»ó?EæÀ? ÆÄÆ¼¸¦ °á¼ºÇÏ?E¾Ê¾Ò½À´Ï´Ù.
				GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
				NetMsgFB.emFB = EMCONFRONT_TARMASTER;
				SENDTOCLIENT ( dwClientID, &NetMsgFB );
				return FALSE;
			}

			GLPARTY *pTarParty = m_cPartyMan.GetParty(dwTarPartyID);
			if ( NULL==pTarParty )
			{
				//	Note : (»ó?EæÀ? ÆÄÆ¼¸¦ °á¼ºÇÏ?E¾Ê¾Ò½À´Ï´Ù.
				GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
				NetMsgFB.emFB = EMCONFRONT_TARMASTER;
				SENDTOCLIENT ( dwClientID, &NetMsgFB );
				return FALSE;
			}

			if ( FALSE==pTarParty->ISMASTER(pTarChar->m_dwGaeaID) )
			{
				//	Note : (»ó?EæÀ? ÆÄÆ¼ ¸¶½ºÅÍ°¡ ¾Æ´Õ´Ï´Ù.
				GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
				NetMsgFB.emFB = EMCONFRONT_TARMASTER;
				SENDTOCLIENT ( dwClientID, &NetMsgFB );
				return FALSE;
			}

			//	Note : ?E?¿ÀÃ»ÇÑ Á¤º¸ Àú?E
			//
			pMyChar->m_sREQCONFTING.RESET();
			pMyChar->m_sREQCONFTING.emTYPE = EMCONFT_PARTY;
			pMyChar->m_sREQCONFTING.dwTAR_ID = pTarChar->m_dwGaeaID;
			pMyChar->m_sREQCONFTING.sOption = pNetMsg->sOption;

			//	Note : ?E?(»ó?Eæ¿¡°? ¿äÃ».
			//
			GLMSG::SNETPC_REQ_CONFRONT_TAR NetMsgTAR;
			NetMsgTAR.emTYPE = EMCONFT_PARTY;
			NetMsgTAR.dwID = dwGaeaID;	// ÀÚ½ÅÀÇ ID.
			NetMsgTAR.sOption = pNetMsg->sOption;
			SENDTOCLIENT ( pTarChar->m_dwClientID, &NetMsgTAR );

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
			if( pMyChar->m_bTracingUser )
			{
				CDebugSet::ToTracingFile( pMyChar->m_szUserName, "Confront2 Request, [%s][%s], Target Char: [%s][%s]",
										  pMyChar->m_szUserName, pMyChar->m_szName, pTarChar->m_szUserName, pTarChar->m_szName );
			}
#endif
		}
		break;

	case EMCONFT_GUILD:
		{
			DWORD dwMyClubID = pMyChar->m_dwGuild;
			DWORD dwTarClubID = pTarChar->m_dwGuild;

			if ( dwTarClubID==CLUB_NULL )
			{
				//	Note : Å¬·´ ¸¶½ºÅÍ°¡ ¾Æ´Õ´Ï´Ù.
				GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
				NetMsgFB.emFB = EMCONFRONT_FAIL;
				SENDTOCLIENT ( dwClientID, &NetMsgFB );
				return FALSE;
			}

			GLCLUB *pTarClub = m_cClubMan.GetClub ( dwTarClubID );
			if ( !pTarClub || pTarClub->m_dwMasterID!=pTarChar->m_dwCharID )
			{
				//	Note : Å¬·´ ¸¶½ºÅÍ°¡ ¾Æ´Õ´Ï´Ù.
				GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
				NetMsgFB.emFB = EMCONFRONT_FAIL;
				SENDTOCLIENT ( dwClientID, &NetMsgFB );
				return FALSE;
			}

			if ( dwMyClubID==CLUB_NULL )
			{
				//	Note : Å¬·´ ¸¶½ºÅÍ°¡ ¾Æ´Õ´Ï´Ù.
				GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
				NetMsgFB.emFB = EMCONFRONT_FAIL;
				SENDTOCLIENT ( dwClientID, &NetMsgFB );
				return FALSE;
			}

			GLCLUB *pMyClub = m_cClubMan.GetClub ( dwMyClubID );
			if ( !pMyClub || pMyClub->m_dwMasterID!=pMyChar->m_dwCharID )
			{
				//	Note : Å¬·´ ¸¶½ºÅÍ°¡ ¾Æ´Õ´Ï´Ù.
				GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
				NetMsgFB.emFB = EMCONFRONT_FAIL;
				SENDTOCLIENT ( dwClientID, &NetMsgFB );
				return FALSE;
			}

			//	Note : ?E?¿ÀÃ»ÇÑ Á¤º¸ Àú?E
			//
			pMyChar->m_sREQCONFTING.RESET();
			pMyChar->m_sREQCONFTING.emTYPE = EMCONFT_GUILD;
			pMyChar->m_sREQCONFTING.dwTAR_ID = pTarChar->m_dwGaeaID;
			pMyChar->m_sREQCONFTING.sOption = pNetMsg->sOption;

			//	Note : ?E?(»ó?Eæ¿¡°? ¿äÃ».
			//
			GLMSG::SNETPC_REQ_CONFRONT_TAR NetMsgTAR;
			NetMsgTAR.emTYPE = EMCONFT_GUILD;
			NetMsgTAR.dwID = dwGaeaID;	// ÀÚ½ÅÀÇ ID.
			NetMsgTAR.sOption = pNetMsg->sOption;
			SENDTOCLIENT ( pTarChar->m_dwClientID, &NetMsgTAR );

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
			if( pMyChar->m_bTracingUser )
			{
				CDebugSet::ToTracingFile( pMyChar->m_szUserName, "Confront3 Request, [%s][%s], Target Char: [%s][%s]",
										  pMyChar->m_szUserName, pMyChar->m_szName, pTarChar->m_szUserName, pTarChar->m_szName );
			}
#endif
		}
		break;
	};

	return TRUE;
}

BOOL GLAgentServer::MsgAnsConfront ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETPC_REQ_CONFRONT_ANS *pNetMsg = (GLMSG::SNETPC_REQ_CONFRONT_ANS *) nmg;

	// Absolute Non-PK State Check. ?E?¾ÈµÊ.
	if ( GLCONST_CHAR::bPKLESS ) return FALSE;

	if ( pNetMsg->emFB == EMCONFRONT_REFUSE )
	{
		PGLCHARAG pReqChar = GetChar ( pNetMsg->dwID );
		if ( !pReqChar )	return FALSE;

		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emTYPE = pNetMsg->emTYPE;
		NetMsgFB.dwID = dwGaeaID;
		NetMsgFB.emFB = EMCONFRONT_REFUSE;

		SENDTOCLIENT ( pReqChar->m_dwClientID, &NetMsgFB );
	}
	/*else if ( pNetMsg->emFB == EMCONFRONT_NO_BET ) // add duel bet
	{
		PGLCHARAG pReqChar = GetChar ( pNetMsg->dwID );
		if ( !pReqChar )	return FALSE;

		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emTYPE = pNetMsg->emTYPE;
		NetMsgFB.dwID = dwGaeaID;
		NetMsgFB.emFB = EMCONFRONT_NO_BET;

		SENDTOCLIENT ( pReqChar->m_dwClientID, &NetMsgFB );
	}
	else if ( pNetMsg->emFB == EMCONFRONT_CANT_BET_MONEY )
	{
		PGLCHARAG pReqChar = GetChar ( pNetMsg->dwID );
		if ( !pReqChar )	return FALSE;

		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emTYPE = pNetMsg->emTYPE;
		NetMsgFB.dwID = dwGaeaID;
		NetMsgFB.emFB = EMCONFRONT_CANT_BET_MONEY;

		SENDTOCLIENT ( pReqChar->m_dwClientID, &NetMsgFB );
	}
	else if ( pNetMsg->emFB == EMCONFRONT_CANT_BET )
	{
		PGLCHARAG pReqChar = GetChar ( pNetMsg->dwID );
		if ( !pReqChar )	return FALSE;

		GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
		NetMsgFB.emTYPE = pNetMsg->emTYPE;
		NetMsgFB.dwID = dwGaeaID;
		NetMsgFB.emFB = EMCONFRONT_CANT_BET;

		SENDTOCLIENT ( pReqChar->m_dwClientID, &NetMsgFB );
	}*/
	else if ( pNetMsg->emFB == EMCONFRONT_AGREE )
	{
		//	?E?±âº» Á¤º¸.
		const EMCONFT_TYPE emTYPE = pNetMsg->emTYPE;
		const DWORD dwMY_ID = dwGaeaID;
		const DWORD dwREQ_ID = pNetMsg->dwID;
		const SCONFT_OPTION _sOption = pNetMsg->sOption;

		//	?E?»ó?EEID ?E
		const DWORD dwMY_TAR = dwREQ_ID;
		const DWORD dwREQ_TAR = dwMY_ID;

		PGLCHARAG pMyChar = GetChar ( dwMY_ID );
		if ( !pMyChar )		return FALSE;

		PGLCHARAG pReqChar = GetChar ( dwREQ_ID );
		if ( !pReqChar )	return FALSE;

		const SCONFTING& sMY_CONFTING = pMyChar->GETCONFRONTING();
		const SCONFTING& sREQ_CONFTING = pReqChar->GETCONFRONTING();

		if ( sMY_CONFTING.IsCONFRONTING() || sREQ_CONFTING.IsCONFRONTING() )
			return FALSE;

		//	Note : ?E?Á¶°Ç ¹«°á¼º °Ë?E
		//
		if ( emTYPE != pReqChar->m_sREQCONFTING.emTYPE )			return FALSE;
		if ( dwREQ_TAR != pReqChar->m_sREQCONFTING.dwTAR_ID )		return FALSE;
		if ( _sOption != pReqChar->m_sREQCONFTING.sOption )			return FALSE;

#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM) // ***Tracing Log print
		if( pMyChar->m_bTracingUser )
		{
			CDebugSet::ToTracingFile( pMyChar->m_szUserName, "Confront Answer OK, [%s][%s], Request Char: [%s][%s]",
									  pMyChar->m_szUserName, pMyChar->m_szName, pReqChar->m_szUserName, pReqChar->m_szName );
		}
#endif

		//	Note : ?E?½ÃÀÛ.
		//
		switch ( emTYPE )
		{
		case EMCONFT_ONE:
			{
				SCONFT_OPTION sREQOption = _sOption;		//	A ( ¿äÃ»ÀÚ )
				SCONFT_OPTION sMYOption = _sOption;			//	B ( ¼ö¶ôÀÚ )
				sMYOption.fHP_RATE = _sOption.fTAR_HP_RATE;	//	( ¼ö¶ôÀÚ ) ´Â Ã¼·Â Áõ°¡À² ´Ù¸£°³ °¡?E

				pMyChar->StartConfront ( emTYPE, dwMY_TAR, sMYOption );
				pReqChar->StartConfront ( emTYPE, dwREQ_TAR, sREQOption );
			}
			break;

		case EMCONFT_PARTY:
			{
				bool bmyparty(false), breqparty(false);
				DWORD dwMyPartyID = pMyChar->GetPartyID();
				DWORD dwReqPartyID = pReqChar->GetPartyID();
			
				if ( dwMyPartyID!=GAEAID_NULL )
				{
					GLPARTY *pMyParty = m_cPartyMan.GetParty(dwMyPartyID);
					if ( pMyParty && pMyParty->ISMASTER(pMyChar->m_dwGaeaID) )
					{
						bmyparty = true;
					}
				}
				
				if ( dwReqPartyID!=GAEAID_NULL )
				{
					GLPARTY *pReqParty = m_cPartyMan.GetParty(dwReqPartyID);
					if ( pReqParty && pReqParty->ISMASTER(pReqChar->m_dwGaeaID) )
					{
						breqparty = true;
					}
				}

				//	Note : ÆÄÆ¼ À¯È¿ÇÒ¶§ ?E?½ÃÀÛµÊ.
				//
				if ( bmyparty && breqparty )
				{
					//	Note : ?EÃ½ÃÀÛÀE?E?¸â?EÃ¼Å©.
					//
					GLMSG::SNETPC_CONFRONTPTY_CHECKMBR2_FLD NetMsgCheck;
					NetMsgCheck.sMapID = pReqChar->m_sCurMapID;
					NetMsgCheck.dwPARTY_A = dwReqPartyID;
					NetMsgCheck.dwPARTY_B = dwMyPartyID;
					NetMsgCheck.sOption = _sOption;

					SENDTOFIELDSVR ( pMyChar->m_nChannel, pMyChar->m_dwCurFieldSvr, &NetMsgCheck );
				}
				else
				{
					//	Note : ÆÄÆ¼°¡ ¾Æ´Ï¿©¼­ ?E?ºÒ°¡´É.
					//
					GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
					NetMsgFB.emTYPE = emTYPE;
					NetMsgFB.dwID = dwGaeaID;
					NetMsgFB.emFB = EMCONFRONT_FAIL;
					
					SENDTOCLIENT ( pMyChar->m_dwClientID, &NetMsgFB );
					SENDTOCLIENT ( pReqChar->m_dwClientID, &NetMsgFB );
				}
			}
			break;

		case EMCONFT_GUILD:
			{
				bool bmyclub(false), breqclub(false);
				DWORD dwMyClubID = pMyChar->m_dwGuild;
				DWORD dwReqClubID = pReqChar->m_dwGuild;
			
				if ( dwMyClubID!=CLUB_NULL )
				{
					GLCLUB *pCLUB = m_cClubMan.GetClub ( dwMyClubID );
					if ( pCLUB && pCLUB->m_dwMasterID==pMyChar->m_dwCharID )
					{
						bmyclub = true;
					}
				}
				
				if ( dwReqClubID!=GAEAID_NULL )
				{
					GLCLUB *pCLUB = m_cClubMan.GetClub ( dwReqClubID );
					if ( pCLUB && pCLUB->m_dwMasterID==pReqChar->m_dwCharID )
					{
						breqclub = true;
					}
				}

				//	Note : Å¬·´ À¯È¿ÇÒ¶§ ?E?½ÃÀÛµÊ.
				//
				if ( bmyclub && breqclub )
				{
					//	Note : ?EÃ½ÃÀÛÀE?E?¸â?EÃ¼Å©.
					//
					GLMSG::SNET_CONFRONTCLB_CHECKMBR_FLD NetMsgCheck;
					NetMsgCheck.sMapID = pReqChar->m_sCurMapID;
					NetMsgCheck.dwCLUB_A = dwReqClubID;
					NetMsgCheck.dwCLUB_B = dwMyClubID;
					NetMsgCheck.sOption = _sOption;

					SENDTOFIELDSVR ( pMyChar->m_nChannel, pMyChar->m_dwCurFieldSvr, &NetMsgCheck );
				}
				else
				{
					//	Note : Å¬·´ÀÌ ¾Æ´Ï¿©¼­ ?E?ºÒ°¡´É.
					//
					GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
					NetMsgFB.emTYPE = emTYPE;
					NetMsgFB.dwID = dwGaeaID;
					NetMsgFB.emFB = EMCONFRONT_FAIL;
					
					SENDTOCLIENT ( pMyChar->m_dwClientID, &NetMsgFB );
					SENDTOCLIENT ( pReqChar->m_dwClientID, &NetMsgFB );
				}
			}
			break;
		};
	}

	return TRUE;
}

BOOL GLAgentServer::MsgConfrontPtyCheckMber ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_CONFRONTPTY_CHECKMBR2_AGT *pNetMsg = (GLMSG::SNETPC_CONFRONTPTY_CHECKMBR2_AGT *) nmg;
	
	StartPartyConfront ( pNetMsg->dwPARTY_A, pNetMsg->dwPARTY_B, pNetMsg->sMapID, pNetMsg->sOption,
		pNetMsg->dwPARTY_A_MEMBER, pNetMsg->dwPARTY_B_MEMBER, pNetMsg->vPosition );

	return TRUE;
}

BOOL GLAgentServer::MsgConfrontClbCheckMber ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_CONFRONTCLB_CHECKMBR_AGT *pNetMsg = (GLMSG::SNET_CONFRONTCLB_CHECKMBR_AGT *) nmg;
	
	GLCLUB *pClubA = m_cClubMan.GetClub(pNetMsg->dwCLUB_A);
	GLCLUB *pClubB = m_cClubMan.GetClub(pNetMsg->dwCLUB_B);
	if ( !pClubA || !pClubB )		return FALSE;

	CLUBCONFT_ITER pos, end;

	SCONFT_OPTION sOPT_A = pNetMsg->sOption;
	SCONFT_OPTION sOPT_B = pNetMsg->sOption;

	DWORD i(0);

	//	Note : A ÆÀ 'Å¬·´?E? ÃÊ±âÈ­.
	//
	pClubA->CLEARCONFT();

	for ( i=0; i<pNetMsg->dwCLUB_A_NUM; ++i )
	{
		DWORD dwMBR = pNetMsg->dwCLUB_A_MEMBER[i];

		PGLCHARAG pChar = GetCharID ( dwMBR );
		if ( !pChar )									continue;
		if ( pChar->m_sCurMapID != pNetMsg->sMapID )	continue;

		//	Note :Å¬·´¿øÀÇ ?EÃÁ¤º?¼³Á¤.
		//
		pChar->m_sCONFTING.RESET();
		pChar->m_sCONFTING.emTYPE = EMCONFT_GUILD;
		pChar->m_sCONFTING.dwTAR_ID = pNetMsg->dwCLUB_B;
		pChar->m_sCONFTING.sOption = sOPT_A;

		pClubA->ADDCONFT_MEMBER ( dwMBR );
	}

	if ( pClubA->GETCONFT_NUM()==0 )			return FALSE;
	
	//	Note : B ÆÀ 'Å¬·´?E? ÃÊ±âÈ­.
	//
	pClubB->CLEARCONFT();

	for ( i=0; i<pNetMsg->dwCLUB_B_NUM; ++i )
	{
		DWORD dwMBR = pNetMsg->dwCLUB_B_MEMBER[i];

		PGLCHARAG pChar = GetCharID ( dwMBR );
		if ( !pChar )									continue;
		if ( pChar->m_sCurMapID != pNetMsg->sMapID )	continue;

		//	Note : Å¬·´¿øÀÇ ?EÃÁ¤º?¼³Á¤.
		//
		pChar->m_sCONFTING.RESET();
		pChar->m_sCONFTING.emTYPE = EMCONFT_GUILD;
		pChar->m_sCONFTING.dwTAR_ID = pNetMsg->dwCLUB_A;
		pChar->m_sCONFTING.sOption = sOPT_B;

		pClubB->ADDCONFT_MEMBER ( dwMBR );
	}

	if ( pClubB->GETCONFT_NUM()==0 )		return FALSE;

	//	Note : Å¬·´?E?Á¤º¸ ÃÊ±âÈ­.
	//
	pClubA->m_conftOPT = sOPT_A;
	pClubA->m_dwconftCLUB = pNetMsg->dwCLUB_B;
	pClubA->m_fconftTIMER = 0.0f;
	pClubA->SETCONFT_MEMBER();

	pClubB->m_conftOPT = sOPT_B;
	pClubB->m_dwconftCLUB = pNetMsg->dwCLUB_A;
	pClubB->m_fconftTIMER = 0.0f;
	pClubB->SETCONFT_MEMBER();

	//	Note : ÇÊµå¿¡ ?E?ÃÊ±âÈ­ ¸Þ½Ã?E
	//		¸Þ½ÃÁö¿¡ ?EÛµ?my, tar school Àº »ç?EÇÁE¾Ê´Â´Ù.
	GLMSG::SNETPC_CONFRONTCLB_START2_FLD NetMsgFld;
	NetMsgFld.sMapID = pNetMsg->sMapID;
	NetMsgFld.dwCLUB_A= pNetMsg->dwCLUB_A;
	NetMsgFld.dwCLUB_B= pNetMsg->dwCLUB_B;
	NetMsgFld.sOption = sOPT_A;
	NetMsgFld.vPos = pNetMsg->vPosition;

	pos = pClubA->m_setConftCURRENT.begin();
	end = pClubA->m_setConftCURRENT.end();
	for ( ; pos!=end; ++pos )
	{
		NetMsgFld.dwCLUB_A_MEMBER[NetMsgFld.dwCLUB_A_NUM++] = (*pos);
	}

	pos = pClubB->m_setConftCURRENT.begin();
	end = pClubB->m_setConftCURRENT.end();
	for ( ; pos!=end; ++pos )
	{
		NetMsgFld.dwCLUB_B_MEMBER[NetMsgFld.dwCLUB_B_NUM++] = (*pos);
	}

	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}

BOOL GLAgentServer::MsgAnsConfrontFB ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETPC_REQ_CONFRONT_FB *pNetMsg = (GLMSG::SNETPC_REQ_CONFRONT_FB *)nmg;

	switch ( pNetMsg->emTYPE )
	{
	case EMCONFT_ONE:
		{
			PGLCHARAG pCHAR = GetChar(pNetMsg->dwID);
			if ( pCHAR->m_sCONFTING.IsCONFRONTING() )
			{
				PGLCHARAG pTAR = GetChar(pCHAR->m_sCONFTING.dwTAR_ID);
				if ( pTAR )
				{
					pTAR->m_sCONFTING.RESET();

					// Note : Å¬¶óÀÌ¾ðÆ®¿¡ ?E?¿À?E¼Û½Å.
					if( pNetMsg->emFB == EMCONFRONT_FAIL )
						SENDTOCLIENT(pTAR->m_dwClientID,pNetMsg);
				}
			}

			pCHAR->m_sCONFTING.RESET();

			//	Note : Å¬¶óÀÌ¾ðÆ®¿¡ ?E?¿À?E¼Û½Å.
			SENDTOCLIENT(pCHAR->m_dwClientID,pNetMsg);
		}
		break;

	case EMCONFT_PARTY:
		{
			m_cPartyMan.ConfrontFB ( (NET_MSG_GENERIC*) pNetMsg );
		}
		break;

	case EMCONFT_GUILD:
		{
			GLCLUB *pCLUB = m_cClubMan.GetClub ( pNetMsg->dwID );
			if ( pCLUB )
			{
				pCLUB->CLEARCONFT();

				CLUBMEMBERS_ITER pos = pCLUB->m_mapMembers.begin();
				CLUBMEMBERS_ITER end = pCLUB->m_mapMembers.end();
				for ( ; pos!=end; ++pos )
				{
					PGLCHARAG pCHAR = GetCharID((*pos).first);
					if ( !pCHAR )	continue;

					pCHAR->m_sCONFTING.RESET ();

					//	Note : Å¬¶óÀÌ¾ðÆ®¿¡ ?E?¿À?E¼Û½Å.
					//
					GLMSG::SNETPC_REQ_CONFRONT_FB NetMsgFB;
					NetMsgFB.emFB = pNetMsg->emFB;
					SENDTOCLIENT(pCHAR->m_dwClientID,&NetMsgFB);
				}
			}
		}
		break;
	};

	return TRUE;
}

BOOL GLAgentServer::MsgConfrontEnd2Agt ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETPC_CONFRONT_END2_AGT *pNetMsg = (GLMSG::SNETPC_CONFRONT_END2_AGT *)nmg;
	
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )					return FALSE;

	const SCONFTING &sCONFT = pMyChar->GETCONFRONTING();

	switch ( sCONFT.emTYPE )
	{
	case EMCONFT_ONE:
		{
			DWORD dwTAR_ID = sCONFT.dwTAR_ID;
			pMyChar->ResetConfrontOk ();

			PGLCHARAG pTarChar = GetChar ( dwTAR_ID );
			if ( !pTarChar )		return TRUE;
			pTarChar->ResetConfrontOk ();
		}
		break;

	case EMCONFT_PARTY:
		{
			pMyChar->ResetConfrontOk();

			GLPARTY *pParty = GetParty ( pMyChar->GetPartyID() );
			if ( !pParty )			return FALSE;
				
			pParty->DELCONFT_MEMBER ( pMyChar->m_dwGaeaID );
		}
		break;

	case EMCONFT_GUILD:
		{
			pMyChar->ResetConfrontOk();

			GLCLUB *pCLUB = m_cClubMan.GetClub ( pMyChar->m_dwGuild );
			if ( !pCLUB )			return FALSE;

			pCLUB->DELCONFT_MEMBER ( pMyChar->m_dwCharID );
		}
		break;
	};

	return TRUE;
}

BOOL GLAgentServer::MsgServerCtrlWeather ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM3 )	return FALSE;

	SENDTOALLCHANNEL ( nmg );

	return TRUE;
}

BOOL GLAgentServer::MsgServerCtrlGenHold ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	SENDTOALLCHANNEL ( nmg );

	return TRUE;
}

BOOL GLAgentServer::MsgServerCtrlTime ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNETSERVER_CTRL_TIME *pNetMsg = (GLMSG::SNETSERVER_CTRL_TIME *)nmg;
	GLPeriod::GetInstance().SetHour ( pNetMsg->dwTime );

	SENDTOALLCHANNEL ( pNetMsg );

	return TRUE;
}

BOOL GLAgentServer::MsgServerCtrlMonth ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNETSERVER_CTRL_MONTH *pNetMsg = (GLMSG::SNETSERVER_CTRL_MONTH *)nmg;

	//GLPeriod::GetInstance();

	return TRUE;
}

BOOL GLAgentServer::MsgBlockDetected ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;

	GLMSG::SNET_BLOCK_DETECTED *pNetMsg = (GLMSG::SNET_BLOCK_DETECTED*) nmg;
	if ( pMyChar->m_dwCharID == pNetMsg->dwCHARID )
	{
		std::string strTIME = CDebugSet::GetCurTime ();
		CDebugSet::ToFile ( "block_detected.txt", "%s	userid= %s (%d), charid= %s (%d), detect=%d, %s",
			strTIME.c_str(),
			pMyChar->m_szUserName,
			pMyChar->m_dwUserID, pMyChar->m_szName, pMyChar->m_dwCharID, pNetMsg->dwDETECTED, pNetMsg->szINFO );

		CLogHackProgram *pDbAction = new CLogHackProgram(
											pMyChar->m_dwUserID,
											pMyChar->m_dwCharID,
											(int) pNetMsg->dwDETECTED,
											pNetMsg->szINFO );
		GLDBMan *pDbMan = GLAgentServer::GetInstance().GetDBMan();
		if ( pDbMan )	pDbMan->AddJob ( pDbAction );
	}

	return TRUE;
}

// *****************************************************
// Desc: ÄÉ¸¯ÅÍ °­Á¦ Á¢¼Ó Á¾?E¿äÃ» Ã³¸®
// *****************************************************
BOOL GLAgentServer::MsgGmKickUser ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM3 )	return FALSE;

	GLMSG::SNET_GM_KICK_USER *pNetMsg = (GLMSG::SNET_GM_KICK_USER*) nmg;

	if ( pNetMsg->bName )
	{
		PGLCHARAG pTarChar = GetChar ( pNetMsg->szNAME );
		if ( !pTarChar )	return FALSE;

		GLMSG::SNET_GM_KICK_USER_PROC_FLD NetMsgFld;
		NetMsgFld.dwID = pTarChar->m_dwCharID;
		SENDTOALLCHANNEL ( &NetMsgFld );

		GLMSG::SNET_GM_KICK_USER_PROC NetMsgProc;
		SENDTOCLIENT ( pTarChar->m_dwClientID, &NetMsgProc );

		ReserveDropOutPC ( pTarChar->m_dwGaeaID );
	}
	else
	{
		PGLCHARAG pTarChar = GetCharID ( pNetMsg->dwID );
		if ( !pTarChar )	return FALSE;

		GLMSG::SNET_GM_KICK_USER_PROC_FLD NetMsgFld;
		NetMsgFld.dwID = pNetMsg->dwID;
		SENDTOALLCHANNEL ( &NetMsgFld );

		GLMSG::SNET_GM_KICK_USER_PROC NetMsgProc;
		SENDTOCLIENT ( pTarChar->m_dwClientID, &NetMsgProc );

		ReserveDropOutPC ( pTarChar->m_dwGaeaID );

	}
	return TRUE;
}

BOOL GLAgentServer::MsgGMMove2Gate ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pCHAR = GetChar ( dwGaeaID );
	if ( !pCHAR )						 return FALSE;
	if ( pCHAR->m_dwUserLvl < USER_GM3 ) return FALSE;

	GLMSG::SNET_GM_MOVE2GATE* pNetMsg = (GLMSG::SNET_GM_MOVE2GATE*) nmg;

	GLMSG::SNET_GM_MOVE2GATE_FLD NetMsgFld;
	NetMsgFld.dwGATE   = pNetMsg->dwGATE;
	NetMsgFld.dwGaeaID = dwGaeaID;
	
	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}

// *****************************************************
// Desc: Æ¯Á¤¸ÊÀÇ Æ¯Á¤À§Ä¡¿¡ ÀÌµ¿ ¿äÃ» Ã³¸®
// *****************************************************
BOOL GLAgentServer::MsgGMMove2Pos ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pCHAR = GetChar ( dwGaeaID );
	if ( !pCHAR )						 return FALSE;
	//if ( pCHAR->m_dwUserLvl < USER_GM3 ) return FALSE;

	GLMSG::SNET_GM_MOVE2MAPPOS* pNetMsg = (GLMSG::SNET_GM_MOVE2MAPPOS*) nmg;

	GLMSG::SNET_GM_MOVE2MAPPOS_FLD NetMsgFld;
	NetMsgFld.nidMAP   = pNetMsg->nidMAP;
	NetMsgFld.dwGaeaID = dwGaeaID;
	NetMsgFld.dwPOSX   = pNetMsg->dwPOSX;
	NetMsgFld.dwPOSY   = pNetMsg->dwPOSY;
	
	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}

BOOL GLAgentServer::MsgServerGeneralChat ( NET_MSG_GENERIC* nmg )
{
	SENDTOALLCLIENT ( nmg );

	return TRUE;
}

BOOL GLAgentServer::ChatMsgLoudSpeakerAgt ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETPC_CHAT_LOUDSPEAKER_AGT *pNetMsg = (GLMSG::SNETPC_CHAT_LOUDSPEAKER_AGT *) nmg;
	
	PGLCHARAG pChar = GetChar ( dwGaeaID );
	if ( !pChar )							return FALSE;
	if ( pChar->IsCHATBLOCK() )				return FALSE;

	NET_CHAT_FB NetMsgFB;
	NetMsgFB.emType = CHAT_TYPE_LOUDSPEAKER;
	NetMsgFB.sITEMLINK = pNetMsg->sITEMLINK;
	StringCchCopy ( NetMsgFB.szName, CHAR_SZNAME, pChar->m_szName );
	StringCchCopy ( NetMsgFB.szChatMsg, CHAT_MSG_SIZE, pNetMsg->szMSG );

	if ( pNetMsg->bchannel_all )	SENDTOALLCLIENT ( &NetMsgFB );
	else							SENDTOALLCLIENT ( &NetMsgFB, pChar->m_nChannel );

	return TRUE;
}

BOOL GLAgentServer::MsgClubNew2Agt ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_CLUB_NEW_2AGT *pNetMsg = (GLMSG::SNET_CLUB_NEW_2AGT *) nmg;

	PGLCHARAG pChar = GetChar ( dwGaeaID );
	if ( !pChar )		return FALSE;

	GLMSG::SNET_CLUB_NEW_FB NetMsgFB;
	NetMsgFB.emFB = EMCLUB_NEW_FB_FAIL;
	StringCchCopy ( NetMsgFB.szClubName, CHAR_SZNAME, pNetMsg->szClubName );

	if ( pChar->m_dwGuild!=CLUB_NULL )
	{
		NetMsgFB.emFB = EMCLUB_NEW_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	GLPARTY *pPARTY = m_cPartyMan.GetParty ( pChar->m_dwPartyID );
	if ( !pPARTY || !pPARTY->ISMASTER(pChar->m_dwGaeaID) )
	{
		NetMsgFB.emFB = EMCLUB_NEW_FB_NOTMASTER;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pPARTY->GETNUMBER() < GLCONST_CHAR::dwCLUB_PARTYNUM )
	{
		NetMsgFB.emFB = EMCLUB_NEW_FB_NOTMEMBER;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return S_FALSE;
	}

	GLPARTY::MEMBER_ITER pos = pPARTY->m_cMEMBER.begin();
	GLPARTY::MEMBER_ITER end = pPARTY->m_cMEMBER.end();
	for ( ; pos!=end; ++pos )
	{
		PGLCHARAG pMEMBER = GetChar ( (*pos) );
		if ( !pMEMBER )
		{
			NetMsgFB.emFB = EMCLUB_NEW_FB_NOTEXIST_MEM;
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
			return FALSE;
		}

		if ( pMEMBER->m_dwGuild != CLUB_NULL )
		{
			NetMsgFB.emFB = EMCLUB_NEW_FB_MEM_ALREADY;
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
			return FALSE;
		}
	}

	//	Note : ½ÅÃ»ÇÑ Å¬·´ ÀÌ¸§ÀÌ ÀÌ¹Ì »ç?E?
	//
	DWORD dwOLDGLUB = m_cClubMan.FindClub ( pNetMsg->szClubName );
	if ( dwOLDGLUB!=CLUB_NULL )
	{
		NetMsgFB.emFB = EMCLUB_NEW_FB_NAME;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Note : DB¿¡ µ¥ÀÌÅÍ ¼³Á¤.
	//
	CCreateClub *pDbAction = new CCreateClub ( dwClientID, pNetMsg->szClubName, pChar->m_dwCharID );
	m_pDBMan->AddJob ( pDbAction );

	return TRUE;
}

BOOL GLAgentServer::MsgClubNewDb2Agt ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_CLUB_NEW_DB2AGT *pNetMsg = (GLMSG::SNET_CLUB_NEW_DB2AGT *) nmg;

	PGLCHARAG pChar = GetCharID ( pNetMsg->dwMasterID );
	if ( !pChar )
	{
		//	Note : db¿¡ Å¬·´À» ¸¸µé¾úÀ¸³ª Å¬·´ ¸¶½ºÅÍ°¡ Á¸Á¦ÇÏ?E¾ÊÀ» ¶§´Â Å¬·´À» »èÁ¦ÇÑ´Ù.
		CDeleteClub *pDbAction = new CDeleteClub(pNetMsg->dwClubID,pNetMsg->dwMasterID);
		m_pDBMan->AddJob ( pDbAction );
		return FALSE;
	}

	GLMSG::SNET_CLUB_NEW_FB NetMsgFB;

	if ( pNetMsg->emFB==EMCLUB_NEW_FB_ALREADY )
	{
		NetMsgFB.emFB = EMCLUB_NEW_FB_ALREADY;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pNetMsg->emFB==EMCLUB_NEW_FB_NAME )
	{
		NetMsgFB.emFB = EMCLUB_NEW_FB_NAME;
		StringCchCopy ( NetMsgFB.szClubName, CHAR_SZNAME, pNetMsg->szClubName );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pNetMsg->emFB==EMCLUB_NEW_FB_FAIL )
	{
		NetMsgFB.emFB = EMCLUB_NEW_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	NetMsgFB.emFB = EMCLUB_NEW_FB_FAIL;
	StringCchCopy ( NetMsgFB.szClubName, CHAR_SZNAME, pNetMsg->szClubName );

	GLPARTY *pPARTY = m_cPartyMan.GetParty ( pChar->m_dwPartyID );
	if ( !pPARTY || !pPARTY->ISMASTER(pChar->m_dwGaeaID) )
	{
		NetMsgFB.emFB = EMCLUB_NEW_FB_NOTMASTER;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );

		CDeleteClub *pDbAction = new CDeleteClub(pNetMsg->dwClubID,pNetMsg->dwMasterID);
		m_pDBMan->AddJob ( pDbAction );

		return FALSE;
	}

	if ( pPARTY->GETNUMBER() < GLCONST_CHAR::dwCLUB_PARTYNUM )
	{
		NetMsgFB.emFB = EMCLUB_NEW_FB_NOTMEMBER;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );

		CDeleteClub *pDbAction = new CDeleteClub(pNetMsg->dwClubID,pNetMsg->dwMasterID);
		m_pDBMan->AddJob ( pDbAction );

		return S_FALSE;
	}

	//	Note : Å¬·´ ¼³Á¤.
	//
	GLCLUB cClubNew;
	cClubNew.m_dwID = pNetMsg->dwClubID;
	StringCchCopy(cClubNew.m_szName,CHAR_SZNAME,pNetMsg->szClubName);
	
	CTime cTIME_CUR = CTime::GetCurrentTime();
	cClubNew.m_tOrganize = cTIME_CUR.GetTime();

	cClubNew.m_dwMasterID = pChar->m_dwCharID;
	StringCchCopy(cClubNew.m_szMasterName,CHAR_SZNAME,pChar->m_szName);

	//	Note : ÄÉ¸¯ÅÍ °³Ã¼¿¡ Å¬·´ ID ÁöÁ¤.
	//pChar->m_dwGuild = cClubNew.m_dwID;

	CTime cTIME_DIS(1970,2,1,1,1,1);
	cClubNew.m_tDissolution = cTIME_DIS.GetTime();

	//	Note : ¸â¹ö?EµûÓÏ.
	{
		GLPARTY::MEMBER_ITER pos = pPARTY->m_cMEMBER.begin();
		GLPARTY::MEMBER_ITER end = pPARTY->m_cMEMBER.end();
		for ( ; pos!=end; ++pos )
		{
			PGLCHARAG pMEMBER = GetChar ( (*pos) );
			if ( !pMEMBER )								continue;
			if ( pMEMBER->m_dwGuild != CLUB_NULL )		continue;

			//	Note : ÄÉ¸¯ÅÍ °³Ã¼¿¡ Å¬·´ ID ÁöÁ¤.
			pMEMBER->m_dwGuild = cClubNew.m_dwID;

			GLCLUBMEMBER cMEMBER;
			cMEMBER.dwID = pMEMBER->m_dwCharID;
			StringCchCopy ( cMEMBER.m_szName, CHAR_SZNAME, pMEMBER->m_szName );

			cClubNew.m_mapMembers.insert ( std::make_pair(cMEMBER.dwID,cMEMBER) );

			//	Note : DB¿¡ ¸â?E¼³Á¤.
			//
			CAddClubMember *pDbAction = new CAddClubMember ( cClubNew.m_dwID, cMEMBER.dwID );
			m_pDBMan->AddJob ( pDbAction );
		}
	}

	m_cClubMan.AddClub ( cClubNew );

	//	Note : Å¬·´ »ý¼º ¼º?E
	GLMSG::SNET_CLUB_NEW_2FLD NetMsgFLD;
	NetMsgFLD.emFB = EMCLUB_NEW_FB_OK;
	NetMsgFLD.dwCLUBID = cClubNew.m_dwID;
	StringCchCopy ( NetMsgFLD.szClubName, CHAR_SZNAME, cClubNew.m_szName );
	SENDTOFIELD ( dwClientID, &NetMsgFLD );

	//	Note : »ý¼º Á¤º¸ ?E?
	//
	GLMSG::SNET_CLUB_INFO_2FLD NetMsgInfo;
	NetMsgInfo.dwClubID = cClubNew.m_dwID;
	StringCchCopy ( NetMsgInfo.szClubName, CHAR_SZNAME, cClubNew.m_szName );

	NetMsgInfo.dwMasterID = cClubNew.m_dwMasterID;
	StringCchCopy ( NetMsgInfo.szMasterName, CHAR_SZNAME, cClubNew.m_szMasterName );
	NetMsgInfo.dwCDCertifior = cClubNew.m_dwCDCertifior;

	NetMsgInfo.dwRank = cClubNew.m_dwRank;
	NetMsgInfo.dwMarkVER = cClubNew.m_dwMarkVER;

	NetMsgInfo.tOrganize = cClubNew.m_tOrganize;
	NetMsgInfo.tDissolution = cClubNew.m_tDissolution;

	NetMsgInfo.dwMemberNum = cClubNew.GetNemberNum();
	{
		DWORD i=0;
		CLUBMEMBERS_ITER pos = cClubNew.m_mapMembers.begin();
		CLUBMEMBERS_ITER end = cClubNew.m_mapMembers.end();
		for ( ; pos!=end; ++pos )
		{
			const GLCLUBMEMBER &sCLUBMEMBER = (*pos).second;

			StringCchCopy ( NetMsgInfo.szMemberName[i], CHAR_SZNAME, sCLUBMEMBER.m_szName );
			NetMsgInfo.aMembers[i] = sCLUBMEMBER.dwID;
			++i;

			//	Note : Å¬·´ °¡ÀÔ ·Î±× ±â·Ï.
			GLITEMLMT::GetInstance().ReqAction
			(
				cClubNew.m_dwMasterID,		//	´ç»çÀÚ.
				EMLOGACT_CLUB_JOIN_MEMBER,	//	ÇàÀ§.
				ID_CHAR, sCLUBMEMBER.dwID,	//	»ó?EE
				0,							//	exp
				0,							//	bright
				0,							//	life
				0							//	money
			);
		}
	}
	SENDTOALLCHANNEL ( &NetMsgInfo );

	return TRUE;
}

BOOL GLAgentServer::MsgClubDissolution ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_CLUB_DISSOLUTION *pNetMsg = (GLMSG::SNET_CLUB_DISSOLUTION *) nmg;

	PGLCHARAG pChar = GetChar ( dwGaeaID );
	if ( !pChar )		return FALSE;

	GLMSG::SNET_CLUB_DISSOLUTION_FB NetMsgFB;

	if ( pChar->m_dwGuild == CLUB_NULL )
	{
		NetMsgFB.emFB = EMCLUB_DIS_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	GLCLUB* pCLUB = m_cClubMan.GetClub ( pChar->m_dwGuild );
	if ( !pCLUB )
	{
		NetMsgFB.emFB = EMCLUB_DIS_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( !pCLUB->IsMaster( pChar->m_dwCharID ) )
	{
		NetMsgFB.emFB = EMCLUB_DIS_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Memo :	µ¿¸Í¿¡ °¡ÀÔµÇ?EÀÖ´Ù?E?E?
	if ( pCLUB->IsAlliance() )
	{
		NetMsgFB.emFB = EMCLUB_DIS_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pCLUB->GetAllBattleNum() > 0 )
	{
		NetMsgFB.emFB = EMCLUB_DIS_FB_CLUBBATTLE;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pNetMsg->bCANCEL )
	{
		if ( !pCLUB->IsRegDissolution() )
		{
			NetMsgFB.emFB = EMCLUB_DIS_FB_FAIL;
			SENDTOCLIENT ( dwClientID, &NetMsgFB );
			return FALSE;
		}

		pCLUB->DoDissolutionCancel ();

		//	Note : DB¿¡ Å¬·´ ÇØ?E½Ã°£ ¼³Á¤.
		CSetClubDissolutionTime *pDbAction = new CSetClubDissolutionTime(pCLUB->m_dwID,pCLUB->m_tDissolution);
		m_pDBMan->AddJob ( pDbAction );

		//	Note : ÇØÃ¼ ?E?to FIELD
		//
		GLMSG::SNET_CLUB_DISSOLUTION_2FLD NetMsgFld;
		NetMsgFld.dwClubID = pCLUB->m_dwID;
		CTime tDisTime(1970,2,1,1,1,1);
		NetMsgFld.tDissolution = tDisTime.GetTime();
		SENDTOALLCHANNEL ( &NetMsgFld );

		//	Note : ÇØÃ¼ ?E?FB
		//
		NetMsgFB.emFB = EMCLUB_DIS_FB_CANCEL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
	}
	else
	{
		//	Note : ÇØÃ¼ ¿¹Á¤ÀÏ ÁöÁ¤.
		CTime tDisTime = CTime::GetCurrentTime();
		CTimeSpan tADD(GLCONST_CHAR::dwCLUB_DISSOLUTION_DAY,0,10,0);
		tDisTime += tADD;

		pCLUB->DoDissolution(tDisTime.GetTime());

		//	Note : DB¿¡ Å¬·´ ÇØ?E½Ã°£ ¼³Á¤.
		CSetClubDissolutionTime *pDbAction = new CSetClubDissolutionTime(pCLUB->m_dwID,pCLUB->m_tDissolution);
		m_pDBMan->AddJob ( pDbAction );

		//	Note : ÇØÃ¼ FB.
		//
		NetMsgFB.emFB = EMCLUB_DIS_FB_OK;
		NetMsgFB.tDissolution = pCLUB->m_tDissolution;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );

		//	Note : ÇØÃ¼ to FIELD
		//
		GLMSG::SNET_CLUB_DISSOLUTION_2FLD NetMsgFld;
		NetMsgFld.dwClubID = pCLUB->m_dwID;
		NetMsgFld.tDissolution = pCLUB->m_tDissolution;
		SENDTOALLCHANNEL ( &NetMsgFld );
	}

	return TRUE;
}
//add sw buff
BOOL GLAgentServer::MsgSwCertified ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_SCHOOL_WARS_CERTIFIED_AGT *pNetMsg = (GLMSG::SNET_SCHOOL_WARS_CERTIFIED_AGT *) nmg;

	bool bOK = GLSchoolWarsAgentMan::GetInstance().ChangeSWSchoolID ( pNetMsg->dwID, pNetMsg->dwSCHOOL );
	if ( !bOK )		return FALSE;

	GLMSG::SNET_SCHOOL_WARS_CERTIFIED_FLD NetMsgFld;
	NetMsgFld.dwID = pNetMsg->dwID;
	NetMsgFld.dwSCHOOL = pNetMsg->dwSCHOOL;
	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}
BOOL GLAgentServer::MsgTowerWarsCertified ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_TOWERWARS_CERTIFIED_AGT *pNetMsg = (GLMSG::SNET_TOWERWARS_CERTIFIED_AGT *) nmg;

	bool bOK = GLTowerWarsAgentMan::GetInstance().ChangeSWSchoolID ( pNetMsg->dwID, pNetMsg->dwSCHOOL );
	if ( !bOK )		return FALSE;

	GLMSG::SNET_TOWERWARS_CERTIFIED_FLD NetMsgFld;
	NetMsgFld.dwID = pNetMsg->dwID;
	NetMsgFld.dwSCHOOL = pNetMsg->dwSCHOOL;
	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}
BOOL GLAgentServer::MsgTowerWarsDoBattleEnd ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_TOWERWARS_DOBATTLEEND_AGT *pNetMsg = (GLMSG::SNET_TOWERWARS_DOBATTLEEND_AGT *) nmg;

	bool bOK = GLTowerWarsAgentMan::GetInstance().EndBattle( pNetMsg->dwID, pNetMsg->dwSCHOOL, pNetMsg->bEnd );
	if ( !bOK )		return FALSE;

	GLMSG::SNET_TOWERWARS_DOBATTLEEND_FLD NetMsgFld;
	NetMsgFld.dwID = pNetMsg->dwID;
	NetMsgFld.dwSCHOOL = pNetMsg->dwSCHOOL;
	NetMsgFld.bEnd = pNetMsg->bEnd;
	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}

/*BOOL GLAgentServer::MsgTowerWarsLastCapture ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_TOWERWARS_LASTCAPTURE_AGT *pNetMsg = (GLMSG::SNET_TOWERWARS_LASTCAPTURE_AGT *) nmg;

	//bool bOK = GLTowerWarsAgentMan::GetInstance().EndBattle( pNetMsg->dwID, pNetMsg->dwSCHOOL, pNetMsg->bEnd );
	//if ( !bOK )		return FALSE;

	GLMSG::SNET_TOWERWARS_LASTCAPTURE_FLD NetMsgFld;
	NetMsgFld.dwID = pNetMsg->dwID;
	NetMsgFld.dwSCHOOL = pNetMsg->dwSCHOOL;
	NetMsgFld.bLastCapture = pNetMsg->bLastCapture;
	SENDTOALLCHANNEL ( &NetMsgFld );

	if ( pNetMsg->bLastCapture )
	{
		CInnerInterface::GetInstance().PrintConsoleTextDlg ( "Captured 2 towers" );
	}

	return TRUE;
}*/

BOOL GLAgentServer::MsgClubCertified ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_CLUB_CERTIFIED_AGT *pNetMsg = (GLMSG::SNET_CLUB_CERTIFIED_AGT *) nmg;

	bool bOK = GLGuidanceAgentMan::GetInstance().ChangeGuidClub ( pNetMsg->dwID, pNetMsg->dwCLUBID );
	if ( !bOK )		return FALSE;

	//	Note : ÇÊµå¼­¹ö¿¡ ¾Ë¸².
	//
	GLMSG::SNET_CLUB_CERTIFIED_FLD NetMsgFld;
	NetMsgFld.dwID = pNetMsg->dwID;
	NetMsgFld.dwCLUBID = pNetMsg->dwCLUBID;
	SENDTOALLCHANNEL ( &NetMsgFld );

	//	Note : Å¬¶óÀÌ¾ðÆ®Æ²¿¡°Ô ¾Ë¸².
	//
	std::string strGuidName, strClubName;
	GLGuidance *pGuid = GLGuidanceAgentMan::GetInstance().Find ( pNetMsg->dwID );
	if ( pGuid )	strGuidName = pGuid->m_strName;

	GLCLUB *pCLUB = m_cClubMan.GetClub ( pNetMsg->dwCLUBID );
	if ( pCLUB )	strClubName = pCLUB->m_szName;

	//	Note : Å¬¶óÀÌ¾ðÆ®¿¡ ¾Ë¸².
	CString strTEXT;
	strTEXT.Format ( ID2SERVERTEXT("EMGUIDCLUB_CERTIFIED"), strClubName.c_str(), strGuidName.c_str() );

	GLMSG::SNET_SERVER_GENERALCHAT NetMsg;
	NetMsg.SETTEXT ( strTEXT.GetString() );
	SENDTOALLCLIENT ( &NetMsg );

	return TRUE;
}

BOOL GLAgentServer::MsgClubIncomeMoney ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_CLUB_INCOME_MONEY_AGT *pNetMsg = (GLMSG::SNET_CLUB_INCOME_MONEY_AGT *) nmg;

	GLCLUB *pCLUB = m_cClubMan.GetClub ( pNetMsg->dwID );
	if ( !pCLUB )		return FALSE;

	if ( pNetMsg->lnMoney < 0 ) return FALSE;

	//	Note : Å¬·´ÀÇ ¼öÀÍÀ» ¹Ý¿µ.
	pCLUB->m_lnIncomeMoney += LONGLONG ( pNetMsg->lnMoney * GLCONST_CHAR::fEARNING_RATE + 0.1f );

	GLITEMLMT::GetInstance().ReqMoneyExc(	ID_CLUB, pNetMsg->dwID, 
											ID_CLUB, pNetMsg->dwID, 
											pNetMsg->lnMoney, 
											EMITEM_ROUTE_CLUBINCOME );

	CDebugSet::ToFile ( "club_income_agent.txt", "{MsgClubIncomeMoney}, ClubID[%u], MoneyFromField[%I64d], IncomeMoney[%I64d]",
						pNetMsg->dwID, pNetMsg->lnMoney, pCLUB->m_lnIncomeMoney );

	//	Note : Db¿¡ Àú?E
	CSetClubIncomeMoney *pDbAction = new CSetClubIncomeMoney ( pCLUB->m_dwID, pCLUB->m_lnIncomeMoney );
	m_pDBMan->AddJob ( pDbAction );

	return TRUE;
}

BOOL GLAgentServer::MsgClubIncomeMoneyUp ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_CLUB_INCOME_UP *pNetMsg = (GLMSG::SNET_CLUB_INCOME_UP *) nmg;

	GLCLUB *pCLUB = m_cClubMan.GetClub ( pNetMsg->dwClubID );
	if ( !pCLUB )		return FALSE;

	//	Note : Å¬·´ÀÇ ¼öÀÍÀ» ¹Ý¿µ.
	if ( pCLUB->m_lnIncomeMoney > 0 )
	{
		GLMSG::SNET_CLUB_INCOME_DN NetMsgDn;
		NetMsgDn.dwClubID = pCLUB->m_dwID;
		NetMsgDn.lnInComeMoney = pCLUB->m_lnIncomeMoney;
		SENDTOALLCHANNEL ( &NetMsgDn );

		pCLUB->m_lnIncomeMoney = 0;

		CDebugSet::ToFile ( "club_income_agent.txt", "{MsgClubIncomeMoneyUp}, ClubID[%u], IncomeMoney[%I64d]",
							pCLUB->m_dwID, NetMsgDn.lnInComeMoney );

		//	Note : Db¿¡ Àú?E
		CSetClubIncomeMoney *pDbAction = new CSetClubIncomeMoney ( pCLUB->m_dwID, pCLUB->m_lnIncomeMoney );
		m_pDBMan->AddJob ( pDbAction );
	}

	return TRUE;
}

// *****************************************************
// Desc: Å¬·´¼öÀÍ¿¡¼­ µ·À» »©°£´Ù incomemoney->storagemoney
// *****************************************************
//BOOL GLAgentServer::MsgClubIncomeMoneyFb ( NET_MSG_GENERIC* nmg )
//{
//	GLMSG::SNET_CLUB_INCOME_FB *pNetMsg = (GLMSG::SNET_CLUB_INCOME_FB *) nmg;
//
//	GLCLUB *pCLUB = m_cClubMan.GetClub ( pNetMsg->dwClubID );
//	if ( !pCLUB )		return FALSE;
//
//	if( pNetMsg->lnInComeMoney <= 0 ) return FALSE;
//
//	// µ·À» ?E¸¹ÀÌ »©°¡·Á±¸ ½ÃµµÇØ¼­ DB¿¡¼­ Overflow »ý?E
//	if ( pCLUB->m_lnIncomeMoney < pNetMsg->lnInComeMoney ) return FALSE;
//
//	//	Note : Å¬·´ÀÇ ¼öÀÍÀÌ ¹Ý¿µµÈµÚ Á¤?E
//	pCLUB->m_lnIncomeMoney -= pNetMsg->lnInComeMoney;
//
//	//m_pConsoleMsg->Write( LOG_CONSOLE, "m_lnIncomeMoney : %d", pCLUB->m_lnIncomeMoney );
//
//	//	Note : Db¿¡ Àú?E
//	CSetClubIncomeMoney *pDbAction = new CSetClubIncomeMoney ( pCLUB->m_dwID, pCLUB->m_lnIncomeMoney );
//	m_pDBMan->AddJob ( pDbAction );
//
//	return TRUE;
//}

BOOL GLAgentServer::MsgClubMemberDb2Del ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_CLUB_MEMBER_DB2DEL *pNetMsg = (GLMSG::SNET_CLUB_MEMBER_DB2DEL *) nmg;

	if ( pNetMsg->dwClub==CLUB_NULL )
	{
		return S_FALSE;
	}

	GLClubMan &sClubMan = GLAgentServer::GetInstance().GetClubMan();
	GLCLUB *pCLUB = sClubMan.GetClub ( pNetMsg->dwClub );
	if ( !pCLUB )
	{
		return S_FALSE;
	}

	if ( pCLUB->m_dwMasterID==pNetMsg->dwMember )
	{
		return S_FALSE;
	}

	bool bFOUND = pCLUB->IsMember ( pNetMsg->dwMember );
	if ( !bFOUND )
	{
		return S_FALSE;
	}

	//	Note : Å¬·´ ¸É?EÅ»?E·Î±× ±â·Ï.
	GLITEMLMT::GetInstance().ReqAction
	(
		pCLUB->m_dwMasterID,		//	´ç»çÀÚ.
		EMLOGACT_CLUB_SECEDE_MEMBER,//	ÇàÀ§.
		ID_CHAR, pNetMsg->dwMember,	//	»ó?EE
		0,							//	exp
		0,							//	bright
		0,							//	life
		0							//	money
	);

	//	Note : DB¿¡¼­ »èÁ¦.
	CDeleteClubMember *pDbAction = new CDeleteClubMember(pNetMsg->dwMember);
	GLAgentServer::GetInstance().GetDBMan()->AddJob ( pDbAction );

	//	Note : Á¾?EÀÎ?E±ÇÇÑÀÚ ¹é?E
	DWORD dwCD_OLD = pCLUB->m_dwCDCertifior;

	//	CDM ±ÇÇÑ ÀÖÀ»°æ?EÁ¦°Å
	pCLUB->SetMemberCDMFlag( pNetMsg->dwMember, FALSE );

	//	Note : Å¬·´ ¸ñ·Ï¿¡¼­ Á¦°Å.
	pCLUB->DelMember ( pNetMsg->dwMember );

	//	Note : ¼±µµÅ¬·´ ÀÎÁõÀÚ º¯°æ½Ã.
	if ( dwCD_OLD!=pCLUB->m_dwCDCertifior )
	{
		//	Note : ¼­¹ö¿¡ ÀÎ?E±ÇÇÑÀÚ Àú?E
		CDbAction *pDbAction = new CSetClubDeputy ( pCLUB->m_dwID, pCLUB->m_dwCDCertifior );
		GLDBMan* pDbMan = GLAgentServer::GetInstance().GetDBMan();
		if ( pDbMan )	pDbMan->AddJob ( pDbAction );

		//	Note : ÀÚ?EÅ¬·´¿ø¿¡°Ô ÀÎÁõ±ÇÇÑ ¾Ë¸².
		GLMSG::SNET_CLUB_SUBMASTER_BRD NetMsgBrd;
		NetMsgBrd.dwCharID = pCLUB->m_dwMasterID;	//  ( ¸¶½ºÅÍ ID ¸¦ »ç?E )
		NetMsgBrd.dwFlags = NULL;
		NetMsgBrd.dwCDCertifior = pCLUB->m_dwCDCertifior;
		GLAgentServer::GetInstance().SENDTOCLUBCLIENT ( pCLUB->m_dwID, &NetMsgBrd );
	}

	//	Note : ¸É¹ö¿¡¼­ »èÁ¦ ÇÊµå¿¡ ¾Ë¸².
	GLMSG::SNET_CLUB_MEMBER_DEL_2FLD NetMsgFld;
	NetMsgFld.dwClub = pNetMsg->dwClub;
	NetMsgFld.dwMember = pNetMsg->dwMember;
	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}



BOOL GLAgentServer::MsgGmViewWorkEvent ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM3 )	return FALSE;

	GLMSG::SNET_GM_VIEWWORKEVENT_FB NetMsgFB;

	if( m_WorkEvent.bWorkEvent[0] )  // °æÇèÄ¡ 
	{
		sprintf( NetMsgFB.szWorkEventInfo, "Event Type : Exp, Event Rate : %.2f", m_WorkEvent.exp_Event.fSCALE );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
	}
	if( m_WorkEvent.bWorkEvent[1] )  // ¾ÆÀÌÅÛ
	{
		sprintf( NetMsgFB.szWorkEventInfo, "Event Type : Item, Event Rate : %.2f", m_WorkEvent.item_Event.fRATE );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
	}
	if( m_WorkEvent.bWorkEvent[2] )  // µ· µå¶øÀ²
	{
		sprintf( NetMsgFB.szWorkEventInfo, "Event Type : Money, Event Rate : %.2f", m_WorkEvent.money_Event.fRATE );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
	}
	if( m_WorkEvent.bWorkEvent[3] )  // EX ÀÌº¥Æ®
	{
		char szTempChar[32] = {0,};
		if( m_WorkEvent.ex_Event.emType & EMGM_EVENT_SPEED )
			strcat( szTempChar, "SPEED,");
		if( m_WorkEvent.ex_Event.emType & EMGM_EVENT_ASPEED )
			strcat( szTempChar, "ATTACK SPEED,");
		if( m_WorkEvent.ex_Event.emType & EMGM_EVENT_ATTACK )
			strcat( szTempChar, "ATTACK RATE,");
		
		szTempChar[strlen(szTempChar)-1] = '\0';
		sprintf( NetMsgFB.szWorkEventInfo, "Event Type : Ex Event[%s] Event Rate : %d", szTempChar, m_WorkEvent.ex_Event.wValue );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
	}
	if( m_WorkEvent.bWorkEvent[4] )  // ¸®¹ÌÆ® ÀÌº¥Æ® 
	{
		sprintf( NetMsgFB.szWorkEventInfo, "Event Type : LimitEvent, Start_LV %d, End_LV %d, Play_Time %d, Buster_Time %d, Item Rate : %.2f Exp Rate : %.2f, Attack Rate : %.2f, EventMinute %d,", 
				m_WorkEvent.limit_Event.start_Lv, m_WorkEvent.limit_Event.end_Lv, m_WorkEvent.limit_Event.play_Time, m_WorkEvent.limit_Event.buster_Time, 
				m_WorkEvent.limit_Event.expGain_Rate, m_WorkEvent.limit_Event.itemGain_Rate,m_WorkEvent.limit_Event.attackGain_Rate, m_WorkEvent.limit_Event.dwEventMinute );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
	}
	for( int i = 0; i < 3; i++ )
	{
		if( !m_WorkEvent.bWorkEvent[5+i] )  continue;// Å¬·¡½ºº° °æÇèÄ¡ ÀÌº¥Æ®

		char szTempChar[128] = {0,};
		char szTempChar2[32] = {0,};
		if( m_WorkEvent.class_Event[i].dwClassIndex == GLCC_ALL_NEWSEX )
		{
			strcpy( szTempChar, "ALL," );
		}else{
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_FIGHTER_M )
			{
				strcat( szTempChar, "FIGHT_M," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_ARMS_M )	
			{
				strcat( szTempChar, "ARMS_M," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_ARCHER_W )	
			{
				strcat( szTempChar, "ARCHER_W," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_SPIRIT_W )	
			{
				strcat( szTempChar, "SPIRIT_W," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_EXTREME_M )	
			{
				strcat( szTempChar, "EXTREME_M," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_EXTREME_W )	
			{
				strcat( szTempChar, "EXTREME_W," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_FIGHTER_W )
			{
				strcat( szTempChar, "FIGHTER_W," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_ARMS_W )
			{
				strcat( szTempChar, "ARMS_W," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_ARCHER_M )
			{
				strcat( szTempChar, "ARCHER_M," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_SPIRIT_M )
			{
				strcat( szTempChar, "SPIRIT_M," );
			}
			//added by   | 14-7-2012 | add new class
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_SCIENCE_M )
			{
				strcat( szTempChar, "SCIENCE_M," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_SCIENCE_W )
			{
				strcat( szTempChar, "SCIENCE_W," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_ASSASSIN_M )
			{
				strcat( szTempChar, "ASSASSIN_M," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_ASSASSIN_W )
			{
				strcat( szTempChar, "ASSASSIN_W," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_TESTING_M )
			{
				strcat( szTempChar, "TESTING_M," );
			}
			if( m_WorkEvent.class_Event[i].dwClassIndex&GLCC_TESTING_W )
			{
				strcat( szTempChar, "TESTING_W," );
			}
		}
		szTempChar[strlen(szTempChar)-1] = '\0';

		if( i == 0 )
			strcpy( szTempChar2, "Exp" );
		else if( i == 1 )
			strcpy( szTempChar2, "Item" );
		else if( i == 2 )
			strcpy( szTempChar2, "Money" );
		
		sprintf( NetMsgFB.szWorkEventInfo, "Event Type : Class %s Event[%s], Event Rate : %.2f, start_LV %d, end_LV %d", szTempChar2, szTempChar, 
				m_WorkEvent.class_Event[i].fEventRate, m_WorkEvent.class_Event[i].start_Lv, m_WorkEvent.class_Event[i].end_Lv );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
	}


	
	


	return TRUE;
}

BOOL GLAgentServer::MsgGmEventEx ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNET_GM_EVENT_EX *pNetMsg = (GLMSG::SNET_GM_EVENT_EX *)nmg;

	//if( pNetMsg->wValue < 1 )		pNetMsg->wValue = 1;
	//else if( pNetMsg->wValue > 200 )	pNetMsg->wValue = 200;

	SENDTOALLCHANNEL ( pNetMsg );

	m_WorkEvent.bWorkEvent[3] = TRUE;
	m_WorkEvent.ex_Event	  = *pNetMsg;

	return TRUE;
}

BOOL GLAgentServer::MsgGmEventExEnd ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNET_GM_EVENT_EX_END *pNetMsg = (GLMSG::SNET_GM_EVENT_EX_END *)nmg;

	SENDTOALLCHANNEL ( nmg );

	m_WorkEvent.bWorkEvent[3] = FALSE;

	return TRUE;
}

BOOL GLAgentServer::MsgGmEventExp( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;
	GLMSG::SNET_GM_EVENT_EXP *pNetMsg = (GLMSG::SNET_GM_EVENT_EXP *)nmg;
	//if( pNetMsg->fSCALE < 1.0f ) pNetMsg->fSCALE = 1.0f;
	//if( pNetMsg->fSCALE > 40.0f ) pNetMsg->fSCALE = 40.0f;

	SENDTOALLCHANNEL ( nmg );

	m_WorkEvent.bWorkEvent[0] = TRUE;
	m_WorkEvent.exp_Event	  = *pNetMsg;

	return TRUE;
}

BOOL GLAgentServer::MsgGmEventExpEnd( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	SENDTOALLCHANNEL ( nmg );

	m_WorkEvent.bWorkEvent[0] = FALSE;

	return TRUE;
}


// ÀÌº¥Æ® ½ÃÀÛ!!
BOOL GLAgentServer::MsgGmLimitEventBegin ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	//** Add EventTime
	GLMSG::SNET_GM_LIMIT_EVENT_BEGIN *pNetMsg = (GLMSG::SNET_GM_LIMIT_EVENT_BEGIN *)nmg;

	m_sEventState.bEventStart = TRUE;
	m_sEventState.EventBusterTime  = pNetMsg->buster_Time * 60;
	m_sEventState.EventPlayTime   = pNetMsg->play_Time * 60;

	m_sEventState.fExpGainRate     = pNetMsg->expGain_Rate;
	m_sEventState.fItemGainRate    = pNetMsg->itemGain_Rate;
	m_sEventState.MinEventLevel	   = pNetMsg->start_Lv;
	m_sEventState.MaxEventLevel    = pNetMsg->end_Lv;
	//add btg attack
	m_sEventState.fAttackGainRate  = pNetMsg->attackGain_Rate;
	m_sEventState.dwEventEndMinute = pNetMsg->dwEventMinute;
	
	m_sEventState.EventStartTime  = CTime::GetCurrentTime();

	CTime	  crtTime      = CTime::GetCurrentTime();
	for ( DWORD i=0; i<m_dwMaxClient; ++i )
	{
		PGLCHARAG pChar = m_PCArray[i];
		if ( pChar )
		{
			pChar->m_sEventTime.loginTime = crtTime.GetTime();
		}
	}

	SENDTOALLCHANNEL ( pNetMsg );

	m_WorkEvent.bWorkEvent[4] = TRUE;
	m_WorkEvent.limit_Event	  = *pNetMsg;

	return TRUE;
}

// ÀÌº¥Æ® Á¾?E!
BOOL GLAgentServer::MsgGmLimitEventEnd ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	m_sEventState.bEventStart = false;

	GLMSG::SNET_GM_LIMIT_EVENT_END *pNetMsg = (GLMSG::SNET_GM_LIMIT_EVENT_END *)nmg;

	SENDTOALLCHANNEL ( nmg );

	m_WorkEvent.bWorkEvent[4] = FALSE;

	return TRUE;
}


BOOL GLAgentServer::MsgGmLimitEventRestart ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;

	GLMSG::SNET_GM_LIMIT_EVENT_RESTART *pNetMsg = (GLMSG::SNET_GM_LIMIT_EVENT_RESTART *)nmg;
	
	pMyChar->m_sEventTime.loginTime = pNetMsg->restartTime;


	return TRUE;
}

BOOL GLAgentServer::MsgGmLimitEventTimeReq( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
//	GLMSG::SNET_GM_LIMIT_EVENT_TIME_REQ *pNetMsg = (GLMSG::SNET_GM_LIMIT_EVENT_TIME_REQ *)nmg;;

	PGLCHARAG pCHAR = GetChar ( dwGaeaID );
	if ( !pCHAR )							return FALSE;

	GLMSG::SNET_GM_LIMIT_EVENT_TIME_REQ_FB NetSendMsg;

	if( m_sEventState.bEventStart == FALSE )
	{
		NetSendMsg.bEventStart = FALSE;
	}else{
		NetSendMsg.bEventStart = TRUE;

		NetSendMsg.buster_Time = m_sEventState.EventBusterTime;
		NetSendMsg.play_Time   = m_sEventState.EventPlayTime;
		NetSendMsg.start_Lv	   = m_sEventState.MinEventLevel;
		NetSendMsg.end_Lv	   = m_sEventState.MaxEventLevel;

		// ¸¸?EÃ³À½ °ÔÀÓÀ» ½ÃÀÛÇÑ´Ù?E·Î±×ÀÎ ½Ã°£À» RESETÇÑ´Ù.
		if( pCHAR->m_bReciveEventTime == FALSE )
		{
			CTime	  crtTime      = CTime::GetCurrentTime();

			pCHAR->m_sEventTime.loginTime = crtTime.GetTime();
			NetSendMsg.loginTime   = pCHAR->m_sEventTime.loginTime;

			GLMSG::SNET_GM_LIMIT_EVENT_TIME_RESET NetResetMsg;
			NetResetMsg.dwGaeaID  = pCHAR->m_dwGaeaID;
			NetResetMsg.loginTime = crtTime.GetTime();
			SENDTOFIELD ( pCHAR->m_dwClientID, &NetResetMsg );


			pCHAR->m_bReciveEventTime = TRUE;

		}else{
			NetSendMsg.loginTime   = pCHAR->m_sEventTime.loginTime;
		}
	}
        




	SENDTOCLIENT ( pCHAR->m_dwClientID, &NetSendMsg );

	return TRUE;
}


BOOL GLAgentServer::MsgCyberCafeClassUpdate( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pCHAR = GetChar ( dwGaeaID );
	if ( !pCHAR )							return FALSE;

	GLMSG::SNET_CYBERCAFECLASS_UPDATE *pNetMsg = (GLMSG::SNET_CYBERCAFECLASS_UPDATE *)nmg;
	pCHAR->m_dwThaiCCafeClass = pNetMsg->dwCyberCafeClass;
	pCHAR->m_nMyCCafeClass = pNetMsg->dwCyberCafeClass;

	SENDTOFIELD ( pCHAR->m_dwClientID, pNetMsg );
	SENDTOCLIENT ( pCHAR->m_dwClientID, pNetMsg );

	return TRUE;
}


BOOL GLAgentServer::MsgGmEventItemGen ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNET_GM_EVEN_ITEM_GEN *pNetMsg = (GLMSG::SNET_GM_EVEN_ITEM_GEN *)nmg;
	//if ( pNetMsg->fRATE > 50.0f )	pNetMsg->fRATE = 50.0f;

	SENDTOALLCHANNEL ( pNetMsg );

	m_WorkEvent.bWorkEvent[1] = TRUE;
	m_WorkEvent.item_Event	  = *pNetMsg;

	return TRUE;
}

BOOL GLAgentServer::MsgGmEventItemGenEnd ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	SENDTOALLCHANNEL ( nmg );

	m_WorkEvent.bWorkEvent[1] = FALSE;

	return TRUE;
}

BOOL GLAgentServer::MsgGmEventClassEvent ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNET_GM_CLASS_EVENT *pNetMsg = (GLMSG::SNET_GM_CLASS_EVENT *)nmg;
	if ( pNetMsg->fEventRate > 50.0f )	pNetMsg->fEventRate = 50.0f;

	SENDTOALLCHANNEL ( pNetMsg );

	m_WorkEvent.bWorkEvent[5+pNetMsg->dwEventType]	= pNetMsg->bStart;
	m_WorkEvent.class_Event[pNetMsg->dwEventType]	= *pNetMsg;

	return TRUE;
}

//add sw buff
BOOL GLAgentServer::MsgGmEventSchoolEvent ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNET_GM_SCHOOL_EVENT *pNetMsg = (GLMSG::SNET_GM_SCHOOL_EVENT *)nmg;
	if ( pNetMsg->fEventRate > 10.0f )	pNetMsg->fEventRate = 10.0f;

	SENDTOALLCHANNEL ( pNetMsg );

	m_WorkEvent.bWorkEvent[8+pNetMsg->dwEventType]	= pNetMsg->bStart;
	m_WorkEvent.school_Event[pNetMsg->dwEventType]	= *pNetMsg;

	return TRUE;
}

BOOL GLAgentServer::MsgGmEventMoneyGen ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNET_GM_EVEN_MONEY_GEN *pNetMsg = (GLMSG::SNET_GM_EVEN_MONEY_GEN *)nmg;
	//if ( pNetMsg->fRATE > 50.0f )	pNetMsg->fRATE = 50.0f;

	SENDTOALLCHANNEL ( pNetMsg );

	m_WorkEvent.bWorkEvent[2] = TRUE;
	m_WorkEvent.money_Event	  = *pNetMsg;

	return TRUE;
}

BOOL GLAgentServer::MsgGmEventMoneyGenEnd ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	SENDTOALLCHANNEL ( nmg );

	m_WorkEvent.bWorkEvent[2] = FALSE;

	return TRUE;
}

BOOL GLAgentServer::MsgGmBigHead ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM2 )	return FALSE;

	GLMSG::SNET_GM_BIGHEAD* pNetMsg = (GLMSG::SNET_GM_BIGHEAD*) nmg;

	//	Note : ¸ð?EÇÊ?E¼­¹ö¿¡ ¼Û½Å.
	//
	SENDTOALLCHANNEL ( nmg );

	//	Note : ¸ð?EÅ¬¶óÀÌ¾ðÆ®¿¡ ¼Û½Å.
	//
	GLMSG::SNET_GM_BIGHEAD_BRD NetMsgBrd;
	NetMsgBrd.bBIGHEAD = pNetMsg->bBIGHEAD;
	SENDTOALLCLIENT ( &NetMsgBrd );

	return TRUE;
}
BOOL GLAgentServer::MsgCTFParticipate ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )		return FALSE;

	GLMSG::SNET_TYRANNY_PARTICIPATE* pNetMsg = (GLMSG::SNET_TYRANNY_PARTICIPATE*) nmg;

	GLMSG::SNET_TYRANNY_PARTICIPATE_BRD NetMsgBrd;
	NetMsgBrd.bParticipate = pNetMsg->bParticipate;
	SENDTOCLIENT ( pMyChar->m_dwClientID, &NetMsgBrd );

	return TRUE;
}
//BattleFieldUI Data Rejoin - Eduj
BOOL GLAgentServer::MsgCTFRejoin ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )		return FALSE;

	GLMSG::SNET_PVP_REJOIN* pNetMsg = (GLMSG::SNET_PVP_REJOIN*) nmg;

	GLMSG::SNET_PVP_REJOIN_BRD NetMsgBrd;
	NetMsgBrd.bRejoin = pNetMsg->bRejoin;
	SENDTOCLIENT ( pMyChar->m_dwClientID, &NetMsgBrd );

	return TRUE;
}
BOOL GLAgentServer::MsgGmBigHand ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM2 )	return FALSE;

	GLMSG::SNET_GM_BIGHAND* pNetMsg = (GLMSG::SNET_GM_BIGHAND*) nmg;

	//	Note : ¸ð?EÇÊ?E¼­¹ö¿¡ ¼Û½Å.
	//
	SENDTOALLCHANNEL ( nmg );

	//	Note : ¸ð?EÅ¬¶óÀÌ¾ðÆ®¿¡ ¼Û½Å.
	//
	GLMSG::SNET_GM_BIGHAND_BRD NetMsgBrd;
	NetMsgBrd.bBIGHAND = pNetMsg->bBIGHAND;
	SENDTOALLCLIENT ( &NetMsgBrd );

	return TRUE;
}

BOOL GLAgentServer::MsgGmFreePK ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM2 )	return FALSE;

	GLMSG::SNET_GM_FREEPK* pNetMsg = ( GLMSG::SNET_GM_FREEPK*) nmg;

	m_cFreePK.StartFREEPKMODE ( pNetMsg->dwPKTIME );

	SENDTOALLCHANNEL ( nmg );
	
	GLMSG::SNET_GM_FREEPK_BRD NetMsgBrd;
	NetMsgBrd.dwPKTIME = pNetMsg->dwPKTIME;
	SENDTOALLCLIENT ( &NetMsgBrd );

	return TRUE;
}

BOOL GLAgentServer::MsgGmViewAllPlayer ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM3 )	return FALSE;

	GLMSG::SNET_GM_VIEWALLPLAYER_FLD_REQ NetMsgFld;
	NetMsgFld.dwID = dwGaeaID;

	// ÇÊµå¼­¹ö¿¡ ¿äÃ»
	SENDTOFIELD ( pMyChar->m_dwClientID, &NetMsgFld );

	return TRUE;
}

// *****************************************************
// Desc: ÁöÁ¤µÈ ÄÉ¸¯ÅÍ¸¦ ÀÚ?E¿·À¸·Î ¼ÒÈ¯
// *****************************************************
BOOL GLAgentServer::MsgGmGenChar ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM3 )	return FALSE;

	GLMSG::SNETPC_GM_GENCHAR* pNetMsg = (GLMSG::SNETPC_GM_GENCHAR*) nmg;
	GLMSG::SNETPC_GM_GENCHAR_FB NetMsgFB;

	PGLCHARAG pGenCHAR;

	if ( pNetMsg->dwCHARID != 0 )
	{
		pGenCHAR = GetCharID ( pNetMsg->dwCHARID );
	}
	else
	{
		pGenCHAR = GetChar ( pNetMsg->szNAME );
	}

	if ( !pGenCHAR )
	{
		NetMsgFB.emFB = EMGM_MOVE2CHAR_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pGenCHAR->m_dwCurFieldSvr==FIELDSERVER_MAX )
	{
		NetMsgFB.emFB = EMGM_MOVE2CHAR_FB_TO_CONDITION;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pGenCHAR->m_nChannel!=pMyChar->m_nChannel )
	{
		NetMsgFB.emFB = EMGM_MOVE2CHAR_FB_CHANNEL;
		NetMsgFB.nChannel = pGenCHAR->m_nChannel;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	// GMÀÇ À§Ä¡¸¦ È®ÀÎÇÑ´Ù.
	GLMSG::SNETPC_GM_MOVE2CHAR_POS NetMsgCK;
	NetMsgCK.dwCOMMAND_CHARID = pGenCHAR->m_dwCharID;
	NetMsgCK.dwTO_CHARID = pMyChar->m_dwCharID;
	SENDTOFIELDSVR ( pMyChar->m_nChannel, pMyChar->m_dwCurFieldSvr, &NetMsgCK );

	NetMsgFB.emFB       = EMGM_MOVE2CHAR_FB_OK;
	
	SENDTOCLIENT ( dwClientID, &NetMsgFB );

	return TRUE;
}


BOOL GLAgentServer::MsgGmPrintCrowList ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pCHAR = GetChar ( dwGaeaID );
	if ( !pCHAR )							return FALSE;
	if ( pCHAR->m_dwUserLvl < USER_GM3 )	return FALSE;

	GLMSG::SNET_GM_PRINT_CROWLIST* pNetMsg = (GLMSG::SNET_GM_PRINT_CROWLIST*) nmg;

	GLMSG::SNET_GM_PRINT_CROWLIST_FLD NetMsgFld;
	NetMsgFld.dwFindMob = pNetMsg->dwFindMob;
	NetMsgFld.dwGaeaID  = dwGaeaID;
	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}

BOOL GLAgentServer::MsgGmGenMob ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNET_GM_MOB_GEN* pNetMsg = (GLMSG::SNET_GM_MOB_GEN*) nmg;

	GLMSG::SNET_GM_MOB_GEN_FLD NetMsgFld;

	NetMsgFld.dwGaeaID = dwGaeaID;
	NetMsgFld.wMainID = pNetMsg->wMainID;
	NetMsgFld.wSubID = pNetMsg->wSubID;
	NetMsgFld.wPosX = pNetMsg->wPosX;
	NetMsgFld.wPosY = pNetMsg->wPosY;
	
	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}

BOOL GLAgentServer::MsgGmGenMobEx ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNET_GM_MOB_GEN_EX* pNetMsg = (GLMSG::SNET_GM_MOB_GEN_EX*) nmg;

	SNATIVEID sMapID(pNetMsg->wMapMID,pNetMsg->wMapSID);
	GLMapList::FIELDMAP MapsList = m_sMapList.GetMapList ();
	GLMapList::FIELDMAP_ITER iter = MapsList.find ( sMapID.dwID );
	if ( iter==MapsList.end() ) return FALSE;	

	GLMSG::SNET_GM_MOB_GEN_EX_FLD NetMsgFld;
	NetMsgFld.wMobMID  = pNetMsg->wMobMID;
	NetMsgFld.wMobSID  = pNetMsg->wMobSID;
	NetMsgFld.wMapMID  = pNetMsg->wMapMID;
	NetMsgFld.wMapSID  = pNetMsg->wMapSID;
	NetMsgFld.wPosX	   = pNetMsg->wPosX;
	NetMsgFld.wPosY    = pNetMsg->wPosY;
	NetMsgFld.wRange   = pNetMsg->wRange;
	NetMsgFld.wNum     = pNetMsg->wNum;
	NetMsgFld.dwGaeaID = dwGaeaID;
	
	if ( pNetMsg->bThisChannel ) SENDTOCHANNEL ( &NetMsgFld, pMyChar->m_nChannel );
	else						 SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}

BOOL GLAgentServer::MsgGmDelMobEx ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNET_GM_MOB_DEL_EX* pNetMsg = (GLMSG::SNET_GM_MOB_DEL_EX*) nmg;

	SNATIVEID sMapID(pNetMsg->wMapMID,pNetMsg->wMapSID);
	GLMapList::FIELDMAP MapsList = m_sMapList.GetMapList ();
	GLMapList::FIELDMAP_ITER iter = MapsList.find ( sMapID.dwID );
	if ( iter==MapsList.end() ) return FALSE;	

	GLMSG::SNET_GM_MOB_DEL_EX_FLD NetMsgFld;
	NetMsgFld.wMobMID  = pNetMsg->wMobMID;
	NetMsgFld.wMobSID  = pNetMsg->wMobSID;
	NetMsgFld.wMapMID  = pNetMsg->wMapMID;
	NetMsgFld.wMapSID  = pNetMsg->wMapSID;
	
	if ( pNetMsg->bThisChannel ) SENDTOCHANNEL ( &NetMsgFld, pMyChar->m_nChannel );
	else						 SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}

BOOL GLAgentServer::MsgGmDelMob( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNET_GM_MOB_DEL* pNetMsg = (GLMSG::SNET_GM_MOB_DEL*) nmg;

	GLMSG::SNET_GM_MOB_DEL_FLD NetMsgFld;
	NetMsgFld.dwGaeaID	= dwGaeaID;
	NetMsgFld.sMobID	= pNetMsg->sMobID;
	NetMsgFld.bMaterial	= pNetMsg->bMaterial;

	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}

BOOL GLAgentServer::MsgGmMobLevel ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pCHAR = GetChar ( dwGaeaID );
	if ( !pCHAR )							return FALSE;
	if ( pCHAR->m_dwUserLvl < USER_GM1 )	return FALSE;

	SENDTOALLCHANNEL ( nmg );

	return TRUE;
}

BOOL GLAgentServer::MsgGmMobLevelClear ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pCHAR = GetChar ( dwGaeaID );
	if ( !pCHAR )							return FALSE;
	if ( pCHAR->m_dwUserLvl < USER_GM1 )	return FALSE;

	SENDTOALLCHANNEL ( nmg );

	return TRUE;
}

BOOL GLAgentServer::MsgGmWhereNPC ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pCHAR = GetChar ( dwGaeaID );
	if ( !pCHAR )							return FALSE;
	if ( pCHAR->m_dwUserLvl < USER_GM3 )	return FALSE;

	GLMSG::SNET_GM_WHERE_NPC* pNetMsg = (GLMSG::SNET_GM_WHERE_NPC*) nmg;

	GLMSG::SNET_GM_WHERE_NPC_FLD NetMsgFld;

	NetMsgFld.nidNPC   = pNetMsg->nidNPC;
	NetMsgFld.dwGaeaID = dwGaeaID;
	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}


// *****************************************************
// Desc: Ä£±¸À§Ä¡ È®ÀÎÈÄ ÇÊµå¼­¹ö¿¡ ÀÌµ¿ ¿äÃ» (field->Agent)
// *****************************************************
BOOL GLAgentServer::Msg2FriendAG ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_2_FRIEND_AG *pNetMsg = (GLMSG::SNETPC_2_FRIEND_AG *) nmg;
	GLMSG::SNETPC_2_FRIEND_FB NetMsgFB;

	PGLCHARAG pCHAR = GetCharID ( pNetMsg->dwCOMMAND_CHARID );
	if ( !pCHAR )	return FALSE;

	if ( pNetMsg->emFB==EM2FRIEND_FB_OK )
	{
		GLMSG::SNETPC_2_FRIEND_FLD NetMsgFld;
		NetMsgFld.sFriendMapID = pNetMsg->sFriendMapID;
		NetMsgFld.vFriendPos = pNetMsg->vFriendPos;
		NetMsgFld.wItemPosX = pNetMsg->wItemPosX;
		NetMsgFld.wItemPosY = pNetMsg->wItemPosY;
		SENDTOFIELD ( pCHAR->m_dwClientID, &NetMsgFld );
	}
	else
	{
		//	Note : Ä£±¸¿¡°Ô ÀÌµ¿ ½ÇÆÐ ¹ÝÈ¯.
		NetMsgFB.emFB = pNetMsg->emFB;
		SENDTOCLIENT ( pCHAR->m_dwClientID, &NetMsgFB );
	}

	return TRUE;
}

// *****************************************************
// Desc: Ä£±¸ÀÌµ¿ ¿äÃ» Ã³¸®
// *****************************************************
BOOL GLAgentServer::Msg2FriendReq ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETPC_2_FRIEND_REQ* pNetMsg = (GLMSG::SNETPC_2_FRIEND_REQ*) nmg;
	GLMSG::SNETPC_2_FRIEND_FB NetMsgFB;

	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;

	GLCHARAG_DATA::MAPFRIEND_ITER pos = pMyChar->m_mapFriend.find ( pNetMsg->szFRIEND_NAME );
	if ( pos==pMyChar->m_mapFriend.end() )
	{
		NetMsgFB.emFB = EM2FRIEND_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

//	SFRIEND * pFRIEND = (*pos).second;
//	if( !pFRIEND ) return FALSE;
	SFRIEND &sFRIEND = (*pos).second;


	if ( !sFRIEND.bONLINE )
//	if ( !pFRIEND->bONLINE )
	{
		NetMsgFB.emFB = EM2FRIEND_FB_FRIEND_CONDITION;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

//	PGLCHARAG pCHAR_FRIEND = GetCharID ( pFRIEND->nCharID );
	PGLCHARAG pCHAR_FRIEND = GetCharID ( sFRIEND.nCharID );
	if ( !pCHAR_FRIEND )
	{
		NetMsgFB.emFB = EM2FRIEND_FB_FRIEND_CONDITION;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	// Memo : »ó?E?³ª¸¦ »èÁ¦Çß°Å³ª Â÷´ÜÇÑ »óÅÂÀÌ?EÀÌµ¿ÀÌ ?EÒµÈ´?
	//
	pos = pCHAR_FRIEND->m_mapFriend.find( pMyChar->m_szName );
	if ( pos==pCHAR_FRIEND->m_mapFriend.end() )
	{
		NetMsgFB.emFB = EM2FRIEND_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}	

	SFRIEND &sFRIEND2 = (*pos).second;
//	if( !pMe ) return FALSE;

	if( sFRIEND2.IsBLOCK() )
	{
		NetMsgFB.emFB = EM2FRIEND_FB_FRIEND_BLOCK;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if( sFRIEND2.IsOFF() )
	{
		NetMsgFB.emFB = EM2FRIEND_FB_FRIEND_OFF;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pCHAR_FRIEND->m_dwCurFieldSvr==FIELDSERVER_MAX )
	{
		NetMsgFB.emFB = EM2FRIEND_FB_FRIEND_CONDITION;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pCHAR_FRIEND->m_nChannel!=pMyChar->m_nChannel )
	{
		NetMsgFB.emFB = EM2FRIEND_FB_FRIEND_CHANNEL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Note : Ä£±¸ÀÇ À§Ä¡ Á¡°Ë ¿äÃ».
	GLMSG::SNETPC_2_FRIEND_CK NetMsgCK;
	NetMsgCK.dwCOMMAND_CHARID = pMyChar->m_dwCharID;
	NetMsgCK.dwFRIEND_CHARID = pCHAR_FRIEND->m_dwCharID;
	NetMsgCK.wItemPosX = pNetMsg->wItemPosX;
	NetMsgCK.wItemPosY = pNetMsg->wItemPosY;
	SENDTOFIELDSVR ( pCHAR_FRIEND->m_nChannel, pCHAR_FRIEND->m_dwCurFieldSvr, &NetMsgCK );


	return TRUE;
}




// *****************************************************
// Desc: ÁöÁ¤ÇÑ Ä³¸¯ÅÍÀÇ ±Ó¼Ó¸»À» ¿³µè´Â´Ù.
// *****************************************************
BOOL GLAgentServer::MsgGetWhisperMsg( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETPC_GM_GETWHISPERMSG* pNetMsg = (GLMSG::SNETPC_GM_GETWHISPERMSG*) nmg;

	PGLCHARAG pMyChar = GetChar( dwGaeaID );
	if( !pMyChar ) return FALSE;

	if( pMyChar->m_dwUserLvl < USER_GM1 )
	{
		return FALSE;
	}


	if( strlen( pNetMsg->szNAME ) != 0 )
	{
		PGLCHARAG pTo_CHAR;
		pTo_CHAR = GetChar( pNetMsg->szNAME );
		if( pTo_CHAR )
		{		
			UINT i; 
			bool bAdd = TRUE;
			for( i = 0; i < pTo_CHAR->m_vecGetWhisperList.size(); i++ )
			{
				if( dwClientID == pTo_CHAR->m_vecGetWhisperList[i].dwClientID &&
					dwGaeaID == pTo_CHAR->m_vecGetWhisperList[i].dwGaeaID )
				{
					bAdd = FALSE; break;
				}
			}
			if( bAdd )
			{
				SGETWHISPERLIST WhisperList;
				WhisperList.dwClientID = dwClientID;
				WhisperList.dwGaeaID   = dwGaeaID;
				pTo_CHAR->m_vecGetWhisperList.push_back( WhisperList );

				pMyChar->m_GmWhisperList.dwGaeaID   = pTo_CHAR->m_dwGaeaID;
				pMyChar->m_GmWhisperList.dwClientID = pTo_CHAR->m_dwClientID;
				pMyChar->m_bViewWhisperMSG			= TRUE;
			}
		}
	}else{
		pMyChar->m_bViewWhisperMSG = FALSE;
	}
	return TRUE;
}

// *****************************************************
// Desc: ÁöÁ¤µÈ ÄÉ¸¯ÅÍ À§Ä¡·Î ÀÌµ¿
// *****************************************************
BOOL GLAgentServer::MsgMove2Char ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETPC_GM_MOVE2CHAR* pNetMsg = (GLMSG::SNETPC_GM_MOVE2CHAR*) nmg;
	GLMSG::SNETPC_GM_MOVE2CHAR_FB NetMsgFB;

	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;

	if ( pMyChar->m_dwUserLvl < USER_GM3 )
	{
		NetMsgFB.emFB = EMGM_MOVE2CHAR_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	PGLCHARAG pTO_CHAR;;

	if ( pNetMsg->dwCHARID != 0 )
	{
		pTO_CHAR = GetCharID ( pNetMsg->dwCHARID );
	}
	else
	{
		pTO_CHAR = GetChar ( pNetMsg->szNAME );
	}

	if ( !pTO_CHAR )
	{
		NetMsgFB.emFB = EMGM_MOVE2CHAR_FB_FAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pTO_CHAR->m_dwCurFieldSvr==FIELDSERVER_MAX )
	{
		NetMsgFB.emFB = EMGM_MOVE2CHAR_FB_TO_CONDITION;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pTO_CHAR->m_nChannel!=pMyChar->m_nChannel )
	{
		NetMsgFB.emFB = EMGM_MOVE2CHAR_FB_CHANNEL;
		NetMsgFB.nChannel = pTO_CHAR->m_nChannel;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Note : Ä£±¸ÀÇ À§Ä¡ Á¡°Ë ¿äÃ».
	GLMSG::SNETPC_GM_MOVE2CHAR_POS NetMsgCK;
	NetMsgCK.dwCOMMAND_CHARID = pMyChar->m_dwCharID;
	NetMsgCK.dwTO_CHARID = pTO_CHAR->m_dwCharID;
	SENDTOFIELDSVR ( pTO_CHAR->m_nChannel, pTO_CHAR->m_dwCurFieldSvr, &NetMsgCK );

	return TRUE;
}

// *****************************************************
// Desc: À¯?EÃ¤ÆÃ ºúÓ° Ã³¸® (User Account)
// *****************************************************
BOOL GLAgentServer::MsgGmChatBlockUA ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM3 )	return FALSE;

	GLMSG::SNET_GM_CHAT_BLOCK_UACCOUNT *pNetMsg = (GLMSG::SNET_GM_CHAT_BLOCK_UACCOUNT *) nmg;
	GLMSG::SNET_GM_CHAT_BLOCK_FB NetMsgFB;

	PGLCHARAG pCHAR = GetCharUA ( pNetMsg->szUACCOUNT );
	// Á¢¼ÓÁßÀÌ ¾Æ´Ò°æ?E
	if ( !pCHAR )
	{
		NetMsgFB.bBLOCK = false;
		StringCchCopy ( NetMsgFB.szUACCOUNT, USR_ID_LENGTH+1, pNetMsg->szUACCOUNT );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );

		// Ã¤ÆÃºúÓ° ¿¹¾àÀÚ DB¿¡ ÀúÀåÇÑ´Ù.

		return FALSE;
	}

	if ( pNetMsg->dwBLOCK_MINUTE!=0 )
	{
		//	ºúÓ°½Ã°£ ÁöÁ¤.
		CTime cBLOCK = CTime::GetCurrentTime();
		CTimeSpan cSPAN(0,0,pNetMsg->dwBLOCK_MINUTE,0);
		cBLOCK += cSPAN;

		pCHAR->m_tCHATBLOCK = cBLOCK.GetTime();
	}
	else
	{
		//	ºúÓ°½Ã°£ ÇØ?E
		pCHAR->m_tCHATBLOCK = 0;
	}

	//	DB¿¡ Àú?E
	CSetChatBlockTime *pDbAction = new CSetChatBlockTime(pCHAR->m_dwUserID,pCHAR->m_tCHATBLOCK);
	if ( GetDBMan() )	GetDBMan()->AddJob ( pDbAction );

	//	FLD¿¡ ¾Ë¸².
	GLMSG::SNET_GM_CHAT_BLOCK_FLD NetMsgFLD;
	NetMsgFLD.dwCHARID = pCHAR->m_dwCharID;
	NetMsgFLD.dwBLOCK_MINUTE = pNetMsg->dwBLOCK_MINUTE;
	SENDTOALLCHANNEL(&NetMsgFLD);

	//	FB.
	NetMsgFB.bBLOCK = true;
	NetMsgFB.dwBLOCK_MINUTE = pNetMsg->dwBLOCK_MINUTE;
	StringCchCopy ( NetMsgFB.szCHARNAME, CHAR_SZNAME, pCHAR->m_szName );
	StringCchCopy ( NetMsgFB.szUACCOUNT, USR_ID_LENGTH+1, pCHAR->m_szUserName );
	SENDTOCLIENT ( dwClientID, &NetMsgFB );

	return TRUE;
}

// *****************************************************
// Desc: À¯?EÃ¤ÆÃ ºúÓ° Ã³¸® (Ä³¸¯ÅÍ?E
// *****************************************************
BOOL GLAgentServer::MsgGmChatBlockCN ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM3 )	return FALSE;

	GLMSG::SNET_GM_CHAT_BLOCK_CHARNAME *pNetMsg = (GLMSG::SNET_GM_CHAT_BLOCK_CHARNAME *) nmg;
	GLMSG::SNET_GM_CHAT_BLOCK_FB NetMsgFB;

	PGLCHARAG pCHAR = GetChar ( pNetMsg->szCHARNAME );
	// Á¢¼ÓÁßÀÌ ¾Æ´Ò°æ?E
	if ( !pCHAR )
	{
		NetMsgFB.bBLOCK = false;
		StringCchCopy ( NetMsgFB.szUACCOUNT, USR_ID_LENGTH+1, pNetMsg->szCHARNAME );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );

		// Ã¤ÆÃºúÓ° ¿¹¾àÀÚ DB¿¡ ÀúÀåÇÑ´Ù.
		

		return FALSE;
	}

	if ( pNetMsg->dwBLOCK_MINUTE!=0 )
	{
		//	ºúÓ°½Ã°£ ÁöÁ¤.
		CTime cBLOCK = CTime::GetCurrentTime();
		CTimeSpan cSPAN(0,0,pNetMsg->dwBLOCK_MINUTE,0);
		cBLOCK += cSPAN;

		pCHAR->m_tCHATBLOCK = cBLOCK.GetTime();
	}
	else
	{
		//	ºúÓ°½Ã°£ ÇØ?E
		pCHAR->m_tCHATBLOCK = 0;
	}

	//	DB¿¡ Àú?E
	CSetChatBlockTime *pDbAction = new CSetChatBlockTime(pCHAR->m_dwUserID,pCHAR->m_tCHATBLOCK);
	if ( GetDBMan() )	GetDBMan()->AddJob ( pDbAction );

	//	FLD¿¡ ¾Ë¸².
	GLMSG::SNET_GM_CHAT_BLOCK_FLD NetMsgFLD;
	NetMsgFLD.dwCHARID = pCHAR->m_dwCharID;
	NetMsgFLD.dwBLOCK_MINUTE = pNetMsg->dwBLOCK_MINUTE;
	SENDTOALLCHANNEL(&NetMsgFLD);

	//	FB.
	NetMsgFB.bBLOCK = true;
	NetMsgFB.dwBLOCK_MINUTE = pNetMsg->dwBLOCK_MINUTE;
	StringCchCopy ( NetMsgFB.szCHARNAME, CHAR_SZNAME, pCHAR->m_szName );
	StringCchCopy ( NetMsgFB.szUACCOUNT, USR_ID_LENGTH+1, pCHAR->m_szUserName );
	SENDTOCLIENT ( dwClientID, &NetMsgFB );

	return TRUE;
}

BOOL GLAgentServer::MsgGmChatBlockCI ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM3 )	return FALSE;

	GLMSG::SNET_GM_CHAT_BLOCK_CHARID *pNetMsg = (GLMSG::SNET_GM_CHAT_BLOCK_CHARID *) nmg;
	GLMSG::SNET_GM_CHAT_BLOCK_FB NetMsgFB;

	PGLCHARAG pCHAR = GetCharID ( pNetMsg->dwCHARID );
	if ( !pCHAR )
	{
		NetMsgFB.bBLOCK = false;
		StringCchCopy ( NetMsgFB.szUACCOUNT, USR_ID_LENGTH+1, "notfound" );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	if ( pNetMsg->dwBLOCK_MINUTE!=0 )
	{
		//	ºúÓ°½Ã°£ ÁöÁ¤.
		pCHAR->m_tCHATBLOCK;

		CTime cBLOCK = CTime::GetCurrentTime();
		CTimeSpan cSPAN(0,0,pNetMsg->dwBLOCK_MINUTE,0);
		cBLOCK += cSPAN;

		pCHAR->m_tCHATBLOCK = cBLOCK.GetTime();
	}
	else
	{
		//	ºúÓ°½Ã°£ ÇØ?E
		pCHAR->m_tCHATBLOCK = 0;
	}

	//	DB¿¡ Àú?E
	CSetChatBlockTime *pDbAction = new CSetChatBlockTime(pCHAR->m_dwUserID,pCHAR->m_tCHATBLOCK);
	if ( GetDBMan() )	GetDBMan()->AddJob ( pDbAction );

	//	FLD¿¡ ¾Ë¸².
	GLMSG::SNET_GM_CHAT_BLOCK_FLD NetMsgFLD;
	NetMsgFLD.dwCHARID = pCHAR->m_dwCharID;
	NetMsgFLD.dwBLOCK_MINUTE = pNetMsg->dwBLOCK_MINUTE;
	SENDTOALLCHANNEL(&NetMsgFLD);

	//	FB.
	NetMsgFB.bBLOCK = true;
	NetMsgFB.dwBLOCK_MINUTE = pNetMsg->dwBLOCK_MINUTE;
	StringCchCopy ( NetMsgFB.szCHARNAME, CHAR_SZNAME, pCHAR->m_szName );
	StringCchCopy ( NetMsgFB.szUACCOUNT, USR_ID_LENGTH+1, pCHAR->m_szUserName );
	SENDTOCLIENT ( dwClientID, &NetMsgFB );

	return TRUE;
}
BOOL GLAgentServer::MsgGlobalSuccess ( NET_MSG_GENERIC* nmg )
{
		GLMSG::SNET_GLOBAL_SUCCESS_GRIND *NetMsgBrd = (GLMSG::SNET_GLOBAL_SUCCESS_GRIND *) nmg;
		GLMSG::SNET_GLOBAL_SUCCESS_GRIND NetMsg;
		
		//TEXTCONSOLEMSG_WRITE( "Received Agent %d %d",NetMsgBrd->dwCharID,NetMsgBrd->dwGrindUp );
	

		NetMsg.dwCharID = NetMsgBrd->dwCharID;
		NetMsg.dwGrindUp = NetMsgBrd->dwGrindUp;
		NetMsg.sItemCustom = NetMsgBrd->sItemCustom;
		StringCchCopy ( NetMsg.szName, CHAR_SZNAME, NetMsgBrd->szName );
		SENDTOALLCLIENT ( &NetMsg , 0 );
		
	return TRUE;
}

BOOL GLAgentServer::MsgGmWarningMSG ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNET_GM_WARNING_MSG *pNetMsg = (GLMSG::SNET_GM_WARNING_MSG*) nmg;
	GLMSG::SNET_GM_WARNING_MSG_FLD NetMsgBrd;

	NetMsgBrd.dwGaeaID = dwGaeaID;
	NetMsgBrd.bOn = pNetMsg->bOn;
	SENDTOALLCHANNEL ( &NetMsgBrd );

	return TRUE;
}

BOOL GLAgentServer::MsgGmSlotEVENT ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM1 )	return FALSE;

	GLMSG::SNET_GM_SLOT_EVENT *pNetMsg = (GLMSG::SNET_GM_SLOT_EVENT*) nmg;
	GLMSG::SNET_GM_SLOT_EVENT_FLD NetMsgBrd;

	NetMsgBrd.dwGaeaID = dwGaeaID;
	NetMsgBrd.bOn = pNetMsg->bOn;
	NetMsgBrd.nSlotNumber = pNetMsg->nSlotNumber;
	SENDTOALLCHANNEL ( &NetMsgBrd );

	return TRUE;
}

BOOL GLAgentServer::MsgGmShowMeTheMoney ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
#if defined(_RELEASED) || defined(KRT_PARAM)
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM3 )	return FALSE;

	GLMSG::SNET_GM_SHOWMETHEMONEY *pNetMsg = (GLMSG::SNET_GM_SHOWMETHEMONEY*) nmg;
	GLMSG::SNET_GM_SHOWMETHEMONEY_FLD NetMsgBrd;

	NetMsgBrd.dwGaeaID = dwGaeaID;
	NetMsgBrd.llMoney = pNetMsg->llMoney;
	SENDTOALLCHANNEL( &NetMsgBrd );
#endif

	return TRUE;
}

BOOL GLAgentServer::MsgUserCharInfo4NAME ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;

	GLMSG::SNET_USER_CHAR_INFO_4NAME *pNetMsg = (GLMSG::SNET_USER_CHAR_INFO_4NAME *) nmg;
	GLMSG::SNET_USER_CHAR_INFO_AGT_FB NetMsgFB;

	PGLCHARAG pCHAR = GetChar ( pNetMsg->szCHARNAME );
	if ( !pCHAR )
	{
		StringCchCopy ( NetMsgFB.szCHARNAME, CHAR_SZNAME, "not found" );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );

		return FALSE;
	}

	//	ÇÊµå¿¡ »ó¼¼ Á¤º¸ ¿äÃ».
	GLMSG::SNET_USER_CHAR_INFO_FLD NetMsgFld;
	NetMsgFld.dwCHARID = pCHAR->m_dwCharID;
	NetMsgFld.dwCLIENTID_FB = dwClientID;
	SENDTOALLCHANNEL( &NetMsgFld );

	return TRUE;
}

BOOL GLAgentServer::MsgGmCharInfo4NAME ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM3 )	return FALSE;

	GLMSG::SNET_GM_CHAR_INFO_4NAME *pNetMsg = (GLMSG::SNET_GM_CHAR_INFO_4NAME *) nmg;
	GLMSG::SNET_GM_CHAR_INFO_AGT_FB NetMsgFB;

	PGLCHARAG pCHAR = GetChar ( pNetMsg->szCHARNAME );
	if ( !pCHAR )
	{
		StringCchCopy ( NetMsgFB.szCHARNAME, CHAR_SZNAME, "notfound" );
		StringCchCopy ( NetMsgFB.szUACCOUNT, USR_ID_LENGTH+1, "notfound" );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Å¬¶óÀÌ¾ðÆ®¿¡ agt fb
	StringCchCopy ( NetMsgFB.szCHARNAME, CHAR_SZNAME, pCHAR->m_szName );
	StringCchCopy ( NetMsgFB.szUACCOUNT, USR_ID_LENGTH+1, pCHAR->m_szUserName );
	NetMsgFB.dwSERVER;
	NetMsgFB.dwCHANNEL = (DWORD) pCHAR->m_nChannel;
	NetMsgFB.dwCHARID = pCHAR->m_dwCharID;
	NetMsgFB.dwGAEAID = pCHAR->m_dwGaeaID;
	SENDTOCLIENT ( dwClientID, &NetMsgFB );

	//	ÇÊµå¿¡ »ó¼¼ Á¤º¸ ¿äÃ».
	GLMSG::SNET_GM_CHAR_INFO_FLD NetMsgFld;
	NetMsgFld.dwCHARID = pCHAR->m_dwCharID;
	NetMsgFld.dwCLIENTID_FB = dwClientID;
	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}

BOOL GLAgentServer::MsgGmCharInfo4CID ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar ( dwGaeaID );
	if ( !pMyChar )							return FALSE;
	if ( pMyChar->m_dwUserLvl < USER_GM3 )	return FALSE;

	GLMSG::SNET_GM_CHAR_INFO_4CHARID *pNetMsg = (GLMSG::SNET_GM_CHAR_INFO_4CHARID *) nmg;
	GLMSG::SNET_GM_CHAR_INFO_AGT_FB NetMsgFB;

	PGLCHARAG pCHAR = GetCharID ( pNetMsg->dwCHARID );
	if ( !pCHAR )
	{
		StringCchCopy ( NetMsgFB.szCHARNAME, CHAR_SZNAME, "notfound" );
		StringCchCopy ( NetMsgFB.szUACCOUNT, USR_ID_LENGTH+1, "notfound" );
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	//	Å¬¶óÀÌ¾ðÆ®¿¡ agt fb
	StringCchCopy ( NetMsgFB.szCHARNAME, CHAR_SZNAME, pCHAR->m_szName );
	StringCchCopy ( NetMsgFB.szUACCOUNT, USR_ID_LENGTH+1, pCHAR->m_szUserName );
	NetMsgFB.dwSERVER;
	NetMsgFB.dwCHANNEL = (DWORD) pCHAR->m_nChannel;
	NetMsgFB.dwCHARID = pCHAR->m_dwCharID;
	NetMsgFB.dwGAEAID = pCHAR->m_dwGaeaID;
	SENDTOCLIENT ( dwClientID, &NetMsgFB );

	//	ÇÊµå¿¡ »ó¼¼ Á¤º¸ ¿äÃ».
	GLMSG::SNET_GM_CHAR_INFO_FLD NetMsgFld;
	NetMsgFld.dwCHARID = pCHAR->m_dwCharID;
	NetMsgFld.dwCLIENTID_FB = dwClientID;
	SENDTOALLCHANNEL ( &NetMsgFld );

	return TRUE;
}

BOOL GLAgentServer::MsgGmCharInfoFldFB ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_GM_CHAR_INFO_FLD_FB *pNetMsg = (GLMSG::SNET_GM_CHAR_INFO_FLD_FB *) nmg;

	SENDTOCLIENT ( pNetMsg->dwCLIENTID_FB, pNetMsg );

	return TRUE;
}

BOOL GLAgentServer::MsgUserCharInfoFldFB ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_USER_CHAR_INFO_FLD_FB *pNetMsg = (GLMSG::SNET_USER_CHAR_INFO_FLD_FB *) nmg;

	SENDTOCLIENT ( pNetMsg->dwCLIENTID_FB, pNetMsg );

	return TRUE;
}

// *****************************************************
// Desc: ÄÉ¸¯ÅÍ ÀÌµ¿À» ÇÊµå¼­¹ö¿¡ ¿äÃ»
// *****************************************************
BOOL GLAgentServer::MsgMove2CharAG ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_GM_MOVE2CHAR_AG *pNetMsg = (GLMSG::SNETPC_GM_MOVE2CHAR_AG *) nmg;
	GLMSG::SNETPC_GM_MOVE2CHAR_FB NetMsgFB;

	PGLCHARAG pCHAR = GetCharID ( pNetMsg->dwCOMMAND_CHARID );
	if ( !pCHAR )	return FALSE;

	if ( pNetMsg->emFB==EMGM_MOVE2CHAR_FB_OK )
	{
		GLMSG::SNETPC_GM_MOVE2CHAR_FLD NetMsgFld;
		NetMsgFld.sToMapID = pNetMsg->sToMapID;
		NetMsgFld.vToPos = pNetMsg->vToPos;
		SENDTOFIELD ( pCHAR->m_dwClientID, &NetMsgFld );
	}
	else
	{
		//	Note : Ä£±¸¿¡°Ô ÀÌµ¿ ½ÇÆÐ ¹ÝÈ¯.
		NetMsgFB.emFB = pNetMsg->emFB;
		SENDTOCLIENT ( pCHAR->m_dwClientID, &NetMsgFB );
	}

	return TRUE;
}

BOOL GLAgentServer::MsgClubBattleRemainTime ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_SERVER_CLUB_BATTLE_REMAIN_AG* pNetMsg = 
		(GLMSG::SNETPC_SERVER_CLUB_BATTLE_REMAIN_AG*) nmg;

	PGLCHARAG pChar = GetChar ( pNetMsg->dwGaeaID );
	if ( pChar )
	{
		GLMSG::SNET_CLUB_BATTLE_REMAIN_BRD NetMsgBrd;
		NetMsgBrd.dwTime = GLGuidanceAgentMan().GetInstance().GetRemainTime ();
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgBrd );
	}

	return TRUE;
}

BOOL GLAgentServer::MsgClubDeathMatchRemainTime ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_SERVER_CLUB_DEATHMATCH_REMAIN_AG* pNetMsg = 
		(GLMSG::SNETPC_SERVER_CLUB_DEATHMATCH_REMAIN_AG*) nmg;

	PGLCHARAG pChar = GetChar ( pNetMsg->dwGaeaID );
	if ( pChar )
	{
		GLMSG::SNET_CLUB_DEATHMATCH_REMAIN_BRD NetMsgBrd;
		NetMsgBrd.dwTime = GLClubDeathMatchAgentMan().GetInstance().GetRemainTime ();
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgBrd );
	}

	return TRUE;
}

BOOL GLAgentServer::MsgSchoolWarsRemainTime ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_SERVER_SCHOOL_WARS_REMAIN_AG* pNetMsg = 
		(GLMSG::SNETPC_SERVER_SCHOOL_WARS_REMAIN_AG*) nmg;

	PGLCHARAG pChar = GetChar ( pNetMsg->dwGaeaID );
	if ( pChar )
	{
		GLMSG::SNET_SCHOOL_WARS_REMAIN_BRD NetMsgBrd;
		NetMsgBrd.dwTime = GLSchoolWarsAgentMan().GetInstance().GetRemainTime ();
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgBrd );
	}

	return TRUE;
}

BOOL GLAgentServer::MsgRoyalRumbleRemainTime ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_SERVER_ROYAL_RUMBLE_REMAIN_AG* pNetMsg = 
		(GLMSG::SNETPC_SERVER_ROYAL_RUMBLE_REMAIN_AG*) nmg;

	PGLCHARAG pChar = GetChar ( pNetMsg->dwGaeaID );
	if ( pChar )
	{
		GLMSG::SNET_ROYAL_RUMBLE_REMAIN_BRD NetMsgBrd;
		NetMsgBrd.dwTime = GLRoyalRumbleAgentMan().GetInstance().GetRemainTime ();
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgBrd );
	}

	return TRUE;
}


BOOL GLAgentServer::MsgTowerWarsRemainTime ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_SERVER_TOWERWARS_REMAIN_AG* pNetMsg = 
		(GLMSG::SNETPC_SERVER_TOWERWARS_REMAIN_AG*) nmg;

	PGLCHARAG pChar = GetChar ( pNetMsg->dwGaeaID );
	if ( pChar )
	{
		GLMSG::SNET_TOWERWARS_REMAIN_BRD NetMsgBrd;
		NetMsgBrd.dwTime = GLTowerWarsAgentMan().GetInstance().GetRemainTime ();
		SENDTOCLIENT ( pChar->m_dwClientID, &NetMsgBrd );
	}

	return TRUE;
}
// Detect AutoPots Global Announcement - Eduj
BOOL GLAgentServer::MsgAPDetectedBrd ( NET_MSG_GENERIC* nmg )
{
	SENDTOALLCLIENT ( nmg );

	return TRUE;
}
BOOL GLAgentServer::MsgWPEDetectedBrd ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_WPE_DT_BRD* pNetMsg = (GLMSG::SNET_WPE_DT_BRD*) nmg;
	PGLCHARAG pChar = GetCharID ( pNetMsg->dwCHARID );
    if ( pChar )
	{
      CTime cCurTime = CTime::GetCurrentTime();
      int nDay = cCurTime.GetDay ();
	  CUserBlock *pDbAction = new CUserBlock(pNetMsg->dwUSERID,nDay);
      if ( GetDBMan() )	GetDBMan()->AddJob ( pDbAction );
	}

	SENDTOALLCLIENT ( nmg );

	return TRUE;
}
BOOL GLAgentServer::MsgClubCDCertifyIngBrd ( NET_MSG_GENERIC* nmg )
{
	SENDTOALLCLIENT ( nmg );

	return TRUE;
}
BOOL GLAgentServer::MsgNonDropBrd ( NET_MSG_GENERIC* nmg )
{
	SENDTOALLCLIENT ( nmg );

	return TRUE;
}
BOOL GLAgentServer::MsgRemoveNonDropBrd ( NET_MSG_GENERIC* nmg )
{
	SENDTOALLCLIENT ( nmg );

	return TRUE;
}
BOOL GLAgentServer::MsgClubCDCertifyBrd ( NET_MSG_GENERIC* nmg )
{
	SENDTOALLCLIENT ( nmg );

	return TRUE;
}

BOOL GLAgentServer::MsgMarketOpenCheck ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	PGLCHARAG pMyChar = GetChar(dwGaeaID);

	if( pMyChar == NULL )
	{
		m_pConsoleMsg->Write( LOG_TEXT_CONSOLE, "%%%% Could not found Character..%d %%%%", dwGaeaID );
	}

	return TRUE;
}

BOOL GLAgentServer::MsgClubBattleKillUpdate ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_CLUB_BATTLE_KILL_UPDATE_AGT* pNetMsg = (GLMSG::SNET_CLUB_BATTLE_KILL_UPDATE_AGT*) nmg;

	GLCLUB* pClub = m_cClubMan.GetClub ( pNetMsg->dwClubID );
	if ( !pClub ) return FALSE;

	pClub->KillBattleClubMem( pNetMsg->dwBattleClubID, pNetMsg->wKillPoint );
	pClub->DeathBattleClubMem( pNetMsg->dwBattleClubID, pNetMsg->wDeathPoint );

	return TRUE;
}

BOOL GLAgentServer::MsgClubBattleLastKillUpdate( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_CLUB_BATTLE_LAST_KILL_UPDATE_AGT* pNetMsg = (GLMSG::SNET_CLUB_BATTLE_LAST_KILL_UPDATE_AGT*) nmg;

	GLCLUB* pClub = m_cClubMan.GetClub ( pNetMsg->dwClubID_A );
	if ( !pClub ) return FALSE;

	pClub->SetLastBattlePoint( pNetMsg->dwClubID_B, pNetMsg->wKillPoint, pNetMsg->wDeathPoint );

	return TRUE;
}

BOOL GLAgentServer::MsgReqTaxi ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNETPC_REQ_TAXI* pNetMsg = (GLMSG::SNETPC_REQ_TAXI*)nmg;

	GLMSG::SNETPC_REQ_TAXI_FB NetMsgFB;

	PGLCHARAG pMyChar = GetChar(dwGaeaID);
	if ( !pMyChar ) return FALSE;

	// Á¤·ù?E°Ë?E
	STAXI_MAP* pTaxiMap = GLTaxiStation::GetInstance().GetTaxiMap ( pNetMsg->dwSelectMap );
	if ( !pTaxiMap )
	{
		NetMsgFB.emFB = EMTAXI_TAKE_MAPFAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	// Á¤·ù?E°Ë?E
	STAXI_STATION* pStation = pTaxiMap->GetStation( pNetMsg->dwSelectStop );
	if ( !pStation )
	{
		NetMsgFB.emFB = EMTAXI_TAKE_STATIONFAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}
	
	SNATIVEID sMAPID(pStation->dwMAPID);

	if ( sMAPID==SNATIVEID(false) )
	{
		NetMsgFB.emFB = EMTAXI_TAKE_MAPFAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	DWORD dwFieldServer = GetFieldServer( sMAPID );
	if ( dwFieldServer == FIELDSERVER_MAX )
	{
		NetMsgFB.emFB = EMTAXI_TAKE_MAPFAIL;
		SENDTOCLIENT ( dwClientID, &NetMsgFB );
		return FALSE;
	}

	// °°Àº ÇÊµåÀÌ?E±×³É º¸³»?E
	// ´Ù¸¥ ÇÊµåÀÌ?EÁÂÇ¥¸¦ ±¸ÇØ¼­ º¸³»ÁØ´Ù.
	if ( dwFieldServer == pMyChar->m_dwCurFieldSvr )
	{
		SENDTOFIELD( dwClientID, pNetMsg );
	}
	else
	{
		GLMSG::SNETPC_REQ_TAXI_NPCPOS NetMsgPos;
		NetMsgPos.dwSelectMap = pNetMsg->dwSelectMap;
		NetMsgPos.dwSelectStop = pNetMsg->dwSelectStop;
		NetMsgPos.dwGaeaID = pNetMsg->dwGaeaID;
		NetMsgPos.wPosX = pNetMsg->wPosX;
		NetMsgPos.wPosY = pNetMsg->wPosY;

		SENDTOFIELDSVR( pMyChar->m_nChannel, dwFieldServer, &NetMsgPos );
	}

	return TRUE;
}

BOOL GLAgentServer::MsgReqTaxiNpcPos ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_REQ_TAXI_NPCPOS_FB* pNetMsg = (GLMSG::SNETPC_REQ_TAXI_NPCPOS_FB*)nmg;
	GLMSG::SNETPC_REQ_TAXI_FB NetMsgFB;

	PGLCHARAG pMyChar = GetChar(pNetMsg->dwGaeaID);
	if ( !pMyChar )
	{
		return FALSE;
	}

	if ( pNetMsg->vPos == D3DXVECTOR3(FLT_MAX,FLT_MAX,FLT_MAX) )
	{
		NetMsgFB.emFB = EMTAXI_TAKE_NPCFAIL;
		SENDTOCLIENT ( pMyChar->m_dwClientID, &NetMsgFB );
		return FALSE;
	}
	


	GLMSG::SNETPC_REQ_TAXI NetMsg;
	NetMsg.dwSelectMap = pNetMsg->dwSelectMap;
	NetMsg.dwSelectStop = pNetMsg->dwSelectStop;
	NetMsg.wPosX = pNetMsg->wPosX;
	NetMsg.wPosY = pNetMsg->wPosY;
	NetMsg.dwGaeaID = pNetMsg->dwGaeaID;
	NetMsg.vPos = pNetMsg->vPos;
	
	SENDTOFIELD( pMyChar->m_dwClientID, &NetMsg );

	return TRUE;
}

BOOL GLAgentServer::MsgNpcCommission( NET_MSG_GENERIC* nmg, DWORD dwClientID)
{
	GLMSG::SNET_INVEN_NPC_COMMISSION* pNetMsg = (GLMSG::SNET_INVEN_NPC_COMMISSION*)nmg;
	GLMSG::SNET_INVEN_NPC_COMMISSION_FB NetMsgFB;

	NetMsgFB.dwCharID = pNetMsg->dwCharID;
	NetMsgFB.dwUserID = pNetMsg->dwUserID;
	NetMsgFB.lnCommission = pNetMsg->lnCommission;

	PGLCHARAG pChar = GetCharID(pNetMsg->dwCharID);	

	//	Ä³¸¯ÅÍ°¡ Á¢¼ÓÁßÀÏ¶§ ( Å¸ÇÊµå¿¡ ÀÖ´Â »óÈ² ) 
	//	ºñÁ¢¼ÓÁßÀÏ¶§ ÇÊµå¿¡ ÀúÀåÀ» ¿äÃ»ÇÑ´Ù.
	if ( pChar )
	{
		NetMsgFB.emFB = EMREQ_NPC_COMMISSION_CHAR;		
		SENDTOFIELDSVR( pChar->m_nChannel, pChar->m_dwCurFieldSvr, &NetMsgFB );
	}
	else
	{
		NetMsgFB.emFB = EMREQ_NPC_COMMISSION_DB;			
		SENDTOFIELDSVR(  pNetMsg->nCHANNEL, pNetMsg->dwFieldID, &NetMsgFB );
	}
	
	return TRUE;
}
BOOL GLAgentServer::MsgTowerWarsSetWinner ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_SERVER_TOWERWARS_WINNER_AG* pNetMsg = (GLMSG::SNETPC_SERVER_TOWERWARS_WINNER_AG*) nmg;

	GLTowerWars *pSW = GLTowerWarsAgentMan::GetInstance().Find ( pNetMsg->dwID );
	if ( pSW )
	{
		GLTowerWars &sSW = *pSW;
		sSW.m_wSchoolWinner = pNetMsg->wSCHOOL;

		GLMSG::SNET_TOWERWARS_WINNER_BRD NetMsgBrd;
		NetMsgBrd.wSCHOOL = sSW.m_wSchoolWinner;
		StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_TOWERWARS_WINNER_BRD::TEXT_LEN, sSW.m_strName.c_str() );
		SENDTOALLCLIENT ( &NetMsgBrd );

		GLTowerWarsAgentMan::GetInstance().SetLastWinner( sSW.m_wSchoolWinner );

		//send the winner info to all field servers
		GLMSG::SNET_TOWERWARS_WINNER_FLD NetMsgFld;
		NetMsgFld.dwID = pNetMsg->dwID;
		NetMsgFld.wWINNERSCHOOL = sSW.m_wSchoolWinner;
		SENDTOALLCHANNEL ( &NetMsgFld );

		if ( m_pConsoleMsg )
			m_pConsoleMsg->Write( "CTF:Set Winner Agent ID:%d School:%s", pNetMsg->dwID, GLCONST_CHAR::strSCHOOLNAME[pNetMsg->wSCHOOL].c_str() );
	}

	return TRUE;
}

HRESULT GLAgentServer::MsgProcess ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	switch ( nmg->nType )
	{
	default:										break;
	case NET_MSG_GCTRL_REQ_GATEOUT:					MsgReqGateOut ( nmg, dwClientID, dwGaeaID ); break;
	case NET_MSG_GCTRL_REQ_GENITEM_AGT:				MsgReqGenItemAgt ( nmg, dwClientID ); break;
	case NET_MSG_FIELDSVR_CHARCHK_FB:				MsgReqFieldSvrCharChkFb ( nmg, dwClientID, dwGaeaID ); break;
	case NET_MSG_SERVER_GENERALCHAT:				MsgServerGeneralChat ( nmg ); break;
	
	case NET_MSG_GCTRL_CONFRONTPTY_CHECKMBR_AGT:	MsgConfrontPtyCheckMber ( nmg ); break;
	case NET_MSG_GCTRL_CONFRONTCLB_CHECKMBR_AGT:	MsgConfrontClbCheckMber ( nmg ); break;

	case NET_MSG_GCTRL_CLUB_MEMBER_DB2DEL:			MsgClubMemberDb2Del ( nmg, dwClientID, dwGaeaID ); break;

	case NET_MSG_GCTRL_CLUB_CERTIFIED_AGT:			MsgClubCertified ( nmg, dwClientID, dwGaeaID ); break;
	//add sw buff
	case NET_MSG_GCTRL_SCHOOL_WARS_CERTIFIED_AGT:	MsgSwCertified ( nmg, dwClientID, dwGaeaID ); break;
	case NET_MSG_GCTRL_TOWERWARS_CERTIFIED_AGT:		MsgTowerWarsCertified ( nmg, dwClientID, dwGaeaID ); break;
	case NET_MSG_GCTRL_TOWERWARS_DOBATTLEEND_AGT:	MsgTowerWarsDoBattleEnd ( nmg, dwClientID, dwGaeaID ); break;
	case NET_MSG_GCTRL_TOWERWARS_LASTCAPTURE_AGT:	MsgTowerWarsLastCapture ( nmg, dwClientID, dwGaeaID ); break;
	case NET_MSG_GCTRL_REQ_TO_AGENT_TOWERWARS_WINNER:	MsgTowerWarsSetWinner( nmg ); break;

	case NET_MSG_GCTRL_CLUB_INCOME_MONEY_AGT:		MsgClubIncomeMoney ( nmg ); break;
	case NET_MSG_GCTRL_CLUB_INCOME_UP:				MsgClubIncomeMoneyUp ( nmg ); break;
	//case NET_MSG_GCTRL_CLUB_INCOME_FB:			MsgClubIncomeMoneyFb ( nmg ); break;
	case NET_MSG_GCTRL_2_FRIEND_AG:					Msg2FriendAG ( nmg ); break;
	case NET_MSG_GM_MOVE2CHAR_AG:					MsgMove2CharAG ( nmg ); break;
	case NET_MSG_GM_CHAR_INFO_FLD_FB:				MsgGmCharInfoFldFB ( nmg );	break;
	case NET_MSG_USER_CHAR_INFO_FLD_FB:				MsgUserCharInfoFldFB ( nmg );	break;
	case NET_MSG_GCTRL_CLUB_CD_CERTIFY_ING_BRD:		MsgClubCDCertifyIngBrd ( nmg ); break;
	case NET_MSG_WPE_DT_BRD:		                MsgWPEDetectedBrd ( nmg ); break; // Detect AutoPots Global Announcement - Eduj
	case NET_MSG_AP_DT_BRD:		                    MsgAPDetectedBrd ( nmg ); break; // Detect AutoPots Global Announcement - Eduj
//	case NET_MSG_GCTRL_INVEN_GRINDING_BRD:		    MsgGrindUpBrd ( nmg ); break; // global grind - Eduj
	case NET_MSG_INVEN_NONDROP_BRD:		            MsgNonDropBrd ( nmg ); break; //nondrop card Eduj
	case NET_MSG_INVEN_REMOVE_NONDROP_BRD:		    MsgRemoveNonDropBrd ( nmg ); break; //nondrop card Eduj
	case NET_MSG_GCTRL_CLUB_CD_CERTIFY_BRD:			MsgClubCDCertifyBrd ( nmg ); break;
	case NET_MSG_GCTRL_GLOBAL_SUCCESS_GRIND:			MsgGlobalSuccess	( nmg );			break;
	case NET_MSG_GCTRL_CLUB_BATTLE_KILL_UPDATE_AGT:		MsgClubBattleKillUpdate ( nmg );		break;
	case NET_MSG_GCTRL_CLUB_BATTLE_LAST_KILL_UPDATE_AGT:	MsgClubBattleLastKillUpdate ( nmg ); break;
	case NET_MSG_GCTRL_REQ_TAXI_NPCPOS_FB:			MsgReqTaxiNpcPos( nmg );					break;
	case NET_MSG_GCTRL_CREATE_INSTANT_MAP_REQ:		MsgReqCreateInstantMap ( nmg, dwClientID, dwGaeaID ); break;
	case NET_MSG_GCTRL_CREATE_INSTANT_MAP_DEL:		MsgReqDeleteInstantMap ( nmg );				break;
	case NET_MSG_GCTRL_NPC_COMMISSION:				MsgNpcCommission( nmg, dwClientID );		break;

	case NET_MSG_GCTRL_REQ_TO_AGENT_TOWERWARS_CAPTURE:	MsgTowerWarCapture ( nmg );			break;
	
	};

	if ( dwGaeaID == GAEAID_NULL )				return E_FAIL;
	if ( !GetChar(dwGaeaID) )					return E_FAIL;

	switch ( nmg->nType )
	{
	default:									break;

	case NET_MSG_REQ_FRIENDLIST:
	case NET_MSG_REQ_FRIENDADD:
	case NET_MSG_REQ_FRIENDADD_ANS:
	case NET_MSG_REQ_FRIENDDEL:
	case NET_MSG_REQ_FRIENDBLOCK:

	case NET_MSG_GCTRL_ACTSTATE:

	case NET_MSG_GCTRL_CLUB_MEMBER_REQ_2AGT:
	case NET_MSG_GCTRL_CLUB_MEMBER_DEL:
	case NET_MSG_GCTRL_CLUB_MEMBER_SECEDE:
	case NET_MSG_GCTRL_CLUB_AUTHORITY_REQ:
	case NET_MSG_GCTRL_CLUB_AUTHORITY_REQ_ANS:
	case NET_MSG_GCTRL_CLUB_MARK_INFO:
	case NET_MSG_GCTRL_CLUB_MARK_CHANGE:
	case NET_MSG_GCTRL_CLUB_RANK_2AGT:

	case NET_MSG_GCTRL_CLUB_COMMISSION:
	case NET_MSG_GCTRL_CLUB_NOTICE_REQ:
	case NET_MSG_GCTRL_CLUB_SUBMASTER:

	case NET_MSG_GCTRL_CLUB_ALLIANCE_REQ:
	case NET_MSG_GCTRL_CLUB_ALLIANCE_REQ_ANS:
	case NET_MSG_GCTRL_CLUB_ALLIANCE_DEL_REQ:
	case NET_MSG_GCTRL_CLUB_ALLIANCE_SEC_REQ:
	case NET_MSG_GCTRL_CLUB_ALLIANCE_DIS_REQ:

	case NET_MSG_GCTRL_CLUB_BATTLE_REQ:
	case NET_MSG_GCTRL_CLUB_BATTLE_REQ_ANS:
	case NET_MSG_GCTRL_CLUB_BATTLE_ARMISTICE_REQ:
	case NET_MSG_GCTRL_CLUB_BATTLE_ARMISTICE_REQ_ANS:
	case NET_MSG_GCTRL_CLUB_BATTLE_SUBMISSION_REQ:

	case NET_MSG_GCTRL_ALLIANCE_BATTLE_REQ:
	case NET_MSG_GCTRL_ALLIANCE_BATTLE_REQ_ANS:
	case NET_MSG_GCTRL_ALLIANCE_BATTLE_ARMISTICE_REQ:
	case NET_MSG_GCTRL_ALLIANCE_BATTLE_ARMISTICE_REQ_ANS:
	case NET_MSG_GCTRL_ALLIANCE_BATTLE_SUBMISSION_REQ:

	case NET_MSG_GCTRL_INVEN_RENAME_AGTBRD:
	case NET_MSG_SMS_PHONE_NUMBER_AGTBRD:
	case NET_MSG_GCTRL_UPDATE_STARTCALL:

	case NET_MSG_GCTRL_PUTON_CHANGE_AG:
	case NET_MSG_REQ_FRIEND_CLUB_OPEN:
	case NET_QBOX_OPTION_REQ_AG:
	case NET_MSG_REQ_ATTENDLIST:
	case NET_MSG_REQ_ATTENDANCE:
		{
			PGLCHARAG pMyChar = GetChar(dwGaeaID);
			pMyChar->MsgProcess ( nmg );
		}
		break;

	case NET_MSG_CHAT:							ChatMsgProc ( nmg, dwClientID, dwGaeaID );			break;
	case NET_MSG_CHAT_LOUDSPEAKER_AGT:			ChatMsgLoudSpeakerAgt ( nmg, dwClientID, dwGaeaID );break;
	case NET_MSG_GCTRL_REQ_REBIRTH:				MsgReqReBirth ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GCTRL_REGEN_GATE_FB:			MsgReqReGenGate ( nmg, dwClientID, dwGaeaID );		break;

	case NET_MSG_GCTRL_FIELDSVR_OUT_FB:			MsgFieldSvrOutFb ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GCTRL_REBIRTH_OUT_FB:			MsgReBirthOutFb ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GCTRL_REQ_RECALL_AG:			MsgReCallAg ( nmg, dwClientID, dwGaeaID );			break;
	case NET_MSG_REQ_MUST_LEAVE_MAP_AG:			MsgLvUpMustLeaveMap ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_GCTRL_REQ_TELEPORT_AG:			MsgTeleportAg ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GCTRL_REQ_SERVER_CLUB_BATTLE_REMAIN_AG:		MsgClubBattleRemainTime ( nmg );		break;
	case NET_MSG_GCTRL_REQ_SERVER_CLUB_DEATHMATCH_REMAIN_AG:	MsgClubDeathMatchRemainTime ( nmg );	break;
	case NET_MSG_GCTRL_REQ_SERVER_SCHOOL_WARS_REMAIN_AG:	MsgSchoolWarsRemainTime ( nmg );			break;
	case NET_MSG_GCTRL_REQ_SERVER_ROYAL_RUMBLE_REMAIN_AG:	MsgRoyalRumbleRemainTime (nmg );			break; //crashfix
	case NET_MSG_GCTRL_REQ_SERVER_TOWERWARS_REMAIN_AG:	MsgTowerWarsRemainTime ( nmg );				break;


	case NET_MSG_GCTRL_PARTY_LURE:				MsgPartyLure ( nmg, dwClientID, dwGaeaID );			break;
	case NET_MSG_GCTRL_PARTY_LURE_TAR_ANS:		MsgPartyLureTarAns ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_GCTRL_PARTY_SECEDE:			MsgPartySecede ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GCTRL_PARTY_AUTHORITY:			MsgPartyAuthority( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GCTRL_PARTY_DISSOLVE:			MsgPartyDissolve ( nmg, dwClientID, dwGaeaID );		break;

	case NET_MSG_GCTRL_2_FRIEND_REQ:			Msg2FriendReq ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GM_MOVE2CHAR:					MsgMove2Char ( nmg, dwClientID, dwGaeaID );			break;

	case NET_MSG_GCTRL_REQ_GATEOUT_FB:			MsgReqGateOutFB ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GCTRL_REQ_REBIRTH_FB:			MsgReqReBirthFB ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GCTRL_CREATE_INSTANT_MAP_FB:		MsgReqCreateInstantMapFB ( nmg, dwClientID, dwGaeaID );		break;

	case NET_MSG_GCTRL_CONFRONT:				MsgReqConfront ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GCTRL_CONFRONT_ANS:			MsgAnsConfront ( nmg, dwClientID, dwGaeaID );		break;

	case NET_MSG_GCTRL_CONFRONT_FB:				MsgAnsConfrontFB ( nmg, dwClientID, dwGaeaID );		break;

	case NET_MSG_GCTRL_CONFRONT_END2_AGT:		MsgConfrontEnd2Agt ( nmg, dwClientID, dwGaeaID );	break;

	case NET_MSG_GCTRL_CLUB_NEW_2AGT:			MsgClubNew2Agt ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GCTRL_CLUB_NEW_DB2AGT:			MsgClubNewDb2Agt ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GCTRL_CLUB_DISSOLUTION:		MsgClubDissolution ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_CHARPOS_FROMDB2AGT:			GameJoinToFieldSvr ( nmg, dwClientID, dwGaeaID );	break;


	case NET_MSG_SERVER_CTRL_WEATHER:			
	case NET_MSG_SERVER_CTRL_WEATHER2:			MsgServerCtrlWeather ( nmg, dwClientID, dwGaeaID );	break;
		
	case NET_MSG_SERVER_CTRL_GENITEMHOLD:		MsgServerCtrlGenHold ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_SERVER_CTRL_TIME:				MsgServerCtrlTime ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_SERVER_CTRL_MONTH:				MsgServerCtrlMonth ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_BLOCK_DETECTED:				MsgBlockDetected ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GM_KICK_USER:					MsgGmKickUser ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GM_MOVE2GATE:					MsgGMMove2Gate ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GM_MOVE2MAPPOS:				MsgGMMove2Pos ( nmg, dwClientID, dwGaeaID );		break;

	case NET_MSG_GM_EVENT_ITEM_GEN:				MsgGmEventItemGen ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_GM_EVENT_ITEM_GEN_END:			MsgGmEventItemGenEnd ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_GM_EVENT_MONEY_GEN:			MsgGmEventMoneyGen ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_GM_EVENT_MONEY_GEN_END:		MsgGmEventMoneyGenEnd ( nmg, dwClientID, dwGaeaID );break;
	case NET_MSG_GM_CLASS_EVENT:				MsgGmEventClassEvent ( nmg, dwClientID, dwGaeaID ); break;
	//add sw buff
	case NET_MSG_GM_SCHOOL_EVENT:				MsgGmEventSchoolEvent ( nmg, dwClientID, dwGaeaID ); break;
	case NET_MSG_GM_EVENT_EX:					MsgGmEventEx ( nmg, dwClientID, dwGaeaID );			break;
	case NET_MSG_GM_EVENT_EX_END:				MsgGmEventExEnd ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GM_EVENT_EXP:					MsgGmEventExp( nmg, dwClientID, dwGaeaID );			break;
	case NET_MSG_GM_EVENT_EXP_END:				MsgGmEventExpEnd( nmg, dwClientID, dwGaeaID );		break;

	case NET_MSG_GM_VIEWWORKEVENT:				MsgGmViewWorkEvent( nmg, dwClientID, dwGaeaID );		break;

	case NET_MSG_GM_LIMIT_EVENT_BEGIN:			MsgGmLimitEventBegin ( nmg, dwClientID, dwGaeaID ); break;
	case NET_MSG_GM_LIMIT_EVENT_END:			MsgGmLimitEventEnd ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_GM_LIMIT_EVENT_RESTART:		MsgGmLimitEventRestart ( nmg, dwClientID, dwGaeaID ); break;
	case NET_MSG_GM_LIMIT_EVENT_TIME_REQ:       MsgGmLimitEventTimeReq ( nmg, dwClientID, dwGaeaID ); break; 
	case NET_MSG_CYBERCAFECLASS_UPDATE:			MsgCyberCafeClassUpdate ( nmg, dwClientID, dwGaeaID ); break; 

	case NET_MSG_MARKET_CHECKTIME:				MsgMarketOpenCheck( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_PVP_REJOIN:			        MsgCTFRejoin ( nmg, dwClientID, dwGaeaID );	break;

	case NET_MSG_TYRANNY_PARTICIPATE:			MsgCTFParticipate ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_GM_BIGHEAD:					MsgGmBigHead ( nmg, dwClientID, dwGaeaID );			break;
	case NET_MSG_GM_BIGHAND:					MsgGmBigHand ( nmg, dwClientID, dwGaeaID );			break;
	case NET_MSG_GM_CHAT_BLOCK_UACCOUNT:		MsgGmChatBlockUA ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GM_CHAT_BLOCK_CHARNAME:		MsgGmChatBlockCN ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GM_CHAT_BLOCK_CHARID:			MsgGmChatBlockCI ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_USER_CHAR_INFO_4NAME:			MsgUserCharInfo4NAME ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_GM_CHAR_INFO_4NAME:			MsgGmCharInfo4NAME ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_GM_CHAR_INFO_4CHARID:			MsgGmCharInfo4CID ( nmg, dwClientID, dwGaeaID );	break;

	case NET_MSG_GM_FREEPK:						MsgGmFreePK ( nmg, dwClientID, dwGaeaID );			break;
	case NET_MSG_GM_VIEWALLPLAYER:				MsgGmViewAllPlayer ( nmg, dwClientID, dwGaeaID );   break;

	case NET_MSG_GM_GENCHAR:					MsgGmGenChar ( nmg, dwClientID, dwGaeaID );			break;
	case NET_MSG_GM_MOB_GEN:					MsgGmGenMob ( nmg, dwClientID, dwGaeaID );			break;
	case NET_MSG_GM_MOB_GEN_EX:					MsgGmGenMobEx ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GM_MOB_DEL_EX:					MsgGmDelMobEx ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GM_MOB_DEL:					MsgGmDelMob ( nmg, dwClientID, dwGaeaID );			break;
	case NET_MSG_GM_MOB_LEVEL:					MsgGmMobLevel ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GM_MOB_LEVEL_CLEAR:			MsgGmMobLevelClear ( nmg, dwClientID, dwGaeaID );	break;
	case NET_MSG_GM_WHERE_NPC:					MsgGmWhereNPC ( nmg, dwClientID, dwGaeaID );		break;

	case NET_MSG_GM_PRINT_CROWLIST:				MsgGmPrintCrowList ( nmg, dwClientID, dwGaeaID );	break;

	case NET_MSG_GM_WARNING_MSG:				MsgGmWarningMSG ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GM_SLOT_EVENT:					MsgGmSlotEVENT ( nmg, dwClientID, dwGaeaID );		break;
	case NET_MSG_GM_SHOWMETHEMONEY:				MsgGmShowMeTheMoney ( nmg, dwClientID, dwGaeaID );	break;

	case NET_MSG_GM_GETWHISPERMSG:				MsgGetWhisperMsg( nmg, dwClientID, dwGaeaID );      break;
	case NET_MSG_GCTRL_REQ_TAXI:				MsgReqTaxi( nmg, dwClientID, dwGaeaID );			break;
	};

	return S_OK;
}
BOOL GLAgentServer::MsgTowerWarCapture ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_SERVER_TOWERWARS_CAPTURE_AG* pNetMsg = (GLMSG::SNETPC_SERVER_TOWERWARS_CAPTURE_AG*) nmg;

	GLTowerWars *pSW = GLTowerWarsAgentMan::GetInstance().Find ( pNetMsg->dwID );
	if ( pSW )
	{
		GLMSG::SNET_TOWERWARS_CAPTURE_BRD NetMsgBrd;
		NetMsgBrd.emHOLDER = pNetMsg->emHOLDER;
		NetMsgBrd.sID = pNetMsg->sID;
		StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_TOWERWARS_CAPTURE_BRD::TEXT_LEN, pNetMsg->szName );
		StringCchCopy ( NetMsgBrd.szNameCrow, GLMSG::SNET_TOWERWARS_CAPTURE_BRD::TEXT_LEN, pNetMsg->szNameCrow );
		SENDTOALLCLIENT ( &NetMsgBrd );

		if ( m_pConsoleMsg )
			m_pConsoleMsg->Write( "SCHOOLWARINFO: Capture Agent ID:%d Name:%s School:%s Crow:(%d~%d)%s", 
			pNetMsg->dwID, 
			NetMsgBrd.szName,
			GLCONST_CHAR::strSCHOOLNAME[NetMsgBrd.emHOLDER].c_str(), 
			pNetMsg->sID.wMainID, 
			pNetMsg->sID.wSubID,
			pNetMsg->szNameCrow 
			);
	}

	return TRUE;
}
BOOL GLAgentServer::MsgTowerWarsLastCapture ( NET_MSG_GENERIC* nmg, DWORD dwClientID, DWORD dwGaeaID )
{
	GLMSG::SNET_TOWERWARS_LASTCAPTURE_AGT *pNetMsg = (GLMSG::SNET_TOWERWARS_LASTCAPTURE_AGT *) nmg;

	//bool bOK = GLTowerWarsAgentMan::GetInstance().EndBattle( pNetMsg->dwID, pNetMsg->dwSCHOOL, pNetMsg->bEnd );
	//if ( !bOK )		return FALSE;

	GLTowerWars *pSW = GLTowerWarsAgentMan::GetInstance().Find ( pNetMsg->dwID );
	if ( pSW )
	{
		GLMSG::SNET_TOWERWARS_LASTCAPTURE_BRD NetMsgBrd;
		NetMsgBrd.dwID = pNetMsg->dwID;
		NetMsgBrd.dwSCHOOL = pNetMsg->dwSCHOOL;
		NetMsgBrd.bLastCapture = pNetMsg->bLastCapture;
		SENDTOALLCHANNEL ( &NetMsgBrd );
	}

	return TRUE;
}
