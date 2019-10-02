#include "StdAfx.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "GLGaeaClient.h"
#include "GLCharacter.h"
#include "InnerInterface.h"
#include ".\qboxbutton.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "CharacterEnum.h"



CQBoxButton::CQBoxButton(void) :
	m_bQBoxEnable(TRUE),
	m_bQBoxAlarm(FALSE),
	m_fBLINK_TIME(0.0f)
{
	for ( int i = 0; i < QBOX_SIZE; ++i )
	{
		m_pQBoxButton[i] = NULL;
	}
}

CQBoxButton::~CQBoxButton(void)
{
}

void CQBoxButton::SetQBoxEnable( bool bQBoxEnable )
{
	if( m_bQBoxEnable != bQBoxEnable )
	{
		GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
		if( pCharacter->IsPartyMem() && pCharacter->IsPartyMaster() == FALSE )
		{
			m_bQBoxAlarm = TRUE;
			m_pBoxLock->SetVisibleSingle ( !m_bQBoxEnable );
		}
	}

	m_bQBoxEnable = bQBoxEnable;

	for ( int i = 0; i < QBOX_SIZE; ++i )
	{
		m_pQBoxButton[i]->SetFlip( m_bQBoxEnable );
	}
	m_pBoxLock->SetVisibleSingle ( !m_bQBoxEnable );
}


void CQBoxButton::CreateSubControl ()
{
	CString strImage[QBOX_SIZE] =
	{
		"QBOX_BUTTON_BUTTON",
		"QBOX_BUTTON_BUTTON",
		"Q_BOX_SPEED_UP",
		"Q_BOX_CRAZY_TIME",
		"Q_BOX_POWER_UP",
		"Q_BOX_EXP_TIME",
		"Q_BOX_LUCKY",
		"Q_BOX_SPEED_UP_MAX",
		"Q_BOX_MADNESS_TIME",
		"Q_BOX_POWER_UP_MAX",
	};

	CString strImage_f[QBOX_SIZE] =
	{
		"QBOX_BUTTON_BUTTON_F",
		"QBOX_BUTTON_BUTTON_F",
		"Q_BOX_SPEED_UP_F",
		"Q_BOX_CRAZY_TIME_F",
		"Q_BOX_POWER_UP_F",
		"Q_BOX_EXP_TIME_F",
		"Q_BOX_LUCKY_F",
		"Q_BOX_SPEED_UP_MAX_F",
		"Q_BOX_MADNESS_TIME_F",
		"Q_BOX_POWER_UP_MAX_F",
	};
		
	for ( int i = 0; i < QBOX_SIZE; ++i )
	{
		m_pQBoxButton[i] = new CBasicButton;
		m_pQBoxButton[i]->CreateSub ( this,strImage[i].GetString(), UI_FLAG_DEFAULT, QBOX_ON_OFF_BUTTON + i);
		m_pQBoxButton[i]->CreateFlip ( strImage_f[i].GetString(), CBasicButton::RADIO_FLIP );
		m_pQBoxButton[i]->SetUseGlobalAction ( TRUE );
		m_pQBoxButton[i]->SetFlip( m_bQBoxEnable );
		m_pQBoxButton[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pQBoxButton[i] );
	}

	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, "QBOX_ALARM_BLINK" );
	pControl->SetVisibleSingle ( FALSE );
	RegisterControl ( pControl );
	m_pAlarmBlink = pControl;

	m_pBoxLock = new CUIControl;
	m_pBoxLock->CreateSub ( this, "QBOX_BUTTON_BUTTON_LOCK" );
	m_pBoxLock->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pBoxLock );

	m_pQBoxButton[1]->SetVisibleSingle ( TRUE );
}

void CQBoxButton::Start( UIGUID ImageID )
{
	int nImageID =  ImageID;
	m_pQBoxButton[nImageID]->SetVisibleSingle( TRUE ) ;
}

void CQBoxButton::Change( UIGUID ImageID )
{
	for ( int i = 0; i < QBOX_SIZE; ++i )
	{
		m_pQBoxButton[i]->SetVisibleSingle ( FALSE );
	}

	int nImageID =  ImageID;
	m_pQBoxButton[nImageID]->SetVisibleSingle( TRUE ) ;
}

void CQBoxButton::Stop()
{
	for ( int i = 0; i < QBOX_SIZE; ++i )
	{
		m_pQBoxButton[i]->SetVisibleSingle ( FALSE );
	}

	m_pQBoxButton[1]->SetVisibleSingle ( TRUE );
}

void CQBoxButton::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	const float fBLINK_TIME_LOOP = 0.2f;

	if ( m_bQBoxAlarm )
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

void CQBoxButton::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case	QBOX_DEFAULT:
	case 	QBOX_SPEED_UP:
	case 	QBOX_CRAZY_TIME:
	case 	QBOX_POWER_UP:
	case 	QBOX_EXP_TIME:
	case 	QBOX_LUCKY:
	case 	QBOX_SPEED_UP_M:
	case 	QBOX_MADNESS:
	case 	QBOX_ATTACK_UP_M:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( ID2GAMEINTEXT( "QBOX_BUTTON_MESSAGE" ), NS_UITEXTCOLOR::WHITE  );				
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
				if( !pCharacter->IsPartyMem() || pCharacter->IsPartyMaster() )
				{
					m_bQBoxEnable = !m_bQBoxEnable;

					for ( int i = 0; i < QBOX_SIZE; ++i )
					{
						m_pQBoxButton[i]->SetFlip( m_bQBoxEnable );
					}
					if( pCharacter->IsPartyMaster() )
					{
						pCharacter->ReqQBoxEnableState(m_bQBoxEnable);		
					}
					m_pBoxLock->SetVisibleSingle ( !m_bQBoxEnable );
				}
				else
				{
					m_bQBoxAlarm = FALSE;
					m_pAlarmBlink->SetVisibleSingle ( FALSE );
					m_pBoxLock->SetVisibleSingle ( !m_bQBoxEnable );
				}
			}
		}
		break;
	}
}
