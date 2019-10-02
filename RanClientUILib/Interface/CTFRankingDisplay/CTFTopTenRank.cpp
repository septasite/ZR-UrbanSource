#include "StdAfx.h"
#include "CTFTopTenRank.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "d3dfont.h"
#include "GLGaeaClient.h"
#include "../UITextControl.h"
#include "../GameTextControl.h"
#include "../BasicLineBox.h"
#include "GLCharDefine.h"
//#include "InnerInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCtfTopTenRank::CCtfTopTenRank()
	//For Player Ranking
	:	m_pRrPRankText ( NULL )
	,	m_pRrPNameText ( NULL )
	,	m_pRrPKillText ( NULL )
	,	m_pRrPDeathText ( NULL )

	, m_pBackGround( NULL )

	//Gui for Menu Bar Player Ranking
	,	m_pRrStaticRankText ( NULL )
	,	m_pRrStaticNameText ( NULL )
	,	m_pRrStaticKillText ( NULL )
	,	m_pRrStaticDeathText ( NULL )
{
}

CCtfTopTenRank::~CCtfTopTenRank()
{
}

void CCtfTopTenRank::CreateSubControl ()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE, _DEFAULT_FONT_SHADOW_FLAG );

	
	m_pBackGround = new CUIControl;
	m_pBackGround->CreateSub ( this, "ROYALRUMBLE_WINDOW_BACKGROUND", UI_FLAG_DEFAULT );	
	m_pBackGround->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pBackGround );
	

	{	
		// Player Menu Bar
		m_pBackLine1 = new CBasicLineBox;
		m_pBackLine1->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBackLine1->CreateBaseBoxSkill ( "ROYALRUMBLE_MENU_PLAYER_BACK" );
		RegisterControl ( m_pBackLine1 );

		// Player Score Back
		m_pBackLine2 = new CBasicLineBox;
		m_pBackLine2->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBackLine2->CreateBaseBoxSkill ( "ROYALRUMBLE_SCORE_PLAYER_BACK" );
		RegisterControl ( m_pBackLine2 );
	}

	//For Player Ranking
	m_pRrPRankText = new CBasicTextBox;
	m_pRrPRankText->CreateSub ( this, "RRP_RANK_TEXT" );
	m_pRrPRankText->SetFont ( pFont );
	m_pRrPRankText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pRrPRankText );

	m_pRrPNameText = new CBasicTextBox;
	m_pRrPNameText->CreateSub ( this, "RRP_NAME_TEXT" );
	m_pRrPNameText->SetFont ( pFont );
	m_pRrPNameText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pRrPNameText );

	m_pRrPKillText = new CBasicTextBox;
	m_pRrPKillText->CreateSub ( this, "RRP_KILL_TEXT" );
	m_pRrPKillText->SetFont ( pFont );
	m_pRrPKillText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pRrPKillText );

	m_pRrPDeathText = new CBasicTextBox;
	m_pRrPDeathText->CreateSub ( this, "RRP_DEATH_TEXT" );
	m_pRrPDeathText->SetFont ( pFont );
	m_pRrPDeathText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pRrPDeathText );
	//End player ranking

	//Gui for Menu Bar Player
	m_pRrStaticRankText = new CBasicTextBox;
	m_pRrStaticRankText->CreateSub ( this, "RR_RANK_STATIC_TEXT" );
	m_pRrStaticRankText->SetFont ( pFont );
	m_pRrStaticRankText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pRrStaticRankText );

	m_pRrStaticNameText = new CBasicTextBox;
	m_pRrStaticNameText->CreateSub ( this, "RR_NAME_STATIC_TEXT" );
	m_pRrStaticNameText->SetFont ( pFont );
	m_pRrStaticNameText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pRrStaticNameText );

	m_pRrStaticKillText = new CBasicTextBox;
	m_pRrStaticKillText->CreateSub ( this, "RR_KILL_STATIC_TEXT" );
	m_pRrStaticKillText->SetFont ( pFont );
	m_pRrStaticKillText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pRrStaticKillText );

	m_pRrStaticDeathText = new CBasicTextBox;
	m_pRrStaticDeathText->CreateSub ( this, "RR_DEATH_STATIC_TEXT" );
	m_pRrStaticDeathText->SetFont ( pFont );
	m_pRrStaticDeathText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pRrStaticDeathText );
}

void CCtfTopTenRank::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CCtfTopTenRank::RefreshRrPRanking()
{
	CString strStaticStrings; //Field String - HAHAHAH. Arrrrt

	//Player
	if ( !m_pRrPRankText ) return;
	if ( !m_pRrPNameText ) return;
	if ( !m_pRrPKillText ) return;
	if ( !m_pRrPDeathText ) return;

	//Player
	m_pRrPRankText->ClearText();
	m_pRrPNameText->ClearText();
	m_pRrPKillText->ClearText();
	m_pRrPDeathText->ClearText();

	//For Player Ranking
	strStaticStrings.Format( "Rank");
	m_pRrStaticRankText->AddText( strStaticStrings, NS_UITEXTCOLOR::WHITESMOKE );

	strStaticStrings.Format( "Character Name");
	m_pRrStaticNameText->AddText( strStaticStrings, NS_UITEXTCOLOR::WHITESMOKE );

	strStaticStrings.Format( "Kill");
	m_pRrStaticKillText->AddText( strStaticStrings, NS_UITEXTCOLOR::WHITESMOKE );

	strStaticStrings.Format( "Death");
	m_pRrStaticDeathText->AddText( strStaticStrings, NS_UITEXTCOLOR::WHITESMOKE );

	//Player Ranking Start
	int nRankNum = GLGaeaClient::GetInstance().m_vecRrPRank.size();
	CString strRank;
	CString strName;
	CString strKill;
	CString strDeath;

	//RRP_RANK_VEC& vecRrPRank = GLGaeaClient::GetInstance().m_vecRrPRank;
	RRP_RANK_VEC& vecCtfRank = GLGaeaClient::GetInstance().m_vecRrPRank;

	for ( int i = 0; i < nRankNum; ++i )
	{
		strRank.Format( "%2d" ,vecCtfRank[i].wCharRanking);
		m_pRrPRankText->AddText( strRank, NS_UITEXTCOLOR::LIGHTGREY );

		strName.Format( "%s" ,vecCtfRank[i].szCharName);
		m_pRrPNameText->AddText( strName, NS_UITEXTCOLOR::PALEGREEN );
	}
}