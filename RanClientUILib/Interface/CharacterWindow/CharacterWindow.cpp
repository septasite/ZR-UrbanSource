#include "StdAfx.h"
#include "./CharacterWindow.h"

#include "../EngineUiLib/GUInterface/BasicTextBox.h"
#include "../EngineUiLib/GUInterface/BasicProgressBar.h"
#include "../EngineUiLib/GUInterface/BasicButton.h"
#include "../EngineLib/DxCommon/d3dfont.h"

#include "../BasicTextButton.h"
#include "../UITextControl.h"
#include "../GameTextControl.h"
#include "../RanClientLib/G-Logic/GLGaeaClient.h"
#include "../InnerInterface.h"
#include "CharacterWindowChar.h"
#include "CharacterWindowCharAdditionalInfo.h"
#include "CharacterWindowVehicle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCharacterWindow::CCharacterWindow () :
	nActivePage(0)
	, m_pPageChar( NULL )
	, m_pPageCharAdditional ( NULL )
	, m_pPageVehicle( NULL )
	, m_pBackGround( NULL )
	, m_pButtonChar( NULL )
	, m_pButtonVehicle( NULL )
{
}

CCharacterWindow::~CCharacterWindow ()
{
}

void CCharacterWindow::CreateSubControl ()
{
	m_pBackGround = new CUIControl;
	m_pBackGround->CreateSub ( this, "CHARACTER_WINDOW_BACKGROUND", UI_FLAG_DEFAULT );	
	m_pBackGround->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pBackGround );

	m_pButtonChar = CreateTextButton23 ( "CHARACTER_WINDOW_CHAR_TAP", BUTTON_CHARACTER, (char*)ID2GAMEWORD ( "CHARACTER_TAP_NAME", 0 ) );
	m_pButtonVehicle = CreateTextButton23 ( "CHARACTER_WINDOW_VEHICLE_TAP", BUTTON_VEHICLE, (char*)ID2GAMEWORD ( "CHARACTER_TAP_NAME", 1 ) );

	m_pPageChar = new CCharacterWindowChar;
	m_pPageChar->CreateSub ( this, "CHARACTER_WINDOW_REGION", UI_FLAG_YSIZE, PAGE_CHARACTER );
	m_pPageChar->CreateSubControl ();
	RegisterControl ( m_pPageChar );

	m_pPageCharAdditional = new CCharacterWindowCharAdditionalInfo;
	m_pPageCharAdditional->Create ( CHARACTER_ADDITIONAL_WINDOW, "BASIC_WINDOW", UI_FLAG_XSIZE | UI_FLAG_YSIZE);
	m_pPageCharAdditional->CreateBaseWindowBlack ( "CHARACTER_ADDITIONAL_WINDOW_MAIN", (char*)ID2GAMEWORD("CHARACTER_ADDITIONAL_STATIC") );
	m_pPageCharAdditional->CreateSubControl ();
	m_pPageCharAdditional->ResetAlignFlag ();
	RegisterControl ( m_pPageCharAdditional );

	m_pPageVehicle = new CCharacterWindowVehicle;
	m_pPageVehicle->CreateSub ( this, "CHARACTER_WINDOW_REGION", UI_FLAG_YSIZE, PAGE_VEHICLE );
	m_pPageVehicle->CreateSubControl ();
	RegisterControl ( m_pPageVehicle );
}

CBasicTextButton*  CCharacterWindow::CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButtonEx ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText, _DEFAULT_FONT_SHADOW_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}

void CCharacterWindow::SetGlobalPos(const D3DXVECTOR2& vPos)
{
	CUIGroup::SetGlobalPos( vPos );
}

void CCharacterWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( CHARACTER_WINDOW );
			}
		}
		break;
	case BUTTON_CHARACTER:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	
			{
				if ( nActivePage == CHARPAGE_CHARACTER )	return;
				OpenPage( CHARPAGE_CHARACTER );
			}
		}break;
	case BUTTON_VEHICLE:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	
			{
				if ( nActivePage == CHARPAGE_VEHICLE )	return;
				OpenPage( CHARPAGE_VEHICLE );
			}
		}break;
	}
}


void CCharacterWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{	
	CUIWindow::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

void CCharacterWindow::SetVisibleSingle ( BOOL bVisible )
{
	CUIWindow::SetVisibleSingle( bVisible );

	if( bVisible )
	{
		OpenPage( 0 );
	}
	else
	{
		if ( m_pPageChar )
			m_pPageChar->ClearRender();

		if ( m_pPageVehicle )
			m_pPageVehicle->ClearRender();
	}
}

void CCharacterWindow::OpenPage( int nPage )
{
	m_pButtonChar->SetFlipYellow ( FALSE );
	m_pButtonVehicle->SetFlipYellow ( FALSE );

	m_pPageChar->SetVisibleSingle ( FALSE );
	m_pPageCharAdditional->SetVisibleSingle ( FALSE );
	m_pPageVehicle->SetVisibleSingle ( FALSE );

	switch( nPage )
	{
	case CHARPAGE_CHARACTER:
		{
			m_pPageChar->SetVisibleSingle ( TRUE );
			m_pButtonChar->SetFlipYellow ( TRUE );
			nActivePage = nPage;
		}break;
	case CHARPAGE_VEHICLE:
		{
			m_pPageVehicle->SetVisibleSingle ( TRUE );
			m_pButtonVehicle->SetFlipYellow ( TRUE );
			nActivePage = nPage;
		}break;
	};
}

void CCharacterWindow::SetArmSwapTabButton( BOOL bArmSub )
{
	if( m_pPageChar )
	{
		m_pPageChar->SetArmSwapTabButton( bArmSub );
	}
}

void CCharacterWindow::RefreshVehiclePage()
{
	if( m_pPageVehicle )
	{
		if ( m_pPageVehicle->IsVisible() )
		{
			m_pPageVehicle->InitVehicle();
		}
	}
}