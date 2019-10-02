#include "StdAfx.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "GLGaeaClient.h"
#include "GLCharacter.h"
#include "InnerInterface.h"
#include ".\SWarIcon.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "../EngineUIlib/GUInterface/BasicProgressBar.h"
#include "BasicLineBoxEx.h"
#include "ModalWindow.h"
#include "ModalCallerID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSWarIcon::CSWarIcon(void) :
	m_pSWarIcon(NULL)
{
}

CSWarIcon::~CSWarIcon(void)
{
}
void CSWarIcon::CreateSubControl ()
{
	m_pSWarIcon = new CBasicButton;
	m_pSWarIcon->CreateSub ( this, "COMPETITION_NOTIFY_BUTTON_IMAGE", UI_FLAG_DEFAULT, SWarIconOnMouse );
	m_pSWarIcon->SetUseGlobalAction ( TRUE );
	RegisterControl ( m_pSWarIcon );
}
void CSWarIcon::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}
void CSWarIcon::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
switch ( ControlID )
	{
	case SWarIconOnMouse:
		{
		PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{	
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "BattleFieldUI/Tyranny Wars Ranking", NS_UITEXTCOLOR::WHITE  );
            if  ( dwMsg & UIMSG_LB_UP && pLand && !pLand->m_bTowerWars  )
				{
					if ( !CInnerInterface::GetInstance().IsVisibleGroup ( BATTLEFIELDUI_WINDOW ) )
					{

						CInnerInterface::GetInstance().ShowGroupFocus ( BATTLEFIELDUI_WINDOW );
					}
					else
					{
						CInnerInterface::GetInstance().HideGroup ( BATTLEFIELDUI_WINDOW );
					}
              }

				 if  ( dwMsg & UIMSG_LB_UP && pLand && pLand->m_bTowerWars  )
				 {
					DoModal ( "Exit School wars?", MODAL_QUESTION, YESNO, MODAL_EXIT_TOWERWARS );
				 }

				

				if ( CHECK_KEYFOCUSED ( dwMsg ) || CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
				{
					//CInnerInterface::GetInstance().CaptureTheFieldRankingDisplayOpen();
				}
			}
		}
		break;
	}
}