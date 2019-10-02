#include "StdAfx.h"
#include "CPvpWindowDisplay.h"
#include "../BasicLineBoxEx.h"
#include "GLGaeaClient.h"
#include "../InnerInterface.h"
#include "../BasicTextButton.h"
#include "../GameTextControl.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"
#include "../../EngineLib/DxCommon/d3dfont.h"
#include "../BasicTextButton.h" 

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPvpWindowDisplay::CPvpWindowDisplay () :
	m_nActivePage(0),
	m_pMapImg ( NULL ),
	m_pButtonSchoolWarPage( NULL ),
    m_pLineBoxMapImg( NULL ),
	m_pInfo( NULL ),
	m_pReward( NULL ),
	m_pTitle( NULL ),
	m_pStart( NULL ),
	m_pEnd( NULL ),
	m_bQueue( FALSE ),
	fRegTime( 0.0f ),
	m_pTimeTextNext( NULL ),
	m_pButtonClose( NULL ),
	m_pButtonParticipate ( NULL ),
	m_pLineBoxBottomEx( NULL ),
	m_pLineBoxBattle ( NULL ),
	m_pLineBoxPrevious( NULL ),
	m_pWinnerIconNone( NULL ),
	//
	m_pLineBoxBuff00( NULL ),
	m_pLineBoxBuff01( NULL ),
	m_pLineBoxBuff02( NULL ),
	//m_pLineBoxBuff03( NULL ),
	//
	m_bCHECK_MOUSE_STATE( false ),
    m_bFirstGap(FALSE),
	m_PosX(0),
	m_PosY(0),
	m_pLineBoxUpper( NULL ),
	m_pLineBoxBottom( NULL ),
	m_pLineBoxTopWhite ( NULL ),
	m_pTextProgress ( NULL ),
	m_pTextRegister ( NULL ),
	m_pLineBoxBottomWhite ( NULL )


{
	for(int i = 0; i < 3; i++ )
	{
		m_pWinnerIcon[i] = NULL;
	}
}

CPvpWindowDisplay::~CPvpWindowDisplay ()
{
}

CBasicTextButton*  CPvpWindowDisplay::CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE23;
	CBasicTextButton* pTextButton = new CBasicTextButton;
	pTextButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE|UI_FLAG_YSIZE, ControlID );
	pTextButton->CreateBaseButtonEx ( szButton, nBUTTONSIZE, CBasicButton::RADIO_FLIP, szText );
	RegisterControl ( pTextButton );
	return pTextButton;
}

CBasicTextButton* CPvpWindowDisplay::CreateTextButton ( char* szButton, UIGUID ControlID , char* szText )
{
	const int nBUTTONSIZE = CBasicTextButton::SIZE19;
	CBasicTextButton* pButton = new CBasicTextButton;
	pButton->CreateSub( this, "BASIC_TEXT_BUTTON19", UI_FLAG_XSIZE, ControlID );
	pButton->CreateBaseButton( szButton, nBUTTONSIZE, CBasicButton::CLICK_FLIP, szText );
	RegisterControl( pButton );

	return pButton;
}

void CPvpWindowDisplay::CreateSubControl ()
{	
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_FLAG );
	D3DCOLOR dwColor = NS_UITEXTCOLOR::WHITE;

	m_pLineBoxTop = new CBasicLineBoxEx;
	m_pLineBoxTop->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxTop->CreateBaseBoxDialogueBlackBack ( "PVP_LINEBOX_TOP" );
	m_pLineBoxTop->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxTop );

	
	m_pLineBoxTopWhite = new CBasicLineBoxEx;
	m_pLineBoxTopWhite->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxTopWhite->CreateBaseBoxDialogueWhiteBack ( "PVP_LINEBOX_BODY_WHITE" );
	m_pLineBoxTopWhite->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxTopWhite );
	
	m_pLineBoxBottomWhite = new CBasicLineBoxEx;
	m_pLineBoxBottomWhite->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxBottomWhite->CreateBaseBoxDialogueBlackBack ( "PVP_LINEBOX_TOP_EX" );
	m_pLineBoxBottomWhite->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxBottomWhite );

	m_pLineBoxUpper = new CBasicLineBoxEx;
	m_pLineBoxUpper->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxUpper->CreateBaseBoxDialogueGrayBack ( "PVP_LINEBOX_UPPER" );
	m_pLineBoxUpper->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxUpper );
	
	m_pLineBoxBottom = new CBasicLineBoxEx;
	m_pLineBoxBottom->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxBottom->CreateBaseBoxDialogueBlackBack ( "PVP_LINEBOX_UPPER_EX" );
	m_pLineBoxBottom->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxBottom );

	m_pLineBoxMapImg = new CBasicLineBoxEx;
	m_pLineBoxMapImg->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxMapImg->CreateBaseBoxDialogueGrayBack ( "PVP_LINEBOX_MAP_IMG" );
	m_pLineBoxMapImg->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxMapImg );

	m_pLineBoxBottomEx = new CBasicLineBoxEx;
	m_pLineBoxBottomEx->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxBottomEx->CreateBaseBoxMiniParty ( "PVP_LINEBOX_BOTTOM_EX" );
	m_pLineBoxBottomEx->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxBottomEx );

	m_pLineBoxBattle = new CBasicLineBoxEx;
	m_pLineBoxBattle->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxBattle->CreateBaseBoxDialogueBlackBack ( "PVP_LINEBOX_BATTLE" );
	m_pLineBoxBattle->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxBattle );

	m_pLineBoxPrevious = new CBasicLineBoxEx;
	m_pLineBoxPrevious->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxPrevious->CreateBaseBoxDialogueBlackBack ( "PVP_LINEBOX_PREVIOUS" );
	m_pLineBoxPrevious->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxPrevious );

    // reward buff linevox
	m_pLineBoxBuff00 = new CBasicLineBoxEx;
	m_pLineBoxBuff00->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxBuff00->CreateBaseBoxDialogueGrayBack ( "PVP_LINEBOX_BUFF00" );
	m_pLineBoxBuff00->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxBuff00 );

	m_pLineBoxBuff01 = new CBasicLineBoxEx;
	m_pLineBoxBuff01->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxBuff01->CreateBaseBoxDialogueGrayBack ( "PVP_LINEBOX_BUFF01" );
	m_pLineBoxPrevious->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxBuff01 );

	m_pLineBoxBuff02 = new CBasicLineBoxEx;
	m_pLineBoxBuff02->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxBuff02->CreateBaseBoxDialogueGrayBack ( "PVP_LINEBOX_BUFF02" );
	m_pLineBoxBuff02->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxBuff02 );

	/*m_pLineBoxBuff03 = new CBasicLineBoxEx;
	m_pLineBoxBuff03->CreateSub ( this, "BASIC_LINE_BOX_EX_DIALOGUE_WHITE", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	m_pLineBoxBuff03->CreateBaseBoxDialogueGrayBack ( "PVP_LINEBOX_BUFF03" );
	m_pLineBoxBuff03->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pLineBoxBuff03 );*/
    // end
	m_pButtonSchoolWarPage = CreateTextButton23 ( "PVP_BUTTON_PAGE", SCHOOLWAR_BUTTON_PAGE, (char*)ID2GAMEWORD ( "PVP_WINDOW_TEXTS", 1 ) );

	m_pTitle = new CBasicTextBox;
	m_pTitle->CreateSub ( this, "COMPETITION_CTF_PAGE_INFO_TITLE" );
	m_pTitle->SetFont ( pFont9 );
	m_pTitle->SetTextAlign ( TEXT_ALIGN_LEFT );
	m_pTitle->SetText( "Tyranny", NS_UITEXTCOLOR::ORANGE );
	RegisterControl ( m_pTitle );
	m_pTitle->SetVisibleSingle( TRUE );

	m_pTitle = new CBasicTextBox;
	m_pTitle->CreateSub ( this, "COMPETITION_CTF_PAGE_NEXT_BATTLE" );
	m_pTitle->SetFont ( pFont9 );
	m_pTitle->SetTextAlign ( TEXT_ALIGN_LEFT );
	m_pTitle->SetText( "<Next Battle>", NS_UITEXTCOLOR::WHITE );
	RegisterControl ( m_pTitle );
	m_pTitle->SetVisibleSingle( TRUE );

	m_pTitle = new CBasicTextBox;
	m_pTitle->CreateSub ( this, "COMPETITION_CTF_PAGE_PREVIOUS_BATTLE" );
	m_pTitle->SetFont ( pFont9 );
	m_pTitle->SetTextAlign ( TEXT_ALIGN_LEFT );
	m_pTitle->SetText( "<Previous Record>", NS_UITEXTCOLOR::WHITE );
	RegisterControl ( m_pTitle );
	m_pTitle->SetVisibleSingle( TRUE );

	m_pInfo = new CBasicTextBox;
	m_pInfo->CreateSub ( this, "COMPETITION_CTF_PAGE_INFO_DESC_TEXT" );
	m_pInfo->SetFont ( pFont9 );
	m_pInfo->SetTextAlign ( TEXT_ALIGN_LEFT );
	m_pInfo->AddTextNoSplit( "<Information>", NS_UITEXTCOLOR::WHITE );
	m_pInfo->AddTextNoSplit( "* Goal: Occupy 3 bases (Occupy half to dominate)", NS_UITEXTCOLOR::WHITE );
	m_pInfo->AddTextNoSplit( "\t(Note. No PET/HP, Only MP/SP are usable)", NS_UITEXTCOLOR::WHITE );
	m_pInfo->AddTextNoSplit( "* Match:     vs     vs ", NS_UITEXTCOLOR::WHITE );
	m_pInfo->AddTextNoSplit( "* Players: No Limit/School ()", NS_UITEXTCOLOR::WHITE );
	m_pInfo->AddTextNoSplit( "* Level: 197 or higher", NS_UITEXTCOLOR::WHITE );
	RegisterControl ( m_pInfo );
	m_pInfo->SetVisibleSingle( TRUE );

	m_pReward = new CBasicTextBox;
	m_pReward->CreateSub ( this, "COMPETITION_CTF_PAGE_INFO_AWARD_TEXT" );
	m_pReward->SetFont ( pFont9 );
	m_pReward->SetTextAlign ( TEXT_ALIGN_LEFT );
	m_pReward->AddTextNoSplit( "<Reward>", NS_UITEXTCOLOR::WHITE );
	m_pReward->AddTextNoSplit( "Win: Contribution Point(s), SW Bonus (School Winner)", NS_UITEXTCOLOR::GREEN );
	m_pReward->AddTextNoSplit( "Lose: Contribution Point(s)", NS_UITEXTCOLOR::GREEN );
	RegisterControl ( m_pReward );
	m_pReward->SetVisibleSingle( TRUE );

	m_pHelp = new CBasicButton;
	m_pHelp->CreateSub ( this, "COMPETITION_CTF_PAGE_HISTORY_RANKING_BUTTON" , UI_FLAG_DEFAULT, HISTORY_HELP );
	m_pHelp->CreateFlip ( "COMPETITION_CTF_PAGE_HISTORY_RANKING_BUTTON_FLIP", CBasicButton::MOUSEIN_FLIP );
	m_pHelp->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pHelp );


	m_pWinnerIconNone = CreateControl( "INFO_CTF_DISPLAY_WINNER_ICON_NONE", INFO_CTF_DISPLAY_WINNER_ICON_NONE );

	CString strSchool[3] = 
	{
		"INFO_CTF_DISPLAY_WINNER_ICON_SG",
		"INFO_CTF_DISPLAY_WINNER_ICON_MP",
		"INFO_CTF_DISPLAY_WINNER_ICON_PHX"
	};

	for(int i = 0; i < 3; i++ )
	{
		m_pWinnerIcon[i] = CreateControl( (char*)strSchool[i].GetString(), INFO_CTF_DISPLAY_WINNER_ICON_SG+i );
		m_pWinnerIcon[i]->SetVisibleSingle(FALSE);
	}



	CString imgSchool[3] = 
	{
		"COMPETITION_CTF_PAGE_INFO_RACE_SCHOOL0",
		"COMPETITION_CTF_PAGE_INFO_RACE_SCHOOL1",
		"COMPETITION_CTF_PAGE_INFO_RACE_SCHOOL2"
	};
	for ( int i = 0; i < 3; ++i )
	{
		m_pSchoolImg[i] = new CUIControl;
		m_pSchoolImg[i]->CreateSub ( this, (char*)imgSchool[i].GetString() );	
		m_pSchoolImg[i]->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pSchoolImg[i] );
	}
	CString strBuffImg[3] = 
	{
		"CTF_REWARD_BUFF_TEXT00",
		"CTF_REWARD_BUFF_TEXT01",
		"CTF_REWARD_BUFF_TEXT02",

	};
	for( int i = 0; i < 3; ++i )
	{
		m_pRewardBuffBack[i] = new CUIControl;
		m_pRewardBuffBack[i]->CreateSub( this,(char*)strBuffImg[i].GetString(), UI_FLAG_DEFAULT, CTF_REWARD_BUFF_TEXT00+i );
		m_pRewardBuffBack[i]->SetVisibleSingle( TRUE );
		RegisterControl( m_pRewardBuffBack[i] );			
	
	}

	CString strText[nTEXT] = 
	{
		"PVP_TEXT_START_TIME",
		"PVP_TEXT_END_TIME",
		"PVP_TEXT_PROGRESS",
		"PVP_TEXT_REGISTRATION",
		"PVP_TEXT_DURATION",
		"PVP_TEXT_WINNER",
		"PVP_TEXT_REWARD",
		"PVP_TEXT_TOP"
	};

	for(int i = 0; i < 8; i++ )
	{
		m_pText[i] = CreateStaticControl( (char*)strText[i].GetString(), pFont9, dwColor, TEXT_ALIGN_LEFT | TEXT_ALIGN_CENTER_Y );
		m_pText[i]->SetText( ID2GAMEWORD("PVP_TEXT_STATIC",i), dwColor );
	}

	m_pMapImg = new CUIControl;
	m_pMapImg->CreateSub ( this, "COMPETITION_CTF_PAGE_INFO_MAP", UI_FLAG_DEFAULT );	
	m_pMapImg->SetVisibleSingle ( TRUE );
	RegisterControl ( m_pMapImg );

	m_pButtonClose = CreateTextButton( "PVP_BUTTON_CLOSE", SCHOOLWAR_BUTTON_CLOSE, (char*)ID2GAMEWORD("COMPETITION_CTF_BATTLE_TEXT",2)); 

	m_pButtonParticipate = CreateTextButton( "SCHOOLWAR_BUTTON_PARTICIPATE", SCHOOLWAR_BUTTON_PARTICIPATE, (char*)ID2GAMEWORD("COMPETITION_CTF_BATTLE_TEXT",0)); 
	m_pTimeTextNext	= CreateStaticControl( "COMPETITION_CTF_PAGE_HISTORY_TIME", pFont9,dwColor, TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
	m_pTextRegister = CreateStaticControl( "INFO_CTF_DISPLAY_REGISTER_TEXT", pFont9,dwColor, TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
	m_pTextProgress = CreateStaticControl( "INFO_CTF_DISPLAY_PROGRESS_TEXT", pFont9,dwColor, TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
	m_pStart = CreateStaticControl( "COMPETITION_CTF_PAGE_BATTLE_STARTTIME_TEXT", pFont9,dwColor, TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
	m_pEnd = CreateStaticControl( "COMPETITION_CTF_PAGE_BATTLE_ENDTIME_TEXT", pFont9,dwColor, TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );

}
void CPvpWindowDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{

	m_bCHECK_MOUSE_STATE = false;
 
	m_PosX = x;
	m_PosY = y;

	Refresh();

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

    if ( GLGaeaClient::GetInstance().m_bTowerWars )
	{
	     m_pButtonParticipate->SetOneLineText("Join",NS_UITEXTCOLOR::WHITE);
	}
	
	if ( IsExclusiveSelfControl() )
	{
		SetGlobalPos ( D3DXVECTOR2 ( x - m_vGap.x, y - m_vGap.y ) );
	}
}
void CPvpWindowDisplay::Refresh()
{
	for(int i = 0; i < 3; i++ ) 
		m_pWinnerIcon[i]->SetVisibleSingle(FALSE);

	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap ();
	int nWinner = pLand->m_dwCTFWINNER;
	if ( nWinner < 0 || nWinner > 2 )
	{
		m_pWinnerIconNone->SetVisibleSingle(TRUE);
		return;
	}

	m_pWinnerIconNone->SetVisibleSingle(FALSE);

	if ( m_pWinnerIcon[nWinner] )
		m_pWinnerIcon[nWinner]->SetVisibleSingle(TRUE);
}
void CPvpWindowDisplay::SetProgressTime(float fElapsedTime)
{
	CString strCombine,strProgress,strRegister;
	int nSec = (int)fElapsedTime%60;
	int nMin = (int)(fElapsedTime/60)%60;
	int nHour = (int)(fElapsedTime/60)/60;
    fRegTime = fElapsedTime;
	if (fElapsedTime > 3600 ) 
	{
      strCombine.Format("%02dh : %02dm : %02ds", nHour, nMin, nSec );
      m_pTextProgress->SetOneLineText( strCombine, NS_UITEXTCOLOR::WHITE );
  }else{
	  if ( fElapsedTime >= 2 )
	  {
	  strCombine.Format("After %02dm : %02ds", nMin, nSec );
      m_pTextProgress->SetOneLineText( strCombine, NS_UITEXTCOLOR::WHITE );
	}else{
	  strCombine.Format("- - : - -");
      m_pTextProgress->SetOneLineText( strCombine, NS_UITEXTCOLOR::WHITE );
	  }
   }
 if ( m_bQueue )
  {
	 strRegister.Format( "Quequed" );
	 m_pTextRegister->SetOneLineText( strRegister, NS_UITEXTCOLOR::FORESTGREEN );
  }else{
	 if ( fRegTime < 600 )
	 {
		 if ( fRegTime >= 2 )
		 {
		 strRegister.Format( "Possible" );
		 m_pTextRegister->SetOneLineText( strRegister, NS_UITEXTCOLOR::FORESTGREEN );
	   }else if ( fRegTime == 0 && GLGaeaClient::GetInstance().m_bTowerWars ) {
		 strRegister.Format( "Not Possible" );
		 m_pTextRegister->SetOneLineText( strRegister, NS_UITEXTCOLOR::DISABLE );
	   }else{
		 strRegister.Format( "~ ~ : ~ ~" );
		 m_pTextRegister->SetOneLineText( strRegister, NS_UITEXTCOLOR::FORESTGREEN );
	   }
	}
   else
	{
		strRegister.Format( "Not Possible" );
		m_pTextRegister->SetOneLineText( strRegister, NS_UITEXTCOLOR::DISABLE );
	 }
  }
}
void CPvpWindowDisplay::SetNextBattleTime(DWORD dwNextBattleStartTime , DWORD dwNextBattleEndTime )
{
	m_pStart->ClearText();
	m_pEnd->ClearText();
	CString strTemp;

	DWORD BattleEndTime = 1; 
	DWORD BattleEndTimeEx = 1;
    if ( dwNextBattleStartTime == 0 ) dwNextBattleStartTime = 24;
	
	BattleEndTime += dwNextBattleStartTime;
	if ( dwNextBattleStartTime == 24 && dwNextBattleEndTime == 24 )
	{
	strTemp.Format("- - : - -",dwNextBattleStartTime);
	m_pStart->SetText( strTemp, NS_UITEXTCOLOR::WHITE );
  }else{
	strTemp.Format("%02d : 00",dwNextBattleStartTime);
	m_pStart->SetText( strTemp, NS_UITEXTCOLOR::WHITE );
	if ( dwNextBattleEndTime == 3600 )
	{
	   if ( dwNextBattleStartTime == 24 ) 
	   {
	      strTemp.Format("%02d : 00",BattleEndTimeEx );
	      m_pEnd->SetText( strTemp, NS_UITEXTCOLOR::WHITE );
	 }else{
	      strTemp.Format("%02d : 00",BattleEndTime );
	      m_pEnd->SetText( strTemp, NS_UITEXTCOLOR::WHITE );
	    }
	}
	else
	{
	strTemp.Format("%02d : %02d",dwNextBattleStartTime, (dwNextBattleEndTime/60));
	m_pEnd->SetText( strTemp, NS_UITEXTCOLOR::WHITE );
	}
  }
}
void CPvpWindowDisplay::SetBattleRecord( DWORD dwPreviousTime, float fLastBattleTime ) 
{
	m_pTimeTextNext->ClearText();
    DWORD dwBattlePreviosEndTime = 1;
    dwBattlePreviosEndTime += dwPreviousTime;
    if ( fLastBattleTime > 0.0f )
	{
       if ( fLastBattleTime >= 3600 )
	   {
		   CString strTemp;
		   strTemp.Format("%02d:00 ~ %02d:00",dwPreviousTime, dwBattlePreviosEndTime);
		   m_pTimeTextNext->SetText( strTemp, NS_UITEXTCOLOR::WHITE );
	 }else{
		   CString strTemp;
		   strTemp.Format("%02d:00 ~ %02d:%02d",dwPreviousTime, dwPreviousTime, ((DWORD)fLastBattleTime/60));
		   m_pTimeTextNext->SetText( strTemp, NS_UITEXTCOLOR::WHITE );

	   }
  }else{
	CString strTemp;
	strTemp.Format("00:00 ~ 00:00");
	m_pTimeTextNext->SetText( strTemp, NS_UITEXTCOLOR::WHITE );

    }
}
void CPvpWindowDisplay::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{

	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( TOWER_RANKING_DISPLAY );
			}
		}break;
	case SCHOOLWAR_BUTTON_PARTICIPATE:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				WORD wLevel = GLGaeaClient::GetInstance().GetCharacter()->m_wLevel;			
				if ( GLGaeaClient::GetInstance().m_bTowerWars )
				{
				 if ( wLevel >= 197 )
				 {
				 GLGaeaClient::GetInstance().GetCharacter()->ReqSchoolWarRejoin();
				 m_pButtonParticipate->SetOneLineText(ID2GAMEWORD("COMPETITION_CTF_BATTLE_TEXT",0),NS_UITEXTCOLOR::WHITE);
			   }else{
				CInnerInterface::GetInstance().PrintConsoleText("Your level must be equal/greater than 197 to proceed.");
				 }
				  break;
				}
				if ( fRegTime > 600 )
				{
				  CInnerInterface::GetInstance().PrintConsoleText("Progress time must be 10mins or less than 10mins to Participate!.");
				  break;
				}
            	  GLGaeaClient::GetInstance().GetCharacter()->ReqSchoolWarParticipate();
			if ( wLevel >= 197  )
			{
				bool Participate = GLGaeaClient::GetInstance().m_bParticipate;
				if ( Participate && !GLGaeaClient::GetInstance().m_bTowerWars )
				{
					m_bQueue = FALSE;
		            m_pButtonParticipate->SetOneLineText(ID2GAMEWORD("COMPETITION_CTF_BATTLE_TEXT",0),NS_UITEXTCOLOR::WHITE);
				}
				else
				{
					m_pButtonParticipate->SetOneLineText(ID2GAMEWORD("COMPETITION_CTF_BATTLE_TEXT",1),NS_UITEXTCOLOR::WHITE);
					m_bQueue = TRUE;
				}
			}else{
				CInnerInterface::GetInstance().PrintConsoleText("Your level must be equal/greater than 197 to proceed.");
			}

			}
		}break;
	case HISTORY_HELP:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "View Top 10" , NS_UITEXTCOLOR::DODGERBLUE );
			}
		}
		break;
	case CTF_REWARD_BUFF_TEXT00:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Gain: X2 EXP", NS_UITEXTCOLOR::PALEGREEN  );
			}
		}
		break;
		case CTF_REWARD_BUFF_TEXT01:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Gain: X2 GOLD", NS_UITEXTCOLOR::PALEGREEN  );
			}
		}
		break;
		case CTF_REWARD_BUFF_TEXT02:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Gain: X2 ITEMDROP", NS_UITEXTCOLOR::PALEGREEN  );
			}
		}
		break;
	/*case CTF_REWARD_BUFF_TEXT03:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Gain: +20% Speed Buff.", NS_UITEXTCOLOR::PALEGREEN  );
			}
		}
		break;	*/
	case INFO_CTF_DISPLAY_WINNER_ICON_SG:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Sacred Gate School", NS_UITEXTCOLOR::WHITE  );
			}
		}
		break;
	case INFO_CTF_DISPLAY_WINNER_ICON_MP:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Mystic Peak School", NS_UITEXTCOLOR::WHITE  );
			}
		}
		break;
	case INFO_CTF_DISPLAY_WINNER_ICON_PHX:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Phoenix School", NS_UITEXTCOLOR::WHITE  );
			}
		}
		break;
	case INFO_CTF_DISPLAY_WINNER_ICON_NONE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "No School Winner", NS_UITEXTCOLOR::RED  );
			}
		}
		break;	
	case ET_CONTROL_BUTTON:
	case SCHOOLWAR_BUTTON_CLOSE:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				CInnerInterface::GetInstance().HideGroup ( GetWndID () );
			}
		}break;

	case SCHOOLWAR_BUTTON_PAGE:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )	OpenPage( 1 );
		}break;
	}

	if ( !m_bCHECK_MOUSE_STATE )
	{
		CheckMouseState ();
		m_bCHECK_MOUSE_STATE = true;
	}

	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );
}

void CPvpWindowDisplay::SetVisibleSingle ( BOOL bVisible )
{
	CUIWindowEx::SetVisibleSingle( bVisible );

	if( bVisible )
	{
		OpenPage( 1 );
	}
}

void CPvpWindowDisplay::CheckMouseState ()
{
	const DWORD dwMsg = GetMessageEx ();
	if ( CHECK_MOUSE_IN ( dwMsg ) )
	{
		if( UIMSG_LB_DUP & dwMsg )
			return ;
		
		if ( dwMsg & UIMSG_LB_DOWN )
		{
			SetExclusiveControl();	

			if ( !m_bFirstGap )
			{
				UIRECT rcPos = GetGlobalPos ();
				m_vGap.x = m_PosX - rcPos.left;
				m_vGap.y = m_PosY - rcPos.top;
				m_bFirstGap = TRUE;
			}
		}
		else if ( CHECK_LB_UP_LIKE ( dwMsg ) )
		{
			ResetExclusiveControl();
			m_bFirstGap = FALSE;				
		}
	}
	else if ( CHECK_LB_UP_LIKE ( dwMsg ) )		
	{								
		ResetExclusiveControl();
		m_bFirstGap = FALSE;					
	}
}


void CPvpWindowDisplay::OpenPage( int nPage )
{
	if ( m_pButtonSchoolWarPage )	m_pButtonSchoolWarPage->SetFlip ( FALSE );
	
	switch( nPage )
	{
	case 1:
		{
			if ( m_pButtonSchoolWarPage )	m_pButtonSchoolWarPage->SetFlip ( TRUE );
		}break;
	};
}

CBasicTextBox* CPvpWindowDisplay::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	return pStaticText;
}