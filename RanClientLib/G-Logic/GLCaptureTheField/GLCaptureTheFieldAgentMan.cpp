#include "StdAfx.h"
#include "GLCaptureTheFieldMan.h"
#include "GLAgentServer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//agent server
GLCaptureTheFieldAgentMan& GLCaptureTheFieldAgentMan::GetInstance()
{
	static GLCaptureTheFieldAgentMan cInstance;
	return cInstance;
}

bool GLCaptureTheFieldAgentMan::SetMapState ()
{
	for ( CTF_VEC::size_type i=0; i<m_vecCTF.size(); ++i )
	{
		GLCaptureTheField &sCTF= m_vecCTF[i];

		SNATIVEID nidMAP ( sCTF.m_dwCaptureTheFieldMap );
		GLAGLandMan *pLandMan = GLAgentServer::GetInstance().GetByMapID ( nidMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwCaptureTheFieldMapID = sCTF.m_dwID;
			pLandMan->m_bCaptureTheFieldMap = true;
		}
	}

	return true;
}

bool GLCaptureTheFieldAgentMan::FrameMove ( float fElapsedAppTime )
{
	if ( GLCONST_CHAR::bPKLESS ) return false;

	for ( CTF_VEC::size_type i=0; i<m_vecCTF.size(); ++i )
	{
		GLCaptureTheField &sCTF = m_vecCTF[i];

		CTime cCurTime = CTime::GetCurrentTime();
		int nDayOfWeek = cCurTime.GetDayOfWeek ();
		int nDay = cCurTime.GetDay ();
		int nHour = cCurTime.GetHour();
		int nMinute = cCurTime.GetMinute ();

		DWORD dwORDER = sCTF.IsBattleWeekDay(nDayOfWeek, nHour );
		if ( dwORDER!=UINT_MAX )
		{
			if ( sCTF.IsBattleHour ( dwORDER, nHour ) )
			{
				sCTF.DoBattleStart ( dwORDER );
				m_fRemainTimer = (float)sCTF.m_dwBattleTime;
				m_fTimer = 0.0f;
			}
			else
			{
				sCTF.UpdateNotifyBattle ( dwORDER, nHour, nMinute );
			}
		}

		if ( sCTF.IsBattle() )
		{
			sCTF.m_fBattleTimer += fElapsedAppTime;
			if ( sCTF.m_fBattleTimer > float(sCTF.m_dwBattleTime) )
			{
				sCTF.DoBattleEndAward();
			}
		}

		if ( sCTF.IsBattleEndAward() )
		{
			BOOL bENDED = sCTF.CheckAwardTime( fElapsedAppTime );
			if ( bENDED )
			{
				sCTF.DoBattleEnd();
			}
		}

		if ( sCTF.ScheduleIsEmpty() )
		{
			BOOL bRELOADED = sCTF.ReloadSchedule();
		}
	}

	if ( !m_vecCTF.empty() )
	{
		if ( m_vecCTF[0].IsBattle() )
		{
			GLMSG::SNET_CAPTURETHEFIELD_REMAIN_BRD NetMsgBrd;

			if ( m_fRemainTimer == m_vecCTF[0].m_dwBattleTime )
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