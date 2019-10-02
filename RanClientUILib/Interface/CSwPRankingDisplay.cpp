#include "StdAfx.h"
#include "CSwPRankingDisplay.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "d3dfont.h"
#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "BasicLineBox.h"
#include "GLCharDefine.h"
//#include "InnerInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSwPRankingDisplay::CSwPRankingDisplay()
	//For Player Ranking
	:	m_pSwPRankText ( NULL )
	,	m_pSwPNameText ( NULL )
	,	m_pSwPKillText ( NULL )
	,	m_pSwPDeathText ( NULL )

	//For School Rankings
	,	m_pSwRankText ( NULL )
	,	m_pSwSchoolText ( NULL )
	,	m_pSwKillText ( NULL )
	,	m_pSwDeathText ( NULL )

	, m_pBackGround( NULL )

	//Gui for Menu Bar Player Ranking
	,	m_pSwStaticRankText ( NULL )
	,	m_pSwStaticNameText ( NULL )
	,	m_pSwStaticKillText ( NULL )
	,	m_pSwStaticDeathText ( NULL )

	//Gui for Menu Bar
	,	m_pSwStaticRankText1 ( NULL )
	,	m_pSwStaticSchoolText1 ( NULL )
	,	m_pSwStaticKillText1 ( NULL )
	,	m_pSwStaticDeathText1 ( NULL )
{
}

CSwPRankingDisplay::~CSwPRankingDisplay()
{
}

void CSwPRankingDisplay::CreateSubControl ()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE,_DEFAULT_FONT_SHADOW_FLAG );

	
	m_pBackGround = new CUIControl;
	m_pBackGround->CreateSub ( this, "SCHOOLWARS_WINDOW_BACKGROUND", UI_FLAG_DEFAULT );	
	m_pBackGround->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pBackGround );
	

	{	
		// Player Menu Bar
		m_pBackLine1 = new CBasicLineBox;
		m_pBackLine1->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBackLine1->CreateBaseBoxSkill ( "SCHOOLWAR_MENU_PLAYER_BACK" );
		RegisterControl ( m_pBackLine1 );

		// Player Score Back
		m_pBackLine2 = new CBasicLineBox;
		m_pBackLine2->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBackLine2->CreateBaseBoxSkill ( "SCHOOLWAR_SCORE_PLAYER_BACK" );
		RegisterControl ( m_pBackLine2 );

		// School Menu Bar
		m_pBackLine3 = new CBasicLineBox;
		m_pBackLine3->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBackLine3->CreateBaseBoxSkill ( "SCHOOLWAR_MENU_SCHOOL_BACK" );
		RegisterControl ( m_pBackLine3 );

		// School Score Back
		m_pBackLine4 = new CBasicLineBox;
		m_pBackLine4->CreateSub ( this, "BASIC_LINE_BOX_SKILL", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		m_pBackLine4->CreateBaseBoxSkill ( "SCHOOLWAR_SCORE_SCHOOL_BACK" );
		RegisterControl ( m_pBackLine4 );
	}

	//For Player Ranking
	m_pSwPRankText = new CBasicTextBox;
	m_pSwPRankText->CreateSub ( this, "SWP_RANK_TEXT" );
	m_pSwPRankText->SetFont ( pFont );
	m_pSwPRankText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwPRankText );

	m_pSwPNameText = new CBasicTextBox;
	m_pSwPNameText->CreateSub ( this, "SWP_NAME_TEXT" );
	m_pSwPNameText->SetFont ( pFont );
	m_pSwPNameText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwPNameText );

	m_pSwPKillText = new CBasicTextBox;
	m_pSwPKillText->CreateSub ( this, "SWP_KILL_TEXT" );
	m_pSwPKillText->SetFont ( pFont );
	m_pSwPKillText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwPKillText );

	m_pSwPDeathText = new CBasicTextBox;
	m_pSwPDeathText->CreateSub ( this, "SWP_DEATH_TEXT" );
	m_pSwPDeathText->SetFont ( pFont );
	m_pSwPDeathText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwPDeathText );
	//End player ranking

	//For School Ranking
	m_pSwRankText = new CBasicTextBox;
	m_pSwRankText->CreateSub ( this, "SW_RANK_TEXT" );
	m_pSwRankText->SetFont ( pFont );
	m_pSwRankText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwRankText );

	m_pSwSchoolText = new CBasicTextBox;
	m_pSwSchoolText->CreateSub ( this, "SW_SCHOOL_TEXT" );
	m_pSwSchoolText->SetFont ( pFont );
	m_pSwSchoolText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwSchoolText );

	m_pSwKillText = new CBasicTextBox;
	m_pSwKillText->CreateSub ( this, "SW_KILL_TEXT" );
	m_pSwKillText->SetFont ( pFont );
	m_pSwKillText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwKillText );

	m_pSwDeathText = new CBasicTextBox;
	m_pSwDeathText->CreateSub ( this, "SW_DEATH_TEXT" );
	m_pSwDeathText->SetFont ( pFont );
	m_pSwDeathText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwDeathText );
	//End School Ranking

	//Gui for Menu Bar Player
	m_pSwStaticRankText = new CBasicTextBox;
	m_pSwStaticRankText->CreateSub ( this, "SW_RANK_STATIC_TEXT" );
	m_pSwStaticRankText->SetFont ( pFont );
	m_pSwStaticRankText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwStaticRankText );

	m_pSwStaticNameText = new CBasicTextBox;
	m_pSwStaticNameText->CreateSub ( this, "SW_NAME_STATIC_TEXT" );
	m_pSwStaticNameText->SetFont ( pFont );
	m_pSwStaticNameText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwStaticNameText );

	m_pSwStaticKillText = new CBasicTextBox;
	m_pSwStaticKillText->CreateSub ( this, "SW_KILL_STATIC_TEXT" );
	m_pSwStaticKillText->SetFont ( pFont );
	m_pSwStaticKillText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwStaticKillText );

	m_pSwStaticDeathText = new CBasicTextBox;
	m_pSwStaticDeathText->CreateSub ( this, "SW_DEATH_STATIC_TEXT" );
	m_pSwStaticDeathText->SetFont ( pFont );
	m_pSwStaticDeathText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwStaticDeathText );

	//Gui for Menu Bar School
	m_pSwStaticRankText1 = new CBasicTextBox;
	m_pSwStaticRankText1->CreateSub ( this, "SW_RANK_STATIC_TEXT1" );
	m_pSwStaticRankText1->SetFont ( pFont );
	m_pSwStaticRankText1->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwStaticRankText1 );

	m_pSwStaticSchoolText1 = new CBasicTextBox;
	m_pSwStaticSchoolText1->CreateSub ( this, "SW_SCHOOL_STATIC_TEXT1" );
	m_pSwStaticSchoolText1->SetFont ( pFont );
	m_pSwStaticSchoolText1->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwStaticSchoolText1 );

	m_pSwStaticKillText1 = new CBasicTextBox;
	m_pSwStaticKillText1->CreateSub ( this, "SW_KILL_STATIC_TEXT1" );
	m_pSwStaticKillText1->SetFont ( pFont );
	m_pSwStaticKillText1->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwStaticKillText1 );

	m_pSwStaticDeathText1 = new CBasicTextBox;
	m_pSwStaticDeathText1->CreateSub ( this, "SW_DEATH_STATIC_TEXT1" );
	m_pSwStaticDeathText1->SetFont ( pFont );
	m_pSwStaticDeathText1->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( m_pSwStaticDeathText1 );
}

void CSwPRankingDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CSwPRankingDisplay::RefreshSwPRanking()
{
	CString strStaticStrings; //Field String - HAHAHAH. Arrrrt

	//Player
	if ( !m_pSwPRankText ) return;
	if ( !m_pSwPNameText ) return;
	if ( !m_pSwPKillText ) return;
	if ( !m_pSwPDeathText ) return;

	//Player
	m_pSwPRankText->ClearText();
	m_pSwPNameText->ClearText();
	m_pSwPKillText->ClearText();
	m_pSwPDeathText->ClearText();

	//For Player Ranking
	strStaticStrings.Format( "Rank");
	m_pSwStaticRankText->AddText( strStaticStrings, NS_UITEXTCOLOR::WHITESMOKE );

	strStaticStrings.Format( "Character Name");
	m_pSwStaticNameText->AddText( strStaticStrings, NS_UITEXTCOLOR::WHITESMOKE );

	strStaticStrings.Format( "Kill");
	m_pSwStaticKillText->AddText( strStaticStrings, NS_UITEXTCOLOR::WHITESMOKE );

	strStaticStrings.Format( "Death");
	m_pSwStaticDeathText->AddText( strStaticStrings, NS_UITEXTCOLOR::WHITESMOKE );

	//Player Ranking Start
	int nRankNum = GLGaeaClient::GetInstance().m_vecSwPRank.size();
	CString strRank;
	CString strName;
	CString strKill;
	CString strDeath;

	SWP_RANK_VEC& vecSwPRank = GLGaeaClient::GetInstance().m_vecSwPRank;

	for ( int i = 0; i < nRankNum; ++i )
	{
		strRank.Format( "%2d" ,vecSwPRank[i].wCharRanking);
		m_pSwPRankText->AddText( strRank, NS_UITEXTCOLOR::LIGHTGREY );

		strName.Format( "%s" ,vecSwPRank[i].szCharName);
		m_pSwPNameText->AddText( strName, NS_UITEXTCOLOR::PALEGREEN );

		strKill.Format( "%d" ,vecSwPRank[i].wKillNum);
		m_pSwPKillText->AddText( strKill, NS_UITEXTCOLOR::GOLD );

		strDeath.Format( "%d" ,vecSwPRank[i].wDeathNum);
		m_pSwPDeathText->AddText( strDeath, NS_UITEXTCOLOR::RED );
	}

	//School Ranking Start
	if ( !m_pSwRankText ) return;
	if ( !m_pSwSchoolText ) return;
	if ( !m_pSwKillText ) return;
	if ( !m_pSwDeathText ) return;

	m_pSwRankText->ClearText();
	m_pSwSchoolText->ClearText();
	m_pSwKillText->ClearText();
	m_pSwDeathText->ClearText();

	strStaticStrings.Format( "Rank");
	m_pSwStaticRankText1->AddText( strStaticStrings, NS_UITEXTCOLOR::WHITESMOKE );

	strStaticStrings.Format( "School Name");
	m_pSwStaticSchoolText1->AddText( strStaticStrings, NS_UITEXTCOLOR::WHITESMOKE );

	strStaticStrings.Format( "Kill");
	m_pSwStaticKillText1->AddText( strStaticStrings, NS_UITEXTCOLOR::WHITESMOKE );

	strStaticStrings.Format( "Death");
	m_pSwStaticDeathText1->AddText( strStaticStrings, NS_UITEXTCOLOR::WHITESMOKE );

	int nRankNum1 = GLGaeaClient::GetInstance().m_vecSwRank.size();
	CString strRank1;
	CString strKill1;
	CString strDeath1;
	CString strSchool1;
	CString m_zScName = "";

	SW_RANK_VEC& vecSwRank = GLGaeaClient::GetInstance().m_vecSwRank;

	for ( int i = 0; i < nRankNum1; ++i )
	{
		strRank1.Format( "%2d" ,vecSwRank[i].wClubRanking);
		m_pSwRankText->AddText( strRank1, NS_UITEXTCOLOR::LIGHTGREY );

		strSchool1.Format( "%s" ,vecSwRank[i].szClubName);
		m_pSwSchoolText->AddText( strSchool1, NS_UITEXTCOLOR::PALEGREEN );

		strKill1.Format( "%d" ,vecSwRank[i].wKillNum);
		m_pSwKillText->AddText( strKill1, NS_UITEXTCOLOR::GOLD );

		strDeath1.Format( "%d" ,vecSwRank[i].wDeathNum);
		m_pSwDeathText->AddText( strDeath1, NS_UITEXTCOLOR::RED );
	}
}