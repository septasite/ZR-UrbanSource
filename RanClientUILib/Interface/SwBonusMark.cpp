#include "StdAfx.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "../EngineUIlib/GUInterface/BasicProgressBar.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "BasicLineBoxEx.h"
#include "InnerInterface.h"
#include "SwBonusMark.h"
#include "GLGaeaClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSwBonusMark::CSwBonusMark()
{
}

CSwBonusMark::~CSwBonusMark()
{
}

void CSwBonusMark::CreateSubControl ()
{
	/*m_pImage =  new CBasicButton;
	m_pImage->CreateSub ( this, "SW_BONUS_IMAGE", UI_FLAG_DEFAULT, SWIconOnMouse );	
	m_pImage->SetUseGlobalAction ( TRUE );
	RegisterControl ( m_pImage );
	//m_pImage->SetVisibleSingle(FALSE);*/

	CString strBuffImg[3] = 
	{
		"CTF_REWARD_BUFF_TOP_TEXT00",
		"CTF_REWARD_BUFF_TOP_TEXT01",
		"CTF_REWARD_BUFF_TOP_TEXT02",

	};
	for( int i = 0; i < 3; ++i )
	{
		m_pRewardBuffBack[i] = new CUIControl;
		m_pRewardBuffBack[i]->CreateSub( this,(char*)strBuffImg[i].GetString(), UI_FLAG_DEFAULT, CTF_REWARD_BUFF_TOP_TEXT00+i );
		m_pRewardBuffBack[i]->SetVisibleSingle( TRUE );
		RegisterControl( m_pRewardBuffBack[i] );			
	
	}
}

void CSwBonusMark::SetSwBonus( bool isWinner )
{
	for( int i = 0; i < 3; ++i )
	{
		if ( isWinner )		m_pRewardBuffBack[i]->SetVisibleSingle( TRUE );
		else				m_pRewardBuffBack[i]->SetVisibleSingle( FALSE );
	}
}
void CSwBonusMark::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
switch ( ControlID )
	{
	case CTF_REWARD_BUFF_TOP_TEXT00:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Gain: X2 EXP", NS_UITEXTCOLOR::LIME  );
			}
		}
		break;
	case CTF_REWARD_BUFF_TOP_TEXT01:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Gain: X2 GOLD", NS_UITEXTCOLOR::LIME  );
			}
		}
		break;
	case CTF_REWARD_BUFF_TOP_TEXT02:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Gain: X2 ITEMDROP", NS_UITEXTCOLOR::LIME  );
			}
		}
		break;
	}
}