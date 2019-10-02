#include "StdAfx.h"

#include <algorithm>

#include "GLDefine.h"
#include "gltexfile.h"
#include "IniLoader.h"

#include "GLTowerWars.h"

#include "GLLandMan.h"
#include "GLGaeaServer.h"
#include "GLAgentServer.h"

GLTowerWarsFieldMan& GLTowerWarsFieldMan::GetInstance()
{
	static GLTowerWarsFieldMan cInstance;
	return cInstance;
}

bool GLTowerWarsFieldMan::SetMapState ()
{
	for ( SW_VEC::size_type i=0; i<m_vecSchoolWAR.size(); ++i )
	{
		GLTowerWars &sSW = m_vecSchoolWAR[i];

		SNATIVEID nidMAP ( sSW.m_dwClubMap );
		SMAPNODE *pMAPNODE = GLGaeaServer::GetInstance().FindMapNode ( nidMAP );
		if ( pMAPNODE )
		{
			pMAPNODE->bTWZone = true;
		}

		GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( nidMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwTowerWarsMapID = sSW.m_dwID;
			pLandMan->m_bTowerWarsMap = true;	
		}
	}

	return true;
}
bool GLTowerWarsFieldMan::ReadyBattle( DWORD dwID )
{
	GLTowerWars *pSW = Find ( dwID );
	if ( !pSW )	return false;

	pSW->SetBattle( GLTowerWars::BATTLE_READY );
	pSW->SetBattleEnd( false );

	return true;
}

bool GLTowerWarsFieldMan::BeginBattle ( DWORD dwID )
{
	GLTowerWars *pSW = Find ( dwID );
	if ( !pSW )	return false;

	pSW->SetBattle( GLTowerWars::BATTLE_START );
	pSW->SetForceExit( GLTowerWars::FORCE_EXIT_NO );
	pSW->SetBattleEnd( false );

	GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( pSW->m_dwClubMap );
	if ( pLandMan  )
	{
		pLandMan->ResetCrowOwner();
	}

	return true;
}

bool GLTowerWarsFieldMan::ChangeSWSchoolID ( DWORD dwID, DWORD dwSwID )
{
	GLTowerWars *pSwid = Find ( dwID );
	if ( !pSwid )	return false;

	pSwid->m_dwWinClub = dwSwID;

	return true;
}
bool GLTowerWarsFieldMan::EndBattle ( DWORD dwID, WORD wSchool, bool bEnd )
{
	GLTowerWars *pSwid = Find ( dwID );
	if ( !pSwid )	return false;

	pSwid->EndBattle( wSchool, bEnd );

	return true;
}

bool GLTowerWarsFieldMan::EndBattle ( DWORD dwID, bool bForceExit )
{
	GLTowerWars *pSW = Find ( dwID );
	if ( !pSW )	return false;

	pSW->SetBattle( GLTowerWars::BATTLE_END_AWARD );

	if( !bForceExit )
	{
		pSW->SetForceExit( GLTowerWars::FORCE_EXIT_NO );

		pSW->m_fCHECK_TIME = 10.0f;

		SWAwardItem( dwID );

		pSW->SetBattleEnd( false );

		GLMSG::SNET_TOWERWARS_DOBATTLEEND_AGT NetMsg;
		NetMsg.dwID = dwID;
		NetMsg.dwSCHOOL = pSW->m_dwWinClub;
		NetMsg.bEnd = true;
		GLGaeaServer::GetInstance().SENDTOAGENT ( &NetMsg );
	}else{
		pSW->m_vecCtfAwardChar.clear();
		pSW->m_mapCtfScore.clear();
		pSW->m_mapTowerStatus.clear();

		GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( pSW->m_dwClubMap );
		if ( pLandMan && bForceExit )
		{
			pLandMan->DoGateOutPCAll ( pSW->m_dwCLubMapGate );
			pLandMan->ResetCrowOwner();
		}
	}
	

	return true;
}

const std::string GLTowerWarsFieldMan::GetName ( DWORD dwID )
{
	GLTowerWars *pSW = Find ( dwID );
	if ( !pSW )				return "";

	return pSW->m_strName;
}

void GLTowerWarsFieldMan::UpdateTower( DWORD dwID )
{
	GLTowerWars *pSW = Find ( dwID );
	if ( !pSW )	return;
	
	GLTowerWars &sSchoolWAR = *pSW;

	//check capture here
	int nSCORE[SW_SCHOOL_MAX] = { 0, 0, 0 };
	DWORD dwWinner = 3;

	SCHOOLWAR_TOWER_STATUS_MAP_ITER	pos = sSchoolWAR.m_mapTowerStatus.begin();
	SCHOOLWAR_TOWER_STATUS_MAP_ITER	end = sSchoolWAR.m_mapTowerStatus.end();
	for ( ; pos != end; pos++ )
	{
		const SSCHOOLWAR_TOWER_STATUS&	sTOWER = pos->second;
		if ( sTOWER.emHOLDER >= SW_SCHOOL_MAX )	continue;
		nSCORE[sTOWER.emHOLDER] ++;
	}

	for( int i=0; i < SW_SCHOOL_MAX; ++ i )
	{
	if ( nSCORE[i] >= 2 )
		{
			dwWinner = i;
		}
	}

	GLMSG::SNET_TOWERWARS_CERTIFIED_AGT NetMsg;
	NetMsg.dwID = dwID;
	NetMsg.dwSCHOOL = dwWinner;
	GLGaeaServer::GetInstance().SENDTOAGENT ( &NetMsg );
}

//dmk14 | 1-11-17
void GLTowerWarsFieldMan::UpdateCTFRanking( DWORD dwID, DWORD dwCharID )
{
	GLTowerWars *pSWP = Find ( dwID );
	if ( !pSWP )	return;
	
	GLTowerWars &sSchoolWAR = *pSWP;
	
	TWP_RANK_INFO_VEC	m_vecSwPRankNew;
	m_vecSwPRankNew.reserve( sSchoolWAR.m_mapCtfScore.size() );

	TWP_RANK_INFO_MAP_ITER	pos = sSchoolWAR.m_mapCtfScore.begin();
	TWP_RANK_INFO_MAP_ITER	end = sSchoolWAR.m_mapCtfScore.end();

	for ( ; pos != end; pos++ )
	{
		const STWP_RANK_INFO&	sRankInfo = pos->second;					
		m_vecSwPRankNew.push_back( sRankInfo );
	}
	
	std::sort( m_vecSwPRankNew.begin(), m_vecSwPRankNew.end() );	

	int nSize = m_vecSwPRankNew.size();

	for ( int i = 0; i < nSize; ++i )
	{
		m_vecSwPRankNew[i].wCharRanking = i+1;
		m_vecSwPRankNew[i].nIndex = i;
	}

	int nRanking;

	for ( int i = nSize-1; i > 0; --i )
	{
		if ( m_vecSwPRankNew[i] == m_vecSwPRankNew[i-1] )
		{
			m_vecSwPRankNew[i-1].wCharRanking = m_vecSwPRankNew[i].wCharRanking;			
		}
	}	
	
	
	GLMSG::SNET_TOWERWARS_CTFRANKING_UPDATE	NetMsg;
	NetMsg.emFB = EMCTF_RANKING_UPDATE_FB_CLEAR;
	GLGaeaServer::GetInstance().SENDTOPLAYERCLIENT_ONMAP( sSchoolWAR.m_dwClubMap, dwCharID, &NetMsg );

	NetMsg.emFB = EMCTF_RANKING_UPDATE_FB_ADD;
	for ( int i = 0; i < m_vecSwPRankNew.size(); ++i )
	{
		TWP_RANK_INFO_MAP_ITER iter = sSchoolWAR.m_mapCtfScore.find( m_vecSwPRankNew[i].dwCharID );
		if ( iter == sSchoolWAR.m_mapCtfScore.end() )	continue;

		STWP_RANK_INFO&	sRankInfo = iter->second;
		
		if ( m_vecSwPRankNew[i].nIndex != sRankInfo.nIndex || 
			 m_vecSwPRankNew[i].wCharRanking != sRankInfo.wCharRanking )
		{
			sRankInfo.wCharRanking = m_vecSwPRankNew[i].wCharRanking;
			sRankInfo.nIndex = m_vecSwPRankNew[i].nIndex;
			sRankInfo.dwCharID = m_vecSwPRankNew[i].dwCharID;
			sRankInfo.dwGaeaID = m_vecSwPRankNew[i].dwGaeaID;
			sRankInfo.dwClass = m_vecSwPRankNew[i].dwClass;
			sRankInfo.dwDamageNum = m_vecSwPRankNew[i].dwDamageNum;
			sRankInfo.dwHealNum = m_vecSwPRankNew[i].dwHealNum;
			sRankInfo.wDeathNum = m_vecSwPRankNew[i].wDeathNum;
			sRankInfo.wKillNum = m_vecSwPRankNew[i].wKillNum;
			sRankInfo.wResuNum = m_vecSwPRankNew[i].wResuNum;
			sRankInfo.wSchool = m_vecSwPRankNew[i].wSchool;
			StringCchCopy ( sRankInfo.szCharName, CHAR_NAME+1, m_vecSwPRankNew[i].szCharName );

			if ( m_vecSwPRankNew[i].nIndex <= RANKING_TWNUM ) 
			{
				STWP_RANK sSwPRank = sRankInfo;
				NetMsg.sSwPRank = sSwPRank;
				GLGaeaServer::GetInstance().SENDTOPLAYERCLIENT_ONMAP( sSchoolWAR.m_dwClubMap, dwCharID, &NetMsg );
			}
		}		
	}
	NetMsg.emFB = EMCTF_RANKING_UPDATE_FB_END;
	GLGaeaServer::GetInstance().SENDTOPLAYERCLIENT_ONMAP( sSchoolWAR.m_dwClubMap, dwCharID, &NetMsg );


	GLMSG::SNET_TOWERWARS_MYCTFRANK_UPDATE	NetMsgMy;

	pos = sSchoolWAR.m_mapCtfScore.begin();
	end = sSchoolWAR.m_mapCtfScore.end();

	for ( ; pos != end; pos++ )
	{
		const STWP_RANK_INFO&	sRankInfo = pos->second;
		NetMsgMy.sMySwPRank.wCharRanking = sRankInfo.wCharRanking;
		NetMsgMy.sMySwPRank.wKillNum = sRankInfo.wKillNum;
		NetMsgMy.sMySwPRank.wDeathNum = sRankInfo.wDeathNum;
		NetMsgMy.sMySwPRank.dwDamageNum = sRankInfo.dwDamageNum;
		NetMsgMy.sMySwPRank.dwHealNum = sRankInfo.dwHealNum;
		NetMsgMy.sMySwPRank.wResuNum = sRankInfo.wResuNum;
		NetMsgMy.sMySwPRank.dwClass = sRankInfo.dwClass;
		NetMsgMy.sMySwPRank.wSchool = sRankInfo.wSchool;
		StringCchCopy ( NetMsgMy.sMySwPRank.szCharName, CHAR_NAME+1, sRankInfo.szCharName );

		if( sRankInfo.dwCharID == dwCharID ) GLGaeaServer::GetInstance().SENDTOPLAYERCLIENT_ONMAP( sSchoolWAR.m_dwClubMap, sRankInfo.dwCharID, &NetMsgMy );
	}
}

void GLTowerWarsFieldMan::SWAwardItem( DWORD dwID )
{
	GLTowerWars *pSW = Find ( dwID );
	if ( !pSW )	return;

	if ( !pSW->IsBattleEndAward() ) return;	

	GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( pSW->m_dwClubMap );
	if ( !pLandMan ) return;
	{
		GLCHARNODE* pCharNode = pLandMan->m_GlobPCList.m_pHead;
		for ( ; pCharNode; pCharNode = pCharNode->pNext )
		{
			PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar( pCharNode->Data->m_dwGaeaID );
			if ( !pChar )
			{
				std::string strTIME = CDebugSet::GetCurTime ();
				CDebugSet::ToFile ( "SWLOG1.txt", "%s	userid= %s (%d), charid= %s (%d), Character not available or disconnected",
					strTIME.c_str(),pChar->m_szUID,pChar->GetUserID(),pChar->m_szName,pChar->GetCharID());
				strTIME.clear();

				continue;
			}
		
			TWP_RANK_INFO_MAP_ITER iter = pSW->m_mapCtfScore.find( pChar->m_dwCharID );
			if ( iter != pSW->m_mapCtfScore.end() ) 
			{
				STWP_RANK_INFO& sSwPRankInfo = iter->second;
				
				TWP_AWARD_CHAR_ITER iter = pSW->m_vecCtfAwardChar.find( pChar->m_dwCharID );
				if ( iter != pSW->m_vecCtfAwardChar.end() )	continue;
				
				int nAwardIndex;
				if ( sSwPRankInfo.wCharRanking < 10 ) nAwardIndex = sSwPRankInfo.wCharRanking - 1;
				else if ( sSwPRankInfo.wCharRanking <= pSW->m_sTwPAwardItem.dwAwardLimit ) nAwardIndex = 9;
				else continue;
				
				SNATIVEID sNativeID = pSW->m_sTwPAwardItem.nAwardItem[nAwardIndex];
					
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
					
					GLITEMLMT::GetInstance().ReqItemRoute ( sITEM_NEW, ID_CHAR, 0, ID_CHAR, pChar->m_dwCharID, 
						EMITEM_ROUTE_SYSTEM, sITEM_NEW.wTurnNum );
				}
				else
				{
					pLandMan->DropItem ( pChar->m_vPos, &(cDropItem.sItemCustom), EMGROUP_ONE, pChar->m_dwGaeaID );
				}

				pSW->m_vecCtfAwardChar.insert( pChar->m_dwCharID );
			}
		}
	}
}