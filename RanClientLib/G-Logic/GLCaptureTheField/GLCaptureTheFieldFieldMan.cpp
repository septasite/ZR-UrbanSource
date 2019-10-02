#include "StdAfx.h"
#include "GLCaptureTheFieldMan.h"
#include "GLGaeaServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//field server
GLCaptureTheFieldFieldMan& GLCaptureTheFieldFieldMan::GetInstance()
{
	static GLCaptureTheFieldFieldMan cInstance;
	return cInstance;
}

bool GLCaptureTheFieldFieldMan::SetMapState ()
{
	for ( CTF_VEC::size_type i=0; i<m_vecCTF.size(); ++i )
	{
		GLCaptureTheField &sCTF = m_vecCTF[i];

		SNATIVEID nidMAP ( sCTF.m_dwCaptureTheFieldMap );
		SMAPNODE *pMAPNODE = GLGaeaServer::GetInstance().FindMapNode ( nidMAP );
		if ( pMAPNODE )
		{
			pMAPNODE->bCTFZone = TRUE;
		}

		GLLandMan *pLandMan = GLGaeaServer::GetInstance().GetByMapID ( nidMAP );
		if ( pLandMan )
		{
			pLandMan->m_dwCaptureTheFieldMapID = sCTF.m_dwID;
			pLandMan->m_bCaptureTheFieldMap = true;	
		}
	}

	return true;
}

bool GLCaptureTheFieldFieldMan::FrameMove ( float fElaps )
{
	for ( CTF_VEC::size_type i=0; i<m_vecCTF.size(); ++i )
	{
		GLCaptureTheField &sCTF = m_vecCTF[i];

		if( sCTF.IsBattle() )
		{
			sCTF.m_fRankingUpdate += fElaps;
			if ( sCTF.m_fRankingUpdate > sCTF.m_fRankingUpdateTime )
			{
				UpdateRanking( sCTF.m_dwID );
				sCTF.m_fRankingUpdate = 0.0f;
			}

			sCTF.m_fTowerUpdate += fElaps;
			if ( sCTF.m_fTowerUpdate > sCTF.m_fTowerUpdateTime )
			{
				UpdateTower( sCTF.m_dwID );
				sCTF.m_fTowerUpdate = 0.0f;
			}

		}

		if ( sCTF.IsBattleEndAward() )
		{
			BOOL bENDED = sCTF.CheckAwardTime( fElaps );
			if ( bENDED )
			{
				EndBattleField( sCTF.m_dwID );
			}
			else
			{
				if ( sCTF.m_bAwardStart )
				{
					SendRewards( sCTF.m_dwID );
				}
			}
		}
	}

	return true;
}


bool GLCaptureTheFieldFieldMan::ReadyBattle( DWORD dwID )
{
	GLCaptureTheField *pCTF = FindCTF ( dwID, FALSE, FALSE );
	if ( !pCTF )	return false;

	pCTF->SetBattle( GLCaptureTheField::BATTLE_READY );

	GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF: ReadyBattle:ID %d", dwID );
	return true;
}

bool GLCaptureTheFieldFieldMan::BeginBattle ( DWORD dwID )
{
	GLCaptureTheField *pCTF = FindCTF ( dwID, FALSE, FALSE );
	if ( !pCTF )	return false;

	pCTF->SetBattle( GLCaptureTheField::BATTLE_START );
	GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF: BeginBattle:ID %d", dwID );

	return true;
}

bool GLCaptureTheFieldFieldMan::EndBattleAward ( DWORD dwID )
{
	GLCaptureTheField *pCTF = FindCTF ( dwID, FALSE, FALSE );
	if ( !pCTF )	return false;

	pCTF->SetBattle( GLCaptureTheField::BATTLE_END_AWARD );

	//send final rankings to players
	UpdateRanking( dwID );

	//decide the winner
	CheckWinner( dwID );

	pCTF->m_bAwardStart = true;

	GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF: EndBattleAward:ID %d", dwID );

	return true;
}

bool GLCaptureTheFieldFieldMan::EndBattleField ( DWORD dwID )
{
	GLCaptureTheField *pCTF = FindCTF ( dwID, FALSE, FALSE );
	if ( !pCTF )	return false;

	GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF: Reward Ended:ID %d RewardNum:%d", dwID, pCTF->m_vecAwardChar.size() );

	pCTF->SetBattle( GLCaptureTheField::BATTLE_END );
	pCTF->FieldBattleEnd();

	GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF: EndBattleField:ID %d", dwID );

	return true;
}

bool GLCaptureTheFieldFieldMan::WinnerField ( DWORD dwID, WORD wWINNER )
{
	GLCaptureTheField *pCTF = FindCTF ( dwID, FALSE, FALSE );
	if ( !pCTF )	return false;
	pCTF->m_wSchoolWinner = wWINNER;
	SetLastWinner( pCTF->m_wSchoolWinner );
	GLGaeaServer::GetInstance().GetConsoleMsg()->Write( "CTF: FieldWinner ID:%d  %s", dwID, GLCONST_CHAR::strSCHOOLNAME[pCTF->m_wSchoolWinner].c_str() );

	return true;
}
