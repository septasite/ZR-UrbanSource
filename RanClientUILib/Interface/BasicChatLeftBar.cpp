#include "StdAfx.h"
#include "BasicChatLeftBar.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "InnerInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CBasicChatLeftBar::CBasicChatLeftBar ()
{
}

CBasicChatLeftBar::~CBasicChatLeftBar ()
{
}

void CBasicChatLeftBar::CreateSubControl ()
{
/*	CUIControl* pTop = new CUIControl;
	pTop->CreateSub ( this, "CHAT_LEFT_BAR_TOP", UI_FLAG_DEFAULT, CHAT_LEFT_BAR_TOP );
	pTop->SetProtectSizePoint ();
	RegisterControl ( pTop );

	CUIControl* pBody = new CUIControl;
	pBody->CreateSub ( this, "CHAT_LEFT_BAR_BODY", UI_FLAG_YSIZE );
	pBody->SetProtectSizePoint ();
	RegisterControl ( pBody );

	CUIControl* pBottom = new CUIControl;
	pBottom->CreateSub ( this, "CHAT_LEFT_BAR_BOTTOM", UI_FLAG_BOTTOM );
	pBottom->SetProtectSizePoint ();
	RegisterControl ( pBottom );*/

	CUIControl* pNormalChat = new CUIControl;
	pNormalChat->CreateSub ( this, "CHAT_NORMAL_STATE", UI_FLAG_BOTTOM, CHAT_NORMAL_STATE );
	RegisterControl ( pNormalChat );
	m_pCHATSTATE[0] = pNormalChat;

	CUIControl* pPrivateChat = new CUIControl;
	pPrivateChat->CreateSub ( this, "CHAT_PRIVATE_STATE", UI_FLAG_BOTTOM, CHAT_PRIVATE_STATE );	
	RegisterControl ( pPrivateChat );
	m_pCHATSTATE[1] = pPrivateChat;

	CUIControl* pPartyChat = new CUIControl;
	pPartyChat->CreateSub ( this, "CHAT_PARTY_STATE", UI_FLAG_BOTTOM, CHAT_PARTY_STATE );	
	RegisterControl ( pPartyChat );
	m_pCHATSTATE[2] = pPartyChat;

	CUIControl* pToallChat = new CUIControl;
	pToallChat->CreateSub ( this, "CHAT_TOALL_STATE", UI_FLAG_BOTTOM, CHAT_TOALL_STATE );	
	RegisterControl ( pToallChat );
	m_pCHATSTATE[3] = pToallChat;

	CUIControl* pGuildChat = new CUIControl;
	pGuildChat->CreateSub ( this, "CHAT_GUILD_STATE", UI_FLAG_BOTTOM, CHAT_GUILD_STATE );	
	RegisterControl ( pGuildChat );
	m_pCHATSTATE[4] = pGuildChat;

	CUIControl* pAllianceChat = new CUIControl;
	pAllianceChat->CreateSub ( this, "CHAT_ALLIANCE_STATE", UI_FLAG_BOTTOM, CHAT_ALLIANCE_STATE );	
	RegisterControl ( pAllianceChat );
	m_pCHATSTATE[5] = pAllianceChat;

	CUIControl* pRegionChat = new CUIControl;
	pRegionChat->CreateSub ( this, "CHAT_REGION_STATE", UI_FLAG_BOTTOM, CHAT_REGION_STATE );	
	RegisterControl ( pRegionChat );
	m_pCHATSTATE[6] = pRegionChat;

	DO_CHAT_STATE( 0 );
	CBasicButton* pButton = new CBasicButton;
	pButton->CreateSub ( this, "CHAT_MACRO_BUTTON", UI_FLAG_BOTTOM, CHAT_MACRO_BUTTON );
	pButton->CreateFlip ( "CHAT_MACRO_BUTTON_F", CBasicButton::CLICK_FLIP );
	pButton->CreateMouseOver ( "CHAT_MACRO_BUTTON_F" );
	pButton->SetUseGlobalAction ( TRUE );
	RegisterControl ( pButton );
//	m_pChatShowFlagButton = pButton;
}

void CBasicChatLeftBar::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case CHAT_MACRO_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( dwMsg & UIMSG_LB_UP )
				{
					if ( !CInnerInterface::GetInstance().IsVisibleGroup ( CHATMACRO_WINDOW ) )
					{
						CInnerInterface::GetInstance().GetChatMacro();
						CInnerInterface::GetInstance().ShowGroupFocus ( CHATMACRO_WINDOW );
					}
					else
					{
						CInnerInterface::GetInstance().HideGroup ( CHATMACRO_WINDOW );
					}
				}
			}
		}	
		break;

	case CHAT_NORMAL_STATE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( UIMSG_LB_DOWN & dwMsg )
				{
					AddMessageEx ( UIMSG_MOUSEIN_PRIVATE_CHAT );
				}
			}			
		}
		break;

	case CHAT_PRIVATE_STATE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( UIMSG_LB_DOWN & dwMsg )
				{
					AddMessageEx ( UIMSG_MOUSEIN_PARTY_CHAT );
				}
			}			
		}
		break;

	case CHAT_PARTY_STATE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( UIMSG_LB_DOWN & dwMsg )
				{
					AddMessageEx ( UIMSG_MOUSEIN_TOALL_CHAT );
				}
			}			
		}
		break;

	case CHAT_TOALL_STATE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( UIMSG_LB_DOWN & dwMsg )
				{
					AddMessageEx ( UIMSG_MOUSEIN_GUILD_CHAT );
				}
			}
		}
		break;

	case CHAT_GUILD_STATE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( UIMSG_LB_DOWN & dwMsg )
				{
					AddMessageEx ( UIMSG_MOUSEIN_ALLIANCE_CHAT );
				}
			}
		}
		break;

	case CHAT_ALLIANCE_STATE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( UIMSG_LB_DOWN & dwMsg )
				{
					AddMessageEx ( UIMSG_MOUSEIN_REGION_CHAT );
				}
			}
		}
		break;

	case CHAT_REGION_STATE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( UIMSG_LB_DOWN & dwMsg )
				{
					AddMessageEx ( UIMSG_MOUSEIN_NORMAL_CHAT );
				}
			}
		}
		break;
	}
}

void CBasicChatLeftBar::DO_CHAT_STATE ( int nSTATE )
{
	if ( nSTATE < 0 || TOTAL_CHAT_STATE <= nSTATE )
		return ;

	for ( int i = 0; i < TOTAL_CHAT_STATE; ++i )
	{
		m_pCHATSTATE[i]->SetVisibleSingle ( FALSE );
	}

	m_pCHATSTATE[nSTATE]->SetVisibleSingle ( TRUE );
}