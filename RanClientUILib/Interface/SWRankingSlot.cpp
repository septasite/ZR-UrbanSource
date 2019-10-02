#include "StdAfx.h"
#include "SWRankingSlot.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "BasicLineBox.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "BasicLineBoxEx.h"
#include "GLGaeaClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSWRankingSlot::CSWRankingSlot () :
	m_pPlayerName ( NULL ),
	m_pKill ( NULL ),
	m_pDeath ( NULL ),
	m_pRank ( NULL )
{
	for ( int i = 0; i < 3; i++ )
	{
		m_pSchool[i] = NULL;	
	}

	for ( int i = 0; i < 16; i++ )
	{
		m_pClass[i] = NULL;	
	}
}

CSWRankingSlot::~CSWRankingSlot ()
{
}

void CSWRankingSlot::CreateSubControl ()
{
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, _DEFAULT_FONT_SHADOW_FLAG );
	CD3DFontPar* pFont9Default = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, FALSE );
	int nTextAlign = TEXT_ALIGN_CENTER_X;
	int nTextAlignLeft = TEXT_ALIGN_LEFT;
	int nTextAlignRight = TEXT_ALIGN_RIGHT;
	D3DCOLOR dwFontColor = NS_UITEXTCOLOR::DEFAULT;
	D3DCOLOR dwNameColor = NS_UITEXTCOLOR::PARTYNAME;

	{
		CString strSchool[3] = 
		{
			"SW_RANKING_SLOT_SCHOOL0",
			"SW_RANKING_SLOT_SCHOOL1",
			"SW_RANKING_SLOT_SCHOOL2"
		};

		for ( int i = 0; i < 3; i++ )
		{
			m_pSchool[i] = CreateControl ( strSchool[i].GetString() );
		}
	}

	{
		CString strClass[GLCI_NUM_NEWEST] = 
		{
			"SW_RANKING_SLOT_BRAWLER_M",
			"SW_RANKING_SLOT_SWORDSMAN_M",
			"SW_RANKING_SLOT_ARCHER_F",
			"SW_RANKING_SLOT_SHAMAN_F",
			"SW_RANKING_SLOT_EXTREME_M",
			"SW_RANKING_SLOT_EXTREME_F",
			"SW_RANKING_SLOT_BRAWLER_F",
			"SW_RANKING_SLOT_SWORDSMAN_F",
			"SW_RANKING_SLOT_ARCHER_M",
			"SW_RANKING_SLOT_SHAMAN_M",
			"SW_RANKING_SLOT_SCIENCE_M",
			"SW_RANKING_SLOT_SCIENCE_F",
			"SW_RANKING_SLOT_ASSASSIN_M",
			"SW_RANKING_SLOT_ASSASSIN_F",
			"SW_RANKING_SLOT_MAGICIAN_M",
			"SW_RANKING_SLOT_MAGICIAN_F",
		};

		for ( int i = 0; i < GLCI_NUM_NEWEST; i++ )
		{
			m_pClass[i] = CreateControl ( strClass[i].GetString() );
		}
	}

	m_pSwPRankingText = new CBasicTextBox;
	m_pSwPRankingText->CreateSub ( this, "SWP_RANKING_TEXT" );
	m_pSwPRankingText->SetFont ( pFont9 );
	m_pSwPRankingText->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( m_pSwPRankingText );	

	m_pRank = new CBasicTextBox;
	m_pRank->CreateSub ( this, "SW_RANKING_RANK_TEXT" );
	m_pRank->SetFont ( pFont9 );
	m_pRank->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( m_pRank );	

	m_pPlayerName = new CBasicTextBox;
	m_pPlayerName->CreateSub ( this, "SW_RANKING_NAME_TEXT" );
	m_pPlayerName->SetFont ( pFont9 );
	m_pPlayerName->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( m_pPlayerName ); 

	m_pKill = new CBasicTextBox;
	m_pKill->CreateSub ( this, "SW_RANKING_KILL_TEXT" );
	m_pKill->SetFont ( pFont9 );
	m_pKill->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( m_pKill );	

	m_pDeath = new CBasicTextBox;
	m_pDeath->CreateSub ( this, "SW_RANKING_DEATH_TEXT" );
	m_pDeath->SetFont ( pFont9 );
	m_pDeath->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( m_pDeath );

	

	//m_pPlayerName = CreateStaticControl ( "SW_RANKING_SLOT_PLAYER_NAME", pFont9Default, NS_UITEXTCOLOR::WHITE, nTextAlignRight );
}

CUIControl*	CSWRankingSlot::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

CBasicTextBox* CSWRankingSlot::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	return pStaticText;
}

void CSWRankingSlot::SetNumber ( int nSlotNumber )
{
	int nRankNum = GLGaeaClient::GetInstance().m_vecSwPRank.size();
	SWP_RANK_VEC& vecSwPRank = GLGaeaClient::GetInstance().m_vecSwPRank;

	CString strNum;
	for ( int i = 0; i < nRankNum; ++i )
	{
	strNum.Format( "%d" ,vecSwPRank[i].wCharRanking );
	m_pRank->AddText( strNum, NS_UITEXTCOLOR::WHITE );
	}
}

void CSWRankingSlot::SetScore( int nKill, int nDeath )
{
	int nRankNum = GLGaeaClient::GetInstance().m_vecSwPRank.size();
	SWP_RANK_VEC& vecSwPRank = GLGaeaClient::GetInstance().m_vecSwPRank;

	CString strKill;
	CString strDeath;

	for ( int i = 0; i < nRankNum; ++i )
	{
	strKill.Format( "%d" ,vecSwPRank[i].wKillNum );
	m_pKill->AddText( strKill, NS_UITEXTCOLOR::WHITE );

	strDeath.Format( "%d" ,vecSwPRank[i].wDeathNum );
	m_pDeath->AddText( strDeath, NS_UITEXTCOLOR::WHITE );
	}

}

void CSWRankingSlot::SetPlayerName ( CString strName )
{ 
	int nRankNum = GLGaeaClient::GetInstance().m_vecSwPRank.size();
	SWP_RANK_VEC& vecSwPRank = GLGaeaClient::GetInstance().m_vecSwPRank;

	for ( int i = 0; i < nRankNum; ++i )
	{
	strName.Format( "%d" ,vecSwPRank[i].szCharName );
	m_pPlayerName->AddText( strName, NS_UITEXTCOLOR::WHITE );
	}
}

void CSWRankingSlot::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
}

void CSWRankingSlot::SetClass ( int nClassType )
{
	//add class
	if ( nClassType < GLCI_FIGHTER_M && GLCI_TESTING_W < nClassType )
	{
		GASSERT ( 0 && "?????? ?????? ??? ?????." );
		return ;
	}

	m_pClass[0]->SetVisibleSingle ( FALSE );
	m_pClass[1]->SetVisibleSingle ( FALSE );
	m_pClass[2]->SetVisibleSingle ( FALSE );
	m_pClass[3]->SetVisibleSingle ( FALSE );
	m_pClass[4]->SetVisibleSingle ( FALSE );
	m_pClass[5]->SetVisibleSingle ( FALSE );
	m_pClass[6]->SetVisibleSingle ( FALSE );
	m_pClass[7]->SetVisibleSingle ( FALSE );
	m_pClass[8]->SetVisibleSingle ( FALSE );
	m_pClass[9]->SetVisibleSingle ( FALSE );
	m_pClass[10]->SetVisibleSingle ( FALSE );
	m_pClass[11]->SetVisibleSingle ( FALSE );
	m_pClass[12]->SetVisibleSingle ( FALSE );
	m_pClass[13]->SetVisibleSingle ( FALSE );
	m_pClass[14]->SetVisibleSingle ( FALSE );
	m_pClass[15]->SetVisibleSingle ( FALSE );


	if ( nClassType == 0 ) { m_pClass[0]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 1 ) { m_pClass[1]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 2 ) { m_pClass[2]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 3 ) { m_pClass[3]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 4 ) { m_pClass[4]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 5 ) { m_pClass[5]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 6 ) { m_pClass[6]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 7 ) { m_pClass[7]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 8 ) { m_pClass[8]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 9 ) { m_pClass[9]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 10 ) { m_pClass[10]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 11 ) { m_pClass[11]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 12 ) { m_pClass[12]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 13 ) { m_pClass[13]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 14 ) { m_pClass[14]->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 15 ) { m_pClass[15]->SetVisibleSingle ( TRUE ); }
}

void CSWRankingSlot::SetSchool ( int nSchoolType )
{
	//add class
	for ( int i = 0; i < 3; i++ )
	{
		m_pSchool[i]->SetVisibleSingle ( FALSE );
	}

	m_pSchool[nSchoolType]->SetVisibleSingle ( TRUE );
}