#include "StdAfx.h"
#include "CCtfRankingDisplay.h"
#include "CCtfRankingPage2.h"
#include "CCtfRankingSelf.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "d3dfont.h"
#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "BasicTextButton.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCtfRankingDisplay::CCtfRankingDisplay()
	:	m_pSwPRankingText ( NULL )
	,	m_pPage_whole ( NULL )
	,	m_pPage_sg ( NULL )
	,	m_pPage_mp ( NULL )
	,	m_pPage_phx ( NULL )
	,	m_pCloseBtn ( NULL )
	,	m_pCTFBaseLineBoxHead	( NULL )
	,	m_pCTFBaseLineBoxBody	( NULL )
	,	m_pCtfMyRankingPage ( NULL )
{
	memset ( m_pCtfRankingPage, 0, sizeof ( m_pCtfRankingPage ) );
}

CCtfRankingDisplay::~CCtfRankingDisplay()
{
}

void CCtfRankingDisplay::CreateSubControl ()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_SHADOW_FLAG );

	m_pPage_whole = CreateTextButton23 ( "CTF_RESULT_SORTBUTTON_TOTAL", PAGE_WHOLE, (char*)ID2GAMEWORD ( "CTF_RESULT_BUTTON", 0 ) );
	m_pPage_sg = CreateTextButton23 ( "CTF_RESULT_SORTBUTTON_SM", PAGE_SG, (char*)ID2GAMEWORD ( "CTF_RESULT_BUTTON", 1 ) );
	m_pPage_mp = CreateTextButton23 ( "CTF_RESULT_SORTBUTTON_HA", PAGE_MP, (char*)ID2GAMEWORD ( "CTF_RESULT_BUTTON", 2 ) );
	m_pPage_phx = CreateTextButton23 ( "CTF_RESULT_SORTBUTTON_BH", PAGE_PHX, (char*)ID2GAMEWORD ( "CTF_RESULT_BUTTON", 3 ) );
	m_pCloseBtn = CreateTextButton ( "CTF_RESULT_BUTTON_CLOSE", BUTTON_CLOSE, (char*)ID2GAMEWORD ( "CTF_RESULT_BUTTON", 4 ) );

	m_pCTFBaseLineBoxHead = new CBasicLineBoxEx;
	m_pCTFBaseLineBoxHead->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pCTFBaseLineBoxHead->CreateBaseBoxWhiteOuter ( "CTF_RESULT_RANKSLOT_BASE" );
	m_pCTFBaseLineBoxHead->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pCTFBaseLineBoxHead );

	m_pCTFBaseLineBoxBody = new CBasicLineBoxEx;
	m_pCTFBaseLineBoxBody->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pCTFBaseLineBoxBody->CreateBaseBoxWhiteOuter ( "CTF_RESULT_RANKSLOT_BODY" );
	m_pCTFBaseLineBoxBody->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pCTFBaseLineBoxBody );

	for ( int i = 0; i < nMAXPAGE; i++ )
	{			
		m_pCtfRankingPage[i] = new CCtfRankingPage2;
		m_pCtfRankingPage[i]->CreateSub ( this, "CTF_RESULT_RANKING", UI_FLAG_DEFAULT, PAGE_RANKING_0 +i );
		m_pCtfRankingPage[i]->CreateSubControl ();
		m_pCtfRankingPage[i]->SetVisibleSingle( (i==3)? TRUE:FALSE);
		m_pCtfRankingPage[i]->m_nRankType = i;
		RegisterControl ( m_pCtfRankingPage[i] );
	}	

	m_pCtfMyRankingPage = new CCtfRankingSelf;
	m_pCtfMyRankingPage->CreateSub ( this, "CTF_RESULT_MYRANKING", UI_FLAG_DEFAULT, PAGE_MYRANK  );
	m_pCtfMyRankingPage->CreateSubControl ();
	m_pCtfMyRankingPage->SetVisibleSingle( FALSE );
	RegisterControl ( m_pCtfMyRankingPage );


	m_pSwPRankingText = new CBasicTextBox;
	m_pSwPRankingText->CreateSub ( this, "SWP_RANKING_TEXT" );
	m_pSwPRankingText->SetFont ( pFont );
	m_pSwPRankingText->SetTextAlign ( TEXT_ALIGN_LEFT );
	RegisterControl ( m_pSwPRankingText );	

	m_pPage_sg->SetFlip(false);
	m_pPage_mp->SetFlip(false);
	m_pPage_phx->SetFlip(false);

	CBasicTextBox* pClubTimeText = new CBasicTextBox;	
	pClubTimeText->CreateSub ( this, "CTF_RESULT_TEXT_TIME" );
	pClubTimeText->SetFont ( pFont );
	pClubTimeText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	RegisterControl ( pClubTimeText );
	m_pClubTimeText = pClubTimeText;

}

CBasicTextButton*  CCtfRankingDisplay::CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText ,_DEFAULT_FONT_SHADOW_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}

CBasicTextButton*  CCtfRankingDisplay::CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE24;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON24", UI_FLAG_XSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText );
	pTextButton->SetFlip(FALSE);
	RegisterControl ( pTextButton );
	return pTextButton;
}

void CCtfRankingDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CCtfRankingDisplay::TranslateUIMessage( UIGUID ControlID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
		case PAGE_WHOLE:
			{
				if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	
				{
					SetVisiblePage(3);
				}
			}
			break;
		case PAGE_SG:
			{
				if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	
				{
					SetVisiblePage(0);
				}
			}
			break;
		case PAGE_MP:
			{
				if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	
				{
					SetVisiblePage(1);
				}
			}
			break;
		case PAGE_PHX:
			{
				if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	
				{
					SetVisiblePage(2);
				}
			}
			break;
		case BUTTON_CLOSE:
			{
				if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	
				{
					this->SetVisibleSingle(FALSE);
				}
			}
			break;
	}
}

void CCtfRankingDisplay::SetVisiblePage( int page )
{
	m_pPage_whole->SetFlip(false);
	m_pPage_sg->SetFlip(false);
	m_pPage_mp->SetFlip(false);
	m_pPage_phx->SetFlip(false);
	
	for ( int i = 0; i < nMAXPAGE; i++ )
		m_pCtfRankingPage[i]->SetVisibleSingle( FALSE );

	switch( page )
	{
	case 0:
		{
			m_pPage_sg->SetFlip(true);
			RefreshSwPRanking(0);
		}
		break;
	case 1:
		{
			m_pPage_mp->SetFlip(true);
			RefreshSwPRanking(1);
		}
		break;
	case 2:
		{
		    m_pPage_phx->SetFlip(true);
			RefreshSwPRanking(2);
		}
		break;
	case 3:
		{
			m_pPage_whole->SetFlip(true);
			RefreshSwPRanking(3);
		}
		break;
	}
}

void CCtfRankingDisplay::RefreshSwPRanking()
{
	for ( int i = 0; i < nMAXPAGE; i++ )
		m_pCtfRankingPage[i]->RefreshRankSlot();

	m_pCtfMyRankingPage->SetVisibleSingle( TRUE );
	m_pCtfMyRankingPage->RefreshRankSlot();
}

void CCtfRankingDisplay::RefreshSwPRanking( int page )
{
	for ( int i = 0; i < nMAXPAGE; i++ )
		m_pCtfRankingPage[i]->SetVisibleSingle(FALSE);

	m_pCtfRankingPage[page]->RefreshRankSlot();
	m_pCtfRankingPage[page]->SetVisibleSingle(TRUE);
}

void CCtfRankingDisplay::UpdateClubTime( float fBATTLETime )
{
	CString strCombine;

	m_pClubTimeText->ClearText();
	m_pClubTimeText->SetText( ID2GAMEWORD( "CTF_RESULT_TEXT", 0 ), NS_UITEXTCOLOR::WHITE );
	strCombine.Format ( ID2GAMEWORD( "CTF_RESULT_TEXT", 1 ), (DWORD)fBATTLETime/60, (DWORD)fBATTLETime%60 );
	m_pClubTimeText->AddString(0,strCombine, NS_UITEXTCOLOR::ORANGE);
	m_pClubTimeText->AddString(0,">", NS_UITEXTCOLOR::WHITE);
	
	m_pClubTimeText->SetVisibleSingle( TRUE );
}