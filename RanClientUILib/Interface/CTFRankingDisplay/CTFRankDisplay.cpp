#include "StdAfx.h"
#include "CTFRankDisplay.h"

#include "../InnerInterface.h"
#include "../BasicTextButton.h"
#include "../GameTextControl.h"

#include "CTFRankPlayer.h"
#include "CTFRankPlayerSG.h"
#include "CTFRankPlayerMP.h"
#include "CTFRankPlayerPHX.h"
#include "CTFRankSelf.h"
#include "CTFTowerScore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCTFRankDisplay::CCTFRankDisplay () :
	m_nActivePage(0)
	, m_pButtonSchool( NULL )
	, m_pButtonAll( NULL )
	, m_pButtonSG( NULL )
	, m_pButtonMP( NULL )
	, m_pButtonPHX( NULL )
	, m_pRankAll( NULL )
	, m_pRankSG( NULL )
	, m_pRankMP( NULL )
	, m_pRankPHX( NULL )
	, m_pRankSelf( NULL )
	, m_pTowerScore( NULL )
{
	
}

CCTFRankDisplay::~CCTFRankDisplay ()
{
}

CBasicTextButton*  CCTFRankDisplay::CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButtonEx ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText );
	RegisterControl ( pTextButton );
	return pTextButton;

	/*const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButtonEx ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText );
	RegisterControl ( pTextButton );
	return pTextButton;*/
}

void CCTFRankDisplay::CreateSubControl ()
{	
	m_pButtonSchool = CreateTextButton23 ( "CTF_RESULT_SORTBUTTON_SCHOOL", CTF_RANK_BUTTON_SCHOOL, (char*)ID2GAMEWORD ( "CTF_RESULT_BUTTON", 0 ) );
	m_pButtonAll = CreateTextButton23 ( "CTF_RESULT_SORTBUTTON_TOTAL", CTF_RANK_BUTTON_ALL, (char*)ID2GAMEWORD ( "CTF_RESULT_BUTTON", 1 ) );
	m_pButtonSG = CreateTextButton23 ( "CTF_RESULT_SORTBUTTON_SM", CTF_RANK_BUTTON_SG, (char*)ID2GAMEWORD ( "CTF_RESULT_BUTTON", 2 ) );
	m_pButtonMP = CreateTextButton23 ( "CTF_RESULT_SORTBUTTON_HA", CTF_RANK_BUTTON_MP, (char*)ID2GAMEWORD ( "CTF_RESULT_BUTTON", 3 ) );
	m_pButtonPHX = CreateTextButton23 ( "CTF_RESULT_SORTBUTTON_BH", CTF_RANK_BUTTON_PHX, (char*)ID2GAMEWORD ( "CTF_RESULT_BUTTON", 4 ) );

	m_pRankAll = new CCTFRankPlayer;
	m_pRankAll->CreateSub( this, "CTF_RESULT_RANKING" );
	m_pRankAll->CreateSubControl();
	m_pRankAll->SetVisibleSingle( FALSE );
	RegisterControl( m_pRankAll );

	m_pRankSG = new CCTFRankPlayerSG;
	m_pRankSG->CreateSub( this, "CTF_RESULT_RANKING" );
	m_pRankSG->CreateSubControl();
	m_pRankSG->SetVisibleSingle( FALSE );
	RegisterControl( m_pRankSG );

	m_pRankMP = new CCTFRankPlayerMP;
	m_pRankMP->CreateSub( this, "CTF_RESULT_RANKING" );
	m_pRankMP->CreateSubControl();
	m_pRankMP->SetVisibleSingle( FALSE );
	RegisterControl( m_pRankMP );

	m_pRankPHX = new CCTFRankPlayerPHX;
	m_pRankPHX->CreateSub( this, "CTF_RESULT_RANKING" );
	m_pRankPHX->CreateSubControl();
	m_pRankPHX->SetVisibleSingle( FALSE );
	RegisterControl( m_pRankPHX );

	m_pTowerScore = new CCTFTowerScore;
	m_pTowerScore->CreateSub( this, "CTF_RESULT_RANKING" );
	m_pTowerScore->CreateSubControl();
	m_pTowerScore->SetVisibleSingle( FALSE );
	RegisterControl( m_pTowerScore );

	m_pRankSelf = new CCTFRankSelf;
	m_pRankSelf->CreateSub( this, "CTF_RESULT_SELF" );
	m_pRankSelf->CreateSubControl();
	m_pRankSelf->SetVisibleSingle( FALSE );
	RegisterControl( m_pRankSelf );

}

void CCTFRankDisplay::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( CTF_RANKING_DISPLAY );
			}
		}break;
	case ET_CONTROL_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			}
		}break;

	case CTF_RANK_BUTTON_SCHOOL:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	OpenPage( 0 );
		}break;
	case CTF_RANK_BUTTON_ALL:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	OpenPage( 1 );
		}break;
	case CTF_RANK_BUTTON_SG:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	OpenPage( 2 );
		}break;
	case CTF_RANK_BUTTON_MP:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	OpenPage( 3 );
		}break;
	case CTF_RANK_BUTTON_PHX:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	OpenPage( 4 );
		}break;
	}

	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );
}

void CCTFRankDisplay::SetVisibleSingle ( BOOL bVisible )
{
	CUIWindowEx::SetVisibleSingle( bVisible );

	if( bVisible )
	{
		OpenPage( 0 );
	}
}

void CCTFRankDisplay::RefreshRanking()
{
	if ( m_pRankAll )
		m_pRankAll->RefreshRanking();

	if ( m_pRankSG )
		m_pRankSG->RefreshRanking();

	if ( m_pRankMP )
		m_pRankMP->RefreshRanking();

	if ( m_pRankPHX )
		m_pRankPHX->RefreshRanking();

	if ( m_pRankSelf )
		m_pRankSelf->RefreshRanking();

	if ( m_pTowerScore )
		m_pTowerScore->RefreshRanking();
}

void CCTFRankDisplay::OpenPage( int nPage )
{
	if ( m_pButtonSchool )	m_pButtonSchool->SetFlip ( nPage == 0 );
	if ( m_pButtonAll )		m_pButtonAll->SetFlip ( nPage == 1 );
	if ( m_pButtonSG )		m_pButtonSG->SetFlip ( nPage == 2 );
	if ( m_pButtonMP )		m_pButtonMP->SetFlip ( nPage == 3 );
	if ( m_pButtonPHX )		m_pButtonPHX->SetFlip ( nPage == 4 );

	if ( m_pTowerScore )	m_pTowerScore->SetVisibleSingle( nPage == 0 );
	if ( m_pRankAll )		m_pRankAll->SetVisibleSingle( nPage == 1 );
	if ( m_pRankSG )		m_pRankSG->SetVisibleSingle( nPage == 2 );
	if ( m_pRankMP )		m_pRankMP->SetVisibleSingle( nPage == 3 );
	if ( m_pRankPHX )		m_pRankPHX->SetVisibleSingle( nPage == 4 );

	if ( m_pRankSelf )		m_pRankSelf->SetVisibleSingle( nPage == 1 || nPage == 2 || nPage == 3 || nPage == 4 );
}