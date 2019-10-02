#include "StdAfx.h"

#include <algorithm>
//#include <strstream>
#include "GLDefine.h"
#include "gltexfile.h"
#include "IniLoader.h"
//#include "GLOGIC.h"
#include "GLSchoolWar.h"

//#include "dbactionlogic.h"
#include "GLLandMan.h"
#include "GLGaeaServer.h"
#include "GLAgentServer.h"
//#include "GLChar.h"
//#include "GLCrow.h"

#include "GLCharClient.h"
#include "GLGaeaClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GLSchoolWar::GLSchoolWar () :
	m_dwID(UINT_MAX),
	
	m_dwClubMap(0),
	m_dwCLubMapGate(0),
	m_dwClubHallMap(0),
	m_dwClubHallGate(0),

//	m_fItemDropRate(0),
//	m_fDefaultCommissionPer(5),

	m_dwWinChar(GAEAID_NULL),
//	m_fCommissionPercent(0.0f),

	m_dwBattleTime(3600),

//	m_bNewCommission(false),
//	m_fCommissionTimer(0.0f),
//	m_fNewCommissionPercent(0.0f),

	m_bNotifyOneHour(false),
	m_bNotifyHalfHour(false),
	m_bNotify10MinHour(false),
	
	m_emBattleState(BATTLE_NOSTART),
	m_dwBattleOrder(0),
	m_dwLastBattleHour(0),
	m_fBattleTimer(0.0f),

//	m_dwCERTIFY_CHARID(0),
//	m_dwCERTIFY_NPCID(0),
//	m_fCERTIFY_TIMER(0),
//	m_vCERTIFY_POS(0,0,0),

	m_fCHECK_TIMER(0.0f),
	m_fCHECK_TIME(0.0f),
	m_fRankingUpdate(0.0f)
{
}

GLSchoolWar& GLSchoolWar::operator= ( const GLSchoolWar& value )
{
	m_dwID = value.m_dwID;
	m_strName = value.m_strName;
//	m_vecMaps = value.m_vecMaps;

	m_dwClubMap = value.m_dwClubMap;
	m_dwCLubMapGate = value.m_dwCLubMapGate;
	m_dwClubHallMap = value.m_dwClubHallMap;
	m_dwClubHallGate = value.m_dwClubHallGate;

	m_dwBattleTime = value.m_dwBattleTime;

	for ( int i=0; i<MAX_TIME; ++i )
		m_sDWTime[i] = value.m_sDWTime[i];


	m_sDWAwardItem = value.m_sDWAwardItem;

//	m_fItemDropRate = value.m_fItemDropRate;
//	m_fDefaultCommissionPer = value.m_fDefaultCommissionPer;

	m_dwWinChar = value.m_dwWinChar;
//	m_fCommissionPercent = value.m_fCommissionPercent;

//	m_bNewCommission = value.m_bNewCommission;
//	m_fCommissionTimer = value.m_fCommissionTimer;
//	m_fNewCommissionPercent = value.m_fNewCommissionPercent;

	m_bNotifyOneHour = value.m_bNotifyOneHour;
	m_bNotifyHalfHour = value.m_bNotifyHalfHour;
	m_bNotify10MinHour = value.m_bNotify10MinHour;

	m_emBattleState = value.m_emBattleState;
	m_dwLastBattleHour = value.m_dwLastBattleHour;
	m_fBattleTimer = value.m_fBattleTimer;

//	m_dwCERTIFY_CHARID = value.m_dwCERTIFY_CHARID;
//	m_dwCERTIFY_NPCID = value.m_dwCERTIFY_NPCID;
//	m_fCERTIFY_TIMER = value.m_fCERTIFY_TIMER;
//	m_vCERTIFY_POS = value.m_vCERTIFY_POS;

//	m_bBattleEndCheck = value.m_bBattleEndCheck;
	m_fCHECK_TIMER = value.m_fCHECK_TIMER;
	m_fCHECK_TIME = value.m_fCHECK_TIME;

	m_vecDWAwardChar = value.m_vecDWAwardChar;

	m_fRankingUpdate = value.m_fRankingUpdate;

	return *this;
}

bool GLSchoolWar::Load ( std::string strFile )
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
		CDebugSet::ToLogFile ( "ERROR : GLSchoolWar::Load(), File Open %s", strFile.c_str() );
		return false;
	}
	
	cFILE.getflag( "DOMI_WARS", "ID", 0, 1, m_dwID );
	cFILE.getflag( "DOMI_WARS", "NAME", 0, 1, m_strName );

	SNATIVEID nidMAP;
	cFILE.getflag( "DOMI_WARS", "CLUB_MAP", 0, 2, nidMAP.wMainID );
	cFILE.getflag( "DOMI_WARS", "CLUB_MAP", 1, 2, nidMAP.wSubID );
	m_dwClubMap = nidMAP.dwID;

	cFILE.getflag( "DOMI_WARS", "CLUB_GATE", 0, 1, m_dwCLubMapGate );

	cFILE.getflag( "DOMI_WARS", "CLUB_HALL_MAP", 0, 2, nidMAP.wMainID );
	cFILE.getflag( "DOMI_WARS", "CLUB_HALL_MAP", 1, 2, nidMAP.wSubID );
	m_dwClubHallMap = nidMAP.dwID;

	cFILE.getflag( "DOMI_WARS", "CLUB_HALL_GATE", 0, 1, m_dwClubHallGate );

	DWORD dwNUM = cFILE.GetKeySize( "DOMI_WARS", "BATTLE_TIME" );
	if( dwNUM > MAX_TIME )
	{
		CDebugSet::ToLogFile( "ERROR : GLSchoolWar::Load(), %s, It was wrong size of BATTLE_TIME", strFile.c_str() );
		return false;
	}

	for( DWORD i=0; i<dwNUM; ++i )
	{
		cFILE.getflag( i, "DOMI_WARS", "BATTLE_TIME", 0, 2, m_sDWTime[i].dwWeekDay );
		cFILE.getflag( i, "DOMI_WARS", "BATTLE_TIME", 1, 2, m_sDWTime[i].dwStartTime );
	}

	cFILE.getflag( "DOMI_WARS", "BATTLE_THE_TIME", 0, 1, m_dwBattleTime );

	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_1", 0, 2, m_sDWAwardItem.nAwardItem[0].wMainID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_1", 1, 2, m_sDWAwardItem.nAwardItem[0].wSubID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_2", 0, 2, m_sDWAwardItem.nAwardItem[1].wMainID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_2", 1, 2, m_sDWAwardItem.nAwardItem[1].wSubID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_3", 0, 2, m_sDWAwardItem.nAwardItem[2].wMainID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_3", 1, 2, m_sDWAwardItem.nAwardItem[2].wSubID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_4", 0, 2, m_sDWAwardItem.nAwardItem[3].wMainID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_4", 1, 2, m_sDWAwardItem.nAwardItem[3].wSubID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_5", 0, 2, m_sDWAwardItem.nAwardItem[4].wMainID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_5", 1, 2, m_sDWAwardItem.nAwardItem[4].wSubID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_6", 0, 2, m_sDWAwardItem.nAwardItem[5].wMainID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_6", 1, 2, m_sDWAwardItem.nAwardItem[5].wSubID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_7", 0, 2, m_sDWAwardItem.nAwardItem[6].wMainID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_7", 1, 2, m_sDWAwardItem.nAwardItem[6].wSubID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_8", 0, 2, m_sDWAwardItem.nAwardItem[7].wMainID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_8", 1, 2, m_sDWAwardItem.nAwardItem[7].wSubID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_9", 0, 2, m_sDWAwardItem.nAwardItem[8].wMainID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_9", 1, 2, m_sDWAwardItem.nAwardItem[8].wSubID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_10", 0, 2, m_sDWAwardItem.nAwardItem[9].wMainID );
	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_10", 1, 2, m_sDWAwardItem.nAwardItem[9].wSubID );

	cFILE.getflag( "DOMI_WARS", "AWARD_ITEM_LIMIT", 0, 1, m_sDWAwardItem.dwAwardLimit );
	return true;
}

DWORD GLSchoolWar::IsBattleWeekDay ( int nDayOfWeek, int nHour )
{
	if ( IsBattle() )	return UINT_MAX;

	//	Note : 결정전이 있는 날인지 검사. 결정전이 오늘 있었는지 검사.
	for ( DWORD i=0; i<MAX_TIME; ++i )
	{
		if ( (nDayOfWeek==m_sDWTime[i].dwWeekDay) && 
			 (nHour==m_sDWTime[i].dwStartTime) &&
			 (m_dwLastBattleHour!=nHour) )
		{
			return i;
		}
	}
	return UINT_MAX;
}

// 선도클럽 시작시간인가?
bool GLSchoolWar::IsBattleHour ( DWORD dwORDER, int nHour )
{
	// 선도클럽 결정전은 날짜가 다른 요일 총 4번이 가능하다.
	if ( dwORDER>=MAX_TIME )
	{
		return false;
	}
	
	if (m_sDWTime[dwORDER].dwStartTime == nHour)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

// 최종적으로 선도클럽결정전이 일어난 날을 세팅한다.
// 하루에 두번 일어나지 않기 위해서이다.
void GLSchoolWar::UpdateBattleDay ( int nHour )
{
	m_dwLastBattleHour = nHour;
}

// 선도클럽 결정전 남은 시간을 클라이언트에게 알린다.
void GLSchoolWar::UpdateNotifyBattle ( DWORD dwORDER, int nHour, int nMinute )
{
	if ( dwORDER>=MAX_TIME )	return;

	DWORD dwOTime = m_sDWTime[dwORDER].dwStartTime;
	if ( dwOTime <= 0 )			return;
	
	dwOTime -= 1;
	if ( nHour == dwOTime )
	{
		//	Note : 
		if ( !m_bNotifyOneHour )
		{
			m_bNotifyOneHour = true;

			//	Note : 모든 클라이언트에 알림.
			GLMSG::SNET_SCHOOL_WAR_START_BRD NetMsgBrd;
			NetMsgBrd.nTIME = 60-nMinute;
			StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_SCHOOL_WAR_START_BRD::TEXT_LEN, m_strName.c_str() );
			GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
		}

		if ( nMinute == 30 )
		{
			if ( !m_bNotifyHalfHour )
			{
				m_bNotifyHalfHour = true;

				//	Note : 모든 클라이언트에 알림.
				GLMSG::SNET_SCHOOL_WAR_START_BRD NetMsgBrd;
				NetMsgBrd.nTIME = 30;
				StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_SCHOOL_WAR_START_BRD::TEXT_LEN, m_strName.c_str() );
				GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
			}
		}

		if ( nMinute == 50 )
		{
			if ( !m_bNotify10MinHour )
			{
				m_bNotify10MinHour = true;
				m_emBattleState = BATTLE_READY;

				//	Note : 모든 클라이언트에 알림.
				GLMSG::SNET_SCHOOL_WAR_START_BRD NetMsgBrd;
				NetMsgBrd.nTIME = 10;
				StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_SCHOOL_WAR_START_BRD::TEXT_LEN, m_strName.c_str() );
				GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );

				GLMSG::SNET_SCHOOL_WAR_READY_FLD NetMsgFld;
				NetMsgFld.dwID = m_dwID;
				GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );
			}
		}
	}

}

// 선도클럽 결정전을 시작한다.
void GLSchoolWar::DoBattleStart ( DWORD dwORDER, int nHour )
{
	//	Note : 결정전을 시작시킴.
	m_emBattleState = BATTLE_START;
	m_dwBattleOrder = dwORDER;
	m_fRankingUpdate = 0.0f;
	m_vecDWAwardChar.clear();
	m_mapDWScore.clear();
	//m_mapDWSchoolScore.clear();

	UpdateBattleDay ( nHour );

/*
	//	Note : 선도 클럽 변경을 필드서버에 알림.
	//
	GLMSG::SNET_CLUB_CERTIFIED_FLD NetMsgGuidFld;
	NetMsgGuidFld.dwID = m_dwID;
	NetMsgGuidFld.dwCLUBID = m_dwGuidanceClub;
	GLAgentServer::GetInstance().SENDTOALLCHANNEL ( &NetMsgGuidFld );

	//	Note : 수수료 변경 필드에 알림.
	GLMSG::SNET_CLUB_GUID_COMMISSION_FLD NetMsgCommissionFld;
	NetMsgCommissionFld.dwID = m_dwID;
	NetMsgCommissionFld.fCommission = m_fCommissionPercent;
	GLAgentServer::GetInstance().SENDTOALLCHANNEL ( &NetMsgCommissionFld );

	//	Note : 클라이언트들에게 알림.
	GLMSG::SNET_CLUB_GUID_COMMISSION_BRD NetMsgCmBrd;
	NetMsgCmBrd.fCommission = m_fCommissionPercent;

	std::vector<DWORD>::size_type nSize = m_vecMaps.size();
	for ( std::vector<DWORD>::size_type i=0; i<nSize; ++i )
	{
		SNATIVEID nidMAP = (m_vecMaps[i]);
		GLAGLandMan *pLand = GLAgentServer::GetInstance().GetByMapID ( nidMAP );
		if ( !pLand )	continue;

		pLand->SENDTOALLCLIENT ( &NetMsgCmBrd );
	}
*/
	//	Note : 전투 시작을 알림.
	GLMSG::SNET_SCHOOL_WAR_START_FLD NetMsgFld;
	NetMsgFld.dwID = m_dwID;
	GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );

	//	Note : 모든 클라이언트에 알림.
	GLMSG::SNET_SCHOOL_WAR_START_BRD NetMsgBrd;
	NetMsgBrd.nTIME = 0;
	StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_CLUB_BATTLE_START_BRD::TEXT_LEN, m_strName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );

}

void GLSchoolWar::DoBattleEnd()
{
	//	Note : 결정전이 종료.
	m_emBattleState = BATTLE_END;
	m_dwBattleOrder = UINT_MAX;

	m_bNotifyOneHour = false;
	m_bNotifyHalfHour = false;
	m_bNotify10MinHour = false;
	m_fBattleTimer = 0.0f;
	m_fRankingUpdate = 0.0f;


	//	Note : 결정전 종료를 알림.
	//
	//GLCLUB *pCLUB = GLAgentServer::GetInstance().GetClubMan().GetClub(m_dwWinChar);

	//std::string strClubName;
	//if ( pCLUB )	strClubName = pCLUB->m_szName;

	PGLCHARCLIENT pChar = GLGaeaClient::GetInstance().GetChar( m_dwWinChar );
	std::string strPlayerName;
	if ( pChar ) strPlayerName = pChar->m_szName;

	//	Note : 전투 종료를 알림.
	GLMSG::SNET_SCHOOL_WAR_END_FLD NetMsgFld;
	NetMsgFld.dwID = m_dwID;
	GLAgentServer::GetInstance().SENDTOCHANNEL ( &NetMsgFld, 0 );

	//	Note : 전투 결과를 알려줌 ( 해당 맵에 있는 유저들에게만 ) 

	GLMSG::SNET_SCHOOL_WAR_END_BRD NetMsgBrd;
	StringCchCopy ( NetMsgBrd.szName, GLMSG::SNET_SCHOOL_WAR_END_BRD::TEXT_LEN, m_strName.c_str() );
	StringCchCopy ( NetMsgBrd.szPlayerName, CHAR_SZNAME, strPlayerName.c_str() );
	GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
}

/*   
void GLSchoolWar::CheckExtraClub ( float fElaps )
{
	m_fCHECK_TIMER += fElaps;
	if ( m_fCHECK_TIMER > m_fCHECK_TIME )
	{
		if ( m_fCHECK_TIME >= 30.0f )
		{
			m_bBattleEndCheck = false;
			m_fCHECK_TIMER = 0.0f;
		}

		//	보상 지급
		{

		}

		GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( m_dwClubMap );
		if ( pLandMan )
		{
//			pLandMan->DoGateOutPCAll ( m_dwCLubMapGate );
		}
		m_fCHECK_TIME += 10.0f;
	}
}
*/

void GLSchoolWar::CheckAwardClub( float fElaps )
{
	m_fCHECK_TIMER += fElaps;
	if ( m_fCHECK_TIMER > m_fCHECK_TIME )
	{
		//	30초 동안은 보상지급
		if ( m_fCHECK_TIME < 30.0f )
		{
			//보상 지급
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

bool GLSchoolWar::IsEnterMap()
{
	if ( IsBattle() ) return true;
	if ( IsBattleReady() ) return true;

	return false;
}

SDW_RANK_INFO* GLSchoolWar::GetDWRankInof( DWORD dwCharID )
{
	DW_RANK_INFO_MAP_ITER pos = m_mapDWScore.find( dwCharID );
	if( pos == m_mapDWScore.end() )
	{
		return NULL;
	}
	
	return &(*pos).second;;
}

void GLSchoolWar::AddDWScore( DWORD dwKillChar, DWORD dwDeathChar )
{
	SDW_RANK_INFO* pKillDWRankInfo = GetDWRankInof( dwKillChar );
	if ( pKillDWRankInfo )
	{
		pKillDWRankInfo->wKillNum++;
	}
	else
	{

		SDW_RANK_INFO sDWRankInfo;		
		sDWRankInfo.dwCharID = dwKillChar;
		sDWRankInfo.wKillNum++;

		PGLCHAR pChar = GLGaeaServer::GetInstance().GetCharID( dwKillChar );
		if ( pChar )
		{
			StringCchCopy ( sDWRankInfo.szPlayerName, PLAYER_NAME+1, pChar->m_szName );
			sDWRankInfo.szPlayerName[PLAYER_NAME] = '\0';
		}	
	
		m_mapDWScore[sDWRankInfo.dwCharID] = sDWRankInfo;
	}

	SDW_RANK_INFO* pDeathDWRankInfo = GetDWRankInof( dwDeathChar );
	if ( pDeathDWRankInfo )
	{
		pDeathDWRankInfo->wDeathNum++;
	}
	else
	{
		
		SDW_RANK_INFO sDWRankInfo;		
		sDWRankInfo.dwCharID = dwDeathChar;
		sDWRankInfo.wDeathNum++;

		PGLCHAR pChar = GLGaeaServer::GetInstance().GetCharID( dwDeathChar );
		if ( pChar )
		{
			StringCchCopy ( sDWRankInfo.szPlayerName, PLAYER_NAME+1, pChar->m_szName );
			sDWRankInfo.szPlayerName[PLAYER_NAME] = '\0';
		}
		
	
		m_mapDWScore[sDWRankInfo.dwCharID] = sDWRankInfo;
	}
}

bool GLSchoolWarMan::Load ( std::vector<std::string> &vecFiles )
{
	std::vector<std::string>::size_type i = 0, j = vecFiles.size();
	for( ; i < j; ++i )
	{
		GLSchoolWar sDW;
		bool bOK = sDW.Load( vecFiles[i] );
		if( !bOK )
		{
			CDebugSet::ToLogFile ( "sSchoolWar.Load() fail, %s", vecFiles[i].c_str() );
		}

		m_vecDW.push_back ( sDW );
	}

	std::sort( m_vecDW.begin(), m_vecDW.end() );

	return true;
}

GLSchoolWar* GLSchoolWarMan::Find ( DWORD dwID )
{
	GLSchoolWar cObj;
	cObj.m_dwID = dwID;

	DW_VEC_ITER pos = std::lower_bound ( m_vecDW.begin(), m_vecDW.end(), cObj );
	if ( pos==m_vecDW.end() )
	{
		return NULL;
	}
	else
	{
		return &(*pos);
	}
}

bool GLSchoolWarMan::IsBattle ()
{
	for ( DW_VEC::size_type i=0; i<m_vecDW.size(); ++i )
	{
		GLSchoolWar &sDW = m_vecDW[i];
	
		if ( sDW.IsBattle() )		return true;
	}

	return false;
}

GLSchoolWarAgentMan& GLSchoolWarAgentMan::GetInstance()
{
	static GLSchoolWarAgentMan cInstance;
	return cInstance;
}

bool GLSchoolWarAgentMan::SetMapState ()
{
	
	for ( DW_VEC::size_type i=0; i<m_vecDW.size(); ++i )
	{
		GLSchoolWar &sDW= m_vecDW[i];

		//	Note : 선도 클럽 전투 입구존.
		SNATIVEID nidHallMAP ( sDW.m_dwClubHallMap );
		GLAGLandMan *pLandMan = GLAgentServer::GetInstance().GetByMapID ( nidHallMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwClubMapID = sDW.m_dwID;
		}

		//	Note : 선도 클럽 전투존.
		SNATIVEID nidMAP ( sDW.m_dwClubMap );
		pLandMan = GLAgentServer::GetInstance().GetByMapID ( nidMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwClubMapID = sDW.m_dwID;
			pLandMan->m_bDomiWarsMap = true;
		}
	}

	return true;
}

/*
bool GLGuidanceAgentMan::ChangeGuidClub ( DWORD dwID, DWORD dwClubID )
{
	GLGuidance *pGuid = Find ( dwID );
	if ( !pGuid )				return false;

	pGuid->ChangeGuidClub ( dwClubID );

	return true;
}

bool GLGuidanceAgentMan::ChangeCommission ( DWORD dwID, float fRate )
{
	GLGuidance *pGuid = Find ( dwID );
	if ( !pGuid )				return false;

	pGuid->ChangeCommission ( fRate );

	return true;
}
*/

bool GLSchoolWarAgentMan::FrameMove ( float fElapsedAppTime )
{
	// 선도전을 시작하지 않는다.
	if ( GLCONST_CHAR::bPKLESS ) return false;

	for ( DW_VEC::size_type i=0; i<m_vecDW.size(); ++i )
	{
		GLSchoolWar &sDW = m_vecDW[i];

		CTime cCurTime = CTime::GetCurrentTime();
		int nDayOfWeek = cCurTime.GetDayOfWeek ();
		int nDay = cCurTime.GetDay ();
		int nHour = cCurTime.GetHour();
		int nMinute = cCurTime.GetMinute ();

		DWORD dwORDER = sDW.IsBattleWeekDay(nDayOfWeek,nHour);
		if ( dwORDER!=UINT_MAX )
		{
			//	Note : 결정전 시작 점검.
			if ( sDW.IsBattleHour ( dwORDER, nHour ) )
			{
				//	Note : 클럽 결정전 시작.
				sDW.DoBattleStart ( dwORDER, nHour );
				m_fRemainTimer = (float)sDW.m_dwBattleTime;
				m_fTimer = 0.0f;
			}
			else
			{
				//	Note : 결정전 시작 공지.
				sDW.UpdateNotifyBattle ( dwORDER, nHour, nMinute );
			}
		}

		if ( sDW.IsBattle() )
		{
			sDW.m_fBattleTimer += fElapsedAppTime;
			if ( sDW.m_fBattleTimer > float(sDW.m_dwBattleTime) )
			{
				sDW.DoBattleEnd();
			}
		}
	}

	// 클라이언트에게 경과 시간을 알린다.
	if ( !m_vecDW.empty() )
	{
		if ( m_vecDW[0].IsBattle() )
		{
			GLMSG::SNET_SCHOOL_WAR_REMAIN_BRD NetMsgBrd;

			// 시작하면 통지
			if ( m_fRemainTimer == m_vecDW[0].m_dwBattleTime )
			{
				NetMsgBrd.dwTime = (DWORD)m_fRemainTimer;
				GLAgentServer::GetInstance().SENDTOALLCLIENT ( &NetMsgBrd );
			}

			m_fTimer += fElapsedAppTime;
			m_fRemainTimer -= fElapsedAppTime;

			// 이후 10분만다 통지
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

GLSchoolWarFieldMan& GLSchoolWarFieldMan::GetInstance()
{
	static GLSchoolWarFieldMan cInstance;
	return cInstance;
}

bool GLSchoolWarFieldMan::SetMapState ()
{
	for ( DW_VEC::size_type i=0; i<m_vecDW.size(); ++i )
	{
		GLSchoolWar &sDW = m_vecDW[i];

		//	Note : 선도 클럽 전투 입구존.
		SNATIVEID nidHallMAP ( sDW.m_dwClubHallMap );
		GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( nidHallMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwClubMapID = sDW.m_dwID;
//			pLandMan->m_pGuidance = GLGuidanceFieldMan::GetInstance().Find ( sGuidance.m_dwID );

			pLandMan->m_bDomiWarsMapHall = true;
		}

		//	Note : 선도 클럽 전투존.
		SNATIVEID nidMAP ( sDW.m_dwClubMap );
		SMAPNODE *pMAPNODE = GLGaeaServer::GetInstance().FindMapNode ( nidMAP );
		if ( pMAPNODE )
		{
			pMAPNODE->bDomiWars = TRUE;
		}

		pLandMan = GLGaeaServer::GetInstance().GetByMapID ( nidMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwClubMapID = sDW.m_dwID;
//			pLandMan->m_pGuidance = GLGuidanceFieldMan::GetInstance().Find ( sGuidance.m_dwID );

			pLandMan->m_bDomiWarsMap = true;	
		}
	}

	return true;
}
bool GLSchoolWarFieldMan::ReadyBattle( DWORD dwID )
{
	GLSchoolWar *pDW = Find ( dwID );
	if ( !pDW )	return false;

	pDW->SetBattle( GLSchoolWar::BATTLE_READY );

	//	Note : 멥 설정 변경.

	return true;
}

bool GLSchoolWarFieldMan::BeginBattle ( DWORD dwID )
{
	GLSchoolWar *pDW = Find ( dwID );
	if ( !pDW )	return false;

	pDW->SetBattle( GLSchoolWar::BATTLE_START );

	//	Note : 멥 설정 변경.
	return true;
}

bool GLSchoolWarFieldMan::EndBattle ( DWORD dwID )
{
	GLSchoolWar *pDW = Find ( dwID );
	if ( !pDW )	return false;

	pDW->SetBattle( GLSchoolWar::BATTLE_END_AWARD );

	// 체크시작
//	pCDM->m_bBattleEndCheck = true;
	pDW->m_fCHECK_TIME = 10.0f;


	UpdateDWRanking( dwID );//Mike915
	DWAwardItem( dwID );

	pDW->m_vecDWAwardChar.clear();
	pDW->m_mapDWScore.clear();

	GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( pDW->m_dwClubMap );
	if ( pLandMan )
	{
		pLandMan->DoGateOutPCAll ( pDW->m_dwCLubMapGate );
	}

	return true;
}


const std::string GLSchoolWarFieldMan::GetName ( DWORD dwID )
{
	GLSchoolWar *pDW = Find ( dwID );
	if ( !pDW )				return "";

	return pDW->m_strName;
}

DWORD GLSchoolWarFieldMan::GetWinCharID ( DWORD dwCharID )
{
	for ( DW_VEC::size_type i=0; i<m_vecDW.size(); ++i )
	{
		GLSchoolWar &sDW = m_vecDW[i];

		if ( sDW.m_dwWinChar == dwCharID )		return sDW.m_dwID;
	}

	return UINT_MAX;
}


bool GLSchoolWarFieldMan::FrameMove ( float fElaps )
{
	for ( DW_VEC::size_type i=0; i<m_vecDW.size(); ++i )
	{
		GLSchoolWar &sDW = m_vecDW[i];

		if( sDW.IsBattle() )
		{
			sDW.m_fRankingUpdate += fElaps;

			//	5분마다 랭킹 갱신
			if ( sDW.m_fRankingUpdate > 0.0f )
			{
				UpdateDWRanking( sDW.m_dwID );// Mike915
				sDW.m_fRankingUpdate = 0.0f;
			}
		}

		if ( sDW.IsBattleEndAward() )
		{
			sDW.CheckAwardClub( fElaps );
		}

		if ( sDW.IsBattleEnd() )
		{
			//sSW.CheckExtraClub( fElaps );
		}
	}

	return true;
}

void GLSchoolWarFieldMan::UpdateDWRanking( DWORD dwID )// Mike915
{
	GLSchoolWar *pDW = Find ( dwID );
	if ( !pDW )	return;
	
	GLSchoolWar &sDW = *pDW;
	
	DW_RANK_INFO_VEC	m_vecDWRankNew;
	m_vecDWRankNew.reserve( sDW.m_mapDWScore.size() );

	DW_RANK_INFO_MAP_ITER	pos = sDW.m_mapDWScore.begin();
	DW_RANK_INFO_MAP_ITER	end = sDW.m_mapDWScore.end();

	for ( ; pos != end; pos++ )
	{
		const SDW_RANK_INFO&	sRankInfo = pos->second;					
		m_vecDWRankNew.push_back( sRankInfo );
	}

	
	std::sort( m_vecDWRankNew.begin(), m_vecDWRankNew.end() );	

	// 랭킹 계산
	int nSize = m_vecDWRankNew.size();
	for ( int i = 0; i < nSize; ++i )
	{
		m_vecDWRankNew[i].wPlayerRanking = i+1;
		m_vecDWRankNew[i].nIndex = i;
	}

	//	동점상황 랭킹 계산 아래 랭킹에 맞춤

	for ( int i = nSize-1; i > 0; --i )
	{
		if ( m_vecDWRankNew[i] == m_vecDWRankNew[i-1] )
		{
			m_vecDWRankNew[i-1].wPlayerRanking = m_vecDWRankNew[i].wPlayerRanking;			
		}
	}	
	
	GLMSG::SNET_SCHOOL_WAR_RANKING_UPDATE	NetMsg;

	for ( int i = 0; i < m_vecDWRankNew.size(); ++i )
	{
		DW_RANK_INFO_MAP_ITER iter = sDW.m_mapDWScore.find( m_vecDWRankNew[i].dwCharID );
		if ( iter == sDW.m_mapDWScore.end() )	continue;	//	이럴경우는 없어야 함

		SDW_RANK_INFO&	sRankInfo = iter->second;
		

		if ( m_vecDWRankNew[i].nIndex != sRankInfo.nIndex || 
			 m_vecDWRankNew[i].wPlayerRanking != sRankInfo.wPlayerRanking )
		{
			sRankInfo.wPlayerRanking = m_vecDWRankNew[i].wPlayerRanking;
			sRankInfo.wKillNum = m_vecDWRankNew[i].wKillNum;
			sRankInfo.wDeathNum = m_vecDWRankNew[i].wDeathNum;
			sRankInfo.nIndex = m_vecDWRankNew[i].nIndex;

			//	9개 클럽만 보낸다.
			if ( m_vecDWRankNew[i].nIndex < RANKING_NUM ) 
			{
				SDW_RANK sDWRank = sRankInfo;
				NetMsg.ADDDW( sDWRank );
			}
		}		
				
	}

	if ( NetMsg.wRankNum > 0 )	{

		GLGaeaServer::GetInstance().SENDTOCLIENT_ONMAP( sDW.m_dwClubMap, &NetMsg );
	}


	GLMSG::SNET_SCHOOL_WAR_MYRANK_UPDATE	NetMsgMy;

	pos = sDW.m_mapDWScore.begin();
	end = sDW.m_mapDWScore.end();

	for ( ; pos != end; pos++ )
	{
		const SDW_RANK_INFO&	sRankInfo = pos->second;
		NetMsgMy.sMyDWRank.wPlayerRanking = sRankInfo.wPlayerRanking;
		NetMsgMy.sMyDWRank.wKillNum = sRankInfo.wKillNum;
		NetMsgMy.sMyDWRank.wDeathNum = sRankInfo.wDeathNum;

		GLGaeaServer::GetInstance().SENDTOCLUBCLIENT_ONDWMAP( sDW.m_dwClubMap, sRankInfo.dwCharID, &NetMsgMy );
	}
}

void GLSchoolWarFieldMan::DWAwardItem( DWORD dwID )
{
	GLSchoolWar *pDW = Find ( dwID );
	if ( !pDW )	return;

	if ( !pDW->IsBattleEndAward() ) return;	

	GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( pDW->m_dwClubMap );
	if ( !pLandMan ) return;

	//	해당 맵에 있는 유저들 보상 지급
	{
		//GLClubMan& cClubMan = GLGaeaServer::GetInstance().GetClubMan();

		GLCHARNODE* pCharNode = pLandMan->m_GlobPCList.m_pHead;
		for ( ; pCharNode; pCharNode = pCharNode->pNext )
		{
			PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar( pCharNode->Data->m_dwGaeaID );
			if ( !pChar ) continue;

			//GLCLUB* pClub = cClubMan.GetClub( pChar->m_dwGuild );
			//if ( !pClub ) continue;

			DW_RANK_INFO_MAP_ITER iter = pDW->m_mapDWScore.find( pChar->m_dwCharID );
			if ( iter != pDW->m_mapDWScore.end() ) 
			{
				SDW_RANK_INFO& sDWRankInfo = iter->second;

				// ( 보상 받은 캐릭터인지 점검 ) 
				DW_AWARD_CHAR_ITER iter = pDW->m_vecDWAwardChar.find( pChar->m_dwCharID );
				if ( iter != pDW->m_vecDWAwardChar.end() )	continue;

				int nAwardIndex;
				if ( sDWRankInfo.wPlayerRanking < 10 ) nAwardIndex = sDWRankInfo.wPlayerRanking - 1;
				else if ( sDWRankInfo.wPlayerRanking <= pDW->m_sDWAwardItem.dwAwardLimit ) nAwardIndex = 3;
				else continue;
				
				SNATIVEID sNativeID = pDW->m_sDWAwardItem.nAwardItem[nAwardIndex];
				
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

				pDW->m_vecDWAwardChar.insert( pChar->m_dwCharID );
			}
		}
	}

}
