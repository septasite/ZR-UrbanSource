#include "StdAfx.h"
#include "RebirthDialogue.h"
#include "BasicLineBox.h"
#include "BasicTextButton.h"

#include "BasicLineBoxEx.h"
#include "BasicTextBoxEx.h"

#include "../EngineLib/DxCommon/DxFontMan.h"
#include "GameTextControl.h"
#include "GLGaeaClient.h"
#include "DxGlobalStage.h"
#include "InnerInterface.h"
#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const float CRebirthDialogue::fDEFAULT_TIME_LEFT = 5.0f;
const float CRebirthDialogue::fDEFAULT_SELECT_TIME_LEFT = 10.0f;

CRebirthDialogue::CRebirthDialogue ()
	: m_pTextBox(NULL)
    , m_pCheckPointButton(NULL)
	, m_pCurrentPositionButton(NULL)
	, m_pRecoveryExpButton(NULL)
	, m_pDummy_1BUTTON(NULL)
	, m_pDummy_2BUTTON_L(NULL)
	, m_pDummy_2BUTTON_R(NULL)
	, m_bDO_ACTION(false)
	, m_CallerID(NO_ID)
	, m_fTIME_LEFT(fDEFAULT_TIME_LEFT)
	, m_fSelTIME_LEFT( fDEFAULT_SELECT_TIME_LEFT )
	, m_nACTION(NO_ID)
	, m_bDONE_ACTION(false)
	, m_bAutoRebirth( false )
{
}

CRebirthDialogue::~CRebirthDialogue ()
{
}

void CRebirthDialogue::CreateSubControl ()
{
	int nTextAlign = TEXT_ALIGN_LEFT;
	CD3DFontPar* pFont6Shadow = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 7, _DEFAULT_FONT_SHADOW_FLAG );
	CD3DFontPar* pFont8Shadow = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, _DEFAULT_FONT_SHADOW_FLAG );
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_SHADOW_FLAG );
	CD3DFontPar* pFont10 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10,_DEFAULT_FONT_SHADOW_FLAG );
	CD3DFontPar* pFont12 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 12,  _DEFAULT_FONT_SHADOW_FLAG );

	const int nAlignLeft = TEXT_ALIGN_LEFT;
	const int nAlignCenter = TEXT_ALIGN_CENTER_X;		
	const DWORD& dwSilver = NS_UITEXTCOLOR::SILVER;
	const DWORD& dwWhite = NS_UITEXTCOLOR::WHITE;
	const DWORD& dwSubTitle = NS_UITEXTCOLOR::PALEGOLDENROD;

	{
		m_bg_white = new CUIControl;
		m_bg_white->CreateSub ( this, "RNREBIRTH_DIALOGUE", UI_FLAG_DEFAULT);	
		m_bg_white->SetVisibleSingle ( TRUE );
		RegisterControl ( m_bg_white );
	} 

	{
		m_battle_logo = new CUIControl;
		m_battle_logo->CreateSub ( this, "REBIRTH_BATTLE_LOGO", UI_FLAG_DEFAULT);	
		m_battle_logo->SetVisibleSingle ( TRUE );
		RegisterControl ( m_battle_logo );
	}

	{
	CBasicLineBox* pLineBox = new CBasicLineBoxEx;
	pLineBox->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBox->CreateBaseBoxDialogueWhite ( "REBIRTH_DIALOGUE_LINE_BOX" );
	RegisterControl ( pLineBox );	
	
	pLineBox = new CBasicLineBoxEx;
	pLineBox->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBox->CreateBaseBoxDialogueWhite ( "REBIRTH_DIALOGUE_LINE_BOX1" );
	RegisterControl ( pLineBox );

	pLineBox = new	CBasicLineBoxEx;
	pLineBox->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBox->CreateBaseBoxDialogueWhite ( "REBIRTH_DIALOGUE_LINE_BOX2" );
	RegisterControl ( pLineBox );
	}
	CBasicTextBox* pTextBox = new CBasicTextBox;
	pTextBox->CreateSub ( this, "REBIRTH_DIALOGUE_TEXTBOX", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
    pTextBox->SetFont ( pFont12 );
	pTextBox->SetTextAlign ( TEXT_ALIGN_CENTER_X );
	pTextBox->SetPartInterval ( 5.0f );
	RegisterControl ( pTextBox );
	m_pTextBox = pTextBox;
	
	pTextBox = CreateStaticControl ( "REBIRTH_DIALOGUE_BUY_MESSAGE", pFont10, nTextAlign );
	pTextBox->AddTextNoSplit ( (char*)ID2GAMEWORD ( "REBIRTH_BUTTON", 6 ) ,dwWhite);

	m_pCheckPointButton = CreateTextButton24 ( "REBIRTH_DIALOGUE_CHECKPOINT", REBIRTH_CHECK_POINT, (char*)ID2GAMEWORD ( "REBIRTH_BUTTON", 0 ) );
	m_pCurrentPositionButton = CreateTextButton24 ( "REBIRTH_DIALOGUE_CURRENT_POSITION", REBIRTH_CURRENT_POSITION, (char*)ID2GAMEWORD ( "REBIRTH_BUTTON", 1 ) );
	m_pRecoveryExpButton = CreateTextButton24 ( "REBIRTH_DIALOGUE_RECOVERY_EXP", REBIRTH_RECOVERY_EXP, (char*)ID2GAMEWORD ( "REBIRTH_BUTTON", 2 ) );
	m_pADD = CreateTextButton24 ( "REBIRTH_DIALOGUE_BUY", REBIRTH_DIALOGUE_BUY, (char*)ID2GAMEWORD ( "REBIRTH_BUTTON", 4 ) );
	m_pLogo = CreateFlipButton ( "REBIRTH_ROSARY_LOGO", "REBIRTH_ROSARY_LOGO" , REBIRTH_ROSARY_LOGO);

	m_pDummy_1BUTTON = CreateDummyControl ( "REBIRTH_DIALOGUE_1_BUTTON" );
	m_pDummy_2BUTTON_L = CreateDummyControl ( "REBIRTH_DIALOGUE_2_BUTTON_L" );
	m_pDummy_2BUTTON_R = CreateDummyControl ( "REBIRTH_DIALOGUE_2_BUTTON_R" );
}

CUIControl*	CRebirthDialogue::CreateDummyControl ( char* szKeyword )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szKeyword );
	pControl->SetVisibleSingle ( FALSE );
	RegisterControl ( pControl );
	return pControl;
}

CBasicTextButton* CRebirthDialogue::CreateTextButton ( char* szButton, UIGUID ControlID , char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE14;
	CBasicTextButton* pButton = new CBasicTextButton;
	pButton->CreateSub ( this, "BASIC_TEXT_BUTTON14", UI_FLAG_XSIZE, ControlID );
	pButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::CLICK_FLIP, szText );
	RegisterControl ( pButton );
	return pButton;
}
CBasicTextButton*  CRebirthDialogue::CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE24;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON24", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButton ( szButton, nBUTTONSIZE, CBasicButton::CLICK_FLIP, szText , _DEFAULT_FONT_SHADOW_FLAG );
	RegisterControl ( pTextButton );
	return pTextButton;
}
CBasicButton* CRebirthDialogue::CreateFlipButton ( char* szButton, char* szButtonFlip, UIGUID ControlID )
{
	CBasicButton* pButton = new CBasicButton;
	pButton->CreateSub ( this, szButton, UI_FLAG_DEFAULT, ControlID );
	pButton->CreateFlip ( szButtonFlip, CBasicButton::RADIO_FLIP );
	pButton->SetControlNameEx ( szButton );
	RegisterControl ( pButton );
	return pButton;
}
CBasicTextBox* CRebirthDialogue::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword, UI_FLAG_DEFAULT, cID );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );	
	RegisterControl ( pStaticText );

	return pStaticText;
}

void CRebirthDialogue::SET_ITEMREBIRTH ( const bool& bItemRebirth, bool bAutoRebirth, bool bCantUseRebirth )
{
	m_bDO_ACTION = false;
	m_bDONE_ACTION = false;
	m_fTIME_LEFT = fDEFAULT_TIME_LEFT;
	m_fSelTIME_LEFT = fDEFAULT_SELECT_TIME_LEFT;

	m_bAutoRebirth = false;

	if( bCantUseRebirth )
	{
		m_pTextBox->SetText ( ID2GAMEINTEXT("REBIRTH_DIALOGUE_TEXT2") );
	}
	else
	{
		m_pTextBox->SetText ( ID2GAMEINTEXT("REBIRTH_DIALOGUE_TEXT") );
	}
	if ( m_bAutoRebirth )
	{
		CString strLeftTime;
		strLeftTime.Format ( "%1.0f %s", floor(m_fSelTIME_LEFT) + 1.0f, ID2GAMEWORD("WAITSERVER_TIMELEFT_UNIT"));		
		m_pTextBox->AddText ( strLeftTime );
	}

	bool bGuidBattleMap(false);
	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if( pLand )
	{
		bGuidBattleMap = ( pLand->m_bClubBattle || pLand->m_bClubDeathMatch || pLand->m_bSchoolWars || pLand->m_bRoyalRumble ); 
	}
	// eh dito? auto rebirth sa mapa sguro? yep pero di ko alam kung tama kase HAHAH pero walang effect wtf
	ShowButton ();

	if ( bItemRebirth && !bGuidBattleMap )	// ±ÍÈ¥ÁÖ, ¼±µµºÒ°¡Áö¿ªx, ±ÍÈ¥ºÒ°¡Áö¿ªx
	{
		{
			const UIRECT& rc2ButtonL_G = m_pDummy_2BUTTON_L->GetGlobalPos();
			const UIRECT& rc2ButtonL_L = m_pDummy_2BUTTON_L->GetLocalPos();
			
			m_pCheckPointButton->SetGlobalPos( rc2ButtonL_G );
			m_pCheckPointButton->SetLocalPos( rc2ButtonL_L );
			m_pCheckPointButton->SetFlip( TRUE );
		}
		{
			const UIRECT& rc2ButtonR_G = m_pDummy_2BUTTON_R->GetGlobalPos();
			const UIRECT& rc2ButtonR_L = m_pDummy_2BUTTON_R->GetLocalPos();

			m_pCurrentPositionButton->SetGlobalPos( rc2ButtonR_G );
			m_pCurrentPositionButton->SetLocalPos( rc2ButtonR_L );
			m_pCurrentPositionButton->SetFlip( TRUE );
		}

		m_pRecoveryExpButton->SetVisibleSingle ( FALSE );

		m_bAutoRebirth = bAutoRebirth;

	}
// °æÇèÄ¡È¸º¹_Á¤ÀÇ_Normal
/*#if defined( _RELEASED ) || defined ( KRT_PARAM ) || defined ( KR_PARAM )
	else if ( !bCantUseRebirth && !bGuidBattleMap )	// ±ÍÈ¥ÁÖx, ±ÍÈ¥ºÒ°¡Áö¿ªx, ¼±µµÀüÁö¿ªx
	{
		{
			const UIRECT& rc2ButtonL_G = m_pDummy_2BUTTON_L->GetGlobalPos();
			const UIRECT& rc2ButtonL_L = m_pDummy_2BUTTON_L->GetLocalPos();
			
			m_pCheckPointButton->SetGlobalPos( rc2ButtonL_G );
			m_pCheckPointButton->SetLocalPos( rc2ButtonL_L );
			m_pCheckPointButton->SetFlip( TRUE );
		}
		
		{
			const UIRECT& rc2ButtonR_G = m_pDummy_2BUTTON_R->GetGlobalPos();
			const UIRECT& rc2ButtonR_L = m_pDummy_2BUTTON_R->GetLocalPos();

			m_pRecoveryExpButton->SetGlobalPos( rc2ButtonR_G );
			m_pRecoveryExpButton->SetLocalPos( rc2ButtonR_L );
			m_pRecoveryExpButton->SetFlip( TRUE );
		}

		{
			m_pCurrentPositionButton->SetVisibleSingle ( FALSE );
		}
	}
#endif*/
	else
	{
		{
			const UIRECT& rc1BUTTON = m_pDummy_1BUTTON->GetGlobalPos ();
			D3DXVECTOR2 vPos ( rc1BUTTON.left, rc1BUTTON.top );
			m_pCheckPointButton->SetGlobalPos ( vPos );
			m_pCheckPointButton->SetFlip ( TRUE );
		}

		{
			m_pCurrentPositionButton->SetVisibleSingle ( FALSE );
			m_pRecoveryExpButton->SetVisibleSingle ( FALSE );
		}
	}
}

void CRebirthDialogue::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case REBIRTH_CHECK_POINT:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
                m_nACTION = REBIRTH_CHECK_POINT;
				DoACTION ();
				HideButton ();
			}
		}
        break;

	case REBIRTH_CURRENT_POSITION:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				m_nACTION = REBIRTH_CURRENT_POSITION;
				DoACTION ();
                HideButton ();
			}
		}
		break;
	case REBIRTH_RECOVERY_EXP:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				
				m_nACTION = REBIRTH_RECOVERY_EXP;
				DoACTION ();
                HideButton ();				
			}
		}
		break;
	}
}

void CRebirthDialogue::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIWindow::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

    if( m_bDO_ACTION )
	{
		m_fTIME_LEFT -= fElapsedTime;

		bool bTimeEvent = false;
		if ( m_fTIME_LEFT < -1.0f ) bTimeEvent = true;

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

			case REBIRTH_CURRENT_POSITION:
				{
					AddMessageEx ( UIMSG_MODAL_CANCEL );
					CInnerInterface::GetInstance().HideGroup ( GetWndID (), true );

					m_bDONE_ACTION = true;
				}
				break;
			case REBIRTH_RECOVERY_EXP:
				{
					AddMessageEx ( UIMSG_MODAL_CANCEL );
					m_bDONE_ACTION = true;
				}
				break;
			}
		}
		else
		{
			CString strLeftTime;
			strLeftTime.Format ( "%1.0f %s", floor(m_fTIME_LEFT) + 1.0f, ID2GAMEWORD("WAITSERVER_TIMELEFT_UNIT"));

			m_pTextBox->ClearText ();
			m_pTextBox->AddText ( ID2GAMEINTEXT("WAITSERVER_MESSAGE") );
			m_pTextBox->AddText ( strLeftTime );
		}	
	}

	else if ( m_bAutoRebirth )
	{
			m_fSelTIME_LEFT -= fElapsedTime;

			bool bTimeEvent = false;
			if ( m_fSelTIME_LEFT < -1.0f ) bTimeEvent = true;

			if ( bTimeEvent )
			{
				// Default ±ÍÈ¥ÁÖ »ç¿ë
				m_nACTION = REBIRTH_CURRENT_POSITION;
				
				DoACTION ();
				HideButton ();
			}
			else 
			{
				CString strLeftTime;
				strLeftTime.Format ( "%1.0f %s", floor(m_fSelTIME_LEFT) + 1.0f, ID2GAMEWORD("WAITSERVER_TIMELEFT_UNIT"));
		
				m_pTextBox->SetText ( ID2GAMEINTEXT("REBIRTH_DIALOGUE_TEXT") );
				m_pTextBox->AddText ( strLeftTime );
			}
	}

}


void CRebirthDialogue::HideButton ()                                                         
{
	m_pCheckPointButton->SetVisibleSingle ( FALSE );
	m_pCurrentPositionButton->SetVisibleSingle ( FALSE );
	m_pRecoveryExpButton->SetVisibleSingle( FALSE );
}

void CRebirthDialogue::ShowButton ()
{
	m_pCheckPointButton->SetVisibleSingle ( TRUE );
	m_pCurrentPositionButton->SetVisibleSingle ( TRUE );
	m_pRecoveryExpButton->SetVisibleSingle( TRUE );
}