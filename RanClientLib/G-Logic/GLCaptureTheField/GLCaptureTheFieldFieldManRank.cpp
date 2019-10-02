#include "StdAfx.h"
#include "GLCaptureTheFieldMan.h"
#include "GLGaeaServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//field server
void GLCaptureTheFieldFieldMan::UpdateRanking( DWORD dwID )
{
	GLCaptureTheField *pCTF = FindCTF ( dwID, FALSE, FALSE );
	if ( !pCTF )	return;

	UpdateRankingPlayerAll( pCTF );
	UpdateRankingPlayerSG( pCTF );
	UpdateRankingPlayerMP( pCTF );
	UpdateRankingPlayerPHX( pCTF );
	UpdateRankingSelf( pCTF );
	//UpdateTowerScore( pCTF );
}

void GLCaptureTheFieldFieldMan::UpdateTower( DWORD dwID )
{
	GLCaptureTheField *pCTF = FindCTF ( dwID, FALSE, FALSE );
	if ( !pCTF )	return;

	UpdateTowerScore( pCTF );
}

void GLCaptureTheFieldFieldMan::UpdateRankingPlayerAll( GLCaptureTheField *pCTF )
{
	if ( !pCTF )	return;

	GLCaptureTheField &sCTF = *pCTF;

	CTF_RANK_PLAYER_VEC		m_vecNew;
	m_vecNew.reserve( sCTF.m_mapScorePlayerAll.size() );

	CTF_RANK_PLAYER_MAP_ITER	pos = sCTF.m_mapScorePlayerAll.begin();
	CTF_RANK_PLAYER_MAP_ITER	end = sCTF.m_mapScorePlayerAll.end();
	for ( ; pos != end; pos++ )
	{
		const SCTF_RANK_PLAYER&	sRankInfo = pos->second;					
		m_vecNew.push_back( sRankInfo );
	}

	std::sort( m_vecNew.begin(), m_vecNew.end() );	

	int nSize = m_vecNew.size();
	for ( int i = 0; i < nSize; ++i )
	{
		m_vecNew[i].wRanking = i+1;
		m_vecNew[i].nIndex = i;
	}

	for ( int i = nSize-1; i > 0; --i )
	{
		if ( m_vecNew[i] == m_vecNew[i-1] )
			m_vecNew[i-1].wRanking = m_vecNew[i].wRanking;			
	}	

	GLMSG::SNET_CAPTURETHEFIELD_RANKING_PLAYER_UPDATE	NetMsg;
	NetMsg.wINDEX = WORD(EMRANKINDEX_ALL);

	for ( int i = 0; i < m_vecNew.size(); ++i )
	{
		CTF_RANK_PLAYER_MAP_ITER iter = sCTF.m_mapScorePlayerAll.find( m_vecNew[i].dwCharID );
		if ( iter == sCTF.m_mapScorePlayerAll.end() )	continue;

		SCTF_RANK_PLAYER&	sRankInfo = iter->second;
		sRankInfo.wRanking = m_vecNew[i].wRanking;
		sRankInfo.nIndex = m_vecNew[i].nIndex;

		if ( m_vecNew[i].nIndex >= 0 && m_vecNew[i].nIndex < CTF_RANKING_NUM ) 
		{
			SCTF_RANK_PLAYER_CLIENT sRank = sRankInfo;
			NetMsg.ADDRANK( sRank );
		}		
	}

	if ( NetMsg.wRankNum > 0 )	
	{
		GLGaeaServer::GetInstance().SENDTOCLIENT_ONMAP( sCTF.m_dwCaptureTheFieldMap, &NetMsg );
		GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF:Update Ranking Player Index:%d RankNum:%d PacketSize:%d", NetMsg.wINDEX, NetMsg.wRankNum, NetMsg.nmg.dwSize );
	}
}

void GLCaptureTheFieldFieldMan::UpdateRankingPlayerSG( GLCaptureTheField *pCTF )
{
	if ( !pCTF )	return;

	GLCaptureTheField &sCTF = *pCTF;

	CTF_RANK_PLAYER_VEC		m_vecNew;
	m_vecNew.reserve( sCTF.m_mapScorePlayerSG.size() );

	CTF_RANK_PLAYER_MAP_ITER	pos = sCTF.m_mapScorePlayerSG.begin();
	CTF_RANK_PLAYER_MAP_ITER	end = sCTF.m_mapScorePlayerSG.end();
	for ( ; pos != end; pos++ )
	{
		const SCTF_RANK_PLAYER&	sRankInfo = pos->second;					
		m_vecNew.push_back( sRankInfo );
	}

	std::sort( m_vecNew.begin(), m_vecNew.end() );	

	int nSize = m_vecNew.size();
	for ( int i = 0; i < nSize; ++i )
	{
		m_vecNew[i].wRanking = i+1;
		m_vecNew[i].nIndex = i;
	}

	for ( int i = nSize-1; i > 0; --i )
	{
		if ( m_vecNew[i] == m_vecNew[i-1] )
			m_vecNew[i-1].wRanking = m_vecNew[i].wRanking;			
	}	

	GLMSG::SNET_CAPTURETHEFIELD_RANKING_PLAYER_UPDATE	NetMsg;
	NetMsg.wINDEX = WORD(EMRANKINDEX_SG);

	for ( int i = 0; i < m_vecNew.size(); ++i )
	{
		CTF_RANK_PLAYER_MAP_ITER iter = sCTF.m_mapScorePlayerSG.find( m_vecNew[i].dwCharID );
		if ( iter == sCTF.m_mapScorePlayerSG.end() )	continue;

		SCTF_RANK_PLAYER&	sRankInfo = iter->second;
		sRankInfo.wRanking = m_vecNew[i].wRanking;
		sRankInfo.nIndex = m_vecNew[i].nIndex;

		if ( m_vecNew[i].nIndex >= 0 && m_vecNew[i].nIndex < CTF_RANKING_NUM ) 
		{
			SCTF_RANK_PLAYER_CLIENT sRank = sRankInfo;
			NetMsg.ADDRANK( sRank );
		}		
	}

	if ( NetMsg.wRankNum > 0 )	
	{
		GLGaeaServer::GetInstance().SENDTOCLIENT_ONMAP( sCTF.m_dwCaptureTheFieldMap, &NetMsg );
		GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF:Update Ranking Player Index:%d RankNum:%d PacketSize:%d", NetMsg.wINDEX, NetMsg.wRankNum, NetMsg.nmg.dwSize );
	}
}

void GLCaptureTheFieldFieldMan::UpdateRankingPlayerMP( GLCaptureTheField *pCTF )
{
	if ( !pCTF )	return;

	GLCaptureTheField &sCTF = *pCTF;

	CTF_RANK_PLAYER_VEC		m_vecNew;
	m_vecNew.reserve( sCTF.m_mapScorePlayerMP.size() );

	CTF_RANK_PLAYER_MAP_ITER	pos = sCTF.m_mapScorePlayerMP.begin();
	CTF_RANK_PLAYER_MAP_ITER	end = sCTF.m_mapScorePlayerMP.end();
	for ( ; pos != end; pos++ )
	{
		const SCTF_RANK_PLAYER&	sRankInfo = pos->second;					
		m_vecNew.push_back( sRankInfo );
	}

	std::sort( m_vecNew.begin(), m_vecNew.end() );	

	int nSize = m_vecNew.size();
	for ( int i = 0; i < nSize; ++i )
	{
		m_vecNew[i].wRanking = i+1;
		m_vecNew[i].nIndex = i;
	}

	for ( int i = nSize-1; i > 0; --i )
	{
		if ( m_vecNew[i] == m_vecNew[i-1] )
			m_vecNew[i-1].wRanking = m_vecNew[i].wRanking;			
	}	

	GLMSG::SNET_CAPTURETHEFIELD_RANKING_PLAYER_UPDATE	NetMsg;
	NetMsg.wINDEX = WORD(EMRANKINDEX_MP);

	for ( int i = 0; i < m_vecNew.size(); ++i )
	{
		CTF_RANK_PLAYER_MAP_ITER iter = sCTF.m_mapScorePlayerMP.find( m_vecNew[i].dwCharID );
		if ( iter == sCTF.m_mapScorePlayerMP.end() )	continue;

		SCTF_RANK_PLAYER&	sRankInfo = iter->second;
		sRankInfo.wRanking = m_vecNew[i].wRanking;
		sRankInfo.nIndex = m_vecNew[i].nIndex;

		if ( m_vecNew[i].nIndex >= 0 && m_vecNew[i].nIndex < CTF_RANKING_NUM ) 
		{
			SCTF_RANK_PLAYER_CLIENT sRank = sRankInfo;
			NetMsg.ADDRANK( sRank );
		}		
	}

	if ( NetMsg.wRankNum > 0 )	
	{
		GLGaeaServer::GetInstance().SENDTOCLIENT_ONMAP( sCTF.m_dwCaptureTheFieldMap, &NetMsg );
		GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF:Update Ranking Player Index:%d RankNum:%d PacketSize:%d", NetMsg.wINDEX, NetMsg.wRankNum, NetMsg.nmg.dwSize );
	}
}

void GLCaptureTheFieldFieldMan::UpdateRankingPlayerPHX( GLCaptureTheField *pCTF )
{
	if ( !pCTF )	return;

	GLCaptureTheField &sCTF = *pCTF;

	CTF_RANK_PLAYER_VEC		m_vecNew;
	m_vecNew.reserve( sCTF.m_mapScorePlayerPHX.size() );

	CTF_RANK_PLAYER_MAP_ITER	pos = sCTF.m_mapScorePlayerPHX.begin();
	CTF_RANK_PLAYER_MAP_ITER	end = sCTF.m_mapScorePlayerPHX.end();
	for ( ; pos != end; pos++ )
	{
		const SCTF_RANK_PLAYER&	sRankInfo = pos->second;					
		m_vecNew.push_back( sRankInfo );
	}

	std::sort( m_vecNew.begin(), m_vecNew.end() );	

	int nSize = m_vecNew.size();
	for ( int i = 0; i < nSize; ++i )
	{
		m_vecNew[i].wRanking = i+1;
		m_vecNew[i].nIndex = i;
	}

	for ( int i = nSize-1; i > 0; --i )
	{
		if ( m_vecNew[i] == m_vecNew[i-1] )
			m_vecNew[i-1].wRanking = m_vecNew[i].wRanking;			
	}	

	GLMSG::SNET_CAPTURETHEFIELD_RANKING_PLAYER_UPDATE	NetMsg;
	NetMsg.wINDEX = WORD(EMRANKINDEX_PHX);

	for ( int i = 0; i < m_vecNew.size(); ++i )
	{
		CTF_RANK_PLAYER_MAP_ITER iter = sCTF.m_mapScorePlayerPHX.find( m_vecNew[i].dwCharID );
		if ( iter == sCTF.m_mapScorePlayerPHX.end() )	continue;

		SCTF_RANK_PLAYER&	sRankInfo = iter->second;
		sRankInfo.wRanking = m_vecNew[i].wRanking;
		sRankInfo.nIndex = m_vecNew[i].nIndex;

		if ( m_vecNew[i].nIndex >= 0 && m_vecNew[i].nIndex < CTF_RANKING_NUM ) 
		{
			SCTF_RANK_PLAYER_CLIENT sRank = sRankInfo;
			NetMsg.ADDRANK( sRank );
		}		
	}

	if ( NetMsg.wRankNum > 0 )	
	{
		GLGaeaServer::GetInstance().SENDTOCLIENT_ONMAP( sCTF.m_dwCaptureTheFieldMap, &NetMsg );
		GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF:Update Ranking Player Index:%d RankNum:%d PacketSize:%d", NetMsg.wINDEX, NetMsg.wRankNum, NetMsg.nmg.dwSize );
	}
}

void GLCaptureTheFieldFieldMan::UpdateTowerScore( GLCaptureTheField *pCTF )
{
	if ( !pCTF )	return;

	GLCaptureTheField &sCTF = *pCTF;

	{	//determine to holder of tower
		CTF_SCORE_TOWER_MAP_ITER	pos = sCTF.m_mapTowerScore.begin();
		CTF_SCORE_TOWER_MAP_ITER	end = sCTF.m_mapTowerScore.end();
		for ( ; pos != end; pos++  )
		{
			SCTF_SCORE_TOWER&	sRankInfo = pos->second;					

			LONGLONG llDAMAGE = 0;
			for ( int i = 0; i < CTF_TOWER_DAMAGE_VAR; ++ i )
			{
				if ( sRankInfo.sDATA[i].llDAMAGE > llDAMAGE)
				{
					llDAMAGE				= sRankInfo.sDATA[i].llDAMAGE;
					sRankInfo.wOWNER		= sRankInfo.sDATA[i].wSCHOOL;
					sRankInfo.llOwnerDamage = sRankInfo.sDATA[i].llDAMAGE;
				}
			}

			if ( sRankInfo.wOWNER != sRankInfo.wOWNERLAST )
			{
				sRankInfo.wOWNERLAST = sRankInfo.wOWNER;

				GLMSG::SNETPC_SERVER_CAPTURETHEFIELD_CAPTURE_AG	NetMsg;
				NetMsg.dwID = pCTF->m_dwID;
				NetMsg.sID = sRankInfo.sCROWID;
				NetMsg.wSCHOOL = sRankInfo.wOWNER;
				GLGaeaServer::GetInstance().SENDTOAGENT ( &NetMsg );

				GLLandMan* pLAND = GLGaeaServer::GetInstance().GetByMapID( SNATIVEID(sCTF.m_dwCaptureTheFieldMap) );
				if ( pLAND )
				{
					PGLCROW pCROW = pLAND->GetCrowID( sRankInfo.sCROWID );
					if ( pCROW )
					{
						//pCROW->SetOwner( sRankInfo.wOWNER );
						GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF:SetOWner Map:%d~%d Crow:%d~%d Owner:%s", 
							SNATIVEID(sCTF.m_dwCaptureTheFieldMap).wMainID,
							SNATIVEID(sCTF.m_dwCaptureTheFieldMap).wSubID,
							sRankInfo.sCROWID.wMainID,
							sRankInfo.sCROWID.wSubID,
							GLCONST_CHAR::strSCHOOLNAME[sRankInfo.wOWNER].c_str() );
					}
				}
			}
		}
	}

	{	//send info to client
		GLMSG::SNET_CAPTURETHEFIELD_TOWER_SCORE_UPDATE	NetMsg;

		CTF_SCORE_TOWER_MAP_ITER	pos = sCTF.m_mapTowerScore.begin();
		CTF_SCORE_TOWER_MAP_ITER	end = sCTF.m_mapTowerScore.end();
		for ( int i=0; pos != end; pos++, ++i  )
		{
			const SCTF_SCORE_TOWER&	sRankInfo = pos->second;					

			if ( i >= CTF_TOWER_MAX )	continue;
			NetMsg.ADDRANK( sRankInfo );
		}

		if ( NetMsg.wNUM > 0 )	
		{
			GLGaeaServer::GetInstance().SENDTOCLIENT_ONMAP( sCTF.m_dwCaptureTheFieldMap, &NetMsg );
			GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF:Update UpdateTowerScore RankNum:%d PacketSize:%d", NetMsg.wNUM, NetMsg.nmg.dwSize );
		}
	}
		
}

void GLCaptureTheFieldFieldMan::UpdateRankingSelf( GLCaptureTheField *pCTF )
{
	if ( !pCTF )	return;

	GLCaptureTheField &sCTF = *pCTF;

	GLMSG::SNET_CAPTURETHEFIELD_RANKING_SELF_UPDATE	NetMsgMy;

	CTF_RANK_PLAYER_MAP_ITER	pos = sCTF.m_mapScorePlayerAll.begin();
	CTF_RANK_PLAYER_MAP_ITER	end = sCTF.m_mapScorePlayerAll.end();

	for ( ; pos != end; pos++ )
	{
		const SCTF_RANK_PLAYER&	sRankInfo = pos->second;
		NetMsgMy.sRank.wRanking		= sRankInfo.wRanking;
		NetMsgMy.sRank.llDAMAGE		= sRankInfo.llDAMAGE;
		NetMsgMy.sRank.wKillNum		= sRankInfo.wKillNum;
		NetMsgMy.sRank.wDeathNum	= sRankInfo.wDeathNum;
		NetMsgMy.sRank.cSCHOOL		= sRankInfo.cSCHOOL;
		NetMsgMy.sRank.cCLASS		= sRankInfo.cCLASS;
		NetMsgMy.sRank.bVALID		= TRUE;

		PGLCHAR pCHAR = GLGaeaServer::GetInstance().GetCharID( sRankInfo.dwCharID );
		if ( pCHAR )
		{
			GLGaeaServer::GetInstance().SENDTOCLIENT( pCHAR->m_dwClientID, &NetMsgMy );
		}
	}
}

void GLCaptureTheFieldFieldMan::CheckWinner( DWORD dwID )
{
	GLCaptureTheField *pCTF = FindCTF ( dwID, FALSE, FALSE );
	if ( !pCTF )	return;
	if ( !pCTF->IsBattleEndAward() )	return;

	GLCaptureTheField &sCTF = *pCTF;

	sCTF.m_mapScoreWinner.clear();
	sCTF.m_wSchoolWinner = MAX_SCHOOL;

	SCTF_HOLDER_MAP			mapHolders;

	{	
		//gather the holders from towers
		CTF_SCORE_TOWER_MAP_ITER	pos = sCTF.m_mapTowerScore.begin();
		CTF_SCORE_TOWER_MAP_ITER	end = sCTF.m_mapTowerScore.end();
		for ( ; pos != end; pos++  )
		{
			SCTF_SCORE_TOWER&	sINFO = pos->second;	

			SCTF_HOLDER_MAP_ITER iter = mapHolders.find( sINFO.wOWNER );
			if( iter != mapHolders.end() )
			{
				SCTF_HOLDER&	sHOLDER = iter->second;
				sHOLDER.llDAMAGE += sINFO.llOwnerDamage;
				sHOLDER.wOWNED ++;
			}
			else
			{
				SCTF_HOLDER sHOLDER;
				sHOLDER.llDAMAGE += sINFO.llOwnerDamage;
				sHOLDER.wOWNED ++;
				sHOLDER.wSCHOOL = sINFO.wOWNER;
				mapHolders[sHOLDER.wSCHOOL] = sHOLDER;
			}
		}
	}

	{
		//sort the holders for rank
		SCTF_HOLDER_VEC		m_vecNew;
		m_vecNew.reserve( mapHolders.size() );

		SCTF_HOLDER_MAP_ITER	pos = mapHolders.begin();
		SCTF_HOLDER_MAP_ITER	end = mapHolders.end();
		for ( ; pos != end; pos++ )
		{
			const SCTF_HOLDER&	sINFO = pos->second;					
			m_vecNew.push_back( sINFO );
		}

		std::sort( m_vecNew.begin(), m_vecNew.end() );	

		int nSize = m_vecNew.size();

		for ( int i = 0; i < nSize; ++i )
		{
			m_vecNew[i].wRanking = i+1;
			m_vecNew[i].nIndex = i;
		}

		for ( int i = nSize-1; i > 0; --i )
		{
			if ( m_vecNew[i] == m_vecNew[i-1] )
			{
				m_vecNew[i-1].wRanking = m_vecNew[i].wRanking;			
			}
		}

		for ( int i = 0; i < m_vecNew.size(); ++i )
		{
			SCTF_HOLDER_MAP_ITER iter = mapHolders.find( m_vecNew[i].wSCHOOL );
			if ( iter == mapHolders.end() )	continue;

			SCTF_HOLDER&	sINFO = iter->second;
			sINFO.wRanking = m_vecNew[i].wRanking;
			sINFO.nIndex = m_vecNew[i].nIndex;	
		}
	}

	{
		//decide the winner
		SCTF_HOLDER_MAP_ITER	pos = mapHolders.begin();
		SCTF_HOLDER_MAP_ITER	end = mapHolders.end();
		for ( ; pos != end; pos++ )
		{
			const SCTF_HOLDER&	sRankInfo = pos->second;
			if ( sRankInfo.wRanking == 1 )
			{
				sCTF.m_wSchoolWinner = sRankInfo.wSCHOOL;
				break;
			}
		}
	}

	{
		//show info to log just incase somethings wrong
		GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF:Winner Check Selected Winner:%d", sCTF.m_wSchoolWinner );
		GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF:Winner Check Holders SIZE:%d", (int)mapHolders.size() );
		SCTF_HOLDER_MAP_ITER	pos = mapHolders.begin();
		SCTF_HOLDER_MAP_ITER	end = mapHolders.end();
		for ( ; pos != end; pos++ )
		{
			const SCTF_HOLDER&	sRankInfo = pos->second;
			GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF:Winner Check Rank:%d School:%d TowersOwned:%d Damage:%I64d", 
				sRankInfo.wRanking, sRankInfo.wSCHOOL, sRankInfo.wOWNED, sRankInfo.llDAMAGE  );
		}	
	}

	
	WORD wWINNER = sCTF.m_wSchoolWinner;

	if ( wWINNER != MAX_SCHOOL )
	{
		//SetLastWinner ( wWINNER );
		//send winner school to agent
		GLMSG::SNETPC_SERVER_CAPTURETHEFIELD_WINNER_AG NetMsgAgentWinner;
		NetMsgAgentWinner.dwID = sCTF.m_dwID;
		NetMsgAgentWinner.wSCHOOL = sCTF.m_wSchoolWinner;
		GLGaeaServer::GetInstance().SENDTOAGENT ( &NetMsgAgentWinner );

		GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF:Winner ID:%d %s", dwID, GLCONST_CHAR::strSCHOOLNAME[sCTF.m_wSchoolWinner].c_str() );

		switch ( wWINNER )
		{
		case 0:
			{
				CTF_RANK_PLAYER_MAP_ITER	pos = sCTF.m_mapScorePlayerSG.begin();
				CTF_RANK_PLAYER_MAP_ITER	end = sCTF.m_mapScorePlayerSG.end();
				for ( ; pos != end; pos++ )
				{
					const SCTF_RANK_PLAYER&	sRankInfo = pos->second;		
					if ( sRankInfo.nIndex >= 0 && sRankInfo.nIndex < CTF_RANKING_NUM ) 
						sCTF.AddWinner( sRankInfo );
				}	
			}break;
		case 1:
			{
				CTF_RANK_PLAYER_MAP_ITER	pos = sCTF.m_mapScorePlayerMP.begin();
				CTF_RANK_PLAYER_MAP_ITER	end = sCTF.m_mapScorePlayerMP.end();
				for ( ; pos != end; pos++ )
				{
					const SCTF_RANK_PLAYER&	sRankInfo = pos->second;		
					if ( sRankInfo.nIndex >= 0 && sRankInfo.nIndex < CTF_RANKING_NUM ) 
						sCTF.AddWinner( sRankInfo );
				}	
			}break;
		case 2:
			{
				CTF_RANK_PLAYER_MAP_ITER	pos = sCTF.m_mapScorePlayerPHX.begin();
				CTF_RANK_PLAYER_MAP_ITER	end = sCTF.m_mapScorePlayerPHX.end();
				for ( ; pos != end; pos++ )
				{
					const SCTF_RANK_PLAYER&	sRankInfo = pos->second;		
					if ( sRankInfo.nIndex >= 0 && sRankInfo.nIndex < CTF_RANKING_NUM ) 
						sCTF.AddWinner( sRankInfo );
				}	
			}break;
		}
	}
}

void GLCaptureTheFieldFieldMan::SendRewards( DWORD dwID )
{
	GLCaptureTheField *pCTF = FindCTF ( dwID, FALSE, FALSE );
	if ( !pCTF )						return;
	if ( !pCTF->IsBattleEndAward() )	return;
	if ( !pCTF->m_bAwardStart )		return;

	GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( pCTF->m_dwCaptureTheFieldMap );
	if ( !pLandMan ) return;

	GLCHARNODE* pCharNode = pLandMan->m_GlobPCList.m_pHead;
	for ( ; pCharNode; pCharNode = pCharNode->pNext )
	{
		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar( pCharNode->Data->m_dwGaeaID );
		if ( !pChar ) continue;

		CTF_AWARD_CHAR_ITER iterRewarded = pCTF->m_vecAwardChar.find( pChar->m_dwCharID );
		if ( iterRewarded != pCTF->m_vecAwardChar.end() )	continue;

		CTF_RANK_PLAYER_MAP_ITER iterWinner = pCTF->m_mapScoreWinner.find( pChar->m_dwCharID );
		if ( iterWinner != pCTF->m_mapScoreWinner.end() ) 
		{
			SCTF_RANK_PLAYER& sRankInfo = iterWinner->second;

			int nAwardIndex;
			if ( sRankInfo.wRanking < CTF_REWARD_NUM ) nAwardIndex = sRankInfo.wRanking - 1;
			else if ( sRankInfo.wRanking <= pCTF->m_sAwardItem.dwAwardLimit && sRankInfo.wKillNum >= pCTF->m_sAwardItem.dwKillMin ) nAwardIndex = ( CTF_REWARD_NUM -1 );
			else continue;

			SNATIVEID sNativeID = pCTF->m_sAwardItem.nAwardItem[nAwardIndex];

			SITEM* pItem = GLItemMan::GetInstance().GetItem( sNativeID );
			if ( !pItem ) continue;

			SITEMCUSTOM sITEM_NEW;
			sITEM_NEW.sNativeID = sNativeID;
			sITEM_NEW.tBORNTIME = CTime::GetCurrentTime().GetTime();
			sITEM_NEW.cGenType = EMGEN_SYSTEM;
			sITEM_NEW.cChnID = (BYTE)GLGaeaServer::GetInstance().GetServerChannel();
			sITEM_NEW.cFieldID = (BYTE)GLGaeaServer::GetInstance().GetFieldSvrID();
			sITEM_NEW.lnGenNum = GLITEMLMT::GetInstance().RegItemGen ( sITEM_NEW.sNativeID, (EMITEMGEN)sITEM_NEW.cGenType );

			CItemDrop cDropItem;
			cDropItem.sItemCustom = sITEM_NEW;
			if ( pChar->IsInsertToInvenEx ( &cDropItem ) )
			{
				pChar->InsertToInvenEx ( &cDropItem );

				GLITEMLMT::GetInstance().ReqItemRoute ( sITEM_NEW, ID_CLUB, pChar->m_dwGuild, ID_CHAR, pChar->m_dwCharID, 
					EMITEM_ROUTE_SYSTEM, sITEM_NEW.wTurnNum );
			}else{
				pLandMan->DropItem ( pChar->m_vPos, &(cDropItem.sItemCustom), EMGROUP_ONE, pChar->m_dwGaeaID );
			}

			pCTF->m_vecAwardChar.insert( pChar->m_dwCharID );
		}
	}
}