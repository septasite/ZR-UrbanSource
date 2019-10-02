#include "StdAfx.h"
#include "IMAlarm.h"
#include "../EngineUILib/GUInterface/BasicButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const float CItemMix::fBLINK_TIME_LOOP = 0.2f;

CItemMix::CItemMix () :
	m_pItemMixBlink ( NULL ),
	m_fBLINK_TIME ( 0.0f ),
	m_bItemMix( false )
{
}

CItemMix::~CItemMix ()
{
}

void CItemMix::CreateSubControl ()
{
	CBasicButton* pItemMix = new CBasicButton;
	pItemMix->CreateSub ( this, "ITEM_MIX_BUTTON", UI_FLAG_DEFAULT, ITEM_MIX_BUTTON );
//#ifdef CH_PARAM // Áß±¹ ÀÎÅÍÆäÀÌ½º º¯°æ
//	pItemMix->CreateMouseOver( "QUEST_ALARM_BUTTON_F" );
//#else
	pItemMix->CreateFlip ( "ITEM_MIX_BUTTON_F", CBasicButton::CLICK_FLIP );
	pItemMix->SetUseDynamic ( TRUE );
//#endif
	pItemMix->SetUseGlobalAction ( TRUE );
	RegisterControl ( pItemMix );

}

void CItemMix::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( m_bItemMix )
	{		
		m_fBLINK_TIME += fElapsedTime;
		if ( fBLINK_TIME_LOOP <= m_fBLINK_TIME )
		{
			BOOL bVisible = m_pItemMixBlink->IsVisible ();
			m_pItemMixBlink->SetVisibleSingle ( !bVisible );
			m_fBLINK_TIME = 0.0f;
		}
	}
}


void CItemMix::SetVisibleSingle ( BOOL bVisible )
{
	CUIGroup::SetVisibleSingle ( bVisible );

	if ( !bVisible )
	{
		m_pItemMixBlink->SetVisibleSingle ( FALSE );
		m_bItemMix = false;		
	}
}