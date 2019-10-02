#include "StdAfx.h"
#include "MiniPartySlot.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "BasicLineBox.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "BasicLineBoxEx.h"
#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMiniPartySlot::CMiniPartySlot () :
	m_pPlayerName ( NULL ),
	m_bMaster ( FALSE )
{
	for ( int i = 0; i < 3; i++ )
	{
		m_pSchool[i] = NULL;	
	}

	memset( m_pNumber, 0, sizeof(m_pNumber) );
}

CMiniPartySlot::~CMiniPartySlot ()
{
}

void CMiniPartySlot::CreateSubControl ()
{
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	CD3DFontPar* pFont9Default = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII  );
	int nTextAlign = TEXT_ALIGN_CENTER_X;
	int nTextAlignLeft = TEXT_ALIGN_LEFT;
	int nTextAlignRight = TEXT_ALIGN_RIGHT;
	D3DCOLOR dwFontColor = NS_UITEXTCOLOR::DEFAULT;
	D3DCOLOR dwNameColor = NS_UITEXTCOLOR::PARTYNAME;

	CBasicLineBox* pLineBoxCombo = new CBasicLineBox;
	pLineBoxCombo->CreateSub ( this, "BASIC_LINE_BOX_MINIPARTY", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBoxCombo->CreateBaseBoxMiniParty ( "MINIPARTY_SLOT_BACK" );
	RegisterControl ( pLineBoxCombo );

	{

			CBasicProgressBar*	pProgressBar0 = new CBasicProgressBar;
			pProgressBar0->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR0 );
			pProgressBar0->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_FIGHTER_M_OVER" );
			pProgressBar0->SetPercent ( 0.3f );
			pProgressBar0->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar0 );
			m_pHP0 = pProgressBar0;
			
			CBasicProgressBar*	pProgressBar1 = new CBasicProgressBar;
			pProgressBar1->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR1 );
			pProgressBar1->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_ARMS_M_OVER" );
			pProgressBar1->SetPercent ( 0.3f );
			pProgressBar1->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar1 );
			m_pHP1 = pProgressBar1;
			
			CBasicProgressBar*	pProgressBar2 = new CBasicProgressBar;
			pProgressBar2->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR2 );
			pProgressBar2->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_ARCHER_W_OVER" );
			pProgressBar2->SetPercent ( 0.3f );
			pProgressBar2->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar2 );
			m_pHP2 = pProgressBar2;
			
			CBasicProgressBar*	pProgressBar3 = new CBasicProgressBar;
			pProgressBar3->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR3 );
			pProgressBar3->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_SPIRIT_W_OVER" );
			pProgressBar3->SetPercent ( 0.3f );
			pProgressBar3->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar3 );
			m_pHP3 = pProgressBar3;
			
			CBasicProgressBar*	pProgressBar4 = new CBasicProgressBar;
			pProgressBar4->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR4 );
			pProgressBar4->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_EXTREME_M_OVER" );
			pProgressBar4->SetPercent ( 0.3f );
			pProgressBar4->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar4 );
			m_pHP4 = pProgressBar4;
			
			CBasicProgressBar*	pProgressBar5 = new CBasicProgressBar;
			pProgressBar5->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR5 );
			pProgressBar5->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_EXTREME_W_OVER" );
			pProgressBar5->SetPercent ( 0.3f );
			pProgressBar5->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar5 );
			m_pHP5 = pProgressBar5;
			
			CBasicProgressBar*	pProgressBar6 = new CBasicProgressBar;
			pProgressBar6->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR6 );
			pProgressBar6->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_FIGHTER_W_OVER" );
			pProgressBar6->SetPercent ( 0.3f );
			pProgressBar6->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar6 );
			m_pHP6 = pProgressBar6;
			
			CBasicProgressBar*	pProgressBar7 = new CBasicProgressBar;
			pProgressBar7->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR7 );
			pProgressBar7->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_ARMS_W_OVER" );
			pProgressBar7->SetPercent ( 0.3f );
			pProgressBar7->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar7 );
			m_pHP7 = pProgressBar7;
			
			CBasicProgressBar*	pProgressBar8 = new CBasicProgressBar;
			pProgressBar8->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR8 );
			pProgressBar8->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_ARCHER_M_OVER" );
			pProgressBar8->SetPercent ( 0.3f );
			pProgressBar8->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar8 );
			m_pHP8 = pProgressBar8;
			
			CBasicProgressBar*	pProgressBar9 = new CBasicProgressBar;
			pProgressBar9->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR9 );
			pProgressBar9->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_SPIRIT_M_OVER" );
			pProgressBar9->SetPercent ( 0.3f );
			pProgressBar9->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar9 );
			m_pHP9 = pProgressBar9;
			
			CBasicProgressBar*	pProgressBar10 = new CBasicProgressBar;
			pProgressBar10->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR10 );
			pProgressBar10->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_SCIENCE_M_OVER" );
			pProgressBar10->SetPercent ( 0.3f );
			pProgressBar10->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar10 );
			m_pHP10 = pProgressBar10;
			
			CBasicProgressBar*	pProgressBar11 = new CBasicProgressBar;
			pProgressBar11->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR11 );
			pProgressBar11->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_SCIENCE_W_OVER" );
			pProgressBar11->SetPercent ( 0.3f );
			pProgressBar11->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar11 );
			m_pHP11 = pProgressBar11;
			
			CBasicProgressBar*	pProgressBar12 = new CBasicProgressBar;
			pProgressBar12->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR12 );
			pProgressBar12->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_ASSASSIN_M_OVER" );
			pProgressBar12->SetPercent ( 0.3f );
			pProgressBar12->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar12 );
			m_pHP12 = pProgressBar12;
			
			CBasicProgressBar*	pProgressBar13 = new CBasicProgressBar;
			pProgressBar13->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR13 );
			pProgressBar13->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_ASSASSIN_W_OVER" );
			pProgressBar13->SetPercent ( 0.3f );
			pProgressBar13->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar13 );
			m_pHP13 = pProgressBar13;

			CBasicProgressBar*	pProgressBar14 = new CBasicProgressBar;
			pProgressBar14->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR14 );
			pProgressBar14->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_TESTING_W_OVER" );
			pProgressBar14->SetPercent ( 0.3f );
			pProgressBar14->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar14 );
			m_pHP14 = pProgressBar14;

			CBasicProgressBar*	pProgressBar15 = new CBasicProgressBar;
			pProgressBar15->CreateSub ( this, "MINIPARTY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR15 );
			pProgressBar15->CreateOverImage ( "MINIPARTY_PROGRESSBAR_SLOT_CLASS_TESTING_W_OVER" );
			pProgressBar15->SetPercent ( 0.3f );
			pProgressBar15->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar15 );
			m_pHP15 = pProgressBar15;


		
	}

	{//Add School
		CString strSchool[3] = 
		{
			"MINIPARTY_SLOT_SCHOOL0",
			"MINIPARTY_SLOT_SCHOOL1",
			"MINIPARTY_SLOT_SCHOOL2"
		};

		for ( int i = 0; i < 3; i++ )
		{
			m_pSchool[i] = CreateControl ( strSchool[i].GetString() );
		}
	}

	{
		CBasicLineBox* pLineBox1 = new CBasicLineBox;
		pLineBox1->CreateSub ( this, "BASIC_LINE_BOX_MINIPARTY", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pLineBox1->CreateBaseBoxMiniParty ( "MINIPARTY_BACK" );
		RegisterControl ( pLineBox1 );
	}

	{
		m_pMaster = CreateControl ( "MINIPARTY_NUMBER_M" );
		m_pNumberSlot = CreateStaticControl ( "MINIPARTY_NUMBER", pFont9, NS_UITEXTCOLOR::WHITE, nTextAlign );
	}

	m_pPlayerName = CreateStaticControl ( "MINIPARTY_SLOT_PLAYER_NAME", pFont9Default, NS_UITEXTCOLOR::WHITE, nTextAlignRight );
}

CUIControl*	CMiniPartySlot::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

CBasicTextBox* CMiniPartySlot::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	return pStaticText;
}

void CMiniPartySlot::SetNumber ( int nSlotNumber )
{
	if ( nSlotNumber < 0 && MAXPARTY <= nSlotNumber )
	{
		GASSERT ( 0 && "?????? ?????? ??? ?????." );
		return ;
	}

	m_pMaster->SetVisibleSingle ( FALSE );
	m_pNumberSlot->SetVisibleSingle ( FALSE );

	if ( nSlotNumber == 0 )
	{
		m_pMaster->SetVisibleSingle ( TRUE );
		m_pNumberSlot->SetVisibleSingle ( FALSE );
	}
	else
	{
		m_pNumberSlot->SetVisibleSingle ( TRUE );
	
		CString strNum;
		strNum.Format ( "%d", nSlotNumber );

		m_pNumberSlot->AddText ( strNum, NS_UITEXTCOLOR::WHITE );
	}
}

void CMiniPartySlot::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case HP_BAR:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR0:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR1:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR2:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR3:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR4:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR5:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR6:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR7:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR8:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR9:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR10:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR11:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR12:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR13:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR14:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	case HP_BAR15:
		{
			if ( CHECK_MOUSEIN_RBUPLIKE ( dwMsg ) )
			{
				AddMessageEx ( UIMSG_MOUSEIN_RB_EVENT );
			}
		}
		break;
	
	}
}

void CMiniPartySlot::SetClass ( int nClassType )
{
	//add class
	if ( nClassType < GLCI_FIGHTER_M && GLCI_TESTING_W < nClassType )
	{
		GASSERT ( 0 && "?????? ?????? ??? ?????." );
		return ;
	}

	m_pHP0->SetVisibleSingle ( FALSE );
	m_pHP1->SetVisibleSingle ( FALSE );
	m_pHP2->SetVisibleSingle ( FALSE );
	m_pHP3->SetVisibleSingle ( FALSE );
	m_pHP4->SetVisibleSingle ( FALSE );
	m_pHP5->SetVisibleSingle ( FALSE );
	m_pHP6->SetVisibleSingle ( FALSE );
	m_pHP7->SetVisibleSingle ( FALSE );
	m_pHP8->SetVisibleSingle ( FALSE );
	m_pHP9->SetVisibleSingle ( FALSE );
	m_pHP10->SetVisibleSingle ( FALSE );
	m_pHP11->SetVisibleSingle ( FALSE );
	m_pHP12->SetVisibleSingle ( FALSE );
	m_pHP13->SetVisibleSingle ( FALSE );
	m_pHP14->SetVisibleSingle ( FALSE );
	m_pHP15->SetVisibleSingle ( FALSE );


	if ( nClassType == 0 ) { m_pHP0->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 1 ) { m_pHP1->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 2 ) { m_pHP2->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 3 ) { m_pHP3->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 4 ) { m_pHP4->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 5 ) { m_pHP5->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 6 ) { m_pHP6->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 7 ) { m_pHP7->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 8 ) { m_pHP8->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 9 ) { m_pHP9->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 10 ) { m_pHP10->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 11 ) { m_pHP11->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 12 ) { m_pHP12->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 13 ) { m_pHP13->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 14 ) { m_pHP14->SetVisibleSingle ( TRUE ); }
	else if ( nClassType == 15 ) { m_pHP15->SetVisibleSingle ( TRUE ); }

}

void CMiniPartySlot::SetSchool ( int nSchoolType )
{
	//add class
	for ( int i = 0; i < 3; i++ )
	{
		m_pSchool[i]->SetVisibleSingle ( FALSE );
	}

	m_pSchool[nSchoolType]->SetVisibleSingle ( TRUE );
}

//void CMiniPartySlot::SetNameHover ()
//{
//	if ( m_pPlayerName ) m_pPlayerName->SetUseTextColor ( 0, TRUE );
//						 m_pPlayerName->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD );
//}

void CMiniPartySlot::SetNameColorDefault ()
{
	if ( m_pPlayerName ) m_pPlayerName->SetUseTextColor ( 0, FALSE );
						 m_pPlayerName->SetUseTextColor ( 0, FALSE );
}

void CMiniPartySlot::SetPlayerName ( CString strName )
{ 
	CString strLevel;
	strLevel.Format ( "%s", strName ); 
	if ( m_pPlayerName )	m_pPlayerName->SetOneLineText( strLevel, NS_UITEXTCOLOR::WHITE );
}

void CMiniPartySlot::SetPlayerNameColor ( int nPercent )
{
	if( nPercent == 0 )
	{
		if ( m_pPlayerName ) m_pPlayerName->SetUseTextColor ( 0, TRUE );
						 m_pPlayerName->SetUseTextColor ( 0, NS_UITEXTCOLOR::RED );
	}
	else
	{
		if ( m_pPlayerName ) m_pPlayerName->SetUseTextColor ( 0, FALSE );
						 m_pPlayerName->SetUseTextColor ( 0, FALSE );
	}
}

void CMiniPartySlot::IsPlayerSameMap ( BOOL bOK )
{
	if ( !bOK )
	{
		for ( int i = 0; i < 3; i++ )
		{
			m_pSchool[i]->SetVisibleSingle ( FALSE );
		}
	}
	else
	{
		for ( int i = 0; i < 3; i++ )
		{
			m_pSchool[i]->SetVisibleSingle ( TRUE );
		}
	}
}