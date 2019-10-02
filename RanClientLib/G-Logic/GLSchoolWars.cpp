#include "StdAfx.h"

#include <algorithm>

#include "GLDefine.h"
#include "gltexfile.h"
#include "IniLoader.h"

#include "GLSchoolWars.h"

#include "dbactionlogic.h"
#include "GLLandMan.h"
#include "GLGaeaServer.h"
#include "GLAgentServer.h"
#include "GLChar.h"
#include "GLCrow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GLSchoolWars::GLSchoolWars () :
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
	m_fRankingUpdate(0.0f),
	m_wSwBonusRate(0.0f)
{
}

GLSchoolWars& GLSchoolWars::operator= ( const GLSchoolWars& value )
{
	m_dwID = value.m_dwID;
	m_strName = value.m_strName;

	m_dwClubMap = value.m_dwClubMap;
	m_dwCLubMapGate = value.m_dwCLubMapGate;
	m_dwClubHallMap = value.m_dwClubHallMap;
	m_dwClubHallGate = value.m_dwClubHallGate;

	m_dwBattleTime = value.m_dwBattleTime;

	for ( int i=0; i<MAX_TIME; ++i )
		m_sSwTIME[i] = value.m_sSwTIME[i];

	//m_sSwAwardItem = value.m_sSwAwardItem;
	m_sSwPAwardItem = value.m_sSwPAwardItem;

	m_dwWinClub = value.m_dwWinClub;

	m_bNotifyOneHour = value.m_bNotifyOneHour;
	m_bNotifyHalfHour = value.m_bNotifyHalfHour;
	m_bNotify10MinHour = value.m_bNotify10MinHour;

	m_emBattleState = value.m_emBattleState;
	m_dwLastBattleHour = value.m_dwLastBattleHour;
	m_fBattleTimer = value.m_fBattleTimer;

	m_fCHECK_TIMER = value.m_fCHECK_TIMER;
	m_fCHECK_TIME = value.m_fCHECK_TIME;

	m_vecSwAwardChar = value.m_vecSwAwardChar;

	m_vecSwPAwardChar = value.m_vecSwPAwardChar;

	m_fRankingUpdate = value.m_fRankingUpdate;

	m_wSwBonusRate = value.m_wSwBonusRate;

	return *this;
}

bool GLSchoolWars::Load ( std::string strFile )
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
		CDebugSet::ToLogFile ( "ERROR : GLSchoolWars::Load(), File Open %s", strFile.c_str() );
		return false;
	}
	
	cFILE.getflag( "SCHOOL_WARS", "ID", 0, 1, m_dwID );
	cFILE.getflag( "SCHOOL_WARS", "NAME", 0, 1, m_strName );

	SNATIVEID nidMAP;
	cFILE.getflag( "SCHOOL_WARS", "CLUB_MAP", 0, 2, nidMAP.wMainID );
	cFILE.getflag( "SCHOOL_WARS", "CLUB_MAP", 1, 2, nidMAP.wSubID );
	m_dwClubMap = nidMAP.dwID;

	cFILE.getflag( "SCHOOL_WARS", "CLUB_GATE", 0, 1, m_dwCLubMapGate );

	cFILE.getflag( "SCHOOL_WARS", "CLUB_HALL_MAP", 0, 2, nidMAP.wMainID );
	cFILE.getflag( "SCHOOL_WARS", "CLUB_HALL_MAP", 1, 2, nidMAP.wSubID );
	m_dwClubHallMap = nidMAP.dwID;

	cFILE.getflag( "SCHOOL_WARS", "CLUB_HALL_GATE", 0, 1, m_dwClubHallGate );

	DWORD dwNUM = cFILE.GetKeySize( "SCHOOL_WARS", "BATTLE_TIME" );
	if( dwNUM > MAX_TIME )
	{
		CDebugSet::ToLogFile( "ERROR : GLSchoolWars::Load(), %s, It was wrong size of BATTLE_TIME", strFile.c_str() );
		return false;
	}

	for( DWORD i=0; i<dwNUM; ++i )
	{
		cFILE.getflag( i, "SCHOOL_WARS", "BATTLE_TIME", 0, 2, m_sSwTIME[i].dwWeekDay );
		cFILE.getflag( i, "SCHOOL_WARS", "BATTLE_TIME", 1, 2, m_sSwTIME[i].dwStartTime );
	}

	cFILE.getflag( "SCHOOL_WARS", "BATTLE_THE_TIME", 0, 1, m_dwBattleTime );

	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_1", 0, 2, m_sSwPAwardItem.nAwardItem[0].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_1", 1, 2, m_sSwPAwardItem.nAwardItem[0].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_2", 0, 2, m_sSwPAwardItem.nAwardItem[1].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_2", 1, 2, m_sSwPAwardItem.nAwardItem[1].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_3", 0, 2, m_sSwPAwardItem.nAwardItem[2].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_3", 1, 2, m_sSwPAwardItem.nAwardItem[2].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_4", 0, 2, m_sSwPAwardItem.nAwardItem[3].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_4", 1, 2, m_sSwPAwardItem.nAwardItem[3].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_5", 0, 2, m_sSwPAwardItem.nAwardItem[4].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_5", 1, 2, m_sSwPAwardItem.nAwardItem[4].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_6", 0, 2, m_sSwPAwardItem.nAwardItem[5].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_6", 1, 2, m_sSwPAwardItem.nAwardItem[5].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_7", 0, 2, m_sSwPAwardItem.nAwardItem[6].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_7", 1, 2, m_sSwPAwardItem.nAwardItem[6].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_8", 0, 2, m_sSwPAwardItem.nAwardItem[7].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_8", 1, 2, m_sSwPAwardItem.nAwardItem[7].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_9", 0, 2, m_sSwPAwardItem.nAwardItem[8].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_9", 1, 2, m_sSwPAwardItem.nAwardItem[8].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_10", 0, 2, m_sSwPAwardItem.nAwardItem[9].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_10", 1, 2, m_sSwPAwardItem.nAwardItem[9].wSubID );

	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_LIMIT", 0, 1, m_sSwPAwardItem.dwAwardLimit );

	cFILE.getflag( "SCHOOL_WARS", "SW_BONUS_RATE", 0, 1, m_wSwBonusRate );

	return true;
}

DWORD GLSchoolWars::IsBattleWeekDay ( int nDayOfWeek, int nHour )
{
	if ( IsBattle() )	return UINT_MAX;

	for ( DWORD i=0; i<MAX_TIME; ++i )
	{
		if ( (nDayOfWeek==m_sSwTIME[i].dwWeekDay) && 
			 (nHour==m_sSwTIME[i].dwStartTime) &&
			 (m_dwLastBattleHour!=nHour) )
		{
			return i;
		}
	}
	return UINT_MAX;
}

bool GLSchoolWars::IsBattleHour ( DWORD dwORDER, int nHour )
{
	if ( dwORDER>=MAX_TIME )
	{
		return false;
	}
	
	if (m_sSwTIME[dwORDER].dwStartTime == nHour)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

void GLSchoolWars::UpdateBattleDay ( int nHour )
{
	m_dwLastBattleHour = nHour;
}

void GLSchoolWars::UpdateNotifyBattle ( DWORD dwORDER, int nHour, int nMinute )
{
	if ( dwORDER>=MAX_TIME )	return;

	DWORD dwOTime = m_sSwTIME[dwORDER].dwStartTime;
	if ( dwOTime <= 0 )			return;
	
	dwOTime -= 1;
	if ( nHour == dwOTime )
	{
		if ( !m_bNotifyOneHour )
		{
			m_bNotifyOneHour = true;

			GLMSG::SNET_SCHOOL_WARS_START_BRD NetMsgBrd;
			NetMsgBrd.nTIME = 60-nMinute;
			StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_SCHOOL_WARS_START_BRD::TEXT_LEN, m_strName.c_str() );
			GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
		}

		if ( nMinute == 30 )
		{
			if ( !m_bNotifyHalfHour )
			{
				m_bNotifyHalfHour = true;

				GLMSG::SNET_SCHOOL_WARS_START_BRD NetMsgBrd;
				NetMsgBrd.nTIME = 30;
				StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_SCHOOL_WARS_START_BRD::TEXT_LEN, m_strName.c_str() );
				GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
			}
		}

		if ( nMinute == 50 )
		{
			if ( !m_bNotify10MinHour )
			{
				m_bNotify10MinHour = true;
				m_emBattleState = BATTLE_READY;

				GLMSG::SNET_SCHOOL_WARS_START_BRD NetMsgBrd;
				NetMsgBrd.nTIME = 10;
				StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_SCHOOL_WARS_START_BRD::TEXT_LEN, m_strName.c_str() );
				GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );

				GLMSG::SNET_SCHOOL_WARS_READY_FLD NetMsgFld;
				NetMsgFld.dwID = m_dwID;
				GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );
			}
		}
	}

}

void GLSchoolWars::DoBattleStart ( DWORD dwORDER, int nHour )
{
	m_emBattleState = BATTLE_START;
	m_dwBattleOrder = dwORDER;
	m_fRankingUpdate = 0.0f;

	m_vecSwAwardChar.clear();
	m_mapSwScore.clear();
	m_vecSwPAwardChar.clear();
	m_mapSwPScore.clear();

	UpdateBattleDay ( nHour );

	GLMSG::SNET_SCHOOL_WARS_START_FLD NetMsgFld;
	NetMsgFld.dwID = m_dwID;
	GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );

	GLMSG::SNET_SCHOOL_WARS_START_BRD NetMsgBrd;
	NetMsgBrd.nTIME = 0;
	StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_CLUB_BATTLE_START_BRD::TEXT_LEN, m_strName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );

}

void GLSchoolWars::DoBattleEnd()
{
	m_emBattleState = BATTLE_END;
	m_dwBattleOrder = UINT_MAX;

	m_bNotifyOneHour = false;
	m_bNotifyHalfHour = false;
	m_bNotify10MinHour = false;
	m_fBattleTimer = 0.0f;
	m_fRankingUpdate = 0.0f;

	std::string strClubName;

	switch( m_dwWinClub )
	{
		case 0:	strClubName = "SG";		break;
		case 1: strClubName = "MP";		break;
		case 2:	strClubName = "PHX";	break;
		default:strClubName = "none";	break;
	}

	for(int i = 0; i<3;i++)
	{
		GLMSG::SNET_GM_SCHOOL_EVENT NetSwMsg;
		NetSwMsg.bStart = TRUE;
		NetSwMsg.m_wSchool = (WORD) m_dwWinClub;
		NetSwMsg.fEventRate	= m_wSwBonusRate;
		NetSwMsg.dwEventType = i;
		GLAgentServer::GetInstance().SENDTOALLCHANNEL( &NetSwMsg );
	}
	
	GLMSG::SNET_SCHOOL_WARS_END_FLD NetMsgFld;
	NetMsgFld.dwID = m_dwID;
	GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );

	GLMSG::SNET_SCHOOL_WARS_END_BRD NetMsgBrd;
	StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_SCHOOL_WARS_END_BRD::TEXT_LEN, m_strName.c_str() );
	StringCchCopy ( NetMsgBrd.szClubName, CHAR_SZNAME, strClubName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );

	GLMSG::SNET_SCHOOL_WARS_SETWINSCHOOL_BRD NetMsgBrd2;
	NetMsgBrd2.wSchool = (WORD) m_dwWinClub;
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd2 );
}

void GLSchoolWars::CheckAwardClub( float fElaps )
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

bool GLSchoolWars::IsEnterMap(DWORD dwCharID)
{
	if ( dwCharID == GAEAID_NULL ) return false;
	if ( IsBattle() ) return true;
	if ( IsBattleReady() ) return true;

	return false;
}

SSW_RANK_INFO* GLSchoolWars::GetSWRankInof( DWORD dwClubID )
{
	SW_RANK_INFO_MAP_ITER pos = m_mapSwScore.find( dwClubID );
	if( pos == m_mapSwScore.end() )
	{
		return NULL;
	}
	
	return &(*pos).second;;
}

SSWP_RANK_INFO* GLSchoolWars::GetSWPRankInof( DWORD dwCharID )
{
	SWP_RANK_INFO_MAP_ITER pos = m_mapSwPScore.find( dwCharID );
	if( pos == m_mapSwPScore.end() )
	{
		return NULL;
	}
	
	return &(*pos).second;;
}

void GLSchoolWars::AddSWScore( DWORD dwKillClub, DWORD dwDeathClub )
{
	CString m_zScName = "";

	SSW_RANK_INFO* pKillSwRankInfo = GetSWRankInof( dwKillClub );
	if ( pKillSwRankInfo )
	{
		pKillSwRankInfo->wKillNum++;
	}
	else
	{

		SSW_RANK_INFO sSwRankInfo;		
		sSwRankInfo.dwClubID = dwKillClub;
		sSwRankInfo.wKillNum++;

		switch(sSwRankInfo.dwClubID)
		{
			case 0:	m_zScName = "Sacred Gate";	break;
			case 1:	m_zScName = "Mystic Peak";	break;
			case 2:	m_zScName = "Phoenix";		break;
		}
		StringCchCopy ( sSwRankInfo.szClubName, SCHOOL_NAME+1, m_zScName );
		sSwRankInfo.szClubName[SCHOOL_NAME] = '\0';
	
		m_mapSwScore[sSwRankInfo.dwClubID] = sSwRankInfo;
	}

	SSW_RANK_INFO* pDeathSwRankInfo = GetSWRankInof( dwDeathClub );
	if ( pDeathSwRankInfo )
	{
		pDeathSwRankInfo->wDeathNum++;
	}
	else
	{
		SSW_RANK_INFO sSwRankInfo;		
		sSwRankInfo.dwClubID = dwDeathClub;
		sSwRankInfo.wDeathNum++;

		switch(sSwRankInfo.dwClubID)
		{
			case 0:	m_zScName = "Sacred Gate";	break;
			case 1:	m_zScName = "Mystic Peak";	break;
			case 2:	m_zScName = "Phoenix";		break;
		}

		StringCchCopy ( sSwRankInfo.szClubName, SCHOOL_NAME+1, m_zScName );
		sSwRankInfo.szClubName[SCHOOL_NAME] = '\0';		
	
		m_mapSwScore[sSwRankInfo.dwClubID] = sSwRankInfo;
	}
}

void GLSchoolWars::AddSWPScore( DWORD dwKillChar, DWORD dwKillGaeaID, DWORD dwDeathChar, DWORD dwDeathGaeaID )
{
	SSWP_RANK_INFO* pKillSwPRankInfo = GetSWPRankInof( dwKillChar );
	if ( pKillSwPRankInfo )
	{
		pKillSwPRankInfo->wKillNum++;
	}
	else
	{
		SSWP_RANK_INFO sSwPRankInfo;		
		sSwPRankInfo.dwCharID = dwKillChar;
		sSwPRankInfo.wKillNum++;

		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar( dwKillGaeaID );
		if ( pChar )
		{
			StringCchCopy ( sSwPRankInfo.szCharName, CHAR_NAME+1, pChar->m_szName );
			sSwPRankInfo.szCharName[CHAR_NAME] = '\0';
		}	
	
		m_mapSwPScore[sSwPRankInfo.dwCharID] = sSwPRankInfo;
	}

	SSWP_RANK_INFO* pDeathSwPRankInfo = GetSWPRankInof( dwDeathChar );
	if ( pDeathSwPRankInfo )
	{
		pDeathSwPRankInfo->wDeathNum++;
	}
	else
	{
		SSWP_RANK_INFO sSwPRankInfo;		
		sSwPRankInfo.dwCharID = dwDeathChar;
		sSwPRankInfo.wDeathNum++;

		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar( dwDeathGaeaID );
		if ( pChar )
		{
			StringCchCopy ( sSwPRankInfo.szCharName, CHAR_NAME+1, pChar->m_szName );
			sSwPRankInfo.szCharName[CHAR_NAME] = '\0';
		}
		m_mapSwPScore[sSwPRankInfo.dwCharID] = sSwPRankInfo;
	}
}

void GLSchoolWars::AddFlagScore( DWORD dwKillSchool, WORD wKillPoints )
{
	CString m_zScName = "";

	SSW_RANK_INFO* pKillSwRankInfo = GetSWRankInof( dwKillSchool );
	if ( pKillSwRankInfo )
	{
		pKillSwRankInfo->wKillNum += wKillPoints;
	}
	else
	{

		SSW_RANK_INFO sSwRankInfo;		
		sSwRankInfo.dwClubID = dwKillSchool;
		sSwRankInfo.wKillNum += wKillPoints ;

		switch(sSwRankInfo.dwClubID)
		{
			case 0:	m_zScName = "SG";	break;
			case 1:	m_zScName = "MP";	break;
			case 2:	m_zScName = "PHX";	break;
		}
		StringCchCopy ( sSwRankInfo.szClubName, SCHOOL_NAME+1, m_zScName );
		sSwRankInfo.szClubName[SCHOOL_NAME] = '\0';
	
		m_mapSwScore[sSwRankInfo.dwClubID] = sSwRankInfo;
	}
}

bool GLSchoolWars::ChangeSWSchoolID ( DWORD dwSwID )
{
	m_dwWinClub = dwSwID;

	CSetSwRegion *pDbAction = new CSetSwRegion ( m_dwID, m_dwWinClub );
	GLAgentServer::GetInstance().GetDBMan()->AddJob ( pDbAction );

	return true;
}

bool GLSchoolWarsMan::Load ( std::vector<std::string> &vecFiles )
{
	std::vector<std::string>::size_type i = 0, j = vecFiles.size();
	for( ; i < j; ++i )
	{
		GLSchoolWars sSchoolWAR;
		bool bOK = sSchoolWAR.Load( vecFiles[i] );
		if( !bOK )
		{
			CDebugSet::ToLogFile ( "sSchoolWars.Load() fail, %s", vecFiles[i].c_str() );
			continue;
		}

		m_vecSchoolWAR.push_back ( sSchoolWAR );
	}

	std::sort( m_vecSchoolWAR.begin(), m_vecSchoolWAR.end() );

	return true;
}

GLSchoolWars* GLSchoolWarsMan::Find ( DWORD dwID )
{
	GLSchoolWars cObj;
	cObj.m_dwID = dwID;

	SW_VEC_ITER pos = std::lower_bound ( m_vecSchoolWAR.begin(), m_vecSchoolWAR.end(), cObj );
	if ( pos==m_vecSchoolWAR.end() )
	{
		return NULL;
	}
	else
	{
		return &(*pos);
	}
}

bool GLSchoolWarsMan::SetState ( VECSWID_DB &vecSWID )
{
	for ( VECSWID_DB::size_type i=0; i<vecSWID.size(); ++i )
	{
		const GLSWID &sSWID = vecSWID[i];
		
		GLSchoolWars* pSwid = Find ( sSWID.m_dwID );
		if ( !pSwid )
		{			
			//TCHAR szTemp[128] = {0};
			//_snprintf( szTemp, 128, "GLSchoolWars::Find() fail, %u", sSWID.m_dwID );

			//MessageBox ( NULL, szTemp, "ERROR", MB_OK );
			continue;
		}

		pSwid->m_dwWinClub = sSWID.m_dwSWID;
	}

	return true;
}

bool GLSchoolWarsMan::IsBattle ()
{
	for ( SW_VEC::size_type i=0; i<m_vecSchoolWAR.size(); ++i )
	{
		GLSchoolWars &sSchoolWAR = m_vecSchoolWAR[i];
	
		if ( sSchoolWAR.IsBattle() )		return true;
	}

	return false;
}

GLSchoolWarsAgentMan& GLSchoolWarsAgentMan::GetInstance()
{
	static GLSchoolWarsAgentMan cInstance;
	return cInstance;
}

bool GLSchoolWarsAgentMan::SetMapState ()
{
	
	for ( SW_VEC::size_type i=0; i<m_vecSchoolWAR.size(); ++i )
	{
		GLSchoolWars &sSW= m_vecSchoolWAR[i];

		SNATIVEID nidHallMAP ( sSW.m_dwClubHallMap );
		GLAGLandMan *pLandMan = GLAgentServer::GetInstance().GetByMapID ( nidHallMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwSchoolWarMapID = sSW.m_dwID;
		}

		SNATIVEID nidMAP ( sSW.m_dwClubMap );
		pLandMan = GLAgentServer::GetInstance().GetByMapID ( nidMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwSchoolWarMapID = sSW.m_dwID;
			pLandMan->m_bSchoolWarsMap = true;
		}
	}

	return true;
}

bool GLSchoolWarsAgentMan::ChangeSWSchoolID ( DWORD dwID, DWORD dwSwID )
{
	GLSchoolWars *pGuid = Find ( dwID );
	if ( !pGuid )				return false;

	pGuid->ChangeSWSchoolID ( dwSwID );

	return true;
}

bool GLSchoolWarsAgentMan::FrameMove ( float fElapsedAppTime )
{
	if ( GLCONST_CHAR::bPKLESS ) return false;

	for ( SW_VEC::size_type i=0; i<m_vecSchoolWAR.size(); ++i )
	{
		GLSchoolWars &sSchoolWAR = m_vecSchoolWAR[i];

		CTime cCurTime = CTime::GetCurrentTime();
		int nDayOfWeek = cCurTime.GetDayOfWeek ();
		int nDay = cCurTime.GetDay ();
		int nHour = cCurTime.GetHour();
		int nMinute = cCurTime.GetMinute ();

		DWORD dwORDER = sSchoolWAR.IsBattleWeekDay(nDayOfWeek,nHour);
		if ( dwORDER!=UINT_MAX )
		{
			if ( sSchoolWAR.IsBattleHour ( dwORDER, nHour ) )
			{
				sSchoolWAR.DoBattleStart ( dwORDER, nHour );
				m_fRemainTimer = (float)sSchoolWAR.m_dwBattleTime;
				m_fTimer = 0.0f;
			}
			else
			{
				sSchoolWAR.UpdateNotifyBattle ( dwORDER, nHour, nMinute );
			}
		}

		if ( sSchoolWAR.IsBattle() )
		{
			sSchoolWAR.m_fBattleTimer += fElapsedAppTime;
			if ( sSchoolWAR.m_fBattleTimer > float(sSchoolWAR.m_dwBattleTime) )
			{
				sSchoolWAR.DoBattleEnd();
			}
		}
	}

	if ( !m_vecSchoolWAR.empty() )
	{
		if ( m_vecSchoolWAR[0].IsBattle() )
		{
			GLMSG::SNET_SCHOOL_WARS_REMAIN_BRD NetMsgBrd;

			if ( m_fRemainTimer == m_vecSchoolWAR[0].m_dwBattleTime )
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

GLSchoolWarsFieldMan& GLSchoolWarsFieldMan::GetInstance()
{
	static GLSchoolWarsFieldMan cInstance;
	return cInstance;
}

bool GLSchoolWarsFieldMan::SetMapState ()
{
	for ( SW_VEC::size_type i=0; i<m_vecSchoolWAR.size(); ++i )
	{
		GLSchoolWars &sSW = m_vecSchoolWAR[i];

		SNATIVEID nidHallMAP ( sSW.m_dwClubHallMap );
		GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( nidHallMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwSchoolWarMapID = sSW.m_dwID;
			pLandMan->m_bSchoolWarsMapHall = true;
		}

		SNATIVEID nidMAP ( sSW.m_dwClubMap );
		SMAPNODE *pMAPNODE = GLGaeaServer::GetInstance().FindMapNode ( nidMAP );
		if ( pMAPNODE )
		{
			pMAPNODE->bSWZone = TRUE;
		}

		pLandMan = GLGaeaServer::GetInstance().GetByMapID ( nidMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwSchoolWarMapID = sSW.m_dwID;
			pLandMan->m_bSchoolWarsMap = true;	
		}
	}

	return true;
}
bool GLSchoolWarsFieldMan::ReadyBattle( DWORD dwID )
{
	GLSchoolWars *pSW = Find ( dwID );
	if ( !pSW )	return false;

	pSW->SetBattle( GLSchoolWars::BATTLE_READY );

	return true;
}

bool GLSchoolWarsFieldMan::BeginBattle ( DWORD dwID )
{
	GLSchoolWars *pSW = Find ( dwID );
	if ( !pSW )	return false;

	pSW->SetBattle( GLSchoolWars::BATTLE_START );

	return true;
}

bool GLSchoolWarsFieldMan::ChangeSWSchoolID ( DWORD dwID, DWORD dwSwID )
{
	GLSchoolWars *pSwid = Find ( dwID );
	if ( !pSwid )	return false;

	pSwid->m_dwWinClub = dwSwID;

	return true;
}

bool GLSchoolWarsFieldMan::EndBattle ( DWORD dwID )
{
	GLSchoolWars *pSW = Find ( dwID );
	if ( !pSW )	return false;

	pSW->SetBattle( GLSchoolWars::BATTLE_END_AWARD );

	pSW->m_fCHECK_TIME = 10.0f;


	UpdateSWRanking( dwID );
	UpdateSWPRanking( dwID );
	SWAwardItem( dwID );

	pSW->m_vecSwAwardChar.clear();
	pSW->m_mapSwScore.clear();
	pSW->m_vecSwPAwardChar.clear();
	pSW->m_mapSwPScore.clear();

	GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( pSW->m_dwClubMap );
	if ( pLandMan )
	{
		pLandMan->DoGateOutPCAll ( pSW->m_dwCLubMapGate );
	}

	return true;
}


const std::string GLSchoolWarsFieldMan::GetName ( DWORD dwID )
{
	GLSchoolWars *pSW = Find ( dwID );
	if ( !pSW )				return "";

	return pSW->m_strName;
}

DWORD GLSchoolWarsFieldMan::GetWinClubID ( DWORD dwClubID )
{
	for ( SW_VEC::size_type i=0; i<m_vecSchoolWAR.size(); ++i )
	{
		GLSchoolWars &sSchoolWAR = m_vecSchoolWAR[i];

		if ( sSchoolWAR.m_dwWinClub == dwClubID )		return sSchoolWAR.m_dwID;
	}

	return UINT_MAX;
}


bool GLSchoolWarsFieldMan::FrameMove ( float fElaps )
{
	for ( SW_VEC::size_type i=0; i<m_vecSchoolWAR.size(); ++i )
	{
		GLSchoolWars &sSchoolWAR = m_vecSchoolWAR[i];

		if( sSchoolWAR.IsBattle() )
		{
			sSchoolWAR.m_fRankingUpdate += fElaps;

			if ( sSchoolWAR.m_fRankingUpdate > 20.0f )
			{
				UpdateSWRanking( sSchoolWAR.m_dwID );
				UpdateSWPRanking( sSchoolWAR.m_dwID );
				sSchoolWAR.m_fRankingUpdate = 0.0f;
			}
		}

		/*
		if ( sSchoolWAR.IsBattleEndAward() )
		{
			sSchoolWAR.CheckAwardClub( fElaps );
		}

		if ( sSchoolWAR.IsBattleEnd() ) {}
		*/
	}

	return true;
}

void GLSchoolWarsFieldMan::UpdateSWRanking( DWORD dwID )
{
	GLSchoolWars *pSW = Find ( dwID );
	if ( !pSW )	return;
	
	GLSchoolWars &sSchoolWAR = *pSW;
	
	SW_RANK_INFO_VEC	m_vecSwRankNew;
	m_vecSwRankNew.reserve( sSchoolWAR.m_mapSwScore.size() );

	SW_RANK_INFO_MAP_ITER	pos = sSchoolWAR.m_mapSwScore.begin();
	SW_RANK_INFO_MAP_ITER	end = sSchoolWAR.m_mapSwScore.end();

	for ( ; pos != end; pos++ )
	{
		const SSW_RANK_INFO&	sRankInfo = pos->second;					
		m_vecSwRankNew.push_back( sRankInfo );
	}
	
	std::sort( m_vecSwRankNew.begin(), m_vecSwRankNew.end() );	

	int nSize = m_vecSwRankNew.size();

	for ( int i = 0; i < nSize; ++i )
	{
		m_vecSwRankNew[i].wClubRanking = i+1;
		m_vecSwRankNew[i].nIndex = i;

		if( i == 0 && pSW->m_dwWinClub != m_vecSwRankNew[i].dwClubID)
		{
			GLMSG::SNET_SCHOOL_WARS_CERTIFIED_AGT NetMsg;
			NetMsg.dwID = dwID;
			NetMsg.dwSCHOOL = m_vecSwRankNew[i].dwClubID;
			GLGaeaServer::GetInstance().SENDTOAGENT ( &NetMsg );
		}
	}

	int nRanking;

	for ( int i = nSize-1; i > 0; --i )
	{
		if ( m_vecSwRankNew[i] == m_vecSwRankNew[i-1] )
		{
			m_vecSwRankNew[i-1].wClubRanking = m_vecSwRankNew[i].wClubRanking;			
		}
	}	
	
	
	GLMSG::SNET_SCHOOL_WARS_RANKING_UPDATE	NetMsg;

	for ( int i = 0; i < m_vecSwRankNew.size(); ++i )
	{
		SW_RANK_INFO_MAP_ITER iter = sSchoolWAR.m_mapSwScore.find( m_vecSwRankNew[i].dwClubID );
		if ( iter == sSchoolWAR.m_mapSwScore.end() )	continue;

		SSW_RANK_INFO&	sRankInfo = iter->second;
		
		if ( m_vecSwRankNew[i].nIndex != sRankInfo.nIndex || 
			 m_vecSwRankNew[i].wClubRanking != sRankInfo.wClubRanking )
		{
			sRankInfo.wClubRanking = m_vecSwRankNew[i].wClubRanking;
			sRankInfo.nIndex = m_vecSwRankNew[i].nIndex;
			
			if ( m_vecSwRankNew[i].nIndex < RANKING_NUM ) 
			{
				SSW_RANK sSwRank = sRankInfo;
				NetMsg.ADDSCHOOL( sSwRank );
			}
		}		
	}

	if ( NetMsg.wRankNum > 0 )	
		GLGaeaServer::GetInstance().SENDTOCLIENT_ONMAP( sSchoolWAR.m_dwClubMap, &NetMsg );


	GLMSG::SNET_SCHOOL_WARS_MYRANK_UPDATE	NetMsgMy;

	pos = sSchoolWAR.m_mapSwScore.begin();
	end = sSchoolWAR.m_mapSwScore.end();

	for ( ; pos != end; pos++ )
	{
		const SSW_RANK_INFO&	sRankInfo = pos->second;
		NetMsgMy.sMySwRank.wClubRanking = sRankInfo.wClubRanking;
		NetMsgMy.sMySwRank.wKillNum = sRankInfo.wKillNum;
		NetMsgMy.sMySwRank.wDeathNum = sRankInfo.wDeathNum;
		
		GLGaeaServer::GetInstance().SENDTOSCHOOLCLIENT_ONMAP( sSchoolWAR.m_dwClubMap, sRankInfo.dwClubID, &NetMsgMy );
	}

}

void GLSchoolWarsFieldMan::UpdateSWPRanking( DWORD dwID )
{
	GLSchoolWars *pSWP = Find ( dwID );
	if ( !pSWP )	return;
	
	GLSchoolWars &sSchoolWAR = *pSWP;
	
	SWP_RANK_INFO_VEC	m_vecSwPRankNew;
	m_vecSwPRankNew.reserve( sSchoolWAR.m_mapSwPScore.size() );

	SWP_RANK_INFO_MAP_ITER	pos = sSchoolWAR.m_mapSwPScore.begin();
	SWP_RANK_INFO_MAP_ITER	end = sSchoolWAR.m_mapSwPScore.end();

	for ( ; pos != end; pos++ )
	{
		const SSWP_RANK_INFO&	sRankInfo = pos->second;					
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
	
	
	GLMSG::SNET_SCHOOL_WARS_PRANKING_UPDATE	NetMsg;

	for ( int i = 0; i < m_vecSwPRankNew.size(); ++i )
	{
		SWP_RANK_INFO_MAP_ITER iter = sSchoolWAR.m_mapSwPScore.find( m_vecSwPRankNew[i].dwCharID );
		if ( iter == sSchoolWAR.m_mapSwPScore.end() )	continue;

		SSWP_RANK_INFO&	sRankInfo = iter->second;
		
		if ( m_vecSwPRankNew[i].nIndex != sRankInfo.nIndex || 
			 m_vecSwPRankNew[i].wCharRanking != sRankInfo.wCharRanking )
		{
			sRankInfo.wCharRanking = m_vecSwPRankNew[i].wCharRanking;
			sRankInfo.nIndex = m_vecSwPRankNew[i].nIndex;
			
			if ( m_vecSwPRankNew[i].nIndex < RANKING_PNUM ) 
			{
				SSWP_RANK sSwPRank = sRankInfo;
				NetMsg.ADDCHAR( sSwPRank );
			}
		}		
	}

	if ( NetMsg.wRankNum > 0 )	
		GLGaeaServer::GetInstance().SENDTOCLIENT_ONMAP( sSchoolWAR.m_dwClubMap, &NetMsg );


	GLMSG::SNET_SCHOOL_WARS_MYPRANK_UPDATE	NetMsgMy;

	pos = sSchoolWAR.m_mapSwPScore.begin();
	end = sSchoolWAR.m_mapSwPScore.end();

	for ( ; pos != end; pos++ )
	{
		const SSWP_RANK_INFO&	sRankInfo = pos->second;
		NetMsgMy.sMySwPRank.wCharRanking = sRankInfo.wCharRanking;
		NetMsgMy.sMySwPRank.wKillNum = sRankInfo.wKillNum;
		NetMsgMy.sMySwPRank.wDeathNum = sRankInfo.wDeathNum;
		
		GLGaeaServer::GetInstance().SENDTOPLAYERCLIENT_ONMAP( sSchoolWAR.m_dwClubMap, sRankInfo.dwCharID, &NetMsgMy );
	}
}

void GLSchoolWarsFieldMan::SWAwardItem( DWORD dwID )
{
	GLSchoolWars *pSW = Find ( dwID );
	if ( !pSW )	return;

	if ( !pSW->IsBattleEndAward() ) return;	


	GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( pSW->m_dwClubMap );
	if ( !pLandMan ) return;
	{
		GLCHARNODE* pCharNode = pLandMan->m_GlobPCList.m_pHead;
		for ( ; pCharNode; pCharNode = pCharNode->pNext )
		{
			PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar( pCharNode->Data->m_dwGaeaID );
			if ( !pChar ) continue;

			SWP_RANK_INFO_MAP_ITER iter = pSW->m_mapSwPScore.find( pChar->m_dwCharID );
			if ( iter != pSW->m_mapSwPScore.end() ) 
			{
				SSWP_RANK_INFO& sSwPRankInfo = iter->second;

				SWP_AWARD_CHAR_ITER iter = pSW->m_vecSwPAwardChar.find( pChar->m_dwCharID );
				if ( iter != pSW->m_vecSwPAwardChar.end() )	continue;

				int nAwardIndex;
				if ( sSwPRankInfo.wCharRanking < 10 ) nAwardIndex = sSwPRankInfo.wCharRanking - 1;
				else if ( sSwPRankInfo.wCharRanking <= pSW->m_sSwPAwardItem.dwAwardLimit ) nAwardIndex = 9;
				else continue;
				
				SNATIVEID sNativeID = pSW->m_sSwPAwardItem.nAwardItem[nAwardIndex];
				
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
				pSW->m_vecSwPAwardChar.insert( pChar->m_dwCharID );
			}
		}
	}
}