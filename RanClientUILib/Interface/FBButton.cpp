#include "StdAfx.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "GLGaeaClient.h"
#include "GLCharacter.h"
#include "InnerInterface.h"
#include ".\FBbutton.h"
#include "GameTextControl.h"
#include "UITextControl.h"
//#include "../EngineUIlib/GUInterface/BasicProgressBar.h"
#include "BasicLineBoxEx.h"

CFBButton::CFBButton(void) :
	m_pFBButton(NULL),
	m_bFBEnable(TRUE),
	m_bFBAlarm(FALSE),
	//m_BoxGauge(NULL),
	//added by : tobets | 08-03-2012 | add FB new interface
	m_fBLINK_TIME(0.0f)
{
}

CFBButton::~CFBButton(void)
{
}

void CFBButton::SetFBEnable( bool bFBEnable )
{
	if( m_bFBEnable != bFBEnable )
	{
		GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
		if( pCharacter->IsPartyMem() && pCharacter->IsPartyMaster() == FALSE )
		{
			m_bFBAlarm = TRUE;
			m_pFBLock->SetVisibleSingle ( !m_bFBEnable );
		}
	}

	m_bFBEnable = bFBEnable;
	m_pFBButton->SetFlip( m_bFBEnable );
	m_pFBLock->SetVisibleSingle ( !m_bFBEnable );
}

void CFBButton::CreateSubControl ()
{
	m_pFBButton = new CBasicButton;
	m_pFBButton->CreateSub ( this, "FB_BUTTON_BUTTON", UI_FLAG_DEFAULT, FB_ON_OFF_BUTTON );
	m_pFBButton->CreateFlip ( "FB_BUTTON_BUTTON_F", CBasicButton::RADIO_FLIP );
	m_pFBButton->SetUseGlobalAction ( TRUE );
	m_pFBButton->SetFlip( m_bFBEnable );
	RegisterControl ( m_pFBButton );

	{
		CUIControl* pControl = new CUIControl;
		pControl->CreateSub ( this, "FB_ALARM_BLINK" );
		pControl->SetVisibleSingle ( FALSE );
		RegisterControl ( pControl );
		m_pAlarmBlink = pControl;
	}

	CString strFB[FB_SIZE] =
	{
		"FB_BUTTON_BUTTON",
		"Q_BOX_CRAZY_TIME",
		"Q_BOX_EXP_TIME",
		"Q_BOX_LUCKY",
		"Q_BOX_MADNESS_TIME",
		"Q_BOX_POWER_UP",
		"Q_BOX_POWER_UP_MAX",
		"Q_BOX_SPEED_UP",
		"Q_BOX_SPEED_UP_MAX",
	};
		
		for ( int i = 0; i < FB_SIZE; ++i )
		{
		m_pFBImage[i] = new CUIControl;
		m_pFBImage[i]->CreateSub ( this, strFB[i].GetString() );
		m_pFBImage[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pFBImage[i] );
		}

	/*{
		CBasicProgressBar* pHP = new CBasicProgressBar;
		pHP->CreateSub ( this, "BAR_GAUGE_TEMPK" );
		pHP->CreateOverImage ( "BAR_GAUGE_TEMP"  );	
		pHP->SetType ( 1 );
		RegisterControl ( pHP );
		m_BoxGauge = pHP;	
		}*/

		{
		CUIControl* pControl = new CUIControl;
		pControl->CreateSub ( this, "FB_BUTTON_BUTTON_LOCK" );
		pControl->SetVisibleSingle ( FALSE );
		RegisterControl ( pControl );
		m_pFBLock = pControl;
		}

}



bool CFBButton::SetImageBox ( UIGUID cID, float TimeBox )
{
	int m_bSetImageID = cID;
	m_pFBImage[m_bSetImageID]->SetVisibleSingle( TRUE ) ;
	//m_BoxGauge->SetVisibleSingle( TRUE ) ;
	
	m_CurrentTimeBox = TimeBox;
	m_RemainTimeBox = m_CurrentTimeBox;

	return true;
}

bool CFBButton::SetImageStop ()
{
	for ( int i = 0; i < FB_SIZE; ++i )
	{
	m_pFBImage[i]->SetVisibleSingle ( FALSE );
	}
	//m_BoxGauge->SetVisibleSingle( FALSE ) ;
	return true;
}

bool CFBButton::SetChangeImage ( UIGUID cID )
{

	for ( int i = 0; i < FB_SIZE; ++i )
	{
	m_pFBImage[i]->SetVisibleSingle ( FALSE );
	}

	int m_bSetImageID = cID;
	m_pFBImage[m_bSetImageID]->SetVisibleSingle( TRUE ) ;
	//m_BoxGauge->SetVisibleSingle( TRUE ) ;
	return true;
}

void CFBButton::SetTimeConsume ( int nNOW, int nMAX )
{
	//const float fPercent = float(nNOW) / float(nMAX);

	//m_BoxGauge->SetPercent ( fPercent );
}

void CFBButton::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	m_RemainTimeBox -= fElapsedTime;

	SetTimeConsume( m_RemainTimeBox, m_CurrentTimeBox );

	if ( !IsVisible () ) return ;
	const float fBLINK_TIME_LOOP = 0.2f;


	if ( m_bFBAlarm )
	{		
		m_fBLINK_TIME += fElapsedTime;
		if ( fBLINK_TIME_LOOP <= m_fBLINK_TIME )
		{
			BOOL bVisible = m_pAlarmBlink->IsVisible ();
			m_pAlarmBlink->SetVisibleSingle ( !bVisible );
			m_fBLINK_TIME = 0.0f;
		}
	}
}

void CFBButton::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case FB_ON_OFF_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( ID2GAMEINTEXT( "FB_BUTTON_MESSAGE" ), NS_UITEXTCOLOR::WHITE  );				
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
				if( !pCharacter->IsPartyMem() || pCharacter->IsPartyMaster() )
				{
					m_bFBEnable = !m_bFBEnable;
					m_pFBButton->SetFlip( m_bFBEnable );
					//added by : tobets | 08-03-2012 | add FB new interface
					m_pFBLock->SetVisibleSingle ( !m_bFBEnable );
				}else{
					m_bFBAlarm = FALSE;
					m_pAlarmBlink->SetVisibleSingle ( FALSE );
					//added by : tobets | 08-03-2012 | add FB new interface
					m_pFBLock->SetVisibleSingle ( !m_bFBEnable );
				}
			}
		}
		break;
	}
}

