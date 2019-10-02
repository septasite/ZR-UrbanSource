#pragma once

#include "GLSWDefine.h"
#include "GLSWPDefine.h"

#include <vector>

#define SCHOOL_RANK_NUM		10
#define SCHOOL_NAME		15

struct GLSWID
{
	DWORD	m_dwID;				
	DWORD	m_dwSWID;

	GLSWID () :
		m_dwID(UINT_MAX),
		m_dwSWID(GLSCHOOL_NUM)
	{
	}
};

typedef std::vector<GLSWID>	VECSWID_DB;

class GLSchoolWars
{
public:
	enum 
	{		
		MAX_TIME = 56,
	};

	enum EM_BATTLE_STATE 
	{
		BATTLE_NOSTART		= 0,
		BATTLE_READY		= 1,
		BATTLE_START		= 2,	
		BATTLE_END_AWARD	= 3,	
		BATTLE_END			= 4,	
	};

public:
	DWORD				m_dwID;		
	std::string			m_strName;		

	DWORD				m_dwClubMap;		
	DWORD				m_dwCLubMapGate;	
	DWORD				m_dwClubHallMap;	
	DWORD				m_dwClubHallGate;		

	DWORD				m_dwWinClub;	

	DWORD				m_dwBattleTime;
	SSW_TIME			m_sSwTIME[MAX_TIME];	

	//SSW_AWARD_ITEM		m_sSwAwardItem;		
	
	SW_AWARD_CHAR		m_vecSwAwardChar;		
	SW_RANK_INFO_MAP	m_mapSwScore;		

	SSWP_AWARD_ITEM		m_sSwPAwardItem;
	SWP_AWARD_CHAR		m_vecSwPAwardChar;
	SWP_RANK_INFO_MAP	m_mapSwPScore;

	bool				m_bNotifyOneHour;
	bool				m_bNotifyHalfHour;
	bool				m_bNotify10MinHour;

	EM_BATTLE_STATE		m_emBattleState;
	DWORD				m_dwBattleOrder;	
	DWORD				m_dwLastBattleHour;
	float				m_fBattleTimer;

//	DWORD				m_dwCERTIFY_CHARID;
//	DWORD				m_dwCERTIFY_NPCID;
//	float				m_fCERTIFY_TIMER;
//	D3DXVECTOR3			m_vCERTIFY_POS;

	float				m_fCHECK_TIMER;			//	배틀 종료후 타이머들 ( 상품이랑 유저 팅길때 사용 ) 
	float				m_fCHECK_TIME;			//

//	bool				m_bBattleEndCheck;		// 선도전 종료직후 전산실 입장을 막기위해
//	float				m_fCHECK_TIMER;
//	float				m_fCHECK_TIME;


	float				m_fRankingUpdate;		//	랭킹 타이머

	WORD				m_wSwBonusRate;

public:
	GLSchoolWars ();

	GLSchoolWars ( const GLSchoolWars &value )
	{
		operator= ( value );
	}

	GLSchoolWars& operator= ( const GLSchoolWars& value );

	bool operator < ( const GLSchoolWars& sSchoolWAR )
	{
		return m_dwID < sSchoolWAR.m_dwID;
	}

public:
	bool Load ( std::string strFile );

public:
	void AddSWScore( DWORD dwKillClub, DWORD dwDeathClub );
	void AddSWPScore( DWORD dwKillChar, DWORD dwKillGaeaID, DWORD dwDeathChar, DWORD dwDeathGaeaID );
	void AddFlagScore ( DWORD dwKillSchool, WORD wKillPoints );
	SSW_RANK_INFO* GetSWRankInof( DWORD dwClubID );
	SSWP_RANK_INFO* GetSWPRankInof( DWORD dwCharID );

public:
//	bool IsCertify()		{ return m_dwCERTIFY_CHARID!=0; }

public:
//	bool IsNewCommission ();
//	bool IsGuidClub ( DWORD dwClubID );

public:
	bool IsBattle () { return ( m_emBattleState == BATTLE_START ); }
	bool IsBattleReady() { return ( m_emBattleState == BATTLE_READY ); }
	bool IsBattleEndAward() { return ( m_emBattleState == BATTLE_END_AWARD); } //jdev test
	bool IsBattleEnd() { return ( m_emBattleState == BATTLE_END ); }
	bool IsEnterMap(DWORD dwCharID);
	DWORD IsBattleWeekDay ( int nDayOfWeek, int nHour );

	void SetBattle( EM_BATTLE_STATE emBattleState )	{ m_emBattleState = emBattleState; }
	
	// 선도클럽 시작시간인가?
	bool IsBattleHour ( DWORD dwORDER, int nHour );

public:
	// 최종적으로 선도클럽결정전이 일어난 날을 세팅한다.
	void UpdateBattleDay ( int nDay );
	// 선도클럽 결정전 남은 시간을 클라이언트에게 알린다.
	void UpdateNotifyBattle ( DWORD dwORDER, int nHour, int nMinute );
//	void UpdateCommission ( float fElaps );

	//	선도 클럽이 종료되고 나서 유저를 튕군다.
	void CheckExtraGuild ( float fElaps );
	bool IsCheckExtraGuild() { return true; }

	void CheckAwardClub( float fElaps );	//	보상 지급
	void CheckExtraClub( float fElaps );	//	유저 내보내기 

public:
	// 선도클럽 결정전을 시작한다.
	void DoBattleStart ( DWORD dwORDER, int nDay );
	void DoBattleEnd();

//	void DoCertifyEnd();

public:
	bool ChangeSWSchoolID ( DWORD dwSwID );
//	bool ChangeCommission ( float fRate );
};

class GLSchoolWarsMan
{
public:
	typedef std::vector<GLSchoolWars>			SW_VEC;
	typedef SW_VEC::iterator						SW_VEC_ITER;
	typedef std::pair<SW_VEC_ITER,SW_VEC_ITER>	SW_VEC_PAIR;

protected:
	SW_VEC											m_vecSchoolWAR;

public:
	bool Load ( std::vector<std::string> &vecFiles );
	bool SetState ( VECSWID_DB &vecSWID );

public:
	GLSchoolWars* Find ( DWORD dwID );
	bool IsBattle ();
//	bool IsCheckExtraGuild ();

public:
	GLSchoolWarsMan ()
	{
	}

public:
	//static GLGuidanceMan& GetInstance();
};

class GLSchoolWarsAgentMan : public GLSchoolWarsMan
{
protected:
	float m_fRemainTimer, m_fTimer;

public:
	bool ChangeSWSchoolID ( DWORD dwID, DWORD dwSwID );
//	bool ChangeCommission ( DWORD dwID, float fRate );

public:
//	GLSchoolWars* FindByClubID ( DWORD dwClubID );

public:
	bool SetMapState ();

public:
//	DWORD GetGuidID ( DWORD dwClubID );
	DWORD GetRemainTime () { return (DWORD)m_fRemainTimer; }

public:
	bool FrameMove ( float fElapsedAppTime );

public:
	GLSchoolWarsAgentMan ()
		: m_fRemainTimer(0)
		, m_fTimer(0)
	{
	}

public:
	static GLSchoolWarsAgentMan& GetInstance();
};

class GLSchoolWarsFieldMan : public GLSchoolWarsMan
{
public:
	bool SetMapState ();

public:
	bool ReadyBattle( DWORD dwID );
	bool BeginBattle ( DWORD dwID );
	bool EndBattle ( DWORD dwID );

public:
	bool ChangeSWSchoolID ( DWORD dwID, DWORD dwSwID );
//	bool ChangeCommission ( DWORD dwID, float fRate );

//	bool DoCertify ( DWORD dwID, DWORD dwCHARID, DWORD dwNPCID, const D3DXVECTOR3 &vPOS );

public:
	DWORD GetWinClubID ( DWORD dwClubID );
//	EMCHECKCERTIFY CheckCertify ( DWORD dwID, DWORD dwCHARID );
	const std::string GetName ( DWORD dwID );

//	void CheckExtraGuild ( float fElaps );

	void UpdateSWRanking( DWORD dwID );
	void UpdateSWPRanking( DWORD dwID );
	void SWAwardItem( DWORD dwID );

public:
	bool FrameMove ( float fElaps );

protected:
	GLSchoolWarsFieldMan ()
	{
	}

public:
	static GLSchoolWarsFieldMan& GetInstance();
};