#include "StdAfx.h"
#include "PartySlotDisplay.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "BasicLineBox.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"
#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPartySlotDisplay::CPartySlotDisplay () :
	m_pPlayerName ( NULL ),
	m_pPlayerHealth ( NULL ),
	m_bMaster ( FALSE )
{
	//add class
	for ( int i = 0; i < GLCI_NUM_NEWEST; i++ )
	{
		m_pClass[i] = NULL;
	}

	/*for ( int i = 0; i < GLSCHOOL_NUM; i++ )
	{
		m_pSchool[i] = NULL;	
	}*/
	memset( m_pNumber, 0, sizeof(m_pNumber) );
}

CPartySlotDisplay::~CPartySlotDisplay ()
{
}

void CPartySlotDisplay::CreateSubControl ()
{
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	int nTextAlign = TEXT_ALIGN_CENTER_X;
	int nTextAlignRight = TEXT_ALIGN_RIGHT;
	D3DCOLOR dwFontColor = NS_UITEXTCOLOR::DEFAULT;
	D3DCOLOR dwNameColor = NS_UITEXTCOLOR::PARTYNAME;

	CBasicLineBox* pLineBoxCombo = new CBasicLineBox;
	pLineBoxCombo->CreateSub ( this, "BASIC_LINE_BOX_MINIPARTY", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBoxCombo->CreateBaseBoxMiniParty ( "PARTYDISPLAY_SLOT_BACK_HIGH" );
	RegisterControl ( pLineBoxCombo );

	CBasicLineBox* pLineBoxComboLow = new CBasicLineBox;
	pLineBoxComboLow->CreateSub ( this, "BASIC_LINE_BOX_MINIPARTY", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBoxComboLow->CreateBaseBoxMiniParty ( "PARTYDISPLAY_SLOT_BACK_LOW" );
	RegisterControl ( pLineBoxComboLow );

	{
		//add class
		CString strClassKeyword[GLCI_NUM_NEWEST] = 
		{
			"PARTYDISPLAY_SLOT_CLASS_FIGHTER_M",
			"PARTYDISPLAY_SLOT_CLASS_ARMS_M",
			"PARTYDISPLAY_SLOT_CLASS_ARCHER_W",
			"PARTYDISPLAY_SLOT_CLASS_SPIRIT_W",
			"PARTYDISPLAY_SLOT_CLASS_EXTREME_M",
			"PARTYDISPLAY_SLOT_CLASS_EXTREME_W",
			"PARTYDISPLAY_SLOT_CLASS_FIGHTER_W",
			"PARTYDISPLAY_SLOT_CLASS_ARMS_W",
			"PARTYDISPLAY_SLOT_CLASS_ARCHER_M",
			"PARTYDISPLAY_SLOT_CLASS_SPIRIT_M",
			"PARTYDISPLAY_SLOT_CLASS_SCIENCE_M",
			"PARTYDISPLAY_SLOT_CLASS_SCIENCE_W",
			"PARTYDISPLAY_SLOT_CLASS_ASSASSIN_M",
			"PARTYDISPLAY_SLOT_CLASS_ASSASSIN_W",
			"PARTYDISPLAY_SLOT_CLASS_TESTING_M",
			"PARTYDISPLAY_SLOT_CLASS_TESTING_W",
		};

		//add class
		for ( int i = 0; i < GLCI_NUM_NEWEST; i++ )
		{
			m_pClass[i] = CreateControl ( strClassKeyword[i].GetString() );
		}
	}

	m_pRedLineBox = CreateControl ( "PARTYDISPLAY_REDLINEBOX" );
	m_pRedLineBox->SetVisibleSingle ( FALSE );

	/*{//Add School
		CString strSchool[GLSCHOOL_NUM] = 
		{
			"PARTYDISPLAY_SLOT_SCHOOL0",
			"PARTYDISPLAY_SLOT_SCHOOL1",
			"PARTYDISPLAY_SLOT_SCHOOL2"
		};

		for ( int i = 0; i < GLSCHOOL_NUM; i++ )
		{
			m_pSchool[i] = CreateControl ( strSchool[i].GetString() );
		}
	}*/
	
	{

			CBasicProgressBar*	pProgressBar0 = new CBasicProgressBar;
			pProgressBar0->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR0 );
			pProgressBar0->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_FIGHTER_M" );
			pProgressBar0->SetPercent ( 0.3f );
			pProgressBar0->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar0 );
			m_pHP0 = pProgressBar0;
			
			CBasicProgressBar*	pProgressBar1 = new CBasicProgressBar;
			pProgressBar1->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR1 );
			pProgressBar1->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_ARMS_M" );
			pProgressBar1->SetPercent ( 0.3f );
			pProgressBar1->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar1 );
			m_pHP1 = pProgressBar1;
			
			CBasicProgressBar*	pProgressBar2 = new CBasicProgressBar;
			pProgressBar2->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR2 );
			pProgressBar2->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_ARCHER_W" );
			pProgressBar2->SetPercent ( 0.3f );
			pProgressBar2->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar2 );
			m_pHP2 = pProgressBar2;
			
			CBasicProgressBar*	pProgressBar3 = new CBasicProgressBar;
			pProgressBar3->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR3 );
			pProgressBar3->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_SPIRIT_W" );
			pProgressBar3->SetPercent ( 0.3f );
			pProgressBar3->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar3 );
			m_pHP3 = pProgressBar3;
			
			CBasicProgressBar*	pProgressBar4 = new CBasicProgressBar;
			pProgressBar4->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR4 );
			pProgressBar4->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_EXTREME_M" );
			pProgressBar4->SetPercent ( 0.3f );
			pProgressBar4->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar4 );
			m_pHP4 = pProgressBar4;
			
			CBasicProgressBar*	pProgressBar5 = new CBasicProgressBar;
			pProgressBar5->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR5 );
			pProgressBar5->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_EXTREME_W" );
			pProgressBar5->SetPercent ( 0.3f );
			pProgressBar5->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar5 );
			m_pHP5 = pProgressBar5;
			
			CBasicProgressBar*	pProgressBar6 = new CBasicProgressBar;
			pProgressBar6->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR6 );
			pProgressBar6->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_FIGHTER_W" );
			pProgressBar6->SetPercent ( 0.3f );
			pProgressBar6->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar6 );
			m_pHP6 = pProgressBar6;
			
			CBasicProgressBar*	pProgressBar7 = new CBasicProgressBar;
			pProgressBar7->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR7 );
			pProgressBar7->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_ARMS_W" );
			pProgressBar7->SetPercent ( 0.3f );
			pProgressBar7->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar7 );
			m_pHP7 = pProgressBar7;
			
			CBasicProgressBar*	pProgressBar8 = new CBasicProgressBar;
			pProgressBar8->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR8 );
			pProgressBar8->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_ARCHER_M" );
			pProgressBar8->SetPercent ( 0.3f );
			pProgressBar8->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar8 );
			m_pHP8 = pProgressBar8;
			
			CBasicProgressBar*	pProgressBar9 = new CBasicProgressBar;
			pProgressBar9->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR9 );
			pProgressBar9->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_SPIRIT_M" );
			pProgressBar9->SetPercent ( 0.3f );
			pProgressBar9->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar9 );
			m_pHP9 = pProgressBar9;
			
			CBasicProgressBar*	pProgressBar10 = new CBasicProgressBar;
			pProgressBar10->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR10 );
			pProgressBar10->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_SCIENCE_M" );
			pProgressBar10->SetPercent ( 0.3f );
			pProgressBar10->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar10 );
			m_pHP10 = pProgressBar10;
			
			CBasicProgressBar*	pProgressBar11 = new CBasicProgressBar;
			pProgressBar11->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR11 );
			pProgressBar11->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_SCIENCE_W" );
			pProgressBar11->SetPercent ( 0.3f );
			pProgressBar11->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar11 );
			m_pHP11 = pProgressBar11;
			
			CBasicProgressBar*	pProgressBar12 = new CBasicProgressBar;
			pProgressBar12->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR12 );
			pProgressBar12->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_ASSASSIN_M" );
			pProgressBar12->SetPercent ( 0.3f );
			pProgressBar12->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar12 );
			m_pHP12 = pProgressBar12;
			
			CBasicProgressBar*	pProgressBar13 = new CBasicProgressBar;
			pProgressBar13->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR13 );
			pProgressBar13->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_ASSASSIN_W" );
			pProgressBar13->SetPercent ( 0.3f );
			pProgressBar13->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar13 );
			m_pHP13 = pProgressBar13;
			
			CBasicProgressBar*	pProgressBar14 = new CBasicProgressBar;
			pProgressBar14->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR15 );
			pProgressBar14->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_TESTING_M" );
			pProgressBar14->SetPercent ( 0.3f );
			pProgressBar14->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar14 );
			m_pHP14 = pProgressBar14;
			
			CBasicProgressBar*	pProgressBar15 = new CBasicProgressBar;
			pProgressBar15->CreateSub ( this, "PARTYDISPLAY_SLOT_HP", UI_FLAG_DEFAULT, HP_BAR15 );
			pProgressBar15->CreateOverImage ( "PARTYDISPLAY_PROGRESSBAR_SLOT_CLASS_TESTING_W" );
			pProgressBar15->SetPercent ( 0.3f );
			pProgressBar15->SetVisibleSingle( FALSE );
			RegisterControl ( pProgressBar15 );
			m_pHP15 = pProgressBar15;
	}

	{
		m_pMaster = CreateControl ( "PARTYDISPLAY_NUMBER_M" );
	}
	
	m_pPlayerHealth = CreateStaticControl ( "PARTYDISPLAY_SLOT_PLAYER_HEALTH", pFont9, NS_UITEXTCOLOR::WHITE, nTextAlign );
	m_pPlayerName = CreateStaticControl ( "PARTYDISPLAY_SLOT_PLAYER_NAME", pFont9, NS_UITEXTCOLOR::WHITE, nTextAlign );
}

CUIControl*	CPartySlotDisplay::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );
	return pControl;
}

CBasicTextBox* CPartySlotDisplay::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	return pStaticText;
}

void CPartySlotDisplay::SetNumber ( int nSlotNumber )
{
	if ( nSlotNumber < 0 && MAXPARTY <= nSlotNumber )
	{
		GASSERT ( 0 && "?????? ?????? ??? ?????." );
		return ;
	}

	m_pMaster->SetVisibleSingle ( FALSE );

	if ( nSlotNumber == 0 ) { m_pMaster->SetVisibleSingle ( TRUE ); }

}

void CPartySlotDisplay::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
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
void CPartySlotDisplay::SetClass ( int nClassType )
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

	//add class
	for ( int i = 0; i < GLCI_NUM_NEWEST; i++ )
	{
		m_pClass[i]->SetVisibleSingle ( FALSE );
	}
	m_pClass[nClassType]->SetVisibleSingle ( TRUE );

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

void CPartySlotDisplay::SetPlayerHealth ( int fHPNow, int fHPMax )
{
	CString strHP; strHP.Format ( "%d/%d",fHPNow,fHPMax ); 
	if ( fHPNow == 0 ) 
	{
		m_pPlayerHealth->SetOneLineText( strHP, NS_UITEXTCOLOR::RED ); 
		m_pRedLineBox->SetVisibleSingle ( TRUE );
	}
	else
	{
		m_pPlayerHealth->SetOneLineText( strHP, NS_UITEXTCOLOR::WHITE ); 
		m_pRedLineBox->SetVisibleSingle ( FALSE );
	}
}

void CPartySlotDisplay::SetPlayerPos ( BOOL bSame )
{
	if ( !bSame ){
		m_pPlayerHealth->SetVisibleSingle ( FALSE );
	}else{
		m_pPlayerHealth->SetVisibleSingle ( TRUE );
	}
}


/*void CPartySlotDisplay::SetSchool ( int nSchoolType )
{
	//add class
	for ( int i = 0; i < GLSCHOOL_NUM; i++ )
	{
		m_pSchool[i]->SetVisibleSingle ( FALSE );
	}

	m_pSchool[nSchoolType]->SetVisibleSingle ( TRUE );
}*/