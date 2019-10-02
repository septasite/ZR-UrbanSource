#include "stdafx.h"
#include "./GLChar.h"
#include "./GLGaeaServer.h"
#include "./GLQUEST.h"
#include "./GLSchoolFreePK.h"
#include "GLTowerWars/GLTowerWars.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HRESULT GLChar::MsgGameJoin ()
{
	// ≈¨∂Û¿Ãæ∆Æø° ¿ÅE€ : ƒ≥∏Ø≈Õ¡§∫∏ + Ω∫≈≥ + æ∆¿Ã≈€

//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	GLMSG::SNETLOBBY_CHARJOIN NetCharJoin;

	StringCchCopy ( NetCharJoin.szUserID , USR_ID_LENGTH+1, m_szUID );

	NetCharJoin.dwClientID	= m_dwClientID;
	NetCharJoin.dwGaeaID	= m_dwGaeaID;
	NetCharJoin.sMapID		= m_sMapID;
	NetCharJoin.vPos		= m_vPos;
	NetCharJoin.Data		= GETCHARDATA();

	NetCharJoin.wSKILLQUICK_ACT = m_wSKILLQUICK_ACT;
	memcpy ( NetCharJoin.sSKILLQUICK, m_sSKILLQUICK, sizeof(SNATIVEID)*EMSKILLQUICK_SIZE );
	memcpy ( NetCharJoin.sACTIONQUICK, m_sACTIONQUICK, sizeof(SACTION_SLOT)*EMACTIONQUICK_SIZE );

	NetCharJoin.dwNumInvenItems = m_cInventory.GetNumItems();
#if defined(VN_PARAM) //vietnamtest%%%
	NetCharJoin.dwNumVNInvenItems = m_cVietnamInventory.GetNumItems();
#endif

#if defined(TW_PARAM) || defined(_RELEASED) || defined(HK_PARAM) || defined ( TH_PARAM ) // ***Tracing Log print
	NetCharJoin.bTracingChar	  = m_bTracingUser;
#endif

	NetCharJoin.dwNumSkill = static_cast<DWORD>(m_ExpSkills.size());
	
	NetCharJoin.dwNumQuestProc = static_cast<DWORD>(m_cQuestPlay.GetQuestProc().size());
	NetCharJoin.dwNumQuestEnd = static_cast<DWORD>(m_cQuestPlay.GetQuestEnd().size());
	NetCharJoin.dwChargeItem = static_cast<DWORD>(m_mapCharged.size());
	NetCharJoin.dwItemCoolTime = static_cast<DWORD> ( m_mapCoolTimeID.size() + m_mapCoolTimeType.size() );

	NetCharJoin.bBIGHEAD = m_pGLGaeaServer->m_bBigHead;
	NetCharJoin.bBIGHAND = m_pGLGaeaServer->m_bBigHand;

	NetCharJoin.sStartMapID		 = m_sStartMapID;
	NetCharJoin.dwStartGate		 = m_dwStartGate;
	NetCharJoin.sLastCallMapID	 = m_sLastCallMapID;
	NetCharJoin.vLastCallPos	 = m_vLastCallPos;
	NetCharJoin.dwThaiCCafeClass = m_dwThaiCCafeClass;
	// ∏ª∑π¿ÃΩ√æ∆ PCπÅE¿Ã∫•∆Æ
	NetCharJoin.nMyCCafeClass	 = m_nMyCCafeClass;

	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetCharJoin );

	// ƒ…∏Ø≈Õ ¬¯øÅEæ∆¿Ã≈€.
//	GLMSG::SNETLOBBY_CHARPUTON NetMsgCharPutOn; 
//	memcpy ( NetMsgCharPutOn.PutOnItems, m_PutOnItems, sizeof(SITEMCUSTOM)*SLOT_TSIZE );
//	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgCharPutOn );

	// BuffSize √ ∞˙∑Œ «—∞≥æø ∫∏≥ª¥¬ ∞…∑Œ ºˆ¡§
	for ( int i = 0; i < SLOT_TSIZE; ++i )
	{
		GLMSG::SNETLOBBY_CHARPUTON_EX NetMsgCharPutOnEx; 
		NetMsgCharPutOnEx.PutOnItem = m_PutOnItems[i];
		NetMsgCharPutOnEx.nSlot = i;
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgCharPutOnEx );
	}

	// ≈¨∂Û¿Ãæ∆Æø° ¿Œ∫•≈‰∏Æ ¿ÅE€
	// ∑Á«¡∏¶ µπ∏Èº≠ «œ≥™æø ¿ÅE€
	{
		GLInventory::CELL_MAP_ITER iter = m_cInventory.GetItemList()->begin();
		GLInventory::CELL_MAP_ITER iter_end = m_cInventory.GetItemList()->end();
		for ( ; iter!=iter_end; ++iter )
		{
			SINVENITEM* pInvenItem = (*iter).second;

			GLMSG::SNETLOBBY_INVENITEM NetInvenItem;
			NetInvenItem.Data = *pInvenItem;
			
			m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetInvenItem );
		}
	}

#if defined(VN_PARAM) //vietnamtest%%%
	// ≈¨∂Û¿Ãæ∆Æø° ∫£∆Æ≥≤ ¿Œ∫•≈‰∏Æ ¿ÅE€
	// ∑Á«¡∏¶ µπ∏Èº≠ «œ≥™æø ¿ÅE€
	{
		GLInventory::CELL_MAP_ITER iter = m_cVietnamInventory.GetItemList()->begin();
		GLInventory::CELL_MAP_ITER iter_end = m_cVietnamInventory.GetItemList()->end();
		for ( ; iter!=iter_end; ++iter )
		{
			SINVENITEM* pInvenItem = (*iter).second;

			GLMSG::SNETLOBBY_VIETNAM_INVENITEM NetInvenItem;
			NetInvenItem.Data = *pInvenItem;

			m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetInvenItem );
		}
	}
#endif

	//	πËøÅEΩ∫≈≥∏Ò∑œ ∏µŒ ¿ÅE€.
	//
	{
		GLMSG::SNETLOBBY_CHARSKILL NetSkill;

		SKILL_MAP_ITER iter = m_ExpSkills.begin();
		SKILL_MAP_ITER iter_end = m_ExpSkills.end();
		for ( ; iter!=iter_end; ++iter )
		{
			const SCHARSKILL &sSkill = (*iter).second;

			NetSkill.ADD ( sSkill );
			if ( NetSkill.wNum == EMGLMSG_SKILLMAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetSkill );
				NetSkill.wNum = 0;
			}
		}

		if ( NetSkill.wNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetSkill );
	}

	//	¡¯«‡¡ﬂ¿Œ ƒ˘Ω∫∆Æ ∏µŒ ¿ÅE€.
	{
		GLQuestPlay::MAPQUEST_ITER iter = m_cQuestPlay.GetQuestProc().begin();
		GLQuestPlay::MAPQUEST_ITER iter_end = m_cQuestPlay.GetQuestProc().end();
		for ( ; iter!=iter_end; ++iter )
		{
			GLQUESTPROG *pPROG = (*iter).second;

			CByteStream cByteStream;
			pPROG->SET_BYBUFFER ( cByteStream );

			LPBYTE pBuff(NULL);
			DWORD dwSize(0);
			cByteStream.GetBuffer ( pBuff, dwSize );

			GLMSG::SNETLOBBY_QUEST_PROG NetMsg;
			NetMsg.SETSTREAM ( pBuff, dwSize );
			m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsg );
		}
	}

	//	øœ∑·µ» ƒ˘Ω∫∆Æ ∏µŒ ¿ÅE€.
	{
		GLQuestPlay::MAPQUEST_ITER iter = m_cQuestPlay.GetQuestEnd().begin();
		GLQuestPlay::MAPQUEST_ITER iter_end = m_cQuestPlay.GetQuestEnd().end();
		for ( ; iter!=iter_end; ++iter )
		{
			GLQUESTPROG *pPROG = (*iter).second;

			CByteStream cByteStream;
			pPROG->SET_BYBUFFER ( cByteStream );

			LPBYTE pBuff(NULL);
			DWORD dwSize(0);
			cByteStream.GetBuffer ( pBuff, dwSize );

			GLMSG::SNETLOBBY_QUEST_END NetMsg;
			NetMsg.SETSTREAM ( pBuff, dwSize );
			m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsg );
		}
	}

	//	æ∆¿Ã≈€ ƒ≈∏¿” ¿ÅE€
	//
	{
		GLMSG::SNETLOBBY_ITEM_COOLTIME NetCoolTime;

		COOLTIME_MAP_ITER iter = m_mapCoolTimeID.begin();
		COOLTIME_MAP_ITER iter_end = m_mapCoolTimeID.end();

		NetCoolTime.emCoolType = EMCOOL_ITEMID;

		for ( ; iter!=iter_end; ++iter )
		{
			const ITEM_COOLTIME &sCoolTime = (*iter).second;

			NetCoolTime.ADD ( sCoolTime );
			if ( NetCoolTime.dwNum == EMGLMSG_COOLTIMEMAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetCoolTime );
				NetCoolTime.dwNum = 0;
			}
		}

		if ( NetCoolTime.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetCoolTime );

		iter = m_mapCoolTimeType.begin();
		iter_end = m_mapCoolTimeType.end();

		NetCoolTime.emCoolType = EMCOOL_ITEMTYPE;
		NetCoolTime.dwNum = 0;

		for ( ; iter!=iter_end; ++iter )
		{
			const ITEM_COOLTIME &sCoolTime = (*iter).second;

			NetCoolTime.ADD ( sCoolTime );
			if ( NetCoolTime.dwNum == EMGLMSG_COOLTIMEMAX )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetCoolTime );
				NetCoolTime.dwNum = 0;
			}
		}

		if ( NetCoolTime.dwNum != 0 )	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetCoolTime );
	}
/*
	//	æ∆¿Ã≈€ òﬁø°º≠ ±∏¿‘«— π∞«∞ ∏Ò∑œ.
	{
		MAPSHOP_ITER pos = m_mapCharged.begin();
		MAPSHOP_ITER end = m_mapCharged.end();
		for ( ; pos!=end; ++pos )
		{
			SHOPPURCHASE &sPURCHASE = (*pos).second;

			GLMSG::SNETLOBBY_CHARGE_ITEM NetMsg;
			StringCchCopy ( NetMsg.szPurKey, PURKEY_LENGTH+1, sPURCHASE.strPurKey.GetString() );
			NetMsg.nidITEM = SNATIVEID(sPURCHASE.wItemMain,sPURCHASE.wItemSub);
			m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsg );
		}
	}
*/
	//	≈¨∑¥ ¡§∫∏ ¿ÅE€.
	{
		GLClubMan& cClubMan = m_pGLGaeaServer->GetClubMan();
		GLCLUB *pCLUB = cClubMan.GetClub ( m_dwGuild );

		GLMSG::SNETLOBBY_CLUB_INFO NetMsgInfo;
		NetMsgInfo.dwClubID = m_dwGuild;

		if ( pCLUB )
		{
			StringCchCopy ( NetMsgInfo.szClubName, CHAR_SZNAME, pCLUB->m_szName );

			NetMsgInfo.dwMasterID = pCLUB->m_dwMasterID;
			StringCchCopy ( NetMsgInfo.szMasterName, CHAR_SZNAME, pCLUB->m_szMasterName );
			NetMsgInfo.dwCDCertifior = pCLUB->m_dwCDCertifior;

			NetMsgInfo.dwRank = pCLUB->m_dwRank;;

			NetMsgInfo.dwMarkVER = pCLUB->m_dwMarkVER;

			NetMsgInfo.tOrganize = pCLUB->m_tOrganize;
			NetMsgInfo.tDissolution = pCLUB->m_tDissolution;

			NetMsgInfo.dwAlliance = pCLUB->m_dwAlliance;

			NetMsgInfo.dwMEMBER_NUM = pCLUB->GetNemberNum();
			NetMsgInfo.dwALLIANCE_NUM = pCLUB->GetAllianceNum();
			NetMsgInfo.dwBATTLE_NUM = pCLUB->GetBattleNum();

			NetMsgInfo.dwBattleWin	= pCLUB->m_dwBattleWin;
			NetMsgInfo.dwBattleLose	= pCLUB->m_dwBattleLose;
			NetMsgInfo.dwBattleDraw	= pCLUB->m_dwBattleDraw;

			if ( pCLUB->m_dwAlliance!=CLUB_NULL )
			{
				GLCLUB *pCLUB_A = cClubMan.GetClub ( pCLUB->m_dwAlliance );
				if ( pCLUB_A )
				{
					NetMsgInfo.dwALLIANCE_NUM = pCLUB_A->GetAllianceNum();
					NetMsgInfo.dwAllianceBattleWin	= pCLUB_A->m_dwAllianceBattleWin;
					NetMsgInfo.dwAllianceBattleLose	= pCLUB_A->m_dwAllianceBattleLose;
					NetMsgInfo.dwAllianceBattleDraw	= pCLUB_A->m_dwAllianceBattleDraw;
				}
			}

			StringCchCopy ( NetMsgInfo.szNotice, EMCLUB_NOTICE_LEN+1, pCLUB->m_szNotice );
		}

		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgInfo );

		if ( pCLUB )
		{
			GLMSG::SNETLOBBY_CLUB_MEMBER NetMsgMember;

			CLUBMEMBERS_ITER pos = pCLUB->m_mapMembers.begin();
			CLUBMEMBERS_ITER end = pCLUB->m_mapMembers.end();
			for ( ; pos!=end; ++pos )
			{
				const GLCLUBMEMBER &sMEMBER = (*pos).second;
				bool bOK = NetMsgMember.ADDMEMBER ( sMEMBER.dwID, sMEMBER.m_dwFlags, sMEMBER.m_szName );
				if ( !bOK )
				{
					//	Note : ∏ﬁΩ√¡ÅE¿ÅE€.
					m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgMember );
					NetMsgMember.RESET();

					NetMsgMember.ADDMEMBER ( sMEMBER.dwID, sMEMBER.m_dwFlags, sMEMBER.m_szName );
				}
			}

			//	Note : ∏ﬁΩ√¡ÅE¿ÅE€.
			if ( NetMsgMember.dwMemberNum > 0 )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgMember );
				NetMsgMember.RESET();
			}
		}

		if ( pCLUB )
		{
			if ( pCLUB->m_dwAlliance!=CLUB_NULL )
			{
				GLClubMan& cClubMan = m_pGLGaeaServer->GetClubMan();
				GLCLUB *pCLUB_A = cClubMan.GetClub ( pCLUB->m_dwAlliance );
				if ( pCLUB_A )
				{
					GLMSG::SNETLOBY_CLUB_ANCE_2CLT NetMsgAlliance;

					CLUB_ALLIANCE_ITER pos = pCLUB_A->m_setAlliance.begin();
					CLUB_ALLIANCE_ITER end = pCLUB_A->m_setAlliance.end();
					for ( ; pos!=end; ++pos )
					{
						const GLCLUBALLIANCE &sALLIANCE = (*pos);

						bool bOK = NetMsgAlliance.ADDALLIANCE ( sALLIANCE.m_dwID, sALLIANCE.m_szName );
						if ( !bOK )
						{
							//	Note : ∏ﬁΩ√¡ÅE¿ÅE€.
							m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgAlliance );
							NetMsgAlliance.RESET();

							NetMsgAlliance.ADDALLIANCE ( sALLIANCE.m_dwID, sALLIANCE.m_szName );
						}
					}

					//	Note : ∏ﬁΩ√¡ÅE¿ÅE€.
					if ( NetMsgAlliance.dwAllianceNum > 0 )
					{
						m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgAlliance );
						NetMsgAlliance.RESET();
					}
				}
			}
		}

		if ( pCLUB )
		{
			GLMSG::SNETLOBBY_CLUB_BATTLE NetMsgBattle;

			CLUB_BATTLE_ITER pos = pCLUB->m_mapBattle.begin();
			CLUB_BATTLE_ITER end = pCLUB->m_mapBattle.end();
			for ( ; pos!=end; ++pos )
			{
				const GLCLUBBATTLE &sBattle = (*pos).second;
				GLCLUBBATTLE_LOBY sBattleLoby = sBattle;
				bool bOK = NetMsgBattle.ADDBATTLE ( sBattleLoby );
				if ( !bOK )
				{
					//	Note : ∏ﬁΩ√¡ÅE¿ÅE€.
					m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgBattle );
					NetMsgBattle.RESET();

					NetMsgBattle.ADDBATTLE ( sBattleLoby );
				}
			}

			//	Note : ∏ﬁΩ√¡ÅE¿ÅE€.
			if ( NetMsgBattle.dwBattleNum > 0 )
			{
				m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgBattle );
				NetMsgBattle.RESET();
			}
		}
	}

	return S_OK;
}

HRESULT GLChar::MsgClubInfo ()
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	GLClubMan& cClubMan = m_pGLGaeaServer->GetClubMan();
	GLCLUB *pCLUB = cClubMan.GetClub ( m_dwGuild );
	if ( !pCLUB )	return S_OK;

	GLMSG::SNET_CLUB_INFO_2CLT NetMsgInfo;
	NetMsgInfo.dwClubID = m_dwGuild;

	StringCchCopy ( NetMsgInfo.szClubName, CHAR_SZNAME, pCLUB->m_szName );

	NetMsgInfo.dwMasterID = pCLUB->m_dwMasterID;
	StringCchCopy ( NetMsgInfo.szMasterName, CHAR_SZNAME, pCLUB->m_szMasterName );
	NetMsgInfo.dwCDCertifior = pCLUB->m_dwCDCertifior;

	StringCchCopy ( NetMsgInfo.szNickName, CHAR_SZNAME, m_szNick );

	NetMsgInfo.dwMarkVER = pCLUB->m_dwMarkVER;
	NetMsgInfo.dwRank = pCLUB->m_dwRank;

	NetMsgInfo.tOrganize = pCLUB->m_tOrganize;
	NetMsgInfo.tDissolution = pCLUB->m_tDissolution;
	StringCchCopy ( NetMsgInfo.szNotice, EMCLUB_NOTICE_LEN+1, pCLUB->m_szNotice );

	m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgInfo );

	GLMSG::SNET_CLUB_MEMBER_2CLT NetMsgMember;
	CLUBMEMBERS_ITER pos = pCLUB->m_mapMembers.begin();
	CLUBMEMBERS_ITER end = pCLUB->m_mapMembers.end();
	for ( ; pos!=end; ++pos )
	{
		const GLCLUBMEMBER &sMEMBER = (*pos).second;
		bool bFULL = NetMsgMember.ADDMEMBER ( sMEMBER.dwID, sMEMBER.m_dwFlags, sMEMBER.m_szName );
		if ( bFULL )
		{
			//	Note : ∏ﬁΩ√¡ÅE¿ÅE€.
			m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgMember );
			NetMsgMember.RESET();

			NetMsgMember.ADDMEMBER ( sMEMBER.dwID, sMEMBER.m_dwFlags, sMEMBER.m_szName );
		}
	}

	//	Note : ∏ﬁΩ√¡ÅE¿ÅE€.
	if ( NetMsgMember.dwMemberNum > 0 )
	{
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgMember );
		NetMsgMember.RESET();
	}

	return S_OK;
}

NET_MSG_GENERIC* GLChar::ReqNetMsg_Drop ()
{
	static GLMSG::SNETDROP_PC NetMsg;
	NetMsg = GLMSG::SNETDROP_PC();

	SDROP_CHAR &dropChar = NetMsg.Data;

	StringCchCopy ( dropChar.szName, CHAR_SZNAME, m_szName );
	dropChar.emTribe	= m_emTribe;
	dropChar.emClass	= m_emClass;
	dropChar.wSchool	= m_wSchool;
	dropChar.wHair		= m_wHair;
	dropChar.wHairColor = m_wHairColor;
	dropChar.wFace		= m_wFace;
	dropChar.wSex		= m_wSex;
	dropChar.nBright	= m_nBright;
	dropChar.nChaReborn	= m_nChaReborn;

	dropChar.m_dwPkWin	= m_dwPkWin; //add pkrank
	dropChar.m_dwPkStreak = m_dwPkStreak; //add pk streak by njd

	dropChar.dwSummonGUID = m_dwSummonGUID;

	dropChar.dwCharID	= m_dwCharID;
	dropChar.wLevel		= m_wLevel;
	dropChar.dwGuild	= m_dwGuild;

	dropChar.m_bItemShopOpen = m_bItemShopOpen;
	dropChar.m_dwANISUBTYPE = m_dwANISUBSELECT;

	dropChar.m_dwPkWin = m_dwPkWin; //add pkrank

//	dropChar.m_bRankName = m_bRankName; //add pkrank
//	dropChar.m_bRankMark = m_bRankMark; //add pkrank

	//dropChar.m_dwReborn = m_dwReborn;

	dropChar.m_sStats = m_sSUMSTATS;
	dropChar.m_nSUM_HIT = m_nSUM_HIT;
	dropChar.m_nSUM_AVOID = m_nSUM_AVOID;
	dropChar.m_gdDAMAGE_PHYSIC = m_gdDAMAGE_PHYSIC;
	dropChar.m_nDEFENSE_SKILL = m_nDEFENSE_SKILL;
	dropChar.m_wSUM_AP = m_wSUM_AP;
	dropChar.m_wSUM_DP = m_wSUM_DP;
	dropChar.m_wSUM_PA = m_wSUM_PA;
	dropChar.m_wSUM_SA = m_wSUM_SA;
	dropChar.m_wSUM_MA = m_wSUM_MA;

	dropChar.m_dwPkLoss = m_dwPkLoss;
	dropChar.m_lnMoney = m_lnMoney;
	dropChar.m_lnVoteP = m_lnVoteP;
	dropChar.m_lnPremP = m_lnPremP;
	dropChar.m_lnContribP = m_lnContribP; //add contributionpoint by CNDev

	if ( dropChar.dwGuild!=CLUB_NULL )
	{
		GLClubMan &cClubMan = m_pGLGaeaServer->GetClubMan();
		GLCLUB *pCLUB = cClubMan.GetClub ( dropChar.dwGuild );
		if ( pCLUB )
		{
			dropChar.dwGuildMarkVer = pCLUB->m_dwMarkVER;
			dropChar.dwGuildMaster = pCLUB->m_dwMasterID;			
			if ( pCLUB->IsMemberFlgCDCertify ( m_dwCharID ) )	dropChar.dwFLAGS |= SDROP_CHAR::CLUB_CD;

			StringCchCopy ( dropChar.szClubName, CHAR_SZNAME, pCLUB->m_szName );
			
			dropChar.dwAlliance = pCLUB->m_dwAlliance;
		}
//		else
//		{
//			TEXTCONSOLEMSG_WRITE ( _T("ERROR : CLUBID_ERROR CharID %d ClubID %d"), m_dwCharID, m_dwGuild );
//		}

		StringCchCopy ( dropChar.szNick, CHAR_SZNAME, m_szNick );

	}

	if ( m_dwPartyID!=GAEAID_NULL )
	{
		const GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
		if ( pParty )
		{
			dropChar.dwParty = m_dwPartyID;
			dropChar.dwPMasterID = pParty->m_dwMASTER;
		}
	}

	dropChar.sHP		= m_sHP;
	dropChar.sMP		= m_sMP;
	dropChar.sSP		= m_sSP;
	dropChar.sSUMRESIST_SKILL = m_sSUMRESIST_SKILL;
	dropChar.dwGaeaID	= m_dwGaeaID;
	dropChar.sMapID		= m_sMapID;
	dropChar.dwCeID		= m_dwCeID;
	dropChar.vPos		= m_vPos;
	dropChar.vDir		= m_vDir;

	dropChar.Action		= m_Action;
	dropChar.dwActState	= m_dwActState;
	dropChar.vTarPos	= m_TargetID.vPos;

	if ( dropChar.Action==GLAT_MOVE )
	{
		if ( m_actorMove.PathIsActive() )
		{
			dropChar.vTarPos = m_actorMove.GetTargetPosition();
		}
		else
		{
			dropChar.Action = GLAT_IDLE;
		}
	}

	for ( int i=0; i<SKILLFACT_SIZE; ++i )		dropChar.sSKILLFACT[i].Assign ( m_sSKILLFACT[i], i );
	for ( int i=0; i<EMBLOW_MULTI; ++i )		dropChar.sSTATEBLOWS[i] = m_sSTATEBLOWS[i];
	for ( int i=0; i<SLOT_NSIZE_S_2; i++ )		dropChar.m_PutOnItems[i].Assign ( m_PutOnItems[i] );

	std::set<int>::iterator iter_EffNum;
	iter_EffNum = m_setLandEffectNum.begin();
	for( ; iter_EffNum != m_setLandEffectNum.end(); ++iter_EffNum )
	{
		if( i >= EMLANDEFFECT_MULTI ) break;
		dropChar.nLandEffect[i] = *iter_EffNum;
	}
	

	dropChar.m_bUseArmSub = m_bUseArmSub;

	if ( m_fGenAge < 0.6f )
		dropChar.dwFLAGS |= SDROP_CHAR::CHAR_GEN;

	dropChar.sPASSIVE_SKILL = m_sSUM_PASSIVE;

	dropChar.sQITEMFACT = m_sQITEMFACT;
	dropChar.sEVENTFACT = m_pGLGaeaServer->m_sEVENTFACT;


	if ( m_sVehicle.IsActiveValue() )
	{
		dropChar.m_bVehicle = m_bVehicle;
		dropChar.m_sVehicle.m_dwGUID = m_sVehicle.m_dwGUID;
		dropChar.m_sVehicle.m_emTYPE = m_sVehicle.m_emTYPE;
		dropChar.m_sVehicle.m_sVehicleID = m_sVehicle.m_sVehicleID;
		dropChar.m_sVehicle.m_wColor = m_sVehicle.m_wColor; //add bike color

		for ( int i =0; i < ACCE_TYPE_SIZE; ++i )
		{
			dropChar.m_sVehicle.m_PutOnItems[i].Assign( m_sVehicle.m_PutOnItems[i] );
		}
	}


	return (NET_MSG_GENERIC*) &NetMsg;
}

void GLChar::SETFIELDPET ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<m_pGLGaeaServer->GetMaxClient());
	GASSERT(pFIELDCROW->emCROW==CROW_PET);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=m_pGLGaeaServer->GetMaxClient() )	
	{
		CDebugSet::ToListView ( "OutOf PetGUID : %d in GlChar::SETFIELDPET()", pFIELDCROW->dwID );
		return;
	}
	if ( pFIELDCROW->emCROW!=CROW_PET )									return;

	m_arrayFieldPET[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::SETFIELDSUMMON ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<m_pGLGaeaServer->GetMaxClient());
	GASSERT(pFIELDCROW->emCROW==CROW_SUMMON);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=m_pGLGaeaServer->GetMaxClient() )	
	{
		CDebugSet::ToListView ( "OutOf PetGUID : %d in GlChar::SETFIELDPET()", pFIELDCROW->dwID );
		return;
	}
	if ( pFIELDCROW->emCROW!=CROW_SUMMON )									return;

	m_arrayFieldSummon[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::SETFIELDPC ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<m_pGLGaeaServer->GetMaxClient());
	GASSERT(pFIELDCROW->emCROW==CROW_PC);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=m_pGLGaeaServer->GetMaxClient() )		return;
	if ( pFIELDCROW->emCROW!=CROW_PC )									return;

	m_arrayFieldPC[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::SETFIELDCROW ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<MAXCROW);
	GASSERT(pFIELDCROW->emCROW==CROW_MOB);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=MAXCROW )									return;
	if ( pFIELDCROW->emCROW!=CROW_MOB )									return;

	m_arrayFieldCROW[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::SETFIELDMATERIAL ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<MAXCROW);
	GASSERT(pFIELDCROW->emCROW==CROW_MATERIAL);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=MAXCROW )									return;
	if ( pFIELDCROW->emCROW!=CROW_MATERIAL )							return;

	m_arrayFieldMATERIAL[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::SETFIELDITEM ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<MAXITEM);
	GASSERT(pFIELDCROW->emCROW==CROW_ITEM);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=MAXITEM )									return;
	if ( pFIELDCROW->emCROW!=CROW_ITEM )								return;

	m_arrayFieldITEM[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::SETFIELDMONEY ( PSFIELDCROW pFIELDCROW )
{
	GASSERT(pFIELDCROW);
	GASSERT(pFIELDCROW->dwID<MAXMONEY);
	GASSERT(pFIELDCROW->emCROW==CROW_MONEY);

	if ( !pFIELDCROW )													return;
	if ( pFIELDCROW->dwID>=MAXMONEY )									return;
	if ( pFIELDCROW->emCROW!=CROW_MONEY )								return;

	m_arrayFieldMONEY[pFIELDCROW->dwID] = pFIELDCROW;
}

void GLChar::RESETFIELDPET ( DWORD dwID )
{
	GASSERT(dwID<m_pGLGaeaServer->GetMaxClient());
	if ( dwID>=m_pGLGaeaServer->GetMaxClient() )
	{
		CDebugSet::ToListView ( "OutOf PetGUID : %d in GlChar::RESETFIELDPET()", dwID );
		return;
	}

	m_arrayFieldPET[dwID] = NULL;
}

void GLChar::RESETFIELDSUMMON ( DWORD dwID )
{
	GASSERT(dwID<m_pGLGaeaServer->GetMaxClient());
	if ( dwID>=m_pGLGaeaServer->GetMaxClient() )
	{
		CDebugSet::ToListView ( "OutOf SummonGUID : %d in GlChar::RESETFIELDSUMMON()", dwID );
		return;
	}

	m_arrayFieldSummon[dwID] = NULL;
}

void GLChar::RESETFIELDPC ( DWORD dwID )
{
	GASSERT(dwID<m_pGLGaeaServer->GetMaxClient());
	if ( dwID>=m_pGLGaeaServer->GetMaxClient() )					return;

	m_arrayFieldPC[dwID] = NULL;
}

void GLChar::RESETFIELDCROW ( DWORD dwID )
{
	GASSERT(dwID<MAXCROW);
	if ( dwID>=MAXCROW )												return;

	m_arrayFieldCROW[dwID] = NULL;
}

void GLChar::RESETFIELDMATERIAL ( DWORD dwID )
{
	GASSERT(dwID<MAXCROW);
	if ( dwID>=MAXCROW )												return;

	m_arrayFieldMATERIAL[dwID] = NULL;
}


void GLChar::RESETFIELDITEM ( DWORD dwID )
{
	GASSERT(dwID<MAXITEM);
	if ( dwID>=MAXITEM )												return;

	m_arrayFieldITEM[dwID] = NULL;
}

void GLChar::RESETFIELDMONEY ( DWORD dwID )
{
	GASSERT(dwID<MAXMONEY);
	if ( dwID>=MAXMONEY )												return;

	m_arrayFieldMONEY[dwID] = NULL;

}

//	Note : ªı∑Œ ∞‘¿”ø° ¬ÅE°Ω√, ¥Ÿ∏• ∏ ¿∏∑Œ ¡¯¿‘Ω√ø° PC ¡÷∫Ø¿«
//		∏µÅE∞≥√ºø° ¥ÅE— ¡§∫∏∏¶ ¿Œ¡ˆ«œ±ÅE¿ß«ÿº≠ »£√‚«‘.
//		( ≈¨∂Û¿Ãæ∆Æ √¯¿« ∞≥√ºø° ¿Ã¿ÅE¡§∫∏∞° ∏µŒ ∏Æª˚µ«æ˘¿Ω¿ª ∞°¡§«—¥Ÿ. )
//
HRESULT GLChar::GetViewAround ()
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	DxMsgServer *pMsgServer = m_pGLGaeaServer->GetMsgServer();
	if ( pMsgServer==NULL )	return E_FAIL;

	int nX = int ( GetPosition().x );
	int nZ = int ( GetPosition().z );

	LANDQUADTREE* pLandTree = m_pLandMan->GetLandTree();
	LANDQUADNODE* pQuadNode = NULL;
	BOUDRECT bRect(nX+MAX_VIEWRANGE,nZ+MAX_VIEWRANGE,nX-MAX_VIEWRANGE,nZ-MAX_VIEWRANGE);
	pLandTree->FindNodes ( bRect, pLandTree->GetRootNode(), &pQuadNode );


	//	Note : ∞°Ω√ øµø™ø° ¿÷¥¬ ∏µÅEºø¿« ø¿∫ÅEß∆ÆµÈ¿ª ≈Ωªˆ«—¥Ÿ.
	//
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
		GLLandNode *pLandNode = pQuadNode->pData;

		GASSERT(pLandTree->GetCellNum()>pQuadNode->dwCID&&"¿Œµ¶Ω∫∞° ºøªÁ¿Ã¡˚‘¶ √ ∞˙«œø¥Ω¿¥œ¥Ÿ.");

		GLSUMMONNODE* pSummonNode = pLandNode->m_SummonList.m_pHead;
		for ( ; pSummonNode; pSummonNode = pSummonNode->pNext )
		{
			PGLSUMMONFIELD pSummon = pSummonNode->Data;

			if ( pSummon->m_dwGUID>=m_pGLGaeaServer->GetMaxClient() )					continue;

			// ≈¨∂Û¿Ãæ∆Æø° ª˝º∫ ∏ﬁΩ√¡ÅE¿ÅE€
			GLMSG::SNET_SUMMON_DROP_SUMMON nmg;
			nmg.Data = pSummon->ReqNetMsg_Drop ();
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, ( NET_MSG_GENERIC* )&nmg );

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	∏ÆΩ∫∆Æø° µ˚”œ.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

			//	∞™ º≥¡§.
			pFIELDCROW->emCROW = CROW_SUMMON;
			pFIELDCROW->dwID = pSummon->m_dwGUID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	πËø≠ø° µ˚”œ.
			SETFIELDSUMMON(pFIELDCROW);
		}	

		GLPETNODE* pPetNode = pLandNode->m_PETList.m_pHead;
		for ( ; pPetNode; pPetNode = pPetNode->pNext )
		{
			PGLPETFIELD pPet = pPetNode->Data;

			if ( pPet->m_dwGUID>=m_pGLGaeaServer->GetMaxClient() )					continue;

			// ≈¨∂Û¿Ãæ∆Æø° ª˝º∫ ∏ﬁΩ√¡ÅE¿ÅE€
			NET_MSG_GENERIC* nmg = pPet->ReqNetMsg_Drop ();
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) nmg );

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	∏ÆΩ∫∆Æø° µ˚”œ.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

			//	∞™ º≥¡§.
			pFIELDCROW->emCROW = CROW_PET;
			pFIELDCROW->dwID = pPet->m_dwGUID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	πËø≠ø° µ˚”œ.
			SETFIELDPET(pFIELDCROW);
		}	

		//	Note : - Char -
		//
		GLCHARNODE *pCharCur = pLandNode->m_PCList.m_pHead;
		for ( ; pCharCur; pCharCur = pCharCur->pNext )
		{
			PGLCHAR pGLChar = pCharCur->Data;
			if ( !pGLChar ) continue;
			if ( pGLChar->m_dwClientID == m_dwClientID )	continue;

			GASSERT ( pGLChar->m_dwGaeaID != m_dwGaeaID );

			//	Memo :	¡÷¿ß ƒ≥∏Ø≈Õø° ¥ÅE— ±‚∫ª π◊ ø‹«ÅE¡§∫∏∏¶ ¿ÅE€«—¥Ÿ.
			NET_MSG_GENERIC* pNetMsgDrop = pGLChar->ReqNetMsg_Drop ();
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) pNetMsgDrop );

			if ( pGLChar->m_sPMarket.IsOpen() )
			{
				GLMSG::SNETPC_PMARKET_OPEN_BRD NetMsgPMarket;
				NetMsgPMarket.dwGaeaID = pGLChar->m_dwGaeaID;
				StringCchCopy ( NetMsgPMarket.szPMarketTitle, CHAT_MSG_SIZE+1, pGLChar->m_sPMarket.GetTitle().c_str() );
				m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgPMarket );
			}

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	∏ÆΩ∫∆Æø° µ˚”œ.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayPC_FIELDLIST.ADDTAIL ( pFIELDCROW );

			//	∞™ º≥¡§.
			pFIELDCROW->emCROW = CROW_PC;
			pFIELDCROW->dwID = pGLChar->m_dwGaeaID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	πËø≠ø° µ˚”œ.
			SETFIELDPC ( pFIELDCROW );
		}

		//	Note : - Crow -
		//
		GLCROWNODE *pCrowCur = pLandNode->m_CROWList.m_pHead;
		for ( ; pCrowCur; pCrowCur = pCrowCur->pNext )
		{
			PGLCROW pGLCrow = pCrowCur->Data;

			NET_MSG_GENERIC* nmg = pGLCrow->ReqNetMsg_Drop ();
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) nmg );

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	∏ÆΩ∫∆Æø° µ˚”œ.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

			//	∞™ º≥¡§.
			pFIELDCROW->emCROW = CROW_MOB;	//	∏ÅE NPC ∏µŒ CROW_MOB ∑Œ ∫–∑˘«œø© ∞ÅEÆ.
			pFIELDCROW->dwID = pGLCrow->m_dwGlobID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	πËø≠ø° µ˚”œ.
			SETFIELDCROW(pFIELDCROW);
		}

		//	Note : - Material -
		//
		GLMATERIALNODE *pMaterialCur = pLandNode->m_MaterialList.m_pHead;
		for ( ; pMaterialCur; pMaterialCur = pMaterialCur->pNext )
		{
			PGLMATERIAL pGLMaterial = pMaterialCur->Data;

			NET_MSG_GENERIC* nmg = pGLMaterial->ReqNetMsg_Drop ();
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) nmg );

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	∏ÆΩ∫∆Æø° µ˚”œ.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

			//	∞™ º≥¡§.
			pFIELDCROW->emCROW = CROW_MATERIAL;	//	∏ÅE NPC ∏µŒ CROW_MOB ∑Œ ∫–∑˘«œø© ∞ÅEÆ.
			pFIELDCROW->dwID = pGLMaterial->m_dwGlobID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	πËø≠ø° µ˚”œ.
			SETFIELDMATERIAL(pFIELDCROW);
		}
		

		//	Note : - Item -
		//
		ITEMDROPNODE* pCurItem = pLandNode->m_ItemList.m_pHead;
		for ( ; pCurItem; pCurItem = pCurItem->pNext )
		{
			PITEMDROP pItemDrop = pCurItem->Data;

			GLMSG::SNETDROP_ITEM sNetMsg;
			sNetMsg.Data.Assign ( pItemDrop->sDrop );
			sNetMsg.Data.fAge = pItemDrop->fAge;

			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) &sNetMsg );

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	∏ÆΩ∫∆Æø° µ˚”œ.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

			//	∞™ º≥¡§.
			pFIELDCROW->emCROW = CROW_ITEM;
			pFIELDCROW->dwID = pItemDrop->dwGlobID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	πËø≠ø° µ˚”œ.
			SETFIELDITEM(pFIELDCROW);
		}

		//	Note : - Money -
		//
		MONEYDROPNODE* pCurMoney = pLandNode->m_MoneyList.m_pHead;
		for ( ; pCurMoney; pCurMoney = pCurMoney->pNext )
		{
			PMONEYDROP pMoneyDrop = pCurMoney->Data;

			GLMSG::SNETDROP_MONEY sNetMsg;
			sNetMsg.fAge = pMoneyDrop->fAge;
			sNetMsg.dwGlobID = pMoneyDrop->sDrop.dwGlobID;
			sNetMsg.vPos = pMoneyDrop->sDrop.vPos;
			sNetMsg.lnAmount = pMoneyDrop->sDrop.lnAmount;
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) &sNetMsg );

			PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

			//	∏ÆΩ∫∆Æø° µ˚”œ.
			SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

			//	∞™ º≥¡§.
			pFIELDCROW->emCROW = CROW_MONEY;
			pFIELDCROW->dwID = pMoneyDrop->dwGlobID;
			pFIELDCROW->dwFRAME = m_dwViewFrame;
			pFIELDCROW->pNODE = pNODE;

			//	πËø≠ø° µ˚”œ.
			SETFIELDMONEY(pFIELDCROW);
		}
	}

	SetSTATE(EM_GETVA_AFTER);
	m_fMoveDelay = 0.0f;

	//	Note : GLLandMan¿« ºøø° µ˚”œ«œ¥¬ ¿€æÅE
	//
	m_pLandMan->RegistChar ( this );

	//	Note : Preiod Sync
	//
	MsgSendPeriod ();

	//	Note : ≥Øææ √ ±‚»≠.
	//
	GLMSG::SNETPC_WEATHER NetMsg;
//	NetMsg.dwWeather = m_pLandMan->IsWeatherActive() ? GLPeriod::GetInstance().GetWeather () : NULL;
	DWORD dwWeather = GLPeriod::GetInstance().GetMapWeather( m_pLandMan->GetMapID().wMainID, m_pLandMan->GetMapID().wSubID );
	NetMsg.dwWeather = m_pLandMan->IsWeatherActive() ? dwWeather : NULL;
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );

	//	ƒ˘Ω∫∆Æ¿« ∞Ê∞˙µ» Ω√∞£ æ˜µ•¿Ã∆Æ.
	MsgSendQuestTime ();

	//	±‚∞£¿Ã ∏∏∑·µ» æ∆¿Ã≈€¿ª º“∏ÅE
	RESET_TIMELMT_ITEM ();
	RESET_CHECK_ITEM ();

	//	Memo :	π´±ÅEΩ∫ø“ ∂ßπÆø° æ∆¿Ã≈€ ∞™¿ª ¥ŸΩ√ ∞ËªÅE—¥Ÿ.
	INIT_DATA( FALSE, FALSE );

	// º∫«ÅE¿Ã∫•∆Æ ¿Øπ´
	GLMSG::SNETPC_SERVER_BRIGHTEVENT_INFO NetMsgBrightEvnet;
	NetMsgBrightEvnet.bBRIGHTEVENT = m_pGLGaeaServer->IsBRIGHTEVENT();
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBrightEvnet );

	// º±µµ¿ÅEΩ√¿€ ¿Øπ´
	if ( m_pGLGaeaServer->IsClubBattleStarted() )
	{
		GLMSG::SNETPC_SERVER_CLUB_BATTLE_INFO NetMsgClubBattle;
		NetMsgClubBattle.bClubBattle = true;
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgClubBattle );

		GLMSG::SNETPC_SERVER_CLUB_BATTLE_REMAIN_AG NetMsgReq;
		NetMsgReq.dwGaeaID = m_dwGaeaID;
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgReq );
	}

	if ( m_pGLGaeaServer->IsClubDMStarted() )
	{
		GLMSG::SNETPC_SERVER_CLUB_DEATHMATCH_INFO NetMsgClubDM;
		NetMsgClubDM.bClubDeathMatch = true;
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgClubDM );

		GLMSG::SNETPC_SERVER_CLUB_DEATHMATCH_REMAIN_AG NetMsgReq;
		NetMsgReq.dwGaeaID = m_dwGaeaID;
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgReq );
	}

	if ( m_pGLGaeaServer->IsSchoolWarsStarted() )
	{
		GLMSG::SNETPC_SERVER_SCHOOL_WARS_INFO NetMsgSchoolwars;
		NetMsgSchoolwars.bSchoolWars = true;
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgSchoolwars );

		GLMSG::SNETPC_SERVER_SCHOOL_WARS_REMAIN_AG NetMsgReq;
		NetMsgReq.dwGaeaID = m_dwGaeaID;
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgReq );
	}

	if ( m_pGLGaeaServer->IsRoyalRumbleStarted() )
	{
		GLMSG::SNETPC_SERVER_ROYAL_RUMBLE_INFO NetMsgRoyalRumble;
		NetMsgRoyalRumble.bRoyalRumble = true;
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgRoyalRumble );

		GLMSG::SNETPC_SERVER_ROYAL_RUMBLE_REMAIN_AG NetMsgReq;
		NetMsgReq.dwGaeaID = m_dwGaeaID;
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgReq );
	}

	if ( m_pGLGaeaServer->IsTowerWarsStarted() )
	{
		GLMSG::SNETPC_SERVER_TOWERWARS_INFO NetMsgSchoolwars;
		GLMSG::SNETPC_SERVER_TOWERWARS_REMAIN_AG NetMsgReq;

		NetMsgSchoolwars.bTowerWars = true;
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgSchoolwars );

		NetMsgReq.dwGaeaID = m_dwGaeaID;
		m_pGLGaeaServer->SENDTOAGENT ( m_dwClientID, &NetMsgReq );
	}

	//	¡ˆø™ ∆Ø∫∞ ¡§∫∏.
	GLMSG::SNETPC_LAND_INFO NetMsgLandInfo;
	NetMsgLandInfo.nidMAP = m_pLandMan->GetMapID();
	NetMsgLandInfo.bClubBattle = m_pLandMan->m_bGuidBattleMap;
	NetMsgLandInfo.bClubBattleHall = m_pLandMan->m_bGuidBattleMapHall;
	NetMsgLandInfo.bClubDeathMatch = m_pLandMan->m_bClubDeathMatchMap;
	NetMsgLandInfo.bClubDeathMatchHall = m_pLandMan->m_bClubDeathMatchMapHall;
	NetMsgLandInfo.bSchoolWars = m_pLandMan->m_bSchoolWarsMap;
	NetMsgLandInfo.bSchoolWarsHall = m_pLandMan->m_bSchoolWarsMapHall;
	NetMsgLandInfo.bRoyalRumble = m_pLandMan->m_bRoyalRumbleMap;
	NetMsgLandInfo.bRoyalRumbleHall = m_pLandMan->m_bRoyalRumbleMapHall;
	NetMsgLandInfo.bPK = m_pLandMan->IsPKZone();
	NetMsgLandInfo.fCommission = m_pLandMan->m_fCommissionRate;
	NetMsgLandInfo.dwGuidClub = m_pLandMan->m_dwGuidClubID;

	NetMsgLandInfo.bTowerWars = m_pLandMan->m_bTowerWarsMap;
	NetMsgLandInfo.dwCTFWINNER = GLTowerWarsFieldMan::GetInstance().GetLastWinner();


	GLClubMan &sClubMan = m_pGLGaeaServer->GetClubMan();
	GLCLUB* pCLUB = sClubMan.GetClub(m_pLandMan->m_dwGuidClubID);
	if ( pCLUB )
	{
		NetMsgLandInfo.dwGuidClubMarkVer = pCLUB->m_dwMarkVER;
		StringCchCopy ( NetMsgLandInfo.szGuidClubName, CHAR_SZNAME, pCLUB->m_szName );
	}
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgLandInfo );

	// «–ø¯∞£ ¿⁄¿Ø ««ƒ…¿Ã ¿Øπ´ ¿ÅE€
	GLMSG::SNETPC_SERVER_INFO NetMsgServerInfo;
	NetMsgServerInfo.bSCHOOL_FREEPK = GLSchoolFreePK::GetInstance().IsON();
    m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgServerInfo );

	//	Memo :	?æ∆¿Ã≈€ ¿Ã∫•∆Æ ¿Øπ´
	GLMSG::SNETPC_EVENTFACT_INFO NetMsgEvent;
	NetMsgEvent.sEVENTFACT = m_sEVENTFACT = m_pGLGaeaServer->m_sEVENTFACT;
	m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgEvent );
	GLMSG::SNETPC_SERVER_NEXTWAR NetMsgTimeSW;
	NetMsgTimeSW.fProgressTime = m_pGLGaeaServer->m_fProgressTime;
	NetMsgTimeSW.fNextStartTime = m_pGLGaeaServer->m_fNextBattleStart;
	NetMsgTimeSW.fNextEndTime = m_pGLGaeaServer->m_fNextBattleEnd;
	NetMsgTimeSW.fPreviousStartTime = m_pGLGaeaServer->m_fPreviousBattleStart;
	NetMsgTimeSW.fPreviousEndTime = m_pGLGaeaServer->m_fPreviousBattleEnd;
	if ( m_pGLGaeaServer->m_fNextBattleStart > 0.0f ) m_pGLGaeaServer->SENDTOCLIENT( m_dwClientID, &NetMsgTimeSW );
	
	//	?æ∆¿Ã≈€ ∏Æº¬.
	GLMSG::SNETPC_QITEMFACT_END_BRD	NetMsgBrd;
	GLMSG::SNETPC_QITEMFACT_TIMEUPDATE_BRD	NetMsgTUBrd; //add qbox
	NetMsgBrd.dwGaeaID = m_dwGaeaID;
	NetMsgTUBrd.dwGaeaID = m_dwGaeaID;
	NetMsgTUBrd.fQBoxTime = 0;
	if ( m_sQITEMFACT.IsACTIVE() )
	{
		m_sQITEMFACT.RESET();

		//	Note : ¡æ∑·µ«æ˙¿ª ∞ÊøÅE¡÷∫Ø ªÁ∂˜ø°∞‘ æÀ∏≤.
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgTUBrd );//add qbox
	}

	//	Note : ¡æ∑·µ«æ˙¿ª ∞ÊøÅE¿⁄Ω≈ø°∞‘ æÀ∏≤.
	m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgBrd );
	m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgTUBrd );//add qbox

	// º≠πˆ¿« «ˆ¿ÁΩ√∞£¿ª ≈¨∂Û¿Ãæ∆Æø° æÀ∏≤
	GLMSG::SNET_MSG_SERVERTIME_BRD NetMsgTime;
	CTime cServerTime = CTime::GetCurrentTime();
	NetMsgTime.t64Time = cServerTime.GetTime();
	m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgTime );

	return S_OK;
}

HRESULT GLChar::MsgFieldMoveReset ()
{
	//	Note : ≈¨∑¥ ¡§∫∏ ∏Æº¬.
	if ( m_dwGuild!=CLUB_NULL )
	{
		GLCLUB *pCLUB = m_pGLGaeaServer->GetClubMan().GetClub(m_dwGuild);
		if ( pCLUB && pCLUB->m_dwMasterID==m_dwCharID )
		{
			GLMSG::SNET_CLUB_STORAGE_RESET NetMsgClubStorageReset;
			m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgClubStorageReset );
		}
	}

	return S_OK;
}

HRESULT GLChar::SendMsgViewAround ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	FIELDCROWNODE* pNode = m_arrayPC_FIELDLIST.m_pHead;
	while ( pNode )
	{
		GLChar* pPChar = m_pGLGaeaServer->GetChar ( pNode->Data->dwID );

		//	Note : ƒ≥∏Ø≈Õ¿« ªË¡¶ Ω√¡°∞ÅEUpdateViewAround ()∞˙¿« ∫“¿œƒ°∑Œ ƒ≥∏Ø≈Õ∞° ¡∏¿Á«œ¡ÅEæ ¿ª ºÅE¿÷¿Ω.
		if ( pPChar )
		{
			m_pGLGaeaServer->SENDTOCLIENT ( pPChar->m_dwClientID, nmg );

			// ∏∏¿œ ¿œπ› √º∆√ ∏ﬁΩ√¡ˆ¿œ ∞ÊøÅE° √ﬂ¿˚∑Œ±◊∏¶ ≥≤∞‹æﬂ«œπ«∑Œ √º≈©∏¶ «ÿº≠ agentø° ∑Œ±◊∏¶ ∫∏≥Ω¥Ÿ.
			if( nmg->nType == NET_MSG_CHAT_FB )
			{
#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) || defined(HK_PARAM)// ***Tracing Log print
				if( pPChar->m_bTracingUser )
				{
					NET_LOG_UPDATE_TRACINGCHAR TracingMsg;
					NET_CHAT* pNetMsg = (NET_CHAT*) nmg;
					TracingMsg.nUserNum  = pPChar->GetUserID();
					StringCchCopy( TracingMsg.szAccount, USR_ID_LENGTH+1, pPChar->m_szUID );

					CString strTemp;
					strTemp.Format( "**Normal Recv**, [%s][%s]->[%s][%s], %s", 
						     m_szUID, m_szName, pPChar->m_szUID, pPChar->m_szName, pNetMsg->szChatMsg );

					StringCchCopy( TracingMsg.szLogMsg, TRACING_LOG_SIZE, strTemp.GetString() );
					
					m_pGLGaeaServer->SENDTOAGENT( pPChar->m_dwClientID, &TracingMsg );
				}
#endif
			}
		}

		pNode = pNode->pNext;
	};

	return S_OK;
}

BOOL GLChar::IsInViewAround ( DWORD dwGAEAID )
{
	return m_arrayFieldPC[dwGAEAID]!=NULL;
}

HRESULT GLChar::ResetViewAround ()
{
	ReSetSTATE(EM_GETVA_AFTER);
	SetSTATE(EM_ACT_WAITING);

	m_dwViewFrame = 0;

	//	Note : FIELD CROW ¡§∏Æ.
	//
	FIELDCROWNODE* pNode = m_arrayPC_FIELDLIST.m_pHead;
	while ( pNode )
	{
		SFIELDCROW* pFIELD = pNode->Data;

		//	πËø≠ø°º≠ ªË¡¶.
		RESETFIELDPC ( pFIELD->dwID );

		//	∏ÆΩ∫∆Æø°º≠ ªË¡¶.
		m_pGLGaeaServer->RELEASE_FIELDCROW ( pFIELD );

		pNode = pNode->pNext;
	}

	m_arrayPC_FIELDLIST.DELALL ();

	pNode = m_arrayFIELDLIST.m_pHead;
	while ( pNode )
	{
		SFIELDCROW* pFIELD = pNode->Data;

		//	πËø≠ø°º≠ ªË¡¶.
		switch ( pFIELD->emCROW )
		{
		case CROW_MOB:		RESETFIELDCROW(pFIELD->dwID);	break;
		case CROW_ITEM:		RESETFIELDITEM(pFIELD->dwID);	break;
		case CROW_MONEY:	RESETFIELDMONEY(pFIELD->dwID);	break;
		case CROW_PET:		RESETFIELDPET(pFIELD->dwID);	break;	// PetData
		case CROW_SUMMON:	RESETFIELDSUMMON(pFIELD->dwID);	break;	// SummonData
		case CROW_MATERIAL:	RESETFIELDMATERIAL(pFIELD->dwID);	break;	// Material
		};

		//	∏ÆΩ∫∆Æø°º≠ ªË¡¶.
		m_pGLGaeaServer->RELEASE_FIELDCROW ( pFIELD );

		pNode = pNode->pNext;
	};

	m_arrayFIELDLIST.DELALL ();

	return S_OK;
}

HRESULT GLChar::UpdateViewAround ()
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	int nX, nZ;

	++m_dwViewFrame;
	if ( m_dwViewFrame == UINT_MAX )	m_dwViewFrame = 0;

	// if ( m_dwViewFrame%2 == 1 ) return S_FALSE;

	//	Note : «ˆ¿ÅEΩ√æﬂø° µÈæ˚€¿¥¬ CELL ∏µŒ ≈ΩªÅE
	//
	nX = int ( m_vPos.x );
	nZ = int ( m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+MAX_VIEWRANGE,nZ+MAX_VIEWRANGE,nX-MAX_VIEWRANGE,nZ-MAX_VIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ªı∑Œ √ﬂ∞°µ«¥¬ ≥ÅEÂøÕ ¡∏º” ≥ÅEÂ∏¶ «•Ω√.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
		GASSERT(m_pLandMan->GetLandTree()->GetCellNum()>pQuadNode->dwCID&&"The Index exceed cell Size");

		// PET
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		PROFILE_BEGIN("pQuadNode->pData->m_SummonList");
		GLSUMMONNODE* pSummonNode = pQuadNode->pData->m_SummonList.m_pHead;
		for ( ; pSummonNode; pSummonNode = pSummonNode->pNext )
		{
			PGLSUMMONFIELD pSummon = pSummonNode->Data;
			nX = int(pSummon->m_vPos.x); nZ = int(pSummon->m_vPos.z);

			if ( pSummon->m_dwGUID>=m_pGLGaeaServer->GetMaxClient() )					continue;

			// ≥ª∆÷ ª©∞ÅE
			if ( pSummon->m_dwGUID != m_dwSummonGUID && bRect.IsWithIn ( nX, nZ ) )
			{
				// ¿÷¿∏∏ÅE«¡∑π¿” ∞ªΩ≈
				if ( m_arrayFieldSummon[pSummon->m_dwGUID] )
				{
					m_arrayFieldSummon[pSummon->m_dwGUID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					// ≈¨∂Û¿Ãæ∆Æø° ª˝º∫ ∏ﬁΩ√¡ÅE¿ÅE€
					GLMSG::SNET_SUMMON_DROP_SUMMON nmg;
					nmg.Data = pSummon->ReqNetMsg_Drop ();
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, ( NET_MSG_GENERIC* )&nmg );

					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	∏ÆΩ∫∆Æø° µ˚”œ.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

					//	∞™ º≥¡§.
					pFIELDCROW->emCROW = CROW_SUMMON;
					pFIELDCROW->dwID = pSummon->m_dwGUID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;

					//	πËø≠ø° µ˚”œ.
					SETFIELDSUMMON ( pFIELDCROW );
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_SummonList");

		PROFILE_BEGIN("pQuadNode->pData->m_PETList");
		GLPETNODE* pPetNode = pQuadNode->pData->m_PETList.m_pHead;
		for ( ; pPetNode; pPetNode = pPetNode->pNext )
		{
			PGLPETFIELD pPet = pPetNode->Data;
			nX = int(pPet->m_vPos.x); nZ = int(pPet->m_vPos.z);

			if ( pPet->m_dwGUID>=m_pGLGaeaServer->GetMaxClient() )					continue;

			// ≥ª∆÷ ª©∞ÅE
			if ( pPet->m_dwGUID != m_dwPetGUID && bRect.IsWithIn ( nX, nZ ) )
			{
				// ¿÷¿∏∏ÅE«¡∑π¿” ∞ªΩ≈
				if ( m_arrayFieldPET[pPet->m_dwGUID] )
				{
					m_arrayFieldPET[pPet->m_dwGUID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					// ≈¨∂Û¿Ãæ∆Æø° ª˝º∫ ∏ﬁΩ√¡ÅE¿ÅE€
					NET_MSG_GENERIC* pNetMsgDrop = pPet->ReqNetMsg_Drop ();
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID)pNetMsgDrop );
					
					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	∏ÆΩ∫∆Æø° µ˚”œ.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

					//	∞™ º≥¡§.
					pFIELDCROW->emCROW = CROW_PET;
					pFIELDCROW->dwID = pPet->m_dwGUID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;

					//	πËø≠ø° µ˚”œ.
					SETFIELDPET ( pFIELDCROW );
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_PETList");
		
		PROFILE_BEGIN("pQuadNode->pData->m_PCList");
		//	Note : - Char - 
		//
		GLCHARNODE *pCharNode = pQuadNode->pData->m_PCList.m_pHead;
		for ( ; pCharNode; pCharNode = pCharNode->pNext )
		{
			GLChar *pPChar = pCharNode->Data;
			if( !pPChar ) continue;

			nX = int(pPChar->m_vPos.x); nZ = int(pPChar->m_vPos.z);

			if ( pPChar->m_dwClientID != m_dwClientID && bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pPChar->m_dwGaeaID;
				if ( dwID>=m_pGLGaeaServer->GetMaxClient() )					continue;

				if ( m_arrayFieldPC[dwID] )
				{
					m_arrayFieldPC[dwID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					NET_MSG_GENERIC* pNetMsgDrop = pPChar->ReqNetMsg_Drop ();
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, pNetMsgDrop );

					if ( pPChar->m_sPMarket.IsOpen() )
					{
						GLMSG::SNETPC_PMARKET_OPEN_BRD NetMsgPMarket;
						NetMsgPMarket.dwGaeaID = pPChar->m_dwGaeaID;
						StringCchCopy ( NetMsgPMarket.szPMarketTitle, CHAT_MSG_SIZE+1, pPChar->m_sPMarket.GetTitle().c_str() );
						m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgPMarket );
					}

					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	∏ÆΩ∫∆Æø° µ˚”œ.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayPC_FIELDLIST.ADDTAIL ( pFIELDCROW );

					//	∞™ º≥¡§.
					pFIELDCROW->emCROW = CROW_PC;
					pFIELDCROW->dwID = dwID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;

					//	πËø≠ø° µ˚”œ.
					SETFIELDPC ( pFIELDCROW );
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_PCList");

		PROFILE_BEGIN("pQuadNode->pData->m_CROWList");
		//	Note : - Crow - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		GLCROWNODE *pCrowNode = pQuadNode->pData->m_CROWList.m_pHead;
		for ( ; pCrowNode; pCrowNode = pCrowNode->pNext )
		{
			PGLCROW pGLCrow = pCrowNode->Data;
			nX = int(pGLCrow->GetPosition().x); nZ = int(pGLCrow->GetPosition().z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pGLCrow->m_dwGlobID;
				if ( dwID>=MAXCROW )												continue;

				if ( m_arrayFieldCROW[dwID] )
				{
					m_arrayFieldCROW[dwID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					NET_MSG_GENERIC* nmg = pGLCrow->ReqNetMsg_Drop ();
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, nmg );

					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	∏ÆΩ∫∆Æø° µ˚”œ.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

					//	∆˙‹«ªÅEMOB, NPC ∏µŒ CROW_MOB¿∏∑Œ ∫–∑ÅE
					pFIELDCROW->emCROW = CROW_MOB;
					pFIELDCROW->dwID = dwID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;

					//	πËø≠ø° µ˚”œ.
					SETFIELDCROW(pFIELDCROW);
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_CROWList");


		PROFILE_BEGIN("pQuadNode->pData->m_MaterailList");
		//	Note : - Material - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		GLMATERIALNODE *pMaterialNode = pQuadNode->pData->m_MaterialList.m_pHead;
		for ( ; pMaterialNode; pMaterialNode = pMaterialNode->pNext )
		{
			PGLMATERIAL pGLMaterial = pMaterialNode->Data;
			nX = int(pGLMaterial->GetPosition().x); nZ = int(pGLMaterial->GetPosition().z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pGLMaterial->m_dwGlobID;
				if ( dwID>=MAXCROW )												continue;

				if ( m_arrayFieldMATERIAL[dwID] )
				{
					m_arrayFieldMATERIAL[dwID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					NET_MSG_GENERIC* nmg = pGLMaterial->ReqNetMsg_Drop ();
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, nmg );

					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	∏ÆΩ∫∆Æø° µ˚”œ.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

					pFIELDCROW->emCROW = CROW_MATERIAL;
					pFIELDCROW->dwID = dwID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;

					//	πËø≠ø° µ˚”œ.
					SETFIELDMATERIAL(pFIELDCROW);
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_MaterailList");


		//	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		PROFILE_BEGIN("pQuadNode->pData->m_ItemList");
		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM )												continue;

				if ( m_arrayFieldITEM[dwID] )
				{
					m_arrayFieldITEM[dwID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					static GLMSG::SNETDROP_ITEM sNetMsg;
					sNetMsg.Data.Assign ( pItemDrop->sDrop );
					sNetMsg.Data.fAge = pItemDrop->fAge;

					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) &sNetMsg );

					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	∏ÆΩ∫∆Æø° µ˚”œ.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

					//	∆˙‹«ªÅEMOB, NPC ∏µŒ CROW_MOB¿∏∑Œ ∫–∑ÅE
					pFIELDCROW->emCROW = CROW_ITEM;
					pFIELDCROW->dwID = dwID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;


					//	πËø≠ø° µ˚”œ.
					SETFIELDITEM(pFIELDCROW);
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_ItemList");

		//	Note : - Money - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		PROFILE_BEGIN("pQuadNode->pData->m_MoneyList");
		MONEYDROPNODE *pMoneyNode = pQuadNode->pData->m_MoneyList.m_pHead;
		for ( ; pMoneyNode; pMoneyNode = pMoneyNode->pNext )
		{
			PMONEYDROP pMoneyDrop = pMoneyNode->Data;
			nX = int(pMoneyDrop->vPos.x); nZ = int(pMoneyDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pMoneyDrop->dwGlobID;
				if ( dwID>=MAXMONEY )												continue;

				if ( m_arrayFieldMONEY[dwID] )
				{
					m_arrayFieldMONEY[dwID]->dwFRAME = m_dwViewFrame;
				}
				else
				{
					GLMSG::SNETDROP_MONEY sNetMsg;
					sNetMsg.fAge = pMoneyDrop->fAge;
					sNetMsg.dwGlobID = pMoneyDrop->sDrop.dwGlobID;
					sNetMsg.vPos = pMoneyDrop->sDrop.vPos;
					sNetMsg.lnAmount = pMoneyDrop->sDrop.lnAmount;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, (LPVOID) &sNetMsg );

					PSFIELDCROW pFIELDCROW = m_pGLGaeaServer->NEW_FIELDCROW();

					//	∏ÆΩ∫∆Æø° µ˚”œ.
					SGLNODE<SFIELDCROW*>* pNODE = m_arrayFIELDLIST.ADDTAIL ( pFIELDCROW );

					//	∆˙‹«ªÅEMOB, NPC ∏µŒ CROW_MOB¿∏∑Œ ∫–∑ÅE
					pFIELDCROW->emCROW = CROW_MONEY;
					pFIELDCROW->dwID = dwID;
					pFIELDCROW->dwFRAME = m_dwViewFrame;
					pFIELDCROW->pNODE = pNODE;

					//	πËø≠ø° µ˚”œ.
					SETFIELDMONEY(pFIELDCROW);
				}
			}
		}
		PROFILE_END("pQuadNode->pData->m_MoneyList");
	}

	//	Note : ¡¶∞≈µ… ∞≥√ºµÈ∏¶ √≥∏Æ«—¥Ÿ.
	//
	static GLMSG::SNETDROP_OUT NetMsgOut;
	NetMsgOut.RESET_CROW();

	//	Note : ¡¶∞≈µ… FIELD CROW √≥∏Æ.
	//
	PROFILE_BEGIN("m_arrayPC_FIELDLIST");
	FIELDCROWNODE* pNode = m_arrayPC_FIELDLIST.m_pHead;
	while ( pNode )
	{
		FIELDCROWNODE* pNodeDEL = pNode;
		pNode = pNode->pNext;

		SFIELDCROW* pFIELD = pNodeDEL->Data;
		if ( pFIELD->dwFRAME == m_dwViewFrame )	continue;

		//	¡¶∞≈µ… ∞≥√º ∏ﬁΩ√¡ˆø° µ˚”œ,  ∞πºˆ∞° ∞°µÊ«“ ∞ÊøÅEΩ«∆–.
		bool bOK = NetMsgOut.ADD_CROW(STARID(pFIELD->emCROW,pFIELD->dwID));
		if ( !bOK )
		{
			//	«ˆ¿Á±˚›ÅE∏¿Œ ¡§∫∏∏¶ ¿ÅE€.
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgOut );

			//	¥ŸΩ√ ≥÷æ˚›‹.
			NetMsgOut.RESET_CROW();
			NetMsgOut.ADD_CROW(STARID(pFIELD->emCROW,pFIELD->dwID));
		}

		//	πËø≠ø°º≠ ªË¡¶.
		RESETFIELDPC ( pFIELD->dwID );

		//	∏ÆΩ∫∆Æø°º≠ ªË¡¶.
		m_arrayPC_FIELDLIST.DELNODE ( pNodeDEL );
		m_pGLGaeaServer->RELEASE_FIELDCROW ( pFIELD );
	}
	PROFILE_END("m_arrayPC_FIELDLIST");

	PROFILE_BEGIN("m_arrayFIELDLIST");
	pNode = m_arrayFIELDLIST.m_pHead;
	while ( pNode )
	{
		FIELDCROWNODE* pNodeDEL = pNode;
		pNode = pNode->pNext;

		SFIELDCROW* pFIELD = pNodeDEL->Data;
		if ( pFIELD->dwFRAME == m_dwViewFrame )	continue;

		//	¡¶∞≈µ… ∞≥√º ∏ﬁΩ√¡ˆø° µ˚”œ,  ∞πºˆ∞° ∞°µÊ«“ ∞ÊøÅEΩ«∆–.
		bool bOK = NetMsgOut.ADD_CROW(STARID(pFIELD->emCROW,pFIELD->dwID));
		if ( !bOK )
		{
			//	«ˆ¿Á±˚›ÅE∏¿Œ ¡§∫∏∏¶ ¿ÅE€.
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgOut );

			//	¡¶∞≈µ… ∞≥√º ∏ﬁΩ√¡ˆø° µ˚”œ.
			NetMsgOut.RESET_CROW();
			NetMsgOut.ADD_CROW(STARID(pFIELD->emCROW,pFIELD->dwID));
		}

		//	πËø≠ø°º≠ ªË¡¶.
		switch ( pFIELD->emCROW )
		{
		case CROW_MOB:		RESETFIELDCROW(pFIELD->dwID);	break;
		case CROW_ITEM:		RESETFIELDITEM(pFIELD->dwID);	break;
		case CROW_MONEY:	RESETFIELDMONEY(pFIELD->dwID);	break;
		case CROW_PET:		RESETFIELDPET(pFIELD->dwID);	break;	// PetData
		case CROW_SUMMON:	RESETFIELDSUMMON(pFIELD->dwID);	break;	// SummonData
		case CROW_MATERIAL:	RESETFIELDMATERIAL(pFIELD->dwID);	break;	// Material
		};

		//	∏ÆΩ∫∆Æø°º≠ ªË¡¶.
		m_arrayFIELDLIST.DELNODE ( pNodeDEL );
		m_pGLGaeaServer->RELEASE_FIELDCROW ( pFIELD );
	}
	PROFILE_END("m_arrayFIELDLIST");

	if ( NetMsgOut.GETAMOUNT() > 0 )
	{
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgOut );
	}

	return S_OK;
}

DWORD GLChar::ReceiveDamage ( const EMCROW emACrow, const DWORD dwAID, const DWORD dwDamage, const BOOL bShock )
{
	if ( !IsValidBody() )	return m_sHP.dwNow;
	if ( m_sHP.dwNow == 0 )	return m_sHP.dwNow;

	//	Note : ∞¯∞› πﬁ¿ª∂ß π›¿¿ ∞®æ»?
	//		( emACrow, dwAID )
	DWORD wDxHP = GLCHARLOGIC::RECEIVE_DAMAGE ( (DWORD) dwDamage );

	//	Note : √Ê∞› πﬁ¿Ω.
	//
	//TurnAction ( GLAT_SHOCK );

	m_sAssault.emCrow = emACrow;
	m_sAssault.dwID = dwAID;

	bool bTowerWars = false;
	if ( m_pLandMan->m_bTowerWarsMap )
	{
		GLTowerWars* pSW = GLTowerWarsFieldMan::GetInstance().Find( m_pLandMan->m_dwTowerWarsMapID );
		if( pSW && pSW->IsBattle() ) bTowerWars = true;
	}

	if ( wDxHP > 0 )
	{
		if ( emACrow == CROW_PC )
		{
			PGLCHAR pChar = m_pGLGaeaServer->GetChar ( dwAID );
			AddDamageLog ( m_cDamageLog, dwAID, pChar->m_dwUserID, wDxHP );
			if( bTowerWars )
			{
				GLTowerWars* pSW = GLTowerWarsFieldMan::GetInstance().Find( m_pLandMan->m_dwTowerWarsMapID );
				if( pSW && pChar )
				{
					pSW->AddSWPDamageScore( pChar->m_dwGaeaID, wDxHP );

					/*GLMSG::SNET_TOWERWARS_CTFPOINT_UPDATE NetMsg;
					NetMsg.bDamagePoint = true;
					NetMsg.bHealPoint = false;
					NetMsg.bResuPoint = false;
					NetMsg.bKillPoint = false;		
					NetMsg.dwDamage = wDxHP;
					NetMsg.dwHeal = 0;
					m_pGLGaeaServer->SENDTOPLAYERCLIENT_ONMAP ( pChar->m_pLandMan->GetMapID().dwID, pChar->m_dwCharID, &NetMsg);*/

					//GLTowerWarsFieldMan::GetInstance().UpdateSWPRanking( pSW->m_dwID );
				}
			}
		}

		if ( m_dwPartyID!=PARTY_NULL )
		{
			GLMSG::SNET_PARTY_MBR_POINT NetMsg;
			NetMsg.dwGaeaID = m_dwGaeaID;
			NetMsg.sHP = m_sHP;
			NetMsg.sMP = m_sMP;
			m_pGLGaeaServer->SENDTOPARTYCLIENT ( m_dwPartyID, (NET_MSG_GENERIC*) &NetMsg );
		}
	}

	if ( IsACTION(GLAT_GATHERING) )
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

	return m_sHP.dwNow;
}

void GLChar::ReceivePushPull ( const D3DXVECTOR3 &vMovePos, const bool bReact , const bool bAdjustSpeed , const float fSpeed, const  bool  bDash, const  bool  bTeleport ) //add pushpull
{
	//PGLCHAR pChar = GLGaeaClient::GetInstance().GetChar ( m_TargetID.vPos);

	if ( !IsValidBody() )	return;

//	if ( pChar->IsCDCertify() ) return;

	//	Note : π–∑¡≥Ø ¿ßƒ°∑Œ ¿Ãµø Ω√µµ.
	//
	BOOL bSucceed = m_actorMove.GotoLocation
	(
		D3DXVECTOR3(vMovePos.x,vMovePos.y+5,vMovePos.z),
		D3DXVECTOR3(vMovePos.x,vMovePos.y-5,vMovePos.z)
	);

	if ( bSucceed )
	{
		//	Note : π–∑¡≥™¥¬ ø¢º« Ω√¿€.
		//
		m_TargetID.vPos = vMovePos;

		if ( bReact ) TurnAction ( GLAT_PUSHPULL );

		if ( bDash || bTeleport ) SetPosition ( m_TargetID.vPos );

		//	Note : π–∏Æ¥¬ º”µµ º≥¡§.
		//
		if  ( bAdjustSpeed ){ m_actorMove.SetMaxSpeed ( fSpeed );  //add pushpull
		}else{
			m_actorMove.SetMaxSpeed ( GLCONST_CHAR::fPUSHPULL_VELO );
		}

		GLMSG::SNET_PUSHPULL_BRD NetMsgBRD;
		NetMsgBRD.emCrow = GETCROW();
		NetMsgBRD.dwID = m_dwGaeaID;
		NetMsgBRD.vMovePos = vMovePos;
		NetMsgBRD.fSpeed = fSpeed;
		NetMsgBRD.bTeleport = bTeleport;//Mike915

		//	Note : [¿⁄Ω≈ø°∞‘] Msg∏¶ ¿¸¥ﬁ.
		//
		m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgBRD );

		//	Note : [¿⁄Ω≈¿« ¡÷∫Ø Char] ø°∞‘ Msg∏¶ ¿¸¥ﬁ.
		//
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBRD );
	}
}

// ¿Ã∫•∆Æ≥™ ≈Ω¥– πÊ¡ÅEΩ√Ω∫≈€ø° ¿««ÿ ∫Ø∞Êµ» ∞Ê«Ëƒ°∏¶ ±∏«—¥Ÿ.
int GLChar::CalculateReceveExp ( int nGenExp )
{
	float fGenExp = (float)nGenExp;
	int	  nCalculateExp = 0;
#if defined(VN_PARAM) //vietnamtest%%%

	if( m_dwVietnamGainType == GAINTYPE_HALF )
	{
		fGenExp /= 2.0f;
	}
	if( m_dwVietnamGainType == GAINTYPE_EMPTY )
	{
		fGenExp = 0.0f;
	}

	nCalculateExp = (int)fGenExp;

	if( m_dwVietnamGainType == GAINTYPE_EMPTY || m_dwVietnamGainType == GAINTYPE_HALF )
	{
		m_lVNGainSysExp += (nGenExp - nCalculateExp);
	}
#endif

#ifdef CH_PARAM_USEGAIN //chinaTest%%%
	if( m_ChinaGainType == GAINTYPE_HALF )
	{
		fGenExp /= 2.0f;
	}
	if( m_ChinaGainType == GAINTYPE_EMPTY )
	{
		fGenExp = 0;
	}

	nCalculateExp = (int)fGenExp;
#endif

#ifndef CH_PARAM_USEGAIN //** Add EventTime
	if( m_bEventStart && m_bEventApply )
	{
		SEventState sEventState = m_pGLGaeaServer->m_sEventState;
		if( sEventState.bEventStart )
		{
			fGenExp *= sEventState.fExpGainRate;
		}
	}
	nCalculateExp = (int)fGenExp;
#endif

	return nCalculateExp;
}

// *****************************************************
// Desc: ∞Ê«Ëƒ° »πµÅE
// *****************************************************
void GLChar::ReceiveExp ( int nGenExp, const bool bupdate_msg )
{
	if ( !IsValidBody() )	return;

	// ∆ƒ∆ºµÅEæ∆¥œµÅE∞Ê«Ëƒ° ∞ËªÅE∫ ∏∂¡ˆ∏∑¿∏∑Œ ø©±‚º≠«—¥Ÿ!
	//NeedToSaveValue _A
	float fTempExp = (float)nGenExp;
	int nMemExp = (int)(fTempExp * (m_pGLGaeaServer->GetExpGainRate(m_CHARINDEX,m_wLevel) + m_pGLGaeaServer->GetExpGainRate(m_wSchool) - 1) );

	nGenExp = CalculateReceveExp( nMemExp );

	m_sExperience.lnNow += DWORD( nGenExp*m_fEXP_RATE );


#if defined(_RELEASED) || defined(TW_PARAM) || defined(TH_PARAM) ||  defined(HK_PARAM) // ***Tracing Log print
	if( nGenExp != 0 && m_bTracingUser )
	{
		NET_LOG_UPDATE_TRACINGCHAR TracingMsg;
		TracingMsg.nUserNum  = GetUserID();
		StringCchCopy( TracingMsg.szAccount, USR_ID_LENGTH+1, m_szUID );

		CString strTemp;
		strTemp.Format( "Receive Exp, [%s][%s], Receive exp amount[%d]", m_szUID, m_szName, nGenExp );

		StringCchCopy( TracingMsg.szLogMsg, TRACING_LOG_SIZE, strTemp.GetString() );

		m_pGLGaeaServer->SENDTOAGENT( m_dwClientID, &TracingMsg );
	}
#endif
}

// *****************************************************
// Desc: ∞Ê«Ëƒ° »πµÅE∆ƒ∆º)
// *****************************************************
void GLChar::ReceivePartyExp ( const int nGenExp )
{
	if ( !IsValidBody() )	return;

	ReceiveExp ( nGenExp, true );
}

// *****************************************************
// Desc: ªÛ¥ÅE¶ ¡◊ø©º≠ πﬂª˝«œ¥¬ ∞Ê«Ëƒ° (∆ƒ∆º or ΩÃ±€)
// *****************************************************
void GLChar::ReceiveKillExp( const STARGETID &cTargetID, bool bConftSchool/* =false */, bool bSummonReceive/* =false */ )
{
	if ( !IsValidBody() )	return;

	//	Note : ∆ƒ∆º¿œ ∞ÊøÅE
	//
	if ( m_dwPartyID!=PARTY_NULL )
	{
		GLPARTY_FIELD *pParty = m_pGLGaeaServer->GetParty ( m_dwPartyID );
		if ( pParty )
		{
			//	Note : ∞Ê«Ëƒ° ºˆΩ≈ ∞°¥…«— ∆ƒ∆º ¿ŒøÅE
			std::vector<DWORD> vecPARTY;
			vecPARTY.reserve ( MAXPARTY );

			//	Note : ∞Ê«Ëƒ° ºˆΩ≈ ∞°¥…«— ∆ƒ∆º¿ŒøÅE ( ¿⁄Ω≈ ∆˜«‘. )
			//
			WORD wLEVEL_TOTAL(0);
			WORD wLEVEL_LOWER(USHRT_MAX);
			GLPARTY_FIELD::MEMBER_ITER iter = pParty->m_cMEMBER.begin ();
			GLPARTY_FIELD::MEMBER_ITER iter_end = pParty->m_cMEMBER.end ();
			for ( ; iter!=iter_end; ++iter )
			{
				DWORD dwPARTY_MBR = (*iter).first;
				PGLCHAR pChar = m_pGLGaeaServer->GetChar ( dwPARTY_MBR );
				if ( !pChar || pChar->m_pLandMan!=m_pLandMan )		continue;
				if ( !pChar->IsValidBody() )						continue;
			
				D3DXVECTOR3 vDis = GetPosition() - pChar->GetPosition();
				float fDis = D3DXVec3Length ( &vDis );
				if ( fDis > GLCONST_CHAR::fPARTYEXPRANGE )			continue;
		
				wLEVEL_TOTAL += pChar->m_wLevel;
				if ( wLEVEL_LOWER>pChar->m_wLevel )		wLEVEL_LOWER = pChar->m_wLevel;

				vecPARTY.push_back ( dwPARTY_MBR );
			}

			DWORD dwINDEX = DWORD(vecPARTY.size());
			if ( dwINDEX>0 )	--dwINDEX;
			GASSERT(dwINDEX<MAXPARTY);

			float fEXP_ONE(0), fEXP_MBR(0);
			fEXP_ONE = float ( GLCONST_CHAR::aPARTYKILLEXP_ONE[dwINDEX] * 0.01f );

			//	Note : ∞Ê«Ëƒ° ∞ËªÅE
			int nGenExp = GLOGICEX::CALCKILLEXP ( wLEVEL_LOWER, cTargetID, m_pLandMan );
			if ( bConftSchool )		nGenExp = int ( nGenExp * GLCONST_CHAR::fCONFRONT_SCHOOL_EXP_SCALE );
			// º“»Øºˆ∞° ∞Ê«Ëƒ° »πµÊ«ﬂ¿ª ∞‹øÅE1/3∏∏ »πµÅE
			if ( bSummonReceive ) nGenExp /= 3; 

			//	'∞Ê«Ëƒ°'∏¶ ∆ƒ∆º ∞Ê«Ëƒ°∑Œ »ØªÅE
			nGenExp = int ( nGenExp * fEXP_ONE );

			//	Note : ∞¢∞¢ ∆ƒ∆ºø¯ø°∞‘ ∏¬∞‘ ∞Ê«Ëƒ° πﬂª˝.
			//
			DWORD dwSIZE = (DWORD) vecPARTY.size();
			for ( DWORD i=0; i<dwSIZE; ++i )
			{
				DWORD dwPARTY_MBR = vecPARTY[i];
				PGLCHAR pChar = m_pGLGaeaServer->GetChar ( dwPARTY_MBR );
				if ( !pChar )						continue;

				int nMemExp = int ( nGenExp * pChar->m_wLevel / float(wLEVEL_TOTAL) );
				
				//	∑π∫ß¬˜¿Ã(ºˆΩ≈¿⁄∑æ-√÷¿˙∑æ)ø° ∞®º“¿≤¿ª π›øµ«œø© ∞Ê«Ëƒ°∏¶ ∞®º“Ω√≈¥.
				nMemExp -= int ( nMemExp * ( pChar->m_wLevel - wLEVEL_LOWER ) * GLCONST_CHAR::fPARTYEXP_S );

				// æ∆¿Ã≈€ ø°µ∆Æø°º≠ ¿‘∑¬«— ∞Ê«Ëƒ° πË¿≤ ¿˚øÅE(¡ÿ«ÅE
				nMemExp = int( (float)nMemExp * pChar->GetExpMultipleRateFromSlotItem() );

				if ( nMemExp < 0 )		nMemExp = 0;	//	ºˆΩ≈ ∞Ê«Ëƒ°∞° - ∞° µ«¡ÅEæ µµ∑œ.

				pChar->ReceivePartyExp ( nMemExp );

				//disabled
				//enable this if you want to earn CP in party KILL
				int iThisLevel = 0;
				iThisLevel =  GLOGICEX::CALCKILLCP ( cTargetID, m_pLandMan );
				pChar->ReceiveCP ( iThisLevel , dwSIZE); //add cp
			}
		}
	}
	else
	{
		//*/*/*/*//	Note : ∞Ê«Ëƒ° ∞ËªÅE
		int nGenExp = GLOGICEX::CALCKILLEXP ( GETLEVEL(), cTargetID, m_pLandMan );
		if ( bConftSchool )		nGenExp = int ( nGenExp * GLCONST_CHAR::fCONFRONT_SCHOOL_EXP_SCALE );
		// º“»Øºˆ∞° ∞Ê«Ëƒ° »πµÊ«ﬂ¿ª ∞‹øÅE1/3∏∏ »πµÅE
		if ( bSummonReceive ) nGenExp /= 3; 

		// æ∆¿Ã≈€ ø°µ∆Æø°º≠ ¿‘∑¬«— ∞Ê«Ëƒ° πË¿≤ ¿˚øÅE(¡ÿ«ÅE
		int nMyGenExp = int( (float)nGenExp * GetExpMultipleRateFromSlotItem() );

		/*if( m_wSex == 0 )
		{
			nMyGenExp *= 2;
		}*/

		//	Note : ∞Ê«Ëƒ° ¡ı∞° √≥∏Æ.
		//
		ReceiveExp ( nMyGenExp, true );
		int iThisLevel = 0;
		iThisLevel =  GLOGICEX::CALCKILLCP ( cTargetID, m_pLandMan );
		ReceiveCP( iThisLevel , 1); //add cp
	}

	//	Note : questøÕ ø¨∞·µ» √≥∏Æ.
	//
	if ( cTargetID.emCrow==CROW_MOB )
	{
		PGLCROW pCROW = m_pLandMan->GetCrow ( cTargetID.dwID );
		if ( pCROW )
		{
			DoQuestMobKill ( pCROW->m_sNativeID );
		}
	}
}

// *****************************************************
// Desc: ªÛ¥ÅE¶ ∂ß∑¡º≠ πﬂª˝«œ¥¬ ∞Ê«Ëƒ° (∆ƒ∆º or ΩÃ±€)
// *****************************************************
void GLChar::ReceiveAttackExp( const STARGETID &cTargetID, DWORD dwDamage, BOOL bPartySkill, bool bConftSchool/* =false */, 
							   bool bSummonReceive/* =false */ )
{
	if ( !IsValidBody() )	return;

	//	Note : ∆ƒ∆º¿œ ∞ÊøÅE
	//
	if ( m_dwPartyID!=PARTY_NULL )
	{
		GLPARTY_FIELD *pParty = m_pGLGaeaServer->GetParty ( m_dwPartyID );
		if ( pParty )
		{
			//	Note : ∞Ê«Ëƒ° ºˆΩ≈ ∞°¥…«— ∆ƒ∆º ¿ŒøÅE
			std::vector<DWORD> vecPARTY;
			vecPARTY.reserve ( MAXPARTY );

			//	Note : ∞Ê«Ëƒ° ºˆΩ≈ ∞°¥…«— ∆ƒ∆º¿ŒøÅE ( ¿⁄Ω≈ ∆˜«‘. )
			//
			WORD wLEVEL_TOTAL(0);
			WORD wLEVEL_LOWER(USHRT_MAX);
			GLPARTY_FIELD::MEMBER_ITER iter = pParty->m_cMEMBER.begin ();
			GLPARTY_FIELD::MEMBER_ITER iter_end = pParty->m_cMEMBER.end ();
			for ( ; iter!=iter_end; ++iter )
			{
				DWORD dwPARTY_MBR = (*iter).first;
				PGLCHAR pChar = m_pGLGaeaServer->GetChar ( dwPARTY_MBR );
				if ( !pChar || pChar->m_pLandMan!=m_pLandMan )		continue;
				if ( !pChar->IsValidBody() )						continue;
			
				D3DXVECTOR3 vDis = GetPosition() - pChar->GetPosition();
				float fDis = D3DXVec3Length ( &vDis );
				if ( fDis > GLCONST_CHAR::fPARTYEXPRANGE )			continue;
		
				wLEVEL_TOTAL += pChar->m_wLevel;
				if ( wLEVEL_LOWER>pChar->m_wLevel )		wLEVEL_LOWER = pChar->m_wLevel;

				vecPARTY.push_back ( dwPARTY_MBR );
			}

			DWORD dwINDEX = DWORD(vecPARTY.size());
			if ( dwINDEX>0 )	--dwINDEX;
			GASSERT(dwINDEX<MAXPARTY);

			float fEXP_ONE(0);
			fEXP_ONE = float ( GLCONST_CHAR::aPARTYEXP_ONE[dwINDEX] * 0.01f );

			//	Note : ∞Ê«Ëƒ°∑Æ ªÅEÅE
			int nGenExp = GLOGICEX::CALCATTACKEXP ( wLEVEL_LOWER, cTargetID, m_pLandMan, dwDamage );
			if ( bConftSchool )		nGenExp = int ( nGenExp * GLCONST_CHAR::fCONFRONT_SCHOOL_EXP_SCALE );
			// º“»Øºˆ∞° »πµÊ«— ∞Ê«Ëƒ°¥¬ 1/3∑Œ «—¥Ÿ.
			if ( bSummonReceive )	nGenExp /= 3;

			//	'∞Ê«Ëƒ°'∏¶ ¡˜¡¢ πﬂª˝Ω√≈≤ ¥ÁªÁ¿⁄¿« ∞Ê«Ëƒ°∑Æ ∞ËªÅE
			nGenExp = int ( nGenExp * fEXP_ONE );

			//	Note : ∞¢∞¢ ∆ƒ∆ºø¯ø°∞‘ ∏¬∞‘ ∞Ê«Ëƒ° πﬂª˝.
			//
			DWORD dwSIZE = (DWORD) vecPARTY.size();
			for ( DWORD i=0; i<dwSIZE; ++i )
			{
				DWORD dwPARTY_MBR = vecPARTY[i];
				PGLCHAR pChar = m_pGLGaeaServer->GetChar ( dwPARTY_MBR );
				if ( !pChar )						continue;

				//	∆ƒ∆º ∫–πÅE∞Ê«Ëƒ°.
				int nMemExp = int ( nGenExp * pChar->m_wLevel / float(wLEVEL_TOTAL) );
				//	∑π∫ß¬˜¿Ã(ºˆΩ≈¿⁄∑æ-√÷¿˙∑æ)ø° ∞®º“¿≤¿ª π›øµ«œø© ∞Ê«Ëƒ°∏¶ ∞®º“Ω√≈¥.
				nMemExp -= int ( nMemExp * ( pChar->m_wLevel - wLEVEL_LOWER ) * GLCONST_CHAR::fPARTYEXP_S );

				// æ∆¿Ã≈€ ø°µ∆Æø°º≠ ¿‘∑¬«— ∞Ê«Ëƒ° πË¿≤ ¿˚øÅE(¡ÿ«ÅE
				nMemExp = int( (float)nMemExp * pChar->GetExpMultipleRateFromSlotItem() );

				if ( nMemExp < 0 )	nMemExp = 0;	//	ºˆΩ≈ ∞Ê«Ëƒ°∞° - ∞° µ«¡ÅEæ µµ∑œ.

#if defined(TH_PARAM) || defined(MYE_PARAM) || defined(MY_PARAM) || defined(KR_PARAM)
				// ∆ƒ∆º¿œ ∞ÊøÅE« ªÁ¿ÃπÅEƒ´∆ÅE∞Ê«Ëƒ°
				if( pChar->m_dwThaiCCafeClass == 1 || pChar->m_nMyCCafeClass == 1 ) // Aµ˚Õﬁ
				{
					float fTemp = (float)nMemExp;
					fTemp *= 1.5f; // IP BONUS - EXP
					nMemExp = (int)fTemp;
				}
				else if( pChar->m_dwThaiCCafeClass == 2 || pChar->m_nMyCCafeClass == 2 ) // Bµ˚Õﬁ
				{
					float fTemp = (float)nMemExp;
					fTemp *= 1.3f;
					nMemExp = (int)fTemp;
				}else if( pChar->m_dwThaiCCafeClass == 3 || pChar->m_nMyCCafeClass == 3 ) // Cµ˚Õﬁ
				{
					float fTemp = (float)nMemExp;
					fTemp *= 1.2f;
					nMemExp = (int)fTemp;
				}else if( pChar->m_nMyCCafeClass == 4 )
				{
					float fTemp = (float)nMemExp;
					fTemp *= 1.5f;
					nMemExp = (int)fTemp;
				}
#endif

				pChar->ReceivePartyExp ( nMemExp );

			}
		}
	}
	else
	{
		int nGenExp = GLOGICEX::CALCATTACKEXP ( GETLEVEL(), cTargetID, m_pLandMan, dwDamage );
		if ( bConftSchool )		nGenExp = int ( nGenExp * GLCONST_CHAR::fCONFRONT_SCHOOL_EXP_SCALE );
		// º“»Øºˆ∞° »πµÊ«— ∞Ê«Ëƒ°¥¬ 1/3∑Œ «—¥Ÿ.
		if ( bSummonReceive )	nGenExp /= 3;

		// æ∆¿Ã≈€ ø°µ∆Æø°º≠ ¿‘∑¬«— ∞Ê«Ëƒ° πË¿≤ ¿˚øÅE(¡ÿ«ÅE
		int nMyGenExp = int( (float)nGenExp * GetExpMultipleRateFromSlotItem() );

#if defined(TH_PARAM) || defined(MYE_PARAM) || defined(MY_PARAM) || defined(KR_PARAM)
		// º÷∑Œ¿œ ∞ÊøÅE« ªÁ¿ÃπÅEƒ´∆ÅE∞Ê«Ëƒ°
		if( m_dwThaiCCafeClass == 1 || m_nMyCCafeClass == 1 ) // Aµ˚Õﬁ
		{
			float fTemp = (float)nMyGenExp;
			fTemp *= 1.5f;
			nMyGenExp = (int)fTemp;
		}
		else if( m_dwThaiCCafeClass == 2 || m_nMyCCafeClass == 2 ) // Bµ˚Õﬁ
		{
			float fTemp = (float)nMyGenExp;
			fTemp *= 1.3f;
			nMyGenExp = (int)fTemp;
		}else if( m_dwThaiCCafeClass == 3 || m_nMyCCafeClass == 3 ) // Cµ˚Õﬁ
		{
			float fTemp = (float)nMyGenExp;
			fTemp *= 1.2f;
			nMyGenExp = (int)fTemp;
		}else if( m_nMyCCafeClass == 4 )
		{
			float fTemp = (float)nMyGenExp;
			fTemp *= 1.5f;
			nMyGenExp = (int)fTemp;
		}
#endif
		ReceiveExp ( nMyGenExp, true );
	}
}

HRESULT GLChar::CheckInstanceItem ()
{
	EMSLOT emRHand = GetCurRHand();
	EMSLOT emLHand = GetCurLHand();

	SITEM* pRHAND = GET_SLOT_ITEMDATA ( emRHand );
	SITEM* pLHAND = GET_SLOT_ITEMDATA ( emLHand );

	//	ªÁøÅE°¥… »ΩºÅE∏π≈≠ ªÁøÅE√ø° ∏µŒ º“¡¯µ«æÅEæ∆¿Ã≈∆ ªÁ∂Û¡ˆ∞‘ ∏∏µÅE
	if ( pLHAND && pLHAND->sDrugOp.bInstance )
	{
		if ( GET_SLOT_ITEM(emLHand).wTurnNum==0 )
		{
			//	æ∆¿Ã≈∆ ¡¶∞≈.
			RELEASE_SLOT_ITEM(emLHand);

				//	[¿⁄Ω≈ø°∞‘] SLOTø° ¿÷æ˙¥ÅEæ∆¿Ã≈∆ ¡¶∞≈.
			GLMSG::SNETPC_PUTON_RELEASE NetMsg_PutOn_Release(emLHand);
			NetMsg_PutOn_Release.bRefresh = true;
			m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg_PutOn_Release);
		}
		else
		{
			//	[¿⁄Ω≈ø°∞‘] ¿ŒπÅEæ∆¿Ã≈∆ º“∏µ .
			GLMSG::SNETPC_PUTON_DRUG_UPDATE NetMsg_PutOn_Update;
			NetMsg_PutOn_Update.emSlot = emLHand;
			NetMsg_PutOn_Update.wTurnNum = GET_SLOT_ITEM(emLHand).wTurnNum;
			m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg_PutOn_Update);
		}
	}

	if ( pRHAND && pRHAND->sDrugOp.bInstance )
	{
		if ( GET_SLOT_ITEM(emRHand).wTurnNum )
		{
			//	æ∆¿Ã≈∆ ¡¶∞≈.
			RELEASE_SLOT_ITEM(emRHand);

				//	[¿⁄Ω≈ø°∞‘] SLOTø° ¿÷æ˙¥ÅEæ∆¿Ã≈∆ ¡¶∞≈.
			GLMSG::SNETPC_PUTON_RELEASE NetMsg_PutOn_Release(emRHand);
			NetMsg_PutOn_Release.bRefresh = true;
			m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg_PutOn_Release);
		}
		else
		{
			//	[¿⁄Ω≈ø°∞‘] ¿ŒπÅEæ∆¿Ã≈∆ º“∏µ .
			GLMSG::SNETPC_PUTON_DRUG_UPDATE NetMsg_PutOn_Update;
			NetMsg_PutOn_Update.emSlot = emRHand;
			NetMsg_PutOn_Update.wTurnNum = GET_SLOT_ITEM(emRHand).wTurnNum;
			m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg_PutOn_Update);
		}
	}

	return S_OK;
}

void GLChar::ReceiveLivingPoint ( int nVerLP )
{
	if ( !IsValidBody() )	return;

	//	Note : ª˝»∞ ¡°ºÅE∫Ø∞ÅE
	//
	m_nLiving += nVerLP;
	
	//	Note : ª˝»∞¡°ºÅE≈¨∂Û¿Ãæ∆Æø° π›øµ.
	//
	GLMSG::SNETPC_UPDATE_LP NetMsg;
	NetMsg.nLP = m_nLiving;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
}

//add pk
void GLChar::ReceivePkWinPoint ( DWORD dwPkWin , std::string strKilled)
{
	GLMSG::SNETPC_UPDATE_PKWIN NetMsg;
	NetMsg.dwPkWin = dwPkWin;
	//if(strKilled.length() >= 16) strKilled.resize(15); //pk bug
	//NetMsg.strKilled = strKilled.c_str();
	StringCchCopy ( NetMsg.szName , CHAR_SZNAME+1, strKilled.c_str() );

	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	PKWINUP();

	GLMSG::SNETPC_UPDATE_PKWIN_BRD NetMsgBrd;
	NetMsgBrd.dwGaeaID = m_dwGaeaID;
	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
}

void GLChar::ReceivePkLossPoint ( DWORD dwPkLoss , std::string strKilledBy , std::string strKilled  , DWORD dwGaeaID )
{
	GLMSG::SNETPC_UPDATE_PKLOSS NetMsg;
	NetMsg.dwPkLoss = dwPkLoss;
	PGLCHAR pChar = m_pGLGaeaServer->GetChar ( dwGaeaID );
	if ( pChar )
	{
	
	const EMCHARCLASS emCharClass = m_emClass;
	const int nClassType = CharClassToIndex ( emCharClass );
	const EMCHARCLASS emCharClass2 = pChar->m_emClass;
	const int nClassType2 = CharClassToIndex ( emCharClass2 );

	StringCchCopy ( NetMsg.szNameKilledBy , CHAR_SZNAME+1, strKilledBy.c_str() );
	StringCchCopy ( NetMsg.szNameKilled , CHAR_SZNAME+1, strKilled.c_str() );
	//NetMsg.strKilledBy = strKilledBy.c_str();
	//NetMsg.strKilled = strKilled.c_str();

	NetMsg.dwGaeaIDKilled = m_dwGaeaID;
	NetMsg.dwGaeaIDKilledBy = dwGaeaID;

	NetMsg.dwSchoolKilled = m_wSchool;
	NetMsg.dwSchoolKilledBy = pChar->m_wSchool;

	NetMsg.dwClassKilled = nClassType;
	NetMsg.dwClassKilledBy = nClassType2;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	PKLOSSUP();

	GLMSG::SNETPC_UPDATE_PKLOSS_BRD NetMsgBrd;
	NetMsgBrd.dwGaeaIDKilled = m_dwGaeaID;
	NetMsgBrd.dwGaeaIDKiller = dwGaeaID;
	NetMsgBrd.dwSchoolKilled = m_wSchool;
	NetMsgBrd.dwSchoolKilledBy = pChar->m_wSchool;
	NetMsgBrd.dwClassKilled = nClassType;
	NetMsgBrd.dwClassKilledBy = nClassType2;
	StringCchCopy ( NetMsgBrd.szNameKilledBy , CHAR_SZNAME+1, strKilledBy.c_str() );
	StringCchCopy ( NetMsgBrd.szNameKilled , CHAR_SZNAME+1, strKilled.c_str() );
	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
	}
}

void GLChar::ReceiveCP (DWORD dwRCLvl , WORD wRCNum ) //add cp
{
	GLMSG::SNETPC_UPDATE_CP NetMsg;
	NetMsg.dwRCLvl	= dwRCLvl;
	NetMsg.wRCNum	= wRCNum;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);

	CP_UP( dwRCLvl,wRCNum );	
}

/*BOOL GLChar::ReceiveDuelWin ( LONGLONG llWin, WORD wType  ) //add duel bet
{
	if ( !DuelWinReward ( llWin, wType) ) return FALSE;

	GLMSG::SNETPC_UPDATE_DUELWIN NetMsg;
	NetMsg.llWin = llWin;
	NetMsg.wType = wType;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);

	return TRUE;
}

BOOL GLChar::ReceiveDuelLoss ( LONGLONG llLoss, WORD wType  ) //add duel bet
{
	if ( !DuelLossReward ( llLoss, wType) ) return FALSE;

	GLMSG::SNETPC_UPDATE_DUELLOSS NetMsg;
	NetMsg.llLoss = llLoss;
	NetMsg.wType = wType;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);

	return TRUE;
}*/


BOOL GLChar::RecieveQItemFact ( const SNATIVEID nidITEM )
{
	// ≈ª∞Õ ≈æΩ¬Ω√ ¿˚øÅE»µ 
	if ( m_bVehicle ) return FALSE;

	RECEIVE_QITEMFACT ( nidITEM );

	GLMSG::SNETPC_QITEMFACT_BRD NetMsgBrd;
	NetMsgBrd.dwGaeaID = m_dwGaeaID;
	NetMsgBrd.sFACT = m_sQITEMFACT;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgBrd);

	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );

	return TRUE;
}

void GLChar::ReceiveEventEx( const EMGM_EVENT_TYPE emType, const WORD wValue )
{
	//	Memo :	wValue ∞™¿Ã 0¿Ã∏ÅE¿Ã∫•∆Æ ¡æ∑·∏¶ ¿«πÃ«—¥Ÿ.
	if( wValue > 0 )
	{
		RECEIVE_EVENTFACT_BEGIN( emType, wValue );

		GLMSG::SNETPC_EVENTFACT_BRD NetMsgBrd;
		NetMsgBrd.dwGaeaID = m_dwGaeaID;
		NetMsgBrd.emType = emType;
		NetMsgBrd.wValue = wValue;

		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgBrd);
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
	}
	else
	{
		RECEIVE_EVENTFACT_END( emType );
		
		GLMSG::SNETPC_EVENTFACT_END_BRD NetMsgBrd;
		NetMsgBrd.dwGaeaID = m_dwGaeaID;
		NetMsgBrd.emType = emType;

		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgBrd);
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBrd );
	}
}

void GLChar::ReceiveBeginEvent ( const SEventState emType )
{
	//** Add EventTime
	// ¿Ã∫•∆Æ Ω√∞£¿ª ¥ŸΩ√ º¬∆√«—¥Ÿ.
	CTime	  crtTime      = CTime::GetCurrentTime();
	m_sEventTime.loginTime = crtTime.GetTime();
	m_bEventStart		   = FALSE;
	m_bEventApply		   = FALSE;

	GLMSG::SNET_GM_LIMIT_EVENT_BEGIN_FB NetMsgEventBeginFb;
	NetMsgEventBeginFb.start_Lv		= emType.MinEventLevel;
	NetMsgEventBeginFb.end_Lv	    = emType.MaxEventLevel;
	NetMsgEventBeginFb.play_Time     = emType.EventPlayTime;
	NetMsgEventBeginFb.buster_Time   = emType.EventBusterTime;
	NetMsgEventBeginFb.expGain_Rate  = emType.fExpGainRate;
	NetMsgEventBeginFb.itemGain_Rate = emType.fItemGainRate;

	//add btg attack
	NetMsgEventBeginFb.attackGain_Rate = emType.fAttackGainRate;

	if( emType.MinEventLevel <= GETLEVEL() && emType.MaxEventLevel >= GETLEVEL() )
	{
		m_bEventApply = TRUE;
	}


	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgEventBeginFb);
}

void GLChar::ReceiveVietnam( const __time64_t initTime )
{
	m_dwVietnamGainType = GAINTYPE_MAX;
	m_sVietnamSystem.Init();
	m_sVietnamSystem.loginTime = initTime;
	m_sVietnamSystem.gameTime  = 0;

	GLMSG::SNETPC_VIETNAM_ALLINITTIME NetMsg;
	NetMsg.initTime = initTime;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
}

HRESULT GLChar::MsgClubStorage ()
{
	GLCLUB *pCLUB = m_pGLGaeaServer->GetClubMan().GetClub ( m_dwGuild );
	if ( !pCLUB )
	{
		return S_OK;
	}

	if ( pCLUB->m_dwMasterID != m_dwCharID )
	{
		return S_OK;
	}

	//	Note : ≈¨∑¥ √¢∞ÅE¡§∫∏ ∏ÆªÅE
	//
	GLMSG::SNET_CLUB_STORAGE_RESET NetMsgClubStorageReset;
	m_pGLGaeaServer->SENDTOCLIENT ( GETCLIENTID (), &NetMsgClubStorageReset );

	//	Note : √¢∞˙‹« ±‚∫ª ¡§∫∏ ¿ÅE€.
	//
	GLMSG::SNET_CLUB_STORAGE_UPDATE_MONEY NetMsgMoney;
	NetMsgMoney.lnMoney = pCLUB->m_lnStorageMoney;
	m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsgMoney);

	//	Note : æ∆¿Ã≈€¿ª «œ≥™æø ¿ÅE€.
	//
	GLMSG::SNET_CLUB_GETSTORAGE_ITEM NetMsgItem;

	// ≈¨∂Û¿Ãæ∆Æø° √¢∞ÅE¿ÅE€
	// ∑Á«¡∏¶ µπ∏Èº≠ «œ≥™æø ¿ÅE€

	DWORD dwRANK = pCLUB->m_dwRank;
	if ( dwRANK >= MAX_CLUBSTORAGE )	dwRANK = MAX_CLUBSTORAGE-1;

	for ( DWORD i=0; i<=dwRANK; ++i )
	{
		NetMsgItem.dwChannel = i;

		GLInventory::CELL_MAP* pInvenList = pCLUB->m_cStorage[i].GetItemList();

		GLInventory::CELL_MAP_ITER iter = pInvenList->begin();
		GLInventory::CELL_MAP_ITER iter_end = pInvenList->end();
		for ( ; iter!=iter_end; ++iter )
		{
			SINVENITEM* pInvenItem = (*iter).second;

			NetMsgItem.Data = *pInvenItem;
			
			m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsgItem );
		}
	}

	//	Note : ≈¨∑¥¿« ºˆ¿Õ ∞ªΩ≈ ø‰√ª.
	MsgReqClubInComeReNew(NULL);

	return S_OK;
}

bool GLChar::IsCHATBLOCK ()
{
	if ( m_tCHATBLOCK==0 )	return false;

	CTime cBLOCK(m_tCHATBLOCK);
	CTime cCUR(CTime::GetCurrentTime());

	//	∫˙”∞Ω√∞£¿Œ¡ÅE∞ÀªÅE
	if ( cBLOCK > cCUR )	return true;

	//	Ω√∞£¿Ã √ ∞ÅEµ«æ˙¿ª ∞ÊøÅE¬ Ω√∞£¿ª ∏Æº¬.
	m_tCHATBLOCK = 0;

	return false;
}

HRESULT GLChar::MsgGetFieldAllItem ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ªı∑Œ √ﬂ∞°µ«¥¬ ≥ÅEÂøÕ ¡∏º” ≥ÅEÂ∏¶ «•Ω√.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
		//	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			if ( !pItemDrop )
			{
				DEBUGMSG_WRITE ( "Item is Lost in MsgGetFieldAllItem()" );
				continue;
			}
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM ) continue;

				//	æ∆¿Ã≈∆¿Ã ¥Ÿ∏• ªÁ∂˜ø°∞‘ øπæ‡µ«æÅE¿÷¿∏∏ÅE
				if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				SITEM *pItem = GLItemMan::GetInstance().GetItem(pItemDrop->sItemCustom.sNativeID);
				if ( !pItem ) continue;

/*
				WORD wPosX, wPosY;
				BOOL bOk = m_cInventory.FindInsrtable ( 
					pItem->sBasicOp.wInvenSizeX, 
					pItem->sBasicOp.wInvenSizeY, 
					wPosX, 
					wPosY );

				if ( !bOk )	
				{
					// ∆÷¿ª ¡¶∞≈«—¥Ÿ
					// m_pGLGaeaServer->DropOutPET ( m_dwPetGUID, false );

					//	¿ŒπÅEÃ ∞°µÊ¬˜º≠ æ∆¿Ã≈∆¿ª ≥÷¿ªºÅEæ¯¿Ω¿ª æÀ∏≤ 
					GLMSG::SNETPET_MSG_NOTENOUGHINVEN NetMsg;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
					return S_OK;
				}
*/
				// ?æ∆¿Ã≈€¿Ã∏ÅE
				if ( pItem->sBasicOp.emItemType==ITEM_QITEM ) continue;

				// º¯¬˜Ω¿µÊΩ√ ∆ƒ∆ºø¯¿Ã º¯¬˜Ω¿µÊµ«¡ÅEæ ¥¬ πˆ±◊∑Œ ¿Œ«ÿ
				// ∆ƒ≈∏ø° ¥ÅE— ∞ÀªÁ¥¬ ø©±‚º≠ «œ¡ÅEæ ∞ÅEΩ«¡¶ æ∆¿Ã≈€ ¡›¥¬
				// «‡¿ßø°º≠ √≥∏Æ«œµµ∑œ ºˆ¡§. 
/*
				// ∆ƒ∆ºø¯¿Ã∞ÅE¿Ã∫•∆Æ æ∆¿Ã≈€¿Ã æ∆¥“∂ß ∆ƒ∆º ∑Á∆√¿Œ¡ÅE∞ÀªÁ»ƒ √≥∏Æ.
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty && !pItem->ISEVENTITEM() )
				{
					bool ballot = pParty->DOITEM_ALLOT ( this, pItemDrop, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pItemDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_ITEM;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					i = 0;
				}
	
			}
		}

		//	Note : - Money - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		MONEYDROPNODE *pMoneyNode = pQuadNode->pData->m_MoneyList.m_pHead;
		for ( ; pMoneyNode; pMoneyNode = pMoneyNode->pNext )
		{
			PMONEYDROP pMoneyDrop = pMoneyNode->Data;
			if ( !pMoneyDrop ) 
			{
				DEBUGMSG_WRITE ( "Money is Lost in MsgGetFieldAllItem()" );
				continue;
			}
			nX = int(pMoneyDrop->vPos.x); nZ = int(pMoneyDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pMoneyDrop->dwGlobID;
				if ( dwID>=MAXMONEY ) continue;

				//	æ∆¿Ã≈∆¿Ã ¥Ÿ∏• ªÁ∂˜ø°∞‘ øπæ‡µ«æÅE¿÷¿∏∏ÅE
				if ( !pMoneyDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				// º¯¬˜Ω¿µÊΩ√ ∆ƒ∆ºø¯¿Ã º¯¬˜Ω¿µÊµ«¡ÅEæ ¥¬ πˆ±◊∑Œ ¿Œ«ÿ
				// ∆ƒ≈∏ø° ¥ÅE— ∞ÀªÁ¥¬ ø©±‚º≠ «œ¡ÅEæ ∞ÅEΩ«¡¶ æ∆¿Ã≈€ ¡›¥¬
				// «‡¿ßø°º≠ √≥∏Æ«œµµ∑œ ºˆ¡§. 
/*
				// ∆ƒ∆º ∑Á∆√∞ÀªÅE
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty )
				{
					bool ballot = pParty->DOMONEY_ALLOT ( this, pMoneyDrop, m_pLandMan, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pMoneyDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_MONEY;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					i = 0;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}

HRESULT GLChar::MsgGetFieldRareItem ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ªı∑Œ √ﬂ∞°µ«¥¬ ≥ÅEÂøÕ ¡∏º” ≥ÅEÂ∏¶ «•Ω√.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
        //	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			if ( !pItemDrop ) 
			{
				DEBUGMSG_WRITE ( "Item is Lost in MsgGetFieldRareItem()" );
				continue;
			}
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM ) continue;

				//	æ∆¿Ã≈∆¿Ã ¥Ÿ∏• ªÁ∂˜ø°∞‘ øπæ‡µ«æÅE¿÷¿∏∏ÅE
				if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				SITEM *pItem = GLItemMan::GetInstance().GetItem(pItemDrop->sItemCustom.sNativeID);
				if ( !pItem ) continue;
/*
				WORD wPosX, wPosY;
				BOOL bOk = m_cInventory.FindInsrtable ( 
					pItem->sBasicOp.wInvenSizeX, 
					pItem->sBasicOp.wInvenSizeY, 
					wPosX, 
					wPosY );

				if ( !bOk )	
				{
					// ∆÷¿ª ¡¶∞≈«—¥Ÿ
					//m_pGLGaeaServer->DropOutPET ( m_dwPetGUID, false );

					//	¿ŒπÅEÃ ∞°µÊ¬˜º≠ æ∆¿Ã≈∆¿ª ≥÷¿ªºÅEæ¯¿Ω¿ª æÀ∏≤ 
					GLMSG::SNETPET_MSG_NOTENOUGHINVEN NetMsg;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
					return S_OK;
				}
*/
				// ∑πæ˚⁄∆¿Ã≈€¿Ã æ∆¥œ∏ÅE
				if ( pItem->sBasicOp.emLevel != LEVEL_RARE ) continue;

				// º¯¬˜Ω¿µÊΩ√ ∆ƒ∆ºø¯¿Ã º¯¬˜Ω¿µÊµ«¡ÅEæ ¥¬ πˆ±◊∑Œ ¿Œ«ÿ
				// ∆ƒ≈∏ø° ¥ÅE— ∞ÀªÁ¥¬ ø©±‚º≠ «œ¡ÅEæ ∞ÅEΩ«¡¶ æ∆¿Ã≈€ ¡›¥¬
				// «‡¿ßø°º≠ √≥∏Æ«œµµ∑œ ºˆ¡§. 
/*
				// ∆ƒ∆ºø¯¿Ã∞ÅE¿Ã∫•∆Æ æ∆¿Ã≈€¿Ã æ∆¥“∂ß ∆ƒ∆º ∑Á∆√¿Œ¡ÅE∞ÀªÁ»ƒ √≥∏Æ.
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty && !pItem->ISEVENTITEM() )
				{
					bool ballot = pParty->DOITEM_ALLOT ( this, pItemDrop, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pItemDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_ITEM;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					return S_OK;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}
HRESULT GLChar::MsgGetFieldPotions ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ªı∑Œ √ﬂ∞°µ«¥¬ ≥ÅEÂøÕ ¡∏º” ≥ÅEÂ∏¶ «•Ω√.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
        //	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			if ( !pItemDrop )
			{
				DEBUGMSG_WRITE ( "Item is Lost in MsgGetFieldPotions()" );
				continue;
			}
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM ) continue;

				//	æ∆¿Ã≈∆¿Ã ¥Ÿ∏• ªÁ∂˜ø°∞‘ øπæ‡µ«æÅE¿÷¿∏∏ÅE
				if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				SITEM *pItem = GLItemMan::GetInstance().GetItem(pItemDrop->sItemCustom.sNativeID);
				if ( !pItem ) continue;
/*
				WORD wPosX, wPosY;
				BOOL bOk = m_cInventory.FindInsrtable ( 
					pItem->sBasicOp.wInvenSizeX, 
					pItem->sBasicOp.wInvenSizeY, 
					wPosX, 
					wPosY );

				if ( !bOk )	
				{
					// ∆÷¿ª ¡¶∞≈«—¥Ÿ
					//m_pGLGaeaServer->DropOutPET ( m_dwPetGUID, false );

					//	¿ŒπÅEÃ ∞°µÊ¬˜º≠ æ∆¿Ã≈∆¿ª ≥÷¿ªºÅEæ¯¿Ω¿ª æÀ∏≤ 
					GLMSG::SNETPET_MSG_NOTENOUGHINVEN NetMsg;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
					return S_OK;
				}
*/
				// ∆˜º«¿Ã æ∆¥œ∏ÅE
				if ( pItem->sBasicOp.emItemType != ITEM_CURE ) continue;

				// º¯¬˜Ω¿µÊΩ√ ∆ƒ∆ºø¯¿Ã º¯¬˜Ω¿µÊµ«¡ÅEæ ¥¬ πˆ±◊∑Œ ¿Œ«ÿ
				// ∆ƒ≈∏ø° ¥ÅE— ∞ÀªÁ¥¬ ø©±‚º≠ «œ¡ÅEæ ∞ÅEΩ«¡¶ æ∆¿Ã≈€ ¡›¥¬
				// «‡¿ßø°º≠ √≥∏Æ«œµµ∑œ ºˆ¡§. 

/*
				// ∆ƒ∆ºø¯¿Ã∞ÅE¿Ã∫•∆Æ æ∆¿Ã≈€¿Ã æ∆¥“∂ß ∆ƒ∆º ∑Á∆√¿Œ¡ÅE∞ÀªÁ»ƒ √≥∏Æ.
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty && !pItem->ISEVENTITEM() )
				{
					bool ballot = pParty->DOITEM_ALLOT ( this, pItemDrop, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pItemDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_ITEM;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					return S_OK;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}
HRESULT GLChar::MsgGetFieldMoney ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ªı∑Œ √ﬂ∞°µ«¥¬ ≥ÅEÂøÕ ¡∏º” ≥ÅEÂ∏¶ «•Ω√.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
        //	Note : - Money - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		MONEYDROPNODE *pMoneyNode = pQuadNode->pData->m_MoneyList.m_pHead;
		for ( ; pMoneyNode; pMoneyNode = pMoneyNode->pNext )
		{
			PMONEYDROP pMoneyDrop = pMoneyNode->Data;
			if ( !pMoneyDrop ) 
			{
				DEBUGMSG_WRITE ( "Money is Lost in MsgGetFieldMoney()" );
				continue;
			}
			nX = int(pMoneyDrop->vPos.x); nZ = int(pMoneyDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pMoneyDrop->dwGlobID;
				if ( dwID>=MAXMONEY ) continue;

				//	æ∆¿Ã≈∆¿Ã ¥Ÿ∏• ªÁ∂˜ø°∞‘ øπæ‡µ«æÅE¿÷¿∏∏ÅE
				if ( !pMoneyDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				// º¯¬˜Ω¿µÊΩ√ ∆ƒ∆ºø¯¿Ã º¯¬˜Ω¿µÊµ«¡ÅEæ ¥¬ πˆ±◊∑Œ ¿Œ«ÿ
				// ∆ƒ≈∏ø° ¥ÅE— ∞ÀªÁ¥¬ ø©±‚º≠ «œ¡ÅEæ ∞ÅEΩ«¡¶ æ∆¿Ã≈€ ¡›¥¬
				// «‡¿ßø°º≠ √≥∏Æ«œµµ∑œ ºˆ¡§. 
/*
				// ∆ƒ∆º ∑Á∆√∞ÀªÅE
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty )
				{
					bool ballot = pParty->DOMONEY_ALLOT ( this, pMoneyDrop, m_pLandMan, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pMoneyDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_MONEY;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					return S_OK;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}

HRESULT GLChar::MsgGetFieldSton ( NET_MSG_GENERIC* nmg )
{
//	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	if ( !IsSTATE(EM_GETVA_AFTER) && !(m_pGLGaeaServer->IsReserveServerStop ()) )	return S_FALSE;

	GLMSG::SNETPET_REQ_GETRIGHTOFITEM_FB NetMsg;

	WORD i(0);

	PGLPETFIELD pMyPet = m_pGLGaeaServer->GetPET ( m_dwPetGUID );
	if ( !pMyPet || !pMyPet->IsValid () )	return E_FAIL;

	int nX = int ( pMyPet->m_vPos.x );
	int nZ = int ( pMyPet->m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	BOUDRECT bRect(nX+GLCONST_PET::nMAXVIEWRANGE,nZ+GLCONST_PET::nMAXVIEWRANGE,nX-GLCONST_PET::nMAXVIEWRANGE,nZ-GLCONST_PET::nMAXVIEWRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	//	Note : ªı∑Œ √ﬂ∞°µ«¥¬ ≥ÅEÂøÕ ¡∏º” ≥ÅEÂ∏¶ «•Ω√.
	//
	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
        //	Note : - Item - 
		//
		if ( m_pGLGaeaServer->IsReserveServerStop () ) 
			continue;

		ITEMDROPNODE *pItemNode = pQuadNode->pData->m_ItemList.m_pHead;
		for ( ; pItemNode; pItemNode = pItemNode->pNext )
		{
			PITEMDROP pItemDrop = pItemNode->Data;
			if ( !pItemDrop ) 
			{
				DEBUGMSG_WRITE ( "Item is Lost in MsgGetFieldSton()" );
				continue;
			}
			nX = int(pItemDrop->vPos.x); nZ = int(pItemDrop->vPos.z);

			if ( bRect.IsWithIn(nX,nZ) )
			{
				DWORD dwID = pItemDrop->dwGlobID;
				if ( dwID>=MAXITEM ) continue;

				//	æ∆¿Ã≈∆¿Ã ¥Ÿ∏• ªÁ∂˜ø°∞‘ øπæ‡µ«æÅE¿÷¿∏∏ÅE
				if ( !pItemDrop->IsTakeItem(m_dwPartyID,m_dwGaeaID) ) continue;

				SITEM *pItem = GLItemMan::GetInstance().GetItem(pItemDrop->sItemCustom.sNativeID);
				if ( !pItem ) continue;
/*
				WORD wPosX, wPosY;
				BOOL bOk = m_cInventory.FindInsrtable ( 
					pItem->sBasicOp.wInvenSizeX, 
					pItem->sBasicOp.wInvenSizeY, 
					wPosX, 
					wPosY );

				if ( !bOk )	
				{
					// ∆÷¿ª ¡¶∞≈«—¥Ÿ
					//m_pGLGaeaServer->DropOutPET ( m_dwPetGUID, false );

					//	¿ŒπÅEÃ ∞°µÊ¬˜º≠ æ∆¿Ã≈∆¿ª ≥÷¿ªºÅEæ¯¿Ω¿ª æÀ∏≤ 
					GLMSG::SNETPET_MSG_NOTENOUGHINVEN NetMsg;
					m_pGLGaeaServer->SENDTOCLIENT ( m_dwClientID, &NetMsg );
					return S_OK;
				}
*/
				// ø¨∏∂¡¶∞° æ∆¥œ∏ÅE
				if ( pItem->sBasicOp.emItemType != ITEM_GRINDING 
					&& pItem->sBasicOp.emItemType != ITEM_MATERIALS )
					continue;

				// º¯¬˜Ω¿µÊΩ√ ∆ƒ∆ºø¯¿Ã º¯¬˜Ω¿µÊµ«¡ÅEæ ¥¬ πˆ±◊∑Œ ¿Œ«ÿ
				// ∆ƒ≈∏ø° ¥ÅE— ∞ÀªÁ¥¬ ø©±‚º≠ «œ¡ÅEæ ∞ÅEΩ«¡¶ æ∆¿Ã≈€ ¡›¥¬
				// «‡¿ßø°º≠ √≥∏Æ«œµµ∑œ ºˆ¡§. 
/*
				// ∆ƒ∆ºø¯¿Ã∞ÅE¿Ã∫•∆Æ æ∆¿Ã≈€¿Ã æ∆¥“∂ß ∆ƒ∆º ∑Á∆√¿Œ¡ÅE∞ÀªÁ»ƒ √≥∏Æ.
				GLPARTY_FIELD* pParty = m_pGLGaeaServer->GetParty(m_dwPartyID);
				if ( pParty && !pItem->ISEVENTITEM() )
				{
					bool ballot = pParty->DOITEM_ALLOT ( this, pItemDrop, true );
					if ( !ballot ) continue;
				}
*/
				NetMsg.DroppedItems[i].dwID		 = dwID;
				NetMsg.DroppedItems[i].vPos		 = pItemDrop->vPos;
				NetMsg.DroppedItems[i].emCrow	 = CROW_ITEM;
				if ( ++i >= MAXRIGHTOFITEM )
				{
					NetMsg.wSum = MAXRIGHTOFITEM;
					m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
					return S_OK;
				}
			}
		}
	}

	if ( i > 0 )
	{
		NetMsg.wSum = i;
		m_pGLGaeaServer->SENDTOCLIENT(m_dwClientID,&NetMsg);
	}

	return S_OK;
}
