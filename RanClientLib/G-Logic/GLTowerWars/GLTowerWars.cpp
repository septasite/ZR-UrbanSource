#include "StdAfx.h"

#include <algorithm>

#include "GLDefine.h"
#include "gltexfile.h"
#include "IniLoader.h"

#include "GLTowerWars.h"

#include "GLLandMan.h"
#include "GLGaeaServer.h"
#include "GLAgentServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GLTowerWars::GLTowerWars () :
	m_dwID(UINT_MAX),
	m_dwClubMap(0),
	m_dwCLubMapGate(0),

	m_dwWinClub(CLUB_NULL),

	m_dwBattleTime(3600),

	m_bNotifyOneHour(false),
	m_bNotifyHalfHour(false),
	m_bNotify10MinHour(false),
	m_dwBattleTimePrevious( 0 ),
	m_dwBattleTimeNext( 0 ),
    m_dwNextTime( 0 ),
	m_emBattleState(BATTLE_NOSTART),
	m_dwBattleOrder(0),
	m_dwLastBattleHour(0),
	m_fBattleTimer(0.0f),

	m_fCHECK_TIMER(0.0f),
	m_fCHECK_TIME(0.0f),
	bBattleEnd(false),
	m_fRankingUpdate(0.0f),
	m_emForceExit(FORCE_EXIT_NO),
	m_bKickOut(false),
	m_fKickTimer(0.0f),
	m_fKickTotal(0.0f)
{
	for ( int i = 0; i < CTF_MAX_REVIVE_GATE; ++ i )
		m_dwReviveGate[i] = 1;
}

GLTowerWars& GLTowerWars::operator= ( const GLTowerWars& value )
{
	m_dwID = value.m_dwID;
	m_strName = value.m_strName;

	m_dwClubMap = value.m_dwClubMap;
	m_dwCLubMapGate = value.m_dwCLubMapGate;

	m_dwBattleTime = value.m_dwBattleTime;

	for ( int i=0; i<MAX_TIME; ++i )
		m_sTwTIME[i] = value.m_sTwTIME[i];

	m_sTwPAwardItem = value.m_sTwPAwardItem;

	m_vecCtfAwardChar = value.m_vecCtfAwardChar;
	m_mapCtfScore = value.m_mapCtfScore;
	m_mapTowerStatus = value.m_mapTowerStatus;

	m_dwWinClub = value.m_dwWinClub;

	m_bNotifyOneHour = value.m_bNotifyOneHour;
	m_bNotifyHalfHour = value.m_bNotifyHalfHour;
	m_bNotify10MinHour = value.m_bNotify10MinHour;

	m_emBattleState = value.m_emBattleState;
	m_dwLastBattleHour = value.m_dwLastBattleHour;
	m_fBattleTimer = value.m_fBattleTimer;

	m_fCHECK_TIMER = value.m_fCHECK_TIMER;
	m_fCHECK_TIME = value.m_fCHECK_TIME;

	m_fRankingUpdate = value.m_fRankingUpdate;

	bBattleEnd = value.bBattleEnd;

	m_dwBattleTimeNext		= value.m_dwBattleTimeNext;
	m_dwBattleTimePrevious	= value.m_dwBattleTimePrevious;
	m_dwNextTime			= value.m_dwNextTime;

	m_emForceExit = value.m_emForceExit;

	for ( int i=0; i < CTF_MAX_REVIVE_GATE; ++ i )
		m_dwReviveGate[i] = value.m_dwReviveGate[i];

	m_bKickOut = value.m_bKickOut;
	m_fKickTimer = value.m_fKickTimer;
	m_fKickTotal = value.m_fKickTotal;

	return *this;
}

bool GLTowerWars::Load ( std::string strFile )
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
		CDebugSet::ToLogFile ( "ERROR : GLTowerWars::Load(), File Open %s", strFile.c_str() );
		return false;
	}
	
	cFILE.getflag( "SCHOOL_WARS", "ID", 0, 1, m_dwID );

	cFILE.getflag( "SCHOOL_WARS", "NAME", 0, 1, m_strName );

	SNATIVEID nidMAP;
	cFILE.getflag( "SCHOOL_WARS", "CLUB_MAP", 0, 2, nidMAP.wMainID );
	cFILE.getflag( "SCHOOL_WARS", "CLUB_MAP", 1, 2, nidMAP.wSubID );
	m_dwClubMap = nidMAP.dwID;

	cFILE.getflag( "SCHOOL_WARS", "CLUB_GATE", 0, 1, m_dwCLubMapGate );

	DWORD dwNUM = cFILE.GetKeySize( "SCHOOL_WARS", "BATTLE_TIME" );
	if( dwNUM > MAX_TIME )
	{
		CDebugSet::ToLogFile( "ERROR : GLTowerWars::Load(), %s, It was wrong size of BATTLE_TIME", strFile.c_str() );
		return false;
	}

	for( DWORD i=0; i<dwNUM; ++i )
	{
		cFILE.getflag( i, "SCHOOL_WARS", "BATTLE_TIME", 0, 3, m_sTwTIME[i].dwWeekDay );
		cFILE.getflag( i, "SCHOOL_WARS", "BATTLE_TIME", 1, 3, m_sTwTIME[i].dwStartTime );
		cFILE.getflag( i, "SCHOOL_WARS", "BATTLE_TIME", 2, 3, m_sTwTIME[i].dwStartMin );
	}

	cFILE.getflag( "SCHOOL_WARS", "BATTLE_THE_TIME", 0, 1, m_dwBattleTime );
	cFILE.getflag( "SCHOOL_WARS", "BATTLE_LAST_TIME", 0, 1, m_dwBattleTimeNext );
	cFILE.getflag( "SCHOOL_WARS", "BATTLE_NEXT_TIME", 0, 1, m_dwNextTime );
	cFILE.getflag( "SCHOOL_WARS", "BATTLE_PREVIOUS_TIME", 0, 1, m_dwBattleTimePrevious );


	/*std::string AWARD_ITEM[10] = 
	{
		"AWARD_ITEM_1",
		"AWARD_ITEM_2",
		"AWARD_ITEM_3",
		"AWARD_ITEM_4",
		"AWARD_ITEM_5",
		"AWARD_ITEM_6",
		"AWARD_ITEM_7",
		"AWARD_ITEM_8",
		"AWARD_ITEM_9",
		"AWARD_ITEM_10",
	};
	for( int i=0;i<10;++i )
	{
		cFILE.getflag( "SCHOOL_WARS", AWARD_ITEM[i], 0, 2, m_sTwPAwardItem.nAwardItem[i].wMainID );
		cFILE.getflag( "SCHOOL_WARS", AWARD_ITEM[i], 1, 2, m_sTwPAwardItem.nAwardItem[i].wSubID );
	}*/

	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_1", 0, 2, m_sTwPAwardItem.nAwardItem[0].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_1", 1, 2, m_sTwPAwardItem.nAwardItem[0].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_2", 0, 2, m_sTwPAwardItem.nAwardItem[1].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_2", 1, 2, m_sTwPAwardItem.nAwardItem[1].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_3", 0, 2, m_sTwPAwardItem.nAwardItem[2].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_3", 1, 2, m_sTwPAwardItem.nAwardItem[2].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_4", 0, 2, m_sTwPAwardItem.nAwardItem[3].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_4", 1, 2, m_sTwPAwardItem.nAwardItem[3].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_5", 0, 2, m_sTwPAwardItem.nAwardItem[4].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_5", 1, 2, m_sTwPAwardItem.nAwardItem[4].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_6", 0, 2, m_sTwPAwardItem.nAwardItem[5].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_6", 1, 2, m_sTwPAwardItem.nAwardItem[5].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_7", 0, 2, m_sTwPAwardItem.nAwardItem[6].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_7", 1, 2, m_sTwPAwardItem.nAwardItem[6].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_8", 0, 2, m_sTwPAwardItem.nAwardItem[7].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_8", 1, 2, m_sTwPAwardItem.nAwardItem[7].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_9", 0, 2, m_sTwPAwardItem.nAwardItem[8].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_9", 1, 2, m_sTwPAwardItem.nAwardItem[8].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_10", 0, 2, m_sTwPAwardItem.nAwardItem[9].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_10", 1, 2, m_sTwPAwardItem.nAwardItem[9].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_11", 0, 2, m_sTwPAwardItem.nAwardItem[10].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_11", 1, 2, m_sTwPAwardItem.nAwardItem[10].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_12", 0, 2, m_sTwPAwardItem.nAwardItem[11].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_12", 1, 2, m_sTwPAwardItem.nAwardItem[11].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_13", 0, 2, m_sTwPAwardItem.nAwardItem[12].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_13", 1, 2, m_sTwPAwardItem.nAwardItem[12].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_14", 0, 2, m_sTwPAwardItem.nAwardItem[13].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_14", 1, 2, m_sTwPAwardItem.nAwardItem[13].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_15", 0, 2, m_sTwPAwardItem.nAwardItem[14].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_15", 1, 2, m_sTwPAwardItem.nAwardItem[14].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_16", 0, 2, m_sTwPAwardItem.nAwardItem[15].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_16", 1, 2, m_sTwPAwardItem.nAwardItem[15].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_17", 0, 2, m_sTwPAwardItem.nAwardItem[16].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_17", 1, 2, m_sTwPAwardItem.nAwardItem[16].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_18", 0, 2, m_sTwPAwardItem.nAwardItem[17].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_18", 1, 2, m_sTwPAwardItem.nAwardItem[17].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_19", 0, 2, m_sTwPAwardItem.nAwardItem[18].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_19", 1, 2, m_sTwPAwardItem.nAwardItem[18].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_20", 0, 2, m_sTwPAwardItem.nAwardItem[19].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_20", 1, 2, m_sTwPAwardItem.nAwardItem[19].wSubID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_ETCH", 0, 2, m_sTwPAwardItem.nAwardItem[20].wMainID );
	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_ETCH", 1, 2, m_sTwPAwardItem.nAwardItem[20].wSubID );

	cFILE.getflag( "SCHOOL_WARS", "AWARD_ITEM_LIMIT", 0, 1, m_sTwPAwardItem.dwAwardLimit );

	for ( int i=0; i < CTF_MAX_REVIVE_GATE; ++ i )
	{
		cFILE.getflag( "SCHOOL_WARS", "REVIVE_GATE", i, CTF_MAX_REVIVE_GATE, m_dwReviveGate[i] );
	}

	return true;
}
DWORD GLTowerWars::IsFirstStart ( int nDayOfWeek, int nHour )
{
	if ( IsBattle() )	return UINT_MAX;

	for ( DWORD i=0; i<MAX_TIME; ++i )
	{
	     m_dwBattleTimeNext = m_sTwTIME[i+2].dwStartTime;
		 m_dwBattleTimePrevious = m_sTwTIME[i].dwStartTime;
		 return i;
	}
	return UINT_MAX;
}
DWORD GLTowerWars::IsBattleWeekDay ( int nDayOfWeek, int nHour )
{
	if ( IsBattle() )	return UINT_MAX;

	for ( DWORD i=0; i<MAX_TIME; ++i )
	{
		if ( (nDayOfWeek==m_sTwTIME[i].dwWeekDay) && 
			 (nHour==m_sTwTIME[i].dwStartTime) &&
			 (m_dwLastBattleHour!=nHour) )
		{
		    m_dwBattleTimeNext = m_sTwTIME[i+1].dwStartTime;
		    m_dwBattleTimePrevious = m_sTwTIME[i].dwStartTime;
			return i;
		}
		else if ( (nDayOfWeek==m_sTwTIME[i].dwWeekDay) && 
			 (nHour==m_sTwTIME[i].dwStartTime-1) &&
			 (m_dwLastBattleHour!=nHour) )
		{
			return i;
		}
	}
	return UINT_MAX;
}

bool GLTowerWars::IsBattleHour ( DWORD dwORDER, int nHour )
{
	if ( dwORDER>=MAX_TIME )
	{
		return false;
	}
	
	if (m_sTwTIME[dwORDER].dwStartTime == nHour)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

bool GLTowerWars::IsBattleHourMin ( DWORD dwORDER, int nHour, int nMinute )
{
	if ( dwORDER>=MAX_TIME )
	{
		return false;
	}
	
	if (m_sTwTIME[dwORDER].dwStartTime == nHour && m_sTwTIME[dwORDER].dwStartMin == nMinute )
	{
		return true;
	}
	else
	{
		return false;
	}	
}

void GLTowerWars::UpdateBattleDay ( int nHour )
{
	m_dwLastBattleHour = nHour;
}

void GLTowerWars::UpdateNotifyBattle ( DWORD dwORDER, int nHour, int nMinute )
{
	if ( dwORDER>=MAX_TIME )	return;

	DWORD dwOTime = m_sTwTIME[dwORDER].dwStartTime;
	if ( dwOTime <= 0 )			return;
	
	DWORD dwOTimeMin = m_sTwTIME[dwORDER].dwStartMin;
	if( dwOTimeMin > 0 )
	{
		dwOTimeMin -= nMinute;
		if( dwOTimeMin == 30)
		{
			if ( !m_bNotifyHalfHour )
			{
				m_bNotifyHalfHour = true;

				GLMSG::SNET_TOWERWARS_START_BRD NetMsgBrd;
				NetMsgBrd.nTIME = 30;
				StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_TOWERWARS_START_BRD::TEXT_LEN, m_strName.c_str() );
				GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
			}
		}
		if ( dwOTimeMin == 5 )
		{
			if ( !m_bNotify10MinHour )
			{
				m_bNotify10MinHour = true;
				m_emBattleState = BATTLE_READY;

				GLMSG::SNET_TOWERWARS_START_BRD NetMsgBrd;
				NetMsgBrd.nTIME = 5;
				StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_TOWERWARS_START_BRD::TEXT_LEN, m_strName.c_str() );
				GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );

				GLMSG::SNET_TOWERWARS_READY_FLD NetMsgFld;
				NetMsgFld.dwID = m_dwID;
				GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );
			}
		}
	}
	else
	{
		dwOTime -= 1;
		if ( nHour >= dwOTime )
		{
			if ( !m_bNotifyOneHour )
			{
				m_bNotifyOneHour = true;

				GLMSG::SNET_TOWERWARS_START_BRD NetMsgBrd;
				NetMsgBrd.nTIME = 60-nMinute;
				StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_TOWERWARS_START_BRD::TEXT_LEN, m_strName.c_str() );
				GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
			}

			if ( nMinute == 30 )
			{
				if ( !m_bNotifyHalfHour )
				{
					m_bNotifyHalfHour = true;

					GLMSG::SNET_TOWERWARS_START_BRD NetMsgBrd;
					NetMsgBrd.nTIME = 30;
					StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_TOWERWARS_START_BRD::TEXT_LEN, m_strName.c_str() );
					GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
				}
			}

			if ( nMinute == 50 )
			{
				if ( !m_bNotify10MinHour )
				{
					m_bNotify10MinHour = true;
					m_emBattleState = BATTLE_READY;

					GLMSG::SNET_TOWERWARS_START_BRD NetMsgBrd;
					NetMsgBrd.nTIME = 10;
					StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_TOWERWARS_START_BRD::TEXT_LEN, m_strName.c_str() );
					GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );

					GLMSG::SNET_TOWERWARS_READY_FLD NetMsgFld;
					NetMsgFld.dwID = m_dwID;
					GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );
				}
			}
		}
	}
}

void GLTowerWars::DoBattleStart ( DWORD dwORDER, int nHour )
{
	m_emBattleState = BATTLE_START;
	m_dwBattleOrder = dwORDER;
	m_fRankingUpdate = 0.0f;
	m_emForceExit = FORCE_EXIT_NO;
	bBattleEnd = false;
	m_bKickOut = false;
	m_fKickTimer = 0.0f;
	m_fKickTotal = 0.0f;

	m_vecCtfAwardChar.clear();
	m_mapCtfScore.clear();
	m_mapTowerStatus.clear();

	UpdateBattleDay ( nHour );

	GLMSG::SNET_TOWERWARS_START_FLD NetMsgFld;
	NetMsgFld.dwID = m_dwID;
	GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );

	GLMSG::SNET_TOWERWARS_START_BRD NetMsgBrd;
	NetMsgBrd.nTIME = 0;
	StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_CLUB_BATTLE_START_BRD::TEXT_LEN, m_strName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );

	GLMSG::SNET_TOWERWARS_START_ENTRY NetMsgEntry;
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgEntry );
}

void GLTowerWars::DoBattleEnd( bool bForceOut )
{
	m_emBattleState = BATTLE_END;
	m_emForceExit = FORCE_EXIT_YES;
	m_dwBattleOrder = UINT_MAX;

	m_bNotifyOneHour = false;
	m_bNotifyHalfHour = false;
	m_bNotify10MinHour = false;
	m_fBattleTimer = 0.0f;
	m_fRankingUpdate = 0.0f;
	bBattleEnd = false;
	
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
		NetSwMsg.fEventRate	= 1.5f;
		NetSwMsg.dwEventType = i;
		GLAgentServer::GetInstance().SENDTOALLCHANNEL( &NetSwMsg );
	}
	
	GLMSG::SNET_TOWERWARS_END_FLD NetMsgFld;
	NetMsgFld.dwID = m_dwID;
	NetMsgFld.bForceExit = false;
	GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );

	GLMSG::SNET_TOWERWARS_END_BRD NetMsgBrd;
	StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_TOWERWARS_END_BRD::TEXT_LEN, m_strName.c_str() );
	StringCchCopy ( NetMsgBrd.szClubName, CHAR_SZNAME, strClubName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );

	/*GLTowerWars &sSW = *pSW;
	sCTF.m_wSchoolWinner = pNetMsg->wSCHOOL;
	GLMSG::SNET_TOWERWARS_WINNER_BRD NetMsgBrd2;
	NetMsgBrd2.wSCHOOL = sCTF.m_wSchoolWinner;
	StringCchCopy ( NetMsgBrd2.szName, GLMSG::SNET_CAPTURETHEFIELD_WINNER_BRD::TEXT_LEN, sCTF.m_strName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd2 );*/
	
	GLMSG::SNET_TOWERWARS_SETWINSCHOOL_BRD NetMsgBrd3;
	NetMsgBrd3.wSchool = (WORD) m_dwWinClub;
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd3 );
}

void GLTowerWars::CheckAwardClub( float fElaps )
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

bool GLTowerWars::IsEnterMap()
{
	if ( IsBattle() ) return true;

	return false;
}

DWORD GLTowerWars::GetReviveGate( WORD wSCHOOL )
{
	if ( wSCHOOL >= CTF_MAX_REVIVE_GATE )	return NULL; //return the fuck
	return m_dwReviveGate[wSCHOOL];
}

STWP_RANK_INFO* GLTowerWars::GetCTFRankInof( DWORD dwCharID )
{
	TWP_RANK_INFO_MAP_ITER pos = m_mapCtfScore.find( dwCharID );
	if( pos == m_mapCtfScore.end() )
	{
		return NULL;
	}
	
	return &(*pos).second;;
}

SSCHOOLWAR_TOWER_STATUS* GLTowerWars::GetTowerStatus( SNATIVEID sID )
{
	SCHOOLWAR_TOWER_STATUS_MAP_ITER pos = m_mapTowerStatus.find( sID.dwID );
	if( pos == m_mapTowerStatus.end() )	return NULL;

	return &(*pos).second;
}

SW_SCHOOL_DATA GLTowerWars::GetTowerSchool( SNATIVEID sID )
{
	SSCHOOLWAR_TOWER_STATUS* pSTATUS = GetTowerStatus( sID );
	if ( pSTATUS )
		return pSTATUS->emHOLDER;

	return SW_SCHOOL_MAX;
}

void GLTowerWars::AddSWPScore( DWORD dwKillChar, DWORD dwKillGaeaID, DWORD dwDeathChar, DWORD dwDeathGaeaID )
{
	STWP_RANK_INFO* pKillSwPRankInfo = GetCTFRankInof( dwKillChar );
	if ( pKillSwPRankInfo )
	{
		pKillSwPRankInfo->wKillNum++;
	}
	else
	{
		STWP_RANK_INFO sSwPRankInfo;		
		sSwPRankInfo.dwCharID = dwKillChar;
		sSwPRankInfo.dwGaeaID = dwKillGaeaID;
		sSwPRankInfo.wKillNum++;
		
		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar( dwKillGaeaID );
		if ( pChar )
		{
			StringCchCopy ( sSwPRankInfo.szCharName, CHAR_NAME+1, pChar->m_szName );
			sSwPRankInfo.szCharName[CHAR_NAME] = '\0';
			sSwPRankInfo.dwClass = CharClassToIndex(pChar->m_emClass);
			sSwPRankInfo.wSchool = pChar->m_wSchool;
		}	
	
		m_mapCtfScore[sSwPRankInfo.dwCharID] = sSwPRankInfo;
	}

	STWP_RANK_INFO* pDeathSwPRankInfo = GetCTFRankInof( dwDeathChar );
	if ( pDeathSwPRankInfo )
	{
		pDeathSwPRankInfo->wDeathNum++;
	}
	else
	{
		STWP_RANK_INFO sSwPRankInfo;		
		sSwPRankInfo.dwCharID = dwDeathChar;
		sSwPRankInfo.dwGaeaID = dwDeathGaeaID;
		sSwPRankInfo.wDeathNum++;

		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar( dwDeathGaeaID );
		if ( pChar )
		{
			StringCchCopy ( sSwPRankInfo.szCharName, CHAR_NAME+1, pChar->m_szName );
			sSwPRankInfo.szCharName[CHAR_NAME] = '\0';
			sSwPRankInfo.dwClass = CharClassToIndex(pChar->m_emClass);
			sSwPRankInfo.wSchool = pChar->m_wSchool;
		}
		m_mapCtfScore[sSwPRankInfo.dwCharID] = sSwPRankInfo;
	}
}

void GLTowerWars::AddSWPDamageScore( DWORD dwGaeaID, DWORD dwDamage )
{
	PGLCHAR pCharAttacker = GLGaeaServer::GetInstance().GetChar( dwGaeaID );

	STWP_RANK_INFO* pAttackerSwRankInfo = GetCTFRankInof( pCharAttacker->m_dwCharID );
	if ( pAttackerSwRankInfo && pCharAttacker )
	{
		pAttackerSwRankInfo->dwDamageNum += dwDamage;
	}
	else if ( pCharAttacker )
	{
		STWP_RANK_INFO sSwRankInfo;		
		sSwRankInfo.dwCharID = pCharAttacker->m_dwCharID;
		sSwRankInfo.dwGaeaID = dwGaeaID;
		sSwRankInfo.dwDamageNum += dwDamage;
		StringCchCopy ( sSwRankInfo.szCharName, CHAR_NAME+1, pCharAttacker->m_szName );
		sSwRankInfo.szCharName[CHAR_NAME] = '\0';
		sSwRankInfo.dwClass = CharClassToIndex(pCharAttacker->m_emClass);
		sSwRankInfo.wSchool = pCharAttacker->m_wSchool;

		m_mapCtfScore[sSwRankInfo.dwCharID] = sSwRankInfo;
	}		
}

void GLTowerWars::AddSWPHealScore( DWORD dwGaeaID, DWORD dwDeathGaeaID, DWORD dwHeal )
{
	PGLCHAR pCharAttacker = GLGaeaServer::GetInstance().GetChar( dwGaeaID );
	PGLCHAR pCharDeath = GLGaeaServer::GetInstance().GetChar( dwDeathGaeaID );

	STWP_RANK_INFO* pAttackerSwRankInfo = GetCTFRankInof( pCharAttacker->m_dwCharID );
	if ( pAttackerSwRankInfo && pCharAttacker )
	{
		pAttackerSwRankInfo->dwHealNum += dwHeal;
	}
	else if ( pCharAttacker )
	{
		STWP_RANK_INFO sSwRankInfo;		
		sSwRankInfo.dwCharID = pCharAttacker->m_dwCharID;
		sSwRankInfo.dwGaeaID = dwGaeaID;
		sSwRankInfo.dwHealNum += dwHeal;
		StringCchCopy ( sSwRankInfo.szCharName, CHAR_NAME+1, pCharAttacker->m_szName );
		sSwRankInfo.szCharName[CHAR_NAME] = '\0';
		sSwRankInfo.dwClass = CharClassToIndex(pCharAttacker->m_emClass);
		sSwRankInfo.wSchool = pCharAttacker->m_wSchool;

		m_mapCtfScore[sSwRankInfo.dwCharID] = sSwRankInfo;
	}	

	STWP_RANK_INFO* pDeathSwRankInfo = GetCTFRankInof( pCharDeath->m_dwCharID );
	if ( pDeathSwRankInfo && pCharDeath )
	{
		pDeathSwRankInfo->dwHealNum += 0;
	}
	else if ( pCharDeath )
	{
		STWP_RANK_INFO sSwRankInfo;		
		sSwRankInfo.dwCharID = pCharDeath->m_dwCharID;
		sSwRankInfo.dwGaeaID = dwDeathGaeaID;
		sSwRankInfo.dwHealNum += 0;
		StringCchCopy ( sSwRankInfo.szCharName, CHAR_NAME+1, pCharDeath->m_szName );
		sSwRankInfo.szCharName[CHAR_NAME] = '\0';
		sSwRankInfo.dwClass = CharClassToIndex(pCharDeath->m_emClass);
		sSwRankInfo.wSchool = pCharDeath->m_wSchool;

		m_mapCtfScore[sSwRankInfo.dwCharID] = sSwRankInfo;
	}		
}

void GLTowerWars::AddSWPResuScore( DWORD dwGaeaID, DWORD dwDeathGaeaID )
{
	PGLCHAR pCharAttacker = GLGaeaServer::GetInstance().GetChar( dwGaeaID );
	PGLCHAR pCharDeath = GLGaeaServer::GetInstance().GetChar( dwDeathGaeaID );

	STWP_RANK_INFO* pAttackerSwRankInfo = GetCTFRankInof( pCharAttacker->m_dwCharID );
	if ( pAttackerSwRankInfo && pCharAttacker )
	{
		pAttackerSwRankInfo->wResuNum += 1;
	}
	else if ( pCharAttacker )
	{
		STWP_RANK_INFO sSwRankInfo;		
		sSwRankInfo.dwCharID = pCharAttacker->m_dwCharID;
		sSwRankInfo.dwGaeaID = dwGaeaID;
		sSwRankInfo.wResuNum += 1;
		StringCchCopy ( sSwRankInfo.szCharName, CHAR_NAME+1, pCharAttacker->m_szName );
		sSwRankInfo.szCharName[CHAR_NAME] = '\0';
		sSwRankInfo.dwClass = CharClassToIndex(pCharAttacker->m_emClass);
		sSwRankInfo.wSchool = pCharAttacker->m_wSchool;

		m_mapCtfScore[sSwRankInfo.dwCharID] = sSwRankInfo;
	}	

	STWP_RANK_INFO* pDeathSwRankInfo = GetCTFRankInof( pCharDeath->m_dwCharID );
	if ( pDeathSwRankInfo && pCharDeath )
	{
		pDeathSwRankInfo->wResuNum += 0;
	}
	else if ( pCharDeath )
	{
		STWP_RANK_INFO sSwRankInfo;		
		sSwRankInfo.dwCharID = pCharDeath->m_dwCharID;
		sSwRankInfo.dwGaeaID = dwDeathGaeaID;
		sSwRankInfo.wResuNum += 0;
		StringCchCopy ( sSwRankInfo.szCharName, CHAR_NAME+1, pCharDeath->m_szName );
		sSwRankInfo.szCharName[CHAR_NAME] = '\0';
		sSwRankInfo.dwClass = CharClassToIndex(pCharDeath->m_emClass);
		sSwRankInfo.wSchool = pCharDeath->m_wSchool;

		m_mapCtfScore[sSwRankInfo.dwCharID] = sSwRankInfo;
	}
}

BOOL GLTowerWars::AddTower( DWORD dwCHARID, SNATIVEID sID, SW_SCHOOL_DATA emHolder )
{
	BOOL bCAPTURED = FALSE;

	if ( !IsBattle() )	return bCAPTURED;

	PGLCHAR pCHAR = GLGaeaServer::GetInstance().GetCharID( dwCHARID );
	if ( pCHAR )
	{
		SCROWDATA* pCROW = GLCrowDataMan::GetInstance().GetCrowData( sID );
		if ( pCROW )
		{
			SSCHOOLWAR_TOWER_STATUS* pTOWER = GetTowerStatus( sID );
			if ( pTOWER )
			{
				//if tower already exist then we just needed to update the holder
				if ( pTOWER->sCROWID == sID )
				{
					pTOWER->emHOLDER = emHolder;

					if ( pTOWER->emHOLDER != pTOWER->emHOLDER_OLD )
					{
						//if tower holder changes then tell the clients about it
						pTOWER->emHOLDER_OLD = pTOWER->emHOLDER;
						bCAPTURED = TRUE;

						GLMSG::SNETPC_SERVER_TOWERWARS_CAPTURE_AG NetMsgAgentCapture;
						NetMsgAgentCapture.dwID = m_dwID;
						NetMsgAgentCapture.emHOLDER = pTOWER->emHOLDER;
						NetMsgAgentCapture.sID = pCROW->m_sBasic.sNativeID;
						StringCchCopy ( NetMsgAgentCapture.szName, GLMSG::SNETPC_SERVER_TOWERWARS_CAPTURE_AG::TEXT_LEN, pCHAR->m_szName );
						StringCchCopy ( NetMsgAgentCapture.szNameCrow, GLMSG::SNETPC_SERVER_TOWERWARS_CAPTURE_AG::TEXT_LEN, pCROW->GetName() );
						GLGaeaServer::GetInstance().SENDTOAGENT( &NetMsgAgentCapture );
					}
				}
			}else{
				SSCHOOLWAR_TOWER_STATUS sTOWER;
				sTOWER.sCROWID = sID;
				sTOWER.emHOLDER = emHolder;
				sTOWER.emHOLDER_OLD = emHolder;
				m_mapTowerStatus[sTOWER.sCROWID.dwID] = sTOWER;

				bCAPTURED = TRUE;
				//new tower capture tell the clients about it
				//then fuck all the clients

				GLMSG::SNETPC_SERVER_TOWERWARS_CAPTURE_AG NetMsgAgentCapture;
				NetMsgAgentCapture.dwID = m_dwID;
				NetMsgAgentCapture.emHOLDER = sTOWER.emHOLDER;
				NetMsgAgentCapture.sID = pCROW->m_sBasic.sNativeID;
				StringCchCopy ( NetMsgAgentCapture.szName, GLMSG::SNETPC_SERVER_TOWERWARS_CAPTURE_AG::TEXT_LEN, pCHAR->m_szName );
				StringCchCopy ( NetMsgAgentCapture.szNameCrow, GLMSG::SNETPC_SERVER_TOWERWARS_CAPTURE_AG::TEXT_LEN, pCROW->GetName() );
				GLGaeaServer::GetInstance().SENDTOAGENT( &NetMsgAgentCapture );
			}


			//check capture here
			int nSCORE[SW_SCHOOL_MAX] = { 0, 0, 0 };

			SCHOOLWAR_TOWER_STATUS_MAP_ITER	pos = m_mapTowerStatus.begin();
			SCHOOLWAR_TOWER_STATUS_MAP_ITER	end = m_mapTowerStatus.end();
			for ( ; pos != end; pos++ )
			{
				const SSCHOOLWAR_TOWER_STATUS&	sTOWER = pos->second;
				if ( sTOWER.emHOLDER >= SW_SCHOOL_MAX )	continue;
				nSCORE[sTOWER.emHOLDER] ++;
			}

			for( int i=0; i < SW_SCHOOL_MAX; ++ i )
			{
				if ( nSCORE[i] >= 3 )
				{
					GLMSG::SNET_TOWERWARS_DOBATTLEEND_AGT NetMsgAgentReqEnd;
					NetMsgAgentReqEnd.dwID = m_dwID;
					NetMsgAgentReqEnd.dwSCHOOL = i;
					NetMsgAgentReqEnd.bEnd = true;
					GLGaeaServer::GetInstance().SENDTOAGENT( &NetMsgAgentReqEnd );


					GLMSG::SNETPC_SERVER_TOWERWARS_WINNER_AG NetMsgAgentWinner;
					NetMsgAgentWinner.dwID = m_dwID;
					NetMsgAgentWinner.wSCHOOL = i;
					GLGaeaServer::GetInstance().SENDTOAGENT ( &NetMsgAgentWinner );
				}
			}

			for( int i=0; i < SW_SCHOOL_MAX; ++ i )
			{
				if ( nSCORE[i] >= 2 )
				{
					GLMSG::SNET_TOWERWARS_LASTCAPTURE_AGT NetMsgAgentReqLastCapture;
					NetMsgAgentReqLastCapture.dwID = m_dwID;
					NetMsgAgentReqLastCapture.dwSCHOOL = i;
					NetMsgAgentReqLastCapture.bLastCapture = true;
					GLGaeaServer::GetInstance().SENDTOAGENT( &NetMsgAgentReqLastCapture );
				}
			}
		}
	}

	return bCAPTURED;
}

bool GLTowerWars::ChangeSWSchoolID ( DWORD dwSwID )
{
	m_dwWinClub = dwSwID;

	CSetSwRegion *pDbAction = new CSetSwRegion ( m_dwID, m_dwWinClub );
	GLAgentServer::GetInstance().GetDBMan()->AddJob ( pDbAction );

	return true;
}

bool GLTowerWars::EndBattle( WORD wSchool, bool bEnd )
{
	bBattleEnd = bEnd;

	return true;
}

bool GLTowerWarsMan::Load ( std::vector<std::string> &vecFiles )
{
	std::vector<std::string>::size_type i = 0, j = vecFiles.size();
	for( ; i < j; ++i )
	{
		GLTowerWars sSchoolWAR;
		bool bOK = sSchoolWAR.Load( vecFiles[i] );
		if( !bOK )
		{
			CDebugSet::ToLogFile ( "sTowerWars.Load() fail, %s", vecFiles[i].c_str() );
		}

		m_vecSchoolWAR.push_back ( sSchoolWAR );
	}

	std::sort( m_vecSchoolWAR.begin(), m_vecSchoolWAR.end() );

	return true;
}

GLTowerWars* GLTowerWarsMan::Find ( DWORD dwID )
{
	GLTowerWars cObj;
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

bool GLTowerWarsMan::SetState ( VECTWID_DB &vecTWID )
{
	for ( VECTWID_DB::size_type i=0; i<vecTWID.size(); ++i )
	{
		const GLTWID &sTWID = vecTWID[i];
		
		GLTowerWars* pTwid = Find ( sTWID.m_dwID );
		if ( !pTwid )
		{			
			TCHAR szTemp[128] = {0};
			_snprintf( szTemp, 128, "GLTowerWars::Find() fail, %u", sTWID.m_dwID );

			MessageBox ( NULL, szTemp, "ERROR", MB_OK );
			continue;
		}

		pTwid->m_dwWinClub = sTWID.m_dwTWID;
	}

	return true;
}

bool GLTowerWarsMan::IsBattle ()
{
	for ( SW_VEC::size_type i=0; i<m_vecSchoolWAR.size(); ++i )
	{
		GLTowerWars &sSchoolWAR = m_vecSchoolWAR[i];
	
		if ( sSchoolWAR.IsBattle() )		return true;
	}

	return false;
}

