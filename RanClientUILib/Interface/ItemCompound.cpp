#include "StdAfx.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "GLGaeaClient.h"
#include "GLCharacter.h"
#include "InnerInterface.h"
#include ".\ItemCompound.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "CharacterEnum.h"



CCompundCompete::CCompundCompete(void)
{
}

CCompundCompete::~CCompundCompete(void)
{
}
void CCompundCompete::CreateSubControl ()
{
	
	m_pCompundButton = new CBasicButton;
	m_pCompundButton->CreateSub ( this,"ITEM_COMPOUND_BUTTON_IMAGE", UI_FLAG_DEFAULT, COMPOUND_BUTTON );
	m_pCompundButton->SetUseGlobalAction ( TRUE );
	m_pCompundButton->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pCompundButton );
}


void CCompundCompete::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );	

	m_pCompundButton->SetVisibleSingle ( TRUE );
}

void CCompundCompete::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case	COMPOUND_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Item Compound System", NS_UITEXTCOLOR::WHITE  );				
			}

			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				//if ( 
				//CInnerInterface::GetInstance().OpenItemMixWindowButton();
				//GLGaeaClient::GetInstance().GetCharacter()->ResetItemMix();
				if ( dwMsg & UIMSG_LB_UP )
				{
					if ( !CInnerInterface::GetInstance().IsVisibleGroup ( ITEM_MIX_WINDOW ) )
					{
						CInnerInterface::GetInstance().OpenItemMixWindowButton();
					}
					else
					{
						CInnerInterface::GetInstance().CloseItemMixWindow();
						CInnerInterface::GetInstance().HideGroup ( ITEM_MIX_WINDOW );
					}
				}
			}
		}
		break;
	}
}

