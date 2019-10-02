#include "StdAfx.h"

#include <algorithm>

#include "GLDefine.h"
#include "gltexfile.h"
#include "IniLoader.h"

#include "GLRoyalRumble.h"

//#include "dbactionlogic.h"
#include "GLLandMan.h"
#include "GLGaeaServer.h"
#include "GLAgentServer.h"
//#include "GLChar.h"
//#include "GLCrow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GLRoyalRumble::GLRoyalRumble () :
	m_dwID(UINT_MAX),
	
	m_dwClubMap(0),
	m_dwCLubMapGate(0),
	m_dwClubHallMap(0),
	m_dwClubHallGate(0),

	m_dwWinClub(CLUB_NULL),

	m_dwBattleTime(3600),

	m_bNotifyOneHour(false),
	m_bNotifyHalfHour(false),
	m_bNotify10MinHour(false),
	
	m_emBattleState(BATTLE_NOSTART),
	m_dwBattleOrder(0),
	m_dwLastBattleHour(0),
	m_fBattleTimer(0.0f),

	m_fCHECK_TIMER(0.0f),
	m_fCHECK_TIME(0.0f),
	m_fRankingUpdate(0.0f)
{
}

GLRoyalRumble& GLRoyalRumble::operator= ( const GLRoyalRumble& value )
{
	m_dwID = value.m_dwID;
	m_strName = value.m_strName;

	m_dwClubMap = value.m_dwClubMap;
	m_dwCLubMapGate = value.m_dwCLubMapGate;
	m_dwClubHallMap = value.m_dwClubHallMap;
	m_dwClubHallGate = value.m_dwClubHallGate;

	m_dwBattleTime = value.m_dwBattleTime;

	for ( int i=0; i<MAX_TIME; ++i )
		m_sRrTIME[i] = value.m_sRrTIME[i];

	m_sRrPAwardItem = value.m_sRrPAwardItem;

	m_dwWinClub = value.m_dwWinClub;

	m_bNotifyOneHour = value.m_bNotifyOneHour;
	m_bNotifyHalfHour = value.m_bNotifyHalfHour;
	m_bNotify10MinHour = value.m_bNotify10MinHour;

	m_emBattleState = value.m_emBattleState;
	m_dwLastBattleHour = value.m_dwLastBattleHour;
	m_fBattleTimer = value.m_fBattleTimer;

	m_fCHECK_TIMER = value.m_fCHECK_TIMER;
	m_fCHECK_TIME = value.m_fCHECK_TIME;

	m_vecRrPAwardChar = value.m_vecRrPAwardChar;

	m_fRankingUpdate = value.m_fRankingUpdate;

	return *this;
}

bool GLRoyalRumble::Load ( std::string strFile )
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
		CDebugSet::ToLogFile ( "ERROR : GLRoyalRumble::Load(), File Open %s", strFile.c_str() );
		return false;
	}
	
	cFILE.getflag( "ROYAL_RUMBLE", "ID", 0, 1, m_dwID );
	cFILE.getflag( "ROYAL_RUMBLE", "NAME", 0, 1, m_strName );

	SNATIVEID nidMAP;
	cFILE.getflag( "ROYAL_RUMBLE", "CLUB_MAP", 0, 2, nidMAP.wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "CLUB_MAP", 1, 2, nidMAP.wSubID );
	m_dwClubMap = nidMAP.dwID;

	cFILE.getflag( "ROYAL_RUMBLE", "CLUB_GATE", 0, 1, m_dwCLubMapGate );

	cFILE.getflag( "ROYAL_RUMBLE", "CLUB_HALL_MAP", 0, 2, nidMAP.wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "CLUB_HALL_MAP", 1, 2, nidMAP.wSubID );
	m_dwClubHallMap = nidMAP.dwID;

	cFILE.getflag( "ROYAL_RUMBLE", "CLUB_HALL_GATE", 0, 1, m_dwClubHallGate );

	DWORD dwNUM = cFILE.GetKeySize( "ROYAL_RUMBLE", "BATTLE_TIME" );
	if( dwNUM > MAX_TIME )
	{
		CDebugSet::ToLogFile( "ERROR : GLRoyalRumble::Load(), %s, It was wrong size of BATTLE_TIME", strFile.c_str() );
		return false;
	}

	for( DWORD i=0; i<dwNUM; ++i )
	{
		cFILE.getflag( i, "ROYAL_RUMBLE", "BATTLE_TIME", 0, 2, m_sRrTIME[i].dwWeekDay );
		cFILE.getflag( i, "ROYAL_RUMBLE", "BATTLE_TIME", 1, 2, m_sRrTIME[i].dwStartTime );
	}

	cFILE.getflag( "ROYAL_RUMBLE", "BATTLE_THE_TIME", 0, 1, m_dwBattleTime );

	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_1", 0, 2, m_sRrPAwardItem.nAwardItem[0].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_1", 1, 2, m_sRrPAwardItem.nAwardItem[0].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_2", 0, 2, m_sRrPAwardItem.nAwardItem[1].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_2", 1, 2, m_sRrPAwardItem.nAwardItem[1].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_3", 0, 2, m_sRrPAwardItem.nAwardItem[2].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_3", 1, 2, m_sRrPAwardItem.nAwardItem[2].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_4", 0, 2, m_sRrPAwardItem.nAwardItem[3].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_4", 1, 2, m_sRrPAwardItem.nAwardItem[3].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_5", 0, 2, m_sRrPAwardItem.nAwardItem[4].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_5", 1, 2, m_sRrPAwardItem.nAwardItem[4].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_6", 0, 2, m_sRrPAwardItem.nAwardItem[5].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_6", 1, 2, m_sRrPAwardItem.nAwardItem[5].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_7", 0, 2, m_sRrPAwardItem.nAwardItem[6].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_7", 1, 2, m_sRrPAwardItem.nAwardItem[6].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_8", 0, 2, m_sRrPAwardItem.nAwardItem[7].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_8", 1, 2, m_sRrPAwardItem.nAwardItem[7].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_9", 0, 2, m_sRrPAwardItem.nAwardItem[8].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_9", 1, 2, m_sRrPAwardItem.nAwardItem[8].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_10", 0, 2, m_sRrPAwardItem.nAwardItem[9].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_10", 1, 2, m_sRrPAwardItem.nAwardItem[9].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_11", 0, 2, m_sRrPAwardItem.nAwardItem[10].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_11", 1, 2, m_sRrPAwardItem.nAwardItem[10].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_12", 0, 2, m_sRrPAwardItem.nAwardItem[11].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_12", 1, 2, m_sRrPAwardItem.nAwardItem[11].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_13", 0, 2, m_sRrPAwardItem.nAwardItem[12].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_13", 1, 2, m_sRrPAwardItem.nAwardItem[12].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_14", 0, 2, m_sRrPAwardItem.nAwardItem[13].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_14", 1, 2, m_sRrPAwardItem.nAwardItem[13].wSubID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_15", 0, 2, m_sRrPAwardItem.nAwardItem[14].wMainID );
	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_15", 1, 2, m_sRrPAwardItem.nAwardItem[14].wSubID );

	cFILE.getflag( "ROYAL_RUMBLE", "AWARD_ITEM_LIMIT", 0, 1, m_sRrPAwardItem.dwAwardLimit );

	return true;
}

DWORD GLRoyalRumble::IsBattleWeekDay ( int nDayOfWeek, int nHour )
{
	if ( IsBattle() )	return UINT_MAX;

	for ( DWORD i=0; i<MAX_TIME; ++i )
	{
		if ( (nDayOfWeek==m_sRrTIME[i].dwWeekDay) && 
			 (nHour==m_sRrTIME[i].dwStartTime) &&
			 (m_dwLastBattleHour!=nHour) )
		{
			return i;
		}
	}
	return UINT_MAX;
}

bool GLRoyalRumble::IsBattleHour ( DWORD dwORDER, int nHour )
{
	if ( dwORDER>=MAX_TIME )
	{
		return false;
	}
	
	if (m_sRrTIME[dwORDER].dwStartTime == nHour)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

void GLRoyalRumble::UpdateBattleDay ( int nHour )
{
	m_dwLastBattleHour = nHour;
}

void GLRoyalRumble::UpdateNotifyBattle ( DWORD dwORDER, int nHour, int nMinute )
{
	if ( dwORDER>=MAX_TIME )	return;

	DWORD dwOTime = m_sRrTIME[dwORDER].dwStartTime;
	if ( dwOTime <= 0 )			return;
	
	dwOTime -= 1;
	if ( nHour == dwOTime )
	{
		if ( !m_bNotifyOneHour )
		{
			m_bNotifyOneHour = true;

			GLMSG::SNET_ROYAL_RUMBLE_START_BRD NetMsgBrd;
			NetMsgBrd.nTIME = 60-nMinute;
			StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_ROYAL_RUMBLE_START_BRD::TEXT_LEN, m_strName.c_str() );
			GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
		}

		if ( nMinute == 30 )
		{
			if ( !m_bNotifyHalfHour )
			{
				m_bNotifyHalfHour = true;

				GLMSG::SNET_ROYAL_RUMBLE_START_BRD NetMsgBrd;
				NetMsgBrd.nTIME = 30;
				StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_ROYAL_RUMBLE_START_BRD::TEXT_LEN, m_strName.c_str() );
				GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
			}
		}

		if ( nMinute == 50 )
		{
			if ( !m_bNotify10MinHour )
			{
				m_bNotify10MinHour = true;
				m_emBattleState = BATTLE_READY;

				GLMSG::SNET_ROYAL_RUMBLE_START_BRD NetMsgBrd;
				NetMsgBrd.nTIME = 10;
				StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_ROYAL_RUMBLE_START_BRD::TEXT_LEN, m_strName.c_str() );
				GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );

				GLMSG::SNET_ROYAL_RUMBLE_READY_FLD NetMsgFld;
				NetMsgFld.dwID = m_dwID;
				GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );
			}
		}
	}

}

void GLRoyalRumble::DoBattleStart ( DWORD dwORDER, int nHour )
{
	m_emBattleState = BATTLE_START;
	m_dwBattleOrder = dwORDER;
	m_fRankingUpdate = 0.0f;

	m_vecRrPAwardChar.clear();
	m_mapRrPScore.clear();

	UpdateBattleDay ( nHour );

	GLMSG::SNET_ROYAL_RUMBLE_START_FLD NetMsgFld;
	NetMsgFld.dwID = m_dwID;
	GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );

	GLMSG::SNET_ROYAL_RUMBLE_START_BRD NetMsgBrd;
	NetMsgBrd.nTIME = 0;
	StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_ROYAL_RUMBLE_START_BRD::TEXT_LEN, m_strName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );

}

void GLRoyalRumble::DoBattleEnd()
{
	m_emBattleState = BATTLE_END;
	m_dwBattleOrder = UINT_MAX;

	m_bNotifyOneHour = false;
	m_bNotifyHalfHour = false;
	m_bNotify10MinHour = false;
	m_fBattleTimer = 0.0f;
	m_fRankingUpdate = 0.0f;

	std::string strClubName;
	
	GLMSG::SNET_ROYAL_RUMBLE_END_FLD NetMsgFld;
	NetMsgFld.dwID = m_dwID;
	GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );

	GLMSG::SNET_ROYAL_RUMBLE_END_BRD NetMsgBrd;
	StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_ROYAL_RUMBLE_END_BRD::TEXT_LEN, m_strName.c_str() );
	StringCchCopy ( NetMsgBrd.szCharName, CHAR_SZNAME, strClubName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
}

void GLRoyalRumble::CheckAwardClub( float fElaps )
{
	m_fCHECK_TIMER += fElaps;
	if ( m_fCHECK_TIMER > m_fCHECK_TIME )
	{
		if ( m_fCHECK_TIME < 30.0f )
		{
			m_fCHECK_TIME += 10.0f;
			return;
		}

		m_fCHECK_TIME = 999.0f;	
	}

	if ( m_fCHECK_TIMER > 300.0f )
	{
		SetBattle( EM_BATTLE_STATE::BATTLE_END );
		m_fCHECK_TIMER = 0.0f;
		m_fCHECK_TIME = 0.0f;
		return;
	}
}

bool GLRoyalRumble::IsEnterMap(DWORD dwCharID)
{
	if ( dwCharID == GAEAID_NULL ) return false;
	if ( IsBattle() ) return true;
	if ( IsBattleReady() ) return true;

	return false;
}

SRRP_RANK_INFO* GLRoyalRumble::GetRRPRankInof( DWORD dwCharID )
{
	RRP_RANK_INFO_MAP_ITER pos = m_mapRrPScore.find( dwCharID );
	if( pos == m_mapRrPScore.end() )
	{
		return NULL;
	}
	
	return &(*pos).second;;
}

void GLRoyalRumble::AddRRPScore( DWORD dwKillChar, DWORD dwKillGaeaID, DWORD dwDeathChar, DWORD dwDeathGaeaID )
{
	SRRP_RANK_INFO* pKillRrPRankInfo = GetRRPRankInof( dwKillChar );
	if ( pKillRrPRankInfo )
	{
		pKillRrPRankInfo->wKillNum++;
	}
	else
	{
		SRRP_RANK_INFO sRrPRankInfo;		
		sRrPRankInfo.dwCharID = dwKillChar;
		sRrPRankInfo.wKillNum++;

		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar( dwKillGaeaID );
		if ( pChar )
		{
			StringCchCopy ( sRrPRankInfo.szCharName, CHAR_NAME+1, pChar->m_szName );
			sRrPRankInfo.szCharName[CHAR_NAME] = '\0';
		}	
	
		m_mapRrPScore[sRrPRankInfo.dwCharID] = sRrPRankInfo;
	}

	SRRP_RANK_INFO* pDeathRrPRankInfo = GetRRPRankInof( dwDeathChar );
	if ( pDeathRrPRankInfo )
	{
		pDeathRrPRankInfo->wDeathNum++;
	}
	else
	{
		SRRP_RANK_INFO sRrPRankInfo;		
		sRrPRankInfo.dwCharID = dwDeathChar;
		sRrPRankInfo.wDeathNum++;

		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar( dwDeathGaeaID );
		if ( pChar )
		{
			StringCchCopy ( sRrPRankInfo.szCharName, CHAR_NAME+1, pChar->m_szName );
			sRrPRankInfo.szCharName[CHAR_NAME] = '\0';
		}
		m_mapRrPScore[sRrPRankInfo.dwCharID] = sRrPRankInfo;
	}
}

bool GLRoyalRumbleMan::Load ( std::vector<std::string> &vecFiles )
{
	std::vector<std::string>::size_type i = 0, j = vecFiles.size();
	for( ; i < j; ++i )
	{
		GLRoyalRumble sRoyalRUMBLE;
		bool bOK = sRoyalRUMBLE.Load( vecFiles[i] );
		if( !bOK )
		{
			CDebugSet::ToLogFile ( "sRoyalRumble.Load() fail, %s", vecFiles[i].c_str() );
			continue;
		}

		m_vecRoyalRUMBLE.push_back ( sRoyalRUMBLE );
	}

	std::sort( m_vecRoyalRUMBLE.begin(), m_vecRoyalRUMBLE.end() );

	return true;
}

GLRoyalRumble* GLRoyalRumbleMan::Find ( DWORD dwID )
{
	GLRoyalRumble cObj;
	cObj.m_dwID = dwID;

	RR_VEC_ITER pos = std::lower_bound ( m_vecRoyalRUMBLE.begin(), m_vecRoyalRUMBLE.end(), cObj );
	if ( pos==m_vecRoyalRUMBLE.end() )
	{
		return NULL;
	}
	else
	{
		return &(*pos);
	}
}

bool GLRoyalRumbleMan::IsBattle ()
{
	for ( RR_VEC::size_type i=0; i<m_vecRoyalRUMBLE.size(); ++i )
	{
		GLRoyalRumble &sRoyalRUMBLE = m_vecRoyalRUMBLE[i];
	
		if ( sRoyalRUMBLE.IsBattle() )		return true;
	}

	return false;
}

GLRoyalRumbleAgentMan& GLRoyalRumbleAgentMan::GetInstance()
{
	static GLRoyalRumbleAgentMan cInstance;
	return cInstance;
}

bool GLRoyalRumbleAgentMan::SetMapState ()
{
	
	for ( RR_VEC::size_type i=0; i<m_vecRoyalRUMBLE.size(); ++i )
	{
		GLRoyalRumble &sRR= m_vecRoyalRUMBLE[i];

		SNATIVEID nidHallMAP ( sRR.m_dwClubHallMap );
		GLAGLandMan *pLandMan = GLAgentServer::GetInstance().GetByMapID ( nidHallMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwRoyalRumbleMapID = sRR.m_dwID;
		}

		SNATIVEID nidMAP ( sRR.m_dwClubMap );
		pLandMan = GLAgentServer::GetInstance().GetByMapID ( nidMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwRoyalRumbleMapID = sRR.m_dwID;
			pLandMan->m_bRoyalRumbleMap = true;
		}
	}

	return true;
}

bool GLRoyalRumbleAgentMan::FrameMove ( float fElapsedAppTime )
{
	if ( GLCONST_CHAR::bPKLESS ) return false;

	for ( RR_VEC::size_type i=0; i<m_vecRoyalRUMBLE.size(); ++i )
	{
		GLRoyalRumble &sRoyalRUMBLE = m_vecRoyalRUMBLE[i];

		CTime cCurTime = CTime::GetCurrentTime();
		int nDayOfWeek = cCurTime.GetDayOfWeek ();
		int nDay = cCurTime.GetDay ();
		int nHour = cCurTime.GetHour();
		int nMinute = cCurTime.GetMinute ();

		DWORD dwORDER = sRoyalRUMBLE.IsBattleWeekDay(nDayOfWeek,nHour);
		if ( dwORDER!=UINT_MAX )
		{
			if ( sRoyalRUMBLE.IsBattleHour ( dwORDER, nHour ) )
			{
				sRoyalRUMBLE.DoBattleStart ( dwORDER, nHour );
				m_fRemainTimer = (float)sRoyalRUMBLE.m_dwBattleTime;
				m_fTimer = 0.0f;
			}
			else
			{
				//	Note : 결정전 시작 공지.
				sRoyalRUMBLE.UpdateNotifyBattle ( dwORDER, nHour, nMinute );
			}
		}

		if ( sRoyalRUMBLE.IsBattle() )
		{
			sRoyalRUMBLE.m_fBattleTimer += fElapsedAppTime;
			if ( sRoyalRUMBLE.m_fBattleTimer > float(sRoyalRUMBLE.m_dwBattleTime) )
			{
				sRoyalRUMBLE.DoBattleEnd();
			}
		}
	}

	if ( !m_vecRoyalRUMBLE.empty() )
	{
		if ( m_vecRoyalRUMBLE[0].IsBattle() )
		{
			GLMSG::SNET_ROYAL_RUMBLE_REMAIN_BRD NetMsgBrd;

			if ( m_fRemainTimer == m_vecRoyalRUMBLE[0].m_dwBattleTime )
			{
				NetMsgBrd.dwTime = (DWORD)m_fRemainTimer;
				GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
			}

			m_fTimer += fElapsedAppTime;
			m_fRemainTimer -= fElapsedAppTime;

			if ( m_fTimer > 600.0f )
			{
				NetMsgBrd.dwTime = (DWORD)m_fRemainTimer;
				GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
				m_fTimer = 0.0f;
			}
		}
	}

	return true;
}

GLRoyalRumbleFieldMan& GLRoyalRumbleFieldMan::GetInstance()
{
	static GLRoyalRumbleFieldMan cInstance;
	return cInstance;
}

bool GLRoyalRumbleFieldMan::SetMapState ()
{
	for ( RR_VEC::size_type i=0; i<m_vecRoyalRUMBLE.size(); ++i )
	{
		GLRoyalRumble &sRR = m_vecRoyalRUMBLE[i];

		SNATIVEID nidHallMAP ( sRR.m_dwClubHallMap );
		GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( nidHallMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwRoyalRumbleMapID = sRR.m_dwID;
			pLandMan->m_bRoyalRumbleMapHall = true;
		}

		SNATIVEID nidMAP ( sRR.m_dwClubMap );
		SMAPNODE *pMAPNODE = GLGaeaServer::GetInstance().FindMapNode ( nidMAP );
		if ( pMAPNODE )
		{
			pMAPNODE->bRRZone = TRUE;
		}

		pLandMan = GLGaeaServer::GetInstance().GetByMapID ( nidMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwRoyalRumbleMapID = sRR.m_dwID;
			pLandMan->m_bRoyalRumbleMap = true;	
		}
	}

	return true;
}
bool GLRoyalRumbleFieldMan::ReadyBattle( DWORD dwID )
{
	GLRoyalRumble *pRR = Find ( dwID );
	if ( !pRR )	return false;

	pRR->SetBattle( GLRoyalRumble::BATTLE_READY );

	return true;
}

bool GLRoyalRumbleFieldMan::BeginBattle ( DWORD dwID )
{
	GLRoyalRumble *pRR = Find ( dwID );
	if ( !pRR )	return false;

	pRR->SetBattle( GLRoyalRumble::BATTLE_START );

	return true;
}

bool GLRoyalRumbleFieldMan::EndBattle ( DWORD dwID )
{
	GLRoyalRumble *pRR = Find ( dwID );
	if ( !pRR )	return false;

	pRR->SetBattle( GLRoyalRumble::BATTLE_END_AWARD );

	pRR->m_fCHECK_TIME = 10.0f;

	UpdateRRPRanking( dwID );
	RRAwardItem( dwID );

	pRR->m_vecRrPAwardChar.clear();
	pRR->m_mapRrPScore.clear();

	GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( pRR->m_dwClubMap );
	if ( pLandMan )
	{
		pLandMan->DoGateOutPCAll ( pRR->m_dwCLubMapGate );
	}

	return true;
}


const std::string GLRoyalRumbleFieldMan::GetName ( DWORD dwID )
{
	GLRoyalRumble *pRR = Find ( dwID );
	if ( !pRR )				return "";

	return pRR->m_strName;
}

DWORD GLRoyalRumbleFieldMan::GetWinClubID ( DWORD dwCharID )
{
	for ( RR_VEC::size_type i=0; i<m_vecRoyalRUMBLE.size(); ++i )
	{
		GLRoyalRumble &sRoyalRUMBLE = m_vecRoyalRUMBLE[i];

		if ( sRoyalRUMBLE.m_dwWinClub == dwCharID )		return sRoyalRUMBLE.m_dwID;
	}

	return UINT_MAX;
}


bool GLRoyalRumbleFieldMan::FrameMove ( float fElaps )
{
	for ( RR_VEC::size_type i=0; i<m_vecRoyalRUMBLE.size(); ++i )
	{
		GLRoyalRumble &sRoyalRUMBLE = m_vecRoyalRUMBLE[i];

		if( sRoyalRUMBLE.IsBattle() )
		{
			m_fRankingUpdateEx += fElaps;
			if ( m_fRankingUpdateEx >= 20.0f )
			{
				UpdateRRPRanking( sRoyalRUMBLE.m_dwID );
				m_fRankingUpdateEx = 0.0f;
			}
		}
	}

	return true;
}

void GLRoyalRumbleFieldMan::UpdateRRPRanking( DWORD dwID )
{
	GLRoyalRumble *pRRP = Find ( dwID );
	if ( !pRRP )	return;
	
	GLRoyalRumble &sRoyalRUMBLE = *pRRP;
	
	RRP_RANK_INFO_VEC	m_vecRrPRankNew;
	m_vecRrPRankNew.reserve( sRoyalRUMBLE.m_mapRrPScore.size() );

	RRP_RANK_INFO_MAP_ITER	pos = sRoyalRUMBLE.m_mapRrPScore.begin();
	RRP_RANK_INFO_MAP_ITER	end = sRoyalRUMBLE.m_mapRrPScore.end();

	for ( ; pos != end; pos++ )
	{
		const SRRP_RANK_INFO&	sRankInfo = pos->second;					
		m_vecRrPRankNew.push_back( sRankInfo );
	}
	
	std::sort( m_vecRrPRankNew.begin(), m_vecRrPRankNew.end() );	

	int nSize = m_vecRrPRankNew.size();

	for ( int i = 0; i < nSize; ++i )
	{
		m_vecRrPRankNew[i].wCharRanking = i+1;
		m_vecRrPRankNew[i].nIndex = i;
	}

	int nRanking;

	for ( int i = nSize-1; i > 0; --i )
	{
		if ( m_vecRrPRankNew[i] == m_vecRrPRankNew[i-1] )
		{
			m_vecRrPRankNew[i-1].wCharRanking = m_vecRrPRankNew[i].wCharRanking;			
		}
	}	
	
	
	GLMSG::SNET_ROYAL_RUMBLE_PRANKING_UPDATE	NetMsg;

	for ( int i = 0; i < m_vecRrPRankNew.size(); ++i )
	{
		RRP_RANK_INFO_MAP_ITER iter = sRoyalRUMBLE.m_mapRrPScore.find( m_vecRrPRankNew[i].dwCharID );
		if ( iter == sRoyalRUMBLE.m_mapRrPScore.end() )	continue;

		SRRP_RANK_INFO&	sRankInfo = iter->second;
		
		if ( m_vecRrPRankNew[i].nIndex != sRankInfo.nIndex || 
			 m_vecRrPRankNew[i].wCharRanking != sRankInfo.wCharRanking )
		{
			sRankInfo.wCharRanking = m_vecRrPRankNew[i].wCharRanking;
			sRankInfo.nIndex = m_vecRrPRankNew[i].nIndex;
			
			if ( m_vecRrPRankNew[i].nIndex < RANKING_RRNUM ) 
			{
				SRRP_RANK sRrPRank = sRankInfo;
				NetMsg.RRADDCHAR( sRrPRank );
			}
		}		
	}

	if ( NetMsg.wRankNum > 0 )	
		GLGaeaServer::GetInstance().SENDTOCLIENT_ONMAP( sRoyalRUMBLE.m_dwClubMap, &NetMsg );


	GLMSG::SNET_ROYAL_RUMBLE_MYPRANK_UPDATE	NetMsgMy;

	pos = sRoyalRUMBLE.m_mapRrPScore.begin();
	end = sRoyalRUMBLE.m_mapRrPScore.end();

	for ( ; pos != end; pos++ )
	{
		const SRRP_RANK_INFO&	sRankInfo = pos->second;
		NetMsgMy.sMyRrPRank.wCharRanking = sRankInfo.wCharRanking;
		NetMsgMy.sMyRrPRank.wKillNum = sRankInfo.wKillNum;
		NetMsgMy.sMyRrPRank.wDeathNum = sRankInfo.wDeathNum;
		
		GLGaeaServer::GetInstance().SENDTOPLAYERCLIENT_ONMAP( sRoyalRUMBLE.m_dwClubMap, sRankInfo.dwCharID, &NetMsgMy );
	}
}

void GLRoyalRumbleFieldMan::RRAwardItem( DWORD dwID )
{
	GLRoyalRumble *pRR = Find ( dwID );
	if ( !pRR )	return;

	if ( !pRR->IsBattleEndAward() ) return;	


	GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( pRR->m_dwClubMap );
	if ( !pLandMan ) return;
	{
		GLCHARNODE* pCharNode = pLandMan->m_GlobPCList.m_pHead;
		for ( ; pCharNode; pCharNode = pCharNode->pNext )
		{
			PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar( pCharNode->Data->m_dwGaeaID );
			if ( !pChar ) continue;

			RRP_RANK_INFO_MAP_ITER iter = pRR->m_mapRrPScore.find( pChar->m_dwCharID );
			if ( iter != pRR->m_mapRrPScore.end() ) 
			{
				SRRP_RANK_INFO& sRrPRankInfo = iter->second;

				RRP_AWARD_CHAR_ITER iter = pRR->m_vecRrPAwardChar.find( pChar->m_dwCharID );
				if ( iter != pRR->m_vecRrPAwardChar.end() )	continue;

				int nAwardIndex;
				if ( sRrPRankInfo.wCharRanking < 10 ) nAwardIndex = sRrPRankInfo.wCharRanking - 1;
				else if ( sRrPRankInfo.wCharRanking <= pRR->m_sRrPAwardItem.dwAwardLimit ) nAwardIndex = 9;
				else continue;
				
				SNATIVEID sNativeID = pRR->m_sRrPAwardItem.nAwardItem[nAwardIndex];
				
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
				pRR->m_vecRrPAwardChar.insert( pChar->m_dwCharID );
			}
		}
	}
}