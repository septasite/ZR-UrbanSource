#pragma once

#include "GLCaptureTheFieldData.h"

class GLCaptureTheField
{
public:
	

	enum EM_BATTLE_STATE 
	{
		BATTLE_NOSTART		= 0,
		BATTLE_READY		= 1,
		BATTLE_START		= 2,
		BATTLE_END_AWARD	= 3,
		BATTLE_END			= 4,
	};

public:
	//common var
	DWORD					m_dwID;	
	std::string				m_strName;
	EM_BATTLE_STATE			m_emBattleState;
	DWORD					m_dwCaptureTheFieldMap;

	float					m_fCHECK_TIMER;
	float					m_fCHECK_TIMER_MAX;
	WORD					m_wSchoolWinner;

	DWORD					m_dwReviveGate[CTF_MAX_REVIVE_GATE];

	//agent server
	SCTF_SCHEDULE_MAP		m_MapSchedule;
	SCTF_SCHEDULE_VEC		m_VecSchedule;
	DWORD					m_dwLastID;
	DWORD					m_dwBattleOrder;
	bool					m_bNotifyOneHour;
	bool					m_bNotifyHalfHour;
	bool					m_bNotify10MinHour;
	DWORD					m_dwBattleTime;
	float					m_fBattleTimer;

	//field server
	CTF_RANK_PLAYER_MAP		m_mapScorePlayerAll;
	CTF_RANK_PLAYER_MAP		m_mapScorePlayerSG;
	CTF_RANK_PLAYER_MAP		m_mapScorePlayerMP;
	CTF_RANK_PLAYER_MAP		m_mapScorePlayerPHX;
	CTF_RANK_PLAYER_MAP		m_mapScoreWinner;
	CTF_SCORE_TOWER_MAP		m_mapTowerScore;

	float					m_fRankingUpdate;
	float					m_fRankingUpdateTime;

	SCTF_AWARD_ITEM			m_sAwardItem;
	CTF_AWARD_CHAR			m_vecAwardChar;
	bool					m_bAwardStart;

	float					m_fTowerUpdate;
	float					m_fTowerUpdateTime;
	
public:
	GLCaptureTheField ();

	GLCaptureTheField ( const GLCaptureTheField &value )
	{
		operator= ( value );
	}

	GLCaptureTheField& operator= ( const GLCaptureTheField& value );

	bool operator < ( const GLCaptureTheField& sCaptureTheField )
	{
		return m_dwID < sCaptureTheField.m_dwID;
	}

public:
	bool Load ( std::string strFile );


public:
	//common
	void SetBattle( EM_BATTLE_STATE emBattleState )	{ m_emBattleState = emBattleState; }
	bool IsBattle ()		{ return ( m_emBattleState == BATTLE_START ); }
	bool IsBattleReady()	{ return ( m_emBattleState == BATTLE_READY ); }
	bool IsBattleEndAward() { return ( m_emBattleState == BATTLE_END_AWARD); }
	bool IsBattleEnd()		{ return ( m_emBattleState == BATTLE_END); }

	bool IsEnterMap( WORD wSCHOOL );
	DWORD GetReviveGate( WORD wSCHOOL );
	BOOL CheckAwardTime( float fElaps );

	//agent server 
	DWORD IsBattleWeekDay ( int nDayOfWeek, int nHour );
	bool IsBattleHour ( DWORD dwORDER, int nHour );
	void UpdateNotifyBattle ( DWORD dwORDER, int nHour, int nMinute );
	void NotifyBattleBroadcast( int nTIME, BOOL bREADY );
	void DoBattleStart ( DWORD dwORDER );
	void DoBattleEndAward();
	void DoBattleEnd();
	BOOL ScheduleIsEmpty()	{	return (m_MapSchedule.size() == 0);	}
	BOOL ReloadSchedule();

	//field server
	void FieldBattleEnd();
	SCTF_RANK_PLAYER*	GetRankingPlayerAll( DWORD dwCharID );
	SCTF_RANK_PLAYER*	GetRankingPlayerSG( DWORD dwCharID );
	SCTF_RANK_PLAYER*	GetRankingPlayerMP( DWORD dwCharID );
	SCTF_RANK_PLAYER*	GetRankingPlayerPHX( DWORD dwCharID );
	SCTF_SCORE_TOWER*	GetTowerScore( DWORD dwCROWID );

	void AddScore( DWORD dwKillChar, DWORD dwDeathChar );
	void AddDamageTower( SNATIVEID sID, DWORD dwDAMAGE, WORD wSCHOOL );
	void AddDamageChar( DWORD dwCHARID, DWORD dwDAMAGE );

	void AddWinner( SCTF_RANK_PLAYER sRANK );


public:
};
