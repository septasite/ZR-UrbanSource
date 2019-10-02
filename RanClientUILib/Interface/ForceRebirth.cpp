#include "StdAfx.h"
#include "ForceRebirth.h"
#include "BasicLineBox.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"

#include "GameTextControl.h"
#include "GLGaeaClient.h"
#include "DxGlobalStage.h"
#include "InnerInterface.h"
#include "../Interface/UIWindowEx.h"
#include "d3dfont.h"

#include "UITextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const float CForceRebirth::fDEFAULT_TIME_LEFT = 30.0f;
const float CForceRebirth::fDEFAULT_SELECT_TIME_LEFT = 10.0f;

CForceRebirth::CForceRebirth ()
	: m_pTextBox(NULL)
	, m_pGauge (NULL)
	, m_bDO_ACTION(false)
	, m_CallerID(NO_ID)
	, m_fTIME_LEFT(fDEFAULT_TIME_LEFT)
	, m_fSelTIME_LEFT( fDEFAULT_SELECT_TIME_LEFT )
	, m_fTime( 0.0f )
	, m_nACTION(NO_ID)
	, m_bDONE_ACTION(false)
{
}

CForceRebirth::~CForceRebirth ()
{
}

void CForceRebirth::CreateSubControl ()
{
	CD3DFontPar* pFont10 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 13, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );

	pTimerIcon = CreateControl ( "FORCE_REBIRTH_WATCH_ICON" );

	m_pGauge = new CBasicProgressBar;
	m_pGauge->CreateSub ( this, "FORCE_REBIRTH_BLANK_LINE" );
	m_pGauge->CreateOverImage ( "FORCE_REBIRTH_GAUGE_LINE" );	
	m_pGauge->SetType(3);
	RegisterControl ( m_pGauge );

	CBasicTextBox* pTextBox = new CBasicTextBox;
	pTextBox->CreateSub ( this, "FORCE_REBIRTH_TEXT", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
    pTextBox->SetFont ( pFont10 );
	pTextBox->SetTextAlign ( TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
	pTextBox->SetPartInterval ( 5.0f );
	RegisterControl ( pTextBox );
	m_pTextBox = pTextBox;	
	m_pTextBox->SetVisibleSingle(TRUE);
}

void CForceRebirth::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIWindow::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

    if( m_bDO_ACTION )
	{
		m_fTIME_LEFT -= fElapsedTime;

		bool bTimeEvent = false;
		if ( m_fTIME_LEFT < 0.0f ) bTimeEvent = true;

		if ( bTimeEvent )
		{
			if ( m_bDONE_ACTION ) return ;

			switch ( m_nACTION )
			{
			case REBIRTH_CHECK_POINT:
				{
					AddMessageEx ( UIMSG_MODAL_OK );
					CInnerInterface::GetInstance().HideGroup ( GetWndID (), true );

					m_bDONE_ACTION = true;
				}
				break;
			}
		}
		else
		{
			m_fTime += fElapsedTime;
			if ( m_fTime > fDEFAULT_TIME_LEFT ) m_fTime = fDEFAULT_TIME_LEFT;

			const float fPercent = m_fTime / fDEFAULT_TIME_LEFT;
			m_pGauge->SetPercent ( fPercent );

			CString strLeftTime;
			strLeftTime.Format ( ID2GAMEINTEXT("NOTIFY_FORCE_REBIRTH"), (int)m_fTIME_LEFT+1 );

			m_pTextBox->ClearText ();
			m_pTextBox->SetText ( strLeftTime );
		}	
	}
}

void CForceRebirth::DoForceRebirth()
{
	m_nACTION = REBIRTH_CHECK_POINT;
	m_bDONE_ACTION = false;
	m_fTIME_LEFT = fDEFAULT_TIME_LEFT;
	m_fSelTIME_LEFT = fDEFAULT_SELECT_TIME_LEFT;
	m_fTime = 0.0f;

	DoACTION();
}