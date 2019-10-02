#pragma once

#include "GLCaptureTheField.h"
#include "../GLogicData.h"

class GLCaptureTheFieldMan
{
public:
	typedef std::vector<GLCaptureTheField>	CTF_VEC;
	typedef CTF_VEC::iterator				CTF_VEC_ITER;

protected:
	CTF_VEC	m_vecCTF;
	DWORD	m_dwLASTWINNER;

public:
	bool Load ( std::vector<std::string> &vecFiles );

public:
	void	SetLastWinner( DWORD dwWINNER )	{	m_dwLASTWINNER = dwWINNER; }
	DWORD	GetLastWinner()	{	return m_dwLASTWINNER;	}

public:
	GLCaptureTheField* FindCTF ( DWORD dwID, BOOL bCHECK, BOOL bINIT );
	bool IsBattle ();

public:
	GLCaptureTheFieldMan ()
		: m_dwLASTWINNER( MAX_SCHOOL )
	{
	}

public:
};


class GLCaptureTheFieldFieldMan : public GLCaptureTheFieldMan
{
public:

public:
	bool FrameMove ( float fElaps );

public:
	bool SetMapState ();


	bool ReadyBattle( DWORD dwID );
	bool BeginBattle ( DWORD dwID );
	bool EndBattleAward ( DWORD dwID );
	bool EndBattleField ( DWORD dwID );
	bool WinnerField ( DWORD dwID, WORD wWINNER );

	void UpdateRanking( DWORD dwID );
	void UpdateTower( DWORD dwID );

	void UpdateRankingPlayerAll( GLCaptureTheField *pCTF );
	void UpdateRankingPlayerSG( GLCaptureTheField *pCTF );
	void UpdateRankingPlayerMP( GLCaptureTheField *pCTF );
	void UpdateRankingPlayerPHX( GLCaptureTheField *pCTF );
	void UpdateRankingSelf( GLCaptureTheField *pCTF );

	void UpdateTowerScore( GLCaptureTheField *pCTF );

	void CheckWinner( DWORD dwID );
	void SendRewards( DWORD dwID );


protected:
	GLCaptureTheFieldFieldMan ()
	{
	}

public:
	static GLCaptureTheFieldFieldMan& GetInstance();
};




class GLCaptureTheFieldAgentMan : public GLCaptureTheFieldMan
{
protected:
	float m_fRemainTimer, m_fTimer;
	float m_fEndedTimer;

public:
	bool SetMapState ();

public:
	DWORD GetRemainTime () { return (DWORD)m_fRemainTimer; }

public:
	bool FrameMove ( float fElapsedAppTime );

public:
	GLCaptureTheFieldAgentMan ()
		: m_fRemainTimer(0)
		, m_fTimer(0)
		, m_fEndedTimer( 0.0f )
	{
	}

public:
	static GLCaptureTheFieldAgentMan& GetInstance();
};