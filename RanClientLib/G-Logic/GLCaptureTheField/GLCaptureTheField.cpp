#include "StdAfx.h"

#include <algorithm>
#include "GLDefine.h"
#include "gltexfile.h"
#include "IniLoader.h"
#include "GLCaptureTheField.h"
#include "GLLandMan.h"
#include "GLGaeaServer.h"
#include "GLAgentServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GLCaptureTheField::GLCaptureTheField ()
	: m_dwID( UINT_MAX )
	, m_emBattleState( BATTLE_NOSTART )
	, m_dwCaptureTheFieldMap( 0 )
	, m_fCHECK_TIMER( 0.0f )
	, m_fCHECK_TIMER_MAX( 300.0f )
	, m_wSchoolWinner( MAX_SCHOOL )

	, m_dwLastID( 0 )
	, m_dwBattleOrder( 0 )
	, m_dwBattleTime( 3600 )
	, m_bNotifyOneHour( false )
	, m_bNotifyHalfHour( false )
	, m_bNotify10MinHour( false )
	, m_fBattleTimer( 0.0f )

	, m_fRankingUpdate( 0.0f )
	, m_fRankingUpdateTime( 60.0f )

	, m_fTowerUpdate( 0.0f )
	, m_fTowerUpdateTime( 60.0f )

	, m_bAwardStart( false )
{
	for ( int i = 0; i < CTF_MAX_REVIVE_GATE; ++ i )
		m_dwReviveGate[i] = 1;

	m_MapSchedule.clear();
	m_VecSchedule.clear();
}

GLCaptureTheField& GLCaptureTheField::operator= ( const GLCaptureTheField& value )
{
	m_dwID					= value.m_dwID;
	m_strName				= value.m_strName;
	m_emBattleState			= value.m_emBattleState;
	m_dwCaptureTheFieldMap	= value.m_dwCaptureTheFieldMap;

	m_fCHECK_TIMER			= value.m_fCHECK_TIMER;
	m_fCHECK_TIMER_MAX		= value.m_fCHECK_TIMER_MAX;
	m_wSchoolWinner			= value.m_wSchoolWinner;

	m_dwLastID				= value.m_dwLastID;
	m_dwBattleTime			= value.m_dwBattleTime;
	m_bNotifyOneHour		= value.m_bNotifyOneHour;
	m_bNotifyHalfHour		= value.m_bNotifyHalfHour;
	m_bNotify10MinHour		= value.m_bNotify10MinHour;
	m_fBattleTimer			= value.m_fBattleTimer;
	
	m_fRankingUpdate		= value.m_fRankingUpdate;
	m_fRankingUpdateTime	= value.m_fRankingUpdateTime;
	m_fTowerUpdate			= value.m_fTowerUpdate;
	m_fTowerUpdateTime		= value.m_fTowerUpdateTime;
	m_sAwardItem			= value.m_sAwardItem;
	m_vecAwardChar			= value.m_vecAwardChar;
	m_bAwardStart			= value.m_bAwardStart;

	for ( int i=0; i < CTF_MAX_REVIVE_GATE; ++ i )
		m_dwReviveGate[i] = value.m_dwReviveGate[i];

	m_MapSchedule			= value.m_MapSchedule;
	m_VecSchedule			= value.m_VecSchedule;


	return *this;
}

bool GLCaptureTheField::Load ( std::string strFile )
{
	if( strFile.empty() )	return FALSE;

	std::string strPath;
	strPath = GLOGIC::GetServerPath ();
	strPath += strFile;

	CIniLoader cFILE;

	if( GLOGIC::bGLOGIC_ZIPFILE )
		cFILE.SetZipFile( GLOGIC::strGLOGIC_SERVER_ZIPFILE );

	if( !cFILE.open ( strPath, true ) )
	{
		CDebugSet::ToLogFile ( "ERROR : GLCaptureTheField::Load(), File Open %s", strFile.c_str() );
		return false;
	}
	
	cFILE.getflag( "CTF", "ID", 0, 1, m_dwID );
	cFILE.getflag( "CTF", "NAME", 0, 1, m_strName );

	SNATIVEID nidMAP;
	cFILE.getflag( "CTF", "CTF_MAP", 0, 2, nidMAP.wMainID );
	cFILE.getflag( "CTF", "CTF_MAP", 1, 2, nidMAP.wSubID );
	m_dwCaptureTheFieldMap = nidMAP.dwID;

	//for each school there is a revive gate
	for ( int i=0; i < CTF_MAX_REVIVE_GATE; ++ i )
	{
		cFILE.getflag( "CTF", "REVIVE_GATE", i, CTF_MAX_REVIVE_GATE, m_dwReviveGate[i] );
	}

	DWORD dwNUM = cFILE.GetKeySize( "CTF", "BATTLE_TIME" );
	m_VecSchedule.clear();
	m_VecSchedule.reserve( dwNUM );

	for( DWORD i=0; i<dwNUM; ++i )
	{
		SCTF_SCHEDULE sDATA;
		cFILE.getflag( i, "CTF", "BATTLE_TIME", 0, 2, sDATA.dwWeekDay );
		cFILE.getflag( i, "CTF", "BATTLE_TIME", 1, 2, sDATA.dwStartTime );

		m_VecSchedule.push_back( sDATA );
	}

	std::sort( m_VecSchedule.begin(), m_VecSchedule.end() );	

	for ( size_t i=0; i < m_VecSchedule.size(); ++i )
	{
		m_VecSchedule[i].dwID = i+1;
	}

	m_MapSchedule.clear();


	cFILE.getflag( "CTF", "BATTLE_THE_TIME", 0, 1, m_dwBattleTime );
	cFILE.getflag( "CTF", "AWARD_TIME_LIMIT", 0, 1, m_fCHECK_TIMER_MAX );
	cFILE.getflag( "CTF", "RANKING_UPDATE_INTERVAL", 0, 1, m_fRankingUpdateTime );
	cFILE.getflag( "CTF", "TOWER_UPDATE_INTERVAL", 0, 1, m_fTowerUpdateTime );

	cFILE.getflag( "CTF", "AWARD_ITEM_LIMIT", 0, 1, m_sAwardItem.dwAwardLimit );
	cFILE.getflag( "CTF", "AWARD_KILL_MIN", 0, 1, m_sAwardItem.dwKillMin );
	cFILE.getflag( "CTF", "AWARD_ITEM_001", 0, 2, m_sAwardItem.nAwardItem[0].wMainID );
	cFILE.getflag( "CTF", "AWARD_ITEM_001", 1, 2, m_sAwardItem.nAwardItem[0].wSubID );
	cFILE.getflag( "CTF", "AWARD_ITEM_002", 0, 2, m_sAwardItem.nAwardItem[1].wMainID );
	cFILE.getflag( "CTF", "AWARD_ITEM_002", 1, 2, m_sAwardItem.nAwardItem[1].wSubID );
	cFILE.getflag( "CTF", "AWARD_ITEM_003", 0, 2, m_sAwardItem.nAwardItem[2].wMainID );
	cFILE.getflag( "CTF", "AWARD_ITEM_003", 1, 2, m_sAwardItem.nAwardItem[2].wSubID );
	cFILE.getflag( "CTF", "AWARD_ITEM_004", 0, 2, m_sAwardItem.nAwardItem[3].wMainID );
	cFILE.getflag( "CTF", "AWARD_ITEM_004", 1, 2, m_sAwardItem.nAwardItem[3].wSubID );
	cFILE.getflag( "CTF", "AWARD_ITEM_005", 0, 2, m_sAwardItem.nAwardItem[4].wMainID );
	cFILE.getflag( "CTF", "AWARD_ITEM_005", 1, 2, m_sAwardItem.nAwardItem[4].wSubID );
	cFILE.getflag( "CTF", "AWARD_ITEM_006", 0, 2, m_sAwardItem.nAwardItem[5].wMainID );
	cFILE.getflag( "CTF", "AWARD_ITEM_006", 1, 2, m_sAwardItem.nAwardItem[5].wSubID );
	cFILE.getflag( "CTF", "AWARD_ITEM_007", 0, 2, m_sAwardItem.nAwardItem[6].wMainID );
	cFILE.getflag( "CTF", "AWARD_ITEM_007", 1, 2, m_sAwardItem.nAwardItem[6].wSubID );
	cFILE.getflag( "CTF", "AWARD_ITEM_008", 0, 2, m_sAwardItem.nAwardItem[7].wMainID );
	cFILE.getflag( "CTF", "AWARD_ITEM_008", 1, 2, m_sAwardItem.nAwardItem[7].wSubID );
	cFILE.getflag( "CTF", "AWARD_ITEM_009", 0, 2, m_sAwardItem.nAwardItem[8].wMainID );
	cFILE.getflag( "CTF", "AWARD_ITEM_009", 1, 2, m_sAwardItem.nAwardItem[8].wSubID );
	cFILE.getflag( "CTF", "AWARD_ITEM_010", 0, 2, m_sAwardItem.nAwardItem[9].wMainID );
	cFILE.getflag( "CTF", "AWARD_ITEM_010", 1, 2, m_sAwardItem.nAwardItem[9].wSubID );
	cFILE.getflag( "CTF", "AWARD_ITEM_ETCH", 0, 2, m_sAwardItem.nAwardItem[10].wMainID );
	cFILE.getflag( "CTF", "AWARD_ITEM_ETCH", 1, 2, m_sAwardItem.nAwardItem[10].wSubID );

	return true;
}

bool GLCaptureTheField::IsEnterMap( WORD wSCHOOL )
{
	if ( IsBattle() ) return true;
	if ( IsBattleReady() ) return true;

	if ( m_wSchoolWinner != MAX_SCHOOL )
	{
		if ( m_wSchoolWinner == wSCHOOL )	
			return true;
	}

	return false;
}

DWORD GLCaptureTheField::GetReviveGate( WORD wSCHOOL )
{
	if ( wSCHOOL >= CTF_MAX_REVIVE_GATE )	return NULL; //return the fuck
	return m_dwReviveGate[wSCHOOL];
}

BOOL GLCaptureTheField::CheckAwardTime( float fElaps )
{
	m_fCHECK_TIMER += fElaps;

	if ( m_fCHECK_TIMER > m_fCHECK_TIMER_MAX )
	{
		SetBattle( EM_BATTLE_STATE::BATTLE_END );
		m_fCHECK_TIMER = 0.0f;
		return TRUE;
	}

	return FALSE;
}



//agent server
DWORD GLCaptureTheField::IsBattleWeekDay ( int nDayOfWeek, int nHour )
{
	if ( IsBattle() )	return UINT_MAX;
	if ( IsBattleEndAward() )	return UINT_MAX;

	SCTF_SCHEDULE_MAP_ITER pos = m_MapSchedule.begin();
	SCTF_SCHEDULE_MAP_ITER end = m_MapSchedule.end();

	for ( ; pos != end; pos++ )
	{
		const SCTF_SCHEDULE&	sched = pos->second;	

		if ( nDayOfWeek != sched.dwWeekDay )	continue;
		if ( m_dwLastID == sched.dwID )			continue;
		if ( nHour > sched.dwStartTime )		continue;

		if ( sched.dwStartTime == nHour )	return sched.dwID;

		int nDiff = sched.dwStartTime - nHour;
		if ( nDiff == 0 || nDiff == 1 )	return sched.dwID;
	}
	return UINT_MAX;
}

bool GLCaptureTheField::IsBattleHour ( DWORD dwORDER, int nHour )
{
	SCTF_SCHEDULE_MAP_ITER pos = m_MapSchedule.find( dwORDER );
	if ( pos !=m_MapSchedule.end() ) 
	{
		const SCTF_SCHEDULE&	sched = pos->second;	
		if ( sched.dwStartTime == nHour )	return TRUE;
	}

	return false;
}

void GLCaptureTheField::UpdateNotifyBattle ( DWORD dwORDER, int nHour, int nMinute )
{
	SCTF_SCHEDULE_MAP_ITER pos = m_MapSchedule.find( dwORDER );
	if ( pos == m_MapSchedule.end() ) return;

	const SCTF_SCHEDULE&	sched = pos->second;
	DWORD dwOTime = sched.dwStartTime;

	if ( dwOTime <= 0 )			return;

	dwOTime -= 1;
	if ( nHour == dwOTime )
	{
		if ( !m_bNotifyOneHour )
		{
			m_bNotifyOneHour = true;
			NotifyBattleBroadcast( 60-nMinute, FALSE );
		}

		if ( nMinute == 30 )
		{
			if ( !m_bNotifyHalfHour )
			{
				m_bNotifyHalfHour = true;
				NotifyBattleBroadcast( 30, FALSE );
			}
		}

		if ( nMinute == 50 )
		{
			if ( !m_bNotify10MinHour )
			{
				m_bNotify10MinHour = true;
				m_emBattleState = BATTLE_READY;
				NotifyBattleBroadcast( 10, TRUE );
			}
		}
	}
}

void GLCaptureTheField::NotifyBattleBroadcast( int nTIME, BOOL bREADY )
{
	GLMSG::SNET_CAPTURETHEFIELD_START_BRD NetMsgBrd;
	NetMsgBrd.nTIME = nTIME;
	StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_CAPTURETHEFIELD_START_BRD::TEXT_LEN, m_strName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );

	GLAgentServer::GetInstance().CONSOLEMSG_WRITE( "CTF:Update Time To Start ID:%d Time:%d Minutes", m_dwID, nTIME );

	if ( bREADY )
	{
		GLMSG::SNET_CAPTURETHEFIELD_READY_FLD NetMsgFld;
		NetMsgFld.dwID = m_dwID;
		GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );

		GLMSG::SNET_CAPTURETHEFIELD_READY_BRD NetMsgReadyBrd;
		StringCchCopy ( NetMsgReadyBrd.szName, GLMSG::SNET_CAPTURETHEFIELD_READY_BRD::TEXT_LEN, m_strName.c_str() );
		GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgReadyBrd );

		GLAgentServer::GetInstance().CONSOLEMSG_WRITE( "CTF: Ready Battle:ID %d", m_dwID );
	}
}

void GLCaptureTheField::DoBattleStart ( DWORD dwORDER )
{
	SCTF_SCHEDULE_MAP_ITER pos = m_MapSchedule.find( dwORDER );
	if ( pos == m_MapSchedule.end() ) return;

	m_MapSchedule.erase( pos );

	m_dwLastID = dwORDER;

	m_emBattleState = BATTLE_START;
	m_dwBattleOrder = dwORDER;

	GLMSG::SNET_CAPTURETHEFIELD_START_FLD NetMsgFld;
	NetMsgFld.dwID = m_dwID;
	GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );

	GLMSG::SNET_CAPTURETHEFIELD_START_BRD NetMsgBrd;
	NetMsgBrd.nTIME = 0;
	StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_CAPTURETHEFIELD_START_BRD::TEXT_LEN, m_strName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
	GLAgentServer::GetInstance().CONSOLEMSG_WRITE( "CTF: DoBattleStart :ID %d ORDER:%d Remain:%d", m_dwID, dwORDER, m_MapSchedule.size() );
}

void GLCaptureTheField::DoBattleEndAward()
{
	m_emBattleState = BATTLE_END_AWARD;
	m_dwBattleOrder = UINT_MAX;

	m_bNotifyOneHour = false;
	m_bNotifyHalfHour = false;
	m_bNotify10MinHour = false;
	m_fBattleTimer = 0.0f;

	GLMSG::SNET_CAPTURETHEFIELD_END_FLD NetMsgFld;
	NetMsgFld.dwID = m_dwID;
	GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );

	GLMSG::SNET_CAPTURETHEFIELD_END_BRD NetMsgBrd;
	NetMsgBrd.bREWARD = TRUE;
	StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_CAPTURETHEFIELD_END_BRD::TEXT_LEN, m_strName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
	GLAgentServer::GetInstance().CONSOLEMSG_WRITE( "CTF:DoBattleEndAward:ID %d", m_dwID );
}

void GLCaptureTheField::DoBattleEnd()
{
	m_emBattleState = BATTLE_END;
	m_wSchoolWinner = MAX_SCHOOL;
	m_fCHECK_TIMER = 0.0f;

	GLMSG::SNET_CAPTURETHEFIELD_END_BRD NetMsgBrd;
	NetMsgBrd.bREWARD = FALSE;
	StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_CAPTURETHEFIELD_END_BRD::TEXT_LEN, m_strName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
	GLAgentServer::GetInstance().CONSOLEMSG_WRITE( "CTF:DoBattleEnd:ID %d", m_dwID );
}

BOOL GLCaptureTheField::ReloadSchedule()
{
	if ( IsBattle() )					return FALSE;
	if ( IsBattleEndAward()	)			return FALSE;
	if ( m_VecSchedule.size() == 0 )	return FALSE;

	for ( int i=0; i < m_VecSchedule.size(); ++i )
	{
		const SCTF_SCHEDULE sched = m_VecSchedule[i];
		m_MapSchedule[sched.dwID] = sched;
	}

	GLAgentServer::GetInstance().CONSOLEMSG_WRITE( "CTF:ReSchedule:ID %d Number %d~%d", 
		m_dwID, 
		m_VecSchedule.size(), 
		m_MapSchedule.size() 
		);

	return TRUE;
}

//field server
void GLCaptureTheField::FieldBattleEnd()
{
	m_emBattleState = BATTLE_END;
	m_wSchoolWinner = MAX_SCHOOL;
	m_fCHECK_TIMER = 0.0f;

	m_mapScorePlayerAll.clear();
	m_mapScorePlayerSG.clear();
	m_mapScorePlayerMP.clear();
	m_mapScorePlayerPHX.clear();

	m_mapTowerScore.clear();
	m_mapScoreWinner.clear();
	m_vecAwardChar.clear();

	m_fRankingUpdate = 0.0f;
	m_bAwardStart = false;

	GLLandMan* pLAND = GLGaeaServer::GetInstance().GetByMapID( SNATIVEID(m_dwCaptureTheFieldMap) );
	if ( pLAND )
		pLAND->ResetCrowOwner();
}

SCTF_RANK_PLAYER* GLCaptureTheField::GetRankingPlayerAll( DWORD dwCharID )
{
	CTF_RANK_PLAYER_MAP_ITER pos = m_mapScorePlayerAll.find( dwCharID );
	if( pos == m_mapScorePlayerAll.end() )	return NULL;

	return &(*pos).second;;
}

SCTF_RANK_PLAYER* GLCaptureTheField::GetRankingPlayerSG( DWORD dwCharID )
{
	CTF_RANK_PLAYER_MAP_ITER pos = m_mapScorePlayerSG.find( dwCharID );
	if( pos == m_mapScorePlayerSG.end() )	return NULL;

	return &(*pos).second;;
}

SCTF_RANK_PLAYER* GLCaptureTheField::GetRankingPlayerMP( DWORD dwCharID )
{
	CTF_RANK_PLAYER_MAP_ITER pos = m_mapScorePlayerMP.find( dwCharID );
	if( pos == m_mapScorePlayerMP.end() )	return NULL;

	return &(*pos).second;;
}

SCTF_RANK_PLAYER* GLCaptureTheField::GetRankingPlayerPHX( DWORD dwCharID )
{
	CTF_RANK_PLAYER_MAP_ITER pos = m_mapScorePlayerPHX.find( dwCharID );
	if( pos == m_mapScorePlayerPHX.end() )	return NULL;

	return &(*pos).second;;
}

SCTF_SCORE_TOWER* GLCaptureTheField::GetTowerScore( DWORD dwCROWID )
{
	CTF_SCORE_TOWER_MAP_ITER pos = m_mapTowerScore.find( dwCROWID );
	if( pos == m_mapTowerScore.end() )	return NULL;

	return &(*pos).second;;
}

void GLCaptureTheField::AddScore( DWORD dwKillChar, DWORD dwDeathChar )
{
	PGLCHAR pCHARKILL = GLGaeaServer::GetInstance().GetCharID( dwKillChar );
	if ( pCHARKILL )
	{
		SCTF_RANK_PLAYER sRANK;
		sRANK.dwCharID = dwKillChar;
		StringCchCopy ( sRANK.szCharName, CTF_RANKING_NAME+1, pCHARKILL->m_szName );
		sRANK.szCharName[CTF_RANKING_NAME] = '\0';
		sRANK.cSCHOOL = (BYTE)pCHARKILL->m_wSchool;
		sRANK.cCLASS = (BYTE)CharClassToIndex( pCHARKILL->m_emClass );
		sRANK.wKillNum++;

		SCTF_RANK_PLAYER* pKillPlayerAll = GetRankingPlayerAll( dwKillChar );
		if ( pKillPlayerAll )
		{
			pKillPlayerAll->wKillNum++;
		}else{
			m_mapScorePlayerAll[sRANK.dwCharID] = sRANK;
		}

		if ( pCHARKILL->m_wSchool == 0 )
		{
			SCTF_RANK_PLAYER* pKillPlayerSG = GetRankingPlayerSG( dwKillChar );
			if ( pKillPlayerSG )
			{
				pKillPlayerSG->wKillNum++;
			}else{
				m_mapScorePlayerSG[sRANK.dwCharID] = sRANK;
			}
		}
		
		if ( pCHARKILL->m_wSchool == 1 )
		{
			SCTF_RANK_PLAYER* pKillPlayerMP = GetRankingPlayerMP( dwKillChar );
			if ( pKillPlayerMP )
			{
				pKillPlayerMP->wKillNum++;
			}else{
				m_mapScorePlayerMP[sRANK.dwCharID] = sRANK;
			}
		}

		if ( pCHARKILL->m_wSchool == 2 )
		{
			SCTF_RANK_PLAYER* pKillPlayerPHX = GetRankingPlayerPHX( dwKillChar );
			if ( pKillPlayerPHX )
			{
				pKillPlayerPHX->wKillNum++;
			}else{
				m_mapScorePlayerPHX[sRANK.dwCharID] = sRANK;
			}
		}
	}

	PGLCHAR pCHARDEATH = GLGaeaServer::GetInstance().GetCharID( dwDeathChar );
	if ( pCHARDEATH )
	{
		SCTF_RANK_PLAYER sRANK;
		sRANK.dwCharID = dwDeathChar;
		StringCchCopy ( sRANK.szCharName, CTF_RANKING_NAME+1, pCHARDEATH->m_szName );
		sRANK.szCharName[CTF_RANKING_NAME] = '\0';
		sRANK.cSCHOOL = (BYTE)pCHARDEATH->m_wSchool;
		sRANK.cCLASS = (BYTE)CharClassToIndex( pCHARDEATH->m_emClass );
		sRANK.wDeathNum++;
		
		SCTF_RANK_PLAYER* pDeathPlayerAll = GetRankingPlayerAll( dwDeathChar );
		if ( pDeathPlayerAll )
		{
			pDeathPlayerAll->wDeathNum++;
		}else{
			m_mapScorePlayerAll[sRANK.dwCharID] = sRANK;
		}

		if ( pCHARDEATH->m_wSchool == 0 )
		{
			SCTF_RANK_PLAYER* pDeathPlayerSG = GetRankingPlayerSG( dwDeathChar );
			if ( pDeathPlayerSG )
			{
				pDeathPlayerSG->wDeathNum++;
			}else{
				m_mapScorePlayerSG[sRANK.dwCharID] = sRANK;
			}
		}

		if ( pCHARDEATH->m_wSchool == 1 )
		{
			SCTF_RANK_PLAYER* pDeathPlayerMP = GetRankingPlayerMP( dwDeathChar );
			if ( pDeathPlayerMP )
			{
				pDeathPlayerMP->wDeathNum++;
			}else{
				m_mapScorePlayerMP[sRANK.dwCharID] = sRANK;
			}
		}

		if ( pCHARDEATH->m_wSchool == 2 )
		{
			SCTF_RANK_PLAYER* pDeathPlayerPHX = GetRankingPlayerPHX( dwDeathChar );
			if ( pDeathPlayerPHX )
			{
				pDeathPlayerPHX->wDeathNum++;
			}else{
				m_mapScorePlayerPHX[sRANK.dwCharID] = sRANK;
			}
		}
	}
}

void GLCaptureTheField::AddDamageTower( SNATIVEID sID, DWORD dwDAMAGE, WORD wSCHOOL )
{
	if ( wSCHOOL >= CTF_TOWER_DAMAGE_VAR )	return;
	if ( dwDAMAGE <= 0 )	return;

	SCROWDATA* pCROWDATA = GLCrowDataMan::GetInstance().GetCrowData( sID );
	if( pCROWDATA )
	{
		SCTF_SCORE_TOWER* pSCORE = GetTowerScore( sID.dwID );
		if ( pSCORE )
		{
			pSCORE->sDATA[wSCHOOL].wSCHOOL = wSCHOOL;
			pSCORE->sDATA[wSCHOOL].llDAMAGE += dwDAMAGE;
		}
		else
		{
			SCTF_SCORE_TOWER sSCORE;
			sSCORE.sCROWID = sID;
			sSCORE.sDATA[wSCHOOL].wSCHOOL = wSCHOOL;
			sSCORE.sDATA[wSCHOOL].llDAMAGE += dwDAMAGE;
			m_mapTowerScore[sSCORE.sCROWID.dwID] = sSCORE;
		}
	}
}

void GLCaptureTheField::AddDamageChar( DWORD dwCHARID, DWORD dwDAMAGE )
{
	if ( dwDAMAGE <= 0 )	return;

	PGLCHAR pCHAR = GLGaeaServer::GetInstance().GetCharID( dwCHARID );
	if ( pCHAR )
	{
		SCTF_RANK_PLAYER sRANK;
		sRANK.dwCharID = dwCHARID;
		StringCchCopy ( sRANK.szCharName, CTF_RANKING_NAME+1, pCHAR->m_szName );
		sRANK.szCharName[CTF_RANKING_NAME] = '\0';
		sRANK.cSCHOOL = (BYTE)pCHAR->m_wSchool;
		sRANK.cCLASS = (BYTE)CharClassToIndex( pCHAR->m_emClass );
		sRANK.llDAMAGE += dwDAMAGE;

		SCTF_RANK_PLAYER* pRANK = GetRankingPlayerAll( dwCHARID );
		if ( pRANK )
		{
			pRANK->llDAMAGE += dwDAMAGE;
		}else{
			m_mapScorePlayerAll[sRANK.dwCharID] = sRANK;
		}


		if ( pCHAR->m_wSchool == 0 )
		{
			SCTF_RANK_PLAYER* pCharSG = GetRankingPlayerSG( dwCHARID );
			if ( pCharSG )
			{
				pCharSG->llDAMAGE += dwDAMAGE;
			}else{
				m_mapScorePlayerSG[sRANK.dwCharID] = sRANK;
			}
		}

		if ( pCHAR->m_wSchool == 1 )
		{
			SCTF_RANK_PLAYER* pCharMP = GetRankingPlayerMP( dwCHARID );
			if ( pCharMP )
			{
				pCharMP->llDAMAGE += dwDAMAGE;
			}else{
				m_mapScorePlayerMP[sRANK.dwCharID] = sRANK;
			}
		}

		if ( pCHAR->m_wSchool == 2 )
		{
			SCTF_RANK_PLAYER* pCharPHX = GetRankingPlayerPHX( dwCHARID );
			if ( pCharPHX )
			{
				pCharPHX->llDAMAGE += dwDAMAGE;
			}else{
				m_mapScorePlayerPHX[sRANK.dwCharID] = sRANK;
			}
		}
	}
}

void GLCaptureTheField::AddWinner( SCTF_RANK_PLAYER sRANK )
{
	CTF_RANK_PLAYER_MAP_ITER pos = m_mapScoreWinner.find( sRANK.dwCharID );
	if( pos == m_mapScoreWinner.end() )
	{
		m_mapScoreWinner[sRANK.dwCharID] = sRANK;
	}
}