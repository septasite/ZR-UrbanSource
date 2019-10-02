#include "StdAfx.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "GLGaeaClient.h"
#include "GLCharacter.h"
#include "InnerInterface.h"
#include ".\TWbutton.h"
#include "GameTextControl.h"
#include "UITextControl.h"
//#include "../EngineUIlib/GUInterface/BasicProgressBar.h"
#include "BasicLineBoxEx.h"

CTWButton::CTWButton(void) :
	m_pTWButton(NULL),
	m_bTWEnable(TRUE),
	m_bTWAlarm(FALSE),
	//m_BoxGauge(NULL),
	//added by : tobets | 08-03-2012 | add TW new interface
	m_fBLINK_TIME(0.0f)
{
}

CTWButton::~CTWButton(void)
{
}

void CTWButton::SetTWEnable( bool bTWEnable )
{
	if( m_bTWEnable != bTWEnable )
	{
		GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
		if( pCharacter->IsPartyMem() && pCharacter->IsPartyMaster() == FALSE )
		{
			m_bTWAlarm = TRUE;
			m_pTWLock->SetVisibleSingle ( !m_bTWEnable );
		}
	}

	m_bTWEnable = bTWEnable;
	m_pTWButton->SetFlip( m_bTWEnable );
	m_pTWLock->SetVisibleSingle ( !m_bTWEnable );
}

void CTWButton::CreateSubControl ()
{
	m_pTWButton = new CBasicButton;
	m_pTWButton->CreateSub ( this, "TW_BUTTON_BUTTON", UI_FLAG_DEFAULT, TW_ON_OFF_BUTTON );
	m_pTWButton->CreateFlip ( "TW_BUTTON_BUTTON_F", CBasicButton::RADIO_FLIP );
	m_pTWButton->SetUseGlobalAction ( TRUE );
	m_pTWButton->SetFlip( m_bTWEnable );
	RegisterControl ( m_pTWButton );

	{
		CUIControl* pControl = new CUIControl;
		pControl->CreateSub ( this, "TW_ALARM_BLINK" );
		pControl->SetVisibleSingle ( FALSE );
		RegisterControl ( pControl );
		m_pAlarmBlink = pControl;
	}

	CString strTW[TW_SIZE] =
	{
		"TW_BUTTON_BUTTON",
		"Q_BOX_CRAZY_TIME",
		"Q_BOX_EXP_TIME",
		"Q_BOX_LUCKY",
		"Q_BOX_MADNESS_TIME",
		"Q_BOX_POWER_UP",
		"Q_BOX_POWER_UP_MAX",
		"Q_BOX_SPEED_UP",
		"Q_BOX_SPEED_UP_MAX",
	};
		
		for ( int i = 0; i < TW_SIZE; ++i )
		{
		m_pTWImage[i] = new CUIControl;
		m_pTWImage[i]->CreateSub ( this, strTW[i].GetString() );
		m_pTWImage[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pTWImage[i] );
		}

	/*{
		CBasicProgressBar* pHP = new CBasicProgressBar;
		pHP->CreateSub ( this, "BAR_GAUGE_TEMP" );
		pHP->CreateOverImage ( "BAR_GAUGE_TEMP"  );	
		pHP->SetType ( 1 );
		RegisterControl ( pHP );
		m_BoxGauge = pHP;	
		}*/

		{
		CUIControl* pControl = new CUIControl;
		pControl->CreateSub ( this, "TW_BUTTON_BUTTON_LOCK" );
		pControl->SetVisibleSingle ( FALSE );
		RegisterControl ( pControl );
		m_pTWLock = pControl;
		}

}



bool CTWButton::SetImageBox ( UIGUID cID, float TimeBox )
{
	int m_bSetImageID = cID;
	m_pTWImage[m_bSetImageID]->SetVisibleSingle( TRUE ) ;
	//m_BoxGauge->SetVisibleSingle( TRUE ) ;
	
	m_CurrentTimeBox = TimeBox;
	m_RemainTimeBox = m_CurrentTimeBox;

	return true;
}

bool CTWButton::SetImageStop ()
{
	for ( int i = 0; i < TW_SIZE; ++i )
	{
	m_pTWImage[i]->SetVisibleSingle ( FALSE );
	}
	//m_BoxGauge->SetVisibleSingle( FALSE ) ;
	return true;
}

bool CTWButton::SetChangeImage ( UIGUID cID )
{

	for ( int i = 0; i < TW_SIZE; ++i )
	{
	m_pTWImage[i]->SetVisibleSingle ( FALSE );
	}

	int m_bSetImageID = cID;
	m_pTWImage[m_bSetImageID]->SetVisibleSingle( TRUE ) ;
	//m_BoxGauge->SetVisibleSingle( TRUE ) ;
	return true;
}

void CTWButton::SetTimeConsume ( int nNOW, int nMAX )
{
	//const float fPercent = float(nNOW) / float(nMAX);

	//m_BoxGauge->SetPercent ( fPercent );
}

void CTWButton::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	m_RemainTimeBox -= fElapsedTime;

	SetTimeConsume( m_RemainTimeBox, m_CurrentTimeBox );

	if ( !IsVisible () ) return ;
	const float fBLINK_TIME_LOOP = 0.2f;


	if ( m_bTWAlarm )
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

void CTWButton::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case TW_ON_OFF_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( ID2GAMEINTEXT( "TW_BUTTON_MESSAGE" ), NS_UITEXTCOLOR::WHITE  );				
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
				if( !pCharacter->IsPartyMem() || pCharacter->IsPartyMaster() )
				{
					m_bTWEnable = !m_bTWEnable;
					m_pTWButton->SetFlip( m_bTWEnable );
					//added by : tobets | 08-03-2012 | add TW new interface
					m_pTWLock->SetVisibleSingle ( !m_bTWEnable );
				}else{
					m_bTWAlarm = FALSE;
					m_pAlarmBlink->SetVisibleSingle ( FALSE );
					//added by : tobets | 08-03-2012 | add TW new interface
					m_pTWLock->SetVisibleSingle ( !m_bTWEnable );
				}
			}
		}
		break;
	}
}

