#include "StdAfx.h"
#include "CRRRankingDisplay.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "BasicTextButton.h"
#include "InnerInterface.h"
#include "ModalWindow.h"
#include "ModalCallerID.h"
#include "GameTextControl.h"
#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CRRRankingDisplay::CRRRankingDisplay ()
{
}

CRRRankingDisplay::~CRRRankingDisplay ()
{
}

void CRRRankingDisplay::CreateSubControl ()
{
	CreateTextButton ( "ROYALRUMBLE_SCOREBOARD_OPEN_BUTTON", ROYALRUMBLE_SCOREBOARD_OPEN_BUTTON, (char*)ID2GAMEWORD ( "ROYAL_RUMBLE", 0 ) );
}

CBasicButton* CRRRankingDisplay::CreateFlipButton ( char* szButton, char* szButtonFlip, UIGUID ControlID )
{
	CBasicButton* pButton = new CBasicButton;
	pButton->CreateSub ( this, szButton, UI_FLAG_DEFAULT, ControlID );
	pButton->CreateFlip ( szButtonFlip, CBasicButton::CLICK_FLIP );
	pButton->SetUseDynamic ( TRUE );
	RegisterControl ( pButton );

	return pButton;
}

void CRRRankingDisplay::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case ROYALRUMBLE_SCOREBOARD_OPEN_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( ID2GAMEINTEXT( "ROYALRUMBLE_SCOREBOARD_MESSAGE" ), NS_UITEXTCOLOR::WHITE );
			}
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				if( !CInnerInterface::GetInstance().IsVisibleGroup ( ROYAL_RUMBLE_WINDOW ) )
				{
					CInnerInterface::GetInstance().ShowGroupFocus ( ROYAL_RUMBLE_WINDOW );
				}
				else
				{
					CInnerInterface::GetInstance().HideGroup ( ROYAL_RUMBLE_WINDOW );
				}
			}
		}
		break;
	}
}
CBasicTextButton*	 CRRRankingDisplay::CreateTextButton ( char* szButton, UIGUID ControlID, char* szText )
{
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON22", UI_FLAG_XSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, 
									CBasicTextButton::SIZE22, 
									CBasicButton::CLICK_FLIP, 
									szText,
									_DEFAULT_FONT_SHADOW_EX_FLAG );
	pTextButton->SetFlip ( TRUE );
	RegisterControl ( pTextButton );

	return pTextButton;
}
